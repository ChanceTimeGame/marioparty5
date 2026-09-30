/*
 * The types m549.c, game.c, stage.c and cloud.c all need.
 *
 * m549dll is a KETTOU duel (overlay #63) on work head D of the duel stage
 * framework, REL/duelstage.h: three chr/motion slots, the PadRead-262 pad
 * block, stageDataTbl at 0x170, with the duellists moved by the actor manager
 * (game/mg/actman.h). The work is 0x804 and is the static lbl_1_bss_DD0
 * (2,052 bytes), not a heap allocation; stage.c's lbl_1_bss_1608 points at it
 * and game.c's lbl_1_bss_15F4 is a separate pointer to the same object.
 *
 * Every offset was measured off the reference objects rather than inherited
 * from m553 -- build/mp5-duelstage/20260915-m549-w0/FINDINGS.md (scan549.txt).
 * The work happens to match M553_WORK field for field; nothing else does.
 * Names that say unkNNN are unexplained, not unallocated.
 */
#ifndef M549_H
#define M549_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_628, 1,960 bytes). */
typedef DS_MODEL M549_MODEL;        /* 0x1C */

#define M549_MODEL_MAX 70

typedef DS_CHAR262 M549_CHAR;       /* 0x1C */

/*
 * One stage effect slot, the head-D 0x4C slot. Twenty-one fill the work from
 * 0x1C8 to 0x804: 0..8 the nine orbiting props, 9..12 the four turning ones,
 * 13 the light fn_1_134AC parks, 14..18 the big orbiter and its four
 * companions, 19 and 20 the two sky props.
 */
typedef DS_EFFECTD M549_EFFECT;     /* 0x4C */

typedef struct M549Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M549_CHAR chr[3];
    /* 0x058 */ M549_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];
    /* 0x188 */ u8 unk188[0x40];
    /* 0x1C8 */ M549_EFFECT effect[21];
} M549_WORK;                        /* 0x804 */

/* The cameras' state (bss_14, four allocated), from lbl_1_data_288. */
typedef struct M549Camera_s {
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
} M549_CAMERA;                      /* 0x50 */

typedef struct M549CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M549_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_10). */
typedef struct M549Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M549_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_C). */
typedef struct M549Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M549_SHADOW;                      /* 0x50 */

/* What fn_1_2F70 spawns a dust particle with (lbl_1_data_3F0, bss_15D8). */
typedef struct M549ParticleParam_s {
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
} M549_PARTICLEPARAM;               /* 0x38 */

/*
 * The duellists' actor-manager players (bss_0). +0x00 is the collision-map
 * model id fn_1_3B74 passes to MgActorColMapInit as an array, not a plain s16.
 */
typedef struct M549Actors_s {
    /* 0x00 */ HU3DMODELID colMdlId[1];
    /* 0x02 */ s16 pad02;
    /* 0x04 */ MGPLAYER *player[2];
} M549_ACTORS;                      /* 0x0C */

/* One stage object (bss_18); ten of them, spawned by a duellist collision. */
typedef struct M549StageObj_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 endF;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 wait;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 no;
    /* 0x0C */ float radius;
    /* 0x10 */ float size;
    /* 0x14 */ HuVecF pos;
} M549_STAGEOBJ;                    /* 0x20 */

/* One of the ten moving objects fn_1_7CC0 throws (bss_158). */
typedef struct M549Obj_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 state;
    /* 0x04 */ s16 mode;
    /* 0x06 */ s16 hitF;
    /* 0x08 */ s16 owner;
    /* 0x0A */ s16 deadF;
    /* 0x0C */ float angle;
    /* 0x10 */ s16 level;
    /* 0x12 */ s16 charge;
    /* 0x14 */ float range;
    /* 0x18 */ float scale;
    /* 0x1C */ float zScale;
    /* 0x20 */ float scaleSpeed;
    /* 0x24 */ HuVecF pos;
    /* 0x30 */ HuVecF vel;
} M549_OBJ;                         /* 0x3C */

