/*
 * The types m546.c, game.c and stage.c all need.
 *
 * m546dll is a KETTOU duel (overlay #60) on work head C of the duel stage
 * framework, REL/duelstage.h, like m545dll: the duel head to `motId` with the
 * PadRead-262 pad block, two DS_PLAYERC slots, `stageDataTbl` at 0xD8, and
 * the five stage props (DS_S_PROPS_B, DS_PROPSWING_GO) at 0x130 on models
 * 16-23. The work is 0x250.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M546_H
#define M546_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"
#include "game/mg/timer.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_14CFC). */
typedef DS_MODEL M546_MODEL;        /* 0x1C */

#define M546_MODEL_MAX 29

typedef DS_CHAR262 M546_CHAR;       /* 0x1C */
typedef DS_PLAYERC M546_PLAYER;     /* 0x44 */

typedef struct M546Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M546_CHAR chr[2];
    /* 0x03C */ M546_MODEL *models;
    /* 0x040 */ unsigned int *charMotData[2];
    /* 0x048 */ HU3DMOTID *motId[2];
    /* 0x050 */ M546_PLAYER player[2];
    /* 0x0D8 */ unsigned int *stageDataTbl;
    /* 0x0DC */ s16 stageNo;
    /* 0x0DE */ s16 pad0DE;
    /* 0x0E0 */ int mode[4];
    /* 0x0F0 */ int count[2];
    /* 0x0F8 */ u8 unkF8[0x38];
    /* 0x130 */ DS_PROPB effect[5]; /* DS_S_PROPS_B */
    /* 0x220 */ u8 unk220[0x30];
} M546_WORK;                        /* 0x250 */

/* The four cameras' state (bss_48), from lbl_1_data_250. */
typedef struct M546Camera_s {
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
} M546_CAMERA;                      /* 0x50 */

typedef struct M546CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M546_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_44). */
typedef struct M546Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M546_LIGHT;                       /* 0x3C */

/* The point light (bss_4, one). */
typedef struct M546PointLight_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 activeF;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ float unk38;
    /* 0x3C */ GXColor color;
} M546_POINTLIGHT;                  /* 0x40 */

/* The shadow camera (bss_0). */
typedef struct M546Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M546_SHADOW;                      /* 0x50 */

/* What fn_1_2448 spawns a dust particle with (lbl_1_data_340, bss_15280). */
typedef struct M546ParticleParam_s {
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
} M546_PARTICLEPARAM;               /* 0x38 */

/* One paper piece (bss_1F0[1000], bss_4C[5]), drawn by a hook. */
typedef struct M546Piece_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 mode;
    /* 0x04 */ s16 timer;
    /* 0x06 */ s16 kind;            /* which of the set's four models */
    /* 0x08 */ HuVecF pos;
    /* 0x14 */ HuVecF vel;
    /* 0x20 */ HuVecF rot;
    /* 0x2C */ HuVecF rotVel;
    /* 0x38 */ float tpLvl;
    /* 0x3C */ HuVecF color;
    /* 0x48 */ HuVecF colorMul;
} M546_PIECE;                       /* 0x54 */

/* A set of pieces and the hook model that draws them (bss_14AB8, bss_14A10). */
typedef struct M546PieceSet_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ float floorY;
    /* 0x14 */ s16 timer;
    /* 0x16 */ s16 num;
    /* 0x18 */ s16 spawnCnt;
    /* 0x1A */ s16 total;
    /* 0x1C */ s16 pad1C;
    /* 0x1E */ HU3DMODELID modelId[4];
    /* 0x26 */ char objName[4][32];
    /* 0xA6 */ HU3DMODELID hookId;
} M546_PIECESET;                    /* 0xA8 */

/* One duellist's game state (bss_14B60). */
typedef struct M546Duel_s {
    /* 0x00 */ s16 mode;            /* fn_1_743C's step */
    /* 0x02 */ s16 subMode;         /* the step's own state */
    /* 0x04 */ u8 unk04[0x04];
    /* 0x08 */ char *hookName;
    /* 0x0C */ s16 timer;
    /* 0x0E */ s16 pad0E;
    /* 0x10 */ float speed;         /* frames for the current lane step */
    /* 0x14 */ s16 lane;            /* -1, 0, 1 */
    /* 0x16 */ s16 pad16;
    /* 0x18 */ HuVecF scale;
    /* 0x24 */ HuVecF startPos;
    /* 0x30 */ HuVecF endPos;
    /* 0x3C */ HuVecF startRot;
    /* 0x48 */ float unk48;
    /* 0x4C */ float endRotY;
    /* 0x50 */ u8 unk50[0x04];
    /* 0x54 */ s16 squashSeF;
    /* 0x56 */ s16 walkMode;
    /* 0x58 */ float walkTime;
    /* 0x5C */ float angleZ;
    /* 0x60 */ float angleX;
    /* 0x64 */ float baseX;
    /* 0x68 */ s16 comMoves;        /* computer: lane changes left */
    /* 0x6A */ s16 comChance;       /* computer: percent chance to change */
    /* 0x6C */ s16 comMode;
    /* 0x6E */ s16 pad6E;
} M546_DUEL;                        /* 0x70 */

