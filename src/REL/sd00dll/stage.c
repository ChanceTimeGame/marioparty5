/*
 * sd00dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/stage.s.
 */

#include "REL/sd00dll.h"

/* CW: HuAudFXPlay / HuAudFXStop are called unprototyped (SdStageCreate's result copies);
 * SdStageMachineCol / StageObjCol need HuAudFXPlayVolPan's s16 prototype. */
#ifndef __MWERKS__
#include "game/audio.h"
#else
int HuAudFXPlayVolPan(int seId, s16 vol, s16 pan);
void HuAudAUXSet(s32 auxA, s32 auxB);
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "math.h"
#include "string.h"
#include "game/mg/seqman.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_D90 = 75.0f; /* 0xD90 */
/* 0xD94 lbl_1_rodata_D94 (0xC): 0xC61C4000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xDA0 lbl_1_rodata_DA0 (0xC): 0x00000000 0x00000000 0x3CF5C28F -- an aggregate initialiser, write it as a local */
/* 0xDAC lbl_1_rodata_DAC (0xC): 0x00000000 0x00000000 0x3CF5C28F -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_DB8 = -0.005f; /* 0xDB8 */
static const float lbl_1_rodata_DBC = 320.0f; /* 0xDBC */
static const float lbl_1_rodata_DC0 = 0.0f; /* 0xDC0 */
static const float lbl_1_rodata_DC4 = 480.0f; /* 0xDC4 */
static const float lbl_1_rodata_DC8 = 1.0f; /* 0xDC8 */
static const float lbl_1_rodata_DCC = 60.0f; /* 0xDCC */
static const float lbl_1_rodata_DD0 = 20.0f; /* 0xDD0 */
static const float lbl_1_rodata_DD4 = 35000.0f; /* 0xDD4 */
static const float lbl_1_rodata_DD8 = 0.6f; /* 0xDD8 */
static const float lbl_1_rodata_DDC = 0.1f; /* 0xDDC */
static const float lbl_1_rodata_DE0 = 0.04f; /* 0xDE0 */
/* 0xDE8 lbl_1_rodata_DE8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_DF0 = 180.0f; /* 0xDF0 */
static const float lbl_1_rodata_DF4 = 360.0f; /* 0xDF4 */
static const float lbl_1_rodata_DF8 = -180.0f; /* 0xDF8 */
static const float lbl_1_rodata_DFC = 0.0125f; /* 0xDFC */
static const float lbl_1_rodata_E00 = 0.025f; /* 0xE00 */
static const float lbl_1_rodata_E04 = 2.0f; /* 0xE04 */
/* 0xE08 lbl_1_rodata_E08 (0xC): 0x3F800000 0xBF800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xE14 lbl_1_rodata_E14 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE20 lbl_1_rodata_E20 (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE2C lbl_1_rodata_E2C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE38 lbl_1_rodata_E38 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_E44 = 90.0f; /* 0xE44 */
static const float lbl_1_rodata_E48 = 24.0f; /* 0xE48 */
static const float lbl_1_rodata_E4C = 100.0f; /* 0xE4C */
static const float lbl_1_rodata_E50 = 50.0f; /* 0xE50 */
static const float lbl_1_rodata_E54 = 127.0f; /* 0xE54 */
static const float lbl_1_rodata_E58 = 48.0f; /* 0xE58 */
static const float lbl_1_rodata_E5C = 150.0f; /* 0xE5C */
static const float lbl_1_rodata_E60 = 300.0f; /* 0xE60 */
static const float lbl_1_rodata_E64 = 3.0f; /* 0xE64 */
/* 0xE68 lbl_1_rodata_E68 (0xC): 0x3F800000 0xBF800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xE74 lbl_1_rodata_E74 (0xC): lbl_1_data_1860 lbl_1_data_1862 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE80 lbl_1_rodata_E80 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xE81 lbl_1_rodata_E81 (0x3): 0x00, 0x00, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xE84 lbl_1_rodata_E84 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xE90 lbl_1_rodata_E90 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xE9C lbl_1_rodata_E9C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xEA8 lbl_1_rodata_EA8 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xEB4 lbl_1_rodata_EB4 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xEC0 lbl_1_rodata_EC0 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xECC lbl_1_rodata_ECC (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xED8 lbl_1_rodata_ED8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xEE4 lbl_1_rodata_EE4 (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_EF0 = 0.5f; /* 0xEF0 */
static const float lbl_1_rodata_EF4 = -10000.0f; /* 0xEF4 */
/* 0xEF8 lbl_1_rodata_EF8 (0x18): 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xF10 lbl_1_rodata_F10 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xF1C lbl_1_rodata_F1C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xF28 lbl_1_rodata_F28 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xF34 lbl_1_rodata_F34 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_F40 = 0.05f; /* 0xF40 */
static const float lbl_1_rodata_F44 = -0.25f; /* 0xF44 */
static const float lbl_1_rodata_F48 = 1.5f; /* 0xF48 */
static const float lbl_1_rodata_F4C = 10.0f; /* 0xF4C */
static const float lbl_1_rodata_F50 = -50.0f; /* 0xF50 */
static const float lbl_1_rodata_F54 = 1.06f; /* 0xF54 */
static const float lbl_1_rodata_F58 = 45.0f; /* 0xF58 */
static const float lbl_1_rodata_F5C = 65.0f; /* 0xF5C */
static const double lbl_1_rodata_F60 = 180.0; /* 0xF60 */
static const double lbl_1_rodata_F68 = 3.141592653589793; /* 0xF68 */
static const float lbl_1_rodata_F70 = 0.017453292f; /* 0xF70 */
static const float lbl_1_rodata_F74 = 120.0f; /* 0xF74 */
static const float lbl_1_rodata_F78 = -1.0f; /* 0xF78 */
static const float lbl_1_rodata_F7C = -5000.0f; /* 0xF7C */
static const float lbl_1_rodata_F80 = 25.0f; /* 0xF80 */
static const float lbl_1_rodata_F84 = 2400.0f; /* 0xF84 */
static const float lbl_1_rodata_F88 = 4800.0f; /* 0xF88 */
/* 0xF8C lbl_1_rodata_F8C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xF98 lbl_1_rodata_F98 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xFA4 lbl_1_rodata_FA4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_FB0 = 10000.0f; /* 0xFB0 */
/* 0xFB4 lbl_1_rodata_FB4 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xFC0 lbl_1_rodata_FC0 (0xC): 0xBF800000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xFCC lbl_1_rodata_FCC (0xC): 0x3F800000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xFD8 lbl_1_rodata_FD8 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
/* 0xFE4 lbl_1_rodata_FE4 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_FF0 = 2350.0f; /* 0xFF0 */
static const float lbl_1_rodata_FF4 = -2350.0f; /* 0xFF4 */
/* 0xFF8 lbl_1_rodata_FF8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1004 lbl_1_rodata_1004 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1010 = -40.0f; /* 0x1010 */
/* 0x1014 lbl_1_rodata_1014 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1020 lbl_1_rodata_1020 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_102C = -25.0f; /* 0x102C */
/* 0x1030 lbl_1_rodata_1030 (0x10): 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1040 lbl_1_rodata_1040 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x1048 lbl_1_rodata_1048 (0x10): 0x3F34FDF4 0x00000000 0xBF34FDF4 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_1058 = 1.0; /* 0x1058 */
static const float lbl_1_rodata_1060 = 4.0f; /* 0x1060 */
static const double lbl_1_rodata_1068 = 0.5; /* 0x1068 */
static const float lbl_1_rodata_1070 = 0.25f; /* 0x1070 */
/* 0x1074 lbl_1_rodata_1074 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1080 lbl_1_rodata_1080 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x108C lbl_1_rodata_108C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1098 = 1000.0f; /* 0x1098 */
static const float lbl_1_rodata_109C = 2450.0f; /* 0x109C */
static const float lbl_1_rodata_10A0 = 3600.0f; /* 0x10A0 */
static const float lbl_1_rodata_10A4 = 1800.0f; /* 0x10A4 */
/* 0x10A8 lbl_1_rodata_10A8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x10B4 lbl_1_rodata_10B4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_10C0 = 450.0f; /* 0x10C0 */
static const float lbl_1_rodata_10C4 = 15.0f; /* 0x10C4 */
static const float lbl_1_rodata_10C8 = 0.01f; /* 0x10C8 */
/* 0x10CC lbl_1_rodata_10CC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x10D8 lbl_1_rodata_10D8 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x10E4 lbl_1_rodata_10E4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_10F0 = 200.0f; /* 0x10F0 */
static const float lbl_1_rodata_10F4 = 12.0f; /* 0x10F4 */
static const float lbl_1_rodata_10F8 = 660.0f; /* 0x10F8 */
static const float lbl_1_rodata_10FC = 900.0f; /* 0x10FC */
/* 0x1100 lbl_1_rodata_1100 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x110C lbl_1_rodata_110C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1118 lbl_1_rodata_1118 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x1124 lbl_1_rodata_1124 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x1130 lbl_1_rodata_1130 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_113C = 5.0f; /* 0x113C */
/* 0x1140 lbl_1_rodata_1140 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x114C lbl_1_rodata_114C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x1158 lbl_1_rodata_1158 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1164 lbl_1_rodata_1164 (0xC): 0x00000000 0x447A0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1170 lbl_1_rodata_1170 (0xC): 0x3F800000 0xBF800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x117C lbl_1_rodata_117C (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x117D lbl_1_rodata_117D (0x3): 0xFF, 0xFF, 0x80 -- an aggregate initialiser, write it as a local */
/* 0x1180 lbl_1_rodata_1180 (0xC): 0x00000000 0x447A0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x118C lbl_1_rodata_118C (0xC): 0x00000000 0xBF800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x1198 lbl_1_rodata_1198 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x1199 lbl_1_rodata_1199 (0x3): 0x80, 0x00, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x119C lbl_1_rodata_119C (0xC): 0x00000000 0x453B8000 0xC5DAC000 -- an aggregate initialiser, write it as a local */
/* 0x11A8 lbl_1_rodata_11A8 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x11B4 lbl_1_rodata_11B4 (0xC): 0x00000000 0xC53B8000 0x45DAC000 -- an aggregate initialiser, write it as a local */
/* 0x11C0 lbl_1_rodata_11C0 (0xC): 0x00000000 0x453B8000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x11CC lbl_1_rodata_11CC (0xC): 0x00000000 0x447A0000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_11D8 = 3000.0f; /* 0x11D8 */
static const float lbl_1_rodata_11DC = 0.95f; /* 0x11DC */
/* 0x11E0 lbl_1_rodata_11E0 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_11E4 = -0.02f; /* 0x11E4 */
static const float lbl_1_rodata_11E8 = 640.0f; /* 0x11E8 */
static const float lbl_1_rodata_11EC = 1.2f; /* 0x11EC */
static const float lbl_1_rodata_11F0 = -0.5f; /* 0x11F0 */
static const float lbl_1_rodata_11F4 = 0.8f; /* 0x11F4 */
/* 0x11F8 lbl_1_rodata_11F8 (0x20): 0x00000010 0x00000020 0x00000030 0x00000040 0x00000020 0x00000020 0x00000030 0x00000040 -- an aggregate initialiser, write it as a local */
/* 0x1218 lbl_1_rodata_1218 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1224 lbl_1_rodata_1224 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1230 lbl_1_rodata_1230 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x123C lbl_1_rodata_123C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1248 lbl_1_rodata_1248 (0xC): 0x43960000 0x00000000 0x43960000 -- an aggregate initialiser, write it as a local */
/* 0x1254 lbl_1_rodata_1254 (0xC): 0x45834000 0x00000000 0x45834000 -- an aggregate initialiser, write it as a local */
/* 0x1260 lbl_1_rodata_1260 (0xC): 0x44610000 0x00000000 0x44610000 -- an aggregate initialiser, write it as a local */
/* 0x126C lbl_1_rodata_126C (0xC): 0x45610000 0x00000000 0x45610000 -- an aggregate initialiser, write it as a local */
/* 0x1278 lbl_1_rodata_1278 (0xC): 0x44610000 0x00000000 0x45610000 -- an aggregate initialiser, write it as a local */
/* 0x1284 lbl_1_rodata_1284 (0xC): 0x45610000 0x00000000 0x44610000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1290 = 800.0f; /* 0x1290 */
static const float lbl_1_rodata_1294 = 2.6f; /* 0x1294 */
static const float lbl_1_rodata_1298 = 600.0f; /* 0x1298 */
static const float lbl_1_rodata_129C = 1.6f; /* 0x129C */
static const float lbl_1_rodata_12A0 = 22.5f; /* 0x12A0 */
/* 0x12A4 lbl_1_rodata_12A4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12B0 lbl_1_rodata_12B0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12BC lbl_1_rodata_12BC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12C8 lbl_1_rodata_12C8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12D4 lbl_1_rodata_12D4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12E0 lbl_1_rodata_12E0 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x12E1 lbl_1_rodata_12E1 (0x3): 0x00, 0x00, 0x80 -- an aggregate initialiser, write it as a local */
/* 0x12E4 lbl_1_rodata_12E4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12F0 lbl_1_rodata_12F0 (0xC): 0x00000000 0xC1200000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x12FC lbl_1_rodata_12FC (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x12FD lbl_1_rodata_12FD (0x3): 0x00, 0x00, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1300 = 6.0f; /* 0x1300 */
static const float lbl_1_rodata_1304 = 30.0f; /* 0x1304 */
static const float lbl_1_rodata_1308 = 1.01f; /* 0x1308 */
static const float lbl_1_rodata_130C = 0.995f; /* 0x130C */
static const float lbl_1_rodata_1310 = 0.98f; /* 0x1310 */
static const float lbl_1_rodata_1314 = 0.9f; /* 0x1314 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x240 */ static SDSTAGEWORK stageWork;
/* 0x23C */ static s8 *stageTrialMap; /* 16 x 16 tiles [z * 16 + x]: type << 4 | height (lbzx + extsb) */
/* 0x238 */ static u8 *stageTrialMapColType;
/* 0x234 */ static SDTRIALVTXCELL *stageTrialMapHeight;
/* 0x230 */ static SDTRIALNRMCELL *stageTrialMapNum;
/* 0x22C */ static SDSTAGECOLMESH *stageColMesh; /* HuMemDirectMallocNum(0x15A800) */
/* 0x228 */ static SDSTAGECOLMESH *stageColWall;
/* 0x224 */ static SDSTAGECOLMESH *stageColCurTriangle;
/* 0x220 */ static s32 stageColFloorNum;
/* 0x21C */ static s32 stageColWallNum;
/* 0x21A gap_05_0000021A_bss (0x2): alignment gap */
/* 0x218 */ static s16 stageLavaModelId;
/* 0x214 */ static float stageTrialHeight;
/* 0x210 */ static s32 stageTrialSmooth;
/* 0x20C */ u8 lbl_1_bss_20C[0x4]; /* unreferenced (alignment 4) */
/* 0x208 */ static s32 stageTrialNoiseNum;
/* 0x204 */ static s32 stageTrialNoiseX;
/* 0x200 */ static s32 stageTrialNoiseY;
/* 0x1FC */ static s32 stageTrialNoiseDec;
/* 0x1F8 */ static s32 stageTrialClearOff;
/* 0x1F4 */ static s32 stageTrialLavaFloorOnF;
/* 0x1F0 */ static void *texturePtr; /* GUESS: pointer */
/* 0x10 */ static SDSTAGE07SMOKE stage07Smoke[20];
/* 0xC */ u8 lbl_1_bss_C[0x4]; /* unreferenced (alignment 4) */
/* 0x8 */ static void *textureBackupPtr; /* memcpy / HuMemDirectFree */

static char **stageShadowObjTbl[8]; /* defined after SdStageClose (.data order) */
extern char lbl_1_data_1860[2]; /* "g", "w": MakeMainStage's nameTbl; defined after SdStageObjCreate (.data order) */
extern char lbl_1_data_1862[2];

