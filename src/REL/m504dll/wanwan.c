/*
 * m504dll wanwan.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/wanwan.s.
 */

#include "REL/m504dll.h"

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
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 2.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 0.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 4.0f; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 1.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 2.5f; */
/* 0x1FC */ /* s32 lbl_1_rodata_1FC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x208 */ /* s32 lbl_1_rodata_208[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x214 */ /* float lbl_1_rodata_214 = 8.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 24.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 180.0f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 360.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = -180.0f; */
/* 0x228 */ /* float lbl_1_rodata_228 = 20.0f; */
/* 0x230 */ /* double lbl_1_rodata_230 = 6; */
/* 0x238 */ /* double lbl_1_rodata_238 = 0.8; */
/* 0x240 */ /* float lbl_1_rodata_240 = 10.0f; */
/* 0x244 */ /* float lbl_1_rodata_244 = 90.0f; */
/* 0x248 */ /* double lbl_1_rodata_248 = 3.141592653589793; */
/* 0x250 */ /* double lbl_1_rodata_250 = 180; */
/* 0x258 */ /* float lbl_1_rodata_258 = 50.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = -3.75f; */
/* 0x260 */ /* float lbl_1_rodata_260 = 0.8f; */
/* 0x264 */ /* float lbl_1_rodata_264 = 100.0f; */
/* 0x268 */ /* float lbl_1_rodata_268 = 45.0f; */
/* 0x26C */ /* float lbl_1_rodata_26C = 75.0f; */
/* 0x270 */ /* float lbl_1_rodata_270 = 200.0f; */
/* 0x274 */ /* float lbl_1_rodata_274 = 25.0f; */
/* 0x278 */ /* float lbl_1_rodata_278 = 0.95f; */
/* 0x280 */ /* double lbl_1_rodata_280 = 0.6; */
/* 0x288 */ /* float lbl_1_rodata_288 = 0.9f; */
/* 0x28C */ /* float lbl_1_rodata_28C = 0.1f; */
/* 0x290 */ /* float lbl_1_rodata_290 = 40.0f; */
/* 0x294 */ /* float lbl_1_rodata_294 = 3700.0f; */
/* 0x298 */ /* float lbl_1_rodata_298 = 3.0f; */
/* 0x29C */ /* float lbl_1_rodata_29C = 3550.0f; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 4503599627370496; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = 1; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 0; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 0.5; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 3; */
/* 0x2C8 */ /* float lbl_1_rodata_2C8 = 270.0f; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 360; */
/* 0x2D8 */ /* double lbl_1_rodata_2D8 = -180; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0[2] = { 250.0f, 0.0f }; */

/* --- .data --- */
/* 0x498: jumptable_1_data_498 is fn_1_9CAC's switch; lbl_1_data_4C4 is defined below it */

/* --- functions (reference order) --- */
/* 356 insns */
void fn_1_9680(M504_WANWAN *wanwan, M504_LANE *laneP)
{
    M504_LANE *lane = laneP;
    M504_WORK *work = lane->unk000;
    s16 *models = work->unk012;
    s16 cameraNo = lane->unk004;
    s16 modelId;

    memset(wanwan, 0, sizeof(M504_WANWAN));
    wanwan->unk000 = laneP;
    wanwan->unk07C = 0;
    wanwan->unk008 = 0;
    wanwan->unk00A = 0;
    wanwan->unk00C = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x0), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelReflectTypeSet(modelId, 4);
    wanwan->unk00E[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x3D), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[1] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x3E), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[2] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x3F), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[3] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x40), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[4] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x41), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[5] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x42), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[6] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x43), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[7] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x44), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[8] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x45), HU_MEMNUM_OVL, HEAP_MODEL));
    wanwan->unk00E[9] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x46), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, wanwan->unk00E[0]);
    Hu3DMotionSpeedSet(modelId, 2.0f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(modelId);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[laneP->unk004]);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    wanwan->unk038 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    wanwan->unk044 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    Hu3DModelPosSet(modelId, wanwan->unk038.x, wanwan->unk038.y, wanwan->unk038.z);
    Hu3DModelRotSet(modelId, wanwan->unk044.x, wanwan->unk044.y, wanwan->unk044.z);
    wanwan->unk004 = 5;
    wanwan->unk028 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x24), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 4.0f, 4.0f, 4.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[cameraNo]);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    wanwan->unk02A = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x47), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, wanwan->unk02A);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    wanwan->unk02C = 0;
    wanwan->unk030 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x25), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 2.5f, 2.5f, 2.5f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[cameraNo]);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    wanwan->unk032 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m504, 0x48), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, wanwan->unk032);
    Hu3DMotionSpeedSet(modelId, 2.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    wanwan->unk034 = 0;
}

