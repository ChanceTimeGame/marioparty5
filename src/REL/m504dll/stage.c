/*
 * m504dll stage.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/stage.s.
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
#include "string.h"

/* retail passes the camera word unnarrowed (lwz, no extsh): no prototype in scope */
void Hu3D3Dto2D();

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x30 */ /* float lbl_1_rodata_30 = 0.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 1.0f; */
/* 0x38 */ /* s32 lbl_1_rodata_38[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x44 */ /* float lbl_1_rodata_44 = 96.0f; */
/* 0x48 */ /* float lbl_1_rodata_48 = 576.0f; */
/* 0x4C */ /* s32 lbl_1_rodata_4C[3] = { 0x3F800000, 0x00000000, 0x00000000 }; */
/* 0x58 */ /* s32 lbl_1_rodata_58[3] = { 0x00000000, 0x00000000, 0x3F800000 }; */
/* 0x64 */ /* s32 lbl_1_rodata_64[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x70 */ /* s32 lbl_1_rodata_70[3] = { 0xC3660000, 0x00000000, 0x00000000 }; */
/* 0x7C */ /* s32 lbl_1_rodata_7C[3] = { 0x43660000, 0x00000000, 0x00000000 }; */
/* 0x88 */ /* s32 lbl_1_rodata_88[3] = { 0x00000000, 0x00000000, 0x45674000 }; */
/* 0x94 */ /* s32 lbl_1_rodata_94[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xA0 */ /* s32 lbl_1_rodata_A0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xAC */ /* s32 lbl_1_rodata_AC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xB8 */ /* s32 lbl_1_rodata_B8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xC4 */ /* float lbl_1_rodata_C4 = -400.0f; */
/* 0xC8 */ /* float lbl_1_rodata_C8 = 400.0f; */
/* 0xCC */ /* float lbl_1_rodata_CC = 3550.0f; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = -230.0f; */
/* 0xD4 */ /* float lbl_1_rodata_D4 = 230.0f; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 250.0f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 4.0f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 30.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 10.0f; */

/* --- functions (reference order) --- */

#define M504_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m504, n), HU_MEMNUM_OVL, HEAP_MODEL)
#define M504_ABS(x) ((x) >= 0.0f ? (x) : -(x))

/* stage fn_1_23DC, 49 insns. Lane init: camera, stage, player, wanwan. */
void fn_1_23DC(M504_LANE *lane, s32 idx, M504_WORK *work)
{
    memset(lane, 0, sizeof(M504_LANE));
    lane->unk000 = work;
    lane->unk004 = idx;
    lane->unk46C = (idx & 1) ? 0 : 1;
    fn_1_C4F4(&lane->unk3BC, idx, lane);
    fn_1_255C(&lane->unk15C, idx, lane);
    fn_1_5934(&lane->unk008, idx, lane);
    lane->unk008.unk0C4 = 0;
    fn_1_9680(&lane->unk0DC, lane);
    lane->unk008.unk0C4 = 0;
}

/* stage fn_1_24A0, 22 insns. Lane close. */
void fn_1_24A0(M504_LANE *lane)
{
    fn_1_9C10(&lane->unk0DC);
    fn_1_5E1C(&lane->unk008);
    fn_1_3B9C(&lane->unk15C);
    fn_1_C71C(&lane->unk3BC);
    memset(lane, 0, sizeof(M504_LANE));
}

/* stage fn_1_24F8, 25 insns. Lane frame; returns the wanwan's result. */
s32 fn_1_24F8(M504_LANE *lane)
{
    s32 ret = 0;

    fn_1_5EC8(&lane->unk008);
    if (fn_1_9CAC(&lane->unk0DC)) {
        ret = 1;
    }
    fn_1_3D9C(&lane->unk15C);
    fn_1_C74C(&lane->unk3BC);
    return ret;
}

/* stage fn_1_255C, 1424 insns. Stage init: fourteen linked scenery models, the
   animated props, and the ten collision objects of lbl_1_data_A8. */
