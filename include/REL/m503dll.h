#ifndef M503DLL_H
#define M503DLL_H

/*
 * m503dll (overlay #17): types, globals and prototypes shared by its eight translation
 * units (m503 camera stage player input block opening ending bat).
 *
 * Offsets are GameCube ones from build/mp5-asm/m503Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels; work-struct
 * fields are named by hex offset.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"
#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/mg/timer.h"
#include "game/gamemes.h"
#include "game/mg/score.h"
#include "game/sprite.h"
#include "dolphin/gx.h"

#include "game/sprite.h"

/* merged by structmerge.py from forks ABCDEFGHIJK: owner fields + every other fork's fields by offset */

typedef struct M503_MAIN_s M503_MAIN;
typedef struct M503_CAMERA_s M503_CAMERA;
typedef struct M503_CAMVIEW_s M503_CAMVIEW;
typedef struct M503_ACTORENT_s M503_ACTORENT;
typedef struct M503_ACTORBOX_s M503_ACTORBOX;
typedef struct M503_STAGE_s M503_STAGE;
typedef struct M503_SCOREPL_s M503_SCOREPL;
typedef struct M503_SCORE_s M503_SCORE;
typedef struct M503_SCOREPOS_s M503_SCOREPOS;
typedef struct M503_STAGECELL_s M503_STAGECELL;
typedef struct M503_STAGEBUF_s M503_STAGEBUF;
typedef struct M503_ACTOR_s M503_ACTOR;
typedef struct M503_PARTICLE_s M503_PARTICLE;
typedef struct M503_PLAYER_s M503_PLAYER;
typedef struct M503_SARUSHADOW_s M503_SARUSHADOW;
typedef struct M503_SARU_s M503_SARU;
typedef struct M503_PLAYERCOM_s M503_PLAYERCOM;
typedef struct M503_PLAYERMOT_s M503_PLAYERMOT;
typedef struct M503_SARUDATA_s M503_SARUDATA;
typedef struct M503_SARUMOT_s M503_SARUMOT;
typedef struct M503_STAGECOL_s M503_STAGECOL;

struct M503_MAIN_s {
    s32 unk000;
    s32 unk004;
    s32 unk008;
    s32 unk00C;
    s32 unk010;  /* opening camera phase (fn_1_2DD8 switch: cmpwi) */  /* fB */
    u32 unk014;
    s32 unk018;
    s32 unk01C;
    s32 unk020;  /* result phase (fn_1_2FC0 switch: cmpwi) */
    u32 unk024;  /* result phase timer (fn_1_2FC0: unsigned int->float, no xoris) */
    s32 unk028[4];
    s32 unk038[4];
    s32 unk048[4];
    s32 unk058;  /* winners counted by fn_1_2E80 */
    u32 unk05C;  /* losers counted by fn_1_2E80 (player converts fn_1_1D00 unsigned) */  /* fB */
    u32 unk060[4];  /* per player rank within winners/losers (fn_1_2E80) */  /* fB */
    u32 unk070;  /* 1 when someone scored (fn_1_2E80; cmplwi in fn_1_2FC0 and player) */  /* fB */
    u32 unk074;  /* nibble flag per player (fn_1_1B70) */
    u32 unk078;  /* nibble value per player (fn_1_1BA0 / fn_1_1BFC) */
    u32 unk07C;  /* nibble flag per player (fn_1_1C80) */  /* fB */
}; /* size 0x80 (fA) */

struct M503_CAMERA_s {
    s32 unk000;  /* camera motion playing (fn_1_2AD4 sets 1, fn_1_2354 clears) */
    s32 unk004;  /* next motion-time cue index into lbl_1_data_4C (fn_1_298C) */
    s16 unk008;  /* HU3DMOTID (fn_1_2AD4: sth/lha) */
    s16 unk00A;  /* HU3DMODELID of the camera model (fn_1_2AD4) */
}; /* size 0xC (fB) */

struct M503_CAMVIEW_s {
    HuVecF unk000;
    HuVecF unk00C;
}; /* size 0x18 (fB) */

struct M503_ACTORENT_s {
    u32 unk000;  /* bit 0: live (actor fn_1_D84C clrlwi+cmplwi) */
    s32 unk004;  /* kind: 1 player/monkey, 2 stage box */
    s32 unk008;  /* index */
    s32 unk00C;  /* nonzero: skipped (cmpwi) */
    OMOBJ * unk010;  /* owner object, handed to unk014 */
    OMOBJFUNC unk014;  /* post-collision callback */
    HuVecF * unk018;  /* position (owned by the caller) */
    float unk01C;  /* radius */
}; /* size 0x20 (fE) */

