/*
 * m528Dll m528.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m528Dll/asm/REL/m528Dll/m528.s.
 */

#include "REL/m528Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ const u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 }; /* camera bits */
/* 0x18 */ /* s16 lbl_1_rodata_18[4] = { 0x0002, 0x000D, 0x0019, 0x0027 }; */
/* 0x20 */ /* float lbl_1_rodata_20 = 0.0f; */
/* 0x24 */ /* float lbl_1_rodata_24 = 3.0f; */
/* 0x28 */ /* float lbl_1_rodata_28 = 100.0f; */
/* 0x30 */ /* double lbl_1_rodata_30 = 0.5; */
/* 0x38 */ /* double lbl_1_rodata_38 = 1; */
/* 0x40 */ /* double lbl_1_rodata_40 = 3.141592653589793; */
/* 0x48 */ /* float lbl_1_rodata_48 = 180.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 60.0f; */
/* 0x50 */ /* double lbl_1_rodata_50 = 180; */
/* 0x58 */ /* float lbl_1_rodata_58 = 360.0f; */
/* 0x60 */ /* double lbl_1_rodata_60 = 0.20000000298023224; */
/* 0x68 */ /* float lbl_1_rodata_68 = 120.0f; */
/* 0x6C */ /* float lbl_1_rodata_6C = 22.5f; */
/* 0x70 */ /* double lbl_1_rodata_70 = 4503601774854144; */
/* 0x78 */ /* void *lbl_1_rodata_78[8] = { (void *)fn_1_C314, (void *)fn_1_C3DC, (void *)fn_1_C530, (void *)fn_1_C728, (void *)fn_1_C8B4, (void *)fn_1_CA34, (void *)fn_1_CAEC, (void *)fn_1_CC40 }; */
/* 0x98 */ /* s32 lbl_1_rodata_98[8] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000000, 0x00000001, 0x00000000 }; */
/* 0xB8 */ /* float lbl_1_rodata_B8 = 1000.0f; */
/* 0xBC */ /* float lbl_1_rodata_BC = -1.0f; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = -0.5f; */
/* 0xC4 */ /* float lbl_1_rodata_C4 = 15.0f; */
/* 0xC8 */ /* float lbl_1_rodata_C8 = 20.0f; */
/* 0xCC */ /* float lbl_1_rodata_CC = 20000.0f; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 1.2f; */
/* 0xD4 */ /* float lbl_1_rodata_D4 = 300.0f; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 1.0f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 150.0f; */
/* 0xE0 */ /* s32 lbl_1_rodata_E0[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0xEC */ /* s32 lbl_1_rodata_EC[3] = { 0x00000000, 0x457A0000, 0x447A0000 }; */
/* 0xF8 */ /* s32 lbl_1_rodata_F8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x104 */ /* float lbl_1_rodata_104 = 0.3f; */
/* 0x108 */ /* s16 lbl_1_rodata_108[4] = { 0x0028, 0x0038, 0x0048, 0x0058 }; */
/* 0x110 */ /* float lbl_1_rodata_110 = 2501.0f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 75.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 200.0f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 2.4f; */
/* 0x120 */ /* s32 lbl_1_rodata_120[2] = { 0x41C80000, 0x421C0000 }; */
/* 0x128 */ /* float lbl_1_rodata_128 = 6.3f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 1.5f; */
/* 0x130 */ /* s32 lbl_1_rodata_130[8] = { 0x00000032, 0x00000050, 0x0000005F, 0x00000063, 0x00000019, 0x0000000F, 0x0000000A, 0x00000005 }; */
/* 0x150 */ /* s32 lbl_1_rodata_150[8] = { 0x0000000A, 0x00000005, 0x00000000, 0x00000000, 0x0000000A, 0x00000005, 0x00000000, 0x00000000 }; */
/* 0x170 */ /* s32 lbl_1_rodata_170[8] = { 0x0000001E, 0x0000003C, 0x00000037, 0x00000032, 0x0000001E, 0x0000003C, 0x00000037, 0x00000032 }; */
/* 0x190 */ /* s32 lbl_1_rodata_190[8] = { 0x00000050, 0x00000055, 0x0000005A, 0x0000005F, 0x00000050, 0x00000055, 0x0000005A, 0x0000005F }; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 5.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 25.0f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 6.4f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 0.5f; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = -25.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 6.0f; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = 150; */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 0.95f; */
/* 0x1D4 */ /* float lbl_1_rodata_1D4 = 0.01f; */
/* 0x1D8 */ /* s32 lbl_1_rodata_1D8[2] = { 0x3F800000, 0xBF800000 }; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 500.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 2.0f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 1.8f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 1198.0f; */
/* 0x1F0 */ /* double lbl_1_rodata_1F0 = 1480; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = -620.0f; */
/* 0x200 */ /* double lbl_1_rodata_200 = 1680; */
/* 0x208 */ /* float lbl_1_rodata_208 = 90.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 30.0f; */
/* 0x210 */ /* s16 lbl_1_rodata_210[1] = { 0x0030 }; */
/* 0x212 */ /* s16 lbl_1_rodata_212[1] = { 0x0050 }; */
/* 0x214 */ /* float lbl_1_rodata_214 = -1000.0f; */
/* 0x218 */ /* s32 lbl_1_rodata_218[1] = { 0xC0E00000 }; */
/* 0x21C */ /* s32 lbl_1_rodata_21C[1] = { 0x40E00000 }; */
/* 0x220 */ /* double lbl_1_rodata_220 = 100; */
/* 0x228 */ /* double lbl_1_rodata_228 = 2.4; */
/* 0x230 */ /* double lbl_1_rodata_230 = 2; */
/* 0x238 */ /* float lbl_1_rodata_238 = -600.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = -1680.0f; */
/* 0x240 */ /* float lbl_1_rodata_240 = 600.0f; */
/* 0x244 */ /* float lbl_1_rodata_244 = 2500.0f; */
/* 0x248 */ /* s32 lbl_1_rodata_248[8] = { 0x00000014, 0x00000014, 0x0000000F, 0x0000000F, 0x0000000A, 0x0000000A, 0x00000007, 0x00000003 }; */
/* 0x268 */ /* float lbl_1_rodata_268 = 11.25f; */
/* 0x270 */ /* double lbl_1_rodata_270 = 300; */
/* 0x278 */ /* float lbl_1_rodata_278 = -300.0f; */
/* 0x280 */ /* double lbl_1_rodata_280 = 220; */
/* 0x288 */ /* double lbl_1_rodata_288 = 0.10000000149011612; */
/* 0x290 */ /* float lbl_1_rodata_290 = 0.9f; */
/* 0x298 */ /* double lbl_1_rodata_298 = 210; */
/* 0x2A0 */ /* float lbl_1_rodata_2A0 = -200.0f; */
/* 0x2A4 */ /* float lbl_1_rodata_2A4 = 0.2f; */
/* 0x2A8 */ /* float lbl_1_rodata_2A8 = 10000.0f; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 70; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 200; */
/* 0x2C0 */ /* float lbl_1_rodata_2C0 = 11.0f; */
/* 0x2C4 */ /* float lbl_1_rodata_2C4 = -400.0f; */
/* 0x2C8 */ /* float lbl_1_rodata_2C8 = -10.0f; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = 45.0f; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = -20.0f; */
/* 0x2D4 */ /* float lbl_1_rodata_2D4 = 3.7f; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = -3.7f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 55.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 84.0f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 42.0f; */
/* 0x2E8 */ /* float lbl_1_rodata_2E8 = 6.1f; */
/* 0x2EC */ /* float lbl_1_rodata_2EC = 3.3f; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 40.0f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = -5.0f; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 2.7f; */
/* 0x2FC */ /* float lbl_1_rodata_2FC = -40.0f; */
/* 0x300 */ /* float lbl_1_rodata_300 = 135.0f; */
/* 0x304 */ /* float lbl_1_rodata_304 = 4.0f; */
/* 0x308 */ /* float lbl_1_rodata_308 = -3.0f; */
/* 0x30C */ /* float lbl_1_rodata_30C = 10.0f; */
/* 0x310 */ /* float lbl_1_rodata_310 = -800.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 50.0f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 4.3f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 270.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 0.7f; */
/* 0x324 */ /* float lbl_1_rodata_324 = -700.0f; */
/* 0x328 */ /* float lbl_1_rodata_328 = 4.2f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 35.0f; */
/* 0x330 */ /* float lbl_1_rodata_330 = 28.0f; */
/* 0x334 */ /* float lbl_1_rodata_334 = 0.1f; */
/* 0x338 */ /* float lbl_1_rodata_338 = 350.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 8.0f; */
/* 0x340 */ /* float lbl_1_rodata_340 = -4.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 1680.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 1.5707964f; */
/* 0x34C */ /* float lbl_1_rodata_34C = -1.5707964f; */
/* 0x350 */ /* double lbl_1_rodata_350 = -1; */

