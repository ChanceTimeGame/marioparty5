/* player.cpp -- m539::CPlayer. The ctor's assert is retail's player.cpp:48 (keep the line). */
#include "REL/mgcpp/minigame.h"
#include "REL/mgcpp/gameobject.h"
#include "REL/m539Dll/player.h"
#include "REL/m539Dll/score.h"

namespace m539 {

CInput* CInput::Create(int idx)
{
    if (GwPlayerConf[idx].type != 0) {
        return new CInputCom;
    }
    return new CInputPad(idx);
}

/* fn_1_D0B4 (masked 0; raw residue = .data labels only) */
CPlayer::CPlayer(int idx, CScore* score)
    : m_input(CInput::Create(idx)), m_mot_id(), m_model(new CModel(GwPlayerConf[idx].charNo, 3)), m_count(0),
      m_score(score)
{
    m_model.get()->setCamera(1 << idx);
    insertBack(ASet<CPlayer>::instance());
    m_idx = idx;
    m_charNo = GwPlayerConf[idx].charNo;
    m_height = CharModelHeightGet(m_charNo);
    m_motion = 0;
    m_mot_id.clear();
    m_mot_id.reserve(NUMBEROF_MOTION);
    createMotion(0x8C0000); /* 0 idle */
    createMotion(0x8C0003); /* 1 jump */
    createMotion(0x8C000B); /* 2 (unused) */
    createMotion(0x8700DD); /* 3 intro peak */
    createMotion(0x8C0004); /* 4 land */
    createMotion(0x8C0030); /* 5 win */
    createMotion(0x8C0031); /* 6 lose */
    /* line padding: the assert below is retail's player.cpp:48 */










    assert(m_mot_id.size() == NUMBEROF_MOTION);
    CharMotionDataClose(m_charNo);
    CharModelFxFlagSet(m_charNo, 0);
    HU3DMODELID id = m_model.get()->id();
    Hu3DModelShadowSet(id);
    Hu3DModelShadowDispOn(id);
    setProc(&CPlayer::proc_init);
    CharMotionShiftSet(m_charNo, m_mot_id[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
    setState(0);
    m_vel.x = 0.0f;
    m_vel.y = 0.0f;
    m_vel.z = 0.0f;
    m_accel.x = 0.0f;
    m_accel.y = 0.0f;
    m_accel.z = 0.0f;
    m_model.get()->setLayer(2);
    m_intro = false;
    m_yaw = 270.0f;
}

void CPlayer::createMotion(int dataNum)
{
    s16 mot = CharMotionCreate(m_charNo, dataNum);
    m_mot_id.push_back(mot);
}

/* the board's "8 reels stopped" test through an inline taking the board (update D788's register use; retail
 * probably a CScore accessor -- score.h is F2's) */
static inline bool IsBoardStopped(CScore* score) { return score->m_stopCount == 8; }

void CPlayer::update()
{
    CharModelVoicePanSet(m_charNo, (m_idx & 1) == 0 ? 0x30 : 0x50);
    CInput* input = m_input.get();
    if (CGameObject::GetUpdateMode() == 2 && !IsBoardStopped(m_score)) {
        input->update();
    } else {
        input->m_data.on = false;
    }
    if (m_proc) {
        (this->*m_proc)();
    }
    updatePhysics();
    m_model->setPos(&m_pos);
    Vec rot;
    SetVec(&rot, 0.0f, m_yaw, 0.0f);
    m_model->setRot(&rot);
}

void CPlayer::setMotion(int slot, bool once)
{
    s16 model = m_model->id(); /* retail: dead */
    s16 mot = m_mot_id[slot];
    if (m_motion != slot) {
        int start = 0;
        int blend = 3;
        if (slot == 1) {
            switch (GwPlayerConf[m_idx].charNo) {
            case 2:
            case 5:
                start = Hu3DMotionMotionMaxTimeGet(mot);
                blend = 2;
                break;
            }
        }
        CharMotionShiftSet(m_charNo, mot, start, blend, !once ? HU3D_MOTATTR_LOOP : 0);
        m_motion = slot;
    }
}

void CPlayer::updatePhysics()
{
    m_accel.y += -3.3333333333333335;
    Vec old;
    old.x = m_vel.x;
    old.y = m_vel.y;
    old.z = m_vel.z;
    PSVECAdd(&m_accel, &m_vel, &m_vel);
    m_accel.x = 0.0f;
    m_accel.y = 0.0f;
    m_accel.z = 0.0f;
    PSVECAdd(&m_vel, &old, &old);
    PSVECScale(&old, &old, 0.5f);
    PSVECAdd(&old, &m_pos, &m_pos);
    if (m_pos.y < 0.0f) {
        m_pos.y = 0.0f;
        m_vel.y = 0.0f;
    }
}

void CPlayer::setState(int state)
{
    /* stays OUT of line (retail calls it everywhere): its size sits just over CW's auto-inline limit (probe:
     * inline_max_size >= 499 inlined the old draft). The vel reset through SetVec (case 4) is what pushes it
     * over -- the same code as three float stores. The impulse switch reads GwPlayerConf, not m_charNo.
     * Doubles: charNo 2/5 27.5 (1650/60), 6 30.833 (1850/60), others 33.333 (2000/60). */
    switch (state) {
    case 0:
        setMotion(0, false);
        break;
    case 1:
        setMotion(1, true);
        switch (GwPlayerConf[m_idx].charNo) {
        case 2:
        case 5:
            m_accel.y += 27.5;
            break;
        case 6:
            m_accel.y += 30.833333333333336;
            break;
        default:
            m_accel.y += 33.333333333333336;
            break;
        }
        break;
    case 2:
        break;
    case 3:
        Hu3DMotionSpeedSet(m_model->id(), 1.0f);
        setMotion(4, true);
        break;
    case 4:
        SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
        break;
    default:
        break;
    }
    m_state = state;
    m_stateTime = 0;
}

void CPlayer::stateIdle()
{
    SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
    CInput::Data* data = getInputData();
    if (data->on) {
        setState(1);
        return;
    }
}

void CPlayer::stateJump()
{
    if (m_vel.y < 0.0f) {
        if (!m_intro) {
            m_score->stopNext();
            if (GwPlayerConf[m_idx].type == 0) {
                omVibrate(m_idx, 10, 4, 2);
            }
        }
        setState(2);
        return;
    }
}

void CPlayer::stateFall()
{
    float h = m_pos.y - 30.000002f;
    if (h <= 0.0f) {
        setState(3);
        return;
    }
}

void CPlayer::stateLand()
{
    if (m_pos.y <= 0.0f) {
        SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
        if (CharMotionEndCheck(m_charNo)) {
            setState(0);
            return;
        }
    }
}

void CPlayer::setWin()
{
    setMotion(5, true);
    setState(4);
    CharFXPlayPan(m_charNo, 0x1FA, (m_idx & 1) == 0 ? 0x30 : 0x50);
}

void CPlayer::setLose()
{
    setMotion(6, true);
    setState(4);
}

/* the head's position/velocity through an inline taking the board (retail's register hops in E554/E6C0: the
 * board pointer is the inline's parameter, then its return). Retail probably had CScore accessors (score.h is
 * F2's; the code is the same) */
static inline Vec* GetHeadPos(CScore* score) { return &score->m_headPos; }
static inline Vec* GetHeadVel(CScore* score) { return &score->m_headVel; }

void CPlayer::proc_none() {}

void CPlayer::proc_init()
{
    m_pos.x = 125.0f;
    m_pos.y = 0.0f;
    m_pos.z = -210.0f;
    int wait = 120; /* retail: a named local (li r31) */
    m_count = wait;
    setProc(&CPlayer::proc_wait);
    m_intro = true;
}

void CPlayer::proc_wait()
{
    if (countDown()) {
        m_accel.x -= 8.333333333333334;
        m_accel.y += 58.333333333333336;
        setMotion(1, true);
        setProc(&CPlayer::proc_enterJump);
    }
}

void CPlayer::proc_enterJump()
{
    if (m_vel.y > 0.0f && m_pos.y > 250.0f) {
        setMotion(3, true);
    }
    if (m_vel.y < 0.0f) {
        Vec* pos = GetHeadPos(m_score); /* retail: dead (E664) */
        m_score->start();
        setProc(&CPlayer::proc_enterLand);
    }
}

void CPlayer::proc_enterLand()
{
    Vec* pos = GetHeadPos(m_score);
    m_pos.x = pos->x;
    m_pos.y = pos->y;
    m_pos.z = pos->z;
    if (GetHeadVel(m_score)->y > 0.0f) {
        m_pos.x = 50.0f;
        setProc(&CPlayer::proc_turn);
        setMotion(4, true);
        m_score->startSpin();
    }
    SetVec(&m_vel, 0.0f, 0.0f, 0.0f);
}

void CPlayer::proc_turn()
{
    m_yaw += 10.0f;
    if (m_yaw >= 345.0f) {
        m_yaw = 345.0f;
    }
    if (m_pos.y <= 0.0f) {
        setProc(&CPlayer::proc_ready);
        setState(0);
        int wait = 30; /* retail: a named local (li r30) */
        m_count = wait;
    }
}

void CPlayer::proc_ready()
{
    if (countDown()) {
        setProc(&CPlayer::proc_main);
        m_intro = false;
        m_score->appear();
    }
}

void CPlayer::proc_main()
{
    switch (m_state) {
    case 0:
        stateIdle();
        break;
    case 1:
        stateJump();
        break;
    case 2:
        stateFall();
        break;
    case 3:
        stateLand();
        break;
    case 4:
        break;
    }
}

} // namespace m539
