/*
 * The types m554.c, game.c and stage.c all need.
 *
 * m554dll is a KETTOU duel built on the duel stage framework (REL/duelstage.h),
 * like m550dll. What differs from m550:
 *
 *  - M554_WORK is 0x814 bytes, not 0xA14. The head (0x000..0x110) is the
 *    framework's; 0x110..0x364 is this overlay's own (the race round the
 *    arena, from game.c); the effect slots start at 0x364 and are the
 *    framework's bare 0x3C bytes, twenty of them (m550's are 0x4C).
 *  - The model table has 92 entries, not 183.
 */
#ifndef M554_H
#define M554_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_10C). */
typedef DS_MODEL M554_MODEL;        /* 0x1C */

#define M554_MODEL_MAX 92

/* Who the two duellists are. */
typedef DS_CHAR M554_CHAR;          /* 0x1C */

/* One duellist's requested and applied motion state. */
typedef DS_PLAYER M554_PLAYER;      /* 0x54 */

/* The framework's effect slot, no more. Fields seen: 0x00, 0x04..0x0C, 0x10, 0x2C..0x38. */
typedef DS_EFFECT M554_EFFECT;      /* 0x3C */

#define M554_EFFECT_MAX 20

/* One duellist's pace this frame (fn_1_3578). */
typedef struct M554Pace_s {
    /* 0x00 */ int level;          /* 0..6, from the presses in the last second */
    /* 0x04 */ int step;           /* distance gained this frame */
} M554_PACE;                        /* 0x08 */

/*
 * Where one duellist is on the circle round the arena (-600 on z): dist and
 * angle for the character, dist2 and angle2 for the object knocked off it.
 */
typedef struct M554Run_s {
    /* 0x00 */ float dist;
    /* 0x04 */ float angle;
    /* 0x08 */ float dist2;
    /* 0x0C */ float angle2;
} M554_RUN;                         /* 0x10 */

typedef struct M554Work_s {
    /*
     * 0x000..0x110, the duel framework's head: objman, chr[2], models,
     * charMotData[2], motId[2], player[2], stageDataTbl, stageNo and mode[4].
     *
     * mode[0] indexes m554.c's three hook tables. mode[3] is the result: 0 or
     * 1 the duellist who won the clash, 2 a draw.
     */
    DS_WORK_HEAD;
    /* 0x110 */ int timer[4];      /* timer[i] is duellist i's own clock after the clash */
    /* 0x120 */ int count;         /* half-seconds of the main phase; drives every difficulty table */
    /* 0x124 */ M554_PACE pace[2];
    /* 0x134 */ M554_RUN run[2];
    /*
     * 0x154 -- one flag per frame of the last second, per duellist: 1 where
     * that frame had an alternating L/R press. fn_1_38D4 counts it.
     */
    /* 0x154 */ int press[2][60];
    /* 0x334 */ u8 unk334[0x30];
    /* 0x364 */ M554_EFFECT effect[M554_EFFECT_MAX];
} M554_WORK;                        /* 0x814 */

/* bss_14: one per model 7..13, zeroed by game.c's fn_1_5A5C, run by fn_1_5CCC. */
typedef struct M554Slot_s {
    /* 0x00 */ int mode;
    /* 0x04 */ int wait;
    /* 0x08 */ float maxTime;
} M554_SLOT;                        /* 0x0C */

/* bss_6C: one per duellist, zeroed by game.c's fn_1_3AC8. */
typedef struct M554Com_s {
    /* 0x00 */ s16 level;          /* the duellist's dif, less one */
    /* 0x02 */ s16 pad02;
    /* 0x04 */ int side;           /* which trigger to press next */
    /* 0x08 */ int wait;           /* frames until that press */
} M554_COM;                         /* 0x0C */

/* m554.c */
extern M554_SLOT lbl_1_bss_14[7];
extern M554_COM lbl_1_bss_6C[2];
extern OMCAMERAVIEW lbl_1_bss_98[4];
extern M554_WORK lbl_1_bss_B1C;

void fn_1_A34(void);
s32 fn_1_A54(void);
void fn_1_12A4(int mdlNo, float alpha);

/* game.c */
void fn_1_1F00(void);
void fn_1_2118(void);
void fn_1_22CC(void);
void fn_1_240C(void);
void fn_1_2654(void);
void fn_1_2800(void);
void fn_1_2804(void);
void fn_1_2870(void);
void fn_1_2C74(void);
void fn_1_31C8(void);
void fn_1_53B0(OMOBJ *obj);

/* stage.c */
void fn_1_62F0(M554_WORK *work, M554_MODEL *models, unsigned int *dataTbl);
void fn_1_653C(s16 stageNo);
void fn_1_6C20(unsigned int *dataA, unsigned int *dataB);
void fn_1_6C44(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_6C68(void);
void fn_1_6E80(OMOBJ *obj);
void fn_1_733C(void);
void fn_1_7490(OMOBJ *obj);
void fn_1_7880(OMOBJ *obj);
void fn_1_78A8(void);
void fn_1_7F68(void);
void fn_1_7F80(void);
void fn_1_7F84(void);

#endif
