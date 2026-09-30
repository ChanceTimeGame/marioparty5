/*
 * m508dll m508.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m508Dll/asm/REL/m508Dll/m508.s.
 */

#include "REL/m508dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* The shared object library. It is #included at the TOP of this unit: an
 * included .c file is compiled before the including file's own code, so plain
 * -inline auto can inline it into that code, and its .text is emitted as its
 * own section AFTER this file's -- which is where the reference has it
 * (fn_1_5D20..fn_1_A114). It also brings math.c's .bss statics in first, so
 * they land at the top of .bss. See m540dll/NOTES.md. */
#include "REL/m508Dll/objlib.c"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 0; */
/* 0x18 */ /* double lbl_1_rodata_18 = 0.5; */
/* 0x20 */ /* double lbl_1_rodata_20 = 3; */
/* 0x28 */ /* float lbl_1_rodata_28 = 1.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 0.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = -1.0f; */
/* 0x38 */ /* double lbl_1_rodata_38 = 4503601774854144; */
/* 0x40 */ /* float lbl_1_rodata_40 = 30.0f; */
/* 0x44 */ /* float lbl_1_rodata_44 = 10.0f; */
/* 0x48 */ /* float lbl_1_rodata_48 = 8000.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 1.2f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 640.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 480.0f; */
/* 0x58 */ /* double lbl_1_rodata_58 = 3.141592653589793; */
/* 0x60 */ /* double lbl_1_rodata_60 = 180; */
/* 0x68 */ /* float lbl_1_rodata_68 = 90.0f; */
/* 0x6C */ /* float lbl_1_rodata_6C = 0.1f; */
/* 0x70 */ /* float lbl_1_rodata_70 = 0.02f; */
/* 0x78 */ /* double lbl_1_rodata_78 = 4503599627370496; */
/* 0x80 */ /* double lbl_1_rodata_80 = 360; */
/* 0x88 */ /* float lbl_1_rodata_88 = 360.0f; */
/* 0x8C */ /* float lbl_1_rodata_8C[14] = { 180.0f, 0.000000000000000000000000000000000000000000717f, 0.00000000000000000000000000000000000000000069f, 0.000000000000000000000000000000000000000000858f, 0.00000000000000000000000000000000000000000097f, 0.000000000000000000000000000000000000000000914f, 0.000000000000000000000000000000000000000000087f, 0.000000000000000000000000000000000000000000942f, 0.000000000000000000000000000000000000000000661f, 0.000000000000000000000000000000000000000000886f, 0.000000000000000000000000000000000000000000802f, 0.00000000000000000000000000000000000000000083f, 0.000000000000000000000000000000000000000000774f, 0.000000000000000000000000000000000000000000745f }; */
/* 0xC4 */ /* s32 lbl_1_rodata_C4[2] = { 0x00280038, 0x00480058 }; */
/* 0xCC */ /* s32 lbl_1_rodata_CC[3] = { 0x00000043, 0x00000044, 0x00000042 }; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 40.0f; */
/* 0xDC */ /* s32 lbl_1_rodata_DC[8] = { 0x428C0000, 0x42680000, 0x433E0000, 0x42680000, 0x43C20000, 0x42680000, 0x43FE0000, 0x42680000 }; */
/* 0xFC */ /* float lbl_1_rodata_FC = -500.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 250.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = -450.0f; */
/* 0x108 */ /* float lbl_1_rodata_108 = -300.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 200.0f; */
/* 0x110 */ /* s32 lbl_1_rodata_110[3] = { 0x00000000, 0x43FA0000, 0x447A0000 }; */
/* 0x11C */ /* s32 lbl_1_rodata_11C[3] = { 0x00000000, 0x00000000, 0xC3960000 }; */
/* 0x128 */ /* u8 lbl_1_rodata_128[1] = { 0xFF }; */
/* 0x129 */ /* u8 lbl_1_rodata_129[1] = { 0xFF, 0xFF, 0xFF }; */
/* 0x12C */ /* s32 lbl_1_rodata_12C[3] = { 0x00000000, 0x4410C000, 0xC485D948 }; */
/* 0x138 */ /* s32 lbl_1_rodata_138[3] = { 0x4139999A, 0xBDCCCCCD, 0x40E00000 }; */
/* 0x144 */ /* float lbl_1_rodata_144 = 2202.3f; */
/* 0x148 */ /* float lbl_1_rodata_148 = 288.0f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 64.0f; */
/* 0x150 */ /* s32 lbl_1_rodata_150[12] = { 0x00000004, 0x00000006, 0x00000003, 0x00000006, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000001, 0x00000005, 0x00000000, 0x00000004 }; */
/* 0x180 */ /* s32 lbl_1_rodata_180[6] = { 0x00000000, 0x00000002, 0x00000003, 0x00000004, 0x00000001, 0x00000005 }; */
/* 0x198 */ /* s32 lbl_1_rodata_198[6] = { 0x40000000, 0xC0000000, 0x3F800000, 0xBF800000, 0x40400000, 0xC0400000 }; */
/* 0x1B0 */ /* s32 lbl_1_rodata_1B0[3] = { 0x3F800000, 0x3ECCCCCD, 0x40000000 }; */
/* 0x1BC */ /* s32 lbl_1_rodata_1BC[3] = { 0x00000000, 0x447A0000, 0x44480000 }; */
/* 0x1C8 */ /* s32 lbl_1_rodata_1C8[3] = { 0x00000000, 0x00000000, 0xC3C80000 }; */
/* 0x1D4 */ /* s32 lbl_1_rodata_1D4[1] = { 0xFFFFFFFF }; */
/* 0x1D8 */ /* s32 lbl_1_rodata_1D8[3] = { 0x00000000, 0x447A0000, 0x44480000 }; */
/* 0x1E4 */ /* s32 lbl_1_rodata_1E4[3] = { 0x00000000, 0x00000000, 0xC4160000 }; */
/* 0x1F0 */ /* s32 lbl_1_rodata_1F0[8] = { 0xFFFFFFFF, 0x00000000, 0x447A0000, 0x44480000, 0x00000000, 0x00000000, 0xC4160000, 0xFFFFFFFF }; */
/* 0x210 */ /* s32 lbl_1_rodata_210[120] = { 0x00000001, 0x0000000A, 0x00000002, 0x0000000A, 0x00000003, 0x0000000A, 0x00000004, 0x0000000A, 0x000000FF, 0x0000000A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x0000001E, 0x00000000, 0x00000004, 0x00000002, 0x0000001E, 0x00000000, 0x00000004, 0x000000FF, 0x0000000A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x0000003C, 0x00000000, 0x0000001E, 0x00000003, 0x0000003C, 0x00000000, 0x0000001E, 0x000000FF, 0x0000000A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x0000000A, 0x00000003, 0x0000000A, 0x00000001, 0x0000000A, 0x00000002, 0x0000000A, 0x000000FF, 0x0000000A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000000F, 0x00000001, 0x0000000F, 0x00000002, 0x0000000F, 0x00000003, 0x0000000F, 0x00000004, 0x0000000F, 0x000000FF, 0x0000000A, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000005A, 0x000000FF, 0x0000003C, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x3F0 */ /* s32 lbl_1_rodata_3F0[10] = { 0x00000000, 0x3F800000, 0x41200000, 0x41980000, 0x41A00000, 0x41E80000, 0x41F00000, 0x421C0000, 0x42200000, 0x42440000 }; */
/* 0x418 */ /* s32 lbl_1_rodata_418[3] = { 0x00000000, 0x447A0000, 0x44480000 }; */
/* 0x424 */ /* s32 lbl_1_rodata_424[3] = { 0x00000000, 0x00000000, 0xC3C80000 }; */
/* 0x430 */ /* s32 lbl_1_rodata_430[1] = { 0xFFFFFFFF }; */
/* 0x434 */ /* s32 lbl_1_rodata_434[9] = { 0x00420001, 0x00420002, 0x00420003, 0x00420004, 0x00420005, 0x00420006, 0x00420007, 0x00420008, 0x00420009 }; */
/* 0x458 */ /* float lbl_1_rodata_458 = 8.0f; */
/* 0x45C */ /* s32 lbl_1_rodata_45C[7] = { 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007 }; */
/* 0x478 */ /* float lbl_1_rodata_478 = 16.0f; */
/* 0x47C */ /* float lbl_1_rodata_47C = 45.0f; */
/* 0x480 */ /* double lbl_1_rodata_480 = 410; */
/* 0x488 */ /* double lbl_1_rodata_488 = 1.5707963267948966; */
/* 0x490 */ /* float lbl_1_rodata_490 = 0.022222223f; */
/* 0x494 */ /* float lbl_1_rodata_494 = 410.0f; */
/* 0x498 */ /* float lbl_1_rodata_498 = 9.0f; */
/* 0x4A0 */ /* double lbl_1_rodata_4A0 = 2; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 400; */
/* 0x4B0 */ /* double lbl_1_rodata_4B0 = 80; */
/* 0x4B8 */ /* float lbl_1_rodata_4B8 = 0.033333335f; */
/* 0x4C0 */ /* double lbl_1_rodata_4C0 = 200; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 400.0f; */
/* 0x4CC */ /* s32 lbl_1_rodata_4CC[3] = { 0x00000000, 0x447A0000, 0x44480000 }; */
/* 0x4D8 */ /* s32 lbl_1_rodata_4D8[3] = { 0x00000000, 0x00000000, 0xC4160000 }; */
/* 0x4E4 */ /* s32 lbl_1_rodata_4E4[1] = { 0xFFFFFFFF }; */
/* 0x4E8 */ /* s32 lbl_1_rodata_4E8[5] = { 0x00420015, 0x00420014, 0x00420017, 0x00420016, 0x00420018 }; */
/* 0x4FC */ /* s32 lbl_1_rodata_4FC[117] = { 0x008C0006, 0x008C0031, 0x008C003B, 0x008C003C, 0x008C003D, 0x008C0046, 0x008C0047, 0x008C0048, 0x008C0049, 0x00330006, 0x00330031, 0x0033003B, 0x0033003C, 0x0033003D, 0x00330046, 0x00330047, 0x00330048, 0x00330049, 0x00B70006, 0x00B70031, 0x00B7003B, 0x00B7003C, 0x00B7003D, 0x00B70046, 0x00B70047, 0x00B70048, 0x00B70049, 0x00ED0006, 0x00ED0031, 0x00ED003B, 0x00ED003C, 0x00ED003D, 0x00ED0046, 0x00ED0047, 0x00ED0048, 0x00ED0049, 0x00E60006, 0x00E60031, 0x00E6003B, 0x00E6003C, 0x00E6003D, 0x00E60046, 0x00E60047, 0x00E60048, 0x00E60049, 0x00170006, 0x00170031, 0x0017003B, 0x0017003C, 0x0017003D, 0x00170046, 0x00170047, 0x00170048, 0x00170049, 0x00E00006, 0x00E00031, 0x00E0003B, 0x00E0003C, 0x00E0003D, 0x00E00046, 0x00E00047, 0x00E00048, 0x00E00049, 0x002D0006, 0x002D0031, 0x002D003B, 0x002D003C, 0x002D003D, 0x002D0046, 0x002D0047, 0x002D0048, 0x002D0049, 0x00C90006, 0x00C90031, 0x00C9003B, 0x00C9003C, 0x00C9003D, 0x00C90046, 0x00C90047, 0x00C90048, 0x00C90049, 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049, 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049, 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049, 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049 }; */
/* 0x6D0 */ /* s32 lbl_1_rodata_6D0[4] = { 0x0000000A, 0x00000028, 0x0000003C, 0x00000055 }; */
/* 0x6E0 */ /* float lbl_1_rodata_6E0 = 0.02173913f; */
/* 0x6E4 */ /* float lbl_1_rodata_6E4 = -180.0f; */
/* 0x6E8 */ /* float lbl_1_rodata_6E8 = 0.016666668f; */
/* 0x6EC */ /* float lbl_1_rodata_6EC = -360.0f; */
/* 0x6F0 */ /* s32 lbl_1_rodata_6F0[13] = { 0x00960000, 0x00960001, 0x00960002, 0x00960003, 0x00960004, 0x00960006, 0x00960007, 0x00960008, 0x00960009, 0x0096000A, 0x0096000B, 0x0096000C, 0x0096000D }; */
/* 0x724 */ /* float lbl_1_rodata_724 = -36.0f; */
/* 0x728 */ /* float lbl_1_rodata_728 = -8.0f; */
/* 0x72C */ /* float lbl_1_rodata_72C = 14.0f; */
/* 0x730 */ /* float lbl_1_rodata_730 = 36.0f; */
/* 0x734 */ /* float lbl_1_rodata_734 = 2.0f; */
/* 0x738 */ /* s32 lbl_1_rodata_738[7] = { 0x0042001A, 0x00420019, 0x0042001C, 0x0042001B, 0x0042001D, 0x0042001E, 0x0042000A }; */
/* 0x754 */ /* s32 lbl_1_rodata_754[6] = { 0x0042000D, 0x00420011, 0x0042000E, 0x0042000F, 0x00420010, 0x00420012 }; */
/* 0x76C */ /* float lbl_1_rodata_76C = -20.0f; */

