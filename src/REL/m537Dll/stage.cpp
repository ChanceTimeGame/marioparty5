#include "REL/m537Dll/stage.h"
#include "REL/m537Dll/dorrie.h"
#include "REL/m537Dll/water.h"
#include "REL/m537Dll/effect.h"

namespace m537 {

CStage::CStage() : CModel(0x5F0001u), m_sub(new CModel(0x5F0002u))
{
    HU3DMODELID id = ((CModel*)this)->id();
    Hu3DModelLightInfoSet((int)id, 1);
    setLayer(0);
    setAttr(0x40000001);
    m_sub->setLayer(0);
    m_sub->set_shadow();
    CreateDorrie();
    CreateObj();
    new CWater((int)id);
    new CEffect;
}

CStage::~CStage() {}

CDorrie* CStage::GetDorrie(int i)
{
    return m_dorrie[i].get();
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* one Dorrie per player at the diagonals (lbl_1_rodata_2A8), no turn time */
void CStage::CreateDorrie()
{
    static const float s_angle[NUM_DORRIE] = { 45.0f, -45.0f, 135.0f, -135.0f };
    for (int i = 0; i < NUM_DORRIE; i++) {
        m_dorrie[i].reset(new CDorrie(i));
        m_dorrie[i]->SetAngle(s_angle[i], 0.0);
    }
}

/* the three props (lbl_1_rodata_2C0), each motion ~500 frames long, phase-shifted by one frame */
void CStage::CreateObj()
{
    static const u32 s_objData[NUM_OBJ] = { 0x5F000F, 0x5F0010, 0x5F0011 };
    for (int i = 0; i < NUM_OBJ; i++) {
        m_obj[i].reset(new CModel((unsigned int)s_objData[i]));
        s16 id = m_obj[i]->id();
        float max = Hu3DMotionMaxTimeGet((int)id);
        float len = 499.8f;
        Hu3DMotionSpeedSet((int)id, max / len);
        Hu3DMotionTimeSet((int)id, max - (float)i);
        m_obj[i]->setAttr(0x40000001);
    }
}

} // namespace m537
