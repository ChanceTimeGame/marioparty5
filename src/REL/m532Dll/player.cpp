#include "REL/m532Dll/config.h"
#include "REL/m532Dll/param.h"
#include "REL/mgcpp/minigame.h"
#include "REL/m532Dll/player.h"
#include "REL/m532Dll/ball.h"
#include "REL/m532Dll/man_map.h"
#include "REL/m532Dll/score.h"
#include "REL/m532Dll/rumble_warn.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
}

namespace m532 {

/* the two team lists (bss AA0 / AB4, each with its DestructorChain record A94 / AA8): first = the front
 * player, first->next = the back player */
static TLinkList<CPlayer> s_team0;
static TLinkList<CPlayer> s_team1;

/* lbl_1_rodata_3B0 .. 434: the stand spots and paths (x is negated for team 0) */
static const Vec s_frontSpot = { 90.0f, 116.0f, 300.0f };
static const Vec s_backSpot = { 320.0f, 0.0f, 455.0f };
static const Vec s_carrySpot[3] = { { 265.0f, 98.0f, 207.0f }, { 205.0f, 98.0f, 155.0f }, { 145.0f, 98.0f, 102.0f } };
static const Vec s_throwTarget[3] = { { 336.0f, 280.0f, 126.0f }, { 275.0f, 280.0f, 75.0f }, { 213.0f, 280.0f, 23.0f } };
static const Vec s_missSpot = { 0.0f, 156.0f, 335.0f };
static const Vec s_backPath = { 245.0f, 98.0f, 305.0f };
static const Vec s_frontPath = { 210.0f, 98.0f, 314.0f };
static const Vec s_midPath = { 315.0f, 3.5f, 427.0f };

/* |v| through one inline return level (m501's VecLength) */
static inline float VecLength(Vec* v)
{
    return PSVECMag(v);
}

/* |a - b|, the difference left in b: one more inline return level (proc_catch 108A8: fmr x3) */
static inline float VecDistance(Vec* a, Vec* b)
{
    PSVECSubtract(a, b, b);
    return VecLength(b);
}

s16 GetPan(Vec* pos)
{
    Vec screen;
    Hu3D3Dto2D(pos, 1, &screen);
    screen.x *= 0.11111111f;
    int pan = 32.0f + screen.x;
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

void PlaySe(int se, Vec* pos)
{
    HuAudFXPlayPan(se, GetPan(pos));
}

void CPlayer::Create()
{
    for (int i = 0; i < 4; i++) {
        new CPlayer(i); /* owned by its team list */
    }
    Arrange(&s_team0, 0);
    Arrange(&s_team1, 1);
    s_team0.begin()->setMotion(2, true);
    s_team1.begin()->setMotion(2, true);
    CharEffectLayerSet(3);
}

void CPlayer::Arrange(TLinkList<CPlayer>* list, int side)
{
    if (CRandom::irandom() & 1) {
        CPlayer* first = list->begin();
        first->unlink();
        first->insertBack(list);
    }
    CPlayer* front = list->begin();
    CPlayer* back = front->next();
    int sign = side == 0 ? -1 : 1;
    front->m_pos = s_frontSpot;
    front->m_pos.x *= sign;
    front->m_yaw.set(front->m_yawTarget = sign * -45);
    back->m_pos = s_backSpot;
    back->m_pos.x *= sign;
    back->m_yaw.set(back->m_yawTarget = sign * -135);
}

void CPlayer::UpdateAll()
{
    TLinkList<CPlayer>::exec(&s_team0, Update);
    TLinkList<CPlayer>::exec(&s_team1, Update);
}

void CPlayer::Update(CPlayer* p)
{
    (p->*p->m_proc)();
    p->updateModel();
}

void CPlayer::SetFrontIdle()
{
    s_team0.begin()->setMotion(0, true);
    s_team1.begin()->setMotion(0, true);
}

void CPlayer::StartTiming(int cue)
{
    CPlayer* front[2] = { 0, 0 };
    front[0] = s_team0.begin();
    front[1] = s_team1.begin();
    for (CPlayer **p = front, **end = p + 2; p != end; p++) {
        (*p)->startTiming(cue);
    }
}

/* the round's winner by the fronts' `late`: a foul (< 0) loses to a valid press; two fouls: the later foul
 * wins; two presses: both >= s_reactTime = 3 (miss), else the smaller wins; ties by coin. *out = the ball's x. */
int CPlayer::Judge(float* out)
{
    CPlayer* f0 = s_team0.begin();
    CPlayer* f1 = s_team1.begin();
    int d0 = f0->getLate();
    int d1 = f1->getLate();
    /* retail lays out the four outcomes once, after every test (the tests branch to them) */
    if (d0 < 0 && d1 >= 0) {
        goto win1_left;
    }
    if (d1 < 0 && d0 >= 0) {
        goto win0_right;
    }
    if (d0 < 0 && d1 < 0) {
        if (d0 > d1) {
            goto win0_right;
        }
        if (d1 > d0) {
            goto win1_left;
        }
        if (!(CRandom::irandom() & 1)) {
            goto win1_left;
        }
        goto win0_right;
    }
    if (d0 >= s_reactTime && d1 >= s_reactTime) {
        *out = 0.0f;
        return 3;
    }
    if (d0 < d1) {
        goto win0_left;
    }
    if (d1 < d0) {
        goto win1_right;
    }
    if (!(CRandom::irandom() & 1)) {
        goto win1_right;
    }
win0_left:
    *out = -s_frontSpot.x;
    return 0;
win0_right:
    *out = s_frontSpot.x;
    return 0;
win1_right:
    *out = s_frontSpot.x;
    return 1;
win1_left:
    *out = -s_frontSpot.x;
    return 1;
}

bool CPlayer::IsBallTaken()
{
    CPlayer* f0 = s_team0.begin();
    CPlayer* f1 = s_team1.begin();
    if (f0->m_proc == &CPlayer::proc_hold || f1->m_proc == &CPlayer::proc_hold) {
        return true;
    }
    if (f0->m_ball == 0 && f1->m_ball == 0) {
        return true;
    }
    return false;
}

void CPlayer::GoHome()
{
    CPlayer* f0 = s_team0.begin();
    CPlayer* f1 = s_team1.begin();
    if (f0->addPath(&s_frontSpot)) {
        f0->setMotion(1, true);
    }
    f0->setProc(&CPlayer::proc_goHome);
    if (f1->addPath(&s_frontSpot)) {
        f1->setMotion(1, true);
    }
    f1->setProc(&CPlayer::proc_goHome);
}

/* the ball to the round's winner (a fouling rival gets it on the head); 3 (both missed): a ball drops between */
void CPlayer::Award(int who)
{
    CPlayer* f0 = s_team0.begin();
    CPlayer* f1 = s_team1.begin();
    bool foul0 = f0->getLate() < 0;
    bool foul1 = f1->getLate() < 0;
    Vec pos;
    switch (who) {
    case 0:
        if (foul1) {
            f1->setBonk(CSingleton<CMapMan>::GetInstance()->grabNearest(f1->getHeadPos(&pos)));
        } else {
            int ball = CSingleton<CMapMan>::GetInstance()->grabNearest(f0->getCatchPos(&pos));
            f0->setCatch(ball);
            f1->setWatch(ball);
        }
        break;
    case 1:
        if (foul0) {
            f0->setBonk(CSingleton<CMapMan>::GetInstance()->grabNearest(f0->getHeadPos(&pos)));
        } else {
            int ball = CSingleton<CMapMan>::GetInstance()->grabNearest(f1->getCatchPos(&pos));
            f1->setCatch(ball);
            f0->setWatch(ball);
        }
        break;
    default: {
        int ball = CSingleton<CMapMan>::GetInstance()->grabNearest((Vec*)&s_missSpot);
        f0->setWatch(ball);
        f1->setWatch(ball);
        break;
    }
    }
}

void CPlayer::Rotate()
{
    RotateTeam(&s_team0, 0);
    RotateTeam(&s_team1, 1);
}

void CPlayer::RotateTeam(TLinkList<CPlayer>* list, int side)
{
    CPlayer* front = list->begin();
    CPlayer* back = front->next();
    front->moveToBack();
    back->moveToFront();
    back->rumble(0);
    front->unlink();
    front->insertBack(list);
}

bool CPlayer::IsTimingDone()
{
    CPlayer* f0 = s_team0.begin();
    CPlayer* f1 = s_team1.begin();
    return f0->m_proc == &CPlayer::proc_idle && f1->m_proc == &CPlayer::proc_idle;
}

void CPlayer::SetResult(int result)
{
    switch (result) {
    case 0:
        SetResultTeam(&s_team0, 7);
        SetResultTeam(&s_team1, 8);
        break;
    case 1:
        SetResultTeam(&s_team0, 8);
        SetResultTeam(&s_team1, 7);
        break;
    case 2:
    case 3: {
        SetResultTeam(&s_team0, 8);
        SetResultTeam(&s_team1, 8);
        CPlayer* a0 = s_team0.begin();
        CPlayer* a1 = a0->next();
        CPlayer* b0 = s_team1.begin();
        CPlayer* b1 = b0->next();
        CharLoseVoicePlay(a0->m_charNo, a1->m_charNo, b0->m_charNo, b1->m_charNo);
        break;
    }
    }
}

/* every member turns to camera 1 and plays the win (7) / lose (8) motion; 7 records the winners (2VS2 payout in
 * ~CMinigameCore). Retail passes one scratch Vec for both of Hu3DCameraPosGet's other outputs. */
void CPlayer::SetResultTeam(TLinkList<CPlayer>* list, int motion)
{
    Vec cam;
    Vec tmp;
    CPlayer* p = list->begin();
    CLinkNode* end = list->end();
    Hu3DCameraPosGet(1, &cam, &tmp, &tmp);
    for (; p != end; p = p->next()) {
        p->m_yawTarget = 180.0 * (atan2f(cam.x - p->m_pos.x, cam.z - p->m_pos.z) / 3.141592653589793);
        p->setProc(&CPlayer::proc_result);
        p->setMotion(motion, false);
        if (motion == 7) {
            CMinigameCore::AddWinner(p->m_idx);
        }
    }
}

void CPlayer::DeleteAll()
{
    while (!s_team0.isEmpty()) {
        delete s_team0.last();
    }
    while (!s_team1.isEmpty()) {
        delete s_team1.last();
    }
}

/* the number of players on a team list (retail inlines it into the ctor: n and p in registers, the return
 * value through a stack temporary) */
static inline int CountTeam(TLinkList<CPlayer>* list)
{
    int n = 0;
    for (CPlayer* p = list->begin(); p != list->end(); p = p->next()) {
        n++;
    }
    return n;
}

/* fn_1_FE8C (186 insns). The team: GwPlayerConf.grp unless that list already has two players. */
CPlayer::CPlayer(int idx)
    : CModel(GwPlayerConf[idx].charNo, 1), m_idx(idx), m_charNo(GwPlayerConf[idx].charNo),
      m_grp(GwPlayerConf[idx].grp), m_padNo(GwPlayerConf[idx].type != 0 ? -1 : GwPlayerConf[idx].padNo),
      m_dif(GwPlayerConf[idx].dif), m_ball(0), m_timer(0), m_cue(0), m_comPress(0), m_path(),
      m_yaw(0.0f, 360.0f, 0.0f), m_wait(0), m_proc(&CPlayer::proc_none), m_motion_id(), m_motion(-1)
{
    setLayer(3);
    set_shadow();
    TLinkList<CPlayer>* list = m_grp == 0 ? &s_team0 : &s_team1;
    int team = m_grp;
    if (CountTeam(list) >= 2) {
        team = m_grp == 0 ? 1 : 0;
    }
    insertBack(team == 0 ? &s_team0 : &s_team1);
    m_team = team == 0 ? 0 : 1;
    createMotions();
    setMotion(0, true);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
}

CPlayer::~CPlayer() {}

void CPlayer::proc_none() {}

/* the COM press frame: r frames after the cue, r = frandom(lo[dif], hi[dif]) (+15 when >= 0) */
void CPlayer::startTiming(int cue)
{
    m_timer = s_roundTime;
    m_cue = cue;
    int react = 15;
    int tbl[4][2] = { { -4, 0 }, { -2, 0 }, { -1, 0 }, { 0, 0 } };
    tbl[0][1] = 1.1 * s_reactTime - react;
    tbl[1][1] = (double)s_reactTime - react;
    tbl[2][1] = 0.5 * s_reactTime - react;
    tbl[3][1] = 0.4 * s_reactTime - react;
    int lo = tbl[m_dif][0];
    int hi = tbl[m_dif][1];
    int r = CRandom::frandom(lo, hi);
    if (r >= 0) {
        r += react;
    }
    m_comPress = cue - r;
    setProc(&CPlayer::proc_timing);
}

void CPlayer::proc_timing()
{
    int timer = m_timer;
    if (m_cue == timer) {
        rumble(1);
    }
    if (isPressed()) {
        setMotion(2, true);
    } else if (getLate() >= s_reactTime || countDown()) {
        m_timer = 0;
    } else {
        CPlayer* rival = getRival();
        if (rival->m_proc == &CPlayer::proc_idle && rival->getLate() < 0) {
            m_timer = 0; /* the rival fouled */
        } else {
            return;
        }
    }
    setProc(&CPlayer::proc_idle);
}

bool CPlayer::isPressed()
{
    if (m_padNo >= 0) {
        return HuPadBtnDown[m_padNo] & PAD_BUTTON_A;
    }
    int timer = m_timer;
    return m_comPress == timer;
}

void CPlayer::setCatch(int ball)
{
    m_ball = ball;
    setProc(&CPlayer::proc_catch);
}

void CPlayer::proc_catch()
{
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball) {
        Vec q;
        Vec c;
        ball->predict(&q, 0.21666667f);
        getCatchPos(&c);
        c.y += CharModelHeightGet(m_charNo) * 0.5f;
        float dist = VecDistance(&q, &c);
        if (dist < 50.0) {
            setMotion(3, false);
            getRival()->setMotion(0, true);
            PlaySe(0x7AD, getHandPos(&q));
            setProc(&CPlayer::proc_hold);
        }
    }
}

/* the score-indexed spot (carry spot / throw target): clamp(points - 1, 0, 2); retail inlines it (a return
 * temporary per branch) */
static inline int SpotIndex(int n)
{
    if (n < 0) {
        return 0;
    }
    if (n > 2) {
        return 2;
    }
    return n;
}

void CPlayer::proc_hold()
{
    if (getMotionTime() < 12.0f) {
        return;
    }
    holdBall();
    if (CharMotionEndCheck(m_charNo)) {
        addPath(&s_carrySpot[SpotIndex(CSingleton<CScore>::GetInstance()->getPoint(m_team) - 1)]);
        setMotion(5, true);
        setProc(&CPlayer::proc_carry);
    }
}

void CPlayer::proc_carry()
{
    holdBall();
    if (updatePath()) {
        setMotion(6, false);
        setProc(&CPlayer::proc_throw);
    }
}

/* face the score-indexed target; from motion time 15 release the ball; at the motion's end go idle */
void CPlayer::proc_throw()
{
    holdBall();
    Vec t = s_throwTarget[SpotIndex(CSingleton<CScore>::GetInstance()->getPoint(m_team) - 1)];
    if (m_team == 0) {
        t.x *= -1.0f;
    }
    PSVECSubtract(&t, &m_pos, &t);
    m_yaw.approach(180.0 * (atan2f(t.x, t.z) / 3.141592653589793), 0.1);
    if (getMotionTime() < 15.0f) {
        return;
    }
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball) {
        Vec t2 = s_throwTarget[SpotIndex(CSingleton<CScore>::GetInstance()->getPoint(m_team) - 1)];
        if (m_team == 0) {
            t2.x *= -1.0f;
        }
        ball->throwTo(&t2);
        PlaySe(0x7B0, ball->getPos());
        m_ball = 0;
    }
    if (CharMotionEndCheck(m_charNo)) {
        int wait = 60; /* a literal, not s_reactTime; retail holds it in a register (li r20,60) */
        m_wait = wait;
        setMotion(0, true);
        setProc(&CPlayer::proc_idle);
    }
}

