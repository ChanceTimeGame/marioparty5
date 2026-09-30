#include "REL/m511Dll/config.h"
#include "REL/m511Dll/player.h"
#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in player.o's .bss / __sinit; AddWinner */
#include "REL/mgcpp/random.h"
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m511Dll/camera.h"
#include "REL/m511Dll/score.h"
#include "REL/m511Dll/star.h"
#include "REL/m511Dll/staryaji.h"
#include "REL/m511Dll/particle.h"
#include "REL/m511Dll/kibako.h"
#include "REL/m511Dll/water.h"
#include "REL/m511Dll/boat.h"
#include <vector>

namespace m511 {

/* .bss after the header triple, in definition order: s_winner AB4, then the list AC4 (its chain AB8) */
static CPlayer* s_winner; /* lbl_1_bss_AB4 zeroed at the top of every CheckGameEnd */
TLinkList<CPlayer> CPlayer::playerList;

/* data_4F8: the start slots (shuffled by ShuffleStart); start x = 300 * slot - 450 */
static int s_startSlot[4] = { 0, 1, 2, 3 };
/* data_508: the COM brake threshold type (60 + 15 * type degrees; shuffled by ShuffleStart) */
static int s_comType[4] = { 0, 1, 2, 3 };

/* Vec setter with DOUBLE components (m512 player.h): a non-constant component is stored with `frsp; stfs` */
inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* |x| through an inline (if/else form: m512 / m536; the result stays in a register) */
inline float Abs(float x)
{
    if (x < 0.0f) {
        return -x;
    } else {
        return x;
    }
}

/* in a line at z = 7500: x = 300 * slot - 450 (the SetVec(double) pattern: only x is rounded) */
void CPlayer::GetStartPos(Vec* pos, int idx)
{
    SetVec(pos, 300 * s_startSlot[idx] - 450, 0.0f, 7500.0f);
}

void CPlayer::ShuffleStart()
{
    for (int i = 0; i < 4; i++) {
        int j = CRandom::irandom() & 3;
        int a = s_startSlot[i];
        int b = s_startSlot[j];
        s_startSlot[i] = b;
        s_startSlot[j] = a;
        int k = CRandom::irandom() & 3;
        int c = s_comType[i];
        int d = s_comType[k];
        s_comType[i] = d;
        s_comType[k] = c;
    }
}

/* EXACT shape m579 / m509 (the non-virtual ~CPlayer is called out of line with flag 1) */
void CPlayer::Close()
{
    while (!playerList.isEmpty()) {
        delete playerList.last();
    }
}

/* rodata_520: the boat-with-driver model per character; rodata_554: the two engine loops per player ([idx], [4 + idx]) */
static const u32 s_boatModel[13] = { 0x450000, 0x450001, 0x450002, 0x450003, 0x450004, 0x450005, 0x450006, 0x450007,
    0x450008, 0x450009, 0x45000A, 0x45000B, 0x45000C };
static const int s_engineSe[8] = { 0x6A2, 0x6A3, 0x6A4, 0x6A5, 0x6A6, 0x6A7, 0x6A8, 0x6A9 };

/* DRAFT from player.s FCE4 (415 insns). The mem-initialisers are the ascending stores 0x78 .. 0xEC (the vector and
 * the wake array are the implicit ones); m_idx .. m_motion follow insertBack. */
CPlayer::CPlayer(int idx)
    : m_stun(0), m_throttle(0.0f), m_unk80(0), m_hit(false), m_speed(0.0f), m_kmh(0.0f), m_time(1), m_rank(0),
      m_stickSmooth(0.0f), m_boat(s_boatModel[GwPlayerConf[idx].charNo]), m_char(GwPlayerConf[idx].charNo, 1),
      m_showChar(false), m_goal(false), m_autoDrive(false), m_gate(0), m_hitTimer(60), m_gateRumble(0)
{
    int i;
    insertBack(&playerList);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_dif = GwPlayerConf[idx].dif;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_motion = -1;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    createMotion(0x8700BE); /* 0 on the boat (the winner shows the character) */
    /* line padding (CPlayer ctor): the assert below is retail's player.cpp:161 */













































    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    Hu3DMotionAttrSet(m_mot_id[0], 1);
    HU3DMODELID id = m_boat.id();
    Hu3DModelLayerSet(id, 4);
    Hu3DModelCameraSet(id, 0xF);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_SHIFT_PAUSE);
    Hu3DModelAttrSet(id, HU3D_ATTR_NOCULL);
    id = m_char.id();
    Hu3DModelLayerSet(id, 4);
    Hu3DModelCameraSet(id, 0xF);
    CharModelAttrSet(m_charNo, HU3D_MOTATTR_PAUSE);
    CharModelAttrSet(m_charNo, HU3D_ATTR_NOCULL);
    GetStartPos(&m_pos, idx);
    m_prevPos = m_pos;
    m_rotY = 180.0f;
    m_steer = 0.0f;
    m_vel.x = m_vel.y = m_vel.z = 0.0f;
    m_unkC0 = 750.0f;
    m_boat.setPos(&m_pos);
    setProc(&CPlayer::procStart);
    CSingleton<CScore>::GetInstance()->initPlayer(m_idx, m_charNo);
    CSingleton<CScore>::GetInstance()->setValue(m_idx, m_gate, m_time);
    new CStarYaji(idx, m_charNo);
    m_splash.reset(new CBoatSplash);
    m_shadow.reset(new CBoatShadow);
    for (i = 0; i < 4; i++) {
        m_wake[i].reset(new CBoatWake);
        m_wakeTimer = 0;
        m_wakeIdx = 0;
    }
    m_engineSe[0] = CCameraObj::PlaySe(&m_pos, s_engineSe[m_idx], m_idx);
    m_engineSe[1] = CCameraObj::PlaySe(&m_pos, s_engineSe[m_idx + 4], m_idx);
}