void fn_1_255C(M504_STAGE *stage, s32 idx, M504_LANE *lane)
{
    s16 *mdl;
    HU3DMODELID modelId;
    s32 i;
    M504_STAGEOBJ *obj;
    M504_STAGEOBJDATA *data;

    mdl = lane->unk000->unk012;
    memset(stage, 0, sizeof(M504_STAGE));
    stage->unk000 = lane;
    stage->unk004 = modelId = Hu3DModelLink(mdl[1]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk006 = modelId = Hu3DModelLink(mdl[2]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk008 = modelId = Hu3DModelLink(mdl[3]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk00C = modelId = Hu3DModelLink(mdl[9]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk00E = modelId = Hu3DModelLink(mdl[4]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk010 = modelId = Hu3DModelLink(mdl[5]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk012 = modelId = Hu3DModelLink(mdl[6]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk014 = modelId = Hu3DModelLink(mdl[10]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk016 = modelId = Hu3DModelLink(mdl[7]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk018 = modelId = Hu3DModelLink(mdl[8]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk01A = modelId = Hu3DModelLink(mdl[11]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk01C = modelId = Hu3DModelLink(mdl[12]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk01E = modelId = Hu3DModelLink(mdl[13]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk020 = modelId = Hu3DModelLink(mdl[14]);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk022 = modelId = Hu3DModelCreate(M504_DATA(0x16));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk024[0] = Hu3DJointMotion(modelId, M504_DATA(0x26));
    stage->unk024[1] = Hu3DJointMotion(modelId, M504_DATA(0x27));
    stage->unk024[2] = Hu3DJointMotion(modelId, M504_DATA(0x28));
    Hu3DMotionSet(modelId, stage->unk024[0]);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 3; i++) {
        stage->unk02E[i] = modelId = Hu3DModelCreate(M504_DATA(0x17));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    }
    stage->unk034[0] = Hu3DJointMotion(modelId, M504_DATA(0x29));
    stage->unk034[1] = Hu3DJointMotion(modelId, M504_DATA(0x2A));
    stage->unk034[2] = Hu3DJointMotion(modelId, M504_DATA(0x2B));
    stage->unk034[3] = Hu3DJointMotion(modelId, M504_DATA(0x2C));
    stage->unk034[4] = Hu3DJointMotion(modelId, M504_DATA(0x2D));
    stage->unk034[5] = Hu3DJointMotion(modelId, M504_DATA(0x2E));
    stage->unk034[6] = Hu3DJointMotion(modelId, M504_DATA(0x2F));
    Hu3DMotionSpeedSet(stage->unk02E[0], 1.0f);
    Hu3DMotionSpeedSet(stage->unk02E[1], 1.0f);
    Hu3DMotionSpeedSet(stage->unk02E[2], 1.0f);
    Hu3DMotionSet(stage->unk02E[0], stage->unk034[0]);
    Hu3DModelAttrSet(stage->unk02E[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(stage->unk02E[0], HU3D_ATTR_DISPOFF);
    stage->unk04A = modelId = Hu3DModelCreate(M504_DATA(0x18));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk052 = Hu3DJointMotion(modelId, M504_DATA(0x30));
    stage->unk04E = modelId = Hu3DModelCreate(M504_DATA(0x19));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk056 = Hu3DJointMotion(modelId, M504_DATA(0x31));
    stage->unk04C = modelId = Hu3DModelCreate(M504_DATA(0x1A));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk054 = Hu3DJointMotion(modelId, M504_DATA(0x32));
    stage->unk050 = modelId = Hu3DModelCreate(M504_DATA(0x1B));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk058 = Hu3DJointMotion(modelId, M504_DATA(0x33));
    stage->unk060 = modelId = Hu3DModelCreate(M504_DATA(0x13));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk066 = Hu3DJointMotion(modelId, M504_DATA(0x34));
    Hu3DMotionSet(stage->unk060, stage->unk066);
    Hu3DMotionTimeSet(stage->unk060, 0.0f);
    Hu3DMotionSpeedSet(stage->unk060, 1.0f);
    Hu3DModelAttrSet(stage->unk060, HU3D_MOTATTR_LOOP);
    stage->unk062 = modelId = Hu3DModelCreate(M504_DATA(0x14));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk068 = Hu3DJointMotion(modelId, M504_DATA(0x35));
    stage->unk064 = modelId = Hu3DModelCreate(M504_DATA(0x15));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    stage->unk06A = Hu3DJointMotion(modelId, M504_DATA(0x36));
    stage->unk05C = -1;
    stage->unk072 = modelId = Hu3DModelCreate(M504_DATA(0x1C));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    stage->unk074[0] = Hu3DJointMotion(modelId, M504_DATA(0x37));
    stage->unk074[1] = Hu3DJointMotion(modelId, M504_DATA(0x38));
    Hu3DMotionSet(modelId, stage->unk074[0]);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 10; i++) {
        obj = &stage->unk07C[i];
        data = &lbl_1_data_A8[i];
        memset(obj, 0, sizeof(M504_STAGEOBJ));
        obj->unk000 = stage;
        if (data->unk1C != 0 || data->unk00 == -1) {
            modelId = -1;
        } else {
            modelId = Hu3DModelLink(mdl[data->unk00]);
        }
        obj->unk004 = modelId;
        obj->unk010 = data->unk02;
        obj->unk014 = data->unk04;
        obj->unk020 = data->unk10;
        obj->unk008 = 0;
        obj->unk02C = data->unk1C;
        obj->unk00C = 1;
        if (data->unk1C == 0 && modelId != -1) {
            Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
            Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(modelId, lbl_1_data_45E0[idx]);
            Hu3DModelLayerSet(modelId, 0);
            Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        }
    }
}

/* stage fn_1_3B9C, 128 insns. Stage close. Retail kills only the first six
   object models (the init links ten; objects 6..9 have unk02C set in the data). */
void fn_1_3B9C(M504_STAGE *stage)
{
    s32 i;
    M504_STAGEOBJ *obj;

    for (i = 0; i < 2; i++) {
        Hu3DMotionKill(stage->unk074[i]);
    }
    Hu3DMotionKill(stage->unk06A);
    Hu3DMotionKill(stage->unk068);
    Hu3DMotionKill(stage->unk058);
    Hu3DMotionKill(stage->unk054);
    Hu3DMotionKill(stage->unk056);
    Hu3DMotionKill(stage->unk052);
    for (i = 0; i < 7; i++) {
        Hu3DMotionKill(stage->unk034[i]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(stage->unk024[i]);
    }
    for (i = 0; i < 6; i++) {
        obj = &stage->unk07C[i];
        if (obj->unk02C == 0 && obj->unk004 != -1) {
            Hu3DModelKill(obj->unk004);
        }
    }
    Hu3DModelKill(stage->unk072);
    Hu3DModelKill(stage->unk064);
    Hu3DModelKill(stage->unk062);
    Hu3DModelKill(stage->unk060);
    Hu3DModelKill(stage->unk050);
    Hu3DModelKill(stage->unk04C);
    Hu3DModelKill(stage->unk04E);
    Hu3DModelKill(stage->unk04A);
    for (i = 0; i < 3; i++) {
        Hu3DModelKill(stage->unk02E[i]);
    }
    Hu3DModelKill(stage->unk022);
    Hu3DModelKill(stage->unk020);
    Hu3DModelKill(stage->unk01E);
    Hu3DModelKill(stage->unk01C);
    Hu3DModelKill(stage->unk01A);
    Hu3DModelKill(stage->unk018);
    Hu3DModelKill(stage->unk016);
    Hu3DModelKill(stage->unk014);
    Hu3DModelKill(stage->unk012);
    Hu3DModelKill(stage->unk010);
    Hu3DModelKill(stage->unk00E);
    Hu3DModelKill(stage->unk00C);
    Hu3DModelKill(stage->unk008);
    Hu3DModelKill(stage->unk006);
    Hu3DModelKill(stage->unk004);
    memset(stage, 0, sizeof(M504_STAGE));
}

/* stage fn_1_3D9C, 140 insns. Stage frame: show an object's model while any
   corner of its box projects on screen, then run the props. */
void fn_1_3D9C(M504_STAGE *stage)
{
    HuVecF v68;
    HuVecF v5C;
    HuVecF v50;
    HuVecF v44;
    HuVecF v38;
    HuVecF v2C;
    HuVecF v20;
    HuVecF v14;
    M504_STAGEOBJ *obj;
    s32 i;
    M504_LANE *lane;
    M504_WORK *work;

    lane = stage->unk000;
    work = lane->unk000;
    for (i = 0; i < 6; i++) {
        obj = &stage->unk07C[i];
        if (obj->unk02C == 0) {
            {
                HuVecF t = { 0.0f, 0.0f, 0.0f };
                HuVecF *tp = &t;
                v68 = v5C = v50 = v44 = *tp;
            }
            v68.x = obj->unk014.x;
            v68.z = obj->unk014.z;
            v5C.x = obj->unk020.x;
            v5C.z = obj->unk014.z;
            v50.x = obj->unk014.x;
            v50.z = obj->unk020.z;
            v44.x = obj->unk020.x;
            v44.z = obj->unk020.z;
            Hu3D3Dto2D(&v68, stage->unk000->unk3BC.unk004, &v38);
            Hu3D3Dto2D(&v5C, stage->unk000->unk3BC.unk004, &v2C);
            Hu3D3Dto2D(&v50, stage->unk000->unk3BC.unk004, &v20);
            Hu3D3Dto2D(&v44, stage->unk000->unk3BC.unk004, &v14);
            if (work->unk1218 && i == 2) {
                obj->unk008 = 1;
                Hu3DModelAttrReset(obj->unk004, HU3D_ATTR_DISPOFF);
            } else if (fn_1_3FCC(&v38) || fn_1_3FCC(&v2C) || fn_1_3FCC(&v20) || fn_1_3FCC(&v14)) {
                if (!obj->unk008) {
                    obj->unk008 = 1;
                    Hu3DModelAttrReset(obj->unk004, HU3D_ATTR_DISPOFF);
                }
            } else if (obj->unk008) {
                obj->unk008 = 0;
                Hu3DModelAttrSet(obj->unk004, HU3D_ATTR_DISPOFF);
            }
        }
    }
    fn_1_4FA4(stage);
}

/* stage fn_1_3FCC, 25 insns. 1 when a projected point's y is within the screen
   plus a 96-pixel margin. */
s32 fn_1_3FCC(HuVecF *pos2d)
{
    float margin = 96.0f;

    if (pos2d->y < -margin || pos2d->y >= 576.0f + margin) {
        return 0;
    }
    return 1;
}

/* stage fn_1_4030, 989 insns. Collision of a circle (pos, radius) in the XZ plane
   against the course walls and the stage objects; out gets the push-out (x, z),
   hitIdx the object (< 6) touched, corner the box corner (0..3) rounded. */
s32 fn_1_4030(M504_STAGE *stage, HuVecF *pos, float radius, HuVecF *out, s32 flag, s16 *hitIdx, s16 *corner)
{
    HuVecF v;
    HuVecF p;
    HuVecF far;
    HuVecF axisX;
    HuVecF axisZ;
    HuVecF c0;
    HuVecF c1;
    HuVecF c2;
    HuVecF c3;
    HuVecF d0;
    HuVecF d1;
    HuVecF d2;
    HuVecF d3;
    HuVecF g;
    HuVecF e;
    float m2;
    float m3;
    float rad;
    float pen;
    float dxMin;
    float dxMax;
    float dzMin;
    float dzMax;
    float mag;
    float m0;
    float m1;
    float minX;
    float maxX;
    float minZ;
    float maxZ;
    float dx;
    float dz;
    M504_STAGEOBJ *obj;
    s32 i;
    s32 hit;

    {
        HuVecF t = { 1.0f, 0.0f, 0.0f };
        HuVecF *tp = &t;
        axisX = *tp;
    }
    {
        HuVecF t = { 0.0f, 0.0f, 1.0f };
        HuVecF *tp = &t;
        axisZ = *tp;
    }
    p = *pos;
    *hitIdx = -1;
    *corner = -1;
    hit = 0;
    {
        HuVecF t = { 0.0f, 0.0f, 0.0f };
        HuVecF *tp = &t;
        *out = *tp;
    }
    dx = dz = 0.0f;
    minX = -400.0f;
    maxX = 400.0f;
    if (p.x - radius < minX) {
        dx += minX - (p.x - radius);
        hit = 1;
    } else if (p.x + radius > maxX) {
        dx += maxX - (p.x + radius);
        hit = 1;
    }
    minZ = 0.0f;
    maxZ = 3550.0f;
    if (p.z - radius < minZ) {
        dz += minZ - (p.z - radius);
        hit = 1;
    } else if (p.z + radius > maxZ) {
        {
            HuVecF t = { -230.0f, 0.0f, 0.0f };
            HuVecF *tp;
            t.z = maxZ;
            tp = &t;
            c0 = *tp;
        }
        PSVECSubtract(&c0, &p, &d0);
        m0 = PSVECMag(&d0);
        {
            HuVecF t = { 230.0f, 0.0f, 0.0f };
            HuVecF *tp;
            t.z = maxZ;
            tp = &t;
            c1 = *tp;
        }
        PSVECSubtract(&c1, &p, &d1);
        m1 = PSVECMag(&d1);
        if (m0 < radius && p.x > c0.x) {
            PSVECNormalize(&d0, &v);
            PSVECScale(&v, &v, radius);
            PSVECSubtract(&v, &d0, &v);
            dx += -v.x;
            dz += -v.z;
            hit = 1;
        } else if (m1 < radius && p.x < c0.x) {
            PSVECNormalize(&d1, &v);
            PSVECScale(&v, &v, radius);
            PSVECSubtract(&v, &d1, &v);
            dx += -v.x;
            dz += -v.z;
            hit = 1;
        } else if (p.x - radius < -230.0f || p.x + radius > 230.0f) {
            if (p.z < maxZ) {
                dz += maxZ - (p.z + radius);
                hit = 1;
            } else if (p.z - radius < maxZ) {
                dz += maxZ - (p.z - radius);
                hit = 1;
            }
        }
        if (p.z > maxZ) {
            {
                HuVecF t = { 0.0f, 0.0f, 3700.0f };
                HuVecF *tp = &t;
                far = *tp;
            }
            PSVECSubtract(&far, &p, &v);
            mag = PSVECMag(&v);
            if (mag > 250.0f - radius) {
                PSVECNormalize(&v, &v);
                PSVECScale(&v, &v, mag - (250.0f - radius));
                dx += v.x;
                dz += v.z;
                hit = 1;
            }
        }
    }
    p.x += dx;
    p.z += dz;
    dx = dz = 0.0f;
    for (i = 0; i < 10; i++) {
        obj = &stage->unk07C[i];
        if (obj->unk00C == 0) {
            continue;
        }
        if (obj->unk02C != 0 && flag == 0) {
            continue;
        }
        if (obj->unk010 == 1) {
            rad = obj->unk020.x;
            PSVECSubtract(&obj->unk014, &p, &v);
            v.y = 0.0f;
            mag = PSVECMag(&v);
            if (mag < radius + rad) {
                pen = (radius + rad) - mag;
                PSVECNormalize(&v, &v);
                PSVECScale(&v, &e, radius - pen);
                PSVECAdd(&e, &p, &e);
                PSVECScale(&v, &g, -(rad - pen));
                PSVECAdd(&g, &obj->unk014, &g);
                dx += e.x - g.x;
                dz += e.z - g.z;
                hit = 1;
                if (i < 6) {
                    *hitIdx = i;
                }
            }
        } else {
            minX = obj->unk014.x;
            maxX = obj->unk020.x;
            minZ = obj->unk014.z;
            maxZ = obj->unk020.z;
            if (p.x - radius < maxX && p.x + radius > minX && p.z - radius < maxZ && p.z + radius > minZ) {
                {
                    HuVecF t = { 0.0f, 0.0f, 0.0f };
                    HuVecF *tp;
                    t.x = minX;
                    t.z = minZ;
                    tp = &t;
                    c0 = *tp;
                }
                PSVECSubtract(&c0, &p, &d0);
                m0 = PSVECMag(&d0);
                {
                    HuVecF t = { 0.0f, 0.0f, 0.0f };
                    HuVecF *tp;
                    t.x = maxX;
                    t.z = minZ;
                    tp = &t;
                    c1 = *tp;
                }
                PSVECSubtract(&c1, &p, &d1);
                m1 = PSVECMag(&d1);
                {
                    HuVecF t = { 0.0f, 0.0f, 0.0f };
                    HuVecF *tp;
                    t.x = minX;
                    t.z = maxZ;
                    tp = &t;
                    c2 = *tp;
                }
                PSVECSubtract(&c2, &p, &d2);
                m2 = PSVECMag(&d2);
                {
                    HuVecF t = { 0.0f, 0.0f, 0.0f };
                    HuVecF *tp;
                    t.x = maxX;
                    t.z = maxZ;
                    tp = &t;
                    c3 = *tp;
                }
                PSVECSubtract(&c3, &p, &d3);
                m3 = PSVECMag(&d3);
                if (m0 < radius && p.x < minX && p.z < minZ) {
                    PSVECNormalize(&d0, &v);
                    PSVECScale(&v, &v, radius - m0);
                    dx += -v.x;
                    dz += -v.z;
                    *corner = 0;
                    hit = 1;
                } else if (m1 < radius && p.x > maxX && p.z < minZ) {
                    PSVECNormalize(&d1, &v);
                    PSVECScale(&v, &v, radius - m1);
                    dx += -v.x;
                    dz += -v.z;
                    *corner = 1;
                    hit = 1;
                } else if (m2 < radius && p.x < minX && p.z > maxZ) {
                    PSVECNormalize(&d2, &v);
                    PSVECScale(&v, &v, radius - m2);
                    dx += -v.x;
                    dz += -v.z;
                    *corner = 2;
                    hit = 1;
                } else if (m3 < radius && p.x > maxX && p.z > maxZ) {
                    PSVECNormalize(&d3, &v);
                    PSVECScale(&v, &v, radius - m3);
                    dx += -v.x;
                    dz += -v.z;
                    *corner = 3;
                    hit = 1;
                } else if (p.x > minX && p.x < maxX && p.z < minZ) {
                    dz += minZ - (p.z + radius);
                    hit = 1;
                } else if (p.x > minX && p.x < maxX && p.z > maxZ) {
                    dz += maxZ - (p.z - radius);
                    hit = 1;
                } else if (p.z > minZ && p.z < maxZ && p.x < minX) {
                    dx += minX - (p.x + radius);
                    hit = 1;
                    *hitIdx = i;
                } else if (p.z > minZ && p.z < maxZ && p.x > maxX) {
                    dx += maxX - (p.x - radius);
                    hit = 1;
                } else if (flag == 0) {
                    dzMin = minZ - (p.z + radius);
                    dzMax = maxZ - (p.z - radius);
                    dxMin = minX - (p.x + radius);
                    dxMax = maxX - (p.x - radius);
                    if (M504_ABS(dxMin) < M504_ABS(dxMax) && M504_ABS(dxMin) < M504_ABS(dzMin) && M504_ABS(dxMin) < M504_ABS(dzMax)) {
                        dx += dxMin;
                    } else if (M504_ABS(dxMax) < M504_ABS(dxMin) && M504_ABS(dxMax) < M504_ABS(dzMin) && M504_ABS(dxMax) < M504_ABS(dzMax)) {
                        dx += dxMax;
                    } else if (M504_ABS(dzMin) < M504_ABS(dxMin) && M504_ABS(dzMin) < M504_ABS(dxMax) && M504_ABS(dzMin) < M504_ABS(dzMax)) {
                        dz += dzMin;
                    } else {
                        dz += dzMax;
                    }
                    hit = 1;
                }
                if (i < 6 && hit) {
                    *hitIdx = i;
                }
            }
        }
    }
    p.x += dx;
    p.z += dz;
    out->x = p.x - pos->x;
    out->z = p.z - pos->z;
    return hit;
}

/* stage fn_1_4FA4, 18 insns. The props. */
void fn_1_4FA4(M504_STAGE *stage)
{
    fn_1_4FEC(stage);
    fn_1_5168(stage);
    fn_1_53AC(stage);
    fn_1_572C(stage);
}

/* stage fn_1_4FEC, 95 insns. Prop unk022: trigger motion, then the after-loop for
   360 frames, then back to idle. */
void fn_1_4FEC(M504_STAGE *stage)
{
    M504_LANE *lane;
    M504_WORK *work;

    lane = stage->unk000;
    work = lane->unk000;
    switch (stage->unk02A) {
    case 0:
        break;
    case 1:
        Hu3DMotionShiftSet(stage->unk022, stage->unk024[2], 0.0f, 4.0f, 0);
        stage->unk02A++;
        if (work->unk1210) {
            if (lane->unk46C) {
                fn_1_5EC(0x653);
            } else {
                fn_1_5EC(0x654);
            }
        }
        break;
    case 2:
        if (Hu3DMotionShiftIDGet(stage->unk022) < 0) {
            Hu3DMotionShiftSet(stage->unk022, stage->unk024[1], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
            stage->unk02C = 360;
            stage->unk02A++;
        }
        break;
    case 3:
        if (stage->unk02C-- <= 0) {
            Hu3DMotionShiftSet(stage->unk022, stage->unk024[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            stage->unk02C = 0;
            stage->unk02A = 0;
        }
        break;
    }
}

/* stage fn_1_5168, 19 insns. */
void fn_1_5168(M504_STAGE *stage)
{
    fn_1_51B4(stage, 0);
    fn_1_51B4(stage, 1);
    fn_1_51B4(stage, 2);
}

/* stage fn_1_51B4, 126 insns. Prop unk02E[idx]: show and play motion A once,
   then loop motion B. */
void fn_1_51B4(M504_STAGE *stage, u16 idx)
{
    M504_LANE *lane;
    M504_WORK *work;
    s16 motA;
    s16 motB;
    float maxTime;

    lane = stage->unk000;
    work = lane->unk000;
    motA = (idx == 0) ? stage->unk034[1] : (idx == 1) ? stage->unk034[3] : stage->unk034[5];
    motB = (idx == 0) ? stage->unk034[2] : (idx == 1) ? stage->unk034[4] : stage->unk034[6];
    switch (stage->unk042[idx]) {
    case 0:
        break;
    case 1:
        Hu3DModelAttrReset(stage->unk02E[idx], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk02E[idx], HU3D_MOTATTR_LOOP);
        Hu3DMotionSet(stage->unk02E[idx], motA);
        stage->unk042[idx]++;
        if (work->unk1210) {
            if (lane->unk46C) {
                fn_1_5EC(0x651);
            } else {
                fn_1_5EC(0x652);
            }
        }
        break;
    case 2:
        maxTime = Hu3DMotionMaxTimeGet(stage->unk02E[idx]);
        if (Hu3DMotionTimeGet(stage->unk02E[idx]) >= maxTime) {
            Hu3DModelAttrSet(stage->unk02E[idx], HU3D_MOTATTR_LOOP);
            Hu3DMotionSet(stage->unk02E[idx], motB);
            stage->unk042[idx]++;
        }
        break;
    case 3:
        break;
    }
}

/* stage fn_1_53AC, 224 insns. Shape-motion props: unk062 then unk064 (state
   unk06C), and unk04A/04C then unk04E/050 (state unk06E). */
void fn_1_53AC(M504_STAGE *stage)
{
    M504_LANE *lane;
    M504_WORK *work;
    float time;
    float maxTime;

    lane = stage->unk000;
    work = lane->unk000;
    switch (stage->unk06C) {
    case 0:
        break;
    case 1:
        Hu3DMotionShapeSet(stage->unk062, stage->unk068);
        Hu3DMotionShapeTimeSet(stage->unk062, 0.0f);
        Hu3DMotionShapeSpeedSet(stage->unk062, 1.0f);
        Hu3DModelAttrReset(stage->unk062, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(stage->unk060, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk062, HU3D_ATTR_DISPOFF);
        if (work->unk1210) {
            if (lane->unk46C) {
                fn_1_5EC(0x657);
            } else {
                fn_1_5EC(0x658);
            }
        }
        stage->unk06C++;
        break;
    case 2:
        time = Hu3DData[stage->unk062].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk062);
        if (time >= maxTime) {
            Hu3DMotionShapeSet(stage->unk064, stage->unk06A);
            Hu3DMotionShapeTimeSet(stage->unk064, 0.0f);
            Hu3DMotionShapeSpeedSet(stage->unk064, 1.0f);
            Hu3DModelAttrSet(stage->unk064, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(stage->unk062, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(stage->unk064, HU3D_ATTR_DISPOFF);
            stage->unk06C++;
        }
        break;
    case 3:
        time = Hu3DData[stage->unk064].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk064);
        if (time >= maxTime) {
            Hu3DMotionShapeTimeSet(stage->unk064, 0.0f);
        }
        break;
    }
    switch (stage->unk06E) {
    case 0:
        break;
    case 1:
        Hu3DMotionShapeSet(stage->unk04A, stage->unk052);
        Hu3DMotionShapeSet(stage->unk04C, stage->unk054);
        Hu3DModelAttrReset(stage->unk04A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk04C, HU3D_ATTR_DISPOFF);
        stage->unk06E++;
        break;
    case 2:
        time = Hu3DData[stage->unk04A].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk04A);
        if (time >= maxTime) {
            Hu3DMotionShapeSet(stage->unk04E, stage->unk056);
            Hu3DMotionShapeSet(stage->unk050, stage->unk058);
            Hu3DModelAttrSet(stage->unk04A, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(stage->unk04C, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(stage->unk04E, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(stage->unk050, HU3D_ATTR_DISPOFF);
            stage->unk06E++;
        }
        break;
    case 3:
        time = Hu3DData[stage->unk04E].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk04E);
        if (time >= maxTime) {
            Hu3DMotionShapeTimeSet(stage->unk04E, 0.0f);
        }
        time = Hu3DData[stage->unk050].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk050);
        if (time >= maxTime) {
            Hu3DMotionShapeTimeSet(stage->unk050, 0.0f);
        }
        break;
    }
}

/* stage fn_1_572C, 81 insns. Prop unk072: play its shape motion once and
   disable collision object 1. */
void fn_1_572C(M504_STAGE *stage)
{
    M504_LANE *lane;
    M504_WORK *work;
    float time;
    float maxTime;

    lane = stage->unk000;
    work = lane->unk000;
    switch (stage->unk078) {
    case 0:
        break;
    case 1:
        Hu3DMotionShapeSet(stage->unk072, stage->unk074[1]);
        Hu3DMotionShapeSpeedSet(stage->unk072, 1.0f);
        Hu3DModelAttrReset(stage->unk072, HU3D_MOTATTR_LOOP);
        stage->unk07C[1].unk00C = 0;
        if (work->unk1210) {
            if (lane->unk46C) {
                fn_1_5EC(0x655);
            } else {
                fn_1_5EC(0x656);
            }
        }
        stage->unk078++;
        break;
    case 2:
        time = Hu3DData[stage->unk072].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(stage->unk072);
        if (time >= maxTime) {
            Hu3DModelAttrSet(stage->unk072, HU3D_ATTR_DISPOFF);
            stage->unk078++;
        }
        break;
    case 3:
        break;
    }
}

/* stage fn_1_5870, 49 insns. Trigger a prop from the object the wanwan hit
   (wanwan passes fn_1_4030's hitIdx). */
void fn_1_5870(M504_STAGE *stage, s16 kind)
{
    switch (kind) {
    case 1:
        if (stage->unk078 == 0) {
            stage->unk078 = 1;
        }
        break;
    case 3:
        if (stage->unk042[0] == 0) {
            stage->unk042[0] = 1;
        } else if (stage->unk042[1] == 0) {
            stage->unk042[1] = 1;
        } else if (stage->unk042[2] == 0) {
            stage->unk042[2] = 1;
        }
        break;
    case 4:
        stage->unk02A = 1;
        break;
    case 5:
        if (stage->unk06C == 0) {
            stage->unk06C = 1;
        }
        if (stage->unk06E == 0) {
            stage->unk06E = 1;
        }
        break;
    }
}
