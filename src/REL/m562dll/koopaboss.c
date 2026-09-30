/*
 * m562dll koopaboss.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/koopaboss.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
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
static const float lbl_1_rodata_478 = 5.5f; /* 0x478 */
static const float lbl_1_rodata_47C = 0.0f; /* 0x47C */
static const float lbl_1_rodata_480 = 4.0f; /* 0x480 */
static const float lbl_1_rodata_484 = 1.5f; /* 0x484 */
static const float lbl_1_rodata_488 = -30.0f; /* 0x488 */
static const float lbl_1_rodata_48C = 0.75f; /* 0x48C */
static const float lbl_1_rodata_490 = 9.66f; /* 0x490 */
static const float lbl_1_rodata_494 = 100.0f; /* 0x494 */
static const float lbl_1_rodata_498 = 800.0f; /* 0x498 */
static const float lbl_1_rodata_49C = 1.0f; /* 0x49C */
static const float lbl_1_rodata_4A0 = 200.0f; /* 0x4A0 */
static const float lbl_1_rodata_4A4 = 0.05f; /* 0x4A4 */
static const float lbl_1_rodata_4A8 = 80.0f; /* 0x4A8 */
static const float lbl_1_rodata_4AC = 0.5f; /* 0x4AC */
static const float lbl_1_rodata_4B0 = -1.0f; /* 0x4B0 */
static const float lbl_1_rodata_4B4 = 40.0f; /* 0x4B4 */
static const float lbl_1_rodata_4B8 = 0.9f; /* 0x4B8 */
static const float lbl_1_rodata_4BC = 90.0f; /* 0x4BC */
static const float lbl_1_rodata_4C0 = 0.96f; /* 0x4C0 */
static const float lbl_1_rodata_4C4 = -1.2217305f; /* 0x4C4 */
static const float lbl_1_rodata_4C8 = 220.0f; /* 0x4C8 */
static const float lbl_1_rodata_4CC = 250.0f; /* 0x4CC */
static const double lbl_1_rodata_4D0 = 180.0; /* 0x4D0 */
static const double lbl_1_rodata_4D8 = 3.141592653589793; /* 0x4D8 */
static const double lbl_1_rodata_4E0 = 360.0; /* 0x4E0 */
static const double lbl_1_rodata_4E8 = -180.0; /* 0x4E8 */
/* 0x4F0 lbl_1_rodata_4F0 (0xC): 0x00000000 0x42480000 0x43160000 -- an aggregate initialiser, write it as a local */
/* 0x4FC lbl_1_rodata_4FC (0xC): 0x00000000 0x42480000 0x43160000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_508 = -341.66666f; /* 0x508 */
static const float lbl_1_rodata_50C = 341.66666f; /* 0x50C */
static const float lbl_1_rodata_510 = 10000.0f; /* 0x510 */
static const double lbl_1_rodata_518 = 40.0; /* 0x518 */
static const double lbl_1_rodata_520 = 100.0; /* 0x520 */
static const double lbl_1_rodata_528 = 500.0; /* 0x528 */
static const float lbl_1_rodata_530 = 1025.0f; /* 0x530 */
static const float lbl_1_rodata_534 = -1025.0f; /* 0x534 */
static const float lbl_1_rodata_538 = 500.0f; /* 0x538 */
static const float lbl_1_rodata_53C = -300.0f; /* 0x53C */
/* 0x540 lbl_1_rodata_540 = 4503599627370496: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_548 = 50.0; /* 0x548 */
static const double lbl_1_rodata_550 = 3.0; /* 0x550 */
static const float lbl_1_rodata_558 = 24.0f; /* 0x558 */
static const float lbl_1_rodata_55C = 360.0f; /* 0x55C */
static const float lbl_1_rodata_560 = 8.0f; /* 0x560 */
static const double lbl_1_rodata_568 = 0.5; /* 0x568 */
static const float lbl_1_rodata_570 = 18.0f; /* 0x570 */
static const double lbl_1_rodata_578 = 45.0; /* 0x578 */
static const float lbl_1_rodata_580 = 0.03125f; /* 0x580 */
static const float lbl_1_rodata_584 = 16.0f; /* 0x584 */
/* 0x588 lbl_1_rodata_588 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x590 lbl_1_rodata_590 (0xC): 0x00000000 0x42480000 0x42C80000 -- an aggregate initialiser, write it as a local */
/* 0x59C lbl_1_rodata_59C (0xC): 0x00000000 0x42480000 0x42C80000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5A8 = 60.0f; /* 0x5A8 */
static const float lbl_1_rodata_5AC = 2.0f; /* 0x5AC */
static const float lbl_1_rodata_5B0 = 0.4f; /* 0x5B0 */
static const float lbl_1_rodata_5B4 = 0.6f; /* 0x5B4 */
static const float lbl_1_rodata_5B8 = 120.0f; /* 0x5B8 */
static const float lbl_1_rodata_5BC = 55.0f; /* 0x5BC */
static const float lbl_1_rodata_5C0 = 4.1666665f; /* 0x5C0 */
static const float lbl_1_rodata_5C4 = 10.0f; /* 0x5C4 */
static const float lbl_1_rodata_5C8 = 0.7f; /* 0x5C8 */
static const float lbl_1_rodata_5CC = 0.3f; /* 0x5CC */
static const float lbl_1_rodata_5D0 = 1400.0f; /* 0x5D0 */
static const float lbl_1_rodata_5D4 = 180.0f; /* 0x5D4 */
static const float lbl_1_rodata_5D8 = 30.0f; /* 0x5D8 */
static const float lbl_1_rodata_5DC = 70.0f; /* 0x5DC */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x783E gap_05_0000783E_bss (0x2): alignment gap */
/* 0x783C */ s16 lbl_1_bss_783C;
/* 0x7838 */ float lbl_1_bss_7838;
/* 0x7834 */ s32 lbl_1_bss_7834; /* mecha target taken */
/* 0x7830 */ M562_MECHAENTRY *lbl_1_bss_7830; /* mecha breath target */
/* 0x782E */ s16 lbl_1_bss_782E;
/* 0x782C */ s16 lbl_1_bss_782C;
/* 0x7828 */ M562_SUNBOMBOBJ *lbl_1_bss_7828; /* sun bomb being thrown */

