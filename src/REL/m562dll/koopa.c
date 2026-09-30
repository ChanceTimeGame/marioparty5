/*
 * m562dll koopa.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/koopa.s.
 */

#include "REL/m562dll.h"

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
#include "game/audio.h" /* CharFXPlay: retail calls it unprototyped (fn_1_F014 passes an int, no extsh) */
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_340 = 0.0f; /* 0x340 */
static const float lbl_1_rodata_344 = 1.5f; /* 0x344 */
static const float lbl_1_rodata_348 = 1.0f; /* 0x348 */
static const float lbl_1_rodata_34C = 4.0f; /* 0x34C */
static const float lbl_1_rodata_350 = 30.0f; /* 0x350 */
static const float lbl_1_rodata_354 = 8.0f; /* 0x354 */
static const float lbl_1_rodata_358 = 15.0f; /* 0x358 */
static const float lbl_1_rodata_35C = 40.0f; /* 0x35C */
/* 0x360 lbl_1_rodata_360 (0xC): 0xC2A00000 0x00000000 0x42480000 -- an aggregate initialiser, write it as a local */
/* 0x36C lbl_1_rodata_36C (0xC): 0x42A00000 0x00000000 0x42480000 -- an aggregate initialiser, write it as a local */
/* 0x378 lbl_1_rodata_378 (0xC): 0xC2A00000 0x00000000 0x41F00000 -- an aggregate initialiser, write it as a local */
/* 0x384 lbl_1_rodata_384 (0xC): 0x42A00000 0x00000000 0x41F00000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_390 = 6.0f; /* 0x390 */
static const float lbl_1_rodata_394 = 5.5f; /* 0x394 */
static const float lbl_1_rodata_398 = 5.0f; /* 0x398 */
static const float lbl_1_rodata_39C = 4.5f; /* 0x39C */
static const float lbl_1_rodata_3A0 = 20.0f; /* 0x3A0 */
static const float lbl_1_rodata_3A4 = 0.6f; /* 0x3A4 */
static const float lbl_1_rodata_3A8 = 0.4f; /* 0x3A8 */
static const float lbl_1_rodata_3AC = -150.0f; /* 0x3AC */
static const float lbl_1_rodata_3B0 = -5000.0f; /* 0x3B0 */
static const float lbl_1_rodata_3B4 = 175.0f; /* 0x3B4 */
static const float lbl_1_rodata_3B8 = 525.0f; /* 0x3B8 */
static const float lbl_1_rodata_3BC = -525.0f; /* 0x3BC */
static const float lbl_1_rodata_3C0 = 400.0f; /* 0x3C0 */
static const float lbl_1_rodata_3C4 = -400.0f; /* 0x3C4 */
static const float lbl_1_rodata_3C8 = 10.0f; /* 0x3C8 */
static const float lbl_1_rodata_3CC = 0.75f; /* 0x3CC */
static const float lbl_1_rodata_3D0 = 90.0f; /* 0x3D0 */
static const float lbl_1_rodata_3D4 = 0.017453292f; /* 0x3D4 */
static const float lbl_1_rodata_3D8 = 60.0f; /* 0x3D8 */
static const float lbl_1_rodata_3DC = 16.0f; /* 0x3DC */
static const float lbl_1_rodata_3E0 = 200.0f; /* 0x3E0 */
static const float lbl_1_rodata_3E4 = 0.5f; /* 0x3E4 */
/* 0x3E8 lbl_1_rodata_3E8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_3F0 = 0.25f; /* 0x3F0 */
static const double lbl_1_rodata_3F8 = 1.0; /* 0x3F8 */
static const double lbl_1_rodata_400 = 180.0; /* 0x400 */
static const double lbl_1_rodata_408 = 3.141592653589793; /* 0x408 */
static const double lbl_1_rodata_410 = 360.0; /* 0x410 */
static const double lbl_1_rodata_418 = -180.0; /* 0x418 */
static const float lbl_1_rodata_420 = 0.98f; /* 0x420 */
static const float lbl_1_rodata_424 = 0.3f; /* 0x424 */
static const float lbl_1_rodata_428 = 0.7f; /* 0x428 */
static const float lbl_1_rodata_42C = 65.0f; /* 0x42C */
static const double lbl_1_rodata_430 = 0.05235987755982988; /* 0x430 */
static const float lbl_1_rodata_438 = 1.6f; /* 0x438 */
static const float lbl_1_rodata_43C = 0.9f; /* 0x43C */
static const float lbl_1_rodata_440 = 0.95f; /* 0x440 */
static const float lbl_1_rodata_444 = 0.99f; /* 0x444 */
static const float lbl_1_rodata_448 = 125.0f; /* 0x448 */
static const float lbl_1_rodata_44C = -500.0f; /* 0x44C */
static const float lbl_1_rodata_450 = 250.0f; /* 0x450 */
static const float lbl_1_rodata_454 = -375.0f; /* 0x454 */
static const double lbl_1_rodata_458 = 0.08726646259971647; /* 0x458 */
static const float lbl_1_rodata_460 = 180.0f; /* 0x460 */
static const float lbl_1_rodata_464 = 500.0f; /* 0x464 */
static const float lbl_1_rodata_468 = 8.5f; /* 0x468 */
static const float lbl_1_rodata_46C = 300.0f; /* 0x46C */
static const float lbl_1_rodata_470 = 230.0f; /* 0x470 */
static const float lbl_1_rodata_474 = 0.1f; /* 0x474 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7822 */ s16 lbl_1_bss_7822[3];
/* 0x7820 */ s16 lbl_1_bss_7820;


