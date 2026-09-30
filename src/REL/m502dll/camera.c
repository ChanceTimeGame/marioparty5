/*
 * m502dll camera.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/camera.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

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
/* 0x28 */ /* s32 lbl_1_rodata_28[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x34 */ /* s32 lbl_1_rodata_34[3] = { 0x00000000, 0x00000000, 0x44FA0000 }; */
/* 0x40 */ /* s32 lbl_1_rodata_40[3] = { 0x00000000, 0x00000000, 0x43FA0000 }; */
/* 0x4C */ /* float lbl_1_rodata_4C = 0.1f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 0.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 640.0f; */
/* 0x58 */ /* float lbl_1_rodata_58 = 480.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 1.0f; */
/* 0x60 */ /* float lbl_1_rodata_60 = 20.0f; */
/* 0x64 */ /* float lbl_1_rodata_64 = 30000.0f; */
/* 0x68 */ /* float lbl_1_rodata_68 = 1.2f; */
/* 0x70 */ /* double lbl_1_rodata_70 = 3.141592653589793; */
/* 0x78 */ /* float lbl_1_rodata_78 = 90.0f; */
/* 0x80 */ /* double lbl_1_rodata_80 = 180; */

/* --- .data --- */
/* 0xB60 */ s32 lbl_1_data_B60[8] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080 };

/* --- functions (reference order) --- */
/* 88 insns */
void fn_1_1830(M502_CAMERA *cam, s32 idx, M502_PLAYER *player)
{
    memset(cam, 0, sizeof(M502_CAMERA));
    cam->unk000 = player;
    cam->unk004 = lbl_1_data_B60[idx];
    cam->unk008 = lbl_1_data_B60[idx + 4];
    fn_1_1990(cam, cam->unk004);
    fn_1_1990(cam, cam->unk008);
    cam->unk040 = (HuVecF) { 0.0f, 1.0f, 0.0f };
    cam->unk010 = (HuVecF) { 0.0f, 0.0f, 2000.0f };
    cam->unk028 = (HuVecF) { 0.0f, 0.0f, 500.0f };
    cam->unk04C = 0.1f;
}

/* 52 insns */
void fn_1_1990(M502_CAMERA *cam, s32 camBit)
{
    Hu3DCameraCreate(camBit);
    Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(camBit, 20.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraScissorSet(camBit, 0, 0, 640, 480);
}

/* 12 insns */
void fn_1_1A60(M502_CAMERA *cam)
{
    memset(cam, 0, sizeof(M502_CAMERA));
}

/* 44 insns */
void fn_1_1A90(M502_CAMERA *cam)
{
    HuVecF eyeD;
    HuVecF targetD;

    PSVECSubtract(&cam->unk010, &cam->unk028, &eyeD);
    PSVECSubtract(&cam->unk01C, &cam->unk034, &targetD);
    PSVECScale(&eyeD, &eyeD, cam->unk04C);
    PSVECScale(&targetD, &targetD, cam->unk04C);
    PSVECAdd(&cam->unk028, &eyeD, &cam->unk028);
    PSVECAdd(&cam->unk034, &targetD, &cam->unk034);
    Hu3DCameraPosSetV(cam->unk004, &cam->unk028, &cam->unk040, &cam->unk034);
    Hu3DCameraPosSetV(cam->unk008, &cam->unk028, &cam->unk040, &cam->unk034);
}

/* 93 insns */
HuVecF fn_1_1B40(float t, HuVecF *from, HuVecF *to)
{
    HuVecF out;
    float w;

    if (1.0f < t) {
        t = 1.0f;
    }
    w = sin(M_PI * (90.0f * t) / 180.0) * sin(M_PI * (90.0f * t) / 180.0);
    out.x = from->x + w * (to->x - from->x);
    out.y = from->y + w * (to->y - from->y);
    out.z = from->z + w * (to->z - from->z);
    return out;
}

/* 43 insns */
void fn_1_1CB4(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    cam->unk040 = *up;
    cam->unk010 = cam->unk028 = cam->unk054 = *eye;
    cam->unk01C = cam->unk034 = cam->unk060 = *target;
}

/* 21 insns */
void fn_1_1D60(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target, float *rate)
{
    cam->unk040 = *up;
    cam->unk010 = *eye;
    cam->unk01C = *target;
    cam->unk04C = *rate;
}

/* 19 insns */
void fn_1_1DB4(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    cam->unk040 = *up;
    cam->unk054 = *eye;
    cam->unk060 = *target;
}

/* 23 insns */
void fn_1_1E00(M502_CAMERA *cam, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    cam->unk040 = *up;
    cam->unk06C = *eye;
    cam->unk078 = *target;
    cam->unk050 = 0.0f;
}

/* 2 insns */
void fn_1_1E5C(M502_CAMERA *cam, float t)
{
    cam->unk050 = t;
}

/* 212 insns */
int fn_1_1E64(M502_CAMERA *cam, float frames, HuVecF *up)
{
    HuVecF eye;
    HuVecF target;

    cam->unk050 += 1.0f / frames;
    eye = fn_1_1B40(cam->unk050, &cam->unk054, &cam->unk06C);
    target = fn_1_1B40(cam->unk050, &cam->unk060, &cam->unk078);
    cam->unk040 = *up;
    cam->unk010 = cam->unk028 = eye;
    cam->unk01C = cam->unk034 = target;
    if (1.0f <= cam->unk050) {
        return 1;
    }
    return 0;
}

/* 1 insns */
void fn_1_21B4(void) { }
