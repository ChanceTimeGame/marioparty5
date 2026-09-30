/*
 * m505dll m505.c -- minigame #19, one translation unit, 17 functions in
 * reference order. Line ranges are into build/mp5-asm/m505Dll/asm/REL/m505Dll/m505.s.
 *
 * math.h (fork A, 2026-09-23). Unlike m566, this TU needs NO suppression of
 * libc/math.h; it is included normally and three of the reference's facts
 * follow from that alone:
 *   - .rodata 0x0..0x10 (dtk's pad_03_00000000_rodata: 0.5, 3.0) is libc
 *     sqrtf's `static const double _half/_three`, which CodeWarrior emits
 *     for every TU that includes libc/math.h;
 *   - fn_1_1828's six `frsqrte` sequences are that sqrtf inlined (the
 *     inliner pools .5/3.0 as fresh literals, lbl_1_rodata_6E0/708, and
 *     leaves _half/_three unreferenced);
 *   - fn_1_1828's three `fabs fN,fN` (0x2DBC, 0x2E04, 0x3B84, each with the
 *     O0 stfd/lfd parameter and return copies) are libc's extern-inline fabs.
 * The one irregularity is fn_1_4FB4: its three fabs calls are `bl fabs`
 * (0x5B88, 0x5BE0, 0x897C) to an out-of-line 2-insn copy at .text 0x12188.
 * No pragma is needed (fork D, measured with the whole function written):
 * fn_1_4FB4 is so large that CodeWarrior's inliner stops inlining inside it
 * by itself, calls fabs, and emits libc's fabs as a weak `W fabs` in its own
 * .text section after fn_1_120D0, exactly where dtk shows it. The earlier
 * `#pragma dont_inline on` around fn_1_4FB4 also produced the calls but added
 * an `addi rX,r1,<array>` after every local aggregate initialiser that the
 * reference does not have (and a 5th saved GPR). Do not write fabs by hand.
 *
 * On the host math.h is the ordinary one; humath.h supplies M_PI.
 */

#include "REL/m505dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "game/wipe.h"
/* The reference's own declaration returns a value: fn_1_4FB4 0x5AB4 copies
 * the result (`mr r10,r3`) into a dead local. game/hsfex.h is not included on
 * GC so this declaration can differ; nothing else from it is used. */
s32 Hu3D3Dto2D(HuVecF *src, s16 cameraBit, HuVecF *dst);
#include "game/init.h"
#include "game/flag.h"
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

/* no SDK header declares rand8 */
int rand8(void);

/* fn_1_4FB4 calls abs out of line (`bl abs` 0x8814); libc/stdlib.h would
 * turn it into the __abs builtin, so declare it instead of including that. */
int abs(int);

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* u8 lbl_1_rodata_10[1] = { 0x00 }; */
/* 0x11 */ /* u8 lbl_1_rodata_11[1] = { 0x00, 0x00, 0xFF }; */
/* 0x14 */ /* u8 lbl_1_rodata_14[1] = { 0xFF }; */
/* 0x15 */ /* u8 lbl_1_rodata_15[1] = { 0xFF, 0xFF, 0xFF }; */
/* 0x18 */ /* float lbl_1_rodata_18 = 0.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 255.0f; */
/* 0x20 */ /* float lbl_1_rodata_20 = 1.0f; */
/* 0x24 */ /* float lbl_1_rodata_24 = -1.0f; */
/* 0x28 */ /* float lbl_1_rodata_28 = 0.999969f; */
/* 0x30 */ /* double lbl_1_rodata_30 = 4503601774854144; */
/* 0x38 */ /* double lbl_1_rodata_38 = 5; */
/* 0x40 */ /* double lbl_1_rodata_40 = 20; */
/* 0x48 */ /* double lbl_1_rodata_48 = 0.0078125; */
/* 0x50 */ /* double lbl_1_rodata_50 = 25; */
/* 0x58 */ /* double lbl_1_rodata_58 = 0.03125; */
/* 0x60 */ /* double lbl_1_rodata_60 = -32; */
/* 0x68 */ /* double lbl_1_rodata_68 = 3.141592653589793; */
/* 0x70 */ /* double lbl_1_rodata_70 = 180; */
/* 0x78 */ /* s32 lbl_1_rodata_78[10] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xA0 */ /* s32 lbl_1_rodata_A0[12] = { 0x00000028, 0x0000001E, 0x0000000C, 0x00000006, 0x00000006, 0x00000006, 0x00000005, 0x00000003, 0x00000078, 0x00000046, 0x00000014, 0x00000005 }; */
/* 0xD0 */ /* s32 lbl_1_rodata_D0[4] = { 0x00000064, 0x0000012C, 0x00000320, 0x000007D0 }; */
/* 0xE0 */ /* s32 lbl_1_rodata_E0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xEC */ /* s32 lbl_1_rodata_EC[2] = { 0x42180000, 0x00000000 }; */
/* 0xF4 */ /* s32 lbl_1_rodata_F4[360] = { 0x00000000, 0x41200000, 0x3E000000, 0x3EA00000, 0x3F300000, 0x3F800000, 0x40A00000, 0x41D00000, 0x00000000, 0x3F800000, 0x42040000, 0xBDE00000, 0x3E600000, 0x3F300000, 0x3F900000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x41100000, 0x3E000000, 0x3DE00000, 0x3F300000, 0x3F900000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x41E80000, 0x3D800000, 0x3DC00000, 0x3F300000, 0x3F900000, 0x00000000, 0x40400000, 0xBE700000, 0x40000000, 0x41500000, 0x3E000000, 0x3E700000, 0x3F300000, 0x3F900000, 0x00000000, 0x41000000, 0xBE300000, 0x00000000, 0x00000000, 0x3E500000, 0x3E800000, 0x3F300000, 0x3F900000, 0x40800000, 0x41880000, 0xBDC00000, 0x3F800000, 0x41000000, 0x00000000, 0x3EA80000, 0x3F300000, 0x3F900000, 0x40800000, 0x41500000, 0xBE400000, 0x3F800000, 0x41F00000, 0x00000000, 0x3EA80000, 0x3F300000, 0x3F900000, 0x40800000, 0x41500000, 0xBE400000, 0x40000000, 0x40400000, 0x00000000, 0x3F680000, 0x3F300000, 0x3F900000, 0x40800000, 0x41500000, 0xBEA80000, 0x40000000, 0x41A00000, 0x00000000, 0x3F860000, 0x3F300000, 0x3F900000, 0x40800000, 0x41100000, 0xBEB80000, 0x00000000, 0x41200000, 0x00000000, 0x3E800000, 0x3EE00000, 0x3F700000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x42000000, 0x00000000, 0x3E800000, 0x3EE00000, 0x3F700000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x41000000, 0x00000000, 0x3E800000, 0x3EE00000, 0x3F700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x41900000, 0x00000000, 0x3EB80000, 0x3EE00000, 0x3F700000, 0x00000000, 0x00000000, 0x00000000, 0x40000000, 0x40400000, 0x00000000, 0x3EB80000, 0x3EE00000, 0x3F700000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41200000, 0x00000000, 0x3EC80000, 0x3F4C0000, 0x3FAE0000, 0x00000000, 0x00000000, 0x3DC00000, 0x3F800000, 0x41F80000, 0x00000000, 0x3EC80000, 0x3F4C0000, 0x3FAE0000, 0x00000000, 0x00000000, 0x3DC00000, 0x3F800000, 0x41000000, 0x00000000, 0x3EC80000, 0x3F4C0000, 0x3FAE0000, 0x00000000, 0x00000000, 0x3DC00000, 0x40000000, 0x41E80000, 0x00000000, 0x3C800000, 0x3F4C0000, 0x3FAE0000, 0x00000000, 0x00000000, 0x3DC00000, 0x40000000, 0x41400000, 0x00000000, 0x3C800000, 0x3F4C0000, 0x3FAE0000, 0x00000000, 0x00000000, 0x3DC00000, 0x00000000, 0x41200000, 0x00000000, 0x3F860000, 0x3F580000, 0x3FAC0000, 0x00000000, 0x41B80000, 0x3EE80000, 0x3F800000, 0x42100000, 0x00000000, 0x3F860000, 0x3F500000, 0x3FAC0000, 0x00000000, 0x41D00000, 0x3E500000, 0x3F800000, 0x41100000, 0x00000000, 0x3F860000, 0x3F500000, 0x3FAC0000, 0x00000000, 0x41D00000, 0x3E500000, 0x40000000, 0x40800000, 0x00000000, 0x3FA00000, 0x3F500000, 0x3FAC0000, 0x00000000, 0x41D00000, 0x3E100000, 0x40000000, 0x41B00000, 0x00000000, 0x3FA00000, 0x3F500000, 0x3FAC0000, 0x00000000, 0x41D00000, 0x3E100000, 0x00000000, 0x41200000, 0xBC800000, 0x3FB40000, 0x3EF00000, 0x3FAC0000, 0x00000000, 0x42040000, 0x3F7C0000, 0x3F800000, 0x41A80000, 0x00000000, 0x40330000, 0x3EF00000, 0x3FA00000, 0x00000000, 0x41B00000, 0xBEF00000, 0x3F800000, 0x3F800000, 0x00000000, 0x40330000, 0x3EF00000, 0x3FA00000, 0x00000000, 0x41B00000, 0xBEF00000, 0x40000000, 0x41E80000, 0x00000000, 0x40140000, 0x3EF00000, 0x3FA00000, 0x00000000, 0x42000000, 0xBF580000, 0x40000000, 0x41500000, 0x00000000, 0x403C0000, 0x3EF00000, 0x3FA00000, 0x00000000, 0x41E80000, 0xBF700000, 0x00000000, 0x00000000, 0x00000000, 0x3EB80000, 0x3F200000, 0x3F540000, 0x40800000, 0x41980000, 0x3DE00000, 0x3F800000, 0x41980000, 0x00000000, 0x3E500000, 0x3F200000, 0x3F540000, 0x00000000, 0x40000000, 0xBE300000, 0x3F800000, 0x42240000, 0x00000000, 0x3E500000, 0x3F200000, 0x3F540000, 0x00000000, 0x40000000, 0xBE300000, 0x40000000, 0x41700000, 0x00000000, 0x00000000, 0x3F200000, 0x3F540000, 0x00000000, 0x00000000, 0xBE300000, 0x40000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F200000, 0x3F540000, 0x00000000, 0x00000000, 0xBE300000, 0x00000000, 0x00000000, 0x00000000, 0xBF3C0000, 0x3FA80000, 0x3FB20000, 0x00000000, 0x41700000, 0x3E600000, 0x3F800000, 0x3F800000, 0x00000000, 0xBF8A0000, 0x3FA80000, 0x3FB20000, 0x00000000, 0x00000000, 0xBEA80000, 0x3F800000, 0x41B00000, 0x00000000, 0xBF8A0000, 0x3FA80000, 0x3FB20000, 0x00000000, 0x00000000, 0xBEA80000, 0x40000000, 0x3F800000, 0x00000000, 0xBF960000, 0x3FA80000, 0x3FB20000, 0x00000000, 0x00000000, 0xBE900000, 0x40000000, 0x41880000, 0x00000000, 0xBF960000, 0x3FA80000, 0x3FB20000, 0x00000000, 0x00000000, 0xBE900000 }; */
/* 0x694 */ /* s32 lbl_1_rodata_694[10] = { 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001 }; */
/* 0x6BC */ /* float lbl_1_rodata_6BC = 2000.0f; */
/* 0x6C0 */ /* float lbl_1_rodata_6C0 = 600.0f; */
/* 0x6C4 */ /* float lbl_1_rodata_6C4 = 100.0f; */
/* 0x6C8 */ /* float lbl_1_rodata_6C8 = 20.0f; */
/* 0x6CC */ /* float lbl_1_rodata_6CC = 700.0f; */
/* 0x6D0 */ /* float lbl_1_rodata_6D0 = -570.0f; */
/* 0x6D4 */ /* float lbl_1_rodata_6D4 = 570.0f; */
/* 0x6D8 */ /* float lbl_1_rodata_6D8 = -100.0f; */
/* 0x6E0 */ /* double lbl_1_rodata_6E0 = 0.5; */
/* 0x6E8 */ /* float lbl_1_rodata_6E8 = -400.0f; */
/* 0x6EC */ /* float lbl_1_rodata_6EC = 400.0f; */
/* 0x6F0 */ /* float lbl_1_rodata_6F0 = 2.0f; */
/* 0x6F4 */ /* float lbl_1_rodata_6F4 = 0.25f; */
/* 0x6F8 */ /* double lbl_1_rodata_6F8 = 0.25; */
/* 0x700 */ /* float lbl_1_rodata_700 = 0.017453292f; */
/* 0x708 */ /* double lbl_1_rodata_708 = 3; */
/* 0x710 */ /* float lbl_1_rodata_710 = 0.5f; */
/* 0x714 */ /* float lbl_1_rodata_714 = 10.0f; */
/* 0x718 */ /* float lbl_1_rodata_718 = 8.0f; */
/* 0x71C */ /* float lbl_1_rodata_71C = 50.0f; */
/* 0x720 */ /* float lbl_1_rodata_720 = 1.125f; */
/* 0x724 */ /* float lbl_1_rodata_724 = 198.0f; */
/* 0x728 */ /* float lbl_1_rodata_728 = -710.0f; */
/* 0x72C */ /* float lbl_1_rodata_72C = -610.0f; */
/* 0x730 */ /* float lbl_1_rodata_730 = 610.0f; */
/* 0x734 */ /* float lbl_1_rodata_734 = -0.1f; */
/* 0x738 */ /* float lbl_1_rodata_738 = -194.0f; */
/* 0x73C */ /* float lbl_1_rodata_73C = -1.6333333f; */
/* 0x740 */ /* double lbl_1_rodata_740 = -0.5; */
/* 0x748 */ /* float lbl_1_rodata_748 = 0.375f; */
/* 0x74C */ /* float lbl_1_rodata_74C = -1.25f; */
/* 0x750 */ /* float lbl_1_rodata_750 = 64.0f; */
/* 0x754 */ /* float lbl_1_rodata_754 = 32.0f; */
/* 0x758 */ /* float lbl_1_rodata_758 = -215.0f; */
/* 0x75C */ /* float lbl_1_rodata_75C = -0.33333334f; */
/* 0x760 */ /* double lbl_1_rodata_760 = 0.95; */
/* 0x768 */ /* float lbl_1_rodata_768 = -1110.0f; */
/* 0x76C */ /* float lbl_1_rodata_76C = -709.0f; */
/* 0x770 */ /* float lbl_1_rodata_770 = -609.0f; */
/* 0x774 */ /* float lbl_1_rodata_774 = 609.0f; */
/* 0x778 */ /* float lbl_1_rodata_778 = 12.0f; */
/* 0x77C */ /* float lbl_1_rodata_77C = 0.8f; */
/* 0x780 */ /* float lbl_1_rodata_780 = 90.0f; */
/* 0x784 */ /* float lbl_1_rodata_784 = 0.015625f; */
/* 0x788 */ /* float lbl_1_rodata_788 = 360.0f; */
/* 0x78C */ /* float lbl_1_rodata_78C = 180.0f; */
/* 0x790 */ /* double lbl_1_rodata_790 = 0.96875; */
/* 0x798 */ /* float lbl_1_rodata_798 = 179.0f; */
/* 0x79C */ /* float lbl_1_rodata_79C = 181.0f; */
/* 0x7A0 */ /* float lbl_1_rodata_7A0 = 0.75f; */
/* 0x7A8 */ /* double lbl_1_rodata_7A8 = 4503599627370496; */
/* 0x7B0 */ /* s32 lbl_1_rodata_7B0[4] = { 0x00000000, 0x00000002, 0x00000004, 0x00000006 }; */
/* 0x7C0 */ /* s32 lbl_1_rodata_7C0[6] = { 0x00000000, 0x00000000, 0x00000000, 0xC3800000, 0x43800000, 0x00000000 }; */
/* 0x7D8 */ /* s32 lbl_1_rodata_7D8[6] = { 0xBF800000, 0x00000000, 0x00000000, 0x40400000, 0x00000000, 0x00000000 }; */
/* 0x7F0 */ /* s32 lbl_1_rodata_7F0[2] = { 0x00000000, 0x00000000 }; */
/* 0x7F8 */ /* s32 lbl_1_rodata_7F8[20] = { 0x0000000A, 0x0000001E, 0x00000014, 0x00000028, 0x00000014, 0x00000028, 0x00000028, 0x0000003C, 0x00000032, 0x00000046, 0x00000046, 0x00000063, 0x0000005A, 0x00000063, 0x0000005A, 0x0000005A, 0x00000046, 0x00000050, 0x00000063, 0x00000063 }; */
/* 0x848 */ /* s32 lbl_1_rodata_848[20] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000003, 0x00000001, 0x00000002, 0x00000000, 0x00000001, 0x00000000, 0x00000002, 0x00000004, 0x00000006, 0x00000006, 0x00000008, 0x00000008, 0x00000008, 0x00000008, 0x00000008 }; */
/* 0x898 */ /* float lbl_1_rodata_898 = 0.0625f; */
/* 0x89C */ /* float lbl_1_rodata_89C = -40.0f; */
/* 0x8A0 */ /* float lbl_1_rodata_8A0 = 0.29411766f; */
/* 0x8A4 */ /* float lbl_1_rodata_8A4 = 0.0009765625f; */
/* 0x8A8 */ /* float lbl_1_rodata_8A8 = 320.0f; */
/* 0x8AC */ /* float lbl_1_rodata_8AC = 640.0f; */
/* 0x8B0 */ /* float lbl_1_rodata_8B0 = 288.0f; */
/* 0x8B4 */ /* float lbl_1_rodata_8B4 = 576.0f; */
/* 0x8B8 */ /* float lbl_1_rodata_8B8 = 240.0f; */
/* 0x8BC */ /* float lbl_1_rodata_8BC = 480.0f; */
/* 0x8C0 */ /* double lbl_1_rodata_8C0 = 0.00390625; */
/* 0x8C8 */ /* double lbl_1_rodata_8C8 = -90; */
/* 0x8D0 */ /* double lbl_1_rodata_8D0 = 1.5; */
/* 0x8D8 */ /* double lbl_1_rodata_8D8 = 0; */
/* 0x8E0 */ /* float lbl_1_rodata_8E0 = -90.0f; */
/* 0x8E4 */ /* float lbl_1_rodata_8E4 = 40.0f; */
/* 0x8E8 */ /* float lbl_1_rodata_8E8 = 6.0f; */
/* 0x8EC */ /* float lbl_1_rodata_8EC = -63.0f; */
/* 0x8F0 */ /* float lbl_1_rodata_8F0 = 450.0f; */
/* 0x8F4 */ /* float lbl_1_rodata_8F4 = 900.0f; */
/* 0x8F8 */ /* float lbl_1_rodata_8F8 = 2400.0f; */
/* 0x8FC */ /* float lbl_1_rodata_8FC = 1800.0f; */
/* 0x900 */ /* float lbl_1_rodata_900 = -4.0f; */
/* 0x904 */ /* float lbl_1_rodata_904 = -0.25f; */
/* 0x908 */ /* float lbl_1_rodata_908 = 300.0f; */
/* 0x90C */ /* float lbl_1_rodata_90C = 280.0f; */
/* 0x910 */ /* float lbl_1_rodata_910 = 120.0f; */
/* 0x914 */ /* float lbl_1_rodata_914 = 434.0f; */
/* 0x918 */ /* float lbl_1_rodata_918 = 4300.0f; */
/* 0x91C */ /* float lbl_1_rodata_91C = -50.0f; */
/* 0x920 */ /* float lbl_1_rodata_920 = -150.0f; */
/* 0x924 */ /* float lbl_1_rodata_924 = -2000.0f; */
/* 0x928 */ /* float lbl_1_rodata_928 = -1200.0f; */
/* 0x930 */ /* double lbl_1_rodata_930 = 15; */
/* 0x938 */ /* float lbl_1_rodata_938 = 14.0f; */
/* 0x93C */ /* float lbl_1_rodata_93C = -250.0f; */
/* 0x940 */ /* double lbl_1_rodata_940 = 0.75; */
/* 0x948 */ /* float lbl_1_rodata_948 = 15.0f; */
/* 0x94C */ /* float lbl_1_rodata_94C = 3.0f; */
/* 0x950 */ /* float lbl_1_rodata_950 = -2.0f; */
/* 0x958 */ /* double lbl_1_rodata_958 = 658.2857142857143; */
/* 0x960 */ /* float lbl_1_rodata_960 = -640.0f; */
/* 0x968 */ /* double lbl_1_rodata_968 = 0.875; */
/* 0x970 */ /* float lbl_1_rodata_970 = 1.5f; */
/* 0x978 */ /* double lbl_1_rodata_978 = 0.3; */
/* 0x980 */ /* double lbl_1_rodata_980 = 1.65; */
/* 0x988 */ /* float lbl_1_rodata_988 = -310.0f; */
/* 0x98C */ /* float lbl_1_rodata_98C = 30.0f; */
/* 0x990 */ /* float lbl_1_rodata_990 = 270.0f; */
/* 0x998 */ /* double lbl_1_rodata_998 = -350; */
/* 0x9A0 */ /* double lbl_1_rodata_9A0 = -500; */
/* 0x9A8 */ /* double lbl_1_rodata_9A8 = 60; */
/* 0x9B0 */ /* double lbl_1_rodata_9B0 = -640; */
/* 0x9B8 */ /* float lbl_1_rodata_9B8 = 110.0f; */
/* 0x9C0 */ /* double lbl_1_rodata_9C0 = -400; */
/* 0x9C8 */ /* double lbl_1_rodata_9C8 = 200; */
/* 0x9D0 */ /* double lbl_1_rodata_9D0 = 255; */
/* 0x9D8 */ /* double lbl_1_rodata_9D8 = -600; */
/* 0x9E0 */ /* float lbl_1_rodata_9E0 = 256.0f; */
/* 0x9E4 */ /* float lbl_1_rodata_9E4 = 60.0f; */
/* 0x9E8 */ /* float lbl_1_rodata_9E8 = 350.0f; */
/* 0x9F0 */ /* double lbl_1_rodata_9F0 = 256; */
/* 0x9F8 */ /* double lbl_1_rodata_9F8 = 1.25; */
/* 0xA00 */ /* double lbl_1_rodata_A00 = 500; */
/* 0xA08 */ /* float lbl_1_rodata_A08 = 0.00390625f; */
/* 0xA0C */ /* u8 lbl_1_rodata_A0C[1] = { 0x40 }; */
/* 0xA0D */ /* TODO lbl_1_rodata_A0D .rodata size=0x3 (0 entries):  */
/* 0xA10 */ /* u8 lbl_1_rodata_A10[1] = { 0x00 }; */
/* 0xA14 */ /* float lbl_1_rodata_A14 = 55.0f; */
/* 0xA18 */ /* u8 lbl_1_rodata_A18[1] = { 0x40 }; */
/* 0xA19 */ /* TODO lbl_1_rodata_A19 .rodata size=0x3 (0 entries):  */
/* 0xA1C */ /* s32 lbl_1_rodata_A1C[3] = { 0x00000000, 0x425C0000, 0x00000000 }; */
/* 0xA28 */ /* u8 lbl_1_rodata_A28[1] = { 0x00 }; */
/* 0xA2C */ /* float lbl_1_rodata_A2C = 26.0f; */
/* 0xA30 */ /* float lbl_1_rodata_A30 = 22.0f; */
/* 0xA34 */ /* s32 lbl_1_rodata_A34[12] = { 0xBF800000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0xBF800000, 0xBF800000, 0x00000000 }; */
/* 0xA64 */ /* s32 lbl_1_rodata_A64[48] = { 0xBF800000, 0x00000000, 0x40000000, 0x3F800000, 0x00000000, 0x40000000, 0x3F800000, 0x00000000, 0x00000000, 0xBF800000, 0x00000000, 0x00000000, 0xBF800000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0xC0000000, 0xBF800000, 0x00000000, 0xC0000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xB24 */ /* s32 lbl_1_rodata_B24[8] = { 0x3F000000, 0x00000000, 0x3F800000, 0x3F000000, 0x00000000, 0x3F000000, 0x3F000000, 0x3F800000 }; */
/* 0xB44 */ /* s32 lbl_1_rodata_B44[3] = { 0x00000000, 0x425C0000, 0x00000000 }; */
/* 0xB50 */ /* s32 lbl_1_rodata_B50[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0xB5C */ /* s32 lbl_1_rodata_B5C[3] = { 0x00000000, 0x425C0000, 0x00000000 }; */
/* 0xB68 */ /* s32 lbl_1_rodata_B68[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xB74 */ /* float lbl_1_rodata_B74 = -3.0f; */
/* 0xB78 */ /* float lbl_1_rodata_B78 = 12.5f; */
/* 0xB7C */ /* float lbl_1_rodata_B7C = 28.0f; */
/* 0xB80 */ /* float lbl_1_rodata_B80 = 24.0f; */
/* 0xB84 */ /* s32 lbl_1_rodata_B84[12] = { 0xBF800000, 0x3F800000, 0x00000000, 0x3F800000, 0x3F800000, 0x00000000, 0x3F800000, 0xBF800000, 0x00000000, 0xBF800000, 0xBF800000, 0x00000000 }; */
/* 0xBB4 */ /* s32 lbl_1_rodata_BB4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xBC0 */ /* s32 lbl_1_rodata_BC0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xBCC */ /* float lbl_1_rodata_BCC = 200.0f; */
/* 0xBD0 */ /* double lbl_1_rodata_BD0 = 1; */
/* 0xBD8 */ /* double lbl_1_rodata_BD8 = 2.5; */
/* 0xBE0 */ /* double lbl_1_rodata_BE0 = 2; */
/* 0xBE8 */ /* float lbl_1_rodata_BE8 = 34.0f; */
/* 0xBEC */ /* s32 lbl_1_rodata_BEC[11] = { 0x00000660, 0x00000661, 0x00000662, 0x00000663, 0x00000664, 0x00000665, 0x00000663, 0x00000667, 0x00000668, 0x00000669, 0x0000066A }; */
/* 0xC18 */ /* s32 lbl_1_rodata_C18[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF }; */
/* 0xC28 */ /* float lbl_1_rodata_C28 = 5.0f; */
/* 0xC2C */ /* float lbl_1_rodata_C2C = 525.0f; */
/* 0xC30 */ /* float lbl_1_rodata_C30 = 210.0f; */
/* 0xC34 */ /* s32 lbl_1_rodata_C34[3] = { 0xC49C4000, 0xC3480000, 0xC4C1C000 }; */
/* 0xC40 */ /* s32 lbl_1_rodata_C40[3] = { 0x44ED8000, 0xC3480000, 0x447A0000 }; */
/* 0xC4C */ /* s32 lbl_1_rodata_C4C[2] = { 0xBF800000, 0x3F800000 }; */
/* 0xC54 */ /* s32 lbl_1_rodata_C54[2] = { 0x00000000, 0x00000000 }; */
/* 0xC5C */ /* s32 lbl_1_rodata_C5C[2] = { 0x003F000E, 0x003F0008 }; */
/* 0xC64 */ /* s32 lbl_1_rodata_C64[2] = { 0x003F0010, 0x003F000A }; */
/* 0xC6C */ /* s32 lbl_1_rodata_C6C[2] = { 0x003F0012, 0x003F000C }; */
/* 0xC74 */ /* s32 lbl_1_rodata_C74[2] = { 0x003F000F, 0x003F0009 }; */
/* 0xC7C */ /* s32 lbl_1_rodata_C7C[2] = { 0x003F0011, 0x003F000B }; */
/* 0xC84 */ /* s32 lbl_1_rodata_C84[6] = { 0xBF800000, 0x00000000, 0x00000000, 0x40400000, 0x00000000, 0x00000000 }; */
/* 0xC9C */ /* s32 lbl_1_rodata_C9C[4] = { 0x00000000, 0x00000002, 0x00000004, 0x00000006 }; */
/* 0xCAC */ /* s32 lbl_1_rodata_CAC[2] = { 0x003F0005, 0x003F0006 }; */
/* 0xCB4 */ /* float lbl_1_rodata_CB4 = 2.4f; */
/* 0xCB8 */ /* float lbl_1_rodata_CB8 = 0.9f; */
/* 0xCBC */ /* float lbl_1_rodata_CBC = -600.0f; */
/* 0xCC0 */ /* float lbl_1_rodata_CC0 = 1300.0f; */
/* 0xCC4 */ /* float lbl_1_rodata_CC4 = 150.0f; */
/* 0xCC8 */ /* double lbl_1_rodata_CC8 = 1000; */
/* 0xCD0 */ /* double lbl_1_rodata_CD0 = 1600; */
/* 0xCD8 */ /* float lbl_1_rodata_CD8 = 500.0f; */
/* 0xCDC */ /* float lbl_1_rodata_CDC = -370.0f; */
/* 0xCE0 */ /* float lbl_1_rodata_CE0 = -9.166667f; */
/* 0xCE4 */ /* float lbl_1_rodata_CE4 = -3.5f; */
/* 0xCE8 */ /* s32 lbl_1_rodata_CE8[4] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003 }; */
/* 0xCF8 */ /* s32 lbl_1_rodata_CF8[3] = { 0x00000000, 0x459C4000, 0x00000000 }; */
/* 0xD04 */ /* s32 lbl_1_rodata_D04[3] = { 0x00000000, 0xBF800000, 0xBF000000 }; */
/* 0xD10 */ /* u8 lbl_1_rodata_D10[1] = { 0xFF }; */
/* 0xD11 */ /* u8 lbl_1_rodata_D11[1] = { 0xFF, 0xFF, 0xFF }; */
/* 0xD14 */ /* float lbl_1_rodata_D14 = 25000.0f; */
/* 0xD18 */ /* float lbl_1_rodata_D18 = 1.2f; */
/* 0xD1C */ /* float lbl_1_rodata_D1C = 4000.0f; */
/* 0xD20 */ /* float lbl_1_rodata_D20 = 345.0f; */
/* 0xD28 */ /* double lbl_1_rodata_D28 = 10000; */
/* 0xD30 */ /* double lbl_1_rodata_D30 = 1.5707963267948966; */
/* 0xD38 */ /* float lbl_1_rodata_D38 = 346.0f; */
/* 0xD3C */ /* float lbl_1_rodata_D3C = 7000.0f; */
/* 0xD40 */ /* float lbl_1_rodata_D40 = 12000.0f; */

