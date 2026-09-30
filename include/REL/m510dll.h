#ifndef M510DLL_H
#define M510DLL_H

/*
 * m510dll (overlay #24): types, globals and prototypes shared by its thirteen translation
 * units (m510 stage player playermodel pitch ball pad camera light opening ending
 * ball_path score).
 *
 * Offsets are GameCube ones from build/mp5-asm/m510dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels; work-struct
 * fields are named by hex offset.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"
#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/mg/score.h"

#include "game/sprite.h"

/* merged by structmerge.py from forks ABCDEFGHIJ: owner fields + every other fork's fields by offset */

typedef struct M510_CAMERA_s M510_CAMERA;
typedef struct M510_LIGHT_s M510_LIGHT;
typedef struct M510_BALLPATH_s M510_BALLPATH;
typedef struct M510_BALLOBJ_s M510_BALLOBJ;
typedef struct M510_BALL_s M510_BALL;
typedef struct M510_PITCH_s M510_PITCH;
typedef struct M510_PADAI_s M510_PADAI;
typedef struct M510_PAD_s M510_PAD;
typedef struct M510_PLAYERMODEL_s M510_PLAYERMODEL;
typedef struct M510_SCORE_s M510_SCORE;
typedef struct M510_PLAYER_s M510_PLAYER;
typedef struct M510_STAGENUM_s M510_STAGENUM;
typedef struct M510_STAGEOBJ_s M510_STAGEOBJ;
typedef struct M510_STAGE_s M510_STAGE;
typedef struct M510_WORK_s M510_WORK;
typedef struct M510_ENDOBJ_s M510_ENDOBJ;
typedef struct M510_ENDPIECE_s M510_ENDPIECE;
typedef struct M510_ENDING_s M510_ENDING;

struct M510_CAMERA_s {
    M510_WORK * unk000;  /* the work block (fn_1_89B8 a1) */
    s32 unk004;  /* camera bit, 1 */
    u8 pad008[0x4];
    HuVecF unk00C;  /* eye goal */
    HuVecF unk018;  /* eye current */
    HuVecF unk024;  /* target goal */
    HuVecF unk030;  /* target current */
    HuVecF unk03C;  /* eye offset (zeroed each frame) */
    HuVecF unk048;  /* target offset (zeroed each frame) */
    HuVecF unk054;  /* up */
    float unk060;  /* follow rate, 0.4 */
}; /* size 0x64 (fH) */

struct M510_LIGHT_s {
    M510_WORK * unk000;  /* the work (light/fn_1_959C arg 2) */
    s16 unk004;  /* HU3DLIGHTID (lha, cmpwi: signed) */
    u8 pad006[0x2];
}; /* size 0x8 (fB) */

struct M510_BALLPATH_s {
    s16 unk000;  /* key count, lha (signed) */
    u8 pad002[0x2];
    HuVecF unk004[24];  /* key positions */
    s32 unk124[24];  /* per-key duration, cmpw (signed) */
    s32 unk184[24];  /* cumulative time, cmpw (signed) */
}; /* size 0x1E4 (fH) */

struct M510_BALLOBJ_s {
    M510_BALL * unk000;  /* owning M510_BALL (fn_1_53E0 a2) */
    u16 unk004;  /* state 0..3: lhz + cmpwi/cmplwi, sth */
    s16 unk006;  /* timer: lha, cmpwi 0xF, xoris int->float */
    s16 unk008;  /* index 0..2 (fn_1_53E0 a1) */
    u8 pad00A[0x2];
    s32 unk00C;  /* in play: lwz/cmpwi */
    HuVecF unk010;  /* position */
    HuVecF unk01C;  /* previous position */
    u8 pad028[0x30];
    s16 unk058;  /* pitch kind 0..3: lha, indexes lbl_1_data_3A4/3AC/3BC */
    HU3DMODELID unk05A;  /* ball model (Hu3DModelLink of unk6F6) */
    HU3DMODELID unk05C;  /* second model (Hu3DModelLink of unk6F8) */
    u8 pad05E[0x2];
    M510_BALLPATH unk060;  /* flight path */
    s16 unk244;  /* path speed per frame: lha, divw result extsh */
    s16 unk246;  /* path position: lha, cmpw */
    s16 unk248;  /* written by fn_1_7038, read by fn_1_64B0 (lha, xoris) */
    u8 pad24A[0x2];
    M510_STAGEOBJ * unk24C;  /* target hit next, NULL none (cmplwi) */
}; /* size 0x250 (fE) */

