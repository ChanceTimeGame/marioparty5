#include "REL/m511Dll/config.h"
#include "REL/m511Dll/particle.h"
#include "REL/m511Dll/boatshadow.h"
#include "REL/m511Dll/player.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/frand.h"
}

namespace m511 {

/* the borrowed sparkle anim: CSingleton<CEffTex>::GetInstance() (assert singleton.h:39) through an accessor */
static inline ANIMDATA* GetStarGetAnim(CEffTex* tex)
{
    return tex->m_starGetAnim;
}

static inline float GetOwnerRotY(CPlayer* owner)
{
    return owner->m_rotY;
}

static inline void SetYawRot(Vec* rot, double y)
{
    rot->x = 0.0f;
    rot->y = y;
    rot->z = 0.0f;
}

static inline Vec GetOwnerPos(CPlayer* owner)
{
    return owner->m_pos;
}

void CStarGetEff::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CStarGetEff* self = (CStarGetEff*)particle->work;
    self->UpdateParticles(mtx);
}

CStarGetEff::CStarGetEff(CPlayer* owner) : m_owner(owner), m_time(0.0f), m_stop(false), m_frame(0), m_num(1)
{
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    HU3DMODELID id = Hu3DParticleCreate(GetStarGetAnim(tex), 8);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 1);
    Hu3DModelLayerSet((int)id, 6);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_pos = GetOwnerPos(m_owner);
    SetYawRot(&m_rot, GetOwnerRotY(m_owner));
    HU3DPARTICLEDATA* p;
    int i;
    for (p = m_particle->data, i = 0; i < m_particle->maxCnt; i++, p++) {
        InitParticle(p);
    }
    m_id = (int)id;
}

CStarGetEff::~CStarGetEff()
{
    Hu3DModelKill(m_id);
}

void CStarGetEff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* follow the owner; every 2nd frame one more particle is walked (up to 8); after 3 s no respawn */
void CStarGetEff::on_update()
{
    m_pos = GetOwnerPos(m_owner);
    SetYawRot(&m_rot, GetOwnerRotY(m_owner));
    if (m_stop == true) {
        return;
    }
    m_frame++;
    if ((m_frame & 1) == 0) {
        m_num++;
        if (m_num >= 8) {
            m_num = 8;
        }
    }
    m_time += 1.0 / 60.0;
    if (m_time > 3.0f) {
        m_stop = true;
    }
}

void CStarGetEff::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 7;
    p->pos.x = m_pos.x + 50.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f));
    p->pos.y = 100.0f + m_pos.y;
    p->pos.z = m_pos.z + 50.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f));
    p->scale = 100.0f * (0.2f + 0.1f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    p->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    u32 rgb = frand();
    p->color.r = rgb & 0xFF;
    p->color.g = (rgb >> 8) & 0xFF;
    p->color.b = (rgb >> 16) & 0xFF;
    p->color.a = 0;
}

void CStarGetEff::UpdateParticles(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[m_id]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    bool dead = true;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = particle->data; i < particle->maxCnt, i < m_num; i++, p++) {
        if (p->time > 1) {
            continue;
        }
        if (p->time == 0) {
            p->color.a += p->parManId;
            if (p->color.a > 230) {
                p->color.a = 255;
                p->time++;
            }
        } else {
            p->color.a -= p->parManId;
            if (p->color.a < 25) {
                if (m_stop == true) {
                    p->time++;
                } else {
                    InitParticle(p);
                }
            }
        }
        p->zRot += 0.08726646f;
        dead = false;
    }
    if (dead) {
        delete this;
    }
}

void CStarEff::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CStarEff* self = (CStarEff*)particle->work;
    self->UpdateParticles(mtx);
}

CStarEff::CStarEff(Vec* pos)
{
    m_unk20 = 0;
    m_active = 1;
    m_pos = *pos;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    CEffTex* tex = CSingleton<CEffTex>::GetInstance();
    HU3DMODELID id = Hu3DParticleCreate(GetStarGetAnim(tex), 40);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xFF, 0xFF, 0xFF);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 1);
    Hu3DModelLayerSet((int)id, 7);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    HU3DPARTICLEDATA* p;
    int i;
    for (p = m_particle->data, i = 0; i < m_particle->maxCnt; i++, p++) {
        InitParticle(p);
    }
    m_id = (int)id;
}

CStarEff::~CStarEff()
{
    Hu3DModelKill(m_id);
}

void CStarEff::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 7;
    p->pos.x = m_pos.x + 70.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f));
    p->pos.y = m_pos.y;
    p->pos.z = m_pos.z + 70.0f * ((1.0f / 32768) * ((CRandom::irandom() & 0xFFFF) - 32768.0f));
    p->scale = 100.0f * (0.2f + 0.3f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    p->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (CRandom::irandom() & 0xFFFF)));
    u32 rgb = frand();
    p->vel.y = 0.0f;
    p->color.r = rgb & 0xFF;
    p->color.g = (rgb >> 8) & 0xFF;
    p->color.b = (rgb >> 16) & 0xFF;
    p->color.a = 0;
}

/* time 0: fade in by 4 to 255; 1: fade out by the speed, below 25 respawn (InitParticle inlined); spin 1 degree
 * and fall (g * 0.3, the average velocity added) */
void CStarEff::UpdateParticles(Mtx mtx)
{
    HU3DMODEL* model = &Hu3DData[m_id]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
        if (p->time == 0xFF) {
            continue;
        }
        if (p->time == 0) {
            p->color.a += 4;
            if (p->color.a > 250) {
                p->color.a = 0xFF;
                p->time++;
            }
        } else {
            p->color.a -= p->parManId;
            if (p->color.a < 25) {
                InitParticle(p);
            }
        }
        p->zRot += 0.017453292f;
        float vy = p->vel.y;
        p->vel.y += -(9.80665 * 100 / 60 / 60) * 0.3f; /* rodata_238 BFB4EBBD19399252 */
        vy = 0.5f * (vy + p->vel.y);
        p->pos.y += vy;
    }
}

void CStarEff::SetPos(Vec* pos, Vec* rot)
{
    m_pos = *pos;
    m_rot = *rot;
}

} // namespace m511
