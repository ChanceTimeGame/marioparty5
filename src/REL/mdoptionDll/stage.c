/*
 * mdoptiondll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mdoptiondll/asm/REL/mdoptiondll/stage.s.
 */

#define MDOPTION_H2D_PROTO /* CW only: see mdoptiondll.gen.h */
#include "REL/mdoptionDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "messnum/mgname.h"
#include "game/disp.h"
#include "game/frand.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_388 = 0.6f; /* 0x388 */
static const float lbl_1_rodata_38C = 0.0f; /* 0x38C */
static const float lbl_1_rodata_390 = 1.0f; /* 0x390 */
static const float lbl_1_rodata_394 = -56.0f; /* 0x394 */
static const float lbl_1_rodata_398 = -155.0f; /* 0x398 */
static const float lbl_1_rodata_39C = -147.0f; /* 0x39C */
static const float lbl_1_rodata_3A0 = -288.0f; /* 0x3A0 */
static const float lbl_1_rodata_3A4 = -112.0f; /* 0x3A4 */
/* 0x3A8 lbl_1_rodata_3A8 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x3B0 lbl_1_rodata_3B0 (0xC): 0x00000000 0x00000000 0x44FA0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_3BC = 0.28f; /* 0x3BC */
/* 0x3C0 lbl_1_rodata_3C0 (0xC): 0x00000000 0x00000000 0x44FA0000 -- an aggregate initialiser, write it as a local */
/* 0x3CC lbl_1_rodata_3CC (0xC): 0x00000000 0x00000000 0x447A0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_3D8 = -204.0f; /* 0x3D8 */
static const float lbl_1_rodata_3DC = 15.0f; /* 0x3DC */
static const float lbl_1_rodata_3E0 = 0.4f; /* 0x3E0 */
static const float lbl_1_rodata_3E4 = -10.0f; /* 0x3E4 */
static const float lbl_1_rodata_3E8 = 115.0f; /* 0x3E8 */
static const float lbl_1_rodata_3EC = 0.75f; /* 0x3EC */
static const float lbl_1_rodata_3F0 = -94.0f; /* 0x3F0 */
static const float lbl_1_rodata_3F4 = -88.0f; /* 0x3F4 */
static const float lbl_1_rodata_3F8 = 0.84f; /* 0x3F8 */
static const float lbl_1_rodata_3FC = -180.0f; /* 0x3FC */
static const float lbl_1_rodata_400 = -20.0f; /* 0x400 */
static const float lbl_1_rodata_404 = 50.0f; /* 0x404 */
static const float lbl_1_rodata_408 = 1.6666666f; /* 0x408 */
/* 0x410 lbl_1_rodata_410 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x418 lbl_1_rodata_418 (0x20): 0x001F003F 0x001F0040 0x001F0041 0x001F0042 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0x438 lbl_1_rodata_438 (0x20): 0x001F003F 0x001F0040 0x001F0041 0x001F0042 0x001F0043 0x001F0044 0x001F0045 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_458 = 150.0f; /* 0x458 */
static const float lbl_1_rodata_45C = 116.0f; /* 0x45C */
static const float lbl_1_rodata_460 = -138.0f; /* 0x460 */
static const float lbl_1_rodata_464 = -80.0f; /* 0x464 */
static const float lbl_1_rodata_468 = 26.0f; /* 0x468 */
static const float lbl_1_rodata_46C = 402.0f; /* 0x46C */
static const float lbl_1_rodata_470 = 300.0f; /* 0x470 */
static const float lbl_1_rodata_474 = 114.0f; /* 0x474 */
static const float lbl_1_rodata_478 = 108.0f; /* 0x478 */
static const float lbl_1_rodata_47C = 350.0f; /* 0x47C */
static const float lbl_1_rodata_480 = 62.0f; /* 0x480 */
static const float lbl_1_rodata_484 = 60.0f; /* 0x484 */
static const float lbl_1_rodata_488 = -228.0f; /* 0x488 */
/* 0x48C lbl_1_rodata_48C (0x20): 0x001F003F 0x001F0040 0x001F0041 0x001F0042 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0x4AC lbl_1_rodata_4AC (0x20): 0x001F003F 0x001F0040 0x001F0041 0x001F0042 0x001F0043 0x001F0044 0x001F0045 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0x4CC lbl_1_rodata_4CC (0x68): 0x00920003 0x00920004 0x00920005 0x00920006 0x00920018 0x00920007 0x00920008 0x00920009 0x0092000A 0x0092000B 0x0092000C 0x0092000D 0x0092000E 0x00920011 0x0092000E 0x0092000F 0x00920010 0x00920013 0x00920012 0x00920016 0x00920017 0x00920014 0x00920015 0x0092000E 0x0092000F 0x00920010 -- an aggregate initialiser, write it as a local */
/* 0x534 lbl_1_rodata_534 (0x10): 0xC3820000 0xC3BE0000 0xC3FA0000 0xC41EC000 -- an aggregate initialiser, write it as a local */
/* 0x544 lbl_1_rodata_544 (0x8): 0x00920019 0x0092001A -- an aggregate initialiser, write it as a local */
/* 0x54C lbl_1_rodata_54C (0x10): 0x0092001E 0x0092001D 0x0092001C 0x0092001B -- an aggregate initialiser, write it as a local */
/* 0x55C lbl_1_rodata_55C (0xC): 0x43900000 0x43480000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x568 lbl_1_rodata_568 (0xC): 0x00000000 0x00000000 0x3D75C28F -- an aggregate initialiser, write it as a local */
/* 0x574 lbl_1_rodata_574 (0xC): 0x00000000 0x00000000 0x3D75C28F -- an aggregate initialiser, write it as a local */
/* 0x580 lbl_1_rodata_580 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_584 = 90.0f; /* 0x584 */
static const float lbl_1_rodata_588 = 0.5f; /* 0x588 */
static const float lbl_1_rodata_58C = -0.005f; /* 0x58C */
/* 0x590 lbl_1_rodata_590 (0xC): 0x00000000 0x41400000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_59C = 20.0f; /* 0x59C */
/* 0x5A0 lbl_1_rodata_5A0 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x5A1 lbl_1_rodata_5A1 (0x3): 0x00, 0x00, 0x80 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5A4 = 8.0f; /* 0x5A4 */
static const float lbl_1_rodata_5A8 = 640.0f; /* 0x5A8 */
static const float lbl_1_rodata_5AC = 480.0f; /* 0x5AC */
static const float lbl_1_rodata_5B0 = -16777215.0f; /* 0x5B0 */
static const float lbl_1_rodata_5B4 = -90.0f; /* 0x5B4 */
static const float lbl_1_rodata_5B8 = 130.0f; /* 0x5B8 */
static const float lbl_1_rodata_5BC = 0.25f; /* 0x5BC */
static const float lbl_1_rodata_5C0 = 10.0f; /* 0x5C0 */
/* 0x5C4 lbl_1_rodata_5C4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5D0 = 2.0f; /* 0x5D0 */
static const float lbl_1_rodata_5D4 = 380.0f; /* 0x5D4 */
static const float lbl_1_rodata_5D8 = 360.0f; /* 0x5D8 */
static const float lbl_1_rodata_5DC = 0.017453292f; /* 0x5DC */
/* 0x5E0 lbl_1_rodata_5E0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x5EC lbl_1_rodata_5EC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_5F8 = 5.0; /* 0x5F8 */
static const double lbl_1_rodata_600 = 3.141592653589793; /* 0x600 */
static const float lbl_1_rodata_608 = 2160.0f; /* 0x608 */
static const float lbl_1_rodata_60C = 180.0f; /* 0x60C */
static const double lbl_1_rodata_610 = 180.0; /* 0x610 */
static const float lbl_1_rodata_618 = 4.0f; /* 0x618 */
static const float lbl_1_rodata_61C = -40.0f; /* 0x61C */
static const float lbl_1_rodata_620 = 11.0f; /* 0x620 */
static const float lbl_1_rodata_624 = 400.0f; /* 0x624 */
/* 0x628 lbl_1_rodata_628 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x634 lbl_1_rodata_634 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_640 = 30.0f; /* 0x640 */
static const float lbl_1_rodata_644 = -1.0f; /* 0x644 */
static const float lbl_1_rodata_648 = 500.0f; /* 0x648 */
static const float lbl_1_rodata_64C = 45.0f; /* 0x64C */
static const float lbl_1_rodata_650 = 0.09f; /* 0x650 */
static const float lbl_1_rodata_654 = -0.02f; /* 0x654 */
/* 0x658 lbl_1_rodata_658 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_65C = 1.2f; /* 0x65C */
static const float lbl_1_rodata_660 = -0.5f; /* 0x660 */
static const float lbl_1_rodata_664 = 0.8f; /* 0x664 */
static const float lbl_1_rodata_668 = 288.0f; /* 0x668 */
static const float lbl_1_rodata_66C = -128.0f; /* 0x66C */
static const float lbl_1_rodata_670 = 192.0f; /* 0x670 */
static const float lbl_1_rodata_674 = 64.0f; /* 0x674 */

static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx);
static void LayerHook(s16 layerNo);
static void WaveEffectHook(s16 layerNo);
static void WaveEffectDrawHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x688 */ static u32 SpriteAnimFile[40] = { DATANUM(DATA_mdoption, 38), DATANUM(DATA_mdoption, 39), DATANUM(DATA_mdoption, 51), DATANUM(DATA_mdoption, 75), DATANUM(DATA_mdoption, 40), DATANUM(DATA_mdoption, 78), DATANUM(DATA_mdoption, 44), DATANUM(DATA_mdoption, 45), DATANUM(DATA_mdoption, 46), DATANUM(DATA_mdoption, 47), DATANUM(DATA_mdoption, 41), DATANUM(DATA_mdoption, 42), DATANUM(DATA_mdoption, 43), DATANUM(DATA_mdoption, 48), DATANUM(DATA_mdoption, 49), DATANUM(DATA_mdoption, 50), DATANUM(DATA_mdoption, 52), DATANUM(DATA_mdoption, 53), DATANUM(DATA_mdoption, 54), DATANUM(DATA_mdoption, 55), DATANUM(DATA_mdoption, 56), DATANUM(DATA_mdoption, 57), DATANUM(DATA_mdoption, 58), DATANUM(DATA_mdoption, 59), DATANUM(DATA_mdoption, 60), DATANUM(DATA_mdoption, 61), DATANUM(DATA_mdoption, 62), DATANUM(DATA_mdoption, 63), DATANUM(DATA_mdoption, 64), DATANUM(DATA_mdoption, 65), DATANUM(DATA_mdoption, 66), DATANUM(DATA_mdoption, 74), DATANUM(DATA_mdoption, 67), DATANUM(DATA_mdoption, 68), DATANUM(DATA_mdoption, 69), DATANUM(DATA_mdoption, 70), DATANUM(DATA_mdoption, 72), DATANUM(DATA_mdoption, 71), DATANUM(DATA_mdoption, 73), DATANUM(DATA_mdoption, 79) };

/* 63 insns */
void MdSpriteCreate(MDSPRITE_WORK *sprite)
{
    int i;
    for(i=0; i<MDSPR_ANIM_MAX; i++) {
        sprite->animP[i] = HuSprAnimRead(HuDataReadNum(SpriteAnimFile[i], HU_MEMNUM_OVL));
        HuSprAnimLock(sprite->animP[i]);
    }
    MdOptionSprGrpCreate(sprite, 0);
    MdOptionSprGrpCreate(sprite, 1);
    MdOptionSprGrpCreate(sprite, 7);
    HuSprDrawNoSet(sprite->grpId[1], 0, 63);
    sprite->unk2A0 = 0.6f;
    HuSprExecLayerCameraSet(64, sysP->camera->camera[0].bit, 5);
    HuSprExecLayerCameraSet(63, sysP->camera->camera[0].bit, 2);
}

/* 28 insns */
void MdSpriteFadeDispSet(BOOL dispF)
{
    if(dispF == FALSE) {
        HuSprDispOff(sysP->sprite->grpId[1], 0);
    } else {
        HuSprDispOn(sysP->sprite->grpId[1], 0);
    }
}