/* --- functions (reference order), .data placed before its first user --- */
/* 0x880 */ u32 lbl_1_data_880[19] = { DATANUM(DATA_m562, 61), DATANUM(DATA_m562, 62), DATANUM(DATA_m562, 63), DATANUM(DATA_m562, 64), DATANUM(DATA_m562, 65), DATANUM(DATA_m562, 66), DATANUM(DATA_m562, 67), DATANUM(DATA_m562, 68), DATANUM(DATA_m562, 69), DATANUM(DATA_m562, 70), DATANUM(DATA_m562, 71), DATANUM(DATA_m562, 72), DATANUM(DATA_m562, 73), DATANUM(DATA_m562, 74), DATANUM(DATA_m562, 75), DATANUM(DATA_m562, 76), DATANUM(DATA_m562, 77), DATANUM(DATA_m562, 78), DATANUM(DATA_m562, 79) };
/* 0x8CC */ HuVecF lbl_1_data_8CC = { 0.0f, -500.0f, -1250.0f };

#define KB_CLAMP(v, lo, hi) (((v) > (hi)) ? (hi) : (((v) < (lo)) ? (lo) : (v)))
#define KB_ABS(v) (((v) >= 0.0f) ? (v) : -(v))

void fn_1_F784(M562_KOOPABOSS *boss, M562_WORK *work)
{
    M562_WORK *w = work;
    M562_CAMERA *camera = &w->camera[0];
    HU3DMODELID modelId;
    s32 i;

    memset(boss, 0, sizeof(M562_KOOPABOSS));
    boss->unk000 = work;
    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x1A));
    boss->unk020 = modelId;
    Hu3DModelScaleSet(modelId, 5.5f, 5.5f, 5.5f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk010 = boss->unk014 = 0;
    boss->unk058 = lbl_1_data_8CC;
    Hu3DModelPosSet(modelId, boss->unk058.x, boss->unk058.y, boss->unk058.z);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 19; i++) {
        boss->unk022[i] = Hu3DJointMotionData(modelId, lbl_1_data_880[i]);
    }
    Hu3DMotionSet(modelId, boss->unk022[1]);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(modelId, boss->unk022[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
    boss->unk050 = boss->unk052 = 1;
    boss->unk054 = 1;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x1C));
    boss->unk11C = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk11E = Hu3DJointMotionData(modelId, DATANUM(DATA_m562, 0x51));
    Hu3DMotionSet(modelId, boss->unk11E);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x1F));
    boss->unk120 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk122 = Hu3DJointMotionData(modelId, DATANUM(DATA_m562, 0x54));
    Hu3DMotionSet(modelId, boss->unk122);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x1D));
    boss->unk136 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk138 = Hu3DJointMotionData(modelId, DATANUM(DATA_m562, 0x52));
    Hu3DMotionSet(modelId, boss->unk138);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x1E));
    boss->unk13A = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.5f, 1.5f, 1.5f);
    Hu3DModelRotSet(modelId, -30.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk13C = Hu3DJointMotionData(modelId, DATANUM(DATA_m562, 0x53));
    Hu3DMotionSpeedSet(modelId, 0.75f);
    Hu3DMotionSet(modelId, boss->unk13C);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    boss->unk140 = 0;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x15));
    boss->unk130 = modelId;
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m562, 0x22));
    boss->unk132 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    boss->unk134 = Hu3DJointMotionData(modelId, DATANUM(DATA_m562, 0x57));
    Hu3DMotionSet(modelId, boss->unk134);
    Hu3DMotionSpeedSet(modelId, 9.66f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);

    boss->unk144 = -1;
    boss->unk148 = 0.0f;
    boss->unk3F4 = -1;
    if (w->unk0020 == 0) {
        boss->unk00E = 60;
    } else if (w->unk0020 == 1) {
        boss->unk00E = 80;
    } else if (w->unk0020 == 2) {
        boss->unk00E = 100;
    } else {
        boss->unk00E = 120;
    }
    boss->unk018 = 5;
    fn_1_1EE3C(&boss->unk14C, boss);
    boss->unk004 = 1;
    boss->unk008 = 100;
    fn_1_2CD6C(&w->unk286C[2], 45);
    fn_1_2CE3C(&w->unk286C[2], fn_1_10348);
}

void fn_1_10018(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    s32 i;

    if (boss->unk144 >= 0) {
        Hu3DGLightKill(boss->unk144);
    }
    fn_1_2CDE8(&work->unk286C[2]);
    fn_1_1F138(&boss->unk14C);
    Hu3DMotionKill(boss->unk134);
    Hu3DModelKill(boss->unk132);
    Hu3DModelKill(boss->unk130);
    Hu3DMotionKill(boss->unk13C);
    Hu3DModelKill(boss->unk13A);
    Hu3DMotionKill(boss->unk138);
    Hu3DModelKill(boss->unk136);
    Hu3DMotionKill(boss->unk122);
    Hu3DModelKill(boss->unk120);
    Hu3DMotionKill(boss->unk11E);
    Hu3DModelKill(boss->unk11C);
    for (i = 0; i < 19; i++) {
        Hu3DMotionKill(boss->unk022[i]);
    }
    Hu3DModelKill(boss->unk020);
    memset(boss, 0, sizeof(M562_KOOPABOSS));
}

/* 0x8D8 */ HuVecF lbl_1_data_8D8 = { 0.0f, 0.0f, -100.0f };

MtxPtr fn_1_1010C(M562_KOOPABOSS *boss)
{
    if (!boss->unk110) {
        Hu3DModelObjMtxGet(boss->unk020, "g000mSP-itemhook_R", boss->unk080);
        boss->unk110 = 1;
    }
    return boss->unk080;
}

