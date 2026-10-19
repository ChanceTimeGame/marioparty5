/*
 * carddll player.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/player.s.
 */

/* player calls Hu3D2Dto3D / Hu3D3Dto2D unprototyped (an mr after these void calls): hide their
 * prototypes from CW only */
#ifdef __MWERKS__
#define Hu3D2Dto3D Hu3D2Dto3D_hidden
#define Hu3D3Dto2D Hu3D3Dto2D_hidden
#endif
#include "REL/carddll.h"
#ifdef __MWERKS__
#undef Hu3D2Dto3D
#undef Hu3D3Dto2D
#endif

#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#endif
#include "game/esprite.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_220 = 0.3f; /* 0x220 */
static const float lbl_1_rodata_224 = 200.0f; /* 0x224 */
static const float lbl_1_rodata_228 = 540.0f; /* 0x228 */
static const float lbl_1_rodata_22C = 576.0f; /* 0x22C */
/* 0x230 lbl_1_rodata_230 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x238 lbl_1_rodata_238 (0xC): 0x43900000 0x43200000 0x44E10000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_244 = 6.0f; /* 0x244 */
static const float lbl_1_rodata_248 = 15.0f; /* 0x248 */
static const float lbl_1_rodata_24C = 0.0f; /* 0x24C */
static const float lbl_1_rodata_250 = -50.0f; /* 0x250 */
/* 0x254 lbl_1_rodata_254 (0x8): 0x43B00000 0x43B00000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_25C = 288.0f; /* 0x25C */
static const float lbl_1_rodata_260 = 0.5f; /* 0x260 */
static const float lbl_1_rodata_264 = 78.0f; /* 0x264 */
/* 0x268 lbl_1_rodata_268 (0xC): 0x43900000 0x43A00000 0x44BB8000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_274 = 240.0f; /* 0x274 */
static const float lbl_1_rodata_278 = 400.0f; /* 0x278 */
static const double lbl_1_rodata_280 = 0.03; /* 0x280 */
static const float lbl_1_rodata_288 = 1.0f; /* 0x288 */
static const float lbl_1_rodata_28C = 20.0f; /* 0x28C */
static const float lbl_1_rodata_290 = 5.0f; /* 0x290 */
static const float lbl_1_rodata_294 = 40.0f; /* 0x294 */
static const double lbl_1_rodata_298 = 0.05; /* 0x298 */
static const float lbl_1_rodata_2A0 = 2.0f; /* 0x2A0 */
/* 0x2A4 lbl_1_rodata_2A4 (0xC): 0x43900000 0x43160000 0x44BB8000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_2B0 = 0.05f; /* 0x2B0 */
static const float lbl_1_rodata_2B4 = -360.0f; /* 0x2B4 */
static const float lbl_1_rodata_2B8 = 210.0f; /* 0x2B8 */
static const float lbl_1_rodata_2BC = 100.0f; /* 0x2BC */
static const double lbl_1_rodata_2C0 = 0.06; /* 0x2C0 */
/* 0x2C8 lbl_1_rodata_2C8 (0xC): 0x43900000 0x43700000 0x44E10000 -- an aggregate initialiser, write it as a local */
/* 0x2D4 lbl_1_rodata_2D4 (0xC): 0x42880000 0x435C0000 0x44E10000 -- an aggregate initialiser, write it as a local */
/* 0x2E0 lbl_1_rodata_2E0 (0xC): 0x43FE0000 0x435C0000 0x44E10000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_2EC = 3000.0f; /* 0x2EC */
static const float lbl_1_rodata_2F0 = 1800.0f; /* 0x2F0 */
static const float lbl_1_rodata_2F4 = -500.0f; /* 0x2F4 */
static const float lbl_1_rodata_2F8 = 300.0f; /* 0x2F8 */
static const float lbl_1_rodata_2FC = 180.0f; /* 0x2FC */
static const float lbl_1_rodata_300 = 80.0f; /* 0x300 */
static const float lbl_1_rodata_304 = 50.0f; /* 0x304 */
static const float lbl_1_rodata_308 = 480.0f; /* 0x308 */
static const float lbl_1_rodata_30C = 1200.0f; /* 0x30C */
static const float lbl_1_rodata_310 = -275.0f; /* 0x310 */
static const float lbl_1_rodata_314 = 150.0f; /* 0x314 */
static const float lbl_1_rodata_318 = -200.0f; /* 0x318 */
static const float lbl_1_rodata_31C = 360.0f; /* 0x31C */
static const float lbl_1_rodata_320 = 500.0f; /* 0x320 */
static const float lbl_1_rodata_324 = -1.0f; /* 0x324 */
static const float lbl_1_rodata_328 = 60.0f; /* 0x328 */
static const float lbl_1_rodata_32C = -4800.0f; /* 0x32C */
static const float lbl_1_rodata_330 = 1140.0f; /* 0x330 */
static const float lbl_1_rodata_334 = 72.0f; /* 0x334 */
static const float lbl_1_rodata_338 = 10.0f; /* 0x338 */
static const float lbl_1_rodata_33C = 0.25f; /* 0x33C */
static const float lbl_1_rodata_340 = 170.0f; /* 0x340 */
static const float lbl_1_rodata_344 = 3.0f; /* 0x344 */
static const float lbl_1_rodata_348 = 0.02f; /* 0x348 */
static const float lbl_1_rodata_34C = 0.2f; /* 0x34C */
static const float lbl_1_rodata_350 = 18.0f; /* 0x350 */
static const float lbl_1_rodata_354 = 1500.0f; /* 0x354 */
static const double lbl_1_rodata_358 = 0.02; /* 0x358 */
static const float lbl_1_rodata_360 = 350.0f; /* 0x360 */
static const float lbl_1_rodata_364 = 25.0f; /* 0x364 */
static const float lbl_1_rodata_368 = 2.5f; /* 0x368 */
/* 0x36C lbl_1_rodata_36C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x378 lbl_1_rodata_378 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
/* 0x384 lbl_1_rodata_384 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x390 lbl_1_rodata_390 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_39C = 30.0f; /* 0x39C */
static const float lbl_1_rodata_3A0 = 11000.0f; /* 0x3A0 */
static const float lbl_1_rodata_3A4 = 31.0f; /* 0x3A4 */
static const double lbl_1_rodata_3A8 = 180.0; /* 0x3A8 */
static const double lbl_1_rodata_3B0 = 3.141592653589793; /* 0x3B0 */
/* 0x3B8 lbl_1_rodata_3B8 (0xC): 0x00000000 0x455AC000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_3C4 = 3500.0f; /* 0x3C4 */
static const float lbl_1_rodata_3C8 = 2000.0f; /* 0x3C8 */
static const float lbl_1_rodata_3CC = -150.0f; /* 0x3CC */
static const float lbl_1_rodata_3D0 = 0.12f; /* 0x3D0 */
static const float lbl_1_rodata_3D4 = 370.0f; /* 0x3D4 */
static const float lbl_1_rodata_3D8 = 90.0f; /* 0x3D8 */
static const float lbl_1_rodata_3DC = 0.15f; /* 0x3DC */
static const float lbl_1_rodata_3E0 = 322.0f; /* 0x3E0 */
static const float lbl_1_rodata_3E4 = 0.7f; /* 0x3E4 */
static const float lbl_1_rodata_3E8 = 1000.0f; /* 0x3E8 */
static const float lbl_1_rodata_3EC = 2.8f; /* 0x3EC */
static const float lbl_1_rodata_3F0 = 160.0f; /* 0x3F0 */
static const float lbl_1_rodata_3F4 = 1080.0f; /* 0x3F4 */
static const float lbl_1_rodata_3F8 = 108.0f; /* 0x3F8 */
static const float lbl_1_rodata_3FC = 2160.0f; /* 0x3FC */
static const float lbl_1_rodata_400 = 36.0f; /* 0x400 */
static const float lbl_1_rodata_404 = 2880.0f; /* 0x404 */
static const float lbl_1_rodata_408 = 0.0125f; /* 0x408 */
static const float lbl_1_rodata_40C = 0.35f; /* 0x40C */
/* 0x410 lbl_1_rodata_410 (0xC): 0x3F800000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_41C = 1.6f; /* 0x41C */
static const float lbl_1_rodata_420 = 0.08f; /* 0x420 */
/* 0x424 lbl_1_rodata_424 (0x14): 0x72, 0x6F, 0x30, 0x30, 0x30, 0x00, 0x72, 0x6F 0x30, 0x30, 0x32, 0x00, 0x72, 0x6F, 0x30, 0x30 0x31, 0x00, 0x00, 0x00 -- an aggregate initialiser, write it as a local */
/* 0x438 lbl_1_rodata_438 (0xC): 0x42B40000 0x00000000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x444 lbl_1_rodata_444 (0xC): 0x42B40000 0xC1200000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x450 lbl_1_rodata_450 (0xC): 0x42B40000 0x00000000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x45C lbl_1_rodata_45C (0xC): 0x42B40000 0xC1200000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x468 lbl_1_rodata_468 (0xC): 0x42B40000 0xC1200000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x474 lbl_1_rodata_474 (0xC): 0x42B40000 0x00000000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x480 lbl_1_rodata_480 (0xC): 0x42B40000 0x00000000 0xC0800000 -- an aggregate initialiser, write it as a local */
/* 0x48C lbl_1_rodata_48C (0xC): 0x42B40000 0xC1200000 0xC0800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_498 = 12.0f; /* 0x498 */
static const float lbl_1_rodata_49C = 13.0f; /* 0x49C */
static const float lbl_1_rodata_4A0 = 0.13f; /* 0x4A0 */
static const float lbl_1_rodata_4A4 = 155.0f; /* 0x4A4 */
static const float lbl_1_rodata_4A8 = 7.0f; /* 0x4A8 */
static const float lbl_1_rodata_4AC = 0.017453292f; /* 0x4AC */
static const float lbl_1_rodata_4B0 = 75.0f; /* 0x4B0 */
static const float lbl_1_rodata_4B4 = 5000.0f; /* 0x4B4 */
static const float lbl_1_rodata_4B8 = 4700.0f; /* 0x4B8 */
static const float lbl_1_rodata_4BC = 4900.0f; /* 0x4BC */
static const float lbl_1_rodata_4C0 = 0.01f; /* 0x4C0 */
static const float lbl_1_rodata_4C4 = 0.99f; /* 0x4C4 */
/* 0x4C8 lbl_1_rodata_4C8 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x4D0 lbl_1_rodata_4D0 (0xC): 0x43900000 0x43160000 0x44BB8000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_4DC = -90.0f; /* 0x4DC */
static const float lbl_1_rodata_4E0 = 900.0f; /* 0x4E0 */
static const float lbl_1_rodata_4E4 = 220.0f; /* 0x4E4 */
static const float lbl_1_rodata_4E8 = 800.0f; /* 0x4E8 */
static const float lbl_1_rodata_4EC = 720.0f; /* 0x4EC */
static const float lbl_1_rodata_4F0 = 201.5625f; /* 0x4F0 */
static const float lbl_1_rodata_4F4 = 103.125f; /* 0x4F4 */
static const float lbl_1_rodata_4F8 = 0.1f; /* 0x4F8 */
static const float lbl_1_rodata_4FC = 66.66667f; /* 0x4FC */
static const float lbl_1_rodata_500 = 0.015f; /* 0x500 */
/* 0x504 lbl_1_rodata_504 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_510 = 182.0f; /* 0x510 */
static const float lbl_1_rodata_514 = 238.0f; /* 0x514 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1140 */ s32 lbl_1_bss_1140[10];
/* 0x113C */ s32 lbl_1_bss_113C;
/* 0x1138 */ s32 lbl_1_bss_1138;
/* 0x1134 */ s32 lbl_1_bss_1134;
/* 0x1130 */ s32 lbl_1_bss_1130;
/* 0x112E */ s16 lbl_1_bss_112E;
/* 0x1126 */ s16 lbl_1_bss_1126[4];
/* 0x111E */ s16 lbl_1_bss_111E[4];
/* 0x1116 */ s16 lbl_1_bss_1116[4];
/* 0x1086 */ s16 lbl_1_bss_1086[4][18];
/* 0x1080 */ s16 lbl_1_bss_1080[3];
/* 0x1056 */ s16 lbl_1_bss_1056[21];
/* 0x1050 */ s16 lbl_1_bss_1050[3];
/* 0x104E */ s16 lbl_1_bss_104E;
/* 0x102A */ s16 lbl_1_bss_102A[18];
/* 0x100A */ s16 lbl_1_bss_100A[4][4];
/* 0x1002 */ s16 lbl_1_bss_1002[4];
/* 0xFFA */ s16 lbl_1_bss_FFA[4];
/* 0xFF2 */ s16 lbl_1_bss_FF2[4];
/* 0xFEA */ s16 lbl_1_bss_FEA[4];
/* 0xFE2 */ s16 lbl_1_bss_FE2[4];
/* 0xFDA */ s16 lbl_1_bss_FDA[4];
/* 0xFD2 */ s16 lbl_1_bss_FD2[4];
/* 0xFCA */ s16 lbl_1_bss_FCA[4];
/* 0xFC2 */ s16 lbl_1_bss_FC2[4];
/* 0xFBA */ s16 lbl_1_bss_FBA[4];
/* 0xFB2 */ s16 lbl_1_bss_FB2[4];
/* 0xFAA */ s16 lbl_1_bss_FAA[4];
/* 0xFA2 */ s16 lbl_1_bss_FA2[4];
/* 0xF9E */ s16 lbl_1_bss_F9E[2];
/* 0xF96 */ s16 lbl_1_bss_F96[4];
/* 0xF92 */ s16 lbl_1_bss_F92[2]; /* [1] at 0xF94 is used; dtk sizes it 2 and calls 0xF94 a gap */
/* 0xF8E */ s16 lbl_1_bss_F8E[2]; /* [1] at 0xF90 is used; dtk sizes it 2 and calls 0xF90 a gap */
/* 0xF86 */ s16 lbl_1_bss_F86[4];
/* 0xF84 */ s16 lbl_1_bss_F84;
/* 0xF64 */ s32 lbl_1_bss_F64[8];
/* 0xF3C */ s32 lbl_1_bss_F3C[10];
/* 0xF14 */ float lbl_1_bss_F14[10];
/* 0xE9C */ HuVecF lbl_1_bss_E9C[10];
/* 0xE98 */ s32 lbl_1_bss_E98;
/* 0xE8C */ s32 lbl_1_bss_E8C[3];
/* 0xE68 */ HuVecF lbl_1_bss_E68[3];
/* 0xE60 */ float lbl_1_bss_E60[2];
/* 0xE54 */ HuVecF lbl_1_bss_E54;
/* 0xE48 */ HuVecF lbl_1_bss_E48;
/* 0xD70 */ HuVecF lbl_1_bss_D70[18];
/* 0xC98 */ HuVecF lbl_1_bss_C98[18];
/* 0xC50 */ s32 lbl_1_bss_C50[18];
/* 0xC48 */ s32 lbl_1_bss_C48[2];
/* 0xC44 */ s32 lbl_1_bss_C44;
/* 0xC40 */ s32 lbl_1_bss_C40;
/* 0xC3C */ s32 lbl_1_bss_C3C;
/* 0xC30 */ HuVecF lbl_1_bss_C30;
/* 0xC24 */ HuVecF lbl_1_bss_C24;
/* 0xC1C */ s16 lbl_1_bss_C1C[4];
/* 0xC14 */ s16 lbl_1_bss_C14[4];
/* 0xC10 */ s32 lbl_1_bss_C10;
/* 0xC04 */ HuVecF lbl_1_bss_C04;
/* 0xC00 */ float lbl_1_bss_C00;
/* 0xBF4 */ HuVecF lbl_1_bss_BF4;
/* 0xBF0 */ s32 lbl_1_bss_BF0;
/* 0xBEC */ s32 lbl_1_bss_BEC;
/* 0xBEA gap_05_00000BEA_bss (0x2): alignment gap */
/* 0xBE8 */ s16 lbl_1_bss_BE8;

/* --- functions (reference order), .data placed before its first user --- */
/* 59 insns */
void fn_1_FA24(void)
{
    lbl_1_bss_1174 = 0;
    lbl_1_bss_1168[0] = 0;
    lbl_1_bss_1168[1] = 0;
    lbl_1_bss_1168[2] = 0;
    lbl_1_bss_C48[0] = 0;
    lbl_1_bss_C48[1] = 0;
    lbl_1_bss_C44 = 1;
    lbl_1_bss_1298[0] = 0;
    lbl_1_bss_1298[1] = 0;
    lbl_1_bss_1298[2] = 0;
    lbl_1_bss_11DC = 0;
    HuPrcChildCreate(fn_1_FB10, 100, 0x2000, 0, HuPrcCurrentGet());
}

/* 30 insns */
void fn_1_FB10(void)
{
    if (lbl_1_bss_8[1] != 0 && HuAudSStreamStatGet(lbl_1_bss_8[0]) == 0) {
        HuAudSStreamVolSet(0, 127, 1000);
        lbl_1_bss_8[0] = lbl_1_bss_8[1] = 0;
    }
    HuPrcVSleep();
}

/* 83 insns */
s32 fn_1_FB88(CardGameWork *work)
{
    s32 result = 0;
    if (lbl_1_bss_1174 == 0) {
        if (fn_1_13728(work)) {
            lbl_1_bss_1174 = 1;
        }
    }
    else if (lbl_1_bss_1174 == 1) {
        if (fn_1_FCD4(work)) {
            lbl_1_bss_1174 = 2;
        }
    }
    else if (lbl_1_bss_1174 == 2) {
        if (fn_1_11C48(work)) {
            lbl_1_bss_1174 = 3;
        }
    }
    else if (lbl_1_bss_1174 == 3) {
        if (fn_1_1658C(work)) {
            lbl_1_bss_1174 = 4;
        }
    }
    else if (lbl_1_bss_1174 == 4) {
        if (fn_1_127F8()) {
            lbl_1_bss_1174 = 0;
            result = 1;
        }
    }
    return result;
}

/* 0xB0 */ u32 lbl_1_data_B0[122] = { DATA_card, DATANUM(DATA_card, 1), DATANUM(DATA_card, 2), DATANUM(DATA_card, 3), DATANUM(DATA_card, 4), DATANUM(DATA_card, 5), DATANUM(DATA_card, 6), DATANUM(DATA_card, 7), DATANUM(DATA_card, 8), DATANUM(DATA_card, 9), DATANUM(DATA_card, 10), DATANUM(DATA_card, 11), DATANUM(DATA_card, 12), DATANUM(DATA_card, 13), DATANUM(DATA_card, 14), DATANUM(DATA_card, 15), DATANUM(DATA_card, 16), DATANUM(DATA_card, 17), DATANUM(DATA_card, 18), DATANUM(DATA_card, 19), DATANUM(DATA_card, 20), DATANUM(DATA_card, 21), DATANUM(DATA_card, 22), DATANUM(DATA_card, 23), DATANUM(DATA_card, 24), DATANUM(DATA_card, 25), DATANUM(DATA_card, 26), DATANUM(DATA_card, 27), DATANUM(DATA_card, 28), DATANUM(DATA_card, 29), DATANUM(DATA_card, 30), DATANUM(DATA_card, 31), DATANUM(DATA_card, 32), DATANUM(DATA_card, 33), DATANUM(DATA_card, 34), DATANUM(DATA_card, 35), DATANUM(DATA_card, 36), DATANUM(DATA_card, 37), DATANUM(DATA_card, 38), DATANUM(DATA_card, 39), DATANUM(DATA_card, 40), DATANUM(DATA_card, 41), DATANUM(DATA_card, 42), DATANUM(DATA_card, 43), DATANUM(DATA_card, 44), DATANUM(DATA_card, 45), DATANUM(DATA_card, 46), DATANUM(DATA_card, 47), DATANUM(DATA_card, 48), DATANUM(DATA_card, 49), DATANUM(DATA_card, 50), DATANUM(DATA_card, 51), DATANUM(DATA_card, 52), DATANUM(DATA_card, 53), DATANUM(DATA_card, 54), DATANUM(DATA_card, 55), DATANUM(DATA_card, 56), DATANUM(DATA_card, 64), DATANUM(DATA_card, 65), DATANUM(DATA_card, 66), DATANUM(DATA_card, 67), DATANUM(DATA_card, 68), DATANUM(DATA_card, 69), DATANUM(DATA_card, 70), DATANUM(DATA_card, 71), DATANUM(DATA_card, 72), DATANUM(DATA_card, 73), DATANUM(DATA_card, 74), DATANUM(DATA_card, 75), DATANUM(DATA_card, 76), DATANUM(DATA_card, 77), DATANUM(DATA_card, 78), DATANUM(DATA_card, 79), DATANUM(DATA_card, 80), DATANUM(DATA_card, 81), DATANUM(DATA_card, 82), DATANUM(DATA_card, 83), DATANUM(DATA_card, 84), DATANUM(DATA_card, 85), DATANUM(DATA_card, 86), DATANUM(DATA_card, 87), DATANUM(DATA_card, 88), DATANUM(DATA_card, 89), DATANUM(DATA_card, 90), DATANUM(DATA_card, 91), DATANUM(DATA_card, 92), DATANUM(DATA_card, 93), DATANUM(DATA_card, 94), DATANUM(DATA_card, 95), DATANUM(DATA_card, 96), DATANUM(DATA_card, 97), DATANUM(DATA_card, 98), DATANUM(DATA_card, 99), DATANUM(DATA_card, 100), DATANUM(DATA_card, 101), DATANUM(DATA_card, 102), DATANUM(DATA_card, 103), DATANUM(DATA_card, 104), DATANUM(DATA_card, 105), DATANUM(DATA_card, 106), DATANUM(DATA_card, 107), DATANUM(DATA_card, 108), DATANUM(DATA_card, 109), DATANUM(DATA_card, 110), DATANUM(DATA_card, 111), DATANUM(DATA_card, 112), DATANUM(DATA_card, 113), DATANUM(DATA_card, 114), DATANUM(DATA_card, 115), DATANUM(DATA_card, 116), DATANUM(DATA_card, 117), DATANUM(DATA_card, 118), DATANUM(DATA_card, 119), DATANUM(DATA_card, 120), DATANUM(DATA_card, 121), DATANUM(DATA_card, 122), DATANUM(DATA_card, 123), DATANUM(DATA_card, 124), DATANUM(DATA_card, 125), DATANUM(DATA_card, 126), DATANUM(DATA_card, 127), DATANUM(DATA_card, 128) };
/* 0x298 */ u32 lbl_1_data_298[7] = { DATANUM(DATA_card, 57), DATANUM(DATA_card, 58), DATANUM(DATA_card, 59), DATANUM(DATA_card, 60), DATANUM(DATA_card, 61), DATANUM(DATA_card, 62), DATANUM(DATA_card, 63) };
/* 0x2B4 */ u32 lbl_1_data_2B4[36] = { DATANUM(DATA_card, 129), DATANUM(DATA_card, 130), DATANUM(DATA_card, 131), DATANUM(DATA_card, 132), DATANUM(DATA_card, 133), DATANUM(DATA_card, 134), DATANUM(DATA_card, 135), DATANUM(DATA_card, 136), DATANUM(DATA_card, 137), DATANUM(DATA_card, 138), DATANUM(DATA_card, 139), DATANUM(DATA_card, 140), DATANUM(DATA_card, 141), DATANUM(DATA_card, 142), DATANUM(DATA_card, 143), DATANUM(DATA_card, 144), DATANUM(DATA_card, 145), DATANUM(DATA_card, 146), DATANUM(DATA_card, 147), DATANUM(DATA_card, 148), DATANUM(DATA_card, 149), DATANUM(DATA_card, 150), DATANUM(DATA_card, 151), DATANUM(DATA_card, 152), DATANUM(DATA_card, 153), DATANUM(DATA_card, 154), DATANUM(DATA_card, 155), DATANUM(DATA_card, 156), DATANUM(DATA_card, 157), DATANUM(DATA_card, 158), DATANUM(DATA_card, 159), DATANUM(DATA_card, 160), DATANUM(DATA_card, 161), DATANUM(DATA_card, 162), DATANUM(DATA_card, 163), DATANUM(DATA_card, 164) };
/* 0x344 */ u32 lbl_1_data_344[26] = { DATANUM(DATA_card, 165), DATANUM(DATA_card, 166), DATANUM(DATA_card, 167), DATANUM(DATA_card, 168), DATANUM(DATA_card, 169), DATANUM(DATA_card, 170), DATANUM(DATA_card, 171), DATANUM(DATA_card, 172), DATANUM(DATA_card, 173), DATANUM(DATA_card, 174), DATANUM(DATA_card, 175), DATANUM(DATA_card, 176), DATANUM(DATA_card, 177), DATANUM(DATA_card, 178), DATANUM(DATA_card, 179), DATANUM(DATA_card, 180), DATANUM(DATA_card, 181), DATANUM(DATA_card, 182), DATANUM(DATA_card, 183), DATANUM(DATA_card, 184), DATANUM(DATA_card, 185), DATANUM(DATA_card, 186), DATANUM(DATA_card, 187), DATANUM(DATA_card, 188), DATANUM(DATA_card, 189), DATANUM(DATA_card, 190) };
/* 0x3AC */ u32 lbl_1_data_3AC[3] = { DATANUM(DATA_card, 191), DATANUM(DATA_card, 192), DATANUM(DATA_card, 193) };
/* 0x3B8 */ u32 lbl_1_data_3B8[6] = { DATANUM(DATA_card, 194), DATANUM(DATA_card, 195), DATANUM(DATA_card, 196), DATANUM(DATA_card, 197), DATANUM(DATA_card, 198), DATANUM(DATA_card, 199) };
/* 0x3D0 */ u32 lbl_1_data_3D0[3] = { DATANUM(DATA_card, 200), DATANUM(DATA_card, 192), DATANUM(DATA_card, 193) };
/* 0x3DC */ u32 lbl_1_data_3DC[4] = { DATANUM(DATA_card, 201), DATANUM(DATA_card, 202), DATANUM(DATA_card, 203), DATANUM(DATA_card, 204) };
/* 0x3EC */ u32 lbl_1_data_3EC[5] = { DATANUM(DATA_card, 205), DATANUM(DATA_card, 206), DATANUM(DATA_card, 207), DATANUM(DATA_card, 208), DATANUM(DATA_card, 209) };
/* 0x400 */ u32 lbl_1_data_400[10] = { DATANUM(DATA_card, 210), DATANUM(DATA_card, 211), DATANUM(DATA_card, 212), DATANUM(DATA_card, 213), DATANUM(DATA_card, 214), DATANUM(DATA_card, 215), DATANUM(DATA_card, 216), DATANUM(DATA_card, 217), DATANUM(DATA_card, 218), DATANUM(DATA_card, 219) };
/* 0x428 */ float lbl_1_data_428[8] = { 438.0f, 72.0f, 438.0f, 140.0f, 438.0f, 208.0f, 438.0f, 276.0f };
/* 0x448 */ float lbl_1_data_448[8] = { 474.0f, 72.0f, 474.0f, 140.0f, 474.0f, 208.0f, 474.0f, 276.0f };
/* 0x468 */ float lbl_1_data_468[8] = { 546.0f, 90.0f, 546.0f, 158.0f, 546.0f, 226.0f, 546.0f, 294.0f };
/* 0x488 */ float lbl_1_data_488[8] = { 554.0f, 90.0f, 554.0f, 158.0f, 554.0f, 226.0f, 554.0f, 294.0f };
/* 0x4A8 */ float lbl_1_data_4A8[8] = { 454.0f, 88.0f, 454.0f, 156.0f, 454.0f, 224.0f, 454.0f, 292.0f };
/* 0x4C8 */ float lbl_1_data_4C8[8] = { 514.0f, 90.0f, 514.0f, 158.0f, 514.0f, 226.0f, 514.0f, 294.0f };
/* 0x4E8 */ float lbl_1_data_4E8[8] = { 530.0f, 90.0f, 530.0f, 158.0f, 530.0f, 226.0f, 530.0f, 294.0f };
/* 0x508 */ float lbl_1_data_508[8] = { 548.0f, 90.0f, 548.0f, 158.0f, 548.0f, 226.0f, 548.0f, 294.0f };
/* 0x528 */ float lbl_1_data_528[8] = { 494.0f, 101.0f, 494.0f, 169.0f, 494.0f, 237.0f, 494.0f, 305.0f };
/* 0x548 */ float lbl_1_data_548[8] = { 492.0f, 60.0f, 492.0f, 128.0f, 492.0f, 196.0f, 492.0f, 264.0f };
/* 0x568 */ float lbl_1_data_568[8] = { 520.0f, 60.0f, 520.0f, 128.0f, 520.0f, 196.0f, 520.0f, 264.0f };
/* 0x588 */ float lbl_1_data_588[8] = { 548.0f, 60.0f, 548.0f, 128.0f, 548.0f, 196.0f, 548.0f, 264.0f };
/* 0x5A8 */ float lbl_1_data_5A8[8] = { 400.0f, 60.0f, 400.0f, 128.0f, 400.0f, 196.0f, 400.0f, 264.0f };

