/* player.h -- m501::CPlayer (player.cpp): one of the four cone-carrying players (human: analog stick;
 * COM: nearest untargeted scoop). GC size 0x14C. No virtuals.
 * player.h does not include minigame.h (camera.cpp includes this header and has no 120/210/210 triple). */
#ifndef M501_PLAYER_H
#define M501_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/link.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/om.h"
#include "REL/m501Dll/joint.h"
#include <vector>

namespace m501 {

/* Vec setter with DOUBLE components: retail stores each component with `frsp; stfs`, evaluates the arguments
 * right to left, and in deep inline contexts spills them with stfd (GetStartPos BA00, getJointPos BFE8, the
 * rotation Vec in UpdatePlayer BE7C). A float-parameter setter compiles without the frsp. */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v; /* retail materialises this (unused) reference where the Vec is a stack local: getStartDist C6C8 */
}

/* VECSubtract returning the result by reference (d = a - b). With SetVec, the reference returns are what
 * retail materialises after every inlined getStartDir (getStartDist C6C8..C6EC: three `addi; mr` copies). */
inline Vec& VecSub(Vec* a, Vec* b, Vec* d)
{
    VECSubtract(a, b, d);
    return *d;
}

/* VECMag through one inline return level: the length lands in a temporary before the variable
 * (doStageCollide BF64: fmr f30,f1; fmr f31,f30). */
inline float VecLength(Vec* v)
{
    return VECMag(v);
}

/* the reference overload: an argument that is itself an inline's reference result is then not copied again
 * (proc_winner_move D7B8 passes &dir straight to PSVECMag; getStartDist C6F0 copies it through the pointer
 * overload) */
inline float VecLength(Vec& v)
{
    return VECMag(&v);
}

/* VECDotProduct through one inline level (UpdatePlayerEnding CD74: the dot product passes two temporaries) */
inline float VecDot(Vec& a, Vec& b)
{
    return VECDotProduct(&a, &b);
}

/* degrees <-> 16-bit binary angle (65536 per turn), and the wrapped difference of two binary angles.
 * SubAngle/SubAngleMax are built from these (D0BC, D174: each helper is one more inline return level). */
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

class CPlayer : public CLinkItem {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 6 };

    static s16 getVoicePan(Vec* pos);
    CPlayer(int idx);
    void createMotion(int dataNum);
    static void GetStartPos(Vec* out, int idx);
    static void PlayerShow();
    static void Close();
    static void UpdateAll();
    static void UpdatePlayer(CPlayer* player);
    void doStageCollide();
    void getJointPos(Vec* out);
    static void CheckAisu(CPlayer* player);
    void startConeDrop(int handle);
    bool centerAisu();
    void updateComTargetPos();
    Vec& getStartDir(Vec* out);   /* fn_1_C400: *out = start position - position */
    float getStartDist();         /* fn_1_C59C */
    /* pairwise push-apart; retail symbol has one parameter (FPQ24m5017CPlayer), the body uses r3/r4
     * (map.player.txt) */
    static void UpdatePlayerEnding(CPlayer* a, CPlayer* b);
    void shrinkCone();
    void setMotion(int motion, bool once); /* once: no HU3D_MOTATTR_LOOP */
    static float SubAngle(float a, float b);
    static float SubAngleMax(float a, float b, float max);
    void proc_hold_cone();
    void proc_main();
    void proc_drop_cone_start();
    void proc_drop_cone();
    static void startWinnerMove();
    void proc_winner_move();
    static void SortPlayerList();
    static bool ComparePlayer(CLinkNode* a, CLinkNode* b); /* a->m_score > b->m_score */
    static bool StartPlayerWin();  /* true = draw */
    /* winners get proc_win (motion 3), the others proc_lose (motion 4, then proc_shrink_cone);
     * symbols.txt has the two names swapped (map.player.txt) */
    void proc_win();
    void proc_lose();
    void proc_shrink_cone();
    float getWinAngleSpeed(float a, float b);
    bool movePlayer(Vec* dir);
    /* retail -char unsigned: these chars are unsigned on CW and signed on x86/x64 (host note) */
    static void GetStickData(char* x, char* y, char dead, char max);
    void getMoveDir(Vec* dir);
    void clampMag();
    static int getNearAisu(std::vector<int>& list, Vec* pos); /* fn_1_F588 */
    void getComMoveDir(Vec* dir);
    void removeOtherTargets(std::vector<int>& list);          /* fn_1_FBAC */
    static void GetPlayerDist(std::vector<HuVec2f_s>* list);
    static bool CheckWinIdle();
    static void execPlayerList(CLinkList* list, void (*func)(CPlayer*));
    static void execPlayerList(CPlayer* begin, CPlayer* end, void (*func)(CPlayer*));
    /* calls func(p, q) for every pair p before q; the retail symbol types func as void(*)(CPlayer*)
     * (map.player.txt) */
    static void execPlayerListReverse(CLinkList* list, void (*func)(CPlayer*, CPlayer*));

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc: B710..B744) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static CLinkList playerList;

    /* 0x000 CLinkNode (through CLinkItem) */
    ProcFunc m_proc;          /* 0x008 (12 bytes on CW) */
    int m_idx;                /* 0x014 player 0..3 */
    int m_charNo;             /* 0x018 GwPlayerConf[i].charNo */
    int m_padNo;              /* 0x01C -1 for COM */
    float m_comSkill;         /* 0x020 (dif+1)*0.25 */
    int m_score;              /* 0x024 scoops caught */
    u8 m_winner;              /* 0x028 */
    u32 m_aisuHandle;         /* 0x02C scoop handle being centred / dropped (compared unsigned: C20C) */
    int m_busyTimer;          /* 0x030 */
    int m_winTimer;           /* 0x034 never read */
    float m_yaw;              /* 0x038 degrees */
    float m_targetYaw;        /* 0x03C */
    float m_moveMag;          /* 0x040 */
    float m_coneScale;        /* 0x044 */
    CSphere m_sphere;         /* 0x048 pos (0x48) + radius 80 (0x54); HitPushSphere */
    Mtx m_mtx;                /* 0x058 RotY(yaw) * Trans(pos) */
    Vec m_stepPos;            /* 0x088 last footprint position */
    int m_stepCount;          /* 0x094 */
    bool m_running;           /* 0x098 speed > 4.5 (bool: retail stores the compare result with no clrlwi, E680) */
    CModel m_model;           /* 0x09A CModel(charNo, 2) */
    CModel m_coneModel;       /* 0x09C CModel(*CGameMaster::GetConeModel()) */
    CJoint m_coneJoint;       /* 0x0A0 */
    CJoint* m_topJoint;       /* 0x114 top of the scoop stack */
    int m_motion;             /* 0x118 current motion index */
    std::vector<int> m_mot_id; /* 0x11C 6 CharMotionCreate ids */
    /* 0x128..0x14B: COM state, cleared by one memset in the ctor (host: sized by the member span, not 0x24).
     * m_comDelay/m_comUnk12C are also member-initialised (two direct stores before the ctor body, B470..B47C),
     * so they are plain members, not a sub-struct. */
    int m_comDelay;           /* 0x128 COM reaction delay */
    int m_comUnk12C;          /* 0x12C only zeroed */
    Vec m_comTarget;          /* 0x130 COM target position */
    int m_comTargetHandle;    /* 0x13C COM target aisu handle */
    Vec m_topJointPos;        /* 0x140 top joint position, player-local */
};

} // namespace m501

#endif
