#ifndef M512_GAMEMASTER_H
#define M512_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"

namespace m512 {

class CRaceTimer;

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();
    /* prints "m512::CGameMaster::~CGameMaster()"; m_raceTimer is a CGameObject (CGameObject::Close frees it) */
    virtual ~CGameMaster();
    virtual void on_setup(Process_s* om); /* om unused */
    virtual void on_update();
    /* fn_1_66FC: the empty virtual with no caller (m536's on_draw; the name is ours) */
    virtual void on_draw();
    /* never returns: ends in for(;;) sleepThread(-1). The int is CSubThread's m_param (m501 convention). */
    virtual void thread_exec(CThreadParam param);
    /* fn_1_650C: finish message, then the record (normal mode, non-practice, improved only) */
    void finish();
    /* fn_1_65E4: ++m_frame; deca: race timer done or all 4 at the goal; else: CTimer done or anyone at the goal */
    bool checkEnd();
    /* fn_1_66A0: m_record = min(m_record, CPlayer::GetBestTime()) (unsigned compare); true when lowered */
    bool updateRecord();
    virtual void on_close();

    CTimer m_timer;          /* 0x358 CTimer(0); switched on only after frame 16200 */
    CRaceTimer* m_raceTimer; /* 0x35C score.cpp: the on-screen race clock (count-up) */
    int m_frame;             /* 0x360 play frames since mode 2 (not set by the ctor; signed ble) */
    u32 m_record;            /* 0x364 GWMgRecordGet(3): best race time in frames (cmplw) */
    bool m_deca;             /* 0x368 _CheckFlag(FLAG_INST_DECA) != 0 */
};

} // namespace m512

#endif
