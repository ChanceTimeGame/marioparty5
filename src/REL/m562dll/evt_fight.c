/*
 * m562dll evt_fight.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_fight.s.
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

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0xBF0 lbl_1_rodata_BF0 (0xC): 0x00000000 0x00000000 0x43BB8000 -- an aggregate initialiser, write it as a local */
/* 0xBFC lbl_1_rodata_BFC (0xC): 0x00000000 0x00000000 0x43BB8000 -- an aggregate initialiser, write it as a local */
/* 0xC08 lbl_1_rodata_C08 (0xC): 0x00000000 0x447A0000 0xC2FA0000 -- an aggregate initialiser, write it as a local */
/* 0xC14 lbl_1_rodata_C14 (0xC): 0x00000000 0x00000000 0x43BB8000 -- an aggregate initialiser, write it as a local */
/* 0xC20 lbl_1_rodata_C20 (0xC): 0x00000000 0x00000000 0x43BB8000 -- an aggregate initialiser, write it as a local */
/* 0xC2C lbl_1_rodata_C2C (0xC): 0x00000000 0x447A0000 0xC2FA0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_C38 = 0.04f; /* 0xC38 */
static const float lbl_1_rodata_C3C = 0.03f; /* 0xC3C */
static const float lbl_1_rodata_C40 = 120.0f; /* 0xC40 */
static const double lbl_1_rodata_C48 = 0.25; /* 0xC48 */
static const double lbl_1_rodata_C50 = 2.0; /* 0xC50 */
static const double lbl_1_rodata_C58 = 3.141592653589793; /* 0xC58 */
static const float lbl_1_rodata_C60 = 180.0f; /* 0xC60 */
static const double lbl_1_rodata_C68 = 180.0; /* 0xC68 */
static const float lbl_1_rodata_C70 = 0.0f; /* 0xC70 */
static const float lbl_1_rodata_C74 = 50.0f; /* 0xC74 */
static const float lbl_1_rodata_C78 = 56.0f; /* 0xC78 */
static const float lbl_1_rodata_C7C = 4.0f; /* 0xC7C */
static const float lbl_1_rodata_C80 = 40.0f; /* 0xC80 */
static const float lbl_1_rodata_C84 = 0.95f; /* 0xC84 */
static const float lbl_1_rodata_C88 = 90.0f; /* 0xC88 */
static const float lbl_1_rodata_C8C = 1.0f; /* 0xC8C */
static const float lbl_1_rodata_C90 = 20.0f; /* 0xC90 */
static const float lbl_1_rodata_C94 = 0.06f; /* 0xC94 */
static const float lbl_1_rodata_C98 = 1000.0f; /* 0xC98 */
static const float lbl_1_rodata_C9C = 1.5f; /* 0xC9C */
static const float lbl_1_rodata_CA0 = -125.0f; /* 0xCA0 */
static const float lbl_1_rodata_CA4 = 5.0f; /* 0xCA4 */
static const float lbl_1_rodata_CA8 = 10.0f; /* 0xCA8 */
static const float lbl_1_rodata_CAC = -1.0f; /* 0xCAC */
static const float lbl_1_rodata_CB0 = 0.9f; /* 0xCB0 */
/* 0xCB8 lbl_1_rodata_CB8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_CC0 = 0.7f; /* 0xCC0 */
static const float lbl_1_rodata_CC4 = 0.3f; /* 0xCC4 */
static const float lbl_1_rodata_CC8 = 6.0f; /* 0xCC8 */
static const float lbl_1_rodata_CCC = 0.5f; /* 0xCCC */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7958 */ float lbl_1_bss_7958[2];

/* --- functions (reference order), .data placed before its first user --- */
/* 0xD28 */ HuVecF lbl_1_data_D28[2] = { { 0.0f, 347.9f, 26.0f }, { 0.0f, 1000.0f, 1400.0f } };
/* 0xD40 */ HuVecF lbl_1_data_D40[2] = { { 0.0f, 346.54f, 21.37f }, { 0.0f, 100.0f, -200.0f } };
/* 0xD58 */ s32 lbl_1_data_D58 = -1;

/* 1476 insns. Phase 2 -> 3: messages 0x410002/0x410003, the back wall opens, Bowser drops in
   (floor tile 7 is hit) and lands. Cases 10..14 are the retry (subGameNo >= 2) variant.
   Returns 1 when done. */
