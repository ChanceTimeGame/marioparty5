#ifndef M537_PLAYER_H
#define M537_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
/* <deque> before <vector>: decides the order of the MSL error strings in player .data (retail: deque::push_back
 * first, then vector::insert / reserve) */
#include <deque>
#include <vector>

namespace m537 {

class CDorrie;

/* A scalar wrapped into [min, max) (m532's class). 0x10 bytes, no vptr. Defined at the end of player.cpp in retail
 * order approach, wrap, ctor, diff(v), diff(a, b) (the weak exec / reserve / deque copies interleave). */
class CAngle {
public:
    CAngle(float a, float b, float v);    /* fn_1_CD4C (= m532 12AD4) */
    float diff(float v);                  /* fn_1_CEB0 diff(m_value, v) */
    float approach(float v, double rate); /* fn_1_BF8C d = diff(v); m_value = wrap(m_value + rate * d) */
    float wrap(float v);                  /* fn_1_BFE8 */
    float diff(float a, float b);         /* fn_1_E320 the shortest signed difference b - a */

    float m_min;   /* 0x0 */
    float m_max;   /* 0x4 */
    float m_range; /* 0x8 */
    float m_value; /* 0xC */
};

class CPlayer : public TLinkItem<CPlayer>, public CModel {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 10 };
    enum { FPS = 60 };
    typedef std::deque<bool> BeatRec;

    static void CreateAll();                /* fn_1_99D0 gm on_setup; assert player.cpp:52 */
    static void UpdateAll();                /* fn_1_9ACC exec(Update), exec(CheckFall), rotate the list (retail) */
    static void StartAll();                 /* fn_1_9B64 every m_proc = &procPlay; BalanceCom */
    static void JudgeAll();                 /* fn_1_9BFC AddWinner + mgCoinBonus (gm mode 3) */
    static void ResultAll();                /* fn_1_9D74 win / lose motions, the draw voices (gm mode 4) */
    static void DeleteAll();                /* fn_1_9EE4 gm on_close */
    static Vec* GetCenter(Vec* out);        /* fn_1_9F88 (center_obj) the survivors' head centroid */
    static int GetAliveNum();               /* fn_1_A0C4 */
    static int GetWinner();                 /* fn_1_A0D4 (camera) the survivor's number when exactly one, else -1 */
    CPlayer(int idx, CDorrie* dorrie);      /* fn_1_A164 */
    ~CPlayer();                             /* fn_1_A574 NON-virtual */
    static void Update(CPlayer* p);         /* fn_1_A67C */
    static void CheckFall(CPlayer* p);
    static void Reposition();               /* fn_1_AB34 */
    static void BalanceCom();               /* fn_1_AC88 the COM tie-breaker (list order, retail) */
    void procInit();                        /* fn_1_AE1C */
    void procIdle();                        /* fn_1_AE98 */
    void procPlay();                        /* fn_1_AED4 */
    void procFall();
    void procFloat();                       /* fn_1_B2D8 */
    void procJudge();                       /* fn_1_B478 */
    void procNone();                        /* fn_1_B4DC */
    void updatePos(bool reset);             /* fn_1_B4E0 */
    static bool IsPressA(int pad);          /* fn_1_B66C (unreferenced; inlined in getInput) */
    static bool ComPress(int dif);          /* fn_1_B6AC (unreferenced; inlined in getInput) */
    bool getInput();                        /* fn_1_B71C */
    void resetBeat();                       /* fn_1_B80C assert player.cpp:582 */
    void push(double a);                    /* fn_1_B8B8 */
    bool isOnDorrie();                      /* fn_1_B9D8 */
    void updateMarker();                    /* fn_1_B9F0 */
    Vec* getHeadPos(Vec* out);              /* fn_1_BA98 */
    void createMotions();                   /* fn_1_BB18 assert player.cpp:650 */
    void addMotion(u32 data);               /* fn_1_BC2C */
    void setMotion(int no, bool loop);      /* fn_1_BCA4 */
    float getMotionTime();                  /* fn_1_BDA4 (= m522 10160) */
    void vibrate(int kind);                 /* fn_1_BE10 */
    void playSE(int id);                    /* fn_1_BED0 */
    /* by value: retail copies the PTMF constant to a stack temporary before storing it */
    void setProc(ProcFunc proc) { m_proc = proc; }
    void setWait(int wait) { m_wait = wait; }

    /* 0x00 CLinkNode (TLinkItem) */
    /* 0x08 CModel base (CModel(charNo, 2)): ~CPlayer calls ~CModel with flag 0 (a base; a member gets -1) */
    ProcFunc m_proc;                /* 0x0C (12 bytes on CW) */
    int m_idx;                      /* 0x18 */
    int m_charNo;                   /* 0x1C GwPlayerConf.charNo */
    int m_padNo;                    /* 0x20 iscom ? -1 : pad_idx */
    int m_dif;                      /* 0x24 */
    int m_bias;                     /* 0x28 COM tie-break (signed) */
    int m_vibWait;                  /* 0x2C */
    int m_turnSec;                  /* 0x30 1 */
    double m_pushMax;               /* 0x38 170 */
    double m_pushStart;             /* 0x40 80 */
    double m_pushMin;               /* 0x48 -40 */
    CDorrie* m_dorrie;              /* 0x50 */
    int m_wait;                     /* 0x54 > 0 blocks input and falls */
    bool m_out;                     /* 0x58 */
    int m_beatCount;                /* 0x5C presses in the window (signed) */
    BeatRec m_beat_rec;             /* 0x60 (retail name: the assert text) FPS entries */
    Vec m_pos;                      /* 0x7C */
    Vec m_vel;                      /* 0x88 */
    double m_push;                  /* 0x98 */
    double m_pushSmooth;            /* 0xA0 */
    float m_rotY;                   /* 0xA8 degrees */
    std::vector<s16> m_motion_id;   /* 0xAC (retail name) */
    int m_motion;                   /* 0xB8 -1 */
    float m_motTime;                /* 0xBC */
};

} // namespace m537

#endif
