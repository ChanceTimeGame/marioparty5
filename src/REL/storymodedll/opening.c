/*
 * storymodedll opening.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/storymodedll/asm/REL/storymodedll/opening.s.
 */

#include "REL/storymodeDll.h"

/* Retail calls HuAudFXPlay/HuAudFXPanning/HuAudSStreamFadeOut/HuAudSStreamStatGet unprototyped (an `mr`
 * after the void calls; fork B, fn_1_2448). The host keeps the prototypes. */
#ifndef __MWERKS__
#include "game/audio.h"
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/sprite.h"
#ifndef __MWERKS__ /* Hu3D3Dto2D/Hu3D2Dto3D unprototyped in retail (storymodedll.gen.h) */
#include "game/hsfex.h"
#endif
#include "game/window.h"
#include "game/process.h"
#ifdef __MWERKS__
/* retail calls HuTHPSprCreateVol unprototyped (fn_1_13E8 passes volume 0 in r6, nothing in f1):
   hide only that prototype from CodeWarrior */
#define HuTHPSprCreateVol HuTHPSprCreateVol_hidden
#include "game/thpmain.h"
#undef HuTHPSprCreateVol
#else
#include "game/thpmain.h"
#endif
#include "math.h"

#include "REL/storymodedll/effect.c"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_A0 = 90.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 0.0f; /* 0xA4 */
/* 0xA8 lbl_1_rodata_A8 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0xB0 lbl_1_rodata_B0 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_BC = 60.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = -1.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 128.72514f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 1.991341f; /* 0xC8 */
static const float lbl_1_rodata_CC = 142.54988f; /* 0xCC */
static const float lbl_1_rodata_D0 = 170.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 480.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 10.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 120.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = 420.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 140.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 180.0f; /* 0xE8 */
static const double lbl_1_rodata_F0 = 3.141592653589793; /* 0xF0 */
static const double lbl_1_rodata_F8 = 180.0; /* 0xF8 */
static const float lbl_1_rodata_100 = 1550.0f; /* 0x100 */
static const float lbl_1_rodata_104 = 9.0f; /* 0x104 */
static const float lbl_1_rodata_108 = 12.0f; /* 0x108 */
static const float lbl_1_rodata_10C = 4.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 1.0f; /* 0x110 */
static const float lbl_1_rodata_114 = 5.0f; /* 0x114 */
static const float lbl_1_rodata_118 = 25.0f; /* 0x118 */
static const float lbl_1_rodata_11C = 384.0f; /* 0x11C */
static const float lbl_1_rodata_120 = 127.0f; /* 0x120 */
static const float lbl_1_rodata_124 = 0.05f; /* 0x124 */
static const float lbl_1_rodata_128 = 1024.0f; /* 0x128 */
static const float lbl_1_rodata_12C = 256.0f; /* 0x12C */
static const float lbl_1_rodata_130 = 0.5f; /* 0x130 */
static const float lbl_1_rodata_134 = 0.08f; /* 0x134 */
static const float lbl_1_rodata_138 = 0.025f; /* 0x138 */
static const float lbl_1_rodata_13C = 150.0f; /* 0x13C */
static const double lbl_1_rodata_140 = 300.0; /* 0x140 */
static const float lbl_1_rodata_148 = 616.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 0.03846154f; /* 0x14C */
static const float lbl_1_rodata_150 = 0.07692308f; /* 0x150 */
static const float lbl_1_rodata_154 = 0.115384616f; /* 0x154 */
static const float lbl_1_rodata_158 = 0.7f; /* 0x158 */
static const float lbl_1_rodata_15C = -60.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 0.6923077f; /* 0x160 */
static const float lbl_1_rodata_164 = -40.0f; /* 0x164 */
static const float lbl_1_rodata_168 = 20.0f; /* 0x168 */
static const float lbl_1_rodata_16C = 200.0f; /* 0x16C */
static const float lbl_1_rodata_170 = 0.8f; /* 0x170 */
static const float lbl_1_rodata_174 = 0.15384616f; /* 0x174 */
static const float lbl_1_rodata_178 = 0.30769232f; /* 0x178 */
static const float lbl_1_rodata_17C = 0.46153846f; /* 0x17C */
static const double lbl_1_rodata_180 = 420.0; /* 0x180 */
static const float lbl_1_rodata_188 = 30.0f; /* 0x188 */
static const float lbl_1_rodata_18C = 700.0f; /* 0x18C */
static const float lbl_1_rodata_190 = -90.0f; /* 0x190 */
static const float lbl_1_rodata_194 = 2.6153846f; /* 0x194 */
static const float lbl_1_rodata_198 = 340.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 0.1923077f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 42.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 0.23076923f; /* 0x1A4 */
static const double lbl_1_rodata_1A8 = 15.0; /* 0x1A8 */
static const double lbl_1_rodata_1B0 = -150.0; /* 0x1B0 */
static const double lbl_1_rodata_1B8 = 600.0; /* 0x1B8 */
static const double lbl_1_rodata_1C0 = 20.0; /* 0x1C0 */
static const double lbl_1_rodata_1C8 = 60.0; /* 0x1C8 */
static const float lbl_1_rodata_1D0 = -85.0f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 57.0f; /* 0x1D4 */
static const double lbl_1_rodata_1D8 = 288.0; /* 0x1D8 */
static const float lbl_1_rodata_1E0 = 1.3f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = 1.6f; /* 0x1E4 */
static const float lbl_1_rodata_1E8 = 160.0f; /* 0x1E8 */
static const float lbl_1_rodata_1EC = 0.9f; /* 0x1EC */
static const float lbl_1_rodata_1F0 = 45.0f; /* 0x1F0 */
static const double lbl_1_rodata_1F8 = -60.0; /* 0x1F8 */
static const float lbl_1_rodata_200 = 0.01f; /* 0x200 */
static const float lbl_1_rodata_204 = 0.1f; /* 0x204 */
static const double lbl_1_rodata_208 = 30.0; /* 0x208 */
static const double lbl_1_rodata_210 = 120.0; /* 0x210 */
static const double lbl_1_rodata_218 = 1.0; /* 0x218 */
static const double lbl_1_rodata_220 = 336.0; /* 0x220 */
static const double lbl_1_rodata_228 = 156.0; /* 0x228 */
static const float lbl_1_rodata_230 = 1.85f; /* 0x230 */
static const float lbl_1_rodata_234 = 185.0f; /* 0x234 */
static const float lbl_1_rodata_238 = 0.9230769f; /* 0x238 */
static const float lbl_1_rodata_23C = 0.003f; /* 0x23C */
static const float lbl_1_rodata_240 = 260.0f; /* 0x240 */
/* 0x248 lbl_1_rodata_248 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_250 = 1.5f; /* 0x250 */
static const float lbl_1_rodata_254 = 18.0f; /* 0x254 */
static const float lbl_1_rodata_258 = 360.0f; /* 0x258 */
static const float lbl_1_rodata_25C = -10000.0f; /* 0x25C */
static const float lbl_1_rodata_260 = 48.0f; /* 0x260 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1BC */ s32 lbl_1_bss_1BC[3];
/* 0x1B0 */ float lbl_1_bss_1B0[3];
/* 0x18C */ float lbl_1_bss_18C[9];
/* 0x188 */ s32 lbl_1_bss_188;
/* 0x184 */ s32 lbl_1_bss_184;
/* 0x180 */ s32 lbl_1_bss_180;
/* 0x17C */ s32 lbl_1_bss_17C;
/* 0x178 */ s32 lbl_1_bss_178;
/* 0x174 */ s32 lbl_1_bss_174;
/* 0x170 */ s32 lbl_1_bss_170;
/* 0x16C */ s32 lbl_1_bss_16C;
/* 0x15C */ float lbl_1_bss_15C[4];
/* 0x154 */ float lbl_1_bss_154[2];
/* 0x144 */ float lbl_1_bss_144[4];
/* 0x140 */ s16 lbl_1_bss_140;
/* 0x138 */ s16 lbl_1_bss_138[4];
/* 0x134 */ s32 lbl_1_bss_134;
/* 0x130 */ s32 lbl_1_bss_130;
/* 0x12E */ s16 lbl_1_bss_12E;
/* 0x128 */ s16 lbl_1_bss_128[3];
/* 0x124 */ s32 lbl_1_bss_124;
/* 0x122 gap_05_00000122_bss (0x2): alignment gap */
/* 0x120 */ s16 lbl_1_bss_120[2];
/* 0x11E gap_05_0000011E_bss (0x2): alignment gap */
/* 0x11C */ s16 lbl_1_bss_11C[2];
/* 0x118 */ s32 lbl_1_bss_118;
/* 0x116 gap_05_00000116_bss (0x2): alignment gap */
/* 0x114 */ s16 lbl_1_bss_114;
/* 0xF4 */ s16 lbl_1_bss_F4[16];
/* 0xF0 */ float lbl_1_bss_F0;
/* 0xEC */ float lbl_1_bss_EC;
/* 0xE8 */ s32 lbl_1_bss_E8;
/* 0xE4 */ s32 lbl_1_bss_E4;
/* 0xE2 */ s16 lbl_1_bss_E2;
/* 0xD0 */ s16 lbl_1_bss_D0[9];
/* 0xC6 */ s16 lbl_1_bss_C6[5];
/* 0xC0 */ s16 lbl_1_bss_C0[3];
/* 0xBE gap_05_000000BE_bss (0x2): alignment gap */
/* 0xBC */ s16 lbl_1_bss_BC[2];
/* 0xB8 */ s32 lbl_1_bss_B8;
/* 0xA8 */ float lbl_1_bss_A8[4];
/* 0x9C */ float lbl_1_bss_9C[3];
/* 0x60 */ STORY_WINWORK lbl_1_bss_60;
/* 0x58 */ STORY_PARWORK *lbl_1_bss_58[2];

/* --- functions (reference order), .data placed before its first user --- */
/* 0x178 */ HuVecF lbl_1_data_178 = { 288.0f, 240.0f, 1500.0f };
/* 0x184 */ float lbl_1_data_184[10] = { 0.0f, 0.0f, 46.87f, -10.54f, -10.89f, 46.87f, 53.7f, -30.43f, 21.96f, -24.16f };

/* 1048 insns */
/* cutscene setup for the current story stage (called once from fn_1_894): mode from
   GwCommon.storyNo exactly as fn_1_894 derives it */
