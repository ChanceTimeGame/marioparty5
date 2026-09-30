#ifndef M577DLL_H
#define M577DLL_H

/*
 * m577Dll (overlay #88): types and prototypes shared by its three translation
 * units (m577 stagedata effect).
 *
 * Offsets are GameCube ones from build/mp5-asm/m577Dll. No upstream names exist,
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

/*
 * Shape (fork A, measured over the whole m577.s with a register-tracking scan,
 * merged with fork B's names): ObjectSetup creates the OMOBJMAN (lbl_1_bss_10),
 * the main object (lbl_1_bss_C) whose data is one M577_WORK (0x1BA4 on GC,
 * allocated with sizeof) and four player objects whose data is an M577_PLAYER
 * (0x54, sizeof). Every other struct is embedded in the work; the pointers in
 * M577_TEAM / M577_CART / M577_TOW are set by fn_1_3AB8 and fn_1_3494 to point
 * back into it. No .bss address is ever stored as obj->data.
 */

struct M577_PLAYER;
struct M577_TEAM;
struct M577_NODE;
struct M577_LIST;

/* task node callback: returns 1 when done, and fn_1_278C frees the node */
typedef s32 (*M577_TASKFUNC)(struct M577_NODE *node);

/* task node on the work+0xA8 list (fn_1_263C..fn_1_278C; same code as m567 fn_1_4680..47D0).
   Fork E called it M577_TASK. */
typedef struct M577_NODE { /* size 0x14 (GC) */
    struct M577_NODE *unk000; /* prev */
    struct M577_NODE *unk004; /* next */
    struct M577_LIST *unk008; /* owning list */
    M577_TASKFUNC unk00C; /* callback (fn_1_AB34, AF68, B318, B3CC) */
    void *unk010; /* callback data: M577_PLAYER * or s16 * counter (0x89B0, 0x5ECC) */
} M577_NODE;

/* task list at work+0xA8 (fn_1_263C init, fn_1_26C0 add, fn_1_278C run; add inlined at 0x5DC4). Fork C called it M577_TASKLIST. */
typedef struct M577_LIST { /* size 0x8 (GC) */
    M577_NODE *unk000; /* active head (0x5DEC lwz, 0x5E08 stw) */
    M577_NODE *unk004; /* free head (0x5DC4 lwz, 0x5DD4 stw) */
} M577_LIST;

/* forks C/E spelled these M577_TASK / M577_TASKLIST: same types */
typedef M577_NODE M577_TASK;
typedef M577_LIST M577_TASKLIST;

/* verlet rope between two carts (fn_1_2E08; init fn_1_2B60) */
typedef struct M577_ROPE { /* size 0x4EC (GC) */
    HuVecF unk000[32]; /* node positions (0x2E08 mulli 0xC) */
    HuVecF unk180[32]; /* node velocities */
    HuVecF unk300[32]; /* previous node positions */
    HuVecF unk480; /* start anchor; &unk480 stored in cart unk03C (0x3920) */
    HuVecF unk48C; /* end anchor; &unk48C stored in cart unk038 / tow unk00C */
    float unk498; /* segment rest length */
    float unk49C; /* velocity factor */
    float unk4A0; /* full slack length (=100 for team A, 0x3CBC) */
    float unk4A4; /* stiffness */
    s32 unk4A8; /* node count (<= 32) */
    s16 unk4AC[32]; /* node models */
} M577_ROPE;

/* line through two course points (fn_1_A754 writes it) */
typedef struct M577_LINE { /* size 0x10 (GC) */
    float unk000; /* slope */
    float unk004; /* sqrt(1 + slope^2) */
    float unk008; /* intercept (or x when vertical) */
    s16 unk00C; /* vertical flag */
    u8 pad00E[2];
} M577_LINE;

/* course (work+0x1AC8): fn_1_B498 fills it */
typedef struct M577_COURSE { /* size 0xC (GC) */
    float (*unk000)[2]; /* lbl_1_data_398 (x, z) pairs */
    s32 unk004; /* pair count (0x1FE) */
    float unk008; /* course length: lbl_1_data_398[unk004 - 3][1] (0x377C lfs 0x1AD0) */
} M577_COURSE;

/* particle emitter (effect.c fn_1_B5D4); particle->work points back here */
typedef struct M577_EFFECT { /* size 0x10 (GC) */
    HU3DPARTICLE *unk000; /* Hu3DData[unk00C].hookData; emitCnt is the emit switch (fn_1_B720) */
    ANIMDATA *unk004; /* particle animation */
    HuVecF *unk008; /* emitter position, read by fn_1_B730 */
    s16 unk00C; /* particle model */
    u8 pad00E[2];
} M577_EFFECT;

