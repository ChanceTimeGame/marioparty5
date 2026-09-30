#ifndef M522_PLAYER_H
#define M522_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <memory>
#include <vector>

namespace m522 {

/* fn_1_F564: SE pan of a world position, 32 + screen x / 9, clamped to 0..127 (= m532 EE18) */
s16 GetPan(Vec* pos);

/* A scalar wrapped into [min, max) (m532's class; player.md §2.5). 0x10 bytes, no vptr. The functions are defined
 * at the end of player.cpp in retail order ctor, diff(v), approach, wrap, get, [templates], diff(a, b). */
class CAngle {
public:
    CAngle(float a, float b, float v);   /* fn_1_14D04 calls wrap out of line (defined after it) */
    float diff(float v);                 /* fn_1_14DF4 diff(m_value, v) */
    float approach(float v, double rate); /* fn_1_14E30 (callers keep the result: stfs f1) */
    float wrap(float v);                 /* fn_1_14EA4 */
    float get();                         /* fn_1_14F40 */
    float diff(float a, float b);        /* fn_1_15430 the shortest signed difference b - a */

    float m_min;   /* 0x0 */
    float m_max;   /* 0x4 */
    float m_range; /* 0x8 */
    float m_value; /* 0xC */
};

/* the COM pad (0x14, name ours): steered yaw + magnitude, and the button words for MgPlayerPadSet */
class CComPad {
public:
    void clear();              /* fn_1_14868 (unreferenced; = the tail of apply) */
    void press(bool edge);     /* fn_1_148B4 btn |= A; edge: btnDown |= A */
    bool steer(Vec* d);        /* fn_1_148DC true when the stick ends at 0 */
    void apply(MGPLAYER* mp);  /* fn_1_14B20 */

    float m_yaw;               /* 0x00 -pi/2 */
    float m_x;                 /* 0x04 */
    float m_y;                 /* 0x08 */
    u32 m_btnDown;             /* 0x0C */
    u32 m_btn;                 /* 0x10 */
};

class CPlayerBase : public TLinkItem<CPlayerBase> {
public:
    typedef void (CPlayerBase::*ProcFunc)();

    ProcFunc m_proc;                     /* 0x08 (12 bytes on CW) -- declared first: the vptr follows it */

    /* vtable slots in declaration order (+8 .. +0x1C) */
    virtual void main() {}               /* fn_1_14CFC weak */
    virtual void ready() {}              /* fn_1_14D00 weak */
    virtual void go() = 0;
    virtual void result() = 0;
    virtual void judge() = 0;            /* AddWinner (gm step 10, CheckEnd's JudgeAll) */
    virtual void draw() = 0;             /* per frame, after m_proc */

    static void CreateAll();
    static void UpdateAll();             /* fn_1_F6E4 exec(Update); MgActorExec; rotates the list (retail) */
    static void ReadyAll();              /* fn_1_F76C every m_proc = &ready */
    static void GoAll();                 /* fn_1_F800 every m_proc = &go */
    static void JudgeAll();              /* fn_1_F894 every judge() */
    static void ResultAll();             /* fn_1_F904 every result() */
    static void DeleteAll();
    static int GetAliveNum();            /* fn_1_FA18 unreferenced */
    static int CheckEnd();               /* fn_1_FA28 0 team out, 1 every survivor grounded, -1 otherwise */
    static CPlayerBase* Find(int idx);   /* fn_1_FA84 unreferenced */
    static CPlayerBase* FindSolo();      /* fn_1_FAF8 unreferenced (inlined in CTeam::procCom) */
    CPlayerBase(int idx);                /* fn_1_FB6C (inlined in both derived ctors) */
    ~CPlayerBase();                      /* fn_1_FEA8 NON-virtual */
    static void Update(CPlayerBase* p);  /* fn_1_FF70 (this->*m_proc)(); draw(); m_vibWait; m_frame */
    void addMotion(u32 dataNum);         /* fn_1_FFF8 (unreferenced; inlined in both createMotions) */
    void setMotion(u32 motion, bool loop); /* fn_1_10070 (unreferenced; inlined 11x) assert player.cpp:257 */
    float getMotionTime();               /* fn_1_10160 (unreferenced; inlined) */
    void setVisible(bool on);            /* fn_1_101CC unreferenced */
    void vibrate(int kind);              /* fn_1_10240 unreferenced (inlined) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it (F76C) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* 0x14 vptr */
    int m_idx;                           /* 0x18 */
    int m_charNo;                        /* 0x1C GwPlayerConf.charNo */
    int m_group;                         /* 0x20 GwPlayerConf.grp: 0 = the solo */
    int m_padNo;                         /* 0x24 -1 for COM */
    int m_dif;                           /* 0x28 */
    int m_vibWait;                       /* 0x2C */
    int m_frame;                         /* 0x30 ++ per frame, never read */
    std::vector<s16> m_motion_id;        /* 0x34 */
    int m_motion;                        /* 0x40 -1 */
};

/* CModel (the character model, CModel(charNo, 2)) is CSolo's SECOND BASE at +0x44, not a member (F6): the ctor
 * stores vptr 740 after it, ~CSolo passes it flag 0 (a member gets -1), and retail converts `this` with a null
 * check to reach it (Hu3DModelHookSet / Hu3DModelObjPosGet). Same offsets as the proven layout. */
class CSolo : public CPlayerBase, public CModel {
public:
    enum { NUMBEROF_MOTION = 5 };
    enum { ACTION_STRIKE = 0, ACTION_RAISE = 1, ACTION_NONE = 2 };
    typedef void (CSolo::*SoloProc)();

