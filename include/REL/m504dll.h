#ifndef M504DLL_H
#define M504DLL_H

/*
 * m504dll (overlay #18): types and prototypes shared by its eleven translation
 * units (m504 player stage wanwan input com camera light particle opening ending).
 *
 * Offsets are GameCube ones from build/mp5-asm/m504dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/mg/timer.h"


typedef struct M504_WORK_s M504_WORK; /* lbl_1_bss_0: the work block (fork A defines it) */
typedef struct M504_LANE_s M504_LANE; /* per-player hub, work+0x40 [4] (stage fn_1_23DC) */
typedef struct M504_STAGE_s M504_STAGE; /* lane+0x15C (stage fn_1_255C) */

typedef struct M504_PLAYER_s M504_PLAYER;
typedef struct M504_INPUT_s M504_INPUT;

/* COM route walker (0x24 at input+4; fork I owns). First cut by fork P from input.s
 * (fn_1_B828/fn_1_BAC4); fork I completes it. */
typedef struct M504_COM_s {
    M504_INPUT *unk000; /* owner (fn_1_BAC4 arg 2) */
    u16 unk004; /* walker state 0..7 (fn_1_BC84 lhz, cmplwi 7, jumptable_1_data_45C0): 0 walk unk00, 1 wait, 2 arm (hold A), 3 wait for the chomp, 4 walk unk04, 5 wait, 6 pick next node, 7 finished */
    u16 unk006; /* index into the current path's pos[] (fn_1_BEF0 lhz, mulli 0xC; cmpw vs path->num) */
    struct M504_NODE_s *unk008; /* current route node; start by level &lbl_1_data_2E14/2E38/2E74/2EB0 (fn_1_BAC4 0xBBF0), then fn_1_C2CC result (fn_1_BC84 0xBECC) */
    s32 unk00C; /* wait frames: fn_1_C3E0 result (clrlwi -> stw), lwz/cmpwi, decremented (fn_1_BC84) */
    s32 unk010; /* GwPlayerConf[no].type: nonzero = COM (fn_1_BAC4 0xBB14; fn_1_B8D8 tests input+0x14) */
    u16 unk014; /* COM difficulty 0..3 from GwPlayerConf[no].dif (fn_1_BAC4 0xBB94 sth; camera fn_1_C3E0 lhz 0x14, switch; com lhz, cmplwi 0/1) */
    u8 pad016[0x2];
    HuVecF unk018; /* smoothed stick direction: x/z eased 0.8/0.2 (fn_1_BEF0 lfs/stfs 0x18, 0x20; .y never touched) */
} M504_COM; /* size 0x24 (GC; input fn_1_BAC4 / com fn_1_BC54 memset) */

/* Per-player input block, embedded at player+0x20 (fn_1_B828 memsets 0x40). */
struct M504_INPUT_s {
    M504_PLAYER *unk000; /* owner (fn_1_B828 arg 3) */
    M504_COM unk004; /* COM state (fn_1_BAC4(&input->unk004, input)) */
    s32 unk028; /* pad port: GwPlayerConf[no].padNo (fn_1_B828 0xB874) */
    s32 unk02C; /* HuPadBtn (lhz -> stw) */
    s32 unk030; /* HuPadBtnDown; player tests 0x100 (A) with rlwinm 23,23 */
    s8 unk034; /* HuPadStkX, deadzone 10 (lbz + extsb) */
    s8 unk035; /* HuPadStkY, deadzone 10 */
    u16 unk036; /* HuPadBtnRep */
    s8 unk038; /* HuPadSubStkX */
    s8 unk039; /* HuPadSubStkY */
    u8 unk03A; /* HuPadTrigL */
    u8 unk03B; /* HuPadTrigR */
    u8 unk03C; /* HuPadDStk */
    u8 unk03D; /* HuPadDStkRep */
    u8 pad03E[0x2];
}; /* size 0x40 (GC; input fn_1_B828/fn_1_B898 memset) */

