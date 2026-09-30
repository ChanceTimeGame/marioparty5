/*
 * m527Dll m527.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m527Dll/asm/REL/m527Dll/m527.s.
 */

#include "REL/m527Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "string.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "dolphin/os.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 20; */
/* 0x18 */ /* double lbl_1_rodata_18 = 0.0078125; */
/* 0x20 */ /* double lbl_1_rodata_20 = 25; */
/* 0x28 */ /* double lbl_1_rodata_28 = 0.03125; */
/* 0x30 */ /* double lbl_1_rodata_30 = -32; */
/* 0x38 */ /* double lbl_1_rodata_38 = 3.141592653589793; */
/* 0x40 */ /* double lbl_1_rodata_40 = 180; */
/* 0x48 */ /* double lbl_1_rodata_48 = 4503601774854144; */
/* 0x50 */ /* s32 lbl_1_rodata_50[4] = { 0x00000001, 0x00000000, 0x00000003, 0x00000002 }; */
/* 0x60 */ /* s32 lbl_1_rodata_60[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x6C */ /* s32 lbl_1_rodata_6C[18] = { 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x00000009, 0x00000003, 0x00000002, 0x00000006, 0x00000005, 0x00000004, 0x00000008, 0x00000007, 0x00000001 }; */
/* 0xB4 */ /* s32 lbl_1_rodata_B4[8] = { 0x000000B4, 0x0000003C, 0x00000078, 0x0000003C, 0x0000005A, 0x0000003C, 0x0000001E, 0x0000003C }; */
/* 0xD4 */ /* s32 lbl_1_rodata_D4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 0.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 40.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 85.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 2.9833333f; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 2.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 0.017453292f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 350.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 233.33333f; */
/* 0x100 */ /* double lbl_1_rodata_100 = 0.25; */
/* 0x108 */ /* float lbl_1_rodata_108 = 900.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 2704.0f; */
/* 0x110 */ /* float lbl_1_rodata_110 = 700.0f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 3.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 1.0f; */
/* 0x120 */ /* double lbl_1_rodata_120 = 0.01745329238474369; */
/* 0x128 */ /* double lbl_1_rodata_128 = 45; */
/* 0x130 */ /* float lbl_1_rodata_130 = 95.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = -20.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 120.0f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 0.8f; */
/* 0x140 */ /* float lbl_1_rodata_140 = -500.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = 500.0f; */
/* 0x148 */ /* float lbl_1_rodata_148 = -1.0f; */
/* 0x150 */ /* double lbl_1_rodata_150 = 0.75; */
/* 0x158 */ /* double lbl_1_rodata_158 = 3; */
/* 0x160 */ /* double lbl_1_rodata_160 = 1.875; */
/* 0x168 */ /* float lbl_1_rodata_168 = 10.0f; */
/* 0x170 */ /* double lbl_1_rodata_170 = 0.3; */
/* 0x178 */ /* float lbl_1_rodata_178 = 50.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 70.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 20.0f; */
/* 0x188 */ /* double lbl_1_rodata_188 = 0.7; */
/* 0x190 */ /* float lbl_1_rodata_190 = 32.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = 255.0f; */
/* 0x198 */ /* float lbl_1_rodata_198 = 200.0f; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 0.5; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = 0.5f; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 0.875; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = 0.125; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 8.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 26.766666f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 4.866667f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = -2.4333334f; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = -26.766666412353516; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = -116.666664f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 116.666664f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 2.4f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 160.0f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 110.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = -300.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 300.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 30.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 58.0f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = 60.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = 27.0f; */
/* 0x208 */ /* double lbl_1_rodata_208 = 1.7; */
/* 0x210 */ /* double lbl_1_rodata_210 = 1; */
/* 0x218 */ /* double lbl_1_rodata_218 = 222; */
/* 0x220 */ /* double lbl_1_rodata_220 = 500; */
/* 0x228 */ /* float lbl_1_rodata_228 = 340.0f; */
/* 0x22C */ /* float lbl_1_rodata_22C = -850.0f; */
/* 0x230 */ /* float lbl_1_rodata_230 = 100.0f; */
/* 0x238 */ /* double lbl_1_rodata_238 = 30; */
/* 0x240 */ /* float lbl_1_rodata_240 = 4.0f; */
/* 0x244 */ /* float lbl_1_rodata_244 = 64.0f; */
/* 0x248 */ /* float lbl_1_rodata_248 = 16.0f; */
/* 0x24C */ /* float lbl_1_rodata_24C = 127.0f; */
/* 0x250 */ /* float lbl_1_rodata_250 = 15.0f; */
/* 0x258 */ /* double lbl_1_rodata_258 = 4503599627370496; */
/* 0x260 */ /* s32 lbl_1_rodata_260[4] = { 0x00000001, 0x00000004, 0x00000002, 0x00000003 }; */
/* 0x270 */ /* s32 lbl_1_rodata_270[27] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 115.0f; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 0.66; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 0.34; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 5.0f; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = -500; */
/* 0x300 */ /* double lbl_1_rodata_300 = 148.5; */
/* 0x308 */ /* double lbl_1_rodata_308 = 2.0943951023931953; */
/* 0x310 */ /* float lbl_1_rodata_310 = 320.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 10000.0f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 576.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 640.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 480.0f; */
/* 0x324 */ /* float lbl_1_rodata_324 = -270.0f; */
/* 0x328 */ /* float lbl_1_rodata_328 = 270.0f; */
/* 0x330 */ /* double lbl_1_rodata_330 = 2.07; */
/* 0x338 */ /* float lbl_1_rodata_338 = 170.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 1.25f; */
/* 0x340 */ /* float lbl_1_rodata_340 = -1000.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 0.75f; */
/* 0x348 */ /* double lbl_1_rodata_348 = 0.15000000596046448; */
/* 0x350 */ /* double lbl_1_rodata_350 = 15; */
/* 0x358 */ /* double lbl_1_rodata_358 = 9.75; */
/* 0x360 */ /* double lbl_1_rodata_360 = 770; */
/* 0x368 */ /* double lbl_1_rodata_368 = -750; */
/* 0x370 */ /* float lbl_1_rodata_370 = 6.0f; */
/* 0x374 */ /* float lbl_1_rodata_374 = 375.0f; */
/* 0x378 */ /* float lbl_1_rodata_378 = 17.0f; */
/* 0x37C */ /* float lbl_1_rodata_37C = 933.3333f; */
/* 0x380 */ /* float lbl_1_rodata_380 = 0.25f; */
/* 0x384 */ /* s32 lbl_1_rodata_384[12] = { 0xBF800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0x3F800000 }; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = 133.33333f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = 1.5f; */
/* 0x3BC */ /* s32 lbl_1_rodata_3BC[12] = { 0xBF800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0x3F800000 }; */
/* 0x3EC */ /* s32 lbl_1_rodata_3EC[25] = { 0x42480000, 0x00000000, 0x422D3480, 0xC1C80000, 0x41C7FFFF, 0xC22D3480, 0xB60637BD, 0xC247FFFF, 0xC1C80000, 0xC22D347F, 0xC22D347F, 0xC1C7FFFE, 0xC247FFFE, 0x358637BD, 0xC22D347E, 0x41C7FFFF, 0xC1C7FFFC, 0x422D347F, 0x36A7C5AC, 0x4247FFFE, 0x41C80000, 0x422D347E, 0x422D347F, 0x41C7FFFC, 0x00000000 }; */
/* 0x450 */ /* double lbl_1_rodata_450 = 90; */
/* 0x458 */ /* float lbl_1_rodata_458 = 360.0f; */
/* 0x460 */ /* double lbl_1_rodata_460 = -1; */
/* 0x468 */ /* double lbl_1_rodata_468 = 2; */
/* 0x470 */ /* float lbl_1_rodata_470 = 2.07f; */
/* 0x474 */ /* float lbl_1_rodata_474 = 0.005f; */
/* 0x478 */ /* double lbl_1_rodata_478 = -400.391602; */
/* 0x480 */ /* double lbl_1_rodata_480 = 0; */
/* 0x488 */ /* s32 lbl_1_rodata_488[12] = { 0xBF800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0x3F800000 }; */
/* 0x4B8 */ /* s32 lbl_1_rodata_4B8[16] = { 0x00000776, 0x00000777, 0x00000778, 0x00000779, 0x0000077A, 0x0000077B, 0x0000077C, 0x0000077D, 0x0000077E, 0x0000077F, 0x00000780, 0x00000781, 0x00000782, 0x00000783, 0x00000784, 0x00000785 }; */
/* 0x4F8 */ /* s32 lbl_1_rodata_4F8[12] = { 0x00000001, 0x00000009, 0x00000002, 0x00000008, 0x00000003, 0x00000007, 0x00000004, 0x00000006, 0x00000005, 0x00000005, 0x00000006, 0x00000004 }; */
/* 0x528 */ /* s32 lbl_1_rodata_528[12] = { 0x00000001, 0x00000009, 0x00000002, 0x00000008, 0x00000003, 0x00000007, 0x00000004, 0x00000006, 0x00000005, 0x00000005, 0x00000006, 0x00000004 }; */
/* 0x558 */ /* float lbl_1_rodata_558 = 135.0f; */
/* 0x55C */ /* float lbl_1_rodata_55C = 288.0f; */
/* 0x560 */ /* double lbl_1_rodata_560 = 650; */
/* 0x568 */ /* double lbl_1_rodata_568 = 100; */
/* 0x570 */ /* double lbl_1_rodata_570 = 255; */
/* 0x578 */ /* double lbl_1_rodata_578 = 50; */
/* 0x580 */ /* float lbl_1_rodata_580 = 0.00390625f; */
/* 0x584 */ /* float lbl_1_rodata_584 = 210.0f; */
/* 0x588 */ /* s32 lbl_1_rodata_588[2] = { 0x00000052, 0x000001EE }; */
/* 0x590 */ /* s32 lbl_1_rodata_590[2] = { 0x00000036, 0x00000036 }; */
/* 0x598 */ /* s32 lbl_1_rodata_598[20] = { 0xFFFFFFD0, 0xFFFFFFE8, 0x00000000, 0x00000018, 0x00000030, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x5E8 */ /* s32 lbl_1_rodata_5E8[20] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x638 */ /* float lbl_1_rodata_638 = -4.0f; */
/* 0x63C */ /* float lbl_1_rodata_63C = 82.0f; */
/* 0x640 */ /* float lbl_1_rodata_640 = 56.0f; */
/* 0x644 */ /* float lbl_1_rodata_644 = 494.0f; */
/* 0x648 */ /* s32 lbl_1_rodata_648[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 }; */
/* 0x658 */ /* float lbl_1_rodata_658 = -2.0f; */
/* 0x65C */ /* s32 lbl_1_rodata_65C[3] = { 0x00000000, 0x459C4000, 0x00000000 }; */
/* 0x668 */ /* s32 lbl_1_rodata_668[3] = { 0x3F400000, 0xBF800000, 0xBF000000 }; */
/* 0x674 */ /* u8 lbl_1_rodata_674[1] = { 0x00 }; */
/* 0x678 */ /* float lbl_1_rodata_678 = 1.2f; */
/* 0x67C */ /* float lbl_1_rodata_67C = 0.6f; */
/* 0x680 */ /* float lbl_1_rodata_680 = 322.0f; */
/* 0x684 */ /* float lbl_1_rodata_684 = 318.0f; */
/* 0x688 */ /* float lbl_1_rodata_688 = 1775.0f; */
/* 0x68C */ /* float lbl_1_rodata_68C = -30.0f; */
/* 0x690 */ /* float lbl_1_rodata_690 = 345.0f; */
/* 0x698 */ /* double lbl_1_rodata_698 = 10000; */
/* 0x6A0 */ /* double lbl_1_rodata_6A0 = 1.5707963267948966; */
/* 0x6A8 */ /* float lbl_1_rodata_6A8 = 346.0f; */
/* 0x6AC */ /* float lbl_1_rodata_6AC = 12.0f; */
/* 0x6B0 */ /* float lbl_1_rodata_6B0 = 7000.0f; */
/* 0x6B4 */ /* float lbl_1_rodata_6B4 = 12000.0f; */