static void StageBackObjInit(void);
static void StageShadowInit(void);
static void ReadFace(s32 triNo, HSFFACE *face, HSFBUFFER *vtx, s8 *nrm, HuVecF **vtxOut, s8 **nrmOut);
static void MakeStage(s32 a0, s32 a1, float a2);
static void MakeTrialStage(s32 a0, float a1);
static void MakeMainStage(void);
static s32 StageTrialFloorCheck(HuVecF *pos, HuVecF *out, float yOfs);
static s32 StageMainFloorCheck(HuVecF *pos, HuVecF *out, float yOfs);
static s32 StageTrialWallCheck(HuVecF *pos, HuVecF *out, float yOfs);
static s32 StageMainWallCheck(HuVecF *pos, HuVecF *out, float yOfs);
static float StageTrialDistCalc(HuVecF pos);
static float StageMainDistCalc(HuVecF pos);
static void StageTrialObjCreate(void);
static void StageMainObjCreate(void);
static void StageDataClose(void);
static void StageObjUpdate(void);
static void StageDokanUpdate(SDSTAGEOBJ *obj);
static void StageTogezoUpdate(SDSTAGEOBJ *obj);
static void StageBomheiUpdate(SDSTAGEOBJ *obj);
static void StageBomheiBigUpdate(SDSTAGEOBJ *obj);
static void StageKinokoUpdate(SDSTAGEOBJ *obj);
static s32 StageKinokoCheck(HuVecF pos, float radius);
static void StageNKinokoUpdate(SDSTAGEOBJ *obj);
static void StageObjCol(SDSTAGEOBJ *obj);
static void StageRabbitUpdate(void);
static void StageCreateDust(SDSTAGEOBJ *obj, float scale);
static void StageUpdateFire(SDSTAGEOBJ *obj);
static void MakeStageLight(void);
static void StageHamonCreate(void);
static void StageHamonKill(void);
static void StageHamonLayerHook(s16 layerNo);
static void StageHamonPosSet(HuVecF pos1, HuVecF pos2);
static void StageHamonColorSet(GXColor *color);
static void StageHamonSpeedSet(float speed);
static void StageHamonMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);
static void StageTrialMakeGround(void);
static s32 StageTrialAddNoise(s32 *x, s32 *y, s32 flag);
static void StageTrialAddSpecial(s32 x, s32 y, s32 a2, s32 flag);
static void StageTrialAddBoundary(void);
static void StageTrialClearDist(HuVecF pos, float dist);
static void StageTrialAddSlope(HuVecF pos, float a1);
static void StageTrialAddSlope2(HuVecF a0, HuVecF a1, float a2);
static void MakeTrialStageMesh(void);
static void Stage07SmokeMain(void);
static void Stage07SmokeCreate(void);
static void Stage07SmokeUpdate(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 36 insns */
void SdStageInit(s32 a0)
{
    stageColWall = (SDSTAGECOLMESH *)(stageTrialMapColType = (u8 *)(stageTrialMap = NULL)); /* one chain in retail (void * there) */
    stageColMesh = HuMemDirectMallocNum(HEAP_MODEL, 0x15A800, HU_MEMNUM_OVL);
    SdStageCreate(a0);
    MakeStage(a0, 5, 75.0f);
}

/* 0x1388 */ static s16 trialModelId[4] = { -1, -1, -1, -1 };
/* 0x1390 */ static SDSTAGEDATA stageDataTbl[8] = {
    { DATANUM(DATA_sd00, 0), DATANUM(DATA_sd00, 10), 0, 2350.0f, 2350.0f },
    { DATANUM(DATA_sd00, 2), DATANUM(DATA_sd00, 11), 1, 3500.0f, 3500.0f },
    { DATANUM(DATA_sd00, 3), DATANUM(DATA_sd00, 12), 1, 3000.0f, 3000.0f },
    { DATANUM(DATA_sd00, 4), DATANUM(DATA_sd00, 13), 1, 4200.0f, 4200.0f },
    { DATANUM(DATA_sd00, 5), DATANUM(DATA_sd00, 14), 1, 3000.0f, 3000.0f },
    { DATANUM(DATA_sd00, 6), DATANUM(DATA_sd00, 15), 1, 2950.0f, 2950.0f },
    { DATANUM(DATA_sd00, 7), DATANUM(DATA_sd00, 16), 1, 2500.0f, 2500.0f },
    { DATANUM(DATA_sd00, 8), DATANUM(DATA_sd00, 17), 2, 3000.0f, 3000.0f },
};
/* 0x1430 */ static u32 objModelFile[6] = { DATANUM(DATA_sd00, 96), DATANUM(DATA_sd00, 97), DATANUM(DATA_sd00, 100), DATANUM(DATA_sd00, 103), DATANUM(DATA_sd00, 106), DATANUM(DATA_sd00, 107) };
/* 0x1448 */ static u32 objBomheiMotTbl[2] = { DATANUM(DATA_sd00, 98), DATANUM(DATA_sd00, 99) };
/* 0x1450 */ static u32 objBomheiBigMotTbl[2] = { DATANUM(DATA_sd00, 101), DATANUM(DATA_sd00, 102) };
/* 0x1458 */ static SDSTAGEOBJDATA objDataTbl[6] = {
    { 1, 0, 0.0f, 0.0f, { 150.0f, 300.0f, 150.0f }, 0, 0, 0.0f, 0 },
    { 0, 0, 80.0f, 0.0f, { 60.0f, 60.0f, 60.0f }, 300, 300, 450.0f, 2 },
    { 0, 0, 100.0f, 0.0f, { 70.0f, 70.0f, 70.0f }, 600, 600, 750.0f, 3 },
    { 0, 0, 0.0f, 0.0f, { 68.0f, 68.0f, 68.0f }, 0, 0, 0.0f, 1 },
    { 1, 0, 0.0f, 0.0f, { 100.0f, 160.0f, 100.0f }, 0, 0, 0.0f, 0 },
    { 1, 0, 0.0f, 0.0f, { 75.0f, 120.0f, 75.0f }, 0, 0, 0.0f, 0 },
};

/* 764 insns */
void SdStageCreate(s32 a0)
{
    s32 i;
    u8 *tex;
    char *texName = "sd00_g00";

    if (stageColWall != 0) {
        HuMemDirectFree(stageColWall);
        stageColWall = NULL;
    }
    if (stageTrialMapColType != 0) {
        HuMemDirectFree(stageTrialMapColType);
        stageTrialMapColType = NULL;
    }
    if (stageTrialMap != 0) {
        HuMemDirectFree(stageTrialMap);
        stageTrialMap = NULL;
    }
    texturePtr = NULL;
    sys->unkA34[0] = sys->unkA34[1] = sys->unkA34[2] = sys->unkA34[3] = sys->unkA34[4] = (HuVecF) { -10000.0f, 0.0f, 0.0f };
    sys->stageMdlId = sys->unk168 = sys->unk160[0] = sys->unk160[1] = sys->unk164[0] = sys->unk164[1] = stageLavaModelId = HU3D_MODELID_NONE;
    sys->stageNo = a0;
    sys->stageMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(stageDataTbl[sys->stageNo].dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
    if (sys->stageNo == 2) {
        sys->unk164[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 9), HU_MEMNUM_OVL, HEAP_MODEL));
        sys->unk164[1] = Hu3DModelLink(sys->unk164[0]);
        StageHamonCreate();
        Hu3DLayerHookSet(14, StageHamonLayerHook);
        StageHamonPosSet((HuVecF) { 0.0f, 0.0f, 0.03f }, (HuVecF) { 0.0f, 0.0f, 0.03f });
        StageHamonSpeedSet(-0.005f);
        for (i = 0; i < 2; i++) {
            Hu3DCameraCreate(sdCameraBitTbl[i + 2]);
            Hu3DCameraViewportSet(sdCameraBitTbl[i + 2], 320.0f * i, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f);
            Hu3DCameraScissorSet(sdCameraBitTbl[i + 2], 320.0f * i, 0, 320, 480);
            Hu3DCameraPerspectiveSet(sdCameraBitTbl[i + 2], 60.0f, 20.0f, 35000.0f, 0.6f);
            Hu3DModelCameraSet(sys->unk164[i], sdCameraBitTbl[i + 2]);
            Hu3DModelLayerSet(sys->unk164[i], 7);
            Hu3DModelMatHookSet(sys->unk164[i], StageHamonMatHook);
        }
    }
    sys->unk160[0] = Hu3DModelCreate(HuDataSelHeapReadNum(stageDataTbl[sys->stageNo].unk4, HU_MEMNUM_OVL, HEAP_MODEL));
    sys->unk160[1] = Hu3DModelLink(sys->unk160[0]);
    if (sys->stageNo == 1) {
        sys->unk168 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 1), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(sys->unk168, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(sys->unk168, 0);
        Hu3DModelLayerSet(sys->stageMdlId, 1);
    } else {
        Hu3DModelLayerSet(sys->stageMdlId, 0);
    }
    for (i = 0; i < 2; i++) {
        Hu3DModelCameraSet(sys->unk160[i], sdCameraBitTbl[i]);
        Hu3DModelLayerSet(sys->unk160[i], 0);
    }
    StageShadowInit();
    StageBackObjInit();
    if (sys->stageNo == 2 || sys->stageNo == 7) {
        Hu3DModelAmbSet(sys->stageMdlId, 0.1f, 0.1f, 0.1f);
    } else if (sys->stageNo == 6) {
        Hu3DModelAmbSet(sys->stageMdlId, 1.0f, 1.0f, 1.0f);
    } else {
        Hu3DModelAmbSet(sys->stageMdlId, 1.0f, 1.0f, 1.0f);
    }
    Hu3DMotionTimeSet(sys->stageMdlId, 0.0f);
    if (sys->stageNo == 1) {
        Hu3DMotionSpeedSet(sys->unk160[0], 0.04f);
        Hu3DMotionSpeedSet(sys->unk160[1], 0.04f);
    } else if (sys->stageNo == 2 || sys->stageNo == 6) {
        Hu3DMotionSpeedSet(sys->unk160[0], 1.0f);
        Hu3DMotionSpeedSet(sys->unk160[1], 1.0f);
        Hu3DModelAttrSet(sys->unk160[0], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(sys->unk160[1], HU3D_MOTATTR_LOOP);
    } else {
        Hu3DMotionSpeedSet(sys->stageMdlId, 1.0f);
    }
    Hu3DModelAttrSet(sys->stageMdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelCameraSet(sys->stageMdlId, 3);
    if (sys->stageNo == 0) {
        textureBackupPtr = HuMemDirectMallocNum(HEAP_HEAP, 0x40000, HU_MEMNUM_OVL);
        for (i = 0; i < Hu3DData[sys->stageMdlId].hsf->bitmapNum; i++) {
            if (strlen(Hu3DData[sys->stageMdlId].hsf->attribute->bitmap[i].name) == strlen(texName)
                && memcmp(texName, Hu3DData[sys->stageMdlId].hsf->attribute->bitmap[i].name, strlen(texName)) == 0) {
                break;
            }
        }
        texturePtr = tex = Hu3DData[sys->stageMdlId].hsf->attribute->bitmap[i].data;
        memcpy(textureBackupPtr, tex + (rand8() % 2) * 0x40000, 0x40000);
        memcpy(tex, textureBackupPtr, 0x40000);
        memcpy(tex + 0x40000, textureBackupPtr, 0x40000);
        HuMemDirectFree(textureBackupPtr);
    }
    if (sys->unkFF0 != -1) {
        HuAudFXStop(sys->unkFF0);
        sys->unkFF0 = -1;
    }
    if (sys->stageNo == 5) {
        sys->unkFF0 = HuAudFXPlay(931);
    } else if (sys->stageNo == 7) {
        sys->unkFF0 = HuAudFXPlay(930);
    }
}

/* 0x1570 */ static char *stage1Obj[2] = { "sky", NULL };
/* 0x1578 */ static float stage1ObjScale[1] = { 1.25f };
/* 0x158C */ static char *stage2Obj[5] = { "sky", "cloud", "hill", "mt", NULL };
/* 0x15A0 */ static float stage2ObjScale[4] = { 1.25f, 1.1f, 0.025f, 0.0125f };
/* 0x15E4 */ static char *stage3Obj[11] = { "sky", "moon", "s01", "s02", "s03", "s04", "s05", "woods01", "woods02", "woods03", NULL };
/* 0x1610 */ static float stage3ObjScale[10] = { 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 1.25f, 0.1f, 0.05f, 0.025f };
/* 0x1640 */ static char *stage4Obj[5] = { "sky", "cloud", "mt1", "mt2", NULL };
/* 0x1654 */ static float stage4ObjScale[4] = { 1.25f, 1.0f, 0.3f, 0.2f };
/* 0x1664 */ static char *stage5Obj[4] = { "sky", "mt", "cloud", NULL };
/* 0x1674 */ static float stage5ObjScale[3] = { 1.15f, 1.0f, 0.5f };
/* 0x1690 */ static char *stage6Obj[4] = { "sky", "palm01", "palm02", NULL };
/* 0x16A0 */ static float stage6ObjScale[3] = { 0.5f, 0.15f, 0.1f };
/* 0x1700 */ static char *stage7Obj[11] = { "cosmos", "gus", "earth_add", "earth_mat", "moonbase", "antena1", "antena2", "antena3", "antena4", "pipeline", NULL };
/* 0x172C */ static float stage7ObjScale[10] = { 1.25f, 1.15f, 1.0f, 1.0f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f, 0.1f };
/* 0x175C */ static char *stage8Obj[6] = { "sky", "mt", "fp1", "fp2", "cloud", NULL };
/* 0x1774 */ static float stage8ObjScale[5] = { 1.25f, 1.1f, 1.0f, 0.75f, 1.15f };
/* 0x1788 */ static char **stageObjTbl[8] = { stage1Obj, stage2Obj, stage3Obj, stage4Obj, stage5Obj, stage6Obj, stage7Obj, stage8Obj };

/* 61 insns */
static void StageBackObjInit(void)
{
    s32 i;
    s32 j;
    char **names;

    memset(sys->backObj, 0, sizeof(sys->backObj));
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 20; j++) {
            names = stageObjTbl[sys->stageNo];
            if (names[j] == NULL) {
                break;
            }
            sys->backObj[i][j] = Hu3DModelObjPtrGet(sys->unk160[i], names[j]);
        }
    }
}

/* 0x17A8 */ static float *stageObjScaleTbl[8] = { stage1ObjScale, stage2ObjScale, stage3ObjScale, stage4ObjScale, stage5ObjScale, stage6ObjScale, stage7ObjScale, stage8ObjScale };

/* 158 insns */
void SdStageBackRotYSet(s32 no, float a1, float a2)
{
    s32 i;
    float rotY = a1;

    if (MgSeqModeGet() >= 2) {
        a1 -= a2;
        if (a1 > 180.0f) {
            a1 -= 360.0f;
        }
        if (a1 < -180.0f) {
            a1 += 360.0f;
        }
        for (i = 0; sys->backObj[no][i] != 0; i++) {
            sys->backObj[no][i]->mesh.base.rot.y -= a1 * stageObjScaleTbl[sys->stageNo][i];
        }
        if (sys->stageNo == 7) {
            sys->backObj[no][4]->mesh.base.rot.y += 0.1f;
        } else if (sys->stageNo == 1) {
            sys->backObj[no][0]->mesh.base.rot.y -= 0.0125f;
            sys->backObj[no][1]->mesh.base.rot.y -= 0.025f;
        } else if (sys->stageNo == 4) {
            sys->backObj[no][0]->mesh.base.rot.y += 0.1f;
            sys->backObj[no][2]->mesh.base.rot.y += 2.0f;
        }
    }
}

/* 34 insns */
static void StageShadowInit(void)
{
    s32 i;
    char **names = stageShadowObjTbl[sys->stageNo];

    for (i = 0; names[i] != 0; i++) {
        Hu3DModelShadowMapObjSet(sys->stageMdlId, names[i]);
    }
}

/* 153 insns */
void SdStageClose(void)
{
    char *name = "grid1";
    s32 i;
    HSFBUFFER *vtx;
    HSFBUFFER *nrm;
    HSFS8VEC *nrmData;
    HSFDATA *hsf;

    if (sys->stageNo == 0) {
        hsf = Hu3DData[sys->stageMdlId].hsf;
        for (i = 0; i < hsf->faceNum; i++) {
            if (strlen(hsf->face[i].name) == strlen(name) && memcmp(name, hsf->face[i].name, strlen(name)) == 0) {
                break;
            }
        }
        vtx = &hsf->vertex[i];
        nrm = &hsf->normal[i];
        nrmData = nrm->data;
        for (i = 0; i < vtx->count; i++) {
            ((HuVecF *)vtx->data)[i].y = 0.0f;
        }
        for (i = 0; i < nrm->count; i++) {
            nrmData[i].x = 0;
            nrmData[i].y = 127;
            nrmData[i].z = 0;
        }
        if (stageLavaModelId != HU3D_MODELID_NONE) {
            Hu3DModelAttrSet(stageLavaModelId, HU3D_ATTR_DISPOFF);
        }
    }
    StageDataClose();
    if (stageColMesh != 0) {
        HuMemDirectFree(stageColMesh);
        stageColMesh = NULL;
    }
    if (stageColWall != 0) {
        HuMemDirectFree(stageColWall);
        stageColWall = NULL;
    }
    if (stageTrialMapColType != 0) {
        HuMemDirectFree(stageTrialMapColType);
        stageTrialMapColType = NULL;
    }
    if (stageTrialMap != 0) {
        HuMemDirectFree(stageTrialMap);
        stageTrialMap = NULL;
    }
}

/* 0x17D0 */ static char *stage1ShadowObj[2] = { "grid1", NULL };
/* 0x17DC */ static char *stage2ShadowObj[2] = { "y01", NULL };
/* 0x17EC */ static char *stage3ShadowObj[4] = { "y01", "y02", "y03", NULL };
/* 0x1800 */ static char *stage4ShadowObj[5] = { "y01", "y02", "y03", "y04", NULL };
/* 0x1814 */ static char *stage5ShadowObj[2] = { "y01", NULL };
/* 0x181C */ static char *stage6ShadowObj[4] = { "y01", "y02", "y03", NULL };
/* 0x182C */ static char *stage7ShadowObj[3] = { "y01", "y02", NULL };
/* 0x1838 */ static char *stage8ShadowObj[2] = { "y01", NULL };
/* 0x1840 */ static char **stageShadowObjTbl[8] = { stage1ShadowObj, stage2ShadowObj, stage3ShadowObj, stage4ShadowObj, stage5ShadowObj, stage6ShadowObj, stage7ShadowObj, stage8ShadowObj };

