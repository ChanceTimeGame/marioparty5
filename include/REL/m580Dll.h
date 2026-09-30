#ifndef M580DLL_H
#define M580DLL_H

/*
 * m580Dll (overlay #90): types and prototypes shared by its eight translation
 * units.
 *
 * Offsets are GameCube ones from build/mp5-asm/m580Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/mg/score.h"
#include "game/hu3d.h"

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

/* shared structs are defined by the forks (see BRIEF.md ownership table) */

/* ------------------------------------------------------------ reflect.c (fork R)
 * Collision registry (m574 collide.c layout, reworked: X/Z plane, one 0x40
 * record shape for both actors and meshes, 20 + 20 slots).
 */
typedef struct M580_COLLACTOR_s M580_COLLACTOR;
typedef struct M580_COLLOBJ_s M580_COLLOBJ;

/* hit callback: (self, other). 11410 ignores the result; 11880 skips the bounce
 * when a mesh's callback returns nonzero. other is an actor or a mesh. */
typedef s32 (*M580_COLLHITFUNC)(void *self, void *other);

/* One transformed collision segment (X/Z line with outward normal). */
typedef struct M580_COLLSEG_s {
    /* 0x00 */ HuVecF unk000;       /* end point 0 (world; x,z used) */
    /* 0x0C */ HuVecF unk00C;       /* end point 1 */
    /* 0x18 */ HuVecF unk018;       /* unit normal (-dz, 0, dx) (122D0) */
    /* 0x24 */ float unk024;        /* plane distance: n . p + d = 0 */
} M580_COLLSEG; /* size 0x28 (GC) */

/* One source edge in model space, from an HSF quad (11F88). */
typedef struct M580_COLLEDGE_s {
    /* 0x00 */ HuVecF unk000;       /* end point 0 (x,z only; y left 0) */
    /* 0x0C */ HuVecF unk00C;       /* end point 1 */
    /* 0x18 */ Mtx *unk018;         /* owning object's matrix (unk038[] slot) */
} M580_COLLEDGE; /* size 0x1C (GC) */

/*
 * Collision actor: a circle in the X/Z plane (Y ignored). Registered in the
 * 20 actor slots by fn_1_11DC4 (player 0xE8.. / stick / puck own the storage).
 */
struct M580_COLLACTOR_s {
    /* 0x00 */ u32 unk000;          /* bit0 live; bit1 skip meshes (1113C rlwinm 30,30);
                                       bit2 push harder (0.5 not 0.1) unless other has bit3;
                                       bit4 no push against a type-1 partner (11410) */
    /* 0x04 */ u32 unk004;          /* collision mask, (a->unk004 & b->unk004) != 0 */
    /* 0x08 */ u32 unk008;          /* type 0/1 (cmplwi, 11410) */
    /* 0x0C */ s32 unk00C;          /* not read by reflect.c */
    /* 0x10 */ s32 unk010;          /* shape: 0 actor (cmpwi 0) */
    /* 0x14 */ void *unk014;        /* argument handed to unk018 */
    /* 0x18 */ void (*unk018)(void *arg); /* post-pass callback (1113C bctrl) */
    /* 0x1C */ M580_COLLHITFUNC unk01C; /* hit callback (11410/11880 bctrl) */
    /* 0x20 */ HuVecF *unk020;      /* position (owner's storage) */
    /* 0x24 */ HuVecF *unk024;      /* velocity (owner's storage) */
    /* 0x28 */ HuVecF unk028;       /* previous position; restored when unk020 is NaN (1113C) */
    /* 0x34 */ float unk034;        /* radius */
    /* 0x38 */ float unk038;        /* push-velocity scale (11410) */
    /* 0x3C */ u8 pad03C[4];        /* not read on actors; guessed from the mesh stride */
}; /* size 0x40 (GC) -- guessed from the mesh record */

/*
 * Collision mesh: registered in the 20 obstacle slots by fn_1_11E3C (stage),
 * or used directly (puck: 0x40 stride at +0x9C, fn_1_126C8 inside test).
 */
