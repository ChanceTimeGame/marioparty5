/*
 * The types m547.c, game.c and stage.c all need.
 *
 * m547dll is a KETTOU duel (overlay #61) on work head B of the duel stage
 * framework, REL/duelstage.h, like m542dll and m548dll: the duel head to
 * `motId`, two DS_PLAYERB slots, `stageDataTbl` at 0x98, and m548's five
 * stage props (DS_S_PROPS_B) at 0xF0. The work is 0x210.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M547_H
#define M547_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/score.h"
#include "game/mg/timer.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_E8). */
typedef DS_MODEL M547_MODEL;        /* 0x1C */

#define M547_MODEL_MAX 30

typedef DS_CHAR M547_CHAR;          /* 0x1C */
typedef DS_PLAYERB M547_PLAYER;     /* 0x24 */

typedef struct M547Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M547_CHAR chr[2];
    /* 0x03C */ M547_MODEL *models;
    /* 0x040 */ unsigned int *charMotData[2];
    /* 0x048 */ HU3DMOTID *motId[2];
    /* 0x050 */ M547_PLAYER player[2];
    /* 0x098 */ unsigned int *stageDataTbl;
    /* 0x09C */ s16 stageNo;
    /* 0x09E */ s16 pad09E;
    /* 0x0A0 */ int mode[4];        /* [0] sub-state (data_1F8/200/214), [1] its step, [2] sky scroll stopped, [3] duellists still bobbing (bit per side) */
    /* 0x0B0 */ int count[3];       /* [0] frame timer, [1] and [2] each duellist's presses */
    /* 0x0BC */ int frame;          /* frames since the result began */
    /* 0x0C0 */ HuVecF pos[4];      /* [0] [1] the duellists, [2] [3] their targets; pos[3].z doubles as the rise speed */
    /* 0x0F0 */ DS_PROPB effect[5]; /* DS_S_PROPS_B */
    /* 0x1E0 */ u8 unk1E0[0x30];
} M547_WORK;                        /* 0x210 */

/* m547.c */
extern s16 lbl_1_bss_2;
extern s32 lbl_1_bss_24[4];
extern s32 lbl_1_bss_34;
extern HuVecF lbl_1_bss_38[3];
extern OMCAMERAVIEW lbl_1_bss_78[4];
extern s32 lbl_1_bss_430[4];
extern HuVecF lbl_1_bss_440[2];
extern HuVecF lbl_1_bss_458;
extern HuVecF lbl_1_bss_464;
extern s16 lbl_1_bss_470[8];
extern s16 lbl_1_bss_480[2];
extern OMOBJ *lbl_1_bss_484;
extern M547_WORK lbl_1_bss_488;
extern s32 lbl_1_data_240[2];

void fn_1_21BC(s32 no, float alpha);
void fn_1_2648(s32 no);

/* game.c */
extern HuVecF lbl_1_data_280;
extern HuVecF lbl_1_data_28C;
extern HuVecF lbl_1_data_298;
extern s32 lbl_1_data_2A4[2];
extern s32 lbl_1_bss_6C4[4];
extern s32 lbl_1_bss_6D4[4];

void fn_1_4094(void);
void fn_1_41B0(void);
void fn_1_43A0(void);
void fn_1_47E0(void);
void fn_1_4A94(void);
void fn_1_5894(void);
void fn_1_5DC4(void);
void fn_1_6FF4(void);
void fn_1_750C(void);
void fn_1_7724(void);
void fn_1_7A08(void);
void fn_1_7DAC(void);
void fn_1_7F2C(void);
void fn_1_8298(void);

/* stage.c */
void fn_1_86B8(M547_WORK *work, M547_MODEL *models, unsigned int *dataTbl);
void fn_1_8904(s16 stageNo);
void fn_1_8B9C(unsigned int *dataA, unsigned int *dataB);
void fn_1_8BC0(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_8BE4(void);
void fn_1_8D2C(OMOBJ *obj);
void fn_1_91E8(void);
void fn_1_933C(OMOBJ *obj);
void fn_1_954C(OMOBJ *obj);

#endif
