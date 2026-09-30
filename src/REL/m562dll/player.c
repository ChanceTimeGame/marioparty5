/*
 * m562dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/player.s.
 */

#include "REL/m562dll.h"

#ifdef __MWERKS__
/* retail passes the s32 charNo unnarrowed (lwz, no extsh): CharFXPlay is called unprototyped */
s32 CharFXPlay();
#else
#include "game/audio.h"
#endif
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x220 lbl_1_rodata_220 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x22C lbl_1_rodata_22C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_238 = 0.0f; /* 0x238 */
static const float lbl_1_rodata_23C = 4.0f; /* 0x23C */
static const float lbl_1_rodata_240 = 0.5f; /* 0x240 */
static const float lbl_1_rodata_244 = 9.08f; /* 0x244 */
static const float lbl_1_rodata_248 = 1.5f; /* 0x248 */
static const float lbl_1_rodata_24C = 5.0f; /* 0x24C */
static const float lbl_1_rodata_250 = 1.0f; /* 0x250 */
static const float lbl_1_rodata_254 = 0.05f; /* 0x254 */
static const float lbl_1_rodata_258 = 0.95f; /* 0x258 */
static const float lbl_1_rodata_25C = 20.0f; /* 0x25C */
static const float lbl_1_rodata_260 = 75.0f; /* 0x260 */
static const float lbl_1_rodata_264 = 575.0f; /* 0x264 */
static const float lbl_1_rodata_268 = -575.0f; /* 0x268 */
static const float lbl_1_rodata_26C = 450.0f; /* 0x26C */
static const float lbl_1_rodata_270 = -450.0f; /* 0x270 */
static const float lbl_1_rodata_274 = 1075.0f; /* 0x274 */
static const float lbl_1_rodata_278 = -1075.0f; /* 0x278 */
static const float lbl_1_rodata_27C = 550.0f; /* 0x27C */
static const float lbl_1_rodata_280 = -350.0f; /* 0x280 */
/* 0x288 lbl_1_rodata_288 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_290 = 15.0f; /* 0x290 */
static const double lbl_1_rodata_298 = 0.5; /* 0x298 */
static const double lbl_1_rodata_2A0 = 3.0; /* 0x2A0 */
static const float lbl_1_rodata_2A8 = 10.0f; /* 0x2A8 */
static const float lbl_1_rodata_2AC = 56.0f; /* 0x2AC */
static const float lbl_1_rodata_2B0 = 0.001f; /* 0x2B0 */
static const double lbl_1_rodata_2B8 = 180.0; /* 0x2B8 */
static const double lbl_1_rodata_2C0 = 3.141592653589793; /* 0x2C0 */
static const double lbl_1_rodata_2C8 = 360.0; /* 0x2C8 */
static const double lbl_1_rodata_2D0 = -180.0; /* 0x2D0 */
static const float lbl_1_rodata_2D8 = 6.0f; /* 0x2D8 */
static const double lbl_1_rodata_2E0 = 600.0; /* 0x2E0 */
static const float lbl_1_rodata_2E8 = 30.0f; /* 0x2E8 */
static const float lbl_1_rodata_2EC = 0.4f; /* 0x2EC */
static const float lbl_1_rodata_2F0 = 150.0f; /* 0x2F0 */
static const double lbl_1_rodata_2F8 = 1.0471975511965976; /* 0x2F8 */
static const float lbl_1_rodata_300 = 0.6f; /* 0x300 */
static const double lbl_1_rodata_308 = 0.800000011920929; /* 0x308 */
static const double lbl_1_rodata_310 = 10.0; /* 0x310 */
static const double lbl_1_rodata_318 = 1200.0; /* 0x318 */
static const float lbl_1_rodata_320 = 93.0f; /* 0x320 */
static const double lbl_1_rodata_328 = 200.0; /* 0x328 */
static const float lbl_1_rodata_330 = 180.0f; /* 0x330 */
static const float lbl_1_rodata_334 = 360.0f; /* 0x334 */
static const float lbl_1_rodata_338 = -180.0f; /* 0x338 */
static const float lbl_1_rodata_33C = 3.0f; /* 0x33C */

