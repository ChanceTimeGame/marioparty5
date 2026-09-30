/*
 * m562dll camera.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/camera.s.
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
/* 0x960 lbl_1_rodata_960 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x96C lbl_1_rodata_96C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x978 lbl_1_rodata_978 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x984 lbl_1_rodata_984 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_990 = 0.0f; /* 0x990 */
static const float lbl_1_rodata_994 = 0.4f; /* 0x994 */
/* 0x998 lbl_1_rodata_998 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_9A4 = 45.0f; /* 0x9A4 */
static const float lbl_1_rodata_9A8 = 20.0f; /* 0x9A8 */
static const float lbl_1_rodata_9AC = 50000.0f; /* 0x9AC */
static const float lbl_1_rodata_9B0 = 1.2f; /* 0x9B0 */
static const float lbl_1_rodata_9B4 = 640.0f; /* 0x9B4 */
static const float lbl_1_rodata_9B8 = 480.0f; /* 0x9B8 */
static const float lbl_1_rodata_9BC = 1.0f; /* 0x9BC */
/* 0x9C0 lbl_1_rodata_9C0 (0x10): 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_9D0 = 3.141592653589793; /* 0x9D0 */
static const double lbl_1_rodata_9D8 = 180.0; /* 0x9D8 */
/* 0x9E0 lbl_1_rodata_9E0 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x9EC lbl_1_rodata_9EC (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_9F8 = 5.0f; /* 0x9F8 */
/* 0x9FC lbl_1_rodata_9FC (0xC): 0x00000000 0x447A0000 0x44AF0000 -- an aggregate initialiser, write it as a local */
/* 0xA08 lbl_1_rodata_A08 (0xC): 0x00000000 0x42C80000 0xC3480000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A14 = 1400.0f; /* 0xA14 */
static const float lbl_1_rodata_A18 = 0.25f; /* 0xA18 */
static const float lbl_1_rodata_A1C = 0.5f; /* 0xA1C */
static const float lbl_1_rodata_A20 = 200.0f; /* 0xA20 */
/* 0xA24 lbl_1_rodata_A24 (0xC): 0x00000000 0x44480000 0x44AF0000 -- an aggregate initialiser, write it as a local */
/* 0xA30 lbl_1_rodata_A30 (0xC): 0x00000000 0x42C80000 0xC3480000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A3C = 0.8f; /* 0xA3C */
static const float lbl_1_rodata_A40 = 0.6f; /* 0xA40 */
static const float lbl_1_rodata_A44 = 90.0f; /* 0xA44 */
static const float lbl_1_rodata_A48 = 59.0f; /* 0xA48 */
static const float lbl_1_rodata_A4C = 0.1f; /* 0xA4C */
static const float lbl_1_rodata_A50 = 0.05f; /* 0xA50 */
static const float lbl_1_rodata_A54 = 0.2f; /* 0xA54 */
static const float lbl_1_rodata_A58 = 0.02f; /* 0xA58 */
static const float lbl_1_rodata_A5C = 50.0f; /* 0xA5C */
static const float lbl_1_rodata_A60 = 1.5f; /* 0xA60 */
/* 0xA68 lbl_1_rodata_A68 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- functions (reference order), .data placed before its first user --- */

/* 133 insns */
void fn_1_20CE0(M562_CAMERA *camera, s32 camBit, s32 viewF, M562_WORK *work)
{
    memset(camera, 0, sizeof(M562_CAMERA));
    camera->unk00 = work;
    camera->unk04 = camBit;
    camera->unk0A = camera->unk0C = 0;
    fn_1_20EF4(camera, camera->unk04);
    camera->unk70 = (HuVecF) { 0.0f, 1.0f, 0.0f };
    camera->unk10 = camera->unk34 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    camera->unk1C = camera->unk40 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    camera->unk28 = camera->unk4C = (HuVecF) { 0.0f, 0.0f, -1.0f };
    if (viewF == 0) {
        Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    }
    camera->unk7C = 0.4f;
}