/* 0x728 */ static MDSPR_INFO SpriteInfo[247] = {
    { 0, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 0 */
    { 1, 2, { 0.0f, -126.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 1 */
    { 2, 2, { 0.0f, -128.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 2 */
    { 4, 2, { -206.0f, -108.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 3 */
    { 4, 2, { 206.0f, -108.0f }, { 1.0f, 1.0f }, 1.0f, 2 }, /* 4 */
    { 16, 2, { -188.0f, -132.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 5 */
    { 16, 2, { 188.0f, -132.0f }, { 1.0f, 1.0f }, 1.0f, 2 }, /* 6 */
    { 17, 2, { -188.0f, -132.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 7 */
    { 17, 2, { 188.0f, -132.0f }, { 1.0f, 1.0f }, 1.0f, 2 }, /* 8 */
    { 3, 2, { 0.0f, 0.0f }, { 72.0f, 6e+01f }, 0.5f, 0 }, /* 9 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 10 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 11 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 12 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 13 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 14 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 15 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 16 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 17 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 18 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 19 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 20 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 21 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 22 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 23 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 24 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 25 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 26 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 27 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 28 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 29 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 30 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 31 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 32 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 33 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 34 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 35 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 36 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 37 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 38 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 39 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 40 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 41 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 42 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 43 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 44 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 45 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 46 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 47 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 48 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 49 */
    { 15, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 50 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 51 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 52 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 53 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 54 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 55 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 56 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 57 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 58 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 59 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 60 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 61 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 62 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 63 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 64 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 65 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 66 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 67 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 68 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 69 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 70 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 71 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 72 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 73 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 74 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 75 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 76 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 77 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 78 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 79 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 80 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 81 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 82 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 83 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 84 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 85 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 86 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 87 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 88 */
    { 5, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 89 */
    { 6, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 90 */
    { 7, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 91 */
    { 8, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 92 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 93 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 94 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 95 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 96 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 97 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 98 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 99 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 100 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 101 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 102 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 103 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 104 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 105 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 106 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 107 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 108 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 109 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 110 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 111 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 112 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 113 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 114 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 115 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 116 */
    { 14, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 117 */
    { 14, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 118 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 119 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 120 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 121 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 122 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 123 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 124 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 125 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 126 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 127 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 128 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 129 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 130 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 131 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 132 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 133 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 134 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 135 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 136 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 137 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 138 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 139 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 140 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 141 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 142 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 143 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 144 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 145 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 146 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 147 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 148 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 149 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 150 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 151 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 152 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 153 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 154 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 155 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 156 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 157 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 158 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 159 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 160 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 161 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 162 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 163 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 164 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 165 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 166 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 167 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 168 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 169 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 170 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 171 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 172 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 173 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 174 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 175 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 176 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 177 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 178 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 179 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 180 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 181 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 182 */
    { 28, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 183 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 184 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 185 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 186 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 187 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 188 */
    { 13, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 189 */
    { 18, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 190 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 191 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 192 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 193 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 194 */
    { 11, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 195 */
    { 29, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 196 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 197 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 198 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 199 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 200 */
    { 30, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 201 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 202 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 203 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 204 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 205 */
    { 31, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 206 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 207 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 208 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 209 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 210 */
    { 32, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 211 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 212 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 213 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 214 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 215 */
    { 33, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 216 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 217 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 218 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 219 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 220 */
    { 34, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 221 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 222 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 223 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 224 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 225 */
    { 35, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 226 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 227 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 228 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 229 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 230 */
    { 36, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 231 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 232 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 233 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 234 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 235 */
    { 37, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 236 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 237 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 238 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 239 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 240 */
    { 38, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 241 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 242 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 243 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 244 */
    { 10, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 245 */
    { 39, 2, { 0.0f, 0.0f }, { 1.0f, 1.0f }, 1.0f, 0 }, /* 246 */
};
/* 0x222C */ static MDSPR_GRP_INFO SpriteGrpInfo[8] = {
    { 0, 8, 288.0f, 1.9e+02f }, /* 0 */
    { 9, 9, 288.0f, 2.4e+02f }, /* 1 */
    { 10, 49, 288.0f, 1.9e+02f }, /* 2 */
    { 50, 89, 288.0f, 1.9e+02f }, /* 3 */
    { 90, 118, 288.0f, 1.9e+02f }, /* 4 */
    { 119, 188, 288.0f, 1.9e+02f }, /* 5 */
    { 189, 245, 288.0f, 1.9e+02f }, /* 6 */
    { 246, 246, 288.0f, -6e+01f }, /* 7 */
};

/* 148 insns */
void MdOptionModeSpriteKill(MDSPRITE_WORK *sprite)
{
    MDMESS_WORK *mess;
    MDMODEL_WORK *model;
    int i;
    int j;
    HUSPRGRPID grpId;
    mess = sysP->mess;
    model = sysP->model;
    grpId = sprite->grpId[0];
    switch(sysP->unk18) {
        case 0:
            break;
        case 1:
        case 2:
            MdOptionSprGrpKill(sprite, 2);
            break;
        case 3:
        case 4:
            MdOptionSprGrpKill(sprite, 3);
            break;
        case 7:
            MdOptionSprGrpKill(sprite, 4);
            break;
        case 5:
            MdOptionSprGrpKill(sprite, 5);
            break;
        case 6:
            MdOptionSprGrpKill(sprite, 6);
            break;
        case 8:
            break;
    }
    HuSprDispOff(grpId, 0);
    HuSprDispOff(grpId, 1);
    HuSprDispOff(grpId, 2);
    HuSprDispOff(grpId, 3);
    HuSprDispOff(grpId, 4);
    HuSprDispOff(grpId, 5);
    HuSprDispOff(grpId, 6);
    HuSprDispOff(grpId, 7);
    HuSprDispOff(grpId, 8);
    for(i=2; i<MDMESS_HELPWIN_MAX; i++) {
        MdMessWinAttrSet(mess, i, HUWIN_ATTR_DISPOFF);
        MdMessWinScaleSet(mess, i, 0.0f, 0.0f);
        MdMessWinHomeClear(mess, i);
    }
    for(i=0; i<4; i++) {
        for(j=0; j<7; j++) {
            Hu3DModelDispOff(model->mdlId[(i*7)+29+j]);
        }
    }
    for(i=0; i<2; i++) {
        for(j=0; j<35; j++) {
            Hu3DModelDispOff(model->mdlId[(i*35)+57+j]);
        }
    }
    sysP->unk18 = 0;
}

/* 174 insns */
void MdOptionSprGrpCreate(MDSPRITE_WORK *sprite, int grpNo)
{
    int grpNum;
    MDSPR_GRP_INFO *grpInfo;
    HUSPRGRPID grpId;
    int i;
    MDSPR_INFO *sprInfo;
    grpInfo = &SpriteGrpInfo[grpNo];
    grpNum = grpInfo->end-grpInfo->start+1;
    grpId = HuSprGrpCreate(grpNum);
    sprite->grpId[grpNo] = grpId;
    sprInfo = &SpriteInfo[grpInfo->start];
    switch(grpNo) {
        case 4:
            sprInfo[1].animNo = 7;
            sprInfo[2].animNo = 8;
            break;
        case 5:
            for(i=0; i<10; i++) {
                if(GwCommon.decaScore[i].charNo == -1) {
                    sprInfo[(i*7)+1].animNo = 12;
                } else {
                    sprInfo[(i*7)+1].animNo = 28;
                }
            }
            break;
        case 6:
            sprInfo[1].animNo = GwCommon.decaScore[sysP->unkC].charNo+18;
            break;
    }
    for(i=0; i<grpNum; i++, sprInfo++) {
        sprite->sprId[i] = HuSprCreate(sprite->animP[sprInfo->animNo], 0, sprInfo->bank);
        HuSprGrpMemberSet(grpId, i, sprite->sprId[i]);
        HuSprPriSet(grpId, i, sprInfo->pri);
        HuSprDispOff(grpId, i);
        HuSprPosSet(grpId, i, sprInfo->pos.x, sprInfo->pos.y);
        HuSprZRotSet(grpId, i, 0.0f);
        HuSprScaleSet(grpId, i, sprInfo->scale.x, sprInfo->scale.y);
        HuSprColorSet(grpId, i, 255, 255, 255);
        HuSprTPLvlSet(grpId, i, sprInfo->tpLvl);
    }
    HuSprGrpPosSet(grpId, grpInfo->posX, grpInfo->posY);
    HuSprGrpCenterSet(grpId, 0.0f, 0.0f);
    HuSprGrpZRotSet(grpId, 0.0f);
    HuSprGrpScaleSet(grpId, 1.0f, 1.0f);
    HuSprGrpDrawNoSet(grpId, 64);
    HuSprGrpScissorSet(grpId, 0, 0, 640, 480);
}

/* 16 insns */
void MdOptionSprGrpKill(MDSPRITE_WORK *sprite, int grpNo)
{
    HuSprGrpKill(sprite->grpId[grpNo]);
}

/* 41 insns */
/* fork B's copy (by-value pos): MdOptionSpriteTitleUpdate inlines it */
void MdOptionTitlePosSet(MDSPRITE_WORK *sprite, HuVecF pos)
{
    HUSPRGRPID grpId = sprite->grpId[7];
    HuVec2f *grpPos = MdSpriteGrpPosGet(sprite, 7);
    grpPos->x = pos.x;
    grpPos->y = pos.y;
    if(pos.y < -56.0f) {
        HuSprDispOff(grpId, 0);
    } else {
        HuSprDispOn(grpId, 0);
    }
}

/* 0x22B0 */ static HuVecF BoardRecordSprPosTbl[4] = { { 0.0f, 0.0f, 0.0f }, { -16.0f, 46.0f, 0.0f }, { 0.0f, 46.0f, 0.0f }, { 16.0f, 46.0f, 0.0f } };

/* 386 insns */
void MdOptionBoardRecordUpdate(MDSPRITE_WORK *sprite, int boardNo)
{
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    HuVecF *baseScale;
    HUSPRGRPID recGrpId;
    HuVecF *pos;
    HuVecF *scale;
    int i;
    int j;
    int num;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 1) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 2);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        HuSprDispOn(grpId, 3);
        HuSprDispOn(grpId, 4);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrReset(mess, 3, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinAttrSet(mess, 3, HUWIN_ATTR_ALIGN_CENTER);
        sysP->unk18 = 1;
    }
    recGrpId = sprite->grpId[2];
    pos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 2);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 2);
    *pos = *basePos;
    *scale = *baseScale;
    for(i=0; i<10; i++) {
        HuSprDispOn(recGrpId, i);
        HuSprPosSet(recGrpId, i, BoardRecordSprPosTbl[0].x+(((i%5)*95)-190), BoardRecordSprPosTbl[0].y+(((i/5)*110)-40));
        HuSprBankSet(recGrpId, i, i);
        num = GwCommon.charPlayNum[boardNo][i];
        if(num > 999) {
            num = 999;
        }
        for(j=0; j<3; j++) {
            HuSprDispOn(recGrpId, (i*3)+10+j);
            HuSprPosSet(recGrpId, (i*3)+10+j, (((i%5)*95)-190)+BoardRecordSprPosTbl[j+1].x, (((i/5)*110)-40)+BoardRecordSprPosTbl[j+1].y);
            if(j == 0) {
                HuSprBankSet(recGrpId, (i*3)+10+j, num/100);
            } else if(j == 1) {
                HuSprBankSet(recGrpId, (i*3)+10+j, (num%100)/10);
            } else if(j == 2) {
                HuSprBankSet(recGrpId, (i*3)+10+j, num%10);
            }
        }
    }
    MdMessWinScaleSet(mess, 2, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*baseScale->x)+basePos->x, (-147.0f*baseScale->y)+basePos->y);
    MdMessWinScaleSet(mess, 3, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 3, (-288.0f*baseScale->x)+basePos->x, (-112.0f*baseScale->y)+basePos->y);
    if(boardNo == 6 && GwCommon.w07Unlock == FALSE) {
        MdMessWinMesSet(mess, 2, 0x1F0051);
    } else {
        MdMessWinMesSet(mess, 2, boardNo+0x1F001D);
    }
    num = GwCommon.playNum[boardNo];
    if(num > 9999) {
        num = 9999;
    }
    MdOptionTextListUpdate(10, 0x1F003F, num);
    MdMessWinInsertMesSet(mess, 3, 0x1F0025, 0x1F003F);
}

/* 384 insns */
void MdOptionBoardTotalRecordUpdate(MDSPRITE_WORK *sprite)
{
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    int j;
    HUSPRGRPID recGrpId;
    HuVecF *pos;
    HuVecF *scale;
    int i;
    HuVecF *baseScale;
    int num;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 2) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 2);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        HuSprDispOn(grpId, 3);
        HuSprDispOn(grpId, 4);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrReset(mess, 3, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinAttrSet(mess, 3, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F0024);
        num = 0;
        for(i=0; i<7; i++) {
            num += GwCommon.playNum[i];
        }
        if(num > 9999) {
            num = 9999;
        }
        MdOptionTextListUpdate(10, 0x1F003F, num);
        MdMessWinInsertMesSet(mess, 3, 0x1F0025, 0x1F003F);
        sysP->unk18 = 2;
    }
    recGrpId = sprite->grpId[2];
    pos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 2);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 2);
    *pos = *basePos;
    *scale = *baseScale;
    for(i=0; i<10; i++) {
        HuSprDispOn(recGrpId, i);
        HuSprPosSet(recGrpId, i, BoardRecordSprPosTbl[0].x+(((i%5)*95)-190), BoardRecordSprPosTbl[0].y+(((i/5)*110)-40));
        HuSprBankSet(recGrpId, i, i);
        num = 0;
        for(j=0; j<7; j++) {
            num += GwCommon.charPlayNum[j][i];
        }
        if(num > 999) {
            num = 999;
        }
        for(j=0; j<3; j++) {
            HuSprDispOn(recGrpId, (i*3)+10+j);
            HuSprPosSet(recGrpId, (i*3)+10+j, (((i%5)*95)-190)+BoardRecordSprPosTbl[j+1].x, (((i/5)*110)-40)+BoardRecordSprPosTbl[j+1].y);
            if(j == 0) {
                HuSprBankSet(recGrpId, (i*3)+10+j, num/100);
            } else if(j == 1) {
                HuSprBankSet(recGrpId, (i*3)+10+j, (num%100)/10);
            } else if(j == 2) {
                HuSprBankSet(recGrpId, (i*3)+10+j, num%10);
            }
        }
    }
    MdMessWinScaleSet(mess, 2, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*baseScale->x)+basePos->x, (-147.0f*baseScale->y)+basePos->y);
    MdMessWinScaleSet(mess, 3, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 3, (-288.0f*baseScale->x)+basePos->x, (-112.0f*baseScale->y)+basePos->y);
}

/* 53 insns */
int MdOptionStoryRankCalc(int charNo)
{
    int rank;
    int i;
    rank = 0;
    for(i=0; i<7; i++) {
        if(GwCommon.charStoryPlayNum[i][charNo] != 0) {
            rank += GwCommon.charStoryRank[i][charNo]+1;
        }
    }
    if(rank == 0) {
        rank = 0;
    } else if(rank <= 8) {
        rank = 1;
    } else if(rank <= 15) {
        rank = 2;
    } else if(rank <= 22) {
        rank = 3;
    } else if(rank <= 27) {
        rank = 4;
    } else {
        rank = 5;
    }
    return rank;
}

/* 0x22E0 */ static HuVecF StoryRecordSprPosTbl[9] = { { 0.0f, 0.0f, 0.0f }, { -16.0f, 43.0f, 0.0f }, { 0.0f, 43.0f, 0.0f }, { 16.0f, 43.0f, 0.0f }, { -18.0f, -34.0f, 0.0f }, { 0.0f, -34.0f, 0.0f }, { 18.0f, -34.0f, 0.0f }, { -9.0f, -49.0f, 0.0f }, { 9.0f, -49.0f, 0.0f } };

/* 483 insns */
void MdOptionStoryRecordUpdate(MDSPRITE_WORK *sprite)
{
    MDMODEL_WORK *model;
    MDCAMERA_WORK *camera;
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    HuVecF *baseScale;
    int rank;
    HUSPRGRPID recGrpId;
    HuVecF *pos;
    HuVecF *scale;
    float posX;
    float posY;
    int i;
    int j;
    int num;
    int mdlNo;
    HuVecF *pos2DP;
    HuVecF pos3D;
    model = sysP->model;
    camera = sysP->camera;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 3) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 3);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrReset(mess, 3, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinAttrSet(mess, 3, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F0028);
        for(i=num=0; i<7; i++) {
            num += GwCommon.storyPlayNum[i];
        }
        if(num > 9999) {
            num = 9999;
        }
        MdOptionTextListUpdate(10, 0x1F003F, num);
        MdMessWinInsertMesSet(mess, 3, 0x1F0025, 0x1F003F);
        sysP->unk18 = 3;
    }
    recGrpId = sprite->grpId[3];
    pos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 3);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 3);
    *pos = *basePos;
    *scale = *baseScale;
    for(i=0; i<7; i++) {
        posX = ((i%4)*96)-144+((i/4)*48);
        posY = ((i/4)*110)-18;
        HuSprDispOn(recGrpId, (i*4)+1);
        HuSprPosSet(recGrpId, (i*4)+1, posX+StoryRecordSprPosTbl[0].x, posY+StoryRecordSprPosTbl[0].y);
        HuSprBankSet(recGrpId, (i*4)+1, i);
        num = GwCommon.storyPlayNum[i];
        if(num > 999) {
            num = 999;
        }
        for(j=0; j<3; j++) {
            if(j == 0) {
                HuSprBankSet(recGrpId, (i*4)+2+j, num/100);
            } else if(j == 1) {
                HuSprBankSet(recGrpId, (i*4)+2+j, (num%100)/10);
            } else {
                HuSprBankSet(recGrpId, (i*4)+2+j, num%10);
            }
            HuSprDispOn(recGrpId, (i*4)+2+j);
            HuSprPosSet(recGrpId, (i*4)+2+j, posX+StoryRecordSprPosTbl[j+1].x, posY+StoryRecordSprPosTbl[j+1].y);
        }
        rank = MdOptionStoryRankCalc(i);
        for(j=0; j<5; j++) {
            if(j < rank) {
                mdlNo = (i*5)+57+j;
            } else {
                mdlNo = (i*5)+92+j;
            }
            Hu3DModelDispOn(model->mdlId[mdlNo]);
            {
                HuVecF pos2D = { 0.0f, 0.0f, 2000.0f };
                pos2D.x = basePos->x+(baseScale->x*(posX+StoryRecordSprPosTbl[j+4].x));
            pos2D.y = basePos->y+(baseScale->y*(posY+StoryRecordSprPosTbl[j+4].y));
            pos2DP = &pos2D;
            pos3D = *pos2DP;
            Hu3D2Dto3D(&pos3D, camera->camera[0].bit, &pos3D);
            Hu3DModelPosSetV(model->mdlId[mdlNo], &pos3D);
            Hu3DModelScaleSet(model->mdlId[mdlNo], 0.28f*baseScale->x, 0.28f*baseScale->y, 0.28f*baseScale->y);
            }
        }
    }
    MdMessWinScaleSet(mess, 2, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*baseScale->x)+basePos->x, (-147.0f*baseScale->y)+basePos->y);
    MdMessWinScaleSet(mess, 3, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 3, (-288.0f*baseScale->x)+basePos->x, (-112.0f*baseScale->y)+basePos->y);
}

/* 0x234C */ static HuVecF StoryTotalRecordSprPosTbl[11] = { { 0.0f, 0.0f, 0.0f }, { -16.0f, 52.0f, 0.0f }, { 0.0f, 52.0f, 0.0f }, { 16.0f, 52.0f, 0.0f }, { 288.0f, 144.0f, 0.0f }, { 260.0f, 140.0f, 0.0f }, { 288.0f, 140.0f, 0.0f }, { 316.0f, 140.0f, 0.0f }, { 274.0f, 114.0f, 0.0f }, { 302.0f, 114.0f, 0.0f }, { 0.0f, -10.0f, 0.0f } };

/* 479 insns */
void MdOptionStoryTotalRecordUpdate(MDSPRITE_WORK *sprite, int charNo)
{
    MDMODEL_WORK *model;
    MDCAMERA_WORK *camera;
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HUSPRGRPID recGrpId;
    float posX;
    float posY;
    int i;
    int num;
    int rank;
    int mdlNo;
    BOOL playF;
    BOOL lockF;
    HuVecF *pos2DP;
    HuVecF pos3D;
    playF = FALSE;
    model = sysP->model;
    camera = sysP->camera;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    if(sysP->unk18 != 4) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 3);
        MdMessWinScaleSet(mess, 2, 1.0f, 1.0f);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F0029);
        sysP->unk18 = 4;
        recGrpId = sprite->grpId[3];
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        HuSprDispOn(recGrpId, 0);
        posX = -204.0f;
        posY = 15.0f;
        HuSprPosSet(recGrpId, 0, posX+StoryTotalRecordSprPosTbl[10].x, posY+StoryTotalRecordSprPosTbl[10].y);
        HuSprDispOn(recGrpId, 29);
        HuSprPosSet(recGrpId, 29, posX+StoryTotalRecordSprPosTbl[0].x, posY+StoryTotalRecordSprPosTbl[0].y);
        HuSprBankSet(recGrpId, 29, charNo);
        num = GwCommon.storyPlayNum[charNo];
        if(num > 999) {
            num = 999;
        }
        rank = MdOptionStoryRankCalc(charNo);
        for(i=0; i<5; i++) {
            if(i < rank) {
                mdlNo = i+57;
            } else {
                mdlNo = i+92;
            }
            Hu3DModelDispOn(model->mdlId[mdlNo]);
            {
                HuVecF pos2D = { 0.0f, 0.0f, 2000.0f };
                pos2D.x = posX+StoryTotalRecordSprPosTbl[i+5].x;
                pos2D.y = posY+StoryTotalRecordSprPosTbl[i+5].y;
                pos2DP = &pos2D;
                pos3D = *pos2DP;
                Hu3D2Dto3D(&pos3D, camera->camera[0].bit, &pos3D);
                Hu3DModelPosSetV(model->mdlId[mdlNo], &pos3D);
                Hu3DModelScaleSet(model->mdlId[mdlNo], 0.4f, 0.4f, 0.4f);
            }
        }
        for(i=0; i<3; i++) {
            if(i == 0) {
                HuSprBankSet(recGrpId, i+30, num/100);
            } else if(i == 1) {
                HuSprBankSet(recGrpId, i+30, (num%100)/10);
            } else {
                HuSprBankSet(recGrpId, i+30, num%10);
            }
            HuSprDispOn(recGrpId, i+30);
            HuSprPosSet(recGrpId, i+30, posX+StoryTotalRecordSprPosTbl[i+1].x, posY+StoryTotalRecordSprPosTbl[i+1].y);
        }
        playF = FALSE;
        for(i=0; i<7; i++) {
            if(GwCommon.charStoryPlayNum[6][i] != 0) {
                playF = TRUE;
            }
        }
        for(i=0; i<7; i++) {
            if(i < 3) {
                posX = (i*104)-80;
                posY = -10.0f;
            } else {
                posX = ((i-3)*104)-128;
                posY = 115.0f;
            }
            HuSprDispOn(recGrpId, i+33);
            HuSprPosSet(recGrpId, i+33, posX+StoryTotalRecordSprPosTbl[0].x, posY+StoryTotalRecordSprPosTbl[0].y);
            lockF = (i == 6 && playF == FALSE);
            num = (lockF) ? 7 : i;
            HuSprBankSet(recGrpId, i+33, num);
            if(GwCommon.charStoryPlayNum[i][charNo] != 0) {
                mdlNo = (GwCommon.charStoryRank[i][charNo]*7)+29;
                Hu3DModelDispOn(model->mdlId[mdlNo+i]);
                {
                    HuVecF pos2D = { 0.0f, 0.0f, 1000.0f };
                    pos2D.x = posX+StoryTotalRecordSprPosTbl[4].x;
                    pos2D.y = posY+StoryTotalRecordSprPosTbl[4].y;
                    pos2DP = &pos2D;
                    pos3D = *pos2DP;
                    Hu3D2Dto3D(&pos3D, camera->camera[1].bit, &pos3D);
                    Hu3DModelPosSetV(model->mdlId[mdlNo+i], &pos3D);
                    Hu3DModelScaleSet(model->mdlId[mdlNo+i], 0.75f, 0.75f, 0.75f);
                }
            }
        }
    }
}

/* 31 insns */
int MdOptionDecaGetBestRecord(int num)
{
    int i;
    int best;
    for(i=0, best=0; i<=num; i++) {
        if(i > 0 && GwCommon.decaScore[i-1].finalScore > GwCommon.decaScore[i].finalScore) {
            best = i;
        }
    }
    return best;
}

/* 0x23D0 */ static HuVecF DecaRecordSprPosTbl[7] = { { 0.0f, 0.0f, 0.0f }, { -32.0f, 44.0f, 0.0f }, { -16.0f, 44.0f, 0.0f }, { 0.0f, 44.0f, 0.0f }, { 16.0f, 44.0f, 0.0f }, { 32.0f, 44.0f, 0.0f }, { 0.0f, -44.0f, 0.0f } };

/* 361 insns */
void MdOptionDecaRecordUpdate(MDSPRITE_WORK *sprite)
{
    int best;
    int digit;
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    HuVecF *baseScale;
    HUSPRGRPID recGrpId;
    HuVecF *pos;
    HuVecF *scale;
    GWDECASCORE *score;
    float posX;
    float posY;
    int i;
    int j;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 5) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 5);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F002C);
        sysP->unk18 = 5;
    }
    recGrpId = sprite->grpId[5];
    pos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 5);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 5);
    *pos = *basePos;
    *scale = *baseScale;
    for(i=0, best=0; i<10; i++) {
        score = &GwCommon.decaScore[i];
        posX = ((i%5)*96)-194;
        posY = ((i/5)*126)-42;
        HuSprDispOn(recGrpId, (i*7)+1);
        HuSprPosSet(recGrpId, (i*7)+1, posX+DecaRecordSprPosTbl[0].x, posY+DecaRecordSprPosTbl[0].y);
        if(score->charNo != -1) {
            HuSprBankSet(recGrpId, (i*7)+1, score->charNo);
        }
        best = MdOptionDecaGetBestRecord(i);
        HuSprDispOn(recGrpId, i*7);
        HuSprPosSet(recGrpId, i*7, posX+DecaRecordSprPosTbl[6].x, posY+DecaRecordSprPosTbl[6].y);
        HuSprBankSet(recGrpId, i*7, best);
        for(j=0; j<5; j++) {
            if(j == 0) {
                digit = score->finalScore/10000;
            } else if(j == 1) {
                digit = (score->finalScore%10000)/1000;
            } else if(j == 2) {
                digit = (score->finalScore%1000)/100;
            } else if(j == 3) {
                digit = (score->finalScore%100)/10;
            } else {
                digit = score->finalScore%10;
            }
            HuSprDispOn(recGrpId, (i*7)+2+j);
            HuSprPosSet(recGrpId, (i*7)+2+j, posX+DecaRecordSprPosTbl[j+1].x, posY+DecaRecordSprPosTbl[j+1].y);
            HuSprBankSet(recGrpId, (i*7)+2+j, digit);
        }
    }
    MdMessWinScaleSet(mess, 2, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*baseScale->x)+basePos->x, (-147.0f*baseScale->y)+basePos->y);
}

/* 0x2424 */ static HuVecF DecaTotalRecordSprPosTbl[12] = { { 0.0f, 0.0f, 0.0f }, { -24.0f, 54.0f, 0.0f }, { -8.0f, 54.0f, 0.0f }, { 8.0f, 54.0f, 0.0f }, { 24.0f, 54.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 60.0f, 0.0f, 0.0f }, { 112.0f, 0.0f, 0.0f }, { 132.0f, 0.0f, 0.0f }, { 152.0f, 0.0f, 0.0f }, { 172.0f, 0.0f, 0.0f }, { 192.0f, 0.0f, 0.0f } };

/* 424 insns */
void MdOptionDecaTotalRecordUpdate(MDSPRITE_WORK *sprite, int recNo)
{
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    HuVecF *baseScale;
    HUSPRGRPID recGrpId;
    GWDECASCORE *score;
    float posX;
    float posY;
    int i;
    int j;
    int best;
    int digit;
    u32 mgScore;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 6) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 6);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        MdMessWinScaleSet(mess, 2, 1.0f, 1.0f);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F002D);
        sysP->unk18 = 6;
        recGrpId = sprite->grpId[6];
        posX = -94.0f;
        posY = -88.0f;
        best = MdOptionDecaGetBestRecord(recNo);
        score = &GwCommon.decaScore[recNo];
        HuSprDispOn(recGrpId, 0);
        HuSprPosSet(recGrpId, 0, posX+DecaTotalRecordSprPosTbl[5].x, posY+DecaTotalRecordSprPosTbl[5].y);
        HuSprBankSet(recGrpId, 0, best);
        HuSprDispOn(recGrpId, 1);
        HuSprPosSet(recGrpId, 1, posX+DecaTotalRecordSprPosTbl[6].x, posY+DecaTotalRecordSprPosTbl[6].y);
        for(i=0; i<5; i++) {
            if(i == 0) {
                digit = score->finalScore/10000;
            } else if(i == 1) {
                digit = (score->finalScore%10000)/1000;
            } else if(i == 2) {
                digit = (score->finalScore%1000)/100;
            } else if(i == 3) {
                digit = (score->finalScore%100)/10;
            } else {
                digit = score->finalScore%10;
            }
            HuSprDispOn(recGrpId, i+2);
            HuSprPosSet(recGrpId, i+2, posX+DecaTotalRecordSprPosTbl[i+7].x, posY+DecaTotalRecordSprPosTbl[i+7].y);
            HuSprBankSet(recGrpId, i+2, digit);
        }
        for(i=0; i<10; i++) {
            posX = ((i%5)*96)-194;
            posY = ((i/5)*110)-26;
            HuSprDispOn(recGrpId, (i*5)+7);
            HuSprPosSet(recGrpId, (i*5)+7, posX+DecaTotalRecordSprPosTbl[0].x, posY+DecaTotalRecordSprPosTbl[0].y);
            HuSprScaleSet(recGrpId, (i*5)+7, 0.84f, 0.84f);
            mgScore = MgDecaScoreCalc(i, score->mgScore[i]);
            for(j=0; j<4; j++) {
                if(j == 0) {
                    digit = (mgScore%10000)/1000;
                } else if(j == 1) {
                    digit = (mgScore%1000)/100;
                } else if(j == 2) {
                    digit = (mgScore%100)/10;
                } else {
                    digit = mgScore%10;
                }
                HuSprDispOn(recGrpId, (i*5)+8+j);
                HuSprPosSet(recGrpId, (i*5)+8+j, posX+DecaTotalRecordSprPosTbl[j+1].x, posY+DecaTotalRecordSprPosTbl[j+1].y);
                HuSprBankSet(recGrpId, (i*5)+8+j, digit);
            }
        }
    }
}

/* 0x24B4 */ static HuVecF SdRecordSprPosTbl[5] = { { 0.0f, 0.0f, 0.0f }, { -40.0f, 66.0f, 0.0f }, { 0.0f, 66.0f, 0.0f }, { 20.0f, 66.0f, 0.0f }, { 40.0f, 66.0f, 0.0f } };

/* 411 insns */
void MdOptionSdRecordUpdate(MDSPRITE_WORK *sprite)
{
    MDMESS_WORK *mess;
    HUSPRGRPID grpId;
    HuVecF *basePos;
    HuVecF *baseScale;
    HuVecF *pos;
    HuVecF *scale;
    float posX;
    float posY;
    int i;
    int j;
    int num;
    HUSPRGRPID recGrpId;
    int digit;
    mess = sysP->mess;
    grpId = sprite->grpId[0];
    basePos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 0);
    baseScale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 0);
    if(sysP->unk18 != 7) {
        MdOptionModeSpriteKill(sprite);
        MdOptionSprGrpCreate(sprite, 4);
        HuSprDispOn(grpId, 0);
        HuSprDispOn(grpId, 1);
        MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinAttrSet(mess, 3, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F0030);
        MdMessWinAttrReset(mess, 3, HUWIN_ATTR_DISPOFF);
        digit = GwCommon.sdVsPlayCnt;
        if(digit > 999) {
            digit = 999;
        }
        MdOptionTextListUpdate(11, 0x1F003F, digit);
        MdMessWinInsertMesSet(mess, 3, 0x1F0031, 0x1F003F);
        sysP->unk18 = 7;
    }
    recGrpId = sprite->grpId[4];
    pos = (HuVecF *)MdSpriteGrpPosGet(sysP->sprite, 4);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sysP->sprite, 4);
    *pos = *basePos;
    *scale = *baseScale;
    for(i=0; i<2; i++) {
        posX = -180.0f;
        posY = (i*50)+44;
        HuSprDispOn(recGrpId, i+27);
        HuSprPosSet(recGrpId, i+27, posX, posY);
        HuSprBankSet(recGrpId, i+27, i);
    }
    for(i=0; i<3; i++) {
        posX = (i*120)-80;
        posY = -20.0f;
        HuSprDispOn(recGrpId, i);
        HuSprPosSet(recGrpId, i, posX+SdRecordSprPosTbl[0].x, posY+SdRecordSprPosTbl[0].y);
        for(j=0; j<4; j++) {
            num = GwCommon.sdVsWinCnt[i][0];
            if(num > 999) {
                num = 999;
            }
            if(j == 0) {
                digit = 10;
            } else if(j == 1) {
                digit = num/100;
            } else if(j == 2) {
                digit = (num%100)/10;
            } else {
                digit = num%10;
            }
            HuSprBankSet(recGrpId, (i*4)+3+j, digit);
            HuSprDispOn(recGrpId, (i*4)+3+j);
            HuSprPosSet(recGrpId, (i*4)+3+j, posX+SdRecordSprPosTbl[j+1].x, posY+SdRecordSprPosTbl[j+1].y);
            num = GwCommon.sdVsWinCnt[i][1];
            if(num > 999) {
                num = 999;
            }
            if(j == 0) {
                digit = 10;
            } else if(j == 1) {
                digit = num/100;
            } else if(j == 2) {
                digit = (num%100)/10;
            } else {
                digit = num%10;
            }
            HuSprBankSet(recGrpId, (i*4)+15+j, digit);
            HuSprDispOn(recGrpId, (i*4)+15+j);
            HuSprPosSet(recGrpId, (i*4)+15+j, posX+SdRecordSprPosTbl[j+1].x, 50.0f+(posY+SdRecordSprPosTbl[j+1].y));
        }
    }
    MdMessWinScaleSet(mess, 2, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*baseScale->x)+basePos->x, (-147.0f*baseScale->y)+basePos->y);
    MdMessWinScaleSet(mess, 3, baseScale->x, baseScale->y);
    MdMessWinPosSet(mess, 3, (-288.0f*baseScale->x)+basePos->x, (-112.0f*baseScale->y)+basePos->y);
}

