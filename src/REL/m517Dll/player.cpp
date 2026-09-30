/* player.cpp -- m517::CPlayerCarrier and m517::CPlayer (player_kuribo.md §1-§2; names ours). Retail order (.text
 * 15500..1A4D4): CPlayerCarrier(), [~auto_ptr<CModel> 15614, auto_ptr<CModel>::__defctor 1566C,
 * ~CSingleton<CPlayerCarrier> 15698 (weak)], ~CPlayerCarrier, getHookPos (unreferenced; inlined in procIntro),
 * HitCounter::operator() (unreferenced), SetStartPosDefault (unreferenced), Finish, SetStartPos (inlined in the ctor),
 * CreateRide / CreateInput (unreferenced; inlined in the ctor), [auto_ptr<CModel>(CModel*) 15DC0], CPlayer(int),
 * [the member auto_ptr dtors 166A0..167CC, ~TLinkItem<CPlayer> 16848 (weak)], addMotion, update, setMotion, procNone,
 * procIntro, procStart, AngleLerp (unreferenced; inlined), procPlay, procOut, procStay, Hit, Stun, SetResult,
 * GetOutPos, procReturnSolo, procReturnTeam, procReturn, VecYaw (unreferenced), MoveSolo, Fall, MoveTeam, ClampArena,
 * PushPair, [ForEachSpherePair<HitCounter> 1A2B8, vector<s16>::reserve 1A378 (weak)], __sinit (the minigame.h triple).
 * .data 6D0..858: the player.h PTMF triple, s_model, the singleton strings, the hook names and s_hookName, procReturn,
 * the a_set strings, procNone, the motion-count assert (player.cpp:227), procPlay, procStay, procOut, procStay x2, the
 * MSL vector strings. .rodata 588..6A8 (util.h's zero block first). .bss A48..A58: the minigame.h triple. */
#include "REL/m517Dll/config.h"
#include "REL/m517Dll/player.h"
#include "REL/m517Dll/util.h"
#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in player.o's .bss / __sinit; AddWinner */
#include "REL/m517Dll/stage.h"
#include "REL/m517Dll/dustcloud.h"
#include "REL/m517Dll/audio.h"