struct M510_BALL_s {
    M510_PLAYER * unk000;  /* owning player (fn_1_509C a1) */
    M510_BALLOBJ unk004[3];
    s16 unk6F4;  /* balls in play, counted by fn_1_5230 (lha) */
    HU3DMODELID unk6F6;  /* ball model 0x440003 */
    HU3DMODELID unk6F8;  /* second model 0x440004 */
    HU3DMOTID unk6FA;  /* its motion 0x440018 */
}; /* size 0x6FC (fE) */

struct M510_PITCH_s {
    M510_PLAYER * unk000;  /* owning player */
    u16 unk004;  /* mode: lhz */
    s16 unk006;  /* frame counter (lha, xoris int->float) */
    HU3DMODELID unk008;  /* pitcher base model */
    HU3DMOTID unk00A;  /* its joint motion */
    HU3DMODELID unk00C;  /* rotating arm model */
    u8 pad00E[0x2];
    HuVecF unk010;  /* base position (player writes it from lbl_1_data_110) */
    float unk01C;  /* arm angle, degrees, wrapped to (-180, 180] */
    s16 unk020;  /* speed class index into lbl_1_data_344 (lha) */
    u8 pad022[0x2];
    s32 unk024;  /* nonzero: start a pitch */
    HuVecF unk028;  /* release point (world) */
    float unk034;  /* curve width */  /* fA */
    s32 unk038;  /* wind-up sound handle, -1 none (cmpwi/blt: signed) */
}; /* size 0x3C (fD) */

struct M510_PADAI_s {
    M510_PAD * unk000;  /* back pointer to the owning M510_PAD */
    u16 unk004;  /* state: 0 wait for pitch, 1 swing countdown, 2 wait for reset */
    s16 unk006;  /* swing countdown (frames) */
    s32 unk008;  /* GwPlayerConf[].type (0 = human) */
    s32 unk00C;  /* zeroed in init; never read in pad.c */
    u16 unk010;  /* level: dif 3->0, 2->1, 1->2, else 3 */
    u8 pad012[0x1A];
    s16 unk02C[30];  /* per-pitch plan: 0 = take, 1 = swing, 2 = swing with a timing error */
}; /* size 0x68 (fF) */

struct M510_PAD_s {
    M510_PLAYERMODEL * unk000;  /* owner (fn_1_8184 arg 3) */
    M510_PADAI unk004;
    s32 unk06C;  /* pad port: GwPlayerConf[no].padNo */
    s32 unk070;  /* cleared by playermodel fn_1_4328 each frame */  /* fD */
    s32 unk074;  /* button bits; playermodel tests 0x100 (A) */  /* fD */
    s8 unk078;  /* HuPadStkX, deadzone 10 */
    s8 unk079;  /* HuPadStkY, deadzone 10 */
    u16 unk07A;  /* HuPadBtnRep */
    s8 unk07C;  /* HuPadSubStkX */
    s8 unk07D;  /* HuPadSubStkY */
    u8 unk07E;  /* HuPadTrigL */
    u8 unk07F;  /* HuPadTrigR */
    u8 unk080;  /* HuPadDStk */
    u8 unk081;  /* HuPadDStkRep */
    u8 pad082[0x2];
}; /* size 0x84 (fF) */