/* 0x24F0 */ static MDOPTION_MGRECORD MgRecordTbl[13] = {
    { 0x430005, 0x430005, 0x2, 0x0 },
    { 0x430009, 0x430009, 0x1, 0x1 },
    { 0x43000A, 0x43000A, 0x7, 0x2 },
    { 0x43000B, 0x43000B, 0x7, 0x3 },
    { 0x43000C, 0x43000C, 0x7, 0x4 },
    { 0x43000D, 0x43000D, 0xD, 0x5 },
    { 0x43001C, 0x43001C, 0x1, 0x6 },
    { 0x430049, 0x430049, 0x4, 0x9 },
    { 0x43002E, 0x43002E, 0x2, 0x7 },
    { 0x430033, 0x430033, 0x5, 0x8 },
    { 0x430033, 0x1F0052, 0x5, 0xA },
    { 0x430033, 0x1F0053, 0x5, 0xB },
    { 0xFFFFFFFF, 0xFFFFFFFF, 0x0, 0x0 }
};
/* 0x25C0 */ u32 lbl_1_data_25C0[24] = { MESS_MGNAME_M501, MESS_MGNAME_M502, MESS_MGNAME_M503, MESS_MGNAME_M504, MESS_MGNAME_M563, MESS_MGNAME_M564, MESS_MGNAME_M565, MESS_MGNAME_M576, MESS_MGNAME_M505, MESS_MGNAME_M506, MESS_MGNAME_M507, MESS_MGNAME_M508, MESS_MGNAME_M509, MESS_MGNAME_M510, MESS_MGNAME_M579, MESS_MGNAME_M511, MESS_MGNAME_M512, MESS_MGNAME_M513, MESS_MGNAME_M514, MESS_MGNAME_M515, MESS_MGNAME_M524, MESS_MGNAME_M516, MESS_MGNAME_M566, HU_DATANUM_NONE };
/* 0x2620 */ u32 lbl_1_data_2620[13] = { MESS_MGNAME_M517, MESS_MGNAME_M518, MESS_MGNAME_M519, MESS_MGNAME_M520, MESS_MGNAME_M522, MESS_MGNAME_M523, MESS_MGNAME_M525, MESS_MGNAME_M567, MESS_MGNAME_M568, MESS_MGNAME_M569, MESS_MGNAME_M570, MESS_MGNAME_M577, HU_DATANUM_NONE };
/* 0x2654 */ u32 lbl_1_data_2654[13] = { MESS_MGNAME_M526, MESS_MGNAME_M527, MESS_MGNAME_M528, MESS_MGNAME_M521, MESS_MGNAME_M529, MESS_MGNAME_M530, MESS_MGNAME_M531, MESS_MGNAME_M574, MESS_MGNAME_M532, MESS_MGNAME_M533, MESS_MGNAME_M534, MESS_MGNAME_M575, HU_DATANUM_NONE };
/* 0x2688 */ u32 lbl_1_data_2688[7] = { MESS_MGNAME_M535, MESS_MGNAME_M536, MESS_MGNAME_M537, MESS_MGNAME_M538, MESS_MGNAME_M539, MESS_MGNAME_M540, HU_DATANUM_NONE };
/* 0x26A4 */ u32 lbl_1_data_26A4[16] = { MESS_MGNAME_M541, MESS_MGNAME_M542, MESS_MGNAME_M543, MESS_MGNAME_M544, MESS_MGNAME_M545, MESS_MGNAME_M546, MESS_MGNAME_M547, MESS_MGNAME_M548, MESS_MGNAME_M549, MESS_MGNAME_M550, MESS_MGNAME_M551, MESS_MGNAME_M552, MESS_MGNAME_M553, MESS_MGNAME_M554, MESS_MGNAME_M555, HU_DATANUM_NONE };
/* 0x26E4 */ u32 lbl_1_data_26E4[19] = { MESS_MGNAME_M501, MESS_MGNAME_M502, MESS_MGNAME_M503, MESS_MGNAME_M563, MESS_MGNAME_M564, MESS_MGNAME_M565, MESS_MGNAME_M576, MESS_MGNAME_M505, MESS_MGNAME_M506, MESS_MGNAME_M507, MESS_MGNAME_M508, MESS_MGNAME_M509, MESS_MGNAME_M510, MESS_MGNAME_M579, MESS_MGNAME_M513, MESS_MGNAME_M524, MESS_MGNAME_M516, MESS_MGNAME_M566, HU_DATANUM_NONE };
/* 0x2730 */ u32 lbl_1_data_2730[10] = { MESS_MGNAME_M517, MESS_MGNAME_M518, MESS_MGNAME_M520, MESS_MGNAME_M522, MESS_MGNAME_M523, MESS_MGNAME_M568, MESS_MGNAME_M569, MESS_MGNAME_M570, MESS_MGNAME_M577, HU_DATANUM_NONE };
/* 0x2758 */ u32 lbl_1_data_2758[10] = { MESS_MGNAME_M526, MESS_MGNAME_M528, MESS_MGNAME_M521, MESS_MGNAME_M529, MESS_MGNAME_M574, MESS_MGNAME_M532, MESS_MGNAME_M533, MESS_MGNAME_M534, MESS_MGNAME_M575, HU_DATANUM_NONE };
/* 0x2780 */ u32 lbl_1_data_2780[5] = { MESS_MGNAME_M535, MESS_MGNAME_M538, MESS_MGNAME_M539, MESS_MGNAME_M540, HU_DATANUM_NONE };
/* 0x2794 */ u32 lbl_1_data_2794[11] = { MESS_MGNAME_M541, MESS_MGNAME_M542, MESS_MGNAME_M544, MESS_MGNAME_M546, MESS_MGNAME_M547, MESS_MGNAME_M548, MESS_MGNAME_M550, MESS_MGNAME_M551, MESS_MGNAME_M553, MESS_MGNAME_M554, HU_DATANUM_NONE };
/* 0x27C0 */ u32 lbl_1_data_27C0[11] = { MESS_MGNAME_M502, MESS_MGNAME_M503, MESS_MGNAME_M563, MESS_MGNAME_M564, MESS_MGNAME_M565, MESS_MGNAME_M576, MESS_MGNAME_M511, MESS_MGNAME_M512, MESS_MGNAME_M524, MESS_MGNAME_M516, HU_DATANUM_NONE };
/* 0x27EC */ u32 lbl_1_data_27EC[7] = { MESS_MGNAME_M517, MESS_MGNAME_M518, MESS_MGNAME_M519, MESS_MGNAME_M520, MESS_MGNAME_M568, MESS_MGNAME_M569, HU_DATANUM_NONE };
/* 0x2808 */ u32 lbl_1_data_2808[7] = { MESS_MGNAME_M526, MESS_MGNAME_M527, MESS_MGNAME_M521, MESS_MGNAME_M531, MESS_MGNAME_M534, MESS_MGNAME_M575, HU_DATANUM_NONE };
/* 0x2824 */ u32 lbl_1_data_2824[4] = { MESS_MGNAME_M536, MESS_MGNAME_M537, MESS_MGNAME_M538, HU_DATANUM_NONE };
/* 0x2834 */ u32 lbl_1_data_2834[6] = { MESS_MGNAME_M541, MESS_MGNAME_M543, MESS_MGNAME_M549, MESS_MGNAME_M551, MESS_MGNAME_M553, HU_DATANUM_NONE };
/* 0x284C */ u32 lbl_1_data_284C[11] = { MESS_MGNAME_M501, MESS_MGNAME_M504, MESS_MGNAME_M505, MESS_MGNAME_M506, MESS_MGNAME_M507, MESS_MGNAME_M509, MESS_MGNAME_M510, MESS_MGNAME_M515, MESS_MGNAME_M524, MESS_MGNAME_M516, HU_DATANUM_NONE };
/* 0x2878 */ u32 lbl_1_data_2878[7] = { MESS_MGNAME_M522, MESS_MGNAME_M523, MESS_MGNAME_M525, MESS_MGNAME_M567, MESS_MGNAME_M569, MESS_MGNAME_M577, HU_DATANUM_NONE };
/* 0x2894 */ u32 lbl_1_data_2894[7] = { MESS_MGNAME_M526, MESS_MGNAME_M528, MESS_MGNAME_M529, MESS_MGNAME_M530, MESS_MGNAME_M532, MESS_MGNAME_M575, HU_DATANUM_NONE };
/* 0x28B0 */ u32 lbl_1_data_28B0[4] = { MESS_MGNAME_M535, MESS_MGNAME_M539, MESS_MGNAME_M540, HU_DATANUM_NONE };
/* 0x28C0 */ u32 lbl_1_data_28C0[6] = { MESS_MGNAME_M542, MESS_MGNAME_M544, MESS_MGNAME_M548, MESS_MGNAME_M552, MESS_MGNAME_M555, HU_DATANUM_NONE };
/* 0x28D8 */ u32 lbl_1_data_28D8[11] = { MESS_MGNAME_M501, MESS_MGNAME_M502, MESS_MGNAME_M508, MESS_MGNAME_M579, MESS_MGNAME_M513, MESS_MGNAME_M514, MESS_MGNAME_M515, MESS_MGNAME_M524, MESS_MGNAME_M516, MESS_MGNAME_M566, HU_DATANUM_NONE };
/* 0x2904 */ u32 lbl_1_data_2904[7] = { MESS_MGNAME_M518, MESS_MGNAME_M522, MESS_MGNAME_M523, MESS_MGNAME_M567, MESS_MGNAME_M569, MESS_MGNAME_M570, HU_DATANUM_NONE };
/* 0x2920 */ u32 lbl_1_data_2920[7] = { MESS_MGNAME_M527, MESS_MGNAME_M529, MESS_MGNAME_M574, MESS_MGNAME_M533, MESS_MGNAME_M534, MESS_MGNAME_M575, HU_DATANUM_NONE };
/* 0x293C */ u32 lbl_1_data_293C[4] = { MESS_MGNAME_M536, MESS_MGNAME_M537, MESS_MGNAME_M540, HU_DATANUM_NONE };
/* 0x294C */ u32 lbl_1_data_294C[6] = { MESS_MGNAME_M545, MESS_MGNAME_M546, MESS_MGNAME_M547, MESS_MGNAME_M550, MESS_MGNAME_M554, HU_DATANUM_NONE };
/* 0x2964 */ static u32 *ListTbl[25] = { lbl_1_data_25C0, lbl_1_data_2620, lbl_1_data_2654, lbl_1_data_2688, lbl_1_data_26A4, lbl_1_data_26E4, lbl_1_data_2730, lbl_1_data_2758, lbl_1_data_2780, lbl_1_data_2794, lbl_1_data_27C0, lbl_1_data_27EC, lbl_1_data_2808, lbl_1_data_2824, lbl_1_data_2834, lbl_1_data_284C, lbl_1_data_2878, lbl_1_data_2894, lbl_1_data_28B0, lbl_1_data_28C0, lbl_1_data_28D8, lbl_1_data_2904, lbl_1_data_2920, lbl_1_data_293C, lbl_1_data_294C };
/* 0x29C8 */ static s32 ListNumTbl[25] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
/* 0x2A2C */ static s32 ListMgNumTbl[25] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

