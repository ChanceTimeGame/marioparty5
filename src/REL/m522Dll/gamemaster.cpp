#include "REL/m522Dll/gamemaster.h"
#include "REL/m522Dll/sunfire.h"
#include "REL/m522Dll/stage.h"
#include "REL/m522Dll/camera.h"
#include "REL/m522Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m522 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0), m_handleMan(0x1000) {}

CGameMaster::~CGameMaster() {}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons); list order = Close's delete order */
    new CSunFireMan(&m_handleMan);
    new CStage;
    new CCameraObj;
    CPlayerBase::CreateAll();
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CPlayerBase::UpdateAll();
    CGameObject::UpdateAll();
}

void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    while (WipeCheck()) {
        sleepThread(0);
    }
    HuAudFXPlay(0x749);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    int bgm = HuAudBGMPlay(0x3A);

    CGameObject::SetObjExecMode(1);
    CPlayerBase::ReadyAll();
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(2);
    CPlayerBase::GoAll();
    m_timer.setParam(1800, 0, 0);
    m_timer.setModeOn(1);
    while (!checkEnd()) {
        sleepThread(0);
    }
    m_timer.stopTimer();

    CGameObject::SetObjExecMode(3);
    CPlayerBase::JudgeAll();
    CMinigameCore::StartFinishGameMes();
    HuAudSStreamFadeOut(bgm, 100);
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    CPlayerBase::ResultAll();
    CMinigameCore::StartWinnerGameMes();
    HuAudJinglePlay(0x79);
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

/* never while a block slides; at once when the team is out; else once every survivor is grounded and the timer is
 * done or no block is left (sheet §1.3) */
bool CGameMaster::checkEnd()
{
    if (!CSingleton<CStage>::GetInstance()->IsDropDone()) {
        return false;
    }
    int r = CPlayerBase::CheckEnd();
    if (r < 0) {
        return false;
    }
    if (r == 0) {
        return true;
    }
    bool end = true;
    if (!m_timer.checkDone()) {
        if (CSingleton<CStage>::GetInstance()->GetBlocksLeft() > 0) {
            end = false;
        }
    }
    return end;
}

bool CGameMaster::isTimeUp()
{
    return m_timer.checkDone();
}

void CGameMaster::on_close()
{
    CPlayerBase::DeleteAll();
    CGameObject::Close();
}

} // namespace m522

/* gamemaster.o's .bss weak template static (after the triple): A1C. Only camera.cpp and stage.cpp use it. */
template <> m522::CCameraObj* CSingleton<m522::CCameraObj>::ms_pointer = 0;
