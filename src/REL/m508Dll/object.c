/*
 * m508dll object.c -- the overlay's second translation unit. It has no code of
 * its own: all 81 of its functions are the shared object library, which this
 * unit and m508.c both #include from objlib.c. The skeleton gen_skel.py
 * produced for it (81 stubs plus lbl_1_bss_220..2D4) is gone, because the
 * library and m526dll/math.c define every one of them.
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

/* This unit is nothing but a second copy of the shared object library: all 81
 * of its functions are objlib.c's. M508_CAMTBL is the camera state table,
 * which is lbl_1_data_B0 here and lbl_1_data_0 in m508.o. */
#define M508_CAMTBL lbl_1_data_B0
#include "REL/m508Dll/objlib.c"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x770 */ /* double lbl_1_rodata_770 = 0; */
/* 0x778 */ /* double lbl_1_rodata_778 = 0.5; */
/* 0x780 */ /* double lbl_1_rodata_780 = 3; */
/* 0x788 */ /* float lbl_1_rodata_788 = 1.0f; */
/* 0x78C */ /* float lbl_1_rodata_78C = 0.0f; */
/* 0x790 */ /* float lbl_1_rodata_790 = -1.0f; */
/* 0x798 */ /* double lbl_1_rodata_798 = 4503601774854144; */
/* 0x7A0 */ /* float lbl_1_rodata_7A0 = 30.0f; */
/* 0x7A4 */ /* float lbl_1_rodata_7A4 = 10.0f; */
/* 0x7A8 */ /* float lbl_1_rodata_7A8 = 8000.0f; */
/* 0x7AC */ /* float lbl_1_rodata_7AC = 1.2f; */
/* 0x7B0 */ /* float lbl_1_rodata_7B0 = 640.0f; */
/* 0x7B4 */ /* float lbl_1_rodata_7B4 = 480.0f; */
/* 0x7B8 */ /* double lbl_1_rodata_7B8 = 3.141592653589793; */
/* 0x7C0 */ /* double lbl_1_rodata_7C0 = 180; */
/* 0x7C8 */ /* float lbl_1_rodata_7C8 = 90.0f; */
/* 0x7CC */ /* float lbl_1_rodata_7CC = 0.1f; */
/* 0x7D0 */ /* float lbl_1_rodata_7D0 = 0.02f; */
/* 0x7D8 */ /* double lbl_1_rodata_7D8 = 4503599627370496; */
/* 0x7E0 */ /* double lbl_1_rodata_7E0 = 360; */
/* 0x7E8 */ /* float lbl_1_rodata_7E8 = 360.0f; */
/* 0x7EC */ /* float lbl_1_rodata_7EC = 180.0f; */

/* --- .data --- */
/* 0xB0 */ void (*lbl_1_data_B0[3])(void *) = { (void (*)(void *))fn_1_8D30, (void (*)(void *))fn_1_926C, (void (*)(void *))fn_1_8C70 };

/* --- .bss --- */
/* This unit's entire .bss (0x220..0x2DC, 0xBC bytes) is math.c's 23
 * function-local statics, which objlib.c's include brings in. The skeleton's
 * lbl_1_bss_220..2D4 stand-ins for them are gone; declaring them as well
 * would emit the storage twice. */

