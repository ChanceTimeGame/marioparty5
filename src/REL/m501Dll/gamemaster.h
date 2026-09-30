/* gamemaster.h -- m501::CGameMaster (gamemaster.cpp): the minigame root. CMinigameCore drives the
 * frame; the CSubThread runs the game flow (thread_exec) as a coroutine woken once per frame.
 * GC: CMinigameCore +0x000 (vptr +4), CSubThread +0x020 (secondary vptr), m_timer +0x358,
 * m_coneModel +0x35C, m_aisuModel +0x35E, m_aisuHandleMan +0x360; size 0x370.
 * Vtable (CW): primary {~, on_setup, on_update, on_close}, secondary {thunk ~, thunk thread_exec},
 * then thread_exec again (CW appends overrides of a non-primary base's virtuals). */
#ifndef M501_GAMEMASTER_H
#define M501_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/handle.h"

namespace m501 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();
    virtual ~CGameMaster();
    virtual void on_setup(Process_s* om); /* om unused */
    virtual void on_update();
    /* never returns: ends in for(;;) sleepThread(-1). symbols.txt: thread_exec__Q24m50111CGameMasterFv and
     * swapped @32@ thunk names (map.gamemaster.txt) */
    virtual void thread_exec(CThreadParam param);
    void newAisu();
    virtual void on_close();
    static CModel* GetConeModel();
    static CModel* GetAisuModel();

    CTimer m_timer;           /* 0x358 CTimer(0) */
    CModel m_coneModel;       /* 0x35C data 0x3B0006 */
    CModel m_aisuModel;       /* 0x35E data 0x3B0005 (display off; drawn by CAisu::drawHook) */
    CHandleMan m_aisuHandleMan; /* 0x360 CHandleMan(0x1000); CAisu::aisuHandleMan points here */
};

} // namespace m501

#endif
