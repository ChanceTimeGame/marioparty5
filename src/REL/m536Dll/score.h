/* score.h -- m536::CScore (score.cpp): the four-player lives HUD (character icon + three hearts per player).
 * GC: CGameObject +0x00, empty CSingleton<CScore> at +0x10 (shares the offset with m_active), m_active +0x10,
 * m_entry[4] +0x14 (stride 0x20); size 0x94 (game_master `li r3,0x94`). Vtable data_5A0.
 * score.cpp does not include minigame.h; the singleton asserts are present. */
#ifndef M536_SCORE_H
#define M536_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m536 {

class CScore : public CGameObject, public CSingleton<CScore> {
public:
    /* one player's HUD block. GC size 0x20 */
    struct Entry {
        HUSPRGRPID grp; /* 0x00 HuSprGrpCreate(8): 0 frame, 1 icon, 2..4 heart frames, 5..7 hearts */
        int charNo;     /* 0x04 icon index (s_charIcon) */
        int value;      /* 0x08 lives shown (signed compare) */
        int anim[3];    /* 0x0C per-heart pop counter 0..18 */
        float x;        /* 0x18 HUD position */
        float y;        /* 0x1C */
    };

    CScore();
    /* fn_1_DAC0: called by the CPlayer ctor with (player no, charNo) */
    void initPlayer(int pno, int charNo);
    /* fn_1_DBF4: m_entry[pno].value = value (CPlayer: lives at start and after a hit). No range check. */
    void setValue(int pno, int value);
    /* fn_1_DC04 / fn_1_DCC4: on_update's per-entry steps (both also inlined there) */
    void updateCount(Entry* e);
    void updateDisp(Entry* e);
    virtual void on_update();
    virtual void on_new_mode(int mode);
    virtual ~CScore(); /* the sprite groups/anims are not killed (retail: overlay reset frees them) */

    bool m_active;     /* 0x10 set by on_new_mode(2) */
    Entry m_entry[4];  /* 0x14 */
};

} // namespace m536

#ifndef __MWERKS__
template <> m536::CScore* CSingleton<m536::CScore>::ms_pointer; /* defined in game_master.cpp */
#endif

#endif
