/*
 * The types m544.c, game.c and stage.c all need.
 *
 * m544dll is a KETTOU duel (overlay #58) on work head D of the duel stage
 * framework, REL/duelstage.h: head A's fields with three of everything (the
 * third player slot is the stage actor, model 34, which dangles the items), the
 * PadRead-262 pad block, `stageDataTbl` at 0x170, and m548's stage props
 * (DS_S_PROPS_B) at 0x1C8 on models 21-28. The work is 0x2E8.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M544_H
#define M544_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_15C). */
typedef DS_MODEL M544_MODEL;        /* 0x1C */

#define M544_MODEL_MAX 35

/*
 * Models: 0-9 the ten items, 10-11 what each duellist holds up, 12-15 and
 * 16-19 the two stages of a throw (four slots), 20-31 the arena (21-28 the
 * props), 32-33 the duellists, 34 the stage actor.
 */

typedef DS_CHAR262 M544_CHAR;       /* 0x1C */

typedef struct M544Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M544_CHAR chr[3];
    /* 0x058 */ M544_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];        /* [0] winner poses set */
    /* 0x188 */ u8 unk188[0x40];
    /* 0x1C8 */ DS_PROPB effect[5]; /* DS_S_PROPS_B */
    /* 0x2B8 */ u8 unk2B8[0x30];
} M544_WORK;                        /* 0x2E8 */

/* The cameras' state (bss_8, four allocated), from lbl_1_data_210. */
typedef struct M544Camera_s {
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
} M544_CAMERA;                      /* 0x50 */

typedef struct M544CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M544_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_4). */
typedef struct M544Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M544_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_0). */
typedef struct M544Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M544_SHADOW;                      /* 0x50 */

/* What fn_1_2EE4 spawns a dust particle with (lbl_1_data_370, bss_820). */
typedef struct M544ParticleParam_s {
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
} M544_PARTICLEPARAM;               /* 0x38 */

/* The item hook on the stage actor (bss_C). */
typedef struct M544Hook_s {
    /* 0x00 */ s16 mode;            /* fn_1_6B64: wait, dangle, reel in */
    /* 0x02 */ s16 dropMode;        /* fn_1_7288: drop the item, fade it */
    /* 0x04 */ s16 hookMode;        /* fn_1_5574: 0 hung, 1 held, 2 let go */
    /* 0x06 */ s16 unk06;
    /* 0x08 */ float tpLvl;
    /* 0x0C */ s16 timer;
    /* 0x0E */ s16 timer2;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 itemNo;          /* which of bss_8D8 is out */
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 dropF;
    /* 0x18 */ char name[0x2C];     /* "g003m1-itemhook_R" */
    /* 0x44 */ Mtx mtx;
} M544_HOOK;                        /* 0x74 */

/* One duellist's reaction state (bss_80). */
typedef struct M544Duellist_s {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 mode;            /* fn_1_5EFC, fn_1_614C, fn_1_6274 */
    /* 0x06 */ s16 holdMode;        /* fn_1_6F38 */
    /* 0x08 */ s16 timer;
    /* 0x0A */ s16 hitF;
    /* 0x0C */ s16 result;          /* 0 none, 1 grabbed, 2 beaten to it, 3 fooled */
    /* 0x0E */ s16 throwCnt;
    /* 0x10 */ HuVecF scale;
    /* 0x1C */ char *hookName;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 comTimer;
    /* 0x24 */ s16 comMode;
    /* 0x26 */ s16 comItem;
} M544_DUELLIST;                    /* 0x28 */

