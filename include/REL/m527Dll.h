#ifndef M527DLL_H
#define M527DLL_H

/*
 * m527Dll (overlay #41): types and prototypes shared by its one translation
 * unit (m527).
 *
 * Offsets are GameCube ones from build/mp5-asm/m527Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/hu3d.h"

/* no SDK header declares rand8 (m502dll.h / m504dll.h do the same); C408
 * uses the result as an int (mulhw on r3 with no clrlwi) */
int rand8(void);

/* Player work: obj->data of the four player objects (ObjectSetup allocates
 * 0x6C with HuMemDirectMallocNum, fn_1_C408 memsets 0x6C and fills it).
 * Fields named by fork A are the ones fn_1_C408 / fn_1_D1F0 write or read;
 * the pads are fields the other forks measure. */
typedef struct M527_PWORK_s {
    /* 0x00 */ s32 unk000; /* player slot 0..3 = obj->work[0]; team = unk000 / 2, partner = unk000 ^ 1 (C408 0xC4C0) */
    /* 0x04 */ s32 unk004; /* player no. (GwPlayer/GwPlayerConf index) from the grp-sorted list (C408 0xC4D4); omVibrate, coin payout */
    /* 0x08 */ s32 unk008; /* charNo clamped to 9 (C408 0xC520) */
    /* 0x0C */ s32 unk00C; /* charNo: CharModelKill (D1F0), CharFXPlay / GameMes winner (A0D0) */
    /* 0x10 */ s32 unk010; /* padNo, -1 for a COM (GwPlayerConf[].type != 0) */
    /* 0x14 */ s32 unk014; /* COM difficulty (0 for a human) */
    /* 0x18 */ s32 unk018; /* current motion slot (B: stw 0x3724, switch 0x2218); 0 in C408; nonzero delays the result timer (E) */
    /* 0x1C */ s32 unk01C; /* forced motion slot, < 0 = none (B 0x3638); -1 in C408 */
    /* 0x20 */ s32 unk020; /* jump-hold frame counter (B 0x28D4) */
    /* 0x24 */ s32 unk024; /* on-ground flag (B 0x2F70, 0x3634) */
    /* 0x28 */ s32 unk028; /* 0/1 (B 0x2988, 0x2AB4) */
    /* 0x2C */ s32 unk02C; /* case-5 counter (B cmpwi 6 0x29DC) */
    /* 0x30 */ s32 unk030; /* player state: 1 in C408; 2 play, 3 finished, 4, 5 result (B switch 0x764; E) */
    /* 0x34 */ s32 unk034; /* frame counter (B ++ 0x75C) */
    /* 0x38 */ s32 unk038; /* score-sprite timer (B stw 30 0x3F6C) */
    /* 0x3C */ float unk03C; /* speed (B 0x24AC) */
    /* 0x40 */ float unk040; /* velocity x (B 0x74C) */
    /* 0x44 */ float unk044; /* velocity y (B 0x2544) */
    /* 0x48 */ float unk048; /* velocity z (B 0x750) */
    /* 0x4C */ s32 unk04C; /* COM state 0..3 (B cmpwi 3 0xF2C); 0 in C408 */
    /* 0x50 */ s32 unk050; /* COM target cell (B 0xBE4) */
    /* 0x54 */ float unk054; /* COM target x (B 0xF40) */
    /* 0x58 */ float unk058; /* COM target z (B 0xF50) */
    /* 0x5C */ s32 unk05C; /* COM timer (B % 75 0x1628) */
    /* 0x60 */ s32 unk060; /* push/stuck counter (B 0xFD8) */
    /* 0x64 */ s32 unk064; /* COM feint flag: dif 0 -> rand8()%10 < 5, dif 1 -> < 3, else 0 (C408 0xC648) */
    /* 0x68 */ s16 unk068; /* HU3DLLIGHTID of mdlId[0] (C408 0xC738; Hu3DLLightColorSet in 4F98) */
    /* 0x6A */ u8 pad06A[2];
} M527_PWORK; /* size 0x6C (GC) */

/* lbl_1_bss_D0[16]: sound-effect requests (fork E, fn_1_A0D0) */
typedef struct M527_SE_s {
    /* 0x00 */ s32 unk000; /* pending count, clamped to 3 (A1C0) */
    /* 0x04 */ float unk004[3]; /* indexed by unk000 (A3B0) */
    /* 0x10 */ s32 unk010; /* last HuAudFXPlay handle (A224) */
} M527_SE; /* size 0x14 (GC) */

/* fork D: esprite.c keeps ESPRITE/ESPANIM file-local, so the overlay redeclares
 * them (m505/m535 precedent). fn_1_7E5C: HuSprTexLoad(espanim[esprite[bss_210]
 * .animNo].anim, ...) -- slwi 2 + lha 2 = animNo, mulli 12 + lwz 8 = anim. */
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


/* --- m527.c --- */
void fn_1_A0(void);
void fn_1_5B4(OMOBJ *obj); /* player objFunc (C408 0xCB44) */
void fn_1_4F98(OMOBJ *obj); /* stage objFunc (B8C4 0xC3E0) */
void fn_1_7E5C(HU3DMODEL *modelP, Mtx *mtx); /* Hu3DHookFuncCreate (B8C4 0xBCA4) */
void fn_1_87F4(HU3DMODEL *modelP, Mtx *mtx); /* Hu3DHookFuncCreate (B8C4 0xBEC0) */
void fn_1_94F4(HU3DMODEL *modelP, Mtx *mtx); /* Hu3DHookFuncCreate (B8C4 0xBD10) */
void fn_1_9FE8(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);
void fn_1_A0D0(OMOBJ *obj); /* mode objFunc (CB68 0xCB9C) */
void fn_1_B8C4(OMOBJ *obj);
void fn_1_C408(OMOBJ *obj);
void fn_1_CB68(OMOBJ *obj);
void ObjectSetup(void);
void fn_1_D198(OMOBJ *obj);
void fn_1_D1F0(OMOBJ *obj);

#endif
