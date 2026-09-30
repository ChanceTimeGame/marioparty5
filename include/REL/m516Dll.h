#ifndef M516DLL_H
#define M516DLL_H

/*
 * m516dll (MG_TYPE_4P, overlay #30): types and prototypes shared by its seven
 * translation units (m516, camera, player, stage, effect, score, actor).
 *
 * Offsets are GameCube ones from build/mp5-asm/m516Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels; work-struct
 * fields are named by hex offset.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "game/mg/timer.h"
#include "humath.h"
#include "game/gamemes.h"
#include "game/mg/score.h"
#include "game/sprite.h"
#include "game/hsfformat.h"
#include "dolphin/gx.h"

/*
 * Work structs. Every field is named by its hex offset; the width of the
 * digits follows the struct's chosen spelling (M516_MAIN and M516_PLAYER use
 * three digits, everything else two -- see MERGE.md).
 */

/* ---------------------------------------------------------------- m516.c */

/* 0x64 bytes: the main object's work (fn_1_330); obj->data of lbl_1_bss_18. */
typedef struct M516Main_s {
    /* 0x00 */ s32 unk000;              /* mode: 0 open, 1 camera, 2 play, 3 result, 4 sys exit, 5 closing */
    /* 0x04 */ s32 unk004;              /* frames since the last mode change */
    /* 0x08 */ s32 unk008;              /* set while the closing wipe runs; freezes fn_1_524 */
    /* 0x0C */ s32 unk00C;              /* cleared by fn_1_330 and never read again */
    /* 0x10 */ u32 unk010;              /* camera phase (camera.c) */
    /* 0x14 */ u32 unk014;              /* camera phase timer; BGM 84 starts at 18 */
    /* 0x18 */ s32 unk018;              /* play phase: 0 start mes, 1 wait, 2 play, 3 finish mes, 4 done */
    /* 0x1C */ s32 unk01C;              /* play phase timer */
    /* 0x20 */ s32 unk020;              /* result phase (camera.c fn_1_21C4) */
    /* 0x24 */ u32 unk024;              /* result phase timer (unsigned: camera.c fn_1_21C4 converts it) */
    /* 0x28 */ s32 unk028[4];           /* per player, arg 1 of fn_1_19E0 */
    /* 0x38 */ s32 unk038[4];           /* per player charNo, arg 2 of fn_1_19E0 */
    /* 0x48 */ s32 unk048[4];           /* per player winner charNo or -1 (fn_1_2108, fn_1_18B0) */
    /* 0x58 */ s32 unk058;              /* 1 until fn_1_2108 resolves the winners */
    /* 0x5C */ u32 unk05C;              /* fn_1_18E0: nibble bit per player; 0x1111 when all four are done */
    /* 0x60 */ u32 unk060;              /* fn_1_1910: nibble bit per player */
} M516_MAIN;

/* -------------------------------------------------------------- camera.c */

/* 0x18 bytes: one row of camera.c lbl_1_data_50. */
typedef struct M516CamView_s {
    /* 0x00 */ HuVecF center;
    /* 0x0C */ HuVecF rot;              /* x, y rotation; z is the zoom */
} M516_CAMVIEW;

/* --------------------------------------------------------------- actor.c */

/*
 * The collision actor descriptor, 0x40 bytes (fork I proved the size from
 * fn_1_89EC's stack probe). player.c registers four of them through fn_1_8D88
 * and stage.c registers up to 0x43 scenery boxes through fn_1_8E00; actor.c
 * only ever sees the pointers. It holds host pointers -- never size it with a
 * literal.
 *
 * 0x28/0x2C carry two meanings: a character (the unk000[] array) uses them as
 * the two "was landed on / landed on someone" flags that fn_1_815C clears and
 * fn_1_83FC sets, while a box (the unk010[] array) uses them as the +X and +Y
 * edges of its AABB. Hence the union.
 */
