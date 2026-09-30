#ifndef M528DLL_H
#define M528DLL_H

/*
 * m528Dll (overlay #42): types and prototypes shared by its one translation
 * unit (m528).
 *
 * Offsets are GameCube ones from build/mp5-asm/m528Dll. No upstream names exist,
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

/* shared structs: fork A owns the work/.bss types (see BRIEF.md ownership table) */

typedef struct M528_WORK_s M528_WORK;
typedef struct M528_PLAYER_s M528_PLAYER;
typedef struct M528_NODE_s M528_NODE;
typedef s32 (*M528_PLAYERFUNC)(M528_PLAYER *player);
typedef s32 (*M528_NODEFUNC)(M528_NODE *node);

/* camera orbit, work+0x20 (fn_1_1918 init, fn_1_198C preset, fn_1_1A20 apply) */
typedef struct {
    HuVecF unk000; /* look-at target */
    float unk00C; /* yaw, degrees (wrapped to [0,360] in fn_1_1A20) */
    float unk010; /* pitch, degrees */
    float unk014; /* distance */
    s16 unk018; /* cleared by fn_1_238 when team 0 finishes (0x88C) */
    s16 unk01A;
} M528_CAMERA; /* size 0x1C (GC) */

/* lbl_1_data_2BC[4]: camera presets copied by fn_1_198C (mulli 0x18) */
typedef struct {
    HuVecF unk000; /* -> M528_CAMERA.unk000 */
    float unk00C; /* -> M528_CAMERA.unk00C */
    float unk010; /* -> M528_CAMERA.unk010 */
    float unk014; /* -> M528_CAMERA.unk014 */
} M528_CAMPARAM; /* size 0x18 (GC) */

/* one member slot of a team; M528_PLAYER.unk058 points here (fn_1_113C 0x1254) */
typedef struct M528_TEAM_s M528_TEAM;

typedef struct {
    M528_TEAM *unk000; /* parent team (fork C: stw of &work->unk03C[i], 0x5974) */
    HuVecF unk004; /* pos; player X = .x, player Z = 75 + .z (fn_1_1CAC) */
    float unk010; /* push strength, decays *0.95f (fork B fn_1_32D0); 0.0f (fork C 0x5954) */
    float unk014; /* 1.0 while the player is ready (fn_1_1F8C) / on landing (fn_1_3330), 0.0 on jump (fn_1_2080) */
    s16 unk018; /* landing cooldown, counts down (fork B fn_1_32D0) */
    s16 unk01A; /* model (fork C 0x586C, B 0x3218) */
    s16 unk01C; /* landed flag -> HuAudFXPlay(team->unk066) (fork B 0x3064); 0 (fork C 0x598C) */
    u8 pad01E[2];
} M528_SLOT; /* size 0x20 (GC) */

/* the 0x2C objects at work+0x10C[16]; a team's unk054 points at one (fn_1_36DC init) */
typedef struct {
    HuVecF unk000;
    HuVecF unk00C; /* fn_1_4B04 copies unk000 here */
    float unk018; /* progress 0..1 (fork B fn_1_3750) */
    float unk01C; /* yaw offset, added to work->unk4C98 (fork B fn_1_3A00); rot y (fork C) */
    s16 unk020; /* model (fork C 0x5D2C) */
    s16 unk022; /* model (fork C 0x6028) */
    s16 unk024; /* model (fork C 0x623C) */
    s16 unk026; /* state (switch in fn_1_4B04); cleared by fn_1_954/fn_1_B10 */
    s16 unk028; /* timer (fork B) */
    s16 unk02A; /* kind 0..7 (weighted pick, fork C 0x5E3C): indexes the fn_1_C314.. table and flag table in fn_1_B10; 7 plays SE 0x78D */
} M528_ITEM; /* size 0x2C (GC) */

