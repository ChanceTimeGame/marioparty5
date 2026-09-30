/*
 * The types m548.c, game.c and stage.c all need. SKELETON (W1), 2026-09-14.
 *
 * m548dll is a KETTOU duel (overlay #62) on work head B of the duel stage
 * framework, REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table): the
 * head is DS_WORK_HEAD's up to `motId`, then two 0x24 player slots (the first
 * 0x24 bytes of DS_PLAYER), so `stageDataTbl` sits at 0x98 rather than 0xF8.
 * m542dll and m547dll share this head.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated; W2 renames them.
 */
#ifndef M548_H
#define M548_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_154). */
typedef DS_MODEL M548_MODEL;        /* 0x1C */

#define M548_MODEL_MAX 20

/* Who the two duellists are, and their pads (fn_1_6890). */
typedef DS_CHAR M548_CHAR;          /* 0x1C */

/* Head B's player slot: DS_PLAYER without the shift and queued-motion state. */
typedef DS_PLAYERB M548_PLAYER;     /* 0x24 */

/*
 * One stage prop's slot; fn_1_7104, 773C, 7C88, 856C and 8F78 (DS_S_PROPS_B)
 * own one each. effect[0].mode is the arena's state, which every other updater
 * also reads.
 */
typedef DS_PROPB M548_EFFECT;       /* 0x30 */

#define M548_EFFECT_MAX 5

typedef struct M548Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M548_CHAR chr[2];
    /* 0x03C */ M548_MODEL *models;
    /* 0x040 */ unsigned int *charMotData[2];
    /* 0x048 */ HU3DMOTID *motId[2];
    /* 0x050 */ M548_PLAYER player[2];
    /* 0x098 */ unsigned int *stageDataTbl;
    /* 0x09C */ s16 stageNo;
    /* 0x09E */ s16 pad09E;
    /* 0x0A0 */ int mode[4];        /* 0xA0..0xA8 seen; mode[0] likely indexes data_318 */
    /* 0x0B0 */ int unkB0;
    /* 0x0B4 */ int unkB4;
    /* 0x0B8 */ int unkB8;
    /* 0x0BC */ int unkBC;
    /* 0x0C0 */ float unkC0;
    /* 0x0C4 */ float unkC4;
    /* 0x0C8 */ float unkC8;
    /* 0x0CC */ float unkCC;
    /* 0x0D0 */ float unkD0;
    /* 0x0D4 */ float unkD4;
    /* 0x0D8 */ float unkD8;
    /* 0x0DC */ u8 unkDC[0x14];
    /* 0x0F0 */ M548_EFFECT effect[M548_EFFECT_MAX];
} M548_WORK;                        /* 0x1E0 */

/* bss_3B8: fn_1_4F44 fills it, fn_1_4FC4 and fn_1_5098 read it. */
typedef struct M548Unk3B8_s {
    /* 0x00 */ int unk0;
    /* 0x04 */ int unk4;
    /* 0x08 */ int unk8;
    /* 0x0C */ HuVecF vec;
} M548_UNK3B8;                      /* 0x18 */

/* bss_3D0: seven shorts and two float pairs the sequence hooks and game.c share. */
typedef struct M548Unk3D0_s {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;            /* fn_1_15C sets 9 */
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 padE;
    /* 0x10 */ float unk10[2];
    /* 0x18 */ float unk18[2];
} M548_UNK3D0;                      /* 0x20 */

/* m548.c */
extern float lbl_1_data_288[13][2];
extern s32 lbl_1_bss_0[2][4];
extern HuVecF lbl_1_bss_38;
extern HuVecF lbl_1_bss_44;
extern MGTIMER *lbl_1_bss_54;
extern OMCAMERAVIEW lbl_1_bss_58[8];
extern HuVecF lbl_1_bss_384[2][2];      /* two vectors per duellist, copied from data_0 by charNo */
extern s16 lbl_1_bss_3B4;
extern M548_UNK3B8 lbl_1_bss_3B8;
extern M548_UNK3D0 lbl_1_bss_3D0;
extern M548_WORK lbl_1_bss_3F0;
extern s16 lbl_1_bss_5D0;
extern s16 lbl_1_bss_5D2[3];

void fn_1_194C(void);
s32 fn_1_196C(void);

/* game.c */
extern s32 lbl_1_data_398;

void fn_1_1D84(OMOBJ *obj);
void fn_1_202C(void);
void fn_1_23A4(void);
void fn_1_257C(void);
void fn_1_282C(void);
void fn_1_2AD4(void);
void fn_1_309C(void);
void fn_1_3DCC(void);
void fn_1_4F44(void);
void fn_1_5014(s32 dispF);
void fn_1_54C0(void);
void fn_1_59FC(void);
void fn_1_5D84(void);
void fn_1_5DF4(void);

/* stage.c */
void fn_1_6104(M548_WORK *work, M548_MODEL *models, unsigned int *dataTbl);
void fn_1_6350(s16 stageNo);
void fn_1_65E8(unsigned int *dataA, unsigned int *dataB);
void fn_1_660C(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_6630(void);
void fn_1_6890(OMOBJ *obj);
void fn_1_6D4C(void);
void fn_1_6EA0(OMOBJ *obj);
void fn_1_70B0(OMOBJ *obj);

#endif
