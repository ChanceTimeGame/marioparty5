/*
 * m504dll camera.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/camera.s.
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x318 */ /* s32 lbl_1_rodata_318[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x324 */ /* s32 lbl_1_rodata_324[3] = { 0x00000000, 0x44FA0000, 0x00000000 }; */
/* 0x330 */ /* s32 lbl_1_rodata_330[3] = { 0x00000000, 0x43FA0000, 0x00000000 }; */
/* 0x33C */ /* float lbl_1_rodata_33C = 0.4f; */
/* 0x340 */ /* float lbl_1_rodata_340 = 0.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 640.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 480.0f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 1.0f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 20.0f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 30000.0f; */
/* 0x358 */ /* float lbl_1_rodata_358 = 1.2f; */
/* 0x35C */ /* s32 lbl_1_rodata_35C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x368 */ /* double lbl_1_rodata_368 = 3.141592653589793; */
/* 0x370 */ /* double lbl_1_rodata_370 = 180; */
/* 0x378 */ /* float lbl_1_rodata_378[2] = { 90.0f, 0.0f }; */

/* --- .data --- */
/* 0x45E0 */ s32 lbl_1_data_45E0[4] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008 };

/* --- functions (reference order) --- */
/* 69 insns */
u16 fn_1_C3E0(M504_COM *com)
{
    u16 wait = 0;

    switch (com->unk014) {
        case 0:
            wait = rand8() % 3;
            break;
        case 1:
            wait = rand8() % 5;
            break;
        case 2:
            wait = (rand8() % 20) + 30;
            break;
        case 3:
            wait = (rand8() % 20) + 30;
            break;
    }
    return wait;
}

/* 86 insns */
void fn_1_C4F4(M504_CAMERA *camera, s32 idx, M504_LANE *lane)
{
    memset(camera, 0, sizeof(M504_CAMERA));
    camera->unk000 = lane;
    camera->unk004 = lbl_1_data_45E0[idx];
    fn_1_C64C(camera, camera->unk004);
    camera->unk054 = (HuVecF) { 0.0f, 0.0f, -1.0f };
    camera->unk00C = (HuVecF) { 0.0f, 2000.0f, 0.0f };
    camera->unk024 = (HuVecF) { 0.0f, 500.0f, 0.0f };
    camera->unk060 = 0.4f;
    if (idx != 0) {
        Hu3DCameraScissorSet(camera->unk004, 0, 0, 0, 0);
    }
}

/* 52 insns */
void fn_1_C64C(M504_CAMERA *camera, s32 camBit)
{
    Hu3DCameraCreate(camBit);
    Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(camBit, 20.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraScissorSet(camBit, 0, 0, 640, 480);
}

/* 12 insns */
void fn_1_C71C(M504_CAMERA *camera)
{
    memset(camera, 0, sizeof(M504_CAMERA));
}

/* 49 insns */
void fn_1_C74C(M504_CAMERA *camera)
{
    HuVecF eyeD;
    HuVecF targetD;
    HuVecF eye;
    HuVecF target;

    PSVECSubtract(&camera->unk00C, &camera->unk024, &eyeD);
    PSVECSubtract(&camera->unk018, &camera->unk030, &targetD);
    PSVECScale(&eyeD, &eyeD, camera->unk060);
    PSVECScale(&targetD, &targetD, camera->unk060);
    PSVECAdd(&camera->unk024, &eyeD, &camera->unk024);
    PSVECAdd(&camera->unk030, &targetD, &camera->unk030);
    fn_1_C810(camera);
    PSVECAdd(&camera->unk024, &camera->unk03C, &eye);
    PSVECAdd(&camera->unk030, &camera->unk048, &target);
    Hu3DCameraPosSetV(camera->unk004, &eye, &camera->unk054, &target);
}

/* 99 insns */
void fn_1_C810(M504_CAMERA *camera)
{
    float shake;

    if (camera->unk068 != 0) {
        shake = camera->unk06C * sin(M_PI * camera->unk078 / 180.0);
        camera->unk078 += camera->unk074;
        camera->unk06C *= camera->unk070;
        if (camera->unk064 == 0 || camera->unk064 == 3) {
            camera->unk03C.x = shake;
            camera->unk048.x = shake;
        }
        else if (camera->unk064 == 1 || camera->unk064 == 3) {
            camera->unk03C.y = shake;
            camera->unk048.y = shake;
        }
        else if (camera->unk064 == 2 || camera->unk064 == 3) {
            camera->unk03C.z = shake;
            camera->unk048.z = shake;
        }
        if (--camera->unk068 == 0) {
            camera->unk03C = camera->unk048 = (HuVecF) { 0.0f, 0.0f, 0.0f };
            camera->unk06C = camera->unk070 = camera->unk074 = camera->unk078 = 0.0f;
        }
    }
}

/* 10 insns */
void fn_1_C99C(M504_CAMERA *camera, u16 axis, s32 frames, float amp, float decay, float speed)
{
    camera->unk064 = axis;
    camera->unk068 = frames;
    camera->unk06C = amp;
    camera->unk070 = decay;
    camera->unk074 = speed;
    camera->unk078 = 90.0f;
}

/* 1 insns */
void fn_1_C9C4(void) { }

/* 93 insns */
HuVecF fn_1_C9C8(float t, HuVecF *from, HuVecF *to)
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
void fn_1_CB3C(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    camera->unk054 = *up;
    camera->unk00C = camera->unk024 = camera->unk080 = *eye;
    camera->unk018 = camera->unk030 = camera->unk08C = *target;
}

/* 21 insns */
void fn_1_CBE8(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target, float *rate)
{
    camera->unk054 = *up;
    camera->unk00C = *eye;
    camera->unk018 = *target;
    camera->unk060 = *rate;
}

/* 19 insns */
void fn_1_CC3C(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    camera->unk054 = *up;
    camera->unk080 = *eye;
    camera->unk08C = *target;
}

/* 23 insns */
void fn_1_CC88(M504_CAMERA *camera, HuVecF *eye, HuVecF *up, HuVecF *target)
{
    camera->unk054 = *up;
    camera->unk098 = *eye;
    camera->unk0A4 = *target;
    camera->unk07C = 0.0f;
}

/* 2 insns */
void fn_1_CCE4(M504_CAMERA *camera, float t)
{
    camera->unk07C = t;
}

/* 212 insns */
s32 fn_1_CCEC(M504_CAMERA *camera, float frames, HuVecF *up)
{
    HuVecF eye;
    HuVecF target;

    camera->unk07C += 1.0f / frames;
    eye = fn_1_C9C8(camera->unk07C, &camera->unk080, &camera->unk098);
    target = fn_1_C9C8(camera->unk07C, &camera->unk08C, &camera->unk0A4);
    camera->unk054 = *up;
    camera->unk00C = camera->unk024 = eye;
    camera->unk018 = camera->unk030 = target;
    if (1.0f <= camera->unk07C) {
        return 1;
    }
    return 0;
}
