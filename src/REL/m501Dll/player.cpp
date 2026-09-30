/* player.cpp -- m501::CPlayer. */
#include "REL/m501Dll/player.h"
#include "REL/m501Dll/gamemaster.h"
#include "REL/m501Dll/aisu.h"
#include "REL/m501Dll/asiato.h"
#include "REL/m501Dll/camera.h"
#include "REL/m501Dll/random.h"
#include <vector>

extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
#ifdef __MWERKS__
#include <string.h> /* memset (games/mp5/libc; the host gets it from game.h) */
#endif
}

namespace m501 {

/* .bss after the header triple: playerList (+ its DestructorChain), the sole winner, the cone shrink step
 * (1/30, dynamically initialised) */
CLinkList CPlayer::playerList;
static CPlayer* s_winner;      /* lbl_1_bss_F8: 0 on a tie or a draw */
inline float ConeShrinkStep() { return 1.0f / 30.0f; }
static float s_coneShrinkStep = ConeShrinkStep(); /* lbl_1_bss_FC */

/* Player flow (retail order below):
 *   ctor: model, cone hook, six motions (0x8C0040..43, 0x8C0007, 0x8C0021; index 0 idle, 2 cone drop, 3 win,
 *         4 lose, 1 and 5 movement), start position on the start line, proc = proc_hold_cone.
 *   UpdateAll (every frame, gamemaster): UpdatePlayer for each player (voice pan, proc, stage clamp, matrix,
 *         cone scale), then UpdatePlayerEnding for every pair (push apart), then CheckAisu for each player
 *         (catch scoops), then rotate the list so the collision order changes every frame.
 *   proc_hold_cone -> proc_main (human: analog stick only, no buttons; COM: nearest untargeted scoop);
 *   a scoop landing on the cone above the stack starts proc_drop_cone_start -> proc_drop_cone -> proc_main.
 *   Ending: startWinnerMove (every player walks back to its start slot, proc_winner_move), then
 *   StartPlayerWin decides winners/draw, and the procs play the win/lose motions.
 *
 * Winners (StartPlayerWin): sort by score (descending); top = first player's score. If top != 0 every player
 * with score == top is a winner (CMinigameCore::AddWinner(idx), m_winner = 1), so a tie gives several
 * winners; s_winner keeps the single winner only when there is exactly one (the camera focuses on it).
 * A draw is only "every score is 0": no AddWinner at all, every player plays the draw voice, and
 * StartPlayerWin returns true.
 *
 * Host notes: CPlayer has no virtuals and one base chain CLinkItem -> CLinkNode, so CLinkNode is at offset 0
 * on every ABI and the retail static_casts between CLinkNode* and CPlayer* are exact; the list loops keep the
 * retail form (begin node, CPlayer* cursor, end node). The PTMF m_proc is a real member pointer. The only
 * pointer-sized members are CLinkNode's links and m_topJoint; nothing here uses GC offsets or strides.
 *
 * The assert in the ctor must stay on line 97 (its __LINE__ is in .data).
 */

s16 CPlayer::getVoicePan(Vec* pos)
{
    Vec out;
    Hu3D3Dto2D(pos, 1, &out);
    out.x *= 1.0f / 9.0f;
    int pan = 32.0f + out.x;
    int ret;
    if (pan < 0) {
        ret = 0;
    } else if (pan > 127) {
        ret = 127;
    } else {
        ret = pan;
    }
    return ret;
}

CPlayer::CPlayer(int idx)
    : m_busyTimer(0), m_winTimer(0), m_model(GwPlayerConf[idx].charNo, 2),
      m_coneModel(*CGameMaster::GetConeModel()), m_comDelay(0), m_comUnk12C(0)
{
    insertBack(&playerList);
    m_sphere.r = 80.0f;
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_comSkill = (GwPlayerConf[idx].dif + 1) / 4.0f;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_yaw = m_targetYaw = 53.26265f;
    m_topJoint = &m_coneJoint;
    m_score = 0;
    m_winner = 0;
    m_motion = -1;
    m_coneScale = 1.0f;
    PSMTXIdentity(m_mtx);
    Hu3DModelShadowSet(m_model.id());
    Hu3DModelShadowDispOn(m_model.id());
    Hu3DModelLayerSet(m_model.id(), 0);
    Hu3DModelCameraSet(m_model.id(), 1);
    m_model.setAttr(1);
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    for (int i = 0; i < 4; i++) {
        createMotion(0x8C0040 + i);
    }
    createMotion(0x8C0007);
    createMotion(0x8C0021);
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionVoiceOnSet(m_charNo, 0x43, 0);
    CharMotionVoiceOnSet(m_charNo, 7, 0);
    char* hook = CharModelItemHookGet(m_charNo, 4, 0);
    Hu3DModelHookSet(m_model.id(), hook, m_coneModel.id());
    CharMotionDataClose(m_charNo);
    CharModelFxFlagSet(m_charNo, 0);
    GetStartPos(&m_sphere.pos, idx);
    m_stepPos = m_sphere.pos;
    m_stepCount = 0;
    setProc(&CPlayer::proc_hold_cone);
    memset(&m_comDelay, 0, 0x24);
    m_aisuHandle = 0;
}

void CPlayer::createMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

void CPlayer::GetStartPos(Vec* out, int idx)
{
    float angle = -0.9296086f;
    float step = 1.8f;
    float ofs = idx * step - 1.5 * step;
    float x = 100.0 * (ofs * cos(angle));
    float z = 100.0 * (ofs * sin(angle));
    SetVec(out, 1578.489f + x, 5060.02f, 414.244f + z);
}

void CPlayer::PlayerShow()
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        p->m_model.resetAttr(1);
    }
}