/* 2013 insns */
s32 fn_1_FCD4(CardGameWork *work)
{
    s32 i;
    s32 result = 0;
    s32 t;

    switch (lbl_1_bss_1168[0]) {
        case 0:
            for (i = 0; i < 4; i++) {
                lbl_1_bss_1002[i] = espEntry(lbl_1_data_2B4[4], 0, 0);
                espDrawNoSet(lbl_1_bss_1002[i], 64);
                espBankSet(lbl_1_bss_1002[i], GwPlayerConf[work->unk174[i]].charNo);
                espTPLvlSet(lbl_1_bss_1002[i], 0.3f);
                espPriSet(lbl_1_bss_1002[i], 0x1F0);
                lbl_1_bss_FFA[i] = espEntry(lbl_1_data_2B4[5], 0, 0);
                espDrawNoSet(lbl_1_bss_FFA[i], 64);
                espBankSet(lbl_1_bss_FFA[i], GwPlayerConf[work->unk174[i]].charNo * 2);
                espTPLvlSet(lbl_1_bss_FFA[i], 0.3f);
                espPriSet(lbl_1_bss_FFA[i], 0x1F0);
                lbl_1_bss_FF2[i] = espEntry(lbl_1_data_2B4[5], 0, 0);
                espDrawNoSet(lbl_1_bss_FF2[i], 64);
                espBankSet(lbl_1_bss_FF2[i], GwPlayerConf[work->unk174[i]].charNo * 2 + 1);
                espTPLvlSet(lbl_1_bss_FF2[i], 0.3f);
                espPriSet(lbl_1_bss_FF2[i], 0x1F0);
                lbl_1_bss_100A[i][0] = espEntry(lbl_1_data_2B4[0], 0, 0);
                espDrawNoSet(lbl_1_bss_100A[i][0], 64);
                espBankSet(lbl_1_bss_100A[i][0], GwPlayerConf[work->unk174[i]].charNo);
                espPriSet(lbl_1_bss_100A[i][0], 0x1E0);
                lbl_1_bss_100A[i][1] = espEntry(lbl_1_data_2B4[1], 0, 0);
                espDrawNoSet(lbl_1_bss_100A[i][1], 64);
                espBankSet(lbl_1_bss_100A[i][1], GwPlayerConf[work->unk174[i]].charNo);
                espPriSet(lbl_1_bss_100A[i][1], 0x1E0);
                espDispOff(lbl_1_bss_100A[i][1]);
                lbl_1_bss_100A[i][2] = espEntry(lbl_1_data_2B4[2], 0, 0);
                espDrawNoSet(lbl_1_bss_100A[i][2], 64);
                espBankSet(lbl_1_bss_100A[i][2], GwPlayerConf[work->unk174[i]].charNo);
                espPriSet(lbl_1_bss_100A[i][2], 0x1E0);
                espDispOff(lbl_1_bss_100A[i][2]);
                lbl_1_bss_100A[i][3] = espEntry(lbl_1_data_2B4[3], 0, 0);
                espDrawNoSet(lbl_1_bss_100A[i][3], 64);
                espBankSet(lbl_1_bss_100A[i][3], GwPlayerConf[work->unk174[i]].charNo);
                espPriSet(lbl_1_bss_100A[i][3], 0x1E0);
                espDispOff(lbl_1_bss_100A[i][3]);
                lbl_1_bss_FEA[i] = espEntry(lbl_1_data_2B4[6], 0, 0);
                espDrawNoSet(lbl_1_bss_FEA[i], 64);
                espBankSet(lbl_1_bss_FEA[i], 0);
                espPriSet(lbl_1_bss_FEA[i], 0x1D0);
                lbl_1_bss_FE2[i] = espEntry(lbl_1_data_2B4[7], 0, 0);
                espDrawNoSet(lbl_1_bss_FE2[i], 64);
                espBankSet(lbl_1_bss_FE2[i], 2);
                espPriSet(lbl_1_bss_FE2[i], 0x1E0);
                lbl_1_bss_FDA[i] = espEntry(lbl_1_data_2B4[7], 0, 0);
                espDrawNoSet(lbl_1_bss_FDA[i], 64);
                espBankSet(lbl_1_bss_FDA[i], 3);
                espPriSet(lbl_1_bss_FDA[i], 0x1D0);
                lbl_1_bss_FD2[i] = espEntry(lbl_1_data_2B4[7], 0, 0);
                espDrawNoSet(lbl_1_bss_FD2[i], 64);
                espBankSet(lbl_1_bss_FD2[i], 3);
                espPriSet(lbl_1_bss_FD2[i], 0x1C0);
                lbl_1_bss_FCA[i] = espEntry(lbl_1_data_2B4[8], 0, 0);
                espDrawNoSet(lbl_1_bss_FCA[i], 64);
                espBankSet(lbl_1_bss_FCA[i], 0);
                espPriSet(lbl_1_bss_FCA[i], 0x1E0);
                lbl_1_bss_FC2[i] = espEntry(lbl_1_data_2B4[9], 0, 0);
                espDrawNoSet(lbl_1_bss_FC2[i], 64);
                espBankSet(lbl_1_bss_FC2[i], 0);
                espPriSet(lbl_1_bss_FC2[i], 0x1E0);
                lbl_1_bss_FBA[i] = espEntry(lbl_1_data_2B4[9], 0, 0);
                espDrawNoSet(lbl_1_bss_FBA[i], 64);
                espBankSet(lbl_1_bss_FBA[i], 1);
                espPriSet(lbl_1_bss_FBA[i], 0x1D0);
                lbl_1_bss_FB2[i] = espEntry(lbl_1_data_2B4[9], 0, 0);
                espDrawNoSet(lbl_1_bss_FB2[i], 64);
                espBankSet(lbl_1_bss_FB2[i], 2);
                espPriSet(lbl_1_bss_FB2[i], 0x1C0);
                lbl_1_bss_FAA[i] = espEntry(lbl_1_data_2B4[10], 0, 0);
                espDrawNoSet(lbl_1_bss_FAA[i], 64);
                espBankSet(lbl_1_bss_FAA[i], i);
                /* retail: sets the priority of FC2, not the FAA sprite just created */
                espPriSet(lbl_1_bss_FC2[i], 0x1D0);
                lbl_1_bss_FA2[i] = espEntry(lbl_1_data_2B4[GwPlayerConf[work->unk174[i]].charNo + 27], 0, 0);
                espDrawNoSet(lbl_1_bss_FA2[i], 0);
                espPosSet(lbl_1_bss_FA2[i], 200.0f, 540.0f);
                espDispOff(lbl_1_bss_FA2[i]);
            }
            HuSprExecLayerSet(64, 6);
            fn_1_2FFAC(work);
            for (i = 0; i < 4; i++) {
                lbl_1_bss_1140[i] = 300;
                espPosSet(lbl_1_bss_1002[i], ((float (*)[2])lbl_1_data_448)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_448)[i][1]);
                espPosSet(lbl_1_bss_FFA[i], ((float (*)[2])lbl_1_data_468)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_468)[i][1]);
                espPosSet(lbl_1_bss_FF2[i], ((float (*)[2])lbl_1_data_488)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_488)[i][1]);
                espPosSet(lbl_1_bss_100A[i][0], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][1], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][2], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][3], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_FEA[i], ((float (*)[2])lbl_1_data_4A8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4A8)[i][1]);
                espPosSet(lbl_1_bss_FE2[i], ((float (*)[2])lbl_1_data_4C8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4C8)[i][1]);
                espPosSet(lbl_1_bss_FDA[i], ((float (*)[2])lbl_1_data_4E8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4E8)[i][1]);
                espPosSet(lbl_1_bss_FD2[i], ((float (*)[2])lbl_1_data_508)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_508)[i][1]);
                espPosSet(lbl_1_bss_FCA[i], ((float (*)[2])lbl_1_data_528)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_528)[i][1]);
                espPosSet(lbl_1_bss_FC2[i], ((float (*)[2])lbl_1_data_548)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_548)[i][1]);
                espPosSet(lbl_1_bss_FBA[i], ((float (*)[2])lbl_1_data_568)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_568)[i][1]);
                espPosSet(lbl_1_bss_FB2[i], ((float (*)[2])lbl_1_data_588)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_588)[i][1]);
                espPosSet(lbl_1_bss_FAA[i], ((float (*)[2])lbl_1_data_5A8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_5A8)[i][1]);
                if (GwPlayerConf[work->unk174[i]].type == 0) {
                    espDispOff(lbl_1_bss_FEA[i]);
                }
            }
            lbl_1_bss_1168[0]++;
            break;
        case 1:
            lbl_1_bss_113C = fn_1_15D38(work);
            if (lbl_1_bss_113C != -1) {
                lbl_1_bss_1168[0]++;
            }
            break;
        case 2:
            i = lbl_1_bss_113C;
            if (lbl_1_bss_1140[i] > 0) {
                t = lbl_1_bss_1140[i] - 20;
            }
            else {
                t = 0;
            }
            lbl_1_bss_1140[i] = t;
            espPosSet(lbl_1_bss_1002[i], ((float (*)[2])lbl_1_data_448)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_448)[i][1]);
            espPosSet(lbl_1_bss_FFA[i], ((float (*)[2])lbl_1_data_468)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_468)[i][1]);
            espPosSet(lbl_1_bss_FF2[i], ((float (*)[2])lbl_1_data_488)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_488)[i][1]);
            espPosSet(lbl_1_bss_100A[i][0], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
            espPosSet(lbl_1_bss_100A[i][1], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
            espPosSet(lbl_1_bss_100A[i][2], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
            espPosSet(lbl_1_bss_100A[i][3], ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_428)[i][1]);
            espPosSet(lbl_1_bss_FEA[i], ((float (*)[2])lbl_1_data_4A8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4A8)[i][1]);
            espPosSet(lbl_1_bss_FE2[i], ((float (*)[2])lbl_1_data_4C8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4C8)[i][1]);
            espPosSet(lbl_1_bss_FDA[i], ((float (*)[2])lbl_1_data_4E8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_4E8)[i][1]);
            espPosSet(lbl_1_bss_FD2[i], ((float (*)[2])lbl_1_data_508)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_508)[i][1]);
            espPosSet(lbl_1_bss_FCA[i], ((float (*)[2])lbl_1_data_528)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_528)[i][1]);
            espPosSet(lbl_1_bss_FC2[i], ((float (*)[2])lbl_1_data_548)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_548)[i][1]);
            espPosSet(lbl_1_bss_FBA[i], ((float (*)[2])lbl_1_data_568)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_568)[i][1]);
            espPosSet(lbl_1_bss_FB2[i], ((float (*)[2])lbl_1_data_588)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_588)[i][1]);
            espPosSet(lbl_1_bss_FAA[i], ((float (*)[2])lbl_1_data_5A8)[i][0] + lbl_1_bss_1140[i], ((float (*)[2])lbl_1_data_5A8)[i][1]);
            if (lbl_1_bss_20[0] == 0 && ((float (*)[2])lbl_1_data_428)[i][0] + lbl_1_bss_1140[i] <= 576.0f) {
                if (GwPlayerConf[work->unk174[i]].charNo == 0) {
                    lbl_1_bss_20[1] = 0x1F8;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 1) {
                    lbl_1_bss_20[1] = 0x1E4;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 2) {
                    lbl_1_bss_20[1] = 0x25C;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 3) {
                    lbl_1_bss_20[1] = 0x2AC;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 4) {
                    lbl_1_bss_20[1] = 0x284;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 5) {
                    lbl_1_bss_20[1] = 0x1BC;
                }
                if (GwPlayerConf[work->unk174[i]].charNo == 6) {
                    lbl_1_bss_20[1] = 0x298;
                }
                fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_1126[3], 1);
                lbl_1_bss_20[1] = 0;
                lbl_1_bss_20[0] = 1;
            }
            if (lbl_1_bss_1140[i] == 0) {
                if (i == 3) {
                    lbl_1_bss_1168[0] = 0;
                    result = 1;
                    for (i = 0; i < 4; i++) {
                        Hu3DLLightKill(lbl_1_bss_1116[i], lbl_1_bss_0[i]);
                        lbl_1_bss_0[i] = -1;
                        Hu3DModelShadowMapObjReset(lbl_1_bss_1126[i]);
                        Hu3DModelShadowReset(lbl_1_bss_111E[i]);
                        Hu3DModelShadowReset(lbl_1_bss_1116[i]);
                        Hu3DModelKill(lbl_1_bss_111E[i]);
                        Hu3DModelKill(lbl_1_bss_1116[i]);
                        Hu3DModelKill(lbl_1_bss_1126[i]);
                    }
                }
                else {
                    lbl_1_bss_1168[0]--;
                }
                lbl_1_bss_20[0] = 0;
            }
            break;
    }
    return result;
}

/* 510 insns */
s32 fn_1_11C48(CardGameWork *work)
{
    s32 j;
    s32 i;
    s32 k;
    s32 cnt;
    s32 result;
    HuVecF pos;

    result = 0;
    cnt = 0;
    switch (lbl_1_bss_1168[0]) {
        case 0:
            lbl_1_bss_F14[5] -= 6.0f;
            pos = (HuVecF){ 288.0f, 160.0f, 1800.0f };
            pos.y += lbl_1_bss_F14[5];
            fn_1_36A70(&pos);
            lbl_1_bss_F14[6] += 15.0f;
            Hu3DModelRotSet(fn_1_36A60(), 0.0f, lbl_1_bss_F14[6], 0.0f);
            if (fn_1_30FA4(0, 0)) {
                lbl_1_bss_1168[0]++;
                fn_1_36B78();
            }
            break;
        case 1:
            k = 0;
            for (j = 0; j < work->unk194; j++) {
                lbl_1_bss_1140[j] = (j + 1) * 2000;
                for (i = 0; i < work->unk194; i++) {
                    fn_1_9C74(&pos, i, j, 1, 1);
                    Hu3DModelPosSet(lbl_1_bss_478[i][j], -50.0f + pos.x, pos.y + lbl_1_bss_1140[j], pos.z);
                    Hu3DModelAttrReset(lbl_1_bss_478[i][j], HU3D_ATTR_DISPOFF);
                    if (lbl_1_bss_8C4[i][j] & 0xF00) {
                        Hu3DModelAttrSet(lbl_1_bss_478[i][j], HU3D_ATTR_DISPOFF);
                        Hu3DModelPosSet(lbl_1_bss_3F4[k], -50.0f + pos.x, pos.y + lbl_1_bss_1140[j], pos.z);
                        Hu3DModelAttrReset(lbl_1_bss_3F4[k], HU3D_ATTR_DISPOFF);
                        k++;
                    }
                }
            }
            lbl_1_bss_1168[0]++;
            break;
        case 2:
            k = 0;
            for (j = 0; j < work->unk194; j++) {
                lbl_1_bss_1140[j] = (lbl_1_bss_1140[j] > 0) ? lbl_1_bss_1140[j] - 100 : 0;
                for (i = 0; i < work->unk194; i++) {
                    fn_1_9C74(&pos, i, j, 1, 1);
                    Hu3DModelPosSet(lbl_1_bss_478[i][j], -50.0f + pos.x, pos.y + lbl_1_bss_1140[j], pos.z);
                    if (lbl_1_bss_8C4[i][j] & 0xF00) {
                        Hu3DModelPosSet(lbl_1_bss_3F4[k], -50.0f + pos.x, pos.y + lbl_1_bss_1140[j], pos.z);
                        k++;
                    }
                }
                if (lbl_1_bss_1140[j] == 0) {
                    cnt++;
                    if (lbl_1_bss_20[j] == 0) {
                        fn_1_8D04(0x410, lbl_1_bss_478[work->unk194 - 1][j], 1);
                        lbl_1_bss_20[j] = 1;
                    }
                }
            }
            if (cnt == work->unk194) {
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[0]++;
                for (i = 0; i < work->unk194; i++) {
                    for (j = 0; j < work->unk194; j++) {
                        if (lbl_1_bss_8C4[i][j] & 0xF00) {
                            fn_1_9C74(&pos, i, j, 1, 1);
                            pos.x += -50.0f;
                            fn_1_3ED3C(15, pos);
                        }
                    }
                    lbl_1_bss_20[i] = 0;
                }
                HuAudFXPlay(0x411);
            }
            break;
        case 3:
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] >= 100) {
                for (i = 0; i < work->unk194; i++) {
                    for (j = 0; j < work->unk194; j++) {
                        if (lbl_1_bss_8C4[i][j] & 0xF00) {
                            Hu3DModelAttrReset(lbl_1_bss_478[i][j], HU3D_ATTR_DISPOFF);
                        }
                    }
                }
                for (i = 0; i < lbl_1_bss_3F0; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_3F4[i], HU3D_ATTR_DISPOFF);
                }
            }
            if (lbl_1_bss_F3C[0] >= 200) {
                for (i = 0; i < lbl_1_bss_3F0; i++) {
                    Hu3DModelKill(lbl_1_bss_3F4[i]);
                }
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 238 insns */
s32 fn_1_12440(s32 a0)
{
    s32 result = 0;
    float size[2] = { 352.0f, 352.0f };

    switch (lbl_1_bss_1168[0]) {
        case 0:
            lbl_1_bss_112E = espEntry(lbl_1_data_2B4[a0 + 12], 0, 0);
            espDrawNoSet(lbl_1_bss_112E, (a0 != 0) ? 0 : 64);
            lbl_1_bss_F3C[0] = 300;
            espPosSet(lbl_1_bss_112E, 288.0f - size[a0] / 2.0f + size[a0] / 2.0f, 78.0f - lbl_1_bss_F3C[0]);
            lbl_1_bss_1168[0]++;
            HuSprExecLayerSet(64, 6);
            break;
        case 1:
            lbl_1_bss_F3C[0] -= 10;
            espPosSet(lbl_1_bss_112E, 288.0f - size[a0] / 2.0f + size[a0] / 2.0f, 78.0f - lbl_1_bss_F3C[0]);
            if (lbl_1_bss_F3C[0] <= 0) {
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[0]++;
                result = 1;
            }
            break;
        case 2:
            lbl_1_bss_F3C[0] += 10;
            espPosSet(lbl_1_bss_112E, 288.0f - size[a0] / 2.0f + size[a0] / 2.0f, 78.0f - lbl_1_bss_F3C[0]);
            if (lbl_1_bss_F3C[0] >= 300) {
                espKill(lbl_1_bss_112E);
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 387 insns */
s32 fn_1_127F8(void)
{
    s32 result = 0;
    HuVecF pos = { 288.0f, 320.0f, 1500.0f };

    switch (lbl_1_bss_1168[0]) {
        case 0:
            lbl_1_bss_F3C[0] = 600;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_112E = espEntry(lbl_1_data_2B4[14], 0, 0);
            espDrawNoSet(lbl_1_bss_112E, 64);
            espPosSet(lbl_1_bss_112E, 288.0f, 240.0f - lbl_1_bss_F3C[0]);
            espTPLvlSet(lbl_1_bss_112E, lbl_1_bss_F14[0]);
            fn_1_36828();
            lbl_1_bss_F14[5] = 400.0f;
            pos.y -= lbl_1_bss_F14[5];
            fn_1_36A70(&pos);
            lbl_1_bss_F14[6] = 0.0f;
            lbl_1_bss_1168[0]++;
            break;
        case 1:
            if (lbl_1_bss_F3C[0] == 20) {
                HuAudSStreamStop(lbl_1_bss_14);
            }
            lbl_1_bss_F3C[0] -= 20;
            if (lbl_1_bss_F3C[0] < 0) {
                lbl_1_bss_F3C[0] = 0;
            }
            lbl_1_bss_F14[0] += 0.03;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
            }
            espPosSet(lbl_1_bss_112E, 288.0f, 240.0f - lbl_1_bss_F3C[0]);
            espTPLvlSet(lbl_1_bss_112E, lbl_1_bss_F14[0]);
            lbl_1_bss_F14[5] -= 20.0f;
            if (lbl_1_bss_F14[5] < 0.0f) {
                lbl_1_bss_F14[5] = 0.0f;
            }
            pos.y -= lbl_1_bss_F14[5];
            fn_1_36A70(&pos);
            if (1.0f == lbl_1_bss_F14[0]) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[0] = 10;
                lbl_1_bss_F3C[1] = 0;
            }
            break;
        case 2:
            lbl_1_bss_F3C[1]++;
            if (lbl_1_bss_F3C[1] >= 60) {
                lbl_1_bss_F14[5] -= 5.0f;
                pos.y += lbl_1_bss_F14[5];
                lbl_1_bss_F14[6] += 40.0f;
                pos.z -= lbl_1_bss_F14[6];
                fn_1_36A70(&pos);
                if (lbl_1_bss_F3C[1] >= 80) {
                    lbl_1_bss_F14[0] += 0.05;
                    if (lbl_1_bss_F14[0] > 2.0f) {
                        lbl_1_bss_F14[0] = 2.0f;
                    }
                    espScaleSet(lbl_1_bss_112E, 1.0f + lbl_1_bss_F14[0], 1.0f + lbl_1_bss_F14[0]);
                    espTPLvlSet(lbl_1_bss_112E, 1.0f - lbl_1_bss_F14[0] / 2.0f);
                    if (2.0f == lbl_1_bss_F14[0]) {
                        fn_1_36B78();
                        espKill(lbl_1_bss_112E);
                        lbl_1_bss_1168[0] = 0;
                        result = 1;
                    }
                }
            }
            break;
        case 10:
            if (HuAudSStreamStatGet(lbl_1_bss_14) == 0) {
                lbl_1_bss_14 = HuAudBGMPlay(40);
                HuAudFXPlay(25);
                lbl_1_bss_1168[0] = 2;
            }
            break;
    }
    return result;
}

/* 290 insns */
s32 fn_1_12E04(void)
{
    s32 result = 0;
    HuVecF pos = { 288.0f, 150.0f, 1500.0f };

    switch (lbl_1_bss_1168[0]) {
        case 0:
            lbl_1_bss_112E = espEntry(lbl_1_data_2B4[15], 0, 0);
            espDrawNoSet(lbl_1_bss_112E, 0);
            espPosSet(lbl_1_bss_112E, 288.0f, 240.0f);
            espScaleSet(lbl_1_bss_112E, 1.0f, 0.0f);
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_1168[0]++;
            HuAudSStreamFadeOut(lbl_1_bss_14, 1000);
            HuAudFXPlay(26);
            lbl_1_bss_20[9] = HuAudFXPlay(0x450);
            break;
        case 1:
            lbl_1_bss_F14[0] += 0.05f;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
            }
            espScaleSet(lbl_1_bss_112E, 1.0f, lbl_1_bss_F14[0]);
            if (1.0f == lbl_1_bss_F14[0]) {
                lbl_1_bss_1168[0]++;
            }
            break;
        case 2:
            if ((HuPadBtnDown[0] & PAD_BUTTON_A) || (HuPadBtnDown[1] & PAD_BUTTON_A) || (HuPadBtnDown[2] & PAD_BUTTON_A)
                || (HuPadBtnDown[3] & PAD_BUTTON_A)) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[0]++;
            }
            break;
        case 3:
            lbl_1_bss_F14[0] += 0.05;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
            }
            espScaleSet(lbl_1_bss_112E, 1.0f - lbl_1_bss_F14[0], 1.0f);
            if (1.0f == lbl_1_bss_F14[0]) {
                espKill(lbl_1_bss_112E);
                lbl_1_bss_1168[0]++;
            }
            break;
        case 4:
            lbl_1_bss_F14[8] -= 6.0f;
            pos.y += lbl_1_bss_F14[8];
            fn_1_36A70(&pos);
            lbl_1_bss_F14[9] -= 15.0f;
            Hu3DModelRotSet(fn_1_36A60(), 0.0f, lbl_1_bss_F14[9], 0.0f);
            if (lbl_1_bss_F14[8] <= -360.0f) {
                fn_1_36B78();
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 295 insns */
s32 fn_1_1328C(s32 a0)
{
    s32 result = 0;

    switch (lbl_1_bss_1168[2]) {
        case 0:
            lbl_1_bss_F3C[0] = 300;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_112E = espEntry(lbl_1_data_2B4[(a0 < 2) ? 16 : 17], 0, 0);
            espDrawNoSet(lbl_1_bss_112E, 0);
            espPosSet(lbl_1_bss_112E, 210.0f, 100.0f + lbl_1_bss_F3C[0]);
            espTPLvlSet(lbl_1_bss_112E, lbl_1_bss_F14[0]);
            lbl_1_bss_1168[2]++;
            break;
        case 1:
            lbl_1_bss_F3C[0] -= 20;
            if (lbl_1_bss_F3C[0] < 0) {
                lbl_1_bss_1168[2]++;
                lbl_1_bss_F3C[0] = 0;
            }
            if (lbl_1_bss_F3C[0] <= 300) {
                lbl_1_bss_F14[0] += 0.06;
                if (lbl_1_bss_F14[0] > 1.0f) {
                    lbl_1_bss_F14[0] = 1.0f;
                }
            }
            espPosSet(lbl_1_bss_112E, 210.0f, 100.0f + lbl_1_bss_F3C[0]);
            espTPLvlSet(lbl_1_bss_112E, lbl_1_bss_F14[0]);
            if (lbl_1_bss_F3C[0] == 280) {
                lbl_1_bss_8[0] = HuAudJinglePlay((a0 < 2) ? 127 : 138);
                lbl_1_bss_8[1] = 1;
            }
            break;
        case 2:
            break;
        case 3:
            lbl_1_bss_F3C[0] = 0;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_1168[2]++;
            break;
        case 4:
            lbl_1_bss_F14[0] += 0.05;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
            }
            espScaleSet(lbl_1_bss_112E, 1.0f - lbl_1_bss_F14[0] / 2.0f, 1.0f - lbl_1_bss_F14[0] / 2.0f);
            espTPLvlSet(lbl_1_bss_112E, 1.0f - lbl_1_bss_F14[0]);
            if (1.0f == lbl_1_bss_F14[0]) {
                espKill(lbl_1_bss_112E);
                lbl_1_bss_1168[2] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 0x5C8 */ float lbl_1_data_5C8[8] = { 594.0f, 76.0f, 594.0f, 144.0f, 594.0f, 212.0f, 594.0f, 280.0f };

/* 2436 insns */
s32 fn_1_13728(CardGameWork *work)
{
    s32 tbl[2][4];
    HuVecF v;
    s32 ret = 0;
    HuVecF a = { 288.0f, 240.0f, 1800.0f };
    HuVecF b = { 68.0f, 220.0f, 1800.0f };
    HuVecF c = { 508.0f, 220.0f, 1800.0f };
    HuVecF out;
    s32 tmp[2];
    s32 i;
    s32 j;
    float y;

    switch (lbl_1_bss_1168[1]) {
        case 0: {
            s32 done = 0;
            float size[2] = { 352.0f, 352.0f };
            switch (lbl_1_bss_1168[0]) {
                case 0:
                    lbl_1_bss_112E = espEntry(lbl_1_data_2B4[12], 0, 0);
                    espDrawNoSet(lbl_1_bss_112E, 0x40);
                    lbl_1_bss_F3C[0] = 300;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    lbl_1_bss_1168[0]++;
                    HuSprExecLayerSet(0x40, 6);
                    break;
                case 1:
                    lbl_1_bss_F3C[0] -= 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] <= 0) {
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0]++;
                        done = 1;
                    }
                    break;
                case 2:
                    lbl_1_bss_F3C[0] += 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] >= 300) {
                        espKill(lbl_1_bss_112E);
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0] = 0;
                        done = 1;
                    }
                    break;
            }
            if (done) {
                lbl_1_bss_1168[1]++;
            }
            break;
        }
        case 1:
            for (i = 0; i < 4; i++) {
                tbl[0][i] = i;
                tbl[1][i] = frandmod(100);
            }
            for (i = 0; i < 3; i++) {
                for (j = i + 1; j < 4; j++) {
                    if (tbl[1][i] > tbl[1][j]) {
                        tmp[0] = tbl[0][j];
                        tmp[1] = tbl[1][j];
                        tbl[0][j] = tbl[0][i];
                        tbl[1][j] = tbl[1][i];
                        tbl[0][i] = tmp[0];
                        tbl[1][i] = tmp[1];
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                lbl_1_bss_F64[i] = tbl[0][i];
                lbl_1_bss_1126[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[lbl_1_bss_F64[i] + 0x57], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_1126[i], 1);
                lbl_1_bss_F14[0] = 3000.0f;
                lbl_1_bss_F14[8] = 1800.0f;
                Hu3DModelPosSet(lbl_1_bss_1126[i], -500.0f + 300.0f * i + lbl_1_bss_F14[0], 0.0f, 400.0f);
                Hu3DModelRotSet(lbl_1_bss_1126[i], 0.0f, 0.0f, 180.0f);
                Hu3DModelShadowMapSet(lbl_1_bss_1126[i]);
                lbl_1_bss_111E[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[GwPlayerConf[i].charNo + 0x50], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_111E[i], 1);
                Hu3DModelPosSet(lbl_1_bss_111E[i], -500.0f + 300.0f * i - 80.0f, 50.0f, 480.0f);
                Hu3DModelRotSet(lbl_1_bss_111E[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_111E[i], 1);
                Hu3DModelShadowSet(lbl_1_bss_111E[i]);
                lbl_1_bss_1116[i] = Hu3DModelCreate(HuDataSelHeapReadNum(work->player[i].unk28 + lbl_1_data_B0[GwPlayerConf[i].charNo * 3 + 0x24], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_1116[i], 1);
                y = lbl_1_bss_F14[0] + 1200.0f * i;
                Hu3DModelPosSet(lbl_1_bss_1116[i], -275.0f + 150.0f * i, y, -200.0f);
                Hu3DModelRotSet(lbl_1_bss_1116[i], 0.0f, lbl_1_bss_F14[8] + 360.0f * i, 0.0f);
                Hu3DModelShadowSet(lbl_1_bss_1116[i]);
                Hu3DModelShadowDispOff(lbl_1_bss_1116[i]);
                lbl_1_bss_0[i] = Hu3DLLightCreate(lbl_1_bss_1116[i], -275.0f + 150.0f * i, 80.0f + y, 500.0f, 0.0f, 0.0f, -1.0f, 0x60, 0x60, 0x60);
                Hu3DLLightStaticSet(lbl_1_bss_1116[i], lbl_1_bss_0[i], 1);
                Hu3DLLightInfinitytSet(lbl_1_bss_1116[i], lbl_1_bss_0[i]);
            }
            lbl_1_bss_1168[1]++;
            break;
        case 2:
            lbl_1_bss_F14[0] -= 100.0f;
            lbl_1_bss_F14[8] -= 60.0f;
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_F14[0] >= 0.0f) {
                    Hu3DModelPosSet(lbl_1_bss_1126[i], -500.0f + 300.0f * i + lbl_1_bss_F14[0], 0.0f, 400.0f);
                }
                y = lbl_1_bss_F14[0] + 1200.0f * i;
                if (y >= 0.0f) {
                    Hu3DModelRotSet(lbl_1_bss_1116[i], 0.0f, lbl_1_bss_F14[8] + 360.0f * i, 0.0f);
                }
                if (y < 0.0f) {
                    y = 0.0f;
                }
                Hu3DModelPosSet(lbl_1_bss_1116[i], -275.0f + 150.0f * i, y, -200.0f);
                if (y <= 300.0f) {
                    Hu3DModelShadowDispOn(lbl_1_bss_1116[i]);
                }
                if (lbl_1_bss_0[i] != -1) {
                    Hu3DLLightPosSet(lbl_1_bss_1116[i], lbl_1_bss_0[i], -275.0f + 150.0f * i, 80.0f + y, 500.0f, 0.0f, 0.0f, -1.0f);
                }
            }
            v.x = -500.0f + lbl_1_bss_F14[0];
            v.y = 0.0f;
            v.z = 400.0f;
            Hu3D3Dto2D(&v, 1, &out);
            if (lbl_1_bss_20[0] == 0 && out.x <= 576.0f) {
                fn_1_8D04(0x3FD, lbl_1_bss_1126[0], 1);
                lbl_1_bss_20[0] = 1;
            }
            if (lbl_1_bss_F14[0] <= -4800.0f) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[1] = 10;
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_F3C[1] = 0;
                lbl_1_bss_F3C[2] = 0;
                lbl_1_bss_F3C[3] = 0;
                fn_1_36828();
                lbl_1_bss_F14[5] = 300.0f;
                a.y -= lbl_1_bss_F14[5];
                fn_1_36A70(&a);
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 3:
            if (lbl_1_bss_C44 != 0) {
                if (GwPlayerConf[lbl_1_bss_F3C[1]].type != 0) {
                    for (i = 0; i < 10; i++) {
                        HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWComKeyDelayGet());
                    }
                }
                lbl_1_bss_12A8.unk28 = 60;
                lbl_1_bss_12A8.unk8[0] = GwPlayerConf[lbl_1_bss_F3C[1]].charNo;
                fn_1_4FBC8(work, 2);
                lbl_1_bss_C44 = 0;
                Hu3DModelAttrReset(lbl_1_bss_111E[lbl_1_bss_F3C[1]], 1);
                fn_1_36B10(0);
            }
            fn_1_18054(lbl_1_bss_F3C[1], lbl_1_bss_F3C[0]);
            if (GwPlayerConf[lbl_1_bss_F3C[1]].type == 0) {
                fn_1_502E0(0x13);
            }
            if (HuPadDStkRep[lbl_1_bss_F3C[1]] & 2) {
                do {
                    lbl_1_bss_F3C[0]++;
                    if (lbl_1_bss_F3C[0] > 3) {
                        lbl_1_bss_F3C[0] = 0;
                    }
                } while (lbl_1_bss_F64[lbl_1_bss_F3C[0]] == -1);
                if (lbl_1_bss_F3C[1] < 3) {
                    HuAudFXPlay(0);
                }
            }
            else if (HuPadDStkRep[lbl_1_bss_F3C[1]] & 1) {
                do {
                    lbl_1_bss_F3C[0]--;
                    if (lbl_1_bss_F3C[0] < 0) {
                        lbl_1_bss_F3C[0] = 3;
                    }
                } while (lbl_1_bss_F64[lbl_1_bss_F3C[0]] == -1);
                if (lbl_1_bss_F3C[1] < 3) {
                    HuAudFXPlay(0);
                }
            }
            for (i = 0; i < 4; i++) {
                Hu3DModelPosSet(lbl_1_bss_111E[i], -500.0f + 300.0f * lbl_1_bss_F3C[0] - 80.0f, 50.0f, 480.0f);
            }
            if (HuPadBtnDown[lbl_1_bss_F3C[1]] & PAD_BUTTON_A) {
                fn_1_50460();
                if (lbl_1_bss_F64[lbl_1_bss_F3C[0]] != -1) {
                    lbl_1_bss_E9C[0].x = -275.0f + 150.0f * lbl_1_bss_F3C[1];
                    lbl_1_bss_E9C[0].y = 0.0f;
                    lbl_1_bss_E9C[0].z = -200.0f;
                    lbl_1_bss_E9C[1].x = -500.0f + 300.0f * lbl_1_bss_F3C[0];
                    lbl_1_bss_E9C[1].y = 0.0f;
                    lbl_1_bss_E9C[1].z = 200.0f;
                    lbl_1_bss_F14[8] = 0.0f;
                    lbl_1_bss_F14[9] = 1.0f;
                    lbl_1_bss_F3C[8] = 0;
                    lbl_1_bss_F3C[9] = 0;
                    lbl_1_bss_1168[1] = 6;
                    HuAudFXPlay(2);
                }
            }
            break;
        case 4: {
            s32 done = 0;
            float size[2] = { 352.0f, 352.0f };
            switch (lbl_1_bss_1168[0]) {
                case 0:
                    lbl_1_bss_112E = espEntry(lbl_1_data_2B4[12], 0, 0);
                    espDrawNoSet(lbl_1_bss_112E, 0x40);
                    lbl_1_bss_F3C[0] = 300;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    lbl_1_bss_1168[0]++;
                    HuSprExecLayerSet(0x40, 6);
                    break;
                case 1:
                    lbl_1_bss_F3C[0] -= 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] <= 0) {
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0]++;
                        done = 1;
                    }
                    break;
                case 2:
                    lbl_1_bss_F3C[0] += 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[0] / 2 + size[0] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] >= 300) {
                        espKill(lbl_1_bss_112E);
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0] = 0;
                        done = 1;
                    }
                    break;
            }
            if (done) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x3F6, lbl_1_bss_1126[2], 1);
            }
            break;
        }
        case 5:
            lbl_1_bss_F14[0] += 20.0f;
            if (lbl_1_bss_F14[0] <= 180.0f) {
                Hu3DModelRotSet(lbl_1_bss_1126[0], 0.0f, 0.0f, 180.0f + lbl_1_bss_F14[0]);
                Hu3DModelRotSet(lbl_1_bss_1126[1], 0.0f, 0.0f, 180.0f - lbl_1_bss_F14[0]);
                Hu3DModelRotSet(lbl_1_bss_1126[2], 0.0f, 0.0f, 180.0f + lbl_1_bss_F14[0]);
                Hu3DModelRotSet(lbl_1_bss_1126[3], 0.0f, 0.0f, 180.0f - lbl_1_bss_F14[0]);
            }
            if (lbl_1_bss_F14[0] >= 1140.0f) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_F14[1] = 0.0f;
                lbl_1_bss_F14[2] = 0.0f;
                lbl_1_bss_1168[1] = 0;
                ret = 1;
                fn_1_36B10(1);
                lbl_1_bss_12A8.unk38 = 0;
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 3);
            }
            break;
        case 6:
            if (lbl_1_bss_F3C[9] == 0) {
                if (0.0f == lbl_1_bss_F14[8]) {
                    lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                    fn_1_8D04(0x3FF, lbl_1_bss_1116[lbl_1_bss_F3C[1]], 1);
                }
                lbl_1_bss_F14[8] += 72.0f;
                lbl_1_bss_F14[9] -= 0.05f;
                if (lbl_1_bss_F14[9] <= 0.0f) {
                    lbl_1_bss_F14[8] = 0.0f;
                    lbl_1_bss_F14[9] = 0.0f;
                    fn_1_3F278(8, lbl_1_bss_F92[0]);
                    Hu3DModelPosSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], lbl_1_bss_E9C[1].x, 0.0f, lbl_1_bss_E9C[1].z);
                    lbl_1_bss_F3C[9]++;
                }
                Hu3DModelRotSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], 0.0f, lbl_1_bss_F14[8], 0.0f);
                Hu3DModelScaleSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], lbl_1_bss_F14[9], 1.0f, lbl_1_bss_F14[9]);
            }
            else if (lbl_1_bss_F3C[9] == 1) {
                if (0.0f == lbl_1_bss_F14[8]) {
                    lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[1]);
                    Hu3DModelAttrSet(lbl_1_bss_111E[lbl_1_bss_F3C[1]], 1);
                    fn_1_8D04(0x400, lbl_1_bss_1116[lbl_1_bss_F3C[1]], 1);
                }
                lbl_1_bss_F14[8] += 72.0f;
                lbl_1_bss_F14[9] += 0.05f;
                if (lbl_1_bss_F14[9] >= 1.0f) {
                    lbl_1_bss_F14[8] = 0.0f;
                    lbl_1_bss_F14[9] = 1.0f;
                    fn_1_3F278(8, lbl_1_bss_F92[0]);
                    lbl_1_bss_1168[1]++;
                }
                Hu3DModelRotSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], 0.0f, lbl_1_bss_F14[8], 0.0f);
                Hu3DModelScaleSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], lbl_1_bss_F14[9], 1.0f, lbl_1_bss_F14[9]);
                if (lbl_1_bss_0[lbl_1_bss_F3C[1]] != -1) {
                    Hu3DLLightPosSet(lbl_1_bss_1116[lbl_1_bss_F3C[1]], lbl_1_bss_0[lbl_1_bss_F3C[1]], lbl_1_bss_E9C[1].x, 80.0f, 100.0f + lbl_1_bss_E9C[1].z, 0.0f, 0.0f, -1.0f);
                }
            }
            break;
        case 7:
            work->unk174[lbl_1_bss_F64[lbl_1_bss_F3C[0]]] = lbl_1_bss_F3C[1];
            (&lbl_1_bss_F64[4])[lbl_1_bss_F64[lbl_1_bss_F3C[0]]] = lbl_1_bss_F3C[0];
            lbl_1_bss_F64[lbl_1_bss_F3C[0]] = -1;
            lbl_1_bss_F3C[1]++;
            lbl_1_bss_C44 = 1;
            if (lbl_1_bss_F3C[1] == 4) {
                lbl_1_bss_1168[1] = 11;
                a.y -= 80.0f;
                fn_1_4F144(0, c, a, 60, 80.0f, 0x315);
            }
            else {
                do {
                    lbl_1_bss_F3C[0]++;
                    if (lbl_1_bss_F3C[0] > 3) {
                        lbl_1_bss_F3C[0] = 0;
                    }
                } while (lbl_1_bss_F64[lbl_1_bss_F3C[0]] == -1);
                for (i = 0; i < 4; i++) {
                    Hu3DModelPosSet(lbl_1_bss_111E[i], -500.0f + 300.0f * lbl_1_bss_F3C[0] - 80.0f, 50.0f, 480.0f);
                }
                lbl_1_bss_1168[1] = 11;
                if (lbl_1_bss_F3C[1] % 2) {
                    fn_1_4F144(0, b, c, 60, 100.0f, 0x315);
                }
                else {
                    fn_1_4F144(0, c, b, 60, 100.0f, 0x315);
                }
            }
            break;
        case 10:
            lbl_1_bss_F14[5] -= 10.0f;
            if (lbl_1_bss_F14[5] < 0.0f) {
                lbl_1_bss_F14[5] = 0.0f;
            }
            a.y -= lbl_1_bss_F14[5];
            fn_1_36A70(&a);
            if (0.0f == lbl_1_bss_F14[5]) {
                fn_1_36B10(1);
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 1);
                fn_1_36B10(0);
                lbl_1_bss_1168[1] = 11;
                fn_1_4F144(0, a, b, 60, 80.0f, 0x315);
                lbl_1_bss_F14[6] = 0.0f;
            }
            break;
        case 11:
            if (lbl_1_bss_F3C[1] % 2) {
                lbl_1_bss_F14[6] -= 0.5f;
            }
            else if (lbl_1_bss_F3C[1] == 0 || lbl_1_bss_F3C[1] == 4) {
                lbl_1_bss_F14[6] += 0.25f;
            }
            else {
                lbl_1_bss_F14[6] += 0.5f;
            }
            Hu3DModelRotSet(fn_1_36A60(), 0.0f, 0.0f, lbl_1_bss_F14[6]);
            if (fn_1_4F1EC(0, &v)) {
                if (lbl_1_bss_F3C[1] == 4) {
                    lbl_1_bss_1168[1] = 4;
                }
                else {
                    lbl_1_bss_1168[1] = 3;
                    fn_1_36B10(1);
                }
            }
            fn_1_36A70(&v);
            break;
    }
    return ret;
}

