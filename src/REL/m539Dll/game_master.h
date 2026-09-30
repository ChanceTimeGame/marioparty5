#ifndef M539_GAME_MASTER_H
#define M539_GAME_MASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"
#include "REL/m539Dll/a_set.h"
#include "REL/m539Dll/player.h"
#include "REL/m539Dll/score.h"
#include <memory>
#include <utility>

namespace m539 {

/* The two element sets (0x10, plain ::operator new; its ctor fully inlined into CGameMaster(), its dtor out of
 * line (fn_1_83FC) for ~auto_ptr<CObjSet>). Deleting it deletes every CScore (+8 first) then every CPlayer.
 * The name is ours. */
struct CObjSet {
    ASet<CPlayer> m_players; /* 0x0 sm_ptr bss A08 */
    ASet<CScore> m_scores;   /* 0x8 sm_ptr bss A04 */
};

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_8248 */
    /* fn_1_8A80: deletes the CModelMan (straight from ms_pointer) and the sets; prints nothing */
    virtual ~CGameMaster();
    virtual void on_setup(Process_s* om); /* fn_1_8B38 om unused */
    virtual void on_update();             /* fn_1_8C4C */
    /* fn_1_8DF0: std::sort's comparator, descending by score */
    static bool CompareScore(const std::pair<int, int>& a, const std::pair<int, int>& b);
    /* fn_1_8E10: ranks by score into GwPlayer[].mgCoinBonus (not in practice) and plays win/lose; false = draw
     * (the best score is 0). Retail returns an int (thread_exec's `!` has no clrlwi) */
    int setResult();
    /* fn_1_901C: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_947C CGameObject::Close() only */

    CTimer m_timer;                  /* 0x358 CTimer(0); 600 frames from mode 2 */
    CPlayer* m_player[4];            /* 0x35C not owned (m_set owns them) */
    std::auto_ptr<CObjSet> m_set;    /* 0x36C */
    CScore* m_score[4];              /* 0x370 not owned */
};

} // namespace m539

#endif
