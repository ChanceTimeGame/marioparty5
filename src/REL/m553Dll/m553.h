/*
 * The types m553.c, game.c and stage.c all need.
 *
 * m553dll is a KETTOU duel (overlay #67) on work head D of the duel stage
 * framework, REL/duelstage.h: three chr/motion slots, the PadRead-262 pad
 * block, stageDataTbl at 0x170, with the duellists moved by the actor manager
 * (game/mg/actman.h). The work is 0x804 and is the static lbl_1_bss_16DC
 * (2,052 bytes), not a heap allocation; stage.c's lbl_1_bss_1F00 points at it.
 *
 * Offsets come from every access in the reference assembly
 * (build/mp5-duelstage/20260915-m553-w1/list/scan.txt). Names that say unkNNN
 * are unexplained, not unallocated.
 */
#ifndef M553_H
#define M553_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_7FC, 3,808 bytes). */
typedef DS_MODEL M553_MODEL;        /* 0x1C */

#define M553_MODEL_MAX 136

typedef DS_CHAR262 M553_CHAR;       /* 0x1C */

/*
 * One stage effect slot. The same 0x4C as m550's: the framework head plus three
 * more floats. Twenty-one of them fill the work exactly from 0x1C8 to 0x804, and
 * every prop updater in stage.c owns one or a run of them -- 0..8 the nine
 * orbiting props, 9..12 the four turning ones, 13 the light that fn_1_F290
 * parks, 14..18 the big orbiter and its four companions, 19 and 20 the two sky
 * props.
 */
typedef DS_EFFECTD M553_EFFECT;     /* 0x4C */

typedef struct M553Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M553_CHAR chr[3];
    /* 0x058 */ M553_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];
    /* 0x188 */ u8 unk188[0x40];
    /* 0x1C8 */ M553_EFFECT effect[21];
} M553_WORK;                        /* 0x804 */

/* The cameras' state (bss_14, four allocated), from lbl_1_data_190. */
typedef struct M553Camera_s {
    /* 0x00 */ int no;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF center;
    /* 0x28 */ HuVecF up;
    /* 0x34 */ float zoom;
    /* 0x38 */ float aspect;
    /* 0x3C */ float vpX;
    /* 0x40 */ float vpY;
    /* 0x44 */ float vpW;
    /* 0x48 */ float vpH;
    /* 0x4C */ float fov;
} M553_CAMERA;                      /* 0x50 */

typedef struct M553CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M553_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_10). */
typedef struct M553Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M553_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_C). */
typedef struct M553Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M553_SHADOW;                      /* 0x50 */

/* What fn_1_2D1C spawns a dust particle with (lbl_1_data_2F8). */
typedef struct M553ParticleParam_s {
    /* 0x00 */ float unk00;
    /* 0x04 */ GXColor color;
    /* 0x08 */ GXColor colorEnd;
    /* 0x0C */ HuVecF vel;
    /* 0x18 */ HuVecF velMul;
    /* 0x24 */ float accelY;
    /* 0x28 */ float unk28;
    /* 0x2C */ float scaleSpeed;
    /* 0x30 */ float alphaSpeed;
    /* 0x34 */ float colorSpeed;
} M553_PARTICLEPARAM;               /* 0x38 */

/*
 * The duellists' actor-manager players (bss_0). +0x00 is the collision-map
 * model id fn_1_3AE4 passes to MgActorColMapInit as an array, not a plain s16.
 */
typedef struct M553Actors_s {
    /* 0x00 */ HU3DMODELID colMdlId[1];
    /* 0x02 */ s16 pad02;
    /* 0x04 */ MGPLAYER *player[2];
} M553_ACTORS;                      /* 0x0C */

/*
 * The overlay's game state (bss_70C). seNo and seF are 22 entries each, which
 * is exactly what lbl_1_data_330's sound table holds.
 *
 * f008 and s018 are arrays because two functions reach them two ways: fn_1_8948
 * indexes them by the duellist (f008[player], s018[player+2]) while fn_1_9A70
 * uses constant slots -- f008 is the camera/shadow ease pair (start, end) twice
 * over and s018 is {collapsing row, puff frame counter, -, wait}. A constant
 * index compiles the same as a named field, so one array serves both.
 */
typedef struct M553Game_s {
    /* 0x000 */ s16 mode;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 unk004;
    /* 0x006 */ s16 timer;
    /* 0x008 */ float f008[4];
    /* 0x018 */ s16 s018[4];
    /* 0x020 */ s16 winner;
    /* 0x022 */ s16 unk022;
    /* 0x024 */ s16 shakeNo;
    /* 0x026 */ s16 shakeF;
    /* 0x028 */ u8 unk028[0x00E];
    /* 0x036 */ s16 sepMode;
    /* 0x038 */ s16 sepCnt;
    /* 0x03A */ s16 hitF;
    /* 0x03C */ float scale3C;
    /* 0x040 */ float scale40;
    /* 0x044 */ MGTIMER *mgTimer;
    /* 0x048 */ u8 unk048[0x004];
    /* 0x04C */ s32 bgmNo;
    /* 0x050 */ s32 jingleNo;
    /* 0x054 */ s16 breakF;
    /* 0x056 */ s16 unk056;
    /* 0x058 */ s32 seNo[22];
    /* 0x0B0 */ s16 seF[22];
} M553_GAME;                        /* 0xDC */

