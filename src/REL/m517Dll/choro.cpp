#include "REL/m517Dll/config.h"
#include "REL/m517Dll/player.h"
#include "REL/m517Dll/util.h"
#include "REL/m517Dll/stage.h"
#include "REL/m517Dll/audio.h"
#include "REL/m517Dll/misc.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/frand.h"
}

namespace m517 {

/* Vec setter with DOUBLE components (m513 / m539: retail `fmuls; frsp; stfs` in stateIntro) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}
/* component-wise copy (lfs/stfs) */
static inline Vec& SetVec(Vec* d, const Vec& s)
{
    d->x = s.x;
    d->y = s.y;
    d->z = s.z;
    return *d;
}

/* ---- CChoroEff ---- */

void CChoroEff::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx m)
{
    CChoroEff* self = (CChoroEff*)particle->work;
    self->Update(m);
}

CChoroEff::CChoroEff()
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
    Hu3DModelPosSet((int)id, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet((int)id, 0.0f, 0.0f, 0.0f);
    m_model = (int)id;
    m_done = true;
    Init(m_particle);
    Hu3DModelAttrSet((int)id, HU3D_ATTR_DISPOFF);
}

CChoroEff::~CChoroEff()
{
    m_particle->work = 0;
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

void CChoroEff::Start(Vec* pos)
{
    Hu3DModelPosSet(m_model, pos->x, pos->y, pos->z);
    Hu3DParticleTPLvlSet(m_model, 0.0f);
    m_done = false;
    Hu3DModelAttrReset(m_model, HU3D_ATTR_DISPOFF);
}

void CChoroEff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* every particle on a ring (360 * i / maxCnt degrees), a random rise speed, a small random xz offset, alpha 0,
 * fade speed 15..30, a random spin */
void CChoroEff::Init(HU3DPARTICLE* particle)
{
    HU3DPARTICLEDATA* d = particle->data;
    int i;
    for (i = 0; i < particle->maxCnt; i++, d++) {
        d->vel.x = sin(0.017453292f * (360.0f * i / particle->maxCnt));
        d->vel.y = d->accel.y = 0.27240694444444447 * (10.0f + 15.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
        d->vel.z = cos(0.017453292f * (360.0f * i / particle->maxCnt));
        d->scale = 100.0f;
        d->pos.x = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
        d->pos.y = 0.0f;
        d->pos.z = 100.0f * (0.01f * ((CRandom::irandom() & 63) - 31.0f));
        d->color.a = 0;
        d->time = 0;
        d->parManId = (CRandom::irandom() & 15) + 15;
        d->zRot = 0.017453292f * (360.0f * ((1.0f / 65536) * (frand() & 0xFFFF)));
    }
}

/* the hook: time 0 fades in by the particle's speed to 220, time 1 fades out by half of it down to 32, then the
 * particle is done (2); grow, rise and fall, drift outwards. When every particle is done the puff re-inits them all
 * (Init inlined) and hides itself until the next Start. */
void CChoroEff::Update(Mtx m)
{
    if (!m_done) {
        HU3DMODEL* model = &Hu3DData[m_model]; /* unused (retail keeps the store) */
        HU3DPARTICLE* particle = m_particle;
        bool done = true;
        HU3DPARTICLEDATA* d = particle->data;
        int i;
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
            d->scale += 3.3333333333333335;
            float vy = d->vel.y;
            d->vel.y += -0.27240694444444447;
            float dy = 0.5f * (vy + d->vel.y);
            d->pos.x += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.x));
            d->pos.y += dy;
            d->pos.z += (1.0 / 60.0) * (100.0f * (2.0f * d->vel.z));
            done = false;
        }
        m_done = done;
        if (m_done) {
            Init(particle);
            Hu3DModelAttrSet(m_model, HU3D_ATTR_DISPOFF);
        }
    }
}

/* ---- CChoro ---- */

/* rodata_3FC: the mole's three motions, read in place (the first is loaded twice) */
static const u32 s_motTbl[CChoro::NUM_MOT] = { 0x4B0008, 0x4B0008, 0x4B0009 };

