/* timer.h -- CTimer (timer.cpp): wraps an MGTIMER. GC size 4. No virtuals. */
#ifndef MGCPP_TIMER_H
#define MGCPP_TIMER_H

#include "REL/mgcpp/game.h"

class CTimer {
public:
    CTimer(int type);  /* 0/1/2, else assert(false) timer.cpp:30 */
    ~CTimer();
    void setParam(int a, int b, int c);
    int getValue();
    void setPos(float x, float y);
    void getPos(float* x, float* y);
    void setModeOn(int mode); /* 0/1/2, else assert(false) timer.cpp:72 */
    void setModeOff();
    void stopTimer();
    void resetTimer();
    bool checkDone();
    void setWinColor(u8 r, u8 g, u8 b);

    MGTIMER* m_timer; /* 0x0 */
};

#endif