typedef struct M504_LIGHT_s {
    M504_WORK *unk000; /* the work (light fn_1_D03C arg 2; m510 light twin) */
    s16 unk004; /* HU3DLIGHTID (lha, cmpwi: signed) */
    u8 pad006[0x2];
} M504_LIGHT; /* size 0x8 (GC) */

/* ---- per-player lane: stage.c fn_1_23DC hub object, work+0x40 [4], stride 0x474 ----
 * Names follow fork A (M504_LANE = the 0x474 hub, M504_STAGE = the 0x260 scenery).
 * PLAYER / WANWAN / CAMERA are owned by forks P / W / C: the views below carry only
 * the fields m504.c (fork A) and stage.c (fork S) touch. Offsets are GC. */
struct M504_PLAYER_s {
    M504_LANE *unk000; /* owning lane (fn_1_5934 arg 3) */
    u16 unk004; /* cleared every frame by fn_1_5EC8 (sth only) */
    u16 unk006; /* mode (lhz; fn_1_5F58 switch): 0 walk 613C, 1 face chomp/arm 6AA0, 2 swing 7710, 3 hit by chomp 8A40, 4 lose 85AC */
    u16 unk008; /* sub-state within the mode (lhz, cmpwi switch) */
    u16 unk00A; /* frame counter (lhz, cmplwi) */
    s32 unk00C; /* player number = lane index (fn_1_5934 arg 2; m504 fn_1_460 0x4D8) */
    s32 unk010; /* GwPlayerConf[no].charNo (lwz, extsh to Char*; m504 CharLoseVoicePlay) */
    s32 unk014; /* GwPlayerConf[no].grp */
    OMOBJ *unk018; /* omAddObjEx result; mdlId[0] character, mtnId[0..11] */
    s32 unk01C; /* shift motion loops: nonzero -> HU3D_MOTATTR_LOOP */
    M504_INPUT unk020; /* input (fn_1_B828(&player->unk020, no, player)) */
    HuVecF unk060; /* position */
    HuVecF unk06C; /* velocity: fn_1_91B0 sets, fn_1_8A40 state 4 applies gravity -2.43 to .y */
    float unk078; /* walk speed (14 * stick / 56) */
    float unk07C; /* walk direction (deg) */
    float unk080; /* facing (deg), omSetRot y */
    float unk084; /* target direction (deg) */
    s16 unk088; /* current shift motion index (lha) */
    s16 unk08A; /* requested shift motion index (lha) */
    s32 unk08C; /* nonzero: go to mode 4 (lose; m504 fn_1_10C4 sets it) */
    u16 unk090; /* idle-stick counter (lhz, cmplwi 0xf) */
    u8 pad092[0x2];
    s32 unk094; /* swing window reached */
    s32 unk098; /* A pressed during turn */
    u16 unk09C; /* carried-over-chomp arc phase (lhz, cmpwi switch in fn_1_8A40 state 4) */
    u16 unk09E; /* hit/arc frame counter (lhz; unsigned int->float) */
    HuVecF unk0A0; /* fall arc: start */
    HuVecF unk0AC; /* fall arc: apex */
    HuVecF unk0B8; /* fall arc: end (fn_1_B52C result) */
    s32 unk0C4; /* nonzero: human/COM control active (stage fn_1_23DC clears it at lane+0xCC) */
    HU3DMODELID unk0C8; /* swing effect model (0x3E001E) */
    HU3DMOTID unk0CA; /* its joint motion (0x3E0039) */
    HU3DMODELID unk0CC; /* held item model (0x3E001D), hooked to the character */
    u8 pad0CE[0x2];
    s32 unk0D0; /* finished (decathlon: m504 fn_1_C64 0xE78 / fn_1_460 0x4CC); with work->unk122C, fn_1_613C auto-turns to 0 deg while the chomp is in state 6 */
}; /* size 0xD4 (GC; player fn_1_5934/fn_1_5E1C memset) -- fork P */

