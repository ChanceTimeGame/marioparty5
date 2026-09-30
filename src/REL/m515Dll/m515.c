/*
 * m515dll m515.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m515Dll/asm/REL/m515Dll/m515.s.
 */

#include "REL/m515dll.h"

#include "game/esprite.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

const u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 };

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s16 lbl_1_rodata_10[4] = { 0x0001, 0x0002, 0x0004, 0x0008 }; */
/* 0x18 */ /* s32 lbl_1_rodata_18[9] = { 0xC3160000, 0x41C80000, 0x447A0000, 0x00000000, 0x41C80000, 0x447A0000, 0x00000000, 0x41C80000, 0x43E10000 }; */
/* 0x3C */ /* s32 lbl_1_rodata_3C[4] = { 0x43200000, 0x43340000, 0x43430000, 0x43480000 }; */
/* 0x4C */ /* float lbl_1_rodata_4C = 40.0f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 1.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 0.0f; */
/* 0x58 */ /* float lbl_1_rodata_58 = 5.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 60.0f; */
/* 0x60 */ /* float lbl_1_rodata_60 = 90.0f; */
/* 0x64 */ /* float lbl_1_rodata_64 = 180.0f; */
/* 0x68 */ /* float lbl_1_rodata_68 = 120.0f; */
/* 0x6C */ /* float lbl_1_rodata_6C = 640.0f; */
/* 0x70 */ /* float lbl_1_rodata_70 = 320.0f; */
/* 0x74 */ /* float lbl_1_rodata_74 = 480.0f; */
/* 0x78 */ /* float lbl_1_rodata_78 = 240.0f; */
/* 0x80 */ /* double lbl_1_rodata_80 = 4503601774854144; */
/* 0x88 */ /* float lbl_1_rodata_88 = 25.0f; */
/* 0x8C */ /* float lbl_1_rodata_8C = 100.0f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 45.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 20.0f; */
/* 0x98 */ /* float lbl_1_rodata_98 = 12000.0f; */
/* 0x9C */ /* float lbl_1_rodata_9C = 1.2f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 200.0f; */
/* 0xA4 */ /* s32 lbl_1_rodata_A4[3] = { 0xC3160000, 0x41C80000, 0x447A0000 }; */
/* 0xB0 */ /* s32 lbl_1_rodata_B0[4] = { 0x43340000, 0x42B40000, 0x43870000, 0x00000000 }; */
/* 0xC0 */ /* s16 lbl_1_rodata_C0[4] = { 0x0030, 0x0050, 0x0030, 0x0050 }; */
/* 0xC8 */ /* float lbl_1_rodata_C8 = 150.0f; */
/* 0xCC */ /* float lbl_1_rodata_CC = 300.0f; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 450.0f; */
/* 0xD4 */ /* float lbl_1_rodata_D4 = -450.0f; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 15.0f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 1.17f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 1000.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 8.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 312.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 220.0f; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 4800.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 3600.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = -1.0f; */
/* 0xFC */ /* s32 lbl_1_rodata_FC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x108 */ /* s32 lbl_1_rodata_108[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x114 */ /* s32 lbl_1_rodata_114[3] = { 0x00000000, 0x43340000, 0x00000000 }; */
/* 0x120 */ /* s32 lbl_1_rodata_120[3] = { 0x00000000, 0x43C80000, 0x00000000 }; */
/* 0x12C */ /* s32 lbl_1_rodata_12C[3] = { 0x00000000, 0x44480000, 0x00000000 }; */
/* 0x138 */ /* s32 lbl_1_rodata_138[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x144 */ /* float lbl_1_rodata_144 = 0.7f; */
/* 0x148 */ /* s32 lbl_1_rodata_148[4] = { 0x43340000, 0x42B40000, 0x43870000, 0x00000000 }; */
/* 0x158 */ /* float lbl_1_rodata_158 = 360.0f; */
/* 0x15C */ /* s16 lbl_1_rodata_15C[4] = { 0x0003, 0x0002, 0x0001, 0x0000 }; */
/* 0x164 */ /* s16 lbl_1_rodata_164[16] = { 0x0000, 0x0002, 0x0001, 0x0003, 0x0001, 0x0000, 0x0003, 0x0002, 0x0002, 0x0003, 0x0000, 0x0001, 0x0003, 0x0001, 0x0002, 0x0000 }; */
/* 0x184 */ /* s16 lbl_1_rodata_184[4] = { 0x0030, 0x0050, 0x0030, 0x0050 }; */
/* 0x18C */ /* float lbl_1_rodata_18C = 1.1f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 0.5f; */
/* 0x194 */ /* s32 lbl_1_rodata_194[4] = { 0x43340000, 0x42B40000, 0x43870000, 0x00000000 }; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 400.0f; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 180; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 3.141592653589793; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 32.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = -30.0f; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 60; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = -120.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 2.0f; */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 0.125f; */
/* 0x1D4 */ /* float lbl_1_rodata_1D4 = 3.0f; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = -150.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 75.0f; */
/* 0x1E0 */ /* double lbl_1_rodata_1E0 = 1; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 0.5; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 70.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 80.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 576.0f; */
/* 0x1FC */ /* s32 lbl_1_rodata_1FC[4] = { 0x41000000, 0xC1000000, 0x41000000, 0xC1000000 }; */
/* 0x20C */ /* s32 lbl_1_rodata_20C[4] = { 0x41A00000, 0x41A00000, 0xC1A00000, 0xC1A00000 }; */
/* 0x21C */ /* float lbl_1_rodata_21C = 16.0f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 288.0f; */
/* 0x224 */ /* s32 lbl_1_rodata_224[4] = { 0xC3E10000, 0xC4160000, 0xC43B8000, 0xC4610000 }; */
/* 0x234 */ /* s16 lbl_1_rodata_234[4] = { 0x0030, 0x0050, 0x0030, 0x0050 }; */
/* 0x23C */ /* float lbl_1_rodata_23C = 425.0f; */
/* 0x240 */ /* float lbl_1_rodata_240 = 825.0f; */
/* 0x244 */ /* float lbl_1_rodata_244 = -900.0f; */
/* 0x248 */ /* float lbl_1_rodata_248 = 135.0f; */
/* 0x24C */ /* s32 lbl_1_rodata_24C[2] = { 0x00000000, 0x43C80000 }; */
/* 0x254 */ /* s32 lbl_1_rodata_254[2] = { 0x43C80000, 0x44480000 }; */
/* 0x25C */ /* float lbl_1_rodata_25C = 0.3f; */
/* 0x260 */ /* s32 lbl_1_rodata_260[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x26C */ /* float lbl_1_rodata_26C = 800.0f; */
/* 0x270 */ /* float lbl_1_rodata_270 = 2400.0f; */
/* 0x274 */ /* float lbl_1_rodata_274 = 1200.0f; */
/* 0x278 */ /* float lbl_1_rodata_278 = 0.0001f; */
/* 0x27C */ /* s32 lbl_1_rodata_27C[12] = { 0x43020000, 0x42DC0000, 0xC4480000, 0x41F00000, 0x42C80000, 0xC4430000, 0xC2200000, 0x42F00000, 0xC44A8000, 0xC2F00000, 0x42DC0000, 0xC4480000 }; */
/* 0x2AC */ /* s32 lbl_1_rodata_2AC[4] = { 0x4079999A, 0x40B66666, 0x4114CCCD, 0x40F00000 }; */
/* 0x2BC */ /* s32 lbl_1_rodata_2BC[4] = { 0x0000000F, 0x00000012, 0x00000010, 0x0000000E }; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = -180.0f; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = 6.0f; */
/* 0x2D8 */ /* double lbl_1_rodata_2D8 = 3; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 0.39f; */
/* 0x2E4 */ /* s16 lbl_1_rodata_2E4[4] = { 0x0078, 0x003C, 0x002D, 0x001E }; */
/* 0x2EC */ /* s16 lbl_1_rodata_2EC[4] = { 0x003C, 0x001E, 0x000F, 0x0000 }; */
/* 0x2F4 */ /* s16 lbl_1_rodata_2F4[4] = { 0x0078, 0x003C, 0x002D, 0x001E }; */
/* 0x2FC */ /* s16 lbl_1_rodata_2FC[4] = { 0x0078, 0x005A, 0x003C, 0x002D }; */
/* 0x304 */ /* s16 lbl_1_rodata_304[4] = { 0x001E, 0x0000, 0x0000, 0x0000 }; */
/* 0x30C */ /* s16 lbl_1_rodata_30C[4] = { 0x003C, 0x002D, 0x001E, 0x000F }; */
/* 0x314 */ /* s16 lbl_1_rodata_314[6] = { 0x0003, 0x0004, 0x0006, 0x0009, 0x0000, 0x0000 }; */
/* 0x320 */ /* double lbl_1_rodata_320 = 0.05000000074505806; */
/* 0x328 */ /* float lbl_1_rodata_328 = 1.05f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 0.0f; */

/* --- .data --- */
/* 0x0 */ MGSEQ_PARAM lbl_1_data_0 = { 300, 0, (MGSEQ_FUNC)fn_1_1FC, (MGSEQ_FUNC)fn_1_26C, (MGSEQ_FUNC)fn_1_928, (MGSEQ_FUNC)fn_1_968, (MGSEQ_FUNC)fn_1_B08, (MGSEQ_FUNC)fn_1_D30, (MGSEQ_FUNC)fn_1_1B58, (MGSEQ_FUNC)fn_1_1D20, (MGSEQ_FUNC)fn_1_1D24 }; /* the nine hooks take no arguments in this overlay */
/* 0x28 */ float lbl_1_data_28[60] = { 270.0f, 10.0f, 4240.0f, 0.0f, 108.0f, 204.0f, 420.0f, 40.0f, 6000.0f, 25.0f, 25.0f, 75.0f, 420.0f, 40.0f, 6000.0f, 25.0f, 25.0f, -900.0f, 240.0f, 40.0f, 6000.0f, -25.0f, 425.0f, -675.0f, 240.0f, 40.0f, 6000.0f, -25.0f, 425.0f, -75.0f, 240.0f, 40.0f, 6000.0f, -25.0f, 425.0f, 900.0f, 60.0f, 40.0f, 6000.0f, 25.0f, 825.0f, 675.0f, 60.0f, 40.0f, 6000.0f, 25.0f, 825.0f, 75.0f, 90.0f, 15.0f, 1900.0f, 0.0f, 1000.0f, -225.0f, 90.0f, 4.0f, 1970.0f, 0.0f, 150.0f, -225.0f };
/* 0x118 */ u32 lbl_1_data_118[13][8] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0005, 0x008C0006, 0x008C0007, 0x008C000D, 0x008C000E, 0x00330000, 0x00330001, 0x00330002, 0x00330005, 0x00330006, 0x00330007, 0x0033000D, 0x0033000E, 0x00B70000, 0x00B70001, 0x00B70002, 0x00B70005, 0x00B70006, 0x00B70007, 0x00B7000D, 0x00B7000E, 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED0005, 0x00ED0006, 0x00ED0007, 0x00ED000D, 0x00ED000E, 0x00E60000, 0x00E60001, 0x00E60002, 0x00E60005, 0x00E60006, 0x00E60031, 0x00E6000D, 0x00E6000E, 0x00170000, 0x00170001, 0x00170002, 0x00170005, 0x00170006, 0x00170007, 0x0017000D, 0x0017000E, 0x00E00000, 0x00E00001, 0x00E00002, 0x00E00005, 0x00E00006, 0x00E00007, 0x00E0000D, 0x00E0000E, 0x002D0000, 0x002D0001, 0x002D0002, 0x002D0005, 0x002D0006, 0x002D0007, 0x002D000D, 0x002D000E, 0x00C90000, 0x00C90001, 0x00C90002, 0x00C90005, 0x00C90006, 0x00C90007, 0x00C9000D, 0x00C9000E, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00005, 0x00B00006, 0x00B00007, 0x00B0000D, 0x00B0000E, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00005, 0x00B00006, 0x00B00007, 0x00B0000D, 0x00B0000E, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00005, 0x00B00006, 0x00B00007, 0x00B0000D, 0x00B0000E, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00005, 0x00B00006, 0x00B00007, 0x00B0000D, 0x00B0000E };
/* 0x2B8 */ s32 lbl_1_data_2B8[26] = { 0x00490000, 0x00490002, 0x00490004, 0x00490005, 0x00490007, 0x00490009, 0x0049000B, 0x0049000D, 0x0049000F, 0x00490010, 0x00490012, 0x00490026, 0x00490027, 0x00490013, 0x00490014, 0x00490016, 0x00490018, 0x00490019, 0x0049001D, 0x00490020, 0x00490021, 0x00490022, 0x0049001B, 0x00490023, 0x00490024, 0x00490025 };
/* 0x320 */ s32 lbl_1_data_320[17] = { 0x00490028, 0x00490029, 0x0049002A, 0x0049002B, 0x0049002C, 0x0049002D, 0x0049002E, 0x0049002F, 0x00490030, 0x00490031, 0x00490032, 0x00490033, 0x00490034, 0x00490035, 0x00490036, 0x00490037, 0x00490038 };
/* 0x364 */ s32 lbl_1_data_364[17] = { 0x00490039, 0x0049003A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x3A8 */ s32 lbl_1_data_3A8[8] = { 0x0049003B, 0x0049003C, 0x0049003D, 0x0049003E, 0x0049003F, 0x00490040, 0x00490041, 0x00490042 };
/* 0x3C8 */ s32 lbl_1_data_3C8[14] = { 0x00490001, 0x00490003, 0x00490006, 0x00490008, 0x0049000A, 0x0049000C, 0x0049000E, 0x00490011, 0x00490015, 0x00490017, 0x0049001C, 0x0049001A, 0x0049001E, 0x0049001F };
/* Forward declarations for the late .data block, which is defined below
   fn_1_DD18 so the jumptables keep their addresses. */
extern u16 lbl_1_data_530[25];
extern u16 lbl_1_data_562[25];
extern u16 lbl_1_data_594[25];
extern u16 lbl_1_data_5C6[25];
extern u16 lbl_1_data_5F8[25];
extern u16 lbl_1_data_62A[25];
extern u16 lbl_1_data_65C[25];
extern u16 lbl_1_data_68E[25];
extern u16 lbl_1_data_6C0[25];
extern u16 lbl_1_data_6F2[25];
extern u16 lbl_1_data_724[25];
extern u16 lbl_1_data_756[25];
extern u16 lbl_1_data_788[25];
extern u16 lbl_1_data_7BA[25];
extern u16 lbl_1_data_7EC[25];
extern u16 lbl_1_data_81E[25];
extern u16 lbl_1_data_850[25];
extern u16 lbl_1_data_882[25];
extern u16 lbl_1_data_8B4[25];
extern u16 lbl_1_data_8E6[25];
extern u16 lbl_1_data_918[25];
extern u16 lbl_1_data_94A[25];
extern u16 lbl_1_data_97C[25];
extern u16 lbl_1_data_9AE[25];
extern u16 lbl_1_data_9E0[25];
extern u16 lbl_1_data_A12[25];
extern u16 lbl_1_data_A44[25];
extern u16 lbl_1_data_A76[25];
extern u16 lbl_1_data_AA8[25];
extern u16 lbl_1_data_ADA[25];
extern M515_LAYOUT lbl_1_data_B0C[5];
extern M515_LAYOUT lbl_1_data_B34[4];
extern M515_LAYOUT lbl_1_data_B54[7];
extern M515_LAYOUT lbl_1_data_B8C[6];
extern M515_LAYOUT lbl_1_data_BBC[8];
extern M515_LAYOUT lbl_1_data_BFC[7];
extern M515_LAYOUT lbl_1_data_C34[6];
extern M515_LAYOUT lbl_1_data_C64[6];
extern M515_LAYOUT lbl_1_data_C94[6];
extern M515_LAYOUT lbl_1_data_CC4[6];
extern M515_LAYOUT lbl_1_data_CF4[4];
extern M515_LAYOUT lbl_1_data_D14[6];
extern M515_LAYOUT lbl_1_data_D44[6];
extern M515_LAYOUT lbl_1_data_D74[5];
extern M515_LAYOUT lbl_1_data_D9C[5];
extern M515_LAYOUT lbl_1_data_DC4[9];
extern M515_LAYOUT lbl_1_data_E0C[9];
extern M515_LAYOUT lbl_1_data_E54[9];
extern M515_LAYOUT lbl_1_data_E9C[8];
extern M515_LAYOUT lbl_1_data_EDC[8];
extern M515_LAYOUT lbl_1_data_F1C[5];
extern M515_LAYOUT lbl_1_data_F44[7];
extern M515_LAYOUT lbl_1_data_F7C[3];
extern M515_LAYOUT lbl_1_data_F94[3];
extern M515_LAYOUT lbl_1_data_FAC[5];
extern M515_LAYOUT lbl_1_data_FD4[3];
extern M515_LAYOUT lbl_1_data_FEC[5];
extern M515_LAYOUT lbl_1_data_1014[5];
extern M515_LAYOUT lbl_1_data_103C[5];
extern M515_LAYOUT lbl_1_data_1064[6];
extern u16 *lbl_1_data_1094[10];
extern u16 *lbl_1_data_10BC[10];
extern u16 *lbl_1_data_10E4[10];
extern void *lbl_1_data_110C[10];
extern void *lbl_1_data_1134[10];
extern void *lbl_1_data_115C[10];
extern s16 lbl_1_data_1184[11];
extern s16 lbl_1_data_119A[14];
extern s16 lbl_1_data_11B6[20];
extern s16 lbl_1_data_11DE[16];
extern s16 lbl_1_data_11FE[18];
extern s16 lbl_1_data_1222[14];
extern s16 lbl_1_data_123E[13];
extern s16 lbl_1_data_1258[13];
extern s16 lbl_1_data_1272[19];
extern s32 lbl_1_data_1298[7];
extern s16 lbl_1_data_12B4[23];
extern s16 lbl_1_data_12E2[6];
extern s16 lbl_1_data_12EE[11];
extern s32 lbl_1_data_1304[6];
extern s16 lbl_1_data_131C[17];
extern s16 lbl_1_data_133E[11];
extern s16 lbl_1_data_1354[13];
extern s16 lbl_1_data_136E[23];
extern s16 lbl_1_data_139C[13];
extern s16 lbl_1_data_13B6[12];
extern s16 lbl_1_data_13CE[33];
extern s16 lbl_1_data_1410[15];
extern s16 lbl_1_data_142E[10];
extern s16 lbl_1_data_1442[24];
extern s16 lbl_1_data_1472[11];
extern s32 lbl_1_data_1488[6];
extern s16 lbl_1_data_14A0[17];
extern s16 lbl_1_data_14C2[13];
extern s32 lbl_1_data_14DC[8];
extern s32 lbl_1_data_14FC[15];
extern s16 lbl_1_data_1538[13];
extern s16 lbl_1_data_1552[11];
extern s16 lbl_1_data_1568[21];
extern s16 lbl_1_data_1592[16];
extern s16 lbl_1_data_15B2[12];
extern s16 lbl_1_data_15CA[15];
extern s32 lbl_1_data_15E8[7];
extern s32 lbl_1_data_1604[6];
extern s16 lbl_1_data_161C[19];
extern s16 lbl_1_data_1642[15];
extern s32 lbl_1_data_1660[6];
extern s32 lbl_1_data_1678[10];
extern s16 lbl_1_data_16A0[13];
extern s16 lbl_1_data_16BA[16];
extern s16 lbl_1_data_16DA[28];
extern s16 lbl_1_data_1712[15];
extern s32 lbl_1_data_1730[5];
extern s16 lbl_1_data_1744[29];
extern s16 lbl_1_data_177E[13];
extern s32 lbl_1_data_1798[7];
extern s16 lbl_1_data_17B4[21];
extern s16 lbl_1_data_17DE[15];
extern s16 lbl_1_data_17FC[21];
extern s16 lbl_1_data_1826[16];
extern s16 lbl_1_data_1846[12];
extern s16 lbl_1_data_185E[16];
extern s16 lbl_1_data_187E[16];
extern s16 lbl_1_data_189E[15];
extern s16 lbl_1_data_18BC[11];
extern s16 lbl_1_data_18D2[16];
extern s16 lbl_1_data_18F2[14];
extern s16 lbl_1_data_190E[15];
extern s16 lbl_1_data_192C[23];
extern s16 lbl_1_data_195A[18];
extern s16 lbl_1_data_197E[33];
extern s16 lbl_1_data_19C0[19];
extern s16 lbl_1_data_19E6[16];
extern s16 lbl_1_data_1A06[23];
extern s32 lbl_1_data_1A34[10];
extern s16 lbl_1_data_1A5C[23];
extern s16 lbl_1_data_1A8A[29];
extern s16 lbl_1_data_1AC4[21];
extern s16 lbl_1_data_1AEE[15];
extern s16 lbl_1_data_1B0C[15];
extern s16 lbl_1_data_1B2A[29];
extern s32 lbl_1_data_1B64[11];
extern s32 lbl_1_data_1B90[11];
extern s32 lbl_1_data_1BBC[13];
extern s16 lbl_1_data_1BF0[17];
extern s16 lbl_1_data_1C12[15];
extern s16 lbl_1_data_1C30[37];
extern s16 lbl_1_data_1C7A[27];
extern s32 lbl_1_data_1CB0[16];
extern s16 lbl_1_data_1CF0[31];
extern s16 lbl_1_data_1D2E[17];
extern s16 lbl_1_data_1D50[19];
extern s16 lbl_1_data_1D76[23];
extern s16 lbl_1_data_1DA4[25];
extern s16 lbl_1_data_1DD6[40];
extern s16 lbl_1_data_1E26[27];
extern s16 lbl_1_data_1E5C[17];
extern s16 lbl_1_data_1E7E[13];
extern s16 lbl_1_data_1E98[27];
extern s16 lbl_1_data_1ECE[24];
extern s16 lbl_1_data_1EFE[27];
extern s16 lbl_1_data_1F34[35];
extern s16 lbl_1_data_1F7A[16];
extern s16 lbl_1_data_1F9A[20];
extern s16 lbl_1_data_1FC2[25];
extern s16 lbl_1_data_1FF4[23];
extern s16 lbl_1_data_2022[30];
extern s16 lbl_1_data_205E[16];
extern s16 lbl_1_data_207E[17];
extern s32 lbl_1_data_20A0[11];
extern s32 lbl_1_data_20CC[18];
extern s32 lbl_1_data_2114[12];
extern s32 lbl_1_data_2144[12];
extern s32 lbl_1_data_2174[10];
extern s16 lbl_1_data_219C[17];
extern s16 lbl_1_data_21BE[22];
extern s16 lbl_1_data_21EA[26];
extern s16 lbl_1_data_221E[26];
extern s16 lbl_1_data_2252[25];
extern s16 lbl_1_data_2284[15];
extern s16 lbl_1_data_22A2[21];
extern s16 lbl_1_data_22CC[25];
extern s16 lbl_1_data_22FE[28];
extern s16 lbl_1_data_2336[32];
extern s16 lbl_1_data_2376[18];
extern s16 lbl_1_data_239A[31];
extern s32 lbl_1_data_23D8[7];
extern s32 lbl_1_data_23F4[8];
extern s16 lbl_1_data_2414[21];
extern s16 lbl_1_data_243E[21];
extern s16 lbl_1_data_2468[17];
extern s16 lbl_1_data_248A[15];
extern s32 lbl_1_data_24A8[7];
extern s32 lbl_1_data_24C4[8];
extern s16 lbl_1_data_24E4[21];
extern s16 lbl_1_data_250E[17];
extern s16 lbl_1_data_2530[27];
extern s16 lbl_1_data_2566[31];
extern s32 lbl_1_data_25A4[6];
extern s16 lbl_1_data_25BC[17];
extern s16 lbl_1_data_25DE[29];
extern s32 lbl_1_data_2618[7];
extern s16 lbl_1_data_2634[17];
extern s16 lbl_1_data_2656[29];
extern s16 lbl_1_data_2690[17];
extern s16 lbl_1_data_26B2[14];
extern s16 lbl_1_data_26CE[38];
extern s16 lbl_1_data_271A[16];
extern s16 lbl_1_data_273A[18];
extern s16 lbl_1_data_275E[31];
extern s32 lbl_1_data_279C[7];
extern s32 lbl_1_data_27B8[7];
extern s32 lbl_1_data_27D4[10];
extern s16 lbl_1_data_27FC[19];
extern s16 lbl_1_data_2822[25];
extern s16 lbl_1_data_2854[33];
extern s16 lbl_1_data_2896[17];
extern s16 lbl_1_data_28B8[13];
extern s16 lbl_1_data_28D2[24];
extern s16 lbl_1_data_2902[19];
extern s16 lbl_1_data_2928[17];
extern s16 lbl_1_data_294A[31];
extern s32 lbl_1_data_2988[10];
extern s32 lbl_1_data_29B0[8];
extern s32 lbl_1_data_29D0[12];
extern s16 lbl_1_data_2A00[23];
extern s16 lbl_1_data_2A2E[17];
extern s16 lbl_1_data_2A50[41];
extern s16 lbl_1_data_2AA2[16];
extern s16 lbl_1_data_2AC2[21];
extern s32 lbl_1_data_2AEC[19];
extern s16 lbl_1_data_2B38[21];
extern s16 lbl_1_data_2B62[12];
extern s16 lbl_1_data_2B7A[25];
extern s32 lbl_1_data_2BAC[10];
extern s32 lbl_1_data_2BD4[9];
extern s32 lbl_1_data_2BF8[12];
extern s16 lbl_1_data_2C28[19];
extern s16 lbl_1_data_2C4E[18];
extern s16 lbl_1_data_2C72[31];
extern s32 lbl_1_data_2CB0[9];
extern s16 lbl_1_data_2CD4[21];
extern s16 lbl_1_data_2CFE[22];
extern s16 lbl_1_data_2D2A[22];
extern s16 lbl_1_data_2D56[18];
extern s16 lbl_1_data_2D7A[32];
extern s16 lbl_1_data_2DBA[21];
extern s16 lbl_1_data_2DE4[23];
extern s16 lbl_1_data_2E12[29];
extern s32 lbl_1_data_2E4C[8];
extern s32 lbl_1_data_2E6C[4];
extern s16 lbl_1_data_2E7C[13];
extern s16 lbl_1_data_2E96[23];
extern s16 lbl_1_data_2EC4[25];
extern s16 lbl_1_data_2EF6[26];
extern s16 lbl_1_data_2F2A[17];
extern s16 lbl_1_data_2F4C[31];
extern s16 lbl_1_data_2F8A[21];
extern s32 lbl_1_data_2FB4[15];
extern s32 lbl_1_data_2FF0[13];
extern s32 lbl_1_data_3024[14];
extern s32 lbl_1_data_305C[9];
extern s16 lbl_1_data_3080[19];
extern s16 lbl_1_data_30A6[26];
extern s16 lbl_1_data_30DA[29];
extern s32 lbl_1_data_3114[17];
extern s16 lbl_1_data_3158[23];
extern s16 lbl_1_data_3186[34];
extern s16 lbl_1_data_31CA[26];
extern s16 lbl_1_data_31FE[37];
extern s32 lbl_1_data_3248[13];
extern s16 lbl_1_data_327C[23];
extern s16 lbl_1_data_32AA[29];
extern s16 lbl_1_data_32E4[25];
extern s16 lbl_1_data_3316[29];
extern s32 lbl_1_data_3350[19];
extern s16 lbl_1_data_339C[21];
extern s16 lbl_1_data_33C6[26];
extern s16 lbl_1_data_33FA[18];
extern s16 lbl_1_data_341E[36];
extern s16 lbl_1_data_3466[27];
extern s16 lbl_1_data_349C[35];
extern s16 lbl_1_data_34E2[24];
extern s16 lbl_1_data_3512[31];
extern s16 lbl_1_data_3550[25];
extern s16 lbl_1_data_3582[24];
extern s16 lbl_1_data_35B2[15];
extern s16 lbl_1_data_35D0[35];
extern s16 lbl_1_data_3616[36];
extern s16 lbl_1_data_365E[31];
extern s16 lbl_1_data_369C[17];
extern s16 lbl_1_data_36BE[34];
extern s16 lbl_1_data_3702[27];
extern s32 lbl_1_data_3738[16];
extern s16 lbl_1_data_3778[15];
extern s16 lbl_1_data_3796[28];
extern s16 lbl_1_data_37CE[28];
extern s16 lbl_1_data_3806[25];
extern s32 lbl_1_data_3838[9];
extern s32 lbl_1_data_385C[14];
extern s16 lbl_1_data_3894[19];
extern s16 lbl_1_data_38BA[19];
extern s16 lbl_1_data_38E0[23];
extern s16 lbl_1_data_390E[23];
extern s32 lbl_1_data_393C[15];
extern s32 lbl_1_data_3978[16];
extern void *lbl_1_data_39B8[60];
extern void *lbl_1_data_3AA8[60];
extern void *lbl_1_data_3B98[120];

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x8 */ OMOBJMAN *lbl_1_bss_8;
/* 0x4 */ OMOBJ *lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 87 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    M515_WORK *work;
    s32 i;

    lbl_1_bss_8 = omInitObjMan(500, 0x2000);
    omGameSysInit(lbl_1_bss_8);
    obj = omAddObjEx(lbl_1_bss_8, 0x65, 0, 0, OM_GRP_NONE, fn_1_29D0);
    lbl_1_bss_4 = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M515_WORK), HU_MEMNUM_OVL);
    work = obj->data;
    fn_1_2B6C(work);
    fn_1_2EB4(work);
    fn_1_C83C();
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_8, 0x64, 1, 8, 0, fn_1_1D60);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M515_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
        work->player[i] = obj->data;
    }
    fn_1_2F3C(work);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(TRUE);
    MgSeqCreate(&lbl_1_data_0);
    work->unkCAC = 0;
}

