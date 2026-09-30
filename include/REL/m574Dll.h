#ifndef M574DLL_H
#define M574DLL_H

/*
 * m574Dll (overlay #85): types and prototypes shared by its six translation
 * units (m574 player stage ball score collide).
 *
 * Offsets are GameCube ones from build/mp5-asm/m574Dll. No upstream names exist,
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

typedef struct {
    u16 unk00; /* lhz: motion number */
    u16 unk02;
    float unk04; /* lfs */
    u32 unk08; /* lwz: motion attr */
} M574_MOTPARAM; /* player lbl_1_data_C4[5], 0xC each */

/* player.c: COM tuning, lbl_1_data_1BC[4] indexed by GwPlayerConf.dif & 3 (mulli 0x18, fn_1_19AC) */
typedef struct {
    float unk00; /* lfs: farthest ball the COM reacts to (fn_1_6D7C maxDist) */
    s32 unk04; /* lwz: first wait, slow ball */
    s32 unk08; /* lwz: second wait, slow ball */
    s32 unk0C; /* lwz: first wait, fast ball */
    s32 unk10; /* lwz: second wait, fast ball */
    float unk14; /* lfs: chance threshold against a [0,1) roll */
} M574_COMPARAM; /* size 0x18 (GC) */

/* player.c: obj->data of each player object (HuMemDirectMallocNum 0x78, fn_1_1068) */
typedef struct {
    s32 unk000; /* player number (obj->work[0]) */
    u32 unk004; /* team (obj->work[1]); cmplw in fn_1_1CD4/1F28/1F9C */
    s32 unk008; /* slot in team order, 0..3 (obj->work[2]); indexes lbl_1_data_100/130/160/1AC */
    s32 unk00C; /* charNo (extsh at every use) */
    s32 unk010; /* current lbl_1_data_C4 motion, -1 = none */
    u32 unk014; /* HuPadBtnDown copy */
    u32 unk018; /* HuPadBtn copy (0x100 = A) */
    float unk01C; /* cleared every frame, otherwise unused */
    float unk020; /* cleared every frame; > 0 is handed to fn_1_6478 */
    s32 unk024; /* GwPlayerConf.type: nonzero = COM */
    s32 unk028; /* GwPlayerConf.dif & 3 */
    s32 unk02C; /* COM state 0..2 (fn_1_19AC) */
    s32 unk030; /* COM wait counter */
    s32 unk034; /* COM: target ball is fast */
    s32 unk038; /* mode (switch in fn_1_1264 / fn_1_1588) */
    s32 unk03C; /* mode counter */
    s32 unk040; /* frame counter */
    s32 unk044; /* mode timer */
    HuVecF unk048; /* position */
    HuVecF unk054; /* velocity */
    u8 pad060[0xC];
    float unk06C; /* rotY */
    s32 unk070; /* set 1 when the game ends */
    s32 unk074; /* cleared once the current motion ends */
} M574_PLAYER; /* size 0x78 (GC) */

/*
 * Collision actor: a circle in the X/Y plane (Z is ignored). Registered in
 * the 0x52 actor slots by fn_1_8AD0 (ball.c); the owner keeps the storage.
 * Size is a guess (highest offset read by collide.c is 0x2C).
 */
typedef struct M574_COLLACTOR_s {
    /* 0x00 */ u32 unk00;           /* bit 0 live; bit 1 skip obstacles (7AE4 rlwinm 30,30) */
    /* 0x04 */ u32 unk04;           /* unused by collide.c */
    /* 0x08 */ s32 unk08;           /* unused by collide.c */
    /* 0x0C */ s32 unk0C;           /* must be 0 to collide (7AE4 cmpwi 0) */
    /* 0x10 */ void *unk10;         /* argument handed to unk14 */
    /* 0x14 */ void (*unk14)(void *arg); /* post-pass callback (7AE4 bctrl) */
    /* 0x18 */ HuVecF *unk18;       /* position (owner's storage) */
    /* 0x1C */ HuVecF *unk1C;       /* velocity (owner's storage) */
    /* 0x20 */ HuVecF unk20;        /* previous position, x/y read (82AC/87B8) */
    /* 0x2C */ float unk2C;         /* radius */
} M574_COLLACTOR; /* size 0x30 (GC) -- guessed */
typedef M574_COLLACTOR M574_COLLIDE; /* ball.c's name for the same record */