struct M580_COLLOBJ_s {
    /* 0x00 */ u32 unk000;          /* bit0 live */
    /* 0x04 */ u32 unk004;          /* collision mask */
    /* 0x08 */ u32 unk008;          /* stage writes 3 */
    /* 0x0C */ s32 unk00C;          /* stage writes; not read by reflect.c */
    /* 0x10 */ s32 unk010;          /* shape: 10 mesh (1113C cmpwi 0xa) */
    /* 0x14 */ void *unk014;        /* argument handed to unk018 (stage writes) */
    /* 0x18 */ void (*unk018)(void *arg); /* unused for meshes; stage writes NULL */
    /* 0x1C */ M580_COLLHITFUNC unk01C; /* hit callback; nonzero result skips the bounce */
    /* 0x20 */ s32 unk020;          /* segment count */
    /* 0x24 */ M580_COLLSEG *unk024; /* this frame's segments */
    /* 0x28 */ M580_COLLSEG *unk028; /* last frame's segments (swapped by 122D0) */
    /* 0x2C */ M580_COLLEDGE *unk02C; /* source edges */
    /* 0x30 */ s32 unk030;          /* HSF object count */
    /* 0x34 */ HSFTRANSFORM **unk034; /* &object->mesh.base per object */
    /* 0x38 */ Mtx *unk038;         /* per-object matrix */
    /* 0x3C */ M580_COLLSEG *unk03C; /* segment last hit (set before unk01C) */
}; /* size 0x40 (GC) -- puck array stride slwi 6 */

/* collide object work (lbl_1_bss_258->data), 0xA0 bytes (GC). */
typedef struct M580_COLLWORK_s {
    /* 0x000 */ M580_COLLACTOR *unk000[20];
    /* 0x050 */ M580_COLLOBJ *unk050[20];
} M580_COLLWORK; /* size 0xA0 (GC) */

/* ------------------------------------------------------------ effect.c (fork R) */

/*
 * Ground shadow/marker record drawn by the effect hook (fn_1_E36C). Registered
 * with fn_1_ED34; the owner keeps the storage (player +0xE8, stick +0x68).
 */
typedef struct M580_EFFECTSHADOW_s {
    /* 0x00 */ s32 unk000;          /* draw when nonzero (cmpwi) */
    /* 0x04 */ s32 unk004;          /* lbl_1_data_7A0 index (16 entries, unchecked) */
    /* 0x08 */ s32 unk008;          /* not read by effect.c */
    /* 0x0C */ HuVecF *unk00C;      /* position (owner's storage) */
    /* 0x10 */ HuVecF *unk010;      /* offset (.data vector); y is added, pos y negated */
    /* 0x14 */ float *unk014;       /* rotation (deg) -> unk01C frame */
    /* 0x18 */ ANIMDATA *unk018;    /* texture (ED34) */
    /* 0x1C */ s32 unk01C;          /* frame 0..15, -1 = not yet computed */
} M580_EFFECTSHADOW; /* size 0x20 (GC) */

/* mdlId[2] hook data (fn_1_DF28, 0x1C). */
typedef struct M580_EFFECTLIST_s {
    /* 0x00 */ M580_EFFECTSHADOW *unk000[7];
} M580_EFFECTLIST; /* size 0x1C (GC) */

/* banner sprite state (work +0x08) */
typedef struct M580_EFFECTBANNER_s {
    /* 0x00 */ s32 unk000;          /* requested on/off (fn_1_EDF8) */
    /* 0x04 */ s32 unk004;          /* pulse mode 0..3 */
    /* 0x08 */ float unk008;        /* transparency */
    /* 0x0C */ HUSPRGRPID unk00C;   /* sprite group (lha) */
    /* 0x0E */ u8 pad00E[2];
    /* 0x10 */ float unk010;        /* scale */
} M580_EFFECTBANNER; /* size 0x14 (GC) */

/* effect object work (lbl_1_bss_248->data), 0x1C (GC) */
typedef struct M580_EFFECT_s {
    /* 0x00 */ ANIMDATA *unk000;    /* shadow ring texture (DF28) */
    /* 0x04 */ float unk004;        /* fn_1_1970() each frame; shadow alpha scale */
    /* 0x08 */ M580_EFFECTBANNER unk008;
} M580_EFFECT; /* size 0x1C (GC) */

/* ------------------------------------------------------------ puck.c (fork C) */