/* 136 insns */
static void ReadFace(s32 triNo, HSFFACE *face, HSFBUFFER *vtx, s8 *nrm, HuVecF **vtxOut, s8 **nrmOut)
{
    HSFFACEINDEX *idx[3];

    switch (face->type) {
        case 2:
            idx[0] = &face->index[0];
            idx[1] = &face->index[1];
            idx[2] = &face->index[2];
            break;
        case 3:
            if (triNo == 0) {
                idx[0] = &face->index[0];
                idx[1] = &face->index[1];
                idx[2] = &face->index[2];
            } else {
                idx[0] = &face->index[1];
                idx[1] = &face->index[3];
                idx[2] = &face->index[2];
            }
            break;
        case 4:
            if (triNo == 0) {
                idx[0] = &face->strip.index[0];
                idx[1] = &face->strip.index[1];
                idx[2] = &face->strip.index[2];
            } else if (triNo == 1) {
                idx[0] = &face->strip.index[2];
                idx[1] = &face->strip.index[1];
                idx[2] = &face->strip.data[0];
            } else if (triNo == 2) {
                idx[0] = &face->strip.index[1];
                idx[1] = &face->strip.data[1];
                idx[2] = &face->strip.data[0];
            } else if (triNo % 2) {
                idx[0] = &face->strip.data[triNo - 3];
                idx[1] = &face->strip.data[triNo - 2];
                idx[2] = &face->strip.data[triNo - 1];
            } else {
                idx[0] = &face->strip.data[triNo - 3];
                idx[1] = &face->strip.data[triNo - 1];
                idx[2] = &face->strip.data[triNo - 2];
            }
            break;
    }
    vtxOut[0] = &((HuVecF *)vtx->data)[idx[0]->vertex];
    vtxOut[1] = &((HuVecF *)vtx->data)[idx[1]->vertex];
    vtxOut[2] = &((HuVecF *)vtx->data)[idx[2]->vertex];
    if (nrm != 0) {
        nrmOut[0] = &nrm[idx[0]->normal * 3];
        nrmOut[1] = &nrm[idx[1]->normal * 3];
        nrmOut[2] = &nrm[idx[2]->normal * 3];
    }
}

/* 21 insns */
static void MakeStage(s32 a0, s32 a1, float a2)
{
    if (sys->stageNo == 0) {
        MakeTrialStage(a1, a2);
    } else {
        MakeMainStage();
    }
    MakeStageLight();
}

/* 1220 insns */
static void MakeTrialStage(s32 a0, float a1)
{
    Mtx mtx;
    HuVecF d1;
    HuVecF d2;
    HuVecF *vtxP[3];
    HuVecF scale = { 1.0f, -1.0f, 1.0f };
    s8 *nrmP[3];
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 x;
    s32 z;
    s32 mx;
    s32 mz;
    s32 triNum;
    float sum;
    s8 *nrmData;
    HSFBUFFER *nrmBuf;
    char *name = "grid1";
    HSFDATA *hsf;
    HSFBUFFER *vtxBuf;
    HSFBUFFER *faceBuf;
    HSFFACE *face;
    SDSTAGECOLMESH *col;

    stageTrialClearOff = stageTrialLavaFloorOnF = 0;
    stageTrialHeight = a1;
    stageTrialSmooth = a0;
    memset(stageColMesh, 0, 0x15A800);
    stageTrialMapColType = HuMemDirectMallocNum(HEAP_HEAP, 0x4000, HU_MEMNUM_OVL);
    memset(stageTrialMapColType, 0, 0x4000);
    stageTrialMap = HuMemDirectMallocNum(HEAP_HEAP, 0x100, HU_MEMNUM_OVL);
    x = rand8() % 5;
    if (x == 1) {
        stageTrialClearOff = 1;
    }
    memset(stageTrialMap, (x << 4) + 2, 0x100);
    hsf = Hu3DData[sys->stageMdlId].hsf;
    for (i = 0; i < hsf->faceNum; i++) {
        if (strlen(hsf->face[i].name) == strlen(name) && memcmp(name, hsf->face[i].name, strlen(name)) == 0) {
            break;
        }
    }
    vtxBuf = &hsf->vertex[i];
    nrmBuf = &hsf->normal[i];
    faceBuf = &hsf->face[i];
    face = faceBuf->data;
    if (stageLavaModelId == HU3D_MODELID_NONE) {
        stageLavaModelId = Hu3DModelCreateData(DATANUM(DATA_sd00, 95));
        for (i = 0; i < Hu3DData[stageLavaModelId].hsf->st->count; i++) {
            stageWork.unk8[i] = &((HuVec2f *)Hu3DData[stageLavaModelId].hsf->st->data)[i];
        }
        stageWork.unk18 = Hu3DData[stageLavaModelId].hsf->material;
        Hu3DModelShadowMapSet(stageLavaModelId);
        Hu3DModelCameraSet(stageLavaModelId, 3);
    }
    stageWork.unk4 = Hu3DData[stageLavaModelId].pos.y = 90.0f;
    n = 49;
    stageTrialMapHeight = HuMemDirectMallocNum(HEAP_HEAP, sizeof(SDTRIALVTXCELL) * n * n, HU_MEMNUM_OVL);
    memset(stageTrialMapHeight, 0, sizeof(SDTRIALVTXCELL) * n * n);
    StageTrialMakeGround();
    for (i = 0; i < vtxBuf->count; i++) {
        x = 24.0f + ((HuVecF *)vtxBuf->data)[i].x / 100.0f;
        z = 24.0f + ((HuVecF *)vtxBuf->data)[i].z / 100.0f;
        stageTrialMapHeight[x + z * n].vtx[stageTrialMapHeight[x + z * n].num++] = &((HuVecF *)vtxBuf->data)[i];
        mx = x / 3;
        mx = (mx > 15) ? 15 : ((mx < 0) ? 0 : mx);
        mz = z / 3;
        mz = (mz > 15) ? 15 : ((mz < 0) ? 0 : mz);
        if ((stageTrialMap[mx + mz * 16] & 0xF) > 4) {
            j = stageTrialMap[mx + mz * 16] & 0xF;
            j = stageTrialMap[mx + mz * 16] & 0xF;
            j = stageTrialMap[mx + mz * 16] & 0xF;
        }
        if (a1 > 0.0f) {
            triNum = stageTrialMap[mx + mz * 16] & 0xF;
            if (triNum == 0) {
                ((HuVecF *)vtxBuf->data)[i].y = 0.0f;
            } else if (triNum == 1) {
                ((HuVecF *)vtxBuf->data)[i].y = 50.0f;
            } else if (triNum == 2) {
                ((HuVecF *)vtxBuf->data)[i].y = 100.0f;
            } else {
                ((HuVecF *)vtxBuf->data)[i].y = 100.0f + (triNum - 2) * a1;
            }
        } else {
            ((HuVecF *)vtxBuf->data)[i].y = 100.0f;
        }
    }
    if (a0 >= 3) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                sum = 0.0f;
                for (k = 0; k < a0 * a0; k++) {
                    x = i + (k / a0 - a0 / 2);
                    x = (x > 48) ? 48 : ((x < 0) ? 0 : x);
                    z = j + (k % a0 - a0 / 2);
                    z = (z > 48) ? 48 : ((z < 0) ? 0 : z);
                    sum += stageTrialMapHeight[z + x * n].vtx[0]->y;
                }
                for (k = 0; k < stageTrialMapHeight[j + i * n].num; k++) {
                    stageTrialMapHeight[j + i * n].vtx[k]->y = sum / (a0 * a0);
                }
            }
        }
    }
    HuMemDirectFree(stageTrialMapHeight);
    stageTrialMapNum = HuMemDirectMallocNum(HEAP_HEAP, sizeof(SDTRIALNRMCELL) * n * n, HU_MEMNUM_OVL);
    memset(stageTrialMapNum, 0, sizeof(SDTRIALNRMCELL) * n * n);
    nrmData = nrmBuf->data;
    for (i = 0; i < faceBuf->count; i++) {
        face = &((HSFFACE *)faceBuf->data)[i];
        triNum = 0;
        if (face->type == 2) {
            triNum = 1;
        } else if (face->type == 3) {
            triNum = 2;
        } else if (face->type == 4) {
            triNum = face->strip.count + 1;
        }
        if (triNum == 0) {
            continue;
        }
        for (j = 0; j < triNum; j++) {
            ReadFace(j, face, vtxBuf, nrmData, vtxP, nrmP);
            VECSubtract(vtxP[1], vtxP[0], &d1);
            VECNormalize(&d1, &d1);
            VECSubtract(vtxP[2], vtxP[1], &d2);
            VECNormalize(&d2, &d2);
            VECCrossProduct(&d1, &d2, &d2);
            VECNormalize(&d2, &d2);
            nrmP[0][0] = nrmP[1][0] = nrmP[2][0] = 127.0f * d2.x;
            nrmP[0][1] = nrmP[1][1] = nrmP[2][1] = 127.0f * d2.y;
            nrmP[0][2] = nrmP[1][2] = nrmP[2][2] = 127.0f * d2.z;
            for (k = 0; k < 3; k++) {
                x = 24.0f + vtxP[k]->x / 100.0f;
                z = 24.0f + vtxP[k]->z / 100.0f;
                stageTrialMapNum[x + z * n].nrm[stageTrialMapNum[x + z * n].num++] = nrmP[k];
            }
            mx = 48.0f + (vtxP[0]->x + vtxP[1]->x + vtxP[2]->x) / 150.0f;
            mz = 24.0f + (vtxP[0]->z + vtxP[1]->z + vtxP[2]->z) / 300.0f;
            col = &stageColMesh[mx + mz * 96];
            col->nrm = d2;
            VECCrossProduct(&d1, &col->nrm, &d2);
            VECNormalize(&d2, &d2);
            col->pos = (HuVecF) { (vtxP[0]->x + vtxP[1]->x + vtxP[2]->x) / 3.0f, (vtxP[0]->y + vtxP[1]->y + vtxP[2]->y) / 3.0f,
                (vtxP[0]->z + vtxP[1]->z + vtxP[2]->z) / 3.0f };
            MTXIdentity(mtx);
            mtx[0][0] = d1.x;
            mtx[1][0] = d1.y;
            mtx[2][0] = d1.z;
            mtx[0][1] = col->nrm.x;
            mtx[1][1] = col->nrm.y;
            mtx[2][1] = col->nrm.z;
            mtx[0][2] = d2.x;
            mtx[1][2] = d2.y;
            mtx[2][2] = d2.z;
            MTXCopy(mtx, col->mtx);
            MTXInverse(col->mtx, col->invMtx);
            d1 = (HuVecF) { 0.0f, -1.0f, 0.0f };
            MTXMultVec(col->invMtx, &d1, &d1);
            d1.y = 0.0f;
            MTXMultVec(col->mtx, &d1, &col->unkC);
        }
    }
    if (a0 >= 3) {
        for (i = 0; i < 49; i++) {
            for (j = 0; j < 49; j++) {
                d1 = (HuVecF) { 0.0f, 0.0f, 0.0f };
                for (k = 0; k < a0 * a0; k++) {
                    x = i + (k % a0 - a0 / 2);
                    x = (x > 48) ? 48 : ((x < 0) ? 0 : x);
                    z = j + (k / a0 - a0 / 2);
                    z = (z > 48) ? 48 : ((z < 0) ? 0 : z);
                    d2 = (HuVecF) { stageTrialMapNum[x + z * n].nrm[0][0] / 127.0f, stageTrialMapNum[x + z * n].nrm[0][1] / 127.0f,
                        stageTrialMapNum[x + z * n].nrm[0][2] / 127.0f };
                    VECAdd(&d1, &d2, &d1);
                }
                VECScale(&d1, &d1, 1.0f / (a0 * a0));
                for (k = 0; k < stageTrialMapNum[j + i * n].num; k++) {
                    stageTrialMapNum[j + i * n].nrm[k][0] = 127.0f * d1.x;
                    stageTrialMapNum[j + i * n].nrm[k][1] = 127.0f * d1.y;
                    stageTrialMapNum[j + i * n].nrm[k][2] = 127.0f * d1.z;
                }
            }
        }
    }
    HuMemDirectFree(stageTrialMapNum);
    trialModelId[0] = Hu3DModelCreateData(DATANUM(DATA_sd00, 91));
    trialModelId[1] = Hu3DModelCreateData(DATANUM(DATA_sd00, 92));
    trialModelId[2] = Hu3DModelCreateData(DATANUM(DATA_sd00, 93));
    trialModelId[3] = Hu3DModelCreateData(DATANUM(DATA_sd00, 94));
    MakeTrialStageMesh();
    Hu3DModelKill(trialModelId[0]);
    Hu3DModelKill(trialModelId[1]);
    Hu3DModelKill(trialModelId[2]);
    Hu3DModelKill(trialModelId[3]);
}

/* 843 insns */
static void MakeMainStage(void)
{
    HuVecF vtx[3];
    HuVecF d1;
    HuVecF d2;
    HuVecF *vtxP[3];
    HuVecF objPos;
    HuVecF scale = { 1.0f, -1.0f, 1.0f };
    char *nameTbl[] = { lbl_1_data_1860, lbl_1_data_1862, NULL }; /* "g", "w" */
    SDSTAGECOLMESH *floorMesh;
    SDSTAGECOLMESH *wallMesh;
    GXColor color = { 0xFF, 0x00, 0x00, 0xFF };
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 nameNo;
    s32 triNum;
    s32 floorNum;
    s32 wallNum;
    float radius;
    float mag;
    HSFDATA *hsf;
    HSFBUFFER *faceBuf;
    HSFBUFFER *vtxBuf;
    HSFFACE *face;
    HSFMATERIAL *mat;
    SDSTAGECOLMESH *col;

    hsf = Hu3DData[sys->stageMdlId].hsf;
    floorNum = wallNum = 0;
    for (i = 0; i < hsf->faceNum; i++) {
        faceBuf = &hsf->face[i];
        vtxBuf = &hsf->vertex[i];
        for (j = 0; nameTbl[j] != 0; j++) {
            if (strlen(faceBuf->name) == strlen(nameTbl[j]) && memcmp(nameTbl[j], faceBuf->name, strlen(nameTbl[j])) == 0) {
                break;
            }
        }
        if (nameTbl[j] == 0) {
            continue;
        }
        for (j = 0; j < faceBuf->count; j++) {
            face = &((HSFFACE *)faceBuf->data)[j];
            triNum = 0;
            if (face->type == 2) {
                triNum = 1;
            } else if (face->type == 3) {
                triNum = 2;
            } else if (face->type == 4) {
                triNum = face->strip.count + 1;
            }
            if (triNum == 0) {
                continue;
            }
            for (k = 0; k < triNum; k++) {
                ReadFace(k, face, vtxBuf, NULL, vtxP, NULL);
                VECSubtract(vtxP[1], vtxP[0], &d1);
                if (VECMag(&d1) == 0.0f) {
                    d1 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d1, &d1);
                VECSubtract(vtxP[2], vtxP[1], &d2);
                if (VECMag(&d2) == 0.0f) {
                    d2 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d2, &d2);
                VECCrossProduct(&d1, &d2, &d1);
                if (VECMag(&d1) == 0.0f) {
                    d1 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d1, &d1);
                if (d1.y >= 0.5f) {
                    floorNum++;
                } else {
                    wallNum++;
                }
            }
        }
    }
    stageColFloorNum = floorNum;
    stageColWallNum = wallNum;
    floorMesh = stageColMesh;
    wallMesh = stageColWall = HuMemDirectMallocNum(HEAP_HEAP, wallNum * sizeof(SDSTAGECOLMESH), HU_MEMNUM_OVL);
    memset(stageColMesh, 0, floorNum * sizeof(SDSTAGECOLMESH));
    memset(stageColWall, 0, wallNum * sizeof(SDSTAGECOLMESH));
    floorNum = wallNum = 0;
    for (i = 0; i < hsf->faceNum; i++) {
        vtxBuf = &hsf->vertex[i];
        faceBuf = &hsf->face[i];
        for (nameNo = 0; nameTbl[nameNo] != 0; nameNo++) {
            if (strlen(faceBuf->name) == strlen(nameTbl[nameNo]) && memcmp(nameTbl[nameNo], faceBuf->name, strlen(nameTbl[nameNo])) == 0) {
                break;
            }
        }
        if (nameTbl[nameNo] == 0) {
            continue;
        }
        Hu3DModelObjPosGet(sys->stageMdlId, nameTbl[nameNo], &objPos);
        for (j = 0; j < faceBuf->count; j++) {
            face = &((HSFFACE *)faceBuf->data)[j];
            triNum = 0;
            if (face->type == 2) {
                triNum = 1;
            } else if (face->type == 3) {
                triNum = 2;
            } else if (face->type == 4) {
                triNum = face->strip.count + 1;
            }
            if (triNum == 0) {
                continue;
            }
            for (k = 0; k < triNum; k++) {
                ReadFace(k, face, vtxBuf, NULL, vtxP, NULL);
                VECAdd(vtxP[0], &objPos, &vtx[0]);
                VECAdd(vtxP[1], &objPos, &vtx[1]);
                VECAdd(vtxP[2], &objPos, &vtx[2]);
                VECSubtract(&vtx[1], &vtx[0], &d1);
                if (VECMag(&d1) == 0.0f) {
                    d1 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d1, &d1);
                VECSubtract(&vtx[2], &vtx[1], &d2);
                if (VECMag(&d2) == 0.0f) {
                    d2 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d2, &d2);
                VECCrossProduct(&d1, &d2, &d2);
                if (VECMag(&d2) == 0.0f) {
                    d2 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d2, &d2);
                if (d2.y >= 0.5f) {
                    col = &floorMesh[floorNum++];
                } else {
                    col = &wallMesh[wallNum++];
                }
                if (nameNo == 0) {
                    col->flags = 1;
                }
                if (nameNo == 1) {
                    col->flags = 2;
                }
                col->nrm = d2;
                VECCrossProduct(&d1, &col->nrm, &d2);
                if (VECMag(&d2) == 0.0f) {
                    d2 = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&d2, &d2);
                col->pos = (HuVecF) { (vtx[0].x + vtx[1].x + vtx[2].x) / 3.0f, (vtx[0].y + vtx[1].y + vtx[2].y) / 3.0f,
                    (vtx[0].z + vtx[1].z + vtx[2].z) / 3.0f };
                MathPlaneRotMtxGet(&d1, &col->nrm, 0.0f, col->mtx);
                MTXInverse(col->mtx, col->invMtx);
                d1 = (HuVecF) { 0.0f, -1.0f, 0.0f };
                MTXMultVec(col->invMtx, &d1, &d1);
                d1.y = 0.0f;
                MTXMultVec(col->mtx, &d1, &col->unkC);
                radius = -10000.0f;
                for (l = 0; l < 3; l++) {
                    VECSubtract(&vtx[l], &col->pos, &col->tri[1].vtx[l]);
                    col->tri[0].vtx[l] = col->tri[1].vtx[l];
                    col->tri[0].vtx[l].y = 0.0f;
                    mag = VECMag(&col->tri[0].vtx[l]);
                    if (radius < mag) {
                        radius = mag;
                    }
                    MTXMultVec(col->invMtx, &col->tri[1].vtx[l], &col->tri[1].vtx[l]);
                    col->tri[1].vtx[l].y = 0.0f;
                }
                col->radius = radius;
                mat = &hsf->material[face->mat & 0xFFF];
                if (mat->color[0] == 0 && mat->color[1] == 0 && mat->color[2] == 255) {
                    col->flags |= 0x10;
                }
                if (mat->color[0] == 255 && mat->color[1] == 255 && mat->color[2] == 0) {
                    col->flags |= 0x20;
                }
                if (mat->color[0] == 0 && mat->color[1] == 255 && mat->color[2] == 0) {
                    col->flags |= 0x40;
                }
                for (l = 0; l < 3; l++) {
                    VECSubtract(&col->tri[1].vtx[(l + 1) % 3], &col->tri[1].vtx[l], &d1);
                    VECNormalize(&d1, &d1);
                    VECSubtract(&col->tri[1].vtx[(l + 2) % 3], &col->tri[1].vtx[l], &d2);
                    VECNormalize(&d2, &d2);
                    VECAdd(&d1, &d2, &col->tri[1].edgeNrm[l]);
                    VECNormalize(&col->tri[1].edgeNrm[l], &col->tri[1].edgeNrm[l]);
                    col->tri[1].edgeD[l] = VECDotProduct(&col->tri[1].edgeNrm[l], &d1);
                    VECSubtract(&col->tri[0].vtx[(l + 1) % 3], &col->tri[0].vtx[l], &d1);
                    VECNormalize(&d1, &d1);
                    VECSubtract(&col->tri[0].vtx[(l + 2) % 3], &col->tri[0].vtx[l], &d2);
                    VECNormalize(&d2, &d2);
                    VECAdd(&d1, &d2, &col->tri[0].edgeNrm[l]);
                    VECNormalize(&col->tri[0].edgeNrm[l], &col->tri[0].edgeNrm[l]);
                    col->tri[0].edgeD[l] = VECDotProduct(&col->tri[0].edgeNrm[l], &d1);
                }
            }
        }
    }
}