void fn_1_13E8(void)
{
    HuVecF pos;
    s32 storyNo;
    s32 mode;
    s32 lostF;
    HU3DMODELID modelId;
    ANIMDATA *anim;

    storyNo = GwCommon.storyNo;
    HuWinInit(1);
    fn_1_9CCC(0);
    if(storyNo == -2) {
        mode = 0;
    } else if(storyNo == -3) {
        mode = 100;
    } else if(storyNo == 5) {
        mode = 300;
        lostF = 0;
    } else if(storyNo < 6) {
        mode = 200;
    } else if(GwPlayer[0].mgCoinBonus != 0) {
        mode = 400;
    } else {
        mode = 300;
        lostF = 1;
    }
    lbl_1_bss_188 = GwPlayerConf[0].charNo;
    switch(mode) {
        case 0:
            lbl_1_bss_184 = 1;
            lbl_1_bss_17C = 1;
            fn_1_70F4(8);
            pos = lbl_1_data_178;
            pos.x += 60.0f;
            pos.y += 90.0f;
            fn_1_7408(&pos);
            pos = Hu3DData[lbl_1_bss_114].pos;
            lbl_1_bss_C0[0] = Hu3DLLightCreate(lbl_1_bss_114, pos.x, pos.y, pos.z, 0.0f, 0.0f, -1.0f, 0, 0, 0);
            Hu3DLLightStaticSet(lbl_1_bss_114, lbl_1_bss_C0[0], TRUE);
            Hu3DLLightInfinitytSet(lbl_1_bss_114, lbl_1_bss_C0[0]);
            lbl_1_bss_E4 = 0;
            HuPrcChildCreate(fn_1_7660, 100, 0x2000, 0, HuPrcCurrentGet());
            fn_1_7BE4();
            Hu3DData[lbl_1_bss_E2].pos.x = Hu3DData[lbl_1_bss_114].pos.x - 128.72514f;
            Hu3DData[lbl_1_bss_E2].pos.y = Hu3DData[lbl_1_bss_114].pos.y - 1.991341f;
            Hu3DData[lbl_1_bss_E2].pos.z = 142.54988f + Hu3DData[lbl_1_bss_114].pos.z;
            pos = Hu3DData[lbl_1_bss_E2].pos;
            lbl_1_bss_C0[1] = Hu3DLLightCreate(lbl_1_bss_E2, pos.x, pos.y, pos.z, 0.0f, 0.0f, -1.0f, 0, 0, 0);
            Hu3DLLightStaticSet(lbl_1_bss_E2, lbl_1_bss_C0[1], TRUE);
            Hu3DLLightInfinitytSet(lbl_1_bss_E2, lbl_1_bss_C0[1]);
            HuPrcChildCreate(fn_1_8018, 100, 0x2000, 0, HuPrcCurrentGet());
            *(HuVecF *)&lbl_1_bss_18C[0] = Hu3DData[lbl_1_bss_114].pos;
            lbl_1_bss_18C[1] += 170.0f;
            *(HuVecF *)&lbl_1_bss_18C[3] = *(HuVecF *)&lbl_1_bss_18C[0];
            lbl_1_bss_18C[2] += 480.0f;
            {
                HuVecF up = { 0.0f, 1.0f, 0.0f };
                HuVecF *upP = &up;
                *(HuVecF *)&lbl_1_bss_18C[6] = *upP;
            }
            Hu3DCameraPosSetV(2, (HuVecF *)&lbl_1_bss_18C[0], (HuVecF *)&lbl_1_bss_18C[6], (HuVecF *)&lbl_1_bss_18C[3]);
            Hu3DGLightColorSet(lbl_1_bss_40[0], 0, 0, 0, 255);
            Hu3DGLightColorSet(lbl_1_bss_40[1], 0, 0, 0, 255);
            modelId = Hu3DModelCreateData(DATA_storymode + 0x61);
            Hu3DModelAttrSet(modelId, 0x40000001);
            Hu3DModelCameraSet(modelId, 2);
            Hu3DModelLayerSet(modelId, 7);
            pos = Hu3DData[lbl_1_bss_E2].pos;
            pos.x = 0.0f;
            pos.y -= 10.0f;
            Hu3DModelPosSetV(modelId, &pos);
            lbl_1_bss_C = 0x1C;
            break;
        case 100:
            lbl_1_bss_184 = 0x65;
            fn_1_66C4(lbl_1_bss_188, 1);
            pos = lbl_1_data_178;
            pos.x += 120.0f;
            fn_1_6924(&pos);
            fn_1_6B38();
            pos = lbl_1_data_178;
            pos.x -= 120.0f;
            fn_1_6CBC(&pos);
            fn_1_6E0C();
            pos = lbl_1_data_178;
            pos.x += 420.0f;
            fn_1_6F5C(&pos);
            lbl_1_bss_C = 0x1D;
            break;
        case 200:
            if(GWPlayerCoinGet(0) > 0) {
                if(storyNo < 4) {
                    lbl_1_bss_184 = GwCommon.storyBoardNo[storyNo - 1] == 0 ? 0xCC :
                        GwCommon.storyBoardNo[storyNo - 1] == 1 ? 0xCD :
                        GwCommon.storyBoardNo[storyNo - 1] == 2 ? 0xCE :
                        GwCommon.storyBoardNo[storyNo - 1] == 3 ? 0xCF :
                        GwCommon.storyBoardNo[storyNo - 1] == 4 ? 0xD0 : 0xD1;
                } else {
                    lbl_1_bss_184 = 0xD4;
                }
                lbl_1_bss_17C = 1;
                fn_1_66C4(lbl_1_bss_188, 1);
            } else {
                lbl_1_bss_184 = 0xC9;
                fn_1_66C4(lbl_1_bss_188, 3);
            }
            pos = lbl_1_data_178;
            pos.x += 120.0f;
            fn_1_6924(&pos);
            fn_1_6B38();
            pos = lbl_1_data_178;
            pos.x -= 120.0f;
            fn_1_6CBC(&pos);
            fn_1_6E0C();
            pos = lbl_1_data_178;
            pos.x += 420.0f;
            fn_1_6F5C(&pos);
            lbl_1_bss_C = 0x1D;
            break;
        case 300:
            lbl_1_bss_184 = (lostF == 0) ? 0x12D : 0x131;
            fn_1_66C4(lbl_1_bss_188, (lostF == 0) ? 1 : 3);
            pos = lbl_1_data_178;
            pos.x += 120.0f;
            fn_1_6924(&pos);
            fn_1_70F4(1);
            pos = lbl_1_data_178;
            pos.x -= 140.0f;
            fn_1_7408(&pos);
            HuPrcChildCreate(fn_1_7660, 100, 0x2000, 0, HuPrcCurrentGet());
            /* mgDataTbl[61] is m562 (the finale): its instruction picture as a texture and its movie */
            anim = HuSprAnimRead(HuDataReadNumHeapShortForce(mgDataTbl[61].instPic[0], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DAnimCreate(anim, lbl_1_bss_3C, "S3TC_mg_movie");
            HuTHPSprCreateVol(mgDataTbl[61].movie[0], 1, 100, 0);
            Hu3DModelMatHookSet(lbl_1_bss_3C, HuTHPMatHook);
            lbl_1_bss_C = 0x1E;
            break;
        case 400:
            lbl_1_bss_184 = 0x191;
            fn_1_66C4(lbl_1_bss_188, 1);
            pos = lbl_1_data_178;
            pos.x += 120.0f;
            fn_1_6924(&pos);
            fn_1_70F4(1);
            pos = lbl_1_data_178;
            pos.x -= 140.0f;
            fn_1_7408(&pos);
            HuPrcChildCreate(fn_1_7660, 100, 0x2000, 0, HuPrcCurrentGet());
            fn_1_6B38();
            pos = lbl_1_data_178;
            pos.x -= 420.0f;
            fn_1_6CBC(&pos);
            fn_1_6E0C();
            pos = lbl_1_data_178;
            pos.x += 420.0f;
            fn_1_6F5C(&pos);
            fn_1_6FF8(2);
            lbl_1_bss_C = 0x1F;
            break;
    }
    lbl_1_bss_1BC[0] = lbl_1_bss_1BC[1] = lbl_1_bss_1BC[2] = 0;
    lbl_1_bss_1B0[0] = lbl_1_bss_1B0[1] = lbl_1_bss_1B0[2] = 0.0f;
    lbl_1_bss_178 = 0;
    lbl_1_bss_154[0] = lbl_1_bss_154[1] = 0.0f;
    lbl_1_bss_174 = 0;
    if(GwCommon.storyNo == -2) {
        lbl_1_bss_C6[0] = espEntry(DATA_storymode + 0x5E, 0, 0);
        lbl_1_bss_C6[1] = espEntry(DATA_storymode + 0x5F, 0, 0);
        lbl_1_bss_C6[2] = espEntry(DATA_storymode + 0x5F, 0, 0);
        lbl_1_bss_C6[3] = espEntry(DATA_storymode + 0x60, 0, 0);
        lbl_1_bss_C6[4] = espEntry(DATA_storymode + 0x60, 0, 0);
        espScaleSet(lbl_1_bss_C6[0], 0.0f, 0.0f);
        espScaleSet(lbl_1_bss_C6[1], 0.0f, 0.0f);
        espScaleSet(lbl_1_bss_C6[2], 0.0f, 0.0f);
        espScaleSet(lbl_1_bss_C6[3], 0.0f, 0.0f);
        espScaleSet(lbl_1_bss_C6[4], 0.0f, 0.0f);
    }
    if(GwCommon.storyNo != -2) {
        lbl_1_bss_58[0] = fn_1_A61C(HuSprAnimRead(HuDataReadNum(DATA_storymode + 0x6C, HU_MEMNUM_OVL)), 4, 2);
        lbl_1_bss_58[1] = fn_1_A61C(HuSprAnimRead(HuDataReadNum(DATA_storymode + 0x6C, HU_MEMNUM_OVL)), 4, 2);
    }
}

/* 4255 insns */
s32 fn_1_2448(void)
{
    Vec pos2d;
    s32 result;
    s32 storyNo;

    result = 0;
    storyNo = GwCommon.storyNo;
    switch (lbl_1_bss_184) {
        case 1:
            if (lbl_1_bss_17C == 1) {
                if (lbl_1_bss_1BC[0] == 0) {
                    HuAudFXPanning(HuAudFXPlay(0x2C9), 56);
                }
                if (++lbl_1_bss_1BC[0] > 30) {
                    float speed = 180.0f;
                    Vec pos = *(Vec *)&lbl_1_bss_18C[0];
                    Vec target = *(Vec *)&lbl_1_bss_18C[3];
                    pos.x -= lbl_1_bss_18C[0] * HuSin(lbl_1_bss_1B0[0]);
                    pos.y -= lbl_1_bss_18C[1] * HuSin(lbl_1_bss_1B0[0]);
                    pos.z += (1550.0f - lbl_1_bss_18C[2]) * HuSin(lbl_1_bss_1B0[0]);
                    target.x -= lbl_1_bss_18C[3] * HuSin(lbl_1_bss_1B0[0]);
                    target.y -= lbl_1_bss_18C[4] * HuSin(lbl_1_bss_1B0[0]);
                    Hu3DCameraPosSetV(2, &pos, (Vec *)&lbl_1_bss_18C[6], &target);
                    lbl_1_bss_1B0[0] += 90.0f / speed;
                    if (lbl_1_bss_1B0[0] >= 90.0f) {
                        lbl_1_bss_17C = 2;
                        lbl_1_bss_1BC[0] = 0;
                        lbl_1_bss_9C[0] = 0.0f;
                        lbl_1_bss_9C[1] = 0.0f;
                        lbl_1_bss_9C[2] = 0.0f;
                        Hu3DModelAttrReset(lbl_1_bss_BC[0], 0x40000002);
                        Hu3DModelAttrReset(lbl_1_bss_BC[1], 0x40000002);
                    }
                }
            }
            else if (lbl_1_bss_17C == 2) {
                lbl_1_bss_9C[1] += 9.0f;
                lbl_1_bss_9C[2] += 12.0f;
                Hu3DLLightColorSet(lbl_1_bss_114, lbl_1_bss_C0[0], lbl_1_bss_9C[0], lbl_1_bss_9C[1], lbl_1_bss_9C[2], 255);
                Hu3DLLightColorSet(lbl_1_bss_E2, lbl_1_bss_C0[1], lbl_1_bss_9C[0], lbl_1_bss_9C[1], lbl_1_bss_9C[2], 255);
                if (++lbl_1_bss_1BC[0] == 20) {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                HuAudFXPanning(HuAudFXPlay(0x2C9), 56);
                fn_1_744C(9);
                fn_1_9D84(0x29);
                lbl_1_bss_1BC[0] = (lbl_1_bss_E8 == 8) ? 10 : 0;
                lbl_1_bss_184 = 2;
            }
            break;
        case 2:
            if (++lbl_1_bss_1BC[0] == 20) {
                fn_1_744C(10);
                fn_1_9D84(0x2A);
                fn_1_744C(8);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 3;
            }
            break;
        case 3:
            if (++lbl_1_bss_1BC[0] == 10) {
                fn_1_7E24(2);
                fn_1_9D84(0x2B);
                fn_1_7E24(1);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 4;
            }
            break;
        case 4:
            if (++lbl_1_bss_1BC[0] == 10) {
                fn_1_744C(10);
                fn_1_9D84(0x2C);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 5;
            }
            break;
        case 5:
            if (++lbl_1_bss_1BC[0] == 10) {
                HuAudFXPanning(HuAudFXPlay(0x2CB), 56);
                fn_1_744C(13);
                fn_1_9D84(0x2D);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 6;
            }
            break;
        case 6:
            if (++lbl_1_bss_1BC[0] == 15) {
                fn_1_7E24(5);
                fn_1_9D84(0x2E);
                fn_1_7E24(4);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 7;
            }
            break;
        case 7:
            if (++lbl_1_bss_1BC[0] == 10) {
                fn_1_744C(15);
                fn_1_9D84(0x2F);
                fn_1_744C(14);
                lbl_1_bss_184 = 8;
            }
            break;
        case 8:
            HuAudFXPanning(HuAudFXPlay(0x237), 56);
            fn_1_7E24(6);
            fn_1_9D84(0x30);
            fn_1_7E24(4);
            lbl_1_bss_1BC[0] = 0;
            lbl_1_bss_184 = 9;
            break;
        case 9:
            if (++lbl_1_bss_1BC[0] == 10) {
                fn_1_744C(11);
                fn_1_9D84(0x31);
                fn_1_744C(12);
                fn_1_7E24(8);
                lbl_1_bss_17C = 1;
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 11;
            }
            break;
        case 10:
            if (++lbl_1_bss_1BC[0] == 60) {
                HuAudFXPanning(HuAudFXPlay(0x59C), 56);
                fn_1_7E24(9);
                fn_1_9D84(0x32);
                fn_1_7E24(8);
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_184 = 11;
            }
            break;
        case 11:
            if (lbl_1_bss_17C == 1) {
                if (++lbl_1_bss_1BC[0] == 15) {
                    espDrawNoSet(lbl_1_bss_C6[0], 0);
                    espPriSet(lbl_1_bss_C6[0], 1500);
                    espDrawNoSet(lbl_1_bss_C6[1], 0);
                    espPriSet(lbl_1_bss_C6[1], 1500);
                    espDrawNoSet(lbl_1_bss_C6[2], 0);
                    espPriSet(lbl_1_bss_C6[2], 1500);
                    espDrawNoSet(lbl_1_bss_C6[3], 0);
                    espPriSet(lbl_1_bss_C6[3], 1500);
                    espDrawNoSet(lbl_1_bss_C6[4], 0);
                    espPriSet(lbl_1_bss_C6[4], 1500);
                    espScaleSet(lbl_1_bss_C6[0], 4.0f, 4.0f);
                    espScaleSet(lbl_1_bss_C6[1], 1.0f, 4.0f);
                    espScaleSet(lbl_1_bss_C6[2], 1.0f, 4.0f);
                    espScaleSet(lbl_1_bss_C6[3], 4.0f, 1.0f);
                    espScaleSet(lbl_1_bss_C6[4], 4.0f, 1.0f);
                    Hu3DModelObjPosGet(lbl_1_bss_114, "itemhook_R", (Vec *)&lbl_1_bss_18C[0]);
                    lbl_1_bss_18C[0] += 5.0f;
                    lbl_1_bss_18C[1] -= 25.0f;
                    Hu3D3Dto2D((Vec *)&lbl_1_bss_18C[0], 2, &pos2d);
                    lbl_1_bss_A8[0] = pos2d.x - 384.0f - 127.0f;
                    lbl_1_bss_A8[1] = 127.0f + (384.0f + pos2d.x);
                    lbl_1_bss_A8[2] = pos2d.y - 384.0f - 127.0f;
                    lbl_1_bss_A8[3] = 127.0f + (384.0f + pos2d.y);
                    espPosSet(lbl_1_bss_C6[0], pos2d.x, pos2d.y);
                    espPosSet(lbl_1_bss_C6[1], lbl_1_bss_A8[0], pos2d.y);
                    espPosSet(lbl_1_bss_C6[2], lbl_1_bss_A8[1], pos2d.y);
                    espPosSet(lbl_1_bss_C6[3], pos2d.x, lbl_1_bss_A8[2]);
                    espPosSet(lbl_1_bss_C6[4], pos2d.x, lbl_1_bss_A8[3]);
                    lbl_1_bss_17C++;
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_1B0[0] = 4.0f;
                }
            }
            else if (lbl_1_bss_17C == 2) {
                lbl_1_bss_1B0[0] -= 0.05f;
                if (lbl_1_bss_1B0[0] < 1.0f) {
                    lbl_1_bss_1B0[0] = 1.0f;
                }
                lbl_1_bss_1B0[1] = 1024.0f - 256.0f * lbl_1_bss_1B0[0];
                espScaleSet(lbl_1_bss_C6[0], lbl_1_bss_1B0[0], lbl_1_bss_1B0[0]);
                espScaleSet(lbl_1_bss_C6[1], lbl_1_bss_1B0[1], 4.0f);
                espScaleSet(lbl_1_bss_C6[2], lbl_1_bss_1B0[1], 4.0f);
                espScaleSet(lbl_1_bss_C6[3], 4.0f, lbl_1_bss_1B0[1]);
                espScaleSet(lbl_1_bss_C6[4], 4.0f, lbl_1_bss_1B0[1]);
                Hu3D3Dto2D((Vec *)&lbl_1_bss_18C[0], 2, &pos2d);
                espPosSet(lbl_1_bss_C6[1], lbl_1_bss_A8[0] - lbl_1_bss_1B0[1] / 2.0f, pos2d.y);
                espPosSet(lbl_1_bss_C6[2], lbl_1_bss_A8[1] - lbl_1_bss_1B0[1] / 2.0f, pos2d.y);
                espPosSet(lbl_1_bss_C6[3], pos2d.x, lbl_1_bss_A8[2] - lbl_1_bss_1B0[1] / 2.0f);
                espPosSet(lbl_1_bss_C6[4], pos2d.x, lbl_1_bss_A8[3] - lbl_1_bss_1B0[1] / 2.0f);
                if (lbl_1_bss_1B0[0] == 1.0f) {
                    lbl_1_bss_17C++;
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_184 = 10;
                }
            }
            else if (lbl_1_bss_17C == 3) {
                if (++lbl_1_bss_1BC[0] == 15) {
                    HuAudSStreamFadeOut(lbl_1_bss_10, 500);
                    lbl_1_bss_17C++;
                }
            }
            else if (lbl_1_bss_17C == 4) {
                lbl_1_bss_1B0[0] -= 0.08f;
                if (lbl_1_bss_1B0[0] < 0.0f) {
                    lbl_1_bss_1B0[0] = 0.0f;
                }
                lbl_1_bss_1B0[1] = 1024.0f - 256.0f * lbl_1_bss_1B0[0];
                espScaleSet(lbl_1_bss_C6[0], lbl_1_bss_1B0[0], lbl_1_bss_1B0[0]);
                espScaleSet(lbl_1_bss_C6[1], lbl_1_bss_1B0[1], 4.0f);
                espScaleSet(lbl_1_bss_C6[2], lbl_1_bss_1B0[1], 4.0f);
                espScaleSet(lbl_1_bss_C6[3], 4.0f, lbl_1_bss_1B0[1]);
                espScaleSet(lbl_1_bss_C6[4], 4.0f, lbl_1_bss_1B0[1]);
                Hu3D3Dto2D((Vec *)&lbl_1_bss_18C[0], 2, &pos2d);
                espPosSet(lbl_1_bss_C6[1], lbl_1_bss_A8[0] - lbl_1_bss_1B0[1] / 2.0f, pos2d.y);
                espPosSet(lbl_1_bss_C6[2], lbl_1_bss_A8[1] - lbl_1_bss_1B0[1] / 2.0f, pos2d.y);
                espPosSet(lbl_1_bss_C6[3], pos2d.x, lbl_1_bss_A8[2] - lbl_1_bss_1B0[1] / 2.0f);
                espPosSet(lbl_1_bss_C6[4], pos2d.x, lbl_1_bss_A8[3] - lbl_1_bss_1B0[1] / 2.0f);
                if (lbl_1_bss_1B0[0] == 0.0f) {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (HuAudSStreamStatGet(lbl_1_bss_10) == 0) {
                    result = -1;
                    lbl_1_bss_184 = 1000;
                }
            }
            break;
        case 101:
            if (++lbl_1_bss_1BC[0] > 120) {
                HuAudFXPanning(HuAudFXPlay(0x2F3), 56);
                fn_1_6D00(2);
                fn_1_9D84(0);
                lbl_1_bss_17C = 1;
                lbl_1_bss_184 = 102;
            }
            break;
        case 102:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_9EE8(0x21)) {
                    lbl_1_bss_180 = lbl_1_bss_184;
                    lbl_1_bss_184 = 500;
                }
                else {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_17C = 1;
                    fn_1_6D00(1);
                    lbl_1_bss_184 = 103;
                }
            }
            break;
        case 103:
            if (lbl_1_bss_17C != 0) {
                Hu3DModelAttrReset(lbl_1_bss_3C, HU3D_ATTR_DISPOFF);
                lbl_1_bss_1B0[0] += 0.025f;
                if (lbl_1_bss_1B0[0] > 1.0f) {
                    lbl_1_bss_1B0[0] = 1.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_3C, lbl_1_bss_1B0[0], lbl_1_bss_1B0[0], lbl_1_bss_1B0[0]);
                if (lbl_1_bss_1B0[0] == 1.0f) {
                    fn_1_6D00(2);
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                fn_1_A294(lbl_1_bss_188, 0);
                fn_1_9D84(1);
                fn_1_6D00(1);
                lbl_1_bss_184 = 104;
            }
            break;
        case 104:
            if (fn_1_8150(0)) {
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_1B0[0] = 0.0f;
                lbl_1_bss_1B0[1] = 150.0f;
                lbl_1_bss_17C = 1;
                lbl_1_bss_184 = 105;
            }
            break;
        case 105:
            if (++lbl_1_bss_1BC[0] > 60) {
                if (lbl_1_bss_17C != 0) {
                    lbl_1_bss_1B0[0] += 1.0f;
                    if (lbl_1_bss_1B0[0] > 90.0f) {
                        lbl_1_bss_1B0[0] = 90.0f;
                    }
                    pos2d = lbl_1_data_178;
                    pos2d.x += 420.0f;
                    pos2d.x -= 300.0 * HuSin(lbl_1_bss_1B0[0]);
                    pos2d.y -= lbl_1_bss_1B0[1];
                    if (pos2d.x <= 616.0f) {
                        lbl_1_bss_1B0[1] = lbl_1_bss_1B0[1] - lbl_1_bss_1B0[1] / 9.0f;
                        if (pos2d.y > lbl_1_data_178.y) {
                            pos2d.y = lbl_1_data_178.y;
                        }
                    }
                    fn_1_6F5C(&pos2d);
                    if (lbl_1_bss_1B0[0] == 90.0f) {
                        lbl_1_bss_17C = 0;
                    }
                }
                else {
                    HuAudFXPanning(HuAudFXPlay(0x1D0), 56);
                    fn_1_A294(lbl_1_bss_188, 0);
                    fn_1_9D84(2);
                    fn_1_6D00(2);
                    lbl_1_bss_184 = 106;
                }
            }
            break;
        case 106:
            fn_1_9D84(3);
            fn_1_6D00(1);
            lbl_1_bss_17C = 1;
            lbl_1_bss_184 = 107;
            break;
        case 107:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_96CC(1)) {
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_17C = 2;
                }
            }
            else if (lbl_1_bss_17C == 2) {
                if (++lbl_1_bss_1BC[0] > 30) {
                    if (fn_1_8150(1)) {
                        lbl_1_bss_1BC[0] = 0;
                        lbl_1_bss_17C = 0;
                    }
                }
            }
            else {
                if (++lbl_1_bss_1BC[0] > 60) {
                    result = 1;
                    lbl_1_bss_184 = 1000;
                }
            }
            break;
        case 201:
            if (++lbl_1_bss_1BC[0] > 60) {
                HuAudFXPanning(HuAudFXPlay(0x2F3), 56);
                lbl_1_bss_17C = 1;
                fn_1_6D00(2);
                fn_1_A294(lbl_1_bss_188, 0);
                fn_1_9D84(4);
                lbl_1_bss_184 = (storyNo < 4) ? 202 : 203;
            }
            break;
        case 202:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_9EE8(0x22)) {
                    lbl_1_bss_180 = lbl_1_bss_184;
                    lbl_1_bss_184 = 500;
                }
                else {
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_17C = 2;
                    fn_1_69CC(1);
                }
            }
            else if (lbl_1_bss_17C == 2) {
                if (++lbl_1_bss_1BC[0] > 30) {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_17C = 1;
                    fn_1_6D00(1);
                    lbl_1_bss_184 = 103;
                }
            }
            break;
        case 203:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_9EE8(0x26)) {
                    lbl_1_bss_180 = lbl_1_bss_184;
                    lbl_1_bss_184 = 500;
                }
                else {
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_17C = 2;
                    fn_1_69CC(1);
                }
            }
            else if (lbl_1_bss_17C == 2) {
                if (++lbl_1_bss_1BC[0] > 30) {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_17C = 1;
                    fn_1_6D00(1);
                    lbl_1_bss_184 = 103;
                }
            }
            break;
        case 204:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(5);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 205:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(6);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 206:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(7);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 207:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(8);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 208:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(9);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 209:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(10);
            lbl_1_bss_184 = (storyNo < 4) ? 210 : 212;
            break;
        case 210:
            fn_1_9D84(11);
            lbl_1_bss_17C = 1;
            lbl_1_bss_184 = 211;
            break;
        case 211:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_9EE8(0x25)) {
                    lbl_1_bss_180 = lbl_1_bss_184;
                    lbl_1_bss_184 = 500;
                }
                else {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_17C = 1;
                    fn_1_69CC(1);
                    fn_1_6D00(1);
                    lbl_1_bss_184 = 103;
                }
            }
            break;
        case 212:
            HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(12);
            lbl_1_bss_17C = 1;
            lbl_1_bss_184 = 213;
            break;
        case 213:
            if (lbl_1_bss_17C == 1) {
                if (fn_1_9EE8(0x26)) {
                    lbl_1_bss_180 = lbl_1_bss_184;
                    lbl_1_bss_184 = 500;
                }
                else {
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_17C = 1;
                    fn_1_69CC(1);
                    fn_1_6D00(1);
                    lbl_1_bss_184 = 103;
                }
            }
            break;
        case 301:
            if (++lbl_1_bss_1BC[0] > 60) {
                HuAudFXPanning(HuAudFXPlay(0x2C9), 56);
                fn_1_744C(7);
                fn_1_A294(lbl_1_bss_188, 0);
                fn_1_9D84(13);
                fn_1_744C(6);
                lbl_1_bss_184 = 302;
            }
            break;
        case 302:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                fn_1_9D84(14);
                lbl_1_bss_17C = 1;
                fn_1_744C(1);
                lbl_1_bss_184 = 303;
            }
            break;
        case 303:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                if (lbl_1_bss_17C == 1) {
                    if (fn_1_9EE8(0x23)) {
                        lbl_1_bss_180 = lbl_1_bss_184;
                        lbl_1_bss_184 = 500;
                    }
                    else {
                        lbl_1_bss_17C = 0;
                    }
                }
                else {
                    if (fn_1_96CC(0)) {
                        lbl_1_bss_17C = 0;
                        fn_1_744C(6);
                        lbl_1_bss_184 = 304;
                    }
                }
            }
            break;
        case 304:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                if (lbl_1_bss_17C == 0) {
                    HuAudFXPanning(HuAudFXPlay(0x2CB), 56);
                    fn_1_A294(lbl_1_bss_188, 0);
                    fn_1_9D84(15);
                    lbl_1_bss_17C = 1;
                }
            }
            break;
        case 305:
            if (++lbl_1_bss_1BC[0] > 60) {
                HuAudFXPanning(HuAudFXPlay(0x2C9), 56);
                fn_1_744C(7);
                fn_1_A294(lbl_1_bss_188, 0);
                fn_1_9D84(16);
                lbl_1_bss_17C = 1;
                fn_1_744C(1);
                lbl_1_bss_184 = 306;
            }
            break;
        case 306:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                if (lbl_1_bss_17C == 1) {
                    if (fn_1_9EE8(0x24)) {
                        lbl_1_bss_180 = lbl_1_bss_184;
                        lbl_1_bss_184 = 500;
                    }
                    else {
                        lbl_1_bss_1BC[0] = 0;
                        lbl_1_bss_17C = 2;
                        fn_1_69CC(1);
                    }
                }
                else if (lbl_1_bss_17C == 2) {
                    if (++lbl_1_bss_1BC[0] > 30) {
                        lbl_1_bss_17C = 0;
                    }
                }
                else {
                    if (fn_1_96CC(0)) {
                        lbl_1_bss_17C = 0;
                        fn_1_744C(6);
                        lbl_1_bss_184 = 304;
                    }
                }
            }
            break;
        case 307:
            if (lbl_1_bss_17C == 1 && fn_1_8B34()) {
                lbl_1_bss_17C = 0;
            }
            if (++lbl_1_bss_1BC[0] > 30) {
                if (fn_1_8150(0)) {
                    result = 1;
                    lbl_1_bss_184 = 1000;
                }
            }
            break;
        case 401:
            HuAudFXPanning(HuAudFXPlay(0x2CA), 56);
            fn_1_744C(3);
            fn_1_9D84(17);
            fn_1_744C(1);
            lbl_1_bss_184 = 402;
            break;
        case 402:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                fn_1_9D84(18);
                lbl_1_bss_17C = 1;
                lbl_1_bss_184 = 403;
            }
            break;
        case 403:
            if (lbl_1_bss_17C == 1) {
                if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                    fn_1_744C(4);
                    fn_1_9D84(19);
                    fn_1_744C(1);
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (fn_1_96CC(0)) {
                    lbl_1_bss_14[0] = 0;
                    lbl_1_bss_184 = 404;
                    fn_1_744C(6);
                }
            }
            break;
        case 404:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                fn_1_9D84(20);
                lbl_1_bss_14[0] = 0;
                lbl_1_bss_184 = 405;
            }
            break;
        case 405:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                HuAudFXPanning(HuAudFXPlay(0x2CB), 56);
                fn_1_744C(4);
                fn_1_9D84(21);
                fn_1_744C(1);
                lbl_1_bss_184 = 406;
            }
            break;
        case 406:
            if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                HuAudFXPanning(HuAudFXPlay(0x2C9), 56);
                fn_1_744C(7);
                fn_1_9D84(22);
                fn_1_744C(1);
                lbl_1_bss_17C = 0;
                lbl_1_bss_184 = 407;
            }
            break;
        case 407:
            if (lbl_1_bss_17C == 0) {
                if (Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
                    fn_1_744C(6);
                    fn_1_A294(lbl_1_bss_188, 0);
                    fn_1_9D84(23);
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_17C = 1;
                    fn_1_744C(1);
                }
            }
            else {
                if (++lbl_1_bss_1BC[0] > 15) {
                    HSFOBJECT *obj = Hu3DModelObjPtrGet(lbl_1_bss_140, "ske_head");
                    lbl_1_bss_EC = obj->mesh.curr.rot.z;
                    lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                    if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                        obj = Hu3DModelObjPtrGet(lbl_1_bss_140, "root_motion");
                        lbl_1_bss_F0 = obj->mesh.curr.rot.x;
                        lbl_1_bss_1B0[2] = lbl_1_bss_F0;
                    }
                    lbl_1_bss_1B0[0] = 0.0f;
                    lbl_1_bss_184 = 408;
                }
            }
            break;
        case 408:
            if (fn_1_914C()) {
                lbl_1_bss_1BC[0] = 0;
                lbl_1_bss_17C = 1;
                lbl_1_bss_184 = 409;
            }
            if (lbl_1_bss_E8 == 5) {
                if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                    lbl_1_bss_1B0[1] -= 0.03846154f;
                    Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                    lbl_1_bss_1B0[2] -= 0.07692308f;
                    Hu3DMotionForceSet(lbl_1_bss_140, "root_motion", 0x80, lbl_1_bss_1B0[2]);
                }
                else {
                    lbl_1_bss_1B0[1] -= 0.115384616f;
                    Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                }
            }
            else {
                lbl_1_bss_1B0[0] += 0.7f;
                Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f - lbl_1_bss_1B0[0], 0.0f);
            }
            break;
        case 409:
            if (lbl_1_bss_17C == 1) {
                if (++lbl_1_bss_1BC[0] > 65) {
                    lbl_1_bss_1B0[0] += 0.6923077f;
                    if (lbl_1_bss_1B0[0] > 90.0f) {
                        lbl_1_bss_1B0[0] = 90.0f;
                    }
                    pos2d = lbl_1_data_178;
                    pos2d.x -= 420.0f;
                    pos2d.x += 300.0 * HuSin(lbl_1_bss_1B0[0]);
                    pos2d.y += lbl_1_bss_1B0[1];
                    if (pos2d.x >= -40.0f) {
                        lbl_1_bss_1B0[1] = lbl_1_bss_1B0[1] - lbl_1_bss_1B0[1] / 20.0f;
                        if (pos2d.y < lbl_1_data_178.y) {
                            pos2d.y = lbl_1_data_178.y;
                        }
                    }
                    fn_1_6CBC(&pos2d);
                    if (lbl_1_bss_1B0[0] == 90.0f) {
                        lbl_1_bss_1B0[0] = 0.0f;
                        lbl_1_bss_1B0[1] = 200.0f;
                        lbl_1_bss_17C = 2;
                    }
                }
                else {
                    lbl_1_bss_1B0[0] -= 0.8f;
                    if (lbl_1_bss_1B0[0] < 0.0f) {
                        lbl_1_bss_1B0[0] = 0.0f;
                    }
                    Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f - lbl_1_bss_1B0[0], 0.0f);
                    if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                        lbl_1_bss_1B0[1] += 0.15384616f;
                        if (lbl_1_bss_1B0[1] > lbl_1_bss_EC) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                        lbl_1_bss_1B0[2] += 0.30769232f;
                        if (lbl_1_bss_1B0[2] > lbl_1_bss_F0) {
                            lbl_1_bss_1B0[2] = lbl_1_bss_F0;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "root_motion", 0x80, lbl_1_bss_1B0[2]);
                    }
                    else {
                        lbl_1_bss_1B0[1] += 0.46153846f;
                        if (lbl_1_bss_1B0[1] > lbl_1_bss_EC) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                    }
                    if (lbl_1_bss_1BC[0] == 65) {
                        lbl_1_bss_1B0[1] = 150.0f;
                    }
                }
            }
            else if (lbl_1_bss_17C == 2) {
                lbl_1_bss_1B0[0] += 1.0f;
                if (lbl_1_bss_1B0[0] > 90.0f) {
                    lbl_1_bss_1B0[0] = 90.0f;
                }
                pos2d = lbl_1_data_178;
                pos2d.x += 420.0f;
                pos2d.x -= 420.0 * HuSin(lbl_1_bss_1B0[0]);
                pos2d.y -= lbl_1_bss_1B0[1];
                if (pos2d.x <= 616.0f) {
                    lbl_1_bss_1B0[1] = lbl_1_bss_1B0[1] - lbl_1_bss_1B0[1] / 9.0f;
                    if (pos2d.y > lbl_1_data_178.y) {
                        pos2d.y = lbl_1_data_178.y;
                    }
                }
                pos2d.y += 30.0f;
                pos2d.z += 700.0f;
                fn_1_6F5C(&pos2d);
                Hu3DModelRotSet(lbl_1_bss_120[0], 0.0f, -90.0f + lbl_1_bss_1B0[0], 0.0f);
                if (lbl_1_bss_1B0[0] == 90.0f) {
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_1B0[0] = 0.0f;
                    lbl_1_bss_17C = 0;
                    fn_1_6FF8(1);
                }
            }
            else {
                if (++lbl_1_bss_1BC[0] > 60) {
                    HuAudFXPanning(HuAudFXPlay(0x1D0), 56);
                    fn_1_A294(lbl_1_bss_188, 0);
                    fn_1_9D84(24);
                    lbl_1_bss_17C = 1;
                    fn_1_6D00(3);
                    lbl_1_bss_184 = 410;
                }
                else {
                    lbl_1_bss_1B0[0] += 0.7f;
                    Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f - lbl_1_bss_1B0[0], 0.0f);
                }
            }
            break;
        case 410:
            if (lbl_1_bss_17C == 1) {
                HuAudFXPanning(HuAudFXPlay(0x2F1), 56);
                fn_1_A294(lbl_1_bss_188, 0);
                fn_1_9D84(25);
                lbl_1_bss_17C = 2;
            }
            else if (lbl_1_bss_17C == 2) {
                if (fn_1_96CC(1)) {
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_17C = 0;
                }
            }
            else {
                if (++lbl_1_bss_1BC[0] > 30) {
                    HSFOBJECT *obj = Hu3DModelObjPtrGet(lbl_1_bss_140, "ske_head");
                    lbl_1_bss_EC = obj->mesh.curr.rot.z;
                    lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                    if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                        obj = Hu3DModelObjPtrGet(lbl_1_bss_140, "root_motion");
                        lbl_1_bss_F0 = obj->mesh.curr.rot.x;
                        lbl_1_bss_1B0[2] = lbl_1_bss_F0;
                    }
                    lbl_1_bss_1BC[0] = 0;
                    lbl_1_bss_1B0[0] = 0.0f;
                    lbl_1_bss_17C = 1;
                    fn_1_6D00(1);
                    fn_1_6FF8(2);
                    lbl_1_bss_184 = 411;
                }
            }
            break;
        case 411:
            if (lbl_1_bss_17C == 1) {
                if (++lbl_1_bss_1BC[0] >= 15) {
                    lbl_1_bss_1B0[0] += 2.6153846f;
                    if (lbl_1_bss_1B0[0] > 340.0f) {
                        lbl_1_bss_1B0[0] = 340.0f;
                    }
                    pos2d = lbl_1_data_178;
                    pos2d.y -= lbl_1_bss_1B0[0];
                    pos2d.y += 30.0f;
                    pos2d.z += 700.0f;
                    fn_1_6F5C(&pos2d);
                    if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                        lbl_1_bss_1B0[1] -= 0.07692308f;
                        if (lbl_1_bss_1B0[1] < lbl_1_bss_EC - 10.0f) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC - 10.0f;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                        lbl_1_bss_1B0[2] -= 0.07692308f;
                        if (lbl_1_bss_1B0[2] < lbl_1_bss_F0 - 10.0f) {
                            lbl_1_bss_1B0[2] = lbl_1_bss_F0 - 10.0f;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "root_motion", 0x80, lbl_1_bss_1B0[2]);
                        if (lbl_1_bss_1B0[1] == lbl_1_bss_EC - 10.0f && lbl_1_bss_1B0[2] == lbl_1_bss_F0 - 10.0f) {
                            lbl_1_bss_1BC[0] = 0;
                            lbl_1_bss_17C = 2;
                        }
                    }
                    else {
                        lbl_1_bss_1B0[1] -= 0.1923077f;
                        if (lbl_1_bss_1B0[1] < lbl_1_bss_EC - 25.0f) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC - 25.0f;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                        if (lbl_1_bss_1B0[1] == lbl_1_bss_EC - 25.0f) {
                            lbl_1_bss_1BC[0] = 0;
                            lbl_1_bss_17C = 2;
                        }
                    }
                }
            }
            else if (lbl_1_bss_17C == 2) {
                if (++lbl_1_bss_1BC[0] > 30) {
                    if (lbl_1_bss_134 == 2 || lbl_1_bss_134 == 5) {
                        lbl_1_bss_1B0[1] += 0.115384616f;
                        if (lbl_1_bss_1B0[1] > lbl_1_bss_EC) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                        if (lbl_1_bss_1B0[1] == lbl_1_bss_EC) {
                            lbl_1_bss_17C = 0;
                            lbl_1_bss_1B0[0] = 42.0f;
                        }
                        lbl_1_bss_1B0[2] += 0.115384616f;
                        if (lbl_1_bss_1B0[2] > lbl_1_bss_F0) {
                            lbl_1_bss_1B0[2] = lbl_1_bss_F0;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "root_motion", 0x80, lbl_1_bss_1B0[2]);
                    }
                    else {
                        lbl_1_bss_1B0[1] += 0.23076923f;
                        if (lbl_1_bss_1B0[1] > lbl_1_bss_EC) {
                            lbl_1_bss_1B0[1] = lbl_1_bss_EC;
                        }
                        Hu3DMotionForceSet(lbl_1_bss_140, "ske_head", 0x200, lbl_1_bss_1B0[1]);
                        if (lbl_1_bss_1B0[1] == lbl_1_bss_EC) {
                            lbl_1_bss_17C = 0;
                            lbl_1_bss_1B0[0] = 42.0f;
                        }
                    }
                }
            }
            else {
                lbl_1_bss_1B0[0] -= 0.7f;
                if (lbl_1_bss_1B0[0] < 0.0f) {
                    lbl_1_bss_1B0[0] = 0.0f;
                }
                Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f - lbl_1_bss_1B0[0], 0.0f);
                if (lbl_1_bss_1B0[0] == 0.0f) {
                    fn_1_6D00(2);
                    lbl_1_bss_184 = 412;
                }
            }
            break;
        case 412:
            fn_1_A294(lbl_1_bss_188, 0);
            fn_1_9D84(26);
            fn_1_6D00(3);
            lbl_1_bss_184 = 413;
            break;
        case 413:
            fn_1_9D84(27);
            lbl_1_bss_184 = 414;
            break;
        case 414:
            fn_1_9D84(28);
            lbl_1_bss_1BC[0] = 0;
            fn_1_6D00(1);
            lbl_1_bss_184 = 415;
            break;
        case 415:
            if (++lbl_1_bss_1BC[0] > 90) {
                fn_1_9D84(29);
                lbl_1_bss_184 = 416;
            }
            break;
        case 416:
            fn_1_9D84(30);
            lbl_1_bss_184 = 417;
            break;
        case 417:
            fn_1_9D84(31);
            lbl_1_bss_184 = 418;
            Hu3DCameraPosGet(2, (Vec *)&lbl_1_bss_18C[0], (Vec *)&lbl_1_bss_18C[6], (Vec *)&lbl_1_bss_18C[3]);
            lbl_1_bss_1BC[0] = 0;
            lbl_1_bss_1B0[0] = 0.0f;
            lbl_1_bss_1B0[1] = 0.0f;
            break;
        case 418:
            if (++lbl_1_bss_1BC[0] > 15) {
                float speed = 180.0f;
                Vec mdlPos = Hu3DData[lbl_1_bss_140].pos;
                Vec pos = *(Vec *)&lbl_1_bss_18C[0];
                Vec target = *(Vec *)&lbl_1_bss_18C[3];
                pos.x += (mdlPos.x - lbl_1_bss_18C[0]) * HuSin(lbl_1_bss_1B0[0]);
                if (lbl_1_bss_134 != 3) {
                    pos.y -= 15.0 * HuSin(lbl_1_bss_1B0[0]);
                }
                else {
                    pos.y -= -150.0 * HuSin(lbl_1_bss_1B0[0]);
                }
                pos.z -= 600.0 * HuSin(lbl_1_bss_1B0[0]);
                target.x += pos.x;
                target.y -= 20.0 * HuSin(lbl_1_bss_1B0[0]);
                Hu3DCameraPosSetV(1, &pos, (Vec *)&lbl_1_bss_18C[6], &target);
                Hu3DCameraPosSetV(2, &pos, (Vec *)&lbl_1_bss_18C[6], &target);
                Hu3DCameraPosSetV(4, &pos, (Vec *)&lbl_1_bss_18C[6], &target);
                lbl_1_bss_1B0[1] = 60.0 * HuSin(lbl_1_bss_1B0[0]);
                Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f + lbl_1_bss_1B0[1], 0.0f);
                lbl_1_bss_1B0[0] += 90.0f / speed;
                if (lbl_1_bss_1B0[0] >= 90.0f) {
                    fn_1_69CC(4);
                    result = 1;
                    lbl_1_bss_184 = 1000;
                }
            }
            break;
        case 500:
            if (fn_1_9EE8(0x20)) {
                lbl_1_bss_184 = lbl_1_bss_180;
            }
            else {
                result = -1;
                lbl_1_bss_184 = 1000;
            }
            break;
    }
    return result;
}

