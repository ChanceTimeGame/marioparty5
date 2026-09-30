#include "REL/m517Dll/config.h"
#include "REL/m517Dll/dusteff.h"
#include "REL/m517Dll/util.h"
extern "C" {
/* no live prototype (game/sprite.h has it commented out); as m513 powereff.cpp */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m517 {

void CShadow::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CShadow* self = (CShadow*)model->hookData;
    self->Draw(mtx);
}

CShadow::CShadow()
{
    m_model = Hu3DHookFuncCreate(DrawHook);
    HU3DMODEL* model = &Hu3DData[m_model];
    model->hookData = this;
    Hu3DModelLayerSet(m_model, 4);
    Hu3DModelCameraSet(m_model, 1);
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0013, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
    m_color.r = 0;
    m_color.g = 0;
    m_color.b = 0x40;
    m_color.a = 0x40;
}

CShadow::~CShadow()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

/* a 100 x 100 quad 5 above m_pos, texture anim 0x4B0013 modulated by m_color */
void CShadow::Draw(Mtx* view)
{
    Mtx m;
    PSMTXTrans(m, m_pos.x, m_pos.y + 5.0f, m_pos.z);
    PSMTXConcat(*view, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXColor color = m_color;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-50.0f, 0.0f, -50.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(50.0f, 0.0f, -50.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(50.0f, 0.0f, 50.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(-50.0f, 0.0f, 50.0f);
    GXColor4u8(color.r, color.g, color.b, color.a);
    GXTexCoord2f32(1.0f, 0.0f);
    GXEnd();
}

void CShadow2::DrawHook(HU3DMODEL* model, Mtx* mtx)
{
    CShadow2* self = (CShadow2*)model->hookData;
    self->Draw(mtx);
}

CShadow2::CShadow2()
{
    m_model = Hu3DHookFuncCreate(DrawHook);
    HU3DMODEL* model = &Hu3DData[m_model];
    model->hookData = this;
    Hu3DModelLayerSet(m_model, 2);
    Hu3DModelCameraSet(m_model, 1);
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x4B0013, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
    m_pos.x = 0.0f;
    m_pos.y = 0.0f;
    m_pos.z = 0.0f;
}

CShadow2::~CShadow2()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

/* a disc of radius 50 (centre 2 above m_pos, rim 16 below the centre), back faces culled, no Z test */
void CShadow2::Draw(Mtx* view)
{
    Mtx m;
    PSMTXTrans(m, m_pos.x, m_pos.y + 2.0f, m_pos.z);
    PSMTXConcat(*view, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 10);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(0, 0, 0x40, 0x40);
    GXTexCoord2f32(0.5f, 0.5f);
    for (int i = 0; i < 9; i++) {
        float a = M_PI * (45.0f * i) / 180.0;
        float c = cos(a);
        float s = sin(a);
        float x = 100.0f * (0.5f * c);
        float z = 100.0f * (0.5f * s);
        float u = 0.5f + 0.5f * c;
        float v = 0.5f + 0.5f * s;
        GXPosition3f32(x, -16.0f, z);
        GXColor4u8(0, 0, 0x40, 0x40);
        GXTexCoord2f32(u, v);
    }
    GXEnd();
}

} // namespace m517
