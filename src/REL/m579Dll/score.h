#ifndef M579_SCORE_H
#define M579_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"
extern "C" {
#include "game/mg/score.h"
}

namespace m579 {

class CScore : public CGameObject, public CSingleton<CScore> {
public:
    /* one player's counter. GC size 0x1C */
    struct Entry {
        HUSPRGRPID win;  /* 0x00 MgScoreWinCreate(0x50, 0x28) */
        HUSPRGRPID grp;  /* 0x02 HuSprGrpCreate(1): the character icon */
        MGSCORE* score;  /* 0x04 MgScoreCreate(0x960031, -1, 1), 2 digits */
        float alpha;     /* 0x08 fade-in 0 -> 1 (+0.1 a frame) */
        int chr;         /* 0x0C initPlayer: icon index (s_icon) */
        int value;       /* 0x10 the catch count shown */
        float x;         /* 0x14 */
        float y;         /* 0x18 */
    };

    CScore();                              /* fn_1_14208 chr / value / x / y left for initPlayer */
    void initPlayer(int i, int chr);       /* fn_1_14460 (player ctor) */
    void setValue(int i, int value);       /* fn_1_14590 (player ctor, procPlay) no range check */
    void update(Entry* e);                 /* fn_1_145A0 unreferenced out-of-line copy (inlined in on_update) */
    virtual void on_update();              /* fn_1_14684 */
    virtual void on_new_mode(int mode);    /* fn_1_147A4 mode 2: m_show (= m512 E65C / m536 E144) */
    virtual ~CScore();                     /* fn_1_147E0 (= m509 EA48) kills nothing */

    bool m_show;       /* 0x10 */
    Entry m_entry[4];  /* 0x14 */
};

} // namespace m579

#ifndef __MWERKS__
template <> m579::CScore* CSingleton<m579::CScore>::ms_pointer; /* defined in game_master.cpp (bss A2C) */
#endif

#endif
