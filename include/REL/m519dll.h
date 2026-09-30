#ifndef M519DLL_H
#define M519DLL_H

/*
 * m519dll (overlay #33): types and prototypes shared by its one translation
 * units (m519).
 *
 * Offsets are GameCube ones from build/mp5-asm/m519dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

/* Retail m519 calls frand/frandmod with no prototype in scope (fork B:
 * fn_1_4E18 0x4F30 passes a float in f1 to frandmod, and every frand()/
 * frandmod() result is used as a signed int: srawi/extsh, 0x4F64, 0x5028,
 * 0x51E8). On GC the frand.h prototypes are renamed away and K&R int
 * declarations stand in; the host keeps the real prototypes. */
#define frand frand_m519_prototype_hidden
#define frandmod frandmod_m519_prototype_hidden
#include "game/frand.h"
#undef frand
#undef frandmod
s32 frand();
s32 frandmod();
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

/*
 * Record types (fork A). Every creator allocates its record with
 * HuMemDirectMallocNum(HEAP_HEAP, sizeof(...), HU_MEMNUM_OVL) and hands it to a
 * child process (HUPROCESS.property = record, read back through
 * HuPrcCurrentGet()->property). Sizes are GameCube ones; pointers widen on the
 * host, so never size or index these with a GC constant.
 */

/* Every process-driven record starts with this pair: the process function
 * dispatches on unk000 each frame, and M519_OBJWAIT ends the running state
 * function as soon as unk000 changes (unk002 = last seen unk000). m518 pattern. */
typedef struct m519_objhdr {
    /* 0x00 */ s16 unk000; /* mode (state-table index) */
    /* 0x02 */ s16 unk002; /* mode seen last frame */
} M519_OBJHDR; /* size 0x4 (GC) */

#define M519_OBJCUR ((M519_OBJHDR *)HuPrcCurrentGet()->property)

/* Sleep n frames; return from the calling state function when the mode
 * changes (fn_1_26A0 = m518 fn_1_4698 with n = 1). */
#define M519_OBJWAIT(n)                                       \
    {                                                         \
        s16 _mode;                                            \
        s16 _prev;                                            \
        s32 _waitMax = (n);                                   \
        s32 _waitCnt;                                         \
        for (_waitCnt = 0; _waitCnt < _waitMax; _waitCnt++) { \
            HuPrcVSleep();                                    \
            _mode = M519_OBJCUR->unk000;                      \
            _prev = M519_OBJCUR->unk002;                      \
            M519_OBJCUR->unk002 = _mode;                      \
            if (_mode != _prev) {                             \
                return;                                       \
            }                                                 \
        }                                                     \
    }

/* fn_1_C058: breakable block (fork D: M519_BLOCK), one per slot of lbl_1_rodata_568 (M519_STAGE unk014[12]);
 * process fn_1_C248, modes lbl_1_data_64[] */
typedef struct m519_stageobj {
    /* 0x00 */ s16 unk000; /* mode: 0 idle, 1 rise (C570), 2 break (C798), 3 stand (C470); 1 and 3 collide (fn_1_9700) */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* type (fn_1_C058 arg, 0..1) */
    /* 0x06 */ s16 unk006[3]; /* models (lbl_1_rodata_ED0[stage][type]) */
    /* 0x0C */ s16 unk00C; /* hit points: init 1; lbl_1_rodata_F1C[type] (fn_1_C544) */
    /* 0x0E */ s16 unk00E; /* serial of the last item that hit (M519_ITEM unk00C), init -1 */
    /* 0x10 */ s16 unk010; /* lbl_1_bss_F8[] index of the last thrower, init -1 */
    /* 0x12 */ u8 pad012[2];
    /* 0x14 */ HuVecF unk014; /* pos (fn_1_C288 / C30C) */
    /* 0x20 */ HuVecF unk020; /* rot (fn_1_C328 / C3AC) */
    /* 0x2C */ float unk02C; /* radius: (float)lbl_1_rodata_F18[type] (fn_1_9700) */
    /* 0x30 */ s32 unk030; /* respawn flag (fn_1_C788 arg) */
    /* 0x34 */ HUPROCESS *unk034; /* child process fn_1_C248 */
} M519_STAGEOBJ; /* size 0x38 (GC) */

