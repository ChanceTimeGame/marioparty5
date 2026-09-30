/* model.cpp -- CModel: a Hu3D model id with helpers. Retail order.
 * getObjPtr's assert must stay on model.cpp line 138 (retail .data / li r6,0x8a). */
#include "REL/mgcpp/model.h"
#include "REL/mgcpp/assert.h"

CModel::CModel(void* data)
{
    m_id = Hu3DModelCreate(data);
}

CModel::CModel(unsigned int dataNum)
{
    m_id = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

CModel::CModel(HU3DMODELHOOK hook)
{
    m_id = Hu3DHookFuncCreate(hook);
}

/* type 0..3 selects the character model variant bit (1/2/4/8); anything else passes 0 */
CModel::CModel(int charNo, int type)
{
    int bit = 0;
    switch (type) {
    case 0:
        bit = 1;
        break;
    case 1:
        bit = 2;
        break;
    case 2:
        bit = 4;
        break;
    case 3:
        bit = 8;
        break;
    }
    m_id = CharModelCreate(charNo, bit);
}

CModel::CModel(CModel& src)
{
    m_id = Hu3DModelLink(src.id());
}

void CModel::setAttr(unsigned int attr)
{
    Hu3DModelAttrSet(m_id, attr);
}

void CModel::resetAttr(unsigned int attr)
{
    Hu3DModelAttrReset(m_id, attr);
}

void CModel::setObjXform(omObj_s* obj)
{
    HU3DMODELID id = m_id;
    Hu3DModelPosSet(id, obj->trans.x, obj->trans.y, obj->trans.z);
    Hu3DModelRotSet(id, obj->rot.x, obj->rot.y, obj->rot.z);
    Hu3DModelScaleSet(id, obj->scale.x, obj->scale.y, obj->scale.z);
}

void CModel::setPos(Vec* pos)
{
    Hu3DModelPosSet(m_id, pos->x, pos->y, pos->z);
}

void CModel::setRot(Vec* rot)
{
    Hu3DModelRotSet(m_id, rot->x, rot->y, rot->z);
}

void CModel::setScale(Vec* scale)
{
    Hu3DModelScaleSet(m_id, scale->x, scale->y, scale->z);
}

void CModel::setScale(float scale)
{
    Hu3DModelScaleSet(m_id, scale, scale, scale);
}

void CModel::setTPLvl(float tpLvl)
{
    Hu3DModelTPLvlSet(m_id, tpLvl);
}

void CModel::setLayer(s16 layer)
{
    Hu3DModelLayerSet(m_id, layer);
}

void CModel::setCamera(u16 camBit)
{
    Hu3DModelCameraSet(m_id, camBit);
}

void CModel::setHookData(void* data)
{
    Hu3DData[m_id].hookData = data;
}

Mtx* CModel::getMatrix()
{
    return &Hu3DData[m_id].mtx;
}

CModel::~CModel()
{
    Hu3DModelKill(m_id);
}




















/* a missing object name panics (retail asserts are compiled in) */
HSFOBJECT* CModel::getObjPtr(const char* name)
{
    HSFOBJECT* p = Hu3DModelObjPtrGet(m_id, (char*)name);
    assert(p != NULL);
    return p;
}

void CModel::set_shadow()
{
    Hu3DModelShadowSet(m_id);
}

void CModel::setShadowMap()
{
    Hu3DModelShadowMapSet(m_id);
}

void CModel::setShadowMapObj(const char* name)
{
    Hu3DModelShadowMapObjSet(m_id, (char*)name);
}

void CModel::resetShadowMapObj()
{
    Hu3DModelShadowMapObjReset(m_id);
}

void CModel::shadowMapOffObj(char* name)
{
    HSFOBJECT* obj = getObjPtr(name);
    HSFCONSTDATA* constData = (HSFCONSTDATA*)obj->constData;
    constData->attr &= ~HU3D_CONST_SHADOW_MAP;
}

void CModel::shadowOnObj(char* name)
{
    HSFOBJECT* obj = getObjPtr(name);
    obj->flags |= HU3D_CONST_SHADOW;
}

void CModel::shadowOffObj(char* name)
{
    HSFOBJECT* obj = getObjPtr(name);
    obj->flags &= ~HU3D_CONST_SHADOW;
}

/* shadow caster only: shadowed, but drawn at zero scale */
void CModel::shadowOnlyObjOn(char* name)
{
    HSFOBJECT* obj = getObjPtr(name);
    obj->flags |= HU3D_CONST_SHADOW;
    HSFTRANSFORM* base = &obj->mesh.base;
    base->scale.x = 0.0f;
    base->scale.y = 0.0f;
    base->scale.z = 0.0f;
}

void CModel::shadowOnlyObjOff(char* name)
{
    HSFOBJECT* obj = getObjPtr(name);
    obj->flags &= ~HU3D_CONST_SHADOW;
    HSFTRANSFORM* base = &obj->mesh.base;
    base->scale.x = 1.0f;
    base->scale.y = 1.0f;
    base->scale.z = 1.0f;
}

void CModel::setMotTime(int time)
{
    Hu3DMotionTimeSet(id(), time);
}
