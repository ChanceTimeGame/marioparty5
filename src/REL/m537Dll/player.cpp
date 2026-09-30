#include "REL/mgcpp/minigame.h"
#include "REL/m537Dll/player.h"
#include "REL/m537Dll/stage.h"
#include "REL/m537Dll/dorrie.h"
#include "REL/m537Dll/center_obj.h"
#include "REL/m537Dll/water.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}

namespace m537 {

static TLinkList<CPlayer> s_list; /* bss A40 (DestructorChain A34); rotated every frame (retail) */
static int s_aliveNum;

/* the stage class's retail name (player.cpp:52's assert text; stage.h) */
typedef CStage CMapMan;

static s16 GetPan(Vec* pos)
{
    Vec screen;
    Hu3D3Dto2D(pos, 1, &screen);
    screen.x *= 0.055555556f;
    int pan = 48.0f + screen.x;
    int result;
    if (pan < 0) {
        result = 0;
    } else if (pan > 127) {
        result = 127;
    } else {
        result = pan;
    }
    return result;
}

/* line padding (CreateAll): the assert below must stay on retail's player.cpp:52 */




void CPlayer::CreateAll()
{
    assert(CMapMan::GetSingletonPtr() != NULL);
    for (int i = 0; i < 4; i++) {
        new CPlayer(i, CSingleton<CStage>::GetInstance()->GetDorrie(i));
    }
    CharEffectLayerSet(5);
    s_aliveNum = 4;
}

void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&s_list, Update);
    TLinkList<CPlayer>::exec(&s_list, CheckFall);
    CPlayer* p = s_list.begin();
    if (p != s_list.end()) {
        p->unlink();
        p->insertBack(&s_list);
    }
}

/* retail reads begin() then end() once into a local (CPlayer has no vptr: CLinkNode is at 0 on every ABI) */
#define FOR_EACH_PLAYER(p)                                                                                      \
    CPlayer* p = s_list.begin();                                                                                 \
    CLinkNode* end_ = s_list.end();                                                                              \
    for (; p != end_; p = p->next())

/* the same walk over loop variables declared at the function top (one register pair for every loop) */
#define WALK_PLAYERS(p, end)                                                                                    \
    p = s_list.begin();                                                                                          \
    end = s_list.end();                                                                                          \
    for (; p != end; p = p->next())

void CPlayer::StartAll()
{
    {
        FOR_EACH_PLAYER(p) {
            p->setProc(&CPlayer::procPlay);
        }
    }
    BalanceCom();
}

/* survivors win (AddWinner + mgCoinBonus 0) unless nobody fell: a draw (mgCoinBonus 3, no AddWinner); practice
 * writes nothing (sheet §1.6) */
void CPlayer::JudgeAll()
{
    {
        FOR_EACH_PLAYER(p) {
            if (!p->m_out) {
                if (s_aliveNum < 4) {
                    CMinigameCore::AddWinner(p->m_idx);
                    int no = p->m_idx;
                    if (!_CheckFlag(FLAG_MG_PRACTICE)) {
                        GwPlayer[no].mgCoinBonus = 0;
                    }
                } else {
                    int no = p->m_idx;
                    if (!_CheckFlag(FLAG_MG_PRACTICE)) {
                        GwPlayer[no].mgCoinBonus = 3;
                    }
                }
                p->setProc(&CPlayer::procJudge);
                p->setMotion(5, false);
            }
        }
    }
    CSingleton<CCenterObj>::GetInstance()->Release();
}

void CPlayer::ResultAll()
{
    /* retail loads begin() / end() before the test */
    CPlayer* p = s_list.begin();
    CLinkNode* end_ = s_list.end();
    if (s_aliveNum >= 4) {
        /* lbl_1_rodata_2E0: a local aggregate */
        s16 c[4] = { -1, -1, -1, -1 };
        s16* cp = c;
        for (; p != end_; p = p->next(), cp++) {
            p->setMotion(9, false);
            p->setProc(&CPlayer::procNone);
            *cp = p->m_charNo;
        }
        CharLoseVoicePlay(c[0], c[1], c[2], c[3]);
    } else {
        for (; p != end_; p = p->next()) {
            if (!p->m_out) {
                p->setMotion(8, false);
                p->setProc(&CPlayer::procNone);
            }
        }
    }
}

