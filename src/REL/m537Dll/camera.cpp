#include "REL/m537Dll/camera.h"
#include "REL/m537Dll/stage.h"
#include "REL/m537Dll/dorrie.h"
#include "REL/m537Dll/player.h"

namespace m537 {

/* lbl_1_rodata_238: the debug camera's start view */
static const CCameraView s_debugView = { { 1.0529807f, 1812.2629f, 900.00208f },
                                         { -0.33956355f, -0.0016347608f, -0.00059535523f, 0.94058156f } };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    m_camModel = -1;
    m_duration = 180.0;
    m_debug = 0;
    m_debugHold = 0;
    Hu3DCameraCreate(1);
    Hu3DBGColorSet(0, 0, 0);
    m_debugCam.setView((CCameraView*)&s_debugView);
}

CCameraObj::~CCameraObj() {}

/* compare chain on 0..4 (r30 = mode) */
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
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
        SetWinnerView();
        m_execFlags &= ~(1 << mode);
        break;
    case 4:
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

/* lbl_1_rodata_260 / 26C / 278: the winner view in the Dorrie's "stage_a" frame (eye, target, up) */
static const Vec s_winEye = { 0.0f, 96.0f, 420.0f };
static const Vec s_winAt = { 0.0f, 96.048218f, 419.00116f };
static const Vec s_winUp = { 0.0f, 0.99883699f, -0.048218f };

void CCameraObj::SetWinnerView()
{
    int no = CPlayer::GetWinner();
    if (no < 0) {
        return;
    }
    m_camera.getView(&m_viewFrom);
    CDorrie* d = CSingleton<CStage>::GetInstance()->GetDorrie(no);
    CCamera c;
    Mtx m;
    d->GetObjMtx(CDorrie::OBJ_STAGE, m);
    PSMTXMultVec(m, (Vec*)&s_winEye, &c.m_pos);
    PSMTXMultVec(m, (Vec*)&s_winAt, &c.m_target);
    PSMTXMultVec(m, (Vec*)&s_winUp, &c.m_up);
    c.getView(&m_viewTo);
    m_frame = 0;
    setProc(&CCameraObj::proc_ease);
}

/* a double square taking a const reference (m522: the stfd / lfd / lfd round trip) */
static inline double Square(const double& x)
{
    return x * x;
}

/* ((1 - cos(pi f / d)) / 2)^2; runs m_duration + 1 frames (180.0: never 0) */
void CCameraObj::proc_ease()
{
    double t = Square(1.0 - cos(M_PI * ((double)m_frame / m_duration))) / 4.0;
    m_camera.lerpView(&m_viewFrom, &m_viewTo, t);
    m_camera.setPos(1);
    if (++m_frame > m_duration) {
        setProc(&CCameraObj::proc_idle);
    }
}

void CCameraObj::startMotion()
{
    HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x5F0000, HU_MEMNUM_OVL, HEAP_MODEL));
    m_camModel = Hu3DModelCameraCreate((int)mot, 1); /* the int cast is the extsh at the call (m532) */
    Hu3DCameraMotionStart(m_camModel, 1);
}

void CCameraObj::killMotion()
{
    Hu3DModelKill(m_camModel);
    m_camModel = -1;
}

/* dead debug code: Y toggles the debug camera, L holds it, R copies the game camera into it (m522 DD5C) */
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

} // namespace m537
