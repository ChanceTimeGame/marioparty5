/* tube.cpp -- m568::CTube. Retail order: GetModelId, ctor, [~TLinkItem<CTube>], dtor, Reset, GetRot, AddSteer,
 * Brake, GetNormPos, Stop, update, stateSlide, stateBlown, SetTargetUp, ApplySteer, CollideGround, CollideNormal,
 * WallCheck, ApplyGravity, Damp, WallProbe, ApplyForce, GravityPart, ClampLateral, Integrate, UpdateMatrix,
 * LocalToWorld, CollideTubes, HitObstacle, TakeEvent, KnockOut, PlayVoice, StopVoice.
 * .data 6A0..774: GetModelId's assert strings + jumptable, the stateSlide PTMF, "sm_ptr != 0"/"a_set.h", the ctor's
 * jumptable (the inlined GetModelId), the singleton strings, the stateBlown PTMF. .rodata 488..540. No .bss.
 * F2: every body written from the asm; all masked 0 except the unreferenced SetTargetUp copy (see OUT.md).
 * The stage is reached through CStage::GetInstance() and its ICollision interface (retail calls Raycast /
 * GetNormal through the +0x10 subobject, no null check: the local Raycast / Normal inlines take ICollision&). */
#include "REL/m568Dll/tube.h"
#include "REL/m568Dll/stage.h"
#include "REL/m568Dll/octtree.h"
#include "REL/m568Dll/effect.h"
#include "REL/m568Dll/misc.h"

