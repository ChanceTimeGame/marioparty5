/* game_master.cpp -- m568::CGameMaster: the minigame root. on_update wakes the game-flow sub-thread (thread_exec)
 * once per frame (and stops for good once it has ended), then updates every object, player and tube and runs the
 * tube-tube / tube-obstacle collision walks.
 * Retail order: ctor, [~auto_ptr<CObjSet>, ~CObjSet, the two empty MSL __vector_base accessors, ~ASet<CObstacle>,
 * ~TLinkList<CObstacle>, ~ASet<CTube>, ~TLinkList<CTube>, ~ASet<CPlayer>, ~TLinkList<CPlayer>], dtor, on_setup,
 * HitTubeOct, on_update, IsGoal, IsAllOut, thread_exec, on_close, [ForEachPair<CTube>, ForEachCross<CTube,
 * CObstacle>], __sinit (the minigame.h triple), the two thunks.
 * .data 2A8..360: the a_set strings (ctor :29, then :58), the six PTMFs (on_update, thread_exec), the singleton
 * strings (thread_exec's camera), the vtable. .rodata 110..140. .bss A00..A18: the triple, then the weak statics
 * below (A0C, A10, A14).
 * EXACT (m539 game_master shapes): ~auto_ptr<CObjSet> / ~CObjSet / the ~ASet / ~TLinkList copies come from the
 * m539 a_set.h + CObjSet spelling; the dtor, on_close, __sinit and the thunks are m539's.
 * Fork F5: every function written; all 24 masked 0 at count (OUT.md). */
#include "REL/m568Dll/game_master.h"
#include "REL/m568Dll/stage.h"
#include "REL/m568Dll/camera.h"
#include "REL/m568Dll/effect.h"
#include "REL/mgcpp/random.h"

namespace m568 {

CGameMaster::CGameMaster() : CSubThread(0x8000), m_set(new CObjSet) {}

CGameMaster::~CGameMaster() {}

void CGameMaster::on_setup(Process_s* om)
{
    CRandom::setSeed(OSGetTick());
    /* the objects register themselves (ObjectList, singletons, the sets) */
    new CStage;
    new CCameraObj;
    new CEffectMan;
    for (int i = 0; i < 4; i++) {
        new CPlayer(i);
    }
    /* number the tubes: the solo 0, the team 1..3 (the SE tables' index) */
    ASet<CTube>* tubes = ASet<CTube>::instance();
    CTube* t = tubes->begin();
    CLinkNode* end = tubes->end();
    int n = 1;
    for (; t != end; t = t->next()) {
        if (t->IsSolo()) {
            t->m_no = 0;
        } else {
            int no = n++; /* retail: the post-increment copy is its own register (r22) */
            t->m_no = no;
        }
    }
}

void HitTubeOct(CTube* t, CObstacle* o)
{
    CSphere* os = &o->m_sphere;
    CSphere* ts = &t->m_sphere;
    if (HitCheckSphere(ts, os)) {
        t->HitObstacle(o);
        o->Hit(t);
    }
}

/* the three instance() asserts first (players, tubes, obstacles), then the walks (the register pressure of the
 * inlined walks spills `this` and the iterators to the stack: CW's own doing) */
void CGameMaster::on_update()
{
    if (wakeupThread(0) < 0) {
        return;
    }
    CGameObject::UpdateAll();
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    ASet<CTube>* tubes = ASet<CTube>::instance();
    ASet<CObstacle>* obstacles = ASet<CObstacle>::instance();
    players->exec(&CPlayer::update);
    ForEachPair<CTube>(tubes, CTube::CollideTubes);
    ForEachCross<CTube, CObstacle>(tubes, obstacles, HitTubeOct);
    tubes->exec(&CTube::update);
}

bool IsGoal()
{
    ASet<CTube>* tubes = ASet<CTube>::instance();
    CLinkNode* end = tubes->end();
    for (CTube* t = tubes->begin(); t != end; t = t->next()) {
        if (!t->IsSolo() && !t->IsOut() && t->GetSphere()->pos.z < -39000.0f) {
            return true;
        }
    }
    return false;
}

bool IsAllOut()
{
    ASet<CTube>* tubes = ASet<CTube>::instance();
    CLinkNode* end = tubes->end();
    for (CTube* t = tubes->begin(); t != end; t = t->next()) {
        if (!t->IsSolo() && !t->IsOut()) {
            return false;
        }
    }
    return true;
}

/* lbl_1_rodata_114: the zoom target */
static const Vec s_zero = { 0.0f, 0.0f, 0.0f };

/* The flow (sheet §1.2): 0 fade-in, 1 start message, 2 play (1800 frames, or every team tube out, or a team tube
 * past the goal), 3 finish (150 frames, float compare) + wipe out, the result PTMFs (the players set read once),
 * 4 wipe in + the win/lose motions, the jingle, the winner message, the camera zoom. Never returns. With every
 * r17..r31 live, CW spills the inlined IsAllOut/IsGoal walks' iterator copies through stack slot pairs and their
 * bools to stack bytes 0xB..0x8: the plain source gives that (masked 0) once CTube's const accessors are used. */
void CGameMaster::thread_exec(CThreadParam param)
{
    int bgm = HuAudSStreamPlay(0x35);
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
    int t = 1800;
    while (--t != 0) {
        if (IsAllOut()) {
            break;
        }
        if (IsGoal()) {
            break;
        }
        sleepThread(0);
    }

    CGameObject::SetObjExecMode(3);
    HuAudSStreamFadeOut(bgm, 100);
    CMinigameCore::StartFinishGameMes();
    for (int i = 0; i < 150.0f; i++) {
        sleepThread(0);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    for (int i = 0; i < 60; i++) {
        sleepThread(0);
    }
    HuAudFadeOut(150);
    ASet<CPlayer>* players = ASet<CPlayer>::instance();
    if (IsAllOut()) {
        players->exec(&CPlayer::startResultSoloWin);
    } else {
        players->exec(&CPlayer::startResultTeamWin);
    }

    CGameObject::SetObjExecMode(4);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_WHITEFADE, 60);
    for (int i = 0; i < 120; i++) {
        sleepThread(0);
    }
    if (IsAllOut()) {
        players->exec(&CPlayer::startWinLoseMotion);
    } else {
        players->exec(&CPlayer::startWinLoseMotion2);
    }
    HuAudJinglePlay(0x79);
    CMinigameCore::StartWinnerGameMes();
    for (int i = 0; i < 30.0; i++) {
        sleepThread(0);
    }
    CSingleton<CCameraObj>::GetInstance()->ZoomTo((Vec*)&s_zero, 2500.0f);
    while (!CMinigameCore::CheckGameMes()) {
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

} // namespace m568

/* The game_master.o .bss template statics (retail's weak statics, kept in the first TU in link order to
 * instantiate them), after the header triple, in this address order (A0C..A14): ASet<CPlayer>, then the effect
 * manager's and the camera's singleton pointers (effect before camera although on_setup news the camera first).
 * input.o holds CSingleton<CStage> / ASet<CObstacle> / ASet<CTube> (9F0..9F8). */
template <> ASet<m568::CPlayer>* ASet<m568::CPlayer>::sm_ptr = 0;
template <> m568::CEffectMan* CSingleton<m568::CEffectMan>::ms_pointer = 0;
template <> m568::CCameraObj* CSingleton<m568::CCameraObj>::ms_pointer = 0;
