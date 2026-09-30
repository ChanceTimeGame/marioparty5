/*
 * m510dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/stage.s.
 */

#include "REL/m510dll.h"

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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x60 */ /* s32 lbl_1_rodata_60[3] = { 0x43D20000, 0x433E0000, 0xC4638000 }; */
/* 0x6C */ /* s32 lbl_1_rodata_6C[3] = { 0x43AA0000, 0x433E0000, 0xC4638000 }; */
/* 0x78 */ /* float lbl_1_rodata_78 = 0.0f; */
/* 0x7C */ /* float lbl_1_rodata_7C = 380.0f; */
/* 0x80 */ /* float lbl_1_rodata_80 = 4.0f; */
/* 0x84 */ /* float lbl_1_rodata_84 = 2.0f; */
/* 0x88 */ /* float lbl_1_rodata_88 = 576.0f; */
/* 0x8C */ /* float lbl_1_rodata_8C = 0.5f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 64.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 16.0f; */

/* --- .data --- */
/* 0x60 */ HuVecF lbl_1_data_60[11] = {   /* spectator offsets; x is added to 380 (mirrored for the right stand) */
    { 385.0f, 60.0f, -850.0f },
    { 470.0f, 70.0f, -815.0f },
    { 560.0f, 80.0f, -780.0f },
    { 630.0f, 88.0f, -745.0f },
    { 450.0f, 90.0f, -865.0f },
    { 545.0f, 105.0f, -830.0f },
    { 610.0f, 115.0f, -810.0f },
    { 420.0f, 105.0f, -905.0f },
    { 500.0f, 125.0f, -890.0f },
    { 590.0f, 145.0f, -865.0f },
    { 660.0f, 160.0f, -840.0f },
};
/* 0xE4 */ float lbl_1_data_E4[11] = { 0.65f, 0.7f, 0.7f, 0.75f, 0.6f, 0.65f, 0.7f, 0.55f, 0.6f, 0.6f, 0.55f };  /* spectator scale */

/* --- functions (reference order) --- */
/* stage.c fn_1_295C, 396 insns. Stage init: three stage models, sixteen shuffled spectators, the two scoreboard digits. */
void fn_1_295C(M510_STAGE *stage, M510_WORK *work)
{
    HuVecF pos;
    s16 order[11];
    s32 i;
    s32 j;
    HU3DMODELID modelId;
    M510_WORK *w;
    M510_CAMERA *camera;
    M510_STAGEOBJ *obj;
    s16 a;
    s16 b;
    s16 t;

    w = work;
    camera = &w->unk2474;
    memset(stage, 0, sizeof(M510_STAGE));
    stage->unk000 = work;
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    stage->unk008 = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapSet(modelId);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x07), HU_MEMNUM_OVL, HEAP_MODEL));
    stage->unk00A = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(modelId, 380.0f, 0.0f, 0.0f);
    Hu3DModelShadowMapSet(modelId);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x05), HU_MEMNUM_OVL, HEAP_MODEL));
    stage->unk00C = modelId;
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(modelId, 380.0f, 0.0f, 0.0f);
    stage->unk00E = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, stage->unk00E);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 11; i++) {
        order[i] = i;
    }
    for (i = 0; i < 50; i++) {
        a = i % 11;
        b = frand() % 11;
        t = order[a];
        order[a] = order[b];
        order[b] = t;
    }
    for (i = 0, j = 0; i < 8; j++, i++) {
        obj = &stage->unk010[i];
        pos.x = 380.0f + lbl_1_data_60[order[j]].x;
        pos.y = lbl_1_data_60[order[j]].y;
        pos.z = lbl_1_data_60[order[j]].z;
        fn_1_30D8(obj, i % 3, &pos, lbl_1_data_E4[order[j]], stage);
    }
    for (j = 10; i < 16; j--, i++) {
        obj = &stage->unk010[i];
        pos.x = 380.0f + -lbl_1_data_60[order[j]].x;
        pos.y = lbl_1_data_60[order[j]].y;
        pos.z = lbl_1_data_60[order[j]].z;
        fn_1_30D8(obj, i % 3, &pos, lbl_1_data_E4[order[j]], stage);
    }
    {
        HuVecF p = { 420.0f, 190.0f, -910.0f };
        HuVecF *pp = &p;
        pos = *pp;
        fn_1_3598(&stage->unk210, w->unk2508 % 10, &pos, stage);
    }
    {
        HuVecF p = { 340.0f, 190.0f, -910.0f };
        HuVecF *pp = &p;
        pos = *pp;
        fn_1_3598(&stage->unk234, w->unk2508 / 10, &pos, stage);
    }
}