MtxPtr fn_1_10160(M562_KOOPABOSS *boss)
{
    if (!boss->unk114) {
        Hu3DModelObjMtxGet(boss->unk020, "g000mSP-itemhook_L", boss->unk0B0);
        boss->unk114 = 1;
    }
    return boss->unk0B0;
}

MtxPtr fn_1_101B4(M562_KOOPABOSS *boss)
{
    if (!boss->unk118) {
        Hu3DModelObjMtxGet(boss->unk020, "g000mSP-head", boss->unk0E0);
        boss->unk118 = 1;
    }
    return boss->unk0E0;
}

void fn_1_10208(M562_KOOPABOSS *boss)
{
    M562_SUNBOMB *sunbomb = &boss->unk14C;
    s32 flameHit;
    s32 i;
    M562_SUNBOMBOBJ *obj;

    if (boss->unk004 != 7) {
        boss->unk052 = 9;
        boss->unk054 = 0;
        if (boss->unk3F4 >= 0) {
            fn_1_83C(boss->unk3F4);
            boss->unk3F4 = -1;
        }
        fn_1_814(0x8B4);
        flameHit = 0;
        if (boss->unk124 != 1 && boss->unk124 == 2) {
            boss->unk126 = 0;
            boss->unk124 = 5;
            flameHit = 1;
        }
        boss->unk00C = boss->unk004;
        boss->unk008 = 60;
        if (boss->unk004 == 6 && flameHit == 0) {
            boss->unk00C = 1;
            boss->unk008 = boss->unk00E;
        }
        boss->unk004 = 7;
        Hu3DModelAttrSet(boss->unk136, HU3D_ATTR_DISPOFF);
        for (i = 0; i < 5; i++) {
            obj = &sunbomb->unk004[i];
            if (obj->unk10 != 0 && obj->unk04 <= 2) {
                obj->unk08 = 0;
                obj->unk04 = 8;
            }
        }
        boss->unk018--;
    }
}

void fn_1_10348(M562_HITENTRY *a, M562_HITENTRY *b)
{
    if (a->unk00 == 0 && b->unk00 == 4) {
        fn_1_10520(a->unk08);
    } else if (b->unk00 == 0 && a->unk00 == 4) {
        fn_1_10520(b->unk08);
    } else if (a->unk00 == 0 && b->unk00 == 5) {
        fn_1_10AF0(a->unk08, b->unk08);
    } else if (b->unk00 == 0 && a->unk00 == 5) {
        fn_1_10AF0(b->unk08, a->unk08);
    } else if (a->unk00 == 0 && b->unk00 == 6) {
        fn_1_10FEC(a->unk08);
    } else if (b->unk00 == 0 && a->unk00 == 6) {
        fn_1_10FEC(b->unk08);
    } else if (a->unk00 == 5 && b->unk00 == 4) {
        fn_1_10588(a->unk08, b);
    } else if (b->unk00 == 5 && a->unk00 == 4) {
        fn_1_10588(b->unk08, a);
    } else if (a->unk00 == 5 && b->unk00 == 7) {
        fn_1_10918(a->unk08, b);
    } else if (b->unk00 == 5 && a->unk00 == 7) {
        fn_1_10918(b->unk08, a);
    } else if (b->unk00 == 5 && a->unk00 == 5) {
        fn_1_10784(a->unk08, b->unk08);
    }
}

void fn_1_10520(M562_PLAYER *player)
{
    M562_WORK *work = player->unk000;

    if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0 && work->unk000C == 4) {
        player->unk00A = 0;
        player->unk006 = 0;
        player->unk008 = 0;
        player->unk004 = 4;
    }
}

void fn_1_10588(M562_SUNBOMBOBJ *obj, M562_HITENTRY *hit)
{
    HuVecF dir;
    float dist;
    float t;

    PSVECSubtract(&obj->unk38, &hit->unk0C, &dir);
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (dist < 100.0f) {
        if (obj->unk04 == 5) {
            obj->unk04 = 6;
        }
        PSVECSubtract(&obj->unk38, &lbl_1_data_8D8, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        t = dist / 800.0f;
        t = KB_CLAMP(t, 0.0f, 1.0f);
        t = 1.0f - t;
        if (dir.z < 200.0f) {
            dir.z = 200.0f;
        }
        if (!dir.x && !dir.z) {
            dir.z = 800.0f;
        }
        PSVECScale(&dir, &dir, 0.05f * t);
        PSVECAdd(&obj->unk38, &dir, &obj->unk38);
    }
}

void fn_1_10784(M562_SUNBOMBOBJ *a, M562_SUNBOMBOBJ *b)
{
    HuVecF dir;
    float dist;

    PSVECSubtract(&a->unk38, &b->unk38, &dir);
    dist = PSVECMag(&dir);
    if (dist < 80.0f) {
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dir.x || dir.z) {
            PSVECNormalize(&dir, &dir);
        } else {
            dir.z = 1.0f;
        }
        PSVECScale(&dir, &dir, 0.5f * (80.0f - dist));
        PSVECAdd(&a->unk38, &dir, &a->unk38);
        PSVECScale(&dir, &dir, -1.0f);
        PSVECAdd(&b->unk38, &dir, &b->unk38);
        if (a->unk38.y < 0.0f) {
            a->unk38.y = 0.0f;
        }
        if (b->unk38.y < 0.0f) {
            b->unk38.y = 0.0f;
        }
    }
}

