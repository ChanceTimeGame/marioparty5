#ifndef M537_GAME_MASTER_H
#define M537_GAME_MASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"

namespace m537 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_83CC (= m536 ctor) */
    virtual ~CGameMaster();               /* fn_1_8438 (= m568 8798; no OSReport) */
    virtual void on_setup(Process_s* om); /* fn_1_84C4 om unused; every `new` result is dropped */
    virtual void on_update();             /* fn_1_8604 */
    bool checkEnd();                      /* fn_1_87C4 */
    /* fn_1_881C: the extra virtual with no caller (m_timer.checkDone(); = m522 D094). DECLARED BEFORE thread_exec:
     * the appended vtable block is declaration order (+0x28 isTimeUp, +0x2C thread_exec); defined after it. */
    virtual bool isTimeUp();
    /* fn_1_8640: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param. */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_8848 */

    CTimer m_timer; /* 0x358 CTimer(0): setParam(3600) = 60 s */
};

} // namespace m537

#endif
