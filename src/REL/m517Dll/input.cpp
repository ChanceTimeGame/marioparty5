#include "REL/m517Dll/config.h"
#include "REL/m517Dll/player.h"
#include "REL/m517Dll/util.h"
#include "REL/m517Dll/effect.h"
#include "REL/m517Dll/stage.h"
#include "REL/m517Dll/input.h"
extern "C" {
#include "game/frand.h"
}

namespace m517 {

/* (frand() & 0xFFFF) / 65536 as an expression (m513: an inline function keeps its result in a saved FPR) */
#define RND() ((1.0f / 65536) * (frand() & 0xFFFF))

CInput::CInput()
{
    m_data.x = 0.0f;
    m_data.y = 0.0f;
    m_data.mag = 0.0f;
    m_data.level = 0;
}

void CInput::update()
{
    m_data.x = 0.0f;
    m_data.y = 0.0f;
    get(&m_data);
}

CInputPad::CInputPad(int idx)
{
    m_idx = idx;
    m_padNo = GwPlayerConf[idx].padNo;
}

CInput::~CInput() {}

void CInputPad::get(Data* data)
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
    data->x = x;
    data->y = y;
    data->mag = m;
}

CInputCom::CInputCom(int idx, int dif)
{
    m_idx = idx;
    m_timer = 0.0f;
    m_fresh = true;
    m_data.level = dif;
    m_stick.x = 0.0f;
    m_stick.y = 0.0f;
    m_stick.z = 0.0f;
    m_ballVel.x = 0.0f;
    m_ballVel.y = 0.0f;
    m_ballVel.z = 0.0f;
    m_target.x = 0.0f;
    m_target.y = 0.0f;
    m_target.z = 0.0f;
    m_smooth.x = 0.0f;
    m_smooth.y = 0.0f;
    m_smooth.z = 0.0f;
}

CInputCom::~CInputCom() {}

/* PSVECMag as an inline: its result is a temporary, which CW ranks below the named locals for f31 down (retail's
 * FPR order in get) */
static inline float VecMag(const Vec* v)
{
    return PSVECMag(v);
}

/* run from the ball: a fresh target when Think finds one, else the power decays; the stick eases toward the
 * target. Nothing is written while the ball is still (update() cleared x / y). */
void CInputCom::get(Data* data)
{
    Update();
    Vec d;
    PSVECSubtract(&m_ballPos, &m_self, &d);
    float dist = VecMag(&d);
    if (VecMag(&m_ballVel) <= 0.0f) {
        return;
    }
    m_fresh = Think(dist);
    float k = 0.02f;
    if (!m_fresh) {
        m_stick.y += -data->mag * k;
    } else {
        m_stick.y = 1.0f;
    }
    m_smooth.x += (m_target.x - m_smooth.x) / 54.0f;
    m_smooth.y += (m_target.y - m_smooth.y) / 54.0f;
    m_smooth.z += (m_target.z - m_smooth.z) / 54.0f;
    PSVECSubtract(&m_smooth, &m_self, &d);
    if (VecMag(&d) > 100.0f) {
        PSVECNormalize(&d, &d);
        float power = m_stick.y;
        PSVECScale(&d, &d, power);
        m_stick.x = d.x;
        m_stick.z = d.z;
    }
    data->x = m_stick.x;
    data->y = m_stick.z;
    data->mag = m_stick.y;
    m_timer += 1.0 / 60.0;
}

/* data_284: the arena margin by difficulty (non-const: .data) */
static float s_margin[4] = { 100.0f, 150.0f, 250.0f, 300.0f };

/* choose a point to run to, by which of self / ball is near the rim (bit 0 / bit 1); false when the ball is far
 * (> 500) or slow (< 0.05). The stage instance is fetched and not used (retail). */
bool CInputCom::Think(float dist)
{
    bool along;
    CStage* stage = CSingleton<CStage>::GetInstance();
    float arena = 600.0f;
    float centre;
    float edge = arena - s_margin[GetLevel()];
    Vec self = m_self;
    Vec ball = m_ballPos;
    int flags = 0;
    float selfDist = PSVECMag(&self);
    if (selfDist > edge) {
        flags |= 1;
    }
    float ballDist = PSVECMag(&ball);
    if (ballDist > edge) {
        flags |= 2;
    }
    float r = 100.0f * (3.0f * RND());
    float a = 10.0f * RND();
    if (dist > 500.0f) {
        return false;
    }
    if (m_speed < 0.05) {
        return false;
    }
    float mag = PSVECMag(&m_ballPos);
    centre = mag;
    switch (flags) {
    case 0:
        m_target = SidePoint(700.0f + r, 90.0f + a, true);
        break;
    case 1:
        m_target = SidePoint(600.0f + r, 90.0f + a, true);
        break;
    case 2:
        m_target = OppositePoint(700.0f + r);
        break;
    case 3:
        if (centre < 300.0f) {
            along = dist > 400.0f ? true : false;
            m_target = SidePoint(600.0f + r, 130.0f + a, along);
        } else {
            m_target = OppositePoint(700.0f + r);
        }
        break;
    }
    return true;
}

