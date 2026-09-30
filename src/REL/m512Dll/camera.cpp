/* camera.cpp -- m512::CCameraObj: the game camera and the positional SE helpers.
 * Fork C: every function written whole in reference order; all 15 at the reference count, masked 0
 * (raw residue: unnamed .data PTMF/assert literals only). */
#include "REL/m512Dll/camera.h"
#include "REL/m512Dll/player.h"

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}

namespace m512 {

/* lbl_1_rodata_80/8C/98: the start view (copied component-wise; retail emits them before the ctor's literals) */
static const Vec s_startPos = { 0.0f, 2800.0f, 3000.0f };
static const Vec s_startUp = { 0.0f, 1.0f, 0.0f };
static const Vec s_startTarget = { 0.0f, 0.0f, 200.0f };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_follow)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCamera[0].fov = 45.0f; /* retail: redundant with PerspectiveSet (camera index 0 hard-coded) */
    Hu3DFogSet(1500.0f, 30000.0f, 200, 200, 200);
    m_camera.m_pos.x = s_startPos.x;
    m_camera.m_pos.y = s_startPos.y;
    m_camera.m_pos.z = s_startPos.z;
    m_camera.m_up.x = s_startUp.x;
    m_camera.m_up.y = s_startUp.y;
    m_camera.m_up.z = s_startUp.z;
    m_camera.m_target.x = s_startTarget.x;
    m_camera.m_target.y = s_startTarget.y;
    m_camera.m_target.z = s_startTarget.z;
    m_count = 0;
    proc_follow();
}

/* the view that frames every player: centre of the players' bounding box (which always holds the origin,
 * CPlayer::GetBounds), the eye 45 degrees up and back at a distance from the box size */
void CCameraObj::getView(Vec* center, Vec* eye)
{
    Vec ext;
    float off;
    CPlayer::GetBounds(center, &ext);
    float dist = ext.x;
    ext.z *= 0.9;
    if (ext.z > dist) {
        dist = ext.z;
    }
    dist += 750.0f;
    center->y += 100.0f;
    if (ext.x > ext.z) {
        off = 0.1f * (ext.x - ext.z);
    }
    center->z -= off;
    center->z += 200.0f;
    eye->x = center->x;
    eye->y = center->y + dist * cos(M_PI / 4);
    eye->z = center->z + dist * sin(M_PI / 4);
}

/* the idle/intro-end camera: ease the eye (0.05) and the target (0.1) toward getView */
void CCameraObj::proc_follow()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Vec center;
    Vec eye;
    getView(&center, &eye);
    pos->x += 0.05f * (eye.x - pos->x);
    pos->y += 0.05f * (eye.y - pos->y);
    pos->z += 0.05f * (eye.z - pos->z);
    target->x += 0.1f * (center.x - target->x);
    target->y += 0.1f * (center.y - target->y);
    target->z += 0.1f * (center.z - target->z);
    Hu3DCameraPosSetV(1, pos, up, target);
}

/* mode 2: getView set immediately; m_pos/m_target are not updated */
void CCameraObj::proc_play()
{
    Vec* up = &m_camera.m_up;
    Vec center;
    Vec eye;
    getView(&center, &eye);
    Hu3DCameraPosSetV(1, &eye, up, &center);
}

/* dead debug code: no PTMF points here */
void CCameraObj::proc_debug()
{
    m_camera.debugView(0);
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        setProc(&CCameraObj::proc_follow);
    }
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Hu3DCameraPosSetV(1, pos, up, target);
}

/* mode 0: the intro camera motion plays; at its end the camera continues from where the motion left it */
void CCameraObj::proc_move()
{
    if (Hu3DMotionEndCheck(m_camModel)) {
        setProc(&CCameraObj::proc_follow);
        m_execFlags &= ~1;
        Vec pos, up, target;
        Hu3DCameraPosGet(1, &pos, &up, &target);
        m_camera.m_pos = pos;
        m_camera.m_up = up;
        m_camera.m_target = target;
    }
    m_count++;
}

/* winner view: ease around the winner, 1000 units along its heading turned by 90 degrees, 300 up */
void CCameraObj::proc_zoom()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Vec eye;
    Vec w;
    float a = 90.0f + -CPlayer::GetWinnerPos(&w);
    float dx = 100.0 * (10.0 * cos(M_PI * a / 180.0));
    float dz = 100.0 * (10.0 * sin(M_PI * a / 180.0));
    w.y += 100.0f;
    eye.x = w.x + dx;
    eye.z = w.z + dz;
    eye.y = 300.0f + w.y;
    pos->x += 0.05f * (eye.x - pos->x);
    pos->y += 0.05f * (eye.y - pos->y);
    pos->z += 0.05f * (eye.z - pos->z);
    target->x += 0.1f * (w.x - target->x);
    target->y += 0.1f * (w.y - target->y);
    target->z += 0.1f * (w.z - target->z);
    Hu3DCameraPosSetV(1, pos, up, target);
}

void CCameraObj::startWinnerZoom()
{
    setProc(&CCameraObj::proc_zoom);
}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        m_count = 0;
        setProc(&CCameraObj::proc_move);
        {
            HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x460012, HU_MEMNUM_OVL, HEAP_MODEL));
            m_camModel = Hu3DModelCameraCreate(mot, 1);
        }
        Hu3DCameraMotionStart(m_camModel, 1);
        break;
    case 1:
        Hu3DModelKill(m_camModel);
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        setProc(&CCameraObj::proc_play);
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
        Hu3DFogSet(1000.0f, 30000.0f, 200, 200, 200);
    }
}

/* retail: always -1, the handle is dropped (every caller ignores it) */
int CCameraObj::PlaySe(Vec* pos, int se)
{
    int mode = CGameObject::GetUpdateMode(); /* a named local: retail's arg spill + r31 */
    if (mode == 2) {
        PlaySePan(pos, se);
    }
    return -1;
}

/* pan = 48 + screen x / 18, clamped to 0..127 (m536 GetSePan) */
int CCameraObj::PlaySePan(Vec* pos, int se)
{
    Vec screen;
    Hu3D3Dto2D(pos, 1, &screen);
    screen.x *= 0.055555556f;
    int result;
    int pan = 48.0f + screen.x;
    if (pan < 0) {
        result = 0;
    } else if (pan > 127) {
        result = 127;
    } else {
        result = pan;
    }
    int p = (s16)result; /* int holding an s16: retail's second extsh at the HuAudFXPanning call */
    int id = HuAudFXPlay(se);
    HuAudFXPanning(id, p);
    return id;
}

CCameraObj::~CCameraObj() {}

} // namespace m512
