/* effect.cpp -- CHookEffect and CParticleEffect (effect.h). Every function is written whole (skeleton). */
#include "REL/m531Dll/effect.h"

namespace m531 {

void CHookEffect::ObjUpdate(omObj_s* obj)
{
    CHookEffect* self = (CHookEffect*)obj->data;
    self->on_update();
}

void CHookEffect::on_update() {}

void CHookEffect::HookDraw(HU3DMODEL* model, Mtx* mtx)
{
    CHookEffect* self = (CHookEffect*)model->hookData;
    self->draw(mtx);
}

void CHookEffect::draw(Mtx* mtx) {}

CHookEffect::CHookEffect(Process_s* om, s16 layer, s16 prio, u16 camBit)
{
    m_om = om;
    m_obj = omAddObjEx(om, prio, 0, 0, -1, ObjUpdate);
    m_obj->data = this;
    m_model = Hu3DHookFuncCreate(HookDraw);
    HU3DMODEL* model = &Hu3DData[m_model];
    model->hookData = this;
    Hu3DModelLayerSet(m_model, layer);
    Hu3DModelCameraSet(m_model, camBit);
}

CHookEffect::~CHookEffect()
{
    m_obj->data = 0;
    omDelObjEx(m_om, m_obj);
    Hu3DModelKill(m_model);
}

void CHookEffect::setCamera(u16 camBit)
{
    Hu3DModelCameraSet(m_model, camBit);
}

void CHookEffect::show()
{
    Hu3DModelAttrReset(m_model, HU3D_ATTR_DISPOFF);
}

void CHookEffect::hide()
{
    Hu3DModelAttrSet(m_model, HU3D_ATTR_DISPOFF);
}

void CParticleEffect::Hook(HU3DMODEL* model, HU3DPARTICLE* particle, Mtx mtx)
{
    CParticleEffect* self = (CParticleEffect*)particle->work;
    self->on_hook(mtx);
}

void CParticleEffect::on_hook(Mtx mtx) {}

CParticleEffect::CParticleEffect(u32 dataNum, int maxCnt, u16 camBit)
{
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    m_model = Hu3DParticleCreate(m_anim, maxCnt);
    m_particle = (HU3DPARTICLE*)Hu3DData[m_model].hookData;
    m_particle->work = this;
    setCamera(camBit);
}

CParticleEffect::~CParticleEffect()
{
    HuSprAnimKill(m_anim);
    Hu3DModelKill(m_model);
}

void CParticleEffect::setCamera(u16 camBit)
{
    Hu3DModelCameraSet(m_model, camBit);
}

void CParticleEffect::show()
{
    Hu3DModelAttrReset(m_model, HU3D_ATTR_DISPOFF);
}

void CParticleEffect::hide()
{
    Hu3DModelAttrSet(m_model, HU3D_ATTR_DISPOFF);
}

} // namespace m531