void CPlayer::DeleteAll()
{
    while (!s_list.isEmpty()) {
        delete s_list.last();
    }
}

/* the survivors' head centroid; *out is left unchanged at <= 1 survivor (retail: center_obj keeps its target) */
Vec* CPlayer::GetCenter(Vec* out)
{
    float scale;
    if (s_aliveNum <= 1) {
        return out;
    }
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    FOR_EACH_PLAYER(p) {
        if (!p->m_out) {
            Vec h;
            p->getHeadPos(&h);
            PSVECAdd(&h, out, out);
        }
    }
    scale = 1.0 / s_aliveNum;
    PSVECScale(out, out, scale);
    return out;
}

int CPlayer::GetAliveNum()
{
    return s_aliveNum;
}

int CPlayer::GetWinner()
{
    if (s_aliveNum != 1) {
        return -1;
    }
    FOR_EACH_PLAYER(p) {
        if (!p->m_out) {
            return p->m_idx;
        }
    }
    return -1;
}

/* m_beat_rec is copy-constructed from a temporary deque (sheet §3.2: C8A4 from CBCC, the temporary destroyed inline) */
CPlayer::CPlayer(int idx, CDorrie* dorrie)
    : CModel(GwPlayerConf[idx].charNo, 2), m_proc(&CPlayer::procInit), m_idx(idx),
      m_charNo(GwPlayerConf[idx].charNo), m_padNo(GwPlayerConf[idx].type ? -1 : GwPlayerConf[idx].padNo),
      m_dif(GwPlayerConf[idx].dif), m_bias(0), m_vibWait(0), m_turnSec(1), m_pushMax(170.0), m_pushStart(80.0),
      m_pushMin(-40.0), m_dorrie(dorrie), m_wait(0), m_out(0), m_beatCount(0), m_beat_rec(BeatRec()), m_push(0.0),
      m_pushSmooth(0.0), m_rotY(0.0f), m_motion(-1), m_motTime(0.0f)
{
    insertBack(&s_list);
    setLayer(5);
    set_shadow();
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    createMotions();
    resetBeat();
}

CPlayer::~CPlayer() {}

/* retail: two dead "reached 0" locals */
void CPlayer::Update(CPlayer* p)
{
    (p->*(p->m_proc))();
    Vec rot = { 0.0f, 0.0f, 0.0f };
    rot.y = p->m_rotY;
    p->setRot(&rot);
    p->setPos(&p->m_pos);
    CharModelVoicePanSet(p->m_charNo, GetPan(&p->m_pos));
    bool vibDone = false;
    if (p->m_vibWait > 0 && --p->m_vibWait == 0) {
        vibDone = true;
    }
    bool waitDone = false;
    if (p->m_wait > 0 && --p->m_wait == 0) {
        waitDone = true;
    }
    p->m_dorrie->update();
    p->m_motTime = p->getMotionTime();
}

#ifdef __MWERKS__
/* retail inlines MSL's double sqrt (frsqrte + four Newton steps; m512 player.cpp's spelling) into CheckFall */
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

/* (also CAngle's ctor) */
template <class T> static inline T Min(T a, T b)
{
    return a < b ? a : b;
}

template <class T> static inline T Max(T a, T b)
{
    return a > b ? a : b;
}

/* a float atan2 (the arguments and the result each land in a temporary; m532) */
static inline float Atan2(float y, float x)
{
    return atan2(y, x);
}

/* updatePos's 10% ease */
static inline double Smooth(double from, double to)
{
    return 0.9 * from + 0.1 * to;
}

/* a Vec stored from doubles (retail frsp at each store) */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* lbl_1_rodata_32C: the per-slot landing points */
static const Vec s_fallTarget[4] = { { 150.0f, 0.0f, -100.0f }, { -150.0f, 0.0f, -100.0f },
                                     { 60.0f, 0.0f, -200.0f },  { -60.0f, 0.0f, -200.0f } };

