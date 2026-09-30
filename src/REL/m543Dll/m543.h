/*
 * The types m543.c, game.c and stage.c all need.
 *
 * m543dll is a KETTOU duel (overlay #57) on work head D of the duel stage
 * framework, REL/duelstage.h: m544's layout (three chr/motion slots, the
 * PadRead-262 pad block, stageDataTbl at 0x170), with the duellists moved by
 * the actor manager (game/mg/actman.h) rather than MotionExec's slots alone.
 * The work is 0x2E8.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M543_H
#define M543_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_C24). */
typedef DS_MODEL M543_MODEL;        /* 0x1C */

#define M543_MODEL_MAX 62

typedef DS_CHAR262 M543_CHAR;       /* 0x1C */

typedef struct M543Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M543_CHAR chr[3];
    /* 0x058 */ M543_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];        /* [0] winner pose set */
    /* 0x188 */ u8 unk188[0x160];
} M543_WORK;                        /* 0x2E8 */

/* The cameras' state (bss_18, four allocated), from lbl_1_data_1D8. */
typedef struct M543Camera_s {
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
} M543_CAMERA;                      /* 0x50 */

typedef struct M543CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M543_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_14). */
typedef struct M543Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M543_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_10). */
typedef struct M543Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M543_SHADOW;                      /* 0x50 */

/* What fn_1_2F3C spawns a dust particle with (lbl_1_data_340, bss_15D8). */
typedef struct M543ParticleParam_s {
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
} M543_PARTICLEPARAM;               /* 0x38 */

/* The duellists' actor-manager players and the collision models (bss_0). */
typedef struct M543Actors_s {
    /* 0x00 */ HU3DMODELID colMdlId[3];
    /* 0x06 */ s16 pad06;
    /* 0x08 */ MGPLAYER *player[2];
} M543_ACTORS;                      /* 0x10 */

/* One of the 40 path nodes the computer walks between (bss_1C); only 0-29 are placed. */
typedef struct M543Tile_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ s16 link[4];         /* the panel (bss_33C) on each side, or -1 */
} M543_TILE;                        /* 0x14 */

/* One of the 45 floor panels (bss_33C); 0-40 are models 15-55, 41-44 are never placed. */
typedef struct M543Panel_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 dropF;           /* fn_1_7C18 drops it */
    /* 0x04 */ s16 mode;            /* fn_1_71AC */
    /* 0x06 */ s16 motSel;          /* which of lbl_1_data_7F4 runs it */
    /* 0x08 */ s16 motSelOld;
    /* 0x0A */ s16 motMode;         /* fn_1_7394, fn_1_7704 */
    /* 0x0C */ s16 dropMode;
    /* 0x0E */ s16 unk0E;
    /* 0x10 */ s16 owner;           /* the duellist on it */
    /* 0x12 */ s16 pad12;
    /* 0x14 */ float motTime;
    /* 0x18 */ HU3DMOTID motId[3];
    /* 0x1E */ s16 pad1E;
} M543_PANEL;                       /* 0x20 */

/* One duellist's state (bss_8DC). */
typedef struct M543Duellist_s {
    /* 0x000 */ s16 mode;           /* fn_1_69BC */
    /* 0x002 */ s16 knockMode;      /* fn_1_6CF0 */
    /* 0x004 */ u8 unk004[0x08];
    /* 0x00C */ float tint;         /* fn_1_3650 fades the materials by it */
    /* 0x010 */ s8 *matColor;       /* fn_1_3558: the materials' colours */
    /* 0x014 */ s16 padOffF;
    /* 0x016 */ s16 hitF;
    /* 0x018 */ s16 knockF;
    /* 0x01A */ s16 knockTimer;
    /* 0x01C */ HuVecF knockStart;
    /* 0x028 */ HuVecF knockEnd;
    /* 0x034 */ s16 stunF;
    /* 0x036 */ s16 pad036;
    /* 0x038 */ HuVecF pos;
    /* 0x044 */ HuVecF oldPos;
    /* 0x050 */ s16 comF;
    /* 0x052 */ s16 comLevel;
    /* 0x054 */ s16 comMode;        /* fn_1_D9E8 */
    /* 0x056 */ u8 unk056[0x04];
    /* 0x05A */ s16 comWait;
    /* 0x05C */ s16 comTimer;
    /* 0x05E */ s16 stepTimer;
    /* 0x060 */ s16 pathMode;       /* fn_1_EF58 */
    /* 0x062 */ s16 stepMode;       /* fn_1_E340 */
    /* 0x064 */ s16 stepWait;
    /* 0x066 */ s16 dirNo;
    /* 0x068 */ s16 altDirNo;
    /* 0x06A */ s16 openNum;
    /* 0x06C */ s16 openDir[4];
    /* 0x074 */ s16 dirWeight[4];
    /* 0x07C */ s16 dirBonus;
    /* 0x07E */ s16 tryChance;
    /* 0x080 */ s16 chaseMode;      /* fn_1_E144 */
    /* 0x082 */ s16 pad082;
    /* 0x084 */ HuVecF chasePos;
    /* 0x090 */ HuVecF stepPos;
    /* 0x09C */ float chaseRadius;
    /* 0x0A0 */ float chaseSpeed;
    /* 0x0A4 */ float walkSpeed;
    /* 0x0A8 */ float stepSpeed;
    /* 0x0AC */ s16 panelF[45];
    /* 0x106 */ s16 tileF[30];
    /* 0x142 */ s16 stepWaitMax;
    /* 0x144 */ s16 prevTile;
    /* 0x146 */ s16 curTile;
    /* 0x148 */ s16 nextTile;
    /* 0x14A */ s16 blockedF;
    /* 0x14C */ int btn;
    /* 0x150 */ int btnDown;
    /* 0x154 */ int stkX;
    /* 0x158 */ int stkY;
} M543_DUELLIST;                    /* 0x15C */