/* team A's lead/tow object (work+0x1AD4), cart[0]->unk040 */
typedef struct M577_TOW { /* size 0x30 (GC) */
    HuVecF unk000; /* position (0x413C..0x41D4) */
    HuVecF *unk00C; /* rope end anchor (0x3940); Hu3DModelObjPosGet "mark01" (0xAA4C) */
    M577_EFFECT *unk010; /* effect (0x3D40) */
    float unk014;
    float unk018;
    float unk01C; /* 0x85F4 lfs/stfs */
    float unk020; /* initial y */
    float unk024;
    s16 unk028; /* model (data_1FC[7]) */
    s16 unk02A; /* model (data_1FC[6]) hooked on unk028 "mark03" */
    s16 unk02C; /* model (data_1FC[8]) */
    u8 pad02E[2];
} M577_TOW;

typedef struct M577_CART { /* size 0x68 (GC) */
    struct M577_PLAYER *unk000; /* rider (0x3E48) */
    struct M577_TEAM *unk004; /* team (0x3688) */
    M577_LINE unk008; /* fn_1_A754 (0x457C) */
    float unk018; /* (x, z) point tested by fn_1_B4D0 (0x72D0) */
    float unk01C;
    HuVecF unk020; /* position */
    HuVecF unk02C; /* rotation */
    HuVecF *unk038; /* rope end anchor (0x399C) */
    HuVecF *unk03C; /* rope start anchor (0x392C) */
    M577_TOW *unk040; /* team A cart only (0x3C9C) */
    M577_EFFECT *unk044; /* (0x3CFC) */
    float unk048;
    float unk04C; /* 0x85F4, 0x8BB8 */
    float unk050; /* 0x85F4, 0x8BB8 */
    float unk054; /* course height */
    float unk058;
    s16 unk05C; /* model (data_1FC[5]) */
    s16 unk05E; /* model (data_1FC[6]) hooked "mark03" */
    s16 unk060; /* model (data_1FC[8]) */
    s16 unk062;
    s16 unk064;
    u8 pad066[2];
} M577_CART;

typedef void (*M577_PLAYERFUNC)(struct M577_PLAYER *player);
typedef void (*M577_TEAMFUNC)(struct M577_TEAM *team);

/* player object data (fn_1_1870 init) */
typedef struct M577_PLAYER { /* size 0x54 (GC) */
    HuVecF unk000; /* position (omSetTra) */
    HuVecF unk00C; /* rotation (omSetRot) */
    OMOBJ *unk018; /* player object: ->mtnId motions (0xAB9C), ->data is this player (0x1A20) */
    struct M577_TEAM *unk01C; /* team (0x3BBC) */
    M577_CART *unk020; /* cart (0x44EC) */
    M577_PLAYERFUNC unk024; /* state func, called with the player (0x1B9C): 64BC/674C man, 6ACC/6D0C COM */
    float unk028; /* motion max time (0x1AC0; 0xB0D0 lfs) */
    float unk02C; /* motion speed, eased to 0.5 (0xAEB8 stfs) */
    s16 *unk030; /* stagedata s16 stream (fn_1_B430/B460, 0x35E4) */
    s16 unk034; /* blink counter (0xB420 lha/sth); 0 -> 1 at the course end (0x75AC, 0x75E0) */
    s16 unk036; /* character model */
    s16 unk038; /* player number (obj->work[0]; 0xB0AC omVibrate) */
    s16 unk03A; /* character number (0xAC9C CharMotionShiftSet) */
    s16 unk03C; /* grp: 0 = solo side (0x3B98) */
    s16 unk03E; /* pad no. (0x64E4 HuPadStkX index) */
    u8 pad040[4]; /* unreferenced */
    s16 unk044; /* COM flag (GwPlayerConf type) */
    s16 unk046; /* COM difficulty (stream index) */
    s16 unk048; /* team slot (0x3C08) */
    s16 unk04A; /* set 2 when the finish motion ends (0xAFFC) */
    s16 unk04C; /* finish-motion state (0xAC64 switch) */
    s16 unk04E; /* finish-motion timer (0xACE8) */
    s16 unk050; /* steer input -1/0/1: stick (0x6508) or COM stream value (0x6AF4) */
    u8 pad052[2];
} M577_PLAYER;

/* orbit camera, one per side (fn_1_2364 init, fn_1_23CC update) */
typedef struct M577_VIEW { /* size 0x38 (GC) */
    HuVecF unk000; /* target; .x = cart x / 2 (0x78C4) */
    float unk00C; /* angle x (yaw) */
    float unk010; /* angle y (pitch) */
    float unk014; /* distance */
    u8 pad018[0x1C]; /* unreferenced */
    s16 unk034; /* camera bit (passed as u16) */
    u8 pad036[2];
} M577_VIEW;