/* the member dtors only (retail: an empty body) */
CPlayer::~CPlayer() {}

s16 CPlayer::createMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
    return mot;
}

void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&playerList, SavePrev);
    TLinkList<CPlayer>::exec(&playerList, UpdateMain);
    TLinkList<CPlayer>::exec(&playerList, UpdatePlayer);
    TLinkList<CPlayer>::exec(&playerList, UpdateCourseThunk);
    UpdateRank();
    /* rotate the list: the first player moves to the back (m512 shape) */
    CPlayer* p = playerList.begin();
    if (p != playerList.end()) {
        p->unlink();
        p->insertBack(&playerList);
    }
}

void CPlayer::SavePrev(CPlayer* p)
{
    p->m_prevPos = p->m_pos;
}

void CPlayer::UpdateRank()
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    double key[4];
    CPlayer* ptr[4];
    int order[4] = { 0, 1, 2, 3 };
    Vec g;
    int i = 0;
    for (; p != end; p = p->next()) {
        ptr[i] = p;
        CStarMan::GetPos(p->m_gate, &g);
        double dx = g.x - p->m_pos.x;
        double dz = g.z - p->m_pos.z;
        double d = 40000.0 - sqrt(dx * dx + dz * dz);
        key[i] = d + p->m_gate * 40000;
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
            if (i < 3 && key[rank] != key[rank + 1]) {
                rank++;
            }
        }
    }
}

/* deca: all 4 at the goal. Else: the goal player with the smallest goal z is s_winner (retail clears the m_goal of an
 * earlier candidate) -> procWin, AddWinner, the camera zoom; false while nobody is at the goal */
bool CPlayer::CheckGameEnd(bool deca)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    int n = 0;
    s_winner = 0;
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
        float best = 1.0f;
        for (; p != end; p = p->next()) {
            if (p->m_goal && p->m_goalZ < best) {
                if (s_winner) {
                    s_winner->m_goal = false;
                }
                best = p->m_goalZ;
                s_winner = p;
                n++;
            }
        }
        if (n == 0) {
            return false;
        }
        s_winner->setProc(&CPlayer::procWin);
        CMinigameCore::AddWinner(s_winner->m_idx);
        CSingleton<CCameraObj>::GetInstance()->setWinner(s_winner->m_idx);
        return true;
    }
    return false;
}

/* after the winner message (gamemaster 81E8); the same body as PlayWinnerFX (retail plays the FX twice) */
void CPlayer::PlayWinnerFX2()
{
    if (s_winner) {
        CharFXPlay(s_winner->m_charNo, 0x1FA);
    }
}

/* the decathlon score write (retail: an inline; its arguments are register temps; m512) */
inline void SetMgScore(int pno, int score)
{
    GwPlayer[pno].mgScore = score;
}

/* deca: GwPlayer[].mgScore = race frames (0 if unfinished). Returns true (draw) when nobody reached the goal */
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
                n++;
            }
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

/* before the winner message (gamemaster 81E0) */
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
        CSingleton<CCameraObj>::GetInstance()->setWinner(s_winner->m_idx);
    }
}

