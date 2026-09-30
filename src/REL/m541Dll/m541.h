/*
 * The types m541.c, game.c and stage.c all need.
 *
 * m541dll is a KETTOU duel (overlay #55) on work head D of the duel stage
 * framework, REL/duelstage.h: m543's layout exactly (three chr/motion slots,
 * the PadRead-262 pad block, stageDataTbl at 0x170), with the duellists moved
 * by the actor manager (game/mg/actman.h). The work is 0x2E8.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M541_H
#define M541_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_27E0, 0xBD0 = 108 of them). */
typedef DS_MODEL M541_MODEL;        /* 0x1C */

#define M541_MODEL_MAX 108

typedef DS_CHAR262 M541_CHAR;       /* 0x1C */

/* Eight motions per duellist; lbl_1_data_28 is one row per character. */
#define M541_MOTION_MAX 8

typedef struct M541Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M541_CHAR chr[3];
    /* 0x058 */ M541_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];
    /* 0x188 */ u8 unk188[0x160];
} M541_WORK;                        /* 0x2E8 */

/* The cameras' state (bss_1C, four allocated plus eight bytes), from lbl_1_data_1F8. */
typedef struct M541Camera_s {
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
} M541_CAMERA;                      /* 0x50 */

typedef struct M541CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M541_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_18). */
typedef struct M541Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M541_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_14). */
typedef struct M541Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M541_SHADOW;                      /* 0x50 */

/* One duellist's state (bss_2614), two of them. */
typedef struct M541Duellist_s {
    /* 0x000 */ s16 mode;           /* fn_1_7850 */
    /* 0x002 */ s16 hitMode;        /* fn_1_7DE8, and the hit reaction fn_1_832C reports */
    /* 0x004 */ s16 hitResult;
    /* 0x006 */ u8 unk006[0x02];
    /* 0x008 */ s16 flashTimer;
    /* 0x00A */ s16 pad00A;
    /* 0x00C */ void *itemHook;     /* CharModelItemHookGet */
    /* 0x010 */ s16 stopF;
    /* 0x012 */ s16 unk012;
    /* 0x014 */ float tint;         /* fn_1_2378 scales the materials by it */
    /* 0x018 */ s8 *matColor;       /* fn_1_2280: the materials' colours */
    /* 0x01C */ HuVecF pos;
    /* 0x028 */ HuVecF oldPos;
    /* 0x034 */ s16 hitType;        /* 1 and 2 are the two hits fn_1_7850 reacts to */
    /* 0x036 */ s16 pad036;
    /* 0x038 */ float rotY;
    /* 0x03C */ s16 comF;
    /* 0x03E */ s16 comDif;         /* the character's difficulty, 0-3 */
    /* 0x040 */ s16 comMode;        /* fn_1_11BF8 */
    /* 0x042 */ u8 unk042[0x04];
    /* 0x046 */ s16 thinkTimer;      /* fn_1_14EB0 runs when it reaches thinkTime */
    /* 0x048 */ s16 escapeWallNo;    /* fn_1_14EB0: the wall polyline of the chosen ray */
    /* 0x04A */ s16 chaseMode;      /* fn_1_11DE8 */
    /* 0x04C */ u8 unk04C[0x04];
    /* 0x050 */ HuVecF vel;
    /* 0x05C */ float chaseRadius;  /* fn_1_11DE8's MgPlayerVecChase radius; vel is its target */
    /* 0x060 */ float turnRate;
    /* 0x064 */ float turnRateBase;
    /* 0x068 */ s16 thinkSlowStep;  /* fn_1_11BF8: past this platform step thinkTime grows */
    /* 0x06A */ s16 thinkTime;
    /* 0x06C */ s16 thinkTimeAdd;
    /* 0x06E */ s16 escapeNo;        /* fn_1_14EB0: the chosen ray */
    /* 0x070 */ HuVecF escapePos;    /* where that ray meets a wall */
    /* 0x07C */ float escapeDist;
    /* 0x080 */ int btn;
    /* 0x084 */ int btnDown;
    /* 0x088 */ int stkX;
    /* 0x08C */ int stkY;
} M541_DUELLIST;                    /* 0x90 */

