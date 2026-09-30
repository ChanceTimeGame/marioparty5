/*
 * The types m551.c, game.c and stage.c all need.
 *
 * m551dll is a KETTOU duel (overlay #65) on work head D of the duel stage
 * framework, REL/duelstage.h: m543's layout exactly (three chr/motion slots,
 * the PadRead-262 pad block, stageDataTbl at 0x170), with the duellists moved
 * by the actor manager (game/mg/actman.h). The work is 0x2E8.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M551_H
#define M551_H

#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_16D94, 0x914 = 83 of them). */
typedef DS_MODEL M551_MODEL;        /* 0x1C */

#define M551_MODEL_MAX 83

typedef DS_CHAR262 M551_CHAR;       /* 0x1C */

/* Fourteen motions per duellist; lbl_1_data_28 is one row per character. */
#define M551_MOTION_MAX 14

typedef struct M551Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M551_CHAR chr[3];
    /* 0x058 */ M551_MODEL *models;
    /* 0x05C */ unsigned int *charMotData[3];
    /* 0x068 */ HU3DMOTID *motId[3];
    /* 0x074 */ DS_PLAYER player[3];
    /* 0x170 */ unsigned int *stageDataTbl;
    /* 0x174 */ s16 stageNo;
    /* 0x176 */ s16 pad176;
    /* 0x178 */ int mode[4];
    /* 0x188 */ u8 unk188[0x160];
} M551_WORK;                        /* 0x2E8 */

/* The cameras' state (bss_38, four allocated plus eight bytes), from lbl_1_data_368. */
typedef struct M551Camera_s {
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
} M551_CAMERA;                      /* 0x50 */

typedef struct M551CameraInit_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ float zoom;
    /* 0x1C */ float aspect;
    /* 0x20 */ float vpX;
    /* 0x24 */ float vpY;
    /* 0x28 */ float vpW;
    /* 0x2C */ float vpH;
    /* 0x30 */ float fov;
} M551_CAMERAINIT;                  /* 0x34 */

/* The global light (bss_34). */
typedef struct M551Light_s {
    /* 0x00 */ HU3DLIGHTID id;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ HuVecF target;
    /* 0x28 */ HuVecF dir;
    /* 0x34 */ float dist;
    /* 0x38 */ GXColor color;
} M551_LIGHT;                       /* 0x3C */

/* The shadow camera (bss_30). */
typedef struct M551Shadow_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF target;
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ HuVecF up;
    /* 0x3C */ HuVecF unk3C;
    /* 0x48 */ float dist;
    /* 0x4C */ float tpLvl;
} M551_SHADOW;                      /* 0x50 */

/* What fn_1_3B58 spawns a particle with (lbl_1_data_4D0, bss_17998). */
typedef struct M551ParticleParam_s {
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
} M551_PARTICLEPARAM;               /* 0x38 */

/*
 * One of the thousand scraps of paper (bss_3C). fn_1_43F8 spawns them from
 * the emitter below, fn_1_4CB0 flies them and fn_1_5614 draws them; `no`
 * picks which of the emitter's four models and object names it is drawn as.
 */
typedef struct M551Paper_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 mode;            /* fn_1_4CB0's five-case switch */
    /* 0x04 */ s16 timer;
    /* 0x06 */ s16 no;              /* 0-3 */
    /* 0x08 */ s16 moveF;
    /* 0x0A */ s16 pad0A;
    /* 0x0C */ HuVecF pos;
    /* 0x18 */ HuVecF vel;
    /* 0x24 */ HuVecF rot;
    /* 0x30 */ HuVecF rotSpeed;
    /* 0x3C */ float restY;         /* the emitter's scale when it was spawned */
    /* 0x40 */ float tpLvl;
    /* 0x44 */ float color[3];      /* from lbl_1_data_508 */
    /* 0x50 */ float scale[3];      /* from lbl_1_data_538 */
} M551_PAPER;                       /* 0x5C */

#define M551_PAPER_MAX 1000

/* The paper emitter (bss_1679C): four models, their object names, and the rate. */
typedef struct M551PaperMan_s {
    /* 0x00 */ s16 activeF;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ float scale;
    /* 0x14 */ s16 wait;
    /* 0x16 */ s16 num;             /* how many fn_1_43F8 spawns in one call */
    /* 0x18 */ s16 cnt;
    /* 0x1A */ s16 total;
    /* 0x1C */ s16 pad1C;
    /* 0x1E */ HU3DMODELID mdlId[4];
    /* 0x26 */ char name[4][0x20];
    /* 0xA6 */ HU3DMODELID hookId;
} M551_PAPERMAN;                    /* 0xA8 */

