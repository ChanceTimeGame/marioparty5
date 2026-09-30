#ifndef M575DLL_H
#define M575DLL_H

/*
 * m575dll (overlay #86): types and prototypes shared by its fourteen translation
 * units.
 *
 * Offsets are GameCube ones from build/mp5-asm/m575dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/hu3d.h"

#include "game/mg/score.h"
#include "game/sprite.h"

/*
 * Merged by fork A (header owner) from forks A, B, C, E. D (opening/tubo) and F
 * (effect/camera/jugem) were still running: M575_TUBO, M575_CAMERA and M575_JUGEM are
 * MINIMAL VIEWS (measured fields only, GC-layout padding) that D/F replace by offset.
 * Owners: A = WORK TEAM SCORE LIGHT PATH; B = COM; C = COINMGR COIN TUBOEFF;
 * E = PLAYER STAGE STAGEOBJ TEN.
 */
typedef struct M575_WORK_s M575_WORK;
typedef struct M575_TEAM_s M575_TEAM;
typedef struct M575_PLAYER_s M575_PLAYER;
typedef struct M575_COM_s M575_COM;
typedef struct M575_TUBOEFF_s M575_TUBOEFF;
typedef struct M575_TEN_s M575_TEN;
typedef struct M575_STAGEOBJ_s M575_STAGEOBJ;
typedef struct M575_STAGE_s M575_STAGE;
typedef struct M575_CAMERA_s M575_CAMERA;
typedef struct M575_LIGHT_s M575_LIGHT;
typedef struct M575_TUBO_s M575_TUBO;
typedef struct M575_COIN_s M575_COIN;
typedef struct M575_COINMGR_s M575_COINMGR;
typedef struct M575_SCORE_s M575_SCORE;
typedef struct M575_JUGEM_s M575_JUGEM;
typedef struct M575_PATH_s M575_PATH;

/* fork B: COM AI state, embedded in the player at +0x2C (player.c: addi r3, r31, 0x2c; bl fn_1_6630) */
struct M575_COM_s {
    M575_PLAYER *unk000;  /* owning player (fn_1_6630 0x665C stw r30) */
    u16 unk004;  /* action: 0 wander 1 chase ten 2 carry coin 3 wait/jump (switch 0x6B1C) */
    s16 unk006;  /* action timer, frand()%30+30 (lha/sth) */
    s32 unk008;  /* GwPlayerConf[].type copy (0x6678); player 0x5690 tests it before MgPlayerPadSet */
    s32 unk00C;  /* COM enabled; fn_1_678C returns at once when 0. = player+0x38: 0 in m575 fn_1_334, 1 in fn_1_F3C */
    u16 unk010;  /* level: dif 3->0, 2->1, 1->2, else 3 (lhz/cmplwi) */
    u8 pad012[0x2];
    HuVecF unk014;  /* stick target vector (fn_1_8180 PSVECSubtract a0) */
    HuVecF unk020;  /* wander point (fn_1_7A80) */
    s32 unk02C;  /* request A-press */
    s32 unk030;  /* A-hold in progress */
    float unk034;  /* smoothed stick x */
    float unk038;  /* smoothed stick z */
    s32 unk03C;  /* btnDown (ori 0x100) */
    s32 unk040;  /* stick x (s8 of 56*unk034) */
    s32 unk044;  /* stick y (s8 of 56*-unk038) */
    s32 unk048;  /* btn (ori 0x100) */
}; /* size 0x4C (GC) */