/* 39 insns */
void fn_1_9C10(M504_WANWAN *wanwan)
{
    s32 i;

    Hu3DMotionKill(wanwan->unk032);
    Hu3DMotionKill(wanwan->unk02A);
    Hu3DModelKill(wanwan->unk030);
    Hu3DModelKill(wanwan->unk028);
    Hu3DModelAttrSet(wanwan->unk00C, HU3D_MOTATTR_PAUSE);
    for (i = 0; i < 10; i++) {
        Hu3DMotionKill(wanwan->unk00E[i]);
    }
    Hu3DModelKill(wanwan->unk00C);
    memset(wanwan, 0, sizeof(M504_WANWAN));
}

/* 933 insns */
s32 fn_1_9CAC(M504_WANWAN *wanwan)
{
    M504_LANE *lane = wanwan->unk000;
    M504_STAGE *stage = &lane->unk15C;
    M504_CAMERA *camera = &lane->unk3BC;
    M504_PLAYER *player = &lane->unk008;
    M504_WORK *work = lane->unk000;
    s32 result;
    float speed;
    float cosTilt;
    float mag;
    float dot;
    float rad;
    float angle;
    HuVecF push;
    HuVecF dir;
    HuVecF normal;
    s16 itemNo;
    s16 hitNo;

    if (work->unk1218) {
        return 0;
    }
    wanwan->unk05C = (HuVecF) { 0.0f, 0.0f, 0.0f };
    result = 0;
    switch (wanwan->unk004) {
        case 0:
            if (wanwan->unk07C) {
                wanwan->unk004 = 1;
            }
            break;
        case 1:
            Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[4], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            wanwan->unk004 = 2;
            break;
        case 2:
            wanwan->unk044.y += 24.0f;
            wanwan->unk044.y = (wanwan->unk044.y > 180.0f) ? (wanwan->unk044.y - 360.0f) : ((wanwan->unk044.y <= -180.0f) ? (360.0f + wanwan->unk044.y) : wanwan->unk044.y);
            if (!(wanwan->unk044.y < 0.0f) && !(wanwan->unk044.y > 24.0f)) {
                if (wanwan->unk008) {
                    wanwan->unk008--;
                }
                if (wanwan->unk008 == 0 && player->unk006 != 3) {
                    wanwan->unk050.y = 20.0f;
                    wanwan->unk074 = 6.0 + 0.8 * (float)wanwan->unk00A;
                    wanwan->unk044.y = wanwan->unk078;
                    wanwan->unk068 = 20.0f;
                    wanwan->unk06C = 0.0f;
                    wanwan->unk006 = 30;
                    Hu3DModelAttrReset(wanwan->unk00C, HU3D_MOTATTR_LOOP);
                    Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                    if (wanwan->unk07C) {
                        fn_1_5EC(0x2D8);
                    }
                    wanwan->unk004 = 3;
                }
            }
            break;
        case 3:
            wanwan->unk06C += 10.0f;
            if (wanwan->unk06C > 90.0f) {
                wanwan->unk06C = 0.0f;
            }
            cosTilt = cos(M_PI * wanwan->unk06C / 180.0);
            wanwan->unk044.x = wanwan->unk068 * cosTilt;
            wanwan->unk05C.x = 50.0f * cosTilt * sin(M_PI * wanwan->unk044.y / 180.0);
            wanwan->unk05C.z = 50.0f * cosTilt * cos(M_PI * wanwan->unk044.y / 180.0);
            if (wanwan->unk006) {
                wanwan->unk006--;
            }
            if (wanwan->unk006 == 0) {
                Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                wanwan->unk044.x = 0.0f;
                wanwan->unk004 = 4;
            }
            break;
        case 4:
            wanwan->unk074 += 0.8;
            wanwan->unk050.y += -3.75f;
            speed = wanwan->unk074 + 0.8f * wanwan->unk050.y;
            wanwan->unk050.x = speed * sin(M_PI * wanwan->unk078 / 180.0);
            wanwan->unk050.z = speed * cos(M_PI * wanwan->unk078 / 180.0);
            wanwan->unk038.x += wanwan->unk050.x;
            wanwan->unk038.y += wanwan->unk050.y;
            wanwan->unk038.z += wanwan->unk050.z;
            if (wanwan->unk038.y < 0.0f) {
                fn_1_D1F0(lbl_1_data_45E0[lane->unk004], &wanwan->unk038);
                if (wanwan->unk07C) {
                    if (lane->unk46C) {
                        fn_1_5EC(0x646);
                    } else {
                        fn_1_5EC(0x647);
                    }
                }
                wanwan->unk038.y = 0.0f;
                wanwan->unk050.y = 20.0f;
            }
            wanwan->unk006 = 1;
            if (fn_1_4030(stage, &wanwan->unk038, 100.0f, &push, 1, &itemNo, &hitNo) == 0) {
                break;
            }
            mag = PSVECMag(&push);
            if (hitNo >= 0 && mag < speed) {
                break;
            }
            dir = wanwan->unk050;
            dir.y = 0.0f;
            PSVECNormalize(&dir, &dir);
            normal.x = -push.x;
            normal.z = -push.z;
            normal.y = 0.0f;
            PSVECNormalize(&normal, &normal);
            dot = PSVECDotProduct(&dir, &normal);
            rad = acos(dot);
            angle = 180.0 * (rad / M_PI);
            if (itemNo >= 0) {
                if (stage->unk07C[itemNo].unk010 == 1) {
                    if (angle > 45.0f) {
                        break;
                    }
                } else if (angle > 75.0f) {
                    break;
                }
            } else if (angle > 75.0f) {
                break;
            }
            wanwan->unk006 = 0;
            Hu3DModelPosSet(wanwan->unk028, wanwan->unk038.x, 200.0f + wanwan->unk038.y, wanwan->unk038.z);
            Hu3DMotionTimeSet(wanwan->unk028, 0.0f);
            Hu3DModelAttrReset(wanwan->unk028, HU3D_ATTR_DISPOFF);
            wanwan->unk02C = 1;
            if (wanwan->unk07C) {
                if (lane->unk46C) {
                    fn_1_5EC(0x649);
                } else {
                    fn_1_5EC(0x64A);
                }
            }
            omVibrate(lane->unk004, 20, 6, 6);
            Hu3DModelAttrReset(wanwan->unk00C, HU3D_MOTATTR_LOOP);
            Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[7], 0.0f, 2.0f, HU3D_MOTATTR_NONE);
            fn_1_C99C(&stage->unk000->unk3BC, 0, 60, 25.0f, 0.95f, 90.0f);
            fn_1_5870(stage, itemNo);
            wanwan->unk004 = 5;
            break;
        case 5:
            if (Hu3DMotionShiftIDGet(wanwan->unk00C) < 0) {
                Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                wanwan->unk004 = 6;
            }
        case 6:
            wanwan->unk050.y += -3.75f;
            wanwan->unk038.y += wanwan->unk050.y;
            if (wanwan->unk038.y > 0.0f) {
                break;
            }
            wanwan->unk038.y = 0.0f;
            if (wanwan->unk006++ < 120) {
                break;
            }
            player->unk006 != 0;
            break;
        case 7:
            if (wanwan->unk006++ < 30) {
                break;
            }
            wanwan->unk006 = 0;
            wanwan->unk004 = 1;
            break;
        case 8:
            wanwan->unk074 += 0.6;
            wanwan->unk050.y += -3.75f;
            wanwan->unk044.y *= 0.9f;
            speed = wanwan->unk074 + 0.8f * wanwan->unk050.y;
            wanwan->unk050.x = 0.1f * -wanwan->unk038.x;
            wanwan->unk050.z = speed;
            wanwan->unk038.x += wanwan->unk050.x;
            wanwan->unk038.y += wanwan->unk050.y;
            wanwan->unk038.z += wanwan->unk050.z;
            if (wanwan->unk038.y < 0.0f) {
                wanwan->unk038.y = 0.0f;
                wanwan->unk050.y = 40.0f;
            }
            if (wanwan->unk038.z > 3700.0f) {
                wanwan->unk038.z = 3700.0f;
                if (((wanwan->unk044.y >= 0.0f) ? wanwan->unk044.y : -wanwan->unk044.y) < 3.0f && wanwan->unk038.y <= 0.0f) {
                    wanwan->unk044.y = 0.0f;
                    Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[8], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    wanwan->unk004 = 10;
                }
            }
            break;
        case 9:
            wanwan->unk038.y = 0.0f;
            if (((wanwan->unk044.y >= 0.0f) ? wanwan->unk044.y : -wanwan->unk044.y) > 24.0f) {
                wanwan->unk044.y += 24.0f;
                wanwan->unk044.y = (wanwan->unk044.y > 180.0f) ? (wanwan->unk044.y - 360.0f) : ((wanwan->unk044.y <= -180.0f) ? (360.0f + wanwan->unk044.y) : wanwan->unk044.y);
            } else {
                wanwan->unk044.y = 0.0f;
            }
            break;
        case 10:
            break;
    }
    if (wanwan->unk004 < 8 && wanwan->unk038.z > 3550.0f) {
        wanwan->unk07C = 0;
        result = 1;
    }
    if (fn_1_4030(stage, &wanwan->unk038, 100.0f, &push, 1, &itemNo, &hitNo)) {
        wanwan->unk038.x += push.x;
        wanwan->unk038.z += push.z;
    }
    Hu3DModelPosSet(wanwan->unk00C, wanwan->unk038.x + wanwan->unk05C.x, wanwan->unk038.y + wanwan->unk05C.y, wanwan->unk038.z + wanwan->unk05C.z);
    Hu3DModelRotSet(wanwan->unk00C, wanwan->unk044.x, wanwan->unk044.y, wanwan->unk044.z);
    if (wanwan->unk024 && wanwan->unk004 != 9) {
        Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[8], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        wanwan->unk05C = (HuVecF) { 0.0f, 0.0f, 0.0f };
        wanwan->unk038.y = 0.0f;
        wanwan->unk044.x = 0.0f;
        wanwan->unk004 = 9;
    }
    if (wanwan->unk02C) {
        if (Hu3DMotionTimeGet(wanwan->unk028) >= Hu3DMotionMaxTimeGet(wanwan->unk028)) {
            Hu3DModelAttrSet(wanwan->unk028, HU3D_ATTR_DISPOFF);
            wanwan->unk02C = 0;
        }
    }
    if (wanwan->unk034) {
        if (Hu3DMotionTimeGet(wanwan->unk030) >= Hu3DMotionMaxTimeGet(wanwan->unk030)) {
            Hu3DModelAttrSet(wanwan->unk030, HU3D_ATTR_DISPOFF);
            wanwan->unk034 = 0;
        }
    }
    return result;
}

