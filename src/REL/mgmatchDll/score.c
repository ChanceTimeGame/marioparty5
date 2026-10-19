/*
 * mgmatchDll score.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgmatchDll/asm/REL/mgmatchDll/score.s.
 */

#include "REL/mgmatchDll.h"

/* Retail mg* units call the audio API unprototyped (mgtour/mgwars): keep game/audio.h out of
 * the CW build; the host keeps its prototypes. */
#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#include "msm_grp.h"
#include "msm_se.h"
#include "msm_stream.h"
#endif

#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_220 = 0.0f; /* 0x220 */
static const float lbl_1_rodata_224 = 42.0f; /* 0x224 */
static const float lbl_1_rodata_228 = 1.0f; /* 0x228 */
static const float lbl_1_rodata_22C = 60.0f; /* 0x22C */
static const double lbl_1_rodata_230 = 3.141592653589793; /* 0x230 */
static const double lbl_1_rodata_238 = 0.5; /* 0x238 */
static const float lbl_1_rodata_240 = 45.0f; /* 0x240 */
static const float lbl_1_rodata_244 = 40.0f; /* 0x244 */
static const float lbl_1_rodata_248 = 120.0f; /* 0x248 */
static const double lbl_1_rodata_250 = 2.0; /* 0x250 */
static const float lbl_1_rodata_258 = 30.0f; /* 0x258 */
static const float lbl_1_rodata_25C = 10.0f; /* 0x25C */
/* 0x260 lbl_1_rodata_260 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_268 = 288.0f; /* 0x268 */
static const float lbl_1_rodata_26C = 21.0f; /* 0x26C */
static const float lbl_1_rodata_270 = -160.0f; /* 0x270 */
static const float lbl_1_rodata_274 = 72.0f; /* 0x274 */
static const float lbl_1_rodata_278 = 0.5f; /* 0x278 */
static const float lbl_1_rodata_27C = 23.0f; /* 0x27C */
static const float lbl_1_rodata_280 = 54.0f; /* 0x280 */
static const float lbl_1_rodata_284 = 550.0f; /* 0x284 */
/* 0x288 lbl_1_rodata_288 (0x1C): 0x00000498 0x00000499 0x0000049A 0x0000049B 0x0000049C 0x0000049E 0x0000049F -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_2A4 = 0.01f; /* 0x2A4 */
static const float lbl_1_rodata_2A8 = 0.8f; /* 0x2A8 */
static const float lbl_1_rodata_2AC = 0.45f; /* 0x2AC */
static const float lbl_1_rodata_2B0 = 0.9f; /* 0x2B0 */
static const float lbl_1_rodata_2B4 = 20.0f; /* 0x2B4 */
static const double lbl_1_rodata_2B8 = 0.7; /* 0x2B8 */
static const float lbl_1_rodata_2C0 = 180.0f; /* 0x2C0 */
static const double lbl_1_rodata_2C8 = 0.05000000074505806; /* 0x2C8 */
static const double lbl_1_rodata_2D0 = 180.0; /* 0x2D0 */
static const float lbl_1_rodata_2D8 = 3.0f; /* 0x2D8 */
static const double lbl_1_rodata_2E0 = 360.0; /* 0x2E0 */
static const double lbl_1_rodata_2E8 = 1.1111111111111112; /* 0x2E8 */
static const float lbl_1_rodata_2F0 = 5.0f; /* 0x2F0 */
static const float lbl_1_rodata_2F4 = 15000.0f; /* 0x2F4 */
static const float lbl_1_rodata_2F8 = 1.2f; /* 0x2F8 */
static const float lbl_1_rodata_2FC = 640.0f; /* 0x2FC */
static const float lbl_1_rodata_300 = 480.0f; /* 0x300 */
static const float lbl_1_rodata_304 = 100.0f; /* 0x304 */
static const float lbl_1_rodata_308 = 8000.0f; /* 0x308 */
static const float lbl_1_rodata_30C = 160.0f; /* 0x30C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xEC0 */ MGMATCH_SCOREGRP lbl_1_bss_EC0;
/* 0xE74 */ MGMATCH_SCOREWORK lbl_1_bss_E74;
/* 0xE68 */ s16 lbl_1_bss_E68[6];
/* 0xE38 */ HuVecF lbl_1_bss_E38[4];