/* fn_1_2298: stage / field (fork D: M519_FIELD), one (lbl_1_bss_178); process fn_1_2654, modes lbl_1_data_1C[] */
typedef struct m519_stage {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004[7]; /* models (lbl_1_rodata_508[stage], -1 = none) */
    /* 0x12 */ u8 pad012[2];
    /* 0x14 */ M519_STAGEOBJ *unk014[12]; /* fn_1_C058 (NULL where lbl_1_rodata_568 type == 2) */
    /* 0x44 */ HUPROCESS *unk044; /* child process fn_1_2654 */
} M519_STAGE; /* size 0x48 (GC) */

/* fn_1_CC44: particle burst (fork D: M519_PART) (M519_PLAYER unk0B4/unk0B8); particle hook fn_1_CCF4,
 * modes lbl_1_data_74[] */
typedef struct m519_effect {
    /* 0x00 */ s16 unk000; /* Hu3DParticleCreate */
    /* 0x02 */ u8 pad002[2];
    /* 0x04 */ HuVecF unk004; /* emit pos (fn_1_CD54 / CD70, read by CFE8) */
    /* 0x10 */ ANIMDATA *unk010; /* HuSprAnimRead */
} M519_EFFECT; /* size 0x14 (GC) */

/* fn_1_297C: player (lbl_1_bss_F8[4]); process fn_1_2F54, modes lbl_1_data_20[unk004][unk000] */
typedef struct m519_player {
    /* 0x00 */ s16 unk000; /* mode: lbl_1_data_20[unk004 * 5 + unk000] */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* type: 0 solo, 1 team (fn_1_297C arg0) */
    /* 0x06 */ s16 unk006; /* slot 0..3 (fn_1_297C arg1): lbl_1_bss_108[] / lbl_1_bss_20[] / camera bit */
    /* 0x08 */ s16 unk008; /* lbl_1_bss_E8[] index (fn_1_3518) */
    /* 0x0A */ s16 unk00A[9]; /* models (lbl_1_rodata_958[type], -1 = none) */
    /* 0x1C */ s16 unk01C[7]; /* Hu3DJointMotion (lbl_1_rodata_9A0[type]) */
    /* 0x2A */ s16 unk02A; /* motion requested (fn_1_2FA0) */
    /* 0x2C */ s16 unk02C; /* motion shown (fn_1_2FA0) */
    /* 0x2E */ s16 unk02E; /* action cooldown (fn_1_8E40; fork C) */
    /* 0x30 */ s16 unk030; /* HP: > 0 takes input, == 0 out (fn_1_A1D4); unk032 steps towards it */
    /* 0x32 */ s16 unk032; /* displayed HP, stepped by 1 towards unk030 (E7E8, EF64) */
    /* 0x34 */ s16 unk034; /* max HP: lbl_1_rodata_9D8[type].unk00C; copied to unk030/unk032 */
    /* 0x36 */ s16 unk036; /* button-A hold counter (fn_1_8E40; fork C) */
    /* 0x38 */ s16 unk038; /* button-B hold counter (fn_1_8E40, 8DD0; fork C) */
    /* 0x3A */ s16 unk03A;
    /* 0x3C */ s16 unk03C; /* init -1 */
    /* 0x3E */ s16 unk03E; /* COM sub-state 0..3 (fn_1_4E18 0x57C0; fork B) */
    /* 0x40 */ u8 pad040[4];
    /* 0x44 */ s32 unk044; /* input enabled (fn_1_14E8 sets 1, fn_1_1628 clears) */
    /* 0x48 */ s32 unk048; /* trigger-drive mode latched (fn_1_3664; fork B) */
    /* 0x4C */ s32 unk04C; /* camera-follow flag, init 1 (fn_1_8450; 19C4 clears) */
    /* 0x50 */ float unk050; /* speed */
    /* 0x54 */ float unk054; /* turn speed */
    /* 0x58 */ float unk058; /* target speed */
    /* 0x5C */ float unk05C; /* target turn speed */
    /* 0x60 */ float unk060; /* stick-X scale: lbl_1_rodata_9D8[type].unk004 */
    /* 0x64 */ float unk064; /* stick-Y scale: lbl_1_rodata_9D8[type].unk000 */
    /* 0x68 */ float unk068; /* knock-back speed (fn_1_82E4; fork C) */
    /* 0x6C */ float unk06C; /* knock-back direction (fn_1_82E4; fork C) */
    /* 0x70 */ float unk070; /* radius: lbl_1_rodata_9D8[type].unk008 (140 / 80) */
    /* 0x74 */ float unk074; /* angle to the solo player (fn_1_8D40; 3290) */
    /* 0x78 */ u8 pad078[0xC];
    /* 0x84 */ HuVecF unk084; /* pos (fn_1_3138 / 3274) */
    /* 0x90 */ HuVecF unk090; /* rot (fn_1_3290 / 34FC) */
    /* 0x9C */ HuVecF unk09C; /* previous pos (fn_1_3138) */
    /* 0xA8 */ HuVecF unk0A8; /* previous rot (fn_1_3290) */
    /* 0xB4 */ M519_EFFECT *unk0B4; /* fn_1_CC44 (type 1 only, else NULL) */
    /* 0xB8 */ M519_EFFECT *unk0B8; /* fn_1_CC44 (type 1 only, else NULL) */
    /* 0xBC */ HUPROCESS *unk0BC; /* child process fn_1_2F54 */
    /* 0xC0 */ s32 unk0C0; /* touching a teammate (fn_1_95B0; fork C) */
    /* 0xC4 */ s32 unk0C4; /* COM: hold button 0x200 (fn_1_69BC; fork C) */
    /* 0xC8 */ s16 unk0C8; /* pad buttons pressed */
    /* 0xCA */ s16 unk0CA; /* pad buttons held */
    /* 0xCC */ s16 unk0CC; /* stick x */
    /* 0xCE */ s16 unk0CE; /* stick y */
    /* 0xD0 */ s16 unk0D0; /* trigger L */
    /* 0xD2 */ s16 unk0D2; /* trigger R */
    /* 0xD4 */ s32 unk0D4; /* COM: target chosen */
    /* 0xD8 */ HuVecF unk0D8; /* target pos (fn_1_4E18 0x5608 copies a player's unk084) */
    /* 0xE4 */ s16 unk0E4; /* COM target: lbl_1_bss_F8[unk0E4] (fn_1_4E18); NOT initialised by fn_1_297C */
    /* 0xE6 */ s16 unk0E6; /* COM: button-A repeat delay */
    /* 0xE8 */ s16 unk0E8; /* COM: state timer */
    /* 0xEA */ s16 unk0EA; /* COM timer */
    /* 0xEC */ s16 unk0EC; /* COM: stick magnitude */
    /* 0xEE */ s16 unk0EE; /* COM: state 0 wander / 1 chase / 2 flee */
    /* 0xF0 */ s32 unk0F0; /* HuAudFXPlay handle, -1 = none */
    /* 0xF4 */ u8 pad0F4[4];
    /* 0xF8 */ float unk0F8; /* footstep phase, reset on a motion change (fn_1_2FA0) */
} M519_PLAYER; /* size 0xFC (GC) */

