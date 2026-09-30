/*
 * m562dll evt_winner.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_winner.s.
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
static const float lbl_1_rodata_F38 = 0.2f; /* 0xF38 */
static const float lbl_1_rodata_F3C = 60.0f; /* 0xF3C */
static const float lbl_1_rodata_F40 = 1.0f; /* 0xF40 */
static const float lbl_1_rodata_F44 = 0.0f; /* 0xF44 */
static const float lbl_1_rodata_F48 = 1000.0f; /* 0xF48 */
static const float lbl_1_rodata_F4C = 0.04f; /* 0xF4C */
static const float lbl_1_rodata_F50 = 0.9f; /* 0xF50 */
/* 0xF58 lbl_1_rodata_F58 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_F60 = 150.0f; /* 0xF60 */
static const float lbl_1_rodata_F64 = 200.0f; /* 0xF64 */
static const double lbl_1_rodata_F68 = 180.0; /* 0xF68 */
static const double lbl_1_rodata_F70 = 3.141592653589793; /* 0xF70 */
static const double lbl_1_rodata_F78 = 360.0; /* 0xF78 */
static const double lbl_1_rodata_F80 = -180.0; /* 0xF80 */
static const float lbl_1_rodata_F88 = -400.0f; /* 0xF88 */
static const float lbl_1_rodata_F8C = 400.0f; /* 0xF8C */
static const float lbl_1_rodata_F90 = -90.0f; /* 0xF90 */
static const float lbl_1_rodata_F94 = 90.0f; /* 0xF94 */
static const float lbl_1_rodata_F98 = 8.5f; /* 0xF98 */
static const float lbl_1_rodata_F9C = 4.5f; /* 0xF9C */
static const float lbl_1_rodata_FA0 = 0.25f; /* 0xFA0 */
static const double lbl_1_rodata_FA8 = 1.0; /* 0xFA8 */
static const float lbl_1_rodata_FB0 = 0.95f; /* 0xFB0 (+4 bytes: section tail alignment) */

/* --- functions (reference order), .data placed before its first user --- */
/* 0xF88 */ HuVecF lbl_1_data_F88 = { 0.0f, 0.0f, 0.0f };
/* 0xF94 */ HuVecF lbl_1_data_F94 = { 0.0f, 0.0f, 0.0f };

/* 332 insns: the loss sequence (player HP 0 or time out): camera pulls back onto the player,
   lose motion / voice, jingle 0x7A, Bowser wipe; returns 1 when done (m562 fn_1_6DC -> CLOSE) */
