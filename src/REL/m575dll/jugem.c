/*
 * m575dll jugem.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/jugem.s.
 */

#include "REL/m575dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x5A8 */ /* float lbl_1_rodata_5A8 = 0.0f; */
/* 0x5AC */ /* float lbl_1_rodata_5AC = 1.0f; */
/* 0x5B0 */ /* s32 lbl_1_rodata_5B0[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x5BC */ /* float lbl_1_rodata_5BC = -400.0f; */
/* 0x5C0 */ /* float lbl_1_rodata_5C0 = 2000.0f; */
/* 0x5C4 */ /* float lbl_1_rodata_5C4 = -600.0f; */
/* 0x5C8 */ /* float lbl_1_rodata_5C8 = 120.0f; */
/* 0x5CC */ /* float lbl_1_rodata_5CC = 80.0f; */
/* 0x5D0 */ /* float lbl_1_rodata_5D0 = -3000.0f; */
/* 0x5D4 */ /* float lbl_1_rodata_5D4 = 70.0f; */
/* 0x5D8 */ /* float lbl_1_rodata_5D8 = 100.0f; */
/* 0x5DC */ /* float lbl_1_rodata_5DC = 360.0f; */
/* 0x5E0 */ /* float lbl_1_rodata_5E0 = 10000.0f; */
/* 0x5E4 */ /* float lbl_1_rodata_5E4 = 0.017453292f; */
/* 0x5E8 */ /* float lbl_1_rodata_5E8 = 150.0f; */
/* 0x5EC */ /* float lbl_1_rodata_5EC = 400.0f; */
/* 0x5F0 */ /* float lbl_1_rodata_5F0 = -1.0f; */
/* 0x5F4 */ /* float lbl_1_rodata_5F4 = 50.0f; */
/* 0x5F8 */ /* double lbl_1_rodata_5F8 = 3.141592653589793; */
/* 0x600 */ /* double lbl_1_rodata_600 = 180; */
/* 0x608 */ /* double lbl_1_rodata_608 = 0; */
/* 0x610 */ /* float lbl_1_rodata_610 = 20.0f; */
/* 0x614 */ /* float lbl_1_rodata_614 = 40.0f; */
/* 0x618 */ /* float lbl_1_rodata_618 = 0.1f; */
/* 0x620 */ /* double lbl_1_rodata_620 = 4503599627370496; */
/* 0x628 */ /* float lbl_1_rodata_628 = 4.0f; */
/* 0x62C */ /* float lbl_1_rodata_62C = -120.0f; */

/* --- .data --- */
/* 0x2E0 */ char lbl_1_data_2E0[] = "itemhook_sao";

/* --- functions (reference order) --- */
/* 95 insns: Lakitu (jugem) model; the carrier that fishes a fallen player out */
void fn_1_C464(M575_JUGEM *jugem, M575_TEAM *game)
{
    M575_CAMERA *camera = &game->unkE20;
    HU3DMODELID modelId;

    memset(jugem, 0, sizeof(M575_JUGEM));
    jugem->unk000 = game;
    jugem->unk008 = modelId = Hu3DModelCreateData(0x82000C);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 3);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowSet(modelId);
    jugem->unk00A = Hu3DJointMotionData(modelId, 0x820013);
    jugem->unk00C = Hu3DJointMotionData(modelId, 0x820014);
    Hu3DMotionSet(modelId, jugem->unk00A);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrSet(modelId, 0x40000001);
}

/* 20 insns */
void fn_1_C5E0(M575_JUGEM *jugem)
{
    Hu3DMotionKill(jugem->unk00C);
    Hu3DMotionKill(jugem->unk00A);
    Hu3DModelKill(jugem->unk008);
    memset(jugem, 0, sizeof(M575_JUGEM));
}

