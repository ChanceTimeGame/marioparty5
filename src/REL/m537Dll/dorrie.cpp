#include "REL/m537Dll/dorrie.h"
#include "REL/m537Dll/water.h"
#include "REL/mgcpp/singleton.h"

namespace m537 {

/* lbl_1_data_210..22C: the object names (a .data table, relocated; defined first: its strings open .data) */
static const char* s_objName[2] = { "stage_a", "spling_in" };

/* lbl_1_rodata_80: the per-player Dorrie model */
static const u32 s_model[4] = { 0x5F0003, 0x5F0004, 0x5F0005, 0x5F0006 };

CDorrie::CDorrie(int no)
    : CModel((unsigned int)s_model[no]), m_angle(0.0, 360.0, 0.0), m_angleFrom(0.0), m_angleTo(0.0),
      m_turnTime(0.0), m_turnDuration(0.0), m_motionReq(0), m_frame(0), m_shadowDelay(170),
      m_sub(new CModel(0x5F0007u))
{
    setLayer(5);
    LoadMotion();
    m_sub->setLayer(1);
    m_sub->setAttr(0x40000002);
}

CDorrie::~CDorrie() {}

/* the shadow map is switched on 170 frames in (a dead-looking bool local: retail) */
void CDorrie::update()
{
    bool sh = false;
    if (m_shadowDelay > 0 && --m_shadowDelay == 0) {
        sh = true;
    }
    if (sh) {
        setShadowMap();
    }
    UpdateTurn();
    UpdateMotion();
    UpdateRipple();
    m_frame++;
}

/* a double square taking a const reference (camera proc_ease's ease: the stfd / lfd / lfd round trip) */
static inline double Square(const double& x)
{
    return x * x;
}

/* the cosine ease from m_angleFrom to m_angleTo over m_turnDuration seconds; nothing (not even setRot) once there */
void CDorrie::UpdateTurn()
{
    if (m_angle == m_angleTo) {
        return;
    }
    if (m_turnDuration <= 0.0 || m_turnTime >= m_turnDuration) {
        m_angle.set(m_angleTo);
    } else {
        double t = Square(1.0 - cos(M_PI * (m_turnTime / m_turnDuration))) / 4.0;
        m_angle.lerp(m_angleFrom, m_angleTo, t);
        m_turnTime += 1.0 / 60.0;
    }
    Vec rot = { 0.0f, 0.0f, 0.0f };
    rot.y = m_angle.get();
    setRot(&rot);
    m_sub->setRot(&rot);
}

/* every 300 frames (frame 0 included) a ripple at the "spling_in" object */
void CDorrie::UpdateRipple()
{
    if (m_frame % 300 == 0) {
        Vec p;
        GetObjPos(OBJ_SPLING, &p);
        CSingleton<CWater>::GetInstance()->AddForce(&p, -0.2f);
    }
}

Mtx* CDorrie::GetObjMtx(int which, Mtx m)
{
    s16 id = this->id();
    switch (which) {
    default:
    case OBJ_STAGE:
        id = this->id();
        break;
    case OBJ_SPLING:
        id = m_sub->id();
        break;
    }
    Hu3DModelObjMtxGet(id, (char*)s_objName[which], m);
    return (Mtx*)m;
}

Vec* CDorrie::GetObjPos(int which, Vec* out)
{
    Vec zero = { 0.0f, 0.0f, 0.0f };
    s16 id = this->id();
    switch (which) {
    default:
    case OBJ_STAGE:
        id = this->id();
        break;
    case OBJ_SPLING:
        id = m_sub->id();
        break;
    }
    Mtx m;
    Hu3DModelObjMtxGet(id, (char*)s_objName[which], m);
    PSMTXMultVec(m, &zero, out);
    return out;
}

void CDorrie::SetAngle(double to, double time)
{
    m_angleFrom = m_angle.get();
    m_angleTo = to;
    m_turnTime = 0.0;
    m_turnDuration = time;
}

void CDorrie::RequestMotion()
{
    m_motionReq = 1;
}

/* the requested motion plays once the turn is finished */
void CDorrie::UpdateMotion()
{
    if (m_motionReq && !(m_angle != m_angleTo)) {
        PlayMotion(0, false);
        Hu3DMotionOverlaySpeedSet(id(), 0.4f);
        setLayer(2);
        m_sub->resetAttr(0x40000002);
        Hu3DMotionSpeedSet(m_sub->id(), 0.4f);
        m_motionReq = 0;
    }
}

/* line padding (LoadMotion): the assert below must stay on retail's dorrie.cpp:179 */
























void CDorrie::LoadMotion()
{
    m_motion_id.clear();
    AddMotion(0x5F0009);
    AddMotion(0x5F0008);
    assert(m_motion_id.size() == NUMBER_OF_MOTION);
    int id = this->id();
    s16& m = m_motion_id.at(1);
    Hu3DMotionSet(id, m);
    setAttr(0x40000001);
}

void CDorrie::AddMotion(u32 data)
{
    int id = this->id();
    void* p = HuDataSelHeapReadNum(data, HU_MEMNUM_OVL, HEAP_MODEL);
    s16 m = Hu3DJointMotion(id, p);
    m_motion_id.push_back(m);
}

void CDorrie::PlayMotion(int idx, bool loop)
{
    int id = this->id();
    s16& r = m_motion_id.at(idx);
    int m = (s16)r;
    Hu3DMotionOverlaySet(id, m);
    resetAttr(0x40000E00);
    if (loop) {
        setAttr(0x40000200);
    }
}

/* ---- CAngleD (the double CAngle) ---- */

void CAngleD::set(double v)
{
    m_value = wrap(v);
}

bool CAngleD::operator==(double v)
{
    return m_value == wrap(v);
}

bool CAngleD::operator!=(double v)
{
    return m_value != wrap(v);
}

void CAngleD::lerp(double a, double b, double t)
{
    m_value = wrap(a + diff(a, b) * t);
}

double CAngleD::wrap(double v)
{
    if (v < m_min) {
        return m_max - fmod(m_min - v, m_range);
    }
    if (v >= m_max) {
        return m_min + fmod(v - m_max, m_range);
    }
    return v;
}

double CAngleD::get()
{
    return m_value;
}

template <class T> static inline T Min(T a, T b)
{
    return a < b ? a : b;
}

template <class T> static inline T Max(T a, T b)
{
    return a > b ? a : b;
}

CAngleD::CAngleD(double a, double b, double v)
{
    m_min = Min(a, b);
    m_max = Max(a, b);
    m_range = m_max - m_min;
    m_value = wrap(v);
}

double CAngleD::diff(double a, double b)
{
    double d = wrap(b) - wrap(a);
    double ad = d < 0.0 ? -d : d;
    double r;
    if (ad < m_range / 2.0) {
        r = d;
    } else {
        r = (m_range - ad) * (d < 0.0 ? 1 : -1);
    }
    return r;
}

} // namespace m537

template <> m537::CWater* CSingleton<m537::CWater>::ms_pointer = 0;