/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0[20] = { 0x00550015, 0x00550015, 0x00550015, 0x00550015, 0x00550015, 0x00550016, 0x00550016, 0x00550016, 0x00550016, 0x00550016, 0x00550014, 0x00550014, 0x00550014, 0x00550014, 0x00550014, 0x00550016, 0x00550016, 0x00550016, 0x00550016, 0x00550016 };
/* 0x50 */ s32 lbl_1_data_50[33] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00890000, 0x00300000, 0x00B40000, 0x00EA0000, 0x00E30000, 0x00140000, 0x00DD0000, 0x002A0000, 0x00C60000, 0x00AD0000, 0x00000000, 0x00000000, 0x00000000 };
/* 0xD4 */ s32 lbl_1_data_D4[13] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C0008, 0x008C000A, 0x008C0009, 0x008C001A, 0x008C000E, 0x008C0006, 0x008C0031, 0x008C002B };
/* 0x108 */ u8 lbl_1_data_108[13] = { 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 };
/* 0x115 */ u8 lbl_1_data_115[15] = { 8, 8, 8, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0 };
/* 0x124 */ s32 lbl_1_data_124[13] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000005, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x158 */ s32 lbl_1_data_158[2] = { -1, 1800 }; /* [0] winning team (0/1, 4 = draw; -1 in ObjectSetup), [1] timer */
/* 0x160 */ s32 lbl_1_data_160[1] = { 0xFFFFFFFF };
/* 0x164 */ s32 lbl_1_data_164[1] = { 0x00000001 }; /* omOvlReturnEx arg (D1F0) */
/* 0x168 */ s32 lbl_1_data_168[2] = { 0x00000000, 0x00000000 };
/* 0x170 */ u32 lbl_1_data_170[2] = { 0x00000000, 0x00000000 };
/* 0x178 */ s32 lbl_1_data_178[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x188 */ u32 lbl_1_data_188[2] = { 0x0000003C, 0x0000003C };
/* 0x190 */ s32 lbl_1_data_190[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x1A0 */ s32 lbl_1_data_1A0[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x1B0 */ s32 lbl_1_data_1B0[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x1C0 */ s32 lbl_1_data_1C0[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x1D0 */ s32 lbl_1_data_1D0[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
/* 0x1D8 */ float lbl_1_data_1D8[4][4] = { { -200.0f, 0.0f, 0.0f, 170.0f }, { 200.0f, 0.0f, 0.0f, -170.0f }, { -200.0f, 0.0f, 0.0f, 170.0f }, { 200.0f, 0.0f, 0.0f, -170.0f } }; /* player start x, y, z, rot.y by slot (C408) */
/* 0x218 */ float lbl_1_data_218 = 1.0f; /* unreferenced; dtk counts it in data_1D8 (size 0x44) */
/* 0x21C: jumptable_1_data_21C is fn_1_5B4's switch */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x210 */ s32 lbl_1_bss_210; /* espEntry(0x550006) id (B8C4 0xC390): stw of an extsh'd s16 */
/* 0xD0 */ M527_SE lbl_1_bss_D0[16]; /* SE requests (fn_1_A0D0) */
/* 0xCC */ OMOBJ *lbl_1_bss_CC; /* fn_1_CB68 object (ObjectSetup 0xD144) */
/* 0xC8 */ OMOBJ *lbl_1_bss_C8; /* omOutViewMulti object: stw 0x4c(r3) (ObjectSetup 0xD114) */
/* 0xB8 */ OMOBJ *lbl_1_bss_B8[4]; /* player objects (ObjectSetup 0xD0A4); ->data is M527_PWORK */
/* 0xB4 */ OMOBJ *lbl_1_bss_B4; /* stage object, fn_1_B8C4 (ObjectSetup 0xD05C) */
/* 0xB0 */ OMOBJ *lbl_1_bss_B0; /* fn_1_D198 object (ObjectSetup 0xD178) */
/* 0xAC */ s32 lbl_1_bss_AC; /* game mode: = 1000 in fn_1_CB68 -- an int, not a pointer */
/* 0xA8 */ OMOBJMAN *lbl_1_bss_A8; /* omInitObjMan result */
/* 0xA6 */ s16 lbl_1_bss_A6; /* GameMes id (lha; GameMesKill arg at 0xD268) */
/* 0xA4 */ s16 lbl_1_bss_A4;
/* 0xA0 */ s32 lbl_1_bss_A0;
/* 0x9C */ s32 lbl_1_bss_9C; /* Hu3DGLightCreateV id: extsh+stw, lwz+extsh */
/* 0x8C */ s32 lbl_1_bss_8C[4]; /* HU3DLLIGHTIDs (extsh+stw): [0] mdlId[1], [1] mdlId[4], [2..3] mdlId[2..3] (B8C4) */
/* 0x84 */ float lbl_1_bss_84[2]; /* per-side x (fork D: fn_1_7E5C, fn_1_87F4) */
/* 0x7C */ float lbl_1_bss_7C[2]; /* per-side z (fork D) */
/* 0x78 */ s16 lbl_1_bss_78[2]; /* MgScoreWin group ids, one per team (B8C4 0xC2D8/0xC348); dtk sizes it 2 + 2 skip */
/* 0x14 */ float lbl_1_bss_14[25]; /* only [0] addressed (lfs/stfs 0x0, fn_1_4F98); 0x64 per dtk */
/* 0x10 */ s32 lbl_1_bss_10;
/* 0x8 */ s32 lbl_1_bss_8[2]; /* [0] = end flag (fn_1_D198 lwz+cmpwi); [1] never addressed */
/* 0x0 */ float lbl_1_bss_0[2]; /* [0] = mode timer (lfs/stfs only); [1] never addressed */

/* --- functions (reference order) --- */
/* 325 insns */
void fn_1_A0(void)
{
    HuVecF pos;
    HuVecF center;
    HuVecF up;
    float rx;
    float ry;
    float rz;
    int i;

    for (i = 0; i < 2; i++) {
        CenterM[i].y += 20.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0);
        CZoomM[i] += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
        CRotM[i].y += HuPadSubStkX[0] / 32.0;
        CRotM[i].x += HuPadSubStkY[0] / -32.0;
        rx = CRotM[i].x;
        ry = CRotM[i].y;
        rz = CRotM[i].z;
        pos.x = CenterM[i].x + CZoomM[i] * (sin(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
        pos.y = CenterM[i].y + CZoomM[i] * -sin(M_PI * rx / 180.0);
        pos.z = CenterM[i].z + CZoomM[i] * (cos(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
        center.x = CenterM[i].x;
        center.y = CenterM[i].y;
        center.z = CenterM[i].z;
        up.x = sin(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
        up.y = cos(M_PI * rx / 180.0);
        up.z = cos(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
    }
}

/* 4729 insns. Player object hook (obj->data = M527_PWORK; objects in
 * lbl_1_bss_B8[4], partner = lbl_1_bss_B8[unk000 ^ 1]): pad/COM input, the
 * jump/land motion state machine (switch jumptable_1_data_21C on unk018),
 * partner push-out, motion shifts, the per-team cell roll (data_178/190/188,
 * odd player only), score sprites and voice pan/volume. */
#define M527_CELL(o) ((s32)((350.0f + (o)->trans.x) / 233.33333f) + (s32)((350.0f + (o)->trans.z) / 233.33333f) * 3)

void fn_1_5B4(OMOBJ *obj)
{
    s32 partner[4] = { 1, 0, 3, 2 };
    OMOBJ *pobj = lbl_1_bss_B8[partner[obj->work[0]]];
    M527_PWORK *work = obj->data;
    M527_PWORK *pwork = lbl_1_bss_B8[partner[obj->work[0]]]->data;
    float mag = 0.0f;
    float stkX = 0.0f;
    float stkY = 0.0f;
    float jumpHold = 0.0f;
    float jumpTrig = 0.0f;
    s16 motion = -1;
    float groundY = 0.0f;
    float vx;
    float vz;
    float dx;
    float dz;
    float light;
    s32 otherCell;
    s32 isOdd;
    s32 isOdd2;
    s32 team;
    s32 i;
    s32 teamA;
    s32 teamB;
    s32 old188;
    s32 motIdx;
    s32 espIdx;
    float fade;

    lbl_1_data_124[9] = (work->unk000 % 2) * 60;
    if (work->unk018 != 3) {
        work->unk040 = work->unk048 = 0.0f;
    }
    work->unk034++;
    switch (work->unk030) {
    case 0:
        break;
    case 1:
        if (lbl_1_bss_AC == 1001) {
            motion = 0;
            if (lbl_1_bss_0[0] >= 40.0f && lbl_1_bss_0[0] < 85.0f && work->unk000 < 2) {
                motion = 8;
            }
        } else if (lbl_1_bss_AC == 1002) {
            float step = 2.9833333f;
            float sign;

            sign = (obj->rot.y < 0.0f) ? -1 : ((obj->rot.y > 0.0f) ? 1 : 0);
            obj->rot.y += -sign * step;
            obj->rot.y = (sign != ((obj->rot.y < 0.0f) ? -1 : ((obj->rot.y > 0.0f) ? 1 : 0))) ? 0.0f : obj->rot.y;
            motion = 9;
        } else if (lbl_1_bss_AC == 1003) {
            motion = 0;
            if (2.0f == lbl_1_bss_0[0]) {
                work->unk018 = 9;
            }
        }
        break;
    case 2:
        if (work->unk010 != -1) {
            stkX = HuPadStkX[work->unk010];
            stkY = HuPadStkY[work->unk010];
            jumpHold = (HuPadBtn[work->unk010] & 0x100) > 0;
            jumpTrig = (HuPadBtnDown[work->unk010] & ((work->unk018 == 3) ? 0x140 : 0x100)) > 0;
            {
                Vec dir = { 0.0f, 0.0f, 0.0f };
                Mtx rot;

                dir.x = stkX;
                dir.z = -stkY;
                PSMTXRotRad(rot, 'y', 0.017453292f * CRotM[0].y);
                PSMTXMultVec(rot, &dir, &dir);
                stkX = dir.x;
                stkY = -dir.z;
            }
        } else {
            s32 cellTbl[2][9] = { { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { 9, 3, 2, 6, 5, 4, 8, 7, 1 } };

            if (lbl_1_data_188[work->unk000 / 2] == 29
                || (work->unk04C == 2 && work->unk050 != M527_CELL(obj) && work->unk064 == 0)) {
                s32 waitTbl[4][2] = { { 180, 60 }, { 120, 60 }, { 90, 60 }, { 30, 60 } };

                work->unk04C = 1;
                work->unk05C = waitTbl[work->unk014][0] + rand8() % waitTbl[work->unk014][1];
                isOdd = work->unk000 % 2 == 1;
                if (work->unk064 > 0) {
                    if (cellTbl[1][work->unk050] == cellTbl[0][work->unk050]) {
                        work->unk064 = 0;
                    }
                }
                work->unk050 = lbl_1_data_178[isOdd + (work->unk000 & 2)];
                otherCell = lbl_1_data_178[!isOdd + (work->unk000 & 2)];
                if (pwork->unk010 == -1 && work->unk014 <= 1) {
                    M527_CELL(obj) == otherCell;
                }
                if (work->unk014 <= 1 && work->unk064 > 0) {
                    if (otherCell == cellTbl[work->unk064 > 0][work->unk050] - 1) {
                        work->unk064 = 0;
                    } else if (M527_CELL(pobj) == cellTbl[work->unk064 > 0][work->unk050] - 1) {
                        work->unk064 = 0;
                    }
                }
            }
            if (work->unk04C == 3) {
                if (work->unk05C == 0) {
                    float tdx;
                    float tdz;

                    tdx = work->unk054 - obj->trans.x;
                    tdz = work->unk058 - obj->trans.z;
                    stkX = tdx / 0.25;
                    stkY = -tdz / 0.25;
                    if (tdx * tdx + tdz * tdz < 900.0f) {
                        work->unk04C = 0;
                        work->unk05C = 0;
                    } else if (work->unk060 > 120) {
                        work->unk04C = 0;
                        work->unk05C = 0;
                    }
                } else {
                    work->unk05C--;
                }
            } else if (work->unk04C == 1) {
                if (work->unk05C == 0) {
                    float tdx2;
                    float tdz2;

                    tdx2 = work->unk054 - obj->trans.x;
                    tdz2 = work->unk058 - obj->trans.z;
                    stkX = tdx2 / 0.25;
                    stkY = -tdz2 / 0.25;
                    if (tdx2 * tdx2 + tdz2 * tdz2 < 2704.0f) {
                        work->unk04C = 2;
                        work->unk05C = 0;
                    } else if (work->unk060 > work->unk000 * 5 + 120) {
                        work->unk060 = 0;
                        work->unk064 = 0;
                        work->unk050 = (work->unk050 == lbl_1_data_178[(work->unk000 & 2) + (work->unk000 % 2 == 1)])
                            ? lbl_1_data_178[(work->unk000 & 2) + (work->unk000 % 2 == 0)]
                            : lbl_1_data_178[(work->unk000 & 2) + (work->unk000 % 2 == 1)];
                        work->unk054 = 700.0f * ((cellTbl[work->unk064 > 0][work->unk050] - 1) % 3 - 1) / 3.0f;
                        work->unk058 = 700.0f * ((cellTbl[work->unk064 > 0][work->unk050] - 1) / 3 - 1) / 3.0f;
                    }
                } else {
                    work->unk05C--;
                    if (work->unk05C == 0) {
                        if (pwork->unk010 != -1 && work->unk050 == M527_CELL(lbl_1_bss_B8[work->unk000 ^ 1])) {
                            work->unk050 = (work->unk050 == lbl_1_data_178[work->unk000 & 2])
                                ? lbl_1_data_178[(work->unk000 & 2) + 1]
                                : lbl_1_data_178[work->unk000 & 2];
                        }
                        if (work->unk014 <= 1 && work->unk064 > 0) {
                            if (M527_CELL(pobj) == cellTbl[work->unk064 > 0][work->unk050] - 1) {
                                work->unk064 = 0;
                            }
                        }
                        work->unk054 = 700.0f * ((cellTbl[work->unk064 > 0][work->unk050] - 1) % 3 - 1) / 3.0f;
                        work->unk058 = 700.0f * ((cellTbl[work->unk064 > 0][work->unk050] - 1) / 3 - 1) / 3.0f;
                    }
                }
            } else if (work->unk04C == 2) {
                switch (work->unk05C % 75) {
                case 1:
                    if (pwork->unk010 == -1 || work->unk014 <= 1 || pwork->unk018 == 3 || pwork->unk018 == 5
                        || (work->unk04C == 2 && work->unk05C == 0)) {
                        work->unk05C++;
                        if (pwork->unk018 == 5) {
                            jumpHold = jumpTrig = 1.0f;
                            work->unk05C = 15;
                        }
                    }
                    break;
                case 8:
                    jumpHold = jumpTrig = 1.0f;
                    work->unk05C++;
                    break;
                case 17:
                    jumpHold = 0.0f;
                    work->unk05C++;
                    break;
                case 18:
                    jumpHold = jumpTrig = 1.0f;
                    work->unk05C++;
                    break;
                case 54:
                    if (work->unk064 == 1
                        || ((pwork->unk018 == 0 || work->unk05C > 200) && work->unk050 == M527_CELL(lbl_1_bss_B8[work->unk000 ^ 1]))) {
                        s32 otherCell2;

                        isOdd2 = work->unk000 % 2 == 1;
                        work->unk050 = lbl_1_data_178[isOdd2 + (work->unk000 & 2)];
                        otherCell2 = lbl_1_data_178[!isOdd2 + (work->unk000 & 2)];
                        work->unk04C = 1;
                        work->unk05C = (work->unk064 != 0 ? 60 : 0) + 20;
                        work->unk064 += (work->unk064 > 0) ? -1 : 0;
                    } else {
                        work->unk05C++;
                    }
                    break;
                case 55:
                    if (work->unk010 == -1 && pwork->unk010 == -1 && work->unk000 % 2 == 1) {
                        work->unk05C += 14;
                    }
                default:
                    jumpHold = work->unk05C % 75 < 13;
                    work->unk05C++;
                    break;
                }
            }
            {
                Vec dir2 = { 0.0f, 0.0f, 0.0f };
                Mtx rot2;

                dir2.x = stkX;
                dir2.z = -stkY;
                PSMTXRotRad(rot2, 'y', 0.017453292f * (45.0 * sin(M_PI * (rand8() % 2 * 2 + work->unk060 * 3 % 360 - 1) / 180.0)));
                PSMTXMultVec(rot2, &dir2, &dir2);
                stkX = dir2.x;
                stkY = -dir2.z;
            }
        }
        break;
    case 3:
        break;
    case 4:
        if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] == 1 - work->unk000 / 2 && work->unk018 == 8 && lbl_1_bss_0[0] >= 95.0f) {
            groundY = obj->trans.y = -20.0f * (lbl_1_bss_0[0] - 95.0f);
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
            if (95.0f == lbl_1_bss_0[0]) {
                CharFXPlay(work->unk00C, 0x1F9);
            }
            if (95.0f == lbl_1_bss_0[0] && work->unk000 % 2 == 0 && lbl_1_bss_D0[work->unk000 / 2 + 13].unk000 < 3) {
                lbl_1_bss_D0[work->unk000 / 2 + 13].unk004[lbl_1_bss_D0[work->unk000 / 2 + 13].unk000] = 0.0f;
                lbl_1_bss_D0[work->unk000 / 2 + 13].unk000++;
            }
        }
        if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] == 1 - work->unk000 / 2 && lbl_1_bss_0[0] >= 120.0f) {
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
        }
        if (lbl_1_bss_AC >= 1006 && lbl_1_data_158[0] == 1 - work->unk000 / 2) {
            motion = 12;
            Hu3DMotionSpeedSet(obj->mdlId[0], 0.8f);
            Hu3DModelLayerSet(obj->mdlId[0], 3);
            Hu3DLLightPosSet(obj->mdlId[0], work->unk068, 0.0f, -500.0f, 500.0f, 0.0f, 1.0f, -1.0f);
            Hu3DLLightColorSet(obj->mdlId[0], work->unk068, 0x80, 0x80, 0x80, 0xFF);
            obj->trans.x -= 0.75 * (((obj->trans.x > 0.0f) ? 1 : -1) * 2);
            obj->trans.z -= 3.0;
            obj->rot.x += 1.875;
            if (lbl_1_bss_AC == 1006 && lbl_1_bss_0[0] <= 10.0f) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
        }
        break;
    case 5:
        obj->rot.y *= 0.3;
        if (lbl_1_bss_AC == 1006 && work->unk018 == 0) {
            work->unk01C = (lbl_1_data_158[0] == work->unk000 / 2) ? 10 : 11;
        }
        break;
    }
    if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] == 1 - work->unk000 / 2 && lbl_1_bss_0[0] >= 50.0f && lbl_1_bss_0[0] <= 70.0f) {
        light = (lbl_1_bss_0[0] < 50.0f) ? 0.0f : ((lbl_1_bss_0[0] > 70.0f) ? 1.0f : (lbl_1_bss_0[0] - 50.0f) / 20.0f);
        light = 1.0f - (1.0f - light) * (1.0f - light);
        light = 0.3 + 0.7 * (1.0f - light);
        Hu3DLLightColorSet(obj->mdlId[0], work->unk068, 2.0f * (32.0f * light) / 3.0f, 2.0f * (255.0f * light) / 3.0f,
            2.0f * (200.0f * light) / 3.0f, 0xFF);
    }
    if (work->unk030 >= 2) {
        switch (work->unk018) {
        case 7:
            if (Hu3DData[obj->mdlId[0]].motIdShift == -1 && CharMotionEndCheck(work->unk00C)) {
                motion = 0;
            }
            break;
        case 4:
            if (CharMotionEndCheck(work->unk00C)) {
                motion = 0;
            }
        case 0:
        case 1:
        case 2:
            vx = 0.25 * stkX;
            vz = 0.25 * -stkY;
            mag = sqrtf(vx * vx + vz * vz);
            if (mag >= 0.5f) {
                if (mag < 10.0f) {
                    work->unk040 = vx;
                    work->unk048 += vz;
                } else {
                    vx /= mag;
                    vz /= mag;
                    mag = 10.0f;
                    if (work->unk018 != 3) {
                        work->unk040 = vx * mag;
                        work->unk048 = vz * mag;
                    } else {
                        work->unk040 = 0.875 * work->unk040 + 0.125 * (vx * mag);
                        work->unk048 = 0.875 * work->unk048 + 0.125 * (vz * mag);
                    }
                }
                work->unk03C = mag;
                obj->rot.y = 180.0 * (atan2(work->unk040, work->unk048) / M_PI);
                if (work->unk03C >= 8.0f) {
                    motion = 2;
                } else {
                    motion = 1;
                }
            } else if (work->unk018 != 7 && work->unk018 != 4 && work->unk018 != 8) {
                motion = 0;
            }
            work->unk044 = 0.0f;
            if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] == 1 - work->unk000 / 2 && 70.0f == lbl_1_bss_0[0]) {
                motion = 8;
                work->unk030 = 4;
                break;
            }
            if (0.0f != groundY && obj->trans.y > groundY) {
                work->unk024 = 0;
                work->unk020 = 1;
                work->unk044 = 0.0f;
                motion = 3;
                break;
            }
            if (jumpTrig) {
                work->unk024 = 0;
                work->unk020 = 1;
                work->unk044 = 26.766666f;
                motion = 3;
            }
            break;
        case 3:
            vx = 0.25 * stkX;
            vz = 0.25 * -stkY;
            mag = sqrtf(vx * vx + vz * vz);
            if (mag >= 0.5f) {
                if (mag < 10.0f) {
                    work->unk040 = vx;
                    work->unk048 = vz;
                } else {
                    vx /= mag;
                    vz /= mag;
                    mag = 10.0f;
                    if (work->unk018 != 3) {
                        work->unk040 = vx * mag;
                        work->unk048 = vz * mag;
                    } else {
                        work->unk040 = 0.875 * work->unk040 + 0.125 * (vx * mag);
                        work->unk048 = 0.875 * work->unk048 + 0.125 * (vz * mag);
                    }
                }
                work->unk03C = mag;
                obj->rot.y = 180.0 * (atan2(work->unk040, work->unk048) / M_PI);
            } else {
                0.875 * work->unk040;
                0.875 * work->unk048;
            }
            if (work->unk020 != 0) {
                if (jumpHold) {
                    if (++work->unk020 > 4) {
                        work->unk020 = 0;
                    } else {
                        work->unk044 += 4.866667f;
                    }
                } else {
                    work->unk020 = 0;
                }
            }
            work->unk044 += -2.4333334f;
            if (work->unk024 != 0) {
                work->unk044 = 0.0f;
                work->unk024 = 1;
                motion = 4;
                break;
            }
            if (jumpTrig) {
                work->unk044 = 0.0f;
                work->unk028 = 0;
                motion = 5;
                work->unk02C = 0;
            }
            break;
        case 5:
            if (Hu3DData[obj->mdlId[0]].motIdShift == -1 && CharMotionEndCheck(work->unk00C)) {
                work->unk044 = -26.766666f * ((work->unk02C == 6) ? 0.5 : ((work->unk02C >= 6) ? 1 : 0));
                work->unk02C++;
            } else {
                work->unk044 = 0.0f;
            }
            if (work->unk044 <= 0.0f && obj->trans.y <= groundY) {
                motion = 6;
                work->unk028 = 1;
                obj->trans.y = groundY;
                work->unk044 = 0.0f;
                if (work->unk010 != -1) {
                    omVibrate(work->unk004, 12, 6, 6);
                }
                if (work->unk030 == 2 && lbl_1_bss_AC == 1004) {
                    lbl_1_data_1A0[work->unk000] = (obj->trans.x < -116.666664f) ? 0 : ((obj->trans.x < 116.666664f) ? 1 : 2);
                    lbl_1_data_1A0[work->unk000] += ((obj->trans.z < -116.666664f) ? 0 : ((obj->trans.z < 116.666664f) ? 1 : 2)) * 3;
                    lbl_1_data_1C0[work->unk000] = (lbl_1_data_1A0[work->unk000] == lbl_1_data_178[work->unk000 & 2]
                                                       || lbl_1_data_1A0[work->unk000] == lbl_1_data_178[(work->unk000 & 2) + 1])
                        ? 1
                        : -1;
                    lbl_1_data_1B0[work->unk000] = (lbl_1_data_1C0[work->unk000] == 1) ? 30 : 20;
                    if (lbl_1_data_1C0[work->unk000] == 1 && lbl_1_bss_D0[work->unk000 / 2 + 5].unk000 < 3) {
                        lbl_1_bss_D0[work->unk000 / 2 + 5].unk004[lbl_1_bss_D0[work->unk000 / 2 + 5].unk000] = 0.0f;
                        lbl_1_bss_D0[work->unk000 / 2 + 5].unk000++;
                    }
                    if (lbl_1_data_1C0[work->unk000] == -1 && lbl_1_bss_D0[work->unk000 / 2 + 11].unk000 < 3) {
                        lbl_1_bss_D0[work->unk000 / 2 + 11].unk004[lbl_1_bss_D0[work->unk000 / 2 + 11].unk000] = 0.0f;
                        lbl_1_bss_D0[work->unk000 / 2 + 11].unk000++;
                    }
                }
            }
            break;
        case 6:
            motion = 6;
            if (Hu3DData[obj->mdlId[0]].motIdShift == -1 && CharMotionEndCheck(work->unk00C)) {
                work->unk044 = groundY;
                work->unk028 = 0;
                motion = 7;
            }
            break;
        case 8:
        case 9:
            break;
        case 10:
        case 11:
            obj->rot.y = 2.4f + 0.8f * obj->rot.y;
            break;
        }
    }
    obj->trans.x += work->unk040;
    if (work->unk024 == 0) {
        obj->trans.y += work->unk044;
    }
    obj->trans.z += work->unk048;
    {
        float dy;
        float dist;

        dx = lbl_1_bss_B8[partner[work->unk000]]->trans.x - obj->trans.x;
        dz = lbl_1_bss_B8[partner[work->unk000]]->trans.z - obj->trans.z;
        dy = fabs(lbl_1_bss_B8[partner[work->unk000]]->trans.y - obj->trans.y);
        dy = (dy > 160.0f) ? 0.0f : ((dy > 110.0f) ? 50.0f * (1.0f - (dy - 110.0f) / 50.0f) : 50.0f);
        if (0.0f != dy) {
            if (0.0f == dx && 0.0f == dz) {
                dz = -1.0f;
            }
            dist = sqrtf(dx * dx + dz * dz);
            if (dist < 50.0f + dy) {
                dx *= (50.0f + dy) / dist;
                dz *= (50.0f + dy) / dist;
                obj->trans.x = lbl_1_bss_B8[partner[work->unk000]]->trans.x - dx;
                obj->trans.z = lbl_1_bss_B8[partner[work->unk000]]->trans.z - dz;
                work->unk060++;
            } else {
                work->unk060 = 0;
            }
        } else {
            work->unk060 = 0;
        }
        if (work->unk030 != 4) {
            obj->trans.x = (obj->trans.x < -300.0f) ? -300.0f : ((obj->trans.x > 300.0f) ? 300.0f : obj->trans.x);
            obj->trans.z = (obj->trans.z < -300.0f) ? -300.0f : ((obj->trans.z > 300.0f) ? 300.0f : obj->trans.z);
            if (obj->trans.x == lbl_1_bss_B8[work->unk000 ^ 1]->trans.x && obj->trans.y == lbl_1_bss_B8[work->unk000 ^ 1]->trans.y
                && obj->trans.z == lbl_1_bss_B8[work->unk000 ^ 1]->trans.z) {
                float dist2;

                dist2 = sqrtf(obj->trans.x * obj->trans.x + obj->trans.z * obj->trans.z);
                obj->trans.x -= 2.0f * (50.0f * (obj->trans.x / dist2));
                obj->trans.z -= 2.0f * (50.0f * (obj->trans.x / dist2));
            }
        }
    }
    if (obj->trans.y < groundY) {
        obj->trans.y = groundY;
        work->unk024 = 1;
    }
    if (work->unk01C >= 0) {
        motion = work->unk01C;
    }
    if (motion >= 0 && motion != work->unk018) {
        motIdx = motion;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[motIdx], lbl_1_data_124[motIdx], lbl_1_data_115[motIdx],
            lbl_1_data_108[motIdx] ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        work->unk018 = motion;
    }
    lbl_1_data_1B0[work->unk000] -= lbl_1_data_1B0[work->unk000] > 0;
    if (lbl_1_bss_AC >= 1004 && work->unk000 % 2 == 1) {
        team = work->unk000 / 2;
        teamA = team * 2;
        teamB = teamA + 1;
        old188 = lbl_1_data_188[team];
        if (lbl_1_data_188[team] == 30 && lbl_1_bss_AC == 1005 && 30.0f == lbl_1_bss_0[0]) {
            lbl_1_data_188[team] = 31;
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamA] + 2], Hu3DMotionMaxTimeGet(obj->mdlId[lbl_1_data_178[teamA] + 2]));
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamB] + 2], Hu3DMotionMaxTimeGet(obj->mdlId[lbl_1_data_178[teamB] + 2]));
        }
        lbl_1_data_170[team] += lbl_1_data_170[team] < 0xFFFFFFFF;
        lbl_1_data_188[team] += lbl_1_data_188[team] != 30 && lbl_1_data_188[team] < 0xFFFFFFFF
            && !(lbl_1_data_188[team] == 59 && lbl_1_data_158[0] != -1)
            && (lbl_1_data_188[team] != 31
                || Hu3DMotionTimeGet(obj->mdlId[lbl_1_data_178[work->unk000] + 2])
                    >= Hu3DMotionMaxTimeGet(obj->mdlId[lbl_1_data_178[work->unk000] + 2]) - 1.0f);
        if (lbl_1_data_188[team] >= 60) {
            s32 oldA;
            s32 oldB;

            oldA = lbl_1_data_178[teamA];
            oldB = lbl_1_data_178[teamB];
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamA] + 2], 0.0f);
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamB] + 2], 0.0f);
            lbl_1_data_188[team] = 0;
            do {
                lbl_1_data_178[teamA] = lbl_1_data_178[teamB] = rand8() % 9;
                while (lbl_1_data_178[teamA] == lbl_1_data_178[teamB]) {
                    lbl_1_data_178[teamB] = rand8() % 9;
                }
            } while (oldA == lbl_1_data_178[teamA] || oldB == lbl_1_data_178[teamB]);
            lbl_1_data_190[teamA] = lbl_1_data_190[teamB] = rand8() % 3 - 1;
            while (lbl_1_data_190[teamA] == lbl_1_data_190[teamB]) {
                lbl_1_data_190[teamB] = rand8() % 3 - 1;
            }
        }
        for (i = 0; i < 2; i++) {
            if (Hu3DMotionTimeGet(obj->mdlId[lbl_1_data_178[work->unk000 - i] + 2]) >= 58.0f && lbl_1_data_188[team] == 30) {
                Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[work->unk000 - i] + 2], 0.0f);
            }
        }
        if (lbl_1_data_158[0] == -1 && lbl_1_data_1B0[teamA] != 0 && lbl_1_data_1B0[teamB] != 0 && lbl_1_data_188[team] == 30
            && lbl_1_data_188[team] == 30 && lbl_1_data_1B0[teamA] > 0 && lbl_1_data_1C0[teamA] == 1 && lbl_1_data_1B0[teamB] > 0
            && lbl_1_data_1C0[teamB] == 1 && lbl_1_data_1A0[teamA] != lbl_1_data_1A0[teamB]) {
            lbl_1_data_188[team] = 31;
            lbl_1_data_168[team]++;
            if (lbl_1_data_168[team] == 5) {
                lbl_1_data_158[0] = team;
            }
            work->unk038 = 30;
            work->unk04C = 0;
            pwork->unk04C = 0;
            work->unk064 = (work->unk014 == 0) ? (rand8() % 10 < 5) : ((work->unk014 == 1) ? (rand8() % 10 < 3) : 0);
            pwork->unk064 = (pwork->unk014 == 0) ? (rand8() % 10 < 5) : ((pwork->unk014 == 1) ? (rand8() % 10 < 3) : 0);
            if (work->unk010 == -1 && pwork->unk010 != -1) {
                work->unk04C = 3;
                work->unk05C = 60;
                work->unk054 = 116.666664f * ((obj->trans.x < 0.0f) ? -1 : 1);
                work->unk058 = 116.666664f * ((obj->trans.z < 0.0f) ? -1 : 1);
            }
            if (pwork->unk010 == -1 && work->unk010 != -1) {
                pwork->unk04C = 3;
                pwork->unk05C = 60;
                pwork->unk054 = 116.666664f * ((pobj->trans.x < 0.0f) ? -1 : 1);
                pwork->unk058 = 116.666664f * ((pobj->trans.z < 0.0f) ? -1 : 1);
            }
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamA] + 2], 60.0f);
            Hu3DMotionTimeSet(obj->mdlId[lbl_1_data_178[teamB] + 2], 60.0f);
            if (lbl_1_bss_D0[team + 7].unk000 < 3) {
                lbl_1_bss_D0[team + 7].unk004[lbl_1_bss_D0[team + 7].unk000] = 0.0f;
                lbl_1_bss_D0[team + 7].unk000++;
            }
        }
        if (old188 == 0 && lbl_1_data_188[team] == 1 && lbl_1_bss_D0[team + 1].unk000 < 3) {
            lbl_1_bss_D0[team + 1].unk004[lbl_1_bss_D0[team + 1].unk000] = 0.0f;
            lbl_1_bss_D0[team + 1].unk000++;
        }
        if (old188 == 31 && lbl_1_data_188[team] == 31
            && Hu3DMotionTimeGet(obj->mdlId[lbl_1_data_178[work->unk000] + 2]) == Hu3DMotionMaxTimeGet(obj->mdlId[lbl_1_data_178[work->unk000] + 2]) - 85.0f
            && lbl_1_bss_D0[team + 9].unk000 < 3) {
            lbl_1_bss_D0[team + 9].unk004[lbl_1_bss_D0[team + 9].unk000] = 0.0f;
            lbl_1_bss_D0[team + 9].unk000++;
        }
        if (old188 == 32 && lbl_1_data_188[team] == 33 && lbl_1_bss_D0[team + 3].unk000 < 3) {
            lbl_1_bss_D0[team + 3].unk004[lbl_1_bss_D0[team + 3].unk000] = 0.0f;
            lbl_1_bss_D0[team + 3].unk000++;
        }
        for (i = 0; i < 9; i++) {
            Hu3DModelAttrSet(obj->mdlId[i + 2], HU3D_ATTR_DISPOFF);
        }
        {
            float t;
            float s;

            t = (lbl_1_data_188[team] <= 30) ? lbl_1_data_188[team] / 30.0f
                : ((lbl_1_data_188[team] <= 33) ? 1.0f : 1.0f - (lbl_1_data_188[team] - 33) / 27.0f);
            s = 1.0f - t;
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_AC <= 1005) {
                    Hu3DModelAttrReset(obj->mdlId[lbl_1_data_178[teamA + i] + 2], HU3D_ATTR_DISPOFF);
                }
                Hu3DModelPosSet(obj->mdlId[lbl_1_data_178[teamA + i] + 2],
                    (i * 2 - 1) * (222.0 + s * (s * (500.0 * ((lbl_1_data_190[teamA + i] == 0) ? 1.7 : 1.0)))),
                    340.0f + s * (s * (lbl_1_data_190[teamA + i] * 500)), -850.0f - 100.0f * (1.0f - t * t));
            }
        }
        if (work->unk038 > 0 && lbl_1_data_168[team] <= 5) {
            float tp;

            fade = 1.0 - (work->unk038 - 1) / 30.0;
            espIdx = lbl_1_data_168[team] + team * 10;
            espIdx += 4;
            fade = 0.5 * fade + 0.5 * (1.0f - (1.0f - fade) * (1.0f - fade));
            tp = (fade < 0.75) ? fade / 0.75 : 1.0;
            fade = 1.0f - (1.0f - fade) * (1.0f - fade);
            tp = 1.0f - (1.0f - tp) * (1.0f - tp);
            if (work->unk038 == 30) {
                espDispOn(lbl_1_data_50[espIdx]);
                espDispOff(lbl_1_data_50[lbl_1_data_168[team] - 1 + team * 10]);
            }
            espTPLvlSet(lbl_1_data_50[espIdx], tp);
            espScaleSet(lbl_1_data_50[espIdx], 4.0f - 3.0f * fade, 4.0f - 3.0f * fade);
            work->unk038--;
        }
    }
    if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] == 1 - work->unk000 / 2 && lbl_1_bss_0[0] <= 20.0f) {
        if ((s32)lbl_1_bss_0[0] % 2 == 0) {
            Hu3DModelAttrSet(obj->mdlId[1], HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrReset(obj->mdlId[1], HU3D_ATTR_DISPOFF);
        }
    }
    Hu3DModelPosSet(obj->mdlId[1], obj->trans.x, 0.0f, obj->trans.z);
    {
        float panX;
        float panZ;

        panX = obj->trans.x / 350.0f;
        panZ = obj->trans.z / 350.0f;
        panX = (panX < -1.0f) ? -1.0f : ((panX > 1.0f) ? 1.0f : panX);
        panZ = (panZ < -1.0f) ? -1.0f : ((panZ > 1.0f) ? 1.0f : panZ);
        if (lbl_1_bss_AC > 1002 && lbl_1_bss_AC != 1006) {
            panX = 0.5 * panX + 0.5 * ((work->unk000 < 2) ? -1 : 1);
        }
        CharModelVoicePanSet(work->unk00C, 64.0f + 16.0f * panX);
        CharModelVoiceVolSet(work->unk00C, 127.0f + 15.0f * (0.5f * panZ - 0.5f));
    }
}
/* .data after jumptable_1_data_21C (emitted when fn_1_5B4 is compiled) */
/* 0x24C */ s32 lbl_1_data_24C[1] = { 0x0000008A };
/* 0x250 */ char lbl_1_data_250[] = "*** main mode error(%d)!!\n";