/* 152 insns */
/* player character model (charNo, 5 files from storymode+9) with its 4 motions; mot is 1-based */
void fn_1_66C4(s32 charNo, s32 mot)
{
    HU3DMOTID motId;

    Hu3DZClearLayerSet(15);
    lbl_1_bss_140 = Hu3DModelCreateData(DATA_storymode + charNo * 5 + 9);
    lbl_1_bss_138[0] = Hu3DJointMotionData(lbl_1_bss_140, DATA_storymode + charNo * 5 + 10);
    lbl_1_bss_138[1] = Hu3DJointMotionData(lbl_1_bss_140, DATA_storymode + charNo * 5 + 11);
    lbl_1_bss_138[2] = Hu3DJointMotionData(lbl_1_bss_140, DATA_storymode + charNo * 5 + 12);
    lbl_1_bss_138[3] = Hu3DJointMotionData(lbl_1_bss_140, DATA_storymode + charNo * 5 + 13);
    Hu3DMotionSet(lbl_1_bss_140, lbl_1_bss_138[mot - 1]);
    Hu3DModelCameraSet(lbl_1_bss_140, 2);
    Hu3DModelRotSet(lbl_1_bss_140, 0.0f, -60.0f, 0.0f);
    Hu3DModelLayerSet(lbl_1_bss_140, 6);
    if(mot != 4) {
        Hu3DModelAttrSet(lbl_1_bss_140, 0x40000001);
    }
    motId = Hu3DJointMotionData(lbl_1_bss_140, DATA_storymode + charNo + 0x62);
    Hu3DMotionOverlaySet(lbl_1_bss_140, motId);
    Hu3DModelAttrSet(lbl_1_bss_140, 0x40000200);
    lbl_1_bss_134 = charNo;
    lbl_1_bss_130 = mot;
}

