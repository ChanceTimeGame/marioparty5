/* camera.cpp -- m522::CCameraObj (camera.h). Retail order (sheet §4.3): ctor, [~CSingleton<CCameraObj>,
 * ~CLinkItem (the weak copy retail keeps here)], dtor, on_new_mode, on_update, proc_intro, proc_idle, Lower,
 * proc_follow, SetFinishView, SetResultView, proc_ease, startMotion, killMotion, proc_debug. Fork F3.
 * EXACT (adapted by name/offset): the dtor and ~CSingleton (= m509 EA48 / E114), on_update (= m501's PTMF test),
 * proc_intro (= m532 9AD8), proc_idle (= m513 FF9C), killMotion (= m532 9C00), startMotion (m532 9B9C with the
 * data number), proc_debug (m532 9C38, offsets). The rest drafted from the sheet (§4.3-§4.5).
 * .data: the ctor's mem-initialiser PTMF first, the singleton strings, the six setProc PTMFs in use order, the vtable. */
#include "REL/m522Dll/camera.h"
#include "REL/m522Dll/stage.h"
#include "REL/m522Dll/player.h"

namespace m522 {

/* lbl_1_rodata_390: the debug camera's start view */
static const CCameraView s_debugView = { { -194.44806f, 3260.5298f, 1098.8625f },
                                         { -0.47258842f, 0.000948564033f, 0.000509720878f, 0.881282687f } };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    m_camModel = -1;
    m_duration = 1;
    m_frame = 0;
    m_debug = 0;
    m_debugHold = 0;
    Hu3DCameraCreate(1);
    Hu3DBGColorSet(0, 0, 0);
    m_debugCam.setView((CCameraView*)&s_debugView);
}

CCameraObj::~CCameraObj() {}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        startMotion();
        setProc(&CCameraObj::proc_intro);
        break;
    case 1:
        killMotion();
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        m_camera.getView(&m_viewFrom);
        m_camera.getView(&m_viewTo);
        setProc(&CCameraObj::proc_follow);
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
        SetFinishView();
        m_execFlags &= ~(1 << mode);
        break;
    case 4:
        SetResultView();
        m_execFlags &= ~(1 << mode);
        break;
    }
}

void CCameraObj::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
}

void CCameraObj::proc_intro()
{
    if (m_camModel != -1) {
        m_camera.getPos(1);
        if (Hu3DMotionEndCheck(m_camModel)) {
            m_execFlags &= ~1;
            setProc(&CCameraObj::proc_idle);
        }
    }
}

void CCameraObj::proc_idle()
{
    m_camera.setPos(1);
}

void CCameraObj::Lower(float dy)
{
    m_camera.getView(&m_viewFrom);
    m_viewTo = m_viewFrom;
    m_viewTo.pos.y -= dy;
}

void CCameraObj::proc_follow()
{
    m_camera.lerpView(&m_viewFrom, &m_viewTo, 0.1f);
    m_camera.getView(&m_viewFrom);
    m_camera.setPos(1);
}

/* the target 450 above the tower top at x = -580 (a local aggregate, rodata_3B0; the add in double). The
 * reference sizes rodata_3B0 0x10 (the pad before the double 450.0), which is chk's masked 4. */
void CCameraObj::SetFinishView()
{
    m_camera.getView(&m_viewFrom);
    float top = CSingleton<CStage>::GetInstance()->GetTopY();
    Vec at = { -580.0f, 0.0f, 0.0f };
    at.y = 450.0 + top;
    CCamera c;
    c.m_pos = m_camera.m_pos;
    c.m_target = at;
    c.m_up.x = 0.0f;
    c.m_up.y = 1.0f;
    c.m_up.z = 0.0f;
    c.getView(&m_viewTo);
    m_frame = 0;
    m_duration = 180;
    setProc(&CCameraObj::proc_ease);
}

/* rodata_3D0 / 3E8: the result targets and eye offsets, [0] the solo won, [1] the team survived */
static const Vec s_resultTarget[2] = { { -580.0f, 450.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } };
static const Vec s_resultOffset[2] = { { 0.0f, -460.0f, -800.0f }, { 0.0f, -920.0f, -1100.0f } };

/* Vec setter with DOUBLE components (m568 camera.cpp / m532 util.h): retail stores each component with
 * `frsp; stfs` after evaluating the arguments right to left (D980's z, y + top, x) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

void CCameraObj::SetResultView()
{
    m_camera.getView(&m_viewFrom);
    float top = CSingleton<CStage>::GetInstance()->GetTopY();
    int i = CPlayerBase::CheckEnd() == 0 ? 0 : 1; /* 0 the solo won, 1 the team survived */
    CCamera c;
    SetVec(&c.m_target, s_resultTarget[i].x, s_resultTarget[i].y + top, s_resultTarget[i].z);
    PSVECSubtract(&c.m_target, (Vec*)&s_resultOffset[i], &c.m_pos);
    c.m_up.x = 0.0f;
    c.m_up.y = 1.0f;
    c.m_up.z = 0.0f;
    c.getView(&m_viewTo);
    m_frame = 0;
    m_duration = 120;
    setProc(&CCameraObj::proc_ease);
}

/* a double square taking a const reference: bound to the (1 - cos) expression, the temporary gives retail's
 * stfd / lfd / lfd round trip, and the return its fmr (DB5C) */
static inline double Square(const double& x)
{
    return x * x;
}

/* ((1 - cos(pi f / d)) / 2)^2 = Square(1 - cos) / 4: the division by a power of two is retail's fmul by 0.25,
 * operand order included. Runs duration + 1 frames; m_duration is 180 / 120 whenever this runs (never 0) */
void CCameraObj::proc_ease()
{
    double t = Square(1.0 - cos(M_PI * (double)m_frame / (double)m_duration)) / 4.0;
    m_camera.lerpView(&m_viewFrom, &m_viewTo, t);
    m_camera.setPos(1);
    if (++m_frame > m_duration) {
        setProc(&CCameraObj::proc_idle);
    }
}

void CCameraObj::startMotion()
{
    HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x500000, HU_MEMNUM_OVL, HEAP_MODEL));
    m_camModel = Hu3DModelCameraCreate((int)mot, 1); /* the int cast is the extsh at the call (m532) */
    Hu3DCameraMotionStart(m_camModel, 1);
}

void CCameraObj::killMotion()
{
    Hu3DModelKill(m_camModel);
    m_camModel = -1;
}

/* dead debug code: Y toggles the debug camera, L holds it, R copies the game camera into it (m532 9C38) */
void CCameraObj::proc_debug()
{
    u32 btn = HuPadBtnDown[0];
    if (btn & PAD_BUTTON_Y) {
        m_debug = !m_debug;
    }
    if (m_debug) {
        if (btn & PAD_TRIGGER_L) {
            m_debugHold = !m_debugHold;
        }
        if (!m_debugHold) {
            m_debugCam.debugView(0);
        }
        if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
            m_debugCam = m_camera;
        }
        m_debugCam.setPos(1);
        /* retail: dead stores of a removed call's arguments */
        Vec* pos = &m_debugCam.m_pos;
        Vec* target = &m_debugCam.m_target;
        Vec* up = &m_debugCam.m_up;
        u8 alpha = m_debugHold ? 0xFF : 0;
    }
}

} // namespace m522
