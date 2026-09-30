#ifndef M579_PLAYER_H
#define M579_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>

namespace m579 {

class CFishLine;

/* degrees <-> 16-bit binary angle and the wrapped difference of two binary angles (m509/m512 player.h) */
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

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 7 };

    static float SubAngle(float a, float b);               /* fn_1_C6D4 unreferenced (= m509 EE38) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_C78C unreferenced (= m509 EEF0) */
    static void GetStartPos(Vec* pos, int idx);            /* fn_1_C8F0 unreferenced (inlined in the ctor) */
    static void Close();                                   /* fn_1_CA2C gm on_close (= m512 91AC / m537 9EE4) */
    CPlayer(int idx);                                      /* fn_1_CAD0 assert player.cpp:134 */
    ~CPlayer();                                            /* fn_1_D17C NON-virtual (= m513 ~CHeiho DE94) */
    s16 addMotion(u32 dataNum);                            /* fn_1_D244 */
    static void UpdateAll();                               /* fn_1_D2C0 exec(Update), exec(UpdateAfter), rotate */
    static void JudgeAll();                                /* fn_1_D358 gm: ranks, AddWinner, s_winner */
    static void FinishAll();                               /* fn_1_D594 gm: winner zoom, every proc = procFinish */
    void procFinish();
    void procEnter();                                      /* fn_1_DA38 */
    static bool ResultAll();                               /* fn_1_DE88 gm: true = draw (nobody won) */
    void procWin();                                        /* fn_1_DFBC */
    void procLose();                                       /* fn_1_DFEC */
    static void Update(CPlayer* p);                        /* fn_1_E01C */
    static void UpdateAfter(CPlayer* p);                   /* fn_1_E060 */
    void UpdateModel();                                    /* fn_1_E0AC */
    void PushOthers();
    void setMotion(int no, bool once);                     /* fn_1_E524 */
    void procStart();                                      /* fn_1_E5E4 */
    void procPlay();                                       /* fn_1_E6C8 */
    void getHandMtx(Mtx m);                                /* fn_1_E9BC (fishline CalcRodMtx) */
    void procReel();                                       /* fn_1_EA28 */
    void procShow();                                       /* fn_1_EEF4 */
    void updateReel();                                     /* fn_1_F050 unreferenced (inlined in procFinishReel) */
    void procFinishReel();                                 /* fn_1_F3A8 */
    void setMotionWin();                                   /* fn_1_F810 unreferenced: setMotion(5, true) */
    bool move(Vec* dir);                                   /* fn_1_F8B0 */
    void GetInput(Vec* dir);                               /* fn_1_FC6C */
    bool ClampRing();
    float GetRingAngle();                                  /* fn_1_10100 */
    void GetComInput(Vec* dir);                            /* fn_1_101C8 */

    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPlayer> s_list; /* bss AD4; its DestructorChain AC8 */

    /* 0x00 CLinkNode (TLinkItem) */
    Vec m_pos;                    /* 0x08 (camera proc_winner reads it) */
    ProcFunc m_proc;              /* 0x14 (12 bytes on CW; called with no __ptmf_test) */
    int m_idx;                    /* 0x20 player 0..3 */
    int m_charNo;                 /* 0x24 GwPlayerConf.charNo */
    int m_padNo;                  /* 0x28 -1 for COM (signed test) */
    int m_motion;                 /* 0x2C current m_mot_id index, -1 */
    int m_dif;                    /* 0x30 COM difficulty */
    float m_yaw;                  /* 0x34 degrees */
    float m_unk38;                /* 0x38 0, never read */
    float m_targetYaw;            /* 0x3C degrees */
    float m_speed;                /* 0x40 |dir| */
    int m_state;                  /* 0x44 0 / 1 / 18, write-only */
    float m_radius;               /* 0x48 ClampRing's |pos.xz|, write-only */
    CModel m_model;               /* 0x4C CModel(charNo, 1) */
    bool m_win;                   /* 0x4E JudgeAll */
    int m_timer;                  /* 0x50 reel / show frames (not set by the ctor) */
    CFishLine* m_line;            /* 0x54 the rod being reeled */
    CFishLine* m_comTarget;       /* 0x58 COM target rod */
    int m_comWait;                /* 0x5C */
    int m_score;                  /* 0x60 catch count */
    bool m_free;                  /* 0x64 pushable (not set by the ctor; host: zeroed) */
    int m_frame;                  /* 0x68 */
    int m_active;                 /* 0x6C procEnter done: PushOthers / ClampRing run */
    int m_reelState;              /* 0x70 0 play / 1 reel / 2 show (not set by the ctor) */
    std::vector<s16> m_mot_id;    /* 0x74 NUMBEROF_MOTION CharMotionCreate ids */
};

} // namespace m579

#endif