/* 533 insns */
s32 fn_1_15D38(CardGameWork *work)
{
    HuVecF pos;
    s16 id;
    s32 ret = -1;

    if (lbl_1_bss_C44 != 0) {
        fn_1_36B10(1);
        lbl_1_bss_12A8.unk38 = 1;
        lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[lbl_1_bss_F3C[2]]].charNo;
        fn_1_4FBC8(work, lbl_1_bss_F3C[2] + 0x21);
        lbl_1_bss_C44 = 0;
        fn_1_36B10(0);
    }
    if (++lbl_1_bss_F3C[3] < 30) {
        return -1;
    }
    if (0.0f == lbl_1_bss_F14[2]) {
        pos.x = -500.0f + 300.0f * (&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]];
        pos.y = 170.0f;
        pos.z = 300.0f;
        id = fn_1_3ED3C(1, pos);
        lbl_1_bss_E9C[0].x = 3.0f;
        lbl_1_bss_E9C[0].y = 3.0f;
        lbl_1_bss_E9C[0].z = 3.0f;
        fn_1_3F6B0(1, id, lbl_1_bss_E9C[0]);
        lbl_1_bss_F14[6] = 360.0f;
        omVibrate(work->unk174[lbl_1_bss_F3C[2]], 15, 12, 0);
        fn_1_8D04(0x40F, lbl_1_bss_1126[(&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]]], 1);
    }
    lbl_1_bss_F14[1] += 20.0f;
    lbl_1_bss_F14[2] += 0.02f;
    if (lbl_1_bss_F14[2] > 1.0f) {
        lbl_1_bss_F14[2] = 1.0f;
    }
    if ((&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]] == 0) {
        Hu3DModelRotSet(lbl_1_bss_1126[0], 0.0f, lbl_1_bss_F14[1], 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_1126[0], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
    }
    else if ((&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]] == 1) {
        Hu3DModelRotSet(lbl_1_bss_1126[1], 0.0f, lbl_1_bss_F14[1], 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_1126[1], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
    }
    else if ((&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]] == 2) {
        Hu3DModelRotSet(lbl_1_bss_1126[2], 0.0f, lbl_1_bss_F14[1], 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_1126[2], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
    }
    else {
        Hu3DModelRotSet(lbl_1_bss_1126[3], 0.0f, lbl_1_bss_F14[1], 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_1126[3], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
    }
    if (lbl_1_bss_F14[2] >= 0.2f) {
        Hu3DModelAttrSet(lbl_1_bss_1116[work->unk174[lbl_1_bss_F3C[2]]], 1);
    }
    if (lbl_1_bss_F14[2] > 0.2f) {
        lbl_1_bss_F14[6] -= 18.0f;
        if (lbl_1_bss_F14[6] < 0.0f) {
            lbl_1_bss_F14[6] = 0.0f;
        }
        Hu3DModelRotSet(fn_1_36A60(), 0.0f, -lbl_1_bss_F14[6], 0.0f);
    }
    if (1.0f == lbl_1_bss_F14[2]) {
        Hu3DModelAttrSet(lbl_1_bss_1126[(&lbl_1_bss_F64[4])[lbl_1_bss_F3C[2]]], 1);
        ret = lbl_1_bss_F3C[2];
        lbl_1_bss_F14[0] = 0.0f;
        lbl_1_bss_F14[1] = 0.0f;
        lbl_1_bss_F14[2] = 0.0f;
        lbl_1_bss_F3C[2]++;
        lbl_1_bss_F3C[3] = 0;
        work->unk170++;
        if (lbl_1_bss_F3C[2] == 4) {
            lbl_1_bss_F3C[2] = 0;
            lbl_1_bss_1168[1] = 0;
            work->unk170 = 0;
            lbl_1_bss_12A8.unk38 = 0;
            fn_1_36B10(0);
            lbl_1_bss_F14[5] = 0.0f;
            lbl_1_bss_F14[6] = 0.0f;
        }
        lbl_1_bss_C44 = 1;
    }
    return ret;
}

/* 524 insns */
s32 fn_1_1658C(CardGameWork *work)
{
    s32 ret = 0;

    switch (lbl_1_bss_1168[1]) {
        case 0: {
            s32 done = 0;
            float size[2] = { 352.0f, 352.0f };
            switch (lbl_1_bss_1168[0]) {
                case 0:
                    lbl_1_bss_112E = espEntry(lbl_1_data_2B4[13], 0, 0);
                    espDrawNoSet(lbl_1_bss_112E, 0);
                    lbl_1_bss_F3C[0] = 300;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    lbl_1_bss_1168[0]++;
                    HuSprExecLayerSet(0x40, 6);
                    break;
                case 1:
                    lbl_1_bss_F3C[0] -= 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] <= 0) {
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0]++;
                        done = 1;
                    }
                    break;
                case 2:
                    lbl_1_bss_F3C[0] += 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] >= 300) {
                        espKill(lbl_1_bss_112E);
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0] = 0;
                        done = 1;
                    }
                    break;
            }
            if (done) {
                lbl_1_bss_1168[1]++;
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 4);
                lbl_1_bss_12A8.unk38 = 1;
            }
            break;
        }
        case 1:
            if (fn_1_16DBC(work)) {
                work->unk170++;
                if (work->unk170 == 4) {
                    work->unk170 = 0;
                    lbl_1_bss_1168[1]++;
                }
                lbl_1_bss_C44 = 1;
            }
            break;
        case 2:
            if (fn_1_30FA4(0, work)) {
                lbl_1_bss_1168[1]++;
            }
            break;
        case 3: {
            s32 done = 0;
            float size[2] = { 352.0f, 352.0f };
            switch (lbl_1_bss_1168[0]) {
                case 0:
                    lbl_1_bss_112E = espEntry(lbl_1_data_2B4[13], 0, 0);
                    espDrawNoSet(lbl_1_bss_112E, 0);
                    lbl_1_bss_F3C[0] = 300;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    lbl_1_bss_1168[0]++;
                    HuSprExecLayerSet(0x40, 6);
                    break;
                case 1:
                    lbl_1_bss_F3C[0] -= 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] <= 0) {
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0]++;
                        done = 1;
                    }
                    break;
                case 2:
                    lbl_1_bss_F3C[0] += 10;
                    espPosSet(lbl_1_bss_112E, 288.0f - size[1] / 2 + size[1] / 2, 78.0f - lbl_1_bss_F3C[0]);
                    if (lbl_1_bss_F3C[0] >= 300) {
                        espKill(lbl_1_bss_112E);
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[0] = 0;
                        done = 1;
                    }
                    break;
            }
            if (done) {
                lbl_1_bss_1168[1]++;
            }
            break;
        }
        case 4:
            lbl_1_bss_1168[1] = 0;
            ret = 1;
            lbl_1_bss_12A8.unk38 = 0;
            lbl_1_bss_12A8.unk28 = 100;
            fn_1_4FBC8(work, 5);
            HuAudSStreamFadeOut(lbl_1_bss_14, 750);
            lbl_1_bss_12A8.unk38 = 1;
            break;
    }
    return ret;
}

/* 907 insns */
s32 fn_1_16DBC(CardGameWork *work)
{
    HuVecF pos;
    s32 ret;
    CardPlayerWork *player;
    s32 x;
    s32 y;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_1168[2]) {
        case 0:
            if (fn_1_30FA4(1, work)) {
                lbl_1_bss_1168[2]++;
                fn_1_17BE8(work, 0);
                fn_1_9DA8(&pos, work);
                lbl_1_bss_1080[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[116], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_1080[0], 1);
                Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelLayerSet(lbl_1_bss_1080[0], 4);
                Hu3DModelAttrSet(lbl_1_bss_1080[0], 0x40000001);
                Hu3DModelAttrSet(lbl_1_bss_1080[0], 1);
                lbl_1_bss_1080[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[117], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_1080[1], 1);
                Hu3DModelPosSet(lbl_1_bss_1080[1], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelLayerSet(lbl_1_bss_1080[1], 4);
                Hu3DModelAttrSet(lbl_1_bss_1080[1], 0x40000001);
                Hu3DModelAttrSet(lbl_1_bss_1080[1], 1);
                lbl_1_bss_F14[0] = 0.0f;
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
            }
            break;
        case 1:
            fn_1_17BE8(work, 0);
            fn_1_9DA8(&pos, work);
            Hu3DModelPosSet(lbl_1_bss_470[work->unk174[work->unk170]], -50.0f + pos.x, pos.y, pos.z);
            Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + pos.x, pos.y, pos.z);
            lbl_1_bss_F14[0] += 0.05f;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
                lbl_1_bss_1168[2]++;
            }
            Hu3DModelScaleSet(lbl_1_bss_470[work->unk174[work->unk170]], 1.0f, lbl_1_bss_F14[0], lbl_1_bss_F14[0]);
            break;
        case 2:
            if (lbl_1_bss_C44 != 0) {
                lbl_1_bss_12A8.unk28 = 60;
                lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
                fn_1_4FBC8(work, 0x20);
                lbl_1_bss_C44 = 0;
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    fn_1_502E0(0x13);
                }
            }
            fn_1_18054(work->unk174[work->unk170], player->unk0);
            if (HuPadDStkRep[work->unk174[work->unk170]] & 8) {
                if (player->unk0 == 3 || player->unk0 == 4) {
                    if (player->unk10 == 0) {
                        player->unk0 = 1;
                    }
                    else {
                        player->unk10--;
                    }
                    HuAudFXPlay(0);
                }
                fn_1_17BE8(work, 1);
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & 4) {
                if (player->unk0 == 3 || player->unk0 == 4) {
                    if (player->unk10 == work->unk194 - 1) {
                        player->unk0 = 2;
                    }
                    else {
                        player->unk10++;
                    }
                    HuAudFXPlay(0);
                }
                fn_1_17BE8(work, 2);
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & 1) {
                if (player->unk0 == 1 || player->unk0 == 2) {
                    if (player->unk14 == 0) {
                        player->unk0 = 3;
                    }
                    else {
                        player->unk14--;
                    }
                    HuAudFXPlay(0);
                }
                fn_1_17BE8(work, 3);
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & 2) {
                if (player->unk0 == 1 || player->unk0 == 2) {
                    if (player->unk14 == work->unk194 - 1) {
                        player->unk0 = 4;
                    }
                    else {
                        player->unk14++;
                    }
                    HuAudFXPlay(0);
                }
                fn_1_17BE8(work, 4);
            }
            fn_1_9DA8(&pos, work);
            Hu3DModelPosSet(lbl_1_bss_470[work->unk174[work->unk170]], -50.0f + pos.x, pos.y, pos.z);
            Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + pos.x, pos.y, pos.z);
            if (player->unk0 == 1 || player->unk0 == 2) {
                Hu3DModelAttrReset(lbl_1_bss_1080[0], 1);
                Hu3DModelAttrSet(lbl_1_bss_1080[1], 1);
            }
            else {
                Hu3DModelAttrReset(lbl_1_bss_1080[1], 1);
                Hu3DModelAttrSet(lbl_1_bss_1080[0], 1);
            }
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, pos.y, pos.z);
            Hu3DModelPosSet(lbl_1_bss_1080[1], -50.0f + pos.x, pos.y, pos.z);
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                fn_1_50460();
                Hu3DModelKill(lbl_1_bss_1080[0]);
                Hu3DModelKill(lbl_1_bss_1080[1]);
                player->unk4 = player->unk0;
                player->unk8 = player->unk10;
                player->unkC = player->unk14;
                if (player->unk0 == 1) {
                    x = player->unk10 - 1;
                    y = player->unk14;
                }
                else if (player->unk0 == 2) {
                    x = player->unk10 + 1;
                    y = player->unk14;
                }
                else if (player->unk0 == 3) {
                    x = player->unk10;
                    y = player->unk14 - 1;
                }
                else if (player->unk0 == 4) {
                    x = player->unk10;
                    y = player->unk14 + 1;
                }
                fn_1_9C74(&pos, x, y, 1, 1);
                pos.x += -50.0f;
                fn_1_3ED3C(15, pos);
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, 0.0f, 0.0f);
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[2]++;
                if (player->unk0 == 1) {
                    lbl_1_bss_8C4[player->unk10][player->unk14] |= 0x10000;
                }
                else if (player->unk0 == 2) {
                    lbl_1_bss_8C4[player->unk10][player->unk14] |= 0x20000;
                }
                else if (player->unk0 == 3) {
                    lbl_1_bss_8C4[player->unk10][player->unk14] |= 0x40000;
                }
                else if (player->unk0 == 4) {
                    lbl_1_bss_8C4[player->unk10][player->unk14] |= 0x80000;
                }
                fn_1_8D04(0x3F8, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                HuAudFXPlay(2);
                lbl_1_bss_0[work->unk174[work->unk170]] = Hu3DLLightCreate(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + pos.x, 80.0f + pos.y,
                    100.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x60, 0x60, 0x60);
                Hu3DLLightStaticSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_0[work->unk174[work->unk170]], 1);
                Hu3DLLightInfinitytSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_0[work->unk174[work->unk170]]);
            }
            fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
            pos.x += 150.0f;
            pos.y += 100.0f;
            fn_1_31788(&pos);
            pos.x = pos.x;
            pos.y = 1500.0f + pos.y;
            pos.z = 3000.0f + pos.z;
            fn_1_31710(&pos);
            break;
        case 3:
            if (lbl_1_bss_F3C[0] == 98) {
                fn_1_8D04(0x412, lbl_1_bss_468[work->unk174[work->unk170]], 1);
            }
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] >= 100) {
                lbl_1_bss_F14[0] += 0.05f;
                if (lbl_1_bss_F14[0] > 1.0f) {
                    lbl_1_bss_F14[0] = 1.0f;
                }
                Hu3DModelAttrReset(lbl_1_bss_468[work->unk174[work->unk170]], 1);
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_F14[0], lbl_1_bss_F14[0], lbl_1_bss_F14[0]);
            }
            if (lbl_1_bss_F3C[0] >= 200) {
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[2] = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 283 insns */
void fn_1_17BE8(CardGameWork *work, s32 a1)
{
    s32 unused0 = 0;
    s32 unused1 = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    while (TRUE) {
        if ((lbl_1_bss_8C4[player->unk10][player->unk14] & 0x80) || (player->unk0 == 1 && (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x10000))
            || (player->unk0 == 2 && (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x20000))
            || (player->unk0 == 3 && (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40000))
            || (player->unk0 == 4 && (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x80000))) {
            if (a1 == 1) {
                if (player->unk0 == 1) {
                    if (player->unk14 == 0) {
                        a1 = 4;
                        player->unk14++;
                    }
                    else {
                        a1 = 3;
                        player->unk14--;
                    }
                }
                else if (player->unk10 == 0) {
                    if (player->unk0 == 3) {
                        a1 = 4;
                    }
                    else {
                        a1 = 3;
                    }
                    player->unk0 = 1;
                }
                else {
                    player->unk10--;
                }
            }
            else if (a1 == 2) {
                if (player->unk0 == 2) {
                    if (player->unk14 == 0) {
                        a1 = 4;
                        player->unk14++;
                    }
                    else {
                        a1 = 3;
                        player->unk14--;
                    }
                }
                else if (player->unk10 == work->unk194 - 1) {
                    if (player->unk0 == 3) {
                        a1 = 4;
                    }
                    else {
                        a1 = 3;
                    }
                    player->unk0 = 2;
                }
                else {
                    player->unk10++;
                }
            }
            else if (a1 == 3) {
                if (player->unk0 == 3) {
                    if (player->unk10 == 0) {
                        a1 = 2;
                        player->unk10++;
                    }
                    else {
                        a1 = 1;
                        player->unk10--;
                    }
                }
                else if (player->unk14 == 0) {
                    if (player->unk0 == 1) {
                        a1 = 2;
                    }
                    else {
                        a1 = 1;
                    }
                    player->unk0 = 3;
                }
                else {
                    player->unk14--;
                }
            }
            else if (a1 == 4) {
                if (player->unk0 == 4) {
                    if (player->unk10 == 0) {
                        a1 = 2;
                        player->unk10++;
                    }
                    else {
                        a1 = 1;
                        player->unk10--;
                    }
                }
                else if (player->unk14 == work->unk194 - 1) {
                    if (player->unk0 == 1) {
                        a1 = 2;
                    }
                    else {
                        a1 = 1;
                    }
                    player->unk0 = 4;
                }
                else {
                    player->unk14++;
                }
            }
            else if (player->unk0 == 1) {
                if (player->unk14 == 0) {
                    player->unk0 = 3;
                }
                else {
                    player->unk14--;
                }
            }
            else if (player->unk0 == 2) {
                if (player->unk14 == work->unk194 - 1) {
                    player->unk0 = 4;
                }
                else {
                    player->unk14++;
                }
            }
            else if (player->unk0 == 3) {
                if (player->unk10 == work->unk194 - 1) {
                    player->unk0 = 2;
                }
                else {
                    player->unk10++;
                }
            }
            else if (player->unk0 == 4) {
                if (player->unk10 == 0) {
                    player->unk0 = 1;
                }
                else {
                    player->unk10--;
                }
            }
        }
        else {
            break;
        }
    }
}

/* 163 insns */
void fn_1_18054(s32 playerNo, s32 a1)
{
    if (GwPlayerConf[playerNo].type != 0) {
        HuPadBtnDown[playerNo] = 0;
        HuPadDStkRep[playerNo] = 0;
        if (lbl_1_bss_C48[1] == 0) {
            if (lbl_1_bss_1174 == 0) {
                lbl_1_bss_C48[1] = frandmod(30) + 31;
            }
            else if (lbl_1_bss_1174 == 3) {
                lbl_1_bss_C48[1] = frandmod(120) + 31;
            }
        }
        lbl_1_bss_C48[0]++;
        if (lbl_1_bss_C48[0] == lbl_1_bss_C48[1]) {
            HuPadBtnDown[playerNo] = PAD_BUTTON_A;
            lbl_1_bss_C48[0] = 0;
            lbl_1_bss_C48[1] = 0;
        }
        else if (lbl_1_bss_1174 == 0) {
            if (lbl_1_bss_C48[0] % 10 == 0) {
                HuPadDStkRep[playerNo] = frandmod(2) ? PAD_BUTTON_RIGHT : PAD_BUTTON_LEFT;
            }
        }
        else if (lbl_1_bss_1174 == 3) {
            if (lbl_1_bss_C48[0] % 20 == 0) {
                HuPadDStkRep[playerNo] = (a1 <= 2) ? (frandmod(2) ? PAD_BUTTON_LEFT : PAD_BUTTON_RIGHT) : (frandmod(2) ? PAD_BUTTON_UP : PAD_BUTTON_DOWN);
            }
        }
    }
}

/* 327 insns */
s32 fn_1_182E0(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    switch (lbl_1_bss_1168[0]) {
        case 0:
            espDispOn(lbl_1_bss_FA2[work->unk170]);
            lbl_1_bss_F3C[0] = 300;
            espPosSet(lbl_1_bss_FA2[work->unk170], 200.0f, 240.0f + lbl_1_bss_F3C[0]);
            espScaleSet(lbl_1_bss_FA2[work->unk170], 1.0f, 1.0f);
            espZRotSet(lbl_1_bss_FA2[work->unk170], 0.0f);
            espTPLvlSet(lbl_1_bss_FA2[work->unk170], 1.0f);
            lbl_1_bss_1168[0]++;
            HuAudFXPlay(0x2FD);
            break;
        case 1:
            lbl_1_bss_F3C[0] -= 20;
            if (lbl_1_bss_F3C[0] == 20) {
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
            }
            if (lbl_1_bss_F3C[0] == 0) {
                lbl_1_bss_1168[0]++;
            }
            espPosSet(lbl_1_bss_FA2[work->unk170], 200.0f, 240.0f + lbl_1_bss_F3C[0]);
            break;
        case 2:
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                lbl_1_bss_F14[0] = 1.0f;
                lbl_1_bss_F14[1] = 0.0f;
                lbl_1_bss_F14[2] = 1.0f;
                lbl_1_bss_1168[0]++;
            }
            break;
        case 3:
            lbl_1_bss_F14[0] -= 0.02;
            if (lbl_1_bss_F14[0] < 0.0f) {
                lbl_1_bss_F14[0] = 0.0f;
            }
            espScaleSet(lbl_1_bss_FA2[work->unk170], lbl_1_bss_F14[0], lbl_1_bss_F14[0]);
            lbl_1_bss_F14[1] += 10.0f;
            if (lbl_1_bss_F14[1] > 350.0f) {
                lbl_1_bss_F14[1] = 0.0f;
            }
            espZRotSet(lbl_1_bss_FA2[work->unk170], lbl_1_bss_F14[1]);
            lbl_1_bss_F14[2] -= 0.02;
            if (lbl_1_bss_F14[2] < 0.0f) {
                lbl_1_bss_F14[2] = 0.0f;
                espDispOff(lbl_1_bss_FA2[work->unk170]);
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            espTPLvlSet(lbl_1_bss_FA2[work->unk170], lbl_1_bss_F14[2]);
            break;
    }
    return result;
}

/* 1086 insns */
s32 fn_1_187FC(CardGameWork *work, s32 a1)
{
    s32 i;
    s32 j;
    s32 n;
    CardPlayerWork *player;
    s32 playerNo;
    HUWIN *win;
    s32 result = 0;

    switch (lbl_1_bss_1168[0]) {
        case 0:
            for (i = 0; i < 4; i++) {
                player = &work->player[work->unk174[i]];
                n = 0;
                for (j = 0; j < player->unk44; j++) {
                    lbl_1_bss_1086[i][n] = espEntry(lbl_1_data_2B4[8], 0, 0);
                    espDrawNoSet(lbl_1_bss_1086[i][n], 0);
                    espBankSet(lbl_1_bss_1086[i][n], 1);
                    espPosSet(lbl_1_bss_1086[i][n], 25.0f * n + ((float (*)[2])lbl_1_data_5C8)[i][0], ((float (*)[2])lbl_1_data_5C8)[i][1]);
                    n++;
                }
                for (j = 0; j < player->unk48; j++) {
                    lbl_1_bss_1086[i][n] = espEntry(lbl_1_data_2B4[8], 0, 0);
                    espDrawNoSet(lbl_1_bss_1086[i][n], 0);
                    espBankSet(lbl_1_bss_1086[i][n], 2);
                    espPosSet(lbl_1_bss_1086[i][n], 25.0f * n + ((float (*)[2])lbl_1_data_5C8)[i][0], ((float (*)[2])lbl_1_data_5C8)[i][1]);
                    n++;
                }
                for (j = 0; j < player->unk4C; j++) {
                    lbl_1_bss_1086[i][n] = espEntry(lbl_1_data_2B4[8], 0, 0);
                    espDrawNoSet(lbl_1_bss_1086[i][n], 0);
                    espBankSet(lbl_1_bss_1086[i][n], 3);
                    espPosSet(lbl_1_bss_1086[i][n], 25.0f * n + ((float (*)[2])lbl_1_data_5C8)[i][0], ((float (*)[2])lbl_1_data_5C8)[i][1]);
                    n++;
                }
                lbl_1_bss_F64[i] = n;
            }
            lbl_1_bss_5E = 0;
            Hu3DModelAttrReset(lbl_1_bss_5C, HU3D_ATTR_DISPOFF);
            lbl_1_bss_1134 = 0;
            lbl_1_bss_1130 = 0;
            lbl_1_bss_1168[0]++;
            break;
        case 1:
            lbl_1_bss_1134 = (lbl_1_bss_1130 == 0) ? lbl_1_bss_1134 + 20 : lbl_1_bss_1134 - 20;
            for (i = 0; i < 4; i++) {
                espPosSet(lbl_1_bss_1002[i], ((float (*)[2])lbl_1_data_448)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_448)[i][1]);
                espPosSet(lbl_1_bss_100A[i][0], ((float (*)[2])lbl_1_data_428)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][1], ((float (*)[2])lbl_1_data_428)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][2], ((float (*)[2])lbl_1_data_428)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_100A[i][3], ((float (*)[2])lbl_1_data_428)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_428)[i][1]);
                espPosSet(lbl_1_bss_FEA[i], ((float (*)[2])lbl_1_data_4A8)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_4A8)[i][1]);
                espPosSet(lbl_1_bss_FE2[i], ((float (*)[2])lbl_1_data_4C8)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_4C8)[i][1]);
                espPosSet(lbl_1_bss_FDA[i], ((float (*)[2])lbl_1_data_4E8)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_4E8)[i][1]);
                espPosSet(lbl_1_bss_FD2[i], ((float (*)[2])lbl_1_data_508)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_508)[i][1]);
                espPosSet(lbl_1_bss_FCA[i], ((float (*)[2])lbl_1_data_528)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_528)[i][1]);
                espPosSet(lbl_1_bss_FC2[i], ((float (*)[2])lbl_1_data_548)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_548)[i][1]);
                espPosSet(lbl_1_bss_FBA[i], ((float (*)[2])lbl_1_data_568)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_568)[i][1]);
                espPosSet(lbl_1_bss_FB2[i], ((float (*)[2])lbl_1_data_588)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_588)[i][1]);
                espPosSet(lbl_1_bss_FAA[i], ((float (*)[2])lbl_1_data_5A8)[i][0] - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_5A8)[i][1]);
                espPosSet(lbl_1_bss_FFA[i], ((float (*)[2])lbl_1_data_468)[i][0] - lbl_1_bss_1134 / 2.0f, ((float (*)[2])lbl_1_data_468)[i][1]);
                espScaleSet(lbl_1_bss_FFA[i], 1.0f + 2.5f * (lbl_1_bss_1134 / 20), 1.0f);
                for (j = 0; j < lbl_1_bss_F64[i]; j++) {
                    espPosSet(lbl_1_bss_1086[i][j], (25.0f * j + ((float (*)[2])lbl_1_data_5C8)[i][0]) - lbl_1_bss_1134, ((float (*)[2])lbl_1_data_5C8)[i][1]);
                }
            }
            if (lbl_1_bss_1130 == 0) {
                lbl_1_bss_5E = (lbl_1_bss_5E <= 140) ? lbl_1_bss_5E + 10 : 150;
                if (lbl_1_bss_1134 == 360) {
                    lbl_1_bss_1130 = 1;
                    lbl_1_bss_1168[0]++;
                }
            }
            else {
                lbl_1_bss_5E = (lbl_1_bss_5E >= 10) ? lbl_1_bss_5E - 10 : 0;
                if (lbl_1_bss_1134 == 0) {
                    for (i = 0; i < 4; i++) {
                        for (j = 0; j < lbl_1_bss_F64[i]; j++) {
                            espKill(lbl_1_bss_1086[i][j]);
                        }
                    }
                    Hu3DModelAttrSet(lbl_1_bss_5C, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_1130 = 0;
                    lbl_1_bss_1168[0] = 0;
                    result = 1;
                }
            }
            if (a1 != -1) {
                espColorSet(lbl_1_bss_F9E[0], 255 - lbl_1_bss_5E, 255 - lbl_1_bss_5E, 255 - lbl_1_bss_5E);
                espColorSet(lbl_1_bss_F9E[1], 255 - lbl_1_bss_5E, 255 - lbl_1_bss_5E, 255 - lbl_1_bss_5E);
            }
            break;
        case 2:
            fn_1_502E0(0x16);
            playerNo = (a1 == -1) ? work->unk174[work->unk170] : a1;
            if (HuPadBtnDown[playerNo] & PAD_BUTTON_START) {
                fn_1_50460();
                lbl_1_bss_1168[0]--;
                HuAudFXPlay(0x3FC);
                HuAudSStreamVolSet(0, 127, 500);
            }
            else if (HuPadBtnDown[playerNo] & PAD_BUTTON_X) {
                HuAudFXPlay(2);
                fn_1_50460();
                lbl_1_bss_12A8.unk38 = 0;
                fn_1_4FBFC(work, 0x43);
                lbl_1_bss_1168[0]++;
            }
            break;
        case 3:
            playerNo = (a1 == -1) ? work->unk174[work->unk170] : a1;
            win = &winData[lbl_1_bss_12A8.unk44];
            win->padMask = 1 << GwPlayerConf[playerNo].padNo;
            if (HuWinChoiceGet(lbl_1_bss_12A8.unk44, 1) == 0) {
                result = -1;
                HuAudSStreamFadeOut(lbl_1_bss_14, 1000);
            }
            else {
                lbl_1_bss_1168[0]--;
            }
            lbl_1_bss_12A8.unk38 = 1;
            fn_1_4FFEC();
            break;
    }
    return result;
}