void CPlayer::setBonk(int ball)
{
    m_ball = ball;
    setProc(&CPlayer::proc_bonk);
}

void CPlayer::proc_bonk()
{
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball) {
        float height[13] = { 170.0f, 170.0f, 210.0f, 190.0f, 170.0f, 210.0f, 240.0f, 170.0f, 170.0f, 170.0f, 170.0f,
            170.0f, 170.0f };
        Vec lim = { 0.0f, 0.0f, 0.0f };
        lim.x = m_pos.x;
        lim.y = m_pos.y + height[m_charNo];
        lim.z = m_pos.z;
        Vec q;
        ball->predict(&q, 0.083333336f);
        if (!(q.y > lim.y)) {
            setMotion(4, false);
            rumble(2);
            setProc(&CPlayer::proc_bonkPass);
        }
    }
}

void CPlayer::proc_bonkPass()
{
    if (!(getMotionTime() < 5.0f)) {
        CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
        if (ball) {
            CPlayer* rival = getRival();
            Vec c;
            ball->throwTo(rival->getCatchPos(&c));
            PlaySe(0x7AF, ball->getPos());
            rival->setCatch(m_ball);
            rival->setMotion(2, true);
            m_ball = 0;
            setProc(&CPlayer::proc_watch);
        }
    }
}

