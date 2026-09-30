/*
 * m504dll opening.c -- written 2026-09-23 (fork O, batch 2). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/opening.s.
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

void *memset(); /* unprototyped on GC: fn_1_E14C passes lbl_1_bss_7870 BY VALUE (0xE1C8) */

#define M504_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m504, n), HU_MEMNUM_OVL, HEAP_MODEL)

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3F8 */ /* s32 lbl_1_rodata_3F8[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0x404 */ /* s32 lbl_1_rodata_404[3] = { 0x00000000, 0x42340000, 0x00000000 }; */
/* 0x410 */ /* s32 lbl_1_rodata_410[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x41C */ /* s32 lbl_1_rodata_41C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x428 */ /* s32 lbl_1_rodata_428[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x434 */ /* s32 lbl_1_rodata_434[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x440 */ /* s32 lbl_1_rodata_440[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x44C */ /* s32 lbl_1_rodata_44C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x458 */ /* s32 lbl_1_rodata_458[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x464 */ /* s32 lbl_1_rodata_464[3] = { 0x00000000, 0x00000000, 0x40C00000 }; */
/* 0x470 */ /* s32 lbl_1_rodata_470[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x47C */ /* s32 lbl_1_rodata_47C[3] = { 0x00000000, 0x00000000, 0x40C00000 }; */
/* 0x488 */ /* s32 lbl_1_rodata_488[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x494 */ /* s32 lbl_1_rodata_494[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x4A0 */ /* s32 lbl_1_rodata_4A0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x4AC */ /* s32 lbl_1_rodata_4AC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x4B8 */ /* s32 lbl_1_rodata_4B8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x4C4 */ /* float lbl_1_rodata_4C4 = 0.0f; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 0.3f; */
/* 0x4CC */ /* float lbl_1_rodata_4CC = 4.0f; */
/* 0x4D0 */ /* float lbl_1_rodata_4D0 = 10.0f; */
/* 0x4D4 */ /* float lbl_1_rodata_4D4 = 1.0f; */
/* 0x4D8 */ /* float lbl_1_rodata_4D8 = 700.0f; */
/* 0x4DC */ /* float lbl_1_rodata_4DC = 640.0f; */
/* 0x4E0 */ /* float lbl_1_rodata_4E0 = 480.0f; */
/* 0x4E4 */ /* float lbl_1_rodata_4E4 = 60.0f; */
/* 0x4E8 */ /* float lbl_1_rodata_4E8 = 80.0f; */
/* 0x4EC */ /* float lbl_1_rodata_4EC = 20.0f; */
/* 0x4F0 */ /* float lbl_1_rodata_4F0 = 2.0f; */
/* 0x4F4 */ /* float lbl_1_rodata_4F4 = 0.6f; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = 0.01f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = 90.0f; */
/* 0x500 */ /* double lbl_1_rodata_500 = 3.141592653589793; */
/* 0x508 */ /* double lbl_1_rodata_508 = 180; */
/* 0x510 */ /* float lbl_1_rodata_510 = 50.0f; */
/* 0x514 */ /* float lbl_1_rodata_514 = 15.0f; */
/* 0x518 */ /* float lbl_1_rodata_518 = 30.0f; */
/* 0x51C */ /* float lbl_1_rodata_51C = 240.0f; */
/* 0x520 */ /* float lbl_1_rodata_520 = 0.2f; */
/* 0x524 */ /* float lbl_1_rodata_524 = 70.0f; */
/* 0x528 */ /* float lbl_1_rodata_528 = 1.08f; */
/* 0x52C */ /* float lbl_1_rodata_52C = 35.0f; */
/* 0x530 */ /* float lbl_1_rodata_530 = 25.0f; */
/* 0x534 */ /* float lbl_1_rodata_534 = 0.95f; */
/* 0x538 */ /* float lbl_1_rodata_538 = 100.0f; */
/* 0x53C */ /* float lbl_1_rodata_53C = 200.0f; */
/* 0x540 */ /* float lbl_1_rodata_540 = 150.0f; */
/* 0x548 */ /* double lbl_1_rodata_548 = 1; */
/* 0x550 */ /* float lbl_1_rodata_550 = 5.0f; */
/* 0x558 */ /* double lbl_1_rodata_558 = 200; */
/* 0x560 */ /* float lbl_1_rodata_560 = 1.2f; */
/* 0x568 */ /* double lbl_1_rodata_568 = 80; */
/* 0x570 */ /* float lbl_1_rodata_570 = 180.0f; */
/* 0x574 */ /* float lbl_1_rodata_574 = 7.5f; */
/* 0x578 */ /* float lbl_1_rodata_578 = 320.0f; */
/* 0x57C */ /* float lbl_1_rodata_57C = 45.0f; */
/* 0x580 */ /* double lbl_1_rodata_580 = 10; */
/* 0x588 */ /* float lbl_1_rodata_588 = 8.0f; */
/* 0x58C */ /* float lbl_1_rodata_58C = 360.0f; */
/* 0x590 */ /* double lbl_1_rodata_590 = 100; */
/* 0x598 */ /* float lbl_1_rodata_598 = 144.0f; */
/* 0x5A0 */ /* double lbl_1_rodata_5A0 = 4503601774854144; */
/* 0x5A8 */ /* double lbl_1_rodata_5A8 = 4503599627370496; */
/* 0x5B0 */ /* float lbl_1_rodata_5B0 = -20.0f; */
/* 0x5B8 */ /* double lbl_1_rodata_5B8 = 0; */
/* 0x5C0 */ /* double lbl_1_rodata_5C0 = 0.5; */
/* 0x5C8 */ /* double lbl_1_rodata_5C8 = 3; */
/* 0x5D0 */ /* float lbl_1_rodata_5D0 = 270.0f; */
/* 0x5D8 */ /* double lbl_1_rodata_5D8 = 360; */