/* 0x618 */ HuVecF lbl_1_data_618[4] = { { 64.0f, 80.0f, 0.0f }, { 512.0f, 80.0f, 0.0f }, { 64.0f, 280.0f, 0.0f }, { 512.0f, 280.0f, 0.0f } };

/* 1166 insns */
s32 fn_1_198F4(CardGameWork *work)
{
    s32 i;
    s32 charNo;
    float mag;
    GXColor color;
    HuVecF out;
    s32 result = 0;

    switch (lbl_1_bss_1168[2]) {
        case 0:
            lbl_1_bss_C10 = 0;
            for (i = 0; i < 4; i++) {
                lbl_1_bss_C1C[i] = espEntry(lbl_1_data_2B4[0], 0, 0);
                espDrawNoSet(lbl_1_bss_C1C[i], 0x40);
                espBankSet(lbl_1_bss_C1C[i], GwPlayerConf[work->unk174[i]].charNo);
                espPosSet(lbl_1_bss_C1C[i], lbl_1_data_618[i].x, lbl_1_data_618[i].y);
                espPriSet(lbl_1_bss_C1C[i], 0x1C0);
                espDispOff(lbl_1_bss_C1C[i]);
                lbl_1_bss_C14[i] = espEntry(DATANUM(DATA_card, 222), 0, 0);
                espDrawNoSet(lbl_1_bss_C14[i], 0x40);
                espPosSet(lbl_1_bss_C14[i], lbl_1_data_618[i].x, lbl_1_data_618[i].y);
                espPriSet(lbl_1_bss_C14[i], 0x1D0);
                espDispOff(lbl_1_bss_C14[i]);
            }
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 2);
            lbl_1_bss_1168[2]++;
            break;
        case 1:
            if (WipeCheckEnd() == 0) {
                for (i = 0; i < 4; i++) {
                    espPosSet(lbl_1_bss_1002[i], 288.0f + ((float (*)[2])lbl_1_data_448)[i][0], ((float (*)[2])lbl_1_data_448)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][0], 288.0f + ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][1], 288.0f + ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][2], 288.0f + ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][3], 288.0f + ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_FEA[i], 288.0f + ((float (*)[2])lbl_1_data_4A8)[i][0], ((float (*)[2])lbl_1_data_4A8)[i][1]);
                    espPosSet(lbl_1_bss_FE2[i], 288.0f + ((float (*)[2])lbl_1_data_4C8)[i][0], ((float (*)[2])lbl_1_data_4C8)[i][1]);
                    espPosSet(lbl_1_bss_FDA[i], 288.0f + ((float (*)[2])lbl_1_data_4E8)[i][0], ((float (*)[2])lbl_1_data_4E8)[i][1]);
                    espPosSet(lbl_1_bss_FD2[i], 288.0f + ((float (*)[2])lbl_1_data_508)[i][0], ((float (*)[2])lbl_1_data_508)[i][1]);
                    espPosSet(lbl_1_bss_FCA[i], 288.0f + ((float (*)[2])lbl_1_data_528)[i][0], ((float (*)[2])lbl_1_data_528)[i][1]);
                    espPosSet(lbl_1_bss_FC2[i], 288.0f + ((float (*)[2])lbl_1_data_548)[i][0], ((float (*)[2])lbl_1_data_548)[i][1]);
                    espPosSet(lbl_1_bss_FBA[i], 288.0f + ((float (*)[2])lbl_1_data_568)[i][0], ((float (*)[2])lbl_1_data_568)[i][1]);
                    espPosSet(lbl_1_bss_FB2[i], 288.0f + ((float (*)[2])lbl_1_data_588)[i][0], ((float (*)[2])lbl_1_data_588)[i][1]);
                    espPosSet(lbl_1_bss_FAA[i], 288.0f + ((float (*)[2])lbl_1_data_5A8)[i][0], ((float (*)[2])lbl_1_data_5A8)[i][1]);
                    espPosSet(lbl_1_bss_FFA[i], 288.0f + ((float (*)[2])lbl_1_data_468)[i][0], ((float (*)[2])lbl_1_data_468)[i][1]);
                    espPosSet(lbl_1_bss_FF2[i], 288.0f + ((float (*)[2])lbl_1_data_488)[i][0], ((float (*)[2])lbl_1_data_468)[i][1]);
                }
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 15);
                lbl_1_bss_C30 = Hu3DCamera[0].pos;
                lbl_1_bss_C24 = Hu3DCamera[0].target;
                Hu3DCamera[0].target = (HuVecF) { 0.0f, 0.0f, 300.0f + 30.0f * (work->unk194 - 6) };
                Hu3DCamera[0].up = (HuVecF) { 0.0f, 0.0f, -1.0f };
                Hu3DCamera[0].pos = (HuVecF) { 0.0f, 11000.0f + 1200.0f * (work->unk194 - 6), 300.0f + 30.0f * (work->unk194 - 6) };
                lbl_1_bss_1168[2]++;
            }
            break;
        case 2:
            if (WipeCheckEnd() == 0) {
                for (i = 0; i < 4; i++) {
#ifdef __MWERKS__
                    /* retail passes the position struct itself to the unprototyped call; the EABI hands the
                     * callee a pointer to a stack copy, so it works on GameCube */
                    Hu3D3Dto2D(Hu3DData[lbl_1_bss_468[work->unk174[i]]].pos, 1, &out);
#else
                    {
                        HuVecF pos = Hu3DData[lbl_1_bss_468[work->unk174[i]]].pos;
                        Hu3D3Dto2D(&pos, 1, &out);
                    }
#endif
                    PSVECSubtract(&out, &lbl_1_data_618[i], &out);
                    mag = PSVECMag(&out);
                    espScaleSet(lbl_1_bss_C14[i], 0.5f, mag / 31.0f);
                    espPosSet(lbl_1_bss_C14[i], out.x / 2.0f + lbl_1_data_618[i].x, out.y / 2.0f + lbl_1_data_618[i].y);
                    PSVECNormalize(&out, &out);
                    mag = -(180.0 * (atan2(out.x, out.y) / 3.141592653589793));
                    espZRotSet(lbl_1_bss_C14[i], 180.0f + mag);
                    charNo = work->player[work->unk174[i]].unk2C;
                    if (charNo >= 5) {
                        charNo++;
                    }
                    if (charNo > 7) {
                        charNo = 7;
                    }
                    GWCharColorGet(charNo, &color);
                    espColorSet(lbl_1_bss_C14[i], color.r, color.g, color.b);
                }
                fn_1_502E0(0x15);
                lbl_1_bss_1168[2]++;
            }
            break;
        case 3:
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_C10 == 0) {
                        espDispOn(lbl_1_bss_C1C[i]);
                        espDispOn(lbl_1_bss_C14[i]);
                    }
                    else {
                        espDispOff(lbl_1_bss_C1C[i]);
                        espDispOff(lbl_1_bss_C14[i]);
                    }
                }
                lbl_1_bss_C10 ^= 1;
            }
            if (HuPadBtnDown[work->unk174[work->unk170]] & (PAD_BUTTON_B | PAD_TRIGGER_R)) {
                for (i = 0; i < 4; i++) {
                    espKill(lbl_1_bss_C1C[i]);
                    espKill(lbl_1_bss_C14[i]);
                }
                for (i = 0; i < 4; i++) {
                    espPosSet(lbl_1_bss_1002[i], ((float (*)[2])lbl_1_data_448)[i][0], ((float (*)[2])lbl_1_data_448)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][0], ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][1], ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][2], ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_100A[i][3], ((float (*)[2])lbl_1_data_428)[i][0], ((float (*)[2])lbl_1_data_428)[i][1]);
                    espPosSet(lbl_1_bss_FEA[i], ((float (*)[2])lbl_1_data_4A8)[i][0], ((float (*)[2])lbl_1_data_4A8)[i][1]);
                    espPosSet(lbl_1_bss_FE2[i], ((float (*)[2])lbl_1_data_4C8)[i][0], ((float (*)[2])lbl_1_data_4C8)[i][1]);
                    espPosSet(lbl_1_bss_FDA[i], ((float (*)[2])lbl_1_data_4E8)[i][0], ((float (*)[2])lbl_1_data_4E8)[i][1]);
                    espPosSet(lbl_1_bss_FD2[i], ((float (*)[2])lbl_1_data_508)[i][0], ((float (*)[2])lbl_1_data_508)[i][1]);
                    espPosSet(lbl_1_bss_FCA[i], ((float (*)[2])lbl_1_data_528)[i][0], ((float (*)[2])lbl_1_data_528)[i][1]);
                    espPosSet(lbl_1_bss_FC2[i], ((float (*)[2])lbl_1_data_548)[i][0], ((float (*)[2])lbl_1_data_548)[i][1]);
                    espPosSet(lbl_1_bss_FBA[i], ((float (*)[2])lbl_1_data_568)[i][0], ((float (*)[2])lbl_1_data_568)[i][1]);
                    espPosSet(lbl_1_bss_FB2[i], ((float (*)[2])lbl_1_data_588)[i][0], ((float (*)[2])lbl_1_data_588)[i][1]);
                    espPosSet(lbl_1_bss_FAA[i], ((float (*)[2])lbl_1_data_5A8)[i][0], ((float (*)[2])lbl_1_data_5A8)[i][1]);
                    espPosSet(lbl_1_bss_FFA[i], ((float (*)[2])lbl_1_data_468)[i][0], ((float (*)[2])lbl_1_data_468)[i][1]);
                    espPosSet(lbl_1_bss_FF2[i], ((float (*)[2])lbl_1_data_488)[i][0], ((float (*)[2])lbl_1_data_468)[i][1]);
                }
                fn_1_50460();
                Hu3DCamera[0].pos = lbl_1_bss_C30;
                Hu3DCamera[0].target = lbl_1_bss_C24;
                Hu3DCamera[0].up = (HuVecF) { 0.0f, 1.0f, 0.0f };
                lbl_1_bss_1168[2] = 0;
                result = 1;
                HuAudFXPlay(0x3FC);
                HuAudSStreamVolSet(0, 127, 100);
            }
            break;
    }
    return result;
}

/* 497 insns */
s32 fn_1_1AB2C(CardGameWork *work)
{
    float angle;
    HuVecF target;
    HuVecF move;
    s32 result = 0;
    float speed = 1.0f;

    switch (lbl_1_bss_1168[2]) {
        case 0:
            lbl_1_bss_C30 = Hu3DCamera[0].pos;
            lbl_1_bss_C24 = Hu3DCamera[0].target;
            target = Hu3DCamera[0].target;
            target.y = 3500.0f;
            target.z += 2000.0f;
            lbl_1_bss_C04 = Hu3DCamera[0].target;
            fn_1_317F0(&Hu3DCamera[0].pos, &target, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
            lbl_1_bss_1168[2]++;
            break;
        case 1:
            if (fn_1_319D4(30.0f)) {
                fn_1_502E0(0x14);
                lbl_1_bss_1168[2]++;
            }
            break;
        case 2:
            if (HuPadBtn[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                speed = 2.0f;
            }
            move.x = HuPadStkX[work->unk174[work->unk170]];
            move.y = 0.0f;
            move.z = HuPadStkY[work->unk174[work->unk170]];
            if (move.x || move.z) {
                angle = 180.0 * (atan2(move.x, -move.z) / 3.141592653589793);
                move.x = 20.0f * speed * sin(3.141592653589793 * angle / 180.0);
                move.z = 20.0f * speed * cos(3.141592653589793 * angle / 180.0);
            }
            PSVECAdd(&move, &lbl_1_bss_C04, &lbl_1_bss_C04);
            if (lbl_1_bss_C04.x < -150.0f * (work->unk194 + 1)) {
                lbl_1_bss_C04.x = -150.0f * (work->unk194 + 1);
            }
            if (lbl_1_bss_C04.x > 150.0f * (work->unk194 + 1)) {
                lbl_1_bss_C04.x = 150.0f * (work->unk194 + 1);
            }
            if (lbl_1_bss_C04.z < -150.0f * (work->unk194 + 1)) {
                lbl_1_bss_C04.z = -150.0f * (work->unk194 + 1);
            }
            if (lbl_1_bss_C04.z > 150.0f * (work->unk194 + 1)) {
                lbl_1_bss_C04.z = 150.0f * (work->unk194 + 1);
            }
            PSVECSubtract(&lbl_1_bss_C04, &Hu3DCamera[0].target, &move);
            PSVECScale(&move, &move, 0.12f);
            PSVECAdd(&move, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
            Hu3DCamera[0].pos = (HuVecF) { Hu3DCamera[0].target.x, 3500.0f, 2000.0f + Hu3DCamera[0].target.z };
            if (HuPadBtnDown[work->unk174[work->unk170]] & (PAD_BUTTON_B | PAD_BUTTON_Y)) {
                fn_1_50460();
                Hu3DCamera[0].pos = lbl_1_bss_C30;
                Hu3DCamera[0].target = lbl_1_bss_C24;
                fn_1_317F0(&Hu3DCamera[0].pos, &Hu3DCamera[0].pos, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
                lbl_1_bss_1168[2] = 0;
                result = 1;
                HuAudFXPlay(0x3FC);
                HuAudSStreamVolSet(0, 127, 100);
            }
            break;
    }
    return result;
}

/* 5821 insns */
s32 fn_1_1B2F0(CardGameWork *work)
{
    HuVecF pos;
    s32 cards[3];
    CardPlayerWork *player;
    s32 ret;
    s32 idx;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    fn_1_9DA8(&pos, work);
    if (player->unk34 == -1) {
        ret = 1;
    }
    else if (player->unk50 & 0x20) {
        ret = 1;
    }
    else {
        switch (lbl_1_bss_1168[0]) {
            case 0:
                if (fn_1_30FA4(7, work)) {
                    lbl_1_bss_E98 = 0;
                    lbl_1_bss_1168[0] = 1;
                    lbl_1_bss_C40 = -1;
                    lbl_1_bss_C3C = 0;
                }
                break;
            case 1:
                idx = player->unk34 == 0 ? 0x1A : (player->unk34 == 1 ? 0x18 : 0x19);
                lbl_1_bss_1080[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[idx], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_1080[0], 1);
                Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, 370.0f + pos.y, pos.z);
                Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_1080[0], 1);
                Hu3DModelScaleSet(lbl_1_bss_1080[0], 0.15f, 0.15f, 0.15f);
                Hu3DCamera[1] = Hu3DCamera[0];
                Hu3DModelLayerSet(lbl_1_bss_1080[0], 7);
                Hu3DModelCameraSet(lbl_1_bss_1080[0], 2);
                lbl_1_bss_E98++;
                if (player->unk38 != -1) {
                    idx = player->unk38 == 0 ? 0x1A : (player->unk38 == 1 ? 0x18 : 0x19);
                    lbl_1_bss_1080[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[idx], HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelCameraSet(lbl_1_bss_1080[1], 1);
                    Hu3DModelPosSet(lbl_1_bss_1080[1], -50.0f + pos.x, 370.0f + pos.y, pos.z);
                    Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, 0.0f, 0.0f);
                    Hu3DModelAttrSet(lbl_1_bss_1080[1], 1);
                    Hu3DModelScaleSet(lbl_1_bss_1080[1], 0.15f, 0.15f, 0.15f);
                    Hu3DCamera[1] = Hu3DCamera[0];
                    Hu3DModelLayerSet(lbl_1_bss_1080[1], 7);
                    Hu3DModelCameraSet(lbl_1_bss_1080[1], 2);
                    lbl_1_bss_E98++;
                    if (player->unk3C != -1) {
                        idx = player->unk3C == 0 ? 0x1A : (player->unk3C == 1 ? 0x18 : 0x19);
                        lbl_1_bss_1080[2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[idx], HU_MEMNUM_OVL, HEAP_MODEL));
                        Hu3DModelCameraSet(lbl_1_bss_1080[2], 1);
                        Hu3DModelPosSet(lbl_1_bss_1080[2], -50.0f + pos.x, 370.0f + pos.y, pos.z);
                        Hu3DModelRotSet(lbl_1_bss_1080[2], 90.0f, 0.0f, 0.0f);
                        Hu3DModelAttrSet(lbl_1_bss_1080[2], 1);
                        Hu3DModelScaleSet(lbl_1_bss_1080[2], 0.15f, 0.15f, 0.15f);
                        Hu3DCamera[1] = Hu3DCamera[0];
                        Hu3DModelLayerSet(lbl_1_bss_1080[2], 7);
                        Hu3DModelCameraSet(lbl_1_bss_1080[2], 2);
                        lbl_1_bss_E98++;
                    }
                }
                lbl_1_bss_111E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[GwPlayerConf[work->unk174[work->unk170]].charNo + 0x50], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_111E[0], 1);
                Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f, 322.0f + pos.y, 100.0f + pos.z);
                Hu3DModelRotSet(lbl_1_bss_111E[0], 90.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_111E[0], 1);
                Hu3DModelScaleSet(lbl_1_bss_111E[0], 0.7f, 0.7f, 0.7f);
                Hu3DCamera[1] = Hu3DCamera[0];
                Hu3DModelLayerSet(lbl_1_bss_111E[0], 7);
                Hu3DModelCameraSet(lbl_1_bss_111E[0], 2);
                lbl_1_bss_1056[5] = Hu3DLLightCreate(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f, 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                Hu3DLLightStaticSet(lbl_1_bss_111E[0], lbl_1_bss_1056[5], 1);
                Hu3DLLightInfinitytSet(lbl_1_bss_111E[0], lbl_1_bss_1056[5]);
                if (lbl_1_bss_E98 == 1) {
                    lbl_1_bss_1056[0] = Hu3DLLightCreate(lbl_1_bss_1080[0], -50.0f + pos.x, 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0]);
                    lbl_1_bss_E68[0].x = -50.0f + pos.x;
                    lbl_1_bss_E68[0].y = 370.0f + pos.y;
                    lbl_1_bss_E68[0].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                    fn_1_4F144(0, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    Hu3DModelAttrReset(lbl_1_bss_1080[0], 1);
                    fn_1_4F1EC(0, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, 0.0f, 0.0f);
                }
                else if (lbl_1_bss_E98 == 2) {
                    Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x - 80.0f, 370.0f + pos.y, pos.z);
                    Hu3DModelPosSet(lbl_1_bss_1080[1], 80.0f + (-50.0f + pos.x), 370.0f + pos.y, pos.z);
                    Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f - 80.0f, 322.0f + pos.y, 100.0f + pos.z);
                    lbl_1_bss_1056[0] = Hu3DLLightCreate(lbl_1_bss_1080[0], -50.0f + pos.x - 80.0f, 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0]);
                    lbl_1_bss_1056[1] = Hu3DLLightCreate(lbl_1_bss_1080[1], 80.0f + (-50.0f + pos.x), 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[1], lbl_1_bss_1056[1], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[1], lbl_1_bss_1056[1]);
                    lbl_1_bss_E68[0].x = -50.0f + pos.x - 80.0f;
                    lbl_1_bss_E68[0].y = 370.0f + pos.y;
                    lbl_1_bss_E68[0].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                    fn_1_4F144(0, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    lbl_1_bss_E68[1].x = 80.0f + (-50.0f + pos.x);
                    lbl_1_bss_E68[1].y = 370.0f + pos.y;
                    lbl_1_bss_E68[1].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                    fn_1_4F144(1, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    Hu3DModelAttrReset(lbl_1_bss_1080[0], 1);
                    Hu3DModelAttrReset(lbl_1_bss_1080[1], 1);
                    fn_1_4F1EC(0, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, 0.0f, 0.0f);
                    fn_1_4F1EC(1, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, 0.0f, 0.0f);
                }
                else if (lbl_1_bss_E98 == 3) {
                    Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x - 160.0f, 370.0f + pos.y, pos.z);
                    Hu3DModelPosSet(lbl_1_bss_1080[2], 160.0f + (-50.0f + pos.x), 370.0f + pos.y, pos.z);
                    Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f - 160.0f, 322.0f + pos.y, 100.0f + pos.z);
                    lbl_1_bss_1056[0] = Hu3DLLightCreate(lbl_1_bss_1080[0], -50.0f + pos.x - 160.0f, 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[0], lbl_1_bss_1056[0]);
                    lbl_1_bss_1056[1] = Hu3DLLightCreate(lbl_1_bss_1080[1], -50.0f + pos.x, 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[1], lbl_1_bss_1056[1], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[1], lbl_1_bss_1056[1]);
                    lbl_1_bss_1056[2] = Hu3DLLightCreate(lbl_1_bss_1080[2], 160.0f + (-50.0f + pos.x), 370.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                    Hu3DLLightStaticSet(lbl_1_bss_1080[2], lbl_1_bss_1056[2], 1);
                    Hu3DLLightInfinitytSet(lbl_1_bss_1080[2], lbl_1_bss_1056[2]);
                    lbl_1_bss_E68[0].x = -50.0f + pos.x - 160.0f;
                    lbl_1_bss_E68[0].y = 370.0f + pos.y;
                    lbl_1_bss_E68[0].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                    fn_1_4F144(0, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    lbl_1_bss_E68[1].x = -50.0f + pos.x;
                    lbl_1_bss_E68[1].y = 370.0f + pos.y;
                    lbl_1_bss_E68[1].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                    fn_1_4F144(1, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    lbl_1_bss_E68[2].x = 160.0f + (-50.0f + pos.x);
                    lbl_1_bss_E68[2].y = 370.0f + pos.y;
                    lbl_1_bss_E68[2].z = pos.z;
                    Hu3D3Dto2D(&lbl_1_bss_E68[2], 1, &lbl_1_bss_E54);
                    lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_588)[work->unk170][0] - 2.8f;
                    lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_588)[work->unk170][1] - 2.5f;
                    lbl_1_bss_E9C[0].z = lbl_1_bss_E68[2].z;
                    fn_1_4F144(2, lbl_1_bss_E9C[0], lbl_1_bss_E54, 40, 0.0f, 0x21);
                    Hu3DModelAttrReset(lbl_1_bss_1080[0], 1);
                    Hu3DModelAttrReset(lbl_1_bss_1080[1], 1);
                    Hu3DModelAttrReset(lbl_1_bss_1080[2], 1);
                    fn_1_4F1EC(0, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, 0.0f, 0.0f);
                    fn_1_4F1EC(1, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, 0.0f, 0.0f);
                    fn_1_4F1EC(2, &pos);
                    lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[2], pos.x, pos.y);
                    Hu3DModelPosSetV(lbl_1_bss_1080[2], &lbl_1_bss_E9C[0]);
                    Hu3DModelRotSet(lbl_1_bss_1080[2], 90.0f, 0.0f, 0.0f);
                }
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_F14[1] = 0.15f;
                lbl_1_bss_1138 = 0;
                lbl_1_bss_1168[0] = 2;
                lbl_1_bss_5E = 0;
                Hu3DModelAttrReset(lbl_1_bss_5C, 1);
                Hu3DZClearLayerSet(15);
                fn_1_303E0(work);
                break;
            case 2:
                if (lbl_1_bss_1138 == 0) {
                    lbl_1_bss_5E = lbl_1_bss_5E <= 140 ? lbl_1_bss_5E + 10 : 150;
                    if (!(player->unk50 & 0x1000)) {
                        fn_1_305B4(work, lbl_1_bss_5E);
                    }
                    if (0.0f == lbl_1_bss_F14[0]) {
                        fn_1_8D04(0x40B, lbl_1_bss_1080[lbl_1_bss_E98 == 1 ? 0 : 1], 1);
                    }
                    fn_1_8D04(0x840B, lbl_1_bss_1080[lbl_1_bss_E98 == 1 ? 0 : 1], 1);
                    lbl_1_bss_F14[0] += lbl_1_bss_F14[0] < 1080.0f ? 108.0f : (lbl_1_bss_F14[0] < 1800.0f ? 72.0f : (lbl_1_bss_F14[0] < 2160.0f ? 36.0f : 18.0f));
                    if (lbl_1_bss_F14[0] >= 2880.0f) {
                        lbl_1_bss_F14[0] = 2880.0f;
                    }
                    lbl_1_bss_F14[1] += 0.0125f;
                    if (lbl_1_bss_F14[1] > 0.5f) {
                        lbl_1_bss_F14[1] = 0.5f;
                    }
                    if (lbl_1_bss_E98 == 1) {
                        fn_1_4F1EC(0, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[0], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                    }
                    else if (lbl_1_bss_E98 == 2) {
                        fn_1_4F1EC(0, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[0], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                        fn_1_4F1EC(1, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                    }
                    else if (lbl_1_bss_E98 == 3) {
                        fn_1_4F1EC(0, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[0], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                        fn_1_4F1EC(1, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                        fn_1_4F1EC(2, &pos);
                        lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[2], pos.x, pos.y);
                        Hu3DModelPosSetV(lbl_1_bss_1080[2], &lbl_1_bss_E9C[0]);
                        Hu3DModelRotSet(lbl_1_bss_1080[2], 90.0f, lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelScaleSet(lbl_1_bss_1080[2], lbl_1_bss_F14[1], lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
                    }
                    if (2880.0f == lbl_1_bss_F14[0]) {
                        lbl_1_bss_1138 = 1;
                        work->unk1A4 = 0;
                        Hu3DModelAttrReset(lbl_1_bss_111E[0], 1);
                        lbl_1_bss_1168[0] = 3;
                        lbl_1_bss_12A8.unk0 = 0;
                        lbl_1_bss_12A8.unk4 = 0;
                    }
                }
                else {
                    if (2880.0f == lbl_1_bss_F14[0]) {
                        fn_1_8D04(0x40C, lbl_1_bss_1080[lbl_1_bss_E98 == 1 ? 0 : 1], 1);
                    }
                    fn_1_8D04(0x840C, lbl_1_bss_1080[lbl_1_bss_E98 == 1 ? 0 : 1], 1);
                    lbl_1_bss_F14[0] -= lbl_1_bss_F14[0] < 1080.0f ? 108.0f : (lbl_1_bss_F14[0] < 1800.0f ? 72.0f : (lbl_1_bss_F14[0] < 2160.0f ? 36.0f : 18.0f));
                    if (lbl_1_bss_E98 == 1) {
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    }
                    else if (lbl_1_bss_E98 == 2) {
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    }
                    else if (lbl_1_bss_E98 == 3) {
                        Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                        Hu3DModelRotSet(lbl_1_bss_1080[2], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    }
                    if (lbl_1_bss_F14[0] < 2160.0f) {
                        lbl_1_bss_5E = lbl_1_bss_5E >= 10 ? lbl_1_bss_5E - 10 : 0;
                        if (!(player->unk50 & 0x1000)) {
                            fn_1_305B4(work, lbl_1_bss_5E);
                        }
                        lbl_1_bss_F14[1] += 0.0125f;
                        if (lbl_1_bss_F14[1] > 0.35f) {
                            lbl_1_bss_F14[1] = 0.35f;
                        }
                        if (lbl_1_bss_E98 == 1) {
                            fn_1_4F1EC(0, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[0], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                        }
                        else if (lbl_1_bss_E98 == 2) {
                            fn_1_4F1EC(0, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[0], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                            fn_1_4F1EC(1, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                        }
                        else if (lbl_1_bss_E98 == 3) {
                            fn_1_4F1EC(0, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[0], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[0], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                            fn_1_4F1EC(1, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[1], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                            fn_1_4F1EC(2, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[2], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[2], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[2], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                        }
                        lbl_1_bss_F3C[0]++;
                        if (lbl_1_bss_F3C[0] > 40) {
                            Hu3DLLightKill(lbl_1_bss_1080[0], lbl_1_bss_1056[0]);
                            Hu3DModelKill(lbl_1_bss_1080[0]);
                            if (player->unk38 != -1) {
                                Hu3DLLightKill(lbl_1_bss_1080[1], lbl_1_bss_1056[1]);
                                Hu3DModelKill(lbl_1_bss_1080[1]);
                                if (player->unk3C != -1) {
                                    Hu3DLLightKill(lbl_1_bss_1080[2], lbl_1_bss_1056[2]);
                                    Hu3DModelKill(lbl_1_bss_1080[2]);
                                }
                            }
                            Hu3DLLightKill(lbl_1_bss_111E[0], lbl_1_bss_1056[5]);
                            Hu3DModelKill(lbl_1_bss_111E[0]);
                            Hu3DModelAttrSet(lbl_1_bss_5C, 1);
                            Hu3DLayerHookSet(15, NULL);
                            fn_1_2FFAC(work);
                            lbl_1_bss_1138 = 1;
                            lbl_1_bss_1168[0] = 0;
                            ret = 1;
                        }
                    }
                }
                break;
            case 3:
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    lbl_1_bss_12A8.unk2C = 1;
                    fn_1_502E0(0x13);
                }
                if (lbl_1_bss_C44 != 0) {
                    if ((&player->unk34)[work->unk1A4] == 0) {
                        lbl_1_bss_12A8.unk2C = 1;
                        fn_1_4FBFC(work, 0x1F);
                    }
                    else if ((&player->unk34)[work->unk1A4] == 1) {
                        lbl_1_bss_12A8.unk2C = 1;
                        fn_1_4FBFC(work, 0x1D);
                    }
                    else if ((&player->unk34)[work->unk1A4] == 2) {
                        lbl_1_bss_12A8.unk2C = 1;
                        fn_1_4FBFC(work, 0x1E);
                    }
                    lbl_1_bss_12A8.unk0 = 1;
                    lbl_1_bss_C44 = 0;
                }
                fn_1_20DE4(work->unk174[work->unk170], work);
                if (HuPadDStkRep[work->unk174[work->unk170]] & 1) {
                    if (work->unk1A4 == 0) {
                        if (player->unk3C != -1) {
                            work->unk1A4 = 2;
                        }
                        else if (player->unk38 != -1) {
                            work->unk1A4 = 1;
                        }
                    }
                    else {
                        work->unk1A4--;
                    }
                    lbl_1_bss_C44 = 1;
                    if (lbl_1_bss_E98 > 1) {
                        HuAudFXPlay(0);
                    }
                }
                else if (HuPadDStkRep[work->unk174[work->unk170]] & 2) {
                    if (work->unk1A4 == 0) {
                        if (player->unk38 != -1) {
                            work->unk1A4 = 1;
                        }
                    }
                    else if (work->unk1A4 == 1) {
                        if (player->unk3C != -1) {
                            work->unk1A4 = 2;
                        }
                        else {
                            work->unk1A4 = 0;
                        }
                    }
                    else if (work->unk1A4 == 2) {
                        work->unk1A4 = 0;
                    }
                    lbl_1_bss_C44 = 1;
                    if (lbl_1_bss_E98 > 1) {
                        HuAudFXPlay(0);
                    }
                }
                else if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                    if ((&player->unk34)[work->unk1A4] == 0 && fn_1_25624(work)) {
                        HuAudFXPlay(4);
                        fn_1_4FBC8(work, 0x28);
                        lbl_1_bss_12A8.unk0 = 1;
                        lbl_1_bss_12A8.unk2C = 1;
                        fn_1_4FBFC(work, 0x1F);
                        lbl_1_bss_12A8.unk0 = 1;
                    }
                    else {
                        fn_1_50460();
                        lbl_1_bss_113C = 0;
                        lbl_1_bss_F14[1] = 0.0f;
                        lbl_1_bss_1168[0] = 4;
                        lbl_1_bss_F3C[0] = 1;
                        if (work->unk1A4 == 0) {
                            lbl_1_bss_F3C[8] = 1;
                            lbl_1_bss_F3C[9] = 2;
                        }
                        else if (work->unk1A4 == 1) {
                            lbl_1_bss_F3C[8] = 0;
                            lbl_1_bss_F3C[9] = 2;
                        }
                        else if (work->unk1A4 == 2) {
                            lbl_1_bss_F3C[8] = 0;
                            lbl_1_bss_F3C[9] = 1;
                        }
                        lbl_1_bss_C44 = 1;
                        lbl_1_bss_12A8.unk0 = 0;
                        fn_1_4FFEC();
                        HuAudFXPlay(2);
                        lbl_1_bss_12A8.unk28 = 60;
                        lbl_1_bss_12A8.unk8[0] = fn_1_502DC(GwPlayerConf[work->unk174[work->unk170]].charNo);
                        if ((&player->unk34)[work->unk1A4] == 0) {
                            fn_1_4FBC8(work, 0xE);
                        }
                        else if ((&player->unk34)[work->unk1A4] == 1) {
                            fn_1_4FBC8(work, 0xA);
                        }
                        else if ((&player->unk34)[work->unk1A4] == 2) {
                            fn_1_4FBC8(work, 0xC);
                        }
                        lbl_1_bss_12A8.unk4 = 1;
                        Hu3DModelAttrSet(lbl_1_bss_111E[0], 1);
                        if ((&player->unk34)[work->unk1A4] == 0) {
                            lbl_1_bss_C3C = 1;
                        }
                        HuAudSStreamVolSet(0, 127, 100);
                    }
                }
                else if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_B) {
                    HuAudFXPlay(0x3FC);
                    fn_1_50460();
                    lbl_1_bss_1168[0] = 4;
                    Hu3DModelAttrSet(lbl_1_bss_111E[0], 1);
                    lbl_1_bss_F3C[0] = 0;
                    lbl_1_bss_C44 = 1;
                    lbl_1_bss_12A8.unk0 = 0;
                    fn_1_4FFEC();
                    lbl_1_bss_12A8.unk4 = 1;
                    HuAudSStreamVolSet(0, 127, 500);
                }
                if (lbl_1_bss_E98 == 1) {
                    Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f, 322.0f + pos.y, 100.0f + pos.z);
                }
                else if (lbl_1_bss_E98 == 2) {
                    Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f - 80.0f + 160.0f * work->unk1A4, 322.0f + pos.y, 100.0f + pos.z);
                }
                else if (lbl_1_bss_E98 == 3) {
                    Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 50.0f - 160.0f + 160.0f * work->unk1A4, 322.0f + pos.y, 100.0f + pos.z);
                }
                break;
            case 4:
                if (lbl_1_bss_F3C[0] != 0) {
                    if (lbl_1_bss_E98 != 1) {
                        if (lbl_1_bss_E98 == 2) {
                            if (work->unk1A4 == 0) {
                                lbl_1_bss_E68[0].x = 80.0f + (-50.0f + pos.x);
                                lbl_1_bss_E68[0].y = 370.0f + pos.y;
                                lbl_1_bss_E68[0].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                                fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                            }
                            else {
                                lbl_1_bss_E68[0].x = -50.0f + pos.x - 80.0f;
                                lbl_1_bss_E68[0].y = 370.0f + pos.y;
                                lbl_1_bss_E68[0].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                                fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                            }
                        }
                        else if (lbl_1_bss_E98 == 3) {
                            if (work->unk1A4 == 0) {
                                lbl_1_bss_E68[0].x = -50.0f + pos.x;
                                lbl_1_bss_E68[0].y = 370.0f + pos.y;
                                lbl_1_bss_E68[0].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                                fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                                lbl_1_bss_E68[1].x = 160.0f + (-50.0f + pos.x);
                                lbl_1_bss_E68[1].y = 370.0f + pos.y;
                                lbl_1_bss_E68[1].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                                fn_1_4F144(1, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                            }
                            else if (work->unk1A4 == 1) {
                                lbl_1_bss_E68[0].x = -50.0f + pos.x - 160.0f;
                                lbl_1_bss_E68[0].y = 370.0f + pos.y;
                                lbl_1_bss_E68[0].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                                fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                                lbl_1_bss_E68[1].x = 160.0f + (-50.0f + pos.x);
                                lbl_1_bss_E68[1].y = 370.0f + pos.y;
                                lbl_1_bss_E68[1].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                                fn_1_4F144(1, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                            }
                            else {
                                lbl_1_bss_E68[0].x = -50.0f + pos.x - 160.0f;
                                lbl_1_bss_E68[0].y = 370.0f + pos.y;
                                lbl_1_bss_E68[0].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                                fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                                lbl_1_bss_E68[1].x = -50.0f + pos.x;
                                lbl_1_bss_E68[1].y = 370.0f + pos.y;
                                lbl_1_bss_E68[1].z = pos.z;
                                Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                                lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                                lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                                lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                                fn_1_4F144(1, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                            }
                        }
                    }
                    lbl_1_bss_113C = 0;
                    lbl_1_bss_F3C[1] = 0;
                    lbl_1_bss_F14[0] = 2880.0f;
                    lbl_1_bss_F14[1] = 0.0f;
                    lbl_1_bss_1168[0] = 5;
                }
                else {
                    if (lbl_1_bss_E98 == 1) {
                        lbl_1_bss_E68[0].x = -50.0f + pos.x;
                        lbl_1_bss_E68[0].y = 370.0f + pos.y;
                        lbl_1_bss_E68[0].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                        fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                    }
                    else if (lbl_1_bss_E98 == 2) {
                        lbl_1_bss_E68[0].x = -50.0f + pos.x - 80.0f;
                        lbl_1_bss_E68[0].y = 370.0f + pos.y;
                        lbl_1_bss_E68[0].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                        fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                        lbl_1_bss_E68[1].x = 80.0f + (-50.0f + pos.x);
                        lbl_1_bss_E68[1].y = 370.0f + pos.y;
                        lbl_1_bss_E68[1].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                        fn_1_4F144(1, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                    }
                    else if (lbl_1_bss_E98 == 3) {
                        lbl_1_bss_E68[0].x = -50.0f + pos.x - 160.0f;
                        lbl_1_bss_E68[0].y = 370.0f + pos.y;
                        lbl_1_bss_E68[0].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[0], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_548)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_548)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[0].z;
                        fn_1_4F144(0, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                        lbl_1_bss_E68[1].x = -50.0f + pos.x;
                        lbl_1_bss_E68[1].y = 370.0f + pos.y;
                        lbl_1_bss_E68[1].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[1], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_568)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_568)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[1].z;
                        fn_1_4F144(1, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                        lbl_1_bss_E68[2].x = 160.0f + (-50.0f + pos.x);
                        lbl_1_bss_E68[2].y = 370.0f + pos.y;
                        lbl_1_bss_E68[2].z = pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_E68[2], 1, &lbl_1_bss_E54);
                        lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_588)[work->unk170][0] - 2.8f;
                        lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_588)[work->unk170][1] - 2.5f;
                        lbl_1_bss_E9C[0].z = lbl_1_bss_E68[2].z;
                        fn_1_4F144(2, lbl_1_bss_E54, lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                    }
                    lbl_1_bss_F3C[1] = 0;
                    lbl_1_bss_F14[0] = 2880.0f;
                    lbl_1_bss_F14[1] = 0.0f;
                    lbl_1_bss_1168[0] = 2;
                }
                break;
            case 5:
                if (2880.0f == lbl_1_bss_F14[0]) {
                    fn_1_8D04(0x40C, lbl_1_bss_E98 == 1 ? lbl_1_bss_1080[0] : lbl_1_bss_1080[1], 1);
                }
                fn_1_8D04(0x840C, lbl_1_bss_E98 == 1 ? lbl_1_bss_1080[0] : lbl_1_bss_1080[1], 1);
                lbl_1_bss_F14[0] -= lbl_1_bss_F14[0] < 1080.0f ? 108.0f : (lbl_1_bss_F14[0] < 1800.0f ? 72.0f : (lbl_1_bss_F14[0] < 2160.0f ? 36.0f : 18.0f));
                if (lbl_1_bss_E98 == 1) {
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                }
                else if (lbl_1_bss_E98 == 2) {
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                }
                else if (lbl_1_bss_E98 == 3) {
                    Hu3DModelRotSet(lbl_1_bss_1080[0], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    Hu3DModelRotSet(lbl_1_bss_1080[1], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                    Hu3DModelRotSet(lbl_1_bss_1080[2], 90.0f, -lbl_1_bss_F14[0], 0.0f);
                }
                if (lbl_1_bss_F14[0] < 2160.0f) {
                    lbl_1_bss_5E = lbl_1_bss_5E >= 10 ? lbl_1_bss_5E - 10 : 0;
                    if (!(player->unk50 & 0x1000)) {
                        fn_1_305B4(work, lbl_1_bss_5E);
                    }
                    lbl_1_bss_113C += 30;
                    if (lbl_1_bss_113C > 3000) {
                        lbl_1_bss_113C = 3000;
                    }
                    if (lbl_1_bss_E98 == 1) {
                        lbl_1_bss_F14[2] = -50.0f + pos.x;
                    }
                    else if (lbl_1_bss_E98 == 2) {
                        if (work->unk1A4 == 0) {
                            lbl_1_bss_F14[2] = -50.0f + pos.x - 80.0f;
                        }
                        else {
                            lbl_1_bss_F14[2] = 80.0f + (-50.0f + pos.x);
                        }
                    }
                    else if (lbl_1_bss_E98 == 3) {
                        if (work->unk1A4 == 0) {
                            lbl_1_bss_F14[2] = -50.0f + pos.x - 160.0f;
                        }
                        else if (work->unk1A4 == 1) {
                            lbl_1_bss_F14[2] = -50.0f + pos.x;
                        }
                        else {
                            lbl_1_bss_F14[2] = 160.0f + (-50.0f + pos.x);
                        }
                    }
                    Hu3DModelPosSet(lbl_1_bss_1080[work->unk1A4], lbl_1_bss_F14[2], 370.0f + pos.y + lbl_1_bss_113C, pos.z);
                    lbl_1_bss_F14[1] += 0.0125f;
                    if (lbl_1_bss_F14[1] > 0.35f) {
                        lbl_1_bss_F14[1] = 0.35f;
                    }
                    if (lbl_1_bss_E98 != 1) {
                        if (lbl_1_bss_E98 == 2) {
                            fn_1_4F1EC(0, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[lbl_1_bss_F3C[8]], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[lbl_1_bss_F3C[8]], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                        }
                        else if (lbl_1_bss_E98 == 3) {
                            fn_1_4F1EC(0, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[0], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[lbl_1_bss_F3C[8]], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[lbl_1_bss_F3C[8]], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                            fn_1_4F1EC(1, &pos);
                            lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E68[1], pos.x, pos.y);
                            Hu3DModelPosSetV(lbl_1_bss_1080[lbl_1_bss_F3C[9]], &lbl_1_bss_E9C[0]);
                            Hu3DModelScaleSet(lbl_1_bss_1080[lbl_1_bss_F3C[9]], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                        }
                    }
                    lbl_1_bss_F3C[1]++;
                    if (lbl_1_bss_F3C[1] > 40) {
                        Hu3DLLightKill(lbl_1_bss_1080[0], lbl_1_bss_1056[0]);
                        Hu3DModelKill(lbl_1_bss_1080[0]);
                        if (player->unk38 != -1) {
                            Hu3DLLightKill(lbl_1_bss_1080[1], lbl_1_bss_1056[1]);
                            Hu3DModelKill(lbl_1_bss_1080[1]);
                            if (player->unk3C != -1) {
                                Hu3DLLightKill(lbl_1_bss_1080[2], lbl_1_bss_1056[2]);
                                Hu3DModelKill(lbl_1_bss_1080[2]);
                            }
                        }
                        Hu3DLLightKill(lbl_1_bss_111E[0], lbl_1_bss_1056[5]);
                        Hu3DModelKill(lbl_1_bss_111E[0]);
                        if ((&player->unk34)[work->unk1A4] == 0) {
                            lbl_1_bss_1168[0] = 10;
                        }
                        else if ((&player->unk34)[work->unk1A4] == 1) {
                            lbl_1_bss_1168[0] = 6;
                        }
                        else if ((&player->unk34)[work->unk1A4] == 2) {
                            lbl_1_bss_1168[0] = 7;
                        }
                        Hu3DModelAttrSet(lbl_1_bss_5C, 1);
                        Hu3DLayerHookSet(15, NULL);
                        if (lbl_1_bss_F3C[0] != 0) {
                            cards[0] = player->unk34;
                            cards[1] = player->unk38;
                            cards[2] = player->unk3C;
                            if (work->unk1A4 == 0) {
                                cards[0] = cards[1];
                                cards[1] = cards[2];
                                cards[2] = -1;
                            }
                            else if (work->unk1A4 == 1) {
                                cards[1] = cards[2];
                                cards[2] = -1;
                            }
                            else if (work->unk1A4 == 2) {
                                cards[2] = -1;
                            }
                            fn_1_304D8(work, cards);
                        }
                    }
                }
                break;
            case 6:
                if (fn_1_21CA4(0, work)) {
                    lbl_1_bss_1168[0] = 11;
                }
                break;
            case 7:
                if (fn_1_21CA4(1, work)) {
                    lbl_1_bss_1168[0] = 8;
                }
                break;
            case 8:
                if (fn_1_227A4(1, work)) {
                    lbl_1_bss_1168[0] = 9;
                }
                break;
            case 9:
                if (fn_1_21CA4(-1, work)) {
                    lbl_1_bss_1168[0] = 11;
                }
                break;
            case 10:
                if (fn_1_258E4(work)) {
                    lbl_1_bss_1168[0] = 11;
                }
                break;
            case 11:
                if (work->unk1A4 == 0) {
                    player->unk34 = player->unk38;
                    player->unk38 = player->unk3C;
                    player->unk3C = -1;
                }
                else if (work->unk1A4 == 1) {
                    player->unk38 = player->unk3C;
                    player->unk3C = -1;
                }
                else if (work->unk1A4 == 2) {
                    player->unk3C = -1;
                }
                fn_1_2FFAC(work);
                player->unk50 |= 0x20;
                lbl_1_bss_1168[0] = 0;
                ret = 1;
                break;
        }
    }
    return ret;
}

/* 145 insns */
void fn_1_20DE4(s32 playerNo, CardGameWork *work)
{
    if (GwPlayerConf[playerNo].type != 0) {
        HuPadBtnDown[playerNo] = 0;
        HuPadDStkRep[playerNo] = 0;
        if (lbl_1_bss_C40 == -1) {
            lbl_1_bss_C40 = fn_1_21028(work);
        }
        if (lbl_1_bss_C48[1] == 0) {
            lbl_1_bss_C48[1] = frandmod(60) + 31;
        }
        lbl_1_bss_C48[0]++;
        if (lbl_1_bss_C48[0] == lbl_1_bss_C48[1]) {
            HuPadBtnDown[playerNo] = PAD_BUTTON_A;
            lbl_1_bss_C48[0] = 0;
            lbl_1_bss_C48[1] = 0;
            if ((&work->player[work->unk174[work->unk170]].unk34)[work->unk1A4] == 0) {
                if (fn_1_21028(work) == 0) {
                    HuPadBtnDown[playerNo] = 0;
                    HuPadDStkRep[playerNo] = PAD_BUTTON_RIGHT;
                    lbl_1_bss_C48[0] = 0;
                    lbl_1_bss_C48[1] = 20;
                }
            }
        }
        else if (lbl_1_bss_C48[0] % 30 == 0) {
            HuPadDStkRep[playerNo] = frandmod(2) ? PAD_BUTTON_RIGHT : PAD_BUTTON_LEFT;
        }
    }
}

/* 799 insns */
s32 fn_1_21028(CardGameWork *work)
{
    s32 dir = 0;
    s32 x = work->player[work->unk174[work->unk170]].unk10;
    s32 y = work->player[work->unk174[work->unk170]].unk14;
    s32 a = work->player[work->unk174[work->unk170]].unk20;
    s32 b = work->player[work->unk174[work->unk170]].unk24;
    s32 i;

    if (a == 1 && b == 1) {
        if (x < 2) {
            if ((lbl_1_bss_8C4[x + 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x + 2][y] & 0xF00) != 0) {
                    dir = 2;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                }
            }
        }
        else {
            if ((lbl_1_bss_8C4[x - 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x - 2][y] & 0xF00) != 0) {
                    dir = 1;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                }
            }
        }
        if (x > work->unk194 - 3) {
            if ((lbl_1_bss_8C4[x - 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x - 2][y] & 0xF00) != 0) {
                    dir = 1;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                }
            }
        }
        else {
            if ((lbl_1_bss_8C4[x + 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x + 2][y] & 0xF00) != 0) {
                    dir = 2;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                }
            }
        }
        if (y < 2) {
            if ((lbl_1_bss_8C4[x][y + 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y + 2] & 0xF00) != 0) {
                    dir = 4;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                }
            }
        }
        else {
            if ((lbl_1_bss_8C4[x][y - 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y - 2] & 0xF00) != 0) {
                    dir = 3;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                }
            }
        }
        if (y > work->unk194 - 3) {
            if ((lbl_1_bss_8C4[x][y - 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y - 2] & 0xF00) != 0) {
                    dir = 3;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                }
            }
        }
        else {
            if ((lbl_1_bss_8C4[x][y + 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y + 2] & 0xF00) != 0) {
                    dir = 4;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                }
            }
        }
    }
    else if (a == 0 && b == 1) {
        if (x >= 2) {
            if ((lbl_1_bss_8C4[x - 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x - 2][y] & 0xF00) != 0) {
                    dir = 1;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 1;
                    }
                }
            }
        }
    }
    else if (a == 2 && b == 1) {
        if (x <= work->unk194 - 3) {
            if ((lbl_1_bss_8C4[x + 1][y] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x + 2][y] & 0xF00) != 0) {
                    dir = 2;
                }
                else {
                    if (y > 0 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                    if (y < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 2;
                    }
                }
            }
        }
    }
    else if (a == 1 && b == 0) {
        if (y >= 2) {
            if ((lbl_1_bss_8C4[x][y - 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y - 2] & 0xF00) != 0) {
                    dir = 3;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y - 1] & 0xF00) != 0) {
                        dir = 3;
                    }
                }
            }
        }
    }
    else if (a == 1 && b == 2) {
        if (y <= work->unk194 - 3) {
            if ((lbl_1_bss_8C4[x][y + 1] & 0xF00) == 0) {
                if ((lbl_1_bss_8C4[x][y + 2] & 0xF00) != 0) {
                    dir = 4;
                }
                else {
                    if (x > 0 && (lbl_1_bss_8C4[x - 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                    if (x < work->unk194 - 1 && (lbl_1_bss_8C4[x + 1][y + 1] & 0xF00) != 0) {
                        dir = 4;
                    }
                }
            }
        }
    }
    if (dir != 0) {
        if (dir == 1) {
            x--;
        }
        else if (dir == 2) {
            x++;
        }
        else if (dir == 3) {
            y--;
        }
        else if (dir == 4) {
            y++;
        }
        for (i = 0; i < 4; i++) {
            if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                dir = 0;
                break;
            }
        }
    }
    return dir;
}

/* 704 insns */
s32 fn_1_21CA4(s32 a0, CardGameWork *work)
{
    HuVecF pos;
    s32 x;
    s32 y;
    s32 k;
    s32 a;
    s32 b;
    s32 i;
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    s16 id;

    if (a0 != -1) {
        if (a0 == 0) {
            player->unk50 |= 2;
        }
        fn_1_9DA8(&pos, work);
    }
    else {
        for (i = 0; i < 4; i++) {
            if (work->unk1A8 == work->player[i].unk2C) {
                work->player[i].unk50 |= 4;
                work->unk1AC = i;
                x = work->player[i].unk10;
                y = work->player[i].unk14;
                a = work->player[i].unk20;
                b = work->player[i].unk24;
                if (work->player[i].unk0 == 1) {
                    x--;
                }
                else if (work->player[i].unk0 == 2) {
                    x++;
                }
                else if (work->player[i].unk0 == 3) {
                    y--;
                }
                else if (work->player[i].unk0 == 4) {
                    y++;
                }
                break;
            }
        }
        fn_1_9C74(&pos, x, y, a, b);
        if (work->player[work->unk1AC].unk50 & 0x200) {
            HuVecF scale = { 1.0f, 0.0f, 1.0f };
            pos.x += -50.0f;
            work->player[work->unk1AC].unk56 = fn_1_3ED3C(4, pos);
            fn_1_3F6B0(4, work->player[work->unk1AC].unk56, scale);
            lbl_1_bss_1168[1] = 0;
            lbl_1_bss_12A8.unk28 = 60;
            lbl_1_bss_12A8.unk8[0] = fn_1_502DC(GwPlayerConf[work->unk1AC].charNo);
            fn_1_4FBC8(work, 13);
            return 1;
        }
    }
    switch (lbl_1_bss_1168[1]) {
        case 0:
            k = (a0 == 0) ? 0x66 : 0x67;
            lbl_1_bss_1080[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[k], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_1080[0], 1);
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, 1000.0f + pos.y, pos.z);
            Hu3DModelScaleSet(lbl_1_bss_1080[0], 1.6f, 1.6f, 1.6f);
            lbl_1_bss_113C = 0;
            lbl_1_bss_F3C[0] = 0;
            lbl_1_bss_F14[0] = 1.6f;
            if (a0 != -1) {
                lbl_1_bss_1168[1]++;
            }
            else {
                lbl_1_bss_1168[1] = 4;
            }
            break;
        case 1:
            lbl_1_bss_113C += 20;
            if (lbl_1_bss_113C > 600) {
                lbl_1_bss_113C = 600;
            }
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, (1000.0f + pos.y) - lbl_1_bss_113C, pos.z);
            if (lbl_1_bss_20[0] == 0) {
                if (fn_1_8D04(0x319, lbl_1_bss_1080[0], 1) != -1) {
                    lbl_1_bss_20[0] = 1;
                }
            }
            if (lbl_1_bss_113C == 600) {
                if (a0 == 1) {
                    if (lbl_1_bss_F3C[0] == 0) {
                        pos.x += -50.0f;
                        pos.y += (1000.0f - lbl_1_bss_113C) - 40.0f;
                        id = fn_1_3ED3C(2, pos);
                        lbl_1_bss_E9C[0].x = 2.0f;
                        lbl_1_bss_E9C[0].y = 2.0f;
                        lbl_1_bss_E9C[0].z = 2.0f;
                        fn_1_3F6B0(2, id, lbl_1_bss_E9C[0]);
                    }
                    if (lbl_1_bss_F3C[0] == 10) {
                        Hu3DModelKill(lbl_1_bss_1080[0]);
                    }
                }
                lbl_1_bss_F3C[0]++;
            }
            if (lbl_1_bss_F3C[0] > 15) {
                if (a0 != 1) {
                    lbl_1_bss_1168[1]++;
                }
                else {
                    lbl_1_bss_1168[1] = 3;
                }
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            if (lbl_1_bss_113C == 600) {
                lbl_1_bss_20[0] = (a0 == 0) ? 0x31A : 0x31B;
                fn_1_8D04(lbl_1_bss_20[0], lbl_1_bss_1080[0], 1);
                lbl_1_bss_20[0] = 0;
            }
            lbl_1_bss_113C += 20;
            lbl_1_bss_F14[0] -= 0.08f;
            if (lbl_1_bss_F14[0] < 0.0f) {
                lbl_1_bss_F14[0] = 0.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + pos.x, (1000.0f + pos.y) - lbl_1_bss_113C, pos.z);
            Hu3DModelScaleSet(lbl_1_bss_1080[0], lbl_1_bss_F14[0], lbl_1_bss_F14[0], lbl_1_bss_F14[0]);
            if (lbl_1_bss_113C == 1000) {
                pos.x += -50.0f;
                if (a0 == 0) {
                    if (player->unk50 & 4) {
                        fn_1_3F278(4, player->unk56);
                        player->unk56 = -1;
                        player->unk50 &= ~4;
                    }
                    player->unk56 = fn_1_3ED3C(3, pos);
                }
                else if (a0 != 0) {
                    if (work->player[work->unk1AC].unk50 & 2) {
                        fn_1_3F278(3, work->player[work->unk1AC].unk56);
                        work->player[work->unk1AC].unk56 = -1;
                        work->player[work->unk1AC].unk50 &= ~2;
                    }
                    else if ((work->player[work->unk1AC].unk50 & 4) && work->player[work->unk1AC].unk56 != -1) {
                        fn_1_3F278(4, work->player[work->unk1AC].unk56);
                        work->player[work->unk1AC].unk56 = -1;
                    }
                    work->player[work->unk1AC].unk56 = fn_1_3ED3C(4, pos);
                }
                lbl_1_bss_1168[1]++;
            }
            break;
        case 3:
            if (a0 != 1) {
                Hu3DModelKill(lbl_1_bss_1080[0]);
            }
            lbl_1_bss_1168[1] = 0;
            result = 1;
            lbl_1_bss_12A8.unk28 = 60;
            if (a0 == 0) {
                fn_1_4FBC8(work, (player->unk50 & 0x800) ? 0x3F : 0xB);
            }
            else if (a0 == -1) {
                lbl_1_bss_12A8.unk8[0] = fn_1_502DC(GwPlayerConf[work->unk1AC].charNo);
                fn_1_4FBC8(work, 13);
            }
            break;
        case 4:
            if (fn_1_30FA4(9, &pos)) {
                lbl_1_bss_1168[1] = 1;
            }
            break;
    }
    return result;
}

