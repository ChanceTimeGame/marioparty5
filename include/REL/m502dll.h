#ifndef M502DLL_H
#define M502DLL_H

/*
 * m502dll (overlay #16): types, globals and prototypes shared by its nine translation
 * units (m502 camera stage player input block opening ending bat).
 *
 * Offsets are GameCube ones from build/mp5-asm/m502dll. No upstream names exist,
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
#include "game/animdata.h"

#include "game/sprite.h"

/* merged by structmerge.py from forks ABCDEFGHIJ: owner fields + every other fork's fields by offset */

typedef struct M502_LIGHT_s M502_LIGHT;
typedef struct M502_BATOBJ_s M502_BATOBJ;
typedef struct M502_BAT_s M502_BAT;
typedef struct M502_BLOCKCELL_s M502_BLOCKCELL;
typedef struct M502_BLOCKEFFECT_s M502_BLOCKEFFECT;
typedef struct M502_BLOCKSHARD_s M502_BLOCKSHARD;
typedef struct M502_BLOCK_s M502_BLOCK;
typedef struct M502_CAMERA_s M502_CAMERA;
typedef struct M502_INPUTCOM_s M502_INPUTCOM;
typedef struct M502_INPUT_s M502_INPUT;
typedef struct M502_CHAR_s M502_CHAR;
typedef struct M502_STAGE_s M502_STAGE;
typedef struct M502_PLAYER_s M502_PLAYER;
typedef struct M502_OPENING_s M502_OPENING;
typedef struct M502_WORKMODEL_s M502_WORKMODEL;
typedef struct M502_WORK_s M502_WORK;

struct M502_LIGHT_s {
    void * unk000;  /* retail passes an uninitialised r4 here (fn_1_398 calls fn_1_15C0 with one argument) */
    s16 unk004;  /* HU3DLIGHTID (lha, cmpwi: signed) */
    u8 pad006[0x2];
}; /* size 0x8 (fA) */

struct M502_BATOBJ_s {
    M502_BAT * unk000;  /* owning bat set: stw r5 in fn_1_CB10 */
    u16 unk004;  /* state: lhz, cmplwi 3 in fn_1_CEBC */
    u16 unk006;  /* frame count: lhz, cmplwi 0xC/0x18, unsigned int->float */
    u16 unk008;  /* wobble angle: lhz, unsigned int->float (0x4330000000000000) */
    u16 unk00A;  /* wobble rate 10..29: clrlwi 16 on store, lhz */
    s16 unk00C;  /* HU3DMODELID: lha */
    s16 unk00E;  /* HU3DMOTID idle: lha */
    s16 unk010;  /* HU3DMOTID: lha */
    s16 unk012;  /* HU3DMOTID: lha */
    s32 unk014;  /* shown flag: lwz, cmpwi 0 */
    HuVecF unk018;  /* position */
    HuVecF unk024;  /* position offset (y = sine wobble) */
    HuVecF unk030;  /* rotation */
    s32 unk03C;  /* direction flag: rand8()%100 < 50 */
    u8 pad040[0x4];
    float unk044;  /* random 0..99 */
}; /* size 0x48 (fJ) */

struct M502_BAT_s {
    M502_PLAYER * unk000;  /* owning player: stw r4 in fn_1_C468 */
    u16 unk004;  /* state: lhz, addi, sth */
    u8 pad006[0x2];
    M502_BATOBJ unk008[8];
}; /* size 0x248 (fJ) */