/* --- .data --- */
/* 0x4648 */ HuVecF lbl_1_data_4648 = { 0.0f, 0.0f, 100.0f }; /* lane 0 player start */
/* 0x4654 */ HuVecF lbl_1_data_4654 = { 0.0f, 180.0f, 0.0f }; /* lane 0 player start rotation */
/* 0x4660 */ HuVecF lbl_1_data_4660 = { 220.0f, 0.0f, 250.0f }; /* player walk-off goal */
/* 0x466C */ HuVecF lbl_1_data_466C = { 0.0f, -120.0f, 0.0f };
/* 0x4678 */ HuVecF lbl_1_data_4678 = { 0.0f, 0.0f, -6e+02f }; /* chomp start */
/* 0x4684 */ HuVecF lbl_1_data_4684 = { 0.0f, 0.0f, -100.0f };
/* 0x4690 */ HuVecF lbl_1_data_4690 = { 0.0f, 0.0f, 100.0f };
/* 0x469C */ HuVecF lbl_1_data_469C = { 0.0f, 0.0f, 0.0f };
/* 0x46A8 */ HuVecF lbl_1_data_46A8 = { 0.0f, 0.0f, 0.0f };
/* 0x46B4 */ HuVecF lbl_1_data_46B4 = { 0.0f, 18.0f, 2e+02f };
/* 0x46C0 */ HuVecF lbl_1_data_46C0 = { 9e+01f, 0.0f, 0.0f };
/* 0x46CC */ HuVecF lbl_1_data_46CC[10] = { { -1.5e+02f, 5e+01f, -5e+02f }, { 5e+01f, 2e+02f, -7e+02f }, { 2.3e+02f, 1.5e+02f, -5e+02f }, { -4e+02f, 1e+02f, -6e+02f }, { -2.5e+02f, 2e+02f, -7e+02f }, { -2e+02f, 1.5e+02f, -5e+02f }, { 2.5e+02f, 5e+01f, -5e+02f }, { 3e+02f, 2e+02f, -7e+02f }, { 3.5e+02f, 1.5e+02f, -5e+02f }, { 2e+02f, 3e+02f, -7e+02f } };
/* 0x4744 */ HuVecF lbl_1_data_4744[10] = { { 3e+01f, 15.0f, 0.0f }, { 3e+01f, -5.0f, 0.0f }, { 3e+01f, -15.0f, 0.0f }, { 3e+01f, 15.0f, 0.0f }, { 3e+01f, 1e+01f, 0.0f }, { 3e+01f, 5.0f, 0.0f }, { 3e+01f, -5.0f, 0.0f }, { 3e+01f, -1e+01f, 0.0f }, { 3e+01f, -15.0f, 0.0f }, { 3e+01f, -1e+01f, 0.0f } };
/* 0x47BC */ HuVecF lbl_1_data_47BC[10] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } };
/* 0x4834 */ HuVecF lbl_1_data_4834 = { 0.0f, 432.0f, 522.0f };
/* 0x4840 */ HuVecF lbl_1_data_4840 = { 0.0f, 332.0f, 1481.0f };
/* 0x484C */ HuVecF lbl_1_data_484C = { 0.0f, 1.8e+03f, 1.25e+03f };
/* 0x4858 */ HuVecF lbl_1_data_4858[2] = { { 0.0f, 1e+02f, -6e+02f }, { 0.0f, 0.0f, 3e+02f } };
/* 0x4870 */ HuVecF lbl_1_data_4870 = { 0.0f, 2e+02f, 2.5e+02f };
/* 0x487C */ HuVecF lbl_1_data_487C = { 0.0f, 8000.0f, 1500.0f }; /* shadow camera position */
/* 0x4888 */ HuVecF lbl_1_data_4888 = { 0.0f, 1.0f, 0.0f }; /* shadow camera up */
/* 0x4894 */ HuVecF lbl_1_data_4894 = { 0.0f, 0.0f, 0.0f }; /* shadow camera target */
/* 0x48A0 jumptable_1_data_48A0: the switch in fn_1_E14C (10 cases) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7A04 gap_05_00007A04_bss (0x4) -- dtk filler */
/* 0x7A00 */ float lbl_1_bss_7A00; /* split-screen width */
/* 0x79FC */ float lbl_1_bss_79FC; /* split-screen height */
/* 0x7870 */ M504_OPENING lbl_1_bss_7870;
/* 0x7848 */ float lbl_1_bss_7848[10]; /* per-flyer x drift */

