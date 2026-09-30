/* killereff.h -- the Bullet Bill particle effects (killereff.cpp): m536::CKillerEffMan (owns the particle
 * sprite bank 0x5E000E and drives the three effect lists) and three self-deleting effects, one list each:
 * CKillerSpark (never constructed: dead retail code), CKillerSmoke (muzzle ring), CKillerBomb (explosion).
 * killereff.cpp does not include minigame.h. Class names are ours (W0 proposals). */
#ifndef M536_KILLEREFF_H
#define M536_KILLEREFF_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m536 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CKillerEffMan> at +0x10, no members; size 0x10
 * (game_master `li r3,0x10`). Vtable data_320 {~, on_new_mode, on_update} (+ .data pad word). */
class CKillerEffMan : public CGameObject, public CSingleton<CKillerEffMan> {
public:
    CKillerEffMan();
    virtual ~CKillerEffMan();
    virtual void on_new_mode(int mode);
    virtual void on_update();
};

/* The three effects: GC TLinkItem (CLinkNode) +0x0, m_id +0x8 (Hu3DParticleCreate), m_unk0C +0xC (set to 0,
 * never read); size 0x10 (killer `li r3,0x10`). No vptr. Each Update deletes its effect once the hook marks
 * the particle set dead (dataCnt < 0): the list walk must not read the deleted node (tlink.h, host). */
class CKillerSpark : public TLinkItem<CKillerSpark> {
public:
    CKillerSpark(Vec* pos);    /* fn_1_7674, never called */
    ~CKillerSpark();           /* fn_1_779C Hu3DModelKill(m_id) */
    static void DeleteAll();   /* fn_1_7804 */
    static void UpdateAll();   /* fn_1_78D4 */
    static void Update(CKillerSpark* e);   /* fn_1_7904 */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_7984 */

    static TLinkList<CKillerSpark> list; /* bss A38; chain A2C */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C */
};

class CKillerSmoke : public TLinkItem<CKillerSmoke> {
public:
    CKillerSmoke(Vec* pos, float rot); /* fn_1_7B3C: CKiller::start */
    ~CKillerSmoke();           /* fn_1_7C8C */
    static void DeleteAll();   /* fn_1_7CF4 */
    static void UpdateAll();   /* fn_1_7DC4 */
    static void Update(CKillerSmoke* e);   /* fn_1_7DF4 */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_7E74 */

    static TLinkList<CKillerSmoke> list; /* bss A4C; chain A40 */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C */
};

class CKillerBomb : public TLinkItem<CKillerBomb> {
public:
    CKillerBomb(Vec* pos);     /* fn_1_8098: CKiller::stateExplode */
    ~CKillerBomb();            /* fn_1_81EC */
    static void DeleteAll();   /* fn_1_8254 */
    static void UpdateAll();   /* fn_1_8324 */
    static void Update(CKillerBomb* e);    /* fn_1_8354 */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_83D4 */

    static TLinkList<CKillerBomb> list; /* bss A60; chain A54 */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CKillerEffMan* CSingleton<m536::CKillerEffMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