/* fork E: player, team+0x8 [2] (m575 0x0F7C mulli 0xcc; player fn_1_535C memset 0xcc) */
struct M575_PLAYER_s {
    M575_TEAM *unk000;  /* fn_1_535C 0x539C stw a3 */
    u16 unk004;  /* state: opening (fn_1_E050) and finish walk 0..3 (m575 fn_1_14F0): lhz, sth */
    s16 unk006;  /* timer (opening: sth 0) */
    MGPLAYER *unk008;  /* MgPlayerCreate result 0x5478; ->mode (0x28), ->actor (0x3C) */
    s16 unk00C;  /* a1: side (odd -> x = 150, even -> x = -150) */
    s16 unk00E;  /* a2: player no (GwPlayerConf, bss_7810 slot, MgPlayerCreate, GwPlayer[] mulli 0x108, omVibrate) */
    s32 unk010;  /* charNo (GwPlayerConf[].charNo 0x53BC lha -> stw); CharLoseVoicePlay (m575 fn_1_FEC) */
    s16 unk014;  /* actor model (player->actor->mdlId, 0x5488 extsh) */
    s16 unk016[9];  /* CharMotionCreate lbl_1_data_A0[charNo][i]; m575 uses [0] idle/end, [1] walk, [7] win, [8] lose; jugem [6] */
    float unk028;  /* CharModelHeightGet */
    M575_COM unk02C;  /* fork B: fn_1_6630(&player->unk02C, player) */
    HuVecF *unk078;  /* &Hu3DData[model].pos */
    HuVecF *unk07C;  /* &Hu3DData[model].rot */
    u8 pad080[0x4];
    float unk084;  /* fall speed (velY / 100, clamped <= 0, -1.5/frame to -225) */
    HuVecF unk088;  /* position in the ten's frame, minus the ten position */
    float unk094;  /* horizontal distance from the ten centre (150 at init) */
    M575_COIN *unk098;  /* nearest coin (coin fn_1_B0E8 stw; com 0x6A70 cmplwi 0) */
    float unk09C;  /* its horizontal distance (coin fn_1_B0E8, 1000000 reset) */
    s32 unk0A0;  /* frame counter */
    s32 unk0A4;  /* pad input enabled (0 at init; 0 -> MgPlayerPadSet all zero) */
    s32 unk0A8;  /* set once mode == 1 (jump) */
    s16 unk0AC;  /* frames since unk0A8, capped at 60 */
    u8 pad0AE[0x2];
    s32 unk0B0;  /* fell off (y < -25) */
    s32 unk0B4;  /* airborne (mode 1 or 2) */
    s32 unk0B8;  /* landed on another player this jump (narrow hook) */
    float unk0BC;  /* previous actor->velY */
    HuVecF unk0C0;  /* push from a head-landing, decays 0.8/frame */
}; /* size 0xCC (GC) */

/* fork C: rigid-body integrator embedded in tubo (+0x2C) and ten (+0x2C) */
struct M575_TUBOEFF_s {
    u8 pad000[0x4];
    u16 unk004;  /* inertia shape: 0 = cylinder formula, else box (fn_1_9320 0x9374 clrlwi/cmpwi) */
    u8 pad006[0x2];
    float unk008;  /* mass (fn_1_9320 f1; fn_1_9728 1/mass) */
    float unk00C;  /* principal inertia x */
    float unk010;  /* principal inertia y */
    float unk014;  /* principal inertia z */
    Mtx unk018;  /* inverse body inertia: identity with diag 1/unk00C..014 */
    Mtx unk048;  /* orientation; rows renormalised each step (com reads row 1 = 0x58..0x60) */
    Mtx unk078;  /* inverse orientation (PSMTXInverse 0x9A88); player fn_1_562C PSMTXCopy source */
    Vec unk0A8;  /* linear momentum; damped 0.9999 (ten 0x4FC0 scales 0.9) */
    Vec unk0B4;  /* angular momentum; damped 0.9999 (ten 0x4FD8 scales 0.9) */
    Vec unk0C0;  /* position (+= dt*velocity) */
    Vec unk0CC;  /* force accumulator (fn_1_9B58), zeroed every step */
    Vec unk0D8;  /* torque accumulator (fn_1_9B58 cross product), zeroed every step */
    float unk0E4;  /* fn_1_9320 f2 (radius/extent) */
    float unk0E8;  /* fn_1_9320 f3 (height) */
}; /* size 0xEC (GC; memset 0xEC) -- no pointers, same on host */

