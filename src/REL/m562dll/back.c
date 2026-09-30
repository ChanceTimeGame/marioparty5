/*
 * m562dll back.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/back.s.
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
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0xC8 lbl_1_rodata_C8 (0xC): 0x00000000 0xC2480000 0xC4D48000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_D4 = 0.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = -680.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 370.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = -2100.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 680.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 0.25f; /* 0xE8 */
static const float lbl_1_rodata_EC = 37.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 25.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 40.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 400.0f; /* 0xF8 */
static const double lbl_1_rodata_100 = 30.0; /* 0x100 */
static const double lbl_1_rodata_108 = 3.141592653589793; /* 0x108 */
static const float lbl_1_rodata_110 = 360.0f; /* 0x110 */
static const double lbl_1_rodata_118 = 180.0; /* 0x118 */
/* 0x120 lbl_1_rodata_120 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_128 = 10000.0f; /* 0x128 */
static const float lbl_1_rodata_12C = 1.0f; /* 0x12C */
static const float lbl_1_rodata_130 = 0.7853982f; /* 0x130 */
static const float lbl_1_rodata_134 = 0.017453292f; /* 0x134 */
static const float lbl_1_rodata_138 = 180.0f; /* 0x138 */
static const float lbl_1_rodata_13C = 0.6457718f; /* 0x13C */
static const float lbl_1_rodata_140 = 0.5f; /* 0x140 */
/* 0x148 lbl_1_rodata_148 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_150 = 45.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 50.0f; /* 0x154 */
static const float lbl_1_rodata_158 = 55.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 110.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 20.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 5.0f; /* 0x164 */
static const float lbl_1_rodata_168 = 2.0f; /* 0x168 */
/* 0x16C lbl_1_rodata_16C (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x16D gap_03_0000016D_rodata: 0x00, 0x00, 0x00 */
/* 0x170 lbl_1_rodata_170 (0x1): 0x40 -- an aggregate initialiser, write it as a local */
/* 0x171 lbl_1_rodata_171 (0x3): "PP" -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_174 = 0.01f; /* 0x174 */
static const float lbl_1_rodata_178 = 1.2f; /* 0x178 */
static const float lbl_1_rodata_17C = -0.5f; /* 0x17C */
static const float lbl_1_rodata_180 = -51.0f; /* 0x180 */
static const float lbl_1_rodata_184 = -874.0f; /* 0x184 */
static const float lbl_1_rodata_188 = 0.05f; /* 0x188 */
static const float lbl_1_rodata_18C = 120.0f; /* 0x18C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7810 */ float lbl_1_bss_7810[4];

/* --- functions (reference order), .data placed before its first user --- */
/* 0x60 */ float lbl_1_data_60[3] = { 0.0f, -4000.0f, -26000.0f };

#define M562_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m562, n), HU_MEMNUM_OVL, HEAP_MODEL)

/* 619 insns. Background init: arena, side pillars, lava sea (warp material), sky and the three
   distant layers whose position/scale follow the battle phase (fn_1_4748). */
