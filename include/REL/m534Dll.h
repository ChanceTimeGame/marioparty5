#ifndef M534DLL_H
#define M534DLL_H

/*
 * m534dll (MG_TYPE_2VS2, overlay #48): types and prototypes shared by its six
 * translation units (m534, camera, player, stage, effect, score).
 *
 * No seqman and no mgframe.h: ObjectSetup builds the light, shadow and camera
 * itself, creates the main object (fn_1_36C, data M534_MAIN) and hands the
 * rest to score.c, effect.c, stage.c and player.c. The main object's objFunc
 * steps through fn_1_648 .. fn_1_1364; fn_1_19E8 and fn_1_1DF4 set up a camera
 * or result phase and return the object function to install next.
 *
 * Offsets are GameCube ones from build/mp5-asm/m534Dll. No upstream names
 * exist, so functions keep reference addresses and globals lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "humath.h"

/* 0x60 bytes: the main object's work (fn_1_36C). */
typedef struct M534Main_s {
    /* 0x00 */ s32 mode;
    /* 0x04 */ s32 time;
    /* 0x08 */ s32 flag;
    /* 0x0C */ u32 camMode;             /* opening camera phase (fn_1_1A74) */
    /* 0x10 */ u32 camTime;
    /* 0x14 */ s32 playMode;            /* start/play/finish phase (fn_1_E28 .. fn_1_1364) */
    /* 0x18 */ s32 playTime;
    /* 0x1C */ s32 resultMode;          /* result phase (fn_1_1F1C) */
    /* 0x20 */ u32 resultTime;
    /* 0x24 */ u32 team[4];             /* per player, set by fn_1_1800 */
    /* 0x34 */ s32 charNo[4];           /* per player, set by fn_1_1800 */
    /* 0x44 */ s32 winner[4];           /* charNo or -1 */
    /* 0x54 */ u32 winTeam;             /* 0 draw, 1 or 2 */
    /* 0x58 */ u32 bits58;              /* fn_1_173C: bit per player */
    /* 0x5C */ u32 bits5C;              /* fn_1_176C: bit per player */
} M534_MAIN;

/* 0x60 bytes per player object (fn_1_245C). */
typedef struct M534Player_s {
    /* 0x00 */ s32 no;
    /* 0x04 */ s32 team;
    /* 0x08 */ s32 slot;                /* row of lbl_1_data_160 */
    /* 0x0C */ s32 charNo;
    /* 0x10 */ s32 motNo;               /* row of lbl_1_data_110, -1 for none */
    /* 0x14 */ u32 btnDown;
    /* 0x18 */ u32 btn;
    /* 0x1C */ s32 com;
    /* 0x20 */ float comDelay;
    /* 0x24 */ float comTime;
    /* 0x28 */ s32 mode;
    /* 0x2C */ s32 time;
    /* 0x30 */ s32 frame;
    /* 0x34 */ s32 pressed;
    /* 0x38 */ s32 pressTime;           /* frames since the last press */
    /* 0x3C */ float speed;
    /* 0x40 */ HuVecF pos;
    /* 0x4C */ float rotY;
    /* 0x50 */ float scaleY;
    /* 0x54 */ float scaleXZ;
    /* 0x58 */ s32 squashed;
    /* 0x5C */ s32 fxPlayed;
} M534_PLAYER;

/* 0x14 bytes: one row of lbl_1_data_110. */
typedef struct M534Motion_s {
    /* 0x00 */ u16 motNo;
    /* 0x02 */ u16 pad;
    /* 0x04 */ float shift;
    /* 0x08 */ float start;
    /* 0x0C */ float end;
    /* 0x10 */ u32 attr;
} M534_MOTION;

/* 0x8 bytes: a playing stage sound. */
typedef struct M534Sound_s {
    /* 0x00 */ s32 seNo;                /* -1 when free */
    /* 0x04 */ s32 seId;                /* HuAudFXPlay id, -1 when free */
} M534_SOUND;

/* 0x200 bytes: the stage object's work (fn_1_3360). */
typedef struct M534Stage_s {
    /* 0x000 */ M534_SOUND sound[32];
    /* 0x100 */ HuVecF propPos[5];
    /* 0x13C */ float propSpeed[5];
    /* 0x150 */ s32 effectActive[16];   /* mdlId[10 + i] is playing its one-shot motion */
    /* 0x190 */ float buttonY[4];       /* rest height of lbl_1_data_2C8[i] */
    /* 0x1A0 */ float buttonOfs[4];     /* press offset, halves every frame */
    /* 0x1B0 */ s32 splashActive;       /* mdlId[4] is playing its motion */
    /* 0x1B4 */ s32 mode;
    /* 0x1B8 */ s32 time;
    /* 0x1BC */ s32 seId;
    /* 0x1C0 */ s32 spray;              /* spray particles per frame, counts down */
    /* 0x1C4 */ s32 pressCount;
    /* 0x1C8 */ float footAmp;
    /* 0x1CC */ float footAngle;
    /* 0x1D0 */ float bodyAmp;
    /* 0x1D4 */ float bodyAngle;
    /* 0x1D8 */ float speed;
    /* 0x1DC */ float centerY;          /* camera Center.y before the shake */
    /* 0x1E0 */ float shake;
    /* 0x1E4 */ float shakeAngle;
    /* 0x1E8 */ float rate;
    /* 0x1EC */ float targetY;
    /* 0x1F0 */ float curY;
    /* 0x1F4 */ float rotX;
    /* 0x1F8 */ float rotY;
    /* 0x1FC */ float rotZ;
} M534_STAGE;