/* fork E: ten (the balance board): team+0x1A0 (fn_1_4BCC memset 0x118) */
struct M575_TEN_s {
    M575_TEAM *unk000;
    s16 unk004;  /* model m575 0x07 (team 0) / 0x06 (team 1) */
    s16 unk006;  /* motion m575 0x16 / 0x15 */
    HuVecF *unk008;  /* &Hu3DData[unk004].pos */
    MtxPtr unk00C;  /* Hu3DData[unk004].mtx */
    s16 unk010;  /* model m575 0x0E (DISPOFF); m575 fn_1_730 puts it in work->unk25E0 (MgActorColMapInit) */
    u8 pad012[0x2];
    HuVecF *unk014;  /* &Hu3DData[unk010].pos */
    MtxPtr unk018;  /* Hu3DData[unk010].mtx */
    s16 unk01C;  /* timer, counts down; set to 4 by player fn_1_5CD8 */
    u8 pad01E[0x2];
    float unk020;  /* tilt angle (deg, 0..90); m575 fn_1_FEC waits for < 3 */
    float unk024;  /* previous tilt angle */
    s16 unk028;  /* SE cooldown (30) */
    u8 pad02A[0x2];
    M575_TUBOEFF unk02C;  /* fork C */
}; /* size 0x118 (GC) */

/* fork E: one stage block: stage+0x20 [60] (fn_1_4538 memset 0x30) */
struct M575_STAGEOBJ_s {
    M575_STAGE *unk000;  /* the stage */
    u16 unk004;  /* state 0..5 (fn_1_46B4 lhz switch) */
    s16 unk006;  /* index */
    s16 unk008;  /* Hu3DModelLink(stage->unk00A) */
    u8 pad00A[0x2];
    HuVecF unk00C;  /* rest position */
    HuVecF unk018;  /* position */
    float unk024;  /* velocity y */
    float unk028;  /* target rot z */
    float unk02C;  /* rot z */
}; /* size 0x30 (GC) */

/* fork E: stage: team+0x2B8 (fn_1_3DE0 memset 0xb68) */
struct M575_STAGE_s {
    M575_TEAM *unk000;
    u8 pad004[0x4];
    s16 unk008;  /* model m575 0x00 */
    s16 unk00A;  /* model m575 0x01 (block template, DISPOFF) */
    s16 unk00C;  /* model m575 0x02 (its motion time drives SE 0x932/0x933) */
    s16 unk00E;  /* model m575 0x03 */
    s16 unk010;  /* model m575 0x04 */
    s16 unk012;  /* model m575 0x05 at z 8000 */
    s16 unk014;  /* motion m575 0x0F on unk008 */
    s16 unk016;  /* motion m575 0x10 on unk00C */
    s16 unk018;  /* motion m575 0x11 on unk00E */
    s16 unk01A;  /* motion m575 0x12 on unk012 */
    float unk01C;  /* previous motion time of unk00C */
    M575_STAGEOBJ unk020[60];
    s32 unkB60;  /* blocks live */
    u8 padB64[0x4];
}; /* size 0xB68 (GC) */

/* fork F: camera, team+0xE20 (fn_1_851C memset 0x68) */
struct M575_CAMERA_s {
    M575_TEAM *unk000;  /* fn_1_851C a2 */
    s32 unk004;  /* camera bit (lbl_1_data_278[idx*4]): Hu3DModelCameraSet (clrlwi 16), MgPlayerCreate (extsh), Hu3D3Dto2D (raw) */
    u8 pad008[0x4];
    HuVecF unk00C;  /* eye goal */
    HuVecF unk018;  /* eye current */
    HuVecF unk024;  /* target goal */
    HuVecF unk030;  /* target current */
    HuVecF unk03C;  /* eye shake offset */
    HuVecF unk048;  /* target shake offset */
    HuVecF unk054;  /* up */
    float unk060;  /* follow rate, 0.4 */
    s32 unk064;  /* shake on (lwz, cmpwi 0) */
}; /* size 0x68 (GC) */
extern s32 lbl_1_data_278[8];

/* fork A */
struct M575_LIGHT_s {
    M575_TEAM *unk000;  /* owning team (fn_1_9250 a1) */
    s16 unk004;  /* HU3DLIGHTID: lha + cmpwi (signed) */
    u8 pad006[0x2];
}; /* size 0x8 (GC) */