/* 42 insns */
void fn_1_6924(HuVecF *pos)
{
    HuVecF pos2D;
    HuVecF pos3D;
    float height;

    pos2D = *pos;
    height = CharModelHeightGet(lbl_1_bss_134);
    pos2D.y += height * 0.5f;
    Hu3D2Dto3D(&pos2D, 2, &pos3D);
    Hu3DModelPosSetV(lbl_1_bss_140, &pos3D);
}

/* 56 insns */
void fn_1_69CC(s32 mot)
{
    if(mot != lbl_1_bss_130) {
        if(mot != 4) {
            Hu3DMotionShiftSet(lbl_1_bss_140, lbl_1_bss_138[mot - 1], 0.0f, 20.0f, 0x40000001);
        } else {
            Hu3DMotionShiftSet(lbl_1_bss_140, lbl_1_bss_138[mot - 1], 0.0f, 30.0f, 0);
        }
    }
    lbl_1_bss_130 = mot;
}

/* 35 insns */
void fn_1_6AAC(void)
{
    Hu3DMotionSet(lbl_1_bss_140, HU3D_MOTID_NONE);
    Hu3DMotionKill(lbl_1_bss_138[0]);
    Hu3DMotionKill(lbl_1_bss_138[1]);
    Hu3DMotionKill(lbl_1_bss_138[2]);
    Hu3DMotionKill(lbl_1_bss_138[3]);
    Hu3DModelKill(lbl_1_bss_140);
    Hu3DLayerHookSet(14, NULL);
}

