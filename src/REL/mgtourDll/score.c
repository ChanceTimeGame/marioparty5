/*
 * mgtourDll score.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgtourDll/asm/REL/mgtourDll/score.s.
 */

#include "REL/mgtourDll.h"

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
#include "math.h"

/* score.c lbl_1_data_920: 0x28 records; key = screen pos + a third word (time is a GUESS: 20/40/60/120, -1 unused) */
typedef struct MgTourScoreKey_s {
    HuVec2f pos; /* screen position (copied from lbl_1_data_8A8 by fn_1_BF2C) */
    float time; /* -1 = unused */
} MGTOUR_SCOREKEY;

typedef struct MgTourScoreRec_s {
    s32 num;
    MGTOUR_SCOREKEY key[3];
} MGTOUR_SCOREREC;

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_198 = 40.0f; /* 0x198 */
/* 0x1A0 lbl_1_rodata_1A0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_1A8 = 196.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 315.0f; /* 0x1AC */
/* 0x1B0 lbl_1_rodata_1B0 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1BC = 1000.0f; /* 0x1BC */
static const float lbl_1_rodata_1C0 = 1200.0f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = 72.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = 60.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = 0.5f; /* 0x1CC */
static const float lbl_1_rodata_1D0 = 0.7f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 0.35f; /* 0x1D4 */
static const float lbl_1_rodata_1D8 = 0.1f; /* 0x1D8 */
static const float lbl_1_rodata_1DC = 0.42f; /* 0x1DC */
static const double lbl_1_rodata_1E0 = 1.1111111111111112; /* 0x1E0 */
static const double lbl_1_rodata_1E8 = 3.141592653589793; /* 0x1E8 */
static const double lbl_1_rodata_1F0 = 0.5; /* 0x1F0 */
static const float lbl_1_rodata_1F8 = 20.0f; /* 0x1F8 */
static const float lbl_1_rodata_1FC = 30.0f; /* 0x1FC */
static const float lbl_1_rodata_200 = 0.5235988f; /* 0x200 */
static const float lbl_1_rodata_204 = 0.0f; /* 0x204 */
static const float lbl_1_rodata_208 = 120.0f; /* 0x208 */
static const double lbl_1_rodata_210 = 0.10000000149011612; /* 0x210 */
static const double lbl_1_rodata_218 = 0.9; /* 0x218 */
static const float lbl_1_rodata_220 = 50.0f; /* 0x220 */
static const float lbl_1_rodata_224 = 1.0f; /* 0x224 */
static const double lbl_1_rodata_228 = 180.0; /* 0x228 */
static const float lbl_1_rodata_230 = 10.0f; /* 0x230 */
static const float lbl_1_rodata_234 = 2.0f; /* 0x234 */
static const float lbl_1_rodata_238 = 360.0f; /* 0x238 */
/* 0x240 lbl_1_rodata_240 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_248 = 0.2f; /* 0x248 */
static const float lbl_1_rodata_24C = 0.0f; /* 0x24C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x177A0 */ MGTOUR_SCOREWORK lbl_1_bss_177A0;
/* 0x17770 */ HuVecF lbl_1_bss_17770[4]; /* PSVECSubtract operand (fn_1_B9C0) */
/* 0x17740 */ HuVecF lbl_1_bss_17740[4]; /* PSVECSubtract operand (fn_1_B9C0) */
/* 0x17710 */ HuVecF lbl_1_bss_17710[4]; /* PSVECSubtract operand (fn_1_B9C0) */
/* 0x176E0 */ HuVecF lbl_1_bss_176E0[4];

/* --- functions (reference order), .data placed before its first user --- */
/* 63 insns */
void fn_1_B8C4(s16 layerNo)
{
    int i;
    if (Hu3DCameraBit == HU3D_CAM1 && lbl_1_bss_177A0.player != 0) {
        for (i = 0; i < 4; i++) {
            Hu3DFbCopyExec((int)(lbl_1_bss_176E0[i].x - 40.0f), (int)(lbl_1_bss_176E0[i].y - 40.0f), 80, 80, GX_TF_RGB5A3, FALSE, lbl_1_bss_177A0.fbAnim[i]->bmp->data);
        }
        Hu3DZClear();
    }
}