struct M503_ACTORBOX_s {
    M503_ACTORENT unk000;
    s32 unk020;  /* 0: keep out of the circle, else keep inside (actor fn_1_DC6C cmpwi) */
}; /* size 0x24 (fE) */

struct M503_STAGE_s {
    M503_ACTORBOX unk000[5];
}; /* size 0xB4 (fC) */

struct M503_SCOREPL_s {
    s32 unk000;  /* score value; lwzx + cmpwi 99 (signed) */
    HUSPRGRPID unk004;  /* MgScoreWin group; lhax (signed s16) */
    HUSPRGRPID unk006;  /* icon sprite group (1 member); lhax */
    MGSCORE * unk008;  /* pointer: host stride differs */
}; /* size 0xC (fD) */

struct M503_SCORE_s {
    s32 unk000;  /* fade state; lwz + cmpwi */
    float unk004;  /* fade level 0..1 */
    M503_SCOREPL unk008[4];
}; /* size 0x38 (fD) */

struct M503_SCOREPOS_s {
    float unk000;  /* x */
    float unk004;  /* y */
}; /* size 0x8 (fD) */

struct M503_STAGECELL_s {
    float unk000;  /* height (y), eased toward unk004 + unk008 */
    float unk004;  /* rest height */
    float unk008;  /* dent, cleared each frame by fn_1_B888 */
    GXColor unk00C;  /* vertex colour; bytes stored, word read by GXColor1u32 */
}; /* size 0x10 (fD) */

struct M503_STAGEBUF_s {
    ANIMDATA * unk000;  /* grid texture */
    float unk004;  /* translation x */
    float unk008;  /* translation y */
    float unk00C;  /* translation z */
    float unk010[13][13];  /* dent kernel; fn_1_C424 mulli 0x34 row stride */
    M503_STAGECELL unk2B4[40][40];  /* fn_1_B888 mulli 0x280 row stride */
}; /* size 0x66B4 (fD) */

struct M503_ACTOR_s {
    M503_ACTORENT * unk000[40];
    M503_ACTORBOX * unk0A0[8];
}; /* size 0xC0 (fE) */

struct M503_PARTICLE_s {
    M503_SARUSHADOW * unk000[40];
    float unk0A0[32];  /* sin(i * 11 deg) */
    float unk120[32];  /* cos(i * 11 deg) */
}; /* size 0x1A0 (fE) */

struct M503_PLAYER_s {
    s32 unk000;  /* player number (obj->work[0]) */
    s32 unk004;  /* GwPlayerConf[no].grp (obj->work[1]) */
    s32 unk008;  /* slot (obj->work[2]), row of lbl_1_data_140 */
    s32 unk00C;  /* charNo */
    s32 unk010;  /* current motion, -1 = none */
    float unk014;  /* overlay motion time left */  /* fG */
    u32 unk018;  /* HuPadBtnDown */
    u32 unk01C;  /* HuPadBtn */
    float unk020;  /* stick direction, degrees */
    float unk024;  /* stick magnitude 0..1 */
    s32 unk028;  /* GwPlayerConf[no].type: nonzero = COM */
    s32 unk02C;  /* GwPlayerConf[no].dif & 3 */
    s32 unk030;  /* CPU wait counter */
    s32 unk034;  /* CPU: last seen unk084 */  /* fG */
    OMOBJ * unk038;  /* CPU: targeted monkey */  /* fG */
    s32 unk03C;  /* CPU: frames on target */  /* fG */
    HuVecF unk040;  /* CPU: throw target */  /* fG */
    s32 unk04C;  /* state (cmpwi) */
    s32 unk050;  /* state timer (cmpwi, signed int->float) */
    s32 unk054;  /* frame counter */  /* fG */
    u8 pad058[0x4];
    HuVecF unk05C;  /* position */
    HuVecF unk068;  /* velocity */
    float unk074;  /* model Y rotation */
    s32 unk078;
    s32 unk07C;  /* busy in a one-shot motion */
    s32 unk080;  /* voice volume follows z */
    s32 unk084;  /* holding a monkey */  /* fG */
    OMOBJ * unk088;  /* the held monkey */  /* fG */
    M503_ACTORENT unk08C;  /* registered with actor.c fn_1_DF30 */
}; /* size 0xAC (fF) */

