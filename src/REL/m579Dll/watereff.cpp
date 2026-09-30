#include "REL/m579Dll/watereff.h"

extern "C" {
/* exported, but its prototype is commented out in game/sprite.h (m537 effect.cpp precedent) */
void HuSprTexLoad(ANIMDATA* anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);
void GXSetVtxAttrFmtv(GXVtxFmt vtxfmt, GXVtxAttrFmtList* list);
}

namespace m579 {

/* the copy buffer's data pointer: retail reads the vector's data word directly (no at()); the void* return is
 * retail's extra return copy (ctor 148AC / LoadScreenTex 15168 masked 0) */
static inline void* CopyBufData(std::vector<char>& v)
{
#ifdef __MWERKS__
    return v.begin();
#else
    return v.data();
#endif
}

CWaterEff::CWaterEff() : CModel(Hook), m_copyBuf(GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0))
{
    m_bumpData = HuDataSelHeapReadNum(0x850012, HU_MEMNUM_OVL, HEAP_MODEL);
    m_waveAnim = HuSprAnimRead(HuDataSelHeapReadNum(0x850013, HU_MEMNUM_OVL, HEAP_MODEL));
    m_scrollA = 0.0f;
    m_scrollB = 0.0f;
    setHookData(this);
    setLayer(1);
    PSMTXIdentity(m_model);
    PSMTXIdentity(m_texMtxWave);
    PSMTXIdentity(m_texMtxBump);
    PSMTXIdentity(m_texMtxWave2);
    GXInitTexObj(&m_screenTex, CopyBufData(m_copyBuf), 320, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObj(&m_bumpTex, m_bumpData, 128, 128, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_TRUE);
    GXInitTexObjLOD(&m_bumpTex, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, 7.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
}

/* the copy buffer only: m_bumpData and m_waveAnim are never freed (retail) */
CWaterEff::~CWaterEff() {}

void CWaterEff::on_new_mode(int mode)
{
    m_execFlags &= ~(1 << mode);
}

/* camera 1's eye and far plane x 1.8 */
void CWaterEff::GetCamera(Vec* pos, float* far)
{
    Vec t;
    float u;
    Hu3DCameraPosGet(1, pos, &t, &t);
    Hu3DCameraPerspectiveGet(1, &u, &u, far);
    *far *= 1.8;
}

/* the disc follows the camera (scale 1.8 far, y -150); three texture matrices scroll at 10/7 and 10/17 a frame */
void CWaterEff::on_update()
{
    Vec pos;
    float far;
    GetCamera(&pos, &far);
    PSMTXScale(m_model, far, 1.0f, far);
    PSMTXTransApply(m_model, m_model, pos.x, -150.0f, pos.z);
    m_scrollA -= 1.4285715f;
    m_scrollB -= 0.5882353f;
    float s = far / 600.0f;
    PSMTXScale(m_texMtxWave, s, s, 1.0f);
    PSMTXTransApply(m_texMtxWave, m_texMtxWave, (pos.x - 0.5 * m_scrollA) / 600.0, (pos.z + 0.8 * m_scrollB) / 600.0,
                    0.0f);
    PSMTXScale(m_texMtxBump, s, s, 1.0f);
    PSMTXTransApply(m_texMtxBump, m_texMtxBump, (pos.x + m_scrollA) / 600.0f, (pos.z + m_scrollB) / 600.0f, 0.0f);
    PSMTXScale(m_texMtxWave2, s, s, 1.0f);
    PSMTXTransApply(m_texMtxWave2, m_texMtxWave2, pos.x / 600.0f, pos.z / 600.0f, 0.0f);
}

void CWaterEff::Hook(HU3DMODEL* model, Mtx* mtx)
{
    ((CWaterEff*)model->hookData)->Draw(mtx);
}

void CWaterEff::LoadScreenTex(GXTexMapID map, u32 texMtx, Mtx mv)
{
    Mtx m;
    float fovy;
    float u;
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(CopyBufData(m_copyBuf), GX_FALSE);
    GXPixModeSync();
    GXLoadTexObj(&m_screenTex, map);
    Hu3DCameraPerspectiveGet(1, &fovy, &u, &u);
    C_MTXLightPerspective(m, fovy, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXConcat(m, mv, m);
    GXLoadTexMtxImm(m, texMtx, GX_MTX3x4);
}

void CWaterEff::LoadBumpTex(GXTexMapID map, u32 texMtx)
{
    GXLoadTexObj(&m_bumpTex, map);
    GXLoadTexMtxImm(m_texMtxBump, texMtx, GX_MTX2x4);
}

void CWaterEff::LoadWaveTex(GXTexMapID map, u32 texMtx)
{
    HuSprTexLoad(m_waveAnim, 0, (s16)map, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXLoadTexMtxImm(m_texMtxWave2, texMtx, GX_MTX2x4);
}

/* `this` unused */
void CWaterEff::SetIndStage(GXIndTexStageID stage, GXTexMapID map, GXTexCoordID coord)
{
    GXSetIndTexOrder(stage, coord, map);
    GXSetIndTexCoordScale(stage, GX_ITS_1, GX_ITS_1);
}

void CWaterEff::Draw(Mtx* mtx)
{
    static const float s_indMtx[3][2][3] = {
        { { 0.01f, 0.0f, 0.0f }, { 0.0f, 0.01f, 0.0f } },
        { { 0.02f, 0.0f, 0.0f }, { 0.0f, 0.02f, 0.0f } },
        { { 0.03f, 0.0f, 0.0f }, { 0.0f, 0.03f, 0.0f } },
    };
    Mtx mv;
    PSMTXConcat(*mtx, m_model, mv);
    GXLoadPosMtxImm(mv, GX_PNMTX0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    LoadScreenTex(GX_TEXMAP0, GX_TEXMTX0, mv);
    LoadBumpTex(GX_TEXMAP1, GX_TEXMTX1);
    LoadWaveTex(GX_TEXMAP2, GX_TEXMTX2);
    GXLoadTexMtxImm(m_texMtxWave, GX_TEXMTX3, GX_MTX2x4);
    GXSetNumTexGens(4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX3, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD3, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX2, GX_FALSE, GX_PTIDENTITY);
    GXSetIndTexMtx(GX_ITM_0, (f32(*)[3])s_indMtx[0], 0);
    GXSetIndTexMtx(GX_ITM_1, (f32(*)[3])s_indMtx[1], 0);
    GXSetIndTexMtx(GX_ITM_2, (f32(*)[3])s_indMtx[2], 0);
    GXSetNumIndStages(2);
    SetIndStage(GX_INDTEXSTAGE0, GX_TEXMAP1, GX_TEXCOORD2);
    SetIndStage(GX_INDTEXSTAGE1, GX_TEXMAP2, GX_TEXCOORD3);
    GXColor k0 = { 0x3D, 0x3B, 0x1B, 0x29 };
    GXSetTevKColor(GX_KCOLOR0, k0);
    GXSetNumTevStages(4);
    /* 0: the screen copy warped by IND0 / ITM_0 */
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    /* 1: + K0 x the bump alpha (TC1 / MAP1) warped by IND1 / ITM_1 */
    GXSetTevIndWarp(GX_TEVSTAGE1, GX_INDTEXSTAGE1, GX_TRUE, GX_FALSE, GX_ITM_1);
    GXSetTevKColorSel(GX_TEVSTAGE1, GX_TEV_KCSEL_K0);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_KONST, GX_CC_TEXA, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    /* 2: lerp to the vertex colour by its alpha (the indirect state of stage 2 is left as it was: retail) */
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_CPREV, GX_CC_RASC, GX_CC_RASA, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    /* 3: + K0.a x the bump colour (TC2 / MAP1) warped by IND1 / ITM_2; alpha = K0.a */
    GXSetTevIndWarp(GX_TEVSTAGE3, GX_INDTEXSTAGE1, GX_TRUE, GX_FALSE, GX_ITM_2);
    GXSetTevKColorSel(GX_TEVSTAGE3, GX_TEV_KCSEL_K0_A);
    GXSetTevOrder(GX_TEVSTAGE3, GX_TEXCOORD2, GX_TEXMAP1, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE3, GX_CC_ZERO, GX_CC_KONST, GX_CC_TEXC, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE3, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE3, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_BACK);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 255, GX_AOP_OR, GX_ALWAYS, 255);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    DrawDisc();
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetTevDirect(GX_TEVSTAGE1);
    GXSetTevDirect(GX_TEVSTAGE2);
    GXSetTevDirect(GX_TEVSTAGE3);
    GXSetNumIndStages(0);
}

#define DISC_ALIGNED(decl) static const decl ATTRIBUTE_ALIGN(32)
void CWaterEff::DrawDisc()
{
    static const GXVtxDescList discDesc[] = {
        { GX_VA_POS, GX_INDEX8 },
        { GX_VA_CLR0, GX_INDEX8 },
        { GX_VA_TEX0, GX_INDEX8 },
        { GX_VA_NULL, GX_NONE },
    };
    static const GXVtxAttrFmtList discFmt[] = {
        { GX_VA_POS, GX_POS_XYZ, GX_S16, 14 },
        { GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA4, 0 },
        { GX_VA_TEX0, GX_TEX_ST, GX_S16, 14 },
        { GX_VA_NULL, GX_POS_XY, GX_U8, 0 },
    };
    DISC_ALIGNED(u8 discPos[32 * 6]) = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00,
        0xF9, 0x1F, 0x00, 0x00, 0x1F, 0x40, 0xF2, 0x91, 0x00, 0x00, 0x1D, 0x0A,
        0xEC, 0xA3, 0x00, 0x00, 0x19, 0x79, 0xE7, 0x9D, 0x00, 0x00, 0x14, 0xB7,
        0xE3, 0xBB, 0x00, 0x00, 0x0E, 0xFD, 0xE1, 0x2B, 0x00, 0x00, 0x08, 0x8F,
        0xE0, 0x0D, 0x00, 0x00, 0x01, 0xBB, 0xE0, 0x6C, 0x00, 0x00, 0xFA, 0xD3,
        0xE2, 0x46, 0x00, 0x00, 0xF4, 0x28, 0xE5, 0x84, 0x00, 0x00, 0xEE, 0x0B,
        0xE9, 0xFF, 0x00, 0x00, 0xE8, 0xC5, 0xEF, 0x81, 0x00, 0x00, 0xE4, 0x95,
        0xF5, 0xC9, 0x00, 0x00, 0xE1, 0xAD, 0xFC, 0x8B, 0x00, 0x00, 0xE0, 0x31,
        0x03, 0x75, 0x00, 0x00, 0xE0, 0x31, 0x0A, 0x37, 0x00, 0x00, 0xE1, 0xAD,
        0x10, 0x7F, 0x00, 0x00, 0xE4, 0x95, 0x16, 0x01, 0x00, 0x00, 0xE8, 0xC5,
        0x1A, 0x7C, 0x00, 0x00, 0xEE, 0x0B, 0x1D, 0xBA, 0x00, 0x00, 0xF4, 0x28,
        0x1F, 0x94, 0x00, 0x00, 0xFA, 0xD3, 0x1F, 0xF3, 0x00, 0x00, 0x01, 0xBB,
        0x1E, 0xD5, 0x00, 0x00, 0x08, 0x8F, 0x1C, 0x45, 0x00, 0x00, 0x0E, 0xFD,
        0x18, 0x63, 0x00, 0x00, 0x14, 0xB7, 0x13, 0x5D, 0x00, 0x00, 0x19, 0x79,
        0x0D, 0x6F, 0x00, 0x00, 0x1D, 0x0A, 0x06, 0xE1, 0x00, 0x00, 0x1F, 0x40,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    DISC_ALIGNED(u8 discColor[2 * 2]) = { 0x57, 0x42, 0x17, 0xFB };
    DISC_ALIGNED(u8 discTex[32 * 4]) = {
        0x20, 0x00, 0x20, 0x00, 0x20, 0x00, 0x40, 0x00, 0x19, 0x1E, 0x3F, 0x40, 0x12, 0x90, 0x3D, 0x0A,
        0x0C, 0xA2, 0x39, 0x79, 0x07, 0x9C, 0x34, 0xB7, 0x03, 0xBA, 0x2E, 0xFD, 0x01, 0x2A, 0x28, 0x8F,
        0x00, 0x0C, 0x21, 0xBB, 0x00, 0x6B, 0x1A, 0xD2, 0x02, 0x45, 0x14, 0x27, 0x05, 0x83, 0x0E, 0x0A,
        0x09, 0xFE, 0x08, 0xC4, 0x0F, 0x80, 0x04, 0x94, 0x15, 0xC8, 0x01, 0xAC, 0x1C, 0x8A, 0x00, 0x30,
        0x23, 0x75, 0x00, 0x30, 0x2A, 0x37, 0x01, 0xAC, 0x30, 0x7F, 0x04, 0x94, 0x36, 0x01, 0x08, 0xC4,
        0x3A, 0x7C, 0x0E, 0x0A, 0x3D, 0xBA, 0x14, 0x27, 0x3F, 0x94, 0x1A, 0xD2, 0x3F, 0xF3, 0x21, 0xBB,
        0x3E, 0xD5, 0x28, 0x8F, 0x3C, 0x45, 0x2E, 0xFD, 0x38, 0x63, 0x34, 0xB7, 0x33, 0x5D, 0x39, 0x79,
        0x2D, 0x6F, 0x3D, 0x0A, 0x26, 0xE1, 0x3F, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    DISC_ALIGNED(u8 discList[0x60]) = {
        0xA0, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x02, 0x01, 0x02, 0x03, 0x01, 0x03, 0x04,
        0x01, 0x04, 0x05, 0x01, 0x05, 0x06, 0x01, 0x06, 0x07, 0x01, 0x07, 0x08, 0x01, 0x08, 0x09, 0x01,
        0x09, 0x0A, 0x01, 0x0A, 0x0B, 0x01, 0x0B, 0x0C, 0x01, 0x0C, 0x0D, 0x01, 0x0D, 0x0E, 0x01, 0x0E,
        0x0F, 0x01, 0x0F, 0x10, 0x01, 0x10, 0x11, 0x01, 0x11, 0x12, 0x01, 0x12, 0x13, 0x01, 0x13, 0x14,
        0x01, 0x14, 0x15, 0x01, 0x15, 0x16, 0x01, 0x16, 0x17, 0x01, 0x17, 0x18, 0x01, 0x18, 0x19, 0x01,
        0x19, 0x1A, 0x01, 0x1A, 0x1B, 0x01, 0x1B, 0x1C, 0x01, 0x1C, 0x1D, 0x01, 0x1D, 0x01, 0x01, 0x01,
    };
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList*)discDesc);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList*)discFmt);
    GXSetArray(GX_VA_POS, discPos, 6);
    GXSetArray(GX_VA_CLR0, discColor, 2);
    GXSetArray(GX_VA_TEX0, discTex, 4);
    GXCallDisplayList((void*)discList, sizeof(discList));
}
#undef DISC_ALIGNED

} // namespace m579