/* puck.c: lbl_1_bss_240->data (HuMemDirectMallocNum 0x11C, fn_1_C8F8) */
typedef struct {
    s32 unk000; /* previous frame's unk004 */
    s32 unk004; /* set by fn_1_D018 when hit by an actor of kind 3; cleared every frame */
    s32 unk008; /* not in play (1 = dead ball): fn_1_D054/D30C/D390 refuse; fn_1_D544 returns it */
    s32 unk00C; /* held/placed: position is set externally (fn_1_D60C), physics off */
    s32 unk010; /* scoring team (goal index ^ 1), fn_1_D7B8 returns it */
    s32 unk014; /* state 0..4 (switch in fn_1_CBCC) */
    s32 unk018; /* frame counter */
    s32 unk01C; /* state timer */
    s16 unk020; /* puck model (lha) */
    s16 unk022; /* shadow model: Hu3DModelLink, scaled (1,-1,1) */
    HuVecF unk024; /* position */
    HuVecF unk030; /* velocity */
    OMOBJ *unk03C; /* last player object to touch the puck (cmplw 0; fn_1_D390 a2, fn_1_D714 a0) */
    s32 unk040; /* frames since unk03C was set */
    s32 unk044; /* "hot" flag handed to fn_1_EDF8; cleared after 180 frames */
    s32 unk048; /* frames since fn_1_D68C */
    s32 unk04C[4]; /* per-player touch count (index fn_1_7E2C(player)), fn_1_D714 */
    M580_COLLACTOR unk05C; /* collision actor (reflect.c type; pointer members) */
    M580_COLLOBJ unk09C[2]; /* goal_L / goal_R mesh obstacles (reflect.c type; pointer members) */
} M580_PUCK; /* size 0x11C (GC); holds pointers -- allocate with sizeof */

/* ------------------------------------------------------------ score.c (fork C) */

/* score.c: one team's score window (0xC each, mulli 0xC at work+0x24) */
typedef struct {
    s32 unk000; /* goals, clamped to 99 (fn_1_10F58, fn_1_F0B8) */
    s16 unk004; /* MgScoreWinCreate (lhax) */
    u8 pad006[2];
    MGSCORE *unk008; /* MgScoreCreate */
} M580_SCORETEAM; /* size 0xC (GC) */

/* score.c: m433's M433_SCOREOVL_SPR, byte-identical (fn_1_F4E8/F640 are exact copies) */
typedef struct {
    s16 unk000[2]; /* sprId */
    float unk004[2]; /* sprOfs */
    float unk00C; /* posX */
    float unk010; /* posY */
    float unk014; /* velX */
    float unk018; /* velY */
    float unk01C; /* scaleX */
    float unk020; /* scaleY */
    float unk024; /* tpLvl */
    float unk028; /* zRot */
} M580_SCOREOVLSPR; /* size 0x2C (GC) */

/* score.c: m433's M433_SCORESPRNUM */
typedef struct {
    s32 unk000[4]; /* sprId (espEntry, extsh at use) */
} M580_SCORESPRNUM; /* size 0x10 (GC) */

/* score.c: the goal overlay (m433 M433_SCOREOVL without titleTime/scoreValue*) */
typedef struct {
    s32 unk000; /* mode (switch in fn_1_F758) */
    u32 unk004; /* time (u32 -> float compares) */
    u32 unk008; /* moveTime */
    u32 unk00C[2]; /* previous score per team */
    u32 unk014[2]; /* score per team */
    u32 unk01C; /* scoring team (cmplwi 0) */
    M580_SCOREOVLSPR unk020[4];
    M580_SCORESPRNUM unk0D0[3][20];
    M580_SCORESPRNUM unk490; /* dash */
} M580_SCOREOVL; /* size 0x4A0 (GC) */

/* score.c: lbl_1_bss_250->data (HuMemDirectMallocNum 0x4DC, fn_1_EE34) */
typedef struct {
    s32 unk000; /* team window state (fn_1_F0B8) */
    float unk004; /* team window tpLvl */
    s32 unk008; /* timer window state (fn_1_10C44) */
    float unk00C; /* timer window tpLvl */
    s32 unk010; /* time left in frames (3600/10800/18000 by mgMatchMaxScore) */
    s16 unk014; /* timer MgScoreWinCreate */
    s16 unk016; /* timer ':' / '.' sprite group */
    MGSCORE *unk018; /* minutes */
    MGSCORE *unk01C; /* seconds */
    MGSCORE *unk020; /* hundredths */
    M580_SCORETEAM unk024[2];
    M580_SCOREOVL unk03C;
} M580_SCORE; /* size 0x4DC (GC) */