namespace m517 {

/* data_6F4: the carriers' models (a non-const table: .data) */
static u32 s_model[CPlayerCarrier::NUM] = { 0x4B000D, 0x4B000F, 0x4B0010, 0x4B000E };

/* PSVECMag's result reaches the caller through a temporary (m531) */
static inline float VecMag(Vec* v)
{
    return PSVECMag(v);
}

/* the practice flag guards the coin write (m503 / m537 shape) */
static inline s16 GetCoin(int no)
{
    return GwPlayer[no].mgCoinBonus;
}
static inline void SetCoin(int no, s16 coin)
{
    if (!_CheckFlag(FLAG_MG_PRACTICE)) {
        GwPlayer[no].mgCoinBonus = coin;
    }
}

CPlayerCarrier::CPlayerCarrier()
{
    for (int i = 0; i < NUM; i++) {
        m_model[i].reset(new CModel(s_model[i]));
    }
}

CPlayerCarrier::~CPlayerCarrier() {}

/* data_73C: the carriers' hook objects by team index (a non-const table: .data) */
static char* s_hookName[CPlayerCarrier::NUM] = { (char*)"1p", (char*)"3p", (char*)"4p", (char*)"2p" };

bool CPlayerCarrier::getHookPos(int i, Vec* pos, Vec* rot)
{
    HU3DMODELID id = m_model[i]->id();
    HSFOBJECT* obj = Hu3DModelObjPtrGet(id, s_hookName[i]);
    if (obj) {
        *pos = *(Vec*)&obj->mesh.curr.pos;
        *rot = *(Vec*)&obj->mesh.curr.rot;
        rot->y += 90.0f;
    }
    return !Hu3DMotionEndCheck(id);
}

void HitCounter::operator()(CSphere* a, CSphere* b)
{
    if (HitCheckSphere(a, b)) {
        m_count++;
    }
}

/* f(&a->m_sphere, &b->m_sphere) for every unordered pair of the list (the functor by reference) */
template <class F>
void ForEachSpherePair(TLinkList<CPlayer>* list, F& f)
{
    CPlayer* a = list->begin();
    CLinkNode* e = list->end();
    CLinkNode* l = e->prev();
    for (; a != l; a = a->next()) {
        for (CPlayer* b = a->next(); b != e; b = b->next()) {
            f(a->GetSphere(), b->GetSphere());
        }
    }
}

void CPlayer::SetStartPosDefault()
{
    SetStartPos(250.0f, -300.0f);
}

void CPlayer::Finish()
{
    m_immune = 1;
    m_finished = true;
    if (!m_out) {
        if (m_isSolo) {
            m_ball->Stop();
            m_home.x = 0.0f;
        } else {
            m_home.x = 300.0f * (m_teamIdx - 2);
        }
        m_home.z = m_isSolo ? -300.0f : 100.0f;
        m_home.y = 0.0f;
        setProc(&CPlayer::procReturn);
    }
}

/* the solo stands on its ball; a team player takes the first of x = -300 / 0 / 300 free of every other player */
void CPlayer::SetStartPos(float teamZ, float soloZ)
{
    m_sphere.pos.y = 0.0f;
    m_sphere.pos.z = m_isSolo ? soloZ : teamZ;
    if (m_isSolo) {
        m_sphere.pos.x = 0.0f;
        m_ball->SetPos(&m_sphere.pos);
        m_sphere.pos.y += 195.0f;
    } else {
        for (int i = -1; i <= 1; i++) {
            m_sphere.pos.x = 100.0f * (3.0f * i);
            HitCounter counter;
            counter.m_count = 0;
            ForEachSpherePair(ASet<CPlayer>::instance(), counter);
            if (counter.count() == 0) {
                break;
            }
        }
    }
}

CBall* CPlayer::CreateRide(int idx)
{
    if (GwPlayerConf[idx].grp != 0) {
        return 0;
    }
    return new CBall(idx);
}

CInput* CPlayer::CreateInput(int idx)
{
    if (GwPlayerConf[idx].grp == 0) {
        if (GwPlayerConf[idx].type) {
            return new CInputComSolo(GwPlayerConf[idx].dif);
        }
        return new CInputPad(idx);
    }
    if (GwPlayerConf[idx].type) {
        return new CInputCom(idx, GwPlayerConf[idx].dif);
    }
    return new CInputPad(idx);
}

/* line padding (CPlayer ctor) */
































CPlayer::CPlayer(int idx)
    : m_immune(0), m_out(false), m_idx(idx), m_charNo(GwPlayerConf[idx].charNo), m_motion(-1),
      m_isSolo(GwPlayerConf[idx].grp == 0), m_introDust(false), m_finished(false), m_homeState(0), m_mot_id(),
      m_model(new CModel(GwPlayerConf[idx].charNo, 2)), m_input(CreateInput(idx)), m_ball(CreateRide(idx)), m_paper(0),
      m_shadow(0)
{
    int team = 0;
    if (GwPlayerConf[idx].grp == 0) {
        team = 0;
    } else {
        for (int i = 0; i <= idx; i++) {
            if (GwPlayerConf[i].grp != 0) {
                team++;
            }
        }
    }
    m_teamIdx = team;
    insertBack(ASet<CPlayer>::instance());
    m_sphere.r = 60.000004f;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0000);
    addMotion(0x8C0001);
    addMotion(0x8C0002);
    addMotion(0x8C0003);
    addMotion(0x8C0004);
    addMotion(0x8C003A);
    addMotion(0x8C0013);
    addMotion(0x8C0014);
    addMotion(0x8C0051);
    addMotion(0x87002D);
    addMotion(0x870097);
    addMotion(0x870098);
    addMotion(0x8C0030);
    if (!m_isSolo) {
        addMotion(0x8C0031);
    } else {
        addMotion(0x8C002E);
    }
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model->id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    CharEffectLayerSet(5);
    if (!m_isSolo) {
        CharModelStepFxSet(m_charNo, 2);
        setMotion(0, false, 8.0f);
    } else {
        CharModelFxFlagSet(m_charNo, 0);
        setMotion(9, false, 8.0f);
        m_shadow.reset(new CShadow2);
    }
    SetStartPosDefault();
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_outPos.x = 0.0f;
    m_outPos.y = 0.0f;
    m_outPos.z = 0.0f;
    m_home.x = 0.0f;
    m_home.y = 0.0f;
    m_home.z = 0.0f;
    m_move.x = 0.0f;
    m_move.y = 0.0f;
    m_move.z = 0.0f;
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_scale.z = 1.0f;
    m_outState = 0;
    m_introState = 0;
    m_introTime = 0.0f;
    m_stun = 45;
    CharMotionVoiceOnSet(m_charNo, 0x13, 0);
    setProc(&CPlayer::procNone);
}