/* --- fork B .rodata (named so fndiff compares the referenced bytes) --- */
/* 0xCC */ static const s32 lbl_1_rodata_CC[3] = { 0x43, 0x44, 0x42 };
/* 0x150 */ static const s32 lbl_1_rodata_150[3][4] = {
    { 4, 6, 3, 6 },
    { 1, 2, 3, 4 },
    { 1, 5, 0, 4 },
};
/* 0x180 */ static const s32 lbl_1_rodata_180[3][2] = {
    { 0, 2 },
    { 3, 4 },
    { 1, 5 },
};
/* 0x198 */ static const f32 lbl_1_rodata_198[3][2] = {
    { 2.0f, -2.0f },
    { 1.0f, -1.0f },
    { 3.0f, -3.0f },
};
/* 0x1B0 */ static const f32 lbl_1_rodata_1B0[3] = { 1.0f, 0.4f, 2.0f };
/* 0x1BC */ static const HuVecF lbl_1_rodata_1BC = { 0.0f, 1000.0f, 800.0f };
/* 0x1C8 */ static const HuVecF lbl_1_rodata_1C8 = { 0.0f, 0.0f, -400.0f };
/* 0x1D4 */ static const GXColor lbl_1_rodata_1D4 = { 255, 255, 255, 255 };
/* 0x1D8 */ static const HuVecF lbl_1_rodata_1D8 = { 0.0f, 1000.0f, 800.0f };
/* 0x1E4 */ static const HuVecF lbl_1_rodata_1E4 = { 0.0f, 0.0f, -600.0f };
/* 0x1F0 */ /* dtk merges 0x1F0..0x20F into one 32-byte object: fn_1_1E64's
 * colour is followed by an unreferenced duplicate of its own pos/dir/colour
 * triple.  Spelling the whole run as one object is what makes the reloc
 * target the same size, and so fn_1_1E64 raw=0. */
