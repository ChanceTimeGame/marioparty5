/* game_master.h -- m536::CGameMaster (game_master.cpp): the minigame root. CMinigameCore drives the frame;
 * the CSubThread runs the game flow (thread_exec) as a coroutine woken once per frame.
 * GC: CMinigameCore +0x000 (vptr +4), CSubThread +0x020 (secondary vptr), m_timer +0x358, m_frame +0x35C;
 * size 0x360 (ObjectSetup `li r3,0x360`).
 * Vtable __vt__Q24m53611CGameMaster (.data 238, 0x30): primary {~, on_setup, on_update, on_close},
 * secondary {thunk ~, thunk thread_exec}, then CW appends this class's own new virtual (on_draw, +0x28) and
 * the non-primary override thread_exec (+0x2C) in DECLARATION order (tested: test/exp/t3.cpp) -- so on_draw
 * is declared before thread_exec although its body comes after checkEnd. */
#ifndef M536_GAME_MASTER_H
#define M536_GAME_MASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"

namespace m536 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();
    /* prints "m536::CGameMaster::~CGameMaster()" */
    virtual ~CGameMaster();
    virtual void on_setup(Process_s* om); /* om unused */
    virtual void on_update();
    /* fn_1_6524: an empty virtual with no caller and no base slot; the name is ours (map.game_master.txt) */
    virtual void on_draw();
    /* never returns: ends in for(;;) sleepThread(-1). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    /* fn_1_64B8: ++m_frame; true when the timer ran out or at least 3 players are dead */
    bool checkEnd();
    virtual void on_close();

    CTimer m_timer; /* 0x358 CTimer(0); switched on only after frame 16200 */
    int m_frame;    /* 0x35C play frames since mode 2 (not set by the ctor) */
};

} // namespace m536

#endif
