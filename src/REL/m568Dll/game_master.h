#ifndef M568_GAME_MASTER_H
#define M568_GAME_MASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/m568Dll/a_set.h"
#include "REL/m568Dll/player.h"
#include "REL/m568Dll/tube.h"
#include "REL/m568Dll/octtree.h"
#include <memory>

namespace m568 {

struct CObjSet {
    ASet<CPlayer> m_players;     /* 0x00 sm_ptr bss A0C (game_master.o) */
    ASet<CTube> m_tubes;         /* 0x08 sm_ptr bss 9F8 (input.o) */
    ASet<CObstacle> m_obstacles; /* 0x10 sm_ptr bss 9F4 (input.o) */
};

/* fn_1_898C: game_master's tube-vs-obstacle callback (ForEachCross): both sides react to an overlap */
void HitTubeOct(CTube* t, CObstacle* o);
/* fn_1_8C24 (unreferenced; inlined into thread_exec): a team tube still in has passed z < -39000 */
bool IsGoal();
/* fn_1_8D04 (unreferenced; inlined 3x): every team tube is out */
bool IsAllOut();

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();                        /* fn_1_7F1C */
    virtual ~CGameMaster();               /* fn_1_8798 */
    virtual void on_setup(Process_s* om); /* fn_1_8824 om unused */
    virtual void on_update();             /* fn_1_8A08 returns early once the sub-thread has ended */
    /* fn_1_8DC8: never returns (for(;;) sleepThread(-1)). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    virtual void on_close();              /* fn_1_970C CGameObject::Close() only */

    std::auto_ptr<CObjSet> m_set; /* 0x358 */
};

} // namespace m568

#endif