/* --- functions (reference order), .data placed before its first user --- */
/* 0x190 */ u32 lbl_1_data_190[403] = { DATA_mariomot, DATANUM(DATA_mariomot, 1), DATANUM(DATA_mariomot, 2), DATANUM(DATA_mariomot, 3), DATANUM(DATA_mariomot, 4), DATANUM(DATA_mariomot, 40), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 39), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 89), DATANUM(DATA_mariomot, 43), DATANUM(DATA_mariomot, 21), DATANUM(DATA_mariomot, 23), DATANUM(DATA_mariomot, 24), DATANUM(DATA_mariomot, 22), DATANUM(DATA_mariomot, 36), DATANUM(DATA_mariomot, 63), DATANUM(DATA_mariomot, 16), DATANUM(DATA_mariomot, 17), DATANUM(DATA_mariomot, 19), DATANUM(DATA_mariomot, 20), DATANUM(DATA_mariomot, 26), DATANUM(DATA_mariomot, 6), DATANUM(DATA_mariomot, 49), DATANUM(DATA_mariomot, 25), DATANUM(DATA_mariomot, 44), DATANUM(DATA_mariomot, 131), DATANUM(DATA_mariomot, 132), DATANUM(DATA_mario, 189), DATA_luigimot, DATANUM(DATA_luigimot, 1), DATANUM(DATA_luigimot, 2), DATANUM(DATA_luigimot, 3), DATANUM(DATA_luigimot, 4), DATANUM(DATA_luigimot, 40), DATANUM(DATA_luigimot, 38), DATANUM(DATA_luigimot, 38), DATANUM(DATA_luigimot, 39), DATANUM(DATA_luigimot, 38), DATANUM(DATA_luigimot, 38), DATANUM(DATA_luigimot, 89), DATANUM(DATA_luigimot, 43), DATANUM(DATA_luigimot, 21), DATANUM(DATA_luigimot, 23), DATANUM(DATA_luigimot, 24), DATANUM(DATA_luigimot, 22), DATANUM(DATA_luigimot, 36), DATANUM(DATA_luigimot, 63), DATANUM(DATA_luigimot, 16), DATANUM(DATA_luigimot, 17), DATANUM(DATA_luigimot, 19), DATANUM(DATA_luigimot, 20), DATANUM(DATA_luigimot, 26), DATANUM(DATA_luigimot, 6), DATANUM(DATA_luigimot, 49), DATANUM(DATA_luigimot, 25), DATANUM(DATA_luigimot, 44), DATANUM(DATA_luigimot, 131), DATANUM(DATA_luigimot, 132), DATANUM(DATA_luigi, 189), DATA_peachmot, DATANUM(DATA_peachmot, 1), DATANUM(DATA_peachmot, 2), DATANUM(DATA_peachmot, 3), DATANUM(DATA_peachmot, 4), DATANUM(DATA_peachmot, 40), DATANUM(DATA_peachmot, 38), DATANUM(DATA_peachmot, 38), DATANUM(DATA_peachmot, 39), DATANUM(DATA_peachmot, 38), DATANUM(DATA_peachmot, 38), DATANUM(DATA_peachmot, 89), DATANUM(DATA_peachmot, 43), DATANUM(DATA_peachmot, 21), DATANUM(DATA_peachmot, 23), DATANUM(DATA_peachmot, 24), DATANUM(DATA_peachmot, 22), DATANUM(DATA_peachmot, 36), DATANUM(DATA_peachmot, 63), DATANUM(DATA_peachmot, 16), DATANUM(DATA_peachmot, 17), DATANUM(DATA_peachmot, 19), DATANUM(DATA_peachmot, 20), DATANUM(DATA_peachmot, 26), DATANUM(DATA_peachmot, 6), DATANUM(DATA_peachmot, 49), DATANUM(DATA_peachmot, 25), DATANUM(DATA_peachmot, 44), DATANUM(DATA_peachmot, 131), DATANUM(DATA_peachmot, 132), DATANUM(DATA_peach, 189), DATA_yoshimot, DATANUM(DATA_yoshimot, 1), DATANUM(DATA_yoshimot, 2), DATANUM(DATA_yoshimot, 3), DATANUM(DATA_yoshimot, 4), DATANUM(DATA_yoshimot, 40), DATANUM(DATA_yoshimot, 38), DATANUM(DATA_yoshimot, 38), DATANUM(DATA_yoshimot, 39), DATANUM(DATA_yoshimot, 38), DATANUM(DATA_yoshimot, 38), DATANUM(DATA_yoshimot, 89), DATANUM(DATA_yoshimot, 43), DATANUM(DATA_yoshimot, 21), DATANUM(DATA_yoshimot, 23), DATANUM(DATA_yoshimot, 24), DATANUM(DATA_yoshimot, 22), DATANUM(DATA_yoshimot, 36), DATANUM(DATA_yoshimot, 63), DATANUM(DATA_yoshimot, 16), DATANUM(DATA_yoshimot, 17), DATANUM(DATA_yoshimot, 19), DATANUM(DATA_yoshimot, 20), DATANUM(DATA_yoshimot, 26), DATANUM(DATA_yoshimot, 6), DATANUM(DATA_yoshimot, 49), DATANUM(DATA_yoshimot, 25), DATANUM(DATA_yoshimot, 44), DATANUM(DATA_yoshimot, 131), DATANUM(DATA_yoshimot, 132), DATANUM(DATA_yoshi, 189), DATA_wariomot, DATANUM(DATA_wariomot, 1), DATANUM(DATA_wariomot, 2), DATANUM(DATA_wariomot, 3), DATANUM(DATA_wariomot, 4), DATANUM(DATA_wariomot, 40), DATANUM(DATA_wariomot, 38), DATANUM(DATA_wariomot, 38), DATANUM(DATA_wariomot, 39), DATANUM(DATA_wariomot, 38), DATANUM(DATA_wariomot, 38), DATANUM(DATA_wariomot, 89), DATANUM(DATA_wariomot, 43), DATANUM(DATA_wariomot, 21), DATANUM(DATA_wariomot, 23), DATANUM(DATA_wariomot, 24), DATANUM(DATA_wariomot, 22), DATANUM(DATA_wariomot, 36), DATANUM(DATA_wariomot, 63), DATANUM(DATA_wariomot, 16), DATANUM(DATA_wariomot, 17), DATANUM(DATA_wariomot, 19), DATANUM(DATA_wariomot, 20), DATANUM(DATA_wariomot, 26), DATANUM(DATA_wariomot, 6), DATANUM(DATA_wariomot, 49), DATANUM(DATA_wariomot, 25), DATANUM(DATA_wariomot, 44), DATANUM(DATA_wariomot, 131), DATANUM(DATA_wariomot, 132), DATANUM(DATA_wario, 189), DATA_daisymot, DATANUM(DATA_daisymot, 1), DATANUM(DATA_daisymot, 2), DATANUM(DATA_daisymot, 3), DATANUM(DATA_daisymot, 4), DATANUM(DATA_daisymot, 40), DATANUM(DATA_daisymot, 38), DATANUM(DATA_daisymot, 38), DATANUM(DATA_daisymot, 39), DATANUM(DATA_daisymot, 38), DATANUM(DATA_daisymot, 38), DATANUM(DATA_daisymot, 89), DATANUM(DATA_daisymot, 43), DATANUM(DATA_daisymot, 21), DATANUM(DATA_daisymot, 23), DATANUM(DATA_daisymot, 24), DATANUM(DATA_daisymot, 22), DATANUM(DATA_daisymot, 36), DATANUM(DATA_daisymot, 63), DATANUM(DATA_daisymot, 16), DATANUM(DATA_daisymot, 17), DATANUM(DATA_daisymot, 19), DATANUM(DATA_daisymot, 20), DATANUM(DATA_daisymot, 26), DATANUM(DATA_daisymot, 6), DATANUM(DATA_daisymot, 49), DATANUM(DATA_daisymot, 25), DATANUM(DATA_daisymot, 44), DATANUM(DATA_daisymot, 131), DATANUM(DATA_daisymot, 132), DATANUM(DATA_daisy, 189), DATA_waluigimot, DATANUM(DATA_waluigimot, 1), DATANUM(DATA_waluigimot, 2), DATANUM(DATA_waluigimot, 3), DATANUM(DATA_waluigimot, 4), DATANUM(DATA_waluigimot, 40), DATANUM(DATA_waluigimot, 38), DATANUM(DATA_waluigimot, 38), DATANUM(DATA_waluigimot, 39), DATANUM(DATA_waluigimot, 38), DATANUM(DATA_waluigimot, 38), DATANUM(DATA_waluigimot, 89), DATANUM(DATA_waluigimot, 43), DATANUM(DATA_waluigimot, 21), DATANUM(DATA_waluigimot, 23), DATANUM(DATA_waluigimot, 24), DATANUM(DATA_waluigimot, 22), DATANUM(DATA_waluigimot, 36), DATANUM(DATA_waluigimot, 63), DATANUM(DATA_waluigimot, 16), DATANUM(DATA_waluigimot, 17), DATANUM(DATA_waluigimot, 19), DATANUM(DATA_waluigimot, 20), DATANUM(DATA_waluigimot, 26), DATANUM(DATA_waluigimot, 6), DATANUM(DATA_waluigimot, 49), DATANUM(DATA_waluigimot, 25), DATANUM(DATA_waluigimot, 44), DATANUM(DATA_waluigimot, 131), DATANUM(DATA_waluigimot, 132), DATANUM(DATA_waluigi, 189), DATA_kinopiomot, DATANUM(DATA_kinopiomot, 1), DATANUM(DATA_kinopiomot, 2), DATANUM(DATA_kinopiomot, 3), DATANUM(DATA_kinopiomot, 4), DATANUM(DATA_kinopiomot, 40), DATANUM(DATA_kinopiomot, 38), DATANUM(DATA_kinopiomot, 38), DATANUM(DATA_kinopiomot, 39), DATANUM(DATA_kinopiomot, 38), DATANUM(DATA_kinopiomot, 38), DATANUM(DATA_kinopiomot, 89), DATANUM(DATA_kinopiomot, 43), DATANUM(DATA_kinopiomot, 21), DATANUM(DATA_kinopiomot, 23), DATANUM(DATA_kinopiomot, 24), DATANUM(DATA_kinopiomot, 22), DATANUM(DATA_kinopiomot, 36), DATANUM(DATA_kinopiomot, 63), DATANUM(DATA_kinopiomot, 16), DATANUM(DATA_kinopiomot, 17), DATANUM(DATA_kinopiomot, 19), DATANUM(DATA_kinopiomot, 20), DATANUM(DATA_kinopiomot, 26), DATANUM(DATA_kinopiomot, 6), DATANUM(DATA_kinopiomot, 49), DATANUM(DATA_kinopiomot, 25), DATANUM(DATA_kinopiomot, 44), DATANUM(DATA_kinopiomot, 131), DATANUM(DATA_kinopiomot, 132), DATANUM(DATA_kinopio, 189), DATA_teresamot, DATANUM(DATA_teresamot, 1), DATANUM(DATA_teresamot, 2), DATANUM(DATA_teresamot, 3), DATANUM(DATA_teresamot, 4), DATANUM(DATA_teresamot, 40), DATANUM(DATA_teresamot, 38), DATANUM(DATA_teresamot, 38), DATANUM(DATA_teresamot, 39), DATANUM(DATA_teresamot, 38), DATANUM(DATA_teresamot, 38), DATANUM(DATA_teresamot, 89), DATANUM(DATA_teresamot, 43), DATANUM(DATA_teresamot, 21), DATANUM(DATA_teresamot, 23), DATANUM(DATA_teresamot, 24), DATANUM(DATA_teresamot, 22), DATANUM(DATA_teresamot, 36), DATANUM(DATA_teresamot, 63), DATANUM(DATA_teresamot, 16), DATANUM(DATA_teresamot, 17), DATANUM(DATA_teresamot, 19), DATANUM(DATA_teresamot, 20), DATANUM(DATA_teresamot, 26), DATANUM(DATA_teresamot, 6), DATANUM(DATA_teresamot, 49), DATANUM(DATA_teresamot, 25), DATANUM(DATA_teresamot, 44), DATANUM(DATA_teresamot, 131), DATANUM(DATA_teresamot, 132), DATANUM(DATA_teresa, 189), DATA_minikoopamot, DATANUM(DATA_minikoopamot, 1), DATANUM(DATA_minikoopamot, 2), DATANUM(DATA_minikoopamot, 3), DATANUM(DATA_minikoopamot, 4), DATANUM(DATA_minikoopamot, 40), DATANUM(DATA_minikoopamot, 38), DATANUM(DATA_minikoopamot, 38), DATANUM(DATA_minikoopamot, 39), DATANUM(DATA_minikoopamot, 38), DATANUM(DATA_minikoopamot, 38), DATANUM(DATA_minikoopamot, 89), DATANUM(DATA_minikoopamot, 43), DATANUM(DATA_minikoopamot, 21), DATANUM(DATA_minikoopamot, 23), DATANUM(DATA_minikoopamot, 24), DATANUM(DATA_minikoopamot, 22), DATANUM(DATA_minikoopamot, 36), DATANUM(DATA_minikoopamot, 63), DATANUM(DATA_minikoopamot, 16), DATANUM(DATA_minikoopamot, 17), DATANUM(DATA_minikoopamot, 19), DATANUM(DATA_minikoopamot, 20), DATANUM(DATA_minikoopamot, 26), DATANUM(DATA_minikoopamot, 6), DATANUM(DATA_minikoopamot, 49), DATANUM(DATA_minikoopamot, 25), DATANUM(DATA_minikoopamot, 44), DATANUM(DATA_minikoopamot, 131), DATANUM(DATA_minikoopamot, 132), DATANUM(DATA_minikoopa, 189), DATA_mariomot, DATANUM(DATA_mariomot, 1), DATANUM(DATA_mariomot, 2), DATANUM(DATA_mariomot, 3), DATANUM(DATA_mariomot, 4), DATANUM(DATA_mariomot, 40), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 39), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 89), DATANUM(DATA_mariomot, 43), DATANUM(DATA_mariomot, 21), DATANUM(DATA_mariomot, 23), DATANUM(DATA_mariomot, 24), DATANUM(DATA_mariomot, 22), DATANUM(DATA_mariomot, 36), DATANUM(DATA_mariomot, 63), DATANUM(DATA_mariomot, 16), DATANUM(DATA_mariomot, 17), DATANUM(DATA_mariomot, 19), DATANUM(DATA_mariomot, 20), DATANUM(DATA_mariomot, 26), DATANUM(DATA_mariomot, 6), DATANUM(DATA_mariomot, 49), DATANUM(DATA_mariomot, 25), DATANUM(DATA_mariomot, 44), DATANUM(DATA_mariomot, 131), DATANUM(DATA_mariomot, 132), DATANUM(DATA_mario, 189), DATA_mariomot, DATANUM(DATA_mariomot, 1), DATANUM(DATA_mariomot, 2), DATANUM(DATA_mariomot, 3), DATANUM(DATA_mariomot, 4), DATANUM(DATA_mariomot, 40), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 39), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 89), DATANUM(DATA_mariomot, 43), DATANUM(DATA_mariomot, 21), DATANUM(DATA_mariomot, 23), DATANUM(DATA_mariomot, 24), DATANUM(DATA_mariomot, 22), DATANUM(DATA_mariomot, 36), DATANUM(DATA_mariomot, 63), DATANUM(DATA_mariomot, 16), DATANUM(DATA_mariomot, 17), DATANUM(DATA_mariomot, 19), DATANUM(DATA_mariomot, 20), DATANUM(DATA_mariomot, 26), DATANUM(DATA_mariomot, 6), DATANUM(DATA_mariomot, 49), DATANUM(DATA_mariomot, 25), DATANUM(DATA_mariomot, 44), DATANUM(DATA_mariomot, 131), DATANUM(DATA_mariomot, 132), DATANUM(DATA_mario, 189), DATA_mariomot, DATANUM(DATA_mariomot, 1), DATANUM(DATA_mariomot, 2), DATANUM(DATA_mariomot, 3), DATANUM(DATA_mariomot, 4), DATANUM(DATA_mariomot, 40), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 39), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 38), DATANUM(DATA_mariomot, 89), DATANUM(DATA_mariomot, 43), DATANUM(DATA_mariomot, 21), DATANUM(DATA_mariomot, 23), DATANUM(DATA_mariomot, 24), DATANUM(DATA_mariomot, 22), DATANUM(DATA_mariomot, 36), DATANUM(DATA_mariomot, 63), DATANUM(DATA_mariomot, 16), DATANUM(DATA_mariomot, 17), DATANUM(DATA_mariomot, 19), DATANUM(DATA_mariomot, 20), DATANUM(DATA_mariomot, 26), DATANUM(DATA_mariomot, 6), DATANUM(DATA_mariomot, 49), DATANUM(DATA_mariomot, 25), DATANUM(DATA_mariomot, 44), DATANUM(DATA_mariomot, 131), DATANUM(DATA_mariomot, 132), DATANUM(DATA_mario, 189) };