/* 79 insns */
void MdOptionMgListInit(void)
{
    int i;
    int j;
    int k;
    int mgNo;
    for(i=0; i<5; i++) {
        for(j=0; j<5; j++) {
            ListMgNumTbl[(i*5)+j] = 0;
            for(k=0; ListTbl[(i*5)+j][k] != HU_DATANUM_NONE; k++) {
                mgNo = (ListTbl[(i*5)+j][k]-MESS_MGNAME_M501)+501;
                if(GWMgUnlockGet(mgNo)) {
                    ListMgNumTbl[(i*5)+j]++;
                }
            }
            ListNumTbl[(i*5)+j] = k;
        }
    }
}

/* 57 insns */
u32 MdOptionTextListNameGet(int listNo, int subNo, int no)
{
    int mgNo;
    if(no >= ListNumTbl[(listNo*5)+subNo]) {
        return 0x1F0043;
    }
    mgNo = (ListTbl[(listNo*5)+subNo][no]-MESS_MGNAME_M501)+501;
    if(GWMgUnlockGet(mgNo)) {
        return ListTbl[(listNo*5)+subNo][no];
    } else {
        return 0x1F004F;
    }
}


/* 974 insns */
void MdOptionTextListUpdate(int type, u32 mes, u32 num)
{
    char *buf;
    int i;
    int hour;
    int min;
    int sec;
    buf = HuWinMesPtrGet(mes);
    switch(type) {
        case 0:
            for(i=0; i<7; i++) {
                if(i < 6) {
                    buf[i] = ' ';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 1:
            for(i=0; i<7; i++) {
                if(i < 5) {
                    buf[i] = ' ';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 2:
            for(i=0; i<7; i++) {
                if(i < 4) {
                    buf[i] = ' ';
                } else if(i == 4) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 3:
            for(i=0; i<7; i++) {
                if(i < 3) {
                    buf[i] = ' ';
                } else if(i == 3) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 4) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 4:
            for(i=0; i<7; i++) {
                if(i < 2) {
                    buf[i] = ' ';
                } else if(i == 2) {
                    buf[i] = ((num%100000)/10000)+'0';
                } else if(i == 3) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 4) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 5:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = ' ';
                } else if(i == 1) {
                    buf[i] = ((num%1000000)/100000)+'0';
                } else if(i == 2) {
                    buf[i] = ((num%100000)/10000)+'0';
                } else if(i == 3) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 4) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 6:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = ((num%10000000)/1000000)+'0';
                } else if(i == 1) {
                    buf[i] = ((num%1000000)/100000)+'0';
                } else if(i == 2) {
                    buf[i] = ((num%100000)/10000)+'0';
                } else if(i == 3) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 4) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 7:
            hour = num/3600;
            min = (num%3600)/60;
            sec = 1.6666666f*((num%3600)%60);
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = (hour%10)+'0';
                } else if(i == 1) {
                    buf[i] = '\\';
                } else if(i == 2) {
                    buf[i] = ((min%100)/10)+'0';
                } else if(i == 3) {
                    buf[i] = (min%10)+'0';
                } else if(i == 4) {
                    buf[i] = '[';
                } else if(i == 5) {
                    buf[i] = ((sec%100)/10)+'0';
                } else {
                    buf[i] = (sec%10)+'0';
                }
            }
            break;
        case 8:
            for(i=0; i<7; i++) {
                if(i < 2) {
                    buf[i] = ' ';
                } else if(i == 2) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 3) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 4) {
                    buf[i] = 0x85;
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
        case 9:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = (num%10)+'0';
                } else {
                    buf[i] = 0;
                }
            }
            break;
        case 10:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 1) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 2) {
                    buf[i] = ((num%100)/10)+'0';
                } else if(i == 3) {
                    buf[i] = (num%10)+'0';
                } else {
                    buf[i] = 0;
                }
            }
            break;
        case 11:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 1) {
                    buf[i] = ((num%100)/10)+'0';
                } else if(i == 2) {
                    buf[i] = (num%10)+'0';
                } else {
                    buf[i] = 0;
                }
            }
            break;
        case 12:
            for(i=0; i<7; i++) {
                buf[i] = ' ';
            }
            break;
        case 13:
            for(i=0; i<7; i++) {
                if(i == 0) {
                    buf[i] = ' ';
                } else if(i == 1) {
                    buf[i] = ((num%100000)/10000)+'0';
                } else if(i == 2) {
                    buf[i] = ((num%10000)/1000)+'0';
                } else if(i == 3) {
                    buf[i] = ((num%1000)/100)+'0';
                } else if(i == 4) {
                    buf[i] = 0x85;
                } else if(i == 5) {
                    buf[i] = ((num%100)/10)+'0';
                } else {
                    buf[i] = (num%10)+'0';
                }
            }
            break;
    }
}