/* 1143 insns */
void SdStageMachineCol(SDMACHINE *machine)
{
    Mtx mtx;
    HuVecF oldPos[4];
    s32 i;
    s32 x;
    s32 z;
    s32 pos;
    s32 num2 = 0;
    s32 num3 = 0;
    s32 num4 = 0;
    s32 colNum[6] = { 0, 0, 0, 0, 0, 0 };
    s32 floorNum;
    s32 colSet = 0;
    HuVecF ofs;
    HuVecF delta;
    HuVecF side;
    HuVecF up;
    HuVecF front;
    HuVecF rot;
    HuVecF vec;
    HuVecF vel;
    HuVecF refl;
    HuVecF dir;
    float temp;
    float maxAngle;

    if (machine->unk368 & 2) {
        machine->pos.y -= machine->unk354;
    }
    machine->unk90 = 1;
    floorNum = 0;
    VECSubtract(&machine->pos, &machine->unk138, &vel);
    if (SdStageYOfsWallCheck(&machine->pos, &vec, machine->unk358)) {
        vel.y = 0.0f;
        VECReflect(&vel, &vec, &refl);
        if (machine->mode == 2) {
            dir = (HuVecF) { machine->unk21C[0][2], machine->unk21C[1][2], machine->unk21C[2][2] };
            VECReflect(&dir, &vec, &dir);
            dir.y = 0.0f;
            MathPlaneRotMtxGet(&dir, NULL, 0.0f, machine->unk21C);
        }
        if (VECDotProduct(&vec, &refl) > 0.05f) {
            if (VECMag(&machine->unk160) == 0.0f) {
                machine->unk160 = (HuVecF) { 1.0f, 1.0f, 1.0f };
            }
            VECNormalize(&machine->unk160, &side);
            if (VECDotProduct(&vec, &side) < -0.25f && VECMag(&machine->unk160) > 1.5f + machine->unk28C) {
                HuAudFXPlayVolPan(machine->playerNo + 0x563, 127, (machine->playerNo * 32) + 48);
                SdVibrate(machine->playerNo, 0, 5);
            }
            temp = VECMag(&machine->unkE8);
            temp = (temp > 10.0f) ? 10.0f : ((temp < 1.0f) ? 1.0f : temp);
            VECScale(&refl, &machine->unkE8, temp);
        }
    }
    for (i = 0; i < 4; i++) {
        MTXTrans(mtx, machine->unk36C[i].x, machine->unk36C[i].y, machine->unk36C[i].z);
        MTXConcat(machine->mtx, mtx, mtx);
        machine->unk1B0[i] = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
        VECAdd(&machine->unk1B0[i], &machine->pos, &machine->unk1B0[i]);
        if (machine->unk16C == 0) {
            machine->unk1B0[i].y -= machine->unk170[i];
        }
        machine->unk1E0[i] = 0;
        oldPos[i] = machine->unk1B0[i];
        temp = (i < 2) ? machine->unk360 : machine->unk364;
        if (SdStageYOfsFloorCheck(&machine->unk1B0[i], NULL, temp)) {
            machine->unk1E0[i] = 1;
            machine->unk90 = machine->unk94 = 0;
            VECAdd(&machine->unkF8, &stageColCurTriangle->unkC, &machine->unkF8);
            machine->unk1F0[i] = 0;
            if (stageColCurTriangle->flags & 0x10) {
                machine->unk1F0[i] = 2;
                num2++;
            } else if (stageColCurTriangle->flags & 0x20) {
                machine->unk1F0[i] = 3;
                num3++;
            } else if (stageColCurTriangle->flags & 0x40) {
                machine->unk1F0[i] = 4;
                num4++;
            }
            if (sys->stageNo == 4) {
                machine->unk1F0[i] = 1;
            } else if (machine->unk1B0[i].y - machine->unk360 < -50.0f) {
                if (sys->stageNo == 2) {
                    machine->unk1F0[i] = 6;
                } else if (sys->stageNo == 7) {
                    machine->unk1F0[i] = 5;
                }
            }
            floorNum++;
            machine->unk170[i] = 2.0f;
        }
        machine->unk170[i] *= 1.06f;
        machine->unk170[i] = (machine->unk170[i] > 100.0f) ? 100.0f : ((machine->unk170[i] < 2.0f) ? 2.0f : machine->unk170[i]);
        VECSubtract(&machine->unk1B0[i], &oldPos[i], &delta);
        VECScale(&delta, &delta, 0.5f);
        VECAdd(&oldPos[i], &delta, &machine->unk1B0[i]);
        if (machine->unk368 & 2) {
            if (sys->stageNo == 0) {
                if (machine->unk1B0[i].y - machine->unk360 < 100.0f) {
                    machine->unk1B0[i].y = 100.0f + machine->unk360;
                    machine->unk1E0[i] = 1;
                    machine->unk90 = machine->unk94 = 0;
                }
            } else if (sys->stageNo == 2 || sys->stageNo == 7) {
                if (machine->unk1B0[i].y - machine->unk360 < 0.0f) {
                    machine->unk1B0[i].y = machine->unk360;
                    machine->unk1E0[i] = 1;
                    machine->unk90 = machine->unk94 = 0;
                }
            }
        }
    }
    machine->unk1B0[2].y += machine->unk360 - machine->unk364;
    VECSubtract(&machine->unk1B0[0], &machine->unk1B0[2], &front);
    VECNormalize(&front, &front);
    VECSubtract(&machine->unk1B0[1], &machine->unk1B0[0], &side);
    VECNormalize(&side, &side);
    VECCrossProduct(&side, &front, &up);
    VECNormalize(&up, &up);
    VECCrossProduct(&up, &front, &side);
    VECNormalize(&side, &side);
    maxAngle = (sys->stageNo < 8) ? 45.0f : 65.0f;
    rot.y = 180.0 * (atan2(machine->mtx[0][2], machine->mtx[2][2]) / 3.141592653589793);
    MTXIdentity(machine->mtx);
    MTXRotRad(mtx, 'y', MTXDegToRad(rot.y));
    MTXConcat(machine->mtx, mtx, machine->mtx);
    MTXRotRad(mtx, 'y', MTXDegToRad(-rot.y));
    MTXMultVec(mtx, &front, &front);
    MTXMultVec(mtx, &side, &side);
    rot.x = -(180.0 * (atan2(front.y, front.z) / 3.141592653589793));
    rot.x = (rot.x > maxAngle) ? maxAngle : ((rot.x < -maxAngle) ? -maxAngle : rot.x);
    temp = 1.0f;
    if (machine->unk90) {
        if (++machine->unk94 > 120.0f) {
            machine->unk94 = 120;
        }
        temp = 1.0f - machine->unk94 / 120.0f;
    }
    rot.x *= temp;
    MTXRotRad(mtx, 'x', MTXDegToRad(-rot.x));
    MTXMultVec(mtx, &side, &side);
    rot.z = 180.0 * (atan2(side.y, side.x) / 3.141592653589793);
    rot.z = (rot.z > maxAngle) ? maxAngle : ((rot.z < -maxAngle) ? -maxAngle : rot.z);
    rot.z *= temp;
    VECSubtract(&rot, &machine->unk150, &rot);
    VECScale(&rot, &rot, 0.5f);
    VECAdd(&machine->unk150, &rot, &rot);
    MTXRotRad(mtx, 'x', MTXDegToRad(rot.x));
    MTXConcat(machine->mtx, mtx, machine->mtx);
    MTXRotRad(mtx, 'z', MTXDegToRad(rot.z));
    MTXConcat(machine->mtx, mtx, machine->mtx);
    MathMtxRotGet(machine->mtx, &machine->rot);
    machine->unk150 = rot;
    vec = machine->pos;
    VECScale(&machine->unk36C[0], &ofs, -1.0f);
    MTXMultVec(machine->mtx, &ofs, &ofs);
    VECAdd(&ofs, &machine->unk1B0[0], &machine->pos);
    machine->pos.x = vec.x;
    machine->pos.z = vec.z;
    if (machine->unk368 & 2) {
        machine->pos.y += machine->unk354;
    }
    if (machine->pos.y < -5000.0f) {
        machine->pos.y = -5000.0f;
    }
    if (machine->unk28 == 5) {
        machine->unk28 = 0;
    }
    for (i = 0; i < 4; i++) {
        MTXTrans(mtx, machine->unk36C[i].x, machine->unk36C[i].y, machine->unk36C[i].z);
        MTXConcat(machine->mtx, mtx, mtx);
        machine->unk1B0[i] = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
        VECAdd(&machine->unk1B0[i], &machine->pos, &machine->unk1B0[i]);
        if (sys->stageNo == 0) {
            temp = (i < 2) ? machine->unk360 : machine->unk364;
            if (machine->unk1B0[i].y - temp < stageWork.unk4 - 25.0f && stageTrialLavaFloorOnF) {
                machine->unk1F0[i] = machine->unk28 = 5;
                continue;
            }
            if (machine->unk1E0[i] == 0) {
                continue;
            }
            pos = 2400.0f + machine->unk1B0[i].x;
            x = pos * 128 / 4800.0f;
            x = (x > 127) ? 127 : ((x < 0) ? 0 : x);
            pos = 2400.0f + machine->unk1B0[i].z;
            z = pos * 128 / 4800.0f;
            z = (z > 127) ? 127 : ((z < 0) ? 0 : z);
            machine->unk1F0[i] = (stageTrialMapColType + z * 128)[x];
            if (machine->unk28 != 5 && colSet == 0) {
                if (++colNum[(stageTrialMapColType + z * 128)[x]] >= 2) {
                    machine->unk28 = (stageTrialMapColType + z * 128)[x];
                    colSet = 1;
                }
            }
        } else {
            if (machine->unk28 == 5) {
                continue;
            }
            machine->unk28 = 0;
            if (num2) {
                machine->unk28 = 2;
            }
            if (num3 >= 2) {
                machine->unk28 = 3;
            }
            if (num4 >= 2) {
                machine->unk28 = 4;
            }
            if (sys->stageNo == 4) {
                machine->unk28 = 1;
            } else if (machine->unk1B0[i].y - machine->unk360 < -50.0f) {
                if (sys->stageNo == 2) {
                    machine->unk28 = 4;
                } else if (sys->stageNo == 7) {
                    machine->unk28 = 5;
                }
            }
        }
    }
}

/* 83 insns */
s32 fn_1_237D8(SDSTAGECOLMESH *mesh, HuVecF *pos)
{
    HuVecF dir;
    s32 i;
    float dot;

    if (pos->y > 0.0f) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        VECSubtract(pos, &mesh->tri[1].vtx[i], &dir);
        dir.y = 0.0f;
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF) { 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        dot = VECDotProduct(&mesh->tri[1].edgeNrm[i], &dir);
        if (dot < mesh->tri[1].edgeD[i]) {
            return 0;
        }
    }
    return 1;
}

/* 73 insns */
s32 fn_1_23924(SDSTAGECOLMESH *mesh, HuVecF *pos)
{
    HuVecF dir;
    s32 i;
    float dot;

    for (i = 0; i < 3; i++) {
        VECSubtract(pos, &mesh->tri[0].vtx[i], &dir);
        dir.y = 0.0f;
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF) { 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        dot = VECDotProduct(&mesh->tri[0].edgeNrm[i], &dir);
        if (dot < mesh->tri[0].edgeD[i]) {
            return 0;
        }
    }
    return 1;
}

/* 32 insns */
s32 SdStageFloorCheck(HuVecF *pos, HuVecF *out)
{
    if (sys->stageNo == 0) {
        return StageTrialFloorCheck(pos, out, 0.0f);
    } else {
        return StageMainFloorCheck(pos, out, 0.0f);
    }
}

/* 31 insns */
s32 SdStageYOfsFloorCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    if (sys->stageNo == 0) {
        return StageTrialFloorCheck(pos, out, yOfs);
    } else {
        return StageMainFloorCheck(pos, out, yOfs);
    }
}

/* 164 insns */
static s32 StageTrialFloorCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    s32 z;
    s32 x;
    s32 cx;
    s32 i;
    s32 ret;
    float minDist;
    float dist;
    SDSTAGECOLMESH *mesh;
    SDSTAGECOLMESH *cell;
    HuVecF local;
    HuVecF dir;

    ret = 0;
    cx = 48.0f + pos->x / 50.0f;
    z = 24.0f + pos->z / 100.0f;
    z = (z > 47) ? 47 : ((z < 0) ? 0 : z);
    minDist = 10000.0f;
    for (i = 0; i < 3; i++) {
        x = cx + (i % 3);
        x -= 1;
        x = (x > 95) ? 95 : ((x < 0) ? 0 : x);
        cell = &stageColMesh[z * 96 + x];
        VECSubtract(pos, &cell->pos, &dir);
        dist = VECMag(&dir);
        if (minDist > dist) {
            minDist = dist;
            local = dir;
            mesh = cell;
            stageColCurTriangle = mesh;
        }
    }
    local.y -= yOfs;
    MTXMultVec(mesh->invMtx, &local, &local);
    if (local.y <= 0.0f) {
        ret = 1;
        local = (HuVecF) { 0.0f, -local.y, 0.0f };
        MTXMultVec(mesh->mtx, &local, &local);
        VECAdd(pos, &local, pos);
        if (out != 0) {
            *out = mesh->nrm;
        }
    }
    return ret;
}

/* 165 insns */
static s32 StageMainFloorCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    HuVecF ofs;
    HuVecF upLocal;
    HuVecF local;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    SDSTAGECOLMESH *mesh;
    s32 i;

    for (i = 0; i < stageColFloorNum; i++) {
        mesh = &stageColMesh[i];
        stageColCurTriangle = mesh;
        VECSubtract(pos, &mesh->pos, &local);
        ofs = local;
        ofs.y = 0.0f;
        if (VECMag(&ofs) - yOfs > mesh->radius) {
            continue;
        }
        if (fn_1_23924(mesh, &local)) {
            local.y -= yOfs;
            MTXMultVec(mesh->invMtx, &local, &local);
            MTXMultVec(mesh->invMtx, &up, &upLocal);
            if (local.y > 0.0f) {
                continue;
            }
            VECScale(&up, &ofs, -local.y / upLocal.y);
            VECAdd(pos, &ofs, pos);
            if (out != 0) {
                *out = mesh->nrm;
            }
            return 1;
        }
    }
    return 0;
}

/* 32 insns */
s32 SdStageWallCheck(HuVecF *pos, HuVecF *out)
{
    if (sys->stageNo == 0) {
        return StageTrialWallCheck(pos, out, 0.0f);
    } else {
        return StageMainWallCheck(pos, out, 0.0f);
    }
}

/* 31 insns */
s32 SdStageYOfsWallCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    if (sys->stageNo == 0) {
        return StageTrialWallCheck(pos, out, yOfs);
    } else {
        return StageMainWallCheck(pos, out, yOfs);
    }
}

