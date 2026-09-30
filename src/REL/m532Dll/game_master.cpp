/* game_master.cpp -- m532::CGameMaster (game_master.h). Retail order: ctor, dtor, on_setup, on_update,
 * thread_exec, playRounds, isTimeUp, on_close, __sinit (triple + pair), the two thunks.
 * EXACT shapes adapted: on_update / on_close (m509 C4A8 / C8BC, masked 0 per the sheet), the ctor/dtor
 * (m512/m509 minus their extras, plus CHandleMan). thread_exec / playRounds drafted whole from the sheet
 * (master_camera_map_score_rumble.md §1.1-§1.2); the assert is retail's game_master.cpp:175 (keep the line). */
#include "REL/m532Dll/config.h"
#include "REL/m532Dll/game_master.h"
#include "REL/m532Dll/man_object.h"
#include "REL/m532Dll/ball.h"
#include "REL/m532Dll/camera.h"
#include "REL/m532Dll/man_map.h"
#include "REL/m532Dll/score.h"
#include "REL/m532Dll/man_referee.h"
#include "REL/m532Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m532 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0), m_handleMan(0x1000) {}

CGameMaster::~CGameMaster() {}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, the team lists) */
    new CObjectMan(&m_handleMan);
    new CBallMan;
    new CCameraObj;
    new CMapMan;
    new CScore;
    new CRefereeMan;
    CPlayer::Create();
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CPlayer::UpdateAll();
    CGameObject::UpdateAll();
}

/* seconds to frames at 60 fps: retail copies the product once more (fmr, 8C78), a nested inline's return */
inline float SecToFrames(float sec)
{
    return 60.0f * sec;
}

void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    while (!CSingleton<CRefereeMan>::GetInstance()->IsJumpStart()) {
        sleepThread(0);
    }
    int bgm = HuAudBGMPlay(0x32);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    for (int i = 0; !CMinigameCore::CheckGameMes(); i++) {
        if (i == s_mgWaitStart - (int)SecToFrames(CSingleton<CRefereeMan>::GetInstance()->GetWhistleTime())) {
            CSingleton<CRefereeMan>::GetInstance()->Whistle();
        }
        sleepThread(0);
    }

    int result = playRounds();
    m_timer.stopTimer();

    CGameObject::SetObjExecMode(3);
    CPlayer::GoHome();
    CMinigameCore::StartFinishGameMes();
    HuAudSStreamFadeOut(bgm, 100);
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    CSingleton<CRefereeMan>::GetInstance()->ShowResult(result);
    CPlayer::SetResult(result);
    CMinigameCore::StartWinnerGameMes();
    HuAudJinglePlay((result == 2 || result == 3) ? 0x7B : 0x79);
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

/* STUB detail (fn_1_8F60, 393 insns): the rounds. Retail's later GetInstance results go through two stack
 * slots each (r17..r31 all live, sheet §1.2). */
int CGameMaster::playRounds()
{
    int game_result = PLAYING_GAME;
    CGameObject::SetObjExecMode(2);
    for (int round = 1; round <= 5; round++) {
        if (round > 1) {
            CSingleton<CRefereeMan>::GetInstance()->Whistle();
            while (!CSingleton<CRefereeMan>::GetInstance()->IsMotionDone()) {
                sleepThread(0);
            }
        }
        m_timer.setParam(s_roundTime, 0, 0);
        m_timer.setModeOn(1);
        CSingleton<CMapMan>::GetInstance()->startSpin();
        int cue = (int)CRandom::frandom((float)s_reactTime, (float)s_roundTime);
        CPlayer::StartTiming(cue);
        while (!m_timer.checkDone() && !CPlayer::IsTimingDone()) {
            sleepThread(0);
        }
        m_timer.stopTimer();
        float pos = 0.0f;
        int team = CPlayer::Judge(&pos);
        while (!CSingleton<CMapMan>::GetInstance()->isBallAt(pos)) {
            sleepThread(0);
        }
        CSingleton<CMapMan>::GetInstance()->stopSpin();
        switch (team) {
        case 0:
            CSingleton<CScore>::GetInstance()->addPoint(0);
            break;
        case 1:
            CSingleton<CScore>::GetInstance()->addPoint(1);
            break;
        }
        CPlayer::Award(team);
        while (!CPlayer::IsBallTaken()) {
            sleepThread(0);
        }
        CSingleton<CRefereeMan>::GetInstance()->ShowResult(team);
        CSingleton<CScore>::GetInstance()->showPoints();
        while (!CPlayer::IsTimingDone() || !CSingleton<CRefereeMan>::GetInstance()->IsMotionDone()) {
            sleepThread(0);
        }
        for (int i = 0; i < 60; i++) {
            sleepThread(0);
        }
        CSingleton<CRefereeMan>::GetInstance()->Idle();
        game_result = CSingleton<CScore>::GetInstance()->checkResult(round);
        if (game_result != PLAYING_GAME || round >= 5) {
            break;
        }
        CPlayer::Rotate();
        while (!CPlayer::IsTimingDone()) {
            sleepThread(0);
        }
    }
    /* line padding: the assert below is retail's game_master.cpp:175 */



















    assert(game_result != PLAYING_GAME);
    return game_result;
}

bool CGameMaster::isTimeUp()
{
    return m_timer.checkDone();
}

void CGameMaster::on_close()
{
    CPlayer::DeleteAll();
    CGameObject::Close();
}

} // namespace m532

/* game_master.o's .bss weak template statics (the first TU in link order to instantiate them), after the
 * triple and the pair, in this address order (A24, A28, A2C). CCameraObj's is used only by camera.cpp. */
template <> m532::CRefereeMan* CSingleton<m532::CRefereeMan>::ms_pointer = 0;
template <> m532::CScore* CSingleton<m532::CScore>::ms_pointer = 0;
template <> m532::CCameraObj* CSingleton<m532::CCameraObj>::ms_pointer = 0;
