#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in player.o's .bss/__sinit */
#include "REL/mgcpp/singleton.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m579Dll/player.h"
#include "REL/m579Dll/camera.h"
#include "REL/m579Dll/score.h"
#include "REL/m579Dll/fishline.h"

namespace m579 {

/* .bss after the header triple, in definition order: s_winner AC4, then the list AD4 (its chain AC8) */
static CPlayer* s_winner; /* lbl_1_bss_AC4: the only top scorer (JudgeAll), else 0 */
TLinkList<CPlayer> CPlayer::s_list;

/* Vec setter with DOUBLE components (m509 player.h's SetVec: the frsp per component) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* |v| through an inline: retail's procFinish / procEnter keep the PSVECMag results in copies */
static inline float Mag(const Vec* v)
{
    return PSVECMag(v);
}

/* ---- player region F3 (.text 0xC6D4..0xE6C8: SubAngle .. procStart) ---- */

/* EXACT m509 EE38 */
float CPlayer::SubAngle(float a, float b)
{
    int ia = DegToAngle(a);
    int ib = DegToAngle(b);
    int d = AngleSub(ia, ib);
    return AngleToDeg(d);
}

/* EXACT m509 EEF0 */
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

/* DRAFT (fn_1_C8F0, 79 insns): the start spoke, radius 900: a = 45 + (180 + tbl[idx]) degrees (rodata_490
 * {0, 90, 270, 180}); x = 900 cos a, z = 900 sin a (retail calls sin first) */
void CPlayer::GetStartPos(Vec* pos, int idx)
{
    float tbl[4] = { 0.0f, 90.0f, 270.0f, 180.0f };
    float r = 900.0f;
    float deg = 45.0f + (180.0f + tbl[idx]);
    float a = M_PI * deg / 180.0;
    double s = r * sin(a);
    double c = r * cos(a);
    pos->x = c;
    pos->y = 0.0f;
    pos->z = s;
}

/* EXACT m509 F0F4 / m537 9EE4 (the non-virtual ~CPlayer is called out of line with flag 1) */
void CPlayer::Close()
{
    while (!s_list.isEmpty()) {
        delete s_list.last();
    }
}

/* DRAFT from player.s CAD0 (300 insns; m509 F1FC's structure). The mem-initialisers are the ascending stores
 * 0x38, 0x40, 0x44, the model, 0x4E, 0x54 .. 0x6C, the vector; 0x50 / 0x64 / 0x70 are left unset (retail). */
CPlayer::CPlayer(int idx)
    : m_unk38(0.0f), m_speed(0.0f), m_state(0), m_model(GwPlayerConf[idx].charNo, 1), m_win(false), m_line(0),
      m_comTarget(0), m_comWait(0), m_score(0), m_frame(0), m_active(0)
{
    insertBack(&s_list);
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_dif = GwPlayerConf[idx].dif;
    m_padNo = (GwPlayerConf[idx].type != 0) ? -1 : GwPlayerConf[idx].padNo;
    m_motion = -1;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0000);           /* 0 idle */
    s16 mot = addMotion(0x8C0001); /* 1 walk */
    CharNpcDustVoiceOffSet(m_model.id(), mot, 0);
    mot = addMotion(0x8C0002); /* 2 run */
    CharNpcDustVoiceOffSet(m_model.id(), mot, 1);
    addMotion(0x8C0076); /* 3 reel */
    addMotion(0x8C0077); /* 4 show the catch */
    addMotion(0x8C0030); /* 5 win */
    addMotion(0x8C0031); /* 6 lose */
    /* line padding (CPlayer ctor): the assert below is retail's player.cpp:134 */







    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model.id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    GetStartPos(&m_pos, idx);
    m_yaw = m_targetYaw = m_yaw = GetRingAngle() + 90.0f; /* retail stores 0x34, 0x3C, 0x34 */
    m_radius = 500.0f;
    m_model.setPos(&m_pos);
    setProc(&CPlayer::procEnter);
    CSingleton<CScore>::GetInstance()->initPlayer(m_idx, m_charNo);
    CSingleton<CScore>::GetInstance()->setValue(m_idx, 0);
}

