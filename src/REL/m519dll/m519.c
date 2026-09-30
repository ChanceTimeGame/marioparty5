/*
 * m519dll m519.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m519dll/asm/REL/m519dll/m519.s.
 */

#include "REL/m519dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/object.h"
#include "game/process.h"
#include "game/wipe.h"
#include "game/flag.h"

#include "math.h"

/* DOL data: retail reads it signed (ObjectSetup mulhw); not in dol.def yet (OUT.txt) */
extern s32 GlobalCounter;

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s16 lbl_1_rodata_10[4] = { 0x0001, 0x0002, 0x0004, 0x0008 }; */
/* 0x18 */ /* s32 lbl_1_rodata_18[1] = { 0x00200060 }; */
/* 0x1C */ /* s32 lbl_1_rodata_1C[1] = { 0x00300050 }; */
/* 0x20 */ /* s32 lbl_1_rodata_20[33] = { 0x00000000, 0x00000000, 0x00000000, 0x44E10000, 0x43340000, 0x43340000, 0x44E10000, 0x42340000, 0x42340000, 0x44E10000, 0x439D8000, 0x439D8000, 0x00000000, 0x44960000, 0x40A00000, 0x00000000, 0x00000000, 0xC0A00000, 0xFFFFFFFF, 0x00000000, 0x44960000, 0x40A00000, 0x00000000, 0x00000000, 0xC0A00000, 0xFFFFFFFF, 0x00000000, 0x44960000, 0x40A00000, 0x00000000, 0x00000000, 0xC0A00000, 0xFFFFFFFF }; */
/* 0xA4 */ /* s32 lbl_1_rodata_A4[48] = { 0x00000000, 0x44BB8000, 0x44BB8000, 0x00000000, 0x00000000, 0xC4BB8000, 0xFFFFFFFF, 0x00000000, 0x44BB8000, 0x44BB8000, 0x00000000, 0x00000000, 0xC4BB8000, 0xFFFFFFFF, 0x00000000, 0x44BB8000, 0x44BB8000, 0x00000000, 0x00000000, 0xC4BB8000, 0xFFFFFFFF, 0x00000000, 0x459C4000, 0x42C80000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x459C4000, 0x42C80000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x459C4000, 0x42C80000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x164 */ /* s32 lbl_1_rodata_164[13] = { 0x000001F9, 0x000001E5, 0x0000025D, 0x000002AD, 0x00000285, 0x000001BD, 0x00000299, 0x000001D1, 0x00000271, 0x00000235, 0x00000249, 0x00000221, 0x0000020D }; */
/* 0x198 */ /* s32 lbl_1_rodata_198[56] = { 0x42480000, 0x41200000, 0x46BB8000, 0x3F99999A, 0x00000000, 0x00000000, 0x44200000, 0x43F00000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x44200000, 0x43F00000, 0x42480000, 0x41200000, 0x46BB8000, 0x3FE19A80, 0x44150000, 0x00000000, 0x43B60000, 0x4355547B, 0x00000000, 0x3F800000, 0x44200000, 0x00000000, 0x43A00000, 0x432D547B, 0x42480000, 0x41200000, 0x46BB8000, 0x400AD55C, 0x44150000, 0x4319547B, 0x43B60000, 0x4319547B, 0x00000000, 0x3F800000, 0x44200000, 0x432D547B, 0x43A00000, 0x4305547B, 0x42480000, 0x41200000, 0x46BB8000, 0x3FE19A80, 0x44150000, 0x438F547B, 0x438A0000, 0x4341547B, 0x00000000, 0x3F800000, 0x44200000, 0x4399547B, 0x43A00000, 0x432D547B }; */
/* 0x278 */ /* s32 lbl_1_rodata_278[3] = { 0x004D0047, 0x004D0048, 0x004D0048 }; */
/* 0x284 */ /* s32 lbl_1_rodata_284[12] = { 0x00000000, 0x43000000, 0x44020000, 0x00010000, 0x44200000, 0x42AE0000, 0x00020000, 0x44200000, 0x43708000, 0x00030000, 0x44200000, 0x43C50000 }; */
/* 0x2B4 */ /* float lbl_1_rodata_2B4 = 0.0f; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 3.141592653589793; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 180; */
/* 0x2C8 */ /* float lbl_1_rodata_2C8 = -10.0f; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = 1000.0f; */
/* 0x2D0 */ /* s32 lbl_1_rodata_2D0[112] = { 0x42480000, 0x42C80000, 0x46BB8000, 0x3F99999A, 0x00000000, 0x00000000, 0x44200000, 0x43F00000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x44200000, 0x43F00000, 0x42480000, 0x42C80000, 0x46BB8000, 0x3FE19A80, 0x44150000, 0x00000000, 0x43B60000, 0x4355547B, 0x00000000, 0x3F800000, 0x44200000, 0x00000000, 0x43A00000, 0x432D547B, 0x42480000, 0x42C80000, 0x46BB8000, 0x400AD55C, 0x44150000, 0x4319547B, 0x43B60000, 0x4319547B, 0x00000000, 0x3F800000, 0x44200000, 0x432D547B, 0x43A00000, 0x4305547B, 0x42480000, 0x42C80000, 0x46BB8000, 0x3FE19A80, 0x44150000, 0x438F547B, 0x438A0000, 0x4341547B, 0x00000000, 0x3F800000, 0x44200000, 0x4399547B, 0x43A00000, 0x432D547B, 0x42480000, 0x42C80000, 0x46BB8000, 0x3F19999A, 0x00000000, 0x00000000, 0x43A00000, 0x43F00000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x43A00000, 0x43F00000, 0x42480000, 0x42C80000, 0x46BB8000, 0x3FE19A80, 0x438A0000, 0x00000000, 0x43B60000, 0x4355547B, 0x00000000, 0x3F800000, 0x43A00000, 0x00000000, 0x43A00000, 0x432D547B, 0x42480000, 0x42C80000, 0x46BB8000, 0x3FE19A80, 0x438A0000, 0x4319547B, 0x43B60000, 0x4341547B, 0x00000000, 0x3F800000, 0x43A00000, 0x432D547B, 0x43A00000, 0x4305547B, 0x42480000, 0x42C80000, 0x46BB8000, 0x3FE19A80, 0x438A0000, 0x438F547B, 0x43B60000, 0x4341547B, 0x00000000, 0x3F800000, 0x43A00000, 0x4399547B, 0x43A00000, 0x432D547B }; */
/* 0x490 */ /* float lbl_1_rodata_490 = 90.0f; */
/* 0x494 */ /* float lbl_1_rodata_494 = 0.016666668f; */
/* 0x498 */ /* float lbl_1_rodata_498 = 0.9f; */
/* 0x49C */ /* float lbl_1_rodata_49C = 239.0f; */
/* 0x4A0 */ /* float lbl_1_rodata_4A0 = 16.0f; */
/* 0x4A4 */ /* float lbl_1_rodata_4A4 = 160.0f; */
/* 0x4A8 */ /* float lbl_1_rodata_4A8 = 1.0f; */
/* 0x4B0 */ /* double lbl_1_rodata_4B0 = 4503601774854144; */
/* 0x4B8 */ /* s32 lbl_1_rodata_4B8[4] = { 0xC3A00000, 0xC2700000, 0x43020000, 0x43A00000 }; */
/* 0x4C8 */ /* s32 lbl_1_rodata_4C8[2] = { 0x00280038, 0x00480058 }; */
/* 0x4D0 */ /* float lbl_1_rodata_4D0 = -5000.0f; */
/* 0x4D4 */ /* float lbl_1_rodata_4D4 = 50.0f; */
/* 0x4D8 */ /* float lbl_1_rodata_4D8 = 10.0f; */
/* 0x4DC */ /* float lbl_1_rodata_4DC = 24000.0f; */
/* 0x4E0 */ /* float lbl_1_rodata_4E0 = 1.2f; */
/* 0x4E4 */ /* float lbl_1_rodata_4E4 = 640.0f; */
/* 0x4E8 */ /* float lbl_1_rodata_4E8 = 480.0f; */
/* 0x4F0 */ /* double lbl_1_rodata_4F0 = 0; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = 150.0f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = 600.0f; */
/* 0x500 */ /* float lbl_1_rodata_500 = -15.0f; */
/* 0x504 */ /* float lbl_1_rodata_504 = 1500.0f; */
/* 0x508 */ /* s32 lbl_1_rodata_508[21] = { 0x004D0000, 0x004D0003, 0x004D0001, 0x004D0002, 0x004D0004, 0x004D0005, 0x004D0006, 0x004D0000, 0x004D000D, 0x004D0001, 0x004D0002, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x004D0000, 0x004D0017, 0x004D0001, 0x004D0002, 0x004D0018, 0x004D0019, 0xFFFFFFFF }; */
/* 0x55C */ /* s32 lbl_1_rodata_55C[3] = { 0x00000000, 0x00000000, 0x646E7800 }; */
/* 0x568 */ /* s32 lbl_1_rodata_568[252] = { 0x00000000, 0x44480000, 0x00000000, 0xC4480000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x44480000, 0x00000000, 0x44480000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4480000, 0x00000000, 0xC4480000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4480000, 0x00000000, 0x44480000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC4BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x44BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC4160000, 0x00000000, 0xC4BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC4160000, 0x00000000, 0x44BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x44160000, 0x00000000, 0xC4BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x44160000, 0x00000000, 0x44BB8000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x447A0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x44160000, 0x00000000, 0xC47A0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4160000, 0x00000000, 0xC47A0000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC4160000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0xC4548000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC4898000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x44160000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x44548000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x44898000, 0x00000000, 0x43FA0000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x00000000, 0x00000000, 0xC47A0000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC3E10000, 0x00000000, 0xC3E10000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0xC3E10000, 0x00000000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x43E10000, 0x00000000, 0xC3E10000, 0x00000000, 0x00000000, 0x00000000, 0x00010000, 0x43E10000, 0x00000000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4A8C000, 0x00000000, 0xC3E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC4A8C000, 0x00000000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x44A8C000, 0x00000000, 0xC3E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x44A8C000, 0x00000000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3E10000, 0x00000000, 0xC4A8C000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC3E10000, 0x00000000, 0x44A8C000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x43E10000, 0x00000000, 0xC4A8C000, 0x00000000, 0x00000000, 0x00000000, 0x00020000, 0x43E10000, 0x00000000, 0x44A8C000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x958 */ /* s32 lbl_1_rodata_958[18] = { 0x004D0021, 0x004D0034, 0x004D0037, 0x004D0032, 0x004D0033, 0x004D003F, 0x004D0022, 0x004D0023, 0x004D0040, 0x004D002B, 0x004D003A, 0x004D0041, 0x004D0031, 0x004D0042, 0x004D0043, 0x004D0044, 0xFFFFFFFF, 0xFFFFFFFF }; */
/* 0x9A0 */ /* s32 lbl_1_rodata_9A0[14] = { 0x004D0024, 0x004D0025, 0x004D0026, 0x004D0028, 0x004D0027, 0x004D0029, 0x004D002A, 0x004D002C, 0x004D002D, 0x004D002E, 0x004D002D, 0x004D002E, 0x004D002F, 0x004D002F }; */
/* 0x9D8 */ /* s32 lbl_1_rodata_9D8[8] = { 0x3E36DB6E, 0x3CF3CF3D, 0x430C0000, 0x00500000, 0x3F186186, 0x3D73CF3D, 0x42A00000, 0x00280000 }; */
/* 0x9F8 */ /* s32 lbl_1_rodata_9F8[42] = { 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41800000, 0x40000001, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x41800000, 0x00000000, 0x00000000, 0x41800000, 0x00000000 }; */
/* 0xAA0 */ /* float lbl_1_rodata_AA0 = 8.0f; */
/* 0xAA4 */ /* float lbl_1_rodata_AA4 = 180.0f; */
/* 0xAA8 */ /* float lbl_1_rodata_AA8 = 0.017453292f; */
/* 0xAB0 */ /* double lbl_1_rodata_AB0 = 360; */
/* 0xAB8 */ /* float lbl_1_rodata_AB8 = -45.0f; */
/* 0xABC */ /* float lbl_1_rodata_ABC = 0.5f; */
/* 0xAC0 */ /* float lbl_1_rodata_AC0 = 0.2f; */
/* 0xAC8 */ /* double lbl_1_rodata_AC8 = 0.5; */
/* 0xAD0 */ /* double lbl_1_rodata_AD0 = 3; */
/* 0xAD8 */ /* float lbl_1_rodata_AD8 = 80.0f; */
/* 0xADC */ /* float lbl_1_rodata_ADC = 39.0f; */
/* 0xAE0 */ /* s32 lbl_1_rodata_AE0[4] = { 0x000000B4, 0x000000AA, 0x00000096, 0x000000A0 }; */
/* 0xAF0 */ /* s32 lbl_1_rodata_AF0[4] = { 0x41700000, 0x41800000, 0x41880000, 0x41900000 }; */
/* 0xB00 */ /* s32 lbl_1_rodata_B00[2] = { 0x001E0019, 0x00140014 }; */
/* 0xB08 */ /* s32 lbl_1_rodata_B08[4] = { 0x00000280, 0x00000294, 0x000002A8, 0x000002BC }; */
/* 0xB18 */ /* s32 lbl_1_rodata_B18[4] = { 0x00000514, 0x000004B0, 0x0000044C, 0x000003E8 }; */
/* 0xB28 */ /* s32 lbl_1_rodata_B28[2] = { 0x00230019, 0x0014000F }; */
/* 0xB30 */ /* s32 lbl_1_rodata_B30[4] = { 0x00000258, 0x00000262, 0x0000026C, 0x00000276 }; */
/* 0xB40 */ /* s32 lbl_1_rodata_B40[2] = { 0x00060004, 0x00020000 }; */
/* 0xB48 */ /* s32 lbl_1_rodata_B48[4] = { 0x420C0000, 0x42080000, 0x42040000, 0x42000000 }; */
/* 0xB58 */ /* float lbl_1_rodata_B58 = 2390.0f; */
/* 0xB5C */ /* float lbl_1_rodata_B5C = 300.0f; */
/* 0xB60 */ /* float lbl_1_rodata_B60 = 4780.0f; */
/* 0xB64 */ /* float lbl_1_rodata_B64 = 360.0f; */
/* 0xB68 */ /* float lbl_1_rodata_B68 = 2000.0f; */
/* 0xB6C */ /* float lbl_1_rodata_B6C = 500.0f; */
/* 0xB70 */ /* double lbl_1_rodata_B70 = 0.015; */
/* 0xB78 */ /* float lbl_1_rodata_B78 = 60.0f; */
/* 0xB7C */ /* float lbl_1_rodata_B7C = -60.0f; */
/* 0xB80 */ /* float lbl_1_rodata_B80 = 68.0f; */
/* 0xB84 */ /* float lbl_1_rodata_B84 = 0.18f; */
/* 0xB88 */ /* float lbl_1_rodata_B88 = 0.36f; */
/* 0xB8C */ /* float lbl_1_rodata_B8C = 40.0f; */
/* 0xB90 */ /* float lbl_1_rodata_B90 = 100.0f; */
/* 0xB94 */ /* float lbl_1_rodata_B94[3] = { 72.0f, 0.000000000000000000000000000000000000000459183f, 0.000000000000000000000000000000000000000183671f }; */
/* 0xBA0 */ /* s32 lbl_1_rodata_BA0[4] = { 0x000007D0, 0x00000834, 0x00000898, 0x000008FC }; */
/* 0xBB0 */ /* s32 lbl_1_rodata_BB0[4] = { 0x00000028, 0x0000001E, 0x00000014, 0x0000000A }; */
/* 0xBC0 */ /* s32 lbl_1_rodata_BC0[4] = { 0x000000B4, 0x000000AA, 0x00000096, 0x000000A0 }; */
/* 0xBD0 */ /* s32 lbl_1_rodata_BD0[4] = { 0x00000226, 0x0000021C, 0x00000212, 0x00000208 }; */
/* 0xBE0 */ /* s32 lbl_1_rodata_BE0[4] = { 0x0000000A, 0x0000000F, 0x00000014, 0x00000019 }; */
/* 0xBF0 */ /* s32 lbl_1_rodata_BF0[2] = { 0x00040003, 0x00020000 }; */
/* 0xBF8 */ /* float lbl_1_rodata_BF8 = 2.0f; */
/* 0xBFC */ /* float lbl_1_rodata_BFC = 250.0f; */
/* 0xC00 */ /* float lbl_1_rodata_C00 = 20.0f; */
/* 0xC04 */ /* float lbl_1_rodata_C04 = 120.0f; */
/* 0xC08 */ /* float lbl_1_rodata_C08 = 2300.0f; */
/* 0xC0C */ /* float lbl_1_rodata_C0C = 30.0f; */
/* 0xC10 */ /* float lbl_1_rodata_C10 = 0.33333334f; */
/* 0xC14 */ /* float lbl_1_rodata_C14 = 240.0f; */
/* 0xC18 */ /* float lbl_1_rodata_C18 = 0.25f; */
/* 0xC20 */ /* double lbl_1_rodata_C20 = 740; */
/* 0xC28 */ /* float lbl_1_rodata_C28 = 1600.0f; */
/* 0xC2C */ /* float lbl_1_rodata_C2C = -26.0f; */
/* 0xC30 */ /* double lbl_1_rodata_C30 = 500; */
/* 0xC38 */ /* float lbl_1_rodata_C38 = 1200.0f; */
/* 0xC3C */ /* float lbl_1_rodata_C3C = -22.5f; */
/* 0xC40 */ /* float lbl_1_rodata_C40 = 170.0f; */
/* 0xC44 */ /* float lbl_1_rodata_C44 = 0.0009f; */
/* 0xC48 */ /* s32 lbl_1_rodata_C48[2] = { 0x00000711, 0x00000713 }; */
/* 0xC50 */ /* float lbl_1_rodata_C50 = 0.01f; */
/* 0xC58 */ /* double lbl_1_rodata_C58 = 0.011111111111111112; */
/* 0xC60 */ /* s32 lbl_1_rodata_C60[78] = { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C0001, 0x008C0006, 0x008C0007, 0x00330000, 0x00330003, 0x00330004, 0x00330001, 0x00330006, 0x00330007, 0x00B70000, 0x00B70003, 0x00B70004, 0x00B70001, 0x00B70006, 0x00B70007, 0x00ED0000, 0x00ED0003, 0x00ED0004, 0x00ED0001, 0x00ED0006, 0x00ED0007, 0x00E60000, 0x00E60003, 0x00E60004, 0x00E60001, 0x00E60006, 0x00E60007, 0x00170000, 0x00170003, 0x00170004, 0x00170001, 0x00170006, 0x00170007, 0x00E00000, 0x00E00003, 0x00E00004, 0x00E00001, 0x00E00006, 0x00E00007, 0x002D0000, 0x002D0003, 0x002D0004, 0x002D0001, 0x002D0006, 0x002D0007, 0x00C90000, 0x00C90003, 0x00C90004, 0x00C90001, 0x00C90006, 0x00C90007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007 }; */
/* 0xD98 */ /* s32 lbl_1_rodata_D98[15] = { 0x004D005D, 0x004D005E, 0x004D005F, 0x004D0060, 0x004D0061, 0x004D0062, 0x004D0063, 0x004D0064, 0x004D0065, 0x004D0066, 0x004D0067, 0x004D0068, 0x004D0069, 0x43340000, 0x42C80000 }; */
/* 0xDD4 */ /* s32 lbl_1_rodata_DD4[10] = { 0x004D0035, 0x004D0036, 0x004D0038, 0x004D0039, 0x004D003D, 0x004D0039, 0x004D003E, 0x004D0039, 0x004D003B, 0x004D003C }; */
/* 0xDFC */ /* s32 lbl_1_rodata_DFC[30] = { 0x4292AAAB, 0x41400000, 0x41400000, 0x00280001, 0x0003001E, 0x00000001, 0x42995555, 0x42A00000, 0x42A00000, 0x00780001, 0x000F00C8, 0x00000000, 0x00000000, 0x43FA0000, 0x43480000, 0x000F000F, 0x000100C8, 0x00000000, 0x00000000, 0x447A0000, 0x43480000, 0x001E001E, 0x000300C8, 0x00000000, 0x4292AAAB, 0x41400000, 0x41400000, 0x00190001, 0x0001000A, 0x00000001 }; */
/* 0xE74 */ /* s32 lbl_1_rodata_E74[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xE80 */ /* s32 lbl_1_rodata_E80[5] = { 0x0000070C, 0x0000070E, 0x0000070F, 0x0000070F, 0x00000712 }; */
/* 0xE94 */ /* float lbl_1_rodata_E94 = 0.1f; */
/* 0xE98 */ /* s32 lbl_1_rodata_E98[2] = { 0x00000714, 0x00000715 }; */
/* 0xEA0 */ /* s32 lbl_1_rodata_EA0[10] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000000, 0x00000001 }; */
/* 0xEC8 */ /* s32 lbl_1_rodata_EC8[2] = { 0x0000071B, 0x0000071C }; */
/* 0xED0 */ /* s32 lbl_1_rodata_ED0[18] = { 0x004D0007, 0x004D0008, 0x004D0009, 0x004D000A, 0x004D000B, 0x004D000C, 0x004D0011, 0x004D0012, 0x004D0013, 0x004D0014, 0x004D0015, 0x004D0016, 0x004D001B, 0x004D001C, 0x004D001D, 0x004D001E, 0x004D001F, 0x004D0020 }; */
/* 0xF18 */ /* s32 lbl_1_rodata_F18[1] = { 0x008C0064 }; */
/* 0xF1C */ /* s32 lbl_1_rodata_F1C[1] = { 0x000F000A }; */
/* 0xF20 */ /* s32 lbl_1_rodata_F20[2] = { 0x00000719, 0x0000071A }; */
/* 0xF28 */ /* s32 lbl_1_rodata_F28[2] = { 0x00000717, 0x00000718 }; */
/* 0xF30 */ /* s32 lbl_1_rodata_F30[2] = { 0x0000012C, 0x0000012C }; */
/* 0xF38 */ /* float lbl_1_rodata_F38 = -100.0f; */
/* 0xF3C */ /* float lbl_1_rodata_F3C = 4.0f; */
/* 0xF40 */ /* float lbl_1_rodata_F40 = 5.0f; */
/* 0xF44 */ /* s32 lbl_1_rodata_F44[72] = { 0x004D004C, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051, 0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D0059, 0x004D005A, 0x004D004D, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051, 0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C, 0x004D004E, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051, 0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C, 0x004D004F, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051, 0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C }; */
/* 0x1064 */ /* s32 lbl_1_rodata_1064[144] = { 0x00000000, 0x00000000, 0xC2A80000, 0xC1800000, 0xC2000000, 0x00000000, 0xC2A80000, 0xC1800000, 0xC2A80000, 0xC1800000, 0xC2A80000, 0xC1800000, 0xC2A80000, 0xC1800000, 0x42DE0000, 0xC0400000, 0x42DE0000, 0xC0400000, 0x42DE0000, 0xC0400000, 0x43010000, 0xC1B00000, 0x43010000, 0xC1B00000, 0x43010000, 0xC1B00000, 0x43148000, 0xC2260000, 0x43148000, 0xC2260000, 0x43148000, 0xC2260000, 0x41C00000, 0xC1E00000, 0x41C00000, 0xC1E00000, 0x00000000, 0x00000000, 0xC2B00000, 0xC2200000, 0xC1600000, 0x429C0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC1C00000, 0xC1700000, 0xC1C00000, 0xC1700000, 0xC1C00000, 0xC1700000, 0xC0800000, 0xC20C0000, 0xC0800000, 0xC20C0000, 0xC0800000, 0xC20C0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0xC1F80000, 0x41000000, 0xC1F80000, 0x00000000, 0x00000000, 0xC2B00000, 0xC2200000, 0xC1600000, 0x42740000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC1C00000, 0xC2040000, 0xC1C00000, 0xC2040000, 0xC1C00000, 0xC2040000, 0xC0800000, 0xC2500000, 0xC0800000, 0xC2500000, 0xC0800000, 0xC2500000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0xC2400000, 0x41000000, 0xC2400000, 0x00000000, 0x00000000, 0xC2B00000, 0xC2200000, 0xC1600000, 0x42280000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xC1C00000, 0xC2460000, 0xC1C00000, 0xC2460000, 0xC1C00000, 0xC2460000, 0xC0800000, 0xC28A0000, 0xC0800000, 0xC28A0000, 0xC0800000, 0xC28A0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41000000, 0xC2800000, 0x41000000, 0xC2800000 }; */
/* 0x12A4 */ /* float lbl_1_rodata_12A4 = 0.6f; */
/* 0x12A8 */ /* float lbl_1_rodata_12A8 = 0.35f; */
/* 0x12AC */ /* float lbl_1_rodata_12AC = 0.58f; */
/* 0x12B0 */ /* float lbl_1_rodata_12B0 = 0.68f; */
/* 0x12B8 */ /* double lbl_1_rodata_12B8 = 100; */
/* 0x12C0 */ /* float lbl_1_rodata_12C0 = 108.0f; */
/* 0x12C4 */ /* float lbl_1_rodata_12C4 = 0.8f; */
/* 0x12C8 */ /* float lbl_1_rodata_12C8 = 720.0f; */
/* 0x12D0 */ /* double lbl_1_rodata_12D0 = 96; */
/* 0x12D8 */ /* float lbl_1_rodata_12D8 = 96.0f; */
/* 0x12DC */ /* float lbl_1_rodata_12DC = -90.0f; */
/* 0x12E0 */ /* float lbl_1_rodata_12E0 = 0.015f; */
/* 0x12E4 */ /* float lbl_1_rodata_12E4 = 84.0f; */
/* 0x12E8 */ /* float lbl_1_rodata_12E8 = 56.0f; */
/* 0x12EC */ /* float lbl_1_rodata_12EC = 0.125f; */
/* 0x12F0 */ /* float lbl_1_rodata_12F0 = 0.008888889f; */
/* 0x12F4 */ /* float lbl_1_rodata_12F4 = 0.008333334f; */
/* 0x12F8 */ /* float lbl_1_rodata_12F8 = 104.0f; */
/* 0x12FC */ /* float lbl_1_rodata_12FC = -1.0f; */
/* 0x1300 */ /* float lbl_1_rodata_1300 = 127.0f; */
/* 0x1304 */ /* float lbl_1_rodata_1304 = 4800.0f; */
/* 0x1308 */ /* float lbl_1_rodata_1308 = 32.0f; */
/* 0x130C */ /* float lbl_1_rodata_130C = 0.53333336f; */