/* ball.c: one ball; the ball object's data is M574_BALL[80] (0x21C0, fn_1_6650) */
typedef struct {
    s32 unk000; /* state: 0 free, 1 launched, 2 dropping in, 3 in play */
    u8 pad004[4];
    s32 unk008; /* cleared at launch */
    s32 unk00C; /* set once past y 1600, cleared below y 1550 */
    s32 unk010; /* last fn_1_6B38 result (inside the net area) */
    s16 unk014; /* model id */
    u8 pad016[2];
    HuVecF unk018; /* position */
    HuVecF unk024; /* velocity */
    u8 pad030[0xC];
    M574_COLLIDE unk03C; /* collide record */
} M574_BALL; /* size 0x6C (GC) */

/* score.c: one team's score board, 0x1C each */
typedef struct {
    s32 unk000; /* score (lwz; fn_1_77D4 adds, clamped 99999) */
    s32 unk004; /* displayed score, counts up to unk000 by 10/40 (fn_1_7328) */
    s32 unk008; /* bonus blink timer (fn_1_7874 sets 60) */
    s32 unk00C; /* bonus value shown while unk008 runs */
    HU3DANIMID unk010[5]; /* digit animations, sthx/lhax 0x10+j*2 (fn_1_7238) */
    u8 pad01A[2];
} M574_SCORETEAM; /* size 0x1C (GC) */

/* score.c: lbl_1_bss_58->data. Holds a pointer (unk048): allocated with sizeof. */
typedef struct {
    M574_SCORETEAM unk000[2]; /* per team, mulli 0x1C */
    s32 unk038; /* record window state (fn_1_75EC) */
    s32 unk03C; /* record window pulse timer */
    s32 unk040; /* record: GWMgRecordGet(9), cmpw signed in fn_1_797C */
    HUSPRGRPID unk044; /* MgScoreWinCreate */
    HUSPRGRPID unk046; /* record icon sprite group (lha) */
    MGSCORE *unk048; /* MgScoreCreate result (lwz) */
} M574_SCORE; /* size 0x4C (GC) */

/* ------------------------------------------------------------- collide.c */



/* One transformed collision segment (2D line with outward normal). */
typedef struct M574_COLLSEG_s {
    /* 0x00 */ HuVecF unk00;        /* end point 0 (world) */
    /* 0x0C */ HuVecF unk0C;        /* end point 1 (world) */
    /* 0x18 */ HuVecF unk18;        /* unit normal (-dy, dx, 0) */
    /* 0x24 */ float unk24;         /* plane distance: n . p + d = 0 */
} M574_COLLSEG; /* size 0x28 (GC) */

/* One source edge in model space, from an HSF quad (8C94). */
typedef struct M574_COLLEDGE_s {
    /* 0x00 */ HuVecF unk00;        /* end point 0 (x/y only; z left 0) */
    /* 0x0C */ HuVecF unk0C;        /* end point 1 */
    /* 0x18 */ Mtx *unk18;          /* owning object's matrix (unk34[] slot) */
} M574_COLLEDGE; /* size 0x1C (GC) */

typedef struct M574_COLLOBJ_s M574_COLLOBJ;
typedef s32 (*M574_COLLHITFUNC)(M574_COLLOBJ *obj, M574_COLLACTOR *actor);

/*
 * Collision obstacle, registered in the 0x14 obstacle slots by fn_1_8B48
 * (stage.c). unk0C selects the shape: 0 = circle (unk01C.pos / unk020.radius),
 * 1 = segment mesh built by fn_1_8C94 (unk01C.num / unk020.seg ...).
 */