/* 2993 insns */
void fn_1_4F98(OMOBJ *obj)
{
    M527_PWORK *work[4];
    s32 i;
    s32 j;
    s32 k;
    s32 flip;
    M527_PWORK *pwork;
    s32 side;
    s32 idx;
    s32 cx;
    s32 cz;
    s32 lvl;
    s32 cr;
    s32 cg;
    s32 cb;
    s32 inv;
    float scale;
    float t;
    float u;
    float c1;
    float c2;
    float w;
    float l1;
    float r1;
    float l2;
    float r2;
    float grow;
    float f;
    float px;
    float pz;
    float t2;
    float c1b;
    float c2b;
    float wb;
    float l1b;
    float r1b;
    float l2b;
    float r2b;
    float sc;
    float py;
    float sc2;
    float fx;
    float fz;
    float fade;
    float r;
    float g;
    float b;

    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_B8[i]->data;
    }
    if (lbl_1_bss_AC == 1001) {
        scale = lbl_1_bss_0[0] / 115.0f;
        scale = (scale > 1.0f) ? 1.0 : ((scale >= 0.75) ? 0.66 + 0.34 * ((scale - 0.75) / 0.25) : 0.66 * (scale / 0.75));
        if (lbl_1_bss_0[0] <= 5.0f) {
            Hu3DMotionTimeSet(obj->mdlId[5], 0.0f);
        }
        Hu3DModelPosSet(obj->mdlId[5], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(obj->mdlId[5], 1.0f, 1.0f, 1.0f);
        Hu3DModelRotSet(obj->mdlId[5], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(obj->mdlId[5], 1);
        for (i = 0; i < 4; i++) {
            s32 lightMdl[4] = { 1, 4, 2, 3 };

            Hu3DLLightPosSet(obj->mdlId[lightMdl[i]], lbl_1_bss_8C[i], 0.0f, -500.0 * -HuSin(148.5 * scale), -500.0 * HuCos(148.5 * scale), 0.0f,
                -HuSin(148.5 * scale), HuCos(148.5 * scale));
        }
    } else {
        Hu3DModelAttrSet(obj->mdlId[5], 1);
    }
    if (lbl_1_bss_AC == 1002) {
        t = (lbl_1_bss_0[0] > 60.0f) ? 1.0f : lbl_1_bss_0[0] / 60.0f;
        u = HuSin(120.0f * t) / sin(2.0943951023931953);
        c1 = 320.0f - 160.0f * t;
        c2 = 320.0f + 160.0f * t;
        w = 320.0f - 160.0f * t;
        l1 = c1 - w;
        r1 = c1 + w;
        l2 = c2 - w;
        r2 = c2 + w;
        Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 10000.0f, 576.0f * (2.0f * w / 640.0f) / 480.0f);
        Hu3DCameraViewportSet(1, l1, 0.0f, r1 - l1, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(2, 40.0f, 20.0f, 10000.0f, 576.0f * (2.0f * w / 640.0f) / 480.0f);
        Hu3DCameraViewportSet(2, l2, 0.0f, r2 - l2, 480.0f, 0.0f, 1.0f);
        l2 = (r1 > l2) ? r1 : l2;
        l1 = (l1 < 0.0f) ? 0.0f : l1;
        l2 = (l2 < 0.0f) ? 0.0f : l2;
        r1 = (r1 > 640.0f) ? 640.0f : r1;
        r2 = (r2 > 640.0f) ? 640.0f : r2;
        Hu3DCameraScissorSet(1, l1, 0, r1 - l1 - 2.0f, 480);
        Hu3DCameraScissorSet(2, 2.0f + l2, 0, r2 - l2 - 2.0f, 480);
    }
    if (lbl_1_bss_AC == 1003 && 10.0f == lbl_1_bss_0[0]) {
        Hu3DMotionSet(obj->mdlId[5], obj->mtnId[0]);
        Hu3DModelAttrSet(obj->mdlId[5], 0x40000001);
    }
    if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] != 4 && 50.0f == lbl_1_bss_0[0]) {
        if (lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2]->trans.z < lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + 1]->trans.z) {
            side = 0;
        } else {
            side = 1;
        }
        flip = side;
        for (i = 0; i < 2; i++) {
            if (flip == 0) {
                idx = i;
            } else {
                idx = 1 - i;
            }
            lbl_1_bss_84[i] = lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + idx]->trans.x;
            lbl_1_bss_7C[i] = lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + ((flip == 0) ? i : 1 - i)]->trans.z;
            lbl_1_bss_84[i] = (lbl_1_bss_84[i] < -270.0f) ? -270.0f : ((lbl_1_bss_84[i] > 270.0f) ? 270.0f : lbl_1_bss_84[i]);
            lbl_1_bss_7C[i] = (lbl_1_bss_7C[i] < -270.0f) ? -270.0f : ((lbl_1_bss_7C[i] > 270.0f) ? 270.0f : lbl_1_bss_7C[i]);
        }
    }
    if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] != 4) {
        grow = 1.0f;
        f = (lbl_1_bss_0[0] < 50.0f) ? 0.0f : ((lbl_1_bss_0[0] > 70.0f) ? 1.0f : (lbl_1_bss_0[0] - 50.0f) / 20.0f);
        grow *= 1.0f - (1.0f - f) * (1.0f - f);
        for (i = 0; i < 2; i++) {
            px = lbl_1_bss_84[i];
            pz = lbl_1_bss_7C[i];
            Hu3DModelPosSet(obj->mdlId[i + 10], px, 0.0f, pz);
            Hu3DModelScaleSet(obj->mdlId[i + 10], 2.07 * grow, 1.0f, 2.07 * grow);
            Hu3DModelAttrReset(obj->mdlId[i + 10], 1);
            Hu3DModelCameraSet(obj->mdlId[i + 10], (lbl_1_data_158[0] == 1) ? 1 : 2);
            Hu3DModelCameraSet(obj->mdlId[i + 14], (lbl_1_data_158[0] == 1) ? 1 : 2);
            Hu3DModelAttrReset(obj->mdlId[i + 14], 1);
        }
    }
    if (lbl_1_bss_AC == 1005 && lbl_1_data_158[0] != 4) {
        t2 = 1.0f - ((lbl_1_bss_0[0] < 110.0f) ? 0.0f : ((lbl_1_bss_0[0] > 170.0f) ? 1.0f : (lbl_1_bss_0[0] - 110.0f) / 60.0f));
        c1b = 320.0f - 160.0f * t2;
        c2b = 320.0f + 160.0f * t2;
        wb = 320.0f - 160.0f * t2;
        l1b = c1b - wb;
        r1b = c1b + wb;
        l2b = c2b - wb;
        r2b = c2b + wb;
        Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 10000.0f, 576.0f * (2.0f * wb / 640.0f) / 480.0f);
        Hu3DCameraViewportSet(1, l1b, 0.0f, r1b - l1b, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(2, 40.0f, 20.0f, 10000.0f, 576.0f * (2.0f * wb / 640.0f) / 480.0f);
        Hu3DCameraViewportSet(2, l2b, 0.0f, r2b - l2b, 480.0f, 0.0f, 1.0f);
        if (lbl_1_data_158[0] == 0) {
            l2b = (r1b > l2b) ? r1b : l2b;
        } else {
            r1b = (r1b > l2b) ? l2b : r1b;
        }
        l1b = (l1b < 0.0f) ? 0.0f : l1b;
        l2b = (l2b < 0.0f) ? 0.0f : l2b;
        r1b = (r1b > 640.0f) ? 640.0f : r1b;
        r2b = (r2b > 640.0f) ? 640.0f : r2b;
        Hu3DCameraScissorSet(1, l1b, 0, r1b - l1b - 2.0f, 480);
        Hu3DCameraScissorSet(2, 2.0f + l2b, 0, r2b - l2b - 2.0f, 480);
    }
    if (lbl_1_bss_AC >= 1006 && lbl_1_data_158[0] != 4) {
        sc = 1.25f;
        py = (lbl_1_bss_0[0] > 60.0f) ? 0.0f : 1.0f - lbl_1_bss_0[0] / 60.0f;
        py = 270.0f - 500.0f * (py * py);
        if (lbl_1_bss_B4->mdlId[5] == lbl_1_data_1D0[lbl_1_data_158[0]]) {
            lbl_1_data_24C[0]++;
            lbl_1_data_24C[0] -= (lbl_1_data_24C[0] > 268) ? 14 : 0;
            Hu3DMotionTimeSet(lbl_1_data_1D0[lbl_1_data_158[0]], lbl_1_data_24C[0]);
            if (lbl_1_bss_AC == 1006 && 70.0f == lbl_1_bss_0[0] && lbl_1_bss_D0[15].unk000 < 3) {
                lbl_1_bss_D0[15].unk004[lbl_1_bss_D0[15].unk000] = 0.0f;
                lbl_1_bss_D0[15].unk000++;
            }
        } else {
            lbl_1_data_24C[0]++;
            lbl_1_data_24C[0] -= (lbl_1_data_24C[0] - 138 >= 140) ? 48 : 0;
            Hu3DMotionTimeSet(lbl_1_data_1D0[lbl_1_data_158[0]], lbl_1_data_24C[0] - 138);
        }
        Hu3DModelPosSet(lbl_1_data_1D0[lbl_1_data_158[0]], 0.0f, py, -1000.0f);
        Hu3DModelScaleSet(lbl_1_data_1D0[lbl_1_data_158[0]], sc, sc, sc);
        Hu3DModelRotSet(lbl_1_data_1D0[lbl_1_data_158[0]], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(lbl_1_data_1D0[lbl_1_data_158[0]], 1);
    } else if (lbl_1_bss_AC >= 1006 && lbl_1_data_158[0] == 4) {
        sc2 = 0.75f;
        lbl_1_bss_10++;
        lbl_1_bss_14[0] += 1.0 + 0.15f * HuSin(lbl_1_bss_10 * 4);
        for (i = 0; i < 2; i++) {
            Hu3DMotionTimeSet(lbl_1_data_1D0[i], lbl_1_bss_10 % 60);
            Hu3DModelPosSet(lbl_1_data_1D0[i], 30.0 * HuSin((lbl_1_bss_10 * 3) % 360) + 15.0 * HuSin(9.75 * lbl_1_bss_14[0]),
                770.0 + -750.0 * (lbl_1_bss_10 / 180.0), -1000.0f);
            Hu3DModelRotSet(lbl_1_data_1D0[i], 0.0f, 0.0f, 6.0f);
            Hu3DModelScaleSet(lbl_1_data_1D0[i], sc2, sc2, sc2);
            if (lbl_1_bss_10 < 240) {
                Hu3DModelAttrReset(lbl_1_data_1D0[i], 1);
            } else {
                Hu3DModelAttrSet(lbl_1_data_1D0[i], 1);
            }
        }
    }
    if (lbl_1_bss_AC == 1004 || lbl_1_bss_AC == 1005) {
        HuVecF col[3][3] = { 0 };
        s32 ix[2];
        s32 iz[2];
        float wx[2];
        float wz[2];

        for (k = 0; k < 2; k++) {
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    col[i][j].x = 32.0f;
                    col[i][j].y = 255.0f;
                    col[i][j].z = 200.0f;
                }
            }
            for (j = 0; j < 2; j++) {
                i = lbl_1_data_1A0[j + k * 2];
                if (lbl_1_data_1C0[j + k * 2] != 0 && lbl_1_data_1B0[j + k * 2] > 0
                    && (lbl_1_data_1A0[k * 2 + 1 - j] != lbl_1_data_1A0[j + k * 2] || lbl_1_data_1B0[k * 2 + 1 - j] == 0
                        || 0.5 * j + lbl_1_data_1B0[j + k * 2] > 0.5 + lbl_1_data_1B0[k * 2 + 1 - j] - 0.5 * j)) {
                    if (lbl_1_data_1C0[j + k * 2] == 1) {
                        fade = (lbl_1_data_1B0[j + k * 2] >= 29) ? 1.0f : ((lbl_1_data_1B0[j + k * 2] == 28) ? 0.0f : lbl_1_data_1B0[j + k * 2] / 27.0f);
                        fade = ((29 - lbl_1_data_1B0[j + k * 2]) % 2 == 0) ? fade : 0.0f;
                        lvl = 255.0f * fade;
                        inv = 255 - lvl;
                        cr = lvl / 2;
                        cg = lvl;
                        cb = lvl;
                        col[i % 3][i / 3].x += cr;
                        col[i % 3][i / 3].y += cg;
                        col[i % 3][i / 3].z += cb;
                        col[i % 3][i / 3].x = (col[i % 3][i / 3].x > 375.0f) ? 375.0f : col[i % 3][i / 3].x;
                        col[i % 3][i / 3].y = (col[i % 3][i / 3].y > 375.0f) ? 375.0f : col[i % 3][i / 3].y;
                        col[i % 3][i / 3].z = (col[i % 3][i / 3].z > 375.0f) ? 375.0f : col[i % 3][i / 3].z;
                    } else {
                        fade = (lbl_1_data_1B0[j + k * 2] >= 19) ? 1.0f : ((lbl_1_data_1B0[j + k * 2] == 18) ? 0.0f : lbl_1_data_1B0[j + k * 2] / 17.0f);
                        lvl = 255.0f * fade;
                        inv = 255 - lvl;
                        cr = lvl;
                        cg = lvl;
                        cb = (lvl < 128) ? lvl : 255 - lvl;
                        col[i % 3][i / 3].x = cr * (255.0f - col[i % 3][i / 3].x) / 255.0f + inv * col[i % 3][i / 3].x / 255.0f;
                        col[i % 3][i / 3].y = cg * (255.0f - col[i % 3][i / 3].y) / 255.0f + inv * col[i % 3][i / 3].y / 255.0f;
                        col[i % 3][i / 3].z = cb * (255.0f - col[i % 3][i / 3].z) / 255.0f + inv * col[i % 3][i / 3].z / 255.0f;
                    }
                }
            }
            for (j = 0; j < 2; j++) {
                pwork = lbl_1_bss_B8[j + k * 2]->data;
                fx = 0.5f + lbl_1_bss_B8[j + k * 2]->trans.x / 933.3333f;
                fx = (fx < 0.0f) ? 0.0f : ((fx > 1.0f) ? 1.0f : fx);
                cx = fx / 0.25f;
                cx = (cx >= 4) ? 3 : cx;
                fx = 4.0f * fx - (s32)(fx / 0.25f);
                fz = 0.5f + lbl_1_bss_B8[j + k * 2]->trans.z / 933.3333f;
                fz = (fz < 0.0f) ? 0.0f : ((fz > 1.0f) ? 1.0f : fz);
                cz = fz / 0.25f;
                cz = (cz >= 4) ? 3 : cz;
                fz = 4.0f * fz - (s32)(fz / 0.25f);
                ix[0] = (cx == 0) ? 0 : cx - 1;
                ix[1] = (cx == 3) ? 2 : cx;
                wx[0] = 1.0f - fx;
                wx[1] = fx;
                iz[0] = (cz == 0) ? 0 : cz - 1;
                iz[1] = (cz == 3) ? 2 : cz;
                wz[0] = 1.0f - fz;
                wz[1] = fz;
                r = g = b = 0.0f;
                for (i = 0; i < 4; i++) {
                    r += wz[i / 2] * (wx[i % 2] * col[ix[i % 2]][iz[i / 2]].x);
                    g += wz[i / 2] * (wx[i % 2] * col[ix[i % 2]][iz[i / 2]].y);
                    b += wz[i / 2] * (wx[i % 2] * col[ix[i % 2]][iz[i / 2]].z);
                }
                Hu3DLLightColorSet(lbl_1_bss_B8[j + k * 2]->mdlId[0], pwork->unk068, 2.0f * r / 3.0f, 2.0f * g / 3.0f, 2.0f * b / 3.0f, 255);
            }
        }
    }
}

