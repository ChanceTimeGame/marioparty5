#include "REL/m517Dll/config.h"
#include "REL/m517Dll/player.h"
#include "REL/m517Dll/util.h"
#include "REL/m517Dll/stage.h"
#include "REL/m517Dll/misc.h"
#include "REL/m517Dll/audio.h"
#include "REL/m517Dll/effect.h"
extern "C" {
#include "game/frand.h"
}

namespace m517 {

/* the m501/m532 setter with DOUBLE components: retail stores each component with `frsp; stfs` (Roll 1950..1978,
 * CollideStage 1AA4..1AB8) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* ClampVelXZ's clamp: the value is read once, the limits at each use */
static inline float Clamp(float v, float lo, float hi)
{
    if (v < lo) {
        return lo;
    } else if (v > hi) {
        return hi;
    } else {
        return v;
    }
}

void CEffect::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CEffect* self = (CEffect*)particle->work;
    self->UpdateParticles(m);
}

CEffect::CEffect()
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0011, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    HU3DMODELID id = Hu3DParticleCreate(m_anim, NUM_PARTICLE);
    m_particle = (HU3DPARTICLE*)Hu3DData[(int)id].hookData;
    m_particle->work = this;
    Hu3DParticleHookSet((int)id, Hook);
    Hu3DParticleColSet((int)id, 0xF0, 0xE0, 0x80);
    Hu3DParticleTPLvlSet((int)id, 0.0f);
    Hu3DParticleBlendModeSet((int)id, 0);
    Hu3DModelLayerSet((int)id, 2);
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_model = (int)id;
    m_emit.x = 0.0f;
    m_emit.y = 0.0f;
    m_emit.z = 0.0f;
    if (m_particle->count == 0) {
        int i;
        HU3DPARTICLEDATA* p;
        for (i = 0, p = m_particle->data; i < m_particle->maxCnt; i++, p++) {
            p->time = 3;
        }
        m_particle->dataCnt = 0;
    }
}

