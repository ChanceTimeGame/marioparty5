/*
 * m525Dll m525.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m525Dll/asm/REL/m525Dll/m525.s.
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

/* m525 (like m566) has a reference that emits sqrtf OUT OF LINE: a weak,
 * unmangled, 51-instruction symbol with 4 `bl sqrtf` call sites (m566 has 14). libc/math.h's
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
 * of line at the call sites in m566. m525 needs no inline_max_size: its only caller,
 * fn_1_654, is too large for the inliner, so the calls stay out of line by themselves
 * (as m505's fabs). */
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


#include "REL/m525Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/esprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include <string.h>

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 25; */
/* 0x18 */ /* double lbl_1_rodata_18 = 0.03125; */
/* 0x20 */ /* double lbl_1_rodata_20 = -32; */
/* 0x28 */ /* double lbl_1_rodata_28 = 3.141592653589793; */
/* 0x30 */ /* double lbl_1_rodata_30 = 180; */
/* 0x38 */ /* double lbl_1_rodata_38 = 4503601774854144; */
/* 0x40 */ /* s32 lbl_1_rodata_40[4] = { 0x00000011, 0x0000000E, 0x0000000C, 0x0000000C }; */
/* 0x50 */ /* s32 lbl_1_rodata_50[4] = { 0x00000004, 0x00000004, 0x00000002, 0x00000002 }; */
/* 0x60 */ /* s32 lbl_1_rodata_60[60] = { 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x150 */ /* s32 lbl_1_rodata_150[60] = { 0xC3DD0000, 0x43DD0000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x240 */ /* s32 lbl_1_rodata_240[4] = { 0x0000001E, 0x0000001E, 0x0000000A, 0x00000002 }; */
/* 0x250 */ /* s32 lbl_1_rodata_250[4] = { 0x000001C2, 0x000001C2, 0x0000028A, 0x000005DC }; */
/* 0x260 */ /* float lbl_1_rodata_260 = 0.0f; */
/* 0x264 */ /* float lbl_1_rodata_264 = 1.0f; */
/* 0x268 */ /* float lbl_1_rodata_268 = 450.0f; */
/* 0x26C */ /* float lbl_1_rodata_26C = 10000.0f; */
/* 0x270 */ /* float lbl_1_rodata_270 = -500.0f; */
/* 0x274 */ /* float lbl_1_rodata_274 = 500.0f; */
/* 0x278 */ /* float lbl_1_rodata_278 = 150.0f; */
/* 0x27C */ /* float lbl_1_rodata_27C = 255.0f; */
/* 0x280 */ /* float lbl_1_rodata_280 = 75.0f; */
/* 0x284 */ /* float lbl_1_rodata_284 = 120.0f; */
/* 0x288 */ /* float lbl_1_rodata_288 = 220.0f; */
/* 0x28C */ /* float lbl_1_rodata_28C = -180.0f; */
/* 0x290 */ /* float lbl_1_rodata_290 = -80.0f; */
/* 0x294 */ /* float lbl_1_rodata_294 = 0.5f; */
/* 0x298 */ /* double lbl_1_rodata_298 = 800; */
/* 0x2A0 */ /* float lbl_1_rodata_2A0 = 10.0f; */
/* 0x2A4 */ /* float lbl_1_rodata_2A4 = 60.0f; */
/* 0x2A8 */ /* float lbl_1_rodata_2A8 = 23.0f; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 125; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 1; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 0.5; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = 0.25; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = 800.0f; */
/* 0x2D4 */ /* float lbl_1_rodata_2D4 = 1.0833334f; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 0.9375f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 0.0625f; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 0; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 5.860805860805861; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 0.25f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 0.7f; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = 0.3; */
/* 0x300 */ /* double lbl_1_rodata_300 = 0.7; */
/* 0x308 */ /* float lbl_1_rodata_308 = 16.0f; */
/* 0x310 */ /* double lbl_1_rodata_310 = -0.1188118811881188; */
/* 0x318 */ /* float lbl_1_rodata_318 = 175.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 225.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 50.0f; */
/* 0x328 */ /* double lbl_1_rodata_328 = 0.44999999999999996; */
/* 0x330 */ /* double lbl_1_rodata_330 = 0.55; */
/* 0x338 */ /* float lbl_1_rodata_338 = 100.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = -3000.0f; */
/* 0x340 */ /* float lbl_1_rodata_340 = 4.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 45.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = -0.60833335f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 70.0f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 5.0f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 155.0f; */
/* 0x358 */ /* float lbl_1_rodata_358 = -492.0f; */
/* 0x35C */ /* float lbl_1_rodata_35C = 492.0f; */
/* 0x360 */ /* float lbl_1_rodata_360 = -482.0f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 40.0f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 482.0f; */
/* 0x36C */ /* float lbl_1_rodata_36C = 200.0f; */
/* 0x370 */ /* double lbl_1_rodata_370 = 50; */
/* 0x378 */ /* double lbl_1_rodata_378 = -1500; */
/* 0x380 */ /* double lbl_1_rodata_380 = -100; */
/* 0x388 */ /* double lbl_1_rodata_388 = 400; */
/* 0x390 */ /* float lbl_1_rodata_390 = 400.0f; */
/* 0x394 */ /* float lbl_1_rodata_394 = 180.0f; */
/* 0x398 */ /* float lbl_1_rodata_398 = 64.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 63.0f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 0.35f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 28.0f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 2.5f; */
/* 0x3B0 */ /* double lbl_1_rodata_3B0 = 0.875; */
/* 0x3B8 */ /* double lbl_1_rodata_3B8 = 0.125; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = 15.816668f; */
/* 0x3C4 */ /* float lbl_1_rodata_3C4 = 3.7f; */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 2.4333334f; */
/* 0x3CC */ /* float lbl_1_rodata_3CC = -1.2166667f; */
/* 0x3D0 */ /* float lbl_1_rodata_3D0 = 2.4f; */
/* 0x3D4 */ /* float lbl_1_rodata_3D4 = 0.8f; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = 90.0f; */
/* 0x3DC */ /* float lbl_1_rodata_3DC = -442.0f; */
/* 0x3E0 */ /* float lbl_1_rodata_3E0 = 442.0f; */
/* 0x3E4 */ /* float lbl_1_rodata_3E4 = 130.0f; */
/* 0x3E8 */ /* float lbl_1_rodata_3E8 = 125.0f; */
/* 0x3EC */ /* float lbl_1_rodata_3EC = 185.0f; */
/* 0x3F0 */ /* float lbl_1_rodata_3F0 = 110.0f; */
/* 0x3F4 */ /* float lbl_1_rodata_3F4 = 30.0f; */
/* 0x3F8 */ /* double lbl_1_rodata_3F8 = 9; */
/* 0x400 */ /* float lbl_1_rodata_400 = 0.6f; */
/* 0x404 */ /* float lbl_1_rodata_404 = 0.1f; */
/* 0x408 */ /* float lbl_1_rodata_408 = -1.0f; */
/* 0x40C */ /* float lbl_1_rodata_40C = 0.4f; */
/* 0x410 */ /* float lbl_1_rodata_410 = 2.0f; */
/* 0x414 */ /* float lbl_1_rodata_414 = 80.0f; */
/* 0x418 */ /* float lbl_1_rodata_418 = 6.0f; */
/* 0x420 */ /* double lbl_1_rodata_420 = 4503599627370496; */
/* 0x428 */ /* double lbl_1_rodata_428 = 3; */
/* 0x430 */ /* float lbl_1_rodata_430 = 33.0f; */
/* 0x438 */ /* double lbl_1_rodata_438 = 1000; */
/* 0x440 */ /* float lbl_1_rodata_440 = 1700.0f; */
/* 0x444 */ /* float lbl_1_rodata_444 = 115.0f; */
/* 0x448 */ /* float lbl_1_rodata_448 = 0.96f; */
/* 0x44C */ /* float lbl_1_rodata_44C = 2400.0f; */
/* 0x450 */ /* float lbl_1_rodata_450 = 390.0f; */
/* 0x454 */ /* float lbl_1_rodata_454 = 18.0f; */
/* 0x458 */ /* float lbl_1_rodata_458 = 2900.0f; */
/* 0x45C */ /* float lbl_1_rodata_45C = 61.0f; */
/* 0x460 */ /* float lbl_1_rodata_460 = 5.5f; */
/* 0x464 */ /* float lbl_1_rodata_464 = 69.0f; */
/* 0x468 */ /* float lbl_1_rodata_468 = 29.0f; */
/* 0x46C */ /* float lbl_1_rodata_46C = 81.0f; */
/* 0x470 */ /* float lbl_1_rodata_470 = 2000.0f; */
/* 0x474 */ /* float lbl_1_rodata_474 = -1500.0f; */
/* 0x478 */ /* float lbl_1_rodata_478 = 1300.0f; */
/* 0x47C */ /* float lbl_1_rodata_47C = 461.0f; */
/* 0x480 */ /* float lbl_1_rodata_480 = -4.0f; */
/* 0x484 */ /* float lbl_1_rodata_484 = 1000.0f; */
/* 0x488 */ /* float lbl_1_rodata_488 = -8.0f; */
/* 0x48C */ /* float lbl_1_rodata_48C = 0.9f; */
/* 0x490 */ /* float lbl_1_rodata_490 = 7.0f; */
/* 0x498 */ /* double lbl_1_rodata_498 = 900; */
/* 0x4A0 */ /* float lbl_1_rodata_4A0 = 320.0f; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 0.00390625; */
/* 0x4B0 */ /* float lbl_1_rodata_4B0 = -900.0f; */
/* 0x4B4 */ /* float lbl_1_rodata_4B4 = -100.0f; */
/* 0x4B8 */ /* float lbl_1_rodata_4B8 = 0.00390625f; */
/* 0x4C0 */ /* double lbl_1_rodata_4C0 = 4; */
/* 0x4C8 */ /* double lbl_1_rodata_4C8 = 1.5707963267948966; */
/* 0x4D0 */ /* s32 lbl_1_rodata_4D0[4] = { 0x40000000, 0xC0000000, 0xC1000000, 0xC1400000 }; */
/* 0x4E0 */ /* s32 lbl_1_rodata_4E0[4] = { 0x00000000, 0x000000FF, 0x000000FF, 0x00000000 }; */
/* 0x4F0 */ /* double lbl_1_rodata_4F0 = 95.625; */
/* 0x4F8 */ /* double lbl_1_rodata_4F8 = 255; */
/* 0x500 */ /* float lbl_1_rodata_500 = -10.0f; */
/* 0x504 */ /* s32 lbl_1_rodata_504[15] = { 0xBF800000, 0xBF800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0xBF800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000 }; */
/* 0x540 */ /* s32 lbl_1_rodata_540[3] = { 0x00000000, 0x3F800000, 0xBF800000 }; */
/* 0x54C */ /* s32 lbl_1_rodata_54C[15] = { 0x000000FF, 0x00000060, 0x00000060, 0x00000060, 0x000000FF, 0x00000068, 0x00000060, 0x000000B4, 0x000000FF, 0x000000FF, 0x000000FF, 0x0000005A, 0x000000E8, 0x000000E8, 0x000000E8 }; */
/* 0x588 */ /* s32 lbl_1_rodata_588[3] = { 0x3F800000, 0x00000000, 0x00000000 }; */
/* 0x594 */ /* float lbl_1_rodata_594 = 0.017453292f; */
/* 0x598 */ /* float lbl_1_rodata_598 = 360.0f; */
/* 0x59C */ /* s32 lbl_1_rodata_59C[10] = { 0x0000039C, 0x0000039C, 0x0000039B, 0x00000768, 0x00000769, 0x0000076A, 0x0000076B, 0x0000076C, 0x0000076D, 0x00000021 }; */
/* 0x5C4 */ /* s32 lbl_1_rodata_5C4[3] = { 0xFFFFFFFE, 0xFFFFFFFE, 0xFFFFFFFE }; */
/* 0x5D0 */ /* float lbl_1_rodata_5D0 = 0.625f; */
/* 0x5D4 */ /* float lbl_1_rodata_5D4 = 0.375f; */
/* 0x5D8 */ /* float lbl_1_rodata_5D8 = -3.0f; */
/* 0x5DC */ /* float lbl_1_rodata_5DC = 20.0f; */
/* 0x5E0 */ /* float lbl_1_rodata_5E0 = 0.45f; */
/* 0x5E4 */ /* float lbl_1_rodata_5E4 = 21.0f; */
/* 0x5E8 */ /* double lbl_1_rodata_5E8 = 0.2777777777777778; */
/* 0x5F0 */ /* float lbl_1_rodata_5F0 = -2.0f; */
/* 0x5F4 */ /* float lbl_1_rodata_5F4 = 288.0f; */
/* 0x5F8 */ /* float lbl_1_rodata_5F8 = 210.0f; */
/* 0x5FC */ /* s32 lbl_1_rodata_5FC[5] = { 0x0053000D, 0x0053000E, 0x0053000F, 0x00530010, 0x00530011 }; */
/* 0x610 */ /* float lbl_1_rodata_610 = 1400.0f; */
/* 0x614 */ /* float lbl_1_rodata_614 = -35.0f; */
/* 0x618 */ /* float lbl_1_rodata_618 = 1.2f; */
/* 0x61C */ /* float lbl_1_rodata_61C = -1000.0f; */
/* 0x620 */ /* s32 lbl_1_rodata_620[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 }; */
/* 0x630 */ /* s32 lbl_1_rodata_630[3] = { 0x00000000, 0x459C4000, 0x00000000 }; */
/* 0x63C */ /* s32 lbl_1_rodata_63C[3] = { 0x3F400000, 0xBF800000, 0xBF000000 }; */
/* 0x648 */ /* u8 lbl_1_rodata_648[1] = { 0x00 }; */
/* 0x64C */ /* s32 lbl_1_rodata_64C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x658 */ /* float lbl_1_rodata_658 = 25.0f; */
/* 0x65C */ /* float lbl_1_rodata_65C = 20000.0f; */
/* 0x660 */ /* float lbl_1_rodata_660 = 2800.0f; */
/* 0x664 */ /* float lbl_1_rodata_664 = -300.0f; */
/* 0x668 */ /* float lbl_1_rodata_668 = -400.0f; */
/* 0x66C */ /* float lbl_1_rodata_66C = 3000.0f; */
/* 0x670 */ /* float lbl_1_rodata_670 = -50.0f; */
/* 0x674 */ /* float lbl_1_rodata_674 = 260.0f; */
/* 0x678 */ /* float lbl_1_rodata_678 = -20.0f; */
/* 0x67C */ /* float lbl_1_rodata_67C = 32.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0[13] = { 0x00890000, 0x00300000, 0x00B40000, 0x00EA0000, 0x00E30000, 0x00140000, 0x00DD0000, 0x002A0000, 0x00C60000, 0x00AD0000, 0x00000000, 0x00000000, 0x00000000 }; /* dtk pad_: no instruction references it; kept for the .data layout */
/* 0x34 */ s32 lbl_1_data_34[2][10] = { { 0x008C0000, 0x00870095, 0x008C0003, 0x008C0004, 0x00870096, 0x008C0006, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }, { 0x008C0000, 0x00870093, 0x008C0003, 0x008C0004, 0x008C002B, 0x008C0006, 0x008C0031, 0x00870094, 0x008C0019, 0x008C000E } }; /* motion data nums [solo, team][10]: mulli 0x28 at 0xBC80 */
/* 0x84 */ u8 lbl_1_data_84[2][10] = { { 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00 }, { 0x00, 0x00, 0x01, 0x01, 0x00, 0x01, 0x01, 0x00, 0x00, 0x01 } }; /* [team][motion] no-loop flag, fn_1_654 0x5534 (mulli 0xA) */
/* 0x98 */ u8 lbl_1_data_98[2][10] = { { 0x08, 0x0F, 0x00, 0x03, 0x02, 0x08, 0x00, 0x00, 0x00, 0x00 }, { 0x08, 0x00, 0x00, 0x08, 0x00, 0x08, 0x08, 0x00, 0x0F, 0x04 } }; /* [team][motion] shift frames, fn_1_654 0x55D4 */
/* 0xAC */ s32 lbl_1_data_AC[2][10] = { { 0, 0, 0, 8, 2, 0, 0, 0, 0, 0 }, { 0, 0, 0, 5, 0, 0, 0, 0, 0, 60 } }; /* [team][motion] shift start, fn_1_654 0x5584 (mulli 0x28) */
/* 0xFC */ s32 lbl_1_data_FC[1] = { 0xFFFFFFFF };
/* 0x100 */ s32 lbl_1_data_100[1] = { 0xFFFFFFFF };
/* 0x104 */ s32 lbl_1_data_104[1] = { 0x00000001 };
/* 0x108 */ float lbl_1_data_108[11] = { -500.0f, 500.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
/* 0x134 */ float lbl_1_data_134[11] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
/* 0x160 */ float lbl_1_data_160[4][4] = { { 0.0f, 700.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }, { -310.0f, 0.0f, 0.0f, 0.0f }, { 310.0f, 0.0f, 0.0f, 0.0f } }; /* per-slot start x, y, z, rot.y: stride 0x10 (slwi 4 at 0xC428, 0xBD08) */
/* 0x1A0 */ float lbl_1_data_1A0 = 1.0f; /* unreferenced (dtk folded it into data_160's 0x44) */
/* 0x1A4 */ s32 lbl_1_data_1A4[5] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x1B8 */ char lbl_1_data_1B8[] = "*** main mode error(%d)!!\n";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x339C */ M525_339C lbl_1_bss_339C;
/* 0x316C */ M525_BLOCK lbl_1_bss_316C[20];
/* 0x16C */ M525_PIECE lbl_1_bss_16C[256];
/* 0xA4 */ M525_SE lbl_1_bss_A4[10]; /* SE request queues */
/* 0xA0 */ OMOBJ *lbl_1_bss_A0; /* fn_1_BDB4 object */
/* 0x9C */ OMOBJ *lbl_1_bss_9C; /* omOutViewMulti object */
/* 0x8C */ OMOBJ *lbl_1_bss_8C[4]; /* player objects (data = M525_PLAYER) */
/* 0x88 */ OMOBJ *lbl_1_bss_88; /* stage object (fn_1_A690 / fn_1_5AF4) */
/* 0x84 */ OMOBJ *lbl_1_bss_84; /* fn_1_C51C object */
/* 0x80 */ s32 lbl_1_bss_80; /* main mode (1000..) */
/* 0x7C */ OMOBJMAN *lbl_1_bss_7C;
/* 0x7A */ s16 lbl_1_bss_7A; /* GameMes id, -1 = none */
/* 0x78 */ s16 lbl_1_bss_78;
/* 0x74 */ s32 lbl_1_bss_74;
/* 0x5C */ float lbl_1_bss_5C[6]; /* only [0] is addressed */
/* 0x58 */ s32 lbl_1_bss_58; /* esprite id (fn_1_7698) */
/* 0x4C */ HuVecF lbl_1_bss_4C; /* shadow camera pos */
/* 0x40 */ HuVecF lbl_1_bss_40; /* shadow camera up */
/* 0x34 */ HuVecF lbl_1_bss_34; /* shadow camera target */
/* 0x30 */ float lbl_1_bss_30;
/* 0x2C */ float lbl_1_bss_2C;
/* 0x28 */ float lbl_1_bss_28;
/* 0x24 */ float lbl_1_bss_24;
/* 0x20 */ float lbl_1_bss_20;
/* 0x18 */ s32 lbl_1_bss_18[2]; /* only [0] is addressed */
/* 0x10 */ s32 lbl_1_bss_10[2]; /* [0] = end flag (fn_1_C51C) */
/* 0xC */ s32 lbl_1_bss_C;
/* 0x4 */ s32 lbl_1_bss_4[2]; /* only [0] is addressed */
/* 0x0 */ float lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 365 insns */
void fn_1_A0(void)
{
    HuVecF pos;
    HuVecF center;
    HuVecF up;
    float rx;
    float ry;
    float rz;
    s32 i;

    for (i = 0; i < 2; i++) {
        CenterM[i].x += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
        CenterM[i].y += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_UP) != 0) - ((HuPadBtn[0] & PAD_BUTTON_DOWN) != 0));
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

