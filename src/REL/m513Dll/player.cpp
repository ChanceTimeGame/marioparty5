#include "REL/m513Dll/player.h"
#include "REL/mgcpp/minigame.h" /* the 120/210/210 triple is in player.o's .bss / __sinit */
#include "REL/m513Dll/heiho.h"
#include "REL/m513Dll/camera.h"
#include "REL/m513Dll/score.h"
#include "REL/m513Dll/audio.h"
extern "C" {
#include "game/frand.h"
}

namespace m513 {


/* Vec setters (m539 / m531): DOUBLE components (retail `frsp; stfs`, ctor 11C1C); component-wise copy (lfs/stfs) */
static inline Vec& SetVec(Vec* v, double x, double y, double z) { v->x = x; v->y = y; v->z = z; return *v; }
static inline Vec& SetVec(Vec* d, const Vec& s) { d->x = s.x; d->y = s.y; d->z = s.z; return *d; }
static inline void SetMgScore(int idx, int score) { GwPlayer[idx].mgScore = score; } /* the decathlon score */

CInput* CPlayer::CreateInput(int idx)
{
    if (GwPlayerConf[idx].type) {
        return new CInputCom(idx, GwPlayerConf[idx].dif);
    }
    return new CInputPad(idx);
}

/* line padding: the assert below is retail's player.cpp:67 */










CPlayer::CPlayer(int idx, bool deca)
    : m_turning(1), m_charNo(GwPlayerConf[idx].charNo), m_motion(-1), m_idx(idx), m_resultState(0),
      m_resultTime(0.0f), m_time(0), m_pumpTime(0.0f), m_finished(false), m_deca(deca), m_effIdx(0), m_mot_id(),
      m_model(new CModel(GwPlayerConf[idx].charNo, 3)), m_input(CreateInput(idx)), m_leaf(0)
{
    insertBack(ASet<CPlayer>::instance());
    m_unk14 = 60.000004f;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    addMotion(0x8C0000);
    addMotion(0x8C0001);
    addMotion(0x8C0002);
    addMotion(0x8C0074);
    addMotion(0x8C0006);
    addMotion(0x8C0007);
    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    HU3DMODELID id = m_model->id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    Hu3DModelLayerSet(id, 3);
    Hu3DModelCameraSet(id, 1);
    CharEffectLayerSet(5);
    setMotion(0, false, false, 8.0f);
    SetVec(&m_pos, 2.0f * idx * 100.0f - 300.0f, 0.0f, 250.0f);
    SetVec(&m_rot, 0.0f, 180.0f, 0.0f);
    /* each player's tree (local copies of .rodata 498 / 4C8) */
    Vec leafPos[4] = { { -300.0f, 0.0f, -250.0f }, { -100.0f, 0.0f, -250.0f },
                       { 100.0f, 0.0f, -250.0f }, { 300.0f, 0.0f, -250.0f } };
    Vec leafRot = { 0.0f, 180.0f, 0.0f };
    m_leaf.reset(new CLeaf(idx, &leafPos[idx], &leafRot));
    for (int i = 0; i < EFF_NUM; i++) {
        m_eff[i].reset(new CPowerEff);
    }
    setProc(&CPlayer::procIdle);
}

void CPlayer::addMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

void CPlayer::update()
{
    if (m_proc) {
        (this->*m_proc)();
    }
    m_model->setPos(&m_pos);
    m_model->setRot(&m_rot);
    SetVoicePan(m_charNo, m_pos);
}

void CPlayer::setMotion(int no, bool force, bool once, float shift)
{
    HU3DMODELID id = m_model->id();
    s16 mot = m_mot_id[no];
    if (m_motion != no || force) {
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(m_charNo, mot, 0.0f, shift, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = no;
    }
}

void CPlayer::procIdle() {}

void CPlayer::procStop() {}

/* setMotion inlined */
void CPlayer::procStart()
{
    setMotion(0, false, false, 8.0f);
    setProc(&CPlayer::procControl);
}

/* lbl_1_rodata_500: the launch height by charNo */
static const float s_height[13] = { 90.0f, 90.0f, 110.0f, 80.0f, 100.0f, 110.0f, 120.000008f, 50.0f, 80.0f,
                                    100.0f, 100.0f, 100.0f, 100.0f };

/* each A press: the pump motion, a cry, Grow(0.5), a power ball from the head to above the tree; full -> finished */
void CPlayer::procControl()
{
    static bool s_practiceOver;
    CInput* input = m_input.get();
    input->update();
    u32 btn = input->m_data.btn;
    Vec stick; /* the stick on the xz plane, magnitude in y: never read (retail) */
    stick.x = input->m_data.x;
    stick.z = input->m_data.y;
    stick.y = input->m_data.mag;
    HU3DMODELID id = m_model->id();
    if (s_practiceOver == true) {
        return;
    }
    if (btn & PAD_BUTTON_A) {
        setMotion(3, false, false, 8.0f);
        CharModelCryCreate(m_charNo, 30.0f, 0.8f);
        m_pumpTime = 0.0f;
        m_leaf->Grow(0.5f);
        float power = m_leaf->GetPower();
        Vec from;
        Vec to;
        SetVec(&from, SetVec(&to, m_pos));
        to.y += 200.0f + 150.0f * power + 50.0f * ((1.0f / 32768) * ((frand() & 0xFFFF) - 32768.0f));
        to.z += -500.0f;
        from.y += s_height[m_charNo];
        m_eff[m_effIdx]->Start(&from, &to, 0.0f);
        m_effIdx++;
        m_effIdx &= EFF_NUM - 1;
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        PlaySe(0x6CC, m_pos);
    }
    if (m_leaf->IsFull()) {
        m_resultTime = 0.0f;
        CScore* score = CSingleton<CScore>::GetInstance();
        m_time = score->getValue(m_idx);
        m_finished = true;
        score->stopPlayer(m_idx);
        if (m_deca == true) {
            SetMgScore(m_idx, m_time);
        }
        setProc(&CPlayer::procFinished);
        if (m_deca == false) {
            score->stopAll();
            s_practiceOver = true;
        }
        cheerHeiho();
        omVibrate(m_idx, 40, 12, 0);
    }
    if (m_motion == 3) {
        if (m_pumpTime > 1.5f) {
            setMotion(0, false, false, 8.0f);
        } else if (m_pumpTime > 0.5f) {
            Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
        }
        m_pumpTime += 1.0 / 60.0;
    }
}

/* the finisher: turn toward the camera (1/12 a frame) with the result-turn motion for 1 s, then idle and
 * procFaceCamera */
void CPlayer::procFinished()
{
    switch (m_resultState) {
    case 0: {
        m_rot.y += (CSingleton<CCameraObj>::GetInstance()->GetYaw() - m_rot.y) / 12.0f;
        setMotion(1, false, false, 8.0f);
        m_resultTime += 1.0 / 60.0;
        if (m_resultTime < 1.0f) {
            break;
        }
        setMotion(0, false, false, 8.0f);
        m_resultState++;
    }
        /* retail: no break -- state 1 runs in the same frame (behaviour kept) */
    case 1:
        setProc(&CPlayer::procFaceCamera);
        m_resultState++;
        break;
    }
}

/* the same body as procFinished (a distinct function: its own procFaceCamera PTMF constant, data_888) */
void CPlayer::procTimeout()
{
    switch (m_resultState) {
    case 0: {
        m_rot.y += (CSingleton<CCameraObj>::GetInstance()->GetYaw() - m_rot.y) / 12.0f;
        setMotion(1, false, false, 8.0f);
        m_resultTime += 1.0 / 60.0;
        if (m_resultTime < 1.0f) {
            break;
        }
        setMotion(0, false, false, 8.0f);
        m_resultState++;
    }
        /* retail: no break -- state 1 runs in the same frame (behaviour kept) */
    case 1:
        setProc(&CPlayer::procFaceCamera);
        m_resultState++;
        break;
    }
}

void CPlayer::procFaceCamera()
{
    CCameraObj* camera = CSingleton<CCameraObj>::GetInstance();
    float yaw = camera->GetYaw();
    m_rot.y += (yaw - m_rot.y) / 60.0f;
    if (m_rot.y - yaw < 1.0f) {
        m_turning = 0;
    }
}

int CPlayer::getMotion() const
{
    return m_motion;
}

void CPlayer::SetResult(bool win)
{
    if (win) {
        setMotion(4, false, true, 8.0f);
        CMinigameCore::AddWinner(m_idx);
    } else {
        setMotion(5, false, true, 8.0f);
    }
}

void CPlayer::timeUp()
{
    if (m_deca == true) {
        SetMgScore(m_idx, 0);
    }
    setProc(&CPlayer::procTimeout);
}

bool CPlayer::IsCom() const
{
    return (bool)(GwPlayerConf[m_idx].type != 0);
}

void CPlayer::cheerHeiho()
{
    ASet<CHeiho>* heihos = ASet<CHeiho>::instance();
    CHeiho* h = heihos->begin(); /* begin before end: retail's order */
    CLinkNode* end = heihos->end();
    for (; h != end; h = h->next()) {
        if (h->GetIdx() == m_idx) {
            h->cheer();
            break;
        }
    }
}

} // namespace m513