/* fn_1_A204: character (lbl_1_bss_E8[4]); process fn_1_A40C, modes lbl_1_data_48[] */
typedef struct m519_char {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* fn_1_A204 arg0 (group) */
    /* 0x06 */ s16 unk006; /* fn_1_A204 arg1 = playerNo (GwPlayer index, fn_1_1628 coins); fn_1_3518 -> player unk008 */
    /* 0x08 */ s16 unk008; /* player slot: fn_1_3518 copies player->unk006 */
    /* 0x0A */ s16 unk00A; /* GwPlayerConf[].charNo */
    /* 0x0C */ s32 unk00C; /* GwPlayerConf[].type (COM) */
    /* 0x10 */ s16 unk010; /* GwPlayerConf[].dif */
    /* 0x12 */ s16 unk012; /* GwPlayerConf[].padNo */
    /* 0x14 */ s16 unk014[2]; /* [0] CharModelCreate, [1] model (lbl_1_rodata_D98[charNo]), hook target (fn_1_3518 0x3550); lhax 0x14 + i*2 (fn_1_A834; fork D) */
    /* 0x18 */ s16 unk018[6]; /* CharMotionCreate (lbl_1_rodata_C60[charNo]) */
    /* 0x24 */ HuVecF unk024; /* pos (fn_1_A44C / A4D0) */
    /* 0x30 */ HuVecF unk030; /* rot (fn_1_A4EC / A570) */
    /* 0x3C */ HUPROCESS *unk03C; /* child process fn_1_A40C */
} M519_CHAR; /* size 0x40 (GC) */