/* --- functions (reference order), .data placed before its first user --- */
/* 0x6C8 */ MGMATCH_VEC2 lbl_1_data_6C8[3][4] = { { { -138.0f, -39.0f }, { -138.0f, 3.0f }, { -138.0f, 45.0f }, { -138.0f, 87.0f } }, { { -96.0f, -39.0f }, { -96.0f, 3.0f }, { -96.0f, 45.0f }, { -96.0f, 87.0f } }, { { -54.0f, -39.0f }, { -54.0f, 3.0f }, { -54.0f, 45.0f }, { -54.0f, 87.0f } } }; /* [winsNeeded idx][player] (fn_1_12404) */
/* 0x728 */ MGMATCH_VEC2 lbl_1_data_728[3][8] = { /* [SCOREGRP.unk40][base + no]; struct-copied in fn_1_12404 */ { { -96.0f, -39.0f }, { -96.0f, 3.0f }, { -96.0f, 45.0f }, { -96.0f, 87.0f }, { -96.0f, -18.0f }, { -96.0f, 66.0f }, { -96.0f, -39.0f }, { -96.0f, 45.0f } }, { { -54.0f, -39.0f }, { -54.0f, 3.0f }, { -54.0f, 45.0f }, { -54.0f, 87.0f }, { -54.0f, -18.0f }, { -54.0f, 66.0f }, { -54.0f, -39.0f }, { -54.0f, 45.0f } }, { { -12.0f, -39.0f }, { -12.0f, 3.0f }, { -12.0f, 45.0f }, { -12.0f, 87.0f }, { -12.0f, -18.0f }, { -12.0f, 66.0f }, { -12.0f, -39.0f }, { -12.0f, 45.0f } } };
/* 0x7E8 */ u32 lbl_1_data_7E8[10] = { DATANUM(DATA_mgmatch, 64), DATANUM(DATA_mgmatch, 65), DATANUM(DATA_mgmatch, 66), DATANUM(DATA_mgmatch, 67), DATANUM(DATA_mgmatch, 68), DATANUM(DATA_mgmatch, 69), DATANUM(DATA_mgmatch, 70), DATANUM(DATA_mgmatch, 71), DATANUM(DATA_mgmatch, 72), DATANUM(DATA_mgmatch, 73) };
/* 0x810 */ u32 lbl_1_data_810[3][3] = { { DATANUM(DATA_mgmatch, 32), DATANUM(DATA_mgmatch, 33), DATANUM(DATA_mgmatch, 34) }, { DATANUM(DATA_mgmatch, 35), DATANUM(DATA_mgmatch, 36), DATANUM(DATA_mgmatch, 37) }, { DATANUM(DATA_mgmatch, 38), DATANUM(DATA_mgmatch, 39), DATANUM(DATA_mgmatch, 40) } }; /* [gameType][winsNeeded idx] (fn_1_12404) */
/* 0x834 */ MGMATCH_VEC2 lbl_1_data_834[2] = { { 288.0f, 600.0f }, { 288.0f, 150.0f } }; /* [0] struct-copied to lbl_1_bss_EC0.pos (fn_1_12934) */
/* 0x844 */ HuVecF lbl_1_data_844[3][2][2] = { /* [unk40][mdl][0 = off-screen, 1 = on-screen] (fn_1_12404 / fn_1_12B60) */ { { { -600.0f, -630.0f, -500.0f }, { -665.0f, 800.0f, -500.0f } }, { { 600.0f, -630.0f, -500.0f }, { 665.0f, 800.0f, -500.0f } } }, { { { -478.0f, -630.0f, -500.0f }, { -528.7999877929688f, 800.0f, -500.0f } }, { { 478.0f, -630.0f, -500.0f }, { 528.7999877929688f, 800.0f, -500.0f } } }, { { { -356.1000061035156f, -630.0f, -500.0f }, { -400.0f, 800.0f, -500.0f } }, { { 356.1000061035156f, -630.0f, -500.0f }, { 400.0f, 800.0f, -500.0f } } } };
/* 0x8D4 */ u32 lbl_1_data_8D4[3][2][3] = { /* model DATANUMs (0 = none); [type][mode != 0][winsNeeded 7/5/3] (fn_1_13C1C) */ { { DATANUM(DATA_mgmatch, 41), DATANUM(DATA_mgmatch, 42), DATANUM(DATA_mgmatch, 43) }, { 0x0, 0x0, 0x0 } }, { { DATANUM(DATA_mgmatch, 44), DATANUM(DATA_mgmatch, 46), DATANUM(DATA_mgmatch, 48) }, { DATANUM(DATA_mgmatch, 45), DATANUM(DATA_mgmatch, 47), DATANUM(DATA_mgmatch, 49) } }, { { DATANUM(DATA_mgmatch, 50), DATANUM(DATA_mgmatch, 52), DATANUM(DATA_mgmatch, 54) }, { DATANUM(DATA_mgmatch, 51), DATANUM(DATA_mgmatch, 53), DATANUM(DATA_mgmatch, 55) } } };
/* 0x91C */ MGMATCH_VEC2 lbl_1_data_91C[54] = { /* struct-copied (lwz only); indexed with strides 0x50 / 8 */ { -96.0f, -81.0f }, { -96.0f, -27.0f }, { -96.0f, 27.0f }, { -96.0f, 81.0f }, { -96.0f, -54.0f }, { -96.0f, 54.0f }, { -96.0f, -81.0f }, { -96.0f, 27.0f }, { -96.0f, -27.0f }, { -96.0f, 81.0f }, { -42.0f, -81.0f }, { -42.0f, -27.0f }, { -42.0f, 27.0f }, { -42.0f, 81.0f }, { -42.0f, -54.0f }, { -42.0f, 54.0f }, { -42.0f, -81.0f }, { -42.0f, 27.0f }, { -42.0f, -27.0f }, { -42.0f, 81.0f }, { 12.0f, -81.0f }, { 12.0f, -27.0f }, { 12.0f, 27.0f }, { 12.0f, 81.0f }, { 12.0f, -54.0f }, { 12.0f, 54.0f }, { 12.0f, -81.0f }, { 12.0f, 27.0f }, { 12.0f, -27.0f }, { 12.0f, 81.0f }, { -150.0f, -81.0f }, { -150.0f, -27.0f }, { -150.0f, 27.0f }, { -150.0f, 81.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { -96.0f, -81.0f }, { -96.0f, -27.0f }, { -96.0f, 27.0f }, { -96.0f, 81.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { -42.0f, -81.0f }, { -42.0f, -27.0f }, { -42.0f, 27.0f }, { -42.0f, 81.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f } };
/* 0xACC */ MGMATCH_VEC2 lbl_1_data_ACC[3][10] = { /* struct-copied (lwz only); stride 0x50 / 8 */ { { -217.0f, -81.0f }, { -217.0f, -27.0f }, { -217.0f, 27.0f }, { -217.0f, 81.0f }, { -217.0f, -54.0f }, { -217.0f, 54.0f }, { -217.0f, -81.0f }, { -217.0f, 27.0f }, { -217.0f, -27.0f }, { -217.0f, 81.0f } }, { { -163.0f, -81.0f }, { -163.0f, -27.0f }, { -163.0f, 27.0f }, { -163.0f, 81.0f }, { -163.0f, -54.0f }, { -163.0f, 54.0f }, { -163.0f, -81.0f }, { -163.0f, 27.0f }, { -163.0f, -27.0f }, { -163.0f, 81.0f } }, { { -109.0f, -81.0f }, { -109.0f, -27.0f }, { -109.0f, 27.0f }, { -109.0f, 81.0f }, { -109.0f, -54.0f }, { -109.0f, 54.0f }, { -109.0f, -81.0f }, { -109.0f, 27.0f }, { -109.0f, -27.0f }, { -109.0f, 81.0f } } };
/* 0xBBC */ MGMATCH_VEC2 lbl_1_data_BBC[3][4] = { /* [winsNeeded 7/5/3][i]; fn_1_13C1C subtracts 23 from .y on first use */ { { -150.0f, -81.0f }, { -150.0f, -27.0f }, { -150.0f, 27.0f }, { -150.0f, 81.0f } }, { { -96.0f, -81.0f }, { -96.0f, -27.0f }, { -96.0f, 27.0f }, { -96.0f, 81.0f } }, { { -42.0f, -81.0f }, { -42.0f, -27.0f }, { -42.0f, 27.0f }, { -42.0f, 81.0f } } };
/* 0xC1C */ float lbl_1_data_C1C[4] = { 288.0f, 800.0f, 288.0f, 240.0f };
/* 0xC2C */ float lbl_1_data_C2C[4] = { 288.0f, 800.0f, 288.0f, 240.0f };
/* 0xC3C */ float lbl_1_data_C3C[4] = { 288.0f, 800.0f, 288.0f, 240.0f };
/* 0xC4C */ float lbl_1_data_C4C[15] = { 0.0f, 0.0f, 0.0f, -300.0f, 0.0f, 0.0f, -100.0f, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, 300.0f, 0.0f, 0.0f };
/* 0xC9C */ char *lbl_1_data_C9C[15] = {
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
/* 0xCD8 */ float lbl_1_data_CD8[13] = { 15.0f, 18.0f, 12.0f, 20.0f, 15.0f, 6.0f, 0.0f, 20.0f, 90.0f, 15.0f, 15.0f, 15.0f, 15.0f };
/* 0xD0C */ float lbl_1_data_D0C[62] = { -300.0f, 400.0f, 0.0f, -295.0f, 290.0f, 0.0f, -290.0f, 185.0f, 0.0f, -285.0f, 85.0f, 0.0f, -190.0f, 400.0f, 0.0f, -187.0f, 290.0f, 0.0f, -185.0f, 185.0f, 0.0f, -183.0f, 84.0f, 0.0f, -87.0f, 400.0f, 0.0f, -86.0f, 290.0f, 0.0f, -85.0f, 185.0f, 0.0f, -84.0f, 84.0f, 0.0f, -35.0f, -35.0f, -35.0f, -45.0f, -50.0f, -35.0f, -40.0f, -35.0f, -60.0f, -80.0f, -80.0f, -80.0f, -80.0f, 550.0f, 600.0f, 500.0f, 600.0f, 700.0f, 550.0f, 500.0f, 600.0f, 900.0f, 800.0f, 800.0f, 800.0f, 800.0f };
/* 0xE04 */ u32 lbl_1_data_E04[2] = { DATANUM(DATA_mgmatch, 5), DATANUM(DATA_mgmatch, 6) };

/* 332 insns */
void fn_1_12404(s16 gameType, s16 winsNeeded, MGMATCH_PLAYER *player, s8 *score, HU3DMODELID *mdlId)
{
    HuVecF mdlPos;
    MGMATCH_VEC2 pos;
    int i;
    HUSPRGRPID grpId;
    s32 idx;
    s32 cols;
    s32 rows;
    s32 j;
    ANIMDATA *anim;
    s32 type;
    s32 base;
    ANIMDATA *baseAnim;
    HU3DMOTID motId;
    HU3DMODELID modelId;
    s32 memberNo;
    switch (gameType) {
        case MGMATCH_GAMETYPE_4P:
            type = 0;
            rows = 4;
            base = 0;
            break;
        case MGMATCH_GAMETYPE_2VS2:
            type = 1;
            rows = 2;
            base = 4;
            break;
        case MGMATCH_GAMETYPE_1VS3:
            type = 2;
            rows = 2;
            base = 6;
            break;
    }
    switch (winsNeeded) {
        case 7:
            idx = 0;
            cols = 7;
            break;
        case 5:
            idx = 1;
            cols = 5;
            break;
        case 3:
            idx = 2;
            cols = 3;
            break;
    }
    lbl_1_bss_EC0.rows = rows;
    lbl_1_bss_EC0.cols = cols;
    lbl_1_bss_EC0.unk40 = idx;
    baseAnim = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_810[type][idx], HU_MEMNUM_OVL, HEAP_MODEL));
    grpId = HuSprGrpCreate(cols * rows + 5);
    lbl_1_bss_EC0.grpId = grpId;
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(baseAnim, 100, 0));
    for (i = 4; i--;) {
        anim = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_7E8[GwPlayerConf[player[i].no].charNo], HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, i + 1, HuSprCreate(anim, 50, 0));
        HuSprPosSet(grpId, i + 1, lbl_1_data_6C8[idx][i].x, lbl_1_data_6C8[idx][i].y);
        lbl_1_bss_EC0.unkC[i] = score[i];
    }
    for (i = rows; i--;) {
        pos = lbl_1_data_728[lbl_1_bss_EC0.unk40][base + i];
        for (j = 0; j < cols; j++, pos.x += 42.0f) {
            memberNo = i * lbl_1_bss_EC0.cols + j;
            memberNo += 5;
            anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 59), HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 10, 0));
            HuSprPosSet(grpId, memberNo, pos.x, pos.y);
            HuSprTPLvlSet(grpId, memberNo, 0.0f);
        }
    }
    HuSprGrpDrawNoSet(grpId, 64);
    HuSprExecLayerSet(64, 1);
    for (i = 0; i < cols * rows + 5; i++) {
        HuSprAttrSet(grpId, i, HUSPR_ATTR_NOANIM);
        HuSprScaleSet(grpId, i, 1.0f, 1.0f);
    }
    for (i = 2; i--;) {
        mdlPos = lbl_1_data_844[lbl_1_bss_EC0.unk40][i][0];
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 2), HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_EC0.mdl[i].mdlId = modelId;
        lbl_1_bss_EC0.mdl[i].pos = mdlPos;
        motId = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(lbl_1_data_E04[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DMotionSet(modelId, motId);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(modelId, 2);
        Hu3DModelCameraSet(modelId, HU3D_CAM4);
        Hu3DModelPosSet(modelId, mdlPos.x, mdlPos.y, mdlPos.z);
    }
    lbl_1_bss_EC0.mdlIdP = mdlId;
    fn_1_12934();
    lbl_1_bss_E74.unk6 = 0;
    HuPrcChildCreate(fn_1_12B60, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 108 insns */
void fn_1_12934(void)
{
    s32 i;
    s32 j;
    s32 memberNo;
    for (i = lbl_1_bss_EC0.rows; i--;) {
        for (j = lbl_1_bss_EC0.unkC[i]; j--;) {
            memberNo = i * lbl_1_bss_EC0.cols + j;
            memberNo += 5;
            HuSprTPLvlSet(lbl_1_bss_EC0.grpId, memberNo, 1.0f);
        }
    }
    HuSprGrpPosSet(lbl_1_bss_EC0.grpId, lbl_1_data_834[0].x, lbl_1_data_834[0].y);
    lbl_1_bss_EC0.pos = lbl_1_data_834[0];
    for (i = 0; i < lbl_1_bss_EC0.cols * lbl_1_bss_EC0.rows + 5; i++) {
        HuSprAttrSet(lbl_1_bss_EC0.grpId, i, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelAttrSet(lbl_1_bss_EC0.mdl[i].mdlId, HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_EC0.mode = 3;
    lbl_1_bss_EC0.time = 0;
    lbl_1_bss_EC0.unk41 = 0;
}

/* 9 insns */
void fn_1_12AE4(s32 mode)
{
    lbl_1_bss_EC0.mode = mode;
    lbl_1_bss_EC0.time = 0;
}

/* 17 insns */
s32 fn_1_12B08(void)
{
    switch (lbl_1_bss_EC0.mode) {
        case 1:
        case 2:
        case 4:
        case 5:
            return 0;
    }
    return 1;
}

/* 5 insns */
s32 fn_1_12B4C(void)
{
    return lbl_1_bss_EC0.unk41;
}

/* 854 insns */
void fn_1_12B60(void)
{
    HuVecF showDir[2];
    HuVecF hideDir[2];
    HuVecF mdlPos;
    MGMATCH_VEC2 showPos;
    MGMATCH_VEC2 hidePos;
    MGMATCH_VEC2 grpPos;
    s32 i;
    s32 k;
    s32 time;
    s32 frame;
    s32 winner;
    s32 n;
    s32 j;
    s32 memberNo;
    s32 num;
    s32 base;
    float s;
    float hs;
    float cs;
    float ss;
    float bob;
    float ofs;
    float scale;
    float fade;
    float showDy;
    float hideDy;

    frame = 0;
    while (TRUE) {
        switch (lbl_1_bss_EC0.mode) {
            case 1:
                showDy = lbl_1_data_834[1].y - lbl_1_data_834[0].y;
                switch (lbl_1_bss_EC0.time) {
                    case 0:
                        for (i = 0; i < lbl_1_bss_EC0.cols * lbl_1_bss_EC0.rows + 5; i++) {
                            HuSprAttrReset(lbl_1_bss_EC0.grpId, i, HUSPR_ATTR_DISPOFF);
                        }
                        for (i = 0; i < 2; i++) {
                            Hu3DModelAttrReset(lbl_1_bss_EC0.mdl[i].mdlId, HU3D_ATTR_DISPOFF);
                        }
                        time = 0;
                        lbl_1_bss_EC0.time = 1;
                        break;
                    case 1:
                        for (i = 2; i--;) {
                            PSVECSubtract(&lbl_1_data_844[lbl_1_bss_EC0.unk40][i][1], &lbl_1_data_844[lbl_1_bss_EC0.unk40][i][0], &showDir[i]);
                        }
                        if (time <= 60) {
                            s = time / 60.0f;
                            s = sin(M_PI * s / 2.0);
                            s = sin(M_PI * s / 2.0);
                            showPos = lbl_1_data_834[0];
                            showPos.y += showDy * s;
                            HuSprGrpPosSet(lbl_1_bss_EC0.grpId, showPos.x, showPos.y);
                            lbl_1_bss_EC0.pos = showPos;
                            for (i = 2; i--;) {
                                PSVECScale(&showDir[i], &lbl_1_bss_EC0.mdl[i].pos, s);
                                PSVECAdd(&lbl_1_data_844[lbl_1_bss_EC0.unk40][i][0], &lbl_1_bss_EC0.mdl[i].pos, &lbl_1_bss_EC0.mdl[i].pos);
                                Hu3DModelPosSet(lbl_1_bss_EC0.mdl[i].mdlId, lbl_1_bss_EC0.mdl[i].pos.x, lbl_1_bss_EC0.mdl[i].pos.y, lbl_1_bss_EC0.mdl[i].pos.z);
                            }
                            time++;
                        } else {
                            lbl_1_bss_EC0.time = 2;
                        }
                        break;
                    case 2:
                        lbl_1_bss_EC0.mode = 3;
                        lbl_1_bss_EC0.time = 0;
                        lbl_1_bss_EC0.unk41 = 1;
                        break;
                }
                break;
            case 2:
                hideDy = lbl_1_data_834[0].y - lbl_1_data_834[1].y;
                switch (lbl_1_bss_EC0.time) {
                    case 0:
                        time = 0;
                        lbl_1_bss_EC0.time = 1;
                        break;
                    case 1:
                        for (k = 2; k--;) {
                            PSVECSubtract(&lbl_1_data_844[lbl_1_bss_EC0.unk40][k][0], &lbl_1_data_844[lbl_1_bss_EC0.unk40][k][1], &hideDir[k]);
                        }
                        if (time <= 60) {
                            hs = time / 60.0f;
                            hs = cos(M_PI * hs / 2.0);
                            hs = cos(M_PI * hs / 2.0);
                            hidePos = lbl_1_data_834[1];
                            hidePos.y += hideDy * hs;
                            HuSprGrpPosSet(lbl_1_bss_EC0.grpId, hidePos.x, hidePos.y);
                            lbl_1_bss_EC0.pos = hidePos;
                            for (k = 2; k--;) {
                                PSVECScale(&hideDir[k], &lbl_1_bss_EC0.mdl[k].pos, hs);
                                PSVECAdd(&lbl_1_data_844[lbl_1_bss_EC0.unk40][k][1], &lbl_1_bss_EC0.mdl[k].pos, &lbl_1_bss_EC0.mdl[k].pos);
                                Hu3DModelPosSet(lbl_1_bss_EC0.mdl[k].mdlId, lbl_1_bss_EC0.mdl[k].pos.x, lbl_1_bss_EC0.mdl[k].pos.y, lbl_1_bss_EC0.mdl[k].pos.z);
                            }
                            time++;
                        } else {
                            lbl_1_bss_EC0.time = 2;
                        }
                        break;
                    case 2:
                        for (k = 0; k < lbl_1_bss_EC0.cols * lbl_1_bss_EC0.rows + 5; k++) {
                            HuSprAttrSet(lbl_1_bss_EC0.grpId, k, HUSPR_ATTR_DISPOFF);
                        }
                        for (k = 0; k < 2; k++) {
                            Hu3DModelAttrSet(lbl_1_bss_EC0.mdl[k].mdlId, HU3D_ATTR_DISPOFF);
                        }
                        lbl_1_bss_EC0.mode = 3;
                        lbl_1_bss_EC0.time = 0;
                        lbl_1_bss_EC0.unk41 = 0;
                        break;
                }
                break;
            case 3:
                break;
            case 4:
                winner = fn_1_588();
                num = lbl_1_bss_EC0.unkC[winner];
                memberNo = lbl_1_bss_EC0.cols * winner + num;
                memberNo += 5;
                switch (lbl_1_bss_EC0.time) {
                    case 0:
                        HuAudFXPlay(0x48F);
                        time = 0;
                        lbl_1_bss_EC0.time = 1;
                        break;
                    case 1:
                        if (time <= 45) {
                            cs = time / 45.0f;
                            ss = cs;
                            ss = sin(M_PI * ss / 2.0);
                            ss = sin(M_PI * ss / 2.0);
                            cs = cos(M_PI * cs / 2.0);
                            cs = cos(M_PI * cs / 2.0);
                            scale = 1.0f + 40.0f * (1.0f - ss);
                            HuSprTPLvlSet(lbl_1_bss_EC0.grpId, memberNo, cs);
                            HuSprScaleSet(lbl_1_bss_EC0.grpId, memberNo, scale, scale);
                            time++;
                        } else {
                            lbl_1_bss_EC0.time = 2;
                        }
                        break;
                    case 2:
                        switch (fn_1_59C()) {
                            case MGMATCH_GAMETYPE_4P:
                                fn_1_5D0(winner, 12);
                                break;
                            case MGMATCH_GAMETYPE_2VS2:
                                if (winner == 0) {
                                    fn_1_5D0(0, 12);
                                    fn_1_5D0(1, 12);
                                } else {
                                    fn_1_5D0(2, 12);
                                    fn_1_5D0(3, 12);
                                }
                                break;
                            case MGMATCH_GAMETYPE_1VS3:
                                if (winner == 0) {
                                    fn_1_5D0(0, 12);
                                } else {
                                    fn_1_5D0(1, 12);
                                    fn_1_5D0(2, 12);
                                    fn_1_5D0(3, 12);
                                }
                                break;
                        }
                        HuAudFXPlay(0x490);
                        lbl_1_bss_EC0.unkC[fn_1_588()]++;
                        lbl_1_bss_EC0.mode = 3;
                        lbl_1_bss_EC0.time = 0;
                        break;
                }
                break;
            case 5:
                base = lbl_1_bss_EC0.cols * fn_1_624() + 5;
                switch (lbl_1_bss_EC0.time) {
                    case 0:
                        time = 0;
                        lbl_1_bss_EC0.time = 1;
                        break;
                    case 1:
                        if (time <= 60.0f) {
                            fade = time / 60.0f;
                            for (n = lbl_1_bss_EC0.unkC[fn_1_624()]; n--;) {
                                Hu3DModelTPLvlSet(lbl_1_bss_EC0.mdlIdP[n + 9], fade);
                                HuSprTPLvlSet(lbl_1_bss_EC0.grpId, base + n, 1.0f - fade);
                            }
                            time++;
                        } else {
                            lbl_1_bss_EC0.mode = 3;
                            lbl_1_bss_EC0.time = 0;
                        }
                        break;
                }
                break;
        }
        bob = frame / 120.0f;
        bob = sin(2.0 * (M_PI * bob));
        ofs = 30.0f * bob;
        for (j = 2; j--;) {
            mdlPos = lbl_1_bss_EC0.mdl[j].pos;
            mdlPos.y += ofs;
            Hu3DModelPosSet(lbl_1_bss_EC0.mdl[j].mdlId, mdlPos.x, mdlPos.y, mdlPos.z);
        }
        ofs = 10.0f * bob;
        grpPos = lbl_1_bss_EC0.pos;
        grpPos.y -= ofs;
        HuSprGrpPosSet(lbl_1_bss_EC0.grpId, grpPos.x, grpPos.y);
        frame++;
        frame %= 120;
        HuPrcVSleep();
    }
}

/* 217 insns */
void fn_1_138B8(HuVecF *pos3D, HuVecF *scale, s32 no, s32 num, float size, s32 gameType, float z)
{
    HuVecF pos;
    HuVecF min;
    HuVecF max;
    s32 base;

    switch (gameType) {
        case 0:
            base = 0;
            break;
        case 2:
            base = 4;
            break;
        case 1:
            base = 6;
            break;
    }
    pos.x = 288.0f + (num * 42 + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].x);
    pos.y = lbl_1_data_834[1].y + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].y;
    pos.z = z;
    min.x = (288.0f + (num * 42 + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].x)) - 21.0f;
    min.y = (lbl_1_data_834[1].y + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].y) - 21.0f;
    min.z = z;
    max.x = 21.0f + (288.0f + (num * 42 + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].x));
    max.y = 21.0f + (lbl_1_data_834[1].y + lbl_1_data_728[lbl_1_bss_EC0.unk40][base + no].y);
    max.z = z;
    scale->x = (max.x - min.x) / size;
    scale->y = (max.y - min.y) / size;
    scale->z = 1.0f;
    Hu3D2Dto3D(&pos, HU3D_CAM4, pos3D);
}