struct M574_COLLOBJ_s {
    /* 0x00 */ u32 unk00;           /* bit 0 live */
    /* 0x04 */ u32 unk04;           /* kind; 6 = only collides on its X side (87B8 cmplwi 6) */
    /* 0x08 */ s32 unk08;           /* kind 6: (unk08 >> 1) is the side, 0 = x<0, 1 = x>=0 */
    /* 0x0C */ s32 unk0C;           /* shape: 0 circle, 1 mesh */
    /* 0x10 */ void *unk10;          /* owner (stage: the stage OMOBJ); stage writes it */
    /* 0x14 */ void (*unk14)(void *arg); /* stage writes NULL */
    /* 0x18 */ M574_COLLHITFUNC unk18; /* hit callback; mesh: nonzero result skips the bounce */
    /* 0x1C */ union {
        HuVecF *pos;                /* circle: centre */
        s32 num;                    /* mesh: segment count */
    } unk01C;
    /* 0x20 */ union {
        float radius;               /* circle: radius */
        M574_COLLSEG *seg;          /* mesh: this frame's segments */
    } unk020;
    /* 0x24 */ M574_COLLSEG *unk024; /* mesh: last frame's segments (swapped by 8FDC) */
    /* 0x28 */ M574_COLLEDGE *unk028; /* mesh: source edges */
    /* 0x2C */ s32 unk02C;          /* mesh: HSF object count */
    /* 0x30 */ HSFTRANSFORM **unk030; /* mesh: &object->mesh.base per object */
    /* 0x34 */ Mtx *unk034;         /* mesh: per-object matrix */
    /* 0x38 */ M574_COLLSEG *unk038; /* mesh: segment last hit (set before unk18) */
}; /* size 0x3C (GC) -- at least; nothing past 0x38 read here */

/* collide object work (lbl_1_bss_60->data), 0x198 bytes (GC). */
typedef struct M574_COLLWORK_s {
    /* 0x000 */ M574_COLLACTOR *unk000[82];
    /* 0x148 */ M574_COLLOBJ *unk148[20];
} M574_COLLWORK; /* size 0x198 (GC) */

/* --- stage.c (fork S) ---
 * Stage object records. One 0x88 layout is used by five arrays; each uses a
 * subset of it (stage.c fn_1_2514/34B0/3154, T's 448C/4660/5750/5934).
 */
typedef struct {
    s32 unk000; /* state */
    s32 unk004; /* timer */
    s32 unk008;
    s32 unk00C;
    HuVecF unk010; /* position */
    HuVecF unk01C; /* velocity / offset */
    HuVecF unk028; /* walkers: rotation, unk028.y eased by fn_1_CC8 (4EE8) */
    float unk034; /* launcher: ball height offset (34B0); walkers: direction -1/0/1; blocks: raise offset (4660) */
    s32 unk038; /* hit flag from the collide callbacks: walkers 1 ball (5628) / 2 block (5680); bomb 1 (5D64) */
    float unk03C; /* walkers: scale x..z (Hu3DModelScaleSetV, 4EE8); bomb: model-object base pos (5750) */
    float unk040;
    float unk044;
    void *unk048; /* launchers: M574_COLLACTOR * held (34B0/3704); blocks: HSFOBJECT * */
    M574_COLLOBJ unk04C; /* bumpers: circle obstacle (2F8C) */
} M574_STAGEOBJ; /* size 0x88 (GC) */

typedef struct {
    float unk000; /* last fn_1_6478 value (SE when it rises > 0.2) */
    float unk004; /* swing speed, (target - angle) / 60, sign by side (2B88) */
    float unk008; /* angle, rot z (2B88) */
    float unk00C; /* target angle (lbl_1_data_280, T's fn_1_6478) */
    s32 unk010; /* layer switched at MGSEQ_MODE_FINISH */
    M574_COLLOBJ unk014; /* kind-6 mesh obstacle, hit fn_1_2D88 */
} M574_PADDLE; /* size 0x50 (GC) */

typedef struct {
    s32 unk000; /* state 0..4 (3A1C switch, cmpwi) */
    s32 unk004; /* timer */
    s32 unk008; /* result wait */
    s32 unk00C; /* spin SE handle (-1 at init) */
    s32 unk010; /* spinning */
    s32 unk014[3]; /* reel stopped */
    s32 unk020[3]; /* reel symbol, lbl_1_data_2C4 value 0..2 */
    float unk02C[3]; /* reel angle shown */
    float unk038[3]; /* reel angle target */
    float unk044[3]; /* reel speed */
    HSFOBJECT *unk050[3]; /* reel objects "slot_*" */
} M574_SLOT; /* size 0x5C (GC) */