#define M562_ANGLEWRAP(a) (((a) > 180.0f) ? ((a) - 360.0f) : (((a) <= -180.0f) ? (360.0f + (a)) : (a)))
#define M562_CLAMP01(t) (((t) > 1.0f) ? 1.0f : (((t) < 0.0f) ? 0.0f : (t)))
#define M562_ABS(x) (((x) >= 0) ? (x) : -(x))

/* 293 insns: player init (main fn_1_AC4, work+0x28). */
void fn_1_6B28(M562_PLAYER *player, s16 playerNo, M562_WORK *work)
{
    HuVecF *src;
    HuVecF *src2;
    u16 i;
    HU3DMODELID mdlId;
    OMOBJ *obj;
    M562_CAMERA *camera;
    M562_WORK *w;

    w = work;
    camera = &w->camera[0];
    obj = NULL;
    memset(player, 0, sizeof(M562_PLAYER));
    player->unk000 = work;
    player->unk014 = playerNo;
    player->unk01C = GwPlayerConf[player->unk014].grp;
    player->unk018 = GwPlayerConf[player->unk014].charNo;
    obj = omAddObjEx(w->unk0000, 100, 1, 31, -1, NULL);
    player->unk020 = obj;
    player->unk088 = 0;
    player->unk068 = CharModelHeightGet(player->unk018);
    player->unk00C = 1;
    mdlId = CharModelCreate(player->unk018, 2);
    player->unk024 = mdlId;
    obj->mdlId[0] = mdlId;
    Hu3DModelShadowSet(mdlId);
    CharModelStepFxSet(player->unk018, 0);
    CharEffectLayerSet(4);
    for (i = 0; i < 31; i++) {
        obj->mtnId[i] = CharMotionCreate(player->unk018, ((u32(*)[31])lbl_1_data_190)[player->unk018][i]);
        CharMotionSet(player->unk018, obj->mtnId[i]);
    }
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DMotionSet(mdlId, obj->mtnId[0]);
    Hu3DModelCameraSet(mdlId, camera->unk04);
    Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[0], 0.0f, 4.0f, 0);
    player->unk09A = player->unk098 = 0;
    player->unk09C = 1;
    player->unk0B8 = &Hu3DData[mdlId].pos;
    player->unk0BC = &Hu3DData[mdlId].rot;
    if (w->unk0020 == 0) {
        player->unk08C = 6;
    } else if (w->unk0020 == 1) {
        player->unk08C = 8;
    } else if (w->unk0020 == 2) {
        player->unk08C = 10;
    } else {
        player->unk08C = 10;
    }
    {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        src = &zero;
        player->unk0A0 = *src;
    }
    {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        src2 = &zero;
        player->unk0AC = *src2;
    }
    omSetTra(obj, player->unk0A0.x, player->unk0A0.y, player->unk0A0.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x750020, HU_MEMNUM_OVL, HEAP_MODEL));
    player->unk064 = mdlId;
    Hu3DModelScaleSet(mdlId, 0.5f, 0.5f, 0.5f);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, camera->unk04);
    Hu3DModelLayerSet(mdlId, 4);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    player->unk066 = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(0x750055, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdlId, player->unk066);
    Hu3DMotionSpeedSet(mdlId, 9.08f);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_B07C(&player->unk06C, playerNo, player);
}

