#ifndef M515DLL_H
#define M515DLL_H

/*
 * m566dll (overlay #77): types and prototypes for its single translation
 * unit (m566).
 *
 * Offsets are GameCube ones from build/mp5-asm/m566Dll. No upstream names exist,
 * so functions keep reference addresses and globals keep lbl_1_* labels.
 */

#include "dolphin/types.h"
#include "game/object.h"
#include "game/hu3d.h"
#include "math.h"
#include "humath.h"

#include "game/mg/seqman.h"
#include "game/mg/actman.h"

/* TODO: work structs. Name every field by hex offset (unk050, unk0B4). */

/* obj->data of the four 0x64 "player" objects.
 * ObjectSetup: HuMemDirectMallocNum(HEAP_HEAP, 0x108, HU_MEMNUM_OVL);
 * fn_1_DACC memsets 0x108 bytes, which fixes the size. Every access seen in
 * fork K's range is a whole-word lwz/stw, so every field below is 4 bytes.
 *
 * Signedness evidence (all from fn_1_DACC / fn_1_E544):
 *   0x000  stw of obj->work[0]                              -> s32
 *   0x004  lwz + `cmpwi r0, 0x4`                            -> s32
 *   0x008  stw of the 0x00C value clamped with `cmpwi 0x9`  -> s32
 *   0x00C  stw of `lha 0x0(GwPlayerConf)`, later `extsh`    -> s32 holding a s16
 *   0x010  lwz + `cmpwi r0, -0x1`                           -> s32
 *   0x014  stw of `lha 0x4(GwPlayerConf)` (dif)             -> s32 holding a s16
 *   0x05C  lwz + `cmpwi r0, 0x0`, value is a rumble mask    -> s32
 * The remaining offsets are untouched by fork K's functions and stay unkXXX. */
typedef struct M566Ent_s {
    /* 0x00 */ s32 unk00;      /* lwz + `cmpwi 0/1/2` and `blt`   -> s32 (state) */
    /* 0x04 */ s32 unk04;      /* stw of 0 (word store)           -> s32 */
    /* 0x08 */ s32 unk08;      /* lwz + `cmpw` vs actor.unk01C, then
                                * `slwi 2` index into lbl_1_bss_C8[] and into a
                                * 4-entry local -> s32 player index 0..3 */
    /* 0x0C */ s32 unk0C;      /* stw of the s32 loop counter j   -> s32 */
    /* 0x10 */ float unk10;    /* lfs/stfs, world X   */
    /* 0x14 */ float unk14;    /* lfs/stfs, world Y   */
    /* 0x18 */ float unk18;    /* lfs/stfs, world Z   */
    /* 0x1C */ float unk1C;    /* lfs/stfs, 30*sin(...) offset X */
    /* 0x20 */ float unk20;    /* lfs/stfs.  fork F: in fn_1_668 0x4000..0x402C
                                * it is `CharModelHeightGet(work->charNo) - 20.0f`
                                * -- a DIFFERENT expression from the
                                * `100.0f + CharModelHeightGet()` fork A read in
                                * fn_1_48F8.  Both are writes of the same field. */
    /* 0x24 */ float unk24;    /* lfs/stfs, 30*cos(...) offset Z */
    /* 0x28 */ float unk28;    /* lfs/stfs + `fcmpo` vs -180.0f/180.0f, degrees */
    /* 0x2C */ float unk2C;    /* stfs of sqrtf(dx*dx + dz*dz), distance */
} M566_ENT;

/*
 * lbl_1_bss_1810 -- 29 x 0x60 (strides.py).  Fields below are the ones
 * fn_1_C708 touches; the rest are s32 placeholders for the merge.
 */
