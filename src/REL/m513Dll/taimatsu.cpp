#include "REL/m513Dll/taimatsu.h"
#include "REL/m513Dll/powerind.h"
extern "C" {
#include "game/frand.h"
}

namespace m513 {

void CTaimatsu::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CTaimatsu* self = (CTaimatsu*)particle->work;
    self->UpdateParticles(m);
}

CTaimatsu::CTaimatsu(Vec* pos)
{
    m_time = 0.0f;
    m_frame = 0;
    m_count = 1;
    int id = Hu3DParticleCreate(CSingleton<CPowerInd>::GetInstance()->GetFireAnim(), 16);
    m_particle = (HU3DPARTICLE*)Hu3DData[(HU3DMODELID)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet(id, Hook);
    Hu3DParticleColSet(id, 0xE0, 0x60, 0x30);
    Hu3DParticleBlendModeSet(id, 1);
    Hu3DModelLayerSet(id, 5);
    Hu3DModelPosSet(id, pos->x, pos->y, pos->z);
    Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
    m_id = id;
    HU3DPARTICLEDATA* p = m_particle->data;
    for (int i = 0; i < m_particle->maxCnt; i++, p++) {
        p->time = 0;
    }
}

CTaimatsu::~CTaimatsu()
{
    m_particle->work = 0;
    Hu3DModelKill(m_id);
}

void CTaimatsu::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CTaimatsu::on_update()
{
    m_time += 1.0 / 60.0;
    if (m_count < 16) {
        m_frame++;
        if ((m_frame & 3) == 0) {
            m_count++;
        }
    }
}

/* fn_1_7078 (unreferenced): a new flame particle at the torch */
void CTaimatsu::InitParticle(HU3DPARTICLEDATA* p)
{
    p->vel.x = 0.0f;
    p->vel.y = 0.0f;
    p->vel.z = 0.0f;
    p->scale = 50.0f;
    p->pos.x = 20.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->pos.y = 0.5f * p->scale;
    p->pos.z = 20.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->color.r = 0xE0;
    p->color.g = 0x60;
    p->color.b = 0x30;
    p->color.a = 0;
    p->time = 0;
    p->parManId = 0.5f * (7.0f + 15.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
}

/* fn_1_72AC: time is the state (0 spawn, 1 fade in by parManId per frame, 2 fade out, back to 0); every live
 * particle shrinks, rises (vel.y accelerates to a cap), pulls in to the torch axis and darkens. */
void CTaimatsu::UpdateParticles(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_id];
    HU3DPARTICLE* particle = m_particle;
    HU3DPARTICLEDATA* p = particle->data;
    for (int i = 0; i < m_count; i++, p++) {
        if (p->time > 2) {
            continue;
        }
        switch (p->time) {
        case 0:
            InitParticle(p);
            p->time++;
        case 1:
            p->color.a += p->parManId;
            if (p->color.a < 0xE6) {
                break;
            }
            p->color.a = 0xFF;
            p->time++;
        case 2:
            p->color.a -= p->parManId;
            if (p->color.a <= 15) {
                p->color.a = 0;
                p->time = 0;
            }
            break;
        }
        p->scale -= 0.16666666666666666;
        if (p->scale < 0.0f) {
            p->scale = 0.0f;
        }
        float vy = p->vel.y;
        p->vel.y += 0.027240694850362426;
        if (p->vel.y > 0.5448138888888889) {
            p->vel.y = 0.5448138888888889;
        }
        vy = 0.5f * (vy + p->vel.y);
        p->pos.y += vy;
        p->pos.x *= 0.95f;
        p->pos.z *= 0.95f;
        p->color.r *= 0.999f;
        p->color.g *= 0.999f;
        p->color.b *= 0.999f;
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt * sizeof(HU3DPARTICLEDATA));
}

} // namespace m513