typedef struct m516_actor {
    /* 0x00 */ u32 unk00;                 /* bit 0: registered/live */
    /* 0x04 */ u32 unk04;                 /* box kind; 2 = wraps in X */
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;                 /* nonzero: skipped this frame */
    /* 0x10 */ OMOBJ *unk10;              /* owner object, handed to unk14 */
    /* 0x14 */ OMOBJFUNC unk14;           /* post-collision callback */
    /* 0x18 */ HuVecF *unk18;             /* position (owned by the caller) */
    /* 0x1C */ HuVecF *unk1C;             /* velocity (owned by the caller) */
    /* 0x20 */ f32 unk20;                 /* character: height  box: -X edge */
    /* 0x24 */ f32 unk24;                 /* character: half-width  box: +Y edge */
    /* 0x28 */ union { s32 i; f32 f; } unk28; /* character: hit-from-above flag  box: +X edge */
    /* 0x2C */ union { s32 i; f32 f; } unk2C; /* character: hit-from-below flag  box: -Y edge */
    /* 0x30 */ union { s32 i; OMOBJ *o; } unk30; /* character: the actor we collided with (its unk10)
                                                    box: pick-up group id, 0 = not pickable */
    /* 0x34 */ s32 unk34;                 /* claimer's player number (see the aliasing note on M516_PLAYER) */
    /* 0x38 */ s32 unk38;                 /* 1 once claimed */
    /* 0x3C */ OMOBJ *unk3C;              /* the claiming player object; scored by fn_1_800C */
} M516_ACTOR;

/* actor object work (lbl_1_bss_50->data), 0x11C bytes. */
typedef struct m516_actorwork {
    /* 0x000 */ M516_ACTOR *unk000[4];
    /* 0x010 */ M516_ACTOR *unk010[67];
} M516_ACTORWORK;

/* -------------------------------------------------------------- effect.c */

/* One quad effect: Hu3DData[obj->mdlId[0]].hookData -> M516_EFFECT.unk004[8]. */
typedef struct m516Effectdata_s {
    /* 0x00 */ s32 unk00;      /* in use */
    /* 0x04 */ u32 unk04;      /* RGBA8 vertex colour; byte 3 is the alpha that fades */
    /* 0x08 */ float unk08;    /* half-extent of the quad, grows 5.0 per frame */
    /* 0x0C */ HuVecF unk0C;   /* world position */
} M516_EFFECTDATA;             /* 0x18 */

/* Hu3DData[obj->mdlId[0]].hookData, HuMemDirectMallocNum(HEAP_HEAP, 0xC4, HU_MEMNUM_OVL) */
typedef struct m516Effect_s {
    /* 0x000 */ ANIMDATA *unk000;
    /* 0x004 */ M516_EFFECTDATA unk004[8];
} M516_EFFECT;                 /* 0xC4 */

/* A ring registration owned by the caller (player.c work + 0xD0). */
typedef struct m516Ring_s {
    /* 0x00 */ s32 unk00;      /* visible */
    /* 0x04 */ float unk04;    /* radius */
    /* 0x08 */ HuVecF *unk08;  /* position, read every frame */
} M516_RING;                   /* 0x0C */

/* Hu3DData[obj->mdlId[1]].hookData, HuMemDirectMallocNum(HEAP_HEAP, 0x110, HU_MEMNUM_OVL) */
typedef struct m516Ringwork_s {
    /* 0x000 */ M516_RING *unk000[4];
    /* 0x010 */ float unk010[32];   /* sin(i * 11 deg) */
    /* 0x090 */ float unk090[32];   /* cos(i * 11 deg) */
} M516_RINGWORK;               /* 0x110 */

/* -------------------------------------------------------------- player.c */

/*
 * 0x34 bytes: the block at M516_PLAYER+0x9C that fn_1_8D88 (actor.c) registers.
 * actor.c sees it as an M516_ACTOR, whose first 0x34 bytes this reproduces
 * field for field (same widths, same pointer members, so the two views agree
 * on the host as well as on GameCube). The remaining 0xC bytes of the actor
 * record, 0x34..0x40, are the ring at M516_PLAYER+0xD0 -- see the note there.
 */
