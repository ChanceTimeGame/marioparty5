/*
 * m575dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/stage.s.
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
/* 0xF0 */ /* s32 lbl_1_rodata_F0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0xFC */ /* float lbl_1_rodata_FC = 0.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 50.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 400.0f; */
/* 0x108 */ /* float lbl_1_rodata_108 = 100.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 8000.0f; */
/* 0x110 */ /* double lbl_1_rodata_110 = 4503601774854144; */
/* 0x118 */ /* float lbl_1_rodata_118 = 90.0f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 5000.0f; */
/* 0x120 */ /* float lbl_1_rodata_120 = 1.0f; */
/* 0x124 */ /* float lbl_1_rodata_124 = -20.0f; */
/* 0x128 */ /* float lbl_1_rodata_128 = 0.1f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 1.5f; */
/* 0x130 */ /* float lbl_1_rodata_130 = 200.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 10000.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 20.0f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 60.0f; */
/* 0x140 */ /* float lbl_1_rodata_140 = -1.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = 0.8f; */
/* 0x148 */ /* float lbl_1_rodata_148 = -3000.0f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 0.2f; */
/* 0x150 */ /* float lbl_1_rodata_150 = 0.05f; */
/* 0x158 */ /* double lbl_1_rodata_158 = 4503599627370496; */

/* --- functions (reference order) --- */

#define M575_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m575, n), HU_MEMNUM_OVL, HEAP_MODEL)

/* stage fn_1_3DE0, 352 insns. Stage init: five scenery models and the 60 blocks. */
void fn_1_3DE0(M575_STAGE *stage, M575_TEAM *team)
{
    HU3DMODELID modelId;
    M575_STAGEOBJ *obj;
    s32 i;
    M575_TEAM *t;
    M575_CAMERA *camera;

    t = team;
    camera = &t->unkE20;
    memset(stage, 0, sizeof(M575_STAGE));
    stage->unk000 = team;
    if (t->unk004 == 0) {
        stage->unk008 = modelId = Hu3DModelCreate(M575_DATA(0x00));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, 0x11);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        stage->unk014 = Hu3DJointMotion(modelId, M575_DATA(0x0F));
        Hu3DMotionSet(modelId, stage->unk014);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        stage->unk00A = modelId = Hu3DModelCreate(M575_DATA(0x01));
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        for (i = 0; i < 60; i++) {
            obj = &stage->unk020[i];
            fn_1_4538(obj, i, stage);
            {
                HuVecF zero = { 0.0f, 0.0f, 0.0f };
                HuVecF *src = &zero;
                obj->unk018 = *src;
            }
            obj->unk00C = obj->unk018;
            obj->unk00C.z = obj->unk018.z = 50.0f + (400.0f + 100.0f * i);
        }
        stage->unkB60 = 1;
        stage->unk00C = modelId = Hu3DModelCreate(M575_DATA(0x02));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, 0x11);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        stage->unk016 = Hu3DJointMotion(modelId, M575_DATA(0x10));
        Hu3DMotionSet(modelId, stage->unk016);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        stage->unk00E = modelId = Hu3DModelCreate(M575_DATA(0x03));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, 1);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        stage->unk018 = Hu3DJointMotion(modelId, M575_DATA(0x11));
        Hu3DMotionSet(modelId, stage->unk018);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        stage->unk010 = modelId = Hu3DModelCreate(M575_DATA(0x04));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, 0x11);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        stage->unk012 = modelId = Hu3DModelCreate(M575_DATA(0x05));
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 8000.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, 0x11);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        stage->unk01A = Hu3DJointMotion(modelId, M575_DATA(0x12));
        Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    }
    stage->unk01C = 0.0f;
}

/* stage fn_1_4360, 51 insns. Stage close. */
void fn_1_4360(M575_STAGE *stage)
{
    s32 i;
    M575_TEAM *team;

    team = stage->unk000;
    if (team->unk004 == 0) {
        for (i = 0; i < 60; i++) {
            fn_1_463C(&stage->unk020[i]);
        }
        Hu3DMotionKill(stage->unk01A);
        Hu3DMotionKill(stage->unk018);
        Hu3DMotionKill(stage->unk016);
        Hu3DMotionKill(stage->unk014);
        Hu3DModelKill(stage->unk012);
        Hu3DModelKill(stage->unk010);
        Hu3DModelKill(stage->unk00E);
        Hu3DModelKill(stage->unk00C);
        Hu3DModelKill(stage->unk00A);
        Hu3DModelKill(stage->unk008);
    }
    memset(stage, 0, sizeof(M575_STAGE));
}