void CPlayer::setWatch(int ball)
{
    m_ball = ball;
    setProc(&CPlayer::proc_watch);
}

void CPlayer::proc_watch()
{
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball == 0 || ball->isLanded()) {
        m_ball = 0;
        setMotion(0, true);
        setProc(&CPlayer::proc_idle);
    }
}

void CPlayer::moveToBack()
{
    addPath(&s_carrySpot[0]);
    addPath(&s_backPath);
    addPath(&s_midPath);
    addPath(&s_backSpot);
    bool now = m_wait <= 0;
    setMotion(now ? 1 : 0, true);
    setProc(&CPlayer::proc_moveToBack);
}

void CPlayer::proc_moveToBack()
{
    bool walk = false;
    if (m_wait > 0 && --m_wait == 0) {
        walk = true;
    }
    if (walk) {
        setMotion(1, true);
    }
    if (m_wait <= 0 && updatePath()) {
        m_yawTarget = m_team == 0 ? 135 : -135;
        setProc(&CPlayer::proc_turn);
    }
}

void CPlayer::moveToFront()
{
    addPath(&s_midPath);
    addPath(&s_frontPath);
    addPath(&s_frontSpot);
    setMotion(1, true);
    setProc(&CPlayer::proc_moveToFront);
}

void CPlayer::proc_moveToFront()
{
    if (updatePath()) {
        m_yawTarget = m_team == 0 ? 45 : -45;
        setProc(&CPlayer::proc_turn);
    }
}