/* 5303 insns */
void fn_1_654(OMOBJ *obj)
{
    s32 seNo;
    float unused;
    M525_PLAYER *work;
    M525_PLAYER *works[4];
    float mag;
    float stickX;
    float stickY;
    float btnHold;
    float btnA;
    float btnB;
    s16 motNo;
    float floorY;
    s32 team;
    s32 i;
    s32 j;
    s32 k;
    s32 shot;
    s32 mdl;
    s32 shotNo;
    s32 r;
    s32 n;
    s32 p;
    s32 q;
    s32 m;
    s32 s;
    float scale;
    float t;
    float t2;
    float vx;
    float vz;
    float lo;
    float hi;
    float dist;
    float dist2;
    float motT;

    work = obj->data;
    mag = 0.0f;
    stickX = 0.0f;
    stickY = 0.0f;
    btnHold = 0.0f;
    btnA = 0.0f;
    btnB = 0.0f;
    motNo = -1;
    floorY = 0.0f;
    team = work->unk000 != 0;
    for (i = 0; i < 4; i++) {
        works[i] = lbl_1_bss_8C[i]->data;
    }
    lbl_1_data_AC[1][8] = (work->unk000 * 60) % 120;
    if (work->unk018 != 2) {
        work->unk0A0 = work->unk0A8 = 0.0f;
    }
    work->unk02C++;
    work->unk034++;
    if (work->unk000 == 0) {
        float prev;

        scale = (work->unk058 <= 0) ? 1.0f : ((work->unk058 <= 450) ? 1.0f - work->unk058 / 450.0f : 0.0f);
        work->unk060++;
        prev = lbl_1_bss_339C.unk008;
        lbl_1_bss_339C.unk004 += lbl_1_bss_339C.unk008;
        lbl_1_bss_339C.unk008 += (lbl_1_bss_80 >= 1003) * (lbl_1_bss_339C.unk00C * ((lbl_1_bss_339C.unk004 < 0.0f) ? 1 : -1));
        if (((prev < 0.0f) ? -1 : ((prev > 0.0f) ? 1 : 0)) != ((lbl_1_bss_339C.unk008 < 0.0f) ? -1 : ((lbl_1_bss_339C.unk008 > 0.0f) ? 1 : 0))) {
            work->unk034 = 0;
            work->unk060 = 0;
            work->unk05C = rand8() % ((work->unk014 == 2) ? 8 : 4) == 0;
            if (work->unk010 == -1 && work->unk028 == 2) {
                float best = 10000.0f;
                float bestNo = 0.0f;
                float nearNo = 0.0f;

                for (j = 0; j < 3; j++) {
                    float left = -500.0f;
                    float right = 500.0f;

                    for (k = 1; k < 3; k++) {
                        left = (lbl_1_bss_8C[j + 1]->trans.x > lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x && left < lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x) ? lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x : left;
                        right = (lbl_1_bss_8C[j + 1]->trans.x < lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x && right > lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x) ? lbl_1_bss_8C[(j + k) % 3 + 1]->trans.x : right;
                    }
                    if (right - left < best && works[j + 1]->unk030 == 0) {
                        best = right - left;
                        bestNo = j + 1;
                        nearNo = (fabs(lbl_1_bss_8C[j + 1]->trans.x - lbl_1_bss_8C[(j + 1) % 3 + 1]->trans.x) < fabs(lbl_1_bss_8C[j + 1]->trans.x - lbl_1_bss_8C[(j + 2) % 3 + 1]->trans.x)) ? j + 1 : j + 2;
                    }
                }
                work->unk0B8 = -1;
                if (work->unk014 == 4) {
                    work->unk0B8 = rand8() % 12 + 15;
                }
                work->unk0B0 = bestNo;
                work->unk0B4 = 150.0f * (rand8() / 255.0f) - 75.0f;
            }
        }
        Hu3DModelRotSet(lbl_1_bss_88->mdlId[2], 0.0f, 0.0f, lbl_1_bss_339C.unk004 * scale);
        Hu3DModelRotSet(lbl_1_bss_88->mdlId[3], 0.0f, 0.0f, lbl_1_bss_339C.unk004 * scale);
        work->unk040++;
        switch (work->unk028) {
            case 1:
                motNo = (work->unk040 == 0 || work->unk040 >= 30) ? 1 : 4;
                break;
            case 2:
                if (lbl_1_bss_80 == 1003) {
                    if (lbl_1_bss_0 < 120.0f && lbl_1_bss_339C.unk008 > 0.0f && work->unk040 >= 11 && obj->trans.x > 120.0f && obj->trans.x < 220.0f) {
                        btnA = 1.0f;
                    }
                    if (lbl_1_bss_0 < 120.0f && lbl_1_bss_339C.unk008 > 0.0f && work->unk040 >= 11 && obj->trans.x > -180.0f && obj->trans.x < -80.0f) {
                        btnA = 1.0f;
                    }
                } else if (lbl_1_bss_80 == 1005) {
                    if (work->unk010 != -1) {
                        btnA = (HuPadBtnDown[work->unk010] & PAD_BUTTON_A) > 0;
                        btnB = (HuPadBtnDown[work->unk010] & PAD_BUTTON_B) > 0;
                    } else {
                        s32 waitMin[4] = { 17, 14, 12, 12 };
                        s32 waitRnd[4] = { 4, 4, 2, 2 };
                        s32 dir;

                        dir = (lbl_1_bss_339C.unk008 < 0.0f) ? -1 : 1;
                        if (work->unk0B8 == -1 && work->unk014 >= 4) {
                            work->unk0B8 = 0;
                        } else if (work->unk0B8 == -1) {
                            float ang = lbl_1_bss_339C.unk004;
                            float vel = lbl_1_bss_339C.unk008;

                            for (i = 0; i < (waitMin[work->unk014] + waitRnd[work->unk014] / 2) * 4 / 2.0f; i++) {
                                ang += vel;
                                vel = vel + lbl_1_bss_339C.unk00C * ((ang < 0.0f) ? 1 : -1);
                            }
                            if (dir * (work->unk0B4 + lbl_1_bss_8C[work->unk0B0]->trans.x) < dir * (800.0 * sin(M_PI * ang / 180.0))) {
                                work->unk0B8 = 0;
                            }
                        }
                        for (i = 0; i < 5; i++) {
                            if (lbl_1_data_1A4[i] == 1) {
                                btnA = 1.0f;
                            }
                            lbl_1_data_1A4[i] -= lbl_1_data_1A4[i] > 0;
                        }
                        if (work->unk0B8 == 0) {
                            if (work->unk014 >= 4) {
                                if (lbl_1_bss_339C.unk008 < 0.0f && work->unk038 < 5) {
                                    btnB = 1.0f;
                                    lbl_1_data_1A4[work->unk038] = (80 - work->unk060) * 2 + 7 + rand8() % 7;
                                }
                            } else if (work->unk014 >= 2) {
                                btnB = work->unk05C;
                                btnA = !btnB;
                            } else {
                                btnA = 1.0f;
                            }
                            work->unk0B8 = waitMin[work->unk014] + rand8() % waitRnd[work->unk014];
                        }
                        work->unk0B8 -= work->unk0B8 > 0;
                    }
                }
                if (work->unk044 == 0 && lbl_1_bss_339C.unk008 * lbl_1_bss_339C.unk004 > 0.0f && fabs(lbl_1_bss_339C.unk008) < 10.0f * lbl_1_bss_339C.unk00C
                    && lbl_1_data_FC[0] != 1 && lbl_1_bss_80 == 1006 && lbl_1_bss_0 >= 60.0f && lbl_1_data_FC[0] == 0) {
                    work->unk044 = 1;
                    work->unk048 = (lbl_1_bss_80 == 1006 && lbl_1_bss_0 >= 60.0f && lbl_1_data_FC[0] == 0) ? 1 : 0;
                    work->unk04C = obj->trans.x;
                    work->unk050 = obj->trans.y - 75.0f;
                    unused = 0.0f;
                    Hu3DModelHookReset(obj->mdlId[0]);
                    if (work->unk038 < 5) {
                        Hu3DModelAttrSet(lbl_1_bss_88->mdlId[work->unk038 + 23 + work->unk03C * 5], HU3D_ATTR_DISPOFF);
                    }
                }
                if (work->unk044 == -1) {
                    s32 no = work->unk038 + 23 + work->unk03C * 5;

                    if (work->unk038 < 5) {
                        Hu3DModelAttrReset(lbl_1_bss_88->mdlId[no], HU3D_ATTR_DISPOFF);
                    }
                    work->unk044 = 0;
                }
                if (work->unk044 > 0) {
                    t = (work->unk044 <= 23) ? work->unk044 / 23.0f : ((work->unk044 <= 27) ? 1.0f : 1.0f - (work->unk044 - 27) / 23.0f);
                    obj->trans.x = (1.0f - t) * work->unk04C + t * (((lbl_1_bss_339C.unk004 < 0.0f) ? -1 : 1) * (work->unk048 * 75 + 650));
                    obj->trans.y = 125.0 * (1.0 - (t - 0.5) * (t - 0.5) / 0.25);
                    obj->trans.y += 800.0f * t + (1.0f - t) * work->unk050;
                    obj->rot.y = ((work->unk044 <= 27) ? 1 : -1) * (((lbl_1_bss_339C.unk004 < 0.0f) ? -1 : 1) * 90);
                    obj->rot.z = 0.0f;
                    motNo = (1.0f != t) ? 2 : 3;
                    work->unk044++;
                    if (work->unk044 == 50) {
                        s32 no = work->unk038 + 23 + work->unk03C * 5;

                        if (work->unk038 < 5) {
                            Hu3DModelPosSet(lbl_1_bss_88->mdlId[no], 0.0f, 0.0f, 0.0f);
                            Hu3DModelScaleSet(lbl_1_bss_88->mdlId[no], 1.0833334f, 1.0833334f, 1.0833334f);
                            Hu3DModelHookSet(obj->mdlId[0], CharModelItemHookGet(work->unk00C, 2, 0), lbl_1_bss_88->mdlId[no]);
                            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[no], HU3D_ATTR_DISPOFF);
                        }
                    }
                    if (work->unk044 == 26 && work->unk048 != 0 && lbl_1_bss_80 == 1006) {
                        work->unk028 = 4;
                        work->unk02C = 0;
                        work->unk058 = 1;
                        break;
                    }
                    if (work->unk044 >= 50) {
                        work->unk044 = -1;
                    }
                } else {
                    work->unk054 = 1;
                    obj->trans.x = 800.0 * sin(M_PI * (lbl_1_bss_339C.unk004 * scale) / 180.0);
                    obj->trans.y = lbl_1_bss_339C.unk010 - 800.0 * cos(M_PI * (lbl_1_bss_339C.unk004 * scale) / 180.0);
                    obj->rot.y = work->unk054 ? 0 : 180;
                    obj->rot.z = lbl_1_bss_339C.unk004 * scale;
                    if (work->unk040 >= 11 && (btnA || btnB) && work->unk038 < 5) {
                        Mtx mtx;

                        shotNo = work->unk038 + work->unk03C * 5;
                        Hu3DModelObjMtxGet(obj->mdlId[0], CharModelItemHookGet(work->unk00C, 2, 0), mtx);
                        work->unk040 = 0;
                        lbl_1_bss_316C[shotNo].unk004 = mtx[0][3];
                        lbl_1_bss_316C[shotNo].unk008 = mtx[1][3];
                        lbl_1_bss_316C[shotNo].unk004 = 0.9375f * obj->trans.x;
                        lbl_1_bss_316C[shotNo].unk008 = 0.9375f * obj->trans.y + lbl_1_bss_339C.unk010 / 16.0f;
                        lbl_1_bss_316C[shotNo].unk00C = 0.0f;
                        lbl_1_bss_316C[shotNo].unk010 = btnA ? 0.0 : 5.860805860805861;
                        lbl_1_bss_316C[shotNo].unk000 = 1;
                        lbl_1_bss_316C[shotNo].unk014 = 0;
                        Hu3DModelHookReset(obj->mdlId[0]);
                        work->unk038++;
                        work->unk038 %= 5;
                        work->unk03C += work->unk038 == 0;
                        work->unk03C %= 4;
                        if (lbl_1_bss_A4[btnA ? 5 : 4].unk000 < 3) {
                            lbl_1_bss_A4[btnA ? 5 : 4].unk004[lbl_1_bss_A4[btnA ? 5 : 4].unk000] = 0.25f * (obj->trans.x / 500.0f);
                            lbl_1_bss_A4[btnA ? 5 : 4].unk000++;
                        }
                    }
                    motNo = (work->unk040 == 0 || work->unk040 >= 30) ? 1 : 4;
                    if (work->unk040 == 20) {
                        s32 no = work->unk038 + 23 + work->unk03C * 5;

                        if (work->unk038 < 5) {
                            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[no], HU3D_ATTR_DISPOFF);
                            Hu3DModelPosSet(lbl_1_bss_88->mdlId[no], 0.0f, 0.0f, 0.0f);
                            Hu3DModelScaleSet(lbl_1_bss_88->mdlId[no], 1.0833334f, 1.0833334f, 1.0833334f);
                            Hu3DModelHookSet(obj->mdlId[0], CharModelItemHookGet(work->unk00C, 2, 0), lbl_1_bss_88->mdlId[no]);
                        }
                    }
                }
                break;
            case 4:
                work->unk058++;
                if (work->unk02C >= 3) {
                    obj->rot.y *= 0.7f;
                    motNo = 0;
                }
                break;
            case 6:
                work->unk058++;
                obj->rot.y = 0.3 * obj->rot.y + 0.7 * (16.0f * ((lbl_1_bss_8C[0]->trans.x < 0.0f) ? -1 : 1));
                if (lbl_1_bss_80 == 1007) {
                    work->unk01C = 5;
                }
                break;
        }
        for (shot = 0; shot < 20; shot++) {
            mdl = shot + 23;
            Hu3DLLightColorSet(lbl_1_bss_88->mdlId[mdl], lbl_1_bss_316C[shot].unk018, 0xFF, 0xFF, 0xFF, 0xFF);
            Hu3DModelAmbSet(lbl_1_bss_88->mdlId[mdl], 1.0f, 1.0f, 1.0f);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[mdl + 20], HU3D_ATTR_DISPOFF);
            if (lbl_1_bss_316C[shot].unk000 == 0) {
                if (lbl_1_bss_80 == 1003) {
                    HU3DMODEL *model = &Hu3DData[lbl_1_bss_88->mdlId[mdl]];

                    if (model->attr & 0x8000) {
                        Mtx mtx;

                        Hu3DModelObjMtxGet(obj->mdlId[0], CharModelItemHookGet(work->unk00C, 2, 0), mtx);
                        Hu3DModelAttrSet(lbl_1_bss_88->mdlId[mdl + 20], HU3D_ATTR_DISPOFF);
                        Hu3DModelPosSet(lbl_1_bss_88->mdlId[mdl + 20], mtx[0][3], mtx[1][3], mtx[2][3]);
                        Hu3DModelScaleSet(lbl_1_bss_88->mdlId[mdl + 20], 1.0833334f, 1.0833334f, 1.0833334f);
                    }
                }
            } else {
                lbl_1_bss_316C[shot].unk010 += -0.1188118811881188;
                lbl_1_bss_316C[shot].unk004 += lbl_1_bss_316C[shot].unk00C;
                lbl_1_bss_316C[shot].unk008 += lbl_1_bss_316C[shot].unk010;
                lbl_1_bss_316C[shot].unk000++;
                Hu3DModelAttrReset(lbl_1_bss_88->mdlId[mdl], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(lbl_1_bss_88->mdlId[mdl], lbl_1_bss_316C[shot].unk004, lbl_1_bss_316C[shot].unk008, 0.0f);
                Hu3DModelScaleSet(lbl_1_bss_88->mdlId[mdl], 1.0833334f, 1.0833334f, 1.0833334f);
                if (lbl_1_bss_80 == 1003) {
                    Hu3DModelAttrReset(lbl_1_bss_88->mdlId[mdl + 20], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSet(lbl_1_bss_88->mdlId[mdl + 20], lbl_1_bss_316C[shot].unk004, lbl_1_bss_316C[shot].unk008, 0.0f);
                    Hu3DModelScaleSet(lbl_1_bss_88->mdlId[mdl + 20], 1.0833334f, 1.0833334f, 1.0833334f);
                }
                if (lbl_1_bss_316C[shot].unk008 <= -500.0f) {
                    lbl_1_bss_316C[shot].unk000 = 0;
                    Hu3DModelAttrSet(lbl_1_bss_88->mdlId[mdl], HU3D_ATTR_DISPOFF);
                } else if (lbl_1_bss_316C[shot].unk014 != 0) {
                    if (lbl_1_bss_316C[shot].unk000 % 2) {
                        Hu3DModelAttrReset(lbl_1_bss_88->mdlId[mdl], HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(lbl_1_bss_88->mdlId[mdl], HU3D_ATTR_DISPOFF);
                    }
                }
                if (lbl_1_bss_80 == 1003) {
                    float dx = lbl_1_bss_316C[shot].unk004 - obj->trans.x;
                    float dy = lbl_1_bss_316C[shot].unk008 - obj->trans.y;
                    float len = sqrtf(dx * dx + dy * dy);
                    float amb = 1.0 - 0.55 + 0.55 * ((len < 175.0f) ? 1.0f : ((len < 225.0f) ? 1.0f - (len - 175.0f) / 50.0f : 0.0f));
                    s32 col = 255.0f * amb;

                    if (sqrtf(dx * dx + dy * dy) >= 100.0f) {
                        Hu3DLLightColorSet(lbl_1_bss_88->mdlId[mdl], lbl_1_bss_316C[shot].unk018, col, col, col, 0xFF);
                        Hu3DModelAmbSet(lbl_1_bss_88->mdlId[mdl], amb, amb, amb);
                    }
                }
            }
        }
    } else {
        switch (work->unk028) {
            case 3:
                if (obj->trans.y > -3000.0f) {
                    obj->trans.y += work->unk0A4;
                    obj->trans.z -= 4.0f;
                    obj->rot.x = 45.0f;
                    obj->rot.y = 0.0f;
                    work->unk0A4 += -0.60833335f;
                }
                motNo = 4;
                break;
            case 2:
                if (lbl_1_bss_80 > 1001 && lbl_1_bss_80 != 1006 && lbl_1_bss_80 == 1005) {
                    if (work->unk010 != -1) {
                        stickX = HuPadStkX[work->unk010];
                        stickY = 0.0f;
                        btnHold = (HuPadBtn[work->unk010] & PAD_BUTTON_A) > 0;
                        btnA = (HuPadBtnDown[work->unk010] & ((work->unk018 == 2) ? (PAD_BUTTON_A | PAD_TRIGGER_L) : PAD_BUTTON_A)) > 0;
                    } else {
                        switch (work->unk0AC) {
                            case 0:
                            case 1: {
                                s32 link[30][2] = { { -1, -1 } };
                                s32 head = 0;
                                s32 num = 1;
                                float span[30][2] = { { -442.0f, 442.0f } };

                                for (p = 0; p < 22; p++) {
                                    if (p < 20) {
                                        s32 ageMin[4] = { 30, 30, 10, 2 };
                                        s32 yRange[4] = { 450, 450, 650, 1500 };

                                        float y;
                                        float vy;
                                        s32 f;

                                        if (lbl_1_bss_316C[p].unk000 == 0 || lbl_1_bss_316C[p].unk014 != 0 || lbl_1_bss_316C[p].unk000 < ageMin[work->unk014]
                                            || lbl_1_bss_316C[p].unk008 > obj->trans.y + yRange[work->unk014] || lbl_1_bss_316C[p].unk010 > 0.0f
                                            || obj->trans.y - 10.0f >= lbl_1_bss_316C[p].unk008) {
                                            continue;
                                        }
                                        {
                                            lo = lbl_1_bss_316C[p].unk004 - 70.0f - 5.0f;
                                            hi = 5.0f + (70.0f + lbl_1_bss_316C[p].unk004);
                                            y = lbl_1_bss_316C[p].unk008;
                                            vy = lbl_1_bss_316C[p].unk010;
                                            for (f = 0; f < 60.0f; f++) {
                                                vy += -0.1188118811881188;
                                                y += vy;
                                            }
                                            if (155.0f + obj->trans.y >= y) {
                                                if (lbl_1_bss_316C[p].unk004 < obj->trans.x) {
                                                    lo = -492.0f;
                                                } else {
                                                    hi = 492.0f;
                                                }
                                            }
                                        }
                                    } else {
                                        q = (p - 20 + work->unk000) % 3 + 1;
                                        if (works[q]->unk024 == 0) {
                                            continue;
                                        }
                                        if (lbl_1_bss_8C[q]->trans.x < obj->trans.x) {
                                            lo = -482.0f;
                                            hi = 40.0f + (40.0f + lbl_1_bss_8C[q]->trans.x);
                                        } else {
                                            lo = lbl_1_bss_8C[q]->trans.x - 40.0f - 40.0f;
                                            hi = 482.0f;
                                        }
                                    }
                                    for (q = head; q != -1; q = link[q][1]) {
                                        if (span[q][0] < lo && lo < span[q][1] && span[q][0] < hi && hi < span[q][1]) {
                                            link[num][1] = link[q][1];
                                            link[q][1] = num;
                                            link[num][0] = q;
                                            span[num][1] = span[q][1];
                                            span[num][0] = hi;
                                            span[q][1] = lo;
                                            num++;
                                            break;
                                        } else if (lo <= span[q][0] && span[q][0] <= hi && lo <= span[q][1] && span[q][1] <= hi) {
                                            head = (head == q) ? link[q][1] : head;
                                            if (link[q][0] != -1) {
                                                link[link[q][0]][1] = link[q][1];
                                            }
                                            if (link[q][1] != -1) {
                                                link[link[q][1]][0] = link[q][0];
                                            }
                                        } else if (span[q][0] < lo && lo < span[q][1]) {
                                            span[q][1] = lo;
                                        } else if (span[q][0] < hi && hi < span[q][1]) {
                                            span[q][0] = hi;
                                        }
                                    }
                                }
                                q = head;
                                work->unk0BC = 10000.0f;
                                for (; q != -1; q = link[q][1]) {
                                    if (q == head || fabs(work->unk0BC - obj->trans.x) > fabs(span[q][0] - obj->trans.x)
                                        || fabs(work->unk0BC - obj->trans.x) > fabs(span[q][1] - obj->trans.x)) {
                                        work->unk0BC = (fabs(span[q][0] - obj->trans.x) < fabs(span[q][1] - obj->trans.x)) ? span[q][0] : span[q][1];
                                    }
                                    if (span[q][0] <= obj->trans.x && obj->trans.x <= span[q][1]) {
                                        work->unk0BC = obj->trans.x;
                                        break;
                                    }
                                }
                                if (10000.0f == work->unk0BC) {
                                    work->unk0BC = obj->trans.x;
                                }
                                stickX = (work->unk0BC - obj->trans.x) / 0.25f;
                                if (work->unk014 == 0) {
                                    if (0.0f != stickX && work->unk098 == 0 && work->unk094 == 0) {
                                        if (rand8() % 2 == 0) {
                                            work->unk098 = rand8() % 4 + 13;
                                        }
                                        work->unk094 = rand8() % 25 + 40;
                                    }
                                    stickX = work->unk098 ? -stickX : stickX;
                                    work->unk094 -= work->unk094 > 0;
                                    work->unk098 -= work->unk098 > 0;
                                }
                            } break;
                        }
                    }
                }
                break;
            case 4:
                t2 = (work->unk044 <= 45) ? work->unk044 / 45.0f : 1.0f;
                obj->trans.x = 200.0f * work->unk08C * t2 + (1.0f - t2) * work->unk04C;
                obj->trans.z = t2 * (50.0 + (-1500.0 + -100.0 * fabs(work->unk08C)));
                obj->trans.y = 400.0 * (1.0 - (t2 - 0.5) * (t2 - 0.5) / 0.25);
                obj->trans.y += 400.0f * t2 + (1.0f - t2) * work->unk050;
                obj->rot.y = (work->unk044 <= 55) ? 180.0f : ((work->unk044 <= 115) ? 180.0f + 180.0f * ((work->unk044 - 55) / 60.0f) * ((0.5 == work->unk08C || 0.0f == work->unk08C) ? -1 : 1) : 0.0f);
                lbl_1_data_AC[1][9] = (0.5 == work->unk08C || 0.0f == work->unk08C) ? 0 : 60;
                obj->rot.z = 0.0f;
                motNo = (work->unk044 <= 45) ? 2 : ((work->unk044 <= 55) ? 3 : ((work->unk044 <= 109) ? 9 : 0));
                work->unk044++;
                if (lbl_1_bss_80 == 1007) {
                    work->unk028 = 6;
                }
                break;
            case 6:
                obj->rot.y *= 0.7;
                if (lbl_1_bss_80 == 1007) {
                    work->unk01C = 5;
                }
                break;
            case 0:
            case 1:
                break;
        }
        if (work->unk028 == 2) {
            switch (work->unk018) {
                case 3:
                    if (Hu3DMotionTimeGet(obj->mdlId[0]) >= 0.0f) {
                        motNo = 7;
                        HuAudFXPanning(CharFXPlay(work->unk00C, 0x1FF), 0.5 + (64.0f + 63.0f * (0.35f * (obj->trans.x / 500.0f))));
                    }
                    break;
                case 7:
                    work->unk090 = 6;
                    if (Hu3DMotionTimeGet(obj->mdlId[0]) >= 28.0f) {
                        motNo = 0;
                    }
                    break;
                case 0:
                case 1:
                    vx = 0.25 * stickX;
                    vz = 0.25 * -stickY;
                    mag = sqrtf(vx * vx + vz * vz);
                    if (mag >= 0.5f) {
                        if (mag < 2.5f) {
                            work->unk0A0 = vx;
                            work->unk0A8 += vz;
                        } else {
                            vx /= mag;
                            vz /= mag;
                            mag = 2.5f;
                            if (work->unk018 != 2) {
                                work->unk0A0 = vx * mag;
                                work->unk0A8 = vz * mag;
                            } else {
                                work->unk0A0 = 0.875 * work->unk0A0 + 0.125 * (vx * mag);
                                work->unk0A8 = 0.875 * work->unk0A8 + 0.125 * (vz * mag);
                            }
                        }
                        work->unk09C = mag;
                        motNo = 1;
                    } else if (work->unk018 != 3) {
                        motNo = 0;
                    }
                    work->unk0A4 = 0.0f;
                    if (lbl_1_bss_80 == 1006 && lbl_1_data_FC[0] == 1 - work->unk000 / 2 && 70.0f == lbl_1_bss_0) {
                        work->unk028 = 5;
                        break;
                    }
                    if (btnA) {
                        work->unk024 = 0;
                        work->unk020 = 1;
                        work->unk0A4 = 15.816668f;
                        motNo = 2;
                    }
                    break;
                case 2:
                    vx = 0.25 * stickX;
                    vz = 0.25 * -stickY;
                    mag = sqrtf(vx * vx + vz * vz);
                    if (mag >= 0.5f) {
                        if (mag < 3.7f) {
                            work->unk0A0 = vx;
                            work->unk0A8 = vz;
                        } else {
                            vx /= mag;
                            vz /= mag;
                            mag = 3.7f;
                            if (work->unk018 != 2) {
                                work->unk0A0 = vx * mag;
                                work->unk0A8 = vz * mag;
                            } else {
                                work->unk0A0 = 0.875 * work->unk0A0 + 0.125 * (vx * mag);
                                work->unk0A8 = 0.875 * work->unk0A8 + 0.125 * (vz * mag);
                            }
                        }
                        work->unk09C = mag;
                        obj->rot.y = 180.0 * (atan2(work->unk0A0, work->unk0A8) / M_PI);
                    } else {
                        0.875 * work->unk0A0;
                        0.875 * work->unk0A8;
                    }
                    if (work->unk020 != 0) {
                        if (btnHold) {
                            if (++work->unk020 > 4) {
                                work->unk020 = 0;
                            } else {
                                work->unk0A4 += 2.4333334f;
                            }
                        } else {
                            work->unk020 = 0;
                        }
                    }
                    work->unk0A4 += -1.2166667f;
                    if (work->unk024 != 0) {
                        work->unk0A4 = 0.0f;
                        motNo = 3;
                        if (lbl_1_bss_A4[9].unk000 < 3) {
                            lbl_1_bss_A4[9].unk004[lbl_1_bss_A4[9].unk000] = 0.25f * (obj->trans.x / 500.0f);
                            lbl_1_bss_A4[9].unk000++;
                        }
                    }
                    break;
                case 4:
                    break;
                case 5:
                case 6:
                    obj->rot.y = 2.4f + 0.8f * obj->rot.y;
                    break;
            }
        }
        if (work->unk028 == 2) {
            if (0.0f == work->unk0A0 || work->unk080 == ((work->unk0A0 < 0.0f) ? -1 : ((work->unk0A0 > 0.0f) ? 1 : 0))) {
                work->unk088++;
            } else {
                work->unk084 = work->unk080;
                work->unk080 = (work->unk0A0 < 0.0f) ? -1 : ((work->unk0A0 > 0.0f) ? 1 : 0);
                work->unk088 = 0;
            }
            if (work->unk088 < 10) {
                float rate = work->unk088 / 10.0f;

                obj->rot.y = (1.0f - rate) * (work->unk084 * 90) + 90.0f * (rate * work->unk080);
            } else {
                obj->trans.x += work->unk0A0;
                obj->rot.y = work->unk080 * 90;
            }
            if (work->unk024 == 0) {
                obj->trans.y += work->unk0A4;
            }
            obj->trans.z += work->unk0A8;
            obj->trans.x = (obj->trans.x < -442.0f) ? -442.0f : ((obj->trans.x > 442.0f) ? 442.0f : obj->trans.x);
            for (r = 0; r < 2; r++) {
                s32 other = (work->unk000 + r) % 3 + 1;
                float dx = lbl_1_bss_8C[other]->trans.x - obj->trans.x;

                dist = fabs(lbl_1_bss_8C[other]->trans.y - obj->trans.y);
                if (works[other]->unk030 == 0) {
                    dist = (dist > 130.0f) ? 0.0f : ((dist > 60.0f) ? 50.0f * (1.0f - (dist - 60.0f) / 70.0f) : 50.0f);
                    if (0.0f != dist && fabs(dx) < 50.0f + dist) {
                        obj->trans.x = lbl_1_bss_8C[other]->trans.x - (50.0f + dist) * ((lbl_1_bss_8C[other]->trans.x >= 482.0f) ? -1 : ((lbl_1_bss_8C[other]->trans.x <= -482.0f) ? 1 : ((dx < 0.0f) ? -1 : 1)));
                    }
                }
            }
            if (work->unk028 != 5) {
                for (r = 0; r < 2; r++) {
                    s32 other = (work->unk000 - 1 + r) % 3 + 1;

                    if (works[other]->unk030 == 0) {
                        lbl_1_bss_8C[other]->trans.x = (lbl_1_bss_8C[other]->trans.x < -442.0f) ? -442.0f : ((lbl_1_bss_8C[other]->trans.x > 442.0f) ? 442.0f : lbl_1_bss_8C[other]->trans.x);
                    }
                }
                for (r = 0; r < 2; r++) {
                    s32 other = (work->unk000 + r) % 3 + 1;
                    float dx = lbl_1_bss_8C[other]->trans.x - obj->trans.x;

                    dist2 = fabs(lbl_1_bss_8C[other]->trans.y - obj->trans.y);
                    if (works[other]->unk030 == 0) {
                        dist2 = (dist2 > 130.0f) ? 0.0f : ((dist2 > 60.0f) ? 50.0f * (1.0f - (dist2 - 60.0f) / 70.0f) : 50.0f);
                        if (0.0f != dist2 && fabs(dx) < 50.0f + dist2) {
                            lbl_1_bss_8C[other]->trans.x = obj->trans.x + (50.0f + dist2) * ((obj->trans.x >= 482.0f) ? -1 : ((obj->trans.x <= -482.0f) ? 1 : ((dx < 0.0f) ? -1 : 1)));
                        }
                    }
                }
            }
            for (s = 0; lbl_1_data_108[s] < 500.0f; s++) {
                if (lbl_1_data_108[s] <= obj->trans.x && obj->trans.x <= lbl_1_data_108[s + 1]) {
                    float y;
                    float rate;

                    rate = (obj->trans.x - lbl_1_data_108[s]) / (lbl_1_data_108[s + 1] - lbl_1_data_108[s]);
                    y = (1.0f - rate) * lbl_1_data_134[s] + rate * lbl_1_data_134[s + 1];

                    if (floorY > y) {
                        floorY = y;
                    }
                    break;
                }
            }
            if (obj->trans.y < floorY) {
                obj->trans.y = floorY;
                if (work->unk0A4 < 0.0f) {
                    if (work->unk024 == 0) {
                        work->unk07C++;
                        work->unk07C %= 3;
                    }
                    work->unk024 = 1;
                }
            }
            if (lbl_1_bss_80 == 1003 && 125.0f == lbl_1_bss_0) {
                omVibrate(work->unk004, 12, 4, 2);
            }
            if (lbl_1_bss_80 == 1003 && lbl_1_bss_0 >= 125.0f && lbl_1_bss_0 < 185.0f) {
                motNo = 7;
            }
            if (lbl_1_bss_80 == 1003 && 125.0f == lbl_1_bss_0) {
                seNo = CharFXPlay(work->unk00C, 0x1FF);
                HuAudFXPanning(seNo, 0.5 + (64.0f + 63.0f * (0.35f * (obj->trans.x / 500.0f))));
            }
            if (lbl_1_bss_80 == 1003 && lbl_1_bss_0 < 110.0f) {
                motNo = 8;
            }
            if (lbl_1_bss_80 == 1002 && lbl_1_bss_0 > 30.0f) {
                motNo = 8;
            }
            for (m = 0; m < 20; m++) {
                if (lbl_1_bss_316C[m].unk000 != 0 && lbl_1_bss_316C[m].unk014 == 0 && obj->trans.x - 70.0f < lbl_1_bss_316C[m].unk004
                    && lbl_1_bss_316C[m].unk004 < 70.0f + obj->trans.x && obj->trans.y - 10.0f < lbl_1_bss_316C[m].unk008
                    && lbl_1_bss_316C[m].unk008 < 155.0f + obj->trans.y) {
                    float ang;

                    lbl_1_bss_316C[m].unk014 = 1;
                    ang = 180.0 * (atan2(lbl_1_bss_316C[m].unk004 - obj->trans.x, lbl_1_bss_316C[m].unk008 - (70.0f + obj->trans.y)) / M_PI);
                    lbl_1_bss_316C[m].unk00C = 9.0 * sin(M_PI * ang / 180.0);
                    lbl_1_bss_316C[m].unk010 = 9.0 * -cos(M_PI * ang / 180.0);
                    work->unk030 = 1;
                    work->unk028 = 3;
                    work->unk0A4 = 10.0f;
                    omVibrate(work->unk004, 12, 12, 0);
                    if (lbl_1_bss_80 == 1005 && works[1]->unk030 != 0 && works[2]->unk030 != 0 && works[3]->unk030 != 0) {
                        lbl_1_data_FC[0] = 0;
                    }
                    if (lbl_1_bss_A4[6].unk000 < 3) {
                        lbl_1_bss_A4[6].unk004[lbl_1_bss_A4[6].unk000] = 0.25f * (obj->trans.x / 500.0f);
                        lbl_1_bss_A4[6].unk000++;
                    }
                    if (lbl_1_bss_A4[7].unk000 < 3) {
                        lbl_1_bss_A4[7].unk004[lbl_1_bss_A4[7].unk000] = 0.25f * (obj->trans.x / 500.0f);
                        lbl_1_bss_A4[7].unk000++;
                    }
                    lbl_1_bss_C = 1;
                    lbl_1_bss_5C[0] = 0.25f * (obj->trans.x / 500.0f);
                }
            }
        }
    }
    if (work->unk000 != 0) {
        for (n = 0; n < 3; n++) {
            if (work->unk024 != 0 && work->unk030 == 0 && work->unk028 < 4 && n == work->unk07C) {
                work->unk064[n] = obj->trans.x;
                work->unk070[n] = 0.6f * (1.0f + work->unk070[n]) - 0.1f - 1.0f;
                work->unk070[n] = (work->unk070[n] > 0.0f) ? 0.0f : ((work->unk070[n] < -1.0f) ? -1.0f : work->unk070[n]);
            } else {
                work->unk070[n] = 0.1f + 0.4f * work->unk070[n];
                work->unk070[n] = (work->unk070[n] > 0.0f) ? 0.0f : ((work->unk070[n] < -1.0f) ? -1.0f : work->unk070[n]);
            }
        }
    }
    if (work->unk01C >= 0) {
        motNo = work->unk01C;
    }
    if (lbl_1_bss_80 == 1006 && 2.0f == lbl_1_bss_0 && work->unk018 == 0) {
        motNo = 0;
        work->unk018 = 8;
    }
    if (motNo >= 0 && motNo != work->unk018) {
        s32 mot = motNo;

        if (mot == 0 && (lbl_1_bss_80 == 1004 || lbl_1_bss_80 == 1005)) {
            mot = 8;
        }
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[mot], lbl_1_data_AC[team][mot], lbl_1_data_98[team][mot], lbl_1_data_84[team][mot] ? 0 : HU3D_MOTATTR_LOOP);
        work->unk018 = motNo;
    }
    if (work->unk000 == 0) {
        HU3DMODEL *model = &Hu3DData[obj->mdlId[0]];

        motT = work->unk034 / 80.0f;
        motT = (motT < 0.0f) ? 0.0f : ((motT > 1.0f) ? 1.0f : motT);
        motT = (lbl_1_bss_339C.unk008 < 0.0f) ? 1.0f - motT : motT;
        if (model->motIdShift == obj->mtnId[1]) {
            model->motShiftWork.time = motT * Hu3DMotionMotionMaxTimeGet(obj->mtnId[1]);
        }
        if (model->motId == obj->mtnId[1]) {
            model->motWork.time = motT * Hu3DMotionMotionMaxTimeGet(obj->mtnId[1]);
        }
    }
    obj->rot.y *= 1.0f - work->unk090 / 6.0f;
    work->unk090 -= work->unk090 > 0;
    if (lbl_1_bss_80 == 1007 && lbl_1_data_FC[0] != 1) {
        CharModelVoicePanSet(work->unk00C, 64);
    } else {
        CharModelVoicePanSet(work->unk00C, 0.5 + (64.0f + 63.0f * (0.35f * (obj->trans.x / 500.0f))));
    }
}

