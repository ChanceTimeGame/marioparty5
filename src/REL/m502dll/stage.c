/*
 * m502dll stage.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/stage.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/disp.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "string.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x88 */ /* float lbl_1_rodata_88 = 0.002f; */
/* 0x8C */ /* float lbl_1_rodata_8C = 0.0f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 300.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 622.5f; */
/* 0x98 */ /* float lbl_1_rodata_98 = -9300.0f; */
/* 0x9C */ /* float lbl_1_rodata_9C = -5.0f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 600.5f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 1.3f; */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 1.0f; */
/* 0xAC */ /* float lbl_1_rodata_AC = 0.01f; */
/* 0xB0 */ /* double lbl_1_rodata_B0 = 4503601774854144; */
/* 0xB8 */ /* u8 lbl_1_rodata_B8[1] = { 0x40 }; */
/* 0xB9 */ /* TODO lbl_1_rodata_B9 .rodata size=0x7 (2 entries): 0x40401800 0x00, 0x00, 0x00 */
/* 0xC0 */ /* double lbl_1_rodata_C0 = 0.125; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 0.25; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 1.3333334f; */
/* 0xD4 */ /* float lbl_1_rodata_D4 = 0.5f; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = -0.5f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 0.25f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 0.8f; */
/* 0xE4 */ /* s32 lbl_1_rodata_E4[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000001 }; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 6.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 0.003f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 3.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 1.2f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 1.1f; */
/* 0x108 */ /* float lbl_1_rodata_108 = 2.0f; */
/* 0x110 */ /* double lbl_1_rodata_110 = 300; */
/* 0x118 */ /* double lbl_1_rodata_118 = 1; */
/* 0x120 */ /* float lbl_1_rodata_120 = 5.0f; */
/* 0x124 */ /* float lbl_1_rodata_124 = 600.0f; */
/* 0x128 */ /* float lbl_1_rodata_128 = -9301.0f; */
/* 0x12C */ /* u8 lbl_1_rodata_12C[1] = { 0x60, 0x60, 0x60, 0x09 }; */
/* 0x130 */ /* double lbl_1_rodata_130 = 0.5; */

/* --- .data --- */
/* 0xB80 */ s16 lbl_1_data_B80[4] = { 0, 1, 2, 3 };  /* work models linked into stage->unk03C */
/* 0xB88 */ s16 lbl_1_data_B88[8] = { 4, 5, 6, 7, 8, 9, 10, 11 };  /* copied into stage->unk044 */
/* 0xB98 */ char lbl_1_data_B98[] = "model-hasira";
/* 0xBA5 */ char lbl_1_data_BA5[] = "model-kabe00";
/* 0xBB2 */ char lbl_1_data_BB2[] = "model-kabe01";
/* 0xBBF */ char lbl_1_data_BBF[] = "model-kabe02";
/* 0xBCC */ char lbl_1_data_BCC[] = "model-kabe04";
/* 0xBD9 */ char lbl_1_data_BD9[] = "model-yuka00";
/* 0xBE6 */ char lbl_1_data_BE6[] = "model-yuka01";
/* 0xBF3 */ char lbl_1_data_BF3[] = "model-yuka02";
/* 0xC00 */ char *lbl_1_data_C00[8] = { lbl_1_data_B98, lbl_1_data_BA5, lbl_1_data_BB2, lbl_1_data_BBF, lbl_1_data_BCC, lbl_1_data_BD9, lbl_1_data_BE6, lbl_1_data_BF3 };
/* 0xC20 */ float lbl_1_data_C20[2][3] = { { 0.03f, 0.0f, 0.0f }, { 0.0f, 0.04f, 0.0f } };  /* indirect texture matrix */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5044 */ s32 lbl_1_bss_5044;  /* fn_1_2E08 frame toggle, 0/1 */
/* 0x5040 */ float lbl_1_bss_5040;  /* fn_1_3390 scroll speed, set by fn_1_3380 */
/* 0x503C */ float lbl_1_bss_503C;  /* fn_1_3390 scroll */
/* 0x5038 */ float lbl_1_bss_5038;  /* fn_1_2878 horizontal scroll */

extern M502_WORK *lbl_1_data_0;  /* m502.c (fork A spells the definition) */
extern s32 lbl_1_data_B60[8];  /* camera.c: camera bits */

void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