/* lbl_1_bss_48->data, HuMemDirectMallocNum 0x108C (fn_1_2028) */
typedef struct {
    s32 unk000[2]; /* per side ball resupply timer, 120 (26F4) */
    s16 unk008; /* tex scroll id, "m548time" (5E5C) */
    u8 pad00A[2];
    s32 unk00C; /* bomb counter, 5 -> 0 (5934); indexes unk09C[4 - n] (63B0) */
    float unk010; /* counter shown on the texture, eases towards unk00C (5ECC) */
    M574_STAGEOBJ unk014; /* Bowser (launch point, 2514) */
    s16 unk09C[5]; /* particle model ids (6168) */
    u8 pad0A6[2];
    M574_PADDLE unk0A8[4];
    M574_SLOT unk1E8[2];
    M574_STAGEOBJ unk2A0[2]; /* ball launchers */
    M574_STAGEOBJ unk3B0[14]; /* blocks */
    M574_STAGEOBJ unkB20[6]; /* bumpers */
    M574_STAGEOBJ unkE50[2];
    M574_COLLOBJ unkF60; /* kind-5 stage mesh obstacle */
    M574_COLLOBJ unkF9C[4]; /* kind-4 wall meshes "b_ata*", hit fn_1_47DC (448C) */
} M574_STAGE; /* size 0x108C (GC) */

/* --- m574.c --- */
void ObjectSetup(void);
void fn_1_348(s16 mode, s16 frameNo);
void fn_1_3B8(s16 mode, s16 frameNo);
void fn_1_548(s16 mode, s16 frameNo);
void fn_1_54C(s16 mode, s16 frameNo);
void fn_1_5A8(s16 mode, s16 frameNo);
void fn_1_730(s16 mode, s16 frameNo);
void fn_1_82C(s16 mode, s16 frameNo);
void fn_1_8E4(s16 mode, s16 frameNo);
void fn_1_8E8(s16 mode, s16 frameNo);
s32 fn_1_918(void); /* lha of an s16 global, but callers do not extsh (stage fn_1_26F4 0x2728) */
s32 fn_1_928(s32 no);
s32 fn_1_940(u32 team);
void fn_1_9FC(s32 no, s32 team, s32 charNo);
s32 fn_1_A34(u32 team, u32 idx);
void fn_1_AAC(s32 no);
s32 fn_1_B20(float x);
s32 fn_1_B7C(HuVecF *pos);
s32 fn_1_C10(s32 seNo, HuVecF *pos);
float fn_1_CC8(float cur, float target, float rate);
float fn_1_DE4(float from, float to);

/* --- player.c --- */
void fn_1_E98(OMOBJMAN *objman);
void fn_1_1044(void);
void fn_1_1068(OMOBJ *obj);
void fn_1_1264(OMOBJ *obj);
void fn_1_1588(OMOBJ *obj);
void fn_1_17A0(OMOBJ *obj);
void fn_1_182C(OMOBJ *obj);
void fn_1_1830(OMOBJ *obj);
void fn_1_1938(OMOBJ *obj);
void fn_1_19AC(OMOBJ *obj);
OMOBJ *fn_1_1CD4(OMOBJ *obj);
void fn_1_1D54(OMOBJ *obj, u32 motNo);
BOOL fn_1_1E4C(OMOBJ *obj);
s32 fn_1_1EB8(OMOBJ *obj);
BOOL fn_1_1ED4(OMOBJ *obj, HuVecF *pos, float *rotY);
s32 fn_1_1F28(u32 team);
void fn_1_1F9C(u32 team);