/* 113 insns */
float fn_1_5930(float t, float accel, float flat, float decel)
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

/* 1769 insns */
void fn_1_5AF4(OMOBJ *obj)
{
    M525_PLAYER *players[4];
    float x;
    float y;
    float prevX;
    float prevY;
    float px;
    float py;
    float t;
    float v;
    s32 i;
    s32 idx;
    s32 sign;

    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_8C[i]->data;
    }
    x = 0.0f;
    y = 0.0f;
    prevX = -500.0f;
    prevY = 0.0f;
    idx = 0;
    lbl_1_data_108[idx] = -500.0f;
    lbl_1_data_134[idx] = 0.0f;
    while (x < 500.0f) {
        x = 500.0f;
        y = 0.0f;
        for (i = 0; i < 9; i++) {
            px = players[i / 3 + 1]->unk064[i % 3];
            py = 33.0f * (players[i / 3 + 1]->unk064 + 3)[i % 3];
            if (prevX >= px) {
                continue;
            }
            t = fabs(px) / 1000.0;
            py *= 1.0 - (0.875 * t + 0.125 * (t * t));
            t = (px - prevX) / (x - prevX);
            v = prevY * (1.0f - t) + y * t;
            if (v > py) {
                x = px;
                y = py;
            }
        }
        idx++;
        lbl_1_data_108[idx] = x;
        lbl_1_data_134[idx] = y;
        prevX = x;
        prevY = y;
    }
    for (i = 0; i < 3; i++) {
        if (players[i + 1]->unk030 == 0 && players[i + 1]->unk028 < 4 && players[i + 1]->unk024 != 0) {
            float s;
            float pos;
            float h;

            pos = players[i + 1]->unk064[players[i + 1]->unk07C];
            h = 33.0f * (players[i + 1]->unk064 + 3)[players[i + 1]->unk07C];
            s = fabs(pos) / 1000.0;
            h *= 1.0 - (0.875 * s + 0.125 * (s * s));
            lbl_1_bss_8C[i + 1]->trans.y = h;
        }
    }
    if (lbl_1_bss_80 <= 1001) {
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 1700.0f;
            CenterM[i].y = 115.0f;
            CRotM[i].x = 5.0f;
        }
    }
    if (lbl_1_bss_80 == 1003) {
        for (i = 0; i < 2; i++) {
            float rate = 0.96f;
            float rateInv = 1.0f - rate;

            CZoomM[i] = 2400.0f * rateInv + rate * CZoomM[i];
            CenterM[i].y = 390.0f * rateInv + rate * CenterM[i].y;
            CRotM[i].x = 18.0f * rateInv + rate * CRotM[i].x;
        }
    }
    if (lbl_1_bss_80 == 1004) {
        for (i = 0; i < 2; i++) {
            float rate = 0.96f;
            float rateInv = 1.0f - rate;

            CZoomM[i] = 2900.0f * rateInv + rate * CZoomM[i];
            CenterM[i].y = 390.0f * rateInv + rate * CenterM[i].y;
            CRotM[i].x = 0.0f * rateInv + rate * CRotM[i].x;
        }
    }
    if (lbl_1_bss_80 == 1006 && lbl_1_data_FC[0] == 1 && lbl_1_bss_0 >= 61.0f) {
        float time;
        float blend;
        float blendInv;

        time = lbl_1_bss_0 - 61.0f;
        blend = fn_1_5930(time, 10.0f, 30.0f, 30.0f);
        blendInv = 1.0f - blend;
        if (lbl_1_bss_0 == 61.0f) {
            lbl_1_bss_30 = CZoomM[0];
            lbl_1_bss_2C = CenterM[0].x;
            lbl_1_bss_28 = CenterM[0].y;
            lbl_1_bss_24 = CenterM[0].z;
            lbl_1_bss_20 = CRotM[0].x;
        }
        if (lbl_1_bss_0 == 81.0f) {
            Hu3DModelShadowDispOff(lbl_1_bss_8C[0]->mdlId[0]);
            Hu3DModelShadowSet(lbl_1_bss_8C[1]->mdlId[0]);
            Hu3DModelShadowSet(lbl_1_bss_8C[2]->mdlId[0]);
            Hu3DModelShadowSet(lbl_1_bss_8C[3]->mdlId[0]);
            lbl_1_bss_4C.x = 0.0f;
            lbl_1_bss_4C.y = 2000.0f;
            lbl_1_bss_4C.z = -1500.0f;
            lbl_1_bss_40.x = 0.0f;
            lbl_1_bss_40.y = 0.0f;
            lbl_1_bss_40.z = -1.0f;
            lbl_1_bss_34.x = 0.0f;
            lbl_1_bss_34.y = 0.0f;
            lbl_1_bss_34.z = -1500.0f;
            Hu3DShadowMultiPosSet(&lbl_1_bss_4C, &lbl_1_bss_40, &lbl_1_bss_34, -1);
        }
        for (i = 0; i < 2; i++) {
            CZoomM[i] = 1300.0f * blend + lbl_1_bss_30 * blendInv;
            CenterM[i].x = 0.0f * blend + lbl_1_bss_2C * blendInv;
            CenterM[i].y = 461.0f * blend + lbl_1_bss_28 * blendInv;
            CenterM[i].z = -1500.0f * blend + lbl_1_bss_24 * blendInv;
            CRotM[i].x = -4.0f * blend + lbl_1_bss_20 * blendInv;
        }
    }
    if (lbl_1_bss_80 == 1007) {
        if (lbl_1_data_FC[0] == 0) {
            Hu3DModelPosSet(obj->mdlId[64], lbl_1_bss_8C[0]->trans.x, 100.0f + lbl_1_bss_8C[0]->trans.y, lbl_1_bss_8C[0]->trans.z);
            Hu3DModelAttrReset(obj->mdlId[20], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(obj->mdlId[20], lbl_1_bss_8C[0]->trans.x, lbl_1_bss_8C[0]->trans.y, lbl_1_bss_8C[0]->trans.z);
            for (i = 0; i < 2; i++) {
                float rate = 0.96f;
                float rateInv = 1.0f - rate;

                CZoomM[i] = 1000.0f * rateInv + rate * CZoomM[i];
                CenterM[i].x = rate * CenterM[i].x + rateInv * lbl_1_bss_8C[0]->trans.x;
                CenterM[i].y = rate * CenterM[i].y + rateInv * (100.0f + lbl_1_bss_8C[0]->trans.y);
                CenterM[i].z = rate * CenterM[i].z + rateInv * lbl_1_bss_8C[0]->trans.z;
                CRotM[i].x = -8.0f * rateInv + rate * CRotM[i].x;
                if (lbl_1_bss_8C[0]->trans.x < 0.0f) {
                    sign = -1;
                } else {
                    sign = 1;
                }
                CRotM[i].y = rate * CRotM[i].y + 16.0f * rateInv * sign;
            }
            lbl_1_bss_4C.x = lbl_1_bss_8C[0]->trans.x;
            lbl_1_bss_4C.y = 2000.0f + lbl_1_bss_8C[0]->trans.y;
            lbl_1_bss_4C.z = lbl_1_bss_8C[0]->trans.z;
            lbl_1_bss_40.x = 0.0f;
            lbl_1_bss_40.y = 0.0f;
            lbl_1_bss_40.z = -1.0f;
            lbl_1_bss_34.x = lbl_1_bss_8C[0]->trans.x;
            lbl_1_bss_34.y = lbl_1_bss_8C[0]->trans.y;
            lbl_1_bss_34.z = lbl_1_bss_8C[0]->trans.z;
            Hu3DShadowMultiPosSet(&lbl_1_bss_4C, &lbl_1_bss_40, &lbl_1_bss_34, -1);
        } else {
            Hu3DModelPosSet(obj->mdlId[64], 0.0f, 461.0f, -1500.0f);
            for (i = 0; i < 3; i++) {
                Hu3DModelAttrReset(obj->mdlId[i + 20], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(obj->mdlId[i + 20], lbl_1_bss_8C[i + 1]->trans.x, lbl_1_bss_8C[i + 1]->trans.y, lbl_1_bss_8C[i + 1]->trans.z);
            }
            for (i = 0; i < -2; i++) {
                float rate = 0.9f;
                float rateInv = 1.0f - rate;
                s32 winner = (players[1]->unk030 == 0) ? 1 : (players[2]->unk030 == 0) ? 2 : 3;

                CZoomM[i] = 1300.0f * rateInv + rate * CZoomM[i];
                CenterM[i].x = 0.0f * rateInv + rate * CenterM[i].x;
                CenterM[i].y = 461.0f * rateInv + rate * CenterM[i].y;
                CenterM[i].z = -1500.0f * rateInv + rate * CenterM[i].z;
                CRotM[i].x = -4.0f * rateInv + rate * CRotM[i].x;
            }
        }
    }
    if (lbl_1_data_FC[0] != -1 && lbl_1_bss_80 >= 1007) {
        if (lbl_1_data_FC[0] == 1 || (lbl_1_bss_80 == 1007 && lbl_1_bss_0 > 7.0f)) {
            Hu3DModelAttrReset(lbl_1_bss_88->mdlId[64], HU3D_ATTR_DISPOFF);
        }
        for (i = 0; i < 256; i++) {
            if (lbl_1_bss_16C[i].unk000 >= 256) {
                lbl_1_bss_16C[i].unk008 = 900.0 * (rand8() / 255.0f - 0.5);
                lbl_1_bss_16C[i].unk00C = 320.0f;
                lbl_1_bss_16C[i].unk010 = 0.0f;
                lbl_1_bss_16C[i].unk014 = 400.0 * (rand8() / 255.0f - 0.5) / 256.0;
                lbl_1_bss_16C[i].unk018 = (-900.0f + -100.0f * (rand8() / 255.0f)) / 256.0f;
                lbl_1_bss_16C[i].unk01C = 0.0f;
                lbl_1_bss_16C[i].unk020.x = 4.0 * (rand8() / 255.0f - 0.5);
                lbl_1_bss_16C[i].unk020.y = rand8() / 255.0f - 0.5;
                lbl_1_bss_16C[i].unk020.z = 0.5 * (rand8() / 255.0f - 0.5);
                lbl_1_bss_16C[i].unk02C = 1.0f / (45.0f + 30.0f * (rand8() / 255.0f));
                if (lbl_1_bss_16C[i].unk020.x == 0.0f && lbl_1_bss_16C[i].unk020.y == 0.0f && lbl_1_bss_16C[i].unk020.z == 0.0f) {
                    lbl_1_bss_16C[i].unk020.x = 1.0f;
                }
                lbl_1_bss_16C[i].unk000 = 0;
                lbl_1_bss_16C[i].unk004 = rand8() % 4;
            }
            lbl_1_bss_16C[i].unk008 += lbl_1_bss_16C[i].unk014;
            lbl_1_bss_16C[i].unk00C += lbl_1_bss_16C[i].unk018;
            lbl_1_bss_16C[i].unk010 += lbl_1_bss_16C[i].unk01C;
            lbl_1_bss_16C[i].unk000++;
        }
    }
    if (lbl_1_bss_C != 0) {
        if (lbl_1_bss_18[0] > 1 && lbl_1_bss_A4[1].unk010 != -1) {
            HuAudFXStop(lbl_1_bss_A4[1].unk010);
            lbl_1_bss_A4[1].unk010 = -1;
        }
        if (lbl_1_bss_A4[1].unk000 < 3) {
            lbl_1_bss_A4[1].unk004[lbl_1_bss_A4[1].unk000] = lbl_1_bss_5C[0];
            lbl_1_bss_A4[1].unk000++;
        }
        lbl_1_bss_18[0] = 120;
        lbl_1_bss_C = 0;
    }
    lbl_1_bss_18[0] -= (lbl_1_bss_18[0] > 0);
    if (lbl_1_bss_18[0] == 1 && lbl_1_bss_A4[1].unk010 != -1) {
        HuAudFXStop(lbl_1_bss_A4[1].unk010);
        lbl_1_bss_A4[1].unk010 = -1;
    }
    lbl_1_bss_4C.x = 0.0f;
    lbl_1_bss_4C.y = 0.0 * sin(M_PI / 2);
    lbl_1_bss_4C.z = 10000.0f;
    lbl_1_bss_40.x = 0.0f;
    lbl_1_bss_40.y = 1.0f;
    lbl_1_bss_40.z = 0.0f;
    lbl_1_bss_34.x = lbl_1_bss_8C[0]->trans.x;
    lbl_1_bss_34.y = lbl_1_bss_8C[0]->trans.y;
    lbl_1_bss_34.z = lbl_1_bss_8C[0]->trans.z;
    Hu3DModelPosSet(obj->mdlId[13], lbl_1_bss_8C[0]->trans.x, lbl_1_bss_8C[0]->trans.y, lbl_1_bss_8C[0]->trans.z);
}

/* 370 insns */
void fn_1_7698(HU3DMODEL *model, Mtx *mtx)
{
    M525_PLAYER *players[4];
    float x0;
    float y0;
    float x1;
    float y1;
    s32 c;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_8C[i]->data;
    }
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    HuSprTexLoad(espanim[esprite[lbl_1_bss_58].animNo].anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    x0 = 0.0f;
    y0 = 0.0f;
    x1 = -500.0f;
    y1 = 0.0f;
    c = (lbl_1_bss_80 == 1002 || lbl_1_bss_80 == 1003) ? 95.625 : 255.0;
    for (i = 0; lbl_1_data_108[i] < 500.0f; i++) {
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 8);
        for (j = 0; j < 4; j++) {
            float ofs[4] = { 2.0f, -2.0f, -8.0f, -12.0f };
            s32 alpha[4] = { 0, 255, 255, 0 };

            GXPosition3f32(lbl_1_data_108[i], lbl_1_data_134[i] + ofs[j], 0.0f);
            GXColor4u8(c, c, c, alpha[j]);
            GXTexCoord2f32(50.0f * (lbl_1_data_108[i] / 500.0f), ofs[j] / -10.0f);
            GXPosition3f32(lbl_1_data_108[i + 1], lbl_1_data_134[i + 1] + ofs[j], 0.0f);
            GXColor4u8(c, c, c, alpha[j]);
            GXTexCoord2f32(50.0f * (lbl_1_data_108[i + 1] / 500.0f), ofs[j] / -10.0f);
        }
    }
    GXPixModeSync();
}