/* --- .data --- */
/* 0x0 */ MGSEQ_PARAM lbl_1_data_0 = { 300, 0, fn_1_1E8, fn_1_238, fn_1_8E4, fn_1_954, fn_1_9CC, fn_1_B10, fn_1_ED0, fn_1_1118, fn_1_111C };
/* 0x28 */ s32 lbl_1_data_28[13][8] = { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C0008, 0x008C000A, 0x008C0009, 0x008C0006, 0x008C0007, 0x00330000, 0x00330003, 0x00330004, 0x00330008, 0x0033000A, 0x00330009, 0x00330006, 0x00330007, 0x00B70000, 0x00B70003, 0x00B70004, 0x00B70008, 0x00B7000A, 0x00B70009, 0x00B70006, 0x00B70007, 0x00ED0000, 0x00ED0003, 0x00ED0004, 0x00ED0008, 0x00ED000A, 0x00ED0009, 0x00ED0006, 0x00ED0007, 0x00E60000, 0x00E60003, 0x00E60004, 0x00E60008, 0x00E6000A, 0x00E60009, 0x00E60006, 0x00E60007, 0x00170000, 0x00170003, 0x00170004, 0x00170008, 0x0017000A, 0x00170009, 0x00170006, 0x00170007, 0x00E00000, 0x00E00003, 0x00E00004, 0x00E00008, 0x00E0000A, 0x00E00009, 0x00E00006, 0x00E00007, 0x002D0000, 0x002D0003, 0x002D0004, 0x002D0008, 0x002D000A, 0x002D0009, 0x002D0006, 0x002D0007, 0x00C90000, 0x00C90003, 0x00C90004, 0x00C90008, 0x00C9000A, 0x00C90009, 0x00C90006, 0x00C90007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B0000A, 0x00B00009, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B0000A, 0x00B00009, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B0000A, 0x00B00009, 0x00B00006, 0x00B00007, 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B0000A, 0x00B00009, 0x00B00006, 0x00B00007 };
/* 0x1C8 */ s32 lbl_1_data_1C8[54] = { 0x00560000, 0x00560001, 0x00560002, 0x00560003, 0x00560004, 0x00560005, 0x00560006, 0x00560007, 0x00560008, 0x00560009, 0x0056000A, 0x0056000D, 0x0056000E, 0x00560011, 0x00560012, 0x00560013, 0x00560014, 0x00560015, 0x00560016, 0x00560017, 0x00560018, 0x00560019, 0x0056001A, 0x0056001B, 0x0056001C, 0x0056001D, 0x0056001E, 0x0056001F, 0x00560020, 0x00560021, 0x00560022, 0x00560023, 0x00560024, 0x00560025, 0x00560026, 0x00560027, 0x00560028, 0x00560029, 0x0056002A, 0x0056002B, 0x0056002C, 0x0056002D, 0x0056002E, 0x0056002F, 0x00560030, 0x00560031, 0x00560033, 0x00560035, 0x00560037, 0x00560038, 0x00560039, 0x0056003A, 0x0056003B, 0x0056003C };
/* 0x2A0 */ s32 lbl_1_data_2A0[7] = { 0x0056000B, 0x0056000C, 0x0056000F, 0x00560010, 0x00560032, 0x00560034, 0x00560036 };
/* 0x2BC */ M528_CAMPARAM lbl_1_data_2BC[4] = { { { 0.0f, 717.0f, 0.0f }, 90.0f, 37.0f, 8680.0f }, { { 0.0f, 124.0f, 0.0f }, 90.0f, 26.0f, 3810.0f }, { { -300.0f, 124.0f, 0.0f }, 90.0f, 21.0f, 3810.0f }, { { 300.0f, 124.0f, 0.0f }, 90.0f, 21.0f, 3810.0f } };
/* 0x31C */ HuVecF lbl_1_data_31C[55] = { { 76.3527f, -28.65594f, 303.8886f }, { 89.36818f, -20.12116f, 627.3725f }, { 132.45467f, -7.8856f, 617.07947f }, { 175.47755f, 5.14328f, 603.90344f }, { 213.52226f, 19.1923f, 583.2219f }, { 258.0741f, 35.48818f, 558.334f }, { 307.4178f, 53.50759f, 528.4491f }, { 351.7477f, 71.07372f, 488.91357f }, { 387.29947f, 86.45116f, 453.47565f }, { 423.9798f, 102.31677f, 416.9127f }, { 453.92682f, 114.74768f, 374.23383f }, { 482.55255f, 128.153f, 327.6315f }, { 506.63617f, 140.91176f, 280.20404f }, { 523.21515f, 149.26572f, 234.10138f }, { 536.4226f, 157.65977f, 186.78319f }, { 545.4938f, 165.1289f, 144.12125f }, { 550.5082f, 169.3213f, 99.43111f }, { 555.52264f, 173.5137f, 54.74098f }, { 554.31415f, 178.93967f, 10.26389f }, { 548.245f, 182.21725f, -43.50827f }, { 540.7429f, 184.87166f, -94.25285f }, { 526.2494f, 189.22081f, -148.9162f }, { 508.16705f, 190.19507f, -199.4755f }, { 485.3958f, 191.22429f, -246.7632f }, { 455.54944f, 191.06044f, -297.0153f }, { 422.8942f, 189.8421f, -342.977f }, { 387.02106f, 188.64108f, -381.5805f }, { 347.565f, 184.92625f, -416.4199f }, { 297.2428f, 181.25046f, -457.2818f }, { 241.78398f, 175.96623f, -490.8356f }, { 182.54707f, 170.04622f, -518.3706f }, { 126.37634f, 165.11037f, -538.3222f }, { 64.86789f, 158.29259f, -552.0461f }, { 5.82033f, 152.42786f, -559.9274f }, { -56.36307f, 144.40205f, -559.3981f }, { -127.3225f, 136.82695f, -552.8494f }, { -175.3741f, 132.81107f, -542.1f }, { -219.185f, 128.13605f, -528.8677f }, { -271.0152f, 123.20982f, -509.1224f }, { -328.317f, 119.05633f, -478.0202f }, { -383.0389f, 115.4856f, -437.4594f }, { -429.5695f, 112.6725f, -396.8103f }, { -477.0712f, 112.08831f, -339.5657f }, { -511.2278f, 113.79501f, -290.2382f }, { -544.9306f, 114.67406f, -219.9456f }, { -565.2117f, 118.71691f, -148.9897f }, { -576.6864f, 124.72604f, -55.24234f }, { -571.7904f, 132.87604f, 20.97713f }, { -559.52f, 138.74858f, 81.16179f }, { -541.5015f, 145.87262f, 143.0994f }, { -516.2133f, 150.99301f, 190.12534f }, { -486.0693f, 159.3626f, 235.53607f }, { -453.4974f, 169.35678f, 280.1392f }, { -419.3569f, 178.96738f, 310.31488f }, { -205.5353f, 173.01883f, 111.80605f } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x29C */ OMOBJMAN *lbl_1_bss_29C;
/* 0x298 */ OMOBJ *lbl_1_bss_298; /* main object; ->data is the M528_WORK */
/* 0x4 */ HuVecF lbl_1_bss_4[55];
/* 0x0 */ s32 lbl_1_bss_0; /* BGM stream number (HuAudBGMPlay, fn_1_238) */

/* --- functions (reference order) --- */
/* 82 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    s32 i;
    M528_WORK *work;

    lbl_1_bss_29C = omInitObjMan(10, 0x2000);
    omGameSysInit(lbl_1_bss_29C);
    obj = omAddObjEx(lbl_1_bss_29C, 0x65, 0, 0, -1, fn_1_13D0);
    lbl_1_bss_298 = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M528_WORK), HU_MEMNUM_OVL);
    work = obj->data;
    fn_1_16C4(work);
    fn_1_15EC(work);
    fn_1_17B0(work);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_29C, 0x64, 1, 8, 0, fn_1_113C);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M528_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    fn_1_1538(work);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(TRUE);
    MgSeqCreate(&lbl_1_data_0);
}

/* 20 insns */
void fn_1_1E8(s16 mode, s16 frameNo)
{
    M528_WORK *work = lbl_1_bss_298->data;

    work->unk4CAC = 0;
    work->unk4CA8[0] = -1;
    work->unk4CA8[1] = -1;
    MgSeqModeNext();
}

/* 427 insns */
void fn_1_238(s16 mode, s16 frameNo)
{
    s16 sp8[4] = { 2, 13, 25, 39 };
    M528_WORK *work;
    s32 i;
    M528_PLAYER *player;
    s32 stop;
    s32 sector;

    work = lbl_1_bss_298->data;
    switch (work->unk4CAC) {
        case 0:
            MgSeqModeChangeOff();
            work->unk4C98 = 0.0f;
            work->unk4CAE = 0;
            work->unk4CAC++;
        case 1:
            work->unk4CAE++;
            if (work->unk4CAE >= 60) {
                work->unk4C94 = 3.0f + (s32)frandmod(100) / 100.0f;
                work->unk4CAE = 0;
                HuAudFXPlay(0x786);
                HuAudFXPlay(0x78E);
                work->unk4CAC++;
            }
            break;
        case 2:
            work->unk4C9C = 0.5 * (work->unk4C94 * (1.0 + cos(M_PI * (180.0f * (work->unk4CAE / 60.0f) - 180.0f) / 180.0)));
            work->unk4C98 -= work->unk4C9C;
            if (work->unk4C98 < 0.0f) {
                work->unk4C98 += 360.0f;
            }
            if (work->unk4CAE == 50) {
                work->unk3CC = fn_1_3CA0;
            }
            work->unk4CAE++;
            if (work->unk4CAE > 60) {
                work->unk4CAE = 0;
                work->unk4CAC++;
            }
            break;
        case 3:
            work->unk4C9C = 0.2f + 0.5 * (work->unk4C94 * (1.0 + cos(M_PI * (180.0f * (work->unk4CAE / 120.0f)) / 180.0)));
            work->unk4C98 -= work->unk4C9C;
            if (work->unk4C98 < 0.0f) {
                work->unk4C98 += 360.0f;
            }
            work->unk4CAE++;
            if (work->unk4CAE >= 120) {
                work->unk4CAC++;
                stop = work->unk4C98 / 22.5f;
                work->unk4CA0 = 22.5f * stop;
            }
            break;
        case 4:
            work->unk4C98 -= work->unk4C9C;
            if (work->unk4C98 <= work->unk4CA0) {
                work->unk4C98 = work->unk4CA0;
                work->unk4CAC++;
            }
            break;
        case 5:
            if (work->unk4C98 < 0.0f) {
                work->unk4C98 += 360.0f;
            }
            sector = work->unk4C98 / 22.5f;
            work->unk4CA8[0] = (16 - sector) % 16;
            work->unk4CA8[1] = (work->unk4CA8[0] + 1) % 16;
            work->unk4CAC++;
            work->unk4CAE = 0;
            fn_1_46CC(work);
            break;
        case 6:
            work->unk4CAE++;
            if (work->unk4CAE == 1) {
                work->unk3D0[0] = fn_1_47F0;
            }
            if (work->unk4CAE == 5) {
                work->unk3D0[1] = fn_1_47F0;
            }
            if (work->unk4CAE >= 8) {
                fn_1_B384(work);
                work->unk4BE4[0].unk022++;
                work->unk4BE4[1].unk022++;
                work->unk4BE4[2].unk022++;
                work->unk4BE4[3].unk022++;
                work->unk4CAE = 0;
                work->unk4CAC++;
            }
            break;
        case 7:
            work->unk4CAE++;
            for (i = 0; i < 4; i++) {
                if (work->unk4CAE == sp8[i]) {
                    player = work->unk000[i];
                    player->unk020 = 0;
                    player->unk01C = fn_1_1ECC;
                }
            }
            if (work->unk4CAE >= 40) {
                work->unk4CAE = 0;
                work->unk4CAC++;
            }
            break;
        case 8:
            lbl_1_bss_0 = HuAudBGMPlay(60);
            MgSeqModeNext();
            break;
    }
    fn_1_3A00(work);
    if (work->unk3CC && work->unk3CC(&work->unk020) != 0) {
        work->unk3CC = NULL;
    }
    if (work->unk3D0[0] && work->unk3D0[0](&work->unk03C[0]) != 0) {
        HuAudFXPlay(0x787);
        work->unk3CC = fn_1_43B4;
        work->unk020.unk018 = 0;
        work->unk3D0[0] = NULL;
    }
    if (work->unk3D0[1] && work->unk3D0[1](&work->unk03C[1]) != 0) {
        HuAudFXPlay(0x788);
        work->unk3D0[1] = NULL;
    }
}


/* 28 insns */
void fn_1_8E4(s16 mode, s16 frameNo)
{
    M528_WORK *work = lbl_1_bss_298->data;

    if (work->unk3CC && work->unk3CC(&work->unk020) != 0) {
        work->unk3CC = NULL;
    }
    work->unk4CAC = 0;
    work->unk4D6E = 0;
}

/* 30 insns */
void fn_1_954(s16 mode, s16 frameNo)
{
    M528_WORK *work = lbl_1_bss_298->data;

    work->unk4CB2 = 1;
    if (work->unk4CB0 >= 0) {
        work->unk3D8 = fn_1_4C84;
        work->unk03C[work->unk4CB0].unk054->unk026 = 0;
        work->unk4CB2 = 0;
        MgSeqModeNext();
    }
}

/* 81 insns */
void fn_1_9CC(s16 mode, s16 frameNo)
{
    M528_WORK *work;
    M528_PLAYER *player1;
    M528_PLAYER *player2;

    work = lbl_1_bss_298->data;
    work->unk4CB2 = 0;
    if (work->unk4D6E == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0, 1000);
        work->unk4D6E++;
    }
    if (work->unk4CB0 < 0) {
        MgSeqWinnerSet(-1, -1, -1, -1);
    } else {
        player1 = work->unk010[work->unk4CB0][0];
        player2 = work->unk010[work->unk4CB0][1];
        MgSeqWinnerSet(player1->unk02A, player2->unk02A, -1, -1);
        fn_1_4E80(work);
        work->unk3D0[work->unk4CB0 ^ 1] = fn_1_495C;
        work->unk03C[work->unk4CB0 ^ 1].unk062 = 0;
    }
    if (work->unk3D8 && work->unk3D8(work->unk03C[work->unk4CB0].unk054) != 0) {
        work->unk3D8 = NULL;
    }
}

/* 240 insns */
void fn_1_B10(s16 mode, s16 frameNo)
{
    void (*prizeFunc[8])(M528_WORK *work) = { fn_1_C314, fn_1_C3DC, fn_1_C530, fn_1_C728, fn_1_C8B4, fn_1_CA34, fn_1_CAEC, fn_1_CC40 };
    s32 prizeSe[8] = { 1, 1, 1, 1, 1, 0, 1, 0 };
    M528_WORK *work;
    s32 i;
    s32 loser;
    M528_PLAYER *player;

    work = lbl_1_bss_298->data;
    switch (work->unk4CAC) {
        case 0:
            MgSeqModeChangeOff();
            if (work->unk4CB0 >= 0) {
                work->unk3CC = (work->unk4CB0 != 0) ? fn_1_4158 : fn_1_3EFC;
            }
            work->unk4CAC++;
        case 1:
            if (work->unk3CC == NULL) {
                work->unk4CAC++;
            }
            break;
        case 2:
            for (i = 0; i < 4; i++) {
                player = work->unk000[i];
                if (player->unk01C != fn_1_1F8C) {
                    break;
                }
            }
            if (i == 4) {
                work->unk4CAC++;
            }
            break;
        case 3:
            if (work->unk4CB0 >= 0) {
                work->unk3D8 = fn_1_4B04;
                work->unk03C[work->unk4CB0].unk054->unk026 = 0;
                omVibrate(work->unk010[work->unk4CB0][0]->unk028, 12, 12, 0);
                omVibrate(work->unk010[work->unk4CB0][1]->unk028, 12, 12, 0);
            }
            work->unk4CAC++;
            break;
        case 4:
            if (work->unk4CB0 >= 0) {
                prizeFunc[work->unk03C[work->unk4CB0].unk054->unk02A](work);
                if (prizeSe[work->unk03C[work->unk4CB0].unk054->unk02A] != 0) {
                    HuAudFXPlay(0x78C);
                }
                if (work->unk03C[work->unk4CB0].unk054->unk02A == 7) {
                    HuAudFXPlay(0x78D);
                }
            }
            work->unk4CAE = 0;
            work->unk4CAC++;
            break;
        case 5:
            work->unk4CAE++;
            if (work->unk4CAE > 30) {
                MgSeqModeNext();
                work->unk4CAC = 0;
            }
            break;
    }
    if (work->unk3CC && work->unk3CC(&work->unk020) != 0) {
        work->unk3CC = NULL;
    }
    if (work->unk3D8 && work->unk3D8(work->unk03C[work->unk4CB0].unk054) != 0) {
        work->unk3D8 = NULL;
    }
    if (work->unk4CB0 >= 0) {
        loser = work->unk4CB0 ^ 1;
        if (work->unk3D0[loser] && work->unk3D0[loser](&work->unk03C[loser]) != 0) {
            work->unk3D0[loser] = NULL;
        }
    }
}

/* 146 insns */
void fn_1_ED0(s16 mode, s16 frameNo)
{
    M528_WORK *work;
    s32 i;
    M528_PLAYER *player;

    work = lbl_1_bss_298->data;
    switch (work->unk4CAC) {
        case 0:
            if (work->unk4CB0 < 0) {
                CharLoseVoicePlay(work->unk000[0]->unk02A, work->unk000[1]->unk02A, work->unk000[2]->unk02A, work->unk000[3]->unk02A);
                for (i = 0; i < 4; i++) {
                    player = work->unk000[i];
                    player->unk01C = fn_1_25FC;
                    player->unk020 = 0;
                }
            } else {
                for (i = 0; i < 2; i++) {
                    if (i == work->unk4CB0) {
                        player = work->unk010[i][0];
                        player->unk01C = fn_1_2680;
                        player->unk020 = 0;
                        GWMgCoinBonusSet(player->unk028, 10);
                        CharModelVoicePanSet(player->unk02A, 64);
                        player = work->unk010[i][1];
                        player->unk01C = fn_1_2680;
                        player->unk020 = 0;
                        GWMgCoinBonusSet(player->unk028, 10);
                        CharModelVoicePanSet(player->unk02A, 64);
                    } else {
                        player = work->unk010[i][0];
                        player->unk01C = fn_1_25FC;
                        player->unk020 = 0;
                        player = work->unk010[i][1];
                        player->unk01C = fn_1_25FC;
                        player->unk020 = 0;
                    }
                }
            }
            work->unk4CAC++;
            break;
        case 1:
            break;
    }
    if (work->unk3D8 && work->unk3D8(work->unk03C[work->unk4CB0].unk054) != 0) {
        work->unk3D8 = NULL;
    }
    if (work->unk3CC && work->unk3CC(&work->unk020) != 0) {
        work->unk3CC = NULL;
    }
}

/* 1 insns */
void fn_1_1118(s16 mode, s16 frameNo) { }

/* 8 insns */
void fn_1_111C(s16 mode, s16 frameNo)
{
    M528_WORK *work = lbl_1_bss_298->data;
}

/* 139 insns */
void fn_1_113C(OMOBJ *obj)
{
    M528_PLAYER *player;
    s32 i;
    M528_WORK *work;

    player = obj->data;
    work = lbl_1_bss_298->data;
    player->unk028 = obj->work[0];
    player->unk02A = GwPlayerConf[player->unk028].charNo;
    player->unk02C = GwPlayerConf[player->unk028].grp;
    player->unk02E = GwPlayerConf[player->unk028].padNo;
    player->unk034 = GwPlayerConf[player->unk028].type;
    player->unk036 = GwPlayerConf[player->unk028].dif;
    player->unk018 = obj;
    work->unk000[player->unk028] = player;
    i = work->unk010[player->unk02C][0] != NULL;
    work->unk010[player->unk02C][i] = player;
    player->unk058 = &work->unk03C[player->unk02C].unk000[i];
    obj->mdlId[0] = CharModelCreate(player->unk02A, 2);
    for (i = 0; i < 8; i++) {
        obj->mtnId[i] = CharMotionCreate(player->unk02A, lbl_1_data_28[player->unk02A][i]);
    }
    CharMotionSet(player->unk02A, obj->mtnId[0]);
    CharModelAttrSet(player->unk02A, 0x40000001);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharEffectLayerSet(3);
    CharMotionDataClose(player->unk02A);
    player->unk01C = fn_1_1DFC;
    player->unk020 = 0;
    player->unk03E = 0;
    player->unk050[0] = 0;
    obj->objFunc = fn_1_1368;
}

