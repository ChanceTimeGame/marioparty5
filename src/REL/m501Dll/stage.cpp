/* stage.cpp -- m501::CStage: stage models, the global light and shadow, and the scoop-pile bob. */
#include "REL/m501Dll/stage.h"

namespace m501 {

/* lbl_1_data_408 / lbl_1_data_414: light position and colour (non-const .data) */
static Vec s_lightPos = { 9654.0f, 8151.0f, 2774.0f };
static GXColor s_lightColor = { 255, 255, 255, 255 };

CStage::CStage() : m_stageModel(0x3B0000U), m_shadowModel(0x3B0002U), m_camModel(0x3B0001U), m_aisuModel(0x3B0004U)
{
    Vec dir;
    Vec pos;
    Vec up;
    Vec target;

    m_timer = 0;
    Hu3DLighInit();
    PSVECNormalize(&s_lightPos, &dir);
    PSVECScale(&dir, &dir, -1.0f);
    int light = Hu3DGLightCreateV(&s_lightPos, &dir, &s_lightColor);
    Hu3DGLightInfinitytSet(light);
    Hu3DShadowCreate(30.0f, 20.0f, 25000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    target.x = 1578.489f;
    target.y = 5060.02f;
    target.z = 414.244f;
    PSVECScale(&dir, &pos, -3000.0f);
    PSVECAdd(&pos, &target, &pos);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DShadowColSet(0, 0, 64);
    Hu3DModelShadowMapSet(m_shadowModel.id());
    HU3DMODELID id = m_stageModel.id();
    HU3DMOTID mot = Hu3DMotionShapeIDGet(id);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DMotionShapeSet(id, mot);
    int start = 1;
    int end = 240;
    Hu3DMotionShapeTimeSet(id, start);
    Hu3DMotionShapeStartEndSet(id, start, end);
    m_angle = 0.0f;
}

/* restart the scoop-pile shape motion (called when a scoop lands); at most once per 37 frames */
void CStage::setAisuMotion()
{
    if (m_timer <= 0) {
        m_timer = 37;
        HU3DMODELID id = m_aisuModel.id();
        HU3DMOTID mot = Hu3DMotionShapeIDGet(id);
        Hu3DMotionShapeSet(id, mot);
    }
}

void CStage::on_update()
{
    bool done = false; /* retail: computed and never used */
    if (m_timer > 0) {
        if (--m_timer == 0) {
            done = true;
        }
    }
    Mtx* mtx = m_aisuModel.getMatrix();
    (*mtx)[1][3] = 0.1f * (100.0 * cos(m_angle));
    m_angle += 0.017453292519943292;
    if (m_angle > 3.141592653589793) {
        m_angle -= 6.283185307179586;
    }
}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 2:
        Hu3DCameraMotionOff(m_camModel.id());
        break;
    case 5:
        break;
    }
}

CStage::~CStage() {}

} // namespace m501