/* the point r from the ball, deg around Y from the ball's heading (alongVel) or from ball -> self; the other side
 * (deg + 180) when the path to it crosses the ball's line of motion (+-r) */
Vec CInputCom::SidePoint(float r, float deg, bool alongVel)
{
    Mtx m;
    Vec self = m_self;
    Vec ball = m_ballPos;
    Vec vel = m_ballVel;
    Vec result;
    Vec dir;
    if (alongVel != true) {
        PSVECSubtract(&self, &ball, &dir);
        PSVECNormalize(&dir, &dir);
    } else {
        dir = vel;
        PSVECNormalize(&dir, &dir);
    }
    Vec p = dir;
    PSMTXRotRad(m, 'Y', 0.017453292f * deg);
    PSMTXMultVecSR(m, &p, &p);
    PSVECScale(&p, &p, r);
    PSVECAdd(&p, &m_ballPos, &p);
    result = p;
    Vec b = m_ballVel;
    Vec e = m_ballPos;
    PSVECNormalize(&b, &b);
    PSVECScale(&b, &b, r);
    PSVECAdd(&e, &b, &e);
    bool c1 = SegCross(&m_self, &p, &m_ballPos, &e);
    b = m_ballVel;
    e = m_ballPos;
    PSVECNormalize(&b, &b);
    PSVECScale(&b, &b, -r);
    PSVECAdd(&e, &b, &e);
    bool c2 = SegCross(&m_self, &p, &m_ballPos, &e);
    if (c1 || c2) {
        p = dir;
        PSMTXRotRad(m, 'Y', 0.017453292f * (180.0f + deg));
        PSMTXMultVecSR(m, &p, &p);
        PSVECScale(&p, &p, r);
        PSVECAdd(&p, &m_ballPos, &p);
        result = p;
    }
    return result;
}

/* the point r beyond the centre, opposite the ball */
Vec CInputCom::OppositePoint(float r)
{
    Vec v = m_ballPos;
    PSVECNormalize(&v, &v);
    PSVECScale(&v, &v, -r);
    return v;
}

/* the XZ side of c relative to the line a -> b: 1, -1 or 0 (`this` unused) */
float CInputCom::Side(Vec a, Vec b, Vec c)
{
    float s = c.x * (a.z - b.z) + (a.x * (b.z - c.z) + b.x * (c.z - a.z));
    if (s > 0.0f) {
        return 1.0f;
    } else if (s < 0.0f) {
        return -1.0f;
    } else {
        return 0.0f;
    }
}

/* c and d on different sides (or on) the line a -> b. u8, not bool: retail converts the compare once here (clrlwi)
 * and SegCross tests the byte as is (a bool return adds a second clrlwi at both inlined sites) */
u8 CInputCom::Straddle(Vec a, Vec b, Vec c, Vec d)
{
    return 0.0f >= Side(c, a, b) * Side(d, a, b);
}

/* the XZ bounding-box helpers of SegCross (retail passes every value through its own temporaries) */
static inline float Max(float a, float b)
{
    return a > b ? a : b;
}

static inline float Min(float a, float b)
{
    return a < b ? a : b;
}

/* do the XZ segments a0-a1 and b0-b1 cross */
bool CInputCom::SegCross(const Vec* a0, const Vec* a1, const Vec* b0, const Vec* b1)
{
    if (Min(a0->x, a1->x) > Max(b0->x, b1->x)) {
        return false;
    }
    if (Min(a0->z, a1->z) > Max(b0->z, b1->z)) {
        return false;
    }
    if (Min(b0->x, b1->x) > Max(a0->x, a1->x)) {
        return false;
    }
    if (Min(b0->z, b1->z) > Max(a0->z, a1->z)) {
        return false;
    }
    return Straddle(*a0, *a1, *b0, *b1) && Straddle(*b0, *b1, *a0, *a1);
}

/* The list walks below: retail keeps more inline temporaries than CW has registers for (_savegpr_17), so several
 * results round-trip through stack slots; which ones depends on the exact inline shape, kept here as found:
 * begin() through TLinkList, end() through one free inline, a player's position as a functional-cast rvalue
 * `Vec(*p->GetPos())` (a temporary built through a register-held address), the ball as an inline's parameter. */
static inline CLinkNode* EndOf(ASet<CPlayer>* set)
{
    return set;
}

static inline Vec DeltaOf(CBall* ball)
{
    return ball->m_delta;
}

/* the ball's last motion (the zero Vec is util.h's, read at 9804; the zero arm is unreachable: owner only) */
static inline Vec BallVel(CPlayer* p)
{
    Vec zero = s_zeroVec;
    if (!p->m_isSolo) {
        return zero;
    } else {
        return DeltaOf(p->m_ball.get());
    }
}

static inline Vec MoveOf(CPlayer* p)
{
    return p->m_move;
}

/* a runner stunned by a Monty Mole (motion slot 5) */
static inline bool IsDown(CPlayer* p)
{
    return p->m_motion == 5 ? true : false;
}