/* EXACT m513 ~CHeiho DE94: the member dtors (the vector's free, ~CModel(-1)), ~CLinkNode */
CPlayer::~CPlayer() {}

s16 CPlayer::addMotion(u32 dataNum)
{
    s16 id = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(id);
    return id;
}

/* EXACT m537 9ACC: update every player, then the post pass, then rotate the list (update order changes) */
void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&s_list, Update);
    TLinkList<CPlayer>::exec(&s_list, UpdateAfter);
    CPlayer* p = s_list.begin();
    if (p != s_list.end()) {
        p->unlink();
        p->insertBack(&s_list);
    }
}

/* STUB-level DRAFT (fn_1_D358, 143 insns; sheet §1.5): bubble sort of (score, index) descending, n = players tied
 * with the top; a 4-way tie at 0 is the draw (no winner); n == 1 sets s_winner; every top player m_win + AddWinner.
 * Fixed 4-entry arrays (retail: exactly four list entries). */
void CPlayer::JudgeAll()
{
    CPlayer* q = s_list.begin();
    CLinkNode* e = s_list.end();
    CPlayer* p[4];
    int score[4];
    int num;
    int i;
    int j;
    int n;
    int k;
    int m;
    s_winner = 0;
    int idx[4] = { 0, 1, 2, 3 }; /* rodata_4CC */
    int unused = 0; /* retail: a dead zero store at sp+8 */
    num = 0;
    for (; q != e; q = q->next()) {
        p[num] = q;
        score[num] = q->m_score;
        num++;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (score[j] < score[j + 1]) {
                int a = score[j];
                int b = score[j + 1];
                score[j] = b;
                score[j + 1] = a;
                a = idx[j];
                b = idx[j + 1];
                idx[j] = b;
                idx[j + 1] = a;
            }
        }
    }
    n = 1;
    for (k = 1; k < 4; k++) {
        if (score[0] == score[k]) {
            n++;
        }
    }
    if (n == 4 && score[0] == 0) {
        return; /* a 4-way tie at 0: the draw, nobody wins */
    }
    if (n == 1) {
        s_winner = p[idx[0]];
    }
    for (m = 0; m < n; m++) {
        p[idx[m]]->m_win = true;
        CMinigameCore::AddWinner(p[idx[m]]->m_idx);
    }
}

/* DRAFT (fn_1_D594, 68 insns): the single winner's zoom, then every player to procFinish (m_state 1) */
void CPlayer::FinishAll()
{
    if (s_winner) {
        CSingleton<CCameraObj>::GetInstance()->startWinnerZoom(s_winner);
    }
    CPlayer* p = s_list.begin();
    CLinkNode* e = s_list.end();
    for (; p != e; p = p->next()) {
        HU3DMODELID id = p->m_model.id(); /* retail: a dead model-id local */
        p->setProc(&CPlayer::procFinish);
        p->m_state = 1;
    }
}

void CPlayer::procFinish()
{
    if (m_line) {
        procFinishReel();
        return;
    }
    Vec target;
    Vec d;
    float len = Mag(&m_pos);
    float r = 700.0f;
    target.x = r * m_pos.x / len;
    target.y = r * m_pos.y / len;
    target.z = r * m_pos.z / len;
    float s = 700.0 / Mag(&m_pos);
    PSVECScale(&m_pos, &target, s);
    PSVECSubtract(&target, &m_pos, &d);
    float dist = Mag(&d);
    if (dist > 25.0f) {
        PSVECScale(&d, &d, 1.0f / dist);
        move(&d);
        setMotion(m_speed > 0.5f ? 2 : 1, false);
        return;
    }
    float t = SubAngleMax(0.0f, m_yaw, 41.0f / 3.0f);
    m_yaw += t;
    if (HuAbs(t) < 0.01f) {
        setMotion(0, false);
    } else {
        int state = 18;
        m_state = state;
    }
    m_speed = 0.0f;
}

