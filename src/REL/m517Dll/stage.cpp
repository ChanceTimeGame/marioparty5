#include "REL/m517Dll/config.h"
#include "REL/m517Dll/stage.h"
#include "REL/m517Dll/kuribo.h"

namespace m517 {

/* lbl_1_data_4F0 / 4F4 / 500 */
static GXColor s_bgCol = { 0xF0, 0xFA, 0xA0, 0x00 };
static Vec s_lightPos = { 1.0f, 4179.7339f, 3252.001f };
static GXColor s_lightCol = { 0xFF, 0xFF, 0xFF, 0xFF };

/* lbl_1_rodata_2A0 / 2D0 / 300: four entries, only two Goombas are made (retail) */
static const Vec s_kuriboPos[4] = { { 600.0f, 245.0f, -1085.0f }, { -950.0f, 147.0f, -587.0f },
                                    { 545.0f, 257.0f, 498.0f }, { -200.0f, 61.0f, 752.0f } };
static const Vec s_kuriboRot[4] = { { 0.0f, -8.0f, 0.0f }, { 0.0f, 65.0f, 0.0f }, { 0.0f, -130.0f, 0.0f },
                                    { 0.0f, 170.0f, 0.0f } };
static const int s_kuriboType[4] = { 2, 0, 0, 1 };

CStage::CStage() : m_bg0(0x4B0001u), m_bg1(0x4B0002u), m_bg2(0x4B0003u)
{
    Vec dir;
    Vec shadowPos;
    Vec up;
    Vec target;
    Vec zero;
    Hu3DBGColorSet(s_bgCol.r, s_bgCol.g, s_bgCol.b);
    Hu3DLighInit();
    PSVECNormalize(&s_lightPos, &dir);
    PSVECScale(&dir, &dir, -1.0f);
    int light = Hu3DGLightCreateV(&s_lightPos, &dir, &s_lightCol);
    Hu3DGLightInfinitytSet(light);
    Hu3DGLightStaticSet(light, 1);
    Hu3DShadowCreate(20.0f, 100.0f, 50000.0f);
    Hu3DShadowTPLvlSet(0.4f);
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    PSVECScale(&dir, &shadowPos, -3000.0f);
    PSVECAdd(&shadowPos, &target, &shadowPos);
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    Hu3DShadowPosSet(&shadowPos, &up, &target);
    Hu3DShadowColSet(0, 0, 0x40);
    Hu3DModelShadowMapSet(m_bg1.id());
    Hu3DModelLayerSet(m_bg1.id(), 1);
    Hu3DModelLayerSet(m_bg0.id(), 1);
    Hu3DModelLayerSet(m_bg2.id(), 1);
    Hu3DModelAttrSet(m_bg2.id(), HU3D_MOTATTR_LOOP);
    zero.x = 0.0f;
    zero.y = 0.0f;
    zero.z = 0.0f;
    m_bg1.setPos(&zero);
    m_impact.x = 0.0f;
    m_impact.y = 0.0f;
    m_impact.z = 0.0f;
    Hu3DFogSet(1000.0f, 1500.0f, s_bgCol.r, s_bgCol.g, s_bgCol.b);
    Hu3DLayerHookSet(0, FogHookLayer0);
    Hu3DLayerHookSet(1, FogHookLayer1);
    for (int i = 0; i < 2; i++) {
        new CKuribo((Vec*)&s_kuriboPos[i], (Vec*)&s_kuriboRot[i], s_kuriboType[i]);
    }
}

void CStage::on_update() {}

/* the fog starts at the XZ distance from the eye to a point 100 ahead of it (d - pos: retail's math) */
void CStage::FogHookLayer0(s16 layer)
{
    HU3DCAMERA* cam = &Hu3DCamera[0];
    Vec pos = cam->pos;
    Vec tgt = cam->target;
    Vec ofs;
    Vec dir;
    pos.y = 0.0f;
    tgt.y = 0.0f;
    PSVECSubtract(&tgt, &pos, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 100.0f);
    PSVECSubtract(&dir, &pos, &ofs);
    float mag = PSVECMag(&ofs);
    float dist = mag;
    GXSetFog(GX_FOG_PERSP_LIN, dist, 2000.0f + dist, cam->near, cam->far, s_bgCol); /* s_bgCol by value: the temp */
}

void CStage::FogHookLayer1(s16 layer)
{
    HU3DCAMERA* cam = &Hu3DCamera[0];
    Vec pos = cam->pos;
    Vec tgt = cam->target;
    Vec ofs;
    Vec dir;
    pos.y = 0.0f;
    tgt.y = 0.0f;
    PSVECSubtract(&tgt, &pos, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 2200.0f);
    PSVECSubtract(&dir, &pos, &ofs);
    float mag = PSVECMag(&ofs);
    float dist = mag;
    GXSetFog(GX_FOG_PERSP_EXP, dist - 200.0f, dist, cam->near, cam->far, s_bgCol);
}

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

} // namespace m517