/* stage.c fn_1_2F8C, 37 insns. Stage close. Retail kills only the first three spectators. */
void fn_1_2F8C(M510_STAGE *stage)
{
    s32 i;

    fn_1_3834(&stage->unk234);
    fn_1_3834(&stage->unk210);
    for (i = 0; i < 3; i++) {
        fn_1_33C0(&stage->unk010[i]);
    }
    Hu3DMotionKill(stage->unk00E);
    Hu3DModelKill(stage->unk00C);
    Hu3DModelKill(stage->unk00A);
    Hu3DModelKill(stage->unk008);
    memset(stage, 0, sizeof(M510_STAGE));
}

/* stage.c fn_1_3020, 46 insns. Stage frame: spectators, then the scoreboard follows work->unk2508. */
void fn_1_3020(M510_STAGE *stage)
{
    s32 score;
    M510_WORK *work;
    s32 i;
    M510_STAGEOBJ *obj;

    work = stage->unk000;
    for (i = 0; i < 16; i++) {
        obj = &stage->unk010[i];
        fn_1_3418(obj);
    }
    score = work->unk2508;
    stage->unk234.unk020 = score / 10;
    stage->unk210.unk020 = score % 10;
    fn_1_38A0(&stage->unk210);
    fn_1_38A0(&stage->unk234);
}

/* stage.c fn_1_30D8, 186 insns. Spectator init: one of three kinds, idle motion looping. */
void fn_1_30D8(M510_STAGEOBJ *obj, u16 kind, HuVecF *pos, float scale, M510_STAGE *stage)
{
    M510_STAGE *s;
    M510_WORK *work;
    M510_CAMERA *camera;
    HU3DMODELID modelId;

    s = stage;
    work = s->unk000;
    camera = &work->unk2474;
    memset(obj, 0, sizeof(M510_STAGEOBJ));
    obj->unk000 = stage;
    obj->unk008 = kind;
    obj->unk014 = *pos;
    if (kind == 0) {
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x12), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00A = modelId;
        obj->unk00C = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x20), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00E = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x21), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk010 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x22), HU_MEMNUM_OVL, HEAP_MODEL));
    } else if (kind == 1) {
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x13), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00A = modelId;
        obj->unk00C = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x23), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00E = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x24), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk010 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x25), HU_MEMNUM_OVL, HEAP_MODEL));
    } else {
        modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x14), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00A = modelId;
        obj->unk00C = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x26), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk00E = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x27), HU_MEMNUM_OVL, HEAP_MODEL));
        obj->unk010 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x28), HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, scale, scale, scale);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(modelId, pos->x, pos->y, pos->z);
    Hu3DMotionSet(modelId, obj->unk00C);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
}

/* stage.c fn_1_33C0, 22 insns. Spectator close. */
void fn_1_33C0(M510_STAGEOBJ *obj)
{
    Hu3DMotionKill(obj->unk010);
    Hu3DMotionKill(obj->unk00E);
    Hu3DMotionKill(obj->unk00C);
    Hu3DModelKill(obj->unk00A);
    memset(obj, 0, sizeof(M510_STAGEOBJ));
}