/* 472 insns: state machine on unk004 (jumptable_1_data_2F0, 7 entries) */
void fn_1_C630(M575_JUGEM *jugem)
{
    M575_PLAYER *player = jugem->unk028;
    M575_TEAM *game = jugem->unk000;
    M575_TEN *ten = &game->unk1A0;
    M575_PLAYER *other;
    HuVecF dir;
    HuVecF pos;
    HuVecF ofs;
    Mtx rot;
    float angle;
    float mag;

    if (jugem->unk010.y < -400.0f) {
        Hu3DModelShadowDispOff(jugem->unk008);
    }
    else {
        Hu3DModelShadowDispOn(jugem->unk008);
    }
    switch (jugem->unk004) {
        case 0:
            break;
        case 1:
            if (!player) {
                jugem->unk004 = 0;
                break;
            }
            jugem->unk010.x = jugem->unk01C.x = jugem->unk028->unk078->x;
            jugem->unk010.y = jugem->unk01C.y = 2000.0f;
            jugem->unk010.z = jugem->unk01C.z = -600.0f;
            Hu3DModelPosSet(jugem->unk008, jugem->unk010.x, jugem->unk010.y, jugem->unk010.z);
            Hu3DModelAttrReset(jugem->unk008, HU3D_ATTR_DISPOFF);
            Hu3DModelObjPosGet(jugem->unk008, lbl_1_data_2E0, &pos);
            PSVECSubtract(&pos, &jugem->unk010, &jugem->unk03C);
            jugem->unk03C.y -= 120.0f;
            jugem->unk004++;
            break;
        case 2:
            jugem->unk01C.y -= 80.0f;
            if (jugem->unk010.y < -3000.0f) {
                jugem->unk006 = 0;
                jugem->unk004++;
            }
            break;
        case 3:
            fn_1_CD90(jugem, 1);
            jugem->unk006 = 0;
            jugem->unk004++;
            break;
        case 4:
            if (!player) {
                jugem->unk004 = 0;
                break;
            }
            jugem->unk01C.y += 70.0f;
            other = (&game->unk008[0] == player) ? &game->unk008[1] : &game->unk008[0];
            if (jugem->unk010.y > 100.0f) {
                if (other->unk0B0 != 0 || (!other->unk088.x && !other->unk088.z)) {
                    angle = 360.0f * ((frand() % 10000) / 10000.0f);
                    dir = (HuVecF) { 0.0f, 0.0f, -1.0f };
                    PSMTXRotRad(rot, 'Y', 0.017453292f * angle);
                    PSMTXMultVec(rot, &dir, &dir);
                    PSVECScale(&dir, &dir, 150.0f);
                    jugem->unk030.x = dir.x;
                    jugem->unk030.y = 400.0f;
                    jugem->unk030.z = dir.z;
                }
                else {
                    dir = other->unk088;
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, -1.0f);
                    mag = PSVECMag(&dir);
                    if (mag < 50.0f) {
                        PSVECScale(&dir, &dir, 50.0f / mag);
                    }
                    else if (mag > 150.0f) {
                        PSVECScale(&dir, &dir, 150.0f / mag);
                    }
                    jugem->unk030.x = dir.x;
                    jugem->unk030.y = 400.0f;
                    jugem->unk030.z = dir.z;
                }
                jugem->unk006 = 0;
                jugem->unk004++;
            }
            break;
        case 5:
            pos.x = jugem->unk030.x * ((cos(M_PI * ten->unk020 / 180.0) >= 0.0) ? cos(M_PI * ten->unk020 / 180.0) : -cos(M_PI * ten->unk020 / 180.0));
            pos.y = jugem->unk030.y;
            pos.z = jugem->unk030.z * ((cos(M_PI * ten->unk020 / 180.0) >= 0.0) ? cos(M_PI * ten->unk020 / 180.0) : -cos(M_PI * ten->unk020 / 180.0));
            PSVECAdd(&jugem->unk01C, &jugem->unk03C, &ofs);
            PSVECSubtract(&pos, &ofs, &dir);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 20.0f);
            PSVECAdd(&jugem->unk01C, &dir, &jugem->unk01C);
            PSVECAdd(&jugem->unk010, &jugem->unk03C, &ofs);
            PSVECSubtract(&pos, &ofs, &dir);
            mag = PSVECMag(&dir);
            if (mag < 40.0f) {
                fn_1_CD90(jugem, 0);
                jugem->unk028 = NULL;
                jugem->unk006 = 0;
                jugem->unk004++;
            }
            break;
        case 6:
            jugem->unk01C.y += 40.0f;
            if (jugem->unk010.z > -600.0f) {
                jugem->unk01C.z -= 20.0f;
            }
            if (jugem->unk010.y > 2000.0f) {
                Hu3DModelAttrSet(jugem->unk008, HU3D_ATTR_DISPOFF);
                jugem->unk006 = 0;
                jugem->unk004 = 0;
            }
            break;
    }
    PSVECSubtract(&jugem->unk01C, &jugem->unk010, &dir);
    PSVECScale(&dir, &dir, 0.1f);
    PSVECAdd(&jugem->unk010, &dir, &jugem->unk010);
    Hu3DModelPosSet(jugem->unk008, jugem->unk010.x, jugem->unk010.y, jugem->unk010.z);
}

/* 149 insns: grab (flag != 0) or release the carried player */
void fn_1_CD90(M575_JUGEM *jugem, s32 flag)
{
    M575_PLAYER *player = jugem->unk028;
    HuVecF pos;

    if (!player) {
        return;
    }
    if (flag) {
        fn_1_5C88(player, 0);
        Hu3DMotionShiftSet(player->unk014, player->unk016[6], 0.0f, 4.0f, 0x40000001);
        Hu3DMotionShiftSet(jugem->unk008, jugem->unk00C, 0.0f, 4.0f, 0);
        jugem->unk02C = 1;
        Hu3DModelHookSet(jugem->unk008, lbl_1_data_2E0, player->unk014);
        Hu3DModelPosSet(player->unk014, 0.0f, -120.0f, 0.0f);
        Hu3DModelRotSet(player->unk014, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(player->unk014, 1.0f, 1.0f, 1.0f);
        Hu3DModelAttrReset(player->unk014, HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelObjPosGet(jugem->unk008, lbl_1_data_2E0, &pos);
        PSVECSubtract(&pos, &jugem->unk010, &jugem->unk03C);
        jugem->unk03C.y -= 120.0f;
        PSVECAdd(&jugem->unk010, &jugem->unk03C, player->unk078);
        MgActorPosUpdate(player->unk008->actor, player->unk078);
        Hu3DModelHookReset(jugem->unk008);
        fn_1_5C88(player, 1);
        MgPlayerModeLandSet(player->unk008, 0);
        Hu3DMotionShiftSet(jugem->unk008, jugem->unk00A, 0.0f, 4.0f, 0x40000001);
        player->unk008->actor->velY = 0.0f;
        player->unk008->actor->rotY = player->unk07C->y;
        MgPlayerModeSet(player->unk008, 2);
        player->unk0B0 = 0;
        jugem->unk02C = 0;
        jugem->unk028 = NULL;
    }
}

/* 10 insns: player.c hands a fallen player to the jugem */
void fn_1_CFE4(M575_JUGEM *jugem, M575_PLAYER *player)
{
    if (!jugem->unk028) {
        jugem->unk028 = player;
    }
    if (jugem->unk004 == 0) {
        jugem->unk004 = 1;
    }
}