/* team block, work+0x3C[2] (mulli 0x68); team[1] = work+0xA4 */
struct M528_TEAM_s {
    M528_SLOT unk000[2]; /* member slots (fn_1_113C) */
    float unk040; /* wheel rotation, wraps at 360 (fork B); 0.0f (fork C 0x5ACC) */
    s16 unk044; /* model (fork C 0x5AB4) */
    u8 pad046[2];
    HuVecF unk048; /* pos: 600*i-300, 2500, 0 (fork C) */
    M528_ITEM *unk054; /* = &work->unk10C[work->unk4CA8[i]] (fork B fn_1_46CC 0x4710) */
    float unk058; /* tilt, clamped +-25 (fork B fn_1_2EC0) */
    float unk05C; /* 0.0f (fork C 0x5684) */
    s16 unk060; /* model (fork C 0x5654) */
    s16 unk062; /* state (fork B fn_1_47F0/fn_1_495C); cleared for the loser in fn_1_9CC */
    s16 unk064; /* timer (fork B) */
    s16 unk066; /* SE 0x789 / 0x78A (fork C 0x572C) */
}; /* size 0x68 (GC) */

/* list node, work+0x3E4[256]; unk3DC = active head, unk3E0 = free head (fn_1_4F30) */
struct M528_NODE_s {
    M528_NODE *unk000; /* prev */
    M528_NODE *unk004; /* next */
    M528_NODEFUNC unk008; /* run each frame by fn_1_50B0; nonzero = free */
    struct M528_EFFECT_s *unk00C; /* data: &work->unk13E4[n] (fn_1_C314..fn_1_CC40) */
}; /* size 0x10 (GC) */

/* work+0x13E4[256] (mulli 0x38, fn_1_C314..) */
typedef struct M528_EFFECT_s {
    HuVecF unk000; /* position (Hu3DModelPosSetV) */
    HuVecF unk00C; /* rotation (Hu3DModelRotSetV) */
    HuVecF unk018; /* velocity, added to unk000 each frame */
    HuVecF unk024; /* rotation velocity (fork D: fn_1_8FFC adds all three; fn_1_83E4/87F4 use .z) */
    s16 unk030; /* state */
    s16 unk032; /* timer */
    s16 unk034; /* timer limit / delay; second model id in fn_1_8CD0 */
    s16 unk036; /* model id, -1/<0 = none (fn_1_5194) */
} M528_EFFECT; /* size 0x38 (GC) */

/* work+0x4BE4[4]: carts driven along the track in lbl_1_bss_4 (fork E); fn_1_B528 init
 * (delays 0/150/330/900 from fn_1_51A8), fn_1_B6D4 update */
typedef struct {
    HuVecF unk000; /* pos */
    HuVecF unk00C; /* rot */
    float unk018; /* rot.y lerp start */
    float unk01C; /* rot.y lerp end */
    s16 unk020; /* model id */
    s16 unk022; /* state (switch jumptable_1_data_5D4 in fn_1_B6D4); fn_1_238 case 6 bumps it */
    s16 unk024; /* timer */
    s16 unk026; /* track point index */
    s16 unk028; /* start delay */
    s16 unk02A; /* track point count (55) */
} M528_CART; /* size 0x2C (GC) */

/* obj->data of each player object (HuMemDirectMallocNum 0x5C, ObjectSetup) */
struct M528_PLAYER_s {
    HuVecF unk000; /* position */
    HuVecF unk00C; /* rotation */
    OMOBJ *unk018; /* own object */
    M528_PLAYERFUNC unk01C; /* state function (fn_1_1368) */
    s32 unk020; /* state step */
    s32 unk024; /* step timer */
    s16 unk028; /* player number (obj->work[0]) */
    s16 unk02A; /* GwPlayerConf.charNo */
    s16 unk02C; /* GwPlayerConf.grp: team 0/1 */
    s16 unk02E; /* GwPlayerConf.padNo */
    u8 pad030[4];
    s16 unk034; /* GwPlayerConf.type: nonzero = COM */
    s16 unk036; /* GwPlayerConf.dif */
    u8 pad038[2];
    s16 unk03A;
    s16 unk03C; /* jump strength index 0/1 (fn_1_2080) */
    s16 unk03E; /* 1 while ready */
    float unk040; /* jump peak Y */
    float unk044;
    float unk048; /* push strength (fork B) */
    M528_PLAYER *unk04C; /* partner (fork B fn_1_38F8) */
    s16 unk050[3]; /* COM state / counter / limit (fork B) */
    u8 pad056[2];
    M528_SLOT *unk058; /* &work->unk03C[grp].unk000[slot] */
}; /* size 0x5C (GC) */