/* 78 insns */
void fn_1_20EF4(M562_CAMERA *camera, s32 camBit)
{
    Hu3DCameraCreate(camBit);
    Hu3DCameraPerspectiveSet(camBit, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(camBit, 0, 0, 640, 480);
    camera->unk58 = camera->unk64 = (HuVecF) { 0.0f, 0.0f, 0.0f };
}

/* 12 insns */
void fn_1_2102C(M562_CAMERA *camera)
{
    memset(camera, 0, sizeof(M562_CAMERA));
}

/* 38 insns */
void fn_1_2105C(M562_CAMERA *camera)
{
    M562_WORK *work = camera->unk00;

    switch (camera->unk0A) {
        case 0:
            fn_1_21280(camera);
            break;
        case 1:
            fn_1_21344(camera);
            break;
        case 2:
            fn_1_21700(camera);
            break;
        case 3:
            fn_1_2191C(camera);
            break;
    }
    fn_1_210F4(camera);
    camera->unk0C = camera->unk0A;
}

/* 99 insns */
void fn_1_210F4(M562_CAMERA *camera)
{
    float shake;

    if (camera->unk88 != 0) {
        shake = camera->unk8C * sin(M_PI * camera->unk98 / 180.0);
        camera->unk98 += camera->unk94;
        camera->unk8C *= camera->unk90;
        if (camera->unk84 == 0 || camera->unk84 == 3) {
            camera->unk58.x = shake;
            camera->unk64.x = shake;
        }
        else if (camera->unk84 == 1 || camera->unk84 == 3) {
            camera->unk58.y = shake;
            camera->unk64.y = shake;
        }
        else if (camera->unk84 == 2 || camera->unk84 == 3) {
            camera->unk58.z = shake;
            camera->unk64.z = shake;
        }
        if (--camera->unk88 == 0) {
            camera->unk58 = camera->unk64 = (HuVecF) { 0.0f, 0.0f, 0.0f };
            camera->unk8C = camera->unk90 = camera->unk94 = camera->unk98 = 0.0f;
        }
    }
}

/* 49 insns */
void fn_1_21280(M562_CAMERA *camera)
{
    M562_WORK *work = camera->unk00;
    HuVecF eyeD;
    HuVecF targetD;
    HuVecF eye;
    HuVecF target;

    PSVECSubtract(&camera->unk10, &camera->unk34, &eyeD);
    PSVECSubtract(&camera->unk1C, &camera->unk40, &targetD);
    PSVECScale(&eyeD, &eyeD, camera->unk7C);
    PSVECScale(&targetD, &targetD, camera->unk7C);
    PSVECAdd(&camera->unk34, &eyeD, &camera->unk34);
    PSVECAdd(&camera->unk40, &targetD, &camera->unk40);
    PSVECAdd(&camera->unk34, &camera->unk58, &eye);
    PSVECAdd(&camera->unk40, &camera->unk64, &target);
    Hu3DCameraPosSetV(camera->unk04, &eye, &camera->unk70, &target);
}

/* 239 insns */
void fn_1_21344(M562_CAMERA *camera)
{
    M562_WORK *work = camera->unk00;
    float mag;
    float dist;
    HuVecF eyeD;
    HuVecF eye;
    HuVecF target;
    Quaternion quatStart;
    Quaternion quatEnd;
    Quaternion quat;
    HuVecF dir;
    HuVecF side;
    HuVecF up;
    HuVecF front;
    Mtx mtx;

    if (camera->unk0C != 1) {
        PSVECSubtract(&camera->unk40, &camera->unk34, &dir);
        PSVECNormalize(&dir, &camera->unk4C);
        PSVECSubtract(&camera->unk1C, &camera->unk10, &dir);
        PSVECNormalize(&dir, &camera->unk28);
    }
    PSVECSubtract(&camera->unk40, &camera->unk34, &dir);
    dist = PSVECMag(&dir);
    PSVECSubtract(&camera->unk10, &camera->unk34, &eyeD);
    PSVECScale(&eyeD, &eyeD, camera->unk7C);
    PSVECAdd(&camera->unk34, &eyeD, &camera->unk34);
    front.x = camera->unk4C.x;
    front.y = camera->unk4C.y;
    front.z = camera->unk4C.z;
    up = (HuVecF) { 0.0f, 1.0f, 0.0f };
    PSVECCrossProduct(&front, &up, &side);
    PSVECCrossProduct(&front, &side, &up);
    mtx[0][0] = side.x;
    mtx[1][0] = side.y;
    mtx[2][0] = side.z;
    mtx[0][1] = up.x;
    mtx[1][1] = up.y;
    mtx[2][1] = up.z;
    mtx[0][2] = front.x;
    mtx[1][2] = front.y;
    mtx[2][2] = front.z;
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    C_QUATMtx(&quatStart, mtx);
    front.x = camera->unk28.x;
    front.y = camera->unk28.y;
    front.z = camera->unk28.z;
    up = (HuVecF) { 0.0f, 1.0f, 0.0f };
    PSVECCrossProduct(&front, &up, &side);
    PSVECCrossProduct(&front, &side, &up);
    mtx[0][0] = side.x;
    mtx[1][0] = side.y;
    mtx[2][0] = side.z;
    mtx[0][1] = up.x;
    mtx[1][1] = up.y;
    mtx[2][1] = up.z;
    mtx[0][2] = front.x;
    mtx[1][2] = front.y;
    mtx[2][2] = front.z;
    mtx[0][3] = 0.0f;
    mtx[1][3] = 0.0f;
    mtx[2][3] = 0.0f;
    C_QUATMtx(&quatEnd, mtx);
    C_QUATSlerp(&quatStart, &quatEnd, &quat, camera->unk80);
    PSMTXQuat(mtx, &quat);
    camera->unk4C.x = mtx[0][2];
    camera->unk4C.y = mtx[1][2];
    camera->unk4C.z = mtx[2][2];
    PSVECScale(&camera->unk4C, &dir, dist);
    mag = PSVECMag(&dir);
    if (mag > 5.0f) {
        if (mag < 20.0f) {
            PSVECScale(&dir, &dir, 20.0f / mag);
        }
        PSVECAdd(&camera->unk34, &dir, &camera->unk40);
    }
    PSVECAdd(&camera->unk34, &camera->unk58, &eye);
    PSVECAdd(&camera->unk40, &camera->unk64, &target);
    Hu3DCameraPosSetV(camera->unk04, &eye, &camera->unk70, &target);
}

/* 135 insns */
void fn_1_21700(M562_CAMERA *camera)
{
    M562_WORK *work = camera->unk00;
    M562_PLAYER *player = &work->player;
    HuVecF dir;

    switch (camera->unk08) {
        case 0:
            camera->unk10 = camera->unk34 = (HuVecF) { 0.0f, 1000.0f, 1400.0f };
            camera->unk1C = camera->unk40 = (HuVecF) { 0.0f, 100.0f, -200.0f };
            camera->unk08++;
        case 1:
            camera->unk10.z = 1400.0f + 0.25f * player->unk0A0.z;
            camera->unk1C.z = 0.5f * player->unk0A0.z - 200.0f;
            fn_1_21280(camera);
            break;
    }
    PSVECSubtract(&camera->unk40, &camera->unk34, &dir);
    PSVECNormalize(&dir, &dir);
    fn_1_904(&camera->unk34, &dir);
}

/* 147 insns */
void fn_1_2191C(M562_CAMERA *camera)
{
    M562_WORK *work = camera->unk00;
    M562_PLAYER *player = &work->player;
    HuVecF dir;

    switch (camera->unk08) {
        case 0:
            camera->unk10 = camera->unk34 = (HuVecF) { 0.0f, 800.0f, 1400.0f };
            camera->unk1C = camera->unk40 = (HuVecF) { 0.0f, 100.0f, -200.0f };
            camera->unk08++;
        case 1:
            camera->unk10.x = 0.8f * player->unk0A0.x;
            camera->unk1C.x = 0.6f * player->unk0A0.x;
            camera->unk10.z = 1400.0f + 0.25f * player->unk0A0.z;
            camera->unk1C.z = 0.5f * player->unk0A0.z - 200.0f;
            fn_1_21280(camera);
            break;
    }
    PSVECSubtract(&camera->unk40, &camera->unk34, &dir);
    PSVECNormalize(&dir, &dir);
    fn_1_904(&camera->unk34, &dir);
}

/* 16 insns */
void fn_1_21B68(M562_CAMERA *camera, u16 type, s32 time, float power, float f2, float f3)
{
    camera->unk84 = type;
    if (camera->unk88 < time) {
        camera->unk88 = time;
    }
    if (camera->unk8C < power) {
        camera->unk8C = power;
    }
    camera->unk90 = f2;
    camera->unk94 = f3;
    camera->unk98 = 90.0f;
}

/* 0xAE0 */ float lbl_1_data_AE0 = 45.0f;
/* 0xAE4 */ char lbl_1_data_AE4[] = "PX:%f";
/* 0xAEA */ char lbl_1_data_AEA[] = "PY:%f";
/* 0xAF0 */ char lbl_1_data_AF0[] = "PZ:%f";
/* 0xAF6 */ char lbl_1_data_AF6[] = "IX:%f";
/* 0xAFC */ char lbl_1_data_AFC[] = "IY:%f";
/* 0xB02 */ char lbl_1_data_B02[] = "IZ:%f";
/* 0xB08 */ char lbl_1_data_B08[] = "FOVY:%f";

/* 613 insns: pad-driven debug camera (unreferenced in retail) */
void fn_1_21BA8(M562_CAMERA *camera)
{
    float dist;
    HuVecF dir;
    HuVecF target;
    Mtx rotY;
    Mtx rotX;
    float stkX;
    float stkY;
    float moveX;
    float scale;

    target = camera->unk40;
    PSVECSubtract(&camera->unk34, &camera->unk40, &dir);
    dist = PSVECMag(&dir);
    if ((HuPadBtn[0] & PAD_BUTTON_TRIGGER_L) && !(HuPadBtn[0] & PAD_BUTTON_TRIGGER_R)) {
        stkX = HuPadSubStkX[0] / 59.0f;
        stkY = -(HuPadSubStkY[0] / 59.0f);
        stkX = (((stkX >= 0.0f) ? stkX : -stkX) < 0.1f) ? 0.0f : stkX;
        stkY = (((stkY >= 0.0f) ? stkY : -stkY) < 0.1f) ? 0.0f : stkY;
        PSMTXRotRad(rotY, 'Y', 0.05f * stkX);
        PSMTXRotRad(rotX, 'X', 0.05f * stkY);
        PSMTXMultVec(rotY, &dir, &dir);
        PSMTXMultVec(rotX, &dir, &dir);
        PSVECAdd(&dir, &target, &target);
        camera->unk10 = target;
        camera->unk34 = camera->unk10;
        camera->unk40 = camera->unk1C;
        if (HuPadBtn[0] & PAD_BUTTON_Y) {
            lbl_1_data_AE0 = (0.2f + lbl_1_data_AE0 > 90.0f) ? 90.0f : ((0.2f + lbl_1_data_AE0 < 0.0f) ? 0.0f : 0.2f + lbl_1_data_AE0);
            Hu3DCameraPerspectiveSet(camera->unk04, lbl_1_data_AE0, 20.0f, 50000.0f, 1.2f);
        }
        else if (HuPadBtn[0] & PAD_BUTTON_X) {
            lbl_1_data_AE0 = (lbl_1_data_AE0 - 0.2f > 90.0f) ? 90.0f : ((lbl_1_data_AE0 - 0.2f < 0.0f) ? 0.0f : lbl_1_data_AE0 - 0.2f);
            Hu3DCameraPerspectiveSet(camera->unk04, lbl_1_data_AE0, 20.0f, 50000.0f, 1.2f);
        }
    }
    else if (!(HuPadBtn[0] & PAD_BUTTON_TRIGGER_L) && (HuPadBtn[0] & PAD_BUTTON_TRIGGER_R)) {
        stkY = -(HuPadSubStkY[0] / 59.0f);
        scale = 1.0f + 0.02f * stkY;
        PSVECScale(&dir, &dir, scale);
        PSVECAdd(&dir, &target, &target);
        camera->unk10 = target;
        camera->unk34 = camera->unk10;
        camera->unk40 = camera->unk1C;
    }
    else if ((HuPadBtn[0] & PAD_BUTTON_TRIGGER_L) && (HuPadBtn[0] & PAD_BUTTON_TRIGGER_R)) {
        moveX = HuPadSubStkX[0] / 59.0f;
        stkY = HuPadSubStkY[0] / 59.0f;
        moveX *= 50.0f;
        stkY *= 50.0f;
        camera->unk10.z += moveX;
        camera->unk10.y += stkY;
        camera->unk1C.z += moveX;
        camera->unk1C.y += stkY;
    }
    fontcolor = 1;
    print8(442, 338, 1.5f, lbl_1_data_AE4, camera->unk10.x);
    print8(442, 350, 1.5f, lbl_1_data_AEA, camera->unk10.y);
    print8(442, 362, 1.5f, lbl_1_data_AF0, camera->unk10.z);
    print8(442, 374, 1.5f, lbl_1_data_AF6, camera->unk1C.x);
    print8(442, 386, 1.5f, lbl_1_data_AFC, camera->unk1C.y);
    print8(442, 398, 1.5f, lbl_1_data_B02, camera->unk1C.z);
    print8(442, 410, 1.5f, lbl_1_data_B08, lbl_1_data_AE0);
    fontcolor = 7;
    print8(440, 336, 1.5f, lbl_1_data_AE4, camera->unk10.x);
    print8(440, 348, 1.5f, lbl_1_data_AEA, camera->unk10.y);
    print8(440, 360, 1.5f, lbl_1_data_AF0, camera->unk10.z);
    print8(440, 372, 1.5f, lbl_1_data_AF6, camera->unk1C.x);
    print8(440, 384, 1.5f, lbl_1_data_AFC, camera->unk1C.y);
    print8(440, 396, 1.5f, lbl_1_data_B02, camera->unk1C.z);
    print8(440, 408, 1.5f, lbl_1_data_B08, lbl_1_data_AE0);
}
