/* gamemaster.cpp -- m521::CGameMaster (gamemaster.h). Retail order (master_camera_stage_score_debugline.md §2.4):
 * ctor, [Team() 11774, ~auto_ptr<CObjSet> 11780, ~CObjSet 117D8, the two empty MSL __vector_base accessors
 * 1194C / 11950, ~ASet<CPlayer> 11954, ~TLinkList<CPlayer> 11AB0: weak], dtor, on_setup, on_update, checkRoundEnd,
 * judge, showRoundResult, showWinner, playRound, thread_exec, on_close, [ForEachPair<CPlayer> 134A8, the MSL
 * std::sort<unsigned*> family 1353C..13F6C: weak], __sinit (triple + the two global stands), the two thunks.
 * EXACT-shaped (from finished overlays): the teardown chain from the a_set.h + CObjSet spelling (m513 / m568), the
 * dtor (= m522 CC64 / m532 8AA4), on_close (= m512 7B2C), ForEachPair (= m568 972C), the sort family (= m531 flow,
 * MSL <algorithm>), the thunks. From the asm (F4, all masked 0): the ctor, on_setup, on_update, the round helpers
 * (checkRoundEnd / judge / showRoundResult / showWinner are both emitted out of line and inlined in playRound /
 * thread_exec: they are defined above them), playRound, thread_exec. Team::seTimer is clock.h's CTickTimer: its
 * inlined Set() is what spills the 330 in playRound / thread_exec, its Tick() is on_update's countdown.
 * .data 4B0..568: the a_set strings (ctor :17), "dasu", on_update's PTMF, "sm_ptr != 0" (:36), the singleton strings
 * (judge's CScore :39), the hazusu / daiza names, thread_exec's two PTMFs, the vtable. .rodata 240..278.
 * .bss A18..A88: the triple, the two stands (+ their DestructorChain records), the module globals, judge's s_turn
 * (+ guard), then the weak template statics below (A70..A7C) and the sort's rot (+ guard). */
#include "REL/mgcpp/minigame.h"
#include "REL/m521Dll/gamemaster.h"
#include "REL/m521Dll/player.h"
#include "REL/m521Dll/score.h"
#include "REL/m521Dll/stage.h"
#include "REL/m521Dll/camera.h"
#include "REL/m521Dll/clock.h"
#include "REL/mgcpp/random.h"
#include <algorithm>

namespace m521 {

std::auto_ptr<CModel> s_standR;
std::auto_ptr<CModel> s_standB;
int s_round;
int s_roundRand;
bool s_draw;
CClock* s_clockR;
CClock* s_clockB;
CClock* s_clockQ;
bool s_inputOn;
/* A60: (dif + 1) / 4 summed and halved per team; never read (retail) */
static float s_teamLevel[2];


/* fn_1_11520: m_set's CObjSet() is inlined (ASet ctor, assert a_set.h:17); the stands through
 * the inlined auto_ptr::reset */
CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0), m_set(new CObjSet)
{
    CRandom::setSeed(OSGetTick());
    s_standR.reset(new CModel(0x4F0002U));
    s_standB.reset(new CModel(0x4F0003U));
    s_standR->shadowOnlyObjOn((char*)"dasu");
    s_standB->shadowOnlyObjOn((char*)"dasu");
    s_inputOn = false;
    m_team[0].busy = false;
    m_team[1].busy = false;
    m_team[0].seId = -1;
    m_team[1].seId = -1;
    m_team[0].stand = s_standR.get();
    m_team[1].stand = s_standB.get();
}

CGameMaster::~CGameMaster()
{
}

static inline void SetPartner(CPlayer* a, CPlayer* b)
{
    a->m_partner = b;
}

/* fn_1_11BA0 (sheet §1.2): the teams by GwPlayerConf.grp (MSL sort of (grp << 16) | player). SetPartner's two
 * inlined argument pairs are the four callee-saved temporaries (and the one spill) of the partner loop. */
void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    new CStage;
    new CCameraObj;
    new CScore;
    s_clockQ->SetTarget(11, 55);
    unsigned int key[4];
    for (int i = 0; i < 4; i++) {
        key[i] = (GwPlayerConf[i].grp << 16) | i;
    }
    std::sort(key, key + 4);
    s_teamLevel[0] = 0.0f;
    s_teamLevel[1] = 0.0f;
    for (int j = 0; j < 4; j++) {
        int pl = key[j] & 3;
        CPlayer* p = new CPlayer(pl, j);
        int team = j / 2;
        int k = j % 2;
        m_player[team][k] = p;
        m_playerNo[team][k] = pl;
        s_teamLevel[team] += (GwPlayerConf[pl].dif + 1) / 4.0f;
    }
    for (int t = 0; t < 2; t++) {
        SetPartner(m_player[t][0], m_player[t][1]);
        SetPartner(m_player[t][1], m_player[t][0]);
    }
    s_teamLevel[0] *= 0.5f;
    s_teamLevel[1] *= 0.5f;
    m_win[0] = 0;
    m_win[1] = 0;
}

