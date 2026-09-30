#ifndef M518DLL_H
#define M518DLL_H

/*
 * m518Dll (overlay #32): types and prototypes shared by its one translation
 * units (m518).
 *
 * Offsets are GameCube ones from build/mp5-asm/m518dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

/* Retail m518 calls Hu3DMotionMaxTimeGet with no prototype in scope (fork E:
 * fn_1_BC28, fn_1_BFAC): the float result in f1 is dropped and frandmod()
 * gets the int in r3. On GC the hu3d.h prototype is renamed away and a K&R
 * int declaration stands in (below); the host keeps the float prototype, so
 * the same source passes the real motion length there. */
#define Hu3DMotionMaxTimeGet Hu3DMotionMaxTimeGet_m518_prototype_hidden
#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/hu3d.h"

#include "game/process.h"
#include "game/animdata.h"
#include "game/charman.h"

#undef Hu3DMotionMaxTimeGet
s32 Hu3DMotionMaxTimeGet();

/*
 * Record types (fork A). Every .bss pointer array holds heap records that a
 * creator allocates with HuMemDirectMallocNum and hands to a child process
 * (HUPROCESS.property = record, read back through HuPrcCurrentGet()->property).
 * Sizes are GameCube ones; pointers widen on the host, so never size or index
 * these with a GC constant.
 */

/* {s8 x, s8 y} grid cell, passed BY VALUE (fn_1_3554, fn_1_D958, lbl_1_rodata_490) */
typedef struct m518_pos {
    /* 0x00 */ s8 x;
    /* 0x01 */ s8 y;
} M518_POS; /* size 0x2 (GC) */

/* fn_1_DC14: s32 ring/queue (M518_PLAYER unk0D8/unk0DC[]) */
typedef struct m518_queue {
    /* 0x00 */ s32 *unk000; /* HuMemDirectMallocNum(num * 4): s32 entries (fn_1_DC84 stwx, fn_1_DCBC lwzx) */
    /* 0x04 */ s32 unk004; /* capacity (fn_1_DC14 arg) */
    /* 0x08 */ s32 unk008; /* write index */
    /* 0x0C */ s32 unk00C; /* read index */
} M518_QUEUE; /* size 0x10 (GC) */

/* fn_1_2D24: player (lbl_1_bss_4E0[4]); process fn_1_31F0, modes lbl_1_data_20[] */
typedef struct m518_player {
    /* 0x00 */ s16 unk000; /* mode: lbl_1_data_20[unk000] */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* fn_1_2D24 arg1 (slot) */
    /* 0x06 */ s16 unk006; /* fn_1_2D24 arg0 = playerNo (GwPlayer index, 1EFC 0x2424) */
    /* 0x08 */ s16 unk008; /* fn_1_2D24 arg2 (0 solo / 1 team) */
    /* 0x0A */ s16 unk00A; /* GwPlayerConf[].charNo */
    /* 0x0C */ s16 unk00C[2]; /* models (lbl_1_rodata_5BC/624), sthx base 0xC, loop 2 (fn_1_2D24) */
    /* 0x10 */ u8 pad010[2];
    /* 0x12 */ s16 unk012;
    /* 0x14 */ s32 unk014; /* direction 0..3 (4B80 lwz/cmpwi, *0xC into rodata_6E8) */
    /* 0x18 */ s16 unk018;
    /* 0x1A */ s16 unk01A;
    /* 0x1C */ s16 unk01C;
    /* 0x1E */ u8 pad01E[2];
    /* 0x20 */ HuVecF unk020; /* pos */
    /* 0x2C */ HuVecF unk02C;
    /* 0x38 */ HuVecF unk038; /* scale (fn_1_3440), init 1.0f */
    /* 0x44 */ u8 pad044[0x18];
    /* 0x5C */ HuVecF unk05C;
    /* 0x68 */ HuVecF unk068;
    /* 0x74 */ HuVecF unk074;
    /* 0x80 */ HuVecF unk080;
    /* 0x8C */ HuVecF unk08C; /* init 1.0f */
    /* 0x98 */ float unk098; /* TPLvl (fn_1_34D8 stfs) */
    /* 0x9C */ M518_POS unk09C; /* grid cell (s8 x, s8 y) */
    /* 0x9E */ M518_POS unk09E;
    /* 0xA0 */ s16 unk0A0;
    /* 0xA2 */ u8 pad0A2[2];
    /* 0xA4 */ s32 unk0A4; /* flag */
    /* 0xA8 */ s16 unk0A8; /* fn_1_88B4 arg */
    /* 0xAA */ s16 unk0AA; /* fn_1_88B4 arg */
    /* 0xAC */ s16 unk0AC;
    /* 0xAE */ u8 pad0AE[2];
    /* 0xB0 */ s32 unk0B0; /* flag */
    /* 0xB4 */ s32 unk0B4; /* GwPlayerConf[].type (COM) */
    /* 0xB8 */ s32 unk0B8;
    /* 0xBC */ s32 unk0BC;
    /* 0xC0 */ s16 unk0C0; /* GwPlayerConf[].dif */
    /* 0xC2 */ s16 unk0C2;
    /* 0xC4 */ s16 unk0C4;
    /* 0xC6 */ s16 unk0C6;
    /* 0xC8 */ s16 unk0C8;
    /* 0xCA */ s16 unk0CA;
    /* 0xCC */ M518_POS unk0CC;
    /* 0xCE */ s16 unk0CE; /* GwPlayerConf[].padNo */
    /* 0xD0 */ s16 unk0D0;
    /* 0xD2 */ s16 unk0D2;
    /* 0xD4 */ s16 unk0D4;
    /* 0xD6 */ u8 pad0D6[2];
    /* 0xD8 */ M518_QUEUE *unk0D8; /* fn_1_DC14(40) */
    /* 0xDC */ M518_QUEUE *unk0DC[4]; /* fn_1_DC14(40) x4 */
    /* 0xEC */ HUPROCESS *unk0EC; /* child process fn_1_31F0 */
} M518_PLAYER; /* size 0xF0 (GC) */

