/* zako.cpp -- the crowd of eight runners (scenery). Fork Z: every function written (27/27 masked 0 but __sinit).
 * The ctor's assert must stay on line 55 ("zako.cpp" is in .data). Functions in reference order (-inline auto
 * inlines only earlier bodies: setMotion into the states). */
#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in zako.o's .bss/__sinit */
#include "REL/mgcpp/random.h"
#include "REL/m512Dll/zako.h"
#include "REL/m512Dll/player.h" /* DegToAngle/AngleSub/SetVec */

namespace m512 {

TLinkList<CZako> CZako::list;

CZakoMan::CZakoMan() : m_model(0x460009U)
{
    HU3DMODELID id = m_model.id();
    Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_PMOTION);
    createMotion(0x46000D); /* 0 walk */
    createMotion(0x46000E); /* 1 dash */
    createMotion(0x46000F); /* 2 brake */
    /* line padding: the assert below is retail's zako.cpp:55 */
































    assert(m_mot_id.size() == NUMBEROF_PMOTION);
    /* the eight start points on the centre line (radius 500), rodata_3E8 copied to the stack */
    Vec pos[8] = {
        { -300.0f, 49.0f, -500.0f }, { 0.0f, 49.0f, -500.0f }, { 300.0f, 49.0f, -500.0f }, { -800.0f, 49.0f, 0.0f },
        { 800.0f, 49.0f, 0.0f }, { -300.0f, 49.0f, 500.0f }, { 0.0f, 49.0f, 500.0f }, { 300.0f, 49.0f, 500.0f },
    };
    for (int i = 0; i < 8; i++) {
        new CZako(&pos[i]);
    }
}

s16 CZakoMan::createMotion(int dataNum)
{
    s16 mot = Hu3DJointMotion(m_model.id(), HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_mot_id.push_back(mot);
    return mot;
}

CZakoMan::~CZakoMan()
{
    CZako::DeleteAll();
}

void CZakoMan::on_update()
{
    CZako::UpdateAll();
}

void CZakoMan::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        break;
    }
}

float CZako::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

float CZako::SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

CZako::CZako(Vec* pos) : m_unk30(0), m_model(0x460009U)
{
    insertBack(&list);
    m_hit = false;
    m_yaw = 0.0f;
    m_motion = -1;
    m_pushTimer = 0;
    m_speed = 0.0f;
    m_pos = *pos;
    HU3DMODELID id = m_model.id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelScaleSet(id, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    m_yaw = GetTrackAngle();
    ClampTrack();
    m_unk40.x = m_unk40.y = m_unk40.z = 0.0f;
    m_unk4C = 0.0f;
    m_unk54 = 0;
    m_dashTimer = 0;
    m_steer = 0.0f;
    m_steerTarget = 70.0f * CRandom::randomMantissa() - 40.0f;
    m_radius = 750.0f;
    m_model.setPos(&m_pos);
    setState(&CZako::stateStart);
}

void CZako::DeleteAll()
{
    while (!list.isEmpty()) {
        CZako* z = list.last();
        delete z;
    }
}

void CZako::UpdateAll()
{
    TLinkList<CZako>::exec(&list, Update);
    CZako* first = list.begin();
    if (first != list.end()) {
        first->unlink();
        first->insertBack(&list);
    }
}

void CZako::Update(CZako* z)
{
    (z->*(z->m_state))();
    z->m_hit = false;
    z->CheckPush();
    z->m_hit |= z->ClampTrack();
    z->updateModel();
}

void CZako::updateModel()
{
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model.setRot(&rot);
    m_model.setPos(&m_pos);
}

/* push apart from every other zako closer than 120: both move 1.05 x half the overlap */
void CZako::CheckPush()
{
    Vec pos = m_pos; /* retail dead copy (F214), never read */
    if (m_pushTimer > 0) {
        m_pushTimer--;
    }
    CZako* o = list.begin();
    CLinkNode* end = list.end();
    for (; o != end; o = o->next()) {
        if (this == o) {
            continue;
        }
        Vec opos = o->m_pos; /* retail dead copy (F26C), never read */
        Vec d;
        PSVECSubtract(&o->m_pos, &m_pos, &d);
        float len = PSVECMag(&d);
        if (len >= 120.0f) {
            continue;
        }
        float w = 0.5f;
        float wo = 1.0f - w;
        PSVECScale(&d, &d, (120.0f - len) / len);
        Vec a, b;
        PSVECScale(&d, &a, 1.05f * -w);
        PSVECScale(&d, &b, 1.05f * wo);
        PSVECAdd(&a, &m_pos, &m_pos);
        PSVECAdd(&b, &o->m_pos, &o->m_pos);
        o->m_pushTimer = (wo >= 0.5f) ? 5 : 0; /* retail: always 5 */
        m_hit |= ClampTrack();
        o->m_hit |= o->ClampTrack();
    }
}

/* retail's setMotion reaches the motion id through an inline taking the vector: the element reference is kept
 * in a saved register, and in the three inlined copies (walk/dash/brake) the vector address gets its own
 * register. `s16& r = m_mot_id.at(motion)` (fork S, heiho) matches the out-of-line copy F3F0 only; this form
 * matches F3F0 and its inlined copies. Name ours. */
inline s16& MotionAt(std::vector<s16>& ids, int i)
{
    return ids.at(i);
}

/* out-of-line copy unreferenced: inlined into stateWalk/stateDash/stateBrake */
void CZako::setMotion(int motion, bool once)
{
    CZakoMan* man = CSingleton<CZakoMan>::GetInstance();
    HU3DMODELID id = m_model.id();
    s16 mot = MotionAt(man->m_mot_id, motion);
    if (m_motion != motion) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
    }
}

