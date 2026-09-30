/* gamemaster.cpp -- m509::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread
 * (thread_exec) once per frame and then updates every object and the players. The first players at the maze
 * centre win (CPlayer::CheckGoal -> AddWinner, every goal player of that frame); a 45 s time-out with nobody
 * there is a draw. Every 2 s of play the maze switches layout (CMazeSelector::setLayout).
 * SKELETON: written whole from the W0 sheet (master_camera_back_setup.md §1.1, §2) in m512's shape; the fork
 * verifies it. */
#include "REL/m509Dll/gamemaster.h"
#include "REL/m509Dll/back.h"
#include "REL/m509Dll/maze.h"
#include "REL/m509Dll/camera.h"
#include "REL/m509Dll/player.h"
#include "REL/m509Dll/random.h"

namespace m509 {

CGameMaster::CGameMaster() : CSubThread(0x10000), m_timer(0) {}

CGameMaster::~CGameMaster()
{
    /* CW's __PRETTY_FUNCTION__ is exactly "m509::CGameMaster::~CGameMaster()", pooled before "%s\n" (.data 3280) */
    printf("%s\n", __PRETTY_FUNCTION__);
}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, the player list) */
    new CStage;
    new CCameraObj;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    CPlayer::CreateStartSpr();
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
}

/* seconds -> frames: an inline return value, which thread_exec (r17..r31 all live) spills through 0x10(r1) */
static inline int SecToFrame(int sec)
{
    return sec * 60;
}

/* The game flow: the background, the maze and its selector are created here (not in on_setup); 0 intro
 * (180 frames, no CheckObjExec wait), 1 start message, 2 play (45 s timer from the start; the maze changes
 * layout at once and then every 120 frames), 3 finish (180 frames), 4 result. Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    new CBack;
    new CBackObj;
    new CMaze;
    new CMazeSelector; /* never freed (sheet §8.4) */

    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    HuAudFXPlay(0x692);
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(1);
    int bgm = HuAudBGMPlay(0x3E);
    CMinigameCore::StartStartGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    int frame = 0;
    int sec = 0;
    int n = 0; /* counted, never read (retail) */
    CGameObject::SetObjExecMode(2);
    m_timer.setParam(2700, 0, 0);
    m_timer.setModeOn(1);
    while (!checkEnd()) {
        if (frame >= SecToFrame(sec)) {
            Vec pos = { 0.0f, 0.0f, 0.0f };
            CSingleton<CMazeSelector>::GetInstance()->setLayout(CRandom::irandom());
            HuAudFXPlayVol(0x68F, CCameraObj::GetSeVol(&pos));
            CPlayer::ResetCells();
            n++;
            sec += 2;
        }
        frame++;
        sleepThread(0);
    }
    m_timer.stopTimer();

    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 180; i++) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    bool draw = CPlayer::SetResult();
    HuAudJinglePlay(draw ? 0x7B : 0x79);
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
    bool end = true;
    if (!m_timer.checkDone() && !CPlayer::CheckGoal()) {
        end = false;
    }
    return end;
}

void CGameMaster::on_draw() {}

void CGameMaster::on_close()
{
    CPlayer::Close();
    CGameObject::Close();
}

} // namespace m509

/* The two player/camera singleton pointers: retail's weak template statics, kept by the linker in gamemaster.o
 * (the first TU in link order to instantiate them), at the end of its .bss in this order (bss_44, bss_48). */
template <> m509::CStage* CSingleton<m509::CStage>::ms_pointer = 0;
template <> m509::CCameraObj* CSingleton<m509::CCameraObj>::ms_pointer = 0;
