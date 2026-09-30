/*
 * m520Dll m520.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m520Dll/asm/REL/m520Dll/m520.s.
 */

#include "REL/m520Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "game/esprite.h"
#include "game/init.h"
#include "datadir_enum.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include <string.h>

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 25; */
/* 0x18 */ /* double lbl_1_rodata_18 = 0.03125; */
/* 0x20 */ /* double lbl_1_rodata_20 = -32; */
/* 0x28 */ /* float lbl_1_rodata_28 = 2.0f; */
/* 0x30 */ /* double lbl_1_rodata_30 = 3.141592653589793; */
/* 0x38 */ /* double lbl_1_rodata_38 = 180; */
/* 0x40 */ /* double lbl_1_rodata_40 = 4503601774854144; */
/* 0x48 */ /* float lbl_1_rodata_48 = 2000.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 10.0f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 12.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 0.0f; */
/* 0x58 */ /* float lbl_1_rodata_58 = 5.0f; */
/* 0x60 */ /* double lbl_1_rodata_60 = 0.7; */
/* 0x68 */ /* float lbl_1_rodata_68 = 1.0f; */
/* 0x6C */ /* s32 lbl_1_rodata_6C[8] = { 0x0000001E, 0x0000000A, 0x0000000A, 0x00000000, 0x0000001E, 0x00000014, 0x0000000A, 0x00000005 }; */
/* 0x8C */ /* s32 lbl_1_rodata_8C[4] = { 0x00000014, 0x00000032, 0x00000046, 0x0000005A }; */
/* 0x9C */ /* s32 lbl_1_rodata_9C[4] = { 0x00000000, 0x0000000A, 0x0000001E, 0x00000032 }; */
/* 0xAC */ /* s32 lbl_1_rodata_AC[8] = { 0x00000078, 0x0000003C, 0x00000014, 0x00000014, 0x0000003C, 0x0000001E, 0x0000005A, 0x0000003C }; */
/* 0xCC */ /* s32 lbl_1_rodata_CC[8] = { 0x0000000F, 0x0000000F, 0x0000000A, 0x00000007, 0x00000014, 0x00000014, 0x0000000F, 0x0000000A }; */
/* 0xEC */ /* s32 lbl_1_rodata_EC[8] = { 0x00000017, 0x00000012, 0x0000000C, 0x0000000A, 0x0000000F, 0x00000005, 0x00000004, 0x00000004 }; */
/* 0x10C */ /* s32 lbl_1_rodata_10C[5] = { 0x00000000, 0x00000002, 0x00000006, 0x00000008, 0x0000000A }; */
/* 0x120 */ /* s32 lbl_1_rodata_120[5] = { 0x00000000, 0x00000000, 0x00000000, 0x00000005, 0x0000000A }; */
/* 0x134 */ /* s32 lbl_1_rodata_134[10] = { 0x00000000, 0x00000000, 0x00000001, 0x00000002, 0x00000007, 0x00000000, 0x00000000, 0x00000001, 0x00000002, 0x0000000A }; */
/* 0x15C */ /* s32 lbl_1_rodata_15C[20] = { 0x00000028, 0x00000028, 0x0000004A, 0x0000004B, 0x0000006C, 0x000000A1, 0x000000BA, 0x000000E5, 0x00000116, 0x0000014D, 0x00000176, 0x000001AF, 0x000001D6, 0x00000209, 0x00000235, 0x00000265, 0x00000283, 0x000002BC, 0x000002BC, 0x000002BC }; */
/* 0x1AC */ /* s32 lbl_1_rodata_1AC[20] = { 0x00000068, 0x00000078, 0x0000007E, 0x0000009B, 0x000000BC, 0x000000E3, 0x0000010A, 0x00000135, 0x00000166, 0x0000019D, 0x000001CE, 0x000001FF, 0x00000226, 0x00000259, 0x00000285, 0x000002B9, 0x000002EE, 0x00000320, 0x00000320, 0x00000320 }; */
/* 0x1FC */ /* s32 lbl_1_rodata_1FC[30] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFF1, 0xFFFFFFE2, 0x00000000, 0xFFFFFFF1, 0xFFFFFFE2, 0xFFFFFFF6, 0x00000000, 0xFFFFFFEC, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFE2, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x274 */ /* float lbl_1_rodata_274 = 15.0f; */
/* 0x278 */ /* float lbl_1_rodata_278 = 96.0f; */
/* 0x27C */ /* float lbl_1_rodata_27C = -1.0f; */
/* 0x280 */ /* float lbl_1_rodata_280 = 360.0f; */
/* 0x288 */ /* double lbl_1_rodata_288 = 0.5; */
/* 0x290 */ /* double lbl_1_rodata_290 = 3; */
/* 0x298 */ /* float lbl_1_rodata_298 = -180.0f; */
/* 0x29C */ /* float lbl_1_rodata_29C = 180.0f; */
/* 0x2A0 */ /* float lbl_1_rodata_2A0 = 300.0f; */
/* 0x2A4 */ /* float lbl_1_rodata_2A4 = 400.0f; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = 60; */
/* 0x2B0 */ /* float lbl_1_rodata_2B0 = 100.0f; */
/* 0x2B4 */ /* float lbl_1_rodata_2B4 = 255.0f; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 1; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 0.01; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = 30; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = 1.5f; */
/* 0x2D4 */ /* float lbl_1_rodata_2D4 = 20.0f; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 55.0f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = -55.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 10000.0f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 80.0f; */
/* 0x2E8 */ /* float lbl_1_rodata_2E8 = 70.0f; */
/* 0x2EC */ /* float lbl_1_rodata_2EC = 440.0f; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 210.0f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 150.0f; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 30.0f; */
/* 0x300 */ /* double lbl_1_rodata_300 = 0.3; */
/* 0x308 */ /* double lbl_1_rodata_308 = 45; */
/* 0x310 */ /* double lbl_1_rodata_310 = 35; */
/* 0x318 */ /* float lbl_1_rodata_318 = 5.6f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 120.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 64.0f; */
/* 0x324 */ /* float lbl_1_rodata_324 = -5.6f; */
/* 0x328 */ /* float lbl_1_rodata_328 = 700.0f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 9025.0f; */
/* 0x330 */ /* float lbl_1_rodata_330 = 1800.0f; */
/* 0x334 */ /* float lbl_1_rodata_334 = 16.0f; */
/* 0x338 */ /* float lbl_1_rodata_338 = 50.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 0.04f; */
/* 0x340 */ /* float lbl_1_rodata_340 = 0.5f; */
/* 0x344 */ /* s32 lbl_1_rodata_344[10] = { 0x43F00000, 0x44048000, 0x44048000, 0x43F00000, 0x43F00000, 0x44048000, 0x44098000, 0x43DC0000, 0x43F00000, 0x43F00000 }; */
/* 0x36C */ /* s32 lbl_1_rodata_36C[10] = { 0xC2200000, 0xC2080000, 0xC1D80000, 0xC2200000, 0xC2180000, 0xC1D80000, 0xC2200000, 0xC2200000, 0xC1F00000, 0xC2200000 }; */
/* 0x394 */ /* float lbl_1_rodata_394 = 48.0f; */
/* 0x398 */ /* float lbl_1_rodata_398 = 0.0625f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 8.5f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 63.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 1425.0f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 4575.0f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = 505.0f; */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = -120.0f; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = -35.0f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = -70.0f; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = -120; */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 6.0f; */
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 1.2217304763960306; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = 0.9f; */
/* 0x3DC */ /* float lbl_1_rodata_3DC = 900.0f; */
/* 0x3E0 */ /* float lbl_1_rodata_3E0 = 140.0f; */
/* 0x3E4 */ /* float lbl_1_rodata_3E4 = 3825.0f; */
/* 0x3E8 */ /* float lbl_1_rodata_3E8 = -95.0f; */
/* 0x3EC */ /* float lbl_1_rodata_3EC = -51.0f; */
/* 0x3F0 */ /* float lbl_1_rodata_3F0 = 0.6666667f; */
/* 0x3F4 */ /* float lbl_1_rodata_3F4 = -190.0f; */
/* 0x3F8 */ /* double lbl_1_rodata_3F8 = -50; */
/* 0x400 */ /* float lbl_1_rodata_400 = 135.0f; */
/* 0x404 */ /* float lbl_1_rodata_404 = -50.0f; */
/* 0x408 */ /* float lbl_1_rodata_408 = 40.0f; */
/* 0x40C */ /* float lbl_1_rodata_40C = 240.0f; */
/* 0x410 */ /* float lbl_1_rodata_410 = -90.0f; */
/* 0x414 */ /* float lbl_1_rodata_414 = 45.0f; */
/* 0x418 */ /* float lbl_1_rodata_418 = 500.0f; */
/* 0x420 */ /* double lbl_1_rodata_420 = 175; */
/* 0x428 */ /* double lbl_1_rodata_428 = 200; */
/* 0x430 */ /* double lbl_1_rodata_430 = 575; */
/* 0x438 */ /* float lbl_1_rodata_438 = -4.285714f; */
/* 0x43C */ /* float lbl_1_rodata_43C = 60.0f; */
/* 0x440 */ /* s32 lbl_1_rodata_440[8] = { 0x00000722, 0x00000723, 0x00000724, 0x00000725, 0x00000726, 0x00000727, 0x00000728, 0x00000729 }; */
/* 0x460 */ /* s32 lbl_1_rodata_460[12] = { 0xC3160000, 0x43160000, 0x00000000, 0x43160000, 0x43160000, 0x00000000, 0x43160000, 0xC3160000, 0x00000000, 0xC3160000, 0xC3160000, 0x00000000 }; */
/* 0x490 */ /* float lbl_1_rodata_490 = 0.2f; */
/* 0x494 */ /* float lbl_1_rodata_494 = 0.003125f; */
/* 0x498 */ /* float lbl_1_rodata_498 = 0.0078125f; */
/* 0x49C */ /* s32 lbl_1_rodata_49C[6] = { 0x00000000, 0x3B2EC33E, 0x00000000, 0x3B83126F, 0x00000000, 0x00000000 }; */
/* 0x4B4 */ /* float lbl_1_rodata_4B4 = 0.03125f; */
/* 0x4B8 */ /* double lbl_1_rodata_4B8 = 128; */
/* 0x4C0 */ /* double lbl_1_rodata_4C0 = 127; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 480.0f; */
/* 0x4CC */ /* float lbl_1_rodata_4CC = 0.05f; */
/* 0x4D0 */ /* s32 lbl_1_rodata_4D0[5] = { 0x004E000D, 0x004E000E, 0x004E000F, 0x004E0010, 0x004E0011 }; */
/* 0x4E4 */ /* float lbl_1_rodata_4E4 = 450.0f; */
/* 0x4E8 */ /* float lbl_1_rodata_4E8 = 0.25f; */
/* 0x4EC */ /* float lbl_1_rodata_4EC = 540.0f; */
/* 0x4F0 */ /* s32 lbl_1_rodata_4F0[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 }; */
/* 0x500 */ /* float lbl_1_rodata_500 = 600.0f; */
/* 0x504 */ /* float lbl_1_rodata_504 = -500.0f; */
/* 0x508 */ /* float lbl_1_rodata_508 = 75.0f; */
/* 0x50C */ /* s32 lbl_1_rodata_50C[3] = { 0x00000000, 0x459C4000, 0x00000000 }; */
/* 0x518 */ /* s32 lbl_1_rodata_518[3] = { 0x00000000, 0xBF800000, 0xBF000000 }; */
/* 0x524 */ /* u8 lbl_1_rodata_524[1] = { 0xFF }; */
/* 0x525 */ /* u8 lbl_1_rodata_525[1] = { 0xFF, 0xFF, 0xFF }; */
/* 0x528 */ /* float lbl_1_rodata_528 = 25000.0f; */
/* 0x52C */ /* float lbl_1_rodata_52C = 1.2f; */
/* 0x530 */ /* float lbl_1_rodata_530 = 640.0f; */
/* 0x534 */ /* float lbl_1_rodata_534 = 5000.0f; */
/* 0x538 */ /* float lbl_1_rodata_538 = -0.1f; */
/* 0x53C */ /* float lbl_1_rodata_53C = 13000.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0[39] = { 0x00890000, 0x00300000, 0x00B40000, 0x00EA0000, 0x00E30000, 0x00140000, 0x00DD0000, 0x002A0000, 0x00C60000, 0x00AD0000, 0x00000000, 0x00000000, 0x00000000, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C000F, 0x008C004B, 0x00870069, 0x008C0016, 0x008C004F, 0x008C001F, 0x008C0031, 0x00000001, 0x00010000, 0x00010808, 0x08000808, 0x08080808, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000001C, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFF0000 }; /* dtk pad_: no instruction references it; kept for the .data layout */
/* 0x9C */ s32 lbl_1_data_9C[1] = { 0xFFFFFFFF };
/* 0xA0 */ s32 lbl_1_data_A0[1] = { 0xFFFFFFFF };
/* 0xA4 */ s32 lbl_1_data_A4[1] = { 0x00000001 };
/* 0xA8 */ MGSEQ_PARAM lbl_1_data_A8 = { 30, 2, fn_1_9CE0, fn_1_5F48, fn_1_5F4C, fn_1_5F50, fn_1_5F54, fn_1_5F58, fn_1_5F5C, fn_1_5F60, fn_1_9E18 };
/* 0xD0 */ u8 lbl_1_data_D0[13] = { 0x0D, 0x00, 0x17, 0x69, 0x0D, 0x1D, 0x14, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D }; /* lbz */
/* 0xDD */ char lbl_1_data_DD[] = "%f,%f,%f";
/* 0xE6 */ char lbl_1_data_E6[] = "%f";
/* 0xEC */ float lbl_1_data_EC[5] = { 32.0f, 32.0f, 32.0f, 32.0f, 60.0f };
/* 0x100 */ s32 lbl_1_data_100[1] = { 0x00000006 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5C8 */ M520_WORK lbl_1_bss_5C8; /* game state; memset by fn_1_7ED8 */
/* 0x280 */ M520_PARTICLE lbl_1_bss_280[30];
/* 0x270 */ M520_PAIR lbl_1_bss_270[2];
/* 0x1D0 */ M520_SE lbl_1_bss_1D0[8];
/* 0x1CC */ OMOBJ *lbl_1_bss_1CC; /* prio 0x67 fn_1_9860 */
/* 0x1C8 */ OMOBJ *lbl_1_bss_1C8; /* prio 0x7FDA omOutView */
/* 0x1B8 */ OMOBJ *lbl_1_bss_1B8[4]; /* prio 0x66 fn_1_8A98, obj->data = 0x54-byte malloc */
/* 0x1B4 */ OMOBJ *lbl_1_bss_1B4; /* prio 0x64 fn_1_7ED8 */
/* 0x1A4 */ MGPLAYER *lbl_1_bss_1A4[4];
/* 0x1A0 */ s32 lbl_1_bss_1A0; /* MgSeq mode (MgSeqModeGet result), cmpwi 2/3/5/6/8/9, cmplwi 0xB */
/* 0x19C */ OMOBJMAN *lbl_1_bss_19C; /* MgActorObjectSetup() */
/* 0x19A gap_05_0000019A_bss (0x2) -- dtk filler */
/* 0x198 */ s16 lbl_1_bss_198; /* GameMes id, -1 = none */
/* 0x190 */ s32 lbl_1_bss_190[2]; /* [0] the s16 Hu3DGLightCreateV id stored word-wide; [1] unreferenced */
/* 0x17C */ s32 lbl_1_bss_17C[5]; /* [0] an espEntry id stored word-wide; [1..4] unreferenced */
/* 0x16C */ u32 lbl_1_bss_16C[4]; /* [0] GXGetTexBufferSize(640, 480, 6); [1..3] unreferenced */
/* 0x168 */ void *lbl_1_bss_168; /* tex buffer, lbl_1_bss_16C[0] bytes */
/* 0x164 */ u32 lbl_1_bss_164; /* GXGetTexBufferSize(32, 32, 3); cmplwi 0 */
/* 0x160 */ void *lbl_1_bss_160; /* tex buffer, lbl_1_bss_164 bytes */
/* 0x15C */ MGPLAYER_MODE_FUNC lbl_1_bss_15C; /* saved modeFunc[0] (fn_1_8A98 0x9794) */
/* 0x158 */ MGPLAYER_MODE_FUNC lbl_1_bss_158; /* saved modeFunc[5], called by fn_1_90C */
/* 0x118 */ GXTexObj lbl_1_bss_118[2]; /* fn_1_7014 GXInitTexObj/GXLoadTexObj */
/* 0xE8 */ Mtx lbl_1_bss_E8; /* fn_1_7014 PSMTXIdentity + GXLoadPosMtxImm */
/* 0xB8 */ Mtx lbl_1_bss_B8; /* fn_1_7014 C_MTXOrtho + GXSetProjection: a 4x4 written into 3x4 (retail) */
/* 0x48 */ M520_MTXBLK lbl_1_bss_48;
/* 0x18 */ Mtx lbl_1_bss_18; /* fn_1_7830 C_MTXOrtho + GXSetProjection: a 4x4 written into 3x4 (retail) */
/* 0x14 */ s32 lbl_1_bss_14;
/* 0x10 */ s32 lbl_1_bss_10;
/* 0xC */ float lbl_1_bss_C;
/* 0x4 */ s32 lbl_1_bss_4[2]; /* [0] referenced; [1] unreferenced */
/* 0x0 */ s32 lbl_1_bss_0; /* frame counter (MgSeqFrameNoGet) */

/* --- functions (reference order) --- */
/* 382 insns */
void fn_1_A0(void)
{
    HuVecF pos;
    HuVecF center;
    HuVecF up;
    float rx;
    float ry;
    float rz;

    Center.x += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    Center.y += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
    CZoom += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRot.y += HuPadSubStkX[0] / 32.0;
    CRot.x += HuPadSubStkY[0] / -32.0;
    fontcolor = 15;
    print8(64, 392, 2.0f, lbl_1_data_DD, Center.x, Center.y, Center.z);
    print8(64, 408, 2.0f, lbl_1_data_DD, CRot.x, CRot.y, CRot.z);
    print8(64, 424, 2.0f, lbl_1_data_E6, CZoom);
    rx = CRot.x;
    ry = CRot.y;
    rz = CRot.z;
    pos.x = Center.x + CZoom * (sin(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
    pos.y = Center.y + CZoom * -sin(M_PI * rx / 180.0);
    pos.z = Center.z + CZoom * (cos(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
    center.x = Center.x;
    center.y = Center.y;
    center.z = Center.z;
    up.x = sin(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
    up.y = cos(M_PI * rx / 180.0);
    up.z = cos(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
}

/* 157 insns */
void fn_1_698(MGPLAYER *player)
{
    HU3DMODEL *model;

    if (player->actor->colGroundAttr & 0x407F) {
        if (!MgPlayerAttrCheck(player, MGPLAYER_ATTR_COMSTK) && (HuPadBtnDown[player->padNo] & PAD_BUTTON_A)
            && (player->actionFlag & MGPLAYER_ACTFLAG_JUMP)) {
            MgPlayerModeSet(player, MGPLAYER_MODE_JUMP);
        }
    } else if (fabsf(player->actor->velY) > 2000.0f) {
        MgPlayerModeSet(player, MGPLAYER_MODE_FALL);
    }
    if (player->motNo != 11) {
        if (lbl_1_data_100[0] == 0) {
            CharMotionShiftSet(player->charNo, player->omObj->mtnId[11], 10.0f + 10.0f * lbl_1_bss_5C8.unk00C, 12.0f, 0x40000002);
            player->motNo = 11;
        }
        lbl_1_data_100[0] -= lbl_1_data_100[0] > 0;
    }
    if (player->motNo == 11) {
        model = &Hu3DData[lbl_1_bss_1B8[0]->mdlId[0]];
        if (model->motIdShift != -1) {
            model->motShiftWork.time = 10.0f + 10.0f * lbl_1_bss_5C8.unk00C;
        } else {
            Hu3DMotionTimeSet(player->actor->mdlId, 10.0f + 10.0f * lbl_1_bss_5C8.unk00C);
        }
    }
}

/* 63 insns */
void fn_1_90C(MGPLAYER *player)
{
    s32 subMode = player->subMode;

    lbl_1_bss_158(player);
    if (subMode == 2 && player->subMode == 3 && lbl_1_bss_5C8.unk014 == 0) {
        lbl_1_bss_5C8.unk014 = 1;
        if (lbl_1_bss_5C8.unk018 == 0) {
            lbl_1_bss_5C8.unk018 = 1;
            if (lbl_1_bss_1D0[5].unk000 < 3) {
                lbl_1_bss_1D0[5].unk004[lbl_1_bss_1D0[5].unk000] = 0.0f;
                lbl_1_bss_1D0[5].unk000++;
            }
        }
    }
}

/* 35 insns */
void fn_1_A08(MGPLAYER *player)
{
    if (player->motNo != 10) {
        CharMotionShiftSet(player->charNo, player->omObj->mtnId[10], 0.0f, 5.0f, 0);
        player->motNo = 10;
    }
    player->actor->rotY *= 0.7;
}

/* 28 insns */
void fn_1_A94(MGPLAYER *player)
{
    if (player->motNo != 11) {
        CharMotionShiftSet(player->charNo, player->omObj->mtnId[11], 0.0f, 1.0f, 0x40000001);
        player->motNo = 11;
    }
}

/* 27 insns */
void fn_1_B04(MGPLAYER *player)
{
    if (player->motNo != 12) {
        CharMotionShiftSet(player->charNo, player->omObj->mtnId[12], 0.0f, 1.0f, 0);
        player->motNo = 12;
    }
}

/* 3490 insns */
void fn_1_B70(OMOBJ *obj)
{
    M520_PLAYER *work;
    s32 i;
    MGPLAYER *player;
    s32 btn;
    s32 btnDown;
    s32 j;
    s32 t;
    HU3DMODEL *model3;
    s32 stkX;
    s32 stkY;
    s32 best;
    HU3DMODEL *model2;
    s32 btnDownMask;
    HU3DMODEL *model;
    float speed;
    float dx;
    float dz;
    float minDiff;
    float d;
    float zero;
    s32 btnMask;
    float curRate;
    float accel;
    float angle;
    float bestScore;
    float score;
    float cur;
    s32 state;
    s32 inAir;
    float dist;
    float ringAngle;
    float ringSpeed;
    float myAngle;
    float myDist;
    float radius;
    float stkXf;
    float stkYf;
    float mag;
    s32 ring;
    float lo;
    float hi;
    float pdx;
    float pdy;
    float pdz;
    float nx;
    float nz;
    float dist2;
    float ofs;
    float blend;
    s32 kind[2];
    M520_PLAYER *works[4];
    HuVecF pos;
    float runAngle[3];
    float runDiff[3];
    float runDist[3];
    HuVecF runPos[3];

    work = obj->data;
    player = lbl_1_bss_1A4[work->unk000];
    zero = 0.0f;
    stkX = 0;
    stkY = 0;
    btn = 0;
    btnDown = 0;
    for (i = 0; i < 4; i++) {
        works[i] = lbl_1_bss_1B8[i]->data;
    }
    MgActorPosGet(player->actor, &pos);
    if (work->unk000 <= 0 || work->unk01C != 3) {
        obj->trans.x = pos.x;
        obj->trans.y = pos.y;
        obj->trans.z = pos.z;
        obj->rot.y = player->actor->rotY;
    }
    lbl_1_bss_1A0 = MgSeqModeGet();
    lbl_1_bss_0 = MgSeqFrameNoGet();
    btnMask = HuPadBtn[player->padNo] & ~PAD_BUTTON_A;
    btnDownMask = HuPadBtnDown[player->padNo] & ~PAD_BUTTON_A;
    if (lbl_1_bss_1A0 != 5) {
        MgPlayerPadSet(player, 0, 0, 0, 0);
        HuPadTrigL[player->padNo] = HuPadTrigR[player->padNo] = 0;
    } else if (work->unk010 != -1) {
        stkX = HuPadStkX[work->unk010];
        stkY = HuPadStkY[work->unk010];
        btn = HuPadBtn[work->unk010];
        btnDown = HuPadBtnDown[work->unk010];
    }
    if (work->unk000 == 0) {
        model = &Hu3DData[obj->mdlId[0]];
        speed = 0.0f;
        curRate = lbl_1_bss_5C8.unk00C;
        accel = 15.0f;
        Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->mdlId[1], HU3D_ATTR_DISPOFF);
        if (lbl_1_bss_1A0 == 2) {
            if (lbl_1_bss_0 == 68) {
                btn = btnDown = 256;
            } else if (lbl_1_bss_0 > 68 && lbl_1_bss_0 <= 71) {
                btn = 256;
            } else if (lbl_1_bss_0 == 78) {
                btn = btnDown = 256;
            }
        } else if (lbl_1_bss_1A0 == 5 && work->unk010 != -1) {
            speed = ((HuPadBtn[work->unk010] & PAD_TRIGGER_R) > 0) * 96 - ((HuPadBtn[work->unk010] & PAD_TRIGGER_L) > 0) * 96;
            speed /= 96.0f;
        } else if (lbl_1_bss_1A0 == 5) {
            best = -1;
            bestScore = -1.0f;
            angle = lbl_1_bss_5C8.unk008;
            for (i = 0; i < 3; i++) {
                MgActorPosGet(lbl_1_bss_1A4[i + 1]->actor, &runPos[i]);
                runAngle[i] = HuAtan(runPos[i].x, runPos[i].z);
                runDiff[i] = 360.0f;
                runDist[i] = sqrtf(runPos[i].x * runPos[i].x + runPos[i].z * runPos[i].z);
                for (j = 0; j < 3; j++) {
                    d = runAngle[i] - (angle + j * 120);
                    d += (d < -180.0f) ? 180 : ((d > 180.0f) ? -180 : 0);
                    d += (d < -180.0f) ? 180 : ((d > 180.0f) ? -180 : 0);
                    if (fabs(runDiff[i]) > fabs(d)) {
                        runDiff[i] = d;
                    }
                }
                score = 60.0 - fabs(runDiff[i]) + 10.0f * ((runDist[i] < 300.0f) ? 0.0f : (runDist[i] - 300.0f) / 400.0f);
                if (best == -1 || bestScore < score) {
                    best = i;
                    bestScore = score;
                }
            }
            switch (work->unk038) {
            case 0:
                speed = lbl_1_bss_5C8.unk00C;
                if (work->unk03C == 0) {
                    s32 waitTbl[2][4] = { { 30, 10, 10, 0 }, { 30, 20, 10, 5 } };

                    work->unk040 = waitTbl[0][work->unk014] + rand8() % waitTbl[1][work->unk014];
                }
                work->unk03C++;
                if (work->unk03C >= work->unk040) {
                    s32 jumpTbl[4] = { 20, 50, 70, 90 };
                    s32 turnTbl[4] = { 0, 10, 30, 50 };
                    s32 timeTbl[2][4] = { { 120, 60, 20, 20 }, { 60, 30, 90, 60 } };

                    if (lbl_1_bss_5C8.unk018 == 0 && jumpTbl[work->unk014] > 100.0f * (rand8() / 255.0f)) {
                        work->unk038 = 3;
                        work->unk03C = 0;
                    } else {
                        work->unk040 = timeTbl[0][work->unk014] + rand8() % timeTbl[1][work->unk014];
                        if (work->unk014 == 3) {
                            work->unk038 = (lbl_1_bss_5C8.unk00C * runDiff[best] < 0.0f) ? 1 : 2;
                        } else {
                            work->unk038 = (turnTbl[work->unk014] > 100.0f * (rand8() / 255.0f)) ? 2 : 1;
                        }
                        work->unk038 = (work->unk038 == 1) ? 1 : ((work->unk044 == 1) ? rand8() % 2 + 1 : ((work->unk044 >= 2) ? 1 : work->unk038));
                        work->unk03C = 0;
                        if (work->unk038 == 2) {
                            work->unk040 = 0;
                            work->unk044++;
                        } else {
                            work->unk044 = 0;
                        }
                        work->unk048 = ((work->unk038 == 1 || work->unk044 > 0) ? 1.0 : ((rand8() % 3) ? 0.01 : ((rand8() % 3) ? 0.5 : 1.0))) * ((work->unk048 < 0.0f) ? 1 : -1);
                    }
                }
                break;
            case 1:
            case 2:
            case 4:
            case 5:
                speed = work->unk048;
                if (lbl_1_bss_5C8.unk00C == work->unk048) {
                    work->unk03C++;
                    if (work->unk038 != 4 && work->unk03C > work->unk040
                        && !(work->unk014 == 3 && work->unk048 * runDiff[best] >= 0.0f && fabs(runDiff[best]) < 30.0 && work->unk03C < work->unk040 + 90)) {
                        work->unk038 = 0;
                        work->unk03C = work->unk040 = 1;
                    } else if (work->unk03C > work->unk040 && work->unk038 == 4) {
                        work->unk038 = 5;
                        work->unk03C = 0;
                        work->unk040 = rand8() % 40 + 100;
                        work->unk048 = (work->unk048 < 0.0f) ? 1 : -1;
                    }
                }
                break;
            case 3: {
                s32 pressTbl[2][4] = { { 15, 15, 10, 7 }, { 20, 20, 15, 10 } };

                work->unk03C++;
                if (work->unk03C == 1) {
                    btn = btnDown = 256;
                } else if (work->unk03C < pressTbl[0][work->unk014]) {
                    btn = 256;
                } else if (work->unk03C == pressTbl[1][work->unk014]) {
                    btn = btnDown = 256;
                }
                if (work->unk03C > pressTbl[1][work->unk014] && player->mode == 0) {
                    work->unk03C = 0;
                    switch (work->unk014) {
                    case 0:
                        work->unk038 = 4;
                        work->unk048 = 0.01 * ((rand8() % 2) * 2 - 1);
                        work->unk040 = 120;
                        break;
                    case 1:
                        work->unk038 = 5;
                        work->unk048 = (rand8() % 2) * 2 - 1;
                        work->unk040 = 120;
                        break;
                    case 2:
                        work->unk038 = rand8() % 2 + 4;
                        work->unk048 = (rand8() % 2) * 2 - 1;
                        work->unk040 = (work->unk038 == 4) ? rand8() % 30 : rand8() % 40 + 40;
                        break;
                    case 3:
                        work->unk038 = (rand8() % 4 == 0) + 4;
                        work->unk048 = ((rand8() % 2) ? 1.0 : 0.01) * ((rand8() % 2) * 2 - 1);
                        work->unk040 = (work->unk038 == 4) ? rand8() % 25 + 15 : rand8() % 65 + 35;
                        break;
                    }
                }
                break;
            }
            }
        }
        if (player->mode != 0 || model->motIdShift != -1) {
            speed = 0.0f;
        }
        cur = lbl_1_bss_5C8.unk00C;
        lbl_1_bss_5C8.unk00C += ((cur < speed) ? 1 : -1) * ((fabs(speed) < fabs(cur)) ? 1.0f / accel : 1.5f / accel);
        if ((cur <= speed && lbl_1_bss_5C8.unk00C > speed) || (cur >= speed && lbl_1_bss_5C8.unk00C < speed)) {
            lbl_1_bss_5C8.unk00C = speed;
        }
        lbl_1_bss_5C8.unk01C[lbl_1_bss_5C8.unk1FC] = lbl_1_bss_5C8.unk008;
        lbl_1_bss_5C8.unk10C[lbl_1_bss_5C8.unk1FC] = lbl_1_bss_5C8.unk00C;
        lbl_1_bss_5C8.unk1FC++;
        lbl_1_bss_5C8.unk1FC %= 60;
        lbl_1_bss_5C8.unk008 += 360.0f * lbl_1_bss_5C8.unk00C / 360.0f;
        lbl_1_bss_5C8.unk008 += (lbl_1_bss_5C8.unk008 < -180.0f) ? 360 : ((lbl_1_bss_5C8.unk008 >= 180.0f) ? -360 : 0);
        Hu3DModelRotSet(lbl_1_bss_1B4->mdlId[6], 0.0f, lbl_1_bss_5C8.unk008, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_1B4->mdlId[8], 0.0f, lbl_1_bss_5C8.unk008, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[7], 20.0f + 20.0f * lbl_1_bss_5C8.unk00C);
        if (lbl_1_bss_10 == 0) {
            if ((speed < 0.0f && lbl_1_bss_C >= 0.0f) || (speed > 0.0f && lbl_1_bss_C <= 0.0f)) {
                if (lbl_1_bss_1D0[7].unk000 < 3) {
                    lbl_1_bss_1D0[7].unk004[lbl_1_bss_1D0[7].unk000] = 0.0f;
                    lbl_1_bss_1D0[7].unk000++;
                }
                lbl_1_bss_10 = 6;
            }
        }
        lbl_1_bss_10 -= lbl_1_bss_10 > 0;
        lbl_1_bss_C = speed;
        stkX = 0;
        stkY = 0;
    } else {
        state = work->unk01C;
        inAir = !(player->actor->colGroundAttr & 0x407F);
        dist = sqrtf(pos.x * pos.x + pos.z * pos.z);
        if (lbl_1_bss_1A0 == 2 || lbl_1_bss_1A0 == 3) {
            if (lbl_1_bss_1A0 == 2) {
                if (lbl_1_bss_0 < 215) {
                    player->actor->pos.x = ((work->unk000 != 1 ? 0 : 0) + 540) * HuSin(0.5 * (work->unk000 == 1) + (work->unk000 * 120 + 60));
                    player->actor->pos.z = ((work->unk000 != 1 ? 0 : 0) + 540) * HuCos(0.5 * (work->unk000 == 1) + (work->unk000 * 120 + 60)) - 25.0;
                }
                if (lbl_1_bss_0 == 225) {
                    btn = btnDown = 256;
                } else if (lbl_1_bss_0 > 225 && lbl_1_bss_0 <= 240) {
                    btn = 256;
                }
            }
            if (lbl_1_bss_1A0 == 2 && ((lbl_1_bss_0 >= 220 && lbl_1_bss_0 <= 225) || inAir)) {
                stkX = 55.0f * (-pos.x / dist);
                stkY = -55.0f * (-pos.z / dist);
            }
        } else if (lbl_1_bss_1A0 == 5 && work->unk01C == 2 && work->unk010 == -1) {
            s32 delayTbl[2][4] = { { 23, 18, 12, 10 }, { 15, 5, 4, 4 } };

            ring = (lbl_1_bss_5C8.unk1FC - delayTbl[lbl_1_bss_5C8.unk018 > 0 && lbl_1_bss_5C8.unk018 < 190][work->unk014] + 60) % 60;
            ringAngle = lbl_1_bss_5C8.unk01C[ring];
            ringSpeed = lbl_1_bss_5C8.unk10C[ring];
            myAngle = HuAtan(pos.x, pos.z);
            myDist = sqrtf(pos.x * pos.x + pos.z * pos.z);
            minDiff = 10000.0f;
            for (i = -6; i <= 6; i++) {
                minDiff = (fabs(minDiff) > fabs(myAngle - (ringAngle + i * 120))) ? myAngle - (ringAngle + i * 120) : minDiff;
            }
            radius = (lbl_1_bss_5C8.unk018 == 0) ? 360.0f
                   : (lbl_1_bss_5C8.unk018 < 70)  ? 360.0f + 80.0f * (lbl_1_bss_5C8.unk018 / 70.0f)
                   : (lbl_1_bss_5C8.unk018 < 100) ? 440.0f
                   : (lbl_1_bss_5C8.unk018 < 160) ? 210.0f
                   : (lbl_1_bss_5C8.unk018 < 190) ? 210.0f + 150.0f * ((lbl_1_bss_5C8.unk018 - 160) / 30.0f)
                                                  : 360.0f;
            btnDown = (lbl_1_bss_5C8.unk018 == 102) ? 256 : 0;
            btn = (lbl_1_bss_5C8.unk018 >= 102 && lbl_1_bss_5C8.unk018 <= 110) ? 256 : 0;
            work->unk03C++;
            switch (work->unk038) {
            case 0:
                work->unk04C = myAngle;
                if ((fabs(ringSpeed) > 0.3 && minDiff * ringSpeed > 0.0f && fabs(minDiff) < 45.0)
                    || (fabs(minDiff) < 35.0 && (minDiff * ringSpeed > 0.0f || fabs(ringSpeed) < 0.5))) {
                    work->unk038 = (minDiff < 0.0f) ? -1 : 1;
                    work->unk03C = 0;
                }
                break;
            case -1:
            case 1:
                if (work->unk03C >= work->unk040
                    && ((fabs(ringSpeed) < 0.3 && fabs(minDiff) > 45.0) || (minDiff * work->unk038 < 0.0f && fabs(minDiff) < 35.0))) {
                    work->unk038 = 0;
                    work->unk03C = 0;
                } else {
                    work->unk04C = myAngle + work->unk038 * 5;
                }
                if (work->unk03C >= work->unk040) {
                    switch (work->unk014) {
                    case 0:
                        work->unk040 = (rand8() % 3) * 5 + 5;
                        break;
                    case 1: {
                        s32 waitTbl1[5] = { 0, 2, 6, 8, 10 };

                        work->unk040 = waitTbl1[rand8() % 5];
                        break;
                    }
                    case 2: {
                        s32 waitTbl2[5] = { 0, 0, 0, 5, 10 };

                        work->unk040 = waitTbl2[rand8() % 5];
                        break;
                    }
                    case 3: {
                        s32 waitTbl3[2][5] = { { 0, 0, 1, 2, 7 }, { 0, 0, 1, 2, 10 } };

                        work->unk040 = waitTbl3[lbl_1_bss_5C8.unk018 > 0 && lbl_1_bss_5C8.unk018 < 190][rand8() % 5];
                        break;
                    }
                    }
                    work->unk03C = 0;
                }
                break;
            }
            if (lbl_1_bss_5C8.unk018 == 0 && lbl_1_bss_5C8.unk018 < 190) {
                work->unk050 = radius;
            }
            work->unk050 = radius;
            dx = work->unk050 * HuSin(work->unk04C) - pos.x;
            dz = work->unk050 * HuCos(work->unk04C) - pos.z;
            mag = 5.6f * sqrtf(dx * dx + dz * dz);
            stkXf = 5.6f * dx * ((mag < 120.0f) ? 1.0f : 64.0f * (1.0f / mag));
            stkYf = -5.6f * dz * ((mag < 120.0f) ? 1.0f : 64.0f * (1.0f / mag));
            stkX = stkXf;
            stkY = stkYf;
        }
        if ((lbl_1_bss_1A0 == 5 || lbl_1_bss_1A0 == 6) && work->unk01C == 2) {
            if (dist > 700.0f && (!inAir || pos.y < 0.0f)) {
                work->unk01C = 3;
            } else if (lbl_1_bss_1A0 == 5 && lbl_1_bss_5C8.unk018 >= 40 && lbl_1_bss_5C8.unk018 < 200
                       && (player->actor->colGroundAttr & 0x407F) != 0) {
                s32 innerTbl[20] = { 40, 40, 74, 75, 108, 161, 186, 229, 278, 333, 374, 431, 470, 521, 565, 613, 643, 700, 700, 700 };
                s32 outerTbl[20] = { 104, 120, 126, 155, 188, 227, 266, 309, 358, 413, 462, 511, 550, 601, 645, 697, 750, 800, 800, 800 };

                t = lbl_1_bss_5C8.unk018 - 30;
                lo = (1.0f - (t % 10) / 10.0f) * innerTbl[t / 10] + ((t % 10) / 10.0f) * innerTbl[t / 10 + 1];
                hi = (1.0f - (t % 10) / 10.0f) * outerTbl[t / 10] + ((t % 10) / 10.0f) * outerTbl[t / 10 + 1];
                if (lo - 30.0f <= dist && dist <= 30.0f + hi) {
                    work->unk01C = 3;
                }
            }
            if (lbl_1_bss_1A0 == 5) {
                for (i = 0; i < 30; i++) {
                    if (lbl_1_bss_280[i].unk018 != 0) {
                        pdx = pos.x - lbl_1_bss_280[i].unk000.x;
                        pdy = pos.y - lbl_1_bss_280[i].unk000.y;
                        pdz = pos.z - lbl_1_bss_280[i].unk000.z;
                        if (pdx * pdx + pdz * pdz < 9025.0f) {
                            work->unk01C = 3;
                        }
                    }
                }
            }
        }
        if (work->unk01C == 3) {
            stkX = stkY = btn = btnDown = 0;
            if (state == 2) {
                MgPlayerModeSet(player, 11);
                MgPlayerPauseOn(player);
                omVibrate(work->unk004, 48, 1, 0);
                CharFXPlay(work->unk00C, 505);
                work->unk034 = 1.0f;
            } else {
                pos.x = obj->trans.x;
                pos.y = obj->trans.y;
                pos.z = obj->trans.z;
            }
            dist2 = sqrtf(pos.x * pos.x + pos.z * pos.z);
            if (dist2 > 1800.0f) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
            CharMotionShiftSet(player->charNo, player->omObj->mtnId[11], 1.0f, 0.0f, 0x40000001);
            if (0.0f == dist2) {
                nx = nz = 0.0f;
            } else {
                nx = pos.x / dist2;
                nz = pos.z / dist2;
            }
            pos.x += 16.0f * nx;
            pos.z += 16.0f * nz;
            pos.y += 50.0f * work->unk034;
            work->unk034 -= 0.04f;
            obj->rot.y = HuAtan(nx, nz);
            omSetTra(obj, pos.x, pos.y, pos.z);
        }
    }
    if ((lbl_1_bss_1A0 == 8 || lbl_1_bss_1A0 == 9) && lbl_1_data_9C[0] == 0 && work->unk000 == 0) {
        model2 = &Hu3DData[obj->mdlId[1]];
        Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_1B8[1]->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_1B8[2]->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_1B8[3]->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(obj->mdlId[1], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(obj->mdlId[1], obj->trans.x, obj->trans.y, obj->trans.z + ((work->unk008 == 3) ? -30 : ((work->unk008 == 4) ? -30 : 0)));
        if (model2->motId != obj->mtnId[2]) {
            Hu3DMotionSet(obj->mdlId[1], obj->mtnId[2]);
            Hu3DModelAttrReset(obj->mdlId[1], 0x40000002);
        } else if ((s32)model2->motWork.time - 1 == lbl_1_data_D0[work->unk00C]) {
            CharFXPlay(work->unk00C, 506);
        }
    } else if (lbl_1_bss_1A0 == 8 && lbl_1_data_9C[0] > 0 && work->unk000 > 0) {
        MgPlayerModeSet(player, 10);
    } else if (lbl_1_bss_1A0 == 8 && lbl_1_data_9C[0] == 1 && work->unk000 == 0) {
        MgPlayerModeSet(player, 12);
    }
    MgPlayerPadSet(player, stkX, stkY, btnDown | btnDownMask, btn | btnMask);
    HuPadBtnRep[player->padNo] &= 0x1010;
    HuPadBtnRep[player->padNo] |= btnDown | btnDownMask;
    if (work->unk000 == 0) {
        s32 ofsTbl[3][10] = {
            { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            { 0, 0, -15, -30, 0, -15, -30, -10, 0, -20 },
            { 0, 0, 0, -30, 0, 0, 0, 0, 0, 0 },
        };

        ofs = 0.0f;
        model3 = &Hu3DData[obj->mdlId[0]];
        if (lbl_1_bss_1A0 == 2 && lbl_1_bss_0 <= 68) {
            ofs = ofsTbl[0][work->unk008];
        } else {
            for (i = 0; i < 2; i++) {
                j = (i == 0) ? model3->motId : model3->motIdShift;
                if (j == -1) {
                    kind[i] = -1;
                } else if (j == player->omObj->mtnId[11]) {
                    kind[i] = 0;
                } else if (j == player->omObj->mtnId[10] || j == player->omObj->mtnId[12]) {
                    kind[i] = 2;
                } else {
                    kind[i] = 1;
                }
            }
            ofs = ofsTbl[kind[0]][work->unk008];
            if (kind[1] != -1) {
                blend = model3->motOvlWork.start / model3->motOvlWork.end;
                ofs = ofs * (1.0f - blend) + blend * ofsTbl[kind[1]][work->unk008];
            }
        }
        player->actor->pos.z = ofs;
    }
}

/* 113 insns */
float fn_1_41F8(float t, float accel, float flat, float decel)
{
    float total;

    total = decel / 2.0f + (accel / 2.0f + flat);
    return (t < accel)
               ? (1.0f + t) / 2.0f * t / accel / total
               : (t < accel + flat)
                     ? (1.0f + accel) / 2.0f * accel / accel / total + (t - accel) / total
                     : (t < decel + (accel + flat) - 1.0f)
                           ? 1.0f - (1.0f + (decel + (accel + flat) - t - 1.0f)) / 2.0f
                                        * (decel + (accel + flat) - 1.0f - t - 1.0f) / (decel - 1.0f) / total
                           : 1.0f;
}

/* 1763 insns */
void fn_1_43BC(OMOBJ *obj)
{
    float angle;
    float shake;
    float blend;
    float blendInv;
    s32 i;
    s32 j;
    HU3DMODEL *model;
    COL_ATTRPARAM param;
    M520_PLAYER *players[4];


    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_1B8[i]->data;
    }
    lbl_1_bss_1A0 = MgSeqModeGet();
    lbl_1_bss_0 = MgSeqFrameNoGet();
    lbl_1_bss_4[0]++;
    if (lbl_1_bss_164 == 0) {
        Hu3DModelAttrSet(lbl_1_bss_1B4->mdlId[21], HU3D_ATTR_DISPOFF);
    }
    if ((lbl_1_bss_1A0 == 2 && lbl_1_bss_0 >= 130) || lbl_1_bss_1A0 == 3) {
        lbl_1_bss_14++;
        blend = fn_1_41F8(lbl_1_bss_14, 16.0f, 32.0f, 16.0f);
        blendInv = 1.0f - blend;
        CZoom = 1425.0f * blendInv + 4575.0f * blend;
        Center.y = 505.0f * blendInv + -120.0f * blend;
        CRot.x = -35.0f * blendInv + -70.0f * blend;
    }
    if (lbl_1_bss_1A0 == 3 && lbl_1_bss_0 > 47) {
        shake = 62 - lbl_1_bss_0;
        if (shake >= 0.0f) {
            shake *= -(((s32)shake % 2) * 2 - 1) / 15.0f;
            Center.y = -120.0 + 6.0f * shake * cos(1.2217304763960306);
            Center.z = 6.0f * shake * -sin(1.2217304763960306);
        }
    }
    if (lbl_1_bss_1A0 == 8 && lbl_1_data_9C[0] == 0) {
        float rate = 0.9f;
        float rateInv = 1.0f - rate;
        float zoomY[10] = { 480.0f, 530.0f, 530.0f, 480.0f, 480.0f, 530.0f, 550.0f, 440.0f, 480.0f, 480.0f };
        float rotX[10] = { -40.0f, -34.0f, -27.0f, -40.0f, -38.0f, -27.0f, -40.0f, -40.0f, -30.0f, -40.0f };

        CZoom *= rate;
        CZoom += 900.0f * rateInv;
        Center.y *= rate;
        Center.y += rateInv * (zoomY[players[0]->unk008] - 140.0f);
        CRot.x *= rate;
        CRot.x += rateInv * rotX[players[0]->unk008];
    }
    if (lbl_1_bss_1A0 == 8 && lbl_1_data_9C[0] == 1) {
        float rate2 = 0.9f;
        float rate2Inv = 1.0f - rate2;

        CZoom *= rate2;
        CZoom += 3825.0f * rate2Inv;
        Center.y *= rate2;
        Center.y += -95.0f * rate2Inv;
        CRot.x *= rate2;
        CRot.x += -51.0f * rate2Inv;
    }
    MgActorColAttrParamGet(&param, 2);
    param.yDeviate = (lbl_1_bss_1A0 == 5) ? 0.6666667f : 0.0f;
    MgActorColAttrParamSet(&param, 2);
    lbl_1_bss_5C8.unk010++;
    lbl_1_bss_5C8.unk018 += (lbl_1_bss_5C8.unk018 > 0);
    if (lbl_1_bss_5C8.unk018 >= 480 && lbl_1_bss_1A0 == 5 && lbl_1_bss_1D0[4].unk000 < 3) {
        lbl_1_bss_1D0[4].unk004[lbl_1_bss_1D0[4].unk000] = 0.0f;
        lbl_1_bss_1D0[4].unk000++;
    }
    if (lbl_1_bss_5C8.unk018 == 2 && lbl_1_bss_1D0[4].unk010 != -1) {
        HuAudFXStop(lbl_1_bss_1D0[4].unk010);
    }
    lbl_1_bss_5C8.unk018 = (lbl_1_bss_5C8.unk018 >= 480) ? 0 : lbl_1_bss_5C8.unk018;
    lbl_1_bss_5C8.unk014 += (lbl_1_bss_5C8.unk014 > 0);
    lbl_1_bss_5C8.unk014 = (lbl_1_bss_5C8.unk014 >= 120) ? 0 : lbl_1_bss_5C8.unk014;
    if (lbl_1_bss_1A0 > 5) {
        lbl_1_bss_5C8.unk000 -= 1.5f;
        lbl_1_bss_5C8.unk000 = (lbl_1_bss_5C8.unk000 < -190.0f) ? -190.0f : lbl_1_bss_5C8.unk000;
    } else {
        lbl_1_bss_5C8.unk000 = (lbl_1_bss_5C8.unk014 > 120) ? 0.0f : lbl_1_bss_5C8.unk014 / 120.0f;
        lbl_1_bss_5C8.unk000 = -50.0 + ((lbl_1_bss_5C8.unk014 == lbl_1_bss_5C8.unk018) ? -75 : -60)
            * sin(M_PI * (180.0 * (0.5 * lbl_1_bss_5C8.unk000 + 0.5 * (1.0f - (1.0f - lbl_1_bss_5C8.unk000) * (1.0f - lbl_1_bss_5C8.unk000)))) / 180.0);
        angle = 135.0f - (lbl_1_bss_5C8.unk000 - -50.0f) * ((lbl_1_bss_5C8.unk014 == lbl_1_bss_5C8.unk018) ? 1.0f : 0.6666667f);
        angle += -90.0f * ((lbl_1_bss_5C8.unk018 <= 80) ? 0.0f
                    : (lbl_1_bss_5C8.unk018 <= 120) ? (lbl_1_bss_5C8.unk018 - 80) / 40.0f
                    : (lbl_1_bss_5C8.unk018 <= 240) ? 1.0f
                    : (lbl_1_bss_5C8.unk018 <= 480) ? 1.0f - (lbl_1_bss_5C8.unk018 - 240) / 240.0f
                    : 0.0f);
        angle += 45.0f;
        angle = (angle > 180.0f) ? 180.0f : angle;
    }
    Hu3DModelPosSet(lbl_1_bss_1B4->mdlId[6], 0.0f, 500.0f + lbl_1_bss_5C8.unk000, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_1B4->mdlId[8], 0.0f, 500.0f + lbl_1_bss_5C8.unk000, 0.0f);
    Hu3DModelPosSet(lbl_1_bss_1B4->mdlId[7], 0.0f, 500.0f + lbl_1_bss_5C8.unk000, 0.0f);
    for (i = 0; i < 3; i++) {
        Hu3DModelAttrSet(lbl_1_bss_1B4->mdlId[i + 11], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(lbl_1_bss_1B4->mdlId[i + 11], 0.0f, angle, 0.0f);
    }
    if (lbl_1_bss_5C8.unk018 == 0) {
        Hu3DModelAttrReset(lbl_1_bss_1B4->mdlId[11], HU3D_ATTR_DISPOFF);
    } else if (lbl_1_bss_5C8.unk018 <= 180) {
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[12], lbl_1_bss_5C8.unk018);
        Hu3DModelAttrReset(lbl_1_bss_1B4->mdlId[12], HU3D_ATTR_DISPOFF);
    } else if (lbl_1_bss_5C8.unk018 <= 480) {
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[11], 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[13], lbl_1_bss_5C8.unk018 - 180);
        Hu3DModelAttrReset(lbl_1_bss_1B4->mdlId[13], HU3D_ATTR_DISPOFF);
    }
    if (lbl_1_bss_5C8.unk018 == 30 && lbl_1_bss_1D0[0].unk000 < 3) {
        lbl_1_bss_1D0[0].unk004[lbl_1_bss_1D0[0].unk000] = 0.0f;
        lbl_1_bss_1D0[0].unk000++;
    }
    if (lbl_1_bss_5C8.unk018 == 5) {
        Hu3DModelAttrReset(lbl_1_bss_1B4->mdlId[10], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[10], 0.0f);
    }
    if (lbl_1_bss_5C8.unk018 == 85) {
        Hu3DModelAttrSet(lbl_1_bss_1B4->mdlId[10], HU3D_ATTR_DISPOFF);
    }
    if (lbl_1_bss_5C8.unk018 == 30) {
        Hu3DModelAttrReset(lbl_1_bss_1B4->mdlId[9], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_1B4->mdlId[9], 0.0f);
    }
    if (lbl_1_bss_5C8.unk018 == 210) {
        Hu3DModelAttrSet(lbl_1_bss_1B4->mdlId[9], HU3D_ATTR_DISPOFF);
    }
    if (lbl_1_bss_1A0 > 5) {
        model = &Hu3DData[lbl_1_bss_1B4->mdlId[9]];
        model->pos.y -= 20.0f;
        Hu3DModelAttrSet(obj->mdlId[lbl_1_bss_1B4->mdlId[9]], HU3D_MOTATTR_PAUSE);
    }
    if (lbl_1_bss_1A0 == 3 && lbl_1_bss_0 == 46) {
        if (lbl_1_bss_1D0[1].unk000 < 3) {
            lbl_1_bss_1D0[1].unk004[lbl_1_bss_1D0[1].unk000] = 0.0f;
            lbl_1_bss_1D0[1].unk000++;
        }
        if (lbl_1_bss_1D0[6].unk000 < 3) {
            lbl_1_bss_1D0[6].unk004[lbl_1_bss_1D0[6].unk000] = 0.0f;
            lbl_1_bss_1D0[6].unk000++;
        }
    }
    if (lbl_1_bss_1A0 == 5 || (lbl_1_bss_1A0 == 3 && lbl_1_bss_0 > 45)) {
        if (lbl_1_bss_5C8.unk010 % 32 == 1 || lbl_1_bss_5C8.unk010 % 32 == 7 || lbl_1_bss_5C8.unk010 % 32 == 11
            || lbl_1_bss_5C8.unk010 % 32 == 17 || lbl_1_bss_5C8.unk010 % 32 == 21 || lbl_1_bss_5C8.unk010 % 32 == 27) {
            for (i = 0; i < 3; i++) {
                float ringAngle = lbl_1_bss_5C8.unk008 + (i * 360) / 3;
                for (j = 0; j < 30; j++) {
                    if (lbl_1_bss_280[j].unk018 == 0) {
                        break;
                    }
                }
                if (j == 30) {
                    break;
                }
                lbl_1_bss_280[j].unk018 = 1;
                lbl_1_bss_280[j].unk000.x = 175.0 * sin(M_PI * ringAngle / 180.0);
                lbl_1_bss_280[j].unk000.y = 400.0f + lbl_1_bss_5C8.unk000;
                lbl_1_bss_280[j].unk000.z = 200.0 * cos(M_PI * ringAngle / 180.0);
                lbl_1_bss_280[j].unk00C.x = 575.0 * sin(M_PI * ringAngle / 180.0) / 32.0;
                lbl_1_bss_280[j].unk00C.y = -4.285714f;
                lbl_1_bss_280[j].unk00C.z = 575.0 * cos(M_PI * ringAngle / 180.0) / 32.0;
            }
        }
    }
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_280[i].unk018 != 0) {
            lbl_1_bss_280[i].unk018++;
            lbl_1_bss_280[i].unk000.x += lbl_1_bss_280[i].unk00C.x;
            lbl_1_bss_280[i].unk000.y += lbl_1_bss_280[i].unk00C.y;
            lbl_1_bss_280[i].unk000.z += lbl_1_bss_280[i].unk00C.z;
            if (lbl_1_bss_280[i].unk018 == 33) {
                lbl_1_bss_280[i].unk018 = 0;
            }
        }
    }
    for (i = 0; i < 2; i++) {
        if (lbl_1_bss_270[i].unk000 == 0) {
            lbl_1_bss_270[i].unk004--;
            if (lbl_1_bss_270[i].unk004 <= 0) {
                lbl_1_bss_270[i].unk000 = 1;
                lbl_1_bss_270[i].unk004 = 0;
                Hu3DMotionTimeSet(obj->mdlId[i + 14], 0.0f);
                Hu3DModelAttrReset(obj->mdlId[i + 14], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(obj->mdlId[i + 16], 0.0f);
                Hu3DModelAttrReset(obj->mdlId[i + 16], HU3D_ATTR_DISPOFF);
                if (lbl_1_bss_1D0[(i == 0) ? 3 : 2].unk000 < 3) {
                    lbl_1_bss_1D0[(i == 0) ? 3 : 2].unk004[lbl_1_bss_1D0[(i == 0) ? 3 : 2].unk000] = 0.0f;
                    lbl_1_bss_1D0[(i == 0) ? 3 : 2].unk000++;
                }
            }
        } else {
            lbl_1_bss_270[i].unk004++;
            if (lbl_1_bss_270[i].unk004 >= Hu3DMotionMaxTimeGet(obj->mdlId[i + 14])) {
                lbl_1_bss_270[i].unk000 = 0;
                lbl_1_bss_270[i].unk004 = 60.0f * (rand8() / 255.0f);
                Hu3DModelAttrSet(obj->mdlId[i + 14], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(obj->mdlId[i + 16], HU3D_ATTR_DISPOFF);
            }
        }
    }
}

/* 1 insns */
void fn_1_5F48(s16 mode, s16 frameNo)
{
}

/* 1 insns */
void fn_1_5F4C(s16 mode, s16 frameNo)
{
}

/* 1 insns */
void fn_1_5F50(s16 mode, s16 frameNo)
{
}

/* 1 insns */
void fn_1_5F54(s16 mode, s16 frameNo)
{
}

/* 1 insns */
void fn_1_5F58(s16 mode, s16 frameNo)
{
}

/* 1 insns */
void fn_1_5F5C(s16 mode, s16 frameNo)
{
}

/* 12 insns */
void fn_1_5F60(s16 mode, s16 frameNo)
{
    if (frameNo >= 60) {
        MgSeqModeNext();
    }
}

/* 428 insns */
void fn_1_5F90(OMOBJ *obj)
{
    M520_PLAYER *work[4];
    HuVecF pos;
    s32 frame;
    s32 i;
    s32 seNo;
    s32 playerNo;

    frame = MgSeqFrameNoGet();
    lbl_1_bss_1A0 = MgSeqModeGet();
    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_1B8[i]->data;
    }
    MgActorExec();
    for (i = 0; i < 4; i++) {
        MgActorPosGet(lbl_1_bss_1A4[i]->actor, &pos);
        if (i <= 0 || work[i]->unk01C != 3) {
            lbl_1_bss_1B8[i]->trans.x = pos.x;
            lbl_1_bss_1B8[i]->trans.y = pos.y;
            lbl_1_bss_1B8[i]->trans.z = pos.z;
            lbl_1_bss_1B8[i]->rot.y = lbl_1_bss_1A4[i]->actor->rotY;
        }
        if (i == 0) {
            if (lbl_1_bss_1A0 == 2 && frame == 6) {
                Hu3DMotionShiftSet(lbl_1_bss_1B8[0]->mdlId[1], lbl_1_bss_1B8[0]->mtnId[1], 10.0f + 10.0f * lbl_1_bss_5C8.unk00C, 12.0f, 0x40000002);
            }
            if (lbl_1_bss_1A0 == 2 && frame <= 68) {
                Hu3DModelPosSet(lbl_1_bss_1B8[0]->mdlId[1], lbl_1_bss_1B8[0]->trans.x, lbl_1_bss_1B8[0]->trans.y, lbl_1_bss_1B8[0]->trans.z);
                Hu3DModelAttrReset(lbl_1_bss_1B8[0]->mdlId[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_1B8[0]->mdlId[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_1B8[2]->mdlId[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_1B8[3]->mdlId[0], HU3D_ATTR_DISPOFF);
            } else if (lbl_1_bss_1A0 == 2) {
                Hu3DModelAttrSet(lbl_1_bss_1B8[0]->mdlId[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1B8[0]->mdlId[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1B8[2]->mdlId[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1B8[3]->mdlId[0], HU3D_ATTR_DISPOFF);
            }
        }
    }
    for (i = 0; i < 8; i++) {
        s32 seTbl[8] = { 0x722, 0x723, 0x724, 0x725, 0x726, 0x727, 0x728, 0x729 };

        if (lbl_1_bss_1D0[i].unk000 > 3) {
            lbl_1_bss_1D0[i].unk000 = 3;
        }
        if (lbl_1_bss_1D0[i].unk000 > 0) {
            seNo = HuAudFXPlay(seTbl[i]);
            lbl_1_bss_1D0[i].unk010 = seNo;
            lbl_1_bss_1D0[i].unk000--;
        }
    }
    switch (lbl_1_bss_1A0) {
    case 1:
        if (!WipeCheckEnd()) {
            MgSeqModeNext();
        }
        break;
    case 2:
        if (frame == 10) {
            lbl_1_data_A0[0] = HuAudSStreamPlay(80);
        }
        break;
    case 5:
        if (work[1]->unk01C == 3 && work[2]->unk01C == 3 && work[3]->unk01C == 3) {
            lbl_1_data_9C[0] = 0;
            MgSeqModeNext();
        }
        break;
    case 6:
        if (frame == 1) {
            if (lbl_1_bss_1D0[1].unk010 != -1) {
                HuAudFXStop(lbl_1_bss_1D0[1].unk010);
            }
            if (lbl_1_data_A0[0] != -1) {
                HuAudSStreamFadeOut(lbl_1_data_A0[0], 100);
            }
        }
        if (work[1]->unk01C == 3 && work[2]->unk01C == 3 && work[3]->unk01C == 3) {
            lbl_1_data_9C[0] = 0;
            MgSeqWinnerSet(work[0]->unk00C, -1, -1, -1);
        } else {
            lbl_1_data_9C[0] = 1;
            MgSeqWinnerSet(work[1]->unk00C, work[2]->unk00C, work[3]->unk00C, -1);
        }
        break;
    case 7:
        if (frame == 10) {
            GWMgCoinBonusSet(work[lbl_1_data_9C[0]]->unk004, 10);
            if (lbl_1_data_9C[0] == 1) {
                GWMgCoinBonusSet(work[2]->unk004, 10);
                GWMgCoinBonusSet(work[3]->unk004, 10);
            }
        }
        if (frame >= 70) {
            MgSeqModeNext();
        }
        break;
    case 0:
    case 3:
    case 4:
    case 8:
    case 9:
    case 10:
    case 11:
        break;
    }
}

/* .data after jumptable_1_data_104 (0x104): defined after fn_1_5F90 so CodeWarrior emits the jumptable first */
/* 0x134 */ s32 lbl_1_data_134[1] = { 0x00000008 };
/* 0x138 */ s32 lbl_1_data_138[17] = { 0x00870075, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C0005, 0x008C0050, 0x008C0008, 0x008C000A, 0x008C0009, 0x008C000F, 0x008C0010, 0x008C0012, 0x008C0013, 0x008C0017, 0x008C0018, 0x00000000 };
/* 0x17C */ char lbl_1_data_17C[] = "******* M520 ObjectSetup *********\n";

/* 629 insns */
void fn_1_6640(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx lookAt;
    Mtx trans;
    HuVecF quad[4] = {
        { -150.0f, 150.0f, 0.0f },
        { 150.0f, 150.0f, 0.0f },
        { 150.0f, -150.0f, 0.0f },
        { -150.0f, -150.0f, 0.0f },
    };
    HuVecF corner[4];
    HU3DCAMERA *cam;
    s32 i;
    s32 alpha;
    s32 idx;
    float u0;
    float v0;
    float u1;
    float v1;

    cam = Hu3DCamera;
    C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
    PSMTXTranspose(lookAt, trans);
    PSMTXMultVecArray(trans, quad, corner, 4);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    HuSprTexLoad(espanim[esprite[lbl_1_bss_17C[0]].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    for (i = 0; i < 30; i++) {
        if (lbl_1_bss_280[i].unk018 == 0) {
            continue;
        }
        idx = (lbl_1_bss_280[i].unk018 < 3) ? 0
            : (lbl_1_bss_280[i].unk018 < 6) ? 1
            : (lbl_1_bss_280[i].unk018 < 9) ? 2
            : (lbl_1_bss_280[i].unk018 < 12) ? 3
            : (lbl_1_bss_280[i].unk018 < 15) ? 4
            : (lbl_1_bss_280[i].unk018 < 19) ? 5
            : (lbl_1_bss_280[i].unk018 < 23) ? 6
            : (lbl_1_bss_280[i].unk018 < 27) ? 7
            : 8;
        idx = (idx > 8) ? 8 : idx;
        u0 = (idx % 5) / 5.0f;
        v0 = (idx / 5) / 2.0f;
        u1 = 0.2f + u0;
        v1 = 0.5f + v0;
        u0 += 0.003125f;
        v0 += 0.0078125f;
        u1 -= 0.003125f;
        v1 -= 0.0078125f;
        alpha = 240;
        alpha = (lbl_1_bss_280[i].unk018 < 4) ? (alpha * lbl_1_bss_280[i].unk018) / 4
            : (lbl_1_bss_280[i].unk018 < 27) ? alpha
            : (lbl_1_bss_280[i].unk018 < 32) ? alpha - (alpha * (lbl_1_bss_280[i].unk018 - 27)) / 5
            : 0;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(corner[0].x + lbl_1_bss_280[i].unk000.x, corner[0].y + lbl_1_bss_280[i].unk000.y, corner[0].z + lbl_1_bss_280[i].unk000.z);
        GXColor4u8(255, 255, 255, alpha);
        GXTexCoord2f32(u0, v0);
        GXPosition3f32(corner[1].x + lbl_1_bss_280[i].unk000.x, corner[1].y + lbl_1_bss_280[i].unk000.y, corner[1].z + lbl_1_bss_280[i].unk000.z);
        GXColor4u8(255, 255, 255, alpha);
        GXTexCoord2f32(u1, v0);
        GXPosition3f32(corner[2].x + lbl_1_bss_280[i].unk000.x, corner[2].y + lbl_1_bss_280[i].unk000.y, corner[2].z + lbl_1_bss_280[i].unk000.z);
        GXColor4u8(255, 255, 255, alpha);
        GXTexCoord2f32(u1, v1);
        GXPosition3f32(corner[3].x + lbl_1_bss_280[i].unk000.x, corner[3].y + lbl_1_bss_280[i].unk000.y, corner[3].z + lbl_1_bss_280[i].unk000.z);
        GXColor4u8(255, 255, 255, alpha);
        GXTexCoord2f32(u0, v1);
    }
    GXPixModeSync();
}

/* 519 insns */
void fn_1_7014(HU3DMODEL *modelP, Mtx *mtx)
{
    float unusedF0;
    float th;
    float tw;
    float scroll;
    float period;
    float unusedF1;
    float sx;
    float sy;
    s32 unused0;
    s32 unused1;
    s32 unused2;
    s32 unused3;
    s32 unused4;
    s32 unused5;

    sx = lbl_1_data_EC[0] / 32.0f;
    sy = lbl_1_data_EC[1] / 32.0f;
    th = lbl_1_data_EC[2] / 32.0f;
    tw = lbl_1_data_EC[3] / 32.0f;
    period = lbl_1_data_EC[4];
    scroll = (lbl_1_bss_4[0] % (s32)period) / period;
    C_MTXOrtho(lbl_1_bss_B8, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(lbl_1_bss_B8, GX_ORTHOGRAPHIC);
    PSMTXIdentity(lbl_1_bss_E8);
    GXLoadPosMtxImm(lbl_1_bss_E8, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetCopyFilter(GX_FALSE, RenderMode->sample_pattern, GX_FALSE, RenderMode->vfilter);
    GXSetTexCopySrc(0, 0, 640, 480);
    GXSetTexCopyDst(640, 480, GX_TF_RGBA8, GX_FALSE);
    GXCopyTex(lbl_1_bss_168, GX_FALSE);
    DCFlushRange(lbl_1_bss_168, lbl_1_bss_16C[0]);
    GXPixModeSync();
    GXSetCopyFilter(RenderMode->aa, RenderMode->sample_pattern, GX_TRUE, RenderMode->vfilter);
    GXInitTexObj(&lbl_1_bss_118[0], lbl_1_bss_168, 640, 480, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXLoadTexObj(&lbl_1_bss_118[0], GX_TEXMAP0);
    GXSetVtxDesc(GX_VA_TEX1, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX1, GX_TEX_ST, GX_F32, 0);
    GXInitTexObj(&lbl_1_bss_118[1], lbl_1_bss_160, 32, 32, GX_TF_IA8, GX_REPEAT, GX_REPEAT, GX_FALSE);
    GXLoadTexObj(&lbl_1_bss_118[1], GX_TEXMAP1);
    {
    float indMtx[2][3] = { { 0.0f, 0.0026666666f, 0.0f }, { 0.004f, 0.0f, 0.0f } };

    indMtx[0][1] *= sy;
    indMtx[1][0] *= sx;
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR0A0);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexMtx(GX_ITM_0, indMtx, 0);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2f32(0.0f, 0.0f);
    GXTexCoord2f32(0.0f / tw, 0.0f / th + scroll);
    GXPosition3f32(1.0f, 0.0f, 0.0f);
    GXTexCoord2f32(1.0f, 0.0f);
    GXTexCoord2f32(1.0f / tw, 0.0f / th + scroll);
    GXPosition3f32(1.0f, 1.0f, 0.0f);
    GXTexCoord2f32(1.0f, 1.0f);
    GXTexCoord2f32(1.0f / tw, 12.0f / th + scroll);
    GXPosition3f32(0.0f, 1.0f, 0.0f);
    GXTexCoord2f32(0.0f, 1.0f);
    GXTexCoord2f32(0.0f / tw, 12.0f / th + scroll);
    GXSetNumIndStages(0);
    GXSetTevDirect(GX_TEVSTAGE0);
    }
    /* Guess: the reference saves r26-r31 and f24-f31 but never touches r26-r31,
     * f26 or f31 -- the trace of code CodeWarrior eliminated. This dead block
     * reproduces the reservation (masked 24 -> 0); it emits nothing. */
    if (0) {
        unused0 = unused1 + 1;
        unused1 = unused2 + 1;
        unused2 = unused3 + 1;
        unused3 = unused4 + 1;
        unused4 = unused5 + 1;
        unused5 = unused0 + 1;
        unusedF0 = unusedF1 + unusedF0;
        unusedF1 = unusedF0;
    }
}

/* 426 insns */
void fn_1_7830(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 i;
    s32 a;
    s32 b;

    if (lbl_1_bss_164) {
        C_MTXOrtho(lbl_1_bss_18, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
        GXSetProjection(lbl_1_bss_18, GX_ORTHOGRAPHIC);
        PSMTXIdentity(lbl_1_bss_48.unk000);
        GXLoadPosMtxImm(lbl_1_bss_48.unk000, GX_PNMTX0);
        GXSetNumTevStages(1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 66);
        for (i = 0; i < 32; i++) {
            a = 128.0 + 127.0 * cos(M_PI * (i / 32.0f * 360.0f) / 180.0);
            b = 128.0 + 127.0 * cos(M_PI * (i / 32.0f * 360.0f * 2.0f) / 180.0);
            GXPosition3f32(0.0f, i / 480.0f, 0.0f);
            GXColor4u8(0, b, a, 255);
            GXPosition3f32(0.05f, i / 480.0f, 0.0f);
            GXColor4u8(0, b, a, 255);
        }
        GXPosition3f32(0.0f, i / 480.0f, 0.0f);
        GXColor4u8(0, b, a, 255);
        GXPosition3f32(0.05f, i / 480.0f, 0.0f);
        GXColor4u8(0, b, a, 255);
        GXSetCopyFilter(GX_FALSE, RenderMode->sample_pattern, GX_FALSE, RenderMode->vfilter);
        GXSetTexCopySrc(0, 0, 32, 32);
        GXSetTexCopyDst(32, 32, GX_CTF_GB8, GX_FALSE);
        GXCopyTex(lbl_1_bss_160, GX_FALSE);
        DCFlushRange(lbl_1_bss_160, lbl_1_bss_164);
        GXPixModeSync();
        GXSetCopyFilter(RenderMode->aa, RenderMode->sample_pattern, GX_TRUE, RenderMode->vfilter);
        lbl_1_bss_164 = 0;
    }
}

/* 656 insns */
void fn_1_7ED8(OMOBJ *obj)
{
    HU3DMODELID colMdl[3];
    void *works[4];
    s32 i;
    s32 no;

    for (i = 0; i < 4; i++) {
        works[i] = lbl_1_bss_1B8[i]->data;
    }
    no = 0;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0000);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    colMdl[0] = obj->mdlId[no];
    no = 5;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0005);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    colMdl[1] = obj->mdlId[no];
    no = 8;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E000C);
    Hu3DModelPosSet(obj->mdlId[no], 0.0f, 450.0f, 0.0f);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    colMdl[2] = obj->mdlId[no];
    MgActorColMapInit(colMdl, 3, 128);
    no = 1;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0001);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(obj->mdlId[no], 0.25f);
    no = 2;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0002);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 3;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0003);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 4;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0004);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 14;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0006);
    Hu3DModelLayerSet(obj->mdlId[no], 2);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 15;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0007);
    Hu3DModelLayerSet(obj->mdlId[no], 2);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 16;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0008);
    Hu3DModelLayerSet(obj->mdlId[no], 2);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 17;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E0009);
    Hu3DModelLayerSet(obj->mdlId[no], 2);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    no = 7;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E000A);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(obj->mdlId[no], 0.0f, 450.0f, 0.0f);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    no = 6;
    obj->mdlId[no] = Hu3DModelCreateData(0x4E000B);
    Hu3DModelLayerSet(obj->mdlId[no], 1);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(obj->mdlId[no], 0.0f, 450.0f, 0.0f);
    for (i = 0; i < 5; i++) {
        unsigned int tbl[5] = { 0x4E000D, 0x4E000E, 0x4E000F, 0x4E0010, 0x4E0011 };
        no = i + 9;
        obj->mdlId[no] = Hu3DModelCreateData(tbl[i]);
        Hu3DModelLayerSet(obj->mdlId[no], 1);
        if (i < 2) {
            Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(obj->mdlId[no], 540.0f);
        }
        if (i == 2) {
            Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
        }
    }
    no = 19;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_6640);
    Hu3DModelLayerSet(obj->mdlId[no], 4);
    no = 20;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_7014);
    Hu3DModelLayerSet(obj->mdlId[no], 5);
    no = 21;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_7830);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    lbl_1_bss_17C[0] = espEntry(0x4E0012, 0, 0);
    espDispOff(lbl_1_bss_17C[0]);
    memset(&lbl_1_bss_5C8, 0, sizeof(lbl_1_bss_5C8));
    lbl_1_bss_5C8.unk000 = -50.0f;
    lbl_1_bss_5C8.unk010 = 0;
    lbl_1_bss_5C8.unk008 = 0.0f;
    Hu3DModelRotSet(lbl_1_bss_1B4->mdlId[6], 0.0f, lbl_1_bss_5C8.unk008, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_1B4->mdlId[8], 0.0f, lbl_1_bss_5C8.unk008, 0.0f);
    memset(lbl_1_bss_280, 0, sizeof(lbl_1_bss_280));
    for (i = 0; i < 2; i++) {
        lbl_1_bss_270[i].unk000 = 1;
        lbl_1_bss_270[i].unk004 = (rand8() / 255.0f) * Hu3DMotionMaxTimeGet(obj->mdlId[i + 14]);
        Hu3DMotionTimeSet(obj->mdlId[i + 14], lbl_1_bss_270[i].unk004);
        Hu3DMotionTimeSet(obj->mdlId[i + 16], lbl_1_bss_270[i].unk004);
        Hu3DModelAttrSet(obj->mdlId[i + 14], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->mdlId[i + 16], HU3D_ATTR_DISPOFF);
    }
    {
    COL_ATTRPARAM param;
    MgActorColAttrParamGet(&param, 1);
    param.yDeviate = 0.0f;
    MgActorColAttrParamSet(&param, 1);
    MgActorColAttrParamGet(&param, 2);
    param.yDeviate = 0.0f;
    MgActorColAttrParamSet(&param, 2);
    }
    memset(lbl_1_bss_1D0, 0, sizeof(lbl_1_bss_1D0));
    for (i = 0; i < 8; i++) {
        lbl_1_bss_1D0[i].unk010 = -1;
    }
    obj->objFunc = fn_1_43BC;
}

/* 96 insns */
void *fn_1_8918(s16 charNo, u32 dataNum)
{
    u32 dirNum;
    s16 i;
    void *data;

    dirNum = dataNum & 0xFFFF0000;
    for (i = 0; i < CHARNO_MAX; i++) {
        if (dirNum == charDataDirTbl[i][4]) {
            break;
        }
    }
    if (i != CHARNO_MAX || dirNum == 0) {
        dataNum &= 0xFFFF;
        data = HuAR_ARAMtoMRAMFileRead(dataNum | charDataDirTbl[charNo][4], HU_MEMNUM_OVL, HEAP_MODEL);
        if (!data) {
            data = HuDataSelHeapReadNum(dataNum | charDataDirTbl[charNo][4], HU_MEMNUM_OVL, HEAP_MODEL);
        }
    } else {
        for (i = 0; i < CHARNO_MAX; i++) {
            if (dirNum == charDataDirTbl[i][5]) {
                break;
            }
        }
        if (i != CHARNO_MAX) {
            dataNum = (dataNum & 0xFFFF) | charDataDirTbl[charNo][5];
            data = HuDataReadNumHeapShortForce(dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
        } else {
            data = HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
        }
    }
    return data;
}

/* 882 insns */
void fn_1_8A98(OMOBJ *obj)
{
    MGACTOR_PARAM param;
    MGACTOR_COLMAP_POLY poly;
    s32 order[4] = { 0, 1, 2, 3 };
    HuVecF pos;
    unsigned int mdlDataNum;
    unsigned int motDataNum;
    M520_PLAYER *work;
    s32 num;
    s32 i;
    s32 j;

    num = 0;
    work = obj->data;
    memset(work, 0, sizeof(M520_PLAYER));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayerConf[j].grp) {
                order[num] = j;
                num++;
            }
        }
    }
    work->unk000 = obj->work[0];
    work->unk004 = order[work->unk000];
    if (work->unk004 == 4) {
        work->unk004 = work->unk000;
    }
    work->unk00C = GwPlayerConf[work->unk004].charNo;
    work->unk008 = (work->unk00C >= 9) ? 9 : work->unk00C;
    work->unk010 = (GwPlayerConf[work->unk004].type != 0) ? -1 : GwPlayerConf[work->unk004].padNo;
    work->unk014 = (work->unk010 != -1) ? 0 : GwPlayerConf[work->unk004].dif;
    work->unk01C = 2;
    work->unk034 = 1.0f;
    param.height = 150.0f;
    param.radius = 40.0f;
    param.param = work->unk000;
    param.type = 0;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = NULL;
    param.correctHook = NULL;
    lbl_1_bss_1A4[work->unk000] = MgPlayerCreate(work->unk004, &param, (work->unk000 == 0) ? 4 : 4, 1, 0x13, (work->unk000 == -1) ? (unsigned int *)lbl_1_data_138 : NULL);
    obj->mdlId[0] = lbl_1_bss_1A4[work->unk000]->actor->mdlId;
    CharEffectLayerSet(3);
    if (work->unk000 == 0) {
        lbl_1_bss_1A4[work->unk000]->actor->pos.x = 0.0f;
        lbl_1_bss_1A4[work->unk000]->actor->pos.y = 600.0f;
        lbl_1_bss_1A4[work->unk000]->actor->pos.z = 0.0f;
    } else {
        lbl_1_bss_1A4[work->unk000]->actor->pos.x = (((work->unk000 != 1) ? 0 : 0) + 540) * sin(M_PI * (work->unk000 * 120 + 60) / 180.0);
        lbl_1_bss_1A4[work->unk000]->actor->pos.y = 400.0f;
        lbl_1_bss_1A4[work->unk000]->actor->pos.z = (((work->unk000 != 1) ? 0 : 0) + 540) * cos(M_PI * (work->unk000 * 120 + 60) / 180.0) - 25.0;
    }
    MgPlayerVibrateCreate(lbl_1_bss_1A4[work->unk000]);
    pos = lbl_1_bss_1A4[work->unk000]->actor->pos;
    pos.y = -500.0f;
    if (MgActorColMapPolyGet(&lbl_1_bss_1A4[work->unk000]->actor->pos, &pos, 0xFFFF, &poly)) {
        poly.pos.y += 75.0f;
        MgActorPosUpdate((MGACTOR *)lbl_1_bss_1A4[work->unk000], &poly.pos); /* retail: passes the MGPLAYER as the MGACTOR */
        lbl_1_bss_1A4[work->unk000]->actor->pos.y = poly.pos.y;
    }
    Hu3DModelLayerSet(obj->mdlId[0], 1);
    Hu3DModelShadowSet(obj->mdlId[0]);
    Hu3DModelAmbSet(obj->mdlId[0], 1.0f, 0.5f, 0.5f);
    if (work->unk000 == 0) {
        mdlDataNum = charDataDirTbl[work->unk00C][0];
        obj->mdlId[1] = Hu3DModelCreateData(mdlDataNum);
        Hu3DModelLayerSet(obj->mdlId[1], 1);
        Hu3DModelShadowSet(obj->mdlId[1]);
        Hu3DModelAmbSet(obj->mdlId[1], 1.0f, 0.5f, 0.5f);
    }
    lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_KNOCKBACK + 3] = fn_1_A08;
    if (work->unk000 == 0) {
        motDataNum = 0x8C002F;
        obj->mtnId[0] = Hu3DJointMotion(obj->mdlId[1], fn_1_8918(work->unk00C, 0x8C0000));
        obj->mtnId[1] = Hu3DJointMotion(obj->mdlId[1], fn_1_8918(work->unk00C, 0x870075));
        obj->mtnId[2] = Hu3DJointMotion(obj->mdlId[1], fn_1_8918(work->unk00C, 0x8C002F));
        Hu3DMotionSet(obj->mdlId[1], obj->mtnId[0]);
    } else {
        lbl_1_bss_1A4[work->unk000]->omObj->mtnId[10] = CharMotionCreate(work->unk00C, (work->unk000 == 0) ? 0x8C002F : 0x8C0006);
    }
    lbl_1_bss_1A4[work->unk000]->omObj->mtnId[11] = CharMotionCreate(work->unk00C, (work->unk000 == 0) ? 0x870075 : 0x8C0015);
    if (work->unk000 == 0) {
        lbl_1_bss_1A4[work->unk000]->omObj->mtnId[12] = CharMotionCreate(work->unk00C, 0x8C0031);
        lbl_1_bss_15C = lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_WALK];
        lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_WALK] = fn_1_698;
        lbl_1_bss_158 = lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_HIPDROP];
        lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_HIPDROP] = fn_1_90C;
        lbl_1_bss_1A4[work->unk000]->modeFunc[MGPLAYER_MODE_SQUISH + 4] = fn_1_B04;
    }
    obj->objFunc = fn_1_B70;
}