/* 25 insns */
void fn_1_1368(OMOBJ *obj)
{
    M528_PLAYER *player;
    M528_WORK *work;

    player = obj->data;
    work = lbl_1_bss_298->data;
    if (player->unk01C) {
        player->unk01C(player);
    }
}

/* 1 insns */
void fn_1_13CC(void) { }

/* 34 insns */
void fn_1_13D0(OMOBJ *obj)
{
    M528_WORK *work = lbl_1_bss_298->data;

    fn_1_51A8(work);
    fn_1_1918(&work->unk020);
    fn_1_198C(&work->unk020, 0);
    fn_1_1CAC(work);
    fn_1_38F8(work);
    fn_1_4F30(work);
    fn_1_6320(work);
    obj->objFunc = fn_1_1458;
}

/* 55 insns */
void fn_1_1458(OMOBJ *obj)
{
    M528_WORK *work;
    s32 done0;
    s32 done1;

    work = lbl_1_bss_298->data;
    done0 = fn_1_2EC0(&work->unk03C[0]);
    done1 = fn_1_2EC0(&work->unk03C[1]);
    if (done0 && done1) {
        work->unk4CB0 = frandmod(2);
    } else if (done0) {
        work->unk4CB0 = 0;
    } else if (done1) {
        work->unk4CB0 = 1;
    }
    fn_1_1A20(&work->unk020);
    fn_1_3330(work);
    fn_1_B6D4(&work->unk4BE4[0]);
    fn_1_B6D4(&work->unk4BE4[1]);
    fn_1_B6D4(&work->unk4BE4[2]);
    fn_1_B6D4(&work->unk4BE4[3]);
    fn_1_50B0(work);
}

/* 1 insns */
void fn_1_1534(void) { }

/* 45 insns */
void fn_1_1538(M528_WORK *work)
{
    s32 i;

    work->unk4CB2 = 0;
    work->unk4CB0 = -1;
    fn_1_1874(work);
    fn_1_18E0(work);
    for (i = 0; i < 16; i++) {
        fn_1_36DC(&work->unk10C[i]);
    }
    work->unk010[0][0] = NULL;
    work->unk010[0][1] = NULL;
    work->unk010[1][0] = NULL;
    work->unk010[1][1] = NULL;
    work->unk3CC = NULL;
    work->unk3D0[0] = NULL;
    work->unk3D0[1] = NULL;
    work->unk3D8 = NULL;
}

/* 54 insns */
void fn_1_15EC(M528_WORK *work)
{
    HU3DLIGHTID light;

    light = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -0.5f, 255, 255, 255);
    Hu3DGLightPosAimSet(light, 0.0f, 100.0f, 100.0f, 0.0f, 0.0f, 0.0f);
    Hu3DGLightInfinitytSet(light);
}

/* 59 insns */
void fn_1_16C4(M528_WORK *work)
{
    Hu3DCameraCreate(lbl_1_rodata_10[0]);
    Hu3DCameraPerspectiveSet(lbl_1_rodata_10[0], 15.0f, 20.0f, 20000.0f, 1.2f);
    Hu3DCameraPosSet(lbl_1_rodata_10[0], 0.0f, 300.0f, 1000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 150.0f, 0.0f);
}

/* 49 insns */
void fn_1_17B0(M528_WORK *work)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF pos = { 0.0f, 4000.0f, 1000.0f };
    HuVecF target = { 0.0f, 0.0f, 0.0f };

    Hu3DShadowCreate(15.0f, 20.0f, 20000.0f);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DShadowPosSet(&pos, &up, &target);
}

/* 27 insns */
void fn_1_1874(M528_WORK *work)
{
    s32 i;

    for (i = 0; i < 54; i++) {
        work->unk4CB4[i] = -1;
    }
    for (i = 0; i < 16; i++) {
        work->unk4D2E[i] = -1;
        work->unk4D4E[i] = -1;
    }
}

/* 14 insns */
void fn_1_18E0(M528_WORK *work)
{
    s32 i;

    for (i = 0; i < 7; i++) {
        work->unk4D20[i] = -1;
    }
}

/* 29 insns */
void fn_1_1918(M528_CAMERA *camera)
{
    camera->unk00C = 0.0f;
    camera->unk010 = 0.0f;
    camera->unk014 = 1000.0f;
    camera->unk000.x = 0.0f;
    camera->unk000.y = 0.0f;
    camera->unk000.z = 0.0f;
    camera->unk018 = 0;
    camera->unk01A = 0;
}

/* 37 insns */
void fn_1_198C(M528_CAMERA *camera, s32 preset)
{
    camera->unk00C = lbl_1_data_2BC[preset].unk00C;
    camera->unk010 = lbl_1_data_2BC[preset].unk010;
    camera->unk014 = lbl_1_data_2BC[preset].unk014;
    camera->unk000.x = lbl_1_data_2BC[preset].unk000.x;
    camera->unk000.y = lbl_1_data_2BC[preset].unk000.y;
    camera->unk000.z = lbl_1_data_2BC[preset].unk000.z;
}

/* 163 insns */
void fn_1_1A20(M528_CAMERA *camera)
{
    float x;
    float y;
    float z;

    if (camera->unk00C > 360.0f) {
        camera->unk00C -= 360.0f;
    }
    if (camera->unk00C < 0.0f) {
        camera->unk00C += 360.0f;
    }
    if (camera->unk010 > 360.0f) {
        camera->unk010 -= 360.0f;
    }
    if (camera->unk010 < 0.0f) {
        camera->unk010 += 360.0f;
    }
    x = camera->unk000.x + camera->unk014 * cos(M_PI * camera->unk010 / 180.0) * cos(M_PI * camera->unk00C / 180.0);
    y = camera->unk000.y + camera->unk014 * sin(M_PI * camera->unk010 / 180.0);
    z = camera->unk000.z + camera->unk014 * cos(M_PI * camera->unk010 / 180.0) * sin(M_PI * camera->unk00C / 180.0);
    Hu3DCameraPosSet(lbl_1_rodata_10[0], x, y, z, 0.0f, 1.0f, 0.0f, camera->unk000.x, camera->unk000.y, camera->unk000.z);
}

/* 84 insns */
void fn_1_1CAC(M528_WORK *work)
{
    s16 pan[2][2] = { { 40, 56 }, { 72, 88 } };
    M528_PLAYER *player;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            player = work->unk010[i][j];
            player->unk000.x = player->unk058->unk004.x;
            player->unk000.y = 2501.0f;
            player->unk000.z = 75.0f + player->unk058->unk004.z;
            player->unk00C.x = 0.0f;
            player->unk00C.y = 0.0f;
            player->unk00C.z = 0.0f;
            omSetTra(player->unk018, player->unk000.x, player->unk000.y, player->unk000.z);
            omSetRot(player->unk018, player->unk00C.x, player->unk00C.y, player->unk00C.z);
            CharModelVoicePanSet(player->unk02A, pan[i][j]);
        }
    }
}

/* 52 insns */
s32 fn_1_1DFC(M528_PLAYER *player)
{
    float time;

    switch (player->unk020) {
        case 0:
            CharMotionSet(player->unk02A, player->unk018->mtnId[1]);
            CharModelAttrReset(player->unk02A, 0x40000001);
            CharModelAttrSet(player->unk02A, 0x40000002);
            player->unk020++;
            break;
        case 1:
            time = CharMotionMaxTimeGet(player->unk02A);
            CharMotionTimeSet(player->unk02A, time);
            CharModelAttrReset(player->unk02A, 0x40000002);
            player->unk020++;
            break;
        case 2:
            break;
    }
    return 0;
}

/* 48 insns */
s32 fn_1_1ECC(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            player->unk000.y = 1000.0f;
            player->unk044 = 0.0f;
            player->unk040 = 200.0f;
            player->unk024 = 0;
            player->unk020++;
        case 1:
            player->unk024++;
            player->unk000.y -= 2.4f * player->unk024;
            break;
    }
    return 0;
}

/* 61 insns */
s32 fn_1_1F8C(M528_PLAYER *player)
{
    s32 result;

    switch (player->unk020) {
        case 0:
            player->unk058->unk014 = 1.0f;
            player->unk03E = 1;
            player->unk03A = 0;
            player->unk020++;
        case 1:
            if (player->unk034) {
                result = fn_1_27AC(player);
            } else {
                result = fn_1_2704(player);
            }
            if (result) {
                CharMotionShiftSet(player->unk02A, player->unk018->mtnId[1], 0.0f, 3.0f, 0);
                player->unk020 = 0;
                player->unk01C = fn_1_2080;
            }
            break;
    }
    return 0;
}

/* 141 insns */
s32 fn_1_2080(M528_PLAYER *player)
{
    float jump[2] = { 25.0f, 39.0f };
    s32 result;

    switch (player->unk020) {
        case 0:
            player->unk024 = 0;
            player->unk03A = 0;
            player->unk03C = 0;
            player->unk020++;
        case 1:
            if (player->unk034) {
                player->unk03C = fn_1_2E3C(player);
            } else {
                player->unk03C = fn_1_2D7C(player);
            }
            player->unk024++;
            if (player->unk024 == 6) {
                player->unk024 = 0;
                player->unk020++;
            }
            break;
        case 2:
            player->unk03E = 0;
            player->unk058->unk014 = 0.0f;
            player->unk040 = player->unk000.y;
            player->unk044 = player->unk000.y;
            player->unk048 = 0.0f;
            player->unk020++;
        case 3:
            player->unk024++;
            player->unk000.y += jump[player->unk03C] - 2.4f * player->unk024;
            if (player->unk000.y > player->unk040) {
                player->unk040 = player->unk000.y;
            }
            if (player->unk034) {
                result = fn_1_2A00(player);
            } else {
                result = fn_1_2758(player);
            }
            if (result) {
                player->unk040 = player->unk000.y;
                CharMotionShiftSet(player->unk02A, player->unk018->mtnId[3], 0.0f, 3.0f, 0);
                player->unk020 = 0;
                player->unk01C = fn_1_237C;
            }
            break;
    }
    return 0;
}

/* 50 insns */
s32 fn_1_22B4(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            player->unk024 = 0;
            player->unk020++;
        case 1:
            player->unk024++;
            if (player->unk024 == 9) {
                CharMotionShiftSet(player->unk02A, player->unk018->mtnId[0], 0.0f, 3.0f, 0x40000001);
            }
            if (player->unk024 >= 12) {
                player->unk020 = 0;
                player->unk01C = fn_1_1F8C;
            }
            break;
    }
    return 0;
}

/* 67 insns */
s32 fn_1_237C(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            player->unk024 = 0;
            player->unk020++;
        case 1:
            player->unk024++;
            if (player->unk024 >= 3) {
                player->unk024 = 0;
                player->unk020++;
            }
            break;
        case 2:
            if (CharMotionEndCheck(player->unk02A)) {
                player->unk020++;
            }
            break;
        case 3:
            player->unk024++;
            player->unk000.y -= 6.3f * player->unk024;
            break;
    }
    return 0;
}

/* 55 insns */
s32 fn_1_2488(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            player->unk024 = 0;
            player->unk020++;
        case 1:
            player->unk024++;
            if (player->unk024 >= 3) {
                player->unk020++;
            }
            break;
        case 2:
            if (CharMotionEndCheck(player->unk02A)) {
                CharMotionSet(player->unk02A, player->unk018->mtnId[5]);
                CharMotionSpeedSet(player->unk02A, 1.5f);
                player->unk020 = 0;
                player->unk01C = fn_1_2564;
            }
            break;
    }
    return 0;
}

/* 38 insns */
s32 fn_1_2564(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            if (CharMotionEndCheck(player->unk02A)) {
                CharMotionSet(player->unk02A, player->unk018->mtnId[0]);
                CharMotionSpeedSet(player->unk02A, 1.0f);
                CharModelAttrSet(player->unk02A, 0x40000001);
                player->unk020 = 0;
                player->unk01C = fn_1_1F8C;
            }
            break;
    }
    return 0;
}

/* 33 insns */
s32 fn_1_25FC(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            CharMotionShiftSet(player->unk02A, player->unk018->mtnId[7], 0.0f, 3.0f, 0);
            player->unk020++;
            break;
        case 1:
            break;
    }
    return 0;
}

/* 33 insns */
s32 fn_1_2680(M528_PLAYER *player)
{
    switch (player->unk020) {
        case 0:
            CharMotionShiftSet(player->unk02A, player->unk018->mtnId[6], 0.0f, 3.0f, 0);
            player->unk020++;
            break;
        case 1:
            break;
    }
    return 0;
}

/* 21 insns */
s32 fn_1_2704(M528_PLAYER *player)
{
    M528_WORK *work = lbl_1_bss_298->data;

    if (work->unk4CB2 == 0) {
        return 0;
    }
    return HuPadBtnDown[player->unk02E] & PAD_BUTTON_A;
}

/* 21 insns */
s32 fn_1_2758(M528_PLAYER *player)
{
    M528_WORK *work = lbl_1_bss_298->data;

    if (work->unk4CB2 == 0) {
        return 0;
    }
    return HuPadBtnDown[player->unk02E] & (PAD_BUTTON_A | PAD_TRIGGER_L);
}

/* 149 insns */
s32 fn_1_27AC(M528_PLAYER *player)
{
    int result = 0;
    int tbl1[2][4] = { { 50, 80, 95, 99 }, { 25, 15, 10, 5 } };
    int tbl2[2][4] = { { 10, 5, 0, 0 }, { 10, 5, 0, 0 } };
    M528_WORK *work;
    int flag;
    s16 *com;

    work = lbl_1_bss_298->data;
    if (!work->unk4CB2) {
        return 0;
    }
    com = player->unk050;
    switch (com[0]) {
        case 0:
            flag = player->unk04C->unk01C == fn_1_1F8C || player->unk04C->unk01C == fn_1_22B4 || player->unk04C->unk01C == fn_1_2488;
            if ((s32)frandmod(100) < tbl1[flag][player->unk036]) {
                com[1] = 0;
                if (flag) {
                    com[2] = frandmod(18) + 9;
                }
                else {
                    com[2] = frandmod(8) + 4;
                }
                com[0]++;
            }
            else {
                com[1] = (s32)frandmod(100) >= tbl2[flag][player->unk036];
                result = 1;
            }
            break;
        case 1:
            com[1]++;
            if (com[1] > com[2]) {
                com[1] = 0;
                com[0] = 0;
            }
            break;
    }
    return result;
}

