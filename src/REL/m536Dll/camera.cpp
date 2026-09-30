/* camera.cpp -- m536::CCameraObj: the game camera (intro motion, idle, winner zoom) and the SE pan/volume
 * helpers. SKELETON: bodies marked STUB are the function forks'. */
#include "REL/m536Dll/camera.h"

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}
#ifndef __MWERKS__
#include <math.h> /* sqrtf (GetSeVol) */
#endif

namespace m536 {

/* lbl_1_rodata_80/8C/98: the start view (copied component-wise; retail emits them before the ctor's literals) */
static const Vec s_startPos = { 0.0f, 1700.0f, 480.0f };
static const Vec s_startUp = { 0.0f, 1.0f, 0.0f };
static const Vec s_startTarget = { 0.0f, 0.0f, 20.0f };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCamera[0].fov = 45.0f; /* retail: redundant with PerspectiveSet (camera index 0 hard-coded) */
    m_se = HuAudFXPlayVol(0x7D7, 0x7F);
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
    proc_idle();
}

void CCameraObj::proc_idle()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Hu3DCameraPosSetV(1, pos, up, target);
}

/* dead debug code: no PTMF points here */
void CCameraObj::proc_debug()
{
    m_camera.debugView(0);
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        setProc(&CCameraObj::proc_idle);
    }
    proc_idle();
}

/* mode 0: the intro camera motion plays; the SE fades 127 -> 88 over frames 120..180 */
void CCameraObj::proc_move()
{
    if (Hu3DMotionEndCheck(m_camModel)) {
        setProc(&CCameraObj::proc_idle);
        m_execFlags &= ~1;
        Vec pos, up, target;
        Hu3DCameraPosGet(1, &pos, &up, &target); /* retail: the results are not used */
        HU3DCAMERA* camera = &Hu3DCamera[0];
        m_camera.m_pos.x = camera->pos.x;
        m_camera.m_pos.y = camera->pos.y;
        m_camera.m_pos.z = camera->pos.z;
        m_camera.m_up.x = camera->up.x;
        m_camera.m_up.y = camera->up.y;
        m_camera.m_up.z = camera->up.z;
        m_camera.m_target.x = camera->target.x;
        m_camera.m_target.y = camera->target.y;
        m_camera.m_target.z = camera->target.z;
    }
    if ((float)m_count > 120.0f && (float)m_count < 180.0f) {
        float t = ((float)m_count - 120.0f) / 60.0f;
        s16 vol = 127.0f - 39.0f * t;
        HuAudFXVolSet(m_se, vol);
    }
    m_count++;
}

/* lbl_1_rodata_E0/EC: the winner view */
static const Vec s_zoomPos = { 0.0f, 600.0f, 400.0f };
static const Vec s_zoomTarget = { 0.0f, 0.0f, -100.0f };

/* exponential ease to the winner view */
void CCameraObj::proc_zoom()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    pos->x = pos->x + 0.05f * (s_zoomPos.x - pos->x);
    pos->y = pos->y + 0.05f * (s_zoomPos.y - pos->y);
    pos->z = pos->z + 0.05f * (s_zoomPos.z - pos->z);
    target->x = target->x + 0.05f * (s_zoomTarget.x - target->x);
    target->y = target->y + 0.05f * (s_zoomTarget.y - target->y);
    target->z = target->z + 0.05f * (s_zoomTarget.z - target->z);
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
            HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x5E0007, HU_MEMNUM_OVL, HEAP_MODEL));
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
        Hu3DFogClear();
    }
}

/* SE pan of a world position: 48 + screen x / 18, clamped to 0..127 */
s16 CCameraObj::GetSePan(Vec* pos)
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
    return result;
}

#ifdef __MWERKS__
/* retail GetSeVol inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases); __float_nan and
 * __float_huge come from libc math.h */
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
#endif

/* SE volume of a world position: 127 within 1700 units of the camera, falling to 96 at 2300 (clamped) */
s16 CCameraObj::GetSeVol(Vec* pos)
{
    Vec cam, up, target, dir;
    Hu3DCameraPosGet(1, &cam, &up, &target);
    PSVECSubtract(pos, &cam, &dir);
#ifdef __MWERKS__
    double dist = MslSqrt(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0;
    float w = (dist - 17.0) / 6.0;
#else
    /* host: libm sqrtf instead of the MSL inline (no __float_nan/__float_huge on the host) */
    float w = (sqrtf(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0 - 17.0) / 6.0;
#endif
    s16 vol = 127.0f - 32.0f * w;
    int result;
    if (vol < 96) {
        result = 96;
    } else if (vol > 127) {
        result = 127;
    } else {
        result = vol;
    }
    return result;
}

CCameraObj::~CCameraObj() {}

} // namespace m536