static const struct {
    /* 0x00 */ GXColor unk00;
    /* 0x04 */ HuVecF unk04;
    /* 0x10 */ HuVecF unk10;
    /* 0x1C */ GXColor unk1C;
} lbl_1_rodata_1F0 = {
    { 255, 255, 255, 255 },
    { 0.0f, 1000.0f, 800.0f },
    { 0.0f, 0.0f, -600.0f },
    { 255, 255, 255, 255 },
};
/* 0x210 */ static const s32 lbl_1_rodata_210[6][10][2] = {
    { { 1, 10 }, { 2, 10 }, { 3, 10 }, { 4, 10 }, { 255, 10 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    { { 1, 30 }, { 0, 4 }, { 2, 30 }, { 0, 4 }, { 255, 10 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    { { 2, 60 }, { 0, 30 }, { 3, 60 }, { 0, 30 }, { 255, 10 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    { { 1, 10 }, { 3, 10 }, { 1, 10 }, { 2, 10 }, { 255, 10 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    { { 0, 15 }, { 1, 15 }, { 2, 15 }, { 3, 15 }, { 4, 15 }, { 255, 10 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
    { { 0, 90 }, { 255, 60 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
};
/* 0x3F0 */ static const f32 lbl_1_rodata_3F0[5][2] = {
    { 0.0f, 1.0f },
    { 10.0f, 19.0f },
    { 20.0f, 29.0f },
    { 30.0f, 39.0f },
    { 40.0f, 49.0f },
};
/* 0x418 */ static const HuVecF lbl_1_rodata_418 = { 0.0f, 1000.0f, 800.0f };
/* 0x424 */ static const HuVecF lbl_1_rodata_424 = { 0.0f, 0.0f, -400.0f };
/* 0x430 */ static const GXColor lbl_1_rodata_430 = { 255, 255, 255, 255 };
/* 0x434 */ static const u32 lbl_1_rodata_434[9] = {
    DATANUM(DATA_m508, 1), DATANUM(DATA_m508, 2), DATANUM(DATA_m508, 3),
    DATANUM(DATA_m508, 4), DATANUM(DATA_m508, 5), DATANUM(DATA_m508, 6),
    DATANUM(DATA_m508, 7), DATANUM(DATA_m508, 8), DATANUM(DATA_m508, 9),
};
/* 0x45C */ static const s32 lbl_1_rodata_45C[7] = { 1, 2, 3, 4, 5, 6, 7 };

/* --- .data --- */
/* 0x0 */ void (*lbl_1_data_0[3])(void *) = { (void (*)(void *))fn_1_8D30, (void (*)(void *))fn_1_926C, (void (*)(void *))fn_1_8C70 };
/* 0xC */ s32 lbl_1_data_C[1] = { -1 };
/* 0x10 */ M508_OBJFUNC lbl_1_data_10[5] = { NULL, fn_1_6FC, fn_1_A3C, fn_1_10D4, fn_1_15B4 };
/* 0x24 */ s32 lbl_1_data_24[1] = { 0x00000000 };
/* 0x28 */ s32 lbl_1_data_28[1] = { 0x00000000 };
/* 0x2C */ void *lbl_1_data_2C[2] = { (void *)fn_1_1FDC, (void *)fn_1_20A8 };
/* 0x34 */ void *lbl_1_data_34[2] = { (void *)fn_1_22C0, (void *)fn_1_2394 };
/* 0x3C */ void *lbl_1_data_3C[6] = { (void *)fn_1_25B4, (void *)fn_1_268C, (void *)fn_1_2844, (void *)fn_1_2C88, (void *)fn_1_3090, (void *)fn_1_33E4 };
/* 0x54 */ void *lbl_1_data_54[8] = { (void *)fn_1_3A44, (void *)fn_1_3B98, (void *)fn_1_415C, (void *)fn_1_4380, (void *)fn_1_46A8, (void *)fn_1_479C, (void *)fn_1_4890, (void *)fn_1_49F8 };
/* 0x74 */ char lbl_1_data_74[] = "test11_tex_we-itemhook-r";
/* 0x90 */ M508_OBJFUNC lbl_1_data_90[2] = { fn_1_5084, fn_1_5164 };
/* 0x98 */ M508_OBJFUNC lbl_1_data_98[2] = { fn_1_5470, fn_1_5524 };
/* 0xA0 */ M508_OBJFUNC lbl_1_data_A0[1] = { NULL };
/* 0xA4 */ M508_OBJFUNC lbl_1_data_A4[2] = { fn_1_57E0, fn_1_58C4 };

/* math.c's 23 function-local statics ARE .bss 0x164..0x21C: they come from
 * objlib.c's include above, which is declared first and so emitted last. */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x114 */ M508_SPAWN lbl_1_bss_114[5];
/* 0x110 */ s32 lbl_1_bss_110;
/* 0x10C */ s32 lbl_1_bss_10C;
/* 0x108 */ s32 lbl_1_bss_108;
/* 0x104 */ s32 lbl_1_bss_104;
/* 0xF4 */ s32 lbl_1_bss_F4[4]; /* 0x10: 4-aligned, retype */
/* 0xF0 */ M508_CAMERA *lbl_1_bss_F0;
/* 0xEC */ M508_OBJ *lbl_1_bss_EC;
/* 0xE8 */ M508_OBJ *lbl_1_bss_E8;
/* 0xE4 */ M508_OBJ *lbl_1_bss_E4;
/* 0xE0 */ M508_OBJ *lbl_1_bss_E0;
/* 0xDC */ M508_OBJ *lbl_1_bss_DC;
/* 0xC8 */ M508_OBJ *lbl_1_bss_C8[5]; /* 0x14: 4-aligned, retype */
/* 0xB4 */ M508_OBJ *lbl_1_bss_B4[5]; /* 0x14: 4-aligned, retype */
/* 0xA4 */ M508_OBJ *lbl_1_bss_A4[4];
/* 0x44 */ M508_OBJ *lbl_1_bss_44[6][4]; /* 0x60: 4-aligned, retype */
/* 0x34 */ M508_OBJ *lbl_1_bss_34[4];
/* 0x1C */ M508_OBJ *lbl_1_bss_1C[6];
/* 0x8 */ M508_OBJ *lbl_1_bss_8[5];
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 294 insns */


/* ===== end of fork O's block ===== */

/* --- fork A's file-scope tables --- */
/* .rodata 0xC4 -- CharModelVoicePanSet pans; also read by fork D at 0x39E4 */
static const s16 lbl_1_rodata_C4[4] = { 0x28, 0x38, 0x48, 0x58 };
/* .rodata 0xCC -- HuAudSStreamPlay ids; also read by fork B at 0x1B40 */

/* .rodata 0xDC */
static const f32 lbl_1_rodata_DC[4][2] = { { 70.0f, 58.0f }, { 190.0f, 58.0f }, { 388.0f, 58.0f }, { 508.0f, 58.0f } };
/* .rodata 0x110/0x11C/0x128 -- the global light */
static const HuVecF lbl_1_rodata_110 = { 0.0f, 500.0f, 1000.0f };
static const HuVecF lbl_1_rodata_11C = { 0.0f, 0.0f, -300.0f };
static const GXColor lbl_1_rodata_128 = { 255, 255, 255, 255 };
/* .rodata 0x12C/0x138/0x144 -- the in-game camera view */
static const HuVecF lbl_1_rodata_12C = { 0.0f, 579.0f, -1070.79f };
static const HuVecF lbl_1_rodata_138 = { 11.6f, -0.1f, 7.0f };
static const f32 lbl_1_rodata_144 = 2202.3f;

/* --- functions (reference order) --- */
/* 294 insns */
void ObjectSetup(void)
{
    OMOBJMAN *objman;
    s32 i;
    s32 j;

    objman = omInitObjMan(1, 0x2000);
    omGameSysInit(objman);
    lbl_1_bss_F0 = fn_1_86F0(1);
    fn_1_8C64(lbl_1_bss_F0);
    fn_1_95D8(lbl_1_bss_F0, 40, 10, 8000, 1.2f);
    lbl_1_bss_E8 = fn_1_5414(0);
    lbl_1_bss_EC = fn_1_5B0();
    lbl_1_bss_EC->unk004 = 1;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_F4[i] = 0;
    }
    lbl_1_bss_E4 = fn_1_1D88();
    lbl_1_bss_E0 = fn_1_1F34();
    lbl_1_bss_DC = fn_1_1E64();
    fn_1_7F60(lbl_1_bss_DC);
    for (i = 0; i < 5; i++) {
        lbl_1_bss_C8[i] = fn_1_2260();
    }
    for (i = 0; i < 5; i++) {
        lbl_1_bss_B4[i] = fn_1_37E0(i);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_A4[i] = fn_1_3958(i);
    }
    for (i = 0; i < 5; i++) {
        lbl_1_bss_8[i] = fn_1_24DC();
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 6; j++) {
            lbl_1_bss_44[j][i] = fn_1_5394(j);
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_34[i] = fn_1_4B54(i);
        fn_1_5010(lbl_1_bss_34[i]);
    }
    for (i = 0; i < 6; i++) {
        lbl_1_bss_1C[i] = fn_1_5758(i);
    }
    HuPrcChildCreate(fn_1_538, 4095, 4096, 0, HuPrcCurrentGet());
}

/* 30 insns */
void fn_1_538(void)
{
    while(!omSysExitReq) {
        HuPrcVSleep();
    }
    HuAudFadeOut(1000);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    omOvlReturn(1);
    HuPrcEnd();
}

/* 83 insns */
M508_OBJ *fn_1_5B0(void)
{
    M508_OBJ *obj;

    obj = fn_1_7848(0x1000, 0x2000, 5, lbl_1_data_10);
    return obj;
}

/* 208 insns */
void fn_1_6FC(M508_OBJ *obj)
{
    s32 i;

    fn_1_7D60(lbl_1_bss_E4, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 5; i++) {
        fn_1_7D60(lbl_1_bss_C8[i], -500.0f + 250.0f * i, 250.0f, -450.0f);
    }
    for (i = 0; i < 5; i++) {
        fn_1_38CC(lbl_1_bss_B4[i], -500.0f + 250.0f * i, 250.0f, -450.0f);
    }
    for (i = 0; i < 4; i++) {
        fn_1_7D60(lbl_1_bss_A4[i], -300.0f + 200.0f * i, 0.0f, 0.0f);
        fn_1_4150(lbl_1_bss_A4[i]);
    }
    for (i = 0; i < 5; i++) {
        fn_1_7D60(lbl_1_bss_8[i], -500.0f + 250.0f * i, 0.0f, -450.0f);
    }
    for (i = 0; i < 4; i++) {
        fn_1_4F48(lbl_1_bss_34[i], lbl_1_rodata_DC[i][0], lbl_1_rodata_DC[i][1]);
    }
    lbl_1_bss_EC->unk004 = 2;
}

/* 422 insns */
void fn_1_A3C(M508_OBJ *obj)
{
    HU3DLIGHTID lightId;
    GAMEMESID mesId;
    s32 i;
    s32 j;

    lightId = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lightId, (HuVecF *)&lbl_1_rodata_110, (HuVecF *)&lbl_1_rodata_11C);
    Hu3DGLightColorSet(lightId, lbl_1_rodata_128.r, lbl_1_rodata_128.g, lbl_1_rodata_128.b, lbl_1_rodata_128.a);
    Hu3DGLightStaticSet(lightId, TRUE);
    fn_1_8C64(lbl_1_bss_F0);
    fn_1_5518(lbl_1_bss_E8);
    fn_1_58B8(lbl_1_bss_1C[0]);
    fn_1_2084(lbl_1_bss_E0, 0);
    lbl_1_data_C[0] = HuAudFXPlay(0x39A);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    WipeWait();
    HuPrcSleep(129);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 60);
    fn_1_8E28(lbl_1_bss_F0, &lbl_1_rodata_12C, &lbl_1_rodata_138, &lbl_1_rodata_144, 0);
    HuPrcSleep(0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    fn_1_2084(lbl_1_bss_E0, 5);
    lbl_1_bss_4 = HuAudSStreamPlay(lbl_1_rodata_CC[0]);
    mesId = GameMesCreate(2, 0);
    for (i = 0; i < 120; i++) {
        HuPrcVSleep();
    }
    fn_1_1FD0(lbl_1_bss_E0);
    for (j = 0; j < 5; j++) {
        fn_1_2388(lbl_1_bss_C8[j]);
    }
    HuPrcSleep(19);
    HuAudFXStop(lbl_1_data_C[0]);
    obj->unk004 = 4;
}

/* 312 insns */
void fn_1_10D4(M508_OBJ *obj)
{
    GAMEMESID mesId;
    GAMEMESID mesId2;
    s32 winner[4];
    s32 flag;
    s32 max;
    s32 cnt;
    s32 i;
    s32 j;

    flag = 0;
    fn_1_58B8(lbl_1_bss_1C[1]);
    fn_1_2084(lbl_1_bss_E0, 4);
    HuAudFXStop(lbl_1_data_C[0]);
    mesId = GameMesCreate(2, 1);
    while (GameMesStatGet(mesId)) {
        HuPrcVSleep();
    }
    max = 0;
    for (i = 0; i < 4; i++) {
        if (max < lbl_1_bss_F4[i]) {
            max = lbl_1_bss_F4[i];
        }
    }
    cnt = 0;
    for (i = 0; i < 4; i++) {
        if (max == lbl_1_bss_F4[i]) {
            cnt++;
        }
    }
    if (i == cnt && max == 0) {
        HuAudJinglePlay(123);
        HuPrcSleep(0);
        mesId2 = GameMesCreate(2, 2);
        CharLoseVoicePlay(lbl_1_bss_A4[0]->unk1BC, lbl_1_bss_A4[1]->unk1BC, lbl_1_bss_A4[2]->unk1BC, lbl_1_bss_A4[3]->unk1BC);
        for (i = 0; i < 4; i++) {
            CharModelVoicePanSet(lbl_1_bss_A4[i]->unk1BC, lbl_1_rodata_C4[i]);
            fn_1_49EC(lbl_1_bss_A4[i]);
        }
        for (i = 0; i < 5; i++) {
            HuAudFXPlay(0x68E);
            fn_1_2C7C(lbl_1_bss_8[i]);
            HuPrcSleep(9);
        }
        HuPrcSleep(169);
    } else {
        cnt = 0;
        for (i = 0; i < 4; i++) {
            if (max == lbl_1_bss_F4[i]) {
                winner[cnt++] = lbl_1_bss_A4[i]->unk1BC;
                GWMgCoinSet(i, 10);
                fn_1_4884(lbl_1_bss_A4[i]);
            } else {
                fn_1_49EC(lbl_1_bss_A4[i]);
            }
        }
        for (; cnt < i; cnt++) {
            winner[cnt] = -1;
        }
        HuAudJinglePlay(121);
        HuPrcSleep(0);
        mesId2 = GameMesCreate(4, 3, winner[0], winner[1], winner[2], winner[3]);
        lbl_1_data_C[0] = HuAudFXPlay(0x39A);
        flag = 0;
        for (j = 0; j < 4; j++) {
            if (lbl_1_bss_F4[j] == 3) {
                cnt = 0;
                for (i = 0; i < 4; i++) {
                    if (i != j && lbl_1_bss_F4[i] == 0) {
                        cnt++;
                    }
                }
                if (cnt == 3) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            for (i = 0; i < 5; i++) {
                fn_1_33D8(lbl_1_bss_8[i]);
                HuPrcSleep(9);
            }
            HuPrcSleep(169);
        } else {
            for (i = 0; i < 5; i++) {
                fn_1_265C(lbl_1_bss_8[i], lbl_1_bss_114[lbl_1_bss_110].unk000, 0.0f, 0.0f, 1.0f);
            }
            HuPrcSleep(209);
        }
    }
    HuAudFadeOut(1000);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    omOvlReturn(1);
    HuPrcEnd();
}

/* 384 insns */
void fn_1_15B4(M508_OBJ *obj)
{
    MGTIMER *timer;
    s32 round;
    s32 i;
    M508_OBJ *winner;
    f32 z;
    f32 y;
    f32 x;

    timer = MgTimerCreate(MGTIMER_TYPE_NORMAL);
    MgTimerPosSet(timer, 288.0f, 64.0f);
    round = 0;
    while (round < 3) {
        lbl_1_bss_104 = round;
        if (round > 0) {
            for (i = 0; i < 4; i++) {
                lbl_1_bss_A4[i]->unk004 = 2;
            }
        }
        fn_1_1BB4();
        HuAudFXPlay(0x688);
        for (i = 0; i < 5; i++) {
            fn_1_2838(lbl_1_bss_8[i]);
        }
        HuPrcSleep(45);
        for (i = 0; i < 5; i++) {
            fn_1_265C(lbl_1_bss_8[i], lbl_1_bss_114[i].unk000, lbl_1_bss_114[i].unk004,
                      lbl_1_bss_114[i].unk008, lbl_1_bss_114[i].unk00C);
        }
        fn_1_2084(lbl_1_bss_E0, lbl_1_bss_104 + 1);
        fn_1_58B8(lbl_1_bss_1C[round + 2]);
        MgTimerParamSet(timer, 300, 0, 0);
        MgTimerModeOnSet(timer, MGTIMER_OFFTYPE_FADEOUT);
        for (i = 0; i < 4; i++) {
            fn_1_4FA8(lbl_1_bss_34[i]);
        }
        for (i = 0; i < 4; i++) {
            lbl_1_bss_A4[i]->unk004 = 1;
        }
        lbl_1_bss_0 = 0;
        while (1) {
            if (MgTimerDoneCheck(timer)) {
                break;
            }
            if (lbl_1_bss_0 >= 4) {
                if (timer->stopF == 0) {
                    timer->stopF = TRUE;
                    timer->mode = MGTIMER_MODE_ON;
                }
                break;
            }
            HuPrcSleep(0);
        }
        for (i = 0; i < 4; i++) {
            lbl_1_bss_A4[i]->unk004 = 3;
        }
        HuPrcSleep(59);
        for (i = 0; i < 5; i++) {
            fn_1_2F80(lbl_1_bss_8[i]);
        }
        HuAudSStreamFadeOut(lbl_1_bss_4, 2000);
        fn_1_2084(lbl_1_bss_E0, 5);
        HuPrcSleep(119);
        lbl_1_bss_1C[round + 2]->unk004 = 0;
        fn_1_1FD0(lbl_1_bss_E0);
        for (i = 0; i < 5; i++) {
            fn_1_265C(lbl_1_bss_8[i], lbl_1_bss_114[i].unk000, 0.0f, 0.0f, 1.0f);
        }
        HuAudFXPlay(0x68D);
        winner = lbl_1_bss_8[lbl_1_bss_110];
        fn_1_7DB4(winner, &x, &y, &z);
        fn_1_7D60(lbl_1_bss_1C[5], x, y, z);
        fn_1_58B8(lbl_1_bss_1C[5]);
        lbl_1_data_C[0] = HuAudFXPlay(0x39A);
        for (i = 0; i < 4; i++) {
            if (fn_1_4654(lbl_1_bss_A4[i])) {
                fn_1_469C(lbl_1_bss_A4[i]);
                fn_1_512C(lbl_1_bss_34[i]);
                lbl_1_bss_F4[i]++;
            } else {
                fn_1_4790(lbl_1_bss_A4[i]);
            }
        }
        HuPrcSleep(119);
        if (round == 2) {
            break;
        }
        HuAudFXStop(lbl_1_data_C[0]);
        fn_1_2084(lbl_1_bss_E0, 5);
        fn_1_57D4(lbl_1_bss_1C[5]);
        HuAudFXPlay(0x68E);
        for (i = 0; i < 5; i++) {
            fn_1_2C7C(lbl_1_bss_8[i]);
        }
        round++;
        lbl_1_bss_4 = HuAudSStreamPlay(lbl_1_rodata_CC[round]);
        HuPrcSleep(119);
    }
    MgTimerKill(timer);
    obj->unk004 = 3;
}

/* 117 insns */
void fn_1_1BB4(void)
{
    s32 i;
    s32 lose;
    s32 win;
    s32 dir;

    win = lbl_1_rodata_180[lbl_1_bss_104][frandmod(2)];
    do {
        lose = lbl_1_rodata_150[lbl_1_bss_104][frandmod(4)];
    } while (win == lose);
    lbl_1_bss_110 = frandmod(5);
    for (i = 0; i < 5; i++) {
        lbl_1_bss_114[i].unk000 = lose;
        dir = frandmod(2);
        lbl_1_bss_114[i].unk004 = lbl_1_rodata_198[lbl_1_bss_104][dir];
        lbl_1_bss_114[i].unk008 = (s32)frandmod(30);
        lbl_1_bss_114[i].unk00C = lbl_1_rodata_1B0[lbl_1_bss_104];
    }
    lbl_1_bss_114[lbl_1_bss_110].unk000 = win;
    lbl_1_bss_10C = win;
    lbl_1_bss_108 = lose;
}

/* 52 insns */
M508_OBJ *fn_1_1D88(void)
{
    M508_OBJ *obj;
    M508_LIGHTWK *work;
    HU3DMODELID model;

    obj = fn_1_7A3C(0x1000, 0x2000, DATANUM(DATA_m508, 0xB), 0, NULL, 1,
                    (M508_OBJFUNC *)lbl_1_data_24);
    work = M508_LIGHTWK(obj);
    work->unk000 = Hu3DLLightCreateV(obj->unk184, (HuVecF *)&lbl_1_rodata_1BC,
                                     (HuVecF *)&lbl_1_rodata_1C8, (GXColor *)&lbl_1_rodata_1D4);
    Hu3DLLightInfinitytSet(obj->unk184, work->unk000);
    obj->unk158 = 1;
    Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
    model = obj->unk184;
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    return obj;
}

/* 3 insns */
void fn_1_1E58(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* 52 insns */
M508_OBJ *fn_1_1E64(void)
{
    M508_OBJ *obj;
    M508_LIGHTWK *work;
    HU3DMODELID model;

    obj = fn_1_7A3C(0x1000, 0x2000, DATANUM(DATA_m508, 0x1F), 0, NULL, 1,
                    (M508_OBJFUNC *)lbl_1_data_28);
    work = M508_LIGHTWK(obj);
    work->unk000 = Hu3DLLightCreateV(obj->unk184, (HuVecF *)&lbl_1_rodata_1D8,
                                     (HuVecF *)&lbl_1_rodata_1E4, (GXColor *)&lbl_1_rodata_1F0);
    Hu3DLLightInfinitytSet(obj->unk184, work->unk000);
    obj->unk158 = 1;
    Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
    model = obj->unk184;
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    return obj;
}

/* 39 insns */
M508_OBJ *fn_1_1F34(void)
{
    M508_OBJ *obj;
    M508_LIGHTWK *work;
    HU3DMODELID model;

    obj = fn_1_7A3C(0x1000, 0x2000, DATANUM(DATA_m508, 0xC), 0, NULL, 2,
                    (M508_OBJFUNC *)lbl_1_data_2C);
    work = M508_LIGHTWK(obj);
    obj->unk158 = 1;
    Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
    model = obj->unk184;
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    return obj;
}

/* 3 insns */
void fn_1_1FD0(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* 42 insns */
void fn_1_1FDC(M508_OBJ *obj)
{
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 9 insns */
void fn_1_2084(M508_OBJ *obj, s32 pattern)
{
    M508_LIGHTWK *work;

    work = M508_LIGHTWK(obj);
    work->unk004 = pattern;
    obj->unk004 = 1;
}

/* 72 insns */
void fn_1_20A8(M508_OBJ *obj)
{
    M508_LIGHTWK *work;
    s32 idx;
    s32 wait;
    s32 mot;

    work = M508_LIGHTWK(obj);
    idx = 0;
    wait = 0;
    while (1) {
        if (wait > 0) {
            wait--;
        } else {
            while (1) {
                mot = lbl_1_rodata_210[work->unk004][idx][0];
                wait = lbl_1_rodata_210[work->unk004][idx][1];
                if (mot != 0xFF) {
                    break;
                }
                idx = 0;
            }
            idx++;
            fn_1_21C8(obj, mot);
        }
        M508_OBJWAIT(1);
    }
}

/* 38 insns */
void fn_1_21C8(M508_OBJ *obj, s32 mot)
{
    Hu3DModelAttrReset(obj->unk184, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(obj->unk184, HU3D_MOTATTR_LOOP);
    Hu3DMotionStartEndSet(obj->unk184, lbl_1_rodata_3F0[mot][0], lbl_1_rodata_3F0[mot][1]);
    Hu3DMotionTimeSet(obj->unk184, 0.0f);
}

/* 21 insns */
M508_OBJ *fn_1_2260(void)
{
    M508_OBJ *obj;

    obj = fn_1_7A3C(0x1000, 0x2000, DATANUM(DATA_m508, 0x20), 0, NULL, 2,
                    (M508_OBJFUNC *)lbl_1_data_34);
    return obj;
}

/* 3 insns */
void fn_1_22B4(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* 50 insns */
void fn_1_22C0(M508_OBJ *obj)
{
    obj->unk158 = 0;
    Hu3DModelAttrSet(obj->unk184, HU3D_ATTR_DISPOFF);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_2388(M508_OBJ *obj)
{
    obj->unk004 = 1;
}

/* 82 insns */
void fn_1_2394(M508_OBJ *obj)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 4; i++) {
        fn_1_5C7C(i, 2, 40);
    }
    HuAudFXPlay(0x687);
    obj->unk158 = 1;
    Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
    model = obj->unk184;
    Hu3DModelAttrReset(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(obj->unk184, 0.0f);
    while (fn_1_80EC(obj)) {
        M508_OBJWAIT(1);
    }
    obj->unk004 = 0;
}

/* 51 insns */
M508_OBJ *fn_1_24DC(void)
{
    M508_OBJ *obj;
    M508_CHARWK *work;

    obj = fn_1_7A3C(0x1000, 0x2000, DATANUM(DATA_m508, 0), 9, lbl_1_rodata_434, 6,
                    (M508_OBJFUNC *)lbl_1_data_3C);
    work = M508_CHARWK(obj);
    work->unk000 = 0;
    work->unk010 = Hu3DLLightCreateV(obj->unk184, (HuVecF *)&lbl_1_rodata_418,
                                     (HuVecF *)&lbl_1_rodata_424, (GXColor *)&lbl_1_rodata_430);
    Hu3DLLightInfinitytSet(obj->unk184, work->unk010);
    obj->unk188 = 0;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[0], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    return obj;
}

/* 3 insns */
void fn_1_25A8(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* 42 insns */
void fn_1_25B4(M508_OBJ *obj)
{
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 12 insns */
void fn_1_265C(M508_OBJ *obj, s32 mot, f32 rotY, f32 shift, f32 speed)
{
    M508_CHARWK *work;

    work = M508_CHARWK(obj);
    work->unk000 = mot;
    work->unk004 = rotY;
    work->unk008 = shift;
    work->unk00C = speed;
    obj->unk004 = 1;
}

/* 107 insns */
void fn_1_268C(M508_OBJ *obj)
{
    M508_CHARWK *work;
    f32 rx;
    f32 ry;
    f32 rz;

    work = M508_CHARWK(obj);
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[lbl_1_rodata_45C[work->unk000]],
                       work->unk008, 16.0f, HU3D_MOTATTR_SHIFT_LOOP);
    Hu3DMotionShiftSpeedSet(obj->unk184, work->unk00C);
    fn_1_7E48(obj, &rx, &ry, &rz);
    while (1) {
        ry += work->unk004;
        fn_1_7DF4(obj, rx, ry, rz);
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
/* fn_1_2838  m508  3 insns  (donation: m540Dll/m540/fn_1_7660) */
void fn_1_2838(M508_OBJ *obj)
{
    obj->unk004 = 2;
}


/* 270 insns */
/* fn_1_2844  m508  270 insns */
void fn_1_2844(M508_OBJ *obj)
{
    HuVecF rot;
    HuVecF pos;
    float baseY;
    float rate;
    float t;
    s32 i;

    fn_1_813C(obj, 8, 0.0f, 8.0f, HU3D_MOTATTR_SHIFT_REV);
    Hu3DMotionShiftStartEndSet(obj->unk184, 0.0f, 45.0f);
    fn_1_7E48(obj, &rot.x, &rot.y, &rot.z);
    rot.y = 45.0f * (s32)frandmod(8);
    fn_1_7DF4(obj, rot.x, rot.y, rot.z);
    fn_1_7DB4(obj, &pos.x, &pos.y, &pos.z);
    baseY = 410.0 + (410.0 - 410.0 * sin(90.0f * M_PI / 180.0));
    for (i = 0; i < 45; i++) {
        t = (1.0f / 45.0f) * (i + 1);
        rate = sin(90.0f * t * M_PI / 180.0);
        rate = rate * (rate * rate);
        pos.y = baseY * rate;
        fn_1_7D60(obj, pos.x, pos.y, pos.z);
        fn_1_7E88(obj, t, t, t);
        M508_OBJWAIT(1);
    }
    fn_1_7E88(obj, 1.0f, 1.0f, 1.0f);
    fn_1_7D60(obj, pos.x, 410.0f, pos.z);
    obj->unk004 = 0;
}


/* 3 insns */
/* fn_1_2C7C  m508  3 insns  (donation: m540Dll/m540/fn_1_8B64) */
void fn_1_2C7C(M508_OBJ *obj)
{
    obj->unk004 = 3;
}


/* 190 insns */
/* fn_1_2C88  m508  190 insns */
void fn_1_2C88(M508_OBJ *obj)
{
    HuVecF pos;
    float rate;
    float t;
    s32 i;

    Hu3DMotionSpeedSet(obj->unk184, 1.0f);
    fn_1_813C(obj, 8, 0.0f, 16.0f, HU3D_MOTATTR_NONE);
    fn_1_7DB4(obj, &pos.x, &pos.y, &pos.z);
    for (i = 0; i < 45; i++) {
        t = (1.0f / 45.0f) * (i + 1);
        rate = sin(90.0f * t * M_PI / 180.0);
        rate = rate * (rate * rate);
        pos.y = 410.0f - 410.0f * rate;
        fn_1_7D60(obj, pos.x, pos.y, pos.z);
        fn_1_7E88(obj, 1.0f - t, 1.0f - t, 1.0f - t);
        M508_OBJWAIT(1);
    }
    fn_1_7D60(obj, pos.x, 0.0f, pos.z);
    obj->unk004 = 0;
}


/* 3 insns */
/* fn_1_2F80  m508  3 insns  (donation: m540Dll/m540/fn_1_D09C) */
void fn_1_2F80(M508_OBJ *obj)
{
    obj->unk004 = 4;
}


/* 65 insns */
/* fn_1_2F8C  m508  65 insns */
float fn_1_2F8C(float cur, float target, float rate)
{
    float diff;
    float next;

    diff = fmod(target - cur, 360.0);
    if (diff < 0.0f) {
        diff += 360.0f;
    }
    if (diff > 180.0f) {
        diff -= 360.0f;
    }
    next = fmod(cur + diff * rate, 360.0);
    if (next < 0.0f) {
        next += 360.0f;
    }
    return next;
}


/* 210 insns */
/* fn_1_3090  m508  210 insns */
void fn_1_3090(M508_OBJ *obj)
{
    HuVecF rot;

    fn_1_813C(obj, 0, 9.0f, 9.0f, HU3D_MOTATTR_LOOP);
    fn_1_7E48(obj, &rot.x, &rot.y, &rot.z);
    while (1) {
        rot.y = fn_1_2F8C(rot.y, 180.0 * (atan2(0.0, 2.0) / M_PI), 0.1f);
        fn_1_7DF4(obj, rot.x, rot.y, rot.z);
        if (rot.y < 1.0f && rot.y > -1.0f) {
            break;
        }
        M508_OBJWAIT(1);
    }
    fn_1_7DF4(obj, 0.0f, 0.0f, 0.0f);
    obj->unk004 = 0;
}


/* 3 insns */
/* fn_1_33D8  m508  3 insns  (donation: m540Dll/m540/fn_1_AA24) */
void fn_1_33D8(M508_OBJ *obj)
{
    obj->unk004 = 5;
}


/* 255 insns */
/* fn_1_33E4  m508  255 insns */
void fn_1_33E4(M508_OBJ *obj)
{
    HuVecF pos;
    float t;
    s32 i;

    fn_1_813C(obj, 0, 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    while (1) {
        fn_1_7DB4(obj, &pos.x, &pos.y, &pos.z);
        for (i = 0; i < 10; i++) {
            t = (1.0f / 10.0f) * (i + 1);
            pos.y = 400.0 - 80.0 * sin(180.0f * t * M_PI / 180.0);
            fn_1_7D60(obj, pos.x, pos.y, pos.z);
            M508_OBJWAIT(1);
        }
        for (i = 0; i < 30; i++) {
            t = (1.0f / 30.0f) * (i + 1);
            pos.y = 400.0 + 200.0 * sin(180.0f * t * M_PI / 180.0);
            fn_1_7D60(obj, pos.x, pos.y, pos.z);
            M508_OBJWAIT(1);
        }
        fn_1_7D60(obj, pos.x, 400.0f, pos.z);
    }
}


/* 59 insns */
/* fn_1_37E0  m508  59 insns */
M508_OBJ *fn_1_37E0(s32 no)
{
    static const HuVecF lbl_1_rodata_4CC = { 0.0f, 1000.0f, 800.0f };
    static const HuVecF lbl_1_rodata_4D8 = { 0.0f, 0.0f, -600.0f };
    static const GXColor lbl_1_rodata_4E4 = { 255, 255, 255, 255 };
    static const u32 lbl_1_rodata_4E8[5] = {
        0x00420015, 0x00420014, 0x00420017, 0x00420016, 0x00420018
    };
    M508_OBJ *obj;
    M508_MDLWK *work;

    obj = fn_1_7A3C(0x1000, 0x2000, lbl_1_rodata_4E8[no], 0, NULL, 1, NULL);
    work = M508_MDLWK(obj);
    work->unk000 = Hu3DModelCreate(
        HuDataSelHeapReadNum(0x00420013, HU_MEMNUM_OVL, HEAP_MODEL));
    work->unk002 = Hu3DLLightCreateV(obj->unk184, (HuVecF *)&lbl_1_rodata_4CC,
                                     (HuVecF *)&lbl_1_rodata_4D8,
                                     (GXColor *)&lbl_1_rodata_4E4);
    Hu3DLLightInfinitytSet(obj->unk184, work->unk002);
    work->unk004 = Hu3DLLightCreateV(work->unk000, (HuVecF *)&lbl_1_rodata_4CC,
                                     (HuVecF *)&lbl_1_rodata_4D8,
                                     (GXColor *)&lbl_1_rodata_4E4);
    Hu3DLLightInfinitytSet(work->unk000, work->unk004);
    return obj;
}


/* 35 insns */
/* fn_1_38CC  m508  35 insns */
void fn_1_38CC(M508_OBJ *obj, float x, float y, float z)
{
    M508_MDLWK *work;

    work = M508_MDLWK(obj);
    Hu3DModelPosSet(work->unk000, x, y, z);
    fn_1_7D60(obj, x, y, z);
}


/* 56 insns */
/* fn_1_3958  m508  56 insns */
M508_OBJ *fn_1_3958(s32 playerNo)
{
    static const u32 lbl_1_rodata_4FC[13][9] = {
        { 0x008C0006, 0x008C0031, 0x008C003B, 0x008C003C, 0x008C003D, 0x008C0046, 0x008C0047, 0x008C0048, 0x008C0049 },
        { 0x00330006, 0x00330031, 0x0033003B, 0x0033003C, 0x0033003D, 0x00330046, 0x00330047, 0x00330048, 0x00330049 },
        { 0x00B70006, 0x00B70031, 0x00B7003B, 0x00B7003C, 0x00B7003D, 0x00B70046, 0x00B70047, 0x00B70048, 0x00B70049 },
        { 0x00ED0006, 0x00ED0031, 0x00ED003B, 0x00ED003C, 0x00ED003D, 0x00ED0046, 0x00ED0047, 0x00ED0048, 0x00ED0049 },
        { 0x00E60006, 0x00E60031, 0x00E6003B, 0x00E6003C, 0x00E6003D, 0x00E60046, 0x00E60047, 0x00E60048, 0x00E60049 },
        { 0x00170006, 0x00170031, 0x0017003B, 0x0017003C, 0x0017003D, 0x00170046, 0x00170047, 0x00170048, 0x00170049 },
        { 0x00E00006, 0x00E00031, 0x00E0003B, 0x00E0003C, 0x00E0003D, 0x00E00046, 0x00E00047, 0x00E00048, 0x00E00049 },
        { 0x002D0006, 0x002D0031, 0x002D003B, 0x002D003C, 0x002D003D, 0x002D0046, 0x002D0047, 0x002D0048, 0x002D0049 },
        { 0x00C90006, 0x00C90031, 0x00C9003B, 0x00C9003C, 0x00C9003D, 0x00C90046, 0x00C90047, 0x00C90048, 0x00C90049 },
        { 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049 },
        { 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049 },
        { 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049 },
        { 0x00B00006, 0x00B00031, 0x00B0003B, 0x00B0003C, 0x00B0003D, 0x00B00046, 0x00B00047, 0x00B00048, 0x00B00049 }
    };
    M508_OBJ *obj;
    M508_PLAYERWK *work;

    obj = fn_1_8308(0x1000, 0x2800, playerNo, 9, lbl_1_rodata_4FC[0], 8,
                    (M508_OBJFUNC *)lbl_1_data_54, 2);
    fn_1_813C(obj, 5, 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
    CharModelVoicePanSet(playerNo, lbl_1_rodata_C4[playerNo]);
    work = M508_PLAYERWK(obj);
    work->unk000 = 0;
    work->unk004 = -1;
    obj->unk004 = 0;
    return obj;
}

/* 3 insns */
void fn_1_3A38(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* 82 insns */
void fn_1_3A44(M508_OBJ *obj)
{
    M508_OBJ *mdl;
    char *hook;

    obj->unk188 = 5;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[5], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    mdl = lbl_1_bss_44[0][obj->unk1C8];
    hook = CharModelItemHookGet(obj->unk1BC, 2, 0);
    Hu3DModelHookSet(obj->unk184, hook, mdl->unk184);
    fn_1_7F60(lbl_1_bss_44[0][obj->unk1C8]);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_3B8C(M508_OBJ *obj)
{
    obj->unk004 = 1;
}

/* 366 insns */
static const s32 lbl_1_rodata_6D0[4] = { 10, 40, 60, 85 };
void fn_1_3B98(M508_OBJ *obj)
{
    M508_PLAYERWK *work = (M508_PLAYERWK *)obj->unk018;
    M508_OBJ *mdl;
    M508_OBJ *mdl2;
    char *hook;
    s32 ans;
    s16 pad;

    if (work->unk004 != -1) {
        Hu3DModelHookReset(obj->unk184);
        fn_1_7F9C(lbl_1_bss_44[work->unk004][obj->unk1C8]);
    }
    mdl = lbl_1_bss_44[5][obj->unk1C8];
    hook = CharModelItemHookGet(obj->unk1BC, 2, 0);
    Hu3DModelHookSet(obj->unk184, hook, mdl->unk184);
    fn_1_7F60(lbl_1_bss_44[5][obj->unk1C8]);
    work->unk000 = 0;
    work->unk004 = -1;
    if (obj->unk1B8 != 0) {
        ans = -1;
        while (ans == -1) {
            M508_OBJWAIT(frandmod(120) + 30);
            if ((s32)frandmod(100) < lbl_1_rodata_6D0[obj->unk1C4]) {
                ans = lbl_1_bss_110;
                break;
            } else {
                ans = frandmod(5);
                break;
            }
        }
    } else {
        pad = obj->unk1C0;
        ans = -1;
        while (ans == -1) {
            if (HuPadBtnDown[pad] & PAD_BUTTON_B) {
                ans = 0;
            }
            if (HuPadBtnDown[pad] & PAD_BUTTON_A) {
                ans = 1;
            }
            if (HuPadBtnDown[pad] & PAD_BUTTON_Y) {
                ans = 2;
            }
            if (HuPadBtnDown[pad] & PAD_BUTTON_X) {
                ans = 3;
            }
            if (HuPadBtnDown[pad] & PAD_TRIGGER_R) {
                ans = 4;
            }
            M508_OBJWAIT(1);
        }
    }
    lbl_1_bss_0++;
    work->unk000 = 1;
    work->unk004 = ans;
    fn_1_7F9C(lbl_1_bss_44[5][obj->unk1C8]);
    Hu3DModelHookReset(obj->unk184);
    mdl2 = lbl_1_bss_44[ans][obj->unk1C8];
    Hu3DModelHookSet(obj->unk184, lbl_1_data_74, mdl2->unk184);
    fn_1_7F60(lbl_1_bss_44[ans][obj->unk1C8]);
    switch (obj->unk1C8) {
    case 0:
        HuAudFXPlay(0x689);
        break;
    case 1:
        HuAudFXPlay(0x68A);
        break;
    case 2:
        HuAudFXPlay(0x68B);
        break;
    case 3:
        HuAudFXPlay(0x68C);
        break;
    }
    obj->unk188 = 2;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[2], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    M508_OBJWAIT(20);
    obj->unk188 = 3;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_4150(M508_OBJ *obj)
{
    obj->unk004 = 2;
}

/* 134 insns */
void fn_1_415C(M508_OBJ *obj)
{
    f32 y;
    f32 t;
    f32 rotY;
    s32 i;

    obj->unk188 = 6;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[6], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    fn_1_7E48(obj, NULL, &y, NULL);
    for (i = 0; i < 46; i++) {
        t = 0.02173913f * (i + 1);
        rotY = y + (-180.0f - y) * t;
        M508_OBJROTSET(obj, 0.0f, rotY, 0.0f);
        M508_OBJWAIT(1);
    }
    M508_OBJROTSET(obj, 0.0f, -180.0f, 0.0f);
    obj->unk004 = 0;
}

/* 3 insns */
void fn_1_4374(M508_OBJ *obj)
{
    obj->unk004 = 3;
}

/* 181 insns */
void fn_1_4380(M508_OBJ *obj)
{
    M508_PLAYERWK *work = (M508_PLAYERWK *)obj->unk018;
    f32 y;
    f32 t;
    f32 rotY;
    s32 i;

    HuPrcSleep(59);
    if (work->unk000 != 0) {
        obj->unk188 = 4;
        Hu3DMotionShiftSet(obj->unk184, obj->unk190[4], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    } else {
        obj->unk188 = 6;
        Hu3DMotionShiftSet(obj->unk184, obj->unk190[6], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    }
    fn_1_7E48(obj, NULL, &y, NULL);
    for (i = 0; i < 60; i++) {
        t = 0.016666668f * (i + 1);
        rotY = y + (-360.0f - y) * t;
        M508_OBJROTSET(obj, 0.0f, rotY, 0.0f);
        M508_OBJWAIT(1);
    }
    M508_OBJROTSET(obj, 0.0f, 0.0f, 0.0f);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 18 insns */
s32 fn_1_4654(M508_OBJ *obj)
{
    M508_PLAYERWK *work = (M508_PLAYERWK *)obj->unk018;
    s32 ret;

    if (lbl_1_bss_110 == work->unk004) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

/* 3 insns */
void fn_1_469C(M508_OBJ *obj)
{
    obj->unk004 = 4;
}

/* 58 insns */
void fn_1_46A8(M508_OBJ *obj)
{
    obj->unk188 = 7;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[7], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_4790(M508_OBJ *obj)
{
    obj->unk004 = 5;
}

/* 58 insns */
void fn_1_479C(M508_OBJ *obj)
{
    obj->unk188 = 8;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[8], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_4884(M508_OBJ *obj)
{
    obj->unk004 = 6;
}

/* 87 insns */
void fn_1_4890(M508_OBJ *obj)
{
    M508_PLAYERWK *work = (M508_PLAYERWK *)obj->unk018;
    HuVecF pos;
    Mtx mtx;

    CharModelHookDustCreate(obj->unk1BC, CharModelItemHookGet(obj->unk1BC, 2, 0));
    Hu3DModelObjMtxGet(obj->unk184, CharModelItemHookGet(obj->unk1BC, 2, 0), mtx);
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    CharEffectSmokeCreate(1, &pos);
    obj->unk188 = 0;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[0], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* 3 insns */
void fn_1_49EC(M508_OBJ *obj)
{
    obj->unk004 = 7;
}

/* 87 insns */
void fn_1_49F8(M508_OBJ *obj)
{
    M508_PLAYERWK *work = (M508_PLAYERWK *)obj->unk018;
    HuVecF pos;
    Mtx mtx;

    CharModelHookDustCreate(obj->unk1BC, CharModelItemHookGet(obj->unk1BC, 2, 0));
    Hu3DModelObjMtxGet(obj->unk184, CharModelItemHookGet(obj->unk1BC, 2, 0), mtx);
    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];
    CharEffectSmokeCreate(1, &pos);
    obj->unk188 = 1;
    Hu3DMotionShiftSet(obj->unk184, obj->unk190[1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* ===========================================================================
 * m508dll / m508.c -- fork E: fn_1_4B54 .. fn_1_5C7C (21 functions, 1139 insns)
 * ==========================================================================*/

/* fn_1_4B54, m508.c, 253 insns.  Builds one player's sprite group and score
 * window.  fn_1_7848 (the library's plain-object constructor) inlines here. */
static const s32 lbl_1_rodata_6F0[13] = { 0x00960000, 0x00960001, 0x00960002, 0x00960003, 0x00960004, 0x00960006, 0x00960007, 0x00960008, 0x00960009, 0x0096000A, 0x0096000B, 0x0096000C, 0x0096000D };
M508_OBJ *fn_1_4B54(s32 playerNo)
{
    M508_OBJ *obj;
    M508_SCOREWK *work;
    s32 i;
    s32 anim;

    obj = fn_1_7848(0x1000, 0x2000, 2, lbl_1_data_90);
    work = M508_SCOREWK(obj);
    work->unk000 = HuSprGrpCreate(7);
    work->unk01C = MgScoreWinCreate(0x70, 0x28);
    for (i = 0; i < 7; i++) {
        switch (i) {
            case 0:
                anim = lbl_1_rodata_6F0[GwPlayerConf[playerNo].charNo];
                break;
            case 1:
            case 2:
            case 3:
                anim = 0x420030;
                break;
            case 4:
            case 5:
            case 6:
                anim = 0x420031;
                break;
        }
        work->unk002[i] = (s16)HuSprCreate(HuSprAnimDataRead(anim), 0, 0);
        HuSprGrpMemberSet(work->unk000, i, work->unk002[i]);
    }
    MgScoreWinPosSet(work->unk01C, 0.0f, 0.0f);
    HuSprPosSet(work->unk000, 0, -36.0f, 0.0f);
    HuSprPosSet(work->unk000, 1, -8.0f, 0.0f);
    HuSprPosSet(work->unk000, 2, 14.0f, 0.0f);
    HuSprPosSet(work->unk000, 3, 36.0f, 0.0f);
    HuSprPosSet(work->unk000, 4, -8.0f, 0.0f);
    HuSprPosSet(work->unk000, 5, 14.0f, 0.0f);
    HuSprPosSet(work->unk000, 6, 36.0f, 0.0f);
    HuSprPriSet(work->unk000, 0, 11);
    HuSprPriSet(work->unk000, 1, 11);
    HuSprPriSet(work->unk000, 2, 11);
    HuSprPriSet(work->unk000, 3, 11);
    HuSprPriSet(work->unk000, 4, 10);
    HuSprPriSet(work->unk000, 5, 10);
    HuSprPriSet(work->unk000, 6, 10);
    MgScoreWinDispSet(work->unk01C, FALSE);
    HuSprAttrSet(work->unk000, 4, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(work->unk000, 5, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(work->unk000, 6, HUSPR_ATTR_DISPOFF);
    work->unk018 = 0;
    return obj;
}

/* fn_1_4F48, m508.c, 24 insns.  Moves the group and its score window. */
void fn_1_4F48(M508_OBJ *obj, float posX, float posY)
{
    M508_SCOREWK *work;

    work = M508_SCOREWK(obj);
    HuSprGrpPosSet(work->unk000, work->unk010 = posX, work->unk014 = posY);
    MgScoreWinPosSet(work->unk01C, work->unk010, work->unk014);
}

/* fn_1_4FA8, m508.c, 26 insns.  Shows the four base sprites and the window. */
void fn_1_4FA8(M508_OBJ *obj)
{
    M508_SCOREWK *work;
    s32 i;

    work = M508_SCOREWK(obj);
    for (i = 0; i < 4; i++) {
        HuSprAttrReset(work->unk000, i, HUSPR_ATTR_DISPOFF);
    }
    MgScoreWinDispSet(work->unk01C, TRUE);
}

/* fn_1_5010, m508.c, 26 insns.  Hides all seven sprites and the window. */
void fn_1_5010(M508_OBJ *obj)
{
    M508_SCOREWK *work;
    s32 i;

    work = M508_SCOREWK(obj);
    for (i = 0; i < 7; i++) {
        HuSprAttrSet(work->unk000, i, HUSPR_ATTR_DISPOFF);
    }
    MgScoreWinDispSet(work->unk01C, FALSE);
}

/* fn_1_5078, m508.c, 3 insns.  Donated: m540dll/m540/fn_1_6360. */
void fn_1_5078(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* fn_1_5084, m508.c, 42 insns.  Donated: m540dll/m540/fn_1_73DC. */
void fn_1_5084(M508_OBJ *obj)
{
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* fn_1_512C, m508.c, 14 insns.  Advances the score step, clamped at 3. */
void fn_1_512C(M508_OBJ *obj)
{
    M508_SCOREWK *work;

    work = M508_SCOREWK(obj);
    if (work->unk018 < 3) {
        work->unk018++;
    }
    obj->unk004 = 1;
}

/* fn_1_5164, m508.c, 140 insns.  Pops the next score sprite in over 60 frames. */
void fn_1_5164(M508_OBJ *obj)
{
    M508_SCOREWK *work;
    s32 step;
    s32 i;
    f32 t;
    f32 w;

    work = M508_SCOREWK(obj);
    step = work->unk018;
    HuSprAttrReset(work->unk000, step + 3, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 60; i++) {
        t = (1.0f / 60.0f) * (i + 1);
        w = sin(M_PI * (90.0f * t) / 180.0);
        HuSprScaleSet(work->unk000, step + 3, 1.0f + (2.0f - 2.0f * w),
                      1.0f + (2.0f - 2.0f * w));
        HuSprTPLvlSet(work->unk000, step + 3, w);
        M508_OBJWAIT(1);
    }
    HuSprScaleSet(work->unk000, step + 3, 1.0f, 1.0f);
    HuSprTPLvlSet(work->unk000, step + 3, 1.0f);
    obj->unk004 = 0;
}

/* fn_1_5394, m508.c, 32 insns.  One of the 24 hidden HUD models. */
static const u32 lbl_1_rodata_738[7] = { 0x0042001A, 0x00420019, 0x0042001C, 0x0042001B, 0x0042001D, 0x0042001E, 0x0042000A };
M508_OBJ *fn_1_5394(s32 idx)
{
    M508_OBJ *obj;
    M508_HUDWK *work;

    obj = fn_1_7A3C(0x1000, 0x2000, lbl_1_rodata_738[idx], 0, NULL, 1, NULL);
    obj->unk158 = 0;
    Hu3DModelAttrSet(obj->unk184, HU3D_ATTR_DISPOFF);
    work = M508_HUDWK(obj);
    return obj;
}

/* fn_1_5414, m508.c, 20 insns.  The model-less camera-motion actor. */
M508_OBJ *fn_1_5414(s32 unused)
{
    M508_OBJ *obj;

    obj = fn_1_7A3C(0x1000, 0x2000, -1, 0, NULL, 2, lbl_1_data_98);
    return obj;
}

/* fn_1_5464, m508.c, 3 insns.  Donated: m540dll/m540/fn_1_6360. */
void fn_1_5464(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* fn_1_5470, m508.c, 42 insns.  Donated: m540dll/m540/fn_1_73DC. */
void fn_1_5470(M508_OBJ *obj)
{
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* fn_1_5518, m508.c, 3 insns.  Donated: m540dll/m540/fn_1_7484. */
void fn_1_5518(M508_OBJ *obj)
{
    obj->unk004 = 1;
}

/* fn_1_5524, m508.c, 58 insns.  Runs the 180-frame camera motion. */
void fn_1_5524(M508_OBJ *obj)
{
    HU3DMOTID motId;
    HU3DMODELID model;

    motId = Hu3DMotionCreateData(0x42000A);
    model = Hu3DModelCameraCreate(motId, 1);
    Hu3DCameraMotionStart(model, 1);
    M508_OBJWAIT(180);
    Hu3DModelKill(model);
    obj->unk004 = 0;
}

/* fn_1_560C, m508.c, 83 insns.  A second plain-object creator; never called. */
M508_OBJ *fn_1_560C(void)
{
    M508_OBJ *obj;

    obj = fn_1_7848(0x1000, 0x2000, 1, lbl_1_data_A0);
    return obj;
}

/* fn_1_5758, m508.c, 31 insns.  The six banner models; idx picks the model. */
static const u32 lbl_1_rodata_754[6] = { 0x0042000D, 0x00420011, 0x0042000E, 0x0042000F, 0x00420010, 0x00420012 };
M508_OBJ *fn_1_5758(s32 idx)
{
    M508_OBJ *obj;
    M508_HUDWK *work;

    obj = fn_1_7A3C(0x1000, 0x2000, lbl_1_rodata_754[idx], 0, NULL, 2,
                    lbl_1_data_A4);
    work = M508_HUDWK(obj);
    work->unk000 = idx;
    return obj;
}

/* fn_1_57D4, m508.c, 3 insns.  Donated: m540dll/m540/fn_1_6360. */
void fn_1_57D4(M508_OBJ *obj)
{
    obj->unk004 = 0;
}

/* fn_1_57E0, m508.c, 54 insns.  Donated: m540dll/m540/fn_1_100B8. */
void fn_1_57E0(M508_OBJ *obj)
{
    obj->unk158 = 0;
    Hu3DModelAttrSet(obj->unk184, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->unk184, HU3D_MOTATTR_PAUSE);
    while (1) {
        M508_OBJWAIT(1);
    }
}

/* fn_1_58B8, m508.c, 3 insns.  Donated: m540dll/m540/fn_1_7484. */
void fn_1_58B8(M508_OBJ *obj)
{
    obj->unk004 = 1;
}

/* fn_1_58C4, m508.c, 238 insns.  Plays the banner model's motion. */
void fn_1_58C4(M508_OBJ *obj)
{
    HU3DMODELID model1;
    HU3DMODELID model2;
    HU3DMODELID model3;
    M508_HUDWK *work;

    work = M508_HUDWK(obj);
    switch (work->unk000) {
        case 0:
        case 2:
        case 3:
        case 4: {
            obj->unk158 = 1;
            Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
            model1 = obj->unk184;
            Hu3DModelAttrReset(model1, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(model1, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(obj->unk184, 0.0f);
            while (fn_1_80EC(obj)) {
                M508_OBJWAIT(1);
            }
            break;
        }
        case 1: {
            obj->unk158 = 1;
            Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
            model2 = obj->unk184;
            Hu3DModelAttrReset(model2, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(model2, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(obj->unk184, 0.0f);
            while (fn_1_80EC(obj)) {
                M508_OBJWAIT(1);
            }
            break;
        }
        case 5: {
            f32 z;
            f32 y;
            f32 x;

            fn_1_7DB4(obj, &x, &y, &z);
            y = -20.0f;
            fn_1_7D60(obj, x, y, z);
            Hu3DModelAttrReset(obj->unk184, HU3D_MOTATTR_REV);
            obj->unk158 = 1;
            Hu3DModelAttrReset(obj->unk184, HU3D_ATTR_DISPOFF);
            model3 = obj->unk184;
            Hu3DModelAttrReset(model3, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(model3, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(obj->unk184, 0.0f);
            M508_OBJWAIT(110);
            break;
        }
    }
    obj->unk004 = 0;
}

/* fn_1_5C7C, m508.c, 41 insns.  Donated: m502dll/ending/fn_1_C3C4. */
void fn_1_5C7C(s32 playerNo, s32 type, s32 duration)
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


/* The reference's .text ends with a second out-of-line Dot/Cross pair, past
 * the whole library (fn_1_A154, fn_1_A174). An #included file's .text is its
 * own section, ordered by where the include ENDS, so a file included here --
 * below the library and below the game code -- is emitted last. */
#include "REL/m508Dll/objdot.c"
