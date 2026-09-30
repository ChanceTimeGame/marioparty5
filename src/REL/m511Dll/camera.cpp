#include "REL/m511Dll/config.h"
#include "REL/m511Dll/camera.h"
#include "REL/m511Dll/player.h"

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}

namespace m511 {

/* lbl_1_rodata_248: the Hu3D camera bit of each quadrant */
static const u32 s_camBit[4] = { 1, 2, 4, 8 };

/* lbl_1_bss_A50: the per-player SE volume (proc_result fades the losers) */
static float s_vol[4];


CCameraObj::CCameraObj() : m_proc(&CCameraObj::proc_follow0), m_winner(-1)
{
    /* retail: the quadrant origins, copied to the stack and never read (lbl_1_rodata_258) */
    Vec origin[4] = {
        { 0.0f, 0.0f, 0.0f },
        { 320.0f, 0.0f, 0.0f },
        { 0.0f, 240.0f, 0.0f },
        { 320.0f, 240.0f, 0.0f },
    };
    /* lbl_1_rodata_288/294/2A0: the start view (copied component-wise; after the dead local's initialiser) */
    static const Vec s_startPos = { 0.0f, 2800.0f, 3000.0f };
    static const Vec s_startUp = { 0.0f, 1.0f, 0.0f };
    static const Vec s_startTarget = { 0.0f, 0.0f, 200.0f };
    for (int i = 0; i < 4; i++) {
        SubCam* c = &m_cam[i];
        c->cam.m_pos.x = s_startPos.x;
        c->cam.m_pos.y = s_startPos.y;
        c->cam.m_pos.z = s_startPos.z;
        c->cam.m_up.x = s_startUp.x;
        c->cam.m_up.y = s_startUp.y;
        c->cam.m_up.z = s_startUp.z;
        c->cam.m_target.x = s_startTarget.x;
        c->cam.m_target.y = s_startTarget.y;
        c->cam.m_target.z = s_startTarget.z;
        c->active = false;
        m_count = 0;
    }
    for (int j = 0; j < 4; j++) {
        s_vol[j] = 1.0f;
    }
}

/* clamps to the 640x480 screen; a quadrant of zero width or height has its Hu3D camera killed, re-created later */
void CCameraObj::setViewport(int i, float x, float y, float w, float h)
{
    SubCam* c = &m_cam[i];
    if (x < 0.0f) {
        x = 0.0f;
    }
    if (y < 0.0f) {
        y = 0.0f;
    }
    if (x > 640.0f) {
        x = 640.0f;
    }
    if (y > 480.0f) {
        y = 480.0f;
    }
    if (w < 0.0f) {
        w = 0.0f;
    }
    if (h < 0.0f) {
        h = 0.0f;
    }
    if (w > 640.0f) {
        w = 640.0f;
    }
    if (h > 480.0f) {
        h = 480.0f;
    }
    c->x = x;
    c->y = y;
    c->w = w;
    c->h = h;
    if (0.0f != w && 0.0f != h) {
        if (!c->active) {
            Hu3DCameraCreate(s_camBit[i]);
            c->active = true;
        }
    } else if (c->active == true) {
        Hu3DCameraKill(s_camBit[i]);
        c->active = false;
    }
    if (c->active) {
        Hu3DCameraPerspectiveSet(s_camBit[i], 45.0f, 100.0f, 35000.0f, 1.2f);
        Hu3DCameraViewportSet(s_camBit[i], x, y, w, h, 0.0f, 1.0f);
        Hu3DCameraScissorSet(s_camBit[i], x, y, w, h);
    }
}

/* the four quadrants around the split point, with a 2-pixel divider cross */
void CCameraObj::setSplit(float cx, float cy)
{
    m_split.x = cx;
    m_split.y = cy;
    float x;
    float y;
    float w;
    float h;
    x = y = 0.0f;
    w = cx - 1.0f;
    h = cy - 1.0f;
    setViewport(0, x, y, w, h);
    x = 1.0f + cx;
    y = 0.0f;
    w = 639.0f - cx;
    h = cy - 1.0f;
    setViewport(1, x, y, w, h);
    x = 0.0f;
    y = 1.0f + cy;
    w = cx - 1.0f;
    h = 479.0f - cy;
    setViewport(2, x, y, w, h);
    x = 1.0f + cx;
    y = 1.0f + cy;
    w = 639.0f - cx;
    h = 479.0f - cy;
    setViewport(3, x, y, w, h);
}

/* inline wrappers: inside an inlined smooth() each member-address argument lands in its own temporary (retail's
 * r25..r28 in the procs); out of line they are substituted */
static inline void VecSub(Vec* a, Vec* b, Vec* d)
{
    PSVECSubtract(a, b, d);
}

static inline void VecAdd(Vec* a, Vec* b, Vec* d)
{
    PSVECAdd(a, b, d);
}

static inline void VecScale(Vec* a, Vec* d, float s)
{
    PSVECScale(a, d, s);
}

/* ease the target (0.1) and the eye (0.05) of quadrant i toward the given ones; the results go back out */
void CCameraObj::smooth(int i, Vec* target, Vec* pos)
{
    SubCam* c = &m_cam[i];
    VecSub(target, &c->cam.m_target, target);
    VecScale(target, target, 0.1f);
    VecAdd(target, &c->cam.m_target, target);
    VecSub(pos, &c->cam.m_pos, pos);
    VecScale(pos, pos, 0.05f);
    VecAdd(pos, &c->cam.m_pos, pos);
}

void CCameraObj::getFollow(int i, Vec* target, Vec* pos)
{
    Vec t;
    Vec p;
    CPlayer::GetCameraPos(i, &t, &p);
    smooth(i, &t, &p);
    *target = t;
    *pos = p;
}

void CCameraObj::getFollowResult(int i, Vec* target, Vec* pos)
{
    Vec t;
    Vec p;
    CPlayer::GetFrontCameraPos(i, &t, &p);
    smooth(i, &t, &p);
    *target = t;
    *pos = p;
}

/* every quadrant's follow step (inline only: proc_split's tail). The loop lives in this inlined body so that
 * getFollow's i is copied once (retail r25) and its pointer arguments land in temporaries (r28/r29), as retail's */
inline void CCameraObj::follow()
{
    for (int i = 0; i < 4; i++) {
        SubCam* c = &m_cam[i];
        getFollow(i, &c->cam.m_target, &c->cam.m_pos);
        c->cam.setPos(s_camBit[i]);
    }
}

/* the ctor's proc (proc_follow's body) */
void CCameraObj::proc_follow0()
{
    for (int i = 0; i < 4; i++) {
        SubCam* c = &m_cam[i];
        Vec p;
        Vec t;
        CPlayer::GetCameraPos(i, &t, &p);
        smooth(i, &t, &p);
        c->cam.m_target = t;
        c->cam.m_pos = p;
        c->cam.setPos(s_camBit[i]);
    }
}

void CCameraObj::proc_follow()
{
    for (int i = 0; i < 4; i++) {
        SubCam* c = &m_cam[i];
        Vec p;
        Vec t;
        CPlayer::GetCameraPos(i, &t, &p);
        smooth(i, &t, &p);
        c->cam.m_target = t;
        c->cam.m_pos = p;
        c->cam.setPos(s_camBit[i]);
    }
}

/* dead debug code: no PTMF points here */
void CCameraObj::proc_debug()
{
    m_debugCam.debugView(0);
    if (HuPadBtnDown[0] & PAD_BUTTON_Y) {
        setProc(&CCameraObj::proc_follow);
    }
    m_debugCam.setPos(1);
}

/* the intro split: quadrant 0 shrinks from the full screen to its corner in s_len frames; never changes proc */
void CCameraObj::proc_split()
{
    static float s_len = 60.0f;
    float t = m_count++;
    if (t > s_len) {
        t = s_len;
    }
    /* setSplit written out with the split point as a macro: retail recomputes it for every use */
#define SX (640.0f - 320.0f * t / s_len)
#define SY (480.0f - 240.0f * t / s_len)
    m_split.x = SX;
    m_split.y = SY;
    float h; /* declared in reverse: retail's x..h take f27..f30 */
    float w;
    float y;
    float x;
    x = y = 0.0f;
    w = SX - 1.0f;
    h = SY - 1.0f;
    setViewport(0, x, y, w, h);
    x = 1.0f + SX;
    y = 0.0f;
    w = 639.0f - SX;
    h = SY - 1.0f;
    setViewport(1, x, y, w, h);
    x = 0.0f;
    y = 1.0f + SY;
    w = SX - 1.0f;
    h = 479.0f - SY;
    setViewport(2, x, y, w, h);
    x = 1.0f + SX;
    y = 1.0f + SY;
    w = 639.0f - SX;
    h = 479.0f - SY;
    setViewport(3, x, y, w, h);
#undef SX
#undef SY
    follow();
}

/* mode 0: the intro camera motion; at its end every quadrant continues from where the motion left camera 1 */
void CCameraObj::proc_intro()
{
    if (Hu3DMotionEndCheck(m_camModel)) {
        m_count = 0;
        setProc(&CCameraObj::proc_split);
        m_execFlags &= ~1;
        for (int i = 0; i < 4; i++) {
            SubCam* c = &m_cam[i];
            Vec pos;
            Vec up;
            Vec target;
            Hu3DCameraPosGet(s_camBit[0], &pos, &up, &target);
            c->cam.m_pos = pos;
            c->cam.m_up = up;
            c->cam.m_target = target;
        }
    }
    m_count++;
    Hu3DCameraPerspectiveSet(1, 45.0f, 100.0f, 35000.0f, 1.2f);
}

/* the result: the result framing, then the winner's quadrant grows to the full screen in s_len frames while the
 * others' SE volume fades */
void CCameraObj::proc_result()
{
    for (int i = 0; i < 4; i++) {
        SubCam* c = &m_cam[i];
        Vec p;
        Vec t;
        CPlayer::GetFrontCameraPos(i, &t, &p);
        smooth(i, &t, &p);
        c->cam.m_target = t;
        c->cam.m_pos = p;
        c->cam.setPos(s_camBit[i]);
    }
    if (m_winner >= 0) {
        static float s_len = 120.0f;
        float t = m_count++;
        if (t > s_len) {
            t = s_len;
        }
        t = t / s_len;
        float sx = 320.0f;
        float sy = 240.0f;
        switch (m_winner) {
        case 0:
            sx = 320.0 + 320.0 * t;
            sy = 240.0 + 240.0 * t;
            break;
        case 1:
            sx = 320.0 - 320.0 * t;
            sy = 240.0 + 240.0 * t;
            break;
        case 2:
            sx = 320.0 + 320.0 * t;
            sy = 240.0 - 240.0 * t;
            break;
        case 3:
            sx = 320.0 - 320.0 * t;
            sy = 240.0 - 240.0 * t;
            break;
        }
        setSplit(sx, sy);
        for (int k = 0; k < 4; k++) {
            s_vol[k] = 1.0 - t;
            if (s_vol[k] < 0.0f) {
                s_vol[k] = 0.0f;
            }
        }
        s_vol[m_winner] = 1.0f;
    }
}

/* CPlayer::CheckGameEnd (normal mode) */
void CCameraObj::setWinner(int no)
{
    m_winner = no;
    setProc(&CCameraObj::proc_result);
    m_count = 0;
}

/* lbl_1_bss_A70: the last mode (the SE helpers pan on quadrant 0 in mode 1, on the winner's in mode 3) */
static int s_mode;


void CCameraObj::on_new_mode(int mode)
{
    s_mode = mode;
    switch (mode) {
    case 0: {
        m_count = 0;
        setProc(&CCameraObj::proc_intro);
        SubCam* c = &m_cam[0]; /* retail: stored, never read */
        Hu3DCameraCreate(1);
        HU3DMOTID mot = Hu3DMotionCreate(HuDataSelHeapReadNum(0x45001F, HU_MEMNUM_OVL, HEAP_MODEL));
        m_camModel = Hu3DModelCameraCreate(mot, 1);
        Hu3DCameraMotionStart(m_camModel, 1);
        break;
    }
    case 1:
        Hu3DModelKill(m_camModel);
        m_execFlags &= ~(1 << mode);
        break;
    case 2:
        setProc(&CCameraObj::proc_follow);
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

/* the out-of-line pan: the value is a macro (evaluated up to three times by the clamp, retail) */
#define PAN_VALUE(f) ((int)(32.0f + (f)))

/* pan 0..127 from the screen x of pos in the quadrant that hears it (quadrant 0 in mode 1, the winner's in
 * mode 3): 32 + (x + sx / 576 * w) / 9 */
s16 CCameraObj::GetPan(const Vec* pos, int pno)
{
    CCameraObj* cam = CSingleton<CCameraObj>::GetInstance();
    int c = pno;
    if (s_mode == 1) {
        c = 0;
    }
    if (s_mode == 3 && cam->m_winner >= 0) {
        c = cam->m_winner;
    }
    Vec out;
    Hu3D3Dto2D((Vec*)pos, s_camBit[c], &out);
    float r = out.x / 576.0f;
    float f = cam->m_cam[c].x + r * cam->m_cam[c].w;
    f *= 0.11111111f;
    int pan;
    if (PAN_VALUE(f) < 0) {
        pan = 0;
    } else if (PAN_VALUE(f) > 127) {
        pan = 127;
    } else {
        pan = PAN_VALUE(f);
    }
    return pan;
}

/* the inlined pan of PlaySe / PlaySePlay / UpdateSe: the value computed once */
static inline s16 CalcPan(const Vec* pos, int pno)
{
    CCameraObj* cam = CSingleton<CCameraObj>::GetInstance();
    int c = pno;
    if (s_mode == 1) {
        c = 0;
    }
    if (s_mode == 3 && cam->m_winner >= 0) {
        c = cam->m_winner;
    }
    Vec out;
    Hu3D3Dto2D((Vec*)pos, s_camBit[c], &out);
    float r = out.x / 576.0f;
    float f = cam->m_cam[c].x + r * cam->m_cam[c].w;
    f *= 0.11111111f;
    int v = 32.0f + f;
    int pan;
    if (v < 0) {
        pan = 0;
    } else if (v > 127) {
        pan = 127;
    } else {
        pan = v;
    }
    return pan;
}

/* the player's engine loops: play, pan; the handle */
int CCameraObj::PlaySe(const Vec* pos, int seNo, int pno)
{
    int h = HuAudFXPlay(seNo);
    HuAudFXPanning(h, CalcPan(pos, pno));
    return h;
}

/* play only in update mode 2 (-1 otherwise: UpdateSe guards it on the host) */
int CCameraObj::PlaySePlay(const Vec* pos, int seNo, int pno)
{
    int h = -1;
    if (CGameObject::GetUpdateMode() == 2) {
        h = HuAudFXPlay(seNo);
        HuAudFXPanning(h, CalcPan(pos, pno));
    }
    return h;
}

/* pan, pitch (8191 * 2 * (pitch - 0.5), clamped to an s14) and volume (112 * the player's s_vol: the raw pno, not
 * the remapped quadrant) of a playing SE */
void CCameraObj::UpdateSe(const Vec* pos, int handle, int pno, float pitch)
{
    int p = 8191.0 * (2.0 * (pitch - 0.5));
    if (p > 8191) {
        p = 8191;
    }
    if (p < -8192) {
        p = -8192;
    }
    HuAudFXPanning(handle, CalcPan(pos, pno));
    HuAudFXPitchSet(handle, p);
    HuAudFXVolSet(handle, 112.0f * s_vol[pno]);
}

/* kills no Hu3D camera (the Hu3D teardown does) */
CCameraObj::~CCameraObj() {}

} // namespace m511
