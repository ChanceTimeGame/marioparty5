/* score.h -- the HUD (score.cpp): m512::CRaceTimer (the race clock, an MGTIMER; name ours) and m512::CScore
 * (per player: a score window, the character icon and five lap pips; Decathlon: the frozen finish time).
 * score.cpp does not include minigame.h and has no __sinit; the singleton asserts are present for both.
 * .data: CScore's vtable (4C0) precedes CRaceTimer's (4D4) although CRaceTimer's text comes first. */
#ifndef M512_SCORE_H
#define M512_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m512 {

/* GC: CGameObject +0x00 (vptr +8), empty CSingleton<CRaceTimer> at +0x10, m_timer +0x10, m_record +0x14,
 * m_created +0x18, m_deca +0x19; size 0x1C (gamemaster `li r3,0x1C`). Vtable data_4D4
 * {~, on_new_mode, CGameObject::on_update}: on_update is not overridden. */
class CRaceTimer : public CGameObject, public CSingleton<CRaceTimer> {
public:
    CRaceTimer(u32 record, bool deca);   /* fn_1_D178 normal mode: create() now */
    virtual ~CRaceTimer();               /* fn_1_D308 MgTimerKill if created */
    /* fn_1_D3E8: normal RECORD timer 0..18000 at (292, 424); deca SCORE timer 0..5400 at (292, 432) */
    void create();
    void createDeca();                   /* fn_1_D4C4 if (m_deca) create(); inlined in on_new_mode(1) */
    void start();                        /* fn_1_D5AC MgTimerModeOnSet(0); inlined in on_new_mode(2) */
    void stop();                         /* fn_1_D5E0 stopF/mode pokes; inlined in on_new_mode(3) */
    bool isDone();                       /* fn_1_D60C CGameMaster::checkEnd (deca) */
    int getValue();                      /* fn_1_D664 unreferenced */
    /* inline: CGameMaster::finish keeps the argument and the object in saved registers (retail 656C/6570) */
    void setRecord(u32 record) { MgTimerRecordSet(m_timer, record); }
    virtual void on_new_mode(int mode);

    MGTIMER* m_timer; /* 0x10 */
    u32 m_record;     /* 0x14 the record, shown by the timer (lwz/stw only) */
    bool m_created;   /* 0x18 */
    bool m_deca;      /* 0x19 */
};

/* GC: CGameObject +0x00, empty CSingleton<CScore> at +0x10 (shares the offset with m_active), m_active +0x10,
 * m_deca +0x11, m_entry[4] +0x14 (stride 0x38); size 0xF4 (gamemaster `li r3,0xF4`). Vtable data_4C0. */
class CScore : public CGameObject, public CSingleton<CScore> {
public:
    /* one player's HUD block. GC size 0x38 */
    struct Entry {
        HUSPRGRPID win;  /* 0x00 MgScoreWinCreate(120, 32) (never killed: retail) */
        HUSPRGRPID grp;  /* 0x02 HuSprGrpCreate(11): 0 icon, 1..5 lap frames, 6..10 lap pips */
        int charNo;      /* 0x04 icon index (s_charIcon) */
        int pno;         /* 0x08 index into s_hudPos */
        int laps;        /* 0x0C laps done (signed) */
        int anim[5];     /* 0x10 per-pip pop counter 0..18 */
        int time;        /* 0x24 race frames (setValue) */
        float x;         /* 0x28 HUD position */
        float y;         /* 0x2C */
        bool hasTimer;   /* 0x30 Decathlon: the finish time is shown */
        MGTIMER* timer;  /* 0x34 */
    };

    CScore(bool deca);
    virtual ~CScore(); /* kills the timers and the sprite groups (not the score windows: retail) */
    /* fn_1_DC94: called by the CPlayer ctor with (player no, charNo) */
    void initPlayer(int pno, int charNo);
    /* fn_1_DDDC: CPlayer ctor and lap counter. No range check. */
    void setValue(int pno, int laps, int time);
    /* fn_1_DDF8..E1CC: on_update's per-entry steps (all inlined there; r3 unused) */
    void updateCount(Entry* e);
    void updateDisp(Entry* e);
    void showTime(Entry* e);
    void hideLaps(Entry* e);
    virtual void on_update();
    virtual void on_new_mode(int mode);

    bool m_active;     /* 0x10 set by on_new_mode(2) */
    bool m_deca;       /* 0x11 */
    Entry m_entry[4];  /* 0x14 */
};

} // namespace m512

#ifndef __MWERKS__
template <> m512::CRaceTimer* CSingleton<m512::CRaceTimer>::ms_pointer; /* defined in gamemaster.cpp */
template <> m512::CScore* CSingleton<m512::CScore>::ms_pointer; /* defined in gamemaster.cpp */
#endif

#endif