/* --- .data --- */
/* 0x0 */ s32 lbl_1_data_0[15] = { 0x00000000, 0x00000000, 0x00890000, 0x00300000, 0x00B40000, 0x00EA0000, 0x00E30000, 0x00140000, 0x00DD0000, 0x002A0000, 0x00C60000, 0x00AD0000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x3C */ s32 lbl_1_data_3C[12] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C001D, 0x008C0006, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x6C */ u8 lbl_1_data_6C[6] = { 0, 0, 0, 1, 0, 1 }; /* lbz */
/* 0x72 */ u8 lbl_1_data_72[6] = { 8, 8, 8, 16, 6, 8 }; /* lbz */
/* 0x78 */ s32 lbl_1_data_78[1] = { 0xFFFFFFFF };
/* 0x7C */ s32 lbl_1_data_7C[1] = { 0x00000708 };
/* 0x80 */ s32 lbl_1_data_80[1] = { 0xFFFFFFFF };
/* 0x84 */ s32 lbl_1_data_84[1] = { 0xFFFFFFFF };
/* 0x88 */ s32 lbl_1_data_88[1] = { 0xFFFFFFFF };
/* 0x8C */ s32 lbl_1_data_8C[1] = { 0x00000001 };
/* 0x90 */ float lbl_1_data_90[4][4] = { { -240.0f, 0.0f, -250.0f, 0.0f }, { -80.0f, 0.0f, -250.0f, 0.0f }, { 80.0f, 0.0f, -250.0f, 0.0f }, { 240.0f, 0.0f, -250.0f, 0.0f } }; /* stride 0x10 */
/* 0xD0 */ s32 lbl_1_data_D0[8] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0xF0 */ u8 lbl_1_data_F0[6][4] = { { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0x60 }, { 0x3F, 0x80, 0, 0 } }; /* animation frame counts: fn_1_FADC fills [0][0..3] (MotionMotionMaxTimeGet+1, 0x107F8) and [1..3][0] (MotionMaxTimeGet+1, 0x10868); [2..3][0] read at 0x11560 */
/* 0x108 */ char lbl_1_data_108[] = "ske_head";
/* 0x111 */ s8 lbl_1_data_111[4] = { 4, -1, 4, 4 }; /* extsb, indexed [i<4] (B694/BD58); dtk data_112 is its tail, unreferenced */
/* 0x115 */ s8 lbl_1_data_115[4] = { 0, 0, 0, 0 }; /* 1 byte + dtk gap_04_00000116 (3) */
/* 0x119 */ s8 lbl_1_data_119[3] = { 1, 0, 0 }; /* 1 byte + dtk gap_04_0000011A (2) */
/* 0x11C */ s32 lbl_1_data_11C[2] = { 0xFFFFFFFF, 0xFFFFFFFF };
/* 0x124 */ s32 lbl_1_data_124[1] = { 0x0000003C };
/* 0x128 */ s32 lbl_1_data_128[1] = { 0x00000078 };
/* 0x12C */ s32 lbl_1_data_12C[2] = { 0x00000000, 0x00000000 };
/* 0x134 */ char lbl_1_data_134[] = "*** main mode error(%d)!!\n";
/* 0x14F */ char lbl_1_data_14F[] = "******* M505 ObjectSetup *********\n";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2ED50 */ M505_SE lbl_1_bss_2ED50[11];
/* 0x2ED4C */ OMOBJ *lbl_1_bss_2ED4C; /* fn_1_119A0 object */
/* 0x2ED48 */ OMOBJ *lbl_1_bss_2ED48; /* omOutViewMulti object: stw 0x4c(r3) at 0x11FF4 */
/* 0x2ED38 */ OMOBJ *lbl_1_bss_2ED38[4]; /* player objects: lwz 0x5c(rX) at 0x12110 */
/* 0x2ED34 */ OMOBJ *lbl_1_bss_2ED34; /* fn_1_FADC object: lwz 0x40(rX) (mdlId) */
/* 0x2ED30 */ OMOBJ *lbl_1_bss_2ED30; /* fn_1_12078 object */
/* 0x2ED2C */ s32 lbl_1_bss_2ED2C; /* game mode: = 1000 at 0x119C0, cmpwi 0x3e9 -- an int, not a pointer */
/* 0x2ED28 */ OMOBJMAN *lbl_1_bss_2ED28; /* omInitObjMan result */
/* 0x2ED26 */ GAMEMESID lbl_1_bss_2ED26; /* lha; GameMesKill arg at 0x1214C */
/* 0x2ED24 */ s16 lbl_1_bss_2ED24; /* lha */
/* 0x2ED20 */ s32 lbl_1_bss_2ED20;
/* 0x2ED1C */ s32 lbl_1_bss_2ED1C; /* Hu3DGLightCreateV id: extsh+stw, lwz+extsh */
/* 0x9D1C */ M505_HAZARD lbl_1_bss_9D1C[64];
/* 0x977C */ M505_MARK lbl_1_bss_977C[72];
/* 0x1F7C */ M505_PARTICLE lbl_1_bss_1F7C[640];
/* 0x11FC */ M505_R24 lbl_1_bss_11FC[96];
/* 0x11EC */ s32 lbl_1_bss_11EC[4]; /* byte size of one bss_11AC texture buffer (DCFlushRange len) */
/* 0x11AC */ u8 *lbl_1_bss_11AC[4][4]; /* GXCopyTex dest buffers */
/* 0x119C */ u8 *lbl_1_bss_119C[4];
/* 0x1198 */ s32 lbl_1_bss_1198;
/* 0x1158 */ u8 *lbl_1_bss_1158[4][4];
/* 0x1154 */ float lbl_1_bss_1154; /* lfs/stfs only (0x5A68..0x5CDC) */
/* 0x1150 */ float lbl_1_bss_1150; /* lfs/stfs only */
/* 0x1120 */ float lbl_1_bss_1120[12]; /* lfs x1 stfs x2 (fn_1_4FB4 0x7678) */
/* 0x111D gap_05_0000111D_bss (0x3) -- dtk filler */
/* 0x111C */ GXColor lbl_1_bss_111C; /* 4 bytes: stb 0..3 at 0x12C..0x21C, lbz 0..3 at 0x48C (fn_1_0) */
/* 0x1119 gap_05_00001119_bss (0x3) -- dtk filler */
/* 0x1118 */ GXColor lbl_1_bss_1118; /* 4 bytes: stb 0..3 at 0xB54..0xC44, lbz 0..3 at 0xEB4 (fn_1_A90) */
/* 0x918 */ GXTexObj lbl_1_bss_918[64];
/* 0x18 */ GXTexObj lbl_1_bss_18[72];
/* 0x14 */ s32 lbl_1_bss_14;
/* 0x10 */ float lbl_1_bss_10; /* lfs/stfs only */
/* 0x8 */ s32 lbl_1_bss_8[2]; /* [0] = end flag (fn_1_12078 lwz+cmpwi); [1] never addressed */
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x0 */ float lbl_1_bss_0; /* lfs/stfs only */

/* --- functions (reference order) --- */
/* 676 insns -- HU3DMODELHOOK (fn_1_FADC 0xFCE4). modelP->pos.z is a mode
 * (0 / -1 / other) and modelP->rot is an RGB colour that fn_1_FADC sets with
 * Hu3DModelRotSet (0xFD4C); neither is a transform. */
void fn_1_0(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx m;
    Mtx proj; /* retail: a 48-byte Mtx handed to C_MTXOrtho (writes 64) */
    u8 *(*unused)[4] = lbl_1_bss_11AC;
    GXColor black = { 0, 0, 0, 255 };
    GXColor white = { 255, 255, 255, 255 };
    float z;

    z = 0.0f;
    lbl_1_bss_111C.r = (modelP->rot.x > 255.0f) ? 255.0f : ((modelP->rot.x < 0.0f) ? 0.0f : modelP->rot.x);
    lbl_1_bss_111C.g = (modelP->rot.y > 255.0f) ? 255.0f : ((modelP->rot.y < 0.0f) ? 0.0f : modelP->rot.y);
    lbl_1_bss_111C.b = (modelP->rot.z > 255.0f) ? 255.0f : ((modelP->rot.z < 0.0f) ? 0.0f : modelP->rot.z);
    lbl_1_bss_111C.a = 255;
    C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_A0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetTevColor(GX_TEVREG0, lbl_1_bss_111C);
    if (modelP->pos.z == 0.0f) {
        GXSetColorUpdate(GX_TRUE);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    } else if (modelP->pos.z == -1.0f) {
        GXSetColorUpdate(GX_TRUE);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetTevColor(GX_TEVREG0, black);
        z = 0.999969f;
    } else {
        GXSetColorUpdate(GX_FALSE);
        GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    }
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, z);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(0.0f, 0.0f);
    GXPosition3f32(1.0f, 0.0f, z);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(1.0f, 0.0f);
    GXPosition3f32(1.0f, 1.0f, z);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(1.0f, 1.0f);
    GXPosition3f32(0.0f, 1.0f, z);
    GXColor4u8(255, 255, 255, 255);
    GXTexCoord2f32(0.0f, 1.0f);
    if (modelP->pos.z == -1.0f) {
        GXSetZMode(GX_TRUE, GX_GREATER, GX_TRUE);
        GXSetTevColor(GX_TEVREG0, white);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(0.0f, 0.0f, z);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(1.0f, 0.0f, z);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(1.0f, 1.0f, z);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(0.0f, 1.0f, z);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 1.0f);
    }
    GXSetColorUpdate(GX_TRUE);
}

/* 469 insns -- unreferenced; same HU3DMODELHOOK shape as fn_1_0. Draws
 * modelP->rot.x full-screen quads additively in the colour lbl_1_bss_1118. */