void fn_1_10918(M562_SUNBOMBOBJ *obj, M562_HITENTRY *hit)
{
    M562_SUNBOMB *sunbomb = obj->unk00;
    M562_KOOPABOSS *boss = sunbomb->unk000;
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    M562_CAMERA *camera = &work->camera[0];
    HuVecF dir;
    float dist;

    PSVECSubtract(&obj->unk38, &hit->unk0C, &dir);
    dist = PSVECMag(&dir);
    if (dist < 40.0f + hit->unk18) {
        if (dir.x || dir.z) {
            PSVECNormalize(&dir, &dir);
        } else {
            dir.z = 1.0f;
        }
        PSVECScale(&dir, &dir, (40.0f + hit->unk18) - dist);
        PSVECAdd(&obj->unk38, &dir, &obj->unk38);
        if (obj->unk0C == 2 && boss->unk004 != 7) {
            fn_1_10208(boss);
            Hu3DMotionTimeSet(boss->unk13A, 0.0f);
            Hu3DModelPosSet(boss->unk13A, obj->unk38.x, 100.0f + obj->unk38.y, obj->unk38.z);
            Hu3DModelAttrReset(boss->unk13A, HU3D_ATTR_DISPOFF);
            boss->unk140 = 1;
            obj->unk04 = 10;
            fn_1_814(0x8B2);
            fn_1_21B68(camera, 1, 50, 80.0f, 0.9f, 90.0f);
            omVibrate(player->unk014, 10, 12, 0);
        }
    }
}

void fn_1_10AF0(M562_PLAYER *player, M562_SUNBOMBOBJ *obj)
{
    M562_WORK *work = player->unk000;
    float pBottom;
    float oBottom;
    float pTop;
    float oTop;
    float pMid;
    float oMid;
    float dist;
    float rate;
    float pHalf;
    float oHalf;
    float maxHalf;
    float gap;
    float minHalf;
    s32 hit;
    HuVecF dir;

    pBottom = player->unk0A0.y;
    pTop = pBottom + player->unk068;
    oBottom = obj->unk38.y;
    oTop = 80.0f + oBottom;
    dir.x = player->unk0A0.x - obj->unk38.x;
    dir.y = 0.0f;
    dir.z = player->unk0A0.z - obj->unk38.z;
    dist = PSVECMag(&dir);
    if (((pTop == oTop && pBottom == oBottom) || (pTop <= oTop && pTop >= oBottom) || (pBottom <= oTop && pBottom >= oBottom)
            || (oTop <= pTop && oTop >= pBottom) || (oBottom <= pTop && oBottom >= pBottom))
        && dist < 100.0f) {
        if (dir.x || dir.z) {
            PSVECNormalize(&dir, &dir);
        } else {
            dir.x = 0.0f;
            dir.z = 1.0f;
        }
        PSVECScale(&dir, &dir, 100.0f - dist);
        pMid = 0.5f * (pBottom + pTop);
        oMid = 0.5f * (oBottom + oTop);
        pHalf = KB_ABS(pMid - pBottom);
        oHalf = KB_ABS(oMid - oBottom);
        maxHalf = (pHalf > oHalf) ? pHalf : oHalf;
        minHalf = (pHalf > oHalf) ? oHalf : pHalf;
        gap = KB_ABS(pMid - oMid);
        rate = (gap < maxHalf) ? 1.0f : 1.0f - (gap - maxHalf) / minHalf;
        player->unk0A0.x = player->unk0A0.x + 0.5f * dir.x * rate;
        player->unk0A0.z = player->unk0A0.z + 0.5f * dir.z * rate;
        obj->unk38.x = obj->unk38.x - 0.5f * dir.x * rate;
        obj->unk38.z = obj->unk38.z - 0.5f * dir.z * rate;
    }
    hit = 0;
    dir.x = player->unk0A0.x - obj->unk38.x;
    dir.y = player->unk0A0.y - obj->unk38.y;
    dir.z = player->unk0A0.z - obj->unk38.z;
    dist = PSVECMag(&dir);
    if (dist < obj->unk1C && obj->unk0C == 0) {
        hit = 1;
    }
    if (hit) {
        if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0 && work->unk000C == 4) {
            player->unk00A = 0;
            player->unk006 = 0;
            player->unk008 = 0;
            player->unk004 = 4;
        }
    }
}

void fn_1_10FEC(M562_PLAYER *player)
{
    M562_WORK *work = player->unk000;

    if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0 && work->unk000C == 4) {
        player->unk00A = 0;
        player->unk006 = 0;
        player->unk008 = 0;
        player->unk004 = 5;
    }
}