/* stage.c fn_1_3418, 96 insns. Spectator frame: state 1 starts a panned cheer, state 2 returns to idle after 60 frames. */
void fn_1_3418(M510_STAGEOBJ *obj)
{
    HuVecF pos2d;
    float pan;
    s32 seNo;

    switch (obj->unk004) {
    case 0:
        break;
    case 1:
        Hu3DMotionShiftSet(obj->unk00A, obj->unk010, 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
        obj->unk006 = 0;
        obj->unk004++;
        Hu3D3Dto2D(&obj->unk014, 1, &pos2d);
        pan = 2.0f * (pos2d.x / 576.0f - 0.5f);
        pan = 64.0f + 16.0f * pan;
        seNo = fn_1_5B4(0x6A1);
        fn_1_634(seNo, pan);
        break;
    case 2:
        if (obj->unk006++ > 60) {
            Hu3DMotionShiftSet(obj->unk00A, obj->unk00C, 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            obj->unk006 = 0;
            obj->unk004 = 0;
        }
        break;
    }
}

/* stage.c fn_1_3598, 167 insns. Scoreboard digit init: model, ten flip motions, parked on the end of digit's motion. */
void fn_1_3598(M510_STAGENUM *num, s16 digit, HuVecF *pos, M510_STAGE *stage)
{
    M510_STAGE *s;
    M510_WORK *work;
    M510_CAMERA *camera;
    HU3DMODELID modelId;

    s = stage;
    work = s->unk000;
    camera = &work->unk2474;
    memset(num, 0, sizeof(M510_STAGENUM));
    num->unk000 = stage;
    num->unk01E = num->unk020 = digit;
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x15), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk008 = modelId;
    num->unk00A[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x29), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[1] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2A), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[2] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2B), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[3] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2C), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[4] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2D), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[5] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2E), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[6] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x2F), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[7] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x30), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[8] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x31), HU_MEMNUM_OVL, HEAP_MODEL));
    num->unk00A[9] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m510, 0x32), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(modelId, pos->x, pos->y, pos->z);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_REV);
    Hu3DMotionSet(modelId, num->unk00A[digit]);
    Hu3DMotionTimeSet(modelId, Hu3DMotionMaxTimeGet(modelId));
}

/* stage.c fn_1_3834, 27 insns. Scoreboard digit close. */
void fn_1_3834(M510_STAGENUM *num)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        Hu3DMotionKill(num->unk00A[i]);
    }
    Hu3DModelKill(num->unk008);
    memset(num, 0, sizeof(M510_STAGENUM));
}

/* stage.c fn_1_38A0, 113 insns. Scoreboard digit frame: flip forward or backward (the short way round) toward unk020. */
void fn_1_38A0(M510_STAGENUM *num)
{
    s16 diff;
    float maxTime;

    if ((s16)num->unk01E != num->unk020) {
        diff = num->unk020 - num->unk01E;
        if (((diff >= 0) ? diff : -diff) > 5) {
            diff = (diff > 0) ? diff - 10 : diff + 10;
        }
        if (diff > 0) {
            Hu3DModelAttrReset(num->unk008, HU3D_MOTATTR_REV);
            maxTime = Hu3DMotionMaxTimeGet(num->unk008);
            if (Hu3DMotionTimeGet(num->unk008) >= maxTime) {
                num->unk01E = (num->unk01E >= 9) ? 0 : num->unk01E + 1;
                Hu3DMotionSet(num->unk008, num->unk00A[num->unk01E]);
            }
        } else {
            Hu3DModelAttrSet(num->unk008, HU3D_MOTATTR_REV);
            if (Hu3DMotionTimeGet(num->unk008) <= 0.0f) {
                num->unk01E = (num->unk01E <= 0) ? 9 : num->unk01E - 1;
                Hu3DMotionSet(num->unk008, num->unk00A[num->unk01E]);
                Hu3DMotionTimeSet(num->unk008, Hu3DMotionMaxTimeGet(num->unk008));
                if ((s16)num->unk01E == num->unk020) {
                    Hu3DModelAttrReset(num->unk008, HU3D_MOTATTR_REV);
                }
            }
        }
    }
}