void CPlayer::CheckFall(CPlayer* p)
{
    float scale;
    if (!p->m_out && p->m_wait <= 0 && !p->isOnDorrie()) {
        const Vec* tgt = &s_fallTarget[p->m_idx];
        SetVec(&p->m_vel, tgt->x - p->m_pos.x, 0.0, tgt->z - p->m_pos.z);
        float h = 2.0f * p->m_pos.y / 0.27240694f;
#ifdef __MWERKS__
        scale = 1.0 / MslSqrt(h);
#else
        scale = h > 0.0f ? (float)(1.0 / sqrt(h)) : 1.0f;
#endif
        PSVECScale(&p->m_vel, &p->m_vel, scale);
        p->setProc(&CPlayer::procFall);
        p->setMotion(6, true);
        p->vibrate(1);
        p->playSE(0x7DA);
        p->m_out = 1;
        p->m_dorrie->RequestMotion();
        --s_aliveNum;
        Reposition();
        s16 rank = s_aliveNum;
        int no = p->m_idx;
        if (!_CheckFlag(FLAG_MG_PRACTICE)) {
            GwPlayer[no].mgCoinBonus = rank;
        }
        BalanceCom();
    }
}

/* lbl_1_rodata_378: the Dorrie yaw per survivor mask (bit 3 - idx) and player */
static const float s_angleTbl[16][4] = {
    { 45.0f, -45.0f, 135.0f, -135.0f }, { 45.0f, -45.0f, 135.0f, 0.0f },   { 45.0f, -45.0f, 0.0f, -135.0f },
    { 45.0f, -45.0f, 90.0f, -90.0f },   { 45.0f, 0.0f, 135.0f, -135.0f },  { 45.0f, 0.0f, 135.0f, -180.0f },
    { 45.0f, -90.0f, 90.0f, -135.0f },  { 45.0f, 0.0f, 120.0f, -120.0f },  { 0.0f, -45.0f, 135.0f, -135.0f },
    { 90.0f, -45.0f, 135.0f, -90.0f },  { 0.0f, -45.0f, 180.0f, -135.0f }, { 0.0f, -45.0f, 120.0f, -120.0f },
    { 90.0f, -90.0f, 135.0f, -135.0f }, { 60.0f, -60.0f, 135.0f, -180.0f }, { 60.0f, -60.0f, 180.0f, -135.0f },
    { 45.0f, -45.0f, 135.0f, -135.0f },
};

/* the Dorries re-spread for the survivor mask; out players' Dorries turn too, and the last survivor's does not
 * (retail) */
static inline int SecToFrame(int sec)
{
    return sec * CPlayer::FPS;
}

void CPlayer::Reposition()
{
    CPlayer* p;
    CLinkNode* end;
    u8 mask = 0;
    float angle;
    WALK_PLAYERS(p, end) {
        if (!p->m_out) {
            mask |= 1 << (3 - p->m_idx);
        }
    }
    const float* tbl = s_angleTbl[mask];
    WALK_PLAYERS(p, end) {
        if (!p->m_out && s_aliveNum == 1) {
            continue;
        }
        angle = tbl[p->m_idx];
        p->m_dorrie->SetAngle(angle, (double)p->m_turnSec);
        p->setWait(SecToFrame(p->m_turnSec));
        p->resetBeat();
    }
}

/* when every survivor is COM, the first in list order gets an effective dif of 2 and the others 0, if their difs
 * span less than 2 (retail's tie-breaker, list order) */
void CPlayer::BalanceCom()
{
    CPlayer* p;
    CLinkNode* end;
    if (s_aliveNum < 2) {
        return;
    }
    WALK_PLAYERS(p, end) {
        if (!p->m_out) {
            if (p->m_padNo >= 0) {
                return;
            }
        }
    }
    int lo = 3;
    int hi = 0;
    /* retail keeps the first walk's end() for the other two */
    for (p = s_list.begin(); p != end; p = p->next()) {
        if (!p->m_out && p->m_padNo < 0) {
            p->m_bias = 0;
            lo = Min(lo, p->m_dif);
            hi = Max(hi, p->m_dif);
        }
    }
    if (hi - lo >= 2) {
        return;
    }
    int bias = 2;
    for (p = s_list.begin(); p != end; p = p->next()) {
        if (!p->m_out && p->m_padNo < 0) {
            p->m_bias = bias - p->m_dif;
            bias = 0;
        }
    }
}

void CPlayer::procInit()
{
    m_push = m_pushSmooth = m_pushStart;
    setMotion(1, true);
    setProc(&CPlayer::procIdle);
}