/* stage models (fn_1_45AC creates, fn_1_579C runs) */
typedef struct M577_STAGE { /* size 0x64 (GC) */
    float unk000; /* rotation y */
    s16 unk004;
    s16 unk006;
    s16 unk008;
    s16 unk00A;
    s16 unk00C;
    s16 unk00E;
    s16 unk010;
    s16 unk012;
    s16 unk014;
    s16 unk016;
    s16 unk018;
    s16 unk01A;
    s16 unk01C;
    s16 unk01E;
    s16 unk020;
    s16 unk022[11];
    s16 unk038;
    s16 unk03A;
    s16 unk03C[11]; /* flag per unk022[] model (0x579C) */
    s16 unk052;
    s16 unk054;
    s16 unk056;
    s16 unk058; /* fn_1_26C0 data (0x7EC) */
    s16 unk05A; /* fn_1_26C0 data (0x7EC) */
    s16 unk05C; /* counter, arg of task fn_1_B3CC (0x5DE4, 0x5E10) */
    s16 unk05E; /* counter, arg of task fn_1_B3CC (0x5EA0, 0x5ECC) */
    s16 unk060; /* team side (0x3544) */
    u8 pad062[2];
} M577_STAGE;

typedef struct M577_TEAM { /* size 0x4C (GC) */
    M577_PLAYER *unk000[3];
    M577_CART *unk00C[3];
    M577_VIEW *unk018;
    M577_STAGE *unk01C;
    M577_ROPE *unk020[2];
    M577_COURSE *unk028;
    M577_TEAMFUNC unk02C; /* state: fn_1_703C idle, 7040, 72D0, 7D24, 85F4, 8BB8, 9380, 9C08, A36C, A5CC */
    float unk030;
    float unk034;
    float unk038;
    float unk03C; /* distance along the course (0x7EC: / unk028->unk008) */
    s16 unk040; /* side: 0 = solo, 1 = trio */
    s16 unk042; /* player count */
    s16 unk044;
    s16 unk046; /* sub-state (0x7078 switch in fn_1_7040) */
    s16 unk048; /* timer (0x723C) */
    s16 unk04A;
} M577_TEAM;

/* split-screen divider (work+0xA58; fn_1_1FEC init, fn_1_2044 viewports) */
typedef struct M577_SPLIT { /* size 0xC (GC) */
    float unk000; /* divider x */
    float unk004;
    s16 unk008; /* unreferenced */
    s16 unk00A;
} M577_SPLIT;

#define M577_NODE_MAX 108

typedef struct M577_WORK { /* size 0x1BA4 (GC) */
    M577_PLAYER *unk000[4];
    M577_TEAM unk010[2]; /* [0] solo, [1] trio; indexed by winner ^ 1 (0x7EC, 0xBF8 mulli 0x4C) */
    M577_LIST unk0A8;
    M577_NODE unk0B0[M577_NODE_MAX];
    M577_VIEW unk920[2];
    M577_STAGE unk990[2];
    M577_SPLIT unkA58;
    M577_CART unkA64[4];
    M577_ROPE unkC04[3];
    M577_COURSE unk1AC8;
    M577_TOW unk1AD4;
    M577_EFFECT unk1B04[5];
    float unk1B54; /* course rotation progress (0xB370) */
    s16 unk1B58; /* esprite (0x286C) */
    s16 unk1B5A; /* esprite, solo progress marker (0xB29C) */
    s16 unk1B5C; /* esprite, trio progress marker (0xB314) */
    s16 unk1B5E; /* winning team, -1 none/draw (fn_1_7EC); nonzero: no switch to fn_1_9380 at the course end (0x7738) */
    s16 unk1B60; /* sequence step */
    s16 unk1B62; /* sequence timer */
    s16 unk1B64;
    s16 unk1B66; /* play active: players run, stage animates (0x1B40, 0x5A90) */
    s16 unk1B68[25]; /* model cache, indexed like lbl_1_data_1FC (-1 from fn_1_1CF4) */
    s16 unk1B9A[4]; /* motion cache, indexed like lbl_1_data_260 (-1 from fn_1_1CF4) */
    u8 pad1BA2[2];
} M577_WORK;

/* --- m577.c globals --- */
extern const u16 lbl_1_rodata_10[4]; /* camera bits */
extern s32 lbl_1_data_1FC[25];
extern s32 lbl_1_data_260[4];
extern s32 lbl_1_bss_0[2]; /* HuAudFXPlay ids, lbl_1_data_2A0[i] = playing */
extern s32 lbl_1_bss_8; /* HuAudBGMPlay id */
extern OMOBJ *lbl_1_bss_C; /* main object; data is M577_WORK */
extern OMOBJMAN *lbl_1_bss_10;