typedef struct M516Hit_s {
    /* 0x00 */ u32 unk000;                  /* flags; fn_1_28E0 sets bit 0 when the player goes live */
    /* 0x04 */ u32 unk004;
    /* 0x08 */ s32 unk008;                  /* player number */
    /* 0x0C */ u32 unk00C;
    /* 0x10 */ OMOBJ *unk010;               /* the owning player object */
    /* 0x14 */ OMOBJFUNC unk014;            /* fn_1_3BBC */
    /* 0x18 */ HuVecF *unk018;              /* &M516_PLAYER.unk04C (position) */
    /* 0x1C */ HuVecF *unk01C;              /* &M516_PLAYER.unk058 (velocity) */
    /* 0x20 */ float unk020;                /* 0.8 * CharModelHeightGet(charNo); also the probe offset */
    /* 0x24 */ float unk024;                /* 40.0f; the pick-up radius handed to fn_1_89EC */
    /* 0x28 */ s32 unk028;                  /* actor unk28: hit-from-above flag */
    /* 0x2C */ s32 unk02C;                  /* actor unk2C: hit-from-below flag */
    /* 0x30 */ OMOBJ *unk030;               /* actor unk30: who we collided with */
} M516_HIT;

/* player.c: one row of lbl_1_data_B8 (8 rows of 0x0C). */
typedef struct m516Motion_s {
    /* 0x00 */ u16 unk00;       /* index into OMOBJ::mtnId */
    /* 0x04 */ float unk04;     /* shift time, seconds */
    /* 0x08 */ u32 unk08;       /* HU3D_MOTATTR_* */
} M516_MOTION;  /* 0x0C */

/*
 * 0xDC bytes: obj->data of the four player objects (fn_1_2624).
 *
 * ALIASING, deliberate and retail: the actor record registered at +0x9C is
 * 0x40 bytes (M516_HIT is only its first 0x34), so actor +0x34/+0x38/+0x3C are
 * the same words as unk0D0.unk00/unk04/unk08 -- the effect ring registered at
 * +0xD0 with fn_1_796C. fn_1_3110's stomp claim writes the victim's actor
 * +0x34/+0x38/+0x3C and therefore overwrites the victim's ring fields. This is
 * real retail behaviour; it stays inside the allocation on GameCube (0xDC) and
 * on the host (the actor view ends exactly at sizeof(M516_PLAYER)), so it is
 * reproduced, not fixed.
 */
