/* camera.cpp -- m579::CCameraObj (camera.h). Retail order (sheet master_camera_stage_score_effect_water.md §4.3): ctor,
 * [~CSingleton<CCameraObj> 8C44, ~CLinkItem 8CD0: weak, unreferenced; camera.o is the first TU after the framework
 * whose ctor emits ~CLinkItem], dtor, proc_intro, proc_idle, proc_winner, startWinnerZoom, on_new_mode, on_update,
 * startMotion, killMotion, proc_debug, GetSePan, GetSeVol, PlaySe.
 * EXACT (adapted by name / offset from m537 / m536 camera.cpp, masked 0 per the sheet): the dtor and ~CSingleton (= m509
 * EA48 / E114), proc_idle (= m522 D6E8), on_update (= m501), GetSePan (= m536 6FCC); m537's ctor, startMotion (data
 * number), killMotion, proc_debug (offsets); m536's GetSeVol (constants 14 / 11; the unused int argument). Drafted
 * from the sheet: proc_intro (§4.3), proc_winner (§4.5), startWinnerZoom, on_new_mode (§4.4), PlaySe (§4.6).
 * .data 2B0..320: the ctor's mem-initialiser PTMF first, the singleton strings (ctor :53, dtor :61), the three setProc
 * PTMFs in text order (proc_intro's, startWinnerZoom's, on_new_mode's), the vtable. No .bss (ms_pointer: puku2.o A08). */
#include "REL/m579Dll/camera.h"
#include "REL/m579Dll/player.h"

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}
#ifndef __MWERKS__
#include <math.h> /* sqrtf (GetSeVol) */
#endif

namespace m579 {

/* lbl_1_rodata_1C8: the debug camera's start view */
static const CCameraView s_debugView = { { -4.401607f, 1200.5063f, 1453.7223f },
                                         { -0.38001034f, 3.3136682e-9f, 8.065794e-9f, 0.9249823f } };

CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_idle)
{
    m_camModel = -1;
    m_target = 0;
    m_debug = 0;
    m_debugHold = 0;
    Hu3DCameraCreate(1);
    Hu3DBGColorSet(0, 0, 0);
    m_debugCam.setView((CCameraView*)&s_debugView);
}

CCameraObj::~CCameraObj() {}

/* retail: setProc BEFORE the flag clear (m537 / m522 clear first) */
void CCameraObj::proc_intro()
{
    if (m_camModel != -1) {
        m_camera.getPos(1);
        if (Hu3DMotionEndCheck(m_camModel)) {
            setProc(&CCameraObj::proc_idle);
            m_execFlags &= ~1;
        }
    }
}

void CCameraObj::proc_idle()
{
    m_camera.setPos(1);
}

/* lbl_1_rodata_1E4 / 1F0: the winner view offsets from the winner's position */
static const Vec s_eyeOfs = { 0.0f, 700.0f, 500.0f };
static const Vec s_atOfs = { 0.0f, 200.0f, 0.0f };

/* DRAFT (fn_1_8EB8, 69 insns; sheet §4.5): from frame 90 an exponential ease (0.05 a frame) toward the view
 * (winner + (0,700,500)) -> (winner + (0,200,0)); never finishes (no setProc back) */
void CCameraObj::proc_winner()
{
    if ((float)++m_frame < 90.0f) {
        return;
    }
    Vec* p = &m_target->m_pos;
    CCamera c;
    PSVECAdd(p, (Vec*)&s_eyeOfs, &c.m_pos);
    PSVECAdd(p, (Vec*)&s_atOfs, &c.m_target);
    c.m_up.x = 0.0f;
    c.m_up.y = 1.0f;
    c.m_up.z = 0.0f;
    CCameraView from;
    CCameraView to;
    m_camera.getView(&from);
    c.getView(&to);
    m_camera.lerpView(&from, &to, 0.05f);
    m_camera.setPos(1);
}

/* player FinishAll: the single winner */
void CCameraObj::startWinnerZoom(CPlayer* p)
{
    m_frame = 0;
    m_target = p;
    setProc(&CCameraObj::proc_winner);
}

/* compare chain on 0..4 (r30 = mode); mode 0 does not clear its bit (proc_intro does) */
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

void CCameraObj::startMotion()
{
    HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x850002, HU_MEMNUM_OVL, HEAP_MODEL));
    m_camModel = Hu3DModelCameraCreate((int)mot, 1); /* the int cast is the extsh at the call (m532) */
    Hu3DCameraMotionStart(m_camModel, 1);
}

void CCameraObj::killMotion()
{
    Hu3DModelKill(m_camModel);
    m_camModel = -1;
}

/* dead debug code: Y toggles the debug camera, L holds it, R copies the game camera into it (m537 914C) */
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
        if (btn & PAD_TRIGGER_R) {
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

/* SE pan of a world position: 48 + screen x / 18, clamped to 0..127 (= m536 6FCC) */
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
 * __float_huge come from libc math.h (m536 camera) */
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

/* SE volume of a world position: 127 within 1400 units of the camera, falling to 96 at 2500 (clamped 96..127).
 * `no` (player UpdateModel passes its m_idx) is never read. */
s16 CCameraObj::GetSeVol(Vec* pos, int no)
{
    Vec cam, up, target, dir;
    Hu3DCameraPosGet(1, &cam, &up, &target);
    PSVECSubtract(pos, &cam, &dir);
#ifdef __MWERKS__
    double dist = MslSqrt(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0;
    float w = (dist - 14.0) / 11.0;
#else
    /* host: libm sqrtf instead of the MSL inline (no __float_nan/__float_huge on the host) */
    float w = (sqrtf(dir.z * dir.z + (dir.x * dir.x + dir.y * dir.y)) / 100.0 - 14.0) / 11.0;
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

/* volume from the depth (z) 96..127, pan from GetSePan (inlined) */
void CCameraObj::PlaySe(Vec* pos, int se)
{
    float t = 9.0f + pos->z / 100.0f;
    if (t < 0.0f) {
        t = 0.0f;
    }
    if (t > 18.0f) {
        t = 18.0f;
    }
    int vol = 96.0 + 31.0 * t / 18.0;
    HuAudFXPlayVolPan(se, vol, GetSePan(pos));
}

} // namespace m579