/* 614 insns -- HU3DMODELHOOK (fn_1_B8C4 0xBCA4, one per side: modelP is
 * mdlId[6] -> side 0, otherwise side 1). While lbl_1_bss_AC == 1005 and this is
 * the side 1 - lbl_1_data_158[0], draws a textured quad at each player's
 * (bss_84[i], bss_7C[i]) that grows with lbl_1_bss_0 (50..70). */
void fn_1_7E5C(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx m;
    Mtx proj; /* retail: a 48-byte Mtx handed to C_MTXOrtho (writes 64) */
    s32 side = (modelP == &Hu3DData[lbl_1_bss_B4->mdlId[6]]) ? 0 : 1;
    float vtx[4][3] = { { -1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 1.0f } };
    s32 i;
    s32 j;
    float scale;
    float t;
    float px;
    float pz;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_FALSE);
    GXSetColorUpdate(GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    if (lbl_1_bss_AC == 1005 && side == 1 - lbl_1_data_158[0]) {
        GXSetColorUpdate(GX_FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 128, GX_AOP_AND, GX_GEQUAL, 128);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        HuSprTexLoad(espanim[esprite[lbl_1_bss_210].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        for (i = 0; i < 2; i++) {
            scale = 133.33333f;
            t = (lbl_1_bss_0[0] < 50.0f) ? 0.0f : ((lbl_1_bss_0[0] > 70.0f) ? 1.0f : (lbl_1_bss_0[0] - 50.0f) / 20.0f);
            scale *= 1.0f - (1.0f - t) * (1.0f - t);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            for (j = 0; j < 4; j++) {
                px = lbl_1_bss_84[i];
                pz = lbl_1_bss_7C[i];
                GXPosition3f32(px + scale * vtx[j][0], 1.5f, pz + scale * vtx[j][2]);
                GXColor4u8(255, 255, 255, 255);
                GXTexCoord2f32((1.0f + vtx[j][0]) / 2.0f, (1.0f + vtx[j][2]) / 2.0f);
            }
        }
        GXPixModeSync();
    }
    GXSetColorUpdate(GX_TRUE);
    C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCLR, GX_BL_ONE, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    for (i = 0; i < 1; i++) {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, 0.0f);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(1.0f, 0.0f, 0.0f);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(1.0f, 1.0f, 0.0f);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(0.0f, 1.0f, 0.0f);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 1.0f);
    }
    GXSetColorUpdate(GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
}

/* 832 insns -- HU3DMODELHOOK (fn_1_B8C4 0xBEC0; modelP is mdlId[14] -> side 0).
 * Alpha-compares a pie wedge facing the other side's player, then (bss_AC ==
 * 1005) draws a 26-vertex alpha-graded triangle strip round this side's player. */
void fn_1_87F4(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 side = (modelP == &Hu3DData[lbl_1_bss_B4->mdlId[14]]) ? 0 : 1;
    float vtx[4][3] = { { -1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 1.0f } };
    float circle[12][2] = {
        { 50.0f, 0.0f }, { 43.30127f, -25.0f }, { 24.999998f, -43.30127f }, { -2e-06f, -49.999996f },
        { -25.0f, -43.301266f }, { -43.301266f, -24.999996f }, { -49.999992f, 1e-06f }, { -43.30126f, 24.999998f },
        { -24.999992f, 43.301266f }, { 5e-06f, 49.999992f }, { 25.0f, 43.30126f }, { 43.301266f, 24.999992f },
    };
    float px;
    float pz;
    s32 i;
    s32 k;
    float dx;
    float dz;
    float ang;
    float half;
    float angLo;
    float angHi;
    float scale;
    float t;

    dx = lbl_1_bss_84[1 - side] - lbl_1_bss_84[side];
    dz = lbl_1_bss_7C[1 - side] - lbl_1_bss_7C[side];
    ang = atan2(dx, dz) / M_PI * 180.0 - 90.0;
    ang += (ang < 0.0f) ? 360 : ((ang >= 360.0f) ? -360 : 0);
    ang += (ang < 0.0f) ? 360 : ((ang >= 360.0f) ? -360 : 0);
    half = sqrtf(dx * dx + dz * dz) / 200.0f;
    half = (half > 1.0f) ? -1.0 : 90.0 * (1.0 - 2.0 * (asinf(half) / M_PI));
    angLo = ang - half;
    angHi = ang + half;
    angLo += (angLo < 0.0f) ? 360 : ((angLo >= 360.0f) ? -360 : 0);
    angLo += (angLo < 0.0f) ? 360 : ((angLo >= 360.0f) ? -360 : 0);
    angHi += (angHi < 0.0f) ? 360 : ((angHi >= 360.0f) ? -360 : 0);
    angHi += (angHi < 0.0f) ? 360 : ((angHi >= 360.0f) ? -360 : 0);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    if (half == -1.0f || (s32)(255.0f * angLo / 360.0f) == (s32)(255.0f * angHi / 360.0f)) {
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    } else if (angLo < angHi) {
        GXSetAlphaCompare(GX_LEQUAL, 255.0f * angLo / 360.0f, GX_AOP_OR, GX_GEQUAL, 255.0f * angHi / 360.0f);
    } else {
        GXSetAlphaCompare(GX_LEQUAL, 255.0f * angLo / 360.0f, GX_AOP_AND, GX_GEQUAL, 255.0f * angHi / 360.0f);
    }
    GXSetZCompLoc(GX_FALSE);
    GXSetColorUpdate(GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    if (lbl_1_bss_AC == 1005) {
        for (k = 0; k < 1; k++) {
            scale = 2.07f;
            t = ((lbl_1_bss_0[0] - 1.0f) < 50.0f) ? 0.0f : (((lbl_1_bss_0[0] - 1.0f) > 70.0f) ? 1.0f : ((lbl_1_bss_0[0] - 1.0f) - 50.0f) / 20.0f);
            scale *= 1.0f - (1.0f - t) * (1.0f - t);
            px = lbl_1_bss_84[side];
            pz = lbl_1_bss_7C[side];
            scale = (scale < 0.005f) ? 0.0f : scale - 0.005f;
            GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 26);
            for (i = 0; i < 26; i++) {
                GXPosition3f32(px + scale * circle[(i / 2) % 12][0], (i % 2 == 1) ? -400.391602 : 0.0, pz + scale * circle[(i / 2) % 12][1]);
                GXColor4u8(255, 255, 255, (i / 2) * 255 / 12);
                GXTexCoord2f32(0.0f, 0.0f);
            }
        }
        GXPixModeSync();
    }
    GXSetColorUpdate(GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
}

/* 701 insns -- HU3DMODELHOOK (fn_1_B8C4 0xBD10; modelP is mdlId[8] -> side 0).
 * For each of this side's two players k = side * 2 + i with lbl_1_data_1C0[k]
 * set and a positive timer lbl_1_data_1B0[k], flashes the board cell
 * lbl_1_data_1A0[k] (3x3 grid, 233.3 units a cell). */
void fn_1_94F4(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 side = (modelP == &Hu3DData[lbl_1_bss_B4->mdlId[8]]) ? 0 : 1;
    float vtx[4][3] = { { -1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 1.0f } };
    s32 i;
    s32 cell;
    s32 a;
    s32 alpha;
    s32 r;
    s32 g;
    s32 b;
    float t;
    float x0;
    float z0;
    float x1;
    float z1;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_INVDSTCLR, GX_BL_SRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 2; i++) {
        cell = lbl_1_data_1A0[side * 2 + i];
        if (lbl_1_data_1C0[side * 2 + i] != 0 && lbl_1_data_1B0[side * 2 + i] > 0
            && (lbl_1_data_1A0[side * 2 + 1 - i] != lbl_1_data_1A0[side * 2 + i] || lbl_1_data_1B0[side * 2 + 1 - i] == 0
                || 0.5 * i + lbl_1_data_1B0[side * 2 + i] > 0.5 + lbl_1_data_1B0[side * 2 + 1 - i] - 0.5 * i)) {
            x0 = 116.666664f * ((cell % 3) * 2 - 3);
            z0 = 116.666664f * ((cell / 3) * 2 - 3);
            x1 = 116.666664f * ((cell % 3) * 2 - 1);
            z1 = 116.666664f * ((cell / 3) * 2 - 1);
            if (lbl_1_data_1C0[side * 2 + i] == 1) {
                t = (lbl_1_data_1B0[side * 2 + i] >= 29) ? 1.0f : ((lbl_1_data_1B0[side * 2 + i] == 28) ? 0.0f : lbl_1_data_1B0[side * 2 + i] / 27.0f);
                t = ((29 - lbl_1_data_1B0[side * 2 + i]) % 2 == 0) ? t : 0.0f;
                GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
                a = 255.0f * t;
                alpha = 255 - a;
                r = a / 2;
                g = a;
                b = a;
            } else {
                t = (lbl_1_data_1B0[side * 2 + i] >= 19) ? 1.0f : ((lbl_1_data_1B0[side * 2 + i] == 18) ? 0.0f : lbl_1_data_1B0[side * 2 + i] / 17.0f);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_INVDSTCLR, GX_BL_SRCALPHA, GX_LO_NOOP);
                a = 255.0f * t;
                alpha = 255 - a;
                r = a;
                g = a;
                b = (a < 128) ? a : 255 - a;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(x0, 0.0f, z0);
            GXColor4u8(r, g, b, alpha);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(x1, 0.0f, z0);
            GXColor4u8(r, g, b, alpha);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(x1, 0.0f, z1);
            GXColor4u8(r, g, b, alpha);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(x0, 0.0f, z1);
            GXColor4u8(r, g, b, alpha);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXSetColorUpdate(GX_TRUE);
    GXSetZCompLoc(GX_TRUE);
}

/* 58 insns */
void fn_1_9FE8(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    Hu3DMatLightSet(drawObj->model, 0, material->hiliteScale);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_DIVIDE_2, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
}

/* 1533 insns */
void fn_1_A0D0(OMOBJ *obj)
{
    s32 i;
    s32 vibNo;
    s32 vibNo2;
    s32 loseRight;
    s32 mdlNo;
    M527_PWORK *work[4];

    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_B8[i]->data;
    }
    for (i = 0; i < 16; i++) {
        s32 seTbl[16] = { 0x776, 0x777, 0x778, 0x779, 0x77A, 0x77B, 0x77C, 0x77D, 0x77E, 0x77F, 0x780, 0x781, 0x782, 0x783, 0x784, 0x785 };
        s32 fxNo;
        if (lbl_1_bss_D0[i].unk000 > 3) {
            lbl_1_bss_D0[i].unk000 = 3;
        }
        if (lbl_1_bss_D0[i].unk000 > 0) {
            fxNo = HuAudFXPlay(seTbl[i]);
            lbl_1_bss_D0[i].unk010 = fxNo;
            lbl_1_bss_D0[i].unk000--;
        }
    }
    if (omSysExitReq && !WipeCheckEnd() && !lbl_1_bss_8[0]) {
        HuAudFadeOut(1000);
        lbl_1_data_164[0] = 1;
        lbl_1_bss_8[0] = 1;
    }
    switch (lbl_1_bss_AC) {
        case 1000:
            lbl_1_bss_0[0] += 1.0f;
            if (!WipeCheckEnd()) {
                lbl_1_bss_AC++;
                lbl_1_bss_0[0] = 0.0f;
            }
            break;
        case 1001:
            if (1.0f == lbl_1_bss_0[0] && lbl_1_bss_D0[0].unk000 < 3) {
                lbl_1_bss_D0[0].unk004[lbl_1_bss_D0[0].unk000] = 0.0f;
                lbl_1_bss_D0[0].unk000++;
            }
            lbl_1_bss_0[0] += 1.0f;
            if ((s32)lbl_1_bss_0[0] % 10 == 1) {
                vibNo = (s32)(lbl_1_bss_0[0] - 1.0f) / 10;
                vibNo = (vibNo > 5) ? 5 - (vibNo - 5) : vibNo;
                vibNo = (vibNo < 0) ? 0 : vibNo;
                for (i = 0; i < 4; i++) {
                    if (work[i]->unk010 != -1) {
                        s32 vibTbl[6][2] = { { 1, 9 }, { 2, 8 }, { 3, 7 }, { 4, 6 }, { 5, 5 }, { 6, 4 } };
                        omVibrate(work[i]->unk004, 10, vibTbl[vibNo][0], vibTbl[vibNo][1]);
                    }
                }
            }
            if (lbl_1_bss_0[0] >= 135.0f) {
                lbl_1_bss_AC++;
                lbl_1_bss_0[0] = 0.0f;
            }
            break;
        case 1002:
            lbl_1_bss_0[0] += 1.0f;
            if (lbl_1_bss_0[0] > 60.0f) {
                lbl_1_bss_AC++;
                lbl_1_bss_0[0] = 0.0f;
            }
            break;
        case 1003:
            lbl_1_bss_0[0] += 1.0f;
            if (5.0f == lbl_1_bss_0[0] && lbl_1_bss_A6 < 0) {
                lbl_1_bss_A6 = GameMesMgStartCreate();
            }
            if (lbl_1_bss_0[0] >= 5.0f && lbl_1_data_160[0] == -1) {
                lbl_1_data_160[0] = HuAudSStreamPlay(60);
            }
            if (lbl_1_bss_0[0] >= 5.0f && !GameMesStatGet(lbl_1_bss_A6) && lbl_1_bss_A6 >= 0) {
                lbl_1_bss_AC++;
                lbl_1_bss_A0 = 3600;
                lbl_1_bss_A6 = -1;
                lbl_1_bss_0[0] = 0.0f;
                for (i = 0; i < 4; i++) {
                    work[i]->unk030 = 2;
                }
                for (i = 0; i < 20; i++) {
                    if (i % 10 >= 0 && i % 10 <= 4) {
                        espDispOn(lbl_1_data_50[i]);
                    }
                }
                MgScoreWinDispSet(lbl_1_bss_78[0], 1);
                MgScoreWinDispSet(lbl_1_bss_78[1], 1);
            }
            break;
        case 1004:
            lbl_1_bss_0[0] += 1.0f;
            if (lbl_1_bss_A0 == 3600) {
                lbl_1_bss_A4 = GameMesTimerCreate(lbl_1_bss_A0 / 60);
                GameMesPosSet(lbl_1_bss_A4, 288.0f, 64.0f);
            }
            if (lbl_1_bss_A0 <= 3600) {
                GameMesTimerValueSet(lbl_1_bss_A4, (lbl_1_bss_A0 + 58) / 60);
            }
            lbl_1_bss_A0--;
            if (lbl_1_bss_A0 <= 0 || lbl_1_data_158[0] != -1) {
                lbl_1_bss_AC = 1005;
                lbl_1_bss_0[0] = 0.0f;
                lbl_1_data_158[0] = (lbl_1_data_158[0] != -1) ? lbl_1_data_158[0] : ((lbl_1_data_168[0] > lbl_1_data_168[1]) ? 0 : ((lbl_1_data_168[0] < lbl_1_data_168[1]) ? 1 : 4));
                for (i = 0; i < 4; i++) {
                    work[i]->unk030 = (work[i]->unk030 == 2) ? 3 : work[i]->unk030;
                }
                if (lbl_1_data_158[0] != 4 && lbl_1_bss_A0 >= 2341) {
                    lbl_1_data_1D0[0] = lbl_1_data_1D0[1] = lbl_1_bss_B4->mdlId[5];
                    break;
                }
                for (i = 0; i < 2; i++) {
                    do {
                        mdlNo = rand8() % 9;
                    } while (mdlNo == lbl_1_data_178[i * 2] || mdlNo == lbl_1_data_178[i * 2 + 1]);
                    lbl_1_data_1D0[i] = lbl_1_bss_B8[i * 2 + 1]->mdlId[mdlNo + 2];
                }
            }
            break;
        case 1005:
            if (lbl_1_bss_A6 < 0 && 0.0f == lbl_1_bss_0[0]) {
                GameMesTimerEnd(lbl_1_bss_A4);
                lbl_1_bss_A6 = GameMesMgFinishCreate();
                if (lbl_1_data_160[0] != -1) {
                    HuAudSStreamFadeOut(lbl_1_data_160[0], 100);
                }
            } else if (!GameMesStatGet(lbl_1_bss_A6) && lbl_1_bss_0[0] >= 180 + ((lbl_1_data_158[0] != 4) ? 30 : 0)) {
                lbl_1_bss_AC++;
                lbl_1_bss_0[0] = 0.0f;
                if (lbl_1_data_158[0] != 4) {
                    loseRight = lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2]->trans.x > lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + 1]->trans.x;
                    GWMgCoinBonusSet(work[lbl_1_data_158[0] * 2]->unk004, 10);
                    GWMgCoinBonusSet(work[lbl_1_data_158[0] * 2 + 1]->unk004, 10);
                    lbl_1_bss_A6 = GameMesMgWinnerCreate(work[lbl_1_data_158[0] * 2]->unk00C, work[lbl_1_data_158[0] * 2 + 1]->unk00C, -1, -1);
                    HuAudSStreamPlay(121);
                    lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2]->trans.x = (loseRight * 2 - 1) * (650.0 + 100.0 * (rand8() / 255.0) - 50.0);
                    lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + 1]->trans.x = (loseRight * 2 - 1) * -(650.0 + 100.0 * (rand8() / 255.0) - 50.0);
                    lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2]->trans.x = (loseRight * 2 - 1) * 850;
                    lbl_1_bss_B8[(1 - lbl_1_data_158[0]) * 2 + 1]->trans.x = (loseRight * 2 - 1) * -850;
                    for (i = 0; i < 2; i++) {
                        lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->trans.y = 100.0f;
                        lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->trans.z = -850.0f;
                        lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->rot.y = lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->rot.y = 0.0f;
                        lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->rot.x = 360.0f * ((rand8() % 256) / 256.0f);
                        Hu3DModelCameraSet(lbl_1_bss_B8[i + (1 - lbl_1_data_158[0]) * 2]->mdlId[0], (lbl_1_data_158[0] == 0) ? 1 : 2);
                    }
                    Hu3DModelCameraSet(lbl_1_bss_B4->mdlId[0], (lbl_1_data_158[0] == 0) ? 1 : 2);
                    Hu3DModelCameraSet(lbl_1_bss_B4->mdlId[1], (lbl_1_data_158[0] == 0) ? 1 : 2);
                    Hu3DModelCameraSet(lbl_1_bss_B4->mdlId[4], (lbl_1_data_158[0] == 0) ? 1 : 2);
                    Hu3DModelCameraSet(lbl_1_bss_B4->mdlId[5], (lbl_1_data_158[0] == 0) ? 1 : 2);
                    Hu3DModelAttrSet(lbl_1_bss_B4->mdlId[3 - lbl_1_data_158[0]], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_B4->mdlId[9 - lbl_1_data_158[0]], HU3D_ATTR_DISPOFF);
                } else {
                    lbl_1_bss_A6 = GameMesMgDrawCreate();
                    HuAudSStreamPlay(123);
                    for (i = 0; i < 4; i++) {
                        CharFXPlay(work[i]->unk00C, 0x200);
                    }
                }
            }
            lbl_1_bss_0[0] += 1.0f;
            if (lbl_1_data_158[0] != 4 && 40.0f == lbl_1_bss_0[0]
                && (work[(1 - lbl_1_data_158[0]) * 2]->unk018 != 0 || work[(1 - lbl_1_data_158[0]) * 2 + 1]->unk018 != 0)) {
                lbl_1_bss_0[0] -= 1.0f;
            }
            break;
        case 1006:
            lbl_1_bss_0[0] += 1.0f;
            if ((s32)lbl_1_bss_0[0] % 10 == 1) {
                vibNo2 = (s32)(lbl_1_bss_0[0] - 1.0f) / 5;
                vibNo2 = (vibNo2 > 5) ? 5 - (vibNo2 - 5) : vibNo2;
                for (i = 0; i < 4; i++) {
                    if (lbl_1_data_158[0] == i / 2 && work[i]->unk010 != -1 && vibNo2 >= 0 && vibNo2 < 6) {
                        s32 vibTbl[6][2] = { { 1, 9 }, { 2, 8 }, { 3, 7 }, { 4, 6 }, { 5, 5 }, { 6, 4 } };
                        omVibrate(work[i]->unk004, 10, vibTbl[vibNo2][0], vibTbl[vibNo2][1]);
                    }
                }
            }
            for (i = 0; i < 4; i++) {
                if (lbl_1_data_158[0] == 4 || lbl_1_data_158[0] == i / 2) {
                    work[i]->unk030 = (work[i]->unk030 == 3) ? 5 : work[i]->unk030;
                }
            }
            if (210.0f < lbl_1_bss_0[0] && !lbl_1_bss_8[0]) {
                lbl_1_bss_A6 = -1;
                lbl_1_bss_8[0] = 1;
            }
            break;
        default:
            OSReport(lbl_1_data_250, lbl_1_bss_AC);
            break;
    }
}
/* .data after jumptable_1_data_26C (CodeWarrior emits the table when fn_1_A0D0 is compiled) */
/* 0x288 */ char lbl_1_data_288[] = "******* M527 ObjectSetup *********\n";

