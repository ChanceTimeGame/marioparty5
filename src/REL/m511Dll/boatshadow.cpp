#include "REL/m511Dll/config.h"
#include "REL/m511Dll/boatshadow.h"
extern "C" {
/* no live prototype (game/sprite.h has it commented out); as m537 effect.cpp */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
}

namespace m511 {

CEffTex::CEffTex()
{
    m_starGetAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x450029, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_starGetAnim);
    m_splashAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x450028, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_splashAnim);
    m_wakeAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002A, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_wakeAnim);
    m_yajiAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x450030, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_yajiAnim);
    m_ringAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002E, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_ringAnim);
}

CEffTex::~CEffTex()
{
    HuSprAnimKill(m_starGetAnim);
    HuSprAnimKill(m_splashAnim);
    HuSprAnimKill(m_wakeAnim);
    HuSprAnimKill(m_yajiAnim);
    HuSprAnimKill(m_ringAnim);
}

void CEffTex::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

void CEffTex::on_update() {}

void CBoatShadow::Hook(HU3DMODEL* model, Mtx* mtx)
{
    CBoatShadow* self = (CBoatShadow*)model->hookData;
    self->Draw(mtx);
}

CBoatShadow::CBoatShadow()
{
    HU3DMODELID id = Hu3DHookFuncCreate(Hook); /* (int) at every use: retail re-extends the raw id each time */
    HU3DMODEL* model = &Hu3DData[(int)id];
    model->hookData = this;
    m_model = (int)id;
    Hu3DModelLayerSet((int)id, 3);
    Hu3DModelCameraSet((int)id, 15);
    m_anim = HuSprAnimRead(HuDataSelHeapReadNum(0x45002D, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(m_anim);
}

CBoatShadow::~CBoatShadow()
{
    Hu3DModelKill(m_model);
    HuSprAnimKill(m_anim);
}

/* CPlayer::UpdateMain: the boat's position (the shadow 10 above it) and rotation */
void CBoatShadow::SetPos(Vec* pos, Vec* rot)
{
    m_pos = *pos;
    m_rot = *rot;
    m_pos.y += 10.0f;
}

/* a 160 x 360 quad (z -160..200) at m_pos, turned by rot.y; colour and alpha from the texture */
void CBoatShadow::Draw(Mtx* view)
{
    Mtx m;
    Mtx r;
    PSMTXTrans(m, m_pos.x, m_pos.y, m_pos.z);
    PSMTXRotRad(r, 'Y', 0.017453292f * m_rot.y);
    PSMTXConcat(m, r, m);
    PSMTXConcat(*view, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    HuSprTexLoad(m_anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZCompLoc(GX_TRUE);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-80.0f, 0.0f, -160.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXPosition3f32(-80.0f, 0.0f, 200.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(80.0f, 0.0f, 200.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(80.0f, 0.0f, -160.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXEnd();
}

} // namespace m511