struct M510_PLAYERMODEL_s {
    M510_PLAYER * unk000;  /* owning player */
    u16 unk004;  /* mode: lhz, cmplwi in fn_1_4770 */
    s16 unk006;  /* frame counter / swing-table index (lha, signed compare) */
    s16 unk008;  /* player number (lha, cmpwi) */
    u8 pad00A[0x2];
    s32 unk00C;  /* GwPlayerConf[no].charNo, s32 (lwz, extsh to CharModel*) */
    s32 unk010;  /* GwPlayerConf[no].grp */
    OMOBJ * unk014;  /* omAddObjEx result; motions in mtnId[0..6] */
    HU3DMODELID unk018;  /* character model */
    u8 pad01A[0x12];
    M510_PAD unk02C;  /* pad fn_1_8184(&pm->unk02C, no, pm) */
    s16 unk0B0;  /* current shift motion index (lha) */
    s16 unk0B2;  /* requested shift motion index (lha) */
    s32 unk0B4;  /* shift loops: nonzero -> HU3D_MOTATTR_LOOP */
    HuVecF unk0B8;  /* object translation */
    HuVecF unk0C4;  /* object rotation */
    HuVecF * unk0D0;  /* &Hu3DData[model].pos */
    HuVecF * unk0D4;  /* &Hu3DData[model].rot */
    HU3DMODELID unk0D8;  /* held item model (hooked to the character) */
    u8 pad0DA[0x2];
    float unk0DC;  /* swing table value this frame */
    float unk0E0;  /* swing table value last frame */
    u8 pad0E4[0xC];
    HuVecF unk0F0;  /* item hook position */  /* fI */
    s32 unk0FC;  /* nonzero: poll pad fn_1_8234 */
    s32 unk100;  /* nonzero: start a swing without A */
    s32 unk104;  /* nonzero = winner (lwz, cmpwi) */  /* fI */
    HU3DMODELID unk108;  /* effect model */
    HU3DMOTID unk10A;  /* its joint motion */
    s32 unk10C;  /* nonzero: hide 0x108 when its motion ends */
}; /* size 0x110 (fD) */

struct M510_SCORE_s {
    u8 pad000[0x4];
    u16 unk004;  /* layout: 0 player, 1 work (record), else centre; lhz + cmplwi */
    s16 unk006;  /* player index: extsh before mulli 0xC */
    HUSPRGRPID unk008;  /* MgScoreWin group: lha */
    u8 pad00A[0x2];
    MGSCORE * unk00C;  /* MgScoreCreate result (lwz) */
    s16 unk010;  /* esprite, layout 0: lha */
    s16 unk012;  /* esprite (cross), layout 0: lha */
    s16 unk014;  /* esprite (crown), layout 1: lha */
    u8 pad016[0x2];
    float unk018;  /* digit/crown scale pulse */
    s32 unk01C;  /* pulse direction: lwz + cmpwi */
    s32 unk020;  /* pulse enable: lwz + cmpwi */
    s16 unk024;  /* displayed value: lha into MgScoreValueSet */
    u8 pad026[0x2];
}; /* size 0x28 (fG) */

struct M510_PLAYER_s {
    M510_WORK * unk000;  /* the work (player/fn_1_3A64 arg 3) */
    s16 unk004;  /* playerNo (lha/extsh: signed) */
    u8 pad006[0x2];
    M510_PLAYERMODEL unk008;
    M510_PITCH unk118;
    M510_BALL unk154;
    M510_SCORE unk850;
    s16 unk878;  /* HU3DMODELID (lha) */
    s16 unk87A;  /* HU3DMOTID (lha) */
    s32 unk87C;  /* hide-at-motion-end flag (lwz/cmpwi) */
}; /* size 0x880 (fB) */

struct M510_STAGENUM_s {
    M510_STAGE * unk000;  /* owning stage */
    u8 pad004[0x4];
    HU3DMODELID unk008;  /* model */
    HU3DMOTID unk00A[10];  /* flip motion per digit 0..9 */
    s16 unk01E;  /* digit shown (lha, cmpwi 9 / 0) */
    s16 unk020;  /* digit wanted (lha, cmpw) */
    u8 pad022[0x2];
}; /* size 0x24 (fC) */

struct M510_STAGEOBJ_s {
    M510_STAGE * unk000;  /* owning stage (fn_1_30D8 stw) */
    s16 unk004;  /* state 0 idle, 1 cheer start, 2 cheering (lha, cmpwi) */
    s16 unk006;  /* cheer timer (lha, extsh, cmpwi 60) */
    u16 unk008;  /* spectator kind 0..2 (param compared clrlwi+cmplwi) */
    HU3DMODELID unk00A;  /* model */
    HU3DMOTID unk00C;  /* idle motion */
    HU3DMOTID unk00E;  /* second motion (loaded, never played) */
    HU3DMOTID unk010;  /* cheer motion */
    u8 pad012[0x2];
    HuVecF unk014;  /* position (struct copy) */
}; /* size 0x20 (fC) */