/* --- stage.c --- */
void fn_1_2028(OMOBJMAN *objman);
void fn_1_20C8(void);
void fn_1_20CC(OMOBJ *obj);
void fn_1_2364(OMOBJ *obj);
void fn_1_23E8(OMOBJ *obj, s16 mdlId, s32 idx);
void fn_1_2478(OMOBJ *obj, HuVecF *pos, s32 idx);
void fn_1_2514(OMOBJ *obj, s32 side, s32 num);
void fn_1_26F4(OMOBJ *obj);
void fn_1_2928(OMOBJ *obj);
void fn_1_2B88(OMOBJ *obj);
s32 fn_1_2D88(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_2F8C(OMOBJ *obj);
void fn_1_3154(OMOBJ *obj);
s32 fn_1_3240(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_3374(OMOBJ *obj);
void fn_1_34B0(OMOBJ *obj);
s32 fn_1_3704(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_383C(OMOBJ *obj);
void fn_1_3A1C(OMOBJ *obj);
s32 fn_1_4330(float angle);
void fn_1_43E8(OMOBJ *obj, s32 idx);
s32 fn_1_445C(OMOBJ *obj, s32 idx);
void fn_1_448C(OMOBJ *obj);
void fn_1_4660(OMOBJ *obj);
s32 fn_1_47DC(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_4D28(OMOBJ *obj);
void fn_1_4EE8(OMOBJ *obj);
s32 fn_1_5628(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_5680(HuVecF *pos);
void fn_1_5750(OMOBJ *obj);
void fn_1_5934(OMOBJ *obj);
s32 fn_1_5D64(M574_COLLOBJ *col, M574_COLLACTOR *ball);
void fn_1_5E5C(OMOBJ *obj);
void fn_1_5ECC(OMOBJ *obj);
void fn_1_6168(OMOBJ *obj);
void fn_1_629C(OMOBJ *obj);
void fn_1_62A0(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_63B0(HuVecF *pos, HuVecF *accel, s32 n);
void fn_1_6478(s32 slot, float value);
float fn_1_6568(s32 slot);

/* --- ball.c --- */
void fn_1_6650(OMOBJMAN *objman);
void fn_1_66F0(void);
void fn_1_66F4(OMOBJ *obj);
void fn_1_6730(OMOBJ *obj);
void fn_1_6758(OMOBJ *obj);
void fn_1_686C(OMOBJ *obj);
s32 fn_1_6B38(M574_BALL *ball);
void fn_1_6BD4(M574_BALL *ball);
void fn_1_6C2C(HuVecF *pos, HuVecF *vel);
s32 fn_1_6CC8(s32 side);
s32 fn_1_6D7C(s32 side, HuVecF *pos, float angle, float range, float maxDist);
M574_COLLIDE *fn_1_70B0(s32 no, HuVecF *pos, HuVecF *vel);

/* --- score.c --- */
void fn_1_7130(OMOBJMAN *objman);
void fn_1_71B8(void);
void fn_1_71BC(OMOBJ *obj);
void fn_1_7200(OMOBJ *obj);
void fn_1_7238(OMOBJ *obj);
void fn_1_7328(OMOBJ *obj);
void fn_1_7468(OMOBJ *obj);
void fn_1_75EC(OMOBJ *obj);
void fn_1_77D4(s32 team, s32 kind);
void fn_1_7874(s32 team, s32 kind);
s32 fn_1_7948(s32 team);
s32 fn_1_797C(void);

/* --- collide.c --- */
void fn_1_7A48(OMOBJMAN *objman);
void fn_1_7AD0(void);
void fn_1_7AD4(OMOBJ *obj);
void fn_1_7AE4(OMOBJ *obj);
s32 fn_1_7C88(M574_COLLACTOR *a, M574_COLLACTOR *b);
s32 fn_1_7FD8(M574_COLLACTOR *a, M574_COLLOBJ *b);
s32 fn_1_82AC(M574_COLLACTOR *a, M574_COLLOBJ *b, M574_COLLSEG *seg, HuVecF *prev);
s32 fn_1_87B8(M574_COLLACTOR *a, M574_COLLOBJ *b);
s32 fn_1_8AD0(M574_COLLACTOR *actor);
s32 fn_1_8B48(M574_COLLOBJ *obj);
void fn_1_8BC0(s32 idx);
void *fn_1_8C24(s32 idx);
void fn_1_8C94(M574_COLLOBJ *b, HSFOBJECT *objs, s32 num);
void fn_1_8F54(M574_COLLOBJ *b, s16 mdlId);
void fn_1_8FA8(M574_COLLOBJ *b, HSFOBJECT *obj);
void fn_1_8FDC(M574_COLLOBJ *b);

#endif
