#ifndef M532_PLAYER_H
#define M532_PLAYER_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m532 {

/* fn_1_EE18 (unreferenced; inlined 5x): SE pan of a world position, 32 + screen x / 9, clamped to 0..127 */
s16 GetPan(Vec* pos);
/* fn_1_EEB8: HuAudFXPlayPan(se, GetPan(pos)) (ball.cpp's CBall::stateThrown too) */
void PlaySe(int se, Vec* pos);

/* A scalar wrapped into [min, max) (the yaw, degrees 0..360). No vptr, no base; 0x10 bytes. The name is ours
 * (sheet §1.2: no mgcpp / finished-overlay equivalent). Retail calls every CAngle function out of line and
 * inlines wrap only into the ctor and diff(a, b): so they are ordinary functions defined at the END of
 * player.cpp (after every caller) in retail order set, diff(v), approach, wrap, get, ctor, diff(a, b) -- wrap
 * after set/approach, before the ctor and diff(a, b) (-inline auto inlines only earlier bodies). */
class CAngle {
public:
    CAngle(float a, float b, float v);   /* fn_1_12AD4 */
    void set(float v);                   /* fn_1_12884 */
    float diff(float v);                 /* fn_1_128C0 diff(m_value, v) */
    void approach(float v, double rate); /* fn_1_128FC */
    float wrap(float v);                 /* fn_1_12970 */
    float get();                         /* fn_1_12A0C */
    float diff(float a, float b);        /* fn_1_13390 the shortest signed difference b - a */

    float m_min;   /* 0x0 */
    float m_max;   /* 0x4 */
    float m_range; /* 0x8 */
    float m_value; /* 0xC */
};

