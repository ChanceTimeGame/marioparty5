/* scorespr.h -- scorespr.cpp: m539::CScoreSprMan (a CGameObject that updates the list) and m539::CScoreSpr (a
 * floating MgScore number). DEAD in retail: nothing constructs a CScoreSpr (CScore::m_spr is never set), so the
 * manager updates an always-empty list. scorespr.cpp does not include minigame.h.
 * Class names are ours (W0 proposals). */
#ifndef M539_SCORESPR_H
#define M539_SCORESPR_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/tlink.h"
extern "C" {
#include "game/mg/score.h"
}

namespace m539 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CScoreSprMan> at +0x10, no members; size 0x10
 * (game_master `li r3,0x10`). Vtable data_584 {~, on_new_mode, on_update} (0x14). */
class CScoreSprMan : public CGameObject, public CSingleton<CScoreSprMan> {
public:
    CScoreSprMan();                      /* fn_1_EFF4 */
    virtual ~CScoreSprMan();             /* fn_1_F150 CScoreSpr::DeleteAll */
    virtual void on_new_mode(int mode);  /* fn_1_F220 */
    virtual void on_update();            /* fn_1_F238 CScoreSpr::UpdateAll */
};

class CScoreSpr;

/* The CScoreSpr list head (the name is ours). Not CLinkList: m539.o carries the framework's own weak ~CLinkList
 * (fn_1_6324), so a CLinkList here would share its name and retail's separate 22-insn copy (FA04) could not
 * exist. Not TLinkList<T>: a template's implicit dtor is emitted at the END of the TU; retail's FA04 sits BEFORE
 * __sinit, i.e. right after its first need -- execList's local `tmp` has this same type (m501 aisu's shape).
 * No vptr in CScoreSpr, so the (CScoreSpr*) casts do not adjust on any ABI (host rule §3.3). */
class CScoreSprList : public CLinkNode {
public:
    CScoreSpr* begin() { return (CScoreSpr*)CLinkNode::next(); }
    CScoreSpr* last() { return (CScoreSpr*)CLinkNode::prev(); }
    CLinkList* asList() { return static_cast<CLinkList*>(static_cast<CLinkNode*>(this)); }
};

/* GC: TLinkItem<CScoreSpr> +0, m_pos +8, m_value +0x14, m_count +0x18, m_score +0x1C, m_state +0x20 (12-byte
 * PTMF); size 0x2C (never allocated: the ctor writes up to +0x2B). No vptr. */
class CScoreSpr : public TLinkItem<CScoreSpr> {
public:
    typedef void (CScoreSpr::*StateFunc)();

    /* fn_1_F258 (dead): type 0 pops and holds, else rises and fades out; a failed MgScoreCreate deletes `this`
     * (retail returns the freed pointer) */
    CScoreSpr(const Vec* pos, int value, int type);
    ~CScoreSpr();                           /* fn_1_F40C MgScoreKill */
    static void DeleteAll();                /* fn_1_F480 */
    static void UpdateAll();                /* fn_1_F55C */
    static void Update(CScoreSpr* s);       /* fn_1_F58C (s->*s->m_state)(), no __ptmf_test */
    void statePop();                        /* fn_1_F5C4 type 0 */
    void stateRise();                       /* fn_1_F744 type != 0; deletes this at 60 frames */
    /* fn_1_F914: m501 CAisu::execAisuList's delete-safe walk (moves the list to a local, re-inserts each node
     * before calling fn). Takes CLinkList* (m501's shape): with CScoreSprList* the asList() re-cast cost retail
     * an extra register copy (60 vs 61 insns); UpdateAll passes list.asList(). */
    static void execList(CLinkList* list, void (*fn)(CScoreSpr*));

    static CScoreSprList list; /* bss A64; its DestructorChain A58 */

    Vec m_pos;          /* 0x08 */
    int m_value;        /* 0x14 */
    int m_count;        /* 0x18 frames */
    MGSCORE* m_score;   /* 0x1C */
    StateFunc m_state;  /* 0x20 */
};

} // namespace m539

#ifndef __MWERKS__
template <> m539::CScoreSprMan* CSingleton<m539::CScoreSprMan>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