/* the follow camera of player idx: after the goal, 800 out to the side at y 300 looking at the boat; racing, 500
 * behind and 300 up looking 200 ahead (kept above y 160 over the island, |eye| < 700) */
void CPlayer::GetCameraPos(int idx, Vec* at, Vec* eye)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    for (; p != end; p = p->next()) {
        if (p->m_idx == idx) {
            if (p->m_goal) {
                float a = 90.0f + -p->m_rotY;
                at->x = p->m_pos.x;
                at->y = 100.0 + p->m_pos.y;
                at->z = p->m_pos.z;
                eye->x = p->m_pos.x + 100.0 * (8.0 * cos(3.141592653589793 * a / 180.0));
                eye->y = 300.0f;
                eye->z = p->m_pos.z + 100.0 * (8.0 * sin(3.141592653589793 * a / 180.0));
            } else {
                float a = -p->m_rotY - 90.0f;
                at->x = p->m_pos.x - 100.0 * (2.0 * cos(3.141592653589793 * a / 180.0));
                at->y = 100.0 + p->m_pos.y;
                at->z = p->m_pos.z - 100.0 * (2.0 * sin(3.141592653589793 * a / 180.0));
                eye->x = p->m_pos.x + 100.0 * (5.0 * cos(3.141592653589793 * a / 180.0));
                eye->y = 300.0f + p->m_pos.y;
                eye->z = p->m_pos.z + 100.0 * (5.0 * sin(3.141592653589793 * a / 180.0));
                float mag = PSVECMag(eye);
                if (mag < 700.0f && eye->y < 160.0f) {
                    eye->y = 160.0f;
                }
            }
            return;
        }
    }
}

/* the result camera: 800 out to the side at y 600 */
void CPlayer::GetFrontCameraPos(int idx, Vec* at, Vec* eye)
{
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    for (; p != end; p = p->next()) {
        if (p->m_idx == idx) {
            float a = 90.0f + -p->m_rotY;
            at->x = p->m_pos.x;
            at->y = 100.0 + p->m_pos.y;
            at->z = p->m_pos.z;
            eye->x = p->m_pos.x + 100.0 * (8.0 * cos(3.141592653589793 * a / 180.0));
            eye->y = 600.0f;
            eye->z = p->m_pos.z + 100.0 * (8.0 * sin(3.141592653589793 * a / 180.0));
            break;
        }
    }
}

/* list walk 2: the proc, then float on the water (ease 0.15), the spray / shadow / wakes (a wake every 8 frames while
 * fast). Retail: the water normal is computed and dropped. */
void CPlayer::UpdateMain(CPlayer* p)
{
    (p->*(p->m_proc))();
    float speed = p->m_speed;
    CWater* water = CSingleton<CWater>::GetInstance();
    float h = water->GetHeight(&p->m_pos);
    p->m_pos.y += 0.15 * (h - p->m_pos.y);
    Vec pos;
    Vec rot;
    SetVec(&pos, p->m_pos.x, h, p->m_pos.z);
    SetVec(&rot, 0.0f, p->m_rotY, 0.0f);
    CBoatSplash* splash = p->m_splash.get();
    splash->SetPos(&pos, &rot, speed);
    if (speed > (5.0f / 216.0f)) {
        splash->m_active = true;
    } else {
        splash->m_active = false;
    }
    CBoatShadow* shadow = p->m_shadow.get();
    shadow->SetPos(&pos, &rot);
    float power = 1.0f + 0.001f * (speed * 216.0f - 5.0f);
    if (power >= 1.01f) {
        int& timer = p->m_wakeTimer;
        int& n = p->m_wakeIdx;
        if ((timer & 7U) == 0) {
            p->m_wake[n]->Start(&pos, &rot, speed);
            n++;
            n &= 3;
        }
        timer++;
    }
    for (int i = 0; i < 4; i++) {
        p->m_wake[i]->Update();
    }
    Vec normal = water->GetNormal(&p->m_pos);
}

/* list walk 3: boat and wall hits; mode 2: gate rumble (COM too), hit rumble (humans) */
void CPlayer::UpdatePlayer(CPlayer* p)
{
    p->m_hit = false;
    p->hitCheck();
    p->m_hit |= p->checkWall();
    if (CGameObject::GetUpdateMode() == 2) {
        if (p->m_gateRumble > 0) {
            p->m_gateRumble--;
            if (!p->m_goal) {
                omVibrate(p->m_idx, 12, 4, 2);
            }
        } else if ((float)p->m_hitTimer < 6.0f && p->m_padNo >= 0 && !p->m_goal) {
            omVibrate(p->m_idx, 12, 12, 0);
        }
        p->m_hitTimer++;
    }
}