void CPlayer::Close()
{
    while (!playerList.isEmpty()) {
        CPlayer* p = playerList.last<CPlayer>();
        delete p;
    }
}

void CPlayer::UpdateAll()
{
    execPlayerList(&playerList, UpdatePlayer);
    execPlayerListReverse(&playerList, UpdatePlayerEnding);
    execPlayerList(&playerList, CheckAisu);
    /* rotate the list: the first player moves to the back (collision/update order changes every frame) */
    CPlayer* p = playerList.begin<CPlayer>();
    if (p != playerList.end()) {
        p->unlink();
        p->insertBack(&playerList);
    }
}

void CPlayer::UpdatePlayer(CPlayer* player)
{
    CharModelVoicePanSet(player->m_charNo, getVoicePan(&player->m_sphere.pos));
    (player->*(player->m_proc))();
    player->doStageCollide();
    PSMTXRotRad(player->m_mtx, 'Y', 0.017453292f * player->m_yaw);
    PSMTXTransApply(player->m_mtx, player->m_mtx, player->m_sphere.pos.x, player->m_sphere.pos.y,
                    player->m_sphere.pos.z);
    Vec rot;
    SetVec(&rot, 0.0f, player->m_yaw, 0.0f);
    player->m_model.setRot(&rot);
    player->m_model.setPos(&player->m_sphere.pos);
    player->shrinkCone();
    bool expired = false; /* retail: set and never read */
    if (player->m_busyTimer > 0) {
        if (--player->m_busyTimer == 0) {
            expired = true;
        }
    }
    if (player->m_busyTimer <= 0) {
        player->updateComTargetPos();
    }
}

/* lbl_1_rodata_2A4: the stage centre (the start-line centre uses the same three values as separate literals) */
static const Vec s_stageCenter = { 1578.489f, 5060.02f, 414.244f };

void CPlayer::doStageCollide()
{
    Vec d;
    VECSubtract(&m_sphere.pos, &s_stageCenter, &d);
    float len = VecLength(&d);
    if (len < 474.2f) {
        return;
    }
    VECScale(&d, &d, 1.0f + (474.2f - len) / len);
    VECAdd(&s_stageCenter, &d, &m_sphere.pos);
}

void CPlayer::getJointPos(Vec* out)
{
    Mtx* m = m_topJoint->getMatrix();
    SetVec(out, (*m)[0][3], (*m)[1][3], (*m)[2][3]);
}