struct M503_SARUSHADOW_s {
    s32 unk000;  /* 0 */
    float unk004;  /* 50.0f */
    HuVecF * unk008;  /* position: &work->unk038 */
    HuVecF * unk00C;  /* offset added to unk008 (saru lbl_1_data_420) */  /* fE */
}; /* size 0x10 (fH) */

struct M503_SARU_s {
    u32 unk000;  /* data row 0..8: cmplwi 8 (fn_1_6618), cmplw (fn_1_63C8) */
    s32 unk004;  /* table index (lbl_1_data_494/4A8/4BC) */
    u32 unk008;  /* instance index in the row: cmplw (fn_1_6618 case 2) */
    s32 unk00C;  /* -1 */
    s32 unk010;  /* state: switch in fn_1_60EC / fn_1_6618 */
    s32 unk014;  /* timer: --x > 0 is cmpwi */
    s32 unk018;  /* action step */  /* fI */
    s32 unk01C;  /* step timer, signed int->float */  /* fI */
    s32 unk020;  /* frand() & 1 */  /* fI */
    s32 unk024;  /* fn_1_961C jump state: cmpwi switch */  /* fI */
    s32 unk028;  /* fn_1_961C frame counter: xoris int->float */  /* fI */
    u8 pad02C[0x4];
    s32 unk030;  /* frame counter */
    s32 unk034;  /* -1 */
    HuVecF unk038;  /* position */
    HuVecF unk044;  /* velocity (PSVECAdd into unk038) */
    float unk050;  /* yaw */
    u8 pad054[0x4];
    s32 unk058;  /* 1 while calling (fn_1_60EC) */
    u32 unk05C;  /* slot 0..3 for rows 0..3: int->float with no xoris */
    float unk060;  /* last motion time */
    u32 unk064;  /* row for 0..3, row-4 for 4..8: cmplwi 4 */
    s32 unk068;  /* in a goal: cmpwi 0 */
    s32 unk06C;  /* index into lbl_1_data_35C */
    s32 unk070;
    HuVecF unk074;  /* target position */
    s32 unk080;  /* held by a player: cmpwi 0 */
    OMOBJ * unk084;  /* holding player's object */  /* fK */
    s32 unk088;  /* airborne (thrown): cmpwi 0 */
    HuVecF unk08C;  /* jump velocity */  /* fI */
    HuVecF unk098;  /* target position */  /* fI */
    float unk0A4;  /* heading, degrees */  /* fI */
    M503_ACTORENT unk0A8;
    M503_SARUSHADOW unk0C8;
}; /* size 0xD8 (fH) */

struct M503_PLAYERCOM_s {
    float unk000;  /* chance to throw at the stored target */  /* fG */
    float unk004;  /* fn_1_9D18 cone */  /* fG */
    float unk008;  /* fn_1_9D18 range */  /* fG */
    s32 unk00C;  /* wait after grabbing */  /* fG */
    s32 unk010;  /* wait after throwing */  /* fG */
    s32 unk014;  /* frames before a target is dropped */  /* fG */
    float unk018;  /* stick magnitude */  /* fG */
}; /* size 0x1C (fG) */

struct M503_PLAYERMOT_s {
    u16 unk000;  /* obj->mtnId index */  /* fG */
    s16 unk002;  /* overlay obj->mtnId index, -1 = none */  /* fG */
    float unk004;  /* shift time, seconds */  /* fG */
    u32 unk008;  /* HU3D_MOTATTR_ */  /* fG */
}; /* size 0xC (fG) */

struct M503_SARUDATA_s {
    s32 unk000;  /* model data number */  /* fH */
    u16 unk004;  /* instances (rows 4..7 get one more): lhz */  /* fH */
    u16 unk006;  /* row of lbl_1_data_270 / motion cache: lhz */  /* fH */
    s32 unk008;  /* motion count (omAddObjEx mtncnt; cmpw loop bound) */  /* fH */
    OMOBJFUNC unk00C;  /* first objFunc */  /* fH */
}; /* size 0x10 (fH) */

struct M503_SARUMOT_s {
    float unk000;  /* blend time in seconds (* 60.0f) */  /* fK */
    u32 unk004;  /* Hu3DModelAttrSet / Hu3DMotionShiftSet attribute */  /* fK */
}; /* size 0x8 (fK) */

