#include "REL/m513Dll/camera.h"

namespace m513 {

/* lbl_1_data_6C8: unreferenced (no relocation anywhere); emitted first, so it is a file-scope table
 * (guess {eye, target, up}-like). Non-const: .data. */
static Vec s_view[3] = {
    { 0.0f, 250.0f, -500.0f },
    { 0.0f, 20.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
};

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    m_yaw = 0.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 35.0f, 100.0f, 6000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    m_camera.resetLookAt();
}

void CCameraObj::proc_idle()
{
    m_camera.setPos(1);
}

void CCameraObj::proc_intro()
{
    m_camera.getPos(1);
    if (Hu3DMotionEndCheck(m_camModel)) {
        m_goalPos = m_camera.m_pos;
        m_goalTarget = m_camera.m_target;
        Hu3DModelKill(m_camModel);
        m_execFlags &= ~1;
        setProc(&CCameraObj::proc_idle);
    }
}

void CCameraObj::proc_ease()
{
    Vec target = m_goalTarget;
    Vec pos = m_goalPos;
    float rate = 24.0f;
    Vec* cpos = &m_camera.m_pos;
    Vec* cup = &m_camera.m_up;
    Vec* ctgt = &m_camera.m_target;
    cpos->x += (pos.x - cpos->x) / rate;
    cpos->y += (pos.y - cpos->y) / rate;
    cpos->z += (pos.z - cpos->z) / rate;
    ctgt->x += (target.x - ctgt->x) / rate;
    ctgt->y += (target.y - ctgt->y) / rate;
    ctgt->z += (target.z - ctgt->z) / rate;
    Hu3DCameraPosSetV(1, cpos, cup, ctgt);
}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0: {
        HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x470003, HU_MEMNUM_OVL, HEAP_MODEL));
        m_camModel = Hu3DModelCameraCreate((int)mot, 1); /* the int cast is the extsh at the call (m532) */
        Hu3DCameraMotionStart(m_camModel, 1);
        setProc(&CCameraObj::proc_intro);
        break;
    }
    case 1:
        Hu3DModelKill(m_camModel);
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
        setProc(&CCameraObj::proc_ease);
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
    Vec d;
    PSVECSubtract(&m_camera.m_pos, &m_camera.m_target, &d);
    m_yaw = 180.0 * (atan2(d.x, d.z) / M_PI);
}

CCameraObj::~CCameraObj() {}

} // namespace m513