CChoro::CChoro()
    : m_hole(0x4B0005), m_hole2(0x4B0006), m_mole(0x4B0007), m_active(false), m_alive(false), m_turn(false),
      m_turnYaw(0.0f), m_type(-1), m_time(0.0f), m_lookTime(0.0f), m_scale(1.0f), m_state(0), m_lookState(0),
      m_altLook(false)
{
    int i;
    m_sphere.pos.x = 0.0f;
    m_sphere.pos.y = 0.0f;
    m_sphere.pos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    insertBack(ASet<CChoro>::instance());
    m_sphere.r = 1800 * (1.0f / 60); /* 30.000002f (0x41F00001) */
    m_hole.setPos(&m_sphere.pos);
    m_hole2.setPos(&m_sphere.pos);
    Hu3DModelAttrSet(m_hole.id(), HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m_hole.id(), HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(m_hole2.id(), HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m_hole2.id(), HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(m_mole.id(), HU3D_ATTR_DISPOFF);
    HU3DMODELID id = m_mole.id();
    for (i = 0; i < NUM_MOT; i++) {
        m_mot[i] = Hu3DJointMotion(m_mole.id(), HuDataSelHeapReadNum(s_motTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DMotionSet(id, m_mot[0]);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(m_mole.id(), 1);
    Hu3DModelCameraSet(m_mole.id(), 1);
    Hu3DModelLayerSet(m_hole.id(), 1);
    Hu3DModelCameraSet(m_hole.id(), 1);
    Hu3DModelLayerSet(m_hole2.id(), 1);
    Hu3DModelCameraSet(m_hole2.id(), 1);
    m_mole.setPos(&m_sphere.pos);
    UnpauseSub();
    m_active = false;
    setProc(&CChoro::procNone);
    m_wait = 0.0f;
    m_eff.reset(new CChoroEff);
}

CChoro::~CChoro() {}

void CChoro::SetPos(Vec* pos)
{
    m_hole.setPos(pos);
    m_hole2.setPos(pos);
    SetVec(GetPos(), *pos);
    m_sphere.pos.y = -7200 * (1.0f / 60); /* -120.00001f (0xC2F00001) */
}

void CChoro::ShowHole()
{
    Hu3DMotionTimeSet(m_hole.id(), 0.0f);
    Hu3DModelAttrReset(m_hole.id(), HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(m_hole.id(), HU3D_MOTATTR_PAUSE);
}

void CChoro::UnpauseSub()
{
    Hu3DModelAttrReset(m_hole2.id(), HU3D_MOTATTR_PAUSE);
}

void CChoro::procNone() {}

void CChoro::procStop() {}

/* type -1: the intro demo (no SE, no look-around, no wait) */
void CChoro::Appear(int type, float delay)
{
    m_type = type;
    m_appearDelay = delay;
    m_active = true;
    m_time = 0.0f;
    m_lookTime = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_lookState = frand() & 1;
    m_wait = (type == -1) ? 0.0f : 2.0f * ((1.0f / 65536) * (frand() & 0xFFFF));
    m_state = 0;
    m_turn = false;
    m_turnYaw = 0.0f;
    m_scale = 1.0f;
    Hu3DModelScaleSet(m_hole.id(), 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrSet(m_hole2.id(), HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(m_hole2.id(), HU3D_MOTATTR_PAUSE);
    m_altLook = false;
    m_alive = true;
}

/* up (state > 2): sink with the pop motion reversed; else the hole starts shrinking */
void CChoro::Duck(bool turn, float yaw)
{
    if (m_state > 2) {
        Hu3DModelAttrSet(m_hole.id(), HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(m_hole2.id(), HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(m_hole2.id(), HU3D_MOTATTR_PAUSE);
        HU3DMODELID id = m_mole.id();
        Hu3DMotionShiftSet(id, m_mot[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
        Hu3DMotionSpeedSet(id, 2.0f);
    } else {
        m_scale = 1.0f;
    }
    m_turn = turn;
    m_turnYaw = yaw;
    m_active = false;
}

/* type 0: swing the yaw between +45 and -45, flipping every m_lookInterval; otherwise the alternative look motion
 * (0..10, then paused) and a bob around y -20 */
void CChoro::Look()
{
    if (m_type == -1) {
        return;
    }
    if (m_time < m_wait) {
        return;
    }
    if (m_type == 0) {
        switch (m_lookState) {
        case 0:
            m_rot.y += (45.0f - m_rot.y) / 6.0f;
            if (m_lookTime < m_lookInterval) {
                break;
            }
            m_lookInterval = (1.0f / 65536) * (frand() & 0xFFFF);
            m_lookTime = 0.0f;
            m_lookState++;
        case 1:
            m_rot.y += (-45.0f - m_rot.y) / 6.0f;
            if (m_lookTime < m_lookInterval) {
                break;
            }
            m_lookInterval = (1.0f / 65536) * (frand() & 0xFFFF);
            m_lookTime = 0.0f;
            m_lookState = 0;
            break;
        }
    } else {
        if (!m_altLook) {
            HU3DMODELID id = m_mole.id();
            Hu3DMotionShiftSet(id, m_mot[1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            Hu3DMotionStartEndSet(id, 0.0f, 10.0f);
            m_altLook = true;
        } else {
            HU3DMODELID id = m_mole.id();
            if (Hu3DMotionTimeGet(id) >= 10.0f) {
                Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
            }
        }
        float a = M_PI * (360.0f * m_lookTime * m_lookSpeed) / 180.0;
        m_sphere.pos.y = -20.0 + 10.0 * sin(a);
    }
    m_lookTime += 1.0 / 60.0;
}

/* from + t * the shortest (-180, 180] difference, wrapped to [0, 360) (= m531 player.cpp's) */
float LerpAngle(float from, float to, float t)
{
    float d = fmod(to - from, 360.0);

    if (d < 0.0f) {
        d += 360.0f;
    }
    if (d > 180.0f) {
        d -= 360.0f;
    }
    float r = fmod(from + t * d, 360.0);
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* active: 0 wait the appear delay, open the hole (SE 0x6F5 unless the demo); 1 hole motion ends; 2 wait; 3 pop out
 * (dust, SE 0x6F6); 4 rise to y -20, then 5 look around for m_upTime; 6 done. Inactive: a closed hole shrinks away
 * (states <= 2), an up mole sinks (turning toward m_turnYaw when ducking) and is hidden below y -180. */
void CChoro::Update()
{
    CheckImpact();
    if (m_active) {
        switch (m_state) {
        case 0: {
            m_time += 1.0 / 60.0;
            if (m_time < m_appearDelay) {
                break;
            }
            m_time = 0.0f;
            ShowHole();
            Vec pos = m_sphere.pos;
            pos.y = 0.0f;
            if (m_type != -1) {
                PlaySe(0x6F5, pos);
            }
            m_state++;
        }
        case 1:
            if (!Hu3DMotionEndCheck(m_hole.id())) {
                break;
            }
            m_time = 0.0f;
            m_state++;
        case 2:
            m_time += 1.0 / 60.0;
            if (m_time < m_wait) {
                break;
            }
            m_state++;
        case 3: {
            HU3DMODELID id = m_mole.id();
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
            Hu3DMotionShiftSet(id, m_mot[0], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(id, 1.0f);
            Hu3DModelAttrSet(m_hole.id(), HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(m_hole2.id(), 0.0f);
            Hu3DModelAttrReset(m_hole2.id(), HU3D_ATTR_DISPOFF);
            Vec pos = m_sphere.pos;
            pos.y = 0.0f;
            m_eff->Start(&pos);
            m_lookInterval = (1.0f / 65536) * (frand() & 0xFFFF);
            m_time = 0.0f;
            PlaySe(0x6F6, m_sphere.pos);
            m_state++;
        }
        case 4:
            m_time += 1.0 / 60.0;
            m_sphere.pos.y += (-20.0f - m_sphere.pos.y) / 6.0f;
            if (m_time < 0.5f) {
                break;
            }
            m_wait = 0.5f + 0.5f * ((1.0f / 65536) * (frand() & 0xFFFF));
            m_lookTime = 0.0f;
            m_lookSpeed = 2.0f * ((1.0f / 65536) * (frand() & 0xFFFF));
            m_upTime = 3.0f + 2.0f * ((1.0f / 65536) * (frand() & 0xFFFF));
            m_time = 0.0f;
            {
                HU3DMODELID id = m_mole.id();
                Hu3DMotionShiftSet(id, m_mot[2], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
            }
            m_state++;
        case 5: {
            m_time += 1.0 / 60.0;
            Look();
            if (m_time < m_upTime) {
                break;
            }
            HU3DMODELID id = m_mole.id();
            Hu3DMotionShiftSet(id, m_mot[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
            Hu3DMotionSpeedSet(id, 2.0f);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            UnpauseSub();
            m_time = 0.0f;
            m_state++;
        }
        case 6:
            m_active = false;
            break;
        }
    } else if (m_state <= 2) {
        if (m_alive == true) {
            m_scale += -m_scale / 24.0f;
            if (m_scale < 0.2f) {
                HU3DMODELID id = m_mole.id();
                Hu3DMotionShiftSet(id, m_mot[0], 0.0f, 2.0f, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(id, 2.0f);
                Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(id, HU3D_MOTATTR_REV);
                m_state = 0;
                m_alive = false;
                Hu3DModelAttrSet(m_hole.id(), HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(m_hole.id(), 1.0f, 1.0f, 1.0f);
                m_scale = 1.0f;
            } else {
                Hu3DModelScaleSet(m_hole.id(), m_scale, m_scale, m_scale);
            }
        }
    } else {
        m_sphere.pos.y += (-200.0f - m_sphere.pos.y) / 48.0f;
        if (m_turn) {
            m_rot.y = LerpAngle(m_rot.y, m_turnYaw, 0.5f);
        } else {
            m_rot.y += -m_rot.y / 12.0f;
        }
        if (m_alive == true && m_sphere.pos.y < -180.0f) {
            HU3DMODELID id = m_mole.id();
            Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_REV);
            m_state = 0;
            m_alive = false;
        }
    }
    m_mole.setPos(&m_sphere.pos);
    m_mole.setRot(&m_rot);
    if (m_proc) {
        (this->*m_proc)();
    }
}

/* gamemaster ForEachCross<CChoro, CPlayer>: an active mole touching a team player stuns it */
void CChoro::HitPlayer(CChoro* c, CPlayer* p)
{
    if (!p->m_isSolo && c->IsActive() != false) {
        Vec d;
        VecSub(c->GetPos(), p->GetPos(), &d);
        float lim = 2.0f * c->m_sphere.radius();
        if (VecMag(&d) < lim) {
            p->Stun(c);
        }
    }
}

/* the stage's impact point by value */
static inline Vec ImpactOf(CStage* stage)
{
    return stage->m_impact;
}

/* d = a - b, |d| */
static inline float Distance(Vec a, Vec* b, Vec* d)
{
    PSVECSubtract(&a, b, d);
    return PSVECMag(d);
}

/* the ball's impact point (CStage::m_impact) within 200 of an active mole: it ducks, turning to face it */
void CChoro::CheckImpact()
{
    if (m_active) {
        CStage* stage = CSingleton<CStage>::GetInstance();
        Vec d;
        if (Distance(ImpactOf(stage), &m_sphere.pos, &d) > 200.0f) {
            return;
        }
        Duck(true, 180.0 * (atan2(d.x, d.z) / M_PI));
    }
}

/* ---- CChoroMan ---- */


CChoroMan::CChoroMan()
{
    int i;
    m_timer = 0.0f;
    m_level = 0;
    for (i = 0; i < NUM_CHORO; i++) {
        SetVec(&m_spot[i], 0.0f, 0.0f, 0.0f);
    }
    setState(&CChoroMan::stateNone);
}

CChoroMan::~CChoroMan() {}

void CChoroMan::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        setState(&CChoroMan::stateIntro);
        m_execFlags &= ~(1 << mode);
        break;
    case 1:
        setState(&CChoroMan::stateDuckIntro);
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        setState(&CChoroMan::stateMain);
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
        setState(&CChoroMan::stateNone);
        DuckAll();
        m_execFlags &= ~(1 << mode);
        break;
    case 4:
        m_execFlags &= ~(1 << mode);
        break;
    }
}

void CChoroMan::on_update()
{
    if (m_state) {
        (this->*m_state)();
    }
}

/* the guarded statics' initial value: non-constant (retail stores 0 behind each guard byte) */
static inline int StaticInit()
{
    return 0;
}

/* frame 72 (once): the first three moles pop up at x = -150 / 0 / 150 (Appear(-1, 0) and SetPos inlined) */
void CChoroMan::stateIntro()
{
    static int s_frame = StaticInit();
    static int s_done = StaticInit();
    m_timer += 1.0 / 60.0;
    if (72.0f == s_frame && !s_done) {
        ASet<CChoro>* set = ASet<CChoro>::instance();
        CChoro* p = set->begin();
        for (int i = -1; i < 2; i++) {
            Vec pos;
            SetVec(&pos, 150.0f * i, 0.0f, 0.0f);
            p->Appear(-1, 0.0f);
            p->SetPos(&pos);
            p = p->next();
        }
        s_done = 1;
    }
    s_frame++;
}

/* mode 1 (every frame): the three intro moles duck */
void CChoroMan::stateDuckIntro()
{
    ASet<CChoro>* set = ASet<CChoro>::instance();
    CChoro* p = set->begin();
    for (int i = 0; i < 3; i++) {
        p->Duck(false, 0.0f);
        p = p->next();
    }
}

/* every 5 s: one more mole per wave (cap 12), then a wave */
void CChoroMan::stateMain()
{
    m_timer += 1.0 / 60.0;
    if (m_timer > 5.0f) {
        m_level++;
        if (m_level > NUM_CHORO) {
            m_level = NUM_CHORO;
        }
        Spawn();
        m_timer = 0.0f;
    }
}

void CChoroMan::stateNone() {}

/* up to m_level inactive moles appear at free spots (Appear(0, 0..3 s) and SetPos inlined) */
void CChoroMan::Spawn()
{
    ASet<CChoro>* set = ASet<CChoro>::instance();
    CChoro* begin = set->begin();
    CLinkNode* end = set->end();
    int n = 0;
    int i = 0;
    for (CChoro* c = begin; c != end && n < m_level; c = c->next(), i++) {
        if (!c->IsActive()) {
            Vec pos;
            bool found = FindSpot(begin, end, &pos);
            if (found) {
                m_spot[i] = pos;
                c->Appear(0, (float)(CRandom::irandom() & 3));
                c->SetPos(&pos);
                n++;
            }
        }
    }
}

/* five tries at a random spot in the 800 x 800 square, rejected within 200 of an active mole's spot */
bool CChoroMan::FindSpot(CChoro* begin, CLinkNode* end, Vec* out)
{
    CStage* stage = CSingleton<CStage>::GetInstance(); /* unused (retail) */
    float range = 400.0f;
    for (int n = 0; n < 5; n++) {
        Vec p;
        p.x = range * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
        p.y = 0.0f;
        p.z = range * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
        bool ok = true;
        int i = 0;
        for (CChoro* c = begin; c != end; c = c->next(), i++) {
            if (c->IsActive()) {
                Vec d;
                PSVECSubtract(&m_spot[i], &p, &d);
                float dist = PSVECMag(&d);
                if (dist < 200.0f) {
                    ok = false;
                }
            }
        }
        if (ok == true) {
            *out = p;
            return true;
        }
    }
    return false;
}

/* mode 3: every mole ducks */
void CChoroMan::DuckAll()
{
    ASet<CChoro>* set = ASet<CChoro>::instance();
    CChoro* p = set->begin();
    CLinkNode* e = set->end();
    for (; p != e; p = p->next()) {
        p->Duck(false, 0.0f);
    }
}

} // namespace m517
