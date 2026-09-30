/* camera.cpp -- m539::CCameraObj, the split-screen cameras. Retail order: SetViewport, SetSplitScreen, ctor,
 * [~CSingleton<CCameraObj>, ~CLinkItem], proc_idle, proc_split, on_new_mode, on_update, dtor.
 * Every function is masked-identical on CW; the raw residue is only the unmapped pooled `@NNN` .data labels
 * (assert strings, PTMF constants). Retail's viewport edges are kept: camera 1 ends at 640, camera 3 at 639. */
#include "REL/m539Dll/camera.h"

namespace m539 {

void CCameraObj::SetViewport(int cam, float x0, float y0, float x1, float y1)
{
    float w = x1 - x0;
    float h = y1 - y0;
    if (w < 0.0f || h < 0.0f) {
        Hu3DCameraPerspectiveSet(1 << cam, -1.0f, 100.0f, 35000.0f, 1.2f);
        return;
    }
    Hu3DCameraPerspectiveSet(1 << cam, 35.0f, 100.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1 << cam, x0, y0, w, h, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1 << cam, x0, y0, w, h);
}

void CCameraObj::SetSplitScreen(float s)
{
    /* `const` is load-bearing: with plain locals CW gives SetViewport's arguments stack/register temporaries
     * when this body is inlined into the ctor/proc_split (the out-of-line copy is the same either way) */
    const float cx = 320.0f * s;
    const float cy = 240.0f * s;
    SetViewport(0, 0.0f, 0.0f, cx - 0.5f, cy - 0.5f);
    SetViewport(1, cx + 0.5f, 0.0f, 640.0f, cy - 0.5f);
    SetViewport(2, 0.0f, cy + 0.5f, cx - 0.5f, 480.0f);
    SetViewport(3, cx + 0.5f, cy + 0.5f, 639.0f, 480.0f);
}

/* lbl_1_rodata_178: the two row views (between the ctor's literals and proc_split's; the -0.0f are retail's) */
static const CCameraView s_view[2] = {
    { { -230.16945f, 269.49237f, 1100.0f }, { -0.0f, 0.0f, -0.0f, 1.0f } },
    { { -230.16945f, 203.05112f, 1100.0f }, { -0.0f, 0.0f, -0.0f, 1.0f } },
};

CCameraObj::CCameraObj() : m_proc(0)
{
    Hu3DCameraCreate(0xF);
    SetSplitScreen(2.0f);
    Hu3DBGColorSet(0, 0, 0);
    m_camera[0].setView((CCameraView*)&s_view[0]);
    m_camera[1].setView((CCameraView*)&s_view[1]);
    Hu3DBGColorSet(0, 0, 0);
}

void CCameraObj::proc_idle() {}

void CCameraObj::proc_split()
{
    int start = 300; /* not const: retail keeps it in a register (li r30,300; cmpw; subf) */
    if (m_count > start) {
        float t = (float)(m_count - start); /* two statements: retail divides in place (t in f31) */
        t = t / 60.0f;
        if (t > 1.0f) {
            t = 1.0f;
            m_execFlags &= ~1;
        }
        SetSplitScreen(t + 2.0f * (1.0f - t));
    }
}

void CCameraObj::on_new_mode(int mode)
{
    m_count = 0;
    switch (mode) {
    case 0:
        setProc(&CCameraObj::proc_split);
        break;
    case 1:
        setProc(&CCameraObj::proc_idle);
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

/* lbl_1_data_384: Hu3DFogSet's arguments (non-const .data, no guard) */
static float s_fog[5] = { 1024.0f, 18939.0f, 37.0f, 40.0f, 57.0f };

/* the guarded initialiser of on_update's debug selector (retail stores a constant 0 under a guard, so the
 * initialiser is not a constant expression: m512's GetFps spelling guess) */
inline int FogSelInit() { return 0; }

void CCameraObj::on_update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_count++;
    m_camera[0].setPos(3);
    m_camera[1].setPos(0xC);
    /* retail debug leftover: computed, never used */
    static int s_fogSel = FogSelInit();
    s_fogSel -= (HuPadBtnDown[0] & PAD_BUTTON_UP) != 0;
    s_fogSel += (HuPadBtnDown[0] & PAD_BUTTON_DOWN) != 0;
    if (s_fogSel < 0) {
        s_fogSel = 4;
    } else if (s_fogSel > 4) {
        s_fogSel = 0;
    }
    Hu3DFogSet(s_fog[0], s_fog[1], (u8)s_fog[2], (u8)s_fog[3], (u8)s_fog[4]);
}

CCameraObj::~CCameraObj() {}

} // namespace m539