void CPlayer::procIdle()
{
    updatePos(false);
    updateMarker();
}

/* the 60-frame press window (m_beat_rec), the push, the push-level motions */
void CPlayer::procPlay()
{
    bool b = getInput();
    if (m_beat_rec.front()) {
        m_beatCount--;
    }
    m_beat_rec.pop_front();
    m_beat_rec.push_back(b);
    if (b) {
        double rate = m_beatCount / 60.0;
        push(120.0 * rate);
        playSE(0x7D9);
        m_beatCount++;
    }
    double r = (m_push - m_pushStart) / (m_pushMax - m_pushStart);
    if (r < 0.2) {
        setMotion(m_beatCount > 0 ? 2 : 1, true);
    } else if (m_motTime >= getMotionTime()) {
        if (r < 0.6) {
            setMotion(3, true);
        } else if (r < 1.0) {
            setMotion(4, true);
        }
    }
    bool ready = m_wait <= 0;
    updatePos(!ready);
    updateMarker();
}

static const float s_headForce[13] = { 120.0f, 120.0f, 40.0f, 0.0f, 20.0f, 40.0f, 0.0f,
                                       120.0f, 120.0f, 120.0f, 120.0f, 120.0f, 120.0f };

/* the arc; at y <= -100 the splash, the head force and the float */
void CPlayer::procFall()
{
    char* name = (char*)"ske_head";
    int c = m_charNo;
    int i;
    if (c < 0) {
        i = 0;
    } else if (c > 13) {
        i = 13;
    } else {
        i = c;
    }
    float t = s_headForce[i];
    m_vel.y -= 0.27240694f;
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    if (m_pos.y > -100.0f) {
        return;
    }
    Hu3DMotionForceSet(((CModel*)this)->id(), name, 0x200, t);
    CSingleton<CWater>::GetInstance()->Splash(&m_pos, -0.5f);
    setLayer(2);
    vibrate(2);
    setMotion(7, true);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    setProc(&CPlayer::procFloat);
}

/* face the centre (yaw eased 1%), the head held at the water surface */
void CPlayer::procFloat()
{
    CAngle a(0.0f, 360.0f, m_rotY);
    m_rotY = a.approach(180.0 * (Atan2(-m_pos.x, -m_pos.z) / M_PI), 0.01);
    char* name = (char*)"ske_head";
    float height = CSingleton<CWater>::GetInstance()->GetHeight(&m_pos);
    Vec h;
    Hu3DModelObjPosGet(((CModel*)this)->id(), name, &h);
    m_pos.y += height - h.y;
}

void CPlayer::procJudge()
{
    if (m_motion != 0 && CharMotionEndCheck(m_charNo)) {
        setMotion(0, true);
    }
    updatePos(false);
}

void CPlayer::procNone() {}

/* on the Dorrie's stage object at the smoothed push distance, facing the centre */
void CPlayer::updatePos(bool reset)
{
    if (reset) {
        m_push = m_pushStart;
    }
    m_pushSmooth = Smooth(m_pushSmooth, m_push);
    Vec v = { 0.0f, 0.0f, 0.0f };
    v.z = m_pushSmooth;
    Mtx m;
    m_dorrie->GetObjMtx(CDorrie::OBJ_STAGE, m);
    PSMTXMultVec(m, &v, &m_pos);
    m_rotY = 180.0 * (Atan2(-m_pos.x, -m_pos.z) / M_PI);
}

bool CPlayer::IsPressA(int pad)
{
    bool press = HuPadBtnDown[pad] & PAD_BUTTON_A;
    return press;
}

bool CPlayer::ComPress(int dif)
{
    return CRandom::randomMantissa() < (2 * dif + 4) * (1.0 / 60.0);
}

bool CPlayer::getInput()
{
    bool press;
    if (m_wait > 0) {
        return false;
    }
    if (m_padNo >= 0) {
        press = IsPressA(m_padNo);
    } else {
        press = ComPress(m_dif + m_bias);
    }
    return press;
}

/* line padding (resetBeat): the assert below must stay on retail's player.cpp:582 */

