/* 144 insns */
s32 fn_1_2A00(M528_PLAYER *player)
{
    int result = 0;
    int tbl1[2][4] = { { 30, 60, 55, 50 }, { 30, 60, 55, 50 } };
    int tbl2[2][4] = { { 80, 85, 90, 95 }, { 80, 85, 90, 95 } };
    M528_WORK *work;
    int flag;
    s16 *com;

    work = lbl_1_bss_298->data;
    if (!work->unk4CB2) {
        return 0;
    }
    com = player->unk050;
    switch (com[0]) {
        case 0:
            flag = player->unk04C->unk01C == fn_1_1F8C || player->unk04C->unk01C == fn_1_22B4 || player->unk04C->unk01C == fn_1_2488;
            if (player->unk03C) {
                if ((s32)frandmod(100) < tbl2[flag][player->unk036]) {
                    com[2] = fn_1_2C40(player->unk03C, player->unk036);
                }
                else {
                    com[2] = 0;
                }
            }
            else {
                if ((s32)frandmod(100) < tbl1[flag][player->unk036]) {
                    com[2] = fn_1_2C40(player->unk03C, player->unk036);
                }
                else {
                    com[2] = 0;
                }
            }
            com[0]++;
        case 1:
            com[1]++;
            if (com[1] == com[2]) {
                com[1] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 79 insns */
s16 fn_1_2C40(s16 a0, s32 a1)
{
    s16 result = 0;

    if (a1) {
        switch (a0) {
            case 0:
                result = frandmod(9) + 13;
                break;
            case 1:
                result = frandmod(8) + 11;
                break;
            case 2:
                result = frandmod(7) + 9;
                break;
            case 3:
                result = frandmod(6) + 7;
                break;
        }
    }
    else {
        switch (a0) {
            case 0:
                result = frandmod(5) + 5;
                break;
            case 1:
                result = frandmod(4) + 7;
                break;
            case 2:
                result = frandmod(3) + 9;
                break;
            case 3:
                result = frandmod(2) + 11;
                break;
        }
    }
    return result;
}

/* 48 insns */
s16 fn_1_2D7C(M528_PLAYER *player)
{
    M528_WORK *work = lbl_1_bss_298->data;

    if (!work->unk4CB2) {
        return 0;
    }
    if (HuPadBtnDown[player->unk02E] & PAD_BUTTON_A) {
        player->unk03A = 0;
    }
    else if (HuPadBtn[player->unk02E] & PAD_BUTTON_A) {
        player->unk03A++;
    }
    return player->unk03A > (s16)5;
}

/* 33 insns */
s16 fn_1_2E3C(M528_PLAYER *player)
{
    M528_WORK *work = lbl_1_bss_298->data;
    s16 *com;

    if (!work->unk4CB2) {
        return 0;
    }
    com = player->unk050;
    if (com[1]) {
        player->unk03A++;
    }
    return player->unk03A > (s16)5;
}

/* 260 insns */
s32 fn_1_2EC0(M528_TEAM *boat)
{
    int result;
    M528_WORK *work;
    M528_SLOT *oarA;
    M528_SLOT *oarB;
    float speed;
    float dx;
    float dy;
    float d14;
    float tilt;
    float d10;

    result = 0;
    work = lbl_1_bss_298->data;
    oarA = &boat->unk000[0];
    oarB = &boat->unk000[1];
    d10 = oarA->unk010 - oarB->unk010;
    d14 = oarA->unk014 - oarB->unk014;
    if (0.0f == d14) {
        tilt = 5.0f * (-boat->unk058 / 25.0f);
    }
    else {
        tilt = 0.0f;
    }
    fn_1_32D0(oarA);
    fn_1_32D0(oarB);
    boat->unk058 += tilt + (6.4f * d10 + 0.5f * d14);
    if (oarA->unk018 - oarB->unk018 == 0) {
        speed = 0.0f;
    }
    else {
        speed = fabsf(oarA->unk010 - oarB->unk010);
        if (speed > 1.0f) {
            speed = 1.0f;
        }
        if (oarA->unk01C || oarB->unk01C) {
            HuAudFXPlay(boat->unk066);
        }
    }
    oarA->unk01C = 0;
    oarB->unk01C = 0;
    if (boat->unk058 > 25.0f) {
        speed = 0.0f;
        boat->unk058 = 25.0f;
    }
    if (boat->unk058 < -25.0f) {
        speed = 0.0f;
        boat->unk058 = -25.0f;
    }
    if (work->unk4CB2) {
        result = fn_1_3750(boat->unk054, speed);
    }
    boat->unk040 += 6.0f * speed;
    if (boat->unk040 > 360.0f) {
        boat->unk040 -= 360.0f;
    }
    dx = 150.0 * HuCos(boat->unk058);
    dy = 150.0 * HuSin(boat->unk058);
    Hu3DModelRotSet(boat->unk060, 0.0f, 0.0f, boat->unk058);
    oarA->unk004.x = boat->unk048.x - dx;
    oarA->unk004.y = boat->unk048.y - dy;
    oarB->unk004.x = boat->unk048.x + dx;
    oarB->unk004.y = boat->unk048.y + dy;
    Hu3DModelPosSet(oarA->unk01A, oarA->unk004.x, oarA->unk004.y, oarA->unk004.z);
    Hu3DModelPosSet(oarB->unk01A, oarB->unk004.x, oarB->unk004.y, oarB->unk004.z);
    Hu3DModelRotSet(boat->unk044, 0.0f, 0.0f, boat->unk040);
    return result;
}

/* 24 insns */
void fn_1_32D0(M528_SLOT *oar)
{
    if (oar->unk018) {
        oar->unk018--;
    }
    else {
        oar->unk010 *= 0.95f;
        if (oar->unk010 < 0.01f) {
            oar->unk010 = 0.0f;
        }
    }
}

/* 235 insns */
void fn_1_3330(M528_WORK *work)
{
    float dir[2] = { 1.0f, -1.0f };
    int i;
    int j;
    M528_PLAYER *player;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            player = work->unk010[i][j];
            if (player->unk03E) {
                player->unk000.x = player->unk058->unk004.x;
                player->unk000.y = player->unk058->unk004.y;
            }
            else if (player->unk000.y <= player->unk058->unk004.y) {
                player->unk048 = (player->unk040 - player->unk044) / 500.0f;
                player->unk000.y = player->unk058->unk004.y;
                if (player->unk01C == fn_1_2080) {
                    CharMotionSet(player->unk02A, player->unk018->mtnId[2]);
                    player->unk020 = 0;
                    player->unk03E = 1;
                    player->unk058->unk014 = 1.0f;
                    player->unk058->unk018 = player->unk03C ? 6 : 3;
                    player->unk058->unk010 = player->unk048 > 1.0f ? 1.0f : player->unk048;
                    player->unk01C = fn_1_22B4;
                    player->unk058->unk01C = 1;
                }
                else if (player->unk01C == fn_1_237C) {
                    omVibrate(player->unk028, 12, 6, 6);
                    CharMotionShiftSet(player->unk02A, player->unk018->mtnId[4], 0.0f, 3.0f, HU3D_MOTATTR_NONE);
                    CharMotionSpeedSet(player->unk02A, 1.5f);
                    player->unk020 = 0;
                    player->unk048 *= 2.0f;
                    player->unk03E = 1;
                    player->unk058->unk014 = 1.0f;
                    player->unk058->unk018 = player->unk03C ? 9 : 6;
                    player->unk058->unk010 = player->unk048 > 1.0f ? 1.0f : player->unk048;
                    player->unk01C = fn_1_2488;
                    player->unk058->unk01C = 1;
                }
                else if (player->unk01C == fn_1_1ECC) {
                    omVibrate(player->unk028, 12, 6, 6);
                    CharMotionSet(player->unk02A, player->unk018->mtnId[2]);
                    player->unk020 = 0;
                    player->unk03E = 1;
                    player->unk058->unk014 = 1.0f;
                    player->unk058->unk018 = 6;
                    player->unk058->unk010 = player->unk048;
                    player->unk01C = fn_1_22B4;
                    player->unk058->unk01C = 1;
                }
            }
            omSetTra(player->unk018, player->unk000.x, player->unk000.y, player->unk000.z);
            Hu3DModelPosSet(player->unk018->mdlId[0], player->unk000.x, player->unk000.y, player->unk000.z);
        }
    }
}

/* 29 insns */
void fn_1_36DC(M528_ITEM *item)
{
    item->unk000.x = 0.0f;
    item->unk000.y = 0.0f;
    item->unk000.z = 0.0f;
    item->unk018 = 0.0f;
    item->unk01C = 0.0f;
    item->unk026 = 0;
    item->unk020 = -1;
    item->unk022 = -1;
    item->unk024 = -1;
}

/* 106 insns */
s32 fn_1_3750(M528_ITEM *item, float speed)
{
    int result;
    M528_WORK *work;
    float rot;

    result = 0;
    work = lbl_1_bss_298->data;
    item->unk018 += 1.8f * speed / 360.0f;
    if (item->unk018 >= 1.0f) {
        item->unk018 = 1.0f;
        result = 1;
    }
    rot = work->unk4C98 + (item->unk01C - 360.0f * item->unk018);
    Hu3DModelRotSet(item->unk020, 0.0f, rot, 0.0f);
    Hu3DModelRotSet(item->unk022, 0.0f, rot, 0.0f);
    Hu3DModelRotSet(item->unk024, 0.0f, rot, 0.0f);
    Hu3DMotionShapeTimeSet(item->unk022, 1198.0f * item->unk018);
    Hu3DMotionShapeTimeSet(item->unk024, 1198.0f * item->unk018);
    Hu3DMotionTimeSet(item->unk024, 1198.0f * item->unk018);
    return result;
}

/* 66 insns */
void fn_1_38F8(M528_WORK *work)
{
    int i;

    work->unk010[0][0]->unk04C = work->unk010[0][1];
    work->unk010[0][1]->unk04C = work->unk010[0][0];
    work->unk010[1][0]->unk04C = work->unk010[1][1];
    work->unk010[1][1]->unk04C = work->unk010[1][0];
    i = frandmod(2);
    work->unk010[0][i]->unk050[1] = 0;
    work->unk010[0][i]->unk050[2] = frandmod(15) + 30;
    work->unk010[0][i]->unk050[0] = 1;
    i = frandmod(2);
    work->unk010[1][i]->unk050[1] = 0;
    work->unk010[1][i]->unk050[2] = frandmod(15) + 30;
    work->unk010[1][i]->unk050[0] = 1;
}

/* 168 insns */
void fn_1_3A00(M528_WORK *work)
{
    int i;
    M528_ITEM *item;
    HU3DMODELID model;
    float rot;

    for (i = 0; i < 16; i++) {
        item = &work->unk10C[i];
        rot = work->unk4C98 + item->unk01C;
        work->unk10C[i].unk000.x = 1480.0 * HuSin(rot);
        work->unk10C[i].unk000.y = -620.0f;
        work->unk10C[i].unk000.z = 1480.0 * HuCos(rot) - 1680.0;
        model = item->unk020;
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        model = item->unk022;
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
        model = item->unk024;
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, rot, 0.0f);
    }
    model = work->unk4CB4[4];
    Hu3DModelRotSet(model, 0.0f, work->unk4C98, 0.0f);
    model = work->unk4CB4[5];
    Hu3DModelRotSet(model, 0.0f, work->unk4C98, 0.0f);
    model = work->unk4CB4[7];
    Hu3DModelRotSet(model, 0.0f, work->unk4C98, 0.0f);
}

/* 151 insns */
s32 fn_1_3CA0(M528_CAMERA *camera)
{
    int result;
    float t;
    float s;
    float u;

    result = 0;
    switch (camera->unk018) {
        case 0:
            camera->unk01A = 0;
            camera->unk018++;
        case 1:
            camera->unk01A++;
            if (camera->unk01A >= 100) {
                camera->unk018 = 0;
                result = 1;
            }
            t = camera->unk01A / 100.0f;
            s = 1.0 - (0.5 + 0.5 * HuCos(180.0f * t));
            u = 1.0f - s;
            camera->unk00C = lbl_1_data_2BC[0].unk00C * u + lbl_1_data_2BC[1].unk00C * s;
            camera->unk010 = lbl_1_data_2BC[0].unk010 * u + lbl_1_data_2BC[1].unk010 * s;
            camera->unk014 = lbl_1_data_2BC[0].unk014 * u + lbl_1_data_2BC[1].unk014 * s;
            camera->unk000.x = lbl_1_data_2BC[0].unk000.x * u + lbl_1_data_2BC[1].unk000.x * s;
            camera->unk000.y = lbl_1_data_2BC[0].unk000.y * u + lbl_1_data_2BC[1].unk000.y * s;
            camera->unk000.z = lbl_1_data_2BC[0].unk000.z * u + lbl_1_data_2BC[1].unk000.z * s;
            break;
    }
    return result;
}

/* 151 insns */
s32 fn_1_3EFC(M528_CAMERA *camera)
{
    int result;
    float t;
    float s;
    float u;

    result = 0;
    switch (camera->unk018) {
        case 0:
            camera->unk01A = 0;
            camera->unk018++;
        case 1:
            camera->unk01A++;
            if (camera->unk01A >= 90) {
                camera->unk018 = 0;
                result = 1;
            }
            t = camera->unk01A / 90.0f;
            s = 1.0 - (0.5 + 0.5 * HuCos(180.0f * t));
            u = 1.0f - s;
            camera->unk00C = lbl_1_data_2BC[1].unk00C * u + lbl_1_data_2BC[2].unk00C * s;
            camera->unk010 = lbl_1_data_2BC[1].unk010 * u + lbl_1_data_2BC[2].unk010 * s;
            camera->unk014 = lbl_1_data_2BC[1].unk014 * u + lbl_1_data_2BC[2].unk014 * s;
            camera->unk000.x = lbl_1_data_2BC[1].unk000.x * u + lbl_1_data_2BC[2].unk000.x * s;
            camera->unk000.y = lbl_1_data_2BC[1].unk000.y * u + lbl_1_data_2BC[2].unk000.y * s;
            camera->unk000.z = lbl_1_data_2BC[1].unk000.z * u + lbl_1_data_2BC[2].unk000.z * s;
            break;
    }
    return result;
}