/* fn_1_A9A4: character model (lbl_1_bss_39C[4]); process fn_1_AB3C, modes lbl_1_data_64[] */
typedef struct m518_char {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* playerNo */
    /* 0x06 */ s16 unk006; /* CharModelCreate */
    /* 0x08 */ s16 unk008[7]; /* CharMotionCreate x7 */
    /* 0x16 */ u8 pad016[2];
    /* 0x18 */ HuVecF unk018; /* pos (fn_1_BB00) */
    /* 0x24 */ HuVecF unk024; /* rot (fn_1_BB60) */
    /* 0x30 */ HuVecF unk030; /* target (fn_1_AB7C) */
    /* 0x3C */ s32 unk03C; /* GwPlayerConf[].type */
    /* 0x40 */ s16 unk040; /* GwPlayerConf[].dif */
    /* 0x42 */ s16 unk042; /* GwPlayerConf[].charNo (MgSeqWinnerSet, fn_1_1E28) */
    /* 0x44 */ s16 unk044; /* fn_1_AB7C arg */
    /* 0x46 */ s16 unk046; /* fn_1_AB7C arg */
    /* 0x48 */ HUPROCESS *unk048; /* child process fn_1_AB3C */
} M518_CHAR; /* size 0x4C (GC) */

/* fn_1_C9F4: floor tile, 12 x 12 (lbl_1_bss_150[144]); process fn_1_CB9C, modes lbl_1_data_80[] */
typedef struct m518_tile {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* index */
    /* 0x06 */ s16 unk006; /* type (lbl_1_rodata_6A) */
    /* 0x08 */ s16 unk008; /* Hu3DModelLink(lbl_1_bss_4[type]) */
    /* 0x0A */ s16 unk00A;
    /* 0x0C */ s16 unk00C;
    /* 0x0E */ s16 unk00E;
    /* 0x10 */ M518_POS unk010; /* fn_1_D958 */
    /* 0x12 */ u8 pad012[2];
    /* 0x14 */ HuVecF unk014; /* pos (fn_1_DA7C) */
    /* 0x20 */ HuVecF unk020; /* rot (fn_1_DADC) */
    /* 0x2C */ float unk02C;
    /* 0x30 */ HUPROCESS *unk030; /* child process fn_1_CB9C */
} M518_TILE; /* size 0x34 (GC) */

/* fn_1_BC28: prop, 3 models (lbl_1_bss_390[3]); process fn_1_BD88, modes lbl_1_data_74[] */
typedef struct m518_prop {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004[3]; /* models (lbl_1_rodata_16C0) */
    /* 0x0A */ u8 pad00A[2];
    /* 0x0C */ HuVecF unk00C; /* pos (fn_1_BDC8) */
    /* 0x18 */ HUPROCESS *unk018; /* child process fn_1_BD88 */
} M518_PROP; /* size 0x1C (GC) */

