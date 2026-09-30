/*
 * m510dll ending.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/ending.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = -300.0f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 300.0f; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 0.0f; */
/* 0x2FC */ /* float lbl_1_rodata_2FC = 10.0f; */
/* 0x300 */ /* float lbl_1_rodata_300 = 0.05f; */
/* 0x304 */ /* float lbl_1_rodata_304 = 4.0f; */
/* 0x308 */ /* float lbl_1_rodata_308 = 60.0f; */
/* 0x30C */ /* float lbl_1_rodata_30C = 1.0f; */
/* 0x310 */ /* float lbl_1_rodata_310 = 3.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 180.0f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 360.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = -180.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 0.9f; */
/* 0x324 */ /* float lbl_1_rodata_324 = 2.0f; */
/* 0x328 */ /* float lbl_1_rodata_328 = 400.0f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 0.02f; */
/* 0x330 */ /* float lbl_1_rodata_330 = 380.0f; */
/* 0x334 */ /* float lbl_1_rodata_334 = 200.0f; */
/* 0x338 */ /* float lbl_1_rodata_338 = 0.03f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 0.04f; */
/* 0x340 */ /* double lbl_1_rodata_340 = 4503601774854144; */
/* 0x348 */ /* float lbl_1_rodata_348 = 0.03125f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 10000.0f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 0.2f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 0.6f; */
/* 0x358 */ /* double lbl_1_rodata_358 = 4503599627370496; */
/* 0x360 */ /* float lbl_1_rodata_360 = 450.0f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 150.0f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 0.5f; */
/* 0x36C */ /* float lbl_1_rodata_36C = 1500.0f; */
/* 0x370 */ /* float lbl_1_rodata_370 = 3100.0f; */
/* 0x374 */ /* float lbl_1_rodata_374 = 90.0f; */
/* 0x378 */ /* double lbl_1_rodata_378 = 6; */
/* 0x380 */ /* double lbl_1_rodata_380 = 5; */
/* 0x388 */ /* double lbl_1_rodata_388 = 3.141592653589793; */
/* 0x390 */ /* double lbl_1_rodata_390 = 180; */
/* 0x398 */ /* double lbl_1_rodata_398 = 1.5; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 14.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 0.8f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 20.0f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = -20.0f; */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = 5.0f; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = 1.5f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = 2.5f; */
/* 0x3BC */ /* float lbl_1_rodata_3BC = 0.3f; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = 0.7f; */
/* 0x3C4 */ /* float lbl_1_rodata_3C4 = 30.0f; */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 7.0f; */
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 3; */
/* 0x3D8 */ /* double lbl_1_rodata_3D8 = 1; */
/* 0x3E0 */ /* float lbl_1_rodata_3E0[2] = { 1200.0f, 0.0f }; */

