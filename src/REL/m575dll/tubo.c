/*
 * m575dll tubo.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/tubo.s.
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
/* 0x450 */ /* float lbl_1_rodata_450 = 0.0f; */
/* 0x454 */ /* float lbl_1_rodata_454 = 320.0f; */
/* 0x458 */ /* float lbl_1_rodata_458 = 1.0f; */
/* 0x45C */ /* float lbl_1_rodata_45C = 500.0f; */
/* 0x460 */ /* s32 lbl_1_rodata_460[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x46C */ /* s32 lbl_1_rodata_46C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x478 */ /* float lbl_1_rodata_478 = 30.0f; */
/* 0x480 */ /* double lbl_1_rodata_480 = 3.141592653589793; */
/* 0x488 */ /* float lbl_1_rodata_488 = 180.0f; */
/* 0x490 */ /* double lbl_1_rodata_490 = 180; */
/* 0x498 */ /* float lbl_1_rodata_498 = 130.0f; */
/* 0x49C */ /* float lbl_1_rodata_49C = 0.34906584f; */
/* 0x4A0 */ /* float lbl_1_rodata_4A0 = 120.0f; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 15; */
/* 0x4B0 */ /* float lbl_1_rodata_4B0 = 360.0f; */
/* 0x4B4 */ /* float lbl_1_rodata_4B4 = 0.7f; */
/* 0x4B8 */ /* float lbl_1_rodata_4B8 = 60.0f; */
/* 0x4BC */ /* float lbl_1_rodata_4BC = 1.0471976f; */
/* 0x4C0 */ /* float lbl_1_rodata_4C0 = 3.0f; */
/* 0x4C4 */ /* float lbl_1_rodata_4C4 = 0.2f; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 0.0001f; */
/* 0x4CC */ /* float lbl_1_rodata_4CC = 100.0f; */
/* 0x4D0 */ /* double lbl_1_rodata_4D0 = 360; */
/* 0x4D8 */ /* double lbl_1_rodata_4D8 = -180; */
/* 0x4E0 */ /* float lbl_1_rodata_4E0 = 10000.0f; */
/* 0x4E4 */ /* float lbl_1_rodata_4E4 = 45.0f; */
/* 0x4E8 */ /* float lbl_1_rodata_4E8 = 0.5f; */
/* 0x4EC */ /* float lbl_1_rodata_4EC = 400.0f; */
/* 0x4F0 */ /* float lbl_1_rodata_4F0 = 16.0f; */
/* 0x4F8 */ /* double lbl_1_rodata_4F8 = 4503601774854144; */
/* 0x500 */ /* double lbl_1_rodata_500 = 4503599627370496; */
/* 0x508 */ /* float lbl_1_rodata_508 = 0.001f; */
/* 0x50C */ /* float lbl_1_rodata_50C = 210.0f; */

#define M575_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m575, n), HU_MEMNUM_OVL, HEAP_MODEL)
#define M575_ABS(x) (((x) >= 0.0f) ? (x) : -(x))
#define M575_CLAMP(x, lo, hi) (((x) > (hi)) ? (hi) : (((x) < (lo)) ? (lo) : (x)))