void fn_1_11054(M562_KOOPABOSS *boss)
{
    Mtx mtx;
    Mtx rotMtx;
    HuVecF ofs;
    HuVecF pos;
    HuVecF dir;
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    HU3DMODELID modelId;
    MtxPtr headMtx;
    float radius;
    float maxTime;

    if (boss->unk010 != 0 && boss->unk014 == 0) {
        Hu3DModelAttrReset(boss->unk020, HU3D_ATTR_DISPOFF);
        boss->unk014 = 1;
    } else if (boss->unk010 == 0 && boss->unk014 != 0) {
        Hu3DModelAttrSet(boss->unk020, HU3D_ATTR_DISPOFF);
        boss->unk014 = 0;
    }
    if (boss->unk014 != 0) {
        if (boss->unk01C == 0) {
            if (boss->unk004 != 0 && boss->unk004 != 7) {
                Hu3DModelAttrSet(boss->unk136, HU3D_ATTR_DISPOFF);
                boss->unk07C = 0.0f;
                boss->unk052 = 1;
                boss->unk054 = 1;
                boss->unk004 = 0;
            }
        } else if (boss->unk004 == 0) {
            boss->unk004 = 1;
        }
        switch (boss->unk004) {
            case 0:
                break;
            case 1:
                fn_1_11634(boss);
                if (--boss->unk008 <= 0) {
                    boss->unk004 = 2;
                    boss->unk008 = 0;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 2:
                if (fn_1_1183C(boss)) {
                    boss->unk004 = 3;
                    boss->unk008 = boss->unk00E;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 3:
                fn_1_11634(boss);
                if (--boss->unk008 <= 0) {
                    boss->unk004 = 4;
                    boss->unk008 = 0;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 4:
                if (fn_1_12280(boss)) {
                    boss->unk004 = 5;
                    boss->unk008 = boss->unk00E;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 5:
                fn_1_11634(boss);
                if (--boss->unk008 <= 0) {
                    boss->unk004 = 6;
                    boss->unk008 = 0;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 6:
                if (fn_1_12A38(boss)) {
                    boss->unk004 = 1;
                    boss->unk008 = boss->unk00E;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
            case 7:
                if (--boss->unk008 <= 0) {
                    if (boss->unk01C == 0) {
                        boss->unk07C = 0.0f;
                        boss->unk052 = 1;
                        boss->unk054 = 1;
                        boss->unk004 = 0;
                    } else {
                        boss->unk004 = boss->unk00C;
                    }
                    boss->unk008 = 0;
                    boss->unk006 = 0;
                    boss->unk00A = 0;
                }
                break;
        }
        modelId = boss->unk020;
        if (boss->unk050 != boss->unk052 && Hu3DMotionShiftIDGet(modelId) < 0) {
            boss->unk050 = boss->unk052;
            Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(modelId, boss->unk022[boss->unk050], 0.0f, 4.0f, boss->unk054 ? HU3D_MOTATTR_LOOP : 0);
        }
        Hu3DModelPosSet(boss->unk020, boss->unk058.x, boss->unk058.y, boss->unk058.z);
        Hu3DModelRotSet(boss->unk020, boss->unk064.x, boss->unk064.y, boss->unk064.z);
        if (work->unk000C == 4 || work->unk000C == 5) {
            boss->unk078 = fn_1_36EC(boss->unk07C, boss->unk078, 0.96f);
            Hu3DMotionForceSet(boss->unk020, "g000mSP-head", 0x100, boss->unk078);
        }
        fn_1_1F208(&boss->unk14C);
        fn_1_12BA8(boss);
        fn_1_13A24(boss);
        radius = 0.5f * player->unk068;
        pos = player->unk0A0;
        pos.y += radius;
        fn_1_2CE8C(&work->unk286C[2], 0, 0, &pos, radius, player);
        headMtx = fn_1_101B4(boss);
        PSMTXCopy(headMtx, mtx);
        dir.x = mtx[0][2];
        dir.y = mtx[1][2];
        dir.z = mtx[2][2];
        PSVECNormalize(&dir, &dir);
        PSMTXRotRad(rotMtx, 'X', -1.2217305f);
        PSMTXMultVec(rotMtx, &dir, &ofs);
        PSVECScale(&ofs, &ofs, 220.0f);
        Hu3DMtxTransGet(headMtx, &pos);
        PSVECAdd(&pos, &ofs, &pos);
        fn_1_2CE8C(&work->unk286C[2], 7, 0, &pos, 250.0f, boss);
        fn_1_2CE44(&work->unk286C[2]);
        if (boss->unk140) {
            maxTime = Hu3DMotionMaxTimeGet(boss->unk13A);
            if (Hu3DMotionTimeGet(boss->unk13A) >= maxTime) {
                Hu3DModelAttrSet(boss->unk13A, HU3D_ATTR_DISPOFF);
                boss->unk140 = 0;
            }
        }
        boss->unk110 = 0;
        boss->unk114 = 0;
        boss->unk118 = 0;
    }
}

void fn_1_11634(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    HuVecF dir;

    boss->unk052 = 1;
    boss->unk054 = 1;
    PSVECSubtract(&player->unk0A0, &boss->unk058, &dir);
    dir.y = 0.0f;
    if (dir.x || dir.y) {
        PSVECNormalize(&dir, &dir);
    }
    boss->unk07C = (HuAtan(dir.x, dir.z) > 180.0) ? (HuAtan(dir.x, dir.z) - 360.0)
                                                  : ((HuAtan(dir.x, dir.z) <= -180.0) ? (360.0 + HuAtan(dir.x, dir.z)) : HuAtan(dir.x, dir.z));
}

s32 fn_1_1183C(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    M562_SUNBOMB *sunbomb = &boss->unk14C;
    HuVecF target;
    HuVecF dir;
    s32 result;
    M562_SUNBOMBOBJ *obj;
    float rnd;

    PSVECSubtract(&player->unk0A0, &boss->unk058, &dir);
    dir.y = 0.0f;
    if (dir.x || dir.y) {
        PSVECNormalize(&dir, &dir);
    }
    boss->unk07C = (HuAtan(dir.x, dir.z) > 180.0) ? (HuAtan(dir.x, dir.z) - 360.0)
                                                  : ((HuAtan(dir.x, dir.z) <= -180.0) ? (360.0 + HuAtan(dir.x, dir.z)) : HuAtan(dir.x, dir.z));
    result = 0;
    switch (boss->unk006) {
        case 0:
            lbl_1_bss_782C = frand() % 3 + 2;
            if (lbl_1_bss_782C + sunbomb->unk25C > 4) {
                lbl_1_bss_782C -= (lbl_1_bss_782C + sunbomb->unk25C) - 4;
            }
            lbl_1_bss_782C = KB_CLAMP(lbl_1_bss_782C, 0, 4);
            if (lbl_1_bss_782C == 0) {
                result = 1;
                break;
            }
            lbl_1_bss_782E = 0;
            boss->unk00A = 0;
            boss->unk006++;
        case 1:
            boss->unk052 = 2;
            boss->unk054 = 0;
            boss->unk00A++;
            if (boss->unk00A == 40) {
                obj = fn_1_1F298(sunbomb, &player->unk0A0);
                if (obj == 0) {
                    return 1;
                }
                obj->unk44 = (HuVecF) { 0.0f, 50.0f, 150.0f };
                lbl_1_bss_7828 = obj;
                if (boss->unk3F4 < 0) {
                    boss->unk3F4 = fn_1_814(0x8A9);
                }
            } else if (boss->unk00A >= 90) {
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 2:
            if (player->unk0A0.x <= -341.66666f) {
                boss->unk052 = 4;
                boss->unk054 = 0;
            } else if (player->unk0A0.x >= 341.66666f) {
                boss->unk052 = 5;
                boss->unk054 = 0;
            } else {
                boss->unk052 = 3;
                boss->unk054 = 0;
            }
            boss->unk00A = 0;
            boss->unk006++;
            break;
        case 3:
            if (boss->unk00A == 20) {
                fn_1_814(0x8AA);
            }
            if (++boss->unk00A > 30) {
                obj = lbl_1_bss_7828;
                obj->unk18 = 1;
                rnd = (frand() % 10000) / 10000.0f;
                target = player->unk0A0;
                if (work->unk0020 == 0) {
                    if (frand() % 10000 < 6000) {
                        target.x += 40.0 * (player->unk0C0 * HuSin(player->unk090));
                        target.z += 40.0 * (player->unk0C0 * HuCos(player->unk090));
                    } else {
                        target.x += (rnd - 0.5f) * (100.0 * HuSin(player->unk090));
                        target.z += (rnd - 0.5f) * (100.0 * HuCos(player->unk090));
                    }
                } else {
                    target.x += (rnd - 0.5f) * (500.0 * HuSin(player->unk090));
                    target.z += (rnd - 0.5f) * (500.0 * HuCos(player->unk090));
                }
                target.x = KB_CLAMP(target.x, -1025.0f, 1025.0f);
                target.z = KB_CLAMP(target.z, -300.0f, 500.0f);
                obj->unk5C = target;
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 4:
            obj = lbl_1_bss_7828;
            obj->unk44.x *= 0.9f;
            obj->unk44.z *= 0.9f;
            boss->unk00A++;
            if (lbl_1_bss_782E >= lbl_1_bss_782C - 1) {
                if (boss->unk3F4 >= 0) {
                    fn_1_83C(boss->unk3F4);
                    boss->unk3F4 = -1;
                }
                if (++boss->unk00A >= 40) {
                    boss->unk052 = 1;
                    boss->unk054 = 1;
                    boss->unk00A = 0;
                    boss->unk006 = 0;
                    result = 1;
                }
            } else if (boss->unk00A == 40) {
                obj = fn_1_1F298(sunbomb, &player->unk0A0);
                if (obj == 0) {
                    return 1;
                }
                obj->unk44 = (HuVecF) { 0.0f, 50.0f, 150.0f };
                lbl_1_bss_7828 = obj;
            } else if (boss->unk00A >= 60) {
                lbl_1_bss_782E++;
                boss->unk050 = 2;
                boss->unk00A = 0;
                boss->unk006 = 2;
            }
            break;
    }
    return result;
}

s32 fn_1_12280(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    M562_PLAYER *player = &work->player;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    Mtx mtx;
    HuVecF pos;
    HuVecF ofs;
    M562_MECHAENTRY *mechaObj;
    s32 result;
    float t;
    float scale;

    Hu3DModelObjMtxGet(boss->unk020, "g000mSP-itemhook_M", mtx);
    Hu3DMtxTransGet(mtx, &pos);
    result = 0;
    switch (boss->unk006) {
        case 0:
            boss->unk052 = 6;
            boss->unk054 = 0;
            Hu3DModelScaleSet(boss->unk136, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(boss->unk136, HU3D_ATTR_DISPOFF);
            lbl_1_bss_7834 = 0;
            lbl_1_bss_7830 = NULL;
            lbl_1_bss_7838 = boss->unk07C;
            boss->unk00A = 0;
            boss->unk006++;
        case 1:
            if (boss->unk3F4 < 0) {
                boss->unk3F4 = fn_1_814(0x8AC);
            }
            ofs.x = 50.0 * HuSin(boss->unk078);
            ofs.y = 0.0f;
            ofs.z = 50.0 * HuCos(boss->unk078);
            PSVECAdd(&pos, &ofs, &pos);
            t = boss->unk00A / 90.0f;
            Hu3DModelPosSet(boss->unk136, pos.x + 3.0 * HuSin(24.0f * (360.0f * t)), pos.y + 3.0 * HuCos(24.0f * (360.0f * t)), pos.z);
            scale = 8.0f * t;
            scale += 0.5 * HuSin(18.0f * (360.0f * t));
            Hu3DModelScaleSet(boss->unk136, scale, scale, scale);
            if (++boss->unk00A >= 90) {
                lbl_1_bss_783C = frand();
                boss->unk052 = 7;
                boss->unk054 = 0;
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 2:
            if (boss->unk3F4 >= 0) {
                fn_1_83C(boss->unk3F4);
                boss->unk3F4 = -1;
            }
            if (boss->unk00A % 8 == 0) {
                omVibrate(player->unk014, 5, 12, 0);
            }
            t = (boss->unk00A % 90) / 90.0f;
            if (lbl_1_bss_783C & 1) {
                boss->unk07C = lbl_1_bss_7838 + 45.0 * HuSin(360.0f * t);
            } else {
                boss->unk07C = lbl_1_bss_7838 + 45.0 * HuSin(360.0f * (1.0f - t));
            }
            if (boss->unk00A % 2 == 0) {
                mechaObj = fn_1_181FC(mecha, &pos, boss->unk078);
                if (lbl_1_bss_7834 == 0 && mechaObj != 0) {
                    lbl_1_bss_7830 = mechaObj;
                    lbl_1_bss_7834 = 1;
                }
            }
            if (++boss->unk00A >= 180) {
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 3:
            boss->unk052 = 1;
            boss->unk054 = 1;
            boss->unk00A = 0;
            boss->unk006 = 0;
            result = 1;
            break;
    }
    if (lbl_1_bss_7830 != 0) {
        if (boss->unk006 > 1) {
            t = boss->unk00A / 32.0f;
            t = KB_CLAMP(t, 0.0f, 1.0f);
            scale = 8.0f + 16.0f * t;
            Hu3DModelScaleSet(boss->unk136, scale, scale, scale);
            Hu3DModelPosSet(boss->unk136, lbl_1_bss_7830->unk20.x, lbl_1_bss_7830->unk20.y, lbl_1_bss_7830->unk20.z);
        }
        if (boss->unk00A >= 32) {
            Hu3DModelScaleSet(boss->unk136, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(boss->unk136, HU3D_ATTR_DISPOFF);
            lbl_1_bss_7830 = NULL;
        }
    }
    return result;
}

s32 fn_1_12A38(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    M562_SUNBOMB *sunbomb = &boss->unk14C;
    HuVecF ofs = (HuVecF) { 0.0f, 50.0f, 100.0f };
    s32 result;

    result = 0;
    switch (boss->unk006) {
        case 0:
            boss->unk07C = 0.0f;
            boss->unk052 = 1;
            boss->unk054 = 1;
            boss->unk00A = 0;
            boss->unk006++;
        case 1:
            if (boss->unk124 == 1) {
                boss->unk052 = 8;
                boss->unk054 = 0;
                boss->unk12C = 1;
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 2:
            if (boss->unk124 >= 3) {
                boss->unk00A = 0;
                boss->unk006++;
            }
            break;
        case 3:
            if (++boss->unk00A >= 120) {
                boss->unk00A = 0;
                boss->unk006 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 0x94C */ HuVecF lbl_1_data_94C = { 0.0f, 0.0f, 0.0f };

void fn_1_12BA8(M562_KOOPABOSS *boss)
{
    M562_WORK *work = boss->unk000;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    M562_SUNBOMB *sunbomb = &boss->unk14C;
    HuVecF pos;
    HuVecF dir;
    HuVecF ofs = (HuVecF) { 0.0f, 50.0f, 100.0f };
    MtxPtr hookMtx;
    s32 i;
    M562_SUNBOMBOBJ *obj;
    float dist;
    float t;
    float scale;
    float s;
    float radius;

    switch (boss->unk124) {
        case 0:
            boss->unk128 = 0.0f;
            Hu3DModelScaleSet(boss->unk11C, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(boss->unk11C, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(boss->unk130, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(boss->unk130, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(boss->unk11C, 0.5f);
            boss->unk126 = 0;
            boss->unk124 = 1;
            break;
        case 1:
            if (boss->unk12C != 0) {
                Hu3DModelAttrReset(boss->unk11C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(boss->unk130, HU3D_ATTR_DISPOFF);
                boss->unk126 = 0;
                boss->unk124 = 2;
                boss->unk12C = 0;
            }
            break;
        case 2:
            t = (boss->unk126 - 40) / 60.0f;
            t = KB_CLAMP(t, 0.0f, 1.0f);
            scale = 2.0f * t;
            boss->unk128 = scale;
            Hu3DModelScaleSet(boss->unk11C, scale, scale, scale);
            scale *= 1.5f;
            Hu3DModelScaleSet(boss->unk130, scale, scale, scale);
            hookMtx = fn_1_10160(boss);
            Hu3DMtxTransGet(hookMtx, &pos);
            PSVECAdd(&pos, &ofs, &pos);
            Hu3DModelPosSet(boss->unk11C, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(boss->unk130, pos.x, 0.0f, pos.z);
            boss->unk126++;
            if (boss->unk126 == 40) {
                Hu3DModelScaleSet(boss->unk11C, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrReset(boss->unk11C, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(boss->unk11C, 0.5f);
                if (boss->unk3F4 < 0) {
                    boss->unk3F4 = fn_1_814(0x8AF);
                }
            } else if (boss->unk126 >= 100) {
                lbl_1_data_94C = pos;
                boss->unk126 = 0;
                boss->unk124 = 3;
                if (boss->unk3F4 >= 0) {
                    fn_1_83C(boss->unk3F4);
                    boss->unk3F4 = -1;
                }
                fn_1_814(0x8AA);
            }
            break;
        case 3:
            t = boss->unk126 / 40.0f;
            if (t < 0.4f) {
                s = t / 0.4f;
                s = HuSin(90.0f * s);
                pos.y = lbl_1_data_94C.y + 250.0f * s;
            } else {
                s = (t - 0.4f) / 0.6f;
                s = HuSin(90.0f + 90.0f * s);
                pos.y = lbl_1_data_8D8.y + s * (250.0f + (lbl_1_data_94C.y - lbl_1_data_8D8.y));
            }
            pos.x = lbl_1_data_94C.x + t * (lbl_1_data_8D8.x - lbl_1_data_94C.x);
            pos.z = lbl_1_data_94C.z + t * (lbl_1_data_8D8.z - lbl_1_data_94C.z);
            Hu3DModelPosSet(boss->unk11C, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(boss->unk130, pos.x, 0.0f, pos.z);
            fn_1_2CE8C(&work->unk286C[2], 6, 0, &pos, 120.0f, NULL);
            boss->unk126++;
            if (boss->unk126 >= 40) {
                fn_1_934(0x8B0, &pos);
                if (boss->unk3F4 >= 0) {
                    fn_1_83C(boss->unk3F4);
                    boss->unk3F4 = -1;
                }
                boss->unk3F4 = fn_1_934(0x8B1, &pos);
                if (work->unk000C > 4) {
                    boss->unk126 = 0;
                    boss->unk124 = 5;
                } else {
                    Hu3DModelScaleSet(boss->unk120, 1.0f, 1.0f, 1.0f);
                    Hu3DModelPosSet(boss->unk120, lbl_1_data_8D8.x, 55.0f + lbl_1_data_8D8.y, lbl_1_data_8D8.z);
                    Hu3DMotionSpeedSet(boss->unk120, 4.1666665f);
                    Hu3DMotionTimeSet(boss->unk120, 0.0f);
                    Hu3DModelAttrReset(boss->unk120, HU3D_ATTR_DISPOFF);
                    fn_1_21B68(camera, 1, 50, 40.0f, 0.9f, 90.0f);
                    omVibrate(player->unk014, 10, 12, 0);
                    boss->unk126 = 0;
                    boss->unk124 = 4;
                }
            }
            break;
        case 4:
            if (boss->unk126 > 10 && boss->unk126 % 4 == 0) {
                fn_1_21B68(camera, 1, 50, 10.0f, 0.7f, 90.0f);
            }
            if (boss->unk126 % 8 == 0) {
                omVibrate(player->unk014, 5, 12, 0);
            }
            if (boss->unk126 < 10) {
                t = boss->unk126 / 10.0f;
                t = 1.0f - KB_CLAMP(t, 0.0f, 1.0f);
                t = 0.3f + 0.7f * t;
                scale = t;
                Hu3DModelScaleSet(boss->unk11C, scale, scale, scale);
                scale *= 1.5f;
                Hu3DModelScaleSet(boss->unk130, scale, scale, scale);
            } else if (boss->unk126 == 10) {
                Hu3DModelScaleSet(boss->unk11C, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(boss->unk11C, HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(boss->unk130, 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(boss->unk11C, HU3D_ATTR_DISPOFF);
                boss->unk128 = 0.0f;
            }
            t = boss->unk126 / 60.0f;
            t = KB_CLAMP(t, 0.0f, 1.0f);
            radius = 1400.0f * t;
            sunbomb->unk294 = 1;
            sunbomb->unk298 = lbl_1_data_8D8;
            sunbomb->unk2A4 = radius;
            if (boss->unk3F4 >= 0) {
                PSVECSubtract(&camera->unk34, &lbl_1_data_94C, &dir);
                PSVECNormalize(&dir, &dir);
                PSVECScale(&dir, &dir, radius);
                PSVECAdd(&dir, &lbl_1_data_94C, &dir);
                fn_1_964(boss->unk3F4, &dir);
            }
            if (work->unk000C == 4 && fn_1_13C1C(player, &lbl_1_data_8D8, radius)) {
                if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0 && work->unk000C == 4) {
                    player->unk00A = 0;
                    player->unk006 = 0;
                    player->unk008 = 0;
                    player->unk004 = 5;
                }
            }
            boss->unk148 = HuSin(180.0f * t);
            boss->unk126++;
            if (boss->unk126 >= 60) {
                boss->unk148 = 0.0f;
                if (boss->unk3F4 >= 0) {
                    fn_1_83C(boss->unk3F4);
                    boss->unk3F4 = -1;
                }
                for (i = 0; i < 5; i++) {
                    obj = &sunbomb->unk004[i];
                    PSVECSubtract(&obj->unk38, &lbl_1_data_8D8, &dir);
                    dir.y = 0.0f;
                    dist = PSVECMag(&dir);
                    if (obj->unk20 != 0 && obj->unk10 != 0 && obj != player->unk134) {
                        obj->unk04 = 10;
                        obj->unk20 = 0;
                    }
                }
                boss->unk126 = 0;
                boss->unk124 = 6;
            }
            break;
        case 5:
            t = boss->unk126 / 10.0f;
            t = 1.0f - KB_CLAMP(t, 0.0f, 1.0f);
            scale = boss->unk128 * t;
            Hu3DModelScaleSet(boss->unk11C, scale, scale, scale);
            scale *= 1.5f;
            Hu3DModelScaleSet(boss->unk130, scale, scale, scale);
            if (++boss->unk126 >= 10) {
                boss->unk126 = 0;
                boss->unk124 = 6;
            }
            break;
        case 6:
            Hu3DModelScaleSet(boss->unk120, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(boss->unk120, HU3D_ATTR_DISPOFF);
            Hu3DModelScaleSet(boss->unk11C, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(boss->unk11C, HU3D_ATTR_DISPOFF);
            boss->unk128 = 0.0f;
            boss->unk126 = 0;
            boss->unk124 = 1;
            break;
    }
}

/* 0x974 */ HuVecF lbl_1_data_974 = { 0.0f, 1200.0f, 0.0f };
/* 0x980 */ HuVecF lbl_1_data_980 = { 0.0f, -1.0f, 0.01f };
/* 0x98C */ GXColor lbl_1_data_98C = { 0, 0, 0, 0 };
/* 0x990 */ GXColor lbl_1_data_990 = { 128, 176, 255, 255 };

void fn_1_13A24(M562_KOOPABOSS *boss)
{
    GXColor color;
    float s;

    if (boss->unk148 > 0.0f) {
        color = lbl_1_data_990;
        if (boss->unk144 < 0) {
            boss->unk144 = Hu3DGLightCreateV(&lbl_1_data_974, &lbl_1_data_980, &lbl_1_data_98C);
            Hu3DGLightStaticSet(boss->unk144, 1);
            Hu3DGLightSpotSet(boss->unk144, GX_SP_COS, 30.0f);
            Hu3DGLightInfinitytSet(boss->unk144);
        }
        if (boss->unk144 >= 0) {
            s = boss->unk148;
            color.r = lbl_1_data_990.r * s;
            color.g = lbl_1_data_990.g * s;
            color.b = lbl_1_data_990.b * s;
            color.a = 255;
            Hu3DGLightColorSet(boss->unk144, color.r, color.g, color.b, color.a);
        }
    } else if (boss->unk144 >= 0) {
        Hu3DGLightColorSet(boss->unk144, 0, 0, 0, 0);
        Hu3DGLightKill(boss->unk144);
        boss->unk144 = -1;
    }
}

s32 fn_1_13C1C(M562_PLAYER *player, HuVecF *pos, float radius)
{
    s32 result;
    HuVecF dir;
    float dist;

    result = 0;
    PSVECSubtract(&player->unk0A0, pos, &dir);
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (dist >= radius - 70.0f && dist <= 70.0f + radius && player->unk0A0.y < 40.0f) {
        result = 1;
    }
    return result;
}