void CZako::stateStart()
{
    setState(&CZako::stateWalk);
}

void CZako::stateWalk()
{
    m_yaw = GetTrackAngle();
    if (m_steerTarget > m_steer) {
        m_steer += 2.0;
        if (m_steerTarget < m_steer) {
            m_steer = m_steerTarget;
        }
    }
    if (m_steerTarget < m_steer) {
        m_steer -= 2.0;
        if (m_steerTarget > m_steer) {
            m_steer = m_steerTarget;
        }
    }
    m_yaw += m_steer;
    if (m_yaw > 180.0f) {
        m_yaw -= 360.0f;
    }
    if (m_yaw < -180.0f) {
        m_yaw += 360.0f;
    }
    if ((m_speed += 1.0f / 60.0f) > 1.0f) {
        m_speed = 1.0f;
        if ((CRandom::irandom() & 0x7F) == 0) {
            setState(&CZako::stateDash);
            m_dashTimer = 0;
        }
    }
    move();
    Hu3DMotionSpeedSet(m_model.id(), m_speed);
    setMotion(0, false);
}

void CZako::stateDash()
{
    m_dashTimer++;
    if (m_dashTimer > 60.0f) {
        setState(&CZako::stateBrake);
    }
    m_speed = 3.0f;
    move();
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(1, true);
}

void CZako::stateBrake()
{
    bool stop = false;
    if ((m_speed -= 1.0f / 30.0f) < 0.0f) {
        m_speed = 0.0f;
        stop = true;
    }
    if (stop) {
        m_speed = 0.0f; /* retail stores the zero twice */
        setState(&CZako::stateWalk);
        m_steerTarget = 70.0f * CRandom::randomMantissa() - 10.0f;
    }
    move();
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(2, false);
}

inline double GetFps() { return 60.0; }

/* the guarded function-local static is retail's (bss AA8, guard AB0); the spelling of its initialiser is a
 * guess (m536 KillerSpeed). The result is ignored by all three callers. */
bool CZako::move()
{
    static double s_fps = GetFps();
    Mtx m;
    Vec dir;
    Vec v;
    dir.x = 0.0f;
    dir.y = 0.0f;
    dir.z = 1.5f * m_speed;
    PSMTXRotRad(m, 'y', 0.017453292f * m_yaw);
    PSMTXMultVec(m, &dir, &v);
    m_pos.x += 100.0 * (v.x / s_fps);
    m_pos.y += 100.0 * (v.y / s_fps);
    m_pos.z += 100.0 * (v.z / s_fps);
    if (m_speed <= 0.01f) {
        return false;
    }
    return true;
}

#ifdef __MWERKS__
/* retail inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases): m536 camera's form */
inline double MslSqrt(double x)
{
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0;
    } else if (x) {
        return *(float*)__float_nan;
    }
    return *(float*)__float_huge;
}
#else
/* host: libm sqrt (no __float_nan/__float_huge on the host; last-ulp differences only) */
inline double MslSqrt(double x) { return sqrt(x); }
#endif

bool CZako::ClampTrack()
{
    double dx = m_pos.x - -104.0f;
    double dz = m_pos.z - 550.0f;
    double d = MslSqrt(dx * dx + dz * dz);
    if (d < 150.0) {
        m_pos.x = -104.0 + 150.0 * (dx / d);
        m_pos.z = 550.0 + 150.0 * (dz / d);
        if (m_pos.z > 550.0f) {
            m_pos.z = 550.0f;
        }
        if (m_pos.z < 380.0f) {
            m_pos.z = 380.0f;
        }
        return true;
    }
    if (m_pos.x > -300.0 && m_pos.x < 300.0) {
        if (m_pos.z > 0.0f) {
            if (m_pos.z > 550.0f) {
                m_pos.z = 550.0f;
                m_radius = 550.0f;
                return true;
            }
            if (m_pos.z < 380.0f) {
                m_pos.z = 380.0f;
                m_radius = 380.0f;
                return false;
            }
        } else {
            if (m_pos.z < -550.0f) {
                m_pos.z = -550.0f;
                m_radius = 550.0f;
                return true;
            }
            if (m_pos.z > -380.0f) {
                m_pos.z = -380.0f;
                m_radius = 380.0f;
                return false;
            }
        }
        float z = m_pos.z;
        m_radius = (z < 0.0f) ? -z : z;
        return false;
    }
    double cx = 300.0;
    if (m_pos.x < 0.0f) {
        cx = -cx;
    }
    double cdx = m_pos.x - cx;
    double cdz = m_pos.z;
    double r = MslSqrt(cdx * cdx + cdz * cdz);
    m_radius = r;
    if (r < 380.0) {
        m_pos.x = cx + 380.0 * (cdx / r);
        m_pos.z = 380.0 * (cdz / r);
        m_radius = 380.0f;
        return false;
    }
    if (r > 550.0) {
        m_pos.x = cx + 550.0 * (cdx / r);
        m_pos.z = 550.0 * (cdz / r);
        m_radius = 550.0f;
        return true;
    }
    return false;
}

/* track tangent in degrees: +-90 on the straights, from atan2 about the curve centre on the curves */
float CZako::GetTrackAngle()
{
    if (m_pos.x > -300.0 && m_pos.x < 300.0) {
        if (m_pos.z > 0.0f) {
            return 90.0f;
        }
        return -90.0f;
    }
    float cx = 300.0f;
    if (m_pos.x < 0.0f) {
        cx = -cx;
    }
    float dx = m_pos.x - cx;
    float dz = m_pos.z;
    float a = 90.0 + 180.0 * (atan2(dx, dz) / 3.141592653589793);
    if (a > 180.0f) {
        a -= 360.0f;
    }
    return a;
}

} // namespace m512
