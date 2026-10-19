/*
 * mgmatchDll mgmatch.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgmatchDll/asm/REL/mgmatchDll/mgmatch.s.
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
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 24.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 500.0f; /* 0x14 */
static const float lbl_1_rodata_18 = 9.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 1.0f; /* 0x1C */
/* 0x20 lbl_1_rodata_20 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_28 = 140.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 10.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 0.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 15.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 100.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 60.0f; /* 0x3C */
/* 0x40 lbl_1_rodata_40 = 4503599627370496: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_48 = 3.141592653589793; /* 0x48 */
static const double lbl_1_rodata_50 = 0.5; /* 0x50 */
static const float lbl_1_rodata_58 = 3.8f; /* 0x58 */
static const float lbl_1_rodata_5C = 3.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 4.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 0.06f; /* 0x64 */
static const double lbl_1_rodata_68 = 360.0; /* 0x68 */
static const float lbl_1_rodata_70 = -30.0f; /* 0x70 */
static const double lbl_1_rodata_78 = 2.0; /* 0x78 */
static const double lbl_1_rodata_80 = 150.0; /* 0x80 */
static const float lbl_1_rodata_88 = 300.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 120.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 0.5833333f; /* 0x90 */
static const float lbl_1_rodata_94 = 20.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 900.0f; /* 0x98 */
static const double lbl_1_rodata_A0 = 20.0; /* 0xA0 */
static const float lbl_1_rodata_A8 = 0.3f; /* 0xA8 */
static const double lbl_1_rodata_B0 = 15.0; /* 0xB0 */
static const float lbl_1_rodata_B8 = 2.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 1.5f; /* 0xBC */
static const float lbl_1_rodata_C0 = 180.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 290.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 22.5f; /* 0xC8 */
static const float lbl_1_rodata_CC = 5.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 45.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 40.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 0.5f; /* 0xD8 */
static const float lbl_1_rodata_DC = 240.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = 30.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 288.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 1200.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = -1.0f; /* 0xEC */
static const double lbl_1_rodata_F0 = 50.0; /* 0xF0 */
static const double lbl_1_rodata_F8 = 180.0; /* 0xF8 */
static const float lbl_1_rodata_100 = 6.0f; /* 0x100 */
static const float lbl_1_rodata_104 = 0.01f; /* 0x104 */
/* 0x108 lbl_1_rodata_108 (0xC): 0x00000000 0x45FA0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x114 lbl_1_rodata_114 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x120 lbl_1_rodata_120 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12C lbl_1_rodata_12C (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x138 lbl_1_rodata_138 (0xC): 0x00000000 0x42480000 0x442F0000 -- an aggregate initialiser, write it as a local */
/* 0x144 lbl_1_rodata_144 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_150 = 60000.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 1.2f; /* 0x154 */
static const float lbl_1_rodata_158 = 640.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 480.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 1000.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 150.0f; /* 0x164 */
static const float lbl_1_rodata_168 = 8000.0f; /* 0x168 */
static const float lbl_1_rodata_16C = -10000.0f; /* 0x16C */
static const float lbl_1_rodata_170 = 360.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 0.2f; /* 0x174 */
static const double lbl_1_rodata_178 = 40.0; /* 0x178 */
/* 0x180 lbl_1_rodata_180 (0xC): 0x00000000 0x42480000 0x442F0000 -- an aggregate initialiser, write it as a local */
/* 0x18C lbl_1_rodata_18C (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_198 = -90.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 350.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 250.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = -200.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = -300.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 1900.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = 600.0f; /* 0x1B0 */
static const double lbl_1_rodata_1B8 = 0.01; /* 0x1B8 */
static const float lbl_1_rodata_1C0 = 0.1f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = 28.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = -28.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = 5.6666665f; /* 0x1CC */
static const float lbl_1_rodata_1D0 = 8400.0f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 280.0f; /* 0x1D4 */
static const float lbl_1_rodata_1D8 = 2100.0f; /* 0x1D8 */
static const float lbl_1_rodata_1DC = 1600.0f; /* 0x1DC */
static const float lbl_1_rodata_1E0 = -500.0f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = 800.0f; /* 0x1E4 */
static const double lbl_1_rodata_1E8 = 1900.0; /* 0x1E8 */
static const float lbl_1_rodata_1F0 = 220.0f; /* 0x1F0 */
static const float lbl_1_rodata_1F4 = 700.0f; /* 0x1F4 */
static const float lbl_1_rodata_1F8 = 64.0f; /* 0x1F8 */
static const float lbl_1_rodata_1FC = -2.0f; /* 0x1FC */
static const float lbl_1_rodata_200 = 0.03f; /* 0x200 */
static const float lbl_1_rodata_204 = -5.0f; /* 0x204 */
static const float lbl_1_rodata_208 = 1.6f; /* 0x208 */
static const float lbl_1_rodata_20C = -3.0f; /* 0x20C */
static const float lbl_1_rodata_210 = 9000.0f; /* 0x210 */
static const float lbl_1_rodata_214 = 18000.0f; /* 0x214 */
static const float lbl_1_rodata_218 = 5000.0f; /* 0x218 */
static const float lbl_1_rodata_21C = 14000.0f; /* 0x21C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x8 */ MGMATCH_WORK lbl_1_bss_8; /* reached through lbl_1_bss_0 */
/* 0x4 */ MGMATCH_MODEWORK *lbl_1_bss_4; /* = (MGMATCH_MODEWORK *)mgModeWork (fn_1_85C4) */
/* 0x0 */ MGMATCH_WORK *lbl_1_bss_0; /* = &lbl_1_bss_8 (fn_1_85C4) */

/* --- functions (reference order), .data placed before its first user --- */
/* 40 insns */
void fn_1_A0(s8 *a, s8 *b, s8 num)
{
    int i, j;
    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            if (a[i] > a[j]) {
                s8 temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                if (b) {
                    s8 temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }
    }
}

/* 49 insns */
void fn_1_140(s8 *arr, s32 num)
{
    s8 usednum[256];
    int i, j;
    int no;
    for (i = num; i--;) {
        usednum[i] = arr[i];
    }
    for (i = num; i--;) {
        if (i) {
            no = frandmod(i + 1);
        }
        else {
            no = 0;
        }
        arr[i] = usednum[no];
        for (j = 0; j <= i; j++) {
            if (j != no && j > no) {
                usednum[j - 1] = usednum[j];
            }
        }
    }
}

/* 15 insns */
void fn_1_204(s32 time)
{
    while (time--) {
        HuPrcVSleep();
    }
}

/* 21 insns */
void fn_1_240(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_IN, type, time);
    WipeWait();
}

/* 21 insns */
void fn_1_294(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_OUT, type, time);
    WipeWait();
}

/* 0x0 */ unsigned int lbl_1_data_0[12] = { /* character motion DATANUMs for CharModelMotListCreate (0-terminated) */ 0x8C0000, 0x8C0001, 0x8C0002, 0x8C0032, 0x8C0031, 0x8C0003, 0x8C0004, 0x8C0017, 0x8C0018, 0x8C005A, 0x8C0052, 0x0 };
/* 0x30 */ HuVecF lbl_1_data_30[4] = { { -160.0f, 0.0f, 140.0f }, { 0.0f, 0.0f, 140.0f }, { 160.0f, 0.0f, 140.0f }, { 320.0f, 0.0f, 140.0f } };
/* 0x60 */ HuVecF lbl_1_data_60[4] = { { 0.0f, 120.0f, 0.0f }, { -280.0f, 120.0f, 260.0f }, { -800.0f, 120.0f, 260.0f }, { -280.0f, 120.0f, 50.0f } };
/* 0x90 */ float lbl_1_data_90[6] = { 0.0f, -630.0f, -550.0f, 0.0f, 580.0f, -550.0f };
/* 0xA8 */ HuVecF lbl_1_data_A8 = { 0.0f, 385.0f, 140.0f }; /* struct-copied (lwz only) */
/* 0xB4 */ float lbl_1_data_B4[3] = { 0.0f, 250.0f, 140.0f };
/* 0xC0 */ MGMATCH_MG lbl_1_data_C0[43] = { /* [0..20] 4P, [21..31] 2vs2, [32..42] 1vs3; mgIdx/battleF filled by fn_1_85C4 (the 2 bytes after it are alignment) */ { 15, 501, 0, 0 }, { 16, 502, 0, 0 }, { 17, 503, 0, 0 }, { 18, 504, 0, 0 }, { 19, 505, 0, 0 }, { 20, 506, 0, 0 }, { 21, 507, 0, 0 }, { 22, 508, 0, 0 }, { 23, 509, 0, 0 }, { 24, 510, 0, 0 }, { 25, 511, 0, 0 }, { 26, 512, 0, 0 }, { 27, 513, 0, 0 }, { 28, 514, 0, 0 }, { 29, 515, 0, 0 }, { 74, 563, 0, 0 }, { 75, 564, 0, 0 }, { 76, 565, 0, 0 }, { 77, 566, 0, 0 }, { 87, 576, 0, 0 }, { 89, 579, 0, 0 }, { 35, 521, 0, 0 }, { 40, 526, 0, 0 }, { 41, 527, 0, 0 }, { 42, 528, 0, 0 }, { 43, 529, 0, 0 }, { 44, 530, 0, 0 }, { 45, 531, 0, 0 }, { 46, 532, 0, 0 }, { 47, 533, 0, 0 }, { 48, 534, 0, 0 }, { 85, 574, 0, 0 }, { 31, 517, 0, 0 }, { 32, 518, 0, 0 }, { 33, 519, 0, 0 }, { 34, 520, 0, 0 }, { 36, 522, 0, 0 }, { 37, 523, 0, 0 }, { 39, 525, 0, 0 }, { 78, 567, 0, 0 }, { 79, 568, 0, 0 }, { 81, 570, 0, 0 }, { 88, 577, 0, 0 } };
/* 0x1C4 */ float lbl_1_data_1C4[3] = { -9000.0f, 32387.902f, 5000.0f };
/* 0x1D0 */ float lbl_1_data_1D0[9] = { 0.1f, 0.24f, 0.32f, 0.48f, 0.56f, 0.72f, 0.84f, 0.9f, 1.0f };
/* 0x1F4 */ float lbl_1_data_1F4[9] = { 0.6f, 0.65f, 0.4f, 0.2f, 0.3f, 0.5f, 0.7f, 0.8f, 1.1f };
/* 0x218 */ GXColor lbl_1_data_218[4] = { { 128, 128, 128, 255 }, { 64, 64, 64, 255 }, { 0, 0, 0, 0 }, { 64, 64, 64, 128 } }; /* copied bytewise into lbl_1_data_228 colours (fn_1_85C4) */
/* 0x228 */ HU3DPARMANPARAM lbl_1_data_228 = { 40, 0, 0.3f, 30.0f, 10.0f, { 0.0f, -0.2f, 0.0f }, 2.0f, 1.0f, 40.0f, 0.98f, 2, { { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } }; /* = mgtour lbl_1_data_1F8 */
/* 0x278 */ HuVecF lbl_1_data_278[14] = { { 184.0f, 0.0f, 180.0f }, { 210.0f, 130.0f, 0.0f }, { 0.0f, 180.0f, 230.0f }, { 0.0f, 0.0f, 0.0f }, { -199.0f, 0.0f, -220.0f }, { 0.0f, -170.0f, 0.0f }, { -120.0f, -200.0f, -166.0f }, { 400.0f, 0.0f, 400.0f }, { 400.0f, 400.0f, 0.0f }, { 0.0f, 400.0f, 400.0f }, { 0.0f, 0.0f, 0.0f }, { -400.0f, 0.0f, -400.0f }, { -400.0f, -400.0f, 0.0f }, { 0.0f, -400.0f, -400.0f } };
/* 0x320 */ HuVecF lbl_1_data_320[2] = { { 800.0f, 200.0f, 1000.0f }, { 9450.365234375f, 14472.1240234375f, 4303.53076171875f } }; /* struct-copied (lwz only) */
/* 0x338 */ HuVecF lbl_1_data_338[2] = { { -7.0f, 3.0f, -10.0f }, { -30.0f, -20.0f, -10.0f } };
/* 0x350 */ float lbl_1_data_350[16] = { 2000.0f, 200.0f, 1000.0f, 0.0f, 1300.0f, 280.0f, -2000.0f, 400.0f, -500.0f, 1000.0f, -7000.0f, 800.0f, -8000.0f, 3000.0f, -8000.0f, 1200.0f };
/* 0x390 */ HuVecF lbl_1_data_390 = { -280.0f, 120.0f, 600.0f };
/* 0x39C */ HuVecF lbl_1_data_39C = { 1.0f, 580.0f, -2000.0f };
/* 0x3A8 */ HuVecF lbl_1_data_3A8[5] = { { -160.0f, 270.0f, 350.0f }, { 160.0f, 270.0f, 350.0f }, { -210.0f, 270.0f, 350.0f }, { 0.0f, 270.0f, 350.0f }, { 210.0f, 270.0f, 350.0f } };
/* 0x3E4 */ float lbl_1_data_3E4[13] = { 100.0f, 110.0f, 140.0f, 140.0f, 115.0f, 130.0f, 100.0f, 105.0f, 100.0f, 110.0f, 110.0f, 110.0f, 110.0f };
/* 0x418 */ s32 lbl_1_data_418[10][4] = { /* per character: voice SE ids, fn_1_974 [charNo][seNo] */ { 0x1F8, 0x200, 0x1FA, 0x1F9 }, { 0x1E4, 0x1EC, 0x1E6, 0x1E5 }, { 0x25C, 0x264, 0x25E, 0x25D }, { 0x2AC, 0x2B4, 0x2AE, 0x2AD }, { 0x284, 0x28C, 0x286, 0x285 }, { 0x1BC, 0x1C4, 0x1BE, 0x1BD }, { 0x298, 0x2A0, 0x29A, 0x299 }, { 0x1D0, 0x1D8, 0x1D2, 0x1D1 }, { 0x270, 0x278, 0x272, 0x271 }, { 0x234, 0x23C, 0x236, 0x235 } };

/* 55 insns */
void fn_1_2E8(void)
{
    u32 tick;
    int statId;
    lbl_1_bss_0->dirRead = FALSE;
    tick = OSGetTick();
    statId = HuDataDirReadAsync(mgDataTbl[lbl_1_bss_0->mgNoDir].dataDir);
    while (!HuDataGetAsyncStat(statId)) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->dirRead = TRUE;
    OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick() - tick));
    OSReport("Finished!\n");
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

/* 37 insns */
void fn_1_3C4(s32 mgNoDir)
{
    lbl_1_bss_0->mgNoDir = mgNoDir;
    HuDataDirClose(DATA_mgmatch);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    if (!fn_1_8B4(4)) {
        HuPrcChildCreate(fn_1_2E8, 200, 0x3000, 0, HuPrcCurrentGet());
    }
    else {
        lbl_1_bss_0->dirRead = TRUE;
    }
}

/* 5 insns */
HUWINID fn_1_458(void)
{
    return lbl_1_bss_0->winId;
}

/* 18 insns */
void fn_1_46C(void)
{
    if (!fn_1_8B4(0x20)) {
        fn_1_87C(0x20);
        HuWinExOpen(lbl_1_bss_0->winId);
    }
}

/* 23 insns */
void fn_1_4B4(void)
{
    if (fn_1_8B4(0x20)) {
        fn_1_898(0x20);
        HuWinExClose(lbl_1_bss_0->winId);
        HuWinHomeClear(lbl_1_bss_0->winId);
    }
}

/* 6 insns */
s32 fn_1_510(void)
{
    return lbl_1_bss_4->winsNeeded;
}

/* 24 insns */
u32 fn_1_528(void)
{
    return mgDataTbl[lbl_1_bss_4->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgIdx].nameMes;
}

/* 5 insns */
s8 fn_1_588(void)
{
    return lbl_1_bss_0->winner;
}

/* 5 insns */
s8 fn_1_59C(void)
{
    return lbl_1_bss_4->gameType;
}

/* 8 insns */
s8 fn_1_5B0(s32 i)
{
    return lbl_1_bss_0->player[i].no;
}

/* 21 insns */
void fn_1_5D0(s32 i, s32 time)
{
    omVibrate(lbl_1_bss_0->player[i].padNo, time, 4, 2);
}

/* 5 insns */
s8 fn_1_624(void)
{
    return lbl_1_bss_4->winner;
}

/* 5 insns */
s32 fn_1_638(void)
{
    return lbl_1_bss_0->charNo;
}

/* 140 insns */
BOOL fn_1_64C(s32 *place, s32 *num, s32 *no)
{
    int i, j;
    int tieNum;
    int tieNo;
    s8 winner;
    if (lbl_1_bss_4->gameType != MGMATCH_GAMETYPE_4P) {
        return FALSE;
    }
    tieNum = 0;
    for (i = 0; i < lbl_1_bss_4->num; i++) {
        for (j = i + 1; j < lbl_1_bss_4->num; j++) {
            if (lbl_1_bss_4->score[i] == lbl_1_bss_4->score[j]) {
                tieNo = i;
                tieNum++;
            }
        }
    }
    if (tieNum == 0) {
        return FALSE;
    }
    if (num == 0 || place == 0) {
        return TRUE;
    }
    *num = tieNum;
    if (*num == 1) {
        (*num)++;
        *place = 1;
        for (i = 0; i < lbl_1_bss_4->num; i++) {
            if (tieNo != i && lbl_1_bss_4->score[tieNo] < lbl_1_bss_4->score[i]) {
                (*place)++;
            }
        }
        if (no != 0) {
            *no = lbl_1_bss_4->score[tieNo];
        }
    }
    else {
        *place = 2;
        if (no != 0) {
            winner = lbl_1_bss_4->winner;
            if (winner == 0) {
                *no = lbl_1_bss_4->score[1];
            }
            else {
                *no = lbl_1_bss_4->score[0];
            }
        }
    }
    return TRUE;
}

/* 7 insns */
void fn_1_87C(u32 flag)
{
    lbl_1_bss_0->flag |= flag;
}