struct M502_BLOCKCELL_s {
    u8 pad000[0x4];
    u16 unk004;  /* block kind: 0 empty, 1 normal, 2 special (lhz, cmplwi 2) */
    u16 unk006;  /* lhz in fn_1_7290 copy */
    s32 unk008;  /* on-screen flag, set 1/0 by fn_1_6808 */
    s16 unk00C;  /* countdown, 10000 = idle (lha, cmpwi 0x2710) */
    s16 unk00E;  /* countdown, 10000 = idle (lha, cmpwi 0x2710) */
    HuVecF unk010;  /* position, copied as a 12-byte struct; fn_1_912C reads .y with lfs */
    s16 unk01C;  /* lha in fn_1_6808/fn_1_7290 */
    s16 unk01E;  /* hits left (lha, cmpwi 2 / cmpwi 0) */
    u16 unk020;  /* lhz, subtracted from M502_CHAR.unk078 (u16) */
    u8 pad022[0x2];
}; /* size 0x24 (fF) */

struct M502_BLOCKEFFECT_s {
    M502_BLOCK * unk000;  /* owning block (fn_1_8FDC a1) */
    u16 unk004;  /* state 0 idle / 1 playing (lhz, cmplwi 0 in fn_1_6808: unsigned) */
    u16 unk006;  /* reset to 0 when started; never read */
    HuVecF unk008;  /* model ambient colour */
    s16 unk014;  /* index into M502_WORKMODEL.unk000 (lha: signed) */
    u8 pad016[0x2];
}; /* size 0x18 (fG) */

struct M502_BLOCKSHARD_s {
    M502_BLOCK * unk000;  /* owning block (fn_1_8438 a1) */
    u16 unk004;  /* state 0 idle / 1 flying / 2 reset (lhz, cmplwi 0 in fn_1_83AC: unsigned) */
    u16 unk006;  /* frame counter (lhz, clrlwi, cmplwi 60: unsigned) */
    s32 unk008;  /* drawn flag (lwz, cmpwi 0) */
    HuVecF unk00C[8];  /* shard positions */
    HuVecF unk06C[8];  /* shard velocities */
    HuVecF unk0CC[8];  /* shard velocity step; .y -= 0.4 each frame */
    s16 unk12C[8];  /* index into M502_WORKMODEL.unk000/unk11C (lha: signed) */
}; /* size 0x13C (fG) */

struct M502_BLOCK_s {
    M502_PLAYER * unk000;  /* owning player */
    M502_BLOCKCELL unk004[3][27];  /* three rows of 27 cells */
    M502_BLOCKSHARD unkB68[3];
    M502_BLOCKEFFECT unkF1C[2];
    s16 unkF4C;  /* hook model id (lha in fn_1_6778) */
    u8 padF4E[0x2];
}; /* size 0xF50 (fF) */

struct M502_CAMERA_s {
    M502_PLAYER * unk000;  /* owning player (fn_1_1830 r5) */
    s32 unk004;  /* camera bit lbl_1_data_B60[i] (lwz -> Hu3DCamera*(int)) */
    s32 unk008;  /* camera bit lbl_1_data_B60[i + 4] */
    u8 pad00C[0x4];
    HuVecF unk010;  /* eye goal */
    HuVecF unk01C;  /* target goal */
    HuVecF unk028;  /* eye (eased toward unk010) */
    HuVecF unk034;  /* target (eased toward unk01C) */
    HuVecF unk040;  /* up */
    float unk04C;  /* easing rate, 0.1 */
    float unk050;  /* interpolation time 0..1 (fn_1_1E64) */
    HuVecF unk054;  /* eye start */
    HuVecF unk060;  /* target start */
    HuVecF unk06C;  /* eye end */
    HuVecF unk078;  /* target end */
}; /* size 0x84 (fB) */

struct M502_INPUTCOM_s {
    M502_INPUT * unk000;  /* back-pointer to the M502_INPUT this is embedded in (fn_1_57B4) */
    u16 unk004;  /* COM mode: 0 -> input/fn_1_58E0, 1 -> input/fn_1_5EB8 (lhz, cmplwi) */
    u16 unk006;  /* COM state (lhz; switch in fn_1_58E0 / fn_1_5EB8) */
    u16 unk008;  /* lhz/sth in fn_1_5EB8 */
    u16 unk00A;  /* lhz/sth in fn_1_5EB8 */
    s32 unk00C;  /* GwPlayerConf[i].type (lha -> stw): non-zero = COM player */
    u16 unk010;  /* lhz/sth in fn_1_58E0 */
    u16 unk012;  /* lhz, cmplwi 0 in fn_1_58E0 */
}; /* size 0x14 (fE) */

