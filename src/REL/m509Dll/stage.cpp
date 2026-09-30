/* stage.cpp -- m509::CStage: the arena models and the global light. A translation unit of its own (stage.h):
 * its .data is 0x80 bytes -- the light, the unused view, "ms_pointer == 0"/"singleton.h"/"ms_pointer != 0" and
 * the vtable, which CW emits at the end of a TU -- and player.cpp's .data follows with its own pooled copy of the
 * singleton strings. One TU cannot produce that (CW pools strings across the whole TU and emits vtables at its
 * end, #line/#include files notwithstanding: tested). No minigame.h here (the 120/210/210 triple is player's). */
#include "REL/m509Dll/stage.h"

namespace m509 {

/* .data 3438..3453: the global light (CStage ctor; writable, passed by pointer) */
static Vec s_lightPos = { 0.0f, -1000.0f, 0.0f };
static Vec s_lightTarget = { 0.0f, 10000.0f, 0.0f };
static GXColor s_lightColor = { 0xFF, 0xFF, 0xFF, 0xFF };
/* .data 3454: nine unreferenced floats (sheet C.4); external linkage keeps CW from dropping it; name ours */
Vec s_unusedView[3] = { { 2000.0f, 6000.0f, 2000.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };

/* the arena models' common setup (inlined twice: fresh id/mot temporaries per model, retail's registers) */
static inline void SetupStageModel(HU3DMODELID id, s32 layer)
{
    Hu3DModelLayerSet(id, layer);
    HU3DMOTID mot = Hu3DMotionIDGet(id);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(id, mot);
}

CStage::CStage() : m_model(0x430000U), m_model2(0x430001U)
{
    Hu3DLighInit();
    int light = Hu3DGLightCreateV((HuVecF*)&s_lightPos, (HuVecF*)&s_lightTarget, &s_lightColor);
    Hu3DGLightInfinitytSet(light);
    SetupStageModel(m_model.id(), 2);
    SetupStageModel(m_model2.id(), 0);
}

void CStage::on_update() {}

/* EXACT m512 stage 8758 */
void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 5:
        break;
    }
}

CStage::~CStage() {}

} // namespace m509