/* fn_1_DA38: idle until frame 240, walk from r 900 to r 650 on the own spoke (the start spoke table again,
 * rodata_500), turn to yaw 0; then motion 0, procStart, m_active */
void CPlayer::procEnter()
{
    if (m_frame < 240.0f) {
        setMotion(0, false);
        return;
    }
    Vec target;
    Vec d;
    float tbl[4] = { 0.0f, 90.0f, 270.0f, 180.0f };
    float r = 650.0f;
    float deg = 45.0f + (180.0f + tbl[m_idx]);
    float a = M_PI * deg / 180.0;
    double s = r * sin(a);
    double c = r * cos(a);
    target.x = c;
    target.y = 0.0f;
    target.z = s;
    PSVECSubtract(&target, &m_pos, &d);
    float dist = Mag(&d);
    if (dist > 25.0f) {
        PSVECScale(&d, &d, 1.0f / dist);
        move(&d);
        setMotion(m_speed > 0.5f ? 2 : 1, false);
        return;
    }
    float t = SubAngleMax(0.0f, m_yaw, 41.0f / 3.0f);
    m_yaw += t;
    if (HuAbs(t) < 0.01f) {
        setMotion(0, false);
        setProc(&CPlayer::procStart);
        m_active = 1;
    } else {
        int state = 18;
        m_state = state;
    }
    m_speed = 0.0f;
}

/* DRAFT (fn_1_DE88, 77 insns; m509 SetResult's shape): winners procWin, others procLose; nobody won -> the lose
 * voices (list order) and true (the draw jingle) */
bool CPlayer::ResultAll()
{
    CPlayer* p = s_list.begin();
    CLinkNode* e = s_list.end();
    s16 chars[4];
    bool draw = true;
    int i = 0;
    for (; p != e; p = p->next()) {
        chars[i++] = p->m_charNo;
        HU3DMODELID id = p->m_model.id(); /* retail: a dead model-id local */
        if (p->m_win) {
            p->setProc(&CPlayer::procWin);
            draw = false;
        } else {
            p->setProc(&CPlayer::procLose);
        }
    }
    if (draw) {
        CharLoseVoicePlay(chars[0], chars[1], chars[2], chars[3]);
    }
    return draw;
}

void CPlayer::procWin()
{
    setMotion(5, true);
}

void CPlayer::procLose()
{
    setMotion(6, true);
}

void CPlayer::Update(CPlayer* p)
{
    (p->*(p->m_proc))();
    p->m_frame++;
}

void CPlayer::UpdateAfter(CPlayer* p)
{
    if (p->m_active) {
        p->PushOthers();
        p->ClampRing();
    }
    p->UpdateModel();
}

void CPlayer::UpdateModel()
{
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model.setRot(&rot);
    m_model.setPos(&m_pos);
    CharModelVoicePanSet(m_charNo, CCameraObj::GetSePan(&m_pos));
    CharModelVoiceVolSet(m_charNo, CCameraObj::GetSeVol(&m_pos, m_idx));
}

void CPlayer::PushOthers()
{
    if (!m_free) {
        return;
    }
    CPlayer* p = s_list.begin();
    CLinkNode* e = s_list.end();
    for (; p != e; p = p->next()) {
        if (p == this) {
            continue;
        }
        double dx = p->m_pos.x - m_pos.x;
        double dz = p->m_pos.z - m_pos.z;
        double len = sqrt(dx * dx + dz * dz);
        if (len > 130.0) {
            continue;
        }
        if (0.0 == len) {
            continue;
        }
        double px = 130.0 * dx / len;
        double pz = 130.0 * dz / len;
        if (!p->m_free) {
            m_pos.x = p->m_pos.x - px;
            m_pos.z = p->m_pos.z - pz;
        } else {
            double mx = 0.5 * (p->m_pos.x + m_pos.x);
            double mz = 0.5 * (p->m_pos.z + m_pos.z);
            px *= 0.5;
            pz *= 0.5;
            m_pos.x = mx - px;
            m_pos.z = mz - pz;
            p->m_pos.x = mx + px;
            p->m_pos.z = mz + pz;
        }
        ClampRing();
        p->ClampRing();
    }
}