/* 34 insns: player kill (main fn_1_FB0). */
void fn_1_6FBC(M562_PLAYER *player)
{
    M562_WORK *work = player->unk000;

    fn_1_B0E0(&player->unk06C);
    Hu3DMotionKill(player->unk066);
    Hu3DModelKill(player->unk064);
    if (player->unk020) {
        CharModelKill(player->unk018);
        omDelObjEx(work->unk0000, player->unk020);
        player->unk020 = NULL;
    }
    memset(player, 0, sizeof(M562_PLAYER));
}

/* 25 insns: item hook 0 matrix, fetched once per frame. */
MtxPtr fn_1_7044(M562_PLAYER *player)
{
    if (player->unk128 == 0) {
        Hu3DModelObjMtxGet(player->unk024, CharModelItemHookGet(player->unk018, 2, 0), player->unk0C8);
        player->unk128 = 1;
    }
    return player->unk0C8;
}

/* 25 insns: item hook 1 matrix, fetched once per frame. */
MtxPtr fn_1_70A8(M562_PLAYER *player)
{
    if (player->unk12C == 0) {
        Hu3DModelObjMtxGet(player->unk024, CharModelItemHookGet(player->unk018, 2, 1), player->unk0F8);
        player->unk12C = 1;
    }
    return player->unk0F8;
}

/* 26 insns: gravity while airborne. */
void fn_1_710C(M562_PLAYER *player)
{
    if (player->unk0A0.y > 0.0f) {
        player->unk0C4 -= 1.5f;
        player->unk0A0.y += player->unk0C4;
    } else {
        player->unk0C4 = 0.0f;
        player->unk0A0.y = 0.0f;
    }
}