void fn_1_A90(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx m;
    Mtx proj; /* retail: a 48-byte Mtx handed to C_MTXOrtho (writes 64) */
    u8 *(*unused)[4];
    int i;

    unused = lbl_1_bss_11AC;
    lbl_1_bss_1118.r = (modelP->rot.x > 255.0f) ? 255.0f : ((modelP->rot.x < 0.0f) ? 0.0f : modelP->rot.x);
    lbl_1_bss_1118.g = (modelP->rot.y > 255.0f) ? 255.0f : ((modelP->rot.y < 0.0f) ? 0.0f : modelP->rot.y);
    lbl_1_bss_1118.b = (modelP->rot.z > 255.0f) ? 255.0f : ((modelP->rot.z < 0.0f) ? 0.0f : modelP->rot.z);
    lbl_1_bss_1118.a = 255;
    C_MTXOrtho(proj, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ONE);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCCLR, GX_BL_ONE, GX_LO_NOOP);
    GXSetTevColor(GX_TEVREG0, lbl_1_bss_1118);
    GXSetColorUpdate(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    for (i = 0; i < modelP->rot.x; i++) {
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
}

/* 361 insns -- unreferenced debug camera (cf. m535 fn_1_A0): pad 1 moves
 * camera 1, then eye/target/up are computed and never used. */
void fn_1_1284(void)
{
    HuVecF pos;
    HuVecF center;
    HuVecF up;
    float rx;
    float ry;
    float rz;
    int i;

    i = 1;
    CenterM[i].x += 5.0 * (((HuPadBtn[0] & PAD_BUTTON_RIGHT) != 0) - ((HuPadBtn[0] & PAD_BUTTON_LEFT) != 0));
    CenterM[i].y += 20.0 * ((HuPadTrigL[0] - HuPadTrigR[0]) / 128.0);
    CZoomM[i] += 25.0 * (((HuPadBtn[0] & PAD_BUTTON_X) != 0) - ((HuPadBtn[0] & PAD_BUTTON_Y) != 0));
    CRotM[i].y += HuPadSubStkX[0] / 32.0;
    CRotM[i].x += HuPadSubStkY[0] / -32.0;
    fontcolor = 0;
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

/* 3555 insns. Player object update (installed by fn_1_11650): COM steering,
 * movement, player/hazard push-out, fall-out and landing, motion, dust. */
void fn_1_1828(OMOBJ *obj)
{
    M505_PWORK *work = obj->data;
    float vx;
    float vz;
    float dx;
    float dz;
    float dx2;
    float dz2;
    float mag = 0.0f;
    float stkX = 0.0f;
    float stkY = 0.0f;
    float x0 = obj->trans.x;
    float z0 = obj->trans.z;
    float ry0 = obj->rot.y;
    s16 motion = -1;
    float yOfs[10] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    s32 k2;
    s32 n2;
    s32 p;
    s32 q;
    s32 k3;
    M505_PWORK *work2;

    work->unk044 = x0;
    work->unk034 = work->unk03C = 0.0f;
    if (work->unk024 == 1) {
        if (lbl_1_bss_2ED2C == 0x3EB) {
            if (work->unk010 != -1) {
                stkX = HuPadStkX[work->unk010];
                stkY = HuPadStkY[work->unk010];
            } else {
                if (lbl_1_data_7C[0] <= 0x6CC - work->unk05C) {
                    s32 flag = 0;
                    float dist[12];
                    s32 durTbl[3][4] = { { 40, 30, 12, 6 }, { 6, 6, 5, 3 }, { 120, 70, 20, 5 } };

                    for (i = 0; i < 12; i++) {
                        dist[i] = 2000.0f;
                    }
                    for (i = 0; i < 64; i++) {
                        if (lbl_1_bss_9D1C[i].unk028 >= 0) {
                            s32 lane = (600.0f + lbl_1_bss_9D1C[i].unk008) / 100.0f;
                            for (j = lane + (lbl_1_bss_9D1C[i].unk02C == 0 ? 0 : -1); j <= lane + (lbl_1_bss_9D1C[i].unk02C == 0 ? 0 : 1); j++) {
                                s32 w = (lbl_1_bss_9D1C[i].unk02C == 0) ? 50 : (j == lane ? 150 : 50);
                                s32 look[4] = { 100, 300, 800, 2000 };
                                s32 lim = obj->trans.x + look[work->unk014];
                                lim = (lim > 700) ? 700 : lim;
                                if (j >= 0 && j < 12
                                    && lbl_1_bss_9D1C[i].unk000 < lim + (lbl_1_bss_9D1C[i].unk02C == 0 ? 50 : 150)
                                    && lbl_1_bss_9D1C[i].unk000 >= 20.0f + (obj->trans.x - w)
                                    && lbl_1_bss_9D1C[i].unk000 - w < dist[j]) {
                                    dist[j] = lbl_1_bss_9D1C[i].unk000 - w;
                                    flag = 1;
                                }
                            }
                        }
                    }
                    for (i = 0; i < 4; i++) {
                        s32 lane2;

                        lane2 = j = (600.0f + lbl_1_bss_2ED38[i]->trans.z) / 100.0f;
                        if (i != work->unk000 && lbl_1_bss_2ED38[i]->trans.x < 700.0f
                            && lbl_1_bss_2ED38[i]->trans.x >= obj->trans.x
                            && lbl_1_bss_2ED38[i]->trans.x < dist[j]) {
                            dist[j] = lbl_1_bss_2ED38[i]->trans.x;
                        }
                    }
                    j = (600.0f + obj->trans.z) / 100.0f;
                    if (work->unk064 > 0) {
                        if ((work->unk060 == 1) ? (obj->trans.z < -570.0f) : ((work->unk060 == -1) ? (obj->trans.z > 570.0f) : 0)) {
                            work->unk064 = 0;
                        }
                    }
                    if (work->unk064 > 0) {
                        stkX = 100.0f;
                        stkY = work->unk060 * 100;
                        work->unk064--;
                    } else if (flag == 0) {
                        stkX = 0.0f;
                        stkY = 0.0f;
                        work->unk060 = 0;
                        work->unk064 = 0;
                    } else if (work->unk014 >= 2 && obj->trans.x >= 600.0f && 2000.0f == dist[j]) {
                        stkX = 0.0f;
                        stkY = 0.0f;
                        work->unk060 = 0;
                        work->unk064 = 0;
                    } else if (work->unk058 == -1 && j - 1 >= 0 && dist[j - 1] > dist[j] && (j + 1 >= 12 || dist[j - 1] >= dist[j + 1])) {
                        stkX = 100.0f;
                        stkY = 100.0f;
                        work->unk060 = 1;
                        work->unk064 = durTbl[0][work->unk014];
                    } else if (j + 1 < 12 && dist[j + 1] > dist[j] && (j - 1 < 0 || dist[j + 1] >= dist[j - 1])) {
                        stkX = 100.0f;
                        stkY = -100.0f;
                        work->unk060 = -1;
                        work->unk064 = durTbl[0][work->unk014];
                    } else if (j - 1 >= 0 && dist[j - 1] > dist[j] && (j + 1 >= 12 || dist[j - 1] >= dist[j + 1])) {
                        stkX = 100.0f;
                        stkY = 100.0f;
                        work->unk060 = 1;
                        work->unk064 = durTbl[0][work->unk014];
                    } else if ((s32)(700.0f + obj->trans.z) % 100 < 30) {
                        stkX = 100.0f;
                        stkY = -100.0f;
                        work->unk060 = -1;
                        work->unk064 = durTbl[1][work->unk014];
                    } else if ((s32)(700.0f + obj->trans.z) % 100 > 70) {
                        stkX = 100.0f;
                        stkY = 100.0f;
                        work->unk060 = 1;
                        work->unk064 = durTbl[1][work->unk014];
                    } else {
                        stkX = 100.0f;
                        stkY = 0.0f;
                        work->unk060 = 0;
                        work->unk064 = durTbl[2][work->unk014];
                    }
                    stkX = 0.5 * work->unk050 + 0.5 * stkX;
                    work->unk050 = stkX;
                    stkY = 0.5 * work->unk054 + 0.5 * stkY;
                    work->unk054 = stkY;
                } else {
                    stkX = 0.0f;
                    work->unk050 = stkX;
                    stkY = 0.0f;
                    work->unk054 = stkY;
                }
                if (lbl_1_data_7C[0] % 60 == 0 && work->unk014 >= 2) {
                    work->unk058 = (obj->trans.z < -400.0f) ? 1
                        : ((obj->trans.z > 400.0f) ? -1
                        : ((obj->trans.z < 2.0f * obj->trans.z + 400.0f * (2.0f * (rand8() / 255.0f) - 1.0f)) ? -1 : 1));
                }
            }
        }
    } else if (work->unk024 == 2) {
        if (work->unk02C < 0.0f) {
            stkX = work->unk02C / 0.25f;
        } else {
            s32 t = (work->unk028 < 20) ? 0 : ((work->unk028 < 60) ? (work->unk028 - 20) * 256 / 40 : 256);
            stkX = t * 24 / 256;
            stkY = t * 6 / 256;
        }
    }
    vx = 0.25 * stkX;
    vz = 0.25 * -stkY;
    {
        Vec dir = { 0.0f, 0.0f, 0.0f };
        Mtx rot;

        dir.x = vx;
        dir.z = vz;
        PSMTXRotRad(rot, 'y', 0.017453292f * CRotM[1].y);
        PSMTXMultVec(rot, &dir, &dir);
        vx = dir.x;
        vz = dir.z;
    }
    mag = sqrtf(vx * vx + vz * vz);
    if (mag >= 0.5f) {
        if (mag < 10.0f) {
            work->unk034 = vx;
            work->unk03C += vz;
        } else {
            vx /= mag;
            vz /= mag;
            mag = 10.0f;
            work->unk034 = vx * mag;
            work->unk03C = vz * mag;
        }
        work->unk030 = mag;
        if (work->unk024 == 1) {
            obj->rot.y = 180.0 * (atan2(work->unk034, work->unk03C) / M_PI);
        }
        if (work->unk024 == 1) {
            if (work->unk030 >= 8.0f) {
                motion = 2;
            } else {
                motion = 1;
            }
        }
    } else if (work->unk024 == 1) {
        motion = 0;
    }
    obj->trans.x += work->unk034;
    obj->trans.z += work->unk03C;
    for (k = 0; k < 4; k++) {
        float d;

        dx = lbl_1_bss_2ED38[k]->trans.x - obj->trans.x;
        dz = lbl_1_bss_2ED38[k]->trans.z - obj->trans.z;
        if (k != work->unk000) {
            if (0.0f == dx && 0.0f == dz) {
                dz = -1.0f;
            }
            d = sqrtf(dx * dx + dz * dz);
            if (d < 100.0f) {
                dx *= 100.0f / d;
                dz *= 100.0f / d;
                obj->trans.x = lbl_1_bss_2ED38[k]->trans.x - dx;
                obj->trans.z = lbl_1_bss_2ED38[k]->trans.z - dz;
            }
        }
    }
    if (work->unk024 == 1 && obj->trans.x > 700.0f) {
        obj->trans.x = 700.0f;
    }
    if (lbl_1_bss_2ED2C < 0x3EC || (lbl_1_bss_2ED2C == 0x3EC && 0.0f == lbl_1_bss_0)) {
        for (n = 0; n < 64; n++) {
            if (lbl_1_bss_9D1C[n].unk028 >= 0) {
                s32 m;
                float r = 50.0f + ((lbl_1_bss_9D1C[n].unk02C == 0) ? 40 : 150);

                if (fabs(lbl_1_bss_9D1C[n].unk000 - obj->trans.x) <= r && fabs(lbl_1_bss_9D1C[n].unk008 - obj->trans.z) <= r) {
                    if (lbl_1_bss_9D1C[n].unk02C == 0) {
                        for (m = 0; m < 4; m++) {
                            float radTbl[2] = { 38.0f, 0.0f };
                            float dd;
                            float rr;
                            float ddx;
                            float ddz;

                            ddx = lbl_1_bss_9D1C[n].unk000 - obj->trans.x;
                            ddz = lbl_1_bss_9D1C[n].unk008 - obj->trans.z;
                            ddz *= 1.125f;
                            if (0.0f == ddx && 0.0f == ddz) {
                                ddx = -1.0f;
                            }
                            dd = ddx * ddx + ddz * ddz;
                            rr = 50.0f + radTbl[lbl_1_bss_9D1C[n].unk02C];
                            if (!(dd < rr * rr)) {
                                break;
                            }
                            dd = sqrtf(dd);
                            ddx *= (50.0f + radTbl[lbl_1_bss_9D1C[n].unk02C]) / dd;
                            ddz *= (50.0f + radTbl[lbl_1_bss_9D1C[n].unk02C]) / dd;
                            obj->trans.x = lbl_1_bss_9D1C[n].unk000 - ddx;
                            if (obj->trans.x > lbl_1_bss_9D1C[n].unk000) {
                                obj->trans.z = lbl_1_bss_9D1C[n].unk008 - ddz / 1.125f;
                            }
                        }
                    } else {
                        float ed;
                        float er;
                        float ex;
                        float ez;

                        ex = lbl_1_bss_9D1C[n].unk000 - obj->trans.x;
                        ez = lbl_1_bss_9D1C[n].unk008 - obj->trans.z;
                        if (0.0f == ex && 0.0f == ez) {
                            ex = -1.0f;
                        }
                        ed = ex * ex + ez * ez;
                        er = 198.0f;
                        if (ed < er * er) {
                            ed = sqrtf(ed);
                            ex *= 198.0f / ed;
                            ez *= 198.0f / ed;
                            obj->trans.x = lbl_1_bss_9D1C[n].unk000 - ex;
                            obj->trans.z = lbl_1_bss_9D1C[n].unk008 - ez;
                        }
                    }
                }
            }
        }
    }
    for (k2 = 0; k2 < 4; k2++) {
        float d2;

        dx2 = obj->trans.x - lbl_1_bss_2ED38[k2]->trans.x;
        dz2 = obj->trans.z - lbl_1_bss_2ED38[k2]->trans.z;
        if (k2 != work->unk000) {
            if (0.0f == dx2 && 0.0f == dz2) {
                dz2 = -1.0f;
            }
            d2 = sqrtf(dx2 * dx2 + dz2 * dz2);
            if (d2 < 100.0f) {
                dx2 *= 100.0f / d2;
                dz2 *= 100.0f / d2;
                lbl_1_bss_2ED38[k2]->trans.x = obj->trans.x - dx2;
                lbl_1_bss_2ED38[k2]->trans.z = obj->trans.z - dz2;
            }
        }
    }
    switch (work->unk024) {
    case 1:
        if (!(obj->trans.x <= -710.0f || obj->trans.z <= -610.0f || obj->trans.z >= 610.0f)) {
            break;
        }
        work->unk024 = 2;
        Hu3DModelShadowReset(obj->mdlId[0]);
        work->unk028 = 0;
        work->unk02C = (obj->trans.z <= -610.0f || obj->trans.z >= 610.0f) ? 0.0f
            : ((obj->trans.x - x0 < -0.1f) ? obj->trans.x - x0 : -0.1f);
    case 2: {
        float cx;
        float cz;
        float ex2;
        float ez2;
        float ed2;
        float er2;

        work->unk028++;
        if (obj->trans.y > -194.0f + yOfs[work->unk008]) {
            motion = 3;
            work->unk038 += -1.6333333f;
            obj->trans.y += work->unk038;
            if (obj->trans.y <= -194.0f + yOfs[work->unk008]) {
                for (n2 = 0; n2 < 72; n2++) {
                    if (lbl_1_bss_977C[n2].unk010 == -1) {
                        break;
                    }
                }
                if (n2 < 72) {
                    lbl_1_bss_977C[n2].unk010 = 11;
                    lbl_1_bss_977C[n2].unk000 = obj->trans.x;
                    lbl_1_bss_977C[n2].unk008 = obj->trans.z;
                    lbl_1_bss_977C[n2].unk00C = 2;
                }
                -0.5 * work->unk038;
                if (work->unk010 != -1) {
                    omVibrate(work->unk004, 12, 12, 0);
                }
                work->unk02C *= 0.375f;
                work->unk02C = (work->unk02C < 0.0f && work->unk02C > -1.25f) ? -1.25f : work->unk02C;
                if (lbl_1_bss_2ED50[10].unk000 < 3) {
                    lbl_1_bss_2ED50[10].unk004[lbl_1_bss_2ED50[10].unk000] = obj->trans.x;
                    lbl_1_bss_2ED50[10].unk010[lbl_1_bss_2ED50[10].unk000] = 1;
                    lbl_1_bss_2ED50[10].unk000++;
                }
                HuAudFXPanning(CharFXPlay(work->unk00C, 0x1F9), M505_PanF(64.0f + 32.0f * ((obj->trans.x - CenterM[1].x) / 700.0f)));
            }
        } else {
            motion = 4;
            work->unk038 += -0.33333334f * ((obj->trans.y < -215.0f) ? -1 : 1);
            work->unk038 *= 0.95;
            if (obj->trans.y > -194.0f + yOfs[work->unk008]) {
                obj->trans.y = -194.0f + yOfs[work->unk008];
            }
            if (obj->trans.x < -1110.0f) {
                if (work->unk000 != 0) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
                }
                obj->trans.x = 2000.0f;
                obj->trans.z = -1000 - work->unk000 * 200;
                work->unk02C = 0.0f;
            }
        }
        if (obj->trans.x > -710.0f && obj->trans.z > -610.0f && obj->trans.z < 610.0f) {
            if (-obj->trans.x - 100.0f > fabs(obj->trans.z)) {
                obj->trans.x = -710.0f;
            } else {
                obj->trans.z = (obj->trans.z < 0.0f) ? -610 : 610;
            }
        }
        cx = (obj->trans.x <= -709.0f) ? -709.0f : obj->trans.x;
        cz = (obj->trans.z <= -609.0f) ? -609.0f : ((obj->trans.z >= 609.0f) ? 609.0f : obj->trans.z);
        ex2 = obj->trans.x - cx;
        ez2 = obj->trans.z - cz;
        ed2 = ex2 * ex2 + ez2 * ez2;
        er2 = 1.0f + ((work->unk028 >= 12) ? 100.0f : 100.0f * work->unk028 / 12.0f);
        if (ed2 <= er2 * er2) {
            ed2 = sqrtf(ed2);
            obj->trans.x = cx + er2 * (ex2 / ed2);
            obj->trans.z = cz + er2 * (ez2 / ed2);
        }
    } break;
    }
    if (lbl_1_data_78[0] != -1 && work->unk024 == 3) {
        motion = 0;
        if (lbl_1_bss_2ED2C == 0x3ED) {
            motion = 5;
            obj->rot.y = 0.8f * obj->rot.y;
        }
    }
    if (work->unk020 >= 0) {
        motion = work->unk020;
    }
    if (motion >= 0 && motion != work->unk01C) {
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[motion], 0.0f, lbl_1_data_72[motion],
            lbl_1_data_6C[motion] ? HU3D_MOTATTR_NONE : HU3D_MOTATTR_LOOP);
        work->unk01C = motion;
    }
    if (work->unk008 != 8) {
        s32 ci = (work->unk008 < 5) ? work->unk008
            : ((work->unk008 == 5) ? 2 : ((work->unk008 < 9) ? work->unk008 - 1 : work->unk008 - 2));
        float fxTbl[8][5][9] = {
            {
              { 0.0f, 10.0f, 0.125f, 0.3125f, 0.6875f, 1.0f, 5.0f, 26.0f, 0.0f },
              { 1.0f, 33.0f, -0.109375f, 0.21875f, 0.6875f, 1.125f, 0.0f, 0.0f, 0.0f },
              { 1.0f, 9.0f, 0.125f, 0.109375f, 0.6875f, 1.125f, 0.0f, 0.0f, 0.0f },
              { 2.0f, 29.0f, 0.0625f, 0.09375f, 0.6875f, 1.125f, 0.0f, 3.0f, -0.234375f },
              { 2.0f, 13.0f, 0.125f, 0.234375f, 0.6875f, 1.125f, 0.0f, 8.0f, -0.171875f } },
            {
              { 0.0f, 0.0f, 0.203125f, 0.25f, 0.6875f, 1.125f, 4.0f, 17.0f, -0.09375f },
              { 1.0f, 8.0f, 0.0f, 0.328125f, 0.6875f, 1.125f, 4.0f, 13.0f, -0.1875f },
              { 1.0f, 30.0f, 0.0f, 0.328125f, 0.6875f, 1.125f, 4.0f, 13.0f, -0.1875f },
              { 2.0f, 3.0f, 0.0f, 0.90625f, 0.6875f, 1.125f, 4.0f, 13.0f, -0.328125f },
              { 2.0f, 20.0f, 0.0f, 1.046875f, 0.6875f, 1.125f, 4.0f, 9.0f, -0.359375f } },
            {
              { 0.0f, 10.0f, 0.0f, 0.25f, 0.4375f, 0.9375f, 0.0f, 0.0f, 0.0f },
              { 1.0f, 32.0f, 0.0f, 0.25f, 0.4375f, 0.9375f, 0.0f, 0.0f, 0.0f },
              { 1.0f, 8.0f, 0.0f, 0.25f, 0.4375f, 0.9375f, 0.0f, 0.0f, 0.0f },
              { 2.0f, 18.0f, 0.0f, 0.359375f, 0.4375f, 0.9375f, 0.0f, 0.0f, 0.0f },
              { 2.0f, 3.0f, 0.0f, 0.359375f, 0.4375f, 0.9375f, 0.0f, 0.0f, 0.0f } },
            {
              { 0.0f, 10.0f, 0.0f, 0.390625f, 0.796875f, 1.359375f, 0.0f, 0.0f, 0.09375f },
              { 1.0f, 31.0f, 0.0f, 0.390625f, 0.796875f, 1.359375f, 0.0f, 0.0f, 0.09375f },
              { 1.0f, 8.0f, 0.0f, 0.390625f, 0.796875f, 1.359375f, 0.0f, 0.0f, 0.09375f },
              { 2.0f, 29.0f, 0.0f, 0.015625f, 0.796875f, 1.359375f, 0.0f, 0.0f, 0.09375f },
              { 2.0f, 12.0f, 0.0f, 0.015625f, 0.796875f, 1.359375f, 0.0f, 0.0f, 0.09375f } },
            {
              { 0.0f, 10.0f, 0.0f, 1.046875f, 0.84375f, 1.34375f, 0.0f, 23.0f, 0.453125f },
              { 1.0f, 36.0f, 0.0f, 1.046875f, 0.8125f, 1.34375f, 0.0f, 26.0f, 0.203125f },
              { 1.0f, 9.0f, 0.0f, 1.046875f, 0.8125f, 1.34375f, 0.0f, 26.0f, 0.203125f },
              { 2.0f, 4.0f, 0.0f, 1.25f, 0.8125f, 1.34375f, 0.0f, 26.0f, 0.140625f },
              { 2.0f, 22.0f, 0.0f, 1.25f, 0.8125f, 1.34375f, 0.0f, 26.0f, 0.140625f } },
            {
              { 0.0f, 10.0f, -0.015625f, 1.40625f, 0.46875f, 1.34375f, 0.0f, 33.0f, 0.984375f },
              { 1.0f, 21.0f, 0.0f, 2.796875f, 0.46875f, 1.25f, 0.0f, 22.0f, -0.46875f },
              { 1.0f, 1.0f, 0.0f, 2.796875f, 0.46875f, 1.25f, 0.0f, 22.0f, -0.46875f },
              { 2.0f, 29.0f, 0.0f, 2.3125f, 0.46875f, 1.25f, 0.0f, 32.0f, -0.84375f },
              { 2.0f, 13.0f, 0.0f, 2.9375f, 0.46875f, 1.25f, 0.0f, 29.0f, -0.9375f } },
            {
              { 0.0f, 0.0f, 0.0f, 0.359375f, 0.625f, 0.828125f, 4.0f, 19.0f, 0.109375f },
              { 1.0f, 19.0f, 0.0f, 0.203125f, 0.625f, 0.828125f, 0.0f, 2.0f, -0.171875f },
              { 1.0f, 41.0f, 0.0f, 0.203125f, 0.625f, 0.828125f, 0.0f, 2.0f, -0.171875f },
              { 2.0f, 15.0f, 0.0f, 0.0f, 0.625f, 0.828125f, 0.0f, 0.0f, -0.171875f },
              { 2.0f, 1.0f, 0.0f, 0.0f, 0.625f, 0.828125f, 0.0f, 0.0f, -0.171875f } },
            {
              { 0.0f, 0.0f, 0.0f, -0.734375f, 1.3125f, 1.390625f, 0.0f, 15.0f, 0.21875f },
              { 1.0f, 1.0f, 0.0f, -1.078125f, 1.3125f, 1.390625f, 0.0f, 0.0f, -0.328125f },
              { 1.0f, 22.0f, 0.0f, -1.078125f, 1.3125f, 1.390625f, 0.0f, 0.0f, -0.328125f },
              { 2.0f, 1.0f, 0.0f, -1.171875f, 1.3125f, 1.390625f, 0.0f, 0.0f, -0.28125f },
              { 2.0f, 17.0f, 0.0f, -1.171875f, 1.3125f, 1.390625f, 0.0f, 0.0f, -0.28125f } },
        };
        s32 mot = (Hu3DMotionShiftIDGet(obj->mdlId[0]) == -1) ? Hu3DMotionIDGet(obj->mdlId[0]) : Hu3DMotionShiftIDGet(obj->mdlId[0]);
        float tm = (Hu3DMotionShiftIDGet(obj->mdlId[0]) == -1) ? Hu3DMotionTimeGet(obj->mdlId[0]) : Hu3DMotionShiftTimeGet(obj->mdlId[0]);

        if (lbl_1_bss_2ED2C >= 0x3EA) {
            if (work->unk048 == obj->mtnId[0] && mot != obj->mtnId[0]) {
                for (p = 0; p < 2; p++) {
                    for (q = 0; q < 640; q++) {
                        if (lbl_1_bss_1F7C[q].unk02C == -1) {
                            break;
                        }
                    }
                    if (q < 640) {
                        lbl_1_bss_1F7C[q].unk02C = 11;
                        lbl_1_bss_1F7C[q].unk000 = obj->trans.x + ((lbl_1_bss_9D1C[p].unk02C == 1) ? -40 : 0);
                        lbl_1_bss_1F7C[q].unk008 = obj->trans.z + rand8() * 16 / 255 - 8.0f;
                        lbl_1_bss_1F7C[q].unk018 = fxTbl[ci][0][2];
                        lbl_1_bss_1F7C[q].unk01C = fxTbl[ci][0][3];
                        lbl_1_bss_1F7C[q].unk020 = fxTbl[ci][0][4];
                        lbl_1_bss_1F7C[q].unk024 = fxTbl[ci][0][5];
                        lbl_1_bss_1F7C[q].unk00C = -obj->rot.y - 90.0f + fxTbl[ci][0][6];
                        lbl_1_bss_1F7C[q].unk010 = fxTbl[ci][0][7];
                        lbl_1_bss_1F7C[q].unk014 = fxTbl[ci][0][8] / 64.0f;
                        lbl_1_bss_1F7C[q].unk029 = work->unk008 + 2;
                        lbl_1_bss_1F7C[q].unk028 = p;
                    }
                }
            }
            for (p = 1; p < 5; p++) {
                if (mot == work->unk048) {
                    if (mot == ((p < 3) ? obj->mtnId[1] : obj->mtnId[2])) {
                        if (work->unk04C < fxTbl[ci][p][1] && tm >= fxTbl[ci][p][1]) {
                            for (q = 0; q < 640; q++) {
                                if (lbl_1_bss_1F7C[q].unk02C == -1) {
                                    break;
                                }
                            }
                            if (q < 640) {
                                lbl_1_bss_1F7C[q].unk02C = 11;
                                lbl_1_bss_1F7C[q].unk000 = obj->trans.x + ((lbl_1_bss_9D1C[p].unk02C == 1) ? -40 : 0);
                                lbl_1_bss_1F7C[q].unk008 = obj->trans.z + rand8() * 16 / 255 - 8.0f;
                                lbl_1_bss_1F7C[q].unk018 = fxTbl[ci][p][2];
                                lbl_1_bss_1F7C[q].unk01C = fxTbl[ci][p][3];
                                lbl_1_bss_1F7C[q].unk020 = fxTbl[ci][p][4];
                                lbl_1_bss_1F7C[q].unk024 = fxTbl[ci][p][5];
                                lbl_1_bss_1F7C[q].unk00C = -obj->rot.y - 90.0f + fxTbl[ci][p][6];
                                lbl_1_bss_1F7C[q].unk010 = fxTbl[ci][p][7];
                                lbl_1_bss_1F7C[q].unk014 = fxTbl[ci][p][8] / 64.0f;
                                lbl_1_bss_1F7C[q].unk029 = work->unk008 + 2;
                                lbl_1_bss_1F7C[q].unk028 = 1 - (p - 1) % 2;
                            }
                        }
                    }
                }
            }
        }
        work->unk048 = mot;
        work->unk04C = tm;
    }
    {
        s32 flipTbl[10] = { 1, 1, 0, 0, 0, 0, 0, 1, 1, 1 };

        if (lbl_1_bss_2ED2C == 0x3E9) {
            float ang;
            float px;
            float pz;
            float side;

            side = (obj->rot.y > 0.0f) ? -180 : 180;
            px = lbl_1_bss_9D1C[0].unk000;
            pz = lbl_1_bss_9D1C[0].unk008;
            ang = 180.0 * (atan2(obj->trans.x - px, obj->trans.z - pz) / M_PI);
            ang += 360.0f;
            ang -= (ang >= 360.0f) ? 360 : 0;
            ang = 180.0 + 0.5 * (ang - 180.0f);
            work->unk040 = ang;
            Hu3DMotionForceSet(obj->mdlId[0], lbl_1_data_108, flipTbl[work->unk008] ? 0x100 : 0x80,
                flipTbl[work->unk008] ? 180.0f + -work->unk040 : 180.0f + work->unk040);
        } else if (lbl_1_bss_2ED2C == 0x3EA) {
            work->unk040 = 180.0 + 0.96875 * (work->unk040 - 180.0f);
            work->unk040 = (work->unk040 > 179.0f && work->unk040 < 181.0f) ? 180.0f : work->unk040;
            if (180.0f != work->unk040) {
                Hu3DMotionForceSet(obj->mdlId[0], lbl_1_data_108, flipTbl[work->unk008] ? 0x100 : 0x80,
                    flipTbl[work->unk008] ? 180.0f + -work->unk040 : 180.0f + work->unk040);
            } else {
                Hu3DMotionNoMotReset(obj->mdlId[0], lbl_1_data_108, flipTbl[work->unk008] ? 0x100 : 0x80);
            }
        }
    }
    if (work->unk02C < 0.0f && obj->trans.y <= -194.0f + yOfs[work->unk008] && 0.75f * (obj->trans.x - x0) < work->unk02C) {
        work->unk02C = 0.75f * (obj->trans.x - x0);
    } else if (work->unk02C < 0.0f && obj->trans.x - x0 > work->unk02C) {
        obj->trans.x = x0 + work->unk02C;
    }
    if (work->unk000 == 3) {
        for (k3 = 0; k3 < 4; k3++) {
            work2 = lbl_1_bss_2ED38[k3]->data;
            if (work2->unk024 == 1) {
                if (!(lbl_1_bss_2ED38[k3]->trans.x <= -710.0f || lbl_1_bss_2ED38[k3]->trans.z <= -610.0f || lbl_1_bss_2ED38[k3]->trans.z >= 610.0f)) {
                    break;
                }
                work2->unk024 = 2;
                Hu3DModelShadowReset(lbl_1_bss_2ED38[k3]->mdlId[0]);
                work2->unk028 = 0;
                work2->unk02C = (lbl_1_bss_2ED38[k3]->trans.z <= -610.0f || lbl_1_bss_2ED38[k3]->trans.z >= 610.0f) ? 0.0f
                    : ((lbl_1_bss_2ED38[k3]->trans.x - work2->unk044 < -0.1f) ? lbl_1_bss_2ED38[k3]->trans.x - work2->unk044 : -0.1f);
            }
        }
    }
    CharModelVoicePanSet(work->unk00C, M505_PanF(64.0f + 32.0f * ((obj->trans.x - CenterM[1].x) / 700.0f)));
}

