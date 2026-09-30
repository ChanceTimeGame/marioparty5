#include "REL/m521Dll/driver.h"
#include "REL/m521Dll/player.h"
#include "REL/m521Dll/clock.h"
#include "REL/m521Dll/gamemaster.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/assert.h"
#include <math.h>

namespace m521 {

inline int StuckTime() { return 150; }
static int s_stuckTime = StuckTime(); /* lbl_1_bss_A0C (dynamic, like the minigame.h triple) */

static inline bool CountDown(int& n) /* a bool temporary (retail li / li / clrlwi) */
{
    bool r = false;
    if (n > 0 && --n == 0) { r = true; }
    return r;
}

void CDriver::Update()
{
    m_info.x = 0.0f;
    m_info.y = 0.0f;
    m_info.mag = 0.0f;
    m_info.btn = false;
    Get(m_info);
}
CDriverAsPad::CDriverAsPad(int idx)
{
    m_idx = idx;
    m_padNo = GwPlayerConf[idx].padNo;
}
CDriver::~CDriver() {}
/* line padding (CalcWait) */
void CDriverAsPad::Get(INFO& info) /* m513 CInputPad::get (double precision); btn = A */
{
    int padNo = m_padNo;
    double x = (1.0f / 56.0f) * (s8)HuPadStkX[padNo];
    double y = (1.0f / 56.0f) * (s8)HuPadStkY[padNo];
    x = sin(M_PI * x / 2.0);
    y = sin(M_PI * y / -2.0);
    double m = sqrt(x * x + y * y);
    if (m > 1.0) {
        double inv = 1.0 / m;
        x *= inv;
        y *= inv;
        m = 1.0;
    }
    info.x = x;
    info.y = y;
    info.mag = m;
    info.btn = (HuPadBtnDown[padNo] & PAD_BUTTON_A) != 0;
}

CDriverAsAI::CDriverAsAI(CPlayer* player)
    : CModel(DrawHook), m_stack(Stack()), m_player(player), m_wait(0), m_stuck(0), m_timer2(0), m_procLine(-1)
{
    setHookData(this);
    setLayer(5);
    setCamera(1);
    m_overlap = false;
}

int CDriverAsAI::CalcWait(float lv)
{
    assert(lv >= 0 && lv <= 1);
    float w = 1.0f - lv;
    float r = CRandom::frandom(0.5f, 1.0f) + CRandom::frandom(1.0f, 6.0f);
    float f = 60.0f * (w + r * w);
    return f;
}

static inline CPlayer* PartnerOf(CPlayer* p) { return p->m_partner; } /* one retail pointer copy */
/* runs the top state of the stack (seeding proc00 when it is empty); the team-role toggle and the stuck timer */
void CDriverAsAI::Get(INFO& info)
{
    m_frame++;
    if (!s_inputOn) {
        m_stuck = s_stuckTime;
        return;
    }
    CPlayer* player = m_player;
    CPlayer* partner = PartnerOf(player);
    int bit = (s_roundRand >> ((player->m_slot >> 1) & 1)) & 1;
    m_hand = bit ^ (player->m_slot & 1);
    CClock* clock = player->GetClock();
    if (!partner->IsCom()) {
        if (m_overlap) {
            m_overlap = clock->AreHandsWithin(80.0f);
        } else {
            m_overlap = clock->AreHandsWithin(40.0f);
        }
    }
    if (!m_overlap) {
        if (clock->IsLocked(m_hand)) {
            if (!partner->IsCom() && partner->m_stateTimer <= 0) {
                if (player->m_slot < 2) {
                    s_roundRand ^= 1;
                } else {
                    s_roundRand ^= 2;
                }
            }
            return;
        }
        if (partner->IsCom() && clock->IsBlocked(m_hand)) {
            return;
        }
    } else {
        m_hand = 1;
    }
    Vec front;
    player->GetDir(&front);
    VECScale(&front, &front, 20.0f);
    Vec probe;
    VECAdd(&player->m_sphere.pos, &front, &probe);
    m_hit = clock->HitHands(&probe, &m_hitDir, &m_hitDepth);
    if (m_stack.empty()) {
        m_wait = CalcWait(info.lv);
        m_baseYaw = player->m_yaw;
        Push(&CDriverAsAI::proc00);
    }
    Node& n = m_stack.back();
    (n.obj->*n.fn)(info);
    if (info.mag != 0.0f || !info.btn) {
        m_stuck = s_stuckTime;
    }
    if (CountDown(m_stuck)) {
        m_stuck = s_stuckTime;
        Push(&CDriverAsAI::procToCenter);
    }
}

/* idle for m_wait frames, looking +-45 degrees around the start yaw */
void CDriverAsAI::proc00(INFO& info)
{
    /* line padding (proc00) */










    setProcLine(__LINE__, __PRETTY_FUNCTION__);
    if (CountDown(m_wait) || m_wait <= 0) {
        Change(&CDriverAsAI::proc01);
    } else {
        int w = m_wait;
        int t = w % 360;
        float a = M_PI * (2 * t) / 180.0;
        a = 45.0 * sin(a);
        a += m_baseYaw;
        CPlayer* player = m_player;
        player->m_targetYaw = a;
    }
}
static float s_grabDist = 50.0f; /* lbl_1_data_2A8 (non-const: .data, reloaded per use) */
void CDriverAsAI::proc01(INFO& info) /* walk to the grab point; push there; sidestep + jump when the other hand is hit */
{   /* line padding (proc01) */
    setProcLine(__LINE__, __PRETTY_FUNCTION__);
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    float s = clock->GetTurnDir(m_hand);
    float t;
    if (!m_overlap) {
        t = 0.5f;
    } else {
        t = 0.8f;
    }
    Vec goal;
    clock->GetHandPoint(&goal, m_hand, t, 0.5f * (100.0f * s));
    m_goal = goal;
    Vec d;
    VECSubtract(&goal, &player->m_sphere.pos, &d);
    d.y = 0.0f;
    float sq = VECSquareMag(&d);
    float r2 = s_grabDist * s_grabDist;
    if (sq < r2 && clock->IsPushSide(&player->m_sphere.pos, m_hand)) {
        StartPush();
        return;
    }
    VECNormalize(&d, &d);
    if (m_hit >= 0 && !m_overlap) {
        if (clock->IsPushSide(&player->m_sphere.pos, m_hand) || m_overlap) {
            StartPush();
        } else {
            if (m_hitDepth > 0.0f) {
                VECScale(&m_hitDir, &m_hitDir, -1.0f);
            }
            m_dir = m_hitDir;
            m_wait = 6;
            Push(&CDriverAsAI::proc0f);
        }
    } else {
        info.x = d.x;
        info.y = d.z;
        info.mag = 1.0f;
    }
}

/* Change(proc02) + Push(proc0e): face the push direction (the hand's X axis times -turn sign), then push */
void CDriverAsAI::StartPush()
{
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Change(&CDriverAsAI::proc02);
    clock->GetHandPos(&m_dir, m_hand);
    float sign = -clock->GetTurnDir(m_hand);
    VECScale(&m_dir, &m_dir, sign);
    Push(&CDriverAsAI::proc0e);
}

/* unreferenced (inlined in proc02): the probe 20 ahead touches the hand this COM does not work */
bool CDriverAsAI::IsHitOtherHand()
{
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Vec front;
    player->GetDir(&front);
    VECScale(&front, &front, 20.0f);
    Vec probe;
    VECAdd(&player->m_sphere.pos, &front, &probe);
    float depth;
    int hit = clock->HitHands(&probe, &m_hitDir, &depth);
    return hit >= 0 && hit != m_hand;
}

/* push the hand by orbiting the clock; give up off the push side or when the hand is done */
void CDriverAsAI::proc02(INFO& info)
{
    /* line padding (proc02) */





    setProcLine(__LINE__, __PRETTY_FUNCTION__);
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    if (!clock->IsPushSide(&player->m_sphere.pos, m_hand)) {
        while (m_stack.size()) {
            m_stack.pop_back();
        }
        return;
    }
    if (IsHitOtherHand() && !m_overlap) {
        Change(&CDriverAsAI::proc01);
        Vec tip;
        clock->GetHandPoint(&tip, m_hand, 1.0f, 0.0f);
        VECSubtract(&tip, &player->m_sphere.pos, &m_dir);
        m_dir.y = 0.0f;
        VECNormalize(&m_dir, &m_dir);
        Push(&CDriverAsAI::proc0e);
        Push(&CDriverAsAI::procAway);
        return;
    }
    float s = clock->GetTurnDir(m_hand);
    if (!m_overlap) {
        Orbit(info, -s, m_hand == 0 ? 200.0f : 250.0f);
        if (clock->IsLocked(m_hand)) {
            while (m_stack.size()) {
                m_stack.pop_back();
            }
        }
    } else {
        Orbit(info, -s, 280.0f);
    }
}

static inline Vec* GetCenter(CClock* c) { return &c->m_pos; } /* the clock pivot (one retail pointer copy) */
/* unreferenced: pop after m_timer2 frames, walking to the clock centre (keeps writing INFO after the pop: retail) */
void CDriverAsAI::procXX(INFO& info)
{
    if (CountDown(m_timer2) || m_timer2 <= 0) {
        m_stack.pop_back();
    }
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Vec* center = GetCenter(clock);
    Vec v;
    VECSubtract(&player->m_sphere.pos, center, &v);
    v.y = 0.0f;
    float d = sqrt(VECSquareMag(&v));
    if (!(d <= 120.0)) {
        VECNormalize(&v, &v);
        info.x = -v.x;
        info.y = -v.z;
        info.mag = 1.0f;
    }
}

/* walk to within 120 of the clock centre, then pop (the stuck timer's state) */
void CDriverAsAI::procToCenter(INFO& info)
{
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Vec* center = GetCenter(clock);
    Vec v;
    VECSubtract(&player->m_sphere.pos, center, &v);
    v.y = 0.0f;
    float d = sqrt(VECSquareMag(&v));
    VECNormalize(&v, &v); /* NaN at the centre: unused there (d <= 120) */
    if (d <= 120.0) {
        m_stack.pop_back();
    } else {
        info.x = -v.x;
        info.y = -v.z;
        info.mag = 1.0f;
    }
}

/* back off to 300 from the clock centre, then pop */
void CDriverAsAI::procAway(INFO& info)
{
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Vec* center = GetCenter(clock);
    Vec v;
    VECSubtract(&player->m_sphere.pos, center, &v);
    v.y = 0.0f;
    float d = sqrt(VECSquareMag(&v));
    VECNormalize(&v, &v);
    if (d >= 300.0f) {
        m_stack.pop_back();
    } else {
        info.x = v.x;
        info.y = v.z;
        info.mag = 1.0f;
    }
}

/* turn to face m_dir (0.8 stick), then pop */
void CDriverAsAI::proc0e(INFO& info)
{
    /* line padding (proc0e) */

    setProcLine(__LINE__, __PRETTY_FUNCTION__);
    CPlayer* player = m_player;
    Vec front;
    player->GetDir(&front);
    float dot = VECDotProduct(&m_dir, &front);
    if (dot >= 0.9f) {
        m_stack.pop_back();
        m_frame = 0;
    } else {
        info.x = m_dir.x;
        info.y = m_dir.z;
        info.mag = 0.8f;
    }
}
void CDriverAsAI::proc0f(INFO& info) /* sidestep along m_dir for m_wait frames, then one A press and pop */
{
    /* line padding (proc0f) */
    setProcLine(__LINE__, __PRETTY_FUNCTION__);
    m_dir.y = 0.0f;
    float mag = VECMag(&m_dir);
    if (mag == 0.0) {
        m_dir.x = 1.0f;
    } else {
        VECNormalize(&m_dir, &m_dir);
    }
    info.x = m_dir.x;
    info.y = m_dir.z;
    info.mag = 1.0f;
    if (CountDown(m_wait)) {
        info.btn = true;
        Pop();
        return;
    }
}

static inline float Clamp(float x, float lo, float hi)
{
    if (x < lo) {
        return lo;
    } else if (x > hi) {
        return hi;
    }
    return x;
}
/* walk around the clock centre (tangent by sign), correcting the radius toward r (+-0.1) */
void CDriverAsAI::Orbit(INFO& info, int sign, float r)
{
    CPlayer* player = m_player;
    CClock* clock = player->GetClock();
    Vec* center = GetCenter(clock);
    Vec v;
    VECSubtract(&player->m_sphere.pos, center, &v);
    float d = sqrt(VECSquareMag(&v));
    VECNormalize(&v, &v);
    v.y = 0.0f;
    Vec up;
    up.x = 0.0f;
    up.y = sign;
    up.z = 0.0f;
    Vec t;
    VECCrossProduct(&v, &up, &t);
    float k = r - d;
    k = Clamp(k, -0.1f, 0.1f);
    VECScale(&v, &v, k);
    VECAdd(&v, &t, &t);
    VECNormalize(&t, &t);
    info.x = t.x;
    info.y = t.z;
    info.mag = 1.0f;
}

/* the retail dead re-read of the assigned PTMF (D0F0 stack 0x14) is this assignment's value */
static inline CDriverAsAI::PROC SetFn(CDriverAsAI::Node& n, CDriverAsAI::PROC f) { return n.fn = f; }
/* replace the top state (push when the stack is empty) */
void CDriverAsAI::Change(PROC p)
{
    if (m_stack.empty()) {
        Push(p);
    } else {
        SetFn(m_stack.back(), p);
    }
}

void CDriverAsAI::Push(PROC p)
{
    Node n(this, p);
    m_stack.push_back(n);
}

void CDriverAsAI::Pop()
{
    m_stack.pop_back();
}

/* the name is unused */
void CDriverAsAI::setProcLine(int line, const char* name)
{
    if (m_procLine != line) {
        m_procLine = line;
    }
}

void CDriverAsAI::DrawHook(HU3DMODEL* model, Mtx* mtx) {}

static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}
static inline void SendColor(u8 r, u8 g, u8 b, u8 a)
{
    GXColor c;
    c.r = r;
    c.g = g;
    c.b = b;
    c.a = a;
    GXWGFifo.u8 = c.a;
    GXWGFifo.u8 = c.b;
    GXWGFifo.u8 = c.g;
    GXWGFifo.u8 = c.r;
}
/* unreferenced debug draw: goal -> pos (white), pos + hitDir 300 -> pos (red), pos + stick 300 mag -> pos
 * (FF 00 FF C0), each a 2-vertex GX_LINESTRIP */