/* The duel's shared state (bss_2734). */
typedef struct M541Game_s {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 timer;
    /* 0x08 */ float rotYEnd;         /* fn_1_E0A4: the winner's yaw to turn from */
    /* 0x0C */ u8 unk0C[0x14];
    /* 0x20 */ s16 winner;          /* winner | (loser << 1), 0 for none */
    /* 0x22 */ s16 pad22;
    /* 0x24 */ MGTIMER *mgTimer;
    /* 0x28 */ u8 unk28[0x04];
    /* 0x2C */ HuVecF jumpFrom;     /* fn_1_832C's two-hop jump, set by fn_1_B4E0 */
    /* 0x38 */ HuVecF jumpTo;
    /* 0x44 */ HuVecF jumpVel;
    /* 0x50 */ HuVecF hopVel;
    /* 0x5C */ s16 jumpCnt;
    /* 0x5E */ s16 pad5E;
    /* 0x60 */ float jumpGravity;
    /* 0x64 */ u8 unk64[0x04];
    /* 0x68 */ int bgmNo;
    /* 0x6C */ int jingleNo;
    /* 0x70 */ u8 unk70[0x04];
    /* 0x74 */ int seNo[4];
    /* 0x84 */ s16 seF[4];
} M541_GAME;                        /* 0x8C */

/* The duellists' actor-manager players (bss_0). */
typedef struct M541Actors_s {
    /* 0x00 */ HU3DMODELID colMdlId[1]; /* fn_1_2AD4: the floor, for MgActorColMapInit */
    /* 0x02 */ u8 unk02[0x02];
    /* 0x04 */ MGPLAYER *player[2];
    /* 0x0C */ u8 unk0C[0x08];
} M541_ACTORS;                      /* 0x14 */

/* One of the fifteen moving platforms (bss_20). */
typedef struct M541Mover_s {
    /* 0x00 */ s16 activeF;         /* moving */
    /* 0x02 */ s16 dispF;           /* placed and visible */
    /* 0x04 */ s16 spawnMode;       /* fn_1_A9B8 */
    /* 0x06 */ u8 unk06[0x06];
    /* 0x0C */ float tpLvl;
    /* 0x10 */ s16 stopF;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ HuVecF vel;
    /* 0x20 */ HuVecF savedVel;     /* fn_1_92FC holds the platform still while the beam is up */
    /* 0x2C */ float angle;
} M541_MOVER;                       /* 0x30 */

/* The beam event (bss_2F0): fn_1_92FC links round+2 platforms and zaps what stands between. */
typedef struct M541Stage_s {
    /* 0x000 */ s16 mode;
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 beamF;
    /* 0x006 */ s16 timer;
    /* 0x008 */ s16 round;
    /* 0x00A */ s16 list[10];       /* platform numbers, -1 ended */
    /* 0x01E */ s16 pad01E;
    /* 0x020 */ HuVecF scale[10];   /* the beam models 16-25 */
    /* 0x098 */ HuVecF scale2[10];
    /* 0x110 */ float dist[10];
    /* 0x138 */ float angle[10];
    /* 0x160 */ float speed;
    /* 0x164 */ s16 spawnMode;      /* fn_1_A884 */
    /* 0x166 */ s16 spawnTimer;
    /* 0x168 */ s16 spawnNum;
    /* 0x16A */ s16 pad16A;
} M541_STAGE;                       /* 0x16C */