/* 232 insns: M433StageMtxRotGet (m433dll stage.c) */
void fn_1_AB40(Mtx mtx, HuVecF *rot)
{
    float z;
    float mag;

    rot->x = HuAtan(mtx[1][2], mtx[2][2]);
    if (rot->x < 0.0f) {
        rot->x += 360.0f;
    }
    rot->z = HuAtan(mtx[0][1], mtx[0][0]);
    if (rot->z < 0.0f) {
        rot->z += 360.0f;
    }
    z = -mtx[0][2];
    mag = sqrtf((1.0 - (z * z)) >= 0.0 ? (1.0 - (z * z)) : (-(1.0 - (z * z))));
    if ((rot->x > 90.0f) && (rot->x < 270.0f) && (rot->z > 90.0f) && (rot->z < 270.0f)) {
        rot->x = fmod(180.0f + rot->x, 360.0);
        rot->z = fmod(180.0f + rot->z, 360.0);
        mag = -mag;
    }
    rot->y = HuAtan(z, mag);
    if (rot->y < 0.0f) {
        rot->y += 360.0f;
    }
}

/* 179 insns */
s32 fn_1_AEE0(M504_WANWAN *wanwan, float *angle)
{
    M504_PLAYER *player = &wanwan->unk000->unk008;
    HuVecF dir;
    HuVecF face;
    float dot;
    float diff;
    float rad;

    PSVECSubtract(&player->unk060, &wanwan->unk038, &dir);
    dir.y = 0.0f;
    PSVECNormalize(&dir, &dir);
    *angle = (HuAtan(dir.x, dir.z) > 180.0) ? (HuAtan(dir.x, dir.z) - 360.0) : ((HuAtan(dir.x, dir.z) <= -180.0) ? (360.0 + HuAtan(dir.x, dir.z)) : HuAtan(dir.x, dir.z));
    face.x = sin(M_PI * wanwan->unk044.y / 180.0);
    face.y = 0.0f;
    face.z = cos(M_PI * wanwan->unk044.y / 180.0);
    dot = PSVECDotProduct(&dir, &face);
    rad = acos(dot);
    diff = 180.0 * (rad / M_PI);
    if (diff < 24.0f) {
        return 1;
    } else {
        return 0;
    }
}