void fn_1_3808(M562_BACK *back, M562_WORK *work)
{
    HU3DMODELID modelId;
    M562_WORK *w;
    M562_CAMERA *camera;

    w = work;
    camera = &w->camera[0];
    memset(back, 0, sizeof(M562_BACK));
    back->unk00 = work;
    back->unk0C = modelId = Hu3DModelCreate(M562_DATA(0x08));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk0E = modelId = Hu3DModelCreate(M562_DATA(0x09));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk10 = modelId = Hu3DModelCreate(M562_DATA(0x0A));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk12 = modelId = Hu3DModelCreate(M562_DATA(0x0B));
    Hu3DModelPosSet(modelId, -680.0f, 370.0f, -2100.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk16 = Hu3DJointMotion(modelId, M562_DATA(0x2B));
    Hu3DMotionSet(modelId, back->unk16);
    Hu3DMotionSpeedSet(modelId, 0.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    back->unk14 = modelId = Hu3DModelCreate(M562_DATA(0x0C));
    Hu3DModelPosSet(modelId, 680.0f, 370.0f, -2100.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk18 = Hu3DJointMotion(modelId, M562_DATA(0x2C));
    Hu3DMotionSet(modelId, back->unk18);
    Hu3DMotionSpeedSet(modelId, 0.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    {
        HuVecF pos = { 0.0f, -50.0f, -1700.0f };
        HuVecF *src = &pos;
        back->unk34 = *src;
    }
    back->unk2C = 0;
    back->unk30 = 1;
    back->unk1A = modelId = Hu3DModelCreate(M562_DATA(0x0D));
    Hu3DModelPosSet(modelId, back->unk34.x, back->unk34.y, back->unk34.z);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelMatHookSet(modelId, fn_1_51C4);
    back->unk1C = modelId = Hu3DModelCreate(M562_DATA(0x0E));
    Hu3DModelPosSet(modelId, back->unk34.x, back->unk34.y, back->unk34.z);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DMotionSpeedSet(modelId, 0.25f);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk1E = Hu3DJointMotion(modelId, M562_DATA(0x5F));
    Hu3DMotionSet(modelId, back->unk1E);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk20 = modelId = Hu3DModelCreate(M562_DATA(0x0F));
    Hu3DModelPosSet(modelId, back->unk34.x, back->unk34.y, back->unk34.z);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DMotionSpeedSet(modelId, 0.0f);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk22 = Hu3DJointMotion(modelId, M562_DATA(0x60));
    Hu3DMotionSet(modelId, back->unk22);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    back->unk40 = modelId = Hu3DModelCreate(M562_DATA(0x10));
    Hu3DModelPosSet(modelId, lbl_1_data_60[0], lbl_1_data_60[1], lbl_1_data_60[2]);
    Hu3DModelRotSet(modelId, 37.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 25.0f, 25.0f, 25.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    back->unk42 = Hu3DJointMotion(modelId, M562_DATA(0x5C));
    Hu3DMotionSet(modelId, back->unk42);
    Hu3DMotionSpeedSet(modelId, 0.25f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    back->unk44 = modelId = Hu3DModelCreate(M562_DATA(0x11));
    Hu3DModelPosSet(modelId, lbl_1_data_60[0], lbl_1_data_60[1], lbl_1_data_60[2]);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk48 = Hu3DJointMotion(modelId, M562_DATA(0x5D));
    Hu3DMotionSet(modelId, back->unk48);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    back->unk46 = modelId = Hu3DModelCreate(M562_DATA(0x12));
    Hu3DModelPosSet(modelId, lbl_1_data_60[0], lbl_1_data_60[1], lbl_1_data_60[2]);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    back->unk4A = Hu3DJointMotion(modelId, M562_DATA(0x5E));
    Hu3DMotionSet(modelId, back->unk4A);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    back->unk54 = 40.0f;
    back->unk58 = 60;
}

/* 50 insns. Background kill. */
void fn_1_41B4(M562_BACK *back)
{
    Hu3DMotionKill(back->unk4A);
    Hu3DModelKill(back->unk46);
    Hu3DMotionKill(back->unk48);
    Hu3DModelKill(back->unk44);
    Hu3DMotionKill(back->unk42);
    Hu3DModelKill(back->unk40);
    Hu3DMotionKill(back->unk22);
    Hu3DModelKill(back->unk20);
    Hu3DMotionKill(back->unk1E);
    Hu3DModelKill(back->unk1C);
    Hu3DModelKill(back->unk1A);
    Hu3DMotionKill(back->unk18);
    Hu3DModelKill(back->unk14);
    Hu3DMotionKill(back->unk16);
    Hu3DModelKill(back->unk12);
    Hu3DModelKill(back->unk10);
    Hu3DModelKill(back->unk0E);
    Hu3DModelKill(back->unk0C);
    memset(back, 0, sizeof(M562_BACK));
}

/* 98 insns. Background frame: the two random flare bursts, and the lava sea bobbing on a
   400-frame sine (not in the final phase). */
void fn_1_427C(M562_BACK *back)
{
    HuVecF pos;
    float t;
    M562_WORK *work;

    work = back->unk00;
    fn_1_4404(back, back->unk44, &back->unk4C[0], &back->unk50[0]);
    fn_1_4404(back, back->unk46, &back->unk4C[1], &back->unk50[1]);
    if (work->unk000E != 4) {
        t = (back->unk2C % 400) / 400.0f;
        pos.x = back->unk34.x;
        pos.y = back->unk34.y + 30.0 * sin(3.141592653589793 * (360.0f * t) / 180.0);
        pos.z = back->unk34.z;
        Hu3DModelPosSet(back->unk1A, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(back->unk1C, pos.x, pos.y, pos.z);
        Hu3DModelPosSet(back->unk20, pos.x, pos.y, pos.z);
        if (back->unk30 != 0) {
            back->unk2C++;
        }
    }
}

/* 209 insns. One flare model: wait a random time, then play it once at a random heading/scale. */
void fn_1_4404(M562_BACK *back, s16 modelId, s16 *state, s16 *timer)
{
    Mtx mtx;
    Mtx rot;
    float t;
    float maxTime;

    switch (*state) {
        case 0:
            *timer = frand() % back->unk58 + back->unk58 / 2;
            *state = 1;
            break;
        case 1:
            if ((*timer)-- <= 0) {
                t = (frand() % 10000) / 10000.0f;
                PSMTXScale(mtx, 1.0f, 1.0f, 1.0f);
                PSMTXTrans(mtx, 0.0f, 0.0f, 0.0f);
                PSMTXRotRad(rot, 'X', 0.7853982f);
                PSMTXConcat(rot, mtx, mtx);
                PSMTXRotRad(rot, 'Y', 0.017453292f * (360.0f * t - 180.0f));
                PSMTXConcat(rot, mtx, mtx);
                PSMTXRotRad(rot, 'X', 0.6457718f);
                PSMTXConcat(rot, mtx, mtx);
                PSMTXCopy(mtx, Hu3DData[modelId].mtx);
                t = (frand() % 10000) / 10000.0f;
                t = 0.5f + 0.5f * t;
                Hu3DModelScaleSet(modelId, t * back->unk54, t * back->unk54, t * back->unk54);
                Hu3DMotionTimeSet(modelId, 0.0f);
                Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
                *timer = 0;
                *state = 2;
            }
            break;
        case 2:
            maxTime = Hu3DMotionMaxTimeGet(modelId);
            if (Hu3DMotionTimeGet(modelId) >= maxTime) {
                Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
                *timer = 0;
                *state = 0;
            }
            break;
    }
}

/* 0x6C */ float lbl_1_data_6C = 25.0f;
/* 0x70 */ float lbl_1_data_70[3] = { 0.0f, -2600.0f, -26000.0f };
/* 0x7C */ float lbl_1_data_7C = 40.0f;
/* 0x80 */ float lbl_1_data_80[3] = { 0.0f, -3300.0f, -26000.0f };
/* 0x8C */ float lbl_1_data_8C = 50.0f;
/* 0x90 */ float lbl_1_data_90[3] = { 0.0f, -3300.0f, -26000.0f };
/* 0x9C */ float lbl_1_data_9C = 60.0f;
/* 0xA0 */ float lbl_1_data_A0[3] = { 0.0f, -3300.0f, -26000.0f };
/* 0xAC */ float lbl_1_data_AC = 80.0f;

/* 593 insns. Blend the distant background between the phase's key and the previous one
   (t = 1: this phase). Phase 0 blends against phase 3's key (retail). */
void fn_1_4748(M562_BACK *back, s16 phase, float t)
{
    HuVecF pos;
    float scale;

    switch (phase) {
        case 0:
            pos.x = lbl_1_data_60[0] * t + lbl_1_data_90[0] * (1.0f - t);
            pos.y = lbl_1_data_60[1] * t + lbl_1_data_90[1] * (1.0f - t);
            pos.z = lbl_1_data_60[2] * t + lbl_1_data_90[2] * (1.0f - t);
            scale = lbl_1_data_6C * t + lbl_1_data_9C * (1.0f - t);
            Hu3DModelScaleSet(back->unk40, scale, scale, scale);
            Hu3DModelPosSet(back->unk40, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk44, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk46, pos.x, pos.y, pos.z);
            back->unk54 = 40.0f;
            back->unk58 = 60;
            Hu3DMotionSpeedSet(back->unk44, 1.0f);
            Hu3DMotionSpeedSet(back->unk46, 1.0f);
            Hu3DMotionSpeedSet(back->unk40, 0.25f);
            break;
        case 1:
            pos.x = lbl_1_data_70[0] * t + lbl_1_data_60[0] * (1.0f - t);
            pos.y = lbl_1_data_70[1] * t + lbl_1_data_60[1] * (1.0f - t);
            pos.z = lbl_1_data_70[2] * t + lbl_1_data_60[2] * (1.0f - t);
            scale = lbl_1_data_7C * t + lbl_1_data_6C * (1.0f - t);
            Hu3DModelScaleSet(back->unk40, scale, scale, scale);
            Hu3DModelPosSet(back->unk40, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk44, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk46, pos.x, pos.y, pos.z);
            back->unk54 = 45.0f * t + 40.0f * (1.0f - t);
            back->unk58 = 60;
            Hu3DMotionSpeedSet(back->unk44, 1.0f);
            Hu3DMotionSpeedSet(back->unk46, 1.0f);
            Hu3DMotionSpeedSet(back->unk40, 0.25f);
            break;
        case 2:
            pos.x = lbl_1_data_80[0] * t + lbl_1_data_70[0] * (1.0f - t);
            pos.y = lbl_1_data_80[1] * t + lbl_1_data_70[1] * (1.0f - t);
            pos.z = lbl_1_data_80[2] * t + lbl_1_data_70[2] * (1.0f - t);
            scale = lbl_1_data_8C * t + lbl_1_data_7C * (1.0f - t);
            Hu3DModelScaleSet(back->unk40, scale, scale, scale);
            Hu3DModelPosSet(back->unk40, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk44, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk46, pos.x, pos.y, pos.z);
            back->unk54 = 50.0f * t + 45.0f * (1.0f - t);
            back->unk58 = 50;
            Hu3DMotionSpeedSet(back->unk44, 1.0f);
            Hu3DMotionSpeedSet(back->unk46, 1.0f);
            Hu3DMotionSpeedSet(back->unk40, 0.25f);
            break;
        case 3:
            pos.x = lbl_1_data_90[0] * t + lbl_1_data_80[0] * (1.0f - t);
            pos.y = lbl_1_data_90[1] * t + lbl_1_data_80[1] * (1.0f - t);
            pos.z = lbl_1_data_90[2] * t + lbl_1_data_80[2] * (1.0f - t);
            scale = lbl_1_data_9C * t + lbl_1_data_8C * (1.0f - t);
            Hu3DModelScaleSet(back->unk40, scale, scale, scale);
            Hu3DModelPosSet(back->unk40, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk44, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk46, pos.x, pos.y, pos.z);
            back->unk54 = 55.0f * t + 50.0f * (1.0f - t);
            back->unk58 = 40;
            Hu3DMotionSpeedSet(back->unk44, 1.0f);
            Hu3DMotionSpeedSet(back->unk46, 1.0f);
            Hu3DMotionSpeedSet(back->unk40, 0.25f);
            break;
        case 4:
            pos.x = lbl_1_data_A0[0] * t + lbl_1_data_90[0] * (1.0f - t);
            pos.y = lbl_1_data_A0[1] * t + lbl_1_data_90[1] * (1.0f - t);
            pos.z = lbl_1_data_A0[2] * t + lbl_1_data_90[2] * (1.0f - t);
            scale = lbl_1_data_AC * t + lbl_1_data_9C * (1.0f - t);
            Hu3DModelScaleSet(back->unk40, scale, scale, scale);
            Hu3DModelPosSet(back->unk40, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk44, pos.x, pos.y, pos.z);
            Hu3DModelPosSet(back->unk46, pos.x, pos.y, pos.z);
            back->unk54 = 110.0f * t + 55.0f * (1.0f - t);
            back->unk58 = 20.0f * t + 40.0f * (1.0f - t);
            Hu3DMotionSpeedSet(back->unk44, 5.0f * t + (1.0f - t));
            Hu3DMotionSpeedSet(back->unk46, 5.0f * t + (1.0f - t));
            Hu3DMotionSpeedSet(back->unk40, 2.0f * t + 0.25f * (1.0f - t));
            break;
    }
}

/* 78 insns. Layer-15 hook (main fn_1_AC4/fn_1_16F0): copy the EFB into the work's 320x240
   RGB565 texture for the lava-sea warp. GPU-only consumer (fn_1_51C4): no CPU read. */
void fn_1_508C(s16 layerNo)
{
    HU3DWATER *waterP = &Hu3DWaterData;
    GXColor clearColor = { 0, 0, 0, 0 };
    s32 pause;

    if (lbl_1_bss_0->unk2864 && lbl_1_bss_0->unk000E != 4 && (Hu3DCameraBit & 1)) {
        GXSetTexCopySrc(0, 0, 640, 480);
        GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
        GXSetCopyClear(clearColor, 0xFFFFFF);
        GXCopyTex(lbl_1_bss_0->unk2864, GX_TRUE);
        if ((pause = omPauseChk() + omUPauseFlag) == 0) {
            (void)0;
        }
    }
}

/* 0xB0 */ float lbl_1_data_B0[2][3] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.01f, 0.0f } }; /* indirect texture matrix */

/* 305 insns. Material hook of the lava sea (unk1A): project the EFB copy onto it and warp it by
   the scrolling indirect texture (work+0x2868). back->unk24 scrolls and tints, unk28 strengthens. */
void fn_1_51C4(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXColor color = { 0x40, 0x50, 0x50, 0x00 };
    GXTexObj texObj;
    Mtx trans;
    Mtx scale;
    Mtx mtx;
    Mtx proj;
    Mtx invCam;

    if (lbl_1_bss_0->unk2864) {
        if (lbl_1_bss_0->back.unk28 == 0) {
            lbl_1_data_B0[1][1] = 0.01f;
        } else {
            lbl_1_data_B0[1][1] = 1.0f;
        }
        GXSetNumTexGens(2);
        GXSetNumTevStages(1);
        GXInitTexObj(&texObj, lbl_1_bss_0->unk2864, 320, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
        GXInitTexObjLOD(&texObj, GX_NEAR, GX_NEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
        GXLoadTexObj(&texObj, GX_TEXMAP0);
        HuSprTexLoad(lbl_1_bss_0->unk2868, 0, GX_TEXMAP1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        C_MTXLightPerspective(proj, 45.0f, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
        PSMTXIdentity(trans);
        PSMTXTrans(trans, 0.0f, -51.0f, -874.0f);
        PSMTXInverse(Hu3DCameraMtx, invCam);
        PSMTXConcat(invCam, trans, trans);
        PSMTXConcat(proj, Hu3DCameraMtx, mtx);
        PSMTXConcat(mtx, trans, mtx);
        GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX3x4);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        if (lbl_1_bss_0->back.unk24 != 0) {
            lbl_1_bss_7810[0] += 0.05f;
        }
        PSMTXTrans(trans, 0.0f, lbl_1_bss_7810[0], 0.0f);
        PSMTXScale(scale, 120.0f, 120.0f, 120.0f);
        PSMTXConcat(scale, trans, mtx);
        GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX2x4);
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
        if (lbl_1_bss_0->back.unk24 != 0) {
            GXSetTevColor(GX_TEVREG0, color);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        } else {
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        }
        GXSetNumIndStages(1);
        GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
        GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
        GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
        GXSetIndTexMtx(GX_ITM_0, lbl_1_data_B0, -1);
    }
}
