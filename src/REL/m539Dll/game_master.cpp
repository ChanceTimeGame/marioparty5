/* game_master.cpp -- m539::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread
 * (thread_exec) once per frame, then updates every object, player and board. BATTLE: no AddWinner.
 * Retail order: ctor, [~auto_ptr<CObjSet>, ~CObjSet, two empty MSL helpers, ~auto_ptr<CDrum>, ~ASet<CScore>,
 * ~TLinkList<CScore>, ~ASet<CPlayer>, ~TLinkList<CPlayer>], dtor, on_setup, on_update, CompareScore, setResult,
 * thread_exec, on_close, [std::sort, __median_of_3, __selection_sort], __sinit, the two thunks.
 * Fork F4: every function written whole and checked (OUT.md); ~CObjSet needs the MSL cap() change. */
#define M539_DRUM_INCOMPLETE
#include "REL/m539Dll/game_master.h"
#include "REL/m539Dll/drum.h"
#include "REL/m539Dll/camera.h"
#include "REL/m539Dll/man_map.h"
#include "REL/m539Dll/scorespr.h"
#include "REL/mgcpp/random.h"
#include <algorithm>

namespace m539 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0), m_set(new CObjSet)
{
    CRandom::setSeed(OSGetTick());
    new CModelMan;
}

CGameMaster::~CGameMaster()
{
    delete CModelMan::GetInstancePtr();
}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, the sets) */
    new CCameraObj;
    new CMapMan;
    new CScoreSprMan;
    for (int i = 0; i < 4; i++) {
        CScore* s = m_score[i] = new CScore(i);
        m_player[i] = new CPlayer(i, s);
    }
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    players->exec(&CPlayer::update);
    ASet<CScore>* scores = ASet<CScore>::instance();
    scores->exec(&CScore::update);
}

bool CGameMaster::CompareScore(const std::pair<int, int>& a, const std::pair<int, int>& b)
{
    return a.second > b.second;
}

/* retail reads the score through an inline accessor (its own non-volatile temporaries: `lwzx r23; lwz r22,
 * 0xB0(r23); mr r21,r22`, frame 0x60); a direct `m_score[i]->m_score` is 3 registers and 16 bytes smaller.
 * Name ours; probably a CScore member in retail (score.h is F2's, so it stays file-local here). */
static inline int GetScore(CScore* s)
{
    return s->m_score;
}

int CGameMaster::setResult()
{
    std::pair<int, int> tbl[4];
    for (int i = 0; i < 4; i++) {
        tbl[i].first = i;
        tbl[i].second = GetScore(m_score[i]);
    }
    std::sort(tbl, tbl + 4, CompareScore);
    if (tbl[0].second == 0) {
        for (int i = 0; i < 4; i++) {
            if (!_CheckFlag(0x1000F)) {
                GwPlayer[i].mgCoinBonus = 3;
            }
            CharFXPlay(GwPlayerConf[i].charNo, 0x200);
            m_player[i]->setLose();
        }
        return 0;
    }
    int top = tbl[0].second;
    int prev = top;
    int rank = 0;
    for (int i = 0; i < 4; i++) {
        int no = tbl[i].first;
        if (top == tbl[i].second) {
            m_player[no]->setWin();
        } else {
            m_player[no]->setLose();
        }
        if (prev != tbl[i].second) {
            prev = tbl[i].second;
            rank++;
        }
        if (!_CheckFlag(0x1000F)) {
            GwPlayer[no].mgCoinBonus = rank;
        }
    }
    return 1;
}

/* The game flow: 0 fade-in (the camera split ends it), 1 start message, 2 play (600 frames, or until every
 * board has stopped its 8 reels), 3 finish + the per-line tally, 4 result. Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    int bgm = HuAudSStreamPlay(0x12);
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
    m_timer.setParam(600, 0, 0);
    m_timer.setModeOn(1);
    for (;;) { /* retail tests at the top and branches back (not a rotated while) */
        if (m_timer.checkDone() || CScore::IsAllStopped()) {
            break;
        }
        sleepThread(0);
    }
    m_timer.stopTimer();
    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 108.0; i++) {
        sleepThread(0);
    }
    ASet<CScore>* set = ASet<CScore>::instance();
    set->exec(&CScore::finishA);
    set->exec(&CScore::finishB);
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    for (int i = 0; i < 48.0; i++) {
        sleepThread(0);
    }
    for (int line = 0; line < 8; line++) {
        int sum = 0;
        for (int k = 0; k < 4; k++) {
            sum += m_score[k]->checkLine(line);
        }
        if (sum != 0) {
            for (int n = 0; n < 30.0f; n++) {
                sleepThread(0);
            }
        }
    }
    HuAudFXPlay(0x7FA);
    for (int i = 0; i < 90.0; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    bool draw = !setResult();
    HuAudJinglePlay(draw ? 0x7B : 0x79);
    for (int n = s_mgWaitFinish; n != 0; n--) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

void CGameMaster::on_close()
{
    CGameObject::Close();
}

} // namespace m539

/* The game_master.o .bss template statics (retail's weak statics, kept in the first TU in link order to
 * instantiate them), after the header triple, in this address order (A04..A14); std::sort's function-local
 * rotor + guard (A18/A1C) follow them. CModelMan's (9F0) is drum.o's. */
template <> ASet<m539::CScore>* ASet<m539::CScore>::sm_ptr = 0;
template <> ASet<m539::CPlayer>* ASet<m539::CPlayer>::sm_ptr = 0;
template <> m539::CScoreSprMan* CSingleton<m539::CScoreSprMan>::ms_pointer = 0;
template <> m539::CMapMan* CSingleton<m539::CMapMan>::ms_pointer = 0;
template <> m539::CCameraObj* CSingleton<m539::CCameraObj>::ms_pointer = 0;
