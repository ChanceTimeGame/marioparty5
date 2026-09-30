/*
 * m566dll (minigame #77) -- one translation unit, 15 functions / 14,730
 * instructions, in reference order.
 *
 * Its two largest functions, fn_1_48F8 (4,489) and fn_1_668 (4,260), are 59% of
 * the overlay and were each written as three regions.
 *
 * Two placement facts are load-bearing and must not be "tidied":
 *   - lbl_1_data_284 and lbl_1_data_29F are declared BELOW fn_1_48F8, because
 *     CodeWarrior appends a switch jumptable where the function compiles; as
 *     top-of-file globals they precede it and push jumptable_1_data_268 off its
 *     address.
 *   - the switch in fn_1_48F8 at 0x4FA8 needs explicit `case 0:` and `case 4:`
 *     break arms: the reference's binary-search chain is over {0,1,2,3,4}, and
 *     without them CodeWarrior emits a compare chain and no jumptable at all.
 */

/* --- CodeWarrior (matching build) only -------------------------------------
 * MSVC compiles this file as C and rejects `extern "C"` and the CodeWarrior
 * pragmas outright (C2059 at the `extern "C"` line). On the host, "math.h"
 * resolves to the ordinary header -- games/mp5/libc is only on cc.sh's include
 * path -- and supplies a real sqrtf and fabs, while humath.h supplies M_PI.
 * So the whole out-of-line-sqrtf construction below is guarded off for the PC
 * port, which needs none of it.
 *
 * This is the m515 lesson in mirror image: there, retyping made CodeWarrior
 * reject what MSVC had accepted. Compile a construct like this with BOTH
 * builds before believing it.
 * -------------------------------------------------------------------------- */

/* m566 is the only MP5 overlay whose reference emits sqrtf OUT OF LINE: a weak,
 * unmangled, 51-instruction symbol with 14 `bl sqrtf` call sites. libc/math.h's
 * sqrtf is `extern inline` over `static const double _half/_three` and this
 * toolchain always inlines it; the reference's copy has no local statics at all,
 * so it was never that one. Suppressing libc/math.h for this TU and supplying
 * the reference's own sqrtf reproduces it exactly (raw=0, `W sqrtf`, and no
 * stray `_half`/`_three` statics). libc/math.h is shared with every other
 * overlay and is deliberately NOT edited; this TU needs only M_PI and the three
 * double externs from it. */
#define _MATH_H
#define M_PI 3.141592653589793
double sin(double x);
double cos(double x);
double atan2(double y, double x);
double __frsqrte(double x);

#pragma cplusplus on
/* `extern "C"` is what keeps the symbol unmangled (a plain `extern inline` under
 * `cplusplus on` emits `sqrtf__Ff`); `inline_max_size` below is what keeps it out
 * of line at the call sites. Both are required to match. */
extern "C" extern inline float sqrtf(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}
#pragma cplusplus reset

/* `#define _MATH_H` above also suppresses libc/math.h's `extern inline double
 * fabs(double)`, after which `fabs` becomes an undefined external symbol (our
 * object showed `U fabs` and fn_1_668 emitted `bl fabs`).  The reference has NO
 * `bl fabs` at all and four `fabs fN,fN` instructions (0x17C4, 0x2C00, 0x3434,
 * 0x63AC), so the inline must be restored for this TU.  This is libc/math.h's
 * own body, copied verbatim; libc/math.h itself is still not edited. */
extern inline double fabs(double x)
{
   return __fabs(x);
}

#pragma inline_max_size(64)


#include "REL/m566dll.h"

#include "game/audio.h"
#include "game/esprite.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/seqman.h"

#include <string.h>

#include "dolphin/gx.h"
#include "dolphin/os.h"

#include "math.h"
#include "string.h"


typedef struct esprite_s {
    /* 0x00 */ s16 memberNo;
    /* 0x02 */ s16 animNo;
} ESPRITE;

typedef struct espanim_s {
    /* 0x00 */ unsigned int dataNum;
    /* 0x04 */ u16 useCnt;
    /* 0x08 */ ANIMDATA *anim;
} ESPANIM;

/* DOL data: on Windows a plain `extern` resolves to the import thunk rather
 * than the array, and HuSprTexLoad then reads a bogus ANIMDATA pointer
 * (access violation inside the m535dll image, 2026-09-17). */
extern ESPRITE esprite[];
extern ESPANIM espanim[];

