/*
 * storyresultdll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/storyresultdll/asm/REL/storyresultdll/effect.s.
 */

#include "REL/storyresultDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const double lbl_1_rodata_150 = 1.1111111111111112; /* 0x150 */
static const float lbl_1_rodata_158 = 0.0f; /* 0x158 */
/* 0x160 lbl_1_rodata_160 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_168 = 40.0f; /* 0x168 */
static const float lbl_1_rodata_16C = 480.0f; /* 0x16C */
static const float lbl_1_rodata_170 = 640.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 10.0f; /* 0x174 */
static const float lbl_1_rodata_178 = 1.0f; /* 0x178 */
static const float lbl_1_rodata_17C = 255.0f; /* 0x17C */
static const float lbl_1_rodata_180 = -100.0f; /* 0x180 */
static const double lbl_1_rodata_188 = 1.2000000476837158; /* 0x188 */
static const double lbl_1_rodata_190 = 10000.0; /* 0x190 */
static const float lbl_1_rodata_198 = 0.5f; /* 0x198 */
static const double lbl_1_rodata_1A0 = 0.8333333134651184; /* 0x1A0 */
static const float lbl_1_rodata_1A8 = -10000.0f; /* 0x1A8 */
/* 0x1AC lbl_1_rodata_1AC (0x4): 0x20, 0x20, 0x20, 0x80 -- an aggregate initialiser, write it as a local */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xB0 */ static void *ToueiFbCopyBuf;
/* 0xAC */ static void *RankGlowCopyBuf;
/* 0xA0 */ static HuVecF ToueiFbCopyPos;
/* 0x9C */ static s16 ToueiNo;
/* 0x98 */ float CapsuleGlowTPLvl;

static void ToueiFBCopy(s16 layerNo);
static void RankGlowHook(s16 layerNo);
static void ToueiMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x134 */ static char *ToueiCenterObj[15] = {
    "root_head",
    "root_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head",
    "ske_head"
};
/* 0x170 */ static float ToueiCenterOfsY[13] = { 15.0f, 18.0f, 12.0f, 20.0f, 15.0f, 6.0f, 15.0f, 20.0f, 10.0f, 15.0f, 15.0f, 15.0f, 15.0f };

/* 128 insns */
void ToueiDispInit(void)
{
    s16 charNo = GwPlayerConf[0].charNo;
    HuVecF pos3D;
    HuVecF pos2D;
    s16 posX, posY;
    ToueiFbCopyBuf = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(80, 80, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    Hu3DModelObjPosGet(CharMdlId, ToueiCenterObj[charNo], &pos3D);
    pos3D.y += ToueiCenterOfsY[charNo];
    Hu3D3Dto2D(&pos3D, HU3D_CAM0, &pos2D);
    posX = pos2D.x * (640.0 / 576.0);
    posY = pos2D.y;
    posX &= 0xFFFE;
    posY &= 0xFFFE;
    ToueiFbCopyPos.x = posX;
    ToueiFbCopyPos.y = posY;
    Hu3DModelMatHookSet(CapsuleMdlId, ToueiMatHook);
    RankGlowCopyBuf = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(640, 480, GX_TF_RGBA8, GX_FALSE, 0), HU_MEMNUM_OVL);
    Hu3DLayerHookSet(8, ToueiFBCopy);
    CapsuleGlowTPLvl = 0;
    Hu3DLayerHookSet(10, RankGlowHook);
}

/* 45 insns */
static void ToueiFBCopy(s16 layerNo)
{
    if(Hu3DCameraNo == 0) {
        Hu3DFbCopyExec(ToueiFbCopyPos.x - 40, ToueiFbCopyPos.y - 40, 80, 80, GX_TF_RGB565, GX_FALSE, ToueiFbCopyBuf);
        DispZClear();
        ToueiNo = 0;
    }
}

/* 293 insns */
static void RankGlowHook(s16 layerNo)
{
    GXColor color;
    HU3DCAMERA *cameraP = &Hu3DCamera[0];
    Mtx44 proj;
    Mtx modelview;
    if(Hu3DCameraNo == 1) {
        Hu3DFbCopyExec(0, 0, 640, 480, GX_TF_RGBA8, GX_FALSE, RankGlowCopyBuf);
        DispZClear();
    } else if(Hu3DCameraNo == 2) {
        MTXOrtho(proj, 0, 480, 0, 640, 0, 10);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        GXSetViewport(0, 0, 640, 480, 0, 1);
        GXSetScissor(0, 0, 640, 480);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        /* retail: only the alpha is set; r/g/b are uninitialised (unused by the TEV setup) */
        color.a = 255 * CapsuleGlowTPLvl;
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetNumTevStages(1);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetZCompLoc(GX_FALSE);
        MTXIdentity(modelview);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        Hu3DTexLoad(RankGlowCopyBuf, 640, 480, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE, GX_TEXMAP0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2f32(0, 0);
        GXTexCoord2f32(0, 0);
        GXPosition2f32(640, 0);
        GXTexCoord2f32(1, 0);
        GXPosition2f32(640, 480);
        GXTexCoord2f32(1, 1);
        GXPosition2f32(0, 480);
        GXTexCoord2f32(0, 1);
        GXEnd();
    }
}

/* 274 insns */
void DispZClear(void)
{
    HU3DCAMERA *cameraP = &Hu3DCamera[0];
    Mtx44 proj;
    Mtx modelview;
    Vec pos;
    Vec target;
    Vec up;
    GXColor color;
    float z;

    MTXPerspective(proj, cameraP->fov, cameraP->aspect, cameraP->near, cameraP->far);
    GXSetProjection(proj, GX_PERSPECTIVE);
    GXSetViewport(0, 0, 640, 480, 0, 1);
    GXSetScissor(0, 0, 640, 480);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    color.r = color.g = color.b = 0;
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetCullMode(GX_CULL_NONE);
    GXSetAlphaCompare(GX_GEQUAL, 0, GX_AOP_AND, GX_GEQUAL, 0);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_CLEAR);

    pos.x = pos.y = pos.z = 0;
    target.x = target.y = 0;
    target.z = -100;
    up.x = up.z = 0;
    up.y = 1;
    MTXLookAt(modelview, &pos, &up, &target);
    GXLoadPosMtxImm(modelview, GX_PNMTX0);
    pos.x = (10000 * -sin(cameraP->fov / 2)) * 1.2f;
    pos.y = 10000 * -sin(cameraP->fov / 2) * (1 / 1.2f);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-pos.x, -pos.y, -10000);
    GXPosition3f32(pos.x, -pos.y, -10000);
    GXPosition3f32(pos.x, pos.y, -10000);
    GXPosition3f32(-pos.x, pos.y, -10000);
    GXEnd();
}

/* 118 insns */
static void ToueiMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXTexObj texObj;
    GXColor color = { 32, 32, 32, 128 };
    HU3DCAMERA *cameraP = &Hu3DCamera[Hu3DCameraNo];
    GXInitTexObj(&texObj, ToueiFbCopyBuf, 80, 80, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    ToueiNo++;
}