s32 fn_1_260B8(M562_WORK *work)
{
    M562_LIGHT *light;
    M562_MAINMDL *mainMdl;
    M562_CAMERA *camera;
    M562_STAGE *stage;
    M562_PLAYER *player;
    M562_PAD *pad;
    M562_KOOPA *koopa;
    M562_KOOPABOSS *boss;
    M562_BACK *back;
    M562_FIRE *fire;
    s32 result;
    float t;
    float dist;
    M562_STAGETILE *tile;
    HuVecF dir;
    HuVecF target;

    light = &work->light;
    mainMdl = &work->mainMdl;
    camera = &work->camera[0];
    stage = &work->stage;
    player = &work->player;
    pad = &player->unk06C;
    koopa = &work->koopa;
    boss = &work->koopaboss;
    back = &work->back;
    fire = &work->fire;
    result = 0;
    switch (work->unk0010) {
    case 0:
        back->unk24 = 1;
        back->unk28 = 0;
        fn_1_16F0(work, 2);
        koopa->dispReq = 1;
        koopa->mode = 2;
        koopa->step = 10;
        koopa->motNext = 0;
        koopa->motLoop = 1;
        koopa->unk1C = 0;
        Hu3DModelCameraSet(koopa->model, work->camera[0].unk04 | work->camera[1].unk04);
        if (GWSubGameNoGet() >= 2) {
            camera->unk0A = 1;
            camera->unk10 = lbl_1_data_D28[1];
            camera->unk1C = lbl_1_data_D40[1];
            camera->unk0C = 0;
            camera->unk7C = 0.04f;
            camera->unk80 = 0.04f;
            work->unk001C = 0;
            work->unk0010 = 10;
            break;
        }
        camera->unk0A = 1;
        camera->unk10 = lbl_1_data_D28[0];
        camera->unk1C = lbl_1_data_D40[0];
        camera->unk0C = 0;
        camera->unk7C = 0.04f;
        camera->unk80 = 0.03f;
        player->unk09A = 1;
        player->unk09C = 1;
        lbl_1_data_D58 = -1;
        work->unk0010++;
    case 1:
        t = work->unk001C / 120.0f;
        fn_1_22694(light, 2, t);
        fn_1_4748(back, 2, t);
        Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * HuSin(180.0f * t));
        if (work->unk001C < 60) {
            if (work->unk28AC < 0) {
                work->unk28AC = fn_1_814(0x8B5);
            }
        } else if (work->unk001C == 60) {
            if (work->unk28AC >= 0) {
                fn_1_864(work->unk28AC, 3000);
            }
        }
        target = (HuVecF) { 0.0f, 0.0f, 375.0f };
        PSVECSubtract(&target, &player->unk0A0, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dist > 50.0f) {
            PSVECNormalize(&dir, &dir);
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            pad->unk10 = 56.0f * dir.x;
            pad->unk11 = 56.0f * -dir.z;
            fn_1_7D58(player);
        }
        if (work->unk001C++ > 120) {
            player->unk0A0 = (HuVecF) { 0.0f, 0.0f, 375.0f };
            player->unk094 = player->unk090 = 180.0f;
            player->unk0AC.y = player->unk090;
            player->unk09A = 28;
            player->unk09C = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 2:
        HuWinExOpen(work->unk28A4);
        HuWinMesSet(work->unk28A4, 0x410002);
        fn_1_814(0x8C6);
        koopa->motNext = 5;
        koopa->motShiftNext = 30;
        koopa->motLoop = 1;
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 3:
        if (HuWinStatGet(work->unk28A4) == 2) {
        } else if (HuWinStatGet(work->unk28A4) == 1) {
            koopa->motCur = 0;
            koopa->motNext = 5;
            koopa->motLoop = 1;
        } else if (HuWinStatGet(work->unk28A4) == 0) {
            koopa->motNext = koopa->motCur = 11;
            koopa->motLoop = 0;
            koopa->motShiftTime = 0;
            Hu3DMotionShiftSet(koopa->model, koopa->motion[koopa->motNext], 4.0f, 0.0f, koopa->motLoop ? HU3D_MOTATTR_LOOP : 0);
            HuWinExClose(work->unk28A4);
            HuWinHomeClear(work->unk28A4);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 4:
        if (work->unk001C == 10) {
            fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
            omVibrate(player->unk014, 20, 12, 0);
            Hu3DMotionSpeedSet(back->unk20, 1.0f);
            Hu3DModelAttrReset(back->unk20, HU3D_ATTR_DISPOFF);
            back->unk30 = 0;
        }
        if (work->unk001C == 10) {
            fn_1_814(0x8B8);
        }
        if (work->unk001C == 40) {
            fn_1_814(0x8A3);
        }
        if (work->unk001C < 40) {
            back->unk24 = 1;
            back->unk28 = 0;
        } else if (work->unk001C < 80) {
            back->unk24 = 1;
            back->unk28 = 1;
        } else {
            back->unk24 = 0;
            back->unk28 = 0;
        }
        if (work->unk001C == 80) {
            fn_1_814(0x8BF);
        }
        if (work->unk001C >= 80 && work->unk001C < 100) {
            t = (work->unk001C - 80) / 20.0f;
            fn_1_277C8(work, t);
        }
        work->unk001C++;
        if (work->unk001C >= 120) {
            camera->unk0C = 0;
            camera->unk10 = lbl_1_data_D28[1];
            camera->unk1C = lbl_1_data_D40[1];
            camera->unk7C = 0.06f;
            camera->unk80 = 0.06f;
            koopa->dispReq = 1;
            koopa->mode = 3;
            koopa->step = 0;
            koopa->unk1C = 0;
            fn_1_22694(light, 2, 1.0f);
            fn_1_B578(koopa);
            koopa->pos = (HuVecF) { 0.0f, 1000.0f, -125.0f };
            Hu3DModelPosSet(koopa->model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            Hu3DModelScaleSet(koopa->model, 0.0f, 0.0f, 0.0f);
            koopa->step = 1;
            koopa->motNext = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 5:
        t = work->unk001C / 20.0f;
        koopa->pos.y = 1000.0f;
        Hu3DModelScaleSet(koopa->model, 1.5f * t, 1.5f * t, 1.5f * t);
        if (++work->unk001C >= 20) {
            koopa->motLoop = 0;
            koopa->motCur = koopa->motNext = 3;
            Hu3DModelAttrReset(koopa->model, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(koopa->model, koopa->motion[koopa->motCur], 0.0f, 4.0f, koopa->motLoop ? HU3D_MOTATTR_LOOP : 0);
            Hu3DMotionTimeSet(koopa->model, 40.0f);
            Hu3DModelScaleSet(koopa->model, 1.5f, 1.5f, 1.5f);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 6:
        t = work->unk001C / 20.0f;
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
        koopa->pos.x = 0.0f;
        koopa->pos.y = 1000.0f * (1.0f - t);
        koopa->pos.z = -125.0f;
        work->unk001C++;
        if (work->unk001C == 20) {
            fn_1_814(0x8A7);
            fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
            fn_1_2DC08(camera->unk04, &koopa->pos, 0);
            omVibrate(player->unk014, 20, 12, 0);
            tile = &stage->unk008[7];
            tile->unk34 = 1;
            stage->unk5CC = tile->unk10;
            stage->unk5C8 = 1;
        } else if (work->unk001C == 40) {
            koopa->motNext = 0;
            koopa->motLoop = 1;
        } else if (work->unk001C >= 60) {
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 7:
        HuWinExOpen(work->unk28A4);
        HuWinMesSet(work->unk28A4, 0x410003);
        fn_1_814(0x2CA);
        koopa->motNext = 5;
        koopa->motShiftNext = 30;
        koopa->motLoop = 1;
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 8:
        if (HuWinStatGet(work->unk28A4) == 2) {
        } else if (HuWinStatGet(work->unk28A4) == 1) {
        } else if (HuWinStatGet(work->unk28A4) == 0) {
            koopa->motNext = koopa->motCur = 0;
            koopa->motLoop = 1;
            koopa->motShiftTime = 0;
            Hu3DMotionShiftSet(koopa->model, koopa->motion[koopa->motNext], 0.0f, 20.0f, koopa->motLoop ? HU3D_MOTATTR_LOOP : 0);
            HuWinExClose(work->unk28A4);
            HuWinHomeClear(work->unk28A4);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 9:
        if (work->unk28AC >= 0) {
            fn_1_83C(work->unk28AC);
            work->unk28AC = -1;
        }
        if (GWSubGameNoGet() < 2) {
            GWSubGameNoSet(2);
        }
        player->unk004 = player->unk006 = 0;
        work->unk0010 = 0;
        result = 1;
        break;
    case 10:
        t = work->unk001C / 120.0f;
        fn_1_22694(light, 2, t);
        fn_1_4748(back, 2, t);
        Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * HuSin(180.0f * t));
        if (work->unk001C < 60) {
            if (work->unk28AC < 0) {
                work->unk28AC = fn_1_814(0x8B5);
            }
        } else if (work->unk001C == 60) {
            if (work->unk28AC >= 0) {
                fn_1_864(work->unk28AC, 3000);
            }
        }
        koopa->motNext = 0;
        koopa->motLoop = 1;
        target = (HuVecF) { 0.0f, 0.0f, 375.0f };
        PSVECSubtract(&target, &player->unk0A0, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dist > 5.0f) {
            PSVECNormalize(&dir, &dir);
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            pad->unk10 = 56.0f * dir.x;
            pad->unk11 = 56.0f * -dir.z;
            fn_1_7D58(player);
        } else {
            player->unk09A = 0;
            player->unk09C = 1;
        }
        work->unk001C++;
        if (work->unk001C > 120 && dist <= 10.0f) {
            target = (HuVecF) { 0.0f, 0.0f, 375.0f };
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 11:
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = -1.0f;
        if (fn_1_AD98(player, &dir, 0.9f)) {
            player->unk09A = 28;
            player->unk09C = 0;
            koopa->motNext = koopa->motCur = 11;
            koopa->motLoop = 0;
            koopa->motShiftTime = 0;
            Hu3DMotionShiftSet(koopa->model, koopa->motion[koopa->motNext], 4.0f, 0.0f, koopa->motLoop ? HU3D_MOTATTR_LOOP : 0);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 12:
        if (work->unk001C == 20) {
            fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
            omVibrate(player->unk014, 20, 12, 0);
            Hu3DMotionSpeedSet(back->unk20, 1.0f);
            Hu3DModelAttrReset(back->unk20, HU3D_ATTR_DISPOFF);
            back->unk30 = 0;
        }
        if (work->unk001C == 10) {
            fn_1_814(0x8B8);
        }
        if (work->unk001C == 40) {
            fn_1_814(0x8A3);
        }
        if (work->unk001C < 40) {
            back->unk24 = 1;
            back->unk28 = 0;
        } else if (work->unk001C < 80) {
            back->unk24 = 1;
            back->unk28 = 1;
        } else {
            back->unk24 = 0;
            back->unk28 = 0;
        }
        if (work->unk001C == 80) {
            fn_1_814(0x8BF);
        }
        if (work->unk001C >= 80 && work->unk001C < 100) {
            t = (work->unk001C - 80) / 20.0f;
            fn_1_277C8(work, t);
        }
        work->unk001C++;
        if (work->unk001C >= 120) {
            koopa->dispReq = 1;
            koopa->mode = 3;
            koopa->step = 0;
            koopa->unk1C = 0;
            fn_1_22694(light, 2, 1.0f);
            fn_1_B578(koopa);
            koopa->pos = (HuVecF) { 0.0f, 1000.0f, -125.0f };
            Hu3DModelPosSet(koopa->model, koopa->pos.x, koopa->pos.y, koopa->pos.z);
            Hu3DModelScaleSet(koopa->model, 0.0f, 0.0f, 0.0f);
            koopa->step = 1;
            koopa->motNext = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 13:
        t = work->unk001C / 20.0f;
        koopa->pos.y = 1000.0f;
        Hu3DModelScaleSet(koopa->model, 1.5f * t, 1.5f * t, 1.5f * t);
        if (++work->unk001C >= 20) {
            koopa->motLoop = 0;
            koopa->motCur = koopa->motNext = 3;
            Hu3DModelAttrReset(koopa->model, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(koopa->model, koopa->motion[koopa->motCur], 0.0f, 4.0f, koopa->motLoop ? HU3D_MOTATTR_LOOP : 0);
            Hu3DMotionTimeSet(koopa->model, 40.0f);
            Hu3DModelScaleSet(koopa->model, 1.5f, 1.5f, 1.5f);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 14:
        t = work->unk001C / 20.0f;
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
        koopa->pos.x = 0.0f;
        koopa->pos.y = 1000.0f * (1.0f - t);
        koopa->pos.z = -125.0f;
        work->unk001C++;
        if (work->unk001C == 20) {
            fn_1_21B68(camera, 1, 50, 40.0f, 0.95f, 90.0f);
            fn_1_2DC08(camera->unk04, &koopa->pos, 0);
            omVibrate(player->unk014, 20, 12, 0);
            tile = &stage->unk008[7];
            tile->unk34 = 1;
            stage->unk5CC = tile->unk10;
            stage->unk5C8 = 1;
            fn_1_814(0x8A7);
        } else if (work->unk001C == 40) {
            koopa->motNext = 0;
            koopa->motLoop = 1;
        } else if (work->unk001C >= 60) {
            work->unk001C = 0;
            work->unk0010 = 9;
        }
        break;
    }
    return result;
}

/* 98 insns. The back wall swing during the drop (t 0..1): slows over the last 30%. */
void fn_1_277C8(M562_WORK *work, float t)
{
    M562_BACK *back;
    float speed;

    back = &work->back;
    speed = (t < 0.7f) ? 1.0f : 1.0f - (t - 0.7f) / 0.3f;
    back->unk34.y -= 6.0f * speed;
    lbl_1_bss_7958[0] += 0.5f * speed;
    Hu3DModelRotSet(back->unk1A, 0.0f, 0.0f, lbl_1_bss_7958[0]);
    Hu3DModelRotSet(back->unk1C, 0.0f, 0.0f, lbl_1_bss_7958[0]);
    Hu3DModelRotSet(back->unk20, 0.0f, 0.0f, lbl_1_bss_7958[0]);
}