void CPlayer::proc_goHome()
{
    if (updatePath()) {
        setMotion(0, true);
        setProc(&CPlayer::proc_idle);
    }
}

void CPlayer::proc_turn()
{
    m_yaw.approach(m_yawTarget, 0.1);
    if (fabs(m_yaw.diff(m_yawTarget)) < 1.0) {
        m_yaw.set(m_yawTarget);
        setMotion(0, true);
        setProc(&CPlayer::proc_idle);
    }
}

void CPlayer::proc_result()
{
    m_yaw.approach(m_yawTarget, 0.1);
    if (CharMotionEndCheck(m_charNo)) {
        setProc(&CPlayer::proc_idle);
    }
}

void CPlayer::proc_idle() {}

CPlayer* CPlayer::getRival()
{
    return m_team == 0 ? s_team1.begin() : s_team0.begin();
}

/* by-value min/max (retail inlines them: the ternary result, then the return value, each in its own
 * register -- updatePath's double step, the CAngle ctor's bounds) */
template <class T> static inline T Min(T a, T b)
{
    return a < b ? a : b;
}

template <class T> static inline T Max(T a, T b)
{
    return a > b ? a : b;
}

/* updatePath's float atan2 (the arguments and the result each land in a temporary) */
static inline float Atan2(float y, float x)
{
    return atan2(y, x);
}

