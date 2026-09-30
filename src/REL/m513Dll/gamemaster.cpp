#include "REL/m513Dll/player.h"
#include "REL/m513Dll/gamemaster.h"
#include "REL/m513Dll/leaf.h"
#include "REL/m513Dll/heiho.h"
#include "REL/m513Dll/kuribo.h"
#include "REL/m513Dll/taimatsu.h"
#include "REL/m513Dll/powerind.h"
#include "REL/m513Dll/camera.h"
#include "REL/m513Dll/stage.h"
#include "REL/m513Dll/score.h"
#include "REL/mgcpp/random.h"

namespace m513 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_set(new CObjSet), m_intro(0), m_timer(0) {}

CGameMaster::~CGameMaster() {}

/* The Goombas' and torches' places: local aggregates (retail copies each .rodata literal 258 / 2B8 / 318 to the
 * stack: word-pair loops for the two 8-Vec tables, unrolled for the torches). Stack slots in reverse
 * declaration order (tpos 8, krot 56, kpos 152). */
void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    m_intro.reset(new CHeihoCarrier);
    m_record = GWMgRecordGet(4);
    m_deca = _CheckFlag(FLAG_INST_DECA);
    m_newRecord = false;
    new CScore(m_record, m_deca);
    new CPowerInd;
    new CStage;
    new CCameraObj;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i, m_deca);
        new CHeiho(i);
    }
    Vec kpos[8] = {
        { -287.5f, 40.0f, -1056.0f }, { -225.0f, 85.0f, -1125.0f }, { -162.5f, 40.0f, -1056.0f },
        { 62.5f, 40.0f, -1056.0f },   { -1056.0f, 40.0f, -287.5f }, { -1125.0f, 85.0f, -225.0f },
        { -1056.0f, 40.0f, -162.5f }, { -1056.0f, 40.0f, 62.5f },
    };
    Vec krot[8] = {
        { 0.0f, -45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f },
        { 0.0f, 135.0f, 0.0f }, { 0.0f, 135.0f, 0.0f }, { 0.0f, 135.0f, 0.0f }, { 0.0f, 135.0f, 0.0f },
    };
    int k;
    for (k = 0; k < 8; k++) {
        new CKuribo(&kpos[k], &krot[k]);
    }
    Vec tpos[4] = {
        { -1018.704f, 148.30652f, -48.94452f },
        { -1018.704f, 148.30652f, -400.0594f },
        { -398.4353f, 148.30652f, -978.414f },
        { -49.52887f, 148.30652f, -978.414f },
    };
    for (k = 0; k < 4; k++) {
        new CTaimatsu(&tpos[k]);
    }
    m_winner = -1;
}

/* the four instance() asserts first, then the walks (retail) */
void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    ASet<CLeaf>* leaves = ASet<CLeaf>::instance();
    ASet<CHeiho>* heihos = ASet<CHeiho>::instance();
    ASet<CKuribo>* kuribos = ASet<CKuribo>::instance();
    players->exec(&CPlayer::update);
    leaves->exec(&CLeaf::Exec);
    heihos->exec(&CHeiho::update);
    kuribos->exec(&CKuribo::update);
}

/* The flow (sheet §1.2). Never returns (for(;;) sleepThread(0): m512 used -1). */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    int bgm = HuAudBGMPlay(0x58);
    SetAllIdle();
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    for (int i = 0; (float)i < 60.0f; i++) {
        sleepThread(0);
    }
    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    m_intro.reset(0);
    SetAllPlay();
    CScore* score = CSingleton<CScore>::GetInstance();
    bool shown = false;
    CGameObject::SetObjExecMode(2);
    score->start();
    m_timer.setParam(1800, 0, 0);
    m_timer.setPos(286.0f, 416.0f);
    while (!checkEnd()) {
        updateKuribo();
        if (!shown && score->getValue(0) > 16200) {
            m_timer.setModeOn(1);
            shown = true;
        }
        sleepThread(0);
    }
    checkRecord();
    HuAudSStreamFadeOut(bgm, 100);
    CGameObject::SetObjExecMode(3);
    score->finish();
    if (!m_deca && shown == true) {
        m_timer.stopTimer();
    }
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 120; i++) {
        sleepThread(0);
    }
    showRecord();
    while (!IsAllIdle()) {
        sleepThread(0);
    }
    CGameObject::SetObjExecMode(4);
    if (!m_deca) {
        setResult();
        int jingle;
        if (m_winner != -1) {
            jingle = 0x79;
        } else {
            jingle = 0x7B;
        }
        HuAudJinglePlay((s16)jingle);
        CMinigameCore::StartWinnerGameMes();
        if (m_winner == -1) {
            PlayLoseVoice();
        }
        while (!CMinigameCore::CheckGameMes()) {
            sleepThread(0);
        }
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(0);
    }
}