void CPlayer::CheckAisu(CPlayer* player)
{
    player->centerAisu();
    Vec pos;
    player->getJointPos(&pos);
    CAisu* aisu = CAisu::checkTake(&pos, 20.0f);
    if (aisu == NULL) {
        pos.y += 200.0f;
        aisu = CAisu::checkTake(&pos, 20.0f);
        if (aisu != NULL) {
            int handle = aisu->m_handle;
            player->startConeDrop(handle);
        }
    } else {
        int n = player->m_score++;
        CJoint* top = aisu->doTake(player->m_topJoint, n);
        player->m_topJoint = top;
        omVibrate(player->m_idx, 12, 6, 6);
        player->m_aisuHandle = 0;
    }
}

void CPlayer::startConeDrop(int handle)
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        if (p->m_aisuHandle == (u32)handle) {
            return;
        }
    }
    m_aisuHandle = handle;
    if (CGameObject::GetUpdateMode() == 2) {
        setProc(&CPlayer::proc_drop_cone_start);
    }
}

bool CPlayer::centerAisu()
{
    Vec pos;
    getJointPos(&pos);
    CAisu* aisu = CAisu::getHandle(m_aisuHandle);
    if (aisu == NULL) {
        return false;
    }
    aisu->setPos(&pos, 0.6f);
    return true;
}

void CPlayer::updateComTargetPos()
{
    Mtx inv;
    PSMTXInverse(m_mtx, inv);
    Vec pos;
    getJointPos(&pos);
    PSMTXMultVec(inv, &pos, &m_topJointPos);
}

Vec& CPlayer::getStartDir(Vec* out)
{
    GetStartPos(out, m_idx);
    VecSub(out, &m_sphere.pos, out);
    return *out;
}

float CPlayer::getStartDist()
{
    Vec dir;
    return VecLength(getStartDir(&dir));
}

void CPlayer::UpdatePlayerEnding(CPlayer* a, CPlayer* b)
{
    float ratio = 0.5f;
    if (CGameObject::GetUpdateMode() == 3) {
        float distA = a->getStartDist();
        float distB = b->getStartDist();
        float sum = distA + distB;
        if (sum != 0.0f) {
            ratio = distB / sum;
        }
    } else {
        float sum = a->m_moveMag + b->m_moveMag;
        if (sum != 0.0f) {
            ratio = a->m_moveMag / sum;
        }
    }
    bool hit = HitPushSphere(&a->m_sphere, &b->m_sphere, ratio, 1.05f);
    if (hit && CGameObject::GetUpdateMode() == 3) {
        Vec dirA;
        Vec dirB;
        float dot = VecDot(a->getStartDir(&dirA), b->getStartDir(&dirB));
        float mag = VecLength(dirA) + VecLength(dirB);
        if (mag != 0.0f) {
            (void)(dot / mag); /* retail: the cosine is computed and dropped; the raw dot is tested */
            if (dot > -0.95f) {
                return;
            }
            Vec d;
            VECSubtract(&a->m_sphere.pos, &b->m_sphere.pos, &d);
            d.y = 0.0f;
            VECNormalize(&d, &d);
            Vec up;
            SetVec(&up, 0.0f, 1.0f, 0.0f);
            VECCrossProduct(&d, &up, &d);
            VECScale(&d, &d, 0.0f); /* retail: the side slide is scaled by 0 */
            a->m_sphere.pos.x += d.x;
            a->m_sphere.pos.z += d.z;
            b->m_sphere.pos.x -= d.x;
            b->m_sphere.pos.z -= d.z;
        }
    }
}

void CPlayer::shrinkCone()
{
    char* hook = CharModelItemHookGet(m_charNo, 4, 0);
    Mtx& local = m_coneJoint.lockLocal();
    Hu3DModelObjMtxGet(m_model.id(), hook, local);
    if (m_coneScale < 1.0f) {
        Mtx* coneMtx = m_coneModel.getMatrix();
        Mtx scale;
        PSMTXScale(scale, m_coneScale, m_coneScale, m_coneScale);
        PSMTXConcat(scale, *coneMtx, *coneMtx);
        PSMTXConcat(local, scale, local);
    }
    m_coneJoint.lockMatrixChain();
}

