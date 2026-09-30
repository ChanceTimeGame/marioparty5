/* player.cpp -- m522 GetPan / CPlayerBase / CSolo / CTeam / CComPad / CAngle (player.h). Retail order: sheet
 * player.md §3 (GetPan, the statics CreateAll .. FindSolo, CPlayerBase(), [~vector<s16>, ~__vector_pod<s16>,
 * ~__vector_base<s16>, ~TLinkItem<CPlayerBase>], ~CPlayerBase, Update .. vibrate; CSolo 10324..12530; CTeam
 * 12530..14868; CComPad; [main, ready]; CAngle ctor .. get; [at, exec x2, insert]; CAngle::diff(a, b); __sinit;
 * [~TLinkList<CPlayerBase>]). The asserts sit on retail's player.cpp:257 / :669 / :1060 (test/fixlines.py).
 * Forks (SKELETON.md §7): F4 owns 0xF564..0x10324 (GetPan, statics, CPlayerBase) and 0x14868..0x15728 (CComPad,
 * CAngle, the template copies, __sinit) and player.h; F6 0x10324..0x12530 (CSolo); F5 0x12530..0x14868 (CTeam). Includes minigame.h FIRST: the triple is .bss
 * A48..A50, then s_aliveNum A54, then s_list A64 (its DestructorChain A58).
 * EXACT: GetPan (= m532 EE18), DeleteAll's CW path (= m512 91AC), CAngle diff / approach / wrap / get /
 * diff(a, b) (= m532 128C0 / 128FC / 12970 / 12A0C / 13390), the vector<s16> / TLinkList weak set, __sinit.
 * Everything else is drafted from the sheet + asm (STUB = long body still to write); the PTMF assignments are in
 * retail use order (they ARE .data 5A0..720). */
#include "REL/mgcpp/minigame.h"
#include "REL/m522Dll/player.h"
#include "REL/m522Dll/stage.h"
#include "REL/m522Dll/bubble.h"
#include "REL/m522Dll/sunfire.h"
#include "REL/mgcpp/random.h"
extern "C" {
#include "game/hsfex.h" /* Hu3D3Dto2D */
/* actman.h does not declare it (as include/REL/m520Dll.h) */
void MgActorPosGet(MGACTOR* actorP, HuVecF* pos);
}