struct M502_INPUT_s {
    M502_CHAR * unk000;  /* back-pointer to the owning M502_CHAR (fn_1_6400 r5) */
    M502_INPUTCOM unk004;  /* COM controller (player fn_1_57B4) */
    s32 unk018;  /* pad port, GwPlayerConf[i].padNo (lha -> stw, lwz as index) */
    s32 unk01C;  /* cleared by player fn_1_3BF4 when input is off */  /* fD */
    s32 unk020;  /* button bits: player fn_1_44B8 tests & 0x100 (A) */  /* fD */
    s8 unk024;  /* stick X = HuPadStkX[port], 10 dead zone (lbz + extsb: signed) */
    u8 pad025[0x1];
    u16 unk026;  /* repeat buttons = HuPadBtnRep[port] (sth) */
    s8 unk028;  /* HuPadStkY */
    s8 unk029;  /* HuPadSubStkX */
    s8 unk02A;  /* HuPadSubStkY */
    u8 unk02B;  /* HuPadTrigL */
    u8 unk02C;  /* HuPadTrigR */
    u8 unk02D;  /* HuPadDStk */
    u8 unk02E;  /* HuPadDStkRep */
    u8 pad02F[0x1];
}; /* size 0x30 (fB) */

struct M502_CHAR_s {
    M502_PLAYER * unk000;  /* owning player */
    u16 unk004;  /* top state: lhz */
    u16 unk006;  /* play state: lhz, cmplwi 2 */
    u16 unk008;  /* move state: lhz */
    u16 unk00A;  /* win-jump state: lhz */
    s32 unk00C;  /* frame timer: cmpwi, xoris int->float */
    s32 unk010;  /* player index */
    s32 unk014;  /* charNo (GwPlayerConf.charNo) */
    s32 unk018;  /* GwPlayerConf.grp */
    OMOBJ * unk01C;  /* model object */
    s32 unk020;  /* input enabled */
    M502_INPUT unk024;  /* input (fn_1_6400) */
    s32 unk054;  /* standing on something: lwz, cmpwi 0 */
    float unk058;  /* floor height */  /* fE */
    float unk05C;  /* height the fall started from */  /* fE */
    s32 unk060;  /* lane 0..2: cmpwi, xoris int->float */
    s32 unk064;  /* A held while rising */
    float unk068;  /* vertical speed */
    float unk06C;  /* vertical speed */
    s16 unk070;  /* hang timer: lha, cmpwi 0 */  /* fE */
    u8 pad072[0x2];
    s32 unk074;  /* fall motion started */
    u16 unk078;  /* drop strength 1..3 (clrlwi 16 + sth) */  /* fE */
    u8 pad07A[0x2];
}; /* size 0x7C (fD) */

struct M502_STAGE_s {
    M502_PLAYER * unk000;  /* owning player (fn_1_21B8 stores its 3rd argument) */
    s16 unk004[5];  /* HU3DMODELID, links of work models 0x81..0x85, mat hook fn_1_2878 (lhax: signed) */
    s16 unk00E[3];  /* HU3DMODELID, links of work models 0x86..0x88 (lhax: signed) */
    s16 unk014;  /* HU3DMODELID, work model 0x89 + player: shape-motion model (lha: signed) */
    u8 pad016[0x2];
    s32 unk018;  /* fn_1_2E08 state (lwz, cmpwi: signed) */
    s32 unk01C;  /* fn_1_2E08 frame 0..3, (n + 1) & 3 (lwz, slwi index) */
    s32 unk020;  /* fn_1_3298 state (lwz, cmpwi: signed) */
    float unk024;  /* y offset, 300 * (unk02C - 1) */
    float unk028;  /* x scale */
    float unk02C;  /* y scale, grows by fn_1_2E08's speed to 6 */
    float unk030;  /* y scale of the unk00E model */
    float unk034;  /* scroll, += unk038 per unpaused frame in fn_1_2878 */
    float unk038;  /* scroll speed, 0.002 */
    s16 unk03C[4];  /* HU3DMODELID, links of work models 0..3 (lhax: signed) */
    s16 unk044[8];  /* copied from lbl_1_data_B88 (lha: signed); never read */
    char * unk054[8];  /* copied from lbl_1_data_C00 (model names); never read */
}; /* size 0x74 (fC) */

