#ifndef M514DLL_H
#define M514DLL_H

/*
 * m514dll (MG_TYPE_4P, overlay #28): types and prototypes shared by its six
 * translation units (m514, player, object, stage, effect, score).
 *
 * Offsets are GameCube ones from build/mp5-asm/m514Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels; work-struct
 * fields are named by hex offset.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"
#include "game/sprite.h"
#include "game/mg/score.h"

typedef struct M514Stage_s {
    float unk000; /* x offset of the fn_1_585C quad (fn_1_9794 result) */
} M514_STAGE;

typedef struct M514FogParam_s {
    float unk000;    /* fog start */
    float unk004;    /* fog end, scaled by lbl_1_bss_214 */
    GXColor unk008;  /* fog / background colour */
} M514_FOGPARAM;

typedef struct M514_Main {
    s32 unk000;        /* camera motion running: 1 set by fn_1_163C, 0 by fn_1_9E4; cmpwi only */
    HU3DMOTID unk004;  /* Hu3DMotionCreate result (lha) */
    HU3DMODELID unk006; /* Hu3DModelCameraCreate result (lha) */
} M514_MAIN;

typedef struct M514Player_s {
    /* 0x000 */ s32 unk000;     /* player number (obj->work[0]) */
    /* 0x004 */ u32 unk004;     /* GwPlayerConf[no].grp (obj->work[1]); unsigned per fork D: fn_1_41C4 cmplw */
    /* 0x008 */ s32 unk008;     /* start slot (obj->work[2]) */
    /* 0x00C */ u32 unk00C;     /* charNo; unsigned: fn_1_2D10 cmplwi 8 */
    /* 0x010 */ u32 unk010;     /* HuPadBtnDown */
    /* 0x014 */ u32 unk014;     /* HuPadBtn */
    /* 0x018 */ float unk018;
    /* 0x01C */ float unk01C;
    /* 0x020 */ s32 unk020;     /* GwPlayerConf[no].type (COM flag) */
    /* 0x024 */ s32 unk024;     /* GwPlayerConf[no].dif & 3 */
    /* 0x028 */ s32 unk028;
    /* 0x02C */ s32 unk02C;
    /* 0x030 */ s32 unk030;     /* state (switch) */
    /* 0x034 */ s32 unk034;     /* state timer */
    /* 0x038 */ s32 unk038;     /* frame counter */
    /* 0x03C */ s32 unk03C;     /* current motion, -1 = none */
    /* 0x040 */ HuVecF unk040;  /* position */
    /* 0x04C */ HuVecF unk04C;  /* velocity */
    /* 0x058 */ float unk058;   /* facing angle, degrees */
    /* 0x05C */ float unk05C;
    /* 0x060 */ float unk060;
    /* 0x064 */ s32 unk064;
    /* 0x068 */ s32 unk068;     /* active (pushed apart by fn_1_1ED4) */
    /* 0x06C */ s32 unk06C;
    /* 0x070 */ s32 unk070;
    /* 0x074 */ s32 unk074;
    /* 0x078 */ s32 unk078;     /* footstep side toggle, 0/1 */
    /* 0x07C */ s32 unk07C;
    /* 0x080 */ s32 unk080;
    /* 0x084 */ s32 unk084;
    /* 0x088 */ s32 unk088;
    /* 0x08C */ s32 unk08C;
    /* 0x090 */ s32 unk090;     /* effect id handed to fn_1_7C10, -1 */
    /* 0x094 */ s32 unk094;     /* -1 */
} M514_PLAYER;

typedef struct M514Motion_s {
    /* 0x00 */ u16 unk00;           /* index into OMOBJ::mtnId (read with lhz) */
    /* 0x04 */ float unk04;         /* shift time, seconds */
    /* 0x08 */ u32 unk08;           /* HU3D_MOTATTR_* */
} M514_MOTION;

typedef struct M514Jump_s {
    /* 0x00 */ s32 unk00;           /* crouch frames before take-off */
    /* 0x04 */ float unk04;         /* take-off velocity x */
    /* 0x08 */ float unk08;         /* take-off velocity y */
    /* 0x0C */ float unk0C;         /* button boost x */
    /* 0x10 */ float unk10;         /* button boost y while rising */
    /* 0x14 */ float unk14;         /* button boost y while falling */
    /* 0x18 */ float unk18;         /* distance past which the fall is sped up */
} M514_JUMP;

typedef struct M514ComTime_s {
    /* 0x00 */ float unk00;         /* first-press delay base, frames */
    /* 0x04 */ float unk04;         /* first-press delay random range */
    /* 0x08 */ float unk08;         /* repeat delay base */
    /* 0x0C */ float unk0C;         /* repeat delay random range */
} M514_COMTIME;