typedef struct M566Actor_s {
    /* 0x00 */ s32 unk000;
    /* 0x04 */ s32 unk004;
    /* 0x08 */ s32 unk008;     /* STILL store-only.  Fork F read all 1,592
                                * instructions of fn_1_668 0x3018..0x46FB and
                                * the only actor fields touched are 0x00, 0x10,
                                * 0x14, 0x20, 0x24, 0x28, 0x2C, 0x30.  Forks B,
                                * D, E, J and F have now all checked; only the
                                * fn_1_48F8 owner is left. */
    /* 0x0C */ s32 unk00C;     /* fork E PROVEN s32: stw of a 0..3 index into
                                * lbl_1_data_124[] (0x229C) and of -1 (0x22D4). */
    /* 0x10 */ s32 unk010;     /* fork E PROVEN s32 -- READ, not just stored:
                                * `lwz r5,0x10(r6)` + signed `add`/`cmpwi 0x4`
                                * at 0x28C4/0x28F0/0x291C.  It is a bonus added
                                * to the player's score (M566_PLAYER 0x018). */
    /* 0x14 */ s32 unk014;
    /* 0x18 */ s32 unk018;     /* fork E: word store of 0 at 0x217C. */
    /* 0x1C */ s32 unk01C;     /* fork E PROVEN s32 -- read with `lwz` + signed
                                * `cmpw` against M566_PLAYER.playerNo at 0x2F9C;
                                * written from playerNo at 0x2198.  Owner seat. */
    /* 0x20 */ s32 unk020;     /* fork F PROVEN s32 and READ: `lwz r3,0x20(r3)`
                                * + signed `cmpwi r3,0x0` at 0x38EC/0x38F0, then
                                * `lwz r5,0x20(r3)` / `add` / `stw r4,0x20(r3)`
                                * at 0x3920..0x392C -- `unk020 += (unk020 == 0)
                                * ? 8 : 0`, run once per frame while a player is
                                * standing on the prop.  Fork A's "signed % 8"
                                * reading is consistent. */
    /* 0x24 */ s32 unk024;     /* fork F: `li r6,0x1` / `stw r6,0x24(r3)` at
                                * 0x3930/0x3948, set every frame the prop is
                                * being stood on.  Word store, signedness still
                                * unproven. */
    /* 0x28 */ float unk028;
    /* 0x2C */ float unk02C;
    /* 0x30 */ float unk030;
    /* 0x34 */ float unk034;   /* fork E: stfs of Hu3DMtxTransGet's x (0x26E8),
                                  lfs into Hu3DModelPosSet (0x2764) -> float */
    /* 0x38 */ float unk038;   /* fork E: same, y (0x2704 / 0x277C) */
    /* 0x3C */ float unk03C;   /* fork E: same, z (0x2720 / 0x2794) */
    /* 0x40 */ s32 unk040;
    /* 0x44 */ s32 unk044;
    /* 0x48 */ s32 unk048;
    /* 0x4C */ Quaternion unk04C;  /* fork E: &unk04C is the `Quaternion *` of
                                  * C_QUATMtx (0x2688), PSQUATInverse src AND dst
                                  * (0x26A4/0x26BC) and PSMTXQuat (0x27B4).
                                  * Covers 0x4C..0x58. */
    /* 0x5C */ s32 unk05C;
} M566_ACTOR;

/* lbl_1_bss_600 -- 128 x 0x20 (strides.py; fn_1_9F20 indexes it with
 * `slwi r4, i, 5`, i < 0x80).  The billboard particle pool that fn_1_9F20
 * draws.  Evidence is all from fn_1_9F20 (fork J); the rest is placeholder. */
typedef struct m566Part_s {
    /* 0x00 */ s32 unk00;    /* lwz + `cmpwi r0, 0x0` -> s32, live flag */
    /* 0x04 */ s32 unk04;    /* lwz + `clrlwi ,24` into the GXColor4u8 alpha -> 32-bit, used as u8 */
    /* 0x08 */ float unk08;  /* lfs, added to corner[].x -> float world X */
    /* 0x0C */ float unk0C;  /* lfs, added to corner[].y -> float world Y */
    /* 0x10 */ float unk10;  /* lfs, added to corner[].z -> float world Z */
    /* 0x14 */ float unk14;  /* fork E: stfs at 0x24F0 of a 12.0f-scaled random -> float velocity X */
    /* 0x18 */ float unk18;  /* fork E: stfs at 0x256C, same shape -> float velocity Y */
    /* 0x1C */ float unk1C;  /* fork E: stfs at 0x25EC, same shape -> float velocity Z */
} M566_PART;

