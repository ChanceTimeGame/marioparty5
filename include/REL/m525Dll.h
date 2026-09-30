#ifndef M525DLL_H
#define M525DLL_H

/*
 * m525Dll (overlay #39): types and prototypes shared by its one translation
 * units (m525).
 *
 * Offsets are GameCube ones from build/mp5-asm/m525Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/gamemes.h"
#include "game/wipe.h"

/* Player work: ObjectSetup mallocs 0xC4 per player object (li r4,0xc4 at 0xC32C)
 * and stores it as obj->data; fn_1_B930 memsets it (0xB980). */
typedef struct M525_PLAYER_s {
    /* 0x00 */ s32 unk000; /* player slot = obj->work[0] (0xBA00) */
    /* 0x04 */ s32 unk004; /* GwPlayerConf index (0xBA0C) */
    /* 0x08 */ s32 unk008; /* character clamped to < 9 (0xBA50) */
    /* 0x0C */ s32 unk00C; /* character, GwPlayerConf.charNo (0xBA38) */
    /* 0x10 */ s32 unk010; /* pad no, -1 = COM (0xBA94) */
    /* 0x14 */ s32 unk014; /* COM difficulty (0xBAC4) */
    /* 0x18 */ s32 unk018; /* motion index (0xBC5C) */
    /* 0x1C */ s32 unk01C; /* = -1 (0xBC64) */
    /* 0x20 */ s32 unk020;
    /* 0x24 */ s32 unk024; /* = 1 (0xBAC8) */
    /* 0x28 */ s32 unk028; /* = 2 (0xBAD0) */
    /* 0x2C */ s32 unk02C;
    /* 0x30 */ s32 unk030;
    /* 0x34 */ s32 unk034;
    /* 0x38 */ s32 unk038;
    /* 0x3C */ s32 unk03C;
    /* 0x40 */ s32 unk040; /* = 255 for slot 0 (0xBAF0) */
    /* 0x44 */ s32 unk044;
    /* 0x48 */ s32 unk048;
    /* 0x4C */ float unk04C;
    /* 0x50 */ float unk050;
    /* 0x54 */ s32 unk054;
    /* 0x58 */ s32 unk058;
    /* 0x5C */ s32 unk05C;
    /* 0x60 */ s32 unk060;
    /* 0x64 */ float unk064[3]; /* last x per slot, stfsx 0x64 + 4*i (fn_1_654 0x52A4) */
    /* 0x70 */ float unk070[3]; /* per-slot level, lfsx/stfsx 0x70 + 4*i with the same i (fn_1_654 0x52C4); a [6] from 0x64 costs an addi per access */
    /* 0x7C */ s32 unk07C;
    /* 0x80 */ s32 unk080;
    /* 0x84 */ s32 unk084;
    /* 0x88 */ s32 unk088;
    /* 0x8C */ float unk08C;
    /* 0x90 */ s32 unk090;
    /* 0x94 */ s32 unk094;
    /* 0x98 */ s32 unk098;
    /* 0x9C */ float unk09C;
    /* 0xA0 */ float unk0A0;
    /* 0xA4 */ float unk0A4;
    /* 0xA8 */ float unk0A8;
    /* 0xAC */ s32 unk0AC; /* = 0 (0xBAD8) */
    /* 0xB0 */ s32 unk0B0;
    /* 0xB4 */ s32 unk0B4;
    /* 0xB8 */ s32 unk0B8;
    /* 0xBC */ float unk0BC;
    /* 0xC0 */ s16 unk0C0; /* Hu3DLLightCreate id (sth 0xBBEC) */
    /* 0xC2 */ u8 pad0C2[2];
} M525_PLAYER; /* size 0xC4 (GC) */

/* lbl_1_bss_A4: 10 SE request queues (m535 M535_SE shape; fork D 0x8A04..0x8A7C).
 * Writers (fn_1_654 0x22C8, 0x5138): if (q.unk000 < 3) q.unk004[q.unk000++] = pan; */
typedef struct M525_SE_s {
    /* 0x00 */ s32 unk000; /* queued count (cmpwi 3) */
    /* 0x04 */ float unk004[3]; /* pan per request, stfs 0x4 + 4*count (0x2284) */
    /* 0x10 */ s32 unk010; /* seNo of the last play, -1 = none (fork D) */
} M525_SE; /* size 0x14 (GC) */