typedef struct M516Player_s {
    /* 0x000 */ s32 unk000;                 /* player number (obj->work[0]) */
    /* 0x004 */ s32 unk004;                 /* GwPlayerConf[no].grp (obj->work[1]) */
    /* 0x008 */ s32 unk008;                 /* slot (obj->work[2]) */
    /* 0x00C */ s32 unk00C;                 /* charNo */
    /* 0x010 */ s32 unk010;                 /* current lbl_1_data_B8 motion, -1 = none */
    /* 0x014 */ u32 unk014;                 /* HuPadBtnDown */
    /* 0x018 */ u32 unk018;                 /* HuPadBtn */
    /* 0x01C */ float unk01C;               /* stick direction, degrees */
    /* 0x020 */ float unk020;               /* stick magnitude, 0..1 */
    /* 0x024 */ s32 unk024;                 /* GwPlayerConf[no].type (COM flag) */
    /* 0x028 */ u32 unk028;                 /* GwPlayerConf[no].dif & 3 (unsigned: fn_1_3D40 tests it with cmplwi) */
    /* 0x02C */ float unk02C;               /* facing angle set by fn_1_43B8 */
    /* 0x030 */ float unk030;
    /* 0x034 */ s32 unk034;
    /* 0x038 */ s32 unk038;                 /* state; fn_1_43B8 forces 12 on a blocked turn */
    /* 0x03C */ s32 unk03C;
    /* 0x040 */ s32 unk040;                 /* mode */
    /* 0x044 */ s32 unk044;                 /* mode timer */
    /* 0x048 */ s32 unk048;                 /* frame counter */
    /* 0x04C */ HuVecF unk04C;              /* position */
    /* 0x058 */ HuVecF unk058;              /* velocity */
    /* 0x064 */ HuVecF unk064;              /* handed to the effect ring at 0xD0 */
    /* 0x070 */ float unk070;               /* facing angle, degrees */
    /* 0x074 */ float unk074;               /* 0.8 * model height */
    /* 0x078 */ float unk078;               /* added to unk058.x every frame (moving-platform carry) */
    /* 0x07C */ s32 unk07C;
    /* 0x080 */ s32 unk080;
    /* 0x084 */ s32 unk084;                 /* 0 while on the ground */
    /* 0x088 */ s32 unk088;
    /* 0x08C */ s32 unk08C;
    /* 0x090 */ s32 unk090;
    /* 0x094 */ float unk094;               /* speed scale, 1.0 */
    /* 0x098 */ float unk098;               /* 1.0 */
    /* 0x09C */ M516_HIT unk09C;            /* registered with actor.c fn_1_8D88 as an M516_ACTOR */
    /* 0x0D0 */ M516_RING unk0D0;           /* registered with effect.c fn_1_796C; aliases actor +0x34 */
} M516_PLAYER;

/* --------------------------------------------------------------- stage.c */

/*
 * 0x8C. The stage work's repeated element: one of the 66 collectibles
 * (M516_STAGE.unkA8), the 12 splash/ripple slots (unk24F0), the 4 scrolling
 * props (unk2B80), the 3 swimmers (unk2DB0) or the 3 drifters (unk2F54).
 * unk4C is the 0x40-byte actor descriptor handed to fn_1_8E00 (actor.c).
 */
typedef struct M516StageSub_s {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ HuVecF unk14;
    /* 0x20 */ HuVecF unk20;
    /* 0x2C */ HuVecF unk2C;
    /* 0x38 */ float unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 unk40[0x4C - 0x40];
    /* 0x4C */ M516_ACTOR unk4C;
} M516_STAGESUB;

/* 0x24. One row of stage.c lbl_1_data_174. */
typedef struct M516StageProp_s {
    /* 0x00 */ u32 unk00;               /* data number */
    /* 0x04 */ u32 unk04;               /* Hu3D layer */
    /* 0x08 */ float unk08;             /* rot.y step per frame */
    /* 0x0C */ HuVecF unk0C;            /* pos at t = 0 */
    /* 0x18 */ HuVecF unk18;            /* pos at t = 1 */
} M516_STAGEPROP;

/* 0x3100, the stage object's data (lbl_1_bss_38->data). Pointer-bearing. */
typedef struct M516Stage_s {
    /* 0x0000 */ HuVecF unk00;
    /* 0x000C */ M516_ACTOR unk0C;
    /* 0x004C */ HSFOBJECT *unk4C[6];   /* "block_LA".."block_RC" objects */
    /* 0x0064 */ float unk64[3];
    /* 0x0070 */ s32 unk70;
    /* 0x0074 */ s32 unk74;
    /* 0x0078 */ float unk78;
    /* 0x007C */ float unk7C;
    /* 0x0080 */ float unk80[3];
    /* 0x008C */ float unk8C[3];
    /* 0x0098 */ float unk98[3];
    /* 0x00A4 */ float unkA4;
    /* 0x00A8 */ M516_STAGESUB unkA8[66];
    /* 0x24C0 */ s32 unk24C0[12];
    /* 0x24F0 */ M516_STAGESUB unk24F0[12];
    /* 0x2B80 */ M516_STAGESUB unk2B80[4];
    /* 0x2DB0 */ M516_STAGESUB unk2DB0[3];
    /* 0x2F54 */ M516_STAGESUB unk2F54[3];
    /* 0x30F8 */ float unk30F8;
    /* 0x30FC */ float unk30FC;
} M516_STAGE;