/* 28 insns */
void fn_1_1FC(void)
{
    M515_WORK *work = lbl_1_bss_4->data;

    work->unk1D0 = 0;
    work->unk1DA = 0;
    work->unk1D2 = 0;
    work->unk1D6 = -1;
    work->unk1F4 = 0;
    fn_1_32C4(work);
    fn_1_CE98(work);
    MgSeqModeNext();
}

/* 431 insns */
void fn_1_26C(void)
{
    M515_WORK *work;
    M515_PLAYER *player;
    s32 i;
    float t;
    float u;
    HuVecF camPos[3] = { { -150.0f, 25.0f, 1000.0f }, { 0.0f, 25.0f, 1000.0f }, { 0.0f, 25.0f, 450.0f } };
    float camDist[4] = { 160.0f, 180.0f, 195.0f, 200.0f };

    work = lbl_1_bss_4->data;
    player = work->player[0];
    switch (work->unk1DA) {
    case 0:
        HuAudFXPlay(1768);
        MgSeqModeChangeOff();
        work->unk1D2 = 0;
        work->unk1DA++;
    case 1:
        fn_1_D0D8(work);
        work->unk1D2++;
        t = work->unk1D2 / 40.0f;
        player->unk44C.x = camPos[0].x * (1.0f - t) + camPos[1].x * t;
        omSetTra(player->unk68C, player->unk44C.x, player->unk44C.y, player->unk44C.z);
        if (work->unk1D2 >= 40) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
            work->unk1D2 = 0;
            work->unk1DA++;
        }
        break;
    case 2:
        fn_1_D0D8(work);
        work->unk1D2++;
        if (work->unk1D2 >= 30) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[6], 60.0f, 5.0f, HU3D_MOTATTR_NONE);
            work->unk1D2 = 0;
            work->unk1DA++;
        }
        break;
    case 3:
        fn_1_D0D8(work);
        work->unk1D2++;
        if (work->unk1D2 == 55) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
        t = work->unk1D2 / 60.0f;
        player->unk458.y = 90.0f * (1.0f - t) + 180.0f * t;
        omSetRot(player->unk68C, player->unk458.x, player->unk458.y, player->unk458.z);
        if (work->unk1D2 >= 60) {
            HuAudFXPlay(1759);
            Hu3DModelAttrReset(work->unk0A6[0], HU3D_MOTATTR_PAUSE);
            work->unk1D2 = 0;
            work->unk1DA++;
            work->unk130[0].unk00++;
            work->unk130[1].unk00++;
            work->unk130[2].unk00++;
            work->unk130[3].unk00++;
        }
        break;
    case 4:
        fn_1_D0D8(work);
        work->unk1D2++;
        if (work->unk1D2 >= 80) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[1], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
            work->unk1D2 = 0;
            work->unk1DA++;
        }
        break;
    case 5:
        fn_1_D0D8(work);
        work->unk1D2++;
        t = work->unk1D2 / 120.0f;
        if (t > 1.0f) {
            t = 1.0f;
            if (player->unk68C->mtnId[0] != Hu3DMotionIDGet(player->unk68C->mdlId[0]) &&
                player->unk68C->mtnId[0] != Hu3DMotionShiftIDGet(player->unk68C->mdlId[0])) {
                Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
            }
        }
        player->unk44C.z = camPos[1].z * (1.0f - t) + camPos[2].z * t;
        omSetTra(player->unk68C, player->unk44C.x, player->unk44C.y, player->unk44C.z);
        if (work->unk1D2 == 60) {
            Hu3DModelAttrSet(work->unk0A6[0], HU3D_MOTATTR_REV);
        }
        if (work->unk1D2 == 45) {
            Hu3DModelAttrReset(work->unk01E[0], HU3D_ATTR_DISPOFF);
        }
        if (work->unk1D2 > 20) {
            if (fn_1_83E8(&work->unk234[0])) {
                for (i = 0; i < 4; i++) {
                    Hu3DModelAttrSet(work->unk130[i].unk0C, HU3D_ATTR_DISPOFF);
                }
                work->unk1DA++;
            }
            u = work->unk234[0].unk26 / 120.0f;
            work->unk334.unk04 = 640.0f * (1.0f - u) + 320.0f * u;
            work->unk334.unk08 = 480.0f * (1.0f - u) + 240.0f * u;
            fn_1_9958(&work->unk334);
        }
        break;
    case 6:
        lbl_1_bss_0 = HuAudBGMPlay(MSM_STREAM_MGMUS_6);
        MgSeqModeNext();
        break;
    }
}

/* 16 insns */
void fn_1_928(void)
{
    M515_WORK *work = lbl_1_bss_4->data;

    Hu3DModelAttrSet(work->unk00C, HU3D_ATTR_DISPOFF);
}

/* 104 insns */
void fn_1_968(void)
{
    M515_PLAYER *player;
    M515_WORK *work;
    s32 i;
    s32 num;
    s32 list[4];

    work = lbl_1_bss_4->data;
    num = 0;
    for (i = 0; i < 4; i++) {
        player = work->player[i];
        list[num] = -1;
        if (player->unk482 == 5) {
            list[num] = i;
            num++;
        }
    }
    if (num != 0) {
        work->unkCAC = 1;
        if (num == 1) {
            work->unk1D6 = list[0];
        } else {
            work->unk1D6 = list[rand8() / (255 / num + 1)];
        }
        MgSeqModeNext();
        for (i = 0; i < 4; i++) {
            player = work->player[i];
            if (player->unk688 != fn_1_9DF8) {
                if (i == work->unk1D6) {
                    player->unk688 = fn_1_B5D8;
                } else {
                    player->unk688 = fn_1_B0B8;
                    if (player->unk482 == 5) {
                        player->unk470 = player->unk464;
                        player->unk484 = 0;
                    }
                }
                player->unk684->state = 0;
            }
            player->unk680 = 0;
            player->unk682 = 0;
        }
    } else {
        work->unk1D4 = 1;
    }
}

/* 138 insns */
void fn_1_B08(void)
{
    M515_PLAYER *player;
    M515_WORK *work;
    s32 i;

    work = lbl_1_bss_4->data;
    work->unk1D4 = 0;
    switch (work->unk1D0) {
    case 0:
        HuAudSStreamFadeOut(lbl_1_bss_0, 1000);
        work->unkCAC = 1;
        if (work->unk1D6 >= 0) {
            player = work->player[work->unk1D6];
            MgSeqWinnerSet1(player->unk002);
        } else {
            for (i = 0; i < 4; i++) {
                player = work->player[i];
                if (player->unk688 != fn_1_9DF8) {
                    player->unk688 = fn_1_B0B8;
                    player->unk684->state = 0;
                }
                player->unk680 = 0;
                player->unk682 = 0;
            }
            MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
        }
        work->unk1DA = 0;
        work->unk1D0++;
        break;
    case 1:
        break;
    }
    for (i = 0; i < 4; i++) {
        player = work->player[i];
        if (player->unk688) {
            if (player->unk688(player->unk684, player) && player->unk688 == fn_1_9DF8) {
                player->unk688 = fn_1_B0B8;
                player->unk684->state = 0;
            }
            if (player->unk688 == fn_1_9DF8) {
                fn_1_5FD0(player);
                fn_1_611C(player);
                omSetTra(player->unk68C, player->unk44C.x, player->unk44C.y, player->unk44C.z);
                omSetRot(player->unk68C, player->unk458.x, player->unk458.y, player->unk458.z);
            }
            if (player->unk688 == fn_1_D928) {
                player->unk688 = fn_1_B0B8;
                player->unk684->state = 0;
            }
        }
    }
}