typedef struct M504_WANWAN_s {
    M504_LANE *unk000; /* back pointer (9680 stw r28, 0) */
    u16 unk004; /* state 0..10 (lhz/cmplwi, switch in 9CAC) */
    u16 unk006; /* timer (lhz/sth) */
    u16 unk008; /* lunge countdown: rand8() % 3 (B1AC) */
    u16 unk00A; /* lunge count, feeds speed 6.0 + 0.8 * n (9F18); only ever 0 here */
    s16 unk00C; /* chomp model */
    s16 unk00E[10]; /* chomp motions (9C10 kills [0..9]) */
    u8 pad022[0x2];
    s32 unk024; /* lwz/cmpwi -> state 9 (A994); m504 fn_1_10C4 0x11B8 sets 1 */
    s16 unk028; /* landing-dust model */
    s16 unk02A; /* its motion */
    s32 unk02C; /* dust model playing */
    s16 unk030; /* second effect model */
    s16 unk032; /* its motion */
    s32 unk034; /* second model playing */
    HuVecF unk038; /* position */
    HuVecF unk044; /* rotation (deg) */
    HuVecF unk050; /* velocity */
    HuVecF unk05C; /* model position offset (shake) */
    float unk068; /* wind-up tilt amplitude */
    float unk06C; /* wind-up phase (deg) */
    float unk070; /* opening 0x10840: 10 * cos(unk06C), roll fed to mtxRot (unk068..070 are copied as one 12-byte block at 0x100D0) */
    float unk074; /* lunge speed */
    float unk078; /* lunge heading (deg) */
    s32 unk07C; /* active: sounds play; cleared when it leaves (z > 3550) */
} M504_WANWAN; /* size 0x80 (GC): 9680/9C10 memset 0x80 */

typedef struct M504_CAMERA_s {
    M504_LANE *unk000; /* camera fn_1_C4F4 arg 3 (0xC528) */
    s32 unk004; /* camera bit lbl_1_data_45E0[idx] (camera 0xC540); stage fn_1_3D9C 0x3EA8 lwz lane+0x3C0 -> Hu3D3Dto2D */
    u8 pad008[0x4]; /* never touched in camera.c */
    HuVecF unk00C; /* eye goal (fn_1_C74C 0xC764 PSVECSubtract; C4F4 = {0,2000,0}) */
    HuVecF unk018; /* target goal (fn_1_C74C 0xC770) */
    HuVecF unk024; /* eye, eased toward unk00C by unk060 (C4F4 = {0,500,0}) */
    HuVecF unk030; /* target, eased toward unk018 */
    HuVecF unk03C; /* shake offset added to the eye (fn_1_C810) */
    HuVecF unk048; /* shake offset added to the target (fn_1_C810) */
    HuVecF unk054; /* up vector (C4F4 = {0,0,-1}; Hu3DCameraPosSetV arg 3) */
    float unk060; /* ease rate (C4F4 = 0.4; PSVECScale 0xC784) */
    u16 unk064; /* shake axis 0 x / 1 y / 2 z / 3 (x only: else-if chain) (fn_1_C99C sth; C810 lhz cmplwi) */
    u8 pad066[0x2];
    s32 unk068; /* shake frames left (C810 lwz/cmpwi, decremented) */
    float unk06C; /* shake amplitude */
    float unk070; /* shake amplitude decay factor (multiplied in per frame) */
    float unk074; /* shake phase step (deg) */
    float unk078; /* shake phase (deg), C99C = 90 */
    float unk07C; /* interpolation t (fn_1_CCEC += 1/frames, CC88 = 0, CCE4 sets) */
    HuVecF unk080; /* interpolation eye from (CB3C/CC3C) */
    HuVecF unk08C; /* interpolation target from (CB3C/CC3C) */
    HuVecF unk098; /* interpolation eye to (CC88) */
    HuVecF unk0A4; /* interpolation target to (CC88) */
} M504_CAMERA; /* size 0xB0 (GC; camera fn_1_C4F4/fn_1_C71C memset) */

