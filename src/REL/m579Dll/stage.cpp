#include "REL/m579Dll/stage.h"

namespace m579 {

/* lbl_1_rodata_388 / 394: the shadow projector's up and target (by address) */
static const Vec s_shadowUp = { 0.0f, 0.0f, 1.0f };
static const Vec s_shadowAt = { 0.0f, 0.0f, 0.0f };

CStage::CStage() : m_model(0x850000U), m_sub(0x850001U)
{
    HU3DMODELID id = m_model.id();
    Hu3DModelLightInfoSet(id, 1);
    m_model.setShadowMapObj("feeld_born"); /* sic */
    m_model.setLayer(2);
    m_model.setAttr(0x40000001);
    m_model.setAttr(0x40000040);
    m_sub.setLayer(0);
    m_sub.setAttr(0x40000001);
    double h = 816.0 / tan(0.39269908169872414);
    static Vec s_shadowPos = { 0.0f, (float)h, 0.0f };
    Hu3DShadowCreate(45.0f, h - 400.0, 50.0 + h);
    Hu3DShadowSizeSet(240);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&s_shadowPos, (Vec*)&s_shadowUp, (Vec*)&s_shadowAt);
}

void CStage::on_update() {}

void CStage::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
    /* every case empty: CW keeps only the folded compare chain (cmpwi 5 / bge, cmpwi 0 / b) */
    switch (mode) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
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
    DrawRing();
}

void CStage::DrawRing()
{
    float X[80];
    float Z[80];
    int i;
    int n = 0;
    for (i = 0; i < 33; i++) {
        float d = 360.0f * ((i & 31) / 32.0f) - 180.0f;
        d += 90.0f;
        if (d > 180.0f) {
            d -= 360.0f;
        }
        float a = M_PI * d / 180.0;
        X[n] = 100.0 * (8.5 * cos(a));
        Z[n] = 100.0 * (8.5 * sin(a));
        n++;
        X[n] = 100.0 * (4.5 * cos(a));
        Z[n] = 100.0 * (4.5 * sin(a));
        n++;
    }
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

} // namespace m579