/* 85 insns */
void fn_1_B9C0(void)
{
    HuVecF pos;
    int i;
    int time;
    MGTOUR_PLAYER *player;
    int maxTime;
    float t;
    maxTime = 120;
    for (time = 0; time <= maxTime; time++) {
        t = (float)time / (float)maxTime;
        for (i = 0; i < 4; i++) {
            player = &lbl_1_bss_177A0.player[lbl_1_bss_177A0.playerNo[i]];
            PSVECSubtract(&lbl_1_bss_17710[i], &lbl_1_bss_17740[i], &pos);
            PSVECScale(&pos, &pos, t);
            PSVECSubtract(&lbl_1_bss_17770[i], &pos, &pos);
            Hu3DModelPosSetV(player->mdlId, &pos);
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 25 insns */
void fn_1_BB14(s8 *arr, s32 num)
{
    s8 temp[4];
    int i;
    for (i = num; i--;) {
        temp[i] = arr[i];
    }
    for (i = 1; i < num; i++) {
        arr[i - 1] = temp[i];
    }
    arr[num - 1] = temp[0];
}

/* 114 insns */
void fn_1_BB78(s32 *out)
{
    s32 slot[4];
    switch (fn_1_9D4(0)) {
        case 0:
            out[0] = 4;
            out[1] = 5;
            slot[2] = 0;
            slot[0] = 1;
            break;
        case 1:
            out[0] = 5;
            out[1] = 4;
            slot[2] = 1;
            slot[0] = 0;
            break;
        case -1:
            out[0] = 0;
            out[1] = 1;
            out[2] = 2;
            out[3] = 3;
            break;
    }
    switch (fn_1_9D4(1)) {
        case 0:
            out[2] = 6;
            out[3] = 7;
            slot[3] = 2;
            slot[1] = 3;
            break;
        case 1:
            out[2] = 7;
            out[3] = 6;
            slot[3] = 3;
            slot[1] = 2;
            break;
        case -1:
            out[2] = 2;
            out[3] = 3;
            break;
    }
    switch (fn_1_9D4(2)) {
        case 0:
            out[slot[1]] = 8;
            break;
        case 1:
            out[slot[0]] = 8;
            break;
    }
    switch (fn_1_9D4(3)) {
        case 0:
            out[slot[2]] = 9;
            break;
        case 1:
            out[slot[3]] = 9;
            break;
    }
}

/* 0x3F0 */ HuVec2f lbl_1_data_3F0[2] = { { 288.0f, 800.0f }, { 288.0f, 240.0f } };
/* 0x400 */ HuVec2f lbl_1_data_400[2] = { { 288.0f, 800.0f }, { 288.0f, 150.0f } };
/* 0x410 */ HuVec2f lbl_1_data_410[2] = { { 288.0f, 800.0f }, { 288.0f, 240.0f } };
/* 0x420 */ u32 lbl_1_data_420[12] = { DATANUM(DATA_mgtour, 18), DATANUM(DATA_mgtour, 19), DATANUM(DATA_mgtour, 20), DATANUM(DATA_mgtour, 21), DATANUM(DATA_mgtour, 22), DATANUM(DATA_mgtour, 23), DATANUM(DATA_mgtour, 24), DATANUM(DATA_mgtour, 25), DATANUM(DATA_mgtour, 26), DATANUM(DATA_mgtour, 27), DATANUM(DATA_mgtour, 28), DATANUM(DATA_mgtour, 29) };
/* 0x450 */ HuVec2f lbl_1_data_450 = { 0.0f, -20.0f };
/* 0x458 */ HuVec2f lbl_1_data_458[12] = { { -128.0f, -45.0f }, { -63.0f, -45.0f }, { -128.0f, 75.0f }, { -63.0f, 75.0f }, { 126.0f, -45.0f }, { 189.0f, -45.0f }, { 126.0f, 75.0f }, { 189.0f, 75.0f }, { -61.0f, 109.0f }, { 65.0f, 109.0f }, { -61.0f, -76.0f }, { 62.0f, -76.0f } };
/* 0x4B8 */ GXColor lbl_1_data_4B8[12] = { { 42, 148, 0, 0 }, { 170, 12, 32, 0 } }; /* indexed by lbl_1_data_4E8 (0/1) */
/* 0x4E8 */ s32 lbl_1_data_4E8[12] = { 0x1, 0x1, 0x0, 0x0, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1 };
/* 0x52C */ char *lbl_1_data_52C[15] = {
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
/* 0x568 */ HuVecF lbl_1_data_568[13] = { { 0.0f, 110.0f, 0.0f }, { 0.0f, 125.0f, 0.0f }, { 0.0f, 140.0f, 0.0f }, { 0.0f, 120.0f, 0.0f }, { 0.0f, 100.0f, 0.0f }, { 0.0f, 140.0f, 0.0f }, { 0.0f, 160.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 80.0f, 0.0f } };
/* 0x604 */ HuVecF lbl_1_data_604[13] = { { -15.0f, 80.0f, 0.0f }, { 0.0f, 75.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { 7.0f, 72.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { -25.0f, 170.0f, 0.0f }, { 4.0f, 70.0f, 0.0f }, { 0.0f, 55.0f, 0.0f }, { 60.0f, 45.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 80.0f, 0.0f } };
/* 0x6A0 */ float lbl_1_data_6A0[130] = { 22.0f, 97.0f, 0.0f, -15.0f, 120.0f, 0.0f, 5.0f, 145.0f, 0.0f, 8.0f, 120.0f, 0.0f, 3.0f, 105.0f, 0.0f, -4.0f, 140.0f, 0.0f, 7.0f, 160.0f, 0.0f, 12.0f, 75.0f, 0.0f, 0.0f, 77.0f, 0.0f, 8.0f, 80.0f, 0.0f, 0.0f, 80.0f, 0.0f, 0.0f, 80.0f, 0.0f, 0.0f, 80.0f, 0.0f, -10.0f, 5.0f, 0.0f, 10.0f, 0.0f, -10.0f, 5.0f, -15.0f, 0.0f, -20.0f, 0.0f, 10.0f, -5.0f, -25.0f, 5.0f, -15.0f, -5.0f, 0.0f, 15.0f, 10.0f, 0.0f, -5.0f, 0.0f, -5.0f, 0.0f, -5.0f, 15.0f, 25.0f, 15.0f, 30.0f, 30.0f, 10.0f, 20.0f, 10.0f, 0.0f, 10.0f, 10.0f, 10.0f, 10.0f, 0.0f, -5.0f, 0.0f, -20.0f, 0.0f, -10.0f, -10.0f, -25.0f, 0.0f, -20.0f, 0.0f, 0.0f, 0.0f, -20.0f, 5.0f, -20.0f, 0.0f, 0.0f, 0.0f, -15.0f, 0.0f, 10.0f, 0.0f, 10.0f, 0.0f, 10.0f, -10.0f, 5.0f, 0.0f, 10.0f, 0.0f, -10.0f, 5.0f, -15.0f, 0.0f, -20.0f, 0.0f, 10.0f, -5.0f, -25.0f, 5.0f, -15.0f, -5.0f, 0.0f, 15.0f, 10.0f, 0.0f, -5.0f, 0.0f, -5.0f, 0.0f, -5.0f };
/* 0x8A8 */ HuVec2f lbl_1_data_8A8[14] = { { 99.0f, 259.0f }, { 226.0f, 259.0f }, { 352.0f, 259.0f }, { 479.0f, 259.0f }, { 163.0f, 163.0f }, { 163.0f, 348.0f }, { 415.0f, 163.0f }, { 415.0f, 348.0f }, { 289.0f, 600.0f }, { 289.0f, 132.0f }, { 188.0f, 140.0f }, { 388.0f, 140.0f }, { -200.0f, 550.0f }, { 776.0f, 550.0f } };
/* 0x918 */ HuVec2f lbl_1_data_918 = { 288.0f, 125.0f };
/* 0x920 */ MGTOUR_SCOREREC lbl_1_data_920[14] = { /* count + 3 vectors (0x28, mulli 0xC at +4) */
    { 1, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 3, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f } } },
    { 3, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f } } },
    { 3, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f } } },
    { 3, { { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, 20.0f } } },
    { 3, { { { 0.0f, 0.0f }, 40.0f }, { { 0.0f, 0.0f }, 40.0f }, { { 0.0f, 0.0f }, 15.0f } } },
    { 2, { { { 0.0f, 0.0f }, 40.0f }, { { 0.0f, 0.0f }, 20.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 60.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 60.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 120.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } },
    { 1, { { { 0.0f, 0.0f }, 120.0f }, { { 0.0f, 0.0f }, -1.0f }, { { 0.0f, 0.0f }, -1.0f } } }
};

/* 123 insns */
void fn_1_BD40(void)
{
    int i;
    MGTOUR_SCOREREC *rec;
    int j;
    for (i = 14; i--;) {
        rec = &lbl_1_data_920[i];
        for (j = 3; j--;) {
            rec->key[j].pos.x += lbl_1_data_450.x;
            rec->key[j].pos.y += lbl_1_data_450.y;
        }
    }
    for (i = 14; i--;) {
        lbl_1_data_8A8[i].x += lbl_1_data_450.x;
        lbl_1_data_8A8[i].y += lbl_1_data_450.y;
    }
    for (i = 12; i--;) {
        lbl_1_data_458[i].x += lbl_1_data_450.x;
        lbl_1_data_458[i].y += lbl_1_data_450.y;
    }
    lbl_1_data_918.x += lbl_1_data_450.x;
    lbl_1_data_918.y += lbl_1_data_450.y;
    lbl_1_data_400[1].x += lbl_1_data_450.x;
    lbl_1_data_400[1].y += lbl_1_data_450.y;
}

/* 238 insns */
void fn_1_BF2C(void)
{
    MGTOUR_SCOREREC *rec;
    rec = &lbl_1_data_920[0];
    rec->key[0].pos.x = lbl_1_data_8A8[0].x;
    rec->key[0].pos.y = 196.0f;
    rec = &lbl_1_data_920[1];
    rec->key[0].pos.x = lbl_1_data_8A8[1].x;
    rec->key[0].pos.y = 196.0f;
    rec = &lbl_1_data_920[2];
    rec->key[0].pos.x = lbl_1_data_8A8[2].x;
    rec->key[0].pos.y = 196.0f;
    rec = &lbl_1_data_920[3];
    rec->key[0].pos.x = lbl_1_data_8A8[3].x;
    rec->key[0].pos.y = 196.0f;
    rec = &lbl_1_data_920[4];
    rec->key[0].pos.x = lbl_1_data_8A8[0].x;
    rec->key[0].pos.y = 196.0f;
    rec->key[1].pos.x = lbl_1_data_8A8[4].x;
    rec->key[1].pos.y = 196.0f;
    rec->key[2].pos.x = lbl_1_data_8A8[4].x;
    rec->key[2].pos.y = lbl_1_data_8A8[4].y;
    rec = &lbl_1_data_920[5];
    rec->key[0].pos.x = lbl_1_data_8A8[0].x;
    rec->key[0].pos.y = 315.0f;
    rec->key[1].pos.x = lbl_1_data_8A8[5].x;
    rec->key[1].pos.y = 315.0f;
    rec->key[2].pos.x = lbl_1_data_8A8[5].x;
    rec->key[2].pos.y = lbl_1_data_8A8[5].y;
    rec = &lbl_1_data_920[6];
    rec->key[0].pos.x = lbl_1_data_8A8[2].x;
    rec->key[0].pos.y = 196.0f;
    rec->key[1].pos.x = lbl_1_data_8A8[6].x;
    rec->key[1].pos.y = 196.0f;
    rec->key[2].pos.x = lbl_1_data_8A8[6].x;
    rec->key[2].pos.y = lbl_1_data_8A8[6].y;
    rec = &lbl_1_data_920[7];
    rec->key[0].pos.x = lbl_1_data_8A8[2].x;
    rec->key[0].pos.y = 315.0f;
    rec->key[1].pos.x = lbl_1_data_8A8[7].x;
    rec->key[1].pos.y = 315.0f;
    rec->key[2].pos.x = lbl_1_data_8A8[7].x;
    rec->key[2].pos.y = lbl_1_data_8A8[7].y;
    rec = &lbl_1_data_920[8];
    rec->key[0].pos.x = lbl_1_data_8A8[8].x;
    rec->key[0].pos.y = lbl_1_data_8A8[7].y;
    rec->key[1].pos.x = lbl_1_data_8A8[8].x;
    rec->key[1].pos.y = lbl_1_data_8A8[7].y;
    rec->key[2].pos.x = lbl_1_data_8A8[8].x;
    rec->key[2].pos.y = lbl_1_data_8A8[8].y;
    rec = &lbl_1_data_920[9];
    rec->key[0].pos.x = lbl_1_data_8A8[9].x;
    rec->key[0].pos.y = lbl_1_data_8A8[4].y;
    rec->key[1].pos.x = lbl_1_data_8A8[9].x;
    rec->key[1].pos.y = lbl_1_data_8A8[9].y;
    rec = &lbl_1_data_920[10];
    rec->key[0].pos = lbl_1_data_8A8[10];
    rec = &lbl_1_data_920[11];
    rec->key[0].pos = lbl_1_data_8A8[11];
    rec = &lbl_1_data_920[12];
    rec->key[0].pos = lbl_1_data_8A8[12];
    rec = &lbl_1_data_920[13];
    rec->key[0].pos = lbl_1_data_8A8[13];
}

/* 84 insns */
void fn_1_C2E4(void)
{
    HuVecF pos2d;
    HuVecF pos;
    s32 slot[4];
    int i;
    s32 mdlId;
    fn_1_BB78(slot);
    for (i = 4; i--;) {
        mdlId = lbl_1_bss_177A0.mdlId[i + 12];
        pos2d.x = lbl_1_data_8A8[slot[i]].x;
        pos2d.y = lbl_1_data_8A8[slot[i]].y;
        pos2d.z = 1000.0f;
        Hu3D2Dto3D(&pos2d, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(mdlId, &pos);
    }
    {
        HuVecF unused = { 0.0f, 0.0f, -1.0f }; /* lbl_1_rodata_1B0: copied, never read */
        mdlId = lbl_1_bss_177A0.mdlId[4];
        pos2d.x = lbl_1_data_918.x;
        pos2d.y = lbl_1_data_918.y;
        pos2d.z = 1200.0f;
        Hu3D2Dto3D(&pos2d, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(mdlId, &pos);
    }
}

/* 206 insns */
void fn_1_C434(HU3DMODELID *mdlId)
{
    int i;
    lbl_1_bss_177A0.mdlId = mdlId;
    lbl_1_bss_177A0.unk0 = -1;
    lbl_1_bss_177A0.mode = 0;
    lbl_1_bss_177A0.grp10 = -1;
    lbl_1_bss_177A0.grp12 = -1;
    lbl_1_bss_177A0.unk26 = -1;
    for (i = 4; i--;) {
        lbl_1_bss_177A0.fbAnim[i] = HuSprAnimMake(80, 80, ANIM_BMP_RGB5A3);
        lbl_1_bss_177A0.fbAnim[i]->bmp->data = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_177A0.fbAnim[i]->bmp->dataSize, HU_MEMNUM_OVL);
        memset(lbl_1_bss_177A0.fbAnim[i]->bmp->data, 0, lbl_1_bss_177A0.fbAnim[i]->bmp->dataSize);
    }
    Hu3DLayerHookSet(1, fn_1_B8C4);
    fn_1_BD40();
    fn_1_BF2C();
}

/* 20 insns */
void fn_1_C76C(void)
{
    int i;
    for (i = 4; i--;) {
        HuSprAnimKill(lbl_1_bss_177A0.fbAnim[i]);
    }
}

/* 18 insns */
void fn_1_C7BC(s32 *playerNo, s32 *charNo)
{
    int i;
    for (i = 4; i--;) {
        lbl_1_bss_177A0.playerNo[i] = playerNo[i];
    }
}

/* 226 insns */
void fn_1_C804(void)
{
    HUSPRGRPID grpId;
    ANIMDATA *animP;
    int i;
    s32 memberNo;
    if (lbl_1_bss_177A0.unk0 < 0) {
        lbl_1_bss_177A0.unk0 = grpId = HuSprGrpCreate(14);
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 14), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(animP, 100, 0));
        HuSprScaleSet(grpId, 0, 72.0f, 60.0f);
        HuSprTPLvlSet(grpId, 0, 0.5f);
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 17), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, 1, HuSprCreate(animP, 70, 0));
        HuSprPosSet(grpId, 1, lbl_1_data_450.x, lbl_1_data_450.y);
        for (i = 12; i--;) {
            HuVec2f pos = lbl_1_data_450;
            memberNo = i + 2;
            animP = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_420[i], HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(animP, 50, 0));
            HuSprPosSet(grpId, memberNo, pos.x, pos.y);
            HuSprColorSet(grpId, memberNo, lbl_1_data_4B8[lbl_1_data_4E8[i]].r, lbl_1_data_4B8[lbl_1_data_4E8[i]].g, lbl_1_data_4B8[lbl_1_data_4E8[i]].b);
        }
        HuSprGrpDrawNoSet(grpId, 64);
        HuSprGrpPosSet(grpId, lbl_1_data_3F0[0].x, lbl_1_data_3F0[0].y);
        lbl_1_bss_177A0.unk24 = grpId = HuSprGrpCreate(1);
        switch (GWLanguageGet()) {
            case HUWIN_LANG_JAPAN:
                animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 16), HU_MEMNUM_OVL, HEAP_MODEL));
                break;
            case HUWIN_LANG_ENGLISH:
                animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 36), HU_MEMNUM_OVL, HEAP_MODEL));
                break;
        }
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(animP, 100, 0));
        HuSprGrpDrawNoSet(grpId, 64);
        HuSprGrpPosSet(grpId, lbl_1_data_400[0].x, lbl_1_data_400[0].y);
        HuSprExecLayerSet(64, 3);
    }
    fn_1_D658();
    if (fn_1_7E4(0x80000000) == 0) {
        fn_1_7AC(0x80000000);
        HuPrcChildCreate(fn_1_DEFC, 100, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 0xB50 */ HuVec2f lbl_1_data_B50 = { 0.0f, -160.0f };
/* 0xB58 */ HuVec2f lbl_1_data_B58[4] = { { -178.0f, 0.0f }, { -59.333332f, 0.0f }, { 59.333332f, 0.0f }, { 178.0f, 0.0f } };
/* 0xB78 */ HuVec2f lbl_1_data_B78[4] = { { -178.0f, 45.0f }, { -59.333332f, 45.0f }, { 59.333332f, 45.0f }, { 178.0f, 45.0f } };
/* 0xB98 */ HuVec2f lbl_1_data_B98[4] = { { -178.0f, -30.0f }, { -59.333332f, -30.0f }, { 59.333332f, -30.0f }, { 178.0f, -30.0f } };
/* 0xBB8 */ HuVec2f lbl_1_data_BB8 = { -178.0f, -90.0f };

/* 280 insns */
void fn_1_CB8C(s32 *arr)
{
    HuVecF pos;
    int i;
    HUSPRGRPID grpId;
    ANIMDATA *animP;
    s32 memberNo;
    s32 mdlId;
    if (lbl_1_bss_177A0.grp10 < 0) {
        lbl_1_bss_177A0.grp12 = grpId = HuSprGrpCreate(11);
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 14), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(animP, 100, 0));
        HuSprScaleSet(grpId, 0, 72.0f, 60.0f);
        HuSprTPLvlSet(grpId, 0, 0.7f);
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 32), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, 1, HuSprCreate(animP, 40, 0));
        HuSprPosSet(grpId, 1, lbl_1_data_B50.x, lbl_1_data_B50.y);
        HuSprGrpDrawNoSet(grpId, 64);
        HuSprGrpPosSet(grpId, lbl_1_data_410[0].x, lbl_1_data_410[0].y);
        lbl_1_bss_177A0.grp10 = grpId = HuSprGrpCreate(11);
        for (i = 4; i--;) {
            memberNo = i + 2;
            animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 33), HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(animP, 70, 0));
            HuSprPosSet(grpId, memberNo, lbl_1_data_B58[i].x, lbl_1_data_B58[i].y);
        }
        for (i = 4; i--;) {
            memberNo = i + 6;
            animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 30), HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(animP, 50, i));
            HuSprPosSet(grpId, memberNo, lbl_1_data_B78[i].x, lbl_1_data_B78[i].y);
        }
        animP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 31), HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprGrpMemberSet(grpId, 10, HuSprCreate(animP, 40, 0));
        HuSprPosSet(grpId, 10, lbl_1_data_BB8.x, lbl_1_data_BB8.y);
        HuSprGrpDrawNoSet(grpId, 64);
        HuSprGrpPosSet(grpId, lbl_1_data_410[0].x, lbl_1_data_410[0].y);
        HuSprExecLayerSet(64, 3);
    }
    for (i = 4; i--;) {
        lbl_1_bss_177A0.unk14[i] = arr[i];
        lbl_1_data_B98[i].x += lbl_1_data_410[1].x;
        lbl_1_data_B98[i].y += lbl_1_data_410[1].y;
        pos.x = lbl_1_data_B98[i].x;
        pos.y = lbl_1_data_B98[i].y;
        pos.z = 1000.0f;
        Hu3D2Dto3D(&pos, HU3D_CAM4, &pos);
        mdlId = lbl_1_bss_177A0.mdlId[lbl_1_bss_177A0.unk14[i] + 12];
        Hu3DModelPosSetV(mdlId, &pos);
    }
    if (fn_1_7E4(0x40000000) == 0) {
        fn_1_7AC(0x40000000);
        HuPrcChildCreate(fn_1_F708, 100, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 172 insns */
void fn_1_CFEC(s32 arg0)
{
    int i;
    s32 mdlId;
    if (arg0) {
        fn_1_C2E4();
        HuSprGrpPosSet(lbl_1_bss_177A0.unk0, lbl_1_data_3F0[1].x, lbl_1_data_3F0[1].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.unk24, lbl_1_data_400[0].x, lbl_1_data_400[0].y);
        for (i = 4; i--;) {
            mdlId = lbl_1_bss_177A0.mdlId[i + 12];
            Hu3DModelDispOn(mdlId);
            Hu3DModelScaleSet(mdlId, 0.35f, 0.35f, 0.1f);
        }
    } else {
        HuSprGrpPosSet(lbl_1_bss_177A0.unk0, lbl_1_data_3F0[0].x, lbl_1_data_3F0[0].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.unk24, lbl_1_data_400[0].x, lbl_1_data_400[0].y);
        for (i = 4; i--;) {
            mdlId = lbl_1_bss_177A0.mdlId[i + 12];
            Hu3DModelDispOff(mdlId);
        }
    }
}

/* 95 insns */
void fn_1_D29C(s32 arg0)
{
    int i;
    s32 mdlId;
    if (arg0) {
        HuSprGrpPosSet(lbl_1_bss_177A0.grp10, lbl_1_data_410[1].x, lbl_1_data_410[1].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.grp12, lbl_1_data_410[1].x, lbl_1_data_410[1].y);
        for (i = 4; i--;) {
            mdlId = lbl_1_bss_177A0.mdlId[i + 12];
            Hu3DModelDispOn(mdlId);
            Hu3DModelScaleSet(mdlId, 0.42f, 0.42f, 0.1f);
        }
    } else {
        HuSprGrpPosSet(lbl_1_bss_177A0.grp10, lbl_1_data_410[0].x, lbl_1_data_410[0].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.grp12, lbl_1_data_410[0].x, lbl_1_data_410[0].y);
        for (i = 4; i--;) {
            mdlId = lbl_1_bss_177A0.mdlId[i + 12];
            Hu3DModelDispOff(mdlId);
        }
    }
}

/* 129 insns */
void fn_1_D418(s32 arg0)
{
    if (arg0) {
        fn_1_C2E4();
        HuSprGrpPosSet(lbl_1_bss_177A0.unk0, lbl_1_data_3F0[1].x, lbl_1_data_3F0[1].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.unk24, lbl_1_data_400[0].x, lbl_1_data_400[0].y);
    } else {
        HuSprGrpPosSet(lbl_1_bss_177A0.unk0, lbl_1_data_3F0[0].x, lbl_1_data_3F0[0].y);
        HuSprGrpPosSet(lbl_1_bss_177A0.unk24, lbl_1_data_400[1].x, lbl_1_data_400[1].y);
    }
}

/* 5 insns */
void fn_1_D61C(s32 mode)
{
    lbl_1_bss_177A0.mode = mode;
}

/* 10 insns */
BOOL fn_1_D630(void)
{
    return lbl_1_bss_177A0.mode == 1;
}

/* 114 insns */
void fn_1_D658(void)
{
    s32 grpId;
    int i;
    MGTOUR_SCOREWORK *work;
    grpId = lbl_1_bss_177A0.unk0;
    for (i = 12; i--;) {
        HuSprDispOff(grpId, i + 2);
    }
    switch (fn_1_9D4(0)) {
        case 0:
            HuSprDispOn(grpId, 2);
            HuSprDispOn(grpId, 5);
            break;
        case 1:
            HuSprDispOn(grpId, 3);
            HuSprDispOn(grpId, 4);
            break;
    }
    switch (fn_1_9D4(1)) {
        case 0:
            HuSprDispOn(grpId, 6);
            HuSprDispOn(grpId, 9);
            break;
        case 1:
            HuSprDispOn(grpId, 7);
            HuSprDispOn(grpId, 8);
            break;
    }
    switch (fn_1_9D4(2)) {
        case 0:
            HuSprDispOn(grpId, 11);
            break;
        case 1:
            HuSprDispOn(grpId, 10);
            break;
    }
    switch (fn_1_9D4(3)) {
        case 0:
            HuSprDispOn(grpId, 12);
            break;
        case 1:
            HuSprDispOn(grpId, 13);
            break;
    }
    work = &lbl_1_bss_177A0;
    work->mode = 0;
}

/* 439 insns */
void fn_1_D820(s32 arg0, MGTOUR_PLAYER *player)
{
    HuVecF objPos;
    HuVecF scrPos;
    int i;
    MGTOUR_PLAYER *p;
    s16 x;
    s16 y;
    HU3DMODELID mdlId;
    HuPrcVSleep();
    lbl_1_bss_177A0.player = player;
    for (i = 0; i < 4; i++) {
        p = &player[lbl_1_bss_177A0.playerNo[i]];
        switch (p->mot) {
            case 0:
                OSReport("stand\n");
                Hu3DModelObjPosGet(p->mdlId, "root", &objPos);
                PSVECAdd(&lbl_1_data_568[p->charNo], &objPos, &objPos);
                Hu3D3Dto2D(&objPos, HU3D_CAM1, &scrPos);
                x = scrPos.x * 1.1111111111111112;
                y = scrPos.y;
                break;
            case 3:
                OSReport("lose\n");
                Hu3DModelObjPosGet(p->mdlId, "root", &objPos);
                PSVECAdd(&lbl_1_data_604[p->charNo], &objPos, &objPos);
                Hu3D3Dto2D(&objPos, HU3D_CAM1, &scrPos);
                x = scrPos.x * 1.1111111111111112;
                y = scrPos.y;
                break;
            case 2:
                OSReport("win\n");
                Hu3DModelObjPosGet(p->mdlId, "root", &objPos);
                PSVECAdd(&((HuVecF *)lbl_1_data_6A0)[p->charNo], &objPos, &objPos);
                Hu3D3Dto2D(&objPos, HU3D_CAM1, &scrPos);
                x = scrPos.x * 1.1111111111111112;
                y = scrPos.y;
                break;
        }
        x &= 0xFFFE;
        y &= 0xFFFE;
        lbl_1_bss_176E0[i].x = x;
        lbl_1_bss_176E0[i].y = y;
    }
    HuPrcVSleep();
    for (i = 4; i--;) {
        mdlId = lbl_1_bss_177A0.mdlId[i + 12];
        Hu3DAnimCreate(lbl_1_bss_177A0.fbAnim[i], mdlId, "S3TC_touei");
    }
    if (arg0) {
        fn_1_C2E4();
    } else {
        for (i = 0; i < 4; i++) {
            p = &player[lbl_1_bss_177A0.playerNo[i]];
            Hu3DModelObjPosGet(p->mdlId, "root", &objPos);
            lbl_1_bss_17770[i] = objPos;
            PSVECAdd(&lbl_1_data_568[p->charNo], &objPos, &objPos);
            Hu3D3Dto2D(&objPos, HU3D_CAM1, &scrPos);
            x = scrPos.x * 1.1111111111111112;
            y = scrPos.y;
            x &= 0xFFFE;
            y &= 0xFFFE;
            lbl_1_bss_176E0[i].x = x;
            lbl_1_bss_176E0[i].y = y;
            lbl_1_bss_17740[i] = lbl_1_data_568[p->charNo];
            switch (p->mot) {
                case 0:
                    lbl_1_bss_17710[i] = lbl_1_data_568[p->charNo];
                    break;
                case 3:
                    lbl_1_bss_17710[i] = lbl_1_data_604[p->charNo];
                    break;
                case 2:
                    lbl_1_bss_17710[i] = ((HuVecF *)lbl_1_data_6A0)[p->charNo];
                    break;
            }
        }
        HuPrcChildCreate(fn_1_B9C0, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}
#ifdef __MWERKS__
#endif

/* 1539 insns */
void fn_1_DEFC(void)
{
    HuVec2f pos2D[4];
    s32 rank[4];
    s32 recNo[4];
    s32 frame[4];
    s32 vecNo[4];
    HuVecF pos3;
    HuVecF out3;
    HuVecF pos5;
    HuVecF from5;
    HuVecF to5;
    HuVecF pos7;
    HuVecF from7;
    HuVecF to7;
    HuVecF pos11;
    HuVecF from11;
    HuVecF to11;
    s32 sprNo[2];
    HuVec2f center8;
    HuVec2f center9;
    s32 sprNum;
    s32 delay;
    s8 order[4];
    s32 doneNum5;
    s32 doneNum7;
    ANIMDATA *anim;
    float angleStep8;
    s32 padNo;
    HUSPRGRPID grpId;
    float t5;
    float angle9;
    float t11;
    float ratio9;
    float angle8;
    float radius8;
    float radius9;
    float scale9;
    float tpLvl11;
    float t7;
    float angleStep9;
    float tpLvl9;
    s32 start;
    MGTOUR_SCOREREC *rec5;
    MGTOUR_SCOREREC *rec7;
    MGTOUR_SCOREREC *rec11;
    MGTOUR_SCOREKEY *vec5;
    MGTOUR_SCOREKEY *vec7;
    MGTOUR_SCOREKEY *vec11;
    s32 mdlId;
    s32 seNo;
    s32 time;
    s32 num;
    MGTOUR_SCOREWORK *work;
    s32 i;

    work = &lbl_1_bss_177A0;
    seNo = -1;
    while (fn_1_7E4(0x80000000)) {
        switch (work->mode) {
            case 0:
                work->mode = 1;
                break;
            case 2:
                for (i = 4; i--;) {
                    order[i] = i;
                }
                fn_1_BB14(order, 4);
                num = 4;
                time = 120;
                delay = 6;
                work->mode = 3;
                break;
            case 3:
                start = 4 - num;
                delay--;
                if (delay == 0) {
                    fn_1_BB14(order, num);
                    delay = 6;
                    for (i = num; i--;) {
                        mdlId = lbl_1_bss_177A0.mdlId[order[i] + 12];
                        pos3.x = lbl_1_data_8A8[start + i].x;
                        pos3.y = lbl_1_data_8A8[start + i].y;
                        pos3.z = 1000.0f;
                        Hu3D2Dto3D(&pos3, HU3D_CAM2, &out3);
                        Hu3DModelPosSetV(mdlId, &out3);
                    }
                }
                if (--time == 0) {
                    time = 60;
                    mdlId = lbl_1_bss_177A0.mdlId[start + 12];
                    pos3.x = lbl_1_data_8A8[start].x;
                    pos3.y = lbl_1_data_8A8[start].y;
                    pos3.z = 1000.0f;
                    Hu3D2Dto3D(&pos3, HU3D_CAM2, &out3);
                    Hu3DModelPosSetV(mdlId, &out3);
                    switch (num) {
                        case 4:
                            HuAudFXPlayPan(1189, 52);
                            break;
                        case 3:
                            HuAudFXPlayPan(1189, 70);
                            break;
                        case 2:
                            HuAudFXPlayPan(1189, 82);
                            break;
                    }
                    if (--num == 1) {
                        mdlId = lbl_1_bss_177A0.mdlId[15];
                        pos3.x = lbl_1_data_8A8[3].x;
                        pos3.y = lbl_1_data_8A8[3].y;
                        pos3.z = 1000.0f;
                        Hu3D2Dto3D(&pos3, HU3D_CAM2, &out3);
                        Hu3DModelPosSetV(mdlId, &out3);
                        work->mode = 1;
                    }
                    start = 4 - num;
                    delay = 1;
                    for (i = num; i--;) {
                        order[i] = start + i;
                    }
                }
                break;
            case 4:
                for (i = 4; i--;) {
                    recNo[i] = -1;
                }
                fn_1_BB78(rank);
                switch (fn_1_99C()) {
                    case 0:
                        recNo[0] = 10;
                        recNo[1] = 11;
                        recNo[2] = 12;
                        recNo[3] = 13;
                        break;
                    case 1:
                        recNo[0] = 12;
                        recNo[1] = 13;
                        recNo[2] = 10;
                        recNo[3] = 11;
                        break;
                    case 2:
                        if (rank[0] == 4) {
                            recNo[0] = 12;
                            recNo[1] = 10;
                        } else {
                            recNo[0] = 10;
                            recNo[1] = 12;
                        }
                        if (rank[2] == 6) {
                            recNo[2] = 13;
                            recNo[3] = 11;
                        } else {
                            recNo[2] = 11;
                            recNo[3] = 13;
                        }
                        break;
                    case 3:
                        if (rank[0] == 4) {
                            recNo[0] = 10;
                            recNo[1] = 12;
                        } else {
                            recNo[0] = 12;
                            recNo[1] = 10;
                        }
                        if (rank[2] == 6) {
                            recNo[2] = 11;
                            recNo[3] = 13;
                        } else {
                            recNo[2] = 13;
                            recNo[3] = 11;
                        }
                        break;
                }
                for (i = 4; i--;) {
                    frame[i] = 0;
                    vecNo[i] = 0;
                }
                work->mode = 5;
                break;
            case 5:
                doneNum5 = 0;
                for (i = 4; i--;) {
                    if (recNo[i] >= 0) {
                        mdlId = lbl_1_bss_177A0.mdlId[i + 12];
                        rec5 = &lbl_1_data_920[recNo[i]];
                        vec5 = &rec5->key[vecNo[i]];
                        t5 = frame[i] / vec5->time;
                        t5 = sin(M_PI * t5 / 2.0);
                        t5 = sin(M_PI * t5 / 2.0);
                        if (vecNo[i] == 0) {
                            pos5.x = pos2D[i].x;
                            pos5.y = pos2D[i].y;
                            pos5.z = 1000.0f;
                            Hu3D2Dto3D(&pos5, HU3D_CAM2, &from5);
                        } else {
                            pos5.x = rec5->key[vecNo[i] - 1].pos.x;
                            pos5.y = rec5->key[vecNo[i] - 1].pos.y;
                            pos5.z = 1000.0f;
                            Hu3D2Dto3D(&pos5, HU3D_CAM2, &from5);
                        }
                        pos5.x = vec5->pos.x;
                        pos5.y = vec5->pos.y;
                        pos5.z = 1000.0f;
                        Hu3D2Dto3D(&pos5, HU3D_CAM2, &to5);
                        PSVECSubtract(&to5, &from5, &to5);
                        PSVECScale(&to5, &to5, t5);
                        PSVECAdd(&to5, &from5, &pos5);
                        Hu3DModelPosSetV(mdlId, &pos5);
                        frame[i]++;
                        if (vec5->time <= frame[i]) {
                            frame[i] = 0;
                            vecNo[i]++;
                            if (rec5->num == vecNo[i]) {
                                recNo[i] = -1;
                            }
                        }
                    } else {
                        doneNum5++;
                    }
                }
                if (doneNum5 == 4) {
                    work->mode = 1;
                }
                break;
            case 6:
                for (i = 4; i--;) {
                    recNo[i] = -1;
                }
                fn_1_BB78(rank);
                switch (fn_1_99C()) {
                    case 0:
                        if (!fn_1_7E4(8)) {
                            seNo = HuAudFXPlay(1195);
                        }
                        recNo[0] = 0;
                        recNo[1] = 1;
                        break;
                    case 1:
                        if (!fn_1_7E4(8)) {
                            seNo = HuAudFXPlay(1195);
                        }
                        recNo[2] = 2;
                        recNo[3] = 3;
                        break;
                }
                for (i = 4; i--;) {
                    pos2D[i] = lbl_1_data_8A8[rank[i]];
                    frame[i] = 0;
                    vecNo[i] = 0;
                }
                work->mode = 7;
                break;
            case 7:
                doneNum7 = 0;
                for (i = 4; i--;) {
                    if (recNo[i] >= 0) {
                        mdlId = lbl_1_bss_177A0.mdlId[i + 12];
                        rec7 = &lbl_1_data_920[recNo[i]];
                        vec7 = &rec7->key[vecNo[i]];
                        t7 = frame[i] / vec7->time;
                        if (vecNo[i] == 0) {
                            pos7.x = pos2D[i].x;
                            pos7.y = pos2D[i].y;
                            pos7.z = 1000.0f;
                            Hu3D2Dto3D(&pos7, HU3D_CAM2, &from7);
                        } else {
                            pos7.x = rec7->key[vecNo[i] - 1].pos.x;
                            pos7.y = rec7->key[vecNo[i] - 1].pos.y;
                            pos7.z = 1000.0f;
                            Hu3D2Dto3D(&pos7, HU3D_CAM2, &from7);
                        }
                        pos7.x = vec7->pos.x;
                        pos7.y = vec7->pos.y;
                        pos7.z = 1000.0f;
                        Hu3D2Dto3D(&pos7, HU3D_CAM2, &to7);
                        PSVECSubtract(&to7, &from7, &to7);
                        PSVECScale(&to7, &to7, t7);
                        PSVECAdd(&to7, &from7, &pos7);
                        Hu3DModelPosSetV(mdlId, &pos7);
                        frame[i]++;
                        if (vec7->time <= frame[i]) {
                            frame[i] = 0;
                            vecNo[i]++;
                            if (rec7->num == vecNo[i]) {
                                pos2D[i] = rec7->key[vecNo[i] - 1].pos;
                                recNo[i] = -1;
                            }
                        }
                    } else {
                        doneNum7++;
                    }
                }
                if (doneNum7 == 4) {
                    if (seNo >= 0) {
                        HuAudFXStop(seNo);
                        seNo = -1;
                    }
                    work->mode = 1;
                }
                break;
            case 8:
                center8 = lbl_1_data_918;
                center8.y -= 20.0f;
                if (lbl_1_bss_177A0.unk26 < 0) {
                    lbl_1_bss_177A0.unk26 = grpId = HuSprGrpCreate(12);
                    center8 = lbl_1_data_918;
                    center8.y -= 20.0f;
                    radius8 = 30.0f;
                    angleStep8 = 0.5235988f;
                    angle8 = 0.0f;
                    for (i = 12; i--;) {
                        anim = HuSprAnimDataRead(DATANUM(DATA_mgtour, 35));
                        HuSprGrpMemberSet(grpId, i, HuSprCreate(anim, 40, 0));
                        HuSprPosSet(lbl_1_bss_177A0.unk26, i, center8.x + radius8 * cos(angle8), center8.y + radius8 * sin(angle8));
                    }
                }
                time = 120;
                HuPrcChildCreate(fn_1_F9D0, 100, 0x1000, 0, HuPrcCurrentGet());
                HuAudFXPlay(1194);
                omVibrate(GwPlayerConf[fn_1_938(fn_1_96C())].padNo, 20, 4, 2);
                work->mode = 9;
                break;
            case 9:
                center9 = lbl_1_data_918;
                center9.y -= 20.0f;
                ratio9 = time / 120.0f;
                tpLvl9 = 0.5f * ratio9;
                scale9 = 0.10000000149011612 + 0.9 * ratio9;
                radius9 = 30.0f + 50.0f * (1.0f - ratio9);
                angleStep9 = 0.5235988f;
                angle9 = 0.0f;
                for (i = 12; i--;) {
                    HuSprPosSet(lbl_1_bss_177A0.unk26, i, center9.x + radius9 * cos(angle9), center9.y + radius9 * sin(angle9));
                    HuSprTPLvlSet(lbl_1_bss_177A0.unk26, i, tpLvl9);
                    HuSprScaleSet(lbl_1_bss_177A0.unk26, i, scale9, scale9);
                    angle9 += angleStep9;
                }
                if (--time == 0) {
                    work->mode = 1;
                }
                break;
            case 10:
                for (i = 4; i--;) {
                    recNo[i] = -1;
                }
                fn_1_BB78(rank);
                num = 4;
                switch (fn_1_99C()) {
                    case 0:
                        sprNum = 2;
                        if (fn_1_96C() == 0) {
                            sprNo[0] = 2;
                            sprNo[1] = 5;
                            recNo[0] = 4;
                            recNo[1] = 5;
                        } else {
                            sprNo[0] = 3;
                            sprNo[1] = 4;
                            recNo[0] = 5;
                            recNo[1] = 4;
                        }
                        break;
                    case 1:
                        sprNum = 2;
                        if (fn_1_96C() == 0) {
                            sprNo[0] = 6;
                            sprNo[1] = 9;
                            recNo[2] = 6;
                            recNo[3] = 7;
                        } else {
                            sprNo[0] = 7;
                            sprNo[1] = 8;
                            recNo[2] = 7;
                            recNo[3] = 6;
                        }
                        break;
                    case 2:
                        sprNum = 1;
                        if (fn_1_96C() == 0) {
                            sprNo[0] = 11;
                            if (rank[2] == 6) {
                                recNo[3] = 8;
                            } else {
                                recNo[2] = 8;
                            }
                        } else {
                            sprNo[0] = 10;
                            if (rank[0] == 4) {
                                recNo[1] = 8;
                            } else {
                                recNo[0] = 8;
                            }
                        }
                        break;
                    case 3:
                        sprNum = 1;
                        if (fn_1_96C() == 0) {
                            sprNo[0] = 12;
                            if (rank[0] == 4) {
                                recNo[0] = 9;
                            } else {
                                recNo[1] = 9;
                            }
                        } else {
                            sprNo[0] = 13;
                            if (rank[2] == 6) {
                                recNo[2] = 9;
                            } else {
                                recNo[3] = 9;
                            }
                        }
                        num = 2;
                        break;
                }
                for (i = sprNum; i--;) {
                    HuSprAttrReset(work->unk0, sprNo[i], HUSPR_ATTR_DISPOFF);
                    HuSprTPLvlSet(work->unk0, sprNo[i], 0.0f);
                }
                for (i = 4; i--;) {
                    switch (recNo[i]) {
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                            lbl_1_data_920[recNo[i]].key[0].pos.x = lbl_1_data_8A8[rank[i]].x;
                            break;
                    }
                }
                for (i = 4; i--;) {
                    pos2D[i] = lbl_1_data_8A8[rank[i]];
                    frame[i] = 0;
                    vecNo[i] = 0;
                }
                time = 0;
                seNo = HuAudFXPlay(1195);
                work->mode = 11;
                break;
            case 11:
                t11 = time / 60.0f;
                if (num != 0) {
                    tpLvl11 = sin(M_PI * t11);
                } else {
                    tpLvl11 = sin(M_PI * t11 / 2.0);
                    time++;
                }
                for (i = 4; i--;) {
                    if (recNo[i] >= 0 && rank[i] != recNo[i]) {
                        mdlId = lbl_1_bss_177A0.mdlId[i + 12];
                        rec11 = &lbl_1_data_920[recNo[i]];
                        vec11 = &rec11->key[vecNo[i]];
                        t11 = frame[i] / vec11->time;
                        if (vecNo[i] == 0) {
                            pos11.x = pos2D[i].x;
                            pos11.y = pos2D[i].y;
                            pos11.z = 1000.0f;
                            Hu3D2Dto3D(&pos11, HU3D_CAM2, &from11);
                        } else {
                            pos11.x = rec11->key[vecNo[i] - 1].pos.x;
                            pos11.y = rec11->key[vecNo[i] - 1].pos.y;
                            pos11.z = 1000.0f;
                            Hu3D2Dto3D(&pos11, HU3D_CAM2, &from11);
                        }
                        pos11.x = vec11->pos.x;
                        pos11.y = vec11->pos.y;
                        pos11.z = 1000.0f;
                        Hu3D2Dto3D(&pos11, HU3D_CAM2, &to11);
                        PSVECSubtract(&to11, &from11, &to11);
                        PSVECScale(&to11, &to11, t11);
                        PSVECAdd(&to11, &from11, &pos11);
                        Hu3DModelPosSetV(mdlId, &pos11);
                        frame[i]++;
                        if (vec11->time <= frame[i]) {
                            if (recNo[i] == 8 && vecNo[i] == 1) {
                                if (seNo >= 0) {
                                    HuAudFXStop(seNo);
                                    seNo = -1;
                                }
                                padNo = GwPlayerConf[fn_1_938(fn_1_96C() == 0)].padNo;
                                omVibrate(padNo, 20, 4, 2);
                                HuAudFXPlay(1196);
                            }
                            frame[i] = 0;
                            vecNo[i]++;
                            if (rec11->num == vecNo[i]) {
                                pos2D[i] = rec11->key[vecNo[i] - 1].pos;
                                recNo[i] = -1;
                            }
                        }
                    }
                }
                for (i = sprNum; i--;) {
                    HuSprTPLvlSet(work->unk0, sprNo[i], tpLvl11);
                }
                time++;
                if (time % 60 == 0) {
                    if (num == 0) {
                        work->mode = 1;
                    }
                    if (seNo >= 0) {
                        HuAudFXStop(seNo);
                        seNo = -1;
                    }
                    num--;
                    time = 0;
                }
                break;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 178 insns */
void fn_1_F708(void)
{
    HuVecF pos;
    float angle[4];
    HuVec2f pos2D;
    float ofs;
    float s;
    s32 i;
    s32 mdlId;

    for (i = 4; i--;) {
        angle[i] = frandmod(360);
    }
    while (fn_1_7E4(0x40000000)) {
        for (i = 4; i--;) {
            s = HuSin(angle[i]);
            ofs = 10.0f * s;
            pos2D.x = ((HuVec2f *)lbl_1_data_B98)[i].x;
            pos2D.y = ofs + ((HuVec2f *)lbl_1_data_B98)[i].y;
            pos.x = pos2D.x;
            pos.y = pos2D.y;
            pos.z = 1000.0f;
            Hu3D2Dto3D(&pos, HU3D_CAM4, &pos);
            mdlId = lbl_1_bss_177A0.mdlId[lbl_1_bss_177A0.unk14[i] + 12];
            Hu3DModelPosSetV(mdlId, &pos);
            HuSprPosSet(lbl_1_bss_177A0.grp10, i + 2, ((HuVec2f *)lbl_1_data_B58)[i].x, ofs + ((HuVec2f *)lbl_1_data_B58)[i].y);
            HuSprPosSet(lbl_1_bss_177A0.grp10, i + 6, ((HuVec2f *)lbl_1_data_B78)[i].x, ofs + ((HuVec2f *)lbl_1_data_B78)[i].y);
            if (i == 0) {
                HuSprPosSet(lbl_1_bss_177A0.grp10, 10, lbl_1_data_BB8.x, lbl_1_data_BB8.y + ofs);
            }
            angle[i] += 2.0f;
            if (angle[i] >= 360.0f) {
                angle[i] -= 360.0f;
            }
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 128 insns */
void fn_1_F9D0(void)
{
    float scale;
    s32 time;
    s32 mode;
    BOOL loop;

    loop = TRUE;
    mode = 0;
    while (loop) {
        switch (mode) {
            case 0:
                time = 10;
                mode = 1;
                break;
            case 1:
                scale = 1.0f - time / 10.0f;
                scale = sin(M_PI * scale / 2.0);
                scale *= 0.2f;
                scale += 1.0f;
                Hu3DModelScaleSet(lbl_1_bss_177A0.mdlId[4], scale, scale, scale);
                time--;
                if (time == 0) {
                    mode = 2;
                    time = 30;
                }
                break;
            case 2:
                scale = time / 30.0f;
                scale = sin(M_PI * scale / 2.0);
                scale *= 0.2f;
                scale += 1.0f;
                Hu3DModelScaleSet(lbl_1_bss_177A0.mdlId[4], scale, scale, scale);
                time--;
                if (time == 0) {
                    loop = FALSE;
                }
                break;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