/* 45 insns */
void MdOptionMgCopyName(u32 mes, char *name)
{
    char *mesP = HuWinMesPtrGet(mes);
    int i;
    for(i=0; i<7; i++) {
        if(i == 0) {
            mesP[i] = name[0];
        } else if(i == 1) {
            mesP[i] = name[1];
        } else if(i == 2) {
            mesP[i] = name[2];
        } else if(i == 3) {
            mesP[i] = name[3];
        } else {
            mesP[i] = 0;
        }
    }
}

/* 731 insns */
void MdOptionMgListUpdate(MDSPRITE_WORK *sprite)
{
    MDMESS_WORK *mess = sysP->mess;
    HUSPRGRPID grpId = sprite->grpId[0];
    HuVec2f *grpPos = MdSpriteGrpPosGet(sysP->sprite, 0);
    HuVec2f *grpScale = MdSpriteGrpScaleGet(sysP->sprite, 0);
    int i;
    float posX;
    float posY;
    u32 mes;
    if(sysP->unk18 != 8) {
        MdOptionModeSpriteKill(sprite);
        sysP->unk18 = 8;
    }
    HuSprDispOn(grpId, 0);
    HuSprDispOn(grpId, 1);
    MdMessWinScaleSet(mess, 2, grpScale->x, grpScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*grpScale->x)+grpPos->x, (-147.0f*grpScale->y)+grpPos->y);
    for(i=0; i<2; i++) {
        posX = 0;
        posY = (i*220)-90;
        HuSprDispOn(grpId, i+5);
        HuSprBankSet(grpId, i+5, i);
        HuSprPosSet(grpId, i+5, posX, posY);
        HuSprDispOn(grpId, i+7);
        HuSprTPLvlSet(grpId, i+7, 0);
        HuSprAttrSet(grpId, i+7, HUSPR_ATTR_ADDCOL);
        HuSprBankSet(grpId, i+7, i);
        HuSprPosSet(grpId, i+7, posX, posY);
    }
    MdMessWinAttrReset(mess, 2, HUWIN_ATTR_DISPOFF);
    MdMessWinAttrReset(mess, 3, HUWIN_ATTR_DISPOFF);
    if(sysP->unk4 == 0) {
        HuSprDispOn(grpId, 3);
        HuSprDispOn(grpId, 4);
        MdOptionMgListInit();
        MdOptionListCursorPosSet(0, 0, 0);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F0039);
        MdOptionTextListUpdate(12, 0x1F0043, 0);
        for(i=0; i<7; i++) {
            u32 winMes;
            MdMessWinClose(mess, i+4);
            winMes = MdOptionTextListNameGet(0, 0, i);
            MdMessHelpWinCreate(mess, i+4, winMes, 150, 116, 260, 32, 0, 0);
            MdMessWinAttrSet(mess, i+4, HUWIN_ATTR_SKIP_KEYWAIT|HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinMesSet(mess, i+4, winMes);
            MdMessWinSpeedSet(mess, i+4, 0);
            MdMessWinScaleSet(mess, i+4, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, i+4, (-138.0f*grpScale->x)+grpPos->x, grpPos->y+((-80.0f+(26.0f*i))*grpScale->y));
        }
        {
            u32 insertMes[8] = { 0x1F003F, 0x1F0040, 0x1F0041, 0x1F0042, -1, -1, -1, -1 };
            MdOptionTextListUpdate(9, insertMes[0], ListMgNumTbl[0]/10);
            MdOptionTextListUpdate(9, insertMes[1], ListMgNumTbl[0]%10);
            MdOptionTextListUpdate(9, insertMes[2], ListNumTbl[0]/10);
            MdOptionTextListUpdate(9, insertMes[3], ListNumTbl[0]%10);
            MdMessWinClose(mess, 11);
            MdMessHelpWinCreate(mess, 11, 0x20000B, 402, 300, 115, 28, 0, 0);
            MdMessWinInsertMultiMesSet(mess, 11, 0x1F004D, insertMes);
            MdMessWinSpeedSet(mess, 11, 0);
            MdMessWinScaleSet(mess, 11, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, 11, (114.0f*grpScale->x)+grpPos->x, (108.0f*grpScale->y)+grpPos->y);
        }
    } else if(sysP->unk4 == 2 && sysP->unk8 == 1) {
        fn_1_1A7C0();
    } else if(sysP->unk4 == 3 && sysP->unk8 == 0) {
        u32 recMes[8] = { 0x1F003F, 0x1F0040, 0x1F0041, 0x1F0042, 0x1F0043, 0x1F0044, 0x1F0045, -1 };
        MdOptionRecordCursorPosSet(0);
        HuSprDispOff(grpId, 3);
        HuSprDispOff(grpId, 4);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, 0x1F001C);
        for(i=0; i<7; i++) {
            MdMessWinClose(mess, i+11);
            mes = MgRecordTbl[i].mes-MESS_MGNAME_M501+GW_MGNO_BASE;
            if(GWMgUnlockGet(mes)) {
                MdOptionTextListUpdate(MgRecordTbl[i].type, recMes[i], GwCommon.mgRecord[MgRecordTbl[i].recNo]);
            } else {
                recMes[i] = 0x1F0051;
            }
            MdMessHelpWinCreate(mess, i+11, 0x1F003E, 350, 116, 150, 32, 0, 0);
            MdMessWinAttrSet(mess, i+11, HUWIN_ATTR_ALIGN_RIGHT);
            MdMessWinMesSet(mess, i+11, recMes[i]);
            MdMessWinScaleSet(mess, i+11, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, i+11, (62.0f*grpScale->x)+grpPos->x, grpPos->y+((-80.0f+(26.0f*i))*grpScale->y));
            MdMessWinSpeedSet(mess, i+11, 0);
        }
        MdMessWinClose(mess, 4);
        MdMessHelpWinCreate(mess, 4, 0x1F003E, 60, 116, 260, 180, 0, 0);
        for(i=0; i<7; i++) {
            mes = MgRecordTbl[i].mes-MESS_MGNAME_M501+GW_MGNO_BASE;
            if(GWMgUnlockGet(mes)) {
                recMes[i] = MgRecordTbl[i].recMes;
            } else {
                recMes[i] = 0x1F004F;
            }
        }
        MdMessWinInsertMultiMesSet(mess, 4, 0x1F003E, recMes);
        MdMessWinScaleSet(mess, 4, grpScale->x, grpScale->y);
        MdMessWinPosSet(mess, 4, (-228.0f*grpScale->x)+grpPos->x, (-80.0f*grpScale->y)+grpPos->y);
        MdMessWinSpeedSet(mess, 4, 0);
    }
}

