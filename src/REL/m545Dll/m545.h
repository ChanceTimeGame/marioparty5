/*
 * The types m545.c, game.c and stage.c all need.
 *
 * m545dll is a KETTOU duel (overlay #59) on work head C of the duel stage
 * framework, REL/duelstage.h, like m546dll: the duel head to `motId` with its
 * own pad block (the PadRead-262 layout), two 0x44 player slots, `stageDataTbl`
 * at 0xD8, and m548's five stage props (DS_S_PROPS_B) at 0x130 on models
 * 25-32. The work is 0x250.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M545_H
#define M545_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_254). */
typedef DS_MODEL M545_MODEL;        /* 0x1C */

#define M545_MODEL_MAX 38

/*
 * A duellist and their pads: DS_CHAR262, the layout DS_S_PADREAD_262 reads
 * (one stick axis deadzoned, the bytes one later than DS_CHAR's).
 */
typedef DS_CHAR262 M545_CHAR;       /* 0x1C */

/* A head-C player slot: DS_PLAYER_HEAD, the motion's end flag, and the shift (DS_S_MOTIONEXEC_C). */
typedef DS_PLAYERC M545_PLAYER;     /* 0x44 */

typedef struct M545Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M545_CHAR chr[2];
    /* 0x03C */ M545_MODEL *models;
    /* 0x040 */ unsigned int *charMotData[2];
    /* 0x048 */ HU3DMOTID *motId[2];
    /* 0x050 */ M545_PLAYER player[2];
    /* 0x0D8 */ unsigned int *stageDataTbl;
    /* 0x0DC */ s16 stageNo;
    /* 0x0DE */ s16 pad0DE;
    /* 0x0E0 */ int mode[4];        /* [0] sub-state, [1] winner pose set, [2] block drop, [3] winner's lift */
    /* 0x0F0 */ int count[2];       /* fade-in: [0] its timer, [1] its step */
    /* 0x0F8 */ u8 unkF8[0x38];
    /* 0x130 */ DS_PROPB effect[5]; /* DS_S_PROPS_B */
    /* 0x220 */ u8 unk220[0x30];
} M545_WORK;                        /* 0x250 */

/* The three cameras' state (bss_8, four allocated), from lbl_1_data_178. */
typedef struct M545Camera_s {
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
} M545_CAMERA;                      /* 0x50 */

typedef struct M545CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M545_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_4). */
typedef struct M545Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M545_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_0). */
typedef struct M545Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M545_SHADOW;                      /* 0x50 */

/* What fn_1_1D4C spawns a dust particle with (lbl_1_data_268, bss_8D0). */
typedef struct M545ParticleParam_s {
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
} M545_PARTICLEPARAM;               /* 0x38 */

/* One duellist's stack of blocks (bss_C). */
typedef struct M545Stack_s {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 height;          /* blocks on the stack */
    /* 0x06 */ s16 missCnt;         /* computer: turns at full height */
    /* 0x08 */ HuVecF scale;        /* the duellist's squash */
    /* 0x14 */ HuVecF hookPos;
    /* 0x20 */ Mtx hookMtx;
    /* 0x50 */ s16 mode;            /* how fn_1_373C places the blocks */
    /* 0x52 */ s16 unk52;
    /* 0x54 */ char *hookName[2];
    /* 0x5C */ s16 inputF;          /* a press window just closed */
    /* 0x5E */ s16 aliveF;
    /* 0x60 */ s32 press[6];        /* this window: A, B, X, Y, L, R */
    /* 0x78 */ s32 pressTotal[6];
    /* 0x90 */ s32 unk90[2];
    /* 0x98 */ s32 frame;
    /* 0x9C */ s32 timer;
    /* 0xA0 */ s16 unkA0;
    /* 0xA2 */ s16 unkA2;
    /* 0xA4 */ s32 unkA4[2];
    /* 0xAC */ float angle[6];      /* the tower's sway, per block */
    /* 0xC4 */ s32 unkC4;
} M545_STACK;                       /* 0xC8 */

/* The duel's shared state (bss_19C). */
typedef struct M545Game_s {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 swingMode;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 endTimer;
    /* 0x08 */ float dropSpeed;
    /* 0x0C */ float tpLvl[12];
    /* 0x3C */ float camCenterY;
    /* 0x40 */ float camZoom;
    /* 0x44 */ u8 unk44[0x08];
    /* 0x4C */ s16 winner;          /* -1 a draw */
    /* 0x4E */ s16 waitTimer;
    /* 0x50 */ s16 checkTimer;
    /* 0x52 */ s16 bgmF;
    /* 0x54 */ int bgmNo;
    /* 0x58 */ int jingleNo;
    /* 0x5C */ int seNo[12];
    /* 0x8C */ s16 seF[12];
} M545_GAME;                        /* 0xA4 */

/* m545.c */
extern M545_SHADOW *lbl_1_bss_0;
extern M545_LIGHT *lbl_1_bss_4;
extern M545_CAMERA *lbl_1_bss_8;
extern M545_STACK lbl_1_bss_C[2];
extern M545_GAME lbl_1_bss_19C;

void fn_1_8C4(s16 no);
void fn_1_106C(void);
void fn_1_1474(void);
void fn_1_17EC(void);
void fn_1_1980(HuVecF *pos);
void fn_1_2338(void);
void fn_1_2368(void);
void fn_1_2398(s16 bgmF, s16 speed);
void fn_1_2400(s16 bgmF);
void fn_1_2460(s16 no);
void fn_1_24D8(s16 no, s16 vol, s16 pan);
void fn_1_2560(s16 no, s16 pan);
void fn_1_25F0(s16 no);
void fn_1_269C(void);

/* game.c */
s32 fn_1_26BC(M545_WORK *work);
s32 fn_1_2E88(M545_WORK *work);
s32 fn_1_2FE8(M545_WORK *work);
s32 fn_1_3030(M545_WORK *work);
s32 fn_1_3480(M545_WORK *work);
s32 fn_1_34EC(M545_WORK *work);
s32 fn_1_3538(M545_WORK *work);
s32 fn_1_3600(M545_WORK *work);
s32 fn_1_3638(void);

/* stage.c */
void fn_1_77EC(M545_WORK *work, M545_MODEL *models, unsigned int *dataTbl);
void fn_1_7A38(s16 stageNo);
void fn_1_7CE4(unsigned int *dataA, unsigned int *dataB);
void fn_1_7D08(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_7D2C(void);
void fn_1_803C(OMOBJ *obj);
void fn_1_8454(void);
void fn_1_8580(OMOBJ *obj);
void fn_1_88F0(OMOBJ *obj);

#endif
