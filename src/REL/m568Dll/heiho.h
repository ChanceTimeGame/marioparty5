/* heiho.h -- m568::CHeiho (heiho.cpp): the skiing Shy Guy prop. A body (0x7B0011, shape motion 0x7B0012) holding
 * two items (0x7B0014) on "itemhook_L"/"itemhook_R", riding a ski model (0x7B0013) through its "ski-itemhook-h"
 * hook. Created by CStage::on_update into an auto_ptr (stage +0x24) once the scroll passes -9000; stage drives it.
 * heiho.cpp has no update and does not include minigame.h. Names are ours.
 * GC: four auto_ptr<CModel>: m_body +0, m_itemL +4, m_itemR +8, m_ski +0xC; size 0x10 (stage `li r3,0x10`). No vptr,
 * no base. The dtor is the implicit inline one (stage inlines it: ~CModel(+0xC), (+8), (+4), (+0)). */
#ifndef M568_HEIHO_H
#define M568_HEIHO_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include <memory>

namespace m568 {

/* fn_1_98A0 (unreferenced; inlined 4x into the ctor): Hu3DModelShadowSet + ShadowDispOn (name ours) */
void ShadowOn(s16 id);

class CHeiho {
public:
    CHeiho(); /* fn_1_98D8 */

    std::auto_ptr<CModel> m_body;  /* 0x00 0x7B0011 */
    std::auto_ptr<CModel> m_itemL; /* 0x04 0x7B0014 */
    std::auto_ptr<CModel> m_itemR; /* 0x08 0x7B0014 */
    std::auto_ptr<CModel> m_ski;   /* 0x0C 0x7B0013 */
};

} // namespace m568

#endif