struct M503_STAGECOL_s {
    HuVecF unk000;  /* position */  /* fC */
    float unk00C;  /* radius */  /* fC */
    s32 unk010;  /* flag (1 on the last row only) */  /* fC */
}; /* size 0x14 (fC) */


/* --- m503.c --- */
void ObjectSetup(void);
void fn_1_348(OMOBJ *obj);
void fn_1_430(OMOBJ *obj);
void fn_1_5B0(OMOBJ *obj);
void fn_1_6D0(OMOBJ *obj);
void fn_1_A38(OMOBJ *obj);
void fn_1_DF4(OMOBJ *obj);
void fn_1_10A4(OMOBJ *obj);
void fn_1_13F4(OMOBJ *obj);
void fn_1_16F4(OMOBJ *obj);
u32 fn_1_1AB0(void);
u32 fn_1_1AC8(void);
u32 fn_1_1AE0(void);
u32 fn_1_1AF8(void);
u32 fn_1_1B10(void);
void fn_1_1B28(u32 flag);
s32 fn_1_1B40(s32 no);
void fn_1_1B70(s32 no);
void fn_1_1BA0(s32 no, u32 val);
s32 fn_1_1BFC(s32 val);
void fn_1_1C80(s32 no);
BOOL fn_1_1CB0(void);
s32 fn_1_1CE8(void);
u32 fn_1_1D00(void);
u32 *fn_1_1D18(void);
s32 fn_1_1D30(void);
void fn_1_1D98(s32 no, s32 arg1, s32 charNo);
void fn_1_1DD8(s32 no);
s32 fn_1_1E54(float x);
s32 fn_1_1EB0(); /* unprototyped: player/fn_1_4380 calls it with one argument */
s32 fn_1_1F44(HuVecF *pos);
s32 fn_1_1FD8(s32 seNo, HuVecF *pos);
void fn_1_210C(s32 seId, HuVecF *pos);
void fn_1_2260(s32 seNo, float x);
void fn_1_22FC(OMOBJ *obj);
void fn_1_2354(OMOBJ *obj);
void fn_1_298C(OMOBJ *obj);
void fn_1_2A08(OMOBJ *obj);
void fn_1_2AD4(void *data);
s32 fn_1_2B4C(void);
float fn_1_2B7C(float cur, float target, float rate);
float fn_1_2C98(float from, float to);

/* --- opening.c --- */
OMOBJFUNC fn_1_2D4C(OMOBJMAN *objman);
void fn_1_2DD8(OMOBJ *obj);
OMOBJFUNC fn_1_2E80(OMOBJMAN *objman, OMOBJ *obj);
void fn_1_2FC0(OMOBJ *obj);
void fn_1_32E0(s32 from, s32 to, float t);

/* --- player.c --- */
void fn_1_3440(OMOBJMAN *objman);
void fn_1_34F4(void);
void fn_1_3518(OMOBJ *obj);
void fn_1_37C0(OMOBJ *obj);
void fn_1_3C3C(OMOBJ *obj);
void fn_1_4380(OMOBJ *obj);
void fn_1_443C(OMOBJ *obj);
void fn_1_4658(OMOBJ *obj);
void fn_1_47C8(OMOBJ *obj);
void fn_1_48C8(OMOBJ *obj);
void fn_1_4E94(OMOBJ *obj, u32 motNo);
BOOL fn_1_5038(OMOBJ *obj);
BOOL fn_1_5104(OMOBJ *obj);
BOOL fn_1_5164(OMOBJ *obj, u32 motNo);
s32 fn_1_53B8(OMOBJ *obj);
OMOBJ *fn_1_53D4(HuVecF *pos, float dir, float fov, float range);
s32 fn_1_5708(OMOBJ *obj, HuVecF *pos, float *rot);
BOOL fn_1_575C(OMOBJ *obj, s32 arg);