/* the boat model (tilted back with speed), or after the win the character in its seat; the hull (CBoat) and the two
 * engine loops follow */
void CPlayer::updateDisp()
{
    static const Vec s_seat[13] = {
        { 0.0f, -5.8f, 23.6f }, { 0.0f, -5.0f, 27.0f }, { 0.0f, -15.0f, 20.0f }, { 0.0f, -23.0f, 25.0f },
        { 0.0f, -23.0f, -5.0f }, { 0.0f, -15.0f, 20.0f }, { 0.0f, -3.7f, 8.0f }, { 0.0f, 2.0f, 15.0f },
        { 0.0f, -17.5f, 7.0f }, { 0.0f, -9.0f, -7.0f }, { 0.0f, -9.0f, -7.0f }, { 0.0f, -9.0f, -7.0f },
        { 0.0f, -9.0f, -7.0f },
    };
    HU3DMODELID id;
    Vec rot;
    Vec pos = m_pos;
    float tilt = -m_kmh / 2.0f;
    if (tilt < -20.0f) {
        tilt = -20.0f;
    }
    SetVec(&rot, tilt, m_rotY, 0.0f);
    pos.y = m_pos.y - 1.5 * tilt;
    if (m_showChar) {
        id = m_boat.id();
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        id = m_char.id();
        CharModelAttrReset(m_charNo, HU3D_ATTR_DISPOFF);
        m_char.setRot(&rot);
        Mtx mx;
        Mtx my;
        Mtx mz;
        Vec seat;
        PSMTXRotRad(mx, 'X', 0.017453292f * rot.x);
        PSMTXRotRad(my, 'Y', 0.017453292f * rot.y);
        PSMTXConcat(my, mx, mx);
        PSMTXRotRad(mz, 'Z', 0.017453292f * rot.z);
        PSMTXConcat(mz, mx, mx);
        PSMTXMultVec(mx, (Vec*)&s_seat[m_charNo], &seat);
        PSVECAdd(&pos, &seat, &seat);
        m_char.setPos(&seat);
        setMotion(0, false);
    } else {
        id = m_boat.id();
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        id = m_char.id();
        CharModelAttrSet(m_charNo, HU3D_ATTR_DISPOFF);
        m_boat.setRot(&rot);
        m_boat.setPos(&pos);
    }
    CBoat::SetPos(m_idx, &pos, tilt, m_rotY);
    CCameraObj::UpdateSe(&m_pos, m_engineSe[0], m_idx, m_kmh / 60.0f);
    CCameraObj::UpdateSe(&m_pos, m_engineSe[1], m_idx, m_kmh / 60.0f);
}

/* list walk 4 */
void CPlayer::UpdateCourseThunk(CPlayer* p)
{
    p->UpdateCourse();
}

/* velocity / speed / km/h; mode 2: the next star gate (xz < 150: SE, rumble, score, star pop, burst), then the goal
 * line (z < -5000 after gate 5); updateDisp; racing: the star arrow and the race clock */
void CPlayer::UpdateCourse()
{
    static const int s_gateSe[5] = { 0x6AF, 0x6B0, 0x6B1, 0x6B2, 0x6B3 };
    float vx = m_vel.x = m_pos.x - m_prevPos.x;
    float vy = m_vel.y = m_pos.y - m_prevPos.y; /* unused: retail stores it to a dead stack slot */
    float vz = m_vel.z = m_pos.z - m_prevPos.z;
    m_speed = sqrt(vx * vx + vz * vz) / 100.0;
    m_kmh = m_speed * 216000.0f / 1000.0f;
    if (CGameObject::GetUpdateMode() == 2) {
        if (m_gate < 5) {
            Vec g;
            CStarMan::GetPos(m_gate, &g);
            double dx = g.x - m_pos.x;
            double dz = g.z - m_pos.z;
            double dist = sqrt(dx * dx + dz * dz);
            if (dist < 150.0) {
                HuAudFXPlay(s_gateSe[m_gate]);
                m_gate++;
                m_gateRumble = 60;
                CSingleton<CScore>::GetInstance()->setValue(m_idx, m_gate, m_time);
                int n = m_gate - 1;
                CStarMan* star = CSingleton<CStarMan>::GetInstance();
                star->m_hits[n]++;
                star->m_pop[n] = 18;
                new CStarGetEff(this);
            }
        } else if (!m_goal && m_pos.z < -5000.0f) {
            m_goal = true;
            m_goalZ = m_pos.z;
            m_gate++;
            CStarYaji::Hide(m_idx);
            CSingleton<CScore>::GetInstance()->setValue(m_idx, m_gate, m_time);
        }
    }
    updateDisp();
    if (CGameObject::GetUpdateMode() != 2 || m_goal == true) {
        return;
    }
    CStarYaji::SetTarget(m_idx, &m_pos, m_gate, m_rotY);
    m_time++;
}