/* 7 insns */
void fn_1_898(u32 flag)
{
    lbl_1_bss_0->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_8B4(u32 flag)
{
    return lbl_1_bss_0->flag & flag;
}

/* 8 insns */
void fn_1_8CC(u32 flag)
{
    lbl_1_bss_4->flag |= flag;
}

/* 8 insns */
void fn_1_8EC(u32 flag)
{
    lbl_1_bss_4->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_90C(u32 flag)
{
    return lbl_1_bss_4->flag & flag;
}

/* 7 insns */
void fn_1_924(u32 flag)
{
    lbl_1_bss_0->mesFlag |= flag;
}

/* 7 insns */
void fn_1_940(u32 flag)
{
    lbl_1_bss_0->mesFlag &= ~flag;
}

/* 6 insns */
u32 fn_1_95C(u32 flag)
{
    return lbl_1_bss_0->mesFlag & flag;
}

/* 34 insns */
void fn_1_974(MGMATCH_PLAYER *player, s32 seNo)
{
    HuAudFXPlayPan(lbl_1_data_418[player->charNo][seNo], (int)(24 * (player->pos.x / 500)) + 64);
}

/* 71 insns */
void fn_1_9FC(void)
{
    s32 key[4];
    int i;
    HuWinDisablePlayerSet(lbl_1_bss_0->winId, 15);
    while (!fn_1_95C(lbl_1_bss_0->waitMesFlag)) {
        for (i = 4; i--;) {
            key[i] = -1;
            if (GwPlayerConf[i].type != GW_TYPE_MAN) {
                key[i] = PAD_BUTTON_A;
            }
        }
        HuWinComKeyWait(key[0], key[1], key[2], key[3], 10);
        fn_1_204(30);
    }
    HuWinDisablePlayerReset(lbl_1_bss_0->winId, 15);
    HuWinComKeyReset();
    HuPrcEnd();
}

/* 21 insns */
void fn_1_B18(u32 mesFlag)
{
    lbl_1_bss_0->waitMesFlag = mesFlag;
    HuPrcChildCreate(fn_1_9FC, 200, 0x3000, 0, HuPrcCurrentGet());
}

/* 21 insns */
void ObjectSetup(void)
{
    GwSystem.subGameNo = 0;
    _SetFlag(FLAG_MGINST_ON);
    HuPrcChildCreate(fn_1_BC0, 200, 0x3000, 0, HuPrcCurrentGet());
}

/* 96 insns */
void fn_1_BC0(void)
{
    BOOL mgF;
    BOOL runF;
    OMOVLHIS *his;
    his = omOvlHisGet(0);
    fn_1_85C4();
    runF = TRUE;
    while (runF) {
        mgF = TRUE;
        switch (his->evtno) {
            case 0:
                fn_1_9984();
                runF = TRUE;
                break;

            case 1:
                fn_1_A524();
                if (!fn_1_8B4(8)) {
                    fn_1_B2D8();
                    if (lbl_1_bss_4->winner >= 0) {
                        fn_1_87C(0x200);
                    }
                    if (fn_1_8B4(0x200)) {
                        fn_1_BE50();
                    }
                }
                if (fn_1_90C(2)) {
                    mgF = FALSE;
                }
                break;

            case 2:
                fn_1_112B8();
                mgF = FALSE;
                break;

            case 3:
                if (fn_1_8B4(2)) {
                    fn_1_11F2C();
                }
                mgF = FALSE;
                runF = FALSE;
                break;
        }
        if (mgF) {
            fn_1_C638();
        }
    }
    fn_1_9844();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

/* 18 insns */
void fn_1_D40(s32 evtno)
{
    OMOVLHIS *his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, evtno, his->stat);
}

/* 807 insns */
void fn_1_D88(void)
{
    s32 i;
    s32 mdlId;
    lbl_1_bss_0->mdlId[0] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x09));
    lbl_1_bss_0->mdlId[1] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0A));
    lbl_1_bss_0->mdlId[3] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0D));
    lbl_1_bss_0->mdlId[2] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x08));
    lbl_1_bss_0->mdlId[4] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0B));
    lbl_1_bss_0->mdlId[5] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0C));
    lbl_1_bss_0->mdlId[7] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0F));
    lbl_1_bss_0->mdlId[8] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0F));
    lbl_1_bss_0->mdlId[37] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x13));
    lbl_1_bss_0->mdlId[54] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x19));
    lbl_1_bss_0->mdlId[38] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x14));
    lbl_1_bss_0->mdlId[39] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x15));
    lbl_1_bss_0->mdlId[40] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x15));
    lbl_1_bss_0->mdlId[41] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x14));
    lbl_1_bss_0->mdlId[42] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x15));
    lbl_1_bss_0->mdlId[43] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x14));
    lbl_1_bss_0->mdlId[44] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x15));
    lbl_1_bss_0->mdlId[45] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x14));
    lbl_1_bss_0->mdlId[46] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x15));
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[0], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[1], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[3], 3);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[2], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[4], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[5], 3);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[7], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[8], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[37], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[54], 5);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[8], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[37], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[54], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[0], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[1], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[3], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[2], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[4], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[5], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[7], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[8], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[37], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_0->mdlId[54], HU3D_CAM4);
    for (i = 9; i--;) {
        Hu3DModelLayerSet(lbl_1_bss_0->mdlId[38 + i], 0);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[38 + i], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_0->mdlId[38 + i], HU3D_CAM4);
    }
    for (i = 3; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x1A));
        lbl_1_bss_0->mdlId[55 + i] = mdlId;
        Hu3DModelLayerSet(mdlId, 5);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    lbl_1_bss_0->mdlId[58] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x1B));
    lbl_1_bss_0->mdlId[59] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x1C));
    lbl_1_bss_0->mdlId[60] = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x1D));
    for (i = 3; i--;) {
        mdlId = lbl_1_bss_0->mdlId[58 + i];
        Hu3DModelLayerSet(mdlId, 5);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    for (i = 7; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x10));
        lbl_1_bss_0->mdlId[9 + i] = mdlId;
        lbl_1_bss_0->winMdl[i].mdlId = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    for (i = 10; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x11));
        lbl_1_bss_0->mdlId[16 + i] = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x0E));
    lbl_1_bss_0->unk118 = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DReflectNoSet(2);
    Hu3DModelReflectTypeSet(mdlId, -1);
    Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    for (i = 7; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x02));
        lbl_1_bss_0->effMdl[i].mdlId = mdlId;
        lbl_1_bss_0->mdlId[47 + i] = mdlId;
        lbl_1_bss_0->effMdl[i].unk2A = Hu3DJointMotionData(mdlId, DATANUM(DATA_mgmatch, 0x04));
        lbl_1_bss_0->effMdl[i].unk2C = Hu3DJointMotionData(mdlId, DATANUM(DATA_mgmatch, 0x07));
        Hu3DMotionSet(mdlId, lbl_1_bss_0->effMdl[i].unk2A);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    for (i = 4; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x17));
        lbl_1_bss_0->mdlId[30 + i] = mdlId;
        Hu3DModelLayerSet(mdlId, 5);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    for (i = 3; i--;) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgmatch, 0x12));
        lbl_1_bss_0->mdlId[34 + i] = mdlId;
        Hu3DModelLayerSet(mdlId, 5);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
    }
    lbl_1_bss_0->mdlId[61] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgmatch, 0x1E)), HU3D_CAM4);
    lbl_1_bss_0->mdlId[62] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgmatch, 0x1F)), HU3D_CAM4);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[61], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[62], HU3D_MOTATTR_PAUSE);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[61]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[62]);
}

/* 16 insns */
void fn_1_1A24(void (*func)(void))
{
    HuPrcChildCreate(func, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 105 insns */
s32 fn_1_1A64(s32 cameraMot, s32 time, s32 arg)
{
    HSFMOTION *motion;
    HU3DMODEL *modelP;
    HU3DMOTION *motP;
    HSFDATA *hsf;
    if (lbl_1_bss_0->cameraMot == cameraMot) {
        return 0;
    }
    lbl_1_bss_0->cameraMotNext = cameraMot;
    if (time != 0) {
        CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM4, time, arg);
    }
    else {
        modelP = &Hu3DData[lbl_1_bss_0->mdlId[cameraMot]];
        motP = &Hu3DMotion[modelP->motId];
        hsf = motP->hsf;
        motion = hsf->motion;
        if (motion->maxTime < 9.0f) {
            CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM4, motion->maxTime, arg);
        }
        else {
            CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM4, 1.0f, arg);
        }
    }
    lbl_1_bss_0->cameraMotNext = -1;
    lbl_1_bss_0->cameraMot = cameraMot;
    return 1;
}

/* 120 insns */
void fn_1_1C08(void)
{
    fn_1_1A64(lbl_1_bss_0->cameraMotNext, lbl_1_bss_0->cameraMotTime, lbl_1_bss_0->cameraMotArg);
    lbl_1_bss_0->cameraMotNext = -1;
    HuPrcEnd();
}

