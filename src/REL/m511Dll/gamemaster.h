/* gamemaster.h -- m511::CGameMaster (gamemaster.cpp): the minigame root, m512's (master_camera_stage_score.md §2;
 * 12 of 13 functions m512 d <= 7). CMinigameCore drives the frame; the CSubThread runs the game flow (thread_exec).
 * GC: CMinigameCore +0x000 (vptr +4), CSubThread +0x020 (secondary vptr), m_timer +0x358, m_raceTimer +0x35C,
 * m_frame +0x360, m_record +0x364, m_deca +0x368; size 0x370 (ObjectSetup `li r3,0x370`).
 * Vtable __vt__Q24m51111CGameMaster (.data 304, 0x34) = m512's: primary {~, on_setup, on_update, on_close},
 * secondary {thunk ~, thunk thread_exec}, then on_draw and thread_exec in declaration order.
 * Includes minigame.h: gamemaster.o and objectsetup.o carry the 120/210/210 triple. */
#ifndef M511_GAMEMASTER_H
#define M511_GAMEMASTER_H

#include "REL/mgcpp/game.h"
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/subthread.h"
#include "REL/mgcpp/timer.h"

namespace m511 {

class CRaceTimer;

class CGameMaster : public CMinigameCore, public CSubThread {
public:
    CGameMaster();
    /* prints "m511::CGameMaster::~CGameMaster()" */
    virtual ~CGameMaster();
    /* fn_1_7DB4: prints __PRETTY_FUNCTION__, then creates every object (om unused) */
    virtual void on_setup(Process_s* om);
    virtual void on_update();
    /* fn_1_841C: the empty virtual with no caller (m512's on_draw) */
    virtual void on_draw();
    /* fn_1_7FE8: never returns (for(;;) sleepThread(-1)) */
    virtual void thread_exec(CThreadParam param);
    void finish();       /* fn_1_822C finish message, then the record (normal, non-practice, improved) */
    bool checkEnd();     /* fn_1_8304 */
    bool updateRecord(); /* fn_1_83C0 m_record = min(m_record, CPlayer::GetBestTime()) (unsigned) */
    virtual void on_close();

    CTimer m_timer;          /* 0x358 CTimer(0); switched on only after frame 16200 */
    CRaceTimer* m_raceTimer; /* 0x35C score.cpp: the on-screen race clock */
    int m_frame;             /* 0x360 play frames since mode 2 */
    u32 m_record;            /* 0x364 GWMgRecordGet(2): best human finish frames (cmplw) */
    bool m_deca;             /* 0x368 _CheckFlag(FLAG_INST_DECA) != 0 */
};

} // namespace m511

#endif