/* PSVECScale returning its output (updatePath hands the result to PSVECAdd through two register copies) */
static inline Vec* VecScale(Vec* in, Vec* out, float s)
{
    PSVECScale(in, out, s);
    return out;
}

/* walk toward the first waypoint at 200/60 per frame (a double: retail's step literal); arrive when the
 * remaining distance is 0 (sheet §7 R7) */
bool CPlayer::updatePath()
{
    if (m_path.size() == 0) {
        return true;
    }
    Vec d;
    std::vector<Vec>::iterator it = m_path.begin();
    PSVECSubtract(&*it, &m_pos, &d);
    /* retail copies the length through three float registers (as addPath) */
    float dist;
    float mag = PSVECMag(&d);
    float len = mag;
    dist = len;
    double step = Min(3.3333333333333335, (double)dist);
    if (step <= 0.0) {
        std::vector<Vec>::iterator first = m_path.begin();
        m_path.erase(first);
        return m_path.size() == 0;
    }
    m_yaw.approach(180.0 * (Atan2(d.x, d.z) / 3.141592653589793), 0.1);
    Vec* p = VecScale(&d, &d, step / dist);
    PSVECAdd(p, &m_pos, &m_pos);
    return false;
}

void CPlayer::updateModel()
{
    Vec rot = { 0.0f, 0.0f, 0.0f };
    rot.y = m_yaw.get();
    setPos(&m_pos);
    setRot(&rot);
    CharModelVoicePanSet(m_charNo, GetPan(&m_pos));
}

