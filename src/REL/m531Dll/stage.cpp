/* stage.cpp -- CStage (stage.h). Every function written whole (skeleton). */
#include "REL/m531Dll/stage.h"

namespace m531 {

void CStage::ObjUpdate(omObj_s* obj)
{
    CStage* self = (CStage*)obj->data;
    self->on_update();
}

CStage::CStage(Process_s* om, u32 dataNum, s16 layer, s16 prio, u16 camBit)
{
    m_om = om;
    m_model = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    m_obj = omAddObjEx(om, prio, 16, 16, -1, ObjUpdate);
    m_obj->data = this;
    Hu3DModelLayerSet(m_model, layer);
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

CStage::~CStage()
{
    Hu3DModelKill(m_model);
    m_obj->data = 0;
    omDelObjEx(m_om, m_obj);
}

void CStage::setShadow()
{
    Hu3DModelShadowSet(m_model);
    Hu3DModelShadowDispOn(m_model);
}

} // namespace m531