/* 147 insns */
static s32 StageTrialWallCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    s32 ret = 0;

    if (pos->x + yOfs >= 2350.0f) {
        if (out != 0) {
            *out = (HuVecF) { -1.0f, 0.0f, 0.0f };
        }
        pos->x = 2350.0f - yOfs;
        ret = 1;
    } else if (pos->x - yOfs <= -2350.0f) {
        if (out != 0) {
            *out = (HuVecF) { 1.0f, 0.0f, 0.0f };
        }
        pos->x = -2350.0f + yOfs;
        ret = 1;
    }
    if (pos->z + yOfs >= 2350.0f) {
        if (out != 0) {
            *out = (HuVecF) { 0.0f, 0.0f, -1.0f };
        }
        pos->z = 2350.0f - yOfs;
        ret = 1;
    } else if (pos->z - yOfs <= -2350.0f) {
        if (out != 0) {
            *out = (HuVecF) { 0.0f, 0.0f, 1.0f };
        }
        pos->z = -2350.0f + yOfs;
        ret = 1;
    }
    return ret;
}

/* 294 insns */
static s32 StageMainWallCheck(HuVecF *pos, HuVecF *out, float yOfs)
{
    HuVecF nrm;
    HuVecF nrmLocal;
    HuVecF local;
    float mag;
    float radius;
    SDSTAGECOLMESH *mesh;
    s32 i;
    s32 ret;

    if (stageDataTbl[sys->stageNo].unk8 == 1) {
        nrmLocal = *pos;
        nrm = nrmLocal;
        nrm.y = 0.0f;
        mag = VECMag(&nrm);
        radius = stageDataTbl[sys->stageNo].unkC;
        if (mag + yOfs > radius) {
            VECNormalize(&nrm, &nrm);
            VECScale(&nrm, pos, radius - yOfs);
            pos->y = nrmLocal.y;
            if (out != 0) {
                VECScale(&nrm, out, -1.0f);
            }
            return 1;
        }
    } else {
        ret = 0;
        for (i = 0; i < stageColWallNum; i++) {
            mesh = &stageColWall[i];
            local = (HuVecF) { pos->x, pos->y, pos->z };
            VECSubtract(&local, &mesh->pos, &local);
            MTXMultVec(mesh->invMtx, &local, &local);
            local.y -= yOfs;
            if (!(mesh->flags & 2) && local.y < -40.0f) {
                continue;
            }
            nrm = (HuVecF) { mesh->nrm.x, 0.0f, mesh->nrm.z };
            VECNormalize(&nrm, &nrm);
            MTXMultVec(mesh->invMtx, &nrm, &nrmLocal);
            if (!(mesh->flags & 2)) {
                if (!fn_1_237D8(mesh, &local)) {
                    continue;
                }
            } else if (local.y > 0.0f) {
                continue;
            }
            if (out != 0) {
                *out = nrm;
            }
            VECScale(&nrm, &nrm, (-local.y - 1.0f) / nrmLocal.y);
            VECAdd(pos, &nrm, pos);
            ret = 1;
        }
        if (ret == 1) {
            return 1;
        }
    }
    return 0;
}

/* 45 insns */
float SdStageDistCalc(HuVecF pos)
{
    pos.y = -5000.0f;
    if (sys->stageNo == 0) {
        return StageTrialDistCalc(pos);
    } else {
        return StageMainDistCalc(pos);
    }
}

/* 157 insns */
static float StageTrialDistCalc(HuVecF pos)
{
    HuVecF ofs;
    HuVecF upLocal;
    HuVecF local;
    HuVecF dir;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    s32 z;
    s32 x;
    s32 cx;
    s32 i;
    float minDist;
    float dist;
    SDSTAGECOLMESH *mesh;
    SDSTAGECOLMESH *cell;

    cx = 48.0f + pos.x / 50.0f;
    z = 24.0f + pos.z / 100.0f;
    z = (z > 47) ? 47 : ((z < 0) ? 0 : z);
    minDist = 10000.0f;
    for (i = 0; i < 3; i++) {
        x = cx + (i % 3);
        x -= 1;
        x = (x > 95) ? 95 : ((x < 0) ? 0 : x);
        cell = &stageColMesh[z * 96 + x];
        VECSubtract(&pos, &cell->pos, &dir);
        dist = VECMag(&dir);
        if (minDist > dist) {
            minDist = dist;
            local = dir;
            mesh = cell;
        }
    }
    if (minDist == 10000.0f) {
        return -10000.0f;
    }
    MTXMultVec(mesh->invMtx, &local, &local);
    MTXMultVec(mesh->invMtx, &up, &upLocal);
    VECScale(&up, &ofs, -local.y / upLocal.y);
    VECAdd(&pos, &ofs, &pos);
    return pos.y;
}

/* 145 insns */
static float StageMainDistCalc(HuVecF pos)
{
    HuVecF ofs;
    HuVecF upLocal;
    HuVecF local;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    SDSTAGECOLMESH *mesh;
    s32 i;

    for (i = 0; i < stageColFloorNum; i++) {
        mesh = &stageColMesh[i];
        VECSubtract(&pos, &mesh->pos, &local);
        ofs = local;
        ofs.y = 0.0f;
        if (VECMag(&ofs) > mesh->radius) {
            continue;
        }
        if (fn_1_23924(mesh, &local)) {
            MTXMultVec(mesh->invMtx, &local, &local);
            MTXMultVec(mesh->invMtx, &up, &upLocal);
            VECScale(&up, &ofs, -local.y / upLocal.y);
            VECAdd(&pos, &ofs, &pos);
            return pos.y;
        }
    }
    return -10000.0f;
}

/* 38 insns */
float SdStageRadiusCalc(void)
{
    if (sys->stageNo == 0) {
        return stageWork.unk4 - 25.0f;
    } else if (sys->stageNo == 2 || sys->stageNo == 7) {
        return -25.0f;
    } else {
        return -10000.0f;
    }
}

/* 75 insns */
void SdStageSprPosGet(s32 *type, HuVecF *pos)
{
    *type = stageDataTbl[sys->stageNo].unk8;
    pos->x = stageDataTbl[sys->stageNo].unkC;
    pos->z = stageDataTbl[sys->stageNo].unk10;
    pos->y = SdStageRadiusCalc();
}

/* 514 insns */
HuVecF SdStageRandomPosGet(float radius)
{
    Mtx rot;
    HuVecF pos = { 0.0f, 0.0f, 0.0f };
    HuVecF size;
    s32 type;

    SdStageSprPosGet(&type, &size);
    size.x += radius;
    size.z += radius;
    if (type == 0) {
        pos.x = -size.x + frandmod(2.0f * size.x);
        pos.z = -size.z + frandmod(2.0f * size.z);
    } else {
        pos.x = frandmod(size.x);
        MTXRotRad(rot, 'y', MTXDegToRad(frandmod(360)));
        MTXMultVec(rot, &pos, &pos);
    }
    pos.y = SdStageDistCalc(pos);
    return pos;
}

/* 24 insns */
float SdStageEdgeDistGet(HuVecF pos)
{
    return SdStageEdgeDistRadiusGet(pos, 0.0f);
}

/* 155 insns */
float SdStageEdgeDistRadiusGet(HuVecF pos, float radius)
{
    s32 type;
    HuVecF size;
    float dx;
    float dz;

    SdStageSprPosGet(&type, &size);
    size.x += radius;
    size.z += radius;
    pos.y = 0.0f;
    if (type == 0) {
        if (pos.x < 0.0f) {
            pos.x *= -1.0f;
        }
        if (pos.z < 0.0f) {
            pos.z *= -1.0f;
        }
        dx = size.x - pos.x;
        dz = size.z - pos.z;
        if (dx <= dz) {
            return dx;
        } else {
            return dz;
        }
    } else {
        dx = VECMag(&pos);
        return size.x - dx;
    }
}

/* 216 insns */
void SdStageUpdate(void)
{
    HuVecF dir = { 0.707f, 0.0f, -0.707f };
    float time;
    float amb;

    if (stageLavaModelId != -1) {
        stageWork.unk0++;
        time = stageWork.unk0;
        amb = (1.0 + sin(3.141592653589793 * (4.0f * time) / 180.0)) / 2.0;
        Hu3DModelAmbSet(stageLavaModelId, amb, amb, amb);
        time *= 0.25f;
        amb = (1.0 + sin(3.141592653589793 * time / 180.0)) / 2.0;
        stageWork.unk8[0]->x = 0.25f * amb;
        stageWork.unk8[0]->y = 0.25f * amb;
        stageWork.unk8[1]->x = 1.0f - 0.25f * amb;
        stageWork.unk8[1]->y = 0.25f * amb;
        stageWork.unk8[2]->x = 0.25f * amb;
        stageWork.unk8[2]->y = 1.0f - 0.25f * amb;
        stageWork.unk8[3]->x = 1.0f - 0.25f * amb;
        stageWork.unk8[3]->y = 1.0f - 0.25f * amb;
        DCStoreRangeNoSync(stageWork.unk8[0], 8);
        DCStoreRangeNoSync(stageWork.unk8[1], 8);
        DCStoreRangeNoSync(stageWork.unk8[2], 8);
        DCStoreRangeNoSync(stageWork.unk8[3], 8);
    }
    if (MgSeqModeGet() >= 5) {
        StageRabbitUpdate();
        StageObjUpdate();
    }
    sys->unkFEC++;
    if (sys->stageNo == 7) {
        Stage07SmokeMain();
    }
}

/* 39 insns */
void SdStageObjCreate(void)
{
    StageDataClose();
    sys->unkB60 = 1;
    sys->stageObj = HuMemDirectMallocNum(HEAP_HEAP, 8 * sizeof(SDSTAGEOBJ), HU_MEMNUM_OVL);
    memset(sys->stageObj, 0, 8 * sizeof(SDSTAGEOBJ));
    if (sys->stageNo == 0) {
        StageTrialObjCreate();
    } else {
        StageMainObjCreate();
    }
    SdMachineParticleKill();
    SdMachineParticleCreate();
}

/* 0x1860 */ char lbl_1_data_1860[2] = "g"; /* MakeMainStage's local { "g", "w", NULL } (lbl_1_rodata_E74) */
/* 0x1862 */ char lbl_1_data_1862[2] = "w";

/* 547 insns */
static void StageTrialObjCreate(void)
{
    SDSTAGEOBJ *obj;
    s32 i;
    s32 x;
    s32 y;
    s32 kind;
    s32 *used;
    s32 retry;
    SDSTAGECOLMESH *cell;
    float scale;
    s32 ix;
    s32 iz;
    HuVecF pos;
    HuVecF dir;

    retry = 0;
    used = HuMemDirectMallocNum(HEAP_HEAP, 0x400, HU_MEMNUM_OVL);
    memset(used, 0, 0x380); /* retail: clears 0x380 of the 0x400 bytes (rows 14-15 are never used) */
    for (i = 0; i < 8; i++) {
        retry = 0;
        obj = &sys->stageObj[i];
        obj->mdlId = obj->unk18 = obj->unk16 = -1;
        obj->unk1A = obj->unk1C = -1;
        obj->unk20 = obj->unk24 = -1;
        if (sys->gameType != 0 && i >= 1 && i < 3) {
            continue;
        }
        if (i < 6) {
            while (1) {
                if (++retry >= 10) {
                    break;
                }
                x = rand8() % 8;
                x = (i < 4) ? x + 2 : x + 6;
                x = (x > 16) ? 16 : ((x < 0) ? 0 : x);
                y = rand8() % 8;
                y = (i < 4) ? y + 2 : y + 6;
                y = (y > 16) ? 16 : ((y < 0) ? 0 : y);
                kind = (((s8 *)stageTrialMap)[x + y * 16] >> 4) & 0xF;
                pos = (HuVecF) { 150.0f + 3.0f * (100.0f * x) - 2400.0f, 0.0f, 150.0f + 3.0f * (100.0f * y) - 2400.0f };
                ix = 48.0f + pos.x / 50.0f;
                iz = 24.0f + pos.z / 100.0f;
                cell = &((SDSTAGECOLMESH *)stageColMesh)[ix + iz * 96];
                pos.y = cell->pos.y;
                if (kind >= 3) {
                    continue;
                }
                if (used[x + y * 16] != 0) {
                    continue;
                }
                if (pos.y < 100.0f) {
                    continue;
                }
                PSVECSubtract(&sys->machine[0].pos, &pos, &dir);
                dir.y = 0.0f;
                if (PSVECMag(&dir) < 300.0f + sys->machine[0].unk358) {
                    continue;
                }
                PSVECSubtract(&sys->machine[1].pos, &pos, &dir);
                dir.y = 0.0f;
                if (PSVECMag(&dir) < 300.0f + sys->machine[1].unk358) {
                    continue;
                }
                break;
            }
        } else {
            pos = (HuVecF) { 0.0f, 0.0f, 0.0f };
        }
        if (retry >= 10) {
            continue;
        }
        if (i < 6) {
            kind = rand8() % 4;
        } else if (i == 6) {
            kind = 4;
        } else {
            kind = 5;
        }
        obj->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(objModelFile[kind], HU_MEMNUM_OVL, HEAP_MODEL));
        if (kind == 1 || kind == 2) {
            Hu3DModelAttrSet(obj->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(obj->mdlId, 1.0f);
            obj->unk16 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 108), HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelHookSet(obj->mdlId, "itemhook_c", obj->unk16);
            Hu3DModelAttrSet(obj->unk16, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->unk16, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(obj->unk16, 3);
            Hu3DModelCameraSet(obj->unk16, 3);
            Hu3DMotionSpeedSet(obj->unk16, 1.0f);
            if (kind == 1) {
                Hu3DModelScaleSet(obj->unk16, 1.5f, 1.5f, 1.5f);
                obj->unk1A = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiMotTbl[0], HU_MEMNUM_OVL, HEAP_MODEL));
                obj->unk1C = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiMotTbl[1], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                Hu3DModelScaleSet(obj->unk16, 2.0f, 2.0f, 2.0f);
                obj->unk1A = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiBigMotTbl[0], HU_MEMNUM_OVL, HEAP_MODEL));
                obj->unk1C = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiBigMotTbl[1], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            Hu3DMotionSet(obj->mdlId, obj->unk1A);
        }
        obj->type = kind;
        obj->unk64 = &objDataTbl[kind];
        obj->pos = pos;
        obj->unk5C = 1;
        obj->unk34 = obj->unk64->unk10;
        obj->unk60 = obj->unk64->unk28;
        Hu3DModelPosSetV(obj->mdlId, &pos);
        Hu3DModelLayerSet(obj->mdlId, 0);
        Hu3DModelCameraSet(obj->mdlId, 3);
        if (obj->type == 0) {
            Hu3DModelScaleSet(obj->mdlId, 3.0f, 3.0f, 3.0f);
        }
        obj->unk18 = Hu3DModelLink(sys->unk1E4[4]);
        scale = 2.0f * obj->unk34.x / 100.0f;
        Hu3DModelShadowSet(obj->unk18);
        Hu3DModelPosSetV(obj->unk18, &pos);
        Hu3DModelScaleSet(obj->unk18, scale, 1.0f, scale);
        Hu3DModelLayerSet(obj->unk18, 3);
        Hu3DModelCameraSet(obj->unk18, 3);
        Hu3DModelAttrReset(obj->unk18, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_MOTION_OFF);
        used[x + y * 16] = 1;
        if (i >= 6) {
            Hu3DModelScaleSet(obj->mdlId, 1.5f, 1.5f, 1.5f);
            Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
        }
    }
    HuMemDirectFree(used);
}