/* 0x18 bytes: one row of lbl_1_data_190. */
typedef struct M534Prop_s {
    /* 0x00 */ u32 dataNum;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ float scale;
    /* 0x14 */ float speed;
} M534_PROP;

/* 0x40 bytes per team (fn_1_6BDC allocates two). */
typedef struct M534Score_s {
    /* 0x00 */ s32 mode;
    /* 0x04 */ float t;
    /* 0x08 */ float amp;               /* bob radius */
    /* 0x0C */ float angle;             /* bob angle, degrees */
    /* 0x10 */ HuVecF pos;
    /* 0x1C */ HuVecF vel;
    /* 0x28 */ HuVecF rot;
    /* 0x34 */ s32 score;
    /* 0x38 */ s16 animId[3];           /* hundreds, tens, ones */
    /* 0x3E */ s16 pad;
} M534_SCORE;

/* 0x18 bytes: one row of lbl_1_data_50. */
typedef struct M534CamView_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;              /* x, y rotation; z is the zoom */
} M534_CAMVIEW;

/* m534.c */
void ObjectSetup(void);
void fn_1_36C(OMOBJ *obj);
void fn_1_444(OMOBJ *obj);
void fn_1_518(OMOBJ *obj);
void fn_1_648(OMOBJ *obj);
void fn_1_924(OMOBJ *obj);
void fn_1_C1C(OMOBJ *obj);
void fn_1_E28(OMOBJ *obj);
void fn_1_10F0(OMOBJ *obj);
void fn_1_1364(OMOBJ *obj);
u32 fn_1_1694(void);
u32 fn_1_16AC(void);
u32 fn_1_16C4(void);
u32 fn_1_16DC(void);
void fn_1_16F4(s32 winTeam);
s32 fn_1_170C(s32 no);
void fn_1_173C(s32 no);
void fn_1_176C(s32 no);
BOOL fn_1_179C(void);
BOOL fn_1_17C8(void);
void fn_1_1800(s32 no, s32 team, s32 charNo);

/* camera.c */
s32 fn_1_1840(float x);
s32 fn_1_189C(HuVecF *pos);
s32 fn_1_1930(s32 seNo, HuVecF *pos);
OMOBJFUNC fn_1_19E8(OMOBJMAN *objman);
void fn_1_1A74(OMOBJ *obj);
OMOBJFUNC fn_1_1DF4(OMOBJMAN *objman, OMOBJ *obj);
void fn_1_1F1C(OMOBJ *obj);
void fn_1_2130(s32 from, s32 to, float t);

/* player.c */
void fn_1_2290(OMOBJMAN *objman);
void fn_1_2438(void);
void fn_1_245C(OMOBJ *obj);
void fn_1_2768(OMOBJ *obj);
void fn_1_2968(OMOBJ *obj);
void fn_1_2C50(OMOBJ *obj);
void fn_1_2CB4(OMOBJ *obj);
void fn_1_2CB8(OMOBJ *obj);
void fn_1_2E4C(OMOBJ *obj);
void fn_1_2EB8(OMOBJ *obj);
void fn_1_2F88(OMOBJ *obj, u32 motNo);
BOOL fn_1_3118(OMOBJ *obj);
BOOL fn_1_318C(OMOBJ *obj, u32 motNo);

/* stage.c */
void fn_1_3360(OMOBJMAN *objman);
void fn_1_33E8(void);
void fn_1_33EC(OMOBJ *obj);
void fn_1_3624(OMOBJ *obj);
void fn_1_3674(s16 mdlId, s16 no);
void fn_1_3AC8(OMOBJ *obj);
void fn_1_3B1C(OMOBJ *obj);
void fn_1_3BA8(OMOBJ *obj, s32 seNo);
void fn_1_3C1C(OMOBJ *obj, s32 seNo, s32 time);
void fn_1_3CAC(HU3DMODEL *model, Mtx *mtx);
void fn_1_3D58(HU3DMODEL *model, Mtx *mtx);
void fn_1_3E04(OMOBJ *obj);
void fn_1_3F04(OMOBJ *obj);
void fn_1_3FA0(OMOBJ *obj);
void fn_1_406C(OMOBJ *obj);
void fn_1_4114(s32 slot);
void fn_1_426C(OMOBJ *obj);
void fn_1_430C(OMOBJ *obj);
void fn_1_43D4(s32 slot);
void fn_1_4450(OMOBJ *obj);
void fn_1_449C(s32 team);
s32 fn_1_4624(void);
float fn_1_46A8(void);
float fn_1_4848(void);
void fn_1_4970(void);
BOOL fn_1_49BC(void);
BOOL fn_1_49FC(void);
void fn_1_4A3C(OMOBJ *obj);
void fn_1_5B64(void);
void fn_1_5CB0(s32 num);
void fn_1_5E20(s32 num, HuVecF *pos);
void fn_1_5F94(void);

/* effect.c */
void fn_1_6314(OMOBJMAN *objman);
void fn_1_6338(void);
void fn_1_633C(void);
void fn_1_6458(HuVecF *pos);
void fn_1_64EC(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_681C(void);
void fn_1_6938(HuVecF *pos, HuVecF *vel);
void fn_1_69E4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

/* score.c */
void fn_1_6BDC(OMOBJMAN *objman);
void fn_1_6C74(void);
void fn_1_6C78(OMOBJ *obj);
void fn_1_6CBC(OMOBJ *obj);
void fn_1_6CF4(OMOBJ *obj);
void fn_1_6DEC(OMOBJ *obj);
void fn_1_6EE0(OMOBJ *obj);
void fn_1_6FE8(OMOBJ *obj);
void fn_1_74B0(s32 team, s32 add);
s32 fn_1_74E8(s32 team);

#endif