struct M510_STAGE_s {
    M510_WORK * unk000;  /* the work (fn_1_295C stw r4) */
    u8 pad004[0x4];
    HU3DMODELID unk008;  /* stage model 0x44|0x06 */
    HU3DMODELID unk00A;  /* stage model 0x44|0x07 */
    HU3DMODELID unk00C;  /* stage model 0x44|0x05 */
    HU3DMOTID unk00E;  /* motion 0x44|0x17 on unk00C */
    M510_STAGEOBJ unk010[16];  /* spectators */
    M510_STAGENUM unk210;  /* scoreboard units digit */
    M510_STAGENUM unk234;  /* scoreboard tens digit */
}; /* size 0x258 (fC) */

struct M510_WORK_s {
    OMOBJMAN * unk000;  /* MgActorObjectSetup() result (fn_1_7B4 a1); pointer, so sizeof in fn_1_E8 */
    u8 pad004[0x4];
    s32 unk008;  /* frame counter: fn_1_E54 increments every frame */
    u16 unk00C;  /* seqman phase 0..8: sth; lhz + cmplwi 4 in fn_1_E54 */
    u16 unk00E;  /* opening state (lhz, cmplwi) */  /* fC */
    s32 unk010;  /* 1500-frame countdown in MGSEQ_MODE_MAIN: lwz + cmpwi 0 */
    s32 unk014;  /* opening timer (lwz, cmpwi, xoris) */  /* fC */
    s32 unk018;  /* opening frame counter (lwz, cmpwi) */  /* fC */
    M510_PLAYER unk01C[4];
    M510_STAGE unk221C;
    M510_CAMERA unk2474;
    M510_LIGHT unk24D8;
    M510_SCORE unk24E0;  /* record display; only when unk2534 == 0 */
    s16 unk2508;  /* pitches left, starts at 30: lha + cmpwi */
    u8 unk250A[30];  /* pitch kind per pitch (0,1,3; 2 = unset): lbzx + cmplwi */
    s16 unk2528;  /* next index into unk250A: lha, extsh */
    u8 pad252A[0x2];
    s32 unk252C;  /* GWMgRecordGet(1) */
    s32 unk2530;  /* GameMes id, -1 none: lwz + cmpwi 0 blt */
    s32 unk2534;  /* _CheckFlag(FLAG_INST_DECA) */
    s32 unk2538;  /* stream id, -1 none: lwz + cmpwi 0 blt */
    s32 unk253C;  /* set to -1 by fn_1_7B4 */
}; /* size 0x2540 (fA) */

struct M510_ENDOBJ_s {
    s16 unk000;  /* mode (lha, cmpwi) */  /* fJ */
    s16 unk002;  /* timer (lha, xoris signed int->float) */  /* fJ */
    s32 unk004;  /* active */  /* fJ */
    s16 unk008;  /* index (extsh, sth) */
    s16 unk00A;  /* linked model id */
    HuVecF unk00C;  /* position */  /* fJ */
}; /* size 0x18 (fI) */

struct M510_ENDPIECE_s {
    s16 unk000;  /* mode */  /* fJ */
    s16 unk002;  /* timer (signed) */  /* fJ */
    s32 unk004;  /* active */  /* fJ */
    s16 unk008;  /* index */
    s16 unk00A;  /* linked model id */
    HuVecF unk00C;  /* position */  /* fJ */
    float unk018;  /* heading (deg) */  /* fJ */
    float unk01C;  /* speed */  /* fJ */
}; /* size 0x20 (fI) */