/* bss_45C. */
typedef struct M541Big_s {
    /* 0x0000 */ s16 step;          /* fn_1_11B7C: platform steps simulated */
    /* 0x0002 */ s16 frame;
    /* 0x0004 */ s16 predMode;      /* fn_1_11B7C */
    /* 0x0006 */ s16 num;           /* platforms in play (fn_1_194B4 adds one, at most 15) */
    /* 0x0008 */ float speed;       /* the platforms' speed */
    /* 0x000C */ HuVecF vtx[17][30];
    /* 0x17F4 */ s16 idx[17][30];
    /* 0x1BF0 */ s16 idxNum[17];
    /* 0x1C12 */ s16 head[15];      /* fn_1_12830: ring position of the newest step in vtx[i] */
    /* 0x1C30 */ s16 tail[15];      /* and of the oldest */
    /* 0x1C4E */ s16 lastHitF[15];
    /* 0x1C6C */ s16 hitF[16];      /* fn_1_12F40: bounced this frame */
    /* 0x1C8C */ HuVecF pos[23];      /* entries 15-22 are the fixed platforms' spots (fn_1_2AD4) */
    /* 0x1DA0 */ HuVecF vel[23];
    /* 0x1EB4 */ HuVecF velSave[23]; /* fn_1_187F8: velocity while a route is held still */
    /* 0x1FC8 */ float angle[15];
    /* 0x2004 */ s16 routeMode;     /* fn_1_187F8 */
    /* 0x2006 */ s16 routeTimer;
    /* 0x2008 */ s16 routeLen;
    /* 0x200A */ s16 routeF;
    /* 0x200C */ s16 stopF[15];
    /* 0x202A */ s16 route[10];
    /* 0x203E */ s16 recPick[10];   /* fn_1_92FC with recF: the recorded first platform */
    /* 0x2052 */ s16 recTimer[10];  /* and the recorded wait */
    /* 0x2066 */ s16 placeMode[15];  /* fn_1_19738 */
    /* 0x2084 */ s16 placeF[16];
    /* 0x20A4 */ HuVecF recPlace[15]; /* fn_1_A9B8 type 1: heading, radius and angle of each platform */
    /* 0x2158 */ s16 placeTimer[15];
    /* 0x2176 */ s16 spawnTimer;    /* fn_1_194B4 */
    /* 0x2178 */ s16 spawnMode;
    /* 0x217A */ s16 routeCnt;
    /* 0x217C */ s16 recPickCnt;
    /* 0x217E */ s16 recTimerCnt;
    /* 0x2180 */ s16 waitCnt;
    /* 0x2182 */ u8 unk2182[0x36];
} M541_BIG;                         /* 0x21B8 */

/* The three models of each moving platform (bss_36A4). */
typedef struct M541MoverMdl_s {
    /* 0x00 */ s16 mdlNo[3];
} M541_MOVERMDL;                    /* 0x06 */

/* m541.c */
extern M541_ACTORS lbl_1_bss_0;
#define M541_MOVER_NUM 15
extern M541_MOVER lbl_1_bss_20[M541_MOVER_NUM];
extern M541_STAGE lbl_1_bss_2F0;
extern M541_BIG lbl_1_bss_45C;
extern M541_SHADOW *lbl_1_bss_14;
extern M541_LIGHT *lbl_1_bss_18;
extern M541_CAMERA *lbl_1_bss_1C;
extern M541_DUELLIST lbl_1_bss_2614[2];
extern M541_GAME lbl_1_bss_2734;
extern M541_MODEL lbl_1_bss_27E0[M541_MODEL_MAX];
extern M541_WORK lbl_1_bss_33B0;
extern M541_CAMERAINIT lbl_1_data_1F8[4];

void fn_1_91C(s16 no);
void fn_1_10C4(void);
void fn_1_14C4(void);
s16 fn_1_1850(float *value, float div, float start, float end);
MGTIMER *fn_1_1970(int type, int maxTime, int endTime, float x, float y);
void fn_1_19E4(MGTIMER *timer);
BOOL fn_1_1A10(MGTIMER *timer);
void fn_1_1A38(MGTIMER *timer);
void fn_1_2280(s16 player);
s16 fn_1_2378(s16 player, float scale);
void fn_1_24E8(s16 player);
void fn_1_25E4(void);
void fn_1_2614(void);
void fn_1_2644(s16 bgmF, s16 speed);
void fn_1_26AC(s16 bgmF);
void fn_1_270C(s16 no);
void fn_1_27C8(s16 no, s16 vol, s16 pan);
void fn_1_2894(s16 no, s16 pan);
void fn_1_2924(s16 no);
void fn_1_29EC(s16 no);
void fn_1_2AB4(void);


/* game.c */
extern M541_WORK *lbl_1_bss_3730;

/* game/mg/actman.c; not in actman.h. */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/* stage.c */
void fn_1_19AB0(M541_WORK *work, M541_MODEL *models, unsigned int *dataTbl);
void fn_1_19CFC(s16 stageNo);
void fn_1_19D10(s16 no, unsigned int *data);
void fn_1_19D30(s16 no, HU3DMOTID *id);
void fn_1_19D50(void);
void fn_1_19D54(OMOBJ *obj);
void fn_1_1A16C(void);
void fn_1_1A320(OMOBJ *obj);

#endif