/* One duellist's own state (bss_48C, two of them). */
typedef struct M553Duellist_s {
    /* 0x000 */ s16 unk000;
    /* 0x002 */ s16 mode;
    /* 0x004 */ u8 unk004[0x008];
    /* 0x00C */ float tint;
    /* 0x010 */ s8 *matColor;
    /* 0x014 */ s16 padOffF;
    /* 0x016 */ s16 hitCnt;
    /* 0x018 */ s16 comWait;
    /* 0x01A */ s16 unk01A;
    /* 0x01C */ HuVecF pos;
    /* 0x028 */ HuVecF posOld;
    /* 0x034 */ HuVecF vel;
    /* 0x040 */ float rotY;
    /* 0x044 */ s16 tookF;
    /* 0x046 */ s16 stackNum;
    /* 0x048 */ s16 unk048;
    /* 0x04A */ s16 stackMdl[20];
    /* 0x072 */ s16 comF;
    /* 0x074 */ s16 dif;
    /* 0x076 */ s16 state;
    /* 0x078 */ u8 unk078[0x004];
    /* 0x07C */ s16 chaseState;
    /* 0x07E */ s16 unk07E;
    /* 0x080 */ HuVecF chasePos;
    /* 0x08C */ u8 unk08C[0x00C];
    /* 0x098 */ float chaseRadius;
    /* 0x09C */ float chaseVelZ;
    /* 0x0A0 */ float unk0A0;
    /* 0x0A4 */ s16 comState;
    /* 0x0A6 */ s16 waitMax;
    /* 0x0A8 */ s16 waitCnt;
    /* 0x0AA */ s16 slotF[64];
    /* 0x12A */ s16 prob;
    /* 0x12C */ s16 slotNo;
    /* 0x12E */ s16 randMax;
    /* 0x130 */ u32 btn;
    /* 0x134 */ u32 btnDown;
    /* 0x138 */ u32 stkX;
    /* 0x13C */ u32 stkY;
} M553_DUELLIST;                    /* 0x140 */

/* One stage object (bss_18); fn_1_3AE4 scatters 35 over the 8x8 slot grid. */
typedef struct M553StageObj_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 colF;
    /* 0x04 */ s16 state;
    /* 0x06 */ s16 fadeState;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 fadeWait;
    /* 0x0C */ s16 typeF;
    /* 0x0E */ s16 mdlMain;
    /* 0x10 */ s16 mdlSub;
    /* 0x12 */ s16 mdlIdle;
    /* 0x14 */ s16 takenF;
    /* 0x16 */ s16 slot;
    /* 0x18 */ s16 duellist;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ float tpLvl;
} M553_STAGEOBJ;                    /* 0x20 */

/*
 * The round state (bss_478). Nine s16 and no padding: fn_1_3AE4 clears it with
 * an 18-byte memset, so a tenth field would make that memset 20 and miss.
 */
typedef struct M553State_s {
    /* 0x00 */ s16 state;
    /* 0x02 */ s16 step;
    /* 0x04 */ s16 wait;
    /* 0x06 */ s16 timer;
    /* 0x08 */ s16 numA;
    /* 0x0A */ s16 numB;
    /* 0x0C */ s16 objNum;
    /* 0x0E */ s16 endF;
    /* 0x10 */ s16 takenF;
} M553_STATE;                       /* 0x12 */

/* One side face of a stage object's box, as fn_1_B668 pushes a duellist out. */
typedef struct M553Face_s {
    /* 0x00 */ HuVecF axis;
    /* 0x0C */ HuVecF ofs;
} M553_FACE;                        /* 0x18 */

/* m553.c defines these; game.c and stage.c reach them. */
extern M553_ACTORS lbl_1_bss_0;
extern M553_SHADOW *lbl_1_bss_C;
extern M553_LIGHT *lbl_1_bss_10;
extern M553_CAMERA *lbl_1_bss_14;
extern M553_STAGEOBJ lbl_1_bss_18[35];
extern M553_STATE lbl_1_bss_478;
extern M553_DUELLIST lbl_1_bss_48C[2];
extern M553_GAME lbl_1_bss_70C;
extern M553_CAMERAINIT lbl_1_data_190[4];

/* game.c defines this; it is a separate pointer from stage.c's lbl_1_bss_1F00. */
extern M553_WORK *lbl_1_bss_1EF8;

#endif /* M553_H */
