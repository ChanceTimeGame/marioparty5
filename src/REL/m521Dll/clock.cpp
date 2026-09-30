/* clock.cpp -- m521::CClock (clock.h), the first unit in link order. The notes are at the end of this file: the
 * asserts must stay on clock.cpp:277 / :535 (the `line padding` markers, test/fixlines.py). */
#include "REL/m521Dll/clock.h"
#include "REL/m521Dll/gamemaster.h"
#include "REL/mgcpp/assert.h"
#include "REL/mgcpp/gameobject.h"

namespace m521 {

/* abs: the retail macro (RotateTo recomputes the difference) and an inline taking its argument once (GetTurnDir) */
#define ABS(x) ((x) < 0 ? -(x) : (x))
inline float AbsF(float x) { return x < 0.0f ? -x : x; }
/* SubAngle's integer angle helpers (m579 player.h's); the ctor's TransApply (its arguments go to registers first) */
inline int DegToAngle(float deg) { return (65536.0 / 360.0) * deg; }
inline float AngleToDeg(int angle) { return (360.0 / 65536.0) * angle; }
inline int AngleSub(int a, int b) { return ((a - b - 0x8000) & 0xFFFF) - 0x8000; }
inline void TransApply(Mtx m, float x, float y, float z) { PSMTXTransApply(m, m, x, y, z); }
inline float Dot(const Vec* a, const Vec* b) { return PSVECDotProduct(a, b); }

/* lbl_1_rodata_10: the two paused-motion "gear" models per team clock ([id][0] goes to m_gear[1]) */
const u32 s_gearTbl[2][2] = { { 0x4F000A, 0x4F000B }, { 0x4F000C, 0x4F000D } };
/* lbl_1_rodata_20: the hour / minute hand models per clock */
const u32 s_handTbl[3][2] = { { 0x4F0005, 0x4F0004 }, { 0x4F0009, 0x4F0008 }, { 0x4F0007, 0x4F0006 } };

bool CClock::IsDone() const /* fn_1_0 */
{
    return m_locked[0] && m_locked[1];
}

CClock::CClock(int id, const Vec* pos) : m_id(id), m_pos(*pos)
{
    Mtx minute, hour, rot;
    if (id >= 0 || id <= 1) {
        CModel* g0 = new CModel(s_gearTbl[id][0]);
        CModel* g1 = new CModel(s_gearTbl[id][1]);
        g0->setAttr(HU3D_MOTATTR_PAUSE);
        g1->setAttr(HU3D_MOTATTR_PAUSE);
        Hu3DModelShadowMapSet(g0->id());
        Hu3DModelShadowMapSet(g1->id());
        m_gear[1].reset(g0);
        m_gear[0].reset(g1);
    }
    if (id == 2) {
        PSMTXTrans(hour, 0.0f, -8.0f, 8.5f);
        PSMTXTrans(minute, 0.0f, 0.0f, 8.5f);
    } else {
        PSMTXTrans(hour, 0.0f, -7.235f, 0.0f);
        PSMTXTrans(minute, 0.0f, 7.545f, 0.0f);
    }
    if (id == 2) {
        PSMTXRotRad(rot, 'X', 0.6981317f);
        PSMTXConcat(rot, hour, hour);
        PSMTXConcat(rot, minute, minute);
    }
    TransApply(hour, pos->x, pos->y, pos->z);
    TransApply(minute, pos->x, pos->y, pos->z);
    m_hand[0].reset(new CClockHand(s_handTbl[id][0], hour));
    m_hand[1].reset(new CClockHand(s_handTbl[id][1], minute));
    SetTime(6, 0);
    SetTarget(6, 0);
    SaveTarget();
    m_speed = 0.0f;
    m_state = 0;
    Lock();
    m_turn[0] = 0.0f;
    m_turn[1] = 0.0f;
    m_se[0] = -1;
    m_se[1] = -1;
    m_frame = 0;
    m_lastPush[0] = -1;
    m_lastPush[1] = -1;
}

/* fn_1_5DC: the member arrays only (the looping tick SEs are not stopped: retail) */
CClock::~CClock() {}

/* fn_1_658: the hand frame's X axis */
void CClock::GetHandPos(Vec* out, int hand)
{
    MtxPtr m = m_hand[hand]->GetMtx();
    out->x = m[0][0];
    out->y = m[1][0];
    out->z = m[2][0];
}

void CClock::GetHandPoint(Vec* out, int hand, float t, float x)
{
    MtxPtr m = NULL;
    switch (hand) {
    case 0:
        t *= -250.0f;
        m = m_hand[0]->GetMtx();
        break;
    case 1:
        t *= -330.0f;
        m = m_hand[1]->GetMtx();
        break;
    }
    out->x = x;
    out->y = 0.0f;
    out->z = t;
    PSMTXMultVec(m, out, out);
}

void CClock::Spin() /* fn_1_7A0 */
{
    m_speed = 30.0f;
    m_state = 1;
    Unlock();
}

bool CClock::IsIdle() const /* fn_1_7E8 */
{
    return m_state == 0;
}

void CClock::SetTime(int h, int m) /* fn_1_7F8 */
{
    m_time = h * 60 + m;
    m_angle[0] = -360.0f * m_time / 720.0f;
    m_angle[1] = -360.0f * m_time / 60.0f;
    m_hold[0] = 0;
    m_hold[1] = 0;
}

void CClock::SetTarget(int h, int m) /* fn_1_894 */
{
    float t = h * 60 + m;
    m_target[0] = -360.0f * t / 720.0f;
    m_target[1] = -360.0f * t / 60.0f;
}

void CClock::SaveTarget() /* fn_1_924 */
{
    m_prevTarget[0] = m_target[0];
    m_prevTarget[1] = m_target[1];
}

/* fn_1_938 (unreferenced: inlined everywhere) */
float Wrap(float a, float m)
{
    a = fmod(a, m);
    if (a < 0.0f) a += m;
    return a;
}

/* fn_1_9A8 (unreferenced: inlined in Rotate) */
bool RotateTo(float* a, float target, float step)
{
    float next = Wrap(*a + step, 360.0f);
    target = Wrap(target, 360.0f);
    bool hit = ABS(next - target) < ABS(step);
    *a = hit ? target : next;
    return hit;
}

/* RotateTo as Rotate inlines it: the difference is evaluated once there (not emitted out of line) */
inline bool RotateStep(float* a, float target, float step)
{
    float next = Wrap(*a + step, 360.0f);
    target = Wrap(target, 360.0f);
    float diff = next - target;
    bool hit = ABS(diff) < ABS(step);
    *a = hit ? target : next;
    return hit;
}

/* fn_1_B88 (unreferenced: inlined in Update) */
float AngleToMotTime(float deg)
{
    float t = Wrap(2.0f * deg, 720.0f) / 720.0f;
    return 59.0f * t;
}

void CClock::Update() /* fn_1_C4C */
{
    UpdateState();
    m_hand[1]->SetAngle(m_angle[1]);
    m_hand[0]->SetAngle(m_angle[0]);
    CModel* gear = m_gear[1].get();
    if (gear) {
        HU3DMODELID id = gear->id();
        Hu3DMotionTimeSet(id, AngleToMotTime(m_turn[1]));
    }
    gear = m_gear[0].get();
    if (gear) {
        HU3DMODELID id = gear->id();
        Hu3DMotionTimeSet(id, AngleToMotTime(m_turn[0]));
    }
    if (m_seTimer[0].Tick()) StopTickSe(0);
    if (m_seTimer[1].Tick()) StopTickSe(1);
    m_hold[0]--;
    m_hold[1]--;
    m_frame++;
}

void CClock::UpdateState() /* fn_1_F20 */
{
    switch (m_state) {
    case 0:
        break;
    case 1:
        m_angle[0] -= m_speed;
        m_angle[1] -= m_speed;
        m_speed -= 1.0 / 6.0;
        if (m_speed < 10.0f) m_state++;
        break;
    case 2:
        Rotate(0, -m_speed);
        Rotate(1, -m_speed);
        if (IsDone()) m_state = 0;
        break;
    }
}

/* fn_1_1034 (unreferenced: inlined) the hand's half-width profile along it */
float HandTaper(float t)
{
    return 0.2 + 0.8f * sin(M_PI * t);
}

/* fn_1_1090 (unreferenced: inlined in PushOut / HitHands). A hand is a lens-shaped slab 30.000002 high. */
bool HitHand(Vec* axis, float* push, const Vec* p, Mtx inv, float len, float w)
{
    Vec l;
    PSMTXMultVec(inv, p, &l);
    if (l.z > 0.0f || l.z < -len) return false;
    if (l.y > 30.000002f) return false;
    w *= HandTaper(-l.z / len);
    float x = l.x;
    if (ABS(x) > w) return false;
    *push = (l.x < 0.0f ? -w : w) - l.x;
    axis->x = inv[0][0];
    axis->y = inv[0][1];
    axis->z = inv[0][2];
    return true;
}

/* fn_1_1288 (unreferenced: inlined in CrossHands) */
bool CrossHand(const Vec* a, const Vec* b, Mtx inv, float len)
{
    Vec la, lb;
    PSMTXMultVec(inv, a, &la);
    PSMTXMultVec(inv, b, &lb);
    if (la.z > 0.0f || la.z < -len) return false;
    if (lb.z > 0.0f || lb.z < -len) return false;
    return la.x * lb.x < 0.0f;
}

bool CClock::IsLocked(int hand) const /* fn_1_1370 */
{
    switch (hand) {
    case 0:
    case 1:
        return m_locked[hand];
    }
    return false;
}

/* fn_1_139C (masked 4: fp regs). 1 = locked after the move, else -1; a hand pushed > 20 frames unlocks. */
int CClock::Rotate(int id, float delta)
{
    /* line padding (Rotate) */

    assert(id >= 0 && id < 2);
    int ret = -1;
    float old = m_angle[id];
    if (!m_locked[id]) {
        if (m_id == 2 || s_inputOn) {
            m_locked[id] = RotateStep(&m_angle[id], m_target[id], delta);
        } else {
            m_angle[id] = Wrap(m_angle[id] + delta, 360.0f);
        }
        if (m_locked[id]) {
            switch (m_id) {
            case 0:
                StopTickSe(0);
                HuAudFXPlay(0x738);
                break;
            case 1:
                StopTickSe(1);
                HuAudFXPlay(0x739);
                break;
            }
        } else {
            PlayTickSe(id);
        }
        ret = m_locked[id] ? 1 : -1;
    } else if (m_lastPush[id] != m_frame) {
        m_lastPush[id] = m_frame;
        if (m_hold[id] < 0) m_hold[id] = 0;
        m_hold[id] += 2;
        if (m_hold[id] > 40) {
            m_hold[id] = 0;
            m_locked[id] = false;
            m_angle[id] += 2.0f * delta;
        }
    }
    m_turn[id] += m_angle[id] - old;
    return ret;
}

/* PushOut reaches HitHand one inline level deeper (retail's stack slots: AddScaled's temps above HitHand's; a guess
 * at the shape, not the name) */
inline bool HitHandW(Vec* axis, float* push, const Vec* p, Mtx inv, float len, float w)
{
    return HitHand(axis, push, p, inv, len, w);
}

/* PushOut's push step (the pointer comes back through a stack slot in retail) */
inline Vec* ScaleVec(Vec* out, const Vec* v, float s)
{
    PSVECScale(v, out, s);
    return out;
}
inline void AddScaled(Vec* p, const Vec* v, float s)
{
    Vec d;
    Vec* pd = ScaleVec(&d, v, s);
    PSVECAdd(pd, p, p);
}

/* fn_1_1824 (masked 0: fp registers). Ten relaxation passes; always false (retail). */
bool CClock::PushOut(Vec* p)
{
    CClockHand* minute = m_hand[1].get();
    CClockHand* hour = m_hand[0].get();
    Mtx invM;
    Mtx invH;
    MtxPtr mm = minute->GetMtx();
    PSMTXInverse(mm, invM);
    MtxPtr hm = hour->GetMtx();
    PSMTXInverse(hm, invH);
    for (int i = 0; i < 10; i++) {
        Vec axis;
        float push;
        if (HitHandW(&axis, &push, p, invM, 330.0f, 70.0f)) AddScaled(p, &axis, push);
        if (HitHandW(&axis, &push, p, invH, 250.0f, 80.0f)) AddScaled(p, &axis, push);
    }
    return false;
}

/* fn_1_1CA0 (masked 0: two fp registers swapped). 0 hour, 1 minute, -1 none. */
int CClock::HitHands(const Vec* p, Vec* axis, float* push)
{
    CClockHand* minute = m_hand[1].get();
    CClockHand* hour = m_hand[0].get();
    Mtx invM;
    Mtx invH;
    MtxPtr mm = minute->GetMtx();
    PSMTXInverse(mm, invM);
    MtxPtr hm = hour->GetMtx();
    PSMTXInverse(hm, invH);
    if (HitHand(axis, push, p, invH, 250.0f, 80.0f)) return 0;
    if (HitHand(axis, push, p, invM, 330.0f, 70.0f)) return 1;
    return -1;
}

/* fn_1_20B8 (unreferenced) */
int CClock::CrossHands(const Vec* a, const Vec* b)
{
    CClockHand* minute = m_hand[1].get();
    CClockHand* hour = m_hand[0].get();
    Mtx invM;
    Mtx invH;
    MtxPtr mm = minute->GetMtx();
    PSMTXInverse(mm, invM);
    MtxPtr hm = hour->GetMtx();
    PSMTXInverse(hm, invH);
    if (CrossHand(a, b, invH, 250.0f)) return 0;
    if (CrossHand(a, b, invM, 330.0f)) return 1;
    return -1;
}

/* fn_1_22BC (unreferenced) */
int CClock::GetFreeHand(int prefer) const
{
    if (prefer == 0) {
        if (!m_locked[0]) return 0;
        if (!m_locked[1]) return 1;
    } else {
        if (!m_locked[1]) return 1;
        if (!m_locked[0]) return 0;
    }
    return -1;
}

/* fn_1_231C (unreferenced: inlined) a - b in degrees, wrapped through s16 */
float SubAngle(float a, float b)
{
    return AngleToDeg(AngleSub(DegToAngle(a), DegToAngle(b)));
}

/* fn_1_23D8 (unreferenced: inlined) */
Vec* AngleToVec(Vec* out, float deg)
{
    out->x = cos(M_PI * deg / 180.0);
    out->y = sin(M_PI * deg / 180.0);
    out->z = 0.0f;
    return out;
}
/* ---- clock region F6 (.text 0x2480..0x48FC: IsBlocked .. the weak tail; F1 owns 0x0000..0x2480 above) ---- */
bool CClock::IsBlocked(int hand) /* fn_1_2480 */
{
    return IsApproaching(hand, GetTurnDir(hand));
}

bool CClock::AreHandsWithin(float deg) /* fn_1_24D0 */
{
    Vec a;
    Vec b;
    AngleToVec(&a, m_angle[0]);
    AngleToVec(&b, m_angle[1]);
    float dot = PSVECDotProduct(&a, &b);
    return dot > cos(M_PI * (deg / 2.0f) / 180.0);
}

/* fn_1_2658. DRAFT (208 insns, ours 210, masked 14: the dot-product return copies): turning `hand` by `dir` degrees
 * brings it closer to the other hand */
bool CClock::IsApproaching(int hand, int dir)
{
    Vec v, o;
    AngleToVec(&o, m_angle[hand ^ 1]);
    float c = Dot(AngleToVec(&v, m_angle[hand]), &o);
    AngleToVec(&o, m_angle[hand ^ 1]);
    float c2 = Dot(AngleToVec(&v, m_angle[hand] + dir), &o);
    return c2 > c && c > cos(M_PI / 4);
}

bool CClock::IsTargetTooNear(float deg) /* fn_1_2998 */
{
    float th = cos(M_PI * deg / 180.0);
    Vec t[2];
    Vec p[2];
    AngleToVec(&t[0], m_target[0]);
    AngleToVec(&t[1], m_target[1]);
    AngleToVec(&p[0], m_prevTarget[0]);
    AngleToVec(&p[1], m_prevTarget[1]);
    return Dot(&t[0], &t[1]) > th || Dot(&t[0], &p[0]) > th ||
           Dot(&t[1], &p[1]) > th;
}

bool CClock::IsHandNearTarget(float deg) /* fn_1_2C98 */
{
    float th = cos(M_PI * deg / 180.0);
    Vec t[2];
    Vec v;
    AngleToVec(&t[0], m_target[0]);
    AngleToVec(&t[1], m_target[1]);
    for (int i = 0; i < 2; i++) {
        AngleToVec(&v, m_angle[i]);
        if (Dot(&t[0], &v) > th) return true;
        if (Dot(&t[1], &v) > th) return true;
    }
    return false;
}

/* fn_1_2EFC. DRAFT (219 insns, ours 220, masked 23: SubAngle inline spills): the sign of the shortest turn to the
 * target, reversed when the other
 * hand is in the way */
int CClock::GetTurnDir(int hand)
{
    float d = SubAngle(m_target[hand], m_angle[hand]);
    float o = SubAngle(m_angle[hand ^ 1], m_angle[hand]);
    if (d * o >= 0.0f) {
        const float t = d;
        if (ABS(t) > ABS(o)) d *= -1.0f;
    }
    return 0.0f == d ? 0.0f : (d < 0.0f ? -1.0f : 1.0f);
}

/* fn_1_3268 (unreferenced; masked 0: fp register numbering) */
float CClock::GetTurnDist(int hand)
{
    float d = SubAngle(m_target[hand], m_angle[hand]);
    float o = SubAngle(m_angle[hand ^ 1], m_angle[hand]);
    if (d * o < 0.0f || ABS(d) < ABS(o)) return ABS(d);
    return 360.0f - ABS(d);
}

/* fn_1_35B0 (unreferenced). STUB-level DRAFT (828 insns, ours 766: retail spills the deeper inlines to the stack):
 * four inlined GetTurnDist; both sums are the same
 * (retail compares dist(0) + dist(1) with dist(1) + dist(0)) */
int CClock::ChooseHand()
{
    if (m_locked[1] && m_locked[0]) return -1;
    if (!m_locked[0] && m_locked[1]) return 0;
    if (!m_locked[1] && m_locked[0]) return 1;
    float a = GetTurnDist(0);
    a += GetTurnDist(1);
    float b = GetTurnDist(1);
    b += GetTurnDist(0);
    return a <= b ? 0 : 1;
}

void CClock::Lock() /* fn_1_42A0 */
{
    m_locked[0] = true;
    m_locked[1] = true;
}

void CClock::Unlock() /* fn_1_42B4 */
{
    m_locked[0] = false;
    m_locked[1] = false;
}

/* fn_1_42C8. DRAFT (306 insns, at count, masked 36: stack slots / the inlined GetTurnDir): p is on the side of the
 * hand that pushes it toward its target */
bool CClock::IsPushSide(const Vec* p, int id)
{
    /* line padding (IsPushSide) */










    assert(id >= 0 && id < 2);
    Mtx inv;
    Vec l;
    CClockHand* hand = m_hand[id].get();
    MtxPtr m = hand->GetMtx();
    PSMTXInverse(m, inv);
    PSMTXMultVec(inv, p, &l);
    if (l.z > 0.0f) return false;
    float x = l.x;
    if (ABS(x) > 220.00000000000003) return false;
    return l.x * GetTurnDir(id) >= 0.0f ? true : false;
}

/* lbl_1_rodata_108: the looping tick SE per team clock and hand */
const u32 s_seTbl[2][2] = { { 0x734, 0x736 }, { 0x735, 0x737 } };

void CClock::PlayTickSe(int hand) /* fn_1_4790 */
{
    if (m_id < 2 && CGameObject::GetUpdateMode() == 2) {
        if (m_se[hand] != -1) {
            m_seTimer[hand].n = 5;
        } else {
            m_se[hand] = HuAudFXPlay(s_seTbl[m_id][hand]);
            m_seTimer[hand].n = 5;
        }
    }
}

void CClock::StopTickSe(int hand) /* fn_1_4844 */
{
    if (m_id < 2 && m_se[hand] != -1) {
        HuAudFXStop(m_se[hand]);
        m_se[hand] = -1;
    }
}

} // namespace m521

template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer = 0;

