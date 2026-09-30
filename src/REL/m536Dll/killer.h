/* killer.h -- the Bullet Bills (killer.cpp): m536::CKillerMan (the manager: master model, per-player fire
 * cooldown, owns the pool) and m536::CKiller (one bill of the pool of 8, a PTMF state machine).
 * killer.cpp does not include minigame.h. Class names are ours (W0 proposals). */
#ifndef M536_KILLER_H
#define M536_KILLER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m536 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CKillerMan> at +0x10, m_model +0x10, m_slot[4] +0x14
 * (stride 8); size 0x34 (game_master `li r3,0x34`). Vtable data_65C {~, on_new_mode, on_update}. */
class CKillerMan : public CGameObject, public CSingleton<CKillerMan> {
public:
    /* per-player fire cooldown. GC size 8 */
    struct Slot {
        bool active; /* 0x0 (lbz; cmplwi 1) */
        int timer;   /* 0x4 frames since the shot (signed int->float) */
    };

    CKillerMan();
    virtual ~CKillerMan();
    virtual void on_update();
    /* fn_1_E5B8: false while player no's cooldown runs or no bill is free (CPlayer ignores the result) */
    bool Shoot(int no, Vec* pos, float rot);
    virtual void on_new_mode(int mode);

    CModel m_model;  /* 0x10 data 0x5E000A, DISPOFF: the bills are Hu3DModelLink copies of it */
    Slot m_slot[4];  /* 0x14 */
};

/* A plain list item (no vptr). GC: TLinkItem (CLinkNode) +0x0, m_state +0x8 (12-byte PTMF), m_model +0x14,
 * m_active +0x16, m_index +0x18, m_owner +0x1C, m_timer +0x20, m_pos +0x24, m_vel +0x30, m_rot +0x3C;
 * size 0x40 (killer `li r3,0x40`). */
class CKiller : public TLinkItem<CKiller> {
public:
    typedef void (CKiller::*StateFunc)();

    CKiller(CModel* master, int index);
    /* fn_1_E7BC: another owner's active bill within 50 (XZ) of pos explodes; also inlined in stateFly */
    static bool CheckHit(int owner, Vec* pos);
    static void DeleteAll();  /* fn_1_E8D4: CKillerMan dtor and CGameMaster::on_close */
    static void UpdateAll();  /* fn_1_E9A8: Update each, then rotate the list by one */
    void start(int no, Vec* pos, float rot);             /* fn_1_EA2C; inlined in Launch */
    static bool Launch(int no, Vec* pos, float rot);      /* fn_1_EC28: first idle bill */
    static void Update(CKiller* k);                       /* fn_1_EE68 */
    void stateFly();      /* fn_1_EF4C */
    void stateExplode();  /* fn_1_F3CC */
    void stateIdle();     /* fn_1_F4A8 */
    /* by value: retail copies each PTMF constant to a stack temporary before storing it */
    void setState(StateFunc state) { m_state = state; }

    static TLinkList<CKiller> list; /* bss ABC; its DestructorChain AB0 */

    StateFunc m_state;  /* 0x08 (12 bytes on CW) */
    CModel m_model;     /* 0x14 Hu3DModelLink of CKillerMan::m_model */
    bool m_active;      /* 0x16 */
    int m_index;        /* 0x18 pool index 0..7 (written only) */
    int m_owner;        /* 0x1C player no (signed compare); retail leaves it and the rest uninitialised */
    int m_timer;        /* 0x20 flight frames */
    Vec m_pos;          /* 0x24 */
    Vec m_vel;          /* 0x30 RotY(rot) * {0,0,25} */
    float m_rot;        /* 0x3C yaw, degrees */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CKillerMan* CSingleton<m536::CKillerMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
