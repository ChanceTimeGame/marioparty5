#include "REL/m532Dll/config.h"
#include "REL/m532Dll/camera.h"

namespace m532 {

/* lbl_1_rodata_218: the debug camera's start view (a 12.63 deg X rotation) */
static const CCameraView s_view = { { 0.0f, 104.54084f, 1265.4016f }, { 0.10995659f, 0.0f, 0.0f, 0.99393648f } };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_main)
{
    m_camModel = -1;
    m_count = 0;
    m_debug = 0;
    m_debugHold = 0;
    Hu3DCameraCreate(1);
    Hu3DBGColorSet(0, 0, 0);
    m_debugCam.setView((CCameraView*)&s_view);
}

CCameraObj::~CCameraObj() {}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        startMotion();
        setProc(&CCameraObj::proc_motion);
        break;
    case 1:
        killMotion();
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
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
    m_count++;
}

void CCameraObj::proc_motion()
{
    if (m_camModel != -1) {
        m_camera.getPos(1);
        if (Hu3DMotionEndCheck(m_camModel)) {
            m_execFlags &= ~1;
            setProc(&CCameraObj::proc_main);
        }
    }
}

void CCameraObj::proc_main()
{
    m_camera.setPos(1);
}

void CCameraObj::startMotion()
{
    HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x5A0000, HU_MEMNUM_OVL, HEAP_MODEL));
    m_camModel = Hu3DModelCameraCreate((int)mot, 1); /* the int cast is the extsh at the call (retail) */
    Hu3DCameraMotionStart(m_camModel, 1);
}

void CCameraObj::killMotion()
{
    Hu3DModelKill(m_camModel);
    m_camModel = -1;
}

/* dead debug code: Y toggles the debug camera, L holds it, R copies the game camera into it */
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

} // namespace m532
