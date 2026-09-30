/*
 * m502dll ending.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/ending.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

/* game/audio.h deliberately not included: HuAudAUXSet/HuAudAUXVolSet/CharFXPlay are called unprototyped (retail keeps the int result; no extsh on CharFXPlay args) */
#include "game/charman.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/wipe.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3C8 */ /* float lbl_1_rodata_3C8 = 0.0f; */
/* 0x3CC */ /* float lbl_1_rodata_3CC = 1000.0f; */
/* 0x3D0 */ /* float lbl_1_rodata_3D0 = 1.0f; */
/* 0x3D4 */ /* float lbl_1_rodata_3D4 = 1300.0f; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = -300.0f; */
/* 0x3DC */ /* float lbl_1_rodata_3DC = -45.0f; */
/* 0x3E0 */ /* float lbl_1_rodata_3E0 = 576.0f; */
/* 0x3E4 */ /* float lbl_1_rodata_3E4 = 240.0f; */
/* 0x3E8 */ /* float lbl_1_rodata_3E8 = 640.0f; */
/* 0x3EC */ /* float lbl_1_rodata_3EC = 480.0f; */
/* 0x3F0 */ /* float lbl_1_rodata_3F0 = 20.0f; */
/* 0x3F4 */ /* float lbl_1_rodata_3F4 = 30000.0f; */
/* 0x3F8 */ /* float lbl_1_rodata_3F8 = 1.2f; */
/* 0x3FC */ /* float lbl_1_rodata_3FC = 0.002f; */
/* 0x400 */ /* float lbl_1_rodata_400 = 0.01f; */
/* 0x404 */ /* float lbl_1_rodata_404 = 0.3f; */
/* 0x408 */ /* float lbl_1_rodata_408 = 30.0f; */
/* 0x40C */ /* float lbl_1_rodata_40C = 60.0f; */
/* 0x410 */ /* float lbl_1_rodata_410 = 120.0f; */
/* 0x414 */ /* float lbl_1_rodata_414 = 0.008f; */
/* 0x418 */ /* float lbl_1_rodata_418 = 2.0f; */
/* 0x41C */ /* float lbl_1_rodata_41C = 1700.0f; */
/* 0x420 */ /* float lbl_1_rodata_420 = 0.64f; */
/* 0x424 */ /* float lbl_1_rodata_424 = -200.0f; */
/* 0x428 */ /* float lbl_1_rodata_428 = -125.0f; */
/* 0x42C */ /* float lbl_1_rodata_42C = 40.0f; */
/* 0x430 */ /* float lbl_1_rodata_430 = 180.0f; */
/* 0x434 */ /* float lbl_1_rodata_434 = 0.5f; */
/* 0x438 */ /* float lbl_1_rodata_438 = 1.8f; */
/* 0x43C */ /* float lbl_1_rodata_43C = 3.5f; */
/* 0x440 */ /* float lbl_1_rodata_440 = -70.0f; */
/* 0x444 */ /* float lbl_1_rodata_444 = 3200.0f; */
/* 0x448 */ /* float lbl_1_rodata_448 = 0.75f; */
/* 0x44C */ /* float lbl_1_rodata_44C = 360.0f; */
/* 0x450 */ /* double lbl_1_rodata_450 = 3.141592653589793; */
/* 0x458 */ /* float lbl_1_rodata_458 = 100.0f; */
/* 0x460 */ /* double lbl_1_rodata_460 = 180; */
/* 0x468 */ /* float lbl_1_rodata_468 = 25.0f; */
/* 0x470 */ /* double lbl_1_rodata_470 = -100; */
/* 0x478 */ /* double lbl_1_rodata_478 = 75; */
/* 0x480 */ /* float lbl_1_rodata_480 = 0.025f; */
/* 0x488 */ /* double lbl_1_rodata_488 = 4503601774854144; */
/* 0x490 */ /* float lbl_1_rodata_490[2] = { 50.0f, 0.0f }; */