/* 721 insns */
void fn_1_B8C4(OMOBJ *obj)
{
    int mdlNo;
    int i;
    s16 light;
    int j;

    mdlNo = 0;
    obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550000);
    Hu3DModelLayerSet(obj->mdlId[mdlNo], 4);
    Hu3DModelCameraSet(obj->mdlId[mdlNo], 3);
    Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
    mdlNo = 1;
    obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550001);
    Hu3DModelLayerSet(obj->mdlId[mdlNo], 5);
    Hu3DModelCameraSet(obj->mdlId[mdlNo], 3);
    Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 0.0f, 500.0f, 0.0f, 0.0f, 4.0f, 0xFF, 0xFF, 0xFF);
    lbl_1_bss_8C[0] = light;
    Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
    mdlNo = 4;
    obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550004);
    Hu3DModelLayerSet(obj->mdlId[mdlNo], 5);
    Hu3DModelCameraSet(obj->mdlId[mdlNo], 3);
    Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowMapSet(obj->mdlId[mdlNo]);
    light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 0.0f, 500.0f, 0.0f, 0.0f, 4.0f, 0xFF, 0xFF, 0xFF);
    lbl_1_bss_8C[1] = light;
    Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
    for (i = 0; i < 2; i++) {
        mdlNo = (i == 0) ? 2 : 3;
        obj->mdlId[mdlNo] = Hu3DModelCreateData((i == 0) ? 0x550002 : 0x550003);
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 4);
        Hu3DModelCameraSet(obj->mdlId[mdlNo], (i == 0) ? 1 : 2);
        Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
        light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 0.0f, 500.0f, 0.0f, 0.0f, 4.0f, 0xFF, 0xFF, 0xFF);
        lbl_1_bss_8C[i + 2] = light;
        Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
        mdlNo = (i == 0) ? 6 : 7;
        obj->mdlId[mdlNo] = Hu3DHookFuncCreate(fn_1_7E5C);
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 3);
        Hu3DModelCameraSet(obj->mdlId[mdlNo], (i == 0) ? 1 : 2);
        mdlNo = (i == 0) ? 8 : 9;
        obj->mdlId[mdlNo] = Hu3DHookFuncCreate(fn_1_94F4);
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 6);
        Hu3DModelCameraSet(obj->mdlId[mdlNo], (i == 0) ? 1 : 2);
        mdlNo = i + 10;
        if (i == 0) {
            obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550007);
        } else {
            obj->mdlId[mdlNo] = Hu3DModelLink(obj->mdlId[mdlNo - 1]);
        }
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 1);
        Hu3DModelCameraSet(obj->mdlId[mdlNo], 3);
        Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
        light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 0.0f, 500.0f, 0.0f, 1.0f, -4.0f, 0xFF, 0xFF, 0xFF);
        Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
        Hu3DModelMatHookSet(obj->mdlId[mdlNo], fn_1_9FE8);
        Hu3DModelAmbSet(obj->mdlId[mdlNo], 0.5f, 0.5f, 0.5f);
        mdlNo = i + 14;
        obj->mdlId[mdlNo] = Hu3DHookFuncCreate(fn_1_87F4);
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 0);
        Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
    }
    mdlNo = 5;
    obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550008);
    obj->mtnId[0] = Hu3DJointMotionData(obj->mdlId[mdlNo], 0x550012);
    obj->mtnId[1] = Hu3DJointMotionData(obj->mdlId[mdlNo], 0x550013);
    Hu3DMotionSet(obj->mdlId[mdlNo], obj->mtnId[1]);
    Hu3DModelLayerSet(obj->mdlId[mdlNo], 4);
    Hu3DModelCameraSet(obj->mdlId[mdlNo], 3);
    Hu3DModelAttrReset(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
    light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 500.0f, -500.0f, 0.0f, -1.0f, 1.0f, 0xFF, 0xFF, 0xFF);
    Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
    Hu3DLLightStaticSet(obj->mdlId[mdlNo], light, 1);
    for (i = 0; i < 20; i++) {
        int xBase[2] = { 82, 494 };
        int yBase[2] = { 54, 54 };
        int xOfs[20] = { -48, -24, 0, 24, 48 };
        int yOfs[20] = { 0 };

        lbl_1_data_50[i] = espEntry(lbl_1_data_0[i], 0, 0);
        espDispOff(lbl_1_data_50[i]);
        espAttrSet(lbl_1_data_50[i], 1);
        espBankSet(lbl_1_data_50[i], 0);
        j = i % 10;
        j = (j >= 5) ? j - 5 : j;
        espPosSet(lbl_1_data_50[i], xOfs[j] + xBase[(i < 10) ? 0 : 1], yOfs[j] + yBase[(i < 10) ? 0 : 1]);
    }
    lbl_1_bss_78[0] = MgScoreWinCreate(0x88, 0x24);
    MgScoreWinColorSet(lbl_1_bss_78[0], 250, 0, 30);
    MgScoreWinPosSet(lbl_1_bss_78[0], 82.0f, 56.0f);
    MgScoreWinDispSet(lbl_1_bss_78[0], 0);
    lbl_1_bss_78[1] = MgScoreWinCreate(0x88, 0x24);
    MgScoreWinColorSet(lbl_1_bss_78[1], 0, 50, 250);
    MgScoreWinPosSet(lbl_1_bss_78[1], 494.0f, 56.0f);
    MgScoreWinDispSet(lbl_1_bss_78[1], 0);
    lbl_1_bss_210 = espEntry(0x550006, 0, 0);
    espDispOff(lbl_1_bss_210);
    obj->objFunc = fn_1_4F98;
}