/* 4 insns */
void fn_1_9860(OMOBJ *obj)
{
    obj->objFunc = fn_1_5F90;
}

/* 284 insns */
void ObjectSetup(void)
{
    OSReport(lbl_1_data_17C);
    lbl_1_bss_19C = MgActorObjectSetup();
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    CZoom = 5000.0f;
    Center.x = 0.0f;
    Center.y = 30.0f;
    Center.z = 0.0f;
    CRot.x = -70.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 1425.0f;
    Center.x = 0.0f;
    Center.y = 505.0f;
    Center.z = 0.0f;
    CRot.x = -35.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Hu3DLighInit();
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.0f, -1.0f, -0.5f };
        GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };

        lbl_1_bss_190[0] = Hu3DGLightCreateV(&lightPos, &lightDir, &color);
        Hu3DGLightStaticSet(lbl_1_bss_190[0], 1);
        Hu3DGLightInfinitytSet(lbl_1_bss_190[0]);
    }
    {
        HuVecF pos;
        HuVecF up;
        HuVecF target;

        pos.x = 0.0f;
        pos.y = 10000.0f;
        pos.z = 0.0f;
        up.x = 0.0f;
        up.y = 1.0f;
        up.z = 0.0f;
        target.x = 0.0f;
        target.y = 0.0f;
        target.z = -0.1f;
        Hu3DShadowCreate(8.5f, 5000.0f, 13000.0f);
        Hu3DShadowPosSet(&pos, &up, &target);
    }
    lbl_1_bss_198 = -1;
    lbl_1_data_9C[0] = -1;
    lbl_1_bss_16C[0] = GXGetTexBufferSize(640, 480, GX_TF_RGBA8, GX_FALSE, 0);
    lbl_1_bss_168 = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_16C[0], HU_MEMNUM_OVL);
    lbl_1_bss_164 = GXGetTexBufferSize(32, 32, GX_TF_IA8, GX_FALSE, 0);
    lbl_1_bss_160 = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_164, HU_MEMNUM_OVL);
    MgSeqCreate(&lbl_1_data_A8);
}

/* 78 insns */
void fn_1_9CE0(s16 mode, s16 frameNo)
{
    s32 i;
    OMOBJ *obj;

    lbl_1_bss_1B4 = omAddObjEx(lbl_1_bss_19C, 100, 22, 2, 1, fn_1_7ED8);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_1B8[i] = omAddObjEx(lbl_1_bss_19C, 102, 2, 3, 0, fn_1_8A98);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M520_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_1C8 = omAddObjEx(lbl_1_bss_19C, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_1CC = omAddObjEx(lbl_1_bss_19C, 103, 0, 0, -1, fn_1_9860);
    MgSeqModeNext();
}

/* 39 insns */
void fn_1_9E18(s16 mode, s16 frameNo)
{
    s32 i;
    M520_PLAYER *work;

    MgSeqModeNext();
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_1B8[i]->data;
    }
    if (lbl_1_bss_198 >= 0) {
        GameMesKill(lbl_1_bss_198);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_A4[0], 1);
}