/* fn_1_BFAC: spectator (lbl_1_bss_3AC[76]); process fn_1_C224, modes lbl_1_data_78[] */
typedef struct m518_crowd {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* fn_1_BFAC arg0 (index) */
    /* 0x06 */ s16 unk006; /* fn_1_BFAC arg1 */
    /* 0x08 */ s16 unk008[1]; /* model (loop count 1) */
    /* 0x0A */ s16 unk00A; /* Hu3DJointMotion */
    /* 0x0C */ HuVecF unk00C; /* pos (fn_1_C298) */
    /* 0x18 */ HuVecF unk018; /* rot (fn_1_C2F8) */
    /* 0x24 */ HuVecF unk024; /* fn_1_C454 */
    /* 0x30 */ HuVecF unk030; /* scale (fn_1_C358) */
    /* 0x3C */ s16 unk03C; /* fn_1_C454 */
    /* 0x3E */ s16 unk03E; /* fn_1_C454 */
    /* 0x40 */ HUPROCESS *unk040; /* child process fn_1_C224 */
} M518_CROWD; /* size 0x44 (GC) */

/* fn_1_9860: field, one (lbl_1_bss_4DC); process fn_1_9BB0, modes lbl_1_data_60[] */
typedef struct m518_field {
    /* 0x000 */ s16 unk000; /* mode */
    /* 0x002 */ s16 unk002;
    /* 0x004 */ s16 unk004[20]; /* models (lbl_1_rodata_1450) */
    /* 0x02C */ u8 pad02C[0x24];
    /* 0x050 */ u16 unk050[12 * 12]; /* [x + y * 12]: lhzx/sthx at ((y * 12 + x) << 1) + 0x050, fn_1_9C4C/9CBC/9D98/A200/A268 (fork E) */
    /* 0x170 */ u16 unk170[12 * 12]; /* [x + y * 12]: lhzx/sthx at ((y * 12 + x) << 1) + 0x170, fn_1_9C4C/9CBC/9D98/A200/A268 (fork E) */
    /* 0x290 */ u16 unk290[12 * 12]; /* [x + y * 12]: lhzx/sthx at ((y * 12 + x) << 1) + 0x290, fn_1_9C4C/9CBC/9D98/A200/A268 (fork E) */
    /* 0x3B0 */ s16 unk3B0;
    /* 0x3B2 */ s16 unk3B2;
    /* 0x3B4 */ HUPROCESS *unk3B4; /* child process fn_1_9BB0 */
} M518_FIELD; /* size 0x3B8 (GC) */

/* fn_1_DD40: smoke particle (lbl_1_bss_50[64]); m540 M540_SMOKE layout */
typedef struct m518_smoke {
    /* 0x00 */ s32 unk000;
    /* 0x04 */ s16 unk004; /* Hu3DParticleCreate */
    /* 0x08 */ ANIMDATA *unk008;
    /* 0x0C */ HuVecF unk00C;
    /* 0x18 */ float unk018;
} M518_SMOKE; /* size 0x1C (GC) */

/* lbl_1_rodata_498: {pos, rot} per character (fn_1_728) */
typedef struct m518_posrot {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
} M518_POSROT; /* size 0x18 (GC) */

typedef void (*M518_PLAYERFUNC)(M518_PLAYER *work);
typedef void (*M518_CHARFUNC)(M518_CHAR *work);
typedef void (*M518_TILEFUNC)(M518_TILE *work);
typedef void (*M518_PROPFUNC)(M518_PROP *work);
typedef void (*M518_CROWDFUNC)(M518_CROWD *work);
typedef void (*M518_FIELDFUNC)(M518_FIELD *work);
typedef void (*M518_SMOKEFUNC)(M518_SMOKE *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);

/* ---- fork E ---- */
/* Every process-driven object below starts with this pair: fn_1_AB3C/BD88/
 * C224/CB9C dispatch on unk000 each frame, and M518_OBJWAIT ends the running
 * state function as soon as unk000 changes (unk002 = last seen unk000). */
typedef struct m518_objhdr {
    /* 0x00 */ s16 unk000; /* mode (state-table index) */
    /* 0x02 */ s16 unk002; /* mode seen last frame */
} M518_OBJHDR; /* size 0x4 (GC) */

#define M518_OBJCUR ((M518_OBJHDR *)HuPrcCurrentGet()->property)

/* Sleep n frames; return from the calling state function when the mode
 * changes (ACAC, B60C, ... C480, CEA0 ...). */
