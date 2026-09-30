/* minigame.cpp -- CMinigameCore: the minigame root object (a singleton). setup() creates the object
 * manager and one omObj whose ObjUpdate drives update(); on exit (omSysExitReq) it fades out and MgExit
 * closes and deletes the core, which pays the winners, then returns to the previous overlay. */
#include "REL/mgcpp/minigame.h"

CMinigameCore::CMinigameCore()
{
    int i;

    m_wait = 0;
    for (i = 0; i < 4; i++) {
        m_winner[i] = -1;
    }
}

/* The minigame payout: every recorded winner gets GwPlayer[w].mgCoinBonus = 10, except in practice
 * and in Battle minigames (whose stake is settled by the board). */
CMinigameCore::~CMinigameCore()
{
    if (mgDataTbl[GwSystem.mgNo].type != MG_TYPE_BATTLE) {
        CMinigameCore* core = GetInstance();
        int i;

        for (i = 0; i < 4; i++) {
            int w = core->m_winner[i];
            if (w >= 0 && !_CheckFlag(FLAG_MG_PRACTICE)) {
                GwPlayer[w].mgCoinBonus = 10;
            }
        }
    }
}

/* ObjectSetup: setup(1, 0x2000) */
void CMinigameCore::setup(int objMax, int prio)
{
    Process_s* om = omInitObjMan(objMax, prio);

    omGameSysInit(om);
    on_setup(om);
    omAddObjEx(om, 0, 0, 0, -1, ObjUpdate);
}

/* the same with the actor object manager; both arguments are unused */
void CMinigameCore::actorSetup(int objMax, int prio)
{
    Process_s* om = MgActorObjectSetup();

    on_setup(om);
    omAddObjEx(om, 0, 0, 0, -1, ObjUpdate);
}

void CMinigameCore::ObjUpdate(omObj_s* obj)
{
    if (omSysExitReq && !WipeCheckEnd()) {
        StartFadeOut();
        HuAudFadeOut(1000);
        obj->objFunc = MgExit;
    } else {
        CMinigameCore* core = GetInstancePtr();
        core->update();
    }
}

void CMinigameCore::update()
{
    int done;

    on_update();
    done = FALSE;
    if (m_wait > 0) {
        if (--m_wait == 0) {
            done = TRUE; /* unused */
        }
    }
}

void CMinigameCore::on_update() {}

/* runs until the fade-out has finished, then closes, deletes the core and leaves the overlay */
void CMinigameCore::MgExit(omObj_s* obj)
{
    CMinigameCore* core = GetInstancePtr();

    if (WipeCheckEnd()) {
        core->update();
        return;
    }
    core->on_close();
    delete core;
    CharModelKill(-1);
    omOvlReturnEx(1, 1);
}

/* records player in the first free winner slot */
void CMinigameCore::AddWinner(int player)
{
    CMinigameCore* core = GetInstance();
    int* winner = core->m_winner;
    int i;

    for (i = 0; i < 4; i++) {
        if (winner[i] < 0) {
            winner[i] = player;
            return;
        }
    }
}

bool CMinigameCore::CheckWinner(int player)
{
    CMinigameCore* core = GetInstance();
    int* winner = core->m_winner;
    int i;

    for (i = 0; i < 4; i++) {
        if (player == winner[i]) {
            return true;
        }
    }
    return false;
}

void CMinigameCore::StartStartGameMes()
{
    CMinigameCore* core = GetInstance();

    core->m_gameMesId = GameMesCreate(2, 0);
}

void CMinigameCore::StartFinishGameMes()
{
    CMinigameCore* core = GetInstance();

    core->m_gameMesId = GameMesCreate(2, 1);
}

/* true when no game message is shown and the wait has run out */
bool CMinigameCore::CheckGameMes()
{
    CMinigameCore* core = GetInstance();

    return !GameMesStatGet(-1) && core->isWaitEnd();
}

/* "Draw!" with no winner, else the winners' characters in ascending player order */
void CMinigameCore::StartWinnerGameMes()
{
    CMinigameCore* core = GetInstance();
    int* winner;
    int n;
    int i;
    int j;
    int k;
    int tmp;
    int charNo[4];

    core->m_wait = s_mgWaitWinner;
    winner = core->m_winner;
    for (n = 0; n < 4; n++) {
        if (winner[n] < 0) {
            break;
        }
    }
    if (n == 0) {
        GameMesCreate(2, 2);
    } else {
        for (i = 1; i < n; i++) {
            for (j = i; j >= 1 && winner[j - 1] > winner[j]; j--) {
                tmp = winner[j - 1];
                winner[j - 1] = winner[j];
                winner[j] = tmp;
            }
        }
        for (k = 0; k < 4; k++) {
            charNo[k] = winner[k] < 0 ? -1 : GwPlayerConf[winner[k]].charNo;
        }
        GameMesCreate(4, 3, charNo[0], charNo[1], charNo[2], charNo[3]);
    }
}

void CMinigameCore::StartRecordGameMes(unsigned int value)
{
    if (!_CheckFlag(FLAG_MG_PRACTICE)) {
        CMinigameCore* core = GetInstance();

        core->m_gameMesId = GameMesCreate(14, value);
        HuAudJinglePlay(134);
    }
}

void CMinigameCore::StartFadeIn()
{
    WipeCreate(1, 5, 60);
}

void CMinigameCore::StartFadeOut()
{
    WipeCreate(2, 6, 60);
}

void CMinigameCore::ExitReq()
{
    omSysExitReq = 1;
}
