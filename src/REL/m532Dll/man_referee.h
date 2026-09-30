#ifndef M532_MAN_REFEREE_H
#define M532_MAN_REFEREE_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include <vector>

namespace m532 {

class CRefereeMan : public CGameObject, public CSingleton<CRefereeMan>, public CModel {
public:
    typedef void (CRefereeMan::*StateFunc)();
    enum { NUMBER_OF_MOTION = 8 };
    /* motions 0x5A000B..12: 0 idle, 1 (unused), 2 catch, 3 jump, 4/5 team 0/1 wins, 6 draw, 7 whistle */

    CRefereeMan();                       /* fn_1_AFC0 */
    virtual ~CRefereeMan();              /* fn_1_B450 */
    bool IsJumpStart();
    void Whistle();                      /* fn_1_B600 */
    bool IsMotionDone();                 /* fn_1_B670 */
    void ShowResult(int result);         /* fn_1_B6CC 0/1: motion 4/5 + SE 0x7B3; 2/3: motion 6 + SE 0x7B4 */
    float GetWhistleTime() const;        /* fn_1_B7A8 seconds (m_motion_id[7] through at() const, CA94) */
    virtual void on_new_mode(int mode);  /* fn_1_B800 */
    virtual void on_update();            /* fn_1_B8C8 */
    void Idle();                         /* fn_1_B914 */
    void stateIdle();                    /* fn_1_B984 */
    void Start();                        /* fn_1_B988 mode 0: call a ball */
    void stateWaitBall();                /* fn_1_BAAC */
    void stateCatch();                   /* fn_1_BB58 */
    void stateWait();                    /* fn_1_BBDC 6 frames, then the jump */
    void JumpTo(const Vec* to);          /* fn_1_BC50 a 45-degree arc (inline MSL double sqrt) */
    void stateJump();                    /* fn_1_C070 */
    void stateWhistle();                 /* fn_1_C154 */
    void LoadMotions();                  /* fn_1_C1D8 assert man_referee.cpp:233 */
    void AddMotion(u32 dataNum);         /* fn_1_C2B8 */
    void SetMotion(int motion, bool loop); /* fn_1_C358 (sets PAUSE before ShiftSet: retail R4) */
    bool IsMotionEnd();                  /* fn_1_C46C */
    float GetMotionTime();               /* fn_1_C4E4 (inlined into CheckSE) */
    void CheckSE();                      /* fn_1_C570 SE 0x7B2 when the whistle crosses frame 30 */

    /* PTMF stores go through a by-value copy (three words to a stack temp) */
    void setState(StateFunc state) { m_state = state; }

    StateFunc m_state;               /* 0x14 (12 bytes on CW) */
    CModel m_itemR;                  /* 0x20 0x5A0013 on "itemhook_R" */
    CModel m_itemL;                  /* 0x22 0x5A0014 on "itemhook_L" */
    int m_ball;                      /* 0x24 ball handle (CMapMan::grabNearest) */
    Vec m_pos;                       /* 0x28 home (0, 98, 370) */
    Vec m_target;                    /* 0x34 jump target */
    Vec m_vel;                       /* 0x40 */
    int m_wait;                      /* 0x4C 6 frames before the jump */
    std::vector<s16> m_motion_id;    /* 0x50 Hu3DJointMotion ids */
    int m_motion;                    /* 0x5C current, -1 */
    float m_prevTime;                /* 0x60 previous motion time (CheckSE's edge) */
};

} // namespace m532

#ifndef __MWERKS__
template <> m532::CRefereeMan* CSingleton<m532::CRefereeMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