/* --- stick.c (fork S) --- */

/* one motion row of a stick table (lbl_1_data_310/358/3A0/3E8) */
typedef struct M580_StickMot_s {
    /* 0x000 */ s32 unk000; /* motion data number; -1 skip, -2 end */
    /* 0x004 */ float unk004; /* shift time in seconds (x60) */
    /* 0x008 */ s32 unk008; /* model attribute */
} M580_STICKMOT; /* size 0xC (GC) */

/* one row of lbl_1_data_46C: a group of stage objects */
typedef struct M580_StickData_s {
    /* 0x000 */ s32 unk000; /* object count; -1 terminates */
    /* 0x004 */ s32 unk004; /* nonzero: share the model through the cache */
    /* 0x008 */ s32 unk008; /* kind: 0 hook arm, 1 goalie stick, 2 kuri, 3 kame */
    /* 0x00C */ s32 unk00C; /* first index */
    /* 0x010 */ s32 unk010; /* model data number */
    /* 0x014 */ M580_STICKMOT *unk014;
    /* 0x018 */ HuVecF *unk018; /* position (kind 0: two points) */
    /* 0x01C */ float unk01C; /* rotation Y */
    /* 0x020 */ OMOBJFUNC unk020; /* object init */
} M580_STICKDATA; /* size 0x24 (GC) */

/* stick manager work (lbl_1_bss_238->data) */
typedef struct M580_StickMan_s {
    /* 0x000 */ s32 unk000; /* state */
    /* 0x004 */ s32 unk004; /* fn_1_D544() */
    /* 0x008 */ HU3DMODELID unk008; /* audience model 0x860007 */
    /* 0x00A */ u8 pad00A[2];
} M580_STICKMAN; /* size 0xC (GC) */

/* stick/stage-object work (obj->data), 0xC8 bytes for every row of lbl_1_data_46C */
typedef struct M580_Stick_s {
    /* 0x000 */ M580_STICKDATA *unk000;
    /* 0x004 */ s32 unk004; /* index */
    /* 0x008 */ s32 unk008; /* state */
    /* 0x00C */ u8 pad00C[4];
    /* 0x010 */ s32 unk010; /* timer */
    /* 0x014 */ s32 unk014; /* cooldown */
    /* 0x018 */ s32 unk018; /* current motion, -1 none */
    /* 0x01C */ s32 unk01C; /* frames in motion */
    /* 0x020 */ s32 unk020; /* wait for motion end */
    /* 0x024 */ s32 unk024;
    /* 0x028 */ HuVecF unk028; /* position */
    /* 0x034 */ HuVecF unk034; /* velocity */
    /* 0x040 */ HuVecF unk040; /* rotation */
    /* 0x04C */ float unk04C; /* target rotation Y */
    /* 0x050 */ float unk050;
    /* 0x054 */ s32 unk054;
    /* 0x058 */ u8 pad058[0x10];
    /* 0x068 */ M580_EFFECTSHADOW unk068; /* effect.c shadow record (fn_1_ED34) */
    /* 0x088 */ M580_COLLACTOR unk088; /* reflect.c actor (fn_1_11DC4); 0xC4 is its pad03C */
} M580_STICK; /* size 0xC8 (GC); holds pointers -- allocate with sizeof */

/* --- fork Q (player.c fn_1_55A0..end) --- */

/* player.c lbl_1_data_B0[9]: motion table, mulli 0xC (fn_1_7634) */
typedef struct {
    u16 unk00; /* lhz: index into obj->mtnId */
    u16 unk02;
    float unk04; /* lfs: shift time in seconds (x 60.0f) */
    u32 unk08; /* lwz: motion attr */
} M580_MOTPARAM; /* size 0xC (GC) */