/* 151 insns */
s32 fn_1_4158(M528_CAMERA *camera)
{
    int result;
    float t;
    float s;
    float u;

    result = 0;
    switch (camera->unk018) {
        case 0:
            camera->unk01A = 0;
            camera->unk018++;
        case 1:
            camera->unk01A++;
            if (camera->unk01A >= 90) {
                camera->unk018 = 0;
                result = 1;
            }
            t = camera->unk01A / 90.0f;
            s = 1.0 - (0.5 + 0.5 * HuCos(180.0f * t));
            u = 1.0f - s;
            camera->unk00C = lbl_1_data_2BC[1].unk00C * u + lbl_1_data_2BC[3].unk00C * s;
            camera->unk010 = lbl_1_data_2BC[1].unk010 * u + lbl_1_data_2BC[3].unk010 * s;
            camera->unk014 = lbl_1_data_2BC[1].unk014 * u + lbl_1_data_2BC[3].unk014 * s;
            camera->unk000.x = lbl_1_data_2BC[1].unk000.x * u + lbl_1_data_2BC[3].unk000.x * s;
            camera->unk000.y = lbl_1_data_2BC[1].unk000.y * u + lbl_1_data_2BC[3].unk000.y * s;
            camera->unk000.z = lbl_1_data_2BC[1].unk000.z * u + lbl_1_data_2BC[3].unk000.z * s;
            break;
    }
    return result;
}

/* 99 insns */
s32 fn_1_43B4(M528_CAMERA *camera)
{
    int result;
    float t;
    int ang;

    result = 0;
    switch (camera->unk018) {
        case 0:
            camera->unk01A = 0;
            camera->unk018++;
        case 1:
            camera->unk01A++;
            if (camera->unk01A >= 30) {
                camera->unk018 = 0;
                result = 1;
            }
            t = camera->unk01A / 30.0f;
            ang = (camera->unk01A * 36) % 360;
            camera->unk000.y = lbl_1_data_2BC[1].unk000.y + 15.0f * (1.0f - t) * HuSin(ang);
            break;
    }
    return result;
}

/* 99 insns */
s32 fn_1_4540(M528_CAMERA *camera)
{
    int result;
    float t;
    int ang;

    result = 0;
    switch (camera->unk018) {
        case 0:
            camera->unk01A = 0;
            camera->unk018++;
        case 1:
            camera->unk01A++;
            if (camera->unk01A >= 30) {
                camera->unk018 = 0;
                result = 1;
            }
            t = camera->unk01A / 30.0f;
            ang = (camera->unk01A * 36) % 360;
            camera->unk000.y = lbl_1_data_2BC[1].unk000.y + 30.0f * (1.0f - t) * HuSin(ang);
            break;
    }
    return result;
}

/* 73 insns */
void fn_1_46CC(M528_WORK *work)
{
    int i;
    int near[2];
    HU3DMODELID model;

    for (i = 0; i < 2; i++) {
        work->unk03C[i].unk054 = &work->unk10C[work->unk4CA8[i]];
    }
    near[0] = (work->unk4CA8[0] + 15) % 16;
    near[1] = (work->unk4CA8[1] + 1) % 16;
    for (i = 0; i < 16; i++) {
        if (i != work->unk4CA8[0] && i != work->unk4CA8[1] && i != near[0] && i != near[1]) {
            model = work->unk10C[i].unk022;
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
            model = work->unk10C[i].unk024;
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        }
    }
}

/* 91 insns */
s32 fn_1_47F0(M528_TEAM *boat)
{
    int result;
    HU3DMODELID model;

    result = 0;
    switch (boat->unk062) {
        case 0:
            boat->unk048.y = 1000.0f;
            boat->unk064 = 0;
            boat->unk062++;
        case 1:
            boat->unk064++;
            boat->unk048.y -= 2.4f * boat->unk064;
            if (boat->unk048.y < 0.0f) {
                boat->unk048.y = 0.0f;
                result = 1;
            }
            boat->unk000[0].unk004.y = boat->unk048.y;
            boat->unk000[1].unk004.y = boat->unk048.y;
            model = boat->unk060;
            Hu3DModelPosSet(model, boat->unk048.x, boat->unk048.y, boat->unk048.z);
            model = boat->unk000[0].unk01A;
            Hu3DModelPosSet(model, boat->unk000[0].unk004.x, boat->unk000[0].unk004.y, boat->unk000[0].unk004.z);
            model = boat->unk000[1].unk01A;
            Hu3DModelPosSet(model, boat->unk000[1].unk004.x, boat->unk000[1].unk004.y, boat->unk000[1].unk004.z);
            model = boat->unk044;
            Hu3DModelPosSet(model, boat->unk048.x, boat->unk048.y, boat->unk048.z);
            break;
    }
    return result;
}

/* 106 insns */
s32 fn_1_495C(M528_TEAM *boat)
{
    int result = 0;
    s16 pan[2] = { 48, 80 };
    M528_WORK *work;
    HU3DMODELID model;

    work = lbl_1_bss_298->data;
    switch (boat->unk062) {
        case 0:
            HuAudFXPlayPan(0x78F, pan[work->unk4CB0 ^ 1]);
            boat->unk064 = 0;
            boat->unk062++;
        case 1:
            boat->unk064++;
            boat->unk048.y += 20.0f - 2.4f * boat->unk064;
            if (boat->unk048.y < -1000.0f) {
                result = 1;
            }
            boat->unk000[0].unk004.y = boat->unk048.y;
            boat->unk000[1].unk004.y = boat->unk048.y;
            model = boat->unk060;
            Hu3DModelPosSet(model, boat->unk048.x, boat->unk048.y, boat->unk048.z);
            model = boat->unk000[0].unk01A;
            Hu3DModelPosSet(model, boat->unk000[0].unk004.x, boat->unk000[0].unk004.y, boat->unk000[0].unk004.z);
            model = boat->unk000[1].unk01A;
            Hu3DModelPosSet(model, boat->unk000[1].unk004.x, boat->unk000[1].unk004.y, boat->unk000[1].unk004.z);
            model = boat->unk044;
            Hu3DModelPosSet(model, boat->unk048.x, boat->unk048.y, boat->unk048.z);
            break;
    }
    return result;
}

/* 96 insns */
s32 fn_1_4B04(M528_ITEM *item)
{
    int result = 0;
    float ofs[2] = { -7.0f, 7.0f };
    M528_WORK *work;
    HU3DMODELID model;

    work = lbl_1_bss_298->data;
    switch (item->unk026) {
        case 0:
            item->unk00C = item->unk000;
            item->unk028 = 0;
            item->unk026++;
            HuAudFXPlay(0x78B);
        case 1:
            item->unk028++;
            if (item->unk028 >= 120) {
                result = 1;
            }
            item->unk00C.y += 100.0 - 2.4 * item->unk028;
            item->unk00C.x += ofs[work->unk4CB0];
            item->unk000.z += 1.0f;
            model = item->unk022;
            Hu3DModelPosSet(model, item->unk00C.x, item->unk00C.y, item->unk00C.z);
            break;
    }
    return result;
}

/* 127 insns */
s32 fn_1_4C84(M528_ITEM *item)
{
    int result;
    M528_WORK *work;
    HU3DMODELID model;

    result = 0;
    work = lbl_1_bss_298->data;
    switch (item->unk026) {
        case 0:
            item->unk028 = 0;
            item->unk026++;
        case 1:
            item->unk028++;
            if (item->unk028 == 3) {
                (s32)item->unk028; /* retail: a discarded read of the timer (a lost "= 0"?) */
                item->unk026++;
            }
            break;
        case 2:
            item->unk000.y -= 5.0f;
            item->unk028++;
            if (item->unk028 == 18) {
                item->unk00C = item->unk000;
                item->unk028 = 0;
                item->unk026++;
            }
            model = item->unk022;
            Hu3DModelPosSet(model, item->unk000.x, item->unk000.y, item->unk000.z);
            break;
        case 3:
            item->unk028++;
            if (item->unk028 >= 5) {
                item->unk028 = 0;
            }
            item->unk00C.y += 2.0 * HuSin(360.0f * item->unk028 / 5.0f);
            model = item->unk022;
            Hu3DModelPosSet(model, item->unk00C.x, item->unk00C.y, item->unk00C.z);
            break;
    }
    return result;
}

/* 44 insns */
void fn_1_4E80(M528_WORK *work)
{
    int idx;
    HU3DMODELID model;

    if (work->unk4CB0) {
        idx = (work->unk4CA8[1] + 5) % 16;
    }
    else {
        idx = (work->unk4CA8[0] + 11) % 16;
    }
    model = work->unk10C[idx].unk022;
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    model = work->unk10C[idx].unk024;
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
}

/* 49 insns */
void fn_1_4F30(M528_WORK *work)
{
    int i;

    for (i = 0; i < 255; i++) {
        work->unk3E4[i].unk000 = NULL;
        work->unk3E4[i].unk004 = &work->unk3E4[i + 1];
        work->unk3E4[i].unk008 = NULL;
        work->unk3E4[i].unk00C = NULL;
    }
    work->unk3E4[i].unk000 = NULL;
    work->unk3E4[i].unk004 = NULL;
    work->unk3E4[i].unk008 = NULL;
    work->unk3E4[i].unk00C = NULL;
    work->unk3DC = NULL;
    work->unk3E0 = &work->unk3E4[0];
}

/* 21 insns */
M528_NODE *fn_1_4FF4(M528_WORK *work, M528_NODEFUNC func, void *arg)
{
    M528_NODE *node;

    node = work->unk3E0;
    if (node) {
        work->unk3E0 = node->unk004;
        node->unk008 = func;
        node->unk00C = arg;
        node->unk004 = work->unk3DC;
        if (node->unk004) {
            node->unk004->unk000 = node;
        }
        work->unk3DC = node;
    }
    return node;
}

/* 26 insns */
void fn_1_5048(M528_WORK *work, M528_NODE *node)
{
    if (node) {
        if (node->unk000) {
            node->unk000->unk004 = node->unk004;
        }
        else {
            work->unk3DC = node->unk004;
        }
        if (node->unk004) {
            node->unk004->unk000 = node->unk000;
        }
        node->unk000 = NULL;
        node->unk004 = work->unk3E0;
        node->unk008 = NULL;
        work->unk3E0 = node;
        node = NULL;
    }
}

/* 57 insns */
void fn_1_50B0(M528_WORK *work)
{
    M528_NODE *node;
    M528_NODE *next;

    node = work->unk3DC;
    while (node) {
        next = node->unk004;
        if (node->unk008 && node->unk008(node)) {
            fn_1_5048(work, node);
        }
        node = next;
    }
}
/* 5 insns */
void fn_1_5194(M528_EFFECT *a0)
{
    a0->unk030 = 0;
    a0->unk036 = -1;
}