void CDriverAsAI::DrawDebug(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetLineWidth(30, GX_TO_ZERO);
    CPlayer* player = m_player;
    Vec* goal = &m_goal;
    Vec* pos = &player->m_sphere.pos;
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
    GXPosition3f32(goal->x, goal->y, goal->z);
    SendColor(0xFF, 0xFF, 0xFF, 0xFF);
    GXPosition3f32(pos->x, pos->y, pos->z);
    SendColor(0xFF, 0xFF, 0xFF, 0xFF);
    GXEnd();
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
    Vec v;
    VECScale(&m_hitDir, &v, 300.0f);
    VECAdd(pos, &v, &v);
    GXPosition3f32(v.x, v.y, v.z);
    SendColor(0xFF, 0x00, 0x00, 0xFF);
    GXPosition3f32(pos->x, pos->y, pos->z);
    SendColor(0xFF, 0x00, 0x00, 0xFF);
    GXEnd();
    GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
    const CDriver::INFO& in = player->m_driver->m_info;
    Vec s;
    SetVec(&s, in.x, 0.0, in.y);
    float len = 300.0f * in.mag;
    VECScale(&s, &s, len);
    VECAdd(pos, &s, &s);
    GXPosition3f32(s.x, s.y, s.z);
    SendColor(0xFF, 0x00, 0xFF, 0xC0);
    GXPosition3f32(pos->x, pos->y, pos->z);
    SendColor(0xFF, 0x00, 0xFF, 0xC0);
    GXEnd();
}

} // namespace m521