/*
 * One duellist's state (bss_16A84), two of them. Every mode field is the
 * state of one sequence function, named after it.
 */
typedef struct M551Duellist_s {
    /* 0x000 */ s16 mode;           /* fn_1_9654 */
    /* 0x002 */ u8 unk002[0x0A];
    /* 0x00C */ float height;       /* CharModelHeightGet */
    /* 0x010 */ void *itemHook;     /* CharModelItemHookGet */
    /* 0x014 */ s16 unk014;
    /* 0x016 */ s16 pad016;
    /* 0x018 */ float nearDist;     /* fn_1_117CC's last distance to the panel */
    /* 0x01C */ float gravity;      /* the actor's own, kept to restore it */
    /* 0x020 */ s16 hitMode;        /* fn_1_A078 */
    /* 0x022 */ s16 effMode;        /* the panel effect's, fn_1_A5A4..fn_1_C680 */
    /* 0x024 */ s16 fadeMode;       /* fn_1_A758 */
    /* 0x026 */ s16 hitTimer;
    /* 0x028 */ s16 motF;           /* fn_1_C680: the second model's motion has been started */
    /* 0x02A */ s16 pad02A;
    /* 0x02C */ float velY;
    /* 0x030 */ float tpLvl;
    /* 0x034 */ s16 hitF;
    /* 0x036 */ s16 panelNo;        /* into lbl_1_bss_16844, -1 for none */
    /* 0x038 */ s16 attrF;
    /* 0x03A */ s16 pad03A;
    /* 0x03C */ s16 stopF;
    /* 0x03E */ s16 unk03E;
    /* 0x040 */ float tint;         /* fn_1_5958 scales the materials by it */
    /* 0x044 */ s8 *matColor;       /* fn_1_5860: the materials' colours */
    /* 0x048 */ HuVecF pos;
    /* 0x054 */ HuVecF oldPos;
    /* 0x060 */ HuVecF vel;         /* fn_1_D6A0's step toward chasePos */
    /* 0x06C */ float rotY;
    /* 0x070 */ float rotYStart;    /* fn_1_F814: the winner's facing before it turns */
    /* 0x074 */ s16 comF;
    /* 0x076 */ s16 comDif;         /* the character's difficulty, 0-3 */
    /* 0x078 */ u8 unk078[0x06];
    /* 0x07E */ s16 goMode;         /* fn_1_12510 */
    /* 0x080 */ s16 unk080;
    /* 0x082 */ s16 panelHit[12];   /* how often this duellist has landed on each panel */
    /* 0x09A */ s16 comRetryChance; /* fn_1_12178: per cent, divided by the panel's hits */
    /* 0x09C */ s16 comMarkChance;  /* fn_1_12178: marking a panel the rival has landed on */
    /* 0x09E */ s16 goTimer;
    /* 0x0A0 */ s16 comMode;        /* fn_1_11F4C's jumptable */
    /* 0x0A2 */ s16 pad0A2;
    /* 0x0A4 */ s16 thinkMode;      /* fn_1_12178 */
    /* 0x0A6 */ s16 unk0A6;
    /* 0x0A8 */ s16 chaseMode;      /* fn_1_13384 */
    /* 0x0AA */ s16 stkOnF;
    /* 0x0AC */ HuVecF chasePos;
    /* 0x0B8 */ float chaseSpeed;
    /* 0x0BC */ float chaseRadius;
    /* 0x0C0 */ s16 jumpMode;       /* fn_1_13620, fn_1_13AA4, fn_1_13F68 */
    /* 0x0C2 */ s16 pad0C2;
    /* 0x0C4 */ HuVecF goalPos;     /* the target panel's centre */
    /* 0x0D0 */ s16 jumpTimer;
    /* 0x0D2 */ s16 pad0D2;
    /* 0x0D4 */ int jumpStkX;
    /* 0x0D8 */ int jumpStkY;
    /* 0x0DC */ s16 punchMode;      /* fn_1_143DC */
    /* 0x0DE */ s16 punchTimer;
    /* 0x0E0 */ s16 kickMode;       /* fn_1_14974 */
    /* 0x0E2 */ s16 kickTimer;
    /* 0x0E4 */ s16 pad0E4;
    /* 0x0E6 */ s16 targetPanel;
    /* 0x0E8 */ s16 lastPanel;
    /* 0x0EA */ s16 pad0EA;
    /* 0x0EC */ s16 arriveF;        /* fn_1_14FC4: detouring through the centre */
    /* 0x0EE */ s16 stuckNo;        /* set by the collision, -1 for none */
    /* 0x0F0 */ s16 stuckNoOld;
    /* 0x0F2 */ s16 stuckTimer;
    /* 0x0F4 */ HuVecF arrivePos;
    /* 0x100 */ s16 arriveRadius;
    /* 0x102 */ s16 goType;         /* 1: fn_1_143DC, 2: fn_1_14974 */
    /* 0x104 */ s16 goTypeChance;   /* per cent, when the rival is within 150 */
    /* 0x106 */ s16 avoidF;
    /* 0x108 */ int btn;
    /* 0x10C */ int btnDown;
    /* 0x110 */ int stkX;
    /* 0x114 */ int stkY;
} M551_DUELLIST;                    /* 0x118 */