/* player.c lbl_1_data_208[4]: COM tuning, indexed by M580_PLAYER.unk02C (mulli 0x18) */
typedef struct {
    float unk00; /* lfs: fn_1_6FC4 roll threshold; fn_1_6878 look-ahead scale */
    float unk04; /* lfs: fn_1_6FC4 roll threshold and unk05C decrement */
    float unk08; /* lfs: fn_1_6878 shoot roll threshold */
    float unk0C; /* lfs: fn_1_6FC4 B-press roll threshold */
    s32 unk10; /* lwz: fn_1_6548 base A-press delay */
    s32 unk14; /* lwz (int->double): fn_1_6548 random A-press delay range */
} M580_COMPARAM; /* size 0x18 (GC) */

typedef void (*M580_COMFUNC)(OMOBJ *obj);

/* player.c (fork P layout; COM fields 0x038..0x064 fork Q): obj->data of each player object (HuMemDirectMallocNum 0x148, fn_1_2A10) */
typedef struct M580_PLAYER_s {
    u32 unk000; /* player number (obj->work[0]); cmplwi 0 in fn_1_2EA0 case 6, xor/cmplwi in fn_1_3E94 */
    u32 unk004; /* team (obj->work[1]); cmplw vs fn_1_D7B8 (2EA0) and in fn_1_7818 */
    s32 unk008; /* slot 0..3 (obj->work[2]); indexes lbl_1_data_11C/14C, lbl_1_bss_64/54 */
    s32 unk00C; /* charNo (extsh at every use) */
    s32 unk010; /* current motion (fn_1_7634), -1 = none */
    s32 unk014; /* frames in current motion (++ in fn_1_3B30) */
    u32 unk018; /* HuPadBtnDown copy (0x200 = B) */
    u32 unk01C; /* HuPadBtn copy (0x100 = A, 0x400 = X) */
    float unk020; /* stick angle (deg) */
    float unk024; /* stick magnitude 0..1 */
    s32 unk028; /* GwPlayerConf.type: nonzero = COM (fn_1_8258: 0 = human) */
    s32 unk02C; /* GwPlayerConf.dif & 3; indexes lbl_1_data_208 (mulli 0x18) */
    s32 unk030; /* COM state (fn_1_5B94) */
    u8 pad034[4];
    s32 unk038; /* COM B-press cooldown (set 120, decremented in fn_1_5B94) */
    s32 unk03C; /* COM mode this frame: fn_1_78B4 result -1..3 */
    HuVecF unk040; /* COM target position */
    M580_COMFUNC unk04C; /* COM mode function (fn_1_5C64 sets; bctrl) */
    s32 unk050; /* COM mode last dispatched */
    s32 unk054; /* COM mode sub-state */
    s32 unk058; /* COM mode timer */
    float unk05C; /* COM mode 3: retarget countdown */
    s32 unk060; /* COM mode 3: always chase */
    s32 unk064; /* COM mode 3: angle bias */
    s32 unk068; /* mode (switch in fn_1_2EA0 / fn_1_37C0) */
    s32 unk06C; /* mode timer */
    s32 unk070; /* frame counter */
    HuVecF unk074; /* position */
    HuVecF unk080; /* velocity */
    float unk08C; /* rotY */
    s32 unk090;
    s32 unk094; /* motion lock (set with a one-shot motion) */
    s32 unk098;
    s32 unk09C; /* slot parity == lbl_1_bss_50 (serving side) */
    s32 unk0A0; /* last step foot (fn_1_3E94) */
    s32 unk0A4; /* hit cooldown */
    s32 unk0A8; /* charge counter */
    s32 unk0AC; /* stun timer */
    s32 unk0B0; /* hold frames */
    s32 unk0B4; /* dash timer */
    s32 unk0B8; /* post-shot lockout */
    s32 unk0BC; /* hit flag (previous frame) */
    s32 unk0C0; /* hit flag */
    s32 unk0C4; /* hit flag frames */
    s32 unk0C8; /* hit flag 2 (previous frame) */
    s32 unk0CC; /* hit flag 2 */
    s32 unk0D0; /* hit flag 2 frames */
    s32 unk0D4; /* voice volume follows distance */
    s32 unk0D8; /* sound handle, -1 = none */
    OMOBJ *unk0DC; /* partner object cache (fn_1_7818) */
    s32 unk0E0; /* effect fade direction */
    float unk0E4; /* effect fade 0..1 */
    M580_EFFECTSHADOW unk0E8; /* effect.c shadow record (fn_1_ED34) */
    M580_COLLACTOR unk108; /* reflect.c collision actor (fn_1_11DC4) */
} M580_PLAYER; /* size 0x148 (GC); holds pointers -- allocate with sizeof */