/* the ball (its owner's position, speed ratio and motion) and this player's own position, XZ */
void CInputCom::Update()
{
    ASet<CPlayer>* set = ASet<CPlayer>::instance();
    CPlayer* p = set->begin();
    CLinkNode* end = EndOf(set);
    for (; p != end; p = p->next()) {
        if (p->m_isSolo) {
            m_ballPos = Vec(*p->GetPos());
            m_ballPos.y = 0.0f;
            m_speed = !p->m_isSolo ? 0.0f : p->m_ball.get()->GetSpeedRatio();
            if ((!p->m_isSolo ? 0.0f : p->m_ball.get()->GetSpeedRatio()) > 0.05f) {
                m_ballVel = BallVel(p);
            }
        } else if (m_idx == p->GetIdx()) {
            m_self = Vec(*p->GetPos());
            m_self.y = 0.0f;
        }
    }
}

CInputComSolo::CInputComSolo(int dif)
{
    int i;
    m_timer = 0.0f;
    m_target = 0;
    m_mode = 0;
    m_count = 0;
    m_data.level = dif;
    for (i = 0; i < NUM_RUNNER; i++) {
        m_out[i] = false;
        m_down[i] = false;
    }
}

/* data_2C4 / data_2D4 / data_2E8: the stick's turn rate, the retarget time (s; the 5th is never read) and the
 * speed ratio above which the nearest runner is chosen, by difficulty (non-const: .data) */
static float s_turn[4] = { 0.7f, 0.8f, 0.9f, 1.0f };
static float s_retarget[5] = { 10.0f, 8.0f, 3.0f, 2.0f, 3.0f };
static float s_speedThr[4] = { 0.3f, 0.4f, 0.4f, 0.5f };

void CInputComSolo::get(Data* data)
{
    Update();
    int dif = GetLevel();
    Vec dir;
    if (m_mode != 2) {
        ChooseTarget();
        Vec v = m_vel[m_target];
        float mag = PSVECMag(&v);
        if (mag <= 0.0f || m_mode == 0) {
            Vec* pos = &m_pos[m_target];
            PSVECSubtract(pos, &m_self, &dir);
        } else {
            Vec p = m_pos[m_target];
            PSVECNormalize(&v, &v);
            PSVECScale(&v, &v, 500.0f);
            PSVECAdd(&v, &p, &p);
            PSVECSubtract(&p, &m_self, &dir);
        }
    } else {
        Vec c;
        c.x = 0.0f;
        c.y = 0.0f;
        c.z = 0.0f;
        PSVECSubtract(&c, &m_self, &dir);
        float mag = PSVECMag(&dir);
        if (mag < 100.0f) {
            m_mode = frand() & 1;
        }
    }
    PSVECNormalize(&dir, &dir);
    data->x += (dir.x - data->x) * s_turn[dif];
    data->y += (dir.z - data->y) * s_turn[dif];
    data->mag = 1.0f;
    m_timer += 1.0 / 60.0;
}

/* a stunned runner first (difficulty > 1); else keep the target for s_retarget[dif] s while it is not caught;
 * else the nearest (fast ball) or farthest free runner; every other pick returns to the centre */
void CInputComSolo::ChooseTarget()
{
    int dif = GetLevel();
    int i;
    for (i = 0; i < NUM_RUNNER; i++) {
        if (!m_out[i] && m_down[i] && dif > 1) {
            m_target = i;
            m_mode = 1;
            return;
        }
    }
    if (m_timer < s_retarget[dif] && !m_out[m_target]) {
        return;
    }
    float nearest = 1000.0f;
    float farthest = 0.0f;
    for (i = 0; i < NUM_RUNNER; i++) {
        if (!m_out[i]) {
            Vec d;
            PSVECSubtract(&m_self, &m_pos[i], &d);
            float mag = PSVECMag(&d);
            float dist = mag;
            if (m_speed > s_speedThr[dif]) {
                if (dist < nearest) {
                    nearest = dist;
                    m_target = i;
                }
            } else if (dist > farthest) {
                farthest = dist;
                m_target = i;
            }
        }
    }
    if ((u32)m_count & 1) {
        m_mode = 2;
    } else {
        m_mode = frand() & 1;
    }
    m_count++;
    m_timer = 0.0f;
}

/* own ball position / speed, and every runner's position, motion, caught and stunned flags */
void CInputComSolo::Update()
{
    ASet<CPlayer>* set = ASet<CPlayer>::instance();
    CPlayer* p = set->begin();
    CLinkNode* end = EndOf(set);
    int i = 0;
    for (; p != end; p = p->next()) {
        if (p->m_isSolo) {
            m_self = Vec(*p->GetPos());
            m_self.y = 0.0f;
            m_speed = !p->m_isSolo ? 0.0f : p->m_ball.get()->GetSpeedRatio();
        } else {
            m_pos[i] = Vec(*p->GetPos());
            m_pos[i].y = 0.0f;
            m_vel[i] = MoveOf(p);
            m_out[i] = p->m_out;
            m_down[i] = IsDown(p);
            i++;
        }
    }
}

} // namespace m517

template <> ASet<m517::CPlayer>* ASet<m517::CPlayer>::sm_ptr = 0;
