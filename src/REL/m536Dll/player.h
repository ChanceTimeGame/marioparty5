/* player.h -- m536::CPlayer (player.cpp): one of the four players, each behind an auto-rotating Bill Blaster
 * in an arena corner. Human: A button only; COM: a per-difficulty random roll when an opponent is in the aim
 * window. 3 lives; a hit (killer.cpp -> CheckHit) costs one; at 0 the player is blown away and hidden.
 * GC size 0x98 (game_master `li r3,0x98`). No virtuals, no vptr: CLinkNode is at offset 0 on every ABI.
 * player.h does not include minigame.h (killer.cpp includes this header and has no 120/210/210 triple);
 * player.cpp includes it itself. */
#ifndef M536_PLAYER_H
#define M536_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m536 {

/* degrees <-> 16-bit binary angle (65536 per turn) and the wrapped difference of two binary angles (as m501
 * player.h): SubAngle 9B50 is one inline level per helper (the `mr` chains of 9B50/9C08 and the inlined
 * copies in updateRotate/getTargetAngle). */
inline int DegToAngle(float deg)
{
    return (65536.0 / 360.0) * deg;
}

inline float AngleToDeg(int angle)
{
    return (360.0 / 65536.0) * angle;
}

inline int AngleSub(int a, int b)
{
    return ((a - b - 0x8000) & 0xFFFF) - 0x8000;
}

/* Vec setter with DOUBLE components (as m501 player.h): retail stores the one non-constant component with
 * `frsp; stfs` (the rotation Vec of the ctor A774 and UpdatePlayer B284) */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 6 };

    static float SubAngle(float a, float b);               /* fn_1_9B50 (as m501 D0BC) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_9C08 */
    static void UpdateRotateSE();                          /* fn_1_9D6C UpdateAll's loop-SE block */
    void updateRotate();                                   /* fn_1_9E0C corner, yaw, gun, matrix */
    static void Close();                                   /* fn_1_A3A0 CGameMaster::on_close */
    CPlayer(int idx);                                      /* fn_1_A4A8 */
    void createMotion(int dataNum);                        /* fn_1_AAB0 m_mot_id.push_back */
    static void UpdateAll();                               /* fn_1_AB28 CGameMaster::on_update */
    /* fn_1_AC40: arms damage (s_hitEnable = 1) and returns true when at least 3 players are dead
     * (CGameMaster::checkEnd polls it every play frame) */
    static bool CheckGameEnd();
    /* fn_1_ACD4: the result -- dense rank 0..3 into GwPlayer[no].mgCoinBonus unless practice */
    static void SetRank();
    static bool StartPlayerWin();                          /* fn_1_AFF0 true = draw */
    static void UpdatePlayer(CPlayer* p);                  /* fn_1_B1AC */
    void setMotion(int motion, bool once);                 /* fn_1_B314 once: no HU3D_MOTATTR_LOOP */
    void proc_start();                                     /* fn_1_B3D4 */
    /* fn_1_B4B0: killer.cpp, the bill of `owner` at pos -- true when it hits another live player */
    static bool CheckHit(int owner, Vec* pos);
    static void Shot(int idx, Vec* pos, float yaw);        /* fn_1_B700 CKillerMan::Shoot + CGun::Fire */
    void proc_main();                                      /* fn_1_B79C */
    void proc_blow();                                      /* fn_1_B978 */
    void proc_hide();                                      /* fn_1_BB30 */
    void proc_win();                                       /* fn_1_BB80 */
    void proc_lose();                                      /* fn_1_BC28 (only on the all-alive draw) */
    static float GetAngle(Vec* a, Vec* b);                 /* fn_1_BCD0 degrees */
    bool getTargetAngle(float* diff, bool* noHuman);       /* fn_1_BD44 */
    bool comCheckShot();                                   /* fn_1_C0FC */
    void updateShot();                                     /* fn_1_C6DC */
    void updateDisp();                                     /* fn_1_CF58 */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPlayer> playerList; /* bss A98; its DestructorChain A8C */

    /* 0x00 CLinkNode (through TLinkItem) */
    ProcFunc m_proc;      /* 0x08 (12 bytes on CW; called with no __ptmf_test) */
    bool m_gunReady;      /* 0x14 updateRotate moves the gun only once set (the ctor's call runs before the gun exists) */
    int m_idx;            /* 0x18 player 0..3 */
    int m_charNo;         /* 0x1C GwPlayerConf[i].charNo ("m_char_id") */
    int m_padNo;          /* 0x20 -1 for COM */
    int m_motion;         /* 0x24 current m_mot_id index, -1 */
    int m_dif;            /* 0x28 COM difficulty GwPlayerConf[i].dif */
    float m_force;        /* 0x2C "root_motion" force while blown away */
    Vec m_pos;            /* 0x30 body position (matrix * s_bodyOfs) */
    Vec m_muzzle;         /* 0x3C muzzle position (matrix * s_muzzleOfs) */
    Vec m_vel;            /* 0x48 blow-away velocity */
    bool m_dead;          /* 0x54 */
    bool m_winner;        /* 0x55 sole survivor: slides to the centre */
    int m_slideTimer;     /* 0x58 0..120 */
    bool m_finish;        /* 0x5C game over: turn to about -20 degrees and stop */
    int m_stamp;          /* 0x60 update counter while alive: the rank key of a dead player */
    float m_yaw;          /* 0x64 degrees (-180, 180] */
    float m_yawSpeed;     /* 0x68 degrees per frame */
    int m_holdTimer;      /* 0x6C rotation hold: 240 at spawn, 30 after a shot */
    int m_life;           /* 0x70 3 */
    int m_stun;           /* 0x74 hit stun / blink, 90 */
    bool m_fireReq;       /* 0x78 */
    int m_cooldown;       /* 0x7C 129 on a press; the shot leaves at <= 120 */
    bool m_slideSePlay;   /* 0x80 */
    int m_slideSe;        /* 0x84 HuAudFXPlay(0x7D6) handle */
    CModel m_model;       /* 0x88 CModel(charNo, 1) */
    std::vector<s16> m_mot_id; /* 0x8C six CharMotionCreate ids (s16: sth/lha) */
};

} // namespace m536

#endif