/* fork D: tubo, team+0xE90 (fn_1_9BC8 memset 0x14C) */
struct M575_TUBO_s {
    M575_TEAM *unk000;  /* owning team (fn_1_9BC8 a1) */
    u16 unk004;  /* state 0/1: lhz, switch cmpwi; ==1 cmplwi (com 0x7A40) */
    s16 unk006;  /* timer: lha, xoris int->float */
    s16 unk008;  /* model (0x820009 team 0, 0x820008 team 1) */
    u8 pad00A[0x2];
    HuVecF *unk00C;  /* &Hu3DData[unk008].pos */
    MtxPtr unk010;  /* Hu3DData[unk008].mtx */
    s16 unk014;  /* model 0x82000D */
    s16 unk016;  /* motion 0x820017 */
    HuVecF *unk018;  /* &Hu3DData[unk014].pos */
    MtxPtr unk01C;  /* Hu3DData[unk014].mtx */
    float unk020;  /* bob height 320 + 15 sin */
    float unk024;  /* shake height 130 sin */
    float unk028;  /* max tilt angle seen */
    M575_TUBOEFF unk02C;  /* fork C */
    Mtx unk118;  /* wobble matrix */
    s16 unk148;  /* coin shot counter: lha, cmpw vs work->unk2606[] */
    s16 unk14A;  /* index into work->unk2606: lha, cmpw vs work->unk2604 (<= 2) */
}; /* size 0x14C (GC) */

/* fork C: one in-game coin (the minigame's objects; not a board payout) */
struct M575_COIN_s {
    M575_COINMGR *unk000;  /* owning manager (fn_1_B2E0 arg 2) */
    s16 unk004;  /* cleared (fn_1_B91C, fn_1_BB6C) */
    s16 unk006;  /* post-game blink counter: odd -> hide, >60 -> remove (fn_1_B354 lha) */
    u16 unk008;  /* kind: 1 = big coin (model 2A6, scale 1, +5 score), else small (2A4, 1.33, +1) */
    s16 unk00A;  /* model (Hu3DModelLink result) */
    Vec *unk00C;  /* &Hu3DData[unk00A].pos (fn_1_B91C 0xBA8C) */
    Mtx *unk010;  /* &Hu3DData[unk00A].mtx (fn_1_B91C 0xBAA4 +0xF0); set/cleared only */
    s32 unk014;  /* active */
    Vec unk018;  /* velocity (y = -0.8 gravity per frame, 0xB450) */
    float unk024;  /* target x (fn_1_B91C arg 4 ->x) */
    float unk028;  /* 0 */
    float unk02C;  /* target z (arg 4 ->z) */
    float unk030;  /* start x */
    float unk034;  /* start y */
    float unk038;  /* start z */
    float unk03C;  /* launch height scale (fn_1_B91C f1) */
    float unk040;  /* y at bounce (0xB5D8) */
    s32 unk044;  /* bounced off the ten board (fn_1_BC18 0xC128) */
    Vec unk048;  /* coin position in ten-board space (fn_1_BC18 0xBD04) */
}; /* size 0x54 (GC; fn_1_B2E0/fn_1_B324 memset 0x54) */

/* fork C: team+0xFDC */
struct M575_COINMGR_s {
    M575_TEAM *unk000;  /* the team (fn_1_AEF0 arg 2) */
    M575_COIN unk004[8];
    s16 unk2A4;  /* small coin template model (0x82000A) */
    s16 unk2A6;  /* big coin template model (0x82000B) */
}; /* size 0x2A8 (GC; fn_1_AEF0/fn_1_B074 memset 0x2A8) */

/* fork A: team+0x1284 */
struct M575_SCORE_s {
    M575_TEAM *unk000;  /* owning team (fn_1_3A7C a2) */
    u16 unk004;  /* side: 0 = team 0 (left, red), else right (blue); clrlwi 16 + cmplwi */
    HUSPRGRPID unk006;  /* MgScoreWinCreate: lha */
    MGSCORE *unk008;  /* MgScoreCreate: lwz */
    s16 unk00C;  /* esprite 0x820019: lha */
    s16 unk00E;  /* esprite 0x960046: lha */
    s16 unk010;  /* team coin count (coin fn_1_C184: +1 small, +5 big); paid into GwPlayer[].mgCoin by m575 fn_1_FEC */
    u8 pad012[0x2];
}; /* size 0x14 (GC) */