int CPlayer::getLate()
{
    int timer = m_timer;
    return m_cue - timer;
}

Vec* CPlayer::getHandPos(Vec* out)
{
    char* hook = CharModelItemHookGet(m_charNo, 2, 0);
    Hu3DModelObjPosGet(((CModel*)this)->id(), hook, out);
    return out;
}

Vec* CPlayer::getCatchPos(Vec* out)
{
    *out = m_pos;
    float s;
    if (out->x == 0.0f) {
        s = 0.0f;
    } else {
        s = out->x < 0.0f ? -1.0f : 1.0f;
    }
    out->x += 100.0 * (0.3 * -s);
    out->z += 30.0;
    return out;
}

Vec* CPlayer::getHeadPos(Vec* out)
{
    *out = m_pos;
    out->y += CharModelHeightGet(m_charNo) / 2.0f;
    return out;
}

void CPlayer::holdBall()
{
    CBall* ball = static_cast<CBall*>(CObject::GetHandlePtr(m_ball));
    if (ball) {
        Vec hand;
        ball->hold(getHandPos(&hand));
    }
}

bool CPlayer::addPath(const Vec* p)
{
    Vec t = *p;
    if (m_team == 0) {
        t.x *= -1.0f;
    }
    m_path.push_back(t);
    PSVECSubtract(&m_pos, &t, &t);
    /* retail copies the length through three float registers (f30 -> f29 -> f31): three locals, d first */
    float d;
    float mag = PSVECMag(&t);
    float dist = mag;
    d = dist;
    return d >= 3.3333333f;
}