/* lbl_1_bss_E0: 41 x 0x20 (fork I, from fn_1_8F1C -- complete).
 * A queue of up to 3 pending sound requests, each with an x and a z position. */
typedef struct m566Sub_s {
    /* 0x00 */ s32 unk00;      /* lwz/stw, cmpwi 3 and cmpwi 0 -> s32 count, clamped to 3 */
    /* 0x04 */ float unk04[3]; /* lfs at +4+(count-1)*4 -> float[3], the pan source */
    /* 0x10 */ float unk10[3]; /* lfs at +0x10+(count-1)*4 -> float[3], the volume source */
    /* 0x1C */ s32 unk1C;      /* stw of the HuAudFXPlay return -> s32 sound handle */
} M566_SUB;

typedef struct m566Player_s {
    /* 0x000 */ s32 playerNo;       /* obj->work[0] */
    /* 0x004 */ s32 padIdx;         /* GwPlayerConf index; ==4 -> playerNo */
    /* 0x008 */ s32 unk008;         /* min(charNo, 9) */
    /* 0x00C */ s32 charNo;         /* GwPlayerConf[padIdx].charNo */
    /* 0x010 */ s32 unk010;         /* -1 when GwPlayerConf[].type set, else .padNo */
    /* 0x014 */ s32 unk014;         /* GwPlayerConf[].dif when unk010 == -1, else 0 */
    /* 0x018 */ s32 unk018;         /* fork E: the score.  fork F adds a READ:
                                     * `lwz r3,0x18(r31)` + SIGNED int->double
                                     * (xoris 0x8000) at 0x428C, 0x42DC, 0x43DC,
                                     * 0x442C, divided by 3.0f to drive the
                                     * end-of-round score pop -> s32. */
    /* 0x01C */ s32 unk01C;         /* fork F: the motion index currently shifted
                                     * in.  `lwz r5,0x1c(r31)` + signed `cmpw`
                                     * against `mode` (0x44D8) and `stw` of
                                     * `extsh(mode)` (0x45AC) -> s32. */
    /* 0x020 */ s32 unk020;         /* fork F PROVEN s32: `lwz r3,0x20(r31)` +
                                     * signed `cmpwi r3,0x0` / `blt` at 0x44B4,
                                     * then `extsh r28,r5` into the s16 `mode`.
                                     * A forced motion override, -1 = none. */
    /* 0x024 */ s32 unk024;         /* = 2 */
    /* 0x028 */ s32 unk028;
    /* 0x02C */ s32 unk02C[4];      /* fork E: `slwi rX,unk018,2; addi rX,rX,0x2c;
                                     * stwx r8,r31,rX` with unk018 bounded < 4
                                     * (0x28A8, 0x2900) -> s32[4], 0x2C..0x3B */
    /* 0x03C */ float unk03C;       /* fork D: stfs/lfs (0x1C14, 0x1C64) */
    /* 0x040 */ float unk040;       /* fork D: stfs/lfs -- velocity X */
    /* 0x044 */ s32 unk044;
    /* 0x048 */ float unk048;       /* fork D: stfs/lfs -- velocity Z */
    /* 0x04C */ s32 unk04C;         /* = -1 */
    /* 0x050 */ s32 unk050;
    /* 0x054 */ s32 unk054;         /* fork F: `lwz r5,0x54(r31)` / `addi 1` /
                                     * `stw` at 0x38AC..0x38C8 and cleared to 0
                                     * at 0x3C08 and 0x3C14.  A frame counter
                                     * that only advances while the rumble
                                     * global lbl_1_data_158[0] is 0. */
    /* 0x058 */ float unk058;       /* fork D: stfs/lfs -- ske_head look angle */
    /* 0x05C */ s32 unk05C;         /* rumble mask & HuPadRumbleGet() */
    /* --- fork D, fn_1_668 region 1 (the COM "walk to an actor" brain) --- */
    /* 0x060 */ s32 unk060;         /* lwz + cmpwi 0/1/3 switch -> s32 sub-state */
    /* 0x064 */ s32 unk064;         /* lwz/stw, ++, cmpw -> s32 frame counter */
    /* 0x068 */ s32 unk068;         /* lwz + cmpwi 0, cmpw -> s32 counter target */
    /* 0x06C */ s32 unk06C;         /* lwz + cmpwi -1, used as 0..28 index -> s32 */
    /* 0x070 */ s32 unk070[29];     /* lwzx/stwx at r31+(i*4+0x70), cmpwi 0/2 -> s32[29] */
    /* 0x0E4 */ s32 unk0E4;         /* lwz + cmpwi -1 -> s32 */
    /* 0x0E8 */ float unk0E8;       /* lfs -- a world X */
    /* 0x0EC */ float unk0EC;       /* lfs -- a world Z */
    /* 0x0F0 */ float unk0F0;       /* lfs/stfs -- steering offset in degrees */
    /* 0x0F4 */ s32 unk0F4;         /* lwz + cmpw against unk06C, 0..28 index -> s32.
                                     * fork F: written 0 every frame at 0x31F4 and
                                     * set to work->unk04C at 0x3530 when the
                                     * highlighted prop is alive. */
    /* 0x0F8 */ float unk0F8;       /* lfs/stfs -- best distance so far */
    /* 0x0FC */ s32 unk0FC;         /* lwz/stw, ++, cmpw -> s32 */
    /* 0x100 */ s32 unk100;         /* lwz + cmpwi 0x14/0x46 -> s32 */
    /* 0x104 */ s32 unk104;         /* lwz + cmpwi 0, mullw sign product -> s32 */
} M566_PLAYER;                      /* 0x108 */

