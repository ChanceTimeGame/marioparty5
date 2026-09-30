#include "REL/m536Dll/stage.h"
#include "REL/mgcpp/random.h"

namespace m536 {

TLinkList<CStageCannon> CStageCannon::list;

/* lbl_1_data_338 / lbl_1_data_33C: fog colours, passed by value (one byte-wise copy to the stack) */
static GXColor s_fogColor = { 0, 0, 0, 0 };
static GXColor s_noFogColor = { 255, 255, 255, 0 };

/* fn_1_8A74: layer hook 8 (after layer 0): black exponential fog from the camera's near/far */
void FogOnHook(s16 layerNo)
{
    float fov;
    float near;
    float far;
    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(GX_FOG_EXP, 2200.0f, 15000.0f, near, far, s_fogColor);
}

/* fn_1_8B04: layer hook 0 (before layer 0): fog off */
void FogOffHook(s16 layerNo)
{
    float fov;
    float near;
    float far;
    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(GX_FOG_NONE, 2200.0f, 15000.0f, near, far, s_noFogColor);
}

CStage::CStage()
    : m_bgModel(0x5E0000U), m_model1(0x5E0001U), m_skyModel(0x5E0002U), m_smokeTmplA(0x5E0004U), m_smokeTmplB(0x5E0005U)
{
    HU3DMODELID id;
    HU3DMOTID mot;

    Hu3DLayerHookSet(0, FogOffHook);
    Hu3DLayerHookSet(8, FogOnHook);
    Hu3DZClearLayerSet(1);

    id = m_skyModel.id();
    Hu3DModelLayerSet(id, 0);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);

    id = m_model1.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    mot = Hu3DMotionIDGet(id);
    Hu3DMotionSet(id, mot);

    id = m_bgModel.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelLightInfoSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    mot = Hu3DMotionIDGet(id);
    Hu3DMotionSet(id, mot);

    HU3DMODELID tmplA = m_smokeTmplA.id();
    Hu3DModelAttrSet(tmplA, HU3D_ATTR_DISPOFF);
    HU3DMODELID tmplB = m_smokeTmplB.id();
    Hu3DModelAttrSet(tmplB, HU3D_ATTR_DISPOFF);

    int i = 0;
    float rot = -180.0f;
    for (i = 0; i < 4; i++) {
        new CStageCannon(m_smokeTmplA, i * 2, rot);
        new CStageCannon(m_smokeTmplB, i * 2 + 1, rot);
        m_fireTimer[i] = 0;
        rot += 90.0f;
    }
}

void CStage::on_update()
{
    for (int i = 0; i < 4; i++) {
        if (--m_fireTimer[i] < 0) {
            m_fireTimer[i] = (CRandom::irandom() & 0x7F) + 240;
            if (CRandom::irandom() & 1) {
                CStageCannon::Fire(i * 2);
            } else {
                CStageCannon::Fire(i * 2 + 1);
            }
        }
    }
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 5:
        break;
    }
}

/* lbl_1_data_36C: the clouds' start positions (non-const .data) */
static Vec s_cloudPos[4] = {
    { -1200.0f, -200.0f, -400.0f },
    { 0.0f, -200.0f, -1000.0f },
    { 500.0f, -100.0f, -1200.0f },
    { -700.0f, -300.0f, -1400.0f },
};

CCloud::CCloud() : m_model(0x5E0003U)
{
    m_ids[0] = m_model.id();
    m_ids[1] = Hu3DModelLink(m_model.id());
    m_ids[2] = Hu3DModelLink(m_model.id());
    m_ids[3] = Hu3DModelLink(m_model.id());
    for (int i = 0; i < 4; i++) {
        HU3DMODELID id = m_ids[i];
        m_pos[i] = s_cloudPos[i];
        Hu3DModelLayerSet(id, 0);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(id, 0.2f, 0.2f, 0.2f);
        Hu3DModelPosSet(id, m_pos[i].x, m_pos[i].y, m_pos[i].z);
        Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    }
}

void CCloud::on_update()
{
    for (int i = 0; i < 4; i++) {
        HU3DMODELID id = m_ids[i];
        float lim = 1500 + i * 200;
        if ((m_pos[i].x += 1.0f) > lim) {
            m_pos[i].x = -lim;
        }
        Hu3DModelPosSet(id, m_pos[i].x, m_pos[i].y, m_pos[i].z);
    }
}

void CCloud::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 5:
        break;
    }
}

CStageCannon::CStageCannon(CModel& tmpl, int index, float rotY) : m_model(tmpl)
{
    insertBack(&list);
    m_index = index;
    HU3DMODELID id = m_model.id();
    Hu3DModelLayerSet(id, 4);
    Hu3DModelCameraSet(id, 1);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(id, 1.0f);
    HU3DMOTID mot = Hu3DMotionIDGet(id);
    Hu3DMotionSet(id, mot);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
    Hu3DModelRotSet(id, 0.0f, rotY, 0.0f);
}

void CStageCannon::Close()
{
    while (!list.isEmpty()) {
        CStageCannon* p = list.last();
        delete p;
    }
}

void CStageCannon::UpdateAll()
{
    TLinkList<CStageCannon>::exec(&list, UpdateOne);
}

/* reached only through the dead UpdateAll: a fired smoke is never re-hidden (retail) */
void CStageCannon::UpdateOne(CStageCannon* p)
{
    if (Hu3DMotionEndCheck(p->m_model.id())) {
        Hu3DModelAttrSet(p->m_model.id(), HU3D_ATTR_DISPOFF);
    }
}

void CStageCannon::Fire(int index)
{
    CStageCannon* p = list.begin();
    CLinkNode* end = list.end();
    for (; p != end; p = p->next()) {
        if (p->m_index == index) {
            HU3DMODELID id = p->m_model.id();
            Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(id, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(id, 0.0f);
        }
    }
}

CCloud::~CCloud() {}

CStage::~CStage() {}

} // namespace m536
