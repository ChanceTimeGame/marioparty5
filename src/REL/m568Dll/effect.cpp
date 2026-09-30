#include "REL/m568Dll/effect.h"
#include "REL/mgcpp/random.h"

namespace m568 {

/* lbl_1_bss_A28..A34 (declared before the lists: first in .bss) */
static ANIMDATA* s_animSplash; /* 0x7B0016, locked; both splash classes */
static ANIMDATA* s_animSnow;   /* 0x7B0015 */
static int s_snowMax;          /* 512 */
static int s_snowNum;          /* the active snow particles (<= s_snowMax) */

TLinkList<CEffectA> CEffectA::list;
TLinkList<CEffectB> CEffectB::list;

CEffectMan::CEffectMan()
{
    s_animSplash = HuSprAnimRead(HuDataSelHeapReadNum(0x7B0016, HU_MEMNUM_OVL, HEAP_MODEL));
    s_animSnow = HuSprAnimRead(HuDataSelHeapReadNum(0x7B0015, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(s_animSplash);
    s_snowMax = s_snowNum = 512;
    createSnow();
}

CEffectMan::~CEffectMan()
{
    Hu3DModelKill(m_snowId);
    CEffectA::DeleteAll();
    CEffectB::DeleteAll();
    HuSprAnimKill(s_animSplash);
}

/* the clamp retail inlines (one return temporary, then assigned back) */
template <class T>
inline T Clamp(T x, T lo, T hi)
{
    if (x < lo) {
        return lo;
    }
    if (x > hi) {
        return hi;
    }
    return x;
}

/* fn_1_B92C (unreferenced out-of-line copy; inlined into on_update twice) */
void CEffectMan::SetSnowRate(float t)
{
    t = Clamp(t, 0.0f, 1.0f);
    s_snowNum = s_snowMax * t;
}

void CEffectMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    m_count = 0;
}

/* fn_1_BA04: the snow thins over the first 900 frames of play and drops to 0.2 at the
 * finish */
void CEffectMan::on_update()
{
    if (GetUpdateMode() == 2) {
        int b = 0;
        int e = 900;
        if (m_count >= b && m_count <= e) {
            float n = m_count - b;
            float len = e - b;
            SetSnowRate(1.0 - n / len);
        }
    } else if (GetUpdateMode() == 3) {
        SetSnowRate(0.2f);
    }
    CEffectA::UpdateAll();
    CEffectB::UpdateAll();
    m_count++;
}

/* lbl_1_data_424: the snow model's position (non-const .data) */
static Vec s_zero = { 0.0f, 0.0f, 0.0f };

void CEffectMan::createSnow()
{
    m_snowId = Hu3DParticleCreate(s_animSnow, s_snowMax);
    Hu3DModelPosSetV(m_snowId, &s_zero);
    Hu3DModelLayerSet(m_snowId, 7);
    Hu3DParticleScaleSet(m_snowId, 20.0f);
    Hu3DParticleHookSet(m_snowId, SnowHook);
}

void CEffectMan::SnowHook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    Vec cpos;
    Vec up;
    Vec tgt;
    Hu3DCameraPosGet(1, &cpos, &up, &tgt);
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 1) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            data->pos.x = cpos.x + 1500.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
            data->pos.y = cpos.y * CRandom::randomMantissa();
            data->pos.z = cpos.z - 6000.0f * CRandom::randomMantissa() - 1000.0f;
            data->vel.x = 3.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
            data->vel.y = -10.0f - 3.0f * CRandom::randomMantissa();
            data->vel.z = 3.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
            data->color.r = 0xE0;
            data->color.g = 0xE8;
            data->color.b = 0xFF;
        }
    }
    if (particle->count != 0) {
        int i = 0;
        for (HU3DPARTICLEDATA* data = particle->data; data != end; i++, data++) {
            PSVECAdd(&data->vel, &data->pos, &data->pos);
            if (data->pos.y <= 0.0f || data->pos.z > cpos.z) {
                data->pos.x = cpos.x + 1500.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
                data->pos.y = cpos.y + 200.0f * CRandom::randomMantissa();
                data->pos.z = cpos.z - 6000.0f * CRandom::randomMantissa() - 1000.0f;
                data->vel.x = 3.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
                data->vel.y = -10.0f - 3.0f * CRandom::randomMantissa();
                data->vel.z = 3.0f * (2.0f * (CRandom::randomMantissa() - 0.5f));
            }
            if (s_snowNum > i) {
                data->scale = 20.0f;
            } else {
                data->scale = 0.0f;
            }
        }
        particle->emitCnt = i;
        DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
    }
}