/* DRAFT (fn_1_E524, 48 insns; m509 10608's shape) */
void CPlayer::setMotion(int no, bool once)
{
    HU3DMODELID id = m_model.id();
    s16& ref = m_mot_id.at(no);
    s16 mot = ref;
    if (m_motion != no) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, mot, 0.0f, 8.0f, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

void CPlayer::procStart()
{
    m_reelState = 0;
    setMotion(0, false);
    setProc(&CPlayer::procPlay);
}

/* ---- player region F5 (.text 0xE6C8..0x10C84: procPlay .. GetComInput; the weak tail follows) ---- */

/* the catch kind of a line (retail: two inline levels, the r18 -> r17 -> r28 copies in procPlay) */
static inline int BiteOf(CFishLine* line)
{
    return line->m_bite;
}

static inline int LineKind(CFishLine* line)
{
    return BiteOf(line);
}

static inline void TakeLine(CFishLine* line)
{
    line->m_taken = true;
}

/* the reeling player's hand holds the line (procReel / updateReel: the line pointer in a saved register) */
static inline void HoldLine(CFishLine* line, CPlayer* p)
{
    line->m_held = true;
    line->m_owner = p;
}

/* the line is free again after the catch was shown (procShow / procFinishReel) */
static inline void FreeLine(CFishLine* line)
{
    line->m_held = false;
    line->m_holdStart = false;
    line->m_bite = CFishLine::BITE_NONE;
    line->m_taken = false;
}

/* half a second of frames through an inline (GetComInput: retail loads the 30.0 after converting (4 - dif); a
 * guess at the spelling) */
static inline double HalfSecond()
{
    return 30.0;
}

/* |v| through an inline (GetComInput: the f23 -> f29 copy) */
static inline float VecLen(const Vec* v)
{
    return PSVECMag(v);
}

/* STUB-level DRAFT (fn_1_E6C8, 189 insns; sheet §1.2 / §1.4): press = COM ? IsBiting : A (human only); on a free line:
 * taken, HookFish, score +1 (kinds 0..6) / +3 (7) / 0 (8), setValue, SE 0x95D, procReel at once; else walk */
void CPlayer::procPlay()
{
    bool press = false;
    m_free = true;
    m_reelState = 0;
    if (m_padNo < 0) {
        if (CFishLine::IsBiting(&m_pos)) {
            press = true;
        }
    } else if (HuPadBtnDown[m_padNo] & PAD_BUTTON_A) {
        press = true;
    }
    if (press) {
        if ((m_line = CFishLine::FindFree(&m_pos)) != 0) {
            TakeLine(m_line);
            m_line->HookFish();
            m_timer = 0;
            m_free = false;
            int kind = LineKind(m_line);
            if (kind < CFishLine::BITE_BIG) {
                m_score += 1;
            }
            if (kind == CFishLine::BITE_BIG) {
                m_score += 3;
            }
            CSingleton<CScore>::GetInstance()->setValue(m_idx, m_score);
            CCameraObj::PlaySe(&m_pos, 0x95D);
            setProc(&CPlayer::procReel);
            procReel();
            return;
        }
    }
    Vec dir;
    GetInput(&dir);
    if (move(&dir)) {
        setMotion(m_speed > 0.5f ? 2 : 1, false);
    } else {
        setMotion(0, false);
    }
}

void CPlayer::getHandMtx(Mtx m)
{
    char* hook = CharModelItemHookGet(m_charNo, 2, 0);
    Hu3DModelObjMtxGet(m_model.id(), hook, m);
}

/* fn_1_EA28: face the centre (<= 64/3 a frame); after 48 frames release the line and show the catch; frames
 * 0..11 hold the reel motion at time 0, from 12 the line is held by this player's hand; rumble below 30 */
void CPlayer::procReel()
{
    m_reelState = 1;
    m_targetYaw = 180.0 * (atan2(-m_pos.x, -m_pos.z) / M_PI);
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, 64.0f / 3.0f);
    m_timer++;
    if (m_timer > 48.0f) {
        m_timer = 0;
        if (m_line) {
            m_line->ReleaseFish(true);
        }
        m_reelState = 2;
        setProc(&CPlayer::procShow);
        setMotion(4, true);
        return;
    }
    if (m_timer < 12.0f) {
        Hu3DMotionTimeSet(m_model.id(), 0.0f);
    } else {
        HoldLine(m_line, this);
    }
    if (m_line && m_timer < 30.0f) {
        int kind = LineKind(m_line);
        if (kind < CFishLine::BITE_BIG) {
            omVibrate(m_idx, 12, 6, 6);
        }
        if (kind == CFishLine::BITE_BIG) {
            omVibrate(m_idx, 12, 12, 0);
        }
    }
    setMotion(3, true);
}