/* 164 insns */
void fn_1_B1AC(M504_WANWAN *wanwan)
{
    M504_LANE *lane = wanwan->unk000;
    M504_PLAYER *player = &lane->unk008;
    HuVecF dir;

    if (wanwan->unk07C && (wanwan->unk004 == 5 || wanwan->unk004 == 6)) {
        wanwan->unk044.x = wanwan->unk044.z = 0.0f;
        wanwan->unk044.y = wanwan->unk078;
        wanwan->unk038.y = 0.0f;
        wanwan->unk008 = rand8() % 3;
        wanwan->unk00A = 0;
        Hu3DModelAttrReset(wanwan->unk00C, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[5], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
        PSVECSubtract(&player->unk060, &wanwan->unk038, &dir);
        dir.y = 0.0f;
        PSVECNormalize(&dir, &dir);
        wanwan->unk078 = (HuAtan(dir.x, dir.z) > 180.0) ? (HuAtan(dir.x, dir.z) - 360.0) : ((HuAtan(dir.x, dir.z) <= -180.0) ? (360.0 + HuAtan(dir.x, dir.z)) : HuAtan(dir.x, dir.z));
        wanwan->unk006 = 0;
        wanwan->unk004 = 7;
    }
}

/* 60 insns */
s32 fn_1_B43C(M504_WANWAN *wanwan, HuVecF *pos, float radius, HuVecF *push, s32 useY)
{
    HuVecF dir;
    float mag;
    float depth;

    PSVECSubtract(pos, &wanwan->unk038, &dir);
    if (!useY) {
        dir.y = 0.0f;
    }
    mag = PSVECMag(&dir);
    if (mag < 100.0f + radius) {
        PSVECNormalize(&dir, &dir);
        depth = (100.0f + radius) - mag;
        PSVECScale(&dir, push, depth);
        return 1;
    } else {
        return 0;
    }
}

/* .data 0x4C4: the eight probe directions of fn_1_B52C (defined after fn_1_9CAC so its jumptable comes first) */
/* 0x4C4 */ HuVecF lbl_1_data_4C4[8] = { { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, -1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 1.0f }, { -1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, -1.0f } };

/* 191 insns */
s32 fn_1_B52C(M504_WANWAN *wanwan, HuVecF *out)
{
    s32 i;
    s32 num;
    s32 tries;
    s32 bestNo;
    M504_LANE *lane;
    M504_PLAYER *player;
    M504_STAGE *stage;
    float dist;
    float angle;
    float best;
    float dot;
    float rad;
    HuVecF cand[8];
    s32 dirNo[8];
    HuVecF v;
    HuVecF face;
    HuVecF push;
    s16 itemNo;
    s16 hitNo;

    lane = wanwan->unk000;
    player = &lane->unk008;
    stage = &lane->unk15C;
    dist = 250.0f;
    tries = 0;
    num = tries;
    while (num == 0) {
        num = 0;
        for (i = 0; i < 8; i++) {
            PSVECNormalize(&lbl_1_data_4C4[i], &v);
            PSVECScale(&v, &v, dist);
            PSVECAdd(&v, &wanwan->unk038, &v);
            if (fn_1_4030(stage, &v, 50.0f, &push, 0, &itemNo, &hitNo) == 0) {
                dirNo[num] = i;
                cand[num] = v;
                num++;
            }
        }
        dist += 100.0f;
        if (tries++ > 4) {
            break;
        }
    }
    if (num == 0) {
        return 0;
    }
    best = 0.0f;
    bestNo = 0;
    for (i = 0; i < num; i++) {
        PSVECSubtract(&cand[i], &wanwan->unk038, &v);
        PSVECNormalize(&v, &v);
        if (wanwan->unk004 != 2) {
            face.x = sin(M_PI * wanwan->unk044.y / 180.0);
            face.y = 0.0f;
            face.z = cos(M_PI * wanwan->unk044.y / 180.0);
        } else {
            PSVECSubtract(&wanwan->unk038, &player->unk060, &face);
            face.y = 0.0f;
            PSVECNormalize(&face, &face);
        }
        dot = PSVECDotProduct(&v, &face);
        rad = acos(dot);
        angle = 180.0 * (rad / M_PI);
        if (angle > best) {
            best = angle;
            bestNo = i;
        }
    }
    *out = cand[bestNo];
    return 1;
}