/* fork F: jugem, team+0x1298 */
struct M575_JUGEM_s {
    M575_TEAM *unk000;  /* fn_1_C464 a1 */
    u16 unk004;  /* state (lhz, cmplwi 6: jumptable_1_data_2F0) */
    s16 unk006;  /* state timer, only ever zeroed */
    s16 unk008;  /* model */
    s16 unk00A;  /* motion 0x820013 (fly) */
    s16 unk00C;  /* motion 0x820014 (hold) */
    u8 pad00E[0x2];
    HuVecF unk010;  /* position */
    HuVecF unk01C;  /* goal position */
    M575_PLAYER *unk028;  /* carried player (cmplwi 0; player 0x5A94 cmplw) */
    s32 unk02C;  /* player hooked flag */
    HuVecF unk030;  /* drop point offset */
    HuVecF unk03C;  /* hook offset (itemhook_sao - pos, y -= 120) */
}; /* size 0x48 (GC) */

/* fork F: particle parameters (= m504 M504_EFFECTPARAM); copied by value into the 0x20D0 work (0x38 x 150) */
typedef struct M575_EFFECTPARAM_s {
    u32 unk000;  /* flags: bit 0 = flicker */
    GXColor unk004;  /* colour start */
    GXColor unk008;  /* colour end */
    HuVecF unk00C;  /* velocity */
    HuVecF unk018;  /* speed decay */
    float unk024;  /* y acceleration */
    float unk028;
    float unk02C;  /* scale decay */
    float unk030;  /* alpha step */
    float unk034;  /* colour step */
} M575_EFFECTPARAM; /* size 0x38 (GC) */
extern M575_EFFECTPARAM lbl_1_data_3A0;
extern M575_EFFECTPARAM *lbl_1_bss_7BB8;
extern s16 lbl_1_bss_7B98[16];

/* fork A: work+0x18 [2] (mulli 0x12E0; fn_1_3880 memset 0x12E0) */
struct M575_TEAM_s {
    M575_WORK *unk000;  /* the work (fn_1_3880 a2) */
    s16 unk004;  /* team index 0/1 (fn_1_3880 a1); coin pan base: nonzero -> 80 else 48 */
    u8 pad006[0x2];
    M575_PLAYER unk008[2];  /* stride 0xCC (mulli 0xCC) */
    M575_TEN unk1A0;
    M575_STAGE unk2B8;
    M575_CAMERA unkE20;
    M575_LIGHT unkE88;
    M575_TUBO unkE90;
    M575_COINMGR unkFDC;
    M575_SCORE unk1284;
    M575_JUGEM unk1298;
}; /* size 0x12E0 (GC) */

/* fork A: lbl_1_bss_0 (HuMemDirectMallocNum 0x2614 at m575 0x104) */
struct M575_WORK_s {
    OMOBJMAN *unk000;  /* MgActorObjectSetup() (fn_1_730 a1) */
    u8 pad004[0x4];
    s32 unk008;  /* frame counter (fn_1_D08); bit 0 gates CharModelCryCreate (player 0x6434); % 30 coin spin */
    u16 unk00C;  /* seq mode tag 0..8: sth (m575); lhz + cmplwi in player/stage/ten/coin */
    u16 unk00E;  /* finish state 0..4: lhz + cmpwi (fn_1_FEC) */
    s32 unk010;  /* timer 1800: decremented in MGSEQ_MODE_MAIN (fn_1_D08) */
    s16 unk014;  /* finish wait: lha, cmpwi 0x1E / 0xD1 (fn_1_FEC) */
    u8 pad016[0x2];
    M575_TEAM unk018[2];  /* stride 0x12E0 (mulli 0x12E0) */
    s32 unk25D8;  /* 1 while in MGSEQ_MODE_START (fn_1_2DC/334) */
    s32 unk25DC;  /* GAMEMESID or -1: GameMesKill (fn_1_C5C) */
    HU3DMODELID unk25E0[16];  /* MgActorColMapInit model list, per colMesh (player fn_1_5CD8 0x5D6C lhax) */
    s16 unk2600;  /* model list count (2) */
    s16 unk2602;  /* esprite 0x820018 (fn_1_730) */
    s16 unk2604;  /* frand() & 1 ? 1 : 2 */
    s16 unk2606[2];  /* coin-shot thresholds (tubo lhax [tubo->unk14A < unk2604]): [0] = frand() % 20 + 5; [1] (only if unk2604 == 2) = frand() % 10 + [0] + 10 */
    u8 pad260A[0x2];
    s32 unk260C;  /* BGM stream (fn_1_6B0 0x35) or -1 */
    s32 unk2610;  /* -1 */
}; /* size 0x2614 (GC) */