/* 472 insns */
void fn_1_C408(OMOBJ *obj)
{
    M527_PWORK *work;
    int padList[4] = { 0, 1, 2, 3 };
    s16 light;
    float amb;
    int mdlNo;
    int i;
    int j;
    int n;

    n = 0;
    work = obj->data;
    memset(work, 0, sizeof(M527_PWORK));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayerConf[j].grp) {
                padList[n] = j;
                n++;
            }
        }
    }
    work->unk000 = obj->work[0];
    work->unk004 = padList[work->unk000];
    if (work->unk004 == 4) {
        work->unk004 = work->unk000;
    }
    work->unk00C = GwPlayerConf[work->unk004].charNo;
    work->unk008 = (work->unk00C >= 9) ? 9 : work->unk00C;
    work->unk010 = (GwPlayerConf[work->unk004].type != 0) ? -1 : GwPlayerConf[work->unk004].padNo;
    work->unk014 = (work->unk010 != -1) ? 0 : GwPlayerConf[work->unk004].dif;
    work->unk030 = 1;
    work->unk04C = 0;
    work->unk064 = (work->unk014 == 0) ? (rand8() % 10 < 5) : ((work->unk014 == 1) ? (rand8() % 10 < 3) : 0);
    obj->mdlId[0] = CharModelCreate(work->unk00C, 2);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    Hu3DModelCameraSet(obj->mdlId[0], (work->unk000 < 2) ? 1 : 2);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharEffectLayerSet(7);
    work->unk068 = Hu3DLLightCreate(obj->mdlId[0], 0.0f, -500.0f, 0.0f, 0.0f, 3.0f, -1.0f, 0x15, 0xAA, 0x85);
    Hu3DLLightInfinitytSet(obj->mdlId[0], work->unk068);
    Hu3DLLightStaticSet(obj->mdlId[0], work->unk068, 1);
    amb = 0.75f;
    if (work->unk008 == 5) {
        Hu3DModelAmbSet(obj->mdlId[0], 2.0f * amb / 3.0f, 2.0f * amb / 3.0f, 2.0f * amb / 3.0f);
    } else {
        Hu3DModelAmbSet(obj->mdlId[0], amb, amb, amb);
    }
    work->unk018 = 0;
    work->unk01C = -1;
    for (i = 0; i < 13; i++) {
        obj->mtnId[i] = CharMotionCreate(work->unk00C, lbl_1_data_D4[i]);
    }
    CharMotionVoiceOnSet(work->unk00C, (u16)lbl_1_data_D4[12], 0);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    obj->trans.x = lbl_1_data_1D8[work->unk000][0];
    obj->trans.y = lbl_1_data_1D8[work->unk000][1];
    obj->trans.z = lbl_1_data_1D8[work->unk000][2];
    obj->rot.y = lbl_1_data_1D8[work->unk000][3];
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->rot.x = obj->rot.z = 0.0f;
    obj->mdlId[1] = Hu3DModelCreateData(0x550005);
    Hu3DModelLayerSet(obj->mdlId[1], 6);
    Hu3DModelCameraSet(obj->mdlId[1], (work->unk000 / 2 == 0) ? 1 : 2);
    Hu3DModelAttrSet(obj->mdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(obj->mdlId[1], obj->trans.x, 0.0f, obj->trans.z);
    if (work->unk000 % 2 == 1) {
        for (i = 0; i < 9; i++) {
            mdlNo = i + 2;
            if (work->unk000 == 1) {
                obj->mdlId[mdlNo] = Hu3DModelCreateData(0x550009 + i);
            } else {
                obj->mdlId[mdlNo] = Hu3DModelLink(lbl_1_bss_B8[1]->mdlId[mdlNo]);
            }
            Hu3DModelLayerSet(obj->mdlId[mdlNo], 4);
            Hu3DModelCameraSet(obj->mdlId[mdlNo], (work->unk000 / 2 == 0) ? 1 : 2);
            Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
            light = Hu3DLLightCreate(obj->mdlId[mdlNo], 0.0f, 0.0f, 500.0f, 3.0f, -4.0f, -2.0f, 0xFF, 0xFF, 0xFF);
            Hu3DLLightInfinitytSet(obj->mdlId[mdlNo], light);
        }
    }
    obj->objFunc = fn_1_5B4;
}