typedef struct M514_ObjMot_s {
    /* 0x000 */ s32 unk000; /* data number; -1 skip, -2 end */
    /* 0x004 */ float unk004; /* blend length in seconds */
    /* 0x008 */ u32 unk008; /* motion attribute */
} M514_OBJMOT;

typedef struct M514_ObjData_s {
    /* 0x000 */ s32 unk000; /* kind 0..4; -1 terminates */
    /* 0x004 */ s32 unk004; /* index into lbl_1_data_45C */
    /* 0x008 */ s32 unk008; /* model data number */
    /* 0x00C */ M514_OBJMOT *unk00C;
    /* 0x010 */ HuVecF *unk010; /* position */
    /* 0x014 */ float unk014; /* rotation Y */
    /* 0x018 */ OMOBJFUNC unk018; /* object init */
} M514_OBJDATA;

typedef struct M514_ObjMan_s {
    /* 0x000 */ s32 unk000;
} M514_OBJMAN;

typedef struct M514_Object_s {
    /* 0x000 */ M514_OBJDATA *unk000;
    /* 0x004 */ s32 unk004; /* state */
    /* 0x008 */ s32 unk008; /* timer */
    /* 0x00C */ u8 unk00C[4];
    /* 0x010 */ s32 unk010; /* current motion, -1 none */
    /* 0x014 */ s32 unk014; /* sound, -1 none */
    /* 0x018 */ s32 unk018; /* sound, -1 none */
    /* 0x01C */ HuVecF unk01C; /* position */
    /* 0x028 */ HuVecF unk028; /* velocity */
    /* 0x034 */ HuVecF unk034; /* rotation */
    /* 0x040 */ u8 unk040[4];
    /* 0x044 */ s32 unk044;
    /* 0x048 */ u8 unk048[0x10];
} M514_OBJECT;

typedef struct m514Effect_s {
    /* 0x00 */ s32 unk000;     /* banner state 0/1/2 (cmpwi) */
    /* 0x04 */ s32 unk004;     /* not touched by fork G */
    /* 0x08 */ float unk008;   /* banner transparency */
    /* 0x0C */ s16 unk00C;     /* HUSPRGRPID */
    /* 0x0E */ s16 unk00E;     /* not touched by fork G */
    /* 0x10 */ float unk010;   /* banner scale */
    /* 0x14 */ s16 unk014;     /* requested bank, <0 hides (cmpwi 0 / blt) */
    /* 0x16 */ s16 unk016;     /* bank last applied */
    /* 0x18 */ s32 unk018;     /* not touched by fork G */
} M514_EFFECT;

typedef struct m514Effect0_s {
    /* 0x00 */ s32 unk000;     /* state (cmpwi) */
    /* 0x04 */ s32 unk004;     /* not touched by fork G */
    /* 0x08 */ s32 unk008;     /* spawn countdown (cmpwi 0 / bgt) */
    /* 0x0C */ float unk00C;
    /* 0x10 */ float unk010;
    /* 0x14 */ float unk014;
    /* 0x18 */ float unk018;   /* not touched by fork G */
    /* 0x1C */ float unk01C;
    /* 0x20 */ float unk020;
    /* 0x24 */ float unk024;   /* highest y seen */
    /* 0x28 */ float unk028;
    /* 0x2C */ HuVecF unk02C;  /* start position */
    /* 0x38 */ HuVecF unk038;  /* smoothed position */
} M514_EFFECT0;

typedef struct m514Effect0work_s {
    /* 0x000 */ M514_EFFECT0 unk000[3];
} M514_EFFECT0WORK;   /* mdlId[0] hook data, 0xCC (fn_1_5C34) */

typedef struct m514Effect1data_s {
    /* 0x00 */ s32 unk000;     /* in use (cmpwi) */
    /* 0x04 */ s32 unk004;     /* frand() phase; used as (x++ & 0x1F), sign-neutral */
    /* 0x08 */ s32 unk008;     /* frand() phase */
    /* 0x0C */ s32 unk00C;     /* frand() phase */
    /* 0x10 */ u32 unk010;     /* RGBA8 colour, channels byte-addressed */
    /* 0x14 */ float unk014;
    /* 0x18 */ HuVecF unk018;
} M514_EFFECT1DATA;

typedef struct m514Effect1_s {
    /* 0x000 */ ANIMDATA *unk000;
    /* 0x004 */ M514_EFFECT1DATA unk004[256];
} M514_EFFECT1;

