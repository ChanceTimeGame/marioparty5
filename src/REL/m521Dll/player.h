#ifndef M521_PLAYER_H
#define M521_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/om.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m521Dll/a_set.h"
#include "REL/m521Dll/driver.h"
#include <memory>
#include <vector>

namespace m521 {

class CClock;

/* fn_1_15298 (unreferenced; inlined in Update): the voice pan, clamp(2D x / 9 + 32, 0, 127) (= m532 / m522 GetPan) */
s16 GetPan(Vec* pos);

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 10 };

    static float SubAngle(float a, float b);                 /* fn_1_15338 (= m579 / m509; unreferenced) */
    static float SubAngleMax(float a, float b, float max);   /* fn_1_153F0 (= m579 / m509; inlined in Update) */
    static bool IsMove(const CDriver::INFO& info);           /* fn_1_15554 mag >= 0.7 (unreferenced) */
    void ResetPos();                                         /* fn_1_15578 (inlined in the ctor) */
    static CDriver* CreateDriver(int pl, CPlayer* p);        /* fn_1_155B8 (inlined in the ctor) */
    CPlayer(int pl, int slot);                               /* fn_1_15664 assert player.cpp:119 */
    bool IsCom() const;                                      /* fn_1_15D68 (driver) */
    static void Collide(CPlayer* a, CPlayer* b);             /* fn_1_15D94 (gamemaster ForEachPair) */
    void AddMotion(u32 dataNum);                             /* fn_1_15DF0 */
    static void GetStandMtx(int slot, Mtx out);              /* fn_1_15E68 (inlined in Update) */
    void Update();                                           /* fn_1_15F04 (gamemaster exec PTMF) */
    void Vibrate(int kind);                                  /* fn_1_1644C (unreferenced) */
    CClock* GetClock() const;                                /* fn_1_1650C (driver) */
    void SetMotion(int idx, bool once);                      /* fn_1_1654C */
    void procStart();                                        /* fn_1_16648 */
    void Clamp();                                            /* fn_1_16720 */
    void Physics();                                          /* fn_1_168C0 */
    float GetClockDist() const;                              /* fn_1_16BD0 */
    void SetState(int state);                                /* fn_1_16C54 */
    void stateIdle();                                        /* fn_1_16F98 */
    void stateWalk();                                        /* fn_1_170F8 */
    bool Move();                                             /* fn_1_17218 */
    void statePush();                                        /* fn_1_173B8 */
    void stateJump();                                        /* fn_1_173EC */
    void stateFall();                                        /* fn_1_1743C */
    void stateLand();                                        /* fn_1_174B0 (Physics() a second time: retail) */
    void GetDir(Vec* out) const;                             /* fn_1_17578 (sin yaw, 0, cos yaw) (driver); void: r3 not set (retail) */
    void procMain();                                         /* fn_1_1763C */
    bool IsAirborne() const;                                 /* fn_1_17760 */
    void SetWin();                                           /* fn_1_17788 (gamemaster) */
    void SetLose();                                          /* fn_1_17794 (gamemaster) */
    void stateStun();                                        /* fn_1_177A0 */
    void ResetFacing();                                      /* fn_1_17840 (gamemaster exec PTMF) */
    void PlayMotion4();                                      /* fn_1_17884 (gamemaster) */
    void PlayMotion5();                                      /* fn_1_17920 (gamemaster exec PTMF) */
    void SetOnStand();                                       /* fn_1_179E8 (gamemaster) */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    /* 0x00 CLinkNode (TLinkItem) */
    std::auto_ptr<CDriver> m_driver;   /* 0x08 deleted through the virtual dtor */
    ProcFunc m_proc;                   /* 0x0C procStart -> procMain */
    int m_pl;                          /* 0x18 player number (GwPlayerConf index) */
    int m_slot;                        /* 0x1C 0..3 sorted by group: slot >> 1 = team */
    int m_charNo;                      /* 0x20 */
    int m_curMotion;                   /* 0x24 -1 */
    CSphere m_sphere;                  /* 0x28 pos + radius 50 */
    int m_unk38;                       /* 0x38 0, never read */
    int m_stateTimer;                  /* 0x3C 150 on every SetState (driver reads the partner's) */
    int m_stunTimer;                   /* 0x40 */
    int m_landTimer;                   /* 0x44 */
    int m_idleDelay;                   /* 0x48 */
    CPlayer* m_partner;                /* 0x4C set by gamemaster on_setup */
    u8 m_unk50;                        /* 0x50 never accessed */
    bool m_onStand;                    /* 0x51 */
    int m_result;                      /* 0x54 -1 none, 0 win, 1 lose */
    int m_stateTime;                   /* 0x58 */
    int m_pushHand;                    /* 0x5C */
    float m_yaw;                       /* 0x60 degrees */
    float m_targetYaw;                 /* 0x64 */
    Vec m_vel;                         /* 0x68 */
    Vec m_force;                       /* 0x74 */
    int m_state;                       /* 0x80 */
    std::vector<s16> m_mot_id;         /* 0x84 (the assert's name) NUMBEROF_MOTION entries */
    std::auto_ptr<CModel> m_model;     /* 0x90 CModel(charNo, 2) */
};

} // namespace m521

#ifndef __MWERKS__
template <> ASet<m521::CPlayer>* ASet<m521::CPlayer>::sm_ptr; /* defined in gamemaster.cpp (.bss A70) */
#endif

#endif
