#include "REL/m511Dll/config.h"
#include "REL/m511Dll/gamemaster.h"
#include "REL/m511Dll/score.h"
#include "REL/m511Dll/star.h"
#include "REL/m511Dll/kibako.h"
#include "REL/m511Dll/staryaji.h"
#include "REL/m511Dll/boatshadow.h"
#include "REL/m511Dll/camera.h"
#include "REL/m511Dll/water.h"
#include "REL/m511Dll/stage.h"
#include "REL/m511Dll/boat.h"
#include "REL/m511Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m511 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0)
{
    m_record = GWMgRecordGet(2);
    m_deca = (bool)(_CheckFlag(FLAG_INST_DECA) != 0);
}

CGameMaster::~CGameMaster()
{
    /* CW's __PRETTY_FUNCTION__ is exactly "m511::CGameMaster::~CGameMaster()", pooled before "%s\n" (.data 298) */
    printf("%s\n", __PRETTY_FUNCTION__);
}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    printf("%s\n", __PRETTY_FUNCTION__); /* .data 2BE */
    /* the objects register themselves (ObjectList, singletons, the lists) */
    new CEffTex;
    new CWaterRipple;
    new CWater;
    new CStage;
    new CCameraObj;
    new CScore(m_deca);
    m_raceTimer = new CRaceTimer(m_record, m_deca);
    new CStarYajiMan;
    new CBoatMan;
    CPlayer::ShuffleStart();
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    new CStarMan;
    new CKibakoMan;
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
}

/* The game flow: 0 intro, 1 start message, 2 race (the CTimer countdown appears only after 16200 frames; ends when
 * checkEnd says so), 3 finish + record, 4 result (normal mode only). Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CSingleton<CKibakoMan>::GetInstance()->Create();
    CMinigameCore::StartFadeIn();
    int se = HuAudFXPlay(0x6B8);
    HuAudFXPlay(0x6B9);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    int bgm = HuAudBGMPlay(0x35);

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    bool shown = false;
    CGameObject::SetObjExecMode(2);
    CStarYaji::ShowAll();
    m_frame = 0;
    m_timer.setParam(1800, 0, 0);
    m_timer.setPos(292.0f, 416.0f);
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
    CStarYaji::HideAll();
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
        CPlayer::PlayWinnerFX2();
        while (!CMinigameCore::CheckGameMes()) {
            sleepThread(0);
        }
    }
    HuAudFXFadeOut(se, 100);
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
            GWMgRecordSet(2, m_record);
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

} // namespace m511

template <> m511::CScore* CSingleton<m511::CScore>::ms_pointer = 0;
template <> m511::CRaceTimer* CSingleton<m511::CRaceTimer>::ms_pointer = 0;
template <> m511::CStarMan* CSingleton<m511::CStarMan>::ms_pointer = 0;
template <> m511::CKibakoMan* CSingleton<m511::CKibakoMan>::ms_pointer = 0;
template <> m511::CStarYajiMan* CSingleton<m511::CStarYajiMan>::ms_pointer = 0;
template <> m511::CEffTex* CSingleton<m511::CEffTex>::ms_pointer = 0;
template <> m511::CCameraObj* CSingleton<m511::CCameraObj>::ms_pointer = 0;