/* 461 insns */
void fn_1_13C1C(s16 mode, s32 gameType, s32 winsNeeded, s32 *playerNo, s32 *charNo)
{
    MGMATCH_VEC2 pos;
    ANIMDATA *boardAnim;
    ANIMDATA *titleAnim;
    s32 mdlNo;
    s32 i;
    HUSPRGRPID boardGrpId;
    HUSPRGRPID titleGrpId;
    s32 j;
    HUSPRGRPID lampGrpId;
    ANIMDATA *animP;
    s32 winType;
    s32 winNum;
    s32 rows;
    s32 base;
    s32 memberNo;
    s32 type;
    s32 sub;

    if (mode != 0) {
        sub = 1;
    } else {
        sub = 0;
    }
    lbl_1_bss_E74.unk2C = gameType;
    lbl_1_bss_E74.unk2E = mode;
    switch (gameType) {
        case 0:
            type = 0;
            rows = 4;
            base = 0;
            sub = 0;
            break;
        case 2:
            type = 1;
            rows = 2;
            base = 4;
            break;
        case 1:
            type = 2;
            rows = 2;
            base = (mode != 0) ? 8 : 6;
            break;
    }
    switch (winsNeeded) {
        case 7:
            winType = 0;
            winNum = 7;
            break;
        case 5:
            winType = 1;
            winNum = 5;
            break;
        case 3:
            winType = 2;
            winNum = 3;
            break;
    }
    if (lbl_1_bss_E74.unk6 == 0) {
        lbl_1_bss_E74.unk6 = 1;
        titleAnim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 58), HU_MEMNUM_OVL, HEAP_MODEL));
        titleGrpId = HuSprGrpCreate(2);
        HuSprGrpMemberSet(titleGrpId, 0, HuSprCreate(titleAnim, 80, 0));
        HuSprPosSet(titleGrpId, 0, 0.0f, -160.0f);
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 76), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(titleGrpId, 1, HuSprCreate(animP, 127, 0));
        HuSprScaleSet(titleGrpId, 1, 72.0f, 60.0f);
        HuSprTPLvlSet(titleGrpId, 1, 0.5f);
        lampGrpId = HuSprGrpCreate(4);
        i = 4;
        while (i--) {
            lbl_1_data_BBC[winType][i].y -= 23.0f;
            pos = lbl_1_data_BBC[winType][i];
            animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 75), HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(lampGrpId, i, HuSprCreate(animP, 10, 0));
            HuSprPosSet(lampGrpId, i, pos.x, pos.y);
            HuSprAttrSet(lampGrpId, i, HUSPR_ATTR_DISPOFF);
            HuSprScaleSet(lampGrpId, i, 0.0f, 0.0f);
        }
        boardAnim = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_8D4[type][sub][winType], HU_MEMNUM_OVL, HEAP_MODEL));
        boardGrpId = HuSprGrpCreate(winNum * rows + 6);
        HuSprGrpMemberSet(boardGrpId, 0, HuSprCreate(boardAnim, 100, 0));
        i = rows;
        while (i--) {
            pos = lbl_1_data_ACC[winType][base + i];
            animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 56), HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(boardGrpId, i + 1, HuSprCreate(animP, 10, i));
            HuSprPosSet(boardGrpId, i + 1, pos.x, pos.y);
        }
        i = rows;
        while (i--) {
            pos = ((MGMATCH_VEC2(*)[10])lbl_1_data_91C)[winType][base + i];
            for (j = 0; j < winNum; j++, pos.x += 54.0f) {
                memberNo = i * winNum + (j + 6);
                animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 60), HU_MEMNUM_OVL, HEAP_MODEL));
                HuSprGrpMemberSet(boardGrpId, memberNo, HuSprCreate(animP, 10, 0));
                HuSprPosSet(boardGrpId, memberNo, pos.x, pos.y);
            }
        }
        HuSprGrpDrawNoSet(boardGrpId, 64);
        HuSprGrpDrawNoSet(titleGrpId, 64);
        HuSprGrpDrawNoSet(lampGrpId, 0);
        HuSprExecLayerCameraSet(64, HU3D_CAM4, 12);
        lbl_1_bss_E74.unk0 = boardGrpId;
        lbl_1_bss_E74.unk2 = titleGrpId;
        lbl_1_bss_E74.unk4 = lampGrpId;
    } else {
        boardGrpId = lbl_1_bss_E74.unk0;
        titleGrpId = lbl_1_bss_E74.unk2;
        lampGrpId = lbl_1_bss_E74.unk4;
    }
    HuSprGrpPosSet(boardGrpId, 550.0f + lbl_1_data_C1C[2], lbl_1_data_C1C[3]);
    HuSprGrpPosSet(titleGrpId, lbl_1_data_C2C[2], lbl_1_data_C2C[3]);
    HuSprGrpPosSet(lampGrpId, lbl_1_data_C3C[2], lbl_1_data_C3C[3]);
    i = 4;
    while (i--) {
        lbl_1_bss_E74.unk20[i] = playerNo[i];
    }
    i = rows;
    while (i--) {
        for (j = 0; j < winNum; j++) {
            memberNo = i * winNum + (j + 6);
            HuSprTPLvlSet(boardGrpId, memberNo, 0.0f);
        }
    }
    for (i = 0; i < 4; i++) {
        mdlNo = lbl_1_bss_EC0.mdlIdP[playerNo[i] + 26];
        lbl_1_bss_E74.charNo[i] = charNo[playerNo[i]];
        lbl_1_bss_E74.mdlId[i] = mdlNo;
    }
    fn_1_898(0x20000);
    fn_1_87C(0x400000);
    lbl_1_bss_E74.unk28 = 0;
    HuPrcChildCreate(fn_1_14350, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 0xE0C */ float lbl_1_data_E0C[2] = { 0.0f, -5.0f };

/* 1092 insns */
void fn_1_14350(void)
{
    float t200;
    float t101;
    float t300;
    float angle;
    float tpLvl;
    float t2;
    float wave;
    s32 i;
    s32 animId;
    s32 mdlId;
    s32 sprNo;
    s32 j;
    s32 mdlId2;
    HuVecF scale;
    HuVecF scale2;

    while (fn_1_8B4(0x400000)) {
        switch (lbl_1_bss_E74.unk28) {
            case 0:
                lbl_1_bss_E74.unk28 = 1;
                lbl_1_bss_E74.unk2A = 120;
                break;
            case 1:
                if (lbl_1_bss_E74.unk2A == 0) {
                    lbl_1_bss_E74.unk2A = 60;
                    lbl_1_bss_E74.unk28 = 2;
                }
                else {
                    lbl_1_bss_E74.unk2A--;
                }
                break;
            case 2:
                t2 = lbl_1_bss_E74.unk2A / 60.0f;
                t2 = sin(M_PI * t2 / 2.0);
                HuSprGrpPosSet(lbl_1_bss_E74.unk0, lbl_1_data_C1C[2] + 550.0f * t2, lbl_1_data_C1C[3]);
                if (lbl_1_bss_E74.unk2A == 0) {
                    lbl_1_bss_E74.unk28 = 100;
                }
                else {
                    lbl_1_bss_E74.unk2A--;
                }
                break;
            case 100:
                scale.x = 0.0f;
                scale.y = 0.0f;
                scale.z = 0.01f;
                i = 4;
                while (i--) {
                    mdlId = lbl_1_bss_EC0.mdlIdP[i + 30];
                    switch (lbl_1_bss_E74.unk2C) {
                        case 0:
                            if (i == 0) {
                                HuSprAttrReset(lbl_1_bss_E74.unk4, i, HUSPR_ATTR_DISPOFF);
                                animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 61), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                            }
                            else if (i == 1) {
                                animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 62), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                            }
                            else {
                                animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 63), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                            }
                            break;
                        case 2:
                            if (i <= 1) {
                                HuSprAttrReset(lbl_1_bss_E74.unk4, i, HUSPR_ATTR_DISPOFF);
                                animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 61), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                            }
                            else {
                                animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 63), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                            }
                            break;
                        case 1:
                            if (lbl_1_bss_E74.unk2E == 0) {
                                if (i == 0) {
                                    HuSprAttrReset(lbl_1_bss_E74.unk4, i, HUSPR_ATTR_DISPOFF);
                                    animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 61), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                    Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                                }
                                else {
                                    animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 63), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                    Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                                }
                            }
                            else {
                                if (i <= 2) {
                                    HuSprAttrReset(lbl_1_bss_E74.unk4, i, HUSPR_ATTR_DISPOFF);
                                    animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 61), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                    Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                                }
                                else {
                                    animId = Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 63), HU_MEMNUM_OVL, HEAP_MODEL), mdlId, "resrts_window");
                                    Hu3DAnimBankSet(animId, (u16)lbl_1_bss_E74.charNo[i]);
                                }
                            }
                            break;
                    }
                    Hu3DModelPosSetV(mdlId, &((HuVecF(*)[4])lbl_1_data_D0C)[lbl_1_bss_EC0.unk40][i]);
                    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelScaleSetV(mdlId, &scale);
                }
                i = 4;
                while (i--) {
                    mdlId = lbl_1_bss_EC0.mdlIdP[i + 30];
                    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                }
                HuAudFXPlay(0x497);
                lbl_1_bss_E74.unk28 = 101;
                lbl_1_bss_E74.unk2A = 0;
                lbl_1_bss_E74.unk34 = 0.8f;
                lbl_1_bss_E74.unk38 = M_PI - asinf(lbl_1_bss_E74.unk34);
                break;
            case 101:
                t101 = lbl_1_bss_E74.unk2A / 30.0f;
                t101 = sin(M_PI * t101 / 2.0);
                t101 = sin(t101 * lbl_1_bss_E74.unk38);
                t101 *= 1.0f / lbl_1_bss_E74.unk34;
                scale2.x = 0.45f * t101;
                scale2.y = 0.45f * t101;
                scale2.z = 0.01f;
                i = 4;
                while (i--) {
                    mdlId2 = lbl_1_bss_EC0.mdlIdP[i + 30];
                    Hu3DModelScaleSetV(mdlId2, &scale2);
                }
                if (lbl_1_bss_E74.unk2A >= 30.0f) {
                    lbl_1_bss_E74.unk28 = 102;
                    lbl_1_bss_E74.unk2A = 30;
                }
                else {
                    lbl_1_bss_E74.unk2A++;
                }
                break;
            case 102:
                if (lbl_1_bss_E74.unk2A == 0) {
                    lbl_1_bss_E74.unk34 = 0.9f;
                    lbl_1_bss_E74.unk38 = M_PI - asinf(lbl_1_bss_E74.unk34);
                    lbl_1_bss_E74.unk30 = 1;
                    lbl_1_bss_E74.unk2A = 0;
                    lbl_1_bss_E74.unk28 = 200;
                }
                else {
                    lbl_1_bss_E74.unk2A--;
                }
                break;
            case 200: {
                s32 seNo = lbl_1_bss_E74.unk30 - 1;
                s32 seTbl[] = { 0x498, 0x499, 0x49A, 0x49B, 0x49C, 0x49E, 0x49F };
                t200 = lbl_1_bss_E74.unk2A / 20.0f;
                t200 = sin(M_PI * t200 / 2.0);
                tpLvl = t200;
                t200 = sin(t200 * lbl_1_bss_E74.unk38);
                t200 *= 1.0f / lbl_1_bss_E74.unk34;
                switch (lbl_1_bss_E74.unk2C) {
                    case 0:
                        i = 4;
                        while (i--) {
                            if (lbl_1_bss_EC0.unkC[lbl_1_bss_E74.unk20[i]] >= lbl_1_bss_E74.unk30) {
                                sprNo = i * lbl_1_bss_EC0.cols + seNo;
                                sprNo += 6;
                                HuSprTPLvlSet(lbl_1_bss_E74.unk0, sprNo, tpLvl);
                                HuSprScaleSet(lbl_1_bss_E74.unk0, sprNo, t200, t200);
                            }
                        }
                        break;
                    case 1:
                    case 2:
                        if (lbl_1_bss_E74.unk2E != 0) {
                            if (lbl_1_bss_EC0.unkC[0] >= lbl_1_bss_E74.unk30) {
                                sprNo = lbl_1_bss_EC0.cols + seNo;
                                sprNo += 6;
                                HuSprTPLvlSet(lbl_1_bss_E74.unk0, sprNo, tpLvl);
                                HuSprScaleSet(lbl_1_bss_E74.unk0, sprNo, t200, t200);
                            }
                            if (lbl_1_bss_EC0.unkC[1] >= lbl_1_bss_E74.unk30) {
                                sprNo = seNo + 6;
                                HuSprTPLvlSet(lbl_1_bss_E74.unk0, sprNo, tpLvl);
                                HuSprScaleSet(lbl_1_bss_E74.unk0, sprNo, t200, t200);
                            }
                        }
                        else {
                            if (lbl_1_bss_EC0.unkC[0] >= lbl_1_bss_E74.unk30) {
                                sprNo = seNo + 6;
                                HuSprTPLvlSet(lbl_1_bss_E74.unk0, sprNo, tpLvl);
                                HuSprScaleSet(lbl_1_bss_E74.unk0, sprNo, t200, t200);
                            }
                            if (lbl_1_bss_EC0.unkC[1] >= lbl_1_bss_E74.unk30) {
                                sprNo = lbl_1_bss_EC0.cols + seNo;
                                sprNo += 6;
                                HuSprTPLvlSet(lbl_1_bss_E74.unk0, sprNo, tpLvl);
                                HuSprScaleSet(lbl_1_bss_E74.unk0, sprNo, t200, t200);
                            }
                        }
                        break;
                }
                if (lbl_1_bss_E74.unk2A == 0) {
                    HuAudFXPlay(seTbl[seNo]);
                }
                if (lbl_1_bss_E74.unk2A >= 20.0f) {
                    OSReport("\203X\203R\203A %d \225\216\246\n", lbl_1_bss_E74.unk30);
                    if (lbl_1_bss_E74.unk30 == lbl_1_bss_EC0.cols) {
                        HuAudFXPlay(0x4A0);
                        lbl_1_bss_E74.unk28 = 300;
                        lbl_1_bss_E74.unk2A = 0;
                        lbl_1_bss_E74.unk34 = 0.8f;
                        lbl_1_bss_E74.unk38 = M_PI - asinf(lbl_1_bss_E74.unk34);
                    }
                    else {
                        lbl_1_bss_E74.unk2A = 0;
                    }
                    lbl_1_bss_E74.unk30++;
                }
                else {
                    lbl_1_bss_E74.unk2A++;
                }
                break;
            }
            case 300:
                t300 = lbl_1_bss_E74.unk2A / 30.0f;
                t300 = sin(M_PI * t300 / 2.0);
                t300 = sin(t300 * lbl_1_bss_E74.unk38);
                t300 *= 1.0f / lbl_1_bss_E74.unk34;
                i = 4;
                while (i--) {
                    HuSprScaleSet(lbl_1_bss_E74.unk4, i, 0.7 * t300, 0.7 * t300);
                }
                if (lbl_1_bss_E74.unk2A >= 30.0f) {
                    angle = 180.0f;
                    lbl_1_bss_E74.unk28 = 301;
                    fn_1_87C(0x20000);
                }
                else {
                    lbl_1_bss_E74.unk2A++;
                }
                break;
            case 301:
                wave = 0.05f * sin(M_PI * angle / 180.0);
                angle += 3.0f;
                angle = fmodf(angle, 360.0f);
                j = 4;
                while (j--) {
                    HuSprScaleSet(lbl_1_bss_E74.unk4, j, 0.7 + wave, 0.7 + wave);
                }
                break;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 140 insns */
