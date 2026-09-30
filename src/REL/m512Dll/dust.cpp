/* dust.cpp -- the skate-stroke dust puffs (m536 killereff.cpp's shapes, one effect class).
 * Retail order: CDustMan ctor/dtor/on_new_mode/on_update, then CDust ctor, the TLinkItem<CDust> dtor copy
 * (weak), the dtor, DeleteAll, UpdateAll, Update, the particle hook; the list walk, __sinit and the list dtor
 * follow at the end of the unit (template instances).
 * SKELETON: bodies written from the W0 sheet (zako_heiho_dust.md §4) on killereff's; the fork verifies them. */
#include "REL/m512Dll/dust.h"
#include "REL/mgcpp/random.h"

namespace m512 {

/* lbl_1_bss_A28: the particle sprite bank (declared before the list: first in .bss) */
static ANIMDATA* s_anim;

TLinkList<CDust> CDust::list;

CDustMan::CDustMan()
{
    s_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x460015, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(s_anim);
}

CDustMan::~CDustMan()
{
    CDust::DeleteAll();
    HuSprAnimKill(s_anim);
}

void CDustMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CDustMan::on_update()
{
    CDust::UpdateAll();
}

CDust::CDust(Vec* pos)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_anim, 1);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, 30.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CDust::~CDust()
{
    Hu3DModelKill(m_id);
}

void CDust::DeleteAll()
{
    while (!list.isEmpty()) {
        CDust* d = list.last();
        delete d;
    }
}

void CDust::UpdateAll()
{
    TLinkList<CDust>::exec(&list, Update);
}

/* deletes d once the hook has marked the particle set dead (the host list walk reads next first) */
void CDust::Update(CDust* d)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[d->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete d;
    }
}

/* one puff: rises (vel.y 5..7), spreads +-2 in x/z, alpha 0x80 fades by 12 a frame, then the set is dead */
void CDust::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int count = 0;
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->vel.x = 4.0f * (CRandom::randomMantissa() - 0.5f);
            data->vel.y = 5.0f + 2.0f * CRandom::randomMantissa();
            data->vel.z = 4.0f * (CRandom::randomMantissa() - 0.5f);
            data->pos.x = data->pos.y = data->pos.z = 0.0f;
            data->color.r = 0xFF;
            data->color.g = 0xFF;
            data->color.b = 0xFF;
            data->color.a = 0x80;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        int a = data->color.a;
        a -= 12;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
}

} // namespace m512
