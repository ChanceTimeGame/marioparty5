#ifndef M513_SCORE_H
#define M513_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m513 {

class CScore : public CGameObject, public CSingleton<CScore> {
public:
    enum { PLAYER_NUM = 4 };

    CScore(u32 record, bool deca);      /* fn_1_13174 normal mode: create() now */
    virtual ~CScore();                  /* fn_1_13304 kills the timers and icons (not the score windows: retail) */
    void create();                      /* fn_1_13430 */
    void createOnce();                  /* fn_1_13764 (unreferenced; inlined in on_new_mode(1)) */
    void setIcon(int i, int charNo, int x, int y); /* fn_1_13AA4 */
    void start();                       /* fn_1_13B98 (gamemaster; on_new_mode(2) again: retail) */
    void stopAll();                     /* fn_1_13C0C (player: the first finisher, normal mode) */
    void stopPlayer(int i);             /* fn_1_13C78 (player, deca) */
    void finish();                      /* fn_1_13CDC (gamemaster) stopF / mode pokes */
    bool isDone();                      /* fn_1_13D7C (gamemaster checkEnd, deca) */
    int getValue(int i);                /* fn_1_13E34 i ignored in normal mode */
    virtual void on_new_mode(int mode); /* fn_1_13EA4 */

    MGTIMER* m_timer;               /* 0x10 normal mode */
    MGTIMER* m_timers[PLAYER_NUM];  /* 0x14 deca */
    u32 m_record;                   /* 0x24 */
    bool m_created;                 /* 0x28 */
    bool m_deca;                    /* 0x29 */
    s16 m_icon[PLAYER_NUM];         /* 0x2A espEntry ids (deca) */
    s16 m_win[PLAYER_NUM];          /* 0x32 MgScoreWinCreate ids (deca; never killed: retail) */
};

} // namespace m513

#ifndef __MWERKS__
template <> m513::CScore* CSingleton<m513::CScore>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