#define M518_OBJWAIT(n)                                       \
    {                                                         \
        s16 _mode;                                            \
        s16 _prev;                                            \
        s32 _waitMax = (n);                                   \
        s32 _waitCnt;                                         \
        for (_waitCnt = 0; _waitCnt < _waitMax; _waitCnt++) { \
            HuPrcVSleep();                                    \
            _mode = M518_OBJCUR->unk000;                      \
            _prev = M518_OBJCUR->unk002;                      \
            M518_OBJCUR->unk002 = _mode;                      \
            if (_mode != _prev) {                             \
                return;                                       \
            }                                                 \
        }                                                     \
    }

/* --- m518.c --- (fork A: pinned from call sites and callee argument use; see OUT.txt) */
void ObjectSetup(void);
void fn_1_184(void);
void fn_1_1F4(s16 mode, s16 frameNo);
void fn_1_728(s16 mode, s16 frameNo);
void fn_1_1C3C(void);
void fn_1_1CD8(s16 mode, s16 frameNo);
void fn_1_1D54(s16 mode, s16 frameNo);
void fn_1_1E28(s16 mode, s16 frameNo);
void fn_1_1EFC(s16 mode, s16 frameNo);
void fn_1_2C6C(s16 mode, s16 frameNo);
void fn_1_2CFC(void);
M518_PLAYER *fn_1_2D24(s16 playerNo, s16 slot, s16 team);
void fn_1_31F0(void);
void fn_1_3230(M518_PLAYER *player, HuVecF pos);
void fn_1_32C8(M518_PLAYER *player, HuVecF rot);
void fn_1_3440(M518_PLAYER *player, HuVecF scale);
void fn_1_34D8(M518_PLAYER *player, float tpLvl);
void fn_1_3554(M518_PLAYER *player, M518_POS cell);
void fn_1_37D0(M518_PLAYER *player, M518_POS cell, u16 flag);
void fn_1_3904(M518_PLAYER *player);
M518_POS fn_1_4674(M518_PLAYER *player);
void fn_1_468C(M518_PLAYER *player);
void fn_1_4698(M518_PLAYER *player);
void fn_1_4728(M518_PLAYER *player);
void fn_1_4734(float *a, float *b);
void fn_1_4760(HuVecF rot, HuVecF *axis); /* fork C: r3 = by-value copy of player->unk080 (0x5294..0x52AC); fmod on 0/4/8(r3) */
void fn_1_4B80(M518_PLAYER *player);
void fn_1_6C0C(M518_PLAYER *player);
void fn_1_6CFC(M518_PLAYER *player);
void fn_1_6D84(M518_PLAYER *player);
void fn_1_6E08(M518_PLAYER *player);
void fn_1_7908(M518_PLAYER *player);
void fn_1_83E8(M518_PLAYER *player, s16 arg1, s16 arg2);
void fn_1_83FC(M518_PLAYER *player);
void fn_1_88B4(M518_PLAYER *player, s16 arg1, s16 arg2);
void fn_1_88C8(M518_PLAYER *player);
void fn_1_8E20(M518_PLAYER *player);
void fn_1_8E2C(M518_PLAYER *player);
void fn_1_8FA8(M518_PLAYER *player);
void fn_1_9014(M518_PLAYER *player);
s16 fn_1_9080(M518_PLAYER *player, M518_POS cell); /* fork D: returns the summed unk290 weight along the chosen path (mr r3,r28; extsh) */
s32 fn_1_9258(M518_PLAYER *player, M518_QUEUE *queue, M518_POS cell, s16 arg3, s32 arg4, s16 arg5); /* fork D: cell by value (callers copy to a temp), arg5 s16 (extsh r30,r3 after each recursion), s32 result (9080 stwx r3; "extsh r3,r30; addi r3,r3,1" return) */
M518_FIELD *fn_1_9860(void);
void fn_1_9BB0(void);
void fn_1_9BF0(M518_FIELD *field);
void fn_1_9C4C(M518_FIELD *field, M518_POS cell, u16 value);
u16 fn_1_9CBC(M518_FIELD *field, M518_POS cell);
void fn_1_9D30(M518_FIELD *field);
void fn_1_9D98(M518_FIELD *field);
void fn_1_9E04(M518_FIELD *field);
void fn_1_9E70(M518_FIELD *field);
void fn_1_9ECC(M518_FIELD *field);
void fn_1_9ED8(M518_FIELD *field);
void fn_1_A200(M518_FIELD *field, M518_POS cell, u16 value);
u16 fn_1_A268(M518_FIELD *field, M518_POS cell);
void fn_1_A2D8(M518_FIELD *field, M518_POS cell, s16 arg2);
void fn_1_A480(M518_FIELD *field, M518_POS cell, s16 arg2);
M518_CHAR *fn_1_A9A4(s16 playerNo);
void fn_1_AB3C(void);
void fn_1_AB7C(M518_CHAR *chr, HuVecF target, s16 arg2, s16 arg3);
float fn_1_ABA8(float start, float end, float t);
void fn_1_ACAC(M518_CHAR *chr);
void fn_1_B600(M518_CHAR *chr);
void fn_1_B60C(M518_CHAR *chr);
void fn_1_B6AC(M518_CHAR *chr);
void fn_1_B6B8(M518_CHAR *chr);
void fn_1_B7A0(M518_CHAR *chr);
void fn_1_B7AC(M518_CHAR *chr);
void fn_1_BB00(M518_CHAR *chr, HuVecF pos);
void fn_1_BB60(M518_CHAR *chr, HuVecF rot);
void fn_1_BBC0(M518_CHAR *chr);
void fn_1_BBF4(M518_CHAR *chr);
M518_PROP *fn_1_BC28(void);
void fn_1_BD88(void);
void fn_1_BDC8(M518_PROP *prop, HuVecF pos);
void fn_1_BE60(M518_PROP *prop);
void fn_1_BE6C(M518_PROP *prop);
void fn_1_BEFC(M518_PROP *prop);
void fn_1_BF54(M518_PROP *prop);
M518_CROWD *fn_1_BFAC(s16 index, s16 type);
void fn_1_C224(void);
void fn_1_C264(M518_CROWD *crowd);
void fn_1_C298(M518_CROWD *crowd, HuVecF pos);
void fn_1_C2F8(M518_CROWD *crowd, HuVecF rot);
void fn_1_C358(M518_CROWD *crowd, HuVecF scale);
void fn_1_C3B8(M518_CROWD *crowd);
void fn_1_C3C4(M518_CROWD *crowd);
void fn_1_C454(M518_CROWD *crowd, HuVecF target, s16 arg2, s16 arg3);
void fn_1_C480(M518_CROWD *crowd);
M518_TILE *fn_1_C9F4(s16 index, s16 type);
void fn_1_CB9C(void);
void fn_1_CBDC(M518_TILE *tile);
void fn_1_CBE8(M518_TILE *tile);
void fn_1_CCC0(M518_TILE *tile, s16 arg1, s16 arg2);
void fn_1_CCD4(M518_TILE *tile);
void fn_1_CE54(M518_TILE *tile, float height, s16 frames, s16 delay, s16 seType);
void fn_1_CE78(M518_TILE *tile, float arg3, s16 arg1, s16 arg2); /* fork D: both callers (0x8568, 0x8BF8) evaluate the float (lfs f1) before r4/r5, as for fn_1_CE54 */
void fn_1_CEA0(M518_TILE *tile);
void fn_1_D204(M518_TILE *tile, s16 arg1, s16 arg2);
void fn_1_D218(M518_TILE *tile);
void fn_1_D578(M518_TILE *tile, s16 arg1, s16 arg2);
void fn_1_D58C(M518_TILE *tile);
void fn_1_D958(M518_TILE *tile, M518_POS cell);
void fn_1_DA7C(M518_TILE *tile, HuVecF pos);
void fn_1_DADC(M518_TILE *tile, HuVecF rot);
M518_QUEUE *fn_1_DC14(s32 num);
s32 fn_1_DC84(M518_QUEUE *queue, s32 value);
s32 fn_1_DCBC(M518_QUEUE *queue, s32 *value);
void fn_1_DCF8(M518_QUEUE *queue);
s32 fn_1_DD0C(M518_QUEUE *queue);
M518_SMOKE *fn_1_DD40(void);
void fn_1_DE2C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_DE8C(M518_SMOKE *smoke);
void fn_1_DEF0(M518_SMOKE *smoke, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_DEF4(M518_SMOKE *smoke);
void fn_1_E2A0(M518_SMOKE *smoke, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
s32 fn_1_E508(HuVecF pos, float size);
s16 fn_1_E5BC(HuVecF pos);
s16 fn_1_E6B8(HuVecF pos);
s32 fn_1_E7B4(s32 seNo, HuVecF pos);

#endif
