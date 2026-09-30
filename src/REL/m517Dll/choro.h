#ifndef M517_CHORO_H
#define M517_CHORO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m517Dll/a_set.h"
#include <memory>

namespace m517 {

class CPlayer;

class CChoroEff : public CGameObject {
public:
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m); /* fn_1_FAB0 -> Update */
    CChoroEff();                        /* fn_1_FAF4 (unreferenced; inlined in CChoro()) */
    virtual ~CChoroEff();               /* fn_1_FCA0 */
    void Start(Vec* pos);               /* fn_1_FD3C (unreferenced; inlined in CChoro::Update) */
    virtual void on_new_mode(int mode); /* fn_1_FDAC */
    void Init(HU3DPARTICLE* p);         /* fn_1_FDC4 */
    void Update(Mtx m);                 /* fn_1_100E8 re-inits and hides the model when every particle is done */

    HU3DMODELID m_model;      /* 0x10 Hu3DParticleCreate(m_anim, 6) */
    ANIMDATA* m_anim;         /* 0x14 0x4B0011 */
    HU3DPARTICLE* m_particle; /* 0x18 work = this */
    bool m_done;              /* 0x1C idle (hidden) */
};

class CChoro : public TLinkItem<CChoro> {
public:
    typedef void (CChoro::*ProcFunc)();
    enum { NUM_MOT = 3 };

    /* by value: a PTMF store goes through a stack temporary */
    void setProc(ProcFunc proc) { m_proc = proc; }
    void Stop() { setProc(&CChoro::procStop); }

    CChoro();                           /* fn_1_10634 (gamemaster) */
    ~CChoro();                          /* fn_1_10F88 (gamemaster) */
    void SetPos(Vec* pos);              /* fn_1_11048 (unreferenced; inlined) y = -120 */
    void ShowHole();                    /* fn_1_110D4 (unreferenced; inlined in Update) */
    void UnpauseSub();                  /* fn_1_1115C */
    void procNone();                    /* fn_1_111A4 PTMF data_5AC (the ctor's) */
    void procStop();                    /* fn_1_111A8 PTMF header triple (gamemaster data_338) */
    void Appear(int type, float delay); /* fn_1_111AC (unreferenced; inlined) */
    void Duck(bool turn, float yaw);    /* fn_1_11368 (unreferenced; inlined) */
    void Look();                        /* fn_1_11464 */
    void Update();                      /* fn_1_11850 PTMF gamemaster data_38C */
    static void HitPlayer(CChoro* c, CPlayer* p); /* fn_1_121D8 gamemaster ForEachCross<CChoro, CPlayer> */
    void CheckImpact();                 /* fn_1_122AC */

    bool IsActive() const { return m_active; }
    Vec* GetPos() { return &m_sphere.pos; }

    /* 0x00 CLinkNode (TLinkItem), on ASet<CChoro> */
    s16 m_mot[NUM_MOT];       /* 0x08 [0] pop / sink, [1] alt look, [2] idle loop */
    CModel m_hole;            /* 0x0E 0x4B0005 hole (DISPOFF + PAUSE) */
    CModel m_hole2;           /* 0x10 0x4B0006 */
    CModel m_mole;            /* 0x12 0x4B0007 */
    CSphere m_sphere;         /* 0x14 pos (y -120 when placed), r = 30.000002 */
    Vec m_rot;                /* 0x24 degrees */
    bool m_active;            /* 0x30 popping / up */
    bool m_alive;             /* 0x31 placed (cleared when fully sunk) */
    bool m_turn;              /* 0x32 ducking turns toward m_turnYaw */
    float m_turnYaw;          /* 0x34 */
    int m_unk38;              /* 0x38 never accessed */
    int m_type;               /* 0x3C -1 demo, 0 normal */
    float m_time;             /* 0x40 state timer (+1/60) */
    float m_lookTime;         /* 0x44 */
    float m_wait;             /* 0x48 */
    float m_lookInterval;     /* 0x4C (not set by the ctor) */
    float m_lookSpeed;        /* 0x50 (not set by the ctor) */
    float m_upTime;           /* 0x54 (not set by the ctor) */
    float m_appearDelay;      /* 0x58 (not set by the ctor) */
    float m_scale;            /* 0x5C hole scale */
    int m_state;              /* 0x60 0..6 (jump table data_5CC) */
    int m_lookState;          /* 0x64 */
    bool m_altLook;           /* 0x68 */
    std::auto_ptr<CChoroEff> m_eff; /* 0x6C */
    ProcFunc m_proc;          /* 0x70 (12 bytes on CW) */
};

class CChoroMan : public CGameObject, public CSingleton<CChoroMan> {
public:
    typedef void (CChoroMan::*StateFunc)();
    enum { NUM_CHORO = 12 };

    CChoroMan();                        /* fn_1_124B4 (gamemaster) */
    virtual ~CChoroMan();               /* fn_1_126B4 */
    virtual void on_new_mode(int mode); /* fn_1_12780 */
    virtual void on_update();           /* fn_1_1293C */
    void stateIntro();
    void stateDuckIntro();              /* fn_1_12D00 */
    void stateMain();                   /* fn_1_12E64 */
    void stateNone();                   /* fn_1_12EF8 */
    void Spawn();                       /* fn_1_12EFC */
    bool FindSpot(CChoro* begin, CLinkNode* end, Vec* out); /* fn_1_13214 */
    void DuckAll();                     /* fn_1_1342C */

    void setState(StateFunc s) { m_state = s; }

    StateFunc m_state;        /* 0x10 (12 bytes on CW) */
    float m_timer;            /* 0x1C spawn timer (+1/60, 5 s) */
    int m_level;              /* 0x20 moles per spawn (cap 12) */
    Vec m_spot[NUM_CHORO];    /* 0x24 one per mole (list index) */
};

} // namespace m517

#ifndef __MWERKS__
template <> ASet<m517::CChoro>* ASet<m517::CChoro>::sm_ptr;             /* defined in gamemaster.cpp (A1C) */
template <> m517::CChoroMan* CSingleton<m517::CChoroMan>::ms_pointer;   /* defined in effect.cpp (.bss C) */
#endif

#endif
