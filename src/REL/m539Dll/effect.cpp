/* effect.cpp -- m539::CEffect, the block's ring burst. Retail order: Hook, ctor, [~TLinkItem<CEffect>], dtor,
 * init, update. (sheet player_input_heiho_effect.md §4) */
#include "REL/m539Dll/effect.h"
#include "REL/mgcpp/random.h"

namespace m539 {

void CEffect::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CEffect* self = (CEffect*)particle->work;
    self->update(mtx);
}

CEffect::CEffect(Vec* pos)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x61000C, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    int id = Hu3DParticleCreate(m_anim, 16); /* int: retail sign-extends it at every use */
    m_particle = (HU3DPARTICLE*)Hu3DData[(HU3DMODELID)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet(id, Hook);
    Hu3DParticleColSet(id, 240, 240, 240);
    Hu3DParticleTPLvlSet(id, 0.0f);
    Hu3DParticleBlendModeSet(id, 0);
    Hu3DModelLayerSet(id, 5);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    m_id = id;
    m_done = true;
    init(m_particle);
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(m_id, pos->x, pos->y, pos->z);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    m_done = false;
    Hu3DModelAttrReset(m_id, HU3D_ATTR_DISPOFF);
}

CEffect::~CEffect()
{
    m_particle->work = 0;
    Hu3DModelKill(m_id);
    HuSprAnimKill(m_anim);
}

void CEffect::init(HU3DPARTICLE* particle)
{
    /* the 16 particles on a ring, each with a random offset, alpha step (parManId) and spin */
    HU3DPARTICLEDATA* data = particle->data;
    for (int i = 0; i < particle->maxCnt; i++, data++) {
        data->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
        data->vel.y = cos(0.017453292f * (360.0f * i / particle->maxCnt));
        data->vel.z = 0.0f;
        data->scale = 50.0f;
        data->pos.x = 100.0f * (0.01f * ((CRandom::irandom() & 0x3F) - 31.0f));
        data->pos.y = 100.0f * (0.01f * ((CRandom::irandom() & 0x3F) - 31.0f));
        data->pos.z = 0.0f;
        data->color.a = 0;
        data->time = 0;
        data->parManId = (CRandom::irandom() & 0xF) + 15;
        data->zRot = 0.017453292f * CRandom::frandom(0.0f, 360.0f);
    }
}

void CEffect::update(Mtx mtx)
{
    /* fade in to 220 by parManId, out by 16; grow and drift outward; hide the model when all are done */
    if (!m_done) {
        HU3DMODEL* model = &Hu3DData[m_id]; /* retail: unused */
        HU3DPARTICLE* particle = m_particle;
        bool allDone = true;
        HU3DPARTICLEDATA* data = particle->data;
        for (int i = 0; i < particle->maxCnt; i++, data++) {
            if (data->time == 2) {
                continue;
            }
            if (data->time == 0) {
                data->color.a += data->parManId;
                if (data->color.a >= 220) {
                    data->color.a = 220;
                    data->time++;
                }
            } else if (data->color.a > 16) {
                data->color.a -= 16;
            } else {
                data->color.a = 0;
                data->time++;
            }
            data->scale += 2.5;
            data->pos.x += 0.016666666666666666 * (100.0f * (1.5f * data->vel.x));
            data->pos.y += 0.016666666666666666 * (100.0f * (1.5f * data->vel.y));
            allDone = false;
        }
        DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
        m_done = allDone;
        if (m_done) {
            Hu3DModelAttrSet(m_id, HU3D_ATTR_DISPOFF);
        }
    }
}

} // namespace m539