class CPlayer : public TLinkItem<CPlayer>, public CModel {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 9 };
    /* motion slots: 0 idle, 1 walk, 2 ready, 3 catch, 4 bonk, 5 carry, 6 throw, 7 win, 8 lose (sheet §1.1) */

    static void Create();                                   /* fn_1_EF70 game_master on_setup */
    static void Arrange(TLinkList<CPlayer>* list, int side); /* fn_1_F03C random front/back, start spots */
    static void UpdateAll();                                /* fn_1_F1F8 game_master on_update */
    static void Update(CPlayer* p);                         /* fn_1_F23C the exec callback */
    static void SetFrontIdle();                             /* fn_1_F27C man_referee stateWaitBall */
    static void StartTiming(int cue);                       /* fn_1_F2F8 game_master playRounds */
    static int Judge(float* out);                           /* fn_1_F38C the round's winning team (3: both missed) */
    static bool IsBallTaken();                              /* fn_1_F514 */
    static void GoHome();                                   /* fn_1_F5C4 */
    static void Award(int who);                             /* fn_1_F6E0 the ball to the winner / onto the fouler */
    static void Rotate();                                   /* fn_1_F9C8 */
    static void RotateTeam(TLinkList<CPlayer>* list, int side); /* fn_1_FA04 side unused */
    static bool IsTimingDone();                             /* fn_1_FA78 both fronts idle */
    static void SetResult(int result);                      /* fn_1_FB08 game_master thread_exec */
    static void SetResultTeam(TLinkList<CPlayer>* list, int motion); /* fn_1_FC24 AddWinner when motion 7 */
    static void DeleteAll();                                /* fn_1_FD80 game_master on_close */
    CPlayer(int idx);                                       /* fn_1_FE8C */
    ~CPlayer();                                             /* fn_1_10284 */
    void proc_none();                                       /* fn_1_10370 the ctor's proc */
    void startTiming(int cue);
    void proc_timing();                                     /* fn_1_106A0 */
    bool isPressed();                                       /* fn_1_107FC A (edge) or the COM frame */
    void setCatch(int ball);                                /* fn_1_10860 */
    void proc_catch();                                      /* fn_1_108A8 */
    void proc_hold();                                       /* fn_1_10A88 */
    void proc_carry();                                      /* fn_1_10BD0 */
    void proc_throw();                                      /* fn_1_10C5C */
    void setBonk(int ball);                                 /* fn_1_10FE0 */
    void proc_bonk();
    void proc_bonkPass();                                   /* fn_1_111A4 */
    void setWatch(int ball);                                /* fn_1_11340 */
    void proc_watch();                                      /* fn_1_11388 */
    void moveToBack();                                      /* fn_1_11430 */
    void proc_moveToBack();                                 /* fn_1_11518 */
    void moveToFront();                                     /* fn_1_1162C */
    void proc_moveToFront();                                /* fn_1_116CC */
    void proc_goHome();                                     /* fn_1_11788 */
    void proc_turn();                                       /* fn_1_1180C */
    void proc_result();                                     /* fn_1_118FC */
    void proc_idle();                                       /* fn_1_11988 */
    CPlayer* getRival();                                    /* fn_1_1198C the other team's front player */
    bool updatePath();                                      /* fn_1_119F4 true when the path is done */
    void updateModel();                                     /* fn_1_11BFC */
    int getLate();                                          /* fn_1_11D00 m_cue - m_timer */
    Vec* getHandPos(Vec* out);                              /* fn_1_11D20 */
    Vec* getCatchPos(Vec* out);                             /* fn_1_11DA0 */
    Vec* getHeadPos(Vec* out);                              /* fn_1_11E98 */
    void holdBall();                                        /* fn_1_11F10 */
    bool addPath(const Vec* p);                             /* fn_1_11FAC false when already there */
    void createRumbleWarn();                                /* fn_1_120C4 unreferenced (inlined in rumble) */
    void createMotions();                                   /* fn_1_1215C assert player.cpp:894 */
    void createMotion(int dataNum);                         /* fn_1_12254 */
    void setMotion(int slot, bool loop);                    /* fn_1_122CC */
    float getMotionTime();                                  /* fn_1_123F8 */
    void rumble(int kind);                                  /* fn_1_12464 0 bonk-pass, 1 the cue, 2 bonk */
    static bool IsRumblePad(int pad);                       /* fn_1_1259C unreferenced (inlined 4x) */
    bool IsRumbleAll();                                     /* fn_1_1260C a member: rumble passes this (F2) */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }
    /* proc_timing's countdown: true on the frame m_timer reaches 0 (retail materialises the bool) */
    bool countDown() { return m_timer > 0 && --m_timer == 0; }

    /* 0x00 CLinkNode (TLinkItem), 0x08 CModel base (+2 pad) */
    int m_idx;                     /* 0x0C player 0..3 (AddWinner, omVibrate) */
    int m_charNo;                  /* 0x10 GwPlayerConf[idx].charNo */
    int m_grp;                     /* 0x14 GwPlayerConf[idx].grp: the requested team */
    int m_padNo;                   /* 0x18 -1 for COM */
    int m_dif;                     /* 0x1C GwPlayerConf[idx].diff (read for humans too) */
    int m_team;                    /* 0x20 0/1, the list actually joined; team 0 plays on -x */
    u32 m_ball;                    /* 0x24 ball handle (0 = none; F514 compares it cmplwi), resolved by CObject::GetHandlePtr */
    int m_timer;                   /* 0x28 countdown from s_roundTime */
    int m_cue;                     /* 0x2C */
    int m_comPress;                /* 0x30 COM press frame */
    Vec m_pos;                     /* 0x34 */
    std::vector<Vec> m_path;       /* 0x40 waypoints */
    CAngle m_yaw;                  /* 0x4C [0, 360) */
    float m_yawTarget;             /* 0x5C not set by the ctor (Arrange sets it; retail) */
    int m_wait;                    /* 0x60 frames before walking to the back after a throw */
    ProcFunc m_proc;               /* 0x64 (12 bytes on CW; called with no __ptmf_test) */
    std::vector<s16> m_motion_id;  /* 0x70 nine CharMotionCreate ids */
    int m_motion;                  /* 0x7C current slot, -1 */
};

} // namespace m532

#endif