/* the push that separates two hull circles closer than 160 (xz): half each, from the midpoint; false (zero pushes)
 * when apart or coincident. Unreferenced out of line (retail); inlined in hitCheck. */
bool CPlayer::calcPush(Vec* a, Vec* b, Vec* pa, Vec* pb)
{
    static double s_pushDist = 160.0;
    double dx = b->x - a->x;
    double dz = b->z - a->z;
    double d = sqrt(dx * dx + dz * dz);
    if (d > s_pushDist || d == 0) {
        pa->x = 0.0f;
        pa->y = 0.0f;
        pa->z = 0.0f;
        pb->x = 0.0f;
        pb->y = 0.0f;
        pb->z = 0.0f;
        return false;
    }
    double nx = dx * s_pushDist / d;
    double nz = dz * s_pushDist / d;
    double mx = 0.5 * (b->x + a->x);
    double mz = 0.5 * (b->z + a->z);
    nx *= 0.5;
    nz *= 0.5;
    pa->x = mx - nx - a->x;
    pa->z = mz - nz - a->z;
    pb->x = mx + nx - b->x;
    pb->z = mz + nz - b->z;
    return true;
}

/* boat vs boat: every other boat closer than 400 (xz): three hull circles each, pushed apart pairwise (calcPush);
 * a fresh contact plays SE 0x6AE; then both wall checks. Then the crates: a hit circle stuns 60 frames */
void CPlayer::hitCheck()
{
    Vec circle[3] = { { 0.0f, 0.0f, 100.0f }, { 0.0f, 0.0f, 30.0f }, { 0.0f, 0.0f, -40.0f } };
    CPlayer* p = playerList.begin();
    CLinkNode* end = playerList.end();
    for (; p != end; p = p->next()) {
        if (this == p) {
            continue;
        }
        double dx = p->m_pos.x - m_pos.x;
        double dz = p->m_pos.z - m_pos.z;
        double d = sqrt(dx * dx + dz * dz);
        if (d > 400.0 || d == 0) {
            continue;
        }
        Mtx ma;
        Mtx mb;
        Vec ca[3];
        Vec cb[3];
        PSMTXRotRad(ma, 'y', 0.017453292f * m_rotY);
        PSMTXRotRad(mb, 'y', 0.017453292f * p->m_rotY);
        for (int i = 0; i < 3; i++) {
            PSMTXMultVec(ma, &circle[i], &ca[i]);
            PSMTXMultVec(mb, &circle[i], &cb[i]);
            ca[i].x += m_pos.x;
            ca[i].z += m_pos.z;
            cb[i].x += p->m_pos.x;
            cb[i].z += p->m_pos.z;
        }
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                Vec pa;
                Vec pb;
                bool hit = calcPush(&ca[j], &cb[k], &pa, &pb);
                m_pos.x += pa.x;
                m_pos.z += pa.z;
                p->m_pos.x += pb.x;
                p->m_pos.z += pb.z;
                for (int n = 0; n < 3; n++) {
                    ca[n].x += pa.x;
                    ca[n].z += pa.z;
                    cb[n].x += pb.x;
                    cb[n].z += pb.z;
                }
                if (hit) {
                    bool se = false;
                    if ((float)m_hitTimer > 30.0f) {
                        m_hitTimer = 0;
                        se = true;
                    }
                    if ((float)p->m_hitTimer > 30.0f) {
                        p->m_hitTimer = 0;
                        se = true;
                    }
                    if (se) {
                        HuAudFXPlay(0x6AE);
                    }
                }
            }
        }
        checkWall();
        p->checkWall();
    }
    for (int i = 0; i < 3; i++) {
        Mtx m;
        Vec c;
        PSMTXRotRad(m, 'y', 0.017453292f * m_rotY);
        PSMTXMultVec(m, &circle[i], &c);
        c.x += m_pos.x;
        c.z += m_pos.z;
        if (CKibako::Hit(&c, m_idx)) {
            m_stun = 60;
            m_throttle = 0.0f;
            if ((float)m_hitTimer > 18.0f) {
                static const int s_crateSe[4] = { 0x6AA, 0x6AB, 0x6AC, 0x6AD };
                m_hitTimer = 0;
                CCameraObj::PlaySePlay(&m_pos, s_crateSe[m_idx], m_idx);
            }
        }
    }
}