/* 6584 insns. Object hook (omAddObjEx in fn_1_FADC 0x115F0): stage/background update --
 * EFB texture fix-ups, the intro character sequence (data_111/115/119),
 * camera moves, falling objects (bss_11FC), landing marks and dust ageing,
 * and the hazard (bss_9D1C) simulation: movement, mutual push-apart,
 * splash/dust spawning, spawn scheduling and model/motion updates.
 * It is the reference's one caller of an out-of-line fabs (`bl fabs` at
 * 0x5B88, 0x5BE0, 0x897C): CodeWarrior does not inline in a function this
 * large (see the header comment). Nothing is inlined in here. */
void fn_1_4FB4(OMOBJ *obj)
{
    M505_PWORK *work[4];
    s32 motOfs[4] = { 0, 2, 4, 6 };
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    float t;

    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_2ED38[i]->data;
    }
    if (lbl_1_bss_2ED2C >= 1003) {
        Hu3DModelAttrSet(obj->mdlId[1], 1);
        Hu3DModelAttrSet(obj->mdlId[2], 1);
    }
    if (lbl_1_bss_2ED2C >= 1004 && lbl_1_bss_0 > 0.0f) {
        float s;

        t = 0.0625f;
        s = 1.0f - t;
        CRotM[1].x = -40.0f * t + CRotM[1].x * s;
    }
    if (lbl_1_bss_2ED2C == 1004 && 0.0f == lbl_1_bss_0) {
        for (i = 0; i < 64; i++) {
            if (lbl_1_bss_9D1C[i].unk028 >= 0 && lbl_1_bss_9D1C[i].unk02E != 1) {
                lbl_1_bss_9D1C[i].unk02E = 3;
                lbl_1_bss_9D1C[i].unk030 = 0;
                lbl_1_bss_9D1C[i].unk032 = 0x100;
                lbl_1_bss_9D1C[i].unk00C = lbl_1_bss_9D1C[i].unk010 = lbl_1_bss_9D1C[i].unk014 = 0.0f;
                lbl_1_bss_9D1C[i].unk037 = 0;
                if (lbl_1_bss_9D1C[i].unk036 >= 0) {
                    s32 mdl = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;

                    Hu3DMotionSet(obj->mdlId[mdl], obj->mtnId[lbl_1_bss_9D1C[i].unk02C + motOfs[lbl_1_bss_9D1C[i].unk02E]]);
                    Hu3DMotionTimeSet(obj->mdlId[mdl], 0.0f);
                    Hu3DMotionSpeedSet(obj->mdlId[mdl], 0.29411766f);
                    Hu3DModelAttrReset(obj->mdlId[mdl], 0x40000001);
                }
            }
        }
    }
    lbl_1_bss_10 += 0.0009765625f;
    Hu3DWaterTexPosSet(2.0f * -lbl_1_bss_10, lbl_1_bss_10, -lbl_1_bss_10);
    for (i = 0; i < 4; i++) {
        if (lbl_1_data_119[0] == 0 && i == 0 && lbl_1_data_111[i] != -1 && lbl_1_data_115[i] != -1) {
            for (x = 0; x < 56; x++) {
                for (y = 0; y < 60; y++) {
                    if (((u16 *)(lbl_1_bss_11AC[i][lbl_1_data_111[i]] + lbl_1_data_115[i] * lbl_1_bss_11EC[i]))[x + y * 56] == 0x8000) {
                        ((u16 *)(lbl_1_bss_11AC[i][lbl_1_data_111[i]] + lbl_1_data_115[i] * lbl_1_bss_11EC[i]))[x + y * 56] = 2;
                    }
                }
            }
        }
        if (lbl_1_data_119[0] == 0 && i == 1 && lbl_1_data_111[i] == 0) {
            for (x = 0; x < 80; x++) {
                for (y = 0; y < 68; y++) {
                    s32 r;
                    s32 g;
                    s32 b;
                    s32 a = 255;
                    u16 c;
                    u16 d;
                    s32 r2;
                    s32 g2;
                    s32 b2;

                    d = ((u16 *)(lbl_1_bss_11AC[i][lbl_1_data_111[i]] + lbl_1_data_115[i] * lbl_1_bss_11EC[i]))[x + y * 80];
                    c = *(u16 *)&lbl_1_bss_119C[i][(x + y * 80) * 2];
                    r = (c & 0x7C00) >> 7;
                    g = (c & 0x3E0) >> 2;
                    b = (c & 0x1F) << 3;
                    r2 = (d & 0x7C00) >> 7;
                    g2 = (d & 0x3E0) >> 2;
                    b2 = (d & 0x1F) << 3;
                    a = 255 - (r2 - r);
                    a = (a >= 255) ? 255 : ((a <= 0) ? 0 : a);
                    c = 0xFF00 / a;
                    r = r * c / 256;
                    r = (r >= 255) ? 255 : ((r <= 0) ? 0 : r);
                    g = g * c / 256;
                    g = (g >= 255) ? 255 : ((g <= 0) ? 0 : g);
                    b = b * c / 256;
                    b = (b >= 255) ? 255 : ((b <= 0) ? 0 : b);
                    ((u16 *)(lbl_1_bss_11AC[i][lbl_1_data_111[i]] + lbl_1_data_115[i] * lbl_1_bss_11EC[i]))[x + y * 80]
                        = (a >= 0xE0) ? (((b & 0xF8) >> 3 | ((r & 0xF8) << 7 | (g & 0xF8) << 2)) | 0x8000)
                                      : ((a & 0xE0) << 7 | ((b & 0xF0) >> 4 | ((r & 0xF0) << 4 | (g & 0xF0))));
                }
            }
            DCFlushRange(&lbl_1_bss_11AC[i][lbl_1_data_111[i]][lbl_1_data_115[i] * lbl_1_bss_11EC[i]], lbl_1_bss_11EC[i]);
        }
    }
    if (lbl_1_data_119[0] == 1 && 0.0f == lbl_1_bss_1154 && 0.0f == lbl_1_bss_1150) {
        HuVecF pts[2] = { { 0.0f, 0.0f, 0.0f }, { -256.0f, 256.0f, 0.0f } };
        HuVecF out[2];
        Mtx lookAt;
        Mtx lookAtT;
        HU3DCAMERA *cam;

        cam = &Hu3DCamera[1];
        for (i = 0; i < 2; i++) {
            pts[i].x += cam->target.x;
            pts[i].y += cam->target.y;
            pts[i].z += cam->target.z;
            C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
            PSMTXTranspose(lookAt, lookAtT);
            PSMTXMultVec(lookAtT, &pts[i], &out[i]);
            (void)Hu3D3Dto2D(&out[i], 1, &pts[i]);
            pts[i].x = 320.0f + 640.0f * ((pts[i].x - 288.0f) / 576.0f);
            pts[i].y = 240.0f + 480.0f * ((pts[i].y - 240.0f) / 480.0f);
        }
        lbl_1_bss_1154 = fabs(pts[0].x - pts[1].x) / 256.0;
        lbl_1_bss_1154 = 1.0f / lbl_1_bss_1154;
        lbl_1_bss_1150 = fabs(pts[0].y - pts[1].y) / 256.0;
        lbl_1_bss_1150 = 1.0f / lbl_1_bss_1150;
    }
    if (WipeCheckEnd() == 0) {
        s32 cnt = 0;

        for (i = 0; i < 4; i++) {
            if (lbl_1_data_111[i] < ((i == 0) ? ((lbl_1_data_119[0] >= 2) ? 4 : 4) : 1)) {
                cnt++;
                lbl_1_data_115[i]++;
                if (lbl_1_data_119[0] == 0 && i == 0 && lbl_1_data_111[3] < 1 && lbl_1_data_111[0] == 2) {
                    lbl_1_data_115[i] = 0;
                }
                if (lbl_1_data_111[i] == -1 || lbl_1_data_F0[i][lbl_1_data_111[i]] <= lbl_1_data_115[i]) {
                    if (lbl_1_data_119[0] == 4 && i == 0) {
                        lbl_1_data_111[i] = (lbl_1_data_111[i] == 5) ? 3 : ((lbl_1_data_111[i] == 3) ? 2 : ((lbl_1_data_111[i] == 2) ? 4 : 0));
                    } else if (lbl_1_data_119[0] == 2 && i == 0) {
                        lbl_1_data_111[i] = (lbl_1_data_111[i] == 1) ? 3 : ((lbl_1_data_111[i] == 3) ? 2 : ((lbl_1_data_111[i] == 2) ? 4 : lbl_1_data_111[i] + 1));
                    } else {
                        lbl_1_data_111[i]++;
                    }
                    lbl_1_data_115[i] = 0;
                    if (lbl_1_data_111[i] >= ((i == 0) ? ((lbl_1_data_119[0] >= 2) ? 4 : 4) : 1)) {
                        Hu3DModelAttrSet(obj->mdlId[i + 13], 1);
                        continue;
                    }
                }
                if (lbl_1_data_111[i] < ((i == 0) ? ((lbl_1_data_119[0] >= 2) ? 4 : 4) : 1)) {
                    if (i == 0) {
                        if (i != 0 || lbl_1_data_111[i] != 3 || lbl_1_data_115[i] < 54) {
                            Hu3DMotionSet(obj->mdlId[i + 13], obj->mtnId[i + motOfs[lbl_1_data_111[i]]]);
                        }
                        if (lbl_1_data_111[i] >= 2) {
                            Hu3DModelRotSet(obj->mdlId[i + 13], 0.0f, (lbl_1_data_111[i] == 3 && lbl_1_data_115[i] < 60) ? -90.0 + 1.5 * lbl_1_data_115[i] : 0.0, 0.0f);
                        } else {
                            Hu3DModelRotSet(obj->mdlId[i + 13], 0.0f, -90.0f, 0.0f);
                        }
                    }
                    if (i == 0 && lbl_1_data_111[i] == 3 && lbl_1_data_115[i] >= 54) {
                        if (i == 0 && lbl_1_data_111[i] == 3 && lbl_1_data_115[i] == 54) {
                            Hu3DMotionShiftSet(obj->mdlId[i + 13], obj->mtnId[4], 40.0f, 6.0f, 0);
                        }
                    } else {
                        Hu3DMotionTimeSet(obj->mdlId[i + 13], lbl_1_data_115[i] / ((i == 0 && lbl_1_data_111[i] == 3) ? 2.0f : 1.0f));
                    }
                    Hu3DModelAttrReset(obj->mdlId[i + 13], 1);
                }
            }
        }
        if (lbl_1_data_119[0] == 0 && lbl_1_data_111[3] >= 1 && lbl_1_data_111[0] >= 2 && lbl_1_data_111[0] <= 3) {
            float t2 = 0.0625f;
            float s2 = 1.0f - t2;

            if (lbl_1_data_111[0] == 2 || (lbl_1_data_111[0] == 2 && lbl_1_data_115[0] == 0)) {
                CRotM[0].x = -40.0f;
            } else {
                CRotM[0].x = -40.0f * t2 + CRotM[0].x * s2;
            }
        } else {
            CRotM[0].x = -63.0f;
        }
        if (lbl_1_data_119[0] == 2) {
            CRotM[0].x = -90.0f;
        }
        if (cnt == 0 && lbl_1_data_119[0] == 1) {
            lbl_1_data_119[0] = 0;
            lbl_1_data_111[0] = lbl_1_data_111[1] = lbl_1_data_111[2] = lbl_1_data_111[3] = -1;
            lbl_1_data_115[0] = lbl_1_data_115[1] = lbl_1_data_115[2] = lbl_1_data_115[3] = 0;
            Hu3DModelRotSet(obj->mdlId[3], 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(obj->mdlId[7], 1);
        } else if (cnt == 0 && lbl_1_data_119[0] == 0) {
            HuVecF unused[2] = { { -1.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f } };

            lbl_1_data_119[0] = 2;
            lbl_1_data_111[0] = lbl_1_data_111[1] = lbl_1_data_111[2] = lbl_1_data_111[3] = 4;
            lbl_1_data_111[0] = -1;
            lbl_1_data_115[0] = lbl_1_data_115[1] = lbl_1_data_115[2] = lbl_1_data_115[3] = 0;
            CRotM[0].x = -90.0f;
            Hu3DModelPosSet(obj->mdlId[3], 0.0f, 0.0f, -1.0f);
            Hu3DModelLayerSet(obj->mdlId[3], 2);
            Hu3DModelRotSet(obj->mdlId[3], 255.0f, 255.0f, 255.0f);
        } else if (cnt == 0 && lbl_1_data_119[0] == 2) {
            lbl_1_data_119[0]++;
            for (i = 0; i < 4; i++) {
                if (i == 0) {
                    Hu3DModelShadowSet(obj->mdlId[i + 13]);
                }
                Hu3DModelLayerSet(obj->mdlId[i + 13], 1);
                Hu3DModelCameraSet(obj->mdlId[i + 13], 2);
                Hu3DModelAttrSet(obj->mdlId[i + 13], 1);
            }
            Hu3DModelPosSet(obj->mdlId[3], 0.0f, 0.0f, 0.0f);
            Hu3DModelLayerSet(obj->mdlId[3], 0);
            Hu3DModelAttrSet(obj->mdlId[3], 1);
            Hu3DModelAttrSet(obj->mdlId[4], 1);
        } else if (cnt == 0 && lbl_1_data_119[0] == 4) {
            lbl_1_data_119[0] = 3;
            Hu3DModelAttrSet(obj->mdlId[4], 1);
        }
    }
    if (omSysExitReq) {
        for (i = 0; i < 4; i++) {
            Hu3DModelAttrSet(obj->mdlId[i + 13], 1);
        }
    }
    lbl_1_data_7C[0] -= (lbl_1_data_7C[0] > 0 && lbl_1_bss_2ED2C >= 1003);
    lbl_1_bss_4 += (lbl_1_bss_4 > 0 && lbl_1_bss_2ED2C >= 1001);
    lbl_1_bss_14 -= (lbl_1_bss_14 > 0);
    if (lbl_1_bss_14 == 0 && rand8() % 2 == 0) {
        for (i = 0; i < 96; i++) {
            if (lbl_1_bss_11FC[i].unk01C == -1) {
                break;
            }
        }
        if (i < 96) {
            lbl_1_bss_14 = ((lbl_1_bss_4 > 480) ? 0 : (480 - lbl_1_bss_4) * 14 / 480) + 12;
            do {
                j = rand8() % 4;
            } while (j == lbl_1_data_11C[0] || j == lbl_1_data_11C[1]);
            lbl_1_data_11C[1] = lbl_1_data_11C[0];
            lbl_1_data_11C[0] = j;
            lbl_1_bss_11FC[i].unk01C = 0;
            lbl_1_bss_11FC[i].unk000 = j * 450 + 450.0f * (rand8() / 255.0f) - 900.0f;
            lbl_1_bss_11FC[i].unk004 = 2400.0f;
            lbl_1_bss_11FC[i].unk008 = 1800.0f * (rand8() / 255.0f) - 900.0f;
            lbl_1_bss_11FC[i].unk00C = 0.0f;
            lbl_1_bss_11FC[i].unk010 = (rand8() % 2) * 2 - 1;
            lbl_1_bss_11FC[i].unk014 = -4.0f;
            lbl_1_bss_11FC[i].unk018 = 0;
            lbl_1_bss_11FC[i].unk01A = rand8() % 2;
            lbl_1_bss_11FC[i].unk019 = lbl_1_data_F0[lbl_1_bss_11FC[i].unk01A + 2][0] * (rand8() / 255.0f);
            lbl_1_bss_11FC[i].unk020 = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrSet(obj->mdlId[i + 8], 1);
    }
    for (i = 0; i < 96; i++) {
        if (lbl_1_bss_11FC[i].unk01C >= 0) {
            if (lbl_1_bss_11FC[i].unk004 < 20.0f) {
                lbl_1_bss_11FC[i].unk01C = -1;
                continue;
            }
            lbl_1_bss_11FC[i].unk01C++;
            lbl_1_bss_11FC[i].unk000 += lbl_1_bss_11FC[i].unk00C;
            lbl_1_bss_11FC[i].unk004 += lbl_1_bss_11FC[i].unk014;
            lbl_1_bss_11FC[i].unk00C += 0.0078125 * lbl_1_bss_11FC[i].unk010;
            if ((lbl_1_bss_11FC[i].unk010 == 1 && lbl_1_bss_11FC[i].unk00C >= 0.25f) || (lbl_1_bss_11FC[i].unk010 == -1 && lbl_1_bss_11FC[i].unk00C <= -0.25f)) {
                lbl_1_bss_11FC[i].unk010 = -lbl_1_bss_11FC[i].unk010;
            }
            lbl_1_bss_11FC[i].unk018 = (lbl_1_bss_11FC[i].unk004 < 20.0f) ? 0.0f
                : ((lbl_1_bss_11FC[i].unk004 < 300.0f) ? 255.0f * (lbl_1_bss_11FC[i].unk004 - 20.0f) / 280.0f : 255.0f);
            lbl_1_bss_11FC[i].unk019++;
            lbl_1_bss_11FC[i].unk019 %= lbl_1_data_F0[lbl_1_bss_11FC[i].unk01A + 2][0];
            if (lbl_1_bss_11FC[i].unk020 >= 0 && lbl_1_bss_2ED2C == 1002) {
                lbl_1_bss_11FC[i].unk020 = -1;
            }
            if (lbl_1_bss_11FC[i].unk020 >= 0) {
                Hu3DModelRotSet(obj->mdlId[lbl_1_bss_11FC[i].unk020 + 8], CRotM[1].x, 0.0f, 0.0f);
                Hu3DModelPosSet(obj->mdlId[lbl_1_bss_11FC[i].unk020 + 8], lbl_1_bss_11FC[i].unk000, lbl_1_bss_11FC[i].unk004, lbl_1_bss_11FC[i].unk008);
                Hu3DMotionTimeSet(obj->mdlId[lbl_1_bss_11FC[i].unk020 + 8], lbl_1_bss_11FC[i].unk019);
                Hu3DModelAttrReset(obj->mdlId[lbl_1_bss_11FC[i].unk020 + 8], 1);
            }
        }
    }
    if (lbl_1_bss_2ED2C <= 1001) {
        if (lbl_1_data_124[0] < 120) {
            lbl_1_data_124[0]++;
            CenterM[1].x -= 8.0f * (lbl_1_data_124[0] / 120.0f);
        } else if (CenterM[1].x >= 434.0f) {
            CenterM[1].x -= 8.0f;
        } else if (lbl_1_data_128[0] > 0) {
            CenterM[1].x -= 8.0f * (lbl_1_data_128[0] / 120.0f);
            lbl_1_data_128[0]--;
        }
    }
    if (lbl_1_bss_2ED2C == 1002) {
        float t3 = 0.0625f;
        float s3 = 1.0f - t3;

        CZoomM[1] = 4300.0f * t3 + CZoomM[1] * s3;
        CenterM[1].x = -50.0f * t3 + CenterM[1].x * s3;
        CenterM[1].y = -150.0f * t3 + CenterM[1].y * s3;
        CenterM[1].z = CenterM[1].z * s3;
        CRotM[1].x = -63.0f * t3 + CRotM[1].x * s3;
        CRotM[1].y = CRotM[1].y * s3;
        CRotM[1].z = CRotM[1].z * s3;
    }
    {
        s32 v184 = 0;
        s32 v180 = 0;
        s32 arr1E8[2] = { 0, 0 };
        s32 v17C = -1;
        float arr258[12];

        for (i = 0; i < 12; i++) {
            arr258[i] = -2000.0f;
            lbl_1_bss_1120[i] = 2000.0f;
        }
        for (i = 0; i < 64; i++) {
            lbl_1_bss_9D1C[i].unk018 = lbl_1_bss_9D1C[i].unk000;
            lbl_1_bss_9D1C[i].unk01C = lbl_1_bss_9D1C[i].unk004;
            lbl_1_bss_9D1C[i].unk020 = lbl_1_bss_9D1C[i].unk008;
        }
        for (i = 0; i < 72; i++) {
            if (lbl_1_bss_977C[i].unk010 != -1) {
                lbl_1_bss_977C[i].unk010++;
                if (lbl_1_bss_977C[i].unk010 >= 57) {
                    lbl_1_bss_977C[i].unk010 = -1;
                }
            }
        }
        for (i = 0; i < 640; i++) {
            if (lbl_1_bss_1F7C[i].unk02C != -1) {
                lbl_1_bss_1F7C[i].unk02C++;
                if (lbl_1_bss_1F7C[i].unk02C >= 192) {
                    lbl_1_bss_1F7C[i].unk02C = -1;
                }
            }
        }
        for (i = 0; i < 64; i++) {
            if (lbl_1_bss_9D1C[i].unk028 >= 0 && lbl_1_bss_9D1C[i].unk000 < -1200.0f) {
                if (lbl_1_bss_9D1C[i].unk02C == 1) {
                    Hu3DModelAttrSet(obj->mdlId[lbl_1_bss_9D1C[i].unk036 + 18], 1);
                    lbl_1_data_D0[lbl_1_bss_9D1C[i].unk036] = 0;
                } else if (lbl_1_bss_9D1C[i].unk036 == 0) {
                    Hu3DModelAttrSet(obj->mdlId[12], 1);
                }
                lbl_1_bss_9D1C[i].unk028 = -1;
            }
            if (lbl_1_bss_9D1C[i].unk028 < 0) {
                v17C = (v17C != -1) ? v17C : i;
                continue;
            }
            lbl_1_bss_9D1C[i].unk028++;
            if (lbl_1_bss_9D1C[i].unk02E == 0 && lbl_1_bss_9D1C[i].unk02C == 0 && lbl_1_bss_2ED2C == 1003) {
                v184 = 1;
            }
            if (i == 0 && lbl_1_bss_2ED2C <= 1001) {
                switch (lbl_1_bss_9D1C[i].unk028 - 63) {
                    case -30:
                        Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
                        if (lbl_1_bss_2ED50[0].unk000 < 3) {
                            lbl_1_bss_2ED50[0].unk010[lbl_1_bss_2ED50[0].unk000] = 0;
                            lbl_1_bss_2ED50[0].unk000++;
                        }
                        break;
                    case -1:
                        Hu3DModelAttrSet(obj->mdlId[2], 0x40000002);
                        break;
                    case 65:
                        Hu3DModelAttrReset(obj->mdlId[2], 0x40000002);
                        break;
                    case 73:
                        if (lbl_1_bss_2ED50[1].unk000 < 3) {
                            lbl_1_bss_2ED50[1].unk010[lbl_1_bss_2ED50[1].unk000] = 0;
                            lbl_1_bss_2ED50[1].unk000++;
                        }
                        break;
                }
            }
            if (lbl_1_bss_9D1C[i].unk02E == 1 && lbl_1_bss_9D1C[i].unk030 >= 0) {
                if (lbl_1_bss_9D1C[i].unk02C == 0) {
                    lbl_1_bss_9D1C[i].unk010 = (lbl_1_bss_9D1C[i].unk030 / 16 == 0) ? 15.0
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 == 10) ? lbl_1_bss_9D1C[i].unk010 - 14.0f
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 == 13) ? lbl_1_bss_9D1C[i].unk010 - 12.0f
                        : ((lbl_1_bss_9D1C[i].unk004 < -250.0f) ? 0.75 * lbl_1_bss_9D1C[i].unk010 : lbl_1_bss_9D1C[i].unk010 - 2.0f)));
                } else {
                    lbl_1_bss_9D1C[i].unk010 = (lbl_1_bss_9D1C[i].unk030 / 16 == 0) ? 20.0
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 == 13) ? lbl_1_bss_9D1C[i].unk010 - 20.0f
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 == 14) ? lbl_1_bss_9D1C[i].unk010 - 15.0f
                        : ((lbl_1_bss_9D1C[i].unk004 < -250.0f) ? 0.75 * lbl_1_bss_9D1C[i].unk010
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 == 15) ? lbl_1_bss_9D1C[i].unk010 - 10.0f
                        : ((lbl_1_bss_9D1C[i].unk030 / 16 >= 10) ? lbl_1_bss_9D1C[i].unk010 - 3.0f : lbl_1_bss_9D1C[i].unk010 - 2.0f)))));
                }
                lbl_1_bss_9D1C[i].unk00C = (lbl_1_bss_9D1C[i].unk030 / 16 == 9) ? lbl_1_bss_9D1C[i].unk00C - 3.0f : lbl_1_bss_9D1C[i].unk00C;
            }
            if (lbl_1_bss_2ED2C <= 1003 || lbl_1_bss_9D1C[i].unk02E == 1) {
                s32 v178 = 0;

                if (0.0f == lbl_1_bss_9D1C[i].unk024) {
                    lbl_1_bss_9D1C[i].unk000 += lbl_1_bss_9D1C[i].unk00C;
                    lbl_1_bss_9D1C[i].unk008 += lbl_1_bss_9D1C[i].unk014;
                } else if (lbl_1_bss_9D1C[i].unk028 >= 63) {
                    lbl_1_bss_9D1C[i].unk000 += lbl_1_bss_9D1C[i].unk00C * cos(M_PI * lbl_1_bss_9D1C[i].unk024 / 180.0) - lbl_1_bss_9D1C[i].unk014 * sin(M_PI * lbl_1_bss_9D1C[i].unk024 / 180.0);
                    lbl_1_bss_9D1C[i].unk008 += 0.75 * (lbl_1_bss_9D1C[i].unk00C * sin(M_PI * lbl_1_bss_9D1C[i].unk024 / 180.0) + lbl_1_bss_9D1C[i].unk014 * cos(M_PI * lbl_1_bss_9D1C[i].unk024 / 180.0));
                    lbl_1_bss_9D1C[i].unk032 = 0x200;
                    if (lbl_1_bss_9D1C[i].unk028 == 63) {
                        Hu3DModelAttrReset(obj->mdlId[5], 1);
                    }
                    if (lbl_1_bss_9D1C[i].unk028 >= 87) {
                        lbl_1_bss_9D1C[i].unk024 = (lbl_1_bss_9D1C[i].unk024 <= 2.0f && lbl_1_bss_9D1C[i].unk024 >= -2.0f) ? 0.0f
                            : ((lbl_1_bss_9D1C[i].unk024 < 0.0f) ? 2.0f + lbl_1_bss_9D1C[i].unk024 : lbl_1_bss_9D1C[i].unk024 - 2.0f);
                    }
                }
                lbl_1_bss_9D1C[i].unk004 += lbl_1_bss_9D1C[i].unk010;
                if (lbl_1_bss_9D1C[i].unk004 < -250.0f && lbl_1_bss_9D1C[i].unk01C >= -250.0f) {
                    for (j = 0; j < 72; j++) {
                        if (lbl_1_bss_977C[j].unk010 == -1) {
                            break;
                        }
                    }
                    if (j < 72) {
                        lbl_1_bss_977C[j].unk010 = 11;
                        lbl_1_bss_977C[j].unk000 = lbl_1_bss_9D1C[i].unk000;
                        lbl_1_bss_977C[j].unk008 = lbl_1_bss_9D1C[i].unk008;
                        lbl_1_bss_977C[j].unk00C = lbl_1_bss_9D1C[i].unk02C;
                    }
                    if (lbl_1_bss_2ED2C == 1001) {
                        if (lbl_1_bss_2ED50[6].unk000 < 3) {
                            lbl_1_bss_2ED50[6].unk004[lbl_1_bss_2ED50[6].unk000] = lbl_1_bss_977C[j].unk000;
                            lbl_1_bss_2ED50[6].unk010[lbl_1_bss_2ED50[6].unk000] = 1;
                            lbl_1_bss_2ED50[6].unk000++;
                        }
                    } else if (lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk000 < 3) {
                        lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk004[lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk000] = lbl_1_bss_977C[j].unk000;
                        lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk010[lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk000] = 1;
                        lbl_1_bss_2ED50[(lbl_1_bss_9D1C[i].unk02C == 0) ? 3 : 5].unk000++;
                    }
                }
                for (j = 0; j < 64; j++) {
                    float dx;
                    float w;
                    float tmp;

                    if (i == j) {
                        continue;
                    }
                    if (lbl_1_bss_9D1C[j].unk028 < 0) {
                        continue;
                    }
                    if ((abs((s32)((600.0f + lbl_1_bss_9D1C[i].unk008) / 100.0f) - (s32)((600.0f + lbl_1_bss_9D1C[j].unk008) / 100.0f))
                            > (lbl_1_bss_9D1C[i].unk02C == 1) + lbl_1_bss_9D1C[j].unk02C) == 1) {
                        continue;
                    }
                    dx = lbl_1_bss_9D1C[i].unk000 - (lbl_1_bss_9D1C[j].unk000 + ((i < j) ? lbl_1_bss_9D1C[j].unk00C : 0.0f));
                    w = ((lbl_1_bss_9D1C[i].unk02C == 0) ? 32 : 125) + ((lbl_1_bss_9D1C[j].unk02C == 0) ? 32 : 125);
                    if (fabs(dx) < w) {
                        if (lbl_1_bss_9D1C[i].unk000 < lbl_1_bss_9D1C[j].unk000) {
                            if (lbl_1_bss_9D1C[j].unk02C == 1 && lbl_1_bss_9D1C[i].unk02C == 0) {
                                lbl_1_bss_9D1C[i].unk00C = lbl_1_bss_9D1C[j].unk00C;
                                lbl_1_bss_9D1C[i].unk037 = 1;
                            } else if (lbl_1_bss_9D1C[j].unk02C == lbl_1_bss_9D1C[i].unk02C && lbl_1_bss_9D1C[i].unk00C > lbl_1_bss_9D1C[j].unk00C) {
                                tmp = lbl_1_bss_9D1C[j].unk00C;
                                lbl_1_bss_9D1C[j].unk00C = lbl_1_bss_9D1C[i].unk00C;
                                lbl_1_bss_9D1C[i].unk00C = tmp;
                            }
                            tmp = (lbl_1_bss_9D1C[i].unk000 + (lbl_1_bss_9D1C[j].unk000 + ((i < j) ? lbl_1_bss_9D1C[j].unk00C : 0.0f))) / 2.0f;
                            lbl_1_bss_9D1C[i].unk000 = tmp - w / 2.0f;
                            lbl_1_bss_9D1C[j].unk000 = tmp + w / 2.0f - ((i < j) ? lbl_1_bss_9D1C[j].unk00C : 0.0f);
                            if (lbl_1_bss_9D1C[j].unk037 == 1 && lbl_1_bss_9D1C[i].unk037 == 0) {
                                lbl_1_bss_9D1C[i].unk037 = 1;
                                lbl_1_bss_9D1C[i].unk032 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 658.2857142857143 : lbl_1_bss_9D1C[i].unk032;
                            }
                        } else {
                            if (lbl_1_bss_9D1C[i].unk02C == 1 && lbl_1_bss_9D1C[j].unk02C == 0) {
                                lbl_1_bss_9D1C[j].unk00C = lbl_1_bss_9D1C[i].unk00C;
                                lbl_1_bss_9D1C[j].unk037 = 1;
                            } else if (lbl_1_bss_9D1C[i].unk02C == lbl_1_bss_9D1C[j].unk02C && lbl_1_bss_9D1C[j].unk00C > lbl_1_bss_9D1C[i].unk00C) {
                                tmp = lbl_1_bss_9D1C[j].unk00C;
                                lbl_1_bss_9D1C[j].unk00C = lbl_1_bss_9D1C[i].unk00C;
                                lbl_1_bss_9D1C[i].unk00C = tmp;
                            }
                            tmp = (lbl_1_bss_9D1C[i].unk000 + (lbl_1_bss_9D1C[j].unk000 + ((i < j) ? lbl_1_bss_9D1C[j].unk00C : 0.0f))) / 2.0f;
                            lbl_1_bss_9D1C[j].unk000 = tmp - w / 2.0f - ((i < j) ? lbl_1_bss_9D1C[j].unk00C : 0.0f);
                            lbl_1_bss_9D1C[i].unk000 = tmp + w / 2.0f;
                            lbl_1_bss_9D1C[j].unk037 = (lbl_1_bss_9D1C[i].unk037 == 1) ? 1 : lbl_1_bss_9D1C[j].unk037;
                        }
                    }
                }
                if (lbl_1_bss_9D1C[i].unk02E == 0 && lbl_1_bss_9D1C[i].unk018 >= lbl_1_bss_9D1C[i].unk02C * 50 - 350
                    && lbl_1_bss_9D1C[i].unk000 < lbl_1_bss_9D1C[i].unk02C * 50 - 350 && lbl_1_bss_9D1C[i].unk037 == 0) {
                    lbl_1_bss_9D1C[i].unk00C *= 1.5;
                    lbl_1_bss_9D1C[i].unk037 = 1;
                }
                if (lbl_1_bss_9D1C[i].unk02E == 0 && lbl_1_bss_9D1C[i].unk000 < -640.0f) {
                    lbl_1_bss_9D1C[i].unk02E = 1;
                    lbl_1_bss_9D1C[i].unk030 = -16;
                    if (lbl_1_bss_2ED2C == 1001) {
                        lbl_1_bss_9D1C[i].unk00C *= 0.875;
                    }
                    if (lbl_1_bss_9D1C[i].unk036 >= 0) {
                        s32 mdl2 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;

                        if (lbl_1_bss_9D1C[i].unk02E == 1) {
                            Hu3DModelAttrReset(obj->mdlId[mdl2], 0x40000001);
                        } else {
                            Hu3DModelAttrSet(obj->mdlId[mdl2], 0x40000001);
                        }
                        Hu3DMotionSet(obj->mdlId[mdl2], obj->mtnId[lbl_1_bss_9D1C[i].unk02C + motOfs[lbl_1_bss_9D1C[i].unk02E]]);
                        Hu3DMotionTimeSet(obj->mdlId[mdl2], lbl_1_bss_9D1C[i].unk030 / 16);
                        if (lbl_1_bss_9D1C[i].unk02C == 1) {
                            Hu3DMotionSpeedSet(obj->mdlId[mdl2], 0.75f);
                        }
                    }
                    if (lbl_1_bss_9D1C[i].unk02C == 0) {
                        if (lbl_1_bss_2ED50[7].unk000 < 3) {
                            lbl_1_bss_2ED50[7].unk010[lbl_1_bss_2ED50[7].unk000] = 0;
                            lbl_1_bss_2ED50[7].unk000++;
                        }
                    } else if (lbl_1_bss_2ED50[8].unk000 < 3) {
                        lbl_1_bss_2ED50[8].unk010[lbl_1_bss_2ED50[8].unk000] = 0;
                        lbl_1_bss_2ED50[8].unk000++;
                    }
                }
            } else {
                lbl_1_bss_2ED2C == 1004;
            }
            if (lbl_1_bss_9D1C[i].unk02E != 1 && (lbl_1_bss_2ED2C != 1001 || (i == 0 && lbl_1_bss_9D1C[i].unk028 >= 63))) {
                s32 prev = lbl_1_bss_9D1C[i].unk030;
                s32 a;

                lbl_1_bss_9D1C[i].unk030 += (lbl_1_bss_9D1C[i].unk037 == 1) ? lbl_1_bss_9D1C[i].unk032 * 2 / 16 : lbl_1_bss_9D1C[i].unk032 / 16;
                if (lbl_1_bss_9D1C[i].unk02E == 3) {
                    if (lbl_1_bss_9D1C[i].unk030 >= (s32)(lbl_1_data_F0[0][lbl_1_bss_9D1C[i].unk02E] * 16
                            * ((lbl_1_bss_9D1C[i].unk02E == 3 && lbl_1_bss_9D1C[i].unk036 >= 0) ? 1.5f : 1.0f))) {
                        lbl_1_bss_9D1C[i].unk02E = 2;
                        lbl_1_bss_9D1C[i].unk030 = 0x280;
                        lbl_1_bss_9D1C[i].unk032 = ((lbl_1_data_78[0] == 4) ? 5 : 5) * (rand8() / 2 + 192);
                        if (lbl_1_bss_9D1C[i].unk036 >= 0) {
                            s32 mdl3 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;
                            HU3DMODEL *model;

                            Hu3DMotionShiftSet(obj->mdlId[mdl3], obj->mtnId[lbl_1_bss_9D1C[i].unk02C + motOfs[lbl_1_bss_9D1C[i].unk02E]], 40.0f, 15.0f, 0x40000001);
                            model = &Hu3DData[obj->mdlId[mdl3]];
                            model->motShiftWork.speed = 5.0 * (0.3 + 0.3 * rand8() / 256.0);
                        }
                    }
                }
                lbl_1_bss_9D1C[i].unk030 %= (s32)(lbl_1_data_F0[0][lbl_1_bss_9D1C[i].unk02E] * 16
                    * ((lbl_1_bss_9D1C[i].unk02E == 3 && lbl_1_bss_9D1C[i].unk036 >= 0) ? 1.5f : 1.0f));
                if (lbl_1_bss_9D1C[i].unk02E == 0) {
                    if (lbl_1_bss_9D1C[i].unk02C == 0) {
                        a = ((lbl_1_bss_9D1C[i].unk030 + 240) / 16) / ((lbl_1_data_F0[0][lbl_1_bss_9D1C[i].unk02E] + 1) / 2);
                        prev = ((prev + 240) / 16) / ((lbl_1_data_F0[0][lbl_1_bss_9D1C[i].unk02E] + 1) / 2);
                    } else {
                        s32 mdl4 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;
                        HU3DMODEL *model2;

                        model2 = &Hu3DData[obj->mdlId[mdl4]];
                        a = 1.65 + 2.0f * (Hu3DMotionTimeGet(obj->mdlId[mdl4]) / Hu3DMotionMaxTimeGet(obj->mdlId[mdl4]));
                        prev = 1.65 + 2.0f * ((model2->motWork.speed + Hu3DMotionTimeGet(obj->mdlId[mdl4])) / Hu3DMotionMaxTimeGet(obj->mdlId[mdl4]));
                    }
                    a = a % 2;
                    prev = prev % 2;
                    if (a != prev) {
                        if (lbl_1_bss_2ED2C > 1001 || (i == 0 && lbl_1_bss_9D1C[i].unk008 > -310.0f)) {
                            for (j = 0; j < 640; j++) {
                                if (lbl_1_bss_1F7C[j].unk02C == -1) {
                                    break;
                                }
                            }
                            if (j < 640) {
                                lbl_1_bss_1F7C[j].unk02C = 11;
                                lbl_1_bss_1F7C[j].unk000 = lbl_1_bss_9D1C[i].unk000 + ((lbl_1_bss_9D1C[i].unk02C == 1) ? -40 : 0);
                                lbl_1_bss_1F7C[j].unk008 = lbl_1_bss_9D1C[i].unk008 + (rand8() * 16 / 255) - 8.0f;
                                lbl_1_bss_1F7C[j].unk018 = 0.0f;
                                lbl_1_bss_1F7C[j].unk01C = 0.0f;
                                lbl_1_bss_1F7C[j].unk014 = 0.0f;
                                lbl_1_bss_1F7C[j].unk020 = 1.0f;
                                lbl_1_bss_1F7C[j].unk024 = 1.0f;
                                lbl_1_bss_1F7C[j].unk00C = lbl_1_bss_9D1C[i].unk024;
                                lbl_1_bss_1F7C[j].unk029 = lbl_1_bss_9D1C[i].unk02C;
                                lbl_1_bss_1F7C[j].unk028 = 1 - prev;
                                lbl_1_bss_1F7C[j].unk028 = (lbl_1_bss_1F7C[j].unk028 > 1) ? 1 : lbl_1_bss_1F7C[j].unk028;
                            }
                            if (lbl_1_bss_2ED2C == 1001) {
                                if (lbl_1_bss_2ED50[9].unk000 < 3) {
                                    lbl_1_bss_2ED50[9].unk004[lbl_1_bss_2ED50[9].unk000] = lbl_1_bss_9D1C[i].unk000;
                                    lbl_1_bss_2ED50[9].unk010[lbl_1_bss_2ED50[9].unk000] = 1;
                                    lbl_1_bss_2ED50[9].unk000++;
                                }
                            } else if (lbl_1_bss_9D1C[i].unk02C == 1) {
                                if (lbl_1_bss_2ED50[4].unk000 < 3) {
                                    lbl_1_bss_2ED50[4].unk004[lbl_1_bss_2ED50[4].unk000] = lbl_1_bss_9D1C[i].unk000;
                                    lbl_1_bss_2ED50[4].unk010[lbl_1_bss_2ED50[4].unk000] = 1;
                                    lbl_1_bss_2ED50[4].unk000++;
                                }
                            }
                        }
                    }
                }
            } else {
                lbl_1_bss_9D1C[i].unk030 += (lbl_1_bss_9D1C[i].unk030 / 16 < lbl_1_data_F0[0][lbl_1_bss_9D1C[i].unk02E] - 1) * 16;
            }
            if (lbl_1_bss_9D1C[i].unk02C == 1) {
                s32 t4 = (lbl_1_bss_9D1C[i].unk028 + lbl_1_bss_9D1C[i].unk02D) % 80;

                lbl_1_bss_9D1C[i].unk93C = (t4 < 20) ? 254 - t4 * 6 : ((t4 < 40) ? 134 : ((t4 < 60) ? (t4 - 40) * 6 + 134 : 254));
            }
            arr1E8[lbl_1_bss_9D1C[i].unk02C]++;
            for (j = (s32)((600.0f + lbl_1_bss_9D1C[i].unk008) / 100.0f) - (lbl_1_bss_9D1C[i].unk02C == 1);
                 j <= (s32)((600.0f + lbl_1_bss_9D1C[i].unk008) / 100.0f) + (lbl_1_bss_9D1C[i].unk02C == 1); j++) {
                if (j >= 0 && j < 12 && arr258[j] < lbl_1_bss_9D1C[i].unk000 + ((lbl_1_bss_9D1C[i].unk02C == 0) ? 50 : 200)) {
                    arr258[j] = lbl_1_bss_9D1C[i].unk000 + ((lbl_1_bss_9D1C[i].unk02C == 0) ? 50 : 200);
                }
                if (j >= 0 && j < 12 && lbl_1_bss_1120[j] > lbl_1_bss_9D1C[i].unk000 + ((lbl_1_bss_9D1C[i].unk02C == 0) ? 50 : 200)
                    && lbl_1_bss_9D1C[i].unk000 > -640.0f) {
                    lbl_1_bss_1120[j] = lbl_1_bss_9D1C[i].unk000 + ((lbl_1_bss_9D1C[i].unk02C == 0) ? 50 : 200);
                }
            }
            if (lbl_1_bss_9D1C[i].unk036 >= 0) {
                s32 mdl5 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;

                if (lbl_1_bss_9D1C[i].unk02C == 0) {
                    if (lbl_1_bss_9D1C[i].unk02E == 1) {
                        Hu3DModelAttrReset(obj->mdlId[mdl5], 0x40000001);
                    } else {
                        Hu3DModelAttrSet(obj->mdlId[mdl5], 0x40000001);
                    }
                    Hu3DMotionSet(obj->mdlId[mdl5], obj->mtnId[lbl_1_bss_9D1C[i].unk02C + motOfs[lbl_1_bss_9D1C[i].unk02E]]);
                    Hu3DMotionTimeSet(obj->mdlId[mdl5], lbl_1_bss_9D1C[i].unk030 / 16);
                }
                Hu3DModelAttrReset(obj->mdlId[mdl5], 1);
                Hu3DModelPosSet(obj->mdlId[mdl5], lbl_1_bss_9D1C[i].unk000, lbl_1_bss_9D1C[i].unk004, lbl_1_bss_9D1C[i].unk008);
                Hu3DModelLayerSet(obj->mdlId[mdl5], 1);
                Hu3DModelCameraSet(obj->mdlId[mdl5], 2);
                if (lbl_1_bss_9D1C[i].unk02E >= 2) {
                    Hu3DModelRotSet(obj->mdlId[mdl5], 0.0f,
                        (lbl_1_bss_9D1C[i].unk02E == 3 && lbl_1_bss_9D1C[i].unk030 / 3.0f / 16.0f < 30.0f) ? -90.0f + 3.0f * (lbl_1_bss_9D1C[i].unk030 / 3.0f / 16.0f) : 0.0f,
                        0.0f);
                } else {
                    Hu3DModelRotSet(obj->mdlId[mdl5], 0.0f, 270.0f - lbl_1_bss_9D1C[i].unk024, 0.0f);
                }
            }
        }
        if (v17C != -1 && lbl_1_bss_2ED2C == 1003) {
            s32 tbl1[10][2] = { { 10, 30 }, { 20, 40 }, { 20, 40 }, { 40, 60 }, { 50, 70 }, { 70, 99 }, { 90, 99 }, { 90, 90 }, { 70, 80 }, { 99, 99 } };
            s32 tbl2[10][2] = { { 0, 0 }, { 0, 0 }, { 0, 3 }, { 1, 2 }, { 0, 1 }, { 0, 2 }, { 4, 6 }, { 6, 8 }, { 8, 8 }, { 8, 8 } };
            s32 big;
            s32 lane2;
            s32 v154;
            s32 k;
            s32 v14C;

            big = rand8() % 5 == 4;
            v154 = big + rand8() % (12 - big * 2);
            lane2 = 30 - lbl_1_data_7C[0] / 60;
            i = v17C;
            lbl_1_data_12C[0] -= (lbl_1_data_12C[0] > 0);
            lbl_1_data_12C[1] -= (lbl_1_data_12C[1] > 0);
            lane2 = (lane2 < 0) ? 0 : ((lane2 > 29) ? 29 : lane2);
            v14C = (lane2 - 1) / 3;
            lane2 = lane2 / 3;
            if (big == 1) {
                for (k = 0; k < 8; k++) {
                    if (lbl_1_data_D0[k] == 0) {
                        break;
                    }
                }
            }
            if ((big == 0 || k < 8) && (big * 350 + 1200) + lbl_1_data_7C[0] * ((big == 0) ? -350.0 : -500.0) / 60.0 < -640.0) {
                if ((big == 0 && lbl_1_data_12C[0] == 0 && tbl1[lane2][1] > 0
                        && arr1E8[0] <= tbl1[lane2][0] + ((tbl1[lane2][1] - tbl1[lane2][0] == 0) ? 0 : rand8() % (tbl1[lane2][1] - tbl1[lane2][0])) * 64 / 100)
                    || (big == 1 && lbl_1_data_12C[1] == 0 && tbl2[v14C][1] > 0
                        && arr1E8[1] < tbl2[v14C][0] + ((tbl2[v14C][1] - tbl2[v14C][0] == 0) ? 0 : rand8() % (tbl2[v14C][1] - tbl2[v14C][0])))) {
                    if (110.0f + arr258[v154] <= 1200 + big * 350 + ((big == 0) ? 50 : 200)
                        && (big == 0
                            || ((v154 - 1 < 0 || 110.0f + arr258[v154 - 1] <= big * 350 + 1200 - ((big == 0) ? 50 : 200))
                                && (v154 + 1 >= 12 || 110.0f + arr258[v154 + 1] <= big * 350 + 1200 - ((big == 0) ? 50 : 200))))) {
                        lbl_1_bss_9D1C[i].unk028 = 0;
                        lbl_1_bss_9D1C[i].unk02D = rand8();
                        lbl_1_bss_9D1C[i].unk02C = big;
                        lbl_1_bss_9D1C[i].unk000 = 1200 + big * 350 + rand8() * 36 / 255;
                        lbl_1_bss_9D1C[i].unk004 = 0.0f;
                        lbl_1_bss_9D1C[i].unk008 = v154 * 100 - 550;
                        lbl_1_bss_9D1C[i].unk00C = (big == 0) ? (-400.0 + 200.0 * (rand8() / 255.0 - 0.75)) / 60.0 : (-600.0 + 200.0 * (rand8() / 255.0 - 0.5)) / 60.0;
                        lbl_1_bss_9D1C[i].unk010 = 0.0f;
                        lbl_1_bss_9D1C[i].unk014 = 0.0f;
                        lbl_1_bss_9D1C[i].unk018 = lbl_1_bss_9D1C[i].unk000;
                        lbl_1_bss_9D1C[i].unk020 = lbl_1_bss_9D1C[i].unk008;
                        lbl_1_bss_9D1C[i].unk02E = 0;
                        lbl_1_bss_9D1C[i].unk030 = 0x100;
                        lbl_1_bss_9D1C[i].unk032 = (big == 0) ? 256.0f * (2.0f * (60.0f * -lbl_1_bss_9D1C[i].unk00C / 350.0f))
                                                              : 256.0 * (1.25 * (60.0f * -lbl_1_bss_9D1C[i].unk00C) / 500.0);
                        lbl_1_bss_9D1C[i].unk032 &= 0xFFF0;
                        lbl_1_bss_9D1C[i].unk036 = (lbl_1_bss_9D1C[i].unk02C == 0) ? -1 : k;
                        if (lbl_1_bss_9D1C[i].unk02C == 1) {
                            lbl_1_data_D0[k] = i + 10000;
                        }
                        lbl_1_bss_9D1C[i].unk037 = 0;
                        lbl_1_bss_9D1C[i].unk93C = 255;
                        lbl_1_data_12C[big] = (big == 0) ? rand8() % 3 + 1 : rand8() % 5 + 5;
                        if (lbl_1_bss_9D1C[i].unk036 >= 0) {
                            s32 mdl6 = (lbl_1_bss_9D1C[i].unk02C == 0) ? 12 : lbl_1_bss_9D1C[i].unk036 + 18;

                            if (lbl_1_bss_9D1C[i].unk02E == 1) {
                                Hu3DModelAttrReset(obj->mdlId[mdl6], 0x40000001);
                            } else {
                                Hu3DModelAttrSet(obj->mdlId[mdl6], 0x40000001);
                            }
                            Hu3DMotionSet(obj->mdlId[mdl6], obj->mtnId[lbl_1_bss_9D1C[i].unk02C + motOfs[lbl_1_bss_9D1C[i].unk02E]]);
                            Hu3DMotionTimeSet(obj->mdlId[mdl6], lbl_1_bss_9D1C[i].unk030 / 16);
                            Hu3DMotionSpeedSet(obj->mdlId[mdl6], lbl_1_bss_9D1C[i].unk032 / 256.0f);
                        }
                    }
                }
            }
        }
        if (v184 != 0 && lbl_1_data_88[0] == -1) {
            lbl_1_data_88[0] = HuAudFXPlay(0x662);
        } else if (v184 == 0 && lbl_1_data_88[0] != -1) {
            HuAudFXStop(lbl_1_data_88[0]);
        }
    }
}