/* fn_1_11E70 */
void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    players->exec(&CPlayer::Update);
    ForEachPair<CPlayer>(players, CPlayer::Collide);
    for (int t = 0; t < 2; t++) {
        if (m_team[t].seTimer.Tick()) {
            HuAudFXStop(m_team[t].seId);
            m_team[t].seId = -1;
        }
        if (m_team[t].busy && Hu3DMotionEndCheck(m_team[t].stand->id())) {
            HuAudFXPlay(t == 0 ? 0x72D : 0x72E);
            m_team[t].busy = false;
        }
    }
}

/* fn_1_1204C (unreferenced out-of-line copy; inlined in playRound). The last round (4) shows no result. */
bool CGameMaster::checkRoundEnd()
{
    if (m_timer.checkDone()) {
        return true;
    }
    if (s_clockR->IsDone() || s_clockB->IsDone()) {
        m_timer.setModeOff();
        int r = m_result = judge();
        s_inputOn = false;
        if (s_round < 4) {
            while (m_team[0].busy || m_team[1].busy) {
                sleepThread(0);
            }
            showRoundResult(r);
        }
        return true;
    }
    return false;
}

/* the guarded function-local static's initial value (retail: a dynamic init storing 0 behind the guard) */
static inline int TurnInit()
{
    return 0;
}

int CGameMaster::judge()
{
    int r = 0;
    if (s_clockR->IsDone()) {
        r |= 1;
    }
    if (s_clockB->IsDone()) {
        r |= 2;
    }
    if (r == 3) {
        static int s_turn = TurnInit();
        s_turn ^= 1;
        r = s_turn + 1;
    }
    if (r & 1) {
        m_win[0]++;
    }
    if (r & 2) {
        m_win[1]++;
    }
    CScore* score = CSingleton<CScore>::GetInstance();
    score->setValue(0, m_win[0]);
    score->setValue(1, m_win[1]);
    return r;
}

/* fn_1_122C4: bit 2 = the intro bell (thread_exec's constant 7). A team that just reached 3 gets no stand motion. */
void CGameMaster::showRoundResult(int r)
{
    int i;
    int t = 330;
    if (r & 4) {
        m_team[0].seId = HuAudFXPlay(0x72F);
        m_team[0].seTimer.Set(t);
    }
    for (i = 0; i < 2; i++) {
        if (m_win[i] >= 3) {
            continue;
        }
        if (r & (1 << i)) {
            HU3DMODELID id = m_team[i].stand->id();
            Hu3DMotionTimeSet(id, 0.0f);
            Hu3DMotionSpeedSet(id, 14.0f / 11.0f);
            HuAudFXPlay(i == 0 ? 0x72B : 0x72C);
            if (!(r & 4)) {
                m_team[i].seId = HuAudFXPlay(i == 0 ? 0x730 : 0x731);
                m_team[i].seTimer.Set(t);
                m_team[i].busy = true;
                m_player[i][0]->SetWin();
                m_player[i][1]->SetWin();
            }
        } else {
            m_player[i][0]->SetLose();
            m_player[i][1]->SetLose();
        }
    }
}

/* fn_1_12448 (unreferenced; inlined in thread_exec): open the winner's stand */
void CGameMaster::showWinner(int team)
{
    if (team == 0) {
        HU3DMODELID id = s_standR->id();
        Hu3DMotionTimeSet(id, 0.0f);
        HuAudFXPlay(0x72B);
        s_standR->shadowOnlyObjOn((char*)"hazusuR");
        s_standR->shadowOnlyObjOff((char*)"dasu");
        HU3DMODELID id2 = s_standR->id();
        Hu3DMotionForceSet(id2, (char*)"daizaR", 0x100, 0.0f);
    }
    if (team == 1) {
        HU3DMODELID id = s_standB->id();
        Hu3DMotionTimeSet(id, 0.0f);
        HuAudFXPlay(0x72C);
        s_standB->shadowOnlyObjOn((char*)"hazusuB");
        s_standB->shadowOnlyObjOff((char*)"dasu");
        HU3DMODELID id2 = s_standB->id();
        Hu3DMotionForceSet(id2, (char*)"daizaB", 0x100, 0.0f);
    }
    m_player[team][0]->SetOnStand();
    m_player[team][1]->SetOnStand();
}

