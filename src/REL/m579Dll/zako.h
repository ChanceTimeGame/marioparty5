#ifndef M579_ZAKO_H
#define M579_ZAKO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m579 {

class CZakoMan : public CGameObject, public CSingleton<CZakoMan> {
public:
    enum { NUMBEROF_PMOTION = 2, NUM_ZAKO_S = 12, NUM_ZAKO_L = 6, NUM_PUKU = 5 };

    CZakoMan();                         /* fn_1_15AD8 assert zako.cpp:53 */
    s16 createMotion(int dataNum);      /* fn_1_15FC8 (= m512 E904) */
    virtual ~CZakoMan();                /* fn_1_16060 CZako::DeleteAll, CPuku::DeleteAll */
    virtual void on_update();           /* fn_1_161A8 CZako::UpdateAll, CPuku::UpdateAll */
    virtual void on_new_mode(int mode); /* fn_1_161CC (= m512 EAF4) */

    std::vector<s16> m_mot_id;  /* 0x10 joint motions of m_model0 (CZako / CPuku / CJugem's fish) */
    CModel m_model0;            /* 0x1C 0x850006 master, DISPOFF */
    CModel m_model1;            /* 0x1E 0x850007 master, DISPOFF */
};

class CZako : public TLinkItem<CZako> {
public:
    typedef void (CZako::*StateFunc)();

    CZako(CModel* master, const Vec* pos, bool kind); /* fn_1_161F4 */
    static void DeleteAll();            /* fn_1_163FC (= m536 E8D4) */
    static void UpdateAll();            /* fn_1_164D0 (= m512 zako F070) */
    static void Update(CZako* z);       /* fn_1_16554 */
    void updateModel();                 /* fn_1_165A8 (m512 F168) */
    void setMotion(int motion, bool once); /* fn_1_16624 unreferenced (inlined in stateSwim) (m512 F3F0) */
    void SetCourse();                   /* fn_1_16724 */
    void stateSwim();                   /* fn_1_167B0 */
    bool move();                        /* fn_1_169E0 function-local static s_fps (bss 12A0, guard 12A8) */
    bool ClampArea();
    /* by value: retail copies each PTMF constant to a stack temporary before storing it */
    void setState(StateFunc state) { m_state = state; }

    static TLinkList<CZako> s_list;     /* bss 1294; its DestructorChain 1288 */

    int m_unk08;          /* 0x08 never accessed */
    StateFunc m_state;    /* 0x0C (12 bytes on CW) */
    int m_motion;         /* 0x18 -1 */
    int m_unk1C;          /* 0x1C 0, never read */
    Vec m_pos;            /* 0x20 */
    int m_count;          /* 0x2C ++, never read */
    float m_phase;        /* 0x30 wiggle phase, degrees */
    CModel m_model;       /* 0x34 */
    float m_yaw;          /* 0x38 degrees */
    float m_speed;        /* 0x3C */
    float m_targetSpeed;  /* 0x40 */
    bool m_kind;          /* 0x44 */
    int m_unk48;          /* 0x48 never accessed */
    int m_turnTimer;      /* 0x4C irandom() & 0x82 */
    float m_turnRate;     /* 0x50 degrees / frame */
};

class CJugem : public CGameObject, public CSingleton<CJugem> {
public:
    typedef void (CJugem::*StateFunc)();
    enum { NUMBEROF_PMOTION = 2 };

    CJugem();                           /* fn_1_16F3C assert zako.cpp:352 */
    virtual ~CJugem();                  /* fn_1_172DC */
    s16 createMotion(int dataNum);      /* fn_1_17430 */
    virtual void on_update();           /* fn_1_174C8 new CSplash + PlaySe when the fish surfaces */
    void stateEnter();                  /* fn_1_17768 */
    void stateShow();                   /* fn_1_17944 */
    void stateLeave();                  /* fn_1_17A08 */
    void stateHide();                   /* fn_1_17B40 */
    void setMotion(int motion, bool once); /* fn_1_17BD0 */
    void CreateLineHook();              /* fn_1_17C8C */
    static void Hook(HU3DMODEL* model, Mtx* mtx); /* fn_1_17D64 ((CJugem*)hookData)->DrawLine(mtx) */
    void DrawLine(Mtx* mtx);            /* fn_1_17DA8 mtx unused, no GXLoadPosMtxImm (retail) */
    virtual void on_new_mode(int mode); /* fn_1_17FD4 mode 2: stateHide */
    void setState(StateFunc state) { m_state = state; }

    std::vector<s16> m_mot_id;  /* 0x10 */
    StateFunc m_state;          /* 0x1C (12 bytes on CW) */
    int m_motion;               /* 0x28 -1 */
    CModel m_body;              /* 0x2C 0x85000A (object "itemhook_S") */
    CModel m_bait;              /* 0x2E 0x85000B */
    CModel m_fish;              /* 0x30 0x850006 */
    bool m_shown;               /* 0x32 */
    bool m_done;                /* 0x33 */
    int m_timer;                /* 0x34 */
    Vec m_vel;                  /* 0x38 */
    Vec m_pos;                  /* 0x44 */
    float m_fishYaw;            /* 0x50 */
    float m_fishPitch;          /* 0x54 */
    float m_fishAlpha;          /* 0x58 */
    float m_lineOfs;            /* 0x5C */
    s16 m_hookModel;            /* 0x60 Hu3DHookFuncCreate(Hook) */
    bool m_splash;              /* 0x62 */
    float m_angle;              /* 0x64 leave spiral, degrees */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CZakoMan* CSingleton<m579::CZakoMan>::ms_pointer; /* defined in puku2.cpp (bss A14) */
template <> m579::CJugem* CSingleton<m579::CJugem>::ms_pointer;     /* defined in puku2.cpp (bss A10) */
#endif

#endif