/* The duel's shared state (bss_B94). */
typedef struct M543Game_s {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 winMode;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 timer;
    /* 0x08 */ s16 dropRow;
    /* 0x0A */ s16 dropTimer;
    /* 0x0C */ s16 shakeMode;
    /* 0x0E */ s16 shakeNo;
    /* 0x10 */ s16 shakeCnt;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ HuVecF camPos;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 hitF;
    /* 0x24 */ float rotY;
    /* 0x28 */ u8 unk28[0x14];
    /* 0x3C */ s16 winner;          /* winner | (loser << 1); 0 none */
    /* 0x3E */ u8 unk3E[0x0A];
    /* 0x48 */ MGTIMER *mgTimer;
    /* 0x4C */ u8 unk4C[0x04];
    /* 0x50 */ int bgmNo;
    /* 0x54 */ int jingleNo;
    /* 0x58 */ u8 unk58[0x04];
    /* 0x5C */ int seNo[4];
    /* 0x6C */ s16 seF[4];
} M543_GAME;                        /* 0x74 */

/* m543.c */
extern M543_ACTORS lbl_1_bss_0;
extern M543_SHADOW *lbl_1_bss_10;
extern M543_LIGHT *lbl_1_bss_14;
extern M543_CAMERA *lbl_1_bss_18;
extern M543_TILE lbl_1_bss_1C[40];
extern M543_PANEL lbl_1_bss_33C[45];
extern M543_DUELLIST lbl_1_bss_8DC[2];
extern M543_GAME lbl_1_bss_B94;
extern M543_CAMERAINIT lbl_1_data_1D8[4];

void fn_1_91C(s16 no);
void fn_1_10C4(void);
void fn_1_14C4(void);
s16 fn_1_1850(float *value, float div, float start, float end);
s16 fn_1_1970(float *value, float div, float start, float end);
MGTIMER *fn_1_1A8C(int type, int maxTime, int endTime, float x, float y);
void fn_1_1B00(MGTIMER *timer);
BOOL fn_1_1B2C(MGTIMER *timer);
void fn_1_1B54(MGTIMER *timer);
void fn_1_239C(void);
void fn_1_2898(HuVecF *pos, s16 side);
void fn_1_3558(s16 player);
s16 fn_1_3650(s16 player, float scale);
void fn_1_37C0(s16 player);
void fn_1_38BC(void);
void fn_1_38EC(void);
void fn_1_391C(s16 bgmF, s16 speed);
void fn_1_3984(s16 bgmF);
void fn_1_39E4(s16 no);
void fn_1_3A5C(s16 no, s16 vol, s16 pan);
void fn_1_3AE4(s16 no, s16 pan);
void fn_1_3B74(s16 no);
void fn_1_3C20(s16 no);
void fn_1_3CCC(void);

/* game.c */
extern M543_WORK *lbl_1_bss_15E0;

/* game/mg/actman.c; not in actman.h. */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);


/* stage.c */
void fn_1_FA94(M543_WORK *work, M543_MODEL *models, unsigned int *dataTbl);
void fn_1_FCE0(s16 stageNo);
void fn_1_FCF4(s16 no, unsigned int *data);
void fn_1_FD14(s16 no, HU3DMOTID *id);
void fn_1_FD34(void);
void fn_1_FD38(OMOBJ *obj);
void fn_1_10150(void);
void fn_1_10304(OMOBJ *obj);

#endif
