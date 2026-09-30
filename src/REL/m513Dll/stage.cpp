/* stage.cpp -- m513::CStage: the three stage models, the dark background and the multi-shadow from the model's
 * "light". Retail order (.text 104B0..10964): ctor, [~CSingleton<CStage> 107BC (weak)], on_update, on_new_mode,
 * dtor. .data 760..7A0: the singleton strings, the vtable. .rodata 438..460 ("light", the shadow constants).
 * on_update = m512's; on_new_mode is m512's with five empty cases 0..4 (raw 0; m512's `case 0: case 5:` gives 12). Skeleton draft of the ctor from the sheet
 * (master_camera_stage_score_audio.md §5). */
#include "REL/m513Dll/stage.h"

namespace m513 {

/* fn_1_104B0: the models, the dark background, the multi-shadow cast from 3000 back along the "light" direction */
CStage::CStage() : m_model0(0x470000u), m_model1(0x470001u), m_model2(0x470002u)
{
    Vec pos;
    Vec dir;
    Vec shadowPos;
    Vec up;
    Vec target;
    Hu3DBGColorSet(0x32, 0x32, 0x9C);
    char name[6] = "light";
    GXColor col;
    Hu3DModelLightInfoSet(m_model0.id(), 1);
    HU3DLIGHTID light = Hu3DModelLightIdGet(m_model0.id(), name);
    Hu3DGLightParamGet(light, &pos, &dir, &col);
    Hu3DShadowMultiCreate(20.0f, 100.0f, 50000.0f, 1);
    Hu3DShadowTPLvlSet(0.4f);
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    PSVECScale(&dir, &shadowPos, -3000.0f);
    PSVECAdd(&shadowPos, &target, &shadowPos);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    Hu3DShadowMultiPosSet(&shadowPos, &up, &target, 1);
    Hu3DShadowMultiColSet(0, 0, 0x40, 1);
    Hu3DShadowMultiSizeSet(0x60, 1);
    Hu3DModelShadowMapSet(m_model0.id());
    Hu3DModelLayerSet(m_model0.id(), 1);
    Hu3DModelCameraSet(m_model0.id(), 1);
    Hu3DModelLayerSet(m_model1.id(), 1);
    Hu3DModelCameraSet(m_model1.id(), 1);
    Hu3DModelLayerSet(m_model2.id(), 3);
    Hu3DModelCameraSet(m_model2.id(), 1);
    Hu3DModelAttrSet(m_model2.id(), HU3D_MOTATTR_LOOP);
}

void CStage::on_update() {}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
        break;
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    }
}

CStage::~CStage() {}

} // namespace m513