void CPlayer::setMotion(int motion, bool once)
{
    s16 model = m_model.id();
    s16 mot = m_mot_id[motion];
    if (m_motion != motion) {
        Hu3DModelAttrReset(model, 0x40000002);
        CharMotionShiftSet(m_charNo, mot, 0.0f, 8.0f, !once ? 0x40000001 : 0);
        m_motion = motion;
    }
}

float CPlayer::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

float CPlayer::SubAngleMax(float a, float b, float max)
{
    float d = SubAngle(a, b);
    float ret;
    if (d < -max) {
        ret = -max;
    } else if (d > max) {
        ret = max;
    } else {
        ret = d;
    }
    return ret;
}

void CPlayer::proc_hold_cone()
{
    setMotion(0, false);
    setProc(&CPlayer::proc_main);
}

void CPlayer::proc_main()
{
    Vec dir;
    getMoveDir(&dir);
    movePlayer(&dir);
}

void CPlayer::proc_drop_cone_start()
{
    setMotion(2, true);
    Hu3DMotionShiftStartEndSet(m_model.id(), 0.0f, 24.0f);
    setProc(&CPlayer::proc_drop_cone);
}

void CPlayer::proc_drop_cone()
{
    if (CharMotionEndCheck(m_charNo)) {
        setProc(&CPlayer::proc_main);
    }
}

void CPlayer::startWinnerMove()
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        p->setProc(&CPlayer::proc_winner_move);
        p->m_busyTimer = 1;
    }
}

void CPlayer::proc_winner_move()
{
    Vec dir;
    float dist = VecLength(getStartDir(&dir));
    m_moveMag = 1.0f;
    if (dist > 50.0f) {
        VECScale(&dir, &dir, 1.0f / dist);
        movePlayer(&dir);
        return;
    }
    GetStartPos(&m_sphere.pos, m_idx);
    float d = SubAngleMax(53.26265f, m_yaw, getWinAngleSpeed(13.666667f, 1.3333334f));
    m_yaw += d;
    if (HuAbs(d) < 0.01f) {
        setMotion(0, false);
    } else {
        int wait = 18; /* a register variable in retail (li r24,0x12 at DAD8) */
        m_busyTimer = wait;
    }
    m_moveMag = 0.0f;
}

void CPlayer::SortPlayerList()
{
    playerList.sortList(ComparePlayer);
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    int top = p->m_score;
    s_winner = NULL;
    if (top != 0) {
        s_winner = p;
        int count = 0;
        for (; p != e; p = static_cast<CPlayer*>(p->next())) {
            if (p->m_score == top) {
                CMinigameCore::AddWinner(p->m_idx);
                p->m_winner = 1;
                count++;
            }
        }
        if (count != 1) {
            s_winner = NULL;
        }
    }
}

bool CPlayer::ComparePlayer(CLinkNode* a, CLinkNode* b)
{
    return static_cast<CPlayer*>(a)->m_score > static_cast<CPlayer*>(b)->m_score;
}

/* one inline level over CSingleton<CCameraObj>::GetInstance(): retail passes the pointer through two
 * temporaries (DE44..DE54) */
static inline CCameraObj* GetCameraObj()
{
    return CSingleton<CCameraObj>::GetInstance();
}

bool CPlayer::StartPlayerWin()
{
    SortPlayerList();
    CPlayer* q = playerList.begin<CPlayer>();
    CLinkNode* e2 = playerList.end();
    int winners = 0;
    for (; q != e2; q = static_cast<CPlayer*>(q->next())) {
        if (q->m_winner) {
            q->setProc(&CPlayer::proc_win);
            q->m_winTimer = 30;
            CharWinLoseVoicePlay(q->m_charNo, 0x8C0030, 0x1FA);
            winners++;
        } else {
            q->setProc(&CPlayer::proc_lose);
        }
        if (q == s_winner) {
            GetCameraObj()->set_focus_player(&q->m_sphere.pos);
        }
    }
    if (winners == 0) {
        for (q = playerList.begin<CPlayer>(); q != e2; q = static_cast<CPlayer*>(q->next())) {
            CharWinLoseVoicePlay(q->m_charNo, 0x8C0030, 0x200);
        }
    }
    return winners == 0;
}