/* The duel's shared state (bss_14C40). */
typedef struct M546Game_s {
    /* 0x00 */ s16 camMode;
    /* 0x02 */ s16 poseF;
    /* 0x04 */ u8 unk04[0x1C];
    /* 0x20 */ s16 introTimer;
    /* 0x22 */ s16 order[3];        /* what each lane holds: 0 the box, 1 paper, 2 confetti */
    /* 0x28 */ s16 seDir;
    /* 0x2A */ s16 pad2A;
    /* 0x2C */ float dropSpeed;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 pad32;
    /* 0x34 */ float bombTpLvl[3];
    /* 0x40 */ s16 turn;
    /* 0x42 */ s16 winner;
    /* 0x44 */ s16 loser;
    /* 0x46 */ s16 waitTimer;
    /* 0x48 */ float boxTpLvl;
    /* 0x4C */ float laneTpLvl[3];
    /* 0x58 */ MGTIMER *timer;
    /* 0x5C */ s16 bgmF;
    /* 0x5E */ s16 pad5E;
    /* 0x60 */ int bgmNo;
    /* 0x64 */ int jingleNo;
    /* 0x68 */ s16 slideSeMode;
    /* 0x6A */ s16 pad6A;
    /* 0x6C */ int seNo[7];
    /* 0x88 */ s16 seF[8];
} M546_GAME;                        /* 0x98 */

/* m546.c */
extern M546_SHADOW *lbl_1_bss_0;
extern M546_POINTLIGHT lbl_1_bss_4[1];
extern M546_LIGHT *lbl_1_bss_44;
extern M546_CAMERA *lbl_1_bss_48;
extern M546_PIECE lbl_1_bss_4C[5];
extern M546_PIECE lbl_1_bss_1F0[1000];
extern M546_PIECESET lbl_1_bss_14A10;
extern M546_PIECESET lbl_1_bss_14AB8;
extern M546_DUEL lbl_1_bss_14B60[2];
extern M546_GAME lbl_1_bss_14C40;
extern M546_WORK lbl_1_bss_15028;
extern s16 lbl_1_data_320[16];

void fn_1_884(s16 no);
void fn_1_102C(void);
void fn_1_1434(void);
s16 fn_1_17BC(float *value, float div, float start, float end);
MGTIMER *fn_1_18DC(int type, int maxTime, int endTime, float x, float y);
void fn_1_1950(MGTIMER *timer);
BOOL fn_1_197C(MGTIMER *timer);
void fn_1_19A4(MGTIMER *timer);
void fn_1_19DC(void);
void fn_1_1B80(HuVecF *pos);
void fn_1_1F4C(HuVecF *pos);
s16 fn_1_2448(float x, float y, float z, float scale, M546_PARTICLEPARAM *param);
void fn_1_2E18(M546_WORK *work, s16 mdlNo, HuVecF pos);
void fn_1_301C(void);
void fn_1_38A0(void);
void fn_1_3E2C(M546_WORK *work, s16 mdlNo, HuVecF pos, s16 num);
void fn_1_4010(void);
void fn_1_487C(void);
void fn_1_4E00(void);
void fn_1_554C(void);
void fn_1_557C(void);
void fn_1_55AC(s16 bgmF, s16 speed);
void fn_1_5614(s16 bgmF);
void fn_1_5674(s16 no);
void fn_1_56EC(s16 no, s16 vol, s16 pan);
void fn_1_5774(s16 no, s16 pan);
void fn_1_5804(s16 no);
void fn_1_58B0(void);

/* game.c */
extern int lbl_1_bss_15290;
extern int lbl_1_bss_15294;
extern M546_WORK *lbl_1_bss_15288;

s32 fn_1_58D0(M546_WORK *work);
s32 fn_1_6A90(void);
s32 fn_1_6AC4(void);
s32 fn_1_6B2C(void);
s32 fn_1_6CD4(void);
s32 fn_1_6D14(void);
s32 fn_1_6D4C(void);
s32 fn_1_6E94(void);
s32 fn_1_6EC4(void);

/* stage.c */
void fn_1_B15C(M546_WORK *work, M546_MODEL *models, unsigned int *dataTbl);
void fn_1_B3A8(s16 stageNo);
void fn_1_B654(unsigned int *dataA, unsigned int *dataB);
void fn_1_B678(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_B69C(void);
void fn_1_B9B4(OMOBJ *obj);
void fn_1_BDCC(void);
void fn_1_BEF8(OMOBJ *obj);
void fn_1_C250(OMOBJ *obj);
void fn_1_C2A4(void);

#endif