/* ---- player region P2 (fn_1_133E8 setMotion .. checkWall 14C1C, + the weak tail 152BC..1595C): not-raw-0 insns
 * P1 (FACC..133E8) 2465 / P2 2023 of 4488 ---- */

/* the character's motion (the winner's; the boat model has none) */
void CPlayer::setMotion(int motion, bool once)
{
    if (m_motion != motion) {
        s16 model = m_char.id(); /* retail dead spill */
        s16& ref = m_mot_id.at(motion);
        s16 mot = ref;
        CharMotionSet(m_charNo, mot);
        CharModelAttrReset(m_charNo, HU3D_MOTATTR_PAUSE);
        CharMotionTimeSet(m_charNo, 0.0f);
        CharMotionSpeedSet(m_charNo, 1.0f);
        if (once) {
            CharModelAttrReset(m_charNo, HU3D_MOTATTR_LOOP);
        } else {
            CharModelAttrSet(m_charNo, HU3D_MOTATTR_LOOP);
        }
        m_motion = motion;
    }
}

/* the intro: cruise in at 8.75 a frame to z 4500 */
void CPlayer::procStart()
{
    m_pos.z -= 8.75;
    if (m_pos.z < 4500.0f) {
        setProc(&CPlayer::procMain);
    }
}

/* the winner: the character shows; otherwise procMain */
void CPlayer::procWin()
{
    m_showChar = true;
    updateInput();
    m_rotY += 1.5f * m_steer / 60.0;
    if (m_rotY > 180.0f) {
        m_rotY -= 360.0f;
    }
    if (m_rotY < -180.0f) {
        m_rotY += 360.0f;
    }
    updateThrottle();
    updateMove();
}

void CPlayer::procMain()
{
    updateInput();
    m_rotY += 1.5f * m_steer / 60.0;
    if (m_rotY > 180.0f) {
        m_rotY -= 360.0f;
    }
    if (m_rotY < -180.0f) {
        m_rotY += 360.0f;
    }
    updateThrottle();
    updateMove();
}

