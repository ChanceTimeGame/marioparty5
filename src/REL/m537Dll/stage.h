/* stage.h -- m537::CStage (stage.cpp): the pond model (0x5F0001) and its companion (0x5F0002, shadowed), the four
 * Dorries (CDorrie, dorrie.h: one per player, at yaw 45 / -45 / 135 / -135), three looping background props
 * (0x5F000F..11), and the creator of the water (CWater, water.h) and the sun flare (CEffect, effect.h).
 * GC (sheet master_camera_stage_dorrie_effect.md §6.1; size 0x34, gm on_setup `li r3,0x34`): CGameObject +0 (vptr
 * +8, m_execFlags +0xC), empty CSingleton<CStage> +0x10 (ms_pointer = game_master.o bss A14), CModel base +0x10
 * (2 + 2 pad), m_sub +0x14, m_dorrie[4] +0x18, m_obj[3] +0x28 (std::auto_ptr). Vtable data_3FC {~ 95AC,
 * on_new_mode 96DC, fw CGameObject::on_update 1DDC} (no on_update override). No minigame.h (no .ctors).
 * CDorrie is only forward-declared here: the auto_ptr<CDorrie> set is instantiated in stage.cpp alone. */
#ifndef M537_STAGE_H
#define M537_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m537 {

class CDorrie;

class CStage : public CGameObject, public CSingleton<CStage>, public CModel {
public:
    enum { NUM_DORRIE = 4, NUM_OBJ = 3 };

    CStage();                           /* fn_1_9290 */
    virtual ~CStage();                  /* fn_1_95AC the auto_ptr arrays via __destroy_arr, m_sub, the CModel base */
    CDorrie* GetDorrie(int i);          /* fn_1_96CC (camera SetWinnerView, player CreateAll) */
    static CStage* GetSingletonPtr() { return ms_pointer; }
    virtual void on_new_mode(int mode); /* fn_1_96DC clears the bit only */
    void CreateDorrie();                /* fn_1_96F4 */
    void CreateObj();                   /* fn_1_97C8 */

    /* 0x10 CModel base 0x5F0001 (layer 0, 0x40000001): a base, not a member -- the ctor builds it before the vptr
     * store and reads id() through a null-checked this -> CModel* conversion (m532 CMapMan's shape) */
    std::auto_ptr<CModel> m_sub;             /* 0x14 0x5F0002 (layer 0, shadow caster) */
    std::auto_ptr<CDorrie> m_dorrie[NUM_DORRIE]; /* 0x18 __construct_array (defctor 94F4 calls the ctor 9928) */
    std::auto_ptr<CModel> m_obj[NUM_OBJ];    /* 0x28 0x5F000F..11 __construct_array (defctor 9490, 3 insns) */
};

} // namespace m537

#ifndef __MWERKS__
template <> m537::CStage* CSingleton<m537::CStage>::ms_pointer; /* defined in game_master.cpp (bss A14) */
#endif

#endif
