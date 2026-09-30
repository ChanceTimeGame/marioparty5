#include "REL/m568Dll/input.h"
#include "REL/m568Dll/stage.h"
#include "REL/m568Dll/tube.h"
#include "REL/m568Dll/octtree.h"
#include "REL/mgcpp/random.h"

namespace m568 {

void CInput::update(CTube* tube)
{
    m_data.b = false;
    m_data.a = false;
    m_data.stickX = 0.0f;
    get(&m_data, tube);
}

CInputPad::CInputPad(int idx)
{
    m_idx = idx;
    m_padNo = GwPlayerConf[idx].padNo;
}

CInput::~CInput() {}

void CInputPad::get(Data* data, CTube* tube)
{
    data->stickX = (1.0f / 56.0f) * (s8)HuPadStkX[m_padNo];
    u32 btn = HuPadBtn[m_padNo];
    data->a = (btn & PAD_BUTTON_A) != 0;
    data->b = (btn & PAD_BUTTON_B) != 0;
}

CInputComTeam::CInputComTeam() {}

/* x * x; by reference: the argument expression is read twice (s_escapeRange: two loads, a stack temporary) */
template <class T>
static inline T Sq(const T& x)
{
    return x * x;
}

/* the solo's velocity: read and dropped by CInputComTeam::get (retail) */
static inline const Vec* TubeVel(CTube* t)
{
    return &t->m_vel;
}

/* seconds -> frames */
static inline float Frames(float s)
{
    return 60.0f * s;
}

/* a frame countdown: true on the frame it reaches 0 */
static inline bool Tick(int& n)
{
    return n > 0 && --n == 0;
}

static inline float Dist2(const Vec* a, const Vec* b)
{
    return PSVECSquareDistance(a, b);
}

bool CInputComTeam::FindObstacle(Vec* out, const Vec* pos)
{
    ASet<CObstacle>* set = ASet<CObstacle>::instance();
    CLinkNode* end = set->end();
    for (CObstacle* o = set->begin(); o != end; o = o->next()) {
        if (!o->IsHit()) {
            *out = o->GetSphere()->pos;
            float dz = pos->z - out->z;
            if (dz < 500.0f && dz > -200.0f) {
                float dx = pos->x - out->x;
                if ((dx < 0.0f ? -dx : dx) < 200.0f) {
                    return true;
                }
            }
        }
    }
    return false;
}

CTube* CInputComTeam::FindSoloTube()
{
    ASet<CTube>* set = ASet<CTube>::instance();
    CLinkNode* end = set->end();
    for (CTube* t = set->begin(); t != end; t = t->next()) {
        if (t->IsSolo()) {
            return t;
        }
    }
    return 0;
}

u32 CInputComTeam::SlopeMask(const Vec* v)
{
    u32 mask = 0;
    if (v->z < -0.5f) {
        mask |= 1;
    }
    if (v->z > 0.5f) {
        mask |= 2;
    }
    if (v->x < -0.5f) {
        mask |= 4;
    }
    if (v->x > 0.5f) {
        mask |= 8;
    }
    return mask;
}

int CInputComTeam::Octant(float x, float z)
{
    double a = atan2(x, -z);
    if (a < 0.0) {
        a += 2.0 * M_PI;
    }
    a += M_PI / 8.0;
    int oct = 8.0 * a / (2.0 * M_PI);
    oct &= 7;
    return oct;
}

/* lbl_1_rodata_C8: the stick / button bits of the eight octants (0 = -z: A; 2 = +x: stick +1; 4 = +z: B;
 * 6 = -x: stick -1) */
static const u8 s_dirBits[8] = { 1, 9, 8, 10, 2, 6, 4, 5 };

bool CInputComTeam::OctantHits(int mask, int oct)
{
    oct &= 7;
    return (s_dirBits[oct] & mask) != 0;
}

/* the opposite octant; if blocked, o - i then o + i for i = 0..2 (i = 0 tests the same octant twice); none free:
 * the last one tried, o + 2 (retail, blocked) */
int CInputComTeam::EscapeDir(u32 mask, float x, float z)
{
    int oct = Octant(x, z);
    int k = oct + 4;
    if (OctantHits(mask, k)) {
        for (int i = 0; i < 3; i++) {
            k = oct + 4 - i;
            if (!OctantHits(mask, k)) {
                break;
            }
            k = oct + 4 + i;
            if (!OctantHits(mask, k)) {
                break;
            }
        }
    }
    return s_dirBits[k & 7];
}

void CInputComTeam::DirToData(const Vec* v, Data* d)
{
    if (v->z < 0.0f) {
        d->a = true;
    } else {
        d->b = true;
    }
    d->stickX = v->x < 0.0f ? -1 : 1;
}

/* lbl_1_data_264: the solo distance the team COM flees at (a non-const global: read twice, mullw) */
int s_escapeRange = 800;

void CInputComTeam::get(Data* data, CTube* tube)
{
    const Vec* pos = &tube->GetSphere()->pos;
    if (avoidObstacle(data, tube)) {
        return;
    }
    CTube* solo = FindSoloTube();
    if (!solo) {
        return;
    }
    Vec slope;
    CStage::GetNormPos(&slope, pos, tube->m_sphere.radius());
    const Vec* spos = &solo->GetSphere()->pos;
    float dz = spos->z - pos->z;
    float dx = spos->x - pos->x;
    if (Sq(dz) + Sq(dx) < Sq(s_escapeRange)) {
        const Vec* svel = TubeVel(solo); /* unused (retail) */
        int dir = EscapeDir(SlopeMask(&slope), dx, dz);
        if (dir & 1) {
            data->a = true;
        }
        if (dir & 2) {
            data->b = true;
        }
        if (dir & 4) {
            data->stickX = -1.0f;
        }
        if (dir & 8) {
            data->stickX = 1.0f;
        }
        if (dir != 0) {
            return;
        }
    }
    keepAway(data, tube, solo);
}

bool CInputComTeam::avoidObstacle(Data* data, CTube* tube)
{
    const Vec* pos = &tube->GetSphere()->pos;
    Vec obst;
    if (!FindObstacle(&obst, pos)) {
        return false;
    }
    if (obst.x < -400.0f) {
        data->stickX = 1.0f;
        return true;
    }
    if (obst.x > 400.0f) {
        data->stickX = -1.0f;
        return true;
    }
    if (obst.x < pos->x) {
        data->stickX = 1.0f;
    } else {
        data->stickX = -1.0f;
    }
    return true;
}

void CInputComTeam::keepAway(Data* data, CTube* tube, CTube* solo)
{
    const Vec* pos = &tube->GetSphere()->pos;
    Vec slope;
    CStage::GetNormPos(&slope, pos, tube->m_sphere.radius());
    const Vec* spos = &solo->GetSphere()->pos;
    float dx = spos->x - pos->x;
    float dz = spos->z - pos->z;
    float range = 450.0f + 100.0f * Level();
    float gx = pos->x - spos->x;
    if ((gx < 0.0f ? -gx : gx) < range) {
        float c;
        float g = pos->x - spos->x;
        if (g < -1.0f) {
            c = -1.0f;
        } else if (g > 1.0f) {
            c = 1.0f;
        } else {
            c = g;
        }
        data->stickX = c;
    }
    if (slope.z > -0.5f && slope.z < 0.5f) {
        if (dz > 0.0f) {
            data->a = true;
        } else {
            data->b = true;
        }
    } else {
        float tz = spos->z - pos->z;
        float adz = tz < 0.0f ? -tz : tz;
        if (adz < 200.0f) {
            if (slope.z < 0.0f) {
                data->b = true;
            } else {
                data->a = true;
            }
        }
    }
    if (slope.x > -0.5f && slope.x < 0.5f) {
        data->stickX = dx > 0.0f ? -1 : 1;
    } else {
        float tx = spos->x - pos->x;
        float adx = tx < 0.0f ? -tx : tx;
        if (adx < 200.0f) {
            data->stickX = slope.x > 0.0f ? -1 : 1;
        }
    }
}

/* fn_1_7500: dead code (no caller, no inlined copy); `this` unused, w unused, a always set (retail) */
void CInputComTeam::SteerAround(Data* data, CTube* tube, CTube* other)
{
    const Vec* opos = &other->GetSphere()->pos;
    const Vec* pos = &tube->GetSphere()->pos;
    Vec v;
    PSVECSubtract(pos, opos, &v);
    v.y = 0.0f;
    const Vec* vel = &other->m_vel;
    Vec w = *vel;
    w.y = 0.0f;
    Vec up;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    data->a = true;
    Vec c;
    PSVECCrossProduct(&v, &up, &c);
    if (c.z < 0.0f) {
        data->a = true;
    } else {
        data->b = true;
    }
    data->stickX = c.x < 0.0f ? -1 : 1;
}

CInputComSolo::CInputComSolo()
{
    m_retarget = 0;
    m_switch = 0;
    m_target = 0;
    resetTimers();
}

void CInputComSolo::get(Data* data, CTube* tube)
{
    const Vec* pos = &tube->GetSphere()->pos;
    CTube* t = selectTarget(pos);
    if (t) {
        const Vec* tpos = &t->GetSphere()->pos;
        Vec slope;
        CStage::GetNormPos(&slope, pos, tube->m_sphere.radius());
        float dx = tpos->x - pos->x;
        float c;
        if (dx < -1.0f) {
            c = -1.0f;
        } else if (dx > 1.0f) {
            c = 1.0f;
        } else {
            c = dx;
        }
        data->stickX = c;
        float dz = tpos->z - pos->z;
        if (slope.z > -0.8 && slope.z < 0.8) {
            if (dz < 0.0f) {
                data->a = true;
            } else {
                data->b = true;
            }
        }
    }
}

void CInputComSolo::resetTimers()
{
    int retarget = 30.0f + Frames(Level() * CRandom::frandom(4.0f, 10.0f));
    m_retarget = retarget;
    int sw = Frames((1.0f - Level()) * CRandom::frandom(2.0f, 4.0f));
    m_switch = sw;
}

CTube* CInputComSolo::selectTarget(const Vec* pos)
{
    if (m_target == 0 || (m_target != 0 && m_target->IsOut())) {
        return m_target = nearest(pos);
    }
    if (Tick(m_retarget)) {
        resetTimers();
    }
    if (Tick(m_switch)) {
        m_target = nearest(pos);
        return m_target;
    }
    if (m_switch > 0) {
        ASet<CTube>* set = ASet<CTube>::instance();
        CLinkNode* end = set->end();
        CTube* first = set->begin();
        int k = (++m_counter >> 8) & 3;
        for (CTube* t = first; t != end; t = t->next()) {
            if (--k < 0 && !t->IsSolo() && !t->IsOut()) {
                return t;
            }
        }
    }
    return m_target;
}

CTube* CInputComSolo::nearest(const Vec* pos)
{
    ASet<CTube>* set = ASet<CTube>::instance();
    CLinkNode* end = set->end();
    CTube* t = set->begin();
    CTube* best = 0;
    float bestDist = -1.0f;
    for (; t != end; t = t->next()) {
        if (!t->IsSolo() && !t->IsOut()) {
            float d = Dist2(&t->GetSphere()->pos, pos);
            if (bestDist > d || bestDist < 0.0f) {
                bestDist = d;
                best = t;
            }
        }
    }
    return best;
}

} // namespace m568

template <> m568::CStage* CSingleton<m568::CStage>::ms_pointer = 0;
template <> ASet<m568::CObstacle>* ASet<m568::CObstacle>::sm_ptr = 0;
template <> ASet<m568::CTube>* ASet<m568::CTube>::sm_ptr = 0;
