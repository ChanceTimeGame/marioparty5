/* gamemaster.cpp -- m512::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread
 * (thread_exec) once per frame and then updates every object. Normal mode: the first player over the line
 * after 5 laps is the single AddWinner (CPlayer::CheckGameEnd); Decathlon: finish frames go to
 * GwPlayer[].mgScore (CPlayer::SetResult); a best-time record (id 3) in normal mode.
 * SKELETON: written from the W0 sheet (master_camera_stage_score.md §1.1, §3), m536's shape where it is
 * m536's; the fork verifies it. */
#include "REL/m512Dll/gamemaster.h"
#include "REL/m512Dll/score.h"
#include "REL/m512Dll/dust.h"
#include "REL/m512Dll/zako.h"
#include "REL/m512Dll/heiho.h"
#include "REL/m512Dll/stage.h"
#include "REL/m512Dll/camera.h"
#include "REL/m512Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m512 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0)
{
    m_record = GWMgRecordGet(3);
    m_deca = (bool)(_CheckFlag(FLAG_INST_DECA) != 0);
}

CGameMaster::~CGameMaster()
{
    /* CW's __PRETTY_FUNCTION__ is exactly "m512::CGameMaster::~CGameMaster()", pooled before "%s\n" (.data 210) */
    printf("%s\n", __PRETTY_FUNCTION__);
}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    Hu3DBGColorSet(0x1D, 0x80, 0xFD);
    /* the objects register themselves (ObjectList, singletons, the lists) */
    new CStage;
    new CCameraObj;
    new CScore(m_deca);
    m_raceTimer = new CRaceTimer(m_record, m_deca);
    CPlayer::ShuffleStart();
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    new CDustMan;
    new CHeihoMan;
    new CZakoMan;
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
}

/* The game flow: 0 intro camera, 1 start message, 2 race (the CTimer countdown appears only after 16200
 * frames; ends when checkEnd says so), 3 finish + record, 4 result (normal mode only). Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    int bgm = HuAudBGMPlay(0x55);
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
    bool draw = CPlayer::SetResult(m_deca);
    if (shown) {
        m_timer.stopTimer();
    }

    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    finish();

    CGameObject::SetObjExecMode(4);
    if (!m_deca) {
        HuAudJinglePlay(draw ? 0x7B : 0x79);
        if (draw) {
            CPlayer::PlayLoseVoice();
        } else {
            CPlayer::PlayWinnerFX();
        }
        CMinigameCore::StartWinnerGameMes();
        while (!CMinigameCore::CheckGameMes()) {
            sleepThread(0);
        }
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

void CGameMaster::finish()
{
    CMinigameCore::StartFinishGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    if (updateRecord() && !m_deca) {
        m_raceTimer->setRecord(m_record);
        if (!_CheckFlag(FLAG_MG_PRACTICE)) {
            GWMgRecordSet(3, m_record);
            CMinigameCore::StartRecordGameMes(m_record);
            while (!CMinigameCore::CheckGameMes()) {
                sleepThread(0);
            }
        }
    }
}

bool CGameMaster::checkEnd()
{
    m_frame++;
    if (m_deca) {
        bool end = true;
        if (!m_raceTimer->isDone() && !CPlayer::CheckGameEnd(m_deca)) {
            end = false;
        }
        return end;
    } else {
        bool end = true;
        if (!m_timer.checkDone() && !CPlayer::CheckGameEnd(m_deca)) {
            end = false;
        }
        return end;
    }
}

bool CGameMaster::updateRecord()
{
    bool updated = false;
    u32 best = CPlayer::GetBestTime();
    if (m_record > best) {
        m_record = best;
        updated = true;
    }
    return updated;
}

void CGameMaster::on_draw() {}

void CGameMaster::on_close()
{
    CPlayer::Close();
    CGameObject::Close();
}

} // namespace m512

/* The seven game singleton pointers: retail's weak template statics, kept by the linker in gamemaster.o
 * (the first TU in link order to instantiate them), at the end of its .bss in this order (singleton.h). */
template <> m512::CScore* CSingleton<m512::CScore>::ms_pointer = 0;
template <> m512::CRaceTimer* CSingleton<m512::CRaceTimer>::ms_pointer = 0;
template <> m512::CHeihoMan* CSingleton<m512::CHeihoMan>::ms_pointer = 0;
template <> m512::CZakoMan* CSingleton<m512::CZakoMan>::ms_pointer = 0;
template <> m512::CDustMan* CSingleton<m512::CDustMan>::ms_pointer = 0;
template <> m512::CStage* CSingleton<m512::CStage>::ms_pointer = 0;
template <> m512::CCameraObj* CSingleton<m512::CCameraObj>::ms_pointer = 0;
