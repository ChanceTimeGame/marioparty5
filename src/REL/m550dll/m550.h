/*
 * The types m550.c, game.c and stage.c all need. The original compiles the
 * three as separate translation units (upstream's configure.py declares them
 * that way) and every one of them works through the same M550_WORK, so the
 * struct has to be settled before any of the three can be written.
 *
 * WORK IN PROGRESS. Fields are named as they are pinned down and left as
 * unkNNN otherwise; the padding is exact, so an unnamed field is unexplained
 * rather than unallocated.
 */
#ifndef M550_H
#define M550_H

#include "game/mg/timer.h"

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/*
 * One entry of the retained-mode model table. M550ModelFlush walks all 183 of
 * them once a frame and pushes pos and rot at Hu3D for every one whose id is
 * not negative, so the game code only ever writes this table.
 */
typedef DS_MODEL M550_MODEL;        /* 0x1C */

#define M550_MODEL_MAX 183

/* Who the two duellists are, picked out of GwPlayerConf by group. */
typedef DS_CHAR M550_CHAR;          /* 0x1C */

/*
 * One duellist's model state. The game code only ever writes the requested
 * halves of these pairs; M550MotionExec compares each against the applied one
 * and pushes the difference at Hu3D, which is why nothing else in the overlay
 * calls Hu3DMotionSet directly.
 */
typedef DS_PLAYER M550_PLAYER;      /* 0x54 */

/* The duel framework's 0x3C effect slot, and 0x10 more bytes of m550's own. */
typedef struct M550Effect_s {
    DS_EFFECT_HEAD;
    /* 0x3C */ float f3C;
    /* 0x40 */ float f40;
    /* 0x44 */ float f44;
    /* 0x48 */ u8 unk48[0x04];
} M550_EFFECT;                      /* 0x4C */

typedef struct M550Work_s {
    /*
     * 0x000..0x110, the duel framework's head: objman, chr[2], models,
     * charMotData[2] (a row of CharMotDataTbl each), motId[2] (five motions
     * each), player[2], stageDataTbl, stageNo and mode[4].
     *
     * mode[0] is the sequence sub-state that m550.c's nine hooks index their
     * function tables by. mode[1] and mode[2] are one duellist each, which is
     * why game.c reaches them as mode[winner], winner being 1 or 2.
     */
    DS_WORK_HEAD;
    /* 0x110 */ int timer;
    /* 0x114 */ int unk114;
    /* 0x118 */ int unk118;
    /* 0x11C */ int unk11C;
    /* 0x120 -- count[0..1] live, count[2..3] the values to fall back to. */
    /* 0x120 */ int count[4];
    /* 0x130 */ int winner;    /* 0 none, else duellist + 1 */
    /* 0x134 */ int winMode;
    /* 0x138 */ float unk138[2];
    /* 0x140 */ u8 unk140[0x008];
    /*
     * 0x148 -- four vectors, written as (pos, rot) per duellist by
     * M550ItemHookVecGet. game.c's win animation also uses [0].y and [0].z
     * as two scalars of its own; that overlap is the original's.
     */
    /* 0x148 */ HuVecF hookVec[4];
    /*
     * 0x178 -- 29 generic effect slots, and they fill the work struct exactly:
     * 0x178 + 29*0x4C is 0xA14. Every prop, light and orbiting model in
     * stage.c owns one or a run of them, and the float fields mean different
     * things to different owners, so they are named by offset rather than by
     * role. Entries 15 and 16 are the two sky props, which use only mode and
     * the first two timers.
     */
    /* 0x178 */ M550_EFFECT effect[29];
} M550_WORK;                        /* 0xA14 */

/*
 * bss_4 -- one per duellist, and only a computer player uses it. Zeroed and
 * refilled by M550GameUnk4494 at the start of the duel.
 */
typedef struct M550Com_s {
    /* 0x00 */ s16 level;   /* the pad's difficulty, less one */
    /* 0x02 */ s16 pad02;
    /* 0x04 */ int unk04;
    /* 0x08 */ int wait;    /* frames until the next press */
    /* 0x0C */ int tick;
} M550_COM;                 /* 0x10 */

/* m550.c -- shared with game.c, which reaches all four directly. */
extern MGTIMER *Unk0;
extern M550_COM Com[2];
extern OMCAMERAVIEW CameraView[4];
extern M550_WORK Work;

void M550MatAlphaSet(int mdlNo, float alpha);
void M550ItemPosSet(int player, HuVecF *pos, HuVecF *rot);
void M550ItemPosUpdate(void);
void M550ItemHookVecGet(void);
void M550Unk10BC(int player);

/* stage.c */
void M550WorkInit(M550_WORK *work, M550_MODEL *models, unsigned int *dataTbl);
void M550CharMotDataSet(unsigned int *dataA, unsigned int *dataB);
void M550CharMotIdSet(HU3DMOTID *idA, HU3DMOTID *idB);
void M550CharModelCreate(void);
void M550CharMotionCreate(void);
void M550StageMain(OMOBJ *obj);
void M550PadRead(OMOBJ *obj);
void M550MotionExec(OMOBJ *obj);
void M550Unk6D8C(void);
void M550Unk7C00(void);
void M550Unk7E94(void);
void M550Unk8190(void);

/* game.c */
void M550FadeIn0(void);
void M550FadeIn1(void);
void M550FadeIn2(void);
void M550Main0(void);
void M550Main1(void);
void M550Main2(void);
void M550PreWin0(void);
void M550PreWin1(void);
void M550PreWin2(void);
void M550PreWin3(void);
void M550PreWin4(void);
void M550GameUnk2364(void);
void M550GameUnk2618(void);

#endif
