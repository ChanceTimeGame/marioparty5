/* camera.cpp -- m509::CCameraObj: the top-down camera (proc_main frames every player, zooming in over the
 * first 60 frames; proc_finish eases to the winner view) and the SE volume/pan helpers.
 * SKELETON: every function drafted whole from the W0 sheet (master_camera_back_setup.md §3) in m512/m536's
 * shapes; the fork verifies them. */
#include "REL/m509Dll/camera.h"
#include "REL/m509Dll/player.h"

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}
#ifndef __MWERKS__
#include <math.h> /* sqrtf (GetSeVol) */
#endif

namespace m509 {

/* lbl_1_rodata_318: the start eye (copied component-wise, m512's s_startPos spelling) */
static const Vec s_startPos = { 0.0f, 4500.0f, 0.0f };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_main)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    /* rodata_324 / 330: local aggregates (word-copied to the stack), unlike the start eye */
    Vec up = { 0.0f, 0.0f, -1.0f };
    Vec target = { 0.0f, 0.0f, 0.0f };
    m_camera.m_pos.x = s_startPos.x;
    m_camera.m_pos.y = s_startPos.y;
    m_camera.m_pos.z = s_startPos.z;
    m_camera.m_up.x = up.x;
    m_camera.m_up.y = up.y;
    m_camera.m_up.z = up.z;
    m_camera.m_target.x = target.x;
    m_camera.m_target.y = target.y;
    m_camera.m_target.z = target.z;
    m_count = 0;
}

#ifdef __MWERKS__
/* retail GetSeVol inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases; m536) */
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

/* SE volume of a world position: 127 up to 1000 units from the camera, falling linearly, clamped to 104..127.
 * The two distances are guarded function statics (bss_68 + guard 70, bss_78 + guard 80). */
s16 CCameraObj::GetSeVol(Vec* pos)
{
    static double s_far = 45.0;
    static double s_near = 10.0;
    Vec cam, up, target, dir;
    Hu3DCameraPosGet(1, &cam, &up, &target);
    PSVECSubtract(pos, &cam, &dir);
#ifdef __MWERKS__
    double dist = MslSqrt(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0;
#else
    /* host: libm sqrtf instead of the MSL inline (no __float_nan/__float_huge on the host) */
    double dist = sqrtf(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0;
#endif
    float w = (dist - s_near) / (s_far - s_near);
    s16 vol = 127.0f - 32.0f * w;
    int result;
    if (vol < 104) {
        result = 104;
    } else if (vol > 127) {
        result = 127;
    } else {
        result = vol;
    }
    return result;
}

/* SE pan of a world position: 32 + screen x / 9, clamped to 0..127 (m536 GetSePan: 48 + x / 18) */
s16 CCameraObj::GetSePan(Vec* pos)
{
    Vec screen;
    Hu3D3Dto2D(pos, 1, &screen);
    screen.x *= 0.11111111f;
    int result;
    int pan = 32.0f + screen.x;
    if (pan < 0) {
        result = 0;
    } else if (pan > 127) {
        result = 127;
    } else {
        result = pan;
    }
    s16 ret = result; /* retail: an s16 local (extsh into r29, then mr r3) -- unlike GetSeVol */
    return ret;
}

/* lbl_1_rodata_39C/3A8: the winner view */
static const Vec s_finishPos = { 0.0f, 900.0f, 500.0f };
static const Vec s_finishTarget = { 0.0f, 0.0f, -200.0f };

/* exponential ease to the winner view; m_up stays (0,0,-1) */
void CCameraObj::proc_finish()
{
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    pos->x = pos->x + 0.05f * (s_finishPos.x - pos->x);
    pos->y = pos->y + 0.05f * (s_finishPos.y - pos->y);
    pos->z = pos->z + 0.05f * (s_finishPos.z - pos->z);
    target->x = target->x + 0.05f * (s_finishTarget.x - target->x);
    target->y = target->y + 0.05f * (s_finishTarget.y - target->y);
    target->z = target->z + 0.05f * (s_finishTarget.z - target->z);
    Hu3DCameraPosSetV(1, pos, up, target);
}

void CCameraObj::startFinish()
{
    setProc(&CCameraObj::proc_finish);
}

/* lbl_1_rodata_3B8 */
static const Vec s_up = { 0.0f, 0.0f, -1.0f };

/* frame every player from straight above (CPlayer::GetBounds: x/z centre, y = the extent), 1/8 of the height
 * zooming in to 8/8 over the first 60 frames */
void CCameraObj::proc_main()
{
    m_camera.m_up.x = s_up.x;
    m_camera.m_up.y = s_up.y;
    m_camera.m_up.z = s_up.z;
    CPlayer::GetBounds(&m_camera.m_pos);
    if (m_count < 60) {
        float y = m_camera.m_pos.y / 8.0f;
        m_camera.m_pos.y = y + 7.0f * y * ((float)m_count / 60.0f);
    }
    m_camera.m_target.x = m_camera.m_pos.x;
    m_camera.m_target.y = 0.0f;
    m_camera.m_target.z = m_camera.m_pos.z;
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Hu3DCameraPosSetV(1, pos, up, target);
    m_count++;
}

/* dead debug code: no PTMF points here */
void CCameraObj::proc_debug()
{
    m_camera.debugView(0);
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        setProc(&CCameraObj::proc_main);
    }
    Vec* pos = &m_camera.m_pos;
    Vec* up = &m_camera.m_up;
    Vec* target = &m_camera.m_target;
    Hu3DCameraPosSetV(1, pos, up, target);
}

void CCameraObj::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        m_execFlags &= ~(1 << mode);
        break;
    case 1:
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        m_execFlags &= ~(1 << mode);
        break;
    case 3:
        CPlayer::StartWin();
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

} // namespace m509
