#include "REL/m579Dll/puku2.h"
#include "REL/m579Dll/effect.h"
#include "REL/m579Dll/camera.h"
#include "REL/m579Dll/water.h"
#include "REL/m579Dll/zako.h"
#include "REL/m579Dll/fishline.h"
#ifndef __MWERKS__
#include <math.h> /* sqrt (procJump) */
#endif

namespace m579 {

TLinkList<CPuku> CPuku::s_list;

CPuku::CPuku(CModel& src, int kind) : m_motion(-1), m_unk18(0), m_frame(0), m_model(src), m_caught(false), m_kind(kind),
    m_above(false)
{
    insertBack(&s_list);
    Hu3DModelCameraSet(m_model.id(), 1);
    m_model.setScale(kind ? 1.5 : 1.0);
    m_model.setAttr(HU3D_ATTR_DISPOFF);
    m_model.setLayer(0);
    m_model.set_shadow();
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_prevPos.x = 0.0f;
    m_prevPos.y = 0.0f;
    m_prevPos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_model.setPos(&m_pos);
    setProc(&CPuku::procHide);
}

/* the first free Cheep Cheep of that kind in list order (0 if none); retail keeps a dead 2000.0f local */
CPuku* CPuku::Catch(CFishLine* line, int kind)
{
    CPuku* p = s_list.begin();
    CLinkNode* end = s_list.end();
    float dist = 2000.0f; /* retail: dead (stored to the stack, never read) */
    for (; p != end; p = p->next()) {
        if (!p->m_caught && kind == p->m_kind) {
            p->m_caught = true;
            p->m_line = line;
            p->setProc(&CPuku::procCaught);
            return p;
        }
    }
    return 0;
}

/* EXACT m512 zako EF9C / m536 killer E8D4 (the implicit ~CPuku inlines: ~CModel, ~CLinkNode) */
void CPuku::DeleteAll()
{
    while (!s_list.isEmpty()) {
        CPuku* p = s_list.last();
        delete p;
    }
}

/* EXACT m512 zako F070: update every fish, then rotate the list by one */
void CPuku::UpdateAll()
{
    TLinkList<CPuku>::exec(&s_list, Update);
    CPuku* first = s_list.begin();
    if (first != s_list.end()) {
        first->unlink();
        first->insertBack(&s_list);
    }
}

void CPuku::Update(CPuku* p)
{
    (p->*(p->m_proc))();
    p->updateModel();
    p->m_frame++;
    p->checkSurface();
}

/* a surface crossing (y = -150) since the last frame spawns a splash (result dropped: it lives on CSplash::s_list) */
void CPuku::checkSurface()
{
    if ((m_pos.y > -150.0 && m_prevPos.y <= -150.0) || (m_pos.y < -150.0 && m_prevPos.y >= -150.0)) {
        new CSplash(&m_pos, m_kind);
    }
    m_prevPos = m_pos;
}

/* surfacing SEs, rot / pos, layer by depth, fade underwater */
/* the depth fade's clamp: an inline returning the smaller (one more register copy than a plain ternary) */
inline double MinD(double a, double b)
{
    return a < b ? a : b;
}

void CPuku::updateModel()
{
    if (!m_above && m_pos.y > -150.0) {
        m_above = true;
        CCameraObj::PlaySe(&m_pos, m_kind ? 0x95F : 0x956);
    }
    if (m_above == true && m_pos.y < -150.0) {
        m_above = false;
        CCameraObj::PlaySe(&m_pos, m_kind ? 0x95A : 0x959);
    }
    m_model.setRot(&m_rot);
    m_model.setPos(&m_pos);
    m_model.setLayer(m_pos.y < -150.0 ? 0 : 5);
    float tp = 1.0f;
    if (m_pos.y < -150.0) {
        double t = (-150.0 - m_pos.y) / 550.0;
        double c = MinD(t, 1.0);
        tp = 0.5 * (1.0 - c);
    }
    m_model.setTPLvl(tp);
}

/* m512 zako F3F0's shape: the motion id through an inline taking the manager's vector (the element reference in a
 * saved register) */
inline s16& MotionAt(std::vector<s16>& ids, int i)
{
    return ids.at(i);
}

/* out-of-line copy unreferenced: inlined into procCaught / procJump */
void CPuku::setMotion(int no, bool once)
{
    CZakoMan* man = CSingleton<CZakoMan>::GetInstance();
    HU3DMODELID id = m_model.id();
    s16 mot = MotionAt(man->m_mot_id, no);
    if (m_motion != no) {
        m_model.resetAttr(HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

/* hidden below the lake until a line claims it */
void CPuku::procHide()
{
    m_caught = false;
    m_model.setAttr(HU3D_ATTR_DISPOFF);
    m_pos.y = -500.0f;
    m_prevPos = m_pos;
}

/* on the line: a big one trails drops; shown, swimming motion */
void CPuku::procCaught()
{
    if (m_kind) {
        new CWaterDrop(&m_pos);
    }
    m_model.resetAttr(HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(0, false);
}

#ifdef __MWERKS__
/* retail procJump inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases) = m536 camera */
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
/* host: libm sqrt (no __float_nan / __float_huge on the host) */
inline double MslSqrt(double x)
{
    return sqrt(x);
}
#endif

inline float Mag(Vec& v)
{
    return PSVECMag(&v);
}

/* v /= |v| */
inline void Normalize(Vec& v)
{
    float mag = Mag(v);
    PSVECScale(&v, &v, 1.0f / mag);
}

void CPuku::procJump()
{
    Vec tgt[5] = { { 0.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 1000.0f }, { 1000.0f, 0.0f, 0.0f }, { -1000.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f } };
    int k = 0;
    if (m_pos.x > 0.0f) {
        float z = m_pos.z;
        if (m_pos.x > (z < 0.0f ? -z : z)) {
            k = 2;
        } else if (m_pos.z > 0.0f) {
            k = 1;
        }
    } else {
        float z = m_pos.z;
        if (-m_pos.x > (z < 0.0f ? -z : z)) {
            k = 3;
        } else if (m_pos.z > 0.0f) {
            k = 1;
        }
    }
    if (!m_escape) {
        k = 4;
    }
    Vec d = { 0.0f, 0.0f, 0.0f };
    d.x = m_pos.x;
    d.z = m_pos.z;
    PSVECSubtract(&tgt[k], &m_pos, &d);
    Normalize(d);
    float speed = 5.0f;
    PSVECScale(&d, &d, speed);
    PSVECSubtract(&d, &m_vel, &d);
    PSVECScale(&d, &d, 0.05f);
    d.y = -0.4086104f;
    PSVECAdd(&d, &m_vel, &m_vel);
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    float x = m_pos.x;
    float z = m_pos.z;
    float r = MslSqrt(x * x + z * z);
    if (r > 500.0 && r < 800.0) {
        float floorY = m_kind ? 70.0 : 20.0;
        if (m_pos.y < floorY) {
            m_pos.y = floorY;
            m_vel.y *= -0.5f;
            CCameraObj::PlaySe(&m_pos, m_kind ? 0x958 : 0x957);
        }
    }
    m_rot.x -= 0.05f * m_rot.x;
    m_rot.y += 3.0;
    if (m_rot.y > 180.0f) {
        m_rot.y -= 360.0f;
    }
    if (m_pos.y < -700.0) {
        setProc(&CPuku::procHide);
    }
    m_model.resetAttr(HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    if (m_vel.y > 0.0f) {
        setMotion(1, false);
    } else {
        setMotion(0, false);
    }
    if (m_kind) {
        new CWaterDrop(&m_pos);
    }
}

/* caught fish thrown outward from the lake centre at speed 5 (escape: it heads back to the centre in procJump) */
void CPuku::Launch(bool escape)
{
    m_escape = escape;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    setProc(&CPuku::procJump);
    Vec dir = { 0.0f, 0.0f, 0.0f };
    dir.x = m_pos.x;
    dir.z = m_pos.z;
    Normalize(dir);
    float speed = 5.0f;
    PSVECScale(&dir, &m_vel, speed);
}

} // namespace m579

template <> m579::CEffect* CSingleton<m579::CEffect>::ms_pointer = 0;
template <> m579::CCameraObj* CSingleton<m579::CCameraObj>::ms_pointer = 0;
template <> m579::CWater* CSingleton<m579::CWater>::ms_pointer = 0;
template <> m579::CJugem* CSingleton<m579::CJugem>::ms_pointer = 0;
template <> m579::CZakoMan* CSingleton<m579::CZakoMan>::ms_pointer = 0;