/* 497 insns: player exec (main fn_1_1330). */
s32 fn_1_7174(M562_PLAYER *player)
{
    float t;
    float sx;
    float sy;
    HU3DMODELID mdlId;
    M562_WORK *work;
    M562_PAD *pad;

    pad = &player->unk06C;
    work = player->unk000;
    if (player->unk010 != 0) {
        if (player->unk010 & 1) {
            Hu3DModelAttrSet(player->unk024, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrReset(player->unk024, HU3D_ATTR_DISPOFF);
        }
        player->unk010--;
    } else {
        Hu3DModelAttrReset(player->unk024, HU3D_ATTR_DISPOFF);
    }
    if (player->unk00C == 0) {
        Hu3DModelAttrSet(player->unk024, HU3D_ATTR_DISPOFF);
    }
    if (player->unk012 != 0) {
        if (player->unk012 > 20) {
            t = (player->unk012 - 135) / 5.0f;
            t = 1.0f - M562_CLAMP01(t);
            sx = 1.0f + 0.5f * t;
            sy = 0.05f + 0.95f * (1.0f - t);
            Hu3DModelScaleSet(player->unk024, sx, sy, sx);
        } else {
            t = player->unk012 / 20.0f;
            t = M562_CLAMP01(t);
            sx = 1.0f + 0.5f * t;
            sy = 0.05f + 0.95f * (1.0f - t);
            Hu3DModelScaleSet(player->unk024, sx, sy, sx);
        }
        player->unk012--;
    } else {
        Hu3DModelScaleSet(player->unk024, 1.0f, 1.0f, 1.0f);
    }
    if (work->unk000C >= 7) {
        player->unk010 = player->unk012 = 0;
        player->unk004 = 0;
    }
    pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
    if (player->unk088 != 0) {
        fn_1_B110(pad);
    }
    if (work->unk000E != 1 && work->unk000E != 4 && player->unk004 == 2) {
        player->unk004 = 1;
        player->unk006 = 0;
    }
    switch (player->unk004) {
        case 0:
            break;
        case 1:
            fn_1_7D58(player);
            break;
        case 2:
            fn_1_8DF8(player);
            break;
        case 3:
            if (fn_1_9C3C(player)) {
                player->unk008 = 0;
                player->unk004 = 1;
            }
            break;
        case 4:
            if (fn_1_A02C(player)) {
                player->unk008 = 0;
                player->unk004 = 1;
            }
            break;
        case 5:
            if (fn_1_A48C(player)) {
                player->unk008 = 0;
                player->unk004 = 1;
            }
            break;
        case 6:
            if (fn_1_A87C(player)) {
                player->unk008 = 0;
                player->unk004 = 1;
            }
            break;
    }
    mdlId = player->unk024;
    if (player->unk098 != player->unk09A) {
        if (Hu3DMotionShiftIDGet(mdlId) < 0) {
            if (player->unk098 == 6 || player->unk098 == 7 || player->unk098 == 8 || player->unk098 == 9 || player->unk098 == 10) {
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_OVL_LOOP);
                Hu3DMotionOverlayReset(mdlId);
            }
            fn_1_7938(player);
        }
    } else if (player->unk098 == 28) {
        if (Hu3DMotionTimeGet(mdlId) >= Hu3DMotionMaxTimeGet(mdlId)) {
            Hu3DMotionTimeSet(mdlId, 75.0f);
        }
    }
    if (work->unk000E < 4) {
        player->unk0A0.x = (player->unk0A0.x > 575.0f) ? 575.0f : ((player->unk0A0.x < -575.0f) ? -575.0f : player->unk0A0.x);
        player->unk0A0.z = (player->unk0A0.z > 450.0f) ? 450.0f : ((player->unk0A0.z < -450.0f) ? -450.0f : player->unk0A0.z);
    } else {
        player->unk0A0.x = (player->unk0A0.x > 1075.0f) ? 1075.0f : ((player->unk0A0.x < -1075.0f) ? -1075.0f : player->unk0A0.x);
        player->unk0A0.z = (player->unk0A0.z > 550.0f) ? 550.0f : ((player->unk0A0.z < -350.0f) ? -350.0f : player->unk0A0.z);
    }
    omSetTra(player->unk020, player->unk0A0.x, player->unk0A0.y, player->unk0A0.z);
    omSetRot(player->unk020, player->unk0AC.x, player->unk0AC.y, player->unk0AC.z);
    player->unk128 = 0;
    player->unk12C = 0;
    return 0;
}

/* 264 insns: start the requested motion (base shift + overlay for motions 6..10). */
void fn_1_7938(M562_PLAYER *player)
{
    float shift;
    HU3DMODELID mdlId;

    mdlId = player->unk024;
    if (player->unk09A == 6 || player->unk09A == 7 || player->unk09A == 8 || player->unk09A == 9 || player->unk09A == 10) {
        player->unk098 = player->unk09A;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_OVL_LOOP);
        switch (player->unk09A) {
            case 6:
                Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[0], 0.0f, 4.0f, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
                Hu3DMotionOverlaySet(mdlId, player->unk020->mtnId[player->unk098]);
                if (player->unk09C) {
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_OVL_LOOP);
                }
                break;
            case 7:
                Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[1], 0.0f, 4.0f, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
                Hu3DMotionOverlaySet(mdlId, player->unk020->mtnId[player->unk098]);
                if (player->unk09C) {
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_OVL_LOOP);
                }
                break;
            case 8:
                Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[2], 0.0f, 4.0f, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
                Hu3DMotionOverlaySet(mdlId, player->unk020->mtnId[player->unk098]);
                if (player->unk09C) {
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_OVL_LOOP);
                }
                break;
            case 9:
                Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[3], 0.0f, 4.0f, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
                Hu3DMotionOverlaySet(mdlId, player->unk020->mtnId[player->unk098]);
                if (player->unk09C) {
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_OVL_LOOP);
                }
                break;
            case 10:
                Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[0], 0.0f, 4.0f, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
                Hu3DMotionOverlaySet(mdlId, player->unk020->mtnId[player->unk098]);
                if (player->unk09C) {
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_OVL_LOOP);
                }
                break;
        }
    } else {
        shift = (player->unk098 == 28) ? 15.0f : 4.0f;
        player->unk098 = player->unk09A;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(mdlId, player->unk020->mtnId[player->unk098], 0.0f, shift, player->unk09C ? HU3D_MOTATTR_LOOP : 0);
    }
}