/* 2856 insns */
s32 fn_1_227A4(s32 a0, CardGameWork *work)
{
    HuVecF pos;
    HuVecF rot;
    HuVecF rotOut;
    s32 cnt[3];
    float scale;
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    char names[3][6] = { "ro000", "ro002", "ro001" };
    CardPlayerWork *other;
    HSFMATERIAL *mat;
    s32 i;
    s32 m;
    s32 j;
    s32 n;
    s32 k;
    s32 charNo;
    s32 rnd;
    s16 id;

    if (a0 == 0) {
        pos = lbl_1_bss_BF4;
        scale = lbl_1_bss_C00;
    }
    else {
        fn_1_9DA8(&pos, work);
        pos.x += -50.0f;
        pos.y += 400.0f;
        scale = 0.7f;
    }
    switch (lbl_1_bss_1168[1]) {
        case 0:
            lbl_1_bss_BF0 = lbl_1_bss_BEC = -1;
            k = (a0 == 0) ? 0x42 : 0x45;
            lbl_1_bss_1050[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[k], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelPosSetV(lbl_1_bss_1050[0], &pos);
            rot = (HuVecF) { 90.0f, 0.0f, -4.0f };
            fn_1_25444(&rot, &rotOut);
            Hu3DModelRotSetV(lbl_1_bss_1050[0], &rotOut);
            Hu3DModelScaleSet(lbl_1_bss_1050[0], scale, 1.0f, scale);
            Hu3DModelLayerSet(lbl_1_bss_1050[0], 2);
            lbl_1_bss_1050[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[k + 1], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelPosSetV(lbl_1_bss_1050[1], &pos);
            rot = (HuVecF) { 90.0f, -10.0f, -4.0f };
            fn_1_25444(&rot, &rotOut);
            Hu3DModelRotSetV(lbl_1_bss_1050[1], &rotOut);
            Hu3DModelScaleSet(lbl_1_bss_1050[1], scale, 1.0f, scale);
            Hu3DModelLayerSet(lbl_1_bss_1050[1], 2);
            if (a0 == 0) {
                lbl_1_bss_1050[2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[0x44], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSetV(lbl_1_bss_1050[2], &pos);
                rot = (HuVecF) { 90.0f, 0.0f, -4.0f };
                fn_1_25444(&rot, &rotOut);
                Hu3DModelRotSetV(lbl_1_bss_1050[2], &rotOut);
                Hu3DModelScaleSet(lbl_1_bss_1050[2], scale, 1.0f, scale);
                Hu3DModelLayerSet(lbl_1_bss_1050[2], 2);
            }
            Hu3DModelCameraSet(lbl_1_bss_1050[0], 1);
            Hu3DModelCameraSet(lbl_1_bss_1050[1], 1);
            if (a0 == 0) {
                Hu3DModelCameraSet(lbl_1_bss_1050[2], 1);
            }
            for (n = 0, i = n; i < 4; i++) {
                charNo = GwPlayerConf[i].charNo;
                if (player->unk2C != charNo) {
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[charNo + 0x47], HU_MEMNUM_OVL), lbl_1_bss_1050[1], names[n]);
                    lbl_1_bss_E8C[n] = charNo;
                    n++;
                }
            }
            lbl_1_bss_1056[18] = Hu3DLLightCreate(lbl_1_bss_1050[0], pos.x, pos.y, pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
            Hu3DLLightStaticSet(lbl_1_bss_1050[0], lbl_1_bss_1056[18], 1);
            Hu3DLLightInfinitytSet(lbl_1_bss_1050[0], lbl_1_bss_1056[18]);
            lbl_1_bss_1056[19] = Hu3DLLightCreate(lbl_1_bss_1050[1], pos.x, pos.y, pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
            Hu3DLLightStaticSet(lbl_1_bss_1050[1], lbl_1_bss_1056[19], 1);
            Hu3DLLightInfinitytSet(lbl_1_bss_1050[1], lbl_1_bss_1056[19]);
            if (a0 == 0) {
                lbl_1_bss_1056[20] = Hu3DLLightCreate(lbl_1_bss_1050[2], pos.x, pos.y, pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                Hu3DLLightStaticSet(lbl_1_bss_1050[2], lbl_1_bss_1056[20], 1);
                Hu3DLLightInfinitytSet(lbl_1_bss_1050[2], lbl_1_bss_1056[20]);
            }
            if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                fn_1_502E0(0x12);
            }
            lbl_1_bss_F3C[0] = 0;
            lbl_1_bss_F3C[1] = 0;
            if (a0 == 0) {
                lbl_1_bss_1168[1] = 99;
            }
            else {
                lbl_1_bss_1168[1]++;
            }
            HuAudFXPlay(0x2FF);
            break;
        case 1:
            if (lbl_1_bss_F3C[0] == 0) {
                rot = (HuVecF) { 90.0f, -10.0f, -4.0f };
                rot.y -= lbl_1_bss_F3C[1];
                fn_1_25444(&rot, &rotOut);
                Hu3DModelRotSetV(lbl_1_bss_1050[1], &rotOut);
                lbl_1_bss_F3C[1] = (lbl_1_bss_F3C[1] < 345) ? lbl_1_bss_F3C[1] + 15 : 0;
                fn_1_25518(work->unk174[work->unk170]);
                if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                    lbl_1_bss_F3C[0] = 1;
                    lbl_1_bss_F3C[2] = 15;
                    HuAudFXPlay(0x301);
                }
            }
            else {
                rot = (HuVecF) { 90.0f, -10.0f, -4.0f };
                rot.y -= lbl_1_bss_F3C[1];
                fn_1_25444(&rot, &rotOut);
                Hu3DModelRotSetV(lbl_1_bss_1050[1], &rotOut);
                lbl_1_bss_F3C[1] = (lbl_1_bss_F3C[1] < 360 - lbl_1_bss_F3C[2]) ? lbl_1_bss_F3C[1] + lbl_1_bss_F3C[2] : lbl_1_bss_F3C[1] + lbl_1_bss_F3C[2] - 360;
                if (lbl_1_bss_F3C[2] == 0) {
                    lbl_1_bss_F3C[0] = -1;
                }
                else {
                    lbl_1_bss_F3C[2]--;
                }
            }
            if (lbl_1_bss_F3C[0] == -1) {
                fn_1_50460();
                if (lbl_1_bss_F3C[1] >= 55 && lbl_1_bss_F3C[1] <= 170) {
                    work->unk1A8 = lbl_1_bss_E8C[1];
                }
                else if (lbl_1_bss_F3C[1] >= 175 && lbl_1_bss_F3C[1] <= 290) {
                    work->unk1A8 = lbl_1_bss_E8C[2];
                }
                else {
                    work->unk1A8 = lbl_1_bss_E8C[0];
                }
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[1] = (a0 != 0) ? 2 : 3;
                mat = Hu3DData[lbl_1_bss_1050[1]].hsf->material;
                for (m = 0; m < 3; mat++, m++) {
                    if (work->unk1A8 != lbl_1_bss_E8C[m]) {
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_E8C[m] == work->player[i].unk2C) {
                                mat->color[0] = 0x50;
                                mat->color[1] = 0x50;
                                mat->color[2] = 0x50;
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] == 60) {
                id = fn_1_3ED3C(2, pos);
                lbl_1_bss_E9C[0].x = 2.0f;
                lbl_1_bss_E9C[0].y = 2.0f;
                lbl_1_bss_E9C[0].z = 2.0f;
                fn_1_3F6B0(2, id, lbl_1_bss_E9C[0]);
            }
            if (lbl_1_bss_F3C[0] > 70) {
                Hu3DAnimModelKill(lbl_1_bss_1050[1]);
                Hu3DModelKill(lbl_1_bss_1050[0]);
                Hu3DModelKill(lbl_1_bss_1050[1]);
                Hu3DLLightKill(lbl_1_bss_1050[0], lbl_1_bss_1056[18]);
                Hu3DLLightKill(lbl_1_bss_1050[1], lbl_1_bss_1056[19]);
                lbl_1_bss_1168[1] = 0;
                result = 1;
            }
            break;
        case 3:
            for (i = 0; ; i++) {
                if (work->unk1A8 == work->player[work->unk174[i]].unk2C) {
                    break;
                }
            }
            lbl_1_bss_F3C[0] = i;
            other = &work->player[work->unk174[lbl_1_bss_F3C[0]]];
            cnt[0] = other->unk44;
            cnt[1] = other->unk48;
            cnt[2] = other->unk4C;
            lbl_1_bss_F3C[1] = cnt[0] + (cnt[1] + cnt[2]);
            if (lbl_1_bss_F3C[1] <= 1) {
                if (lbl_1_bss_F3C[1] != 0) {
                    fn_1_4149C(work->unk174[lbl_1_bss_F3C[0]]);
                }
                lbl_1_bss_F3C[2] = 0;
                lbl_1_bss_102A[0] = -1;
                lbl_1_bss_1168[1] = 8;
                break;
            }
            for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                rnd = frandmod(3);
                if (rnd == 0) {
                    if (cnt[0] > 0) {
                        lbl_1_bss_C50[i] = 0;
                        cnt[0]--;
                    }
                    else if (cnt[1] > 0) {
                        lbl_1_bss_C50[i] = 1;
                        cnt[1]--;
                    }
                    else {
                        lbl_1_bss_C50[i] = 2;
                        cnt[2]--;
                    }
                }
                else if (rnd == 1) {
                    if (cnt[1] > 0) {
                        lbl_1_bss_C50[i] = 1;
                        cnt[1]--;
                    }
                    else if (cnt[2] > 0) {
                        lbl_1_bss_C50[i] = 2;
                        cnt[2]--;
                    }
                    else {
                        lbl_1_bss_C50[i] = 0;
                        cnt[0]--;
                    }
                }
                else if (cnt[2] > 0) {
                    lbl_1_bss_C50[i] = 2;
                    cnt[2]--;
                }
                else if (cnt[0] > 0) {
                    lbl_1_bss_C50[i] = 0;
                    cnt[0]--;
                }
                else {
                    lbl_1_bss_C50[i] = 1;
                    cnt[1]--;
                }
            }
            lbl_1_bss_F14[1] = 360.0f / lbl_1_bss_F3C[1];
            lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_528)[lbl_1_bss_F3C[0]][0] - 12.0f;
            lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_528)[lbl_1_bss_F3C[0]][1] - 13.0f;
            lbl_1_bss_E9C[0].z = 100.0f + pos.z;
            for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                k = (lbl_1_bss_C50[i] == 0) ? 0x21 : (lbl_1_bss_C50[i] == 1) ? 0x22 : 0x23;
                lbl_1_bss_102A[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[k], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_102A[i], 1);
                rot = (HuVecF) { 90.0f, 0.0f, -4.0f };
                fn_1_25444(&rot, &rotOut);
                Hu3DModelRotSetV(lbl_1_bss_102A[i], &rotOut);
                Hu3DModelScaleSet(lbl_1_bss_102A[i], 0.13f * scale, 0.13f * scale, 0.13f * scale);
                Hu3DModelAttrSet(lbl_1_bss_102A[i], HU3D_ATTR_DISPOFF);
                Hu3DCamera[1] = Hu3DCamera[0];
                Hu3DModelLayerSet(lbl_1_bss_102A[i], 7);
                Hu3DModelCameraSet(lbl_1_bss_102A[i], 2);
                lbl_1_bss_C98[i] = pos;
                lbl_1_bss_C98[i].z += 100.0f;
                lbl_1_bss_C98[i].x += 155.0f * scale * sin(3.141592653589793 * (lbl_1_bss_F14[1] * i) / 180.0);
                lbl_1_bss_C98[i].y += 155.0f * scale * cos(3.141592653589793 * (lbl_1_bss_F14[1] * i) / 180.0);
                lbl_1_bss_C98[i].x += 7.0f;
                lbl_1_bss_1056[i] = Hu3DLLightCreate(lbl_1_bss_102A[i], lbl_1_bss_C98[i].x, lbl_1_bss_C98[i].y, lbl_1_bss_C98[i].z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
                Hu3DLLightStaticSet(lbl_1_bss_102A[i], lbl_1_bss_1056[i], 1);
                Hu3DLLightInfinitytSet(lbl_1_bss_102A[i], lbl_1_bss_1056[i]);
                Hu3D3Dto2D(&lbl_1_bss_C98[i], 1, &lbl_1_bss_D70[i]);
                fn_1_4F144(i, lbl_1_bss_E9C[0], lbl_1_bss_D70[i], 40, 0.0f, 0x21);
            }
            lbl_1_bss_F3C[2] = 0;
            lbl_1_bss_F14[2] = 0.13f * scale;
            lbl_1_bss_1168[1]++;
            break;
        case 4:
            lbl_1_bss_F14[2] += 0.02f * scale;
            if (lbl_1_bss_F14[2] > 0.2f * scale) {
                lbl_1_bss_F14[2] = 0.2f * scale;
            }
            for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                fn_1_4F1EC(i, &pos);
                lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_C98[i], pos.x, pos.y);
                Hu3DModelPosSetV(lbl_1_bss_102A[i], &lbl_1_bss_E9C[0]);
                Hu3DModelAttrReset(lbl_1_bss_102A[i], HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(lbl_1_bss_102A[i], lbl_1_bss_F14[2], lbl_1_bss_F14[2], lbl_1_bss_F14[2]);
            }
            lbl_1_bss_F3C[2]++;
            if (lbl_1_bss_F3C[2] > 50) {
                lbl_1_bss_F3C[2] = 1;
                lbl_1_bss_F3C[3] = 0;
                lbl_1_bss_F14[2] = 0.0f;
                lbl_1_bss_1168[1]++;
                HuAudFXPlay(0x2FF);
            }
            break;
        case 5:
            lbl_1_bss_F14[2] += lbl_1_bss_F14[1] / 10.0f;
            if (lbl_1_bss_F14[2] > 360.0f) {
                lbl_1_bss_F14[2] = lbl_1_bss_F14[1] / 10.0f;
                lbl_1_bss_F3C[2] = 1;
            }
            if (lbl_1_bss_F14[2] > lbl_1_bss_F14[1] * lbl_1_bss_F3C[2]) {
                if (lbl_1_bss_F3C[3] != 0) {
                    for (j = 0; ; j++) {
                        if (work->unk174[j] == work->unk174[lbl_1_bss_F3C[0]]) {
                            break;
                        }
                    }
                    for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                        if (i == lbl_1_bss_F3C[1] - lbl_1_bss_F3C[2]) {
                            lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_528)[work->unk170][0] - 12.0f;
                            lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_528)[work->unk170][1] - 13.0f;
                            if (lbl_1_bss_C50[i] == 0) {
                                player->unk44++;
                                work->player[work->unk174[lbl_1_bss_F3C[0]]].unk44--;
                            }
                            else if (lbl_1_bss_C50[i] == 1) {
                                player->unk48++;
                                work->player[work->unk174[lbl_1_bss_F3C[0]]].unk48--;
                            }
                            else if (lbl_1_bss_C50[i] == 2) {
                                player->unk4C++;
                                work->player[work->unk174[lbl_1_bss_F3C[0]]].unk4C--;
                            }
                            player->unk40 = player->unk44 + (player->unk48 * 2 + player->unk4C * -1);
                            work->player[work->unk174[lbl_1_bss_F3C[0]]].unk40 = work->player[work->unk174[lbl_1_bss_F3C[0]]].unk44 + (work->player[work->unk174[lbl_1_bss_F3C[0]]].unk48 * 2 + work->player[work->unk174[lbl_1_bss_F3C[0]]].unk4C * -1);
                            lbl_1_bss_BEC = work->unk174[lbl_1_bss_F3C[0]];
                            lbl_1_bss_BF0 = lbl_1_bss_C50[i];
                        }
                        else {
                            lbl_1_bss_E9C[0].x = ((float (*)[2])lbl_1_data_528)[j][0] - 12.0f;
                            lbl_1_bss_E9C[0].y = ((float (*)[2])lbl_1_data_528)[j][1] - 13.0f;
                        }
                        lbl_1_bss_E9C[0].z = 100.0f + pos.z;
                        Hu3D3Dto2D(&lbl_1_bss_C98[i], 1, &lbl_1_bss_D70[i]);
                        fn_1_4F144(i, lbl_1_bss_D70[i], lbl_1_bss_E9C[0], 40, 0.0f, 0x21);
                    }
                    lbl_1_bss_F14[2] = 0.0f;
                    lbl_1_bss_1168[1]++;
                    break;
                }
                else {
                    lbl_1_bss_F3C[2]++;
                }
            }
            for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                lbl_1_bss_C98[i] = pos;
                lbl_1_bss_C98[i].z += 100.0f;
                lbl_1_bss_C98[i].x += 155.0f * scale * sin(3.141592653589793 * (lbl_1_bss_F14[2] + lbl_1_bss_F14[1] * i) / 180.0);
                lbl_1_bss_C98[i].y += 155.0f * scale * cos(3.141592653589793 * (lbl_1_bss_F14[2] + lbl_1_bss_F14[1] * i) / 180.0);
                lbl_1_bss_C98[i].x += 7.0f;
                Hu3DModelPosSetV(lbl_1_bss_102A[i], &lbl_1_bss_C98[i]);
            }
            if (lbl_1_bss_F3C[3] == 0) {
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    fn_1_502E0(0x12);
                }
                fn_1_25518(work->unk174[work->unk170]);
                if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                    fn_1_50460();
                    lbl_1_bss_F3C[3] = 1;
                    HuAudFXPlay(0x301);
                }
            }
            break;
        case 6:
            lbl_1_bss_F14[2] += 5.0f;
            if (lbl_1_bss_F14[2] > 180.0f) {
                lbl_1_bss_F14[2] = 180.0f;
                lbl_1_bss_F14[3] = 0.2f * scale;
                lbl_1_bss_F3C[2] = 0;
                lbl_1_bss_1168[1]++;
            }
            rot = (HuVecF) { 90.0f, 0.0f, -4.0f };
            rot.y += lbl_1_bss_F14[2];
            fn_1_25444(&rot, &rotOut);
            Hu3DModelRotSetV(lbl_1_bss_1050[2], &rotOut);
            break;
        case 7:
            if (lbl_1_bss_F3C[2] >= 30) {
                lbl_1_bss_F14[3] -= 0.02f * scale;
                if (lbl_1_bss_F14[3] < 0.13f * scale) {
                    lbl_1_bss_F14[3] = 0.13f * scale;
                }
            }
            for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                fn_1_4F1EC(i, &pos);
                lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_C98[i], pos.x, pos.y);
                Hu3DModelPosSetV(lbl_1_bss_102A[i], &lbl_1_bss_E9C[0]);
                Hu3DModelScaleSet(lbl_1_bss_102A[i], lbl_1_bss_F14[3], lbl_1_bss_F14[3], lbl_1_bss_F14[3]);
            }
            lbl_1_bss_F3C[2]++;
            if (lbl_1_bss_F3C[2] > 40) {
                lbl_1_bss_F3C[2] = 0;
                if (lbl_1_bss_BF0 >= 0) {
                    if (lbl_1_bss_BF0 != 2) {
                        Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_BEC], lbl_1_bss_430[lbl_1_bss_BEC][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                            lbl_1_bss_20[1] = 0x1F6;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                            lbl_1_bss_20[1] = 0x1E2;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                            lbl_1_bss_20[1] = 0x25A;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                            lbl_1_bss_20[1] = 0x2AA;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                            lbl_1_bss_20[1] = 0x282;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                            lbl_1_bss_20[1] = 0x1BA;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                            lbl_1_bss_20[1] = 0x296;
                        }
                        fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        lbl_1_bss_20[1] = 0;
                    }
                    else {
                        Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_BEC], lbl_1_bss_430[lbl_1_bss_BEC][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                            lbl_1_bss_20[1] = 0x200;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                            lbl_1_bss_20[1] = 0x1EC;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                            lbl_1_bss_20[1] = 0x264;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                            lbl_1_bss_20[1] = 0x2B4;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                            lbl_1_bss_20[1] = 0x28C;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                            lbl_1_bss_20[1] = 0x1C4;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                            lbl_1_bss_20[1] = 0x2A0;
                        }
                        fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        lbl_1_bss_20[1] = 0;
                    }
                    HuAudFXPlay(8);
                }
                fn_1_2FFAC(work);
                lbl_1_bss_1168[1]++;
            }
            break;
        case 8:
            lbl_1_bss_F3C[2]++;
            if (lbl_1_bss_F3C[2] == 1) {
                for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_102A[i], HU3D_ATTR_DISPOFF);
                }
            }
            if (lbl_1_bss_F3C[2] == 20) {
                if (lbl_1_bss_BF0 == 1) {
                    HuAudFXPlay(8);
                }
                Hu3DModelAttrReset(lbl_1_bss_BE8, HU3D_ATTR_DISPOFF);
                fn_1_3FD5C();
            }
            if (lbl_1_bss_F3C[2] > 30) {
                Hu3DAnimModelKill(lbl_1_bss_1050[1]);
                Hu3DModelKill(lbl_1_bss_1050[0]);
                Hu3DModelKill(lbl_1_bss_1050[1]);
                Hu3DModelKill(lbl_1_bss_1050[2]);
                if (lbl_1_bss_102A[0] != -1) {
                    for (i = 0; i < lbl_1_bss_F3C[1]; i++) {
                        Hu3DLLightKill(lbl_1_bss_1050[0], lbl_1_bss_1056[i]);
                        Hu3DModelKill(lbl_1_bss_102A[i]);
                    }
                    result = 1;
                }
                else {
                    result = (lbl_1_bss_F3C[1] != 0) ? 1 : 2;
                }
                Hu3DLLightKill(lbl_1_bss_1050[0], lbl_1_bss_1056[18]);
                Hu3DLLightKill(lbl_1_bss_1050[1], lbl_1_bss_1056[19]);
                Hu3DLLightKill(lbl_1_bss_1050[2], lbl_1_bss_1056[20]);
                lbl_1_bss_1168[1] = 0;
            }
            break;
        case 99:
            rot = (HuVecF) { 90.0f, -10.0f, -4.0f };
            rot.y -= lbl_1_bss_F3C[1];
            fn_1_25444(&rot, &rotOut);
            Hu3DModelRotSetV(lbl_1_bss_1050[1], &rotOut);
            lbl_1_bss_F3C[1] = (lbl_1_bss_F3C[1] < 345) ? lbl_1_bss_F3C[1] + 15 : 0;
            if (Hu3DMotionEndCheck(lbl_1_bss_BE8)) {
                Hu3DModelAttrSet(lbl_1_bss_BE8, HU3D_ATTR_DISPOFF);
                lbl_1_bss_1168[1] = 1;
            }
            break;
    }
    return result;
}

