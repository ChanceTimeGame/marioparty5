#ifndef M532_GAME_MASTER_H
#define M532_GAME_MASTER_H

#include "REL/m532Dll/config.h"
#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/m532Dll/param.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/handle.h"

namespace m532 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_8A2C */
    virtual ~CGameMaster();               /* fn_1_8AA4 */
    virtual void on_setup(Process_s* om); /* fn_1_8B3C om unused; every `new` result is dropped */
    virtual void on_update();             /* fn_1_8C40 */
    /* fn_1_8C78: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param. */
    int playRounds();                     /* fn_1_8F60 the game result (score.h PLAYING_GAME) */
    /* fn_1_9584: the extra virtual with no caller (m_timer.checkDone(); the name is ours) */
    virtual bool isTimeUp();
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_95B0 */

    CTimer m_timer;          /* 0x358 CTimer(0): s_roundTime per round */
    CHandleMan m_handleMan;  /* 0x35C 0x1000 handles (CObjectMan / CObject) */
};

} // namespace m532

#endif