/* 97 insns */
void fn_1_6B38(void)
{
    Hu3DZClearLayerSet(15);
    lbl_1_bss_12E = Hu3DModelCreateData(DATA_storymode + 0x57);
    lbl_1_bss_128[0] = Hu3DJointMotionData(lbl_1_bss_12E, DATA_storymode + 0x58);
    lbl_1_bss_128[1] = Hu3DJointMotionData(lbl_1_bss_12E, DATA_storymode + 0x59);
    lbl_1_bss_128[2] = Hu3DJointMotionData(lbl_1_bss_12E, DATA_storymode + 0x5A);
    Hu3DMotionSet(lbl_1_bss_12E, lbl_1_bss_128[0]);
    Hu3DModelCameraSet(lbl_1_bss_12E, 4);
    Hu3DModelRotSet(lbl_1_bss_12E, 0.0f, 30.0f, 0.0f);
    Hu3DModelLayerSet(lbl_1_bss_12E, 7);
    Hu3DModelAttrSet(lbl_1_bss_12E, 0x40000001);
    lbl_1_bss_124 = 1;
}

/* 17 insns */
void fn_1_6CBC(HuVecF *pos)
{
    HuVecF pos3D;

    Hu3D2Dto3D(pos, 4, &pos3D);
    Hu3DModelPosSetV(lbl_1_bss_12E, &pos3D);
}