/* --- functions (reference order) --- */
/* 177 insns */
void fn_1_9BC8(M575_TUBO *tubo, M575_TEAM *team)
{
    HU3DMODELID model;
    M575_CAMERA *camera;
    M575_TEAM *t;

    t = team;
    camera = &team->unkE20;
    memset(tubo, 0, sizeof(M575_TUBO));
    tubo->unk000 = team;
    if (t->unk004 == 0) {
        model = Hu3DModelCreate(M575_DATA(9));
        tubo->unk008 = model;
    }
    else {
        model = Hu3DModelCreate(M575_DATA(8));
        tubo->unk008 = model;
    }
    Hu3DModelPosSet(model, 0.0f, 320.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(model, camera->unk004);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelAttrReset(model, HU3D_ATTR_DISPOFF);
    tubo->unk00C = &Hu3DData[model].pos;
    tubo->unk010 = Hu3DData[model].mtx;
    Hu3DModelShadowSet(model);
    model = Hu3DModelCreate(M575_DATA(13));
    tubo->unk014 = model;
    Hu3DModelPosSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(model, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(model, camera->unk004);
    Hu3DModelLayerSet(model, 0);
    Hu3DModelAttrSet(model, HU3D_ATTR_DISPOFF);
    tubo->unk018 = &Hu3DData[model].pos;
    tubo->unk01C = Hu3DData[model].mtx;
    tubo->unk016 = Hu3DJointMotion(model, M575_DATA(23));
    Hu3DMotionSet(model, tubo->unk016);
    Hu3DMotionSpeedSet(model, 1.0f);
    Hu3DModelAttrReset(model, HU3D_MOTATTR_LOOP);
    fn_1_9320(&tubo->unk02C, 1, 500.0f, 1.0f, 0.0f);
    PSMTXIdentity(tubo->unk118);
}

/* 22 insns */
void fn_1_9E8C(M575_TUBO *tubo)
{
    fn_1_96F8(&tubo->unk02C);
    Hu3DMotionKill(tubo->unk016);
    Hu3DModelKill(tubo->unk014);
    Hu3DModelKill(tubo->unk008);
    memset(tubo, 0, sizeof(M575_TUBO));
}

/* 754 insns */
void fn_1_9EE4(M575_TUBO *tubo)
{
    Mtx mtx;
    HuVecF axis;
    HuVecF pos;
    HuVecF dir;
    HuVecF cross;
    HuVecF up;
    Quaternion q;
    Quaternion q2;
    Quaternion q3;
    float angle;
    float t;
    float dot;
    float speed;
    s32 flag;
    M575_TUBOEFF *eff;
    M575_WORK *work;
    M575_TEAM *team;

    team = tubo->unk000;
    work = team->unk000;
    eff = &tubo->unk02C;
    up = (HuVecF) { 0.0f, 1.0f, 0.0f };
    switch (tubo->unk004) {
    case 0:
        tubo->unk024 = 0.0f;
        tubo->unk028 = 0.0f;
        break;
    case 1:
        t = tubo->unk006 / 30.0f;
        tubo->unk024 = HuSin(180.0f * t);
        tubo->unk024 = 130.0f * tubo->unk024;
        PSMTXRotRad(mtx, 'Y', 0.34906584f);
        PSMTXConcat(tubo->unk118, mtx, tubo->unk118);
        if (tubo->unk006++ > 30) {
            PSMTXIdentity(tubo->unk118);
            tubo->unk004 = 0;
        }
        break;
    }
    tubo->unk020 = (work->unk008 % 120) / 120.0f;
    tubo->unk020 = 15.0 * HuSin(360.0f * tubo->unk020);
    tubo->unk020 += 320.0f;
    fn_1_9728(eff);
    eff->unk0C0 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    PSVECScale(&eff->unk0A8, &eff->unk0A8, 0.7f);
    PSVECScale(&eff->unk0B4, &eff->unk0B4, 0.7f);
    fn_1_AAAC(tubo, &team->unk008[0]);
    fn_1_AAAC(tubo, &team->unk008[1]);
    angle = 0.0f;
    dir.x = eff->unk048[1][0];
    dir.y = eff->unk048[1][1];
    dir.z = eff->unk048[1][2];
    PSVECNormalize(&dir, &dir);
    dot = PSVECDotProduct(&dir, &up);
    angle = 180.0 * (acosf(dot) / M_PI);
    if (angle > 60.0f) {
        axis.x = dir.x;
        axis.y = 0.0f;
        axis.z = dir.z;
        PSVECNormalize(&axis, &axis);
        PSVECCrossProduct(&up, &axis, &cross);
        PSMTXRotAxisRad(mtx, &cross, 1.0471976f);
        PSMTXMultVec(mtx, &up, &axis);
        fn_1_2D5C(&q, &dir, &axis);
        C_QUATMtx(&q2, eff->unk048);
        PSQUATMultiply(&q, &q2, &q3);
        PSMTXQuat(eff->unk048, &q3);
    }
    if (angle > 3.0f) {
        t = (M575_ABS(angle) - 3.0f) / 60.0f;
        t = M575_CLAMP(t, 0.2f, 1.0f);
        PSVECSubtract(&up, &dir, &axis);
        PSVECNormalize(&axis, &axis);
        PSVECScale(&axis, &axis, 0.0001f * t);
        PSVECScale(&dir, &dir, 100.0f);
        fn_1_9B58(eff, &axis, &dir);
    }
    tubo->unk00C->y = tubo->unk020 + tubo->unk024;
    PSMTXConcat(eff->unk048, tubo->unk118, mtx);
    PSMTXCopy(mtx, tubo->unk010);
    if (tubo->unk028 < angle) {
        tubo->unk028 = angle;
    }
    if (tubo->unk004 == 1 && tubo->unk006 == 15 && work->unk00C < 5) {
        axis.x = eff->unk048[1][0];
        axis.y = eff->unk048[1][1];
        axis.z = eff->unk048[1][2];
        if (axis.x || axis.y || axis.z) {
            PSVECNormalize(&axis, &axis);
        }
        else {
            axis.y = 1.0f;
        }
        PSVECScale(&axis, &pos, 100.0f);
        PSVECAdd(&pos, tubo->unk00C, &pos);
        axis.x = eff->unk048[1][0];
        axis.y = eff->unk048[1][1];
        axis.z = eff->unk048[1][2];
        axis.y = 0.0f;
        if (axis.x || axis.z) {
            PSVECNormalize(&axis, &axis);
        }
        else {
            axis.z = 1.0f;
        }
        angle = (HuAtan(axis.x, axis.z) > 180.0) ? (HuAtan(axis.x, axis.z) - 360.0)
                                                 : ((HuAtan(axis.x, axis.z) <= -180.0) ? (360.0 + HuAtan(axis.x, axis.z)) : HuAtan(axis.x, axis.z));
        angle += 60.0f * ((frand() % 10000) / 10000.0f) - 30.0f;
        axis.x = HuSin(angle);
        axis.y = 0.0f;
        axis.z = HuCos(angle);
        t = M575_ABS(tubo->unk028) / 45.0f;
        t = M575_CLAMP(t, 0.5f, 1.0f);
        PSVECScale(&axis, &axis, 400.0f * t);
        flag = 0;
        speed = 16.0f;
        if ((s16)tubo->unk14A < work->unk2604 && (s16)tubo->unk148 >= work->unk2606[tubo->unk14A]) {
            flag = 1;
            tubo->unk14A++;
        }
        fn_1_B240(&team->unkFDC, flag, &pos, &axis, speed);
        tubo->unk148++;
        Hu3DMotionTimeSet(tubo->unk014, 0.0f);
        Hu3DModelAttrReset(tubo->unk014, HU3D_ATTR_DISPOFF);
    }
    if (Hu3DMotionTimeGet(tubo->unk014) < Hu3DMotionMaxTimeGet(tubo->unk014)) {
        axis.x = eff->unk048[1][0];
        axis.y = eff->unk048[1][1];
        axis.z = eff->unk048[1][2];
        if (axis.x || axis.y || axis.z) {
            PSVECNormalize(&axis, &axis);
        }
        else {
            axis.y = 1.0f;
        }
        PSVECScale(&axis, &pos, 100.0f);
        PSVECAdd(&pos, tubo->unk00C, &pos);
        PSMTXCopy(eff->unk048, tubo->unk01C);
        *tubo->unk018 = pos;
    }
    else {
        Hu3DModelAttrSet(tubo->unk014, HU3D_ATTR_DISPOFF);
    }
}

/* 273 insns */
s32 fn_1_AAAC(M575_TUBO *tubo, M575_PLAYER *player)
{
    HuVecF d2;
    HuVecF diff;
    HuVecF norm;
    float head;
    float bottom;
    float t;
    float dy;
    float dist;
    float top;
    float feet;
    s32 result;
    M575_TUBOEFF *eff;
    M575_TEAM *team;

    team = player->unk000;
    eff = &tubo->unk02C;
    feet = player->unk078->y;
    head = player->unk078->y + player->unk028;
    bottom = tubo->unk00C->y;
    top = 120.0f + bottom;
    dy = 0.0f;
    result = 0;
    if ((feet >= bottom && head < top) || (feet <= bottom && head > top) || (head >= bottom && head < top)) {
        diff.x = player->unk078->x - tubo->unk00C->x;
        diff.y = 0.0f;
        diff.z = player->unk078->z - tubo->unk00C->z;
        dist = PSVECMag(&diff);
        if (dist < 130.0f && player->unk008->actor->velY > 0.0f) {
            if (M575_ABS(head - bottom) < 130.0f - dist) {
                dy = head - bottom;
                player->unk078->y -= M575_ABS(dy);
                MgActorPosUpdate(player->unk008->actor, player->unk078);
                if (tubo->unk004 == 0) {
                    d2 = diff;
                    diff.x = 0.0f;
                    diff.y = 0.001f;
                    diff.z = 0.0f;
                    fn_1_9B58(eff, &diff, &d2);
                    tubo->unk004 = 1;
                    tubo->unk006 = 0;
                    player->unk0A0 = 0;
                    if (player->unk008->actor->velY > 0.0f) {
                        t = player->unk028 / 210.0f;
                        t = 1.0f - M575_CLAMP(t, 0.0f, 1.0f);
                        player->unk008->actor->velY = -player->unk008->actor->velY * t;
                        MgPlayerModeSet(player->unk008, MGPLAYER_MODE_FALL);
                    }
                    omVibrate(player->unk00E, 15, 6, 6);
                    if (team->unk004 == 0) {
                        fn_1_530(0x934);
                    }
                    else if (team->unk004 == 1) {
                        fn_1_530(0x935);
                    }
                }
            }
            else {
                PSVECNormalize(&diff, &norm);
                PSVECScale(&norm, &norm, 130.0f - dist);
                PSVECAdd(player->unk078, &norm, player->unk078);
                MgActorPosUpdate(player->unk008->actor, player->unk078);
            }
            result = 1;
        }
    }
    return result;
}