/* a draw: every player's lose voice (always four players) */
void CGameMaster::PlayLoseVoice()
{
    s16 charNo[4];
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    int n = 0;
    for (; p != end; p = p->next(), n++) {
        charNo[n] = p->GetCharNo();
    }
    CharLoseVoicePlay(charNo[0], charNo[1], charNo[2], charNo[3]);
}

void CGameMaster::on_close()
{
    KillPlayers();
    KillHeihos();
    KillKuribos();
    CGameObject::Close();
}

bool CGameMaster::checkEnd()
{
    CScore* score = CSingleton<CScore>::GetInstance();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    p->unlink();
    p->insertBack(players);
    p = players->begin();
    CLinkNode* end = players->end();
    bool all = true;
    for (; p != end; p = p->next()) {
        if (p->m_turning > 0) {
            all = false;
        } else if (!p->m_finished) {
            all = false;
        } else if (!m_deca && m_winner == -1) {
            m_winner = p->GetIdx();
            return true;
        }
    }
    if (all == true) {
        return true;
    }
    if (m_deca && score->isDone()) {
        return true;
    }
    if (m_timer.checkDone()) {
        return true;
    }
    return false;
}

/* the Goombas get excited (mode 1) while any player is in the pump motion */
void CGameMaster::updateKuribo()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    ASet<CKuribo>* kuribos = ASet<CKuribo>::instance();
    CPlayer* p = players->begin();
    CLinkNode* pend = players->end();
    CKuribo* k = kuribos->begin();
    CLinkNode* kend = kuribos->end();
    int pump = 3;
    bool none = true;
    for (; p != pend; p = p->next()) {
        if (pump == p->getMotion()) {
            none = false;
        }
    }
    int mode = none == true ? 0 : 1;
    for (; k != kend; k = k->next()) {
        k->setMode(mode);
    }
}

bool CGameMaster::IsAllIdle()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        if (p->m_turning > 0) {
            return false;
        }
    }
    return true;
}

/* the non-finishers time out; a human finisher under the record sets a new one (unsigned compare) */
void CGameMaster::checkRecord()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        if (!p->m_finished) {
            p->timeUp();
        } else if (!p->IsCom()) {
            u32 t = p->GetTime();
            if (t < m_record) {
                m_record = t;
                m_newRecord = true;
            }
        }
    }
}

void CGameMaster::showRecord()
{
    ASet<CKuribo>* kuribos = ASet<CKuribo>::instance();
    CKuribo* k = kuribos->begin();
    CLinkNode* end = kuribos->end();
    for (; k != end; k = k->next()) {
        k->startEnd();
    }
    CScore* score = CSingleton<CScore>::GetInstance();
    if (m_newRecord && !m_deca) {
        for (int i = 0; i < 60; i++) {
            sleepThread(0);
        }
        u32 rec = m_record;
        MgTimerRecordSet(score->m_timer, rec);
        if (!_CheckFlag(FLAG_MG_PRACTICE)) {
            CMinigameCore::StartRecordGameMes(m_record);
            for (int i = 0; i < 180; i++) {
                sleepThread(0);
            }
        }
        GWMgRecordSet(4, m_record);
    }
}

void CGameMaster::SetAllIdle()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        p->Stop();
    }
}

void CGameMaster::SetAllPlay()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        p->Start();
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

void CGameMaster::KillHeihos()
{
    ASet<CHeiho>* heihos = ASet<CHeiho>::instance();
    CHeiho* h = heihos->begin();
    CLinkNode* end = heihos->end();
    while (h != end) {
        delete h;
        h = h->next();
    }
}

void CGameMaster::KillKuribos()
{
    ASet<CKuribo>* kuribos = ASet<CKuribo>::instance();
    CKuribo* k = kuribos->begin();
    CLinkNode* end = kuribos->end();
    while (k != end) {
        delete k;
        k = k->next();
    }
}

void CGameMaster::setResult()
{
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    CPlayer* p = players->begin();
    CLinkNode* end = players->end();
    for (; p != end; p = p->next()) {
        if (m_winner != -1) {
            if (m_winner == p->GetIdx()) {
                p->SetResult(true);
            } else {
                p->SetResult(false);
            }
        } else {
            p->SetResult(false);
        }
    }
}

} // namespace m513

template <> ASet<m513::CKuribo>* ASet<m513::CKuribo>::sm_ptr = 0;
template <> ASet<m513::CPlayer>* ASet<m513::CPlayer>::sm_ptr = 0;
template <> ASet<m513::CHeiho>* ASet<m513::CHeiho>::sm_ptr = 0;
template <> m513::CCameraObj* CSingleton<m513::CCameraObj>::ms_pointer = 0;
template <> m513::CStage* CSingleton<m513::CStage>::ms_pointer = 0;
template <> m513::CScore* CSingleton<m513::CScore>::ms_pointer = 0;
