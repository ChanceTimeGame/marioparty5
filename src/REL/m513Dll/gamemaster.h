#ifndef M513_GAMEMASTER_H
#define M513_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/m513Dll/a_set.h"
#include <memory>

namespace m513 {

class CPlayer;
class CLeaf;
class CHeiho;
class CKuribo;
class CHeihoCarrier;

/* The four element sets (0x20, plain ::operator new; its ctor inlined into CGameMaster(), its dtor out of line
 * (weak, fn_1_B7F4) for ~auto_ptr<CObjSet>): destroyed kuribos (+0x18), heihos (+0x10), leaves (+0x08), players
 * (+0x00). The name is ours (m539's). */
struct CObjSet {
    ASet<CPlayer> m_players; /* 0x00 sm_ptr bss A10 */
    ASet<CLeaf> m_leaves;    /* 0x08 sm_ptr bss 9F8 (leaf.o) */
    ASet<CHeiho> m_heihos;   /* 0x10 sm_ptr bss A14 */
    ASet<CKuribo> m_kuribos; /* 0x18 sm_ptr bss A0C */
};

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_B570 */
    virtual ~CGameMaster();               /* fn_1_C0A0 */
    virtual void on_setup(Process_s* om); /* fn_1_C150 om unused */
    virtual void on_update();             /* fn_1_C43C wakeupThread's result ignored (m539 style) */
    /* fn_1_C778: never returns (for(;;) sleepThread(0)). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    void PlayLoseVoice();                 /* fn_1_CA7C (a draw) */
    virtual void on_close();              /* fn_1_CB44 */
    bool checkEnd();                      /* fn_1_CB88 rotates the player list by one (retail) */
    void updateKuribo();                  /* fn_1_CD44 */
    bool IsAllIdle();                     /* fn_1_CE9C (a member: retail passes this, unused) */
    void checkRecord();                   /* fn_1_CF4C */
    void showRecord();                    /* fn_1_D034 */
    void SetAllIdle();                    /* fn_1_D1AC every m_proc = procStop */
    void SetAllPlay();                    /* fn_1_D27C every m_proc = procStart */
    void KillPlayers();
    void KillHeihos();                    /* fn_1_D4C8 */
    void KillKuribos();                   /* fn_1_D56C */
    void setResult();                     /* fn_1_D610 */

    std::auto_ptr<CObjSet> m_set;         /* 0x358 */
    std::auto_ptr<CHeihoCarrier> m_intro; /* 0x35C the Shy Guys' carrier, dropped after the start message */
    u32 m_record;                         /* 0x360 GWMgRecordGet(4) (frames) */
    bool m_deca;                          /* 0x364 _CheckFlag(FLAG_INST_DECA) */
    int m_winner;                         /* 0x368 player number, -1 = none */
    CTimer m_timer;                       /* 0x36C the 5:00 cap, shown after 4:30 */
    bool m_newRecord;                     /* 0x370 */
    int m_unk374;
};

} // namespace m513

#endif