typedef struct m514Effect2data_s {
    /* 0x00 */ s32 unk000;     /* state 0..4 (switch, cmpwi) */
    /* 0x04 */ s32 unk004;     /* hold timer (xoris int->double: signed) */
    /* 0x08 */ float unk008;   /* radius */
    /* 0x0C */ u32 unk00C;     /* RGBA8 vertex colour; byte 3 is the alpha that fades */
    /* 0x10 */ HuVecF unk010;  /* world position */
} M514_EFFECT2DATA;

typedef struct m514Effect2_s {
    /* 0x0000 */ M514_EFFECT2DATA unk000[512];
    /* 0x3800 */ float unk3800[16];   /* sin(i * 22 deg) */
    /* 0x3840 */ float unk3840[16];   /* cos(i * 22 deg) */
} M514_EFFECT2;

typedef struct m514ScorePl_s {
    /* 0x000 */ s32 unk000;         /* score: signed /100 and %100, cmpw */
    /* 0x004 */ s32 unk004;         /* rank slot 0..3 (sorted by unk000) */
    /* 0x008 */ HUSPRGRPID unk008;  /* MgScoreWin group (lhax) */
    /* 0x00A */ HUSPRGRPID unk00A;  /* icon sprite group, 3 members (lhax) */
    /* 0x00C */ MGSCORE *unk00C;    /* hundreds readout, 3 digits */
    /* 0x010 */ MGSCORE *unk010;    /* last two digits */
    /* 0x014 */ HuVec2f unk014;     /* current position */
    /* 0x01C */ HuVec2f unk01C;     /* target position (lbl_1_data_53C[rank]) */
} M514_SCOREPL;

typedef struct m514Score_s {
    /* 0x000 */ s32 unk000;         /* fade state 0..2 (switch) */
    /* 0x004 */ s32 unk004;         /* never accessed */
    /* 0x008 */ float unk008;       /* fade level 0..1 */
    /* 0x00C */ M514_SCOREPL unk00C[4];
    /* 0x09C */ s32 unk09C;         /* record-readout state 0..4 (switch) */
    /* 0x0A0 */ s32 unk0A0;         /* pulse timer: cmpwi, xoris int->float */
    /* 0x0A4 */ s32 unk0A4;         /* record: signed /100, cmpw */
    /* 0x0A8 */ s32 unk0A8;         /* record at start / last shown: xoris */
    /* 0x0AC */ HUSPRGRPID unk0AC;  /* record MgScoreWin */
    /* 0x0AE */ HUSPRGRPID unk0AE;  /* record icon group */
    /* 0x0B0 */ MGSCORE *unk0B0;
    /* 0x0B4 */ MGSCORE *unk0B4;
} M514_SCORE;

/* --- m514.c --- */
void ObjectSetup(void);
void fn_1_3A0(s16 mode, s16 frameNo);
void fn_1_448(s16 mode, s16 frameNo);
void fn_1_540(s16 mode, s16 frameNo);
void fn_1_580(s16 mode, s16 frameNo);
void fn_1_600(s16 mode, s16 frameNo);
void fn_1_7B0(s16 mode, s16 frameNo);
void fn_1_8A0(s16 mode, s16 frameNo);
void fn_1_958(s16 mode, s16 frameNo);
void fn_1_95C(s16 mode, s16 frameNo);
void fn_1_98C(OMOBJ *obj);
void fn_1_9E4(OMOBJ *obj);
void fn_1_14F4(HuVecF *dir, HuVecF *target, float dist);
void fn_1_163C(void *data);
s32 fn_1_16AC(void);
s16 fn_1_16DC(void);
s32 fn_1_16EC(s32 no);
s32 fn_1_1704(u32 no);
s32 fn_1_1814(void);
void fn_1_1824(s32 no);
void fn_1_1838(s32 no, s32 arg1, s32 charNo);
void fn_1_1870(s32 no);
void fn_1_1890(s32 no);
s32 fn_1_1904(float x);
s32 fn_1_1960(HuVecF *pos);
s32 fn_1_19F4(HuVecF *pos);
s32 fn_1_1A18(s32 seNo, HuVecF *pos);
void fn_1_1AF4(s32 seId, HuVecF *pos);
float fn_1_1BCC(float cur, float target, float rate);
float fn_1_1CE8(float from, float to);