void CPlayer::proc_win()
{
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(3, true);
}

void CPlayer::proc_lose()
{
    Hu3DMotionSpeedSet(m_model.id(), 1.0f);
    setMotion(4, true);
    setProc(&CPlayer::proc_shrink_cone);
}

void CPlayer::proc_shrink_cone()
{
    m_coneScale -= s_coneShrinkStep;
    if (m_coneScale <= 0.0f) {
        m_coneScale = 0.0f;
    }
}
/* ---- fork B: getWinAngleSpeed .. end ---- */

/* x * x through a const reference: retail spills the argument and loads it twice (GetStickData, getNearAisu,
 * the footprint spacing in movePlayer) */
inline float Square(const float& x) { return x * x; }

/* blend a (no scoops) -> b (8 or more scoops) by the score */
float CPlayer::getWinAngleSpeed(float a, float b)
{
    float t = m_score / 8.0f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    float u = 1.0f - t;
    return a * u + b * t;
}

/* VECSquareDistance through one inline return level, like player.h's VecLength/VecDot (E804) */
inline float VecSquareDistance(Vec* a, Vec* b) { return VECSquareDistance(a, b); }

/* lbl_1_data_510 / 514: footprint spacing while running / walking (non-const .data; used by movePlayer) */
static float s_stepDistRun = 60.000004f;
static float s_stepDistWalk = 30.000002f;

/* Turns towards dir and walks along the facing direction; false (and the idle motion) when the stick
 * magnitude is below 0.3. Leaves a footprint every s_stepDist* units, alternating feet (not character 8). */
bool CPlayer::movePlayer(Vec* dir)
{
    /* declared up front: CW gives named locals the nonvolatile registers first, in declaration order, and
     * `busy` is a register in retail (li r23,0x30 at E2D0); the order decides which inline temporaries spill */
    float speed;
    float turn;
    int busy;
    if (m_moveMag < 0.3f) {
        Hu3DMotionSpeedSet(m_model.id(), 1.0f);
        setMotion(0, false);
        return false;
    }
    busy = 48;
    m_busyTimer = busy;
    m_targetYaw = HuAtan(dir->x, dir->z);
    turn = getWinAngleSpeed(13.666667f, 1.3333334f);
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, turn);
    float rad = M_PI * m_yaw / 180.0;
    Vec fwd;
    SetVec(&fwd, sin(rad), 0.0f, cos(rad));
    float dot = VecDot(fwd, *dir);
    if (dot < 0.0f) {
        return true;
    }
    speed = getWinAngleSpeed(9.0f, 3.0f);
    speed *= m_moveMag * (1.6666666666666667 * dot);
    if (CAisu::checkSlowMove(&m_sphere.pos)) {
        speed *= 0.3f;
    }
    Vec move;
    PSVECScale(&fwd, &move, speed);
    PSVECAdd(&move, &m_sphere.pos, &m_sphere.pos);
    m_running = speed > 4.5f;
    if (m_running) {
        setMotion(1, false);
    } else {
        setMotion(5, false);
    }
    if (m_charNo != 8) {
        float dist = m_running ? Square(s_stepDistRun) : Square(s_stepDistWalk);
        if (VecSquareDistance(&m_sphere.pos, &m_stepPos) >= dist) {
            m_stepPos.x = m_sphere.pos.x;
            m_stepPos.y = m_sphere.pos.y;
            m_stepPos.z = m_sphere.pos.z;
            Vec foot;
            SetVec(&foot, !(m_stepCount++ & 1) ? -20.0f : 20.0f, 0.0f, 0.0f);
            PSMTXMultVec(m_mtx, &foot, &foot);
            new CAsiato(&foot, m_yaw);
        }
    }
    return true;
}

