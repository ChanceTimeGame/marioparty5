#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is player.o's .bss AA8 / __sinit */
#include "REL/mgcpp/gameobject.h"
#include "REL/m521Dll/player.h"
#include "REL/m521Dll/clock.h"
#include "REL/m521Dll/gamemaster.h"
extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}

namespace m521 {

static float s_groundY = 20.0f; /* lbl_1_data_680: the floor (non-const: retail keeps it in .data; never written) */

/* Vec setter with DOUBLE components (m539 / m501): the non-constant components go out `frsp; stfs` */
static inline Vec& SetVec(Vec* v, double x, double y, double z) { v->x = x; v->y = y; v->z = z; return *v; }

/* degrees <-> 16-bit binary angle and the wrapped difference (m579 / m509 player.h) */
inline int DegToAngle(float deg) { return (65536.0 / 360.0) * deg; }
inline float AngleToDeg(int angle) { return (360.0 / 65536.0) * angle; }
inline int AngleSub(int a, int b) { return ((a - b - 0x8000) & 0xFFFF) - 0x8000; }

/* fn_1_15298 (= m532 / m522 GetPan) */
s16 GetPan(Vec* pos)
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
    return result;
}

/* fn_1_15338 (= m579 / m509 SubAngle) */
float CPlayer::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

/* fn_1_153F0 (= m579 / m509 SubAngleMax) */
float CPlayer::SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

/* fn_1_15554 */
bool CPlayer::IsMove(const CDriver::INFO& info) { return info.mag >= 0.7f; }

static const float s_startX[4] = { -600.0f, -300.0f, 300.0f, 600.0f }; /* lbl_1_rodata_33C: start x by slot */

/* fn_1_15578 (y first: retail) */
void CPlayer::ResetPos() { m_sphere.pos.y = s_groundY; m_sphere.pos.x = s_startX[m_slot]; m_sphere.pos.z = 0.0f; }

/* fn_1_155B8 */
CDriver* CPlayer::CreateDriver(int pl, CPlayer* p)
{
    if (GwPlayerConf[pl].type != 0) {
        return new CDriverAsAI(p);
    }
    return new CDriverAsPad(pl);
}

/* line padding (CPlayer ctor): the assert below is retail's player.cpp:119 */















/* fn_1_15664 (291 insns, masked 0): lv = (dif + 1) / 4.0f (the fmul after the conversion), the driver through a local */
CPlayer::CPlayer(int pl, int slot)
    : m_driver(CreateDriver(pl, this)), m_slot(slot), m_unk38(0), m_stateTimer(0), m_stunTimer(0), m_landTimer(0),
      m_idleDelay(0), m_mot_id(), m_model(new CModel(GwPlayerConf[pl].charNo, 2))
{
    insertBack(ASet<CPlayer>::instance());
    m_sphere.r = 50.0f;
    m_pl = pl;
    m_charNo = GwPlayerConf[pl].charNo;
    m_curMotion = -1;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    AddMotion(0x8C0000); /* 0 idle */
    AddMotion(0x8C0036); /* 1 (never used) */
    AddMotion(0x8C0001); /* 2 walk */
    AddMotion(0x8C0075); /* 3 push */
    AddMotion(0x8C0006); /* 4 PlayMotion4 */
    AddMotion(0x8C0031); /* 5 PlayMotion5 */
    AddMotion(0x8C0003); /* 6 jump */
    AddMotion(0x8C0004); /* 7 land */
    AddMotion(0x8C0030); /* 8 win */
    AddMotion(0x8C002E); /* 9 lose */
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model->id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
    ResetPos();
    setProc(&CPlayer::procStart);
    SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
    SetVec(&m_force, 0.0f, 0.0f, 0.0f);
    m_state = 0;
    m_yaw = 0.0f;
    m_targetYaw = 0.0f;
    m_onStand = false;
    float lv = (GwPlayerConf[pl].dif + 1) / 4.0f;
    CDriver* driver = m_driver.get();
    driver->m_info.lv = lv;
    m_result = -1;
}

/* inline helpers whose extra levels are retail's register hops: CountDown (the timers +0x3C..+0x48, true on the
 * frame the count reaches 0), SetTimer (SetState case 4: the value through a stack slot), GetInfo (the driver's stick / button state: auto_ptr get, then &m_info) */