/* 551 insns */
static void StageMainObjCreate(void)
{
    SDSTAGEOBJ *obj;
    s32 i;
    s32 kind;
    s32 retry;
    s32 flag;
    float dist;
    float minY;
    float radius;
    HuVecF pos;
    HuVecF dir;

    retry = 0;
    minY = SdStageRadiusCalc();
    minY += 24.0f;
    for (i = 0; i < 8; i++) {
        obj = &sys->stageObj[i];
        obj->mdlId = obj->unk18 = obj->unk16 = -1;
        obj->unk1A = obj->unk1C = -1;
        obj->unk20 = obj->unk24 = -1;
    }
    radius = (sys->machine[0].unk358 > sys->machine[1].unk358) ? 2.0f * sys->machine[0].unk358 : 2.0f * sys->machine[1].unk358;
    for (i = 0; i < 8; i++) {
        if ((sys->gameType != 0 || sys->stageNo == 7) && i >= 3 && i < 6) {
            continue;
        }
        retry = 0;
        obj = &sys->stageObj[i];
        if (i < 6) {
            while (1) {
                if (++retry >= 10) {
                    break;
                }
                pos = SdStageRandomPosGet(-(150.0f + radius));
                if (-10000.0f == pos.y) {
                    flag = 1;
                    continue;
                }
                if (pos.y < minY) {
                    flag = 1;
                    continue;
                }
                PSVECSubtract(&sys->machine[0].pos, &pos, &dir);
                dir.y = 0.0f;
                if (PSVECMag(&dir) < 300.0f + sys->machine[0].unk358) {
                    continue;
                }
                PSVECSubtract(&sys->machine[1].pos, &pos, &dir);
                dir.y = 0.0f;
                if (PSVECMag(&dir) < 300.0f + sys->machine[1].unk358) {
                    continue;
                }
                if (sys->stageNo == 7) {
                    dir = pos;
                    dir.y = 0.0f;
                    dist = PSVECMag(&dir);
                    if (dist < 1000.0f + obj->unk34.x) {
                        continue;
                    }
                    if (dist > 2450.0f - obj->unk34.x) {
                        continue;
                    }
                }
                if (SdStageObjHitCheck(pos, 150.0f + radius) == 0) {
                    break;
                }
            }
        } else {
            pos = (HuVecF) { 0.0f, 0.0f, 0.0f };
        }
        if (retry >= 10) {
            continue;
        }
        if (i < 6) {
            if (sys->stageNo == 2 || sys->stageNo == 5 || sys->stageNo == 7) {
                kind = (rand8() % 2) * 3;
            } else {
                kind = rand8() % 4;
            }
        } else if (i == 6) {
            kind = 4;
        } else {
            kind = 5;
        }
        obj->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(objModelFile[kind], HU_MEMNUM_OVL, HEAP_MODEL));
        if (kind == 1 || kind == 2) {
            Hu3DModelAttrSet(obj->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(obj->mdlId, 1.0f);
            obj->unk16 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 108), HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelHookSet(obj->mdlId, "itemhook_c", obj->unk16);
            Hu3DModelAttrSet(obj->unk16, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->unk16, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(obj->unk16, 3);
            Hu3DModelCameraSet(obj->unk16, 3);
            Hu3DMotionSpeedSet(obj->unk16, 1.0f);
            if (kind == 1) {
                Hu3DModelScaleSet(obj->unk16, 1.5f, 1.5f, 1.5f);
                obj->unk1A = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiMotTbl[0], HU_MEMNUM_OVL, HEAP_MODEL));
                obj->unk1C = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiMotTbl[1], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                Hu3DModelScaleSet(obj->unk16, 2.0f, 2.0f, 2.0f);
                obj->unk1A = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiBigMotTbl[0], HU_MEMNUM_OVL, HEAP_MODEL));
                obj->unk1C = Hu3DJointMotion(obj->mdlId, HuDataSelHeapReadNum(objBomheiBigMotTbl[1], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            Hu3DMotionSet(obj->mdlId, obj->unk1A);
        }
        obj->type = kind;
        obj->unk64 = &objDataTbl[kind];
        obj->pos = pos;
        obj->unk5C = 1;
        obj->unk34 = obj->unk64->unk10;
        obj->unk60 = obj->unk64->unk28;
        Hu3DModelPosSetV(obj->mdlId, &pos);
        Hu3DModelLayerSet(obj->mdlId, 0);
        Hu3DModelCameraSet(obj->mdlId, 3);
        if (obj->type == 0) {
            Hu3DModelScaleSet(obj->mdlId, 3.0f, 3.0f, 3.0f);
        }
        obj->unk18 = Hu3DModelLink(sys->unk1E4[4]);
        dist = 2.0f * obj->unk34.x / 100.0f;
        Hu3DModelShadowSet(obj->unk18);
        Hu3DModelPosSetV(obj->unk18, &pos);
        Hu3DModelScaleSet(obj->unk18, dist, 1.0f, dist);
        Hu3DModelLayerSet(obj->unk18, 3);
        Hu3DModelCameraSet(obj->unk18, 3);
        Hu3DModelAttrReset(obj->unk18, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_MOTION_OFF);
        if (i >= 6) {
            obj->unk5C = 0;
            Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(obj->mdlId, 1.5f, 1.5f, 1.5f);
            Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
        }
    }
}

/* 77 insns */
static void StageDataClose(void)
{
    SDSTAGEOBJ *obj;
    s32 i;

    if (sys->unkB60 != 0) {
        for (i = 0; i < 8; i++) {
            obj = &sys->stageObj[i];
            if (obj->unk1A != -1) {
                Hu3DMotionSet(obj->mdlId, -1);
                Hu3DMotionKill(obj->unk1A);
                Hu3DMotionKill(obj->unk1C);
                obj->unk1A = obj->unk1C = -1;
            }
            if (obj->unk16 != -1) {
                Hu3DModelHookReset(obj->mdlId);
                Hu3DModelKill(obj->unk16);
            }
            if (obj->mdlId != -1) {
                Hu3DModelKill(obj->mdlId);
            }
            if (obj->unk18 != -1) {
                Hu3DModelKill(obj->unk18);
            }
            obj->mdlId = obj->unk18 = obj->unk16 = -1;
        }
        HuMemDirectFree(sys->stageObj);
        sys->stageObj = NULL;
    }
    sys->unkB60 = 0;
}

/* 0x1870 */ static SDSTAGEOBJFUNC objUpdateFuncTbl[6] = { StageDokanUpdate, StageBomheiUpdate, StageBomheiBigUpdate, StageTogezoUpdate, StageKinokoUpdate, StageNKinokoUpdate };

/* 104 insns */
static void StageObjUpdate(void)
{
    SDSTAGEOBJ *obj;
    s32 i;

    if (sys->stageObj != 0) {
        if (3600.0f == MgTimerValueGet(sys->timer) || 1800.0f == MgTimerValueGet(sys->timer)) {
            if (rand8() % 10 == 0) {
                sys->stageObj[7].mode = 1;
            } else {
                sys->stageObj[6].mode = 1;
            }
        }
        for (i = 0; i < 8; i++) {
            obj = &sys->stageObj[i];
            if (obj->mdlId != -1) {
                objUpdateFuncTbl[obj->type](obj);
                StageUpdateFire(obj);
            }
        }
    }
}

/* 10 insns */
static void StageDokanUpdate(SDSTAGEOBJ *obj)
{
    StageObjCol(obj);
}

/* 10 insns */
static void StageTogezoUpdate(SDSTAGEOBJ *obj)
{
    StageObjCol(obj);
}