/* Applies a dead zone and a clamp to a stick position. Plain char is SIGNED here (every load is lbz; extsb and
 * the symbol mangles `c`): the C++ overlays build with -char signed (cc.sh changed; see OUT.md). */
void CPlayer::GetStickData(char* x, char* y, char dead, char max)
{
    float mag = sqrtf(Square(*x) + Square(*y));
    if (mag < dead) {
        *x = 0;
        *y = 0;
    } else {
        if (mag > max) {
            *x = *x * max / mag;
            *y = *y * max / mag;
            mag = sqrtf(Square(*x) + Square(*y));
        }
        if (mag > 1e-6f) {
            *x = *x - *x * dead / mag;
            *y = *y - *y * dead / mag;
        }
    }
}

/* Human: analog stick rotated into the camera's view (mode 2 only). COM: getComMoveDir. */
void CPlayer::getMoveDir(Vec* dir)
{
    m_moveMag = 0.0f;
    dir->x = 0.0f;
    dir->y = 0.0f;
    dir->z = 0.0f;
    if (CGameObject::GetUpdateMode() == 2) {
        if (m_padNo < 0) {
            getComMoveDir(dir);
            clampMag();
        } else {
            /* read as plain char: retail loads the byte with no extsb (EF8C), as from a `char` array; an s8
             * element converted to char gets an extsb */
            char x = ((char*)HuPadStkX)[m_padNo];
            char y = ((char*)HuPadStkY)[m_padNo];
            GetStickData(&x, &y, 0, 28);
            float sx = x / 28.0f;
            float sy = y / 28.0f;
            SetVec(dir, sx, 0.0f, -sy);
            Mtx rot;
            PSMTXRotRad(rot, 'Y', 0.9296086f);
            PSMTXMultVecSR(rot, dir, dir);
            m_moveMag = VecLength(dir);
            clampMag();
        }
    }
}

void CPlayer::clampMag()
{
    float mag = m_moveMag;
    if (mag >= 0.8f) {
        mag = 1.0f;
    } else if (mag >= 0.3f) {
        mag = 0.5f;
    } else {
        mag = 0.0f;
    }
    m_moveMag = mag;
}

/* A scoop's position through an inline accessor (retail copies the pointer once: addi; mr). */
inline Vec* AisuPos(CAisu* aisu) { return &aisu->m_pos; }

/* vector<int> [begin, end) as raw pointers. Retail's loops over an int vector copy begin()/end() one register
 * more than the w0 <vector> gives (F5E4..F608, FBF0.., F7B8..); a nested inline with a pointer conversion
 * reproduces it (tested). Probably MSL's own begin()/end() for the scalar specialisation -- report. The host's
 * iterators are classes, so it takes data(). */
template <class T> inline T* VecBegin(std::vector<T>& v)
{
    return (T*)v.begin();
}
template <class T> inline T* VecEnd(std::vector<T>& v)
{
    return (T*)v.end();
}

/* the handle in list whose scoop is nearest to pos in XZ (0 if none) */
int CPlayer::getNearAisu(std::vector<int>& list, Vec* pos)
{
    double best = 2e120;
    int* it = VecBegin(list);
    int* end = VecEnd(list);
    int nearest = 0;
    for (; it != end; ++it) {
        CAisu* aisu = CAisu::getHandle(*it);
        if (aisu != NULL) {
            Vec* p = AisuPos(aisu);
            float dist = Square(p->x - pos->x) + Square(p->z - pos->z);
            if (best < dist) {
                continue;
            }
            best = dist;
            nearest = *it;
        }
    }
    return nearest;
}

/* seconds to frames (60 fps); an inline in retail (its argument and result are register copies, F8D8/F8EC) */
inline float SecToFrame(float sec) { return 60.0f * sec; }

/* COM steering: pick the nearest scoop no other player is after, wait a skill-dependent reaction delay,
 * then head for it in XZ. */