/* 21 insns */
void fn_1_CB68(OMOBJ *obj)
{
    lbl_1_bss_AC = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    obj->objFunc = fn_1_A0D0;
}

/* 375 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;

    OSReport(lbl_1_data_288);
    lbl_1_bss_A8 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_A8);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 40.0f, 20.0f, 10000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(2, 40.0f, 20.0f, 10000.0f, 0.6f);
    Hu3DCameraViewportSet(2, 322.0f, 0.0f, 318.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 0, 0, 480);
    for (i = 0; i < 2; i++) {
        CZoomM[i] = 1775.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 340.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = -30.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
    }
    Hu3DLighInit();
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.75f, -1.0f, -0.5f };
        GXColor lightColor = { 0, 0, 0, 0 };

        lbl_1_bss_9C = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    }
    Hu3DGLightStaticSet(lbl_1_bss_9C, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_9C);
    {
        HuVecF pos;
        HuVecF up;
        HuVecF target;

        pos.x = 345.0f;
        pos.y = 10000.0 * sin(M_PI / 2);
        pos.z = 10000.0 * cos(M_PI / 2);
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
        target.x = 346.0f;
        target.y = 0.0f;
        target.z = 0.0f;
        Hu3DShadowMultiCreate(12.0f, 7000.0f, 12000.0f, 3);
        Hu3DShadowMultiTPLvlSet(0.5f, -1);
        Hu3DShadowMultiPosSet(&pos, &up, &target, -1);
    }
    lbl_1_bss_A6 = -1;
    lbl_1_data_158[0] = -1;
    lbl_1_bss_B4 = omAddObjEx(lbl_1_bss_A8, 101, 16, 2, 1, fn_1_B8C4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_B8[i] = omAddObjEx(lbl_1_bss_A8, 100, 11, 13, 0, fn_1_C408);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M527_PWORK), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_C8 = omAddObjEx(lbl_1_bss_A8, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_C8->work[0] = 2;
    lbl_1_bss_CC = omAddObjEx(lbl_1_bss_A8, 102, 0, 0, -1, fn_1_CB68);
    lbl_1_bss_B0 = omAddObjEx(lbl_1_bss_A8, 103, 1, 0, -1, fn_1_D198);
}

/* 22 insns */
void fn_1_D198(OMOBJ *obj)
{
    if (lbl_1_bss_8[0] != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        obj->objFunc = fn_1_D1F0;
    }
}

/* 46 insns */
void fn_1_D1F0(OMOBJ *obj)
{
    M527_PWORK *work;
    int i;

    if (WipeCheckEnd()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_B8[i]->data;
        CharModelKill(work->unk00C);
    }
    if (lbl_1_bss_A6 >= 0) {
        GameMesKill(lbl_1_bss_A6);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_164[0], 1);
}

