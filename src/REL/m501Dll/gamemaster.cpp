/* gamemaster.cpp -- m501::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread
 * (thread_exec) once per frame and then updates every object. */
/* retail gamemaster.o has no assert: GetConeModel/GetAisuModel inline CSingleton::GetInstance without its
 * singleton.h:39 check, and the unit's .data has no assert strings (as camera.cpp). */
#define MGCPP_NO_ASSERT
#include "REL/m501Dll/gamemaster.h"
#include "REL/m501Dll/aisu.h"
#include "REL/m501Dll/player.h"
#include "REL/m501Dll/stage.h"
#include "REL/m501Dll/particle.h"
#include "REL/m501Dll/camera.h"
#include "REL/m501Dll/random.h"
#include <vector>

namespace m501 {

/* lbl_1_data_238: a non-const int (it is loaded, not folded): no new scoop within this distance of a
 * player or another scoop */
static int s_aisuSpawnDist = 300;

/* retail squares through an inline taking a reference: a temporary operand is stored to the stack and
 * loaded twice, and s_aisuSpawnDist is loaded twice */
template <class T>
static inline T Square(const T& v)
{
    return v * v;
}

/* SetVec (double components, frsp on each store): shared definition in player.h [fork A] */

CGameMaster::CGameMaster() : CSubThread(0x8000), m_timer(0), m_coneModel(0x3B0006U), m_aisuModel(0x3B0005U), m_aisuHandleMan(0x1000)
{
    Hu3DModelShadowSet(m_coneModel.id());
    Hu3DModelShadowDispOn(m_coneModel.id());
    Hu3DModelLayerSet(m_coneModel.id(), 0);
}

CGameMaster::~CGameMaster() {}

void CGameMaster::on_setup(Process_s* om)
{
    Hu3DModelAttrSet(m_aisuModel.id(), HU3D_ATTR_DISPOFF);
    CAisu::init(&m_aisuHandleMan);
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, playerList) */
    new CStage;
    new CParticle;
    new CCameraObj;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
}

void CGameMaster::on_update()
{
    wakeupThread(0);
    CGameObject::UpdateAll();
    CPlayer::UpdateAll();
    CAisu::UpdateAll();
}

/* The game flow: 0 intro camera, 1 start message, 2 play (1800-frame timer, scoops rain down in groups
 * of three), 3 finish (players walk to the winner position), 4 results. Never returns. */
void CGameMaster::thread_exec(CThreadParam param)
{
    CGameObject::SetObjExecMode(0);
    CMinigameCore::StartFadeIn();
    HuAudFXPlay(0x628);
    int se = HuAudFXPlay(0x396);
    while (!CGameObject::CheckObjExec()) {
        sleepThread(0);
    }
    HuAudFXStop(se);

    CGameObject::SetObjExecMode(1);
    CMinigameCore::StartStartGameMes();
    int stream = HuAudSStreamPlay(0x35);
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(2);
    m_timer.setParam(1800, 0, 0);
    m_timer.setModeOn(1);
    int wait = 0;
    while (!m_timer.checkDone()) {
        int time = m_timer.getValue();
        if (!(time < 150.0f)) {
            if (--wait < 0) {
                for (int n = 3; n > 0; n--) {
                    newAisu();
                    for (int j = 0; j < 12.0f; j++) {
                        sleepThread(0);
                    }
                }
                wait = 90.0f + (CRandom::irandom() % 108);
            }
        }
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(stream, 100);
    CPlayer::startWinnerMove();
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 120; i++) {
        sleepThread(0);
    }
    while (!CPlayer::CheckWinIdle()) {
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(4);
    bool draw = CPlayer::StartPlayerWin();
    HuAudJinglePlay(draw ? 0x7B : 0x79);
    if (draw) {
        for (int i = 0; i < 4; i++) {
            CharFXPlay(GwPlayerConf[i].charNo, 0x200);
        }
    } else {
        for (int k = 0; k < 4; k++) {
            if (CMinigameCore::CheckWinner(k)) {
                CharFXPlay(GwPlayerConf[k].charNo, 0x1FA);
            }
        }
    }
    CMinigameCore::StartWinnerGameMes();
    while (!CMinigameCore::CheckGameMes()) {
        sleepThread(0);
    }
    CMinigameCore::ExitReq();
    for (;;) {
        sleepThread(-1);
    }
}

/* fn_1_6C44: true when (x, z) is outside the play circle or within s_aisuSpawnDist of any point of list.
 * Never called; newAisu inlines it. */
bool CheckAisuPos(std::vector<HuVec2f_s>& list, float x, float z)
{
    if (Square(x) + Square(z) > 206297.66f) {
        return true;
    }
    float px = 1578.489f + x;
    float pz = 414.244f + z;
    for (std::vector<HuVec2f_s>::iterator it = list.begin(), end = list.end(); it != end; it++) {
        if (Square(it->x - px) + Square(it->y - pz) < Square(s_aisuSpawnDist)) {
            return true;
        }
    }
    return false;
}

/* drop one scoop at a random free spot of the play circle (gives up after 200 tries) */
void CGameMaster::newAisu()
{
    Vec pos;
    std::vector<HuVec2f_s> list;
    CPlayer::GetPlayerDist(&list);
    CAisu::GetAisuDist(&list);
    int tries = 200;
    float x;
    float z;
    do {
        x = CRandom::frandom(-454.2f, 454.2f);
        z = CRandom::frandom(-454.2f, 454.2f);
        if (--tries == 0) {
            return;
        }
    } while (CheckAisuPos(list, x, z));
    float y = 100.0f * CRandom::frandom(8.0f, 40.0f);
    SetVec(&pos, 1578.489f + x, 5060.02f + y, 414.244f + z);
    new CAisu(CRandom::irandom() % 8, &pos); /* registers itself; type = flavour 0..7 */
}

void CGameMaster::on_close()
{
    CPlayer::Close();
    CAisu::Close();
    CGameObject::Close();
}

CModel* CGameMaster::GetConeModel()
{
    return &static_cast<CGameMaster*>(CMinigameCore::GetInstance())->m_coneModel;
}

CModel* CGameMaster::GetAisuModel()
{
    return &static_cast<CGameMaster*>(CMinigameCore::GetInstance())->m_aisuModel;
}

} // namespace m501

/* The CStage and CCameraObj singleton pointers: retail's weak template statics, kept by the linker in
 * gamemaster.o (first TU in link order to instantiate them), at the end of its .bss (singleton.h).
 * symbols.txt: stageInstance__/cameraInstance__Q24m50111CGameMaster. */
template <> m501::CStage* CSingleton<m501::CStage>::ms_pointer = 0;
template <> m501::CCameraObj* CSingleton<m501::CCameraObj>::ms_pointer = 0;
