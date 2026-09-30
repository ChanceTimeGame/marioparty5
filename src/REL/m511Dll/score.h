#ifndef M511_SCORE_H
#define M511_SCORE_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/mgcpp/singleton.h"

namespace m511 {

/* GC 0x1C (gamemaster `li r3,0x1C`): CGameObject +0, empty CSingleton<CRaceTimer> +0x10 (ms_pointer = gamemaster.o
 * bss A28), m_timer +0x10, m_record +0x14, m_created +0x18, m_deca +0x19. Vtable data_640
 * {~ 15B44, on_new_mode 15ED0, CGameObject::on_update (boat.o fn_1_710)}. */
class CRaceTimer : public CGameObject, public CSingleton<CRaceTimer> {
public:
    CRaceTimer(u32 record, bool deca);   /* fn_1_159B4 normal mode: create() now */
    virtual ~CRaceTimer();               /* fn_1_15B44 MgTimerKill if created */
    void create();                       /* fn_1_15C24 normal 0..18000 at (292, 70); deca 0..5400 at (292, 58) */
    void createDeca();                   /* fn_1_15D00 unreferenced (inlined in on_new_mode(1)) */
    void start();                        /* fn_1_15DE8 unreferenced (inlined in on_new_mode(2)) */
    void stop();                         /* fn_1_15E1C unreferenced (inlined in on_new_mode(3)) */
    bool isDone();                       /* fn_1_15E48 CGameMaster::checkEnd (deca) */
    int getValue();                      /* fn_1_15EA0 unreferenced */
    /* inline: CGameMaster::finish keeps the argument and the object in saved registers (m512) */
    void setRecord(u32 record) { MgTimerRecordSet(m_timer, record); }
    virtual void on_new_mode(int mode);  /* fn_1_15ED0 */

    MGTIMER* m_timer; /* 0x10 */
    u32 m_record;     /* 0x14 */
    bool m_created;   /* 0x18 */
    bool m_deca;      /* 0x19 */
};

/* GC 0x104 (gamemaster `li r3,0x104`): CGameObject +0, empty CSingleton<CScore> +0x10 (ms_pointer = gamemaster.o
 * bss A24), m_active +0x10, m_deca +0x11, m_show +0x12, m_entry[4] +0x14 (stride 0x3C). Vtable data_62C
 * {~ 16414, on_new_mode 16DE4, on_update 16B74}. */
class CScore : public CGameObject, public CSingleton<CScore> {
public:
    /* one player's HUD block. GC size 0x3C */
    struct Entry {
        HUSPRGRPID win;  /* 0x00 MgScoreWinCreate(120, 32) (never killed: retail) */
        HUSPRGRPID grp;  /* 0x02 HuSprGrpCreate(10): 0..4 frames, 5..9 pips */
        int charNo;      /* 0x04 initPlayer arg 2, never read */
        int pno;         /* 0x08 index into s_hudPos */
        int count;       /* 0x0C gates passed (signed) */
        int anim[5];     /* 0x10 per-pip pop counter 0..18 */
        int time;        /* 0x24 race frames (setValue) */
        float x;         /* 0x28 HUD position */
        float y;         /* 0x2C */
        float alpha;     /* 0x30 fade 0..1 */
        bool hasTimer;   /* 0x34 Decathlon: the finish time is shown */
        MGTIMER* timer;  /* 0x38 */
    };

    CScore(bool deca);                          /* fn_1_16040 */
    virtual ~CScore();                          /* fn_1_16414 timers and sprite groups (not the windows) */
    void initPlayer(int pno, int charNo);       /* fn_1_1652C CPlayer ctor */
    void setValue(int pno, int count, int time); /* fn_1_16604 CPlayer ctor / UpdateCourse; no range check */
    void updateCount(Entry* e);                 /* fn_1_16620 unreferenced (inlined in on_update) */
    void updateDisp(Entry* e);                  /* fn_1_166E0 called (not inlined) */
    void showTime(Entry* e);                    /* fn_1_169DC unreferenced (inlined) */
    void hideAll(Entry* e);                     /* fn_1_16B10 unreferenced (inlined) */
    virtual void on_update();                   /* fn_1_16B74 */
    virtual void on_new_mode(int mode);         /* fn_1_16DE4 */

    bool m_active;     /* 0x10 set by on_new_mode(2) */
    bool m_deca;       /* 0x11 */
    bool m_show;       /* 0x12 1; on_new_mode(3) clears it (normal mode): fade out */
    Entry m_entry[4];  /* 0x14 */
};

} // namespace m511

#ifndef __MWERKS__
template <> m511::CRaceTimer* CSingleton<m511::CRaceTimer>::ms_pointer; /* defined in gamemaster.cpp (.bss A28) */
template <> m511::CScore* CSingleton<m511::CScore>::ms_pointer; /* defined in gamemaster.cpp (.bss A24) */
#endif

#endif