/* fn_1_AB40: thrown item (lbl_1_bss_38[44]); process fn_1_ADE4, modes lbl_1_data_5C[] */
typedef struct m519_item {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s32 unk004; /* in flight (B0BC 0xB1D0 / 0xB548) */
    /* 0x08 */ s32 unk008; /* push back on contact (lbl_1_rodata_DFC[type].unk014) */
    /* 0x0C */ s16 unk00C; /* serial: lbl_1_bss_C++ % 32000 (A9F0) */
    /* 0x0E */ s16 unk00E; /* type 0..4 (fn_1_AB40 arg) */
    /* 0x10 */ s16 unk010; /* damage (lbl_1_rodata_DFC[type].unk010) */
    /* 0x12 */ s16 unk012; /* knock-back speed (lbl_1_rodata_DFC[type].unk012) */
    /* 0x14 */ s16 unk014[2]; /* models (lbl_1_rodata_DD4[type]) */
    /* 0x18 */ s16 unk018; /* owner: lbl_1_bss_F8[] index, -1 = none */
    /* 0x1A */ u8 pad01A[2];
    /* 0x1C */ float unk01C; /* speed (lbl_1_rodata_DFC[type].unk000) */
    /* 0x20 */ float unk020; /* current speed */
    /* 0x24 */ HuVecF unk024; /* pos (fn_1_AE24 / AEA8) */
    /* 0x30 */ HuVecF unk030; /* rot (fn_1_AEC4 / AF48); y = heading */
    /* 0x3C */ float unk03C; /* height start (lbl_1_rodata_DFC[type].unk008) */
    /* 0x40 */ float unk040; /* height peak (lbl_1_rodata_DFC[type].unk004) */
    /* 0x44 */ float unk044; /* current height / hit radius, init 1.0f */
    /* 0x48 */ s16 unk048; /* flight frames (lbl_1_rodata_DFC[type].unk00C) */
    /* 0x4A */ s16 unk04A; /* arc frames (lbl_1_rodata_DFC[type].unk00E) */
    /* 0x4C */ HUPROCESS *unk04C; /* child process fn_1_ADE4 */
} M519_ITEM; /* size 0x50 (GC) */

/* lbl_1_rodata_DFC: per item type parameters (fn_1_AB40; fork D) */
typedef struct m519_itemparam {
    /* 0x00 */ float unk000;
    /* 0x04 */ float unk004;
    /* 0x08 */ float unk008;
    /* 0x0C */ s16 unk00C;
    /* 0x0E */ s16 unk00E;
    /* 0x10 */ s16 unk010;
    /* 0x12 */ s16 unk012;
    /* 0x14 */ s32 unk014;
} M519_ITEMPARAM; /* size 0x18 (GC) */

/* fn_1_D0BC: HUD, one per player slot (lbl_1_bss_20[4]); process fn_1_D610,
 * modes lbl_1_data_7C[unk004][unk000] */
