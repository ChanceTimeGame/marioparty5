/* score.h -- m521::CScore (score.cpp): the team points HUD (m536's hearts HUD with 2 entries and no character icon).
 * GC 0x4C (gamemaster `li r3,0x4C`): CGameObject +0x00, empty CSingleton<CScore> +0x10, m_active +0x10, m_entry[2]
 * +0x14 (stride 0x1C). Vtable data_7E4 {~, on_new_mode, on_update}. score.cpp includes no minigame.h. */
#ifndef M521_SCORE_H
#define M521_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m521 {

class CScore : public CGameObject, public CSingleton<CScore> {
public:
    struct Entry {
        HUSPRGRPID grp; /* 0x00 HuSprGrpCreate(8) */
        int value;      /* 0x04 points shown (signed) */
        int anim[3];    /* 0x08 per-lamp pop counter 0..18 */
        float x;        /* 0x14 */
        float y;        /* 0x18 */
    };

    CScore();                            /* fn_1_17F78 */
    void initTeam(int t);                /* fn_1_18360 */
    void setValue(int t, int value);     /* fn_1_1844C (gamemaster judge) */
    static void updateCount(Entry* e);   /* fn_1_1845C (= m536 DC04) */
    static void updateDisp(Entry* e);    /* fn_1_1851C (= m536 DCC4; its host fix) */
    virtual void on_update();            /* fn_1_186F0 */
    virtual void on_new_mode(int mode);  /* fn_1_18A10 */
    virtual ~CScore();                   /* fn_1_18A4C (kills no sprite: retail) */

    bool m_active;    /* 0x10 on_new_mode(2) */
    Entry m_entry[2]; /* 0x14 */
};

} // namespace m521

#ifndef __MWERKS__
template <> m521::CScore* CSingleton<m521::CScore>::ms_pointer; /* defined in gamemaster.cpp (A74) */
#endif

#endif