/* --- functions (reference order) --- */
/* 2792 insns. The opening: returns 1 when done. */
s32 fn_1_E14C(M504_WORK *work)
{
    Mtx mtx;
    HuVecF vec;
    float time;
    float maxTime;
    float c;
    float s;
    M504_PLAYER *player;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    M504_CAMERA *camera;
    s16 *modelId;
    s32 i;
    s32 t;
    s32 result;
    M504_WANWAN *ww;
    M504_WANWAN *ww2;
    s16 model;

    player = &work->unk040[0].unk008;
    stage = &work->unk040[0].unk15C;
    wanwan = &work->unk040[0].unk0DC;
    camera = &work->unk040[0].unk3BC;
    modelId = work->unk012;
    result = 0;
    fn_1_11088();
    switch (work->unk00A) {
    case 0:
        memset(lbl_1_bss_7870, 0, sizeof(lbl_1_bss_7870));
        work->unk1230 = fn_1_76C(0x4D);
        wanwan->unk05C.z = 0.0f;
        work->unk1218 = 1;
        for (i = 0; i < 10; i++) {
            if (i % 3 == 0) {
                model = Hu3DModelCreate(M504_DATA(0x1F));
                lbl_1_bss_7870.unk010[i] = model;
            } else if (i % 3 == 1) {
                model = Hu3DModelCreate(M504_DATA(0x20));
                lbl_1_bss_7870.unk010[i] = model;
            } else {
                model = Hu3DModelCreate(M504_DATA(0x21));
                lbl_1_bss_7870.unk010[i] = model;
            }
            Hu3DModelAttrReset(lbl_1_bss_7870.unk010[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_7870.unk010[i], HU3D_MOTATTR_LOOP);
            Hu3DModelPosSetV(lbl_1_bss_7870.unk010[i], &lbl_1_data_46CC[i]);
            Hu3DModelRotSetV(lbl_1_bss_7870.unk010[i], &lbl_1_data_4744[i]);
            Hu3DModelScaleSet(lbl_1_bss_7870.unk010[i], 0.3f, 0.3f, 0.3f);
            Hu3DModelCameraSet(lbl_1_bss_7870.unk010[i], lbl_1_data_45E0[0]);
            Hu3DMotionSpeedSet(lbl_1_bss_7870.unk010[i], 4.0f);
            Hu3DMotionTimeSet(lbl_1_bss_7870.unk010[i], 10.0f * i);
            Hu3DModelShadowSet(lbl_1_bss_7870.unk010[i]);
        }
        for (i = 0; i < 20; i++) {
            lbl_1_bss_7870.unk04C[i / 2] = 0;
            if (i < 10) {
                model = Hu3DModelCreate(M504_DATA(0x22));
                lbl_1_bss_7870.unk024[i] = model;
            } else {
                model = Hu3DModelCreate(M504_DATA(0x23));
                lbl_1_bss_7870.unk024[i] = model;
            }
            Hu3DModelAttrSet(lbl_1_bss_7870.unk024[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_7870.unk024[i], HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSet(lbl_1_bss_7870.unk024[i], 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(lbl_1_bss_7870.unk024[i], lbl_1_data_45E0[0]);
            Hu3DMotionSpeedSet(lbl_1_bss_7870.unk024[i], 1.0f);
            Hu3DMotionTimeSet(lbl_1_bss_7870.unk024[i], 0.0f);
        }
        for (i = 0; i < 4; i++) {
            omSetTra(work->unk040[i].unk008.unk018, lbl_1_data_4660.x, lbl_1_data_4660.y, lbl_1_data_4660.z);
            omSetRot(work->unk040[i].unk008.unk018, lbl_1_data_466C.x, lbl_1_data_466C.y, lbl_1_data_466C.z);
            Hu3DModelPosSetV(work->unk040[i].unk0DC.unk00C, &lbl_1_data_4690);
            work->unk040[i].unk3BC.unk018 = work->unk040[i].unk3BC.unk030 = lbl_1_data_4870;
            work->unk040[i].unk3BC.unk00C = work->unk040[i].unk3BC.unk024 = lbl_1_data_484C;
            lbl_1_data_487C.z = 700.0f + work->unk040[i].unk008.unk018->trans.z;
            lbl_1_data_4894.z = work->unk040[i].unk008.unk018->trans.z;
            Hu3DModelAttrSet(work->unk040[i].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DShadowMultiPosSet(&lbl_1_data_487C, &lbl_1_data_4888, &lbl_1_data_4894, lbl_1_data_45E0[i]);
            Hu3DModelAttrSet(work->unk040[i].unk15C.unk014, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk040[i].unk15C.unk014, HU3D_MOTATTR_LOOP);
            Hu3DModelPosSetV(work->unk040[i].unk15C.unk014, &lbl_1_data_46B4);
            Hu3DModelRotSetV(work->unk040[i].unk15C.unk014, &lbl_1_data_46C0);
        }
        Hu3DModelAttrReset(player->unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        camera->unk054 = (HuVecF) { 0.0f, 1.0f, 0.0f };
        camera->unk018 = camera->unk030 = lbl_1_data_4858[0];
        camera->unk00C = camera->unk024 = lbl_1_data_4834;
        wanwan->unk038 = lbl_1_data_4678;
        wanwan->unk044 = (HuVecF) { 0.0f, 45.0f, 0.0f };
        omSetTra(player->unk018, lbl_1_data_4648.x, lbl_1_data_4648.y, lbl_1_data_4648.z);
        omSetRot(player->unk018, lbl_1_data_4654.x, lbl_1_data_4654.y, lbl_1_data_4654.z);
        Hu3DMotionSet(wanwan->unk00C, wanwan->unk00E[8]);
        Hu3DModelAttrSet(wanwan->unk00C, HU3D_MOTATTR_LOOP);
        Hu3DMotionSpeedSet(wanwan->unk00C, 1.0f);
        Hu3DMotionTimeSet(wanwan->unk00C, 0.0f);
        Hu3DModelAttrSet(wanwan->unk00C, HU3D_MOTATTR_LOOP);
        Hu3DModelPosSetV(stage->unk014, &lbl_1_data_469C);
        Hu3DModelRotSetV(stage->unk014, &lbl_1_data_46A8);
        Hu3DModelAttrReset(stage->unk014, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(stage->unk014);
        lbl_1_bss_7A00 = 640.0f;
        lbl_1_bss_79FC = 480.0f;
        fn_1_10CEC(work, lbl_1_bss_7A00, lbl_1_bss_79FC);
        fn_1_CC3C(camera, &camera->unk024, &camera->unk054, &camera->unk030);
        fn_1_CC88(camera, &lbl_1_data_4840, &camera->unk054, &camera->unk030);
        Hu3DMotionShiftSet(player->unk018->mdlId[0], player->unk018->mtnId[7], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        work->unk010 = 0;
        work->unk00A++;
        break;
    case 1:
        lbl_1_bss_7870.unk000++;
        if (Hu3DMotionEndCheck(player->unk018->mdlId[0])) {
            Hu3DMotionShiftSet(player->unk018->mdlId[0], player->unk018->mtnId[8], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        }
        if (fn_1_CCEC(camera, 60.0f, &camera->unk054)) {
            Hu3DModelPosSet(player->unk0C8, 0.0f, 80.0f, 0.0f);
            Hu3DModelRotSet(player->unk0C8, 20.0f, 0.0f, 0.0f);
            Hu3DMotionTimeSet(player->unk0C8, 0.0f);
            Hu3DMotionSpeedSet(player->unk0C8, 2.0f);
            Hu3DModelAttrReset(player->unk0C8, HU3D_ATTR_DISPOFF);
            fn_1_5EC(0x65B);
            lbl_1_bss_7870.unk004 = 0;
            lbl_1_bss_7870.unk004 = 0;
            work->unk00A++;
        }
        break;
    case 2:
        lbl_1_bss_7870.unk000++;
        if (++lbl_1_bss_7870.unk004 >= 10) {
            Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[9], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            PSVECSubtract(&camera->unk030, &camera->unk024, &vec);
            PSVECScale(&vec, &vec, 0.6f);
            PSVECAdd(&camera->unk024, &vec, &camera->unk030);
            camera->unk018 = camera->unk030;
            wanwan->unk038.x = wanwan->unk038.y = 0.0f;
            lbl_1_bss_7870.unk000 = lbl_1_bss_7870.unk004 = 0;
            fn_1_11198(wanwan->unk038, (HuVecF) { 0.0f, 0.0f, 0.0f });
            fn_1_11360(wanwan->unk038, (HuVecF) { 0.0f, 0.0f, 0.0f });
            for (i = 0; i < 10; i++) {
                lbl_1_bss_7848[i] = 0.01f * lbl_1_data_46CC[i].x;
            }
            work->unk00A++;
        }
        if (lbl_1_bss_7870.unk004 == 4) {
            Hu3DModelAttrReset(player->unk0CC, HU3D_ATTR_DISPOFF);
            omVibrate(0, 15, 6, 6);
            omVibrate(1, 15, 6, 6);
            omVibrate(2, 15, 6, 6);
            omVibrate(3, 15, 6, 6);
        }
        break;
    case 3:
        if (Hu3DMotionEndCheck(player->unk0C8)) {
            Hu3DModelAttrSet(player->unk0C8, HU3D_ATTR_DISPOFF);
            work->unk00A++;
        }
        break;
    case 4:
        if (++lbl_1_bss_7870.unk000 >= 15) {
            lbl_1_bss_7870.unk000 = 0;
            work->unk00A++;
        }
        break;
    case 5:
        wanwan->unk044.y += 10.0f;
        if (wanwan->unk044.y > 0.0f) {
            Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            fn_1_CC3C(camera, &camera->unk024, &camera->unk054, &camera->unk030);
            fn_1_CC88(camera, &lbl_1_data_484C, &camera->unk054, &lbl_1_data_4870);
            wanwan->unk068 = 20.0f;
            wanwan->unk06C = 0.0f;
            wanwan->unk006 = 30;
            wanwan->unk044.y = 0.0f;
            lbl_1_bss_7870.unk000 = 0;
            fn_1_5EC(0x2D8);
            work->unk00A++;
        }
        break;
    case 6:
        wanwan->unk06C += 10.0f;
        if (wanwan->unk06C > 90.0f) {
            wanwan->unk06C = 0.0f;
        }
        c = cos(M_PI * wanwan->unk06C / 180.0);
        wanwan->unk044.x = wanwan->unk068 * c;
        wanwan->unk05C.z = 50.0f * c * cos(M_PI * wanwan->unk044.y / 180.0);
        if (wanwan->unk006 != 0) {
            wanwan->unk006--;
        }
        if (wanwan->unk006 == 0) {
            wanwan->unk044.x = wanwan->unk05C.z = 0.0f;
            wanwan->unk006 = 0;
            lbl_1_bss_7870.unk000 = 0;
            work->unk00A++;
        }
        break;
    case 7:
        lbl_1_bss_7870.unk000++;
        t = lbl_1_bss_7870.unk000 - 25;
        if (t < 0) {
            t = 0;
        }
        if (t > 30) {
            t = 30;
        }
        if (lbl_1_bss_7870.unk008 == 0) {
            if (t == 1) {
                Hu3DMotionShiftSet(player->unk018->mdlId[0], player->unk018->mtnId[11], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
            }
            if (t != 0) {
                player->unk018->rot.y -= 15.0f;
                if (player->unk018->rot.y < 60.0f) {
                    player->unk018->rot.y = 60.0f;
                }
            }
            if (t == 30) {
                for (i = 0; i < 4; i++) {
                    Hu3DMotionShiftSet(work->unk040[i].unk008.unk018->mdlId[0], work->unk040[i].unk008.unk018->mtnId[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                }
                lbl_1_bss_7870.unk008 = 1;
            }
            player->unk018->trans.x = lbl_1_data_4648.x + t * (lbl_1_data_4660.x - lbl_1_data_4648.x) / 30.0f;
            player->unk018->trans.z = lbl_1_data_4648.z + t * (lbl_1_data_4660.z - lbl_1_data_4648.z) / 30.0f;
        } else {
            player->unk018->rot.y += 10.0f;
            if (player->unk018->rot.y > 240.0f) {
                player->unk018->rot.y = 240.0f;
            }
        }
        t = lbl_1_bss_7870.unk000;
        if (t > 35) {
            t = 35;
        }
        if (lbl_1_bss_7870.unk00C == 0) {
            if (t >= 5 && (t - 5) % 3 == 0) {
                fn_1_11198((HuVecF) { 70.0f + wanwan->unk038.x, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 0.2f * (t - 5) });
                fn_1_11360((HuVecF) { wanwan->unk038.x - 70.0f, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 0.2f * (t - 5) });
            }
            if (t == 1) {
                fn_1_C99C(camera, 0, 60, 1.0f, 1.08f, 35.0f);
            }
            if (t == 20) {
                Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            }
            if (t == 35) {
                omVibrate(0, 30, 6, 6);
                omVibrate(1, 30, 6, 6);
                omVibrate(2, 30, 6, 6);
                omVibrate(3, 30, 6, 6);
                fn_1_C99C(camera, 0, 60, 25.0f, 0.95f, 90.0f);
                Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[7], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                vec = wanwan->unk038;
                vec.y = 100.0f;
                vec.x = 0.0f;
                vec.z = 200.0f;
                fn_1_5EC(0x648);
                Hu3DModelPosSet(wanwan->unk028, wanwan->unk038.x, 150.0f + wanwan->unk038.y, 150.0f + wanwan->unk038.z);
                Hu3DMotionTimeSet(wanwan->unk028, 0.0f);
                Hu3DModelAttrReset(wanwan->unk028, HU3D_ATTR_DISPOFF);
                lbl_1_bss_7870.unk00C = 1;
            }
        } else if (lbl_1_bss_7870.unk00C == 1) {
            if (Hu3DMotionEndCheck(wanwan->unk00C)) {
                for (i = 0; i < 4; i++) {
                    Hu3DMotionShiftSet(work->unk040[i].unk0DC.unk00C, work->unk040[i].unk0DC.unk00E[6], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                }
                lbl_1_bss_7870.unk00C = 2;
            }
        }
        if (lbl_1_bss_7870.unk00C == 0) {
            wanwan->unk038.z = lbl_1_data_4678.z + (lbl_1_data_4684.z - lbl_1_data_4678.z) * (1.0 - cos(M_PI * (90.0f * (t / 35.0f)) / 180.0));
        } else {
            t = lbl_1_bss_7870.unk000 - 35;
            if (t > 30) {
                t = 30;
            }
            if (t < 25 && t % 3 == 0) {
                fn_1_11198((HuVecF) { 70.0f + wanwan->unk038.x, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 6.0f });
                fn_1_11360((HuVecF) { wanwan->unk038.x - 70.0f, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 6.0f });
            }
            Hu3DModelPosSet(wanwan->unk028, wanwan->unk038.x, 200.0f + wanwan->unk038.y, (150.0f + wanwan->unk038.z) - 5.0f * t);
            if (Hu3DMotionEndCheck(wanwan->unk028)) {
                Hu3DModelAttrSet(wanwan->unk028, HU3D_ATTR_DISPOFF);
            }
            wanwan->unk038.z = lbl_1_data_4684.z + (lbl_1_data_4690.z - lbl_1_data_4684.z) * sin(M_PI * (90.0f * (t / 30.0f)) / 180.0);
        }
        if (lbl_1_bss_7870.unk000 >= 35) {
            t = lbl_1_bss_7870.unk000 - 35;
            if (t > 30) {
                t = 30;
            }
            Hu3DData[stage->unk014].pos.z = 200.0 * sin(M_PI * (90.0f * (t / 30.0f)) / 180.0);
            if (t > 15) {
                t = 15;
            }
            if (t == 14) {
                Hu3DModelShadowDispOff(stage->unk014);
            }
            Hu3DData[stage->unk014].pos.y = 1.2f * t + 80.0 * sin(M_PI * (180.0f * (t / 15.0f)) / 180.0);
            Hu3DData[stage->unk014].rot.x += 7.5f;
            if (Hu3DData[stage->unk014].rot.x > 90.0f) {
                Hu3DData[stage->unk014].rot.x = 90.0f;
            }
        }
        if (lbl_1_bss_7870.unk000 >= 65) {
            t = lbl_1_bss_7870.unk000 - 65;
            if (t % 2 != 0) {
                Hu3DModelAttrSet(stage->unk014, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(stage->unk014, HU3D_ATTR_DISPOFF);
            }
            if (t >= 30) {
                Hu3DModelAttrSet(stage->unk014, HU3D_ATTR_DISPOFF);
            }
        }
        if (fn_1_CCEC(camera, 90.0f, &camera->unk054)) {
            for (i = 0; i < 10; i++) {
                Hu3DModelAttrSet(lbl_1_bss_7870.unk010[i], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(lbl_1_bss_7870.unk010[i], HU3D_ATTR_DISPOFF);
                Hu3DModelKill(lbl_1_bss_7870.unk010[i]);
            }
            Hu3DModelAttrReset(work->unk040[0].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk040[1].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk040[2].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk040[3].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
            work->unk010 = 0;
            lbl_1_bss_7870.unk000 = 0;
            for (i = 1; i < 4; i++) {
                work->unk040[i].unk0DC.unk038 = work->unk040[0].unk0DC.unk038;
                work->unk040[i].unk0DC.unk044 = work->unk040[0].unk0DC.unk044;
                *(HuVecF *)&work->unk040[i].unk0DC.unk068 = *(HuVecF *)&work->unk040[0].unk0DC.unk068;
            }
            work->unk00A++;
        }
        if (lbl_1_bss_7870.unk000 == 45) {
            camera->unk054 = (HuVecF) { 0.0f, 0.0f, -1.0f };
        }
        break;
    case 8:
        work->unk010++;
        if (work->unk010 >= 45) {
            for (i = 0; i < 20; i++) {
                Hu3DModelAttrSet(lbl_1_bss_7870.unk024[i], HU3D_ATTR_DISPOFF);
            }
            work->unk00A++;
            work->unk010 = 45;
        }
        lbl_1_bss_7A00 = 640.0f - 320.0f * work->unk010 / 45.0f;
        lbl_1_bss_79FC = 480.0f - 240.0f * work->unk010 / 45.0f;
        fn_1_10CEC(work, lbl_1_bss_7A00, lbl_1_bss_79FC);
        break;
    case 9:
        work->unk1220 = -1;
        work->unk1218 = 0;
        work->unk00A++;
        break;
    default:
        work->unk00A = work->unk010 = 0;
        result = 1;
        break;
    }
    if (work->unk00A < 8 && result == 0) {
        maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_7870.unk010[0]);
        for (i = 0; i < 10; i++) {
            time = Hu3DMotionTimeGet(lbl_1_bss_7870.unk010[i]);
            if (time < 1.0f) {
                if (lbl_1_data_46CC[i].x < 0.0f) {
                    lbl_1_data_47BC[i].x = 4.0f * (rand8() % 6 - 3);
                } else {
                    lbl_1_data_47BC[i].x = 4.0f * (rand8() % 6 - 4);
                }
                if (lbl_1_data_46CC[i].y < 150.0f) {
                    lbl_1_data_47BC[i].y = 2.0f * (rand8() % 6 - 3);
                } else {
                    lbl_1_data_47BC[i].y = 2.0f * (rand8() % 6 - 4);
                }
                PSVECScale(&lbl_1_data_47BC[i], &lbl_1_data_47BC[i], 2.0f / maxTime);
            }
            PSVECAdd(&lbl_1_data_46CC[i], &lbl_1_data_47BC[i], &lbl_1_data_46CC[i]);
            if (work->unk00A >= 3) {
                lbl_1_data_46CC[i].x += lbl_1_bss_7848[i];
                lbl_1_data_46CC[i].z -= 1.0f;
                lbl_1_data_46CC[i].y += 1.0f;
            }
            s = 10.0 * sin(M_PI * (180.0f + 180.0f * time / maxTime) / 180.0);
            if (lbl_1_data_46CC[i].y < 20.0f) {
                lbl_1_data_46CC[i].y = 20.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_7870.unk010[i], lbl_1_data_46CC[i].x, s + lbl_1_data_46CC[i].y, lbl_1_data_46CC[i].z);
        }
    }
    if ((work->unk00A == 7 && lbl_1_bss_7870.unk00C >= 2) || work->unk00A >= 8) {
        for (i = 0; i < 4; i++) {
            ww = &work->unk040[i].unk0DC;
            Hu3DModelAttrReset(ww->unk00C, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrSet(ww->unk00C, HU3D_MOTATTR_REV);
            ww->unk06C += 8.0f;
            ww->unk068 = 10.0 * sin(M_PI * ww->unk06C / 180.0);
            ww->unk070 = 10.0 * cos(M_PI * ww->unk06C / 180.0);
            mtxRot(mtx, 0.0f, 360.0f - ww->unk078, ww->unk070);
            mtxRotCat(mtx, ww->unk068, 0.0f, 0.0f);
            fn_1_11548(mtx, &ww->unk044);
            ww->unk038.y = 0.0f;
        }
    }
    if (work->unk00A >= 1 && work->unk00A <= 2) {
        wanwan->unk044.y = 100.0 * sin(M_PI * (360.0f * ((lbl_1_bss_7870.unk000 + 36) % 144 / 144.0f)) / 180.0);
        wanwan->unk038.x = 100.0 * sin(M_PI * (360.0f * (lbl_1_bss_7870.unk000 % 144 / 144.0f)) / 180.0);
        if (lbl_1_bss_7870.unk000 % 10 == 0) {
            if (lbl_1_bss_7870.unk000 % 144 >= 36 && lbl_1_bss_7870.unk000 % 144 < 108) {
                fn_1_11198((HuVecF) { wanwan->unk038.x - 15.0f, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 0.0f });
            } else {
                fn_1_11360((HuVecF) { 15.0f + wanwan->unk038.x, wanwan->unk038.y, wanwan->unk038.z }, (HuVecF) { 0.0f, 0.0f, 0.0f });
            }
        }
    }
    for (i = 0; i < 4; i++) {
        ww2 = &work->unk040[i].unk0DC;
        Hu3DModelPosSet(ww2->unk00C, ww2->unk038.x, ww2->unk038.y, ww2->unk038.z + ww2->unk05C.z);
        Hu3DModelRotSetV(ww2->unk00C, &ww2->unk044);
    }
    return result;
}

/* 231 insns. Four-way split-screen viewports/scissors of size w x h (m507 fn_1_610C with a
   -20 viewport y offset for the bottom row); work is unused. */
void fn_1_10CEC(M504_WORK *work, float w, float h)
{
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, w - 1.0f, 20.0f + (h - 1.0f), 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, w - 1.0f, h - 1.0f);
    Hu3DCameraViewportSet(2, 2.0f + w, 0.0f, 640.0f - w, 20.0f + (h - 1.0f), 0.0f, 1.0f);
    Hu3DCameraScissorSet(2, 2.0f + w, 0, 640.0f - w, h - 1.0f);
    Hu3DCameraViewportSet(4, 0.0f, -20.0f + (2.0f + h), w - 1.0f, 20.0f + (480.0f - h), 0.0f, 1.0f);
    Hu3DCameraScissorSet(4, 0, 2.0f + h, w - 1.0f, 480.0f - h);
    Hu3DCameraViewportSet(8, 2.0f + w, -20.0f + (2.0f + h), 640.0f - w, 20.0f + (480.0f - h), 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 2.0f + w, 2.0f + h, 640.0f - w, 480.0f - h);
}

/* 68 insns. Moves the active dust puffs; hides each when its motion ends. */
void fn_1_11088(void)
{
    s32 i;

    for (i = 0; i < 20; i++) {
        if (lbl_1_bss_7870.unk04C[i]) {
            PSVECAdd(&Hu3DData[lbl_1_bss_7870.unk024[i]].pos, &lbl_1_bss_7870.unk09C[i], &Hu3DData[lbl_1_bss_7870.unk024[i]].pos);
            if (Hu3DMotionEndCheck(lbl_1_bss_7870.unk024[i])) {
                lbl_1_bss_7870.unk04C[i] = 0;
                Hu3DModelAttrSet(lbl_1_bss_7870.unk024[i], HU3D_ATTR_DISPOFF);
            }
        }
    }
}

/* 114 insns. Starts a free right-side dust puff [0..9] at pos with velocity vel. */
void fn_1_11198(HuVecF pos, HuVecF vel)
{
    s32 i;
    s32 ofs;

    for (i = 0; i < 10; i++) {
        if (lbl_1_bss_7870.unk04C[i] == 0) {
            lbl_1_bss_7870.unk04C[i] = 1;
            lbl_1_bss_7870.unk09C[i] = vel;
            ofs = rand8() % 30;
            Hu3DModelAttrReset(lbl_1_bss_7870.unk024[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_7870.unk024[i], HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSet(lbl_1_bss_7870.unk024[i], 10.0f + pos.x + ofs, 0.0f, pos.z);
            Hu3DMotionSpeedSet(lbl_1_bss_7870.unk024[i], 1.0f);
            Hu3DMotionTimeSet(lbl_1_bss_7870.unk024[i], 0.0f);
            break;
        }
    }
}

/* 122 insns. Starts a free left-side dust puff [10..19]. */
void fn_1_11360(HuVecF pos, HuVecF vel)
{
    s32 i;
    s32 ofs;

    for (i = 0; i < 10; i++) {
        if (lbl_1_bss_7870.unk04C[i + 10] == 0) {
            lbl_1_bss_7870.unk04C[i + 10] = 1;
            lbl_1_bss_7870.unk09C[i + 10] = vel;
            ofs = rand8() % 30;
            Hu3DModelAttrReset(lbl_1_bss_7870.unk024[i + 10], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_7870.unk024[i + 10], HU3D_MOTATTR_PAUSE);
            Hu3DModelPosSet(lbl_1_bss_7870.unk024[i + 10], pos.x - 10.0f - ofs, 0.0f, pos.z);
            Hu3DMotionTimeSet(lbl_1_bss_7870.unk024[i + 10], 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_7870.unk024[i + 10], 1.0f);
            break;
        }
    }
}

/* 232 insns. Matrix -> Euler angles (wanwan fn_1_AB40 twin). */
void fn_1_11548(Mtx mtx, HuVecF *rot)
{
    float z;
    float mag;

    rot->x = HuAtan(mtx[1][2], mtx[2][2]);
    if (rot->x < 0.0f) {
        rot->x += 360.0f;
    }
    rot->z = HuAtan(mtx[0][1], mtx[0][0]);
    if (rot->z < 0.0f) {
        rot->z += 360.0f;
    }
    z = -mtx[0][2];
    mag = sqrtf((1.0 - (z * z)) >= 0.0 ? (1.0 - (z * z)) : (-(1.0 - (z * z))));
    if ((rot->x > 90.0f) && (rot->x < 270.0f) && (rot->z > 90.0f) && (rot->z < 270.0f)) {
        rot->x = fmod(180.0f + rot->x, 360.0);
        rot->z = fmod(180.0f + rot->z, 360.0);
        mag = -mag;
    }
    rot->y = HuAtan(z, mag);
    if (rot->y < 0.0f) {
        rot->y += 360.0f;
    }
}