/* 790 insns: mode 1 -- walk, jump (A), catch a fireball / sun bomb (B). */
void fn_1_7D58(M562_PLAYER *player)
{
    HuVecF vel;
    float scale;
    float angle;
    M562_FIREOBJ *fire;
    M562_SUNBOMBOBJ *bomb;
    M562_PAD *pad;
    M562_WORK *work;

    work = player->unk000;
    pad = &player->unk06C;
    player->unk0C0 = 10.0f * (sqrtf((float)pad->unk10 * (float)pad->unk10 + (float)pad->unk11 * (float)pad->unk11) / 56.0f);
    angle = 0.0f;
    if (player->unk0C0 >= 0.001f && player->unk006 != 4) {
        angle = M562_ANGLEWRAP(HuAtan(pad->unk10, -pad->unk11));
    }
    switch (player->unk006) {
        case 0:
            player->unk09A = 0;
            player->unk09C = 1;
            if (player->unk0C0 >= 0.001f) {
                if (player->unk0C0 > 6.0f) {
                    player->unk09A = 2;
                    player->unk09C = 1;
                } else {
                    player->unk09A = 1;
                    player->unk09C = 1;
                }
                player->unk094 = angle;
            }
            fn_1_710C(player);
            if (pad->unk0C & PAD_BUTTON_A) {
                player->unk09A = 3;
                player->unk09C = 0;
                player->unk0C4 = sqrtf(600.0f);
                player->unk006 = 1;
            } else if (pad->unk0C & PAD_BUTTON_B) {
                if (work->unk000E == 1 || work->unk000E == 4) {
                    player->unk09A = 5;
                    player->unk09C = 0;
                    fn_1_89B0(player);
                    if (work->unk000E == 1) {
                        fire = player->unk130;
                        if (fire) {
                            if (fire->unk10 < 5) {
                                player->unk00A = 0;
                                player->unk006 = 4;
                                player->unk094 = player->unk090;
                            } else {
                                player->unk130 = NULL;
                            }
                        }
                    } else if (work->unk000E == 4) {
                        bomb = player->unk134;
                        if (bomb) {
                            player->unk00A = 0;
                            player->unk006 = 4;
                            player->unk094 = player->unk090;
                        }
                    }
                    if (!player->unk130 && !player->unk134) {
                        player->unk006 = 5;
                    }
                }
            }
            break;
        case 1:
            if (!(pad->unk08 & PAD_BUTTON_A) && player->unk0C4 > 0.0f) {
                player->unk0C4 *= 0.5f;
            }
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 4;
                player->unk09C = 0;
                player->unk006 = 2;
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 2:
            if (player->unk098 == 4) {
                player->unk09A = 0;
                player->unk09C = 1;
                player->unk006 = 0;
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 3:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 4;
                player->unk09C = 0;
                player->unk006 = 2;
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 4:
            player->unk0C0 = 0.0f;
            scale = player->unk00A / 30.0f;
            fn_1_8C50(player, scale);
            if (++player->unk00A >= 30) {
                fn_1_8C50(player, 1.0f);
                player->unk09A = 6;
                player->unk09C = 1;
                player->unk00A = 0;
                player->unk004 = 2;
                player->unk006 = 0;
            }
            break;
        case 5:
            player->unk0C0 = 0.0f;
            if (player->unk098 == 5) {
                if (Hu3DMotionTimeGet(player->unk024) >= Hu3DMotionMaxTimeGet(player->unk024)) {
                    player->unk09A = 0;
                    player->unk09C = 1;
                    player->unk006 = 0;
                }
            }
            break;
    }
    player->unk090 = fn_1_36EC(player->unk094, player->unk090, 0.4f);
    scale = (player->unk012 != 0) ? 0.5f : 1.0f;
    vel.x = scale * (player->unk0C0 * HuSin(player->unk090));
    vel.z = scale * (player->unk0C0 * HuCos(player->unk090));
    player->unk0A0.x += vel.x;
    player->unk0A0.z += vel.z;
    player->unk0AC.y = player->unk090;
}

/* 71 insns: find a catchable fireball (phase 1) or sun bomb (phase 4) in front of the player. */
s32 fn_1_89B0(M562_PLAYER *player)
{
    s32 i;
    M562_WORK *work;
    M562_FIREOBJ *fire;
    M562_FIRE *fireMgr;
    M562_KOOPABOSS *boss;
    M562_SUNBOMB *sunbomb;
    M562_SUNBOMBOBJ *bomb;

    work = player->unk000;
    fireMgr = &work->fire;
    boss = &work->koopaboss;
    sunbomb = &boss->unk14C;
    player->unk130 = NULL;
    player->unk134 = NULL;
    if (work->unk000E == 1) {
        for (i = 0; i < 35; i++) {
            fire = &fireMgr->unk000C[i];
            if (fire->unk10 != 7 && fn_1_8ACC(&player->unk0A0, &fire->unk44, player->unk090)) {
                player->unk130 = fire;
                return 1;
            }
        }
    } else if (work->unk000E == 4) {
        for (i = 0; i < 5; i++) {
            bomb = &sunbomb->unk004[i];
            if (fn_1_8ACC(&player->unk0A0, &bomb->unk38, player->unk090) && bomb->unk04 >= 5 && bomb->unk04 < 9) {
                player->unk134 = bomb;
                return 1;
            }
        }
    }
    return 0;
}

/* 97 insns: target within 150 units and within 60 degrees of the facing direction. */
s32 fn_1_8ACC(HuVecF *pos, HuVecF *target, float yaw)
{
    HuVecF dir;
    HuVecF norm;
    HuVecF fwd;
    float dist;
    float dot;

    PSVECSubtract(target, pos, &dir);
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (dist < 150.0f) {
        if (!dir.x && !dir.z) {
            dir.z = 1.0f;
        }
        PSVECNormalize(&dir, &norm);
        fwd.x = HuSin(yaw);
        fwd.y = 0.0f;
        fwd.z = HuCos(yaw);
        dot = PSVECDotProduct(&norm, &fwd);
        if (dot >= cos(M_PI / 3.0)) {
            return 1;
        }
    }
    return 0;
}

/* 106 insns: pull the held object toward the hand (t = 0..1). */
void fn_1_8C50(M562_PLAYER *player, float t)
{
    HuVecF hand;
    HuVecF d;
    MtxPtr mtx;
    M562_FIREOBJ *fire;
    M562_SUNBOMBOBJ *bomb;
    M562_WORK *work;

    work = player->unk000;
    fire = player->unk130;
    bomb = player->unk134;
    mtx = fn_1_7044(player);
    Hu3DMtxTransGet(mtx, &hand);
    if (work->unk000E == 1) {
        PSVECSubtract(&hand, &fire->unk44, &d);
        PSVECScale(&d, &d, t);
        PSVECAdd(&fire->unk44, &d, &fire->unk44);
        fire->unk34 = fn_1_36EC(player->unk090, fire->unk34, 1.0f - t);
        fire->unk50.y = fire->unk34;
        fire->unk10 = 4;
        fire->unk12 = 0;
        fire->unk14 = 0;
        if (fire->unk6C >= 3 && (player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
            player->unk00A = 0;
            player->unk006 = 0;
            player->unk008 = 0;
            player->unk004 = 4;
        }
    } else if (work->unk000E == 4) {
        PSVECSubtract(&hand, &bomb->unk38, &d);
        PSVECScale(&d, &d, t);
        PSVECAdd(&bomb->unk38, &d, &bomb->unk38);
    }
}

/* 767 insns: mode 2 -- carrying: walk, jump (A), throw (B, or the phase timer). */
void fn_1_8DF8(M562_PLAYER *player)
{
    HuVecF vel;
    float scale;
    float angle;
    M562_PAD *pad;
    M562_WORK *work;

    work = player->unk000;
    pad = &player->unk06C;
    fn_1_99F4(player);
    player->unk0C0 = 10.0f * (sqrtf((float)pad->unk10 * (float)pad->unk10 + (float)pad->unk11 * (float)pad->unk11) / 56.0f);
    angle = 0.0f;
    if (player->unk0C0 >= 0.001f) {
        angle = M562_ANGLEWRAP(HuAtan(pad->unk10, -pad->unk11));
    }
    if (work->unk000E == 4) {
        player->unk0C0 *= 0.6f;
    }
    switch (player->unk006) {
        case 0:
            player->unk09A = 6;
            player->unk09C = 1;
            if (player->unk0C0 >= 0.001f) {
                if (work->unk000E == 4) {
                    player->unk09A = 7;
                    player->unk09C = 1;
                } else if (player->unk0C0 > 6.0f) {
                    player->unk09A = 8;
                    player->unk09C = 1;
                } else {
                    player->unk09A = 7;
                    player->unk09C = 1;
                }
                player->unk094 = angle;
            }
            fn_1_710C(player);
            if (pad->unk0C & PAD_BUTTON_A) {
                player->unk09A = 9;
                player->unk09C = 0;
                player->unk0C4 = sqrtf(600.0f);
                player->unk006 = 1;
            } else if ((pad->unk0C & PAD_BUTTON_B) || work->unk000C > 4) {
                player->unk09A = 11;
                player->unk09C = 0;
                player->unk006 = 4;
            }
            break;
        case 1:
            if (!(pad->unk08 & PAD_BUTTON_A) && player->unk0C4 > 0.0f) {
                player->unk0C4 *= 0.5f;
            }
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if ((pad->unk0C & PAD_BUTTON_B) || work->unk000C > 4) {
                player->unk09A = 11;
                player->unk09C = 0;
                player->unk006 = 5;
                break;
            }
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 10;
                player->unk09C = 0;
                player->unk006 = 2;
                CharModelLandDustCreate(player->unk018, &player->unk0A0);
                CharFXPlay(player->unk018, 150);
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 2:
            if (player->unk098 == 10) {
                player->unk09A = 6;
                player->unk09C = 1;
                player->unk006 = 0;
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 3:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if ((pad->unk0C & PAD_BUTTON_B) || work->unk000C > 4) {
                player->unk09A = 11;
                player->unk09C = 0;
                player->unk006 = 5;
                break;
            }
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 10;
                player->unk09C = 0;
                player->unk006 = 2;
                CharModelLandDustCreate(player->unk018, &player->unk0A0);
                CharFXPlay(player->unk018, 150);
            }
            if (player->unk0C0 >= 0.001f) {
                player->unk094 = angle;
            }
            break;
        case 4:
            if (player->unk098 == 11) {
                fn_1_9AEC(player);
                player->unk09A = 0;
                player->unk09C = 1;
                player->unk004 = 1;
                player->unk006 = 0;
            }
            break;
        case 5:
            if (player->unk098 == 11) {
                fn_1_9AEC(player);
                player->unk09A = 3;
                player->unk09C = 0;
                player->unk004 = 1;
                player->unk006 = 1;
            }
            break;
    }
    player->unk090 = fn_1_36EC(player->unk094, player->unk090, 0.4f);
    scale = (player->unk012 != 0) ? 0.5f : 1.0f;
    vel.x = scale * (player->unk0C0 * HuSin(player->unk090));
    vel.z = scale * (player->unk0C0 * HuCos(player->unk090));
    player->unk0A0.x += vel.x;
    player->unk0A0.z += vel.z;
    player->unk0AC.y = player->unk090;
}

/* 62 insns: keep the held object in the hand. */
void fn_1_99F4(M562_PLAYER *player)
{
    HuVecF hand;
    MtxPtr mtx;
    M562_FIREOBJ *fire;
    M562_SUNBOMBOBJ *bomb;
    M562_WORK *work;

    work = player->unk000;
    fire = player->unk130;
    bomb = player->unk134;
    mtx = fn_1_7044(player);
    Hu3DMtxTransGet(mtx, &hand);
    if (work->unk000E == 1) {
        if (fire) {
            fire->unk44 = hand;
            fire->unk34 = fire->unk38 = player->unk090;
            fire->unk50.y = fire->unk34;
        }
    } else if (work->unk000E == 4) {
        if (bomb) {
            bomb->unk38 = hand;
        }
    }
}

/* 84 insns: throw (or drop) the held object. */
void fn_1_9AEC(M562_PLAYER *player)
{
    M562_FIREOBJ *fire;
    M562_SUNBOMBOBJ *bomb;
    M562_WORK *work;

    work = player->unk000;
    fire = player->unk130;
    bomb = player->unk134;
    if (work->unk000E == 1) {
        if (fire) {
            fire->unk10 = 5;
            fire->unk12 = 0;
            fire->unk14 = 0;
        }
    } else if (work->unk000E == 4) {
        if (bomb) {
            bomb->unk6C = 0.8f * (10.0 * HuSin(player->unk090));
            bomb->unk74 = 0.8f * (10.0 * HuCos(player->unk090));
            bomb->unk68 = 20.0f;
        }
    }
    player->unk130 = NULL;
    player->unk134 = NULL;
}

/* 252 insns: mode 3 -- hit: lose 1 HP, drop what is held, bounce, lie down, get up. */
s32 fn_1_9C3C(M562_PLAYER *player)
{
    s32 ret;

    ret = 0;
    switch (player->unk006) {
        case 0:
            player->unk08C--;
            omVibrate(player->unk014, 30, 4, 2);
            if (player->unk130 || player->unk134) {
                fn_1_9AEC(player);
            }
            player->unk09A = 12;
            player->unk09C = 1;
            player->unk0C4 = sqrtf(1200.0f);
            player->unk006 = 1;
        case 1:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 14;
                player->unk09C = 1;
                player->unk00A = 60;
                player->unk006 = 2;
            }
            break;
        case 2:
            if (player->unk00A-- <= 0) {
                player->unk09A = 15;
                player->unk09C = 0;
                player->unk00A = 60;
                player->unk006 = 3;
            }
            break;
        case 3:
            if (player->unk098 == 15) {
                if (Hu3DMotionTimeGet(player->unk024) >= Hu3DMotionMaxTimeGet(player->unk024)) {
                    player->unk00A = 0;
                    player->unk006 = 0;
                    player->unk010 = 90;
                    ret = 1;
                }
            }
            break;
    }
    return ret;
}

/* 280 insns: mode 4 -- hit while catching a big fireball (fn_1_8C50): as mode 3 plus CharFXPlay 505, gravity on the ground. */
s32 fn_1_A02C(M562_PLAYER *player)
{
    s32 ret;

    ret = 0;
    switch (player->unk006) {
        case 0:
            player->unk08C--;
            omVibrate(player->unk014, 30, 4, 2);
            CharFXPlay(player->unk018, 505);
            if (player->unk130 || player->unk134) {
                fn_1_9AEC(player);
            }
            player->unk09A = 13;
            player->unk09C = 1;
            player->unk0C4 = sqrtf(1200.0f);
            player->unk006 = 1;
        case 1:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 14;
                player->unk09C = 1;
                player->unk00A = 60;
                player->unk006 = 2;
            }
            break;
        case 2:
            fn_1_710C(player);
            if (player->unk00A-- <= 0) {
                player->unk09A = 15;
                player->unk09C = 0;
                player->unk00A = 60;
                player->unk006 = 3;
            }
            break;
        case 3:
            if (player->unk098 == 15) {
                if (Hu3DMotionTimeGet(player->unk024) >= Hu3DMotionMaxTimeGet(player->unk024)) {
                    player->unk00A = 0;
                    player->unk006 = 0;
                    player->unk010 = 90;
                    ret = 1;
                }
            }
            break;
    }
    return ret;
}

