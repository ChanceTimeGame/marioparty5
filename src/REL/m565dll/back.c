/*
 * m565dll back.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/back.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "datadir_enum.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x108 */ /* float lbl_1_rodata_108 = 0.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 600.0f; */
/* 0x110 */ /* double lbl_1_rodata_110 = 3.141592653589793; */
/* 0x118 */ /* float lbl_1_rodata_118 = 360.0f; */
/* 0x120 */ /* double lbl_1_rodata_120 = 180; */
/* 0x128 */ /* float lbl_1_rodata_128 = 950.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = -650.0f; */
/* 0x130 */ /* float lbl_1_rodata_130 = 90.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 180.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = -180.0f; */
/* 0x140 */ /* double lbl_1_rodata_140 = 4503601774854144; */

/* --- functions (reference order) --- */
/* 497 insns. Creates the background models (sky, two orbiting pairs, and four
 * initially hidden ones) and their looping motions. */
void fn_1_3690(M565_BACK *back, M565_OBJECT *obj)
{
    s16 modelId;

    memset(back, 0, sizeof(M565_BACK));
    back->unk000 = obj;
    back->unk008 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x0), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk012 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x74), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk012);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk00A = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x1), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk014 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x75), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk014);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk00C = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x2), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk016 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x76), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk016);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk00E = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk018 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x7E), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk018);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk010 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6E), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk01A = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x7F), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk01A);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk01C = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6F), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk024 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x7A), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk024);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk01E = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x70), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk026 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x7B), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, back->unk026);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk020 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x71), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk028 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x7C), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionShapeSet(modelId, back->unk028);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    back->unk022 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x72), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, 1);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
}

/* 48 insns */
void fn_1_3E54(M565_BACK *back)
{
    Hu3DModelKill(back->unk022);
    Hu3DMotionKill(back->unk028);
    Hu3DModelKill(back->unk020);
    Hu3DMotionKill(back->unk026);
    Hu3DModelKill(back->unk01E);
    Hu3DMotionKill(back->unk024);
    Hu3DModelKill(back->unk01C);
    Hu3DMotionKill(back->unk01A);
    Hu3DModelKill(back->unk010);
    Hu3DMotionKill(back->unk018);
    Hu3DModelKill(back->unk00E);
    Hu3DMotionKill(back->unk016);
    Hu3DModelKill(back->unk00C);
    Hu3DMotionKill(back->unk014);
    Hu3DModelKill(back->unk00A);
    Hu3DMotionKill(back->unk012);
    Hu3DModelKill(back->unk008);
    memset(back, 0, sizeof(M565_BACK));
}

#define M565_ANGLE_WRAP(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))

/* 400 insns. Orbits unk00C/unk00E (phase 0) and unk010 (phase 300) around the
 * stage at radius 950, one lap per 600 frames. */
void fn_1_3F14(M565_BACK *back)
{
    HuVecF pos;
    float t;

    t = (back->unk004 % 600) / 600.0f;
    pos.x = sin(M_PI * (360.0f * t) / 180.0);
    pos.y = 0.0f;
    pos.z = cos(M_PI * (360.0f * t) / 180.0);
    PSVECScale(&pos, &pos, 950.0f);
    Hu3DModelPosSet(back->unk00C, pos.x, -650.0f, pos.z);
    Hu3DModelRotSet(back->unk00C, 0.0f, M565_ANGLE_WRAP(90.0f + 360.0f * t), 0.0f);
    Hu3DModelPosSet(back->unk00E, pos.x, -650.0f, pos.z);
    Hu3DModelRotSet(back->unk00E, 0.0f, M565_ANGLE_WRAP(180.0f + 360.0f * t), 0.0f);
    t = ((back->unk004 + 300) % 600) / 600.0f;
    pos.x = sin(M_PI * (360.0f * t) / 180.0);
    pos.y = 0.0f;
    pos.z = cos(M_PI * (360.0f * t) / 180.0);
    PSVECScale(&pos, &pos, 950.0f);
    Hu3DModelPosSet(back->unk010, pos.x, -650.0f, pos.z);
    Hu3DModelRotSet(back->unk010, 0.0f, M565_ANGLE_WRAP(90.0f + 360.0f * t), 0.0f);
    back->unk004++;
}