/* full while accelerating, else -0.15 a frame */
void CPlayer::updateThrottle()
{
    if (m_accel) {
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
}

/* boat physics (sheet §1.4): the velocity turns 1 % a frame toward the heading, thrust along the heading plus 0.05 of
 * the steering (COM: scaled by difficulty; catch-up +10% per rank; 0.8 when auto-driving), drag in the heading frame
 * (x3 on a hit, with SE 0x6AA + idx; x20 while stunned; x5 braking). The two guarded function-local statics are
 * retail's (bss AE0/AE8, AF0/AF8). Retail: tbl[m_dif] is not range-checked; the drift flag at the end is computed and
 * dropped (no caller reads a result: void here). */
void CPlayer::updateMove()
{
    static double s_fps = 60.0;
    Mtx m;
    Mtx inv;
    Vec out;
    Vec v;
    double vx = s_fps * m_vel.x / 100.0;
    double vy = s_fps * m_vel.y / 100.0;
    double vz = s_fps * m_vel.z / 100.0;
    double spd = sqrt(vx * vx + vz * vz);
    SetVec(&v, 0.0f, 0.0f, spd);
    PSMTXRotRad(m, 'y', 0.017453292f * m_rotY);
    PSMTXMultVec(m, &v, &out);
    vx = 0.01 * (99.0 * vx + out.x);
    vy = 0.01 * (99.0 * vy + out.y);
    vz = 0.01 * (99.0 * vz + out.z);
    float mul = 1.0f + 0.1f * m_rank;
    float com = 1.0f;
    if (m_padNo < 0) {
        float tbl[4] = { 0.58f, 0.7f, 0.85f, 0.95f };
        com = tbl[m_dif];
    }
    if (m_autoDrive) {
        com = 0.8f;
    }
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = com * (0.002 * m_throttle * mul);
    float hd = m_rotY + 0.05 * m_steer;
    if (m_rotY > 180.0f) {
        m_rotY -= 360.0f;
    }
    if (m_rotY < -180.0f) {
        m_rotY += 360.0f;
    }
    PSMTXRotRad(m, 'y', 0.017453292f * hd);
    PSMTXMultVec(m, &v, &out);
    static double s_acc = 3000.0 / s_fps;
    vx += s_acc * out.x;
    vy += s_acc * out.y;
    vz += s_acc * out.z;
    float k = 1.0f;
    SetVec(&v, vx, vy, vz);
    PSMTXInverse(m, inv);
    PSMTXMultVec(inv, &v, &out);
    if (m_hit) {
        if ((float)m_hitTimer > 60.0f) {
            static const int s_wallSe[4] = { 0x6AA, 0x6AB, 0x6AC, 0x6AD };
            m_hitTimer = 0;
            CCameraObj::PlaySePlay(&m_pos, s_wallSe[m_idx], m_idx);
        }
        k *= 3.0f;
    }
    m_stun--;
    if (m_stun < 0) {
        m_stun = 0;
    } else {
        k *= 20.0f;
    }
    if (m_brake) {
        k *= 5.0;
    }
    Vec loc;
    loc.z = out.z - 0.005 * out.z * k;
    loc.x = out.x - 0.007 * out.x * k;
    loc.y = 0.0f;
    float lat = out.x;
    PSMTXMultVec(m, &loc, &out);
    m_pos.x += 100.0 * (out.x / s_fps);
    m_pos.y += 100.0 * (out.y / s_fps);
    m_pos.z += 100.0 * (out.z / s_fps);
    m_hit = false;
    (void)(Abs(lat) > 5.0f); /* retail: the drift test is computed and dropped */
}

/* COM steering (sheet §1.3): toward the next gate (or down the channel), away from the island within 1250; brakes
 * past 60 + 15 * s_comType degrees off. Returns the stick. */
float CPlayer::ComDrive()
{
    float d = 0.0f;
    bool aim = true;
    Vec g;
    CStarMan::GetPos(m_gate, &g);
    if (m_gate > 4 && Abs(m_pos.x) > 500.0f) {
        g.z = -4500.0f;
    }
    float r2 = m_pos.x * m_pos.x + m_pos.z * m_pos.z;
    float r = sqrt(r2);
    if (r < 1250.0) {
        float a = 180.0 * (atan2(-m_pos.x, -m_pos.z) / 3.141592653589793);
        d = SubAngle(a, m_rotY);
        if (Abs(d) < 75.0f) {
            aim = false;
            if (d >= 0.0f) {
                d = 75.0f - d;
            } else {
                d = -75.0f + d;
            }
        }
    }
    if (aim) {
        float a = 180.0 * (atan2(g.x - m_pos.x, g.z - m_pos.z) / 3.141592653589793);
        d = -SubAngle(a, m_rotY);
    }
    float stick = d / 20.0f;
    if (stick > 1.0f) {
        stick = 1.0f;
    }
    if (stick < -1.0f) {
        stick = -1.0f;
    }
    if (!aim) {
        m_accel = true;
        return stick;
    }
    if (Abs(d) < 30.0f) {
        m_accel = true;
    } else {
        m_accel = false;
    }
    float lim = s_comType[m_idx] * 15 + 60;
    if (Abs(d) > lim) {
        m_brake = true;
    }
    return stick;
}

/* after the goal: round the outer canal (+-5400) clockwise; zone by position (sequential ifs, the last match wins) */
float CPlayer::AutoDrive()
{
    m_autoDrive = true;
    float d = 0.0f;
    int zone = 4;
    Vec t;
    if (m_pos.x < 5200.0f && m_pos.z < -5000.0f) {
        zone = 0;
    }
    if (m_pos.x > 5000.0f && m_pos.z < 5200.0f) {
        zone = 1;
    }
    if (m_pos.x > -5200.0f && m_pos.z > 5000.0f) {
        zone = 2;
    }
    if (m_pos.x < -5000.0f && m_pos.z > -5200.0f) {
        zone = 3;
    }
    if (Abs(m_pos.x) < 5200.0f && Abs(m_pos.z) < 5200.0f) {
        zone = 4;
    }
    switch (zone) {
    case 0:
        t.x = 1000.0f + m_pos.x;
        t.z = -5400.0f;
        break;
    case 1:
        t.x = 5400.0f;
        t.z = 1000.0 + m_pos.z;
        break;
    case 2:
        t.x = m_pos.x - 1000.0f;
        t.z = 5400.0f;
        break;
    case 3:
        t.x = -5400.0f;
        t.z = m_pos.z - 1000.0;
        break;
    case 4:
        if (Abs(m_pos.x) > Abs(m_pos.z)) {
            if (m_pos.x > 0.0f) {
                t.x = 5400.0f;
            } else {
                t.x = -5400.0f;
            }
            t.z = m_pos.z;
        } else {
            t.x = m_pos.x;
            if (m_pos.z > 0.0f) {
                t.z = 5400.0f;
            } else {
                t.z = -5400.0f;
            }
        }
        break;
    }
    float a = 180.0 * (atan2(t.x - m_pos.x, t.z - m_pos.z) / 3.141592653589793);
    d = -SubAngle(a, m_rotY);
    float stick = d / 20.0f;
    if (stick > 1.0f) {
        stick = 1.0f;
    }
    if (stick < -1.0f) {
        stick = -1.0f;
    }
    if (Abs(d) < 30.0f) {
        m_accel = true;
    } else {
        m_accel = false;
    }
    return stick;
}

void CPlayer::updateInput()
{
    u32 btn = HuPadBtn[m_padNo];
    m_accel = false;
    m_brake = false;
    int mode = CGameObject::GetUpdateMode();
    if (mode == 0 || mode == 1) {
        return;
    }
    float stick = 0.0f;
    if (m_padNo < 0 || m_goal == true || mode != 2) {
        if (m_goal || mode != 2) {
            if (m_goal) {
                stick = AutoDrive();
            } else {
                m_accel = false;
                m_accel = m_brake; /* retail */
            }
        } else {
            stick = ComDrive();
        }
    } else {
        stick = (1.0f / 56.0f) * HuPadStkX[m_padNo];
        if (btn & PAD_BUTTON_A) {
            m_accel = true;
        }
        if (btn & PAD_BUTTON_B) {
            m_brake = true;
        }
    }
    m_stickSmooth += 0.1 * (stick - m_stickSmooth);
    m_steer -= 8.0f * stick;
    m_steer *= 0.9f;
}

/* auto-driving: snap back onto the outer canal (never a hit). Racing: the lake square (+-4800, z <= 4800), the island
 * (r 700: pushed out, returns at once), then past z -4800 either the south wall (gates left) or the finish channel
 * (|x| < 500, down to z -8000). True on a wall contact. */
bool CPlayer::checkWall()
{
    if (m_autoDrive) {
        float ax = Abs(m_pos.x);
        float az = Abs(m_pos.z);
        if (ax < 5200.0f && ax > 500.0f && az < 5200.0f) {
            float dOut = 5200.0f - ax;
            float dIn = ax - 500.0f;
            float dZ = 5200.0f - az;
            if (dZ < dOut && dZ < dIn) {
                if (m_pos.z > 0.0f) {
                    m_pos.z = 5200.0f;
                } else {
                    m_pos.z = -5200.0f;
                }
            } else if (dOut < dIn) {
                if (m_pos.x > 0.0f) {
                    m_pos.x = 5200.0f;
                } else {
                    m_pos.x = -5200.0f;
                }
            } else {
                if (m_pos.x > 0.0f) {
                    m_pos.x = 500.0f;
                } else {
                    m_pos.x = -500.0f;
                }
            }
        }
        return false;
    }
    int mode = CGameObject::GetUpdateMode();
    if (mode == 0 || mode == 1) {
        return false;
    }
    bool hit = false;
    if (m_pos.x > 4800.0f) {
        m_pos.x = 4800.0f;
        hit = true;
    }
    if (m_pos.x < -4800.0f) {
        m_pos.x = -4800.0f;
        hit = true;
    }
    if (m_pos.z > 4800.0f) {
        m_pos.z = 4800.0f;
        hit = true;
    }
    double px = m_pos.x;
    double pz = m_pos.z;
    double r = sqrt(px * px + pz * pz);
    if (r < 700.0) {
        m_pos.x = 700.0 * (px / r);
        m_pos.z = 700.0 * (pz / r);
        hit = true;
        return hit;
    }
    if (m_pos.z < -4800.0f) {
        if (m_gate < 5) {
            m_pos.z = -4800.0f;
            hit = true;
        } else {
            float over = -m_pos.z - 4800.0f;
            float side = Abs(m_pos.x) - 500.0f;
            if (side > 0.0f) {
                if (over <= side) {
                    m_pos.z = -4800.0f;
                    hit = true;
                } else if (m_pos.x > 0.0f) {
                    m_pos.x = 500.0f;
                    hit = true;
                } else {
                    m_pos.x = -500.0f;
                    hit = true;
                }
            }
            if (m_pos.z < -8000.0f) {
                m_pos.z = -8000.0f;
            }
        }
    }
    return hit;
}

} // namespace m511