/* 53 insns */
void *fn_1_25444(HuVecF *rot, HuVecF *out)
{
    Mtx mtx;
    Mtx rotMtx;

    PSMTXIdentity(mtx);
    PSMTXRotRad(rotMtx, 'x', 0.017453292f * rot->x);
    PSMTXConcat(mtx, rotMtx, mtx);
    PSMTXRotRad(rotMtx, 'z', 0.017453292f * rot->z);
    PSMTXConcat(mtx, rotMtx, mtx);
    PSMTXRotRad(rotMtx, 'y', 0.017453292f * rot->y);
    PSMTXConcat(mtx, rotMtx, mtx);
    Hu3DMtxRotGet(mtx, out);
    return mtx;
}

/* 67 insns */
void fn_1_25518(s32 playerNo)
{
    if (GwPlayerConf[playerNo].type != 0) {
        HuPadBtnDown[playerNo] = 0;
        HuPadDStkRep[playerNo] = 0;
        lbl_1_bss_C48[0]++;
        lbl_1_bss_C48[0] %= 350;
        if (lbl_1_bss_C48[0] > frandmod(300) + 31) {
            HuPadBtnDown[playerNo] = PAD_BUTTON_A;
            lbl_1_bss_C48[0] = 0;
        }
    }
}

/* 176 insns */
s32 fn_1_25624(CardGameWork *work)
{
    s32 flag;
    s32 i;
    CardPlayerWork *player;
    s32 x;
    s32 y;

    player = &work->player[work->unk174[work->unk170]];
    if (player->unk0 != 0) {
        return 1;
    }
    flag = 0;
    x = player->unk10 - 1;
    y = player->unk14;
    if (x < 0) {
        flag |= 1;
    }
    else if (lbl_1_bss_8C4[x][y] & 0x700) {
        flag |= 1;
    }
    else {
        for (i = 0; i < 4; i++) {
            if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                flag |= 1;
                break;
            }
        }
    }
    x = player->unk10 + 1;
    y = player->unk14;
    if (x > work->unk194 - 1) {
        flag |= 2;
    }
    else if (lbl_1_bss_8C4[x][y] & 0x700) {
        flag |= 2;
    }
    else {
        for (i = 0; i < 4; i++) {
            if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                flag |= 2;
                break;
            }
        }
    }
    x = player->unk10;
    y = player->unk14 - 1;
    if (y < 0) {
        flag |= 4;
    }
    else if (lbl_1_bss_8C4[x][y] & 0x700) {
        flag |= 4;
    }
    else {
        for (i = 0; i < 4; i++) {
            if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                flag |= 4;
                break;
            }
        }
    }
    x = player->unk10;
    y = player->unk14 + 1;
    if (y > work->unk194 - 1) {
        flag |= 8;
    }
    else if (lbl_1_bss_8C4[x][y] & 0x700) {
        flag |= 8;
    }
    else {
        for (i = 0; i < 4; i++) {
            if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                flag |= 8;
                break;
            }
        }
    }
    if (flag == 15) {
        return 1;
    }
    else {
        return 0;
    }
}


/* 3313 insns */
s32 fn_1_258E4(CardGameWork *work)
{
    s32 result;
    s32 i;
    CardPlayerWork *player;
    s32 x;
    s32 y;
    HuVecF pos;

    result = 0;
    player = &work->player[work->unk174[work->unk170]];
    x = player->unk10;
    y = player->unk14;
    fn_1_9C74(&pos, x, y, 1, 1);
    switch (lbl_1_bss_1168[1]) {
        case 0:
            pos.x += -50.0f;
            if (fn_1_30FA4(11, &pos)) {
                lbl_1_bss_1168[1]++;
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 15);
            }
            break;
        case 1:
            lbl_1_bss_111E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[GwPlayerConf[work->unk174[work->unk170]].charNo + 0x50], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_111E[0], 1);
            Hu3DModelRotSet(lbl_1_bss_111E[0], 0.0f, 0.0f, 0.0f);
            Hu3DModelShadowSet(lbl_1_bss_111E[0]);
            work->unk1A8 = 0;
            x = player->unk10 - 1;
            y = player->unk14;
            if (x < 0) {
                work->unk1A8 |= 1;
            }
            else if (lbl_1_bss_8C4[x][y] & 0x700) {
                work->unk1A8 |= 1;
            }
            else {
                for (i = 0; i < 4; i++) {
                    if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                        work->unk1A8 |= 1;
                        break;
                    }
                }
            }
            x = player->unk10 + 1;
            y = player->unk14;
            if (x > work->unk194 - 1) {
                work->unk1A8 |= 2;
            }
            else if (lbl_1_bss_8C4[x][y] & 0x700) {
                work->unk1A8 |= 2;
            }
            else {
                for (i = 0; i < 4; i++) {
                    if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                        work->unk1A8 |= 2;
                        break;
                    }
                }
            }
            x = player->unk10;
            y = player->unk14 - 1;
            if (y < 0) {
                work->unk1A8 |= 4;
            }
            else if (lbl_1_bss_8C4[x][y] & 0x700) {
                work->unk1A8 |= 4;
            }
            else {
                for (i = 0; i < 4; i++) {
                    if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                        work->unk1A8 |= 4;
                        break;
                    }
                }
            }
            x = player->unk10;
            y = player->unk14 + 1;
            if (y > work->unk194 - 1) {
                work->unk1A8 |= 8;
            }
            else if (lbl_1_bss_8C4[x][y] & 0x700) {
                work->unk1A8 |= 8;
            }
            else {
                for (i = 0; i < 4; i++) {
                    if (x == work->player[i].unk10 && y == work->player[i].unk14) {
                        work->unk1A8 |= 8;
                        break;
                    }
                }
            }
            if (!(work->unk1A8 & 1)) {
                pos.z -= 300.0f;
                work->unk1AC = 0;
            }
            else if (!(work->unk1A8 & 2)) {
                pos.z += 300.0f;
                work->unk1AC = 1;
            }
            else if (!(work->unk1A8 & 4)) {
                pos.x -= 300.0f;
                work->unk1AC = 2;
            }
            else if (!(work->unk1A8 & 8)) {
                pos.x += 300.0f;
                work->unk1AC = 3;
            }
            Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 80.0f, 100.0f + pos.y, 100.0f + pos.z);
            x = player->unk10;
            y = player->unk14;
            fn_1_9C74(&pos, x, y, 1, 1);
            pos.x += -50.0f;
            pos.y = 0.0f;
            lbl_1_bss_F86[0] = -1;
            if (!(work->unk1A8 & 1)) {
                lbl_1_bss_E9C[0] = pos;
                lbl_1_bss_E9C[0].z -= 300.0f;
                lbl_1_bss_F86[0] = fn_1_3ED3C(18, lbl_1_bss_E9C[0]);
            }
            lbl_1_bss_F86[1] = -1;
            if (!(work->unk1A8 & 2)) {
                lbl_1_bss_E9C[0] = pos;
                lbl_1_bss_E9C[0].z += 300.0f;
                lbl_1_bss_F86[1] = fn_1_3ED3C(18, lbl_1_bss_E9C[0]);
            }
            lbl_1_bss_F86[2] = -1;
            if (!(work->unk1A8 & 4)) {
                lbl_1_bss_E9C[0] = pos;
                lbl_1_bss_E9C[0].x -= 300.0f;
                lbl_1_bss_F86[2] = fn_1_3ED3C(18, lbl_1_bss_E9C[0]);
            }
            lbl_1_bss_F86[3] = -1;
            if (!(work->unk1A8 & 8)) {
                lbl_1_bss_E9C[0] = pos;
                lbl_1_bss_E9C[0].x += 300.0f;
                lbl_1_bss_F86[3] = fn_1_3ED3C(18, lbl_1_bss_E9C[0]);
            }
            lbl_1_bss_1168[1]++;
            break;
        case 2:
            if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                fn_1_502E0(19);
            }
            fn_1_290BC(work->unk174[work->unk170]);
            if (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_UP) {
                if (work->unk1AC != 0 && !(work->unk1A8 & 1)) {
                    work->unk1AC = 0;
                    HuAudFXPlay(0);
                }
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_DOWN) {
                if (work->unk1AC != 1 && !(work->unk1A8 & 2)) {
                    work->unk1AC = 1;
                    HuAudFXPlay(0);
                }
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_LEFT) {
                if (work->unk1AC != 2 && !(work->unk1A8 & 4)) {
                    work->unk1AC = 2;
                    HuAudFXPlay(0);
                }
            }
            else if (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_RIGHT) {
                if (work->unk1AC != 3 && !(work->unk1A8 & 8)) {
                    work->unk1AC = 3;
                    HuAudFXPlay(0);
                }
            }
            if (work->unk1AC == 0) {
                pos.z -= 300.0f;
            }
            else if (work->unk1AC == 1) {
                pos.z += 300.0f;
            }
            else if (work->unk1AC == 2) {
                pos.x -= 300.0f;
            }
            else if (work->unk1AC == 3) {
                pos.x += 300.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_111E[0], -50.0f + pos.x - 80.0f, 100.0f + pos.y, 100.0f + pos.z);
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                fn_1_50460();
                lbl_1_bss_E68[0].x = pos.x;
                lbl_1_bss_E68[0].y = 75.0f + pos.y;
                lbl_1_bss_E68[0].z = pos.z;
                if (work->unk1AC == 0) {
                    x = player->unk10 - 1;
                    y = player->unk14;
                }
                else if (work->unk1AC == 1) {
                    x = player->unk10 + 1;
                    y = player->unk14;
                }
                else if (work->unk1AC == 2) {
                    x = player->unk10;
                    y = player->unk14 - 1;
                }
                else if (work->unk1AC == 3) {
                    x = player->unk10;
                    y = player->unk14 + 1;
                }
                fn_1_28CA8(work, x, y);
                work->unk1AC = 0;
            if (x - 1 >= 0) {
                fn_1_28CA8(work, x - 1, y);
                lbl_1_bss_8C4[x][y] |= 1;
                lbl_1_bss_8C4[x - 1][y] |= 2;
                fn_1_AB64(x - 1, y, lbl_1_bss_8C4[x - 1][y]);
                if (!(lbl_1_bss_8C4[x - 1][y] & 0x700)) {
                    work->unk1AC |= 1;
                }
            }
            if (x + 1 <= work->unk194 - 1) {
                fn_1_28CA8(work, x + 1, y);
                lbl_1_bss_8C4[x][y] |= 2;
                lbl_1_bss_8C4[x + 1][y] |= 1;
                fn_1_AB64(x + 1, y, lbl_1_bss_8C4[x + 1][y]);
                if (!(lbl_1_bss_8C4[x + 1][y] & 0x700)) {
                    work->unk1AC |= 2;
                }
            }
            if (y - 1 >= 0) {
                fn_1_28CA8(work, x, y - 1);
                lbl_1_bss_8C4[x][y] |= 4;
                lbl_1_bss_8C4[x][y - 1] |= 8;
                fn_1_AB64(x, y - 1, lbl_1_bss_8C4[x][y - 1]);
                if (!(lbl_1_bss_8C4[x][y - 1] & 0x700)) {
                    work->unk1AC |= 4;
                }
            }
            if (y + 1 <= work->unk194 - 1) {
                fn_1_28CA8(work, x, y + 1);
                lbl_1_bss_8C4[x][y] |= 8;
                lbl_1_bss_8C4[x][y + 1] |= 4;
                fn_1_AB64(x, y + 1, lbl_1_bss_8C4[x][y + 1]);
                if (!(lbl_1_bss_8C4[x][y + 1] & 0x700)) {
                    work->unk1AC |= 8;
                }
            }
                fn_1_AB64(x, y, lbl_1_bss_8C4[x][y]);
                lbl_1_bss_8C4[x][y] |= 0x50;
                lbl_1_bss_F3C[8] = x;
                lbl_1_bss_F3C[9] = y;
                lbl_1_bss_1168[1]++;
                for (i = 0; i < 4; i++) {
                    if (lbl_1_bss_F86[i] != -1) {
                        fn_1_3F278(18, lbl_1_bss_F86[i]);
                    }
                }
                HuAudFXPlay(2);
            }
            break;
        case 3:
            lbl_1_bss_1080[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[104], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_1080[0], 1);
            Hu3DModelRotSet(lbl_1_bss_1080[0], 0.0f, 0.0f, 0.0f);
            Hu3DModelScaleSet(lbl_1_bss_1080[0], 0.7f, 1.0f, 0.7f);
            lbl_1_bss_E68[0].y += 5000.0f;
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + lbl_1_bss_E68[0].x, lbl_1_bss_E68[0].y, lbl_1_bss_E68[0].z);
            Hu3DModelShadowSet(lbl_1_bss_1080[0]);
            Hu3DModelShadowDispOff(lbl_1_bss_1080[0]);
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_1168[1]++;
            break;
        case 4:
            lbl_1_bss_F14[0] += 100.0f;
            if (5000.0f == lbl_1_bss_F14[0]) {
                omVibrate(0, 17, 12, 0);
                omVibrate(1, 17, 12, 0);
                omVibrate(2, 17, 12, 0);
                omVibrate(3, 17, 12, 0);
            }
            if (lbl_1_bss_F14[0] > 5000.0f) {
                lbl_1_bss_F14[0] = 5000.0f;
                Hu3DModelShadowReset(lbl_1_bss_111E[0]);
                Hu3DModelKill(lbl_1_bss_111E[0]);
                lbl_1_bss_F3C[0] = 100;
                lbl_1_bss_1168[1]++;
            }
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + lbl_1_bss_E68[0].x, lbl_1_bss_E68[0].y - lbl_1_bss_F14[0], lbl_1_bss_E68[0].z);
            if (lbl_1_bss_F14[0] >= 4700.0f) {
                Hu3DModelShadowDispOn(lbl_1_bss_1080[0]);
            }
            if (lbl_1_bss_F14[0] >= 4900.0f) {
                Hu3DModelAttrSet(lbl_1_bss_111E[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 5:
            if (lbl_1_bss_F3C[0] == 100) {
                fn_1_31AC0(&lbl_1_bss_E68[1], &lbl_1_bss_E68[2]);
                fn_1_8D04(0x428, lbl_1_bss_1080[0], 1);
            }
            if (lbl_1_bss_F3C[0] == 55) {
                omVibrate(0, 15, 4, 2);
                omVibrate(1, 15, 4, 2);
                omVibrate(2, 15, 4, 2);
                omVibrate(3, 15, 4, 2);
            }
            if (lbl_1_bss_F3C[0] == 10) {
                omVibrate(0, 10, 6, 6);
                omVibrate(1, 10, 6, 6);
                omVibrate(2, 10, 6, 6);
                omVibrate(3, 10, 6, 6);
            }
            pos.x = lbl_1_bss_E68[1].x + frandmod(lbl_1_bss_F3C[0]);
            pos.y = lbl_1_bss_E68[1].y + frandmod(lbl_1_bss_F3C[0]);
            pos.z = lbl_1_bss_E68[1].z + frandmod(lbl_1_bss_F3C[0]);
            fn_1_31710(&pos);
            pos.x = lbl_1_bss_E68[2].x + frandmod(lbl_1_bss_F3C[0]);
            pos.y = lbl_1_bss_E68[2].y + frandmod(lbl_1_bss_F3C[0]);
            pos.z = lbl_1_bss_E68[2].z + frandmod(lbl_1_bss_F3C[0]);
            fn_1_31788(&pos);
            lbl_1_bss_F3C[0] -= 3;
            if (lbl_1_bss_F3C[0] < 3) {
                fn_1_31710(&lbl_1_bss_E68[1]);
                fn_1_31788(&lbl_1_bss_E68[2]);
                lbl_1_bss_F14[0] = 0.7f;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 6:
            lbl_1_bss_F14[0] += 0.01f;
            if (lbl_1_bss_F14[0] > 0.99f) {
                lbl_1_bss_F14[0] = 0.99f;
                lbl_1_bss_F3C[0] = 0;
                fn_1_F2A8(0, 0, 0);
                lbl_1_bss_1168[1]++;
            }
            Hu3DModelScaleSet(lbl_1_bss_1080[0], lbl_1_bss_F14[0], 1.0f, lbl_1_bss_F14[0]);
            break;
        case 7:
            x = lbl_1_bss_F3C[8];
            y = lbl_1_bss_F3C[9];
            if (lbl_1_bss_F3C[0] == 0) {
                if (!(lbl_1_bss_8C4[x - 1][y] & 0x10)) {
                    if (work->unk1AC & 1) {
                        if (fn_1_F2A8(1, x - 1, y)) {
                            fn_1_F2A8(0, 0, 0);
                            lbl_1_bss_F3C[0]++;
                        }
                    }
                    else {
                        fn_1_F2A8(0, 0, 0);
                        lbl_1_bss_F3C[0]++;
                    }
                }
                else {
                    fn_1_F2A8(0, 0, 0);
                    lbl_1_bss_F3C[0]++;
                }
            }
            else if (lbl_1_bss_F3C[0] == 1) {
                if (!(lbl_1_bss_8C4[x + 1][y] & 0x10)) {
                    if (work->unk1AC & 2) {
                        if (fn_1_F2A8(1, x + 1, y)) {
                            fn_1_F2A8(0, 0, 0);
                            lbl_1_bss_F3C[0]++;
                        }
                    }
                    else {
                        fn_1_F2A8(0, 0, 0);
                        lbl_1_bss_F3C[0]++;
                    }
                }
                else {
                    fn_1_F2A8(0, 0, 0);
                    lbl_1_bss_F3C[0]++;
                }
            }
            else if (lbl_1_bss_F3C[0] == 2) {
                if (!(lbl_1_bss_8C4[x][y - 1] & 0x10)) {
                    if (work->unk1AC & 4) {
                        if (fn_1_F2A8(1, x, y - 1)) {
                            fn_1_F2A8(0, 0, 0);
                            lbl_1_bss_F3C[0]++;
                        }
                    }
                    else {
                        fn_1_F2A8(0, 0, 0);
                        lbl_1_bss_F3C[0]++;
                    }
                }
                else {
                    fn_1_F2A8(0, 0, 0);
                    lbl_1_bss_F3C[0]++;
                }
            }
            else {
                if (!(lbl_1_bss_8C4[x][y + 1] & 0x10)) {
                    if (work->unk1AC & 8) {
                        if (fn_1_F2A8(1, x, y + 1)) {
                            fn_1_F2A8(0, 0, 0);
                            lbl_1_bss_F3C[0]++;
                        }
                    }
                    else {
                        fn_1_F2A8(0, 0, 0);
                        lbl_1_bss_F3C[0]++;
                    }
                }
                else {
                    fn_1_F2A8(0, 0, 0);
                    lbl_1_bss_F3C[0]++;
                }
            }
            if (lbl_1_bss_F3C[0] == 4) {
                lbl_1_bss_1168[1]++;
            }
            break;
        case 8:
            lbl_1_bss_E68[0].y -= 5000.0f;
            lbl_1_bss_1080[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[26], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_1080[1], 1);
            Hu3DModelRotSet(lbl_1_bss_1080[1], 0.0f, 0.0f, 0.0f);
            Hu3DModelPosSet(lbl_1_bss_1080[1], -50.0f + lbl_1_bss_E68[0].x, lbl_1_bss_E68[0].y - 75.0f, lbl_1_bss_E68[0].z);
            Hu3DModelAttrSet(lbl_1_bss_1080[1], HU3D_ATTR_DISPOFF);
            pos.x = -50.0f + lbl_1_bss_E68[0].x;
            pos.y = lbl_1_bss_E68[0].y - 75.0f;
            pos.z = lbl_1_bss_E68[0].z;
            fn_1_3ED3C(17, pos);
            x = lbl_1_bss_F3C[8];
            y = lbl_1_bss_F3C[9];
            lbl_1_bss_F96[0] = -1;
            if (!(lbl_1_bss_8C4[x - 1][y] & 0x40) && (work->unk1AC & 1)) {
                lbl_1_bss_F96[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[((lbl_1_bss_8C4[x - 1][y] & 0xF) == 15) ? 13
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 12) ? 14
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 3) ? 15
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 11) ? 16
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 13) ? 17
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 7) ? 18
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 14) ? 19
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 10) ? 20
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 9) ? 21
                    : ((lbl_1_bss_8C4[x - 1][y] & 0xF) == 5) ? 22
                    : 23], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_F96[0], 1);
                Hu3DModelRotSet(lbl_1_bss_F96[0], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_F96[0], HU3D_ATTR_DISPOFF);
                pos.x = -50.0f + lbl_1_bss_E68[0].x;
                pos.y = lbl_1_bss_E68[0].y - 75.0f;
                pos.z = lbl_1_bss_E68[0].z - 300.0f;
                Hu3DModelPosSetV(lbl_1_bss_F96[0], &pos);
                fn_1_3ED3C(17, pos);
            }
            lbl_1_bss_F96[1] = -1;
            if (!(lbl_1_bss_8C4[x + 1][y] & 0x40) && (work->unk1AC & 2)) {
                lbl_1_bss_F96[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[((lbl_1_bss_8C4[x + 1][y] & 0xF) == 15) ? 13
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 12) ? 14
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 3) ? 15
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 11) ? 16
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 13) ? 17
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 7) ? 18
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 14) ? 19
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 10) ? 20
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 9) ? 21
                    : ((lbl_1_bss_8C4[x + 1][y] & 0xF) == 5) ? 22
                    : 23], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_F96[1], 1);
                Hu3DModelRotSet(lbl_1_bss_F96[1], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_F96[1], HU3D_ATTR_DISPOFF);
                pos.x = -50.0f + lbl_1_bss_E68[0].x;
                pos.y = lbl_1_bss_E68[0].y - 75.0f;
                pos.z = 300.0f + lbl_1_bss_E68[0].z;
                Hu3DModelPosSetV(lbl_1_bss_F96[1], &pos);
                fn_1_3ED3C(17, pos);
            }
            lbl_1_bss_F96[2] = -1;
            if (!(lbl_1_bss_8C4[x][y - 1] & 0x40) && (work->unk1AC & 4)) {
                lbl_1_bss_F96[2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[((lbl_1_bss_8C4[x][y - 1] & 0xF) == 15) ? 13
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 12) ? 14
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 3) ? 15
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 11) ? 16
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 13) ? 17
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 7) ? 18
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 14) ? 19
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 10) ? 20
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 9) ? 21
                    : ((lbl_1_bss_8C4[x][y - 1] & 0xF) == 5) ? 22
                    : 23], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_F96[2], 1);
                Hu3DModelRotSet(lbl_1_bss_F96[2], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_F96[2], HU3D_ATTR_DISPOFF);
                pos.x = -50.0f + lbl_1_bss_E68[0].x - 300.0f;
                pos.y = lbl_1_bss_E68[0].y - 75.0f;
                pos.z = lbl_1_bss_E68[0].z;
                Hu3DModelPosSetV(lbl_1_bss_F96[2], &pos);
                fn_1_3ED3C(17, pos);
            }
            lbl_1_bss_F96[3] = -1;
            if (!(lbl_1_bss_8C4[x][y + 1] & 0x40) && (work->unk1AC & 8)) {
                lbl_1_bss_F96[3] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[((lbl_1_bss_8C4[x][y + 1] & 0xF) == 15) ? 13
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 12) ? 14
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 3) ? 15
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 11) ? 16
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 13) ? 17
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 7) ? 18
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 14) ? 19
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 10) ? 20
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 9) ? 21
                    : ((lbl_1_bss_8C4[x][y + 1] & 0xF) == 5) ? 22
                    : 23], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelCameraSet(lbl_1_bss_F96[3], 1);
                Hu3DModelRotSet(lbl_1_bss_F96[3], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_F96[3], HU3D_ATTR_DISPOFF);
                pos.x = 300.0f + (-50.0f + lbl_1_bss_E68[0].x);
                pos.y = lbl_1_bss_E68[0].y - 75.0f;
                pos.z = lbl_1_bss_E68[0].z;
                Hu3DModelPosSetV(lbl_1_bss_F96[3], &pos);
                fn_1_3ED3C(17, pos);
            }
            lbl_1_bss_F3C[0] = 0;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_1168[1]++;
            fn_1_8D04(0x452, lbl_1_bss_478[x][y], 1);
            break;
        case 9:
            x = lbl_1_bss_F3C[8];
            y = lbl_1_bss_F3C[9];
            lbl_1_bss_F14[0] += 5.0f;
            if (lbl_1_bss_F14[0] > 200.0f) {
                lbl_1_bss_F14[0] = 200.0f;
                lbl_1_bss_1168[1]++;
            }
            Hu3DModelPosSet(lbl_1_bss_1080[0], -50.0f + lbl_1_bss_E68[0].x, lbl_1_bss_E68[0].y - lbl_1_bss_F14[0], lbl_1_bss_E68[0].z);
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] == 20) {
                Hu3DModelAttrSet(lbl_1_bss_478[x][y], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1080[1], HU3D_ATTR_DISPOFF);
                if (lbl_1_bss_F96[0] != -1) {
                    Hu3DModelAttrSet(lbl_1_bss_478[x - 1][y], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_F96[0], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_F96[1] != -1) {
                    Hu3DModelAttrSet(lbl_1_bss_478[x + 1][y], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_F96[1], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_F96[2] != -1) {
                    Hu3DModelAttrSet(lbl_1_bss_478[x][y - 1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_F96[2], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_F96[3] != -1) {
                    Hu3DModelAttrSet(lbl_1_bss_478[x][y + 1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_F96[3], HU3D_ATTR_DISPOFF);
                }
            }
            break;
        case 10:
            x = lbl_1_bss_F3C[8];
            y = lbl_1_bss_F3C[9];
            Hu3DModelShadowReset(lbl_1_bss_1080[0]);
            Hu3DModelKill(lbl_1_bss_1080[0]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_478[x][y]);
            Hu3DModelKill(lbl_1_bss_478[x][y]);
            lbl_1_bss_478[x][y] = lbl_1_bss_1080[1];
            Hu3DModelShadowMapSet(lbl_1_bss_478[x][y]);
            if (lbl_1_bss_F96[0] != -1) {
                Hu3DModelShadowMapObjReset(lbl_1_bss_478[x - 1][y]);
                Hu3DModelKill(lbl_1_bss_478[x - 1][y]);
                lbl_1_bss_478[x - 1][y] = lbl_1_bss_F96[0];
                Hu3DModelShadowMapSet(lbl_1_bss_478[x - 1][y]);
            }
            if (lbl_1_bss_F96[1] != -1) {
                Hu3DModelShadowMapObjReset(lbl_1_bss_478[x + 1][y]);
                Hu3DModelKill(lbl_1_bss_478[x + 1][y]);
                lbl_1_bss_478[x + 1][y] = lbl_1_bss_F96[1];
                Hu3DModelShadowMapSet(lbl_1_bss_478[x + 1][y]);
            }
            if (lbl_1_bss_F96[2] != -1) {
                Hu3DModelShadowMapObjReset(lbl_1_bss_478[x][y - 1]);
                Hu3DModelKill(lbl_1_bss_478[x][y - 1]);
                lbl_1_bss_478[x][y - 1] = lbl_1_bss_F96[2];
                Hu3DModelShadowMapSet(lbl_1_bss_478[x][y - 1]);
            }
            if (lbl_1_bss_F96[3] != -1) {
                Hu3DModelShadowMapObjReset(lbl_1_bss_478[x][y + 1]);
                Hu3DModelKill(lbl_1_bss_478[x][y + 1]);
                lbl_1_bss_478[x][y + 1] = lbl_1_bss_F96[3];
                Hu3DModelShadowMapSet(lbl_1_bss_478[x][y + 1]);
            }
            lbl_1_bss_1168[1] = 0;
            result = 1;
            break;
    }
    return result;
}

/* 261 insns */
void fn_1_28CA8(CardGameWork *work, s32 x, s32 y)
{
    HuVecF pos;

    if (lbl_1_bss_8C4[x][y] & 0x800) {
        lbl_1_bss_8C4[x][y] &= ~0x800;
        Hu3DModelShadowMapObjReset(lbl_1_bss_478[x][y]);
        Hu3DModelKill(lbl_1_bss_478[x][y]);
        lbl_1_bss_478[x][y] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[((lbl_1_bss_8C4[x][y] & 0xF) == 15) ? 13
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 12) ? 14
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 3) ? 15
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 11) ? 16
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 13) ? 17
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 7) ? 18
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 14) ? 19
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 10) ? 20
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 9) ? 21
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 5) ? 22
            : 23], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(lbl_1_bss_478[x][y], 1);
        fn_1_9C74(&pos, x, y, 1, 1);
        Hu3DModelPosSet(lbl_1_bss_478[x][y], -50.0f + pos.x, pos.y, pos.z);
        Hu3DModelRotSet(lbl_1_bss_478[x][y], 0.0f, 0.0f, 180.0f);
        Hu3DModelLayerSet(lbl_1_bss_478[x][y], 2);
        Hu3DModelShadowMapSet(lbl_1_bss_478[x][y]);
        work->unk1D4 = 0;
    }
}

