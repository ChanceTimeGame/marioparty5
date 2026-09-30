/* camera.cpp -- m521::CCameraObj (camera.h). Retail order (master_camera_stage_score_debugline.md §4.3): ctor,
 * [~CSingleton<CCameraObj> 142EC, ~CLinkItem 14378: weak, unreferenced], proc_idle, proc_intro, on_new_mode,
 * on_update, startWinnerZoom, proc_zoom, dtor.
 * EXACT-shaped (from finished overlays): the dtor / ~CSingleton (= m509 EA48 / E114), on_update (m501's plus the
 * `m_frame++`), proc_zoom (m568 B4A0 with 150 frames). Drafted from the asm: ctor, proc_intro, on_new_mode,
 * startWinnerZoom.
 * .data 568..5D0: the ctor's :53 strings, the dtor copy's :61 string, the three PTMFs in text order (on_new_mode's
 * proc_intro / proc_idle, startWinnerZoom's proc_zoom), the vtable. .rodata 278..2D0. No .bss (ms_pointer:
 * gamemaster.o A7C), no minigame.h. */
#include "REL/m521Dll/camera.h"

namespace m521 {

CCameraObj::CCameraObj() : m_proc(0)
{
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 26.0f, 100.0f, 2500.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
}

void CCameraObj::proc_idle() {}

/* the intro camera motion runs 240 frames, then mode 0 is done (the view stays where the motion left it) */
void CCameraObj::proc_intro()
{
    if (m_frame >= 240) {
        m_execFlags &= ~1;
        m_camera.getPos(1);
        return;
    }
}

void CCameraObj::on_new_mode(int mode)
{
    m_frame = 0;
    switch (mode) {
    case 0: {
        setProc(&CCameraObj::proc_intro);
        HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x4F000E, HU_MEMNUM_OVL, HEAP_MODEL));
        m_camModel = Hu3DModelCameraCreate(mot, 1);
        Hu3DCameraMotionStart(m_camModel, 1);
        break;
    }
    case 1:
        setProc(&CCameraObj::proc_idle);
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
    m_frame++;
}

/* lbl_1_rodata_298: the blue (team 1) winner view; mirrored in x for red */
static const CCameraView s_winView = { { 395.93204f, 1367.4567f, 292.0061f }, { -0.39237207f, 0.0f, -0.0f, 0.9198066f } };

/* gamemaster thread_exec: a 150-frame smoothstep from 50 up / 200 back to the winner view */
void CCameraObj::startWinnerZoom(int team)
{
    CCameraView v = s_winView;
    if (team == 0) {
        v.pos.x *= -1.0f;
    }
    m_from = v;
    m_to = v;
    m_from.pos.y += 50.0f;
    m_from.pos.z += 200.0f;
    setProc(&CCameraObj::proc_zoom);
    m_frame = 0;
}

/* (= m568 B4A0, 150 frames) */
void CCameraObj::proc_zoom()
{
    int len = 150;
    float t = (float)m_frame / (float)len;
    if (t > 1.0f) {
        t = 1.0f;
    }
    t = (3.0f - 2.0f * t) * (t * t);
    m_camera.lerpView(&m_from, &m_to, t);
    m_camera.setPos(1);
}

CCameraObj::~CCameraObj() {}

} // namespace m521