/* One collision box / circle of the stage (the stage's ten "objects", filled from
 * player.c lbl_1_data_A8[i] by stage fn_1_255C 0x3A10). */
typedef struct M504_STAGEOBJ_s {
    M504_STAGE *unk000; /* back pointer (0x3A40) */
    s16 unk004; /* HU3DMODELID (Hu3DModelLink of work->unk012[data->unk00]), -1 = none (lha, cmpwi -1) */
    u8 pad006[0x2];
    s32 unk008; /* on screen: display on (fn_1_3D9C) */
    s32 unk00C; /* collision active (fn_1_4030 skips 0; fn_1_572C clears obj[1]) */
    u16 unk010; /* shape (lhz, cmplwi): 1 = circle, else box (fn_1_4030 0x4594) */
    u8 pad012[0x2];
    HuVecF unk014; /* box min corner (x, z) / circle centre */
    HuVecF unk020; /* box max corner (x, z) / circle radius in .x */
    s32 unk02C; /* data->unk1C: no model; passable unless fn_1_4030 flag */
} M504_STAGEOBJ; /* size 0x30 (GC; fn_1_255C memset) */

struct M504_STAGE_s {
    M504_LANE *unk000; /* back pointer (fn_1_255C arg 3) */
    s16 unk004; /* Hu3DModelLink(work->unk012[1]), display on */
    s16 unk006; /* Hu3DModelLink(work->unk012[2]), display off */
    s16 unk008; /* Hu3DModelLink(work->unk012[3]), display on */
    s16 unk00A; /* never written */
    s16 unk00C; /* Hu3DModelLink(work->unk012[9]), display on */
    s16 unk00E; /* Hu3DModelLink(work->unk012[4]), display on (m504 fn_1_F34 0xF84 reads it) */
    s16 unk010; /* Hu3DModelLink(work->unk012[5]), display on */
    s16 unk012; /* Hu3DModelLink(work->unk012[6]), display on */
    s16 unk014; /* Hu3DModelLink(work->unk012[10]), display on */
    s16 unk016; /* Hu3DModelLink(work->unk012[7]), display on */
    s16 unk018; /* Hu3DModelLink(work->unk012[8]), display on */
    s16 unk01A; /* Hu3DModelLink(work->unk012[11]), display on */
    s16 unk01C; /* Hu3DModelLink(work->unk012[12]), display off */
    s16 unk01E; /* Hu3DModelLink(work->unk012[13]), display off */
    s16 unk020; /* Hu3DModelLink(work->unk012[14]), display off */
    s16 unk022; /* model 0x3E0016 (fn_1_4FEC shift-motion actor) */
    s16 unk024[3]; /* motions 0x3E0026..28 of unk022: [0] idle, [1] after, [2] trigger */
    u16 unk02A; /* fn_1_4FEC state (lhz; fn_1_5870 kind 4 sets 1) */
    s16 unk02C; /* fn_1_4FEC countdown, 360 frames (lha) */
    s16 unk02E[3]; /* models 0x3E0017 x3 (fn_1_51B4) */
    s16 unk034[7]; /* motions 0x3E0029..2F: [0] idle, [1+2i]/[2+2i] for unk02E[i] */
    u16 unk042[3]; /* fn_1_51B4 state per unk02E[i] (lhzx; fn_1_5870 kind 3 sets 1) */
    u8 pad048[0x2];
    s16 unk04A; /* model 0x3E0018, layer 4 */
    s16 unk04C; /* model 0x3E001A, layer 5 */
    s16 unk04E; /* model 0x3E0019, layer 4 */
    s16 unk050; /* model 0x3E001B, layer 5 */
    s16 unk052; /* shape motion 0x3E0030 of unk04A */
    s16 unk054; /* shape motion 0x3E0032 of unk04C */
    s16 unk056; /* shape motion 0x3E0031 of unk04E */
    s16 unk058; /* shape motion 0x3E0033 of unk050 */
    u8 pad05A[0x2];
    s32 unk05C; /* = -1 (fn_1_255C 0x38C4); m504 fn_1_10C4: SE handle, -1 = none */
    s16 unk060; /* model 0x3E0013, looping motion unk066 */
    s16 unk062; /* model 0x3E0014 */
    s16 unk064; /* model 0x3E0015 */
    s16 unk066; /* motion 0x3E0034 of unk060 */
    s16 unk068; /* shape motion 0x3E0035 of unk062 */
    s16 unk06A; /* shape motion 0x3E0036 of unk064 */
    u16 unk06C; /* fn_1_53AC state A (unk060/062/064; fn_1_5870 kind 5) */
    u16 unk06E; /* fn_1_53AC state B (unk04A..050; fn_1_5870 kind 5) */
    u8 pad070[0x2];
    s16 unk072; /* model 0x3E001C */
    s16 unk074[2]; /* motions 0x3E0037/38 of unk072: [0] loop, [1] shape */
    u16 unk078; /* fn_1_572C state (fn_1_5870 kind 1) */
    u8 pad07A[0x2];
    M504_STAGEOBJ unk07C[10]; /* collision objects from lbl_1_data_A8 */
    u8 pad25C[0x4];
}; /* size 0x260 (GC; fn_1_255C/fn_1_3B9C memset) */

