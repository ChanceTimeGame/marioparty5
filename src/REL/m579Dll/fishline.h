#ifndef M579_FISHLINE_H
#define M579_FISHLINE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m579 {

class CPlayer;
class CPuku;

class CFishLineMgr : public CGameObject, public CSingleton<CFishLineMgr> {
public:
    enum { NUM_LINE = 12, NUM_ROD_TEX = 4 };

    CFishLineMgr();                     /* fn_1_10C84 */
    virtual ~CFishLineMgr();            /* fn_1_11140 CFishLine::DeleteAll, HuSprAnimKill x4 */
    virtual void on_update();           /* fn_1_11244 CFishLine::UpdateAll */
    virtual void on_new_mode(int mode); /* fn_1_11264 2: s_active = 1, 3: s_active = 0 */
};

class CFishLine : public TLinkItem<CFishLine> {
public:
    enum { NUM_SEG = 20, NUM_RING = 8, NUM_NODE = 30, BITE_NONE = 8, BITE_BIG = 7 };
    typedef void (*ExecFunc)(CFishLine* p);

    static void Hook(HU3DMODEL* model, Mtx* mtx);      /* fn_1_112C4 ((CFishLine*)hookData)->Draw(mtx) */
    CFishLine(const Vec* pos, int idx, float yaw);    /* fn_1_11308 */
    ~CFishLine();                                     /* fn_1_11610 unreferenced (inlined in DeleteAll) */
    static void DeleteAll();                          /* fn_1_11678 */
    static void UpdateAll();                          /* fn_1_11748 exec(UpdateFunc) */
    static CFishLine* FindFree(const Vec* p);         /* fn_1_11778 player procPlay: the LAST free line within 70 */
    static bool IsBiting(const Vec* p);               /* fn_1_11844 player (COM press) */
    static bool IsBigBite();                          /* fn_1_1191C unreferenced (inlined in UpdateBite) */
    static CFishLine* FindNearestBiting(const Vec* p); /* fn_1_11990 player GetComInput */
    float GetDistXZ(const Vec* p);                    /* fn_1_11C34 player GetComInput */
    void UpdateBite();                                /* fn_1_11E2C */
    void CalcBend();
    void Update();                                    /* fn_1_1246C */
    void UpdateFish();
    static void UpdateFunc(CFishLine* p);             /* fn_1_12CDC Update + UpdateFish */
    static void SetupLineGX();                        /* fn_1_12F38 unreferenced (inlined in Draw) */
    void SetupRodGX(int tex);
    void CalcRodMtx();
    void DrawLine(const Vec* tip);                    /* fn_1_132F4 unreferenced (inlined) GX immediate */
    void Draw(Mtx* mtx);
    void HookFish();                                  /* fn_1_13FE0 player procPlay: CPuku::Catch */
    void ReleaseFish(bool escape);                    /* fn_1_1404C player: CPuku::Launch */

    /* fishman.cpp (the line physics) */
    void initRope();                                  /* fn_1_7B4C (ctor) spacing len/30 (retail) */
    bool updateHook(Vec* shift);                      /* fn_1_7CD8 true when the hook hit the length */
    void moveNode(int i, Vec* v, float t);            /* fn_1_805C unreferenced (inlined in updateRope) */
    void relaxForward();                              /* fn_1_8180 unreferenced (inlined) i = 1..27 (retail) */
    void relaxBackward();                             /* fn_1_826C unreferenced (inlined) */
    void constrainNodes();                            /* fn_1_8358 unreferenced (inlined) dead stack-Vec scale */
    void updateRope(Vec* shift, bool held);           /* fn_1_84EC `int w = i / 29.0f` (retail) */

    static TLinkList<CFishLine> s_lineList; /* bss 1280; its DestructorChain 1274 */

    /* 0x000 CLinkNode (TLinkItem) */
    Vec m_pos;                      /* 0x008 rod base */
    int m_idx;                      /* 0x014 0..11 (s_rodTexNo) */
    float m_yaw;                    /* 0x018 degrees */
    bool m_taken;                   /* 0x01C a player stands at it (player procPlay / procShow) */
    bool m_held;                    /* 0x01D reeling (player procReel) */
    bool m_holdStart;               /* 0x01E tension kick once */
    bool m_wasFree;                 /* 0x01F */
    bool m_justReleased;            /* 0x020 */
    int m_holdCount;                /* 0x024 ++ while held; never initialised, never read (retail) */
    Vec m_axis;                     /* 0x028 bend axis */
    float m_bend[NUM_SEG];          /* 0x034 degrees per segment */
    Mtx m_segMtx[NUM_SEG];          /* 0x084 */
    bool m_drawn;                   /* 0x444 set by Draw: gates the physics */
    bool m_tipValid;                /* 0x445 */
    Vec m_hook;                     /* 0x448 line end relative to the tip (fishman) */
    Vec m_hookVel;                  /* 0x454 (fishman) */
    float m_length;                 /* 0x460 100..600 */
    u8 m_under[NUM_NODE];           /* 0x464 node under water (Draw); [29] = +0x481 the hook */
    Vec m_node[NUM_NODE];           /* 0x484 relative to the tip (fishman) */
    Vec m_nodeVel[NUM_NODE];        /* 0x5EC (fishman) */
    Vec m_tip;                      /* 0x754 world (Draw) */
    Vec m_prevTip;                  /* 0x760 */
    s16 m_hookModel;                /* 0x76C Hu3DHookFuncCreate(Hook) */
    int m_phase;                    /* 0x770 irandom() (low byte used) */
    int m_bite;                     /* 0x774 BITE_NONE / 0..7 */
    int m_biteTimer;                /* 0x778 */
    int m_idle;                     /* 0x77C */
    float m_tension;                /* 0x780 */
    float m_tensionTarget;          /* 0x784 */
    float m_kick;                   /* 0x788 */
    float m_pitch;                  /* 0x78C degrees */
    CPlayer* m_owner;               /* 0x790 the reeling player (getHandMtx) */
    CPuku* m_fish;                  /* 0x794 the hooked Cheep Cheep */
    float m_fishYaw;                /* 0x798 */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CFishLineMgr* CSingleton<m579::CFishLineMgr>::ms_pointer; /* defined in game_master.cpp (bss A28) */
#endif

#endif
