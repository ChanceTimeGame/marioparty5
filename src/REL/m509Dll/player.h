/* player.h -- player.cpp's class (and, through stage.h, CStage for gamemaster/camera).
 * m509::CPlayer: one of the four maze racers. Human: analog stick only; COM: follows the maze's route codes.
 *   GC size 0x7C (gamemaster `li r3,0x7C`). No virtuals, no vptr: CLinkNode is at offset 0 on every ABI.
 * player.h does not include minigame.h (player.cpp includes it itself); camera.cpp and gamemaster.cpp include
 * this header. */
#ifndef M509_PLAYER_H
#define M509_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include <vector>
#include "REL/m509Dll/stage.h" /* CStage: its own TU (stage.cpp), declared for player.h's users */

namespace m509 {

/* degrees <-> 16-bit binary angle and the wrapped difference of two binary angles (m536/m512 player.h):
 * SubAngle/SubAngleMax (EE38/EEF0) are m536 9B50/9C08 exactly. */
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

/* Vec setter with DOUBLE components (m501/m536/m512 player.h) */
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

    static float SubAngle(float a, float b);               /* fn_1_EE38 unreferenced (= m536 9B50) */
    static float SubAngleMax(float a, float b, float max); /* fn_1_EEF0 unreferenced (= m536 9C08) */
    static void GetStartPos(Vec* pos, int idx);            /* fn_1_F054 unreferenced (inlined in the ctor) */
    static void Close();                                   /* fn_1_F0F4 CGameMaster::on_close (inline ~CPlayer) */
    CPlayer(int idx);                                      /* fn_1_F1FC */
    s16 addMotion(u32 dataNum);                            /* fn_1_F764 m_mot_id.push_back; returns the id */
    static void UpdateAll();                               /* fn_1_F7E0 CGameMaster::on_update */
    /* fn_1_F864: AddWinner for every player at the goal; s_winner = the only one (else 0); true if any */
    static bool CheckGoal();
    static void StartWin();                                /* fn_1_F924 camera on_new_mode(3) */
    static void ResetCells();                              /* fn_1_FA3C every m_cell = -1 (maze reshuffle) */
    void procWin();                                        /* fn_1_FAA0 */
    static bool SetResult();                               /* fn_1_FDB0 true (draw) when nobody reached the goal */
    void procWinPose();                                    /* fn_1_FF00 */
    void procLosePose();                                   /* fn_1_FF30 */
    static void CreateStartSpr();                          /* fn_1_FF60 CGameMaster::on_setup */
    static void GetBounds(Vec* out);                       /* fn_1_FFFC camera proc_main: centre x/z, y = extent */
    static void Update(CPlayer* p);                        /* fn_1_101E4 the list-walk callback */
    void PushPlayers();
    void setMotion(int no, bool once);                     /* fn_1_10608 */
    void setBlink(bool on);                                /* fn_1_106C8 unreferenced (inlined in procPlay) */
    void procInit();                                       /* fn_1_10774 */
    void procPlay();                                       /* fn_1_10850 */
    void setMotionWin();                                   /* fn_1_10B34 unreferenced: setMotion(3, true) */
    bool move(Vec* dir);                                   /* fn_1_10BD4 false when not moving */
    bool updateCell(float x, float z);                     /* fn_1_10F78 unreferenced (inlined in GetInput) */
    u8 queryMaze();                                        /* fn_1_11020 unreferenced (inlined in GetInput) */
    static u8 GetCellEdge(float x, float z);               /* fn_1_111C8 unreferenced (inlined in GetInput) */
    void GetInput(Vec* dir);                               /* fn_1_11394 */
    void keepInCell();                                     /* fn_1_11D1C unreferenced (inlined in Collide) */
    void Collide();                                        /* fn_1_11EA8 */
    void pushOut(float cx, float cz, float fx, float fz, int ix, int iz); /* fn_1_123E4 corner pillars */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPlayer> list; /* bss A4; its DestructorChain 98 */

    /* 0x00 CLinkNode (through TLinkItem) */
    ProcFunc m_proc;      /* 0x08 (12 bytes on CW; called with no __ptmf_test) */
    int m_idx;            /* 0x14 player 0..3 */
    int m_charNo;         /* 0x18 GwPlayerConf[i].charNo (used as s16 / u8) */
    int m_padNo;          /* 0x1C -1 for COM */
    bool m_unk20;         /* 0x20 0 in the ctor, write-only */
    int m_motion;         /* 0x24 current m_mot_id index, -1 */
    int m_dif;            /* 0x28 COM difficulty */
    float m_yaw;          /* 0x2C degrees */
    float m_targetYaw;    /* 0x30 atan2(dir.x, dir.z), degrees */
    float m_speed;
    int m_pushTimer;      /* 0x38 5 on the pushed player, -- while > 0; never read (retail) */
    int m_stun;           /* 0x3C trap stun frames (60) */
    int m_state;          /* 0x40 0 / 1 / 18, write-only */
    Vec m_pos;            /* 0x44 */
    Vec m_prevPos;        /* 0x50 */
    int m_cell;           /* 0x5C ix + 256 * iz, -1 = re-query */
    u8 m_comDir;          /* 0x60 COM route code (maze getCell & 7) */
    int m_comWait;        /* 0x64 COM dead-end hesitation frames */
    CModel m_model;       /* 0x68 CModel(charNo, 1) */
    bool m_goal;          /* 0x6A */
    bool m_blinkOff;      /* 0x6B model is DISPOFF from blinking */
    int m_frame;          /* 0x6C ++ per Update */
    std::vector<s16> m_mot_id; /* 0x70 six CharMotionCreate ids */
};

} // namespace m509

#endif
