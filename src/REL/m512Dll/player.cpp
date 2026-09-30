/* player.cpp -- m512::CPlayer, the four skaters. SKELETON: bodies marked STUB are the function forks'.
 * Lines in stubs that set a PTMF, pass a string or declare a static are retail's and place .data/.bss.
 * The ctor's assert must stay on line 149 (its __LINE__ is an immediate; "player.cpp" is in .data). */
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m512Dll/player.h"
#include "REL/m512Dll/camera.h"
#include "REL/m512Dll/score.h"
#include "REL/m512Dll/dust.h"
#include <vector>

namespace m512 {

/* .bss after the header triple, in definition order: s_winner A4C, then the list A5C (its chain A50) */
static CPlayer* s_winner; /* lbl_1_bss_A4C set by CheckGameEnd, never cleared */
TLinkList<CPlayer> CPlayer::playerList;

/* lbl_1_data_370: the start order (mutable: ShuffleStart); start z = 850 + 140 * s_order[idx] */
static int s_order[4] = { 0, 1, 2, 3 };

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

/* on the +z straight: x -50, z 850 + 140 * order (double adds, only z rounded: the SetVec(double) pattern) */
void CPlayer::GetStartPos(Vec* pos, int idx)
{
    SetVec(pos, -50.0f, 0.0f, (140 * s_order[idx] + 750.0) + 100.0);
}

void CPlayer::ShuffleStart()
{
    for (int i = 0; i < 4; i++) {
        int j = CRandom::irandom() & 3;
        int a = s_order[i];
        int b = s_order[j];
        s_order[i] = b;
        s_order[j] = a;
    }
}

void CPlayer::Close()
{
    while (!playerList.isEmpty()) {
        delete playerList.last();
    }
}

/* DRAFT from the sheet's ctor order (player.md §7); the fork verifies it (370 insns) */
CPlayer::CPlayer(int idx)
    : m_unk3C(0), m_model(GwPlayerConf[idx].charNo, 3), m_skate(0x460006U), m_strokeFoot(false), m_unkA0(0)
{
    insertBack(&playerList);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_dif = GwPlayerConf[idx].dif;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_wallHit = false;
    m_yaw = 0.0f;
    m_steerYaw = 0.0f;
    m_motion = -1;
    m_pushTimer = 0;
    m_halfLap = false;
    m_lap = 0;
    m_goal = false;
    m_winner = false;
    m_throttle = 0.0f;
    m_hitTimer = 60;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    createMotion(0x87008F); /* 0 idle */
    createMotion(0x870090); /* 1 skate */
    createMotion(0x8C006C); /* 2 lean left */
    createMotion(0x8C006D); /* 3 winner */
    /* line padding: the assert below is retail's player.cpp:149 */





















































    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model.id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    GetStartPos(&m_pos, idx);
    m_yaw = getTrackYaw();
    checkWall();
    m_prevPos = m_pos;
    m_vel.x = m_vel.y = m_vel.z = 0.0f;
    m_speed = 0.0f;
    m_rank = 0;
    m_time = 1;
    m_radius = 750.0f;
    m_model.setPos(&m_pos);
    setProc(&CPlayer::proc_start);
    m_reflect = Hu3DModelLink(m_model.id());
    Hu3DModelShadowReset(m_reflect);
    Hu3DModelLayerSet(m_reflect, 0);
    Hu3DModelCameraSet(m_reflect, 1);
    Hu3DModelAttrReset(m_reflect, HU3D_ATTR_DISPOFF);
    CSingleton<CScore>::GetInstance()->initPlayer(m_idx, m_charNo);
    CSingleton<CScore>::GetInstance()->setValue(m_idx, m_lap, m_time);
    m_skateId[0] = m_skate.id();
    m_skateId[1] = Hu3DModelLink(m_skate.id());
    m_skateId[2] = Hu3DModelLink(m_skate.id());
    m_skateId[3] = Hu3DModelLink(m_skate.id());
    for (int i = 0; i < 4; i++) {
        id = m_skateId[i];
        Hu3DModelShadowSet(id);
        Hu3DModelShadowDispOn(id);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelAttrReset(m_reflect, HU3D_ATTR_DISPOFF); /* retail: the reflection, not the skate (sheet §9.4) */
        char* hook;
        if (i & 1) {
            hook = CharModelItemHookGet(m_charNo, 8, 2);
        } else {
            hook = CharModelItemHookGet(m_charNo, 8, 3);
        }
        if (i < 2) {
            Hu3DModelHookSet(m_model.id(), hook, id);
            Hu3DModelLayerSet(id, 3);
        } else {
            Hu3DModelHookSet(m_reflect, hook, id);
            Hu3DModelLayerSet(id, 0);
        }
    }
}

CPlayer::~CPlayer()
{
    Hu3DModelKill(m_skateId[1]);
    Hu3DModelKill(m_skateId[2]);
    Hu3DModelKill(m_skateId[3]);
    Hu3DModelKill(m_reflect);
}

s16 CPlayer::createMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
    return mot;
}