/* --- .data --- */
/* 0x1068 */ HuVecF lbl_1_data_1068 = { 0.0f, 4000.0f, 6476.0f };
/* 0x1074 */ HuVecF lbl_1_data_1074 = { 0.0f, 1.0f, 0.0f };
/* 0x1080 */ HuVecF lbl_1_data_1080 = { 13.0f, 2029.0f, -1070.0f };
/* 0x108C */ HuVecF lbl_1_data_108C = { 0.0f, 6544.0f, 6476.0f };
/* 0x1098 */ HuVecF lbl_1_data_1098 = { 0.0f, 1.0f, 0.0f };
/* 0x10A4 */ HuVecF lbl_1_data_10A4 = { 13.0f, 1829.0f, -1070.0f };
/* 0x10B0 */ HuVecF lbl_1_data_10B0 = { 156.0f, 5698.0f, 872.0f };
/* 0x10BC */ HuVecF lbl_1_data_10BC = { 0.0f, 1.0f, 0.0f };
/* 0x10C8 */ HuVecF lbl_1_data_10C8 = { -77.0f, 1388.0f, -800.0f };
/* 0x10D4 */ s16 lbl_1_data_10D4 = -1;
/* 0x10D8 */ HuVecF lbl_1_data_10D8 = { 0.0f, 4000.0f, 500.0f };
/* 0x10E4 */ HuVecF lbl_1_data_10E4 = { -0.25f, -1.0f, -0.5f };
/* 0x10F0 */ HuVecF lbl_1_data_10F0 = { 500.0f, 2500.0f, 500.0f };
/* 0x10FC */ HuVecF lbl_1_data_10FC = { -0.3f, 1.0f, -0.3f };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x508C gap_05_0000508C_bss (0x4) -- dtk filler */
/* 0x5088 */ float lbl_1_bss_5088;
/* 0x5084 */ float lbl_1_bss_5084;
/* 0x5080 */ float lbl_1_bss_5080;
/* 0x507C */ float lbl_1_bss_507C;
/* 0x5078 */ float lbl_1_bss_5078;
/* 0x5074 */ float lbl_1_bss_5074;
/* 0x5070 */ s32 lbl_1_bss_5070;
/* 0x506C */ s32 lbl_1_bss_506C;
/* 0x5068 */ s32 lbl_1_bss_5068;

