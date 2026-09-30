#include "REL/m579Dll/game_master.h"
#include "REL/m579Dll/water.h"
#include "REL/m579Dll/effect.h"
#include "REL/m579Dll/stage.h"
#include "REL/m579Dll/camera.h"
#include "REL/m579Dll/score.h"
#include "REL/m579Dll/fishline.h"
#include "REL/m579Dll/zako.h"
#include "REL/m579Dll/watereff.h"
#include "REL/m579Dll/player.h"
#include "REL/mgcpp/random.h"

namespace m579 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0) {}

CGameMaster::~CGameMaster() {}

/* every `new` result is dropped (the objects register themselves: ObjectList, singletons, the player list); plain
 * ::operator new with the CW null check. No shadow here (the stage ctor sets it up). */
void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    new CWater;
    new CEffect;
    new CStage;
    new CCameraObj;
    new CScore;
    new CFishLineMgr;
    new CZakoMan;
    new CWaterEff;
    new CJugem;
    CharEffectLayerSet(3);
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
}

/* The game flow (sheet §1.2): fade-in, BGM before the intro wait (m536 order), start message, 30 s of play (the timer
 * is the only end), JudgeAll (AddWinner), the winner zoom, finish (fade-out before the message), 180 frames, the
 * result poses and the jingle (0x7B only when nobody won), the winner message, exit. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    int bgm = HuAudBGMPlay(0x4D);
    HuAudFXPlay(0x95E);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(2);
    m_timer.setParam(1800, 0, 0);
    m_timer.setModeOn(1);
    m_timer.setPos(292.0f, 416.0f);
    while (!checkEnd()) {
        sleepThread(0);
    }
    m_timer.stopTimer();
    CPlayer::JudgeAll();
    CPlayer::FinishAll();

    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    bool lose = CPlayer::ResultAll();
    int jingle;
    if (lose) {
        jingle = 0x7B;
    } else {
        jingle = 0x79;
    }
    HuAudJinglePlay(jingle);
    CMinigameCore::StartWinnerGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

bool CGameMaster::checkEnd()
{
    return m_timer.checkDone();
}

void CGameMaster::on_draw() {}

/* every other object is a CGameObject (CGameObject::Close deletes them) */
void CGameMaster::on_close()
{
    CPlayer::Close();
    CGameObject::Close();
}

} // namespace m579

template <> m579::CWaterEff* CSingleton<m579::CWaterEff>::ms_pointer = 0;
template <> m579::CFishLineMgr* CSingleton<m579::CFishLineMgr>::ms_pointer = 0;
template <> m579::CScore* CSingleton<m579::CScore>::ms_pointer = 0;
template <> m579::CStage* CSingleton<m579::CStage>::ms_pointer = 0;