struct M510_ENDING_s {
    s32 unk000;  /* frame counter while unk9A0 */
    s16 unk004;  /* model 0x440008 */
    s16 unk006;  /* model 0x440009 */
    s16 unk008;  /* model 0x44000A */
    s16 unk00A;  /* model 0x44000B */
    s16 unk00C;  /* model 0x44000C */
    s16 unk00E;  /* model 0x44000F */
    s16 unk010;  /* model 0x440010 */
    s16 unk012;  /* model 0x440011 */
    s16 unk014;  /* motion of unk004 */
    s16 unk016;  /* motion of unk006 */
    s16 unk018;  /* motion of unk008 */
    s16 unk01A;  /* motion of unk00A */
    s16 unk01C;  /* motion of unk00C */
    u8 pad01E[0x2];
    M510_ENDOBJ unk020[16];
    M510_ENDPIECE unk1A0[64];
    s32 unk9A0;  /* winner scene running */
    s32 unk9A4;  /* compared >= 30 (cmpwi) */
    float unk9A8;  /* model unk00E y */
    float unk9AC;  /* its velocity */
    float unk9B0;  /* model unk010 y */
    float unk9B4;  /* fork I */
    float unk9B8;  /* model unk012 y */
    float unk9BC;  /* fork I */
}; /* size 0x9C0 (fI) */


/* m510.c: the work block, allocated by the init hook fn_1_E8. */
extern M510_WORK *lbl_1_bss_0;