/* fn_1_EEF4: show the catch for 60 frames, then free the line and play on (the second procPlay PTMF, 4A4) */
void CPlayer::procShow()
{
    m_reelState = 2;
    m_timer++;
    if (m_timer > 60.0f) {
        m_timer = 0;
        setProc(&CPlayer::procPlay);
        FreeLine(m_line);
        m_line = 0;
    }
    setMotion(4, true);
}

/* fn_1_F050 (unreferenced; inlined in procFinishReel): procReel's reel step without the timer, rumble and proc */
void CPlayer::updateReel()
{
    m_targetYaw = 180.0 * (atan2(-m_pos.x, -m_pos.z) / M_PI);
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, 64.0f / 3.0f);
    if (m_timer > 48.0f) {
        m_timer = 0;
        m_reelState = 2;
        if (m_line) {
            m_line->ReleaseFish(true);
        }
    } else if (m_timer < 12.0f) {
        Hu3DMotionTimeSet(m_model.id(), 0.0f);
    } else {
        HoldLine(m_line, this);
    }
    setMotion(3, true);
}

/* fn_1_F3A8: the time-up path of a reeling player (procFinish): finish the reel, then show the catch */
void CPlayer::procFinishReel()
{
    m_timer++;
    if (m_reelState == 1) {
        updateReel();
        return;
    }
    if (m_timer > 60.0f) {
        m_timer = 0;
        FreeLine(m_line);
        m_line = 0;
    }
    setMotion(4, true);
}

void CPlayer::setMotionWin()
{
    setMotion(5, true);
}

/* fn_1_F8B0: m_speed = |dir|; < 0.01 stands (false); motion speed 2 speed below 0.5; turn toward dir by <= 41/3;
 * a step of 7 (5/3 dot) speed along the facing unless it points away (dot < 0: turn only) */
bool CPlayer::move(Vec* dir)
{
    m_speed = PSVECMag(dir);
    if (m_speed < 0.01f) {
        Hu3DMotionSpeedSet(m_model.id(), 1.0f);
        return false;
    }
    float spd = m_speed;
    if (m_speed < 0.5) {
        spd = 2.0f * m_speed;
    }
    Hu3DMotionSpeedSet(m_model.id(), spd);
    m_targetYaw = 180.0 * (atan2(dir->x, dir->z) / M_PI);
    m_yaw += SubAngleMax(m_targetYaw, m_yaw, 41.0f / 3.0f);
    float a = M_PI * m_yaw / 180.0;
    Vec fwd;
    SetVec(&fwd, sin(a), 0.0f, cos(a));
    float dot = PSVECDotProduct(&fwd, dir);
    if (dot < 0.0f) {
        return true;
    }
    float step = 7.0f;
    step *= 5.0 / 3.0 * dot;
    Vec v;
    PSVECScale(&fwd, &v, step * m_speed);
    PSVECAdd(&v, &m_pos, &m_pos);
    return true;
}