typedef struct m519_hud {
    /* 0x00 */ s16 unk000; /* mode */
    /* 0x02 */ s16 unk002;
    /* 0x04 */ s16 unk004; /* type 0..3 (fn_1_D0BC arg0, lbl_1_rodata_284) */
    /* 0x06 */ s16 unk006;
    /* 0x08 */ s16 unk008; /* player slot (fn_1_D0BC arg1: lbl_1_bss_F8[unk008]) */
    /* 0x0A */ s16 unk00A[18]; /* espEntry (lbl_1_rodata_F44[type], -1 = none) */
    /* 0x2E */ u8 pad02E[2];
    /* 0x30 */ HuVec2f unk030; /* pos (fn_1_D65C / D708) */
    /* 0x38 */ HuVec2f unk038[18]; /* per-sprite offset (fn_1_D65C lfsx 0x38/0x3C + i * 8) */
    /* 0xC8 */ HUPROCESS *unk0C8; /* child process fn_1_D610 */
} M519_HUD; /* size 0xCC (GC) */

/* lbl_1_rodata_198 / 2D0: camera setup (Hu3DCameraPerspectiveSet, ViewportSet, ScissorSet) */
typedef struct m519_camparam {
    /* 0x00 */ float fov;
    /* 0x04 */ float near;
    /* 0x08 */ float far;
    /* 0x0C */ float aspect;
    /* 0x10 */ float vpX;
    /* 0x14 */ float vpY;
    /* 0x18 */ float vpW;
    /* 0x1C */ float vpH;
    /* 0x20 */ float vpNear;
    /* 0x24 */ float vpFar;
    /* 0x28 */ float scX;
    /* 0x2C */ float scY;
    /* 0x30 */ float scW;
    /* 0x34 */ float scH;
} M519_CAMPARAM; /* size 0x38 (GC) */

/* lbl_1_rodata_A4: Hu3DGLight setup per stage */
typedef struct m519_light {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF aim;
    /* 0x18 */ GXColor color;
} M519_LIGHT; /* size 0x1C (GC) */

/* lbl_1_rodata_9F8[2][7]: Hu3DMotionShiftSet {start, end, attr} per player type and motion (fn_1_2FA0 and its inlined copies) */
typedef struct m519_motshift {
    /* 0x00 */ float unk000; /* start */
    /* 0x04 */ float unk004; /* end (shift) */
    /* 0x08 */ u32 unk008; /* attr */
} M519_MOTSHIFT; /* size 0xC (GC) */

