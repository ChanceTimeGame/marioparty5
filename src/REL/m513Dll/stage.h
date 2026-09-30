/* stage.h -- m513::CStage (stage.cpp): the three stage models (0x470000 lit, shadow map; 0x470001; 0x470002
 * looping), the dark background, and the multi-shadow from the model's "light". Names are ours.
 * GC (0x18, gamemaster `li r3,0x18`; vtable data_78C {~, on_new_mode, on_update}): CGameObject +0x00, empty
 * CSingleton<CStage> +0x10 (ms_pointer = gamemaster.o .bss A1C), m_model0 +0x10, m_model1 +0x12, m_model2 +0x14.
 * stage.cpp does not include minigame.h. */
#ifndef M513_STAGE_H
#define M513_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m513 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();                           /* fn_1_104B0 */
    virtual void on_update();           /* fn_1_10848 empty */
    virtual void on_new_mode(int mode); /* fn_1_1084C */
    virtual ~CStage();                  /* fn_1_10874 */

    /* three named members, not an array: three separate CModel(u32) calls */
    CModel m_model0; /* 0x10 0x470000 lit, shadow map, layer 1 */
    CModel m_model1; /* 0x12 0x470001 layer 1 */
    CModel m_model2; /* 0x14 0x470002 layer 3, loop */
};

} // namespace m513

#ifndef __MWERKS__
template <> m513::CStage* CSingleton<m513::CStage>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
