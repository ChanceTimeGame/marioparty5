#ifndef M539_EFFECT_H
#define M539_EFFECT_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/tlink.h"

namespace m539 {

class CEffect : public TLinkItem<CEffect> {
public:
    /* fn_1_C8DC: the particle hook, ((CEffect*)particle->work)->update(mtx) */
    static void Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx);
    CEffect(Vec* pos);                  /* fn_1_C920 */
    ~CEffect();                         /* fn_1_CB30 unreferenced (dead: nothing deletes a CEffect) */
    void init(HU3DPARTICLE* particle);  /* fn_1_CBAC `this` unused: the 16 particles on a ring */
    void update(Mtx mtx);               /* fn_1_CE40 mtx unused: fade in to 220, out by 16; hide when all done */

    HU3DMODELID m_id;          /* 0x08 Hu3DParticleCreate */
    ANIMDATA* m_anim;          /* 0x0C HuSprAnimRead(0x61000C), locked */
    HU3DPARTICLE* m_particle;  /* 0x10 Hu3DData[m_id].hookData; its work points back here */
    bool m_done;               /* 0x14 */
};

} // namespace m539

#endif