/* The duel's shared state (bss_D0). */
typedef struct M544Game_s {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 endMode;         /* fn_1_753C */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 timer;
    /* 0x08 */ u8 unk08[0x18];
    /* 0x20 */ s16 result;          /* winner | (loser << 1); 0 a draw */
    /* 0x22 */ s16 pad22;
    /* 0x24 */ MGTIMER *timer2;
    /* 0x28 */ s16 realF;           /* the item out is a real one */
    /* 0x2A */ s16 pad2A;
    /* 0x2C */ s16 flashF;
    /* 0x2E */ s16 bgmF;
    /* 0x30 */ int bgmNo;
    /* 0x34 */ int jingleNo;
    /* 0x38 */ s16 slideSeMode;
    /* 0x3A */ s16 pad3A;
    /* 0x3C */ int seNo[6];
    /* 0x54 */ s16 seF[6];
} M544_GAME;                        /* 0x60 */

/* One thrown item (bss_828). */
typedef struct M544Throw_s {
    /* 0x00 */ HuVecF from;
    /* 0x0C */ HuVecF to;
    /* 0x18 */ int timer;
    /* 0x1C */ int mode;
    /* 0x20 */ int activeF;
    /* 0x24 */ int player;
    /* 0x28 */ float alpha;
} M544_THROW;                       /* 0x2C */

/* One item on the hook (bss_8D8). */
typedef struct M544Item_s {
    /* 0x00 */ s16 waitTime;
    /* 0x02 */ s16 hangTime;
    /* 0x04 */ s16 kind;            /* the model; 0-5 real, 6-9 decoys */
} M544_ITEM;                        /* 0x06 */

/* m544.c */
extern M544_SHADOW *lbl_1_bss_0;
extern M544_LIGHT *lbl_1_bss_4;
extern M544_CAMERA *lbl_1_bss_8;
extern M544_HOOK lbl_1_bss_C;
extern M544_DUELLIST lbl_1_bss_80[2];
extern M544_GAME lbl_1_bss_D0;

void fn_1_9C0(s16 no);
void fn_1_1168(void);
void fn_1_1570(void);
s16 fn_1_18E8(float *value, float div, float start, float end);
MGTIMER *fn_1_1A1C(int type, int maxTime, int endTime, float x, float y);
void fn_1_1A90(MGTIMER *timer);
BOOL fn_1_1ABC(MGTIMER *timer);
void fn_1_1AE4(MGTIMER *timer);
void fn_1_2330(void);
void fn_1_2834(HuVecF *pos, s16 side);
void fn_1_34D0(void);
void fn_1_35DC(s16 player);
void fn_1_3EF8(void);
void fn_1_3F28(void);
void fn_1_3F58(s16 bgmF, s16 speed);
void fn_1_3FC0(s16 bgmF);
void fn_1_4020(s16 no);
void fn_1_4098(s16 no, s16 vol, s16 pan);
void fn_1_4120(s16 no, s16 pan);
void fn_1_41B0(s16 no);
void fn_1_425C(s16 no);
void fn_1_4308(void);

/* game.c */
extern M544_WORK *lbl_1_bss_914;
extern M544_ITEM lbl_1_bss_8D8[10];
extern M544_THROW lbl_1_bss_828[4];
extern HU3DMODELID lbl_1_bss_826;
extern HU3DMODELID lbl_1_bss_824;
extern M544_PARTICLEPARAM *lbl_1_bss_820;

s32 fn_1_4328(M544_WORK *work);
s32 fn_1_4E08(void);
s32 fn_1_4E3C(void);
s32 fn_1_4EB4(void);
s32 fn_1_5098(void);
s32 fn_1_5158(void);
s32 fn_1_5514(void);
s32 fn_1_5544(void);
void fn_1_86BC(void);
void fn_1_89AC(OMOBJ *obj);

/* stage.c */
void fn_1_9EF8(M544_WORK *work, M544_MODEL *models, unsigned int *dataTbl);
void fn_1_A144(s16 stageNo);
void fn_1_A3F0(s16 no, unsigned int *data);
void fn_1_A410(s16 no, HU3DMOTID *id);
void fn_1_A430(void);
void fn_1_A9A4(OMOBJ *obj);
void fn_1_ADBC(void);
void fn_1_AF60(OMOBJ *obj);
void fn_1_B318(OMOBJ *obj);
void fn_1_B36C(void);

#endif
