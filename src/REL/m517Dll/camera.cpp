#include "REL/m517Dll/config.h"
#include "REL/m517Dll/camera.h"

namespace m517 {

/* lbl_1_rodata_248 / 260: the finish views {eye, target} (far: the team won; near: the solo won) */
static const Vec s_farView[2] = { { 0.0f, 500.0f, 900.0f }, { 0.0f, 200.0f, 0.0f } };
static const Vec s_nearView[2] = { { 0.0f, 600.0f, 500.0f }, { 0.0f, 400.0f, 0.0f } };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle), m_final(false)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
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
        Hu3DModelKill(m_camModel);
        m_execFlags &= ~1;
        setProc(&CCameraObj::proc_idle);
    }
}

/* mode 3: ease the camera to the finish view, 1/30 per frame */
void CCameraObj::proc_ease()
{
    Vec pos;
    Vec tgt;
    if (!m_final) {
        pos = s_farView[0];
        tgt = s_farView[1];
    } else {
        pos = s_nearView[0];
        tgt = s_nearView[1];
    }
    float rate = 30.0f;
    Vec* cpos = &m_camera.m_pos;
    Vec* cup = &m_camera.m_up;
    Vec* ctgt = &m_camera.m_target;
    cpos->x += (pos.x - cpos->x) / rate;
    cpos->y += (pos.y - cpos->y) / rate;
    cpos->z += (pos.z - cpos->z) / rate;
    ctgt->x += (tgt.x - ctgt->x) / rate;
    ctgt->y += (tgt.y - ctgt->y) / rate;
    ctgt->z += (tgt.z - ctgt->z) / rate;
    Hu3DCameraPosSetV(1, cpos, cup, ctgt);
}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0: {
        HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x4B0000, HU_MEMNUM_OVL, HEAP_MODEL));
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
}

CCameraObj::~CCameraObj() {}

} // namespace m517
