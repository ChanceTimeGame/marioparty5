#ifndef M517_GAMEMASTER_H
#define M517_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/m517Dll/a_set.h"
#include <memory>

namespace m517 {

class CPlayer;
class CBall;
class CChoro;
class CPlayerCarrier;
class CPaperTex;

/* The three element sets (0x18, plain ::operator new; its ctor inlined into CGameMaster(), its dtor out of line
 * (weak, fn_1_A488) for ~auto_ptr<CObjSet>): destroyed moles (+0x10), balls (+0x08), players (+0x00; ~CPlayer
 * inlined). The name is m513's. */
struct CObjSet {
    ASet<CPlayer> m_players; /* 0x00 sm_ptr input.o .bss A08 */
    ASet<CBall> m_balls;     /* 0x08 sm_ptr effect.o .bss 0 */
    ASet<CChoro> m_choros;   /* 0x10 sm_ptr gamemaster.o .bss A1C */
};

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_A168 */
    virtual ~CGameMaster();               /* fn_1_AB90 */
    virtual void on_setup(Process_s* om); /* fn_1_AC64 om unused */
    virtual void on_update();             /* fn_1_ADA8 wakeupThread's result ignored */
    /* fn_1_B058: never returns (for(;;) sleepThread(0)). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_B2CC */
    bool checkEnd();                      /* fn_1_B310 all caught (solo wins) / time up */
    bool IsAllIdle();                     /* fn_1_B414 (a member: retail passes this, unused) */
    void setResult();                     /* fn_1_B4C4 */
    void FinishAll();                     /* fn_1_B5C0 every player Finish() */
    void SetAllIntro();                   /* fn_1_B660 every player Intro() */
    void StartAll();                      /* fn_1_B730 every player Start(), every mole Stop() */
    void KillPlayers();
    void KillEffects();                   /* fn_1_BA58 (the balls) */
    void KillChoros();                    /* fn_1_BAFC */

    std::auto_ptr<CObjSet> m_set;          /* 0x358 */
    std::auto_ptr<CTimer> m_timer;         /* 0x35C new CTimer(0): 45 s */
    std::auto_ptr<CPlayerCarrier> m_intro; /* 0x360 the ride-in carriers, dropped after the start message */
    std::auto_ptr<CPaperTex> m_paper;      /* 0x364 the paper cut-out textures */
    bool m_allCaught;                      /* 0x368 the solo won (checkEnd) */
    bool m_hitOn;                          /* 0x369 the hit walks run (modes 2..3) */
};

} // namespace m517

#endif