/* 433 insns: Hu3DHookFuncCreate hook (ObjectSetup/FADC 0xFD50). Copies the EFB
 * around each player's model into its texture buffer. */
void fn_1_B694(HU3DMODEL *modelP, Mtx *mtx)
{
    HuVecF pos2d;
    HuVecF pos;
    GXColor clear = { 0x40, 0x40, 0x40, 0x40 };
    s32 srcW;
    s32 srcH;
    s32 i;
    HU3DMODEL *model;
    s32 x;
    s32 y;
    u8 *buf;
    s32 texW;
    s32 texH;

    if (!WipeCheckEnd()) {
        if (lbl_1_data_119[0] == 2) {
            fn_1_BD58(modelP, mtx);
        } else {
            GXSetCopyFilter(GX_FALSE, RenderMode->sample_pattern, GX_FALSE, RenderMode->vfilter);
            GXPixModeSync();
            GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
            for (i = 0; i < ((lbl_1_data_119[0] == 4) ? 1 : 4); i++) {
                if (lbl_1_data_111[i] == -1) {
                    continue;
                }
                if (lbl_1_data_111[i] >= ((i == 0) ? 4 : 1)) {
                    continue;
                }
                if (!((lbl_1_data_119[0] == 0) ? 1 : ((lbl_1_data_119[0] == 1) ? (i == 1) : 0))) {
                    continue;
                }
                model = &Hu3DData[lbl_1_bss_2ED34->mdlId[i + 13]];
                buf = (i != 1 || lbl_1_data_119[0] == 1)
                    ? lbl_1_bss_11AC[i][lbl_1_data_111[i]] + lbl_1_data_115[i] * lbl_1_bss_11EC[i]
                    : lbl_1_bss_119C[i];
                srcW = (i == 0) ? 32 : (i == 1) ? 40 : (i == 2) ? 20 : 12;
                srcH = (i == 0) ? 28 : (i == 1) ? 34 : (i == 2) ? 20 : 12;
                texW = (i == 0) ? 56 : (i == 1) ? 80 : (i == 2) ? 40 : 24;
                texH = (i == 0) ? 60 : (i == 1) ? 68 : (i == 2) ? 40 : 24;
                pos.x = model->pos.x;
                pos.y = model->pos.y + ((i == 0) ? 55.0f : (i == 1) ? -90.0f : 0.0f);
                pos.z = model->pos.z;
                Hu3D3Dto2D(&pos, 1, &pos2d);
                pos2d.x = 320.0f + 640.0f * ((pos2d.x - 288.0f) / 576.0f);
                pos2d.y = 240.0f + 480.0f * ((pos2d.y - 240.0f) / 480.0f);
                x = pos2d.x - srcW;
                y = pos2d.y - srcH;
                x = ((x + 1) / 2) * 2;
                y = ((y + 1) / 2) * 2;
                GXSetTexCopySrc(x, y, texW, texH);
                GXSetTexCopyDst(texW, texH, GX_TF_RGB5A3, GX_FALSE);
                GXSetCopyClear(clear, 0xFFFFFF);
                GXCopyTex(buf, GX_TRUE);
                DCFlushRange(buf, lbl_1_bss_11EC[i]);
                GXPixModeSync();
            }
            GXSetCopyFilter(RenderMode->aa, RenderMode->sample_pattern, GX_TRUE, RenderMode->vfilter);
            {
                GXColor clear2 = { 0, 0, 0, 0 };
                GXSetCopyClear(clear2, 0xFFFFFF);
            }
        }
    }
}