/* 461 insns */
void fn_1_7C60(HU3DMODEL *model, Mtx *mtx)
{
    HuVecF out[5];
    HuVecF verts[5] = { { -1.0f, -1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };
    Mtx rot;
    M525_PLAYER *players[4];
    HuVecF light = { 0.0f, 1.0f, -1.0f };
    float dot;
    float b;
    s32 i;
    s32 side;
    s32 k;
    s32 idx;

    for (i = 0; i < 4; i++) {
        players[i] = lbl_1_bss_8C[i]->data;
    }
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    PSVECNormalize(&light, &light);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (i = 0; i < 256; i++) {
        s32 col[5][3] = { { 255, 96, 96 }, { 96, 255, 104 }, { 96, 180, 255 }, { 255, 255, 90 }, { 232, 232, 232 } };
        HuVecF axis = { 1.0f, 0.0f, 0.0f };

        PSMTXRotAxisRad(rot, &lbl_1_bss_16C[i].unk020, 0.017453292f * (360.0f * (lbl_1_bss_16C[i].unk000 * lbl_1_bss_16C[i].unk02C)));
        PSMTXMultVecArray(rot, verts, out, 5);
        dot = PSVECDotProduct(&out[4], &light);
        GXBegin(GX_QUADS, GX_VTXFMT0, 8);
        for (side = 0; side < 2; side++) {
            b = (side == 0) ? dot : -dot;
            b = (b < 0.0f) ? 0.5f : 0.5f + 0.6f * b;
            b = (b > 1.0f) ? 1.0f : b;
            for (k = 0; k < 4; k++) {
                idx = (side == 0) ? k : 3 - k;
                GXPosition3f32(10.0f * out[idx].x + lbl_1_bss_16C[i].unk008, 10.0f * out[idx].y + lbl_1_bss_16C[i].unk00C,
                               10.0f * out[idx].z + lbl_1_bss_16C[i].unk010);
                GXColor4u8(b * col[lbl_1_bss_16C[i].unk004][0], b * col[lbl_1_bss_16C[i].unk004][1], b * col[lbl_1_bss_16C[i].unk004][2], 255);
            }
        }
    }
}

/* 322 insns */
void fn_1_8394(HU3DMODEL *model, Mtx *mtx)
{
    Mtx m;
    Mtx proj;
    s32 c;

    C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
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
    if (model->pos.x > 1.0f) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCLR, GX_BL_ONE, GX_LO_NOOP);
        c = 255.0f * (model->pos.x - 1.0f);
    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_DSTCLR, GX_BL_ZERO, GX_LO_NOOP);
        c = 255.0f * model->pos.x;
    }
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(1.0f, 0.0f, 0.0f);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(1.0f, 1.0f, 0.0f);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, 1.0f, 0.0f);
    GXColor4u8(c, c, c, 255);
    GXTexCoord2f32(0.0f, 1.0f);
}