void CPlayer::resetBeat()
{
    while (m_beat_rec.size() != 0) {
        m_beat_rec.pop_front();
    }
    for (int i = 0; i < FPS; i++) {
        m_beat_rec.push_back(false);
    }
    m_beatCount = 0;
    assert(m_beat_rec.size() == FPS);
}

/* the presser moves back (floored at m_pushMin), every other survivor forward by a / (alive - 1) */
void CPlayer::push(double a)
{
    m_push = Max(m_push - a, m_pushMin);
    if (s_aliveNum >= 2) {
        double share = a / (s_aliveNum - 1);
        FOR_EACH_PLAYER(p) {
            if (!p->m_out && p->m_idx != m_idx) {
                p->m_push += share;
                p->vibrate(0);
            }
        }
    }
}

bool CPlayer::isOnDorrie()
{
    return m_push < m_pushMax;
}

void CPlayer::updateMarker()
{
    Vec head;
    getHeadPos(&head);
    CRope* rope = CSingleton<CCenterObj>::GetInstance()->GetRope(m_idx);
    rope->Reset(&head);
}

Vec* CPlayer::getHeadPos(Vec* out)
{
    char* name = CharModelItemHookGet(m_charNo, 4, 0);
    Hu3DModelObjPosGet(((CModel*)this)->id(), name, out);
    return out;
}

/* line padding (createMotions): the assert below must stay on retail's player.cpp:650 */















void CPlayer::createMotions()
{
    m_motion_id.clear();
    m_motion_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0000);
    addMotion(0x87006E);
    addMotion(0x87006F);
    addMotion(0x8C0057);
    addMotion(0x8C0058);
    addMotion(0x870072);
    addMotion(0x8C002B);
    addMotion(0x8C001D);
    addMotion(0x8C002F);
    addMotion(0x8C0031);
    assert(m_motion_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
}

void CPlayer::addMotion(u32 data)
{
    m_motion_id.push_back(CharMotionCreate(m_charNo, data));
}

/* no assert (unlike m522): the index goes through vector::at. retail reads the model id into a local it never uses */
void CPlayer::setMotion(int no, bool loop)
{
    HU3DMODELID id = ((CModel*)this)->id();
    s16& r = m_motion_id.at(no);
    int m = (s16)r;
    if (m_motion != no || CharMotionEndCheck(m_charNo)) {
        setAttr(HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, m, 0.0f, 16.0f, loop ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
        m_motTime = 0.0f;
    }
}

float CPlayer::getMotionTime()
{
    if (CharMotionShiftIDGet(m_charNo) >= 0) {
        return CharMotionShiftTimeGet(m_charNo) - 1.0f;
    }
    return CharMotionTimeGet(m_charNo);
}

void CPlayer::vibrate(int kind)
{
    switch (kind) {
    case 0:
        if (m_vibWait <= 0) {
            omVibrate(m_idx, 6, 3, 3);
            int wait = 18;
            m_vibWait = wait;
        }
        break;
    case 1:
        omVibrate(m_idx, 12, 4, 2);
        break;
    case 2:
        omVibrate(m_idx, 24, 12, 0);
        break;
    }
}

void CPlayer::playSE(int id)
{
    HuAudFXPlayPan(id, GetPan(&m_pos));
}

/* ---- CAngle (m532's float scalar; the weak exec / reserve / deque copies interleave) ---- */

float CAngle::approach(float v, double rate)
{
    return m_value = wrap((float)(rate * diff(v) + m_value));
}

float CAngle::wrap(float v)
{
    if (v < m_min) {
        return m_max - (float)fmod(m_min - v, m_range);
    }
    if (v >= m_max) {
        return m_min + (float)fmod(v - m_max, m_range);
    }
    return v;
}

CAngle::CAngle(float a, float b, float v)
{
    m_min = Min(a, b);
    m_max = Max(a, b);
    m_range = m_max - m_min;
    m_value = wrap(v);
}

float CAngle::diff(float v)
{
    return diff(m_value, v);
}

float CAngle::diff(float a, float b)
{
    float d = wrap(b) - wrap(a);
    float ad = d < 0.0f ? -d : d;
    float r;
    if (ad < m_range / 2.0f) {
        r = d;
    } else {
        r = (m_range - ad) * (d < 0.0f ? 1 : -1);
    }
    return r;
}

} // namespace m537