void fn_1_15460(s16 layerNo)
{
    HuVecF pos3D;
    HuVecF pos2D;
    s32 i;
    s16 x;
    s16 y;

    if (Hu3DCameraBit == HU3D_CAM0) {
        for (i = 0; i < 4; i++) {
            Hu3DModelObjPosGet(lbl_1_bss_E74.mdlId[i], lbl_1_data_C9C[lbl_1_bss_E74.charNo[i]], &pos3D);
            pos3D.y += lbl_1_data_CD8[lbl_1_bss_E74.charNo[i]];
            Hu3D3Dto2D(&pos3D, HU3D_CAM0, &pos2D);
            x = pos2D.x * 1.1111111111111112;
            y = pos2D.y;
            x &= 0xFFFE;
            y &= 0xFFFE;
            lbl_1_bss_E38[i].x = x;
            lbl_1_bss_E38[i].y = y;
            Hu3DFbCopyExec(lbl_1_bss_E38[i].x - 40.0f, lbl_1_bss_E38[i].y - 40.0f, 80, 80, GX_TF_RGB5A3, FALSE, lbl_1_bss_E74.fbAnim[i]->bmp->data);
        }
        Hu3DZClear();
    }
}

/* 334 insns */
void fn_1_15690(s32 mode, s32 *playerNo, s32 *charNo)
{
    HuVecF pos3D;
    HuVecF pos2D;
    HuVecF scale;
    s32 i;
    HU3DMODELID mdlId;
    s32 cameraBit;
    s16 x;
    s16 y;

    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 24), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DModelCameraSet(mdlId, HU3D_CAM0);
    Hu3DModelPosSet(mdlId, lbl_1_data_C4C[0], lbl_1_data_C4C[1], lbl_1_data_C4C[2]);
    cameraBit = HU3D_CAM0;
    Hu3DCameraCreate(cameraBit);
    Hu3DCameraPerspectiveSet(cameraBit, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(cameraBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(cameraBit, 0, 0, 640, 480);
    Hu3DCameraPosSet(cameraBit, 0.0f, 100.0f, 8000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f);
    for (i = 0; i < 4; i++) {
        mdlId = lbl_1_bss_EC0.mdlIdP[playerNo[i] + 26];
        Hu3DModelPosSet(mdlId, i * 150 - 300, 0.0f, 0.0f);
        Hu3DModelLayerSet(mdlId, 3);
        Hu3DModelCameraSet(mdlId, cameraBit);
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_E74.charNo[i] = charNo[playerNo[i]];
        lbl_1_bss_E74.mdlId[i] = mdlId;
        Hu3DModelObjPosGet(mdlId, lbl_1_data_C9C[charNo[playerNo[i]]], &pos3D);
        pos3D.y += lbl_1_data_CD8[charNo[playerNo[i]]];
        Hu3D3Dto2D(&pos3D, cameraBit, &pos2D);
        x = pos2D.x * 1.1111111111111112;
        y = pos2D.y;
        x &= 0xFFFE;
        y &= 0xFFFE;
        lbl_1_bss_E38[i].x = x;
        lbl_1_bss_E38[i].y = y;
        lbl_1_bss_E74.fbAnim[i] = HuSprAnimMake(80, 80, ANIM_BMP_RGB5A3);
        lbl_1_bss_E74.fbAnim[i]->bmp->data = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_E74.fbAnim[i]->bmp->dataSize, HU_MEMNUM_OVL);
        memset(lbl_1_bss_E74.fbAnim[i]->bmp->data, 0, lbl_1_bss_E74.fbAnim[i]->bmp->dataSize);
    }
    Hu3DLayerHookSet(6, fn_1_15460);
    HuPrcVSleep();
    scale.x = 0.45f;
    scale.y = 0.45f;
    scale.z = 0.01f;
    i = 4;
    while (i--) {
        mdlId = lbl_1_bss_EC0.mdlIdP[i + 30];
        Hu3DModelPosSetV(mdlId, &((HuVecF(*)[4])lbl_1_data_D0C)[mode][i]);
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DAnimCreate(lbl_1_bss_E74.fbAnim[i], mdlId, "S3TC_touei");
        Hu3DModelScaleSetV(mdlId, &scale);
    }
}