/* --- m580.c (fork A) --- */

/*
 * Camera object work (lbl_1_bss_44->data, fn_1_7C4 allocates 0x8C). No pointer
 * members: the host size only changes by alignment.
 */
typedef struct M580_CAMERA_s {
    /* 0x00 */ s32 unk000;         /* intro camera motion playing (fn_1_1838 sets, fn_1_898 clears) */
    /* 0x04 */ HU3DMOTID unk004;   /* Hu3DMotionCreate result (fn_1_1838 sth/lha) */
    /* 0x06 */ HU3DMODELID unk006; /* Hu3DModelCameraCreate result */
    /* 0x08 */ s32 unk008;         /* camera follow on (fn_1_18D8) */
    /* 0x0C */ s32 unk00C;         /* focus points this frame, < 8 (fn_1_1908); fn_1_834 clears */
    /* 0x10 */ HuVecF unk010[8];   /* focus points (fn_1_1908 mulli 0xC) */
    /* 0x70 */ HuVecF unk070;      /* base Center (fn_1_898) */
    /* 0x7C */ HuVecF unk07C;      /* base CRot */
    /* 0x88 */ float unk088;       /* base CZoom */
} M580_CAMERA; /* size 0x8C (GC) */

/* --- stage.c (fork A) --- */


/*
 * Stage object work (lbl_1_bss_B0->data). player.c fn_1_8358 allocates 0x14C:
 * it holds pointers (M580_COLLOBJ.unk014), so allocate sizeof(M580_STAGE).
 */
typedef struct M580_STAGE_s {
    /* 0x00 */ s32 unk000;           /* goal-motion state (fn_1_87A4) */
    /* 0x04 */ s32 unk004;           /* state timer */
    /* 0x08 */ s32 unk008;           /* motion shown (-1 none; fn_1_8710) */
    /* 0x0C */ M580_COLLOBJ unk00C[5]; /* "wall", "post_R", "post_L", "post_R_C", "post_L_C" */
} M580_STAGE; /* size 0x14C (GC) */


/* --- m580.c --- */
void ObjectSetup(void);
void fn_1_37C(s16 mode, s16 frameNo);
void fn_1_424(s16 mode, s16 frameNo);
void fn_1_510(s16 mode, s16 frameNo);
void fn_1_544(s16 mode, s16 frameNo);
void fn_1_548(s16 mode, s16 frameNo);
void fn_1_574(s16 mode, s16 frameNo);
void fn_1_6FC(s16 mode, s16 frameNo);
void fn_1_740(s16 mode, s16 frameNo);
void fn_1_78C(s16 mode, s16 frameNo);
void fn_1_790(s16 mode, s16 frameNo);
void fn_1_7C4(OMOBJ *obj);
void fn_1_834(OMOBJ *obj);
void fn_1_898(OMOBJ *obj);
void fn_1_C5C(OMOBJ *obj);
void fn_1_10D8(OMOBJ *obj);
void fn_1_1838(void *data);
s32 fn_1_18A8(void);
void fn_1_18D8(s32 on);
void fn_1_1908(HuVecF *pos);
float fn_1_1970(void);
s32 fn_1_1D04(void);
s32 fn_1_1D40(s32 no);
s32 fn_1_1D58(u32 team);
void fn_1_1E14(s32 no, s32 team, s32 charNo);
s32 fn_1_1E4C(u32 team, u32 idx);
void fn_1_1EC4(s32 no);
s32 fn_1_1EE4(void);
void fn_1_1F34(s32 no);
s32 fn_1_1FA8(float x);
s32 fn_1_2004(HuVecF *pos);
s32 fn_1_2098(HuVecF *pos);
s32 fn_1_212C(s32 seNo, HuVecF *pos);
s32 fn_1_2260(s32 seNo, HuVecF *pos);
void fn_1_2318(s32 seId, HuVecF *pos);
void fn_1_246C(s32 time);
void fn_1_248C(void);
float fn_1_2634(float cur, float target, float rate);
float fn_1_2750(float from, float to);

