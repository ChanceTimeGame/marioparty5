#ifndef M521_CLOCK_H
#define M521_CLOCK_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/m521Dll/clockhand.h"
#include <memory>

namespace m521 {

/* the per-hand tick-SE countdown (4 bytes; ctor fn_1_5D0 weak, no dtor: __construct_array(.., 5D0, NULL, 4, 2)).
 * Name ours (the sheet's "CTimer" would clash with mgcpp's). Its tick is inlined in Update (C4C). */
struct CTickTimer {
    CTickTimer() : n(0) {}
    bool Tick() { return n > 0 && --n == 0; }
    void Set(int v) { n = v; }
    int n;
};

class CClock {
public:
    bool IsDone() const;                               /* fn_1_0 both hands locked (gamemaster) */
    CClock(int id, const Vec* pos);
    ~CClock();                                         /* fn_1_5DC (does not stop the tick SEs: retail) */
    void GetHandPos(Vec* out, int hand);               /* fn_1_658 the hand matrix X axis (driver StartPush) */
    void GetHandPoint(Vec* out, int hand, float t, float x);
    void Spin();                                       /* fn_1_7A0 speed 30, state 1, Unlock */
    bool IsIdle() const;                               /* fn_1_7E8 m_state == 0 */
    void SetTime(int h, int m);                        /* fn_1_7F8 */
    void SetTarget(int h, int m);                      /* fn_1_894 */
    void SaveTarget();                                 /* fn_1_924 m_prevTarget = m_target */
    void Update();                                     /* fn_1_C4C (stage on_update) */
    void UpdateState();                                /* fn_1_F20 */
    bool IsLocked(int hand) const;                     /* fn_1_1370 range-checked */
    int Rotate(int hand, float delta);                 /* fn_1_139C assert clock.cpp:277; 1 = locked after */
    bool PushOut(Vec* p);                              /* fn_1_1824 always false */
    int HitHands(const Vec* p, Vec* axis, float* push); /* fn_1_1CA0 0 hour / 1 minute / -1 */
    int CrossHands(const Vec* a, const Vec* b);        /* fn_1_20B8 (unreferenced) */
    int GetFreeHand(int prefer) const;                 /* fn_1_22BC (unreferenced) */
    bool IsBlocked(int hand);                          /* fn_1_2480 */
    bool AreHandsWithin(float deg);                    /* fn_1_24D0 */
    bool IsApproaching(int hand, int dir);             /* fn_1_2658 */
    bool IsTargetTooNear(float deg);                   /* fn_1_2998 (gamemaster playRound) */
    bool IsHandNearTarget(float deg);                  /* fn_1_2C98 (gamemaster playRound) */
    int GetTurnDir(int hand);                          /* fn_1_2EFC -1 / 0 / 1 */
    float GetTurnDist(int hand);                       /* fn_1_3268 (unreferenced) */
    int ChooseHand();                                  /* fn_1_35B0 (unreferenced) */
    void Lock();                                       /* fn_1_42A0 both locked */
    void Unlock();                                     /* fn_1_42B4 */
    bool IsPushSide(const Vec* p, int hand);           /* fn_1_42C8 assert clock.cpp:535 */
    void PlayTickSe(int hand);                         /* fn_1_4790 */
    void StopTickSe(int hand);                         /* fn_1_4844 */

    int m_id;                               /* 0x00 0/1 team, 2 display */
    Vec m_pos;                              /* 0x04 pivot (driver / player read &m_pos) */
    float m_time;                           /* 0x10 minutes (60h + m), write-only */
    bool m_locked[2];                       /* 0x14 */
    int m_hold[2];                          /* 0x18 unlock counter (signed) */
    int m_state;                            /* 0x20 0 idle, 1 spin, 2 settle */
    float m_speed;                          /* 0x24 */
    float m_angle[2];                       /* 0x28 0 hour, 1 minute */
    float m_turn[2];                        /* 0x30 accumulated rotation (gear motion time) */
    float m_target[2];                      /* 0x38 */
    float m_prevTarget[2];                  /* 0x40 */
    int m_frame;                            /* 0x48 */
    int m_se[2];                            /* 0x4C tick SE handle, -1 = none */
    CTickTimer m_seTimer[2];                /* 0x54 */
    int m_lastPush[2];                      /* 0x5C frame of the last push, -1 */
    std::auto_ptr<CClockHand> m_hand[2];    /* 0x64 */
    std::auto_ptr<CModel> m_gear[2];        /* 0x6C NB: gearTbl[id][0] goes to m_gear[1] (retail) */
};

} // namespace m521

#endif