/* One of the twelve panels the duel is fought over (bss_16844). */
typedef struct M551Panel_s {
    /* 0x00 */ s16 mode;
    /* 0x02 */ s16 modeOld;
    /* 0x04 */ s16 moveF;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s16 no;              /* which of the five kinds it is */
    /* 0x0A */ s16 doneF;
    /* 0x0C */ s16 pad0C;
    /* 0x10 */ float destY;
    /* 0x14 */ float speedY;
    /* 0x18 */ u8 unk18[0x18];
} M551_PANEL;                       /* 0x30 */

/*
 * The duel's shared state (bss_16CB4). `winner` is `winner | (loser << 1)`
 * with 0 meaning no winner yet, so every read of it is `winner & 1`.
 */
typedef struct M551Game_s {
    /* 0x00 */ s16 mode;            /* fn_1_828C */
    /* 0x02 */ s16 unk02;           /* fn_1_EA8C: the rise step, then the roulette's direction */
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 timer;
    /* 0x08 */ float rotYEnd;       /* fn_1_F814: the facing the winner turns to */
    /* 0x0C */ u8 unk0C[0x04];
    /* 0x10 */ s16 spinPanel;       /* fn_1_EA8C's roulette: the lit panel */
    /* 0x12 */ s16 spinStart;
    /* 0x14 */ s16 spinIdx;
    /* 0x16 */ s16 pad16;
    /* 0x18 */ s16 winner;
    /* 0x1A */ s16 walkMode[2];     /* fn_1_D6A0, one per duellist */
    /* 0x1E */ s16 pad1E;
    /* 0x20 */ float walkRotY[2];   /* the facing each duellist turns to at its mark */
    /* 0x28 */ s16 walkMotF[2];     /* the duellist was moved, so its walk motion runs */
    /* 0x2C */ s16 walkTimer;
    /* 0x2E */ s16 walkStage;
    /* 0x30 */ s16 endTimer;
    /* 0x32 */ s16 spinCnt;
    /* 0x34 */ s16 panelKind[12];   /* the shuffled kind of each panel */
    /* 0x4C */ s16 centreSpot;      /* the spot whose panel kind is 0 */
    /* 0x4E */ s16 pad4E;
    /* 0x50 */ MGTIMER *mgTimer;
    /* 0x54 */ s16 timeUpF;
    /* 0x56 */ s16 mdlSel;          /* indexes lbl_1_bss_179A0 */
    /* 0x58 */ s16 loseRunF;        /* fn_1_F814: the loser runs to the centre */
    /* 0x5A */ s16 pad5A;
    /* 0x5C */ float tpLvl;
    /* 0x60 */ float ambColor;      /* Hu3DAmbColorSet */
    /* 0x64 */ float modelAmb;      /* Hu3DModelAmbSet on the winner */
    /* 0x68 */ u8 unk68[0x04];
    /* 0x6C */ int bgmNo;
    /* 0x70 */ int jingleNo;
    /* 0x74 */ u8 unk74[0x04];
    /* 0x78 */ int seNo[8];
    /* 0x98 */ s16 seF[8];
} M551_GAME;                        /* 0xA8 */

