/*
 * m575dll camera.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/camera.s.
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
#include "game/esprite.h"
#include "game/printfunc.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x328 */ /* s32 lbl_1_rodata_328[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x334 */ /* s32 lbl_1_rodata_334[3] = { 0x00000000, 0x44AB4000, 0x449EC000 }; */
/* 0x340 */ /* s32 lbl_1_rodata_340[3] = { 0x00000000, 0x43480000, 0x00000000 }; */
/* 0x34C */ /* float lbl_1_rodata_34C = 0.4f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 45.0f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 20.0f; */
/* 0x358 */ /* float lbl_1_rodata_358 = 80000.0f; */
/* 0x35C */ /* float lbl_1_rodata_35C = 1.2f; */
/* 0x360 */ /* float lbl_1_rodata_360 = 0.0f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 640.0f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 480.0f; */
/* 0x36C */ /* float lbl_1_rodata_36C = 1.0f; */
/* 0x370 */ /* s32 lbl_1_rodata_370[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x37C */ /* s32 lbl_1_rodata_37C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x388 */ /* float lbl_1_rodata_388 = 0.25f; */
/* 0x390 */ /* double lbl_1_rodata_390 = 3; */
/* 0x398 */ /* double lbl_1_rodata_398 = 3.141592653589793; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 360.0f; */
/* 0x3A8 */ /* double lbl_1_rodata_3A8 = 180; */
/* 0x3B0 */ /* double lbl_1_rodata_3B0 = 4503601774854144; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = 576.0f; */
/* 0x3BC */ /* float lbl_1_rodata_3BC = 240.0f; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = 59.0f; */
/* 0x3C4 */ /* float lbl_1_rodata_3C4 = 0.1f; */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 0.05f; */
/* 0x3CC */ /* float lbl_1_rodata_3CC = 0.02f; */
/* 0x3D0 */ /* float lbl_1_rodata_3D0 = 50.0f; */
/* 0x3D4 */ /* float lbl_1_rodata_3D4 = 1.5f; */

/* --- .data --- */
/* 0x278 */ s32 lbl_1_data_278[8] = { 0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080 };
/* 0x298 */ char lbl_1_data_298[] = "PX:%f";
/* 0x29E */ char lbl_1_data_29E[] = "PY:%f";
/* 0x2A4 */ char lbl_1_data_2A4[] = "PZ:%f";
/* 0x2AA */ char lbl_1_data_2AA[] = "IX:%f";
/* 0x2B0 */ char lbl_1_data_2B0[] = "IY:%f";
/* 0x2B6 */ char lbl_1_data_2B6[] = "IZ:%f";

/* --- functions (reference order) --- */
/* 99 insns; m504 camera fn_1_C4F4 / m510 fn_1_89B8 shape. lbl_1_data_278 is read at idx*4
   (slwi 2; slwi 2): idx 0 -> bit 1, idx 1 -> bit 0x10 */
void fn_1_851C(M575_CAMERA *cam, s32 idx, M575_TEAM *game)
{
    memset(cam, 0, sizeof(M575_CAMERA));
    cam->unk000 = game;
    cam->unk004 = lbl_1_data_278[idx * 4];
    fn_1_86A8(cam, cam->unk004);
    cam->unk054 = (HuVecF) { 0.0f, 1.0f, 0.0f };
    cam->unk00C = cam->unk018 = (HuVecF) { 0.0f, 1370.0f, 1270.0f };
    cam->unk024 = cam->unk030 = (HuVecF) { 0.0f, 200.0f, 0.0f };
    cam->unk060 = 0.4f;
    if (idx != 0) {
        Hu3DCameraScissorSet(cam->unk004, 0, 0, 0, 0);
    }
}

/* 52 insns */
void fn_1_86A8(M575_CAMERA *cam, s32 camBit)
{
    Hu3DCameraCreate(camBit);
    Hu3DCameraPerspectiveSet(camBit, 45.0f, 20.0f, 80000.0f, 1.2f);
    Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(camBit, 0, 0, 640, 480);
}

/* 12 insns; m510 pad fn_1_8778 exact */
void fn_1_8778(M575_CAMERA *cam)
{
    memset(cam, 0, sizeof(M575_CAMERA));
}

