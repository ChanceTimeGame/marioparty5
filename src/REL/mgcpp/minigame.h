/* minigame.h -- CMinigameCore (minigame.cpp + the class operator new/delete in om.cpp): the minigame
 * root object. One instance (CSingleton), created by ObjectSetup; it owns the omObj that drives
 * everything (ObjUpdate), the winner list, the start/finish/winner messages and the exit.
 * GC layout: +0x00 4 bytes never accessed, vptr +0x04, m_winner[4] +0x08, m_gameMesId +0x18, m_wait +0x1C;
 * size 0x20. */
#ifndef MGCPP_MINIGAME_H
#define MGCPP_MINIGAME_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/singleton.h"

/* Header file-statics with dynamic initialisers: retail has this 120/210/210 triple in the .bss and
 * __sinit of exactly the TUs that include this header (m501, objectsetup, gamemaster, aisu, asiato,
 * player) and in none of the others. Only the second one is read (StartWinnerGameMes: m_wait).
 * Keep them non-constant (an inline call), or CW folds them into .data. */
inline int MgWaitTimeShort() { return 120; }
inline int MgWaitTimeLong() { return 210; }
static int s_mgWaitStart = MgWaitTimeShort();  /* 120 */
static int s_mgWaitWinner = MgWaitTimeLong();  /* 210: StartWinnerGameMes m_wait */
static int s_mgWaitFinish = MgWaitTimeLong();  /* 210 */

class CMinigameCore : public CSingleton<CMinigameCore> {
public:
    int m_unk00; /* 0x00 never read or written; declared before the first virtual, so CW puts the vptr at +4 */

    CMinigameCore();
    virtual ~CMinigameCore();                /* 0x08 key function */
    virtual void on_setup(Process_s* om) = 0; /* 0x0C */
    virtual void on_update();                /* 0x10 */
    virtual void on_close() = 0;             /* 0x14 */

    void setup(int objMax, int prio);
    void actorSetup(int objMax, int prio); /* both arguments unused */
    static void ObjUpdate(omObj_s* obj);
    void update();
    static void MgExit(omObj_s* obj);
    static void AddWinner(int player);
    static bool CheckWinner(int player);
    static void StartStartGameMes();
    static void StartFinishGameMes();
    static bool CheckGameMes();
    static void StartWinnerGameMes();
    static void StartRecordGameMes(unsigned int value); /* FUi */
    static void StartFadeIn();
    static void StartFadeOut();
    static void ExitReq();

    /* om.cpp:24 / :31 */
    static void* operator new(size_t size);
    static void* operator new[](size_t size);
    static void operator delete(void* p);
    static void operator delete[](void* p);

    /* true once the m_wait countdown has run out (CheckGameMes: its own inlined bool; `<= 0`, retail rlwnm) */
    bool isWaitEnd() { return m_wait <= 0; }

    int m_winner[4];  /* 0x08 player index, -1 = empty */
    int m_gameMesId;  /* 0x18 GAMEMESID (s16) widened */
    int m_wait;       /* 0x1C countdown frames */
};

#ifndef __MWERKS__
template <> CMinigameCore* CSingleton<CMinigameCore>::ms_pointer; /* defined at the end of m501.cpp */
#endif

#endif