/* 474 insns */
void MdOptionMgListWinUpdate(MDSPRITE_WORK *sprite, int listNo, int subNo, int top)
{
    HUSPRGRPID grpId = sprite->grpId[0];
    MDMESS_WORK *mess = sysP->mess;
    HuVec2f *grpPos = MdSpriteGrpPosGet(sysP->sprite, 0);
    HuVec2f *grpScale = MdSpriteGrpScaleGet(sysP->sprite, 0);
    int i;
    u32 winMes;
    s32 mgNo;
    MdMessWinScaleSet(mess, 2, grpScale->x, grpScale->y);
    MdMessWinPosSet(mess, 2, (-155.0f*grpScale->x)+grpPos->x, (-147.0f*grpScale->y)+grpPos->y);
    if(sysP->unk4 == 0) {
        MdOptionTextListUpdate(12, 0x1F0043, 0);
        MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
        MdMessWinMesSet(mess, 2, subNo+0x1F0039);
        for(i=0; i<7; i++) {
            winMes = MdOptionTextListNameGet(listNo, subNo, top+i);
            MdMessWinMesSet(mess, i+4, winMes);
            MdMessWinAttrSet(mess, i+4, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinScaleSet(mess, i+4, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, i+4, (-138.0f*grpScale->x)+grpPos->x, grpPos->y+((-80.0f+(26.0f*i))*grpScale->y));
        }
        {
            u32 insertMes[8] = { 0x1F003F, 0x1F0040, 0x1F0041, 0x1F0042, -1, -1, -1, -1 };
            MdOptionTextListUpdate(9, insertMes[0], ListMgNumTbl[subNo+(listNo*5)]/10);
            MdOptionTextListUpdate(9, insertMes[1], ListMgNumTbl[subNo+(listNo*5)]%10);
            MdOptionTextListUpdate(9, insertMes[2], ListNumTbl[subNo+(listNo*5)]/10);
            MdOptionTextListUpdate(9, insertMes[3], ListNumTbl[subNo+(listNo*5)]%10);
            MdMessWinInsertMultiMesSet(mess, 11, 0x1F004D, insertMes);
            MdMessWinScaleSet(mess, 11, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, 11, (114.0f*grpScale->x)+grpPos->x, (108.0f*grpScale->y)+grpPos->y);
        }
    } else if(sysP->unk4 == 2 && sysP->unk8 == 1) {
        fn_1_1AD88();
    } else if(sysP->unk4 == 3 && sysP->unk8 == 0) {
        u32 recMes[8] = { 0x1F003F, 0x1F0040, 0x1F0041, 0x1F0042, 0x1F0043, 0x1F0044, 0x1F0045, -1 };
        for(i=0; i<7; i++) {
            mgNo = MgRecordTbl[i+listNo].mes-MESS_MGNAME_M501+GW_MGNO_BASE;
            if(GWMgUnlockGet(mgNo)) {
                MdOptionTextListUpdate(MgRecordTbl[i+listNo].type, recMes[i], GwCommon.mgRecord[MgRecordTbl[i+listNo].recNo]);
            } else {
                recMes[i] = 0x1F0051;
            }
            MdMessWinMesSet(mess, i+11, recMes[i]);
            MdMessWinScaleSet(mess, i+11, grpScale->x, grpScale->y);
            MdMessWinPosSet(mess, i+11, (62.0f*grpScale->x)+grpPos->x, grpPos->y+((-80.0f+(26.0f*i))*grpScale->y));
        }
        for(i=0; i<7; i++) {
            mgNo = MgRecordTbl[i+listNo].mes-MESS_MGNAME_M501+GW_MGNO_BASE;
            if(GWMgUnlockGet(mgNo)) {
                recMes[i] = MgRecordTbl[i+listNo].recMes;
            } else {
                recMes[i] = 0x1F004F;
            }
        }
        MdMessWinInsertMultiMesSet(mess, 4, 0x1F003E, recMes);
        MdMessWinScaleSet(mess, 4, grpScale->x, grpScale->y);
        MdMessWinPosSet(mess, 4, (-228.0f*grpScale->x)+grpPos->x, (-80.0f*grpScale->y)+grpPos->y);
    }
}

/* 43 insns */
void MdSpriteGrpDispSet(MDSPRITE_WORK *sprite, int grpNo, BOOL dispF)
{
    int i;
    MDSPR_GRP_INFO *grpInfo;
    HUSPRGRPID grpId;
    int grpNum;
    grpInfo = &SpriteGrpInfo[grpNo];
    grpId = sprite->grpId[grpNo];
    grpNum = grpInfo->end-grpInfo->start+1;
    for(i=0; i<grpNum; i++) {
        if(dispF == FALSE) {
            HuSprDispOff(grpId, i);
        } else if(dispF == TRUE) {
            HuSprDispOn(grpId, i);
        }
    }
}

/* 13 insns */
HuVec2f *MdSpriteGrpPosGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->pos;
}

/* 13 insns */
HuVec2f *MdSpriteGrpScaleGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->scale;
}

/* 22 insns */
HuVec2f *MdSpritePosGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->pos;
}

/* 22 insns */
HuVec2f *MdSpriteScaleGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->scale;
}

/* 22 insns */
float *MdSpriteAlphaGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->a;
}

/* 0x2AC8 */ static u32 StarMotTbl[2] = { DATANUM(DATA_mdoption, 36), DATANUM(DATA_mdoption, 37) };

/* 1041 insns */
void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera)
{
    int i;
    int j;
    int mdlNo;
    HU3DMODEL *modelP;
    HuVecF pos;
    float scale = sysP->unk3E0;
    model->unkB74 = 1.0f;
    for(i=0; i<16; i++) {
        model->unkB78[i] = -1;
    }
    model->mdlId[0] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 0));
    Hu3DModelDispOn(model->mdlId[0]);
    Hu3DModelLayerSet(model->mdlId[0], 7);
    Hu3DModelCameraSet(model->mdlId[0], camera->camera[1].bit);
    Hu3DModelPosSet(model->mdlId[0], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[0], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[0], 0, 0, 0);
    Hu3DModelAttrSet(model->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(model->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[0], 1.0f);
    model->mdlId[1] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 1));
    Hu3DModelDispOn(model->mdlId[1]);
    Hu3DModelAttrSet(model->mdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model->mdlId[1], 0);
    Hu3DModelCameraSet(model->mdlId[1], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[1], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[1], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[1], scale, scale, scale);
    model->mdlId[2] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 2));
    Hu3DModelDispOn(model->mdlId[2]);
    Hu3DModelAttrSet(model->mdlId[2], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(model->mdlId[2], 0);
    Hu3DModelCameraSet(model->mdlId[2], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[2], 0, 50, 0);
    Hu3DModelRotSet(model->mdlId[2], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[2], 0, 0, 0);
    {
        s32 fileTbl[26] = {
            DATANUM(DATA_mdoption, 3), DATANUM(DATA_mdoption, 4), DATANUM(DATA_mdoption, 5), DATANUM(DATA_mdoption, 6),
            DATANUM(DATA_mdoption, 24), DATANUM(DATA_mdoption, 7), DATANUM(DATA_mdoption, 8), DATANUM(DATA_mdoption, 9),
            DATANUM(DATA_mdoption, 10), DATANUM(DATA_mdoption, 11), DATANUM(DATA_mdoption, 12), DATANUM(DATA_mdoption, 13),
            DATANUM(DATA_mdoption, 14), DATANUM(DATA_mdoption, 17), DATANUM(DATA_mdoption, 14), DATANUM(DATA_mdoption, 15),
            DATANUM(DATA_mdoption, 16), DATANUM(DATA_mdoption, 19), DATANUM(DATA_mdoption, 18), DATANUM(DATA_mdoption, 22),
            DATANUM(DATA_mdoption, 23), DATANUM(DATA_mdoption, 20), DATANUM(DATA_mdoption, 21), DATANUM(DATA_mdoption, 14),
            DATANUM(DATA_mdoption, 15), DATANUM(DATA_mdoption, 16)
        };
        float posZTbl[4] = { -260, -380, -500, -635 };
        for(i=0; i<=25; i++) {
            model->mdlId[i+3] = Hu3DModelCreateData(fileTbl[i]);
            Hu3DModelDispOn(model->mdlId[i+3]);
            Hu3DModelAttrSet(model->mdlId[i+3], HU3D_MOTATTR_LOOP|HU3D_MOTATTR_SHAPE_LOOP);
            Hu3DModelAttrReset(model->mdlId[i+3], HU3D_MOTATTR_PAUSE|HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DModelLayerSet(model->mdlId[i+3], 3);
            Hu3DModelCameraSet(model->mdlId[i+3], camera->camera[0].bit);
            Hu3DModelRotSet(model->mdlId[i+3], 0, 0, 0);
            Hu3DModelScaleSet(model->mdlId[i+3], 0, 0, 0);
            if(i >= 5) {
                Hu3DModelDispOff(model->mdlId[i+3]);
            } else {
                Hu3DModelPosSet(model->mdlId[i+3], 0, 0, posZTbl[i]);
            }
        }
    }
    {
        s32 fileTbl[2] = { DATANUM(DATA_mdoption, 25), DATANUM(DATA_mdoption, 26) };
        for(i=0; i<2; i++) {
            for(j=0; j<35; j++) {
                mdlNo = 57+j+(i*35);
                if(j == 0) {
                    model->mdlId[mdlNo] = Hu3DModelCreateData(fileTbl[i]);
                } else {
                    model->mdlId[mdlNo] = Hu3DModelLink(model->mdlId[mdlNo-j]);
                }
                Hu3DModelDispOff(model->mdlId[mdlNo]);
                Hu3DModelLayerSet(model->mdlId[mdlNo], 7);
                Hu3DModelCameraSet(model->mdlId[mdlNo], camera->camera[0].bit);
                Hu3DModelPosSet(model->mdlId[mdlNo], 0, 0, 0);
                Hu3DModelRotSet(model->mdlId[mdlNo], 0, 0, 0);
                Hu3DModelScaleSet(model->mdlId[mdlNo], 1, 1, 1);
                Hu3DModelAttrSet(model->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[mdlNo], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSpeedSet(model->mdlId[mdlNo], 1.0f);
            }
        }
    }
    for(i=0; i<4; i++) {
        s32 fileTbl[4] = { DATANUM(DATA_mdoption, 30), DATANUM(DATA_mdoption, 29), DATANUM(DATA_mdoption, 28), DATANUM(DATA_mdoption, 27) };
        for(j=0; j<7; j++) {
            if(j == 0) {
                model->mdlId[29+(i*7)+j] = Hu3DModelCreateData(fileTbl[i]);
            } else {
                model->mdlId[29+(i*7)+j] = Hu3DModelLink(model->mdlId[29+(i*7)]);
            }
            Hu3DModelDispOff(model->mdlId[29+(i*7)+j]);
            Hu3DModelLayerSet(model->mdlId[29+(i*7)+j], 7);
            Hu3DModelCameraSet(model->mdlId[29+(i*7)+j], camera->camera[1].bit);
            Hu3DModelPosSet(model->mdlId[29+(i*7)+j], 0, 0, 0);
            Hu3DModelRotSet(model->mdlId[29+(i*7)+j], 0, 0, 0);
            Hu3DModelScaleSet(model->mdlId[29+(i*7)+j], 1, 1, 1);
            Hu3DModelAttrSet(model->mdlId[29+(i*7)+j], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(model->mdlId[29+(i*7)+j], HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(model->mdlId[29+(i*7)+j], 1.0f);
        }
    }
    model->mdlId[131] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 31));
    Hu3DModelDispOn(model->mdlId[131]);
    Hu3DModelLayerSet(model->mdlId[131], 7);
    Hu3DModelCameraSet(model->mdlId[131], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[131], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[131], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[131], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[131], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[131], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[131], 1.0f);
    model->mdlId[128] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 33));
    Hu3DModelDispOff(model->mdlId[128]);
    Hu3DModelLayerSet(model->mdlId[128], 0);
    Hu3DModelCameraSet(model->mdlId[128], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[128], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[128], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[128], scale, scale, scale);
    Hu3DModelAttrReset(model->mdlId[128], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[128], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[128], 1.0f);
    model->mdlId[130] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 35));
    Hu3DModelDispOff(model->mdlId[130]);
    Hu3DModelLayerSet(model->mdlId[130], 6);
    Hu3DModelCameraSet(model->mdlId[130], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[130], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[130], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[130], 1, 1, 1);
    Hu3DModelAttrReset(model->mdlId[130], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[130], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[130], 1.0f);
    model->mdlId[129] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 34));
    Hu3DModelDispOff(model->mdlId[129]);
    Hu3DModelLayerSet(model->mdlId[129], 0);
    Hu3DModelCameraSet(model->mdlId[129], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[129], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[129], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[129], scale, scale, scale);
    Hu3DModelAttrReset(model->mdlId[129], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[129], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[129], 1.0f);
    model->mdlId[132] = Hu3DHookFuncCreate(FontBGFilter);
    Hu3DModelLayerSet(model->mdlId[132], 7);
    Hu3DModelCameraSet(model->mdlId[132], camera->camera[0].bit);
    Hu3DModelDispOn(model->mdlId[132]);
    for(i=0; i<2; i++) {
        model->motId[i] = Hu3DJointMotionData(model->mdlId[0], StarMotTbl[i]);
    }
    Hu3DMotionSet(model->mdlId[0], model->motId[0]);
    Hu3DModelAttrReset(model->mdlId[0], HU3D_MOTATTR_PAUSE);
    MdOptionWaveEffectModelCreate();
    model->mdlId[127] = Hu3DModelCreateData(DATANUM(DATA_mdoption, 32));
    Hu3DModelDispOff(model->mdlId[127]);
    Hu3DModelLayerSet(model->mdlId[127], 4);
    Hu3DModelCameraSet(model->mdlId[127], camera->camera[0].bit);
    pos = (HuVecF){ 288, 200, 1000 };
    Hu3D2Dto3D(&pos, camera->camera[0].bit, &pos);
    Hu3DModelPosSetV(model->mdlId[127], &pos);
    Hu3DModelRotSet(model->mdlId[127], 90, 0, 0);
    Hu3DModelScaleSet(model->mdlId[127], 0.5f, 0.5f, 0.5f);
    Hu3DModelAttrSet(model->mdlId[127], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[127], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[127], 1.0f);
    Hu3DModelMatHookSet(model->mdlId[127], WaveEffectDrawHook);
    Hu3DLayerHookSet(11, WaveEffectHook);
    MdOptionWaveEffectIndTexMtxSet((HuVecF){ 0, 0, 0.06f }, (HuVecF){ 0, 0, 0.06f });
    MdOptionWaveEffectColorSet((GXColor){ 0, 0, 0, 0 });
    MdOptionWaveEffectSpeedSet(-0.005f);
    for(i=0; i<MDMODEL_MAX; i++) {
        modelP = &Hu3DData[model->mdlId[i]];
        model->posP[i] = &modelP->pos;
        model->rotP[i] = &modelP->rot;
        model->scaleP[i] = &modelP->scale;
    }
    Hu3DLayerHookSet(8, LayerHook);
    Hu3DLayerHookSet(9, LayerHook);
    Hu3DLayerHookSet(10, LayerHook);
    Hu3DLayerHookSet(13, LayerHook);
    MdModelUpdateAmb(model);
    MdModelRumbleSet((GwCommon.rumbleF^1)*2);
    if(GwCommon.rumbleF == 0) {
        Hu3DModelAttrSet(model->mdlId[4], HU3D_MOTATTR_PAUSE);
    }
}

