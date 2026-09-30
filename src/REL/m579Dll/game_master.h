#ifndef M579_GAME_MASTER_H
#define M579_GAME_MASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"

namespace m579 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_7650 (= m536 ctor) */
    virtual ~CGameMaster();               /* fn_1_76BC (= m537 8438; no OSReport) */
    virtual void on_setup(Process_s* om); /* fn_1_7748 om unused; every `new` result is dropped */
    virtual void on_update();             /* fn_1_78DC (= m509 C4A8 / m512 6324 / m522 CDA8) */
    /* fn_1_7AE0: m536's empty extra virtual (no caller). DECLARED BEFORE thread_exec (vtable +0x28 / +0x2C). */
    virtual void on_draw();
    /* fn_1_7914: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param. */
    virtual void thread_exec(CThreadParam param);
    bool checkEnd();                      /* fn_1_7AB4 non-virtual: m_timer.checkDone() (= m522 D094) */
    virtual void on_close();              /* fn_1_7AE4 (= m509 C8BC / m512 6700 / m522 D0C0) */

    CTimer m_timer; /* 0x358 CTimer(0): setParam(1800) = 30 s */
};

} // namespace m579

#endif