/* 36 insns */
void fn_1_6D00(s32 mot)
{
    if(mot != lbl_1_bss_124) {
        Hu3DMotionShiftSet(lbl_1_bss_12E, lbl_1_bss_128[mot - 1], 0.0f, 20.0f, 0x40000001);
    }
    lbl_1_bss_124 = mot;
}

/* 31 insns */
void fn_1_6D90(void)
{
    Hu3DMotionSet(lbl_1_bss_12E, HU3D_MOTID_NONE);
    Hu3DMotionKill(lbl_1_bss_128[0]);
    Hu3DMotionKill(lbl_1_bss_128[1]);
    Hu3DMotionKill(lbl_1_bss_128[2]);
    Hu3DModelKill(lbl_1_bss_12E);
    Hu3DLayerHookSet(15, NULL);
}

/* 84 insns */
void fn_1_6E0C(void)
{
    Hu3DZClearLayerSet(15);
    lbl_1_bss_120[0] = Hu3DModelCreateData(DATA_storymode + 0x2C);
    lbl_1_bss_11C[0] = Hu3DJointMotionData(lbl_1_bss_120[0], DATA_storymode + 0x2D);
    lbl_1_bss_11C[1] = Hu3DJointMotionData(lbl_1_bss_120[0], DATA_storymode + 0x2E);
    Hu3DMotionSet(lbl_1_bss_120[0], lbl_1_bss_11C[0]);
    Hu3DModelCameraSet(lbl_1_bss_120[0], 2);
    Hu3DModelRotSet(lbl_1_bss_120[0], 0.0f, -60.0f, 0.0f);
    Hu3DModelLayerSet(lbl_1_bss_120[0], 5);
    Hu3DModelAttrSet(lbl_1_bss_120[0], 0x40000001);
    lbl_1_bss_118 = 1;
}

/* 39 insns */
void fn_1_6F5C(HuVecF *pos)
{
    HuVecF pos2D;
    HuVecF pos3D;
    float height;

    pos2D = *pos;
    height = CharModelHeightGet(7);
    pos2D.y += height * 0.5f;
    Hu3D2Dto3D(&pos2D, 2, &pos3D);
    Hu3DModelPosSetV(lbl_1_bss_120[0], &pos3D);
}

/* 36 insns */
void fn_1_6FF8(s32 mot)
{
    if(mot != lbl_1_bss_118) {
        Hu3DMotionShiftSet(lbl_1_bss_120[0], lbl_1_bss_11C[mot - 1], 0.0f, 20.0f, 0x40000001);
    }
    lbl_1_bss_118 = mot;
}

/* 27 insns */
void fn_1_7088(void)
{
    Hu3DMotionSet(lbl_1_bss_120[0], HU3D_MOTID_NONE);
    Hu3DMotionKill(lbl_1_bss_11C[0]);
    Hu3DMotionKill(lbl_1_bss_11C[1]);
    Hu3DModelKill(lbl_1_bss_120[0]);
    Hu3DLayerHookSet(13, NULL);
}

/* 197 insns */
/* the 16-motion model of the cutscene (set 0 for mot < 8, else set 1); mot is 1-based */
void fn_1_70F4(s32 mot)
{
    s32 set;
    s32 i;

    Hu3DZClearLayerSet(15);
    if(mot < 8) {
        lbl_1_bss_114 = Hu3DModelCreateData(DATA_storymode + 0x45);
        set = 0;
    } else {
        lbl_1_bss_114 = Hu3DModelCreateData(DATA_storymode + 0x4D);
        set = 1;
    }
    for(i = 0; i < 16; i++) {
        lbl_1_bss_F4[i] = Hu3DJointMotionData(lbl_1_bss_114, DATA_storymode + set + i + 0x46);
    }
    Hu3DMotionSet(lbl_1_bss_114, lbl_1_bss_F4[mot - 1]);
    Hu3DModelCameraSet(lbl_1_bss_114, 2);
    Hu3DModelRotSet(lbl_1_bss_114, 0.0f, (mot == 8) ? 0.0f : 60.0f, 0.0f);
    Hu3DModelLayerSet(lbl_1_bss_114, 7);
    if(mot == 1 || mot == 5 || mot == 6 || mot == 8 || mot == 10 || mot == 12 || mot == 14 || mot == 15 || mot == 16) {
        Hu3DModelAttrSet(lbl_1_bss_114, 0x40000001);
    } else if(mot == 13) {
        Hu3DModelAttrSet(lbl_1_bss_114, 0x40000001);
        Hu3DMotionAttrSet(lbl_1_bss_F4[mot - 1], 1);
    }
    if(mot == 8) {
        Hu3DModelAmbSet(lbl_1_bss_114, 0.0f, 0.0f, 0.0f);
        lbl_1_bss_BC[0] = Hu3DModelCreateData(DATA_storymode + 0x5C);
        Hu3DModelAttrSet(lbl_1_bss_BC[0], 0x40000002);
        Hu3DModelCameraSet(lbl_1_bss_BC[0], 2);
        Hu3DModelLayerSet(lbl_1_bss_BC[0], 7);
        Hu3DModelHookSet(lbl_1_bss_114, "itemhook_M", lbl_1_bss_BC[0]);
    }
    lbl_1_bss_E8 = mot;
}

/* 17 insns */
void fn_1_7408(HuVecF *pos)
{
    HuVecF pos3D;

    Hu3D2Dto3D(pos, 2, &pos3D);
    Hu3DModelPosSetV(lbl_1_bss_114, &pos3D);
}

/* 101 insns */
void fn_1_744C(s32 mot)
{
    if(mot != lbl_1_bss_E8) {
        if(mot == 1 || mot == 5 || mot == 6 || mot == 8 || mot == 10 || mot == 12 || mot == 14 || mot == 15 || mot == 16) {
            Hu3DMotionShiftSet(lbl_1_bss_114, lbl_1_bss_F4[mot - 1], 0.0f, 20.0f, 0x40000001);
        } else if(mot == 13) {
            Hu3DMotionShiftSet(lbl_1_bss_114, lbl_1_bss_F4[mot - 1], 0.0f, 20.0f, 0x40000001);
            Hu3DMotionAttrSet(lbl_1_bss_F4[mot - 1], 1);
        } else {
            Hu3DMotionShiftSet(lbl_1_bss_114, lbl_1_bss_F4[mot - 1], 0.0f, 20.0f, 0);
        }
    }
    lbl_1_bss_E8 = mot;
}

/* 32 insns */
void fn_1_75E0(void)
{
    s32 i;

    Hu3DMotionSet(lbl_1_bss_114, HU3D_MOTID_NONE);
    for(i = 0; i < 16; i++) {
        Hu3DMotionKill(lbl_1_bss_F4[i]);
    }
    Hu3DModelKill(lbl_1_bss_114);
    Hu3DLayerHookSet(15, NULL);
}

/* 353 insns */
/* chains fn_1_70F4's motions; created as a process but has no loop, so it runs one frame
   (retail) */
void fn_1_7660(void)
{
    if(Hu3DMotionEndCheck(lbl_1_bss_114)) {
        if(lbl_1_bss_E8 == 3 || lbl_1_bss_E8 == 4 || lbl_1_bss_E8 == 7) {
            fn_1_744C(1);
        } else if(lbl_1_bss_E8 == 9) {
            fn_1_744C(8);
        } else if(lbl_1_bss_E8 == 11) {
            fn_1_744C(12);
        }
    }
    if(lbl_1_bss_184 == 6 && HuWinStatGet(lbl_1_bss_60.winId) == 2) {
        fn_1_744C(16);
    }
    if(lbl_1_bss_184 == 0x130 && Hu3DMotionShiftIDGet(lbl_1_bss_114) == HU3D_MOTID_NONE) {
        if(lbl_1_bss_E8 == 6 && (HuPadBtnDown[0] & (PAD_BUTTON_A | PAD_BUTTON_B))) {
            fn_1_744C(7);
        }
        if(lbl_1_bss_E8 == 1) {
            lbl_1_bss_1BC[0] = 0;
            lbl_1_bss_17C = 1;
            lbl_1_bss_184 = 0x133;
        }
    }
    if(lbl_1_bss_E8 == 11) {
        lbl_1_bss_E4++;
        if(lbl_1_bss_E4 == 20) {
            HuAudFXPanning(HuAudFXPlay(0x59B), 56);
            fn_1_7E24(7);
        }
        if(lbl_1_bss_E4 >= 20) {
            Hu3DModelObjPosGet(lbl_1_bss_114, "itemhook_R", &Hu3DData[lbl_1_bss_E2].pos);
            Hu3DData[lbl_1_bss_E2].pos.x += 5.0f;
            Hu3DData[lbl_1_bss_E2].pos.y += -85.0f;
            Hu3DData[lbl_1_bss_E2].pos.z += 57.0f;
        }
    } else if(lbl_1_bss_E8 == 12) {
        Hu3DModelObjPosGet(lbl_1_bss_114, "itemhook_R", &Hu3DData[lbl_1_bss_E2].pos);
        Hu3DData[lbl_1_bss_E2].pos.x += 5.0f;
        Hu3DData[lbl_1_bss_E2].pos.y += -85.0f;
        Hu3DData[lbl_1_bss_E2].pos.z += 57.0f;
    }
    HuPrcVSleep();
}