/* 418 insns */
static void StageBomheiUpdate(SDSTAGEOBJ *obj)
{
    float scale;

    switch (obj->mode) {
        case 0:
            obj->unk60 = 0;
            if (MgSeqModeGet() == 5) {
                if (obj->unk58 != 0 || ++obj->unk8 >= obj->unk64->unk1C) {
                    Hu3DMotionSet(obj->mdlId, obj->unk1C);
                    Hu3DMotionTimeSet(obj->mdlId, 0.0f);
                    Hu3DModelAttrReset(obj->unk16, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(obj->unk16, 0.0f);
                    obj->mode++;
                    obj->unk8 = 0;
                }
            }
            StageObjCol(obj);
            break;
        case 1:
            if (MgSeqModeGet() == 5) {
                if (++obj->unk8 >= 60.0f) {
                    if (obj->type == 1) {
                        SdImpactStart(0x557, obj->pos, 1.0f, 1, obj->unk64->unk24);
                    } else {
                        SdImpactStart(0x559, obj->pos, 1.0f, 1, obj->unk64->unk24);
                    }
                    Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->unk16, HU3D_ATTR_DISPOFF);
                    Hu3DMotionSet(obj->mdlId, obj->unk1A);
                    Hu3DMotionTimeSet(obj->mdlId, 0.0f);
                    Hu3DModelScaleSet(obj->mdlId, 0.0f, 0.0f, 0.0f);
                    Hu3DModelScaleSet(obj->unk18, 0.0f, 0.0f, 0.0f);
                    SdModelGlowSet(obj->mdlId);
                    obj->unk60 = 1;
                    StageCreateDust(obj, obj->unk64->unk24 / 450.0f);
                    obj->unk8 = 0;
                    obj->mode++;
                }
            }
            StageObjCol(obj);
            break;
        case 2:
            if (MgSeqModeGet() == 5) {
                scale = obj->unk64->unk10.x;
                scale += obj->unk8 * (obj->unk64->unk24 - obj->unk64->unk10.x) / 15.0f;
                obj->unk34 = (HuVecF) { scale, scale, scale };
                StageObjCol(obj);
                if (++obj->unk8 >= 15.0f) {
                    obj->unk5C = 0;
                    obj->unk8 = 0;
                    obj->mode++;
                }
            }
            break;
        case 3:
            if (MgSeqModeGet() == 5) {
                obj->unk58 = obj->unk60 = 0;
                obj->unk34 = obj->unk64->unk10;
                if (++obj->unk8 >= obj->unk64->unk20) {
                    Hu3DModelAttrReset(obj->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(obj->unk18, HU3D_ATTR_DISPOFF);
                    obj->unk5C = 1;
                    obj->unk8 = 0;
                    obj->mode++;
                }
            }
            break;
        case 4:
            if (MgSeqModeGet() == 5) {
                obj->unk8++;
                scale = obj->unk8 / 60.0f;
                Hu3DModelScaleSet(obj->mdlId, scale, scale, scale);
                scale *= 2.0f * obj->unk64->unk10.x / 100.0f;
                Hu3DModelScaleSet(obj->unk18, scale, scale, scale);
                if (scale <= 0.0f) {
                    scale = 0.01f;
                }
                obj->unk34 = (HuVecF) { obj->unk64->unk10.x * scale, obj->unk64->unk10.y * scale, obj->unk64->unk10.z * scale };
            }
            StageObjCol(obj);
            if (MgSeqModeGet() == 5 && obj->unk8 >= 60.0f) {
                Hu3DModelScaleSet(obj->mdlId, 1.0f, 1.0f, 1.0f);
                scale = 2.0f * obj->unk64->unk10.x / 100.0f;
                Hu3DModelScaleSet(obj->unk18, scale, scale, scale);
                obj->unk58 = 0;
                obj->mode = obj->unk8 = 0;
            }
            break;
    }
}

/* 10 insns */
static void StageBomheiBigUpdate(SDSTAGEOBJ *obj)
{
    StageBomheiUpdate(obj);
}

/* 885 insns */
static void StageKinokoUpdate(SDSTAGEOBJ *obj)
{
    s32 target;
    s32 retry;
    s32 machineNo;
    float value;
    Mtx mtx;
    HuVecF center;
    HuVecF dir;
    HuVecF pos;

    if (MgSeqModeGet() != 5) {
        return;
    }
    switch (obj->mode) {
        case 0:
            break;
        case 1:
            if (sys->gameType == 0) {
                if (sys->machine[0].unkE4 == sys->machine[1].unkE4) {
                    target = 0;
                } else if (sys->machine[0].unkE4 < sys->machine[1].unkE4) {
                    target = 1;
                } else {
                    target = 2;
                }
            } else if (sys->gameType == 1) {
                target = SdFlagDispTimerGet(0) - SdFlagDispTimerGet(1);
                if (target == -1) {
                    target = 1;
                } else if (target == 1) {
                    target = 2;
                }
            } else if (sys->gameType == 2) {
                target = SdRabbitDispTimerGet(0) - SdRabbitDispTimerGet(1);
                if (target == -1) {
                    target = 1;
                } else if (target == 1) {
                    target = 2;
                }
            }
            if (target == 0) {
                dir = sys->machine[0].pos;
                pos = sys->machine[1].pos;
                dir.y = pos.y = 0.0f;
                center = (HuVecF) { (dir.x + pos.x) / 2.0f, 0.0f, (dir.z + pos.z) / 2.0f };
                PSVECSubtract(&dir, &pos, &dir);
                if (0.0f == PSVECMag(&dir)) {
                    dir = (HuVecF) { 1.0f, 1.0f, 1.0f };
                }
                PSVECNormalize(&dir, &dir);
                MathPlaneRotMtxGet(&dir, NULL, 0.0f, mtx);
                dir = (HuVecF) { mtx[0][0], mtx[1][0], mtx[2][0] };
                retry = 0;
                while (1) {
                    value = 200.0f * (rand8() % 72 - 36);
                    PSVECScale(&dir, &pos, value);
                    PSVECAdd(&pos, &center, &pos);
                    if (++retry > 25) {
                        break;
                    }
                    if (StageKinokoCheck(pos, 100.0f) == 0) {
                        continue;
                    }
                    if (PSVECDistance(&pos, &sys->machine[0].pos) < 300.0f) {
                        continue;
                    }
                    center = pos;
                    break;
                }
            } else {
                machineNo = target - 1;
                retry = 0;
                do {
                    center = SdRandomPosGet(0, sys->machine[machineNo].pos, NULL, 1000.0f, 300.0f);
                    if (++retry > 25) {
                        break;
                    }
                } while (StageKinokoCheck(center, 100.0f) == 0
                    || PSVECDistance(&center, &sys->machine[machineNo].pos) > PSVECDistance(&center, &sys->machine[machineNo ^ 1].pos));
            }
            if (retry > 25) {
                break;
            }
            center.y = SdStageDistCalc(center);
            obj->unk40 = center;
            SdImpactSoundStart(0x579, center, 1.0f);
            center.y -= 150.0f;
            Hu3DModelAttrReset(obj->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelPosSetV(obj->mdlId, &center);
            if (sys->stageNo != 3) {
                center.y += 150.0f;
            } else {
                center.y += 180.0f;
            }
            Hu3DModelPosSetV(obj->unk18, &center);
            obj->unk8 = 0;
            obj->mode++;
            break;
        case 2:
            obj->unk8++;
            value = 150.0f - 150.0f * MathLerp(1, obj->unk8 / 60.0f);
            Hu3DData[obj->mdlId].pos.y = obj->unk40.y - value;
            if (obj->unk8 >= 12.0f) {
                Hu3DModelAttrReset(obj->unk18, HU3D_ATTR_DISPOFF);
            }
            if (obj->unk8 >= 60.0f) {
                obj->unk5C = 1;
                obj->pos = Hu3DData[obj->mdlId].pos;
                obj->unk8 = 0;
                obj->mode++;
            }
            break;
        case 3:
            obj->unk8++;
            if (obj->unk8 >= 660.0f) {
                if (obj->unk8 % 2) {
                    Hu3DModelAttrReset(obj->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(obj->unk18, HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
                }
            }
            if (obj->unk8 >= 900.0f) {
                Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
                obj->mode = obj->unk8 = 0;
                obj->unk5C = 0;
            }
            StageObjCol(obj);
            break;
    }
}

/* 573 insns */
static s32 StageKinokoCheck(HuVecF pos, float radius)
{
    float dist;

    if (SdStageEdgeDistRadiusGet(pos, -(200.0f + radius)) <= 0.0f) {
        return 0;
    }
    if (SdStageBaseObjHitCheck(pos, radius)) {
        return 0;
    }
    if (sys->stageNo == 7) {
        pos.y = 0.0f;
        dist = PSVECMag(&pos);
        if (dist < 1000.0f + radius || dist > 2450.0f - radius) {
            return 0;
        }
    } else if (SdStageDistCalc(pos) <= 24.0f + SdStageRadiusCalc()) {
        return 0;
    }
    return 1;
}

/* 10 insns */
static void StageNKinokoUpdate(SDSTAGEOBJ *obj)
{
    StageKinokoUpdate(obj);
}

/* 450 insns */
static void StageObjCol(SDSTAGEOBJ *obj)
{
    HuVecF dir;
    HuVecF dirOld;
    HuVecF vec;
    HuVecF refl;
    float dist;
    float diff;
    SDMACHINE *machine;
    s32 i;
    s16 mdlId;

    if (obj->unk5C == 0) {
        return;
    }
    for (i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        dir = machine->pos;
        if (machine->unk368 & 2) {
            dir.y -= machine->unk354;
        }
        if (dir.y - machine->unk354 > obj->pos.y + obj->unk34.y) {
            continue;
        }
        if (dir.y + machine->unk35C < obj->pos.y) {
            continue;
        }
        VECSubtract(&dir, &obj->pos, &dir);
        dirOld = dir;
        dir.y = 0.0f;
        dist = VECMag(&dir);
        if (dist > machine->unk358 + obj->unk34.x) {
            continue;
        }
        if (obj->type == 4 || obj->type == 5) {
            Hu3DModelAttrSet(obj->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(obj->unk18, HU3D_ATTR_DISPOFF);
            obj->unk5C = 0;
            obj->mode = obj->unk8 = 0;
            machine->unk32C = 0;
            if (obj->type == 4) {
                machine->unk328 = 1;
                mdlId = sys->unk1E4[0];
                SdPlayerSoundPlay(machine, 2);
                HuAudFXPlayVolPan(machine->playerNo + 0x575, 0x7F, (machine->playerNo << 5) + 0x30);
            } else {
                machine->unk328 = 2;
                mdlId = sys->unk1E4[2];
                SdPlayerSoundPlay(machine, 3);
                HuAudFXPlayVolPan(machine->playerNo + 0x577, 0x7F, (machine->playerNo << 5) + 0x30);
            }
            Hu3DMotionTimeSet(mdlId, 0.0f);
            SdVibrate(machine->playerNo, 1, 15);
            return;
        }
        obj->unk58 = 1;
        VECSubtract(&machine->unk138, &obj->pos, &vec);
        diff = VECMag(&vec);
        VECSubtract(&machine->pos, &obj->pos, &vec);
        diff -= VECMag(&vec);
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        VECScale(&dir, &dir, (machine->unk358 + obj->unk34.x) - dist);
        if (obj->unk64->unk24 == 0.0f || obj->mode < 2 || obj->mode >= 4) {
            if (machine->mode == 2) {
                refl = (HuVecF){ machine->unk21C[0][2], machine->unk21C[1][2], machine->unk21C[2][2] };
                if (VECMag(&vec) == 0.0f) {
                    vec = (HuVecF){ 1.0f, 1.0f, 1.0f };
                }
                VECNormalize(&vec, &vec);
                VECScale(&vec, &vec, -1.0f);
                VECReflect(&refl, &vec, &refl);
                refl.y = 0.0f;
                MathPlaneRotMtxGet(&refl, NULL, 0.0f, machine->unk21C);
            }
            if (VECMag(&machine->unk160) > 1.5f + machine->unk28C) {
                if (machine->unk334 == 0) {
                    if (sys->unkB68 || sys->unkB6C) {
                        machine->unk334 = 1;
                    }
                    HuAudFXPlayVolPan(machine->playerNo + 0x563, 0x7F, (machine->playerNo << 5) + 0x30);
                    SdVibrate(machine->playerNo, 0, 5);
                }
            }
            machine->pos.x += dir.x;
            machine->pos.z += dir.z;
        }
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        if (diff < 5.0f) {
            diff = 5.0f;
        }
        VECScale(&dir, &dir, 0.5f * diff);
        machine->unkE8 = (HuVecF){ dir.x, 0.0f, dir.z };
        if (machine->unk210 == 0 && obj->unk60 != 0) {
            VECSubtract(&machine->pos, &obj->pos, &dir);
            if (machine->bodyNo == 10) {
                SdMachineDamage(machine, dir, obj->unk64->unk28 / 2.0f);
            } else {
                SdMachineDamage(machine, dir, obj->unk64->unk28);
            }
        }
    }
}

/* 24 insns */
s32 SdStageObjHitCheck(HuVecF pos, float radius)
{
    return SdStageObjHitCheck2(pos, radius, 0);
}

/* 24 insns */
s32 SdStageBaseObjHitCheck(HuVecF pos, float radius)
{
    return SdStageBaseObjHitCheck2(pos, radius, 0);
}

/* 96 insns */
s32 SdStageObjHitCheck2(HuVecF pos, float radius, s32 a1)
{
    HuVecF dir;
    HuVecF dirOld;
    float dist;
    SDSTAGEOBJ *obj;
    s32 i;

    if (sys->stageObj == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        obj = &sys->stageObj[i];
        if (obj->mdlId == -1 || obj->unk5C == 0) {
            continue;
        }
        VECAdd(&obj->pos, &obj->unk64->unk4, &dir);
        VECSubtract(&pos, &dir, &dir);
        dirOld = dir;
        if (obj->unk64->unk0 == 1) {
            dir.y = 0.0f;
        }
        dist = VECMag(&dir);
        if (dist > radius + obj->unk34.x) {
            continue;
        }
        if (a1 == 1) {
            if (obj->unk64->unk0 == 1) {
                if (dirOld.y < 0.0f || dirOld.y > obj->unk34.y) {
                    continue;
                }
            }
            obj->unk58 = 1;
        }
        return 1;
    }
    return 0;
}

/* 95 insns */
s32 SdStageBaseObjHitCheck2(HuVecF pos, float radius, s32 a1)
{
    HuVecF dir;
    HuVecF dirOld;
    float dist;
    SDSTAGEOBJ *obj;
    s32 i;

    if (sys->stageObj == 0) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        obj = &sys->stageObj[i];
        if (obj->mdlId == -1) {
            continue;
        }
        VECAdd(&obj->pos, &obj->unk64->unk4, &dir);
        VECSubtract(&pos, &dir, &dir);
        dirOld = dir;
        if (obj->unk64->unk0 == 1) {
            dir.y = 0.0f;
        }
        dist = VECMag(&dir);
        if (dist > radius + obj->unk64->unk10.x) {
            continue;
        }
        if (a1 == 1) {
            if (obj->unk64->unk0 == 1) {
                if (dirOld.y < 0.0f || dirOld.y > obj->unk64->unk10.y) {
                    continue;
                }
            }
            obj->unk58 = 1;
        }
        return 1;
    }
    return 0;
}

/* 205 insns */
static void StageRabbitUpdate(void)
{
    HuVecF dir;
    HuVecF dirOld;
    HuVecF vec;
    HuVecF rabbitPos;
    float dist;
    float diff;
    SDMACHINE *machine;
    s32 i;

    if (sys->gameType != 2) {
        return;
    }
    if (SdRabbitDoneCheck()) {
        return;
    }
    if (!SdRabbitCheck()) {
        return;
    }
    rabbitPos = SdRabbitPosGet();
    for (i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        dir = machine->pos;
        if (dir.y - machine->unk354 > 90.0f + rabbitPos.y) {
            continue;
        }
        if (dir.y + machine->unk35C < rabbitPos.y) {
            continue;
        }
        VECSubtract(&dir, &rabbitPos, &dir);
        dirOld = dir;
        dir.y = 0.0f;
        dist = VECMag(&dir);
        if (dist > 100.0f + machine->unk358) {
            continue;
        }
        VECSubtract(&machine->unk138, &rabbitPos, &vec);
        diff = VECMag(&vec);
        VECSubtract(&machine->pos, &rabbitPos, &vec);
        diff -= VECMag(&vec);
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        VECScale(&dir, &dir, (100.0f + machine->unk358) - dist);
        machine->pos.x += dir.x;
        machine->pos.z += dir.z;
        if (VECMag(&dir) == 0.0f) {
            dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
        }
        VECNormalize(&dir, &dir);
        if (diff < 5.0f) {
            diff = 5.0f;
        }
        VECScale(&dir, &dir, 0.5f * diff);
        machine->unkE8 = (HuVecF){ dir.x, 0.0f, dir.z };
    }
}

/* 51 insns */
static void StageCreateDust(SDSTAGEOBJ *obj, float scale)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLE *particle2;
    HU3DPARTICLEDATA *data;
    HU3DPARTICLEDATA *data2;

    particle = Hu3DData[sys->particleMdlId[3]].hookData;
    data = &particle->data[obj->unk20];
    particle2 = Hu3DData[sys->particleMdlId[4]].hookData;
    data2 = &particle2->data[obj->unk24];
    SdEffectDustCreateData(obj->pos, data, data2, scale);
}

/* 47 insns */
static void StageUpdateFire(SDSTAGEOBJ *obj)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLE *particle2;
    HU3DPARTICLEDATA *data;
    HU3DPARTICLEDATA *data2;

    if (obj->unk20 != -1) {
        particle = Hu3DData[sys->particleMdlId[3]].hookData;
        data = &particle->data[obj->unk20];
        particle2 = Hu3DData[sys->particleMdlId[4]].hookData;
        data2 = &particle2->data[obj->unk24];
        SdEffectFlameUpdate(data, 48);
        SdEffectFlameUpdateData(data2, 25);
    }
}

/* 0x1888 */ static HuVecF shadowCamPos = { 0.0f, 6000.0f, 0.0f };
/* 0x1894 */ static HuVecF shadowCamUp = { 0.0f, 0.0f, -1.0f };
/* 0x18A0 */ static HuVecF shadowCamTarget = { 0.0f, 0.0f, 0.0f };

/* 291 insns */
static void MakeStageLight(void)
{
    HuVecF lightPos = { 0.0f, 1000.0f, 0.0f };
    HuVecF shadowPos;
    HuVecF shadowUp;
    HuVecF shadowTarget;
    HuVecF lightDir = { 1.0f, -1.0f, 1.0f };
    GXColor color = { 255, 255, 255, 128 };

    if (sys->unk15C != -1) {
        Hu3DGLightKill(sys->unk15C);
    }
    sys->unk15C = Hu3DGLightCreateV(&lightPos, &lightDir, &color);
    Hu3DGLightStaticSet(sys->unk15C, TRUE);
    if (sys->stageNo == 3) {
        lightPos = (HuVecF){ 0.0f, 1000.0f, 0.0f };
        lightDir = (HuVecF){ 0.0f, -1.0f, 1.0f };
        color = (GXColor){ 255, 128, 0, 255 };
        shadowPos = (HuVecF){ 0.0f, 3000.0f, -7000.0f };
        shadowUp = (HuVecF){ 0.0f, 1.0f, 0.0f };
        shadowTarget = (HuVecF){ 0.0f, -3000.0f, 7000.0f };
        Hu3DGLightInfinitytSet(sys->unk15C);
    } else if (sys->stageNo == 7) {
        lightPos = (HuVecF){ 0.0f, 3000.0f, 0.0f };
        shadowPos = shadowCamPos;
        shadowUp = shadowCamUp;
        shadowTarget = shadowCamTarget;
        Hu3DGLightPointSet(sys->unk15C, 3000.0f, 0.95f, GX_DA_MEDIUM);
    } else {
        lightPos = (HuVecF){ 0.0f, 1000.0f, 0.0f };
        shadowPos = shadowCamPos;
        shadowUp = shadowCamUp;
        shadowTarget = shadowCamTarget;
        Hu3DGLightInfinitytSet(sys->unk15C);
    }
    Hu3DGLightPosSetV(sys->unk15C, &lightPos, &lightDir);
    Hu3DGLightColorSet(sys->unk15C, color.r, color.g, color.b, color.a);
    Hu3DShadowMultiPosSet(&shadowPos, &shadowUp, &shadowTarget, 3);
}

/* 106 insns */
static void StageHamonCreate(void)
{
    sys->hamon.unk0 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    sys->hamon.unk4 = HuSprAnimDataRead(DATANUM(DATA_sd00, 157));
    sys->hamon.unk8 = HuSprAnimDataRead(DATANUM(DATA_sd00, 158));
    sys->hamon.pos[0].x = sys->hamon.pos[0].y = sys->hamon.pos[0].z = sys->hamon.pos[1].x = sys->hamon.pos[1].y = sys->hamon.pos[1].z = 0.0f;
    sys->hamon.color = (GXColor){ 0, 0, 0, 0 };
    sys->hamon.unkC = 0.0f;
    sys->hamon.speed = -0.02f;
}

/* 33 insns */
static void StageHamonKill(void)
{
    if (sys->hamon.unk0 != 0) {
        HuMemDirectFree(sys->hamon.unk0);
        sys->hamon.unk0 = 0;
        HuSprAnimKill(sys->hamon.unk4);
        HuSprAnimKill(sys->hamon.unk8);
    }
}

/* 40 insns */
static void StageHamonLayerHook(s16 layerNo)
{
    HU3DWATER *water = &Hu3DWaterData;
    if (Hu3DCameraBit & 4) {
        GXSetTexCopySrc(0, 0, 640, 480);
        GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(sys->hamon.unk0, GX_FALSE);
        if (omUPauseFlag + omPauseChk() != 0) {
            return;
        }
    }
}

/* 31 insns */
static void StageHamonPosSet(HuVecF pos1, HuVecF pos2)
{
    sys->hamon.pos[0].x = pos1.x;
    sys->hamon.pos[0].y = pos1.y;
    sys->hamon.pos[0].z = pos1.z;
    sys->hamon.pos[1].x = pos2.x;
    sys->hamon.pos[1].y = pos2.y;
    sys->hamon.pos[1].z = pos2.z;
}

/* 12 insns */
static void StageHamonColorSet(GXColor *color)
{
    sys->hamon.color = *color;
}

/* 5 insns */
static void StageHamonSpeedSet(float speed)
{
    sys->hamon.speed = speed;
}

/* 363 insns */
static void StageHamonMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    HU3DCAMERA *cameraP = &Hu3DCamera[Hu3DCameraNo];
    float transS;
    Mtx objMtx;
    Mtx scaleMtx;
    Mtx mtx;
    Mtx lightMtx;
    Mtx invCamMtx;
    GXTexObj texObj;
    s32 pauseF;

    if ((pauseF = omUPauseFlag + omPauseChk()) == 0) {
        sys->hamon.unkC += sys->hamon.speed;
    }
    GXInitTexObj(&texObj, sys->hamon.unk0, 320, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    HuSprTexLoad(sys->hamon.unk4, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(sys->hamon.unk8, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    /* retail: camera Hu3DCameraNo - 2 (the hamon model draws in camera 2 only: StageHamonLayerHook) */
    transS = (Hu3DCamera[Hu3DCameraNo - 2].scissorX + (Hu3DCamera[Hu3DCameraNo - 2].scissorW / 2.0f)) / 640.0f;
    C_MTXLightPerspective(lightMtx, cameraP->fov, 1.2f, 0.5f, -0.5f, transS, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, invCamMtx);
    PSMTXConcat(invCamMtx, drawObj->matrix, objMtx);
    PSMTXConcat(lightMtx, Hu3DCameraMtx, mtx);
    PSMTXConcat(mtx, objMtx, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(objMtx, 0, sys->hamon.unkC, 0);
    PSMTXScale(scaleMtx, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(scaleMtx, objMtx, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, sys->hamon.color);
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
    GXSetIndTexMtx(GX_ITM_0, (float (*)[3])sys->hamon.pos, -1);
}

/* 766 insns */
static void StageTrialMakeGround(void)
{
    s32 specialTbl[2][4] = { { 16, 32, 48, 64 }, { 32, 32, 48, 64 } };
    s32 lavaF;

    if (stageTrialHeight > 0.0f) {
        if (rand8() % 6 == 0) {
            if (rand8() % 2) {
                sys->unkA34[0] = (HuVecF){ 300.0f * (rand8() % 6), 0.0f, 300.0f * (rand8() % 6 + 10) };
                StageTrialClearDist(sys->unkA34[0], 800.0f);
            }
            if (rand8() % 2) {
                sys->unkA34[1] = (HuVecF){ 300.0f * (rand8() % 6 + 10), 0.0f, 300.0f * (rand8() % 6) };
                StageTrialClearDist(sys->unkA34[1], 800.0f);
            }
        }
        StageTrialAddSlope((HuVecF){ 300.0f * (rand8() % 16), 2.6f * stageTrialHeight, 300.0f * (rand8() % 16) }, 1000.0f);
        StageTrialAddSlope((HuVecF){ 300.0f * (rand8() % 16), 2.6f * stageTrialHeight, 300.0f * (rand8() % 16) }, 1000.0f);
        StageTrialAddSlope((HuVecF){ 300.0f, 2.6f * stageTrialHeight, 300.0f }, 1000.0f);
        StageTrialAddSlope((HuVecF){ 4200.0f, 2.6f * stageTrialHeight, 4200.0f }, 1000.0f);
        StageTrialAddSlope2((HuVecF){ 900.0f, 0.6f * stageTrialHeight, 900.0f }, (HuVecF){ 3600.0f, 0.6f * stageTrialHeight, 3600.0f }, 600.0f);
        if (rand8() % 2) {
            StageTrialAddSlope2((HuVecF){ 900.0f, 1.6f * stageTrialHeight, 3600.0f }, (HuVecF){ 3600.0f, 1.6f * stageTrialHeight, 900.0f }, 300.0f);
        }
    }
    lavaF = (stageTrialLavaFloorOnF != 0) ? 1 : 0;
    if (rand8() % 2) {
        StageTrialAddSpecial(rand8() % 3, rand8() % 3, rand8() % 15 + 10, specialTbl[lavaF][rand8() % 4]);
        StageTrialAddSpecial(rand8() % 5 + 10, rand8() % 5 + 10, rand8() % 15 + 10, specialTbl[lavaF][rand8() % 4]);
        StageTrialAddSpecial(rand8() % 5, rand8() % 5 + 10, rand8() % 15 + 10, specialTbl[lavaF][rand8() % 4]);
        StageTrialAddSpecial(rand8() % 5 + 10, rand8() % 5, rand8() % 15 + 10, specialTbl[lavaF][rand8() % 4]);
        StageTrialAddSpecial(8, 8, rand8() % 15 + 10, specialTbl[lavaF][rand8() % 4]);
    }
    StageTrialAddBoundary();
}

/* 479 insns */
static s32 StageTrialAddNoise(s32 *x, s32 *y, s32 flag)
{
    ((s8 *)stageTrialMap)[(*y * 16) + *x] &= 0x8F;
    ((s8 *)stageTrialMap)[(*y * 16) + *x] |= flag;
    if (--stageTrialNoiseNum > 0) {
        stageTrialNoiseDec = rand8() % 4;
        if (stageTrialNoiseDec == 0) {
            stageTrialNoiseX = *x;
            stageTrialNoiseY = *y - 1;
        } else if (stageTrialNoiseDec == 1) {
            stageTrialNoiseX = *x;
            stageTrialNoiseY = *y + 1;
        } else if (stageTrialNoiseDec == 2) {
            stageTrialNoiseX = *x - 1;
            stageTrialNoiseY = *y;
        } else {
            stageTrialNoiseX = *x + 1;
            stageTrialNoiseY = *y;
        }
        stageTrialNoiseX = (stageTrialNoiseX > 15) ? 15 : ((stageTrialNoiseX < 0) ? 0 : stageTrialNoiseX);
        stageTrialNoiseY = (stageTrialNoiseY > 15) ? 15 : ((stageTrialNoiseY < 0) ? 0 : stageTrialNoiseY);
        StageTrialAddNoise(&stageTrialNoiseX, &stageTrialNoiseY, flag);
    }
}

/* 115 insns */
static void StageTrialAddSpecial(s32 x, s32 y, s32 noiseNum, s32 flag)
{
    s32 x2 = (x < 8) ? x + 1 : x - 1;
    s32 y2 = (y < 8) ? y + 1 : y - 1;
    stageTrialMap[x + y * 16] &= 0x8F;
    stageTrialMap[x + y * 16] |= flag;
    stageTrialMap[x2 + y * 16] &= 0x8F;
    stageTrialMap[x2 + y * 16] |= flag;
    stageTrialMap[x + y2 * 16] &= 0x8F;
    stageTrialMap[x + y2 * 16] |= flag;
    stageTrialMap[x2 + y2 * 16] &= 0x8F;
    stageTrialMap[x2 + y2 * 16] |= flag;
    stageTrialNoiseNum = noiseNum;
    StageTrialAddNoise(&x2, &y2, flag);
}
/* 339 insns */
static void StageTrialAddBoundary(void)
{
    s32 x;
    s32 y;
    s32 i;
    s32 j;
    s32 nType;
    s32 type;
    s32 num;
    s32 ny;
    s32 nx;
    s32 count;
    s32 typeR;
    s32 typeD;
    float amp;
    s32 flag;

    flag = 0;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            for (i = 0; i < 8; i++) {
                for (j = 0; j < 8; j++) {
                    stageTrialMapColType[j + x * 8 + (i + y * 8) * 128] = (stageTrialMap[x + y * 16] >> 4) & 7;
                }
            }
        }
    }
    if (stageTrialSmooth >= 3) {
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                flag = 0;
                type = (stageTrialMap[x + y * 16] >> 4) & 7;
                for (i = 0; i < 9; i++) {
                    ny = y - 1 + i / 3;
                    ny = (ny > 15) ? 15 : ((ny < 0) ? 0 : ny);
                    nx = x - 1 + i % 3;
                    nx = (nx > 15) ? 15 : ((nx < 0) ? 0 : nx);
                    nType = (stageTrialMap[nx + ny * 16] >> 4) & 7;
                    if (type != nType) {
                        stageTrialMap[x + y * 16] |= 0x80;
                        if (i == 5) {
                            flag |= 1;
                            typeR = nType;
                        }
                        if (i == 7) {
                            flag |= 2;
                            typeD = nType;
                        }
                    }
                }
                if (flag & 1) {
                    for (i = 0; i < 8; i++) {
                        if (i % 4 == 0) {
                            count = rand8() % 2 + 1;
                            amp = (count == 0) ? 45.0f : 22.5f;
                        }
                        num = count + count * sin(M_PI * (i * amp) / 180.0);
                        for (j = 0; j < num; j++) {
                            stageTrialMapColType[(7 - j) + x * 8 + (i + y * 8) * 128] = typeR;
                        }
                    }
                }
                if (flag & 2) {
                    for (j = 0; j < 8; j++) {
                        if (j % 4 == 0) {
                            count = rand8() % 2 + 1;
                            amp = (count == 0) ? 45.0f : 22.5f;
                        }
                        num = count + count * sin(M_PI * (j * amp) / 180.0);
                        for (i = 0; i < num; i++) {
                            stageTrialMapColType[j + x * 8 + ((7 - i) + y * 8) * 128] = typeD;
                        }
                    }
                }
            }
        }
    }
}
/* 110 insns */
static void StageTrialClearDist(HuVecF pos, float dist)
{
    s32 x;
    s32 y;
    HuVecF d;
    float mag;

    if (stageTrialClearOff == 0) {
        stageTrialLavaFloorOnF = 1;
        for (y = 0; y < 16; y++) {
            for (x = 0; x < 16; x++) {
                d = (HuVecF){ pos.x - 3.0f * (100.0f * x), 0.0f, pos.z - 3.0f * (100.0f * y) };
                mag = VECMag(&d);
                if (dist < mag) {
                    continue;
                }
                stageTrialMap[x + y * 16] &= 0xF0;
            }
        }
    }
}
/* 133 insns */
static void StageTrialAddSlope(HuVecF pos, float radius)
{
    s32 x;
    s32 y;
    s32 h;
    HuVecF d;
    float mag;

    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            d = (HuVecF){ pos.x - 3.0f * (100.0f * x), 0.0f, pos.z - 3.0f * (100.0f * y) };
            mag = VECMag(&d);
            if (radius < mag) {
                continue;
            }
            h = (s32)((pos.y * MathLerp(1, (radius - mag) / radius)) / stageTrialHeight) + 2;
            if (h < (stageTrialMap[x + y * 16] & 0xF)) {
                continue;
            }
            stageTrialMap[x + y * 16] &= 0xF0;
            stageTrialMap[x + y * 16] |= h;
        }
    }
}
/* 205 insns */
static void StageTrialAddSlope2(HuVecF start, HuVecF end, float width)
{
    s32 x;
    s32 y;
    s32 h;
    Mtx mtx;
    HuVecF p;
    HuVecF dir;
    float len;
    float angle;
    float ax;
    float mag;

    VECSubtract(&end, &start, &dir);
    dir.y = 0.0f;
    len = VECMag(&dir);
    VECNormalize(&dir, &dir);
    angle = -(180.0 * (atan2(dir.x, dir.z) / M_PI));
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            p = (HuVecF){ 3.0f * (100.0f * x), 0.0f, 3.0f * (100.0f * y) };
            VECSubtract(&p, &start, &dir);
            dir.y = 0.0f;
            MTXRotRad(mtx, 'y', 0.017453292f * angle);
            MTXMultVec(mtx, &dir, &dir);
            if (dir.x < 0.0f) {
                ax = -dir.x;
            } else {
                ax = dir.x;
            }
            if (ax > width) {
                continue;
            }
            if (dir.z < 0.0f) {
                continue;
            }
            if (dir.z > len) {
                continue;
            }
            mag = VECMag(&dir);
            h = (s32)((start.y + (end.y - start.y) * (mag / len)) / stageTrialHeight) + 2;
            if (h < (stageTrialMap[x + y * 16] & 0xF)) {
                continue;
            }
            stageTrialMap[x + y * 16] &= 0xF0;
            stageTrialMap[x + y * 16] |= h;
        }
    }
}
/* 1015 insns */
static void MakeTrialStageMesh(void)
{
    s32 r[6];
    s32 g[6];
    s32 b[6];
    s32 ys[5];
    s32 xs[5];
    u16 *tex[5];
    s32 x;
    s32 y;
    s32 i;
    s32 j;
    s32 u;
    s32 v;
    s32 idx;
    s32 idx2;
    s32 type;
    s32 row;
    s32 sumR;
    s32 sumG;
    s32 sumB;
    u16 *src;
    u8 *colType;
    struct {
        s32 dstX;   /* texel origin of cell (x, y) in the 512x512 ground texture */
        s32 dstY;
        s32 srcX;   /* texel origin in the 128x128 tile texture (4x4 cells per tile) */
        s32 srcY;
        s32 colY;   /* origin in the 128x128 stageTrialMapColType grid */
        s32 colX;
        s32 unk18;  /* written, never read */
        s32 unk1C;
    } ofs;
    u16 *dst;
    u16 color;

#define TRIAL_TEXEL(p) (*(p))
    tex[0] = texturePtr;
    tex[1] = Hu3DData[trialModelId[0]].hsf->attribute->bitmap->data;
    tex[2] = Hu3DData[trialModelId[1]].hsf->attribute->bitmap->data;
    tex[3] = Hu3DData[trialModelId[2]].hsf->attribute->bitmap->data;
    tex[4] = Hu3DData[trialModelId[3]].hsf->attribute->bitmap->data;
    colType = stageTrialMapColType;
    for (y = 0; y < 16; y++) {
        for (x = 0; x < 16; x++) {
            dst = tex[0];
            ofs.dstX = x * 32;
            ofs.dstY = y * 32;
            ofs.srcX = (x % 4) * 32;
            ofs.srcY = (y % 4) * 32;
            ofs.colY = y * 8;
            ofs.colX = x * 8;
            ofs.unk18 = x * 32;
            ofs.unk1C = y * 32;
            if (!(stageTrialMap[x + y * 16] & 0x80)) {
                type = (stageTrialMap[x + y * 16] >> 4) & 7;
                if (type != 0) {
                    src = tex[type];
                    for (i = 0; i < 32; i++) {
                        for (j = 0; j < 32; j++) {
                            u = ofs.dstX + j % 512;
                            v = ofs.dstY + i % 512;
                            idx = u % 4 + ((v % 4) * 4 + (v / 4) * 2048 + (u / 4) * 16);
                            u = ofs.srcX + j % 128;
                            v = ofs.srcY + i % 128;
                            idx2 = u % 4 + ((v % 4) * 4 + (v / 4) * 512 + (u / 4) * 16);
                            memcpy(&dst[idx], &src[idx2], 2);
                        }
                    }
                }
            } else {
                for (i = 0; i < 32; i++) {
                    for (j = 0; j < 32; j++) {
                        u = ofs.dstX + j % 512;
                        v = ofs.dstY + i % 512;
                        idx = u % 4 + ((v % 4) * 4 + (v / 4) * 2048 + (u / 4) * 16);
                        u = ofs.srcX + j % 128;
                        v = ofs.srcY + i % 128;
                        idx2 = u % 4 + ((v % 4) * 4 + (v / 4) * 512 + (u / 4) * 16);
                        src = &tex[0][idx];
                        r[0] = (TRIAL_TEXEL(src) >> 8) & 0xF8;
                        g[0] = (TRIAL_TEXEL(src) >> 3) & 0xFC;
                        b[0] = (TRIAL_TEXEL(src) << 3) & 0xF8;
                        src = &tex[1][idx2];
                        r[1] = (TRIAL_TEXEL(src) >> 8) & 0xF8;
                        g[1] = (TRIAL_TEXEL(src) >> 3) & 0xFC;
                        b[1] = (TRIAL_TEXEL(src) << 3) & 0xF8;
                        src = &tex[2][idx2];
                        r[2] = (TRIAL_TEXEL(src) >> 8) & 0xF8;
                        g[2] = (TRIAL_TEXEL(src) >> 3) & 0xFC;
                        b[2] = (TRIAL_TEXEL(src) << 3) & 0xF8;
                        src = &tex[3][idx2];
                        r[3] = (TRIAL_TEXEL(src) >> 8) & 0xF8;
                        g[3] = (TRIAL_TEXEL(src) >> 3) & 0xFC;
                        b[3] = (TRIAL_TEXEL(src) << 3) & 0xF8;
                        src = &tex[4][idx2];
                        r[4] = (TRIAL_TEXEL(src) >> 8) & 0xF8;
                        g[4] = (TRIAL_TEXEL(src) >> 3) & 0xFC;
                        b[4] = (TRIAL_TEXEL(src) << 3) & 0xF8;
                        sumR = sumG = sumB = 0;
                        ys[0] = ofs.colY + (i - 2) / 4;
                        xs[0] = ofs.colX + (j - 2) / 4;
                        ys[0] = (ys[0] > 127) ? 127 : ((ys[0] < 0) ? 0 : ys[0]);
                        xs[0] = (xs[0] > 127) ? 127 : ((xs[0] < 0) ? 0 : xs[0]);
                        ys[1] = ofs.colY + (i - 1) / 4;
                        xs[1] = ofs.colX + (j - 1) / 4;
                        ys[1] = (ys[1] > 127) ? 127 : ((ys[1] < 0) ? 0 : ys[1]);
                        xs[1] = (xs[1] > 127) ? 127 : ((xs[1] < 0) ? 0 : xs[1]);
                        ys[2] = ofs.colY + i / 4;
                        xs[2] = ofs.colX + j / 4;
                        ys[2] = (ys[2] > 127) ? 127 : ((ys[2] < 0) ? 0 : ys[2]);
                        xs[2] = (xs[2] > 127) ? 127 : ((xs[2] < 0) ? 0 : xs[2]);
                        ys[3] = ofs.colY + (i + 1) / 4;
                        xs[3] = ofs.colX + (j + 1) / 4;
                        ys[3] = (ys[3] > 127) ? 127 : ((ys[3] < 0) ? 0 : ys[3]);
                        xs[3] = (xs[3] > 127) ? 127 : ((xs[3] < 0) ? 0 : xs[3]);
                        ys[4] = ofs.colY + (i + 2) / 4;
                        xs[4] = ofs.colX + (j + 2) / 4;
                        ys[4] = (ys[4] > 127) ? 127 : ((ys[4] < 0) ? 0 : ys[4]);
                        xs[4] = (xs[4] > 127) ? 127 : ((xs[4] < 0) ? 0 : xs[4]);
                        row = ys[0] * 128;
                        type = colType[row + xs[0]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[1]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[2]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[3]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[4]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        row = ys[1] * 128;
                        type = colType[row + xs[0]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[1]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[2]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[3]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[4]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        row = ys[2] * 128;
                        type = colType[row + xs[0]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[1]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[2]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[3]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[4]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        row = ys[3] * 128;
                        type = colType[row + xs[0]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[1]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[2]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[3]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[4]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        row = ys[4] * 128;
                        type = colType[row + xs[0]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[1]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[2]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[3]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        type = colType[row + xs[4]];
                        sumR += r[type];
                        sumG += g[type];
                        sumB += b[type];
                        sumR /= 25;
                        sumG /= 25;
                        sumB /= 25;
                        color = (u16)((sumR & 0xF8) << 8) | ((sumG & 0xFC) << 3) | ((sumB & 0xF8) >> 3);
                        memcpy(&dst[idx], &color, 2);
                    }
                }
            }
        }
    }
    DCStoreRangeNoSync(tex[0], 0x80000);
#undef TRIAL_TEXEL
}
/* 23 insns */
static void Stage07SmokeMain(void)
{
    if (sys->unkFEC % 5 == 0) {
        Stage07SmokeCreate();
    }
    Stage07SmokeUpdate();
}
/* 0x18AC */ HuVecF lbl_1_data_18AC[20] = { { -250.0f, -0.0f, 3750.0f }, { -230.0f, -0.0f, 3710.0f }, { -210.0f, -0.0f, 3680.0f }, { -195.0f, -0.0f, 3655.0f }, { -180.0f, -0.0f, 3630.0f }, { -150.0f, -0.0f, 3590.0f }, { -120.0f, -0.0f, 3550.0f }, { -80.0f, -0.0f, 3550.0f }, { -45.0f, -0.0f, 3550.0f }, { -20.0f, -0.0f, 3550.0f }, { 250.0f, -0.0f, 3750.0f }, { 230.0f, -0.0f, 3710.0f }, { 210.0f, -0.0f, 3680.0f }, { 195.0f, -0.0f, 3655.0f }, { 180.0f, -0.0f, 3630.0f }, { 150.0f, -0.0f, 3590.0f }, { 120.0f, -0.0f, 3550.0f }, { 80.0f, -0.0f, 3550.0f }, { 45.0f, -0.0f, 3550.0f }, { 20.0f, -0.0f, 3550.0f } };

/* 602 insns */
static void Stage07SmokeCreate(void)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[0]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[sys->unkFE8];
    Mtx mtx;
    HU3DPARTICLEDATA *dataP;
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 20; i++) {
        stage07Smoke[i].unk0 = 6.0f + rand8() % 8;
        stage07Smoke[i].unk4 = lbl_1_data_18AC[i].x + rand8() % 20 - 10.0f;
        stage07Smoke[i].unk8 = lbl_1_data_18AC[i].y + rand8() % 20 - 10.0f;
        stage07Smoke[i].unkC = lbl_1_data_18AC[i].z + rand8() % 20 - 10.0f;
        stage07Smoke[i].unk10 = 50.0f + rand8() % 120;
        stage07Smoke[i].unk14 = rand8() % 128 + 128;
    }
    for (i = 0; i < 8; i++) {
        MTXRotRad(mtx, 'y', 0.017453292f * (45.0f * i));
        for (j = 0, k = 0; k < 60; k++) {
            dataP = &data[k + i * 60];
            if (dataP->time == 0) {
                dataP->time = 1;
                dataP->parManId = 0;
                dataP->vel = (HuVecF){ 0.0f, stage07Smoke[j].unk0, 0.0f };
                dataP->pos = (HuVecF){ stage07Smoke[j].unk4, stage07Smoke[j].unk8, stage07Smoke[j].unkC };
                dataP->scale = stage07Smoke[j].unk10;
                dataP->color = (GXColor){ stage07Smoke[j].unk14, stage07Smoke[j].unk14, stage07Smoke[j].unk14, 0x80 };
                MTXMultVec(mtx, &dataP->pos, &dataP->pos);
                if (++j >= 20) {
                    break;
                }
            }
        }
    }
    for (i = 0; i < 20; i++) {
        stage07Smoke[i].unk0 = 2.0f + rand8() % 2;
        stage07Smoke[i].unk10 = 30.0f + rand8() % 40;
    }
    for (j = 0, i = 0; i < 30; i++) {
        dataP = &data[i + 480];
        if (dataP->time == 0) {
            dataP->time = 1;
            dataP->parManId = 0;
            dataP->vel = (HuVecF){ 0.0f, stage07Smoke[j].unk0, 0.0f };
            dataP->pos = SdRandomPosGet(0, (HuVecF){ 0.0f, -10.0f, 0.0f }, NULL, 300.0f, 0.0f);
            dataP->scale = stage07Smoke[j].unk10;
            dataP->color = (GXColor){ stage07Smoke[j].unk14, stage07Smoke[j].unk14, stage07Smoke[j].unk14, 0xFF };
            if (++j >= 10) {
                break;
            }
        }
    }
}
/* 173 insns */
static void Stage07SmokeUpdate(void)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[0]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[sys->unkFE8];
    s32 i;

    for (i = 0; i < 510; i++) {
        if (data[i].time != 0) {
            if (data[i].scale > 0.0f) {
                data[i].pos.y += data[i].vel.y;
                data[i].vel.y *= 1.01f;
                data[i].scale *= 0.95f;
                data[i].color.r *= 0.995f;
                data[i].color.g *= 0.98f;
                data[i].color.b *= 0.9f;
                data[i].color.a *= 0.95f;
                if (data[i].color.a < 2) {
                    data[i].scale = 0.0f;
                }
            }
            if (++data[i].parManId >= 15) {
                data[i].time = data[i].parManId = 0;
                data[i].scale = 0.0f;
            }
        }
    }
}
/* 39 insns */
void SdParticleCameraSet(s32 cameraNo)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[0]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[sys->unkFE8];
    s32 i;

    for (i = 0; i < 510; i++) {
        data[i].cameraBit = sdCameraBitTbl[cameraNo];
    }
}
/* 0x199C */ static s32 auxATbl[8] = { 0x0, 0x0, 0x0, 0x0, 0x3, 0x3, 0x0, 0x4 };

/* 18 insns */
void SdAuxSet(void)
{
    HuAudAUXSet(auxATbl[sys->stageNo], 1);
}