/* 106 insns */
void MdModelSoundTypeSet(int type)
{
    MDMODEL_WORK *model = sysP->model;
    float motTime[3] = { 0, 12, 0 };
    HU3DMODEL *modelP;
    int i;
    int no;
    Hu3DModelDispOff(model->mdlId[15]);
    Hu3DModelDispOff(model->mdlId[26]);
    Hu3DModelDispOff(model->mdlId[27]);
    Hu3DModelDispOff(model->mdlId[28]);
    modelP = &Hu3DData[model->mdlId[type+26]];
    modelP->pos = *model->posP[15];
    model->posP[15] = &modelP->pos;
    modelP->rot = *model->rotP[15];
    model->rotP[15] = &modelP->rot;
    modelP->scale = *model->scaleP[15];
    model->scaleP[15] = &modelP->scale;
    model->mdlId[15] = model->mdlId[type+26];
    for(i=0; i<3; i++) {
        no = (type+i)%3;
        Hu3DMotionTimeSet(model->mdlId[no+17], motTime[no]);
        Hu3DModelAttrSet(model->mdlId[no+17], HU3D_MOTATTR_PAUSE);
    }
    Hu3DModelAttrReset(model->mdlId[type+17], HU3D_MOTATTR_PAUSE);
}

/* 31 insns */
void MdModelRumbleSet(int mode)
{
    MDMODEL_WORK *model = sysP->model;
    SYS *sys = sysP;
    if(mode == 0) {
        if(sys->unk4BC != 0) {
            sys->unk4BC = 3;
        }
    } else if(mode == 1) {
        if(sys->unk4BC == 0) {
            sys->unk4BC = 1;
        }
    } else {
        sys->unk4BC = 2;
    }
}

/* 164 insns */
void MdModelRumbleUpdate(void)
{
    SYS *sys = sysP;
    MDMODEL_WORK *model = sys->model;
    HuVecF scale;
    switch(sys->unk4BC) {
        case 0:
            Hu3DModelDispOff(model->mdlId[7]);
            sys->unk4C0[0] = sys->unk4C0[1] = sys->unk4C8[0] = sys->unk4C8[1] = 0;
            break;
        case 1:
            Hu3DModelDispOn(model->mdlId[7]);
            MdMathOscillate(MDMATH_OSC_90, &sys->unk4C0[0], &sys->unk4C8[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &sys->unk4C0[1], &sys->unk4C8[1], 20);
            scale = *model->scaleP[4];
            PSVECScale(&scale, &scale, sys->unk4C8[0]+(0.75f*sys->unk4C8[1]));
            scale.z = model->scaleP[4]->z;
            *model->scaleP[7] = scale;
            if(sys->unk4C0[0] >= 1.0f) {
                sys->unk4BC++;
            }
            break;
        case 2:
            Hu3DModelDispOn(model->mdlId[7]);
            *model->scaleP[7] = *model->scaleP[4];
            sys->unk4C0[0] = sys->unk4C0[1] = sys->unk4C8[0] = sys->unk4C8[1] = 0;
            break;
        case 3:
            Hu3DModelDispOn(model->mdlId[7]);
            MdMathOscillate(MDMATH_OSC_90, &sys->unk4C0[0], &sys->unk4C8[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &sys->unk4C0[1], &sys->unk4C8[1], 20);
            scale = *model->scaleP[4];
            PSVECScale(&scale, &scale, (1.0f-sys->unk4C8[0])+sys->unk4C8[1]);
            scale.z = model->scaleP[4]->z;
            *model->scaleP[7] = scale;
            if(sys->unk4C0[0] >= 1.0f) {
                sys->unk4BC = 0;
            }
            break;
    }
}

/* 240 insns */
static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx)
{
    MDDEBUGFONT_WORK *debugFont = sysP->debugFont;
    GXColor color = { 0, 0, 0, 128 };
    s16 width = 0;
    if(debugFont->printF == TRUE) {
        Mtx44 proj;
        width = debugFont->maxLen*(int)(8.0f*debugFont->size);
        GXSetViewport(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1);
        MTXOrtho(proj, 0, 480, 0, 640, 0, -16777215);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        MTXIdentity(*mtx);
        GXLoadPosMtxImm(*mtx, GX_PNMTX0);
        GXSetColorUpdate(TRUE);
        GXSetAlphaUpdate(FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetNumChans(1);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColor(GX_COLOR1, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3s16(debugFont->posX, debugFont->posY+debugFont->ofsY, 0);
        GXPosition3s16(debugFont->posX+width, debugFont->posY+debugFont->ofsY, 0);
        GXPosition3s16(debugFont->posX+width, debugFont->posY+debugFont->rowOfsY, 0);
        GXPosition3s16(debugFont->posX, debugFont->posY+debugFont->rowOfsY, 0);
        GXEnd();
    }
}

/* 8 insns */
static void LayerHook(s16 layerNo)
{
    Hu3DZClear();
}

/* 19 insns */
void MdModelAddAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unkB78[i] == -1) {
            model->unkB78[i] = mdlId;
            break;
        }
    }
}

/* 22 insns */
void MdModelRemoveAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unkB78[i] == mdlId) {
            model->unkB78[i] = -1;
            break;
        }
    }
}

/* 29 insns */
void MdModelUpdateAmb(MDMODEL_WORK *model)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unkB78[i] != -1) {
            Hu3DModelAmbSet(model->unkB78[i], model->unkB74, model->unkB74, model->unkB74);
        }
    }
}

/* 1 insns */
void fn_1_17C54(void)
{
}

/* 105 insns */
void MdOptionCursorReset(void)
{
    HUSPRGRPID grpId;
    SYS *sys;
    MDSPRITE_WORK *sprite;
    sys = sysP;
    sprite = sys->sprite;
    grpId = sprite->grpId[0];
    sys->unk464 = 0;
    sys->unk468 = sys->unk46C = 0;
    HuSprScaleSet(grpId, 5, 1, 1);
    HuSprScaleSet(grpId, 7, 1, 1);
    HuSprScaleSet(grpId, 6, 1, 1);
    HuSprScaleSet(grpId, 8, 1, 1);
    HuSprDispOff(grpId, 7);
    HuSprDispOff(grpId, 8);
    HuSprPosSet(grpId, 5, 0, -90);
    HuSprPosSet(grpId, 7, 0, -90);
    HuSprPosSet(grpId, 6, 0, 130);
    HuSprPosSet(grpId, 8, 0, 130);
}

/* 165 insns */
void MdOptionCursorSet(int *cursor, int dir, int listNo, int subNo)
{
    SYS *sys = sysP;
    MDSPRITE_WORK *sprite = sys->sprite;
    int prev = *cursor;
    if(dir == 0) {
        (*cursor)--;
    } else {
        (*cursor)++;
    }
    if(sys->unk4 == 0) {
        MdOptionListCursorClamp(listNo, subNo, cursor);
        MdOptionMgListWinUpdate(sys->sprite, listNo, subNo, *cursor);
    } else if(sys->unk4 == 3) {
        MdOptionRecordCursorClamp(cursor);
        MdOptionMgListWinUpdate(sys->sprite, *cursor, 0, 0);
    }
    if(prev != *cursor) {
        fn_1_A930(9);
        MdOptionCursorReset();
        if(sys->unk4 == 0) {
            MdOptionListCursorPosSet(listNo, subNo, prev);
        } else if(sys->unk4 == 3) {
            MdOptionRecordCursorPosSet(prev);
        }
    }
    sys->unk464 = dir+1;
}

/* 165 insns */
void MdOptionCursorUpdate(void)
{
    SYS *sys = sysP;
    MDSPRITE_WORK *sprite = sysP->sprite;
    HUSPRGRPID grpId = sprite->grpId[0];
    int i;
    if(sys->unk464 != 0) {
        MdMathOscillate(MDMATH_OSC_180, &sys->unk468, &sys->unk46C, 20);
        if(sys->unk464 == 1) {
            for(i=0; i<2; i++) {
                HuSprPosSet(grpId, (i*2)+5, 0, -90.0f+(-10.0f*sys->unk46C));
                HuSprScaleSet(grpId, (i*2)+5, 1.0f+(0.6f*sys->unk46C), 1.0f+(0.25f*sys->unk46C));
                if(i == 1) {
                    HuSprTPLvlSet(grpId, (i*2)+5, sys->unk46C);
                }
            }
        } else {
            for(i=0; i<2; i++) {
                HuSprPosSet(grpId, (i*2)+6, 0, 130.0f+(10.0f*sys->unk46C));
                HuSprScaleSet(grpId, (i*2)+6, 1.0f+(0.6f*sys->unk46C), 1.0f+(0.25f*sys->unk46C));
                if(i == 1) {
                    HuSprTPLvlSet(grpId, (i*2)+6, sys->unk46C);
                }
            }
        }
        if(sys->unk468 >= 1.0f) {
            if(sys->unk4 == 0) {
                MdOptionListCursorPosSet(sys->unk8, sys->unkC, sys->unk10);
            } else if(sys->unk4 == 3) {
                MdOptionRecordCursorPosSet(sys->unkC);
            }
            sys->unk464 = 0;
        }
    }
}

/* 29 insns */
void MdOptionListCursorClamp(int listNo, int subNo, int *cursor)
{
    int num = ListNumTbl[subNo+(listNo*5)];
    if(*cursor < 0) {
        *cursor = 0;
    } else if(num <= 7) {
        *cursor = 0;
    } else if(*cursor > num-7) {
        *cursor = num-7;
    }
}

/* 99 insns */
void MdOptionListCursorPosSet(int listNo, int subNo, int cursor)
{
    HUSPRGRPID grpId;
    int num;
    num = ListNumTbl[subNo+(listNo*5)];
    grpId = sysP->sprite->grpId[0];
    HuSprDispOn(grpId, 5);
    HuSprDispOn(grpId, 6);
    HuSprDispOn(grpId, 7);
    HuSprDispOn(grpId, 8);
    HuSprTPLvlSet(grpId, 7, 0);
    HuSprTPLvlSet(grpId, 8, 0);
    if(num <= 7) {
        HuSprDispOff(grpId, 5);
        HuSprDispOff(grpId, 6);
        HuSprDispOff(grpId, 7);
        HuSprDispOff(grpId, 8);
    } else if(cursor == 0) {
        HuSprDispOff(grpId, 5);
        HuSprDispOff(grpId, 7);
    } else if(cursor >= num-7) {
        HuSprDispOff(grpId, 6);
        HuSprDispOff(grpId, 8);
    }
}

/* 23 insns */
void MdOptionRecordCursorClamp(int *cursor)
{
    int num = 12;
    if(*cursor < 0) {
        *cursor = 0;
    } else if(num <= 7) {
        *cursor = 0;
    } else if(*cursor > num-7) {
        *cursor = num-7;
    }
}

/* 70 insns */
void MdOptionRecordCursorPosSet(int cursor)
{
    HUSPRGRPID grpId;
    int num;
    num = 12;
    grpId = sysP->sprite->grpId[0];
    HuSprDispOn(grpId, 5);
    HuSprDispOn(grpId, 6);
    HuSprDispOn(grpId, 7);
    HuSprDispOn(grpId, 8);
    HuSprTPLvlSet(grpId, 7, 0);
    HuSprTPLvlSet(grpId, 8, 0);
    if(cursor == 0) {
        HuSprDispOff(grpId, 5);
        HuSprDispOff(grpId, 7);
    } else if(cursor >= num-7) {
        HuSprDispOff(grpId, 6);
        HuSprDispOff(grpId, 8);
    }
}

/* 217 insns */
void MdOptionStoryRankUpdate(void)
{
    float angle = 0;
    SYS *sys = sysP;
    MDMODEL_WORK *model = sysP->model;
    int i;
    int j;
    Mtx mtx;
    Mtx rotMtx;
    HuVecF dir;
    switch(sys->unk470) {
        case 0:
            angle = 0;
            if(++sys->unk474 >= 180) {
                sys->unk474 = 0;
                sys->unk470++;
            }
            break;
        case 1:
            sys->unk474++;
            angle = -(2.0f*sys->unk474);
            if(angle < -20.0f) {
                angle = -20.0f;
                sys->unk474 = 0;
                sys->unk470++;
            }
            break;
        case 2:
            sys->unk474++;
            angle = -20.0f+(10.0f*sys->unk474);
            if(angle > 380.0f) {
                angle = 380.0f;
                sys->unk474 = 0;
                sys->unk470++;
            }
            break;
        case 3:
            sys->unk474++;
            angle = 380.0f-sys->unk474;
            if(angle < 360.0f) {
                angle = 0;
                sys->unk474 = sys->unk470 = 0;
            }
            break;
    }
    for(i=0; i<4; i++) {
        for(j=0; j<7; j++) {
            PSVECSubtract(&Hu3DCamera[1].pos, model->posP[29+(i*7)+j], &dir);
            MdMathMtxRotCalc(&dir, &Hu3DCamera[1].up, 0, mtx);
            {
                HuVecF axis = (HuVecF){ mtx[0][1], mtx[1][1], mtx[2][1] };
                PSMTXRotAxisRad(rotMtx, &axis, 0.017453292f*angle);
            }
            PSMTXConcat(rotMtx, mtx, mtx);
            MdMathMtxRotGet(mtx, &dir);
            Hu3DModelRotSetV(model->mdlId[29+(i*7)+j], &dir);
        }
    }
}