/* --- player.c --- */
void fn_1_1D9C(OMOBJMAN *objman);
void fn_1_1EA0(void);
void fn_1_1EC4(OMOBJ *obj);
void fn_1_1ED4(OMOBJ *obj);
void fn_1_20E0(OMOBJ *obj);
void fn_1_22C8(OMOBJ *obj);
void fn_1_2338(OMOBJ *obj);
void fn_1_284C(OMOBJ *obj);
void fn_1_2A88(OMOBJ *obj);
void fn_1_2BC8(OMOBJ *obj, HuVecF *out, s32 side);
void fn_1_2D10(OMOBJ *obj, s32 side);
void fn_1_2E88(OMOBJ *obj);
void fn_1_2E8C(OMOBJ *obj);
void fn_1_37CC(OMOBJ *obj, s32 type);
BOOL fn_1_387C(OMOBJ *obj, HuVecF *target, float rotY, s32 useX);
void fn_1_3CF8(OMOBJ *obj);
void fn_1_3D6C(OMOBJ *obj);
void fn_1_3EC0(OMOBJ *obj, u32 motNo);
BOOL fn_1_3FB8(OMOBJ *obj);
BOOL fn_1_4024(OMOBJ *obj);
BOOL fn_1_4084(OMOBJ *obj, u32 motNo);
BOOL fn_1_41C4(u32 grp);
float fn_1_4238(s32 no);

/* --- object.c --- */
void fn_1_4270(OMOBJMAN *objman);
void fn_1_4344(void);
void fn_1_4348(OMOBJ *obj);
void fn_1_4358(OMOBJ *obj);
void fn_1_435C(void);
HU3DMODELID fn_1_43F8(s32 dataNum);
HU3DMOTID fn_1_44E4(HU3DMODELID mdlId, s32 dataNum);
void fn_1_45D4(OMOBJMAN *objman, M514_OBJDATA *data);
void fn_1_48B0(OMOBJ *obj);
void fn_1_490C(OMOBJ *obj, s32 motNo);
s32 fn_1_49E4(OMOBJ *obj);
void fn_1_4A4C(OMOBJ *obj);
void fn_1_4C40(OMOBJ *obj);
s32 fn_1_50E4(void);

/* --- stage.c --- */
void fn_1_510C(OMOBJMAN *objman);
void fn_1_51BC(void);
void fn_1_51C0(OMOBJ *obj);
void fn_1_536C(OMOBJ *obj);
void fn_1_5430(GXFogType type, s32 no);
void fn_1_54DC(s16 layerNo);
void fn_1_5574(s16 layerNo);
void fn_1_5610(s16 layerNo);
void fn_1_56AC(s16 layerNo);
void fn_1_5744(OMOBJMAN *objman);
void fn_1_57F0(OMOBJ *obj);
void fn_1_5858(OMOBJ *obj);
void fn_1_585C(HU3DMODEL *model, Mtx *mtx);

/* --- effect.c --- */
void fn_1_5B04(OMOBJMAN *objman);
void fn_1_5B8C(void);
void fn_1_5B90(OMOBJ *obj);
void fn_1_5BEC(OMOBJ *obj);
void fn_1_5C34(OMOBJ *obj);
void fn_1_5CD4(OMOBJ *obj);
void fn_1_5DE4(HU3DMODEL *model, Mtx *cameraMtx);
void fn_1_6588(OMOBJ *obj);
void fn_1_6644(OMOBJ *obj);
void fn_1_68EC(HU3DMODEL *model, Mtx *cameraMtx);
void fn_1_6C44(OMOBJ *obj);
void fn_1_6D7C(OMOBJ *obj);
void fn_1_6ED4(HU3DMODEL *model, Mtx *cameraMtx);
void fn_1_7184(OMOBJ *obj);
void fn_1_728C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_76D0(OMOBJ *obj);
void fn_1_77BC(OMOBJ *obj);
s32 fn_1_79F8(HuVecF *pos, float size);
void fn_1_7B14(s32 idx);
void fn_1_7B8C(s32 idx);
void fn_1_7C10(s32 idx, HuVecF *pos);
void fn_1_7EBC(HuVecF *pos);
void fn_1_80C0(HuVecF *pos, float size);
void fn_1_8180(HuVecF *pos);
void fn_1_8228(s32 bank);

/* --- score.c --- */
void fn_1_8268(OMOBJMAN *objman);
void fn_1_8300(void);
void fn_1_8304(OMOBJ *obj);
void fn_1_835C(OMOBJ *obj);
void fn_1_83A8(OMOBJ *obj);
void fn_1_879C(OMOBJ *obj);
void fn_1_8B54(OMOBJ *obj);
void fn_1_8C7C(OMOBJ *obj);
void fn_1_8D58(OMOBJ *obj);
void fn_1_900C(OMOBJ *obj);
void fn_1_9258(OMOBJ *obj);
void fn_1_9300(HUSPRGRPID grpId, s16 prio);
void fn_1_9334(void);
void fn_1_9570(s32 no, float value);
s32 fn_1_95BC(s32 no);
float fn_1_95F4(s32 no);
float fn_1_9688(void);
float fn_1_9794(void);
s32 fn_1_9820(void);
void fn_1_98F4(void);

#endif