/* 906 insns */
void fn_1_D30(void)
{
    M515_WORK *work;
    M515_PLAYER *p;
    s32 i;
    s32 j;
    s32 cnt;
    float t;

    work = lbl_1_bss_4->data;
    switch (work->unk1DA) {
    case 0:
        MgSeqModeChangeOff();
        work->unk1D2 = 0;
        work->unk1D0 = 0;
        work->unk1DA++;
        /* fallthrough */
    case 1:
        cnt = 0;
        for (i = 0; i < 4; i++) {
            p = work->player[i];
            if (p->unk688 == fn_1_B0B8 || p->unk688 == fn_1_B5D8) {
                cnt++;
            }
        }
        if (cnt < 4) {
            break;
        }
        if (work->unk1D6 < 0) {
            work->unk1D0 = 3;
            MgSeqModeNext();
            break;
        }
        p = work->player[work->unk1D6];
        p->unk688 = fn_1_BA64;
        work->unk1DA++;
        break;

    case 2:
        work->unk1D2++;
        if (work->unk1D2 == 20) {
            WipeColorSet(255, 255, 255);
            WipeCreate(2, 0, 60);
            work->unk1DA++;
        }
        t = work->unk1D2 / 60.0f;
        switch (work->unk1D6) {
        case -1:
            break;
        case 0:
            work->unk334.unk04 = 320.0f * (1.0f - t) + 640.0f * t;
            work->unk334.unk08 = 240.0f * (1.0f - t) + 480.0f * t;
            break;
        case 1:
            work->unk334.unk04 = 320.0f * (1.0f - t);
            work->unk334.unk08 = 240.0f * (1.0f - t) + 480.0f * t;
            break;
        case 2:
            work->unk334.unk04 = 320.0f * (1.0f - t) + 640.0f * t;
            work->unk334.unk08 = 240.0f * (1.0f - t);
            break;
        case 3:
            work->unk334.unk04 = 320.0f * (1.0f - t);
            work->unk334.unk08 = 240.0f * (1.0f - t);
            break;
        }
        fn_1_9958(&work->unk334);
        break;

    case 3:
        work->unk1D2++;
        if (work->unk1D2 > 60) {
            work->unk1D2 = 60;
        }
        t = work->unk1D2 / 60.0f;
        switch (work->unk1D6) {
        case -1:
            break;
        case 0:
            work->unk334.unk04 = 320.0f * (1.0f - t) + 640.0f * t;
            work->unk334.unk08 = 240.0f * (1.0f - t) + 480.0f * t;
            break;
        case 1:
            work->unk334.unk04 = 320.0f * (1.0f - t);
            work->unk334.unk08 = 240.0f * (1.0f - t) + 480.0f * t;
            break;
        case 2:
            work->unk334.unk04 = 320.0f * (1.0f - t) + 640.0f * t;
            work->unk334.unk08 = 240.0f * (1.0f - t);
            break;
        case 3:
            work->unk334.unk04 = 320.0f * (1.0f - t);
            work->unk334.unk08 = 240.0f * (1.0f - t);
            break;
        }
        fn_1_9958(&work->unk334);
        if (WipeCheckEnd()) {
            break;
        }
        work->unk1DA++;
        break;

    case 4:
        HuAudFXPlay(0x39E);
        WipeCreate(1, 0, 60);
        p = work->player[work->unk1D6];
        p->unk44C.x = 0.0f;
        p->unk44C.y = 25.0f;
        p->unk44C.z = 100.0f;
        p->unk458.x = 0.0f;
        p->unk458.y = 180.0f;
        p->unk458.z = 0.0f;
        p->unk688 = NULL;
        omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
        omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
        Hu3DShadowMultiSizeSet(0xF0, lbl_1_rodata_10[p->unk000]);
        Hu3DShadowMultiColSet(0x19, 0, 0, lbl_1_rodata_10[p->unk000]);
        CharMotionSet(p->unk002, p->unk68C->mtnId[1]);
        Hu3DCameraPerspectiveSet(lbl_1_rodata_10[p->unk000], 45.0f, 20.0f, 12000.0f, 1.2f);
        work->unk234[p->unk000].unk00.x = lbl_1_data_28[54];
        work->unk234[p->unk000].unk00.y = lbl_1_data_28[55];
        work->unk234[p->unk000].unk00.z = lbl_1_data_28[56];
        work->unk234[p->unk000].unk0C.x = lbl_1_data_28[57];
        work->unk234[p->unk000].unk0C.y = lbl_1_data_28[58];
        work->unk234[p->unk000].unk0C.z = lbl_1_data_28[59];
        work->unk1F4 = 1;
        Hu3DModelAttrReset(work->unk0D6, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk0D6, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(work->unk0D6, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(work->unk0D8, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk0DA, HU3D_ATTR_DISPOFF);
        fn_1_BF24(work, work->unk008, 0);
        fn_1_BF24(work, work->unk00A, 0);
        for (i = 0; i < 4; i++) {
            Hu3DModelAttrSet(work->unk00E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk016[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk01E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk026[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk02E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk036[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk03E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk046[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk04E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk056[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk05E[i][0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk05E[i][1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk06E[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk076[i][0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk076[i][1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk076[i][2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk076[i][3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk096[i][0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk096[i][1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk0A6[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk0AE[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk0B6[i][0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk0B6[i][1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk0B6[i][2], HU3D_ATTR_DISPOFF);
            p = work->player[i];
            for (j = 0; j < p->unk5E8; j++) {
                Hu3DModelAttrSet(p->unk488[j].unk00, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(p->unk488[j].unk04, HU3D_ATTR_DISPOFF);
            }
            for (j = 0; j < 25; j++) {
                if (p->unk5EA[0].unk000[j] >= 0) {
                    Hu3DModelAttrSet(p->unk5EA[0].unk000[j], HU3D_ATTR_DISPOFF);
                }
                if (p->unk5EA[1].unk000[j] >= 0) {
                    Hu3DModelAttrSet(p->unk5EA[1].unk000[j], HU3D_ATTR_DISPOFF);
                }
                if (p->unk5EA[2].unk000[j] >= 0) {
                    Hu3DModelAttrSet(p->unk5EA[2].unk000[j], HU3D_ATTR_DISPOFF);
                }
            }
        }
        work->unk1D2 = 0;
        work->unk1DA++;
        break;

    case 5:
        work->unk1D2++;
        t = work->unk1D2 / 120.0f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        p = work->player[work->unk1D6];
        p->unk44C.z = 100.0f * (1.0f - t) - 200.0f * t;
        omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
        if (WipeCheckEnd() == 0) {
            work->unk1DA++;
            work->unk1D2 = 0;
            p = work->player[work->unk1D6];
            Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[7], 0.0f, 5.0f, 0);
        }
        break;

    case 6:
        p = work->player[work->unk1D6];
        work->unk1D2++;
        if (work->unk1D2 == 54) {
            Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[0], 0.0f, 5.0f, 0);
        }
        if (work->unk1D2 >= 60) {
            work->unk1DA++;
        }
        t = work->unk1D2 / 60.0f;
        if (t > 1.0f) {
            t = 1.0f;
        }
        p->unk458.y = 180.0f * (1.0f - t);
        omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
        break;

    case 7:
        work->unk1D0 = 0;
        MgSeqModeNext();
        break;
    }

    for (i = 0; i < 4; i++) {
        p = work->player[i];
        if (p->unk688 != 0) {
            if ((*p->unk688)(p->unk684, p) != 0) {
                if (p->unk688 == fn_1_9DF8) {
                    p->unk688 = fn_1_B0B8;
                    p->unk684->state = 0;
                }
            }
            if (p->unk688 == fn_1_9DF8) {
                fn_1_5FD0(p);
                fn_1_611C(p);
                omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
                omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
            }
            if (p->unk688 == fn_1_D928) {
                p->unk688 = fn_1_B0B8;
                p->unk684->state = 0;
            }
        }
    }
}

/* 114 insns */
void fn_1_1B58(void)
{
    M515_WORK *work;
    M515_PLAYER *p;
    s32 i;
    s32 charNo;

    work = lbl_1_bss_4->data;
    switch (work->unk1D0) {
    case 0:
        p = work->player[work->unk1D6];
        Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[4], 0.0f, 5.0f, 0);
        charNo = p->unk000;
        if (!_CheckFlag(FLAG_MG_PRACTICE)) {
            GwPlayer[charNo].mgCoinBonus = 10;
        }
        work->unk1D2 = 0;
        work->unk1D0++;
        /* fallthrough */
    case 1:
        p = work->player[work->unk1D6];
        Hu3DModelAttrReset(p->unk68C->mdlId[0], HU3D_MOTATTR_LOOP);
        work->unk1D0++;
        break;

    case 2:
        break;

    case 3:
        for (i = 0; i < 4; i++) {
            p = work->player[i];
            Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[5], 0.0f, 5.0f, 0);
        }
        CharLoseVoicePlay(work->player[0]->unk002, work->player[1]->unk002,
                          work->player[2]->unk002, work->player[3]->unk002);
        work->unk1D0++;
        break;

    case 4:
        break;
    }
}

/* 1 insn */
void fn_1_1D20(void)
{
}

/* 15 insns */
void fn_1_1D24(void)
{
    M515_WORK *work;

    work = lbl_1_bss_4->data;
    fn_1_9920(&work->unk334);
}

/* 585 insns */
void fn_1_1D60(OMOBJ *obj)
{
    M515_PLAYER *p;
    int i;
    int j;
    M515_WORK *work;
    u16 *tbl;
    HuVecF vec = { -150.0f, 25.0f, 1000.0f };
    float rot[4] = { 180.0f, 90.0f, 270.0f, 0.0f };
    s16 pan[4] = { 0x30, 0x50, 0x30, 0x50 };

    p = obj->data;
    work = lbl_1_bss_4->data;
    p->unk00E = 0;
    p->unk000 = (s16)obj->work[0];
    p->unk002 = GwPlayerConf[p->unk000].charNo;
    p->unk004 = GwPlayerConf[p->unk000].padNo;
    p->unk00A = GwPlayerConf[p->unk000].type;
    p->unk00C = GwPlayerConf[p->unk000].dif;
    obj->mdlId[0] = CharModelCreate(p->unk002, 8);
    for (i = 0; i < 8; i++) {
        obj->mtnId[i] = CharMotionCreate(p->unk002, lbl_1_data_118[p->unk002][i]);
    }
    CharMotionSet(p->unk002, obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    Hu3DModelCameraSet(obj->mdlId[0], lbl_1_rodata_10[p->unk000]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharEffectLayerSet(4);
    CharModelStepFxSet(p->unk002, 1);
    CharMotionDataClose(p->unk002);
    tbl = lbl_1_data_1094[work->unk002[p->unk00E]];
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            p->unk010[i][j].unk024 = *tbl++;
            p->unk010[i][j].unk018.x = 150.0f * j - 300.0f;
            p->unk010[i][j].unk018.y = 0.0f;
            p->unk010[i][j].unk018.z = 150.0f * i - 300.0f;
        }
    }
    for (i = 0; i < 5; i++) {
        p->unk010[0][i].unk00C = NULL;
        p->unk010[0][i].unk008 = &p->unk010[1][i];
    }
    for (i = 0; i < 5; i++) {
        p->unk010[4][i].unk008 = NULL;
        p->unk010[4][i].unk00C = &p->unk010[3][i];
    }
    for (i = 0; i < 5; i++) {
        p->unk010[i][0].unk004 = NULL;
        p->unk010[i][0].unk000 = &p->unk010[i][1];
    }
    for (i = 0; i < 5; i++) {
        p->unk010[i][4].unk000 = NULL;
        p->unk010[i][4].unk004 = &p->unk010[i][3];
    }
    for (i = 1; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            p->unk010[i][j].unk00C = &p->unk010[i - 1][j];
            p->unk010[i][j].unk008 = &p->unk010[i + 1][j];
        }
    }
    for (i = 0; i < 5; i++) {
        for (j = 1; j < 4; j++) {
            p->unk010[i][j].unk004 = &p->unk010[i][j - 1];
            p->unk010[i][j].unk000 = &p->unk010[i][j + 1];
        }
    }
    p->unk010[0][2].unk00C = &p->unk424;
    p->unk010[4][2].unk008 = &p->unk3FC;
    p->unk3FC.unk00C = &p->unk010[4][2];
    p->unk3FC.unk000 = NULL;
    p->unk3FC.unk004 = NULL;
    p->unk3FC.unk008 = NULL;
    p->unk3FC.unk024 = 3;
    p->unk3FC.unk018.x = 0.0f;
    p->unk3FC.unk018.y = 25.0f;
    p->unk3FC.unk018.z = 450.0f;
    p->unk424.unk00C = NULL;
    p->unk424.unk000 = NULL;
    p->unk424.unk004 = NULL;
    p->unk424.unk008 = &p->unk010[0][2];
    p->unk424.unk024 = 4;
    p->unk424.unk018.x = 0.0f;
    p->unk424.unk018.y = 25.0f;
    p->unk424.unk018.z = -450.0f;
    p->unk3F8 = &p->unk3FC;
    if (p->unk000 == 0) {
        p->unk44C = vec;
        p->unk458.x = 0.0f;
        p->unk458.y = 90.0f;
        p->unk458.z = 0.0f;
        CharMotionSet(p->unk002, obj->mtnId[1]);
    } else {
        p->unk44C = p->unk3F8->unk018;
        p->unk458.x = 0.0f;
        p->unk458.y = 180.0f;
        p->unk458.z = 0.0f;
    }
    omSetTra(obj, p->unk44C.x, p->unk44C.y, p->unk44C.z);
    omSetRot(obj, p->unk458.x, p->unk458.y, p->unk458.z);
    p->unk482 = 0;
    p->unk484 = 15;
    p->unk486 = 5;
    p->unk480 = 0;
    p->unk47C = 0;
    p->unk47E = 0;
    p->unk464 = p->unk3F8->unk018;
    p->unk470 = p->unk3F8->unk018;
    p->unk680 = 0;
    p->unk682 = 0;
    p->unk684 = &work->unk2F4[p->unk000];
    p->unk688 = NULL;
    fn_1_73B0(p, 0);
    fn_1_73B0(p, 1);
    fn_1_73B0(p, 2);
    fn_1_7768(p, 0);
    fn_1_77F0(p, 1);
    fn_1_77F0(p, 2);
    fn_1_69B8(p, work);
    fn_1_6FE8(p);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (p->unk010[i][j].unk024 == 2) {
                p->unk010[i][j].unk014->unk24 = rand8() / 86 + 1;
                Hu3DModelRotSet(p->unk010[i][j].unk014->unk00, 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(p->unk010[i][j].unk014->unk00, 0.0f,
                                rot[p->unk010[i][j].unk014->unk24], 0.0f);
            }
        }
    }
    p->unk68C = obj;
    fn_1_E274(&p->unk690, 0, p->unk00C);
    CharModelVoicePanSet(p->unk002, pan[p->unk000]);
    obj->objFunc = fn_1_2684;
}

/* 210 insns */
void fn_1_2684(OMOBJ *obj)
{
    M515_PLAYER *p;
    M515_WORK *work;
    int i;
    int a;
    int b;

    work = lbl_1_bss_4->data;
    p = obj->data;
    fn_1_E548(p);
    if (work->unk1D4 != 0) {
        if (p->unk482 == 4) {
            p->unk682 = 0;
            if ((s16)fn_1_7878(p) != 0) {
                p->unk482 = 0;
            }
            fn_1_5FD0(p);
            fn_1_611C(p);
        } else if (p->unk482 == 3) {
            if (fn_1_6324(p, work) != 0) {
                p->unk482 = 0;
            }
        } else {
            if (p->unk00A != 0) {
                p->unk680 = fn_1_DD18(p);
            } else {
                p->unk680 = fn_1_7924(p);
            }
            if (p->unk680 == 0x20) {
                p->unk682 = 0;
                p->unk482 = 4;
                p->unk688 = fn_1_D928;
                return;
            }
            a = fn_1_5FD0(p);
            b = fn_1_611C(p);
            fn_1_6980(p);
            if (a != 0 && b != 0) {
                p->unk482 = fn_1_66D0(p);
                if (p->unk482 == 0 || p->unk482 == 2) {
                    if (p->unk682 > 0) {
                        p->unk482 = 3;
                        fn_1_6318(p);
                        p->unk682 = 0;
                    }
                }
            }
            switch (p->unk482) {
            case 0:
                if (obj->mtnId[0] != Hu3DMotionIDGet(obj->mdlId[0]) &&
                    obj->mtnId[0] != Hu3DMotionShiftIDGet(obj->mdlId[0])) {
                    Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[0], 0.0f, 5.0f,
                                       HU3D_MOTATTR_LOOP);
                }
                break;
            case 1:
            case 2:
                if (obj->mtnId[2] != Hu3DMotionIDGet(obj->mdlId[0]) &&
                    obj->mtnId[2] != Hu3DMotionShiftIDGet(obj->mdlId[0])) {
                    Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[2], 0.0f, 5.0f,
                                       HU3D_MOTATTR_LOOP);
                }
                break;
            case 3:
                Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[3], 0.0f, 5.0f,
                                   HU3D_MOTATTR_LOOP);
                break;
            }
            fn_1_81A8(p->unk684->owner, p);
        }
        if (p->unk482 != 5) {
            omSetTra(obj, p->unk44C.x, p->unk44C.y, p->unk44C.z);
            omSetRot(obj, p->unk458.x, p->unk458.y, p->unk458.z);
        }
        for (i = 0; i < p->unk5E8; i++) {
            fn_1_7BE8(&p->unk488[i], work);
        }
    }
}

/* 1 insns */
void fn_1_29CC(void) { }

/* 60 insns */
void fn_1_29D0(OMOBJ *obj)
{
    int i;
    M515_WORK *work;
    int j;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        fn_1_7E5C(&work->unk234[i], i);
        fn_1_9804(&work->unk2F4[i], &work->unk234[i], i);
    }
    fn_1_5C40(work);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            work->unk1DC[i][j] = 0;
        }
    }
    Hu3DLayerHookSet(1, (HU3DLAYERHOOK)fn_1_CC20);
    obj->objFunc = fn_1_2AC0;
}

/* 42 insns */
void fn_1_2AC0(OMOBJ *obj)
{
    M515_WORK *work;
    int i;
    HuVecF *q;
    HuVecF pos;

    work = obj->data;
    fn_1_5DB0(work);
    for (i = 0; i < 4; i++) {
        fn_1_7EE0(&work->unk234[i]);
        pos = work->player[i]->unk44C;
        q = &pos;
        fn_1_C958(i, q, work->unk1F4);
    }
}

/* 1 insns */
void fn_1_2B68(void) { }

/* 210 insns */
void fn_1_2B6C(M515_WORK *work)
{
    int i;

    work->unk000 = 0;
    for (i = 0; i < 4; i++) {
        int a = i / 2;
        int b = i % 2;

        Hu3DCameraCreate(lbl_1_rodata_10[i]);
        Hu3DCameraPerspectiveSet(lbl_1_rodata_10[i], 15.0f, 20.0f, 12000.0f, 1.17f);
        Hu3DCameraPosSet(lbl_1_rodata_10[i], 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 150.0f, 0.0f);
    }
    Hu3DCameraViewportSet(lbl_1_rodata_10[0], 8.0f, 20.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(lbl_1_rodata_10[1], 312.0f, 20.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(lbl_1_rodata_10[2], 8.0f, 220.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraViewportSet(lbl_1_rodata_10[3], 312.0f, 220.0f, 320.0f, 240.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(lbl_1_rodata_10[0], 0, 0, 319, 239);
    Hu3DCameraScissorSet(lbl_1_rodata_10[1], 321, 0, 319, 239);
    Hu3DCameraScissorSet(lbl_1_rodata_10[2], 0, 241, 319, 239);
    Hu3DCameraScissorSet(lbl_1_rodata_10[3], 321, 241, 319, 239);
    fn_1_9828(&work->unk334);
    fn_1_9958(&work->unk334);
}

/* 34 insns */
void fn_1_2EB4(M515_WORK *work)
{
    HU3DLIGHTID lightId;

    lightId = Hu3DGLightCreate(0.0f, 4800.0f, 3600.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
}

/* 226 insns */
void fn_1_2F3C(M515_WORK *work)
{
    int i;
    s16 a;
    s16 b;
    s16 t;

    for (i = 0; i < 3; i++) {
        work->unk002[i] = rand8() / 26;
    }
    work->unk1D8 = 0;
    work->unk0DC = -1;
    work->unk0DE = -1;
    for (i = 0; i < 17; i++) {
        work->unk10C[i] = -1;
    }
    for (i = 0; i < 8; i++) {
        work->unk0E0[i] = -1;
    }
    work->unk21C = 0;
    work->unk21E = 0;
    work->unk220 = 0;
    for (i = 0; i < 3; i++) {
        work->unk1F8[i] = i;
        work->unk204[i] = i;
        work->unk210[i] = i;
    }
    for (; i < 6; i++) {
        work->unk1F8[i] = 0;
        work->unk204[i] = 0;
        work->unk210[i] = i;
    }
    for (i = 2; i < 2; i++) {
        a = rand8() / 86;
        b = rand8() / 86;
        t = work->unk1F8[a];
        work->unk1F8[a] = work->unk1F8[b];
        work->unk1F8[b] = t;
        a = rand8() / 86;
        b = rand8() / 86;
        t = work->unk204[a];
        work->unk204[a] = work->unk204[b];
        work->unk204[b] = t;
        a = rand8() / 43;
        b = rand8() / 43;
        t = work->unk210[a];
        work->unk210[a] = work->unk210[b];
        work->unk210[b] = t;
    }
    a = rand8() / 43;
    b = rand8() / 43;
    t = work->unk210[a];
    work->unk210[a] = work->unk210[b];
    work->unk210[b] = t;
    work->unk1D4 = 0;
}

/* 2655 insns */
void fn_1_32C4(M515_WORK *work)
{
    int i;
    HuVecF pos = { 0.0f, 0.0f, 0.0f };
    HuVecF rot = { 0.0f, 0.0f, 0.0f };
    HuVecF rot2 = { 0.0f, 180.0f, 0.0f };
    HuVecF pos2 = { 0.0f, 400.0f, 0.0f };
    HuVecF pos3 = { 0.0f, 800.0f, 0.0f };
    HuVecF pos4 = { 0.0f, 0.0f, 0.0f };

    work->unk008 = Hu3DModelCreateData(lbl_1_data_2B8[10]);
    fn_1_5E88(work->unk008, pos, rot, 0, lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DModelDispOn(work->unk008);
    Hu3DModelShadowMapSet(work->unk008);
    work->unk00A = Hu3DModelCreateData(lbl_1_data_2B8[11]);
    fn_1_5E88(work->unk00A, pos, rot, 0, lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DModelDispOn(work->unk00A);
    work->unk00C = Hu3DModelCreateData(lbl_1_data_2B8[12]);
    fn_1_5E88(work->unk00C, pos4, rot, 0, lbl_1_rodata_10[0]);
    Hu3DModelAttrReset(work->unk00C, HU3D_MOTATTR_PAUSE);
    Hu3DModelDispOn(work->unk00C);
    Hu3DMotionSpeedSet(work->unk00C, 0.7f);
    work->unk0D6 = Hu3DModelCreateData(lbl_1_data_2B8[19]);
    fn_1_5E88(work->unk0D6, pos, rot, 0, lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    work->unk0D8 = Hu3DModelCreateData(lbl_1_data_2B8[20]);
    fn_1_5E88(work->unk0D8, pos, rot, 0, lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DModelShadowMapSet(work->unk0D8);
    work->unk0DA = Hu3DModelCreateData(lbl_1_data_2B8[21]);
    fn_1_5E88(work->unk0DA, pos, rot, 0, lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DModelShadowSet(work->unk0DA);
    i = 0;
    work->unk00E[i] = Hu3DModelCreateData(lbl_1_data_2B8[0]);
    fn_1_5E88(work->unk00E[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[0] = Hu3DJointMotionData(work->unk00E[i], lbl_1_data_3C8[0]);
    Hu3DMotionSet(work->unk00E[i], work->unk0F0[0]);
    work->unk016[i] = Hu3DModelCreateData(lbl_1_data_2B8[1]);
    fn_1_5E88(work->unk016[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[1] = Hu3DJointMotionData(work->unk016[i], lbl_1_data_3C8[1]);
    Hu3DMotionSet(work->unk016[i], work->unk0F0[1]);
    work->unk01E[i] = Hu3DModelCreateData(lbl_1_data_2B8[2]);
    fn_1_5E88(work->unk01E[i], pos, rot, 2, lbl_1_rodata_10[i]);
    work->unk026[i] = Hu3DModelCreateData(lbl_1_data_2B8[3]);
    fn_1_5E88(work->unk026[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[2] = Hu3DJointMotionData(work->unk026[i], lbl_1_data_3C8[2]);
    Hu3DMotionSet(work->unk026[i], work->unk0F0[2]);
    work->unk02E[i] = Hu3DModelCreateData(lbl_1_data_2B8[4]);
    fn_1_5E88(work->unk02E[i], pos, rot2, 6, lbl_1_rodata_10[i]);
    work->unk0F0[3] = Hu3DJointMotionData(work->unk02E[i], lbl_1_data_3C8[3]);
    Hu3DMotionSet(work->unk02E[i], work->unk0F0[3]);
    work->unk036[i] = Hu3DModelCreateData(lbl_1_data_2B8[5]);
    fn_1_5E88(work->unk036[i], pos, rot2, 6, lbl_1_rodata_10[i]);
    work->unk0F0[4] = Hu3DJointMotionData(work->unk036[i], lbl_1_data_3C8[4]);
    Hu3DMotionSet(work->unk036[i], work->unk0F0[4]);
    work->unk03E[i] = Hu3DModelCreateData(lbl_1_data_2B8[6]);
    fn_1_5E88(work->unk03E[i], pos, rot2, 6, lbl_1_rodata_10[i]);
    work->unk0F0[5] = Hu3DJointMotionData(work->unk03E[i], lbl_1_data_3C8[5]);
    Hu3DMotionSet(work->unk03E[i], work->unk0F0[5]);
    work->unk046[i] = Hu3DModelCreateData(lbl_1_data_2B8[7]);
    fn_1_5E88(work->unk046[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[6] = Hu3DJointMotionData(work->unk046[i], lbl_1_data_3C8[6]);
    Hu3DMotionSet(work->unk046[i], work->unk0F0[6]);
    work->unk04E[i] = Hu3DModelCreateData(lbl_1_data_2B8[8]);
    fn_1_5E88(work->unk04E[i], pos, rot, 2, lbl_1_rodata_10[i]);
    work->unk056[i] = Hu3DModelCreateData(lbl_1_data_2B8[9]);
    fn_1_5E88(work->unk056[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[7] = Hu3DJointMotionData(work->unk056[i], lbl_1_data_3C8[7]);
    Hu3DMotionSet(work->unk056[i], work->unk0F0[7]);
    work->unk05E[i][0] = Hu3DModelCreateData(lbl_1_data_2B8[13]);
    fn_1_5E88(work->unk05E[i][0], pos, rot2, 2, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk05E[i][0]);
    work->unk05E[i][1] = Hu3DModelLink(work->unk05E[0][0]);
    fn_1_5E88(work->unk05E[i][1], pos2, rot, 2, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk05E[i][1]);
    work->unk06E[i] = Hu3DModelCreateData(lbl_1_data_2B8[14]);
    fn_1_5E88(work->unk06E[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[8] = Hu3DJointMotionData(work->unk06E[i], lbl_1_data_3C8[8]);
    Hu3DMotionSet(work->unk06E[i], work->unk0F0[8]);
    work->unk076[i][0] = Hu3DModelCreateData(lbl_1_data_2B8[15]);
    fn_1_5E88(work->unk076[i][0], pos, rot, 5, lbl_1_rodata_10[i]);
    work->unk0F0[9] = Hu3DJointMotionData(work->unk076[i][0], lbl_1_data_3C8[9]);
    Hu3DMotionSet(work->unk076[i][0], work->unk0F0[9]);
    work->unk076[i][1] = Hu3DModelLink(work->unk076[0][0]);
    fn_1_5E88(work->unk076[i][1], pos2, rot, 5, lbl_1_rodata_10[i]);
    Hu3DMotionSet(work->unk076[i][1], work->unk0F0[9]);
    work->unk076[i][2] = Hu3DModelLink(work->unk076[0][0]);
    fn_1_5E88(work->unk076[i][2], pos2, rot2, 5, lbl_1_rodata_10[i]);
    Hu3DMotionSet(work->unk076[i][2], work->unk0F0[9]);
    work->unk076[i][3] = Hu3DModelLink(work->unk076[0][0]);
    fn_1_5E88(work->unk076[i][3], pos3, rot2, 5, lbl_1_rodata_10[i]);
    Hu3DMotionSet(work->unk076[i][3], work->unk0F0[9]);
    work->unk096[i][0] = Hu3DModelCreateData(lbl_1_data_2B8[16]);
    fn_1_5E88(work->unk096[i][0], pos, rot, 3, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk096[i][0]);
    work->unk096[i][1] = Hu3DModelLink(work->unk096[0][0]);
    fn_1_5E88(work->unk096[i][1], pos2, rot2, 3, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk096[i][1]);
    work->unk0A6[i] = Hu3DModelCreateData(lbl_1_data_2B8[17]);
    fn_1_5E88(work->unk0A6[i], pos, rot, 2, lbl_1_rodata_10[i]);
    work->unk0F0[10] = Hu3DJointMotionData(work->unk0A6[i], lbl_1_data_3C8[11]);
    Hu3DMotionSet(work->unk0A6[i], work->unk0F0[10]);
    work->unk0AE[i] = Hu3DModelCreateData(lbl_1_data_2B8[18]);
    fn_1_5E88(work->unk0AE[i], pos, rot, 6, lbl_1_rodata_10[i]);
    work->unk0F0[11] = Hu3DJointMotionData(work->unk0AE[i], lbl_1_data_3C8[12]);
    Hu3DMotionSet(work->unk0AE[i], work->unk0F0[11]);
    work->unk0F0[12] = Hu3DJointMotionData(work->unk0AE[i], lbl_1_data_3C8[13]);
    work->unk0B6[i][0] = Hu3DModelCreateData(lbl_1_data_2B8[23]);
    fn_1_5E88(work->unk0B6[i][0], pos, rot, 1, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk0B6[i][0]);
    work->unk0B6[i][1] = Hu3DModelCreateData(lbl_1_data_2B8[24]);
    fn_1_5E88(work->unk0B6[i][1], pos2, rot2, 1, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk0B6[i][1]);
    work->unk0B6[i][2] = Hu3DModelCreateData(lbl_1_data_2B8[25]);
    fn_1_5E88(work->unk0B6[i][2], pos3, rot, 1, lbl_1_rodata_10[i]);
    Hu3DModelShadowMapSet(work->unk0B6[i][2]);
    work->unk0CE[i] = Hu3DModelCreateData(lbl_1_data_2B8[22]);
    fn_1_5F2C(work->unk0CE[i], pos, rot, 7, lbl_1_rodata_10[i]);
    work->unk0F0[13] = Hu3DJointMotionData(work->unk0CE[i], lbl_1_data_3C8[10]);
    Hu3DMotionShapeSet(work->unk0CE[i], work->unk0F0[13]);
    for (i++; i < 4; i++) {
        work->unk00E[i] = Hu3DModelLink(work->unk00E[0]);
        fn_1_5E88(work->unk00E[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk00E[i], work->unk0F0[0]);
        work->unk016[i] = Hu3DModelLink(work->unk016[0]);
        fn_1_5E88(work->unk016[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk016[i], work->unk0F0[1]);
        work->unk01E[i] = Hu3DModelLink(work->unk01E[0]);
        fn_1_5E88(work->unk01E[i], pos, rot, 2, lbl_1_rodata_10[i]);
        work->unk026[i] = Hu3DModelLink(work->unk026[0]);
        fn_1_5E88(work->unk026[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk026[i], work->unk0F0[2]);
        work->unk02E[i] = Hu3DModelLink(work->unk02E[0]);
        fn_1_5E88(work->unk02E[i], pos, rot2, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk02E[i], work->unk0F0[3]);
        work->unk036[i] = Hu3DModelLink(work->unk036[0]);
        fn_1_5E88(work->unk036[i], pos, rot2, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk036[i], work->unk0F0[4]);
        work->unk03E[i] = Hu3DModelLink(work->unk03E[0]);
        fn_1_5E88(work->unk03E[i], pos, rot2, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk03E[i], work->unk0F0[5]);
        work->unk046[i] = Hu3DModelLink(work->unk046[0]);
        fn_1_5E88(work->unk046[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk046[i], work->unk0F0[6]);
        work->unk04E[i] = Hu3DModelLink(work->unk04E[0]);
        fn_1_5E88(work->unk04E[i], pos, rot, 2, lbl_1_rodata_10[i]);
        work->unk056[i] = Hu3DModelLink(work->unk056[0]);
        fn_1_5E88(work->unk056[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk056[i], work->unk0F0[7]);
        work->unk05E[i][0] = Hu3DModelLink(work->unk05E[0][0]);
        fn_1_5E88(work->unk05E[i][0], pos, rot2, 2, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk05E[i][0]);
        work->unk05E[i][1] = Hu3DModelLink(work->unk05E[0][0]);
        fn_1_5E88(work->unk05E[i][1], pos2, rot, 2, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk05E[i][1]);
        work->unk06E[i] = Hu3DModelLink(work->unk06E[0]);
        fn_1_5E88(work->unk06E[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk06E[i], work->unk0F0[8]);
        work->unk076[i][0] = Hu3DModelLink(work->unk076[0][0]);
        fn_1_5E88(work->unk076[i][0], pos, rot, 5, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk076[i][0], work->unk0F0[9]);
        work->unk076[i][1] = Hu3DModelLink(work->unk076[0][0]);
        fn_1_5E88(work->unk076[i][1], pos2, rot, 5, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk076[i][1], work->unk0F0[9]);
        work->unk076[i][2] = Hu3DModelLink(work->unk076[0][0]);
        fn_1_5E88(work->unk076[i][2], pos2, rot2, 5, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk076[i][2], work->unk0F0[9]);
        work->unk076[i][3] = Hu3DModelLink(work->unk076[0][0]);
        fn_1_5E88(work->unk076[i][3], pos3, rot2, 5, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk076[i][3], work->unk0F0[9]);
        work->unk096[i][0] = Hu3DModelLink(work->unk096[0][0]);
        fn_1_5E88(work->unk096[i][0], pos, rot, 3, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk096[i][0]);
        work->unk096[i][1] = Hu3DModelLink(work->unk096[0][0]);
        fn_1_5E88(work->unk096[i][1], pos2, rot2, 3, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk096[i][1]);
        work->unk0A6[i] = Hu3DModelLink(work->unk0A6[0]);
        fn_1_5E88(work->unk0A6[i], pos, rot, 2, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk0A6[i], work->unk0F0[10]);
        work->unk0AE[i] = Hu3DModelLink(work->unk0AE[0]);
        fn_1_5E88(work->unk0AE[i], pos, rot, 6, lbl_1_rodata_10[i]);
        Hu3DMotionSet(work->unk0AE[i], work->unk0F0[11]);
        Hu3DMotionSet(work->unk0AE[i], work->unk0F0[12]);
        work->unk0CE[i] = Hu3DModelCreateData(lbl_1_data_2B8[22]);
        fn_1_5F2C(work->unk0CE[i], pos, rot, 7, lbl_1_rodata_10[i]);
        Hu3DMotionShapeSet(work->unk0CE[i], work->unk0F0[13]);
        work->unk0B6[i][0] = Hu3DModelLink(work->unk0B6[0][0]);
        fn_1_5E88(work->unk0B6[i][0], pos, rot, 1, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk0B6[i][0]);
        work->unk0B6[i][1] = Hu3DModelLink(work->unk0B6[0][1]);
        fn_1_5E88(work->unk0B6[i][1], pos2, rot2, 1, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk0B6[i][1]);
        work->unk0B6[i][2] = Hu3DModelLink(work->unk0B6[0][2]);
        fn_1_5E88(work->unk0B6[i][2], pos3, rot, 1, lbl_1_rodata_10[i]);
        Hu3DModelShadowMapSet(work->unk0B6[i][2]);
    }
    fn_1_CAF0(work, 0);
    fn_1_CB60(work, 1);
    fn_1_CB60(work, 2);
    fn_1_CB60(work, 3);
}

/* 41 insns */
void fn_1_5C40(M515_WORK *work)
{
    s32 i;

    for (i = 0; i < 119; i++) {
        work->unk34C[i].unk00C = NULL;
        work->unk34C[i].unk010 = &work->unk34C[i + 1];
        work->unk34C[i].unk008 = NULL;
    }
    work->unk34C[i].unk00C = NULL;
    work->unk34C[i].unk010 = NULL;
    work->unk34C[i].unk008 = NULL;
    work->unk344 = NULL;
    work->unk348 = &work->unk34C[0];
}

/* 25 insns */
M515_NODE *fn_1_5CE4(M515_WORK *work)
{
    M515_NODE *node;

    node = work->unk348;
    if (node) {
        work->unk348 = node->unk010;
        node->unk000 = -1;
        node->unk002 = -1;
        node->unk004 = 0;
        node->unk010 = work->unk344;
        if (node->unk010) {
            node->unk010->unk00C = node;
        }
        work->unk344 = node;
    }
    return node;
}

/* 26 insns */
void fn_1_5D48(M515_WORK *work, M515_NODE *node)
{
    if (node) {
        if (node->unk00C) {
            node->unk00C->unk010 = node->unk010;
        } else {
            work->unk344 = node->unk010;
        }
        if (node->unk010) {
            node->unk010->unk00C = node->unk00C;
        }
        node->unk00C = NULL;
        node->unk010 = work->unk348;
        node->unk008 = NULL;
        work->unk348 = node;
        node = NULL;
    }
}

/* 54 insns */
void fn_1_5DB0(M515_WORK *work)
{
    M515_NODE *node;
    M515_NODE *next;

    node = work->unk344;
    while (node) {
        next = node->unk010;
        if (node->unk008(node) != 0) {
            fn_1_5D48(work, node);
        }
        node = next;
    }
}

/* 41 insns */
void fn_1_5E88(HU3DMODELID model, HuVecF pos, HuVecF rot, s16 layer, u16 camBit)
{
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, layer);
    Hu3DModelCameraSet(model, camBit);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
}

/* 41 insns */
void fn_1_5F2C(HU3DMODELID model, HuVecF pos, HuVecF rot, s16 layer, u16 camBit)
{
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelLayerSet(model, layer);
    Hu3DModelCameraSet(model, camBit);
    Hu3DModelPosSet(model, pos.x, pos.y, pos.z);
    Hu3DModelRotSet(model, rot.x, rot.y, rot.z);
}

/* 70 insns */
s32 fn_1_5FD0(M515_PLAYER *p)
{
    s32 ret = 0;
    float t;

    p->unk484++;
    if (p->unk484 >= 15) {
        p->unk484 = 15;
        p->unk464 = p->unk470;
        ret = 1;
    }
    t = p->unk484 / 15.0f;
    p->unk44C.x = (1.0f - t) * p->unk464.x + t * p->unk470.x;
    p->unk44C.y = (1.0f - t) * p->unk464.y + t * p->unk470.y;
    p->unk44C.z = (1.0f - t) * p->unk464.z + t * p->unk470.z;
    return ret;
}

/* 13 insns */
void fn_1_60E8(M515_PLAYER *p, M515_CELL *cell)
{
    if (p->unk484 == 15) {
        p->unk470 = cell->unk018;
        p->unk3F8 = cell;
        p->unk484 = 0;
    }
}

/* 120 insns */
s32 fn_1_611C(M515_PLAYER *p)
{
    s32 ret = 0;
    float rot[4] = { 180.0f, 90.0f, 270.0f, 0.0f };
    float t;

    p->unk486++;
    if (p->unk486 >= 5) {
        p->unk486 = 5;
        p->unk47C = p->unk47E;
        ret = 1;
    }
    if ((p->unk47C == 2 && p->unk47E == 3) || (p->unk47C == 3 && p->unk47E == 2)) {
        rot[3] += 360.0f;
    }
    if (p->unk00E == 1) {
        if ((p->unk47C == 0 && p->unk47E == 3) || (p->unk47C == 3 && p->unk47E == 0)) {
            rot[3] += 360.0f;
        }
    } else {
        if ((p->unk47C == 2 && p->unk47E == 1) || (p->unk47C == 1 && p->unk47E == 2)) {
            rot[1] += 360.0f;
        }
    }
    t = p->unk486 / 5.0f;
    p->unk458.y = (1.0f - t) * rot[p->unk47C] + t * rot[p->unk47E];
    return ret;
}

/* 7 insns */
void fn_1_62FC(M515_PLAYER *p, s16 dir)
{
    if (p->unk486 == 5) {
        p->unk47E = dir;
        p->unk486 = 0;
    }
}

/* 3 insns */
void fn_1_6318(M515_PLAYER *p)
{
    p->unk480 = 0;
}

/* 235 insns */
s32 fn_1_6324(M515_PLAYER *p, M515_WORK *work)
{
    s32 ret = 0;
    s16 mot[4] = { 3, 2, 1, 0 };
    s16 motTbl[4][4] = { { 0, 2, 1, 3 }, { 1, 0, 3, 2 }, { 2, 3, 0, 1 }, { 3, 1, 2, 0 } };
    s16 pan[4] = { 0x30, 0x50, 0x30, 0x50 };
    M515_CELL *cell = NULL;
    M515_CELL *next = NULL;
    M515_ITEM *item;

    p->unk480++;
    if (p->unk480 == 10) {
        switch (p->unk47C) {
        case 0:
            cell = p->unk3F8->unk00C;
            if (cell) {
                if (cell->unk00C) {
                    next = cell->unk00C;
                }
            }
            break;
        case 1:
            cell = p->unk3F8->unk000;
            if (cell) {
                if (cell->unk000) {
                    next = cell->unk000;
                }
            }
            break;
        case 2:
            cell = p->unk3F8->unk004;
            if (cell) {
                if (cell->unk004) {
                    next = cell->unk004;
                }
            }
            break;
        case 3:
            cell = p->unk3F8->unk008;
            if (cell) {
                if (cell->unk008) {
                    next = cell->unk008;
                }
            }
            break;
        }
        if (cell && cell->unk024 == 2) {
            if (p->unk000 & 1) {
                HuAudFXPlayPan(0x6E2, pan[p->unk000]);
            } else {
                HuAudFXPlayPan(0x6E1, pan[p->unk000]);
            }
            omVibrate(p->unk000, 12, 4, 2);
            CharModelHitCreate(p->unk002);
            item = (M515_ITEM *)cell->unk014;
            if (next && next->unk024 == 0) {
                if (item) {
                    item->unk008 = cell->unk018;
                    item->unk014 = next->unk018;
                }
                next->unk024 = cell->unk024;
                cell->unk024 = 0;
                next->unk014 = cell->unk014;
                cell->unk014 = NULL;
            } else {
                if (item) {
                    item->unk008 = cell->unk018;
                    item->unk014 = cell->unk018;
                }
            }
            if (item) {
                item->unk020 = 1;
                item->unk002 = work->unk0E0[mot[motTbl[p->unk47C][item->unk024]]];
            }
        }
    }
    if (p->unk480 == 25) {
        Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
    if (p->unk480 > 29) {
        ret = 1;
    }
    return ret;
}

/* 172 insns */
s16 fn_1_66D0(M515_PLAYER *p)
{
    s32 ret;
    M515_CELL *cell;

    ret = 0;
    switch (p->unk680 & PAD_BUTTON_DIR) {
    case 0:
        break;
    case PAD_BUTTON_LEFT:
        ret = 2;
        cell = p->unk3F8->unk00C;
        if (cell) {
            if (cell->unk024 == 0 || cell->unk024 == 4) {
                fn_1_60E8(p, cell);
                if (cell->unk024 == 4) {
                    if (p->unk00E == 2) {
                        ret = 5;
                    } else {
                        p->unk688 = fn_1_9DF8;
                        ret = 4;
                    }
                } else {
                    ret = 1;
                }
            }
        }
        fn_1_62FC(p, 0);
        break;
    case PAD_BUTTON_RIGHT:
        ret = 2;
        cell = p->unk3F8->unk000;
        if (cell) {
            if (cell->unk024 == 0 || cell->unk024 == 4) {
                fn_1_60E8(p, cell);
                ret = 1;
            }
        }
        fn_1_62FC(p, 1);
        break;
    case PAD_BUTTON_DOWN:
        ret = 2;
        cell = p->unk3F8->unk004;
        if (cell) {
            if (cell->unk024 == 0 || cell->unk024 == 4) {
                fn_1_60E8(p, cell);
                ret = 1;
            }
        }
        fn_1_62FC(p, 2);
        break;
    case PAD_BUTTON_UP:
        ret = 2;
        cell = p->unk3F8->unk008;
        if (cell) {
            if (cell->unk024 == 0 || cell->unk024 == 4) {
                fn_1_60E8(p, cell);
                if (cell->unk024 == 4) {
                    if (p->unk00E == 2) {
                        ret = 5;
                    } else {
                        p->unk688 = fn_1_9DF8;
                        ret = 4;
                    }
                } else {
                    ret = 1;
                }
            }
        }
        fn_1_62FC(p, 3);
        break;
    }
    return ret;
}

/* 14 insns */
void fn_1_6980(M515_PLAYER *p)
{
    if (p->unk682 > 0) {
        p->unk682--;
    }
    switch (p->unk680 & PAD_TRIGGER_Z) {
    case PAD_TRIGGER_Z:
        p->unk682 = 5;
        break;
    }
}

/* 396 insns */
void fn_1_69B8(M515_PLAYER *p, M515_WORK *work)
{
    s32 i;
    s32 j;
    float scale = 1.1f;

    i = 0;
    if (work->unk0DC < 0) {
        work->unk0DC = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_364[1], HU_MEMNUM_OVL, HEAP_MODEL));
        p->unk488[i].unk00 = work->unk0DC;
        for (j = 0; j < 8; j++) {
            work->unk0E0[j] = Hu3DJointMotion(work->unk0DC, HuDataSelHeapReadNum(lbl_1_data_3A8[j], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        Hu3DMotionSet(work->unk0DC, work->unk0E0[4]);
    } else {
        p->unk488[i].unk00 = Hu3DModelLink(work->unk0DC);
    }
    Hu3DModelAttrSet(p->unk488[i].unk00, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(p->unk488[i].unk00, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(p->unk488[i].unk00, 3);
    Hu3DModelPosSet(p->unk488[i].unk00, 0.0f, 1.0f, 0.0f);
    Hu3DModelRotSet(p->unk488[i].unk00, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(p->unk488[i].unk00, lbl_1_rodata_10[p->unk000]);
    Hu3DModelScaleSet(p->unk488[i].unk00, scale, scale, scale);
    p->unk488[i].unk20 = 0;
    p->unk488[i].unk28 = 45.0f * (rand8() / 32);
    i++;
    while (i < 8) {
        p->unk488[i].unk00 = Hu3DModelLink(work->unk0DC);
        Hu3DModelAttrSet(p->unk488[i].unk00, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(p->unk488[i].unk00, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(p->unk488[i].unk00, 3);
        Hu3DModelPosSet(p->unk488[i].unk00, 0.0f, 1.0f, 0.0f);
        Hu3DModelRotSet(p->unk488[i].unk00, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(p->unk488[i].unk00, lbl_1_rodata_10[p->unk000]);
        Hu3DModelScaleSet(p->unk488[i].unk00, scale, scale, scale);
        p->unk488[i].unk20 = 0;
        p->unk488[i].unk28 = 45.0f * (rand8() / 32);
        i++;
    }
    i = 0;
    if (work->unk0DE < 0) {
        work->unk0DE = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_364[0], HU_MEMNUM_OVL, HEAP_MODEL));
        p->unk488[i].unk04 = work->unk0DE;
    } else {
        p->unk488[i].unk04 = Hu3DModelLink(work->unk0DE);
    }
    Hu3DModelAttrSet(p->unk488[i].unk04, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(p->unk488[i].unk04, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(p->unk488[i].unk04, 2);
    Hu3DModelPosSet(p->unk488[i].unk04, 0.0f, 0.5f, 0.0f);
    Hu3DModelRotSet(p->unk488[i].unk04, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(p->unk488[i].unk04, lbl_1_rodata_10[p->unk000]);
    Hu3DModelScaleSet(p->unk488[i].unk00, scale, scale, scale);
    i++;
    while (i < 8) {
        p->unk488[i].unk04 = Hu3DModelLink(work->unk0DE);
        Hu3DModelAttrSet(p->unk488[i].unk04, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(p->unk488[i].unk04, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(p->unk488[i].unk04, 2);
        Hu3DModelPosSet(p->unk488[i].unk04, 0.0f, 0.5f, 0.0f);
        Hu3DModelRotSet(p->unk488[i].unk04, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(p->unk488[i].unk04, lbl_1_rodata_10[p->unk000]);
        Hu3DModelScaleSet(p->unk488[i].unk04, scale, scale, scale);
        i++;
    }
}

/* 191 insns */
void fn_1_6FE8(M515_PLAYER *player)
{
    float rot[4] = { 180.0f, 90.0f, 270.0f, 0.0f };
    s32 i;
    s32 j;
    s32 k;

    player->unk5E8 = 0;
    for (i = 0, k = 0; i < 5; i++) {
        for (j = 0; j < 5; j++, k++) {
            if (player->unk010[i][j].unk024 == 2) {
                player->unk010[i][j].unk014 = &player->unk488[player->unk5E8];
                player->unk5E8++;
                player->unk010[i][j].unk014->unk08 = player->unk010[i][j].unk018;
                player->unk010[i][j].unk014->unk14 = player->unk010[i][j].unk018;
                player->unk010[i][j].unk014->unk24 = rand8() / 64;
                Hu3DModelAttrReset(player->unk010[i][j].unk014->unk00, HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(player->unk010[i][j].unk014->unk00,
                                player->unk010[i][j].unk018.x,
                                1.0f + player->unk010[i][j].unk018.y,
                                player->unk010[i][j].unk018.z);
                Hu3DModelRotSet(player->unk010[i][j].unk014->unk00, 0.0f,
                                rot[player->unk010[i][j].unk014->unk24], 0.0f);
                Hu3DModelAttrReset(player->unk010[i][j].unk014->unk04, HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(player->unk010[i][j].unk014->unk04,
                                player->unk010[i][j].unk018.x,
                                0.5f + player->unk010[i][j].unk018.y,
                                player->unk010[i][j].unk018.z);
            }
        }
    }
}

/* 51 insns */
void fn_1_72E4(M515_PLAYER *player)
{
    s32 i;
    M515_WORK *work = lbl_1_bss_4->data;

    for (i = 0; i < 8; i++) {
        Hu3DModelAttrSet(player->unk488[i].unk00, HU3D_ATTR_DISPOFF);
        Hu3DMotionSet(player->unk488[i].unk00, work->unk0E0[4]);
        Hu3DMotionTimeSet(player->unk488[i].unk00, 0.0f);
        Hu3DModelAttrSet(player->unk488[i].unk00, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(player->unk488[i].unk04, HU3D_ATTR_DISPOFF);
    }
}

/* 238 insns */
void fn_1_73B0(M515_PLAYER *player, s32 idx)
{
    s32 i;
    M515_WORK *work = lbl_1_bss_4->data;
    M515_LAYOUT *lay;
    s32 no;
    s32 pos;
    s32 row;
    s32 col;
    float rot;

    if (idx == 0) {
        lay = (M515_LAYOUT *)lbl_1_data_110C[work->unk002[idx]];
        rot = 0.0f;
    } else if (idx == 1) {
        lay = (M515_LAYOUT *)lbl_1_data_1134[work->unk002[idx]];
        rot = 180.0f;
    } else {
        lay = (M515_LAYOUT *)lbl_1_data_115C[work->unk002[idx]];
        rot = 0.0f;
    }
    for (i = 0; i < 25; i++, lay++) {
        if (lay->unk0 < 0) {
            break;
        }
        no = lay->unk0 - 1;
        if (work->unk10C[no] < 0) {
            work->unk10C[no] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_320[no], HU_MEMNUM_OVL, HEAP_MODEL));
            player->unk5EA[idx].unk000[i] = work->unk10C[no];
        } else {
            player->unk5EA[idx].unk000[i] = Hu3DModelLink(work->unk10C[no]);
        }
        if (idx == 1) {
            pos = 24 - lay->unk2;
        } else {
            pos = lay->unk2;
        }
        row = pos / 5;
        col = pos % 5;
        Hu3DModelAttrSet(player->unk5EA[idx].unk000[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(player->unk5EA[idx].unk000[i], HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(player->unk5EA[idx].unk000[i], 1);
        Hu3DModelPosSet(player->unk5EA[idx].unk000[i], 150.0f * col - 300.0f, 400.0f * idx, 150.0f * row - 300.0f);
        Hu3DModelRotSet(player->unk5EA[idx].unk000[i], 0.0f, lay->unk4 + rot, 0.0f);
        Hu3DModelCameraSet(player->unk5EA[idx].unk000[i], lbl_1_rodata_10[player->unk000]);
    }
    for (; i < 25; i++) {
        player->unk5EA[idx].unk000[i] = -1;
    }
}

/* 34 insns */
void fn_1_7768(M515_PLAYER *player, s32 idx)
{
    s32 i;

    for (i = 0; i < 25; i++) {
        if (player->unk5EA[idx].unk000[i] >= 0) {
            Hu3DModelAttrReset(player->unk5EA[idx].unk000[i], HU3D_ATTR_DISPOFF);
        }
    }
}

/* 34 insns */
void fn_1_77F0(M515_PLAYER *player, s32 idx)
{
    s32 i;

    for (i = 0; i < 25; i++) {
        if (player->unk5EA[idx].unk000[i] >= 0) {
            Hu3DModelAttrSet(player->unk5EA[idx].unk000[i], HU3D_ATTR_DISPOFF);
        }
    }
}

/* 43 insns */
s32 fn_1_7878(M515_PLAYER *player)
{
    s32 done = 0;
    M515_WORK *work = lbl_1_bss_4->data;

    if (player->unk688) {
        if (player->unk688(player->unk684, player)) {
            if (work->unkCAC == 0) {
                player->unk688 = NULL;
                done = 1;
            } else {
                player->unk688 = fn_1_B0B8;
                player->unk684->state = 0;
            }
        }
    }
    return done;
}

/* 177 insns */
u16 fn_1_7924(M515_PLAYER *player)
{
    u16 key = 0;
    float sx;
    float sy;
    float ang;
    float mag;

    sx = HuPadStkX[player->unk004];
    sy = HuPadStkY[player->unk004];
    if (player->unk00E == 1) {
        sx *= -1.0f;
        sy *= -1.0f;
    }
    ang = HuAtan(sx, sy);
    mag = HuAbs(sx) + HuAbs(sy);
    if (mag > 32.0f) {
        if (ang >= -30.0f && ang < 60.0f) {
            key = 0x1;
        } else if (ang >= 60.0 && ang < 150.0f) {
            key = 0x2;
        } else if (ang >= -120.0f && ang < -30.0f) {
            key = 0x4;
        } else {
            key = 0x8;
        }
    }
    if (HuPadBtnDown[player->unk004] & 0x800) {
        player->unk682 = 0;
        key = 0x20;
    } else if (HuPadBtnDown[player->unk004] & PAD_BUTTON_B) {
        key |= 0x10;
    }
    return key;
}

/* 157 insns */
void fn_1_7BE8(M515_PSUB *psub, M515_WORK *work)
{
    HuVecF pos;
    float t;

    switch (psub->unk20) {
    case 0:
        break;

    case 1:
        psub->unk22 = 0;
        Hu3DMotionSet(psub->unk00, psub->unk02);
        Hu3DModelAttrSet(psub->unk00, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(psub->unk00, HU3D_MOTATTR_PAUSE);
        psub->unk20++;

    case 2:
        psub->unk22++;
        if (psub->unk22 >= 2) {
            psub->unk20++;
        }
        break;

    case 3:
        psub->unk22++;
        if (psub->unk22 >= 10) {
            psub->unk20++;
        }
        t = (psub->unk22 - 2.0f) / 8.0f;
        pos.x = (1.0f - t) * psub->unk08.x + t * psub->unk14.x;
        pos.y = 1.0f + psub->unk14.y;
        pos.z = (1.0f - t) * psub->unk08.z + t * psub->unk14.z;
        Hu3DModelPosSet(psub->unk00, pos.x, pos.y, pos.z);
        pos.y = 0.5f + psub->unk14.y;
        Hu3DModelPosSet(psub->unk04, pos.x, pos.y, pos.z);
        break;

    case 4:
        psub->unk22++;
        if (psub->unk22 >= 20) {
            Hu3DMotionShiftSet(psub->unk00, work->unk0E0[7], 0.0f, 3.0f, HU3D_MOTATTR_LOOP);
            psub->unk20++;
        }
        break;

    case 5:
        psub->unk22++;
        if (psub->unk22 >= 100) {
            Hu3DModelAttrSet(psub->unk00, HU3D_MOTATTR_PAUSE);
        }
        break;
    }
}

/* 33 insns */
void fn_1_7E5C(M515_CAMMOVE *cam, s16 no)
{
    float *key;

    if (no == 0) {
        key = &lbl_1_data_28[0];
    } else {
        key = &lbl_1_data_28[6];
    }
    cam->unk00.x = key[0];
    cam->unk00.y = key[1];
    cam->unk00.z = key[2];
    cam->unk0C.x = key[3];
    cam->unk0C.y = key[4];
    cam->unk0C.z = key[5];
    cam->unk24 = 0;
    cam->unk26 = 0;
    cam->unk28 = no;
    cam->unk2C = 0;
}

/* 178 insns */
void fn_1_7EE0(M515_CAMMOVE *cam)
{
    float x;
    float y;
    float z;

    if (cam->unk00.x > 360.0f) {
        cam->unk00.x = cam->unk00.x - 360.0f;
    }
    if (cam->unk00.x < 0.0f) {
        cam->unk00.x += 360.0f;
    }
    if (cam->unk00.y > 360.0f) {
        cam->unk00.y = cam->unk00.y - 360.0f;
    }
    if (cam->unk00.y < 0.0f) {
        cam->unk00.y += 360.0f;
    }
    x = cam->unk0C.x + 0.5f * cam->unk00.z * HuCos(cam->unk00.y) * HuCos(cam->unk00.x);
    y = cam->unk0C.y + 0.5f * cam->unk00.z * HuSin(cam->unk00.y);
    z = cam->unk0C.z + 0.5f * cam->unk00.z * HuCos(cam->unk00.y) * HuSin(cam->unk00.x);
    Hu3DCameraPosSet(lbl_1_rodata_10[cam->unk28], x, y, z, 0.0f, 1.0f, 0.0f,
                     cam->unk0C.x, cam->unk0C.y, cam->unk0C.z);
}

/* 144 insns */
void fn_1_81A8(M515_CAMMOVE *cam, M515_PLAYER *player)
{
    float ofs;

    if (player->unk00E == 1) {
        if (player->unk44C.x > 150.0f) {
            ofs = player->unk44C.x - 150.0f;
        } else if (player->unk44C.x < -150.0f) {
            ofs = 0.5f * (150.0f + player->unk44C.x);
        } else {
            ofs = 0.0f;
        }
    } else {
        if (player->unk44C.x > 150.0f) {
            ofs = 0.5f * (player->unk44C.x - 150.0f);
        } else if (player->unk44C.x < -150.0f) {
            ofs = 150.0f + player->unk44C.x;
        } else {
            ofs = 0.0f;
        }
    }
    if (player->unk00E == 1) {
        cam->unk0C.x = ofs - 25.0f;
    } else {
        cam->unk0C.x = 25.0f + ofs;
    }
    if (player->unk44C.z > 150.0f) {
        ofs = player->unk44C.z - 150.0f;
    } else if (player->unk44C.z < -150.0f) {
        ofs = 150.0f + player->unk44C.z;
    } else {
        ofs = 0.0f;
    }
    if (ofs > 150.0f) {
        ofs = 150.0f;
    }
    if (ofs < -150.0f) {
        ofs = -150.0f;
    }
    if (player->unk00E == 1) {
        cam->unk0C.z = 75.0f + ofs;
    } else {
        cam->unk0C.z = ofs - 75.0f;
    }
}

/* 195 insns */
s32 fn_1_83E8(M515_CAMMOVE *cam)
{
    s32 done = 0;
    M515_WORK *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 == 55) {
            fn_1_BE78(work, work->unk016[cam->unk28], 0);
            fn_1_BF24(work, work->unk026[cam->unk28], 1);
        }
        if (cam->unk26 >= 120) {
            fn_1_BE78(work, work->unk096[cam->unk28][0], 0);
            fn_1_BE78(work, work->unk076[cam->unk28][0], 0);
            fn_1_BE78(work, work->unk076[cam->unk28][1], 0);
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 120.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[0] * s + lbl_1_data_28[6] * t;
        cam->unk00.y = lbl_1_data_28[1] * s + lbl_1_data_28[7] * t;
        cam->unk00.z = lbl_1_data_28[2] * s + lbl_1_data_28[8] * t;
        cam->unk0C.x = lbl_1_data_28[3] * s + lbl_1_data_28[9] * t;
        cam->unk0C.y = lbl_1_data_28[4] * s + lbl_1_data_28[10] * t;
        cam->unk0C.z = lbl_1_data_28[5] * s + lbl_1_data_28[11] * t;
        break;
    }
    return done;
}

/* fn_1_86F4 -- 156 instructions */
s32 fn_1_86F4(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk18 = cam->unk0C;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 70) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 70.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[6] * s + lbl_1_data_28[12] * t;
        cam->unk00.y = lbl_1_data_28[7] * s + lbl_1_data_28[13] * t;
        cam->unk00.z = lbl_1_data_28[8] * s + lbl_1_data_28[14] * t;
        cam->unk0C.x = cam->unk18.x * s + lbl_1_data_28[15] * t;
        cam->unk0C.y = cam->unk18.y * s + lbl_1_data_28[16] * t;
        cam->unk0C.z = cam->unk18.z * s + lbl_1_data_28[17] * t;
        break;
    }
    return done;
}

/* fn_1_8964 -- 156 instructions */
s32 fn_1_8964(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 100) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 100.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[12] * s + lbl_1_data_28[18] * t;
        cam->unk00.y = lbl_1_data_28[13] * s + lbl_1_data_28[19] * t;
        cam->unk00.z = lbl_1_data_28[14] * s + lbl_1_data_28[20] * t;
        cam->unk0C.x = lbl_1_data_28[15] * s + lbl_1_data_28[21] * t;
        cam->unk0C.y = lbl_1_data_28[16] * s + lbl_1_data_28[22] * t;
        cam->unk0C.z = lbl_1_data_28[17] * s + lbl_1_data_28[23] * t;
        break;
    }
    return done;
}

/* fn_1_8BD4 -- 156 instructions */
s32 fn_1_8BD4(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 45) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 45.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[18] * s + lbl_1_data_28[24] * t;
        cam->unk00.y = lbl_1_data_28[19] * s + lbl_1_data_28[25] * t;
        cam->unk00.z = lbl_1_data_28[20] * s + lbl_1_data_28[26] * t;
        cam->unk0C.x = lbl_1_data_28[21] * s + lbl_1_data_28[27] * t;
        cam->unk0C.y = lbl_1_data_28[22] * s + lbl_1_data_28[28] * t;
        cam->unk0C.z = lbl_1_data_28[23] * s + lbl_1_data_28[29] * t;
        break;
    }
    return done;
}

/* fn_1_8E44 -- 156 instructions */
s32 fn_1_8E44(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk18 = cam->unk0C;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 70) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 70.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[24] * s + lbl_1_data_28[30] * t;
        cam->unk00.y = lbl_1_data_28[25] * s + lbl_1_data_28[31] * t;
        cam->unk00.z = lbl_1_data_28[26] * s + lbl_1_data_28[32] * t;
        cam->unk0C.x = cam->unk18.x * s + lbl_1_data_28[33] * t;
        cam->unk0C.y = cam->unk18.y * s + lbl_1_data_28[34] * t;
        cam->unk0C.z = cam->unk18.z * s + lbl_1_data_28[35] * t;
        break;
    }
    return done;
}

/* fn_1_90B4 -- 156 instructions */
s32 fn_1_90B4(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 100) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 100.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[30] * s + lbl_1_data_28[36] * t;
        cam->unk00.y = lbl_1_data_28[31] * s + lbl_1_data_28[37] * t;
        cam->unk00.z = lbl_1_data_28[32] * s + lbl_1_data_28[38] * t;
        cam->unk0C.x = lbl_1_data_28[33] * s + lbl_1_data_28[39] * t;
        cam->unk0C.y = lbl_1_data_28[34] * s + lbl_1_data_28[40] * t;
        cam->unk0C.z = lbl_1_data_28[35] * s + lbl_1_data_28[41] * t;
        break;
    }
    return done;
}

/* fn_1_9324 -- 156 instructions */
s32 fn_1_9324(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 45) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 45.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[36] * s + lbl_1_data_28[42] * t;
        cam->unk00.y = lbl_1_data_28[37] * s + lbl_1_data_28[43] * t;
        cam->unk00.z = lbl_1_data_28[38] * s + lbl_1_data_28[44] * t;
        cam->unk0C.x = lbl_1_data_28[39] * s + lbl_1_data_28[45] * t;
        cam->unk0C.y = lbl_1_data_28[40] * s + lbl_1_data_28[46] * t;
        cam->unk0C.z = lbl_1_data_28[41] * s + lbl_1_data_28[47] * t;
        break;
    }
    return done;
}

/* fn_1_9594 -- 156 instructions */
s32 fn_1_9594(M515_CAMMOVE *cam)
{
    s32 done = 0;
    void *work = lbl_1_bss_4->data;
    float t;
    float s;
    float rate;

    switch (cam->unk24) {
    case 0:
        cam->unk26 = 0;
        cam->unk18 = cam->unk0C;
        cam->unk24++;
    case 1:
        cam->unk26++;
        if (cam->unk26 >= 80) {
            cam->unk24 = 0;
            done = 1;
        }
        rate = (float)cam->unk26 / 80.0f;
        t = 1.0 - (0.5 + 0.5 * HuCos(180.0f * rate));
        s = 1.0f - t;
        cam->unk00.x = lbl_1_data_28[42] * s + lbl_1_data_28[48] * t;
        cam->unk00.y = lbl_1_data_28[43] * s + lbl_1_data_28[49] * t;
        cam->unk00.z = lbl_1_data_28[44] * s + lbl_1_data_28[50] * t;
        cam->unk0C.x = cam->unk18.x * s + lbl_1_data_28[51] * t;
        cam->unk0C.y = cam->unk18.y * s + lbl_1_data_28[52] * t;
        cam->unk0C.z = cam->unk18.z * s + lbl_1_data_28[53] * t;
        break;
    }
    return done;
}

/* 9 insns */
void fn_1_9804(M515_SEQ *seq, M515_CAMMOVE *cam, s32 idx)
{
    seq->timer = 0;
    seq->state = 0;
    seq->owner = cam;
    seq->index = idx;
    seq->func = NULL;
}

/* 62 insns */
void fn_1_9828(M515_SPLIT *split)
{
    split->unk00 = espEntry(DATANUM(DATA_m515, 0x43), 10, 0);
    espDrawNoSet(split->unk00, 0);
    espPosSet(split->unk00, 576.0f, 240.0f);
    espAttrSet(split->unk00, 1);
    split->unk02 = espEntry(DATANUM(DATA_m515, 0x44), 10, 0);
    espDrawNoSet(split->unk02, 0);
    espPosSet(split->unk02, 576.0f, 240.0f);
    espAttrSet(split->unk02, 1);
    split->unk04 = 640.0f;
    split->unk08 = 480.0f;
    split->unk0C = 0.0f;
}

/* 14 insns */
void fn_1_9920(M515_SPLIT *split)
{
    espKill(split->unk00);
    espKill(split->unk02);
}

/* 296 insns */
void fn_1_9958(M515_SPLIT *split)
{
    float unkX[4] = { 8.0f, -8.0f, 8.0f, -8.0f };
    float unkY[4] = { 20.0f, 20.0f, -20.0f, -20.0f };
    float splitX = split->unk04;
    float splitY = split->unk08;
    s32 unkW = 8;
    s32 unkH = 20;
    float unkFW = 8.0f;
    float unkFH = 20.0f;
    s32 i;

    i = 0;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], 0.0f, 0.0f, 16.0f + splitX, 40.0f + splitY, 0.0f, 1.0f);
    i++;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], splitX - 16.0f, 0.0f, 16.0f + (640.0f - splitX), 40.0f + splitY, 0.0f, 1.0f);
    i++;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], 0.0f, splitY - 40.0f, 16.0f + splitX, 40.0f + (480.0f - splitY), 0.0f, 1.0f);
    i++;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], splitX - 16.0f, splitY - 40.0f, 16.0f + (640.0f - splitX), 40.0f + (480.0f - splitY), 0.0f, 1.0f);
    i = 0;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], 0, 0, (u32)splitX, (u32)splitY);
    i++;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], (u32)splitX, 0, (u32)(640.0f - splitX), (u32)splitY);
    i++;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], 0, (u32)splitY, (u32)splitX, (u32)(480.0f - splitY));
    i++;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], (u32)splitX, (u32)splitY, (u32)(640.0f - splitX), (u32)(480.0f - splitY));
    espPosSet(split->unk00, 576.0f * (splitX / 640.0f), 240.0f);
    espPosSet(split->unk02, 288.0f, 480.0f * (splitY / 480.0f));
}

/* Inlined lane walk.  Must be `static inline` (plain `static` makes CW emit a
 * 25-instruction out-of-line copy the reference object does not have) and must
 * be defined ABOVE fn_1_9DF8, or each expansion costs 6 instructions per load
 * instead of 3.  Fork J's construct; see m433dll/player.c:3373 for the same
 * shape in an already-matched overlay. */
static inline void M515LaneDispOff(M515_LANE *lane)
{
    s32 i;

    for (i = 0; i < 25; i++) {
        if (lane->unk000[i] >= 0) {
            Hu3DModelAttrSet(lane->unk000[i], 1);
        }
    }
}

/* 1200 insns */
s32 fn_1_9DF8(M515_SEQ *seq, M515_PLAYER *player)
{
    s32 ret = 0;
    float ofs[4] = { -450.0f, -600.0f, -750.0f, -900.0f };
    s16 pan[4] = { 48, 80, 48, 80 };
    M515_WORK *work = lbl_1_bss_4->data;
    M515_WORK *work2;
    s32 i;
    s32 k;

    player->unk680 = 0;
    switch (seq->state) {
    case 0:
        seq->timer = 0;
        player->unk486 = 0;
        if (player->unk00E == 0) {
            player->unk47E = 0;
            seq->func = fn_1_86F4;
            player->unk470.z = ofs[0];
            player->unk470.y = 25.0f;
            fn_1_BF24(work, work->unk016[player->unk000], 1);
        } else {
            player->unk47E = 3;
            seq->func = fn_1_8E44;
            player->unk470.z = -ofs[0];
            player->unk470.y = 425.0f;
            fn_1_BF24(work, work->unk036[player->unk000], 1);
            fn_1_BE78(work, work->unk026[player->unk000], 0);
            fn_1_BE78(work, work->unk076[player->unk000][3], 0);
            fn_1_BE78(work, work->unk096[player->unk000][0], 0);
        }
        player->unk484 = 0;
        Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[2], 0.0f, 5.0f, 0x40000001);
        seq->state++;
    case 1:
        seq->timer++;
        if (seq->timer >= 15) {
            seq->state++;
        }
        break;

    case 2:
        if (player->unk00E == 0) {
            player->unk470.z = ofs[1];
        } else {
            player->unk470.z = -ofs[1];
        }
        player->unk484 = 0;
        seq->timer = 0;
        seq->state++;
    case 3:
        seq->timer++;
        if (seq->timer >= 15) {
            seq->state++;
        }
        break;

    case 4:
        if (player->unk00E == 0) {
            Hu3DModelAttrReset(work->unk076[player->unk000][0], 0x40000002);
            player->unk470.z = ofs[2];
        } else {
            Hu3DModelAttrReset(work->unk076[player->unk000][2], 0x40000002);
            player->unk470.z = -ofs[2];
        }
        if (player->unk000 & 1) {
            HuAudFXPlayPan(0x6E6, pan[player->unk000]);
        } else {
            HuAudFXPlayPan(0x6E5, pan[player->unk000]);
        }
        player->unk484 = 0;
        seq->timer = 0;
        seq->state++;
    case 5:
        seq->timer++;
        if (seq->timer >= 15) {
            if (player->unk00E == 0) {
                fn_1_BE78(work, work->unk00E[player->unk000], 1);
                fn_1_BE78(work, work->unk03E[player->unk000], 1);
                fn_1_BE78(work, work->unk046[player->unk000], 1);
                fn_1_BE78(work, work->unk04E[player->unk000], 1);
                fn_1_BE78(work, work->unk056[player->unk000], 1);
                fn_1_BE78(work, work->unk0AE[player->unk000], 0);
                Hu3DModelAttrReset(work->unk076[player->unk000][0], 0x40000002);
            } else {
                fn_1_BE78(work, work->unk00E[player->unk000], 1);
                fn_1_BE78(work, work->unk02E[player->unk000], 1);
                fn_1_BE78(work, work->unk056[player->unk000], 1);
                fn_1_BE78(work, work->unk06E[player->unk000], 1);
                Hu3DModelAttrReset(work->unk076[player->unk000][2], 0x40000002);
            }
            seq->state++;
        }
        break;

    case 6:
        if (player->unk00E == 0) {
            player->unk470.z = ofs[3];
        } else {
            player->unk470.z = -ofs[3];
        }
        player->unk484 = 0;
        seq->timer = 0;
        seq->state++;
    case 7:
        seq->timer++;
        if (seq->timer >= 15) {
            if (player->unk00E == 0) {
                fn_1_BE78(work, work->unk016[player->unk000], 1);
                Hu3DModelAttrSet(work->unk076[player->unk000][0], 0x40000004);
                Hu3DModelAttrReset(work->unk076[player->unk000][0], 0x40000002);
                for (i = 0; i < 25; i++) {
                    if (player->unk5EA[0].unk000[i] >= 0) {
                        Hu3DModelAttrSet(player->unk5EA[0].unk000[i], 1);
                    }
                }
            } else {
                fn_1_BE78(work, work->unk036[player->unk000], 1);
                Hu3DModelAttrSet(work->unk076[player->unk000][2], 0x40000004);
                Hu3DModelAttrReset(work->unk076[player->unk000][2], 0x40000002);
                M515LaneDispOff(&player->unk5EA[1]);
            }
            work2 = lbl_1_bss_4->data;
            for (k = 0; k < 8; k++) {
                Hu3DModelAttrSet(player->unk488[k].unk00, 1);
                Hu3DMotionSet(player->unk488[k].unk00, work2->unk0E0[4]);
                Hu3DMotionTimeSet(player->unk488[k].unk00, 0.0f);
                Hu3DModelAttrSet(player->unk488[k].unk00, 0x40000002);
                Hu3DModelAttrSet(player->unk488[k].unk04, 1);
            }
            seq->state++;
        }
        break;

    case 8:
        player->unk486 = 0;
        seq->timer = 0;
        if (player->unk00E == 0) {
            player->unk47E = 1;
        } else {
            player->unk47E = 2;
        }
        seq->state++;
    case 9:
        if (player->unk00E == 0) {
            if (player->unk47C == 1 && player->unk486 == 5) {
                if (player->unk68C->mtnId[0] != Hu3DMotionIDGet(player->unk68C->mdlId[0]) &&
                    player->unk68C->mtnId[0] != Hu3DMotionShiftIDGet(player->unk68C->mdlId[0])) {
                    Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f, 0x40000001);
                }
                player->unk47E = 3;
                player->unk486 = 0;
            }
        } else {
            if (player->unk47C == 2 && player->unk486 == 5) {
                if (player->unk68C->mtnId[0] != Hu3DMotionIDGet(player->unk68C->mdlId[0]) &&
                    player->unk68C->mtnId[0] != Hu3DMotionShiftIDGet(player->unk68C->mdlId[0])) {
                    Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f, 0x40000001);
                }
                player->unk47E = 0;
                player->unk486 = 0;
            }
        }
        seq->timer++;
        if (seq->timer >= 10) {
            seq->state++;
        }
        break;

    case 10:
        if (seq->func == NULL) {
            seq->timer = 0;
            seq->state++;
            if (player->unk00E == 0) {
                seq->func = fn_1_8964;
            } else {
                seq->func = fn_1_90B4;
            }
            if (player->unk000 & 1) {
                HuAudFXPlayPan(0x6E4, pan[player->unk000]);
            } else {
                HuAudFXPlayPan(0x6E3, pan[player->unk000]);
            }
            omVibrate(player->unk000, 15, 6, 6);
        }
        break;

    case 11:
        seq->timer++;
        if (seq->timer == 5) {
            if (player->unk00E == 0) {
                fn_1_BE78(work, work->unk026[player->unk000], 0);
                fn_1_BE78(work, work->unk02E[player->unk000], 0);
                fn_1_BE78(work, work->unk036[player->unk000], 0);
                fn_1_BE78(work, work->unk0B6[player->unk000][1], 0);
                fn_1_BE78(work, work->unk05E[player->unk000][0], 0);
                fn_1_BE78(work, work->unk076[player->unk000][2], 0);
                fn_1_BE78(work, work->unk076[player->unk000][3], 0);
                fn_1_BE78(work, work->unk096[player->unk000][1], 0);
                fn_1_BF24(work, work->unk0B6[player->unk000][0], 0);
                Hu3DModelLayerSet(work->unk03E[player->unk000], 2);
            } else {
                fn_1_BE78(work, work->unk046[player->unk000], 0);
                fn_1_BE78(work, work->unk04E[player->unk000], 0);
                fn_1_BE78(work, work->unk0B6[player->unk000][2], 0);
                fn_1_BE78(work, work->unk05E[player->unk000][1], 0);
                fn_1_BF24(work, work->unk0B6[player->unk000][1], 0);
            }
        }
        if (seq->timer == 85) {
            omVibrate(player->unk000, 15, 6, 6);
        }
        if (seq->timer >= 100) {
            if (player->unk00E == 1) {
                fn_1_BF24(work, work->unk05E[player->unk000][0], 0);
                fn_1_BF24(work, work->unk096[player->unk000][0], 0);
                fn_1_BF24(work, work->unk0A6[player->unk000], 0);
            }
            seq->state = 18;
        }
        {
            float t = seq->timer / 100.0f;
            float v = fn_1_BD10(work->unk096[player->unk000][player->unk00E], player->unk00E, t);
            player->unk464.y = 25.0f + v;
            player->unk470.y = 25.0f + v;
        }
        break;

    case 12:
        player->unk00E++;
        if (player->unk00E == 1) {
            seq->func = fn_1_8BD4;
            player->unk470.z = ofs[2];
            player->unk470.y = 425.0f;
        } else {
            seq->func = fn_1_9324;
            player->unk470.z = -ofs[2];
            player->unk470.y = 825.0f;
        }
        fn_1_C2B0(player);
        player->unk484 = 0;
        seq->timer = 0;
        if (player->unk68C->mtnId[2] != Hu3DMotionIDGet(player->unk68C->mdlId[0]) &&
            player->unk68C->mtnId[2] != Hu3DMotionShiftIDGet(player->unk68C->mdlId[0])) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[2], 0.0f, 5.0f, 0x40000001);
        }
        seq->state++;
    case 13:
        seq->timer++;
        if (seq->timer == 10) {
            if (player->unk00E == 1) {
                fn_1_BF24(work, work->unk00E[player->unk000], 0);
                fn_1_BF24(work, work->unk026[player->unk000], 0);
                fn_1_BF24(work, work->unk02E[player->unk000], 1);
                fn_1_BF24(work, work->unk046[player->unk000], 0);
                fn_1_BF24(work, work->unk04E[player->unk000], 1);
                fn_1_BF24(work, work->unk056[player->unk000], 1);
                fn_1_BF24(work, work->unk076[player->unk000][3], 0);
                Hu3DMotionSet(work->unk0AE[player->unk000], work->unk0F0[12]);
                fn_1_BF24(work, work->unk0AE[player->unk000], 1);
            } else {
                fn_1_BF24(work, work->unk016[player->unk000], 0);
                fn_1_BF24(work, work->unk046[player->unk000], 1);
                fn_1_BF24(work, work->unk076[player->unk000][1], 0);
                fn_1_BE78(work, work->unk0AE[player->unk000], 0);
            }
        }
        if (seq->timer >= 15) {
            if (player->unk00E == 1) {
                Hu3DModelAttrSet(work->unk076[player->unk000][1], 0x40000004);
                Hu3DModelAttrReset(work->unk076[player->unk000][1], 0x40000002);
            } else {
                Hu3DModelAttrSet(work->unk076[player->unk000][3], 0x40000004);
                Hu3DModelAttrReset(work->unk076[player->unk000][3], 0x40000002);
            }
            seq->state++;
        }
        break;

    case 14:
        if (player->unk00E == 1) {
            player->unk470.z = ofs[1];
        } else {
            player->unk470.z = -ofs[1];
        }
        player->unk484 = 0;
        seq->timer = 0;
        seq->state++;
    case 15:
        seq->timer++;
        if (seq->timer == 5 && player->unk00E == 2) {
            fn_1_BF24(work, work->unk06E[player->unk000], 1);
            Hu3DModelLayerSet(work->unk03E[player->unk000], 6);
        }
        if (seq->timer >= 15) {
            seq->state++;
        }
        break;

    case 16:
        if (player->unk00E == 1) {
            player->unk470.z = ofs[0];
        } else {
            player->unk470.z = -ofs[0];
        }
        player->unk484 = 0;
        seq->timer = 0;
        seq->state++;
    case 17:
        seq->timer++;
        if (seq->timer >= 15) {
            if (player->unk00E == 1) {
                fn_1_BF24(work, work->unk076[player->unk000][0], 0);
            } else {
                fn_1_BF24(work, work->unk01E[player->unk000], 0);
                fn_1_BF24(work, work->unk02E[player->unk000], 0);
                fn_1_BF24(work, work->unk076[player->unk000][2], 0);
                fn_1_BF24(work, work->unk026[player->unk000], 0);
            }
            seq->state = 0;
            ret = 1;
        }
        break;

    case 18:
        if (player->unk00E == 0) {
            Hu3DModelAttrReset(work->unk076[player->unk000][1], 0x40000002);
        } else {
            Hu3DModelAttrReset(work->unk076[player->unk000][3], 0x40000002);
        }
        if (player->unk000 & 1) {
            HuAudFXPlayPan(0x6E6, pan[player->unk000]);
        } else {
            HuAudFXPlayPan(0x6E5, pan[player->unk000]);
        }
        seq->timer = 0;
        seq->state++;
    case 19:
        seq->timer++;
        if (seq->timer >= 10) {
            seq->state = 12;
        }
        break;
    }
    if (seq->func) {
        if (seq->func(seq->owner)) {
            seq->func = NULL;
        }
    }
    return ret;
}

/* 328 insns */
s32 fn_1_B0B8(M515_SEQ *seq, M515_PLAYER *p)
{
    M515_WORK *work;
    HU3DMODEL *model;
    s32 ret = 0;
    s32 i;
    s32 endTra;
    s32 endRot;

    work = lbl_1_bss_4->data;
    switch (seq->state) {
    case 0:
        if (p->unk482 == 3) {
            if (fn_1_6324(p, work)) {
                seq->state++;
            }
        } else {
            endTra = fn_1_5FD0(p);
            endRot = fn_1_611C(p);
            if (endTra && endRot) {
                seq->state++;
            }
            Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
        omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
        omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
        break;

    case 1:
        if (p->unk68C->mtnId[0] != Hu3DMotionIDGet(p->unk68C->mdlId[0])
            && p->unk68C->mtnId[0] != Hu3DMotionShiftIDGet(p->unk68C->mdlId[0])) {
            Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        }
        break;
    }
    if (!(Hu3DModelAttrGet(work->unk0CE[p->unk000]) & HU3D_ATTR_DISPOFF)) {
        model = &Hu3DData[work->unk0CE[p->unk000]];
        if (model->motShapeWork.time >= model->motShapeWork.end) {
            model->motShapeWork.time = model->motShapeWork.end;
            Hu3DModelAttrSet(work->unk0CE[p->unk000], HU3D_ATTR_DISPOFF);
        }
    }
    for (i = 0; i < p->unk5E8; i++) {
        fn_1_7BE8(&p->unk488[i], work);
    }
    return ret;
}

/* 291 insns */
s32 fn_1_B5D8(M515_SEQ *seq, M515_PLAYER *p)
{
    s32 ret = 0;
    M515_WORK *work;
    s32 i;
    s32 endTra;
    s32 endRot;

    work = lbl_1_bss_4->data;
    switch (seq->state) {
    case 0:
        Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[2], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        seq->state++;
        /* fallthrough */
    case 1:
        endTra = fn_1_5FD0(p);
        endRot = fn_1_611C(p);
        if (endTra && endRot) {
            if (p->unk68C->mtnId[0] != Hu3DMotionIDGet(p->unk68C->mdlId[0])
                && p->unk68C->mtnId[0] != Hu3DMotionShiftIDGet(p->unk68C->mdlId[0])) {
                Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
            }
            seq->state++;
        }
        omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
        omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
        break;

    case 2:
        break;
    }
    for (i = 0; i < p->unk5E8; i++) {
        fn_1_7BE8(&p->unk488[i], work);
    }
    return ret;
}

/* 171 insns */
s32 fn_1_BA64(M515_SEQ *seq, M515_PLAYER *p)
{
    M515_WORK *work;
    s32 i;
    float t;

    work = lbl_1_bss_4->data;
    switch (seq->state) {
    case 2:
        Hu3DMotionShiftSet(p->unk68C->mdlId[0], p->unk68C->mtnId[1], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
        p->unk470.z = -900.0f;
        seq->func = fn_1_9594;
        seq->timer = 0;
        seq->state++;
        /* fallthrough */
    case 3:
        seq->timer++;
        if (seq->timer >= 135) {
            seq->state++;
        }
        if (seq->timer == 50) {
            Hu3DMotionSet(work->unk0AE[p->unk000], work->unk0F0[11]);
            Hu3DMotionTimeSet(work->unk0AE[p->unk000], 0.0f);
            Hu3DModelAttrReset(work->unk0AE[p->unk000], HU3D_MOTATTR_PAUSE);
        }
        t = seq->timer / 135.0f;
        p->unk44C.x = (1.0f - t) * p->unk464.x + t * p->unk470.x;
        p->unk44C.y = (1.0f - t) * p->unk464.y + t * p->unk470.y;
        p->unk44C.z = (1.0f - t) * p->unk464.z + t * p->unk470.z;
        omSetRot(p->unk68C, p->unk458.x, p->unk458.y, p->unk458.z);
        omSetTra(p->unk68C, p->unk44C.x, p->unk44C.y, p->unk44C.z);
        break;

    case 4:
        break;
    }
    for (i = 0; i < p->unk5E8; i++) {
        fn_1_7BE8(&p->unk488[i], work);
    }
    if (seq->func) {
        if (seq->func(seq->owner)) {
            seq->func = NULL;
        }
    }
    return 0;
}

/* 90 insns */
float fn_1_BD10(HU3DMODELID modelId, s32 idx, float t)
{
    float from[2] = { 0.0f, 400.0f };
    float to[2] = { 400.0f, 800.0f };
    float rate;
    float y;

    rate = 1.0 - (0.5 + 0.5 * cos(M_PI * (180.0f * t) / 180.0));
    if (rate > 1.0f) {
        rate = 1.0f;
    }
    y = (1.0f - rate) * from[idx] + rate * to[idx];
    Hu3DModelPosSet(modelId, 0.0f, y, 0.0f);
    return y;
}

/* 43 insns */
void fn_1_BE78(M515_WORK *work, HU3DMODELID modelId, s16 flag)
{
    M515_NODE *node;

    node = fn_1_5CE4(work);
    if (node) {
        if (flag) {
            node->unk008 = fn_1_BFD0;
        } else {
            node->unk008 = fn_1_C0D0;
        }
        node->unk000 = modelId;
    }
}

/* 43 insns */
void fn_1_BF24(M515_WORK *work, HU3DMODELID modelId, s16 flag)
{
    M515_NODE *node;

    node = fn_1_5CE4(work);
    if (node) {
        if (flag) {
            node->unk008 = fn_1_C150;
        } else {
            node->unk008 = fn_1_C26C;
        }
        node->unk000 = modelId;
    }
}

/* 64 insns */
s32 fn_1_BFD0(M515_NODE *node)
{
    s32 ret = 0;

    switch (node->unk004) {
    case 0:
        if (node->unk000 >= 0) {
            Hu3DModelAttrReset(node->unk000, HU3D_ATTR_DISPOFF);
            node->unk002 = Hu3DMotionIDGet(node->unk000);
            if (node->unk002 >= 0) {
                Hu3DMotionTimeSet(node->unk000, Hu3DMotionMaxTimeGet(node->unk000) - 1.0f);
                Hu3DModelAttrSet(node->unk000, HU3D_MOTATTR_REV);
                Hu3DModelAttrReset(node->unk000, HU3D_MOTATTR_PAUSE);
                node->unk004++;
            } else {
                ret = 1;
            }
        } else {
            ret = 1;
        }
        break;

    case 1:
        if (Hu3DMotionEndCheck(node->unk000)) {
            ret = fn_1_C0D0(node);
        }
        break;
    }
    return ret;
}

/* 32 insns */
s32 fn_1_C0D0(M515_NODE *node)
{
    if (node->unk000 >= 0) {
        Hu3DModelAttrReset(node->unk000, HU3D_ATTR_DISPOFF);
        node->unk002 = Hu3DMotionIDGet(node->unk000);
        if (node->unk002 >= 0) {
            Hu3DMotionTimeSet(node->unk000, 0.0f);
            Hu3DModelAttrSet(node->unk000, HU3D_MOTATTR_PAUSE);
        }
    }
    return 1;
}

/* 71 insns */
s32 fn_1_C150(M515_NODE *node)
{
    s32 ret = 0;

    switch (node->unk004) {
    case 0:
        if (node->unk000 >= 0) {
            node->unk002 = Hu3DMotionIDGet(node->unk000);
            if (node->unk002 >= 0) {
                Hu3DMotionTimeSet(node->unk000, 0.0f);
                Hu3DModelAttrReset(node->unk000, HU3D_MOTATTR_REV);
                Hu3DModelAttrReset(node->unk000, HU3D_MOTATTR_PAUSE);
                node->unk004++;
            } else {
                Hu3DModelAttrSet(node->unk000, HU3D_ATTR_DISPOFF);
                ret = 1;
            }
        } else {
            ret = 1;
        }
        break;

    case 1:
        if (Hu3DMotionEndCheck(node->unk000)) {
            node->unk004++;
        }
        break;

    case 2:
        Hu3DModelAttrSet(node->unk000, HU3D_ATTR_DISPOFF);
        ret = fn_1_C26C(node);
        break;
    }
    return ret;
}

/* 17 insns */
s32 fn_1_C26C(M515_NODE *node)
{
    if (node->unk000 >= 0) {
        Hu3DModelAttrSet(node->unk000, HU3D_ATTR_DISPOFF);
    }
    return 1;
}

/* 355 insns */
static inline void M515LaneDispOn(M515_LANE *lane)
{
    s32 i;

    for (i = 0; i < 25; i++) {
        if (lane->unk000[i] >= 0) {
            Hu3DModelAttrReset(lane->unk000[i], HU3D_ATTR_DISPOFF);
        }
    }
}

void fn_1_C2B0(M515_PLAYER *pl)
{
    M515_WORK *work;
    u16 *src;
    float y;
    s32 x;
    s32 z;
    s32 zi;
    s32 xi;
    s32 n;

    work = lbl_1_bss_4->data;
    if (pl->unk00E == 1) {
        src = (u16 *)lbl_1_data_10BC[work->unk002[pl->unk00E]];
        y = 400.0f * pl->unk00E;
        for (zi = 4; zi >= 0; zi--) {
            for (xi = 4; xi >= 0; xi--) {
                pl->unk010[zi][xi].unk024 = *src++;
                pl->unk010[zi][xi].unk018.y = y;
            }
        }
        pl->unk3F8 = &pl->unk424;
        pl->unk3FC.unk024 = 4;
        pl->unk3FC.unk018.y = 25.0f + y;
        pl->unk424.unk024 = 3;
        pl->unk424.unk018.y = 25.0f + y;
        M515LaneDispOn(&pl->unk5EA[1]);
    } else {
        src = (u16 *)lbl_1_data_10E4[work->unk002[pl->unk00E]];
        y = 400.0f * pl->unk00E;
        for (zi = 0; zi < 5; zi++) {
            for (xi = 0; xi < 5; xi++) {
                pl->unk010[zi][xi].unk024 = *src++;
                pl->unk010[zi][xi].unk018.y = y;
            }
        }
        pl->unk3F8 = &pl->unk3FC;
        pl->unk3FC.unk024 = 3;
        pl->unk3FC.unk018.y = 25.0f + y;
        pl->unk424.unk024 = 4;
        pl->unk424.unk018.y = 25.0f + y;
        M515LaneDispOn(&pl->unk5EA[2]);
    }
    {
        float rot[4] = { 180.0f, 90.0f, 270.0f, 0.0f };

        pl->unk5E8 = 0;
        for (z = 0, n = 0; z < 5; z++) {
            for (x = 0; x < 5; x++, n++) {
                if (pl->unk010[z][x].unk024 == 2) {
                    pl->unk010[z][x].unk014 = &pl->unk488[pl->unk5E8];
                    pl->unk5E8++;
                    pl->unk010[z][x].unk014->unk08 = pl->unk010[z][x].unk018;
                    pl->unk010[z][x].unk014->unk14 = pl->unk010[z][x].unk018;
                    pl->unk010[z][x].unk014->unk24 = rand8() / 64;
                    Hu3DModelAttrReset(pl->unk010[z][x].unk014->unk00, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(pl->unk010[z][x].unk014->unk00, pl->unk010[z][x].unk018.x,
                        1.0f + pl->unk010[z][x].unk018.y, pl->unk010[z][x].unk018.z);
                    Hu3DModelRotSet(pl->unk010[z][x].unk014->unk00, 0.0f,
                        rot[pl->unk010[z][x].unk014->unk24], 0.0f);
                    Hu3DModelAttrReset(pl->unk010[z][x].unk014->unk04, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(pl->unk010[z][x].unk014->unk04, pl->unk010[z][x].unk018.x,
                        0.5f + pl->unk010[z][x].unk018.y, pl->unk010[z][x].unk018.z);
                }
            }
        }
    }
    fn_1_E274(&pl->unk690, pl->unk00E, pl->unk00C);
}

/* 71 insns */
void fn_1_C83C(void)
{
    Hu3DShadowMultiCreate(15.0f, 20.0f, 12000.0f,
        lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DShadowMultiTPLvlSet(0.3f,
        lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
    Hu3DShadowMultiSizeSet(0x18,
        lbl_1_rodata_10[0] | lbl_1_rodata_10[1] | lbl_1_rodata_10[2] | lbl_1_rodata_10[3]);
}

/* 102 insns */
void fn_1_C958(s32 idx, HuVecF *pos, s32 mode)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF at = *pos;
    HuVecF eye;
    HuVecF side;
    HuVecF newUp;
    HuVecF dir;

    if (mode != 0) {
        eye.x = pos->x;
        eye.y = 800.0f + pos->y;
        eye.z = pos->z - 2400.0f;
    } else {
        eye.x = pos->x;
        eye.y = 1200.0f + pos->y;
        eye.z = pos->z;
    }
    PSVECSubtract(&at, &eye, &dir);
    PSVECNormalize(&dir, &dir);
    if (0.0f == dir.x && 0.0f == dir.z) {
        dir.z = 0.0001f;
    }
    PSVECCrossProduct(&up, &dir, &side);
    PSVECNormalize(&side, &side);
    PSVECCrossProduct(&dir, &side, &newUp);
    PSVECNormalize(&newUp, &newUp);
    Hu3DShadowMultiPosSet(&eye, &newUp, &at, lbl_1_rodata_10[idx]);
}

/* 28 insns */
void fn_1_CAF0(M515_WORK *work, s32 idx)
{
    Hu3DModelAttrReset(work->unk0B6[idx][0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk026[idx], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk0A6[idx], HU3D_ATTR_DISPOFF);
}

/* 48 insns */
void fn_1_CB60(M515_WORK *work, s32 idx)
{
    Hu3DModelAttrReset(work->unk0B6[idx][0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk016[idx], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk01E[idx], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk096[idx][0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk076[idx][0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk076[idx][1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->unk0A6[idx], HU3D_ATTR_DISPOFF);
}

/* 158 insns */
void fn_1_CC20(void)
{
    M515_WORK *work;
    M515_PLAYER *pl;
    s32 i;
    s32 j;
    s32 k;

    work = lbl_1_bss_4->data;
    if (omPauseChk() + omUPauseFlag != 0) {
        if (work->unk1D8 == 0) {
            work->unk1D8 = 1;
            for (i = 0; i < 4; i++) {
                pl = work->player[i];
                for (j = 0; j < 3; j++) {
                    if ((Hu3DModelAttrGet(work->unk0B6[i][j]) & HU3D_ATTR_DISPOFF) == 0) {
                        work->unk1DC[i][j] = 1;
                        for (k = 0; k < 25; k++) {
                            if (pl->unk5EA[j].unk000[k] >= 0) {
                                Hu3DModelAttrSet(pl->unk5EA[j].unk000[k], HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                }
                for (j = 0; j < pl->unk5E8; j++) {
                    Hu3DModelAttrSet(pl->unk488[j].unk00, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(pl->unk488[j].unk04, HU3D_ATTR_DISPOFF);
                }
            }
        }
    } else {
        if (work->unk1D8 != 0) {
            work->unk1D8 = 0;
            for (i = 0; i < 4; i++) {
                pl = work->player[i];
                for (j = 0; j < 3; j++) {
                    if (work->unk1DC[i][j] != 0) {
                        work->unk1DC[i][j] = 0;
                        for (k = 0; k < 25; k++) {
                            if (pl->unk5EA[j].unk000[k] >= 0) {
                                Hu3DModelAttrReset(pl->unk5EA[j].unk000[k], HU3D_ATTR_DISPOFF);
                            }
                        }
                    }
                }
                for (j = 0; j < pl->unk5E8; j++) {
                    Hu3DModelAttrReset(pl->unk488[j].unk00, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(pl->unk488[j].unk04, HU3D_ATTR_DISPOFF);
                }
            }
        }
    }
}

/* 144 insns */
void fn_1_CE98(M515_WORK *work)
{
    HuVecF pos[4] = {
        { 130.0f, 110.0f, -800.0f },
        { 30.0f, 100.0f, -780.0f },
        { -40.0f, 120.0f, -810.0f },
        { -120.0f, 110.0f, -800.0f },
    };
    float scale[4] = { 3.9f, 5.7f, 9.3f, 7.5f };
    s32 tbl[4] = { 15, 18, 16, 14 };
    M515_PLAYER *pl;
    s32 i;

    pl = work->player[0];
    for (i = 0; i < 4; i++) {
        work->unk130[i].unk0C = pl->unk488[i + 2].unk00;
        Hu3DModelAttrReset(work->unk130[i].unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(work->unk130[i].unk0C, pos[i].x, pos[i].y, pos[i].z);
        Hu3DModelRotSet(work->unk130[i].unk0C, 0.0f, 0.0f, 0.0f);
        work->unk130[i].unk10 = 0.0f;
        work->unk130[i].unk18 = scale[i];
        work->unk130[i].unk00 = 0;
        work->unk130[i].unk04 = tbl[i];
        work->unk130[i].unk08 = 0;
        work->unk130[i].unk1C = pos[i];
    }
}

/* 171 insns */
void fn_1_D0D8(M515_WORK *work)
{
    int i;
    float rot;
    float t;
    float y;

    for (i = 0; i < 4; i++) {
        switch (work->unk130[i].unk00) {
        case 0:
            break;

        case 1:
            work->unk130[i].unk08++;
            if (work->unk130[i].unk08 >= work->unk130[i].unk04) {
                work->unk130[i].unk00++;
            }
            t = (float)work->unk130[i].unk08 / (float)work->unk130[i].unk04;
            if (i < 2) {
                rot = 180.0 * t;
            } else {
                rot = -180.0f * t;
            }
            Hu3DModelRotSet(work->unk130[i].unk0C, 0.0f, rot, 0.0f);
            break;

        case 2:
            work->unk130[i].unk1C.z -= 6.0f;
            break;
        }

        work->unk130[i].unk10 += work->unk130[i].unk18;
        if (work->unk130[i].unk10 > 360.0f) {
            work->unk130[i].unk10 -= 360.0f;
        }
        y = work->unk130[i].unk1C.y + 3.0 * sin(M_PI * work->unk130[i].unk10 / 180.0);
        Hu3DModelPosSet(work->unk130[i].unk0C, work->unk130[i].unk1C.x, y, work->unk130[i].unk1C.z);
    }
}

/* 361 insns */
void fn_1_D384(M515_PLAYER *player)
{
    int x;
    int y;
    int i;
    int j;
    int k;
    u16 *src;
    M515_WORK *work;
    s16 rotSel;
    M515_WORK *work2;
    int n;
    float rotY;

    work = lbl_1_bss_4->data;
    if (player->unk00E == 1) {
        src = lbl_1_data_10BC[work->unk002[player->unk00E]];
        for (i = 4; i >= 0; i--) {
            for (j = 4; j >= 0; j--) {
                player->unk010[i][j].unk024 = *src++;
            }
        }
        player->unk3F8 = &player->unk424;
        rotY = 0.0f;
        rotSel = 3;
    } else {
        if (player->unk00E == 0) {
            src = lbl_1_data_1094[work->unk002[player->unk00E]];
        } else {
            src = lbl_1_data_10E4[work->unk002[player->unk00E]];
        }
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                player->unk010[i][j].unk024 = *src++;
            }
        }
        player->unk3F8 = &player->unk3FC;
        rotY = 180.0f;
        rotSel = 0;
    }

    player->unk44C = player->unk3F8->unk018;
    player->unk458.x = 0.0f;
    player->unk458.y = rotY;
    player->unk458.z = 0.0f;
    player->unk484 = 15;
    player->unk486 = 5;
    player->unk480 = 0;
    player->unk47C = rotSel;
    player->unk47E = rotSel;
    player->unk464 = player->unk3F8->unk018;
    player->unk470 = player->unk3F8->unk018;
    omSetTra(player->unk68C, player->unk44C.x, player->unk44C.y, player->unk44C.z);
    omSetRot(player->unk68C, player->unk458.x, player->unk458.y, player->unk458.z);

    work2 = lbl_1_bss_4->data;
    for (k = 0; k < 8; k++) {
        Hu3DModelAttrSet(player->unk488[k].unk00, HU3D_ATTR_DISPOFF);
        Hu3DMotionSet(player->unk488[k].unk00, work2->unk0E0[4]);
        Hu3DMotionTimeSet(player->unk488[k].unk00, 0.0f);
        Hu3DModelAttrSet(player->unk488[k].unk00, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(player->unk488[k].unk04, HU3D_ATTR_DISPOFF);
    }

    {
        float rotTbl[4] = { 180.0f, 90.0f, 270.0f, 0.0f };

        player->unk5E8 = 0;
        for (y = 0, n = 0; y < 5; y++) {
            for (x = 0; x < 5; x++, n++) {
                if (player->unk010[y][x].unk024 == 2) {
                    player->unk010[y][x].unk014 = &player->unk488[player->unk5E8];
                    player->unk5E8++;
                    player->unk010[y][x].unk014->unk08 = player->unk010[y][x].unk018;
                    player->unk010[y][x].unk014->unk14 = player->unk010[y][x].unk018;
                    player->unk010[y][x].unk014->unk24 = rand8() / 64;
                    Hu3DModelAttrReset(player->unk010[y][x].unk014->unk00, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(player->unk010[y][x].unk014->unk00,
                                    player->unk010[y][x].unk018.x,
                                    1.0f + player->unk010[y][x].unk018.y,
                                    player->unk010[y][x].unk018.z);
                    Hu3DModelRotSet(player->unk010[y][x].unk014->unk00, 0.0f,
                                    rotTbl[player->unk010[y][x].unk014->unk24], 0.0f);
                    Hu3DModelAttrReset(player->unk010[y][x].unk014->unk04, HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(player->unk010[y][x].unk014->unk04,
                                    player->unk010[y][x].unk018.x,
                                    0.5f + player->unk010[y][x].unk018.y,
                                    player->unk010[y][x].unk018.z);
                }
            }
        }
    }
}

/* 252 insns */
s32 fn_1_D928(M515_SEQ *seq, M515_PLAYER *player)
{
    M515_WORK *work;
    M515_CAMMOVE *cam;
    s32 ret;
    float px;
    float py;
    float pz;

    ret = 0;
    work = lbl_1_bss_4->data;
    player->unk680 = 0;
    cam = seq->owner;
    switch (seq->state) {
    case 0:
        Hu3DModelAttrReset(work->unk0CE[player->unk000], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk0CE[player->unk000], HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DMotionShapeTimeSet(work->unk0CE[player->unk000], 0.0f);
        if (Hu3DMotionIDGet(player->unk68C->mdlId[0]) != player->unk68C->mtnId[0] &&
            Hu3DMotionShiftIDGet(player->unk68C->mdlId[0]) != player->unk68C->mtnId[0]) {
            Hu3DMotionShiftSet(player->unk68C->mdlId[0], player->unk68C->mtnId[0], 0.0f, 5.0f,
                               HU3D_MOTATTR_LOOP);
        }
        seq->timer = 0;
        seq->state++;
        break;

    case 1:
        seq->timer++;
        if (seq->timer == 45) {
            fn_1_D384(player);
            fn_1_81A8(seq->owner, player);
        }
        if (seq->timer >= 90) {
            fn_1_E274(&player->unk690, player->unk00E, player->unk00C);
            Hu3DModelAttrSet(work->unk0CE[player->unk000], HU3D_ATTR_DISPOFF);
            seq->state = 0;
            seq->timer = 0;
            ret = 1;
        }
        break;
    }

    px = cam->unk0C.x +
         0.39f * cam->unk00.z * cos(M_PI * cam->unk00.y / 180.0) * cos(M_PI * cam->unk00.x / 180.0);
    py = cam->unk0C.y + 0.39f * cam->unk00.z * sin(M_PI * cam->unk00.y / 180.0);
    pz = cam->unk0C.z +
         0.39f * cam->unk00.z * cos(M_PI * cam->unk00.y / 180.0) * sin(M_PI * cam->unk00.x / 180.0);
    if (player->unk000 < 2) {
        py += 8.0f;
    } else {
        py -= 8.0f;
    }
    Hu3DModelPosSet(work->unk0CE[player->unk000], px, py, pz);
    Hu3DModelRotSet(work->unk0CE[player->unk000], -cam->unk00.y, 90.0f - cam->unk00.x, 0.0f);
    return ret;
}

/* 343 insns */
u16 fn_1_DD18(M515_PLAYER *player)
{
    M515_AI *ai;
    u16 ret = 0;
    s16 tbl0[4] = { 120, 60, 45, 30 };
    s16 tbl1[4] = { 60, 30, 15, 0 };
    s16 tbl2[4] = { 120, 60, 45, 30 };
    s16 tbl3[4] = { 120, 90, 60, 45 };
    s16 tbl4[4] = { 30, 0, 0, 0 };
    s16 tbl5[4] = { 60, 45, 30, 15 };

    ai = &player->unk690;
    switch (ai->unk00) {
    case 0:
        ai->unk02 = 0;
        ai->unk06 = 0;
        ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
        ai->unk00++;
        break;

    case 1:
        ai->unk02++;
        if (ai->unk02 > ai->unk08 + tbl0[player->unk00C]) {
            ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
            ai->unk02 = 0;
            ai->unk00++;
        }
        break;

    case 2:
        if (ai->unk0C[ai->unk06] == 0x10) {
            ai->unk00 = 10;
        } else if (ai->unk0C[ai->unk06] == 0x20) {
            ai->unk00 = 20;
        } else {
            ai->unk00 = 30;
        }
        break;

    case 10:
        ai->unk02++;
        if (ai->unk02 < ai->unk08 + tbl1[player->unk00C]) {
            break;
        }
        ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
        ai->unk00 = 11;
        /* fall through */
    case 11:
        ret = ai->unk0C[ai->unk06];
        ai->unk00 = 12;
        ai->unk02 = 0;
        break;

    case 12:
        ai->unk02++;
        if (ai->unk02 < ai->unk08 + tbl2[player->unk00C]) {
            break;
        }
        ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
        ai->unk06++;
        if (ai->unk0C[ai->unk06] == 0x10) {
            ai->unk00 = 10;
        } else if (ai->unk0C[ai->unk06] == 0x20) {
            ai->unk00 = 20;
        } else {
            ai->unk00 = 30;
        }
        ai->unk02 = 0;
        break;

    case 20:
        ai->unk02++;
        if (ai->unk02 < ai->unk08 + tbl3[player->unk00C]) {
            break;
        }
        ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
        ret = ai->unk0C[ai->unk06];
        ai->unk00 = 21;
        break;

    case 30:
        ret = ai->unk0C[ai->unk06];
        ai->unk02++;
        if (ai->unk02 < 15) {
            break;
        }
        ai->unk06++;
        if (ai->unk0C[ai->unk06] == 0x10) {
            ai->unk00 = 10;
        } else if (ai->unk0C[ai->unk06] == 0x20) {
            ai->unk00 = 20;
        } else if (ret == ai->unk0C[ai->unk06]) {
            ai->unk00 = 30;
        } else if (player->unk00C >= 2) {
            ai->unk00 = 30;
        } else {
            ai->unk00 = 31;
        }
        ai->unk02 = 0;
        break;

    case 31:
        ai->unk02++;
        if (ai->unk02 < ai->unk08 + 15) {
            break;
        }
        ai->unk08 = rand8() / (255 / tbl5[player->unk00C] + 1);
        ai->unk00 = 30;
        ai->unk02 = 0;
        break;
    }
    return ret;
}

/* The late .data block, moved below fn_1_DD18 so the five jumptables land at
   their reference addresses (0x400..0x530). See reorder.py. */
/* 0x530 */ u16 lbl_1_data_530[25] = { 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000 };
/* 0x562 */ u16 lbl_1_data_562[25] = { 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000 };
/* 0x594 */ u16 lbl_1_data_594[25] = { 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x5C6 */ u16 lbl_1_data_5C6[25] = { 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001 };
/* 0x5F8 */ u16 lbl_1_data_5F8[25] = { 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001 };
/* 0x62A */ u16 lbl_1_data_62A[25] = { 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000 };
/* 0x65C */ u16 lbl_1_data_65C[25] = { 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000 };
/* 0x68E */ u16 lbl_1_data_68E[25] = { 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001 };
/* 0x6C0 */ u16 lbl_1_data_6C0[25] = { 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001 };
/* 0x6F2 */ u16 lbl_1_data_6F2[25] = { 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0001, 0x0001, 0x0000, 0x0001, 0x0000, 0x0001, 0x0001, 0x0002, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x724 */ u16 lbl_1_data_724[25] = { 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x756 */ u16 lbl_1_data_756[25] = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x788 */ u16 lbl_1_data_788[25] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0002, 0x0001, 0x0001, 0x0002, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000 };
/* 0x7BA */ u16 lbl_1_data_7BA[25] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000 };
/* 0x7EC */ u16 lbl_1_data_7EC[25] = { 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x81E */ u16 lbl_1_data_81E[25] = { 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x850 */ u16 lbl_1_data_850[25] = { 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x882 */ u16 lbl_1_data_882[25] = { 0x0001, 0x0000, 0x0002, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0002, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x8B4 */ u16 lbl_1_data_8B4[25] = { 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001 };
/* 0x8E6 */ u16 lbl_1_data_8E6[25] = { 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0000, 0x0001, 0x0001 };
/* 0x918 */ u16 lbl_1_data_918[25] = { 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000 };
/* 0x94A */ u16 lbl_1_data_94A[25] = { 0x0001, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0000, 0x0001, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x97C */ u16 lbl_1_data_97C[25] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0002, 0x0002, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0002, 0x0002, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x9AE */ u16 lbl_1_data_9AE[25] = { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0002, 0x0002, 0x0002, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0x9E0 */ u16 lbl_1_data_9E0[25] = { 0x0001, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0002, 0x0001, 0x0000, 0x0002, 0x0002, 0x0002, 0x0000, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000 };
/* 0xA12 */ u16 lbl_1_data_A12[25] = { 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000 };
/* 0xA44 */ u16 lbl_1_data_A44[25] = { 0x0001, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0001, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0xA76 */ u16 lbl_1_data_A76[25] = { 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0002, 0x0000, 0x0002, 0x0002, 0x0000, 0x0002, 0x0002, 0x0002, 0x0000, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001 };
/* 0xAA8 */ u16 lbl_1_data_AA8[25] = { 0x0001, 0x0000, 0x0002, 0x0000, 0x0001, 0x0001, 0x0002, 0x0000, 0x0002, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001, 0x0001, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 };
/* 0xADA */ u16 lbl_1_data_ADA[25] = { 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0002, 0x0001, 0x0000, 0x0001, 0x0001, 0x0000, 0x0001, 0x0002, 0x0001, 0x0001, 0x0000, 0x0000, 0x0000, 0x0001 };
/* 0xB0C */ M515_LAYOUT lbl_1_data_B0C[5] = { { 16, 0, 0.0f }, { 6, 12, 0.0f }, { 1, 23, 0.0f }, { 4, 4, 0.0f }, { -1, 0, 0.0f } };
/* 0xB34 */ M515_LAYOUT lbl_1_data_B34[4] = { { 16, 0, 0.0f }, { 6, 12, 180.0f }, { 4, 18, 180.0f }, { -1, 0, 0.0f } };
/* 0xB54 */ M515_LAYOUT lbl_1_data_B54[7] = { { 16, 0, 0.0f }, { 8, 4, 0.0f }, { 7, 7, 0.0f }, { 3, 9, 270.0f }, { 6, 23, 0.0f }, { 1, 24, 0.0f }, { -1, 0, 0.0f } };
/* 0xB8C */ M515_LAYOUT lbl_1_data_B8C[6] = { { 6, 7, 180.0f }, { 4, 11, 0.0f }, { 7, 12, 0.0f }, { 6, 17, 0.0f }, { 16, 24, 180.0f }, { -1, 0, 0.0f } };
/* 0xBBC */ M515_LAYOUT lbl_1_data_BBC[8] = { { 8, 0, 0.0f }, { 4, 1, 0.0f }, { 3, 10, 90.0f }, { 6, 15, 0.0f }, { 7, 17, 0.0f }, { 1, 20, 0.0f }, { 16, 24, 180.0f }, { -1, 0, 0.0f } };
/* 0xBFC */ M515_LAYOUT lbl_1_data_BFC[7] = { { 16, 0, 0.0f }, { 8, 3, 0.0f }, { 2, 4, 0.0f }, { 6, 8, 0.0f }, { 7, 17, 0.0f }, { 4, 18, 0.0f }, { -1, 0, 0.0f } };
/* 0xC34 */ M515_LAYOUT lbl_1_data_C34[6] = { { 16, 0, 0.0f }, { 2, 4, 0.0f }, { 7, 12, 0.0f }, { 4, 13, 0.0f }, { 6, 17, 0.0f }, { -1, 0, 0.0f } };
/* 0xC64 */ M515_LAYOUT lbl_1_data_C64[6] = { { 4, 11, 0.0f }, { 6, 12, 180.0f }, { 7, 17, 0.0f }, { 1, 20, 0.0f }, { 16, 24, 180.0f }, { -1, 0, 0.0f } };
/* 0xC94 */ M515_LAYOUT lbl_1_data_C94[6] = { { 8, 0, 0.0f }, { 2, 1, 0.0f }, { 6, 16, 0.0f }, { 7, 17, 0.0f }, { 16, 24, 180.0f }, { -1, 0, 0.0f } };
/* 0xCC4 */ M515_LAYOUT lbl_1_data_CC4[6] = { { 16, 0, 0.0f }, { 7, 7, 0.0f }, { 4, 13, 0.0f }, { 6, 23, 0.0f }, { 1, 24, 0.0f }, { -1, 0, 0.0f } };
/* 0xCF4 */ M515_LAYOUT lbl_1_data_CF4[4] = { { 11, 6, 0.0f }, { 12, 16, 0.0f }, { 10, 19, 0.0f }, { -1, 0, 0.0f } };
/* 0xD14 */ M515_LAYOUT lbl_1_data_D14[6] = { { 11, 6, 0.0f }, { 12, 8, 270.0f }, { 12, 16, 90.0f }, { 9, 12, 0.0f }, { 11, 18, 180.0f }, { -1, 0, 0.0f } };
/* 0xD44 */ M515_LAYOUT lbl_1_data_D44[6] = { { 10, 10, 0.0f }, { 11, 11, 270.0f }, { 12, 13, 270.0f }, { 12, 20, 90.0f }, { 9, 21, 0.0f }, { -1, 0, 0.0f } };
/* 0xD74 */ M515_LAYOUT lbl_1_data_D74[5] = { { 2, 4, 0.0f }, { 10, 10, 0.0f }, { 11, 12, 270.0f }, { 9, 13, 0.0f }, { -1, 0, 0.0f } };
/* 0xD9C */ M515_LAYOUT lbl_1_data_D9C[5] = { { 10, 7, 0.0f }, { 12, 12, 270.0f }, { 9, 19, 0.0f }, { 9, 20, 0.0f }, { -1, 0, 0.0f } };
/* 0xDC4 */ M515_LAYOUT lbl_1_data_DC4[9] = { { 12, 0, 270.0f }, { 11, 4, 270.0f }, { 11, 10, 0.0f }, { 12, 13, 270.0f }, { 10, 14, 0.0f }, { 11, 19, 270.0f }, { 14, 21, 90.0f }, { 9, 23, 0.0f }, { -1, 0, 0.0f } };
/* 0xE0C */ M515_LAYOUT lbl_1_data_E0C[9] = { { 11, 0, 270.0f }, { 12, 3, 0.0f }, { 11, 9, 270.0f }, { 2, 10, 90.0f }, { 9, 15, 0.0f }, { 12, 16, 270.0f }, { 15, 18, 270.0f }, { 10, 20, 0.0f }, { -1, 0, 0.0f } };
/* 0xE54 */ M515_LAYOUT lbl_1_data_E54[9] = { { 9, 0, 0.0f }, { 9, 5, 0.0f }, { 11, 6, 270.0f }, { 10, 10, 0.0f }, { 12, 18, 270.0f }, { 9, 19, 0.0f }, { 14, 21, 90.0f }, { 10, 24, 0.0f }, { -1, 0, 0.0f } };
/* 0xE9C */ M515_LAYOUT lbl_1_data_E9C[8] = { { 12, 3, 270.0f }, { 10, 4, 0.0f }, { 14, 6, 90.0f }, { 11, 9, 270.0f }, { 10, 10, 0.0f }, { 9, 20, 0.0f }, { 10, 24, 0.0f }, { -1, 0, 0.0f } };
/* 0xEDC */ M515_LAYOUT lbl_1_data_EDC[8] = { { 10, 0, 0.0f }, { 10, 4, 0.0f }, { 12, 9, 180.0f }, { 11, 10, 270.0f }, { 9, 14, 0.0f }, { 15, 18, 270.0f }, { 12, 21, 180.0f }, { -1, 0, 0.0f } };
/* 0xF1C */ M515_LAYOUT lbl_1_data_F1C[5] = { { 13, 5, 90.0f }, { 4, 9, 0.0f }, { 4, 15, 0.0f }, { 17, 19, 0.0f }, { -1, 0, 0.0f } };
/* 0xF44 */ M515_LAYOUT lbl_1_data_F44[7] = { { 17, 0, 0.0f }, { 13, 1, 0.0f }, { 13, 3, 0.0f }, { 17, 4, 0.0f }, { 4, 16, 0.0f }, { 4, 18, 0.0f }, { -1, 0, 0.0f } };
/* 0xF7C */ M515_LAYOUT lbl_1_data_F7C[3] = { { 13, 10, 90.0f }, { 17, 14, 0.0f }, { -1, 0, 0.0f } };
/* 0xF94 */ M515_LAYOUT lbl_1_data_F94[3] = { { 13, 5, 90.0f }, { 17, 9, 0.0f }, { -1, 0, 0.0f } };
/* 0xFAC */ M515_LAYOUT lbl_1_data_FAC[5] = { { 17, 0, 0.0f }, { 17, 14, 0.0f }, { 13, 21, 90.0f }, { 13, 3, 0.0f }, { -1, 0, 0.0f } };
/* 0xFD4 */ M515_LAYOUT lbl_1_data_FD4[3] = { { 13, 6, 90.0f }, { 4, 18, 0.0f }, { -1, 0, 0.0f } };
/* 0xFEC */ M515_LAYOUT lbl_1_data_FEC[5] = { { 13, 0, 90.0f }, { 17, 6, 0.0f }, { 4, 16, 0.0f }, { 5, 17, 0.0f }, { -1, 0, 0.0f } };
/* 0x1014 */ M515_LAYOUT lbl_1_data_1014[5] = { { 17, 0, 0.0f }, { 13, 4, 90.0f }, { 13, 20, 90.0f }, { 17, 24, 0.0f }, { -1, 0, 0.0f } };
/* 0x103C */ M515_LAYOUT lbl_1_data_103C[5] = { { 13, 4, 0.0f }, { 3, 5, 90.0f }, { 4, 16, 0.0f }, { 5, 17, 0.0f }, { -1, 0, 0.0f } };
/* 0x1064 */ M515_LAYOUT lbl_1_data_1064[6] = { { 13, 12, 0.0f }, { 17, 14, 0.0f }, { 4, 17, 0.0f }, { 5, 19, 270.0f }, { 3, 20, 90.0f }, { -1, 0, 0.0f } };
/* 0x1094 */ u16 *lbl_1_data_1094[10] = { lbl_1_data_530, lbl_1_data_562, lbl_1_data_594, lbl_1_data_5C6, lbl_1_data_5F8, lbl_1_data_62A, lbl_1_data_65C, lbl_1_data_68E, lbl_1_data_6C0, lbl_1_data_6F2 };
/* 0x10BC */ u16 *lbl_1_data_10BC[10] = { lbl_1_data_724, lbl_1_data_756, lbl_1_data_788, lbl_1_data_7BA, lbl_1_data_7EC, lbl_1_data_81E, lbl_1_data_850, lbl_1_data_882, lbl_1_data_8B4, lbl_1_data_8E6 };
/* 0x10E4 */ u16 *lbl_1_data_10E4[10] = { lbl_1_data_918, lbl_1_data_94A, lbl_1_data_97C, lbl_1_data_9AE, lbl_1_data_9E0, lbl_1_data_A12, lbl_1_data_A44, lbl_1_data_A76, lbl_1_data_AA8, lbl_1_data_ADA };
/* 0x110C */ void *lbl_1_data_110C[10] = { &lbl_1_data_B0C, &lbl_1_data_B34, &lbl_1_data_B54, &lbl_1_data_B8C, &lbl_1_data_BBC, &lbl_1_data_BFC, &lbl_1_data_C34, &lbl_1_data_C64, &lbl_1_data_C94, &lbl_1_data_CC4 };
/* 0x1134 */ void *lbl_1_data_1134[10] = { &lbl_1_data_CF4, &lbl_1_data_D14, &lbl_1_data_D44, &lbl_1_data_D74, &lbl_1_data_D9C, &lbl_1_data_DC4, &lbl_1_data_E0C, &lbl_1_data_E54, &lbl_1_data_E9C, &lbl_1_data_EDC };
/* 0x115C */ void *lbl_1_data_115C[10] = { &lbl_1_data_F1C, &lbl_1_data_F44, &lbl_1_data_F7C, &lbl_1_data_F94, &lbl_1_data_FAC, &lbl_1_data_FD4, &lbl_1_data_FEC, &lbl_1_data_1014, &lbl_1_data_103C, &lbl_1_data_1064 };
/* 0x1184 */ s16 lbl_1_data_1184[11] = { 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001 };
/* 0x119A */ s16 lbl_1_data_119A[14] = { 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x11B6 */ s16 lbl_1_data_11B6[20] = { 0x0008, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0004, 0x0004, 0x0008, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x11DE */ s16 lbl_1_data_11DE[16] = { 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x11FE */ s16 lbl_1_data_11FE[18] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x1222 */ s16 lbl_1_data_1222[14] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0020 };
/* 0x123E */ s16 lbl_1_data_123E[13] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001 };
/* 0x1258 */ s16 lbl_1_data_1258[13] = { 0x0008, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x1272 */ s16 lbl_1_data_1272[19] = { 0x0001, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x1298 */ s32 lbl_1_data_1298[7] = { 0x00010002, 0x00020001, 0x00100001, 0x00100001, 0x00040010, 0x00040001, 0x00040001 };
/* 0x12B4 */ s16 lbl_1_data_12B4[23] = { 0x0008, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x12E2 */ s16 lbl_1_data_12E2[6] = { 0x0001, 0x0001, 0x0010, 0x0001, 0x0010, 0x0020 };
/* 0x12EE */ s16 lbl_1_data_12EE[11] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001, 0x0004, 0x0001 };
/* 0x1304 */ s32 lbl_1_data_1304[6] = { 0x00080004, 0x00040008, 0x00100008, 0x00100008, 0x00020002, 0x00080008 };
/* 0x131C */ s16 lbl_1_data_131C[17] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0020 };
/* 0x133E */ s16 lbl_1_data_133E[11] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001, 0x0004, 0x0001 };
/* 0x1354 */ s16 lbl_1_data_1354[13] = { 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x136E */ s16 lbl_1_data_136E[23] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x139C */ s16 lbl_1_data_139C[13] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x13B6 */ s16 lbl_1_data_13B6[12] = { 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0004, 0x0008, 0x0008, 0x0002, 0x0002, 0x0008, 0x0008 };
/* 0x13CE */ s16 lbl_1_data_13CE[33] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1410 */ s16 lbl_1_data_1410[15] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x142E */ s16 lbl_1_data_142E[10] = { 0x0008, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008 };
/* 0x1442 */ s16 lbl_1_data_1442[24] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0020 };
/* 0x1472 */ s16 lbl_1_data_1472[11] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x1488 */ s32 lbl_1_data_1488[6] = { 0x00080002, 0x00080010, 0x00080002, 0x00080008, 0x00080004, 0x00040008 };
/* 0x14A0 */ s16 lbl_1_data_14A0[17] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x14C2 */ s16 lbl_1_data_14C2[13] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x14DC */ s32 lbl_1_data_14DC[8] = { 0x00080004, 0x00080010, 0x00080010, 0x00080004, 0x00080008, 0x00020010, 0x00020010, 0x00020008 };
/* 0x14FC */ s32 lbl_1_data_14FC[15] = { 0x00010010, 0x00020002, 0x00010004, 0x00080004, 0x00040001, 0x00020010, 0x00020001, 0x00100001, 0x00040010, 0x00080004, 0x00100004, 0x00010010, 0x00010002, 0x00100001, 0x00100020 };
/* 0x1538 */ s16 lbl_1_data_1538[13] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1552 */ s16 lbl_1_data_1552[11] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x1568 */ s16 lbl_1_data_1568[21] = { 0x0010, 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1592 */ s16 lbl_1_data_1592[16] = { 0x0001, 0x0002, 0x0002, 0x0008, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x15B2 */ s16 lbl_1_data_15B2[12] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x15CA */ s16 lbl_1_data_15CA[15] = { 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0020 };
/* 0x15E8 */ s32 lbl_1_data_15E8[7] = { 0x00010002, 0x00100002, 0x00010002, 0x00010001, 0x00040010, 0x00040001, 0x00040001 };
/* 0x1604 */ s32 lbl_1_data_1604[6] = { 0x00080008, 0x00080002, 0x00080010, 0x00080004, 0x00100004, 0x00080008 };
/* 0x161C */ s16 lbl_1_data_161C[19] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x1642 */ s16 lbl_1_data_1642[15] = { 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x1660 */ s32 lbl_1_data_1660[6] = { 0x00080008, 0x00080002, 0x00080010, 0x00040008, 0x00100008, 0x00100020 };
/* 0x1678 */ s32 lbl_1_data_1678[10] = { 0x00010010, 0x00020002, 0x00010010, 0x00010010, 0x00010004, 0x00010010, 0x00040010, 0x00040001, 0x00020008, 0x00020020 };
/* 0x16A0 */ s16 lbl_1_data_16A0[13] = { 0x0001, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x16BA */ s16 lbl_1_data_16BA[16] = { 0x0008, 0x0008, 0x0008, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x16DA */ s16 lbl_1_data_16DA[28] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1712 */ s16 lbl_1_data_1712[15] = { 0x0001, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0008, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x1730 */ s32 lbl_1_data_1730[5] = { 0x00080008, 0x00080004, 0x00080010, 0x00080002, 0x00010020 };
/* 0x1744 */ s16 lbl_1_data_1744[29] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0008, 0x0004, 0x0020 };
/* 0x177E */ s16 lbl_1_data_177E[13] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001 };
/* 0x1798 */ s32 lbl_1_data_1798[7] = { 0x00100008, 0x00100008, 0x00040010, 0x00040008, 0x00020010, 0x00020008, 0x00080008 };
/* 0x17B4 */ s16 lbl_1_data_17B4[21] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x17DE */ s16 lbl_1_data_17DE[15] = { 0x0001, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0001, 0x0002, 0x0001, 0x0001 };
/* 0x17FC */ s16 lbl_1_data_17FC[21] = { 0x0010, 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0010, 0x0001, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008 };
/* 0x1826 */ s16 lbl_1_data_1826[16] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0001, 0x0020 };
/* 0x1846 */ s16 lbl_1_data_1846[12] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x185E */ s16 lbl_1_data_185E[16] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x187E */ s16 lbl_1_data_187E[16] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x189E */ s16 lbl_1_data_189E[15] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0004, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x18BC */ s16 lbl_1_data_18BC[11] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0010, 0x0008, 0x0004, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x18D2 */ s16 lbl_1_data_18D2[16] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0010, 0x0001, 0x0001, 0x0001 };
/* 0x18F2 */ s16 lbl_1_data_18F2[14] = { 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x190E */ s16 lbl_1_data_190E[15] = { 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0002, 0x0002, 0x0002, 0x0008, 0x0008, 0x0004, 0x0004, 0x0008 };
/* 0x192C */ s16 lbl_1_data_192C[23] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0008, 0x0001, 0x0001, 0x0002, 0x0010, 0x0001, 0x0001 };
/* 0x195A */ s16 lbl_1_data_195A[18] = { 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0008, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0008, 0x0010, 0x0001 };
/* 0x197E */ s16 lbl_1_data_197E[33] = { 0x0008, 0x0004, 0x0008, 0x0002, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0001, 0x0001, 0x0001, 0x0004, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x19C0 */ s16 lbl_1_data_19C0[19] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0020 };
/* 0x19E6 */ s16 lbl_1_data_19E6[16] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0001, 0x0002, 0x0010, 0x0001 };
/* 0x1A06 */ s16 lbl_1_data_1A06[23] = { 0x0008, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x1A34 */ s32 lbl_1_data_1A34[10] = { 0x00010001, 0x00100008, 0x00020002, 0x00010010, 0x00010004, 0x00100004, 0x00010004, 0x00100004, 0x00100001, 0x00010001 };
/* 0x1A5C */ s16 lbl_1_data_1A5C[23] = { 0x0001, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0004, 0x0001, 0x0010, 0x0002, 0x0001, 0x0004, 0x0004, 0x0001, 0x0008, 0x0001, 0x0001 };
/* 0x1A8A */ s16 lbl_1_data_1A8A[29] = { 0x0008, 0x0002, 0x0004, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0001, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0002, 0x0004, 0x0004, 0x0008 };
/* 0x1AC4 */ s16 lbl_1_data_1AC4[21] = { 0x0001, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0001, 0x0004, 0x0010, 0x0001, 0x0010, 0x0020 };
/* 0x1AEE */ s16 lbl_1_data_1AEE[15] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001, 0x0008, 0x0008, 0x0001, 0x0001, 0x0004, 0x0001 };
/* 0x1B0C */ s16 lbl_1_data_1B0C[15] = { 0x0008, 0x0010, 0x0008, 0x0001, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0002, 0x0002, 0x0008, 0x0008 };
/* 0x1B2A */ s16 lbl_1_data_1B2A[29] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x1B64 */ s32 lbl_1_data_1B64[11] = { 0x00010010, 0x00010002, 0x00010010, 0x00020010, 0x00020001, 0x00010001, 0x00080008, 0x00080002, 0x00100001, 0x00010001, 0x00040001 };
/* 0x1B90 */ s32 lbl_1_data_1B90[11] = { 0x00080010, 0x00040004, 0x00080010, 0x00080001, 0x00010002, 0x00020008, 0x00100008, 0x00100008, 0x00020008, 0x00040010, 0x00040008 };
/* 0x1BBC */ s32 lbl_1_data_1BBC[13] = { 0x00010010, 0x00010002, 0x00100002, 0x00010004, 0x00100004, 0x00010010, 0x00020001, 0x00100001, 0x00040010, 0x00040001, 0x00020004, 0x00020008, 0x00020020 };
/* 0x1BF0 */ s16 lbl_1_data_1BF0[17] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0008, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x1C12 */ s16 lbl_1_data_1C12[15] = { 0x0008, 0x0002, 0x0008, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0008, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008 };
/* 0x1C30 */ s16 lbl_1_data_1C30[37] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0010, 0x0008, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0001, 0x0001 };
/* 0x1C7A */ s16 lbl_1_data_1C7A[27] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0002, 0x0008, 0x0002, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0008, 0x0008, 0x0002, 0x0004, 0x0001, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x1CB0 */ s32 lbl_1_data_1CB0[16] = { 0x00080002, 0x00020008, 0x00040008, 0x00100008, 0x00010001, 0x00040010, 0x00040010, 0x00080004, 0x00020001, 0x00020002, 0x00080008, 0x00100008, 0x00020008, 0x00040010, 0x00040010, 0x00040008 };
/* 0x1CF0 */ s16 lbl_1_data_1CF0[31] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0001, 0x0010, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0001, 0x0001, 0x0020 };
/* 0x1D2E */ s16 lbl_1_data_1D2E[17] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0008, 0x0008, 0x0001, 0x0001, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x1D50 */ s16 lbl_1_data_1D50[19] = { 0x0008, 0x0002, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0010, 0x0008 };
/* 0x1D76 */ s16 lbl_1_data_1D76[23] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0001, 0x0001, 0x0001 };
/* 0x1DA4 */ s16 lbl_1_data_1DA4[25] = { 0x0001, 0x0004, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0008, 0x0004, 0x0008, 0x0008, 0x0001, 0x0001, 0x0002, 0x0001, 0x0004, 0x0010, 0x0001, 0x0001 };
/* 0x1DD6 */ s16 lbl_1_data_1DD6[40] = { 0x0008, 0x0004, 0x0004, 0x0002, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0010, 0x0001, 0x0001, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0008, 0x0001, 0x0001, 0x0002, 0x0001, 0x0001, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0020 };
/* 0x1E26 */ s16 lbl_1_data_1E26[27] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0020 };
/* 0x1E5C */ s16 lbl_1_data_1E5C[17] = { 0x0001, 0x0002, 0x0002, 0x0004, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1E7E */ s16 lbl_1_data_1E7E[13] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0008, 0x0002, 0x0008, 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x1E98 */ s16 lbl_1_data_1E98[27] = { 0x0010, 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x1ECE */ s16 lbl_1_data_1ECE[24] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0004, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0008, 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x1EFE */ s16 lbl_1_data_1EFE[27] = { 0x0008, 0x0008, 0x0008, 0x0001, 0x0001, 0x0008, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0001, 0x0002, 0x0001, 0x0001, 0x0001, 0x0008, 0x0008, 0x0008, 0x0002, 0x0004, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x1F34 */ s16 lbl_1_data_1F34[35] = { 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0001, 0x0010, 0x0004, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0004, 0x0008, 0x0008, 0x0001, 0x0001, 0x0004, 0x0010, 0x0004, 0x0002, 0x0004, 0x0001, 0x0001 };
/* 0x1F7A */ s16 lbl_1_data_1F7A[16] = { 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0008, 0x0001, 0x0002, 0x0001, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x1F9A */ s16 lbl_1_data_1F9A[20] = { 0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0001, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0001, 0x0004, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0008 };
/* 0x1FC2 */ s16 lbl_1_data_1FC2[25] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x1FF4 */ s16 lbl_1_data_1FF4[23] = { 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001, 0x0008, 0x0008, 0x0010, 0x0004, 0x0002, 0x0001, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x2022 */ s16 lbl_1_data_2022[30] = { 0x0008, 0x0008, 0x0008, 0x0002, 0x0004, 0x0004, 0x0002, 0x0001, 0x0001, 0x0008, 0x0008, 0x0002, 0x0008, 0x0010, 0x0008, 0x0001, 0x0004, 0x0004, 0x0002, 0x0008, 0x0010, 0x0004, 0x0008, 0x0002, 0x0004, 0x0001, 0x0002, 0x0008, 0x0001, 0x0020 };
/* 0x205E */ s16 lbl_1_data_205E[16] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0001, 0x0010, 0x0004, 0x0001, 0x0002, 0x0020 };
/* 0x207E */ s16 lbl_1_data_207E[17] = { 0x0001, 0x0004, 0x0001, 0x0008, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x20A0 */ s32 lbl_1_data_20A0[11] = { 0x00080008, 0x00080004, 0x00040002, 0x00020004, 0x00040008, 0x00100002, 0x00020008, 0x00040010, 0x00040008, 0x00020010, 0x00020008 };
/* 0x20CC */ s32 lbl_1_data_20CC[18] = { 0x00010004, 0x00020002, 0x00040001, 0x00100001, 0x00020010, 0x00020001, 0x00100004, 0x00020001, 0x00080004, 0x00100004, 0x00010010, 0x00010002, 0x00100002, 0x00010004, 0x00100004, 0x00010002, 0x00100002, 0x00010001 };
/* 0x2114 */ s32 lbl_1_data_2114[12] = { 0x00010008, 0x00040002, 0x00040001, 0x00040001, 0x00100001, 0x00080008, 0x00020004, 0x00010001, 0x00020010, 0x00080001, 0x00020001, 0x00020001 };
/* 0x2144 */ s32 lbl_1_data_2144[12] = { 0x00080008, 0x00080004, 0x00040002, 0x00020001, 0x00080008, 0x00010004, 0x00040002, 0x00020004, 0x00040008, 0x00100002, 0x00080010, 0x00080020 };
/* 0x2174 */ s32 lbl_1_data_2174[10] = { 0x00010002, 0x00010004, 0x00010010, 0x00010004, 0x00100004, 0x00010010, 0x00010010, 0x00010002, 0x00020004, 0x00040020 };
/* 0x219C */ s16 lbl_1_data_219C[17] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0008, 0x0001, 0x0010, 0x0008, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001 };
/* 0x21BE */ s16 lbl_1_data_21BE[22] = { 0x0010, 0x0008, 0x0004, 0x0002, 0x0002, 0x0004, 0x0004, 0x0008, 0x0010, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0002, 0x0004, 0x0010, 0x0004, 0x0008, 0x0008, 0x0008, 0x0008 };
/* 0x21EA */ s16 lbl_1_data_21EA[26] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0004, 0x0010, 0x0001, 0x0002, 0x0004, 0x0002, 0x0008, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0008, 0x0004, 0x0001, 0x0020 };
/* 0x221E */ s16 lbl_1_data_221E[26] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0008, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0004, 0x0010, 0x0008, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x2252 */ s16 lbl_1_data_2252[25] = { 0x0001, 0x0004, 0x0004, 0x0002, 0x0002, 0x0004, 0x0004, 0x0001, 0x0010, 0x0008, 0x0001, 0x0001, 0x0008, 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0001, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001 };
/* 0x2284 */ s16 lbl_1_data_2284[15] = { 0x0010, 0x0008, 0x0010, 0x0008, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008, 0x0004, 0x0004, 0x0002, 0x0008, 0x0010, 0x0020 };
/* 0x22A2 */ s16 lbl_1_data_22A2[21] = { 0x0001, 0x0010, 0x0001, 0x0008, 0x0001, 0x0002, 0x0002, 0x0001, 0x0008, 0x0004, 0x0004, 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x22CC */ s16 lbl_1_data_22CC[25] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0001, 0x0004, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0001, 0x0002, 0x0008, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x22FE */ s16 lbl_1_data_22FE[28] = { 0x0001, 0x0004, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x2336 */ s16 lbl_1_data_2336[32] = { 0x0001, 0x0008, 0x0004, 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0002, 0x0004, 0x0002, 0x0004, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0001, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x2376 */ s16 lbl_1_data_2376[18] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0001, 0x0004, 0x0002, 0x0008, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008, 0x0002, 0x0002, 0x0004, 0x0004, 0x0020 };
/* 0x239A */ s16 lbl_1_data_239A[31] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0008, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0004, 0x0008, 0x0008, 0x0002, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0001, 0x0020 };
/* 0x23D8 */ s32 lbl_1_data_23D8[7] = { 0x00010001, 0x00020010, 0x00020001, 0x00100001, 0x00040002, 0x00010004, 0x00010001 };
/* 0x23F4 */ s32 lbl_1_data_23F4[8] = { 0x00080004, 0x00080010, 0x00080010, 0x00080002, 0x00020001, 0x00020008, 0x00080004, 0x00040008 };
/* 0x2414 */ s16 lbl_1_data_2414[21] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0004, 0x0001, 0x0001 };
/* 0x243E */ s16 lbl_1_data_243E[21] = { 0x0001, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0004, 0x0008, 0x0004, 0x0001, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001 };
/* 0x2468 */ s16 lbl_1_data_2468[17] = { 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0002, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x248A */ s16 lbl_1_data_248A[15] = { 0x0001, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0020 };
/* 0x24A8 */ s32 lbl_1_data_24A8[7] = { 0x00010002, 0x00020001, 0x00100001, 0x00040010, 0x00010010, 0x00010004, 0x00010001 };
/* 0x24C4 */ s32 lbl_1_data_24C4[8] = { 0x00040008, 0x00040002, 0x00020002, 0x00080008, 0x00080008, 0x00040010, 0x00040010, 0x00040008 };
/* 0x24E4 */ s16 lbl_1_data_24E4[21] = { 0x0001, 0x0001, 0x0010, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x250E */ s16 lbl_1_data_250E[17] = { 0x0001, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0004, 0x0001 };
/* 0x2530 */ s16 lbl_1_data_2530[27] = { 0x0008, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0001, 0x0001, 0x0002, 0x0002, 0x0002, 0x0002, 0x0008, 0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0004, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x2566 */ s16 lbl_1_data_2566[31] = { 0x0001, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x25A4 */ s32 lbl_1_data_25A4[6] = { 0x00010010, 0x00010010, 0x00020010, 0x00020001, 0x00010001, 0x00040001 };
/* 0x25BC */ s16 lbl_1_data_25BC[17] = { 0x0002, 0x0008, 0x0004, 0x0004, 0x0001, 0x0004, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0002, 0x0008, 0x0008 };
/* 0x25DE */ s16 lbl_1_data_25DE[29] = { 0x0001, 0x0004, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x2618 */ s32 lbl_1_data_2618[7] = { 0x00020001, 0x00100001, 0x00020010, 0x00020001, 0x00040001, 0x00040001, 0x00040001 };
/* 0x2634 */ s16 lbl_1_data_2634[17] = { 0x0008, 0x0010, 0x0008, 0x0002, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x2656 */ s16 lbl_1_data_2656[29] = { 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0001, 0x0001 };
/* 0x2690 */ s16 lbl_1_data_2690[17] = { 0x0001, 0x0008, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x26B2 */ s16 lbl_1_data_26B2[14] = { 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0004, 0x0008, 0x0008, 0x0002, 0x0002, 0x0002, 0x0004, 0x0008, 0x0008 };
/* 0x26CE */ s16 lbl_1_data_26CE[38] = { 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0008, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x271A */ s16 lbl_1_data_271A[16] = { 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0004, 0x0002, 0x0001 };
/* 0x273A */ s16 lbl_1_data_273A[18] = { 0x0008, 0x0004, 0x0010, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0002, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x275E */ s16 lbl_1_data_275E[31] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0001, 0x0010, 0x0004, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0002, 0x0010, 0x0020 };
/* 0x279C */ s32 lbl_1_data_279C[7] = { 0x00010002, 0x00040001, 0x00100001, 0x00020001, 0x00100001, 0x00020001, 0x00010001 };
/* 0x27B8 */ s32 lbl_1_data_27B8[7] = { 0x00080002, 0x00040002, 0x00080010, 0x00080002, 0x00080008, 0x00080004, 0x00040008 };
/* 0x27D4 */ s32 lbl_1_data_27D4[10] = { 0x00010010, 0x00010002, 0x00100004, 0x00100004, 0x00010010, 0x00010010, 0x00010002, 0x00100002, 0x00100001, 0x00010001 };
/* 0x27FC */ s16 lbl_1_data_27FC[19] = { 0x0001, 0x0004, 0x0001, 0x0004, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0002, 0x0004, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x2822 */ s16 lbl_1_data_2822[25] = { 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0010, 0x0004, 0x0008, 0x0008, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0002, 0x0008, 0x0002, 0x0010, 0x0002, 0x0010, 0x0008 };
/* 0x2854 */ s16 lbl_1_data_2854[33] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0010, 0x0008, 0x0001, 0x0004, 0x0001, 0x0002, 0x0010, 0x0020 };
/* 0x2896 */ s16 lbl_1_data_2896[17] = { 0x0001, 0x0002, 0x0008, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0001 };
/* 0x28B8 */ s16 lbl_1_data_28B8[13] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0008, 0x0004, 0x0008, 0x0001, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x28D2 */ s16 lbl_1_data_28D2[24] = { 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x2902 */ s16 lbl_1_data_2902[19] = { 0x0001, 0x0004, 0x0001, 0x0002, 0x0002, 0x0008, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0004, 0x0002, 0x0004, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x2928 */ s16 lbl_1_data_2928[17] = { 0x0008, 0x0008, 0x0004, 0x0008, 0x0004, 0x0008, 0x0010, 0x0008, 0x0010, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0008, 0x0008 };
/* 0x294A */ s16 lbl_1_data_294A[31] = { 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0008, 0x0008, 0x0002, 0x0001, 0x0008, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0002, 0x0008, 0x0020 };
/* 0x2988 */ s32 lbl_1_data_2988[10] = { 0x00010002, 0x00100002, 0x00080001, 0x00020001, 0x00010002, 0x00080008, 0x00010001, 0x00040010, 0x00040001, 0x00040001 };
/* 0x29B0 */ s32 lbl_1_data_29B0[8] = { 0x00080008, 0x00080002, 0x00040002, 0x00080010, 0x00080004, 0x00100004, 0x00010008, 0x00080008 };
/* 0x29D0 */ s32 lbl_1_data_29D0[12] = { 0x00010004, 0x00020004, 0x00040001, 0x00100001, 0x00040002, 0x00100002, 0x00100001, 0x00020010, 0x00020001, 0x00020004, 0x00100004, 0x00010001 };
/* 0x2A00 */ s16 lbl_1_data_2A00[23] = { 0x0001, 0x0008, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0004, 0x0002, 0x0001, 0x0001, 0x0004, 0x0008, 0x0001, 0x0004, 0x0010, 0x0001, 0x0004, 0x0001, 0x0004, 0x0002, 0x0004, 0x0001 };
/* 0x2A2E */ s16 lbl_1_data_2A2E[17] = { 0x0008, 0x0008, 0x0008, 0x0010, 0x0002, 0x0004, 0x0002, 0x0008, 0x0010, 0x0008, 0x0004, 0x0004, 0x0002, 0x0002, 0x0001, 0x0004, 0x0020 };
/* 0x2A50 */ s16 lbl_1_data_2A50[41] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0008, 0x0002, 0x0002, 0x0008, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0001, 0x0002, 0x0020 };
/* 0x2AA2 */ s16 lbl_1_data_2AA2[16] = { 0x0001, 0x0002, 0x0004, 0x0001, 0x0004, 0x0001, 0x0008, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x2AC2 */ s16 lbl_1_data_2AC2[21] = { 0x0008, 0x0008, 0x0008, 0x0004, 0x0002, 0x0008, 0x0004, 0x0001, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008, 0x0002, 0x0010, 0x0002, 0x0008 };
/* 0x2AEC */ s32 lbl_1_data_2AEC[19] = { 0x00010002, 0x00010004, 0x00020004, 0x00010010, 0x00010002, 0x00100004, 0x00100004, 0x00020001, 0x00040001, 0x00100002, 0x00020001, 0x00100001, 0x00040010, 0x00020004, 0x00010002, 0x00100002, 0x00010004, 0x00100004, 0x00010001 };
/* 0x2B38 */ s16 lbl_1_data_2B38[21] = { 0x0001, 0x0004, 0x0001, 0x0002, 0x0008, 0x0001, 0x0004, 0x0001, 0x0008, 0x0002, 0x0004, 0x0001, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001 };
/* 0x2B62 */ s16 lbl_1_data_2B62[12] = { 0x0008, 0x0008, 0x0008, 0x0004, 0x0008, 0x0010, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0020 };
/* 0x2B7A */ s16 lbl_1_data_2B7A[25] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0001, 0x0010, 0x0004, 0x0001, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0008, 0x0004, 0x0020 };
/* 0x2BAC */ s32 lbl_1_data_2BAC[10] = { 0x00040001, 0x00040004, 0x00010010, 0x00010002, 0x00080001, 0x00020010, 0x00020001, 0x00020001, 0x00040008, 0x00010001 };
/* 0x2BD4 */ s32 lbl_1_data_2BD4[9] = { 0x00100008, 0x00100004, 0x00020008, 0x00020010, 0x00040010, 0x00040008, 0x00020010, 0x00020008, 0x00080008 };
/* 0x2BF8 */ s32 lbl_1_data_2BF8[12] = { 0x00010002, 0x00040004, 0x00040001, 0x00010002, 0x00100002, 0x00100002, 0x00100008, 0x00010002, 0x00100002, 0x00010004, 0x00100004, 0x00010001 };
/* 0x2C28 */ s16 lbl_1_data_2C28[19] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0002, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0001, 0x0001 };
/* 0x2C4E */ s16 lbl_1_data_2C4E[18] = { 0x0010, 0x0008, 0x0010, 0x0002, 0x0004, 0x0004, 0x0008, 0x0010, 0x0008, 0x0002, 0x0010, 0x0001, 0x0002, 0x0008, 0x0008, 0x0004, 0x0010, 0x0020 };
/* 0x2C72 */ s16 lbl_1_data_2C72[31] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0004, 0x0010, 0x0004, 0x0002, 0x0001, 0x0004, 0x0008, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0002, 0x0001, 0x0004, 0x0004, 0x0001, 0x0002, 0x0010, 0x0001, 0x0010, 0x0020 };
/* 0x2CB0 */ s32 lbl_1_data_2CB0[9] = { 0x00010004, 0x00020001, 0x00100001, 0x00020002, 0x00080001, 0x00100001, 0x00040001, 0x00040002, 0x00040001 };
/* 0x2CD4 */ s16 lbl_1_data_2CD4[21] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008, 0x0001, 0x0008, 0x0002, 0x0010, 0x0008, 0x0002, 0x0001, 0x0008, 0x0008, 0x0004, 0x0010, 0x0004, 0x0008 };
/* 0x2CFE */ s16 lbl_1_data_2CFE[22] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0008, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x2D2A */ s16 lbl_1_data_2D2A[22] = { 0x0001, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0002, 0x0004, 0x0002, 0x0002, 0x0008, 0x0004, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0004, 0x0008, 0x0001 };
/* 0x2D56 */ s16 lbl_1_data_2D56[18] = { 0x0008, 0x0008, 0x0002, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0008, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0004, 0x0008, 0x0010, 0x0020 };
/* 0x2D7A */ s16 lbl_1_data_2D7A[32] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0008, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0008, 0x0008, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0020 };
/* 0x2DBA */ s16 lbl_1_data_2DBA[21] = { 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x2DE4 */ s16 lbl_1_data_2DE4[23] = { 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0001, 0x0001 };
/* 0x2E12 */ s16 lbl_1_data_2E12[29] = { 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0002, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0001, 0x0001 };
/* 0x2E4C */ s32 lbl_1_data_2E4C[8] = { 0x00010004, 0x00100004, 0x00010002, 0x00100001, 0x00100001, 0x00020010, 0x00020001, 0x00080020 };
/* 0x2E6C */ s32 lbl_1_data_2E6C[4] = { 0x00010010, 0x00010004, 0x00020002, 0x00040020 };
/* 0x2E7C */ s16 lbl_1_data_2E7C[13] = { 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0020 };
/* 0x2E96 */ s16 lbl_1_data_2E96[23] = { 0x0001, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x2EC4 */ s16 lbl_1_data_2EC4[25] = { 0x0001, 0x0001, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x2EF6 */ s16 lbl_1_data_2EF6[26] = { 0x0001, 0x0001, 0x0010, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x2F2A */ s16 lbl_1_data_2F2A[17] = { 0x0001, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0001, 0x0010, 0x0020 };
/* 0x2F4C */ s16 lbl_1_data_2F4C[31] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0008, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x2F8A */ s16 lbl_1_data_2F8A[21] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0002, 0x0008, 0x0010, 0x0008, 0x0010, 0x0008, 0x0001, 0x0020 };
/* 0x2FB4 */ s32 lbl_1_data_2FB4[15] = { 0x00010002, 0x00010010, 0x00010004, 0x00100008, 0x00040004, 0x00010010, 0x00020002, 0x00010004, 0x00100004, 0x00010010, 0x00010004, 0x00100004, 0x00010002, 0x00100002, 0x00010001 };
/* 0x2FF0 */ s32 lbl_1_data_2FF0[13] = { 0x00010002, 0x00010010, 0x00040004, 0x00010010, 0x00010002, 0x00100002, 0x00010010, 0x00010002, 0x00100004, 0x00100002, 0x00010004, 0x00100004, 0x00010001 };
/* 0x3024 */ s32 lbl_1_data_3024[14] = { 0x00010004, 0x00010010, 0x00010002, 0x00100008, 0x00020001, 0x00100001, 0x00020010, 0x00020001, 0x00100001, 0x00020001, 0x00040010, 0x00040010, 0x00040010, 0x00010001 };
/* 0x305C */ s32 lbl_1_data_305C[9] = { 0x00010010, 0x00010002, 0x00100002, 0x00010010, 0x00010002, 0x00010004, 0x00100004, 0x00100004, 0x00010001 };
/* 0x3080 */ s16 lbl_1_data_3080[19] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0004, 0x0008, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x30A6 */ s16 lbl_1_data_30A6[26] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0008, 0x0002, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x30DA */ s16 lbl_1_data_30DA[29] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x3114 */ s32 lbl_1_data_3114[17] = { 0x00010004, 0x00010010, 0x00020002, 0x00010010, 0x00010004, 0x00100004, 0x00010002, 0x00100004, 0x00100004, 0x00010010, 0x00020002, 0x00010010, 0x00010004, 0x00100004, 0x00010002, 0x00040010, 0x00010001 };
/* 0x3158 */ s16 lbl_1_data_3158[23] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0010, 0x0002, 0x0010, 0x0020 };
/* 0x3186 */ s16 lbl_1_data_3186[34] = { 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x31CA */ s16 lbl_1_data_31CA[26] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0004, 0x0001, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0001, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x31FE */ s16 lbl_1_data_31FE[37] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0002, 0x0001, 0x0004, 0x0010, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0001, 0x0010, 0x0008, 0x0002, 0x0010, 0x0001, 0x0004, 0x0001, 0x0020 };
/* 0x3248 */ s32 lbl_1_data_3248[13] = { 0x00010010, 0x00010008, 0x00010004, 0x00100004, 0x00010010, 0x00010004, 0x00010002, 0x00100008, 0x00020001, 0x00100001, 0x00020010, 0x00020001, 0x00010001 };
/* 0x327C */ s16 lbl_1_data_327C[23] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x32AA */ s16 lbl_1_data_32AA[29] = { 0x0001, 0x0002, 0x0002, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0008, 0x0010, 0x0001, 0x0008, 0x0002, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001, 0x0001 };
/* 0x32E4 */ s16 lbl_1_data_32E4[25] = { 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x3316 */ s16 lbl_1_data_3316[29] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0001, 0x0008, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0020 };
/* 0x3350 */ s32 lbl_1_data_3350[19] = { 0x00010002, 0x00020004, 0x00040001, 0x00100001, 0x00020010, 0x00020001, 0x00100004, 0x00100002, 0x00040004, 0x00010010, 0x00080002, 0x00010002, 0x00010004, 0x00100004, 0x00100004, 0x00010010, 0x00010008, 0x00020001, 0x00100020 };
/* 0x339C */ s16 lbl_1_data_339C[21] = { 0x0010, 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0010, 0x0001, 0x0001 };
/* 0x33C6 */ s16 lbl_1_data_33C6[26] = { 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x33FA */ s16 lbl_1_data_33FA[18] = { 0x0010, 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x341E */ s16 lbl_1_data_341E[36] = { 0x0010, 0x0001, 0x0004, 0x0004, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0008, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3466 */ s16 lbl_1_data_3466[27] = { 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x349C */ s16 lbl_1_data_349C[35] = { 0x0010, 0x0001, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0008, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x34E2 */ s16 lbl_1_data_34E2[24] = { 0x0001, 0x0002, 0x0002, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3512 */ s16 lbl_1_data_3512[31] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0008, 0x0001, 0x0010, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3550 */ s16 lbl_1_data_3550[25] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3582 */ s16 lbl_1_data_3582[24] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0001, 0x0010, 0x0004, 0x0020 };
/* 0x35B2 */ s16 lbl_1_data_35B2[15] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0020 };
/* 0x35D0 */ s16 lbl_1_data_35D0[35] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0008, 0x0008, 0x0002, 0x0002, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3616 */ s16 lbl_1_data_3616[36] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x365E */ s16 lbl_1_data_365E[31] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0002, 0x0010, 0x0004, 0x0001, 0x0010, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0004, 0x0010, 0x0002, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x369C */ s16 lbl_1_data_369C[17] = { 0x0001, 0x0010, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0020 };
/* 0x36BE */ s16 lbl_1_data_36BE[34] = { 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0010, 0x0001, 0x0008, 0x0002, 0x0008, 0x0002, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x3702 */ s16 lbl_1_data_3702[27] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0002, 0x0004, 0x0010, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0020 };
/* 0x3738 */ s32 lbl_1_data_3738[16] = { 0x00010002, 0x00040004, 0x00020001, 0x00100001, 0x00040010, 0x00040001, 0x00100001, 0x00020010, 0x00080002, 0x00010010, 0x00010004, 0x00010010, 0x00010002, 0x00100002, 0x00100002, 0x00010020 };
/* 0x3778 */ s16 lbl_1_data_3778[15] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0004, 0x0010, 0x0001, 0x0008, 0x0001, 0x0020 };
/* 0x3796 */ s16 lbl_1_data_3796[28] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0004, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0008, 0x0002, 0x0010, 0x0002, 0x0001, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x37CE */ s16 lbl_1_data_37CE[28] = { 0x0001, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3806 */ s16 lbl_1_data_3806[25] = { 0x0001, 0x0004, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0004, 0x0002, 0x0004, 0x0001, 0x0002, 0x0010, 0x0002, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001 };
/* 0x3838 */ s32 lbl_1_data_3838[9] = { 0x00010002, 0x00040004, 0x00040001, 0x00010002, 0x00100002, 0x00010010, 0x00010002, 0x00100002, 0x00010020 };
/* 0x385C */ s32 lbl_1_data_385C[14] = { 0x00010004, 0x00040002, 0x00020002, 0x00020001, 0x00100001, 0x00100001, 0x00040004, 0x00100001, 0x00080002, 0x00010010, 0x00040004, 0x00010010, 0x00010002, 0x00080020 };
/* 0x3894 */ s16 lbl_1_data_3894[19] = { 0x0001, 0x0004, 0x0001, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0004, 0x0010, 0x0004, 0x0001, 0x0001, 0x0001 };
/* 0x38BA */ s16 lbl_1_data_38BA[19] = { 0x0001, 0x0002, 0x0004, 0x0004, 0x0002, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x38E0 */ s16 lbl_1_data_38E0[23] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0008, 0x0004, 0x0004, 0x0001, 0x0010, 0x0001, 0x0004, 0x0001, 0x0001, 0x0002, 0x0010, 0x0002, 0x0010, 0x0002, 0x0001, 0x0001 };
/* 0x390E */ s16 lbl_1_data_390E[23] = { 0x0001, 0x0004, 0x0002, 0x0002, 0x0004, 0x0004, 0x0001, 0x0010, 0x0008, 0x0002, 0x0002, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0010, 0x0001, 0x0002, 0x0001, 0x0004, 0x0010, 0x0020 };
/* 0x393C */ s32 lbl_1_data_393C[15] = { 0x00010004, 0x00010008, 0x00020002, 0x00010010, 0x00010010, 0x00010010, 0x00080008, 0x00040004, 0x00010010, 0x00010004, 0x00010001, 0x00020010, 0x00020008, 0x00100008, 0x00010020 };
/* 0x3978 */ s32 lbl_1_data_3978[16] = { 0x00010004, 0x00020002, 0x00010010, 0x00040004, 0x00010010, 0x00010004, 0x00010001, 0x00020010, 0x00020008, 0x00100008, 0x00020010, 0x00020010, 0x00020001, 0x00040010, 0x00040001, 0x00010000 };
/* 0x39B8 */ void *lbl_1_data_39B8[60] = { &lbl_1_data_1184, &lbl_1_data_18F2, &lbl_1_data_23D8, &lbl_1_data_119A, &lbl_1_data_195A, &lbl_1_data_243E, &lbl_1_data_123E, &lbl_1_data_19E6, &lbl_1_data_24A8, &lbl_1_data_1298, &lbl_1_data_1A5C, &lbl_1_data_250E, &lbl_1_data_12EE, &lbl_1_data_1AEE, &lbl_1_data_25A4, &lbl_1_data_133E, &lbl_1_data_1B64, &lbl_1_data_2618, &lbl_1_data_139C, &lbl_1_data_1BF0, &lbl_1_data_2690, &lbl_1_data_1410, &lbl_1_data_1C7A, &lbl_1_data_271A, &lbl_1_data_1472, &lbl_1_data_1D2E, &lbl_1_data_279C, &lbl_1_data_14C2, &lbl_1_data_1DA4, &lbl_1_data_27FC, &lbl_1_data_1538, &lbl_1_data_1E5C, &lbl_1_data_2896, &lbl_1_data_1592, &lbl_1_data_1ECE, &lbl_1_data_2902, &lbl_1_data_15E8, &lbl_1_data_1F7A, &lbl_1_data_2988, &lbl_1_data_1642, &lbl_1_data_1FF4, &lbl_1_data_2A00, &lbl_1_data_16A0, &lbl_1_data_207E, &lbl_1_data_2AA2, &lbl_1_data_1712, &lbl_1_data_2114, &lbl_1_data_2B38, &lbl_1_data_177E, &lbl_1_data_219C, &lbl_1_data_2BAC, &lbl_1_data_17DE, &lbl_1_data_2252, &lbl_1_data_2C28, &lbl_1_data_1846, &lbl_1_data_22A2, &lbl_1_data_2CB0, &lbl_1_data_189E, &lbl_1_data_2336, &lbl_1_data_2D2A };
/* 0x3AA8 */ void *lbl_1_data_3AA8[60] = { &lbl_1_data_11B6, &lbl_1_data_190E, &lbl_1_data_23F4, &lbl_1_data_11DE, &lbl_1_data_197E, &lbl_1_data_2468, &lbl_1_data_1258, &lbl_1_data_1A06, &lbl_1_data_24C4, &lbl_1_data_12B4, &lbl_1_data_1A8A, &lbl_1_data_2530, &lbl_1_data_1304, &lbl_1_data_1B0C, &lbl_1_data_25BC, &lbl_1_data_1354, &lbl_1_data_1B90, &lbl_1_data_2634, &lbl_1_data_13B6, &lbl_1_data_1C12, &lbl_1_data_26B2, &lbl_1_data_142E, &lbl_1_data_1CB0, &lbl_1_data_273A, &lbl_1_data_1488, &lbl_1_data_1D50, &lbl_1_data_27B8, &lbl_1_data_14DC, &lbl_1_data_1DD6, &lbl_1_data_2822, &lbl_1_data_1552, &lbl_1_data_1E7E, &lbl_1_data_28B8, &lbl_1_data_15B2, &lbl_1_data_1EFE, &lbl_1_data_2928, &lbl_1_data_1604, &lbl_1_data_1F9A, &lbl_1_data_29B0, &lbl_1_data_1660, &lbl_1_data_2022, &lbl_1_data_2A2E, &lbl_1_data_16BA, &lbl_1_data_20A0, &lbl_1_data_2AC2, &lbl_1_data_1730, &lbl_1_data_2144, &lbl_1_data_2B62, &lbl_1_data_1798, &lbl_1_data_21BE, &lbl_1_data_2BD4, &lbl_1_data_17FC, &lbl_1_data_2284, &lbl_1_data_2C4E, &lbl_1_data_185E, &lbl_1_data_22CC, &lbl_1_data_2CD4, &lbl_1_data_18BC, &lbl_1_data_2376, &lbl_1_data_2D56 };
/* 0x3B98 */ void *lbl_1_data_3B98[120] = { &lbl_1_data_11FE, &lbl_1_data_192C, &lbl_1_data_2414, &lbl_1_data_2DBA, &lbl_1_data_2DE4, &lbl_1_data_2E12, &lbl_1_data_1222, &lbl_1_data_19C0, &lbl_1_data_248A, &lbl_1_data_2E4C, &lbl_1_data_2E6C, &lbl_1_data_2E7C, &lbl_1_data_1272, &lbl_1_data_1A34, &lbl_1_data_24E4, &lbl_1_data_2E96, &lbl_1_data_2EC4, &lbl_1_data_2EF6, &lbl_1_data_12E2, &lbl_1_data_1AC4, &lbl_1_data_2566, &lbl_1_data_2F2A, &lbl_1_data_2F4C, &lbl_1_data_2F8A, &lbl_1_data_136E, &lbl_1_data_1B2A, &lbl_1_data_25DE, &lbl_1_data_2FB4, &lbl_1_data_2FF0, &lbl_1_data_305C, &lbl_1_data_131C, &lbl_1_data_1BBC, &lbl_1_data_2656, &lbl_1_data_3024, &lbl_1_data_3080, &lbl_1_data_30A6, &lbl_1_data_13CE, &lbl_1_data_1C30, &lbl_1_data_26CE, &lbl_1_data_30DA, &lbl_1_data_3114, &lbl_1_data_3186, &lbl_1_data_1442, &lbl_1_data_1CF0, &lbl_1_data_275E, &lbl_1_data_3158, &lbl_1_data_31CA, &lbl_1_data_31FE, &lbl_1_data_14A0, &lbl_1_data_1D76, &lbl_1_data_27D4, &lbl_1_data_3248, &lbl_1_data_327C, &lbl_1_data_32AA, &lbl_1_data_14FC, &lbl_1_data_1E26, &lbl_1_data_2854, &lbl_1_data_32E4, &lbl_1_data_3316, &lbl_1_data_3350, &lbl_1_data_1568, &lbl_1_data_1E98, &lbl_1_data_28D2, &lbl_1_data_339C, &lbl_1_data_33C6, &lbl_1_data_33FA, &lbl_1_data_15CA, &lbl_1_data_1F34, &lbl_1_data_294A, &lbl_1_data_341E, &lbl_1_data_3466, &lbl_1_data_349C, &lbl_1_data_161C, &lbl_1_data_1FC2, &lbl_1_data_29D0, &lbl_1_data_34E2, &lbl_1_data_3512, &lbl_1_data_3550, &lbl_1_data_1678, &lbl_1_data_205E, &lbl_1_data_2A50, &lbl_1_data_3582, &lbl_1_data_35B2, &lbl_1_data_35D0, &lbl_1_data_16DA, &lbl_1_data_20CC, &lbl_1_data_2AEC, &lbl_1_data_3616, &lbl_1_data_365E, &lbl_1_data_36BE, &lbl_1_data_1744, &lbl_1_data_2174, &lbl_1_data_2B7A, &lbl_1_data_369C, &lbl_1_data_3702, &lbl_1_data_3738, &lbl_1_data_17B4, &lbl_1_data_221E, &lbl_1_data_2BF8, &lbl_1_data_3796, &lbl_1_data_37CE, &lbl_1_data_3806, &lbl_1_data_1826, &lbl_1_data_21EA, &lbl_1_data_2C72, &lbl_1_data_3778, &lbl_1_data_3838, &lbl_1_data_385C, &lbl_1_data_187E, &lbl_1_data_22FE, &lbl_1_data_2CFE, &lbl_1_data_3894, &lbl_1_data_38BA, &lbl_1_data_38E0, &lbl_1_data_18D2, &lbl_1_data_239A, &lbl_1_data_2D7A, &lbl_1_data_390E, &lbl_1_data_393C, &lbl_1_data_3978 };


/* 181 insns */
void fn_1_E274(M515_AI *ai, s16 kind, s16 level)
{
    M515_WORK *work;
    s16 sel;
    int add;
    s16 tbl[4] = { 3, 4, 6, 9 };

    work = lbl_1_bss_4->data;
    ai->unk00 = 0;
    ai->unk04 = level;
    switch (kind) {
    case 0:
        if (rand8() / (255 / tbl[level] + 1) == 0) {
            add = 3;
        } else {
            add = 0;
        }
        if (work->unk21C < 3) {
            sel = work->unk1F8[work->unk21C] + add;
            work->unk21C++;
        } else {
            sel = add + rand8() / 86;
        }
        ai->unk0C = lbl_1_data_39B8[sel + work->unk002[0] * 6];
        break;

    case 1:
        if (rand8() / (255 / tbl[level] + 1) == 0) {
            add = 3;
        } else {
            add = 0;
        }
        if (work->unk21E < 3) {
            sel = work->unk204[work->unk21E] + add;
            work->unk21E++;
        } else {
            sel = add + rand8() / 86;
        }
        ai->unk0C = lbl_1_data_3AA8[sel + work->unk002[1] * 6];
        break;

    case 2:
        if (rand8() / (255 / tbl[level] + 1) == 0) {
            add = 6;
        } else {
            add = 0;
        }
        if (work->unk220 < 6) {
            sel = work->unk210[work->unk220] + add;
            work->unk220++;
        } else {
            sel = add + rand8() / 43;
        }
        ai->unk0C = lbl_1_data_3B98[sel + work->unk002[2] * 12];
        break;
    }
}

/* 92 insns */
void fn_1_E548(M515_PLAYER *player)
{
    int i;
    float s;

    for (i = 0; i < player->unk5E8; i++) {
        player->unk488[i].unk28 += 2.0f;
        if (player->unk488[i].unk28 > 360.0f) {
            player->unk488[i].unk28 -= 360.0f;
        }
        s = 0.05f * sin(M_PI * player->unk488[i].unk28 / 180.0);
        Hu3DModelScaleSet(player->unk488[i].unk00, 1.1f, 1.05f + s, 1.1f);
        Hu3DModelScaleSet(player->unk488[i].unk04, 1.1f - s, 1.1f, 1.1f - s);
    }
}

