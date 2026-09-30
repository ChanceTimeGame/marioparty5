/* camera.cpp -- m568::CCameraObj. Retail order: ctor, [~CSingleton<CCameraObj>, ~CLinkItem], SetFog, GetStartView,
 * GetGameView, proc_intro, proc_follow, proc_idle, proc_debug, on_new_mode, on_update, ZoomTo, proc_zoom, dtor.
 * .data 388..3F8: "ms_pointer == 0"/"singleton.h" (ctor), "ms_pointer != 0" (the stage GetInstance and :61), the
 * three non-const tuning floats (s_viewHeight, s_viewDist, s_viewLead), the PTMFs proc_follow, proc_intro,
 * proc_zoom (first use), the vtable. .rodata 140..1D8. No .bss / .ctors.
 * Written from the asm (master_camera_effect_archive.md §4); inline helpers: Lerp (double blend, SetFog + proc_intro),
 * VecLerp, SetVec (double components, m539 player.h).
 * SetFog / GetStartView / GetGameView take `this` (retail passes it; unused). */
#include "REL/m568Dll/camera.h"
#include "REL/m568Dll/stage.h"

namespace m568 {

CCameraObj::CCameraObj() : m_proc(0)
{
    m_unk44 = 0;
    m_unk48 = 0;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 35.7766f, 100.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    SetFog(0.0f);
}

/* the linear blend retail inlines everywhere in camera.cpp: evaluated in double, returned as T (SetFog's colours are
 * int temporaries narrowed to u8 afterwards) */
template <class T>
inline T Lerp(T a, T b, double t)
{
    return (1.0 - t) * a + t * b;
}

/* the component-wise Vec form (proc_intro) */
inline void VecLerp(Vec* out, const Vec* a, const Vec* b, float t)
{
    out->x = Lerp(a->x, b->x, t);
    out->y = Lerp(a->y, b->y, t);
    out->z = Lerp(a->z, b->z, t);
}

void CCameraObj::SetFog(float t)
{
    float start = Lerp(10000.0f, 0.001f, t);
    float end = 1000.0f + start;
    u8 r = Lerp(208, 255, t);
    u8 g = Lerp(224, 255, t);
    u8 b = Lerp(224, 255, t);
    Hu3DFogSet(start, end, r, g, b);
    Hu3DBGColorSet(r, g, b);
}

/* lbl_1_data_3B4 / 3B8 / 3BC: tuning variables (non-const .data; m539's s_fog pattern). x100 in use. */
static float s_viewHeight = 18.966015f;
static float s_viewDist = 23.7f;
static float s_viewLead = 38.16f;

/* Vec setter with DOUBLE components (m539 player.h's SetVec): retail stores each non-constant component with
 * `frsp; stfs` and keeps the returned reference in its own register */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* the ICollision call spelling (F2): a local inline taking ICollision&, so the conversion has no null check */
static inline void Raycast(ICollision& col, Vec* out, const Vec* from, const Vec* to)
{
    col.Raycast(out, from, to);
}

/* fn_1_A198 (unreferenced out-of-line copy; inlined into proc_intro): the floor under (1600, z - dist/2) by a
 * vertical raycast */
void CCameraObj::GetStartView(Vec* pos, Vec* target)
{
    CStage* stage = CStage::GetInstance();
    float z = stage->GetScrollZ();
    z += 922.7f;
    Vec from;
    Vec to;
    /* retail converts with no null check (SKELETON §5.4): through an inline taking ICollision& (F2's finding);
     * the arguments evaluate right to left (the lower end first) */
    Raycast(*stage, &from, &SetVec(&from, 1600.0f, 2000.0f, z - 100.0f * s_viewDist / 2),
            &SetVec(&to, 1600.0f, -2000.0f, z - 100.0f * s_viewDist / 2));
    float y = from.y + 100.0f * (s_viewHeight / 2);
    SetVec(pos, 400.0f, y, z - 100.0f * s_viewDist);
    SetVec(target, 0.0f, 0.0f, z);
}

/* fn_1_A3F8 (unreferenced out-of-line copy; inlined into proc_intro / proc_follow) */
void CCameraObj::GetGameView(Vec* pos, Vec* target)
{
    CStage* stage = CStage::GetInstance();
    float z = stage->GetScrollZ();
    z += 100.0f * s_viewLead;
    Vec from;
    Vec to;
    /* retail converts with no null check (SKELETON §5.4): through an inline taking ICollision& (F2's finding);
     * the arguments evaluate right to left (the lower end first) */
    Raycast(*stage, &from, &SetVec(&from, 1600.0f, 2000.0f, z - 100.0f * s_viewDist / 2),
            &SetVec(&to, 1600.0f, -2000.0f, z - 100.0f * s_viewDist / 2));
    float y = from.y + 100.0f * s_viewHeight;
    SetVec(pos, 1.0f, y, z);
    SetVec(target, 1.0f, from.y, z - 100.0f * s_viewDist);
}

/* fn_1_A664 (PTMF data_3CC, mode 0): both views inlined; t = count / 150 is not clamped (retail: the proc switches
 * to proc_follow on the frame m_count reaches 150, which still blends with t = 1) */
void CCameraObj::proc_intro()
{
    Vec p0;
    Vec p1;
    Vec t0;
    Vec t1;
    GetStartView(&p0, &t0);
    GetGameView(&p1, &t1);
    int len = 150;
    if (m_count >= len) {
        setProc(&CCameraObj::proc_follow);
        m_execFlags &= ~1;
    }
    float t = (float)m_count / (float)len;
    VecLerp(&m_camera.m_pos, &p0, &p1, t);
    VecLerp(&m_camera.m_target, &t0, &t1, t);
    m_camera.m_up.x = 0.0f;
    m_camera.m_up.y = 1.0f;
    m_camera.m_up.z = 0.0f;
    m_camera.setPos(1);
}

void CCameraObj::proc_follow()
{
    GetGameView(&m_camera.m_pos, &m_camera.m_target);
    m_camera.m_up.x = 0.0f;
    m_camera.m_up.y = 1.0f;
    m_camera.m_up.z = 0.0f;
    m_camera.setPos(1);
}

void CCameraObj::proc_idle() {}

void CCameraObj::proc_debug()
{
    m_camera.debugView(0);
}

void CCameraObj::on_new_mode(int mode)
{
    m_count = 0;
    switch (mode) {
    case 0:
        setProc(&CCameraObj::proc_intro);
        break;
    case 1:
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        m_execFlags &= ~(1 << mode);
        break;
    case 4: {
        setProc(0);
        CCamera* cam = &m_camera;
        cam->m_up.x = 0.0f;
        cam->m_up.y = 1.0f;
        cam->m_up.z = 0.0f;
        cam->m_pos.x = 0.0f;
        cam->m_pos.y = 712.93f;
        cam->m_pos.z = 3394.86f;
        cam->m_target.x = 0.0f;
        cam->m_target.y = 367.26f;
        cam->m_target.z = -54.77f;
        cam->setPos(1);
        Hu3DCamera[0].fov = 18.43f;
        break;
    }
    }
}

void CCameraObj::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_count++;
}

/* fn_1_B320 (game_master thread_exec, the result): smooth-step from the current view to one aimed at `at` (raised by
 * 120; rodata 1CC is 120.00001f) and pulled back by `dist` */
void CCameraObj::ZoomTo(Vec* at, float dist)
{
    m_camera.getView(&m_viewFrom);
    CCamera c = m_camera;
    Vec v;
    SetVec(&v, at->x, 120.00001f + at->y, at->z);
    c.getOffset(&v);
    SetVec(&v, 0.0f, 0.0f, dist);
    c.applyOffsetLocal(&v);
    c.getView(&m_viewTo);
    m_count = 0;
    setProc(&CCameraObj::proc_zoom);
}

/* fn_1_B4A0 (PTMF data_3D8) */
void CCameraObj::proc_zoom()
{
    int len = 90;
    float t = (float)m_count / (float)len;
    if (t > 1.0f) {
        t = 1.0f;
    }
    t = (3.0f - 2.0f * t) * (t * t);
    m_camera.lerpView(&m_viewFrom, &m_viewTo, t);
    m_camera.setPos(1);
}

CCameraObj::~CCameraObj() {}

} // namespace m568