static inline bool CountDown(int& n) { bool done = false; if (n > 0 && --n == 0) { done = true; } return done; }
static inline void SetTimer(int& t, int n) { int v = n; t = v; }
static inline float VecMag(Vec* v) { return PSVECMag(v); }
static inline float VecDot(Vec* a, Vec* b) { return PSVECDotProduct(a, b); }
static inline float ClampF(float v, float min, float max) { if (v < min) { return min; } else if (v > max) { return max; } else { return v; } }
static inline Vec* ClockPos(CClock* clock) { return &clock->m_pos; }
static inline CDriver::INFO& GetInfo(CDriver* driver) { return driver->m_info; }

/* fn_1_15D68 */
bool CPlayer::IsCom() const
{
    return GwPlayerConf[m_pl].type != 0;
}

/* fn_1_15D94 (the result is tested by an empty if: retail) */
void CPlayer::Collide(CPlayer* a, CPlayer* b)
{
    if (!HitPushSphere(&a->m_sphere, &b->m_sphere, 0.5f, 1.001f)) {
        return;
    }
}

/* fn_1_15DF0 (push_back = insert(end, 1, x)) */
void CPlayer::AddMotion(u32 dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

/* lbl_1_data_6F0: the stand objects the players stand on at the result (s_standR slots 0/1, s_standB 2/3) */
static const char* s_standObj[4] = { "cyara1", "cyara2", "cyara3", "cyara4" };

/* fn_1_15E68 */
void CPlayer::GetStandMtx(int slot, Mtx out)
{
    HU3DMODELID id = ((slot & 2) == 0 ? s_standR.get() : s_standB.get())->id();
    Hu3DModelObjMtxGet(id, (char*)s_standObj[slot & 3], out);
}

/* fn_1_15F04 DRAFT (338 insns; masked 10: GetPan-inline pan/result registers swapped vs the out-of-line copy,
 * the SubAngleMax float chain and stun / CountDown registers) */
void CPlayer::Update()
{
    CharModelVoicePanSet(m_charNo, GetPan(&m_sphere.pos));
    if (m_result >= 0 && !IsAirborne()) {
        int stun = 156; /* retail: a named local (li r23) */
        m_stunTimer = stun;
        switch (m_result) {
        case 0:
            CharMotionVoiceOnSet(m_charNo, 0x30, FALSE);
            CharWinLoseVoicePlay(m_charNo, 0x8C0030, 0x1FB);
            SetMotion(8, true);
            SetState(6);
            break;
        case 1:
            SetMotion(9, true);
            SetState(6);
            break;
        }
        m_result = -1;
    }
    if (m_proc) {
        (this->*m_proc)();
    }
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, 13.666667f);
    Physics();
    Clamp();
    GetClock()->PushOut(&m_sphere.pos);
    if (!m_onStand) {
        Vec rot;
        SetVec(&rot, 0.0f, m_yaw, 0.0f);
        m_model->setRot(&rot);
        m_model->setPos(&m_sphere.pos);
    } else {
        Vec zero = { 0.0f, 0.0f, 0.0f };
        m_model->setRot(&zero);
        m_model->setPos(&zero);
        Mtx* mtx = m_model->getMatrix();
        GetStandMtx(m_slot, *mtx);
        if (GwPlayerConf[m_pl].charNo == 6) {
            Mtx rotY;
            PSMTXRotRad(rotY, 'Y', 0.43633232f);
            PSMTXTransApply(*mtx, *mtx, -20.0f, 0.0f, -50.0f);
            PSMTXConcat(*mtx, rotY, *mtx);
        }
    }
    CountDown(m_stateTimer);
}

/* fn_1_1644C (humans only) */
void CPlayer::Vibrate(int kind)
{
    int pl = m_pl;
    if (GwPlayerConf[pl].type == 0) {
        switch (kind) {
        case 0:
            omVibrate(pl, 12, 6, 6);
            break;
        case 1:
            omVibrate(pl, 12, 4, 2);
            break;
        case 2:
            omVibrate(pl, 12, 12, 0);
            break;
        }
    }
}

/* fn_1_1650C */
CClock* CPlayer::GetClock() const
{
    return m_slot < 2 ? s_clockR : s_clockB;
}

