/* timer.cpp -- CTimer: an MGTIMER (game/mg/timer.h) owned by a C++ object. Retail order.
 * The two assert(false) must stay on timer.cpp lines 30 and 72 (retail .data). */
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/assert.h"

/* MGTIMER_TYPE_NORMAL/RECORD/SCORE is passed to MgTimerCreate; anything else asserts (and leaves m_timer unset) */










CTimer::CTimer(int type)
{
    switch (type) {
    case 0:
        m_timer = MgTimerCreate(MGTIMER_TYPE_NORMAL);
        break;
    case 1:
        m_timer = MgTimerCreate(MGTIMER_TYPE_RECORD);
        break;
    case 2:
        m_timer = MgTimerCreate(MGTIMER_TYPE_SCORE);
        break;
    default:
        assert(false);
        break;
    }
}

/* MgTimerKill frees the MGTIMER */
CTimer::~CTimer() { MgTimerKill(m_timer); }

void CTimer::setParam(int a, int b, int c)
{
    MgTimerParamSet(m_timer, a, b, c);
}

int CTimer::getValue()
{
    return MgTimerValueGet(m_timer);
}

void CTimer::setPos(float x, float y)
{
    MgTimerPosSet(m_timer, x, y);
}

void CTimer::getPos(float* x, float* y)
{
    MgTimerPosGet(m_timer, x, y);
}

/* the MGTIMER_OFFTYPE_* (0/1/2) that MgTimerModeOnSet takes; anything else asserts */
void CTimer::setModeOn(int mode)
{
    switch (mode) {
    case 0:
        MgTimerModeOnSet(m_timer, MGTIMER_OFFTYPE_NORMAL);
        break;
    case 1:
        MgTimerModeOnSet(m_timer, MGTIMER_OFFTYPE_FADEOUT);
        break;
    case 2:
        MgTimerModeOnSet(m_timer, MGTIMER_OFFTYPE_FLASH);
        break;
    default:
        assert(false);
        break;
    }
}

void CTimer::setModeOff()
{
    MgTimerModeOffSet(m_timer);
}

/* freeze the countdown once */
void CTimer::stopTimer()
{
    if (!m_timer->stopF) {
        m_timer->stopF = TRUE;
        m_timer->mode = MGTIMER_MODE_ON;
    }
}

/* a fresh type-0 timer */
void CTimer::resetTimer()
{
    MgTimerKill(m_timer);
    m_timer = MgTimerCreate(MGTIMER_TYPE_NORMAL);
}

bool CTimer::checkDone()
{
    return MgTimerDoneCheck(m_timer);
}

void CTimer::setWinColor(u8 r, u8 g, u8 b)
{
    MgTimerWinColorSet(m_timer, r, g, b);
}