void CPlayer::createRumbleWarn()
{
    Vec pos = m_pos;
    pos.y += 50.0 + CharModelHeightGet(m_charNo);
    new CRumbleWarn(&pos); /* owned by the CObject list */
}

void CPlayer::createMotions()
{
    m_motion_id.clear();
    createMotion(0x8C0000); /* 0 idle */
    createMotion(0x8C0001); /* 1 walk */
    createMotion(0x8700D0); /* 2 ready */
    createMotion(0x8700D1); /* 3 catch */
    createMotion(0x8700D2); /* 4 bonk */
    createMotion(0x8C008C); /* 5 carry */
    createMotion(0x8C008D); /* 6 throw */
    createMotion(0x8C0030); /* 7 win */
    createMotion(0x8C0031); /* 8 lose */
    /* the assert below is retail's player.cpp:894 (a #line, not 160 lines of padding: edits above keep it) */
#line 894
    assert(m_motion_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
}

void CPlayer::createMotion(int dataNum)
{
    m_motion_id.push_back(CharMotionCreate(m_charNo, dataNum));
}

void CPlayer::setMotion(int slot, bool loop)
{
    if (m_motion != slot || CharMotionEndCheck(m_charNo)) {
        CharModelAttrSet(m_charNo, HU3D_MOTATTR_PAUSE);
        bool noBlend = m_charNo == 6 && slot == 3;
        float blend = noBlend ? 0 : 16;
        CharMotionShiftSet(m_charNo, m_motion_id[slot], 0.0f, blend, loop ? HU3D_MOTATTR_LOOP : 0);
        m_motion = slot;
    }
}

float CPlayer::getMotionTime()
{
    if (CharMotionShiftIDGet(m_charNo) >= 0) {
        return CharMotionShiftTimeGet(m_charNo) - 1.0f;
    }
    return CharMotionTimeGet(m_charNo);
}

void CPlayer::rumble(int kind)
{
    switch (kind) {
    case 0:
        omVibrate(m_idx, 12, 4, 2);
        break;
    case 1:
        if (IsRumbleAll()) {
            omVibrate(m_idx, s_reactTime, 12, 0);
        } else {
            createRumbleWarn();
        }
        break;
    case 2:
        omVibrate(m_idx, 12, 12, 0);
        break;
    }
}

/* lbl_1_rodata_564 */
static const u32 s_rumbleMask[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };

bool CPlayer::IsRumblePad(int pad)
{
    return pad < 0 ? true : (bool)(HuPadRumbleGet() & s_rumbleMask[pad]);
}

/* every human pad can rumble (COMs count as able); true at once when all four are COMs */
bool CPlayer::IsRumbleAll()
{
    if (GwCommon.rumbleF == 0) {
        return false;
    }
    int a0 = s_team0.begin()->m_padNo;
    int a1 = s_team0.begin()->next()->m_padNo;
    int b0 = s_team1.begin()->m_padNo;
    int b1 = s_team1.begin()->next()->m_padNo;
    if (a0 < 0 && a1 < 0 && b0 < 0 && b1 < 0) {
        return true;
    }
    return IsRumblePad(a0) && IsRumblePad(a1) && IsRumblePad(b0) && IsRumblePad(b1);
}

/* CAngle (player.h): defined here, after every caller (retail calls them all out of line), in retail order */
void CAngle::set(float v)
{
    m_value = wrap(v);
}

float CAngle::diff(float v)
{
    return diff(m_value, v);
}

void CAngle::approach(float v, double rate)
{
    float d = diff(m_value, v);
    m_value = wrap((float)(m_value + rate * d));
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

float CAngle::get()
{
    return m_value;
}

CAngle::CAngle(float a, float b, float v)
{
    m_min = Min(a, b);
    m_max = Max(a, b);
    m_range = m_max - m_min;
    m_value = wrap(v);
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

} // namespace m532
