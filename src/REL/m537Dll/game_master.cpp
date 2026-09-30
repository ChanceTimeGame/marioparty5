#include "REL/m537Dll/game_master.h"
#include "REL/m537Dll/stage.h"
#include "REL/m537Dll/camera.h"
#include "REL/m537Dll/player.h"
#include "REL/m537Dll/center_obj.h"
#include "REL/mgcpp/random.h"

namespace m537 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0) {}

CGameMaster::~CGameMaster() {}

/* the shadow projector (the framework has no shadow unit in m537), then the objects; every `new` result is dropped
 * (they register themselves: ObjectList, singletons, the player list) */
void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* one 0x24 aggregate (rodata_200): pos, up, target */
    Vec sh[3] = { { 0.0f, 8000.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f, 0.0f } };
    Hu3DShadowCreate(30.0f, 6800.0f, 7200.0f);
    Hu3DShadowPosSet(&sh[0], &sh[1], &sh[2]);
    Hu3DShadowSizeSet(240);
    Hu3DShadowTPLvlSet(0.4f);
    new CStage;
    new CCameraObj;
    CPlayer::CreateAll();
    new CCenterObj;
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
    CCenterObj::Exec();
}

/* The game flow (sheet §1.2): fade-in, the camera intro, start message, play until checkEnd (60 s or <= 1 left),
 * finish (a fixed 180 frames, no message wait), result, the jingle (0x7B draw when all four are in, else 0x79),
 * s_mgWaitFinish frames, exit. No WipeCheck, no StartWinnerGameMes. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    HuAudFXPlay(0x7DC);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    int bgm = HuAudBGMPlay(0x36);

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(2);
    CPlayer::StartAll();
    m_timer.setParam(3600, 0, 0);
    m_timer.setModeOn(1);
    while (!checkEnd()) {
        sleepThread(0);
    }
    m_timer.stopTimer();

    CGameObject::SetObjExecMode(3);
    CPlayer::JudgeAll();
    CMinigameCore::StartFinishGameMes();
    HuAudSStreamFadeOut(bgm, 100);
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    CPlayer::ResultAll();
    int jingle;
    if (CPlayer::GetAliveNum() >= 4) {
        jingle = 0x7B;
    } else {
        jingle = 0x79;
    }
    HuAudJinglePlay(jingle);
    for (int i = 0; i < s_mgWaitFinish; i++) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

/* the m509 C85C pattern: the timer ran out or at most one player is left */
bool CGameMaster::checkEnd()
{
    bool end = true;
    if (!m_timer.checkDone() && CPlayer::GetAliveNum() > 1) {
        end = false;
    }
    return end;
}

bool CGameMaster::isTimeUp()
{
    return m_timer.checkDone();
}

/* CCenterObj is no CGameObject: deleted by hand through the unchecked pointer (its non-virtual dtor null-checks) */
void CGameMaster::on_close()
{
    CPlayer::DeleteAll();
    CGameObject::Close();
    delete CSingleton<CCenterObj>::GetInstancePtr();
}

} // namespace m537

template <> m537::CCenterObj* CSingleton<m537::CCenterObj>::ms_pointer = 0;
template <> m537::CCameraObj* CSingleton<m537::CCameraObj>::ms_pointer = 0;
template <> m537::CStage* CSingleton<m537::CStage>::ms_pointer = 0;