/* sprite.h has this prototype commented out. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

/* no SDK header declares rand8 */
int rand8(void);

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 20; */
/* 0x18 */ /* double lbl_1_rodata_18 = 0.0078125; */
/* 0x20 */ /* double lbl_1_rodata_20 = 25; */
/* 0x28 */ /* double lbl_1_rodata_28 = 0.03125; */
/* 0x30 */ /* double lbl_1_rodata_30 = -32; */
/* 0x38 */ /* double lbl_1_rodata_38 = 3.141592653589793; */
/* 0x40 */ /* double lbl_1_rodata_40 = 180; */
/* 0x48 */ /* double lbl_1_rodata_48 = 4503601774854144; */
/* 0x50 */ /* double lbl_1_rodata_50 = 0.5; */
/* 0x58 */ /* float lbl_1_rodata_58 = 64.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 63.0f; */
/* 0x60 */ /* float lbl_1_rodata_60 = 0.25f; */
/* 0x64 */ /* float lbl_1_rodata_64 = 650.0f; */
/* 0x68 */ /* float lbl_1_rodata_68 = 104.0f; */
/* 0x6C */ /* float lbl_1_rodata_6C = 23.0f; */
/* 0x70 */ /* float lbl_1_rodata_70 = 1.0f; */
/* 0x74 */ /* float lbl_1_rodata_74 = 550.0f; */
/* 0x78 */ /* s32 lbl_1_rodata_78[4] = { 0x00000014, 0xFFFFFFEC, 0x00000014, 0xFFFFFFEC }; */
/* 0x88 */ /* s32 lbl_1_rodata_88[4] = { 0xFFFFFFEC, 0xFFFFFFEC, 0x00000014, 0x00000014 }; */
/* 0x98 */ /* s32 lbl_1_rodata_98[10] = { 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001 }; */
/* 0xC0 */ /* s32 lbl_1_rodata_C0[8] = { 0x0000002D, 0x0000001E, 0x0000000F, 0x00000005, 0x0000001E, 0x0000001E, 0x0000000A, 0x00000005 }; */
/* 0xE0 */ /* s32 lbl_1_rodata_E0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xEC */ /* s32 lbl_1_rodata_EC[8] = { 0x00000078, 0x0000005A, 0x0000003C, 0x0000002D, 0x0000003C, 0x0000003C, 0x0000003C, 0x0000001E }; */
/* 0x10C */ /* s32 lbl_1_rodata_10C[4] = { 0x00000032, 0x00000041, 0x00000050, 0x0000005A }; */
/* 0x11C */ /* s32 lbl_1_rodata_11C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x128 */ /* s32 lbl_1_rodata_128[3] = { 0x00000000, 0x41F00000, 0x00000000 }; */
/* 0x134 */ /* s32 lbl_1_rodata_134[8] = { 0x00000000, 0x00000003, 0x00000004, 0x00000003, 0x00000000, 0x00000001, 0x00000002, 0x00000001 }; */
/* 0x154 */ /* s32 lbl_1_rodata_154[10] = { 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001 }; */
/* 0x17C */ /* float lbl_1_rodata_17C = 0.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 180.0f; */
/* 0x184 */ /* float lbl_1_rodata_184 = -180.0f; */
/* 0x188 */ /* float lbl_1_rodata_188 = 43.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 53.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 168.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = 110.0f; */
/* 0x198 */ /* float lbl_1_rodata_198 = 50.0f; */
/* 0x19C */ /* float lbl_1_rodata_19C = 0.9f; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 60.0f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 45.0f; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 1; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 0.35; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = 90; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 255.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 1048576.0f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 10.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 0.00390625f; */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 10000.0f; */
/* 0x1D8 */ /* double lbl_1_rodata_1D8 = 0.25; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 90.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = -90.0f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 6.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = -6.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 100.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 0.017453292f; */
/* 0x1F8 */ /* double lbl_1_rodata_1F8 = 45; */
/* 0x200 */ /* float lbl_1_rodata_200 = 256.0f; */
/* 0x204 */ /* float lbl_1_rodata_204 = 0.5f; */
/* 0x208 */ /* float lbl_1_rodata_208 = 8.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 9.0f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 0.000001f; */
/* 0x214 */ /* float lbl_1_rodata_214 = 75.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 12.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 2.0f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 360.0f; */
/* 0x228 */ /* double lbl_1_rodata_228 = 100; */
/* 0x230 */ /* float lbl_1_rodata_230 = -1.0f; */
/* 0x234 */ /* float lbl_1_rodata_234 = 74.0f; */
/* 0x238 */ /* float lbl_1_rodata_238 = 120.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = 0.8f; */
/* 0x240 */ /* double lbl_1_rodata_240 = 70; */
/* 0x248 */ /* double lbl_1_rodata_248 = 35; */
/* 0x250 */ /* float lbl_1_rodata_250 = 20.0f; */
/* 0x258 */ /* double lbl_1_rodata_258 = 73.9; */
/* 0x260 */ /* float lbl_1_rodata_260 = 35.0f; */
/* 0x264 */ /* float lbl_1_rodata_264 = 30.0f; */
/* 0x268 */ /* float lbl_1_rodata_268 = 3.0f; */
/* 0x26C */ /* float lbl_1_rodata_26C = 0.866f; */
/* 0x270 */ /* float lbl_1_rodata_270 = 210.0f; */
/* 0x278 */ /* double lbl_1_rodata_278 = 30; */
/* 0x280 */ /* double lbl_1_rodata_280 = 0.75; */
/* 0x288 */ /* float lbl_1_rodata_288 = 4.0f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 4503599627370496; */
/* 0x298 */ /* double lbl_1_rodata_298 = 3; */
/* 0x2A0 */ /* s32 lbl_1_rodata_2A0[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2B0 */ /* s32 lbl_1_rodata_2B0[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x2BC */ /* s32 lbl_1_rodata_2BC[10] = { 0xFFFFFFF6, 0x00000000, 0x0000001E, 0xFFFFFFCE, 0xFFFFFFF6, 0xFFFFFFDD, 0x0000003C, 0xFFFFFFBA, 0xFFFFFFC9, 0xFFFFFF88 }; */
/* 0x2E4 */ /* s32 lbl_1_rodata_2E4[10] = { 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFF1, 0xFFFFFFDD, 0x00000000, 0xFFFFFFEC, 0xFFFFFFFB, 0x00000000, 0xFFFFFFE2 }; */
/* 0x30C */ /* float lbl_1_rodata_30C = -360.0f; */
/* 0x310 */ /* float lbl_1_rodata_310 = 0.125f; */
/* 0x318 */ /* double lbl_1_rodata_318 = 0; */
/* 0x320 */ /* float lbl_1_rodata_320 = 14400.0f; */
/* 0x328 */ /* double lbl_1_rodata_328 = 0.65; */
/* 0x330 */ /* float lbl_1_rodata_330 = 70.0f; */
/* 0x338 */ /* double lbl_1_rodata_338 = 60; */
/* 0x340 */ /* float lbl_1_rodata_340 = 0.4f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 80.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 400.0f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 1.6f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 1000.0f; */
/* 0x358 */ /* double lbl_1_rodata_358 = 360; */
/* 0x360 */ /* float lbl_1_rodata_360 = 40.0f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 1.5f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 32.0f; */
/* 0x36C */ /* float lbl_1_rodata_36C = 150.0f; */
/* 0x370 */ /* float lbl_1_rodata_370 = 0.85f; */
/* 0x374 */ /* float lbl_1_rodata_374 = 0.95f; */
/* 0x378 */ /* float lbl_1_rodata_378 = 2472.0f; */
/* 0x37C */ /* float lbl_1_rodata_37C = 77.25f; */
/* 0x380 */ /* float lbl_1_rodata_380 = 0.96875f; */
/* 0x388 */ /* double lbl_1_rodata_388 = 1.01875; */
/* 0x390 */ /* float lbl_1_rodata_390 = 2.625f; */
/* 0x394 */ /* float lbl_1_rodata_394 = -10000.0f; */
/* 0x398 */ /* float lbl_1_rodata_398 = 25.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 112.5f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 0.875f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 866.0f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 500.0f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = 0.9375f; */
/* 0x3B0 */ /* s32 lbl_1_rodata_3B0[1] = { 0x40700000 }; */
/* 0x3B4 */ /* s32 lbl_1_rodata_3B4[41] = { 0x000008E1, 0x000008E2, 0x000008E4, 0x000008E6, 0x000002D8, 0x000008E8, 0x000008E9, 0x000002C4, 0x000002D7, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x458 */ /* float lbl_1_rodata_458 = 5.0f; */
/* 0x45C */ /* float lbl_1_rodata_45C = 288.0f; */
/* 0x460 */ /* s32 lbl_1_rodata_460[12] = { 0xC2200000, 0x42200000, 0x00000000, 0x42200000, 0x42200000, 0x00000000, 0x42200000, 0xC2200000, 0x00000000, 0xC2200000, 0xC2200000, 0x00000000 }; */
/* 0x490 */ /* s32 lbl_1_rodata_490[12] = { 0xC2340000, 0x42580000, 0x00000000, 0x42340000, 0x42580000, 0x00000000, 0x42340000, 0xC2580000, 0x00000000, 0xC2340000, 0xC2580000, 0x00000000 }; */
/* 0x4C0 */ /* s32 lbl_1_rodata_4C0[4] = { 0x00000000, 0xFFFFFFF9, 0x00000000, 0x00000007 }; */
/* 0x4D0 */ /* s32 lbl_1_rodata_4D0[8] = { 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000 }; */
/* 0x4F0 */ /* s32 lbl_1_rodata_4F0[10] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000001E, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x518 */ /* s32 lbl_1_rodata_518[10] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000001E, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x540 */ /* double lbl_1_rodata_540 = 0.8; */
/* 0x548 */ /* double lbl_1_rodata_548 = 0.6; */
/* 0x550 */ /* float lbl_1_rodata_550 = 34.0f; */
/* 0x554 */ /* float lbl_1_rodata_554 = 27.0f; */
/* 0x558 */ /* double lbl_1_rodata_558 = 0.1; */
/* 0x560 */ /* double lbl_1_rodata_560 = 1.1; */
/* 0x568 */ /* double lbl_1_rodata_568 = 0.4; */
/* 0x570 */ /* double lbl_1_rodata_570 = 0.7; */
/* 0x578 */ /* double lbl_1_rodata_578 = 1.2; */
/* 0x580 */ /* float lbl_1_rodata_580 = 7.0f; */
/* 0x588 */ /* double lbl_1_rodata_588 = 1.2999999999999998; */
/* 0x590 */ /* float lbl_1_rodata_590 = 13.0f; */
/* 0x598 */ /* double lbl_1_rodata_598 = 1.4; */
/* 0x5A0 */ /* double lbl_1_rodata_5A0 = 1.3; */
/* 0x5A8 */ /* double lbl_1_rodata_5A8 = 0.3; */
/* 0x5B0 */ /* float lbl_1_rodata_5B0 = 22.0f; */
/* 0x5B4 */ /* float lbl_1_rodata_5B4 = 66.0f; */
/* 0x5B8 */ /* s32 lbl_1_rodata_5B8[5] = { 0x00790000, 0x00790001, 0x00790002, 0x00790003, 0x00790004 }; */
/* 0x5CC */ /* s32 lbl_1_rodata_5CC[6] = { 0x0000000B, 0x0000000B, 0x00000008, 0x00000004, 0x00000004, 0x00000004 }; */
/* 0x5E4 */ /* s32 lbl_1_rodata_5E4[6] = { 0x0000003A, 0x00000045, 0x00000050, 0x00000058, 0x0000005C, 0x00000060 }; */
/* 0x5FC */ /* s32 lbl_1_rodata_5FC[3] = { 0x00000000, 0x00000001, 0x00000002 }; */
/* 0x608 */ /* s32 lbl_1_rodata_608[6] = { 0x00790021, 0x00790023, 0x00790027, 0x00790026, 0x00790025, 0x0079000D }; */
/* 0x620 */ /* s32 lbl_1_rodata_620[3] = { 0x00790022, 0x00790024, 0x00790028 }; */
/* 0x62C */ /* s32 lbl_1_rodata_62C[7] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x648 */ /* s32 lbl_1_rodata_648[7] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF }; */
/* 0x664 */ /* s32 lbl_1_rodata_664[7] = { 0x00790006, 0x00790007, 0x00790008, 0x00790009, 0x0079000A, 0x0079000B, 0x0079000C }; */
/* 0x680 */ /* s32 lbl_1_rodata_680[29] = { 0x00000001, 0x00000001, 0x00000002, 0x00000003, 0x00000002, 0x00000001, 0x00000001, 0x00000002, 0x00000003, 0x00000002, 0x00000001, 0x00000001, 0x00000002, 0x00000003, 0x00000002, 0x00000001, 0x00000001, 0x00000002, 0x00000003, 0x00000001, 0x00000001, 0x00000002, 0x00000002, 0x00000002, 0x00000002, 0x00000003, 0x00000003, 0x00000003, 0x00000003 }; */
/* 0x6F4 */ /* s32 lbl_1_rodata_6F4[29] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x768 */ /* s32 lbl_1_rodata_768[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x774 */ /* s32 lbl_1_rodata_774[4] = { 0x00000046, 0x000000BE, 0x00000184, 0x000001FC }; */
/* 0x784 */ /* s32 lbl_1_rodata_784[7] = { 0xFFFFFFF8, 0x0000000E, 0x00000024, 0xFFFFFFDC, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x7A0 */ /* float lbl_1_rodata_7A0 = 0.75f; */
/* 0x7A4 */ /* float lbl_1_rodata_7A4 = 14000.0f; */
/* 0x7A8 */ /* double lbl_1_rodata_7A8 = 355; */
/* 0x7B0 */ /* float lbl_1_rodata_7B0 = 11.0f; */
/* 0x7B8 */ /* double lbl_1_rodata_7B8 = 555; */
/* 0x7C0 */ /* float lbl_1_rodata_7C0 = 17.0f; */
/* 0x7C4 */ /* float lbl_1_rodata_7C4 = 56.0f; */
/* 0x7C8 */ /* s32 lbl_1_rodata_7C8[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 }; */
/* 0x7D8 */ /* s32 lbl_1_rodata_7D8[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 }; */
/* 0x7E8 */ /* s32 lbl_1_rodata_7E8[3] = { 0x00000000, 0x459C4000, 0x00000000 }; */
/* 0x7F4 */ /* s32 lbl_1_rodata_7F4[3] = { 0x00000000, 0xBF800000, 0xBF000000 }; */
/* 0x800 */ /* u8 lbl_1_rodata_800[1] = { 0xFF }; */
/* 0x801 */ /* u8 lbl_1_rodata_801[1] = { 0xFF, 0xFF, 0xFF }; */
/* 0x804 */ /* float lbl_1_rodata_804 = 25000.0f; */
/* 0x808 */ /* float lbl_1_rodata_808 = 1.2f; */
/* 0x80C */ /* float lbl_1_rodata_80C = 640.0f; */
/* 0x810 */ /* float lbl_1_rodata_810 = 480.0f; */
/* 0x814 */ /* float lbl_1_rodata_814 = 84.0f; */
/* 0x818 */ /* float lbl_1_rodata_818 = -32.6f; */
/* 0x81C */ /* float lbl_1_rodata_81C = -0.1f; */
/* 0x820 */ /* float lbl_1_rodata_820 = 8.5f; */
/* 0x824 */ /* float lbl_1_rodata_824 = 5000.0f; */
/* 0x828 */ /* float lbl_1_rodata_828 = 13000.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0[7] = { 0x0079001C, 0x0079001C, 0x0079001C, 0x0079001D, 0x0079001D, 0x0079001D, 0x0079000F };
/* 0x1C */ s32 lbl_1_data_1C[41] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00890000, 0x00300000, 0x00B40000, 0x00EA0000, 0x00E30000, 0x00140000, 0x00DD0000, 0x002A0000, 0x00C60000, 0x00AD0000, 0x00000000, 0x00000000, 0x00000000 };
#define M566_ESPTBL ((s32 (*)[7])lbl_1_data_1C) /* fork H: [4][7] espIds */
/* 0xC0 */ s32 lbl_1_data_C0[10] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C000F, 0x008C004B, 0x00870069, 0x008C0016, 0x008C004F, 0x008C001F, 0x008C0031 };
/* 0xE8 */ u8 lbl_1_data_E8[10] = { 0, 0, 0, 1, 0, 1, 0, 0, 0, 1 };
/* 0xF2 */ u8 lbl_1_data_F2[10] = { 8, 8, 8, 0, 8, 8, 8, 8, 8, 8 };
/* 0xFC */ s32 lbl_1_data_FC[10] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000001C, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x124 */ s32 lbl_1_data_124[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x134 */ s16 lbl_1_data_134 = -1;
/* 0x138 */ s32 lbl_1_data_138[2] = { 0xFFFFFFFF, 0x00000708 };
/* 0x140 */ s32 lbl_1_data_140[1] = { 0xFFFFFFFF };
/* 0x144 */ s32 lbl_1_data_144[1] = { 0xFFFFFFFF };
/* 0x148 */ s32 lbl_1_data_148[1] = { 0x00000001 };
/* 0x14C */ s32 lbl_1_data_14C[3] = { 0x00000000, 0x00000004, 0x00000003 };
/* 0x158 */ s32 lbl_1_data_158[1] = { 0x00000001 };
/* 0x15C */ float lbl_1_data_15C[4][4] = { { -100.0f, 0.0f, -100.0f, 0.0f }, { 100.0f, 0.0f, -100.0f, 0.0f }, { -100.0f, 0.0f, 100.0f, 0.0f }, { 100.0f, 0.0f, 100.0f, 0.0f } };
/* 0x19C */ s32 lbl_1_data_19C[29] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x210 */ char lbl_1_data_210[] = "ske_head";
/* 0x21C */ s32 lbl_1_data_21C[5] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x230 */ s32 lbl_1_data_230[5] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
/* 0x244 */ s32 lbl_1_data_244[5] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x258 */ float lbl_1_data_258 = -10000.0f;
/* 0x25C */ char lbl_1_data_25C[] = "itemhook_c";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1810 */ M566_ACTOR lbl_1_bss_1810[29]; /* 0xAE0 = 29 * 0x60 (fork H) */
/* 0x1600 */ M566_ENT lbl_1_bss_1600[11]; /* 0x210 = 11 * 0x30 (strides.py) */
/* 0x600 */ M566_PART lbl_1_bss_600[128]; /* 0x1000 = 128 * 0x20 (fork J) */
/* 0xE0 */ M566_SUB lbl_1_bss_E0[41]; /* 0x520 = 41 * 0x20 (fork I) */
/* 0xDC */ OMOBJ *lbl_1_bss_DC;
/* 0xD8 */ OMOBJ *lbl_1_bss_D8;
/* 0xC8 */ OMOBJ *lbl_1_bss_C8[4];
/* 0xC4 */ OMOBJ *lbl_1_bss_C4;
/* 0xC0 */ OMOBJ *lbl_1_bss_C0;
/* 0xBC */ s32 lbl_1_bss_BC;
/* 0xB8 */ OMOBJMAN *lbl_1_bss_B8;
/* 0xB6 gap_05_000000B6_bss (0x2) -- dtk filler */
/* 0xB4 */ GAMEMESID lbl_1_bss_B4;
/* 0xB0 */ s32 lbl_1_bss_B0;
/* 0xAC */ s32 lbl_1_bss_AC;
/* 0x98 */ s32 lbl_1_bss_98[5]; /* 0x14: 4-aligned, retype */
/* 0x90 */ s32 lbl_1_bss_90[2]; /* 0x8: 4-aligned, retype */
/* 0x8C */ s32 lbl_1_bss_8C;
/* 0x84 */ HUSPRGRPID lbl_1_bss_84[4]; /* 0x8: lha at base + i*2, i < 4 (fork I) */
/* 0x10 */ s32 lbl_1_bss_10[29]; /* 0x74: 4-aligned, retype */
/* 0xC */ s32 lbl_1_bss_C;
/* 0x8 */ s32 lbl_1_bss_8;
/* 0x0 */ float lbl_1_bss_0[2]; /* 0x8: lfs/stfs at +0 only (fork I) */

/* --- functions (reference order) --- */
/* 286 insns */
void fn_1_A0(void)
{
    float rx;
    float ry;
    float rz;
    HuVecF pos;
    HuVecF target;
    HuVecF up;

    CenterM[1].y += 20.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0);
    CZoomM[1] += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRotM[1].y += HuPadSubStkX[0] / 32.0;
    CRotM[1].x += HuPadSubStkY[0] / -32.0;
    rx = CRotM[1].x;
    ry = CRotM[1].y;
    rz = CRotM[1].z;
    pos.x = CenterM[1].x + CZoomM[1] * (sin(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
    pos.y = CenterM[1].y + CZoomM[1] * -sin(M_PI * rx / 180.0);
    pos.z = CenterM[1].z + CZoomM[1] * (cos(M_PI * ry / 180.0) * cos(M_PI * rx / 180.0));
    target.x = CenterM[1].x;
    target.y = CenterM[1].y;
    target.z = CenterM[1].z;
    up.x = sin(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
    up.y = cos(M_PI * rx / 180.0);
    up.z = cos(M_PI * ry / 180.0) * sin(M_PI * rx / 180.0);
}

/* 84 insns -- pan/volume helper. Transcribed verbatim: the pan argument is
 * NOT clamped, the volume argument IS clamped to 104..127 by the reference. */
void fn_1_518(int seNo, float x, float y)
{
    s16 vol;

    HuAudFXPanning(seNo, 0.5 + (64.0f + 63.0f * (0.25f * (x / 650.0f))));
    vol = 0.5 + (104.0f + 23.0f * (1.0f + y / 550.0f));
    vol = (vol < 104) ? 104 : ((vol > 127) ? 127 : vol);
    HuAudFXVolSet(seNo, vol);
}

/* 4260 insns */
void fn_1_668(OMOBJ *obj)
{
    M566_PLAYER *work = obj->data;
    float mag = 0.0f;               /* f30 */
    float velX = 0.0f;              /* f24 */
    float velZ = 0.0f;              /* f23 */
    float press = 0.0f;             /* f27 */
    s16 mode = -1;                  /* r28 -- `extsh r28,rN` on write (0x2A40,
                                     * 0x2B1C, 0x44C4) and `extsh rN,r28` on
                                     * read (0x44C8..0x45A8) -> s16, fork E */
    float unkF130 = 0.0f;           /* sp 0x130 */
    float camX;                     /* f29 */
    float camZ;                     /* f28 */
    M566_PLAYER *p[4];              /* sp 0x1ec */
    s32 i;
    s32 j;                          /* fork E: the 128-particle loop, r24 */
    s32 k;                          /* fork E: the 4-player separation loop, r22 */
    s32 n;                          /* fork E: the 29-actor loop, r26 */
    s32 m;                          /* fork F: the 29-actor target scan, r23 */
    s32 q;                          /* fork F: the 29-actor count / pick loops, r27 */

    if (work->playerNo == 0) {
        for (i = 0; i < 29; i++) {
            lbl_1_bss_10[i] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        p[i] = lbl_1_bss_C8[i]->data;
    }
    work->unk040 = work->unk048 = 0.0f;
    obj->rot.y += (obj->rot.y > 180.0f) ? -360 : ((obj->rot.y < -180.0f) ? 360 : 0);
    if (work->unk024 == 2) {
        if (lbl_1_bss_BC < 1003) {
            if (lbl_1_bss_BC == 1000 && lbl_1_bss_0[0] >= 43.0f && lbl_1_bss_0[0] <= 53.0f) {
                s32 xTbl[4] = { 20, -20, 20, -20 };
                s32 zTbl[4] = { -20, -20, 20, 20 };

                velX = xTbl[work->playerNo] / 20 * 10;
                velZ = zTbl[work->playerNo] / 20 * 10;
            }
            if (lbl_1_bss_BC == 1001 && work->playerNo == 0 && 168.0f == lbl_1_bss_0[0]) {
                press = 1.0f;
            }
            if (lbl_1_bss_BC == 1002) {
                s32 faceTbl[10] = { 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 };

                mag = lbl_1_bss_0[0];
                work->unk058 = (mag < 110.0f)
                                   ? HuAtan(lbl_1_bss_1600[lbl_1_bss_1810[0].unk004].unk14 - 50.0f,
                                            -lbl_1_bss_C8[0]->trans.x)
                                   : 0.9f * work->unk058;
                work->unk058 = (work->unk058 < 0.0f) ? 0.0f
                                                     : ((work->unk058 > 60.0f) ? 60.0f : work->unk058);
                Hu3DMotionForceSet(obj->mdlId[0], lbl_1_data_210, 0x200,
                                   faceTbl[work->unk008]
                                       ? 180.0f - 45.0f * (work->unk058 / 60.0f)
                                       : 90.0 - 45.0f * (work->unk058 / 60.0f)
                                                    * ((work->unk008 != 2) ? 1.0 : 0.35));
            }
            if (lbl_1_bss_BC == 1003 && 0.0f != work->unk058) {
                work->unk058 = 0.0f;
                Hu3DMotionNoMotReset(obj->mdlId[0], lbl_1_data_210, 0x200);
            }
        } else if (lbl_1_bss_BC < 1004) {
            if (work->unk010 != -1 || (HuPadBtn[0] & PAD_BUTTON_B)) {
                velX = HuPadStkX[work->unk010];
                velZ = HuPadStkY[work->unk010];
                press = HuPadBtnDown[work->unk010] & PAD_BUTTON_A;
            } else {
                switch (work->unk060) {
                case 0: {
                    s32 waitTbl[2][4] = { { 45, 30, 15, 5 }, { 30, 30, 10, 5 } };
                    s32 freeNum = 0;

                    for (i = 0; i < 29; i++) {
                        freeNum += work->unk070[i] == 0;
                    }
                    if (freeNum == 0) {
                        for (i = 0; i < 29; i++) {
                            work->unk070[i] = (work->unk070[i] == 2) ? 0 : work->unk070[i];
                        }
                    }
                    work->unk064++;
                    if (work->unk068 == 0) {
                        work->unk068 = waitTbl[0][work->unk014]
                                     + waitTbl[1][work->unk014] * (rand8() / 255.0f);
                    }
                    if (work->unk064 >= work->unk068) {
                        float best = 1048576.0f;
                        float dist;

                        work->unk06C = -1;
                        for (i = 0; i < 29; i++) {
                            if (work->unk070[i] == 0 && lbl_1_bss_1810[i].unk000 != 0
                                && lbl_1_bss_1810[i].unk014 == 0) {
                                dist = 10.0f * (rand8() / 256.0f)
                                     + HuMagPoint2D(lbl_1_bss_1810[i].unk028 - obj->trans.x,
                                                    lbl_1_bss_1810[i].unk030 - obj->trans.z);
                                if (best > dist) {
                                    work->unk06C = i;
                                    best = dist;
                                }
                            }
                        }
                        if (work->unk06C != -1) {
                            work->unk060 = 1;
                            work->unk064 = 0;
                            work->unk0F8 = 10000.0f;
                            work->unk0FC = 0;
                            work->unk100 = 70;
                            work->unk104 = 0;
                        }
                    }
                    break;
                }
                case 1: {
                    float dx;
                    float dz;
                    float curAng;
                    float tgtAng;
                    s32 turn;

                    dx = lbl_1_bss_1810[work->unk06C].unk028 - obj->trans.x;
                    dz = lbl_1_bss_1810[work->unk06C].unk030 - obj->trans.z;
                    velX = dx / 0.25;
                    velZ = -dz / 0.25;
                    if (work->unk0E4 != -1 && work->unk100 >= 20) {
                        curAng = HuAtan(dx, dz);
                        tgtAng = HuAtan(work->unk0E8 - obj->trans.x, work->unk0EC - obj->trans.z);
                        tgtAng += (tgtAng - curAng <= -180.0f)
                                      ? 360
                                      : ((tgtAng - curAng > 180.0f) ? -360 : 0);
                        turn = (work->unk0F0 >= 90.0f || work->unk0F0 <= -90.0f)
                                   ? 0
                                   : ((tgtAng - curAng < 0.0f) ? 4 : -4);
                        work->unk0F0 += turn;
                        if (work->unk104 == 0) {
                            work->unk104 = (turn < 0) ? -1 : ((turn > 0) ? 1 : 0);
                        } else if (turn * work->unk104 < 0) {
                            work->unk100 -= 20;
                            work->unk104 = (turn < 0) ? -1 : ((turn > 0) ? 1 : 0);
                        }
                    } else {
                        work->unk0F0 += (work->unk0F0 < 6.0f && work->unk0F0 > -6.0f)
                                            ? 0
                                            : ((work->unk0F0 < 0.0f) ? 6 : -6);
                    }
                    if (work->unk0F8 * work->unk0F8 - 100.0f > HuMag2Point2D(dx, dz)) {
                        work->unk0F8 = HuMagPoint2D(dx, dz);
                        work->unk0FC = 0;
                    }
                    work->unk0FC++;
                    work->unk064++;
                    work->unk100 += (work->unk100 < 70) ? 1 : 0;
                    work->unk0E4 = -1;
                    {
                        Vec vec = { 0.0f, 0.0f, 0.0f };
                        Mtx mtx;

                        vec.x = velX;
                        vec.z = -velZ;
                        PSMTXRotRad(mtx, 'y', 0.017453292f * work->unk0F0);
                        PSMTXMultVec(mtx, &vec, &vec);
                        velX = vec.x;
                        velZ = -vec.z;
                    }
                    if (lbl_1_bss_1810[work->unk06C].unk000 == 0
                        || lbl_1_bss_1810[work->unk06C].unk014 != 0) {
                        work->unk060 = 0;
                        work->unk064 = 0;
                        work->unk068 = 0;
                    } else if (work->unk0F4 == work->unk06C) {
                        float faceAng;

                        faceAng = HuAtan(lbl_1_bss_1810[work->unk06C].unk028 - obj->trans.x,
                                         lbl_1_bss_1810[work->unk06C].unk030 - obj->trans.z);
                        faceAng += (faceAng - obj->rot.y <= -180.0f)
                                       ? 360
                                       : ((faceAng - obj->rot.y > 180.0f) ? 360 : 0);
                        if (fabs(faceAng - obj->rot.y) <= 45.0) {
                            work->unk060 = 2;
                            work->unk064 = 0;
                            work->unk068 = 0;
                        }
                    } else if (work->unk0FC > work->playerNo * 5 + 90) {
                        work->unk070[work->unk06C] = 2;
                        work->unk060 = 0;
                        work->unk064 = 0;
                        work->unk068 = 1;
                    }
                    break;
                }
                case 2: {
                    s32 holdTbl[2][4] = { { 120, 90, 60, 45 }, { 60, 60, 60, 30 } };
                    s32 hitTbl[4] = { 50, 65, 80, 90 };

                    work->unk064++;
                    if (work->unk068 == 0) {
                        work->unk068 = holdTbl[0][work->unk014]
                                     + holdTbl[1][work->unk014] * (rand8() / 255.0f);
                    }
                    if (work->unk064 >= work->unk068) {
                        work->unk060 = 0;
                        work->unk064 = 0;
                        work->unk068 = 0;
                        if (lbl_1_bss_1810[work->unk0F4].unk000 == 1) {
                            press = 1.0f;
                        }
                        press = (rand8() < 256.0f * hitTbl[work->unk014] / 100.0f) ? press : !press;
                        work->unk070[work->unk06C] = 1;
                    } else if (work->unk0F4 != work->unk06C) {
                        work->unk060 = 1;
                        work->unk064 = 0;
                    }
                    break;
                }
                }
            }
        }
        camX = 0.25 * velX;
        camZ = 0.25 * -velZ;
        {
            Vec vec = { 0.0f, 0.0f, 0.0f };
            Mtx mtx;

            vec.x = camX;
            vec.z = camZ;
            PSMTXRotRad(mtx, 'y', 0.017453292f * CRotM[1].y);
            PSMTXMultVec(mtx, &vec, &vec);
            camX = vec.x;
            camZ = vec.z;
            mag = HuMagPoint2D(camX, camZ);
            if (mag >= 0.5f) {
                if (mag < 10.0f) {
                    work->unk040 = camX;
                    work->unk048 += camZ;
                } else {
                    camX /= mag;
                    camZ /= mag;
                    mag = 10.0f;
                    work->unk040 = camX * mag;
                    work->unk048 = camZ * mag;
                }
                work->unk03C = mag;
                if (work->unk024 == 2) {
                    obj->rot.y = HuAtan(work->unk040, work->unk048);
                }
                if (work->unk024 == 2) {
                    if (work->unk03C >= 8.0f) {
                        mode = 2;
                    } else {
                        mode = 1;
                    }
                }
            } else {
                if (work->unk024 == 2) {
                    mode = 0;
                }
            }
        }
    } else if (work->unk024 == 3) {
        work->unk050 = 0;
        if (work->unk028 < 10) {
            float dist = HuMagPoint2D(lbl_1_bss_1810[work->unk04C].unk028 - obj->trans.x,
                                      lbl_1_bss_1810[work->unk04C].unk030 - obj->trans.z);
            float rate = work->unk028 / 9.0f;
            float ang = HuAtan(lbl_1_bss_1810[work->unk04C].unk028 - obj->trans.x,
                               lbl_1_bss_1810[work->unk04C].unk030 - obj->trans.z);

            ang += (ang - obj->rot.y < -180.0f) ? 360 : ((ang - obj->rot.y > 180.0f) ? -360 : 0);
            obj->rot.y = obj->rot.y * (1.0f - rate) + ang * rate;
            dist = (0.0f == dist) ? 0.000001f : dist;
            obj->trans.x = obj->trans.x * (1.0f - rate)
                         + rate * (lbl_1_bss_1810[work->unk04C].unk028
                                   - 75.0f * ((lbl_1_bss_1810[work->unk04C].unk028 - obj->trans.x) / dist));
            obj->trans.z = obj->trans.z * (1.0f - rate)
                         + rate * (lbl_1_bss_1810[work->unk04C].unk030
                                   - 75.0f * ((lbl_1_bss_1810[work->unk04C].unk030 - obj->trans.z) / dist));
            lbl_1_bss_1810[work->unk04C].unk014 = 4;
            lbl_1_data_19C[work->unk04C] = 0;
        } else if (work->unk028 == 10) {
            char *hook;

            if (lbl_1_bss_E0[1].unk00 < 3) {
                lbl_1_bss_E0[1].unk04[lbl_1_bss_E0[1].unk00] = lbl_1_bss_1810[work->unk04C].unk028;
                lbl_1_bss_E0[1].unk10[lbl_1_bss_E0[1].unk00] = lbl_1_bss_1810[work->unk04C].unk030;
                lbl_1_bss_E0[1].unk00++;
            }
            switch (lbl_1_bss_1810[work->unk04C].unk000) {
            case 1:
                lbl_1_bss_1810[work->unk04C].unk014 = 1;
                break;
            case 2:
                lbl_1_bss_1810[work->unk04C].unk014 = 2;
                break;
            case 3:
                lbl_1_bss_1810[work->unk04C].unk014 = 3;
                break;
            }
            lbl_1_bss_1810[work->unk04C].unk018 = 0;
            lbl_1_bss_1810[work->unk04C].unk01C = work->playerNo;
            hook = CharModelItemHookGet(obj->mdlId[0], 4, 0);
            Hu3DModelHookSet(obj->mdlId[0], hook, lbl_1_bss_C4->mdlId[work->unk04C + 29]);
            Hu3DModelPosSet(lbl_1_bss_C4->mdlId[work->unk04C + 29], 0.0f, 0.0f, 0.0f);
            if (lbl_1_bss_1810[work->unk04C].unk000 == 2) {
                for (i = 0; i < 4; i++) {
                    if (lbl_1_data_124[i] == 0) {
                        break;
                    }
                }
                if (i < 4) {
                    lbl_1_bss_1810[work->unk04C].unk00C = i;
                    lbl_1_data_124[i] = 1;
                } else {
                    lbl_1_bss_1810[work->unk04C].unk00C = -1;
                }
            }
        } else if (work->unk028 == ((lbl_1_bss_1810[work->unk04C].unk000 != 2) ? 20 : 40)) {
            if (lbl_1_bss_1810[work->unk04C].unk000 != 3) {
                s32 cnt = 0;
                HU3DMODEL *modelP = &Hu3DData[lbl_1_bss_C4->mdlId[work->unk04C + 29]];
                char *hook;
                Vec vec = { 0.0f, 30.0f, 0.0f };
                Vec pos;
                Mtx mtx;

                hook = CharModelItemHookGet(obj->mdlId[0], 4, 0);
                Hu3DModelObjMtxGet(obj->mdlId[0], hook, mtx);
                PSMTXMultVec(mtx, &vec, &pos);
                for (j = 0; j < 128; j++) {
                    if (lbl_1_bss_600[j].unk00 > 0) {
                        continue;
                    }
                    lbl_1_bss_600[j].unk00 = 1;
                    lbl_1_bss_600[j].unk04 = 0x80;
                    lbl_1_bss_600[j].unk08 = pos.x;
                    lbl_1_bss_600[j].unk0C = pos.y;
                    lbl_1_bss_600[j].unk10 = pos.z;
                    lbl_1_bss_600[j].unk14 = 12.0f * (2.0f * (rand8() / 255.0f) - 1.0f);
                    lbl_1_bss_600[j].unk18 = 12.0f * (2.0f * (rand8() / 255.0f) - 1.0f);
                    lbl_1_bss_600[j].unk1C = 12.0f * (2.0f * (rand8() / 255.0f) - 1.0f);
                    cnt++;
                    if (cnt >= 32) {
                        break;
                    }
                }
                Hu3DModelAttrSet(lbl_1_bss_C4->mdlId[work->unk04C + 29], 1);
            } else {
                char *hook;
                Vec vec;
                Mtx mtx;

                hook = CharModelItemHookGet(obj->mdlId[0], 4, 0);
                Hu3DModelObjMtxGet(obj->mdlId[0], hook, mtx);
                C_QUATMtx(&lbl_1_bss_1810[work->unk04C].unk04C, mtx);
                PSQUATInverse(&lbl_1_bss_1810[work->unk04C].unk04C,
                              &lbl_1_bss_1810[work->unk04C].unk04C);
                Hu3DMtxTransGet(mtx, &vec);
                lbl_1_bss_1810[work->unk04C].unk034 = vec.x;
                lbl_1_bss_1810[work->unk04C].unk038 = vec.y;
                lbl_1_bss_1810[work->unk04C].unk03C = vec.z;
                Hu3DModelHookReset(obj->mdlId[0]);
                Hu3DModelPosSet(lbl_1_bss_C4->mdlId[work->unk04C + 29],
                                lbl_1_bss_1810[work->unk04C].unk034,
                                lbl_1_bss_1810[work->unk04C].unk038,
                                lbl_1_bss_1810[work->unk04C].unk03C);
                PSMTXQuat(mtx, &lbl_1_bss_1810[work->unk04C].unk04C);
                Hu3DMtxRotGet(mtx, &vec);
                Hu3DModelRotSet(lbl_1_bss_C4->mdlId[work->unk04C + 29], vec.x, vec.y, vec.z);
            }
        }
        mode = 5;
        switch (lbl_1_bss_1810[work->unk04C].unk000) {
        case 1:
            if (work->unk028 >= 20) {
                mode = 0;
            }
            if (work->unk028 >= ((lbl_1_bss_BC == 1002) ? 10 : 60) + 20) {
                if (lbl_1_bss_BC == 1003) {
                    if (work->unk018 < 4) {
                        work->unk02C[work->unk018] = 30;
                    }
                    if (work->unk018 + lbl_1_bss_1810[work->unk04C].unk010 < 4) {
                        work->unk02C[work->unk018 + lbl_1_bss_1810[work->unk04C].unk010] = 30;
                    }
                    work->unk018 = 1 + lbl_1_bss_1810[work->unk04C].unk010 + work->unk018;
                }
                work->unk024 = 2;
                work->unk028 = 0;
            }
            break;
        case 2:
        case 3:
            if (work->unk028 >= ((lbl_1_bss_1810[work->unk04C].unk000 == 3) ? 20 : 40)) {
                work->unk024 = 4;
                work->unk028 = 0;
                if (lbl_1_bss_1810[work->unk04C].unk000 == 2) {
                    omVibrate(work->padIdx, 12, 12, 0);
                }
            }
            break;
        }
    } else if (work->unk024 == 4) {
        if (lbl_1_bss_1810[work->unk04C].unk000 == 3) {
            mode = (work->unk028 <= 54) ? 4 : ((work->unk028 <= 114) ? 6 : 0);
            if (work->unk028 == 3) {
                fn_1_518(CharFXPlay(work->charNo, 0x1F9), obj->trans.x, obj->trans.z);
            }
            if (work->unk028 >= 120) {
                work->unk024 = 2;
            }
            if (work->unk028 < 60) {
                if (work->unk028 % 30 == 1) {
                    omVibrate(work->padIdx, 12, 12, 0);
                }
            }
        } else {
            if (work->unk028 == 40) {
                Hu3DModelAttrSet(obj->mdlId[0], 0x40000002);
            }
            mode = (work->unk028 <= 39) ? 3 : 6;
            if (work->unk028 == 1) {
                float ang = HuAtan(lbl_1_bss_1810[work->unk04C].unk028 - obj->trans.x,
                                   lbl_1_bss_1810[work->unk04C].unk030 - obj->trans.z);
                float absAng = fabs((ang <= -180.0f) ? 360.0f + ang
                                                     : ((ang > 180.0f) ? ang - 360.0f : ang));

                obj->rot.y = ang;
                omVibrate(work->padIdx, 12, 12, 0);
                fn_1_518(CharFXPlay(work->charNo, 0x202), obj->trans.x, obj->trans.z);
            }
            if (work->unk028 >= 105) {
                work->unk024 = 2;
            }
            if (work->unk028 <= 45) {
                work->unk040 = 100.0 * -sin(M_PI * obj->rot.y / 180.0) / 45.0;
                work->unk048 = 100.0 * -cos(M_PI * obj->rot.y / 180.0) / 45.0;
            }
        }
    }
    work->unk028++;
    obj->trans.x += work->unk040;
    obj->trans.z += work->unk048;
    if (lbl_1_bss_BC < 1005) {
        for (k = 0; k < 4; k++) {
            float dx = lbl_1_bss_C8[k]->trans.x - obj->trans.x;
            float dz = lbl_1_bss_C8[k]->trans.z - obj->trans.z;
            float d;

            if (k == work->playerNo) {
                continue;
            }
            if (0.0f == dx && 0.0f == dz) {
                dz = -1.0f;
            }
            d = HuMagPoint2D(dx, dz);
            if (d < 100.0f) {
                dx = dx * (100.0f / d);
                dz = dz * (100.0f / d);
                obj->trans.x = lbl_1_bss_C8[k]->trans.x - dx;
                obj->trans.z = lbl_1_bss_C8[k]->trans.z - dz;
                if (work->unk010 == -1 && work->unk060 == 1) {
                    work->unk0E4 = k;
                    work->unk0E8 = lbl_1_bss_C8[k]->trans.x;
                    work->unk0EC = lbl_1_bss_C8[k]->trans.z;
                }
            }
        }
        {
            s32 lim = (work->unk024 != 3) ? 90.0f : 74.0f;

            for (n = 0; n < 29; n++) {
                float adist;
                float ax = lbl_1_bss_1810[n].unk028 - obj->trans.x;
                float az = lbl_1_bss_1810[n].unk030 - obj->trans.z;

                if (lbl_1_bss_1810[n].unk000 == 0) {
                    continue;
                }
                if (work->playerNo == lbl_1_bss_1810[n].unk01C) {
                    if (lbl_1_bss_1810[n].unk014 == 2) {
                        continue;
                    }
                    if (lbl_1_bss_1810[n].unk014 == 1) {
                        continue;
                    }
                }
                if (0.0f == ax && 0.0f == az) {
                    az = -1.0f;
                }
                adist = HuMagPoint2D(ax, az);
                if (adist < lim) {
                    ax = ax * (lim / adist);
                    az = az * (lim / adist);
                    obj->trans.x = lbl_1_bss_1810[n].unk028 - ax;
                    obj->trans.z = lbl_1_bss_1810[n].unk030 - az;
                    if (work->unk010 == -1 && work->unk060 == 1) {
                        work->unk0E4 = n + 4;
                        work->unk0E8 = lbl_1_bss_1810[n].unk028;
                        work->unk0EC = lbl_1_bss_1810[n].unk030;
                    }
                }
            }
        }
        {
            float mag2 = HuMagPoint2D(obj->trans.x, obj->trans.z);

            if (mag2 > 650.0f) {
                obj->trans.x = obj->trans.x * (650.0f / mag2);
                obj->trans.z = obj->trans.z * (650.0f / mag2);
            }
        }
    }
    work->unk0F4 = 0;
    Hu3DModelAttrSet(lbl_1_bss_C4->mdlId[work->playerNo + 9], 1);
    if (lbl_1_bss_BC >= 1000 && work->unk024 <= 2) {
        s32 sel = -1;
        float selD = 10000.0f;

        for (m = 0; m < 29; m++) {
            float d;
            float a;

            if (lbl_1_bss_1810[m].unk000 == 0) {
                continue;
            }
            if (lbl_1_bss_1810[m].unk014 != 0) {
                continue;
            }
            d = HuMagPoint2D(lbl_1_bss_1810[m].unk028 - obj->trans.x,
                             lbl_1_bss_1810[m].unk030 - obj->trans.z);
            if (d > 120.0f) {
                continue;
            }
            a = HuAtan(lbl_1_bss_1810[m].unk028 - obj->trans.x,
                       lbl_1_bss_1810[m].unk030 - obj->trans.z) - obj->rot.y;
            a += (a <= -180.0f) ? 360 : ((a > 180.0f) ? -360 : 0);
            if (fabs(a) > 100.0) {
                continue;
            }
            if (selD > d) {
                sel = m;
                selD = d;
            }
        }
        work->unk050 = (work->unk04C != sel) ? 0 : work->unk050;
        work->unk04C = sel;
        if (work->unk04C != -1) {
            s32 flag = 0;
            s32 t = work->unk050;
            s32 tbl[8] = { 0, 3, 4, 3, 0, 1, 2, 1 };
            s32 kind;

            if (lbl_1_bss_1810[work->unk04C].unk000 != 0) {
                work->unk0F4 = work->unk04C;
            }
            kind = lbl_1_bss_1810[work->unk04C].unk000 == 1
                ? lbl_1_data_14C[0]
                : (lbl_1_bss_1810[work->unk04C].unk000 == 2 ? lbl_1_data_14C[1] : lbl_1_data_14C[2]);
            switch (kind) {
            case 0:
                if (t % 90 < 60 && t % 12 < 6) {
                    flag = 1;
                }
                break;
            case 1:
                if (((t % 90 < 27 || (t % 90 >= 33 && t % 90 < 60)) && t % 2 == 0) || t % 90 < 3) {
                    flag = 1;
                }
                break;
            case 2:
                if ((t % 90 < 40 && t % 90 % 20 < 10)
                    || (t % 90 >= 40 && t % 90 < 80 && t % 2 == 0)) {
                    flag = 1;
                }
                break;
            case 3:
                if (t % 30 < 20) {
                    flag = 1;
                }
                break;
            case 4:
                if (t % 30 < 6) {
                    flag = 1;
                }
                break;
            }
            if (lbl_1_data_158[0] != 0) {
                if (flag) {
                    omVibrate(work->padIdx, 1, 1, 0);
                }
            } else {
                work->unk054 = flag ? work->unk054 + 1 : 0;
            }
            work->unk050++;
            lbl_1_bss_1810[work->unk04C].unk020 += (lbl_1_bss_1810[work->unk04C].unk020 == 0) ? 8 : 0;
            lbl_1_bss_1810[work->unk04C].unk024 = 1;
            Hu3DModelAttrReset(lbl_1_bss_C4->mdlId[work->playerNo + 9], 1);
            Hu3DModelPosSet(lbl_1_bss_C4->mdlId[work->playerNo + 9],
                            lbl_1_bss_1810[work->unk04C].unk028,
                            lbl_1_bss_1810[work->unk04C].unk02C,
                            lbl_1_bss_1810[work->unk04C].unk030);
            if (press != 0.0f && lbl_1_bss_1810[work->unk04C].unk014 == 0
                && lbl_1_bss_1810[work->unk04C].unk000 != 0
                && lbl_1_data_19C[work->unk04C] == 0) {
                lbl_1_data_19C[work->unk04C] = 1;
                work->unk024 = 3;
                work->unk028 = 0;
                if (lbl_1_bss_1810[work->unk04C].unk000 == 1) {
                    s32 cnt = 0;

                    for (q = 0; q < 29; q++) {
                        if (q == work->unk04C) {
                            continue;
                        }
                        cnt += (lbl_1_bss_1810[q].unk014 == 0 && lbl_1_bss_1810[q].unk000 == 1);
                    }
                    if (cnt == 5) {
                        do {
                            q = rand8() % 29;
                        } while (lbl_1_bss_1810[q].unk000 != 1 || lbl_1_bss_1810[q].unk014 != 0
                                 || q == work->unk04C);
                        for (q = 1;; q++) {
                            if (lbl_1_bss_1810[q].unk000 != 1) {
                                continue;
                            }
                            if (lbl_1_bss_1810[q].unk014 != 0) {
                                continue;
                            }
                            if (q != work->unk04C) {
                                break;
                            }
                        }
                        lbl_1_bss_1810[q].unk010 = 1;
                    }
                }
            }
        } else {
            work->unk054 = 0;
        }
    } else {
        work->unk050 = work->unk054 = 0;
    }
    if (work->unk024 == 5) {
        mode = 0;
    } else if (work->unk024 == 6) {
        mode = 9;
        obj->rot.y *= 0.8f;
        if (work->unk028 == 25) {
            for (i = 0; i < 11; i++) {
                if (work->playerNo == lbl_1_bss_1600[i].unk08 && lbl_1_bss_1600[i].unk00 == 4) {
                    lbl_1_bss_1600[i].unk00 = 6;
                    lbl_1_bss_1600[i].unk04 = 0;
                }
            }
        }
    } else if (work->unk024 == 7) {
        mode = 0;
        obj->rot.y *= 0.8f;
        if (work->unk028 == 25) {
            s32 num = 0;
            s32 idx = 0;

            for (i = 0; i < 11; i++) {
                if (work->playerNo == lbl_1_bss_1600[i].unk08 && lbl_1_bss_1600[i].unk00 == 4) {
                    lbl_1_bss_1600[i].unk00 = 5;
                    lbl_1_bss_1600[i].unk04 = 0;
                    num++;
                }
            }
            for (i = 0; i < 11; i++) {
                if (work->playerNo == lbl_1_bss_1600[i].unk08 && lbl_1_bss_1600[i].unk00 == 5) {
                    lbl_1_bss_1600[i].unk1C =
                        70.0 * sin(M_PI * (180.0f / num / 2.0f + (90.0f + 180.0f / num * idx)) / 180.0);
                    lbl_1_bss_1600[i].unk24 =
                        70.0 * cos(M_PI * (180.0f / num / 2.0f + (90.0f + 180.0f / num * idx)) / 180.0)
                        - 35.0;
                    lbl_1_bss_1600[i].unk20 = CharModelHeightGet(work->charNo) - 20.0f;
                    idx++;
                }
            }
        }
        if (work->unk028 == 181) {
            Hu3DMotionOverlaySet(obj->mdlId[0], obj->mtnId[8]);
            Hu3DMotionOverlayTimeSet(obj->mdlId[0], 0.0f);
            Hu3DModelAttrReset(obj->mdlId[0], 0x40000400);
        }
        if (work->unk028 >= 181) {
            s32 headTbl[10] = { 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 };

            mode = 7;
            obj->rot.y *= 0.8f;
            if (Hu3DMotionOverlayTimeGet(obj->mdlId[0]) >= 73.9) {
                Hu3DMotionOverlayTimeSet(obj->mdlId[0], 35.0f);
                Hu3DModelAttrReset(obj->mdlId[0], 0x40000400);
            }
            Hu3DMotionForceSet(obj->mdlId[0], lbl_1_data_210, 0x200,
                               headTbl[work->unk008] != 0
                                   ? 180 - (work->unk008 != 9) * 45
                                   : 90 - (work->unk008 != 2 && work->unk008 != 5) * 45);
        }
        obj->trans.y += 180.0f
                      * (0.866f
                         * (work->unk028 < 175
                                ? 0.0f
                                : (work->unk028 < 205
                                       ? 6.0f * ((work->unk028 - 175) / 30.0f) * (work->unk018 / 3.0f)
                                       : 6.0f * (work->unk018 / 3.0f))))
                      / 210.0f;
        obj->trans.z += 180.0f
                      * (0.5f
                         * (work->unk028 < 175
                                ? 0.0f
                                : (work->unk028 < 205
                                       ? 6.0f * ((work->unk028 - 175) / 30.0f) * (work->unk018 / 3.0f)
                                       : 6.0f * (work->unk018 / 3.0f))))
                      / 210.0f;
    }
    if (work->unk020 >= 0) {
        mode = work->unk020;
    }
    if (mode >= 0 && mode != work->unk01C) {
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[mode], lbl_1_data_FC[mode], lbl_1_data_F2[mode],
                           lbl_1_data_E8[mode] != 0 ? 0 : 0x40000001);
        work->unk01C = mode;
    }
    for (i = 0; i < 3; i++) {
        if (work->unk02C[i] > 0) {
            float r = 1.0 - (work->unk02C[i] - 1) / 30.0;
            float s;
            s32 c = i + 3;

            r = 0.5 * r + 0.5 * (1.0f - (1.0f - r) * (1.0f - r));
            s = (r < 0.75) ? r / 0.75 : 1.0;
            r = 1.0f - (1.0f - r) * (1.0f - r);
            s = 1.0f - (1.0f - s) * (1.0f - s);
            if (work->unk02C[i] == 30) {
                espDispOn(M566_ESPTBL[work->playerNo][c]);
                espDispOff(M566_ESPTBL[work->playerNo][i]);
            }
            espTPLvlSet(M566_ESPTBL[work->playerNo][c], s);
            espScaleSet(M566_ESPTBL[work->playerNo][c], 4.0f - 3.0f * r, 4.0f - 3.0f * r);
            work->unk02C[i]--;
        }
    }
}

/* 4489 insns */
void fn_1_48F8(OMOBJ *obj)
{
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 e;
    s32 ofs;
    s32 num;
    s32 hit;
    float dx;
    float dz;
    float dx2;  /* sp+0x90 -- fork B, case 2's own pair (region 1's is sp+0x98) */
    float dz2;  /* sp+0x8C */
    float wrp;  /* sp+0x88 -- written once in case 2, never read anywhere */
    float u;    /* sp+0x84 -- case 3's 1.0f - t */
    float scl;  /* f30 in case 2 */
    float ang;  /* f29 in case 2 */
    float t;    /* f31 in case 3 */
    float mscl; /* sp+0x80 -- fork C, the entity-1 ground ring scale */
    float py;   /* sp+0x7C -- fork C, entity-3's dead Y delta */
    float dy;   /* sp+0x78 -- fork C, entity-4/6 Y delta */
    float tx;   /* sp+0x74 */
    float ty;   /* sp+0x70 */
    float tz;   /* sp+0x6C */
    float ay;   /* sp+0x68 */
    float spd0; /* sp+0x64 -- entity-5 speed scale */
    float dx5;  /* sp+0x60 */
    float dy5;  /* sp+0x5C */
    float dz5;  /* sp+0x58 */
    float px;   /* f20 */
    float pz;   /* f19 */
    float dx3;  /* f27 */
    float dz3;  /* f26 */
    float dist; /* f28 */
    float spd;  /* f25 */
    float ax;   /* f24 */
    float az;   /* f23 */
    float d2;   /* f18 */
    float dist5; /* f22 */
    float spd5;  /* f21 */
    s32 cnt[4] = { 0, 0, 0, 0 };
    M566_PLAYER *p[4];

    for (i = 0; i < 4; i++) {
        p[i] = lbl_1_bss_C8[i]->data;
    }
    if (lbl_1_bss_BC == 0x3E8) {
        if (1.0f == lbl_1_bss_0[0] || 2.0f == lbl_1_bss_0[0]) {
            for (i = 0; i < 8; i++) {
                if (1.0f == lbl_1_bss_0[0]) {
                    Hu3DModelAttrReset(obj->mdlId[i + 0x50], HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrSet(obj->mdlId[i + 0x50], HU3D_ATTR_DISPOFF);
                }
            }
        }
    }
    for (i = 0; i < 5; i++) {
        if (lbl_1_data_230[i] == -1) {
            lbl_1_data_230[i] = rand8() % 128 + 20;
        }
        if (lbl_1_data_21C[i] == 0) {
            lbl_1_data_230[i]--;
            if (lbl_1_data_230[i] == 0) {
                lbl_1_data_21C[i] = 1;
                lbl_1_data_230[i] = (rand8() % 4 + 1) * 16;
                if (lbl_1_bss_1810[lbl_1_data_244[i]].unk020 <= lbl_1_data_230[i]) {
                    lbl_1_bss_1810[lbl_1_data_244[i]].unk020 =
                        lbl_1_data_230[i] + lbl_1_bss_1810[lbl_1_data_244[i]].unk020 % 8;
                    lbl_1_bss_1810[lbl_1_data_244[i]].unk024 = 0;
                }
                while (1) {
                    lbl_1_data_244[i] = rand8() % 28 + 1;
                    for (j = 0; j < 5; j++) {
                        if (i != j && lbl_1_data_244[i] == lbl_1_data_244[j]) {
                            break;
                        }
                    }
                    if (j == 5) {
                        break;
                    }
                }
            }
        } else if (lbl_1_data_21C[i] == 1) {
            lbl_1_data_230[i]--;
            /* Retail dead code: the condition is evaluated and thrown away.
             * The first test keeps its branch, the second is materialised into
             * a register that is never read. */
            if (lbl_1_bss_1810[lbl_1_data_244[i]].unk000 != 0 &&
                lbl_1_bss_1810[lbl_1_data_244[i]].unk014 == 0) {
            }
            if (lbl_1_data_230[i] == 0) {
                lbl_1_data_21C[i] = 0;
                lbl_1_data_230[i] = rand8() % 128 + 60;
            }
        }
    }
    for (i = 0; i < 29; i++) {
        k = (lbl_1_bss_1810[i].unk024 != 0) ? 6 : 4;
        Hu3DModelRotSet(obj->mdlId[i + 29], 0.0f, 0.0f,
            k * sin(M_PI * (-360.0f * (lbl_1_bss_1810[i].unk020 % 8) / 8.0f) / 180.0));
        lbl_1_bss_1810[i].unk020 -= (lbl_1_bss_1810[i].unk020 > 0);
    }
    for (i = 0; i < 29; i++) {
        switch (lbl_1_bss_1810[i].unk014) {
        case 0:
            break;
        case 1:
            if (lbl_1_bss_1810[i].unk018 == 0) {
                for (j = 0; j < lbl_1_bss_1810[i].unk010 + 1; j++) {
                    n = (j == 0) ? lbl_1_bss_1810[i].unk004 : 10;
                    lbl_1_bss_1600[n].unk00 = 2;
                    lbl_1_bss_1600[n].unk04 = 0;
                    lbl_1_bss_1600[n].unk08 = lbl_1_bss_1810[i].unk01C;
                    lbl_1_bss_1600[n].unk0C = j;
                    e = (lbl_1_bss_1810[i].unk010 != 0) ? (j * 2 - 1) * 15 : 0;
                    lbl_1_bss_1600[n].unk10 = lbl_1_bss_1810[i].unk028 + e;
                    lbl_1_bss_1600[n].unk14 = lbl_1_bss_1810[i].unk02C;
                    lbl_1_bss_1600[n].unk18 = lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_1600[n].unk1C = lbl_1_bss_1600[n].unk24 = 0.0f;
                    lbl_1_bss_1600[n].unk20 =
                        100.0f + CharModelHeightGet((s16)p[lbl_1_bss_1810[i].unk01C]->charNo);
                    dx = lbl_1_bss_1600[n].unk10 - lbl_1_bss_C8[lbl_1_bss_1600[n].unk08]->trans.x;
                    dz = lbl_1_bss_1600[n].unk18 - lbl_1_bss_C8[lbl_1_bss_1600[n].unk08]->trans.z;
                    lbl_1_bss_1600[n].unk28 = (i == 0) ? 0.0 : (180.0 * (atan2(dx, dz) / M_PI));
                    if (lbl_1_bss_1600[n].unk28 < -180.0f) {
                        ofs = 360;
                    } else {
                        ofs = (lbl_1_bss_1600[n].unk28 > 180.0f) ? -360 : 0;
                    }
                    lbl_1_bss_1600[n].unk28 += ofs;
                    lbl_1_bss_1600[n].unk2C = sqrtf(dx * dx + dz * dz);
                    Hu3DModelPosSet(obj->mdlId[n + 0x3A], lbl_1_bss_1600[n].unk10,
                        lbl_1_bss_1600[n].unk14, lbl_1_bss_1600[n].unk18);
                    Hu3DModelRotSet(obj->mdlId[n + 0x3A], 0.0f,
                        180.0f + lbl_1_bss_C8[lbl_1_bss_1810[i].unk01C]->rot.y, 0.0f);
                    Hu3DMotionTimeSet(obj->mdlId[n + 0x3A], 0.0f);
                    Hu3DModelAttrReset(obj->mdlId[n + 0x3A], HU3D_ATTR_DISPOFF);
                }
            }
            /* Retail dead code, same shape as the one above. */
            if (lbl_1_bss_1810[i].unk018 == 6 && lbl_1_bss_BC > 0x3EA) {
            }
            if (lbl_1_bss_1810[i].unk018 == 12) {
                num = 0;
                for (j = 0; j < 11; j++) {
                    hit = 0;
                    if (lbl_1_bss_1600[j].unk08 == lbl_1_bss_1810[i].unk01C &&
                        lbl_1_bss_1600[j].unk00 >= 2) {
                        hit = 1;
                    }
                    num += hit;
                }
                j = 0;
                for (k = 0; k < 11; k++) {
                    if (lbl_1_bss_1600[k].unk08 == lbl_1_bss_1810[i].unk01C &&
                        lbl_1_bss_1600[k].unk00 != 0 && lbl_1_bss_1600[k].unk00 != 1) {
                        lbl_1_bss_1600[k].unk00 = (lbl_1_bss_BC == 0x3EA) ? 1 : 3;
                        lbl_1_bss_1600[k].unk04 = 0;
                        if (num == 2) {
                            e = -90;
                        } else {
                            e = (num == 4) ? -45 : 0;
                        }
                        lbl_1_bss_1600[k].unk1C =
                            (num > 1) * (30.0 * sin(M_PI * (j * (360.0f / num) + e) / 180.0));
                        e = (num == 2) ? -90 : ((num == 4) ? -45 : 0);
                        lbl_1_bss_1600[k].unk24 =
                            (num > 1) * (30.0 * cos(M_PI * (j * (360.0f / num) + e) / 180.0));
                        j++;
                    }
                }
                if (lbl_1_bss_E0[7].unk00 < 3) {
                    lbl_1_bss_E0[7].unk04[lbl_1_bss_E0[7].unk00] = lbl_1_bss_1810[i].unk028;
                    lbl_1_bss_E0[7].unk10[lbl_1_bss_E0[7].unk00] = lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_E0[7].unk00++;
                }
                if (lbl_1_bss_BC <= 0x3EA) {
                    lbl_1_data_144[0] = HuAudFXPlay(0x8E1);
                } else if (lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9].unk00 < 3) {
                    lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9]
                        .unk04[lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9].unk00] =
                        lbl_1_bss_1600[lbl_1_bss_1810[i].unk004].unk10;
                    lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9]
                        .unk10[lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9].unk00] =
                        lbl_1_bss_1600[lbl_1_bss_1810[i].unk004].unk18;
                    lbl_1_bss_E0[lbl_1_bss_1810[i].unk004 + 9].unk00++;
                }
            }
            if (lbl_1_bss_1810[i].unk018 >= 10 && p[lbl_1_bss_1810[i].unk01C]->unk024 != 3) {
                lbl_1_bss_1810[i].unk000 = 0;
                lbl_1_bss_1810[i].unk014 = 0;
                lbl_1_bss_1810[i].unk018 = 0;
            }
            break;
        case 2:
            /* FORK B: region 2, reference .L_00005BBC (0x5BBC). */
            if (lbl_1_bss_1810[i].unk018 == 0) {
                Hu3DModelPosSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45],
                    lbl_1_bss_1810[i].unk028, lbl_1_bss_1810[i].unk02C,
                    lbl_1_bss_1810[i].unk030);
                Hu3DModelRotSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], 0.0f,
                    180.0f + lbl_1_bss_C8[lbl_1_bss_1810[i].unk01C]->rot.y, 0.0f);
                Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], 0.0f);
                Hu3DModelAttrReset(
                    obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], HU3D_ATTR_DISPOFF);
                if (lbl_1_bss_1810[i].unk00C != -1) {
                    Hu3DModelHookReset(obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x58]);
                    Hu3DModelHookSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45],
                        lbl_1_data_25C, obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x58]);
                    Hu3DModelAttrReset(
                        obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x58], HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x58], 0.0f);
                }
                if (lbl_1_bss_E0[8].unk00 < 3) {
                    lbl_1_bss_E0[8].unk04[lbl_1_bss_E0[8].unk00] =
                        lbl_1_bss_1810[i].unk028;
                    lbl_1_bss_E0[8].unk10[lbl_1_bss_E0[8].unk00] =
                        lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_E0[8].unk00++;
                }
            }
            if (lbl_1_bss_1810[i].unk018 >= 0 && lbl_1_bss_1810[i].unk018 <= 3) {
                scl = 0.75 * (0.5 + 0.5 * (lbl_1_bss_1810[i].unk018 / 3.0f));
                Hu3DModelScaleSet(
                    obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], scl, scl, scl);
                /* Retail: the guard names unk00C but the model scaled again is
                 * still the unk004 one. Transcribed verbatim. */
                if (lbl_1_bss_1810[i].unk00C != -1) {
                    Hu3DModelScaleSet(
                        obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], scl, scl, scl);
                }
            }
            if (lbl_1_bss_1810[i].unk000 != 0 && lbl_1_bss_1810[i].unk018 >= 30 &&
                p[lbl_1_bss_1810[i].unk01C]->unk024 != 3) {
                lbl_1_bss_1810[i].unk000 = 0;
                Hu3DModelAttrSet(
                    obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x45], HU3D_ATTR_DISPOFF);
                if (lbl_1_bss_1810[i].unk00C != -1) {
                    Hu3DModelAttrReset(
                        obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x58], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(
                        obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x5C], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x5C],
                        lbl_1_bss_1810[i].unk028, lbl_1_bss_1810[i].unk02C,
                        lbl_1_bss_1810[i].unk030);
                    Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x5C], 0.0f);
                }
                if (lbl_1_bss_E0[3].unk00 < 3) {
                    lbl_1_bss_E0[3].unk04[lbl_1_bss_E0[3].unk00] =
                        lbl_1_bss_1810[i].unk028;
                    lbl_1_bss_E0[3].unk10[lbl_1_bss_E0[3].unk00] =
                        lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_E0[3].unk00++;
                }
            }
            if (lbl_1_bss_1810[i].unk018 >= 30 && lbl_1_bss_1810[i].unk018 <= 40) {
                for (j = 0; j < 4; j++) {
                    dx2 = lbl_1_bss_1810[i].unk028 - lbl_1_bss_C8[j]->trans.x;
                    dz2 = lbl_1_bss_1810[i].unk030 - lbl_1_bss_C8[j]->trans.z;
                    if (dx2 * dx2 + dz2 * dz2 <= 14400.0f && p[j]->unk024 == 2) {
                        ang = 180.0 * (atan2(dx2, dz2) / M_PI);
                        /* Retail: computed and stored, never read again. */
                        /* `<=` here, not `<`: the reference emits
                         * `cror eq,lt,eq` + `bne` at 0x6350. Region 1's copy of
                         * the same wrap idiom is a plain `<` (`bge`, no cror). */
                        wrp = fabs((ang <= -180.0f)
                                       ? (360.0f + ang)
                                       : ((ang > 180.0f) ? (ang - 360.0f) : ang));
                        lbl_1_bss_C8[j]->rot.y = ang;
                        p[j]->unk024 = 4;
                        p[j]->unk028 = 0;
                        p[j]->unk04C = i;
                    }
                }
            }
            if (lbl_1_bss_1810[i].unk018 == 0x41) {
                if (lbl_1_bss_1810[i].unk00C != -1) {
                    lbl_1_data_124[lbl_1_bss_1810[i].unk00C] = 0;
                    Hu3DModelAttrSet(
                        obj->mdlId[lbl_1_bss_1810[i].unk00C + 0x5C], HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_1810[i].unk014 = 0;
            }
            break;
        case 3:
            /* FORK B: reference .L_000064C8 (0x64C8). */
            if (lbl_1_bss_1810[i].unk018 == 0) {
                Hu3DModelPosSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x50],
                    lbl_1_bss_1810[i].unk028, lbl_1_bss_1810[i].unk02C,
                    lbl_1_bss_1810[i].unk030);
                Hu3DModelRotSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x50], 0.0f,
                    180.0f + lbl_1_bss_C8[lbl_1_bss_1810[i].unk01C]->rot.y, 0.0f);
                Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x50], 0.0f);
                Hu3DModelAttrReset(
                    obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x50], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_1810[i].unk018 == 8) {
                if (lbl_1_bss_E0[4].unk00 < 3) {
                    lbl_1_bss_E0[4].unk04[lbl_1_bss_E0[4].unk00] =
                        lbl_1_bss_1810[i].unk028;
                    lbl_1_bss_E0[4].unk10[lbl_1_bss_E0[4].unk00] =
                        lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_E0[4].unk00++;
                }
            }
            /* Retail: `>= 18 || <= 80` is always true, so the else arm at
             * 0x691C is dead. Transcribed verbatim. */
            if (lbl_1_bss_1810[i].unk018 >= 18 || lbl_1_bss_1810[i].unk018 <= 80) {
                Hu3DModelAttrReset(
                    obj->mdlId[lbl_1_bss_1810[i].unk01C + 0x60], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(obj->mdlId[lbl_1_bss_1810[i].unk01C + 0x60],
                    0.35 * lbl_1_bss_1810[i].unk028 +
                        0.65 * lbl_1_bss_C8[lbl_1_bss_1810[i].unk01C]->trans.x,
                    70.0f + lbl_1_bss_1810[i].unk02C,
                    60.0 +
                        (0.35 * lbl_1_bss_1810[i].unk030 +
                            0.65 * lbl_1_bss_C8[lbl_1_bss_1810[i].unk01C]->trans.z));
                Hu3DModelScaleSet(
                    obj->mdlId[lbl_1_bss_1810[i].unk01C + 0x60], 0.4f, 0.4f, 0.4f);
                if (lbl_1_bss_1810[i].unk018 == 18 || lbl_1_bss_1810[i].unk018 == 40) {
                    Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_1810[i].unk01C + 0x60], 0.0f);
                }
            } else {
                Hu3DModelAttrSet(
                    obj->mdlId[lbl_1_bss_1810[i].unk01C + 0x60], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_1810[i].unk018 >= 10 && lbl_1_bss_1810[i].unk018 <= 0x5A) {
                Quaternion quat;
                Vec rot = { 0.0f, 1.0f, 0.0f };
                Mtx mtx;

                t = (lbl_1_bss_1810[i].unk018 - 10) / 80.0f;
                u = 1.0f - t;
                C_QUATRotAxisRad(&quat, &rot, 0.0f);
                Hu3DModelPosSet(obj->mdlId[i + 29],
                    t * lbl_1_bss_1810[i].unk028 + u * lbl_1_bss_1810[i].unk034,
                    400.0f * (1.0f - (2.0f * t - 1.0f) * (2.0f * t - 1.0f)) +
                        (t * lbl_1_bss_1810[i].unk02C + u * lbl_1_bss_1810[i].unk038),
                    t * lbl_1_bss_1810[i].unk030 + u * lbl_1_bss_1810[i].unk03C);
                C_QUATSlerp(&lbl_1_bss_1810[i].unk04C, &quat, &quat, t);
                PSMTXQuat(mtx, &quat);
                Hu3DMtxRotGet(mtx, &rot);
                Hu3DModelRotSet(obj->mdlId[i + 29], rot.x, rot.y, rot.z);
            }
            if (lbl_1_bss_1810[i].unk018 == 0x5A) {
                Hu3DModelAttrSet(
                    obj->mdlId[lbl_1_bss_1810[i].unk004 + 0x50], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1810[i].unk014 = 0;
                if (lbl_1_bss_E0[5].unk00 < 3) {
                    lbl_1_bss_E0[5].unk04[lbl_1_bss_E0[5].unk00] =
                        lbl_1_bss_1810[i].unk028;
                    lbl_1_bss_E0[5].unk10[lbl_1_bss_E0[5].unk00] =
                        lbl_1_bss_1810[i].unk030;
                    lbl_1_bss_E0[5].unk00++;
                }
            }
            break;
        case 4:
            break;
        }
        lbl_1_bss_1810[i].unk018++;
    }
    for (i = 0; i < 16; i++) {
        Hu3DModelAttrSet(lbl_1_bss_C4->mdlId[i + 13], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(lbl_1_bss_C4->mdlId[8], HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(obj->mdlId[0x3A], 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 11; i++) {
        switch (lbl_1_bss_1600[i].unk00) {
        case 0:
            break;
        case 1:
            mscl = 1.6f * (1.0f - lbl_1_bss_1600[i].unk14 / 1000.0f);
            lbl_1_bss_1600[i].unk14 += 4.0f;
            Hu3DModelPosSet(obj->mdlId[i + 0x3A], lbl_1_bss_1600[i].unk10,
                lbl_1_bss_1600[i].unk14, lbl_1_bss_1600[i].unk18);
            Hu3DModelRotSet(obj->mdlId[i + 0x3A], 0.0f, 0.0f, 0.0f);
            Hu3DModelScaleSet(obj->mdlId[8], mscl, mscl, mscl);
            Hu3DModelPosSet(obj->mdlId[8], lbl_1_bss_1600[i].unk10, 1000.0f,
                lbl_1_bss_1600[i].unk18);
            Hu3DModelRotSet(obj->mdlId[8], 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_C4->mdlId[8], HU3D_ATTR_DISPOFF);
            if (rand8() % 3 == 0) {
                Hu3DModelAttrReset(obj->mdlId[i + 0x3A], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_1600[i].unk14 > 1000.0f) {
                lbl_1_bss_1600[i].unk00 = 0;
                Hu3DModelAttrSet(obj->mdlId[i + 0x3A], HU3D_ATTR_DISPOFF);
                HuAudFXStop(lbl_1_data_144[0]);
            }
            break;
        case 2:
            break;
        case 3:
            px = lbl_1_bss_1600[i].unk10;
            py = lbl_1_bss_1600[i].unk14;
            pz = lbl_1_bss_1600[i].unk18;
            lbl_1_bss_1600[i].unk10 -= lbl_1_bss_1600[i].unk2C *
                sin(M_PI * lbl_1_bss_1600[i].unk28 / 180.0);
            lbl_1_bss_1600[i].unk18 -= lbl_1_bss_1600[i].unk2C *
                cos(M_PI * lbl_1_bss_1600[i].unk28 / 180.0);
            lbl_1_bss_1600[i].unk28 += 360.0 *
                (6.0f / ((lbl_1_bss_1600[i].unk0C != 0) ? 2 : 1) /
                    (M_PI * lbl_1_bss_1600[i].unk2C));
            lbl_1_bss_1600[i].unk28 += (lbl_1_bss_1600[i].unk28 < -360.0f)
                                           ? 360
                                           : ((lbl_1_bss_1600[i].unk28 > 360.0f) ? -360 : 0);
            lbl_1_bss_1600[i].unk2C -=
                (lbl_1_bss_1600[i].unk14 > lbl_1_bss_1600[i].unk20 - 100.0f &&
                    lbl_1_bss_1600[i].unk2C > 20.0f)
                    ? 2
                    : 0;
            lbl_1_bss_1600[i].unk10 += lbl_1_bss_1600[i].unk2C *
                sin(M_PI * lbl_1_bss_1600[i].unk28 / 180.0);
            lbl_1_bss_1600[i].unk18 += lbl_1_bss_1600[i].unk2C *
                cos(M_PI * lbl_1_bss_1600[i].unk28 / 180.0);
            lbl_1_bss_1600[i].unk14 += 4.0f;
            px = lbl_1_bss_1600[i].unk10 - px;
            py = lbl_1_bss_1600[i].unk14 - py;
            pz = lbl_1_bss_1600[i].unk18 - pz;
            Hu3DModelPosSet(obj->mdlId[i + 0x3A], lbl_1_bss_1600[i].unk10,
                lbl_1_bss_1600[i].unk14, lbl_1_bss_1600[i].unk18);
            if (0.0f != px || 0.0f != pz) {
                Hu3DModelRotSet(obj->mdlId[i + 0x3A], 0.0f,
                    180.0 * (atan2(px, pz) / M_PI), 0.0f);
            }
            if (lbl_1_bss_1600[i].unk14 > lbl_1_bss_1600[i].unk20) {
                lbl_1_bss_1600[i].unk00 = 4;
                lbl_1_bss_1600[i].unk04 = 0;
                if (i != 10) {
                    if (lbl_1_bss_E0[i + 9].unk1C != -1) {
                        HuAudFXStop(lbl_1_bss_E0[i + 9].unk1C);
                    }
                }
            }
            break;
        case 4:
        case 6:
            dx3 = lbl_1_bss_1600[i].unk1C +
                lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.x -
                lbl_1_bss_1600[i].unk10;
            dy = lbl_1_bss_1600[i].unk20 - lbl_1_bss_1600[i].unk14;
            dz3 = lbl_1_bss_1600[i].unk24 +
                lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.z -
                lbl_1_bss_1600[i].unk18;
            dist = sqrtf(dz3 * dz3 + (dx3 * dx3 + dy * dy));
            spd = 1.0f;
            spd = (dist > 1.0f) ? (dist - 1.0f) / 8.0f : dist;
            if (spd > 0.0f) {
                lbl_1_bss_1600[i].unk10 += spd * (dx3 / dist);
                lbl_1_bss_1600[i].unk14 += spd * (dy / dist);
                lbl_1_bss_1600[i].unk18 += spd * (dz3 / dist);
            }
            Hu3DModelPosSet(obj->mdlId[i + 0x3A], lbl_1_bss_1600[i].unk10,
                lbl_1_bss_1600[i].unk14, lbl_1_bss_1600[i].unk18);
            if (0.0f != dx3 || 0.0f != dz3) {
                Hu3DModelRotSet(obj->mdlId[i + 0x3A], 0.0f,
                    180.0 * (atan2(dx3, dz3) / M_PI), 0.0f);
            }
            if (lbl_1_bss_1600[i].unk00 == 6 && lbl_1_data_138[0] != 4 &&
                lbl_1_data_138[0] != -1 &&
                lbl_1_data_138[0] != lbl_1_bss_1600[i].unk08) {
                tx = lbl_1_bss_C8[lbl_1_data_138[0]]->trans.x;
                ty = 40.0f + lbl_1_bss_C8[lbl_1_data_138[0]]->trans.y;
                tz = lbl_1_bss_C8[lbl_1_data_138[0]]->trans.z;
                ax = lbl_1_bss_1600[i].unk10 - tx;
                ay = (lbl_1_bss_1600[i].unk14 - ty) / 2.0f;
                az = (lbl_1_bss_1600[i].unk18 - tz) / 1.5f;
                d2 = sqrtf(az * az + (ax * ax + ay * ay));
                if (d2 < 90.0f) {
                    if (0.0f == ax && 0.0f == az) {
                        ax = rand8() % 2 * 2 - 1;
                        az = 0.0f;
                    }
                    lbl_1_bss_1600[i].unk10 = tx + 90.0f * (ax / d2);
                    lbl_1_bss_1600[i].unk14 = ty + 2.0f * (90.0f * (ay / d2));
                    lbl_1_bss_1600[i].unk18 = tz + 1.5f * (90.0f * (az / d2));
                }
            }
            break;
        case 5:
            spd0 = (p[lbl_1_data_138[0]]->unk028 < 0x53) ? 0.5 : 1.0;
            dx5 = spd0 * lbl_1_bss_1600[i].unk1C +
                lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.x -
                lbl_1_bss_1600[i].unk10;
            dy5 = spd0 * lbl_1_bss_1600[i].unk20 - lbl_1_bss_1600[i].unk14;
            dz5 = lbl_1_bss_1600[i].unk24 +
                lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.z -
                lbl_1_bss_1600[i].unk18;
            dist5 = sqrtf(dz5 * dz5 + (dx5 * dx5 + dy5 * dy5));
            spd5 = 1.0f;
            spd5 = (dist5 > 32.0f) ? 4.0f : dist5 / 8.0f;
            if (spd5 > 0.0f) {
                lbl_1_bss_1600[i].unk10 += spd5 * (dx5 / dist5);
                lbl_1_bss_1600[i].unk14 += spd5 * (dy5 / dist5);
                lbl_1_bss_1600[i].unk18 += spd5 * (dz5 / dist5);
            }
            lbl_1_bss_1600[i].unk14 +=
                (p[lbl_1_data_138[0]]->unk028 < 0xAF)
                    ? 0.0f
                    : ((p[lbl_1_data_138[0]]->unk028 < 0xD7)
                              ? 6.0f * ((p[lbl_1_data_138[0]]->unk028 - 0xAF) / 40.0f) *
                                    (p[lbl_1_data_138[0]]->unk018 / 3.0f)
                              : 6.0f * (p[lbl_1_data_138[0]]->unk018 / 3.0f));
            lbl_1_bss_1600[i].unk20 +=
                (p[lbl_1_data_138[0]]->unk028 < 0xAF)
                    ? 0.0f
                    : ((p[lbl_1_data_138[0]]->unk028 < 0xD7)
                              ? 6.0f * ((p[lbl_1_data_138[0]]->unk028 - 0xAF) / 40.0f) *
                                    (p[lbl_1_data_138[0]]->unk018 / 3.0f)
                              : 6.0f * (p[lbl_1_data_138[0]]->unk018 / 3.0f));
            Hu3DModelPosSet(obj->mdlId[i + 0x3A], lbl_1_bss_1600[i].unk10,
                lbl_1_bss_1600[i].unk14, lbl_1_bss_1600[i].unk18);
            Hu3DModelRotSet(obj->mdlId[i + 0x3A], 0.0f, 0.0f, 0.0f);
            break;
        }
        lbl_1_bss_1600[i].unk04++;
        if (cnt[lbl_1_bss_1600[i].unk08] < 4 && lbl_1_bss_1600[i].unk00 == 5 &&
            p[lbl_1_data_138[0]]->unk028 >= 0x3C) {
            s32 n2 = lbl_1_bss_1600[i].unk08 * 4 + cnt[lbl_1_bss_1600[i].unk08];

            n2 += 13;
            {
            s32 oy[10] = { -10, 0, 30, -50, -10, -35, 60, -70, -55, -120 };
            s32 oz[10] = { 0, 0, 0, -15, -35, 0, -20, -5, 0, -30 };
            Vec cpos;
            Vec spos;

            lbl_1_bss_C++;
            lbl_1_bss_C %= 4;
            cpos.x = lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.x;
            cpos.y = 80.0f + lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.y +
                oy[p[lbl_1_bss_1600[i].unk08]->unk008] -
                ((lbl_1_bss_BC >= 0x3ED &&
                     p[lbl_1_bss_1600[i].unk08]->unk008 == 6)
                        ? 90
                        : 0);
            cpos.z = lbl_1_bss_C8[lbl_1_bss_1600[i].unk08]->trans.z - 30.0f +
                oz[p[lbl_1_bss_1600[i].unk08]->unk008] -
                ((lbl_1_bss_BC >= 0x3ED &&
                     p[lbl_1_bss_1600[i].unk08]->unk008 == 7)
                        ? 25
                        : 0);
            spos.x = lbl_1_bss_1600[i].unk10 - cpos.x;
            spos.y = lbl_1_bss_1600[i].unk14 - cpos.y;
            spos.z = lbl_1_bss_1600[i].unk18 - cpos.z;
            Hu3DModelPosSet(lbl_1_bss_C4->mdlId[n2], cpos.x, cpos.y, cpos.z);
            Hu3DModelRotSet(lbl_1_bss_C4->mdlId[n2],
                180.0 * (atan2(spos.y, sqrtf(spos.x * spos.x + spos.z * spos.z)) / M_PI),
                180.0 + 180.0 * (atan2(spos.x, spos.z) / M_PI), 0.0f);
            Hu3DModelScaleSet(lbl_1_bss_C4->mdlId[n2], 1.0f, 1.0f,
                sqrtf(spos.z * spos.z + (spos.x * spos.x + spos.y * spos.y)) / 150.0f);
            Hu3DModelAttrReset(lbl_1_bss_C4->mdlId[n2], HU3D_ATTR_DISPOFF);
            cnt[lbl_1_bss_1600[i].unk08]++;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_data_124[i] += (lbl_1_data_124[i] > 0);
    }
    for (i = 0; i < 128; i++) {
        if (lbl_1_bss_600[i].unk00 != 0) {
            lbl_1_bss_600[i].unk00++;
            lbl_1_bss_600[i].unk08 += lbl_1_bss_600[i].unk14;
            lbl_1_bss_600[i].unk0C += lbl_1_bss_600[i].unk18;
            lbl_1_bss_600[i].unk10 += lbl_1_bss_600[i].unk1C;
            lbl_1_bss_600[i].unk14 *= 0.85f;
            lbl_1_bss_600[i].unk18 *= 0.85f;
            lbl_1_bss_600[i].unk1C *= 0.85f;
            lbl_1_bss_600[i].unk04 *= 0.95f;
            if (lbl_1_bss_600[i].unk04 <= 0) {
                lbl_1_bss_600[i].unk00 = 0;
            }
        }
    }
    if (lbl_1_bss_BC == 0x3EA || (lbl_1_bss_BC == 0x3EB && 2472.0f != CZoomM[1])) {
        CZoomM[1] = 77.25f + 0.96875f * CZoomM[1];
        CRotM[1].x = 0.96875f * CRotM[1].x - 1.01875;
        CenterM[1].y = 2.625f + 0.96875f * CenterM[1].y;
    } else if (lbl_1_bss_BC == 0x3ED && lbl_1_data_138[0] != 4) {
        if (-10000.0f == lbl_1_data_258) {
            lbl_1_data_258 = lbl_1_bss_C8[lbl_1_data_138[0]]->trans.z - 25.0f;
        }
        CZoomM[1] = 112.5f + 0.875f * CZoomM[1];
        CenterM[1].x = 0.875f * CenterM[1].x +
            0.125f * lbl_1_bss_C8[lbl_1_data_138[0]]->trans.x;
        CenterM[1].y = 0.875f * CenterM[1].y +
            0.125f * (866.0f * p[lbl_1_data_138[0]]->unk018 / 3.0f);
        CenterM[1].z = 0.875f * CenterM[1].z +
            0.125f * (lbl_1_data_258 + 500.0f * p[lbl_1_data_138[0]]->unk018 / 3.0f);
        CRotM[1].x = 0.9375f * CRotM[1].x - 3.75f;
    }
    for (i = 0; i < 29; i++) {
        if (lbl_1_bss_1810[i].unk000 == 0 ||
            (lbl_1_bss_1810[i].unk014 != 0 && lbl_1_bss_1810[i].unk014 != 4)) {
            Hu3DModelShadowDispOff(obj->mdlId[i + 29]);
        } else {
            Hu3DModelShadowDispOn(obj->mdlId[i + 29]);
        }
    }
}

/* CodeWarrior appends a switch jumptable where the FUNCTION compiles, so these
 * two OSReport string literals must sit BELOW fn_1_48F8 or they precede the table
 * and it lands at 0x2A8 instead of 0x268. In the real source they are plainly
 * literals inside fn_1_8F1C and ObjectSetup, both compiled after fn_1_48F8.
 * Position only -- no initialiser is changed. (fork C) */
/* 0x284 */ char lbl_1_data_284[] = "*** main mode error(%d)!!\n";
/* 0x29F */ char lbl_1_data_29F[] = "******* M566 ObjectSetup *********\n";

/* 1025 insns */
void fn_1_8F1C(void)
{
    s32 i;
    s32 j;
    M566_PLAYER *p[4];
    s32 vol;
    s32 vol2;
    s32 seNo;

    for (i = 0; i < 4; i++) {
        p[i] = lbl_1_bss_C8[i]->data;
    }
    for (i = 0; i < 41; i++) {
        s32 seTbl[41] = { 0x8E1, 0x8E2, 0x8E4, 0x8E6, 0x2D8, 0x8E8, 0x8E9, 0x2C4, 0x2D7 };

        if (lbl_1_bss_E0[i].unk00 > 3) {
            lbl_1_bss_E0[i].unk00 = 3;
        }
        if (lbl_1_bss_E0[i].unk00 > 0) {
            if (i >= 9 || seTbl[i] != -1) {
                seNo = HuAudFXPlay(seTbl[(i >= 9) ? 2 : i]);
                lbl_1_bss_E0[i].unk1C = seNo;
                HuAudFXPanning(seNo, (s16)(0.5 + (64.0f + 63.0f * (0.25f * (lbl_1_bss_E0[i].unk04[lbl_1_bss_E0[i].unk00 - 1] / 650.0f)))));
                vol = (s32)(0.5 + (104.0f + 23.0f * (1.0f + lbl_1_bss_E0[i].unk10[lbl_1_bss_E0[i].unk00 - 1] / 550.0f)));
                vol = (vol < 0) ? 0 : ((vol >= 127) ? 127 : vol);
                HuAudFXVolSet(seNo, (s16)vol);
            }
            lbl_1_bss_E0[i].unk00--;
        }
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_BC == 0x3ED && lbl_1_data_138[0] != 4) {
            CharModelVoicePanSet((s16)p[i]->charNo, 0x40);
            CharModelVoiceVolSet((s16)p[i]->charNo, 0x7F);
        } else {
            CharModelVoicePanSet((s16)p[i]->charNo, (s16)(0.5 + (64.0f + 63.0f * (0.25f * (lbl_1_bss_C8[i]->trans.x / 650.0f)))));
            vol2 = (s32)(0.5 + (104.0f + 23.0f * (1.0f + lbl_1_bss_C8[i]->trans.z / 550.0f)));
            vol2 = (vol2 < 0) ? 0 : ((vol2 >= 127) ? 127 : vol2);
            CharModelVoiceVolSet((s16)p[i]->charNo, (s16)vol2);
        }
    }
    if (omSysExitReq != 0) {
        if (!WipeCheckEnd()) {
            if (lbl_1_bss_8 == 0) {
                HuAudFadeOut(1000);
                lbl_1_data_148[0] = 1;
                lbl_1_bss_8 = 1;
            }
        }
    }
    switch (lbl_1_bss_BC) {
    case 0x3E8:
        lbl_1_bss_0[0] += 1.0f;
        if (5.0f == lbl_1_bss_0[0]) {
            HuAudFXPlay(0x8EA);
        }
        if (!WipeCheckEnd()) {
            lbl_1_bss_BC++;
            lbl_1_bss_0[0] = 0.0f;
        }
        break;
    case 0x3E9:
        lbl_1_bss_0[0] += 1.0f;
        if (lbl_1_bss_0[0] >= 180.0f) {
            lbl_1_bss_BC++;
            lbl_1_bss_0[0] = 0.0f;
        }
        break;
    case 0x3EA:
        lbl_1_bss_0[0] += 1.0f;
        if (5.0f == lbl_1_bss_0[0] && lbl_1_bss_B4 < 0) {
            lbl_1_bss_B4 = GameMesMgStartCreate();
        }
        if (lbl_1_bss_0[0] >= 5.0f && lbl_1_data_140[0] == -1) {
            lbl_1_data_140[0] = HuAudSStreamPlay(0x34);
        }
        if (lbl_1_bss_0[0] >= 5.0f) {
            if (GameMesStatGet(lbl_1_bss_B4)) {
                break;
            }
            if (lbl_1_bss_B4 < 0) {
                break;
            }
            lbl_1_bss_BC++;
            lbl_1_bss_B0 = 0xE10;
            lbl_1_bss_B4 = -1;
            lbl_1_bss_0[0] = 0.0f;
            for (i = 0; i < 4; i++) {
                p[i]->unk024 = 2;
                for (j = 0; j < 7; j++) {
                    if (j < 3 || j > 5) {
                        espDispOn((s16)((s32 (*)[7])lbl_1_data_1C)[i][j]);
                    }
                }
                MgScoreWinDispSet(lbl_1_bss_84[i], 1);
            }
        }
        break;
    case 0x3EB:
        lbl_1_bss_0[0] += 1.0f;
        if (lbl_1_data_134 == -1 && lbl_1_bss_B0 == 0xE10) {
            lbl_1_data_134 = GameMesTimerCreate(lbl_1_bss_B0 / 60);
            GameMesPosSet(lbl_1_data_134, 288.0f, 64.0f);
        }
        if (lbl_1_data_134 != -1 && lbl_1_bss_B0 <= 0xE10) {
            GameMesTimerValueSet(lbl_1_data_134, (lbl_1_bss_B0 + 0x3A) / 60);
        }
        lbl_1_bss_B0--;
        i = 0;
        j = rand8() % 4;
        for (; i < 4; i++) {
            if (p[i]->unk018 >= 3) {
                if (lbl_1_data_138[0] == -1) {
                    lbl_1_data_138[0] = i;
                } else if (p[i]->unk018 > lbl_1_data_138[0]) {
                    lbl_1_data_138[0] = i;
                }
            }
        }
        if (lbl_1_bss_B0 > 0 && lbl_1_data_138[0] == -1) {
            break;
        }
        lbl_1_bss_BC = 0x3EC;
        lbl_1_bss_0[0] = 0.0f;
        lbl_1_data_138[0] = (lbl_1_data_138[0] != -1) ? lbl_1_data_138[0] : 4;
        break;
    case 0x3EC:
        if (lbl_1_bss_B4 < 0 && 0.0f == lbl_1_bss_0[0]) {
            GameMesTimerEnd(lbl_1_data_134);
            lbl_1_bss_B4 = GameMesMgFinishCreate();
            if (lbl_1_data_140[0] != -1) {
                HuAudSStreamFadeOut(lbl_1_data_140[0], 100);
            }
        } else if (!GameMesStatGet(lbl_1_bss_B4) && lbl_1_bss_0[0] >= 180.0f
                   && (lbl_1_data_138[0] == 4
                       || (p[lbl_1_data_138[0]]->unk024 == 7 && p[lbl_1_data_138[0]]->unk028 >= 0x3C))) {
            lbl_1_bss_BC++;
            lbl_1_bss_0[0] = -1.0f;
            if (lbl_1_data_138[0] != 4) {
                GWMgCoinBonusSet(p[lbl_1_data_138[0]]->padIdx, 10);
                lbl_1_bss_B4 = GameMesMgWinnerCreate(p[lbl_1_data_138[0]]->charNo, -1, -1, -1);
                HuAudSStreamPlay(0x79);
                lbl_1_data_144[0] = HuAudFXPlay(0x8E9);
                CharFXPlay((s16)p[lbl_1_data_138[0]]->charNo, 0x1F8);
            } else {
                lbl_1_bss_B4 = GameMesMgDrawCreate();
                HuAudSStreamPlay(0x7B);
                for (i = 0; i < 4; i++) {
                    CharFXPlay((s16)p[i]->charNo, 0x200);
                }
            }
        }
        for (i = 0; i < 4; i++) {
            s32 prev = p[i]->unk024;

            p[i]->unk024 = (p[i]->unk024 == 2) ? ((lbl_1_data_138[0] == i) ? 7 : 5) : p[i]->unk024;
            p[i]->unk028 = (prev != p[i]->unk024) ? 0 : p[i]->unk028;
        }
        lbl_1_bss_0[0] += 1.0f;
        break;
    case 0x3ED:
        lbl_1_bss_0[0] += 1.0f;
        for (i = 0; i < 4; i++) {
            s32 prev = p[i]->unk024;

            p[i]->unk024 = (p[i]->unk024 == 5) ? ((lbl_1_data_138[0] == i) ? 7 : 6) : p[i]->unk024;
            p[i]->unk028 = (prev != p[i]->unk024) ? 0 : p[i]->unk028;
        }
        if (210.0f < lbl_1_bss_0[0]) {
            if (lbl_1_bss_8 == 0) {
                if (lbl_1_data_138[0] != 4) {
                    HuAudFXFadeOut(lbl_1_data_144[0], 1000);
                }
                lbl_1_bss_B4 = -1;
                lbl_1_bss_8 = 1;
            }
        }
        break;
    default:
        OSReport(lbl_1_data_284, lbl_1_bss_BC);
        break;
    }
}

/* 461 insns */
void fn_1_9F20(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx lookAt;
    Mtx trans;
    HuVecF quad[4] = {
        { -40.0f,  40.0f, 0.0f },
        {  40.0f,  40.0f, 0.0f },
        {  40.0f, -40.0f, 0.0f },
        { -40.0f, -40.0f, 0.0f },
    };
    HuVecF corner[4];
    HU3DCAMERA *cam;
    s32 i;

    cam = &Hu3DCamera[1];
    C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
    PSMTXTranspose(lookAt, trans);
    PSMTXMultVecArray(trans, quad, corner, 4);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
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
    HuSprTexLoad(espanim[esprite[lbl_1_bss_98[0]].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    for (i = 0; i < 128; i++) {
        if (lbl_1_bss_600[i].unk00 != 0) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(corner[0].x + lbl_1_bss_600[i].unk08, corner[0].y + lbl_1_bss_600[i].unk0C,
                           corner[0].z + lbl_1_bss_600[i].unk10);
            GXColor4u8(0xF0, 0xF0, 0xF0, lbl_1_bss_600[i].unk04);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(corner[1].x + lbl_1_bss_600[i].unk08, corner[1].y + lbl_1_bss_600[i].unk0C,
                           corner[1].z + lbl_1_bss_600[i].unk10);
            GXColor4u8(0xF0, 0xF0, 0xF0, lbl_1_bss_600[i].unk04);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(corner[2].x + lbl_1_bss_600[i].unk08, corner[2].y + lbl_1_bss_600[i].unk0C,
                           corner[2].z + lbl_1_bss_600[i].unk10);
            GXColor4u8(0xF0, 0xF0, 0xF0, lbl_1_bss_600[i].unk04);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(corner[3].x + lbl_1_bss_600[i].unk08, corner[3].y + lbl_1_bss_600[i].unk0C,
                           corner[3].z + lbl_1_bss_600[i].unk10);
            /* retail: the fourth corner alone is 0xC0, not 0xF0 */
            GXColor4u8(0xC0, 0xC0, 0xC0, lbl_1_bss_600[i].unk04);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXPixModeSync();
}

/* 1670 insns */
void fn_1_A654(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx camMtx;
    Mtx invMtx;
    Vec quad[4] = {
        { -45.0f, 54.0f, 0.0f },
        { 45.0f, 54.0f, 0.0f },
        { 45.0f, -54.0f, 0.0f },
        { -45.0f, -54.0f, 0.0f },
    };
    Vec vtx[4];
    M566_PLAYER *p[4];
    HU3DCAMERA *cam;
    s32 i;
    s32 j;
    s32 k;
    s32 l;
    s32 kind;
    float baseX;
    float baseY;
    float baseZ;

    for (j = 0; j < 4; j++) {
        p[j] = lbl_1_bss_C8[j]->data;
    }
    cam = &Hu3DCamera[1];
    C_MTXLookAt(camMtx, &cam->pos, &cam->up, &cam->target);
    PSMTXTranspose(camMtx, invMtx);
    PSMTXMultVecArray(invMtx, quad, vtx, 4);
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
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 127, GX_AOP_AND, GX_GEQUAL, 127);
    GXSetZCompLoc(GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 2; i++) {
        HuSprTexLoad(espanim[esprite[lbl_1_bss_90[i]].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        for (j = 0; j < 4; j++) {
            s32 ofs[4] = { 0, -7, 0, 7 };
            float scale = 1.0f;
            float uv[4][2] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
            s32 ofsY[10] = { 0, 0, 0, 0, 0, 0, 30, 0, 0, 0 };
            s32 ofsZ[10] = { 0, 0, 0, 0, 0, 0, 30, 0, 0, 0 };

            if (lbl_1_data_158[0] != 0) {
                continue;
            }
            if (i == 0 && p[j]->unk050 == 0) {
                continue;
            }
            if (i == 1 && p[j]->unk050 == 0) {
                continue;
            }
            if (i == 1) {
                kind = lbl_1_bss_1810[p[j]->unk04C].unk000 == 1
                    ? lbl_1_data_14C[0]
                    : lbl_1_bss_1810[p[j]->unk04C].unk000 == 2 ? lbl_1_data_14C[1] : lbl_1_data_14C[2];
                switch (kind) {
                case 0:
                    scale = p[j]->unk050 % 90 < 56
                        ? (p[j]->unk050 % 90 % 12 < 8 ? 0.8 + 0.6 * (p[j]->unk050 % 90 % 12 / 8.0f)
                                                      : 0.8 + 0.6 * ((12 - p[j]->unk050 % 90 % 12) / 4.0f))
                        : 0.8 + 0.6 * ((90 - p[j]->unk050 % 90) / 34.0f);
                    break;
                case 1:
                    scale = p[j]->unk050 % 90 < 27
                        ? 0.6 + 0.5 * (p[j]->unk050 % 90 / 27.0f)
                            + 0.1 * (p[j]->unk050 % 4 == 3 ? 1 : p[j]->unk050 % 4)
                        : p[j]->unk050 % 90 < 33
                        ? 0.7 + 0.4 - 0.4 * ((p[j]->unk050 % 90 - 27) / 6.0f)
                        : p[j]->unk050 % 90 < 60
                        ? 0.7 + 0.5 * ((p[j]->unk050 % 90 - 33) / 27.0f)
                            + 0.1 * (p[j]->unk050 % 4 == 3 ? 1 : p[j]->unk050 % 4)
                        : p[j]->unk050 % 90 < 90
                        ? 0.6 + 0.6 - 0.6 * ((p[j]->unk050 % 90 - 60) / 30.0f)
                        : 0.0;
                    break;
                case 2:
                    scale = p[j]->unk050 % 90 < 7
                        ? 0.7 + 0.6 * (p[j]->unk050 % 90 / 7.0f)
                        : p[j]->unk050 % 90 < 20
                        ? 0.7 + 0.6 - 0.6 * ((p[j]->unk050 % 90 - 7) / 13.0f)
                        : p[j]->unk050 % 90 < 27
                        ? 0.7 + 0.6 * ((p[j]->unk050 % 90 - 20) / 7.0f)
                        : p[j]->unk050 % 90 < 40
                        ? 0.7 + 0.6 - 0.6 * ((p[j]->unk050 % 90 - 27) / 13.0f)
                        : p[j]->unk050 % 90 < 80
                        ? 0.7 + 0.7 * ((p[j]->unk050 % 90 - 40) / 40.0f)
                            + 0.1 * (p[j]->unk050 % 4 == 3 ? 1 : p[j]->unk050 % 4)
                        : p[j]->unk050 % 90 < 90
                        ? 0.7 + 0.7 - 0.7 * ((p[j]->unk050 % 90 - 80) / 10.0f)
                        : 0.0;
                    break;
                case 3:
                    scale = p[j]->unk050 % 30 < 20
                        ? 1.3 + 0.3 * (p[j]->unk050 % 4 == 3 ? 1 : p[j]->unk050 % 4)
                        : 1.3;
                    break;
                case 4:
                    scale = p[j]->unk050 % 30 < 8 ? 0.6 + 0.4 * (p[j]->unk050 % 30 / 8.0f)
                                                  : 0.6 + 0.4 * ((30 - p[j]->unk050 % 30) / 22.0f);
                    break;
                }
            }
            for (k = 0; k < 4; k++) {
                for (l = 0; l < 2; l++) {
                    uv[k][l] = 0.5f + (uv[k][l] - 0.5f) / scale;
                }
            }
            baseX = lbl_1_bss_C8[j]->trans.x;
            baseY = ofsY[p[j]->unk008]
                + (22.0f + (lbl_1_bss_C8[j]->trans.y + CharModelHeightGet((s16)p[j]->charNo)));
            baseZ = 20.0f + lbl_1_bss_C8[j]->trans.z + ofsZ[p[j]->unk008];
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(baseX + vtx[0].x * scale, baseY + vtx[0].y * scale,
                baseZ + vtx[0].z * scale + i * 2);
            GXColor4u8(255, 255, 255, 255);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(baseX + vtx[1].x * scale, baseY + vtx[1].y * scale,
                baseZ + vtx[1].z * scale + i * 2);
            GXColor4u8(255, 255, 255, 255);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(baseX + vtx[2].x * scale, baseY + vtx[2].y * scale,
                baseZ + vtx[2].z * scale + i * 2);
            GXColor4u8(255, 255, 255, 255);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(baseX + vtx[3].x * scale, baseY + vtx[3].y * scale,
                baseZ + vtx[3].z * scale + i * 2);
            GXColor4u8(255, 255, 255, 255);
            GXTexCoord2f32(0.0f, 1.0f);
        }
        GXPixModeSync();
    }
}

/* 423 insns */
void fn_1_C06C(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 i;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
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
    HuSprTexLoad(espanim[esprite[lbl_1_bss_8C].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    for (i = 0; i < 29; i++) {
        if (lbl_1_bss_1810[i].unk000 != 0 && (lbl_1_bss_1810[i].unk014 == 0 || lbl_1_bss_1810[i].unk014 == 4)) {
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(1.0f + (lbl_1_bss_1810[i].unk028 - 66.0f), 1.0f,
                           4.0f + (lbl_1_bss_1810[i].unk030 - 66.0f));
            GXColor4u8(0, 0, 0, 0x7F);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(1.0f + (66.0f + lbl_1_bss_1810[i].unk028), 1.0f,
                           4.0f + (lbl_1_bss_1810[i].unk030 - 66.0f));
            GXColor4u8(0, 0, 0, 0x7F);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(1.0f + (66.0f + lbl_1_bss_1810[i].unk028), 1.0f,
                           4.0f + (66.0f + lbl_1_bss_1810[i].unk030));
            GXColor4u8(0, 0, 0, 0x7F);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(1.0f + (lbl_1_bss_1810[i].unk028 - 66.0f), 1.0f,
                           4.0f + (66.0f + lbl_1_bss_1810[i].unk030));
            GXColor4u8(0, 0, 0, 0x7F);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
    GXPixModeSync();
}

/* 1265 insns */
void fn_1_C708(OMOBJ *obj)
{
    void *work[4];
    s32 i;
    s32 j;
    s32 k;
    s32 cnt;
    s32 layerA;
    s32 layerB;
    s32 ofs;
    s32 sub;
    s32 fix0;
    s32 fix1;
    s32 fix2;

    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_C8[i]->data;
    }
    obj->mdlId[5] = Hu3DHookFuncCreate((HU3DMODELHOOK)fn_1_9F20);
    Hu3DModelLayerSet(obj->mdlId[5], 4);
    Hu3DModelCameraSet(obj->mdlId[5], 2);
    obj->mdlId[6] = Hu3DHookFuncCreate((HU3DMODELHOOK)fn_1_A654);
    Hu3DModelLayerSet(obj->mdlId[6], 2);
    Hu3DModelCameraSet(obj->mdlId[6], 2);
    obj->mdlId[7] = Hu3DHookFuncCreate((HU3DMODELHOOK)fn_1_C06C);
    Hu3DModelLayerSet(obj->mdlId[7], 0);
    Hu3DModelCameraSet(obj->mdlId[7], 2);
    for (i = 0; i < 5; i++) {
        s32 mdlDataNum[5] = { 0x00790000, 0x00790001, 0x00790002, 0x00790003, 0x00790004 };
        j = i;
        obj->mdlId[j] = Hu3DModelCreateData(mdlDataNum[i]);
        if (i <= 1) {
            layerA = 0;
        } else {
            layerA = 3;
        }
        Hu3DModelLayerSet(obj->mdlId[j], layerA);
        Hu3DModelCameraSet(obj->mdlId[j], 2);
        Hu3DModelAttrSet(obj->mdlId[j], 0x40000001);
        if (i == 0) {
            Hu3DModelShadowMapSet(obj->mdlId[j]);
        }
    }
    for (i = 0; i < 16; i++) {
        j = i + 13;
        if (i == 0) {
            obj->mdlId[j] = Hu3DModelCreateData(0x00790005);
        } else {
            obj->mdlId[j] = Hu3DModelLink(obj->mdlId[13]);
        }
        Hu3DModelLayerSet(obj->mdlId[j], 0);
        Hu3DModelCameraSet(obj->mdlId[j], 2);
        Hu3DModelAttrSet(obj->mdlId[j], 0x40000001);
        Hu3DModelAttrSet(obj->mdlId[j], 1);
        Hu3DModelShadowSet(obj->mdlId[j]);
    }
    for (i = 0; i < 4; i++) {
        j = i + 9;
        if (i == 0) {
            obj->mdlId[j] = Hu3DModelCreateData(0x0079000E);
        } else {
            obj->mdlId[j] = Hu3DModelLink(obj->mdlId[9]);
        }
        Hu3DModelLayerSet(obj->mdlId[j], 2);
        Hu3DModelCameraSet(obj->mdlId[j], 2);
        Hu3DModelAttrSet(obj->mdlId[j], 0x40000001);
        Hu3DModelAttrSet(obj->mdlId[j], 1);
    }
    for (i = 0; i < 6; i++) {
        s32 grpNum[6] = { 11, 11, 8, 4, 4, 4 };
        s32 grpBase[6] = { 0x3A, 0x45, 0x50, 0x58, 0x5C, 0x60 };
        s32 mtnIdx[3] = { 0, 1, 2 };
        s32 grpDataNum[6] = { 0x00790021, 0x00790023, 0x00790027, 0x00790026, 0x00790025, 0x0079000D };
        s32 mtnDataNum[3] = { 0x00790022, 0x00790024, 0x00790028 };
        for (k = 0; k < grpNum[i]; k++) {
            j = k + grpBase[i];
            if (k == 0 || i < 3) {
                obj->mdlId[j] = Hu3DModelCreateData(grpDataNum[i]);
            } else {
                obj->mdlId[j] = Hu3DModelLink(obj->mdlId[grpBase[i]]);
            }
            if (k == 0 && i < 3) {
                obj->mtnId[mtnIdx[i]] = Hu3DJointMotionData(obj->mdlId[j], mtnDataNum[i]);
            }
            if (i < 3) {
                Hu3DMotionSet(obj->mdlId[j], obj->mtnId[mtnIdx[i]]);
                Hu3DModelAttrSet(obj->mdlId[j], 0x40000001);
                if (i != 0 || k != 0) {
                    Hu3DModelShadowSet(obj->mdlId[j]);
                }
            }
            Hu3DMotionTimeSet(obj->mdlId[j], 0.0f);
            if (i < 3) {
                layerB = 1;
            } else {
                layerB = 3;
            }
            Hu3DModelLayerSet(obj->mdlId[j], layerB);
            Hu3DModelCameraSet(obj->mdlId[j], 2);
            Hu3DModelAttrSet(obj->mdlId[j], 1);
            if (i == 0) {
                Hu3DModelScaleSet(obj->mdlId[j], 1.6f, 1.6f, 1.6f);
            } else if (i == 1 || i == 3) {
                Hu3DModelScaleSet(obj->mdlId[j], 0.75f, 0.75f, 0.75f);
            }
            Hu3DModelPosSet(obj->mdlId[j], 0.0f, 14000.0f, 0.0f);
        }
    }
    obj->mdlId[8] = Hu3DModelLink(obj->mdlId[58]);
    Hu3DModelShadowSet(obj->mdlId[8]);
    Hu3DModelLayerSet(obj->mdlId[8], 1);
    Hu3DModelCameraSet(obj->mdlId[8], 2);
    Hu3DModelAttrSet(obj->mdlId[8], 1);
    memset(lbl_1_bss_600, 0, sizeof(lbl_1_bss_600));
    memset(lbl_1_bss_1600, 0, sizeof(lbl_1_bss_1600));
    memset(lbl_1_bss_1810, 0, sizeof(lbl_1_bss_1810));
    cnt = 0;
    {
        s32 actCnt[7] = { 0, 0, 0, 0, 0, 0, 0 };
        s32 actMdl[7] = { -1, -1, -1, -1, -1, -1, -1 };
        s32 actDataNum[7] = { 0x00790006, 0x00790007, 0x00790008, 0x00790009, 0x0079000A, 0x0079000B, 0x0079000C };
        for (i = 0; i < 29; i++) {
            do {
                k = rand8() % 7;
            } while (cnt / 7 != actCnt[k]);
            j = i + 29;
            if (actMdl[k] == -1) {
                actMdl[k] = obj->mdlId[j] = Hu3DModelCreateData(actDataNum[k]);
            } else {
                obj->mdlId[j] = Hu3DModelLink(actMdl[k]);
            }
            lbl_1_bss_1810[i].unk008 = k;
            Hu3DModelLayerSet(obj->mdlId[j], 1);
            Hu3DModelCameraSet(obj->mdlId[j], 2);
            Hu3DModelAttrSet(obj->mdlId[j], 0x40000001);
            Hu3DModelShadowSet(obj->mdlId[j]);
            cnt++;
            actCnt[k]++;
            if (i == 0) {
                lbl_1_bss_1810[i].unk028 = lbl_1_bss_1810[i].unk030 = 0.0f;
            } else if (i <= 11) {
                lbl_1_bss_1810[i].unk028 = 355.0 * sin(M_PI * (360.0f * (i - 1) / 11.0f) / 180.0);
                lbl_1_bss_1810[i].unk030 = 355.0 * cos(M_PI * (360.0f * (i - 1) / 11.0f) / 180.0);
            } else if (i <= 28) {
                lbl_1_bss_1810[i].unk028 = 555.0 * sin(M_PI * (180.0f + 360.0f * (i - 12) / 17.0f) / 180.0);
                lbl_1_bss_1810[i].unk030 = 555.0 * cos(M_PI * (180.0f + 360.0f * (i - 12) / 17.0f) / 180.0);
            }
            Hu3DModelPosSet(obj->mdlId[j], lbl_1_bss_1810[i].unk028, lbl_1_bss_1810[i].unk02C, lbl_1_bss_1810[i].unk030);
            lbl_1_bss_1810[i].unk014 = 0;
        }
    }
    {
        s32 kindTbl[29] = { 1, 1, 2, 3, 2, 1, 1, 2, 3, 2, 1, 1, 2, 3, 2, 1, 1, 2, 3, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
        s32 usedTbl[29] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        s32 kindCnt[3] = { 0, 0, 0 };
        for (i = 0; i < 29; i++) {
            if (i == 0) {
                k = 0;
            } else {
                do {
                    k = rand8() % 29;
                } while (usedTbl[k] != 0);
            }
            usedTbl[k] = 1;
            lbl_1_bss_1810[(i * 4) % 29].unk000 = kindTbl[k];
            lbl_1_bss_1810[(i * 4) % 29].unk010 = 0;
            lbl_1_bss_1810[(i * 4) % 29].unk004 = kindCnt[kindTbl[k] - 1];
            kindCnt[kindTbl[k] - 1]++;
        }
    }
    for (k = 0; k < 4; k++) {
        s32 posX[4] = { 0x46, 0xBE, 0x184, 0x1FC };
        for (i = 0; i < 7; i++) {
            s32 posY[7] = { -8, 14, 0x24, -36, 0, 0, 0 };
            if (i == 6) {
                ofs = ((s32 *)work[k])[3];
            } else {
                ofs = 0;
            }
            M566_ESPTBL[k][i] = espEntry(lbl_1_data_0[i] + ofs, 0, 0);
            espDispOff(M566_ESPTBL[k][i]);
            espAttrSet(M566_ESPTBL[k][i], 1);
            espBankSet(M566_ESPTBL[k][i], 0);
            if (i == 6) {
                sub = 3;
            } else {
                sub = i % 3;
            }
            espPosSet(M566_ESPTBL[k][i], posX[k] - 2 + posY[sub], 56.0f);
        }
        lbl_1_bss_84[k] = MgScoreWinCreate(0x70, 0x24);
        MgScoreWinPosSet(lbl_1_bss_84[k], posX[k], 56.0f);
        MgScoreWinDispSet(lbl_1_bss_84[k], 0);
    }
    lbl_1_bss_98[0] = espEntry(0x00210002, 0, 0);
    espDispOff(lbl_1_bss_98[0]);
    lbl_1_bss_90[0] = espEntry(0x0079001E, 0, 0);
    espDispOff(lbl_1_bss_90[0]);
    lbl_1_bss_90[1] = espEntry(0x0079001F, 0, 0);
    espDispOff(lbl_1_bss_90[1]);
    lbl_1_bss_8C = espEntry(0x00790020, 0, 0);
    espDispOff(lbl_1_bss_8C);
    lbl_1_data_14C[0] = rand8() % 4;
    do {
        lbl_1_data_14C[1] = rand8() % 4;
    } while (lbl_1_data_14C[0] == lbl_1_data_14C[1]);
    do {
        lbl_1_data_14C[2] = rand8() % 4;
    } while (lbl_1_data_14C[0] == lbl_1_data_14C[2] || lbl_1_data_14C[1] == lbl_1_data_14C[2]);
    if (lbl_1_data_14C[0] == 3) {
        fix0 = 4;
    } else {
        fix0 = lbl_1_data_14C[0];
    }
    lbl_1_data_14C[0] = fix0;
    if (lbl_1_data_14C[1] == 3) {
        fix1 = 4;
    } else {
        fix1 = lbl_1_data_14C[1];
    }
    lbl_1_data_14C[1] = fix1;
    if (lbl_1_data_14C[2] == 3) {
        fix2 = 4;
    } else {
        fix2 = lbl_1_data_14C[2];
    }
    lbl_1_data_14C[2] = fix2;
    obj->objFunc = (OMOBJFUNC)fn_1_48F8;
}

/* 248 insns -- the 0x64 player object process */
void fn_1_DACC(OMOBJ *obj)
{
    M566_PLAYER *work;
    int padList[4] = { 0, 1, 2, 3 };
    int n;
    int i;
    int j;

    n = 0;
    work = obj->data;
    memset(work, 0, sizeof(M566_PLAYER));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayerConf[j].grp) {
                padList[n] = j;
                n++;
            }
        }
    }
    work->playerNo = obj->work[0];
    work->padIdx = padList[work->playerNo];
    if (work->padIdx == 4) {
        work->padIdx = work->playerNo;
    }
    work->charNo = GwPlayerConf[work->padIdx].charNo;
    work->unk008 = (work->charNo >= 9) ? 9 : work->charNo;
    work->unk010 = (GwPlayerConf[work->padIdx].type != 0) ? -1 : GwPlayerConf[work->padIdx].padNo;
    {
        int rumbleMask[4] = { 0x80000000, 0x40000000, 0x20000000, 0x10000000 };

        work->unk05C = (GWRumbleFGet() == 0) ? 0 : ((work->unk010 == -1) ? 1 : (rumbleMask[work->unk010] & HuPadRumbleGet()));
    }
    if (work->unk05C == 0) {
        lbl_1_data_158[0] = 0;
    }
    work->unk014 = (work->unk010 != -1) ? 0 : GwPlayerConf[work->padIdx].dif;
    work->unk024 = 2;
    work->unk04C = -1;
    obj->mdlId[0] = CharModelCreate(work->charNo, 4);
    Hu3DModelLayerSet(obj->mdlId[0], 1);
    Hu3DModelCameraSet(obj->mdlId[0], 2);
    CharEffectLayerSet(3);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelShadowSet(obj->mdlId[0]);
    work->unk01C = 0;
    work->unk020 = -1;
    for (i = 0; i < 10; i++) {
        obj->mtnId[i] = CharMotionCreate(work->charNo, lbl_1_data_C0[i]);
    }
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    CharMotionVoiceOnSet(work->charNo, obj->mtnId[9], 0);
    obj->trans.x = lbl_1_data_15C[work->playerNo][0];
    obj->trans.y = lbl_1_data_15C[work->playerNo][1];
    obj->trans.z = lbl_1_data_15C[work->playerNo][2];
    obj->rot.y = lbl_1_data_15C[work->playerNo][3];
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->rot.x = obj->rot.z = 0.0f;
    obj->objFunc = (OMOBJFUNC)fn_1_668;
}

/* 21 insns -- byte-identical to m535Dll/m535 fn_1_B700 */
void fn_1_DEAC(OMOBJ *obj)
{
    lbl_1_bss_BC = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    obj->objFunc = (OMOBJFUNC)fn_1_8F1C;
}

/* 379 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;

    OSReport(lbl_1_data_29F);
    lbl_1_bss_B8 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_B8);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(2, 30.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 0, 640, 480);
    CZoomM[0] = 2472.0f;
    CenterM[0].x = 0.0f;
    CenterM[0].y = 84.0f;
    CenterM[0].z = 0.0f;
    CRotM[0].x = -32.6f;
    CRotM[0].y = 0.0f;
    CRotM[0].z = 0.0f;
    CZoomM[1] = 1000.0f;
    CenterM[1].x = 0.0f;
    CenterM[1].y = 30.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = -32.6f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    Hu3DLighInit();
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.0f, -1.0f, -0.5f };
        GXColor lightColor = { 255, 255, 255, 255 };

        lbl_1_bss_AC = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    }
    Hu3DGLightStaticSet(lbl_1_bss_AC, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_AC);
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
    lbl_1_bss_B4 = -1;
    lbl_1_data_138[0] = -1;
    lbl_1_bss_C4 = omAddObjEx(lbl_1_bss_B8, 101, 100, 3, 1, (OMOBJFUNC)fn_1_C708);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_C8[i] = omAddObjEx(lbl_1_bss_B8, 100, 1, 10, 0, fn_1_DACC);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M566_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_D8 = omAddObjEx(lbl_1_bss_B8, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_D8->work[0] = 2;
    lbl_1_bss_DC = omAddObjEx(lbl_1_bss_B8, 102, 0, 0, -1, fn_1_DEAC);
    lbl_1_bss_C0 = omAddObjEx(lbl_1_bss_B8, 103, 1, 0, -1, fn_1_E4EC);
}

/* 22 insns -- byte-identical to m535Dll/m535 fn_1_BDC8 */
void fn_1_E4EC(OMOBJ *obj)
{
    if (lbl_1_bss_8 != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        obj->objFunc = (OMOBJFUNC)fn_1_E544;
    }
}

/* 46 insns -- byte-identical to m535Dll/m535 fn_1_BE20 */
void fn_1_E544(void)
{
    M566_PLAYER *work;
    int i;

    if (WipeCheckEnd()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_C8[i]->data;
        CharModelKill(work->charNo);
    }
    if (lbl_1_bss_B4 >= 0) {
        GameMesKill(lbl_1_bss_B4);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_148[0], 1);
}

/* sqrtf (51 insns) is the extern inline in libc/math.h -- CodeWarrior
 * emits it per-TU from the #include. Do not hand-write it. */


extern ESPRITE esprite[];
extern ESPANIM espanim[];