#define KOOPA_ABS(x) (((x) >= 0.0f) ? (x) : -(x))
#define KOOPA_ANGLE(x, z) ((HuAtan((x), (z)) > 180.0) ? (HuAtan((x), (z)) - 360.0) \
    : ((HuAtan((x), (z)) <= -180.0) ? (360.0 + HuAtan((x), (z))) : HuAtan((x), (z))))

/* --- functions (reference order), .data placed before its first user --- */
/* 0x7F8 */ u32 lbl_1_data_7F8[14] = { DATANUM(DATA_m562, 45), DATANUM(DATA_m562, 46), DATANUM(DATA_m562, 47), DATANUM(DATA_m562, 48), DATANUM(DATA_m562, 49), DATANUM(DATA_m562, 50), DATANUM(DATA_m562, 51), DATANUM(DATA_m562, 52), DATANUM(DATA_m562, 53), DATANUM(DATA_m562, 54), DATANUM(DATA_m562, 55), DATANUM(DATA_m562, 56), DATANUM(DATA_m562, 57), DATANUM(DATA_m562, 58) };
/* 0x830 */ HuVecF lbl_1_data_830 = { 0.0f, 2000.0f, -1100.0f };

void fn_1_B2E0(M562_KOOPA *koopa, M562_WORK *work)
{
    s32 i;
    M562_WORK *workP = work;
    s16 model;

    memset(koopa, 0, 0xB8);
    koopa->work = work;
    koopa->motTime = 0.0f;
    model = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m562, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
    koopa->model = model;
    Hu3DModelScaleSet(model, 1.5f, 1.5f, 1.5f);
    Hu3DModelCameraSet(model, workP->camera[0].unk04 | workP->camera[1].unk04);
    Hu3DModelLayerSet(model, 4);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(model);
    Hu3DMotionSpeedSet(model, 1.0f);
    koopa->pos = lbl_1_data_830;
    Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    for (i = 0; i < 14; i++) {
        koopa->motion[i] = Hu3DJointMotion(model, HuDataSelHeapReadNum(lbl_1_data_7F8[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DMotionSet(model, koopa->motion[0]);
    Hu3DModelAttrSet(model, HU3D_MOTATTR_LOOP);
    Hu3DMotionShiftSet(model, koopa->motion[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
    koopa->motCur = koopa->motNext = 0;
    koopa->motLoop = 1;
    fn_1_2CD6C(&workP->unk286C[1], 36);
    fn_1_2CE3C(&workP->unk286C[1], fn_1_EEC4);
}

void fn_1_B4F8(M562_KOOPA *koopa)
{
    M562_WORK *work = koopa->work;
    s32 i;

    fn_1_2CDE8(&work->unk286C[1]);
    for (i = 0; i < 14; i++) {
        Hu3DMotionKill(koopa->motion[i]);
    }
    Hu3DModelKill(koopa->model);
    memset(koopa, 0, 0xB8);
}

void fn_1_B578(M562_KOOPA *koopa)
{
    float speed;
    M562_WORK *work = koopa->work;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    s16 model;

    if (koopa->dispReq != 0 && koopa->dispOn == 0) {
        Hu3DModelAttrReset(koopa->model, HU3D_ATTR_DISPOFF);
        koopa->dispOn = 1;
    }
    else if (koopa->dispReq == 0 && koopa->dispOn != 0) {
        Hu3DModelAttrSet(koopa->model, HU3D_ATTR_DISPOFF);
        koopa->dispOn = 0;
    }
    if (koopa->dispOn != 0) {
        switch (koopa->mode) {
            case 0:
                break;
            case 1:
                fn_1_B7F0(koopa);
                break;
            case 2:
                fn_1_BAE8(koopa);
                break;
            case 3:
                fn_1_BDA4(koopa);
                break;
        }
        model = koopa->model;
        if ((s16)koopa->motCur != koopa->motNext && (s16)Hu3DMotionShiftIDGet(model) < 0 && koopa->motShiftTime <= 0) {
            speed = (koopa->motCur == 10) ? 30.0f : ((koopa->motNext == 9) ? 8.0f : ((koopa->motCur == 9) ? 15.0f : 4.0f));
            koopa->motCur = koopa->motNext;
            Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(model, koopa->motion[koopa->motCur], 0.0f, speed, (koopa->motLoop != 0) ? HU3D_MOTATTR_LOOP : 0);
            koopa->motShiftTime = koopa->motShiftNext;
            koopa->motShiftNext = 0;
            koopa->motTime = Hu3DMotionTimeGet(koopa->model);
        }
        if (koopa->motShiftTime != 0) {
            koopa->motShiftTime--;
        }
    }
}

void fn_1_B7F0(M562_KOOPA *koopa)
{
    float maxTime;
    s16 model;
    M562_WORK *work = koopa->work;
    M562_PLAYER *player = &work->player;
    M562_FIRE *fire = &work->fire;

    if (koopa->unk1C == 0) {
        model = koopa->model;
        koopa->pos = lbl_1_data_830;
        Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
    switch (koopa->step) {
        case 0:
            model = koopa->model;
            Hu3DModelCameraSet(model, work->camera[0].unk04 | work->camera[1].unk04);
            Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowReset(model);
            Hu3DMotionSpeedSet(model, 1.0f);
            koopa->pos = lbl_1_data_830;
            Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
            koopa->step = 1;
            koopa->unk0A = 0;
        case 1:
            koopa->motNext = 0;
            koopa->motLoop = 1;
            if (player->unk004 == 4) {
                koopa->motNext = 2;
                koopa->motLoop = 0;
                koopa->step = 2;
                koopa->unk0A = 160;
            }
            else if (fire->unk1100 < lbl_1_bss_7822[0]) {
                koopa->motNext = 9;
                koopa->motLoop = 0;
                koopa->step = 2;
                koopa->unk0A = 20;
            }
            else if (work->unk000C > 4 && work->unk0022 == 0) {
                fn_1_814(0x8C5);
                koopa->motNext = 10;
                koopa->motLoop = 0;
                koopa->step = 3;
                koopa->unk0A = 0;
            }
            break;
        case 2:
            if (koopa->motCur == 2 && koopa->unk0A == 110) {
                fn_1_814(0x8B3);
            }
            if (--koopa->unk0A <= 0) {
                koopa->step = 1;
                koopa->unk0A = 0;
            }
            break;
        case 3:
            maxTime = Hu3DMotionMaxTimeGet(koopa->model);
            if (Hu3DMotionTimeGet(koopa->model) >= maxTime) {
                Hu3DMotionTimeSet(koopa->model, 40.0f);
            }
            break;
        case 10:
            break;
    }
    lbl_1_bss_7822[0] = fire->unk1100;
}

void fn_1_BAE8(M562_KOOPA *koopa)
{
    float maxTime;
    s16 model;
    M562_WORK *work = koopa->work;
    M562_PLAYER *player = &work->player;
    M562_FIRE *fire = &work->fire;

    if (koopa->unk1C == 0) {
        model = koopa->model;
        koopa->pos = lbl_1_data_830;
        Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
        Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    }
    switch (koopa->step) {
        case 0:
            model = koopa->model;
            Hu3DModelCameraSet(model, work->camera[0].unk04 | work->camera[1].unk04);
            Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowReset(model);
            Hu3DMotionSpeedSet(model, 1.0f);
            koopa->pos = lbl_1_data_830;
            Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
            koopa->step = 1;
            koopa->unk0A = 0;
        case 1:
            koopa->motNext = 0;
            koopa->motLoop = 1;
            if (player->unk004 == 4) {
                koopa->motNext = 2;
                koopa->motLoop = 0;
                koopa->step = 2;
                koopa->unk0A = 160;
            }
            else if (work->unk000C > 4 && work->unk0022 == 0) {
                fn_1_814(0x8C5);
                koopa->motNext = 10;
                koopa->motLoop = 0;
                koopa->step = 3;
                koopa->unk0A = 0;
            }
            break;
        case 2:
            if (koopa->motCur == 2 && koopa->unk0A == 110) {
                fn_1_814(0x8B3);
            }
            if (--koopa->unk0A <= 0) {
                koopa->step = 1;
                koopa->unk0A = 0;
            }
            break;
        case 3:
            maxTime = Hu3DMotionMaxTimeGet(koopa->model);
            if (Hu3DMotionTimeGet(koopa->model) >= maxTime) {
                Hu3DMotionTimeSet(koopa->model, 40.0f);
            }
            break;
        case 10:
            break;
    }
}

/* 0x83C */ HuVecF lbl_1_data_83C = { 0.0f, 0.0f, -125.0f };

void fn_1_BDA4(M562_KOOPA *koopa)
{
    float scale;
    float time;
    float minX;
    float maxX;
    float minZ;
    float maxZ;
    float pushX;
    float pushZ;
    float radius;
    M562_WORK *work = koopa->work;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    s16 model;
    s32 rand;
    HuVecF pos;
    Mtx rotMtx;
    Mtx rotMtx2;

    if (koopa->unk1C == 0) {
        if (koopa->step >= 2 && koopa->step < 7) {
            koopa->step = 2;
            koopa->unk10 = 1;
        }
    }
    else if (koopa->step == 1) {
        koopa->timer = 180;
        koopa->step = 3;
    }
    switch (koopa->step) {
        case 0:
            model = koopa->model;
            Hu3DModelCameraSet(model, work->camera[0].unk04);
            Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
            Hu3DModelShadowSet(model);
            Hu3DMotionSet(model, koopa->motion[0]);
            Hu3DMotionSpeedSet(model, 1.0f);
            koopa->pos = lbl_1_data_83C;
            Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
            koopa->motNext = koopa->motCur = 0;
            koopa->motLoop = 1;
            if (work->unk0020 == 0) {
                koopa->speed = 6.0f;
            }
            else if (work->unk0020 == 1) {
                koopa->speed = 5.5f;
            }
            else if (work->unk0020 == 2) {
                koopa->speed = 5.0f;
            }
            else {
                koopa->speed = 4.5f;
            }
            koopa->speedInit = koopa->speed;
            koopa->timer = 180;
            koopa->step = 3;
            break;
        case 1:
            break;
        case 2:
            fn_1_CE10(koopa);
            if (koopa->tile && koopa->tile->unk04 > 2) {
                koopa->velY = 0.0f;
                koopa->timer = 0;
                koopa->step = 7;
            }
            if (--koopa->unk10 <= 0) {
                koopa->step = 3;
            }
            break;
        case 3:
            fn_1_CE24(koopa);
            if (--koopa->timer <= 0) {
                rand = frand() % 10000;
                if (rand < 2000) {
                    koopa->timer = 0;
                    koopa->step = 4;
                    koopa->subStep = 0;
                    koopa->unk0E = 0;
                }
                else if (rand < 4000) {
                    koopa->timer = 0;
                    koopa->step = 5;
                    koopa->subStep = 0;
                    koopa->unk0E = 0;
                }
                else {
                    koopa->timer = 0;
                    koopa->step = 6;
                    koopa->subStep = 0;
                    koopa->unk0E = 0;
                }
            }
            break;
        case 4: 
            if (fn_1_D404(koopa) != 0) {
                koopa->timer = 180;
                koopa->unk10 = 60;
                koopa->step = 2;
            }
            break;
        case 5: 
            if (fn_1_DCC4(koopa) != 0) {
                koopa->timer = 180;
                koopa->unk10 = 60;
                koopa->step = 2;
            }
            break;
        case 6:
            if (fn_1_E558(koopa) != 0) {
                koopa->timer = 180;
                koopa->unk10 = 60;
                koopa->step = 2;
                if (koopa->tile && koopa->tile->unk04 > 2) {
                    koopa->velY = 0.0f;
                    koopa->timer = 0;
                    koopa->step = 7;
                }
            }
            break;
        case 7:
            koopa->motNext = 3;
            koopa->motLoop = 0;
            if (koopa->timer == 20) {
                fn_1_814(0x2CB);
            }
            if (koopa->timer >= 20) {
                koopa->velY -= 1.5f;
                if (koopa->timer >= 25) {
                    scale = (koopa->timer - 25) / 20.0f;
                    scale = 1.0f - ((scale > 1.0f) ? 1.0f : ((scale < 0.0f) ? 0.0f : scale));
                    scale = 0.6f + 0.4f * scale;
                    Hu3DModelScaleSet(koopa->model, 1.5f * scale, 1.5f * scale, 1.5f * scale);
                }
            }
            koopa->pos.y += koopa->velY;
            Hu3DModelPosSet(koopa->model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            koopa->timer++;
            if (koopa->pos.y < -150.0f) {
                Hu3DModelShadowReset(koopa->model);
            }
            if (koopa->pos.y < -5000.0f) {
                Hu3DModelAttrSet(koopa->model, HU3D_ATTR_DISPOFF);
                koopa->timer = 0;
                koopa->step = 8;
            }
            break;
        case 8:
            break;
    }
    if (koopa->tile) {
        if (koopa->tile->unk04 > 2 && koopa->step != 7 && koopa->step != 0 && koopa->step != 8 && koopa->step != 1) {
            koopa->velY = 0.0f;
            koopa->timer = 0;
            koopa->step = 7;
        }
        if (koopa->tile->unk04 > 2) {
            pos = player->unk0A0;
            minX = koopa->tile->unk10.x - 175.0f;
            maxX = 175.0f + koopa->tile->unk10.x;
            minZ = koopa->tile->unk10.z - 175.0f;
            maxZ = 175.0f + koopa->tile->unk10.z;
            if (pos.x > minX && pos.x < maxX && pos.z > minZ && pos.z < maxZ) {
                if (KOOPA_ABS(minX - pos.x) < KOOPA_ABS(maxX - pos.x)) {
                    pushX = 0.4f * (minX - pos.x);
                }
                else {
                    pushX = 0.4f * (maxX - pos.x);
                }
                if (KOOPA_ABS(minZ - pos.z) < KOOPA_ABS(maxZ - pos.z)) {
                    pushZ = 0.4f * (minZ - pos.z);
                }
                else {
                    pushZ = 0.4f * (maxZ - pos.z);
                }
                if (KOOPA_ABS(pushX) < KOOPA_ABS(pushZ)) {
                    pos.x += pushX;
                }
                else {
                    pos.z += pushZ;
                }
            }
            player->unk0A0 = pos;
        }
    }
    model = koopa->model;
    koopa->pos.x = (koopa->pos.x > 525.0f) ? 525.0f : ((koopa->pos.x < -525.0f) ? -525.0f : koopa->pos.x);
    koopa->pos.z = (koopa->pos.z > 400.0f) ? 400.0f : ((koopa->pos.z < -400.0f) ? -400.0f : koopa->pos.z);
    Hu3DModelPosSet(model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
    Hu3DModelRotSet(model, koopa->rot.x, koopa->rot.y, koopa->rot.z);
    time = Hu3DMotionTimeGet(koopa->model);
    if (koopa->motCur == 12 || koopa->motCur == 13) {
        HuVecF offsetL = { -80.0f, 0.0f, 50.0f };
        HuVecF offsetR = { 80.0f, 0.0f, 50.0f };
        if (koopa->motTime < 10.0f && time >= 10.0f) {
            HuVecF footPos;
            if (lbl_1_bss_7820 == 0) {
                fn_1_814(0x2C7);
                lbl_1_bss_7820 = 15;
            }
            fn_1_21B68(camera, 1, 50, 10.0f, 0.75f, 90.0f);
            MTXRotRad(rotMtx, 'Y', MTXDegToRad(koopa->angle));
            MTXMultVec(rotMtx, &offsetL, &footPos);
            VECAdd(&footPos, &koopa->pos, &footPos);
            fn_1_2DC08(camera->unk04, &footPos, 1);
        }
        else if (koopa->motTime < 60.0f && time >= 60.0f) {
            HuVecF footPos;
            if (lbl_1_bss_7820 == 0) {
                fn_1_814(0x2C7);
                lbl_1_bss_7820 = 15;
            }
            fn_1_21B68(camera, 1, 50, 10.0f, 0.75f, 90.0f);
            MTXRotRad(rotMtx, 'Y', MTXDegToRad(koopa->angle));
            MTXMultVec(rotMtx, &offsetR, &footPos);
            VECAdd(&footPos, &koopa->pos, &footPos);
            fn_1_2DC08(camera->unk04, &footPos, 1);
        }
    }
    else if (koopa->motCur == 8) {
        HuVecF offsetL = { -80.0f, 0.0f, 30.0f };
        HuVecF offsetR = { 80.0f, 0.0f, 30.0f };
        if (koopa->motTime < 1.0f && time >= 1.0f) {
            HuVecF footPos;
            if (lbl_1_bss_7820 == 0) {
                fn_1_814(0x2C8);
                lbl_1_bss_7820 = 10;
            }
            fn_1_21B68(camera, 1, 50, 10.0f, 0.75f, 90.0f);
            MTXRotRad(rotMtx2, 'Y', MTXDegToRad(koopa->angle));
            MTXMultVec(rotMtx2, &offsetL, &footPos);
            VECAdd(&footPos, &koopa->pos, &footPos);
            fn_1_2DC08(camera->unk04, &footPos, 1);
        }
        else if (koopa->motTime < 16.0f && time >= 16.0f) {
            HuVecF footPos;
            if (lbl_1_bss_7820 == 0) {
                fn_1_814(0x2C8);
                lbl_1_bss_7820 = 10;
            }
            fn_1_21B68(camera, 1, 50, 10.0f, 0.75f, 90.0f);
            MTXRotRad(rotMtx2, 'Y', MTXDegToRad(koopa->angle));
            MTXMultVec(rotMtx2, &offsetR, &footPos);
            VECAdd(&footPos, &koopa->pos, &footPos);
            fn_1_2DC08(camera->unk04, &footPos, 1);
        }
    }
    koopa->motTime = time;
    if (lbl_1_bss_7820 != 0) {
        lbl_1_bss_7820--;
    }
    pos = koopa->pos;
    pos.y += 200.0f;
    fn_1_2CE8C(&work->unk286C[1], 3, 0, &pos, 200.0f, koopa);
    radius = 0.5f * player->unk068;
    pos = player->unk0A0;
    pos.y += radius;
    fn_1_2CE8C(&work->unk286C[1], 0, 0, &pos, radius, player);
    fn_1_2CE44(&work->unk286C[1]);
    if (koopa->step != 6 && koopa->step < 7) {
        if (koopa->pos.y > 0.0f) {
            koopa->velY -= 1.5f;
            koopa->pos.y += koopa->velY;
        }
        else {
            koopa->velY = 0.0f;
            koopa->pos.y = 0.0f;
        }
    }
}

void fn_1_CE10(M562_KOOPA *koopa)
{
    koopa->motNext = 0;
    koopa->motLoop = 1;
}

void fn_1_CE24(M562_KOOPA *koopa)
{
    float t;
    float time;
    float speed;
    M562_WORK *work = koopa->work;
    M562_PLAYER *player = &work->player;
    s32 fixedAngle;
    HuVecF dir;
    HuVecF target;

    koopa->motNext = 12;
    koopa->motLoop = 1;
    t = (koopa->speed - 4.5f) / 4.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    Hu3DMotionSpeedSet(koopa->model, 1.0 + t);
    fixedAngle = 0;
    if (fixedAngle == 0) {
        fn_1_ED90(koopa, &player->unk0A0, &target);
        VECSubtract(&target, &koopa->pos, &dir);
        dir.y = 0.0f;
        if (dir.x || dir.z) {
            VECNormalize(&dir, &dir);
        }
        koopa->angleTarget = KOOPA_ANGLE(dir.x, dir.z);
    }
    koopa->angle = fn_1_36EC(koopa->angleTarget, koopa->angle, 0.98f);
    speed = koopa->speed;
    time = Hu3DMotionTimeGet(koopa->model);
    if (KOOPA_ABS(time - 15.0f) < 10.0f) {
        t = KOOPA_ABS(time - 15.0f) / 10.0f;
        t = 0.3f + 0.7f * t;
        speed *= t;
    }
    else if (KOOPA_ABS(time - 65.0f) < 10.0f) {
        t = KOOPA_ABS(time - 65.0f) / 10.0f;
        t = 0.3f + 0.7f * t;
        speed *= t;
    }
    dir.x = speed * HuSin(koopa->angle);
    dir.z = speed * HuCos(koopa->angle);
    koopa->pos.x += dir.x;
    koopa->pos.z += dir.z;
    koopa->rot.y = koopa->angle;
}

/* 0x86C "g000m0-ns_hed" */

s32 fn_1_D404(M562_KOOPA *koopa)
{
    float t;
    float time;
    float speed;
    float angle;
    float maxTime;
    M562_WORK *work = koopa->work;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    M562_PLAYER *player = &work->player;
    s32 result;
    s32 fixedAngle;
    HuVecF dir;
    HuVecF pos;
    Mtx mtx;

    t = (koopa->speed - 4.5f) / 4.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    Hu3DMotionSpeedSet(koopa->model, 1.0 + t);
    result = 0;
    switch (koopa->subStep) {
        case 0:
            koopa->motNext = 6;
            koopa->motLoop = 0;
            koopa->subStep++;
            break;
        case 1:
            if (koopa->motCur == 6) {
                if (Hu3DMotionTimeGet(koopa->model) >= Hu3DMotionMaxTimeGet(koopa->model)) {
                    koopa->motNext = 13;
                    koopa->motLoop = 1;
                    koopa->unk0E = 180;
                    koopa->subStep++;
                }
            }
            break;
        case 2:
            if (koopa->unk0E % 3 == 0) {
                Hu3DModelObjMtxGet(koopa->model, "g000m0-ns_hed", mtx);
                Hu3DMtxTransGet(mtx, &pos);
                dir.x = mtx[0][0];
                dir.y = 0.0f;
                dir.z = mtx[2][0];
                angle = koopa->angle;
                if (dir.x || dir.z) {
                    VECNormalize(&dir, &dir);
                    angle = KOOPA_ANGLE(dir.x, dir.z);
                }
                fn_1_181FC(mecha, &pos, angle);
            }
            if (--koopa->unk0E <= 0) {
                result = 1;
            }
            break;
    }
    fixedAngle = 0;
    if (fixedAngle == 0) {
        fn_1_ED90(koopa, &player->unk0A0, &pos);
        VECSubtract(&pos, &koopa->pos, &dir);
        dir.y = 0.0f;
        if (dir.x || dir.z) {
            VECNormalize(&dir, &dir);
        }
        koopa->angleTarget = KOOPA_ANGLE(dir.x, dir.z);
    }
    if (koopa->subStep > 1) {
        speed = koopa->speed;
        time = Hu3DMotionTimeGet(koopa->model);
        if (KOOPA_ABS(time - 15.0f) < 10.0f) {
            t = KOOPA_ABS(time - 15.0f) / 10.0f;
            t = 0.3f + 0.7f * t;
            speed *= t;
        }
        else if (KOOPA_ABS(time - 65.0f) < 10.0f) {
            t = KOOPA_ABS(time - 65.0f) / 10.0f;
            t = 0.3f + 0.7f * t;
            speed *= t;
        }
        dir.x = speed * HuSin(koopa->angle);
        dir.z = speed * HuCos(koopa->angle);
        koopa->pos.x += dir.x;
        koopa->pos.z += dir.z;
    }
    koopa->angle = fn_1_36EC(koopa->angleTarget, koopa->angle, 0.98f);
    koopa->rot.y = koopa->angle;
    return result;
}

s32 fn_1_DCC4(M562_KOOPA *koopa)
{
    float dot;
    M562_WORK *work = koopa->work;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    s32 result;
    s32 hitWall;
    HuVecF diff;
    HuVecF dir;
    HuVecF fwd;

    Hu3DMotionSpeedSet(koopa->model, 1.0f);
    result = 0;
    switch (koopa->subStep) {
        case 0:
            fn_1_ED90(koopa, &player->unk0A0, &koopa->chargeTarget);
            VECSubtract(&koopa->chargeTarget, &koopa->pos, &diff);
            dir = diff;
            dir.y = 0.0f;
            if (dir.x || dir.z) {
                VECNormalize(&dir, &dir);
            }
            else {
                result = 1;
                break;
            }
            fwd.x = HuSin(koopa->angle);
            fwd.y = 0.0f;
            fwd.z = HuCos(koopa->angle);
            dot = VECDotProduct(&dir, &fwd);
            if (dot > cos(0.05235987755982988)) {
                koopa->subStep = 2;
            }
            else {
                koopa->subStep = 1;
            }
            koopa->unk0E = 0;
            break;
        case 1:
            VECSubtract(&koopa->chargeTarget, &koopa->pos, &diff);
            dir = diff;
            dir.y = 0.0f;
            if (dir.x || dir.z) {
                VECNormalize(&dir, &dir);
            }
            else {
                result = 1;
                break;
            }
            fwd.x = HuSin(koopa->angle);
            fwd.y = 0.0f;
            fwd.z = HuCos(koopa->angle);
            dot = VECDotProduct(&dir, &fwd);
            if (dot > cos(0.05235987755982988)) {
                koopa->unk0E = 0;
                koopa->subStep = 2;
            }
            else {
                koopa->angleTarget = KOOPA_ANGLE(dir.x, dir.z);
                koopa->motNext = 12;
                koopa->motLoop = 1;
            }
            break;
        case 2:
            VECSubtract(&koopa->chargeTarget, &koopa->pos, &diff);
            diff.y = 0.0f;
            if (diff.x || diff.z) {
                VECNormalize(&diff, &diff);
            }
            else {
                diff.x = HuSin(koopa->angle);
                diff.z = HuCos(koopa->angle);
            }
            koopa->chargeDir = diff;
            koopa->motNext = 8;
            koopa->motLoop = 1;
            koopa->unk0E = 0;
            koopa->subStep++;
            break;
        case 3:
            koopa->unk0E++;
            VECNormalize(&koopa->chargeDir, &diff);
            koopa->angleTarget = KOOPA_ANGLE(diff.x, diff.z);
            diff.x = 1.6f * (10.0f * koopa->chargeDir.x);
            diff.z = 1.6f * (10.0f * koopa->chargeDir.z);
            koopa->pos.x += diff.x;
            koopa->pos.z += diff.z;
            koopa->motNext = 8;
            koopa->motLoop = 1;
            break;
    }
    koopa->angle = fn_1_36EC(koopa->angleTarget, koopa->angle, 0.9f);
    koopa->rot.y = koopa->angle;
    hitWall = 0;
    if (koopa->pos.z <= -400.0f) {
        hitWall = 1;
    }
    else if (koopa->pos.z >= 400.0f) {
        hitWall = 1;
    }
    if (koopa->pos.x <= -525.0f) {
        hitWall = 1;
    }
    else if (koopa->pos.x >= 525.0f) {
        hitWall = 1;
    }
    if (koopa->subStep < 3 || koopa->unk0E < 10) {
        hitWall = 0;
    }
    if (hitWall != 0) {
        fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
        omVibrate(player->unk014, 20, 12, 0);
        fn_1_814(0x8A6);
        result = 1;
    }
    return result;
}

s32 fn_1_E558(M562_KOOPA *koopa)
{
    float t;
    float dot;
    float s;
    M562_WORK *work = koopa->work;
    M562_CAMERA *camera = &work->camera[0];
    M562_STAGE *stage = &work->stage;
    M562_PLAYER *player = &work->player;
    M562_STAGETILE *tile;
    s32 result;
    s16 tileX;
    s16 tileZ;
    HuVecF dir;
    HuVecF fwd;

    Hu3DMotionSpeedSet(koopa->model, 1.0f);
    result = 0;
    switch (koopa->subStep) {
        case 0:
            tileX = 0.99f * (125.0f + (player->unk0A0.x - -500.0f)) / 250.0f;
            tileZ = 0.99f * (125.0f + (player->unk0A0.z - -375.0f)) / 250.0f;
            tile = &stage->unk008[tileX + tileZ * 5];
            koopa->jumpTarget = tile->unk10;
            koopa->tile = tile;
            VECSubtract(&koopa->jumpTarget, &koopa->pos, &dir);
            dir.y = 0.0f;
            if (dir.x || dir.z) {
                VECNormalize(&dir, &dir);
            }
            else {
                result = 1;
                break;
            }
            fwd.x = HuSin(koopa->angle);
            fwd.y = 0.0f;
            fwd.z = HuCos(koopa->angle);
            dot = VECDotProduct(&dir, &fwd);
            if (dot > cos(0.08726646259971647)) {
                koopa->subStep = 2;
            }
            else {
                koopa->subStep = 1;
            }
        case 1:
            VECSubtract(&koopa->jumpTarget, &koopa->pos, &dir);
            dir.y = 0.0f;
            if (dir.x || dir.z) {
                VECNormalize(&dir, &dir);
            }
            else {
                result = 1;
                break;
            }
            fwd.x = HuSin(koopa->angle);
            fwd.y = 0.0f;
            fwd.z = HuCos(koopa->angle);
            dot = VECDotProduct(&dir, &fwd);
            if (dot > cos(0.08726646259971647)) {
                koopa->subStep = 2;
            }
            else {
                koopa->angleTarget = KOOPA_ANGLE(dir.x, dir.z);
                koopa->motNext = 12;
                koopa->motLoop = 1;
            }
            break;
        case 2:
            koopa->jumpStart = koopa->pos;
            koopa->motNext = 3;
            koopa->motLoop = 0;
            koopa->unk0E = 0;
            koopa->subStep++;
            break;
        case 3:
            if (koopa->unk0E >= 20 && koopa->unk0E <= 60) {
                t = (koopa->unk0E - 20) / 40.0f;
                t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                s = HuSin(180.0f * t);
                koopa->pos.y = 500.0f * s;
                koopa->pos.x = koopa->jumpStart.x + t * (koopa->jumpTarget.x - koopa->jumpStart.x);
                koopa->pos.z = koopa->jumpStart.z + t * (koopa->jumpTarget.z - koopa->jumpStart.z);
            }
            else if (koopa->unk0E == 61) {
                koopa->tile->unk34 = 1;
                stage->unk5CC = koopa->jumpTarget;
                stage->unk5C8 = 1;
                fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
                fn_1_2DC08(camera->unk04, &koopa->pos, 0);
                omVibrate(player->unk014, 20, 12, 0);
                fn_1_814(0x8A7);
            }
            koopa->unk0E++;
            if (koopa->unk0E >= 80) {
                if (work->unk0020 == 0 || work->unk0020 == 1) {
                    koopa->speed += 0.5f;
                    koopa->speed = (koopa->speed > 8.5f) ? 8.5f : ((koopa->speed < 0.0f) ? 0.0f : koopa->speed);
                }
                result = 1;
            }
            break;
    }
    koopa->angle = fn_1_36EC(koopa->angleTarget, koopa->angle, 0.9f);
    koopa->rot.y = koopa->angle;
    return result;
}

void fn_1_ED90(M562_KOOPA *koopa, HuVecF *in, HuVecF *out)
{
    float minX;
    float maxX;
    float minZ;
    float maxZ;
    M562_WORK *work = koopa->work;
    M562_STAGE *stage = &work->stage;
    M562_STAGETILE *tile;

    tile = &stage->unk008[0];
    minX = tile->unk10.x;
    minZ = tile->unk10.z;
    tile = &stage->unk008[19];
    maxX = tile->unk10.x;
    maxZ = tile->unk10.z;
    out->x = (in->x > maxX) ? maxX : ((in->x < minX) ? minX : in->x);
    out->y = in->y;
    out->z = (in->z > maxZ) ? maxZ : ((in->z < minZ) ? minZ : in->z);
}

void fn_1_EEC4(M562_HITENTRY *a, M562_HITENTRY *b)
{
    M562_PLAYER *player;

    if (a->unk00 == 0 && b->unk00 == 3) {
        fn_1_F014(a->unk08, b->unk08);
    }
    else if (a->unk00 == 3 && b->unk00 == 0) {
        fn_1_F014(b->unk08, a->unk08);
    }
    else if (a->unk00 == 4 && b->unk00 == 0) {
        player = b->unk08;
        if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
            player->unk00A = 0;
            player->unk006 = 0;
            player->unk008 = 0;
            player->unk004 = 4;
        }
    }
    else if (a->unk00 == 0 && b->unk00 == 4) {
        player = a->unk08;
        if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
            player->unk00A = 0;
            player->unk006 = 0;
            player->unk008 = 0;
            player->unk004 = 4;
        }
    }
}

void fn_1_F014(M562_PLAYER *player, M562_KOOPA *koopa)
{
    float playerBottom;
    float koopaBottom;
    float playerTop;
    float koopaTop;
    float playerMid;
    float koopaMid;
    float rate;
    float playerHalf;
    float koopaHalf;
    float dist;
    float maxHalf;
    float midDist;
    float minHalf;
    M562_WORK *work = player->unk000;
    M562_CAMERA *camera = &work->camera[0];
    HuVecF diff;

    playerBottom = player->unk0A0.y;
    playerTop = playerBottom + player->unk068;
    koopaBottom = koopa->pos.y;
    koopaTop = 300.0f + koopaBottom;
    if ((playerTop == koopaTop && playerBottom == koopaBottom) || (playerTop <= koopaTop && playerTop >= koopaBottom)
        || (playerBottom <= koopaTop && playerBottom >= koopaBottom) || (koopaTop <= playerTop && koopaTop >= playerBottom)
        || (koopaBottom <= playerTop && koopaBottom >= playerBottom)) {
        diff.x = player->unk0A0.x - koopa->pos.x;
        diff.y = 0.0f;
        diff.z = player->unk0A0.z - koopa->pos.z;
        dist = VECMag(&diff);
        if (dist < 230.0f) {
            if (diff.x || diff.z) {
                VECNormalize(&diff, &diff);
            }
            else {
                diff.x = 0.0f;
                diff.z = 1.0f;
            }
            player->unk044 = KOOPA_ANGLE(-diff.x, -diff.z);
            VECScale(&diff, &diff, 230.0f - dist);
            playerMid = 0.5f * (playerBottom + playerTop);
            koopaMid = 0.5f * (koopaBottom + koopaTop);
            playerHalf = KOOPA_ABS(playerMid - playerBottom);
            koopaHalf = KOOPA_ABS(koopaMid - koopaBottom);
            maxHalf = (playerHalf > koopaHalf) ? playerHalf : koopaHalf;
            minHalf = (playerHalf > koopaHalf) ? koopaHalf : playerHalf;
            midDist = KOOPA_ABS(playerMid - koopaMid);
            rate = (midDist < maxHalf) ? 1.0f : (1.0f - (midDist - maxHalf) / minHalf);
            player->unk0A0.x += 0.9f * diff.x * rate;
            player->unk0A0.z += 0.9f * diff.z * rate;
            koopa->pos.x -= 0.1f * diff.x * rate;
            koopa->pos.z -= 0.1f * diff.z * rate;
            if (koopa->step != 7) {
                if (koopa->step == 3) {
                    koopa->unk10 = 120;
                    koopa->step = 2;
                }
                else if (koopa->step == 4) {
                    koopa->unk10 = 120;
                    koopa->step = 2;
                }
                else if (koopa->step == 6 && koopa->subStep >= 3 && koopa->unk0E >= 20) {
                    if (koopaBottom >= playerBottom && (player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
                        player->unk010 = player->unk012 = 140;
                        player->unk08C--;
                        omVibrate(player->unk014, 30, 4, 2);
                        CharFXPlay(player->unk018, 0x202);
                    }
                    fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
                    koopa->timer = 180;
                    koopa->unk10 = 60;
                    koopa->step = 2;
                }
                if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
                    if (koopa->step == 5) {
                        player->unk00A = 0;
                        player->unk006 = 0;
                        player->unk008 = 0;
                        player->unk004 = 6;
                        koopa->timer = 180;
                        koopa->unk10 = 60;
                        koopa->step = 2;
                    }
                    else {
                        player->unk00A = 0;
                        player->unk006 = 0;
                        player->unk008 = 0;
                        player->unk004 = 3;
                    }
                }
            }
        }
    }
}