    CSolo(int idx);                  /* fn_1_10324 */
    ~CSolo();
    int getAction();                 /* fn_1_108F8 unreferenced (inlined in CTeam::procCom) */
    virtual void go();               /* fn_1_109A4 */
    void procIdle();                 /* fn_1_10A00 */
    void procStrike();               /* fn_1_10DF8 */
    void procRecover();              /* fn_1_1103C */
    void procRaise();                /* fn_1_113BC */
    void procHold();                 /* fn_1_114CC */
    void procWinFloat();             /* fn_1_11694 */
    void procLoseFall();             /* fn_1_117EC */
    void procLoseFly();              /* fn_1_11998 */
    void procWinPose();              /* fn_1_119E8 */
    virtual void result();           /* fn_1_11A20 */
    virtual void judge();            /* fn_1_11D60 */
    virtual void draw();             /* fn_1_11E34 */
    int getInput();                  /* fn_1_12028 */
    int getPadInput();               /* fn_1_12084 */
    int getComInput();               /* fn_1_120DC */
    void createMotions();            /* fn_1_12368 assert player.cpp:669 */
    /* by value, converted to the base PTMF (retail copies the constant twice: F6 go 109A4) */
    void setProc(SoloProc proc) { CPlayerBase::setProc(static_cast<ProcFunc>(proc)); }

    /* 0x44 CModel base */
    int m_action;                    /* 0x48 ACTION_* */
    Vec m_pos;                       /* 0x4C */
    Vec m_vel;                       /* 0x58 */
    float m_strikeY;                 /* 0x64 */
    float m_bobPhase;                /* 0x68 */
    float m_bobAmp;                  /* 0x6C */
    float m_rotY;                    /* 0x70 */
    float m_rotX;                    /* 0x74 */
    std::auto_ptr<CModel> m_item;    /* 0x78 0x500009 (hooked to the hand) */
    std::auto_ptr<CModel> m_itemFx;  /* 0x7C 0x50000A (placed at the hook object each frame) */
    s16 m_itemMot;                   /* 0x80 Hu3DJointMotion(m_itemFx, 0x50000B) */
    float m_itemRotY;                /* 0x84 */
    char* m_hookName;                /* 0x88 CharModelItemHookGet(charNo, 4, 0) */
    int m_unk8C;                     /* 0x8C 0, never written again (a dead guard in procIdle) */
};

class CTeam : public CPlayerBase {
public:
    typedef void (CTeam::*ComFunc)();
    enum { NUMBEROF_MOTION = 3 };

    /* by value, then the base's by-value setProc: retail copies every CTeam proc constant through TWO stack
     * temporaries (12A44 / 12AE4 ...); hides the base setProc, so &CPlayerBase::main converts to ComFunc */
    void setProc(ComFunc proc) { CPlayerBase::setProc(static_cast<ProcFunc>(proc)); }

    CTeam(int idx, const Vec* pos);
    ~CTeam();
    static int CountGrounded();      /* fn_1_12984 */
    virtual void main();             /* fn_1_12A1C checkLanding() */
    virtual void ready();            /* fn_1_12A44 */
    virtual void go();               /* fn_1_12AE4 */
    void procControl();              /* fn_1_12B68 */
    void procFall();                 /* fn_1_12EB0 */
    void burn();
    void procNone();                 /* fn_1_133F8 */
    void procFaceFront();            /* fn_1_133FC */
    virtual void result();           /* fn_1_13550 */
    void eliminate();                /* fn_1_13698 */
    virtual void judge();            /* fn_1_1370C AddWinner for every team object while any survives (retail) */
    void respawn();                  /* fn_1_137D0 unreferenced */
    virtual void draw();             /* fn_1_1384C */
    bool isOnGround();               /* fn_1_13A10 */
    /* fn_1_13A48: the MgActor narrow-phase hook (MGACTOR_PARAM.narrowHook) */
    static int NarrowHook(COL_NARROW_PARAM* a, COL_NARROW_PARAM* b);
    void createMotions();            /* fn_1_13BBC assert player.cpp:1060 */
    void checkLanding();             /* fn_1_13CE8 */
    void comUpdate();                /* fn_1_13DCC (this->*m_comProc)(); m_pushed = 0; m_com.apply(m_mp) */
    void procCom();
    bool findDanger(Vec* out, float radius);
    bool moveTo(Vec* target, float speed);   /* fn_1_14708 */

    bool m_out;                      /* 0x44 eliminated */
    Vec m_startPos;                  /* 0x48 */
    int m_landWait;                  /* 0x54 */
    Vec m_pos;                       /* 0x58 */
    Vec m_vel;                       /* 0x64 */
    float m_rotY;                    /* 0x70 degrees, -90 */
    float m_rotX;                    /* 0x74 */
    MGPLAYER* m_mp;                  /* 0x78 */
    bool m_dropping;                 /* 0x7C */
    bool m_manual;                   /* 0x7D position integrated by hand (MgPlayer paused) */
    ComFunc m_comProc;               /* 0x80 (12 bytes on CW) = &procCom */
    int m_comHold;                   /* 0x8C */
    bool m_wasOnStage;               /* 0x90 */
    bool m_pushed;                   /* 0x91 set by NarrowHook, cleared every COM frame */
    Vec m_pushPos;                   /* 0x94 */
    CComPad m_com;                   /* 0xA0 */
};

} // namespace m522

#endif
