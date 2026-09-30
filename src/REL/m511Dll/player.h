#ifndef M511_PLAYER_H
#define M511_PLAYER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/tlink.h"
#include "REL/m511Dll/angle.h"
#include "REL/m511Dll/boatsplash.h"
#include "REL/m511Dll/boatshadow.h"
#include <memory>
#include <vector>

namespace m511 {

class CPlayer : public TLinkItem<CPlayer> {
public:
    typedef void (CPlayer::*ProcFunc)();
    enum { NUMBEROF_MOTION = 1 };

    static void GetStartPos(Vec* pos, int idx);  /* fn_1_FACC unreferenced (inlined in the ctor) */
    static void ShuffleStart();                  /* fn_1_FB50 on_setup: shuffles s_startSlot / s_comType */
    static void Close();                         /* fn_1_FC40 on_close: tail first */
    CPlayer(int idx);                            /* fn_1_FCE4 */
    ~CPlayer();                                  /* fn_1_10690 out-of-line (Close calls it) */
    s16 createMotion(int dataNum);               /* fn_1_107AC */
    static void UpdateAll();                     /* fn_1_10828 on_update: four walks, UpdateRank, rotate */
    static void SavePrev(CPlayer* p);            /* fn_1_108EC */
    static void UpdateRank();                    /* fn_1_10908 (retail tie bug kept) */
    static bool CheckGameEnd(bool deca);         /* fn_1_10DB4 */
    static void PlayWinnerFX2();                 /* fn_1_10FA4 after the winner message (same body) */
    static bool SetResult(bool deca);            /* fn_1_10FF0 true = draw */
    static void PlayLoseVoice();                 /* fn_1_110E0 */
    static void PlayWinnerFX();                  /* fn_1_11170 before the winner message */
    static int GetBestTime();                    /* fn_1_111BC min frames of human finishers, 18000 */
    static void StartWinCamera();                /* fn_1_11248 unreferenced */
    static void GetCameraPos(int idx, Vec* at, Vec* eye);      /* fn_1_112E0 camera follow */
    static void GetFrontCameraPos(int idx, Vec* at, Vec* eye); /* fn_1_1167C camera result */
    static void UpdateMain(CPlayer* p);          /* fn_1_11804 walk 2: proc, water, splash/shadow/wakes */
    static void UpdatePlayer(CPlayer* p);        /* fn_1_11ADC walk 3: hits, walls, rumble */
    void updateDisp();                           /* fn_1_11BFC */
    static void UpdateCourseThunk(CPlayer* p);   /* fn_1_11EA4 walk 4 */
    void UpdateCourse();                         /* fn_1_11ECC gates, goal, arrow, time */
    bool calcPush(Vec* a, Vec* b, Vec* pa, Vec* pb); /* fn_1_12570 unreferenced (inlined in hitCheck) */
    void hitCheck();                             /* fn_1_1295C boats, crates */
    void setMotion(int motion, bool once);       /* fn_1_133E8 */
    void procStart();                            /* fn_1_134DC */
    void procWin();                              /* fn_1_13554 */
    void procMain();                             /* fn_1_13630 */
    void updateThrottle();                       /* fn_1_13704 */
    void updateMove();                           /* fn_1_13794 retail computes a drift flag and drops it (r3 unset) */
    float ComDrive();                            /* fn_1_1402C -> stick */
    float AutoDrive();                           /* fn_1_14548 -> stick (finished boats) */
    void updateInput();                          /* fn_1_14A40 */
    bool checkWall();                            /* fn_1_14C1C */

    /* PTMF stores go through a by-value copy (three words to a stack temp, then to m_proc) */
    void setProc(ProcFunc proc) { m_proc = proc; }

    static TLinkList<CPlayer> playerList; /* bss AC4; its DestructorChain AB8 */

    /* 0x00 CLinkNode (through TLinkItem) */
    u8 m_unk08[0x48];           /* 0x08 never touched */
    ProcFunc m_proc;            /* 0x50 (12 bytes on CW) */
    int m_idx;                  /* 0x5C player 0..3 */
    int m_charNo;               /* 0x60 GwPlayerConf[i].charNo (used as s16) */
    int m_padNo;                /* 0x64 -1 for COM */
    int m_motion;               /* 0x68 -1 */
    int m_dif;                  /* 0x6C COM difficulty */
    float m_rotY;               /* 0x70 degrees, wrapped +-180 */
    float m_steer;              /* 0x74 */
    int m_stun;                 /* 0x78 crate stun frames */
    float m_throttle;           /* 0x7C 0..1 */
    int m_unk80;                /* 0x80 write-only */
    bool m_hit;                 /* 0x84 wall/boat hit this frame */
    bool m_accel;               /* 0x85 A / COM */
    bool m_brake;               /* 0x86 B / COM */
    Vec m_pos;                  /* 0x88 */
    Vec m_prevPos;              /* 0x94 */
    Vec m_vel;                  /* 0xA0 pos - prevPos */
    float m_speed;              /* 0xAC |vel.xz| / 100 */
    float m_kmh;                /* 0xB0 m_speed * 216 */
    int m_time;                 /* 0xB4 race frames, from 1 */
    int m_rank;                 /* 0xB8 */
    float m_stickSmooth;        /* 0xBC never read */
    float m_unkC0;              /* 0xC0 750, write-only */
    CModel m_boat;              /* 0xC4 s_boatModel[charNo] */
    CModel m_char;              /* 0xC6 CModel(charNo, 1) */
    bool m_showChar;            /* 0xC8 procWin */
    bool m_goal;                /* 0xC9 */
    float m_goalZ;              /* 0xCC pos.z at the goal (winner tie-break) */
    bool m_autoDrive;           /* 0xD0 */
    int m_gate;                 /* 0xD4 0..6 (7 after the CheckGameEnd goal clear: retail) */
    int m_hitTimer;             /* 0xD8 frames since the last hit, 60 */
    int m_gateRumble;           /* 0xDC */
    int m_engineSe[2];          /* 0xE0 CCameraObj::PlaySe handles */
    std::auto_ptr<CBoatSplash> m_splash;  /* 0xE8 */
    std::auto_ptr<CBoatShadow> m_shadow;  /* 0xEC */
    std::vector<s16> m_mot_id;            /* 0xF0 */
    std::auto_ptr<CBoatWake> m_wake[4];   /* 0xFC */
    int m_wakeTimer;            /* 0x10C */
    int m_wakeIdx;              /* 0x110 &3 */
};

} // namespace m511

#endif
