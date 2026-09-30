/* effect.h -- m568's particle effects (effect.cpp): CEffectMan, the falling snow (one 512-particle Hu3D particle
 * model around camera 1, CPU-written by SnowHook; its density fades over play), and two self-deleting splash
 * classes spawned by tube.cpp, one list each: CEffectA (2 particles, every grounded frame, C0A8) and CEffectB
 * (32 particles, a hard landing, C5F8). The two splash classes are m536 killereff's CKillerSmoke family exactly
 * (masked-identical dtor / DeleteAll / UpdateAll / Update). effect.cpp does not include minigame.h: its __sinit
 * only builds the two lists. Names are ours (W0 proposals).
 * CEffectMan GC: CGameObject +0x00 (vptr +8), empty CSingleton<CEffectMan> at +0x10 (shares the offset with
 * m_snowId), m_snowId +0x10 (s16), m_count +0x14; size 0x18 (game_master `li r3,0x18`). Vtable data_430
 * {~, on_new_mode, on_update} (+ pad). ms_pointer: game_master.o's .bss A10.
 * CEffectA / CEffectB GC: TLinkItem +0, m_id +0x8, m_unk0C +0xC; size 0x10 (tube `li r3,0x10`). No vptr. */
#ifndef M568_EFFECT_H
#define M568_EFFECT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"

namespace m568 {

class CEffectMan : public CGameObject, public CSingleton<CEffectMan> {
public:
    CEffectMan();                        /* fn_1_B668 */
    virtual ~CEffectMan();               /* fn_1_B840 */
    static void SetSnowRate(float t);    /* fn_1_B92C (unreferenced; inlined 2x) t clamped to [0, 1] */
    virtual void on_new_mode(int mode);  /* fn_1_B9E4 */
    virtual void on_update();            /* fn_1_BA04 */
    void createSnow();                   /* fn_1_BC9C */
    static void SnowHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_BD28 */

    s16 m_snowId; /* 0x10 */
    int m_count;
};

class CEffectA : public TLinkItem<CEffectA> {
public:
    CEffectA(Vec* pos, float scale);     /* fn_1_C0A8 tube CollideGround (every grounded frame) */
    ~CEffectA();                         /* fn_1_C1CC Hu3DModelKill(m_id) */
    static void DeleteAll();             /* fn_1_C234 */
    static void UpdateAll();             /* fn_1_C304 */
    static void Update(CEffectA* e);     /* fn_1_C334 deletes e once the hook marked the set dead */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_C3B4 */

    static TLinkList<CEffectA> list; /* bss A44; dtor-chain record A38 */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C = 0, never read */
};

class CEffectB : public TLinkItem<CEffectB> {
public:
    CEffectB(Vec* pos);                  /* fn_1_C5F8 tube CollideGround (hard landing) */
    ~CEffectB();                         /* fn_1_C720 */
    static void DeleteAll();             /* fn_1_C788 */
    static void UpdateAll();             /* fn_1_C858 */
    static void Update(CEffectB* e);     /* fn_1_C888 */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx); /* fn_1_C908 */

    static TLinkList<CEffectB> list; /* bss A58; dtor-chain record A4C */

    HU3DMODELID m_id; /* 0x08 */
    int m_unk0C;      /* 0x0C */
};

} // namespace m568

#ifndef __MWERKS__
template <> m568::CEffectMan* CSingleton<m568::CEffectMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