/* --- functions (reference order) --- */
/* stage.c fn_1_21B8, 339 insns. Stage init: link this player's stage models. */
void fn_1_21B8(M502_STAGE *stage, s32 playerNo, M502_PLAYER *player)
{
    M502_WORKMODEL *res;
    s32 i;
    HU3DMODELID modelId;

    res = &player->unk000->unk01C;
    memset(stage, 0, sizeof(M502_STAGE));
    stage->unk000 = player;
    stage->unk038 = 0.002f;
    for (i = 0; i < 4; i++) {
        modelId = Hu3DModelLink(res->unk000[lbl_1_data_B80[i]]);
        stage->unk03C[i] = modelId;
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, lbl_1_data_B60[playerNo]);
        Hu3DModelLayerSet(modelId, 1);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 8; i++) {
        stage->unk044[i] = lbl_1_data_B88[i];
        stage->unk054[i] = lbl_1_data_C00[i];
    }
    for (i = 0; i < 5; i++) {
        stage->unk004[i] = Hu3DModelLink(res->unk000[i + 0x81]);
        Hu3DModelAttrSet(stage->unk004[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk004[i], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(stage->unk004[i], 300.0f * i - 622.5f, -9300.0f, -5.0f);
        Hu3DModelRotSet(stage->unk004[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(stage->unk004[i], lbl_1_data_B60[playerNo + 4]);
        Hu3DModelLayerSet(stage->unk004[i], 4);
        Hu3DModelMatHookSet(stage->unk004[i], fn_1_2878);
        Hu3DModelAttrReset(stage->unk004[i], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 3; i++) {
        stage->unk00E[i] = Hu3DModelLink(res->unk000[i + 0x86]);
        Hu3DModelAttrSet(stage->unk00E[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk00E[i], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(stage->unk00E[i], 300.0f * i - 600.5f, -9300.0f, -5.0f);
        Hu3DModelScaleSet(stage->unk00E[i], 1.3f, 0.0f, 1.0f);
        Hu3DModelRotSet(stage->unk00E[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(stage->unk00E[i], lbl_1_data_B60[playerNo + 4]);
        Hu3DModelLayerSet(stage->unk00E[i], 4);
    }
    stage->unk014 = res->unk000[playerNo + 0x89];
    Hu3DModelAttrSet(stage->unk014, HU3D_ATTR_DISPOFF);
    Hu3DMotionShapeSpeedSet(stage->unk014, 0.0f);
    Hu3DMotionShapeTimeSet(stage->unk014, 0.01f);
    Hu3DModelScaleSet(stage->unk014, 1.0f, 1.0f, 1.0f);
    Hu3DModelRotSet(stage->unk014, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(stage->unk014, lbl_1_data_B60[playerNo + 4]);
    Hu3DModelLayerSet(stage->unk014, 4);
}

/* stage.c fn_1_2704, 41 insns. Stage close. */
void fn_1_2704(M502_STAGE *stage)
{
    s32 i;
    HU3DMODELID modelId;

    for (i = 0; i < 5; i++) {
        Hu3DModelKill(stage->unk004[i]);
        stage->unk004[i] = 0;
    }
    for (i = 0; i < 4; i++) {
        modelId = stage->unk03C[i];
        Hu3DModelKill(modelId);
    }
    memset(stage, 0, sizeof(M502_STAGE));
}

/* stage.c fn_1_27A8, 1 insn. Stage frame: empty. */
void fn_1_27A8(M502_STAGE *stage)
{
}

/* stage.c fn_1_27AC, 51 insns. Layer-12 hook: copy the EFB into the work's 320x240 RGB565 texture. */
void fn_1_27AC(s16 layerNo)
{
    HU3DWATER *waterP = &Hu3DWaterData;
    s32 pause;

    if (!(Hu3DCameraBit & 8)) {
        return;
    }
    GXSetTexCopySrc(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT);
    GXSetTexCopyDst(HU_FB_WIDTH / 2, HU_FB_HEIGHT / 2, GX_TF_RGB565, GX_TRUE);
    GXCopyTex(lbl_1_data_0->unk01C.unk350, GX_FALSE);
    if ((pause = omPauseChk() + omUPauseFlag) == 0) {
        lbl_1_bss_5038 += 0.002f;
    }
}

/* stage.c fn_1_2878, 356 insns. Material hook of the unk004 models: projected framebuffer copy, warped. */
void fn_1_2878(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXColor color = { 0x40, 0x40, 0x40, 0x18 };
    s32 pause;
    GXTexObj texObj;
    Mtx trans;
    Mtx scale;
    Mtx mtx;
    Mtx proj;
    Mtx invCam;
    HU3DCAMERA *cameraP;
    M502_STAGE *stage;
    float transS;

    cameraP = &Hu3DCamera[Hu3DCameraNo];
    stage = &lbl_1_data_0->unk3A4[Hu3DCameraNo - 4].unkFD4;
    if ((pause = omPauseChk() + omUPauseFlag) == 0) {
        stage->unk034 += stage->unk038;
    }
    GXInitTexObj(&texObj, lbl_1_data_0->unk01C.unk350, HU_FB_WIDTH / 2, HU_FB_HEIGHT / 2, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    HuSprTexLoad(lbl_1_data_0->unk01C.unk354, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_data_0->unk01C.unk358, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    transS = 0.125 + 0.25 * (Hu3DCameraNo - 4);
    C_MTXLightPerspective(proj, cameraP->fov, 1.3333334f, 0.5f, -0.5f, transS, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, invCam);
    PSMTXConcat(invCam, drawObj->matrix, trans);
    PSMTXConcat(proj, Hu3DCameraMtx, mtx);
    PSMTXConcat(mtx, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(trans, lbl_1_bss_5038 / 2, stage->unk034 / 4, 0.0f);
    PSMTXScale(scale, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(scale, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, lbl_1_data_C20, -1);
}

/* stage.c fn_1_2E08, 292 insns. Grow this player's column (unk004[n]) and cycle the unk00E frames. */
void fn_1_2E08(M502_STAGE *stage, float speed)
{
    s32 frameTbl[4] = { 0, 1, 2, 1 };
    s32 n;

    n = stage->unk000->unkF58.unk060 + 1;
    switch (stage->unk018) {
        case 0:
            stage->unk028 = 1.0f;
            stage->unk02C = 1.0f;
            stage->unk030 = 0.0f;
            stage->unk024 = 0.0f;
            stage->unk018++;
            stage->unk01C = 0;
            lbl_1_bss_5044 = 0;
            Hu3DModelAttrReset(stage->unk00E[frameTbl[stage->unk01C]], HU3D_ATTR_DISPOFF);
            break;
        case 1:
            lbl_1_bss_5044 = (lbl_1_bss_5044 + 1) & 1;
            stage->unk02C += speed;
            if (stage->unk02C > 6.0f) {
                stage->unk02C = 6.0f;
                stage->unk018++;
            }
            stage->unk038 = 0.002f + 0.003f * (stage->unk02C - 1.0f);
            if (stage->unk02C < 3.0f) {
                stage->unk030 = 1.2f * (stage->unk02C - 1.0f) / 2;
            } else {
                stage->unk030 = 1.2f;
            }
            if (stage->unk02C > 1.0f) {
                stage->unk028 = 1.1f;
            }
            if (stage->unk02C > 2.0f) {
                stage->unk028 = 1.2f;
            }
            if (stage->unk02C > 3.0f) {
                stage->unk028 = 1.3f;
            }
            stage->unk024 = 300.0 * (stage->unk02C - 1.0);
            Hu3DModelPosSet(stage->unk004[n], 300.0f * n - 622.5f, -9300.0f + stage->unk024, 5.0f);
            Hu3DModelScaleSet(stage->unk004[n], stage->unk028, stage->unk02C, 1.0f);
            if (lbl_1_bss_5044 != 0) {
                Hu3DModelAttrSet(stage->unk00E[frameTbl[stage->unk01C]], HU3D_ATTR_DISPOFF);
                stage->unk01C = (stage->unk01C + 1) & 3;
                Hu3DModelAttrReset(stage->unk00E[frameTbl[stage->unk01C]], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelPosSet(stage->unk00E[frameTbl[stage->unk01C]], 300.0f * n - 600.0f, -9300.0f + stage->unk024 - 2.0f, 5.0f);
            Hu3DModelScaleSet(stage->unk00E[frameTbl[stage->unk01C]], 1.3f, stage->unk030, 1.0f);
            break;
        case 2:
            break;
    }
}

/* stage.c fn_1_3298, 58 insns. Show this player's shape-motion model and start it. */
void fn_1_3298(M502_STAGE *stage)
{
    s32 n;

    n = stage->unk000->unkF58.unk060 + 1;
    switch (stage->unk020) {
        case 0:
            Hu3DModelAttrReset(stage->unk014, HU3D_ATTR_DISPOFF);
            Hu3DMotionShapeSpeedSet(stage->unk014, 1.0f);
            Hu3DModelPosSet(stage->unk014, 300.0f * n - 600.0f, -9301.0f, 0.0f);
            stage->unk020++;
            break;
        case 1:
            break;
    }
}

/* stage.c fn_1_3380, 4 insns. Set fn_1_3390's scroll speed. */
void fn_1_3380(float speed)
{
    lbl_1_bss_5040 = speed;
}

/* stage.c fn_1_3390, 340 insns. Material hook (set by ending): projected framebuffer copy, vertical scroll. */
void fn_1_3390(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXColor color = { 0x60, 0x60, 0x60, 0x09 };
    s32 pause;
    GXTexObj texObj;
    Mtx trans;
    Mtx scale;
    Mtx mtx;
    Mtx proj;
    Mtx invCam;
    HU3DCAMERA *cameraP;
    float transS;

    cameraP = &Hu3DCamera[Hu3DCameraNo];
    if ((pause = omPauseChk() + omUPauseFlag) == 0) {
        lbl_1_bss_503C += lbl_1_bss_5040;
    }
    GXInitTexObj(&texObj, lbl_1_data_0->unk01C.unk350, HU_FB_WIDTH / 2, HU_FB_HEIGHT / 2, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    HuSprTexLoad(lbl_1_data_0->unk01C.unk354, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_data_0->unk01C.unk358, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    transS = 0.5 + (float)(Hu3DCameraNo - 4);
    C_MTXLightPerspective(proj, cameraP->fov, 1.3333334f, 0.5f, -0.5f, transS, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, invCam);
    PSMTXConcat(invCam, drawObj->matrix, trans);
    PSMTXConcat(proj, Hu3DCameraMtx, mtx);
    PSMTXConcat(mtx, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(trans, 0.0f, lbl_1_bss_503C, 0.0f);
    PSMTXScale(scale, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(scale, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, lbl_1_data_C20, -1);
}