/* lbl_1_bss_298->data (HuMemDirectMallocNum 0x4D70, ObjectSetup) */
struct M528_WORK_s {
    M528_PLAYER *unk000[4]; /* by player number */
    M528_PLAYER *unk010[2][2]; /* by [team][slot] */
    M528_CAMERA unk020;
    M528_TEAM unk03C[2];
    M528_ITEM unk10C[16];
    s32 (*unk3CC)(M528_CAMERA *camera); /* camera script, called with &unk020 */
    s32 (*unk3D0[2])(M528_TEAM *team); /* per-team script, called with &unk03C[n] */
    s32 (*unk3D8)(M528_ITEM *item); /* winner script, called with unk03C[unk4CB0].unk054 */
    M528_NODE *unk3DC; /* active list head */
    M528_NODE *unk3E0; /* free list head */
    M528_NODE unk3E4[256];
    M528_EFFECT unk13E4[256];
    M528_CART unk4BE4[4];
    float unk4C94; /* roulette spin strength, 3 + rand(100)/100 */
    float unk4C98; /* track yaw / roulette angle, degrees (lbl_1_bss_4 = lbl_1_data_31C rotated by it, fn_1_B384) */
    float unk4C9C; /* roulette angular speed */
    float unk4CA0; /* roulette stop angle (multiple of 22.5) */
    u8 pad4CA4[4];
    s16 unk4CA8[2]; /* item index per team: [0] = (16 - angle/22.5) % 16, [1] = ([0] + 1) % 16 */
    s16 unk4CAC; /* seq step inside a MgSeq mode */
    s16 unk4CAE; /* seq timer */
    s16 unk4CB0; /* winning team, -1 = none/draw */
    s16 unk4CB2; /* input enabled */
    s16 unk4CB4[54]; /* model ids from lbl_1_data_1C8[i] (forks C/D) */
    s16 unk4D20[7]; /* motion ids from lbl_1_data_2A0[i] (forks C/D) */
    s16 unk4D2E[16]; /* per unk10C[i] (fork C) */
    s16 unk4D4E[16]; /* per unk10C[i] (fork C) */
    s16 unk4D6E; /* fade-out done flag (fn_1_9CC) */
}; /* size 0x4D70 (GC) */


