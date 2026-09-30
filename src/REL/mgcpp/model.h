/* model.h -- CModel (model.cpp): a Hu3D model id with helpers. GC size 2. No virtuals. */
#ifndef MGCPP_MODEL_H
#define MGCPP_MODEL_H

#include "REL/mgcpp/game.h"

class CModel {
public:
    CModel(void* data);             /* Hu3DModelCreate */
    CModel(unsigned int dataNum);   /* FUi: Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL)) */
    CModel(HU3DMODELHOOK hook);     /* Hu3DHookFuncCreate */
    CModel(int charNo, int type);   /* CharModelCreate, type 0..3 -> 1/2/4/8 */
    CModel(CModel& src);            /* Hu3DModelLink */
    void setAttr(unsigned int attr);
    void resetAttr(unsigned int attr);
    void setObjXform(omObj_s* obj);
    void setPos(Vec* pos);
    void setRot(Vec* rot);
    void setScale(Vec* scale);
    void setScale(float scale);
    void setTPLvl(float tpLvl);
    void setLayer(s16 layer);
    void setCamera(u16 camBit);
    void setHookData(void* data);
    Mtx* getMatrix();
    ~CModel();
    HSFOBJECT* getObjPtr(const char* name); /* asserts model.cpp:138 */
    void set_shadow();
    void setShadowMap();
    void setShadowMapObj(const char* name);
    void resetShadowMapObj();
    void shadowMapOffObj(char* name);
    void shadowOnObj(char* name);
    void shadowOffObj(char* name);
    void shadowOnlyObjOn(char* name);
    void shadowOnlyObjOff(char* name);
    void setMotTime(int time);

    /* const: retail loads it as lha + extsh through a temporary (CModel(CModel&), setMotTime) */
    HU3DMODELID id() const { return m_id; }

    HU3DMODELID m_id; /* 0x0 */
};

#endif