struct M502_PLAYER_s {
    M502_WORK * unk000;  /* the work (fn_1_1690) */
    s32 unk004;  /* player index (fn_1_1690 stw; passed in as u16) */
    M502_BLOCK unk008;
    M502_CHAR unkF58;
    M502_STAGE unkFD4;
    M502_CAMERA unk1048;
    M502_BAT unk10CC;
    MGTIMER * unk1314;  /* per-player timer (deca mode), created in opening; cmplwi, ->stopF/->mode written */
}; /* size 0x1318 (fA) */

struct M502_OPENING_s {
    M502_WORK * unk000;  /* the work (fn_1_9468: stored after the memset) */
    u8 pad004[0x18];
    s16 unk01C[3];  /* esprite ids (lha: signed HUSPRID); indexed by lhax in fn_1_9644 */
    u8 pad022[0x2];
}; /* size 0x24 (fH) */

struct M502_WORKMODEL_s {
    s16 unk000[141];  /* HU3DMODELID per lbl_1_data_3C entry (lhax: signed) */
    u8 pad11A[0x2];
    char * unk11C[141];  /* model names, from lbl_1_data_8B8 */
    void * unk350;  /* 320x240 RGB565 texture buffer (cmplwi: pointer) */
    ANIMDATA * unk354;  /* sprite anim 0x21000A */
    ANIMDATA * unk358;  /* sprite anim 0x21000C */
}; /* size 0x35C (fA) */

struct M502_WORK_s {
    OMOBJMAN * unk000;  /* fn_1_398 */
    OMOBJ * unk004;  /* fn_1_398 */
    s32 unk008;  /* state (fn_1_5DC switch; cmpwi 7 / cmpwi 5: signed) */
    s32 unk00C;  /* opening sub-state (cmpwi: signed) */  /* fH */
    s32 unk010;  /* state timer (cmpwi 0x78, 0xD2: signed) */
    s32 unk014;  /* shake counter (fn_1_1104: cmpwi 0x1E/0x96, signed divide) */
    s32 unk018;  /* GAMEMESID or -1 (cmpwi < 0; extsh at use) */
    M502_WORKMODEL unk01C;
    M502_LIGHT unk378;
    M502_OPENING unk380;
    M502_PLAYER unk3A4[4];
    s16 unk5004;  /* winner's player number (lha; fn_1_1018) */
    u8 pad5006[0x2];
    s32 unk5008;  /* shake enable (cmpwi 0) */
    s32 unk500C;  /* frames left, 18000 (cmpwi 0x708 bgt: signed) */
    MGTIMER * unk5010;  /* main timer; (MGTIMER *)-1 in deca mode (cmplwi) */
    s32 unk5014;  /* _CheckFlag(FLAG_INST_DECA) */
    s32 unk5018;  /* jingle/stream id or -1 (cmpwi < 0) */
    s32 unk501C;  /* FX id or -1 (cmpwi < 0) */
    s32 unk5020;  /* -1 */
}; /* size 0x5024 (fA) */


/* m502.c: the static work block and the .data pointer to it. */
extern M502_WORK lbl_1_bss_0;
extern M502_WORK *lbl_1_data_0;
/* camera.c: the per-player camera bits {1,2,4,...,0x80} */
extern s32 lbl_1_data_B60[8];
/* no SDK header declares rand8 */
int rand8(void);

