/* man_referee.cpp -- m532::CRefereeMan (man_referee.h). The assert is retail's man_referee.cpp:233 (keep the
 * line). Retail order: ctor, [~vector<s16>, ~__vector_pod<s16>, ~__vector_base<s16>, ~CSingleton<CRefereeMan>],
 * dtor, IsJumpStart, Whistle, IsMotionDone, ShowResult, GetWhistleTime, on_new_mode, on_update, Idle, stateIdle,
 * Start, stateWaitBall, stateCatch, stateWait, JumpTo, stateJump, stateWhistle, LoadMotions, AddMotion,
 * SetMotion, IsMotionEnd, GetMotionTime, CheckSE, [vector<s16>::at, insert, at const: weak, emitted in reverse
 * order of first use], __sinit (the 300/60 pair).
 * Drafts written whole from the sheet (ball_referee_unk.md §2.4, §3.2) and the asm. */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/m532Dll/man_referee.h"
#include "REL/m532Dll/man_map.h"
#include "REL/m532Dll/ball.h"
#include "REL/m532Dll/player.h"
#include "REL/m532Dll/util.h"
#ifndef __MWERKS__
#include <math.h> /* sqrt (JumpTo) */
#endif

namespace m532 {
/* lbl_1_rodata_2A8 / 2B4: home and the jump target */
static const Vec s_home = { 0.0f, 98.0f, 370.0f };
static const Vec s_jumpTarget = { 0.0f, 4.0f, 500.0f };

CRefereeMan::CRefereeMan()
    : CModel(0x5A000AU), m_state(&CRefereeMan::stateIdle), m_itemR(0x5A0013U), m_itemL(0x5A0014U), m_ball(0),
      m_pos(s_home), m_wait(6), m_motion_id(), m_motion(-1), m_prevTime(0.0f)
{
    setLayer(3);
    set_shadow();
    const HU3DMODELID id = ((CModel*)this)->id();
    Hu3DModelHookSet(id, (char*)"itemhook_R", m_itemR.id());
    Hu3DModelHookSet(id, (char*)"itemhook_L", m_itemL.id());
    m_target.x = 0.0f;
    m_target.y = 0.0f;
    m_target.z = 0.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    LoadMotions();
    SetMotion(0, true);
}

CRefereeMan::~CRefereeMan() {}

bool CRefereeMan::IsJumpStart()
{
    return m_motion == 3 && GetMotionTime() == 0.0f;
}

void CRefereeMan::Whistle()
{
    SetMotion(7, false);
    setState(&CRefereeMan::stateWhistle);
}

bool CRefereeMan::IsMotionDone()
{
    return IsMotionEnd() || m_motion == 0;
}

void CRefereeMan::ShowResult(int result)
{
    switch (result) {
    case 0:
        SetMotion(4, false);
        HuAudFXPlay(0x7B3);
        break;
    case 1:
        SetMotion(5, false);
        HuAudFXPlay(0x7B3);
        break;
    case 2:
    case 3:
        SetMotion(6, false);
        HuAudFXPlay(0x7B4);
        break;
    }
    setState(&CRefereeMan::stateIdle);
}

float CRefereeMan::GetWhistleTime() const
{
    return Hu3DMotionMotionMaxTimeGet(m_motion_id[7]) / 60.0f;
}

void CRefereeMan::on_new_mode(int mode)
{
    switch (mode) {
    case 0:
        Start(); /* the bit is cleared by stateJump */
        break;
    case 1:
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

void CRefereeMan::on_update()
{
    (this->*m_state)();
    CModel::setPos(&m_pos);
    CheckSE();
}

void CRefereeMan::Idle()
{
    SetMotion(0, true);
    setState(&CRefereeMan::stateIdle);
}

void CRefereeMan::stateIdle() {}

void CRefereeMan::Start()
{
    Vec pos = { 0.0f, 0.0f, 0.0f };
    pos.x = s_home.x;
    pos.y = 150.0 + s_home.y;
    pos.z = s_home.z;
    m_ball = CSingleton<CMapMan>::GetInstance()->grabNearest(&pos);
    setState(&CRefereeMan::stateWaitBall);
}

void CRefereeMan::stateWaitBall()
{
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball == 0 || ball->isLanded()) {
        SetMotion(2, false);
        HuAudFXPlay(0x7AF);
        CPlayer::SetFrontIdle();
        setState(&CRefereeMan::stateCatch);
    }
}

void CRefereeMan::stateCatch()
{
    if (IsMotionEnd()) {
        SetMotion(0, true);
        setState(&CRefereeMan::stateWait);
    }
}

void CRefereeMan::stateWait()
{
    bool jump = false;
    if (m_wait > 0 && --m_wait == 0) {
        jump = true;
    }
    if (jump) {
        JumpTo(&s_jumpTarget);
    }
}

#ifdef __MWERKS__
/* retail JumpTo inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases; m509 camera) */
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

/* |v| through an inline: retail copies the PSVECMag result twice (BD18 fmr f23 / fmr f30), a nested inline's
 * return (man_map A6C0 has the same shape; a shared util.h helper is the lead's call) */
inline float HorizDist(Vec* v)
{
    return PSVECMag(v);
}

/* fn_1_BC50: the launch speed for a 45-degree arc to `to` (horizontal speed = vertical speed = s, with
 * s^2 = g h^2 / (2 (h - dy))). Retail passes the expression itself to the inline sqrt (re-evaluated at every use).
 * Retail hazard (transcribed): h == 0 (a jump straight up) divides by zero twice, and h <= dy gives a negative or
 * infinite square-root argument (NaN / Inf speed); the only caller jumps from (0, 98, 370) to (0, 4, 500). */
void CRefereeMan::JumpTo(const Vec* to)
{
    m_target.x = to->x;
    m_target.y = to->y;
    m_target.z = to->z;
    SetVec(&m_vel, to->x - m_pos.x, 0.0f, to->z - m_pos.z);
    float h = HorizDist(&m_vel);
    float dy = to->y - m_pos.y;
    float h2 = h * h;
#ifdef __MWERKS__
    float s = MslSqrt(M532_GRAVITY * h2 / (2.0f * (h - dy)));
#else
    float s = sqrt(M532_GRAVITY * h2 / (2.0f * (h - dy)));
#endif
    PSVECScale(&m_vel, &m_vel, s / h);
    m_vel.y = s;
    SetMotion(3, false);
    setState(&CRefereeMan::stateJump);
}

void CRefereeMan::stateJump()
{
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    m_vel.y -= M532_GRAVITY;
    if (m_pos.y <= m_target.y) {
        m_pos = m_target;
        if (IsMotionEnd()) {
            m_execFlags &= ~1;
            Idle(); /* inlined: retail shares Idle's PTMF constant (data_530) */
        }
    }
}

void CRefereeMan::stateWhistle()
{
    if (IsMotionEnd()) {
        Idle(); /* inlined (data_530 shared) */
    }
}

void CRefereeMan::LoadMotions()
{
    m_motion_id.clear();
    AddMotion(0x5A000B);
    AddMotion(0x5A000C);
    AddMotion(0x5A000D);
    AddMotion(0x5A000E);
    AddMotion(0x5A000F);
    AddMotion(0x5A0010);
    AddMotion(0x5A0011);
    AddMotion(0x5A0012);
/* retail's assert is man_referee.cpp:233 (a #line, as player.cpp:894: the code above it is longer than retail's) */
#line 233
    assert(m_motion_id.size() == NUMBER_OF_MOTION);
}

void CRefereeMan::AddMotion(u32 dataNum)
{
    void* data = HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
    m_motion_id.push_back(Hu3DJointMotion(((CModel*)this)->id(), data));
}

void CRefereeMan::SetMotion(int motion, bool loop)
{
    const HU3DMODELID id = ((CModel*)this)->id();
    const s16 mot = m_motion_id[motion];
    if (m_motion != motion || IsMotionEnd()) {
        CModel::setAttr(HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(id, mot, 0.0f, 12.0f, loop ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
        if (motion == 6) {
            Hu3DMotionShiftStartEndSet(id, 0.0f, 14.0f);
        }
    }
}

bool CRefereeMan::IsMotionEnd()
{
    return Hu3DMotionEndCheck(((CModel*)this)->id());
}

float CRefereeMan::GetMotionTime()
{
    const HU3DMODELID id = ((CModel*)this)->id();
    if (Hu3DMotionShiftIDGet(id) >= 0) {
        return Hu3DMotionShiftTimeGet(id) - 1.0f;
    }
    return Hu3DMotionTimeGet(id);
}

void CRefereeMan::CheckSE()
{
    float t = GetMotionTime();
    if (m_motion == 7 && m_prevTime < 30.0f && t >= 30.0f) {
        HuAudFXPlay(0x7B2);
    }
    m_prevTime = t;
}

} // namespace m532