typedef void (*M519_STAGEFUNC)(M519_STAGE *work);
typedef void (*M519_PLAYERFUNC)(M519_PLAYER *work);
typedef void (*M519_CHARFUNC)(M519_CHAR *work);
typedef void (*M519_ITEMFUNC)(M519_ITEM *work);
typedef void (*M519_STAGEOBJFUNC)(M519_STAGEOBJ *work);
typedef void (*M519_EFFECTFUNC)(M519_EFFECT *work, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
typedef void (*M519_HUDFUNC)(M519_HUD *work);

/* shared .rodata (read by several forks' functions) */
extern const u16 lbl_1_rodata_10[4]; /* camera bits 1, 2, 4, 8 per player slot (28C 9F4 D64 19C4 297C 8450 FE20 10244) */
extern const s16 lbl_1_rodata_18[2]; /* SE pan per player type (3664 5EDC 8450 8E40 98AC B0BC; fork C) */
extern const M519_MOTSHIFT lbl_1_rodata_9F8[2][7]; /* fn_1_2FA0 3664 5EDC 8188 9BA8 */

/* --- m519.c --- (fork A: pinned from call sites and callee argument use; see OUT.txt;
 * "guess" marks a parameter only its callee's first use pins) */
void ObjectSetup(void);
void fn_1_21C(void);
void fn_1_28C(s16 mode, s16 frameNo); /* MgSeq initHook */
void fn_1_9F4(s16 mode, s16 frameNo); /* fadeInHook */
void fn_1_D64(void);
void fn_1_143C(s16 mode, s16 frameNo); /* startHook */
void fn_1_14E8(s16 mode, s16 frameNo); /* mainHook */
void fn_1_1628(s16 mode, s16 frameNo); /* finishHook: coin payout */
void fn_1_19C4(s16 mode, s16 frameNo); /* preWinnerHook */
void fn_1_1FC0(s16 mode, s16 frameNo); /* winnerHook */
void fn_1_2270(void);
M519_STAGE *fn_1_2298(void);
void fn_1_2654(void);
void fn_1_2694(M519_STAGE *stage);
void fn_1_26A0(M519_STAGE *stage);
void fn_1_2730(M519_STAGE *stage);
void fn_1_2790(M519_STAGE *stage);
void fn_1_27FC(M519_STAGE *stage);
void fn_1_2890(M519_STAGE *stage);
void fn_1_2900(M519_STAGE *stage);
M519_PLAYER *fn_1_297C(s16 type, s16 slot);
void fn_1_2F54(void);
void fn_1_2FA0(M519_PLAYER *player, s16 motion, float speed);
void fn_1_3098(M519_PLAYER *player);
void fn_1_3138(M519_PLAYER *player, HuVecF pos);
HuVecF fn_1_3274(M519_PLAYER *player);
void fn_1_3290(M519_PLAYER *player, HuVecF rot);
HuVecF fn_1_34FC(M519_PLAYER *player);
void fn_1_3518(M519_PLAYER *player, M519_CHAR *chr);
void fn_1_3580(M519_PLAYER *player);
void fn_1_35B0(M519_PLAYER *player);
void fn_1_35BC(M519_PLAYER *player);
void fn_1_3658(M519_PLAYER *player);
void fn_1_3664(M519_PLAYER *player);
void fn_1_4D40(M519_PLAYER *player);
void fn_1_4E18(M519_PLAYER *player);
void fn_1_5EDC(M519_PLAYER *player);
void fn_1_68E4(M519_PLAYER *player);
void fn_1_69BC(M519_PLAYER *player);
void fn_1_7998(M519_PLAYER *player);
float fn_1_7EB8(M519_PLAYER *player, HuVecF *pos); /* fork C */
float fn_1_7FFC(M519_PLAYER *player, HuVecF *pos); /* fork C */
void fn_1_817C(M519_PLAYER *player);
void fn_1_8188(M519_PLAYER *player);
void fn_1_82E4(M519_PLAYER *player);
void fn_1_8450(M519_PLAYER *player);
void fn_1_8D40(M519_PLAYER *player);
s32 fn_1_8DD0(M519_PLAYER *player); /* fork C */
void fn_1_8E40(M519_PLAYER *player);
void fn_1_95B0(M519_PLAYER *player);
void fn_1_9700(M519_PLAYER *player);
void fn_1_98A0(M519_PLAYER *player);
void fn_1_98AC(M519_PLAYER *player);
void fn_1_9B9C(M519_PLAYER *player);
void fn_1_9BA8(M519_PLAYER *player);
void fn_1_A068(M519_PLAYER *player);
s32 fn_1_A1D4(M519_PLAYER *player); /* unk030 test, callers cmpwi r3, 0 */
M519_CHAR *fn_1_A204(s16 grp, s16 playerNo);
void fn_1_A40C(void);
void fn_1_A44C(M519_CHAR *chr, HuVecF pos);
HuVecF fn_1_A4D0(M519_CHAR *chr);
void fn_1_A4EC(M519_CHAR *chr, HuVecF rot);
HuVecF fn_1_A570(M519_CHAR *chr);
void fn_1_A58C(M519_CHAR *chr);
void fn_1_A598(M519_CHAR *chr);
void fn_1_A628(M519_CHAR *chr);
void fn_1_A634(M519_CHAR *chr);
void fn_1_A6B8(M519_CHAR *chr);
void fn_1_A6C4(M519_CHAR *chr);
void fn_1_A770(M519_CHAR *chr);
void fn_1_A77C(M519_CHAR *chr);
void fn_1_A828(M519_CHAR *chr);
void fn_1_A834(M519_CHAR *chr);
s32 fn_1_A9F0(s16 type, HuVecF pos, HuVecF rot, s16 owner); /* by value: callers copy to temps (fork C, 0x8F4C); s32 result (fork D, li r3, 0) */
M519_ITEM *fn_1_AB40(s16 type);
void fn_1_ADE4(void);
void fn_1_AE24(M519_ITEM *item, HuVecF pos);
HuVecF fn_1_AEA8(M519_ITEM *item);
void fn_1_AEC4(M519_ITEM *item, HuVecF rot);
HuVecF fn_1_AF48(M519_ITEM *item);
void fn_1_AF64(M519_ITEM *item);
void fn_1_B004(M519_ITEM *item);
void fn_1_B0B0(M519_ITEM *item);
void fn_1_B0BC(M519_ITEM *item);
s32 fn_1_B70C(M519_ITEM *item); /* fork D: s32 result */
s32 fn_1_B9BC(M519_ITEM *item); /* callers cmpwi r3, 0 */
s32 fn_1_BAC8(M519_ITEM *item); /* fork D: s32 result */
s32 fn_1_BECC(M519_ITEM *item); /* callers cmpwi r3, 0 */
M519_STAGEOBJ *fn_1_C058(s16 type);
void fn_1_C248(void);
void fn_1_C288(M519_STAGEOBJ *obj, HuVecF pos);
HuVecF fn_1_C30C(M519_STAGEOBJ *obj);
void fn_1_C328(M519_STAGEOBJ *obj, HuVecF rot);
HuVecF fn_1_C3AC(M519_STAGEOBJ *obj);
void fn_1_C3C8(M519_STAGEOBJ *obj);
void fn_1_C3D4(M519_STAGEOBJ *obj);
void fn_1_C464(M519_STAGEOBJ *obj);
void fn_1_C470(M519_STAGEOBJ *obj);
void fn_1_C544(M519_STAGEOBJ *obj);
void fn_1_C570(M519_STAGEOBJ *obj);
void fn_1_C788(M519_STAGEOBJ *obj, s32 respawn);
void fn_1_C798(M519_STAGEOBJ *obj);
void fn_1_CBEC(M519_STAGEOBJ *obj);
M519_EFFECT *fn_1_CC44(void);
void fn_1_CCF4(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CD54(M519_EFFECT *effect, HuVecF pos);
HuVecF fn_1_CD70(M519_EFFECT *effect);
void fn_1_CD8C(M519_EFFECT *effect);
void fn_1_CDF0(M519_EFFECT *effect, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void fn_1_CDF4(M519_EFFECT *effect);
void fn_1_CEE4(M519_EFFECT *effect, HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
s32 fn_1_CFE8(M519_EFFECT *effect); /* fork D: s32 result */
M519_HUD *fn_1_D0BC(s16 type, s16 slot);
void fn_1_D610(void);
void fn_1_D65C(M519_HUD *hud, HuVec2f pos);
HuVec2f fn_1_D708(M519_HUD *hud); /* returns unk030 in r3:r4 (lwz r4, 0x34; lwz r3, 0x30): see OUT.txt */
void fn_1_D714(M519_HUD *hud);
void fn_1_D720(M519_HUD *hud);
void fn_1_D7B0(M519_HUD *hud);
void fn_1_D7BC(M519_HUD *hud);
void fn_1_DD08(M519_HUD *hud);
void fn_1_E168(M519_HUD *hud);
void fn_1_E174(M519_HUD *hud);
void fn_1_E298(M519_HUD *hud);
void fn_1_E2D4(M519_HUD *hud);
void fn_1_E714(M519_HUD *hud);
void fn_1_EA10(M519_HUD *hud);
void fn_1_ED78(M519_HUD *hud);
void fn_1_EE8C(M519_HUD *hud);
void fn_1_F104(M519_HUD *hud);
void fn_1_F2DC(M519_HUD *hud); /* fork C had M519_OBJHDR *: bss_20 records are M519_HUD (fn_1_D0BC) */
void fn_1_F2E8(M519_HUD *hud);
void fn_1_F568(M519_HUD *hud);
void fn_1_F7F0(M519_HUD *hud);
s32 fn_1_F860(HuVecF *a, HuVecF *b, s32 push); /* fork C ("push" a guess) */
s32 fn_1_FA6C(HuVecF *a, HuVecF *b, s32 push); /* fork C */
float fn_1_FC78(float start, float end, float t);
void fn_1_FD7C(s16 playerNo, s16 type, s16 time); /* fork C: omVibrate wrapper */
s16 fn_1_FE20(u16 camMask, HuVecF pos); /* fork E */
s16 fn_1_10244(u16 camMask, HuVecF pos); /* fork E */

#endif