/* fn_1_12640 (sheet §1.4): roll a target the display clock does not already show (after 1000
 * tries only the display-clock test counts), spin to it, then 15 s for the teams */
void CGameMaster::playRound()
{
    s_clockR->Lock();
    s_clockB->Lock();
    int n = 0;
    do {
        int h = CRandom::irandom() % 12;
        int m = CRandom::irandom() % 60;
        s_clockQ->SetTarget(h, m);
        s_clockR->SetTarget(h, m);
        s_clockB->SetTarget(h, m);
        if (++n > 1000 && !s_clockQ->IsTargetTooNear(60.0f)) {
            break;
        }
    } while (s_clockQ->IsTargetTooNear(60.0f) || s_clockR->IsHandNearTarget(20.0f) || s_clockB->IsHandNearTarget(20.0f));
    s_clockQ->SaveTarget();
    HuAudFXPlay(0x732);
    s_clockQ->Spin();
    while (!s_clockQ->IsIdle()) {
        sleepThread(0);
    }
    HuAudFXPlay(0x733);
    m_timer.setParam(900, 0, 0);
    m_timer.setModeOn(1);
    s_clockR->Unlock();
    s_clockB->Unlock();
    s_inputOn = true;
    while (!checkRoundEnd()) {
        sleepThread(0);
    }
    s_inputOn = false;
    s_clockR->Lock();
    s_clockB->Lock();
    m_timer.stopTimer();
    if (s_round < 4 && m_win[0] < 3 && m_win[1] < 3) {
        for (int i = 0; i < 180; i++) {
            sleepThread(0);
        }
    }
}

/* fn_1_12CA8 (sheet §1.3). Never returns. s_draw is `winner < 0` (srwi, no bool normalisation); the jingle
 * id is a bare ternary argument (no named local). */
void CGameMaster::thread_exec(CThreadParam param)
{
    int amb = HuAudFXPlay(0x72A);
    int bgm = HuAudSStreamPlay(0x51);
    showRoundResult(7);
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CGameObject::SetObjExecMode(2);
    for (int r = 0; r < 5; r++) {
        s_round = r;
        s_roundRand = CRandom::irandom();
        playRound();
        if (m_win[0] >= 3 || m_win[1] >= 3) {
            break;
        }
    }
    m_timer.stopTimer();
    HuAudFXStop(amb);
    CGameObject::SetObjExecMode(3);
    int winner = -1;
    if (m_win[0] != m_win[1]) {
        winner = m_win[0] > m_win[1] ? 0 : 1;
    }
    s_draw = winner < 0;
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    if (!s_draw) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        for (int i = 0; i < 60; i++) {
            sleepThread(0);
        }
        CSingleton<CCameraObj>::GetInstance()->startWinnerZoom(winner);
    }
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    players->exec(&CPlayer::ResetFacing);
    CGameObject::SetObjExecMode(4);
    if (!s_draw) {
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_WHITEFADE, 60);
        for (int i = 0; i < 60; i++) {
            sleepThread(0);
        }
        showWinner(winner);
        for (int i = 0; (double)i < 39.0; i++) {
            sleepThread(0);
        }
        for (int k = 0; k < 2; k++) {
            CMinigameCore::AddWinner(m_playerNo[winner][k]);
            m_player[winner][k]->PlayMotion4();
            m_player[winner ^ 1][k]->PlayMotion5();
        }
    } else {
        players->exec(&CPlayer::PlayMotion5);
    }
    HuAudJinglePlay(s_draw ? 0x7B : 0x79);
    CMinigameCore::StartWinnerGameMes();
    for (int i = 0; (double)i < 210.0; i++) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

/* the players die with m_set in the dtor */
void CGameMaster::on_close()
{
    CGameObject::Close();
}

} // namespace m521

template <> ASet<m521::CPlayer>* ASet<m521::CPlayer>::sm_ptr = 0;
template <> m521::CScore* CSingleton<m521::CScore>::ms_pointer = 0;
template <> m521::CStage* CSingleton<m521::CStage>::ms_pointer = 0;
template <> m521::CCameraObj* CSingleton<m521::CCameraObj>::ms_pointer = 0;