/* --------------------------------------------------------------- score.c */

/* score.c: one row of lbl_1_data_2C0 (4 rows of 0x08), screen space. */
typedef struct m516ScorePos_s {
    /* 0x00 */ float x;
    /* 0x04 */ float y;
} M516_SCOREPOS;  /* 0x08 */

/* score.c: one player's score readout. */
typedef struct m516ScorePl_s {
    /* 0x00 */ s32 unk00;       /* score value */
    /* 0x04 */ HUSPRGRPID unk04;/* MgScoreWin group */
    /* 0x06 */ HUSPRGRPID unk06;/* icon sprite group (3 members) */
    /* 0x08 */ MGSCORE *unk08;
} M516_SCOREPL;  /* 0x0C */

/* score.c: OMOBJ::data of the object fn_1_79F8 adds (lbl_1_bss_48). */
typedef struct m516Score_s {
    /* 0x00 */ s32 unk00;       /* fade state machine */
    /* 0x04 */ float unk04;     /* fade level 0..1 */
    /* 0x08 */ M516_SCOREPL unk08[4];
} M516_SCORE;   /* 0x38 */

/* --- m516.c --- */
void ObjectSetup(void);
void fn_1_330(OMOBJ *obj);
void fn_1_410(OMOBJ *obj);
void fn_1_524(OMOBJ *obj);
void fn_1_654(OMOBJ *obj);
void fn_1_970(OMOBJ *obj);
void fn_1_CA8(OMOBJ *obj);
void fn_1_EF8(OMOBJ *obj);
void fn_1_11EC(OMOBJ *obj);
void fn_1_14B0(OMOBJ *obj);
u32 fn_1_1820(void);
u32 fn_1_1838(void);
u32 fn_1_1850(void);
u32 fn_1_1868(void);
s32 fn_1_1880(void);
void fn_1_1898(s32 arg0);
s32 fn_1_18B0(s32 no);
void fn_1_18E0(s32 no);
void fn_1_1910(s32 no);
BOOL fn_1_1940(void);
s32 fn_1_1978(void);
void fn_1_19E0(s32 no, s32 arg1, s32 charNo);
void fn_1_1A20(s32 no);   /* the argument is passed and ignored */
s32 fn_1_1A9C(float x);
s32 fn_1_1AF8(HuVecF *pos, s32 camId);   /* camId is passed and ignored */
s32 fn_1_1B8C(s32 seNo, HuVecF *pos);
void fn_1_1C60(s32 seId, HuVecF *pos);
float fn_1_1D34(float cur, float target, float rate);
float fn_1_1E50(float from, float to);

/* --- camera.c --- */
OMOBJFUNC fn_1_1F04(OMOBJMAN *objman);
void fn_1_1F90(OMOBJ *obj);
OMOBJFUNC fn_1_2108(OMOBJMAN *objman, OMOBJ *obj);
void fn_1_21C4(OMOBJ *obj);
void fn_1_23EC(s32 from, s32 to, float t);

/* --- player.c --- */
void fn_1_254C(OMOBJMAN *objman);
void fn_1_2600(void);
void fn_1_2624(OMOBJ *obj);
void fn_1_28E0(OMOBJ *obj);
void fn_1_2C68(OMOBJ *obj);
void fn_1_2E7C(OMOBJ *obj);
void fn_1_2F08(OMOBJ *obj);
void fn_1_3110(OMOBJ *obj);
void fn_1_3734(OMOBJ *obj);
void fn_1_3BBC(OMOBJ *obj);
void fn_1_3D40(OMOBJ *obj);
M516_ACTOR *fn_1_4298(OMOBJ *obj, float dx, float dy);
M516_ACTOR *fn_1_42E8(OMOBJ *obj, float dx, float dy, float range);
void fn_1_43B8(OMOBJ *obj, float dir, float b1);
void fn_1_4558(OMOBJ *obj, u32 motNo);
BOOL fn_1_4650(OMOBJ *obj);
BOOL fn_1_46BC(OMOBJ *obj);
BOOL fn_1_471C(OMOBJ *obj, u32 motNo);
s32 fn_1_485C(OMOBJ *obj);
BOOL fn_1_4878(OMOBJ *obj, HuVecF *pos, float *out);