struct M504_LANE_s {
    M504_WORK *unk000; /* stage fn_1_23DC arg 3 */
    s32 unk004; /* player index (stage fn_1_23DC arg 2) */
    M504_PLAYER unk008; /* player fn_1_5934 */
    M504_WANWAN unk0DC; /* wanwan fn_1_9680 */
    M504_STAGE unk15C; /* stage fn_1_255C */
    M504_CAMERA unk3BC; /* camera fn_1_C4F4 */
    s32 unk46C; /* stage fn_1_23DC: (idx & 1) ? 0 : 1; picks the left/right SE of each pair */
    MGTIMER *unk470; /* fn_1_F34 MgTimerCreate (decathlon mode only) -- fork A */
}; /* size 0x474 (GC; stage fn_1_23DC/fn_1_24A0 memset) */

struct M504_WORK_s {
    OMOBJMAN *unk000; /* fn_1_7EC arg 2 (lbl_1_bss_4) */
    u8 pad004[0x6];
    u16 unk00A; /* ending fn_1_118E8 state (lhz/cmpwi switch 0..4, sth ++) */
    s32 unk00C; /* fn_1_7EC = 0x2A30 (10800), fn_1_C64 counts down to 0 */
    u16 unk010; /* fn_1_10C4: lose-voice / finish frame counter, 210 -> FADEOUT */
    s16 unk012[19]; /* fn_1_B38 model ids from lbl_1_data_2C (sthx/lhax); stage fn_1_255C reads +0x2 */
    M504_LIGHT unk038; /* light fn_1_D03C */
    M504_LANE unk040[4]; /* stage fn_1_23DC */
    s32 unk1210; /* fn_1_298/2F0/10C4: main-play flag, drives lane active flags */
    s32 unk1214; /* winner lane index, -1 = none (fn_1_C64 0xD68; coin payout fn_1_460) */
    s32 unk1218; /* set by opening (0xE23C, 0x102B4) and ending (0x11ED8); read by player 0x5F20/0x5FE4, stage 0x3EF0 */
    s16 unk121C; /* espEntry 0x3E004A */
    s16 unk121E; /* espEntry 0x3E004B */
    s32 unk1220; /* GAMEMESID: fn_1_10C4 draw message (extsh), ending 0x12404 also sets it; -1 = none */
    u8 pad1224[0x8];
    s32 unk122C; /* _CheckFlag(FLAG_INST_DECA): decathlon mode (player.c reads it) */
    s32 unk1230; /* stream: opening 0xE224 sets it, fn_1_10C4 jingle fn_1_794(123), ending 0x12484; fn_1_2F0 fades it; -1 = none */
    s32 unk1234; /* stream, -1 = none (fn_1_1EC stops it; never set in m504.c) */
}; /* size 0x1238 (GC; fn_1_114 HuMemDirectMallocNum/memset) */