/* --- saru.c --- */
void fn_1_5810(OMOBJMAN *objman);
void fn_1_5D4C(void);
void fn_1_5D50(OMOBJ *obj);
void fn_1_5D60(OMOBJ *obj);
void fn_1_5F50(OMOBJ *obj);
void fn_1_5FF0(OMOBJ *obj);
void fn_1_6044(OMOBJ *obj);
void fn_1_60EC(OMOBJ *obj);
s32 fn_1_63C8(OMOBJ *obj);
void fn_1_6458(OMOBJ *obj);
void fn_1_6618(OMOBJ *obj);
void fn_1_6C0C(OMOBJ *obj, s32 action);
void fn_1_6C5C(OMOBJ *obj, float x, float z, float rate);
void fn_1_6CA4(OMOBJ *obj, float angle, float speed, float rate);
void fn_1_6DBC(OMOBJ *obj, float rate);
void fn_1_6E48(OMOBJ *obj, float speed, float rate);
s32 fn_1_6F8C(OMOBJ *obj);
s32 fn_1_6F94(OMOBJ *obj);
s32 fn_1_6FC4(OMOBJ *obj);
s32 fn_1_721C(OMOBJ *obj);
s32 fn_1_780C(OMOBJ *obj);
s32 fn_1_7A78(OMOBJ *obj);
s32 fn_1_7C8C(OMOBJ *obj);
s32 fn_1_7D6C(OMOBJ *obj);
s32 fn_1_82B4(OMOBJ *obj);
s32 fn_1_8AD8(OMOBJ *obj);
s32 fn_1_8EA0(OMOBJ *obj);
s32 fn_1_9210(OMOBJ *obj);
s32 fn_1_961C(OMOBJ *obj);
void fn_1_98D0(OMOBJ *obj);
void fn_1_9A04(OMOBJ *obj, s32 motNo);
s32 fn_1_9B00(OMOBJ *obj);
s32 fn_1_9B68(OMOBJ *obj);
s32 fn_1_9BC0(OMOBJ *obj, s32 motNo);
s32 fn_1_9D08(void);
OMOBJ *fn_1_9D18(HuVecF *pos, float rotY, float range, float maxDist);
s32 fn_1_A080(OMOBJ *obj, HuVecF *pos, HuVecF *goal);
void fn_1_A338(s32 goalNo, HuVecF *goal);
HU3DMODELID fn_1_A368(OMOBJ *obj, OMOBJ *player);
void fn_1_A438(OMOBJ *obj, HuVecF *pos, s32 check);

/* --- stage.c --- */
void fn_1_A6FC(OMOBJMAN *objman);
void fn_1_A78C(void);
void fn_1_A790(OMOBJ *obj);
void fn_1_A928(OMOBJ *obj);
void fn_1_AA0C(OMOBJ *obj);
void fn_1_AD34(OMOBJ *obj);
void fn_1_AE8C(OMOBJ *obj);
void fn_1_AF20(s32 type, s32 mode);
void fn_1_B278(HU3DMODEL *modelP, float amp);
void fn_1_B888(OMOBJ *obj);
void fn_1_B9D0(HU3DMODELID mdlId);
void fn_1_BA9C(HU3DMODEL *model, Mtx *mtx);
float fn_1_BFE8(float x, float z);
float fn_1_C18C(float x, float z);
void fn_1_C424(float x, float z, float depth);

/* --- particle.c --- */
void fn_1_C574(OMOBJMAN *objman);
void fn_1_C598(void);
void fn_1_C59C(void);
void fn_1_C6A4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_C9FC(void);
void fn_1_CB48(HU3DMODEL *model, Mtx *mtx);
void fn_1_CE1C(HuVecF *pos);
void fn_1_CEB0(HuVecF *pos);
void fn_1_D134(M503_SARUSHADOW *shadow);

/* --- score.c --- */
void fn_1_D1B4(OMOBJMAN *objman);
void fn_1_D23C(void);
void fn_1_D240(OMOBJ *obj);
void fn_1_D27C(OMOBJ *obj);
void fn_1_D2A4(OMOBJ *obj);
void fn_1_D4CC(OMOBJ *obj);
void fn_1_D6D4(s32 no, s32 add);
s32 fn_1_D778(s32 no);

/* --- actor.c --- */
void fn_1_D7B0(OMOBJMAN *objman);
void fn_1_D838(void);
void fn_1_D83C(OMOBJ *obj);
void fn_1_D84C(OMOBJ *obj);
s32 fn_1_D9C4(M503_ACTORENT *a, M503_ACTORENT *b);
s32 fn_1_DC6C(M503_ACTORENT *a, M503_ACTORBOX *b);
s32 fn_1_DF30(M503_ACTORENT *ent);
s32 fn_1_DFA8(M503_ACTORBOX *box);
void fn_1_E020(s32 idx);

#endif