void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&playerList, UpdatePlayer);
    TLinkList<CPlayer>::exec(&playerList, UpdateLap);
    UpdateRank();
    /* rotate the list: the first player moves to the back (m536 shape) */
    CPlayer* p = playerList.begin();
    if (p != playerList.end()) {
        p->unlink();
        p->insertBack(&playerList);
    }
}

/* rank 0 = leader (dense: equal keys share a rank); keys are laps*360 + track angle. Outside mode 2 every rank
 * stays 0. Retail swaps the int order entries through the same float temporaries as the keys (exact for 0..3). */
void CPlayer::UpdateRank()
{
    CPlayer* ptr[4];
    float key[4];
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    int order[4] = { 0, 1, 2, 3 };
    int i = 0;
    for (; p != end; p = p->next()) {
        ptr[i] = p;
        key[i] = p->m_trackAngle + (float)(p->m_lap * 360);
        p->m_rank = 0;
        i++;
    }
    if (CGameObject::GetUpdateMode() == 2) {
        for (int k = 0; k < 3; k++) {
            for (int j = 0; j < 3; j++) {
                if (key[j] < key[j + 1]) {
                    float a = key[j];
                    float b = key[j + 1];
                    key[j] = b;
                    key[j + 1] = a;
                    a = order[j];
                    b = order[j + 1];
                    order[j] = b;
                    order[j + 1] = a;
                }
            }
        }
        int rank = 0;
        for (i = 0; i < 4; i++) {
            ptr[order[i]]->m_rank = rank;
            if (i < 3 && key[i] != key[i + 1]) {
                rank++;
            }
        }
    }
}

bool CPlayer::CheckGameEnd(bool deca)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    int n = 0;
    if (deca) {
        for (; p != end; p = p->next()) {
            if (p->m_goal) {
                n++;
            }
        }
        if (n >= 4) {
            return true;
        }
    } else {
        float best = -1.0f;
        for (; p != end; p = p->next()) {
            if (p->m_goal && p->m_goalX > best) {
                if (s_winner) {
                    s_winner->m_winner = false;
                }
                best = p->m_goalX;
                p->m_winner = true;
                s_winner = p;
                n++;
            }
        }
        if (n == 0) {
            return false;
        }
        CMinigameCore::AddWinner(s_winner->m_idx);
        CSingleton<CCameraObj>::GetInstance()->startWinnerZoom();
        return true;
    }
    return false;
}

/* the decathlon score write (retail: an inline; its arguments are register temps) */
inline void SetMgScore(int pno, int score)
{
    GwPlayer[pno].mgScore = score;
}

bool CPlayer::SetResult(bool deca)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    int n = 0;
    if (deca) {
        for (; p != end; p = p->next()) {
            if (p->m_goal) {
                SetMgScore(p->m_idx, p->m_time);
                n++;
            } else {
                SetMgScore(p->m_idx, 0);
            }
        }
    } else {
        for (; p != end; p = p->next()) {
            if (p->m_goal) {
                p->m_goal = false;
                n++;
            }
        }
        if (s_winner) {
            s_winner->m_goal = true;
        }
    }
    if (n > 0) {
        return false;
    }
    return true;
}