/* lbl_1_bss_16C: 256 x 0x30 debris pieces, drawn by fn_1_7C60. */
typedef struct M525_PIECE_s {
    /* 0x00 */ s32 unk000; /* frame counter: angle = 360 * unk000 * unk02C deg (0x7FD4) */
    /* 0x04 */ s32 unk004; /* colour index into fn_1_7C60's [5][3] table (0x81AC) */
    /* 0x08 */ float unk008; /* pos x (0x8180) */
    /* 0x0C */ float unk00C; /* pos y (0x8158) */
    /* 0x10 */ float unk010; /* pos z (0x8130) */
    /* 0x14 */ float unk014;
    /* 0x18 */ float unk018;
    /* 0x1C */ float unk01C;
    /* 0x20 */ HuVecF unk020; /* rotation axis: &piece.unk020 to PSMTXRotAxisRad (0x7FC8) */
    /* 0x2C */ float unk02C; /* spin rate (0x7FF4) */
} M525_PIECE; /* size 0x30 (GC) */

/* lbl_1_bss_316C: 20 x 0x1C blocks (fn_1_654, fn_1_889C, fn_1_A690). */
typedef struct M525_BLOCK_s {
    /* 0x00 */ s32 unk000; /* active; fn_1_889C clears it with mdlId[0x17 + i] DISPOFF */
    /* 0x04 */ float unk004; /* lfs/stfs fn_1_654 (0x1FF0) */
    /* 0x08 */ float unk008; /* (0x2008) */
    /* 0x0C */ float unk00C; /* (0x2098) */
    /* 0x10 */ float unk010; /* (0x20EC) */
    /* 0x14 */ s32 unk014; /* set 1 for all 20 when the team wins (fork D, mode 1005) */
    /* 0x18 */ s16 unk018; /* lha/sth */
    /* 0x1A */ u8 pad01A[2];
} M525_BLOCK; /* size 0x1C (GC) */

/* lbl_1_bss_339C: 0x14, struct-copied whole by fn_1_A690 (0xA9D8). */
typedef struct M525_339C_s {
    /* 0x00 */ float unk000; /* only read by the whole-struct copy (type guessed) */
    /* 0x04 */ float unk004;
    /* 0x08 */ float unk008;
    /* 0x0C */ float unk00C;
    /* 0x10 */ float unk010;
} M525_339C; /* size 0x14 (GC) */


/* esprite.c keeps ESPRITE/ESPANIM file-local, so the overlay redeclares them
 * (m535/m520 spelling). */
typedef struct esprite_s {
    /* 0x00 */ s16 memberNo;
    /* 0x02 */ s16 animNo;
} ESPRITE;

typedef struct espanim_s {
    /* 0x00 */ unsigned int dataNum;
    /* 0x04 */ u16 useCnt;
    /* 0x08 */ ANIMDATA *anim;
} ESPANIM;

extern ESPRITE esprite[];
extern ESPANIM espanim[];

/* sprite.h has this prototype commented out. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

/* no SDK header declares rand8 */
int rand8(void);

/* --- m525.c --- */
void fn_1_A0(void); /* unreferenced debug camera */
void fn_1_654(OMOBJ *obj); /* player objFunc (fn_1_B930 0xBD94) */
float fn_1_5930(float t, float accel, float flat, float decel); /* = m520 fn_1_41F8; inlined into fn_1_5AF4 (0x6238), so it stays above it */
void fn_1_5AF4(OMOBJ *obj); /* stage objFunc (fn_1_A690 0xB8F4) */
void fn_1_7698(HU3DMODEL *model, Mtx *mtx); /* hook (fn_1_A690 0xB6CC) */
void fn_1_7C60(HU3DMODEL *model, Mtx *mtx); /* hook (fn_1_A690 0xB850) */
void fn_1_8394(HU3DMODEL *model, Mtx *mtx); /* hook (fn_1_A690 0xB718, 0xB7A8) */
void fn_1_889C(OMOBJ *obj); /* main mode objFunc (fn_1_BDB4 0xBDEC) */
void fn_1_A690(OMOBJ *obj); /* stage setup objFunc (ObjectSetup 0xC2CC) */
void fn_1_B930(OMOBJ *obj); /* player setup objFunc (ObjectSetup 0xC308) */
void fn_1_BDB4(OMOBJ *obj);
void ObjectSetup(void);
void fn_1_C51C(OMOBJ *obj);
void fn_1_C574(OMOBJ *obj);

#endif