/* the blob shadow follows the solo (the owner writes CShadow2::m_pos) */
static inline void SetShadowPos(CShadow2* shadow, const Vec& pos)
{
    shadow->m_pos.x = pos.x;
    shadow->m_pos.y = pos.y;
    shadow->m_pos.z = pos.z;
}

void CPlayer::addMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

/* the solo writes the ball position into the stage (y 0) and carries its shadow; every player sets its voice pan */
void CPlayer::update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_model->setPos(&m_sphere.pos);
    m_model->setRot(&m_rot);
    if (m_isSolo) {
        CStage* stage = CSingleton<CStage>::GetInstance();
        stage->m_impact = m_sphere.pos;
        stage->m_impact.y = 0.0f;
        Vec pos = m_sphere.pos;
        pos.y += 5.0f;
        SetShadowPos(m_shadow.get(), pos);
    }
    SetVoicePan(m_charNo, m_sphere.pos);
}

/* no motion change until the stun motion (5) has ended */
void CPlayer::setMotion(int no, bool once, float shift)
{
    if (m_motion == 5 && !CharMotionEndCheck(m_charNo)) {
        return;
    }
    HU3DMODELID id = m_model->id();
    s16 mot = m_mot_id[no];
    if (m_motion != no) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, mot, 0.0f, shift, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

void CPlayer::procNone() {}

/* one extra inline level around the landing copy: retail's GPR numbering in procIntro (r28 for the GetPos pointer,
 * r30 / r29 for the hook pointers) comes out only with it (guess: the retail wrapper's name and form are unknown) */
static inline void SetPosTo(CPlayer* p, const Vec* v)
{
    *p->GetPos() = *v;
}

/* state 0: ride the carrier hook for 3 s (the solo keeps its ball under it), then jump off; 1: ease to the start
 * spot for 1.8 s (a team player's dust puff after 0.55 s). The case falls through (retail). */
void CPlayer::procIntro()
{
    switch (m_introState) {
    case 0: {
        Vec prev = m_sphere.pos;
        CPlayerCarrier* carrier = CSingleton<CPlayerCarrier>::GetInstance();
        carrier->getHookPos(m_teamIdx, &m_sphere.pos, &m_rot);
        if (m_isSolo) {
            float r = m_ball->GetRadius();
            m_sphere.pos.y -= r;
            m_ball->SetPos(&m_sphere.pos);
            m_sphere.pos.y += 195.0f;
            m_ball->Roll(&prev, &m_sphere.pos);
            setMotion(10, false, 8.0f);
        } else {
            setMotion(2, false, 8.0f);
        }
        m_introTime += 1.0 / 60.0;
        if (m_introTime < 3.0f) {
            break;
        }
        if (m_isSolo) {
            m_jumpTo.x = 0.0f;
            m_jumpTo.y = 0.0f;
        } else {
            m_jumpTo.x = 250.0f * (m_teamIdx - 2);
            m_jumpTo.y = 0.0f;
            CharEffectShoeHitCreate(1, &m_sphere.pos, &m_rot);
            setMotion(6, true, 8.0f);
        }
        m_jumpTo.z = m_isSolo ? -200.0f : 250.0f;
        m_introTime = 0.0f;
        CharFXPlay(m_charNo, 0x1FD);
        m_introState++;
    }
    case 1: {
        float k = 18.0f;
        if (!m_isSolo) {
            m_sphere.pos.x += (m_jumpTo.x - m_sphere.pos.x) / k;
            m_sphere.pos.y += (m_jumpTo.y - m_sphere.pos.y) / k;
            m_sphere.pos.z += (m_jumpTo.z - m_sphere.pos.z) / k;
            if (!m_introDust && m_introTime > 0.55f) {
                GXColor color = { 0xFF, 0xE0, 0x20, 0x00 }; /* retail: never used */
                new CDustPuff(&m_sphere.pos);
                m_introDust = true;
            }
        } else {
            Vec prev = m_sphere.pos;
            Vec ball = m_sphere.pos;
            m_sphere.pos.x += -m_sphere.pos.x / k;
            m_sphere.pos.z += (m_jumpTo.z - m_sphere.pos.z) / k;
            ball.y = 0.0f;
            m_ball->SetPos(&ball);
            m_ball->Roll(&prev, &m_sphere.pos);
            Vec d;
            PSVECSubtract(&ball, &m_jumpTo, &d);
            if (VecMag(&d) < 10.0f) { /* the inline's return temp: retail's FPR order (f26) */
                setMotion(9, true, 16.0f);
            } else {
                setMotion(11, false, 8.0f);
            }
        }
        m_introTime += 1.0 / 60.0;
        if (m_introTime < 1.8f) {
            break;
        }
        if (!m_isSolo) {
            SetPosTo(this, &m_jumpTo);
            setMotion(7, true, 16.0f);
        } else {
            setMotion(9, false, 8.0f);
        }
        m_rot.y = 0.0f;
        m_introState++;
    }
    }
}

void CPlayer::procStart()
{
    if (!m_isSolo) {
        setMotion(0, false, 16.0f);
    } else {
        setMotion(9, false, 8.0f);
    }
    setProc(&CPlayer::procPlay);
}

float AngleLerp(float from, float to, float rate)
{
    float d = fmod(to - from, 360.0);

    if (d < 0.0f) {
        d += 360.0f;
    }
    if (d > 180.0f) {
        d -= 360.0f;
    }
    float r = fmod(from + rate * d, 360.0);
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* ---- player region F2 (procPlay 178D0 .. __sinit 1A4A0); above: region F1 (15500 .. AngleLerp 177CC) ---- */

/* 1 while returning home (an inline result: retail's low register) */
static inline int GetImmune(const CPlayer* p)
{
    return p->m_immune;
}

/* by value: the argument is copied to a caller temporary */
static inline float VecMagV(Vec v)
{
    return PSVECMag(&v);
}

/* the stick on the xz plane, magnitude in y (by value to the movers) */
void CPlayer::procPlay()
{
    CInput* input = m_input.get();
    input->update();
    Vec stick;
    stick.x = input->m_data.x;
    stick.z = input->m_data.y;
    stick.y = input->m_data.mag;
    if (m_isSolo) {
        MoveSolo(stick);
    } else {
        Vec prev = m_sphere.pos;
        MoveTeam(stick);
        PSVECSubtract(&m_sphere.pos, &prev, &m_move);
    }
}

/* caught: rumble 0.2 s, squash, become a paper cut-out that flies to the gallery, drop back in there and idle.
 * Cases fall through (retail). Retail: state 1 squashes in one frame (its `< 0.1` test breaks only when already
 * flat). */
void CPlayer::procOut()
{
    float ground = 250.0f;
    switch (m_outState) {
    case 0:
        omVibrate(m_idx, 12, 12, 0);
        m_outTime += 1.0 / 60.0;
        if (m_outTime < 0.2f) {
            break;
        }
        m_outTime = 0.0f;
        m_outState++;
    case 1: {
        m_scale.y += -m_scale.y / 12.0f;
        float y = m_scale.y;
        if ((y < 0.0f ? -y : y) < 0.1f) {
            break;
        }
        m_scale.y = 0.0f;
        m_outPos.y = 800.0f;
        m_paper.reset(new CPaper(&m_sphere.pos, &m_outPos, &m_rot, m_idx));
        *GetPos() = m_outPos;
        m_model->setAttr(HU3D_ATTR_DISPOFF);
        m_outState++;
    }
    case 2: {
        if (m_paper->IsDone() != true) {
            break;
        }
        m_paper.reset(0);
        m_model->resetAttr(HU3D_ATTR_DISPOFF);
        m_scale.y = 1.0f;
        m_rot.y = 0.0f;
        CharModelAttrReset(m_charNo, HU3D_MOTATTR_PAUSE);
        setMotion(3, true, 8.0f);
        GXColor color = { 0xFF, 0xFF, 0xFF, 0x00 };
        new CDustCloud(&m_sphere.pos, color, 6);
        m_outState++;
    }
    case 3:
        Fall();
        if (m_sphere.pos.y > ground) {
            break;
        }
        setMotion(4, true, 8.0f);
        m_outState++;
    case 4:
        if (!CharMotionEndCheck(m_charNo)) {
            break;
        }
        setMotion(8, false, 8.0f);
        m_sphere.pos.y = ground;
        m_vel.y = 0.0f;
        setProc(&CPlayer::procStay);
        break;
    }
    m_model->setScale(&m_scale);
}

void CPlayer::procStay()
{
    m_immune = 0;
}

/* the ball rammed this team player: after time-up (m_finished) a hit re-sends it home (Finish); else a ram at
 * speed >= 6.6667 catches it */
void CPlayer::Hit(CBall* ball)
{
    if (m_out) {
        return;
    }
    m_sphere.pos.y = 0.0f;
    if (GetImmune(this) == 1) {
        return;
    }
    if (m_finished == true) {
        Finish();
        return;
    }
    if (VecMagV(ball->m_delta) < 20.0 / 3.0) {
        return;
    }
    setMotion(6, true, 8.0f);
    m_outPos = GetOutPos();
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_outTime = 0.0f;
    m_out = true;
    Vec pos = m_sphere.pos;
    pos.y += 100.0f;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0x00 };
    new CDustCloud(&pos, color, 6);
    HU3DMODELID id = m_model->id();
    Hu3DModelShadowDispOff(id);
    CharFXPlay(m_charNo, 0x202);
    setProc(&CPlayer::procOut);
}

/* a Monty Mole stunned this team player: 45 frames without control (MoveTeam) */
void CPlayer::Stun(CChoro* choro)
{
    if (m_motion == 5) {
        return;
    }
    setMotion(5, true, 8.0f);
    CharEffectShoeHitCreate(1, &m_sphere.pos, &m_rot);
    CharModelCryCreate(m_charNo, 30.0f, 0.8f);
    CharFXPlay(m_charNo, 0x1FD);
    m_stun = 0;
}

void CPlayer::SetResult(bool win)
{
    if (win) {
        setMotion(12, true, 8.0f);
        SetCoin(m_idx, GetCoin(m_idx) + 10);
        CMinigameCore::AddWinner(m_idx);
        if (m_isSolo) {
            CharFXPlay(m_charNo, 0x1FA);
        }
    } else {
        setMotion(13, true, 8.0f);
    }
}

Vec CPlayer::GetOutPos() const
{
    int slot = m_teamIdx - 2;
    Vec pos;
    pos.x = 150.0f * slot;
    pos.y = 0.0f;
    pos.z = -800.0f;
    return pos;
}

/* time-up, solo: ride home (slowing within 50, snap within 20), then turn to rot.y 0 */
void CPlayer::procReturnSolo()
{
    m_sphere.pos.y = 0.0f;
    Vec d;
    Vec prev = m_sphere.pos;
    PSVECSubtract(&m_home, &prev, &d);
    float dist = VecMag(&d);
    float speed = 0.0f;
    int mot = 10;
    if (m_homeState == 0) {
        if (dist < 50.0f) {
            float f = 1.0f - (50.0f - dist) / 50.0f;
            speed = 5.0 * f;
            mot = 11;
            m_rot.y = AngleLerp(m_rot.y, 180.0 * (atan2(d.x, d.z) / 3.141592653589793), 0.2f * f);
        } else {
            speed = 10.0f;
            m_rot.y = AngleLerp(m_rot.y, 180.0 * (atan2(d.x, d.z) / 3.141592653589793), 0.2f);
        }
        if (dist < 20.0f) {
            *GetPos() = m_home;
            m_homeState = 1;
        } else {
            float rad = 3.141592653589793 * m_rot.y / 180.0;
            m_sphere.pos.x += speed * sin(rad);
            m_sphere.pos.z += speed * cos(rad);
            setMotion(mot, false, 8.0f);
        }
    } else {
        mot = 11;
        m_rot.y = AngleLerp(m_rot.y, 0.0f, 0.1f);
        if (m_rot.y < 0.2f || m_rot.y > 359.8f) {
            m_rot.y = 0.0f;
            setMotion(9, false, 8.0f);
            setProc(&CPlayer::procStay);
        }
    }
    float r = m_ball->GetRadius(); /* retail: unused */
    m_ball->SetPos(&m_sphere.pos);
    m_sphere.pos.y += 195.0f;
    m_ball->Roll(&prev, &m_sphere.pos);
}

/* time-up, team: walk / run home (slowing within 50), snap within 30 and idle */
void CPlayer::procReturnTeam()
{
    Vec d;
    Vec pos = m_sphere.pos;
    pos.y = 0.0f;
    PSVECSubtract(&m_home, &pos, &d);
    float dist = VecMag(&d);
    float speed = 0.0f;
    if (dist < 50.0f) {
        float f = 1.0f - (50.0f - dist) / 50.0f;
        speed = 7.5 * f;
        m_rot.y = AngleLerp(m_rot.y, 180.0 * (atan2(d.x, d.z) / 3.141592653589793), 0.2f * f);
        setMotion(1, false, 8.0f);
    } else {
        speed = 10.0f;
        setMotion(2, false, 8.0f);
        m_rot.y = AngleLerp(m_rot.y, 180.0 * (atan2(d.x, d.z) / 3.141592653589793), 0.2f);
    }
    if (dist < 30.000002f) {
        *GetPos() = m_home;
        m_rot.y = 0.0f;
        setMotion(0, false, 8.0f);
        setProc(&CPlayer::procStay);
    } else {
        float rad = 3.141592653589793 * m_rot.y / 180.0;
        m_sphere.pos.x += speed * sin(rad);
        m_sphere.pos.z += speed * cos(rad);
    }
}

void CPlayer::procReturn()
{
    if (m_isSolo) {
        procReturnSolo();
    } else {
        procReturnTeam();
    }
}

float VecYaw(const Vec* v)
{
    return 180.0 * atan2(v->x, v->z) / 3.141592653589793;
}

/* the solo stands on its ball (+95): face the stick, pick the ride motion from the ball's speed, push the ball */
void CPlayer::MoveSolo(Vec stick)
{
    *GetPos() = *m_ball->GetPos();
    m_sphere.pos.y += 95.0f;
    if (stick.y > 0.2f) {
        m_rot.y = AngleLerp(m_rot.y, VecYaw(&stick), 0.2f);
    }
    float speed = m_ball->GetSpeedRatio();
    if (speed < 0.05f) {
        setMotion(9, false, 8.0f);
    } else {
        float motSpeed = 2.0f * speed;
        if (motSpeed > 1.0f) {
            motSpeed = 1.0f;
        }
        CharMotionSpeedSet(m_charNo, motSpeed);
        if (speed < 0.4f) {
            setMotion(11, false, 8.0f);
        } else {
            setMotion(10, false, 8.0f);
        }
    }
    stick.y = 0.0f;
    m_ball->SetForce(&stick);
}

/* gravity 980.665 / 60^2 per frame, the average of the old and new speed */
void CPlayer::Fall()
{
    Vec vel = m_vel;
    m_vel.y += 0.27240694444444447;
    vel.y = -(0.5f * (vel.y + m_vel.y));
    Vec prev = m_sphere.pos; /* retail: unused */
    PSVECAdd(&vel, &m_sphere.pos, &m_sphere.pos);
}

/* a team player: stunned for 45 frames (no stick), idle / walk / run by the stick, slide 4.1667 a frame while the
 * stun motion runs (rumbling, COMs too), then gravity and the arena wall */
void CPlayer::MoveTeam(Vec stick)
{
    if (m_stun < 45) {
        m_stun++;
        stick.y = 0.0f;
    } else if (stick.y > 0.2f) {
        m_rot.y = AngleLerp(m_rot.y, VecYaw(&stick), 0.2f);
    }
    float speed = 0.0f;
    float mag = stick.y;
    if (mag < 0.1f) {
        setMotion(0, false, 8.0f);
    } else if (mag < 0.6f) {
        setMotion(1, false, 8.0f);
        speed = 7.5 * mag;
    } else {
        setMotion(2, false, 8.0f);
        speed = 10.0f;
    }
    if (m_motion == 5) {
        speed = 4.1666665f;
        omVibrate(m_idx, 12, 12, 0);
    }
    float rad = 0.017453292f * m_rot.y;
    m_vel.x = speed * sin(rad);
    m_vel.z = speed * cos(rad);
    m_sphere.pos.y = 0.0f;
    m_vel.y = 0.0f;
    Fall();
    ClampArena();
}

/* Vec setter with DOUBLE components (retail `frsp; stfs`, m513) */
static inline Vec& SetVec(Vec* v, double x, double y, double z)
{
    v->x = x;
    v->y = y;
    v->z = z;
    return *v;
}

/* keep a team player inside r 550 (retail fetches the stage and never uses it) */
void CPlayer::ClampArena()
{
    CStage* stage = CSingleton<CStage>::GetInstance();
    Vec v;
    SetVec(&v, m_sphere.pos.x, 0.0f, m_sphere.pos.z);
    float d = VecMag(&v);
    float r = 550.0f;
    if (d > r) {
        float over = r - d;
        Vec push;
        PSVECScale(&v, &push, over / d);
        PSVECAdd(&push, &m_sphere.pos, &m_sphere.pos);
        m_vel.x = 0.0f;
        m_vel.y = 0.0f;
        m_vel.z = 0.0f;
    }
}

void CPlayer::PushPair(CPlayer* a, CPlayer* b)
{
    if (!a->m_out && !b->m_out) {
        HitPushSphere(a->GetSphere(), b->GetSphere(), 0.5f, 1.0f);
    }
}

} // namespace m517