/* 35 insns */
void fn_1_1DE8(s16 cameraMot, float time, s32 arg)
{
    lbl_1_bss_0->cameraMotNext = cameraMot;
    lbl_1_bss_0->cameraMotTime = time;
    lbl_1_bss_0->cameraMotArg = arg;
    HuPrcChildCreate(fn_1_1C08, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 11 insns */
BOOL fn_1_1E74(void)
{
    return lbl_1_bss_0->cameraMotNext == -1;
}

/* 24 insns */
void fn_1_1EA0(void)
{
    CamMotionExPath(HU3D_CAM4, lbl_1_bss_0->camMot, lbl_1_bss_0->camMotNum);
    fn_1_87C(0x100);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_1F00(void)
{
    fn_1_898(0x100);
    fn_1_1A24(fn_1_1EA0);
}

/* 42 insns */
void fn_1_1F58(void)
{
    CAMMOTIONWORK *last = &lbl_1_bss_0->camMot[lbl_1_bss_0->camMotNum - 1];
    CamMotionExPath(HU3D_CAM4, lbl_1_bss_0->camMot, lbl_1_bss_0->camMotNum);
    Hu3DCameraPosSetV(HU3D_CAM4, &last->pos, &last->up, &last->target);
    fn_1_87C(0x100);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_2000(void)
{
    fn_1_898(0x100);
    fn_1_1A24(fn_1_1F58);
}

/* 10 insns */
void fn_1_2058(void)
{
    HuAudJinglePlay(MSM_STREAM_JNGL_SDBATTLE_START);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_2080(void)
{
    HuPrcChildCreate(fn_1_2058, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 30 insns */
void fn_1_20BC(void)
{
    HuAudJinglePlay(MSM_STREAM_JNGL_MGWARS_MG_WIN);
    fn_1_204(210);
    if (lbl_1_bss_0->streamNo < 0) {
        lbl_1_bss_0->streamNo = HuAudBGMPlay(35);
    }
    HuPrcEnd();
}

/* 15 insns */
void fn_1_2134(void)
{
    HuPrcChildCreate(fn_1_20BC, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 302 insns */
void fn_1_2170(void)
{
    float posY[4];
    s32 mode[4];
    s32 wait[4];
    float speed;
    float fallSpeed;
    s32 seF;
    s32 i;
    s32 doneNum;
    MGMATCH_PLAYER *player;
    speed = 140.0f;
    seF = 0;
    fallSpeed = 10.0f * speed;
    for (i = 4; i--;) {
        posY[i] = frandmod(1000) + 7500;
        mode[i] = 0;
        player = &lbl_1_bss_0->player[i];
        player->rot = 0.0f;
        player->rotEnd = 0.0f;
        Hu3DModelPosSet(player->mdlId, player->pos.x, posY[i], player->pos.z);
        Hu3DModelDispOn(player->mdlId);
        if (player->mot != 5) {
            CharMotionShiftSet(player->charNo, player->motId[5], 0.0f, 15.0f, 0);
            player->mot = 5;
        }
    }
    while (1) {
        doneNum = 0;
        for (i = 4; i--;) {
            posY[i] -= fallSpeed / 100.0f;
            player = &lbl_1_bss_0->player[i];
            switch (mode[i]) {
                case 0:
                    if (posY[i] > player->pos.y) {
                        Hu3DModelPosSet(player->mdlId, player->pos.x, posY[i], player->pos.z);
                    }
                    else {
                        mode[i] = 1;
                        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
                        if (player->mot != 6) {
                            CharMotionShiftSet(player->charNo, player->motId[6], 0.0f, 15.0f, 0);
                            player->mot = 6;
                        }
                        Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                        omVibrate(player->no, 18, 4, 2);
                    }
                    break;
                case 1:
                    if (Hu3DMotionEndCheck(player->mdlId)) {
                        if (!seF) {
                            HuAudFXPlayPan(1279, 64);
                            seF = 1;
                        }
                        if (player->mot != 7) {
                            CharMotionShiftSet(player->charNo, player->motId[7], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                            player->mot = 7;
                        }
                        Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                        wait[i] = 0;
                        mode[i] = 2;
                    }
                    break;
                case 2:
                    wait[i]++;
                    if (wait[i] == 120) {
                        if (player->mot != 8) {
                            CharMotionShiftSet(player->charNo, player->motId[8], 0.0f, 15.0f, 0);
                            player->mot = 8;
                        }
                        Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                        mode[i] = 3;
                    }
                    break;
                case 3:
                    if (Hu3DMotionEndCheck(player->mdlId)) {
                        if (player->mot != 0) {
                            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                            player->mot = 0;
                        }
                        Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_PAUSE);
                        mode[i] = 4;
                    }
                    break;
                case 4:
                    doneNum++;
                    break;
            }
        }
        if (doneNum == 4) {
            break;
        }
        if (fallSpeed != 60.0f * speed) {
            fallSpeed += speed;
        }
        HuPrcVSleep();
    }
    fn_1_87C(0x40);
    HuPrcEnd();
}

/* 21 insns */
void fn_1_2628(void)
{
    fn_1_898(0x40);
    HuPrcChildCreate(fn_1_2170, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 144 insns */
void fn_1_267C(void)
{
    s32 i;
    float t;
    HuVecF dir;
    HuVecF ofs;
    for (i = 0;; i++) {
        if (lbl_1_bss_0->guidePosNo == i) {
            lbl_1_bss_0->guidePos = lbl_1_bss_0->guideEnd;
            Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
            break;
        }
        t = (float)i / lbl_1_bss_0->guidePosNo;
        t = sin(M_PI * t / 2);
        t = sin(M_PI * t / 2);
        PSVECSubtract(&lbl_1_bss_0->guideEnd, &lbl_1_bss_0->guideStart, &dir);
        PSVECScale(&dir, &ofs, t);
        PSVECAdd(&lbl_1_bss_0->guideStart, &ofs, &lbl_1_bss_0->guidePos);
        Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
        HuPrcVSleep();
    }
    fn_1_87C(0x80);
    HuPrcEnd();
}

/* 54 insns */
void fn_1_28BC(s32 posNo, s16 arg)
{
    lbl_1_bss_0->guideStart = lbl_1_bss_0->guidePos;
    lbl_1_bss_0->guideEnd = lbl_1_data_60[posNo];
    lbl_1_bss_0->guidePosNo = arg;
    fn_1_898(0x80);
    HuPrcChildCreate(fn_1_267C, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 377 insns */
void fn_1_2994(void)
{
    HuVecF start;
    HuVecF pos;
    s8 order[21];
    float t;
    float dist;
    int i;
    int time;
    int count;
    int cnt;
    BOOL dispOffF;
    time = -1;
    for (i = lbl_1_bss_4->mgNum; i--;) {
        order[i] = i;
    }
    fn_1_140(order, lbl_1_bss_4->mgNum);
    if (lbl_1_bss_0->animId >= 0) {
        Hu3DAnimKill(lbl_1_bss_0->animId);
    }
    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[0], lbl_1_bss_0->mdlId[8], "S3TC_mg_movie");
    while (1) {
        if (fn_1_8B4(0x800)) {
            fn_1_898(0x800);
            if (lbl_1_bss_4->mgNum >= 10) {
                time = frandmod(lbl_1_bss_4->mgNum) + 30;
            }
            else if (lbl_1_bss_4->mgNum >= 7) {
                time = frandmod(lbl_1_bss_4->mgNum) + 20;
            }
            else if (lbl_1_bss_4->mgNum >= 4) {
                time = frandmod(lbl_1_bss_4->mgNum) + 15;
            }
            else {
                time = frandmod(lbl_1_bss_4->mgNum) + 10;
            }
            cnt = 0;
        }
        if (time >= 0) {
            if (++cnt >= 3) {
                if (time == 0) {
                    Hu3DModelDispOn(lbl_1_bss_0->mdlId[7]);
                    Hu3DModelDispOff(lbl_1_bss_0->mdlId[8]);
                    HuAudFXPlay(1173);
                    fn_1_87C(0x1000);
                }
                else {
                    HuAudFXPlay(1172);
                    if (lbl_1_bss_0->animId >= 0) {
                        Hu3DAnimKill(lbl_1_bss_0->animId);
                    }
                    /* retail: the new animation id is not stored in animId */
                    Hu3DAnimCreate(lbl_1_bss_0->mgIcon[order[time % lbl_1_bss_4->mgNum]], lbl_1_bss_0->mdlId[8], "S3TC_mg_movie");
                    cnt = 0;
                }
                time--;
            }
        }
        switch (lbl_1_bss_0->movieMode) {
            case 0:
                break;
            case 1:
                Hu3DModelDispOn(lbl_1_bss_0->mdlId[8]);
                HuAudFXPlay(1174);
                dist = lbl_1_data_90[4] - lbl_1_data_90[1];
                start = *(HuVecF *)&lbl_1_data_90[0];
                dispOffF = FALSE;
                count = 0;
                lbl_1_bss_0->movieMode = 3;
                break;
            case 2:
                dist = lbl_1_data_90[1] - lbl_1_data_90[4];
                start = *(HuVecF *)&lbl_1_data_90[3];
                dispOffF = TRUE;
                count = 0;
                lbl_1_bss_0->movieMode = 3;
                break;
            case 3:
                t = count / 60.0f;
                t = sin(M_PI * t / 2);
                t = sin(M_PI * t / 2);
                pos = *(HuVecF *)&lbl_1_data_90[0];
                pos.y += dist * t;
                Hu3DModelPosSet(lbl_1_bss_0->mdlId[7], pos.x, pos.y, pos.z);
                Hu3DModelPosSet(lbl_1_bss_0->mdlId[8], pos.x, pos.y, pos.z);
                if (++count > 60) {
                    if (dispOffF) {
                        Hu3DModelDispOff(lbl_1_bss_0->mdlId[7]);
                        Hu3DModelDispOff(lbl_1_bss_0->mdlId[8]);
                    }
                    lbl_1_bss_0->movieMode = 0;
                }
                break;
        }
        HuPrcVSleep();
    }
}

/* 129 insns */
void fn_1_2F78(void)
{
    if (!fn_1_8B4(0x400)) {
        Hu3DModelDispOff(lbl_1_bss_0->mdlId[7]);
        Hu3DModelScaleSet(lbl_1_bss_0->mdlId[7], 3.8f, 3.8f, 3.0f);
        Hu3DModelRotSet(lbl_1_bss_0->mdlId[7], 10.0f, 0.0f, 0.0f);
        Hu3DModelPosSet(lbl_1_bss_0->mdlId[7], lbl_1_data_90[0], lbl_1_data_90[1], lbl_1_data_90[2]);
        Hu3DModelDispOff(lbl_1_bss_0->mdlId[8]);
        Hu3DModelScaleSet(lbl_1_bss_0->mdlId[8], 3.8f, 3.8f, 3.0f);
        Hu3DModelRotSet(lbl_1_bss_0->mdlId[8], 10.0f, 0.0f, 0.0f);
        Hu3DModelPosSet(lbl_1_bss_0->mdlId[8], lbl_1_data_90[0], lbl_1_data_90[1], lbl_1_data_90[2]);
        lbl_1_bss_0->movieMode = 0;
        fn_1_87C(0x400);
        HuPrcChildCreate(fn_1_2994, 100, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 13 insns */
void fn_1_317C(s32 arg)
{
    (void)arg; /* unused; referenced so CW keeps r3 for it (the reference uses r4 for the pointer) -- a guess */
    fn_1_87C(0x800);
    fn_1_898(0x1000);
}

/* 68 insns */
void fn_1_31B0(void)
{
    s32 mgIdx;
    char *path;
    mgIdx = lbl_1_bss_4->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgIdx;
    if (mgIdx + 501 == 519) {
        path = mgDataTbl[mgIdx].movie[lbl_1_bss_0->mgVariant];
    }
    else {
        path = mgDataTbl[mgIdx].movie[0];
    }
    HuTHPSprCreateVol(path, 1, 0, 0.0f);
    Hu3DModelMatHookSet(lbl_1_bss_0->mdlId[7], HuTHPMatHook);
    OSReport("Movie = %s\n", path);
}

/* 7 insns */
BOOL fn_1_32C0(void)
{
    return lbl_1_bss_0->movieMode == 0;
}

/* 52 insns */
void fn_1_32DC(s32 mode)
{
    if (fn_1_8B4(0x400)) {
        lbl_1_bss_0->movieMode = mode;
        while (lbl_1_bss_0->movieMode != 0) {
            HuPrcVSleep();
        }
        if (mode == 1) {
            fn_1_317C(mode);
            while (!fn_1_8B4(0x1000)) {
                HuPrcVSleep();
            }
        }
    }
}

/* 109 insns */
void fn_1_33AC(void)
{
    s8 last = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum - 1];
    lbl_1_bss_4->round = 0;
    fn_1_140(lbl_1_bss_4->mgOrder, lbl_1_bss_4->mgNum);
    if (lbl_1_bss_4->mgOrder[0] == last) {
        lbl_1_bss_4->mgOrder[0] = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2];
        lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2] = last;
    }
}

/* 188 insns */
void fn_1_3560(void)
{
    s32 i;
    MGMATCH_PLAYER *player;

    i = lbl_1_bss_4->num;
    while (i--) {
        lbl_1_bss_4->score[i] = 0;
    }
    lbl_1_bss_4->flag = 0;
    lbl_1_bss_4->round = 0;
    lbl_1_bss_4->winner = -1;
    fn_1_4B4();
    player = lbl_1_bss_0->player;
    lbl_1_bss_0->guidePos = lbl_1_data_60[0];
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_0->guideMdlId, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 4; i++, player++) {
        player->pos = lbl_1_data_30[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelAttrSet(player->mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
    }
    i = 4;
    while (i--) {
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[i + 30], HU3D_ATTR_DISPOFF);
    }
    fn_1_D40(0);
    HuTHPClose();
    HuPrcVSleep();
    while (HuTHPProcCheck()) {
        HuPrcVSleep();
    }
}

/* 160 insns */
void fn_1_3850(void)
{
    s32 idx[4];
    s32 num;
    s32 place;
    s32 no;
    MGMATCH_PLAYER *player;
    s32 i;
    s32 mode;
    s32 time;
    BOOL endF;

    mode = 0;
    endF = FALSE;
    while (!endF) {
        switch (mode) {
            case 0:
                fn_1_64C(&place, &num, &no);
                num = 0;
                i = lbl_1_bss_4->num;
                while (i--) {
                    if (lbl_1_bss_4->score[i] == no) {
                        idx[num] = i;
                        num++;
                    }
                }
                i = num;
                while (i--) {
                    player = &lbl_1_bss_0->player[idx[i]];
                    if (player->mot != 1) {
                        CharMotionShiftSet(player->charNo, player->motId[1], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                        player->mot = 1;
                    }
                }
                time = 20;
                mode = 1;
                break;
            case 1:
                i = num;
                while (i--) {
                    player = &lbl_1_bss_0->player[idx[i]];
                    player->pos.z += 4.0f;
                    Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
                }
                if (--time == 0) {
                    mode = 2;
                }
                break;
            case 2:
                i = num;
                while (i--) {
                    player = &lbl_1_bss_0->player[idx[i]];
                    if (player->mot != 0) {
                        CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                        player->mot = 0;
                    }
                }
                endF = TRUE;
                break;
        }
        HuPrcVSleep();
    }
    fn_1_87C(0x2000);
    HuPrcEnd();
}

/* 21 insns */
void fn_1_3AD0(void)
{
    fn_1_898(0x2000);
    HuPrcChildCreate(fn_1_3850, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 56 insns */
void fn_1_3B24(void)
{
    float rot = frandmod(36000) / 100.0f;
    Hu3DModelRotSet(lbl_1_bss_0->mdlId[2], 0.0f, rot, 0.0f);
    while (TRUE) {
        rot += 0.06f;
        rot = fmod(rot, 360.0);
        Hu3DModelRotSet(lbl_1_bss_0->mdlId[2], 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
}

/* 15 insns */
void fn_1_3C04(void)
{
    HuPrcChildCreate(fn_1_3B24, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 276 insns */
void fn_1_3C40(void)
{
    HuVecF pos;
    s32 i;
    int parManId;
    float t;
    float angle;

    i = 4;
    while (i--) {
        Hu3DParManAttrSet(lbl_1_bss_0->parManId[i], HU3D_PARMAN_ATTR_TIMEUP);
        lbl_1_bss_0->unkCA4[i] = -30.0f * i;
    }
    while (fn_1_8B4(0x10000)) {
        i = 4;
        while (i--) {
            parManId = lbl_1_bss_0->parManId[i];
            t = (float)lbl_1_bss_0->unkCA4[i] / lbl_1_bss_0->motTime;
            angle = 2.0 * (M_PI * (3.0f * t));
            pos.x = 150.0 * (t * cos(angle));
            pos.y = lbl_1_data_B4[1] + 300.0f * t;
            pos.z = 150.0 * (t * sin(angle));
            Hu3DParManPosSet(parManId, pos.x, pos.y, pos.z);
            if (lbl_1_bss_0->unkCA4[i] > 0) {
                lbl_1_bss_0->unkCA4[i] %= lbl_1_bss_0->motTime;
                if (lbl_1_bss_0->unkCA4[i] == 0) {
                    lbl_1_bss_0->unkCA4[i] = 10;
                }
            }
            else if (lbl_1_bss_0->unkCA4[i] == 0) {
                Hu3DParManAttrReset(lbl_1_bss_0->parManId[i], HU3D_PARMAN_ATTR_TIMEUP);
                lbl_1_bss_0->unkCA4[i] = 10;
            }
            lbl_1_bss_0->unkCA4[i]++;
        }
        HuPrcVSleep();
    }
    i = 4;
    while (i--) {
        Hu3DParManAttrSet(lbl_1_bss_0->parManId[i], HU3D_PARMAN_ATTR_TIMEUP);
    }
    Hu3DParManAttrReset(lbl_1_bss_0->parManId[0], HU3D_PARMAN_ATTR_TIMEUP);
    while (fn_1_8B4(0x80000)) {
        parManId = lbl_1_bss_0->parManId[0];
        pos = lbl_1_bss_0->unk134;
        Hu3DParManPosSet(parManId, pos.x, pos.y, pos.z);
        HuPrcVSleep();
    }
    Hu3DParManAttrSet(lbl_1_bss_0->parManId[0], HU3D_PARMAN_ATTR_TIMEUP);
    HuPrcEnd();
}

/* 33 insns */
void fn_1_4090(void)
{
    lbl_1_bss_0->motTime = Hu3DMotionMaxTimeGet(lbl_1_bss_0->mdlId[16]);
    fn_1_87C(0x90000);
    HuPrcChildCreate(fn_1_3C40, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 2279 insns */
void fn_1_4114(void)
{
    float rot[3];
    HuVecF dir;
    HuVecF target;
    HuVecF pos;
    HuVecF scale;
    HuVecF bobPos;
    HuVecF camPos;
    HuVecF camDir;
    s32 i;
    MGMATCH_PLAYER *player;
    s32 mode;
    s32 time;
    s32 mdlId;
    s32 grpId;
    s32 bobTime;
    s32 mdlNo;
    s32 moveTime;
    s32 j;
    s32 scaleTime;
    s32 count;
    BOOL bobF;
    s32 seNo2;
    s32 seNo;
    ANIMDATA *anim;
    float unused;
    float sprScale;
    float height;
    float bob;
    float t;
    float angle;
    float scaleAdd;
    float parTime;
    float tpLvl;
    float x;
    float y;
    float tpLvl2;
    float rotIn;
    float rotMod;
    float rotOut;

    bobF = FALSE;
    seNo2 = -1;
    mode = 0;
    scaleTime = 0;
    do {
        count = 0;
        i = lbl_1_bss_4->winsNeeded;
        while (i--) {
            switch (lbl_1_bss_0->winMdl[i].unk2) {
                case 0:
                    lbl_1_bss_0->winMdl[i].unk8 = 1.0f + (frandmod(140) / 120.0f - 0.5833333f);
                    lbl_1_bss_0->winMdl[i].unkC = 1.0f + (frandmod(140) / 120.0f - 0.5833333f);
                    lbl_1_bss_0->winMdl[i].unk2 = 1;
                    break;
                case 1:
                    target = lbl_1_data_A8;
                    target.y = (20.0f + target.y) - 20.0f * lbl_1_bss_0->winMdl[i].unkC;
                    PSVECSubtract(&target, &lbl_1_bss_0->winMdl[i].unk10, &dir);
                    if (PSVECSquareMag(&dir) < 900.0f) {
                        lbl_1_bss_0->winMdl[i].unk4 = 90;
                        lbl_1_bss_0->winMdl[i].unk2 = 2;
                    }
                    else {
                        PSVECNormalize(&dir, &dir);
                        PSVECScale(&dir, &dir, 4.0f);
                        PSVECAdd(&lbl_1_bss_0->winMdl[i].unk10, &dir, &lbl_1_bss_0->winMdl[i].unk10);
                        Hu3DModelPosSetV(lbl_1_bss_0->winMdl[i].mdlId, &lbl_1_bss_0->winMdl[i].unk10);
                    }
                    break;
                case 2:
                    angle = lbl_1_bss_0->winMdl[i].unk4 / 120.0f;
                    angle = 2.0 * (M_PI * angle);
                    x = lbl_1_bss_0->winMdl[i].unk8 * (20.0 * cos(angle));
                    y = lbl_1_bss_0->winMdl[i].unkC * (20.0 * sin(angle));
                    pos = lbl_1_bss_0->winMdl[i].unk10;
                    pos.x += x;
                    pos.y += y + 20.0f * lbl_1_bss_0->winMdl[i].unkC;
                    Hu3DModelPosSetV(lbl_1_bss_0->winMdl[i].mdlId, &pos);
                    lbl_1_bss_0->winMdl[i].unk4++;
                    lbl_1_bss_0->winMdl[i].unk4 %= 120;
                    count++;
                    break;
            }
            if (mode == 0) {
                scale = lbl_1_bss_0->winMdl[i].unk1C;
                scaleAdd = 0.3f * (scaleTime / 60.0f);
                scale.x += scaleAdd;
                scale.y += scaleAdd;
                scale.z += scaleAdd;
                Hu3DModelScaleSetV(lbl_1_bss_0->winMdl[i].mdlId, &scale);
            }
        }
        if (scaleTime < 60) {
            scaleTime++;
        }
        else if (mode == 0 && count == lbl_1_bss_4->winsNeeded) {
            mode = 1;
        }
        if (bobF) {
            bob = bobTime / 300.0f;
            bob = 2.0 * (M_PI * bob);
            bob = 15.0 * sin(bob);
            bobPos = lbl_1_bss_0->unk11C;
            bobPos.y += bob - 15.0f;
            lbl_1_bss_0->unk134 = bobPos;
            Hu3DModelPosSetV(lbl_1_bss_0->unk118, &bobPos);
            bobTime++;
            bobTime %= 300;
        }
        switch (mode) {
            case 0:
                break;
            case 1:
                seNo = HuAudFXPlay(1170);
                mdlId = lbl_1_bss_0->mdlId[16];
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelPosSetV(mdlId, (HuVecF *)lbl_1_data_B4);
                Hu3DModelScaleSet(mdlId, 2.0f, 1.5f, 2.0f);
                Hu3DParManAttrReset(lbl_1_bss_0->parManId[0], 1);
                lbl_1_bss_0->unkCA4[0] = 0;
                time = 0;
                mdlNo = 1;
                mode = 2;
                break;
            case 2:
                if (++time > 10) {
                    mdlId = lbl_1_bss_0->mdlId[mdlNo + 16];
                    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(mdlId, (HuVecF *)lbl_1_data_B4);
                    Hu3DModelScaleSet(mdlId, 2.0f, 1.5f, 2.0f);
                    if (mdlNo % 2) {
                        Hu3DModelRotSet(mdlId, 0.0f, 180.0f, 0.0f);
                    }
                    time = 0;
                    if (++mdlNo >= 10) {
                        mode = 3;
                    }
                }
                break;
            case 3:
                if (++time > 60) {
                    mdlId = lbl_1_bss_0->unk118;
                    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelScaleSet(mdlId, 1.0f, 1.0f, 1.0f);
                    Hu3DModelTPLvlSet(mdlId, 0.0f);
                    lbl_1_bss_0->unk11C = lbl_1_data_A8;
                    bobF = TRUE;
                    bobTime = 0;
                    time = 0;
                    mode = 6;
                    anim = HuSprAnimDataRead(DATANUM(DATA_mgmatch, 77));
                    grpId = HuSprGrpCreate(3);
                    i = 3;
                    while (i--) {
                        rot[i] = frandmod(360);
                        HuSprGrpMemberSet(grpId, i, HuSprCreate(anim, 100, 0));
                        HuSprScaleSet(grpId, i, 0.0f, 0.0f);
                        HuSprZRotSet(grpId, i, rot[i]);
                        HuSprAttrSet(grpId, i, HUSPR_ATTR_ADDCOL);
                    }
                    HuSprGrpPosSet(grpId, 290.0f, 120.0f);
                    HuSprGrpDrawNoSet(grpId, 0);
                }
                break;
            case 6:
                sprScale = (time - 22.5f) / 5.0f;
                unused = (time - 45.0f) / 60.0f;
                tpLvl = 1.0f - time / 60.0f;
                if (tpLvl >= 0.0f && sprScale <= 1.0f) {
                    i = lbl_1_bss_4->winsNeeded;
                    while (i--) {
                        Hu3DModelTPLvlSet(lbl_1_bss_0->winMdl[i].mdlId, tpLvl);
                    }
                }
                if (0.0f <= sprScale && sprScale <= 2.0f) {
                    if (seNo2 < 0) {
                        seNo2 = HuAudFXPlay(1171);
                    }
                    if (sprScale >= 1.0f) {
                        i = lbl_1_bss_4->winsNeeded;
                        while (i--) {
                            Hu3DModelTPLvlSet(lbl_1_bss_0->winMdl[i].mdlId, 0.0f);
                        }
                        Hu3DModelTPLvlSet(lbl_1_bss_0->unk118, 1.0f);
                        sprScale = 2.0f - sprScale;
                    }
                    sprScale *= 5.0f;
                    i = 3;
                    while (i--) {
                        if (i & 1) {
                            rot[i] += 10.0f;
                        }
                        else {
                            rot[i] -= 10.0f;
                        }
                        rotIn = rot[i];
                        rotMod = fmod(rotIn, 360.0);
                        rotOut = rotMod;
                        rot[i] = rotOut;
                        HuSprScaleSet(grpId, i, sprScale, sprScale);
                        HuSprZRotSet(grpId, i, rot[i]);
                    }
                }
                else {
                    i = 3;
                    while (i--) {
                        HuSprScaleSet(grpId, i, 0.0f, 0.0f);
                    }
                }
                if (++time > 45) {
                    i = lbl_1_bss_4->winsNeeded;
                    while (i--) {
                        Hu3DModelTPLvlSet(lbl_1_bss_0->winMdl[i].mdlId, 0.0f);
                    }
                    Hu3DModelTPLvlSet(lbl_1_bss_0->unk118, 1.0f);
                    HuAudFXStop(seNo);
                    time = 0;
                    mode = 7;
                }
                break;
            case 7:
                tpLvl2 = 1.0f - time / 120.0f;
                i = 10;
                while (i--) {
                    mdlId = lbl_1_bss_0->mdlId[i + 16];
                    Hu3DModelTPLvlSet(mdlId, tpLvl2);
                }
                if (++time > 120) {
                    i = 10;
                    while (i--) {
                        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[i + 16], HU3D_ATTR_DISPOFF);
                    }
                    fn_1_898(0x10000);
                    HuAudFXStop(lbl_1_bss_0->unkE0C);
                    lbl_1_bss_0->unk128 = lbl_1_bss_0->unk11C;
                    moveTime = 0;
                    mode = 100;
                }
                break;
            case 100:
                t = moveTime / 60.0f;
                switch (lbl_1_bss_4->gameType) {
                    case MGMATCH_GAMETYPE_4P:
                        camPos = lbl_1_data_30[lbl_1_bss_4->winner];
                        camPos.y += 40.0f + CharModelHeightGet(lbl_1_bss_0->player[lbl_1_bss_4->winner].charNo);
                        break;
                    case MGMATCH_GAMETYPE_2VS2:
                        if (lbl_1_bss_4->winner == 0) {
                            PSVECAdd(&lbl_1_data_30[0], &lbl_1_data_30[1], &camPos);
                            PSVECScale(&camPos, &camPos, 0.5f);
                            height = CharModelHeightGet(lbl_1_bss_0->player[0].charNo);
                            if (height < CharModelHeightGet(lbl_1_bss_0->player[1].charNo)) {
                                height = CharModelHeightGet(lbl_1_bss_0->player[1].charNo);
                            }
                            camPos.y += 40.0f + height;
                        }
                        else {
                            PSVECAdd(&lbl_1_data_30[2], &lbl_1_data_30[3], &camPos);
                            PSVECScale(&camPos, &camPos, 0.5f);
                            height = CharModelHeightGet(lbl_1_bss_0->player[2].charNo);
                            if (height < CharModelHeightGet(lbl_1_bss_0->player[3].charNo)) {
                                height = CharModelHeightGet(lbl_1_bss_0->player[3].charNo);
                            }
                            camPos.y += 40.0f + height;
                        }
                        break;
                    case MGMATCH_GAMETYPE_1VS3:
                        if (lbl_1_bss_4->winner == 0) {
                            camPos = lbl_1_data_30[0];
                            camPos.y += 40.0f + CharModelHeightGet(lbl_1_bss_0->player[0].charNo);
                        }
                        else {
                            camPos = lbl_1_data_30[2];
                            camPos.y += 240.0f;
                        }
                        break;
                }
                camPos.z -= 30.0f;
                t = sin((M_PI * t) / 2.0);
                t = sin((M_PI * t) / 2.0);
                PSVECSubtract(&camPos, &lbl_1_bss_0->unk128, &camDir);
                PSVECScale(&camDir, &camDir, t);
                PSVECAdd(&lbl_1_bss_0->unk128, &camDir, &lbl_1_bss_0->unk11C);
                if (++moveTime > 60.0f) {
                    lbl_1_bss_0->camMot[0].time = 0.0f;
                    lbl_1_bss_0->camMot[0].fov = lbl_1_bss_4->camFov;
                    lbl_1_bss_0->camMot[0].pos = lbl_1_bss_4->camPos;
                    lbl_1_bss_0->camMot[0].up = lbl_1_bss_4->camUp;
                    lbl_1_bss_0->camMot[0].target = lbl_1_bss_4->camTarget;
                    lbl_1_bss_0->camMot[1].time = 30.0f;
                    lbl_1_bss_0->camMot[1].fov = 40.0f;
                    lbl_1_bss_0->camMot[1].up = lbl_1_bss_4->camUp;
                    lbl_1_bss_0->camMot[1].pos.x = camPos.x;
                    lbl_1_bss_0->camMot[1].pos.y = 100.0f + camPos.y;
                    lbl_1_bss_0->camMot[1].pos.z = 500.0f + camPos.z;
                    lbl_1_bss_0->camMot[1].target.x = camPos.x;
                    lbl_1_bss_0->camMot[1].target.y = camPos.y - 40.0f;
                    lbl_1_bss_0->camMot[1].target.z = camPos.z;
                    switch (lbl_1_bss_4->gameType) {
                        case MGMATCH_GAMETYPE_4P:
                            fn_1_5D0(lbl_1_bss_4->winner, 20);
                            break;
                        case MGMATCH_GAMETYPE_2VS2:
                            if (lbl_1_bss_4->winner == 0) {
                                fn_1_5D0(0, 15);
                                fn_1_5D0(1, 15);
                            }
                            else {
                                fn_1_5D0(2, 15);
                                fn_1_5D0(3, 15);
                            }
                            break;
                        case MGMATCH_GAMETYPE_1VS3:
                            if (lbl_1_bss_4->winner == 0) {
                                fn_1_5D0(0, 15);
                            }
                            else {
                                fn_1_5D0(1, 15);
                                fn_1_5D0(2, 15);
                                fn_1_5D0(3, 15);
                            }
                            if (lbl_1_bss_4->winner != 0) {
                                lbl_1_bss_0->camMot[1].target.y -= 30.0f;
                            }
                            break;
                    }
                    lbl_1_bss_0->camMotNum = 2;
                    parTime = 0.0f;
                    fn_1_1F00();
                    HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
                    lbl_1_bss_0->streamNo = -1;
                    mode = 101;
                }
                break;
            case 101:
                parTime += 1.0f;
                lbl_1_data_228.scaleBase = 40.0f - 15.0f * (parTime / 30.0f);
                OSReport("%3.2f\n", lbl_1_data_228.scaleBase);
                if (fn_1_8B4(0x100)) {
                    mode = 102;
                }
                break;
            case 102:
                switch (lbl_1_bss_4->gameType) {
                    case MGMATCH_GAMETYPE_4P:
                        GameMesMgWinnerCreate(lbl_1_bss_0->player[lbl_1_bss_4->winner].charNo, -1, -1, -1);
                        j = 4;
                        while (j--) {
                            player = &lbl_1_bss_0->player[j];
                            if (j == lbl_1_bss_4->winner) {
                                fn_1_974(player, 2);
                                if (player->mot != 3) {
                                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                    player->mot = 3;
                                }
                            }
                            else {
                                if (player->mot != 4) {
                                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                    player->mot = 4;
                                }
                            }
                        }
                        break;
                    case MGMATCH_GAMETYPE_2VS2:
                        player = &lbl_1_bss_0->player[0];
                        if (lbl_1_bss_4->winner == 0) {
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            GameMesMgWinnerCreate(lbl_1_bss_0->player[0].charNo, lbl_1_bss_0->player[1].charNo, -1, -1);
                        }
                        else {
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            GameMesMgWinnerCreate(lbl_1_bss_0->player[2].charNo, lbl_1_bss_0->player[3].charNo, -1, -1);
                        }
                        break;
                    case MGMATCH_GAMETYPE_1VS3:
                        player = &lbl_1_bss_0->player[0];
                        if (lbl_1_bss_4->winner == 0) {
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            GameMesMgWinnerCreate(lbl_1_bss_0->player[0].charNo, -1, -1, -1);
                        }
                        else {
                            if (player->mot != 4) {
                                CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 4;
                            }
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            if (player->mot != 3) {
                                CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                                player->mot = 3;
                            }
                            fn_1_974(player, 2);
                            player++;
                            GameMesMgWinnerCreate(lbl_1_bss_0->player[1].charNo, lbl_1_bss_0->player[2].charNo, lbl_1_bss_0->player[3].charNo, -1);
                        }
                        break;
                }
                HuAudJinglePlay(MSM_STREAM_JNGL_MGCIRCUIT_WIN);
                time = 0;
                mode = 1000;
                break;
            case 1000:
                if (++time > 240) {
                    fn_1_87C(0x4000);
                    mode = 10000;
                }
                break;
        }
        HuPrcVSleep();
    } while (mode != 10000);
    HuPrcEnd();
}

/* 21 insns */
void fn_1_64B0(void)
{
    fn_1_898(0x4000);
    HuPrcChildCreate(fn_1_4114, 100, 0x1500, 0, HuPrcCurrentGet());
}

/* 154 insns */
void fn_1_6504(void)
{
    HuVecF pos2D;
    HuVecF pos3D;
    HuVecF pos;
    HuVecF dist;
    s32 i;
    s32 mdlId;

    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[37], HU3D_ATTR_DISPOFF);
    i = 9;
    while (i--) {
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[i + 38], HU3D_ATTR_DISPOFF);
    }
    while (fn_1_8B4(0x8000)) {
        Hu3D3Dto2D((HuVecF *)lbl_1_data_1C4, HU3D_CAM4, &pos2D);
        pos3D = pos2D;
        pos3D.z = lbl_1_bss_4->camPos.z;
        Hu3D2Dto3D(&pos3D, HU3D_CAM4, &pos3D);
        Hu3DModelPosSetV(lbl_1_bss_0->mdlId[37], &pos3D);
        dist.x = 288.0f - pos2D.x;
        dist.y = 240.0f - pos2D.y;
        i = 9;
        while (i--) {
            pos = pos2D;
            pos.x += 2.0f * (dist.x * lbl_1_data_1D0[i]);
            pos.y += 2.0f * (dist.y * lbl_1_data_1D0[i]);
            pos.z = lbl_1_bss_4->camPos.z - lbl_1_data_1D0[i];
            Hu3D2Dto3D(&pos, HU3D_CAM4, &pos);
            mdlId = lbl_1_bss_0->mdlId[i + 38];
            Hu3DModelPosSetV(mdlId, &pos);
            pos.x = pos.y = pos.z = lbl_1_data_1F4[i];
            Hu3DModelScaleSetV(mdlId, &pos);
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 21 insns */
void fn_1_676C(void)
{
    fn_1_87C(0x8000);
    HuPrcChildCreate(fn_1_6504, 100, 0x1500, 0, HuPrcCurrentGet());
}

/* 214 insns */
void fn_1_67C0(void)
{
    s32 i;
    s32 count;
    s32 mdlId;

    count = 0;
    fn_1_204(15);
    fn_1_898(0x100000);
    HuPrcVSleep();
    i = 7;
    while (i--) {
        Hu3DModelAttrReset(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_0->effMdl[i].unk10 = lbl_1_data_320[1];
        PSVECAdd(&lbl_1_bss_0->effMdl[i].unk10, lbl_1_data_278 + i + 7, &lbl_1_bss_0->effMdl[i].unk10);
        lbl_1_bss_0->effMdl[i].unk4 = lbl_1_bss_0->effMdl[i].unk10;
        Hu3DModelPosSet(lbl_1_bss_0->effMdl[i].mdlId, lbl_1_bss_0->effMdl[i].unk4.x, lbl_1_bss_0->effMdl[i].unk4.y, lbl_1_bss_0->effMdl[i].unk4.z);
    }
    while (!fn_1_8B4(0x40000)) {
        i = 7;
        while (i--) {
            mdlId = lbl_1_bss_0->effMdl[i].mdlId;
            PSVECAdd(&lbl_1_bss_0->effMdl[i].unk4, &lbl_1_data_338[1], &lbl_1_bss_0->effMdl[i].unk4);
            Hu3DModelPosSet(mdlId, lbl_1_bss_0->effMdl[i].unk4.x, lbl_1_bss_0->effMdl[i].unk4.y, lbl_1_bss_0->effMdl[i].unk4.z);
        }
        count++;
        if (count >= 1200.0f) {
            count = 0;
            i = 7;
            while (i--) {
                lbl_1_bss_0->effMdl[i].unk4 = lbl_1_bss_0->effMdl[i].unk10;
            }
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 52 insns */
void fn_1_6B18(void)
{
    s32 i = 7;
    while (i--) {
        Hu3DModelAttrReset(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(lbl_1_bss_0->effMdl[i].mdlId, 4);
        Hu3DModelCameraSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_CAM4);
    }
    fn_1_898(0x40000);
    HuPrcChildCreate(fn_1_67C0, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 448 insns */
void fn_1_6BE8(void)
{
    float angle[7];
    float *dst[3];
    float *src[3];
    float val[4];
    float knot[4];
    HuVecF cur;
    HuVecF prev;
    HuVecF dir;
    float *p;
    float t;
    float maxT;
    float rot;
    float ofsY;
    s16 i;
    s16 j;
    s32 mdlId;
    s32 num;
    s32 stride;

    stride = 4;
    num = 4;
    fn_1_204(frandmod(1200));
    for(i = 7; i--;) {
        angle[i] = frandmod(360);
    }
    while(TRUE) {
        maxT = 1200.0f;
        prev.x = prev.y = prev.z = 0.0f;
        dst[0] = &cur.x;
        dst[1] = &cur.y;
        dst[2] = &cur.z;
        for(i = 7; i--;) {
            Hu3DModelAttrReset(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
        }
        for(t = 0.0f; t <= maxT; t += 1.0f) {
            if(!(lbl_1_bss_0->flag & 0x100000)) {
                break;
            }
            for(p = lbl_1_data_350, i = 0; i < num; i++, p += 4) {
                if(p[3] <= t
                    && t < p[7]) {
                    break;
                }
            }
            if(i == num) {
                break;
            }
            src[0] = &p[0];
            src[1] = &p[1];
            src[2] = &p[2];
            if(i == 0) {
                knot[0] = -1.0f;
            } else {
                knot[0] = p[-1];
            }
            knot[1] = p[3];
            if(i >= num - 1) {
                knot[2] = 1.0f + knot[1];
            } else {
                knot[2] = p[7];
            }
            if(i >= num - 2) {
                knot[3] = 1.0f + knot[2];
            } else {
                knot[3] = p[11];
            }
            for(j = 3; j--;) {
                if(i == 0) {
                    val[0] = *src[j];
                } else {
                    val[0] = *(src[j] - stride);
                }
                val[1] = *src[j];
                if(i >= num - 1) {
                    val[2] = val[1];
                } else {
                    val[2] = src[j][stride];
                }
                if(i >= num - 2) {
                    val[3] = val[2];
                } else {
                    val[3] = src[j][stride * 2];
                }
                *dst[j] = InterpolateBMLine(val, knot, t);
            }
            PSVECSubtract(&cur, &prev, &dir);
            PSVECNormalize(&dir, &dir);
            prev = cur;
            if(dir.z > 1.0f) {
                dir.z = 1.0f;
            } else if(dir.z < -1.0f) {
                dir.z = -1.0f;
            }
            rot = acosf(dir.z);
            if(dir.x < 0.0f) {
                rot = -rot;
            }
            rot = (180.0f * rot) / M_PI;
            for(i = 7; i--;) {
                mdlId = lbl_1_bss_0->effMdl[i].mdlId;
                ofsY = 50.0 * sin((M_PI * angle[i]) / 180.0);
                PSVECAdd(&cur, &lbl_1_data_278[i], &lbl_1_bss_0->effMdl[i].unk4);
                Hu3DModelPosSet(mdlId, lbl_1_bss_0->effMdl[i].unk4.x, lbl_1_bss_0->effMdl[i].unk4.y + ofsY, lbl_1_bss_0->effMdl[i].unk4.z);
                Hu3DModelRotSet(mdlId, 0.0f, rot, 0.0f);
                angle[i] += 3.0f;
                angle[i] = fmodf(angle[i], 360.0f);
            }
            HuPrcVSleep();
        }
        for(i = 7; i--;) {
            Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
        }
        if(!(lbl_1_bss_0->flag & 0x100000)) {
            break;
        }
        fn_1_204(1200);
    }
    HuPrcEnd();
}

/* 133 insns */
void fn_1_72E8(void)
{
    s32 i;
    if(lbl_1_bss_0->flag & 0x100000) {
        return;
    }
    i = 7;
    while(i--) {
        Hu3DModelAttrReset(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_0->effMdl[i].unk10 = lbl_1_data_320[0];
        PSVECAdd(&lbl_1_bss_0->effMdl[i].unk10, &lbl_1_data_278[i], &lbl_1_bss_0->effMdl[i].unk10);
        lbl_1_bss_0->effMdl[i].unk4 = lbl_1_bss_0->effMdl[i].unk10;
        Hu3DModelPosSet(lbl_1_bss_0->effMdl[i].mdlId, lbl_1_bss_0->effMdl[i].unk4.x, lbl_1_bss_0->effMdl[i].unk4.y, lbl_1_bss_0->effMdl[i].unk4.z);
        Hu3DModelLayerSet(lbl_1_bss_0->effMdl[i].mdlId, 0);
        Hu3DModelCameraSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_CAM4);
    }
    fn_1_87C(0x100000);
    HuPrcChildCreate(fn_1_6BE8, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 412 insns */
void fn_1_74FC(MGMATCH_PLAYER *player, HuVecF pos)
{
    struct {
        HuVecF pos;
        float t;
    } path[4];
    float *dst[3];
    float *src[3];
    float val[4];
    float knot[4];
    HuVecF cur;
    HuVecF prev;
    HuVecF dir;
    float *p;
    float t;
    float rot;
    s16 i;
    s32 num;
    s16 j;
    s32 stride;

    stride = 4;
    num = 4;
    pos.y = 0.0f;
    path[0].pos = player->pos;
    path[1].pos = player->pos;
    path[1].pos.z += 30.0f;
    path[2].pos = pos;
    path[2].pos.z -= 30.0f;
    path[3].pos = pos;
    path[3].pos.z += 30.0f;
    path[0].t = 0.0f;
    for(i = 1; i < num; i++) {
        PSVECSubtract(&path[i].pos, &path[i - 1].pos, &cur);
        path[i].t = path[i - 1].t + PSVECMag(&cur) / 6.0f;
    }
    if(player->mot != 2) {
        CharMotionShiftSet(player->charNo, player->motId[2], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
        player->mot = 2;
    }
    prev = player->pos;
    prev.z -= 10.0f;
    dst[0] = &cur.x;
    dst[1] = &cur.y;
    dst[2] = &cur.z;
    for(t = 0.0f;; t += 1.0f) {
        for(p = &path[0].pos.x, i = 0; i < num; i++, p += 4) {
            if(p[3] <= t
                && t < p[7]) {
                break;
            }
        }
        if(i == num) {
            break;
        }
        src[0] = &p[0];
        src[1] = &p[1];
        src[2] = &p[2];
        if(i == 0) {
            knot[0] = -1.0f;
        } else {
            knot[0] = p[-1];
        }
        knot[1] = p[3];
        if(i >= num - 1) {
            knot[2] = 1.0f + knot[1];
        } else {
            knot[2] = p[7];
        }
        if(i >= num - 2) {
            knot[3] = 1.0f + knot[2];
        } else {
            knot[3] = p[11];
        }
        for(j = 3; j--;) {
            if(i == 0) {
                val[0] = *src[j];
            } else {
                val[0] = *(src[j] - stride);
            }
            val[1] = *src[j];
            if(i >= num - 1) {
                val[2] = val[1];
            } else {
                val[2] = src[j][stride];
            }
            if(i >= num - 2) {
                val[3] = val[2];
            } else {
                val[3] = src[j][stride * 2];
            }
            *dst[j] = InterpolateBMLine(val, knot, t);
        }
        PSVECSubtract(&cur, &prev, &dir);
        PSVECNormalize(&dir, &dir);
        prev = cur;
        if(dir.z > 1.0f) {
            dir.z = 1.0f;
        } else if(dir.z < -1.0f) {
            dir.z = -1.0f;
        }
        rot = acosf(dir.z);
        if(dir.x < 0.0f) {
            rot = -rot;
        }
        rot = (180.0f * rot) / M_PI;
        player->pos = cur;
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelRotSet(player->mdlId, 0.0f, rot, 0.0f);
        HuPrcVSleep();
    }
    player->pos = path[num - 1].pos;
    Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
    Hu3DModelRotSet(player->mdlId, 0.0f, 0.0f, 0.0f);
    if(player->mot != 0) {
        CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
        player->mot = 0;
    }
}

/* 130 insns */
BOOL fn_1_7B6C(float *angle, float end, float speed)
{
    float diff = *angle - end;
    float change = fmodf(diff, 180);
    float wrap = fmodf(diff, 360);
    if(fabsf(wrap) > 180.0f) {
        if(change > 0) {
            change = -(180.0f - fabsf(change));
        } else {
            change = 180.0f - fabsf(change);
        }
    }
    if(fabsf(change) < speed) {
        *angle = end;
        return TRUE;
    }
    if(change > 0) {
        change -= speed;
    } else {
        change += speed;
    }
    *angle = end + change;
    return FALSE;
}

/* 497 insns */
void fn_1_7D74(void)
{
    HuVecF dir;
    HuVecF aimPos;
    MGMATCH_PLAYER *player;
    int i;
    int doneNum;
    float rotEnd;
    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        switch (lbl_1_bss_0->playerRotMode) {
            case 0:
                player->rotEnd = 0;
                break;

            case 1:
                VECSubtract(&lbl_1_data_390, &player->pos, &aimPos);
                aimPos.y = 0;
                VECNormalize(&aimPos, &dir);
                if (dir.z > 1) {
                    dir.z = 1;
                }
                else if (dir.z < -1) {
                    dir.z = -1;
                }
                rotEnd = acosf(dir.z);
                if (dir.x < 0) {
                    rotEnd = -rotEnd;
                }
                player->rotEnd = (180 * rotEnd) / M_PI;
                break;

            case 2:
                VECSubtract(&lbl_1_data_39C, &player->pos, &aimPos);
                aimPos.y = 0;
                VECNormalize(&aimPos, &dir);
                if (dir.z > 1) {
                    dir.z = 1;
                }
                else if (dir.z < -1) {
                    dir.z = -1;
                }
                rotEnd = acosf(dir.z);
                if (dir.x < 0) {
                    rotEnd = -rotEnd;
                }
                player->rotEnd = (180 * rotEnd) / M_PI;
                break;
        }
        if (!fn_1_7B6C(&player->rot, player->rotEnd, 0.01f)) {
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0, 15, HU3D_MOTATTR_LOOP);
                player->mot = 1;
            }
        }
    }
    while (1) {
        doneNum = 0;
        for (player = &lbl_1_bss_0->player[0], i = 4; i--; player++) {
            if (fn_1_7B6C(&player->rot, player->rotEnd, lbl_1_bss_0->playerRotSpeed)) {
                if (player->mot != 0) {
                    CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_LOOP);
                    player->mot = 0;
                }
                doneNum++;
            }
            Hu3DModelRotSet(player->mdlId, 0, player->rot, 0);
        }
        if (doneNum == 4) {
            break;
        }
        HuPrcVSleep();
    }
    fn_1_87C(0x200000);
    HuPrcEnd();
}

/* 35 insns */
void fn_1_8538(s32 mode, float speed)
{
    fn_1_898(0x200000);
    lbl_1_bss_0->playerRotMode = mode;
    lbl_1_bss_0->playerRotSpeed = speed;
    fn_1_1A24(fn_1_7D74);
}

/* 1184 insns */
void fn_1_85C4(void)
{
    s8 no[4];
    s8 grp[4];
    OMOVLHIS *his;
    MGMATCH_PLAYER *player;
    int i;
    int mgIdx;
    int num;
    int parManId;
    ANIMDATA *parAnim;
    ANIMDATA *anim;

    his = omOvlHisGet(0);
    lbl_1_bss_4 = (MGMATCH_MODEWORK *)mgModeWork;
    lbl_1_bss_0 = &lbl_1_bss_8;
    {
    HuVecF lightPos = { 0, 8000, 0 };
    HuVecF lightUp = { 0, 0, 1 };
    HuVecF lightTarget = { 0, 0, 0 };
    HuVecF lightDir = { 0, -1, 0 };
    HuVecF light2Pos = { 0, 50, 700 };
    HuVecF light2Dir = { 0, 0, -1 };
    int lightId;
    lbl_1_bss_0->objman = omInitObjMan(200, 1000);
    HuDataSelHeapReadNum(DATANUM(DATA_instpic, 0), HU_MEMNUM_OVL, HEAP_MODEL);
    Hu3DCameraCreate(HU3D_CAM4);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, 60, 20, 60000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM4, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
    lightId = Hu3DGLightCreate(0, 1000, 1000, 0, -1, -1, 255, 255, 255);
    Hu3DGLightStaticSet(lightId, TRUE);
    Hu3DGLightPosSetV(lightId, &lightPos, &lightDir);
    lightId = Hu3DGLightCreate(0, 1000, 1000, 0, -1, -1, 128, 128, 128);
    lbl_1_bss_0->lightId = lightId;
    Hu3DGLightStaticSet(lightId, TRUE);
    Hu3DGLightPosSetV(lightId, &light2Pos, &light2Dir);
    Hu3DGLightSpotSet(lightId, GX_SP_FLAT, 150);
    Hu3DShadowCreate(15, 20, 8000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&lightPos, &lightUp, &lightTarget);
    Hu3DShadowSizeSet(240);
    Hu3DParManInit();
    }
    for (i = 0; i < 43; i++) {
        for (mgIdx = 0; mgDataTbl[mgIdx].ovl != lbl_1_data_C0[i].ovl; mgIdx++) {
            if (mgDataTbl[mgIdx].ovl == (u16)DLL_NONE) {
                OSReport("mgmatch.c : \202c\202k\202k\202\252\214\251\202\302\202\251\202\350\202\334\202\271\202\361\201I\201I\n");
                abort();
            }
        }
        lbl_1_data_C0[i].mgIdx = mgIdx;
    }
    for (i = 0; i < 43; i++) {
        lbl_1_data_C0[i].battleF = mgDataTbl[lbl_1_data_C0[i].mgIdx].type == MG_TYPE_BATTLE;
    }
    lbl_1_bss_0->cameraMot = -1;
    lbl_1_bss_0->winId = 0;
    lbl_1_bss_0->winner = -1;
    lbl_1_bss_0->mesFlag = 0;
    lbl_1_bss_0->flag = 0;
    lbl_1_bss_0->cameraMotNext = -1;
    lbl_1_bss_0->cameraMotTime = 0;
    lbl_1_bss_0->cameraMotArg = 0;
    lbl_1_bss_0->animId = -1;
    lbl_1_bss_0->streamNo = MSM_STREAMNO_NONE;
    lbl_1_bss_0->movieMode = 0;
    {
    HuVec2f winSize;
    HuWinInit(1);
    HuWinMesMaxSizeBetGet(&winSize, MGMATCH_MESS(0), MGMATCH_MESS(18));
    lbl_1_bss_0->winId = HuWinExCreate(-10000, 360, winSize.x, winSize.y, HUWIN_SPEAKER_NONE);
    }
    fn_1_D88();
    parAnim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 74), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_data_228.colorStart[0] = lbl_1_data_218[0];
    lbl_1_data_228.colorStart[1] = lbl_1_data_218[1];
    lbl_1_data_228.colorEnd[0] = lbl_1_data_218[2];
    lbl_1_data_228.colorEnd[1] = lbl_1_data_218[3];
    for (i = 4; i--;) {
        parManId = Hu3DParManCreate(parAnim, 100, &lbl_1_data_228);
        lbl_1_bss_0->parManId[i] = parManId;
        Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_SCALEJITTER | HU3D_PARMAN_ATTR_RANDSCALE90 | HU3D_PARMAN_ATTR_RANDSPEED70 | HU3D_PARMAN_ATTR_TIMEUP); /* 0x55 (mgtour passes the same without bit 0) */
        Hu3DParManLayerSet(parManId, 4);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), HU3D_PARTICLE_BLEND_ADDCOL);
    }
    fn_1_2F78();
    if (his->evtno == 0) {
        _SetFlag(FLAG_INST_NOHISCHG);
        _SetFlag(FLAG_INST_MGMODE);
        lbl_1_bss_4->gameType = mgMatchGameType;
        lbl_1_bss_4->winsNeeded = mgMatchMaxScore;
        switch (mgMatchGameType) {
            case MGMATCH_GAMETYPE_4P:
                lbl_1_bss_4->mgNum = 0;
                for (i = 0; i < 21; i++) {
                    if (GWMgUnlockGet(lbl_1_data_C0[i].mgNo)) {
                        lbl_1_bss_4->mg[lbl_1_bss_4->mgNum] = lbl_1_data_C0[i];
                        lbl_1_bss_4->mgNum++;
                    }
                }
                for (i = 0; i < GW_PLAYER_MAX; i++) {
                    GwPlayerConf[i].grp = i;
                }
                break;
            case MGMATCH_GAMETYPE_2VS2:
                lbl_1_bss_4->mgNum = 0;
                for (i = 21; i < 32; i++) {
                    if (GWMgUnlockGet(lbl_1_data_C0[i].mgNo)) {
                        lbl_1_bss_4->mg[lbl_1_bss_4->mgNum] = lbl_1_data_C0[i];
                        lbl_1_bss_4->mgNum++;
                    }
                }
                break;
            case MGMATCH_GAMETYPE_1VS3:
                lbl_1_bss_4->mgNum = 0;
                for (i = 32; i < 43; i++) {
                    if (GWMgUnlockGet(lbl_1_data_C0[i].mgNo)) {
                        lbl_1_bss_4->mg[lbl_1_bss_4->mgNum] = lbl_1_data_C0[i];
                        lbl_1_bss_4->mgNum++;
                    }
                }
                break;
        }
        if (lbl_1_bss_4->gameType == MGMATCH_GAMETYPE_4P) {
            num = 4;
        }
        else {
            num = 2;
        }
        lbl_1_bss_4->num = num;
        for (i = lbl_1_bss_4->num; i--;) {
            lbl_1_bss_4->score[i] = 0;
        }
    }
    else {
        Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_4->camFov, 20, 60000, 1.2f);
    }
    player = &lbl_1_bss_0->player[0];
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        no[i] = i;
        grp[i] = GwPlayerConf[i].grp;
    }
    fn_1_A0(grp, no, GW_PLAYER_MAX);
    for (i = 0; i < GW_PLAYER_MAX; i++, player++) {
        player->no = no[i];
        player->grp = grp[i];
        player->charNo = GwPlayerConf[no[i]].charNo;
        player->padNo = GwPlayerConf[no[i]].padNo;
        player->mdlId = CharModelMotListCreate(player->charNo, CHAR_MODEL1, lbl_1_data_0, player->motId);
        player->mot = -1;
        player->pos = lbl_1_data_30[i];
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[3], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[4], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[5], FALSE);
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelAttrSet(player->mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelLayerSet(player->mdlId, 4);
        Hu3DModelCameraSet(player->mdlId, HU3D_CAM4);
        lbl_1_bss_0->mdlId[i + 26] = player->mdlId;
    }
    CharEffectLayerSet(5);
    {
    HuVecF guidePos = lbl_1_data_60[0];
    HU3DMODELID guideMdlId;
    HU3DMOTID guideMotId;
    guideMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_0->guideMdlId = guideMdlId;
    lbl_1_bss_0->guidePos = guidePos;
    guideMotId = Hu3DJointMotion(guideMdlId, HuDataSelHeapReadNum(DATANUM(DATA_mgmatch, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(guideMdlId, guideMotId);
    Hu3DModelAttrSet(guideMdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(guideMdlId, 3);
    Hu3DModelCameraSet(guideMdlId, HU3D_CAM4);
    Hu3DModelPosSet(guideMdlId, guidePos.x, guidePos.y, guidePos.z);
    }
    fn_1_12404(lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, &lbl_1_bss_0->player[0], &lbl_1_bss_4->score[0], &lbl_1_bss_0->mdlId[0]);
    fn_1_3C04();
    for (i = lbl_1_bss_4->mgNum; i--;) {
        if (lbl_1_bss_4->mg[i].mgIdx + 501 == 519) {
            lbl_1_bss_0->mgVariant = frandmod(3);
            anim = HuSprAnimRead(HuDataSelHeapReadNum(mgDataTbl[lbl_1_bss_4->mg[i].mgIdx].instPic[lbl_1_bss_0->mgVariant], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        else {
            anim = HuSprAnimRead(HuDataSelHeapReadNum(mgDataTbl[lbl_1_bss_4->mg[i].mgIdx].instPic[0], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        HuSprAnimLock(anim);
        lbl_1_bss_0->mgIcon[i] = anim;
    }
    Hu3DModelShadowMapSet(lbl_1_bss_0->mdlId[0]);
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        Hu3DModelShadowSet(lbl_1_bss_0->player[i].mdlId);
    }
    for (i = 0; i < 3; i++) {
        Hu3DModelShadowSet(lbl_1_bss_0->effMdl[i].mdlId);
    }
    Hu3DModelShadowSet(lbl_1_bss_0->guideMdlId);
}

/* 80 insns */
void fn_1_9844(void)
{
    HuDataDirClose(DATA_mgmatch);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    HuPrcVSleep();
    HuTHPClose();
    if (lbl_1_bss_0->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
        lbl_1_bss_0->streamNo = -1;
    }
    GWMgInstFSet(TRUE);
    fn_1_D40(0);
    HuWinExClose(lbl_1_bss_0->winId);
    HuWinExKill(lbl_1_bss_0->winId);
    fn_1_294(WIPE_TYPE_WHITEFADE, 60);
    _ClearFlag(FLAG_INST_NOHISCHG);
    _ClearFlag(FLAG_INST_MGMODE);
    memset(lbl_1_bss_4, 0, sizeof(MGMATCH_MODEWORK));
}

/* 744 insns */
void fn_1_9984(void)
{
    HuVecF pos;
    HuVecF target;
    CAMMOTIONWORK *camMotBuf;
    int camMotMax;
    MGMATCH_PLAYER *player;
    int i;
    CAMMOTIONWORK *camMot;
    s8 last;
    float fov;
    float t;

    fn_1_D40(1);
    lbl_1_bss_4->winner = -1;
    fn_1_898(0x1F);
    lbl_1_bss_0->mesFlag = 0;
    fn_1_87C(1);
    for (i = lbl_1_bss_4->mgNum; i--;) {
        lbl_1_bss_4->mgOrder[i] = i;
    }
    lbl_1_bss_4->round = lbl_1_bss_4->mgNum;
    last = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum - 1];
    lbl_1_bss_4->round = 0;
    fn_1_140(lbl_1_bss_4->mgOrder, lbl_1_bss_4->mgNum);
    if (lbl_1_bss_4->mgOrder[0] == last) {
        lbl_1_bss_4->mgOrder[0] = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2];
        lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2] = last;
    }
    fn_1_31B0();
    fn_1_12934();
    fn_1_15BC8();
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[5], 0);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[3], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[3], 0);
    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        if (player->mot != 5) {
            CharMotionShiftSet(player->charNo, player->motId[5], 0, 15, HU3D_MOTATTR_NONE);
            player->mot = 5;
        }
        Hu3DModelAttrSet(player->mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelLayerSet(player->mdlId, 4);
        Hu3DModelCameraSet(player->mdlId, HU3D_CAM4);
    }
    fn_1_2080();
    camMotBuf = lbl_1_bss_0->camMot;
    camMotMax = 50;
    lbl_1_bss_0->camMotNum = CamMotionExPathGet(lbl_1_bss_0->mdlId[61], 6, 240, 0, &camMotBuf, &camMotMax);
    for (i = lbl_1_bss_0->camMotNum; i--;) {
        camMotBuf[i].pos.y -= 100;
    }
    fn_1_1F00();
    fn_1_240(WIPE_TYPE_PREVTYPE, 60);
    fn_1_204(170);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    while (!fn_1_8B4(0x100)) {
        HuPrcVSleep();
    }
    camMot = &lbl_1_bss_0->camMot[lbl_1_bss_0->camMotNum - 1];
    Hu3DCameraPosGet(HU3D_CAM4, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
    lbl_1_bss_4->camFov = camMot->fov;
    pos = lbl_1_bss_4->camPos;
    target = lbl_1_bss_4->camTarget;
    fov = lbl_1_bss_4->camFov;
    for (i = 60; i--;) {
        fov -= 0.2f;
        pos.y += 2;
        target.z += 2;
        Hu3DCameraPosSetV(HU3D_CAM4, &pos, &lbl_1_bss_4->camUp, &target);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, fov, 20, 60000, 1.2f);
        HuPrcVSleep();
    }
    lbl_1_bss_0->streamNo = HuAudBGMPlay(35);
    fn_1_1A24(fn_1_15F24);
    while (!fn_1_95C(1)) {
        HuPrcVSleep();
    }
    fn_1_4B4();
    fn_1_28BC(1, 90);
    for (i = 0; i < 60.0f; i++) {
        t = i / 60.0f;
        fov += 0.2f;
        pos.y -= 2;
        target.z -= 2;
        Hu3DCameraPosSetV(HU3D_CAM4, &pos, &lbl_1_bss_4->camUp, &target);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, fov, 20, 60000, 1.2f);
        Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0, 45 * t, 0);
        HuPrcVSleep();
    }
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0, 45, 0);
    fn_1_204(30);
    fn_1_2628();
    while (!fn_1_8B4(0x40) || !fn_1_8B4(0x80)) {
        HuPrcVSleep();
    }
    fn_1_8538(1, 2);
}

/* 877 insns */
void fn_1_A524(void)
{
    s32 i;
    s32 j;
    s32 num;
    s32 winner;
    s8 last;
    MGMATCH_PLAYER *player;
    MGMATCH_PLAYER *teamPlayer;
    MGMATCH_PLAYER *soloPlayer;
    MGMATCH_PLAYER *resultPlayer;
    HuVecF pos;

    player = &lbl_1_bss_0->player[0];
    pos = lbl_1_data_60[1];
    for (i = 0; i < 4; i++, player++) {
        player->mot = -1;
        if (player->mot != 0) {
            CharMotionSet(player->charNo, player->motId[0]);
            player->mot = 0;
        }
        Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(player->mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(player->mdlId, lbl_1_data_30[i].x, lbl_1_data_30[i].y, lbl_1_data_30[i].z);
    }
    lbl_1_bss_0->guidePos = pos;
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, 45.0f, 0.0f);
    if (lbl_1_bss_4->round == lbl_1_bss_4->mgNum) {
        last = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum - 1];
        lbl_1_bss_4->round = 0;
        fn_1_140(lbl_1_bss_4->mgOrder, lbl_1_bss_4->mgNum);
        if (lbl_1_bss_4->mgOrder[0] == last) {
            lbl_1_bss_4->mgOrder[0] = lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2];
            lbl_1_bss_4->mgOrder[lbl_1_bss_4->mgNum / 2] = last;
        }
    }
    fn_1_31B0();
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[0], 240.0f);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[1], 240.0f);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[5], Hu3DMotionMaxTimeGet(lbl_1_bss_0->mdlId[5]));
    num = 0;
    switch (lbl_1_bss_4->gameType) {
        case MGMATCH_GAMETYPE_4P:
            if (fn_1_90C(1)) {
                OSReport("\203o\203g\203\213\203Q\201[\203\200\201I\201I\n");
                for (i = 4; i--;) {
                    OSReport("\t Player %d = Rank %d\n", i, GWMgCoinBonusGet(i));
                    if (GWMgCoinBonusGet(i) == 0) {
                        winner = i;
                        num++;
                    }
                }
            }
            else {
                OSReport("VS 4 \203Q\201[\203\200\201I\201I\n");
                for (i = 4; i--;) {
                    OSReport("\t Player %d = Bounus Coin %d\n", i, GWMgCoinBonusGet(i));
                    OSReport("\t          = Coin %d\n", GWMgCoinGet(i));
                    if (GWMgCoinBonusGet(i) >= 10 || GWMgCoinGet(i) >= 10) {
                        winner = i;
                        num++;
                    }
                }
            }
            break;
        case MGMATCH_GAMETYPE_2VS2:
            teamPlayer = &lbl_1_bss_0->player[0];
            OSReport("2 VS 2 \203Q\201[\203\200\201I\201I\n");
            for (i = 0; i < 4; i++, teamPlayer++) {
                OSReport("\t Team %d = Coin %d\n", i, GWMgCoinBonusGet(teamPlayer->no));
                OSReport("\t        = Coin %d\n", GWMgCoinGet(teamPlayer->no));
                if (GWMgCoinBonusGet(teamPlayer->no) >= 10 || GWMgCoinGet(teamPlayer->no) >= 10) {
                    switch (i) {
                        case 0:
                        case 1:
                            winner = 0;
                            break;
                        case 2:
                        case 3:
                            winner = 1;
                            break;
                    }
                    num++;
                }
            }
            if (num == 2) {
                num = 1;
            }
            break;
        case MGMATCH_GAMETYPE_1VS3:
            soloPlayer = &lbl_1_bss_0->player[0];
            OSReport("1 VS 3 \203Q\201[\203\200\201I\201I\n");
            for (i = 0; i < 4; i++, soloPlayer++) {
                OSReport("\t Team %d = Coin %d\n", i, GWMgCoinBonusGet(soloPlayer->no));
                OSReport("\t        = Coin %d\n", GWMgCoinGet(soloPlayer->no));
                if (GWMgCoinBonusGet(soloPlayer->no) >= 10 || GWMgCoinGet(soloPlayer->no) >= 10) {
                    switch (i) {
                        case 0:
                            winner = 0;
                            num = 3;
                            break;
                        case 1:
                        case 2:
                        case 3:
                            winner = 1;
                            num++;
                            break;
                    }
                }
            }
            if (num == 3) {
                num = 1;
            }
            break;
    }
    if (num != 1) {
        if (lbl_1_bss_0->streamNo < 0) {
            lbl_1_bss_0->streamNo = HuAudBGMPlay(0x23);
        }
        fn_1_240(WIPE_TYPE_PREVTYPE, 60);
        fn_1_87C(8);
        lbl_1_bss_0->winner = -1;
        for (i = 4; i--;) {
            resultPlayer = &lbl_1_bss_0->player[i];
            fn_1_974(resultPlayer, 1);
            if (resultPlayer->mot != 4) {
                CharMotionShiftSet(resultPlayer->charNo, resultPlayer->motId[4], 0.0f, 15.0f, 0);
                resultPlayer->mot = 4;
            }
        }
        num = 180;
        fn_1_1A24(fn_1_161E8);
        while (!fn_1_95C(0x20) || num >= 0) {
            num--;
            HuPrcVSleep();
        }
        for (i = 4; i--;) {
            resultPlayer = &lbl_1_bss_0->player[i];
            if (resultPlayer->mot != 0) {
                CharMotionShiftSet(resultPlayer->charNo, resultPlayer->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                resultPlayer->mot = 0;
            }
        }
    }
    else {
        fn_1_240(WIPE_TYPE_PREVTYPE, 60);
        lbl_1_bss_0->winner = winner;
    }
    if (num == 1 && lbl_1_bss_4->score[winner] + 1 >= lbl_1_bss_4->winsNeeded) {
        return;
    }
    if (fn_1_90C(4)) {
        return;
    }
    if (fn_1_8B4(0x100000)) {
        return;
    }
    for (j = 7; j--;) {
        Hu3DModelAttrReset(lbl_1_bss_0->effMdl[j].mdlId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_0->effMdl[j].unk10 = lbl_1_data_320[0];
        PSVECAdd(&lbl_1_bss_0->effMdl[j].unk10, &lbl_1_data_278[j], &lbl_1_bss_0->effMdl[j].unk10);
        lbl_1_bss_0->effMdl[j].unk4 = lbl_1_bss_0->effMdl[j].unk10;
        Hu3DModelPosSet(lbl_1_bss_0->effMdl[j].mdlId, lbl_1_bss_0->effMdl[j].unk4.x, lbl_1_bss_0->effMdl[j].unk4.y, lbl_1_bss_0->effMdl[j].unk4.z);
        Hu3DModelLayerSet(lbl_1_bss_0->effMdl[j].mdlId, 0);
        Hu3DModelCameraSet(lbl_1_bss_0->effMdl[j].mdlId, HU3D_CAM4);
    }
    fn_1_87C(0x100000);
    HuPrcChildCreate(fn_1_6BE8, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 734 insns */
void fn_1_B2D8(void)
{
    MGMATCH_PLAYER *player;
    s32 i;
    s32 scoreF;

    scoreF = TRUE;
    fn_1_2134();
    player = lbl_1_bss_0->player;
    switch (lbl_1_bss_4->gameType) {
    case 0:
        for (i = 0; i < 4; i++, player++) {
            if (lbl_1_bss_0->winner == player->no) {
                fn_1_974(player, 0);
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
            }
            else {
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
            }
        }
        break;
    case 2:
        if (lbl_1_bss_0->winner == 0) {
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        }
        else {
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        }
        break;
    case 1:
        if (lbl_1_bss_0->winner == 0) {
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        }
        else {
        if (player->mot != 4) {
            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 4;
        }
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        fn_1_974(player, 0);
        player++;
        }
        break;
    }
    fn_1_1A24(fn_1_16250);
    while (!fn_1_95C(0x40)) {
        HuPrcVSleep();
    }
    fn_1_12AE4(1);
    while (!fn_1_12B08()) {
        HuPrcVSleep();
    }
    fn_1_204(30);
    fn_1_12AE4(4);
    while (!fn_1_12B08()) {
        HuPrcVSleep();
    }
    fn_1_204(60);
    fn_1_4B4();
    fn_1_1A24(fn_1_16D34);
    while (!fn_1_95C(0x1000)) {
        HuPrcVSleep();
    }
    lbl_1_bss_4->score[lbl_1_bss_0->winner]++;
    if (lbl_1_bss_4->score[lbl_1_bss_0->winner] == lbl_1_bss_4->winsNeeded) {
        lbl_1_bss_4->winner = lbl_1_bss_0->winner;
        if (!fn_1_64C(NULL, NULL, NULL) || fn_1_90C(4)) {
            scoreF = FALSE;
        }
    }
    if (scoreF) {
        fn_1_12AE4(2);
    }
    i = 4;
    while (i--) {
        player = &lbl_1_bss_0->player[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    fn_1_204(90);
}

/* 506 insns */
void fn_1_BE50(void)
{
    s32 i;
    s32 time;
    s32 mdlId;
    s8 playerNo[4];
    s8 score[4];
    HuVecF pos;
    HuVecF scale;

    if (fn_1_64C(NULL, NULL, NULL) && !fn_1_90C(4)) {
        fn_1_D184();
    }
    else {
        for (i = 0; i < lbl_1_bss_4->num; i++) {
            playerNo[i] = i;
            score[i] = lbl_1_bss_4->score[i];
        }
        fn_1_A0(score, playerNo, lbl_1_bss_4->num);
        for (i = 0; i < lbl_1_bss_4->num; i++) {
            OSReport("Player %d  Rank = %d [score : %d]\n", playerNo[i], i, score[i]);
        }
        for (i = 0; i < lbl_1_bss_4->num; i++) {
            lbl_1_bss_4->unk20[i] = playerNo[lbl_1_bss_4->num - i - 1];
        }
    }
    for (i = 0; i < lbl_1_bss_4->num; i++) {
        OSReport("Rank : %d Player %d [score : %d]\n", i, lbl_1_bss_4->unk20[i], lbl_1_bss_4->score[lbl_1_bss_4->unk20[i]]);
    }
    if (lbl_1_bss_0->streamNo < 0) {
        lbl_1_bss_0->streamNo = HuAudBGMPlay(0x23);
    }
    fn_1_1A24(fn_1_169E0);
    while (!fn_1_95C(0x200)) {
        HuPrcVSleep();
    }
    fn_1_8538(2, 2.0f);
    if (fn_1_12B4C() == 0) {
        fn_1_12AE4(1);
        while (!fn_1_12B08()) {
            HuPrcVSleep();
        }
    }
    while (!fn_1_8B4(0x200000)) {
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_16574);
    while (!fn_1_95C(0x80)) {
        HuPrcVSleep();
    }
    fn_1_4B4();
    fn_1_8538(0, 2.0f);
    while (!fn_1_8B4(0x200000)) {
        HuPrcVSleep();
    }
    fn_1_204(60);
    i = lbl_1_bss_4->score[lbl_1_bss_4->winner];
    while (i--) {
        fn_1_138B8(&pos, &scale, lbl_1_bss_4->winner, i, 40.0f, lbl_1_bss_4->gameType, lbl_1_bss_4->camPos.z - lbl_1_data_30[0].z);
        lbl_1_bss_0->winMdl[i].unk10 = pos;
        lbl_1_bss_0->winMdl[i].unk2 = 0;
        lbl_1_bss_0->winMdl[i].unk1C = scale;
        mdlId = lbl_1_bss_0->winMdl[i].mdlId;
        Hu3DModelPosSetV(mdlId, &pos);
        Hu3DModelScaleSetV(mdlId, &scale);
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelTPLvlSet(mdlId, 0.0f);
    }
    lbl_1_bss_0->unkE0C = HuAudFXPlay(0x491);
    fn_1_12AE4(5);
    while (!fn_1_12B08()) {
        HuPrcVSleep();
    }
    fn_1_204(30);
    fn_1_12AE4(2);
    while (!fn_1_12B08()) {
        HuPrcVSleep();
    }
    fn_1_4090();
    fn_1_64B0();
    while (!fn_1_8B4(0x4000)) {
        HuPrcVSleep();
    }
    fn_1_8CC(2);
    fn_1_D40(2);
}

/* 427 insns */
void fn_1_C638(void)
{
    s32 mgNo;
    s32 mgIdx;
    s16 subGameNo;

    if (fn_1_8B4(1)) {
        fn_1_1A24(fn_1_15F88);
        while (!fn_1_95C(2)) {
            HuPrcVSleep();
        }
    }
    else {
        fn_1_1A24(fn_1_16018);
        while (!fn_1_95C(4)) {
            HuPrcVSleep();
        }
    }
    fn_1_8538(2, 2.0f);
    fn_1_32DC(1);
    while (lbl_1_bss_0->movieMode != 0) {
        HuPrcVSleep();
    }
    while (!fn_1_8B4(0x1000)) {
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_16080);
    while (!fn_1_95C(8)) {
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_160F0);
    while (!fn_1_95C(0x10)) {
        HuPrcVSleep();
    }
    mgNo = lbl_1_bss_4->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgNo;
    mgIdx = lbl_1_bss_4->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgIdx;
    if (mgIdx + 501 == 519) {
        subGameNo = lbl_1_bss_0->mgVariant;
        GWSubGameNoSet(subGameNo);
    }
    lbl_1_bss_4->round++;
    if (fn_1_8B4(2)) {
        fn_1_8538(0, 2.0f);
        fn_1_1A24(fn_1_16AC4);
        while (!fn_1_95C(0x800)) {
            HuPrcVSleep();
        }
        fn_1_4B4();
        fn_1_204(30);
        fn_1_D40(3);
        return;
    }
    HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
    lbl_1_bss_0->streamNo = -1;
    fn_1_3C4(mgIdx);
    fn_1_294(WIPE_TYPE_WHITEFADE, 60);
    HuTHPClose();
    HuPrcVSleep();
    while (lbl_1_bss_0->dirRead == 0) {
        HuPrcVSleep();
    }
    while (HuTHPProcCheck()) {
        HuPrcVSleep();
    }
    GwSystem.mgNo = mgNo - 501;
    GWMgUnlockSet(mgNo);
    GwSystem.mgNo = mgNo - 501;
    if (fn_1_8B4(4)) {
        GWMgInstFSet(TRUE);
    }
    else {
        GWMgInstFSet(FALSE);
    }
    omOvlCallEx(DLL_instdll, 1, 0, 0);
    while (TRUE) {
        HuPrcVSleep();
    }
}

/* 94 insns */
void fn_1_CCE4(HuVecF *vec, s32 range)
{
    vec->x += frandmod(range * 20) / 10.0f - range;
    vec->y += frandmod(range * 20) / 10.0f - range;
    vec->z += frandmod(range * 20) / 10.0f - range;
}

/* 181 insns */
void fn_1_CE5C(void)
{
    HuVecF pos;
    float rot[3];
    s32 i;

    for (i = 3; i-- != 0;) {
        rot[i] = frandmod(360);
    }
    while (fn_1_8B4(0x800000)) {
        for (i = 3; i-- != 0;) {
            rot[i] += 1.0f;
            if (rot[i] >= 360.0f) {
                rot[i] -= 360.0f;
            }
            pos = lbl_1_bss_0->effMdl[i].unk4;
            pos.y += 40.0 * sin(3.141592653589793 * rot[i] / 180.0);
            Hu3DModelPosSetV(lbl_1_bss_0->effMdl[i].mdlId, &pos);
        }
        HuPrcVSleep();
    }
    for (i = 3; i-- != 0;) {
        rot[i] += 1.0f;
        if (rot[i] >= 360.0f) {
            rot[i] -= 360.0f;
        }
        pos = lbl_1_bss_0->effMdl[i].unk4;
        pos.y += 40.0 * sin(3.141592653589793 * rot[i] / 180.0);
        lbl_1_bss_0->effMdl[i].unk4 = pos;
    }
    HuPrcEnd();
}

/* 21 insns */
void fn_1_D130(void)
{
    fn_1_87C(0x800000);
    HuPrcChildCreate(fn_1_CE5C, 99, 0x1000, 0, HuPrcCurrentGet());
}

/* 4173 insns */
/* CW inlines every small helper into this function except fn_1_4B4 (called with bl here only;
 * inlined in all its other callers). inline_max_size(32) reproduces that: fn_1_4B4 measures between 32 and 64. */
#ifdef __MWERKS__
#pragma inline_max_size(32)
#endif
void fn_1_D184(void)
{
    HuVecF fallPos[3];
    s32 winList[3];
    s32 flagMdl[3];
    HuVecF lightPosBase = { 0.0f, 50.0f, 700.0f };
    HuVecF lightDir = { 0.0f, 0.0f, -1.0f };
    HuVecF lightPos;
    HuVecF flagPos;
    s32 riseMax[3];
    s32 riseTime[3];
    s32 riseDelay[3];
    HuVecF riseOfs;
    s32 avail[3];
    s32 posFree[3];
    float floorStart[3];
    float floorEnd[3];
    float bobAngle[3];
    s32 fallMode[3];
    s32 fallWait[3];
    s32 flagMode[3];
    float flagVel[3];
    float fallSpeed[3];
    s32 flagIdx[3];
    s32 scaleTime[3];
    s32 scaleMode[3];
    HuVecF camPos;
    HuVecF camTarget;
    HuVecF bobPos;
    HuVecF flagBobPos;
    HuVecF dustPos;
    HuVecF selPos;
    s32 num;
    s8 sel[3];
    s8 order[3];
    int seNo;
    s32 place;
    s32 score;
    HU3DMODELID *mdlP;
    CAMMOTIONWORK *camMot;
    int camNum;
    s32 time;
    s32 rnd;
    s32 done;
    s32 stBTime;
    s32 stD;
    s32 stDTime;
    s32 flagDone;
    s32 endF;
    s32 found;
    s32 landNum;
    int pan0;
    int pan1;
    int pan2;
    int pan3;
    s32 place2;
    s32 score2;
    s32 best;
    s8 landSeF;

    s32 mdl;
    MGMATCH_PLAYER *player;
    HuVecF *posTbl;
    MGTIMER *timer;
    s32 camTime;
    s32 allCom;
    s32 i;
    s32 k;
    s32 cnt;
    s32 cur;
    s32 wait;
    s32 stA;
    s32 stATime;
    s32 stB;
    s32 stC;
    float t;
    float t2;
    float speed;
    float y;
    float t3;

    fn_1_898(0x100000);
    HuPrcVSleep();
    HuPrcVSleep();
    fn_1_64C(&place, &num, &score);
    num = 0;
    allCom = TRUE;
    for (i = 0; i < lbl_1_bss_4->num; i++) {
        if (lbl_1_bss_4->score[i] == score) {
            winList[num] = i;
            if (GwPlayerConf[i].type == 0) {
                allCom = FALSE;
            }
            num++;
        }
    }
    if (allCom) {
        OSReport("ALL COM!!\n");
    }
    for (i = num; i--;) {
        order[i] = i;
    }
    fn_1_140(order, num);
    if (place == 2) {
        mdlP = &lbl_1_bss_0->mdlId[58];
    }
    else {
        mdlP = &lbl_1_bss_0->mdlId[59];
    }
    for (i = 0; i < num; i++) {
        flagMdl[i] = mdlP[order[i]];
        Hu3DModelShadowSet(flagMdl[i]);
    }
    fn_1_15C74(lbl_1_bss_0->player);
    player = lbl_1_bss_0->player;
    for (i = 0; i < 4; i++, player++) {
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[10], FALSE);
    }
    fn_1_12AE4(2);
    while (!fn_1_12B08()) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_0->streamNo < 0) {
        lbl_1_bss_0->streamNo = HuAudBGMPlay(35);
    }
    fn_1_1A24(fn_1_168A4);
    if (allCom) {
        fn_1_B18(0x100);
    }
    while (!fn_1_95C(0x100)) {
        HuPrcVSleep();
    }
    fn_1_4B4();
    fn_1_3AD0();
    while (!fn_1_8B4(0x2000)) {
        HuPrcVSleep();
    }
    switch (num) {
        case 2:
            posTbl = lbl_1_data_3A8;
            for (i = num; i--;) {
                Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_0->effMdl[i].unk1C = lbl_1_data_3A8[i];
                lbl_1_bss_0->effMdl[i].unk10 = lbl_1_data_3A8[i];
                lbl_1_bss_0->effMdl[i].unk10.x += 1200.0f;
                lbl_1_bss_0->effMdl[i].unk4 = lbl_1_bss_0->effMdl[i].unk10;
                Hu3DModelRotSet(lbl_1_bss_0->effMdl[i].mdlId, 0.0f, -90.0f, 0.0f);
            }
            break;
        case 3:
            posTbl = &lbl_1_data_3A8[2];
            for (i = num; i--;) {
                Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_0->effMdl[i].unk1C = lbl_1_data_3A8[i + 2];
                lbl_1_bss_0->effMdl[i].unk10 = lbl_1_data_3A8[i + 2];
                lbl_1_bss_0->effMdl[i].unk10.x += 1200.0f;
                lbl_1_bss_0->effMdl[i].unk4 = lbl_1_bss_0->effMdl[i].unk10;
                Hu3DModelRotSet(lbl_1_bss_0->effMdl[i].mdlId, 0.0f, -90.0f, 0.0f);
            }
            break;
    }
    camMot = lbl_1_bss_0->camMot;
    camNum = 50;
    lbl_1_bss_0->camMotNum = CamMotionExPathGet(lbl_1_bss_0->mdlId[61], 6, 240.0f, 0, &camMot, &camNum);
    for (i = lbl_1_bss_0->camMotNum; i--;) {
        camMot[i].pos.y -= 100.0f;
    }
    camMot = &lbl_1_bss_0->camMot[lbl_1_bss_0->camMotNum - 1];
    lbl_1_bss_0->camMot[0].time = 0.0f;
    lbl_1_bss_0->camMot[0].fov = lbl_1_bss_4->camFov;
    lbl_1_bss_0->camMot[0].pos = lbl_1_bss_4->camPos;
    lbl_1_bss_0->camMot[0].up = lbl_1_bss_4->camUp;
    lbl_1_bss_0->camMot[0].target = lbl_1_bss_4->camTarget;
    lbl_1_bss_0->camMot[1].time = 120.0f;
    lbl_1_bss_0->camMot[1].fov = lbl_1_bss_4->camFov;
    lbl_1_bss_0->camMot[1].pos = camMot->pos;
    lbl_1_bss_0->camMot[1].up = camMot->up;
    lbl_1_bss_0->camMot[1].target = camMot->target;
    lbl_1_bss_0->camMot[1].pos.y += 350.0f;
    lbl_1_bss_0->camMot[1].pos.z += 250.0f;
    lbl_1_bss_0->camMot[1].target.y += -200.0f;
    lbl_1_bss_0->camMot[1].target.z += -300.0f;
    lbl_1_bss_0->camMotNum = 2;
    fn_1_2000();
    for (i = num; i--;) {
        flagPos = posTbl[i];
        flagPos.y = 1900.0f;
        mdl = lbl_1_bss_0->mdlId[55 + i];
        Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSetV(mdl, &flagPos);
        mdl = flagMdl[i];
        Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSetV(mdl, &flagPos);
    }
    time = 240;
    fn_1_D130();
    for (i = num; i--;) {
        rnd = frandmod(25) * 2;
        riseMax[i] = riseTime[i] = 240.0f - rnd - 5.0f;
        riseDelay[i] = frandmod(25) * 2 + 15;
        Hu3DModelAttrReset(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
    }
    seNo = HuAudFXPlayPan(0x4FD, 88);
    HuAudFXVolSet(seNo, 110);
    while (time--) {
        for (i = num; i--;) {
            if (riseTime[i] < 0) {
                continue;
            }
            if (riseTime[i] >= riseDelay[i] && riseTime[i] - riseDelay[i] < 120.0f) {
                t2 = (riseTime[i] - riseDelay[i]) / 120.0f;
                t2 = sin(M_PI * t2 / 2.0);
                t2 = sin(M_PI * t2 / 2.0);
                Hu3DModelRotSet(lbl_1_bss_0->effMdl[i].mdlId, 0.0f, -90.0f * t2, 0.0f);
            }
            t2 = 1.0f - (float)riseTime[i] / (float)riseMax[i];
            t2 = sin(M_PI * t2 / 2.0);
            t2 = sin(M_PI * t2 / 2.0);
            PSVECSubtract(&lbl_1_bss_0->effMdl[i].unk1C, &lbl_1_bss_0->effMdl[i].unk10, &riseOfs);
            PSVECScale(&riseOfs, &riseOfs, t2);
            PSVECAdd(&lbl_1_bss_0->effMdl[i].unk10, &riseOfs, &lbl_1_bss_0->effMdl[i].unk4);
            Hu3DModelPosSetV(lbl_1_bss_0->effMdl[i].mdlId, &lbl_1_bss_0->effMdl[i].unk4);
            riseTime[i]--;
        }
        if (num == 2) {
            HuAudFXPanning(seNo, (int)(24.0f * ((lbl_1_bss_0->effMdl[0].unk4.x + lbl_1_bss_0->effMdl[1].unk4.x) / 2.0f / 600.0f)) + 64);
        }
        else {
            HuAudFXPanning(seNo, (int)(24.0f * (lbl_1_bss_0->effMdl[1].unk4.x / 600.0f)) + 64);
        }
        if (180.0f == time) {
            mdl = lbl_1_bss_0->mdlId[5];
            Hu3DMotionTimeSet(mdl, Hu3DMotionMaxTimeGet(mdl) - 0.01);
            Hu3DMotionShapeTimeSet(mdl, Hu3DMotionMaxTimeGet(mdl) - 0.01);
            Hu3DMotionOverlayTimeSet(mdl, Hu3DMotionMaxTimeGet(mdl) - 0.01);
            Hu3DMotionSpeedSet(mdl, 0.1f);
            Hu3DMotionShapeSpeedSet(mdl, 0.1f);
            Hu3DMotionOverlaySpeedSet(mdl, 0.1f);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE | HU3D_MOTATTR_OVL_PAUSE);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_REV | HU3D_MOTATTR_SHAPE_REV | HU3D_MOTATTR_OVL_REV);
        }
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_16B20);
    if (allCom) {
        fn_1_B18(0x800000);
    }
    while (!fn_1_95C(0x800000)) {
        HuPrcVSleep();
    }
    if (fn_1_8B4(2)) {
        return;
    }
    timer = MgTimerCreate(0);
    for (i = 0; i < num; i++) {
        player = &lbl_1_bss_0->player[winList[i]];
        lbl_1_bss_0->charNo = player->charNo;
        for (k = num; k--;) {
            posFree[k] = k;
        }
        for (k = i; k--;) {
            posFree[sel[k]] = -1;
        }
        cnt = 0;
        for (k = 0; k < num; k++) {
            if (posFree[k] >= 0) {
                avail[cnt] = k;
                cnt++;
            }
        }
        cur = 0;
        if (!((num == 2 && i == 1) || (num == 3 && i == 2))) {
            HuPrcChildCreate(fn_1_16B7C, 100, 0x1000, 0, HuPrcCurrentGet());
            HuPrcVSleep();
            if (GwPlayerConf[player->no].type != 0) {
                lbl_1_bss_0->waitMesFlag = 0x1000000;
                HuPrcChildCreate(fn_1_9FC, 200, 0x3000, 0, HuPrcCurrentGet());
            }
            while (!fn_1_95C(0x1000000)) {
                HuPrcVSleep();
            }
            fn_1_4B4();
            MgTimerParamSet(timer, 300, 0, 0);
            MgTimerModeOnSet(timer, 1);
            MgTimerRecordDispOn(timer);
            fn_1_15DB8(player, &posTbl[avail[cur]]);
            if (GwPlayerConf[player->no].type == 0) {
                wait = 0;
                while (TRUE) {
                    if (MgTimerDoneCheck(timer) || (HuPadBtnDown[player->padNo] & PAD_BUTTON_A)) {
                        HuAudFXPlay(2);
                        break;
                    }
                    if (wait == 0) {
                        if (HuPadStkX[player->padNo] > 28.0f) {
                            if (cur < cnt - 1) {
                                cur++;
                                fn_1_15DB8(player, &posTbl[avail[cur]]);
                                wait = 15;
                                HuAudFXPlay(0);
                            }
                        }
                        else if (HuPadStkX[player->padNo] < -28.0f) {
                            if (cur > 0) {
                                cur--;
                                fn_1_15DB8(player, &posTbl[avail[cur]]);
                                wait = 15;
                                HuAudFXPlay(0);
                            }
                        }
                    }
                    else {
                        wait--;
                    }
                    HuPrcVSleep();
                }
            }
            else {
                done = FALSE;
                wait = 60;
                while (!done) {
                    if (MgTimerDoneCheck(timer)) {
                        HuAudFXPlay(2);
                        break;
                    }
                    if (wait == 0) {
                        switch ((s32)frandmod(frandmod(10) + 8)) {
                            case 0:
                                HuAudFXPlay(2);
                                done = TRUE;
                                break;
                            case 1:
                            case 2:
                                if (cur < cnt - 1) {
                                    cur++;
                                    fn_1_15DB8(player, &posTbl[avail[cur]]);
                                    HuAudFXPlay(0);
                                }
                                break;
                            case 3:
                            case 4:
                                if (cur > 0) {
                                    cur--;
                                    fn_1_15DB8(player, &posTbl[avail[cur]]);
                                    HuAudFXPlay(0);
                                }
                                break;
                        }
                        wait = 15;
                    }
                    else {
                        wait--;
                    }
                    HuPrcVSleep();
                }
            }
            if (!MgTimerDoneCheck(timer)) {
                MgTimerRecordDispOff(timer);
            }
        }
        else {
            MgTimerRecordDispOff(timer);
            fn_1_15DB8(player, &posTbl[avail[cur]]);
            fn_1_1A24(fn_1_16BFC);
            if (GwPlayerConf[player->no].type != 0) {
                fn_1_B18(0x2000000);
            }
            while (!fn_1_95C(0x2000000)) {
                HuPrcVSleep();
            }
            HuAudFXPlay(2);
            fn_1_4B4();
        }
        fn_1_15DB8(player, NULL);
        sel[i] = avail[cur];
        fn_1_74FC(player, posTbl[avail[cur]]);
        fn_1_204(30);
    }
    for (i = 0; i < num; i++) {
        OSReport("%d\n", order[i] + 2);
    }
    fn_1_204(60);
    landSeF = 0;
    stB = stC = stA = stD = 0;
    endF = FALSE;
    for (i = num; i--;) {
        scaleMode[i] = 0;
        flagMode[i] = 0;
        for (k = num; k--;) {
            if (sel[k] == i) {
                lbl_1_bss_0->effMdl[k].unk28 = winList[i];
                flagIdx[k] = i;
            }
        }
    }
    fn_1_898(0x800000);
    HuPrcVSleep();
    while (!endF) {
        switch (stA) {
            case 0:
                for (i = num; i--;) {
                    Hu3DMotionShiftSet(lbl_1_bss_0->effMdl[i].mdlId, lbl_1_bss_0->effMdl[i].unk2C, 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                    floorEnd[i] = 100.0f;
                    floorStart[i] = lbl_1_bss_0->effMdl[i].unk4.y;
                    player = &lbl_1_bss_0->player[lbl_1_bss_0->effMdl[i].unk28];
                    if (player->charNo == 6) {
                        floorEnd[i] += 30.0f;
                    }
                }
                stATime = 0;
                stA = 1;
                break;
            case 1:
                t = stATime / 60.0f;
                t = sin(M_PI * t / 2.0);
                t = sin(M_PI * t / 2.0);
                if (15.0f == stATime) {
                    stB = 1;
                }
                if (60.0f == stATime) {
                    for (i = num; i--;) {
                        lbl_1_bss_0->effMdl[i].unk4.y = floorEnd[i];
                    }
                    stA = 2;
                    stATime = 60;
                    HuPrcChildCreate(fn_1_16C7C, 100, 0x1000, 0, HuPrcCurrentGet());
                    HuPrcVSleep();
                    if (allCom) {
                        fn_1_B18(0x4000000);
                    }
                }
                else {
                    for (i = num; i--;) {
                        y = floorStart[i] + t * (floorEnd[i] - floorStart[i]);
                        lbl_1_bss_0->effMdl[i].unk4.y = y;
                    }
                    stATime++;
                }
                break;
            case 2:
                if (fn_1_95C(0x4000000) && --stATime == 0) {
                    fn_1_4B4();
                    speed = 5.6666665f;
                    stATime = 0;
                    stA = 3;
                    stC = 1;
                    HuAudFXPlay(0x2C4);
                }
                break;
            case 3:
                stATime++;
                if (300.0f == stATime) {
                    for (i = 4; i--;) {
                        found = FALSE;
                        for (k = num; k--;) {
                            if (i == winList[k]) {
                                found = TRUE;
                            }
                        }
                        if (!found) {
                            player = &lbl_1_bss_0->player[i];
                            player->pos.z = 0.0f;
                            Hu3DModelPosSetV(player->mdlId, &player->pos);
                        }
                    }
                    fn_1_28BC(3, 10);
                    stA = 4;
                }
                for (i = num; i--;) {
                    lbl_1_bss_0->effMdl[i].unk4.y += speed;
                }
                lightPos = lightPosBase;
                lightPos.y += lbl_1_bss_0->effMdl[0].unk4.y - 100.0f;
                Hu3DGLightPosSetV(lbl_1_bss_0->lightId, &lightPos, &lightDir);
                break;
            case 4:
                for (i = num; i--;) {
                    lbl_1_bss_0->effMdl[i].unk4.y += speed;
                }
                lightPos = lightPosBase;
                lightPos.y += lbl_1_bss_0->effMdl[0].unk4.y - 100.0f;
                Hu3DGLightPosSetV(lbl_1_bss_0->lightId, &lightPos, &lightDir);
                break;
            case 5:
                for (i = num; i--;) {
                    lbl_1_bss_0->effMdl[i].unk4.y += speed;
                }
                if (--stATime == 0) {
                    stC = 11;
                    for (i = num; i--;) {
                        Hu3DModelAttrSet(lbl_1_bss_0->effMdl[i].mdlId, HU3D_ATTR_DISPOFF);
                    }
                    HuAudFXStop(seNo);
                }
                break;
        }
        switch (stB) {
            case 1:
                for (i = num; i--;) {
                    player = &lbl_1_bss_0->player[winList[i]];
                    if (player->mot != 9) {
                        CharMotionShiftSet(player->charNo, player->motId[9], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                        player->mot = 9;
                    }
                }
                stBTime = 0;
                stB = 2;
                break;
            case 2:
                t3 = stBTime / 30.0f;
                for (i = num; i--;) {
                    player = &lbl_1_bss_0->player[winList[i]];
                    if (player->charNo == 6) {
                        player->pos.y = 30.0f * t3;
                    }
                }
                stBTime++;
                if (30.0f == stBTime) {
                    for (i = num; i--;) {
                        player = &lbl_1_bss_0->player[winList[i]];
                        if (GwPlayerConf[player->no].type == 0) {
                            omVibrate(player->no, 12, 4, 2);
                        }
                    }
                    stB = 10;
                }
                break;
            case 10:
                landNum = 0;
                for (i = num; i--;) {
                    player = &lbl_1_bss_0->player[winList[i]];
                    switch (fallMode[i]) {
                        case 0:
                            player->pos.y = lbl_1_bss_0->effMdl[sel[i]].unk4.y - 100.0f;
                            break;
                        case 1:
                            if (fallWait[i] < 0) {
                                player->pos.y -= fallSpeed[i] / 100.0f;
                                if (fallSpeed[i] <= 8400.0f) {
                                    fallSpeed[i] += 140.0f;
                                }
                                if (player->pos.y < 0.0f) {
                                    fallMode[i] = 2;
                                    player->pos.y = 0.0f;
                                    if (!landSeF) {
                                        HuAudFXPlayPan(0x4FF, 64);
                                        landSeF = 1;
                                    }
                                    if (player->mot != 7) {
                                        CharMotionShiftSet(player->charNo, player->motId[7], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
                                        player->mot = 7;
                                    }
                                    if (GwPlayerConf[player->no].type == 0) {
                                        omVibrate(player->no, 45, 4, 2);
                                    }
                                }
                            }
                            else {
                                fallWait[i]--;
                            }
                            break;
                        case 2:
                            if (fallMode[i] == 2) {
                                landNum++;
                            }
                            break;
                    }
                }
                if (landNum == num) {
                    stB = 11;
                    stC = 10;
                    camTime = 30;
                    stA = 5;
                    stATime = 90;
                }
                break;
        }
        switch (stC) {
            case 1:
                stC = 2;
                camTime = 20;
                break;
            case 2:
                if (--camTime == 0) {
                    stC = 3;
                }
                break;
            case 3:
                lbl_1_bss_0->camMot[0].time = 0.0f;
                lbl_1_bss_0->camMot[0].fov = lbl_1_bss_4->camFov;
                lbl_1_bss_0->camMot[0].pos = lbl_1_bss_0->camMot[1].pos;
                lbl_1_bss_0->camMot[0].up = lbl_1_bss_0->camMot[1].up;
                lbl_1_bss_0->camMot[0].target = lbl_1_bss_0->camMot[1].target;
                lbl_1_bss_0->camMot[1].time = 280.0f;
                lbl_1_bss_0->camMot[1].target.y = 2100.0f;
                lbl_1_bss_0->camMot[1].pos.y = 1600.0f;
                lbl_1_bss_0->camMotNum = 2;
                fn_1_2000();
                stC = 4;
                break;
            case 10:
                camPos = lbl_1_bss_0->camMot[1].pos;
                camTarget = lbl_1_bss_0->camMot[1].target;
                if (camTime != 0) {
                    camTime--;
                    fn_1_CCE4(&camPos, 30);
                    fn_1_CCE4(&camTarget, 30);
                }
                Hu3DCameraPosSetV(HU3D_CAM4, &camPos, &lbl_1_bss_0->camMot[1].up, &camTarget);
                break;
            case 11:
                lbl_1_bss_0->camMot[0].time = 0.0f;
                lbl_1_bss_0->camMot[0].fov = lbl_1_bss_4->camFov;
                lbl_1_bss_0->camMot[0].pos = lbl_1_bss_0->camMot[1].pos;
                lbl_1_bss_0->camMot[0].up = lbl_1_bss_0->camMot[1].up;
                lbl_1_bss_0->camMot[0].target = lbl_1_bss_0->camMot[1].target;
                lbl_1_bss_0->camMot[1].time = 30.0f;
                lbl_1_bss_0->camMot[1].target.y = -500.0f;
                lbl_1_bss_0->camMot[1].pos.y = 800.0f;
                lightPos = lightPosBase;
                Hu3DGLightPosSetV(lbl_1_bss_0->lightId, &lightPos, &lightDir);
                lbl_1_bss_0->camMotNum = 2;
                fn_1_2000();
                stC = 12;
                break;
        }
        switch (stD) {
            case 0:
                for (i = num; i--;) {
                    bobAngle[i] = frandmod(360);
                    flagMode[i] = 0;
                    fallMode[i] = 0;
                }
                stD = 1;
                stDTime = 20;
                break;
            case 1:
                for (i = num; i--;) {
                    if (flagMode[i] >= 1) {
                        continue;
                    }
                    bobPos = posTbl[i];
                    bobPos.y = 1900.0 + 40.0 * sin(M_PI * bobAngle[i] / 180.0);
                    flagBobPos = bobPos;
                    flagBobPos.y -= 40.0f;
                    flagBobPos.z += 30.0f;
                    Hu3DModelPosSetV(lbl_1_bss_0->mdlId[55 + i], &bobPos);
                    Hu3DModelPosSetV(flagMdl[i], &flagBobPos);
                    switch (flagMode[i]) {
                        case 0:
                            if (100.0f + (220.0f + lbl_1_bss_0->effMdl[i].unk4.y) >= bobPos.y) {
                                Hu3DModelAttrReset(lbl_1_bss_0->mdlId[55 + i], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                                flagMode[i] = -1;
                            }
                            break;
                        case -1:
                            if (220.0f + lbl_1_bss_0->effMdl[i].unk4.y >= bobPos.y) {
                                player = &lbl_1_bss_0->player[lbl_1_bss_0->effMdl[i].unk28];
                                if (player->mot != 10) {
                                    CharMotionShiftSet(player->charNo, player->motId[10], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                                    player->mot = 10;
                                }
                                Hu3DMotionAttrSet(player->motId[10], 1);
                                fn_1_974(player, 3);
                                if (GwPlayerConf[player->no].type == 0) {
                                    omVibrate(player->no, 23, 4, 2);
                                }
                                fallMode[flagIdx[i]] = 1;
                                fallWait[flagIdx[i]] = 30;
                                fallSpeed[flagIdx[i]] = 700.0f;
                                Hu3DMotionShiftSet(lbl_1_bss_0->effMdl[i].mdlId, lbl_1_bss_0->effMdl[i].unk2A, 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                                pan0 = 64.0f + 24.0f * (lbl_1_bss_0->effMdl[i].unk4.x / 350.0f);
                                OSReport("\225\227\221D SE Panning : %d\n", pan0);
                                HuAudFXPlayPan(0x4FE, pan0);
                                Hu3DModelAttrReset(flagMdl[i], HU3D_ATTR_DISPOFF);
                                Hu3DModelScaleSet(flagMdl[i], 0.0f, 0.0f, 0.0f);
                                scaleTime[i] = 20;
                                scaleMode[i] = 1;
                                flagMode[i] = 1;
                                fallPos[i] = flagBobPos;
                                flagVel[i] = -2.0f;
                            }
                            break;
                    }
                    bobAngle[i] += 1.0f;
                }
                break;
        }
        flagDone = 0;
        for (i = num; i--;) {
            switch (scaleMode[i]) {
                case 1:
                    scaleTime[i]--;
                    if (scaleTime[i] == 0) {
                        scaleMode[i] = 10;
                        scaleTime[i] = 10;
                    }
                    break;
                case 10:
                    t = (30.0f - scaleTime[i]) / 30.0f;
                    t = sin(M_PI * t / 2.0);
                    t *= 2.0f;
                    scaleTime[i]--;
                    if (scaleTime[i] == 0) {
                        scaleMode[i] = 11;
                        scaleTime[i] = 5;
                    }
                    Hu3DModelScaleSet(flagMdl[i], t, t, t);
                    break;
                case 11:
                    scaleTime[i]--;
                    if (scaleTime[i] == 0) {
                        scaleMode[i] = 20;
                        scaleTime[i] = 20;
                    }
                    break;
                case 20:
                    t = scaleTime[i] / 30.0f;
                    t = sin(M_PI * t / 2.0);
                    t += 1.0f;
                    scaleTime[i]--;
                    if (scaleTime[i] == 0) {
                        scaleMode[i] = 30;
                    }
                    Hu3DModelScaleSet(flagMdl[i], t, t, t);
                    break;
            }
            switch (flagMode[i]) {
                case 1:
                    fallPos[i].y -= flagVel[i];
                    if (flagVel[i] < 3.0f) {
                        if (fallPos[i].z < 100.0f + posTbl[i].z) {
                            fallPos[i].z += 1.0f;
                        }
                        flagVel[i] += 0.03f;
                    }
                    else {
                        flagVel[i] += 1.0f;
                        if (fallPos[i].z > 30.0f + posTbl[i].z) {
                            fallPos[i].z -= 1.0f;
                        }
                    }
                    if (flagVel[i] >= 30.0f) {
                        flagVel[i] = 30.0f;
                    }
                    player = &lbl_1_bss_0->player[lbl_1_bss_0->effMdl[i].unk28];
                    if (fallPos[i].y < lbl_1_data_3E4[player->charNo]) {
                        if (GwPlayerConf[player->no].type == 0) {
                            omVibrate(player->no, 23, 4, 2);
                        }
                        pan1 = 64.0f + 24.0f * (fallPos[i].x / 350.0f);
                        OSReport("\220\224\216\232 SE Panning 1 : %d\n", pan1);
                        HuAudFXPlayPan(0x500, pan1);
                        fallPos[i].y = lbl_1_data_3E4[player->charNo];
                        flagVel[i] = -5.0f;
                        flagMode[i] = 2;
                        mdl = lbl_1_bss_0->mdlId[34 + i];
                        Hu3DModelPosSet(mdl, fallPos[i].x, 30.0f + fallPos[i].y, fallPos[i].z);
                        Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
                        Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
                    }
                    Hu3DModelPosSetV(flagMdl[i], &fallPos[i]);
                    break;
                case 2:
                    fallPos[i].z -= 1.6f;
                    fallPos[i].y -= flagVel[i];
                    if (flagVel[i] < 0.0f) {
                        flagVel[i] += 0.2f;
                    }
                    else {
                        flagVel[i] += 0.2f;
                    }
                    if (flagVel[i] >= 30.0f) {
                        flagVel[i] = 30.0f;
                    }
                    if (fallPos[i].y < 10.0f) {
                        pan2 = 64.0f + 24.0f * (fallPos[i].x / 350.0f);
                        OSReport("\220\224\216\232 SE Panning 2 : %d\n", pan2);
                        HuAudFXPlayVolPan(0x500, 100, pan2);
                        fallPos[i].y = 10.0f;
                        flagVel[i] = -3.0f;
                        flagMode[i] = 3;
                    }
                    Hu3DModelPosSetV(flagMdl[i], &fallPos[i]);
                    break;
                case 3:
                    fallPos[i].z -= 1.6f;
                    fallPos[i].y -= flagVel[i];
                    if (flagVel[i] < 0.0f) {
                        flagVel[i] += 0.2f;
                    }
                    else {
                        flagVel[i] += 0.2f;
                    }
                    if (flagVel[i] >= 30.0f) {
                        flagVel[i] = 30.0f;
                    }
                    Hu3DModelPosSetV(flagMdl[i], &fallPos[i]);
                    if (fallPos[i].y < 10.0f) {
                        pan3 = 64.0f + 24.0f * (fallPos[i].x / 350.0f);
                        OSReport("\220\224\216\232 SE Panning 3 : %d\n", pan3);
                        HuAudFXPlayVolPan(0x500, 80, pan3);
                        fallPos[i].y = 10.0f;
                        flagMode[i] = 10;
                        flagVel[i] = 1.0f;
                        Hu3DModelPosSetV(flagMdl[i], &fallPos[i]);
                    }
                    break;
                case 10:
                    fallPos[i].y -= flagVel[i];
                    flagVel[i] += 0.06f;
                    if (flagVel[i] >= 2.0f) {
                        flagVel[i] = 2.0f;
                    }
                    if (fallPos[i].y < -90.0f) {
                        dustPos = fallPos[i];
                        dustPos.y = 0.0f;
                        CharModelLandDustCreate(0, &dustPos);
                        fallPos[i].y = -90.0f;
                        flagMode[i] = 11;
                    }
                    Hu3DModelRotSet(flagMdl[i], fallPos[i].y, 0.0f, 0.0f);
                    break;
                case 11:
                    flagDone++;
                    break;
            }
        }
        if (flagDone == num) {
            endF = TRUE;
        }
        for (i = num; i--;) {
            Hu3DModelPosSetV(lbl_1_bss_0->effMdl[i].mdlId, &lbl_1_bss_0->effMdl[i].unk4);
            player = &lbl_1_bss_0->player[winList[i]];
            Hu3DModelPosSetV(player->mdlId, &player->pos);
        }
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_16CD8);
    if (allCom) {
        fn_1_B18(0x8000000);
    }
    while (!fn_1_95C(0x8000000)) {
        HuPrcVSleep();
    }
    fn_1_4B4();
    fn_1_204(60);
    fn_1_294(WIPE_TYPE_WHITEFADE, 60);
    mdl = lbl_1_bss_0->mdlId[5];
    Hu3DMotionTimeSet(mdl, Hu3DMotionMaxTimeGet(mdl));
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_REV);
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(mdl, 1.0f);
    fn_1_64C(&place2, &num, &score2);
    if (num == 2) {
        if (place2 == 2) {
            for (i = 0; i < lbl_1_bss_4->num; i++) {
                if (lbl_1_bss_4->score[i] < score2) {
                    lbl_1_bss_4->unk20[3] = i;
                }
                else if (lbl_1_bss_4->score[i] > score2) {
                    lbl_1_bss_4->unk20[0] = i;
                }
            }
            if (order[sel[0]] == 0) {
                lbl_1_bss_4->unk20[1] = winList[0];
                lbl_1_bss_4->unk20[2] = winList[1];
            }
            else {
                lbl_1_bss_4->unk20[1] = winList[1];
                lbl_1_bss_4->unk20[2] = winList[0];
            }
        }
        else {
            best = score2;
            for (i = 0; i < lbl_1_bss_4->num; i++) {
                if (lbl_1_bss_4->score[i] != score2) {
                    if (lbl_1_bss_4->score[i] > best) {
                        if (best != score2) {
                            lbl_1_bss_4->unk20[1] = lbl_1_bss_4->unk20[0];
                        }
                        lbl_1_bss_4->unk20[0] = i;
                        best = lbl_1_bss_4->score[i];
                    }
                    else {
                        lbl_1_bss_4->unk20[1] = i;
                    }
                }
            }
            if (order[sel[0]] == 0) {
                lbl_1_bss_4->unk20[2] = winList[0];
                lbl_1_bss_4->unk20[3] = winList[1];
            }
            else {
                lbl_1_bss_4->unk20[2] = winList[1];
                lbl_1_bss_4->unk20[3] = winList[0];
            }
        }
    }
    else {
        for (i = 0; i < num; i++) {
            lbl_1_bss_4->unk20[order[sel[i]] + 1] = winList[i];
        }
        for (i = 0; i < lbl_1_bss_4->num; i++) {
            if (lbl_1_bss_4->score[i] > score2) {
                lbl_1_bss_4->unk20[0] = i;
                break;
            }
        }
    }
    for (i = 0; i < lbl_1_bss_4->num; i++) {
        OSReport("Rank %d : Player %d\n", i, lbl_1_bss_4->unk20[i]);
    }
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_4->camFov, 20.0f, 60000.0f, 1.2f);
    player = lbl_1_bss_0->player;
    for (i = 0; i < 4; i++, player++) {
        player->pos = lbl_1_data_30[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 1.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[10], TRUE);
    }
    lbl_1_bss_0->guidePos = lbl_1_data_60[1];
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, 45.0f, 0.0f);
    for (i = 0; i < num; i++) {
        Hu3DModelAttrSet(flagMdl[i], HU3D_ATTR_DISPOFF);
    }
    fn_1_240(WIPE_TYPE_PREVTYPE, 60);
}

#ifdef __MWERKS__
/* back to CW's default; `#pragma inline_max_size reset` is silently a no-op */
#pragma inline_max_size(256)
#endif

/* 797 insns */
void fn_1_112B8(void)
{
    s32 charNo[4];
    s32 playerNo[4];
    MGMATCH_PLAYER *player;
    int i;
    fn_1_294(6, 60);
    for (i = 4; i--;) {
        charNo[i] = lbl_1_bss_0->player[i].charNo;
    }
    fn_1_898(0x80000);
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_4->camFov, 20.0f, 60000.0f, 1.2f);
    Hu3DModelAttrSet(lbl_1_bss_0->unk118, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->guideMdlId, HU3D_ATTR_DISPOFF);
    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    switch (lbl_1_bss_4->gameType) {
        case MGMATCH_GAMETYPE_4P:
            fn_1_13C1C(lbl_1_bss_4->winner, lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, lbl_1_bss_4->unk20, charNo);
            break;
        case MGMATCH_GAMETYPE_2VS2:
            if (lbl_1_bss_4->winner == 0) {
                playerNo[0] = 0;
                playerNo[1] = 1;
                playerNo[2] = 2;
                playerNo[3] = 3;
                fn_1_13C1C(0, lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, playerNo, charNo);
            }
            else {
                playerNo[0] = 2;
                playerNo[1] = 3;
                playerNo[2] = 0;
                playerNo[3] = 1;
                fn_1_13C1C(1, lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, playerNo, charNo);
            }
            break;
        case MGMATCH_GAMETYPE_1VS3:
            if (lbl_1_bss_4->winner == 0) {
                playerNo[0] = 0;
                playerNo[1] = 1;
                playerNo[2] = 2;
                playerNo[3] = 3;
                fn_1_13C1C(0, lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, playerNo, charNo);
            }
            else {
                playerNo[0] = 1;
                playerNo[1] = 2;
                playerNo[2] = 3;
                playerNo[3] = 0;
                fn_1_13C1C(1, lbl_1_bss_4->gameType, lbl_1_bss_4->winsNeeded, playerNo, charNo);
            }
            break;
    }
    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        Hu3DModelAttrSet(player->mdlId, HU3D_ATTR_DISPOFF);
    }
    fn_1_4B4();
    if (lbl_1_bss_0->streamNo < 0) {
        lbl_1_bss_0->streamNo = HuAudBGMPlay(MSM_STREAM_MGTOUR_END);
    }
    fn_1_240(5, 60);
    player = &lbl_1_bss_0->player[0];
    switch (lbl_1_bss_4->gameType) {
        case MGMATCH_GAMETYPE_4P:
            for (i = 0; i < 4; i++) {
                OSReport("[No : %d] Rank %d\n", i, lbl_1_bss_4->unk20[i]);
                player = &lbl_1_bss_0->player[lbl_1_bss_4->unk20[i]];
                switch (i) {
                    case 0:
                        if (player->mot != 3) {
                            CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                            player->mot = 3;
                        }
                        break;
                    case 1:
                        if (player->mot != 0) {
                            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                            player->mot = 0;
                        }
                        break;
                    case 2:
                        if (player->mot != 4) {
                            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                            player->mot = 4;
                        }
                        break;
                    case 3:
                        if (player->mot != 4) {
                            CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                            player->mot = 4;
                        }
                        break;
                }
            }
            break;
        case MGMATCH_GAMETYPE_2VS2:
            if (lbl_1_bss_4->winner == 0) {
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
            }
            else {
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
            }
            break;
        case MGMATCH_GAMETYPE_1VS3:
            if (lbl_1_bss_4->winner == 0) {
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
            }
            else {
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 4;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
                if (player->mot != 3) {
                    CharMotionShiftSet(player->charNo, player->motId[3], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                    player->mot = 3;
                }
                player++;
            }
            break;
    }
    while (!fn_1_8B4(0x20000)) {
        HuPrcVSleep();
    }
    fn_1_1A24(fn_1_16A48);
    while (!fn_1_95C(0x400)) {
        HuPrcVSleep();
    }
    if (fn_1_8B4(0x10)) {
        HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
        lbl_1_bss_0->streamNo = -1;
        fn_1_294(6, 60);
        fn_1_3560();
    }
    else {
        fn_1_D40(3);
    }
    fn_1_898(0x400000);
}

/* 310 insns */
void fn_1_11F2C(void)
{
    HuVecF pos;
    CAMMOTIONWORK *camMot;
    int camMotNum;
    int i;
    float scale;
    camMot = &lbl_1_bss_0->camMot[1];
    camMotNum = 50;
    lbl_1_bss_0->camMotNum = CamMotionExPathGet(lbl_1_bss_0->mdlId[62], 6, 120.0f, 0, &camMot, &camMotNum);
    lbl_1_bss_0->camMot[0].time = 0.0f;
    lbl_1_bss_0->camMot[0].pos = lbl_1_bss_4->camPos;
    lbl_1_bss_0->camMot[0].up = lbl_1_bss_4->camUp;
    lbl_1_bss_0->camMot[0].target = lbl_1_bss_4->camTarget;
    lbl_1_bss_0->camMot[0].fov = lbl_1_bss_4->camFov;
    lbl_1_bss_0->camMot[1].time = 1.0f;
    lbl_1_bss_0->camMot[2].time = 120.0f;
    lbl_1_bss_0->camMotNum++;
    lbl_1_data_1C4[0] = lbl_1_bss_0->camMot[2].target.x - 9000.0f;
    lbl_1_data_1C4[1] = 18000.0f + lbl_1_bss_0->camMot[2].target.y;
    lbl_1_data_1C4[2] = 5000.0f + lbl_1_bss_0->camMot[2].target.z;
    lbl_1_data_60[2].x = 0.5f * lbl_1_bss_0->camMot[2].target.x;
    lbl_1_data_60[2].y = 0.5f * lbl_1_bss_0->camMot[2].target.y;
    lbl_1_data_60[2].z = 0.5f * lbl_1_bss_0->camMot[2].target.z;
    HuAudFXPlay(0x49D);
    fn_1_1F00();
    fn_1_676C();
    fn_1_28BC(2, 180);
    fn_1_204(30);
    for (i = 30; i--;) {
        scale = i / 30.0f;
        Hu3DModelTPLvlSet(lbl_1_bss_0->guideMdlId, scale);
        Hu3DModelScaleSet(lbl_1_bss_0->guideMdlId, scale, scale, scale);
        HuPrcVSleep();
    }
    pos.x = 600.0f;
    pos.y = 100.0f;
    pos.z = 14000.0f;
    Hu3D2Dto3D(&pos, HU3D_CAM4, &pos);
    OSReport("%3.3f, %3.3f, %3.3f\n", pos.x, pos.y, pos.z);
}