/* --- functions (reference order) --- */
/* 1590 insns */
int fn_1_A914(M502_WORK *work)
{
    M502_CHAR *chr;
    M502_OPENING *opening;
    M502_WORKMODEL *scene;
    s32 i;
    s32 j;
    float time;
    float maxTime;
    M502_BLOCK *block[4];
    M502_STAGE *stage[4];

    chr = &work->unk3A4[work->unk5004].unkF58;
    opening = &work->unk380;
    scene = &work->unk01C;
    switch (work->unk00C) {
        case 0:
            lbl_1_data_10D4 = Hu3DLLightCreate(scene->unk000[120], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
            Hu3DLLightPointSet(scene->unk000[120], lbl_1_data_10D4, 1000.0f, 1.0f, GX_DA_GENTLE);
            Hu3DLLightPosSetV(scene->unk000[120], lbl_1_data_10D4, &lbl_1_data_10F0, &lbl_1_data_10FC);
            Hu3DLLightColorSet(scene->unk000[120], lbl_1_data_10D4, 0x80, 0x80, 0x80, 0xFF);
            Hu3DLLightStaticSet(scene->unk000[120], lbl_1_data_10D4, TRUE);
            Hu3DGLightPosSetV(work->unk378.unk004, &lbl_1_data_10D8, &lbl_1_data_10E4);
            fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_1068, &lbl_1_data_1074, &lbl_1_data_1080);
            chr->unk01C->trans.x = 0.0f;
            chr->unk01C->trans.y = 1300.0f;
            chr->unk01C->trans.z = -300.0f;
            chr->unk01C->rot.y = chr->unk01C->rot.z = 0.0f;
            chr->unk01C->rot.x = -45.0f;
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[5], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(chr->unk01C->mdlId[0], 0.0f);
            Hu3DMotionSpeedSet(chr->unk01C->mdlId[0], 0.0f);
            Hu3DModelAttrSet(work->unk3A4[0].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk3A4[1].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk3A4[2].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(work->unk3A4[3].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(chr->unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(chr->unk01C->mdlId[0], 5);
            Hu3DModelCameraSet(chr->unk01C->mdlId[0], lbl_1_data_B60[4]);
            for (i = 0; i < 4; i++) {
                stage[i] = &work->unk3A4[i].unkFD4;
                block[i] = &work->unk3A4[i].unk008;
                for (j = 0; j < 5; j++) {
                    Hu3DModelAttrSet(stage[i]->unk004[j], HU3D_ATTR_DISPOFF);
                }
            }
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 27; j++) {
                    Hu3DModelAttrSet(block[0]->unk004[i][j].unk01C, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(block[1]->unk004[i][j].unk01C, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(block[2]->unk004[i][j].unk01C, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(block[3]->unk004[i][j].unk01C, HU3D_ATTR_DISPOFF);
                }
            }
            espPosSet(opening->unk01C[0], 576.0f, 240.0f);
            espPosSet(opening->unk01C[1], 576.0f, 240.0f);
            espPosSet(opening->unk01C[2], 576.0f, 240.0f);
            Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
            Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f);
            Hu3DCameraScissorSet(1, 0, 0, 640, 480);
            Hu3DCameraViewportSet(16, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
            Hu3DCameraPerspectiveSet(16, 20.0f, 20.0f, 30000.0f, 1.2f);
            Hu3DCameraScissorSet(16, 0, 0, 640, 480);
            for (i = 1; i < 4; i++) {
                Hu3DCameraViewportSet(lbl_1_data_B60[i], 0.0f, 0.0f, 0.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraPerspectiveSet(lbl_1_data_B60[i], 20.0f, 20.0f, 30000.0f, 0.0f);
                Hu3DCameraScissorSet(lbl_1_data_B60[i], 0, 0, 0, 480);
                Hu3DCameraViewportSet(lbl_1_data_B60[i + 4], 0.0f, 0.0f, 0.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraPerspectiveSet(lbl_1_data_B60[i + 4], 20.0f, 20.0f, 30000.0f, 0.0f);
                Hu3DCameraScissorSet(lbl_1_data_B60[i + 4], 0, 0, 0, 480);
            }
            lbl_1_bss_507C = 0.0f;
            fn_1_3380(0.002f);
            Hu3DModelAttrSet(scene->unk000[119], HU3D_MOTATTR_SHAPE_LOOP);
            Hu3DMotionShapeSpeedSet(scene->unk000[119], lbl_1_bss_507C);
            Hu3DMotionShapeTimeSet(scene->unk000[119], 0.01f);
            Hu3DModelAttrReset(scene->unk000[119], HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(scene->unk000[119], lbl_1_data_B60[4]);
            Hu3DModelMatHookSet(scene->unk000[119], fn_1_3390);
            Hu3DModelLayerSet(scene->unk000[119], 1);
            Hu3DModelLayerSet(scene->unk000[120], 5);
            Hu3DModelAttrReset(scene->unk000[120], HU3D_ATTR_DISPOFF);
            HuAudAUXSet(0, 1);
            HuAudAUXVolSet(-1, -1);
            CharModelVoicePanSet(chr->unk014, 64);
            work->unk010 = 0;
            work->unk00C = 1;
            break;
        case 1:
            if (WipeCheckEnd()) {
                break;
            }
            if (work->unk501C >= 0) {
                fn_1_1C0(work->unk501C);
                work->unk501C = -1;
            }
            if (work->unk501C < 0) {
                work->unk501C = fn_1_198(0x3A1);
            }
            work->unk00C = 2;
            break;
        case 2:
            work->unk010++;
            if (work->unk010 >= 0.0f) {
                work->unk010 = 0;
                fn_1_1E00(&work->unk3A4[0].unk1048, &lbl_1_data_108C, &lbl_1_data_1098, &lbl_1_data_10A4);
                work->unk00C = 3;
            }
            break;
        case 3:
            work->unk010++;
            time = 0.3f * work->unk010;
            if (time > 20.0f) {
                time = 20.0f;
            }
            if (work->unk010 > 30.0f) {
                fn_1_1E64(&work->unk3A4[0].unk1048, 60.0f, &lbl_1_data_1098);
            }
            fn_1_C1EC(work, time);
            if (work->unk010 > 120.0f) {
                fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_108C, &lbl_1_data_1098, &lbl_1_data_10A4);
                work->unk00C = 4;
                work->unk010 = 0;
            }
            break;
        case 4:
            work->unk010++;
            fn_1_C1EC(work, 60.0f);
            if (work->unk010 >= 8) {
                work->unk00C = 5;
                work->unk010 = 0;
            }
            break;
        case 5:
            if (work->unk5020 >= 0) {
                fn_1_1C0(work->unk5020);
                work->unk5020 = -1;
            }
            if (work->unk501C >= 0) {
                fn_1_1C0(work->unk501C);
                work->unk501C = -1;
            }
            fn_1_198(0x633);
            if (work->unk501C < 0) {
                work->unk501C = fn_1_198(0x634);
            }
            Hu3DModelPosSet(scene->unk000[114], 0.0f, 0.0f, 0.0f);
            Hu3DModelRotSet(scene->unk000[114], 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(scene->unk000[114], lbl_1_data_B60[4]);
            Hu3DMotionSpeedSet(scene->unk000[114], 1.0f);
            Hu3DMotionTimeSet(scene->unk000[114], 0.01f);
            Hu3DModelLayerSet(scene->unk000[114], 5);
            Hu3DModelAttrReset(scene->unk000[114], HU3D_ATTR_DISPOFF);
            fn_1_3380(0.008f);
            lbl_1_bss_507C = 2.0f;
            Hu3DMotionShapeSpeedSet(scene->unk000[119], lbl_1_bss_507C);
            fn_1_1E00(&work->unk3A4[0].unk1048, &lbl_1_data_10B0, &lbl_1_data_10BC, &lbl_1_data_10C8);
            time = Hu3DMotionMaxTimeGet(scene->unk000[114]);
            lbl_1_bss_5080 = 1700.0f / time;
            work->unk010 = 0;
            work->unk00C = 6;
            break;
        case 6:
            fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_108C, &lbl_1_data_1098, &lbl_1_data_10A4);
            time = Hu3DData[scene->unk000[114]].motWork.time;
            maxTime = Hu3DMotionMaxTimeGet(scene->unk000[114]);
            if (time >= maxTime) {
                lbl_1_bss_5080 *= 0.64f;
                Hu3DModelAttrSet(scene->unk000[114], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(scene->unk000[115], 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(scene->unk000[115], 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(scene->unk000[115], lbl_1_data_B60[4]);
                Hu3DMotionShapeSpeedSet(scene->unk000[115], 1.0f);
                Hu3DMotionShapeTimeSet(scene->unk000[115], 0.01f);
                Hu3DModelAttrSet(scene->unk000[115], HU3D_MOTATTR_SHAPE_LOOP | HU3D_MOTATTR_LOOP);
                Hu3DModelLayerSet(scene->unk000[115], 5);
                Hu3DModelAttrReset(scene->unk000[115], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(scene->unk000[116], 0.0f, 0.0f, 0.0f);
                Hu3DModelRotSet(scene->unk000[116], 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(scene->unk000[116], lbl_1_data_B60[4]);
                Hu3DMotionShapeSpeedSet(scene->unk000[116], 1.0f);
                Hu3DMotionShapeTimeSet(scene->unk000[116], 0.01f);
                Hu3DModelLayerSet(scene->unk000[116], 5);
                Hu3DModelAttrSet(scene->unk000[116], HU3D_MOTATTR_SHAPE_LOOP | HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(scene->unk000[116], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(scene->unk000[117], 0.0f, -200.0f, 0.0f);
                Hu3DModelRotSet(scene->unk000[117], 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(scene->unk000[117], lbl_1_data_B60[4]);
                Hu3DMotionShapeSpeedSet(scene->unk000[117], 1.0f);
                Hu3DMotionShapeTimeSet(scene->unk000[117], 0.01f);
                Hu3DModelLayerSet(scene->unk000[117], 6);
                Hu3DModelAttrSet(scene->unk000[117], HU3D_MOTATTR_SHAPE_LOOP | HU3D_MOTATTR_LOOP);
                Hu3DModelLayerSet(chr->unk01C->mdlId[0], 7);
                lbl_1_bss_5078 = -125.0f;
                lbl_1_bss_5074 = 40.0f;
                lbl_1_bss_5070 = 180;
                lbl_1_bss_5088 = 180.0f;
                lbl_1_bss_5084 = 0.0f;
                work->unk010 = 0;
                work->unk00C = 7;
            }
            break;
        case 7:
            time = Hu3DData[scene->unk000[117]].motShapeWork.time;
            maxTime = Hu3DMotionShapeMaxTimeGet(scene->unk000[117]);
            if (time >= 1.0f + maxTime / 2.0f) {
                Hu3DModelPosSet(scene->unk000[118], 0.0f, -200.0f, 0.0f);
                Hu3DModelRotSet(scene->unk000[118], 0.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(scene->unk000[118], lbl_1_data_B60[4]);
                Hu3DMotionShapeSpeedSet(scene->unk000[118], 1.0f);
                Hu3DMotionShapeTimeSet(scene->unk000[118], 0.01f);
                Hu3DModelLayerSet(scene->unk000[118], 6);
                Hu3DModelAttrSet(scene->unk000[118], HU3D_MOTATTR_SHAPE_LOOP | HU3D_MOTATTR_LOOP);
                work->unk010 = 0;
                work->unk00C = 8;
            }
            break;
        case 8:
            break;
        case 9:
            if (++work->unk010 >= 210) {
                work->unk00C = 10;
                work->unk010 = 0;
                work->unk018 = -1;
            }
            break;
        case 10:
            work->unk010++;
            work->unk018 = -1;
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
            if (work->unk501C >= 0) {
                fn_1_1E8(work->unk501C, 1000);
                work->unk501C = -1;
            }
            work->unk00C = 11;
            break;
        case 11:
            if (WipeCheckEnd()) {
                break;
            }
            Hu3DLLightKill(scene->unk000[120], lbl_1_data_10D4);
            return 1;
    }
    if (work->unk00C >= 6 && work->unk00C <= 9) {
        lbl_1_bss_5078 += 1.8f;
        if (lbl_1_bss_5078 > 0.0f) {
            lbl_1_bss_5078 = 0.0f;
        }
        if (fn_1_1E64(&work->unk3A4[0].unk1048, 60.0f, &lbl_1_data_10BC)) {
            fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_10B0, &lbl_1_data_10BC, &lbl_1_data_10C8);
        }
    }
    if (work->unk00C == 6) {
        chr->unk01C->trans.y += lbl_1_bss_5080;
    } else if (work->unk00C > 6) {
        if (work->unk00C < 9) {
            lbl_1_bss_5080 -= 3.5f;
            if (lbl_1_bss_5080 < -70.0f) {
                lbl_1_bss_5080 = -70.0f;
            }
            chr->unk01C->trans.y += lbl_1_bss_5080;
            if (chr->unk01C->trans.y < 3200.0f && lbl_1_bss_5080 < 0.0f) {
                Hu3DMotionSpeedSet(chr->unk01C->mdlId[0], 1.0f);
                work->unk018 = GameMesMgWinnerCreate(chr->unk014, -1, -1, -1);
                chr->unk01C->trans.y = 3200.0f;
                work->unk010 = 0;
                work->unk00C = 9;
                lbl_1_bss_5080 = 0.0f;
                work->unk5020 = CharFXPlay(chr->unk014, 0x1FA);
                work->unk5018 = fn_1_340(0x79);
            }
        } else {
            lbl_1_bss_5080 *= 0.75f;
            lbl_1_bss_5070++;
            maxTime = Hu3DMotionMaxTimeGet(scene->unk000[116]);
            lbl_1_bss_5088 = 360.0f * lbl_1_bss_5070 / maxTime;
            if (lbl_1_bss_5088 < 360.0f) {
                lbl_1_bss_5088 -= 180.0f;
            }
            lbl_1_bss_5084 = lbl_1_bss_5074 * sin(M_PI * (100.0f + lbl_1_bss_5088) / 180.0);
            if (lbl_1_bss_5070 - 180.0f < 25.0f) {
                lbl_1_bss_5080 = -100.0 * sin(M_PI * (180.0f * ((lbl_1_bss_5070 - 180.0f) / 25.0f)) / 180.0);
            }
            chr->unk01C->trans.y = 3200.0f;
            chr->unk01C->trans.y += lbl_1_bss_5084;
            chr->unk01C->trans.y += lbl_1_bss_5080;
        }
    }
    if (work->unk00C >= 6) {
        time = Hu3DData[scene->unk000[116]].motShapeWork.time;
        maxTime = Hu3DMotionMaxTimeGet(scene->unk000[116]);
        lbl_1_bss_5088 = 180.0f + 360.0f * time / maxTime;
        if (lbl_1_bss_5088 > 360.0f) {
            lbl_1_bss_5088 -= 360.0f;
        }
        Hu3DData[scene->unk000[117]].pos.y = lbl_1_bss_5078 + 75.0 * cos(M_PI * lbl_1_bss_5088 / 180.0);
        Hu3DData[scene->unk000[118]].pos.y = lbl_1_bss_5078 + 75.0 * cos(M_PI * lbl_1_bss_5088 / 180.0);
    }
    if (work->unk00C >= 8) {
        time = Hu3DData[scene->unk000[119]].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(scene->unk000[119]);
        lbl_1_bss_507C = 0.025f * (maxTime - time);
        if (lbl_1_bss_507C > 2.0f) {
            lbl_1_bss_507C = 2.0f;
        }
        Hu3DMotionShapeSpeedSet(scene->unk000[119], lbl_1_bss_507C);
    }
    return 0;
}

/* 118 insns */
void fn_1_C1EC(M502_WORK *work, float shake)
{
    M502_CAMERA *camera = &work->unk3A4[0].unk1048;

    if (shake > 0.0f) {
        if (shake < 20.0f) {
            if (lbl_1_bss_506C % 6 == 0) {
                fn_1_C3C4(work->unk5004, 0, 2);
            }
        } else if (shake < 50.0f) {
            if (lbl_1_bss_506C % 6 == 0) {
                fn_1_C3C4(work->unk5004, 1, 4);
            }
        } else {
            fn_1_C3C4(work->unk5004, 2, 12);
        }
    }
    if (lbl_1_bss_5068 < 2) {
        camera->unk010.y = camera->unk028.y -= shake;
        camera->unk01C.y = camera->unk034.y -= shake;
    } else {
        camera->unk010.y = camera->unk028.y += shake;
        camera->unk01C.y = camera->unk034.y += shake;
    }
    lbl_1_bss_5068++;
    lbl_1_bss_506C++;
    lbl_1_bss_5068 %= 4;
}

/* 41 insns */
void fn_1_C3C4(int playerNo, int type, int duration)
{
    switch (type) {
        case 0:
            omVibrate(playerNo, duration, 6, 6);
            break;
        case 1:
            omVibrate(playerNo, duration, 4, 2);
            break;
        case 2:
            omVibrate(playerNo, duration, 12, 0);
            break;
    }
}