/* --- .data --- */
/* 0x450 */ HuVecF lbl_1_data_450 = { 0.0f, 2935.0f, 30070.0f };
/* 0x45C */ HuVecF lbl_1_data_45C = { 0.0f, 230.0f, 400.0f };
/* 0x468 */ HuVecF lbl_1_data_468 = { 0.0f, 0.0f, 0.0f };
/* 0x474 */ HuVecF lbl_1_data_474 = { 0.0f, 0.0f, 0.0f };
/* 0x480 */ s32 lbl_1_data_480[1] = { 0x00000001 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7824 */ M510_ENDING lbl_1_bss_7824;
/* 0x7822 gap_05_00007822_bss (0x2) -- dtk filler */
/* 0x7820 */ s16 lbl_1_bss_7820;

/* --- functions (reference order) --- */
#define M510_ANGLE_WRAP(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))

/* fn_1_9B0C, ending.c, 594 insns. Builds the ending scene models. */
void fn_1_9B0C(M510_WORK *work)
{
    M510_CAMERA *camera = &work->unk2474;
    HU3DMODELID modelId;
    s32 i;
    M510_ENDPIECE *piece;
    M510_ENDOBJ *obj;

    memset(&lbl_1_bss_7824, 0, sizeof(M510_ENDING));
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 8), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk004 = modelId;
    Hu3DModelPosSet(modelId, -300.0f, 300.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 10.0f, 10.0f, 10.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    lbl_1_bss_7824.unk014 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x19), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, lbl_1_bss_7824.unk014);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    lbl_1_bss_7824.unk006 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 9), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk008 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 10), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk00A = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 11), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk00C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 12), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_7824.unk006, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk008, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk00A, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk00C, HU3D_ATTR_DISPOFF);
    lbl_1_bss_7824.unk016 = Hu3DJointMotion(lbl_1_bss_7824.unk006, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_7824.unk006, lbl_1_bss_7824.unk016);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk006, HU3D_MOTATTR_LOOP);
    lbl_1_bss_7824.unk018 = Hu3DJointMotion(lbl_1_bss_7824.unk008, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x1B), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_7824.unk008, lbl_1_bss_7824.unk018);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk008, HU3D_MOTATTR_LOOP);
    lbl_1_bss_7824.unk01A = Hu3DJointMotion(lbl_1_bss_7824.unk00A, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x1C), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_7824.unk00A, lbl_1_bss_7824.unk01A);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk00A, HU3D_MOTATTR_LOOP);
    lbl_1_bss_7824.unk01C = Hu3DJointMotion(lbl_1_bss_7824.unk00C, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x1D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_7824.unk00C, lbl_1_bss_7824.unk01C);
    Hu3DModelAttrSet(lbl_1_bss_7824.unk00C, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 16; i++) {
        obj = &lbl_1_bss_7824.unk020[i];
        memset(obj, 0, sizeof(M510_ENDOBJ));
        modelId = Hu3DModelLink(lbl_1_bss_7824.unk004);
        obj->unk00A = modelId;
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(modelId, 10.0f, 10.0f, 10.0f);
        Hu3DModelCameraSet(modelId, camera->unk004);
        Hu3DModelLayerSet(modelId, 4);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        obj->unk008 = i;
    }
    for (i = 0; i < 64; i++) {
        piece = &lbl_1_bss_7824.unk1A0[i];
        memset(piece, 0, sizeof(M510_ENDPIECE));
        if (i % 4 == 0) {
            modelId = Hu3DModelLink(lbl_1_bss_7824.unk006);
            piece->unk00A = modelId;
        } else if (i % 4 == 1) {
            modelId = Hu3DModelLink(lbl_1_bss_7824.unk008);
            piece->unk00A = modelId;
        } else if (i % 4 == 2) {
            modelId = Hu3DModelLink(lbl_1_bss_7824.unk00A);
            piece->unk00A = modelId;
        } else {
            modelId = Hu3DModelLink(lbl_1_bss_7824.unk00C);
            piece->unk00A = modelId;
        }
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(modelId, 10.0f, 10.0f, 10.0f);
        Hu3DModelCameraSet(modelId, camera->unk004);
        Hu3DModelLayerSet(modelId, 4);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        piece->unk008 = i;
    }
    lbl_1_data_480[0] = 1;
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 15), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk00E = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 16), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk010 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 17), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_7824.unk012 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    lbl_1_bss_7824.unk9A8 = lbl_1_bss_7824.unk9AC = 0.0f;
    lbl_1_bss_7824.unk9B0 = lbl_1_bss_7824.unk9B4 = 0.0f;
    lbl_1_bss_7824.unk9B8 = lbl_1_bss_7824.unk9BC = 0.0f;
    lbl_1_bss_7824.unk9A4 = 0;
    lbl_1_bss_7820 = 0;
}

/* fn_1_A454, ending.c, 40 insns. Frees the ending scene. */
void fn_1_A454(M510_WORK *work)
{
    Hu3DModelKill(lbl_1_bss_7824.unk012);
    Hu3DModelKill(lbl_1_bss_7824.unk010);
    Hu3DModelKill(lbl_1_bss_7824.unk00E);
    Hu3DModelKill(lbl_1_bss_7824.unk006);
    Hu3DModelKill(lbl_1_bss_7824.unk004);
    Hu3DMotionKill(lbl_1_bss_7824.unk016);
    Hu3DMotionKill(lbl_1_bss_7824.unk014);
    memset(&lbl_1_bss_7824, 0, sizeof(M510_ENDING));
}