/* 1917 insns */
void fn_1_889C(OMOBJ *obj)
{
    M525_PLAYER *work[4];
    s32 i;
    s32 j;
    s32 seNo;
    s32 winner;
    s32 num;
    s32 tmp;
    float rate;
    float inv;
    float col;

    lbl_1_bss_4[0]++;
    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_8C[i]->data;
    }
    for (i = 0; i < 10; i++) {
        s32 seTbl[10] = { 0x39C, 0x39C, 0x39B, 0x768, 0x769, 0x76A, 0x76B, 0x76C, 0x76D, 0x21 };

        if (lbl_1_bss_A4[i].unk000 > 3) {
            lbl_1_bss_A4[i].unk000 = 3;
        }
        if (lbl_1_bss_A4[i].unk000 > 0) {
            if (seTbl[i] != -1) {
                seNo = HuAudFXPlay(seTbl[i]);
                lbl_1_bss_A4[i].unk010 = seNo;
                HuAudFXPanning(seNo, 0.5 + (64.0f + 63.0f * lbl_1_bss_A4[i].unk004[lbl_1_bss_A4[i].unk000 - 1]));
                lbl_1_bss_A4[i].unk000--;
            }
        }
    }
    if (omSysExitReq != 0) {
        if (!WipeCheckEnd()) {
            if (lbl_1_bss_10[0] == 0) {
                HuAudFadeOut(1000);
                lbl_1_data_104[0] = 1;
                lbl_1_bss_10[0] = 1;
            }
        }
    }
    switch (lbl_1_bss_80) {
    case 1000:
        lbl_1_bss_0 += 1.0f;
        if (5.0f == lbl_1_bss_0) {
            if (lbl_1_bss_A4[2].unk000 < 3) {
                lbl_1_bss_A4[2].unk004[lbl_1_bss_A4[2].unk000] = 0.0f;
                lbl_1_bss_A4[2].unk000++;
            }
        }
        if (5.0f == lbl_1_bss_0) {
            lbl_1_data_100[0] = HuAudSStreamPlay(0x59);
        }
        if (!WipeCheckEnd()) {
            lbl_1_bss_80++;
            lbl_1_bss_0 = 0.0f;
            for (i = 0; i < 4; i++) {
                work[i]->unk028 = 2;
            }
        }
        break;

    case 1001:
        lbl_1_bss_0 += 1.0f;
        if (lbl_1_bss_0 > 30.0f) {
            lbl_1_bss_80++;
            lbl_1_bss_0 = 0.0f;
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[17], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[18], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[19], HU3D_ATTR_DISPOFF);
            Hu3DShadowMultiTPLvlSet(0.625f, -1);
            Hu3DModelAttrReset(lbl_1_bss_88->mdlId[14], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_88->mdlId[15], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[2], 7);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[4], 7);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[6], 7);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[16], 1);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[16], 3);
            Hu3DMotionTimeSet(lbl_1_bss_88->mdlId[16], 0.0f);
            for (i = 1; i < 4; i++) {
                Hu3DModelAmbSet(lbl_1_bss_8C[i]->mdlId[0], 0.375f, 0.375f, 0.375f);
                Hu3DLLightColorSet(lbl_1_bss_8C[i]->mdlId[0], work[i]->unk0C0, 0x1F, 0x1F, 0x1F, 0xFF);
                Hu3DLLightPosSet(lbl_1_bss_8C[i]->mdlId[0], work[i]->unk0C0, 0.0f, 0.0f, 500.0f, 0.0f, -1.0f, -3.0f);
            }
            if (lbl_1_bss_A4[3].unk000 < 3) {
                lbl_1_bss_A4[3].unk004[lbl_1_bss_A4[3].unk000] = 0.0f;
                lbl_1_bss_A4[3].unk000++;
            }
        }
        break;

    case 1002:
        lbl_1_bss_0 += 1.0f;
        20.0f == lbl_1_bss_0;
        if (lbl_1_bss_0 > 60.0f) {
            lbl_1_bss_80++;
            lbl_1_bss_0 = 0.0f;
        }
        break;

    case 1003:
        lbl_1_bss_0 += 1.0f;
        if (lbl_1_bss_0 > 180.0f) {
            lbl_1_bss_80++;
            lbl_1_bss_0 = 0.0f;
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[0], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[1], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[2], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[4], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[6], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[10], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[11], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[12], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[16], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[63], 1);
            Hu3DModelCameraSet(lbl_1_bss_88->mdlId[14], 2);
            for (i = 1; i < 4; i++) {
                Hu3DModelAmbSet(lbl_1_bss_8C[i]->mdlId[0], 1.0f, 1.0f, 1.0f);
            }
            for (i = 0; i < 4; i++) {
                Hu3DModelLayerSet(lbl_1_bss_88->mdlId[i + 0x17], 2);
            }
            for (i = 0; i < 20; i++) {
                Hu3DModelCameraSet(lbl_1_bss_88->mdlId[i + 0x17], 1);
                Hu3DModelLayerSet(lbl_1_bss_88->mdlId[i + 0x17], 4);
                Hu3DModelShadowDispOff(lbl_1_bss_88->mdlId[i + 0x17]);
            }
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[15], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_88->mdlId[14], 0.45f, 0.0f, 0.0f);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[13], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[5], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_88->mdlId[7], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[2], 0);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[4], 0);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[6], 0);
            Hu3DModelLayerSet(lbl_1_bss_88->mdlId[16], 0);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[0]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[1]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[2]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[12]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[6]);
            Hu3DModelShadowMapObjReset(lbl_1_bss_88->mdlId[11]);
            lbl_1_bss_4C.x = 0.0f;
            lbl_1_bss_4C.y = 10000.0f;
            lbl_1_bss_4C.z = 0.0f;
            lbl_1_bss_40.x = 0.0f;
            lbl_1_bss_40.y = 0.0f;
            lbl_1_bss_40.z = -1.0f;
            lbl_1_bss_34.x = 0.0f;
            lbl_1_bss_34.y = 0.0f;
            lbl_1_bss_34.z = 0.0f;
            Hu3DShadowMultiPosSet(&lbl_1_bss_4C, &lbl_1_bss_40, &lbl_1_bss_34, -1);
        }
        break;

    case 1004:
        lbl_1_bss_0 += 1.0f;
        if (1.0f == lbl_1_bss_0) {
            if (lbl_1_bss_A4[2].unk010 != -1) {
                HuAudFXFadeOut(lbl_1_bss_A4[2].unk010, 2000);
                lbl_1_bss_A4[2].unk010 = -1;
            }
        }
        if (21.0f == lbl_1_bss_0) {
            Hu3DModelAttrReset(lbl_1_bss_88->mdlId[16], HU3D_MOTATTR_PAUSE);
        }
        if (!(lbl_1_bss_0 < 20.0f)) {
            if (lbl_1_bss_0 < 80.0f) {
                Hu3DModelPosSet(lbl_1_bss_88->mdlId[14], (1.0 - 0.55) + 0.55 * ((lbl_1_bss_0 - 20.0f) / 60.0f), 0.0f, 0.0f);
            } else if (80.0f == lbl_1_bss_0) {
                Hu3DModelAttrSet(lbl_1_bss_88->mdlId[14], HU3D_ATTR_DISPOFF);
            }
        }
        if (lbl_1_bss_0 > 20.0f && lbl_1_bss_0 <= 80.0f) {
            rate = (lbl_1_bss_0 - 20.0f) / 60.0f;
            inv = 1.0f - rate;
            col = 255.0 * (rate + 0.2777777777777778 * inv);
            for (i = 1; i < 4; i++) {
                Hu3DLLightColorSet(lbl_1_bss_8C[i]->mdlId[0], work[i]->unk0C0, col, col, col, 0xFF);
                Hu3DLLightPosSet(lbl_1_bss_8C[i]->mdlId[0], work[i]->unk0C0, 0.0f, 500.0f * rate, 500.0f * inv, 0.0f,
                                 -3.0f * rate + -2.0f * inv, -1.0f * rate + -2.0f * inv);
            }
        }
        if (5.0f == lbl_1_bss_0) {
            if (lbl_1_bss_7A < 0) {
                lbl_1_bss_7A = GameMesMgStartCreate();
            }
        }
        if (lbl_1_bss_0 >= 5.0f) {
            if (!GameMesStatGet(lbl_1_bss_7A)) {
                if (lbl_1_bss_7A >= 0) {
                    lbl_1_bss_80++;
                    lbl_1_bss_74 = 1800;
                    lbl_1_bss_7A = -1;
                    lbl_1_bss_0 = 0.0f;
                    for (i = 0; i < 4; i++) {
                        Hu3DModelCameraSet(lbl_1_bss_8C[i]->mdlId[0], 1);
                        Hu3DModelCameraSet(lbl_1_bss_88->mdlId[16], 1);
                    }
                }
            }
        }
        break;

    case 1005:
        lbl_1_bss_0 += 1.0f;
        if (lbl_1_bss_74 == 1800) {
            lbl_1_bss_78 = GameMesTimerCreate(lbl_1_bss_74 / 60);
            GameMesPosSet(lbl_1_bss_78, 288.0f, 64.0f);
        }
        if (lbl_1_bss_74 <= 3600) {
            GameMesTimerValueSet(lbl_1_bss_78, (lbl_1_bss_74 + 58) / 60);
        }
        lbl_1_bss_74--;
        if (lbl_1_bss_74 > 0 && lbl_1_data_FC[0] == -1) {
            break;
        }
        lbl_1_bss_80 = 1006;
        lbl_1_bss_0 = 0.0f;
        lbl_1_data_FC[0] = (lbl_1_data_FC[0] != -1) ? lbl_1_data_FC[0] : 1;
        if (lbl_1_data_FC[0] == 1) {
            for (i = 0; i < 20; i++) {
                lbl_1_bss_316C[i].unk014 = 1;
            }
        }
        break;

    case 1006:
        if (lbl_1_bss_7A < 0 && 0.0f == lbl_1_bss_0) {
            GameMesTimerEnd(lbl_1_bss_78);
            lbl_1_bss_7A = GameMesMgFinishCreate();
            if (lbl_1_data_100[0] != -1) {
                HuAudSStreamFadeOut(lbl_1_data_100[0], 100);
            }
        } else if (!GameMesStatGet(lbl_1_bss_7A) && lbl_1_bss_0 >= 180.0f) {
            lbl_1_bss_80++;
            lbl_1_bss_0 = 0.0f;
            if (lbl_1_bss_A4[1].unk010 != -1) {
                HuAudFXStop(lbl_1_bss_A4[1].unk010);
                lbl_1_bss_A4[1].unk010 = -1;
            }
            if (lbl_1_bss_A4[0].unk000 < 3) {
                lbl_1_bss_A4[0].unk004[lbl_1_bss_A4[0].unk000] = 0.0f;
                lbl_1_bss_A4[0].unk000++;
            }
            if (lbl_1_data_FC[0] != 4) {
                GWMgCoinBonusSet(work[lbl_1_data_FC[0]]->unk004, 10);
                if (lbl_1_data_FC[0] != 0) {
                    GWMgCoinBonusSet(work[2]->unk004, 10);
                    GWMgCoinBonusSet(work[3]->unk004, 10);
                }
                lbl_1_bss_7A = GameMesCreate(4, 3, work[lbl_1_data_FC[0]]->unk00C,
                                             (lbl_1_data_FC[0] == 0) ? -1 : work[2]->unk00C,
                                             (lbl_1_data_FC[0] == 0) ? -1 : work[3]->unk00C, -1);
                HuAudSStreamPlay(0x79);
            } else {
                lbl_1_bss_7A = GameMesMgDrawCreate();
                HuAudSStreamPlay(0x7B);
            }
        }
        lbl_1_bss_0 += (lbl_1_data_FC[0] == 0)
            ? ((lbl_1_bss_0 < 175.0f || work[0]->unk028 == 4) ? 1 : 0)
            : ((60.0f != lbl_1_bss_0
                || ((work[1]->unk030 != 0 || work[1]->unk018 == 0) && (work[2]->unk030 != 0 || work[2]->unk018 == 0)
                    && (work[3]->unk030 != 0 || work[3]->unk018 == 0))) ? 1 : 0);
        if (lbl_1_data_FC[0] == 1 && 61.0f == lbl_1_bss_0) {
            s32 order[3] = { -2, -2, -2 };

            num = 0;
            for (j = 0; j < 3; j++) {
                winner = -1;
                if (work[j + 1]->unk030 == 0) {
                    num++;
                    for (i = 0; i < 3; i++) {
                        if (winner == -1) {
                            if (order[i] == -2 || lbl_1_bss_8C[order[i] + 1]->trans.x > lbl_1_bss_8C[j + 1]->trans.x) {
                                winner = order[i];
                                order[i] = j;
                            }
                        } else {
                            tmp = order[i];
                            order[i] = winner;
                            winner = tmp;
                        }
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                if (order[i] >= 0) {
                    work[order[i] + 1]->unk08C = i - (num - 1) / 2.0f;
                }
            }
            for (i = 1; i < 4; i++) {
                if (work[i]->unk030 == 0) {
                    work[i]->unk028 = 4;
                    work[i]->unk04C = lbl_1_bss_8C[i]->trans.x;
                    work[i]->unk050 = lbl_1_bss_8C[i]->trans.y;
                    work[i]->unk044 = 0;
                }
            }
            if (lbl_1_bss_A4[8].unk000 < 3) {
                lbl_1_bss_A4[8].unk004[lbl_1_bss_A4[8].unk000] = 0.0f;
                lbl_1_bss_A4[8].unk000++;
            }
            for (i = 0; i < 20; i++) {
                if (lbl_1_bss_316C[i].unk000 != 0) {
                    lbl_1_bss_316C[i].unk000 = 0;
                    Hu3DModelAttrSet(lbl_1_bss_88->mdlId[i + 0x17], HU3D_ATTR_DISPOFF);
                }
            }
        }
        break;

    case 1007:
        lbl_1_bss_0 += 1.0f;
        for (i = 0; i < 4; i++) {
            if (lbl_1_data_FC[0] == 4 || lbl_1_data_FC[0] == i / 2) {
                work[i]->unk028 = (work[i]->unk028 == 4) ? 6 : work[i]->unk028;
            }
        }
        if (210.0f < lbl_1_bss_0 && lbl_1_bss_10[0] == 0) {
            if (lbl_1_bss_A4[0].unk010 != -1) {
                HuAudFXFadeOut(lbl_1_bss_A4[0].unk010, 1000);
                lbl_1_bss_A4[0].unk010 = -1;
            }
            lbl_1_bss_7A = -1;
            lbl_1_bss_10[0] = 1;
        }
        break;

    default:
        OSReport(lbl_1_data_1B8, lbl_1_bss_80);
        break;
    }
}