/* --- player.c --- */
void fn_1_2804(OMOBJMAN *objman);
void fn_1_29EC(void);
void fn_1_2A10(OMOBJ *obj);
void fn_1_2EA0(OMOBJ *obj);
void fn_1_37C0(OMOBJ *obj);
void fn_1_3B30(OMOBJ *obj);
void fn_1_3E94(OMOBJ *obj);
void fn_1_4124(OMOBJ *obj, s32 seNo);
void fn_1_4198(OMOBJ *obj);
void fn_1_440C(OMOBJ *obj);
void fn_1_4488(OMOBJ *obj);
void fn_1_4DDC(OMOBJ *obj);
s32 fn_1_4F58(OMOBJ *obj, HuVecF *target, float rot, float speed);
s32 fn_1_5504(OMOBJ *obj);
s32 fn_1_55A0(OMOBJ *obj);
s32 fn_1_5704(void);
s32 fn_1_5770(OMOBJ *obj);
s32 fn_1_583C(OMOBJ *obj);
s32 fn_1_58D8(M580_COLLACTOR *self, M580_COLLACTOR *other); /* used as M580_COLLHITFUNC */
void fn_1_5A14(OMOBJ *obj);
void fn_1_5B94(OMOBJ *obj);
void fn_1_5C64(OMOBJ *obj, M580_COMFUNC func);
s32 fn_1_5CB0(OMOBJ *obj, HuVecF *target, float rotY, float speed);
s32 fn_1_63D4(OMOBJ *obj);
void fn_1_6450(OMOBJ *obj);
void fn_1_6548(OMOBJ *obj);
void fn_1_6754(OMOBJ *obj);
void fn_1_6878(OMOBJ *obj);
void fn_1_6D84(OMOBJ *obj);
void fn_1_6FC4(OMOBJ *obj);
void fn_1_74D4(OMOBJ *obj);
void fn_1_7634(OMOBJ *obj, u32 motNo);
BOOL fn_1_774C(OMOBJ *obj);
BOOL fn_1_77B8(OMOBJ *obj);
OMOBJ *fn_1_7818(OMOBJ *obj);
s32 fn_1_78B4(OMOBJ *obj);
float fn_1_79C4(OMOBJ *obj, HuVecF *pos);
float fn_1_7A6C(OMOBJ *obj, HuVecF *pos);
s32 fn_1_7BE4(OMOBJ *obj, HuVecF *pos, float fov);
s32 fn_1_7E2C(OMOBJ *obj);
OMOBJ *fn_1_7E48(u32 team, OMOBJ *exclude, HuVecF *pos, float rotY, float fov, float maxDist, s32 nearest);
s32 fn_1_8194(OMOBJ *obj, HuVecF *pos, float *rotY);
s32 fn_1_8258(u32 team);
void fn_1_82CC(u32 team);
void fn_1_8358(OMOBJMAN *objman);
void fn_1_83F8(void);

/* --- stage.c --- */
extern OMOBJ *lbl_1_bss_B0; /* stage object (player.c fn_1_8358 stores it) */
void fn_1_83FC(OMOBJ *obj);
void fn_1_86D4(OMOBJ *obj);
void fn_1_8710(OMOBJ *obj);
void fn_1_87A4(OMOBJ *obj);
s32 fn_1_89A8(s32 no, HuVecF *pos, float *rotY);

/* --- stick.c --- */
void fn_1_8A64(OMOBJMAN *objman);
void fn_1_8B60(void);
void fn_1_8B64(OMOBJ *obj);
void fn_1_8B98(OMOBJ *obj);
void fn_1_8C08(void);
HU3DMODELID fn_1_8CA4(s32 dataNum);
HU3DMOTID fn_1_8D90(HU3DMODELID mdlId, s32 dataNum);
void fn_1_8E80(OMOBJMAN *objman, M580_STICKDATA *data);
void fn_1_9194(OMOBJ *obj);
void fn_1_92EC(OMOBJ *obj, s32 motNo);
s32 fn_1_943C(OMOBJ *obj);
void fn_1_94A4(char *name, HuVecF *pos, float *rotY);
float fn_1_9528(OMOBJ *obj, HuVecF *pos);
float fn_1_95D0(OMOBJ *obj, HuVecF *pos);
void fn_1_9748(OMOBJ *obj);
void fn_1_9970(OMOBJ *obj);
void fn_1_9F44(OMOBJ *obj);
void fn_1_A260(OMOBJ *obj);
void fn_1_BAC0(OMOBJ *obj);
void fn_1_BD70(OMOBJ *obj);