/* 148 insns */
void fn_1_290BC(s32 playerNo)
{
    s32 r;

    if (GwPlayerConf[playerNo].type != 0) {
        HuPadBtnDown[playerNo] = 0;
        HuPadDStkRep[playerNo] = 0;
        if (lbl_1_bss_C48[1] == 0) {
            lbl_1_bss_C48[1] = frandmod(45) + 31;
        }
        lbl_1_bss_C48[0]++;
        if (lbl_1_bss_C48[0] == lbl_1_bss_C48[1]) {
            HuPadBtnDown[playerNo] = PAD_BUTTON_A;
            lbl_1_bss_C48[0] = 0;
            lbl_1_bss_C48[1] = 0;
        }
        else {
            if (lbl_1_bss_C40 > 0) {
            if (lbl_1_bss_C48[0] >= 15) {
                HuPadDStkRep[playerNo] = (lbl_1_bss_C40 == 1) ? PAD_BUTTON_UP
                    : (lbl_1_bss_C40 == 2) ? PAD_BUTTON_DOWN
                    : (lbl_1_bss_C40 == 3) ? PAD_BUTTON_LEFT
                    : PAD_BUTTON_RIGHT;
            }
        }
            else if (lbl_1_bss_C48[0] % 30 == 0) {
            r = frandmod(4);
            HuPadDStkRep[playerNo] = (r == 0) ? PAD_BUTTON_UP
                : (r == 1) ? PAD_BUTTON_DOWN
                : (r == 2) ? PAD_BUTTON_LEFT
                : PAD_BUTTON_RIGHT;
            }
        }
    }
}


/* 981 insns */
s32 fn_1_2930C(CardGameWork *work)
{
    s32 i;
    s32 result = 0;
    s32 cnt;
    s32 playerNo;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    HuVecF pos = { 288.0f, 150.0f, 1500.0f };
    s32 list[3];
    HuVecF out;

    switch (lbl_1_bss_1168[0]) {
        case 0:
            if (work->unk1D4 == 0) {
                fn_1_352D0(work);
            }
            if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0xF00) {
                if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x800) {
                    work->unk19C = 5;
                    lbl_1_bss_1168[0] = 1;
                }
                else {
                    if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x100) {
                        work->unk19C = 4;
                        HuAudFXPlay(0x447);
                    }
                    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x200) {
                        work->unk19C = 5;
                        HuAudFXPlay(0x448);
                    }
                    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x400) {
                        work->unk19C = 6;
                        HuAudFXPlay(0x44A);
                    }
                    lbl_1_bss_1168[0] = 20;
                }
                fn_1_30B00(work, -1);
            }
            else {
                lbl_1_bss_1168[0] = 1;
            }
            fn_1_F2A8(0, 0, 0);
            break;
        case 1:
            if (fn_1_F2A8(1, player->unk10, player->unk14)) {
                if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0xF00) {
                    if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x800) {
                        lbl_1_bss_1168[0] = 40;
                        HuAudSStreamVolSet(0, 0, 1000);
                    }
                    else {
                        lbl_1_bss_1168[0] = 3;
                    }
                }
                else if (frandmod(100) < 20 && !(player->unk50 & 0x400) && !(player->unk50 & 2) && !(player->unk50 & 4)
                    && work->unk1A0 == 0) {
                    work->unk184++;
                    player->unk50 |= 0x400;
                    lbl_1_bss_1168[0] = 30;
                }
                else {
                    lbl_1_bss_1168[0] = 0;
                    result = 1;
                }
            }
            break;
        case 2:
            if (fn_1_30FA4(work->unk19C, work)) {
                lbl_1_bss_1168[0] = 1;
                if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x200) {
                    if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x2000) {
                        if (frandmod(2) != 0) {
                            cnt = 0;
                        }
                        else if (player->unk50 & 0x1000) {
                            cnt = 0;
                        }
                        else if (fn_1_5710(work, work->unk170, 1)) {
                            cnt = 0;
                        }
                        else {
                            cnt = 0;
                            for (i = 0; i < 4; i++) {
                                if (i != work->unk170 && fn_1_5710(work, i, 0) == 0) {
                                    list[cnt] = i;
                                    cnt++;
                                }
                            }
                        }
                        if (cnt != 0) {
                            work->unk1A4 = list[frandmod(cnt)];
                        }
                        else {
                            work->unk1A4 = -1;
                            fn_1_F104(player->unk10, player->unk14);
                        }
                    }
                    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x1000) {
                        for (i = 0; i < 4; i++) {
                            if (i != work->unk174[work->unk170] && player->unk4 == work->player[i].unk0) {
                                lbl_1_bss_8C4[player->unk10][player->unk14] &= ~0x1000;
                                lbl_1_bss_8C4[player->unk10][player->unk14] |= 0x2000;
                                work->unk1A4 = -1;
                                fn_1_F1A8(player->unk10, player->unk14);
                                break;
                            }
                        }
                    }
                }
            }
            break;
        case 3:
            if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x100) {
                lbl_1_bss_1168[0] = 4;
            }
            else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x200) {
                lbl_1_bss_1168[0] = 5;
            }
            else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x400) {
                lbl_1_bss_1168[0] = 6;
                Hu3DModelShadowMapObjReset(lbl_1_bss_478[player->unk10][player->unk14]);
            }
            break;
        case 4:
            if (fn_1_2A260(work)) {
                work->unk1C8--;
                lbl_1_bss_1168[0] = 7;
            }
            break;
        case 5:
            if (fn_1_2B10C(work)) {
                work->unk1CC--;
                lbl_1_bss_1168[0] = 7;
            }
            break;
        case 6:
            if (fn_1_36C00(work)) {
                work->unk1D0--;
                lbl_1_bss_1168[0] = 7;
            }
            break;
        case 7:
            fn_1_2FFAC(work);
            lbl_1_bss_1168[0] = 8;
            break;
        case 8:
            if (fn_1_EB38(player->unk10, player->unk14)) {
                lbl_1_bss_8C4[player->unk10][player->unk14] &= 0xFF;
                if (work->unk1D4 == 10) {
                    work->unk184 = 0;
                    work->unk18C = 0x133;
                    fn_1_2FBCC(work);
                    lbl_1_bss_1168[0] = 0;
                    result = 1;
                }
                else {
                    lbl_1_bss_F3C[0] = player->unk10;
                    lbl_1_bss_F3C[1] = player->unk14;
                    lbl_1_bss_F3C[2] = player->unk20;
                    lbl_1_bss_F3C[3] = player->unk24;
                    if (180.0f == player->unk18) {
                        player->unk10++;
                        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
                            player->unk20 = 1;
                        }
                        else {
                            player->unk20 = 0;
                        }
                    }
                    else if (0.0f == player->unk18) {
                        player->unk10--;
                        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
                            player->unk20 = 1;
                        }
                        else {
                            player->unk20 = 2;
                        }
                    }
                    else if (-90.0f == player->unk18) {
                        player->unk14++;
                        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
                            player->unk24 = 1;
                        }
                        else {
                            player->unk24 = 0;
                        }
                    }
                    else if (90.0f == player->unk18) {
                        player->unk14--;
                        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
                            player->unk24 = 1;
                        }
                        else {
                            player->unk24 = 2;
                        }
                    }
                    if (work->unk1D4 == 20) {
                        work->unk184 = 0;
                        work->unk18C = 0x133;
                        lbl_1_bss_1168[0] = 0;
                        result = 1;
                    }
                    else if ((player->unk50 & 8) || (player->unk50 & 0x10)) {
                        work->unk184 = 0;
                        work->unk18C = 0x133;
                        if (player->unk50 & 8) {
                            fn_1_2B280(work);
                        }
                        else if (player->unk50 & 0x10) {
                            fn_1_2E548(work);
                        }
                        lbl_1_bss_1168[0] = 11;
                    }
                    else if (work->unk1D0 == 0) {
                        lbl_1_bss_1168[0] = 10;
                        fn_1_36828();
                        lbl_1_bss_F14[8] = 360.0f;
                        pos.y += lbl_1_bss_F14[8];
                        fn_1_36A70(&pos);
                        lbl_1_bss_F14[9] = 900.0f;
                        Hu3DModelRotSet(fn_1_36A60(), 0.0f, lbl_1_bss_F14[9], 0.0f);
                    }
                    else {
                        work->unk19C = (work->unk19C == 4) ? 3 : 8;
                        lbl_1_bss_1168[0] = 9;
                    }
                }
            }
            break;
        case 9:
            if (fn_1_30FA4(work->unk19C, work)) {
                player->unk10 = lbl_1_bss_F3C[0];
                player->unk14 = lbl_1_bss_F3C[1];
                player->unk20 = lbl_1_bss_F3C[2];
                player->unk24 = lbl_1_bss_F3C[3];
                lbl_1_bss_1168[0] = 0;
                result = 1;
                fn_1_30B00(work, 1);
            }
            break;
        case 10:
            if (fn_1_30FA4(0, work)) {
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            else {
                lbl_1_bss_F14[8] -= 6.0f;
                pos.y += lbl_1_bss_F14[8];
                fn_1_36A70(&pos);
                lbl_1_bss_F14[9] -= 15.0f;
                Hu3DModelRotSet(fn_1_36A60(), 0.0f, lbl_1_bss_F14[9], 0.0f);
            }
            break;
        case 11:
            if (fn_1_5248(work)) {
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            break;
        case 20:
            if (fn_1_325F4(work)) {
                lbl_1_bss_1168[0] = 2;
            }
            break;
        case 30:
            playerNo = work->unk174[work->unk170];
            if (GwPlayerConf[playerNo].type != 0) {
                HuPadBtnDown[playerNo] = 0;
                HuPadDStkRep[playerNo] = 0;
                lbl_1_bss_C48[0]++;
                lbl_1_bss_C48[0] %= 350;
                if (lbl_1_bss_C48[0] > frandmod(300) + 31) {
                    HuPadBtnDown[playerNo] = PAD_BUTTON_A;
                    lbl_1_bss_C48[0] = 0;
                }
            }
            if (fn_1_3EA44(work)) {
                work->unk184--;
                lbl_1_bss_C48[0] = 0;
                lbl_1_bss_C48[1] = 0;
                lbl_1_bss_1168[0] = 0;
                result = 1;
            }
            break;
        case 40:
            if (fn_1_30FA4(work->unk19C, work)) {
                fn_1_9C74(&out, player->unk10, player->unk14, 1, 1);
                out.x += -50.0f;
                lbl_1_bss_F84 = fn_1_3ED3C(0x19, out);
                lbl_1_bss_1168[0]++;
                fn_1_8D04(0x435, lbl_1_bss_478[player->unk10][player->unk14], 1);
                HuAudJinglePlay(0x8B);
            }
            break;
        case 41:
            if (fn_1_3F714(0x19, lbl_1_bss_F84)) {
                lbl_1_bss_1168[0]++;
            }
            break;
        case 42:
            if (fn_1_47AA8(work)) {
                if (work->unk1D4 == 1) {
                    work->unk1D4 = -1;
                }
                lbl_1_bss_1168[0] = 8;
            }
            break;
    }
    return result;
}

/* 939 insns */
s32 fn_1_2A260(CardGameWork *work)
{
    s32 idx;
    s16 mdl;
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    HuVecF pos;

    fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
    switch (lbl_1_bss_1168[1]) {
        case 0:
            if (player->unk3C == -1) {
                if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x1000) {
                    if (player->unk34 == -1) {
                        player->unk34 = 1;
                        lbl_1_bss_F3C[0] = 0;
                    }
                    else if (player->unk38 == -1) {
                        player->unk38 = 1;
                        lbl_1_bss_F3C[0] = 1;
                    }
                    else {
                        player->unk3C = 1;
                        lbl_1_bss_F3C[0] = 2;
                    }
                    lbl_1_bss_F3C[1] = 1;
                }
                else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x2000) {
                    if (player->unk34 == -1) {
                        player->unk34 = 2;
                        lbl_1_bss_F3C[0] = 0;
                    }
                    else if (player->unk38 == -1) {
                        player->unk38 = 2;
                        lbl_1_bss_F3C[0] = 1;
                    }
                    else {
                        player->unk3C = 2;
                        lbl_1_bss_F3C[0] = 2;
                    }
                    lbl_1_bss_F3C[1] = 2;
                }
                else {
                    if (player->unk34 == -1) {
                        player->unk34 = 0;
                        lbl_1_bss_F3C[0] = 0;
                    }
                    else if (player->unk38 == -1) {
                        player->unk38 = 0;
                        lbl_1_bss_F3C[0] = 1;
                    }
                    else {
                        player->unk3C = 0;
                        lbl_1_bss_F3C[0] = 2;
                    }
                    lbl_1_bss_F3C[1] = 0;
                }
                lbl_1_bss_1168[1]++;
            }
            else {
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 9);
                result = 1;
            }
            break;
        case 1:
            idx = (lbl_1_bss_F3C[1] == 0) ? 0x1A : ((lbl_1_bss_F3C[1] == 1) ? 0x18 : 0x19);
            lbl_1_bss_104E = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[idx], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_104E, 1);
            Hu3DModelPosSet(lbl_1_bss_104E, -50.0f + pos.x, 220.0f + pos.y, pos.z);
            Hu3DModelRotSet(lbl_1_bss_104E, 90.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(lbl_1_bss_104E, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(lbl_1_bss_104E, 0.5f, 0.5f, 0.5f);
            Hu3DModelLayerSet(lbl_1_bss_104E, 2);
            lbl_1_bss_1056[0] = Hu3DLLightCreate(lbl_1_bss_104E, -50.0f + pos.x, 220.0f + pos.y, 1000.0f + pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
            Hu3DLLightStaticSet(lbl_1_bss_104E, lbl_1_bss_1056[0], 1);
            Hu3DLLightInfinitytSet(lbl_1_bss_104E, lbl_1_bss_1056[0]);
            lbl_1_bss_E48.x = -50.0f + pos.x;
            lbl_1_bss_E48.y = 220.0f + pos.y;
            lbl_1_bss_E48.z = pos.z;
            pos.x += -50.0f;
            pos.y += 240.0f;
            pos.z += 100.0f;
            mdl = fn_1_3ED3C(1, pos);
            lbl_1_bss_E9C[0].x = 2.0f;
            lbl_1_bss_E9C[0].y = 2.0f;
            lbl_1_bss_E9C[0].z = 2.0f;
            fn_1_3F6B0(1, mdl, lbl_1_bss_E9C[0]);
            lbl_1_bss_F3C[2] = 0;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_1168[1]++;
            break;
        case 2:
            lbl_1_bss_F3C[2]++;
            if (lbl_1_bss_F3C[2] >= 10) {
                Hu3DModelAttrReset(lbl_1_bss_104E, HU3D_ATTR_DISPOFF);
                lbl_1_bss_F14[0] += (lbl_1_bss_F14[0] < 1080.0f) ? 108.0f
                    : ((lbl_1_bss_F14[0] < 1800.0f) ? 72.0f : ((lbl_1_bss_F14[0] < 2160.0f) ? 36.0f : 18.0f));
                if (lbl_1_bss_F14[0] >= 2880.0f) {
                    lbl_1_bss_F14[0] = 2880.0f;
                }
                Hu3DModelRotSet(lbl_1_bss_104E, 90.0f, lbl_1_bss_F14[0], 0.0f);
            }
            if (lbl_1_bss_F3C[2] == 10) {
                fn_1_8D04(0x409, lbl_1_bss_104E, 1);
            }
            if (2880.0f == lbl_1_bss_F14[0]) {
                lbl_1_bss_F3C[2] = 0;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 3:
            if (++lbl_1_bss_F3C[2] > 30) {
                Hu3D3Dto2D(&lbl_1_bss_E48, 1, &lbl_1_bss_E54);
                pos.x = (lbl_1_bss_F3C[0] == 0) ? ((float (*)[2])lbl_1_data_548)[work->unk170][0]
                    : ((lbl_1_bss_F3C[0] == 1) ? ((float (*)[2])lbl_1_data_568)[work->unk170][0] : ((float (*)[2])lbl_1_data_588)[work->unk170][0]);
                pos.y = (lbl_1_bss_F3C[0] == 0) ? ((float (*)[2])lbl_1_data_548)[work->unk170][1]
                    : ((lbl_1_bss_F3C[0] == 1) ? ((float (*)[2])lbl_1_data_568)[work->unk170][1] : ((float (*)[2])lbl_1_data_588)[work->unk170][1]);
                pos.z = lbl_1_bss_E48.z;
                fn_1_4F144(0, lbl_1_bss_E54, pos, 40, 0.0f, 0x21);
                lbl_1_bss_F3C[2] = 0;
                lbl_1_bss_F14[1] = 0.0f;
                Hu3DCamera[1] = Hu3DCamera[0];
                Hu3DModelLayerSet(lbl_1_bss_104E, 7);
                Hu3DModelCameraSet(lbl_1_bss_104E, 2);
                lbl_1_bss_12A8.unk28 = 60;
                if (lbl_1_bss_F3C[1] == 0) {
                    fn_1_4FBC8(work, 8);
                }
                else if (lbl_1_bss_F3C[1] == 1) {
                    fn_1_4FBC8(work, 6);
                }
                else if (lbl_1_bss_F3C[1] == 2) {
                    fn_1_4FBC8(work, 7);
                }
                lbl_1_bss_1168[1]++;
            }
            break;
        case 4:
            if (2880.0f == lbl_1_bss_F14[0]) {
                fn_1_8D04(0x40C, lbl_1_bss_104E, 1);
            }
            fn_1_8D04(0x840C, lbl_1_bss_104E, 1);
            lbl_1_bss_F14[0] -= (lbl_1_bss_F14[0] < 1080.0f) ? 108.0f
                : ((lbl_1_bss_F14[0] < 1800.0f) ? 72.0f : ((lbl_1_bss_F14[0] < 2160.0f) ? 36.0f : 18.0f));
            Hu3DModelRotSet(lbl_1_bss_104E, 90.0f, -lbl_1_bss_F14[0], 0.0f);
            if (lbl_1_bss_F14[0] < 2160.0f) {
                lbl_1_bss_F14[1] += 0.0125f;
                if (lbl_1_bss_F14[1] > 0.35f) {
                    lbl_1_bss_F14[1] = 0.35f;
                }
                Hu3DModelScaleSet(lbl_1_bss_104E, 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1], 0.5f - lbl_1_bss_F14[1]);
                fn_1_4F1EC(0, &pos);
                lbl_1_bss_E9C[0] = fn_1_4EDB8(lbl_1_bss_E48, pos.x, pos.y);
                Hu3DModelPosSetV(lbl_1_bss_104E, &lbl_1_bss_E9C[0]);
                lbl_1_bss_F3C[2]++;
                if (lbl_1_bss_F3C[2] > 40) {
                    Hu3DLLightKill(lbl_1_bss_104E, lbl_1_bss_1056[0]);
                    Hu3DModelKill(lbl_1_bss_104E);
                    lbl_1_bss_1168[1] = 0;
                    result = 1;
                }
                if (lbl_1_bss_F3C[2] == 40) {
                    fn_1_8D04(0x40A, lbl_1_bss_104E, 1);
                }
            }
            break;
    }
    return result;
}

/* 93 insns */
s32 fn_1_2B10C(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x1000) {
        if (fn_1_2E548(work)) {
            result = 1;
        }
    }
    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x2000) {
        if (fn_1_2B280(work)) {
            result = 1;
        }
    }
    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x4000) {
        if (fn_1_3FC50(work)) {
            result = 1;
        }
    }
    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x8000) {
        if (fn_1_42EDC(work)) {
            result = 1;
        }
    }
    return result;
}


