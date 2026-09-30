/* stage.h -- m509::CStage (stage.cpp): the arena models (0x430000 layer 2, 0x430001 layer 0, both looping) and the
 * global light. GC: CGameObject +0x00 (vptr +8), empty CSingleton<CStage> at +0x10, m_model +0x10, m_model2 +0x12;
 * size 0x14 (gamemaster `li r3,0x14`). Vtable data_34A4 {~, on_new_mode, on_update}; ms_pointer bss_44
 * (gamemaster's). stage.cpp is a translation unit of its own: dtk's player split (EB14..12DBC, .data 3438..35B4)
 * covers two retail objects -- stage.o (.text EB14..EE38, .data 3438..34B8 ending with CStage's vtable, its own
 * singleton strings) and player.o (the rest, with the second "ms_pointer != 0"/"singleton.h" copy at 3500). */
#ifndef M509_STAGE_H
#define M509_STAGE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"

namespace m509 {

class CStage : public CGameObject, public CSingleton<CStage> {
public:
    CStage();                          /* fn_1_EB14 */
    virtual void on_update();          /* fn_1_ED28 empty */
    virtual void on_new_mode(int mode);/* fn_1_ED2C */
    virtual ~CStage();                 /* fn_1_ED54 */

    CModel m_model;  /* 0x10 0x430000 layer 2 */
    CModel m_model2; /* 0x12 0x430001 layer 0 */
};

} // namespace m509

#ifndef __MWERKS__
template <> m509::CStage* CSingleton<m509::CStage>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
