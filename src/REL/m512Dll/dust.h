/* dust.h -- the skate-stroke dust puffs (dust.cpp; m536 killereff's pattern with one effect class):
 * m512::CDustMan (owns the sprite bank 0x460015, drives the list) and m512::CDust (one self-deleting
 * one-particle puff; CPlayer::updateMove creates them). dust.cpp does not include minigame.h.
 * Class names are ours (W0 proposals). */
#ifndef M512_DUST_H
#define M512_DUST_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m512 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CDustMan> at +0x10, no members; size 0x10
 * (gamemaster `li r3,0x10`). Vtable data_31C {~, on_new_mode, on_update} (0x14, no pad word). */
class CDustMan : public CGameObject, public CSingleton<CDustMan> {
public:
    CDustMan();
    virtual ~CDustMan();
    virtual void on_new_mode(int mode);
    virtual void on_update();
};

/* GC: TLinkItem (CLinkNode) +0x0, m_id +0x8 (Hu3DParticleCreate), m_unk0C +0xC (set to 0, never read);
 * size 0x10 (player `li r3,0x10`). No vptr. Update deletes the puff once the hook marks the particle set
 * dead (dataCnt < 0): the list walk must not read the deleted node (tlink.h, host). */
class CDust : public TLinkItem<CDust> {
public:
    CDust(Vec* pos);           /* fn_1_7B4C: CPlayer::updateMove */
    ~CDust();                  /* fn_1_7C74 Hu3DModelKill(m_id); out-of-line copy unreferenced (inlined) */
    static void DeleteAll();   /* fn_1_7CDC CDustMan dtor */
    static void UpdateAll();   /* fn_1_7DAC */
    static void Update(CDust* d);  /* fn_1_7DDC */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_7E5C */

    static TLinkList<CDust> list; /* bss A38; its DestructorChain A2C */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CDustMan* CSingleton<m512::CDustMan>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