/* 217 insns: called only from fn_1_B694 when data_119 == 2; the arguments are unused. */
void fn_1_BD58(HU3DMODEL *modelP, Mtx *mtx)
{
    GXColor clear = { 0x40, 0x40, 0x40, 0x40 };
    HuVecF pos2d;
    s32 i;
    HU3DMODEL *model;
    s32 x;
    s32 y;
    u8 *buf;

    GXPixModeSync();
    for (i = 0; i < 1; i++) {
        if (lbl_1_data_111[i] == -1) {
            continue;
        }
        if (lbl_1_data_111[i] >= 4) {
            continue;
        }
        model = &Hu3DData[lbl_1_bss_2ED34->mdlId[i + 13]];
        {
            HuVecF pos = { 0.0f, 55.0f, 0.0f };
            buf = lbl_1_bss_1158[i][lbl_1_data_111[i]] + lbl_1_bss_1198 * lbl_1_data_115[i];
            pos.x += model->pos.x;
            pos.y += model->pos.y;
            pos.z += model->pos.z;
            Hu3D3Dto2D(&pos, 1, &pos2d);
        }
        pos2d.x = 320.0f + 640.0f * ((pos2d.x - 288.0f) / 576.0f);
        pos2d.y = 240.0f + 480.0f * ((pos2d.y - 240.0f) / 480.0f);
        x = pos2d.x - 26.0f;
        y = pos2d.y - 22.0f;
        x = ((x + 1) / 2) * 2;
        y = ((y + 1) / 2) * 2;
        GXSetTexCopySrc(x, y, 52, 44);
        GXSetTexCopyDst(26, 22, GX_TF_I8, GX_TRUE);
        GXSetCopyClear(clear, 0xFFFFFF);
        GXCopyTex(buf, GX_TRUE);
        DCFlushRange(buf, lbl_1_bss_11EC[i]);
        GXPixModeSync();
    }
    {
        GXColor clear2 = { 0, 0, 0, 0 };
        GXSetCopyClear(clear2, 0xFFFFFF);
    }
}

/* 1609 insns: Hu3DHookFuncCreate hook. Three passes in camera-facing space:
 * the dust particles (bss_1F7C, two texture passes), the hazards' shadow
 * quads textured from bss_1158, and the hazards' full-size quads textured
 * from bss_11AC (only once unk93C has reached 255). */
