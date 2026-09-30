/* gamemaster.h -- m521::CGameMaster (gamemaster.cpp): the minigame root. CMinigameCore drives the frame; the
 * CSubThread runs the flow (thread_exec): up to 5 rounds (first to 3), each rolling a target time on the display
 * clock, 15 s for the teams to set it (playRound); the winner team zoom and result.
 * GC 0x3B0 (ObjectSetup `li r3,0x3B0`): CMinigameCore +0x000 (vptr +4), CSubThread +0x020, m_timer +0x358, m_win
 * +0x35C, m_playerNo +0x364, m_result +0x374, m_player +0x378, m_set +0x388, m_team +0x38C (2 x 0x10), pad 0x3AC.
 * Vtable __vt__Q24m52111CGameMaster (.data 538, 0x2C + pad): primary {~, on_setup, on_update, on_close}, secondary
 * {thunk ~, thunk thread_exec}, then thread_exec appended. NO extra virtual (m501 / m513 / m568 layout).
 * Includes minigame.h (gamemaster.o and objectsetup.o carry the triple), mgcpp headers, a_set.h and clock.h
 * (CTickTimer): objectsetup.o has no .data. The module globals gamemaster defines (read by clock / driver / player / stage) are
 * declared here. Names ours (sheet §2). */
#ifndef M521_GAMEMASTER_H
#define M521_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/model.h"
#include "REL/m521Dll/a_set.h"
#include "REL/m521Dll/clock.h"
#include <memory>

namespace m521 {

class CPlayer;
class CClock;

extern std::auto_ptr<CModel> s_standR; /* A30 0x4F0002 */
extern std::auto_ptr<CModel> s_standB; /* A40 0x4F0003 */
extern int s_round;                    /* A44 0..4 */
extern int s_roundRand;                /* A48 CRandom::irandom() per round: driver reads bits 0/1 as the team role bits */
extern bool s_draw;                    /* A4C (player) */
extern CClock* s_clockR;               /* A50 set by the CStage ctor */
extern CClock* s_clockB;               /* A54 */
extern CClock* s_clockQ;               /* A58 the display clock */
extern bool s_inputOn;                 /* A5C the round runs (clock Rotate, driver Get) */

/* the one element set (8 bytes, plain ::operator new; ctor inlined into CGameMaster(), dtor weak 117D8 for
 * ~auto_ptr<CObjSet>). The name is ours (m539's). */
struct CObjSet {
    ASet<CPlayer> m_players; /* 0x00 sm_ptr bss A70 */
};

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    /* one team's stand state (0x10; element ctor 11774 weak: seTimer = 0 only). seTimer is clock.h's CTickTimer
     * (F4: its inlined Set() decides playRound / thread_exec's spills; Tick() is on_update's countdown), which is
     * why this header includes clock.h. */
    struct Team {
        Team() {}
        bool busy;     /* 0x0 stand motion running */
        int seId;      /* 0x4 -1 = none */
        CTickTimer seTimer; /* 0x8 frames to HuAudFXStop */
        CModel* stand; /* 0xC s_standR / s_standB */
    };

    CGameMaster();                        /* fn_1_11520 */
    virtual ~CGameMaster();               /* fn_1_11B08 (= m522 CC64 / m532 8AA4) */
    virtual void on_setup(Process_s* om); /* fn_1_11BA0 */
    virtual void on_update();             /* fn_1_11E70 */
    bool checkRoundEnd();                 /* fn_1_1204C (unreferenced out-of-line copy; inlined in playRound) */
    int judge();                          /* fn_1_1214C function-local static s_turn (A68 / guard A6C) */
    void showRoundResult(int r);          /* fn_1_122C4 */
    void showWinner(int team);            /* fn_1_12448 (unreferenced; inlined in thread_exec) */
    void playRound();                     /* fn_1_12640 */
    /* fn_1_12CA8: never returns (for(;;) sleepThread(-1)) */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_13488 CGameObject::Close() only */

    CTimer m_timer;           /* 0x358 CTimer(0): 15 s per round */
    int m_win[2];             /* 0x35C points red / blue */
    int m_playerNo[2][2];     /* 0x364 [team][k] player number */
    int m_result;             /* 0x374 last judge() (write-only) */
    CPlayer* m_player[2][2];  /* 0x378 */
    std::auto_ptr<CObjSet> m_set; /* 0x388 */
    Team m_team[2];           /* 0x38C */
};

} // namespace m521

#endif