s32 fn_1_2C118(M562_WORK *work)
{
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    M562_KOOPA *koopa = &work->koopa;
    M562_PAD *pad = &player->unk06C; /* unused */
    s32 result = 0;
    float t;
    float dist;
    s32 done;
    HuVecF dir;

    switch (work->unk0010) {
    case 0:
        if (work->unk28A8 >= 0) {
            fn_1_9F4(work->unk28A8, 100);
            work->unk28A8 = -1;
        }
        if (lbl_1_bss_0->unk28B0 >= 0) {
            fn_1_864(lbl_1_bss_0->unk28B0, 1000);
        }
        fn_1_1D9C(work);
        work->unk001C = 0;
        work->unk0010++;
    case 1:
        lbl_1_data_F88 = camera->unk34;
        lbl_1_data_F94 = camera->unk40;
        camera->unk0A = 0;
        camera->unk7C = 0.2f;
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 2:
        t = work->unk001C / 60.0f;
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
        camera->unk1C.x = lbl_1_data_F94.x + t * (player->unk0A0.x - lbl_1_data_F94.x);
        camera->unk1C.y = lbl_1_data_F94.y + t * (player->unk0A0.y - lbl_1_data_F94.y);
        camera->unk1C.z = lbl_1_data_F94.z + t * (player->unk0A0.z - lbl_1_data_F94.z);
        PSVECSubtract(&camera->unk1C, &camera->unk10, &dir);
        dist = PSVECMag(&dir);
        if (dist > 1000.0f) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 0.04f * (dist - 1000.0f));
            PSVECAdd(&camera->unk10, &dir, &camera->unk10);
        }
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 1.0f;
        if (fn_1_AD98(player, &dir, 0.9f)) {
            player->unk09A = 0;
            player->unk09C = 1;
        }
        done = 1;
        if (work->unk000E == 3) {
            done = fn_1_2C648(work);
        }
        work->unk001C++;
        if ((work->unk001C >= 60 && done) || work->unk001C >= 180) {
            fn_1_A6C(0x7A);
            if (work->unk0022 == 2) {
                CharLoseVoicePlay(player->unk018, -1, -1, -1);
                player->unk09A = 25;
                player->unk09C = 0;
                work->unk001C = 0;
                work->unk0010 = 10;
            } else {
                work->unk001C = 0;
                work->unk0010++;
            }
        }
        break;
    case 3:
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 4:
        player->unk09A = 29;
        player->unk09C = 0;
        if (++work->unk001C >= 120) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_KOOPA | WIPE_TYPE_FBKEEP, 60);
            fn_1_814(0x8B6);
            work->unk001C = 0;
            work->unk0010 = 20;
        }
        break;
    case 10:
        player->unk09A = 25;
        player->unk09C = 0;
        if (++work->unk001C >= 180) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_KOOPA | WIPE_TYPE_FBKEEP, 60);
            fn_1_814(0x8B6);
            work->unk001C = 0;
            work->unk0010 = 20;
        }
        break;
    case 20:
        if (!WipeCheckEnd()) {
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 21:
        if (++work->unk001C >= 90) {
            work->unk001C = 0;
            work->unk0010 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 334 insns: phase 3 (Bowser on foot): keep Bowser out of the line between the camera and the
   player by walking him sideways; returns 1 once he is clear */
s32 fn_1_2C648(M562_WORK *work)
{
    M562_KOOPA *koopa = &work->koopa;
    M562_PLAYER *player = &work->player;
    M562_CAMERA *camera = &work->camera[0];
    s32 result = 1;
    HuVecF playerPos;
    HuVecF koopaPos;
    HuVecF cameraPos;
    HuVecF dir;
    HuVecF playerOfs;
    HuVecF koopaOfs;
    float playerDist;
    float koopaDist;
    float dist;
    float t;

    playerPos = player->unk0A0;
    koopaPos = koopa->pos;
    cameraPos = camera->unk10;
    playerPos.y = cameraPos.y = koopaPos.y = 0.0f;
    PSVECSubtract(&cameraPos, &playerPos, &playerOfs);
    playerDist = PSVECMag(&playerOfs);
    PSVECSubtract(&cameraPos, &koopaPos, &koopaOfs);
    koopaDist = PSVECMag(&koopaOfs);
    koopa->motNext = 0;
    koopa->motLoop = 1;
    if (koopaDist < 150.0f + playerDist) {
        dist = 0.0f;
        fn_1_2CB80(&koopaPos, &cameraPos, &playerPos, &dist);
        if (dist < 200.0f) {
            koopa->motNext = 1;
            koopa->motLoop = 1;
            PSVECSubtract(&koopaPos, &playerPos, &dir);
            if (dir.x || dir.z) {
                PSVECNormalize(&dir, &dir);
            } else {
                dir.z = 1.0f;
            }
            koopa->angleTarget = (180.0 * (atan2(dir.x, dir.z) / M_PI) > 180.0) ? 180.0 * (atan2(dir.x, dir.z) / M_PI) - 360.0
                : (180.0 * (atan2(dir.x, dir.z) / M_PI) <= -180.0) ? 360.0 + 180.0 * (atan2(dir.x, dir.z) / M_PI)
                                                                   : 180.0 * (atan2(dir.x, dir.z) / M_PI);
            if (koopa->pos.z <= -400.0f || koopa->pos.z >= 400.0f) {
                koopa->angleTarget = (koopaPos.x > 0.0f) ? -90.0f : 90.0f;
            }
            koopa->speed = 8.5f;
            t = (koopa->speed - 4.5f) / 4.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            Hu3DMotionSpeedSet(koopa->model, 1.0 + t);
            koopa->angle = fn_1_36EC(koopa->angleTarget, koopa->angle, 0.95f);
            dir.x = koopa->speed * sin(M_PI * koopa->angle / 180.0);
            dir.z = koopa->speed * cos(M_PI * koopa->angle / 180.0);
            koopa->pos.x += dir.x;
            koopa->pos.z += dir.z;
            koopa->rot.y = koopa->angle;
            result = 0;
        }
    }
    return result;
}

/* 123 insns: distance from pos to the segment start..end; returns 1 if the projection is inside */
s32 fn_1_2CB80(HuVecF *pos, HuVecF *start, HuVecF *end, float *dist)
{
    HuVecF dir;
    HuVecF nearest;
    HuVecF ofs;
    float startDot;
    float posDot;
    float t;
    s32 result;

    PSVECSubtract(end, start, &dir);
    startDot = PSVECDotProduct(start, &dir);
    posDot = PSVECDotProduct(pos, &dir);
    t = (-startDot + posDot) / (dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    result = 0;
    if (t >= 0.0f && t <= 1.0f) {
        result = 1;
    }
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    nearest.x = start->x + t * dir.x;
    nearest.y = start->y + t * dir.y;
    nearest.z = start->z + t * dir.z;
    PSVECSubtract(&nearest, pos, &ofs);
    *dist = PSVECMag(&ofs);
    return result;
}
