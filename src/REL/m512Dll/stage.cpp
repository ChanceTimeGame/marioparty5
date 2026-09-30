/* stage.cpp -- m512::CStage: the eight stage models and the shadow; a dead track-outline draw hook.
 * SKELETON: bodies marked STUB are the function forks'. The ctor is drafted from stage.s (per model:
 * layer, [light], pos 0, PAUSE off, LOOP on, DISPOFF off, [shadow map], [shape motion]) -- verify. */
#include "REL/m512Dll/stage.h"

namespace m512 {

/* lbl_1_rodata_140/14C/158: the shadow camera, passed to Hu3DShadowPosSet as pointers into .rodata (sheet
 * §8.8: the host casts const away; Hu3D only reads them) */
static const Vec s_shadowPos = { 0.0f, 3800.0f, 0.0f };
static const Vec s_shadowUp = { 0.0f, 0.0f, 1.0f };
static const Vec s_shadowTarget = { 0.0f, 0.0f, 0.0f };

CStage::CStage()
    : m_model0(0x460000U), m_model1(0x460001U), m_model2(0x460002U), m_model3(0x460003U), m_model4(0x460004U),
      m_model5(0x460005U), m_model6(0x460007U), m_model7(0x460008U)
{
    HU3DMODELID id;
    HU3DMOTID shape;

    id = m_model0.id();
    Hu3DModelLayerSet(id, 2);
    Hu3DModelLightInfoSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);

    id = m_model1.id();
    Hu3DModelLayerSet(id, 2);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapSet(id);

    id = m_model2.id();
    Hu3DModelLayerSet(id, 2);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);

    id = m_model3.id();
    Hu3DModelLayerSet(id, 1);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapSet(id);

    id = m_model4.id();
    Hu3DModelLayerSet(id, 0);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);

    id = m_model5.id();
    Hu3DModelLayerSet(id, 0);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);

    id = m_model6.id();
    Hu3DModelLayerSet(id, 2);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    shape = Hu3DMotionShapeIDGet(id);
    Hu3DModelAttrSet(id, 0x40000040);
    Hu3DMotionShapeSet(id, shape);

    id = m_model7.id();
    Hu3DModelLayerSet(id, 0);
    Hu3DModelPosSet(id, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(id, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    shape = Hu3DMotionShapeIDGet(id);
    Hu3DModelAttrSet(id, 0x40000040);
    Hu3DMotionShapeSet(id, shape);

    Hu3DShadowSizeSet(480);
    Hu3DShadowCreate(45.0f, 100.0f, 6000.0f);
    Hu3DShadowTPLvlSet(0.2f);
    Hu3DShadowPosSet((HuVecF*)&s_shadowPos, (HuVecF*)&s_shadowUp, (HuVecF*)&s_shadowTarget);
}

void CStage::on_update() {}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    switch (mode) {
    case 0:
    case 5:
        break;
    }
}

/* dead: nothing registers this hook (no Hu3DHookFuncCreate / CModel(hook) in the REL) */
void CStage::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    Hu3DModelObjDrawInit();
    CStage* stage = CSingleton<CStage>::GetInstancePtr();
    stage->draw(mtx);
}

void CStage::draw(Mtx* mtx)
{
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    DrawTrack();
}

void CStage::DrawTrack()
{
    float X[80];
    float Z[80];
    float iX[33];
    float iZ[33];
    float oX[33];
    float oZ[33];
    int n = 0;
    int i;
    float t;
    float r;

    for (i = 0; i < 33; i++) {
        t = 360.0f * ((i & 31) / 32.0f) - 180.0f;
        t += 90.0f;
        if (t > 180.0f) {
            t -= 360.0f;
        }
        r = M_PI * t / 180.0;
        oX[i] = 100.0 * (15.0 * cos(r));
        oZ[i] = 100.0 * (15.0 * sin(r));
        iX[i] = 100.0 * (7.0 * cos(r));
        iZ[i] = 100.0 * (7.0 * sin(r));
    }
    for (i = 0; i < 17; i++) {
        X[n] = 300.0 + oX[i];
        Z[n] = oZ[i];
        n++;
        X[n] = 300.0 + iX[i];
        Z[n] = iZ[i];
        n++;
    }
    for (i = 16; i < 33; i++) {
        X[n] = -300.0 + oX[i];
        Z[n] = oZ[i];
        n++;
        X[n] = -300.0 + iX[i];
        Z[n] = iZ[i];
        n++;
    }
    X[n] = 300.0 + oX[0];
    Z[n] = oZ[0];
    n++;
    X[n] = 300.0 + iX[0];
    Z[n] = iZ[0];
    n++;

    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, n);
    for (i = 0; i < n; i++) {
        GXPosition3f32(X[i], 0.0f, Z[i]);
        GXColor4u8(0x40, 0x40, 0x40, 0xFF);
    }
    GXEnd();
}

CStage::~CStage() {}

} // namespace m512