/* 3250 insns */
s32 fn_1_2B280(CardGameWork *work)
{
    CardPlayerWork *p;
    s32 idx;
    s32 x;
    s32 y;
    s32 a;
    s32 b;
    CardPlayerWork *q;
    s32 rx;
    s32 ry;
    s32 ret;
    s32 i;
    s32 loop;
    s32 t0;
    s32 t10;
    s32 t14;
    s32 t20;
    s32 t24;
    float t18;
    float t1C;
    float ft;
    HuVecF tmp;

    ret = 0;
    p = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_1168[1]) {
        case 0:
            rx = fn_1_30FA4(7, work);
            if (rx != 0) {
                ry = work->unk1A4;
                if (ry == -1) {
                    lbl_1_bss_1168[1] = 10;
                }
                else {
                    lbl_1_bss_1168[1]++;
                }
            }
            break;
        case 1:
            idx = work->unk174[work->unk1A4];
            x = work->player[idx].unk10;
            y = work->player[idx].unk14;
            a = work->player[idx].unk20;
            b = work->player[idx].unk24;
            if (work->player[idx].unk0 == 1) {
                x--;
            }
            else if (work->player[idx].unk0 == 2) {
                x++;
            }
            else if (work->player[idx].unk0 == 3) {
                y--;
            }
            else if (work->player[idx].unk0 == 4) {
                y++;
            }
            fn_1_9C74(&lbl_1_bss_E68[1], x, y, a, b);
            lbl_1_bss_E60[1] = work->player[idx].unk18;
            x = p->unk10;
            y = p->unk14;
            a = p->unk20;
            b = p->unk24;
            if (180.0f == p->unk18) {
                x++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                }
                else {
                    a = 0;
                }
            }
            else if (0.0f == p->unk18) {
                x--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                }
                else {
                    a = 2;
                }
            }
            else if (-90.0f == p->unk18) {
                y++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                }
                else {
                    b = 0;
                }
            }
            else if (90.0f == p->unk18) {
                y--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                }
                else {
                    b = 2;
                }
            }
            fn_1_9C74(&lbl_1_bss_E68[0], x, y, a, b);
            lbl_1_bss_E60[0] = p->unk18;
            lbl_1_bss_1138 = 0;
            lbl_1_bss_113C = 0;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_F14[1] = 0.0f;
            lbl_1_bss_F14[2] = 0.0f;
            lbl_1_bss_1168[1] = 5;
            lbl_1_bss_F14[3] = 0.0f;
            break;
        case 2:
            idx = work->unk174[work->unk1A4];
            if (lbl_1_bss_1138 == 0) {
                lbl_1_bss_F14[0] = (lbl_1_bss_F14[0] < 90.0f) ? 5.0f + lbl_1_bss_F14[0] : 90.0f;
                lbl_1_bss_F14[1] += lbl_1_bss_F14[0];
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
                Hu3DModelRotSet(lbl_1_bss_468[idx], 0.0f, lbl_1_bss_E60[1] + lbl_1_bss_F14[1], 0.0f);
                if (lbl_1_bss_F14[1] > 1000.0f) {
                    if (lbl_1_bss_113C == 0) {
                        if (p->unk50 & 2) {
                            fn_1_3F278(3, p->unk56);
                            p->unk56 = -1;
                            p->unk50 &= ~2;
                        }
                        if (p->unk50 & 4) {
                            fn_1_3F278(4, p->unk56);
                            p->unk56 = -1;
                            p->unk50 &= ~4;
                        }
                        if (work->player[idx].unk50 & 4) {
                            fn_1_3F278(4, work->player[idx].unk56);
                            work->player[idx].unk56 = -1;
                        }
                    }
                    lbl_1_bss_113C += 20;
                    Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                        lbl_1_bss_113C + (lbl_1_bss_E68[0].y + lbl_1_bss_F14[3]), lbl_1_bss_E68[0].z);
                    Hu3DModelPosSet(lbl_1_bss_468[idx], -50.0f + lbl_1_bss_E68[1].x,
                        lbl_1_bss_113C + (lbl_1_bss_E68[1].y + lbl_1_bss_F14[3]), lbl_1_bss_E68[1].z);
                    if (lbl_1_bss_113C == 20) {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[1] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        fn_1_8D04(0x3FF, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                            lbl_1_bss_20[1] = 0x1F9;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                            lbl_1_bss_20[1] = 0x1E5;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                            lbl_1_bss_20[1] = 0x25D;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                            lbl_1_bss_20[1] = 0x2AD;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                            lbl_1_bss_20[1] = 0x285;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                            lbl_1_bss_20[1] = 0x1BD;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                            lbl_1_bss_20[1] = 0x299;
                        }
                        fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        lbl_1_bss_20[1] = 0;
                    }
                    else {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[0], lbl_1_bss_E9C[0]);
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[1], lbl_1_bss_E9C[0]);
                    }
                    Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    Hu3DModelScaleSet(lbl_1_bss_468[idx], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    lbl_1_bss_F14[2] += 0.05f;
                    if (lbl_1_bss_F14[2] > 1.0f) {
                        lbl_1_bss_F14[2] = 1.0f;
                    }
                    if (lbl_1_bss_113C == 1000) {
                        fn_1_3F278(8, lbl_1_bss_F92[0]);
                        fn_1_3F278(8, lbl_1_bss_F92[1]);
                        lbl_1_bss_1138 = 1;
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[1]++;
                    }
                }
            }
            else {
                lbl_1_bss_113C -= 20;
                if (lbl_1_bss_113C < 0) {
                    lbl_1_bss_113C = 0;
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                    lbl_1_bss_E68[0].y + lbl_1_bss_113C, lbl_1_bss_E68[0].z);
                Hu3DModelPosSet(lbl_1_bss_468[idx], -50.0f + lbl_1_bss_E68[1].x,
                    lbl_1_bss_E68[1].y + lbl_1_bss_113C, lbl_1_bss_E68[1].z);
                if (lbl_1_bss_113C <= 500) {
                    if (lbl_1_bss_113C == 500) {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[1] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        fn_1_8D04(0x400, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    }
                    else {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[0], lbl_1_bss_E9C[0]);
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[1], lbl_1_bss_E9C[0]);
                    }
                    Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    Hu3DModelScaleSet(lbl_1_bss_468[idx], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    lbl_1_bss_F14[2] -= 0.05f;
                    if (lbl_1_bss_F14[2] < 0.0f) {
                        lbl_1_bss_F14[2] = 0.0f;
                    }
                }
                if (lbl_1_bss_F14[1] <= 800.0f) {
                    lbl_1_bss_F14[0] = (lbl_1_bss_F14[0] > 0.0f) ? lbl_1_bss_F14[0] - 5.0f : 0.0f;
                }
                lbl_1_bss_F14[1] -= lbl_1_bss_F14[0];
                if (lbl_1_bss_F14[1] <= 0.0f) {
                    lbl_1_bss_F14[1] = 0.0f;
                    fn_1_3F278(8, lbl_1_bss_F92[0]);
                    fn_1_3F278(8, lbl_1_bss_F92[1]);
                    if (work->player[idx].unk50 & 4) {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        work->player[idx].unk56 = fn_1_3ED3C(4, lbl_1_bss_E9C[0]);
                    }
                    lbl_1_bss_1138 = 0;
                    p->unk50 |= 8;
                    lbl_1_bss_1168[1] = 4;
                    ret = 1;
                }
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
                Hu3DModelRotSet(lbl_1_bss_468[idx], 0.0f, lbl_1_bss_E60[1] + lbl_1_bss_F14[1], 0.0f);
            }
            break;
        case 3:
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] == 30) {
                fn_1_3F278(8, lbl_1_bss_F92[0]);
                fn_1_3F278(8, lbl_1_bss_F92[1]);
            }
            if (lbl_1_bss_F3C[0] >= 35) {
                lbl_1_bss_F3C[0] = 35;
                if (fn_1_30FA4(9, &lbl_1_bss_E68[1]) != 0) {
                    tmp = lbl_1_bss_E68[1];
                    lbl_1_bss_E68[1] = lbl_1_bss_E68[0];
                    lbl_1_bss_E68[0] = tmp;
                    ft = lbl_1_bss_E60[1];
                    lbl_1_bss_E60[1] = lbl_1_bss_E60[0];
                    lbl_1_bss_E60[0] = ft;
                    lbl_1_bss_1168[1] = 2;
                }
            }
            break;
        case 4:
            idx = work->unk174[work->unk1A4];
            t0 = work->player[idx].unk0;
            t10 = work->player[idx].unk10;
            t14 = work->player[idx].unk14;
            t20 = work->player[idx].unk20;
            t24 = work->player[idx].unk24;
            t18 = work->player[idx].unk18;
            t1C = work->player[idx].unk1C;
            work->player[idx].unk0 = p->unk0;
            work->player[idx].unk10 = p->unk10;
            work->player[idx].unk14 = p->unk14;
            work->player[idx].unk20 = p->unk20;
            work->player[idx].unk24 = p->unk24;
            work->player[idx].unk18 = p->unk18;
            work->player[idx].unk1C = p->unk1C;
            p->unk0 = t0;
            p->unk10 = t10;
            p->unk14 = t14;
            p->unk20 = t20;
            p->unk24 = t24;
            p->unk18 = t18;
            p->unk1C = t1C;
            lbl_1_bss_12A8.unk28 = 60;
            lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
            lbl_1_bss_12A8.unk8[1] = GwPlayerConf[idx].charNo;
            fn_1_4FBC8(work, 0x11);
            lbl_1_bss_1168[1] = 0;
            ret = 1;
            break;
        case 5:
            if (0.0f == lbl_1_bss_F14[3]) {
                fn_1_8D04(0x44F, lbl_1_bss_468[work->unk174[work->unk170]], 1);
            }
            idx = work->unk174[work->unk1A4];
            lbl_1_bss_F14[3] += 1.0f;
            if (lbl_1_bss_F14[3] > 50.0f) {
                lbl_1_bss_F14[3] = 50.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                lbl_1_bss_E68[0].y + lbl_1_bss_F14[3], lbl_1_bss_E68[0].z);
            Hu3DModelPosSet(lbl_1_bss_468[idx], -50.0f + lbl_1_bss_E68[1].x,
                lbl_1_bss_E68[1].y + lbl_1_bss_F14[3], lbl_1_bss_E68[1].z);
            lbl_1_bss_F14[1] += 10.0f;
            Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
            Hu3DModelRotSet(lbl_1_bss_468[idx], 0.0f, lbl_1_bss_E60[1] + lbl_1_bss_F14[1], 0.0f);
            if (lbl_1_bss_F14[1] >= 720.0f) {
                lbl_1_bss_F14[1] = 0.0f;
                lbl_1_bss_1168[1] = 2;
            }
            lbl_1_bss_E9C[8] = lbl_1_bss_E68[0];
            lbl_1_bss_E9C[8].x += -50.0f;
            lbl_1_bss_E9C[8].y += lbl_1_bss_F14[3];
            if (p->unk50 & 2) {
                fn_1_3F3D8(3, p->unk56, lbl_1_bss_E9C[8]);
            }
            if (p->unk50 & 4) {
                fn_1_3F3D8(4, p->unk56, lbl_1_bss_E9C[9]);
            }
            lbl_1_bss_E9C[9] = lbl_1_bss_E68[1];
            lbl_1_bss_E9C[9].x += -50.0f;
            lbl_1_bss_E9C[9].y += lbl_1_bss_F14[3];
            if (work->player[idx].unk50 & 2) {
                fn_1_3F3D8(3, work->player[idx].unk56, lbl_1_bss_E9C[8]);
            }
            if (work->player[idx].unk50 & 4) {
                fn_1_3F3D8(4, work->player[idx].unk56, lbl_1_bss_E9C[9]);
            }
            break;
        case 10:
            lbl_1_bss_1168[1]++;
            break;
        case 11:
            loop = 1;
            while (loop != 0) {
                rx = frandmod(work->unk194);
                ry = frandmod(work->unk194);
                if (lbl_1_bss_8C4[rx][ry] & 0x10) {
                    if (p->unk10 != rx || p->unk14 != ry) {
                        for (i = 0; i < 4; i++) {
                            q = &work->player[i];
                            if (rx == q->unk10 && ry == q->unk14 && q->unk20 == 1 && q->unk24 == 1) {
                                break;
                            }
                        }
                        if (i == 4) {
                            loop = 0;
                        }
                    }
                }
            }
            fn_1_9C74(&lbl_1_bss_E68[1], rx, ry, 1, 1);
            lbl_1_bss_F3C[8] = rx;
            lbl_1_bss_F3C[9] = ry;
            x = p->unk10;
            y = p->unk14;
            a = p->unk20;
            b = p->unk24;
            if (180.0f == p->unk18) {
                x++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                }
                else {
                    a = 0;
                }
            }
            else if (0.0f == p->unk18) {
                x--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                }
                else {
                    a = 2;
                }
            }
            else if (-90.0f == p->unk18) {
                y++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                }
                else {
                    b = 0;
                }
            }
            else if (90.0f == p->unk18) {
                y--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                }
                else {
                    b = 2;
                }
            }
            fn_1_9C74(&lbl_1_bss_E68[0], x, y, a, b);
            lbl_1_bss_E60[0] = p->unk18;
            lbl_1_bss_1138 = 0;
            lbl_1_bss_113C = 0;
            lbl_1_bss_F14[0] = 0.0f;
            lbl_1_bss_F14[1] = 0.0f;
            lbl_1_bss_F14[2] = 0.0f;
            lbl_1_bss_1168[1] = 15;
            lbl_1_bss_F14[3] = 0.0f;
            break;
        case 12:
            if (lbl_1_bss_1138 == 0) {
                lbl_1_bss_F14[0] = (lbl_1_bss_F14[0] < 90.0f) ? 5.0f + lbl_1_bss_F14[0] : 90.0f;
                lbl_1_bss_F14[1] += lbl_1_bss_F14[0];
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
                if (lbl_1_bss_F14[1] > 1000.0f) {
                    if (lbl_1_bss_113C == 0) {
                        if (p->unk50 & 2) {
                            fn_1_3F278(3, p->unk56);
                            p->unk56 = -1;
                            p->unk50 &= ~2;
                        }
                        if (p->unk50 & 4) {
                            fn_1_3F278(4, p->unk56);
                            p->unk56 = -1;
                            p->unk50 &= ~4;
                        }
                    }
                    lbl_1_bss_113C += 20;
                    Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                        lbl_1_bss_113C + (lbl_1_bss_E68[0].y + lbl_1_bss_F14[3]), lbl_1_bss_E68[0].z);
                    if (lbl_1_bss_113C == 20) {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        fn_1_8D04(0x3FF, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                            lbl_1_bss_20[1] = 0x1F9;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                            lbl_1_bss_20[1] = 0x1E5;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                            lbl_1_bss_20[1] = 0x25D;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                            lbl_1_bss_20[1] = 0x2AD;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                            lbl_1_bss_20[1] = 0x285;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                            lbl_1_bss_20[1] = 0x1BD;
                        }
                        if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                            lbl_1_bss_20[1] = 0x299;
                        }
                        fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        lbl_1_bss_20[1] = 0;
                    }
                    else {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[0], lbl_1_bss_E9C[0]);
                    }
                    Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    lbl_1_bss_F14[2] += 0.05f;
                    if (lbl_1_bss_F14[2] > 1.0f) {
                        lbl_1_bss_F14[2] = 1.0f;
                    }
                    if (lbl_1_bss_113C == 1000) {
                        fn_1_3F278(8, lbl_1_bss_F92[0]);
                        lbl_1_bss_1138 = 1;
                        lbl_1_bss_F3C[0] = 0;
                        lbl_1_bss_1168[1]++;
                    }
                }
            }
            else {
                lbl_1_bss_113C -= 20;
                if (lbl_1_bss_113C < 0) {
                    lbl_1_bss_113C = 0;
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                    lbl_1_bss_E68[0].y + lbl_1_bss_113C, lbl_1_bss_E68[0].z);
                if (lbl_1_bss_113C <= 500) {
                    if (lbl_1_bss_113C == 500) {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        lbl_1_bss_F92[0] = fn_1_3ED3C(8, lbl_1_bss_E9C[0]);
                        fn_1_8D04(0x400, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    }
                    else {
                        lbl_1_bss_E9C[0] = lbl_1_bss_E68[0];
                        lbl_1_bss_E9C[0].x += -50.0f;
                        lbl_1_bss_E9C[0].y += lbl_1_bss_113C;
                        fn_1_3F3D8(8, lbl_1_bss_F92[0], lbl_1_bss_E9C[0]);
                    }
                    Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f - lbl_1_bss_F14[2], 1.0f, 1.0f - lbl_1_bss_F14[2]);
                    lbl_1_bss_F14[2] -= 0.05f;
                    if (lbl_1_bss_F14[2] < 0.0f) {
                        lbl_1_bss_F14[2] = 0.0f;
                    }
                }
                if (lbl_1_bss_F14[1] <= 800.0f) {
                    lbl_1_bss_F14[0] = (lbl_1_bss_F14[0] > 0.0f) ? lbl_1_bss_F14[0] - 5.0f : 0.0f;
                }
                lbl_1_bss_F14[1] -= lbl_1_bss_F14[0];
                if (lbl_1_bss_F14[1] <= 0.0f) {
                    lbl_1_bss_F14[1] = 0.0f;
                    fn_1_3F278(8, lbl_1_bss_F92[0]);
                    lbl_1_bss_1138 = 0;
                    p->unk50 |= 8;
                    lbl_1_bss_1168[1] = 14;
                    ret = 1;
                }
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
            }
            break;
        case 13:
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] == 30) {
                fn_1_3F278(8, lbl_1_bss_F92[0]);
                fn_1_3F278(8, lbl_1_bss_F92[0]);
            }
            if (lbl_1_bss_F3C[0] >= 35) {
                lbl_1_bss_F3C[0] = 35;
                if (fn_1_30FA4(9, &lbl_1_bss_E68[1]) != 0) {
                    lbl_1_bss_E68[0] = lbl_1_bss_E68[1];
                    lbl_1_bss_1168[1] = 12;
                }
            }
            break;
        case 14:
            p->unk10 = lbl_1_bss_F3C[8];
            p->unk14 = lbl_1_bss_F3C[9];
            p->unk20 = 1;
            p->unk24 = 1;
            lbl_1_bss_12A8.unk28 = 60;
            lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
            fn_1_4FBC8(work, 0x3C);
            lbl_1_bss_1168[1] = 0;
            ret = 1;
            break;
        case 15:
            if (0.0f == lbl_1_bss_F14[3]) {
                fn_1_8D04(0x44F, lbl_1_bss_468[work->unk174[work->unk170]], 1);
            }
            lbl_1_bss_F14[3] += 1.0f;
            if (lbl_1_bss_F14[3] > 50.0f) {
                lbl_1_bss_F14[3] = 50.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x,
                lbl_1_bss_E68[0].y + lbl_1_bss_F14[3], lbl_1_bss_E68[0].z);
            lbl_1_bss_F14[1] += 10.0f;
            Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, lbl_1_bss_E60[0] + lbl_1_bss_F14[1], 0.0f);
            if (lbl_1_bss_F14[1] >= 720.0f) {
                lbl_1_bss_F14[1] = 0.0f;
                lbl_1_bss_1168[1] = 12;
            }
            lbl_1_bss_E9C[8] = lbl_1_bss_E68[0];
            lbl_1_bss_E9C[8].x += -50.0f;
            lbl_1_bss_E9C[8].y += lbl_1_bss_F14[3];
            if (p->unk50 & 2) {
                fn_1_3F3D8(3, p->unk56, lbl_1_bss_E9C[8]);
            }
            if (p->unk50 & 4) {
                fn_1_3F3D8(4, p->unk56, lbl_1_bss_E9C[9]);
            }
            break;
    }
    return ret;
}


/* 1441 insns */
s32 fn_1_2E548(CardGameWork *work)
{
    s32 x;
    s32 y;
    s32 a;
    s32 b;
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    HuVecF pos;
    HuVecF vec;

    fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
    switch (lbl_1_bss_1168[1]) {
        case 0:
            x = player->unk10;
            y = player->unk14;
            a = player->unk20;
            b = player->unk24;
            if (180.0f == player->unk18) {
                x++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                    lbl_1_bss_F14[8] = 300.0f;
                    lbl_1_bss_F14[9] = 201.5625f;
                }
                else {
                    a = 0;
                    lbl_1_bss_F14[8] = 201.5625f;
                    lbl_1_bss_F14[9] = 103.125f;
                }
            }
            else if (0.0f == player->unk18) {
                x--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    a = 1;
                    lbl_1_bss_F14[8] = 300.0f;
                    lbl_1_bss_F14[9] = 201.5625f;
                }
                else {
                    a = 2;
                    lbl_1_bss_F14[8] = 201.5625f;
                    lbl_1_bss_F14[9] = 103.125f;
                }
            }
            else if (-90.0f == player->unk18) {
                y++;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                    lbl_1_bss_F14[8] = 300.0f;
                    lbl_1_bss_F14[9] = 201.5625f;
                }
                else {
                    b = 0;
                    lbl_1_bss_F14[8] = 201.5625f;
                    lbl_1_bss_F14[9] = 103.125f;
                }
            }
            else if (90.0f == player->unk18) {
                y--;
                if (lbl_1_bss_8C4[x][y] & 0x40) {
                    b = 1;
                    lbl_1_bss_F14[8] = 300.0f;
                    lbl_1_bss_F14[9] = 201.5625f;
                }
                else {
                    b = 2;
                    lbl_1_bss_F14[8] = 201.5625f;
                    lbl_1_bss_F14[9] = 103.125f;
                }
            }
            fn_1_9C74(&lbl_1_bss_E68[0], x, y, a, b);
            x = player->unk8;
            y = player->unkC;
            a = 1;
            b = 1;
            if (player->unk4 == 1) {
                x--;
            }
            else if (player->unk4 == 2) {
                x++;
            }
            else if (player->unk4 == 3) {
                y--;
            }
            else if (player->unk4 == 4) {
                y++;
            }
            fn_1_9C74(&lbl_1_bss_E68[1], x, y, a, b);
            lbl_1_bss_F3C[0] = 0;
            lbl_1_bss_1168[1]++;
            break;
        case 1:
            if (lbl_1_bss_F3C[0] == 0) {
                fn_1_9C74(&lbl_1_bss_E9C[0], player->unk10, player->unk14, 1, 1);
                lbl_1_bss_E9C[0].x += -50.0f;
                lbl_1_bss_F8E[0] = fn_1_3ED3C(5, lbl_1_bss_E9C[0]);
                fn_1_8D04(0x414, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            lbl_1_bss_F3C[0]++;
            if (lbl_1_bss_F3C[0] == 100) {
                if (player->unk50 & 2) {
                    fn_1_3F278(3, player->unk56);
                    player->unk56 = -1;
                    player->unk50 &= ~2;
                }
                if (player->unk50 & 4) {
                    fn_1_3F278(4, player->unk56);
                    player->unk56 = -1;
                    player->unk50 &= ~4;
                }
                lbl_1_bss_F8E[1] = fn_1_3ED3C(7, lbl_1_bss_E9C[0]);
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_F14[1] = 0.0f;
                lbl_1_bss_F14[2] = 0.0f;
                lbl_1_bss_1168[1]++;
                omVibrate(work->unk174[work->unk170], 180, 6, 6);
                fn_1_8D04(0x415, lbl_1_bss_478[player->unk10][player->unk14], 1);
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                    lbl_1_bss_20[0] = 0x1F9;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                    lbl_1_bss_20[0] = 0x1E5;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                    lbl_1_bss_20[0] = 0x25D;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                    lbl_1_bss_20[0] = 0x2AD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                    lbl_1_bss_20[0] = 0x285;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                    lbl_1_bss_20[0] = 0x1BD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                    lbl_1_bss_20[0] = 0x299;
                }
                fn_1_8D04(lbl_1_bss_20[0], lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            vec.x = 0.1f * (frandmod(20) + 1);
            vec.x = frandmod(2) ? vec.x : -vec.x;
            vec.z = 0.1f * (frandmod(20) + 1);
            vec.z = frandmod(2) ? vec.z : -vec.z;
            if (180.0f == player->unk18) {
                lbl_1_bss_F14[0] -= lbl_1_bss_F14[8] / 66.66667f;
                if (lbl_1_bss_F14[0] < -lbl_1_bss_F14[8]) {
                    lbl_1_bss_F14[0] = -lbl_1_bss_F14[8];
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x + vec.x, lbl_1_bss_E68[0].y,
                    vec.z + (lbl_1_bss_E68[0].z + lbl_1_bss_F14[0]));
                if (lbl_1_bss_F14[0] < -lbl_1_bss_F14[9]) {
                    lbl_1_bss_F14[1] += 5.0f;
                    lbl_1_bss_F14[2] += 0.015f;
                }
            }
            else if (0.0f == player->unk18) {
                lbl_1_bss_F14[0] += lbl_1_bss_F14[8] / 66.66667f;
                if (lbl_1_bss_F14[0] > lbl_1_bss_F14[8]) {
                    lbl_1_bss_F14[0] = lbl_1_bss_F14[8];
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[0].x + vec.x, lbl_1_bss_E68[0].y,
                    vec.z + (lbl_1_bss_E68[0].z + lbl_1_bss_F14[0]));
                if (lbl_1_bss_F14[0] > lbl_1_bss_F14[9]) {
                    lbl_1_bss_F14[1] += 5.0f;
                    lbl_1_bss_F14[2] += 0.015f;
                }
            }
            else if (-90.0f == player->unk18) {
                lbl_1_bss_F14[0] -= lbl_1_bss_F14[8] / 66.66667f;
                if (lbl_1_bss_F14[0] < -lbl_1_bss_F14[8]) {
                    lbl_1_bss_F14[0] = -lbl_1_bss_F14[8];
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], vec.x + (-50.0f + lbl_1_bss_E68[0].x + lbl_1_bss_F14[0]),
                    lbl_1_bss_E68[0].y, lbl_1_bss_E68[0].z + vec.z);
                if (lbl_1_bss_F14[0] < -lbl_1_bss_F14[9]) {
                    lbl_1_bss_F14[1] += 5.0f;
                    lbl_1_bss_F14[2] += 0.015f;
                }
            }
            else if (90.0f == player->unk18) {
                lbl_1_bss_F14[0] += lbl_1_bss_F14[8] / 66.66667f;
                if (lbl_1_bss_F14[0] > lbl_1_bss_F14[8]) {
                    lbl_1_bss_F14[0] = lbl_1_bss_F14[8];
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], vec.x + (-50.0f + lbl_1_bss_E68[0].x + lbl_1_bss_F14[0]),
                    lbl_1_bss_E68[0].y, lbl_1_bss_E68[0].z + vec.z);
                if (lbl_1_bss_F14[0] > lbl_1_bss_F14[9]) {
                    lbl_1_bss_F14[1] += 5.0f;
                    lbl_1_bss_F14[2] += 0.015f;
                }
            }
            if (lbl_1_bss_F14[2] >= 1.0f) {
                lbl_1_bss_F14[2] = 1.0f;
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[1]++;
            }
            Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_F14[1], player->unk18 + lbl_1_bss_F14[1], lbl_1_bss_F14[1]);
            Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f - lbl_1_bss_F14[2], 1.0f - lbl_1_bss_F14[2], 1.0f - lbl_1_bss_F14[2]);
            break;
        case 3:
            if (lbl_1_bss_F3C[0] == 0) {
                fn_1_3F278(5, lbl_1_bss_F8E[0]);
                fn_1_9C74(&lbl_1_bss_E9C[0], player->unk10, player->unk14, 1, 1);
                lbl_1_bss_E9C[0].x += -50.0f;
                lbl_1_bss_F8E[0] = fn_1_3ED3C(6, lbl_1_bss_E9C[0]);
                lbl_1_bss_F3C[0]++;
                fn_1_8D04(0x418, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            if (fn_1_3F714(6, lbl_1_bss_F8E[0])) {
                fn_1_3F278(6, lbl_1_bss_F8E[0]);
                lbl_1_bss_1168[1]++;
            }
            break;
        case 4:
            if (fn_1_30FA4(10, &lbl_1_bss_E68[1])) {
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 5:
            if (lbl_1_bss_F3C[0] == 0) {
                lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                lbl_1_bss_E9C[0].x += -50.0f;
                lbl_1_bss_F8E[0] = fn_1_3ED3C(5, lbl_1_bss_E9C[0]);
                lbl_1_bss_F3C[0]++;
                fn_1_8D04(0x414, lbl_1_bss_470[work->unk174[work->unk170]], 1);
            }
            if (fn_1_3F714(5, lbl_1_bss_F8E[0])) {
                lbl_1_bss_F14[0] = 0.0f;
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x412, lbl_1_bss_470[work->unk174[work->unk170]], 1);
            }
            break;
        case 6:
            lbl_1_bss_F14[0] += 0.05f;
            if (lbl_1_bss_F14[0] > 1.0f) {
                lbl_1_bss_F14[0] = 1.0f;
                lbl_1_bss_F3C[0] = 0;
                lbl_1_bss_1168[1]++;
            }
            Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + lbl_1_bss_E68[1].x, lbl_1_bss_E68[1].y, lbl_1_bss_E68[1].z);
            Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, 0.0f, 0.0f);
            Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_F14[0], lbl_1_bss_F14[0], lbl_1_bss_F14[0]);
            break;
        case 7:
            if (lbl_1_bss_F3C[0] == 0) {
                fn_1_3F278(5, lbl_1_bss_F8E[0]);
                lbl_1_bss_E9C[0] = lbl_1_bss_E68[1];
                lbl_1_bss_E9C[0].x += -50.0f;
                lbl_1_bss_F8E[0] = fn_1_3ED3C(6, lbl_1_bss_E9C[0]);
                lbl_1_bss_F3C[0]++;
                fn_1_8D04(0x418, lbl_1_bss_470[work->unk174[work->unk170]], 1);
            }
            if (fn_1_3F714(6, lbl_1_bss_F8E[0])) {
                fn_1_3F278(6, lbl_1_bss_F8E[0]);
                lbl_1_bss_1168[1]++;
                player->unk50 |= 0x10;
                result = 1;
            }
            break;
        case 8:
            player->unk0 = player->unk4;
            player->unk10 = player->unk8;
            player->unk14 = player->unkC;
            player->unk20 = 1;
            player->unk24 = 1;
            lbl_1_bss_12A8.unk28 = 60;
            fn_1_4FBC8(work, 16);
            lbl_1_bss_1168[1] = 0;
            result = 1;
            break;
    }
    return result;
}

/* 202 insns */
void fn_1_2FBCC(CardGameWork *work)
{
    s32 i;
    s32 x;
    s32 y;
    s32 dir;
    HuVecF pos;

    if (work->unk1D4 == 1) {
        for (i = 0; i < 4; i++) {
            dir = work->player[i].unk4;
            x = work->player[i].unk8;
            y = work->player[i].unkC;
            if (dir == 1) {
                x--;
            }
            else if (dir == 2) {
                x++;
            }
            else if (dir == 3) {
                y--;
            }
            else if (dir == 4) {
                y++;
            }
            fn_1_9C74(&pos, x, y, 1, 1);
            pos.x += -50.0f;
            Hu3DModelPosSetV(lbl_1_bss_468[i], &pos);
            Hu3DModelRotSet(lbl_1_bss_468[i], 0.0f, 0.0f, 0.0f);
            if (work->player[i].unk50 & 2) {
                fn_1_3F278(3, work->player[i].unk56);
                work->player[i].unk56 = -1;
                work->player[i].unk50 &= ~2;
            }
            if (work->player[i].unk50 & 4) {
                if (i == work->unk174[work->unk170]) {
                    fn_1_3F278(4, work->player[i].unk56);
                    work->player[i].unk56 = -1;
                    work->player[i].unk50 &= ~4;
                }
                else {
                    HuVecF scale = { 1.0f, 1.0f, 1.0f };
                    fn_1_3F6B0(4, work->player[i].unk56, scale);
                    fn_1_3F540(4, work->player[i].unk56, 1);
                    fn_1_3F3D8(4, work->player[i].unk56, pos);
                }
            }
        }
        fn_1_5500(work);
        work->unk1D4 = 10;
    }
    else {
        for (i = 0; i < 4; i++) {
            work->player[i].unk0 = work->player[i].unk4;
            work->player[i].unk10 = work->player[i].unk8;
            work->player[i].unk14 = work->player[i].unkC;
            work->player[i].unk20 = 1;
            work->player[i].unk24 = 1;
        }
        work->unk1D4 = -1;
    }
}

/* 46 insns */
void fn_1_2FEF4(CardGameWork *work)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        work->player[i].unk30 = 1;
        work->player[i].unk34 = -1;
        work->player[i].unk38 = -1;
        work->player[i].unk3C = -1;
        work->player[i].unk40 = 0;
        work->player[i].unk44 = 0;
        work->player[i].unk48 = 0;
        work->player[i].unk4C = 0;
        work->player[i].unk50 = 0;
    }
}

/* 269 insns */
void fn_1_2FFAC(CardGameWork *work)
{
    s32 i;
    s32 j;
    s16 spr;
    s32 abs;
    CardPlayerWork *players[4];

    for (i = 0; i < 4; i++) {
        players[i] = &work->player[work->unk174[i]];
        players[i]->unk30 = 1;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i != j && players[j]->unk40 > players[i]->unk40) {
                players[i]->unk30++;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (j == players[i]->unk30 - 1) {
                espDispOn(lbl_1_bss_100A[i][j]);
            }
            else {
                espDispOff(lbl_1_bss_100A[i][j]);
            }
        }
        espBankSet(lbl_1_bss_FAA[i], players[i]->unk30 - 1);
        for (j = 0; j < 3; j++) {
            spr = (j == 0) ? lbl_1_bss_FC2[i] : ((j == 1) ? lbl_1_bss_FBA[i] : lbl_1_bss_FB2[i]);
            if ((&players[i]->unk34)[j] != -1) {
                espBankSet(spr, (&players[i]->unk34)[j]);
                espDispOn(spr);
            }
            else {
                espDispOff(spr);
            }
        }
        if (players[i]->unk40 > 0) {
            espBankSet(lbl_1_bss_FE2[i], 0);
        }
        else if (players[i]->unk40 < 0) {
            espBankSet(lbl_1_bss_FE2[i], 1);
        }
        else {
            espBankSet(lbl_1_bss_FE2[i], 2);
        }
        if (players[i]->unk40 < 10 && players[i]->unk40 > -10) {
            espBankSet(lbl_1_bss_FDA[i], 3);
        }
        else if (players[i]->unk40 < 20 && players[i]->unk40 > -20) {
            espBankSet(lbl_1_bss_FDA[i], 4);
        }
        else {
            espBankSet(lbl_1_bss_FDA[i], 5);
        }
        abs = (players[i]->unk40 >= 0) ? players[i]->unk40 : players[i]->unk40 * -1;
        espBankSet(lbl_1_bss_FD2[i], abs % 10 + 3);
    }
}

/* 62 insns */
void fn_1_303E0(CardGameWork *work)
{
    s32 j;
    s16 spr;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    for (j = 0; j < 3; j++) {
        spr = (j == 0) ? lbl_1_bss_FC2[work->unk170] : ((j == 1) ? lbl_1_bss_FBA[work->unk170] : lbl_1_bss_FB2[work->unk170]);
        if ((&player->unk34)[j] != -1) {
            espBankSet(spr, (&player->unk34)[j]);
            espDispOff(spr);
        }
    }
}

/* 55 insns */
void fn_1_304D8(CardGameWork *work, s32 *a1)
{
    s32 j;
    s16 spr;

    for (j = 0; j < 3; j++) {
        spr = (j == 0) ? lbl_1_bss_FC2[work->unk170] : ((j == 1) ? lbl_1_bss_FBA[work->unk170] : lbl_1_bss_FB2[work->unk170]);
        if (a1[j] != -1) {
            espBankSet(spr, a1[j]);
            espDispOn(spr);
        }
    }
}

/* 215 insns */
void fn_1_305B4(CardGameWork *work, s32 a1)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (i != work->unk170) {
            espColorSet(lbl_1_bss_1002[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FFA[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FF2[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_100A[i][0], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_100A[i][1], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_100A[i][2], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_100A[i][3], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FEA[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FE2[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FDA[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FD2[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FCA[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FC2[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FBA[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FB2[i], 255 - a1, 255 - a1, 255 - a1);
            espColorSet(lbl_1_bss_FAA[i], 255 - a1, 255 - a1, 255 - a1);
        }
    }
}

/* 124 insns */
void fn_1_30910(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        espKill(lbl_1_bss_1002[i]);
        espKill(lbl_1_bss_FFA[i]);
        espKill(lbl_1_bss_FF2[i]);
        espKill(lbl_1_bss_100A[i][0]);
        espKill(lbl_1_bss_100A[i][1]);
        espKill(lbl_1_bss_100A[i][2]);
        espKill(lbl_1_bss_100A[i][3]);
        espKill(lbl_1_bss_FEA[i]);
        espKill(lbl_1_bss_FE2[i]);
        espKill(lbl_1_bss_FDA[i]);
        espKill(lbl_1_bss_FD2[i]);
        espKill(lbl_1_bss_FCA[i]);
        espKill(lbl_1_bss_FC2[i]);
        espKill(lbl_1_bss_FBA[i]);
        espKill(lbl_1_bss_FB2[i]);
        espKill(lbl_1_bss_FAA[i]);
        espKill(lbl_1_bss_FA2[i]);
    }
    espKill(lbl_1_bss_F9E[0]);
    espKill(lbl_1_bss_F9E[1]);
}

/* 194 insns */
void fn_1_30B00(CardGameWork *work, s32 a1)
{
    if (a1 == 0) {
        lbl_1_bss_F9E[0] = espEntry(lbl_1_data_2B4[11], 0, 0);
        espDrawNoSet(lbl_1_bss_F9E[0], 0);
        espPosSet(lbl_1_bss_F9E[0], 182.0f, 90.0f);
        espBankSet(lbl_1_bss_F9E[0], 0);
        espDispOff(lbl_1_bss_F9E[0]);
        espPriSet(lbl_1_bss_F9E[0], 0x200);
        lbl_1_bss_F9E[1] = espEntry(lbl_1_data_2B4[11], 0, 0);
        espDrawNoSet(lbl_1_bss_F9E[1], 0);
        espPosSet(lbl_1_bss_F9E[1], 238.0f, 90.0f);
        espBankSet(lbl_1_bss_F9E[1], 0);
        espDispOff(lbl_1_bss_F9E[1]);
        espPriSet(lbl_1_bss_F9E[1], 0x200);
    }
    else if (a1 == 1) {
        if (work->unk184 / 10 > 0) {
            espBankSet(lbl_1_bss_F9E[0], work->unk184 / 10);
            espDispOn(lbl_1_bss_F9E[0]);
        }
        else {
            espDispOff(lbl_1_bss_F9E[0]);
        }
        if (work->unk184 / 10 > 0) {
            espPosSet(lbl_1_bss_F9E[1], 238.0f, 90.0f);
        }
        else {
            espPosSet(lbl_1_bss_F9E[1], 210.0f, 90.0f);
        }
        espBankSet(lbl_1_bss_F9E[1], work->unk184 % 10);
        espDispOn(lbl_1_bss_F9E[1]);
        if (work->unk184 == 0) {
            espDispOff(lbl_1_bss_F9E[0]);
            espDispOff(lbl_1_bss_F9E[1]);
        }
    }
    else if (a1 == -1) {
        espDispOff(lbl_1_bss_F9E[0]);
        espDispOff(lbl_1_bss_F9E[1]);
    }
}