/* fn_1_FC6C: only in update mode 2; COM: GetComInput scaled 0.7 / 0.85 / 1.0 by dif; human: the stick x 1/56 */
void CPlayer::GetInput(Vec* dir)
{
    dir->x = 0.0f;
    dir->y = 0.0f;
    dir->z = 0.0f;
    if (CGameObject::GetUpdateMode() == 2) {
        float x = 0.0f;
        float y = 0.0f;
        if (m_padNo < 0) {
            GetComInput(dir);
            if (m_dif == 0) {
                PSVECScale(dir, dir, 0.7f);
            }
            if (m_dif == 1) {
                PSVECScale(dir, dir, 0.85f);
            }
        } else {
            x = (1.0f / 56.0f) * HuPadStkX[m_padNo];
            y = (1.0f / 56.0f) * HuPadStkY[m_padNo];
            SetVec(dir, x, 0.0f, -y);
        }
    }
}

bool CPlayer::ClampRing()
{
    double x = m_pos.x;
    double z = m_pos.z;
    double r = sqrt(x * x + z * z); /* CW: MSL math.h's inline double sqrt; host: libm */
    m_radius = r;
    if (r < 580.0) {
        m_pos.x = 580.0 * (x / r);
        m_pos.z = 580.0 * (z / r);
        m_radius = 580.0f;
        return false;
    } else if (r > 750.0) {
        m_pos.x = 750.0 * (x / r);
        m_pos.z = 750.0 * (z / r);
        m_radius = 750.0f;
        return true;
    }
    return false;
}

float CPlayer::GetRingAngle()
{
    float x = m_pos.x;
    float z = m_pos.z;
    float a = 90.0 + 180.0 * (atan2(x, z) / M_PI);
    if (a > 180.0f) {
        a -= 360.0f;
    }
    return a;
}

/* fn_1_101C8: target = FindNearestBiting (reset the wait on a change); stand while m_comWait < (4 - dif) 30 or
 * without a target; within 300 (GetDistXZ) straight at it; else along the ring: the own angle when the target
 * is ahead (SubAngle > 0), else the own angle + 180 (wrapped), as (cos, 0, -sin) */
void CPlayer::GetComInput(Vec* dir)
{
    CFishLine* t = CFishLine::FindNearestBiting(&m_pos);
    if (t == m_comTarget) {
        m_comWait++;
    } else {
        m_comTarget = t;
        m_comWait = 0;
    }
    if (m_comWait < (4 - m_dif) * HalfSecond()) {
        dir->x = 0.0f;
        dir->y = 0.0f;
        dir->z = 0.0f;
        return;
    }
    if (!t) {
        dir->x = 0.0f;
        dir->y = 0.0f;
        dir->z = 0.0f;
        m_comWait = 0;
        return;
    }
    float a = 0.0f;
    if (t->GetDistXZ(&m_pos) < 300.0f) {
        PSVECSubtract(&t->m_pos, &m_pos, dir);
        float len = VecLen(dir);
        PSVECScale(dir, dir, 1.0f / len);
        return;
    }
    float x = m_pos.x;
    float z = m_pos.z;
    float own = 180.0 * (atan2(x, z) / M_PI);
    float tgt = 180.0 * (atan2(t->m_pos.x, t->m_pos.z) / M_PI);
    if (SubAngle(tgt, own) > 0.0f) {
        a = own;
    } else {
        a = own + 180.0f;
        if (a > 180.0f) {
            a -= 360.0f;
        }
    }
    a = M_PI * a / 180.0;
    SetVec(dir, cos(a), 0.0f, -sin(a));
}

} // namespace m579