/* The duellists' actor-manager players and the collision models (bss_0). */
typedef struct M551Actors_s {
    /* 0x00 */ HU3DMODELID colMdlId[13];
    /* 0x1A */ u8 unk1A[0x0E];
    /* 0x28 */ MGPLAYER *player[2];
} M551_ACTORS;                      /* 0x30 */

/*
 * One panel's four models (bss_179A0), indexed by panel: mdlNo[0] the marker at its
 * centre, [1] the panel, [2] its effect, [3] its collision model. fn_1_5FF4 fills them
 * with 6+4*panel..9+4*panel.
 */
typedef struct M551Spot_s {
    /* 0x00 */ s16 mdlNo[4];
} M551_SPOT;                        /* 0x08 */

/* m551.c */
extern M551_ACTORS lbl_1_bss_0;
extern M551_SHADOW *lbl_1_bss_30;
extern M551_LIGHT *lbl_1_bss_34;
extern M551_CAMERA *lbl_1_bss_38;
extern M551_PAPER lbl_1_bss_3C[M551_PAPER_MAX];
extern M551_PAPERMAN lbl_1_bss_1679C;
extern M551_PANEL lbl_1_bss_16844[12];
extern M551_DUELLIST lbl_1_bss_16A84[2];
extern M551_GAME lbl_1_bss_16CB4;
extern M551_MODEL lbl_1_bss_16D94[M551_MODEL_MAX];
extern M551_WORK lbl_1_bss_176A8;
extern M551_CAMERAINIT lbl_1_data_368[4];
extern M551_PARTICLEPARAM lbl_1_data_4D0;

void fn_1_91C(s16 no);
void fn_1_10C4(void);
void fn_1_14C4(void);
s16 fn_1_1850(float *value, float div, float start, float end);
s16 fn_1_1970(int *value, int div, int start, int end);
MGTIMER *fn_1_1A44(int type, int maxTime, int endTime, float x, float y);
void fn_1_1AB8(MGTIMER *timer);
BOOL fn_1_1AE4(MGTIMER *timer);
void fn_1_1B0C(MGTIMER *timer);
void fn_1_2354(void);
void fn_1_2610(HuVecF *pos);
void fn_1_29DC(HuVecF *pos);
void fn_1_3270(HuVecF *pos);
s16 fn_1_3B58(float x, float y, float z, float scale, M551_PARTICLEPARAM *param, s16 no);
float fn_1_4150(void);
void fn_1_41C8(M551_WORK *work, s16 mdlNo, HuVecF *pos);
void fn_1_43CC(void);
void fn_1_43F8(void);
void fn_1_4CB0(void);
void fn_1_5860(s16 player);
s16 fn_1_5958(s16 player, float scale);
void fn_1_5AC8(s16 player);
void fn_1_5BC4(void);
void fn_1_5BF4(void);
void fn_1_5C24(s16 bgmF, s16 speed);
void fn_1_5C8C(s16 bgmF);
void fn_1_5CEC(s16 no);
void fn_1_5D64(s16 no, s16 vol, s16 pan);
void fn_1_5DEC(s16 no, s16 pan);
void fn_1_5E7C(s16 no);
void fn_1_5F28(s16 no);
void fn_1_5FD4(void);

/* game.c -- defined there, but lbl_1_bss_17998 and lbl_1_bss_1799C are used only by m551.c's
 * particle code; moving them into m551.c would shift every .bss address. */
extern M551_PARTICLEPARAM *lbl_1_bss_17998;
extern HU3DMODELID lbl_1_bss_1799C[2];
extern M551_SPOT lbl_1_bss_179A0[12];
extern M551_WORK *lbl_1_bss_17A00;

/* game/mg/actman.c; not in actman.h. */
void MgActorPosGet(MGACTOR *actorP, HuVecF *pos);

/* stage.c */
void fn_1_169F4(M551_WORK *work, M551_MODEL *models, unsigned int *dataTbl);
void fn_1_16C40(s16 stageNo);
void fn_1_16C54(s16 no, unsigned int *data);
void fn_1_16C74(s16 no, HU3DMOTID *id);
void fn_1_16C94(void);
void fn_1_16C98(OMOBJ *obj);
void fn_1_170B0(void);
void fn_1_17264(OMOBJ *obj);

#endif