void CPlayer::getComMoveDir(Vec* dir)
{
    Vec top;
    PSMTXMultVec(m_mtx, &m_topJointPos, &top);
    if (CAisu::getHandle(m_comTargetHandle) == NULL) {
        std::vector<int> list;
        CAisu::GetHandleList(list);
        removeOtherTargets(list);
        m_comTargetHandle = getNearAisu(list, &top);
        float delay = m_comSkill;
        delay = 1.0f - delay;
        delay = 0.25f + 0.75f * delay;
        delay *= SecToFrame(CRandom::frandom(1.5f, 2.0f));
        m_comDelay = delay;
    }
    bool ready = false; /* set, never read */
    if (m_comDelay > 0) {
        if (--m_comDelay == 0) {
            ready = true;
        }
    }
    if (m_comDelay <= 0) {
        Vec* target = &m_comTarget;
        CAisu* aisu = CAisu::getHandle(m_comTargetHandle);
        if (aisu != NULL) {
            Vec* p = AisuPos(aisu);
            target->x = p->x;
            target->y = p->y;
            target->z = p->z;
            PSVECSubtract(target, &top, dir);
            dir->y = 0.0f;
            float mag = VecLength(dir);
            if (mag < 10.0f) {
                return;
            }
            if (mag > 1.0f) {
                PSVECScale(dir, dir, 1.0f / mag);
                mag = 1.0f;
            }
            m_moveMag = mag;
        }
    }
}

/* std::find, as MSL <algorithm> writes it (the w0 <algorithm> has none) */
template <class InputIterator, class T>
inline InputIterator Find(InputIterator first, InputIterator last, const T& value)
{
    while (first != last && !((T)*first == value)) { /* T: the value type decides the compare (unsigned here) */
        ++first;
    }
    return first;
}

/* clears (to 0) every handle another player is already heading for */
void CPlayer::removeOtherTargets(std::vector<int>& list)
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        if (p != this) {
            u32 target = p->m_comTargetHandle; /* compared unsigned (cmplw, FC3C) */
            int* it = VecBegin(list);
            int* end = VecEnd(list);
            while (it != end) {
                it = Find(it, end, target);
                if (it != end) {
                    *it = 0;
                    ++it;
                }
            }
        }
    }
}

/* appends every player's XZ position */
void CPlayer::GetPlayerDist(std::vector<HuVec2f_s>* list)
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        HuVec2f_s pos = { 0.0f, 0.0f };
        pos.x = p->m_sphere.pos.x;
        pos.y = p->m_sphere.pos.z;
        list->push_back(pos);
    }
}

/* true when no player is moving or turning */
bool CPlayer::CheckWinIdle()
{
    CPlayer* p = playerList.begin<CPlayer>();
    CLinkNode* e = playerList.end();
    for (; p != e; p = static_cast<CPlayer*>(p->next())) {
        if (p->m_busyTimer > 0) {
            return false;
        }
    }
    return true;
}

void CPlayer::execPlayerList(CLinkList* list, void (*func)(CPlayer*))
{
    execPlayerList(list->begin<CPlayer>(), static_cast<CPlayer*>(list->end()), func);
}

void CPlayer::execPlayerList(CPlayer* begin, CPlayer* end, void (*func)(CPlayer*))
{
    for (; begin != end; begin = static_cast<CPlayer*>(begin->next())) {
        func(begin);
    }
}

/* calls func(p, q) once for every pair, p before q in list order */
void CPlayer::execPlayerListReverse(CLinkList* list, void (*func)(CPlayer*, CPlayer*))
{
    CPlayer* p = list->begin<CPlayer>();
    CLinkNode* end = list->end();
    CPlayer* last = static_cast<CPlayer*>(end->prev());
    for (; p != last; p = static_cast<CPlayer*>(p->next())) {
        for (CPlayer* q = static_cast<CPlayer*>(p->next()); q != end; q = static_cast<CPlayer*>(q->next())) {
            func(p, q);
        }
    }
}

} // namespace m501