/* input.c COM route graph (typed at measured widths: com fn_1_BC84 lha +0 of a path,
 * fn_1_C2CC lhz +8/+0xA of a node). The generic views index past [1]; each object
 * is defined with the sized type that matches its bytes. */
typedef struct { s16 num; s16 unk02; HuVecF pos[1]; } M504_PATH;
#define M504_PATH_T(n) struct { s16 num; s16 unk02; HuVecF pos[n]; }
typedef M504_PATH_T(1) M504_PATH1;
typedef M504_PATH_T(2) M504_PATH2;
typedef M504_PATH_T(3) M504_PATH3;
typedef M504_PATH_T(4) M504_PATH4;
typedef M504_PATH_T(5) M504_PATH5;
typedef M504_PATH_T(6) M504_PATH6;
typedef struct M504_NODE_s {
    M504_PATH *unk00;
    M504_PATH *unk04;
    u16 num;
    u16 unk0A; /* visit count (fn_1_BAC4 clears, fn_1_C2CC bumps) */
    struct M504_NODE_s *child[1];
} M504_NODE;
#define M504_NODE_T(n) struct { M504_PATH *unk00; M504_PATH *unk04; u16 num; u16 unk0A; M504_NODE *child[n]; }
typedef M504_NODE_T(1) M504_NODE1;
typedef M504_NODE_T(2) M504_NODE2;
typedef M504_NODE_T(3) M504_NODE3;
typedef M504_NODE_T(6) M504_NODE6;
typedef M504_NODE_T(12) M504_NODE12;
extern M504_NODE1 lbl_1_bss_7810; /* player.c: the dynamic node; lbl_1_data_4134[0] */

typedef struct {
    s16 unk00; /* lha: model index into work+0x12, or -1 */
    u16 unk02; /* lhz */
    HuVecF unk04;
    HuVecF unk10;
    s32 unk1C; /* lwz */
} M504_STAGEOBJDATA; /* player lbl_1_data_A8[10], used by stage fn_1_255C */
extern M504_STAGEOBJDATA lbl_1_data_A8[10]; /* player.c */
extern s32 lbl_1_data_45E0[4]; /* camera.c: camera bits {1,2,4,8} */
extern M504_WORK *lbl_1_bss_0; /* m504.c: the work block (player fn_1_613C reads unk122C) */

/* no SDK header declares rand8 (m502dll.h does the same) */
int rand8(void);

typedef struct {
    u32 flags;
    GXColor colorStart;
    GXColor colorEnd;
    HuVecF vel;
    HuVecF speedDecay;
    float accelY;
    float unk28;
    float scaleDecay;
    float alphaStep;
    float colorStep;
} M504_EFFECTPARAM; /* particle lbl_1_data_4610 = m507 effect.c M507EffectParam */