/* 660 insns */
void fn_1_51A8(M528_WORK *work)
{
    HU3DMODELID model;
    s32 i;
    s32 j;

    if (work->unk4CB4[4] < 0) {
        model = work->unk4CB4[4] = Hu3DModelCreateData(lbl_1_data_1C8[4]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[4]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if (work->unk4CB4[8] < 0) {
        model = work->unk4CB4[8] = Hu3DModelCreateData(lbl_1_data_1C8[8]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[8]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if (work->unk4CB4[5] < 0) {
        model = work->unk4CB4[5] = Hu3DModelCreateData(lbl_1_data_1C8[5]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[5]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if (work->unk4CB4[6] < 0) {
        model = work->unk4CB4[6] = Hu3DModelCreateData(lbl_1_data_1C8[6]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[6]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    if (work->unk4CB4[7] < 0) {
        model = work->unk4CB4[7] = Hu3DModelCreateData(lbl_1_data_1C8[7]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[7]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelPosSet(model, 0.0f, -600.0f, -1680.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    Hu3DReflectMapSet(HuDataSelHeapReadNum(0x56003D, HU_MEMNUM_OVL, HEAP_MODEL));
    fn_1_5BF8(work);
    for (i = 0; i < 2; i++) {
        if (work->unk4CB4[0] < 0) {
            model = work->unk4CB4[0] = Hu3DModelCreateData(lbl_1_data_1C8[0]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[0]);
        }
        work->unk03C[i].unk060 = model;
        work->unk03C[i].unk058 = 0.0f;
        work->unk03C[i].unk05C = 0.0f;
        work->unk03C[i].unk048.x = 600.0f * i - 300.0f;
        work->unk03C[i].unk048.y = 2500.0f;
        work->unk03C[i].unk048.z = 0.0f;
        work->unk03C[i].unk062 = 0;
        if (i == 0) {
            work->unk03C[i].unk066 = 0x789;
        }
        else {
            work->unk03C[i].unk066 = 0x78A;
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, work->unk03C[i].unk048.x, work->unk03C[i].unk048.y, work->unk03C[i].unk048.z);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            if (work->unk4CB4[i + 1] < 0) {
                model = work->unk4CB4[i + 1] = Hu3DModelCreateData(lbl_1_data_1C8[i + 1]);
            }
            else {
                model = Hu3DModelLink(work->unk4CB4[i + 1]);
            }
            work->unk03C[i].unk000[j].unk01A = model;
            work->unk03C[i].unk000[j].unk004.x = work->unk03C[i].unk048.x + 300.0f * j - 150.0f;
            work->unk03C[i].unk000[j].unk004.y = work->unk03C[i].unk048.y;
            work->unk03C[i].unk000[j].unk004.z = work->unk03C[i].unk048.z;
            work->unk03C[i].unk000[j].unk014 = 0.0f;
            work->unk03C[i].unk000[j].unk010 = 0.0f;
            work->unk03C[i].unk000[j].unk000 = &work->unk03C[i];
            work->unk03C[i].unk000[j].unk01C = 0;
            Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(model, 2);
            Hu3DModelPosSet(model, work->unk03C[i].unk000[j].unk004.x, work->unk03C[i].unk000[j].unk004.y, work->unk03C[i].unk000[j].unk004.z);
            Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowMapSet(model);
        }
    }
    for (i = 0; i < 2; i++) {
        if (work->unk4CB4[3] < 0) {
            model = work->unk4CB4[3] = Hu3DModelCreateData(lbl_1_data_1C8[3]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[3]);
        }
        work->unk03C[i].unk044 = model;
        work->unk03C[i].unk040 = 0.0f;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, work->unk03C[i].unk048.x, work->unk03C[i].unk048.y, work->unk03C[i].unk048.z);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    }
    fn_1_6410(work);
    fn_1_654C(work);
    fn_1_6688(work);
    fn_1_67C4(work);
    fn_1_6900(work);
    fn_1_6A3C(work);
    fn_1_6B78(work);
    fn_1_6CB4(work);
    fn_1_B528(&work->unk4BE4[0], 0);
    fn_1_B528(&work->unk4BE4[1], 150);
    fn_1_B528(&work->unk4BE4[2], 330);
    fn_1_B528(&work->unk4BE4[3], 900);
}

/* 458 insns */
void fn_1_5BF8(M528_WORK *work)
{
    s32 weight[8] = { 20, 20, 15, 15, 10, 10, 7, 3 };
    s32 rand;
    s32 sum;
    s32 k;
    HU3DMOTID mot;
    s32 i;
    HU3DMODELID model;
    float ang;

    for (i = 0; i < 16; i++) {
        rand = frandmod(100);
        sum = 0;
        for (k = 0; k < 8; k++) {
            if (rand < sum + weight[k]) {
                break;
            }
            sum += weight[k];
        }
        if (work->unk4CB4[k + 13] < 0) {
            model = work->unk4CB4[k + 13] = Hu3DModelCreateData(lbl_1_data_1C8[k + 13]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[k + 13]);
        }
        work->unk10C[i].unk020 = model;
        ang = 22.5f * i - 11.25f;
        work->unk10C[i].unk000.x = 1480.0 * sin(M_PI * ang / 180.0);
        work->unk10C[i].unk000.y = -620.0f;
        work->unk10C[i].unk000.z = 1480.0 * cos(M_PI * ang / 180.0) - 1680.0;
        work->unk10C[i].unk01C = ang;
        work->unk10C[i].unk02A = k;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 1);
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, work->unk10C[i].unk01C, 0.0f);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
        if (k == 7) {
            if (work->unk4D2E[i] < 0) {
                model = work->unk4D2E[i] = Hu3DModelCreateData(lbl_1_data_1C8[11]);
            }
            else {
                model = Hu3DModelLink(work->unk4D2E[i]);
            }
            if (work->unk4D20[2] < 0) {
                mot = work->unk4D20[2] = Hu3DJointMotionData(model, lbl_1_data_2A0[2]);
            }
            else {
                mot = work->unk4D20[2];
            }
            Hu3DMotionSet(model, mot);
        }
        else {
            if (work->unk4D2E[i] < 0) {
                model = work->unk4D2E[i] = Hu3DModelCreateData(lbl_1_data_1C8[9]);
            }
            else {
                model = Hu3DModelLink(work->unk4D2E[i]);
            }
            if (work->unk4D20[0] < 0) {
                mot = work->unk4D20[0] = Hu3DJointMotionData(model, lbl_1_data_2A0[0]);
            }
            else {
                mot = work->unk4D20[0];
            }
            Hu3DMotionSet(model, mot);
        }
        work->unk10C[i].unk022 = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelLayerSet(model, 1);
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, work->unk10C[i].unk01C, 0.0f);
        Hu3DMotionSet(model, mot);
        Hu3DMotionShapeSet(model, mot);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
        if (k == 7) {
            if (work->unk4D4E[i] < 0) {
                model = work->unk4D4E[i] = Hu3DModelCreateData(lbl_1_data_1C8[12]);
            }
            else {
                model = Hu3DModelLink(work->unk4D4E[i]);
            }
            if (work->unk4D20[3] < 0) {
                mot = work->unk4D20[3] = Hu3DJointMotionData(model, lbl_1_data_2A0[3]);
            }
            else {
                mot = work->unk4D20[3];
            }
            Hu3DMotionSet(model, mot);
        }
        else {
            if (work->unk4D4E[i] < 0) {
                model = work->unk4D4E[i] = Hu3DModelCreateData(lbl_1_data_1C8[10]);
            }
            else {
                model = Hu3DModelLink(work->unk4D4E[i]);
            }
            if (work->unk4D20[1] < 0) {
                mot = work->unk4D20[1] = Hu3DJointMotionData(model, lbl_1_data_2A0[1]);
            }
            else {
                mot = work->unk4D20[1];
            }
            Hu3DMotionSet(model, mot);
        }
        work->unk10C[i].unk024 = model;
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelLayerSet(model, 1);
        Hu3DModelPosSet(model, work->unk10C[i].unk000.x, work->unk10C[i].unk000.y, work->unk10C[i].unk000.z);
        Hu3DModelRotSet(model, 0.0f, work->unk10C[i].unk01C, 0.0f);
        Hu3DMotionSet(model, mot);
        Hu3DMotionShapeSet(model, mot);
        Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    }
}

/* 60 insns */
void fn_1_6320(M528_WORK *work)
{
    HU3DMODELID model;

    if (work->unk4CB4[21] < 0) {
        model = work->unk4CB4[21] = Hu3DModelCreateData(lbl_1_data_1C8[21]);
    }
    else {
        model = Hu3DModelLink(work->unk4CB4[21]);
    }
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(model, 2);
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
}

/* 79 insns */
void fn_1_6410(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 8; i++) {
        if (work->unk4CB4[i + 22] < 0) {
            model = work->unk4CB4[i + 22] = Hu3DModelCreateData(lbl_1_data_1C8[i + 22]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 22]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_654C(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 6; i++) {
        if (work->unk4CB4[i + 30] < 0) {
            model = work->unk4CB4[i + 30] = Hu3DModelCreateData(lbl_1_data_1C8[i + 30]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 30]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_6688(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 5; i++) {
        if (work->unk4CB4[i + 36] < 0) {
            model = work->unk4CB4[i + 36] = Hu3DModelCreateData(lbl_1_data_1C8[i + 36]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 36]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_67C4(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 5; i++) {
        if (work->unk4CB4[i + 41] < 0) {
            model = work->unk4CB4[i + 41] = Hu3DModelCreateData(lbl_1_data_1C8[i + 41]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 41]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_6900(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 1; i++) {
        if (work->unk4CB4[i + 46] < 0) {
            model = work->unk4CB4[i + 46] = Hu3DModelCreateData(lbl_1_data_1C8[i + 46]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 46]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_6A3C(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 1; i++) {
        if (work->unk4CB4[i + 47] < 0) {
            model = work->unk4CB4[i + 47] = Hu3DModelCreateData(lbl_1_data_1C8[i + 47]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 47]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_6B78(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 4; i++) {
        if (work->unk4CB4[i + 48] < 0) {
            model = work->unk4CB4[i + 48] = Hu3DModelCreateData(lbl_1_data_1C8[i + 48]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 48]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 79 insns */
void fn_1_6CB4(M528_WORK *work)
{
    s32 i;
    HU3DMODELID model;

    for (i = 0; i < 2; i++) {
        if (work->unk4CB4[i + 52] < 0) {
            model = work->unk4CB4[i + 52] = Hu3DModelCreateData(lbl_1_data_1C8[i + 52]);
        }
        else {
            model = Hu3DModelLink(work->unk4CB4[i + 52]);
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
}

/* 317 insns */
s32 fn_1_6DF0(M528_NODE *task)
{
    float ang;
    float dist;
    float vy;
    s32 ret;
    s32 no;
    HU3DMODELID model;
    s32 r;
    M528_WORK *work;
    M528_EFFECT *p;

    ret = 0;
    work = lbl_1_bss_298->data;
    p = task->unk00C;
    switch (p->unk030) {
    case 0:
        if (p->unk036 < 0) {
            no = frandmod(8);
            if (work->unk4CB4[no + 22] < 0) {
                model = work->unk4CB4[no + 22] = Hu3DModelCreateData(lbl_1_data_1C8[no + 22]);
            }
            else {
                model = Hu3DModelLink(work->unk4CB4[no + 22]);
            }
            p->unk036 = model;
        }
        else {
            model = p->unk036;
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        r = frandmod(70);
        dist = r;
        r = frandmod(85) - 42;
        ang = r;
        p->unk000.x = 600.0f * work->unk4CB0 + dist * sin(M_PI * ang / 180.0) - 300.0;
        p->unk000.y = -300.0f;
        p->unk000.z = dist * cos(M_PI * ang / 180.0) - 220.0;
        p->unk00C.x = 0.0f;
        if (no < 5) {
            p->unk00C.y = (s32)frandmod(180);
            p->unk00C.z = (s32)frandmod(31) - 15.0f;
        }
        else {
            p->unk00C.y = 0.0f;
            p->unk00C.z = 0.0f;
        }
        r = frandmod(3) + 6;
        dist = r;
        r = frandmod(40) + 40;
        vy = r;
        p->unk018.x = dist * sin(M_PI * ang / 180.0);
        p->unk018.y = vy;
        p->unk018.z = 0.1f + dist * cos(M_PI * ang / 180.0);
        p->unk032 = 0;
        p->unk034 = frandmod(30) + 1;
        Hu3DModelPosSetV(p->unk036, &p->unk000);
        Hu3DModelRotSetV(p->unk036, &p->unk00C);
        p->unk032 = 0;
        p->unk030++;
        break;
    case 1:
        p->unk032++;
        if (p->unk032 == p->unk034) {
            Hu3DModelAttrReset(p->unk036, HU3D_ATTR_DISPOFF);
            p->unk030++;
        }
        break;
    case 2:
        p->unk018.y -= 0.9f;
        p->unk000.x += p->unk018.x;
        p->unk000.y += p->unk018.y;
        p->unk000.z += p->unk018.z;
        Hu3DModelPosSetV(p->unk036, &p->unk000);
        Hu3DModelRotSetV(p->unk036, &p->unk00C);
        break;
    }
    return ret;
}

/* 300 insns */
s32 fn_1_72E4(M528_NODE *task)
{
    float ang;
    float dist;
    float vy;
    s32 ret;
    s32 no;
    HU3DMODELID model;
    s32 r;
    M528_WORK *work;
    M528_EFFECT *p;

    ret = 0;
    work = lbl_1_bss_298->data;
    p = task->unk00C;
    switch (p->unk030) {
    case 0:
        if (p->unk036 < 0) {
            no = frandmod(5);
            if (work->unk4CB4[no + 31] < 0) {
                model = work->unk4CB4[no + 31] = Hu3DModelCreateData(lbl_1_data_1C8[no + 31]);
            }
            else {
                model = Hu3DModelLink(work->unk4CB4[no + 31]);
            }
            p->unk036 = model;
        }
        else {
            model = p->unk036;
        }
        Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(model, 2);
        r = frandmod(50);
        dist = r;
        r = frandmod(85) - 42;
        ang = r;
        p->unk000.x = 600.0f * work->unk4CB0 + dist * sin(M_PI * ang / 180.0) - 300.0;
        p->unk000.y = -300.0f;
        p->unk000.z = dist * cos(M_PI * ang / 180.0) - 210.0;
        p->unk00C.x = 0.0f;
        p->unk00C.y = (s32)frandmod(180);
        p->unk00C.z = (s32)frandmod(31) - 15.0f;
        r = frandmod(4) + 5;
        dist = r;
        r = frandmod(40) + 40;
        vy = r;
        p->unk018.x = dist * sin(M_PI * ang / 180.0);
        p->unk018.y = vy;
        p->unk018.z = dist * cos(M_PI * ang / 180.0);
        p->unk032 = 0;
        p->unk034 = frandmod(30) + 1;
        Hu3DModelPosSetV(p->unk036, &p->unk000);
        Hu3DModelRotSetV(p->unk036, &p->unk00C);
        p->unk030++;
        break;
    case 1:
        p->unk032++;
        if (p->unk032 == p->unk034) {
            Hu3DModelAttrReset(p->unk036, HU3D_ATTR_DISPOFF);
            p->unk030++;
        }
        break;
    case 2:
        p->unk018.y -= 0.9f;
        p->unk000.x += p->unk018.x;
        p->unk000.y += p->unk018.y;
        p->unk000.z += p->unk018.z;
        Hu3DModelPosSetV(p->unk036, &p->unk000);
        Hu3DModelRotSetV(p->unk036, &p->unk00C);
        break;
    }
    return ret;
}

/* 236 insns */
s32 fn_1_7794(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    s32 n;
    float speed;
    float angle;
    float vy;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[30] < 0) {
                    mdl = work->unk4CB4[30] = Hu3DModelCreateData(lbl_1_data_1C8[30]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[30]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            eff->unk000.x = 600.0f * work->unk4CB0 - 300.0f;
            eff->unk000.y = -300.0f;
            eff->unk000.z = -200.0f;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = (s32)frandmod(180);
            eff->unk00C.z = (s32)frandmod(31) - 15.0f;
            n = 10;
            speed = n;
            n = 0;
            angle = n;
            n = 70;
            vy = n;
            eff->unk018.x = speed * HuSin(angle);
            eff->unk018.y = vy;
            eff->unk018.z = speed * HuCos(angle);
            eff->unk032 = 0;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == 80) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 2.4f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 306 insns */
s32 fn_1_7B44(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    HU3DMOTID mot;
    s32 no;
    float angle;
    float scale;
    float speed;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                no = frandmod(5);
                if (work->unk4CB4[no + 41] < 0) {
                    mdl = work->unk4CB4[no + 41] = Hu3DModelCreateData(lbl_1_data_1C8[no + 41]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[no + 41]);
                }
                if (work->unk4D20[4] < 0) {
                    mot = work->unk4D20[4] = Hu3DJointMotionData(mdl, lbl_1_data_2A0[4]);
                }
                else {
                    mot = work->unk4D20[4];
                }
                Hu3DMotionSet(mdl, mot);
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            scale = 1.0f - 0.2f * ((s32)frandmod(10001) / 10000.0f);
            Hu3DModelScaleSet(mdl, scale, scale, scale);
            angle = 15.0f * eff->unk032;
            eff->unk000.x = 600.0f * work->unk4CB0 + 70.0 * HuSin(angle) - 300.0;
            eff->unk000.y = -200.0f;
            eff->unk000.z = 70.0 * HuCos(angle) - 200.0;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = 360.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk00C.z = 0.0f;
            speed = 3.0f;
            eff->unk018.x = speed * HuSin(angle);
            eff->unk018.y = 11.0f;
            eff->unk018.z = 0.0f;
            eff->unk032 = 0;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 246 insns */
s32 fn_1_800C(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    HU3DMOTID mot;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[47] < 0) {
                    mdl = work->unk4CB4[47] = Hu3DModelCreateData(lbl_1_data_1C8[47]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[47]);
                }
                if (work->unk4D20[6] < 0) {
                    mot = work->unk4D20[6] = Hu3DJointMotionData(mdl, lbl_1_data_2A0[6]);
                }
                else {
                    mot = work->unk4D20[6];
                }
                Hu3DMotionSet(mdl, mot);
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            eff->unk000.x = 600.0f * work->unk4CB0 - 300.0f;
            eff->unk000.y = -400.0f;
            eff->unk000.z = -200.0f;
            eff->unk00C.x = -10.0f;
            eff->unk00C.y = 0.0f;
            eff->unk00C.z = 0.0f;
            eff->unk018.x = 0.0f;
            eff->unk018.y = 45.0f;
            eff->unk018.z = 0.0f;
            eff->unk032 = 0;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk030++;
            break;
        case 1:
            Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
            eff->unk030++;
        case 2:
            eff->unk018.y -= 1.5f;
            if (eff->unk018.y < 0.0f) {
                eff->unk032 = 0;
                eff->unk018.y = 0.0f;
                eff->unk030++;
            }
            eff->unk000.y += eff->unk018.y;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            eff->unk032++;
            if (eff->unk032 == 5) {
                eff->unk030++;
            }
            break;
        case 4:
            eff->unk018.y -= 1.5f;
            eff->unk000.y += eff->unk018.y;
            if (eff->unk000.y < -400.0f) {
                HuAudFXPlay(704);
                work->unk3CC = fn_1_4540;
                eff->unk032 = 0;
                eff->unk030++;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 5:
            eff->unk032++;
            if (eff->unk032 == 7) {
                eff->unk032 = 0;
                eff->unk018.y = 45.0f;
                eff->unk030 = 2;
            }
            break;
    }
    return ret;
}

/* 260 insns */
s32 fn_1_83E4(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[48] < 0) {
                    mdl = work->unk4CB4[48] = Hu3DModelCreateData(lbl_1_data_1C8[48]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[48]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            eff->unk000.x = 600.0f * work->unk4CB0 - 300.0f;
            eff->unk000.y = -200.0f;
            eff->unk000.z = -200.0f;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = (work->unk4CB0) ? -20.0f : 20.0f;
            eff->unk00C.z = 0.0f;
            eff->unk018.x = (work->unk4CB0) ? 3.7f : -3.7f;
            eff->unk018.y = 55.0f;
            eff->unk018.z = 1.0f;
            eff->unk024.z = 5.0f;
            eff->unk032 = 0;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == 5) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 1.2f;
            if (eff->unk000.y > 100.0f) {
                eff->unk018.x *= 1.5f;
                eff->unk030++;
            }
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.z += eff->unk024.z;
            if (eff->unk00C.z > 360.0f) {
                eff->unk00C.x -= 360.0f; /* retail bug: wraps .x, not .z */
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            eff->unk018.y -= 1.2f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.z += eff->unk024.z;
            if (eff->unk00C.z > 360.0f) {
                eff->unk00C.z -= 360.0f;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 311 insns */
s32 fn_1_87F4(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    s32 no;
    float angle;
    float speed;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                no = frandmod(3);
                if (work->unk4CB4[no + 49] < 0) {
                    mdl = work->unk4CB4[no + 49] = Hu3DModelCreateData(lbl_1_data_1C8[no + 49]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[no + 49]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            eff->unk000.x = 600.0f * work->unk4CB0 - 300.0f;
            eff->unk000.y = -200.0f;
            eff->unk000.z = -200.0f;
            angle = 84.0f * ((s32)frandmod(10001) / 10000.0f) - 42.0f;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = angle;
            eff->unk00C.z = 0.0f;
            speed = 6.1f + 3.3f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk018.x = speed * HuSin(angle);
            eff->unk018.y = 40.0f + 20.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk018.z = speed * HuCos(angle);
            eff->unk024.z = -5.0f - 3.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk032 = 0;
            eff->unk034 = frandmod(60) * 2 + 30;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 1.2f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.z += eff->unk024.z;
            if (eff->unk00C.z > 360.0f) {
                eff->unk00C.x -= 360.0f; /* retail bug: wraps .x, not .z */
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 203 insns */
s32 fn_1_8CD0(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    float scale;

    switch (eff->unk030) {
        case 0:
            scale = 2.7f;
            if (work->unk4CB4[52] < 0) {
                mdl = work->unk4CB4[52] = Hu3DModelCreateData(lbl_1_data_1C8[52]);
            }
            else {
                mdl = Hu3DModelLink(work->unk4CB4[52]);
            }
            eff->unk036 = mdl;
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            Hu3DModelScaleSet(mdl, scale, scale, scale);
            if (work->unk4CB4[53] < 0) {
                mdl = work->unk4CB4[53] = Hu3DModelCreateData(lbl_1_data_1C8[53]);
            }
            else {
                mdl = Hu3DModelLink(work->unk4CB4[53]);
            }
            eff->unk034 = mdl;
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            Hu3DModelScaleSet(mdl, scale, scale, scale);
            eff->unk000.x = 600.0f * work->unk4CB0 - 300.0f;
            eff->unk000.y = -400.0f;
            eff->unk000.z = -200.0f;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = 0.0f;
            eff->unk00C.z = 0.0f;
            eff->unk032 = 0;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            Hu3DModelPosSetV(eff->unk034, &eff->unk000);
            Hu3DModelRotSetV(eff->unk034, &eff->unk00C);
            Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(eff->unk034, HU3D_ATTR_DISPOFF);
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == 5) {
                eff->unk030++;
            }
            break;
        case 2:
            if (eff->unk000.y >= -40.0f) {
                eff->unk030++;
            }
            eff->unk000.y += 5.0f;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelPosSetV(eff->unk034, &eff->unk000);
            break;
        case 3:
            break;
    }
    return ret;
}

/* 499 insns */
s32 fn_1_8FFC(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    HSFDATA *hsf;
    HSFMATERIAL *mat;
    s32 num;
    s32 i;
    float radius;
    float angle;
    float vy;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[21] < 0) {
                    mdl = work->unk4CB4[21] = Hu3DModelCreateData(lbl_1_data_1C8[21]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[21]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            radius = 135.0f * ((s32)frandmod(10001) / 10000.0f);
            angle = 84.0f * ((s32)frandmod(10001) / 10000.0f) - 42.0f;
            eff->unk000.x = 600.0f * work->unk4CB0 + radius * HuSin(angle) - 300.0;
            eff->unk000.y = -300.0f;
            eff->unk000.z = radius * HuCos(angle) - 210.0;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = 180.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk00C.z = 0.0f;
            eff->unk032 = 0;
            radius = 4.0f + 4.0f * ((s32)frandmod(10001) / 10000.0f);
            vy = 40.0f + 40.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk018.x = radius * HuSin(angle);
            eff->unk018.y = vy;
            eff->unk018.z = 0.1f + radius * HuCos(angle);
            eff->unk024.x = 1.0f + 4.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk024.y = 1.0f + 4.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk024.z = 0.0f;
            hsf = Hu3DData[eff->unk036].hsf;
            mat = hsf->material;
            num = hsf->materialNum;
            for (i = 0; i < num; i++, mat++) {
                mat->color[0] = frandmod(128) + 128;
                mat->color[1] = frandmod(128) + 128;
                mat->color[2] = frandmod(128) + 128;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk032 = 0;
            eff->unk034 = frandmod(5) + 1;
            eff->unk030++;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 0.9f;
            if (eff->unk018.y < 0.0f) {
                eff->unk030++;
            }
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            eff->unk018.y = -3.0f - (30.0f * ((s32)frandmod(10001) / 10000.0f)) / 10.0f;
            eff->unk030++;
        case 4:
            eff->unk018.x *= 0.9f;
            eff->unk018.z *= 0.9f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.x += eff->unk024.x;
            eff->unk00C.y += eff->unk024.y;
            eff->unk00C.z += eff->unk024.z;
            if (eff->unk000.y < -800.0f) {
                ret = 1;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 357 insns */
s32 fn_1_97C8(M528_NODE *task)
{
    s32 ret = 0;
    M528_WORK *work = lbl_1_bss_298->data;
    M528_EFFECT *eff = task->unk00C;
    HU3DMODELID mdl;
    HU3DMOTID mot;
    float angle;
    float speed;
    float vy;

    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[46] < 0) {
                    mdl = work->unk4CB4[46] = Hu3DModelCreateData(lbl_1_data_1C8[46]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[46]);
                }
                if (work->unk4D20[5] < 0) {
                    mot = work->unk4D20[5] = Hu3DJointMotionData(mdl, lbl_1_data_2A0[5]);
                }
                else {
                    mot = work->unk4D20[5];
                }
                Hu3DMotionSet(mdl, mot);
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            angle = eff->unk032;
            speed = 50.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk000.x = 600.0f * work->unk4CB0 + speed * HuSin(angle) - 300.0;
            eff->unk000.y = -300.0f;
            eff->unk000.z = speed * HuCos(angle) - 210.0;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = 360.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk00C.z = 0.0f;
            speed = 4.3f + 2.0f * ((s32)frandmod(10001) / 10000.0f);
            if (angle > 90.0f && angle < 270.0f) {
                speed *= 0.7f;
            }
            vy = 45.0f + 40.0f * ((s32)frandmod(10001) / 10000.0f);
            eff->unk018.x = speed * HuSin(angle);
            eff->unk018.y = vy;
            eff->unk018.z = speed * HuCos(angle);
            eff->unk032 = 0;
            eff->unk034 = frandmod(6) * 5 + 1;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk032 = 0;
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 0.9f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            if (eff->unk000.y < -700.0f) {
                eff->unk030++;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            break;
    }
    return ret;
}

/* FORK_E_BEGIN */

/* uniform random value in [0, 1] (frandmod result converted signed) */
#define M528_FRAND() ((s32)frandmod(10001) / 10000.0f)

/* 401 insns */
s32 fn_1_9D5C(M528_NODE *node)
{
    s32 ret;
    M528_WORK *work;
    M528_EFFECT *eff;
    s32 n;
    s16 mdl;
    float scale;
    float ang;
    float speed;
    float vy;

    ret = 0;
    work = lbl_1_bss_298->data;
    eff = node->unk00C;
    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                n = frandmod(3);
                if (n == 2) {
                    n = 4;
                }
                if (work->unk4CB4[n + 36] < 0) {
                    mdl = work->unk4CB4[n + 36] = Hu3DModelCreateData(lbl_1_data_1C8[n + 36]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[n + 36]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            scale = 0.7f + M528_FRAND();
            Hu3DModelScaleSet(mdl, scale, scale, 1.0f);
            ang = 84.0f * M528_FRAND() - 42.0f;
            speed = 40.0f * M528_FRAND();
            eff->unk000.x = 600.0f * work->unk4CB0 + speed * HuSin(ang) - 300.0;
            eff->unk000.y = -300.0f;
            eff->unk000.z = speed * HuCos(ang) - 210.0;
            eff->unk00C.x = 0.0f;
            eff->unk00C.y = 0.0f;
            eff->unk00C.z = 0.0f;
            speed = 4.2f + 4.0f * M528_FRAND();
            vy = 35.0f + 28.0f * M528_FRAND();
            eff->unk018.x = speed * HuSin(ang);
            eff->unk018.y = vy;
            eff->unk018.z = speed * HuCos(ang);
            eff->unk024.z = 5.0f + 5.0f * M528_FRAND();
            eff->unk032 = 0;
            eff->unk034 = frandmod(6) * 5 + 1;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk032 = 0;
            eff->unk030++;
            break;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 0.9f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.z += eff->unk024.z;
            if (eff->unk00C.z >= 360.0f) {
                eff->unk00C.z -= 360.0f;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            break;
    }
    return ret;
}

/* 515 insns */
s32 fn_1_A3A0(M528_NODE *node)
{
    s32 ret;
    M528_WORK *work;
    M528_EFFECT *eff;
    HSFDATA *hsf;
    HSFMATERIAL *mat;
    s32 i;
    s32 matNum;
    s32 c;
    s16 mdl;
    u8 col[3];
    float scale;
    float speed;
    float ang;
    float t;
    float vy;

    ret = 0;
    work = lbl_1_bss_298->data;
    eff = node->unk00C;
    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[38] < 0) {
                    mdl = work->unk4CB4[38] = Hu3DModelCreateData(lbl_1_data_1C8[38]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[38]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            scale = 0.1f + 0.5f * M528_FRAND();
            Hu3DModelScaleSet(mdl, scale, scale, scale);
            speed = 100.0f * M528_FRAND();
            ang = 84.0f * M528_FRAND() - 42.0f;
            eff->unk000.x = 600.0f * work->unk4CB0 + speed * HuSin(ang) - 300.0;
            eff->unk000.y = -300.0f;
            eff->unk000.z = speed * HuCos(ang) - 210.0;
            t = M528_FRAND();
            eff->unk00C.x = 350.0f - 60.0f * t;
            eff->unk00C.y = 180.0f * M528_FRAND();
            eff->unk00C.z = 0.0f;
            eff->unk032 = 0;
            speed = 4.0f + 4.0f * M528_FRAND();
            vy = 30.0f + 30.0f * M528_FRAND();
            eff->unk018.x = speed * HuSin(ang);
            eff->unk018.y = vy;
            eff->unk018.z = speed * HuCos(ang);
            eff->unk024.x = t;
            eff->unk024.y = 4.0f + 8.0f * M528_FRAND();
            eff->unk024.z = 0.0f;
            hsf = Hu3DData[eff->unk036].hsf;
            mat = hsf->material;
            matNum = hsf->materialNum;
            c = frandmod(3);
            col[0] = 0x60;
            col[1] = 0x60;
            col[2] = 0x60;
            col[c] += frandmod(128) + 0x20;
            for (i = 0; i < matNum; i++, mat++) {
                mat->color[0] = col[0];
                mat->color[1] = col[1];
                mat->color[2] = col[2];
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk032 = 0;
            eff->unk034 = frandmod(3) * 3 + 1;
            eff->unk030++;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 0.9f;
            if (eff->unk018.y < 0.0f) {
                eff->unk030++;
            }
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            eff->unk018.y = -4.0f - 30.0f * eff->unk024.x / 10.0f;
            eff->unk030++;
        case 4:
            eff->unk018.x *= 0.9f;
            eff->unk018.z *= 0.9f;
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            eff->unk00C.y += eff->unk024.y;
            if (eff->unk000.y < -800.0f) {
                ret = 1;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 502 insns */
s32 fn_1_ABAC(M528_NODE *node)
{
    s32 ret;
    M528_WORK *work;
    M528_EFFECT *eff;
    s16 mdl;
    float scale;
    float speed;
    float ang;
    float t;
    float vy;

    ret = 0;
    work = lbl_1_bss_298->data;
    eff = node->unk00C;
    switch (eff->unk030) {
        case 0:
            if (eff->unk036 < 0) {
                if (work->unk4CB4[39] < 0) {
                    mdl = work->unk4CB4[39] = Hu3DModelCreateData(lbl_1_data_1C8[39]);
                }
                else {
                    mdl = Hu3DModelLink(work->unk4CB4[39]);
                }
                eff->unk036 = mdl;
            }
            else {
                mdl = eff->unk036;
            }
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdl, 2);
            scale = 0.1f + 0.5f * M528_FRAND();
            Hu3DModelScaleSet(mdl, scale, scale, scale);
            speed = 100.0f * M528_FRAND();
            ang = 84.0f * M528_FRAND() - 42.0f;
            eff->unk000.x = 600.0f * work->unk4CB0 + speed * HuSin(ang) - 300.0;
            eff->unk000.y = -300.0f;
            eff->unk000.z = speed * HuCos(ang) - 210.0;
            t = M528_FRAND();
            eff->unk00C.x = 350.0f - 60.0f * t;
            eff->unk00C.y = 180.0f * M528_FRAND();
            eff->unk00C.z = 0.0f;
            eff->unk032 = 0;
            speed = 4.0f + 4.0f * M528_FRAND();
            vy = 30.0f + 30.0f * M528_FRAND();
            eff->unk018.x = speed * HuSin(ang);
            eff->unk018.y = vy;
            eff->unk018.z = speed * HuCos(ang);
            eff->unk024.x = t;
            eff->unk024.y = 4.0f + 8.0f * M528_FRAND();
            eff->unk024.z = 0.0f;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            eff->unk032 = 0;
            eff->unk034 = frandmod(3) * 3 + 1;
            eff->unk030++;
        case 1:
            eff->unk032++;
            if (eff->unk032 == eff->unk034) {
                Hu3DModelAttrReset(eff->unk036, HU3D_ATTR_DISPOFF);
                eff->unk030++;
            }
            break;
        case 2:
            eff->unk018.y -= 0.9f;
            if (eff->unk018.y < 0.0f) {
                eff->unk030++;
            }
            eff->unk000.x += eff->unk018.x;
            eff->unk000.y += eff->unk018.y;
            eff->unk000.z += eff->unk018.z;
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
        case 3:
            eff->unk018.y = -4.0f - 30.0f * eff->unk024.x / 10.0f;
            eff->unk030++;
        case 4:
            eff->unk018.x *= 0.9f;
            eff->unk018.z *= 0.9f;
            eff->unk000.x += eff->unk018.x;
            eff->unk00C.y += eff->unk024.y;
            /* retail: adds unk018.x (not .z) plus a sine wobble to z */
            eff->unk000.z += eff->unk018.x + HuSin(eff->unk00C.y);
            eff->unk000.y += eff->unk018.y + HuCos(eff->unk00C.y);
            if (eff->unk000.y < -800.0f) {
                ret = 1;
            }
            Hu3DModelPosSetV(eff->unk036, &eff->unk000);
            Hu3DModelRotSetV(eff->unk036, &eff->unk00C);
            break;
    }
    return ret;
}

/* 105 insns */
void fn_1_B384(M528_WORK *work)
{
    float s;
    float c;
    s32 n;
    s32 i;

    s = HuSin(work->unk4C98);
    c = HuCos(work->unk4C98);
    n = 55;
    for (i = 0; i < n; i++) {
        lbl_1_bss_4[i].x = c * lbl_1_data_31C[i].x + s * lbl_1_data_31C[i].z;
        lbl_1_bss_4[i].z = s * -lbl_1_data_31C[i].x + c * lbl_1_data_31C[i].z - 1680.0f;
        lbl_1_bss_4[i].y = lbl_1_data_31C[i].y - 600.0f;
    }
}

/* 107 insns */
void fn_1_B528(M528_CART *cart, s16 delay)
{
    M528_WORK *work;
    s16 mdl;
    s16 mot;

    work = lbl_1_bss_298->data;
    if (work->unk4CB4[46] < 0) {
        mdl = work->unk4CB4[46] = Hu3DModelCreateData(lbl_1_data_1C8[46]);
    }
    else {
        mdl = Hu3DModelLink(work->unk4CB4[46]);
    }
    if (work->unk4D20[5] < 0) {
        mot = work->unk4D20[5] = Hu3DJointMotionData(mdl, lbl_1_data_2A0[5]);
    }
    else {
        mot = work->unk4D20[5];
    }
    Hu3DMotionSet(mdl, mot);
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 0);
    cart->unk020 = mdl;
    cart->unk000 = lbl_1_bss_4[0];
    cart->unk00C.x = 0.0f;
    cart->unk00C.y = 0.0f;
    cart->unk00C.z = 0.0f;
    cart->unk022 = 0;
    cart->unk024 = 0;
    cart->unk026 = 0;
    cart->unk028 = delay;
    cart->unk02A = 55;
    Hu3DModelPosSetV(mdl, &cart->unk000);
    Hu3DModelRotSetV(mdl, &cart->unk00C);
}

/* out = heading in degrees of the XZ vector (x, z); x and z are evaluated textually */
#define M528_ANGLE_XZ(out, x, z)                 \
    {                                            \
        float rad_;                              \
        if (0.0f == (z)) {                       \
            if ((x) >= 0.0f) {                   \
                rad_ = 1.5707964f;               \
            }                                    \
            else {                               \
                rad_ = -1.5707964f;              \
            }                                    \
        }                                        \
        else {                                   \
            rad_ = atan2f((x), (z));             \
        }                                        \
        (out) = 180.0f * rad_ / acos(-1.0);      \
    }

/* 784 insns */
void fn_1_B6D4(M528_CART *cart)
{
    float t;
    float r;
    s32 i;
    HuVecF *a;
    HuVecF *b;
    float x0;
    float z0;
    float x1;
    float z1;

    switch (cart->unk022) {
        case 1:
            cart->unk024 = 0;
            cart->unk022++;
        case 2:
            cart->unk024++;
            if (cart->unk024 >= cart->unk028) {
                cart->unk024 = 0;
                cart->unk022++;
            }
            break;
        case 3:
            cart->unk024 = 0;
            cart->unk026 = 0;
            cart->unk000 = lbl_1_bss_4[0];
            x0 = lbl_1_bss_4[0].x;
            z0 = lbl_1_bss_4[0].z;
            x1 = lbl_1_bss_4[1].x;
            z1 = lbl_1_bss_4[1].z;
            M528_ANGLE_XZ(r, x1 - x0, z1 - z0);
            if (r < 0.0f) {
                r += 360.0f;
            }
            cart->unk00C.y = r;
            cart->unk018 = r;
            x0 = lbl_1_bss_4[1].x;
            z0 = lbl_1_bss_4[1].z;
            x1 = lbl_1_bss_4[2].x;
            z1 = lbl_1_bss_4[2].z;
            M528_ANGLE_XZ(r, x1 - x0, z1 - z0);
            if (r < 0.0f) {
                r += 360.0f;
            }
            cart->unk01C = r;
            if (cart->unk01C < cart->unk018) {
                cart->unk01C += 360.0f;
            }
            Hu3DModelAttrReset(cart->unk020, HU3D_ATTR_DISPOFF);
            cart->unk022++;
        case 4:
            cart->unk024++;
            t = cart->unk024 / 120.0f;
            i = cart->unk026;
            a = &lbl_1_bss_4[i];
            b = &lbl_1_bss_4[i] + 1;
            cart->unk000.x = a->x * (1.0f - t) + b->x * t;
            cart->unk000.y = a->y * (1.0f - t) + b->y * t;
            cart->unk000.z = a->z * (1.0f - t) + b->z * t;
            Hu3DModelPosSetV(cart->unk020, &cart->unk000);
            Hu3DModelRotSetV(cart->unk020, &cart->unk00C);
            if (cart->unk024 == 120) {
                cart->unk024 = 0;
                cart->unk026++;
                cart->unk022++;
            }
            break;
        case 5:
            cart->unk018 = cart->unk00C.y;
            cart->unk022++;
        case 6:
            cart->unk024++;
            t = cart->unk024 / 60.0f;
            cart->unk00C.y = cart->unk018 * (1.0f - t) + cart->unk01C * t;
            Hu3DModelPosSetV(cart->unk020, &cart->unk000);
            Hu3DModelRotSetV(cart->unk020, &cart->unk00C);
            if (cart->unk024 == 60) {
                cart->unk018 = cart->unk00C.y;
                a = &lbl_1_bss_4[cart->unk026];
                b = a + 1;
                {
                    float dx;
                    float dz;
                    dz = b->z - a->z;
                    dx = b->x - a->x;
                    M528_ANGLE_XZ(r, dx, dz);
                }
                while (r < cart->unk018) {
                    r += 360.0f;
                }
                cart->unk01C = r;
                cart->unk024 = 0;
                cart->unk022++;
            }
            break;
        case 7:
            cart->unk018 = cart->unk00C.y;
            a = &lbl_1_bss_4[cart->unk026];
            b = a + 1;
            {
                float dx;
                float dz;
                dz = b->z - a->z;
                dx = b->x - a->x;
                M528_ANGLE_XZ(r, dx, dz);
            }
            while (r < cart->unk018) {
                r += 360.0f;
            }
            if (r - cart->unk018 > 180.0f) {
                r = cart->unk018;
            }
            cart->unk01C = r;
            cart->unk022++;
        case 8:
            cart->unk024++;
            t = cart->unk024 / 30.0f;
            i = cart->unk026;
            a = &lbl_1_bss_4[i];
            b = &lbl_1_bss_4[i] + 1;
            cart->unk000.x = a->x * (1.0f - t) + b->x * t;
            cart->unk000.y = a->y * (1.0f - t) + b->y * t;
            cart->unk000.z = a->z * (1.0f - t) + b->z * t;
            cart->unk00C.y = cart->unk018 * (1.0f - t) + cart->unk01C * t;
            Hu3DModelPosSetV(cart->unk020, &cart->unk000);
            Hu3DModelRotSetV(cart->unk020, &cart->unk00C);
            if (cart->unk024 == 30) {
                cart->unk026++;
                cart->unk024 = 0;
                if (cart->unk026 == cart->unk02A - 2) {
                    cart->unk022++;
                }
                else {
                    cart->unk022--;
                }
            }
            break;
        case 9:
            cart->unk018 = cart->unk00C.y;
            a = &lbl_1_bss_4[cart->unk026];
            b = a + 1;
            {
                float dx;
                float dz;
                dz = b->z - a->z;
                dx = b->x - a->x;
                M528_ANGLE_XZ(r, dx, dz);
            }
            while (r < cart->unk018) {
                r += 360.0f;
            }
            cart->unk01C = r;
            cart->unk022++;
        case 10:
            cart->unk024++;
            t = cart->unk024 / 60.0f;
            cart->unk00C.y = cart->unk018 * (1.0f - t) + cart->unk01C * t;
            Hu3DModelPosSetV(cart->unk020, &cart->unk000);
            Hu3DModelRotSetV(cart->unk020, &cart->unk00C);
            if (cart->unk024 == 60) {
                cart->unk024 = 0;
                cart->unk022++;
            }
            break;
        case 11:
            cart->unk024++;
            t = cart->unk024 / 120.0f;
            i = cart->unk026;
            a = &lbl_1_bss_4[i];
            b = &lbl_1_bss_4[i] + 1;
            cart->unk000.x = a->x * (1.0f - t) + b->x * t;
            cart->unk000.y = a->y * (1.0f - t) + b->y * t;
            cart->unk000.z = a->z * (1.0f - t) + b->z * t;
            Hu3DModelPosSetV(cart->unk020, &cart->unk000);
            Hu3DModelRotSetV(cart->unk020, &cart->unk00C);
            if (cart->unk024 == 120) {
                cart->unk024 = 0;
                cart->unk026++;
                cart->unk022++;
            }
            break;
        case 12:
            cart->unk024++;
            if (cart->unk024 == 90) {
                cart->unk024 = 0;
                cart->unk022 = 3;
            }
            break;
    }
}

/* add a node to the work's active list from its free list */
static inline M528_NODE *M528NodeCreate(M528_WORK *work, s32 (*func)(M528_NODE *node), M528_EFFECT *eff)
{
    M528_NODE *node;

    node = work->unk3E0;
    if (node) {
        work->unk3E0 = node->unk004;
        node->unk008 = func;
        node->unk00C = eff;
        node->unk004 = work->unk3DC;
        if (node->unk004) {
            node->unk004->unk000 = node;
        }
        work->unk3DC = node;
    }
    return node;
}

static inline void M528EffectInit(M528_EFFECT *eff)
{
    eff->unk030 = 0;
    eff->unk036 = -1;
}

/* 50 insns */
void fn_1_C314(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    for (i = 0; i < 128; i++) {
        node = M528NodeCreate(work, fn_1_6DF0, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
}

/* 85 insns */
void fn_1_C3DC(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    i = 0;
    node = M528NodeCreate(work, fn_1_7794, &work->unk13E4[i]);
    if (node) {
        M528EffectInit(&work->unk13E4[i]);
    }
    for (i++; i < 128; i++) {
        node = M528NodeCreate(work, fn_1_72E4, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
}

/* 126 insns */
void fn_1_C530(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    for (i = 0; i < 10; i++) {
        node = M528NodeCreate(work, fn_1_9D5C, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
    for (; i < 90; i++) {
        node = M528NodeCreate(work, fn_1_A3A0, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
    for (; i < 95; i++) {
        node = M528NodeCreate(work, fn_1_ABAC, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
}

/* 99 insns */
void fn_1_C728(M528_WORK *work)
{
    s16 order[24];
    M528_NODE *node;
    s32 i;
    s16 a;
    s16 b;
    s16 tmp;

    for (i = 0; i < 24; i++) {
        order[i] = i;
    }
    for (i = 0; i < 12; i++) {
        a = frandmod(24);
        b = frandmod(24);
        tmp = order[a];
        order[a] = order[b];
        order[b] = tmp;
    }
    for (i = 0; i < 24; i++) {
        node = M528NodeCreate(work, fn_1_7B44, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
            work->unk13E4[i].unk032 = order[i];
            work->unk13E4[i].unk034 = i * 10 + 10;
        }
    }
}

/* 96 insns */
void fn_1_C8B4(M528_WORK *work)
{
    s16 order[24];
    M528_NODE *node;
    s32 i;
    s16 a;
    s16 b;
    s16 tmp;

    for (i = 0; i < 24; i++) {
        order[i] = i;
    }
    for (i = 0; i < 12; i++) {
        a = frandmod(24);
        b = frandmod(24);
        tmp = order[a];
        order[a] = order[b];
        order[b] = tmp;
    }
    for (i = 0; i < 24; i++) {
        node = M528NodeCreate(work, fn_1_97C8, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
            work->unk13E4[i].unk032 = order[i] * 4 - 46;
        }
    }
}

/* 46 insns */
void fn_1_CA34(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    i = 0;
    node = M528NodeCreate(work, fn_1_800C, &work->unk13E4[i]);
    if (node) {
        M528EffectInit(&work->unk13E4[i]);
    }
}

/* 85 insns */
void fn_1_CAEC(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    i = 0;
    node = M528NodeCreate(work, fn_1_83E4, &work->unk13E4[i]);
    if (node) {
        M528EffectInit(&work->unk13E4[i]);
    }
    for (i++; i < 35; i++) {
        node = M528NodeCreate(work, fn_1_87F4, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
}

/* 85 insns */
void fn_1_CC40(M528_WORK *work)
{
    M528_NODE *node;
    s32 i;

    i = 0;
    node = M528NodeCreate(work, fn_1_8CD0, &work->unk13E4[i]);
    if (node) {
        M528EffectInit(&work->unk13E4[i]);
    }
    for (i++; i < 128; i++) {
        node = M528NodeCreate(work, fn_1_8FFC, &work->unk13E4[i]);
        if (node) {
            M528EffectInit(&work->unk13E4[i]);
        }
    }
}