/* --- m528.c --- */
void ObjectSetup(void);
void fn_1_1E8(s16 mode, s16 frameNo);
void fn_1_238(s16 mode, s16 frameNo);
void fn_1_8E4(s16 mode, s16 frameNo);
void fn_1_954(s16 mode, s16 frameNo);
void fn_1_9CC(s16 mode, s16 frameNo);
void fn_1_B10(s16 mode, s16 frameNo);
void fn_1_ED0(s16 mode, s16 frameNo);
void fn_1_1118(s16 mode, s16 frameNo);
void fn_1_111C(s16 mode, s16 frameNo);
void fn_1_113C(OMOBJ *obj);
void fn_1_1368(OMOBJ *obj);
void fn_1_13CC(void);
void fn_1_13D0(OMOBJ *obj);
void fn_1_1458(OMOBJ *obj);
void fn_1_1534(void);
void fn_1_1538(M528_WORK *work);
void fn_1_15EC(M528_WORK *work);
void fn_1_16C4(M528_WORK *work);
void fn_1_17B0(M528_WORK *work);
void fn_1_1874(M528_WORK *work);
void fn_1_18E0(M528_WORK *work);
void fn_1_1918(M528_CAMERA *camera);
void fn_1_198C(M528_CAMERA *camera, s32 preset);
void fn_1_1A20(M528_CAMERA *camera);
void fn_1_1CAC(M528_WORK *work);
s32 fn_1_1DFC(M528_PLAYER *player);
s32 fn_1_1ECC(M528_PLAYER *player);
s32 fn_1_1F8C(M528_PLAYER *player);
s32 fn_1_2080(M528_PLAYER *player);
s32 fn_1_22B4(M528_PLAYER *player);
s32 fn_1_237C(M528_PLAYER *player);
s32 fn_1_2488(M528_PLAYER *player);
s32 fn_1_2564(M528_PLAYER *player);
s32 fn_1_25FC(M528_PLAYER *player);
s32 fn_1_2680(M528_PLAYER *player);
s32 fn_1_2704(M528_PLAYER *player);
s32 fn_1_2758(M528_PLAYER *player);
s32 fn_1_27AC(M528_PLAYER *player);
s32 fn_1_2A00(M528_PLAYER *player);
s16 fn_1_2C40(s16 a0, s32 a1);
s16 fn_1_2D7C(M528_PLAYER *player);
s16 fn_1_2E3C(M528_PLAYER *player);
s32 fn_1_2EC0(M528_TEAM *team);
void fn_1_32D0(M528_SLOT *slot);
void fn_1_3330(M528_WORK *work);
void fn_1_36DC(M528_ITEM *item);
s32 fn_1_3750(M528_ITEM *item, float speed);
void fn_1_38F8(M528_WORK *work);
void fn_1_3A00(M528_WORK *work);
s32 fn_1_3CA0(M528_CAMERA *camera);
s32 fn_1_3EFC(M528_CAMERA *camera);
s32 fn_1_4158(M528_CAMERA *camera);
s32 fn_1_43B4(M528_CAMERA *camera);
s32 fn_1_4540(M528_CAMERA *camera);
void fn_1_46CC(M528_WORK *work);
s32 fn_1_47F0(M528_TEAM *team);
s32 fn_1_495C(M528_TEAM *team);
s32 fn_1_4B04(M528_ITEM *item);
s32 fn_1_4C84(M528_ITEM *item);
void fn_1_4E80(M528_WORK *work);
void fn_1_4F30(M528_WORK *work);
M528_NODE *fn_1_4FF4(M528_WORK *work, M528_NODEFUNC func, void *arg);
void fn_1_5048(M528_WORK *work, M528_NODE *node);
void fn_1_50B0(M528_WORK *work);
void fn_1_5194(M528_EFFECT *a0);
void fn_1_51A8(M528_WORK *a0);
void fn_1_5BF8(M528_WORK *a0);
void fn_1_6320(M528_WORK *a0);
void fn_1_6410(M528_WORK *a0);
void fn_1_654C(M528_WORK *a0);
void fn_1_6688(M528_WORK *a0);
void fn_1_67C4(M528_WORK *a0);
void fn_1_6900(M528_WORK *a0);
void fn_1_6A3C(M528_WORK *a0);
void fn_1_6B78(M528_WORK *a0);
void fn_1_6CB4(M528_WORK *a0);
s32 fn_1_6DF0(M528_NODE *a0);
s32 fn_1_72E4(M528_NODE *a0);
s32 fn_1_7794(M528_NODE *task);
s32 fn_1_7B44(M528_NODE *task);
s32 fn_1_800C(M528_NODE *task);
s32 fn_1_83E4(M528_NODE *task);
s32 fn_1_87F4(M528_NODE *task);
s32 fn_1_8CD0(M528_NODE *task);
s32 fn_1_8FFC(M528_NODE *task);
s32 fn_1_97C8(M528_NODE *task);
s32 fn_1_9D5C(M528_NODE *node);
s32 fn_1_A3A0(M528_NODE *node);
s32 fn_1_ABAC(M528_NODE *node);
void fn_1_B384(M528_WORK *work);
void fn_1_B528(M528_CART *cart, s16 delay);
void fn_1_B6D4(M528_CART *cart);
void fn_1_C314(M528_WORK *work);
void fn_1_C3DC(M528_WORK *work);
void fn_1_C530(M528_WORK *work);
void fn_1_C728(M528_WORK *work);
void fn_1_C8B4(M528_WORK *work);
void fn_1_CA34(M528_WORK *work);
void fn_1_CAEC(M528_WORK *work);
void fn_1_CC40(M528_WORK *work);

#endif