/* --- m504.c --- */
void ObjectSetup(void);
void fn_1_114(s16 mode, s16 frameNo);
void fn_1_190(s16 mode, s16 frameNo);
void fn_1_1EC(s16 mode, s16 frameNo);
void fn_1_25C(s16 mode, s16 frameNo);
void fn_1_298(s16 mode, s16 frameNo);
void fn_1_2F0(s16 mode, s16 frameNo);
void fn_1_37C(s16 mode, s16 frameNo);
void fn_1_460(s16 mode, s16 frameNo);
void fn_1_59C(s16 mode, s16 frameNo);
int fn_1_5EC(int seId);
void fn_1_614(int seNo);
void fn_1_63C(int seNo, s32 speed);
void fn_1_66C(int seNo, s16 pan);
void fn_1_69C(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis);
int fn_1_6F4(s16 streamId);
void fn_1_71C(int streamNo, s32 speed);
void fn_1_74C(void);
int fn_1_76C(s16 streamId);
int fn_1_794(s16 streamId);
int fn_1_7BC(s16 streamId, s16 chanNo);
void fn_1_7EC(M504_WORK *work, OMOBJMAN *objman);
void fn_1_9F0(M504_WORK *work);
void fn_1_AA8(M504_WORK *work);
void fn_1_AF0(M504_WORK *work);
void fn_1_B38(s16 *modelId);
void fn_1_C08(s16 *modelId);
s32 fn_1_C64(M504_WORK *work, s32 arg1);
s32 fn_1_F34(M504_WORK *work);
s32 fn_1_1080(M504_WORK *work);
s32 fn_1_10C4(M504_WORK *work);
void fn_1_12A8(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_20B8(HuVecF *start, HuVecF *end, GXColor *color);
void fn_1_2190(HuVecF *p0, HuVecF *p1, HuVecF *p2, GXColor *color);
void fn_1_229C(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color);

/* --- player.c --- */
void fn_1_5934(M504_PLAYER *player, s32 playerNo, M504_LANE *lane);
void fn_1_5E1C(M504_PLAYER *player);
s32 fn_1_5EC8(M504_PLAYER *player); /* returns 0 (li r3,0 at 0x5F3C); stage fn_1_24F8 ignores it */
s32 fn_1_5F58(M504_PLAYER *player);
void fn_1_613C(M504_PLAYER *player);
float fn_1_68E8(float cur, float target, float rate);
void fn_1_6A04(M504_PLAYER *player, HuVecF *push);
void fn_1_6AA0(M504_PLAYER *player);
void fn_1_7710(M504_PLAYER *player);
void fn_1_85AC(M504_PLAYER *player);
void fn_1_8A40(M504_PLAYER *player);
void fn_1_91B0(M504_PLAYER *player);
void fn_1_9334(M504_PLAYER *player);

/* --- stage.c --- */
void fn_1_23DC(M504_LANE *lane, s32 idx, M504_WORK *work);
void fn_1_24A0(M504_LANE *lane);
s32 fn_1_24F8(M504_LANE *lane);
void fn_1_255C(M504_STAGE *stage, s32 idx, M504_LANE *lane);
void fn_1_3B9C(M504_STAGE *stage);
void fn_1_3D9C(M504_STAGE *stage);
s32 fn_1_3FCC(HuVecF *pos2d);
s32 fn_1_4030(M504_STAGE *stage, HuVecF *pos, float radius, HuVecF *out, s32 flag, s16 *hitIdx, s16 *corner);
void fn_1_4FA4(M504_STAGE *stage);
void fn_1_4FEC(M504_STAGE *stage);
void fn_1_5168(M504_STAGE *stage);
void fn_1_51B4(M504_STAGE *stage, u16 idx);
void fn_1_53AC(M504_STAGE *stage);
void fn_1_572C(M504_STAGE *stage);
void fn_1_5870(M504_STAGE *stage, s16 kind);

/* --- wanwan.c --- */
void fn_1_9680(M504_WANWAN *wanwan, M504_LANE *lane);
void fn_1_9C10(M504_WANWAN *wanwan);
s32 fn_1_9CAC(M504_WANWAN *wanwan);
void fn_1_AB40(Mtx mtx, HuVecF *rot);
s32 fn_1_AEE0(M504_WANWAN *wanwan, float *angle);
void fn_1_B1AC(M504_WANWAN *wanwan);
s32 fn_1_B43C(M504_WANWAN *wanwan, HuVecF *pos, float radius, HuVecF *push, s32 useY);
s32 fn_1_B52C(M504_WANWAN *wanwan, HuVecF *out);

/* --- input.c --- */
void fn_1_B828(M504_INPUT *input, s32 playerNo, M504_PLAYER *player);
void fn_1_B898(M504_INPUT *input);
void fn_1_B8D8(M504_INPUT *input);
void fn_1_BAC4(M504_COM *com, M504_INPUT *input);

/* --- com.c --- */
void fn_1_BC54(M504_COM *com);
void fn_1_BC84(M504_COM *com);
s32 fn_1_BEF0(M504_COM *com, M504_PATH *path); /* 1 when the last point of path is reached */
s32 fn_1_C178(M504_COM *com);
s32 fn_1_C1E8(M504_COM *com);
M504_NODE *fn_1_C2CC(M504_COM *com, M504_NODE *node); /* least-visited child, ties by rand8() */

/* --- camera.c --- */
u16 fn_1_C3E0(M504_COM *com); /* COM wait frames; com fn_1_BC84 clrlwi the result */
void fn_1_C4F4(M504_CAMERA *camera, s32 idx, M504_LANE *lane);
void fn_1_C64C(M504_CAMERA *camera, s32 camBit);
void fn_1_C71C(M504_CAMERA *camera);
void fn_1_C74C(M504_CAMERA *camera);
void fn_1_C810(M504_CAMERA *camera);
void fn_1_C99C(M504_CAMERA *camera, u16 axis, s32 frames, float amp, float decay, float speed);
void fn_1_C9C4(void);
HuVecF fn_1_C9C8(float t, HuVecF *from, HuVecF *to);
void fn_1_CB3C(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_CBE8(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target, float *rate);
void fn_1_CC3C(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_CC88(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target);
void fn_1_CCE4(M504_CAMERA *camera, float t);
s32 fn_1_CCEC(M504_CAMERA *camera, float frames, HuVecF *up);

/* --- light.c --- */
void fn_1_D03C(); /* unprototyped on GC: m504 fn_1_7EC (0x90C) calls it with one argument */
void fn_1_D0B4(M504_LIGHT *light);
void fn_1_D108(M504_LIGHT *light);

/* --- particle.c --- */
void fn_1_D10C(void);
void fn_1_D15C(void);
void fn_1_D1F0(s16 cameraBit, HuVecF *pos);
s16 fn_1_D560(s16 cameraBit, float posX, float posY, float posZ, float scale, M504_EFFECTPARAM *param);
void fn_1_D804(void);
void fn_1_DA68(void);
void fn_1_DC8C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

/* --- opening.c --- */
/* opening state lbl_1_bss_7870 (fork O) */
typedef struct M504_OPENING_s {
    s32 unk000; /* frame counter of the current step (lwz/stw; cmpwi) */
    s32 unk004; /* step-2 counter (cmpwi 10, == 4 rumble) */
    s32 unk008; /* step-7 player walk done (lwz/stw 1) */
    s32 unk00C; /* step-7 chomp phase 0/1/2 */
    s16 unk010[10]; /* flying models 0x3E001F..21 (lha/sth) */
    s16 unk024[20]; /* dust puffs 0x3E0022 [0..9] / 0x3E0023 [10..19] (lha/sth) */
    s32 unk04C[20]; /* puff active (lwz/stw) */
    HuVecF unk09C[20]; /* puff velocity (word copy in fn_1_11198/11360; PSVECAdd in fn_1_11088) */
} M504_OPENING; /* size 0x18C (GC) */
extern M504_OPENING lbl_1_bss_7870;

s32 fn_1_E14C(M504_WORK *work);
void fn_1_10CEC(M504_WORK *work, float x, float y); /* r3 unused by the body; ending 0x119D0/0x11DC4, opening 0xEAE0/0x102A0 pass it */
void fn_1_11088(void);
void fn_1_11198(HuVecF pos, HuVecF vel); /* by value: caller copies each to a temp */
void fn_1_11360(HuVecF pos, HuVecF vel);
void fn_1_11548(Mtx mtx, HuVecF *rot);

/* --- ending.c --- */
s32 fn_1_118E8(M504_WORK *work);
void fn_1_128E0(M504_WORK *work); /* body ignores it; m504 fn_1_9F0 passes work in r3 */

#endif
