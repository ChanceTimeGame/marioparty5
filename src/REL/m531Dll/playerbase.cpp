/* playerbase.cpp -- CPlayerBase and CModelBase's ctor (playerbase.h), in retail order. Written whole from the asm. */
#include "REL/m531Dll/playerbase.h"

namespace m531 {

void CPlayerBase::ObjEnter(omObj_s* obj)
{
    CPlayerBase* self = (CPlayerBase*)obj->data;
    self->UpdateEnter();
}

void CPlayerBase::ObjMain(omObj_s* obj)
{
    CPlayerBase* self = (CPlayerBase*)obj->data;
    self->UpdateMain();
}

void CPlayerBase::ObjGoal(omObj_s* obj)
{
    CPlayerBase* self = (CPlayerBase*)obj->data;
    self->UpdateGoal();
}

void CPlayerBase::ObjResult(omObj_s* obj)
{
    CPlayerBase* self = (CPlayerBase*)obj->data;
    self->UpdateResult();
}

CPlayerBase::CPlayerBase(Process_s* om, const MotionEntry* tbl, int motNum, s16 playerNo, u16 camBit)
{
    int i;

    /* the (s16) casts are retail's: CW -O0 emits an extsh for each */
    m_om = om;
    m_playerNo = (s16)playerNo;
    m_charNo = (s16)GwPlayerConf[playerNo].charNo;
    m_done = 0;
    m_arrived = 0;
    m_motTbl = tbl;
    m_motNum = motNum;
    m_model = CharModelCreate((s16)m_charNo, 2);
    for (i = 0; i < m_motNum; i++) {
        m_motion[i] = CharMotionCreate((s16)m_charNo, m_motTbl[i].dataNum);
    }
    CharMotionDataClose((s16)m_charNo);
    CharMotionSet((s16)m_charNo, m_motion[0]);
    Hu3DModelAttrSet(m_model, 0x40000001);
    m_obj = omAddObjEx(om, 4, 16, 16, -1, ObjEnter);
    m_obj->data = this;
    Hu3DModelShadowSet(m_model);
    Hu3DModelShadowDispOn(m_model);
    Hu3DModelLayerSet(m_model, 3);
    Hu3DModelCameraSet(m_model, camBit);
    Reset();
}

CPlayerBase::CPlayerBase(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum, u16 camBit)
{
    int i;

    m_om = om;
    m_playerNo = -1;
    m_charNo = -1;
    m_dif = -1;
    m_done = 0;
    m_arrived = 0;
    m_motTbl = tbl;
    m_motNum = motNum;
    m_dataNum = dataNum;
    m_model = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < m_motNum; i++) {
        m_motion[i] = Hu3DJointMotion(m_model, HuDataSelHeapReadNum(m_motTbl[i].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DMotionSet(m_model, m_motion[0]);
    Hu3DModelAttrSet(m_model, 0x40000001);
    Hu3DModelCameraSet(m_model, camBit);
    m_obj = omAddObjEx(om, 4, 16, 16, -1, ObjMain);
    m_obj->data = this;
    Hu3DModelShadowSet(m_model);
    Hu3DModelShadowDispOn(m_model);
    Hu3DModelLayerSet(m_model, 3);
    Hu3DModelCameraSet(m_model, camBit);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_scale.z = 1.0f;
}

CPlayerBase::~CPlayerBase()
{
    int i;

    if (m_charNo != -1) {
        CharModelKill((s16)m_charNo);
    } else {
        for (i = 0; i < m_motNum; i++) {
            Hu3DMotionKill(m_motion[i]);
        }
        Hu3DModelKill(m_model);
    }
    m_obj->data = 0;
    omDelObjEx(m_om, m_obj);
}

void CPlayerBase::Reset()
{
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_rot.x = 0.0f;
    m_rot.y = 0.0f;
    m_rot.z = 0.0f;
    m_scale.x = 1.0f;
    m_scale.y = 1.0f;
    m_scale.z = 1.0f;
    m_type = GwPlayerConf[m_playerNo].type;
    m_dif = GwPlayerConf[m_playerNo].dif;
    m_pad = GwPlayerConf[m_playerNo].padNo;
    m_reqMotion = m_curMotion = 0;
}

void CPlayerBase::UpdateEnter()
{
    UpdateModel();
}

void CPlayerBase::UpdateMain()
{
    if (!m_done) {
        if (m_type != 0 || m_playerNo == -1) {
            InputCom();
        } else {
            InputPad();
        }
    }
    Move();
    UpdateModel();
}

void CPlayerBase::UpdateResult()
{
    UpdateModel();
}

void CPlayerBase::UpdateGoal()
{
    m_arrived = 1;
}

void CPlayerBase::InputPad()
{
    s8 pad = m_pad;

    m_stickX = HuPadStkX[pad];
    m_stickY = -HuPadStkY[pad];
}

void CPlayerBase::SetMotion(int mot)
{
    m_reqMotion = mot;
}

void CPlayerBase::UpdateModel()
{
    s16 model = m_model;

    Hu3DModelPosSet(model, m_pos.x, m_pos.y, m_pos.z);
    Hu3DModelRotSet(model, m_rot.x, m_rot.y, m_rot.z);
    ApplyMotion(m_reqMotion);
}

void CPlayerBase::ApplyMotion(int mot)
{
    if ((u32)m_curMotion != (u32)mot) {
        Hu3DModelAttrReset(m_model, 0x40000002);
        if (m_playerNo != -1) {
            CharMotionShiftSet((s16)m_charNo, m_motion[mot], 0.0f, m_motTbl[mot].shift, m_motTbl[mot].attr);
        } else {
            Hu3DMotionShiftSet(m_model, m_motion[mot], 0.0f, m_motTbl[mot].shift, m_motTbl[mot].attr);
        }
        m_curMotion = mot;
    }
}

void CPlayerBase::Finish()
{
    m_obj->objFunc = ObjGoal;
}

void CPlayerBase::SetResult(int result, int motion)
{
    switch (result) {
    case 0:
        m_reqMotion = motion;
        GWMgCoinBonusSet(m_playerNo, GWMgCoinBonusGet(m_playerNo) + 10);
        break;
    case 1:
        m_reqMotion = motion;
        break;
    case -1:
        m_reqMotion = motion;
        break;
    }
    m_done = 1;
    m_obj->objFunc = ObjResult;
}

void CPlayerBase::Start()
{
    m_obj->objFunc = ObjMain;
}

CModelBase::CModelBase(Process_s* om, const MotionEntry* tbl, int motNum, u32 dataNum)
    : CPlayerBase(om, tbl, motNum, dataNum, 1)
{
}

} // namespace m531
