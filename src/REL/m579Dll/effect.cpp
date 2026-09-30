#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in effect.o's .bss / __sinit */
#include "REL/mgcpp/random.h"
#include "REL/m579Dll/effect.h"
#include "REL/m579Dll/water.h"

namespace m579 {

ANIMDATA* CEffect::s_anim;
TLinkList<CSplash> CSplash::s_list;

CEffect::CEffect()
{
    s_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x850003, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(s_anim);
}

CEffect::~CEffect()
{
    CSplash::DeleteAll();
    HuSprAnimKill(s_anim);
}

void CEffect::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CEffect::on_update()
{
    CSplash::UpdateAll();
}

/* type 0: small (scale 20, HookSmall, ripple 200); else big (scale 30, HookBig, ripple 400). The ripple registers
 * itself (the `new` result is dropped) */
CSplash::CSplash(Vec* pos, int type)
{
    m_frame = 0;
    insertBack(&s_list);
    m_id = Hu3DParticleCreate(CEffect::s_anim, 32);
    Hu3DModelPosSetV(m_id, pos);
    Hu3DModelLayerSet(m_id, 5);
    if (type == 0) {
        Hu3DParticleScaleSet(m_id, 20.0f);
        Hu3DParticleHookSet(m_id, HookSmall);
    } else {
        Hu3DParticleScaleSet(m_id, 30.0f);
        Hu3DParticleHookSet(m_id, HookBig);
    }
    Hu3DParticleTPLvlSet(m_id, 0.0f);
    Hu3DParticleBlendModeSet(m_id, 0);
    new CRipple(pos, type == 0 ? 200 : 400);
}

CSplash::~CSplash()
{
    Hu3DModelKill(m_id);
}

void CSplash::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CSplash* e = s_list.last();
        delete e;
    }
}

void CSplash::UpdateAll()
{
    TLinkList<CSplash>::exec(&s_list, Update);
}

void CSplash::Update(CSplash* s)
{
    if (++s->m_frame > 64) {
        delete s;
    }
}

/* the small splash (fn_1_C0A0): seed 32 drops on a ring of radius 10 at height 10 on the first call, then gravity
 * (980.665 / 60 / 60 a frame), x0.9 drag, alpha -4 a frame. Retail also keeps a dead read of model->hookData. */
void CSplash::HookSmall(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int a;
    int count = 0;
    if (particle->count == 0) {
        void* hook = model->hookData; /* retail: dead (stored to the stack, never read) */
        float r = 10.0f;
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float a = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            float c = cos(a);
            float s = sin(a);
            data->pos.x = c * r;
            data->pos.y = 10.0f;
            data->pos.z = s * r;
            data->vel.x = 3.0f * c;
            data->vel.y = 980.665 / 60.0 / 60.0 * 40.0 * (0.5 * CRandom::randomMantissa() + 0.5);
            data->vel.z = 3.0f * s;
            data->color.r = 0xE0;
            data->color.g = 0xF0;
            data->color.b = 0xFF;
            data->color.a = 0xFF;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        data->vel.y = data->vel.y - 980.665 / 60.0 / 60.0;
        PSVECScale(&data->vel, &data->vel, 0.9f);
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        a = data->color.a;
        a -= 4;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
}

/* the big splash (fn_1_C2F0): radius 30, start height 15 (no dead hookData read here) */
void CSplash::HookBig(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    HU3DPARTICLEDATA* end = &particle->data[particle->maxCnt];
    int a;
    int count = 0;
    if (particle->count == 0) {
        float r = 30.0f;
        for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
            float a = M_PI * (360.0f * CRandom::randomMantissa() - 180.0f) / 180.0;
            float c = cos(a);
            float s = sin(a);
            data->pos.x = c * r;
            data->pos.y = 15.0f;
            data->pos.z = s * r;
            data->vel.x = 3.0f * c;
            data->vel.y = 980.665 / 60.0 / 60.0 * 40.0 * (0.5 * CRandom::randomMantissa() + 0.5);
            data->vel.z = 3.0f * s;
            data->color.r = 0xE0;
            data->color.g = 0xF0;
            data->color.b = 0xFF;
            data->color.a = 0xFF;
        }
    }
    for (HU3DPARTICLEDATA* data = particle->data; data != end; data++) {
        data->vel.y = data->vel.y - 980.665 / 60.0 / 60.0;
        PSVECScale(&data->vel, &data->vel, 0.9f);
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        a = data->color.a;
        a -= 4;
        if (a < 0) {
            a = 0;
            data->scale = 0.0f;
        }
        data->color.a = a;
        count++;
    }
    particle->emitCnt = count;
}

} // namespace m579