/* 140 insns */
void fn_1_87A8(M575_CAMERA *cam)
{
    M575_TEAM *game = cam->unk000;
    M575_WORK *work = game->unk000;
    HuVecF eyeD;
    HuVecF targetD;
    HuVecF eye;
    HuVecF target;
    float shake;

    PSVECSubtract(&cam->unk00C, &cam->unk018, &eyeD);
    PSVECSubtract(&cam->unk024, &cam->unk030, &targetD);
    PSVECScale(&eyeD, &eyeD, cam->unk060);
    PSVECScale(&targetD, &targetD, cam->unk060);
    PSVECAdd(&cam->unk018, &eyeD, &cam->unk018);
    PSVECAdd(&cam->unk030, &targetD, &cam->unk030);
    if (cam->unk064 != 0) {
        shake = (work->unk008 % 4) / 4.0f;
        shake = 3.0 * sin(M_PI * (360.0f * shake) / 180.0);
        cam->unk03C = cam->unk048 = (HuVecF) { shake, shake, 0.0f };
    }
    else {
        cam->unk03C = cam->unk048 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    }
    PSVECAdd(&cam->unk018, &cam->unk03C, &eye);
    PSVECAdd(&cam->unk030, &cam->unk048, &target);
    Hu3DCameraPosSetV(cam->unk004, &eye, &cam->unk054, &target);
}

/* 164 insns: split screen, cam on the left (1 - t), cam2 on the right (t) */
void fn_1_89D8(M575_CAMERA *cam, M575_CAMERA *cam2, float t)
{
    M575_TEAM *game = cam->unk000;
    M575_WORK *work = game->unk000;

    espDispOn(work->unk2602);
    espPosSet(work->unk2602, 576.0f * (1.0f - t), 240.0f);
    Hu3DCameraPerspectiveSet(cam->unk004, 45.0f, 20.0f, 80000.0f, (576.0f * (1.0f - t)) / 480.0f);
    Hu3DCameraViewportSet(cam->unk004, 0.0f, 0.0f, 640.0f * (1.0f - t), 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(cam->unk004, 0, 0, 640.0f * (1.0f - t), 480);
    Hu3DCameraPerspectiveSet(cam2->unk004, 45.0f, 20.0f, 80000.0f, (576.0f * t) / 480.0f);
    Hu3DCameraViewportSet(cam2->unk004, 640.0f * (1.0f - t), 0.0f, 640.0f * t, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(cam2->unk004, 640.0f * (1.0f - t), 0, 640.0f * t, 480);
}

/* 378 insns: debug camera (m510 camera fn_1_8D48 without the FOV keys) */
void fn_1_8C68(M575_CAMERA *cam)
{
    float dist;
    HuVecF dir;
    HuVecF target;
    Mtx rotY;
    Mtx rotX;
    float stkX;
    float stkY;
    float scale;

    target = cam->unk030;
    PSVECSubtract(&cam->unk018, &cam->unk030, &dir);
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
        cam->unk00C = target;
        cam->unk018 = cam->unk00C;
        cam->unk030 = cam->unk024;
    }
    else if (!(HuPadBtn[0] & PAD_BUTTON_TRIGGER_L) && (HuPadBtn[0] & PAD_BUTTON_TRIGGER_R)) {
        stkY = -(HuPadSubStkY[0] / 59.0f);
        scale = 1.0f + 0.02f * stkY;
        PSVECScale(&dir, &dir, scale);
        PSVECAdd(&dir, &target, &target);
        cam->unk00C = target;
        cam->unk018 = cam->unk00C;
        cam->unk030 = cam->unk024;
    }
    else if ((HuPadBtn[0] & PAD_BUTTON_TRIGGER_L) && (HuPadBtn[0] & PAD_BUTTON_TRIGGER_R)) {
        stkX = HuPadSubStkX[0] / 59.0f;
        stkY = HuPadSubStkY[0] / 59.0f;
        stkX *= 50.0f;
        stkY *= 50.0f;
        cam->unk00C.x += stkX;
        cam->unk00C.y += stkY;
        cam->unk024.x += stkX;
        cam->unk024.y += stkY;
    }
    fontcolor = 1;
    print8(40, 336, 1.5f, lbl_1_data_298, cam->unk00C.x);
    print8(40, 348, 1.5f, lbl_1_data_29E, cam->unk00C.y);
    print8(40, 360, 1.5f, lbl_1_data_2A4, cam->unk00C.z);
    print8(40, 372, 1.5f, lbl_1_data_2AA, cam->unk024.x);
    print8(40, 384, 1.5f, lbl_1_data_2B0, cam->unk024.y);
    print8(40, 396, 1.5f, lbl_1_data_2B6, cam->unk024.z);
}