/* one entry per listed player (always 4 here) */
void CPlayer::PlayLoseVoice()
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    s16 chars[4];
    int n = 0;
    for (; p != end; p = p->next()) {
        chars[n++] = p->m_charNo;
    }
    CharLoseVoicePlay(chars[0], chars[1], chars[2], chars[3]);
}

void CPlayer::PlayWinnerFX()
{
    if (s_winner) {
        CharFXPlay(s_winner->m_charNo, 0x1FA);
    }
}

/* human finishers only; 18000 frames (5:00) when none */
int CPlayer::GetBestTime()
{
    int best = 18000;
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    for (; p != end; p = p->next()) {
        if (p->m_goal && p->m_padNo >= 0 && p->m_time < best) {
            best = p->m_time;
        }
    }
    return best;
}

/* unreferenced (retail) */
void CPlayer::StartWinCamera()
{
    if (s_winner) {
        CSingleton<CCameraObj>::GetInstance()->startWinnerZoom();
    }
}

/* the players' x/z bounding box; retail starts every bound at 0, so the box always holds the origin */
void CPlayer::GetBounds(Vec* center, Vec* size)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    float maxX = 0.0f;
    float minX = 0.0f;
    float maxZ = 0.0f;
    float minZ = 0.0f;
    for (; p != end; p = p->next()) {
        if (p->m_pos.x > maxX) {
            maxX = p->m_pos.x;
        }
        if (p->m_pos.x < minX) {
            minX = p->m_pos.x;
        }
        if (p->m_pos.z > maxZ) {
            maxZ = p->m_pos.z;
        }
        if (p->m_pos.z < minZ) {
            minZ = p->m_pos.z;
        }
    }
    center->x = (maxX + minX) / 2.0f;
    center->y = 0.0f;
    center->z = (maxZ + minZ) / 2.0f;
    size->x = maxX - minX;
    size->y = 0.0f;
    size->z = maxZ - minZ;
}

/* no null check of s_winner (its only caller runs after CheckGameEnd set it) */
float CPlayer::GetWinnerPos(Vec* pos)
{
    pos->x = s_winner->m_pos.x;
    pos->y = s_winner->m_pos.y;
    pos->z = s_winner->m_pos.z;
    return s_winner->m_yaw;
}

void CPlayer::UpdatePlayer(CPlayer* p)
{
    (p->*(p->m_proc))();
    p->m_wallHit = false;
    p->hitCheck();
    p->m_wallHit |= p->checkWall();
    p->updateDisp();
    if (CGameObject::GetUpdateMode() == 2) {
        if ((float)p->m_hitTimer < 6.0f && p->m_padNo >= 0 && !p->m_goal) {
            omVibrate(p->m_idx, 12, 12, 0);
        }
        p->m_hitTimer++;
    }
}

/* the reflection (m_reflect) is redrawn mirrored every frame: scale y -1 with front-face culling */
void CPlayer::updateDisp()
{
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model.setRot(&rot);
    m_model.setPos(&m_pos);
    Hu3DModelScaleSet(m_reflect, 1.0f, -1.0f, 1.0f);
    Hu3DModelAttrSet(m_reflect, HU3D_ATTR_CULL_FRONT);
    Hu3DModelRotSet(m_reflect, rot.x, rot.y, rot.z);
    Hu3DModelPosSet(m_reflect, m_pos.x, m_pos.y, m_pos.z);
}

/* list walk 2: velocity and speed; in the race (mode 2, not finished) the lap count: crossing x = 0 on the
 * -z side (x > 0 -> x <= 0) arms m_halfLap, crossing it on the +z side (x < 0 -> x >= 0) then counts a lap */