/* 252 insns: mode 5 -- hit: face yaw 0, show model 0x750020 rising 200 and falling back over 93 frames. */
s32 fn_1_A48C(M562_PLAYER *player)
{
    float t;
    s32 ret;

    ret = 0;
    switch (player->unk006) {
        case 0:
            player->unk08C--;
            omVibrate(player->unk014, 30, 4, 2);
            if (player->unk130 || player->unk134) {
                fn_1_9AEC(player);
            }
            player->unk094 = player->unk090 = 0.0f;
            player->unk0AC.y = player->unk090;
            Hu3DModelPosSet(player->unk064, player->unk0A0.x, player->unk0A0.y, player->unk0A0.z);
            Hu3DModelAttrReset(player->unk064, HU3D_ATTR_DISPOFF);
            player->unk09A = 17;
            player->unk09C = 0;
            player->unk00A = 0;
            player->unk006 = 1;
        case 1:
            t = player->unk00A / 93.0f;
            Hu3DModelPosSet(player->unk064, player->unk0A0.x, player->unk0A0.y + 200.0 * HuSin(180.0f * t), player->unk0A0.z);
            if (++player->unk00A >= 93) {
                Hu3DModelAttrSet(player->unk064, HU3D_ATTR_DISPOFF);
                player->unk09A = 14;
                player->unk09C = 1;
                player->unk00A = 60;
                player->unk006 = 2;
            }
            break;
        case 2:
            fn_1_710C(player);
            if (player->unk00A-- <= 0) {
                player->unk09A = 15;
                player->unk09C = 0;
                player->unk00A = 60;
                player->unk006 = 3;
            }
            break;
        case 3:
            if (player->unk098 == 15) {
                if (Hu3DMotionTimeGet(player->unk024) >= Hu3DMotionMaxTimeGet(player->unk024)) {
                    player->unk00A = 0;
                    player->unk006 = 0;
                    player->unk010 = 90;
                    ret = 1;
                }
            }
            break;
    }
    return ret;
}