void fn_1_C0BC(HU3DMODEL *modelP, Mtx *mtx)
{
    Mtx lookAt;
    Mtx lookAtInv;
    HuVecF basis[4] = { { -1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f } };
    HuVecF basisCam[4];
    Mtx mtxA;
    Mtx mtxB;
    HU3DCAMERA *camera;
    s32 i;
    s32 pass;
    s32 vtxNo;
    s32 uvNo;
    s32 col;
    s32 alpha;
    s32 frame;

    for (i = 0; i < 16; i++) {
        if (modelP->cameraBit & (1 << i)) {
            break;
        }
    }
    camera = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &camera->pos, &camera->up, &camera->target);
    PSMTXTranspose(lookAt, lookAtInv);
    PSMTXMultVecArray(lookAtInv, basis, basisCam, 4);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 128, GX_AOP_AND, GX_GEQUAL, 128);
    GXSetZCompLoc(GX_FALSE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetBlendMode(GX_BM_SUBTRACT, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASA, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    for (pass = 0; pass < 2; pass++) {
        HuSprTexLoad(espanim[esprite[lbl_1_data_0[(pass == 0) ? 0 : 1]].animNo].anim, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        for (i = 0; i < 640; i++) {
            HuVecF vtx[4][4] = {
                { { -1.0f, 0.0f, 2.0f }, { 1.0f, 0.0f, 2.0f }, { 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f } },
                { { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, -2.0f }, { -1.0f, 0.0f, -2.0f } },
                { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
                { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
            };
            float uv[2][4] = { { 0.5f, 0.0f, 1.0f, 0.5f }, { 0.0f, 0.5f, 0.5f, 1.0f } };
            float size = 20.0f;
            float y = -3.0f;
            HuVecF pos = { 0.0f, 55.0f, 0.0f };

            if (lbl_1_bss_1F7C[i].unk02C < 0) {
                continue;
            }
            if (pass == 0 && lbl_1_bss_1F7C[i].unk029 >= 2) {
                continue;
            }
            if (pass == 1 && lbl_1_bss_1F7C[i].unk029 < 2) {
                continue;
            }
            pos.x = lbl_1_bss_1F7C[i].unk000;
            pos.y = y;
            pos.z = lbl_1_bss_1F7C[i].unk008;
            size = (lbl_1_bss_1F7C[i].unk029 != 1) ? 20 : 65;
            alpha = 255 - (lbl_1_bss_1F7C[i].unk02C * 255) / 192;
            col = 0;
            uvNo = vtxNo = lbl_1_bss_1F7C[i].unk028;
            if (0.0f != lbl_1_bss_1F7C[i].unk00C || lbl_1_bss_1F7C[i].unk029 >= 2) {
                HuVecF axis = { 0.0f, 1.0f, 0.0f };
                PSMTXScale(mtxA, lbl_1_bss_1F7C[i].unk024, 1.0f, lbl_1_bss_1F7C[i].unk020);
                PSMTXTrans(mtxB, -lbl_1_bss_1F7C[i].unk01C, 0.0f, -lbl_1_bss_1F7C[i].unk018);
                PSMTXConcat(mtxB, mtxA, mtxA);
                PSMTXTrans(mtxB, 0.0f, 0.0f, -lbl_1_bss_1F7C[i].unk014 * (uvNo * 2 - 1));
                PSMTXConcat(mtxB, mtxA, mtxA);
                PSMTXRotAxisRad(mtxB, &axis, 0.017453292f * lbl_1_bss_1F7C[i].unk00C);
                PSMTXConcat(mtxB, mtxA, mtxA);
                PSMTXRotAxisRad(mtxB, &axis, 0.017453292f * (-lbl_1_bss_1F7C[i].unk010 * (uvNo * 2 - 1)));
                PSMTXConcat(mtxB, mtxA, mtxA);
                PSMTXMultVecArray(mtxA, vtx[vtxNo], vtx[vtxNo + 2], 4);
                vtxNo += 2;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(pos.x + size * vtx[vtxNo][0].x, y, pos.z - size * vtx[vtxNo][0].z);
            GXColor4u8(col, col, 0, alpha);
            GXTexCoord2f32(uv[uvNo][0], uv[uvNo][1]);
            GXPosition3f32(pos.x + size * vtx[vtxNo][1].x, y, pos.z - size * vtx[vtxNo][1].z);
            GXColor4u8(col, col, 0, alpha);
            GXTexCoord2f32(uv[uvNo][2], uv[uvNo][1]);
            GXPosition3f32(pos.x + size * vtx[vtxNo][2].x, y, pos.z - size * vtx[vtxNo][2].z);
            GXColor4u8(col, col, 0, alpha);
            GXTexCoord2f32(uv[uvNo][2], uv[uvNo][3]);
            GXPosition3f32(pos.x + size * vtx[vtxNo][3].x, y, pos.z - size * vtx[vtxNo][3].z);
            GXColor4u8(col, col, 0, alpha);
            GXTexCoord2f32(uv[uvNo][0], uv[uvNo][3]);
        }
        GXPixModeSync();
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_GREATER, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_RASA, GX_CA_TEXA, GX_CA_ZERO);
    for (i = 0; i < 64; i++) {
        HU3DMODEL *model = M505_PC_OK(i + 13 < lbl_1_bss_2ED34->mdlcnt) ? &Hu3DData[lbl_1_bss_2ED34->mdlId[i + 13]] : NULL; /* retail reads mdlId[13..76] of 26 (0xCCFC); unused */
        float size = 26.0f * lbl_1_bss_1154;
        float y = -3.0f;
        s32 shadowAlpha = 127;
        HuVecF pos = { 0.0f, 55.0f, 0.0f };

        pos.x += lbl_1_bss_9D1C[i].unk000;
        pos.z += lbl_1_bss_9D1C[i].unk008;
        if (lbl_1_bss_9D1C[i].unk028 < 0) {
            continue;
        }
        if (lbl_1_bss_9D1C[i].unk036 >= 0) {
            continue;
        }
        frame = lbl_1_bss_9D1C[i].unk030 / 16;
        frame = (lbl_1_bss_9D1C[i].unk02E != 2 || lbl_1_data_119[0] == 3)
            ? frame
            : ((lbl_1_data_119[0] == 2 && lbl_1_data_111[0] == 2) ? ((lbl_1_data_115[0] > frame) ? frame : lbl_1_data_115[0]) : 0);
        GXInitTexObj(&lbl_1_bss_918[i], lbl_1_bss_1158[lbl_1_bss_9D1C[i].unk02C][lbl_1_bss_9D1C[i].unk02E] + lbl_1_bss_1198 * frame, 26, 22, GX_TF_I8,
                     GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&lbl_1_bss_918[i], GX_TEXMAP0);
        GXSetAlphaCompare(GX_GEQUAL, 12.5f * lbl_1_bss_9D1C[i].unk93C / 255.0f, GX_AOP_AND, GX_ALWAYS, 0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(pos.x + basis[0].x * size, y, pos.z - basis[0].y * size);
        GXColor4u8(60, 90, 150, shadowAlpha);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(pos.x + basis[1].x * size, y, pos.z - basis[1].y * size);
        GXColor4u8(60, 90, 150, shadowAlpha);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(pos.x + basis[2].x * size, y, pos.z - basis[2].y * size);
        GXColor4u8(60, 90, 150, shadowAlpha);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(pos.x + basis[3].x * size, y, pos.z - basis[3].y * size);
        GXColor4u8(60, 90, 150, shadowAlpha);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPixModeSync();
    }
    GXSetBlendMode(GX_BM_BLEND, GX_BL_ONE, GX_BL_ZERO, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 192, GX_AOP_AND, GX_GEQUAL, 192);
    GXSetZCompLoc(GX_FALSE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    for (i = 0; i < 64; i++) {
        HU3DMODEL *model = &Hu3DData[lbl_1_bss_2ED34->mdlId[13]];
        HuVecF pos = { 0.0f, 0.0f, 0.0f };

        if (lbl_1_bss_9D1C[i].unk028 < 0) {
            continue;
        }
        if (lbl_1_bss_9D1C[i].unk036 >= 0) {
            continue;
        }
        if (lbl_1_bss_9D1C[i].unk93C < 255) {
            continue;
        }
        pos.x = lbl_1_bss_9D1C[i].unk000;
        pos.y = 55.0f + lbl_1_bss_9D1C[i].unk004;
        pos.z = lbl_1_bss_9D1C[i].unk008;
        GXInitTexObj(&lbl_1_bss_918[i],
                     lbl_1_bss_11AC[lbl_1_bss_9D1C[i].unk02C][lbl_1_bss_9D1C[i].unk02E] + (lbl_1_bss_9D1C[i].unk030 / 16) * lbl_1_bss_11EC[lbl_1_bss_9D1C[i].unk02C],
                     56, 60, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXLoadTexObj(&lbl_1_bss_918[i], GX_TEXMAP0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(pos.x + 32.0f * basisCam[0].x * lbl_1_bss_1154, pos.y + 28.0f * basisCam[0].y * lbl_1_bss_1150, pos.z + 28.0f * basisCam[0].z * lbl_1_bss_1150);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(pos.x + 24.0f * basisCam[1].x * lbl_1_bss_1154, pos.y + 28.0f * basisCam[1].y * lbl_1_bss_1150, pos.z + 28.0f * basisCam[1].z * lbl_1_bss_1150);
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(pos.x + 24.0f * basisCam[2].x * lbl_1_bss_1154, pos.y + 32.0f * basisCam[2].y * lbl_1_bss_1150, pos.z + 32.0f * basisCam[2].z * lbl_1_bss_1150);
        GXColor4u8(255, 255, 255, 0);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(pos.x + 32.0f * basisCam[3].x * lbl_1_bss_1154, pos.y + 32.0f * basisCam[3].y * lbl_1_bss_1150, pos.z + 32.0f * basisCam[3].z * lbl_1_bss_1150);
        GXColor4u8(255, 255, 255, 0);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPixModeSync();
    }
    GXSetZCompLoc(GX_TRUE);
}

/* 1379 insns: Hu3DHookFuncCreate hook. Draws the landing marks (bss_977C)
 * back to front -- an insertion sort by z into a stack-local doubly linked
 * list -- as camera-facing quads textured from bss_11AC[1], then the
 * bss_11FC records as quads textured from bss_11AC[2 + unk01A]. */
void fn_1_D9E0(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 head = -1;
    s32 link[64][2]; /* retail: 64 entries, indexed by all 72 marks -- see OUT.txt */
    Mtx lookAt;
    Mtx lookAtInv;
    HuVecF basis[4] = { { -1.0f, 1.0f, 0.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, -1.0f, 0.0f }, { -1.0f, -1.0f, 0.0f } };
    HuVecF basisCam[4];
    HU3DCAMERA *camera;
    s32 i;
    s32 j;

    for (i = 0; i < 16; i++) {
        if (modelP->cameraBit & (1 << i)) {
            break;
        }
    }
    camera = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &camera->pos, &camera->up, &camera->target);
    PSMTXTranspose(lookAt, lookAtInv);
    PSMTXMultVecArray(lookAtInv, basis, basisCam, 4);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetZCompLoc(GX_TRUE);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
    for (i = 0; i < 72; i++) {
        if (lbl_1_bss_977C[i].unk010 < 0) {
            continue;
        }
        for (j = head;; j = link[j][0]) {
            if (j > -1 && lbl_1_bss_977C[i].unk008 < lbl_1_bss_977C[j].unk008) {
                link[i][0] = j;
                link[i][1] = link[j][1];
                if (link[i][0] != -1) {
                    link[link[i][0]][1] = i;
                }
                if (link[i][1] != -1) {
                    link[link[i][1]][0] = i;
                }
                if (link[i][1] == -1) {
                    head = i;
                }
                break;
            }
            if (head == -1 || link[j][0] == -1) {
                link[i][0] = -1;
                link[i][1] = j;
                if (link[i][1] != -1) {
                    link[link[i][1]][0] = i;
                }
                if (link[i][1] == -1) {
                    head = i;
                }
                break;
            }
        }
    }
    j = head;
    while (j != -1) {
        HuVecF pos = { 0.0f, 0.0f, 0.0f };
        float scale;

        i = j;
        if (lbl_1_bss_977C[i].unk010 < 0) {
            continue;
        }
        pos.x = lbl_1_bss_977C[i].unk000;
        pos.y = -90.0f + lbl_1_bss_977C[i].unk004 - 200.0f;
        pos.z = lbl_1_bss_977C[i].unk008;
        scale = (lbl_1_bss_977C[i].unk00C == 0) ? 1.0 : ((lbl_1_bss_977C[i].unk00C == 1) ? 2.5 : 2.0);
        pos.z += (lbl_1_bss_977C[i].unk00C == 0) ? 0 : ((lbl_1_bss_977C[i].unk00C == 1) ? 0 : 0);
        pos.y += (lbl_1_bss_977C[i].unk00C == 0) ? 200 : ((lbl_1_bss_977C[i].unk00C == 1) ? 310 : 290);
        GXInitTexObj(&lbl_1_bss_18[i], lbl_1_bss_11AC[1][0] + lbl_1_bss_11EC[1] * lbl_1_bss_977C[i].unk010, 80, 68, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP,
                     GX_FALSE);
        GXLoadTexObj(&lbl_1_bss_18[i], GX_TEXMAP0);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(pos.x + scale * (40.0f * basisCam[0].x * lbl_1_bss_1154), pos.y + scale * (34.0f * basisCam[0].y * lbl_1_bss_1150),
                       pos.z + scale * (34.0f * basisCam[0].z * lbl_1_bss_1150));
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(pos.x + scale * (40.0f * basisCam[1].x * lbl_1_bss_1154), pos.y + scale * (34.0f * basisCam[1].y * lbl_1_bss_1150),
                       pos.z + scale * (34.0f * basisCam[1].z * lbl_1_bss_1150));
        GXColor4u8(255, 255, 255, 255);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(pos.x + scale * (40.0f * basisCam[2].x * lbl_1_bss_1154), pos.y + scale * (34.0f * basisCam[2].y * lbl_1_bss_1150),
                       pos.z + scale * (34.0f * basisCam[2].z * lbl_1_bss_1150));
        GXColor4u8(255, 255, 255, 0);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(pos.x + scale * (40.0f * basisCam[3].x * lbl_1_bss_1154), pos.y + scale * (34.0f * basisCam[3].y * lbl_1_bss_1150),
                       pos.z + scale * (34.0f * basisCam[3].z * lbl_1_bss_1150));
        GXColor4u8(255, 255, 255, 0);
        GXTexCoord2f32(0.0f, 1.0f);
        GXPixModeSync();
        j = link[j][0];
    }
    if (lbl_1_bss_2ED2C != 1000 && lbl_1_data_119[0] != 1 && (lbl_1_data_119[0] != 0 || lbl_1_data_111[3] > 0)) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZCompLoc(GX_TRUE);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASA, GX_CC_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        for (i = 0; i < 96; i++) {
            HuVecF pos = { 0.0f, 0.0f, 0.0f };
            float scale = 1.0f;
            s32 texW;
            s32 texH;
            s32 w0;
            s32 w1;
            s32 h0;
            s32 h1;
            s32 alpha;

            if (lbl_1_bss_11FC[i].unk01C < 0) {
                continue;
            }
            if (lbl_1_bss_11FC[i].unk020 >= 0) {
                continue;
            }
            pos.x = lbl_1_bss_11FC[i].unk000;
            pos.y = lbl_1_bss_11FC[i].unk004;
            pos.z = lbl_1_bss_11FC[i].unk008;
            texW = (lbl_1_bss_11FC[i].unk01A == 0) ? 40 : 24;
            texH = (lbl_1_bss_11FC[i].unk01A == 0) ? 40 : 24;
            w0 = (lbl_1_bss_11FC[i].unk01A == 0) ? 20 : 12;
            w1 = (lbl_1_bss_11FC[i].unk01A == 0) ? 20 : 12;
            h0 = (lbl_1_bss_11FC[i].unk01A == 0) ? 20 : 12;
            h1 = (lbl_1_bss_11FC[i].unk01A == 0) ? 20 : 12;
            alpha = lbl_1_bss_11FC[i].unk018;
            GXInitTexObj(&lbl_1_bss_18[i], lbl_1_bss_11AC[lbl_1_bss_11FC[i].unk01A + 2][0] + lbl_1_bss_11FC[i].unk019 * lbl_1_bss_11EC[lbl_1_bss_11FC[i].unk01A + 2],
                         texW, texH, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
            GXLoadTexObj(&lbl_1_bss_18[i], GX_TEXMAP0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(pos.x + scale * (lbl_1_bss_1154 * (basisCam[0].x * w0)), pos.y + scale * (lbl_1_bss_1150 * (basisCam[0].y * h0)),
                           pos.z + scale * (lbl_1_bss_1150 * (basisCam[0].z * h0)));
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(pos.x + scale * (lbl_1_bss_1154 * (basisCam[1].x * w1)), pos.y + scale * (lbl_1_bss_1150 * (basisCam[1].y * h0)),
                           pos.z + scale * (lbl_1_bss_1150 * (basisCam[1].z * h0)));
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(pos.x + scale * (lbl_1_bss_1154 * (basisCam[2].x * w1)), pos.y + scale * (lbl_1_bss_1150 * (basisCam[2].y * h1)),
                           pos.z + scale * (lbl_1_bss_1150 * (basisCam[2].z * h1)));
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(pos.x + scale * (lbl_1_bss_1154 * (basisCam[3].x * w0)), pos.y + scale * (lbl_1_bss_1150 * (basisCam[3].y * h1)),
                           pos.z + scale * (lbl_1_bss_1150 * (basisCam[3].z * h1)));
            GXColor4u8(255, 255, 255, alpha);
            GXTexCoord2f32(0.0f, 1.0f);
            GXPixModeSync();
        }
    }
    GXSetZCompLoc(GX_TRUE);
}

/* 732 insns: main mode driver, installed as the objFunc of the fn_1_119A0 object
 * (0x119D4). Also drains the bss_2ED50 sound-effect requests every frame. */
void fn_1_EF6C(OMOBJ *obj)
{
    s32 i;
    s32 pan;
    s32 winCnt;
    s32 outNum;
    s32 seNo;
    M505_PWORK *work[4];

    for (i = 0; i < 4; i++) {
        work[i] = lbl_1_bss_2ED38[i]->data;
    }
    for (i = 0; i < 11; i++) {
        s32 seTbl[11] = { 0x660, 0x661, 0x662, 0x663, 0x664, 0x665, 0x663, 0x667, 0x668, 0x669, 0x66A };
        if (lbl_1_bss_2ED50[i].unk000 > 3) {
            lbl_1_bss_2ED50[i].unk000 = 3;
        }
        if (lbl_1_bss_2ED50[i].unk000 > 0) {
            if (seTbl[i] != -1) {
                seNo = HuAudFXPlay(seTbl[i]);
                lbl_1_bss_2ED50[i].unk01C = seNo;
                if (lbl_1_bss_2ED50[i].unk010[lbl_1_bss_2ED50[i].unk000 - 1]) {
                    pan = (s16)(0.5 + (64.0f + 32.0f * ((lbl_1_bss_2ED50[i].unk004[lbl_1_bss_2ED50[i].unk000 - 1] - CenterM[1].x) / 700.0f)));
                    pan = (pan >= 96) ? 96 : pan;
                    HuAudFXPanning(seNo, pan);
                }
                lbl_1_bss_2ED50[i].unk010[lbl_1_bss_2ED50[i].unk000 - 1] = 0;
            }
            lbl_1_bss_2ED50[i].unk000--;
        }
    }
    if (omSysExitReq && !WipeCheckEnd() && !lbl_1_bss_8[0]) {
        lbl_1_bss_8[0] = 1;
        HuAudFadeOut(1000);
    }
    switch (lbl_1_bss_2ED2C) {
        case 1000:
            lbl_1_bss_0 += 1.0f;
            if (2.0f == lbl_1_bss_0) {
                lbl_1_data_84[0] = HuAudFXPlay(0x39F);
            }
            if (!WipeCheckEnd()) {
                lbl_1_bss_2ED2C++;
                lbl_1_bss_0 = 0.0f;
            }
            break;
        case 1001:
            lbl_1_bss_0 += (lbl_1_bss_9D1C[0].unk028 == -1);
            if (lbl_1_bss_0 >= 50.0f) {
                lbl_1_bss_2ED2C++;
                lbl_1_bss_0 = 0.0f;
            }
            break;
        case 1002:
            lbl_1_bss_0 += 1.0f;
            if (5.0f == lbl_1_bss_0 && lbl_1_bss_2ED26 < 0) {
                lbl_1_bss_2ED26 = GameMesMgStartCreate();
            }
            if (lbl_1_bss_0 >= 5.0f && lbl_1_data_80[0] == -1) {
                lbl_1_data_80[0] = HuAudSStreamPlay(55);
            }
            if (lbl_1_bss_0 >= 5.0f && !GameMesStatGet(lbl_1_bss_2ED26) && lbl_1_bss_2ED26 >= 0) {
                lbl_1_bss_2ED2C++;
                lbl_1_bss_2ED20 = 1800;
                lbl_1_bss_2ED24 = GameMesTimerCreate(lbl_1_bss_2ED20 / 60);
                GameMesPosSet(lbl_1_bss_2ED24, 525.0f, 64.0f);
                lbl_1_bss_2ED26 = -1;
                lbl_1_bss_0 = 0.0f;
                for (i = 0; i < 4; i++) {
                    work[i]->unk024 = 1;
                }
            }
            break;
        case 1003:
            lbl_1_bss_0 += 1.0f;
            GameMesTimerValueSet(lbl_1_bss_2ED24, (lbl_1_bss_2ED20 + 58) / 60);
            lbl_1_bss_2ED20--;
            outNum = 0;
            for (i = 0; i < 4; i++) {
                outNum += (work[i]->unk024 != 2);
            }
            if (lbl_1_bss_2ED20 <= 0 || outNum <= 1) {
                lbl_1_bss_2ED2C = 1004;
                lbl_1_bss_0 = 0.0f;
            }
            break;
        case 1004:
            if (10.0f == lbl_1_bss_0) {
                lbl_1_data_78[0] = 4;
                for (i = 0; i < 4; i++) {
                    lbl_1_data_78[0] = (work[i]->unk024 != 2) ? i : lbl_1_data_78[0];
                    work[i]->unk024 = (work[i]->unk024 == 1) ? 3 : work[i]->unk024;
                }
            }
            if (lbl_1_bss_2ED26 < 0 && 0.0f == lbl_1_bss_0) {
                GameMesTimerEnd(lbl_1_bss_2ED24);
                lbl_1_bss_2ED26 = GameMesMgFinishCreate();
                if (lbl_1_data_80[0] != -1) {
                    HuAudSStreamFadeOut(lbl_1_data_80[0], 100);
                }
            } else if (!GameMesStatGet(lbl_1_bss_2ED26) && lbl_1_bss_0 >= 90.0f) {
                winCnt = 0;
                {
                    s32 winChar[4] = { -1, -1, -1, -1 };
                    lbl_1_bss_2ED2C++;
                    lbl_1_bss_0 = 0.0f;
                    for (i = 0; i < 4; i++) {
                        if (work[i]->unk024 != 2) {
                            winChar[winCnt] = work[i]->unk00C;
                            GWMgCoinBonusSet(work[i]->unk004, 10);
                            winCnt++;
                        }
                    }
                    if (winCnt > 0) {
                        lbl_1_bss_2ED26 = GameMesMgWinnerCreate(winChar[0], winChar[1], winChar[2], winChar[3]);
                        HuAudSStreamPlay(121);
                    } else {
                        lbl_1_bss_2ED26 = GameMesMgDrawCreate();
                        HuAudSStreamPlay(123);
                    }
                }
            }
            lbl_1_bss_0 += 1.0f;
            break;
        case 1005:
            lbl_1_bss_0 += 1.0f;
            if (210.0f < lbl_1_bss_0 && !lbl_1_bss_8[0]) {
                lbl_1_bss_8[0] = 1;
                HuAudFXFadeOut(lbl_1_data_84[0], 1000);
                lbl_1_bss_2ED26 = -1;
            }
            break;
        default:
            OSReport(lbl_1_data_134, lbl_1_bss_2ED2C);
            break;
    }
}

/* 1757 insns -- stage object (omAddObjEx in ObjectSetup, 26 models, 8 motions):
 * creates the stage models and the four Hu3DHookFuncCreate hooks, allocates the
 * texture-capture buffers and initialises the record arrays; then runs as
 * fn_1_4FB4. */
/* No symbol of its own: inlined at its three uses in fn_1_FADC (the bss_11FC
 * init). Needed to match: it is what reserves fn_1_FADC's f26..f28 (saved but
 * never visibly used in the reference) and removes the `mr` after each rand8. */
static inline float fn_1_randf(void)
{
    return rand8() / 255.0f;
}

void fn_1_FADC(OMOBJ *obj)
{
    Mtx lookAt;
    Mtx view;
    Mtx scale;
    HuVecF waterMin = { -1250.0f, -200.0f, -1550.0f };
    HuVecF waterMax = { 1900.0f, -200.0f, 1000.0f };
    HU3DCAMERA *cam;
    int i;
    int j;
    int k;
    s32 w;
    s32 h;

    Hu3DWaterCreate(1, HU3D_WATER_ANIM_NONE, HU3D_WATER_ANIM_NONE, HU3D_WATER_ANIM_NONE, FALSE, &waterMin, &waterMax);
    Hu3DWaterCameraSet(2);
    Hu3DWaterTexScaleSet(2.4f, 0.9f, 1.0f);
    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(0x3F0000, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[0], 0);
    Hu3DModelCameraSet(obj->mdlId[0], 2);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(obj->mdlId[0]);
    obj->mdlId[1] = Hu3DModelCreateData(0x3F0001);
    Hu3DModelLayerSet(obj->mdlId[1], 0);
    Hu3DModelCameraSet(obj->mdlId[1], 2);
    Hu3DModelShadowMapSet(obj->mdlId[1]);
    obj->mdlId[2] = Hu3DModelCreateData(0x3F0002);
    Hu3DModelLayerSet(obj->mdlId[2], 2);
    Hu3DModelCameraSet(obj->mdlId[2], 2);
    Hu3DModelAttrSet(obj->mdlId[2], HU3D_MOTATTR_PAUSE);
    obj->mdlId[3] = Hu3DHookFuncCreate(fn_1_0);
    Hu3DModelLayerSet(obj->mdlId[3], 0);
    Hu3DModelCameraSet(obj->mdlId[3], 1);
    Hu3DModelRotSet(obj->mdlId[3], 255.0f, 255.0f, 255.0f);
    obj->mdlId[4] = Hu3DHookFuncCreate(fn_1_B694);
    Hu3DModelLayerSet(obj->mdlId[4], 4);
    Hu3DModelCameraSet(obj->mdlId[4], 1);
    obj->mdlId[5] = Hu3DHookFuncCreate(fn_1_C0BC);
    Hu3DModelLayerSet(obj->mdlId[5], 0);
    Hu3DModelCameraSet(obj->mdlId[5], 2);
    Hu3DModelAttrSet(obj->mdlId[5], HU3D_ATTR_DISPOFF);
    obj->mdlId[7] = Hu3DHookFuncCreate(fn_1_D9E0);
    Hu3DModelLayerSet(obj->mdlId[7], 3);
    Hu3DModelCameraSet(obj->mdlId[7], 2);
    Hu3DModelAttrSet(obj->mdlId[7], HU3D_ATTR_DISPOFF);
    obj->mdlId[14] = Hu3DModelCreateData(0x3F0007);
    Hu3DModelLayerSet(obj->mdlId[14], 0);
    Hu3DModelCameraSet(obj->mdlId[14], 1);
    Hu3DModelAttrSet(obj->mdlId[14], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[14], HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(obj->mdlId[14], -600.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(obj->mdlId[14], 0.5f, 0.5f, 0.5f);
    for (i = 0; i < 2; i++) {
        obj->mdlId[i + 15] = Hu3DModelCreate(HuDataSelHeapReadNum((i == 0) ? 0x3F0003 : 0x3F0004, HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelLayerSet(obj->mdlId[i + 15], 0);
        Hu3DModelCameraSet(obj->mdlId[i + 15], 1);
        Hu3DModelAttrSet(obj->mdlId[i + 15], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->mdlId[i + 15], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(obj->mdlId[i + 15], 100.0f, ((i == 0) ? -1 : 1) * -100, ((i == 0) ? -1 : 1) * 100);
        Hu3DModelRotSet(obj->mdlId[i + 15], -63.0f, 0.0f, 0.0f);
    }
    for (i = 0; i < 4; i++) {
        obj->mdlId[i + 8] = Hu3DModelCreate(HuDataSelHeapReadNum((i < 3) ? 0x3F0003 : 0x3F0004, HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelLayerSet(obj->mdlId[i + 8], 3);
        Hu3DModelCameraSet(obj->mdlId[i + 8], 2);
        Hu3DModelAttrSet(obj->mdlId[i + 8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(obj->mdlId[i + 8], HU3D_MOTATTR_LOOP);
    }
    obj->mdlId[12] = Hu3DModelCreateData(0x3F000E);
    Hu3DModelLayerSet(obj->mdlId[12], 1);
    Hu3DModelCameraSet(obj->mdlId[12], 2);
    Hu3DModelAttrSet(obj->mdlId[12], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(obj->mdlId[12], 1300.0f, 0.0f, -400.0f);
    Hu3DModelShadowSet(obj->mdlId[12]);
    for (i = 0; i < 2; i++) {
        s32 mdlNo = (i == 0) ? 13 : 17;
        float dirTbl[2] = { -1.0f, 1.0f };
        float zeroTbl[2] = { 0.0f, 0.0f };
        s32 mdlTbl[2] = { 0x3F000E, 0x3F0008 };
        s32 mot0Tbl[2] = { 0x3F0010, 0x3F000A };
        s32 mot1Tbl[2] = { 0x3F0012, 0x3F000C };
        s32 mot2Tbl[2] = { 0x3F000F, 0x3F0009 };
        s32 mot3Tbl[2] = { 0x3F0011, 0x3F000B };

        obj->mdlId[mdlNo] = Hu3DModelCreate(HuDataSelHeapReadNum(mdlTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        obj->mtnId[i] = Hu3DJointMotion(obj->mdlId[mdlNo], HuDataSelHeapReadNum(mot0Tbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        obj->mtnId[i + 2] = Hu3DJointMotion(obj->mdlId[mdlNo], HuDataSelHeapReadNum(mot1Tbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        obj->mtnId[i + 4] = Hu3DJointMotion(obj->mdlId[mdlNo], HuDataSelHeapReadNum(mot2Tbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        obj->mtnId[i + 6] = Hu3DJointMotion(obj->mdlId[mdlNo], HuDataSelHeapReadNum(mot3Tbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        {
        HuVecF posOfs[2] = { { -1.0f, 0.0f, 0.0f }, { 3.0f, 0.0f, 0.0f } };
        HuVecF pos[2];

        for (k = 0; k < 16; k++) {
            if ((1 << k) & 1) {
                break;
            }
        }
        cam = &Hu3DCamera[k];
        C_MTXLookAt(lookAt, &cam->pos, &cam->up, &cam->target);
        PSMTXTranspose(lookAt, view);
        PSMTXScale(scale, 150.0f, 150.0f, 150.0f);
        PSMTXConcat(scale, view, view);
        PSMTXMultVecArray(view, posOfs, pos, 4); /* retail: 4 vectors through 2-element arrays */
        Hu3DModelPosSet(obj->mdlId[mdlNo], pos[i].x, pos[i].y, pos[i].z);
        Hu3DModelRotSet(obj->mdlId[mdlNo], 0.0f, 270.0f, 0.0f);
        Hu3DMotionSet(obj->mdlId[mdlNo], obj->mtnId[i]);
        Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(obj->mdlId[mdlNo], 1);
        Hu3DModelCameraSet(obj->mdlId[mdlNo], 1);
        Hu3DModelAttrSet(obj->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
        if (i == 1) {
            for (j = 0; j < 8; j++) {
                obj->mdlId[j + 18] = Hu3DModelCreate(HuDataSelHeapReadNum(mdlTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelRotSet(obj->mdlId[j + 18], 0.0f, 270.0f, 0.0f);
                Hu3DMotionSet(obj->mdlId[j + 18], obj->mtnId[i]);
                Hu3DModelAttrSet(obj->mdlId[j + 18], HU3D_MOTATTR_LOOP);
                Hu3DModelLayerSet(obj->mdlId[j + 18], 1);
                Hu3DModelCameraSet(obj->mdlId[j + 18], 1);
                Hu3DModelShadowSet(obj->mdlId[j + 18]);
                Hu3DModelAttrSet(obj->mdlId[j + 18], HU3D_ATTR_DISPOFF);
            }
        }
        }
    }
    for (i = 0; i < 4; i++) {
        w = (i == 0) ? 56 : ((i == 1) ? 80 : ((i == 2) ? 40 : 24));
        h = (i == 0) ? 60 : ((i == 1) ? 68 : ((i == 2) ? 40 : 24));
        lbl_1_bss_11EC[i] = GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0);
        if (i == 0) {
            lbl_1_bss_1198 = GXGetTexBufferSize(26, 22, GX_TF_I8, GX_FALSE, 0);
        }
        for (j = 0; j < ((i == 0) ? 4 : 1); j++) {
            s32 motTbl[4] = { 0, 2, 4, 6 };

            if (i == 0) {
                lbl_1_data_F0[i][j] = (s32)Hu3DMotionMotionMaxTimeGet(obj->mtnId[i + motTbl[j]]) + 1;
                if (j == 3) {
                    lbl_1_data_F0[i][j] *= 2;
                }
            } else {
                lbl_1_data_F0[i][j] = (s32)Hu3DMotionMaxTimeGet(obj->mdlId[i + 13]) + 1;
            }
            if (i < 4) {
                lbl_1_bss_11AC[i][j] = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_11EC[i] * lbl_1_data_F0[i][j], HU_MEMNUM_OVL);
                if (i == 0) {
                    lbl_1_bss_1158[i][j] = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_1198 * lbl_1_data_F0[i][j], HU_MEMNUM_OVL);
                }
            }
        }
        if (i == 1) {
            lbl_1_bss_119C[i] = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_11EC[i], HU_MEMNUM_OVL);
        }
    }
    for (i = 0; i < 2; i++) {
        s32 espTbl[2] = { 0x3F0005, 0x3F0006 };

        lbl_1_data_0[i] = espEntry(espTbl[i], 0, 0);
        espDispOff(lbl_1_data_0[i]);
    }
    for (i = 0; i < 64; i++) {
        lbl_1_bss_9D1C[i].unk028 = -1;
        lbl_1_bss_9D1C[i].unk02D = rand8();
        lbl_1_bss_9D1C[i].unk02C = 0;
        lbl_1_bss_9D1C[i].unk000 = 1000.0 + 1600.0 * (rand8() / 255.0);
        lbl_1_bss_9D1C[i].unk004 = 0.0f;
        lbl_1_bss_9D1C[i].unk008 = (rand8() % 12) * 100 - 550;
        lbl_1_bss_9D1C[i].unk024 = 0.0f;
        lbl_1_bss_9D1C[i].unk00C = (lbl_1_bss_9D1C[i].unk02C == 0) ? ((-400.0 + 200.0 * (rand8() / 255.0 - 0.75)) / 60.0)
                                                                    : ((-600.0 + 200.0 * (rand8() / 255.0 - 0.5)) / 60.0);
        lbl_1_bss_9D1C[i].unk010 = 0.0f;
        lbl_1_bss_9D1C[i].unk014 = 0.0f;
        lbl_1_bss_9D1C[i].unk036 = -1;
        lbl_1_bss_9D1C[i].unk02E = 0;
        /* retail: lbl_1_data_F0[i] for i up to 63 reads far past the 6-row table */
        lbl_1_bss_9D1C[i].unk030 = lbl_1_bss_9D1C[i].unk034 = ((i == 1) ? 2 : 1) * (((M505_PC_OK(i < 6) ? lbl_1_data_F0[i][0] : 0) * 16 * rand8()) / 255);
        lbl_1_bss_9D1C[i].unk032 = (lbl_1_bss_9D1C[i].unk02C == 0) ? (256.0f * (2.0f * ((60.0f * -lbl_1_bss_9D1C[i].unk00C) / 350.0f)))
                                                                    : (256.0f * ((60.0f * -lbl_1_bss_9D1C[i].unk00C) / 500.0f));
        lbl_1_bss_9D1C[i].unk037 = 0;
        if (i == 0) {
            lbl_1_bss_9D1C[i].unk028 = 0;
            lbl_1_bss_9D1C[i].unk000 = 1300.0f;
            lbl_1_bss_9D1C[i].unk008 = -370.0f;
            lbl_1_bss_9D1C[i].unk024 = -90.0f;
            lbl_1_bss_9D1C[i].unk00C = -9.166667f;
            lbl_1_bss_9D1C[i].unk036 = 0;
            lbl_1_bss_9D1C[i].unk030 = 240;
            lbl_1_bss_9D1C[i].unk032 = 0;
        }
        lbl_1_bss_9D1C[i].unk018 = lbl_1_bss_9D1C[i].unk000;
        lbl_1_bss_9D1C[i].unk01C = lbl_1_bss_9D1C[i].unk004;
        lbl_1_bss_9D1C[i].unk020 = lbl_1_bss_9D1C[i].unk008;
        lbl_1_bss_9D1C[i].unk038 = 0;
        for (j = 0; j < 96; j++) {
            lbl_1_bss_9D1C[i].unk03C[j].unk015 = 0;
        }
        lbl_1_bss_9D1C[i].unk93C = 255;
    }
    memset(lbl_1_bss_977C, 0, sizeof(lbl_1_bss_977C));
    for (i = 0; i < 72; i++) {
        lbl_1_bss_977C[i].unk010 = -1;
    }
    memset(lbl_1_bss_1F7C, 0, sizeof(lbl_1_bss_1F7C));
    for (i = 0; i < 640; i++) {
        lbl_1_bss_1F7C[i].unk02C = -1;
    }
    memset(lbl_1_bss_11FC, 0, sizeof(lbl_1_bss_11FC));
    for (i = 0; i < 96; i++) {
        lbl_1_bss_11FC[i].unk01C = -1;
    }
    j = rand8() % 5;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_11FC[i].unk01C = 0;
        lbl_1_bss_11FC[i].unk000 = (j * 450) + 0.0f * (450.0f * fn_1_randf()) - 900.0f;
        lbl_1_bss_11FC[i].unk004 = 0 * ((rand8() * 3) / 2) + 1400;
        if (j == 4) {
            lbl_1_bss_11FC[i].unk000 += rand8() + 350;
            lbl_1_bss_11FC[i].unk004 -= 500.0f;
        }
        lbl_1_bss_11FC[i].unk008 = 1800.0f * fn_1_randf() - 900.0f;
        lbl_1_bss_11FC[i].unk008 = (lbl_1_bss_11FC[i].unk008 < 0.0f) ? -lbl_1_bss_11FC[i].unk008 : lbl_1_bss_11FC[i].unk008;
        lbl_1_bss_11FC[i].unk00C = 0.0f;
        lbl_1_bss_11FC[i].unk010 = (rand8() % 2) * 2 - 1;
        lbl_1_bss_11FC[i].unk014 = -3.5f;
        lbl_1_bss_11FC[i].unk004 -= 30.0f * lbl_1_bss_11FC[i].unk014;
        lbl_1_bss_11FC[i].unk018 = 0;
        lbl_1_bss_11FC[i].unk01A = (i < 3) ? 0 : 1;
        lbl_1_bss_11FC[i].unk019 = lbl_1_data_F0[lbl_1_bss_11FC[i].unk01A + 2][0] * fn_1_randf();
        lbl_1_bss_11FC[i].unk020 = i;
        j = (j + 1) % 5;
    }
    obj->objFunc = fn_1_4FB4;
}

/* 212 insns -- player object init (omAddObjEx in ObjectSetup 0x11F70) */
void fn_1_11650(OMOBJ *obj)
{
    M505_PWORK *work;
    int padList[4] = { 0, 1, 2, 3 };
    int n;
    int i;
    int j;

    n = 0;
    work = obj->data;
    memset(work, 0, sizeof(M505_PWORK));
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
    work->unk024 = 0;
    work->unk050 = work->unk054 = 0;
    work->unk058 = 0;
    work->unk05C = rand8() % 64;
    obj->mdlId[0] = CharModelCreate(work->unk00C, 8);
    Hu3DModelLayerSet(obj->mdlId[0], 1);
    Hu3DModelCameraSet(obj->mdlId[0], 2);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelShadowSet(obj->mdlId[0]);
    work->unk01C = 0;
    work->unk020 = -1;
    for (i = 0; i < 6; i++) {
        obj->mtnId[i] = CharMotionCreate(work->unk00C, lbl_1_data_3C[i]);
    }
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    obj->trans.x = lbl_1_data_90[work->unk000][0];
    obj->trans.y = lbl_1_data_90[work->unk000][1];
    obj->trans.z = lbl_1_data_90[work->unk000][2];
    obj->rot.y = lbl_1_data_90[work->unk000][3];
    obj->scale.x = obj->scale.y = obj->scale.z = 1.0f;
    obj->rot.x = obj->rot.z = 0.0f;
    obj->objFunc = fn_1_1828;
}

/* 21 insns -- = m566 fn_1_DEAC / m535 fn_1_B700 */
void fn_1_119A0(OMOBJ *obj)
{
    lbl_1_bss_2ED2C = 1000;
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    obj->objFunc = fn_1_EF6C;
}

/* 417 insns */
void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;

    OSReport(lbl_1_data_14F);
    lbl_1_bss_2ED28 = omInitObjMan(600, 0x2000);
    omGameSysInit(lbl_1_bss_2ED28);
    Hu3DCameraCreate(3);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(2, 20.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 0, 0, 640, 480);
    for (i = 0; i < 2; i++) {
        CZoomM[i] = 4300.0f;
        CenterM[i].x = -50.0f;
        CenterM[i].y = -150.0f;
        CenterM[i].z = 0.0f;
        CRotM[i].x = -63.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
    }
    CZoomM[1] = 4000.0f;
    CenterM[1].x = 1800.0f;
    CenterM[1].y = -150.0f;
    CenterM[1].z = 0.0f;
    CRotM[1].x = -40.0f;
    CRotM[1].y = 0.0f;
    CRotM[1].z = 0.0f;
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.0f, -1.0f, -0.5f };
        GXColor lightColor = { 255, 255, 255, 255 };

        lbl_1_bss_2ED1C = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    }
    Hu3DGLightStaticSet(lbl_1_bss_2ED1C, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_2ED1C);
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
        Hu3DShadowCreate(12.0f, 7000.0f, 12000.0f);
        Hu3DShadowTPLvlSet(0.5f);
        Hu3DShadowPosSet(&pos, &up, &target);
        Hu3DShadowColSet(60, 90, 150);
    }
    lbl_1_bss_2ED26 = -1;
    lbl_1_data_78[0] = -1;
    lbl_1_bss_2ED34 = omAddObjEx(lbl_1_bss_2ED28, 101, 26, 8, 1, fn_1_FADC);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_2ED38[i] = omAddObjEx(lbl_1_bss_2ED28, 100, 2, 6, 0, fn_1_11650);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M505_PWORK), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_2ED48 = omAddObjEx(lbl_1_bss_2ED28, 32730, 0, 0, -1, omOutViewMulti);
    lbl_1_bss_2ED48->work[0] = 2;
    lbl_1_bss_2ED4C = omAddObjEx(lbl_1_bss_2ED28, 102, 0, 0, -1, fn_1_119A0);
    lbl_1_bss_2ED30 = omAddObjEx(lbl_1_bss_2ED28, 103, 1, 0, -1, fn_1_12078);
}

/* 22 insns -- = m566 fn_1_E4EC / m535 fn_1_BDC8 */
void fn_1_12078(OMOBJ *obj)
{
    if (lbl_1_bss_8[0] != 0) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        obj->objFunc = fn_1_120D0;
    }
}

/* 46 insns -- = m566 fn_1_E544 / m535 fn_1_BE20 */
void fn_1_120D0(OMOBJ *obj)
{
    M505_PWORK *work;
    int i;

    if (WipeCheckEnd()) {
        return;
    }
    for (i = 0; i < 4; i++) {
        work = lbl_1_bss_2ED38[i]->data;
        CharModelKill(work->unk00C);
    }
    if (lbl_1_bss_2ED26 >= 0) {
        GameMesKill(lbl_1_bss_2ED26);
    }
    GameMesClose();
    HuAudAllStop();
    omOvlReturnEx(lbl_1_data_8C[0], 1);
}

/* fabs (2 insns, .text 0x12188) is libc/math.h's extern inline, emitted out
 * of line (weak) because fn_1_4FB4 is compiled under dont_inline. Do not
 * hand-write it. */