/* --- m510.c --- */
void ObjectSetup(void);
void fn_1_E8(s16 mode, s16 frameNo);
void fn_1_164(s16 mode, s16 frameNo);
void fn_1_1C0(s16 mode, s16 frameNo);
void fn_1_21C(s16 mode, s16 frameNo);
void fn_1_260(s16 mode, s16 frameNo);
void fn_1_2BC(s16 mode, s16 frameNo);
void fn_1_30C(s16 mode, s16 frameNo);
void fn_1_404(s16 mode, s16 frameNo);
void fn_1_494(s16 mode, s16 frameNo);
void fn_1_568(s16 mode, s16 frameNo);
int fn_1_5B4(int seId);
void fn_1_5DC(int seNo);
void fn_1_604(int seNo, s32 speed);
void fn_1_634(int seNo, s16 pan);
void fn_1_664(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
int fn_1_6BC(s16 streamId);
void fn_1_6E4(int streamNo, s32 speed);
void fn_1_714(void);
int fn_1_734(s16 streamId);
int fn_1_75C(s16 streamId);
int fn_1_784(s16 streamId, s16 chanNo);
void fn_1_7B4(M510_WORK *work, OMOBJMAN *objman);
void fn_1_9B8(M510_WORK *work, s16 mode);
s32 fn_1_C6C(M510_WORK *work, s16 idx, s16 kind);
void fn_1_D84(M510_WORK *work);
s32 fn_1_E54(M510_WORK *work, s32 arg1);
void fn_1_1074(M510_WORK *work);
s32 fn_1_1274(M510_WORK *work);
s32 fn_1_129C(M510_WORK *work);
s32 fn_1_1308(M510_WORK *work);
s32 fn_1_1310(M510_WORK *work);
void fn_1_1338(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_2148(HuVecF *start, HuVecF *end, GXColor *color);
void fn_1_2220(HuVecF *pos, float size, GXColor *color);
void fn_1_2390(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color);
void fn_1_24D0(Quaternion *out, HuVecF *from, HuVecF *to);
float fn_1_2840(float cur, float target, float rate);

/* --- stage.c --- */
void fn_1_295C(M510_STAGE *stage, M510_WORK *work);
void fn_1_2F8C(M510_STAGE *stage);
void fn_1_3020(M510_STAGE *stage);
void fn_1_30D8(M510_STAGEOBJ *obj, u16 kind, HuVecF *pos, float scale, M510_STAGE *stage);
void fn_1_33C0(M510_STAGEOBJ *obj);
void fn_1_3418(M510_STAGEOBJ *obj);
void fn_1_3598(M510_STAGENUM *num, s16 digit, HuVecF *pos, M510_STAGE *stage);
void fn_1_3834(M510_STAGENUM *num);
void fn_1_38A0(M510_STAGENUM *num);

/* --- player.c --- */
void fn_1_3A64(M510_PLAYER *player, s16 playerNo, M510_WORK *work);
void fn_1_3CCC(M510_PLAYER *player);
s32 fn_1_3D34(M510_PLAYER *player);

/* --- playermodel.c --- */
void fn_1_3DC8(M510_PLAYERMODEL *pm, s16 no, M510_PLAYER *player);
void fn_1_4284(M510_PLAYERMODEL *pm);
s32 fn_1_4328(M510_PLAYERMODEL *pm);
void fn_1_4770(M510_PLAYERMODEL *pm);

/* --- pitch.c --- */
void fn_1_47C4(M510_PITCH *pitch, M510_PLAYER *player);
void fn_1_49A4(M510_PITCH *pitch);
void fn_1_49F4(M510_PITCH *pitch);

/* --- ball.c --- */
void fn_1_509C(M510_BALL *ball, M510_PLAYER *player);
void fn_1_51B4(M510_BALL *ball);
void fn_1_5230(M510_BALL *ball);
M510_BALLOBJ *fn_1_52B0(M510_BALL *ball, HuVecF *pos, s16 kind);
void fn_1_53E0(M510_BALLOBJ *obj, s16 no, M510_BALL *ball);
void fn_1_557C(M510_BALLOBJ *obj);
void fn_1_55C4(M510_BALLOBJ *obj);
void fn_1_5E40(M510_BALLOBJ *obj);
void fn_1_64B0(M510_BALLOBJ *slot, HuVecF *pos);
s32 fn_1_7038(M510_BALLOBJ *obj, HuVecF *hit);
void fn_1_8060(M510_BALL *ball, M510_BALLOBJ *slot, s16 type, s32 on);

/* --- pad.c --- */
void fn_1_8184(M510_PAD *pad, s32 playerNo, M510_PLAYERMODEL *owner);
void fn_1_81F4(M510_PAD *pad);
void fn_1_8234(M510_PAD *pad);
void fn_1_8420(M510_PADAI *ai, M510_PAD *pad);
void fn_1_8778(M510_PADAI *ai);
void fn_1_87A8(M510_PADAI *ai);

/* --- camera.c --- */
void fn_1_89B8(M510_CAMERA *cam, M510_WORK *work);
void fn_1_8B1C(M510_CAMERA *cam, s32 camBit);
void fn_1_8BEC(M510_CAMERA *cam);
void fn_1_8C1C(M510_CAMERA *cam);
void fn_1_8D48(M510_CAMERA *cam);

/* --- light.c --- */
void fn_1_959C(M510_LIGHT *light, M510_WORK *work);
void fn_1_9614(M510_LIGHT *light);
void fn_1_9668(M510_LIGHT *light);

/* --- opening.c --- */
s32 fn_1_966C(M510_WORK *work);

/* --- ending.c --- */
void fn_1_9B0C(M510_WORK *work);
void fn_1_A454(M510_WORK *work);
s32 fn_1_A4F4(M510_WORK *work);
s32 fn_1_B350(M510_WORK *work);
void fn_1_B4A4(M510_WORK *work);
void fn_1_B8F4(M510_WORK *work);
void fn_1_B958(M510_ENDOBJ *fall);
void fn_1_BE48(M510_WORK *work, HuVecF *pos);
void fn_1_BEC4(M510_ENDPIECE *rise);

/* --- ball_path.c --- */
void fn_1_C590(M510_BALLPATH *path);
void fn_1_C5C0(M510_BALLPATH *path);
void fn_1_C5F0(M510_BALLPATH *path);
void fn_1_C650(M510_BALLPATH *path, HuVecF pos, s32 time);
HuVecF fn_1_C70C(M510_BALLPATH *path, s32 time, float tension);
HuVecF fn_1_CAD0(M510_BALLPATH *path, s32 idx, float tension);
HuVecF fn_1_CC58(float t, HuVecF p0, HuVecF p1, HuVecF m0, HuVecF m1);
float fn_1_CD18(float t, float p0, float p1, float m0, float m1);

/* --- score.c --- */
void fn_1_CE04(M510_SCORE *score, u16 mode, s16 idx);
void fn_1_D1AC(M510_SCORE *score);
void fn_1_D234(M510_SCORE *score);
void fn_1_D354(M510_SCORE *score, s32 disp);

#endif