/* --- stagedata.c globals --- */
#define M577_COURSE_PTS 510
extern float lbl_1_data_398[M577_COURSE_PTS][2]; /* course (x, z) pairs */

/* --- m577.c --- */
void ObjectSetup(void);
void fn_1_1F4(s16 mode, s16 frameNo);
void fn_1_314(s16 mode, s16 frameNo);
void fn_1_798(s16 mode, s16 frameNo);
void fn_1_7EC(s16 mode, s16 frameNo);
void fn_1_B0C(s16 mode, s16 frameNo);
void fn_1_BF8(s16 mode, s16 frameNo);
void fn_1_1600(s16 mode, s16 frameNo);
void fn_1_1790(s16 mode, s16 frameNo);
void fn_1_17CC(s16 mode, s16 frameNo);
void fn_1_1870(OMOBJ *obj);
void fn_1_1B40(OMOBJ *obj);
void fn_1_1BC4(void);
void fn_1_1BC8(OMOBJ *obj);
void fn_1_1C4C(OMOBJ *obj);
void fn_1_1CF0(void);
void fn_1_1CF4(M577_WORK *work);
void fn_1_1D50(M577_WORK *work);
void fn_1_1DD8(M577_WORK *work);
void fn_1_1FEC(M577_SPLIT *split);
void fn_1_2044(M577_SPLIT *split);
void fn_1_225C(M577_SPLIT *split);
void fn_1_2260(void);
void fn_1_2364(M577_VIEW *view, s16 cameraBit);
void fn_1_23CC(M577_VIEW *view);
void fn_1_263C(M577_LIST *list, M577_NODE *pool, s32 num);
M577_NODE *fn_1_26C0(M577_LIST *list, M577_TASKFUNC func, void *data);
void fn_1_2714(M577_NODE *node);
void fn_1_278C(M577_LIST *list);
void fn_1_286C(M577_WORK *work);
void fn_1_2B60(M577_ROPE *rope, s32 num);
void fn_1_2E08(M577_ROPE *rope);
void fn_1_3494(M577_TEAM *team, s16 side);
void fn_1_3AB8(M577_WORK *work);
void fn_1_3E10(M577_CART *cart, M577_PLAYER *player, s32 side);
void fn_1_45AC(M577_STAGE *stage, u16 cameraBit);
void fn_1_579C(M577_STAGE *stage);
void fn_1_5F7C(M577_PLAYER *player);
void fn_1_61A4(M577_PLAYER *player);
void fn_1_64BC(M577_PLAYER *player);
void fn_1_674C(M577_PLAYER *player);
void fn_1_6ACC(M577_PLAYER *player);
void fn_1_6D0C(M577_PLAYER *player);
void fn_1_703C(M577_TEAM *team);
void fn_1_7040(M577_TEAM *team);
void fn_1_72A8(M577_TEAM *team);
void fn_1_72D0(M577_TEAM *team);
void fn_1_7D24(M577_TEAM *team);
void fn_1_85F4(M577_TEAM *team);
void fn_1_8BB8(M577_TEAM *team);
void fn_1_9380(M577_TEAM *team);
void fn_1_9C08(M577_TEAM *team);
void fn_1_A36C(M577_TEAM *team);
void fn_1_A5CC(M577_TEAM *team);
void fn_1_A754(M577_LINE *line, float *p0, float *p1);
float fn_1_A8D4(M577_LINE *line, float *pos);
float fn_1_A9D0(M577_LINE *line, float z);
void fn_1_AA4C(M577_WORK *work);
s32 fn_1_AB34(M577_NODE *node);
s32 fn_1_AF68(M577_NODE *node);
void fn_1_B134(M577_WORK *work);
void fn_1_B26C(M577_WORK *work);
s32 fn_1_B318(M577_NODE *node);
s32 fn_1_B3CC(M577_NODE *node);

/* --- stagedata.c --- */
s16 *fn_1_B430(s32 level, s32 pattern);
s16 *fn_1_B460(s32 slot, s32 level, s32 pattern);
void fn_1_B498(M577_COURSE *course);
s32 fn_1_B4D0(float *pos, float (*quad)[2]);

/* --- effect.c --- */
void fn_1_B5D4(M577_EFFECT *effect, u16 cameraBit, HuVecF *pos);
void fn_1_B71C(M577_EFFECT *effect);
void fn_1_B720(M577_EFFECT *effect, s32 mode);
void fn_1_B730(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

#endif