/* --- puck.c --- */
void fn_1_C8F8(OMOBJMAN *a0);
void fn_1_C998(void);
void fn_1_C99C(OMOBJ *a0);
void fn_1_CBCC(OMOBJ *a0);
void fn_1_CF94(OMOBJ *a0);
s32 fn_1_D018(M580_COLLACTOR *a0, M580_COLLACTOR *a1); /* used as M580_COLLHITFUNC */
s32 fn_1_D054(HuVecF *a0, float b0, float b1, float b2);
OMOBJ *fn_1_D30C(HuVecF *a0, HuVecF *a1);
OMOBJ *fn_1_D390(HuVecF *a0, float b0, HuVecF *a1, OMOBJ *a2);
s32 fn_1_D544(void);
s16 fn_1_D56C(void);
void fn_1_D60C(HuVecF *a0);
void fn_1_D654(void);
void fn_1_D68C(void);
s32 fn_1_D6EC(void);
s32 fn_1_D714(OMOBJ *a0);
s32 fn_1_D7B8(void);

/* --- effect.c --- */
void fn_1_D7E0(OMOBJMAN *objman);
void fn_1_D868(void);
void fn_1_D86C(OMOBJ *obj);
void fn_1_D8C0(OMOBJ *obj);
void fn_1_D8F8(OMOBJ *obj);
void fn_1_DA00(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_DC10(OMOBJ *obj);
void fn_1_DD18(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_DF28(OMOBJ *obj);
void fn_1_DFD8(OMOBJ *obj);
void fn_1_E114(HU3DMODEL *model, Mtx *mtx);
void fn_1_E36C(M580_EFFECTSHADOW *shadow, Mtx *mtx);
void fn_1_E8D0(OMOBJ *obj);
void fn_1_E9B8(OMOBJ *obj);
void fn_1_EBCC(HuVecF *pos);
void fn_1_EC74(HuVecF *pos, HuVecF *accel);
void fn_1_ED34(M580_EFFECTSHADOW *shadow);
void fn_1_EDF8(s32 on);

/* --- score.c --- */
void fn_1_EE34(OMOBJMAN *a0);
void fn_1_EEBC(void);
void fn_1_EEC0(OMOBJ *a0);
void fn_1_EF0C(OMOBJ *a0);
void fn_1_EF4C(OMOBJ *a0);
void fn_1_F0B8(OMOBJ *a0);
void fn_1_F254(OMOBJ *a0);
void fn_1_F4E8(M580_SCOREOVLSPR *a0);
void fn_1_F640(M580_SCORESPRNUM *a0, M580_SCOREOVLSPR *a1, u32 a2);
void fn_1_F758(OMOBJ *a0);
void fn_1_10880(u32 a0, u32 a1, u32 a2);
void fn_1_108DC(OMOBJ *a0);
void fn_1_10C44(OMOBJ *a0);
void fn_1_10F58(s32 a0, s32 a1);
s32 fn_1_1100C(s32 a0);
s32 fn_1_11044(void);
s32 fn_1_1104C(void);

/* --- reflect.c --- */
void fn_1_110A0(OMOBJMAN *objman);
void fn_1_11128(void);
void fn_1_1112C(OMOBJ *obj);
void fn_1_1113C(OMOBJ *obj);
s32 fn_1_11410(M580_COLLACTOR *a, M580_COLLACTOR *b);
s32 fn_1_11880(M580_COLLACTOR *a, M580_COLLOBJ *b);
s32 fn_1_11DC4(M580_COLLACTOR *actor);
s32 fn_1_11E3C(M580_COLLOBJ *o);
void fn_1_11EB4(s32 idx);
void *fn_1_11F18(s32 idx);
void fn_1_11F88(M580_COLLOBJ *b, HSFOBJECT *objs, s32 num);
void fn_1_12248(M580_COLLOBJ *b, s16 mdlId);
void fn_1_1229C(M580_COLLOBJ *b, HSFOBJECT *obj);
void fn_1_122D0(M580_COLLOBJ *b);
s32 fn_1_126C8(M580_COLLOBJ *b, HuVecF *pos);

#endif
