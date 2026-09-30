#include "REL/m517Dll/config.h"
#include "REL/m517Dll/dustcloud.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/frand.h"
}

namespace m517 {

void CDustCloud::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CDustCloud* self = (CDustCloud*)particle->work;
    self->Update(m);
}

CDustCloud::CDustCloud(const Vec* pos, GXColor col, int count)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0011, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, count);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, col.r, col.g, col.b);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 5);
    Hu3DModelPosSet((int)id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_model = (int)id;
}

CDustCloud::~CDustCloud()
{
    m_particle->work = 0;
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CDustCloud::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CDustCloud::Update(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_model]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    HU3DPARTICLEDATA* d;
    int i;
    if (particle->count == 0) {
        d = particle->data;
        for (i = 0; i < particle->maxCnt; i++, d++) {
            d->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
            d->vel.y = d->accel.y = 0.27240694444444447 * (10.0f + 30.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
            d->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
            d->scale = 200.0f;
            d->pos.x = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
            d->pos.y = 0.0f;
            d->pos.z = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
            d->color.a = 0;
            d->time = 0;
            d->parManId = (CRandom::irandom() & 15) + 15;
            d->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
        }
    }
    bool done = true;
    d = particle->data;
    for (i = 0; i < particle->maxCnt; i++, d++) {
        if (d->time == 2) {
            continue;
        }
        if (d->time == 0) {
            d->color.a += d->parManId;
            if (d->color.a >= 220) {
                d->color.a = 220;
                d->time++;
            }
        } else if (d->color.a > 32) {
            d->color.a -= (u8)(0.5f * d->parManId);
        } else {
            d->time++;
        }
        d->scale += 200.0 / 60.0;
        float vy = d->vel.y;
        d->vel.y += -0.27240694444444447;
        float dy = 0.5f * (vy + d->vel.y);
        d->pos.x += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.x));
        d->pos.y += dy;
        d->pos.z += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.z));
        done = false;
    }
    if (done) {
        delete this;
    }
}

void CDustPuff::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CDustPuff* self = (CDustPuff*)particle->work;
    self->Update(m);
}

CDustPuff::CDustPuff(const Vec* pos)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0011, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, 6);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xF0, 0xE0, 0x80);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 5);
    Hu3DModelPosSet((int)id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_model = (int)id;
    InitParticles(m_particle);
}

CDustPuff::~CDustPuff()
{
    m_particle->work = 0;
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CDustPuff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* as CDustCloud's first call, slower (g (10 + 15 rnd)) and smaller (scale 50); `this` unused */
void CDustPuff::InitParticles(HU3DPARTICLE* particle)
{
    HU3DPARTICLEDATA* d = particle->data;
    for (int i = 0; i < particle->maxCnt; i++, d++) {
        d->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
        d->vel.y = d->accel.y = 0.27240694444444447 * (10.0f + 15.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
        d->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
        d->scale = 50.0f;
        d->pos.x = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
        d->pos.y = 0.0f;
        d->pos.z = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
        d->color.a = 0;
        d->time = 0;
        d->parManId = (CRandom::irandom() & 15) + 15;
        d->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    }
}

void CDustPuff::Update(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_model]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    bool done = true;
    HU3DPARTICLEDATA* d = particle->data;
    for (int i = 0; i < particle->maxCnt; i++, d++) {
        if (d->time == 2) {
            continue;
        }
        if (d->time == 0) {
            d->color.a += d->parManId;
            if (d->color.a >= 220) {
                d->color.a = 220;
                d->time++;
            }
        } else if (d->color.a > 32) {
            d->color.a -= (u8)(0.5f * d->parManId);
        } else {
            d->time++;
        }
        d->scale += 200.0 / 60.0;
        float vy = d->vel.y;
        d->vel.y += -0.27240694444444447;
        float dy = 0.5f * (vy + d->vel.y);
        d->pos.x += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.x));
        d->pos.y += dy;
        d->pos.z += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.z));
        done = false;
    }
    if (done) {
        delete this;
    }
}

} // namespace m517