/* 294 insns */
void MdOptionStoryRankStarUpdate(void)
{
    float angleY = 0;
    float angleZ = 0;
    SYS *sys = sysP;
    MDMODEL_WORK *model = sysP->model;
    int i;
    int j;
    Mtx mtx;
    Mtx rotMtx;
    HuVecF dir;
    switch(sys->unk478) {
        case 0:
            angleY = 0;
            if(++sys->unk47C >= 180) {
                sys->unk47C = 0;
                sys->unk478++;
            }
            angleZ = 5.0*sin((3.141592653589793*((2160.0f*sys->unk47C)/180.0f))/180.0);
            break;
        case 1:
            sys->unk47C++;
            angleY = -(4.0f*sys->unk47C);
            if(angleY < -40.0f) {
                angleY = -40.0f;
                sys->unk47C = 0;
                sys->unk478++;
            }
            break;
        case 2:
            sys->unk47C++;
            angleY = -40.0f+(11.0f*sys->unk47C);
            if(angleY > 400.0f) {
                angleY = 400.0f;
                sys->unk47C = 0;
                sys->unk478++;
            }
            break;
        case 3:
            sys->unk47C++;
            angleY = 400.0f-(2.0f*sys->unk47C);
            if(angleY < 360.0f) {
                angleY = 0;
                sys->unk47C = sys->unk478 = sys->unk474 = sys->unk470 = 0;
            }
            break;
    }
    for(i=0; i<2; i++) {
        for(j=0; j<35; j++) {
            PSVECSubtract(&Hu3DCamera[0].pos, model->posP[57+(i*35)+j], &dir);
            MdMathMtxRotCalc(&dir, &Hu3DCamera[0].up, 0, mtx);
            {
                HuVecF axisY = (HuVecF){ mtx[0][1], mtx[1][1], mtx[2][1] };
                HuVecF axisZ = (HuVecF){ mtx[0][2], mtx[1][2], mtx[2][2] };
                PSMTXRotAxisRad(rotMtx, &axisY, 0.017453292f*angleY);
                PSMTXConcat(rotMtx, mtx, mtx);
                PSMTXRotAxisRad(rotMtx, &axisZ, 0.017453292f*angleZ);
                PSMTXConcat(rotMtx, mtx, mtx);
            }
            MdMathMtxRotGet(mtx, &dir);
            Hu3DModelRotSetV(model->mdlId[57+(i*35)+j], &dir);
        }
    }
}

/* 29 insns */
void MdOptionTrigSprReset(void)
{
    SYS *sys = sysP;
    MDSPRITE_WORK *sprite = sys->sprite;
    HUSPRGRPID grpId = sprite->grpId[0];
    HuSprBankSet(grpId, 3, 0);
    HuSprBankSet(grpId, 4, 2);
    sys->unk480 = sys->unk484 = 0;
}

/* 37 insns */
void MdOptionTrigSprSet(int type)
{
    SYS *sys = sysP;
    MDSPRITE_WORK *sprite = sys->sprite;
    HUSPRGRPID grpId = sprite->grpId[0];
    MdOptionTrigSprReset();
    sys->unk480 = type+1;
}

/* 54 insns */
void MdOptionTrigSprUpdate(void)
{
    SYS *sys = sysP;
    HUSPRGRPID grpId;
    MDSPRITE_WORK *sprite;
    sprite = sysP->sprite;
    grpId = sprite->grpId[0];
    if(sys->unk480 != 0) {
        sys->unk484++;
        if(sys->unk484 < 10) {
            if(sys->unk480 == 1) {
                HuSprBankSet(grpId, 3, 1);
            } else {
                HuSprBankSet(grpId, 4, 3);
            }
        } else {
            HuSprBankSet(grpId, 3, 0);
            HuSprBankSet(grpId, 4, 2);
            sys->unk480 = sys->unk484 = 0;
        }
    }
}

/* 17 insns */
void MdOptionWaveEffectSet(int type, int mode)
{
    SYS *sys = sysP;
    if(sys->unk48C == 0) {
        sys->unk48C = 1;
        sys->unk488 = type;
        sys->unk490 = mode;
        sys->unk494 = 90;
    }
}

/* 246 insns */
void MdOptionWaveEffectUpdate(void)
{
    SYS *sys = sysP;
    MDMODEL_WORK *model = sys->model;
    MDCAMERA_WORK *camera = sys->camera;
    HuVecF pos2D;
    HuVecF pos;
    HuVecF scale;
    if(sys->unk488 != 0) {
        pos = *model->posP[sys->unk488+2];
        scale = *model->scaleP[sys->unk488+2];
        Hu3DModelDispOn(model->mdlId[127]);
        MdMath3Dto2D(&pos, camera->camera[0].bit, &pos2D);
        if(sys->unk490 == 1) {
            pos2D.y -= 15.0f;
        } else if(sys->unk490 == 2) {
            pos2D.y -= 30.0f;
        }
        pos2D.z *= -1.0f;
        pos2D.z -= 500.0f;
        Hu3D2Dto3D(&pos2D, camera->camera[0].bit, &pos2D);
        Hu3DModelPosSetV(model->mdlId[127], &pos2D);
        if(sys->unk490 == 0) {
            Hu3DModelRotSet(model->mdlId[127], 90, 0, 0);
        } else if(sys->unk490 == 1) {
            Hu3DModelRotSet(model->mdlId[127], 45, 0, 0);
        } else if(sys->unk490 == 2) {
            Hu3DModelRotSet(model->mdlId[127], 30, 0, 0);
        }
        Hu3DModelScaleSet(model->mdlId[127], 0.25f, 1.0f, 0.25f);
        MdOptionWaveEffectIndTexMtxSet((HuVecF){ 0, 0, (0.09f*sys->unk494)/90.0f }, (HuVecF){ 0, 0, (0.09f*sys->unk494)/90.0f });
        MdOptionWaveEffectSpeedSet((-0.02f*sys->unk494)/90.0f);
        if(--sys->unk494 <= 0) {
            sys->unk488 = sys->unk490 = sys->unk494 = 0;
            Hu3DModelDispOff(model->mdlId[127]);
        }
    }
}

/* 75 insns */
void MdOptionWaveEffectModelCreate(void)
{
    SYS *sys = sysP;
    sys->unk3A8 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    sys->unk3AC = HuSprAnimDataRead(DATANUM(DATA_mdoption, 76));
    sys->unk3B0 = HuSprAnimDataRead(DATANUM(DATA_mdoption, 77));
    sys->unk3BC[0][0] = sys->unk3BC[0][1] = sys->unk3BC[0][2] = sys->unk3BC[1][0] = sys->unk3BC[1][1] = sys->unk3BC[1][2] = 0;
    sys->unk3D4 = (GXColor){ 0, 0, 0, 0 };
    sys->unk3B4 = 0;
    sys->unk3B8 = -0.02f;
}

/* 23 insns */
void MdOptionWaveEffectModelKill(void)
{
    SYS *sys = sysP;
    if(sys->unk3A8 != 0) {
        HuMemDirectFree(sys->unk3A8);
        sys->unk3A8 = 0;
        HuSprAnimKill(sys->unk3AC);
        HuSprAnimKill(sys->unk3B0);
    }
}

/* 42 insns */
static void WaveEffectHook(s16 layerNo)
{
    SYS *sys = sysP;
    HU3DWATER *water = &Hu3DWaterData;
    if(Hu3DCameraBit & 1) {
        GXSetTexCopySrc(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT);
        GXSetTexCopyDst(HU_FB_WIDTH/2, HU_FB_HEIGHT/2, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(sys->unk3A8, GX_FALSE);
        if(omUPauseFlag+omPauseChk() != 0) {
            return;
        }
    }
}

/* 20 insns */
void MdOptionWaveEffectIndTexMtxSet(HuVecF row0, HuVecF row1)
{
    SYS *sys = sysP;
    sys->unk3BC[0][0] = row0.x;
    sys->unk3BC[0][1] = row0.y;
    sys->unk3BC[0][2] = row0.z;
    sys->unk3BC[1][0] = row1.x;
    sys->unk3BC[1][1] = row1.y;
    sys->unk3BC[1][2] = row1.z;
}

/* 12 insns */
void MdOptionWaveEffectColorSet(GXColor color)
{
    sysP->unk3D4 = color;
}

/* 5 insns */
void MdOptionWaveEffectSpeedSet(float speed)
{
    sysP->unk3B8 = speed;
}

/* 327 insns */
static void WaveEffectDrawHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    SYS *sys = sysP;
    HU3DCAMERA *cameraP = &Hu3DCamera[0];
    float transS;
    Mtx objMtx;
    Mtx scaleMtx;
    Mtx mtx;
    Mtx lightMtx;
    Mtx invCamMtx;
    GXTexObj texObj;
    int pauseF;
    if((pauseF = omUPauseFlag+omPauseChk()) == 0) {
        sys->unk3B4 += sys->unk3B8;
    }
    GXInitTexObj(&texObj, sys->unk3A8, HU_FB_WIDTH/2, HU_FB_HEIGHT/2, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0, 0, 0, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    HuSprTexLoad(sys->unk3AC, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(sys->unk3B0, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    transS = (Hu3DCamera[0].scissorX+(Hu3DCamera[0].scissorW/2.0f))/640.0f;
    C_MTXLightPerspective(lightMtx, cameraP->fov, 1.2f, 0.5f, -0.5f, transS, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, invCamMtx);
    PSMTXConcat(invCamMtx, drawObj->matrix, objMtx);
    PSMTXConcat(lightMtx, Hu3DCameraMtx, mtx);
    PSMTXConcat(mtx, objMtx, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(objMtx, 0, sys->unk3B4, 0);
    PSMTXScale(scaleMtx, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(scaleMtx, objMtx, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, sys->unk3D4);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, sys->unk3BC, -1);
}

/* 114 insns */
void MdOptionCapsuleOrbitUpdate(void)
{
    SYS *sys = sysP;
    MDMODEL_WORK *model = sys->model;
    MDCAMERA_WORK *camera = sys->camera;
    int i;
    HU3DMODELID mdlId;
    for(i=0; i<2; i++) {
        mdlId = (i == 0) ? model->mdlId[128] : model->mdlId[129];
        switch(sys->unk498[i]) {
            case 0:
                Hu3DModelDispOff(mdlId);
                Hu3DModelPosSet(mdlId, 0, -1.0f*(s32)frandmod(1200), 0);
                sys->unk4A0[i] = 0;
                sys->unk4A8[i] = frandmod(2400)+2400;
                sys->unk498[i]++;
                break;
            case 1:
                if(++sys->unk4A0[i] > sys->unk4A8[i]) {
                    Hu3DModelDispOn(mdlId);
                    Hu3DMotionTimeSet(mdlId, 0);
                    sys->unk498[i]++;
                }
                break;
            case 2:
                if(Hu3DMotionEndCheck(mdlId)) {
                    sys->unk498[i] = 0;
                }
                break;
        }
    }
}

/* 10 insns */
void MdOptionCapsuleOrbitOutSet(int mdlNo)
{
    sysP->unk4B0 = 1;
    sysP->unk4B4 = mdlNo;
}

/* 6 insns */
void MdOptionCapsuleOrbitHideSet(void)
{
    sysP->unk4B0 = 0;
}

/* 90 insns */
void MdOptionCapsuleOrbitOutUpdate(void)
{
    SYS *sys = sysP;
    MDMODEL_WORK *model = sys->model;
    Mtx mtx;
    HuVecF dir;
    if(sys->unk4B0 == 0) {
        Hu3DModelDispOff(model->mdlId[130]);
    } else {
        Hu3DModelDispOn(model->mdlId[130]);
    }
    PSVECSubtract(&Hu3DCamera[0].pos, model->posP[sys->unk4B4], &dir);
    PSVECNormalize(&dir, &dir);
    MdMathMtxRotCalc(&dir, &Hu3DCamera[0].up, 0, mtx);
    MdMathMtxRotGet(mtx, &dir);
    Hu3DModelRotSetV(model->mdlId[130], &dir);
    Hu3DModelScaleSet(model->mdlId[130], model->scaleP[sys->unk4B4]->x, model->scaleP[sys->unk4B4]->y, model->scaleP[sys->unk4B4]->z);
    Hu3DModelLayerSet(model->mdlId[130], Hu3DData[model->mdlId[sys->unk4B4]].layerNo);
    *model->posP[130] = *model->posP[sys->unk4B4];
}

/* 166 insns */
void MdOptionSpriteTitleUpdate(void)
{
    SYS *sys = sysP;
    MDSPRITE_WORK *sprite = sys->sprite;
    HuVecF pos;
    if(sys->unk4D0 == 0) {
        sys->unk4D4 = sys->unk4D8 = 0;
    } else if(sys->unk4D0 == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk4D4, &sys->unk4D8, 15);
        pos.x = 288;
        pos.y = -128.0f+(192.0f*sys->unk4D8);
        MdOptionTitlePosSet(sprite, pos);
        if(sys->unk4D4 >= 1.0f) {
            sys->unk4D0 = 0;
            sys->unk4D4 = sys->unk4D8 = 0;
        }
    } else {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->unk4D4, &sys->unk4D8, 15);
        pos.x = 288;
        pos.y = 64.0f-(192.0f*sys->unk4D8);
        MdOptionTitlePosSet(sprite, pos);
        if(sys->unk4D4 >= 1.0f) {
            sys->unk4D0 = 0;
            sys->unk4D4 = sys->unk4D8 = 0;
        }
    }
}