/* 315 insns: mode 6 -- knocked away by Koopa along his facing direction. */
s32 fn_1_A87C(M562_PLAYER *player)
{
    s32 ret;
    M562_KOOPA *koopa;
    M562_WORK *work;

    work = player->unk000;
    koopa = &work->koopa;
    ret = 0;
    switch (player->unk006) {
        case 0:
            player->unk08C--;
            omVibrate(player->unk014, 30, 4, 2);
            if (player->unk130 || player->unk134) {
                fn_1_9AEC(player);
            }
            player->unk09A = 12;
            player->unk09C = 1;
            player->unk0C4 = sqrtf(1200.0f);
            player->unk006 = 1;
        case 1:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            player->unk0A0.x += 10.0 * HuSin(koopa->angle);
            player->unk0A0.z += 10.0 * HuCos(koopa->angle);
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 14;
                player->unk09C = 1;
                player->unk00A = 60;
                player->unk006 = 2;
            }
            break;
        case 2:
            fn_1_710C(player);
            if (player->unk00A-- <= 0) {
                player->unk09A = 15;
                player->unk09C = 0;
                player->unk00A = 60;
                player->unk006 = 3;
            }
            break;
        case 3:
            if (player->unk098 == 15) {
                if (Hu3DMotionTimeGet(player->unk024) >= Hu3DMotionMaxTimeGet(player->unk024)) {
                    player->unk00A = 0;
                    player->unk006 = 0;
                    player->unk010 = 90;
                    ret = 1;
                }
            }
            break;
    }
    return ret;
}

/* 12 insns: called from fire.c: switch to the falling step (3) of mode 1/2 (while carrying, only if earlier). */
void fn_1_AD68(M562_PLAYER *player)
{
    if (player->unk004 == 2) {
        if (player->unk006 < 3) {
            player->unk006 = 3;
        }
    } else {
        player->unk006 = 3;
    }
}

/* 185 insns: turn toward dir (events); returns 1 once facing it within 3 degrees. */
s32 fn_1_AD98(M562_PLAYER *player, HuVecF *dir, float rate)
{
    HuVecF fwd;
    HuVecF d;
    float angle;
    float diff;
    float dot;
    float rad;
    s32 ret;

    ret = 0;
    fwd.x = HuSin(player->unk090);
    fwd.y = 0.0f;
    fwd.z = HuCos(player->unk090);
    d.x = dir->x;
    d.y = 0.0f;
    d.z = dir->z;
    if (d.x || d.z) {
        PSVECNormalize(&d, &d);
    } else {
        d.z = 1.0f;
    }
    dot = PSVECDotProduct(&fwd, &d);
    rad = acos(dot);
    diff = 180.0 * (rad / M_PI);
    angle = HuAtan(d.x, d.z);
    angle = M562_ANGLEWRAP(angle);
    if (M562_ABS(diff) > 3.0f) {
        player->unk09A = 1;
        player->unk09C = 1;
        player->unk090 = fn_1_36EC(angle, player->unk090, rate);
        player->unk0AC.y = player->unk090;
    } else {
        player->unk09A = 0;
        player->unk09C = 1;
        ret = 1;
    }
    return ret;
}

/* 25 insns: pad init. */
void fn_1_B07C(M562_PAD *pad, s32 playerNo, M562_PLAYER *player)
{
    memset(pad, 0, sizeof(M562_PAD));
    pad->unk00 = player;
    pad->unk04 = GwPlayerConf[playerNo].padNo;
}

/* 12 insns: pad kill. */
void fn_1_B0E0(M562_PAD *pad)
{
    memset(pad, 0, sizeof(M562_PAD));
}

/* 116 insns: read the pad (stick dead zone 10). */
void fn_1_B110(M562_PAD *pad)
{
    pad->unk08 = HuPadBtn[pad->unk04];
    pad->unk0C = HuPadBtnDown[pad->unk04];
    pad->unk12 = HuPadBtnRep[pad->unk04];
    pad->unk10 = HuPadStkX[pad->unk04];
    pad->unk10 = (M562_ABS(pad->unk10) < 10) ? 0 : pad->unk10;
    pad->unk11 = HuPadStkY[pad->unk04];
    pad->unk11 = (M562_ABS(pad->unk11) < 10) ? 0 : pad->unk11;
    pad->unk14 = HuPadSubStkX[pad->unk04];
    pad->unk15 = HuPadSubStkY[pad->unk04];
    pad->unk16 = HuPadTrigL[pad->unk04];
    pad->unk17 = HuPadTrigR[pad->unk04];
    pad->unk18 = HuPadDStk[pad->unk04];
    pad->unk19 = HuPadDStkRep[pad->unk04];
}
