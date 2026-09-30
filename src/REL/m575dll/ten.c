/*
 * m575dll ten.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/ten.s.
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
/* 0x160 */ /* float lbl_1_rodata_160 = 0.0f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 750.0f; */
/* 0x168 */ /* float lbl_1_rodata_168 = 4.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = 1.3f; */
/* 0x170 */ /* s32 lbl_1_rodata_170[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x17C */ /* s32 lbl_1_rodata_17C[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x188 */ /* float lbl_1_rodata_188 = -65.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 0.9f; */
/* 0x190 */ /* double lbl_1_rodata_190 = 180; */
/* 0x198 */ /* double lbl_1_rodata_198 = 3.141592653589793; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 30.0f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 0.5235988f; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = 0.98f; */
/* 0x1AC */ /* float lbl_1_rodata_1AC = 0.5f; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 90.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 0.017453292f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8[2] = { 25.0f, 0.0f }; */

/* --- functions (reference order) --- */

#define M575_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m575, n), HU_MEMNUM_OVL, HEAP_MODEL)

/* ten fn_1_4BCC, 179 insns. Board init: the team's board model and its shadow twin. */
void fn_1_4BCC(M575_TEN *ten, M575_TEAM *team)
{
    HU3DMODELID modelId;
    M575_CAMERA *camera;
    M575_TEAM *t;

    t = team;
    camera = &t->unkE20;
    memset(ten, 0, sizeof(M575_TEN));
    ten->unk000 = team;
    if (t->unk004 == 0) {
        ten->unk004 = modelId = Hu3DModelCreate(M575_DATA(0x07));
        ten->unk006 = Hu3DJointMotion(modelId, M575_DATA(0x16));
    } else {
        ten->unk004 = modelId = Hu3DModelCreate(M575_DATA(0x06));
        ten->unk006 = Hu3DJointMotion(modelId, M575_DATA(0x15));
    }
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelShadowMapSet(modelId);
    ten->unk008 = &Hu3DData[modelId].pos;
    ten->unk00C = Hu3DData[modelId].mtx;
    Hu3DMotionSet(modelId, ten->unk006);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    ten->unk010 = modelId = Hu3DModelCreate(M575_DATA(0x0E));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk004);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    ten->unk014 = &Hu3DData[modelId].pos;
    ten->unk018 = Hu3DData[modelId].mtx;
    fn_1_9320(&ten->unk02C, 0, 750.0f, 4.0f, 1.3f);
}

/* ten fn_1_4E98, 22 insns. Board close. */
void fn_1_4E98(M575_TEN *ten)
{
    fn_1_96F8(&ten->unk02C);
    Hu3DMotionKill(ten->unk006);
    Hu3DModelKill(ten->unk010);
    Hu3DModelKill(ten->unk004);
    memset(ten, 0, sizeof(M575_TEN));
}

/* ten fn_1_4EF0, 283 insns. Board frame: tilt limited to 30 degrees, then (state >= 5)
   tipped by the scored angle; SE 0x930/0x931 when the tilt crosses 25. */
void fn_1_4EF0(M575_TEN *ten)
{
    Mtx mtx;
    HuVecF vec;
    HuVecF dir;
    HuVecF axis;
    HuVecF up;
    Quaternion q1;
    Quaternion q2;
    Quaternion q3;
    Quaternion q4;
    Quaternion q5;
    Quaternion q6;
    float dot;
    float rad;
    float angle;
    M575_TUBOEFF *eff;
    M575_WORK *work;
    M575_TEAM *team;

    team = ten->unk000;
    work = team->unk000;
    eff = &ten->unk02C;
    fn_1_9728(eff);
    PSMTXCopy(eff->unk048, ten->unk00C);
    PSMTXCopy(eff->unk048, ten->unk018);
    ten->unk008->y = -65.0f;
    ten->unk014->y = -65.0f;
    {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        HuVecF *src = &zero;
        eff->unk0C0 = *src;
    }
    PSVECScale(&eff->unk0A8, &eff->unk0A8, 0.9f);
    PSVECScale(&eff->unk0B4, &eff->unk0B4, 0.9f);
    {
        HuVecF yAxis = { 0.0f, 1.0f, 0.0f };
        HuVecF *src = &yAxis;
        up = *src;
    }
    dir.x = eff->unk048[1][0];
    dir.y = eff->unk048[1][1];
    dir.z = eff->unk048[1][2];
    PSVECNormalize(&dir, &dir);
    dot = PSVECDotProduct(&dir, &up);
    rad = acos(dot);
    angle = 180.0 * (rad / 3.141592653589793);
    if (angle > 30.0f) {
        vec.x = dir.x;
        vec.y = 0.0f;
        vec.z = dir.z;
        PSVECNormalize(&vec, &vec);
        PSVECCrossProduct(&up, &vec, &axis);
        PSMTXRotAxisRad(mtx, &axis, 0.5235988f);
        PSMTXMultVec(mtx, &up, &vec);
        fn_1_2D5C(&q1, &dir, &vec);
        C_QUATMtx(&q2, eff->unk048);
        PSQUATMultiply(&q1, &q2, &q3);
        PSMTXQuat(eff->unk048, &q3);
        angle = 30.0f;
    }
    if (work->unk00C >= 5) {
        vec.x = dir.x;
        vec.y = 0.0f;
        vec.z = dir.z;
        angle = 0.98f * (ten->unk020 - 0.5f);
        angle = (angle > 90.0f) ? 90.0f : ((angle < 0.0f) ? 0.0f : angle);
        PSVECNormalize(&vec, &vec);
        PSVECCrossProduct(&up, &vec, &axis);
        PSMTXRotAxisRad(mtx, &axis, 0.017453292f * angle);
        PSMTXMultVec(mtx, &up, &vec);
        fn_1_2D5C(&q4, &dir, &vec);
        C_QUATMtx(&q5, eff->unk048);
        PSQUATMultiply(&q4, &q5, &q6);
        PSMTXQuat(eff->unk048, &q6);
    }
    ten->unk024 = ten->unk020;
    ten->unk020 = angle;
    if (ten->unk024 < 25.0f && ten->unk020 > 25.0f && ten->unk028 == 0) {
        if (team->unk004 == 0) {
            fn_1_530(0x930);
        } else if (team->unk004 == 1) {
            fn_1_530(0x931);
        }
        ten->unk028 = 30;
    }
    if (ten->unk028 != 0) {
        ten->unk028--;
    }
    if (ten->unk01C != 0) {
        ten->unk01C--;
    }
}