/* fn_1_A4F4, ending.c, 919 insns. Ending sequence; returns 1 when done. */
s32 fn_1_A4F4(M510_WORK *work)
{
    M510_CAMERA *camera = &work->unk2474;
    M510_STAGE *stage = &work->unk221C;
    s32 done = 0;
    s32 i;
    s32 settled;
    s32 winNum;
    M510_PLAYER *player;
    M510_PLAYERMODEL *pm;
    M510_STAGEOBJ *stageObj;
    MtxPtr mtx;
    float t;
    float rotY;
    s32 winner[4];

    switch (work->unk00E) {
    case 0:
        lbl_1_data_468 = camera->unk00C;
        lbl_1_data_474 = camera->unk024;
        camera->unk00C = lbl_1_data_450;
        camera->unk00C.x = lbl_1_data_468.x;
        camera->unk024 = lbl_1_data_45C;
        camera->unk024.x = lbl_1_data_474.x;
        camera->unk060 = 0.05f;
        for (i = 0; i < 4; i++) {
            player = &work->unk01C[i];
            pm = &player->unk008;
            Hu3DModelHookReset(pm->unk018);
            mtx = Hu3DData[pm->unk0D8].mtx;
            Hu3DModelObjMtxGet(pm->unk018, CharModelItemHookGet(pm->unk00C, 1, 1), mtx);
            Hu3DModelObjPosGet(pm->unk018, CharModelItemHookGet(pm->unk00C, 1, 1), &pm->unk0F0);
            mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;
            Hu3DModelPosSet(pm->unk0D8, pm->unk0F0.x, pm->unk0F0.y, pm->unk0F0.z);
            Hu3DMotionShiftSet(pm->unk018, pm->unk014->mtnId[1], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            pm->unk004 = 0;
        }
        work->unk014 = 0;
        work->unk00E = 1;
        break;
    case 1:
        settled = 1;
        t = work->unk014 / 60.0f;
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
        for (i = 0; i < 4; i++) {
            player = &work->unk01C[i];
            pm = &player->unk008;
            if (((pm->unk0C4.y >= 0.0f) ? pm->unk0C4.y : -pm->unk0C4.y) > 3.0f) {
                pm->unk0C4.y = M510_ANGLE_WRAP(fn_1_2840(0.0f, M510_ANGLE_WRAP(pm->unk0C4.y), 0.9f));
                omSetRot(pm->unk014, 0.0f, pm->unk0C4.y, 0.0f);
                settled = 0;
            } else if (pm->unk004 == 0) {
                Hu3DMotionShiftSet(pm->unk018, pm->unk014->mtnId[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                pm->unk004 = 1;
                settled = 0;
            }
            mtx = Hu3DData[pm->unk0D8].mtx;
            Hu3DModelRotSet(pm->unk0D8, 2.0f * (360.0f * t), 0.0f, 0.0f);
            Hu3DModelPosSet(pm->unk0D8, pm->unk0F0.x, pm->unk0F0.y + 400.0f * t, pm->unk0F0.z - 300.0f * t);
            Hu3DModelScaleSet(pm->unk0D8, 1.0f - t, 1.0f - t, 1.0f - t);
        }
        work->unk014++;
        if (settled && work->unk014 > 60) {
            for (i = 0; i < 4; i++) {
                player = &work->unk01C[i];
                pm = &player->unk008;
                Hu3DModelAttrSet(pm->unk0D8, HU3D_ATTR_DISPOFF);
            }
            work->unk014 = 0;
            work->unk00E = 2;
        }
        break;
    case 2:
        if (fn_1_B350(work)) {
            work->unk2530 = GameMesRecordCreate(work->unk252C);
            work->unk014 = 0;
            work->unk00E = 3;
            fn_1_75C(0x86);
            if (lbl_1_bss_0->unk2534 == 0) {
                work->unk24E0.unk024 = work->unk252C;
                work->unk24E0.unk020 = 1;
            }
        } else {
            work->unk014 = 0;
            work->unk00E = 5;
        }
        break;
    case 3:
        if (work->unk2530 >= 0 && GameMesStatGet(work->unk2530) == 0) {
            work->unk2530 = -1;
            work->unk014 = 0;
            work->unk00E = 4;
        }
        break;
    case 4:
        if (work->unk014++ > 30) {
            work->unk014 = 0;
            work->unk00E = 5;
        }
        break;
    case 5:
        winNum = 0;
        winner[0] = winner[1] = winner[2] = winner[3] = -1;
        for (i = 0; i < 4; i++) {
            player = &work->unk01C[i];
            pm = &player->unk008;
            if (pm->unk104 != 0) {
                Hu3DMotionShiftSet(pm->unk018, pm->unk014->mtnId[5], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
                winner[winNum] = pm->unk00C;
                GWMgCoinBonusSet(pm->unk008, 10);
                winNum++;
            } else {
                Hu3DMotionShiftSet(pm->unk018, pm->unk014->mtnId[6], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
            }
        }
        if (winNum != 0) {
            work->unk2530 = GameMesMgWinnerCreate(winner[0], winner[1], winner[2], winner[3]);
            lbl_1_bss_7824.unk9A0 = 1;
            fn_1_5B4(0x69F);
            fn_1_5B4(0x398);
            for (i = 0; i < 16; i++) {
                stageObj = &stage->unk010[i];
                Hu3DModelAttrSet(stageObj->unk00A, HU3D_MOTATTR_LOOP);
                Hu3DMotionSet(stageObj->unk00A, stageObj->unk00E);
            }
            if (work->unk2538 < 0) {
                work->unk2538 = fn_1_75C(0x79);
            }
        } else {
            work->unk2530 = GameMesMgDrawCreate();
            if (work->unk2538 < 0) {
                work->unk2538 = fn_1_75C(0x7B);
            }
            CharLoseVoicePlay(work->unk01C[0].unk008.unk00C, work->unk01C[1].unk008.unk00C, work->unk01C[2].unk008.unk00C,
                work->unk01C[3].unk008.unk00C);
        }
        work->unk014 = 0;
        work->unk00E = 6;
        break;
    case 6:
        if (++work->unk014 >= 209) {
            work->unk2530 = -1;
            work->unk014 = 0;
            work->unk00E = 7;
        }
        break;
    case 7:
        done = 1;
        break;
    }
    if (work->unk00E >= 5 && lbl_1_bss_7824.unk9A4 >= 30) {
        if (lbl_1_bss_7824.unk9A8 <= 0.0f) {
            Hu3DModelAttrReset(lbl_1_bss_7824.unk00E, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_7824.unk010, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_7824.unk012, HU3D_ATTR_DISPOFF);
        }
        if (++lbl_1_bss_7820 == 60) {
            fn_1_5B4(0x6A0);
        }
        lbl_1_bss_7824.unk9AC += 0.02f;
        lbl_1_bss_7824.unk9A8 += lbl_1_bss_7824.unk9AC;
        Hu3DModelPosSet(lbl_1_bss_7824.unk00E, 380.0f, lbl_1_bss_7824.unk9A8 - 200.0f, 0.0f);
        lbl_1_bss_7824.unk9B4 += 0.03f;
        lbl_1_bss_7824.unk9B0 += lbl_1_bss_7824.unk9B4;
        Hu3DModelPosSet(lbl_1_bss_7824.unk010, 380.0f, lbl_1_bss_7824.unk9B0 - 200.0f, 0.0f);
        lbl_1_bss_7824.unk9BC += 0.04f;
        lbl_1_bss_7824.unk9B8 += lbl_1_bss_7824.unk9BC;
        Hu3DModelPosSet(lbl_1_bss_7824.unk012, 380.0f, lbl_1_bss_7824.unk9B8 - 200.0f, 0.0f);
    }
    if (lbl_1_bss_7824.unk9A0 != 0) {
        fn_1_B4A4(work);
        lbl_1_bss_7824.unk000++;
    }
    return done;
}

/* 85 insns */
/* .data after fn_1_A4F4: defining these above it moves the switch table (fork I) */
/* 0x4A4 */ HuVecF lbl_1_data_4A4 = { 385.0f, 130.0f, -940.0f };
/* 0x4B0 */ HuVecF lbl_1_data_4B0 = { 670.0f, 185.0f, -860.0f };
/* 0x4BC */ HuVecF lbl_1_data_4BC = { 360.0f, 40.0f, -850.0f };
/* 0x4C8 */ HuVecF lbl_1_data_4C8 = { 635.0f, 65.0f, -720.0f };

s32 fn_1_B350(M510_WORK *work)
{
    M510_PLAYER *player;
    M510_PLAYERMODEL *pm;
    M510_SCORE *score;
    M510_PADAI *com;
    s32 result;
    s32 human;
    s32 best;
    s32 i;

    result = 0;
    best = 0;
    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        pm = &player->unk008;
        score = &player->unk850;
        if (best < score->unk024) {
            best = score->unk024;
        }
        pm->unk104 = 0;
    }
    human = 0;
    for (i = 0; i < 4; i++) {
        player = &work->unk01C[i];
        pm = &player->unk008;
        score = &player->unk850;
        com = &pm->unk02C.unk004;
        if (best == score->unk024 && best > 0) {
            pm->unk104 = 1;
            if (com->unk008 == 0) {
                human = 1;
            }
        }
    }
    if (best > work->unk252C) {
        work->unk252C = best;
        if (human) {
            if (_CheckFlag(FLAG_MG_PRACTICE)) {
                work->unk24E0.unk024 = work->unk252C;
                work->unk24E0.unk020 = 1;
                result = 0;
            }
            else {
                if (lbl_1_bss_0->unk2534 == 0) {
                    GWMgRecordSet(1, work->unk252C);
                }
                result = 1;
            }
        }
    }
    lbl_1_bss_7824.unk9A4 = best;
    return result;
}

/* 276 insns */
void fn_1_B4A4(M510_WORK *work)
{
    HuVecF pos;
    HuVecF from;
    HuVecF to;
    HuVecF mid;
    float t;
    s32 i;
    M510_ENDOBJ *fall;
    M510_ENDPIECE *rise;

    if (lbl_1_bss_7824.unk000 % 30 == 0) {
        fn_1_B8F4(work);
        fn_1_B8F4(work);
    }
    if (lbl_1_data_480[0]) {
        lbl_1_data_480[0] = 0;
        for (i = 0; i < 32; i++) {
            t = 0.03125f * i;
            PSVECSubtract(&lbl_1_data_4B0, &lbl_1_data_4A4, &from);
            PSVECScale(&from, &from, t);
            PSVECAdd(&from, &lbl_1_data_4A4, &from);
            PSVECSubtract(&lbl_1_data_4C8, &lbl_1_data_4BC, &to);
            PSVECScale(&to, &to, t);
            PSVECAdd(&to, &lbl_1_data_4BC, &to);
            t = (frand() % 10000) / 10000.0f;
            t = 0.2f + 0.6f * t;
            PSVECSubtract(&to, &from, &mid);
            PSVECScale(&mid, &mid, t);
            PSVECAdd(&mid, &from, &mid);
            pos = mid;
            pos.x = 380.0f + mid.x;
            fn_1_BE48(work, &pos);
        }
        for (i = 0; i < 32; i++) {
            t = 0.03125f * i;
            PSVECSubtract(&lbl_1_data_4B0, &lbl_1_data_4A4, &from);
            PSVECScale(&from, &from, t);
            PSVECAdd(&from, &lbl_1_data_4A4, &from);
            PSVECSubtract(&lbl_1_data_4C8, &lbl_1_data_4BC, &to);
            PSVECScale(&to, &to, t);
            PSVECAdd(&to, &lbl_1_data_4BC, &to);
            t = (frand() % 10000) / 10000.0f;
            t = 0.2f + 0.6f * t;
            PSVECSubtract(&to, &from, &mid);
            PSVECScale(&mid, &mid, t);
            PSVECAdd(&mid, &from, &mid);
            pos = mid;
            pos.x = 380.0f + -mid.x;
            fn_1_BE48(work, &pos);
        }
    }
    for (i = 0; i < 16; i++) {
        fall = &lbl_1_bss_7824.unk020[i];
        fn_1_B958(fall);
    }
    for (i = 0; i < 64; i++) {
        rise = &lbl_1_bss_7824.unk1A0[i];
        fn_1_BEC4(rise);
    }
}

/* 25 insns */
void fn_1_B8F4(M510_WORK *work)
{
    M510_ENDOBJ *fall;
    s32 i;

    for (i = 0; i < 16; i++) {
        fall = &lbl_1_bss_7824.unk020[i];
        if (!fall->unk004) {
            fall->unk000 = 0;
            fall->unk004 = 1;
            break;
        }
    }
}

/* 316 insns */
void fn_1_B958(M510_ENDOBJ *fall)
{
    float t;
    float scale;

    if (!fall->unk004) {
        return;
    }
    switch (fall->unk000) {
        case 0:
            fall->unk00C.x = 380.0f + 450.0f * ((fall->unk008 % 3) - 1.0f);
            fall->unk00C.x += 150.0f * ((frand() % 10000) / 10000.0f - 0.5f);
            fall->unk00C.y = 1500.0f;
            fall->unk00C.z = 3100.0f + ((fall->unk008 & 1) ? 300.0f : -300.0f);
            Hu3DModelRotSet(fall->unk00A, 0.0f, (fall->unk008 & 1) ? 0.0f : 180.0f, 0.0f);
            Hu3DModelScaleSet(fall->unk00A, 0.2f, 0.2f, 0.2f);
            Hu3DModelAttrReset(fall->unk00A, HU3D_ATTR_DISPOFF);
            fall->unk002 = 0;
            fall->unk000++;
            break;
        case 1:
            t = ((lbl_1_bss_7824.unk000 + (fall->unk008 % 4) * 30) % 90) / 90.0f;
            fall->unk00C.y -= 6.0 + 5.0 * HuSin(180.0f * t);
            fall->unk00C.x += 1.5 * HuSin(360.0f * t);
            t = fall->unk002 / 180.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            scale = 14.0f * (0.2f + 0.8f * t);
            Hu3DModelScaleSet(fall->unk00A, scale, scale, scale);
            fall->unk002++;
            if (fall->unk00C.y < -300.0f) {
                Hu3DModelAttrSet(fall->unk00A, HU3D_ATTR_DISPOFF);
                fall->unk004 = 0;
                fall->unk000 = 0;
            }
            break;
    }
    Hu3DModelPosSet(fall->unk00A, fall->unk00C.x, fall->unk00C.y, fall->unk00C.z);
}

/* 31 insns */
void fn_1_BE48(M510_WORK *work, HuVecF *pos)
{
    M510_ENDPIECE *rise;
    s32 i;

    for (i = 0; i < 64; i++) {
        rise = &lbl_1_bss_7824.unk1A0[i];
        if (!rise->unk004) {
            rise->unk000 = 0;
            rise->unk004 = 1;
            rise->unk00C = *pos;
            break;
        }
    }
}

/* 435 insns */
void fn_1_BEC4(M510_ENDPIECE *rise)
{
    float t;
    float scale;
    s32 r;

    if (!rise->unk004) {
        return;
    }
    switch (rise->unk000) {
        case 0:
            t = (frand() % 10000) / 10000.0f;
            rise->unk018 = 90.0f * (t - 0.5f);
            rise->unk018 += (rise->unk00C.x < 380.0f) ? 20.0f : -20.0f;
            Hu3DModelRotSet(rise->unk00A, 0.0f, rise->unk018 - 90.0f, 0.0f);
            Hu3DModelScaleSet(rise->unk00A, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(rise->unk00A, HU3D_ATTR_DISPOFF);
            rise->unk01C = 5.0f + 5.0f * ((frand() % 10000) / 10000.0f);
            r = frand() % 10000;
            if (r < 3000) {
                t = (frand() % 10000) / 10000.0f;
                Hu3DMotionSpeedSet(rise->unk00A, 1.5f + 2.5f * t);
            }
            else {
                t = (frand() % 10000) / 10000.0f;
                Hu3DMotionSpeedSet(rise->unk00A, 0.3f + 0.7f * t);
            }
            rise->unk002 = 0;
            rise->unk000++;
            break;
        case 1:
            t = rise->unk002 / 30.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            scale = 7.0f + (rise->unk008 % 5);
            scale *= 0.2f + 0.8f * t;
            Hu3DModelScaleSet(rise->unk00A, scale, scale, scale);
            rise->unk00C.x += t * (rise->unk01C * HuSin(rise->unk018));
            rise->unk00C.z += 3.0 + t * (rise->unk01C * HuCos(rise->unk018));
            t = rise->unk002 / 90.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            rise->unk00C.y += 1.0 + (4.0f + 2.0f * (rise->unk008 % 3)) * HuSin(90.0f * t);
            rise->unk002++;
            if (rise->unk00C.y > 1200.0f) {
                Hu3DModelAttrSet(rise->unk00A, HU3D_ATTR_DISPOFF);
                rise->unk004 = 0;
                rise->unk000 = 0;
            }
            break;
    }
    Hu3DModelPosSet(rise->unk00A, rise->unk00C.x, rise->unk00C.y, rise->unk00C.z);
}

