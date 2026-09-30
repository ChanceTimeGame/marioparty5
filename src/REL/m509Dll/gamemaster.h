/* gamemaster.h -- m509::CGameMaster (gamemaster.cpp): the minigame root. CMinigameCore drives the frame;
 * the CSubThread runs the game flow (thread_exec) as a coroutine woken once per frame.
 * GC: CMinigameCore +0x000 (vptr +4), CSubThread +0x020 (secondary vptr), m_timer +0x358, m_random +0x35C;
 * size 0xD20 (ObjectSetup `li r3,0xD20`). Vtable __vt__Q24m50911CGameMaster (.data 32D4, 0x30 + pad):
 * m512's slots {~, on_setup, on_update, on_close}, secondary {thunk ~, thunk thread_exec}, then on_draw (+0x28)
 * and thread_exec (+0x2C), appended in DECLARATION order -- so on_draw is declared before thread_exec.
 * Includes minigame.h: gamemaster.o and objectsetup.o carry the 120/210/210 triple (sheet §5). */
#ifndef M509_GAMEMASTER_H
#define M509_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/mt19937.h"

namespace m509 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();
    /* prints "m509::CGameMaster::~CGameMaster()"; every game object is a CGameObject or a listed CPlayer
     * (on_close frees them) -- except the CMazeSelector singleton, which nothing frees (sheet §8.4) */
    virtual ~CGameMaster();
    virtual void on_setup(Process_s* om); /* om unused */
    virtual void on_update();
    /* fn_1_C8B8: the empty virtual with no caller (m536/m512's on_draw; the name is ours) */
    virtual void on_draw();
    /* never returns: ends in for(;;) sleepThread(-1). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    /* fn_1_C85C: m512's normal-mode branch without m_frame: CTimer done or anyone at the goal */
    bool checkEnd();
    virtual void on_close();

    CTimer m_timer;     /* 0x358 CTimer(0): 45 s (2700 frames), on from the start of mode 2 */
    CMT19937 m_random;  /* 0x35C seeded 5489 by its inline ctor and never used (dead; keeps the size 0xD20) */
};

} // namespace m509

#endif
