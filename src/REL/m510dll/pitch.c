/*
 * m510dll pitch.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/pitch.s.
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 0.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 1.0f; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 90.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 180.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 270.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 360.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = -180.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 0.017453292f; */
/* 0x108 */ /* double lbl_1_rodata_108 = 4503601774854144; */

/* --- .data --- */
/* 0x320 */ HuVecF lbl_1_data_320 = { -50.0f, 0.0f, 0.0f };
/* 0x32C */ HuVecF lbl_1_data_32C = { 0.0f, 75.0f, 0.0f };
/* 0x338 */ HuVecF lbl_1_data_338 = { 0.0f, -50.0f, -15.0f };
/* 0x344 */ s16 lbl_1_data_344[4][5] = { { 0, 0, 0, 0, 0 }, { 60, 20, 30, 40, 0 }, { 5, 5, 5, 5, 0 }, { 30, 40, 30, 20, 0 } };

/* --- functions (reference order) --- */
/* 120 insns */
void fn_1_47C4(M510_PITCH *pitch, M510_PLAYER *player)
{
    M510_PLAYER *owner;
    M510_WORK *work;
    M510_CAMERA *camera;
    HU3DMODELID mdlId;

    owner = player;
    work = owner->unk000;
    camera = &work->unk2474;
    memset(pitch, 0, sizeof(M510_PITCH));
    pitch->unk000 = player;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x440000, HU_MEMNUM_OVL, HEAP_MODEL));
    pitch->unk008 = mdlId;
    Hu3DModelPosSet(mdlId, lbl_1_data_320.x, lbl_1_data_320.y, lbl_1_data_320.z);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, camera->unk004);
    Hu3DModelLayerSet(mdlId, 0);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    pitch->unk00A = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(0x440016, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdlId, pitch->unk00A);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x440001, HU_MEMNUM_OVL, HEAP_MODEL));
    pitch->unk00C = mdlId;
    Hu3DModelPosSet(mdlId, lbl_1_data_32C.x, lbl_1_data_32C.y, lbl_1_data_32C.z);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, camera->unk004);
    Hu3DModelLayerSet(mdlId, 0);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    pitch->unk020 = 2;
    pitch->unk038 = -1;
}

/* 20 insns */
void fn_1_49A4(M510_PITCH *pitch)
{
    Hu3DModelKill(pitch->unk00C);
    Hu3DMotionKill(pitch->unk00A);
    Hu3DModelKill(pitch->unk008);
    memset(pitch, 0, sizeof(M510_PITCH));
}

/* 426 insns */
void fn_1_49F4(M510_PITCH *pitch)
{
    M510_PLAYER *player;
    M510_BALL *ball;
    void *slot;
    float t;
    HuVecF pos;
    Mtx mtx;

    player = pitch->unk000;
    ball = &player->unk154;
    switch (pitch->unk004) {
        case 0:
            if (pitch->unk024 != 0) {
                pitch->unk024 = 0;
                pitch->unk006 = 0;
                pitch->unk004 = 1;
            }
            break;
        case 1:
            slot = fn_1_52B0(&player->unk154, &player->unk118.unk028, pitch->unk020);
            if (player->unk004 == 0) {
                pitch->unk038 = fn_1_5B4(0x69B);
            }
            pitch->unk004 = 2;
            break;
        case 2:
            t = (float)pitch->unk006 / (float)lbl_1_data_344[1][pitch->unk020];
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            pitch->unk01C = 90.0f * t;
            if (pitch->unk006++ > lbl_1_data_344[1][pitch->unk020]) {
                pitch->unk006 = 0;
                pitch->unk004 = 3;
            }
            break;
        case 3:
            pitch->unk004 = 4;
            if (pitch->unk038 >= 0) {
                fn_1_5DC(pitch->unk038);
                pitch->unk038 = -1;
            }
        case 4:
            t = (float)pitch->unk006 / (float)lbl_1_data_344[2][pitch->unk020];
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            pitch->unk01C = 90.0f + 180.0f * t;
            if (pitch->unk006++ > lbl_1_data_344[2][pitch->unk020]) {
                pitch->unk006 = 0;
                pitch->unk004 = 5;
            }
            break;
        case 5:
            t = (float)pitch->unk006 / (float)lbl_1_data_344[3][pitch->unk020];
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            pitch->unk01C = 270.0f + 90.0f * t;
            if (pitch->unk006++ > lbl_1_data_344[3][pitch->unk020]) {
                pitch->unk006 = 0;
                pitch->unk004 = 0;
            }
            break;
    }
    pos = pitch->unk010;
    Hu3DModelPosSet(pitch->unk008, pos.x + lbl_1_data_320.x, pos.y + lbl_1_data_320.y, pos.z + lbl_1_data_320.z);
    Hu3DModelPosSet(pitch->unk00C, pos.x + lbl_1_data_32C.x, pos.y + lbl_1_data_32C.y, pos.z + lbl_1_data_32C.z);
    pitch->unk01C = (pitch->unk01C > 180.0f) ? pitch->unk01C - 360.0f : ((pitch->unk01C <= -180.0f) ? 360.0f + pitch->unk01C : pitch->unk01C);
    Hu3DModelRotSet(pitch->unk00C, pitch->unk01C, 0.0f, 0.0f);
    PSMTXRotRad(mtx, 'X', 0.017453292f * pitch->unk01C);
    PSMTXMultVec(mtx, &lbl_1_data_338, &pos);
    pitch->unk028.x = pitch->unk010.x + (pos.x + lbl_1_data_32C.x);
    pitch->unk028.y = pitch->unk010.y + (pos.y + lbl_1_data_32C.y);
    pitch->unk028.z = pitch->unk010.z + (pos.z + lbl_1_data_32C.z);
}