CEffect::~CEffect()
{
    m_particle->work = 0;
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CEffect::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CEffect::InitParticle(HU3DPARTICLEDATA* p)
{
    p->time = 0;
    p->parManId = (frand() & 15) + 4;
    p->pos.x = m_emit.x + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->pos.z = m_emit.z + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
    p->scale = 100.0f * (0.5f + (1.0f / 65536) * (frand() & 0xFFFF));
    p->pos.y = m_emit.y + 0.5f * p->scale;
    p->zRot = (float)(M_PI / 180.0) * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    p->color.a = 0;
}

/* time 0: spawn (InitParticle, inlined); 1: fade in by 8 to 0xF0 (then 0xFF); 2: fade out by the particle's speed
 * to <= 20; 3: idle until Emit restarts it. Every live particle spins 1 degree a frame. */
void CEffect::UpdateParticles(Mtx m)
{
    HU3DMODEL* model = &Hu3DData[m_model]; /* unused (retail keeps the store) */
    HU3DPARTICLE* particle = m_particle;
    int i;
    HU3DPARTICLEDATA* p;
    for (i = 0, p = particle->data; i < particle->maxCnt; i++, p++) {
        if (p->time > 2) {
            continue;
        }
        switch (p->time) {
        case 0:
            InitParticle(p);
            p->time++;
        case 1:
            p->color.a += 8;
            if (p->color.a < 0xF0) {
                break;
            }
            p->color.a = 0xFF;
            p->time++;
        case 2:
            p->color.a -= p->parManId;
            if (p->color.a > 20) {
                break;
            }
            p->color.a = 0;
            p->time++;
        }
        p->zRot += (float)(M_PI / 180.0);
    }
}

/* restarts the next particle of the ring every 10 units of XZ travel (ring cursor = particle->dataCnt) */
void CEffect::Emit(const Vec* pos)
{
    Vec d;
    Vec v = *pos;
    v.y = 0.0f;
    PSVECSubtract(&v, &m_emit, &d);
    float dist = VecMag(&d);
    if (dist < 10.0f) {
        return;
    }
    m_emit = v;
    HU3DPARTICLEDATA* p = &m_particle->data[m_particle->dataCnt];
    if (p->time > 2) {
        p->time = 0;
    }
    m_particle->dataCnt++;
    if (m_particle->dataCnt >= NUM_PARTICLE) {
        m_particle->dataCnt = 0;
    }
}

void CEffect::SetVec(const Vec* v)
{
    m_vec = *v;
}

/* pushes `pos` and the sphere apart to 130 + s->r: the sphere moves by (1 - w) of the overlap, pos by w */
bool PushOut(Vec* pos, CSphere* s, float w)
{
    float lim = 130.0f + s->radius();
    Vec d;
    Vec t;
    PSVECSubtract(&s->pos, pos, &d);
    float dist = VecMag(&d);
    if (dist >= lim) {
        return false;
    }
    float wa = w;
    float wb = 1.0f - w;
    PSVECScale(&d, &d, (lim - dist) / dist);
    /* the scaled temporary reaches VecAdd as a comma expression (no float parameter copy when inlined twice deep:
     * HitPlayer 1DB0 `fneg f1,f28`) */
    VecAdd((PSVECScale(&d, &t, -wa), &t), pos, pos);
    VecAdd((PSVECScale(&d, &t, wb), &t), &s->pos, &s->pos);
    return true;
}

CBall::CBall(int idx) : m_idx(idx), m_wall(false), m_model(0x4B0004u), m_effect()
{
    insertBack(ASet<CBall>::instance());
    m_sphere.r = 100.0f;
    Hu3DModelShadowSet(m_model.id());
    Hu3DModelShadowDispOn(m_model.id());
    Hu3DModelLayerSet(m_model.id(), 1);
    Hu3DModelCameraSet(m_model.id(), 1);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_unk94.x = 0.0f;
    m_unk94.y = 0.0f;
    m_unk94.z = 0.0f;
    m_unk88.x = 0.0f;
    m_unk88.y = 0.0f;
    m_unk88.z = 0.0f;
    m_force.x = 0.0f;
    m_force.y = 0.0f;
    m_force.z = 0.0f;
    m_delta.x = 0.0f;
    m_delta.y = 0.0f;
    m_delta.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_rot.w = 1.0f;
    PSMTXIdentity(m_mtx);
    m_effect.reset(new CEffect);
    m_se = HuAudFXPlay(0x6F2);
    HuAudFXVolSet(m_se, 0);
    setState(0);
}

CBall::~CBall()
{
    HuAudFXStop(m_se);
}

void CBall::SetPos(const Vec* pos)
{
    CStage* stage = CSingleton<CStage>::GetInstance(); /* dead (retail) */
    *GetPos() = *pos;
    m_sphere.pos.y += 100.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_unk94.x = 0.0f;
    m_unk94.y = 0.0f;
    m_unk94.z = 0.0f;
    m_force.x = 0.0f;
    m_force.y = 0.0f;
    m_force.z = 0.0f;
}

float CBall::GetSpeedRatio()
{
    Vec* v = &m_vel;
    Vec t = *v;
    float mag = PSVECMag(&t);
    return mag / (700.0 / 60.0);
}

void CBall::GetQuat(Quaternion* q)
{
    *q = m_rot;
}

void CBall::SetForce(const Vec* f)
{
    m_force = *f;
}

void CBall::Stop()
{
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
}

void CBall::Update()
{
    if (m_state) {
        (this->*m_state)();
    }
    Move();
    PSVECSubtract(&m_sphere.pos, &m_prevPos, &m_delta);
    m_prevPos = m_sphere.pos;
    m_effect->Emit(&m_sphere.pos);
    m_force.x = 0.0f;
    m_force.y = 0.0f;
    m_force.z = 0.0f;
    SetSePan(m_se, m_sphere.pos);
    float ratio = VecMag(&m_delta) / (700.0 / 60.0);
    if (ratio < 0.0f) {
        ratio = 0.0f;
    }
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    s16 vol = 127.0f * ratio;
    HuAudFXVolSet(m_se, vol);
}

void CBall::ClampVelXZ(float lim)
{
    m_vel.x = Clamp(m_vel.x, -lim, lim);
    m_vel.z = Clamp(m_vel.z, -lim, lim);
}

/* vel += 0.3 force, XZ clamped to 700/60; vel.y is a downward speed (pos.y -= the mean of the old and new);
 * wall and floor (CollideStage), damping 0.99, rolling (Roll) */
void CBall::Move()
{
    Vec f;
    VecAdd(&VecScale(&m_force, &f, 0.3f), &m_vel, &m_vel);
    ClampVelXZ(11.666667f);
    Vec d = m_vel;
    m_vel.y += 0.27240694444444447;
    d.y = -(0.5f * (d.y + m_vel.y));
    Vec old = m_sphere.pos;
    PSVECAdd(&d, &m_sphere.pos, &m_sphere.pos);
    CollideStage();
    PSVECScale(&m_vel, &m_vel, 0.99f);
    Roll(&old, &m_sphere.pos);
    m_model.setPos(&m_sphere.pos);
}

/* the shortest-arc rotation taking the contact vector (0, -r, 0) to (from - to) + (0, -r, 0), applied to m_rot */
void CBall::Roll(const Vec* from, const Vec* to)
{
    float r = GetRadius();
    Vec a;
    Vec b;
    Quaternion q;
    SetVec(&a, from->x - to->x, -r, from->z - to->z);
    SetVec(&b, 0.0f, -r, 0.0f);
    QuatRotArc(&q, &b, &a);
    PSQUATMultiply(&q, &m_rot, &m_rot);
    PSQUATNormalize(&m_rot, &m_rot);
    PSMTXQuat(m_mtx, &m_rot);
    Mtx* mtx = m_model.getMatrix();
    PSMTXCopy(m_mtx, *mtx);
}

/* the arena wall (radius 600 - 100) with the bounce SE 0x6F4, and the floor at y = 100 */
void CBall::CollideStage()
{
    CStage* stage = CSingleton<CStage>::GetInstance(); /* dead (retail) */
    float radius = 600.0f;
    Vec p;
    Vec t;
    SetVec(&p, m_sphere.pos.x, 0.0f, m_sphere.pos.z);
    float dist = VecMag(&p);
    float lim = radius - 100.0f;
    if (dist > lim) {
        float over = lim - dist;
        PSVECScale(&p, &t, over / dist);
        PSVECAdd(&t, &m_sphere.pos, &m_sphere.pos);
        PSVECAdd(&t, &m_vel, &m_vel);
        if (!m_wall) {
            if (VecMag(&m_vel) > 100.0 / 60.0) {
                PlaySe(0x6F4, m_sphere.pos);
                m_wall = true;
            }
        }
    } else {
        m_wall = false;
    }
    if (m_sphere.pos.y < 100.0f) {
        m_sphere.pos.y = 100.0f;
        m_vel.y = 0.0f;
    }
}

void CBall::HitBall(CBall* a, CBall* b)
{
    CSphere* sb = &b->m_sphere;
    CSphere* sa = &a->m_sphere;
    if (!HitPushSphere(sa, sb, 0.5f, 1.0f)) {
        return;
    }
}

/* gamemaster's ForEachCross<CBall, CPlayer> callback: a team player still in play is pushed out of the ball (the
 * ball does not move) and hit */
void CBall::HitPlayer(CBall* ball, CPlayer* p)
{
    if (!p->m_isSolo && !p->m_out) {
        Vec* pos = &ball->m_sphere.pos;
        CSphere* s = &p->m_sphere;
        if (PushOut(pos, s, 0.0f)) {
            p->Hit(ball);
        }
    }
}

} // namespace m517

template <> ASet<m517::CBall>* ASet<m517::CBall>::sm_ptr = 0;
template <> m517::CPlayerCarrier* CSingleton<m517::CPlayerCarrier>::ms_pointer = 0;
template <> m517::CPaperTex* CSingleton<m517::CPaperTex>::ms_pointer = 0;
template <> m517::CChoroMan* CSingleton<m517::CChoroMan>::ms_pointer = 0;
template <> m517::CStage* CSingleton<m517::CStage>::ms_pointer = 0;
