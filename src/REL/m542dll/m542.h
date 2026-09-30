/*
 * The types m542.c, game.c and stage.c all need.
 *
 * m542dll is a KETTOU duel (overlay #56) on work head B of the duel stage
 * framework, REL/duelstage.h, like m548dll and m547dll: the duel head to
 * `motId`, two DS_PLAYERB slots, `stageDataTbl` at 0x98. The work is 0x154.
 *
 * Offsets come from every access in the reference assembly (NOTES.md). Names
 * that say unkNNN are unexplained, not unallocated.
 */
#ifndef M542_H
#define M542_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/* The duel stage framework's types; stage.c includes its functions. */
#include "REL/duelstage.h"

/* One entry of the retained-mode model table (bss_1588). */
typedef DS_MODEL M542_MODEL;        /* 0x1C */

#define M542_MODEL_MAX 34

typedef DS_CHAR M542_CHAR;          /* 0x1C */
typedef DS_PLAYERB M542_PLAYER;     /* 0x24 */

typedef struct M542Work_s {
    /* 0x000 */ OMOBJMAN *objman;
    /* 0x004 */ M542_CHAR chr[2];
    /* 0x03C */ M542_MODEL *models;
    /* 0x040 */ unsigned int *charMotData[2];
    /* 0x048 */ HU3DMOTID *motId[2];
    /* 0x050 */ M542_PLAYER player[2];
    /* 0x098 */ unsigned int *stageDataTbl;
    /* 0x09C */ s16 stageNo;
    /* 0x09E */ s16 pad09E;
    /* 0x0A0 */ int mode[4];        /* mode[0] indexes the sub-state tables data_27C/28C/29C */
    /* 0x0B0 */ int winMode;         /* pre-winner stage (fn_1_5D30, fn_1_6A30) */
    /* 0x0B4 */ int clock[2];        /* frames each clock has run; 600 reads 0, over 600 is a bust */
    /* 0x0BC */ int unkBC;
    /* 0x0C0 */ int mesTimer;        /* frames the result message has shown */
    /* 0x0C4 */ int jump[2][4];      /* [0] jump state (fn_1_4008), [1] its timer */
    /* 0x0E4 */ int sparkDelay[2];   /* frames to the next counter-spark stream */
    /* 0x0EC */ int alarmTimer[2];   /* rings the alarm clock every 50 (33 once decided) frames */
    /* 0x0F4 */ float alarmTime[2];  /* the alarm model's motion time; 99 bursts it */
    /* 0x0FC */ int wobble[2][2];    /* board wobble angles in degrees */
    /* 0x10C */ u8 unk10C[0x1C];
    /* 0x128 */ HuVecF jumpSpeed[2]; /* .x only; retail fn_1_771C(-1) writes [1].y's bytes */
    /* 0x140 */ u8 unk140[0x14];
} M542_WORK;                        /* 0x154 */

/* bss_14: one per duellist; the computer player's state (fn_1_4994, 4B50, 4D48). */
typedef struct M542Com_s {
    /* 0x00 */ s16 dif;             /* 0-3 */
    /* 0x02 */ s16 pad02;
    /* 0x04 */ int mode;
    /* 0x08 */ int timer;
    /* 0x0C */ int holdTime;        /* frames to hold A in the jump */
    /* 0x10 */ int diveTime;        /* frame to press A again to dive; 0 for an idle hop */
    /* 0x14 */ int stopClock;       /* the clock value it aims to land its dive at */
    /* 0x18 */ int hopDelay;        /* frames to the next idle hop */
} M542_COM;                         /* 0x1C */

/* bss_E8 element: four groups of thirty effect particles (fn_1_7E90..835C, fn_1_D3C). */
typedef struct M542Particle_s {
    /* 0x00 */ int mode;            /* live when non-zero */
    /* 0x04 */ int timer;
    /* 0x08 */ u8 unk08[0x04];
    /* 0x0C */ float angle;         /* offset from the emitter's angle */
    /* 0x10 */ HU3DMODELID modelId;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ HuVecF pos;
    /* 0x20 */ HuVecF rot;
} M542_PARTICLE;                    /* 0x2C */

/* bss_1AA8: one emitter per particle group (fn_1_771C..8180). */
typedef struct M542Emitter_s {
    /* 0x00 */ int active;
    /* 0x04 */ int mode;            /* 0-3 a spark stream, 4/5 start the alarm burst, 6 run it */
    /* 0x08 */ int next;            /* next particle slot */
    /* 0x0C */ int timer;
    /* 0x10 */ float angle;
    /* 0x14 */ HuVecF pos;
} M542_EMITTER;                     /* 0x20 */

/* m542.c */
extern s32 lbl_1_bss_4;
extern s32 lbl_1_bss_C;
extern M542_COM lbl_1_bss_14[2];
extern OMCAMERAVIEW lbl_1_bss_78[4];

/* game.c */
extern M542_PARTICLE lbl_1_bss_E8[4][30];
extern M542_MODEL lbl_1_bss_1588[M542_MODEL_MAX];
extern s16 lbl_1_bss_1940[2][5];     /* texture-scroll ids per duellist: counter digits 0-3, burst 4 */
extern M542_WORK lbl_1_bss_1954;
extern HuVecF lbl_1_data_3B0[6];

void fn_1_2858(void);
void fn_1_2978(void);
void fn_1_2A14(void);
void fn_1_2AD0(void);
void fn_1_2BDC(void);
void fn_1_2DAC(void);
void fn_1_2F90(void);
void fn_1_5120(void);
void fn_1_5420(void);
void fn_1_5D30(void);
void fn_1_6A30(void);
void fn_1_737C(void);

/* stage.c */
void fn_1_84D0(M542_WORK *work, M542_MODEL *models, unsigned int *dataTbl);
void fn_1_871C(s16 stageNo);
void fn_1_89DC(unsigned int *dataA, unsigned int *dataB);
void fn_1_8A00(HU3DMOTID *idA, HU3DMOTID *idB);
void fn_1_8A24(void);
void fn_1_8C94(OMOBJ *obj);
void fn_1_9150(void);
void fn_1_92A4(OMOBJ *obj);
void fn_1_94B4(OMOBJ *obj);

#endif
