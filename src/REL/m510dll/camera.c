/*
 * m510dll camera.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/camera.s.
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
#include "game/printfunc.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x258 */ /* s32 lbl_1_rodata_258[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x264 */ /* s32 lbl_1_rodata_264[3] = { 0x43BE0000, 0x45E42000, 0x46E91600 }; */
/* 0x270 */ /* s32 lbl_1_rodata_270[3] = { 0x43BE0000, 0x42D00000, 0x43C80000 }; */
/* 0x27C */ /* float lbl_1_rodata_27C = 0.4f; */
/* 0x280 */ /* float lbl_1_rodata_280 = 2.0f; */
/* 0x284 */ /* float lbl_1_rodata_284 = 400.0f; */
/* 0x288 */ /* float lbl_1_rodata_288 = 100000.0f; */
/* 0x28C */ /* float lbl_1_rodata_28C = 1.2f; */
/* 0x290 */ /* float lbl_1_rodata_290 = 0.0f; */
/* 0x294 */ /* float lbl_1_rodata_294 = 640.0f; */
/* 0x298 */ /* float lbl_1_rodata_298 = 480.0f; */
/* 0x29C */ /* float lbl_1_rodata_29C = 1.0f; */
/* 0x2A0 */ /* s32 lbl_1_rodata_2A0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2AC */ /* float lbl_1_rodata_2AC = 59.0f; */
/* 0x2B0 */ /* float lbl_1_rodata_2B0 = 0.1f; */
/* 0x2B4 */ /* float lbl_1_rodata_2B4 = 0.05f; */
/* 0x2B8 */ /* float lbl_1_rodata_2B8 = 0.2f; */
/* 0x2BC */ /* float lbl_1_rodata_2BC = 90.0f; */
/* 0x2C0 */ /* float lbl_1_rodata_2C0 = 0.02f; */
/* 0x2C4 */ /* float lbl_1_rodata_2C4 = 50.0f; */
/* 0x2C8 */ /* float lbl_1_rodata_2C8 = 1.5f; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 4503601774854144; */

/* --- .data --- */
/* 0x3D0 */ float lbl_1_data_3D0 = 2.0f;
/* 0x3D4 */ char lbl_1_data_3D4[] = "PX:%f";
/* 0x3DA */ char lbl_1_data_3DA[] = "PY:%f";
/* 0x3E0 */ char lbl_1_data_3E0[] = "PZ:%f";
/* 0x3E6 */ char lbl_1_data_3E6[] = "IX:%f";
/* 0x3EC */ char lbl_1_data_3EC[] = "IY:%f";
/* 0x3F2 */ char lbl_1_data_3F2[] = "IZ:%f";
/* 0x3F8 */ char lbl_1_data_3F8[] = "FOVY:%f";

/* --- functions (reference order) --- */
/* 89 insns */
void fn_1_89B8(M510_CAMERA *cam, M510_WORK *work)
{
    memset(cam, 0, sizeof(M510_CAMERA));
    cam->unk000 = work;
    cam->unk004 = 1;
    fn_1_8B1C(cam, cam->unk004);
    cam->unk054 = (HuVecF) { 0.0f, 1.0f, 0.0f };
    cam->unk00C = cam->unk018 = (HuVecF) { 380.0f, 7300.0f, 29835.0f };
    cam->unk024 = cam->unk030 = (HuVecF) { 380.0f, 104.0f, 400.0f };
    cam->unk060 = 0.4f;
}

/* 52 insns */
void fn_1_8B1C(M510_CAMERA *cam, s32 camBit)
{
    Hu3DCameraCreate(camBit);
    Hu3DCameraPerspectiveSet(camBit, 2.0f, 400.0f, 100000.0f, 1.2f);
    Hu3DCameraViewportSet(camBit, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(camBit, 0, 0, 640, 480);
}

/* 12 insns */
void fn_1_8BEC(M510_CAMERA *cam)
{
    memset(cam, 0, sizeof(M510_CAMERA));
}

/* 75 insns */
void fn_1_8C1C(M510_CAMERA *cam)
{
    M510_WORK *work = cam->unk000;
    OMOBJMAN *objman = work->unk000;
    HuVecF eyeD;
    HuVecF targetD;
    HuVecF eye;
    HuVecF target;

    PSVECSubtract(&cam->unk00C, &cam->unk018, &eyeD);
    PSVECSubtract(&cam->unk024, &cam->unk030, &targetD);
    PSVECScale(&eyeD, &eyeD, cam->unk060);
    PSVECScale(&targetD, &targetD, cam->unk060);
    PSVECAdd(&cam->unk018, &eyeD, &cam->unk018);
    PSVECAdd(&cam->unk030, &targetD, &cam->unk030);
    cam->unk03C = cam->unk048 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    PSVECAdd(&cam->unk018, &cam->unk03C, &eye);
    PSVECAdd(&cam->unk030, &cam->unk048, &target);
    Hu3DCameraPosSetV(cam->unk004, &eye, &cam->unk054, &target);
}

/* 533 insns */
void fn_1_8D48(M510_CAMERA *cam)
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
        if (HuPadBtn[0] & PAD_BUTTON_Y) {
            lbl_1_data_3D0 = (0.2f + lbl_1_data_3D0 > 90.0f) ? 90.0f : ((0.2f + lbl_1_data_3D0 < 0.0f) ? 0.0f : 0.2f + lbl_1_data_3D0);
            Hu3DCameraPerspectiveSet(cam->unk004, lbl_1_data_3D0, 400.0f, 100000.0f, 1.2f);
        }
        else if (HuPadBtn[0] & PAD_BUTTON_X) {
            lbl_1_data_3D0 = (lbl_1_data_3D0 - 0.2f > 90.0f) ? 90.0f : ((lbl_1_data_3D0 - 0.2f < 0.0f) ? 0.0f : lbl_1_data_3D0 - 0.2f);
            Hu3DCameraPerspectiveSet(cam->unk004, lbl_1_data_3D0, 400.0f, 100000.0f, 1.2f);
        }
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
    fontcolor = 3;
    print8(440, 336, 1.5f, lbl_1_data_3D4, cam->unk00C.x);
    print8(440, 348, 1.5f, lbl_1_data_3DA, cam->unk00C.y);
    print8(440, 360, 1.5f, lbl_1_data_3E0, cam->unk00C.z);
    print8(440, 372, 1.5f, lbl_1_data_3E6, cam->unk024.x);
    print8(440, 384, 1.5f, lbl_1_data_3EC, cam->unk024.y);
    print8(440, 396, 1.5f, lbl_1_data_3F2, cam->unk024.z);
    print8(440, 408, 1.5f, lbl_1_data_3F8, lbl_1_data_3D0);
}