/* .data after jumptable_1_data_1D4 (0x1D4): defined after fn_1_889C so CodeWarrior emits the jumptable first */
/* 0x1F4 */ char lbl_1_data_1F4[] = "******* M525 ObjectSetup *********\n";

static inline void fn_1_A690_Clear(M525_339C board)
{
    M525_339C *boardP = &board;

    memset(boardP, 0, sizeof(M525_339C));
}

/* 1192 insns */
void fn_1_A690(OMOBJ *obj)
{
    s32 no;
    s32 i;
    HU3DLLIGHTID light;

    no = 0;
    obj->mdlId[no] = Hu3DModelCreateData(0x530006);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, -500.0f, 500.0f, 0.0f, 1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    no = 1;
    obj->mdlId[no] = Hu3DModelCreateData(0x530007);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, -500.0f, 500.0f, 0.0f, 1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    no = 2;
    obj->mdlId[no] = Hu3DModelCreateData(0x530000);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, 500.0f, 500.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    fn_1_A690_Clear(lbl_1_bss_339C);
    lbl_1_bss_339C.unk010 = 1400.0f;
    lbl_1_bss_339C.unk004 = -35.0f;
    lbl_1_bss_339C.unk008 = 0.0f;
    lbl_1_bss_339C.unk00C = 40.0f;
    lbl_1_bss_339C.unk00C = fabs(lbl_1_bss_339C.unk004 / ((1.0f + lbl_1_bss_339C.unk00C) * (lbl_1_bss_339C.unk00C / 2.0f)));
    Hu3DModelPosSet(obj->mdlId[no], 0.0f, lbl_1_bss_339C.unk010, 0.0f);
    Hu3DModelRotSet(obj->mdlId[no], 0.0f, 0.0f, lbl_1_bss_339C.unk004);
    Hu3DModelCameraSet(obj->mdlId[no], 1);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    obj->mdlId[no + 1] = Hu3DModelLink(obj->mdlId[no]);
    Hu3DModelPosSet(obj->mdlId[no + 1], 0.0f, lbl_1_bss_339C.unk010, 0.0f);
    Hu3DModelCameraSet(obj->mdlId[no + 1], 2);
    Hu3DModelShadowSet(obj->mdlId[no + 1]);
    Hu3DModelAttrSet(obj->mdlId[no + 1], HU3D_ATTR_MOTION_OFF);
    for (i = 0; i < 2; i++) {
        no = i * 2 + 4;
        obj->mdlId[no] = Hu3DModelCreateData((i == 0) ? 0x530001 : 0x530002);
        Hu3DModelLayerSet(obj->mdlId[no], 0);
        Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
        light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, 500.0f, 500.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
        Hu3DLLightInfinitytSet(obj->mdlId[no], light);
        Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
        Hu3DModelCameraSet(obj->mdlId[no], 1);
        Hu3DModelShadowMapSet(obj->mdlId[no]);
        obj->mdlId[no + 1] = Hu3DModelLink(obj->mdlId[no]);
        Hu3DModelCameraSet(obj->mdlId[no + 1], 2);
        Hu3DModelShadowSet(obj->mdlId[no + 1]);
        Hu3DModelAttrSet(obj->mdlId[no + 1], HU3D_ATTR_MOTION_OFF);
    }
    no = 8;
    obj->mdlId[no] = Hu3DModelCreateData(0x530003);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, 500.0f, 500.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    Hu3DModelCameraSet(obj->mdlId[no], 1);
    for (i = 0; i < 2; i++) {
        no = i + 10;
        obj->mdlId[no] = Hu3DModelCreateData((i == 0) ? 0x530004 : 0x530005);
        Hu3DModelLayerSet(obj->mdlId[no], 0);
        Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
        light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, 500.0f, 500.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
        Hu3DLLightInfinitytSet(obj->mdlId[no], light);
        Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
        Hu3DModelCameraSet(obj->mdlId[no], 2);
        Hu3DModelShadowMapSet(obj->mdlId[no]);
    }
    no = 12;
    obj->mdlId[no] = Hu3DModelCreateData(0x530008);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, -500.0f, 500.0f, 0.0f, 1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    Hu3DModelShadowMapSet(obj->mdlId[no]);
    no = 16;
    obj->mdlId[no] = Hu3DModelCreateData(0x530009);
    Hu3DModelLayerSet(obj->mdlId[no], 7);
    Hu3DMotionTimeSet(obj->mdlId[no], 10.0f);
    Hu3DMotionSpeedSet(obj->mdlId[no], 0.25f);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_PAUSE);
    light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, -500.0f, 500.0f, 0.0f, 1.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[no], light);
    Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    memset(lbl_1_bss_316C, 0, sizeof(lbl_1_bss_316C));
    for (i = 0; i < 20; i++) {
        s32 tbl[5] = { 0x53000D, 0x53000E, 0x53000F, 0x530010, 0x530011 };

        no = i + 23;
        if (i < 5) {
            obj->mdlId[no] = Hu3DModelCreateData(tbl[i]);
        } else {
            obj->mdlId[no] = Hu3DModelLink(obj->mdlId[i % 5 + 23]);
        }
        Hu3DModelLayerSet(obj->mdlId[no], 0);
        Hu3DModelAttrSet(obj->mdlId[no], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_ZCMP_OFF | HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(obj->mdlId[no], 2);
        light = Hu3DLLightCreate(obj->mdlId[no], 0.0f, 500.0f, 500.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
        Hu3DLLightInfinitytSet(obj->mdlId[no], light);
        Hu3DLLightStaticSet(obj->mdlId[no], light, TRUE);
        lbl_1_bss_316C[i].unk018 = light;
        obj->mdlId[no + 20] = Hu3DModelLink(obj->mdlId[no]);
        Hu3DModelCameraSet(obj->mdlId[no + 20], 2);
        Hu3DModelShadowSet(obj->mdlId[no + 20]);
        Hu3DModelAttrSet(obj->mdlId[no + 20], HU3D_ATTR_MOTION_OFF);
    }
    for (i = 0; i < 3; i++) {
        no = i + 17;
        if (i == 0) {
            obj->mdlId[no] = Hu3DModelCreateData(0x53000A);
        } else {
            obj->mdlId[no] = Hu3DModelLink(obj->mdlId[17]);
        }
        Hu3DModelLayerSet(obj->mdlId[no], 3);
        Hu3DModelPosSet(obj->mdlId[no], lbl_1_data_160[i + 1][0], lbl_1_data_160[i + 1][1], lbl_1_data_160[i + 1][2]);
        Hu3DModelCameraSet(obj->mdlId[no], 2);
    }
    for (i = 0; i < 3; i++) {
        no = i + 20;
        if (i == 0) {
            obj->mdlId[no] = Hu3DModelCreateData(0x53000B);
        } else {
            obj->mdlId[no] = Hu3DModelLink(obj->mdlId[20]);
        }
        Hu3DModelLayerSet(obj->mdlId[no], 7);
        Hu3DModelCameraSet(obj->mdlId[no], 1);
        Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    }
    no = 13;
    obj->mdlId[no] = Hu3DModelCreateData(0x53000C);
    Hu3DModelLayerSet(obj->mdlId[no], 0);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_MOTION_OFF);
    Hu3DModelCameraSet(obj->mdlId[no], 3);
    Hu3DModelShadowSet(obj->mdlId[no]);
    Hu3DModelScaleSet(obj->mdlId[no], 2.0f, 2.0f, 2.0f);
    espDispOff(lbl_1_bss_58 = espEntry(0x530012, 0, 0));
    no = 63;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_7698);
    Hu3DModelLayerSet(obj->mdlId[no], 3);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    no = 14;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_8394);
    Hu3DModelLayerSet(obj->mdlId[no], 6);
    Hu3DModelCameraSet(obj->mdlId[no], 1);
    Hu3DModelPosSet(obj->mdlId[no], 0.375f, 0.0f, 0.0f);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    no = 15;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_8394);
    Hu3DModelLayerSet(obj->mdlId[no], 6);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    Hu3DModelPosSet(obj->mdlId[no], 1.2f, 0.0f, 0.0f);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    memset(lbl_1_bss_16C, 0, sizeof(lbl_1_bss_16C));
    no = 64;
    obj->mdlId[no] = Hu3DHookFuncCreate(fn_1_7C60);
    Hu3DModelLayerSet(obj->mdlId[no], 7);
    Hu3DModelCameraSet(obj->mdlId[no], 2);
    Hu3DModelAttrSet(obj->mdlId[no], HU3D_ATTR_DISPOFF);
    for (i = 0; i < 256; i++) {
        lbl_1_bss_16C[i].unk000 = i;
        lbl_1_bss_16C[i].unk00C = -1000.0f;
    }
    obj->objFunc = fn_1_5AF4;
}

