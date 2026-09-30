#include "REL/m517Dll/config.h"
#include "REL/m517Dll/player.h"
#include "REL/m517Dll/gamemaster.h"
#include "REL/m517Dll/camera.h"
#include "REL/m517Dll/stage.h"
#include "REL/mgcpp/random.h"

namespace m517 {

CGameMaster::CGameMaster()
    : CSubThread(0x8000), m_set(new CObjSet), m_timer(new CTimer(0)), m_intro(0), m_paper(0), m_allCaught(false),
      m_hitOn(false)
{
}

CGameMaster::~CGameMaster() {}

/* every `new` keeps its result in a register only (the objects register themselves) */
void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    new CStage;
    new CCameraObj;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    for (int j = 0; j < 12; j++) {
        new CChoro;
    }
    new CChoroMan;
    m_paper.reset(new CPaperTex);
}

/* STUB-level DRAFT (fn_1_ADA8, 172 insns): the balls' / moles' walks read `next` through stack temporaries in
 * retail (the players' does not) */
void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    ASet<CBall>* balls = ASet<CBall>::instance();
    ASet<CChoro>* choros = ASet<CChoro>::instance();
    players->exec(&CPlayer::update);
    if (m_hitOn == true) {
        ForEachPair<CPlayer>(players, CPlayer::PushPair);
        ForEachCross<CBall, CPlayer>(balls, players, CBall::HitPlayer);
        ForEachCross<CChoro, CPlayer>(choros, players, CChoro::HitPlayer);
    }
    balls->exec(&CBall::Update);
    choros->exec(&CChoro::Update);
}

/* The flow (sheet §1.2). Never returns (for(;;) sleepThread(0)). */
void CGameMaster::thread_exec(CThreadParam param)
{
    int bgm = HuAudBGMPlay(0x53);
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    m_intro.reset(new CPlayerCarrier);
    SetAllIntro();
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    StartAll();
    m_intro.reset(0);
    m_hitOn = true;
    CGameObject::SetObjExecMode(2);
    m_timer->setParam(2700, 0, 0);
    m_timer->setModeOn(1);
    int unused = 0; /* B180: a dead local (retail) */
    while (!checkEnd()) {
        sleepThread(0);
    }
    FinishAll();
    HuAudSStreamFadeOut(bgm, 100);
    if (m_allCaught) {
        CCameraObj* camera = CSingleton<CCameraObj>::GetInstance();
        camera->SetFinal();
    }
    CGameObject::SetObjExecMode(3);
    m_timer->stopTimer();
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 120; i++) {
        sleepThread(0);
    }
    while (!IsAllIdle()) {
        sleepThread(0);
    }
    m_hitOn = false;
    CGameObject::SetObjExecMode(4);
    setResult();
    HuAudJinglePlay(0x79);
    CMinigameCore::StartWinnerGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(0);
    }
}

void CGameMaster::on_close()
{
    KillPlayers();
    KillEffects();
    KillChoros();
    CGameObject::Close();
}

/* the solo wins when every team player is caught (tested first: a same-frame time-out is the solo's too) */
bool CGameMaster::checkEnd()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    bool all = true;
    for (; p != end; p = p->next()) {
        if (!p->m_isSolo && p->m_out != 1) {
            all = false;
        }
    }
    if (all) {
        m_allCaught = true;
        return true;
    }
    if (m_timer->checkDone()) {
        m_allCaught = false;
        return true;
    }
    return false;
}

bool CGameMaster::IsAllIdle()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        if (p->m_immune > 0) {
            return false;
        }
    }
    return true;
}

/* the solo against the team: every team player wins on a time-out, caught or not (retail) */
void CGameMaster::setResult()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        if (m_allCaught) {
            if (p->m_isSolo) {
                p->SetResult(true);
            } else {
                p->SetResult(false);
            }
        } else {
            if (p->m_isSolo) {
                p->SetResult(false);
            } else {
                p->SetResult(true);
            }
        }
    }
}

void CGameMaster::FinishAll()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        p->Finish();
    }
}

void CGameMaster::SetAllIntro()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        p->Intro();
    }
}

void CGameMaster::StartAll()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        p->Start();
    }
    ASet<CChoro>* choros = ASet<CChoro>::instance();
    CChoro* c = choros->begin();
    CLinkNode* cend = choros->end();
    for (; c != cend; c = c->next()) {
        c->Stop();
    }
}

void CGameMaster::KillPlayers()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    while (p != end) {
        delete p;
        p = p->next();
    }
}

void CGameMaster::KillEffects()
{
    ASet<CBall>* balls = ASet<CBall>::instance();
    CBall* b = balls->begin();
    CLinkNode* end = balls->end();
    while (b != end) {
        delete b;
        b = b->next();
    }
}

void CGameMaster::KillChoros()
{
    ASet<CChoro>* choros = ASet<CChoro>::instance();
    CChoro* c = choros->begin();
    CLinkNode* end = choros->end();
    while (c != end) {
        delete c;
        c = c->next();
    }
}

} // namespace m517

template <> ASet<m517::CChoro>* ASet<m517::CChoro>::sm_ptr = 0;
template <> m517::CCameraObj* CSingleton<m517::CCameraObj>::ms_pointer = 0;