namespace m568 {

/* line padding: the assert below is retail's tube.cpp:53 */







u32 CTube::GetModelId(int cid)
{
    switch (cid) {
    case 0:
        return 0x7B0007;
    case 1:
        return 0x7B0008;
    case 2:
        return 0x7B0009;
    case 3:
        return 0x7B000A;
    case 4:
        return 0x7B000B;
    case 5:
        return 0x7B000C;
    case 6:
        return 0x7B000D;
    case 7:
        return 0x7B000E;
    case 8:
        return 0x7B000F;
    case 9:
    case 10:
    case 11:
    case 12:
        return 0x7B0010;
    default:
        assert(!"invalid cid");
        return 0;
    }
}

/* fn_1_12058: member order m_isSolo, m_out, m_event, m_model; GetModelId inlined with its own jumptable (data_718);
 * the mass literal tests the argument (30 / 2 through the int->float magic) */
CTube::CTube(int isTeam, int cid)
    : m_isSolo(isTeam == 0), m_out(false), m_event(0), m_model(m_isSolo ? 0x7B0006u : GetModelId(cid))
{
    insertBack(ASet<CTube>::instance());
    m_no = 0;
    m_voiceSe = -1;
    if (m_isSolo) {
        m_loopSe = HuAudFXPlay(0x90C);
    } else {
        m_loopSe = -1;
    }
    float r = m_isSolo ? 135.0 : 100.0;
    m_sphere.r = r;
    if (IsSolo()) {
        m_model.setAttr(HU3D_MOTATTR_LOOP);
    } else {
        m_model.setAttr(HU3D_MOTATTR_SHAPE_PAUSE);
        m_model.setAttr(HU3D_MOTATTR_PAUSE);
    }
    Hu3DModelShadowSet(m_model.id());
    Hu3DModelShadowDispOn(m_model.id());
    Hu3DModelLayerSet(m_model.id(), 0);
    Hu3DModelCameraSet(m_model.id(), 1);
    m_mass = isTeam == 0 ? 30 : 2;
    setState(&CTube::stateSlide);
}

CTube::~CTube() {}

/* local inline helpers (retail's copies / returns show up as the extra register moves CW -O0 leaves) */

static inline Vec* VecSet(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return v;
}

static inline const Vec* Normal(ICollision& c)
{
    return c.GetNormal();
}

static inline bool Raycast(ICollision& c, Vec* out, const Vec* from, const Vec* to)
{
    return c.Raycast(out, from, to);
}

static inline Vec* VecScale(const Vec* v, Vec* out, float s)
{
    PSVECScale(v, out, s);
    return out;
}

/* dst += a */
static inline void VecAdd(const Vec* a, Vec* dst)
{
    PSVECAdd(a, dst, dst);
}

static inline float VecMag(const Vec* v)
{
    return PSVECMag(v);
}

static inline void VecSub(const Vec* a, const Vec* b, Vec* out)
{
    PSVECSubtract(a, b, out);
}

static inline float VecDot(const Vec* a, const Vec* b)
{
    return PSVECDotProduct(a, b);
}

static inline float Lerp(float a, float b, double k)
{
    return a * (1.0 - k) + b * k;
}

void CTube::Reset(const Vec* pos)
{
    *GetPos() = *pos;
    m_prevPos = *pos;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_force.x = 0.0f;
    m_force.y = 0.0f;
    m_force.z = 0.0f;
    m_impulse.x = 0.0f;
    m_impulse.y = 0.0f;
    m_impulse.z = 0.0f;
    m_steer.x = 0.0f;
    m_steer.y = 0.0f;
    m_steer.z = 0.0f;
    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;
    m_targetUp.x = 0.0f;
    m_targetUp.y = 1.0f;
    m_targetUp.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_rot.w = 1.0f;
    UpdateMatrix();
}

void CTube::GetRot(Quaternion* q)
{
    *q = m_rot;
}

void CTube::AddSteer(const Vec* v)
{
    PSVECAdd(v, &m_steer, &m_steer);
}

/* fn_1_1268C: ray (0,20,0) -> (0,-20,0) in tube space; on a hit, force -= the velocity's in-plane part */
void CTube::Brake()
{
    Vec a;
    Vec b;
    Vec vt;
    Vec f;
    LocalToWorld(&a, VecSet(&a, 0.0f, 20.0f, 0.0f));
    LocalToWorld(&b, VecSet(&b, 0.0f, -20.0f, 0.0f));
    CStage* stage = CStage::GetInstance();
    if (Raycast(*stage, &b, &a, &b)) {
        const Vec* n = Normal(*stage);
        float d = VecDot(n, &m_vel);
        VecScale(n, &vt, -d);
        PSVECAdd(&m_vel, &vt, &vt);
        VecScale(&vt, &f, -1.0f);
        PSVECAdd(&f, &m_force, &m_force);
    }
}

void CTube::GetNormPos(Vec* out)
{
    CStage::GetNormPos(out, &m_sphere.pos, m_sphere.radius());
}

void CTube::Stop()
{
    m_model.setAttr(HU3D_MOTATTR_PAUSE);
    setState(0);
}

/* fn_1_1290C: Brake inlined; the up lerp is Lerp(a, b, (double)0.09f) (rodata 4B8 / 4C0) */
void CTube::update()
{
    if (CGameObject::GetUpdateMode() != 2) {
        if (m_isSolo) {
            Brake();
        } else {
            m_steer.z = -1.0f;
        }
    }
    if (m_state) {
        (this->*m_state)();
    }
    m_up.x = Lerp(m_up.x, m_targetUp.x, 0.09f);
    m_up.y = Lerp(m_up.y, m_targetUp.y, 0.09f);
    m_up.z = Lerp(m_up.z, m_targetUp.z, 0.09f);
    UpdateMatrix();
    m_prevPos = m_sphere.pos;
    m_steer.x = 0.0f;
    m_steer.y = 0.0f;
    m_steer.z = 0.0f;
    CStage::SetSePos(&m_sphere.pos, m_voiceSe);
    CStage::SetSePos(&m_sphere.pos, m_loopSe);
}

void CTube::stateSlide()
{
    ApplyGravity();
    ApplyForce();
    if (!m_out) {
        CStage::ClampToCourse(&m_sphere.pos, m_sphere.radius());
    }
    CollideGround();
    Integrate();
}

void CTube::stateBlown()
{
    ApplyGravity();
    ApplyForce();
    if (!m_out) {
        CStage::ClampToCourse(&m_sphere.pos, m_sphere.radius());
    }
    CollideGround();
    Integrate();
    Vec g;
    CStage::GetGravityDir(&g);
    float d = VecDot(&g, &m_vel);
    if (d > 0.0f) {
        setState(0);
    }
}

/* fn_1_12E80 (unreferenced; inlined 3x into CollideGround, where this spelling matches: n->x re-read each time).
 * The out-of-line copy keeps n->x in one register (3 insns shorter here); no spelling found that gives both. */
void CTube::SetTargetUp(const Vec* n)
{
    if ((n->x < 0.0f ? -n->x : n->x) > sin(M_PI / 30.0)) {
        return;
    }
    m_targetUp = *n;
}

void CTube::ApplySteer(const Vec* n)
{
    Mtx m;
    Vec up;
    Quaternion q;
    Vec f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    QuatRotArc(&q, &up, n);
    PSMTXQuat(m, &q);
    PSMTXMultVecSR(m, &m_steer, &f);
    PSVECScale(&f, &f, 10.0f);
    PSVECAdd(&f, &m_force, &m_force);
}

/* lbl_1_rodata_4D4: the landing SE by m_no */
static const int s_landSe[4] = { 0x903, 0x904, 0x905, 0x906 };

/* fn_1_12FD8: the sheet §3.4 and §7.11 (the airborne probe's overwritten local) */
void CTube::CollideGround()
{
    WallCheck();
    CStage* stage = CStage::GetInstance();
    Vec from = m_prevPos;
    from.y += 200.0f;
    if (!Raycast(*stage, &m_sphere.pos, &from, &m_sphere.pos)) {
        StopVoice();
        float r = m_sphere.radius();
        Vec b;
        Vec a;
        Vec h;
        /* retail (sic, sheet §7.11): the first result lands in b, which the second VecSet then overwrites, so
         * the probe runs from the untransformed local point (0, 0, r) to M.(0, 0, r) */
        LocalToWorld(&b, VecSet(&a, 0.0f, 100.0f, r));
        LocalToWorld(&a, VecSet(&b, 0.0f, 0.0f, r));
        if (!Raycast(*stage, &h, &b, &a)) {
            /* retail: on a miss the stage's previous (stale) hit normal is taken */
            Vec n = *Normal(*stage);
            SetTargetUp(&n);
        }
        return;
    }
    {
        Vec n = *Normal(*stage);
        float d = CollideNormal(&n, &m_vel);
        if (d < -8.0f) {
            new CEffectB(&m_sphere.pos);
            m_event = 2;
            HuAudFXPlay(s_landSe[m_no]);
            PlayVoice();
        }
        new CEffectA(&m_sphere.pos, 100.0f);
        SetTargetUp(&n);
        ApplySteer(&n);
        ApplyForce();
    }
}

float CTube::CollideNormal(const Vec* n, const Vec* v)
{
    Vec f;
    float d = VecDot(v, n);
    if (d < 0.0f) {
        VecAdd(VecScale(n, &f, m_mass * -d), &m_force);
    }
    return d;
}

void CTube::WallCheck()
{
    int n = 4;
    for (int i = 0; i < n; i++) {
        float r = 1.2f * m_sphere.radius();
        float a = 2.0 * M_PI * i / n;
        Vec p;
        VecSet(&p, r * sin(a), 200.0f, r * cos(a));
        WallProbe(&p);
    }
    ApplyForce();
}

void CTube::ApplyGravity()
{
    Vec g;
    CStage* stage = CStage::GetInstance();
    CStage::GetGravity(&g, m_mass);
    PSVECAdd(&g, &m_force, &m_force);
}

void CTube::Damp(float k)
{
    Vec f;
    VecAdd(VecScale(&m_vel, &f, -0.8f * m_mass * k), &m_force);
}

bool CTube::WallProbe(const Vec* local)
{
    Vec a;
    Vec b;
    Vec h;
    Vec d;
    Vec t;
    Vec dir;
    float y = local->y;
    LocalToWorld(&a, VecSet(&a, 0.0f, y, 0.0f));
    LocalToWorld(&b, local);
    CStage* stage = CStage::GetInstance();
    if (!Raycast(*stage, &h, &a, &b)) {
        return false;
    }
    PSVECSubtract(&h, &b, &d);
    PSVECAdd(&d, &m_sphere.pos, &m_sphere.pos);
    PSVECSubtract(&b, &a, &dir);
    PSVECNormalize(&dir, &dir);
    float s = VecDot(&dir, &m_vel);
    PSVECScale(&dir, &t, s);
    const Vec* n = Normal(*stage);
    CollideNormal(n, &t);
    return true;
}

void CTube::ApplyForce()
{
    Vec d;
    VecScale(&m_force, &d, 1.0f / m_mass);
    m_force.x = 0.0f;
    m_force.y = 0.0f;
    m_force.z = 0.0f;
    PSVECAdd(&d, &m_impulse, &m_impulse);
}

void CTube::GravityPart(Vec* out, const Vec* v)
{
    Vec g;
    CStage::GetGravityDir(&g);
    float d = VecDot(&g, v);
    PSVECScale(&g, out, d);
}

void CTube::ClampLateral(float max)
{
    Vec* v = &m_vel;
    Vec gp;
    Vec h;
    GravityPart(&gp, v);
    VecSub(v, &gp, &h);
    float m = VecMag(&h);
    if (!(m < max)) {
        PSVECNormalize(&h, &h);
        VecScale(&h, v, max);
        VecAdd(&gp, v);
    }
}

/* retail: the lateral clamp runs twice (the second is redundant) */
void CTube::Integrate()
{
    Vec old = m_vel;
    PSVECAdd(&m_impulse, &old, &m_vel);
    ClampLateral(25.0f);
    m_impulse.x = 0.0f;
    m_impulse.y = 0.0f;
    m_impulse.z = 0.0f;
    PSVECAdd(&m_vel, &old, &old);
    ClampLateral(25.0f);
    PSVECScale(&old, &old, 0.5f);
    PSVECAdd(&old, &m_sphere.pos, &m_sphere.pos);
}

void CTube::UpdateMatrix()
{
    Vec up;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    QuatRotArc(&m_rot, &up, &m_up);
    PSMTXQuat(m_mtx, &m_rot);
    PSMTXTransApply(m_mtx, m_mtx, m_sphere.pos.x, m_sphere.pos.y, m_sphere.pos.z);
    Mtx* m = m_model.getMatrix();
    PSMTXCopy(m_mtx, *m);
    (*m)[0][3] = 0.0f;
    (*m)[1][3] = 0.0f;
    (*m)[2][3] = 0.0f;
    m_model.setPos(&m_sphere.pos);
}

void CTube::LocalToWorld(Vec* dst, const Vec* src)
{
    PSMTXMultVec(m_mtx, src, dst);
}

void CTube::CollideTubes(CTube* a, CTube* b)
{
    Vec dir;
    Vec t;
    float m = a->m_mass + b->m_mass;
    float ratio = (m - a->m_mass) / m;
    if (HitPushSphere(&a->m_sphere, &b->m_sphere, ratio, 1.001f)) {
        if (a->m_isSolo || b->m_isSolo) {
            a->KnockOut(b);
            b->KnockOut(a);
        } else {
            PSVECSubtract(&b->m_sphere.pos, &a->m_sphere.pos, &dir);
            PSVECNormalize(&dir, &dir);
            float d = VecDot(&a->m_vel, &dir);
            if (d > 0.0f) {
                VecAdd(VecScale(&dir, &t, 0.8f * -d), &a->m_vel);
            }
            d = -VecDot(&b->m_vel, &dir);
            if (d > 0.0f) {
                VecAdd(VecScale(&dir, &t, 0.8f * d), &b->m_vel);
            }
        }
    }
}

void CTube::HitObstacle(CObstacle* o)
{
    Vec dir;
    if (!o->IsHit()) {
        CSphere* s = &m_sphere;
        CSphere* os = o->GetSphere();
        HitPushSphere(s, os, 1.0f, 1.0f);
        m_event = 8;
        if (IsSolo()) {
            PSVECSubtract(&s->pos, &os->pos, &dir);
            PSVECNormalize(&dir, &dir);
            float d = VecDot(&m_vel, &dir);
            VecAdd(VecScale(&dir, &dir, 0.2f * (-d * m_mass)), &m_force);
        }
    }
}

bool CTube::TakeEvent()
{
    bool r = m_event != 0;
    m_event = 0;
    return r;
}

/* lbl_1_rodata_518: the knock-out SE by m_no (the solo's slot 0 is never used) */
static const int s_knockSe[4] = { 0, 0x907, 0x908, 0x909 };

void CTube::KnockOut(CTube* by)
{
    Vec g;
    Vec side;
    Vec c;
    if (CGameObject::GetUpdateMode() == 2 && !(m_isSolo | m_out)) {
        m_model.resetAttr(HU3D_MOTATTR_SHAPE_PAUSE);
        m_model.resetAttr(HU3D_MOTATTR_PAUSE);
        m_out = true;
        m_event = 2;
        HuAudFXPlay(s_knockSe[m_no]);
        CStage::GetGravityDir(&g);
        m_vel.x = 0.0f;
        m_vel.y = 0.0f;
        m_vel.z = 0.0f;
        VecScale(&g, &m_force, -40.0f * m_mass);
        side.x = -1.0f;
        side.y = 0.0f;
        side.z = 0.0f;
        PSVECCrossProduct(&g, &side, &c);
        VecScale(&c, &c, -20.0f * m_mass);
        PSVECAdd(&c, &m_force, &m_force);
        setState(&CTube::stateBlown);
    }
}

/* lbl_1_rodata_52C: the voice SE by m_no */
static const int s_voiceSe[4] = { 0x8FF, 0x900, 0x901, 0x902 };

void CTube::PlayVoice()
{
    if (m_voiceSe == -1) {
        m_voiceSe = HuAudFXPlay(s_voiceSe[m_no]);
    }
}

void CTube::StopVoice()
{
    if (m_voiceSe != -1) {
        HuAudFXStop(m_voiceSe);
        m_voiceSe = -1;
    }
}

} // namespace m568