/* --- m566.c --- */
/* extern lbl_1_data_0; */
/* extern lbl_1_data_1C; */
/* extern lbl_1_data_C0; */
/* extern lbl_1_data_E8; */
/* extern lbl_1_data_F2; */
/* extern lbl_1_data_FC; */
/* extern lbl_1_data_124; */
/* extern lbl_1_data_134; */
/* extern lbl_1_data_138; */
/* extern lbl_1_data_140; */
/* extern lbl_1_data_144; */
/* extern lbl_1_data_148; */
/* extern lbl_1_data_14C; */
/* extern lbl_1_data_158; */
/* extern lbl_1_data_15C; */
/* extern lbl_1_data_19C; */
/* extern lbl_1_data_210; */
/* extern lbl_1_data_21C; */
/* extern lbl_1_data_230; */
/* extern lbl_1_data_244; */
/* extern lbl_1_data_258; */
/* extern lbl_1_data_25C; */
/* extern jumptable_1_data_268; */
/* extern lbl_1_data_284; */
/* extern lbl_1_data_29F; */
/* extern lbl_1_rodata_10; */
/* extern lbl_1_rodata_18; */
/* extern lbl_1_rodata_20; */
/* extern lbl_1_rodata_28; */
/* extern lbl_1_rodata_30; */
/* extern lbl_1_rodata_38; */
/* extern lbl_1_rodata_40; */
/* extern lbl_1_rodata_48; */
/* extern lbl_1_rodata_50; */
/* extern lbl_1_rodata_58; */
/* extern lbl_1_rodata_5C; */
/* extern lbl_1_rodata_60; */
/* extern lbl_1_rodata_64; */
/* extern lbl_1_rodata_68; */
/* extern lbl_1_rodata_6C; */
/* extern lbl_1_rodata_70; */
/* extern lbl_1_rodata_74; */
/* extern lbl_1_rodata_78; */
/* extern lbl_1_rodata_88; */
/* extern lbl_1_rodata_98; */
/* extern lbl_1_rodata_C0; */
/* extern lbl_1_rodata_E0; */
/* extern lbl_1_rodata_EC; */
/* extern lbl_1_rodata_10C; */
/* extern lbl_1_rodata_11C; */
/* extern lbl_1_rodata_128; */
/* extern lbl_1_rodata_134; */
/* extern lbl_1_rodata_154; */
/* extern lbl_1_rodata_17C; */
/* extern lbl_1_rodata_180; */
/* extern lbl_1_rodata_184; */
/* extern lbl_1_rodata_188; */
/* extern lbl_1_rodata_18C; */
/* extern lbl_1_rodata_190; */
/* extern lbl_1_rodata_194; */
/* extern lbl_1_rodata_198; */
/* extern lbl_1_rodata_19C; */
/* extern lbl_1_rodata_1A0; */
/* extern lbl_1_rodata_1A4; */
/* extern lbl_1_rodata_1A8; */
/* extern lbl_1_rodata_1B0; */
/* extern lbl_1_rodata_1B8; */
/* extern lbl_1_rodata_1C0; */
/* extern lbl_1_rodata_1C4; */
/* extern lbl_1_rodata_1C8; */
/* extern lbl_1_rodata_1CC; */
/* extern lbl_1_rodata_1D0; */
/* extern lbl_1_rodata_1D8; */
/* extern lbl_1_rodata_1E0; */
/* extern lbl_1_rodata_1E4; */
/* extern lbl_1_rodata_1E8; */
/* extern lbl_1_rodata_1EC; */
/* extern lbl_1_rodata_1F0; */
/* extern lbl_1_rodata_1F4; */
/* extern lbl_1_rodata_1F8; */
/* extern lbl_1_rodata_200; */
/* extern lbl_1_rodata_204; */
/* extern lbl_1_rodata_208; */
/* extern lbl_1_rodata_20C; */
/* extern lbl_1_rodata_210; */
/* extern lbl_1_rodata_214; */
/* extern lbl_1_rodata_218; */
/* extern lbl_1_rodata_21C; */
/* extern lbl_1_rodata_220; */
/* extern lbl_1_rodata_228; */
/* extern lbl_1_rodata_230; */
/* extern lbl_1_rodata_234; */
/* extern lbl_1_rodata_238; */
/* extern lbl_1_rodata_23C; */
/* extern lbl_1_rodata_240; */
/* extern lbl_1_rodata_248; */
/* extern lbl_1_rodata_250; */
/* extern lbl_1_rodata_258; */
/* extern lbl_1_rodata_260; */
/* extern lbl_1_rodata_264; */
/* extern lbl_1_rodata_268; */
/* extern lbl_1_rodata_26C; */
/* extern lbl_1_rodata_270; */
/* extern lbl_1_rodata_278; */
/* extern lbl_1_rodata_280; */
/* extern lbl_1_rodata_288; */
/* extern lbl_1_rodata_290; */
/* extern lbl_1_rodata_298; */
/* extern lbl_1_rodata_2A0; */
/* extern lbl_1_rodata_2B0; */
/* extern lbl_1_rodata_2BC; */
/* extern lbl_1_rodata_2E4; */
/* extern lbl_1_rodata_30C; */
/* extern lbl_1_rodata_310; */
/* extern lbl_1_rodata_318; */
/* extern lbl_1_rodata_320; */
/* extern lbl_1_rodata_328; */
/* extern lbl_1_rodata_330; */
/* extern lbl_1_rodata_338; */
/* extern lbl_1_rodata_340; */
/* extern lbl_1_rodata_344; */
/* extern lbl_1_rodata_348; */
/* extern lbl_1_rodata_34C; */
/* extern lbl_1_rodata_350; */
/* extern lbl_1_rodata_358; */
/* extern lbl_1_rodata_360; */
/* extern lbl_1_rodata_364; */
/* extern lbl_1_rodata_368; */
/* extern lbl_1_rodata_36C; */
/* extern lbl_1_rodata_370; */
/* extern lbl_1_rodata_374; */
/* extern lbl_1_rodata_378; */
/* extern lbl_1_rodata_37C; */
/* extern lbl_1_rodata_380; */
/* extern lbl_1_rodata_388; */
/* extern lbl_1_rodata_390; */
/* extern lbl_1_rodata_394; */
/* extern lbl_1_rodata_398; */
/* extern lbl_1_rodata_39C; */
/* extern lbl_1_rodata_3A0; */
/* extern lbl_1_rodata_3A4; */
/* extern lbl_1_rodata_3A8; */
/* extern lbl_1_rodata_3AC; */
/* extern lbl_1_rodata_3B0; */
/* extern lbl_1_rodata_3B4; */
/* extern lbl_1_rodata_458; */
/* extern lbl_1_rodata_45C; */
/* extern lbl_1_rodata_460; */
/* extern lbl_1_rodata_490; */
/* extern lbl_1_rodata_4C0; */
/* extern lbl_1_rodata_4D0; */
/* extern lbl_1_rodata_4F0; */
/* extern lbl_1_rodata_518; */
/* extern lbl_1_rodata_540; */
/* extern lbl_1_rodata_548; */
/* extern lbl_1_rodata_550; */
/* extern lbl_1_rodata_554; */
/* extern lbl_1_rodata_558; */
/* extern lbl_1_rodata_560; */
/* extern lbl_1_rodata_568; */
/* extern lbl_1_rodata_570; */
/* extern lbl_1_rodata_578; */
/* extern lbl_1_rodata_580; */
/* extern lbl_1_rodata_588; */
/* extern lbl_1_rodata_590; */
/* extern lbl_1_rodata_598; */
/* extern lbl_1_rodata_5A0; */
/* extern lbl_1_rodata_5A8; */
/* extern lbl_1_rodata_5B0; */
/* extern lbl_1_rodata_5B4; */
/* extern lbl_1_rodata_5B8; */
/* extern lbl_1_rodata_5CC; */
/* extern lbl_1_rodata_5E4; */
/* extern lbl_1_rodata_5FC; */
/* extern lbl_1_rodata_608; */
/* extern lbl_1_rodata_620; */
/* extern lbl_1_rodata_62C; */
/* extern lbl_1_rodata_648; */
/* extern lbl_1_rodata_664; */
/* extern lbl_1_rodata_680; */
/* extern lbl_1_rodata_6F4; */
/* extern lbl_1_rodata_768; */
/* extern lbl_1_rodata_774; */
/* extern lbl_1_rodata_784; */
/* extern lbl_1_rodata_7A0; */
/* extern lbl_1_rodata_7A4; */
/* extern lbl_1_rodata_7A8; */
/* extern lbl_1_rodata_7B0; */
/* extern lbl_1_rodata_7B8; */
/* extern lbl_1_rodata_7C0; */
/* extern lbl_1_rodata_7C4; */
/* extern lbl_1_rodata_7C8; */
/* extern lbl_1_rodata_7D8; */
/* extern lbl_1_rodata_7E8; */
/* extern lbl_1_rodata_7F4; */
/* extern lbl_1_rodata_800; */
/* extern lbl_1_rodata_801; */
/* extern lbl_1_rodata_804; */
/* extern lbl_1_rodata_808; */
/* extern lbl_1_rodata_80C; */
/* extern lbl_1_rodata_810; */
/* extern lbl_1_rodata_814; */
/* extern lbl_1_rodata_818; */
/* extern lbl_1_rodata_81C; */
/* extern lbl_1_rodata_820; */
/* extern lbl_1_rodata_824; */
/* extern lbl_1_rodata_828; */
void fn_1_A0(void);
void fn_1_518(int seNo, float x, float y);
void fn_1_668(OMOBJ *obj);
void fn_1_48F8(OMOBJ *obj);
void fn_1_8F1C(void);
void fn_1_9F20(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_A654(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_C06C(HU3DMODEL *modelP, Mtx *mtx);
void fn_1_C708(OMOBJ *obj);
void fn_1_DACC(OMOBJ *obj);
void fn_1_DEAC(OMOBJ *obj);
void ObjectSetup(void);
void fn_1_E4EC(OMOBJ *obj);
void fn_1_E544(void);

#endif
