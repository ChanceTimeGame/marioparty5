/* game_master.cpp -- m536::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread
 * (thread_exec) once per frame and then updates every object. BATTLE: no AddWinner; the result is the rank
 * CPlayer::SetRank writes into GwPlayer[].mgCoinBonus.
 * SKELETON: written from the W0 sheet (master_camera_stage_score.md §1.1, §3); the fork verifies it. */
#include "REL/m536Dll/game_master.h"
#include "REL/m536Dll/score.h"
#include "REL/m536Dll/killer.h"
#include "REL/m536Dll/gun.h"
#include "REL/m536Dll/killereff.h"
#include "REL/m536Dll/stage.h"
#include "REL/m536Dll/camera.h"
#include "REL/m536Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m536 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0) {}

CGameMaster::~CGameMaster()
{
    /* CW's __PRETTY_FUNCTION__ is exactly "m536::CGameMaster::~CGameMaster()", pooled before "%s\n" (.data 210) */
    printf("%s\n", __PRETTY_FUNCTION__);
}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, the lists) */
    new CKillerEffMan;
    new CStage;
    new CCloud;
    new CCameraObj;
    new CScore;
    new CKillerMan;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    new CGunMan;
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
}

/* The game flow: 0 intro camera, 1 start message, 2 play (up to 16200 frames without a timer, then a
 * 1800-frame countdown; ends early when 3 players are dead), 3 finish, 4 results. Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    int bgm = HuAudBGMPlay(0x54);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    bool shown = false;
    CGameObject::SetObjExecMode(2);
    m_frame = 0;
    m_timer.setParam(1800, 0, 0);
    while (!checkEnd()) {
        if (!shown && m_frame > 16200) {
            m_timer.setModeOn(1);
            shown = true;
        }
        sleepThread(0);
    }
    if (shown) {
        m_timer.stopTimer();
    }

    CPlayer::SetRank();
    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    bool draw = CPlayer::StartPlayerWin();
    HuAudJinglePlay(draw ? 0x7B : 0x79);
    for (int i = 0; i < s_mgWaitFinish; i++) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

bool CGameMaster::checkEnd()
{
    m_frame++;
    bool end = true;
    if (!m_timer.checkDone() && !CPlayer::CheckGameEnd()) {
        end = false;
    }
    return end;
}

void CGameMaster::on_draw() {}

void CGameMaster::on_close()
{
    CKiller::DeleteAll();
    CPlayer::Close();
    CGameObject::Close();
}

} // namespace m536

/* The seven game singleton pointers: retail's weak template statics, kept by the linker in game_master.o
 * (the first TU in link order to instantiate them), at the end of its .bss in this order (singleton.h). */
template <> m536::CScore* CSingleton<m536::CScore>::ms_pointer = 0;
template <> m536::CKillerMan* CSingleton<m536::CKillerMan>::ms_pointer = 0;
template <> m536::CGunMan* CSingleton<m536::CGunMan>::ms_pointer = 0;
template <> m536::CKillerEffMan* CSingleton<m536::CKillerEffMan>::ms_pointer = 0;
template <> m536::CCloud* CSingleton<m536::CCloud>::ms_pointer = 0;
template <> m536::CStage* CSingleton<m536::CStage>::ms_pointer = 0;
template <> m536::CCameraObj* CSingleton<m536::CCameraObj>::ms_pointer = 0;