namespace m522 {

static int s_aliveNum;
static TLinkList<CPlayerBase> s_list;   /* bss A64 (DestructorChain A58); rotated every frame (retail) */

s16 GetPan(Vec* pos)
{
    Vec screen;
    Hu3D3Dto2D(pos, 1, &screen);
    screen.x *= 0.11111111f;
    int result;
    int pan = 32.0f + screen.x;
    if (pan < 0) {
        result = 0;
    } else if (pan > 127) {
        result = 127;
    } else {
        result = pan;
    }
    return result;
}

/* lbl_1_rodata_4D0: the three's drop-in points */
static const Vec s_startPos[3] = { { 0.0f, 2500.0f, -200.0f }, { -173.2f, 3000.0f, 100.0f }, { 173.2f, 3500.0f, 100.0f } };

void CPlayerBase::CreateAll()
{
    s_aliveNum = 0;
    const Vec* pos = s_startPos;
    for (int i = 0; i < 4; i++) {
        if (GwPlayerConf[i].grp == 0) {
            new CSolo(i);
        } else {
            new CTeam(i, pos++);
        }
    }
    CharEffectLayerSet(5);
}

void CPlayerBase::UpdateAll()
{
    TLinkList<CPlayerBase>::exec(&s_list, Update);
    MgActorExec();
    CPlayerBase* p = s_list.begin();
    if (p != s_list.end()) {
        p->unlink();
        p->insertBack(&s_list);
    }
}

/* retail reads begin() then end() once into a local */
#define FOR_EACH_PLAYER(p)                                                                                      \
    CPlayerBase* p = s_list.begin();                                                                             \
    CLinkNode* end_ = s_list.end();                                                                              \
    for (; p != end_; p = p->next())

void CPlayerBase::ReadyAll()
{
    FOR_EACH_PLAYER(p) {
        p->setProc(&CPlayerBase::ready);
    }
}

void CPlayerBase::GoAll()
{
    FOR_EACH_PLAYER(p) {
        p->setProc(&CPlayerBase::go);
    }
}

void CPlayerBase::JudgeAll()
{
    FOR_EACH_PLAYER(p) {
        p->judge();
    }
}

void CPlayerBase::ResultAll()
{
    FOR_EACH_PLAYER(p) {
        p->result();
    }
}

void CPlayerBase::DeleteAll()
{
    while (!s_list.isEmpty()) {
        delete s_list.last();
    }
}

int CPlayerBase::GetAliveNum()
{
    return s_aliveNum;
}

int CPlayerBase::CheckEnd()
{
    if (s_aliveNum <= 0) {
        return 0;
    }
    if (CTeam::CountGrounded() == s_aliveNum) {
        return 1;
    }
    return -1;
}

CPlayerBase* CPlayerBase::Find(int idx)
{
    FOR_EACH_PLAYER(p) {
        if (p->m_idx == idx) {
            return p;
        }
    }
    return 0;
}

CPlayerBase* CPlayerBase::FindSolo()
{
    FOR_EACH_PLAYER(p) {
        if (p->m_group == 0) {
            return p;
        }
    }
    return 0;
}

CPlayerBase::CPlayerBase(int idx)
    : m_proc(&CPlayerBase::main), m_idx(idx), m_charNo(GwPlayerConf[idx].charNo), m_group(GwPlayerConf[idx].grp),
      m_padNo(GwPlayerConf[idx].type ? -1 : GwPlayerConf[idx].padNo), m_dif(GwPlayerConf[idx].dif), m_vibWait(0),
      m_frame(0), m_motion(-1)
{
    insertBack(&s_list);
}

CPlayerBase::~CPlayerBase() {}

/* retail: a dead "reached 0" local */
void CPlayerBase::Update(CPlayerBase* p)
{
    (p->*(p->m_proc))();
    p->draw();
    bool done = false;
    if (p->m_vibWait > 0 && --p->m_vibWait == 0) {
        done = true;
    }
    p->m_frame++;
}

void CPlayerBase::addMotion(u32 dataNum)
{
    m_motion_id.push_back(CharMotionCreate(m_charNo, dataNum));
}

/* line padding (setMotion): the assert below must stay on retail's player.cpp:257 */


































void CPlayerBase::setMotion(u32 motion, bool loop)
{
    assert(motion < m_motion_id.size());
    if (m_motion != (int)motion || CharMotionEndCheck(m_charNo)) {
        CharModelAttrSet(m_charNo, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, m_motion_id[motion], 0.0f, 16.0f, loop ? HU3D_MOTATTR_LOOP : 0);
        m_motion = motion;
    }
}

float CPlayerBase::getMotionTime()
{
    if (CharMotionShiftIDGet(m_charNo) >= 0) {
        return CharMotionShiftTimeGet(m_charNo) - 1.0f;
    }
    return CharMotionTimeGet(m_charNo);
}

void CPlayerBase::setVisible(bool on)
{
    if (on) {
        CharModelAttrReset(m_charNo, HU3D_ATTR_DISPOFF);
    } else {
        CharModelAttrSet(m_charNo, HU3D_ATTR_DISPOFF);
    }
    CharModelFxFlagSet(m_charNo, on);
}

void CPlayerBase::vibrate(int kind)
{
    switch (kind) {
    case 0:
    case 1:
        omVibrate(m_idx, 12, 6, 6);
        break;
    case 2:
        omVibrate(m_idx, 6, 3, 6);
        break;
    case 3:
        if (m_vibWait <= 0) {
            omVibrate(m_idx, 12, 12, 0);
            int wait = 18;
            m_vibWait = wait;
        }
        break;
    case 4:
        omVibrate(m_idx, 24, 12, 0);
        break;
    }
}

/* ---- CSolo (F6: .text 0x10324..0x12530) ---- */

/* file-local helpers, inlined everywhere (retail's register copies show the by-value parameters and returns).
 * Min / Max are used by CSolo, CTeam and CAngle (F6 hoisted them here from above the CAngle ctor). */
template <class T> static inline T Min(T a, T b)
{
    return a < b ? a : b;
}

template <class T> static inline T Max(T a, T b)
{
    return a > b ? a : b;
}

/* a Vec from three doubles, each rounded at its store (F3's bubble.cpp spelling) */
static inline void SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

/* seconds to frames (60 fps) */
static inline double SecToFrames(double sec)
{
    return 60.0 * sec;
}

/* true with probability p */
static inline bool Chance(double p)
{
    return CRandom::randomMantissa() < p;
}

/* (1 - t) a + t b; CSolo::procIdle's m_bobAmp eases toward 10 by 1% a frame through it */
template <class T> static inline T Lerp(T a, T b, double t)
{
    return (1.0 - t) * a + t * b;
}

CSolo::CSolo(int idx)
    : CPlayerBase(idx), CModel(GwPlayerConf[idx].charNo, 2), m_action(ACTION_NONE), m_strikeY(0.0f), m_bobPhase(0.0f),
      m_bobAmp(10.0f), m_rotY(90.0f), m_rotX(0.0f), m_item(new CModel(0x500009u)), m_itemFx(new CModel(0x50000Au))
{
    m_itemMot = Hu3DJointMotion(m_itemFx->id(), HuDataSelHeapReadNum(0x50000B, HU_MEMNUM_OVL, HEAP_MODEL));
    m_itemRotY = m_rotY;
    m_hookName = CharModelItemHookGet(m_charNo, 4, 0);
    m_unk8C = 0;
    setLayer(5);
    HU3DMODELID id = ((CModel*)this)->id();
    Hu3DModelHookSet((int)id, m_hookName, m_item->id());
    m_itemFx->setLayer(5);
    m_itemFx->setAttr(HU3D_MOTATTR_LOOP);
    double y = CSingleton<CStage>::GetInstance()->GetTopY() - 100.0f;
    m_pos.x = -550.0f;
    m_pos.y = y;
    m_pos.z = 0.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    draw();
    createMotions();
    setMotion(0, true);
}

CSolo::~CSolo() {}

int CSolo::getAction()
{
    return getMotionTime() > 15.0f ? m_action : ACTION_NONE;
}

void CSolo::go()
{
    setProc(&CSolo::procIdle);
}

/* fn_1_10A00: bob amplitude eases back to 10; once the stage has settled, the input starts a strike (A) or a raise (B)
 * with the swing motion and SE 0x73A. Retail guards on m_unk8C > 0, which nothing ever sets (dead) */
void CSolo::procIdle()
{
    m_bobAmp = Lerp<float>(m_bobAmp, 10.0f, 0.01);
    if (m_unk8C > 0 || !CSingleton<CStage>::GetInstance()->IsDropDone()) {
        return;
    }
    m_action = getInput();
    switch (m_action) {
    case ACTION_STRIKE:
        setMotion(1, false);
        HuAudFXPlayPan(0x73A, GetPan(&m_pos));
        setProc(&CSolo::procStrike);
        break;
    case ACTION_RAISE:
        setMotion(1, false);
        HuAudFXPlayPan(0x73A, GetPan(&m_pos));
        setProc(&CSolo::procRaise);
        break;
    }
}

/* fn_1_10DF8: at t = 25 the strike knocks out the top block at (-400, top + 100, 0) (a local aggregate {-400, 0, 0}
 * with y patched) */
void CSolo::procStrike()
{
    m_bobAmp *= 0.8;
    float t = getMotionTime();
    if (t < 25.0f) {
        return;
    }
    Vec p = { -400.0f, 0.0f, 0.0f };
    p.y = 100.0f + CSingleton<CStage>::GetInstance()->GetTopY();
    Vec rot = { 0.0f, 90.0f, 0.0f };
    CSingleton<CStage>::GetInstance()->BreakBlock(&p);
    CharEffectHitCreate(1, &p, &rot);
    vibrate(0);
    m_bobAmp = 0.0f;
    m_strikeY = m_pos.y;
    setProc(&CSolo::procRecover);
}

/* fn_1_1103C: after t = 30 the solo rises back from the strike height to max(200, top - 100). Retail divides by
 * CharMotionMaxTimeGet - 30 (0 or negative for a motion no longer than 30 frames; the swing is longer) */
void CSolo::procRecover()
{
    float t = getMotionTime();
    if (t <= 30.0f) {
        return;
    }
    float max = CharMotionMaxTimeGet(m_charNo);
    float range = max - 30.0f;
    float to = Max<float>(200.0f, CSingleton<CStage>::GetInstance()->GetTopY() - 100.0f);
    float k = (t - 30.0f) / range;
    m_pos.y = Lerp<float>(m_strikeY, to, k);
    if (CharMotionEndCheck(m_charNo)) {
        m_bobPhase = M_PI;
        m_bobAmp = 80.0f;
        setMotion(0, true);
        m_action = ACTION_NONE;
        setProc(&CSolo::procIdle);
    }
}

/* fn_1_113BC: at t = 16 the swing plays in reverse (HU3D_MOTATTR_REV: the item goes back down) */
void CSolo::procRaise()
{
    float t = getMotionTime();
    if (t >= 16.0f) {
        CharModelAttrSet(m_charNo, HU3D_MOTATTR_REV);
        setProc(&CSolo::procHold);
    }
}

/* fn_1_114CC: raised and reversing; back to idle when the reversed swing ends, unless the input strikes (forward again) */
void CSolo::procHold()
{
    if (CharMotionEndCheck(m_charNo)) {
        setMotion(0, true);
        m_action = ACTION_NONE;
        setProc(&CSolo::procIdle);
    } else if (getInput() == ACTION_STRIKE) {
        m_action = ACTION_STRIKE;
        CharModelAttrReset(m_charNo, HU3D_MOTATTR_REV);
        setProc(&CSolo::procStrike);
    }
}

/* fn_1_11694: the winner floats up to 400 above the top and turns to face front (rotY down to 0 by 15/29 per frame) */
void CSolo::procWinFloat()
{
    m_bobAmp *= 0.9;
    m_vel.y = 0.01 * (400.0f + CSingleton<CStage>::GetInstance()->GetTopY() - m_pos.y);
    m_rotY = Max<double>(m_rotY - 15.0 / 29.0, 0.0);
}

/* fn_1_117EC: the loser falls (gravity 0.2724 / frame); below y = -100 it is flung away (motion 3) */
void CSolo::procLoseFall()
{
    m_vel.y -= 0.27240694f;
    if (m_pos.y < -100.0f) {
        setMotion(3, true);
        m_vel.x = -25.0f / 3.0f;
        m_vel.y = 50.0f / 3.0f;
        m_vel.z = -25.0f / 3.0f;
        vibrate(4);
        setProc(&CSolo::procLoseFly);
    }
}

void CSolo::procLoseFly()
{
    m_vel.y -= 0.27240694f;
    m_rotY += 0.1 * (-135.0f - m_rotY);
}

void CSolo::procWinPose()
{
    m_rotX += 0.01 * (-30.0f - m_rotX);
}

/* fn_1_11A20 (ResultAll): the solo loses while any team member is in (falls, then is flung: procLoseFall), else it
 * poses (procWinPose). The pan is taken once, before the test */
void CSolo::result()
{
    s16 pan = GetPan(&m_pos);
    if (s_aliveNum > 0) {
        Hu3DMotionSet(m_itemFx->id(), m_itemMot);
        m_itemFx->resetAttr(HU3D_MOTATTR_LOOP);
        setMotion(2, true);
        vibrate(2);
        HuAudFXPlayPan(0x748, (int)pan);
        setProc(&CSolo::procLoseFall);
    } else {
        m_vel.x = 0.0f;
        m_vel.y = 0.0f;
        m_vel.z = 0.0f;
        setMotion(4, true);
        CharFXPlayPan(m_charNo, 0x1FA, (int)pan);
        setProc(&CSolo::procWinPose);
    }
}

void CSolo::judge()
{
    if (s_aliveNum <= 0) {
        CMinigameCore::AddWinner(m_idx);
    }
    CharModelHookDustCreate(m_charNo, m_hookName);
    m_vel.x = -1.0f / 6.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    setProc(&CSolo::procWinFloat);
}

/* fn_1_11E34 (every frame after m_proc): the body bobs by amp * sin(phase) and integrates m_vel; the item effect
 * model follows the hand hook object and eases its yaw toward the body's. One Vec temporary serves every call */
void CSolo::draw()
{
    Vec v;
    SetVec(&v, m_pos.x, m_pos.y + m_bobAmp * sin(m_bobPhase), m_pos.z);
    setPos(&v);
    PSVECAdd(&m_vel, &m_pos, &m_pos);
    m_bobPhase += M_PI / 60.0;
    SetVec(&v, m_rotX, m_rotY, 0.0);
    setRot(&v);
    char* name = CharModelItemHookGet(m_charNo, 4, 4);
    Hu3DModelObjPosGet(((CModel*)this)->id(), name, &v);
    m_itemFx->setPos(&v);
    m_itemRotY += 0.01 * (m_rotY - m_itemRotY);
    SetVec(&v, 0.0, m_itemRotY, 0.0);
    m_itemFx->setRot(&v);
}

int CSolo::getInput()
{
    return m_padNo >= 0 ? getPadInput() : getComInput();
}

int CSolo::getPadInput()
{
    u32 btn = HuPadBtnDown[m_padNo];
    if (btn & PAD_BUTTON_A) {
        return ACTION_STRIKE;
    }
    if (btn & PAD_BUTTON_B) {
        return ACTION_RAISE;
    }
    return ACTION_NONE;
}

/* fn_1_120DC (sheet §1.3): a COM acts only when idle, on average once per 0.2 * (4 - dif) seconds. With team
 * members airborne it strikes with probability lerp(1 - grounded / alive, 1, 0.3 * dif); with all grounded it
 * raises (1/3), strikes (1/3) or waits. Retail divides by the alive count and by (4 - dif) * 12 unguarded: the
 * first is > 0 whenever this runs (grounded < alive), the second only 0 for dif 4 (dif is 0..3) */
int CSolo::getComInput()
{
    float r;
    double t;
    double a;
    if (m_action != ACTION_NONE) {
        return ACTION_NONE;
    }
    if (CRandom::randomMantissa() > 1.0 / SecToFrames(0.2 * (4 - m_dif))) {
        return ACTION_NONE;
    }
    int n = CTeam::CountGrounded();
    int alive = GetAliveNum();
    if (n < alive) {
        a = 1.0 - (double)n / (double)alive;
        t = 0.3 * m_dif;
        if (Chance(Lerp<double>(a, 1.0, t))) {
            return ACTION_STRIKE;
        }
    }
    r = CRandom::frandom(3.0f);
    if (r > 2.0) {
        return ACTION_RAISE;
    }
    if (r > 1.0) {
        return ACTION_STRIKE;
    }
    return ACTION_NONE;
}

/* line padding (CSolo motions): the assert below must stay on retail's player.cpp:669 */


















































void CSolo::createMotions()
{
    m_motion_id.clear();
    addMotion(0x8C005E);
    addMotion(0x8C005F);
    addMotion(0x8C002B);
    addMotion(0x8C0015);
    addMotion(0x8C0060);
    Hu3DMotionAttrSet(m_motion_id[4], 1);
    assert(m_motion_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
}

/* ---- CTeam (F5: .text 0x12530..0x14868) ---- */

CTeam::CTeam(int idx, const Vec* pos)
    : CPlayerBase(idx), m_out(false), m_landWait(0), m_pos(*pos), m_rotY(-90.0f), m_rotX(0.0f), m_dropping(false),
      m_manual(false), m_comProc(&CTeam::procCom), m_comHold(0), m_wasOnStage(true), m_pushed(false)
{
    m_com.m_yaw = -M_PI / 2;
    m_com.m_x = 0.0f;
    m_com.m_y = 0.0f;
    m_com.m_btnDown = 0;
    m_com.m_btn = 0;
    MGACTOR_PARAM param = { 0.0f, 40.0f, 0, 0, NarrowHook, 0, 0, NULL };
    param.height = CharModelHeightGet(m_charNo);
    param.param = idx;
    m_mp = MgPlayerCreate(idx, &param, 4, 1, 0x13, NULL);
    MgPlayerAttrSet(m_mp, 2);
    MgPlayerVibrateCreate(m_mp);
    MgPlayerPauseOn(m_mp);
    createMotions();
    HU3DMODELID id = m_mp->actor->mdlId;
    Hu3DModelShadowSet(id);
    Hu3DModelLayerSet((int)id, 5);
    m_startPos.x = pos->x;
    m_startPos.y = pos->y;
    m_startPos.z = pos->z;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    MgActorPosUpdate(m_mp->actor, &m_startPos);
    m_mp->actor->rotY = m_rotY;
    s_aliveNum++;
}

CTeam::~CTeam()
{
    MgActorKill(m_mp->actor);
}

int CTeam::CountGrounded()
{
    /* retail reads begin, then the sentinel once, then zeroes the count */
    CPlayerBase* p = s_list.begin();
    CLinkNode* end = s_list.end();
    int n = 0;
    for (; p != end; p = p->next()) {
        int group = p->m_group;
        if (group != 0) {
            CTeam* t = static_cast<CTeam*>(p);
            if (!t->m_out && t->isOnGround()) {
                n++;
            }
        }
    }
    return n;
}

void CTeam::main()
{
    checkLanding();
}

void CTeam::ready()
{
    m_manual = false;
    MgPlayerPauseOff(m_mp, &m_startPos);
    MgPlayerAttrSet(m_mp, 1);
    m_dropping = true;
    setProc(&CPlayerBase::main);
}

void CTeam::go()
{
    MgPlayerAttrReset(m_mp, 1);
    setProc(&CTeam::procControl);
}

/* falls off (below the top block - 50, or past x 500) -> eliminated, integrated by hand in procFall; the land-wait
 * keeps MgPlayer attr 1 for 18 frames after touching down; vibrate when the stage starts dropping under a grounded
 * member. retail: a dead "reached 0" local on the countdown (as CPlayerBase::Update) */
void CTeam::procControl()
{
    if (m_padNo < 0) {
        comUpdate();
    }
    Vec p;
    MgActorPosGet(m_mp->actor, &p);
    if (p.y < CSingleton<CStage>::GetInstance()->GetTopY() - 50.0 || p.x > 500.0f) {
        eliminate();
        m_manual = true;
        MgPlayerPauseOn(m_mp);
        setMotion(0, true);
        m_vel.x = p.x;
        m_vel.y = p.y;
        m_vel.z = p.z;
        PSVECSubtract(&m_vel, &m_pos, &m_vel);
        vibrate(2);
        setProc(&CTeam::procFall);
    }
    m_pos.x = p.x;
    m_pos.y = p.y;
    m_pos.z = p.z;
    bool done = false;
    if (m_landWait > 0 && --m_landWait == 0) {
        done = true;
    }
    if (isOnGround()) {
        if (m_landWait <= 0) {
            MgPlayerAttrReset(m_mp, 1);
        } else {
            MgPlayerAttrSet(m_mp, 1);
        }
    } else {
        MgPlayerAttrReset(m_mp, 1);
        int wait = 18;
        m_landWait = wait;
    }
    bool settled = CSingleton<CStage>::GetInstance()->IsDropDone();
    if (isOnGround() && m_wasOnStage && !settled) {
        vibrate(0);
    }
    m_wasOnStage = settled;
}

/* off the tower: past radius 500 the horizontal velocity is turned outward; inside the sun sphere (0, -2400, 0)
 * r 2400 -> burn */
void CTeam::procFall()
{
    Vec d = { 0.0f, 0.0f, 0.0f };
    d.x = m_pos.x;
    d.z = m_pos.z;
    float r = PSVECMag(&d);
    if (r < 500.0f) {
        m_vel.x = (m_pos.x < 0.0f ? -1 : 1) * fabs(m_vel.x);
        m_vel.z = (m_pos.z < 0.0f ? -1 : 1) * fabs(m_vel.z);
    }
    Vec c = { 0.0f, -2400.0f, 0.0f };
    Vec e;
    PSVECSubtract(&c, &m_pos, &e);
    float dist = PSVECMag(&e);
    if (dist < 2400.0f) {
        burn();
    }
}

/* CTeam's file-local helpers (F5 region; distinct names so the merge with F6's SetVec / Min / Lerp does not collide).
 * TeamSetVec = m513 / m532 SetVec: DOUBLE components (retail frsp; stfs), or a component-wise copy (lfs / stfs).
 * Normalize / Scale return / take the vector in a register (burn 130D0: the result reaches Scale through two
 * copies). All code-identical to what retail inlines; none is emitted out of line. */
static inline Vec& TeamSetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

static inline Vec& TeamSetVec(Vec* d, const Vec& s)
{
    d->x = s.x;
    d->y = s.y;
    d->z = s.z;
    return *d;
}

static inline Vec* Normalize(Vec* v)
{
    PSVECNormalize(v, v);
    return v;
}

static inline void Scale(Vec* v, float s)
{
    PSVECScale(v, v, s);
}

/* the length reaches the caller through the inline's return temporary (fmr; fmr: findDanger / moveTo) */
static inline float Mag(Vec* v)
{
    return PSVECMag(v);
}

static inline float MinF(float a, float b)
{
    return a < b ? a : b;
}

/* touched the fire / the sun: eliminated, launched outward (10 horizontal, 40 / 3 up) facing away from the centre */
void CTeam::burn()
{
    eliminate();
    if (!MgPlayerAttrCheck(m_mp, 0x400)) {
        TeamSetVec(&m_pos, m_mp->actor->pos);
    }
    TeamSetVec(&m_vel, m_pos.x, 0.0f, m_pos.z);
    Scale(Normalize(&m_vel), 10.0f);
    m_vel.y = 40.0f / 3.0f;
    m_rotY = 180.0 * (atan2f(m_pos.x, m_pos.z) / M_PI);
    m_rotX = 0.0f;
    m_manual = true;
    MgPlayerPauseOn(m_mp);
    setMotion(1, true);
    vibrate(4);
    HuAudFXPlayPan(0x746, GetPan(&m_pos));
    setProc(&CTeam::procNone);
}

void CTeam::procNone() {}

/* the winners turn to face the camera (rotY -> 0) once grounded (or out) */
void CTeam::procFaceFront()
{
    if (isOnGround() || m_out) {
        float& rot = m_mp->actor->rotY;
        CAngle a(0.0f, 360.0f, rot);
        rot = a.approach(0.0f, 0.1);
        if (fabs(rot) < 0.1) {
            rot = 0.0f;
            setProc(&CPlayerBase::main);
        }
    }
}

void CTeam::result()
{
    if (!m_out && s_aliveNum > 0) {
        setMotion(2, false);
        setProc(&CPlayerBase::main);
    }
}

void CTeam::eliminate()
{
    if (!m_out) {
        MgActorColAttrSet(m_mp->actor, 4);
        MgPlayerAttrSet(m_mp, 1);
        m_out = true;
        s_aliveNum--;
    }
}

void CTeam::judge()
{
    if (s_aliveNum > 0) {
        CMinigameCore::AddWinner(m_idx);
        MgActorColAttrSet(m_mp->actor, 4);
        MgPlayerAttrSet(m_mp, 1);
        if (!m_out) {
            MgPlayerComStkOn(m_mp);
            setProc(&CTeam::procFaceFront);
        }
    }
}

void CTeam::respawn()
{
    m_dropping = true;
    CharModelAttrReset(m_charNo, HU3D_ATTR_DISPOFF);
    CharModelFxFlagSet(m_charNo, TRUE);
    m_manual = false;
    MgPlayerPauseOff(m_mp, &m_startPos);
    m_mp->actor->rotY = 0.0f;
}

/* MgPlayer-driven: only the voice pan; by hand (m_manual, eliminated): integrate with gravity and place the model */
void CTeam::draw()
{
    if (!m_manual) {
        Vec p;
        TeamSetVec(&p, m_mp->actor->pos);
        CharModelVoicePanSet(m_charNo, GetPan(&p));
    } else {
        HU3DMODELID id = m_mp->actor->mdlId;
        PSVECAdd(&m_vel, &m_pos, &m_pos);
        m_vel.y -= 0.27240694f;
        Hu3DModelPosSetV((int)id, &m_pos);
        CharModelVoicePanSet(m_charNo, GetPan(&m_pos));
        Hu3DModelRotSet((int)id, m_rotX, m_rotY, 0.0f);
    }
}

bool CTeam::isOnGround()
{
    u32& attr = m_mp->actor->colGroundAttr;
    return (bool)((attr & 0x407F) != 0);
}

/* STUB detail (fn_1_13A48, 93 insns): Find(a->paramB) inlined; type 0 = a bubble push, 1 = fire */
int CTeam::NarrowHook(COL_NARROW_PARAM* a, COL_NARROW_PARAM* b)
{
    CTeam* t = static_cast<CTeam*>(Find(a->paramB));
    if (!t) {
        return 0;
    }
    if (b->type == 0) {
        t->m_pushed = true;
        t->m_pushPos = b->point;
        return 0;
    }
    if (b->type != 1) {
        return 0;
    }
    t->burn();
    CharFXPlayPan(t->m_charNo, 0x1F9, GetPan(&t->m_pos));
    return 0;
}

/* line padding (CTeam motions): the assert below must stay on retail's player.cpp:1060 */
























































void CTeam::createMotions()
{
    m_motion_id.clear();
    addMotion(0x8C002B);
    addMotion(0x8C0015);
    addMotion(0x8C0006);
    assert(m_motion_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
}

void CTeam::checkLanding()
{
    if (m_dropping) {
        Vec p;
        MgActorPosGet(m_mp->actor, &p);
        if (p.y <= 1.0 + CSingleton<CStage>::GetInstance()->GetTopY()) {
            vibrate(0);
            m_dropping = false;
        }
    }
}

void CTeam::comUpdate()
{
    (this->*m_comProc)();
    m_pushed = false;
    m_com.apply(m_mp);
}

/* 60 frames a second (the COM's hold time): the product is a float local, the frames an int return */
static inline int SecToFrame(float sec)
{
    float f = 60.0f * sec;
    return f;
}

/* (1 - t) a + t b (F6's Lerp, distinct name for the merge): the bubble average pulled 40% toward the last push */
template <class T> static inline T TeamLerp(T a, T b, double t)
{
    return (1.0 - t) * a + t * b;
}

void CTeam::procCom()
{
    bool jump = false;
    CSolo* solo = static_cast<CSolo*>(FindSolo());
    if (solo) {
        int action = solo->getAction();
        switch (action) {
        case CSolo::ACTION_STRIKE:
            jump = CRandom::frandom(5 - m_dif) / 5.0 < 0.048;
            break;
        case CSolo::ACTION_RAISE:
            jump = CRandom::frandom(m_dif + 1) / 4.0 < 0.08;
            break;
        }
    }
    bool dropDone = CSingleton<CStage>::GetInstance()->IsDropDone();
    if (isOnGround()) {
        if (jump) {
            m_com.press(true);
            m_comHold = SecToFrame(CRandom::frandom(0.2f, 1.0f));
        }
    } else {
        /* the easiest COM (dif 0) hops at random while airborne, one frame in 60; retail copies the flag once more
         * before the call (li r21; mr r17,r21) */
        bool hop = false;
        if (m_dif == 0 && CRandom::randomMantissa() < 1.0 / 60) {
            hop = true;
        }
        bool edge = hop;
        if (!dropDone || m_comHold > 0) {
            m_com.press(edge);
        }
    }
    bool done = false;
    if (m_comHold > 0 && --m_comHold == 0) {
        done = true;
    }
    Vec pos;
    MgActorPosGet(m_mp->actor, &pos);
    Vec danger;
    Vec dir = { 0.0f, 0.0f, 0.0f };
    dir.x = pos.x;
    dir.z = pos.z;
    bool found = findDanger(&danger, 150.0f);
    if (found) {
        if (m_pushed) {
            danger.x = TeamLerp(danger.x, m_pushPos.x, 0.4);
            danger.y = TeamLerp(danger.y, m_pushPos.y, 0.4);
            danger.z = TeamLerp(danger.z, m_pushPos.z, 0.4);
        }
        TeamSetVec(&dir, pos.x - danger.x, 0.0f, pos.z - danger.z);
        Scale(Normalize(&dir), 400.0f);
        dir.x += pos.x;
        dir.z += pos.z;
    }
    float range = found ? 400.0 : 250.0;
    float len = Mag(&dir);
    if (len > range || found) {
        PSVECScale(&dir, &dir, range / len);
        moveTo(&dir, (1.0 / 60) * (100.0 * (2.0 + 0.3 * m_dif)));
    }
}

bool CTeam::findDanger(Vec* out, float radius)
{
    std::vector<int>* h = CSingleton<CBubbleMan>::GetInstance()->GetHandles();
    std::vector<int>::iterator it = h->begin();
    std::vector<int>::iterator end = h->end();
    bool found = false;
    int n = 0;
    Vec pos;
    MgActorPosGet(m_mp->actor, &pos);
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;
    for (; it != end; ++it) {
        CBubble* b = static_cast<CBubble*>(CSunFireObj::GetHandlePtr(*it));
        Vec bp;
        b->GetPos(&bp);
        Vec d;
        TeamSetVec(&d, bp.x - pos.x, 0.0f, bp.z - pos.z);
        float dist = Mag(&d);
        if (dist <= radius) {
            radius = dist;
            PSVECAdd(&bp, out, out);
            n++;
            found = true;
        }
    }
    if (n > 0) {
        PSVECScale(out, out, 1.0 / n);
    }
    return found;
}

/* steer the COM stick toward target (x/z) at most `speed` (<= 10) a frame; true once within one step */
bool CTeam::moveTo(Vec* target, float speed)
{
    speed = MinF(speed, 10.0f);
    Vec pos;
    MgActorPosGet(m_mp->actor, &pos);
    Vec d;
    TeamSetVec(&d, target->x - pos.x, 0.0f, target->z - pos.z);
    float len = Mag(&d);
    if (len < speed) {
        return true;
    }
    PSVECScale(&d, &d, speed / len);
    m_com.steer(&d);
    return false;
}

/* ---- CComPad, CAngle, templates, __sinit (F4: .text 0x14868..0x15728) ---- */

void CComPad::clear()
{
    m_x *= 0.9;
    m_y *= 0.9;
    m_btnDown = 0;
    m_btn = 0;
}

void CComPad::press(bool edge)
{
    m_btn |= PAD_BUTTON_A;
    if (edge) {
        m_btnDown |= PAD_BUTTON_A;
    }
}

/* turn the yaw toward d's heading (xz) and set the stick: full length when facing it, zero when opposite */
bool CComPad::steer(Vec* d)
{
    Vec v = { 0.0f, 0.0f, 0.0f };
    v.x = d->x;
    v.z = d->z;
    CAngle a(-3.1415927f, 3.1415927f, m_yaw);
    float t = atan2f(v.x, v.z);
    float df = a.diff(t) / 2.0f;
    double ad = fabs(df);
    float f = 1.0 - ad / M_PI;
    float mag = PSVECMag(&v);
    float m = f * mag;
    m_yaw = a.approach(t, 0.05);
    m_x = m * sin(a.get());
    m_y = -m * cos(a.get());
    return 0.0f == m_x && 0.0f == m_y;
}

static inline float Clamp1(float v)
{
    if (v < -1.0f) {
        return -1.0f;
    }
    if (v > 1.0f) {
        return 1.0f;
    }
    return v;
}

void CComPad::apply(MGPLAYER* mp)
{
    int x = 56.0f * Clamp1(m_x / 10.0f);
    int y = 56.0f * Clamp1(m_y / 10.0f);
    MgPlayerPadSet(mp, x, y, m_btnDown, m_btn | m_btnDown);
    clear();
}

/* Min / Max: hoisted above CSolo (F6: CSolo::procRecover / procWinFloat inline Max) */
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

float CAngle::approach(float v, double rate)
{
    float d = diff(m_value, v);
    return m_value = wrap((float)(m_value + rate * d));
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

} // namespace m522
