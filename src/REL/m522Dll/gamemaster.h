#ifndef M522_GAMEMASTER_H
#define M522_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/mgcpp/handle.h"

namespace m522 {

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_CBEC (= m532 8A2C) */
    virtual ~CGameMaster();               /* fn_1_CC64 (= m532 8AA4) */
    virtual void on_setup(Process_s* om); /* fn_1_CCFC om unused; every `new` result is dropped */
    virtual void on_update();             /* fn_1_CDA8 (= m509 C4A8) */
    bool checkEnd();                      /* fn_1_CF6C */
    /* fn_1_D094: the extra virtual with no caller (m_timer.checkDone(); = m532 9584). DECLARED BEFORE thread_exec:
     * the appended vtable block is declaration order (+0x28 isTimeUp, +0x2C thread_exec); defined after it. */
    virtual bool isTimeUp();
    /* fn_1_CDE0: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param. */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_D0C0 (= m509 C8BC) */

    CTimer m_timer;          /* 0x358 CTimer(0): setParam(1800) = 30 s */
    CHandleMan m_handleMan;  /* 0x35C 0x1000 handles */
};

} // namespace m522

#endif