/* 289 insns */
void fn_1_B930(OMOBJ *obj)
{
    s32 order[4] = { 0, 1, 2, 3 };
    s32 n;
    s32 team;
    M525_PLAYER *work;
    s32 i;
    s32 j;

    n = 0;
    team = obj->work[0] != 0;
    work = obj->data;
    memset(work, 0, sizeof(M525_PLAYER));
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (i == GwPlayerConf[j].grp) {
                order[n] = j;
                n++;
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
    work->unk024 = 1;
    work->unk028 = 2;
    work->unk0AC = 0;
    if (work->unk000 == 0) {
        work->unk040 = 255;
    }
    obj->mdlId[0] = CharModelCreate(work->unk00C, (work->unk000 == 0) ? 2 : 2);
    Hu3DModelLayerSet(obj->mdlId[0], 2);
    Hu3DModelCameraSet(obj->mdlId[0], 2);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    if (work->unk000 == 0) {
        Hu3DModelShadowSet(obj->mdlId[0]);
    }
    CharEffectLayerSet(3);
    work->unk0C0 = Hu3DLLightCreate(obj->mdlId[0], 0.0f, 500.0f, 0.0f, 0.0f, -3.0f, -1.0f, 255, 255, 255);
    Hu3DLLightInfinitytSet(obj->mdlId[0], work->unk0C0);
    Hu3DLLightStaticSet(obj->mdlId[0], work->unk0C0, 1);
    Hu3DModelAmbSet(obj->mdlId[0], 1.0f, 1.0f, 1.0f);
    work->unk018 = (work->unk000 == 0) ? 1 : 0;
    work->unk01C = -1;
    for (i = 0; i < ((team == 0) ? 6 : 10); i++) {
        obj->mtnId[i] = CharMotionCreate(work->unk00C, lbl_1_data_34[team][i]);
    }
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[work->unk018]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    obj->trans.x = lbl_1_data_160[work->unk000][0];
    obj->trans.y = lbl_1_data_160[work->unk000][1];
    obj->trans.z = lbl_1_data_160[work->unk000][2];
    obj->rot.y = lbl_1_data_160[work->unk000][3];
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->rot.x = obj->rot.z = 0.0f;
    obj->objFunc = fn_1_654;
}

/* 21 insns */
void fn_1_BDB4(OMOBJ *obj)
{
    lbl_1_bss_80 = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    obj->objFunc = fn_1_889C;
}

/* 453 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    s32 i;

    OSReport(lbl_1_data_1F4);
    lbl_1_bss_7C = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_7C);
    Hu3DCameraCreate(3);
    for (i = 0; i < 2; i++) {
        s32 w = 640;
        s32 h = w * 3 / 4;
        s32 x = (640 - w) / 2;
        s32 y = (480 - h) / 2;

        Hu3DCameraPerspectiveSet((i == 0) ? 1 : 2, 25.0f, 40.0f, 20000.0f, 1.2f);
        Hu3DCameraViewportSet((i == 0) ? 1 : 2, x, y, w, h, 0.0f, 1.0f);
        Hu3DCameraScissorSet((i == 0) ? 1 : 2, x, y, w, h);
    }
    for (i = 0; i < 2; i++) {
        CZoomM[i] = 2800.0f;
        CenterM[i].x = 0.0f;
        CenterM[i].y = 390.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = 0.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
    }
    Hu3DLighInit();
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.75f, -1.0f, -0.5f };
        GXColor lightColor = { 0 };

        lbl_1_bss_4C.x = -300.0f;
        lbl_1_bss_4C.y = -400.0f;
        lbl_1_bss_4C.z = 3000.0f;
        lbl_1_bss_40.x = 0.0f;
        lbl_1_bss_40.y = 1.0f;
        lbl_1_bss_40.z = 0.0f;
        lbl_1_bss_34.x = -50.0f;
        lbl_1_bss_34.y = 260.0f;
        lbl_1_bss_34.z = -20.0f;
        Hu3DShadowMultiCreate(32.0f, 200.0f, 20000.0f, 3);
        Hu3DShadowMultiPosSet(&lbl_1_bss_4C, &lbl_1_bss_40, &lbl_1_bss_34, -1);
        Hu3DShadowMultiTPLvlSet(0.0f, -1);
        Hu3DShadowMultiColSet(0, 0, 0, -1);
    }
    lbl_1_bss_7A = -1;
    lbl_1_data_FC[0] = -1;
    lbl_1_bss_88 = omAddObjEx(lbl_1_bss_7C, 101, 65, 0, 1, fn_1_A690);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_8C[i] = omAddObjEx(lbl_1_bss_7C, 100, 2, 10, 0, fn_1_B930);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M525_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    {
        float posX[3];
        s32 used[3] = { 0, 0, 0 };
        s32 r;

        posX[0] = lbl_1_data_160[1][0];
        posX[1] = lbl_1_data_160[2][0];
        posX[2] = lbl_1_data_160[3][0];

        for (i = 0; i < 3; i++) {
            do {
                r = rand8();
            } while (r % 4 == 3 || used[r % 3] == 1);
            r = r % 3;
            used[r] = 1;
            lbl_1_data_160[i + 1][0] = posX[r];
        }
    }
    lbl_1_bss_9C = omAddObjEx(lbl_1_bss_7C, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_9C->work[0] = 2;
    lbl_1_bss_A0 = omAddObjEx(lbl_1_bss_7C, 102, 0, 0, -1, fn_1_BDB4);
    lbl_1_bss_84 = omAddObjEx(lbl_1_bss_7C, 103, 1, 0, -1, fn_1_C51C);
}

/* 22 insns */
void fn_1_C51C(OMOBJ *obj)
{
    if (lbl_1_bss_10[0] != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        obj->objFunc = fn_1_C574;
    }
}

/* 46 insns */
void fn_1_C574(OMOBJ *obj)
{
    M525_PLAYER *work;
    int i;

    if (WipeCheckEnd()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_8C[i]->data;
        CharModelKill(work->unk00C);
    }
    if (lbl_1_bss_7A >= 0) {
        GameMesKill(lbl_1_bss_7A);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_104[0], 1);
}

/* sqrtf (51 insns) is the extern inline in libc/math.h -- CodeWarrior
 * emits it per-TU from the #include. Do not hand-write it. */

/* fabs (2 insns) is the extern inline in libc/math.h -- CodeWarrior
 * emits it per-TU from the #include. Do not hand-write it. */