/* --- stage.c --- */
void fn_1_48CC(OMOBJMAN *objman);
void fn_1_495C(void);
void fn_1_4960(OMOBJ *obj);
void fn_1_4CF8(OMOBJ *obj);
void fn_1_4DB4(OMOBJ *obj);
void fn_1_51C4(OMOBJ *obj);
void fn_1_59EC(OMOBJ *obj);
void fn_1_5AC4(OMOBJ *obj);
void fn_1_5B6C(HuVecF *pos);
void fn_1_5C70(OMOBJ *obj);
void fn_1_5D2C(OMOBJ *obj);
void fn_1_5EDC(HuVecF *pos);
void fn_1_5F6C(OMOBJ *obj);
void fn_1_601C(OMOBJ *obj);
void fn_1_6154(OMOBJ *obj);
void fn_1_6234(OMOBJ *obj);
void fn_1_6814(HuVecF *pos);
void fn_1_6870(OMOBJ *obj);
void fn_1_69A4(OMOBJ *obj);
void fn_1_6C54(OMOBJ *obj);
void fn_1_6CF4(OMOBJ *obj);
s32 fn_1_6D78(void);
BOOL fn_1_6DEC(s32 no, HuVecF *pos, float *rotY);
float fn_1_6E94(float x);

/* --- effect.c --- */
void fn_1_6F24(OMOBJMAN *objman);
void fn_1_6F80(void);
void fn_1_6F84(OMOBJ *obj);
void fn_1_6FC8(OMOBJ *obj);
void fn_1_6FF0(OMOBJ *obj);
void fn_1_70AC(OMOBJ *obj);
void fn_1_7164(HU3DMODEL *model, Mtx *cameraMtx);
void fn_1_74B0(OMOBJ *obj);
void fn_1_75E8(HU3DMODEL *model, Mtx *cameraMtx);
void fn_1_78B8(HuVecF *pos, float size);
void fn_1_796C(M516_RING *ring);

/* --- score.c --- */
void fn_1_79F8(OMOBJMAN *objman);
void fn_1_7A80(void);
void fn_1_7A84(OMOBJ *obj);
void fn_1_7AC0(OMOBJ *obj);
void fn_1_7AE8(OMOBJ *obj);
void fn_1_7E04(OMOBJ *obj);
void fn_1_800C(OMOBJ *obj, s32 add);
s32 fn_1_8088(s32 no);

/* --- actor.c --- */
void fn_1_80C0(OMOBJMAN *objman);
void fn_1_8148(void);
void fn_1_814C(OMOBJ *obj);
void fn_1_815C(OMOBJ *obj);
s32 fn_1_8314(M516_ACTOR *a, M516_ACTOR *b);
s32 fn_1_83FC(M516_ACTOR *a, M516_ACTOR *b, f32 dx);
s32 fn_1_86E8(M516_ACTOR *a, M516_ACTOR *b);
s32 fn_1_87DC(M516_ACTOR *a, M516_ACTOR *b, f32 dx);
s32 fn_1_89EC(HuVecF *pos, f32 width);
void fn_1_8BF0(HuVecF *pos, HuVecF *out);
s32 fn_1_8D88(M516_ACTOR *actor);
s32 fn_1_8E00(M516_ACTOR *actor);
M516_ACTOR *fn_1_8E78(s32 idx);
void fn_1_8EE8(s32 idx);

#endif
