/* camera.cpp -- m501::CCameraObj: the game camera (intro motion, idle, winner focus). */
/* retail camera.o has no assert anywhere: its inlined CSingleton ctor/dtor (and fn_1_9C8C) lack the
 * singleton.h asserts and its .data has no assert strings, so this TU was built with asserts off. */
#define MGCPP_NO_ASSERT
#include "REL/m501Dll/camera.h"
#include "REL/m501Dll/player.h"

namespace m501 {

/* SetVec (double components, frsp on each store): shared definition in player.h [fork A] */

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
}

/* blend from the current view to one looking at the winner at pos (called by CPlayer::StartPlayerWin) */
void CCameraObj::set_focus_player(Vec* pos)
{
    m_camera.getView(&m_from);
    CCamera camera = m_camera;
    Vec offset;
    SetVec(&offset, pos->x, 120.00001f + pos->y, pos->z);
    camera.getOffset(&offset);
    SetVec(&offset, 0.0f, 0.0f, 1400.0f);
    camera.applyOffsetLocal(&offset);
    camera.getView(&m_to);
    m_count = 0;
    setProc(&CCameraObj::proc_focus_player);
}

void CCameraObj::proc_focus_player()
{
    int frames = 30;
    float t = (float)m_count / (float)frames;
    if (t > 1.0f) {
        t = 1.0f;
    }
    t = (3.0f - 2.0f * t) * (t * t);
    m_camera.lerpView(&m_from, &m_to, t);
    m_camera.setPos(1);
    m_count++;
}

void CCameraObj::proc_null() {}

/* mode 0: the camera motion (started in on_new_mode) plays; players appear at frame 208 */
void CCameraObj::proc_move_up()
{
    if (m_count >= 127 && m_count <= 185) {
        float t = (m_count - 127) / 58.0f; /* retail: computed and never used */
    }
    if (m_count == 208) {
        CPlayer::PlayerShow();
    }
    if (m_count >= 208 && m_count <= 240) {
        float t = (m_count - 208) / 32.0f; /* retail: computed and never used */
    }
    if (m_count > 240) {
        setProc(&CCameraObj::proc_idle);
        m_execFlags &= ~1;
        m_camera.getPos(1);
    }
    m_count++;
}

void CCameraObj::proc_idle()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Hu3DCameraPosSetV(1, pos, up, target);
}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        m_count = 0;
        setProc(&CCameraObj::proc_move_up);
        {
            HU3DMOTID mot = Hu3DMotionCreateData(0x3B0003);
            m_camModel = Hu3DModelCameraCreate(mot, 1);
        }
        Hu3DCameraMotionStart(m_camModel, 1);
        break;
    case 1:
        Hu3DModelKill(m_camModel);
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
}

CCameraObj::~CCameraObj() {}

} // namespace m501
