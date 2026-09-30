/* gun.h -- the corner cannons (gun.cpp): m536::CGunMan (three master models) and one m536::CGun per player
 * (three linked models: aim barrel, base, damage drum). gun.cpp does not include minigame.h.
 * Class names are ours (W0 proposals). */
#ifndef M536_GUN_H
#define M536_GUN_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"

namespace m536 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CGunMan> at +0x10, CModels +0x10/+0x12/+0x14; size 0x58
 * (game_master `li r3,0x58`). Vtable data_6A8 {~, on_new_mode, on_update}. */
class CGunMan : public CGameObject, public CSingleton<CGunMan> {
public:
    CGunMan();
    virtual ~CGunMan();
    virtual void on_update();
    virtual void on_new_mode(int mode);

    CModel m_barrel; /* 0x10 data 0x5E0008 DISPOFF (master of CGun::m_barrel) */
    CModel m_base;   /* 0x12 data 0x5E0006 DISPOFF (master of CGun::m_base) */
    CModel m_drum;   /* 0x14 data 0x5E0009 DISPOFF (master of CGun::m_drum) */
    /* 0x16..0x57: never constructed, read or written by any code in the REL (W0 killer_gun §9 Q1); kept so
     * that `new CGunMan` asks for retail's 0x58 bytes on GC. Only its size is known. */
    u8 m_unk16[0x42];
};

/* A plain list item (no vptr). GC: TLinkItem (CLinkNode) +0x0, m_state +0x8 (12-byte PTMF), models
 * +0x14/+0x16/+0x18, m_no +0x1C, m_pos +0x20, m_rot +0x2C, m_counter +0x30; size 0x34 (gun `li r3,0x34`). */
class CGun : public TLinkItem<CGun> {
public:
    typedef void (CGun::*StateFunc)();

    CGun(CModel* barrel, CModel* base, CModel* drum, int no);
    static void DeleteAll();            /* fn_1_FBF8: CGunMan dtor */
    static void UpdateAll();            /* fn_1_FCE4 */
    static void Update(CGun* g);        /* fn_1_FD14 */
    void stateNull();                   /* fn_1_FF28 empty, unreferenced (name/signature ours) */
    void stateIdle();                   /* fn_1_FF2C empty; the only state */
    static void SetRot(int no, float rot);  /* fn_1_FF30 CPlayer::updateRotate */
    static void SetPos(int no, Vec* pos);   /* fn_1_FF9C CPlayer::updateRotate */
    static void PlayWin(int no);            /* fn_1_1001C CPlayer::SetRank (the one survivor) */
    static void Fire(int no);               /* fn_1_100D0 CPlayer (recoil, even when the shot was refused) */
    static void SetDamage(int no, int hp);  /* fn_1_10180 CPlayer::CheckHit */
    /* by value: retail copies each PTMF constant to a stack temporary before storing it */
    void setState(StateFunc state) { m_state = state; }

    static TLinkList<CGun> list; /* bss AD4; chain AC8 */

    StateFunc m_state;  /* 0x08 (12 bytes on CW) */
    CModel m_barrel;    /* 0x14 layer 4: aim yaw */
    CModel m_base;      /* 0x16 layer 3: corner yaw, y - 60 */
    CModel m_drum;      /* 0x18 layer 4: spins; its motion shows the damage */
    int m_no;           /* 0x1C player 0..3 */
    Vec m_pos;          /* 0x20 */
    float m_rot;        /* 0x2C aim yaw, degrees */
    int m_counter;      /* 0x30 frame counter (& 0x3FF) */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CGunMan* CSingleton<m536::CGunMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