/* fork A: spline of up to 20 keys, 4 keys per cubic segment (fn_1_3248 / fn_1_33C4, used by opening.c) */
struct M575_PATH_s {
    s16 unk000;  /* key count: lha (signed) */
    u8 pad002[0x2];
    HuVecF unk004[20];  /* key positions (mulli 0xC) */
    s32 unk0F4[20];  /* per-key time */
    s32 unk144[20];  /* cumulative time: cmpw (signed) */
}; /* size 0x194 (GC) */

extern M575_WORK *lbl_1_bss_0;  /* the work block; player.c reads it */
extern OMOBJMAN *lbl_1_bss_4;
extern M575_PLAYER *lbl_1_bss_7810[4];  /* player.c: per player no */

void MgActorColMaskSet(MGACTOR *actorP, u32 mask); /* DOL, no header prototype (m564Dll.h precedent) */


/* --- m575.c --- */
void ObjectSetup(void);
void fn_1_E8(s16 mode, s16 frameNo);
void fn_1_164(s16 mode, s16 frameNo);
void fn_1_1C0(s16 mode, s16 frameNo);
void fn_1_21C(s16 mode, s16 frameNo);
void fn_1_280(s16 mode, s16 frameNo);
void fn_1_2DC(s16 mode, s16 frameNo);
void fn_1_334(s16 mode, s16 frameNo);
void fn_1_444(s16 mode, s16 frameNo);
void fn_1_4A0(s16 mode, s16 frameNo);
void fn_1_4EC(s16 mode, s16 frameNo);
int fn_1_530(int seId);
void fn_1_558(int seNo);
void fn_1_580(int seNo, s32 speed);
void fn_1_5B0(int seNo, s16 pan);
void fn_1_5E0(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
int fn_1_638(s16 streamId);
void fn_1_660(int streamNo, s32 speed);
void fn_1_690(void);
int fn_1_6B0(s16 streamId);
int fn_1_6D8(s16 streamId);
int fn_1_700(s16 streamId, s16 chanNo);
void fn_1_730(M575_WORK *work, OMOBJMAN *objman);
void fn_1_C5C(M575_WORK *work);
s32 fn_1_D08(M575_WORK *work, s32 arg1);
s32 fn_1_F14(M575_WORK *work);
s32 fn_1_F3C(M575_WORK *work);
s32 fn_1_FEC(M575_WORK *work);
s32 fn_1_14F0(M575_PLAYER *player);
s32 fn_1_1C00(OMOBJ *obj);
void fn_1_1C28(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_2A38(HuVecF *start, HuVecF *end, GXColor *color);
void fn_1_2B10(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color);
void fn_1_2C1C(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color);
void fn_1_2D5C(Quaternion *out, HuVecF *from, HuVecF *to);
float fn_1_30CC(float cur, float target, float rate);
void fn_1_31E8(M575_PATH *path);
void fn_1_3218(M575_PATH *path);
void fn_1_3248(M575_PATH *path, HuVecF pos, s32 time);
HuVecF fn_1_33C4(M575_PATH *path, s32 time);
HuVecF fn_1_36E4(float t, HuVecF p0, HuVecF p1, HuVecF p2, HuVecF p3);
float fn_1_37A4(float t, float p0, float p1, float p2, float p3);
void fn_1_3880(M575_TEAM *team, s16 idx, M575_WORK *work);
void fn_1_396C(M575_TEAM *team);
s32 fn_1_39E4(M575_TEAM *team);

/* --- score.c --- */
void fn_1_3A7C(M575_SCORE *score, u16 side, M575_TEAM *team);
void fn_1_3CD8(M575_SCORE *score);
void fn_1_3D28(M575_SCORE *score);
void fn_1_3D5C(M575_SCORE *score, s32 disp);

/* --- stage.c --- */
void fn_1_3DE0(M575_STAGE *stage, M575_TEAM *team);
void fn_1_4360(M575_STAGE *stage);
void fn_1_442C(M575_STAGE *stage);
void fn_1_4538(M575_STAGEOBJ *obj, s16 idx, M575_STAGE *stage);
void fn_1_463C(M575_STAGEOBJ *obj);
s32 fn_1_46B4(M575_STAGEOBJ *obj);

/* --- ten.c --- */
void fn_1_4BCC(M575_TEN *ten, M575_TEAM *team);
void fn_1_4E98(M575_TEN *ten);
void fn_1_4EF0(M575_TEN *ten);

/* --- player.c --- */
void fn_1_535C(M575_PLAYER *player, s16 side, s16 playerNo, M575_TEAM *team);
void fn_1_55EC(M575_PLAYER *player);
s32 fn_1_562C(M575_PLAYER *player);
void fn_1_5C88(M575_PLAYER *player, s32 on);
void fn_1_5CD8(MGACTOR *actor, int param);
int fn_1_5FC8(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_61CC(MGPLAYER *playerP);

/* --- com.c --- */
void fn_1_6630(M575_COM *com, M575_PLAYER *player);
void fn_1_675C(M575_COM *com);
void fn_1_678C(M575_COM *com);
s32 fn_1_6BE4(M575_COM *com);
s32 fn_1_734C(M575_COM *com);
s32 fn_1_79A0(M575_COM *com);
s32 fn_1_7A80(M575_COM *com);
s32 fn_1_8180(M575_COM *com);

/* --- camera.c --- */
void fn_1_851C(M575_CAMERA *cam, s32 idx, M575_TEAM *team);
void fn_1_86A8(M575_CAMERA *cam, s32 camBit);
void fn_1_8778(M575_CAMERA *cam);
void fn_1_87A8(M575_CAMERA *cam);
void fn_1_89D8(M575_CAMERA *cam, M575_CAMERA *cam2, float t);
void fn_1_8C68(M575_CAMERA *cam);

/* --- light.c --- */
void fn_1_9250(M575_LIGHT *light, M575_TEAM *team);
void fn_1_92C8(M575_LIGHT *light);
void fn_1_931C(M575_LIGHT *light);

/* --- tuboeff.c --- */
void fn_1_9320(M575_TUBOEFF *eff, u16 shape, float mass, float w, float h);
void fn_1_96F8(M575_TUBOEFF *eff);
void fn_1_9728(M575_TUBOEFF *eff);
void fn_1_9B58(M575_TUBOEFF *eff, Vec *arm, Vec *point);

/* --- tubo.c --- */
void fn_1_9BC8(M575_TUBO *tubo, M575_TEAM *team);
void fn_1_9E8C(M575_TUBO *tubo);
void fn_1_9EE4(M575_TUBO *tubo);
s32 fn_1_AAAC(M575_TUBO *tubo, M575_PLAYER *player);

/* --- coin.c --- */
void fn_1_AEF0(M575_COINMGR *mgr, M575_TEAM *team);
void fn_1_B074(M575_COINMGR *mgr);
void fn_1_B0E8(M575_COINMGR *mgr);
M575_COIN *fn_1_B240(M575_COINMGR *mgr, u16 kind, Vec *pos, Vec *target, float height);
void fn_1_B2E0(M575_COIN *coin, M575_COINMGR *mgr);
void fn_1_B324(M575_COIN *coin);
s32 fn_1_B354(M575_COIN *coin);
void fn_1_B91C(M575_COIN *coin, u16 kind, Vec *pos, Vec *target, float height);
void fn_1_BB6C(M575_COIN *coin);
void fn_1_BC18(M575_COIN *coin, M575_TEN *ten);
s32 fn_1_C184(M575_COIN *coin, M575_PLAYER *player);

/* --- jugem.c --- */
void fn_1_C464(M575_JUGEM *jugem, M575_TEAM *team);
void fn_1_C5E0(M575_JUGEM *jugem);
void fn_1_C630(M575_JUGEM *jugem);
void fn_1_CD90(M575_JUGEM *jugem, s32 flag);
void fn_1_CFE4(M575_JUGEM *jugem, M575_PLAYER *player);

/* --- opening.c --- */
s32 fn_1_D00C(M575_WORK *work);
s32 fn_1_E050(M575_WORK *work, M575_PLAYER *player);

/* --- effect.c --- */
s32 fn_1_E424(OMOBJ *obj);
void fn_1_E478(void);
void fn_1_E4C8(void);
void fn_1_E55C(s16 cameraBit, HuVecF *pos);
s16 fn_1_E6E4(s16 cameraBit, float posX, float posY, float posZ, float scale, M575_EFFECTPARAM *param);
void fn_1_E988(void);
void fn_1_EBEC(void);
void fn_1_EE10(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

#endif