/* One duellist's own state (bss_3B0, two of them). */
typedef struct M549Duellist_s {
    /* 0x000 */ s16 mode;           /* which of lbl_1_data_49C fn_1_762C runs */
    /* 0x002 */ s16 seqMode;        /* fn_1_A18C's per-duellist step */
    /* 0x004 */ s16 unk004;
    /* 0x006 */ s16 hookMode;       /* fn_1_99E8's step */
    /* 0x008 */ s16 unk008;
    /* 0x00A */ s16 unk00A;
    /* 0x00C */ s16 actMode;        /* fn_1_6048's step */
    /* 0x00E */ s16 motMode;        /* fn_1_67E0's step */
    /* 0x010 */ s16 fallMode;       /* fn_1_71B4's step */
    /* 0x012 */ s16 hitWait;
    /* 0x014 */ s16 loseF;
    /* 0x016 */ s16 unk016;
    /* 0x018 */ float stkXf;
    /* 0x01C */ float stkYf;
    /* 0x020 */ float scale;
    /* 0x024 */ char *itemHook;     /* CharModelItemHookGet's object name */
    /* 0x028 */ s16 padOffF;
    /* 0x02A */ s16 unk02A;
    /* 0x02C */ HuVecF pos;
    /* 0x038 */ HuVecF posOld;
    /* 0x044 */ HuVecF vel;
    /* 0x050 */ HuVecF velOld;
    /* 0x05C */ s16 chargeCnt;
    /* 0x05E */ s16 unk05E;
    /* 0x060 */ s16 chargeLv;       /* chargeCnt/30 */
    /* 0x062 */ s16 idleCnt;
    /* 0x064 */ float angle;
    /* 0x068 */ s16 hitType;
    /* 0x06A */ s16 hitObjF;
    /* 0x06C */ s16 hitStgF;
    /* 0x06E */ s16 comF;
    /* 0x070 */ s16 dif;
    /* 0x072 */ s16 unk072;
    /* 0x074 */ s16 unk074;
    /* 0x076 */ s16 unk076;
    /* 0x078 */ s16 waitCnt;
    /* 0x07A */ s16 hitCnt;
    /* 0x07C */ s16 chaseState;
    /* 0x07E */ s16 unk07E;
    /* 0x080 */ s16 targetF;
    /* 0x082 */ s16 targetFSave;
    /* 0x084 */ s16 chaseEndF;
    /* 0x086 */ s16 unk086;
    /* 0x088 */ HuVecF chasePos;
    /* 0x094 */ HuVecF chasePosSave;
    /* 0x0A0 */ float chaseRadius;
    /* 0x0A4 */ float chaseVelZ;
    /* 0x0A8 */ s16 subMode;
    /* 0x0AA */ s16 subWait;
    /* 0x0AC */ s16 unk0AC;
    /* 0x0AE */ s16 unk0AE;
    /* 0x0B0 */ s16 aimParam;
    /* 0x0B2 */ s16 comMode;
    /* 0x0B4 */ float distOther;
    /* 0x0B8 */ float distHome;
    /* 0x0BC */ float aimAngle;
    /* 0x0C0 */ float speedMul;
    /* 0x0C4 */ float speedBase;
    /* 0x0C8 */ s16 probA;
    /* 0x0CA */ s16 probB;
    /* 0x0CC */ s16 probC;
    /* 0x0CE */ s16 valD;
    /* 0x0D0 */ s16 valE;
    /* 0x0D2 */ s16 probF;
    /* 0x0D4 */ s16 probG;
    /* 0x0D6 */ s16 unk0D6;
    /* 0x0D8 */ u32 btn;
    /* 0x0DC */ u32 btnDown;
    /* 0x0E0 */ u32 stkX;
    /* 0x0E4 */ u32 stkY;
} M549_DUELLIST;                    /* 0xE8 */

/*
 * The overlay's game state (bss_580). seNo and seF are 11 entries each, which
 * is what lbl_1_data_428's twelve-entry sound table is indexed through; the
 * twelfth word is the table's trailing zero.
 */
typedef struct M549Game_s {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 timer;
    /* 0x08 */ float unk08;
    /* 0x0C */ u8 unk0C[0x014];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 winner;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ MGTIMER *mgTimer;
    /* 0x2C */ u8 unk2C[0x004];
    /* 0x30 */ s32 bgmNo;
    /* 0x34 */ s32 jingleNo;
    /* 0x38 */ u8 unk38[0x004];
    /* 0x3C */ s32 seNo[11];
    /* 0x68 */ s16 seF[11];
    /* 0x7E */ s16 pad7E;
} M549_GAME;                        /* 0x80 */

/* m549.c defines these; game.c, stage.c and cloud.c reach them. */
extern M549_ACTORS lbl_1_bss_0;
extern M549_SHADOW *lbl_1_bss_C;
extern M549_LIGHT *lbl_1_bss_10;
extern M549_CAMERA *lbl_1_bss_14;
extern M549_STAGEOBJ lbl_1_bss_18[10];
extern M549_OBJ lbl_1_bss_158[10];
extern M549_DUELLIST lbl_1_bss_3B0[2];
extern M549_GAME lbl_1_bss_580;
extern M549_WORK lbl_1_bss_DD0;
extern M549_CAMERAINIT lbl_1_data_288[4];

void fn_1_4AC(s16 no);
void fn_1_97C(s16 no);
void fn_1_EF4(void);
void fn_1_1124(void);
void fn_1_13FC(void);
void fn_1_1524(void);
s16 fn_1_18B0(float *value, float div, float start, float end);
s16 fn_1_19D0(float *value, float div, float start, float end);
MGTIMER *fn_1_1AEC(int type, int maxTime, int endTime, float x, float y);
void fn_1_1B60(MGTIMER *timer);
BOOL fn_1_1B8C(MGTIMER *timer);
void fn_1_1BB4(MGTIMER *timer);
void fn_1_23FC(void);
void fn_1_2550(HuVecF *pos);
void fn_1_28CC(HuVecF *pos, s16 side);
void fn_1_357C(void);
void fn_1_35AC(void);
void fn_1_35DC(s16 bgmF, s16 speed);
void fn_1_3644(s16 bgmF);
void fn_1_36A4(s16 no);
void fn_1_3754(s16 no, s16 vol, s16 pan);
void fn_1_3814(s16 no, s16 pan);
void fn_1_38A4(s16 no, s16 pitch);
void fn_1_3934(s16 no, s16 vol);
/* fn_1_39C4 is deliberately NOT declared here: retail's game.c calls it with a
 * second, ignored argument, which only an implicit declaration allows. */
void fn_1_3A8C(s16 no);
void fn_1_3B54(void);

/* game.c defines this; it is a separate pointer from stage.c's lbl_1_bss_1608. */
extern M549_WORK *lbl_1_bss_15F4;

/* game/mg/actman.c; not in actman.h. */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/* stage.c */
void fn_1_11BC0(M549_WORK *work, M549_MODEL *models, unsigned int *dataTbl);
void fn_1_11E0C(s16 stageNo);
void fn_1_12450(s16 no, unsigned int *data);
void fn_1_12470(s16 no, HU3DMOTID *id);
void fn_1_12490(void);
void fn_1_12494(OMOBJ *obj);
void fn_1_128AC(void);
void fn_1_12A60(OMOBJ *obj);
void fn_1_12E80(OMOBJ *obj);

/* cloud.c */
void fn_1_115A8(M549_WORK *work);

#endif /* M549_H */