/* stage fn_1_442C, 67 insns. Stage frame: blocks, and the SE at motion time 90. */
void fn_1_442C(M575_STAGE *stage)
{
    s32 i;
    M575_WORK *work;
    M575_TEAM *team;
    float time;

    team = stage->unk000;
    work = team->unk000;
    if (team->unk004 == 0 && stage->unkB60) {
        for (i = 0; i < 60; i++) {
            fn_1_46B4(&stage->unk020[i]);
        }
    }
    if (work->unk00C == 4) {
        time = Hu3DMotionTimeGet(stage->unk00C);
        if (stage->unk01C < 90.0f && time >= 90.0f) {
            if (team->unk004 == 0) {
                fn_1_530(0x932);
            } else if (team->unk004 == 1) {
                fn_1_530(0x933);
            }
        }
        stage->unk01C = time;
    }
}

/* stage fn_1_4538, 65 insns. Block init: a link of the block template. */
void fn_1_4538(M575_STAGEOBJ *obj, s16 idx, M575_STAGE *stage)
{
    HU3DMODELID modelId;
    M575_TEAM *team;
    M575_CAMERA *camera;
    M575_STAGE *s;

    s = stage;
    team = s->unk000;
    camera = &team->unkE20;
    memset(obj, 0, sizeof(M575_STAGEOBJ));
    if (team->unk004 == 0) {
        obj->unk000 = stage;
        obj->unk006 = idx;
        obj->unk008 = modelId = Hu3DModelLink(s->unk00A);
        Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelCameraSet(modelId, camera->unk004);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowMapSet(modelId);
    }
}

/* stage fn_1_463C, 30 insns. Block close. */
void fn_1_463C(M575_STAGEOBJ *obj)
{
    M575_STAGE *stage;
    M575_TEAM *team;

    stage = obj->unk000;
    team = stage->unk000;
    if (team->unk004 != 0) {
        memset(obj, 0, sizeof(M575_STAGEOBJ));
    } else {
        Hu3DModelKill(obj->unk008);
        memset(obj, 0, sizeof(M575_STAGEOBJ));
    }
}

/* stage fn_1_46B4, 326 insns. Block frame: falls away once the lead player passes it. */
s32 fn_1_46B4(M575_STAGEOBJ *obj)
{
    HuVecF diff;
    HuVecF pos;
    s32 ret;
    float lim;
    float t;
    M575_PLAYER *player;
    M575_PLAYER *player2;
    M575_STAGE *stage;
    M575_TEAM *team;

    stage = obj->unk000;
    team = stage->unk000;
    player = &team->unk008[0];
    player2 = &team->unk008[1];
    t = (player->unk078->z - 400.0f - 50.0f) / 5000.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    ret = 0;
    switch (obj->unk004) {
        case 0:
            lim = (obj->unk018.z - 50.0f) + 100.0f * (1.0f - t);
            if (player->unk078->z < lim) {
                obj->unk004++;
            }
            break;
        case 1:
            obj->unk024 = -20.0f * (1.0f - t) - 0.1f;
            obj->unk004++;
            break;
        case 2:
            obj->unk024 += 1.5f;
            if (obj->unk018.y < 0.0f) {
                break;
            }
            pos.x = (obj->unk018.x - 100.0f) + 200.0f * ((frand() % 10000) / 10000.0f);
            pos.y = obj->unk018.y;
            pos.z = obj->unk018.z;
            fn_1_E55C(1, &pos);
            obj->unk004++;
            break;
        case 3:
            obj->unk024 += 1.5f;
            if (obj->unk018.y > 100.0f) {
                obj->unk028 = 20.0f + 60.0f * ((frand() % 10000) / 10000.0f);
                obj->unk028 *= (frand() & 1) ? -1.0f : 1.0f;
                obj->unk004++;
            }
            break;
        case 4:
            obj->unk024 -= 0.8f + ((0.1f * obj->unk024 >= 0.0f) ? 0.1f * obj->unk024 : -(0.1f * obj->unk024));
            if (obj->unk018.y < -3000.0f) {
                Hu3DModelAttrSet(obj->unk008, HU3D_ATTR_DISPOFF);
                obj->unk004++;
            }
            break;
        case 5:
            break;
    }
    obj->unk00C.y += obj->unk024;
    PSVECSubtract(&obj->unk00C, &obj->unk018, &diff);
    PSVECScale(&diff, &diff, 0.2f);
    PSVECAdd(&obj->unk018, &diff, &obj->unk018);
    Hu3DModelPosSet(obj->unk008, obj->unk018.x, obj->unk018.y, obj->unk018.z);
    obj->unk02C = obj->unk02C + 0.05f * (obj->unk028 - obj->unk02C);
    Hu3DModelRotSet(obj->unk008, 0.0f, 0.0f, obj->unk02C);
    return ret;
}