void CPlayer::UpdateLap(CPlayer* p)
{
    float vx = p->m_vel.x = p->m_pos.x - p->m_prevPos.x;
    float vy = p->m_vel.y = p->m_pos.y - p->m_prevPos.y; /* unused: retail stores it to a dead stack slot */
    float vz = p->m_vel.z = p->m_pos.z - p->m_prevPos.z;
    p->m_speed = sqrt((double)(vx * vx + vz * vz)) / 100.0; /* CW: libc math.h's inline double sqrt */
    if (CGameObject::GetUpdateMode() == 2 && !p->m_goal) {
        if (p->m_pos.z > 0.0f) {
            if (p->m_halfLap && p->m_pos.x >= 0.0f && p->m_prevPos.x < 0.0f) {
                p->m_lap++;
                p->m_halfLap = false;
                if (p->m_lap >= 5) {
                    p->m_goal = true;
                    p->m_goalX = p->m_pos.x;
                }
                CSingleton<CScore>::GetInstance()->setValue(p->m_idx, p->m_lap, p->m_time);
                if (p->m_idx & 1) {
                    HuAudFXPlay(0x6C7);
                } else {
                    HuAudFXPlay(0x6C6);
                }
            }
        } else if (p->m_pos.x <= 0.0f && p->m_prevPos.x > 0.0f) {
            p->m_halfLap = true;
        }
    }
    p->m_prevPos.x = p->m_pos.x;
    p->m_prevPos.y = p->m_pos.y;
    p->m_prevPos.z = p->m_pos.z;
    if (CGameObject::GetUpdateMode() != 2 || p->m_goal == true) {
        return;
    }
    p->m_time++;
    float angle = 180.0 * (atan2(p->m_pos.x, p->m_pos.z) / 3.141592653589793);
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    p->m_trackAngle = angle;
}

void CPlayer::hitCheck()
{
    Vec pos = m_pos;
    if (m_pushTimer > 0) {
        m_pushTimer--;
    }
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    for (; p != end; p = p->next()) {
        if (this == p) {
            continue;
        }
        Vec ppos = p->m_pos;
        Vec d;
        Vec t1;
        Vec t2;
        PSVECSubtract(&p->m_pos, &m_pos, &d);
        float dist = PSVECMag(&d);
        if (dist >= 120.0f) {
            continue;
        }
        float ratioA = 0.5f;
        float ratioB = 1.0f - ratioA;
        PSVECScale(&d, &d, (120.0f - dist) / dist);
        PSVECScale(&d, &t1, 1.05f * -ratioA);
        PSVECScale(&d, &t2, 1.05f * ratioB);
        PSVECAdd(&t1, &m_pos, &m_pos);
        PSVECAdd(&t2, &p->m_pos, &p->m_pos);
        p->m_pushTimer = (ratioB >= 0.5f) ? 5 : 0;
        if ((float)m_hitTimer > 30.0f) {
            m_hitTimer = 0;
        }
        if ((float)p->m_hitTimer > 30.0f) {
            p->m_hitTimer = 0;
        }
        if (m_hitTimer == 0 || p->m_hitTimer == 0) {
            CCameraObj::PlaySe(&m_pos, 0x6C3);
        }
        m_wallHit |= checkWall();
        p->m_wallHit |= p->checkWall();
    }
}