/* 43 insns */
void fn_1_15BC8(void)
{
    if (lbl_1_bss_E74.unk6) {
        HuSprGrpPosSet(lbl_1_bss_E74.unk0, lbl_1_data_C1C[0], lbl_1_data_C1C[1]);
        HuSprGrpPosSet(lbl_1_bss_E74.unk2, lbl_1_data_C2C[0], lbl_1_data_C2C[1]);
        /* retail reads [2] / [1] here (the other two read [0] / [1]); the values are equal */
        HuSprGrpPosSet(lbl_1_bss_E74.unk4, lbl_1_data_C3C[2], lbl_1_data_C3C[1]);
    }
}

/* 81 insns */
void fn_1_15C74(MGMATCH_PLAYER *player)
{
    s32 grpId;
    s32 i;
    ANIMDATA *animP;
    s32 memberNo;

    grpId = HuSprGrpCreate(5);
    lbl_1_bss_E68[0] = grpId;
    animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 78), HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(animP, 10, 0));
    i = 4;
    while (i--) {
        animP = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_7E8[player[i].charNo], HU_MEMNUM_OVL, HEAP_MODEL));
        memberNo = i + 1;
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(animP, 10, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_E0C[0], lbl_1_data_E0C[1]);
        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpDrawNoSet(grpId, 0);
    HuSprGrpTPLvlSet(grpId, 0.0f);
}

/* 91 insns */
void fn_1_15DB8(MGMATCH_PLAYER *player, HuVecF *pos)
{
    HuVecF pos2D;
    ANIMDATA *animP;
    s32 i;
    s32 memberNo;

    if (player == 0 || pos == 0) {
        HuSprGrpTPLvlSet(lbl_1_bss_E68[0], 0.0f);
    } else {
        HuSprGrpTPLvlSet(lbl_1_bss_E68[0], 1.0f);
        pos2D = *pos;
        pos2D.y += 160.0f;
        Hu3D3Dto2D(&pos2D, HU3D_CAM4, &pos2D);
        HuSprGrpPosSet(lbl_1_bss_E68[0], pos2D.x, pos2D.y);
        i = 4;
        while (i--) {
            animP = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_7E8[player[i].charNo], HU_MEMNUM_OVL, HEAP_MODEL));
            memberNo = i + 1;
            HuSprAttrSet(lbl_1_bss_E68[0], memberNo, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrReset(lbl_1_bss_E68[0], player->no + 1, HUSPR_ATTR_DISPOFF);
    }
}

