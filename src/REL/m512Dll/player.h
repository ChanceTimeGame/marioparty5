/* player.h -- m512::CPlayer (player.cpp): one of the four skaters of the 5-lap oval race. Human: stick X
 * steers, A held is the throttle; COM: steers toward the inner edge with a per-difficulty gain. The first over
 * the line after 5 laps is the single AddWinner (normal mode); Decathlon writes the finish frames.
 * GC size 0xB0 (gamemaster `li r3,0xB0`). No virtuals, no vptr: CLinkNode is at offset 0 on every ABI.
 * player.h does not include minigame.h (player.cpp includes it itself); zako.cpp includes this header for the
 * angle/SetVec inlines. */
#ifndef M512_PLAYER_H
#define M512_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m512 {

/* degrees <-> 16-bit binary angle and the wrapped difference of two binary angles (m536 player.h):
 * SubAngle/SubAngleMax (player 8E48/8F00, zako EB1C/EBD4) are m536 9B50/9C08 exactly. */
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

/* Vec setter with DOUBLE components (m501/m536 player.h): retail stores the one non-constant component with
 * `frsp; stfs` (the rotation Vec of updateDisp A604, zako updateModel F168) */
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
    enum { NUMBEROF_MOTION = 4 };

    static float SubAngle(float a, float b);               /* fn_1_8E48 unreferenced (= m536 9B50) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_8F00 unreferenced (= m536 9C08) */
    static void GetStartPos(Vec* pos, int idx);            /* fn_1_9064 inlined in the ctor */
    static void ShuffleStart();                            /* fn_1_9104 CGameMaster::on_setup: shuffles s_order */
    static void Close();                                   /* fn_1_91AC CGameMaster::on_close */
    CPlayer(int idx);                                      /* fn_1_9250 */
    ~CPlayer();                                            /* fn_1_9A14 out-of-line (Close calls it) */
    s16 createMotion(int dataNum);                         /* fn_1_9B08 m_mot_id.push_back; returns the id */
    static void UpdateAll();                               /* fn_1_9B84 CGameMaster::on_update */
    static void UpdateRank();                              /* fn_1_9C20 mode 2: dense rank by lap + angle */
    /* fn_1_9EAC: deca: all 4 at the goal. Else: the goal player furthest past the line is s_winner ->
     * AddWinner + CCameraObj::startWinnerZoom; true once anyone is at the goal */
    static bool CheckGameEnd(bool deca);
    /* fn_1_A040: deca: GwPlayer[].mgScore = finish frames (0 if unfinished). Else: only s_winner keeps its
     * goal flag. Returns true (draw) when nobody reached the goal */
    static bool SetResult(bool deca);
    static void PlayLoseVoice();                           /* fn_1_A160 CharLoseVoicePlay (draw) */
    static void PlayWinnerFX();                            /* fn_1_A1F0 CharFXPlay(winner, 0x1FA) */
    static int GetBestTime();                              /* fn_1_A23C min frames of human finishers, 18000 */
    static void StartWinCamera();                          /* fn_1_A2C8 unreferenced */
    static void GetBounds(Vec* center, Vec* size);         /* fn_1_A350 camera getView (min/max start at 0) */
    static float GetWinnerPos(Vec* pos);                   /* fn_1_A4BC camera proc_zoom: pos, returns yaw */
    static void UpdatePlayer(CPlayer* p);                  /* fn_1_A50C list walk 1 */
    void updateDisp();                                     /* fn_1_A604 model + reflection */
    static void UpdateLap(CPlayer* p);                     /* fn_1_A6E0 list walk 2: velocity, laps, time */
    void hitCheck();                                       /* fn_1_AB34 push apart (120) */
    void setMotion(int motion, bool once);                 /* fn_1_ADEC unreferenced copy (inlined 5x) */
    void proc_start();                                     /* fn_1_AF04 */
    void proc_main();                                      /* fn_1_B030 */
    void updateMove();                                     /* fn_1_B420 physics, stroke SE, dust */
    bool updateMotionSpeed();                              /* fn_1_BE20 false when not moving */
    float comSteer(float steer);                           /* fn_1_BEFC COM steering gain by difficulty */
    void updateInput();                                    /* fn_1_C0C0 */
    bool checkWall();                                      /* fn_1_C3C8 track clamp; true on a wall hit */
    float getTrackYaw();                                   /* fn_1_C91C track tangent, degrees */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPlayer> playerList; /* bss A5C; its DestructorChain A50 */

    /* 0x00 CLinkNode (through TLinkItem) */
    bool m_turnLeft;      /* 0x08 steer < -0.5 this frame -> lean motion 2 */
    bool m_wallHit;       /* 0x09 wall/player contact this frame (drag x10) */
    ProcFunc m_proc;      /* 0x0C (12 bytes on CW; called with no __ptmf_test) */
    int m_idx;            /* 0x18 player 0..3 */
    int m_charNo;         /* 0x1C GwPlayerConf[i].charNo (used as s16) */
    int m_padNo;          /* 0x20 -1 for COM */
    int m_motion;         /* 0x24 current m_mot_id index, -1 */
    int m_dif;            /* 0x28 COM difficulty GwPlayerConf[i].dif */
    float m_yaw;          /* 0x2C degrees (-180, 180] = track yaw + m_steerYaw */
    float m_steerYaw;     /* 0x30 offset from the track tangent */
    float m_throttle;     /* 0x34 0..1 */
    int m_pushTimer;      /* 0x38 5 on the pushed player, -- while > 0; never read (retail) */
    int m_unk3C;          /* 0x3C 0 in the ctor, write-only */
    Vec m_pos;            /* 0x40 */
    Vec m_prevPos;        /* 0x4C */
    Vec m_vel;            /* 0x58 pos - prevPos per frame */
    float m_speed;        /* 0x64 |vel.xz| / 100 */
    int m_time;           /* 0x68 race frames, from 1 */
    float m_trackAngle;   /* 0x6C 0..360 around the oval */
    int m_rank;           /* 0x70 0 = leader (dense) */
    float m_radius;       /* 0x74 distance from the track centre line's centre (750..1450) */
    CModel m_model;       /* 0x78 CModel(charNo, 3) */
    CModel m_skate;       /* 0x7A CModel(0x460006) */
    bool m_goal;          /* 0x7C 5 laps done */
    bool m_winner;        /* 0x7D */
    float m_goalX;        /* 0x80 pos.x when the 5th lap was counted (winner tie-break) */
    bool m_halfLap;       /* 0x84 armed by the crossing on the far side */
    int m_lap;            /* 0x88 0..5 */
    HU3DMODELID m_reflect;    /* 0x8C Hu3DModelLink(m_model): the mirrored reflection */
    HU3DMODELID m_skateId[4]; /* 0x8E [0] = m_skate.id(), [1..3] = Hu3DModelLink(m_skate) */
    int m_hitTimer;       /* 0x98 frames since the last hit, 60 at start */
    bool m_strokeFoot;    /* 0x9C last foot that touched the ice */
    int m_unkA0;          /* 0xA0 0 in the ctor, write-only */
    std::vector<s16> m_mot_id; /* 0xA4 four ids (s16: sth/lha) */
};

} // namespace m512

#endif