/* fn_1_1654C */
void CPlayer::SetMotion(int idx, bool once)
{
    HU3DMODELID id = m_model->id(); /* retail: dead */
    s16 mot = m_mot_id[idx];
    if (m_curMotion != idx) {
        CharMotionShiftSet(m_charNo, mot, 0.0f, 18.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_curMotion = idx;
        switch (idx) {
        case 4:
            break;
        case 5:
            if (s_draw) {
                CharWinLoseVoicePlay(m_charNo, 0x8C0031, 0x200);
            }
            break;
        }
    }
}

/* fn_1_16648 */
void CPlayer::procStart()
{
    SetMotion(0, false);
    setProc(&CPlayer::procMain);
}

/* fn_1_16720: the floor, the clock's pivot sphere, the ring r <= 320 around the pivot */
void CPlayer::Clamp()
{
    if (m_sphere.pos.y < s_groundY) {
        m_sphere.pos.y = s_groundY;
        m_vel.y = 0.0f;
    }
    Vec center;
    center.x = m_slot < 2 ? -450 : 450;
    center.y = m_sphere.pos.y;
    center.z = 0.0f;
    CSphere pivot(center, 30.000002f);
    HitPushSphere(&pivot, &m_sphere, 0.0f, 1.0f);
    Vec d;
    PSVECSubtract(&m_sphere.pos, &center, &d);
    float len = VecMag(&d);
    if (!(len < 320.0f)) {
        PSVECScale(&d, &d, 1.0f + (320.0f - len) / len);
        PSVECAdd(&center, &d, &m_sphere.pos);
    }
}

/* fn_1_168C0 (196 insns): gravity, the midpoint step, the push on the hand */
void CPlayer::Physics()
{
    m_force.y += -3.3333333333333335;
    Vec old;
    old.x = m_vel.x;
    old.y = m_vel.y;
    old.z = m_vel.z;
    PSVECAdd(&m_force, &m_vel, &m_vel);
    SetVec(&m_force, 0.0f, 0.0f, 0.0f);
    PSVECAdd(&m_vel, &old, &old);
    PSVECScale(&old, &old, 0.5f);
    PSVECAdd(&old, &m_sphere.pos, &m_sphere.pos);
    if (m_state == 5) {
        Vec axis;
        float push;
        int hand = m_pushHand = GetClock()->HitHands(&m_sphere.pos, &axis, &push);
        if (hand < 0) {
            SetState(1);
        } else {
            if (GetClockDist() >= 328.0f) {
                float yaw;
                float off = 6.0f;
                if (push < 0.0f) {
                    yaw = off + HuAtan(axis.x, axis.z);
                } else {
                    yaw = HuAtan(-axis.x, -axis.z) - off;
                }
                m_yaw = yaw;
            }
            int locked = GetClock()->Rotate(hand, ClampF(push, -0.6666667f, 0.6666667f));
            if (locked == 1) {
                Vibrate(1);
            }
        }
    }
}

/* fn_1_16BD0 */
float CPlayer::GetClockDist() const
{
    Vec d;
    Vec* pos = ClockPos(GetClock());
    PSVECSubtract(pos, &m_sphere.pos, &d);
    return PSVECMag(&d);
}

/* fn_1_16C54 (209 insns; jump table data_70C) */
void CPlayer::SetState(int state)
{
    int timer = 150; /* retail: a named local (li r21) */
    m_stateTimer = timer;
    switch (state) {
    case 0:
        m_idleDelay = 1;
        break;
    case 1:
        SetMotion(2, false);
        break;
    case 2: {
        SetMotion(6, true);
        m_force.y += 50.0;
        CDriver::INFO& info = GetInfo(m_driver.get());
        m_force.x += 1.2f * info.x;
        m_force.z += 1.2f * info.y;
        break;
    }
    case 3:
        break;
    case 4: {
        SetMotion(7, true);
        SetTimer(m_landTimer, 18);
        break;
    }
    case 5:
        SetMotion(3, false);
        break;
    case 6:
        SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
        break;
    }
    m_state = state;
    m_stateTime = 0;
}

/* fn_1_16F98 (masked 0: CountDown's bool and the SetMotion model pointer take r29 / r28 swapped) */
void CPlayer::stateIdle()
{
    SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
    CDriver::INFO& info = GetInfo(m_driver.get());
    if (info.btn) {
        SetState(2);
    } else if (IsMove(info)) {
        SetState(1);
    } else if (CountDown(m_idleDelay)) {
        SetMotion(0, false);
    }
}

/* fn_1_170F8: a hand in front of the player (|dot(axis, facing)| > 0.707) starts the push */
void CPlayer::stateWalk()
{
    if (!Move()) {
        Vec axis;
        float push;
        int hand = GetClock()->HitHands(&m_sphere.pos, &axis, &push);
        if (hand >= 0) {
            Vec dir;
            GetDir(&dir);
            float dot = PSVECDotProduct(&axis, &dir);
            if ((dot < 0.0f ? -dot : dot) > 0.707f) {
                SetState(5);
                return;
            }
        }
    }
}

/* fn_1_17218: A -> jump, no stick -> idle (true: the state changed); else walk along the facing */
bool CPlayer::Move()
{
    CDriver::INFO& info = GetInfo(m_driver.get());
    if (info.btn) {
        SetState(2);
        return true;
    }
    if (!IsMove(info)) {
        SetState(0);
        return true;
    }
    m_targetYaw = HuAtan(info.x, info.y);
    Vec dir;
    GetDir(&dir);
    Vec stick;
    SetVec(&stick, info.x, 0.0f, info.y);
    float dot = VecDot(&dir, &stick);
    if (dot > 0.0f) {
        float speed = dot * (6.666667f * info.mag);
        PSVECScale(&dir, &m_vel, speed);
    }
    return false;
}

/* fn_1_173B8 */
void CPlayer::statePush()
{
    if (Move()) {
        return;
    }
}

/* fn_1_173EC */
void CPlayer::stateJump()
{
    if (m_vel.y < 0.0f) {
        SetState(3);
        return;
    }
}

/* fn_1_1743C (~ m539 stateFall) */
void CPlayer::stateFall()
{
    float h = m_sphere.pos.y - 30.000002f;
    if (h <= s_groundY) {
        SetState(4);
        return;
    }
}

void CPlayer::stateLand()
{
    Physics();
    CountDown(m_landTimer); /* result unused (retail) */
    if (m_sphere.pos.y <= s_groundY) {
        SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
        if (m_landTimer <= 0) {
            SetState(0);
            return;
        }
    }
}

/* fn_1_17578: (sin yaw, 0, cos yaw); CW evaluates the arguments right to left (cos first) */
void CPlayer::GetDir(Vec* out) const
{
    float rad = M_PI * m_yaw / 180.0;
    SetVec(out, sin(rad), 0.0f, cos(rad));
}

/* fn_1_1763C (jump table data_728) */
void CPlayer::procMain()
{
    if (m_driver.get() != NULL) {
        CDriver* driver = m_driver.get();
        if (CGameObject::GetUpdateMode() == 2) {
            driver->Update();
        } else {
            driver->m_info.x = 0.0f;
            driver->m_info.y = 0.0f;
            driver->m_info.mag = 0.0f;
            driver->m_info.btn = false;
        }
        switch (m_state) {
        case 0:
            stateIdle();
            break;
        case 1:
            stateWalk();
            break;
        case 2:
            stateJump();
            break;
        case 3:
            stateFall();
            break;
        case 4:
            stateLand();
            break;
        case 5:
            statePush();
            break;
        case 6:
            stateStun();
            break;
        }
        m_stateTime++;
    }
}

/* fn_1_17760 */
bool CPlayer::IsAirborne() const
{
    switch (m_state) {
    case 2:
    case 3:
    case 4:
        return true;
    }
    return false;
}

/* fn_1_17788 */
void CPlayer::SetWin()
{
    m_result = 0;
}

/* fn_1_17794 */
void CPlayer::SetLose()
{
    m_result = 1;
}

/* fn_1_177A0 */
void CPlayer::stateStun()
{
    bool done = CountDown(m_stunTimer);
    if (CharMotionEndCheck(m_charNo) || done) {
        SetState(0);
        return;
    }
}

/* fn_1_17840 */
void CPlayer::ResetFacing()
{
    SetState(0);
    m_targetYaw = 0.0f;
}

/* fn_1_17884 */
void CPlayer::PlayMotion4()
{
    SetMotion(4, true);
}

/* fn_1_17920 */
void CPlayer::PlayMotion5()
{
    SetMotion(5, true);
}

/* fn_1_179E8 */
void CPlayer::SetOnStand()
{
    m_onStand = true;
}

} // namespace m521