CEffectA::CEffectA(Vec* pos, float scale)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_animSplash, 2);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, scale);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CEffectA::~CEffectA()
{
    Hu3DModelKill(m_id);
}

void CEffectA::DeleteAll()
{
    while (!list.isEmpty()) {
        CEffectA* e = list.last();
        delete e;
    }
}

void CEffectA::UpdateAll()
{
    TLinkList<CEffectA>::exec(&list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CEffectA::Update(CEffectA* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* every grounded frame: a ring thrown out flat (random heading, speed 5) at the particle's own scale as radius,
 * 50 up, slowing (x0.95) and fading (alpha -4). Retail reads data->scale for the radius before it sets it to 100
 * (presumably the ctor's Hu3DParticleScaleSet(m_id, scale): the spawn size from tube.cpp -- a guess). */
void CEffectA::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int count = 0;
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float angle = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            data->vel.x = cos(angle);
            data->vel.y = 0.0f;
            data->vel.z = sin(angle);
            data->pos.x = data->vel.x * data->scale;
            data->pos.y = 50.0f;
            data->pos.z = data->vel.z * data->scale;
            data->vel.x *= 5.0f;
            data->vel.z *= 5.0f;
            data->color.r = 0xE0;
            data->color.g = 0xE8;
            data->color.b = 0xFF;
            data->color.a = 0x80;
            data->scale = 100.0f;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->vel.x *= 0.95;
        data->vel.y *= 0.95;
        data->vel.z *= 0.95;
        int a = data->color.a;
        a -= 4;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
    DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
}

CEffectB::CEffectB(Vec* pos)
{
    insertBack(&list);
    m_id = Hu3DParticleCreate(s_animSplash, 32);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 6);
    Hu3DParticleScaleSet(m_id, 0.0f);
    Hu3DParticleHookSet(m_id, Hook);
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    m_unk0C = 0;
}

CEffectB::~CEffectB()
{
    Hu3DModelKill(m_id);
}

void CEffectB::DeleteAll()
{
    while (!list.isEmpty()) {
        CEffectB* e = list.last();
        delete e;
    }
}

void CEffectB::UpdateAll()
{
    TLinkList<CEffectB>::exec(&list, Update);
}

/* deletes e once the hook has marked the particle set dead (the host list walk reads next first) */
void CEffectB::Update(CEffectB* e)
{
    HU3DPARTICLE* particle = (HU3DPARTICLE*)Hu3DData[e->m_id].hookData;
    if (particle->dataCnt < 0) {
        delete e;
    }
}

/* a hard landing: 32 particles thrown out flat on a ring of radius 100 (random heading, speed 10), rising
 * (vel.y += 0.2 a frame: retail adds to the y velocity, not the scale), slowing (x0.95) and fading (alpha -4) */
void CEffectB::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    if (particle->count == 0) {
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float angle = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            data->vel.x = cos(angle);
            data->vel.y = 0.0f;
            data->vel.z = sin(angle);
            data->pos.x = 100.0f * data->vel.x;
            data->pos.y = 50.0f;
            data->pos.z = 100.0f * data->vel.z;
            data->vel.x *= 10.0f;
            data->vel.z *= 10.0f;
            data->color.r = 0xE0;
            data->color.g = 0xE8;
            data->color.b = 0xFF;
            data->color.a = 0x80;
            data->scale = 150.0f;
        }
    }
    int count = 0;
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->vel.x *= 0.95;
        data->vel.y += 0.2;
        data->vel.z *= 0.95;
        int a = data->color.a;
        a -= 4;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
            particle->dataCnt = -1;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
    DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
}

} // namespace m568