/* out-of-line copy unreferenced: inlined into proc_start and proc_main (5 sites) */
void CPlayer::setMotion(int motion, bool once)
{
    s16 model = m_model.id(); /* retail dead spill (AE14) */
    s16& ref = m_mot_id.at(motion);
    s16 mot = ref;
    if (m_motion != motion) {
        CharModelAttrReset(m_charNo, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        Hu3DModelAttrReset(m_reflect, HU3D_MOTATTR_PAUSE);
        Hu3DMotionShiftSet(m_reflect, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
    }
}

void CPlayer::proc_start()
{
    setMotion(0, false);
    setProc(&CPlayer::proc_main);
}

/* follow the track tangent plus the steering offset; motions: 3 winner (normal speed), 2 hard left, 1 skate,
 * 0 idle when not moving (setMotion inlined 4x) */
void CPlayer::proc_main()
{
    m_yaw = getTrackYaw();
    updateInput();
    m_yaw += m_steerYaw;
    if (m_yaw > 180.0f) {
        m_yaw -= 360.0f;
    }
    if (m_yaw < -180.0f) {
        m_yaw += 360.0f;
    }
    updateMove();
    if (updateMotionSpeed()) {
        if (m_winner) {
            CharMotionSpeedSet(m_charNo, 1.0f);
            Hu3DMotionSpeedSet(m_reflect, 1.0f);
            setMotion(3, false);
        } else if (m_turnLeft) {
            setMotion(2, false);
        } else {
            setMotion(1, false);
        }
    } else {
        setMotion(0, false);
    }
}

#ifdef __MWERKS__
/* retail inlines MSL's double sqrt (frsqrte + four Newton steps, 0 / NaN / Inf cases) into UpdateLap and
 * checkWall: m536 camera.cpp GetSeVol's spelling. P2 local copy for checkWall; fork P1 needs the same inline
 * before UpdateLap (A6E0): the merge keeps ONE definition, before UpdateLap. */
inline double MslSqrt(double x)
{
    if (x > 0.0) {
        double guess = __frsqrte(x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        guess = .5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    } else if (x == 0.0) {
        return 0;
    } else if (x) {
        return *(float*)__float_nan;
    }
    return *(float*)__float_huge;
}
#endif

/* |x| through an inline (if/else form: m536 player.cpp) */
inline float Abs(float x)
{
    if (x < 0.0f) {
        return -x;
    } else {
        return x;
    }
}

inline double GetFps() { return 60.0; }

/* skating physics (player.md §6): the velocity turns toward the heading, thrust along the heading plus half
 * the steering offset (COM: scaled by difficulty; catch-up +10% per rank), drag in the heading frame (x10 on
 * a wall/player contact, x1.3 at low throttle, x3 after the goal), then the stroke SE and ice dust of the
 * foot that touches down.
 * The two guarded function-local statics are retail's (bss A68/A70, A78/A80); their initialisers' spelling
 * (an inline returning 60.0) is a guess (m536 KillerSpeed).
 * Retail: tbl[m_dif] is not range-checked (m_dif is 0..3); m_yaw is re-wrapped after hd used it (dead). */
void CPlayer::updateMove()
{
    static double s_fps = GetFps();
    Mtx m;
    Mtx inv;
    Vec out;
    Vec v;
    double vx = s_fps * m_vel.x / 100.0;
    double vy = s_fps * m_vel.y / 100.0;
    double vz = s_fps * m_vel.z / 100.0;
#ifdef __MWERKS__
    double spd = MslSqrt(vx * vx + vz * vz);
#else
    /* host: libm sqrt instead of the MSL inline (no __float_nan/__float_huge on the host) */
    double spd = sqrt(vx * vx + vz * vz);
#endif
    SetVec(&v, 0.0f, 0.0f, spd);
    PSMTXRotRad(m, 'y', 0.017453292f * m_yaw);
    PSMTXMultVec(m, &v, &out);
    vx = (1.0 / 60.0) * (59.0 * vx + out.x);
    vy = (1.0 / 60.0) * (59.0 * vy + out.y);
    vz = (1.0 / 60.0) * (59.0 * vz + out.z);
    float mul = 1.0f + 0.1f * m_rank;
    float com = 1.0f;
    if (m_padNo < 0) {
        float tbl[4] = { 0.43f, 0.7f, 0.9f, 1.0f };
        com = tbl[m_dif];
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = com * (0.003 * m_throttle * mul);
    float hd = m_yaw + 0.05 * m_steerYaw;
    if (m_yaw > 180.0f) {
        m_yaw -= 360.0f;
    }
    if (m_yaw < -180.0f) {
        m_yaw += 360.0f;
    }
    PSMTXRotRad(m, 'y', 0.017453292f * hd);
    PSMTXMultVec(m, &v, &out);
    static double s_acc = 3600.0 / s_fps;
    vx += s_acc * out.x;
    vy += s_acc * out.y;
    vz += s_acc * out.z;
    float k = 1.0f;
    SetVec(&v, vx, vy, vz);
    PSMTXInverse(m, inv);
    PSMTXMultVec(inv, &v, &out);
    if (m_wallHit) {
        if ((float)m_hitTimer > 30.0f) {
            m_hitTimer = 0;
        }
        k *= 10.0f;
    }
    if (m_throttle <= 0.3) {
        k *= 1.3f;
    }
    if (m_goal == true) {
        k *= 3.0f;
    }
    Vec loc;
    loc.z = out.z - 0.003 * out.z * k;
    loc.x = out.x - 0.008 * out.x * k;
    loc.y = 0.0f;
    float lat = out.x;
    PSMTXMultVec(m, &loc, &out);
    m_pos.x += 100.0 * (out.x / s_fps);
    m_pos.y += 100.0 * (out.y / s_fps);
    m_pos.z += 100.0 * (out.z / s_fps);
    m_wallHit = false;
    Vec footR;
    Vec footL;
    char* hookL = CharModelItemHookGet(m_charNo, 8, 2);
    char* hookR = CharModelItemHookGet(m_charNo, 8, 3);
    Hu3DModelObjPosGet(m_model.id(), hookL, &footL);
    Hu3DModelObjPosGet(m_model.id(), hookR, &footR);
    static const int s_strokeSe[8] = { 0x6BB, 0x6BC, 0x6BD, 0x6BE, 0x6BF, 0x6C0, 0x6C1, 0x6C2 };
    if (m_speed > 0.01f) {
        if (footL.y < footR.y) {
            if (m_strokeFoot == true) {
                m_strokeFoot = false;
                CCameraObj::PlaySe(&m_pos, s_strokeSe[m_idx * 2 + 1]);
            }
            if (Abs(lat) > 10.0f && (m_time & 1) != 0) {
                new CDust(&footL);
            }
        } else {
            if (m_strokeFoot == false) {
                m_strokeFoot = true;
                CCameraObj::PlaySe(&m_pos, s_strokeSe[m_idx * 2]);
            }
            if (Abs(lat) > 10.0f && (m_time & 1) != 0) {
                new CDust(&footR);
            }
        }
    }
}

/* motion playback speed follows the throttle; false when coasting (throttle < 0.01) */
bool CPlayer::updateMotionSpeed()
{
    if (m_throttle < 0.01f) {
        CharMotionSpeedSet(m_charNo, 1.0f);
        Hu3DMotionSpeedSet(m_reflect, 1.0f);
        return false;
    }
    CharMotionSpeedSet(m_charNo, 0.75 * (1.5f * m_throttle));
    Hu3DMotionSpeedSet(m_reflect, 0.75 * (1.5f * m_throttle));
    return true;
}

/* COM steering gain by difficulty; doubled into a curve's second half once racing, none on a straight */
float CPlayer::comSteer(float steer)
{
    bool straight = false;
    bool curve = false;
    float k = 0.55f;
    switch (m_dif) {
    case 1:
        k = 1.0f;
        break;
    case 2:
        k = 1.65f;
        break;
    case 3:
        k = 1.8f;
        break;
    }
    if (m_dif > 0) {
        if (m_pos.x > -300.0 && m_pos.x < 300.0) {
            straight = true;
        }
        if (m_pos.x > 150.0f && m_pos.z > 0.0f) {
            curve = true;
        }
        if (m_pos.x < -150.0f && m_pos.z < 0.0f) {
            curve = true;
        }
        if ((m_lap > 0 || m_halfLap) && !straight && curve) {
            k *= 2.0f;
        }
    }
    steer *= k;
    if (steer < -1.0f) {
        steer = -1.0f;
    }
    if (straight && !curve) {
        steer = 0.0f;
    }
    return steer;
}

/* steering and throttle. Human (mode 2): stick X steers, A held is full throttle. COM, a finished player or
 * outside the race: steer toward the inner edge, always accelerating (throttle capped at 0.3 after the goal
 * and outside the race). Retail reads HuPadBtn[m_padNo] before the COM test: HuPadBtn[-1] for a COM. */
void CPlayer::updateInput()
{
    u32 btn = HuPadBtn[m_padNo];
    bool accel = false;
    int mode = CGameObject::GetUpdateMode();
    if (mode == 0 || mode == 1) {
        return;
    }
    float steer = 0.0f;
    if (m_padNo < 0 || m_goal == true || mode != 2) {
        if (m_goal == false) {
            steer = -(m_radius - 750.0) / 700.0;
            steer = comSteer(steer);
            accel = true;
        } else {
            steer = -(m_radius - 750.0) / 700.0;
            steer += 0.5f;
            if (steer < 0.0f) {
                steer *= 2.0f;
            }
            if (steer < -1.0f) {
                steer = -1.0f;
            }
            accel = true;
        }
    } else {
        steer = (1.0f / 56.0f) * HuPadStkX[m_padNo];
        if (btn & PAD_BUTTON_A) {
            accel = true;
        }
    }
    m_turnLeft = false;
    if (steer < -0.5f) {
        m_turnLeft = true;
    }
    if (accel) {
        m_throttle = 1.0f;
    } else {
        m_throttle -= 0.15;
        if (m_throttle < 0.0f) {
            m_throttle = 0.0f;
        }
    }
    if (m_throttle > 1.0f) {
        m_throttle = 1.0f;
    }
    if (m_goal == true || mode != 2) {
        if (m_throttle > 0.3f) {
            m_throttle = 0.3f;
        }
    }
    m_steerYaw -= 8.0f * steer;
    m_steerYaw *= 0.9f;
}

bool CPlayer::checkWall()
{
    if (m_pos.x > -300.0 && m_pos.x < 300.0) {
        if (m_pos.z > 0.0f) {
            if (m_pos.z > 1450.0f) {
                m_pos.z = 1450.0f;
                m_radius = 1450.0f;
                return true;
            }
            if (m_pos.z < 750.0f) {
                m_pos.z = 750.0f;
                m_radius = 750.0f;
                return true;
            }
        } else {
            if (m_pos.z < -1450.0f) {
                m_pos.z = -1450.0f;
                m_radius = 1450.0f;
                return true;
            }
            if (m_pos.z > -750.0f) {
                m_pos.z = -750.0f;
                m_radius = 750.0f;
                return true;
            }
        }
        m_radius = Abs(m_pos.z);
        return false;
    }
    double cx = 300.0;
    if (m_pos.x < 0.0f) {
        cx = -cx;
    }
    double dx = m_pos.x - cx;
    double dz = m_pos.z;
#ifdef __MWERKS__
    double r = MslSqrt(dx * dx + dz * dz);
#else
    /* host: libm sqrt instead of the MSL inline (no __float_nan/__float_huge on the host) */
    double r = sqrt(dx * dx + dz * dz);
#endif
    m_radius = r;
    if (r < 750.0) {
        m_pos.x = cx + 750.0 * (dx / r);
        m_pos.z = 750.0 * (dz / r);
        m_radius = 750.0f;
        if ((float)m_hitTimer > 30.0f) {
            CCameraObj::PlaySe(&m_pos, 0x6C5);
        }
        return true;
    }
    if (r > 1450.0) {
        m_pos.x = cx + 1450.0 * (dx / r);
        m_pos.z = 1450.0 * (dz / r);
        m_radius = 1450.0f;
        if ((float)m_hitTimer > 30.0f) {
            CCameraObj::PlaySe(&m_pos, 0x6C4);
        }
        return true;
    }
    return false;
}

/* the track tangent in degrees: +-90 on the straights, around the curve centre on the curves */
float CPlayer::getTrackYaw()
{
    if (m_pos.x > -300.0 && m_pos.x < 300.0) {
        if (m_pos.z > 0.0f) {
            return 90.0f;
        }
        return -90.0f;
    }
    float cx = 300.0f;
    if (m_pos.x < 0.0f) {
        cx = -cx;
    }
    float dx = m_pos.x - cx;
    float dz = m_pos.z;
    float yaw = 90.0 + 180.0 * (atan2(dx, dz) / 3.141592653589793);
    if (yaw > 180.0f) {
        yaw -= 360.0f;
    }
    return yaw;
}

} // namespace m512