/* --- m502.c --- */
void ObjectSetup(void);
void fn_1_134(OMOBJ *obj);
int fn_1_198(int seId);
void fn_1_1C0(int seNo);
void fn_1_1E8(int seNo, s32 speed);
void fn_1_218(int seNo, s16 pan);
void fn_1_248(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
int fn_1_2A0(s16 streamId);
void fn_1_2C8(int streamNo, s32 speed);
void fn_1_2F8(void);
int fn_1_318(s16 streamId);
int fn_1_340(s16 streamId);
int fn_1_368(s16 streamId, s16 chanNo);
void fn_1_398(M502_WORK *work, OMOBJMAN *objman, OMOBJ *obj);
void fn_1_504(M502_WORK *work);
int fn_1_5DC(M502_WORK *work);
void fn_1_FD8(M502_WORK *work);
void fn_1_1018(M502_WORK *work);
void fn_1_1104(M502_WORK *work);
void fn_1_1350(M502_WORK *work);
void fn_1_13A0(M502_WORK *work);
void fn_1_13F0(M502_WORKMODEL *model);
void fn_1_147C(M502_WORKMODEL *model);
void fn_1_14C0(M502_WORKMODEL *model);
void fn_1_1564(M502_WORKMODEL *model);
void fn_1_15C0(); /* unprototyped: retail fn_1_398 calls it with one argument (r4 left over) */
void fn_1_1638(M502_LIGHT *light);
void fn_1_168C(void);
void fn_1_1690(M502_PLAYER *player, s32 playerNo, M502_WORK *work);
void fn_1_1740(M502_PLAYER *player);
int fn_1_17C4(M502_PLAYER *player);

/* --- camera.c --- */
void fn_1_1830(M502_CAMERA *cam, s32 idx, M502_PLAYER *player);
void fn_1_1990(M502_CAMERA *cam, s32 camBit);
void fn_1_1A60(M502_CAMERA *cam);
void fn_1_1A90(M502_CAMERA *cam);
HuVecF fn_1_1B40(float t, HuVecF *from, HuVecF *to);
void fn_1_1CB4(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_1D60(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target, float *rate);
void fn_1_1DB4(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_1E00(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_1E5C(M502_CAMERA *cam, float t);
int fn_1_1E64(M502_CAMERA *cam, float frames, HuVecF *up);
void fn_1_21B4(void);

/* --- stage.c --- */
void fn_1_21B8(M502_STAGE *stage, s32 playerNo, M502_PLAYER *player);
void fn_1_2704(M502_STAGE *stage);
void fn_1_27A8(M502_STAGE *stage);
void fn_1_27AC(s16 layerNo);
void fn_1_2878(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);
void fn_1_2E08(M502_STAGE *stage, float speed);
void fn_1_3298(M502_STAGE *stage);
void fn_1_3380(float speed);
void fn_1_3390(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);

/* --- player.c --- */
void fn_1_38E0(M502_CHAR *chr, s32 no, M502_PLAYER *player);
void fn_1_3B88(M502_CHAR *chr);
s32 fn_1_3BF4(M502_CHAR *chr);
s32 fn_1_3D50(M502_CHAR *chr);
s32 fn_1_3FA0(M502_CHAR *chr);
s32 fn_1_402C(M502_CHAR *chr);
void fn_1_40D8(M502_CHAR *chr);
void fn_1_44B8(M502_CHAR *chr);
void fn_1_46CC(M502_CHAR *chr);
void fn_1_4874(M502_CHAR *chr);
void fn_1_4A1C(M502_CHAR *chr);
s32 fn_1_4E70(M502_CHAR *chr);
void fn_1_5384(M502_CHAR *chr);
void fn_1_5510(M502_CHAR *chr);
void fn_1_561C(M502_CHAR *chr, s16 *x, s16 *y, s16 *z);
void fn_1_57B4(M502_INPUTCOM *com, s32 playerNo, M502_INPUT *in);
void fn_1_5818(M502_INPUTCOM *com);
void fn_1_5848(M502_INPUTCOM *com);

/* --- input.c --- */
void fn_1_58E0(M502_INPUTCOM *com);
void fn_1_5EB8(M502_INPUTCOM *com);
void fn_1_6250(M502_INPUTCOM *com, s16 *row, s16 *y, s16 *x);
void fn_1_6400(M502_INPUT *in, s32 idx, M502_CHAR *chr);
void fn_1_6478(M502_INPUT *in);
void fn_1_64B8(M502_INPUT *in);

/* --- block.c --- */
void fn_1_6664(M502_BLOCK *block, s32 idx, M502_PLAYER *player);
void fn_1_6778(M502_BLOCK *block);
void fn_1_6808(M502_BLOCK *block);
s32 fn_1_6CB8(HuVecF *pos);
void fn_1_6CFC(s16 row, s16 col, s16 x, HuVecF *out);
void fn_1_6E1C(HuVecF *pos, s16 *row, s16 *col, s16 *x);
s32 fn_1_70B0(M502_BLOCK *block, s16 row, s16 col, s16 x, s16 num);
void fn_1_7290(M502_BLOCK *dst, M502_BLOCK *src);
void fn_1_735C(M502_BLOCK *block);
void fn_1_7548(M502_BLOCK *block, s16 row, s16 col, s16 pattern);
void fn_1_7BFC(M502_BLOCK *block);
void fn_1_7ECC(M502_BLOCK *block);
void fn_1_8290(M502_BLOCK *block);
void fn_1_8324(M502_BLOCKCELL *cell);
void fn_1_83AC(M502_BLOCK *block, s16 type, s16 row, HuVecF *pos, u16 kind);
void fn_1_8438(M502_BLOCKSHARD *shard, M502_BLOCK *block);
void fn_1_850C(M502_BLOCKSHARD *shard);
void fn_1_8594(M502_BLOCKSHARD *shard);
void fn_1_876C(M502_BLOCKSHARD *shard, s16 type, s16 row, HuVecF *pos, u16 kind);
void fn_1_8904(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_8940(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_897C(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_89B8(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_89F4(M502_BLOCK *block, HU3DMODEL *modelP, Mtx *mtx);
void fn_1_8DE4(M502_BLOCK *block, float *out);
void fn_1_8F04(M502_BLOCK *block);
void fn_1_8FDC(M502_BLOCKEFFECT *effect, M502_BLOCK *block);
void fn_1_9028(M502_BLOCKEFFECT *effect);
void fn_1_9058(M502_BLOCKEFFECT *effect);
void fn_1_912C(M502_BLOCKEFFECT *effect, s32 idx, HuVecF *pos);

/* --- opening.c --- */
void fn_1_9468(M502_OPENING *opening, M502_WORK *work);
void fn_1_95B4(M502_OPENING *opening);
void fn_1_9604(M502_OPENING *opening);
int fn_1_9644(M502_WORK *work);

/* --- ending.c --- */
int fn_1_A914(M502_WORK *work);
void fn_1_C1EC(M502_WORK *work, float shake);
void fn_1_C3C4(int playerNo, int type, int duration);

/* --- bat.c --- */
void fn_1_C468(M502_BAT *bat, M502_PLAYER *player);
void fn_1_C4F0(M502_BAT *bat);
void fn_1_C554(M502_BAT *bat);
void fn_1_CAC8(M502_BAT *bat);
void fn_1_CB10(M502_BATOBJ *obj, u16 no, M502_BAT *bat);
void fn_1_CE54(M502_BATOBJ *obj);
void fn_1_CEBC(M502_BATOBJ *obj);
s32 fn_1_DE94(HuVecF *pos);

#endif