/* shared .rodata (fork A; extern in m519dll.h) */
const u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };
const s16 lbl_1_rodata_18[2] = { 0x20, 0x60 }; /* SE pan per player type (fork C) */
const M519_MOTSHIFT lbl_1_rodata_9F8[2][7] = {
    {
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 0.0f, 0x00000000 },
    },
    {
        { 0.0f, 16.0f, 0x40000001 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 16.0f, 0x00000000 },
        { 0.0f, 16.0f, 0x00000000 },
    },
};

/* --- .data --- */
/* 0x0 */ char lbl_1_data_0[] = "itemhook_c";
/* 0xB */ char lbl_1_data_B[] = "itemfook";
/* 0x14 */ void *lbl_1_data_14[2] = { &lbl_1_data_0, &lbl_1_data_B };
/* 0x1C */ M519_STAGEFUNC lbl_1_data_1C[1] = { fn_1_26A0 };
/* 0x20 */ M519_PLAYERFUNC lbl_1_data_20[2][5] = { { fn_1_35BC, fn_1_3664, fn_1_8188, fn_1_98AC, fn_1_9BA8 }, { fn_1_35BC, fn_1_5EDC, fn_1_8188, fn_1_98AC, fn_1_A068 } };
/* 0x48 */ M519_CHARFUNC lbl_1_data_48[5] = { fn_1_A598, fn_1_A634, fn_1_A6C4, fn_1_A77C, fn_1_A834 };
/* 0x5C */ M519_ITEMFUNC lbl_1_data_5C[2] = { fn_1_B004, fn_1_B0BC };
/* 0x64 */ M519_STAGEOBJFUNC lbl_1_data_64[4] = { fn_1_C3D4, fn_1_C570, fn_1_C798, fn_1_C470 };
/* 0x74 */ M519_EFFECTFUNC lbl_1_data_74[2] = { fn_1_CDF0, fn_1_CEE4 };
/* 0x7C */ M519_HUDFUNC lbl_1_data_7C[4][4] = { { fn_1_D720, fn_1_D7BC, fn_1_E174, fn_1_F2E8 }, { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 }, { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 }, { fn_1_D720, fn_1_DD08, fn_1_ED78, fn_1_F568 } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x17C */ OMOBJ *lbl_1_bss_17C; /* omAddObjEx(omOutViewMulti) (ObjectSetup); work[0] = camera count */
/* 0x178 */ M519_STAGE *lbl_1_bss_178; /* fn_1_2298 */
/* 0x108 */ OMCAMERAVIEW lbl_1_bss_108[4]; /* per player slot (omCameraViewSetMulti) */
/* 0xF8 */ M519_PLAYER *lbl_1_bss_F8[4]; /* fn_1_297C; [0] solo, [1..3] team */
/* 0xE8 */ M519_CHAR *lbl_1_bss_E8[4]; /* fn_1_A204, by player index */
/* 0x38 */ M519_ITEM *lbl_1_bss_38[44]; /* fn_1_AB40 (1 + 2 + 1 + 8 + 32) */
/* 0x32 */ s16 lbl_1_bss_32[3]; /* [0] Hu3DGLightCreate (fn_1_28C); 0x34..0x37 referenced by nothing */
/* 0x30 */ s16 lbl_1_bss_30; /* stage 0..2 (subGameNo or GlobalCounter % 3) */
/* 0x20 */ M519_HUD *lbl_1_bss_20[4]; /* fn_1_D0BC, per player slot */
/* 0x18 */ s16 lbl_1_bss_18[4]; /* espEntry x3 (fn_1_28C); [3] referenced by nothing */
/* 0x14 */ s32 lbl_1_bss_14; /* HuAudSStreamPlay */
/* 0x10 */ s32 lbl_1_bss_10; /* HuAudFXPlay(0x708) */
/* 0xE gap_05_0000000E_bss (0x2) -- dtk filler */
/* 0xC */ s16 lbl_1_bss_C; /* fn_1_A9F0 */
/* 0x8 */ s32 lbl_1_bss_8; /* 1 once the finish hook ran (fn_1_1628, read fn_1_B70C) */
/* 0x4 */ s32 lbl_1_bss_4; /* all three team players out (fn_1_14E8): solo wins */
/* 0x0 */ s32 lbl_1_bss_0; /* solo player out (fn_1_14E8): team wins */

/* --- functions (reference order) --- */
/* 95 insns */
void ObjectSetup(void)
{
    OMOBJMAN *objman;
    MGSEQ_PARAM param;

    objman = omInitObjMan(1, 0x2000);
    lbl_1_bss_17C = omAddObjEx(objman, 0x1000, 0, 0, 0, omOutViewMulti);
    lbl_1_bss_17C->work[0] = 4;
    omGameSysInit(objman);
    Hu3DNoSyncSet(1);
    param.maxTime = 60;
    param.timerPos = 0;
    param.initHook = fn_1_28C;
    param.fadeInHook = fn_1_9F4;
    param.startHook = fn_1_143C;
    param.mainHook = fn_1_14E8;
    param.finishHook = fn_1_1628;
    param.preWinnerHook = fn_1_19C4;
    param.winnerHook = fn_1_1FC0;
    param.fadeOutHook = NULL;
    param.closeHook = NULL;
    MgSeqCreate(&param);
    if (GWSubGameNoGet() == -1) {
        lbl_1_bss_30 = GlobalCounter % 3;
    }
    else {
        lbl_1_bss_30 = GWSubGameNoGet();
    }
}

/* 28 insns */
void fn_1_21C(void)
{
    while (!omSysExitReq) {
        HuPrcVSleep();
    }
    WipeCreate(2, 0, 60);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

/* 474 insns */
void fn_1_28C(s16 mode, s16 frameNo)
{
    static const struct {
        M519_LIGHT light[3];
        struct {
            HuVecF pos;
            HuVecF up;
            HuVecF target;
        } shadow[3]; /* referenced by nothing */
    } lbl_1_rodata_A4 = {
        {
            { { 0.0f, 1500.0f, 1500.0f }, { 0.0f, 0.0f, -1500.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
            { { 0.0f, 1500.0f, 1500.0f }, { 0.0f, 0.0f, -1500.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
            { { 0.0f, 1500.0f, 1500.0f }, { 0.0f, 0.0f, -1500.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
        },
        {
            { { 0.0f, 5000.0f, 100.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { { 0.0f, 5000.0f, 100.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { { 0.0f, 5000.0f, 100.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        },
    };
    static const M519_CAMPARAM lbl_1_rodata_198[4] = {
        { 50.0f, 10.0f, 24000.0f, 1.2f, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 0.0f, 0.0f, 640.0f, 480.0f },
        { 50.0f, 10.0f, 24000.0f, 1.7625275f, 596.0f, 0.0f, 364.0f, 213.33f, 0.0f, 1.0f, 640.0f, 0.0f, 320.0f, 173.33f },
        { 50.0f, 10.0f, 24000.0f, 2.1692724f, 596.0f, 153.33f, 364.0f, 153.33f, 0.0f, 1.0f, 640.0f, 173.33f, 320.0f, 133.33f },
        { 50.0f, 10.0f, 24000.0f, 1.7625275f, 596.0f, 286.66f, 276.0f, 193.33f, 0.0f, 1.0f, 640.0f, 306.66f, 320.0f, 173.33f },
    };
    static const s32 lbl_1_rodata_278[3] = { DATANUM(DATA_m519, 0x47), DATANUM(DATA_m519, 0x48), DATANUM(DATA_m519, 0x48) };
    static const struct {
        s16 type;
        HuVec2f pos;
    } lbl_1_rodata_284[4] = {
        { 0, { 128.0f, 520.0f } },
        { 1, { 640.0f, 87.0f } },
        { 2, { 640.0f, 240.5f } },
        { 3, { 640.0f, 394.0f } },
    };
    s16 grp[4];
    s32 i;
    s32 num;
    s32 n;
    s16 cam;

    switch (frameNo) {
        case 0:
            lbl_1_bss_178 = fn_1_2298();
            for (i = 0; i < 4; i++) {
                switch (i) {
                    case 0:
                        lbl_1_bss_F8[i] = fn_1_297C(0, i);
                        break;
                    case 1:
                    case 2:
                    case 3:
                        lbl_1_bss_F8[i] = fn_1_297C(1, i);
                        break;
                }
            }
            for (i = 0; i < 4; i++) {
                grp[i] = GwPlayerConf[i].grp;
            }
            num = 0;
            for (i = 0; i < 4; i++) {
                if (grp[i] == 0) {
                    num++;
                }
            }
            if (num == 1) {
                for (i = 0; i < 4; i++) {
                    if (grp[i] != 0) {
                        grp[i] = 1;
                    }
                }
            }
            else {
                grp[0] = 0;
                grp[1] = 1;
                grp[2] = 1;
                grp[3] = 1;
            }
            for (i = 0; i < 4; i++) {
                lbl_1_bss_E8[i] = fn_1_A204(grp[i], i);
            }
            for (i = 0; i < 4; i++) {
                if (grp[i] == 0) {
                    fn_1_3518(lbl_1_bss_F8[0], lbl_1_bss_E8[i]);
                    break;
                }
            }
            num = 1;
            for (i = 0; i < 4; i++) {
                if (grp[i] != 0) {
                    fn_1_3518(lbl_1_bss_F8[num++], lbl_1_bss_E8[i]);
                }
            }
            n = 0;
            for (i = 0; i < 1; i++, n++) {
                lbl_1_bss_38[n] = fn_1_AB40(3);
            }
            for (i = 0; i < 2; i++, n++) {
                lbl_1_bss_38[n] = fn_1_AB40(2);
            }
            for (i = 0; i < 1; i++, n++) {
                lbl_1_bss_38[n] = fn_1_AB40(1);
            }
            for (i = 0; i < 8; i++, n++) {
                lbl_1_bss_38[n] = fn_1_AB40(0);
            }
            for (i = 0; i < 32; i++, n++) {
                lbl_1_bss_38[n] = fn_1_AB40(4);
            }
            for (i = 0; i < 4; i++) {
                lbl_1_bss_20[i] = fn_1_D0BC(lbl_1_rodata_284[i].type, i);
                fn_1_D65C(lbl_1_bss_20[i], lbl_1_rodata_284[i].pos);
            }
            for (i = 0; i < 3; i++) {
                lbl_1_bss_18[i] = espEntry(lbl_1_rodata_278[i], 0, 0);
                espPriSet(lbl_1_bss_18[i], 500);
            }
            lbl_1_bss_32[0] = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
            Hu3DGLightPosAimSetV(lbl_1_bss_32[0], (HuVecF *)&lbl_1_rodata_A4.light[lbl_1_bss_30].pos, (HuVecF *)&lbl_1_rodata_A4.light[lbl_1_bss_30].aim);
            Hu3DGLightColorSet(lbl_1_bss_32[0], lbl_1_rodata_A4.light[lbl_1_bss_30].color.r, lbl_1_rodata_A4.light[lbl_1_bss_30].color.g,
                lbl_1_rodata_A4.light[lbl_1_bss_30].color.b, lbl_1_rodata_A4.light[lbl_1_bss_30].color.a);
            Hu3DGLightStaticSet(lbl_1_bss_32[0], FALSE);
            Hu3DCameraCreate(15);
            for (i = 0; i < 4; i++) {
                cam = lbl_1_rodata_10[i];
                Hu3DCameraPerspectiveSet(cam, lbl_1_rodata_198[i].fov, lbl_1_rodata_198[i].near, lbl_1_rodata_198[i].far, lbl_1_rodata_198[i].aspect);
                Hu3DCameraViewportSet(cam, lbl_1_rodata_198[i].vpX, lbl_1_rodata_198[i].vpY, lbl_1_rodata_198[i].vpW, lbl_1_rodata_198[i].vpH,
                    lbl_1_rodata_198[i].vpNear, lbl_1_rodata_198[i].vpFar);
                Hu3DCameraScissorSet(cam, lbl_1_rodata_198[i].scX, lbl_1_rodata_198[i].scY, lbl_1_rodata_198[i].scW, lbl_1_rodata_198[i].scH);
            }
            break;
    }
    MgSeqModeNext();
}

/* 220 insns */
void fn_1_9F4(s16 mode, s16 frameNo)
{
    static const struct {
        HuVecF cam[4]; /* radius, angle, rot.y */
        M519_LIGHT unused[3]; /* referenced by nothing */
    } lbl_1_rodata_20 = {
        {
            { 0.0f, 0.0f, 0.0f },
            { 1800.0f, 180.0f, 180.0f },
            { 1800.0f, 45.0f, 45.0f },
            { 1800.0f, 315.0f, 315.0f },
        },
        {
            { { 0.0f, 1200.0f, 5.0f }, { 0.0f, 0.0f, -5.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
            { { 0.0f, 1200.0f, 5.0f }, { 0.0f, 0.0f, -5.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
            { { 0.0f, 1200.0f, 5.0f }, { 0.0f, 0.0f, -5.0f }, { 0xFF, 0xFF, 0xFF, 0xFF } },
        },
    };
    HuVecF pos;
    HuVecF rot;
    float radius;
    float angle;
    float rotY;
    s32 i;

    switch (frameNo) {
        case 0:
            lbl_1_bss_10 = HuAudFXPlay(0x708);
            for (i = 0; i < 4; i++) {
                radius = lbl_1_rodata_20.cam[i].x;
                angle = lbl_1_rodata_20.cam[i].y;
                rotY = lbl_1_rodata_20.cam[i].z;
                pos.x = radius * sin(M_PI * angle / 180.0);
                pos.z = radius * cos(M_PI * angle / 180.0);
                pos.y = 0.0f;
                rot.x = 0.0f;
                rot.z = 0.0f;
                rot.y = rotY;
                fn_1_3138(lbl_1_bss_F8[i], pos);
                fn_1_3290(lbl_1_bss_F8[i], rot);
                fn_1_9B9C(lbl_1_bss_F8[i]);
            }
            for (i = 0; i < 4; i++) {
                lbl_1_bss_108[i].center.x = 0.0f;
                lbl_1_bss_108[i].center.y = 0.0f;
                lbl_1_bss_108[i].center.z = 0.0f;
                lbl_1_bss_108[i].rot.x = -10.0f;
                lbl_1_bss_108[i].rot.y = 0.0f;
                lbl_1_bss_108[i].rot.z = 0.0f;
                lbl_1_bss_108[i].zoom = 1000.0f;
                omCameraViewSetMulti(lbl_1_rodata_10[i], &lbl_1_bss_108[i]);
            }
            break;
        case 120:
            HuAudFXStop(lbl_1_bss_10);
            break;
        case 180:
            fn_1_2730(lbl_1_bss_178);
            fn_1_D64();
            fn_1_2790(lbl_1_bss_178);
            MgSeqModeNext();
            break;
    }
}

/* 438 insns */
void fn_1_D64(void)
{
    static const M519_CAMPARAM lbl_1_rodata_2D0[2][4] = {
        {
            { 50.0f, 100.0f, 24000.0f, 1.2f, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f, 0.0f, 0.0f, 640.0f, 480.0f },
            { 50.0f, 100.0f, 24000.0f, 1.7625275f, 596.0f, 0.0f, 364.0f, 213.33f, 0.0f, 1.0f, 640.0f, 0.0f, 320.0f, 173.33f },
            { 50.0f, 100.0f, 24000.0f, 2.1692724f, 596.0f, 153.33f, 364.0f, 153.33f, 0.0f, 1.0f, 640.0f, 173.33f, 320.0f, 133.33f },
            { 50.0f, 100.0f, 24000.0f, 1.7625275f, 596.0f, 286.66f, 276.0f, 193.33f, 0.0f, 1.0f, 640.0f, 306.66f, 320.0f, 173.33f },
        },
        {
            { 50.0f, 100.0f, 24000.0f, 0.6f, 0.0f, 0.0f, 320.0f, 480.0f, 0.0f, 1.0f, 0.0f, 0.0f, 320.0f, 480.0f },
            { 50.0f, 100.0f, 24000.0f, 1.7625275f, 276.0f, 0.0f, 364.0f, 213.33f, 0.0f, 1.0f, 320.0f, 0.0f, 320.0f, 173.33f },
            { 50.0f, 100.0f, 24000.0f, 1.7625275f, 276.0f, 153.33f, 364.0f, 193.33f, 0.0f, 1.0f, 320.0f, 173.33f, 320.0f, 133.33f },
            { 50.0f, 100.0f, 24000.0f, 1.7625275f, 276.0f, 286.66f, 364.0f, 193.33f, 0.0f, 1.0f, 320.0f, 306.66f, 320.0f, 173.33f },
        },
    };
    float t;
    float h;
    float x;
    float y;
    float w;
    float near;
    float far;
    float fov;
    float aspect;
    s32 time;
    s32 i;
    s16 cam;

    for (time = 1; time <= 60; time++) {
        for (i = 0; i < 4; i++) {
            cam = lbl_1_rodata_10[i];
            t = sin(M_PI * (90.0f * ((1.0f / 60.0f) * time)) / 180.0);
            fov = lbl_1_rodata_2D0[0][i].fov + t * (lbl_1_rodata_2D0[1][i].fov - lbl_1_rodata_2D0[0][i].fov);
            near = lbl_1_rodata_2D0[0][i].near + t * (lbl_1_rodata_2D0[1][i].near - lbl_1_rodata_2D0[0][i].near);
            far = lbl_1_rodata_2D0[0][i].far + t * (lbl_1_rodata_2D0[1][i].far - lbl_1_rodata_2D0[0][i].far);
            aspect = lbl_1_rodata_2D0[0][i].aspect + t * (lbl_1_rodata_2D0[1][i].aspect - lbl_1_rodata_2D0[0][i].aspect);
            Hu3DCameraPerspectiveSet(cam, fov, near, far, aspect);
            x = lbl_1_rodata_2D0[0][i].vpX + t * (lbl_1_rodata_2D0[1][i].vpX - lbl_1_rodata_2D0[0][i].vpX);
            y = lbl_1_rodata_2D0[0][i].vpY + t * (lbl_1_rodata_2D0[1][i].vpY - lbl_1_rodata_2D0[0][i].vpY);
            w = lbl_1_rodata_2D0[0][i].vpW + t * (lbl_1_rodata_2D0[1][i].vpW - lbl_1_rodata_2D0[0][i].vpW);
            h = lbl_1_rodata_2D0[0][i].vpH + t * (lbl_1_rodata_2D0[1][i].vpH - lbl_1_rodata_2D0[0][i].vpH);
            near = lbl_1_rodata_2D0[0][i].vpNear + t * (lbl_1_rodata_2D0[1][i].vpNear - lbl_1_rodata_2D0[0][i].vpNear);
            far = lbl_1_rodata_2D0[0][i].vpFar + t * (lbl_1_rodata_2D0[1][i].vpFar - lbl_1_rodata_2D0[0][i].vpFar);
            Hu3DCameraViewportSet(cam, x, y, w, h, near, far);
            x = lbl_1_rodata_2D0[0][i].scX + t * (lbl_1_rodata_2D0[1][i].scX - lbl_1_rodata_2D0[0][i].scX);
            y = lbl_1_rodata_2D0[0][i].scY + t * (lbl_1_rodata_2D0[1][i].scY - lbl_1_rodata_2D0[0][i].scY);
            w = lbl_1_rodata_2D0[0][i].scW + t * (lbl_1_rodata_2D0[1][i].scW - lbl_1_rodata_2D0[0][i].scW);
            h = lbl_1_rodata_2D0[0][i].scH + t * (lbl_1_rodata_2D0[1][i].scH - lbl_1_rodata_2D0[0][i].scH);
            Hu3DCameraScissorSet(cam, x, y, w, h);
            switch (i) {
                case 0:
                    espPosSet(lbl_1_bss_18[0], 0.9f * w, 239.0f);
                    break;
                case 1:
                    espPosSet(lbl_1_bss_18[1], 16.0f + 0.9f * (160.0f + x), (y + h) - 1.0f);
                    break;
                case 2:
                    espPosSet(lbl_1_bss_18[2], 16.0f + 0.9f * (160.0f + x), (y + h) - 1.0f);
                    break;
            }
        }
        HuPrcVSleep();
    }
}

/* 43 insns */
void fn_1_143C(s16 mode, s16 frameNo)
{
    s32 i;
    s32 j;

    switch (frameNo) {
        case 0:
            lbl_1_bss_14 = HuAudSStreamPlay(62);
            for (i = 0; i < 4; i++) {
                fn_1_D7B0(lbl_1_bss_20[i]);
                for (j = 0; j < 12; j++) {
                    HuPrcVSleep();
                }
            }
            break;
        case 120:
            MgSeqModeNext();
            break;
    }
}

/* 80 insns */
void fn_1_14E8(s16 mode, s16 frameNo)
{
    s32 i;

    switch (frameNo) {
        case 0:
            for (i = 0; i < 4; i++) {
                fn_1_3658(lbl_1_bss_F8[i]);
                lbl_1_bss_F8[i]->unk044 = 1;
            }
            break;
        default:
            if (fn_1_A1D4(lbl_1_bss_F8[0])) {
                lbl_1_bss_0 = 1;
            }
            if (fn_1_A1D4(lbl_1_bss_F8[1]) && fn_1_A1D4(lbl_1_bss_F8[2]) && fn_1_A1D4(lbl_1_bss_F8[3])) {
                lbl_1_bss_4 = 1;
            }
            if (lbl_1_bss_0 || lbl_1_bss_4) {
                MgSeqModeNext();
            }
            if ((u32)MgSeqTimerValueGet() == 0) {
                MgSeqModeNext();
            }
            break;
    }
}

/* 231 insns: the coin payout (inlined GWMgCoinBonusSet, practice-guarded) */
void fn_1_1628(s16 mode, s16 frameNo)
{
    M519_PLAYER *player;
    s32 i;

    switch (frameNo) {
        case 0:
            lbl_1_bss_8 = 1;
            HuAudSStreamFadeOut(lbl_1_bss_14, 1000);
            for (i = 0; i < 4; i++) {
                player = lbl_1_bss_F8[i];
                player->unk044 = 0;
                player->unk036 = 0;
                player->unk038 = 0;
                fn_1_8E40(player);
            }
            for (i = 0; i < 4; i++) {
                player = lbl_1_bss_F8[i];
                if (!fn_1_A1D4(player)) {
                    fn_1_F2DC(lbl_1_bss_20[player->unk006]);
                }
            }
            break;
        case 30:
            if ((!lbl_1_bss_0 && !lbl_1_bss_4) || (lbl_1_bss_0 && lbl_1_bss_4)) {
                MgSeqDrawSet();
            }
            else if (lbl_1_bss_0) {
                MgSeqWinnerSet(lbl_1_bss_E8[lbl_1_bss_F8[1]->unk008]->unk00A, lbl_1_bss_E8[lbl_1_bss_F8[2]->unk008]->unk00A,
                    lbl_1_bss_E8[lbl_1_bss_F8[3]->unk008]->unk00A, -1);
                GWMgCoinBonusSet(lbl_1_bss_E8[lbl_1_bss_F8[1]->unk008]->unk006, 10);
                GWMgCoinBonusSet(lbl_1_bss_E8[lbl_1_bss_F8[2]->unk008]->unk006, 10);
                GWMgCoinBonusSet(lbl_1_bss_E8[lbl_1_bss_F8[3]->unk008]->unk006, 10);
            }
            else if (lbl_1_bss_4) {
                MgSeqWinnerSet(lbl_1_bss_E8[lbl_1_bss_F8[0]->unk008]->unk00A, -1, -1, -1);
                GWMgCoinBonusSet(lbl_1_bss_E8[lbl_1_bss_F8[0]->unk008]->unk006, 10);
            }
            break;
    }
}

/* 383 insns */
void fn_1_19C4(s16 mode, s16 frameNo)
{
    static const float lbl_1_rodata_4B8[4] = { -320.0f, -60.0f, 130.0f, 320.0f };
    static const s16 lbl_1_rodata_4C8[4] = { 40, 56, 72, 88 };
    HuVecF pos;
    HuVecF rot;
    OMCAMERAVIEW *view;
    M519_PLAYER *player;
    s32 i;
    s16 cam;

    switch (frameNo) {
        case 60:
            WipeColorSet(255, 255, 255);
            WipeCreate(2, 0, 30);
            HuAudFadeOut(30);
            break;
        case 90:
            for (i = 0; i < 4; i++) {
                fn_1_F7F0(lbl_1_bss_20[i]);
            }
            fn_1_2900(lbl_1_bss_178);
            pos.x = 0.0f;
            pos.y = -5000.0f;
            pos.z = 0.0f;
            for (i = 0; i < 4; i++) {
                player = lbl_1_bss_F8[i];
                fn_1_A628(lbl_1_bss_E8[player->unk008]);
                fn_1_35B0(player);
                fn_1_3138(player, pos);
                player->unk04C = 0;
            }
            for (i = 0; i < 4; i++) {
                cam = lbl_1_rodata_10[i];
                player = lbl_1_bss_F8[i];
                switch (i) {
                    case 0:
                        Hu3DCameraPerspectiveSet(cam, 50.0f, 10.0f, 24000.0f, 1.2f);
                        Hu3DCameraViewportSet(cam, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
                        Hu3DCameraScissorSet(cam, 0, 0, 640, 480);
                        view = &lbl_1_bss_108[player->unk006];
                        view->center.x = 0.0 * sin(0.0);
                        view->center.z = 0.0 * cos(0.0);
                        view->center.y = 150.0f;
                        view->zoom = 600.0f;
                        view->rot.y = 0.0f;
                        view->rot.x = -15.0f;
                        view->rot.z = 0.0f;
                        omCameraViewMoveMulti(lbl_1_rodata_10[0], view, 1, 1);
                        break;
                    case 1:
                    case 2:
                    case 3:
                        break;
                }
            }
            Hu3DCameraKill(14);
            lbl_1_bss_17C->work[0] = 1;
            for (i = 0; i < 3; i++) {
                espDispOff(lbl_1_bss_18[i]);
            }
            for (i = 0; i < 4; i++) {
                player = lbl_1_bss_F8[i];
                pos.x = lbl_1_rodata_4B8[i];
                pos.y = 0.0f;
                pos.z = 0.0f;
                fn_1_A44C(lbl_1_bss_E8[player->unk008], pos);
                rot.x = 0.0f;
                rot.y = 0.0f;
                rot.z = 0.0f;
                fn_1_A4EC(lbl_1_bss_E8[player->unk008], rot);
                CharModelVoicePanSet(lbl_1_bss_E8[player->unk008]->unk00A, lbl_1_rodata_4C8[i]);
            }
            break;
        case 120:
            WipeColorSet(255, 255, 255);
            WipeCreate(1, 0, 30);
            player = lbl_1_bss_F8[0];
            view = &lbl_1_bss_108[player->unk006];
            view->center.x = 0.0 * sin(0.0);
            view->center.z = 0.0 * cos(0.0);
            view->center.y = 150.0f;
            view->zoom = 1500.0f;
            view->rot.y = 0.0f;
            view->rot.x = -15.0f;
            view->rot.z = 0.0f;
            omCameraViewMoveMulti(lbl_1_rodata_10[0], view, 400, 2);
            break;
        case 180:
            MgSeqModeNext();
            break;
    }
}

/* 172 insns */
void fn_1_1FC0(s16 mode, s16 frameNo)
{
    M519_PLAYER *player;
    s32 i;

    switch (frameNo) {
        case 0:
            if ((!lbl_1_bss_0 && !lbl_1_bss_4) || (lbl_1_bss_0 && lbl_1_bss_4)) {
                CharLoseVoicePlay(lbl_1_bss_E8[lbl_1_bss_F8[0]->unk008]->unk00A, lbl_1_bss_E8[lbl_1_bss_F8[1]->unk008]->unk00A,
                    lbl_1_bss_E8[lbl_1_bss_F8[2]->unk008]->unk00A, lbl_1_bss_E8[lbl_1_bss_F8[3]->unk008]->unk00A);
                for (i = 0; i < 4; i++) {
                    player = lbl_1_bss_F8[i];
                    fn_1_A770(lbl_1_bss_E8[player->unk008]);
                }
            }
            else if (lbl_1_bss_0) {
                for (i = 0; i < 4; i++) {
                    player = lbl_1_bss_F8[i];
                    if (i == 0) {
                        fn_1_A770(lbl_1_bss_E8[player->unk008]);
                    }
                    else {
                        fn_1_A6B8(lbl_1_bss_E8[player->unk008]);
                    }
                }
            }
            else if (lbl_1_bss_4) {
                for (i = 0; i < 4; i++) {
                    player = lbl_1_bss_F8[i];
                    if (i == 0) {
                        fn_1_A6B8(lbl_1_bss_E8[player->unk008]);
                    }
                    else {
                        fn_1_A770(lbl_1_bss_E8[player->unk008]);
                    }
                }
            }
            fn_1_27FC(lbl_1_bss_178);
            break;
        case 179:
            HuAudFXStop(lbl_1_bss_10);
            break;
    }
}

/* 10 insns */
void fn_1_2270(void)
{
    omOvlReturnEx(0, 1);
}

/* 239 insns */
M519_STAGE *fn_1_2298(void)
{
    static const s32 lbl_1_rodata_508[3][7] = {
        { DATANUM(DATA_m519, 0x00), DATANUM(DATA_m519, 0x03), DATANUM(DATA_m519, 0x01), DATANUM(DATA_m519, 0x02), DATANUM(DATA_m519, 0x04), DATANUM(DATA_m519, 0x05), DATANUM(DATA_m519, 0x06) },
        { DATANUM(DATA_m519, 0x00), DATANUM(DATA_m519, 0x0D), DATANUM(DATA_m519, 0x01), DATANUM(DATA_m519, 0x02), -1, -1, -1 },
        { DATANUM(DATA_m519, 0x00), DATANUM(DATA_m519, 0x17), DATANUM(DATA_m519, 0x01), DATANUM(DATA_m519, 0x02), DATANUM(DATA_m519, 0x18), DATANUM(DATA_m519, 0x19), -1 },
    };
    static const GXColor lbl_1_rodata_55C[3] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 100, 110, 120, 0 } };
    static const struct {
        s16 type;
        HuVecF pos;
        HuVecF rot;
    } lbl_1_rodata_568[3][12] = {
        {
            { 0, { 800.0f, 0.0f, -800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 800.0f, 0.0f, 800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -800.0f, 0.0f, -800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -800.0f, 0.0f, 800.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -1500.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 1500.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, -1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, 1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, -1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, 1500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        },
        {
            { 0, { 0.0f, 0.0f, 1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 600.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -600.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -600.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { -850.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -1100.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 600.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 850.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 1100.0f, 0.0f, 500.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 0.0f, 0.0f, -1000.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
        },
        {
            { 1, { -450.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { -450.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 450.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 1, { 450.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -1350.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -1350.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 1350.0f, 0.0f, -450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { 1350.0f, 0.0f, 450.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -450.0f, 0.0f, -1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 0, { -450.0f, 0.0f, 1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 450.0f, 0.0f, -1350.0f }, { 0.0f, 0.0f, 0.0f } },
            { 2, { 450.0f, 0.0f, 1350.0f }, { 0.0f, 0.0f, 0.0f } },
        },
    };
    M519_STAGE *work;
    s32 i;
    s16 type;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_STAGE), HU_MEMNUM_OVL);
    work->unk000 = 0;
    work->unk002 = 0;
    for (i = 0; i < 7; i++) {
        if (lbl_1_rodata_508[lbl_1_bss_30][i] != -1) {
            work->unk004[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_508[lbl_1_bss_30][i], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelAttrSet(work->unk004[i], HU3D_ATTR_NOCULL);
        }
        else {
            work->unk004[i] = -1;
        }
    }
    Hu3DModelCameraSet(work->unk004[2], 1);
    Hu3DModelCameraSet(work->unk004[3], 1);
    Hu3DModelAttrSet(work->unk004[1], HU3D_MOTATTR_LOOP);
    if (work->unk004[4] != -1) {
        Hu3DModelAttrSet(work->unk004[4], HU3D_MOTATTR_LOOP);
    }
    if (work->unk004[5] != -1) {
        Hu3DModelAttrSet(work->unk004[5], HU3D_MOTATTR_LOOP);
    }
    if (work->unk004[6] != -1) {
        Hu3DModelAttrSet(work->unk004[6], HU3D_MOTATTR_LOOP);
    }
    Hu3DModelLayerSet(work->unk004[0], 1);
    Hu3DModelLayerSet(work->unk004[1], 0);
    Hu3DModelLayerSet(work->unk004[2], 1);
    Hu3DModelLayerSet(work->unk004[3], 2);
    if (work->unk004[4] != -1) {
        Hu3DModelLayerSet(work->unk004[4], 0);
    }
    if (work->unk004[5] != -1) {
        Hu3DModelLayerSet(work->unk004[5], 0);
    }
    if (work->unk004[6] != -1) {
        Hu3DModelLayerSet(work->unk004[6], 0);
    }
    Hu3DBGColorSet(lbl_1_rodata_55C[lbl_1_bss_30].r, lbl_1_rodata_55C[lbl_1_bss_30].g, lbl_1_rodata_55C[lbl_1_bss_30].b);
    work->unk044 = HuPrcChildCreate(fn_1_2654, 0x1000, 0x1000, 0, HuPrcCurrentGet());
    work->unk044->property = work;
    for (i = 0; i < 12; i++) {
        type = lbl_1_rodata_568[lbl_1_bss_30][i].type;
        if (type != 2) {
            work->unk014[i] = fn_1_C058(type);
            fn_1_C288(work->unk014[i], lbl_1_rodata_568[lbl_1_bss_30][i].pos);
            fn_1_C328(work->unk014[i], lbl_1_rodata_568[lbl_1_bss_30][i].rot);
            fn_1_C3C8(work->unk014[i]);
        }
        else {
            work->unk014[i] = NULL;
        }
    }
    return work;
}

/* 16 insns */
void fn_1_2654(void)
{
    M519_STAGE *work = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_1C[work->unk000](work);
    }
}

/* 3 insns */
void fn_1_2694(M519_STAGE *stage)
{
    stage->unk000 = 0;
}

/* 36 insns: lbl_1_data_1C[0], the idle state */
void fn_1_26A0(M519_STAGE *stage)
{
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 24 insns */
void fn_1_2730(M519_STAGE *stage)
{
    Hu3DModelAttrSet(stage->unk004[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(stage->unk004[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(stage->unk004[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(stage->unk004[3], HU3D_MOTATTR_PAUSE);
}

/* 27 insns */
void fn_1_2790(M519_STAGE *stage)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (stage->unk014[i] != NULL) {
            fn_1_C544(stage->unk014[i]);
        }
    }
}

/* 37 insns */
void fn_1_27FC(M519_STAGE *stage)
{
    Hu3DModelAttrReset(stage->unk004[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(stage->unk004[2], HU3D_ATTR_DISPOFF);
    Hu3DMotionStartEndSet(stage->unk004[2], 0.0f, Hu3DMotionMaxTimeGet(stage->unk004[2]));
    Hu3DMotionTimeSet(stage->unk004[2], Hu3DMotionMaxTimeGet(stage->unk004[2]));
    Hu3DModelAttrSet(stage->unk004[2], HU3D_MOTATTR_REV);
    Hu3DModelAttrReset(stage->unk004[2], HU3D_MOTATTR_LOOP);
}

/* 28 insns */
void fn_1_2890(M519_STAGE *stage)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (stage->unk014[i] != NULL) {
            fn_1_C788(stage->unk014[i], 0);
        }
    }
}

/* 31 insns */
void fn_1_2900(M519_STAGE *stage)
{
    s32 i;

    for (i = 0; i < 12; i++) {
        if (stage->unk014[i] != NULL) {
            fn_1_C3C8(stage->unk014[i]);
            fn_1_CBEC(stage->unk014[i]);
        }
    }
}

/* 374 insns */
M519_PLAYER *fn_1_297C(s16 type, s16 slot)
{
    static const s32 lbl_1_rodata_958[2][9] = {
        { DATANUM(DATA_m519, 0x21), DATANUM(DATA_m519, 0x34), DATANUM(DATA_m519, 0x37), DATANUM(DATA_m519, 0x32), DATANUM(DATA_m519, 0x33),
            DATANUM(DATA_m519, 0x3F), DATANUM(DATA_m519, 0x22), DATANUM(DATA_m519, 0x23), DATANUM(DATA_m519, 0x40) },
        { DATANUM(DATA_m519, 0x2B), DATANUM(DATA_m519, 0x3A), DATANUM(DATA_m519, 0x41), DATANUM(DATA_m519, 0x31), DATANUM(DATA_m519, 0x42),
            DATANUM(DATA_m519, 0x43), DATANUM(DATA_m519, 0x44), -1, -1 },
    };
    static const s32 lbl_1_rodata_9A0[2][7] = {
        { DATANUM(DATA_m519, 0x24), DATANUM(DATA_m519, 0x25), DATANUM(DATA_m519, 0x26), DATANUM(DATA_m519, 0x28), DATANUM(DATA_m519, 0x27),
            DATANUM(DATA_m519, 0x29), DATANUM(DATA_m519, 0x2A) },
        { DATANUM(DATA_m519, 0x2C), DATANUM(DATA_m519, 0x2D), DATANUM(DATA_m519, 0x2E), DATANUM(DATA_m519, 0x2D), DATANUM(DATA_m519, 0x2E),
            DATANUM(DATA_m519, 0x2F), DATANUM(DATA_m519, 0x2F) },
    };
    static const struct {
        float unk000;
        float unk004;
        float unk008;
        s16 unk00C;
    } lbl_1_rodata_9D8[2] = {
        { 0.17857143f, 0.029761905f, 140.0f, 80 },
        { 0.5952381f, 0.05952381f, 80.0f, 40 },
    };
    M519_PLAYER *work;
    s32 i;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_PLAYER), HU_MEMNUM_OVL);
    work->unk004 = type;
    work->unk03C = -1;
    work->unk008 = 0;
    work->unk006 = slot;
    work->unk02E = 0;
    work->unk03A = 0;
    work->unk050 = 0.0f;
    work->unk054 = 0.0f;
    work->unk058 = 0.0f;
    work->unk05C = 0.0f;
    work->unk064 = lbl_1_rodata_9D8[type].unk000;
    work->unk060 = lbl_1_rodata_9D8[type].unk004;
    work->unk02A = 1;
    work->unk02C = 0;
    work->unk084.x = 0.0f;
    work->unk084.y = 0.0f;
    work->unk084.z = 0.0f;
    work->unk090.x = 0.0f;
    work->unk090.y = 0.0f;
    work->unk090.z = 0.0f;
    work->unk036 = 0;
    work->unk038 = 0;
    work->unk044 = 0;
    work->unk048 = 0;
    work->unk04C = 1;
    work->unk074 = 0.0f;
    work->unk070 = lbl_1_rodata_9D8[type].unk008;
    work->unk034 = lbl_1_rodata_9D8[type].unk00C;
    work->unk030 = work->unk034;
    work->unk032 = work->unk034;
    work->unk0B4 = NULL;
    work->unk0B8 = NULL;
    work->unk068 = 0.0f;
    work->unk06C = 0.0f;
    work->unk0D4 = 0;
    work->unk0EE = 0;
    work->unk03E = 0;
    work->unk0E6 = 0;
    work->unk0C4 = 0;
    work->unk0F0 = -1;
    work->unk0C0 = 0;
    work->unk000 = 0;
    work->unk002 = 0;
    for (i = 0; i < 9; i++) {
        if (lbl_1_rodata_958[type][i] != -1) {
            work->unk00A[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_958[type][i], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelAttrSet(work->unk00A[i], HU3D_ATTR_NOCULL);
        }
        else {
            work->unk00A[i] = -1;
        }
    }
    switch (type) {
        case 0:
            Hu3DModelAttrSet(work->unk00A[6], HU3D_ATTR_ZWRITE_OFF);
            Hu3DModelAttrSet(work->unk00A[6], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->unk00A[7], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->unk00A[8], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
            Hu3DModelAttrSet(work->unk00A[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[7], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[8], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(work->unk00A[0], 2);
            Hu3DModelLayerSet(work->unk00A[1], 2);
            Hu3DModelLayerSet(work->unk00A[2], 2);
            Hu3DModelLayerSet(work->unk00A[3], 2);
            Hu3DModelLayerSet(work->unk00A[4], 2);
            Hu3DModelLayerSet(work->unk00A[5], 2);
            Hu3DModelLayerSet(work->unk00A[6], 2);
            Hu3DModelLayerSet(work->unk00A[7], 2);
            Hu3DModelLayerSet(work->unk00A[8], 2);
            break;
        case 1:
            Hu3DModelAttrSet(work->unk00A[2], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(work->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
            Hu3DModelAttrSet(work->unk00A[3], HU3D_ATTR_ZCMP_OFF);
            Hu3DModelAttrSet(work->unk00A[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[4], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(work->unk00A[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[5], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk00A[6], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(work->unk00A[0], 2);
            Hu3DModelLayerSet(work->unk00A[1], 2);
            Hu3DModelLayerSet(work->unk00A[2], 2);
            Hu3DModelLayerSet(work->unk00A[4], 2);
            Hu3DModelLayerSet(work->unk00A[5], 2);
            Hu3DModelLayerSet(work->unk00A[6], 2);
            Hu3DModelLayerSet(work->unk00A[3], 7);
            Hu3DModelCameraSet(work->unk00A[3], lbl_1_rodata_10[slot]);
            break;
    }
    for (i = 0; i < 7; i++) {
        work->unk01C[i] = Hu3DJointMotion(work->unk00A[0], HuDataSelHeapReadNum(lbl_1_rodata_9A0[type][i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    fn_1_2FA0(work, 0, 1.0f);
    switch (type) {
        case 0:
            break;
        case 1:
            work->unk0B4 = fn_1_CC44();
            fn_1_CDF4(work->unk0B4);
            work->unk0B8 = fn_1_CC44();
            fn_1_CDF4(work->unk0B8);
            break;
    }
    work->unk0BC = HuPrcChildCreate(fn_1_2F54, 0x800, 0x2800, 0, HuPrcCurrentGet());
    work->unk0BC->property = work;
    return work;
}

/* 19 insns */
void fn_1_2F54(void)
{
    M519_PLAYER *work = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_20[work->unk004][work->unk000](work);
    }
}

/* 62 insns */
void fn_1_2FA0(M519_PLAYER *player, s16 motion, float speed)
{
    if ((s16)player->unk02C != player->unk02A) {
        Hu3DMotionShiftSet(player->unk00A[0], player->unk01C[motion], lbl_1_rodata_9F8[player->unk004][motion].unk000,
            lbl_1_rodata_9F8[player->unk004][motion].unk004, lbl_1_rodata_9F8[player->unk004][motion].unk008);
        player->unk02C = player->unk02A;
        player->unk0F8 = 0.0f;
    }
    player->unk02A = motion;
    Hu3DMotionSpeedSet(player->unk00A[0], speed);
}

/* 40 insns */
void fn_1_3098(M519_PLAYER *player)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (player->unk00A[i] != -1) {
            Hu3DModelTPLvlSet(player->unk00A[i], 0.0f);
            Hu3DModelAttrSet(player->unk00A[i], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(player->unk00A[i], HU3D_ATTR_DISPOFF);
        }
    }
}

/* 79 insns */
void fn_1_3138(M519_PLAYER *player, HuVecF pos)
{
    s32 i;

    player->unk09C = player->unk084;
    player->unk084 = pos;
    for (i = 0; i < 9; i++) {
        if (player->unk00A[i] != -1) {
            Hu3DModelPosSet(player->unk00A[i], pos.x, pos.y, pos.z);
        }
    }
    switch (player->unk004) {
        case 0:
            Hu3DModelPosSet(player->unk00A[5], pos.x, 8.0f + pos.y, pos.z);
            break;
        case 1:
            Hu3DModelPosSet(player->unk00A[2], pos.x, 8.0f + pos.y, pos.z);
            Hu3DModelPosSet(player->unk00A[3], pos.x, 180.0f + pos.y, pos.z);
            break;
    }
}

/* 7 insns */
HuVecF fn_1_3274(M519_PLAYER *player)
{
    return player->unk084;
}

/* 155 insns */
void fn_1_3290(M519_PLAYER *player, HuVecF rot)
{
    MtxPtr mtx;
    s32 i;
    float angle;

    player->unk0A8 = player->unk090;
    player->unk090 = rot;
    for (i = 0; i < 9; i++) {
        if (player->unk004 == 1 && i == 2) {
            continue;
        }
        if (player->unk004 == 0 && i == 5) {
            continue;
        }
        if (player->unk00A[i] != -1) {
            mtx = Hu3DData[player->unk00A[i]].mtx;
            MTXIdentity(mtx);
            MTXRotRad(mtx, 'z', 0.017453292f * rot.z);
            Hu3DModelRotSet(player->unk00A[i], rot.x, rot.y, 0.0f);
        }
    }
    switch (player->unk004) {
        case 0:
            break;
        case 1:
            mtx = Hu3DData[player->unk00A[3]].mtx;
            MTXIdentity(mtx);
            angle = HuAbs(fmod(player->unk090.y - player->unk074, 360.0));
            if (angle > 180.0f) {
                angle = 180.0f - (angle - 180.0f);
            }
            Hu3DModelRotSet(player->unk00A[3], -45.0f + 0.5f * angle, player->unk074, 0.0f);
            break;
    }
}

/* 7 insns */
HuVecF fn_1_34FC(M519_PLAYER *player)
{
    return player->unk090;
}

/* 26 insns: hook the player's body model onto the character's model */
void fn_1_3518(M519_PLAYER *player, M519_CHAR *chr)
{
    Hu3DModelHookSet(player->unk00A[0], (char *)lbl_1_data_14[player->unk004], chr->unk014[1]);
    player->unk008 = chr->unk006;
    chr->unk008 = player->unk006;
}

/* 12 insns */
void fn_1_3580(M519_PLAYER *player)
{
    Hu3DModelHookReset(player->unk00A[0]);
}

/* 3 insns */
void fn_1_35B0(M519_PLAYER *player)
{
    player->unk000 = 0;
}

/* 39 insns: lbl_1_data_20[0] / [5], idle */
void fn_1_35BC(M519_PLAYER *player)
{
    while (1) {
        fn_1_95B0(player);
        fn_1_9700(player);
        fn_1_8450(player);
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_3658(M519_PLAYER *player)
{
    player->unk000 = 1;
}

/* fork B: pan per player row (0x4138, 0x62D8) and voice pan (0x37CC) */
const s16 lbl_1_rodata_1C[2] = { 0x30, 0x50 };
/* voice SE per charNo (0x37B4, 0x604C) */
const s32 lbl_1_rodata_164[13] = { 0x1F9, 0x1E5, 0x25D, 0x2AD, 0x285, 0x1BD, 0x299, 0x1D1, 0x271, 0x235, 0x249, 0x221, 0x20D };

#define M519_ABS(x) (((x) < 0.0f) ? -(x) : (x))

/* 1463 insns: lbl_1_data_20[1], type-0 player drive state */
void fn_1_3664(M519_PLAYER *player)
{
    float stkX;
    float stkY;
    float speed;
    float rotSpeed;
    float accelRot;
    float accelSpeed;
    float dx;
    float dz;
    float angle;
    s32 dead;

    dead = 0;
    accelRot = 0.2f;
    accelSpeed = 0.2f;
    while (1) {
        player->unk0CC = 0;
        player->unk0CE = 0;
        player->unk0D0 = 0;
        player->unk0D2 = 0;
        player->unk0CA = 0;
        player->unk0C8 = 0;
        if (player->unk030 > 0) {
            if (player->unk044) {
                if (lbl_1_bss_E8[player->unk008]->unk00C) {
                    fn_1_4E18(player);
                } else {
                    fn_1_4D40(player);
                }
            }
        } else if (!dead) {
            HuAudFXPlayPan(lbl_1_rodata_164[lbl_1_bss_E8[player->unk008]->unk00A], lbl_1_rodata_1C[player->unk004]);
            HuAudFXPlay(0x71E);
            Hu3DModelAttrReset(player->unk00A[8], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(player->unk00A[8], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(player->unk00A[8], HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(player->unk00A[8], 0.0f);
            fn_1_FD7C(player->unk008, 2, 60);
            dead = 1;
        } else if (player->unk050 <= 0.0f) {
            fn_1_817C(player);
            return;
        }
        if (player->unk0D2 >= 150 || player->unk0D0 >= 150) {
            if (!player->unk048) {
                player->unk048 = 1;
                player->unk050 = 0.0f;
                player->unk054 = 0.0f;
            }
            speed = player->unk050;
            stkX = player->unk0CC * -player->unk064;
            stkY = player->unk0CE * player->unk064;
            angle = 180.0 * (atan2(stkX, stkY) / M_PI);
            speed = sqrtf(stkX * stkX + stkY * stkY);
            dx = speed * sin(M_PI * (angle + player->unk090.y) / 180.0);
            dz = speed * cos(M_PI * (angle + player->unk090.y) / 180.0);
            player->unk050 = speed;
            rotSpeed = 0.0f;
            if (stkY > 0.0f && M519_ABS(stkY) > M519_ABS(stkX)) {
                fn_1_2FA0(player, 1, 1.0f + M519_ABS(0.5f * stkY));
            } else if (stkY < 0.0f && M519_ABS(stkY) > M519_ABS(stkX)) {
                fn_1_2FA0(player, 2, 1.0f + M519_ABS(0.5f * stkY));
            } else if (stkX < 0.0f) {
                fn_1_2FA0(player, 3, 1.0f + M519_ABS(0.5f * stkX));
            } else if (stkX > 0.0f) {
                fn_1_2FA0(player, 4, 1.0f + M519_ABS(0.5f * stkX));
            } else {
                fn_1_2FA0(player, 0, 1.0f);
            }
            if (0.0f != stkY && M519_ABS(stkY) > M519_ABS(stkX)) {
                if (player->unk0F8 >= 0.0f && player->unk0F8 < M519_ABS(0.5f * stkY)) {
                    HuAudFXPlayPan(0x70B, lbl_1_rodata_18[player->unk004]);
                }
                player->unk0F8 += 1.0f + M519_ABS(0.5f * stkY);
            } else if (0.0f != stkX) {
                if (player->unk0F8 >= 0.0f && player->unk0F8 < M519_ABS(0.5f * stkX)) {
                    HuAudFXPlayPan(0x70B, lbl_1_rodata_18[player->unk004]);
                }
                player->unk0F8 += 1.0f + M519_ABS(0.5f * stkX);
            }
            if (player->unk0F8 >= 80.0f) {
                player->unk0F8 = 0.0f;
            }
        } else {
            if (player->unk048) {
                player->unk048 = 0;
                player->unk050 = 0.0f;
            }
            rotSpeed = player->unk054;
            speed = player->unk050;
            player->unk05C = player->unk0CC * -player->unk060;
            player->unk058 = player->unk0CE * player->unk064;
            if (rotSpeed < player->unk05C) {
                rotSpeed += accelRot;
                if (rotSpeed > player->unk05C) {
                    rotSpeed = player->unk05C;
                }
            }
            if (rotSpeed > player->unk05C) {
                rotSpeed -= accelRot;
                if (rotSpeed < player->unk05C) {
                    rotSpeed = player->unk05C;
                }
            }
            if (speed < player->unk058) {
                speed += accelSpeed;
                if (speed > player->unk058) {
                    speed = player->unk058;
                }
            }
            if (speed > player->unk058) {
                speed -= accelSpeed;
                if (speed < player->unk058) {
                    speed = player->unk058;
                }
            }
            dx = speed * sin(M_PI * player->unk090.y / 180.0);
            dz = speed * cos(M_PI * player->unk090.y / 180.0);
            player->unk054 = rotSpeed;
            player->unk050 = speed;
            if (speed > 0.0f) {
                fn_1_2FA0(player, 1, 1.0f + M519_ABS(0.5f * speed));
            } else if (speed < 0.0f) {
                fn_1_2FA0(player, 2, 1.0f + M519_ABS(0.5f * speed));
            } else if (0.0f != rotSpeed) {
                fn_1_2FA0(player, 1, 1.0f + M519_ABS(0.5f * rotSpeed));
            } else {
                fn_1_2FA0(player, 0, 1.0f);
            }
            if (0.0f != speed) {
                if ((player->unk0F8 >= 0.0f && player->unk0F8 < M519_ABS(0.5f * speed))
                    || (player->unk0F8 >= 39.0f && player->unk0F8 < 39.0f + M519_ABS(0.5f * speed))) {
                    HuAudFXPlayPan(0x70A, lbl_1_rodata_18[player->unk004]);
                }
                player->unk0F8 += 1.0f + M519_ABS(0.5f * speed);
            }
            if (0.0f != rotSpeed) {
                if ((player->unk0F8 >= 0.0f && player->unk0F8 < M519_ABS(0.5f * rotSpeed))
                    || (player->unk0F8 >= 39.0f && player->unk0F8 < 39.0f + M519_ABS(0.5f * rotSpeed))) {
                    HuAudFXPlayPan(0x70A, lbl_1_rodata_18[player->unk004]);
                }
                player->unk0F8 += 1.0f + M519_ABS(0.5f * rotSpeed);
            }
            if (player->unk0F8 >= 80.0f) {
                player->unk0F8 = 0.0f;
            }
        }
        player->unk084.x += dx;
        player->unk084.z += dz;
        player->unk090.y += rotSpeed;
        fn_1_82E4(player);
        fn_1_95B0(player);
        fn_1_9700(player);
        fn_1_8450(player);
        fn_1_8E40(player);
        M519_OBJWAIT(1);
    }
}

/* 54 insns: pad input */
void fn_1_4D40(M519_PLAYER *player)
{
    s16 padNo = lbl_1_bss_E8[player->unk008]->unk012;

    player->unk0CC = HuPadStkX[padNo];
    player->unk0CE = HuPadStkY[padNo];
    player->unk0D0 = HuPadTrigL[padNo];
    player->unk0D2 = HuPadTrigR[padNo];
    player->unk0CA = HuPadBtn[padNo];
    player->unk0C8 = HuPadBtnDown[padNo];
}

/* fork B: COM tuning by GwPlayerConf[].dif (fn_1_4E18) */
const s32 lbl_1_rodata_AE0[4] = { 180, 170, 150, 160 };
const float lbl_1_rodata_AF0[4] = { 15.0f, 16.0f, 17.0f, 18.0f };
const s16 lbl_1_rodata_B00[4] = { 30, 25, 20, 20 };
const s32 lbl_1_rodata_B08[4] = { 640, 660, 680, 700 };
const s32 lbl_1_rodata_B18[4] = { 1300, 1200, 1100, 1000 };
const s16 lbl_1_rodata_B28[4] = { 35, 25, 20, 15 };
const s32 lbl_1_rodata_B30[4] = { 600, 610, 620, 630 };
const s16 lbl_1_rodata_B40[4] = { 6, 4, 2, 0 };
const float lbl_1_rodata_B48[4] = { 35.0f, 34.0f, 33.0f, 32.0f };

/* 1073 insns: type-0 COM input */
void fn_1_4E18(M519_PLAYER *player)
{
    HuVecF pos;
    float dx;
    float dz;
    float angle;
    float stkY;
    float dist;
    float turn;
    float minDist;
    float sumDist;
    float minAngle;
    M519_PLAYER *target;
    s16 dif;
    s16 nearIdx;
    s32 inSight;
    s16 count;
    s32 i;

    dif = lbl_1_bss_E8[player->unk008]->unk010;
    pos.x = player->unk084.x;
    pos.y = player->unk084.z;
    pos.z = player->unk070;
    target = lbl_1_bss_F8[player->unk0E4];
    switch (player->unk0EE) {
    case 0:
        if (!player->unk0D4) {
            dist = frandmod(2390.0f - player->unk070);
            angle = frand() % 360;
            player->unk0D8.x = dist * sin(M_PI * angle / 180.0);
            player->unk0D8.z = dist * cos(M_PI * angle / 180.0);
            player->unk0D8.y = 0.0f;
            player->unk0E8 = 0;
            player->unk0EC = frand() % 20 + 50;
            player->unk0D4 = 1;
        }
        dx = player->unk0D8.x - player->unk084.x;
        dz = player->unk0D8.z - player->unk084.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 300.0f || player->unk0E8++ > lbl_1_rodata_AE0[dif]) {
            player->unk0EC = 0;
            player->unk0EE = 1;
            player->unk0E8 = 0;
            player->unk0D4 = 0;
            player->unk0E4 = (s16)frandmod(3) + 1;
        } else {
            player->unk0C8 |= 0x100;
        }
        break;
    case 1:
        nearIdx = 0;
        minDist = 4780.0f;
        minAngle = 360.0f;
        inSight = 0;
        count = 0;
        sumDist = 0.0f;
        if (player->unk0E8 > 0) {
            player->unk0E8--;
        }
        for (i = 0; i < 3; i++) {
            target = lbl_1_bss_F8[i + 1];
            if (!fn_1_A1D4(target)) {
                count++;
                dx = target->unk084.x - player->unk084.x;
                dz = target->unk084.z - player->unk084.z;
                dist = sqrtf(dx * dx + dz * dz);
                sumDist += dist;
                angle = 180.0 * (atan2(player->unk084.x - target->unk084.x, player->unk084.z - target->unk084.z) / M_PI) + 180.0 - player->unk090.y;
                if (angle < 0.0f) {
                    angle = 360.0f + angle;
                }
                if (angle >= 360.0f) {
                    angle -= 360.0f;
                }
                if (angle >= 180.0f) {
                    angle -= 360.0f;
                }
                angle = -angle;
                if (minAngle > M519_ABS(angle)) {
                    minAngle = M519_ABS(angle);
                    if (dist < 2000.0f) {
                        nearIdx = i + 1;
                    }
                }
                if (minDist > dist) {
                    minDist = dist;
                }
                if (M519_ABS(angle) < lbl_1_rodata_AF0[dif]) {
                    inSight = 1;
                }
            }
        }
        if (count == 0) {
            break;
        }
        if (player->unk0E8 == 0) {
            if (nearIdx > 0) {
                player->unk0E4 = nearIdx;
            }
            if (!fn_1_A1D4(lbl_1_bss_F8[player->unk0E4])) {
                player->unk0E8 = lbl_1_rodata_B00[dif];
            } else {
                player->unk0E4 = (s16)frandmod(3) + 1;
            }
        }
        target = lbl_1_bss_F8[player->unk0E4];
        player->unk0D8 = target->unk084;
        dx = player->unk0D8.x - player->unk084.x;
        dz = player->unk0D8.z - player->unk084.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist > 500.0f) {
            player->unk0EC = -(s32)(0.015 * dist);
        }
        if (dist < 2000.0f) {
            player->unk0EC = 0;
        } else {
            player->unk0EC = (s32)(0.015 * dist);
        }
        switch (player->unk03E) {
        case 0:
            if (inSight) {
                player->unk0C8 |= 0x100;
                player->unk0EA = 0;
                if (minDist < lbl_1_rodata_B08[dif]) {
                    player->unk03E = 2;
                }
            } else if (player->unk0EA++ > lbl_1_rodata_B28[dif]) {
                if (sumDist / count > lbl_1_rodata_B18[dif]) {
                    player->unk03E = 1;
                } else {
                    player->unk03E = 3;
                }
            }
            break;
        case 1:
            if (inSight && player->unk036 > 90) {
                player->unk03E = 0;
            } else {
                player->unk0CA |= 0x100;
            }
            break;
        case 2:
            player->unk0C8 |= 0x200;
            if (minDist > lbl_1_rodata_B30[dif]) {
                player->unk03E = 0;
            }
            break;
        case 3:
            if (player->unk038 > 90) {
                player->unk03E = 0;
            } else {
                player->unk0CA |= 0x200;
            }
            break;
        }
        break;
    case 2:
        break;
    }
    if (player->unk0E6 > 0) {
        player->unk0E6--;
        player->unk0C8 &= ~0x100;
    } else if (player->unk0C8 & 0x100) {
        player->unk0E6 = lbl_1_rodata_B40[dif] + 8;
    }
    turn = 0.0f;
    if (player->unk0D8.x != player->unk084.x || player->unk0D8.z != player->unk084.z) {
        turn = 180.0 * (atan2(player->unk084.x - player->unk0D8.x, player->unk084.z - player->unk0D8.z) / M_PI) + 180.0 - player->unk090.y;
        if (turn < 0.0f) {
            turn = 360.0f + turn;
        }
        if (turn >= 360.0f) {
            turn -= 360.0f;
        }
        if (turn >= 180.0f) {
            turn -= 360.0f;
        }
        turn = -turn;
    }
    angle = turn;
    angle = (angle > 60.0f) ? 60.0f : angle;
    angle = (angle < -60.0f) ? -60.0f : angle;
    dx = angle * (s16)(68.0f / lbl_1_rodata_B48[dif]);
    stkY = player->unk0EC;
    dist = sqrt(dx * dx + stkY * stkY);
    angle = 180.0 * (atan2(dx, stkY) / M_PI);
    dx = dist * sin(M_PI * angle / 180.0);
    stkY = dist * cos(M_PI * angle / 180.0);
    player->unk0CC = dx;
    player->unk0CE = stkY;
}

/* 642 insns: lbl_1_data_20[6], type-1 player drive state */
void fn_1_5EDC(M519_PLAYER *player)
{
    float rotSpeed;
    float speed;
    float dx;
    float dz;
    float accelRot;
    float accelSpeed;
    s32 dead;
    s16 padNo;
    s16 playerNo;

    dead = 0;
    accelRot = 0.18f;
    accelSpeed = 0.36f;
    padNo = lbl_1_bss_E8[player->unk008]->unk012;
    playerNo = lbl_1_bss_E8[player->unk008]->unk006;
    while (1) {
        rotSpeed = player->unk054;
        speed = player->unk050;
        player->unk0CC = 0;
        player->unk0CE = 0;
        player->unk0D0 = 0;
        player->unk0D2 = 0;
        player->unk0CA = 0;
        player->unk0C8 = 0;
        if (player->unk030 > 0) {
            if (player->unk044) {
                if (lbl_1_bss_E8[player->unk008]->unk00C) {
                    fn_1_69BC(player);
                } else {
                    fn_1_68E4(player);
                }
            }
        } else if (!dead) {
            HuAudFXPlay(lbl_1_rodata_164[lbl_1_bss_E8[player->unk008]->unk00A]);
            HuAudFXPlay(0x71F);
            Hu3DModelAttrReset(player->unk00A[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(player->unk00A[4], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(player->unk00A[4], HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(player->unk00A[4], 0.0f);
            fn_1_FD7C(player->unk008, 2, 60);
            dead = 1;
        } else if (player->unk050 <= 0.0f) {
            fn_1_817C(player);
            return;
        }
        player->unk05C = player->unk0CC * -player->unk060;
        player->unk058 = player->unk0CE * player->unk064;
        if (player->unk0CA & 0x200) {
            if (player->unk038++ == 0) {
                if (player->unk0F0 != -1) {
                    HuAudFXStop(player->unk0F0);
                }
                player->unk0F0 = HuAudFXPlay(0x721);
                Hu3DModelAttrReset(player->unk00A[5], HU3D_ATTR_DISPOFF);
                Hu3DMotionStartEndSet(player->unk00A[5], 0.0f, 60.0f);
                Hu3DMotionTimeSet(player->unk00A[5], 0.0f);
                Hu3DModelAttrSet(player->unk00A[5], HU3D_MOTATTR_LOOP);
            } else if (player->unk038 == 40) {
                Hu3DMotionStartEndSet(player->unk00A[5], 40.0f, 60.0f);
                Hu3DMotionTimeSet(player->unk00A[5], 0.0f);
                Hu3DModelAttrSet(player->unk00A[5], HU3D_MOTATTR_LOOP);
            }
            if (player->unk038 >= 40 && player->unk038 % 5 == 0) {
                fn_1_FD7C(player->unk008, 1, 3);
            }
        } else if (player->unk038 > 0) {
            Hu3DModelAttrSet(player->unk00A[5], HU3D_ATTR_DISPOFF);
            if (player->unk0F0 != -1) {
                HuAudFXStop(player->unk0F0);
                player->unk0F0 = -1;
            }
            if (player->unk038 >= 90) {
                HuAudFXPlayPan(0x71D, lbl_1_rodata_18[player->unk004]);
                Hu3DMotionStartEndSet(player->unk00A[6], 0.0f, 60.0f);
                Hu3DMotionTimeSet(player->unk00A[6], 0.0f);
                Hu3DModelAttrReset(player->unk00A[6], HU3D_ATTR_DISPOFF);
                player->unk058 = 100.0f * player->unk064;
                speed = 100.0f * player->unk064;
            }
            player->unk038 = 0;
        }
        if (rotSpeed < player->unk05C) {
            rotSpeed += accelRot;
            if (rotSpeed > player->unk05C) {
                rotSpeed = player->unk05C;
            }
        }
        if (rotSpeed > player->unk05C) {
            rotSpeed -= accelRot;
            if (rotSpeed < player->unk05C) {
                rotSpeed = player->unk05C;
            }
        }
        if (speed < player->unk058) {
            speed += accelSpeed;
            if (speed > player->unk058) {
                speed = player->unk058;
            }
        }
        if (speed > player->unk058) {
            speed -= accelSpeed;
            if (speed < player->unk058) {
                speed = player->unk058;
            }
        }
        player->unk090.y += rotSpeed;
        player->unk090.z = rotSpeed * -M519_ABS(0.2f * speed);
        dx = speed * sin(M_PI * player->unk090.y / 180.0);
        dz = speed * cos(M_PI * player->unk090.y / 180.0);
        player->unk084.x += dx;
        player->unk084.z += dz;
        player->unk054 = rotSpeed;
        player->unk050 = speed;
        if (speed > 0.0f) {
            fn_1_2FA0(player, 1, 1.0f);
        } else if (speed < 0.0f) {
            fn_1_2FA0(player, 2, 1.0f);
        } else if (0.0f != rotSpeed) {
            fn_1_2FA0(player, 1, 1.0f);
        } else if (Hu3DMotionEndCheck(player->unk00A[0])) {
            fn_1_2FA0(player, 0, 1.0f);
        }
        if (M519_ABS(speed) > 16.0f) {
            fn_1_7998(player);
        }
        fn_1_82E4(player);
        fn_1_95B0(player);
        fn_1_9700(player);
        fn_1_8450(player);
        fn_1_8D40(player);
        if (M519_ABS(speed) < 72.0f) {
            fn_1_8E40(player);
        }
        M519_OBJWAIT(1);
    }
}

/* 54 insns: pad input (type 1) */
void fn_1_68E4(M519_PLAYER *player)
{
    s16 padNo = lbl_1_bss_E8[player->unk008]->unk012;

    player->unk0CC = HuPadStkX[padNo];
    player->unk0CE = HuPadStkY[padNo];
    player->unk0D0 = HuPadTrigL[padNo];
    player->unk0D2 = HuPadTrigR[padNo];
    player->unk0CA = HuPadBtn[padNo];
    player->unk0C8 = HuPadBtnDown[padNo];
}

/* 1015 insns: COM pad input (fn_1_5EDC calls it instead of fn_1_68E4 when lbl_1_bss_E8[]->unk00C) */
void fn_1_69BC(M519_PLAYER *player)
{
    static const s32 lbl_1_rodata_BA0[4] = { 2000, 2100, 2200, 2300 };
    static const s32 lbl_1_rodata_BB0[4] = { 40, 30, 20, 10 };
    static const s32 lbl_1_rodata_BC0[4] = { 180, 170, 150, 160 };
    static const s32 lbl_1_rodata_BD0[4] = { 550, 540, 530, 520 };
    static const s32 lbl_1_rodata_BE0[4] = { 10, 15, 20, 25 };
    static const s16 lbl_1_rodata_BF0[4] = { 4, 3, 2, 0 };
    HuVecF self;
    HuVecF target;
    HuVecF center;
    s16 dif;
    M519_PLAYER *solo;
    float angle;
    float ofs;
    float stickY;
    float dist;
    float dx;
    float diff;
    float dz;
    float turn;

    dif = lbl_1_bss_E8[player->unk008]->unk010;
    solo = lbl_1_bss_F8[0];
    self.x = player->unk084.x;
    self.y = player->unk084.z;
    self.z = player->unk070;
    switch (player->unk0EE) {
        case 0:
            if (player->unk0D4 == 0) {
                dist = (s32)frand() % (s32)(2390.0f - 2.0f * player->unk070);
                angle = (s32)frand() % 360;
                player->unk0D8.x = dist * sin(M_PI * angle / 180.0);
                player->unk0D8.z = dist * cos(M_PI * angle / 180.0);
                player->unk0D8.y = 0.0f;
                player->unk0E8 = 0;
                player->unk0EC = (s32)frand() % 20 + 50;
                player->unk0D4 = 1;
            }
            dx = player->unk0D8.x - player->unk084.x;
            dz = player->unk0D8.z - player->unk084.z;
            dist = sqrtf(dx * dx + dz * dz);
            if (dist > 300.0f && dist < lbl_1_rodata_BA0[dif]) {
                player->unk0EE = 1;
                player->unk0E8 = 0;
                if (player->unk0C4 == 0 && (s32)frand() % lbl_1_rodata_BB0[dif] == 0) {
                    player->unk0C4 = 1;
                }
            }
            else if (dist < 250.0f || player->unk0E8++ > lbl_1_rodata_BC0[dif]) {
                player->unk0D4 = 0;
                player->unk0E8 = 0;
            }
            break;
        case 1:
            player->unk0D8.x = solo->unk084.x;
            player->unk0D8.z = solo->unk084.z;
            player->unk0D8.y = 0.0f;
            dx = player->unk0D8.x - player->unk084.x;
            dz = player->unk0D8.z - player->unk084.z;
            dist = sqrtf(dx * dx + dz * dz);
            if (dist < lbl_1_rodata_BD0[dif] || player->unk068 > 0.0f) {
                player->unk0EE = 2;
                player->unk0D4 = 0;
                player->unk0E8 = 0;
            }
            else {
                angle = (180.0 + 180.0 * (atan2(player->unk084.x - player->unk0D8.x, player->unk084.z - player->unk0D8.z) / M_PI)) - player->unk090.y;
                if (angle < 0.0f) {
                    angle = 360.0f + angle;
                }
                if (angle >= 360.0f) {
                    angle -= 360.0f;
                }
                if (angle >= 180.0f) {
                    angle -= 360.0f;
                }
                angle = -angle;
                player->unk0EC = 20.0f + dist / 120.0f;
                if (((angle < 0.0f) ? -angle : angle) < lbl_1_rodata_BE0[dif]) {
                    player->unk0C8 = 0x100;
                }
            }
            break;
        case 2:
            if (player->unk0D4 == 0) {
                dist = 2300.0f + (s32)frand() % 1700;
                angle = (s32)frand() % 360;
                center.x = 0.0f;
                center.y = 0.0f;
                center.z = 2390.0f;
                ofs = 0.0f;
                while (TRUE) {
                    target.x = dist * sin(M_PI * (angle + ofs) / 180.0) - player->unk0D8.x;
                    target.y = dist * cos(M_PI * (angle + ofs) / 180.0) - player->unk0D8.z;
                    target.z = player->unk070;
                    if (fn_1_FA6C(&center, &target, 0)) {
                        diff = (180.0 + 180.0 * (atan2(player->unk084.x - target.x, player->unk084.z - target.y) / M_PI)) - player->unk090.y;
                        if (diff < 0.0f) {
                            diff = 360.0f + diff;
                        }
                        if (diff >= 360.0f) {
                            diff -= 360.0f;
                        }
                        if (diff >= 180.0f) {
                            diff -= 360.0f;
                        }
                        diff = -diff;
                        if (((diff < 0.0f) ? -diff : diff) > 30.0f) {
                            break;
                        }
                    }
                    ofs += 30.0f;
                    if (ofs >= 360.0f) {
                        ofs = 0.0f;
                        dist -= 250.0f;
                    }
                }
                player->unk0D8.x = target.x;
                player->unk0D8.z = target.y;
                player->unk0D8.y = 0.0f;
                player->unk0D4 = 1;
                player->unk0E8 = 0;
                player->unk0EC = (s32)frand() % 10 + 60;
            }
            if (player->unk038 >= 90) {
                player->unk0C4 = 0;
            }
            target.x = player->unk0D8.x;
            target.y = player->unk0D8.z;
            target.z = 300.0f;
            if (fn_1_F860(&self, &target, 0) || player->unk0E8++ > 120) {
                player->unk0EE = 0;
                player->unk0D4 = 0;
            }
            break;
    }
    if (player->unk0C4) {
        player->unk0CA |= 0x200;
    }
    if (player->unk0E6 > 0) {
        player->unk0E6--;
        if (player->unk0C8 & 0x100) {
            player->unk0C8 &= ~0x100;
        }
    }
    else if (player->unk0C8 & 0x100) {
        player->unk0E6 = lbl_1_rodata_BF0[dif] + 8;
    }
    if (player->unk0C0) {
        player->unk0D8.x = player->unk084.x;
        player->unk0D8.z = player->unk084.z;
    }
    turn = 0.0f;
    if (player->unk0D8.x != player->unk084.x || player->unk0D8.z != player->unk084.z) {
        turn = (180.0 + 180.0 * (atan2(player->unk084.x - player->unk0D8.x, player->unk084.z - player->unk0D8.z) / M_PI)) - player->unk090.y;
        if (turn < 0.0f) {
            turn = 360.0f + turn;
        }
        if (turn >= 360.0f) {
            turn -= 360.0f;
        }
        if (turn >= 180.0f) {
            turn -= 360.0f;
        }
        turn = -turn;
    }
    angle = turn;
    angle = (angle > 60.0f) ? 60.0f : angle;
    angle = (angle < -60.0f) ? -60.0f : angle;
    dx = angle;
    stickY = player->unk0EC;
    dist = sqrtf(dx * dx + stickY * stickY);
    angle = 180.0 * (atan2(dx, stickY) / M_PI);
    dx = dist * sin(M_PI * angle / 180.0);
    stickY = dist * cos(M_PI * angle / 180.0);
    player->unk0CC = dx;
    player->unk0CE = stickY;
}

/* 328 insns: sword trails (unk0B4 at +120 deg, unk0B8 at +240 deg), 3 steps from the previous to the current pose */
void fn_1_7998(M519_PLAYER *player)
{
    HuVecF from;
    HuVecF to;
    HuVecF pos;
    float len;
    float t;
    s32 i;

    len = 80.0f - 2.0f * player->unk090.z;
    from.x = player->unk09C.x + len * sin(M_PI * (120.0f + player->unk0A8.y) / 180.0);
    from.z = player->unk09C.z + len * cos(M_PI * (120.0f + player->unk0A8.y) / 180.0);
    from.y = 100.0f + player->unk09C.y + player->unk0A8.z;
    to.x = player->unk084.x + len * sin(M_PI * (120.0f + player->unk090.y) / 180.0);
    to.z = player->unk084.z + len * cos(M_PI * (120.0f + player->unk090.y) / 180.0);
    to.y = 100.0f + player->unk084.y + player->unk090.z;
    for (i = 0; i < 3; i++) {
        t = 0.33333334f * i;
        pos.x = from.x + t * (to.x - from.x);
        pos.y = from.y + t * (to.y - from.y);
        pos.z = from.z + t * (to.z - from.z);
        fn_1_CD54(player->unk0B4, pos);
        fn_1_CFE8(player->unk0B4);
    }
    len = 80.0f + 2.0f * player->unk090.z;
    from.x = player->unk09C.x + len * sin(M_PI * (240.0f + player->unk0A8.y) / 180.0);
    from.z = player->unk09C.z + len * cos(M_PI * (240.0f + player->unk0A8.y) / 180.0);
    from.y = 100.0f + player->unk09C.y - player->unk0A8.z;
    to.x = player->unk084.x + len * sin(M_PI * (240.0f + player->unk090.y) / 180.0);
    to.z = player->unk084.z + len * cos(M_PI * (240.0f + player->unk090.y) / 180.0);
    to.y = 100.0f + player->unk084.y - player->unk090.z;
    for (i = 0; i < 3; i++) {
        t = 0.33333334f * i;
        pos.x = from.x + t * (to.x - from.x);
        pos.y = from.y + t * (to.y - from.y);
        pos.z = from.z + t * (to.z - from.z);
        fn_1_CD54(player->unk0B8, pos);
        fn_1_CFE8(player->unk0B8);
    }
}

/* 81 insns: signed turn (-180..180) from the player's facing to pos (inlined into fn_1_69BC) */
float fn_1_7EB8(M519_PLAYER *player, HuVecF *pos)
{
    float angle = 0.0f;

    if (pos->x != player->unk084.x || pos->z != player->unk084.z) {
        angle = (180.0 + 180.0 * (atan2(player->unk084.x - pos->x, player->unk084.z - pos->z) / M_PI)) - player->unk090.y;
        if (angle < 0.0f) {
            angle = 360.0f + angle;
        }
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        if (angle >= 180.0f) {
            angle -= 360.0f;
        }
        angle = -angle;
    }
    return angle;
}

/* 96 insns: xz distance to pos (inlined into fn_1_69BC) */
float fn_1_7FFC(M519_PLAYER *player, HuVecF *pos)
{
    float dx = pos->x - player->unk084.x;
    float dz = pos->z - player->unk084.z;
    float dist = sqrtf(dx * dx + dz * dz);

    return dist;
}

/* 3 insns */
void fn_1_817C(M519_PLAYER *player)
{
    player->unk000 = 2;
}

/* 87 insns: mode 2 */
void fn_1_8188(M519_PLAYER *player)
{
    fn_1_2FA0(player, 5, 1.0f);
    M519_OBJWAIT(50);
    fn_1_A828(lbl_1_bss_E8[player->unk008]);
    fn_1_F2DC(lbl_1_bss_20[player->unk006]);
    fn_1_98A0(player);
}

/* 91 insns: knock-back slide */
void fn_1_82E4(M519_PLAYER *player)
{
    float dx;
    float dz;
    s16 step;

    if (player->unk068 <= 0.0f) {
        return;
    }
    fn_1_FD7C(player->unk008, 2, 2);
    dx = player->unk068 * sin(M_PI * player->unk06C / 180.0);
    dz = player->unk068 * cos(M_PI * player->unk06C / 180.0);
    player->unk084.x += dx;
    player->unk084.z += dz;
    step = player->unk068 / 4.0f;
    player->unk068 = player->unk068 - step;
    if (step == 0) {
        player->unk068 = 0.0f;
    }
}

/* 572 insns: per-frame model update (camera, pose, attachments) */
void fn_1_8450(M519_PLAYER *player)
{
    Mtx mtx;
    HuVecF objPos;
    HuVecF rot;
    HuVecF pos;
    s32 seNo;
    OMCAMERAVIEW *camera;
    s16 no;

    no = player->unk006;
    if (player->unk04C) {
        camera = &lbl_1_bss_108[no];
        switch (no) {
            case 0:
                camera->center.x = player->unk084.x + 740.0 * sin(M_PI * player->unk090.y / 180.0);
                camera->center.z = player->unk084.z + 740.0 * cos(M_PI * player->unk090.y / 180.0);
                camera->center.y = 0.0f;
                camera->zoom = 1600.0f;
                camera->rot.y = 180.0f + player->unk090.y;
                camera->rot.x = -26.0f;
                camera->rot.z = 0.0f;
                break;
            case 1:
            case 2:
            case 3:
                camera->center.x = player->unk084.x + 500.0 * sin(M_PI * player->unk090.y / 180.0);
                camera->center.z = player->unk084.z + 500.0 * cos(M_PI * player->unk090.y / 180.0);
                camera->center.y = 0.0f;
                camera->zoom = 1200.0f;
                camera->rot.y = 180.0f + player->unk090.y;
                camera->rot.x = -22.5f;
                camera->rot.z = 0.0f;
                break;
        }
        omCameraViewSetMulti(lbl_1_rodata_10[no], camera);
    }
    fn_1_3290(player, player->unk090);
    fn_1_3138(player, player->unk084);
    switch (player->unk004) {
        case 0:
            Hu3DModelObjMtxGet(player->unk00A[0], lbl_1_data_14[0], mtx);
            objPos.x = mtx[0][3];
            objPos.y = mtx[1][3];
            objPos.z = mtx[2][3];
            Hu3DModelPosSet(player->unk00A[6], objPos.x, objPos.y, objPos.z);
            Hu3DModelPosSet(player->unk00A[7], objPos.x, objPos.y, objPos.z);
            Hu3DModelPosSet(player->unk00A[8], objPos.x, objPos.y, objPos.z);
            if ((player->unk034 / 5) * (4 - player->unk03A) > player->unk030) {
                seNo = HuAudFXPlayPan(0x710, lbl_1_rodata_18[player->unk004]);
                Hu3DMotionStartEndSet(player->unk00A[6], 40.0f * player->unk03A, 40.0f + 40.0f * player->unk03A);
                Hu3DMotionStartEndSet(player->unk00A[7], 40.0f * player->unk03A, 40.0f + 40.0f * player->unk03A);
                Hu3DMotionTimeSet(player->unk00A[6], 40.0f * player->unk03A);
                Hu3DModelAttrReset(player->unk00A[6], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(player->unk00A[6], HU3D_MOTATTR_PAUSE);
                Hu3DMotionTimeSet(player->unk00A[7], 40.0f * player->unk03A);
                Hu3DModelAttrReset(player->unk00A[7], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(player->unk00A[7], HU3D_MOTATTR_PAUSE);
                player->unk03A++;
            }
            break;
        case 1:
            Hu3DModelObjMtxGet(player->unk00A[0], lbl_1_data_14[1], mtx);
            objPos.x = mtx[0][3];
            objPos.y = mtx[1][3];
            objPos.z = mtx[2][3];
            Hu3DModelPosSet(player->unk00A[4], objPos.x, objPos.y, objPos.z);
            if (player->unk000 == 1) {
                Hu3DModelAttrReset(player->unk00A[3], HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrSet(player->unk00A[3], HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

/* 36 insns: face the solo player (lbl_1_bss_F8[0]) */
void fn_1_8D40(M519_PLAYER *player)
{
    M519_PLAYER *solo = lbl_1_bss_F8[0];

    player->unk074 = 180.0 + 180.0 * (atan2(player->unk084.x - solo->unk084.x, player->unk084.z - solo->unk084.z) / M_PI);
}

/* 28 insns: charge level 0..2 of the held button (no caller in the reference) */
s32 fn_1_8DD0(M519_PLAYER *player)
{
    if (player->unk038 > 0) {
        if (player->unk038 >= 90) {
            return 2;
        }
        if (player->unk038 > 40) {
            return 1;
        }
    }
    else if (player->unk036 > 0) {
        if (player->unk036 >= 90) {
            return 2;
        }
        if (player->unk036 > 40) {
            return 1;
        }
    }
    return 0;
}

/* 476 insns: attack buttons (0x100 A / 0x200 B; hold 90 frames to charge) */
void fn_1_8E40(M519_PLAYER *player)
{
    HuVecF pos;
    HuVecF rot;
    s16 cnt;

    if (player->unk02E > 0) {
        if (--player->unk02E > 0) {
            return;
        }
    }
    switch (player->unk004) {
        case 0:
            pos = player->unk084;
            rot = player->unk090;
            if ((player->unk0C8 & 0x100) && !(player->unk0CA & 0x200)) {
                Hu3DModelAttrReset(player->unk00A[1], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(player->unk00A[1], 0.0f);
                pos.y += 170.0f;
                fn_1_A9F0(0, pos, rot, player->unk006);
                player->unk02E = 8;
                player->unk036 = 0;
                player->unk038 = 0;
                fn_1_FD7C(player->unk008, 0, 3);
            }
            else if ((player->unk0CA & 0x100) && !(player->unk0CA & 0x200)) {
                player->unk038 = 0;
                if (player->unk036++ == 0) {
                    if (player->unk0F0 != -1) {
                        HuAudFXStop(player->unk0F0);
                    }
                    player->unk0F0 = HuAudFXPlayPan(0x70D, lbl_1_rodata_18[player->unk004]);
                    Hu3DModelAttrReset(player->unk00A[3], HU3D_ATTR_DISPOFF);
                    Hu3DMotionShapeStartEndSet(player->unk00A[3], 0.0f, 60.0f);
                    Hu3DMotionTimeSet(player->unk00A[3], 0.0f);
                    Hu3DModelAttrSet(player->unk00A[3], HU3D_MOTATTR_LOOP);
                }
                else if (player->unk036 == 40) {
                    Hu3DMotionShapeStartEndSet(player->unk00A[3], 40.0f, 60.0f);
                    Hu3DMotionTimeSet(player->unk00A[3], 0.0f);
                    Hu3DModelAttrSet(player->unk00A[3], HU3D_MOTATTR_LOOP);
                }
                if (player->unk036 >= 40 && player->unk036 % 5 == 0) {
                    fn_1_FD7C(player->unk008, 1, 3);
                }
            }
            else if (player->unk036 > 0) {
                HuAudFXStop(player->unk0F0);
                player->unk0F0 = -1;
                Hu3DModelAttrSet(player->unk00A[3], HU3D_ATTR_DISPOFF);
                cnt = player->unk036;
                player->unk036 = 0;
                if (cnt < 90) {
                    break;
                }
                Hu3DModelAttrReset(player->unk00A[2], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(player->unk00A[2], 0.0f);
                pos.y += 170.0f;
                fn_1_A9F0(1, pos, rot, player->unk006);
                player->unk02E = 8;
                fn_1_FD7C(player->unk008, 2, 30);
            }
            pos = player->unk084;
            rot = player->unk090;
            if ((player->unk0C8 & 0x200) && !(player->unk0CA & 0x100)) {
                fn_1_A9F0(2, pos, rot, player->unk006);
                player->unk02E = 32;
                player->unk038 = 0;
                player->unk036 = 0;
                fn_1_FD7C(player->unk008, 0, 3);
            }
            else if ((player->unk0CA & 0x200) && !(player->unk0CA & 0x100)) {
                player->unk036 = 0;
                if (player->unk038++ == 0) {
                    if (player->unk0F0 != -1) {
                        HuAudFXStop(player->unk0F0);
                    }
                    player->unk0F0 = HuAudFXPlayPan(0x70D, lbl_1_rodata_18[player->unk004]);
                    Hu3DModelAttrReset(player->unk00A[4], HU3D_ATTR_DISPOFF);
                    Hu3DMotionStartEndSet(player->unk00A[4], 0.0f, 60.0f);
                    Hu3DMotionTimeSet(player->unk00A[4], 0.0f);
                    Hu3DModelAttrSet(player->unk00A[4], HU3D_MOTATTR_LOOP);
                }
                else if (player->unk038 == 30) {
                    Hu3DMotionStartEndSet(player->unk00A[4], 30.0f, 60.0f);
                    Hu3DMotionTimeSet(player->unk00A[4], 0.0f);
                    Hu3DModelAttrSet(player->unk00A[4], HU3D_MOTATTR_LOOP);
                }
                if (player->unk038 >= 30 && player->unk038 % 5 == 0) {
                    fn_1_FD7C(player->unk008, 1, 3);
                }
            }
            else if (player->unk038 > 0) {
                HuAudFXStop(player->unk0F0);
                player->unk0F0 = -1;
                Hu3DModelAttrSet(player->unk00A[4], HU3D_ATTR_DISPOFF);
                cnt = player->unk038;
                player->unk038 = 0;
                if (cnt < 90) {
                    break;
                }
                fn_1_A9F0(3, pos, rot, player->unk006);
                player->unk02E = 8;
                fn_1_FD7C(player->unk008, 2, 30);
            }
            break;
        case 1:
            pos = player->unk084;
            rot = player->unk090;
            if (player->unk0C8 & 0x100) {
                Hu3DModelAttrReset(player->unk00A[1], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(player->unk00A[1], 0.0f);
                pos.y += 170.0f;
                fn_1_A9F0(4, pos, rot, player->unk006);
                player->unk02E = 8;
                fn_1_FD7C(player->unk008, 0, 3);
            }
            break;
    }
}

/* 84 insns: push out of the other players */
void fn_1_95B0(M519_PLAYER *player)
{
    HuVecF self;
    HuVecF other;
    M519_PLAYER *work;
    s32 i;

    self.x = player->unk084.x;
    self.y = player->unk084.z;
    self.z = player->unk070;
    player->unk0C0 = 0;
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_F8[i];
        if (work == player) {
            continue;
        }
        if (work->unk000 == 3) {
            continue;
        }
        other.x = work->unk084.x;
        other.y = work->unk084.z;
        other.z = work->unk070;
        if (fn_1_F860(&self, &other, 1)) {
            player->unk090.y = fn_1_FC78(player->unk090.y, 180.0 * (atan2(self.x - player->unk084.x, self.y - player->unk084.z) / M_PI), 0.0009f * player->unk050);
            player->unk084.x = self.x;
            player->unk084.z = self.y;
            if (player->unk004 == work->unk004) {
                player->unk0C0 = 1;
            }
        }
    }
}

/* 104 insns: push out of the stage obstacles and keep inside the 2390 ring */
void fn_1_9700(M519_PLAYER *player)
{
    HuVecF self;
    HuVecF other;
    float rotY;
    M519_STAGEOBJ *obj;
    s32 i;

    self.x = player->unk084.x;
    self.y = player->unk084.z;
    self.z = player->unk070;
    for (i = 0; i < 12; i++) {
        obj = lbl_1_bss_178->unk014[i];
        if (obj == NULL) {
            continue;
        }
        if (obj->unk000 == 3 || obj->unk000 == 1) {
            other.x = obj->unk014.x;
            other.y = obj->unk014.z;
            other.z = obj->unk02C;
            if (fn_1_F860(&self, &other, 1)) {
                rotY = player->unk090.y;
                player->unk090.y = fn_1_FC78(player->unk090.y, 180.0 * (atan2(self.x - player->unk084.x, self.y - player->unk084.z) / M_PI), 0.0009f * player->unk050);
                player->unk084.x = self.x;
                player->unk084.z = self.y;
            }
        }
    }
    other.x = 0.0f;
    other.y = 0.0f;
    other.z = 2390.0f;
    if (fn_1_FA6C(&self, &other, 1)) {
        player->unk084.x = self.x;
        player->unk084.z = self.y;
    }
}

/* 3 insns */
void fn_1_98A0(M519_PLAYER *player)
{
    player->unk000 = 3;
}

/* 188 insns: mode 3 (out: fade away, then idle) */
void fn_1_98AC(M519_PLAYER *player)
{
    static const s32 lbl_1_rodata_C48[2] = { 0x711, 0x713 };
    float t;
    s32 i;

    HuAudFXPlayPan(lbl_1_rodata_C48[player->unk004], lbl_1_rodata_18[player->unk004]);
    fn_1_FD7C(player->unk008, 1, 90);
    switch (player->unk004) {
        case 0:
            Hu3DModelAttrSet(player->unk00A[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[6], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[7], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[8], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[5], HU3D_ATTR_DISPOFF);
            break;
        case 1:
            Hu3DModelAttrSet(player->unk00A[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(player->unk00A[4], HU3D_ATTR_DISPOFF);
            break;
    }
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(player->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
    for (i = 1; i <= 60; i++) {
        t = 0.016666668f * i;
        Hu3DModelTPLvlSet(player->unk00A[0], 1.0f - t);
        if (player->unk004 == 0) {
            Hu3DModelTPLvlSet(player->unk00A[5], 1.0f - t);
        }
        fn_1_8450(player);
        M519_OBJWAIT(1);
    }
    fn_1_3098(player);
    while (TRUE) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_9B9C(M519_PLAYER *player)
{
    player->unk000 = 4;
}

/* 304 insns: mode 4 (drop back in from 1000 above, then idle) */
void fn_1_9BA8(M519_PLAYER *player)
{
    HuVecF pos;
    float t;
    float height;
    s32 i;

    pos = player->unk084;
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[6], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[7], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(player->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
    HuAudFXPlay(0x709);
    for (i = 1; i <= 100; i++) {
        t = 0.01f * (i + 1);
        height = cos(M_PI * (90.0f * t) / 180.0);
        Hu3DModelTPLvlSet(player->unk00A[0], t);
        Hu3DModelTPLvlSet(player->unk00A[5], t);
        pos.y = 1000.0f * height;
        fn_1_3138(player, pos);
        fn_1_8450(player);
        M519_OBJWAIT(1);
    }
    Hu3DModelTPLvlSet(player->unk00A[0], 1.0f);
    Hu3DModelTPLvlSet(player->unk00A[5], 1.0f);
    Hu3DModelAttrSet(player->unk00A[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
    HuAudFXPlay(0x720);
    fn_1_2FA0(player, 6, 1.0f);
    fn_1_FD7C(player->unk008, 2, 30);
    M519_OBJWAIT(90);
    fn_1_2FA0(player, 0, 1.0f);
    player->unk000 = 0;
}

/* 91 insns: lbl_1_data_20[9], player fade-in */
void fn_1_A068(M519_PLAYER *player)
{
    float tpLvl;
    s32 i;

    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(player->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
    for (i = 0; i < 90; i++) {
        tpLvl = (1.0 / 90) * i;
        Hu3DModelTPLvlSet(player->unk00A[0], tpLvl);
        Hu3DModelTPLvlSet(player->unk00A[2], tpLvl);
        M519_OBJWAIT(1);
    }
    Hu3DModelTPLvlSet(player->unk00A[0], 1.0f);
    Hu3DModelTPLvlSet(player->unk00A[2], 1.0f);
    Hu3DModelAttrSet(player->unk00A[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrReset(player->unk00A[0], HU3D_ATTR_ZWRITE_OFF);
    player->unk000 = 0;
}

/* 12 insns */
s32 fn_1_A1D4(M519_PLAYER *player)
{
    s32 result;

    if (player->unk030 == 0) {
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

/* 130 insns */
static const s32 lbl_1_rodata_C60[13][6] = {
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C0001, 0x008C0006, 0x008C0007 },
    { 0x00330000, 0x00330003, 0x00330004, 0x00330001, 0x00330006, 0x00330007 },
    { 0x00B70000, 0x00B70003, 0x00B70004, 0x00B70001, 0x00B70006, 0x00B70007 },
    { 0x00ED0000, 0x00ED0003, 0x00ED0004, 0x00ED0001, 0x00ED0006, 0x00ED0007 },
    { 0x00E60000, 0x00E60003, 0x00E60004, 0x00E60001, 0x00E60006, 0x00E60007 },
    { 0x00170000, 0x00170003, 0x00170004, 0x00170001, 0x00170006, 0x00170007 },
    { 0x00E00000, 0x00E00003, 0x00E00004, 0x00E00001, 0x00E00006, 0x00E00007 },
    { 0x002D0000, 0x002D0003, 0x002D0004, 0x002D0001, 0x002D0006, 0x002D0007 },
    { 0x00C90000, 0x00C90003, 0x00C90004, 0x00C90001, 0x00C90006, 0x00C90007 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00001, 0x00B00006, 0x00B00007 },
};

static const s32 lbl_1_rodata_D98[13] = {
    0x004D005D, 0x004D005E, 0x004D005F, 0x004D0060, 0x004D0061, 0x004D0062, 0x004D0063,
    0x004D0064, 0x004D0065, 0x004D0066, 0x004D0067, 0x004D0068, 0x004D0069,
};

M519_CHAR *fn_1_A204(s16 team, s16 playerNo)
{
    M519_CHAR *chr;
    s32 i;

    chr = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_CHAR), HU_MEMNUM_OVL);
    chr->unk004 = team;
    chr->unk006 = playerNo;
    chr->unk00C = GwPlayerConf[playerNo].type;
    chr->unk00A = GwPlayerConf[playerNo].charNo;
    chr->unk010 = GwPlayerConf[playerNo].dif;
    chr->unk012 = GwPlayerConf[playerNo].padNo;
    chr->unk000 = 0;
    chr->unk002 = 0;
    chr->unk014[0] = CharModelCreate(chr->unk00A, 2);
    chr->unk014[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_D98[chr->unk00A], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(chr->unk014[1], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(chr->unk014[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(chr->unk014[1], HU3D_ATTR_ZWRITE_OFF);
    Hu3DModelAttrSet(chr->unk014[0], HU3D_ATTR_ZWRITE_OFF);
    Hu3DModelAttrSet(chr->unk014[0], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(chr->unk014[0], 2);
    Hu3DModelLayerSet(chr->unk014[1], 2);
    for (i = 0; i < 6; i++) {
        chr->unk018[i] = CharMotionCreate(chr->unk00A, lbl_1_rodata_C60[chr->unk00A][i]);
    }
    CharMotionDataClose(chr->unk00A);
    Hu3DMotionSet(chr->unk014[0], chr->unk018[0]);
    Hu3DModelAttrSet(chr->unk014[0], HU3D_MOTATTR_PAUSE);
    chr->unk03C = HuPrcChildCreate(fn_1_A40C, 0x1000, 0x1000, 0, HuPrcCurrentGet());
    chr->unk03C->property = chr;
    return chr;
}

/* 16 insns */
void fn_1_A40C(void)
{
    M519_CHAR *chr = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_48[chr->unk000](chr);
    }
}

/* 33 insns */
void fn_1_A44C(M519_CHAR *chr, HuVecF pos)
{
    s32 i;

    chr->unk024 = pos;
    for (i = 0; i < 2; i++) {
        Hu3DModelPosSet(chr->unk014[i], pos.x, pos.y, pos.z);
    }
}

/* 7 insns */
HuVecF fn_1_A4D0(M519_CHAR *chr)
{
    return chr->unk024;
}

/* 33 insns */
void fn_1_A4EC(M519_CHAR *chr, HuVecF rot)
{
    s32 i;

    chr->unk030 = rot;
    for (i = 0; i < 2; i++) {
        Hu3DModelRotSet(chr->unk014[i], rot.x, rot.y, rot.z);
    }
}

/* 7 insns */
HuVecF fn_1_A570(M519_CHAR *chr)
{
    return chr->unk030;
}

/* 3 insns */
void fn_1_A58C(M519_CHAR *chr)
{
    chr->unk000 = 0;
}

/* 36 insns: lbl_1_data_48[0] */
void fn_1_A598(M519_CHAR *chr)
{
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_A628(M519_CHAR *chr)
{
    chr->unk000 = 1;
}

/* 33 insns: lbl_1_data_48[1] */
void fn_1_A634(M519_CHAR *chr)
{
    M519_PLAYER *player;

    Hu3DModelAttrSet(chr->unk014[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(chr->unk014[0], HU3D_ATTR_DISPOFF);
    Hu3DModelTPLvlSet(chr->unk014[0], 1.0f);
    player = lbl_1_bss_F8[chr->unk008];
    Hu3DModelHookReset(player->unk00A[0]);
    chr->unk000 = 0;
}

/* 3 insns */
void fn_1_A6B8(M519_CHAR *chr)
{
    chr->unk000 = 2;
}

/* 43 insns: lbl_1_data_48[2] */
void fn_1_A6C4(M519_CHAR *chr)
{
    Hu3DMotionShiftSet(chr->unk014[0], chr->unk018[4], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_A770(M519_CHAR *chr)
{
    chr->unk000 = 3;
}

/* 43 insns: lbl_1_data_48[3] */
void fn_1_A77C(M519_CHAR *chr)
{
    Hu3DMotionShiftSet(chr->unk014[0], chr->unk018[5], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_A828(M519_CHAR *chr)
{
    chr->unk000 = 4;
}

/* 111 insns: lbl_1_data_48[4], fade out */
void fn_1_A834(M519_CHAR *chr)
{
    float t;
    s32 i;
    s32 j;

    Hu3DModelAttrReset(chr->unk014[1], HU3D_ATTR_NOCULL);
    Hu3DModelAttrReset(chr->unk014[0], HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(chr->unk014[1], HU3D_ATTR_ZWRITE_OFF);
    Hu3DModelAttrSet(chr->unk014[0], HU3D_ATTR_ZWRITE_OFF);
    for (i = 0; i < 90; i++) {
        t = (1.0 / 90) * i;
        for (j = 0; j < 2; j++) {
            Hu3DModelTPLvlSet(chr->unk014[j], 1.0f - t);
        }
        M519_OBJWAIT(1);
    }
    for (j = 0; j < 2; j++) {
        Hu3DModelAttrSet(chr->unk014[j], HU3D_ATTR_DISPOFF);
    }
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 84 insns */
s32 fn_1_A9F0(s16 type, HuVecF pos, HuVecF rot, s16 owner)
{
    M519_ITEM *item;
    s32 i;

    for (i = 0; i < 44; i++) {
        item = lbl_1_bss_38[i];
        if (item != NULL && item->unk000 == 0 && item->unk002 == 0 && item->unk00E == type) {
            item->unk018 = owner;
            item->unk00C = lbl_1_bss_C++ % 32000;
            fn_1_AE24(item, pos);
            fn_1_AEC4(item, rot);
            fn_1_B0B0(item);
            return 1;
        }
    }
    return 0;
}

/* 169 insns */
static const s32 lbl_1_rodata_DD4[5][2] = {
    { 0x004D0035, 0x004D0036 },
    { 0x004D0038, 0x004D0039 },
    { 0x004D003D, 0x004D0039 },
    { 0x004D003E, 0x004D0039 },
    { 0x004D003B, 0x004D003C },
};

static const M519_ITEMPARAM lbl_1_rodata_DFC[5] = {
    { 73.333336f, 12.0f, 12.0f, 40, 1, 3, 30, 1 },
    { 76.666664f, 80.0f, 80.0f, 120, 1, 15, 200, 0 },
    { 0.0f, 500.0f, 200.0f, 15, 15, 1, 200, 0 },
    { 0.0f, 1000.0f, 200.0f, 30, 30, 3, 200, 0 },
    { 73.333336f, 12.0f, 12.0f, 25, 1, 1, 10, 1 },
};

M519_ITEM *fn_1_AB40(s16 type)
{
    M519_ITEM *item;
    s32 i;

    item = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_ITEM), HU_MEMNUM_OVL);
    item->unk00C = 0;
    item->unk00E = type;
    item->unk004 = 0;
    item->unk018 = -1;
    item->unk044 = 1.0f;
    item->unk010 = lbl_1_rodata_DFC[type].unk010;
    item->unk012 = lbl_1_rodata_DFC[type].unk012;
    item->unk040 = lbl_1_rodata_DFC[type].unk004;
    item->unk03C = lbl_1_rodata_DFC[type].unk008;
    item->unk048 = lbl_1_rodata_DFC[type].unk00C;
    item->unk04A = lbl_1_rodata_DFC[type].unk00E;
    item->unk01C = lbl_1_rodata_DFC[type].unk000;
    item->unk008 = lbl_1_rodata_DFC[type].unk014;
    item->unk020 = 0.0f;
    item->unk024.x = 0.0f;
    item->unk024.y = 0.0f;
    item->unk024.z = 0.0f;
    item->unk030.x = 0.0f;
    item->unk030.y = 0.0f;
    item->unk030.z = 0.0f;
    item->unk000 = 0;
    item->unk002 = 0;
    for (i = 0; i < 2; i++) {
        item->unk014[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_DD4[type][i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(item->unk014[i], HU3D_ATTR_NOCULL);
        Hu3DModelAttrSet(item->unk014[i], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(item->unk014[i], 2);
    }
    item->unk04C = HuPrcChildCreate(fn_1_ADE4, 0x900, 0x2000, 0, HuPrcCurrentGet());
    item->unk04C->property = item;
    return item;
}

/* 16 insns */
void fn_1_ADE4(void)
{
    M519_ITEM *item = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_5C[item->unk000](item);
    }
}

/* 33 insns */
void fn_1_AE24(M519_ITEM *item, HuVecF pos)
{
    s32 i;

    item->unk024 = pos;
    for (i = 0; i < 2; i++) {
        Hu3DModelPosSet(item->unk014[i], pos.x, pos.y, pos.z);
    }
}

/* 7 insns */
HuVecF fn_1_AEA8(M519_ITEM *item)
{
    return item->unk024;
}

/* 33 insns */
void fn_1_AEC4(M519_ITEM *item, HuVecF rot)
{
    s32 i;

    item->unk030 = rot;
    for (i = 0; i < 2; i++) {
        Hu3DModelRotSet(item->unk014[i], rot.x, rot.y, rot.z);
    }
}

/* 7 insns */
HuVecF fn_1_AF48(M519_ITEM *item)
{
    return item->unk030;
}

/* 40 insns */
static const HuVecF lbl_1_rodata_E74 = { 0.0f, 0.0f, 0.0f };

/* raw=20 masked=0 (r30/r31 swap). Calling an already-defined external
 * "unk000 = 0" setter instead of the store (e.g. fn_1_A58C through a cast)
 * scores raw=0; a static inline setter does not. Left as the plain store. */
void fn_1_AF64(M519_ITEM *item)
{
    fn_1_AE24(item, lbl_1_rodata_E74);
    item->unk000 = 0;
}

/* 43 insns: lbl_1_data_5C[0] */
void fn_1_B004(M519_ITEM *item)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        Hu3DModelAttrSet(item->unk014[i], HU3D_ATTR_DISPOFF);
    }
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_B0B0(M519_ITEM *item)
{
    item->unk000 = 1;
}

/* 404 insns: lbl_1_data_5C[1], flight */
static const s32 lbl_1_rodata_E80[5] = { 0x70C, 0x70E, 0x70F, 0x70F, 0x712 };

void fn_1_B0BC(M519_ITEM *item)
{
    HuVecF pos;
    float dx;
    float dz;
    float scale;
    s32 hit;
    s32 i;
    s16 t;

    HuAudFXPlayPan(lbl_1_rodata_E80[item->unk00E], lbl_1_rodata_18[lbl_1_bss_F8[item->unk018]->unk004]);
    Hu3DModelAttrReset(item->unk014[0], HU3D_ATTR_DISPOFF);
    switch (item->unk00E) {
        case 1:
            Hu3DModelAttrSet(item->unk014[0], HU3D_MOTATTR_LOOP);
            break;
        case 0:
        case 2:
        case 4:
            Hu3DModelAttrReset(item->unk014[0], HU3D_MOTATTR_LOOP);
            break;
    }
    Hu3DMotionShapeStartEndSet(item->unk014[0], 0.0f, Hu3DMotionMaxTimeGet(item->unk014[0]));
    Hu3DMotionTimeSet(item->unk014[0], 0.0f);
    item->unk004 = 1;
    hit = 0;
    scale = 0.0f;
    for (i = 0; i < item->unk048; i++) {
        if (i < 10) {
            scale += 0.1f;
        }
        if (i > item->unk048 - 10) {
            scale -= 0.1f;
        }
        item->unk020 = item->unk01C;
        dx = item->unk020 * sin(M_PI * item->unk030.y / 180.0);
        dz = item->unk020 * cos(M_PI * item->unk030.y / 180.0);
        if (item->unk00E != 3 && item->unk00E != 2) {
            Hu3DModelScaleSet(item->unk014[0], 1.0f, 1.0f, scale);
        }
        pos = item->unk024;
        pos.x += dx;
        pos.z += dz;
        fn_1_AE24(item, pos);
        t = (i >= item->unk04A) ? item->unk04A : i;
        item->unk044 = item->unk03C + (item->unk040 - item->unk03C) * sin(M_PI * (90.0f * (1.0f / item->unk04A) * t) / 180.0);
        if (item->unk00E == 0 || item->unk00E == 1 || item->unk00E == 4) {
            if (fn_1_BECC(item)) {
                hit = 1;
            }
            if (fn_1_B9BC(item)) {
                hit = 1;
            }
            if (fn_1_B70C(item) && item->unk00E != 1) {
                hit = 1;
            }
            if (fn_1_BAC8(item) && item->unk00E != 1) {
                hit = 1;
            }
        } else {
            fn_1_BECC(item);
            fn_1_B70C(item);
            fn_1_BAC8(item);
        }
        if (hit) {
            break;
        }
        M519_OBJWAIT(1);
    }
    item->unk004 = 0;
    if (item->unk00E == 3 || item->unk00E == 2) {
        M519_OBJWAIT(20);
    }
    if (hit) {
        Hu3DModelAttrSet(item->unk014[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(item->unk014[1], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(item->unk014[1], 0.0f);
        M519_OBJWAIT(Hu3DMotionMaxTimeGet(item->unk014[1]));
        Hu3DModelAttrReset(item->unk014[1], HU3D_ATTR_DISPOFF);
    }
    fn_1_AE24(item, lbl_1_rodata_E74);
    item->unk000 = 0;
}

/* 172 insns: item vs players */
static const s32 lbl_1_rodata_E98[2] = { 0x714, 0x715 };

s32 fn_1_B70C(M519_ITEM *item)
{
    M519_PLAYER *owner;
    M519_PLAYER *player;
    HuVecF a;
    HuVecF b;
    float dx;
    float dz;
    s32 i;

    if (item->unk018 == -1) {
        return 0;
    }
    owner = lbl_1_bss_F8[item->unk018];
    a.x = item->unk024.x;
    a.y = item->unk024.z;
    a.z = item->unk044;
    for (i = 0; i < 4; i++) {
        player = lbl_1_bss_F8[i];
        if (player == owner || player->unk000 == 3) {
            continue;
        }
        b.x = player->unk084.x;
        b.y = player->unk084.z;
        b.z = player->unk070;
        if (!fn_1_F860(&a, &b, 1)) {
            continue;
        }
        HuAudFXPlay(lbl_1_rodata_E98[player->unk004]);
        if (player->unk004 != owner->unk004 && player->unk03C != item->unk00C && !lbl_1_bss_8) {
            if ((player->unk030 -= item->unk010) < 0) {
                player->unk030 = 0;
            }
        }
        player->unk03C = item->unk00C;
        if (item->unk008) {
            item->unk024.x = a.x;
            item->unk024.z = a.y;
            fn_1_AE24(item, item->unk024);
        }
        if (player->unk000 == 1) {
            if (0.0f == item->unk020) {
                dx = player->unk084.x - item->unk024.x;
                dz = player->unk084.z - item->unk024.z;
                item->unk030.y = 180.0 * (atan2(dx, dz) / M_PI);
            }
            player->unk068 = item->unk012;
            player->unk06C = item->unk030.y;
        }
        return 1;
    }
    return 0;
}

/* 67 insns: item vs arena wall */
s32 fn_1_B9BC(M519_ITEM *item)
{
    HuVecF a;
    HuVecF b;

    a.x = item->unk024.x;
    a.y = item->unk024.z;
    a.z = item->unk044;
    b.x = 0.0f;
    b.y = 0.0f;
    b.z = 2390.0f;
    if (fn_1_FA6C(&a, &b, 1)) {
        item->unk024.x = a.x;
        item->unk024.z = a.y;
        fn_1_AE24(item, item->unk024);
        return 1;
    }
    return 0;
}

/* 257 insns: item vs blocks */
static const s32 lbl_1_rodata_EA0[5][2] = {
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 1, 1 },
    { 0, 1 },
};

static const s32 lbl_1_rodata_EC8[2] = { 0x71B, 0x71C };

s32 fn_1_BAC8(M519_ITEM *item)
{
    M519_STAGEOBJ *block;
    M519_PLAYER *owner;
    HuVecF a;
    HuVecF b;
    HuVecF blockPos;
    float angle;
    float dir;
    float rotY;
    s32 i;

    a.x = item->unk024.x;
    a.y = item->unk024.z;
    a.z = item->unk044;
    for (i = 0; i < 12; i++) {
        block = lbl_1_bss_178->unk014[i];
        if (block == NULL || block->unk000 != 3 || block->unk00C <= 0 || block->unk00E == item->unk00C) {
            continue;
        }
        b.x = block->unk014.x;
        b.y = block->unk014.z;
        b.z = block->unk02C;
        if (!fn_1_F860(&a, &b, 1)) {
            continue;
        }
        owner = lbl_1_bss_F8[item->unk018];
        blockPos = block->unk014;
        angle = 0.0f;
        if (blockPos.x != owner->unk084.x || blockPos.z != owner->unk084.z) {
            angle = 180.0 + 180.0 * (atan2(owner->unk084.x - blockPos.x, owner->unk084.z - blockPos.z) / M_PI) - owner->unk090.y;
            if (angle < 0.0f) {
                angle = 360.0f + angle;
            }
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            if (angle >= 180.0f) {
                angle -= 360.0f;
            }
            angle = -angle;
        }
        dir = angle;
        rotY = dir;
        HuAudFXPlayVolPan(lbl_1_rodata_EC8[0], fn_1_FE20(1, item->unk024), fn_1_10244(1, item->unk024));
        HuAudFXPlayVolPan(lbl_1_rodata_EC8[1], fn_1_FE20(14, item->unk024), fn_1_10244(14, item->unk024));
        if (lbl_1_rodata_EA0[item->unk00E][block->unk004] && block->unk00E != item->unk00C) {
            if ((block->unk00C -= item->unk010) < 0) {
                block->unk00C = 0;
            }
        }
        block->unk00E = item->unk00C;
        block->unk010 = item->unk018;
        if (item->unk008) {
            item->unk024.x = a.x;
            item->unk024.z = a.y;
            fn_1_AE24(item, item->unk024);
        }
        return 1;
    }
    return 0;
}

/* 99 insns: item vs items */
s32 fn_1_BECC(M519_ITEM *item)
{
    M519_ITEM *other;
    HuVecF a;
    HuVecF b;
    s32 i;

    if (item->unk00E == 1) {
        return 0;
    }
    a.x = item->unk024.x;
    a.y = item->unk024.z;
    a.z = item->unk044;
    for (i = 0; i < 44; i++) {
        other = lbl_1_bss_38[i];
        if (other == NULL || item->unk000 != 1 || !other->unk004 || other->unk018 == item->unk018 || other == item) {
            continue;
        }
        b.x = other->unk024.x;
        b.y = other->unk024.z;
        b.z = other->unk044;
        if (!fn_1_F860(&a, &b, 1)) {
            continue;
        }
        if (item->unk008) {
            item->unk024.x = a.x;
            item->unk024.z = a.y;
            fn_1_AE24(item, item->unk024);
        }
        return 1;
    }
    return 0;
}

/* 124 insns */
static const s32 lbl_1_rodata_ED0[3][6] = {
    { 0x004D0007, 0x004D0008, 0x004D0009, 0x004D000A, 0x004D000B, 0x004D000C },
    { 0x004D0011, 0x004D0012, 0x004D0013, 0x004D0014, 0x004D0015, 0x004D0016 },
    { 0x004D001B, 0x004D001C, 0x004D001D, 0x004D001E, 0x004D001F, 0x004D0020 },
};

static const s16 lbl_1_rodata_F18[2] = { 140, 100 };

M519_STAGEOBJ *fn_1_C058(s16 type)
{
    M519_STAGEOBJ *block;
    s32 i;

    block = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_STAGEOBJ), HU_MEMNUM_OVL);
    block->unk004 = type;
    block->unk00E = -1;
    block->unk02C = lbl_1_rodata_F18[type];
    block->unk00C = 1;
    block->unk014.x = 0.0f;
    block->unk014.y = 0.0f;
    block->unk014.z = 0.0f;
    block->unk020.x = 0.0f;
    block->unk020.y = 0.0f;
    block->unk020.z = 0.0f;
    block->unk030 = 0;
    block->unk010 = -1;
    block->unk000 = 0;
    block->unk002 = 0;
    for (i = 0; i < 3; i++) {
        block->unk006[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_ED0[lbl_1_bss_30][i + type * 3], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(block->unk006[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(block->unk006[i], HU3D_ATTR_NOCULL);
        Hu3DModelLayerSet(block->unk006[i], 2);
    }
    block->unk034 = HuPrcChildCreate(fn_1_C248, 0x900, 0x2000, 0, HuPrcCurrentGet());
    block->unk034->property = block;
    return block;
}

/* 16 insns */
void fn_1_C248(void)
{
    M519_STAGEOBJ *block = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_64[block->unk000](block);
    }
}

/* 33 insns */
void fn_1_C288(M519_STAGEOBJ *block, HuVecF pos)
{
    s32 i;

    block->unk014 = pos;
    for (i = 0; i < 3; i++) {
        Hu3DModelPosSet(block->unk006[i], pos.x, pos.y, pos.z);
    }
}

/* 7 insns */
HuVecF fn_1_C30C(M519_STAGEOBJ *block)
{
    return block->unk014;
}

/* 33 insns */
void fn_1_C328(M519_STAGEOBJ *block, HuVecF rot)
{
    s32 i;

    block->unk020 = rot;
    for (i = 0; i < 3; i++) {
        Hu3DModelRotSet(block->unk006[i], rot.x, rot.y, rot.z);
    }
}

/* 7 insns */
HuVecF fn_1_C3AC(M519_STAGEOBJ *block)
{
    return block->unk020;
}

/* 3 insns */
void fn_1_C3C8(M519_STAGEOBJ *block)
{
    block->unk000 = 0;
}

/* 36 insns: lbl_1_data_64[0] */
void fn_1_C3D4(M519_STAGEOBJ *block)
{
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_C464(M519_STAGEOBJ *block)
{
    block->unk000 = 3;
}

/* 53 insns: lbl_1_data_64[3], standing */
void fn_1_C470(M519_STAGEOBJ *block)
{
    Hu3DModelAttrReset(block->unk006[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(block->unk006[0], 0.0f);
    Hu3DModelAttrSet(block->unk006[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[2], HU3D_ATTR_DISPOFF);
    while (1) {
        if (block->unk00C <= 0) {
            fn_1_C788(block, 1);
        }
        M519_OBJWAIT(1);
    }
}

/* 11 insns */
static const s16 lbl_1_rodata_F1C[2] = { 15, 10 };

void fn_1_C544(M519_STAGEOBJ *block)
{
    block->unk00C = lbl_1_rodata_F1C[block->unk004];
    block->unk000 = 1;
}

/* 134 insns: lbl_1_data_64[1], break */
static const s32 lbl_1_rodata_F20[2] = { 0x719, 0x71A };

void fn_1_C570(M519_STAGEOBJ *block)
{
    M519_PLAYER *player;

    if (block->unk010 != -1) {
        player = lbl_1_bss_F8[block->unk010];
        HuAudFXPlayVolPan(lbl_1_rodata_F20[0], fn_1_FE20(1, block->unk014), fn_1_10244(1, block->unk014));
        HuAudFXPlayVolPan(lbl_1_rodata_F20[1], fn_1_FE20(14, block->unk014), fn_1_10244(14, block->unk014));
    }
    block->unk010 = -1;
    Hu3DModelAttrReset(block->unk006[1], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(block->unk006[1], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(block->unk006[1], 0.0f);
    Hu3DModelAttrSet(block->unk006[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(block->unk006[2], HU3D_MOTATTR_PAUSE);
    M519_OBJWAIT(Hu3DMotionMaxTimeGet(block->unk006[1]));
    Hu3DModelAttrReset(block->unk006[1], HU3D_MOTATTR_PAUSE);
    block->unk000 = 3;
}

/* 4 insns */
void fn_1_C788(M519_STAGEOBJ *block, s32 respawn)
{
    block->unk030 = respawn;
    block->unk000 = 2;
}

/* 277 insns: lbl_1_data_64[2], broken */
static const s32 lbl_1_rodata_F28[2] = { 0x717, 0x718 };
static const s32 lbl_1_rodata_F30[2] = { 300, 300 };

void fn_1_C798(M519_STAGEOBJ *block)
{
    M519_PLAYER *player;
    HuVecF a;
    HuVecF b;
    s32 n;
    s32 i;

    if (block->unk010 != -1) {
        player = lbl_1_bss_F8[block->unk010];
        HuAudFXPlayVolPan(lbl_1_rodata_F28[0], fn_1_FE20(1, block->unk014), fn_1_10244(1, block->unk014));
        HuAudFXPlayVolPan(lbl_1_rodata_F28[1], fn_1_FE20(14, block->unk014), fn_1_10244(14, block->unk014));
    }
    Hu3DModelAttrReset(block->unk006[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(block->unk006[2], HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(block->unk006[2], 0.0f);
    Hu3DModelAttrSet(block->unk006[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(block->unk006[1], HU3D_MOTATTR_PAUSE);
    M519_OBJWAIT(Hu3DMotionMaxTimeGet(block->unk006[1]));
    Hu3DModelAttrSet(block->unk006[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(block->unk006[2], HU3D_MOTATTR_PAUSE);
    n = lbl_1_rodata_F30[block->unk004];
    for (i = 0; i < n; i++) {
        M519_OBJWAIT(1);
    }
    a.x = block->unk014.x;
    a.y = block->unk014.z;
    a.z = 100.0f + block->unk02C;
    if (block->unk030) {
        while (1) {
            for (i = 0; i < 4; i++) {
                player = lbl_1_bss_F8[i];
                if (player == NULL) {
                    continue;
                }
                b.x = player->unk084.x;
                b.y = player->unk084.z;
                b.z = player->unk070;
                if (fn_1_F860(&a, &b, 0) && !lbl_1_bss_0 && !lbl_1_bss_4) {
                    break;
                }
            }
            if (i == 4) {
                break;
            }
            M519_OBJWAIT(1);
        }
    } else {
        while (1) {
            M519_OBJWAIT(1);
        }
    }
    fn_1_C544(block);
}

/* 22 insns */
void fn_1_CBEC(M519_STAGEOBJ *block)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(block->unk006[i], HU3D_ATTR_DISPOFF);
    }
}

/* 44 insns */
M519_EFFECT *fn_1_CC44(void)
{
    M519_EFFECT *work;
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_EFFECT), HU_MEMNUM_OVL);
    work->unk010 = HuSprAnimRead(HuDataSelHeapReadNum(0x4D0045, HU_MEMNUM_OVL, HEAP_MODEL));
    work->unk000 = Hu3DParticleCreate(work->unk010, 42);
    Hu3DParticleBlendModeSet(work->unk000, HU3D_PARTICLE_BLEND_ADDCOL);
    modelP = &Hu3DData[work->unk000];
    particleP = modelP->hookData;
    particleP->work = work;
    Hu3DParticleHookSet(work->unk000, fn_1_CCF4);
    return work;
}

/* 24 insns */
void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    lbl_1_data_74[particleP->dataCnt](particleP->work, modelP, particleP, mtx);
}

/* 7 insns */
void fn_1_CD54(M519_EFFECT *work, HuVecF pos)
{
    work->unk004 = pos;
}

/* 7 insns */
HuVecF fn_1_CD70(M519_EFFECT *work)
{
    return work->unk004;
}

/* 25 insns */
void fn_1_CD8C(M519_EFFECT *work)
{
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;

    Hu3DModelAttrSet(work->unk000, HU3D_ATTR_DISPOFF);
    modelP = &Hu3DData[work->unk000];
    particleP = modelP->hookData;
    particleP->dataCnt = 0;
}

/* 1 insns: lbl_1_data_74[0] */
void fn_1_CDF0(M519_EFFECT *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
}

/* 60 insns */
void fn_1_CDF4(M519_EFFECT *work)
{
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *data;
    s32 i;

    Hu3DModelAttrReset(work->unk000, HU3D_ATTR_DISPOFF);
    modelP = &Hu3DData[work->unk000];
    particleP = modelP->hookData;
    data = particleP->data;
    for (i = 0, data = particleP->data; i < particleP->maxCnt; i++, data++) {
        data->time = 0;
        data->parManId = 0;
        data->pos.x = 0.0f;
        data->pos.y = -100.0f;
        data->pos.z = 0.0f;
        data->color.r = 0xFF;
        data->color.g = 0xFF;
        data->color.b = 0xFF;
        data->color.a = 0xFF;
        data->scale = 1.0f;
    }
    particleP->dataCnt = 1;
}

/* 65 insns: lbl_1_data_74[1] */
void fn_1_CEE4(M519_EFFECT *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;

    for (i = 0, data = particleP->data; i < particleP->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->pos.x = 0.0f;
                data->pos.y = -100.0f;
                data->pos.z = 0.0f;
                break;
            case 1:
                data->color.a = 64 - (s32)(4.0f * data->parManId);
                if (data->parManId++ > 16) {
                    data->color.a = 0;
                    data->time = 0;
                }
                break;
        }
    }
}

/* 53 insns */
s32 fn_1_CFE8(M519_EFFECT *work)
{
    HU3DMODEL *modelP;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *data;
    s32 i;

    modelP = &Hu3DData[work->unk000];
    particleP = modelP->hookData;
    for (data = particleP->data, i = 0; i < particleP->maxCnt; i++, data++) {
        if (data->time == 0) {
            data->time = 1;
            data->parManId = 0;
            data->pos.x = work->unk004.x;
            data->pos.y = work->unk004.y;
            data->pos.z = work->unk004.z;
            data->color.r = 0xFF;
            data->color.g = 0xFF;
            data->color.b = 0xFF;
            data->color.a = 0xFF;
            data->scale = 5.0f;
            return 1;
        }
    }
    return 0;
}

/* 341 insns */
static const s32 lbl_1_rodata_F44[4][18] = {
    { 0x004D004C, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051,
      0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D0059, 0x004D005A },
    { 0x004D004D, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051,
      0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C },
    { 0x004D004E, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051,
      0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C },
    { 0x004D004F, 0x004D0049, 0x004D004B, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D004A, 0x004D0050, 0x004D0051,
      0x004D0052, 0x004D0053, 0x004D0054, 0x004D0055, 0x004D0056, 0x004D0057, 0x004D0058, 0x004D005B, 0x004D005C },
};

static const HuVec2f lbl_1_rodata_1064[4][18] = {
    { { 0.0f, 0.0f }, { -84.0f, -16.0f }, { -32.0f, 0.0f }, { -84.0f, -16.0f }, { -84.0f, -16.0f }, { -84.0f, -16.0f },
      { -84.0f, -16.0f }, { 111.0f, -3.0f }, { 111.0f, -3.0f }, { 111.0f, -3.0f }, { 129.0f, -22.0f }, { 129.0f, -22.0f },
      { 129.0f, -22.0f }, { 148.5f, -41.5f }, { 148.5f, -41.5f }, { 148.5f, -41.5f }, { 24.0f, -28.0f }, { 24.0f, -28.0f } },
    { { 0.0f, 0.0f }, { -88.0f, -40.0f }, { -14.0f, 78.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
      { 0.0f, 0.0f }, { -24.0f, -15.0f }, { -24.0f, -15.0f }, { -24.0f, -15.0f }, { -4.0f, -35.0f }, { -4.0f, -35.0f },
      { -4.0f, -35.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 8.0f, -31.0f }, { 8.0f, -31.0f } },
    { { 0.0f, 0.0f }, { -88.0f, -40.0f }, { -14.0f, 61.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
      { 0.0f, 0.0f }, { -24.0f, -33.0f }, { -24.0f, -33.0f }, { -24.0f, -33.0f }, { -4.0f, -52.0f }, { -4.0f, -52.0f },
      { -4.0f, -52.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 8.0f, -48.0f }, { 8.0f, -48.0f } },
    { { 0.0f, 0.0f }, { -88.0f, -40.0f }, { -14.0f, 42.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f },
      { 0.0f, 0.0f }, { -24.0f, -49.5f }, { -24.0f, -49.5f }, { -24.0f, -49.5f }, { -4.0f, -69.0f }, { -4.0f, -69.0f },
      { -4.0f, -69.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 0.0f, 0.0f }, { 8.0f, -64.0f }, { 8.0f, -64.0f } },
};

M519_HUD *fn_1_D0BC(s16 layout, s16 arg1)
{
    M519_HUD *hud;
    s32 i;

    hud = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M519_HUD), HU_MEMNUM_OVL);
    hud->unk004 = layout;
    hud->unk006 = 0;
    hud->unk008 = arg1;
    hud->unk000 = 0;
    hud->unk002 = 0;
    for (i = 0; i < 18; i++) {
        if (lbl_1_rodata_F44[layout][i] != -1) {
            hud->unk00A[i] = espEntry(lbl_1_rodata_F44[layout][i], 0, 0);
            espDispOff(hud->unk00A[i]);
        } else {
            hud->unk00A[i] = -1;
        }
    }
    switch (hud->unk004) {
        case 0:
            espPriSet(hud->unk00A[0], 1000);
            espPriSet(hud->unk00A[1], 900);
            espPriSet(hud->unk00A[2], 900);
            espPriSet(hud->unk00A[3], 950);
            espPriSet(hud->unk00A[4], 960);
            espPriSet(hud->unk00A[5], 970);
            espPriSet(hud->unk00A[6], 980);
            espPriSet(hud->unk00A[7], 900);
            espPriSet(hud->unk00A[8], 910);
            espPriSet(hud->unk00A[9], 920);
            espPriSet(hud->unk00A[10], 900);
            espPriSet(hud->unk00A[11], 910);
            espPriSet(hud->unk00A[12], 920);
            espPriSet(hud->unk00A[13], 900);
            espPriSet(hud->unk00A[14], 910);
            espPriSet(hud->unk00A[15], 920);
            espPriSet(hud->unk00A[16], 900);
            espPriSet(hud->unk00A[17], 900);
            espScaleSet(hud->unk00A[7], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[8], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[9], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[10], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[11], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[12], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[13], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[14], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[15], 0.6f, 0.6f);
            break;
        case 1:
        case 2:
        case 3:
            espPriSet(hud->unk00A[0], 1000);
            espPriSet(hud->unk00A[1], 900);
            espPriSet(hud->unk00A[2], 900);
            espPriSet(hud->unk00A[3], 950);
            espPriSet(hud->unk00A[4], 960);
            espPriSet(hud->unk00A[5], 970);
            espPriSet(hud->unk00A[6], 980);
            espPriSet(hud->unk00A[7], 900);
            espPriSet(hud->unk00A[8], 910);
            espPriSet(hud->unk00A[9], 920);
            espPriSet(hud->unk00A[10], 900);
            espPriSet(hud->unk00A[11], 910);
            espPriSet(hud->unk00A[12], 920);
            espPriSet(hud->unk00A[16], 900);
            espPriSet(hud->unk00A[17], 900);
            espScaleSet(hud->unk00A[7], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[8], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[9], 0.6f, 0.6f);
            espScaleSet(hud->unk00A[10], 0.35f, 0.35f);
            espScaleSet(hud->unk00A[11], 0.35f, 0.35f);
            espScaleSet(hud->unk00A[12], 0.35f, 0.35f);
            espScaleSet(hud->unk00A[16], 0.58f, 0.58f);
            espScaleSet(hud->unk00A[17], 0.68f, 0.68f);
            break;
    }
    for (i = 0; i < 18; i++) {
        hud->unk038[i] = lbl_1_rodata_1064[layout][i];
    }
    hud->unk0C8 = HuPrcChildCreate(fn_1_D610, 0x1000, 0x1800, 0, HuPrcCurrentGet());
    hud->unk0C8->property = hud;
    return hud;
}

/* 19 insns: M519_HUD process */
void fn_1_D610(void)
{
    M519_HUD *work = HuPrcCurrentGet()->property;

    while (1) {
        lbl_1_data_7C[work->unk004][work->unk000](work);
    }
}

/* 43 insns */
void fn_1_D65C(M519_HUD *work, HuVec2f pos)
{
    s32 i;

    work->unk030 = pos;
    for (i = 0; i < 18; i++) {
        if (work->unk00A[i] != -1) {
            espPosSet(work->unk00A[i], pos.x + work->unk038[i].x, pos.y + work->unk038[i].y);
        }
    }
}

/* 3 insns */
HuVec2f fn_1_D708(M519_HUD *work)
{
    return work->unk030;
}

/* 3 insns */
void fn_1_D714(M519_HUD *work)
{
    work->unk000 = 0;
}

/* 36 insns: lbl_1_data_7C[*][0], the idle state */
void fn_1_D720(M519_HUD *work)
{
    while (1) {
        M519_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_D7B0(M519_HUD *work)
{
    work->unk000 = 1;
}

/* 339 insns: lbl_1_data_7C[0][1] */
void fn_1_D7BC(M519_HUD *work)
{
    M519_PLAYER *player;
    HuVec2f pos;
    HuVec2f tmp;
    float t;
    float s;
    s32 i;
    s32 j;

    player = lbl_1_bss_F8[work->unk008];
    pos = work->unk030;
    espDispOn(work->unk00A[0]);
    for (i = 1; i <= 60; i++) {
        t = 0.016666668f * i;
        tmp.x = pos.x;
        tmp.y = pos.y - 100.0 * sin(M_PI * (90.0f * t) / 180.0);
        fn_1_D65C(work, tmp);
        M519_OBJWAIT(1);
    }
    pos.y -= 100.0f;
    fn_1_D65C(work, pos);
    espDispOn(work->unk00A[2]);
    espDispOn(work->unk00A[1]);
    espDispOn(work->unk00A[3]);
    espDispOn(work->unk00A[4]);
    espDispOn(work->unk00A[5]);
    espDispOn(work->unk00A[6]);
    espDispOn(work->unk00A[7]);
    espDispOn(work->unk00A[8]);
    espDispOn(work->unk00A[9]);
    espDispOn(work->unk00A[10]);
    espDispOn(work->unk00A[11]);
    espDispOn(work->unk00A[12]);
    espDispOn(work->unk00A[13]);
    espDispOn(work->unk00A[14]);
    espDispOn(work->unk00A[15]);
    espDispOn(work->unk00A[16]);
    fn_1_E298(work);
    fn_1_E2D4(work);
    fn_1_E714(work);
    for (j = 1; j <= 100; j++) {
        t = 0.01f * j;
        s = sin(M_PI * (90.0f * t) / 180.0);
        espScaleSet(work->unk00A[2], 108.0f * s, 0.8f);
        espTPLvlSet(work->unk00A[2], 0.8f * s);
        espTPLvlSet(work->unk00A[7], s);
        espTPLvlSet(work->unk00A[8], 0.0f);
        espTPLvlSet(work->unk00A[9], 0.0f);
        espTPLvlSet(work->unk00A[10], s);
        espTPLvlSet(work->unk00A[11], 0.0f);
        espTPLvlSet(work->unk00A[12], 0.0f);
        espTPLvlSet(work->unk00A[13], s);
        espTPLvlSet(work->unk00A[14], 0.0f);
        espTPLvlSet(work->unk00A[15], 0.0f);
        espTPLvlSet(work->unk00A[16], 0.2f * s);
        espZRotSet(work->unk00A[1], 720.0f * s);
        espTPLvlSet(work->unk00A[1], 0.5f * s);
        for (i = 0; i < 4; i++) {
            espTPLvlSet(work->unk00A[i + 3], s);
        }
        M519_OBJWAIT(1);
    }
    fn_1_E168(work);
}

/* 280 insns: lbl_1_data_7C[1..3][1] */
void fn_1_DD08(M519_HUD *work)
{
    M519_PLAYER *player;
    HuVec2f pos;
    HuVec2f tmp;
    float t;
    float s;
    s32 i;

    player = lbl_1_bss_F8[work->unk008];
    pos = work->unk030;
    espDispOn(work->unk00A[0]);
    for (i = 1; i <= 60; i++) {
        t = 0.016666668f * i;
        tmp.x = pos.x - 96.0 * sin(M_PI * (90.0f * t) / 180.0);
        tmp.y = pos.y;
        fn_1_D65C(work, tmp);
        M519_OBJWAIT(1);
    }
    pos.x -= 96.0f;
    fn_1_D65C(work, pos);
    espDispOn(work->unk00A[7]);
    espDispOn(work->unk00A[8]);
    espDispOn(work->unk00A[9]);
    espDispOn(work->unk00A[2]);
    espDispOn(work->unk00A[16]);
    for (i = 1; i <= 100; i++) {
        t = 0.01f * i;
        s = sin(M_PI * (90.0f * t) / 180.0);
        espTPLvlSet(work->unk00A[7], s);
        espTPLvlSet(work->unk00A[8], 0.0f);
        espTPLvlSet(work->unk00A[9], 0.0f);
        espTPLvlSet(work->unk00A[10], s);
        espTPLvlSet(work->unk00A[11], 0.0f);
        espTPLvlSet(work->unk00A[12], 0.0f);
        espTPLvlSet(work->unk00A[16], 0.2f * s);
        espZRotSet(work->unk00A[2], -90.0f);
        espScaleSet(work->unk00A[2], 72.0f * s, 0.8f);
        espTPLvlSet(work->unk00A[2], 0.8f * s);
        M519_OBJWAIT(1);
    }
    fn_1_E168(work);
}

/* 3 insns */
void fn_1_E168(M519_HUD *work)
{
    work->unk000 = 2;
}

/* 73 insns: lbl_1_data_7C[0][2] */
void fn_1_E174(M519_HUD *work)
{
    while (1) {
        fn_1_E298(work);
        fn_1_E2D4(work);
        fn_1_E714(work);
        fn_1_EA10(work);
        fn_1_D65C(work, work->unk030);
        M519_OBJWAIT(1);
    }
}

/* 15 insns */
void fn_1_E298(M519_HUD *work)
{
    espZRotSet(work->unk00A[1], 0.0f);
}

/* 272 insns: the other three players as radar blips */
void fn_1_E2D4(M519_HUD *work)
{
    HuVecF radar;
    HuVecF blip;
    HuVecF selfRot;
    HuVecF otherRot;
    HuVecF selfPos;
    HuVecF otherPos;
    HuVec2f ofs;
    HuVec2f diff;
    float angle;
    float dist;
    s16 espId;
    s32 n;
    s32 i;

    radar.x = 0.0f;
    radar.y = 0.0f;
    radar.z = 30.0f;
    selfPos = fn_1_3274(lbl_1_bss_F8[work->unk008]);
    selfRot = fn_1_34FC(lbl_1_bss_F8[work->unk008]);
    for (i = 0; i < 4; i++) {
        if (i != work->unk008) {
            otherPos = fn_1_3274(lbl_1_bss_F8[i]);
            otherRot = fn_1_34FC(lbl_1_bss_F8[i]);
            diff.x = otherPos.x - selfPos.x;
            diff.y = otherPos.z - selfPos.z;
            angle = 180.0 + 180.0 * (atan2(diff.x, diff.y) / M_PI);
            dist = sqrtf(diff.x * diff.x + diff.y * diff.y);
            ofs.x = 0.015f * dist * sin(M_PI * (angle - selfRot.y) / 180.0);
            ofs.y = 0.015f * dist * cos(M_PI * (angle - selfRot.y) / 180.0);
            blip.x = ofs.x;
            blip.y = -ofs.y;
            blip.z = 4.0f;
            ofs.x -= 84.0f;
            ofs.y -= 16.0f;
            n = i + 3;
            work->unk038[n] = ofs;
            espId = work->unk00A[n];
            if (!fn_1_A1D4(lbl_1_bss_F8[i]) && fn_1_F860(&radar, &blip, 0)) {
                espZRotSet(espId, selfRot.y - otherRot.y);
                espDispOn(espId);
            } else {
                espDispOff(espId);
            }
        }
    }
}

/* 191 insns */
void fn_1_E714(M519_HUD *work)
{
    M519_PLAYER *player;
    float scale;
    s16 level;

    player = lbl_1_bss_F8[work->unk008];
    espScaleSet(work->unk00A[2], 108.0f * (1.0f / player->unk034 * player->unk032), 0.8f);
    if (player->unk032 > player->unk030) {
        player->unk032--;
    } else if (player->unk032 < player->unk030) {
        player->unk032++;
    }
    scale = 56.0f * ((player->unk064 < 0.0f) ? -player->unk064 : player->unk064);
    espTPLvlSet(work->unk00A[14], 1.0f / scale * player->unk050);
    espTPLvlSet(work->unk00A[15], 1.0f / scale * player->unk050);
    espTPLvlSet(work->unk00A[8], 0.125f * player->unk02E);
    espTPLvlSet(work->unk00A[9], 0.125f * player->unk02E);
    level = (player->unk068 > 10.0f) ? 10.0f : player->unk068;
    espTPLvlSet(work->unk00A[11], 0.1f * level);
    espTPLvlSet(work->unk00A[12], 0.1f * level);
}

/* no symbol: the blink stage of a player's two timers (fn_1_EA10, fn_1_F104) */
static inline s16 fn_1_BlinkStage(M519_PLAYER *player)
{
    if (player->unk038 > 0) {
        if (player->unk038 >= 90) {
            return 2;
        }
        if (player->unk038 > 40) {
            return 1;
        }
    } else if (player->unk036 > 0) {
        if (player->unk036 >= 90) {
            return 2;
        }
        if (player->unk036 > 40) {
            return 1;
        }
    }
    return 0;
}

/* 218 insns */
void fn_1_EA10(M519_HUD *work)
{
    M519_PLAYER *player;

    player = lbl_1_bss_F8[work->unk008];
    espDispOff(work->unk00A[16]);
    espDispOff(work->unk00A[17]);
    if (player->unk038 > 0) {
        switch (fn_1_BlinkStage(player)) {
            case 0:
                espDispOn(work->unk00A[17]);
                espTPLvlSet(work->unk00A[17], 0.2f + 0.008888889f * player->unk038);
                break;
            case 1:
                if ((player->unk038 / 4) % 2 == 0) {
                    espDispOn(work->unk00A[17]);
                    espTPLvlSet(work->unk00A[17], 1.0f);
                }
                break;
            case 2:
                if ((player->unk038 / 2) % 2 == 0) {
                    espDispOn(work->unk00A[17]);
                    espTPLvlSet(work->unk00A[17], 1.0f);
                }
                break;
        }
    } else {
        switch (fn_1_BlinkStage(player)) {
            case 0:
                espDispOn(work->unk00A[16]);
                espTPLvlSet(work->unk00A[16], 0.2f + 0.008888889f * player->unk036);
                break;
            case 1:
                if ((player->unk036 / 4) % 2 == 0) {
                    espDispOn(work->unk00A[16]);
                    espTPLvlSet(work->unk00A[16], 1.0f);
                }
                break;
            case 2:
                if ((player->unk036 / 2) % 2 == 0) {
                    espDispOn(work->unk00A[16]);
                    espTPLvlSet(work->unk00A[16], 1.0f);
                }
                break;
        }
    }
}

/* 69 insns: lbl_1_data_7C[1..3][2] */
void fn_1_ED78(M519_HUD *work)
{
    while (1) {
        fn_1_EE8C(work);
        fn_1_F104(work);
        fn_1_D65C(work, work->unk030);
        M519_OBJWAIT(1);
    }
}

/* 158 insns */
void fn_1_EE8C(M519_HUD *work)
{
    M519_PLAYER *player;
    s16 level;

    player = lbl_1_bss_F8[work->unk008];
    espZRotSet(work->unk00A[2], -90.0f);
    espScaleSet(work->unk00A[2], 72.0f * (1.0f / player->unk034 * player->unk032), 0.8f);
    if (player->unk032 > player->unk030) {
        player->unk032--;
    } else if (player->unk032 < player->unk030) {
        player->unk032++;
    }
    espTPLvlSet(work->unk00A[8], 0.125f * player->unk02E);
    espTPLvlSet(work->unk00A[9], 0.125f * player->unk02E);
    level = (player->unk068 > 10.0f) ? 10.0f : player->unk068;
    espTPLvlSet(work->unk00A[11], 0.1f * level);
    espTPLvlSet(work->unk00A[12], 0.1f * level);
}

/* 118 insns */
void fn_1_F104(M519_HUD *work)
{
    M519_PLAYER *player;

    player = lbl_1_bss_F8[work->unk008];
    espDispOff(work->unk00A[16]);
    espDispOff(work->unk00A[17]);
    switch (fn_1_BlinkStage(player)) {
        case 0:
            espDispOn(work->unk00A[16]);
            espTPLvlSet(work->unk00A[16], 0.2f + 0.008888889f * player->unk038);
            break;
        case 1:
            if ((player->unk038 / 4) % 2 == 0) {
                espDispOn(work->unk00A[16]);
                espTPLvlSet(work->unk00A[16], 1.0f);
            }
            break;
        case 2:
            /* retail: stage 2 blinks unk00A[17], stages 0/1 unk00A[16] */
            if ((player->unk038 / 2) % 2 == 0) {
                espDispOn(work->unk00A[17]);
                espTPLvlSet(work->unk00A[17], 1.0f);
            }
            break;
    }
}

/* 3 insns */
void fn_1_F2DC(M519_HUD *work)
{
    work->unk000 = 3;
}

/* 160 insns: lbl_1_data_7C[0][3] */
void fn_1_F2E8(M519_HUD *work)
{
    M519_PLAYER *player;
    HuVec2f pos;
    HuVec2f tmp;
    float t;
    s32 i;

    player = lbl_1_bss_F8[work->unk008];
    pos = work->unk030;
    for (i = 1; i <= 120; i++) {
        t = 0.008333334f * i;
        tmp.x = pos.x;
        tmp.y = pos.y + 100.0 * sin(M_PI * (90.0f * t) / 180.0);
        fn_1_D65C(work, tmp);
        M519_OBJWAIT(1);
    }
    pos.y += 104.0f;
    fn_1_D65C(work, pos);
    work->unk000 = 0;
}

/* 162 insns: lbl_1_data_7C[1..3][3] */
void fn_1_F568(M519_HUD *work)
{
    M519_PLAYER *player;
    HuVec2f pos;
    HuVec2f tmp;
    float t;
    s32 i;

    player = lbl_1_bss_F8[work->unk008];
    pos = work->unk030;
    espDispOn(work->unk00A[0]);
    for (i = 1; i <= 120; i++) {
        t = 0.008333334f * i;
        tmp.x = pos.x + 96.0 * sin(M_PI * (90.0f * t) / 180.0);
        tmp.y = pos.y;
        fn_1_D65C(work, tmp);
        M519_OBJWAIT(1);
    }
    pos.x += 96.0f;
    fn_1_D65C(work, pos);
    work->unk000 = 0;
}

/* 28 insns */
void fn_1_F7F0(M519_HUD *work)
{
    s32 i;

    for (i = 0; i < 18; i++) {
        if (work->unk00A[i] != -1) {
            espDispOff(work->unk00A[i]);
        }
    }
    work->unk000 = 0;
}

/* 131 insns: circles {x, y, r} a and b overlap; push a out of b */
s32 fn_1_F860(HuVecF *a, HuVecF *b, s32 push)
{
    float dx;
    float dy;
    float r;
    float dist;

    dx = a->x - b->x;
    dy = a->y - b->y;
    r = a->z + b->z;
    dist = sqrtf(dx * dx + dy * dy);
    if (dist < r) {
        if (0.0f == dist) {
            dx = 0.0f;
            dy = -1.0f;
        } else {
            dx /= dist;
            dy /= dist;
        }
        if (push) {
            a->x = b->x + dx * r;
            a->y = b->y + dy * r;
        }
        return 1;
    }
    return 0;
}

/* 131 insns: circle a {x, y, r} pokes out of circle b; pull it back in */
s32 fn_1_FA6C(HuVecF *a, HuVecF *b, s32 push)
{
    float dx;
    float dy;
    float r;
    float dist;

    dx = a->x - b->x;
    dy = a->y - b->y;
    r = b->z - a->z;
    dist = sqrtf(dx * dx + dy * dy);
    if (dist > r) {
        if (0.0f == dist) {
            dx = 0.0f;
            dy = -1.0f;
        } else {
            dx /= dist;
            dy /= dist;
        }
        if (push) {
            a->x = b->x + dx * r;
            a->y = b->y + dy * r;
        }
        return 1;
    }
    return 0;
}

/* 65 insns: m508 object.c fn_1_E140 / m518 fn_1_ABA8 */
float fn_1_FC78(float start, float end, float t)
{
    float angleDiff;
    float result;
    angleDiff = fmod(end - start, 360);
    if (angleDiff < 0) {
        angleDiff += 360;
    }
    if (angleDiff > 180) {
        angleDiff -= 360;
    }
    result = fmod(start + (angleDiff * t), 360);
    if (result < 0) {
        result += 360;
    }
    return result;
}

/* 41 insns */
void fn_1_FD7C(s16 playerNo, s16 type, s16 duration)
{
    switch (type) {
        case 0:
            omVibrate(playerNo, duration, 6, 6);
            break;
        case 1:
            omVibrate(playerNo, duration, 4, 2);
            break;
        case 2:
            omVibrate(playerNo, duration, 12, 0);
            break;
    }
}

/* 265 insns: SE volume from the cameras in camMask facing pos */
s16 fn_1_FE20(u16 camMask, HuVecF pos)
{
    OMCAMERAVIEW *rec;
    HU3DCAMERA *camera;
    float angle;
    float dx;
    float dz;
    s16 vol;
    s16 v;
    s32 i;

    vol = 0;
    for (i = 0; i < 4; i++) {
        if (camMask & lbl_1_rodata_10[i]) {
            rec = &lbl_1_bss_108[i];
            camera = &Hu3DCamera[i];
            angle = (180.0 + 180.0 * (atan2(camera->pos.x - pos.x, camera->pos.z - pos.z) / M_PI)) - (180.0f + rec->rot.y);
            if (angle < 0.0f) {
                angle = 360.0f + angle;
            }
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            if (angle >= 180.0f) {
                angle -= 360.0f;
            }
            angle = -angle;
            if (((angle < 0.0f) ? -angle : angle) < 30.0f) {
                dx = ((camera->pos.x - pos.x) < 0.0f) ? -(camera->pos.x - pos.x) : (camera->pos.x - pos.x);
                dz = ((camera->pos.z - pos.z) < 0.0f) ? -(camera->pos.z - pos.z) : (camera->pos.z - pos.z);
                v = 127.0f - 0.016666668f * (4800.0f - sqrtf(dx * dx + dz * dz));
                if (vol < v) {
                    vol = v;
                }
            }
        }
    }
    if (vol < 0) {
        vol = 0;
    }
    if (vol > 127) {
        vol = 127;
    }
    return vol;
}

/* 246 insns: SE pan from the cameras in camMask facing pos */
s16 fn_1_10244(u16 camMask, HuVecF pos)
{
    OMCAMERAVIEW *rec;
    HU3DCAMERA *camera;
    float angle;
    float dx;
    float dz;
    s16 pan;
    s32 num;
    s32 i;

    pan = 0;
    num = 0;
    for (i = 0; i < 4; i++) {
        if (camMask & lbl_1_rodata_10[i]) {
            rec = &lbl_1_bss_108[i];
            camera = &Hu3DCamera[i];
            angle = (180.0 + 180.0 * (atan2(camera->pos.x - pos.x, camera->pos.z - pos.z) / M_PI)) - (180.0f + rec->rot.y);
            if (angle < 0.0f) {
                angle = 360.0f + angle;
            }
            if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            if (angle >= 180.0f) {
                angle -= 360.0f;
            }
            angle = -angle;
            /* retail: |angle < 30| (the comparison, not the angle, is abs'd) */
            if (((angle < 30.0f) < 0.0f) ? -(angle < 30.0f) : (angle < 30.0f)) {
                dx = ((camera->pos.x - pos.x) < 0.0f) ? -(camera->pos.x - pos.x) : (camera->pos.x - pos.x);
                dz = ((camera->pos.z - pos.z) < 0.0f) ? -(camera->pos.z - pos.z) : (camera->pos.z - pos.z);
                if (i == 0) {
                    pan = pan + (32.0f + 0.53333336f * (30.0f + angle));
                } else {
                    pan = pan + (96.0f - 0.53333336f * (30.0f + angle));
                }
                num++;
            }
        }
    }
    pan = (num > 0) ? pan / num : 64;
    if (pan < 32) {
        pan = 32;
    }
    if (pan > 96) {
        pan = 96;
    }
    return pan;
}