/* 127 insns */
void fn_1_7BE4(void)
{
    s32 i;

    Hu3DZClearLayerSet(15);
    lbl_1_bss_E2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_storymode, 0x44), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 9; i++) {
        lbl_1_bss_D0[i] = Hu3DJointMotion(lbl_1_bss_E2, HuDataSelHeapReadNum(DATANUM(DATA_storymode, 0x3B) + i, HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DMotionSet(lbl_1_bss_E2, lbl_1_bss_D0[0]);
    Hu3DModelCameraSet(lbl_1_bss_E2, 2);
    Hu3DModelRotSet(lbl_1_bss_E2, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(lbl_1_bss_E2, 7);
    Hu3DModelAttrSet(lbl_1_bss_E2, HU3D_MOTATTR_LOOP);
    Hu3DModelAmbSet(lbl_1_bss_E2, 0.0f, 0.0f, 0.0f);
    lbl_1_bss_BC[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_storymode, 0x5D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_BC[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelCameraSet(lbl_1_bss_BC[1], 2);
    Hu3DModelLayerSet(lbl_1_bss_BC[1], 7);
    Hu3DModelHookSet(lbl_1_bss_E2, "itemhook_head", lbl_1_bss_BC[1]);
    lbl_1_bss_B8 = 1;
}

/* 17 insns */
void fn_1_7DE0(HuVecF *pos)
{
    HuVecF out;

    Hu3D2Dto3D(pos, 2, &out);
    Hu3DModelPosSetV(lbl_1_bss_E2, &out);
}

/* 93 insns */
void fn_1_7E24(s32 no)
{
    if (no != lbl_1_bss_B8) {
        if (no == 1 || no == 2 || no == 4 || no == 5 || no == 8) {
            Hu3DMotionShiftSet(lbl_1_bss_E2, lbl_1_bss_D0[no - 1], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
        } else if (no == 9) {
            Hu3DMotionShiftSet(lbl_1_bss_E2, lbl_1_bss_D0[no - 1], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionAttrSet(lbl_1_bss_D0[no - 1], 1);
        } else {
            Hu3DMotionShiftSet(lbl_1_bss_E2, lbl_1_bss_D0[no - 1], 0.0f, 20.0f, HU3D_MOTATTR_NONE);
        }
    }
    lbl_1_bss_B8 = no;
}

/* 32 insns */
void fn_1_7F98(void)
{
    s32 i;

    Hu3DMotionSet(lbl_1_bss_E2, -1);
    for (i = 0; i < 9; i++) {
        Hu3DMotionKill(lbl_1_bss_D0[i]);
    }
    Hu3DModelKill(lbl_1_bss_E2);
    Hu3DLayerHookSet(15, NULL);
}

/* 78 insns */
void fn_1_8018(void)
{
    if (Hu3DMotionEndCheck(lbl_1_bss_E2)) {
        if (lbl_1_bss_B8 == 3 || lbl_1_bss_B8 == 6) {
            if (lbl_1_bss_B8 != 4) {
                Hu3DMotionShiftSet(lbl_1_bss_E2, lbl_1_bss_D0[3], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
            }
            lbl_1_bss_B8 = 4;
        } else if (lbl_1_bss_B8 == 7) {
            if (lbl_1_bss_B8 != 8) {
                Hu3DMotionShiftSet(lbl_1_bss_E2, lbl_1_bss_D0[7], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
            }
            lbl_1_bss_B8 = 8;
        }
    }
    HuPrcVSleep();
}

/* 633 insns */
s32 fn_1_8150(s32 arg0)
{
    s32 charNo;
    s16 mdlId;
    s32 ret;
    float rotX;
    float rotY;
    float rotZ;
    STORY_PARWORK *work;
    HuVecF pos;

    ret = 0;
    mdlId = (arg0 == 0) ? lbl_1_bss_140 : lbl_1_bss_120[0];
    switch (lbl_1_bss_178) {
        case 0:
            lbl_1_bss_15C[0] = 0.0f;
            lbl_1_bss_15C[1] = 0.0f;
            lbl_1_bss_15C[2] = 0.0f;
            lbl_1_bss_15C[3] = 1.0f;
            if (arg0 == 0) {
                if (lbl_1_bss_130 != 2) {
                    Hu3DMotionShiftSet(lbl_1_bss_140, lbl_1_bss_138[1], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                }
                lbl_1_bss_130 = 2;
            } else {
                if (lbl_1_bss_118 != 2) {
                    Hu3DMotionShiftSet(lbl_1_bss_120[0], lbl_1_bss_11C[1], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                }
                lbl_1_bss_118 = 2;
            }
            lbl_1_bss_178++;
            work = lbl_1_bss_58[0];
            Hu3DParManPosSet(work->parManId[0], Hu3DData[mdlId].pos.x, Hu3DData[mdlId].pos.y, Hu3DData[mdlId].pos.z);
            Hu3DParManTimeLimitSet(work->parManId[0], 2);
            Hu3DParManAttrReset(work->parManId[0], 1);
            fn_1_1280(0x580, mdlId, 2);
            break;
        case 1:
            pos = lbl_1_data_178;
            pos.x += 120.0f;
            pos.x -= 288.0 * cos(M_PI * (-90.0f + lbl_1_bss_15C[0]) / 180.0);
            if (arg0 != 0) {
                charNo = 7;
            } else {
                charNo = lbl_1_bss_134;
            }
            pos.y += 1.3f * (120.0f + lbl_1_data_184[charNo] / 2.0f) * sin(M_PI * lbl_1_bss_15C[1] / 180.0);
            if (arg0 == 0) {
                HuVecF out;
                HuVecF pos2;
                float height;

                pos2 = pos;
                height = CharModelHeightGet(lbl_1_bss_134);
                pos2.y += height * 0.5f;
                Hu3D2Dto3D(&pos2, 2, &out);
                Hu3DModelPosSetV(lbl_1_bss_140, &out);
            } else {
                HuVecF out;
                HuVecF pos2;
                float height;

                pos2 = pos;
                height = CharModelHeightGet(7);
                pos2.y += height * 0.5f;
                Hu3D2Dto3D(&pos2, 2, &out);
                Hu3DModelPosSetV(lbl_1_bss_120[0], &out);
            }
            lbl_1_bss_15C[0] += 1.6f;
            if (lbl_1_bss_15C[0] > 160.0f) {
                lbl_1_bss_15C[0] = 160.0f;
            }
            lbl_1_bss_15C[1] -= 1.6f;
            if (lbl_1_bss_15C[1] > 160.0f) {
                lbl_1_bss_15C[1] = 160.0f;
            }
            lbl_1_bss_15C[2] += 0.9f;
            if (lbl_1_bss_15C[2] > 90.0f) {
                lbl_1_bss_15C[2] = 90.0f;
            }
            rotX = (lbl_1_bss_15C[2] < 45.0f) ? 0.0f : lbl_1_bss_15C[2] - 45.0f;
            rotY = -60.0 - 180.0 * sin(M_PI * lbl_1_bss_15C[2] / 180.0);
            rotZ = 0.0f;
            Hu3DModelRotSet(mdlId, rotX, rotY, rotZ);
            lbl_1_bss_15C[3] -= 0.01f;
            if (lbl_1_bss_15C[3] < 0.0f) {
                lbl_1_bss_15C[3] = 0.0f;
            }
            Hu3DModelScaleSet(mdlId, lbl_1_bss_15C[3], lbl_1_bss_15C[3], lbl_1_bss_15C[3]);
            if (0.0f == lbl_1_bss_15C[3]) {
                if (lbl_1_bss_184 < 300 && arg0 == 0) {
                    lbl_1_bss_178 = 2;
                } else {
                    lbl_1_bss_178 = 0;
                    ret = 1;
                }
            }
            if (lbl_1_bss_15C[3] > 0.1f) {
                STORY_PARWORK *work2 = lbl_1_bss_58[0];

                Hu3DParManPosSet(work2->parManId[0], Hu3DData[mdlId].pos.x, Hu3DData[mdlId].pos.y, Hu3DData[mdlId].pos.z);
                Hu3DParManTimeLimitSet(work2->parManId[0], 2);
                Hu3DParManAttrReset(work2->parManId[0], 1);
            }
            if (lbl_1_bss_184 < 300) {
                Hu3DModelRotSet(lbl_1_bss_12E, 0.0f, 30.0 + 120.0 * sin(M_PI * lbl_1_bss_15C[2] / 180.0), 0.0f);
            }
            fn_1_1280(0x8580, mdlId, 2);
            break;
        case 2:
            lbl_1_bss_15C[2] -= 0.9f;
            if (lbl_1_bss_15C[2] < 0.0f) {
                lbl_1_bss_15C[2] = 0.0f;
                lbl_1_bss_178 = 0;
                ret = 1;
            }
            Hu3DModelRotSet(lbl_1_bss_12E, 0.0f, 30.0 + 120.0 * (1.0 - cos(M_PI * lbl_1_bss_15C[2] / 180.0)), 0.0f);
            break;
    }
    return ret;
}

/* 390 insns */
s32 fn_1_8B34(void)
{
    s32 ret;
    s16 mdlId;
    float rotX;
    float rotY;
    float rotZ;
    STORY_PARWORK *work;
    HuVecF pos;
    HuVecF out;

    ret = 0;
    mdlId = lbl_1_bss_114;
    switch (lbl_1_bss_170) {
        case 0:
            lbl_1_bss_144[0] = 0.0f;
            lbl_1_bss_144[1] = 0.0f;
            lbl_1_bss_144[2] = 0.0f;
            lbl_1_bss_144[3] = 1.0f;
            if (lbl_1_bss_E8 != 2) {
                Hu3DMotionShiftSet(lbl_1_bss_114, lbl_1_bss_F4[1], 0.0f, 20.0f, HU3D_MOTATTR_NONE);
            }
            lbl_1_bss_E8 = 2;
            lbl_1_bss_170++;
            work = lbl_1_bss_58[1];
            Hu3DParManPosSet(work->parManId[0], Hu3DData[mdlId].pos.x, Hu3DData[mdlId].pos.y, Hu3DData[mdlId].pos.z);
            Hu3DParManTimeLimitSet(work->parManId[0], 2);
            Hu3DParManAttrReset(work->parManId[0], 1);
            fn_1_1280(0x580, mdlId, 2);
            break;
        case 1:
            pos = lbl_1_data_178;
            pos.x -= 140.0f;
            pos.x += 336.0 * cos(M_PI * (-90.0f + lbl_1_bss_144[0]) / 180.0);
            pos.y += 156.0 * sin(M_PI * lbl_1_bss_144[1] / 180.0);
            Hu3D2Dto3D(&pos, 2, &out);
            Hu3DModelPosSetV(lbl_1_bss_114, &out);
            lbl_1_bss_144[0] += 1.6f;
            if (lbl_1_bss_144[0] > 160.0f) {
                lbl_1_bss_144[0] = 160.0f;
            }
            lbl_1_bss_144[1] -= 1.85f;
            if (lbl_1_bss_144[1] > 185.0f) {
                lbl_1_bss_144[1] = 185.0f;
            }
            lbl_1_bss_144[2] += 0.9f;
            if (lbl_1_bss_144[2] > 90.0f) {
                lbl_1_bss_144[2] = 90.0f;
            }
            rotX = 0.0f;
            rotY = 60.0 + 180.0 * sin(M_PI * lbl_1_bss_144[2] / 180.0);
            rotZ = 0.0f;
            Hu3DModelRotSet(mdlId, rotX, rotY, rotZ);
            lbl_1_bss_144[3] -= 0.01f;
            if (lbl_1_bss_144[3] < 0.0f) {
                lbl_1_bss_144[3] = 0.0f;
            }
            Hu3DModelScaleSet(mdlId, lbl_1_bss_144[3], lbl_1_bss_144[3], lbl_1_bss_144[3]);
            if (0.0f == lbl_1_bss_144[3]) {
                lbl_1_bss_170 = 0;
                ret = 1;
            }
            if (lbl_1_bss_144[3] > 0.1f) {
                STORY_PARWORK *work2 = lbl_1_bss_58[1];

                Hu3DParManPosSet(work2->parManId[0], Hu3DData[mdlId].pos.x, Hu3DData[mdlId].pos.y, Hu3DData[mdlId].pos.z);
                Hu3DParManTimeLimitSet(work2->parManId[0], 2);
                Hu3DParManAttrReset(work2->parManId[0], 1);
            }
            fn_1_1280(0x8580, mdlId, 2);
            break;
    }
    return ret;
}

/* 352 insns */
s32 fn_1_914C(void)
{
    s32 ret;
    s16 mdlId;
    float time;
    s16 seId;
    HuVecF pos;
    HuVecF out;

    ret = 0;
    mdlId = lbl_1_bss_114;
    switch (lbl_1_bss_178) {
        case 0:
            lbl_1_bss_15C[0] = 0.0f;
            lbl_1_bss_15C[1] = 0.0f;
            lbl_1_bss_178++;
            break;
        case 1:
            lbl_1_bss_15C[1] += 0.9230769f;
            if (lbl_1_bss_15C[1] > 60.0f) {
                lbl_1_bss_15C[1] = 60.0f;
            }
            Hu3DModelRotSet(mdlId, 0.0f, 60.0 + 180.0 * sin(M_PI * lbl_1_bss_15C[1] / 180.0), 0.0f);
            if (60.0f == lbl_1_bss_15C[1]) {
                lbl_1_bss_15C[0] = 0.0f;
                lbl_1_bss_15C[1] = 0.0f;
                lbl_1_bss_15C[2] = 0.0f;
                lbl_1_bss_15C[3] = 0.0f;
                lbl_1_bss_16C = 0;
                if (lbl_1_bss_E8 != 5) {
                    Hu3DMotionShiftSet(lbl_1_bss_114, lbl_1_bss_F4[4], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                }
                lbl_1_bss_E8 = 5;
                lbl_1_bss_178++;
            }
            break;
        case 2:
            if (lbl_1_bss_E8 == 5) {
                time = Hu3DMotionTimeGet(lbl_1_bss_114);
                seId = (10.0f == time) ? 0x581 : (60.0f == time) ? 0x582 : (10.0f == lbl_1_bss_15C[3]) ? 0x581 : -1;
                if (seId != -1) {
                    fn_1_1280(seId, lbl_1_bss_114, 2);
                }
                lbl_1_bss_15C[3] += 1.0f;
            }
            lbl_1_bss_15C[0] += 0.003f;
            if (lbl_1_bss_15C[0] > 1.0f) {
                lbl_1_bss_15C[0] = 1.0f;
            }
            Hu3DModelScaleSet(lbl_1_bss_114, 1.0f - lbl_1_bss_15C[0], 1.0f - lbl_1_bss_15C[0], 1.0f - lbl_1_bss_15C[0]);
            lbl_1_bss_15C[1] += 0.7f;
            lbl_1_bss_15C[2] += 1.0f;
            pos = lbl_1_data_178;
            pos.x -= 140.0f;
            pos.x -= lbl_1_bss_15C[1];
            pos.y -= lbl_1_bss_15C[2];
            Hu3D2Dto3D(&pos, 2, &out);
            Hu3DModelPosSetV(lbl_1_bss_114, &out);
            if (++lbl_1_bss_16C >= 260.0f) {
                lbl_1_bss_178 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 129 insns */
s32 fn_1_96CC(s32 arg0)
{
    s32 ret;
    s16 mdlId;
    HSFOBJECT *obj;

    ret = 0;
    mdlId = (arg0 == 0) ? lbl_1_bss_140 : lbl_1_bss_120[0];
    if (lbl_1_bss_174 == 0) {
        obj = Hu3DModelObjPtrGet(mdlId, "ske_head");
        lbl_1_bss_154[1] = obj->mesh.curr.rot.z;
        lbl_1_bss_154[0] = 0.0f;
        lbl_1_bss_174 = 1;
    } else if (lbl_1_bss_174 == 1) {
        lbl_1_bss_154[0] += 1.5f;
        if (lbl_1_bss_154[0] > 18.0f) {
            lbl_1_bss_154[0] = 18.0f;
            lbl_1_bss_174 = 2;
        }
    } else {
        lbl_1_bss_154[0] -= 1.5f;
        if (lbl_1_bss_154[0] < 0.0f) {
            lbl_1_bss_154[0] = 0.0f;
            lbl_1_bss_174 = 0;
            ret = 1;
        }
    }
    Hu3DMotionForceSet(mdlId, "ske_head", 0x200, lbl_1_bss_154[1] + lbl_1_bss_154[0]);
    return ret;
}

/* 0x1F4 */ u32 lbl_1_data_1F4[54] = { DATA_capsulechar0, DATANUM(DATA_capsulechar0, 3), DATANUM(DATA_capsulechar0, 4), DATANUM(DATA_capsulechar0, 5), DATANUM(DATA_capsulechar0, 6), DATANUM(DATA_capsulechar0, 29), DATANUM(DATA_capsulechar0, 30), DATANUM(DATA_capsulechar0, 31), DATANUM(DATA_capsulechar0, 32), DATANUM(DATA_capsulechar0, 33), DATANUM(DATA_capsulechar0, 34), DATANUM(DATA_capsulechar0, 35), DATANUM(DATA_capsulechar0, 37), DATANUM(DATA_capsulechar0, 8), DATANUM(DATA_capsulechar0, 9), DATANUM(DATA_capsulechar0, 11), DATANUM(DATA_capsulechar0, 12), DATANUM(DATA_capsulechar0, 14), DATANUM(DATA_capsulechar0, 15), DATANUM(DATA_capsulechar0, 16), DATANUM(DATA_capsulechar0, 17), DATANUM(DATA_capsulechar0, 18), DATANUM(DATA_capsulechar0, 19), DATANUM(DATA_capsulechar0, 20), DATANUM(DATA_capsulechar0, 21), DATANUM(DATA_capsulechar0, 22), DATANUM(DATA_capsulechar0, 23), DATANUM(DATA_capsulechar0, 24), DATANUM(DATA_capsulechar0, 25), DATANUM(DATA_capsulechar0, 26), DATANUM(DATA_capsulechar0, 27), DATANUM(DATA_capsulechar0, 28), DATANUM(DATA_capsulechar0, 2), DATANUM(DATA_capsulechar0, 1), DATANUM(DATA_capsulechar0, 7), DATANUM(DATA_capsulechar0, 10), DATANUM(DATA_capsulechar0, 13), DATANUM(DATA_capsulechar0, 36), DATANUM(DATA_capsulechar0, 38), DATANUM(DATA_capsulechar0, 39), DATANUM(DATA_capsulechar0, 40), DATANUM(DATA_capsulechar0, 41), DATANUM(DATA_capsulechar0, 42), DATANUM(DATA_capsulechar0, 43), DATANUM(DATA_capsulechar0, 44), DATANUM(DATA_capsulechar0, 45), DATANUM(DATA_capsulechar0, 46), DATANUM(DATA_capsulechar0, 47), DATANUM(DATA_capsulechar0, 48), DATANUM(DATA_capsulechar0, 49), DATANUM(DATA_capsulechar0, 50), DATANUM(DATA_capsulechar0, 51), DATANUM(DATA_capsulechar0, 52), DATANUM(DATA_capsulechar0, 53) };

/* 204 insns */
void fn_1_98D0(s32 mesNo)
{
    s32 i;
    u32 mes;
    void *data;
    HUWIN *win;
    float posY;
    HuVec2f size;

    if (lbl_1_bss_60.winId != -1) {
        HuWinExKill(lbl_1_bss_60.winId);
    }
    if (lbl_1_bss_60.winSprId != -1) {
        HuWinSprKill(lbl_1_bss_60.winId, lbl_1_bss_60.winSprId);
        HuSprAnimKill(lbl_1_bss_60.anim);
    }
    for (i = 0; lbl_1_bss_60.insertMes[i] != -1; i++) {
        HuWinInsertMesSizeGet(lbl_1_bss_60.insertMes[i], i);
    }
    mes = lbl_1_data_1F4[mesNo];
    HuWinMesMaxSizeGet(1, &size, (u32)mes);
    posY = (mesNo < 41) ? 340.0f : 360.0f;
    lbl_1_bss_60.winId = HuWinExCreateFrame(-10000.0f, posY, size.x, size.y, -1, 0);
    if (lbl_1_bss_60.animDataNum != -1) {
        data = HuDataSelHeapReadNum(lbl_1_bss_60.animDataNum, HU_MEMNUM_OVL, HEAP_MODEL);
        lbl_1_bss_60.anim = HuSprAnimRead(data);
        lbl_1_bss_60.winSprId = HuWinAnimSet(lbl_1_bss_60.winId, lbl_1_bss_60.anim, 0, 48.0f, size.y / 2.0f);
    }
    if (lbl_1_bss_60.unk0 == 0) {
        HuWinExOpen(lbl_1_bss_60.winId);
    } else {
        HuWinDispOn(lbl_1_bss_60.winId);
    }
    for (i = 0; lbl_1_bss_60.insertMes[i] != -1; i++) {
        HuWinInsertMesSet(lbl_1_bss_60.winId, lbl_1_bss_60.insertMes[i], i);
    }
    HuWinMesSpeedSet(lbl_1_bss_60.winId, lbl_1_bss_60.mesSpeed);
    HuWinMesSet(lbl_1_bss_60.winId, mes);
    win = &winData[lbl_1_bss_60.winId];
    win->padMask = 1;
    win->disablePlayer = 14;
}

/* 51 insns */
void fn_1_9C00(void)
{
    if (lbl_1_bss_60.winId != -1) {
        HuWinMesWait(lbl_1_bss_60.winId);
        if (lbl_1_bss_60.unk0 == 0) {
            HuWinExClose(lbl_1_bss_60.winId);
        }
        if (lbl_1_bss_60.winSprId != -1) {
            HuWinSprKill(lbl_1_bss_60.winId, lbl_1_bss_60.winSprId);
            HuSprAnimKill(lbl_1_bss_60.anim);
        }
        HuWinExKill(lbl_1_bss_60.winId);
        fn_1_9CCC(1);
    }
}

/* 46 insns */
void fn_1_9CCC(s32 arg0)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        lbl_1_bss_60.insertMes[i] = -1;
    }
    lbl_1_bss_60.winId = -1;
    lbl_1_bss_60.mesSpeed = 1;
    lbl_1_bss_60.unk0 = 0;
    lbl_1_bss_60.animDataNum = lbl_1_bss_60.winSprId = -1;
    lbl_1_bss_60.anim = NULL;
    if (arg0 == 0) {
        lbl_1_bss_60.unk38 = -1;
    }
}

/* 89 insns */
void fn_1_9D84(s32 mesNo)
{
    fn_1_98D0(mesNo);
    if (lbl_1_bss_60.winId != -1) {
        HuWinMesWait(lbl_1_bss_60.winId);
        if (lbl_1_bss_60.unk0 == 0) {
            HuWinExClose(lbl_1_bss_60.winId);
        }
        if (lbl_1_bss_60.winSprId != -1) {
            HuWinSprKill(lbl_1_bss_60.winId, lbl_1_bss_60.winSprId);
            HuSprAnimKill(lbl_1_bss_60.anim);
        }
        HuWinExKill(lbl_1_bss_60.winId);
        fn_1_9CCC(1);
    }
}

/* 235 insns */
s32 fn_1_9EE8(s32 mesNo)
{
    HUWIN *win;
    s32 choice;
    s32 dataNum;

    fn_1_98D0(mesNo);
    win = &winData[lbl_1_bss_60.winId];
    win->padMask = 1 << GwPlayerConf[0].padNo;
    choice = HuWinChoiceGet(lbl_1_bss_60.winId, (mesNo == 32) ? 1 : 0);
    if (lbl_1_bss_60.winId != -1) {
        HuWinMesWait(lbl_1_bss_60.winId);
        if (lbl_1_bss_60.unk0 == 0) {
            HuWinExClose(lbl_1_bss_60.winId);
        }
        if (lbl_1_bss_60.winSprId != -1) {
            HuWinSprKill(lbl_1_bss_60.winId, lbl_1_bss_60.winSprId);
            HuSprAnimKill(lbl_1_bss_60.anim);
        }
        HuWinExKill(lbl_1_bss_60.winId);
        fn_1_9CCC(1);
    }
    if (GwCommon.storyNo != -2 && GwCommon.storyNo < 5 && mesNo != 32 && mesNo != 35 && mesNo != 36 && choice == 0) {
        if (GwCommon.storyNo == -3) {
            GwCommon.storyNo = 0;
        }
        dataNum = (GwCommon.storyBoardNo[GwCommon.storyNo] == 0) ? DATA_w01s
            : (GwCommon.storyBoardNo[GwCommon.storyNo] == 1) ? DATA_w02s
            : (GwCommon.storyBoardNo[GwCommon.storyNo] == 2) ? DATA_w03s
            : (GwCommon.storyBoardNo[GwCommon.storyNo] == 3) ? DATA_w04s
            : (GwCommon.storyBoardNo[GwCommon.storyNo] == 4) ? DATA_w05s
            : (GwCommon.storyBoardNo[GwCommon.storyNo] == 5) ? DATA_w06s
            : DATA_w07s;
        fn_1_19C(dataNum);
    }
    return choice;
}

/* 0x2CC */ s32 lbl_1_data_2CC[10] = { 0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9 };

/* 9 insns */
void fn_1_A294(s32 no, s32 unused)
{
    lbl_1_bss_60.insertMes[0] = lbl_1_data_2CC[no];
}







