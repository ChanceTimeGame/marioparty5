/*
 * m562dll evt_koopagrow.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_koopagrow.s.
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

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_D40 = 0.05f; /* 0xD40 */
static const float lbl_1_rodata_D44 = -500.0f; /* 0xD44 */
static const float lbl_1_rodata_D48 = 0.0f; /* 0xD48 */
static const float lbl_1_rodata_D4C = 500.0f; /* 0xD4C */
static const float lbl_1_rodata_D50 = 180.0f; /* 0xD50 */
static const float lbl_1_rodata_D54 = 1.0f; /* 0xD54 */
static const float lbl_1_rodata_D58 = 1.5f; /* 0xD58 */
static const float lbl_1_rodata_D5C = 9.66f; /* 0xD5C */
static const float lbl_1_rodata_D60 = 30.0f; /* 0xD60 */
static const float lbl_1_rodata_D64 = 20.0f; /* 0xD64 */
static const float lbl_1_rodata_D68 = 40.0f; /* 0xD68 */
static const float lbl_1_rodata_D6C = 300.0f; /* 0xD6C */
static const double lbl_1_rodata_D70 = 0.8999999761581421; /* 0xD70 */
static const double lbl_1_rodata_D78 = 0.10000000149011612; /* 0xD78 */
static const double lbl_1_rodata_D80 = 3.141592653589793; /* 0xD80 */
static const float lbl_1_rodata_D88 = 360.0f; /* 0xD88 */
static const double lbl_1_rodata_D90 = 180.0; /* 0xD90 */
static const float lbl_1_rodata_D98 = 10.0f; /* 0xD98 */
static const float lbl_1_rodata_D9C = 0.75f; /* 0xD9C */
static const float lbl_1_rodata_DA0 = 90.0f; /* 0xDA0 */
static const float lbl_1_rodata_DA4 = 4.0f; /* 0xDA4 */
static const double lbl_1_rodata_DA8 = 0.03999999910593033; /* 0xDA8 */
static const float lbl_1_rodata_DB0 = 200.0f; /* 0xDB0 */
static const float lbl_1_rodata_DB4 = 65.0f; /* 0xDB4 */
static const float lbl_1_rodata_DB8 = 0.01f; /* 0xDB8 */
static const float lbl_1_rodata_DBC = 0.04f; /* 0xDBC */
static const float lbl_1_rodata_DC0 = 0.95f; /* 0xDC0 */
static const float lbl_1_rodata_DC4 = 55.0f; /* 0xDC4 */
static const float lbl_1_rodata_DC8 = -555.0f; /* 0xDC8 */
static const double lbl_1_rodata_DD0 = 10.0; /* 0xDD0 */
static const float lbl_1_rodata_DD8 = 0.3f; /* 0xDD8 */
static const float lbl_1_rodata_DDC = 0.5f; /* 0xDDC */
static const float lbl_1_rodata_DE0 = -5.0f; /* 0xDE0 */
static const float lbl_1_rodata_DE4 = -15.0f; /* 0xDE4 */
static const float lbl_1_rodata_DE8 = 6.0f; /* 0xDE8 */
static const float lbl_1_rodata_DEC = -2200.0f; /* 0xDEC */
static const float lbl_1_rodata_DF0 = -1.0f; /* 0xDF0 */
static const float lbl_1_rodata_DF4 = 60.0f; /* 0xDF4 */
static const double lbl_1_rodata_DF8 = 0.25; /* 0xDF8 */
static const double lbl_1_rodata_E00 = 2.0; /* 0xE00 */
static const float lbl_1_rodata_E08 = 0.9f; /* 0xE08 */
static const float lbl_1_rodata_E0C = 5.0f; /* 0xE0C */
/* 0xE10 lbl_1_rodata_E10 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0xE18 lbl_1_rodata_E18 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x799E gap_05_0000799E_bss (0x2): alignment gap */
/* 0x799C */ s16 lbl_1_bss_799C;
/* 0x799A */ s16 lbl_1_bss_799A;
/* 0x7998 */ s16 lbl_1_bss_7998;
/* 0x7994 */ float lbl_1_bss_7994;
/* 0x7990 */ s16 lbl_1_bss_7990;

/* --- functions (reference order), .data placed before its first user --- */
/* 0xDB0 */ HuVecF lbl_1_data_DB0[4] = { { 0.0f, 478.0f, 485.0f }, { 0.0f, 262.0f, 540.0f }, { 0.0f, 1800.0f, 785.0f }, { 0.0f, 800.0f, 1400.0f } };
/* 0xDE0 */ HuVecF lbl_1_data_DE0[4] = { { 0.0f, -76.0f, -1280.0f }, { 0.0f, 1040.0f, -1280.0f }, { 0.0f, 285.0f, -1026.0f }, { 0.0f, 100.0f, -200.0f } };
/* 0xE10 */ HuVecF lbl_1_data_E10 = { 0.0f, 1000.0f, 1000.0f };
/* 0xE1C */ HuVecF lbl_1_data_E1C = { 0.0f, -1.0f, -1.0f };
/* 0xE28 */ GXColor lbl_1_data_E28 = { 0, 0, 0, 0 };
/* 0xE2C */ GXColor lbl_1_data_E2C = { 0x80, 0xB0, 0xFF, 0xFF };
/* 0xE30 */ HuVecF lbl_1_data_E30 = { 0.0f, 1000.0f, -280.0f };
/* 0xE3C */ HuVecF lbl_1_data_E3C = { 0.0f, 55.0f, -1250.0f };
/* 0xE48 */ HuVecF lbl_1_data_E48 = { 0.0f, 0.0f, 0.0f };
/* 0xE54 */ HuVecF lbl_1_data_E54 = { 0.0f, 0.0f, 0.0f };
/* 0xE60 */ s16 lbl_1_data_E60 = -1;
/* 0xE64 */ s32 lbl_1_data_E64 = -1;

/* Bowser grows giant (phase 3 -> 4 cutscene); main fn_1_1F54 advances the event when it returns 1. */
s32 fn_1_280C8(M562_WORK *work)
{
    M562_LIGHT *light = &work->light;
    M562_MAINMDL *mainMdl = &work->mainMdl;
    M562_CAMERA *camera = &work->camera[0];
    M562_STAGE *stage = &work->stage;
    M562_PLAYER *player = &work->player;
    M562_PAD *pad = &player->unk06C;
    M562_KOOPA *koopa = &work->koopa;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    M562_BACK *back = &work->back;
    M562_FIRE *fire = &work->fire;
    s32 ret = FALSE;
    float t;
    float scale;
    MtxPtr bossMtx;
    MtxPtr mdlMtx;
    HuVecF pos;
    Mtx mtx;

    switch (work->unk0010) {
        case 0:
            fn_1_16F0(work, 3);
            back->unk24 = 0;
            back->unk28 = 0;
            mecha->unk004 = 0;
            lbl_1_bss_7998 = 0;
            lbl_1_data_E64 = -1;
            fn_1_864(lbl_1_bss_0->unk28B0, 1000);
            lbl_1_bss_0->unk28B0 = -1;
            HuAudAUXSet(4, 1);
            if (work->unk28AC >= 0) {
                fn_1_864(work->unk28AC, 3000);
            }
            Hu3DModelAttrReset(stage->unk5B4, HU3D_ATTR_DISPOFF);
            if (GWSubGameNoGet() >= 3) {
                camera->unk0A = 1;
                camera->unk34 = lbl_1_data_DB0[3];
                camera->unk10 = camera->unk34;
                camera->unk40 = lbl_1_data_DE0[3];
                camera->unk1C = camera->unk40;
                camera->unk0C = 0;
                camera->unk7C = 0.05f;
                camera->unk80 = 0.05f;
                boss->unk058 = lbl_1_data_E3C;
                boss->unk058.y = -500.0f;
                boss->unk050 = boss->unk052 = 1;
                boss->unk054 = 1;
                player->unk0A0 = lbl_1_data_E30;
                player->unk0A0.y = 0.0f;
                player->unk0A0.z = 500.0f;
                player->unk094 = player->unk090 = 180.0f;
                player->unk0AC.y = player->unk090;
                player->unk09A = 28;
                player->unk09C = 0;
                Hu3DModelAttrSet(stage->unk5B0, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(mainMdl->unk8, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(stage->unk5B4, HU3D_ATTR_DISPOFF);
                fn_1_22694(light, 3, 1.0f);
                fn_1_4748(back, 3, 1.0f);
                work->unk001C = 0;
                work->unk0010 = 14;
                break;
            }
            if (work->unk28A8 < 0) {
                work->unk28A8 = fn_1_A44(0x57);
                fn_1_9BC(work->unk28A8, 127, 0);
            }
            camera->unk0A = 1;
            camera->unk34 = lbl_1_data_DB0[0];
            camera->unk10 = camera->unk34;
            camera->unk40 = lbl_1_data_DE0[0];
            camera->unk1C = camera->unk40;
            camera->unk0C = 0;
            camera->unk7C = 1.0f;
            camera->unk80 = 1.0f;
            boss->unk058 = lbl_1_data_E3C;
            boss->unk052 = 11;
            boss->unk054 = 1;
            boss->unk004 = 0;
            scale = 1.5f;
            Hu3DModelScaleSet(boss->unk020, scale, scale, scale);
            Hu3DModelAttrReset(mainMdl->unk8, HU3D_ATTR_DISPOFF);
            player->unk004 = 0;
            player->unk09A = 3;
            player->unk09C = 0;
            player->unk0A0 = lbl_1_data_E30;
            player->unk094 = player->unk090 = 180.0f;
            player->unk0AC.y = player->unk090;
            player->unk0C4 = 0.0f;
            fn_1_22694(light, 3, 1.0f);
            fn_1_4748(back, 3, 1.0f);
            lbl_1_data_E60 = -1;
            work->unk001C = 0;
            work->unk0010++;
        case 1:
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0C4 < 0.0f && player->unk0A0.y <= 0.0f) {
                player->unk0A0.y = 0.0f;
                player->unk0C4 = 0.0f;
                player->unk09A = 4;
                player->unk09C = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 2:
            if (work->unk001C == 12) {
                player->unk09A = 28;
                player->unk09C = 0;
            }
            work->unk001C++;
            if (work->unk001C >= 120) {
                HuWinExOpen(work->unk28A4);
                HuWinMesSet(work->unk28A4, 0x410004);
                boss->unk052 = 18;
                boss->unk054 = 1;
                lbl_1_bss_799A = 2;
                lbl_1_bss_799C = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 3:
            if (HuWinStatGet(work->unk28A4) == 2) {
                lbl_1_bss_799A = 2;
            } else if (HuWinStatGet(work->unk28A4) == 1) {
                if (lbl_1_bss_799A == 2) {
                    if (lbl_1_bss_799C == 0) {
                        fn_1_814(0x2CA);
                    } else if (lbl_1_bss_799C == 2) {
                        fn_1_814(0x2CB);
                    }
                    lbl_1_bss_799C++;
                }
                lbl_1_bss_799A = 1;
            } else if (HuWinStatGet(work->unk28A4) == 0) {
                lbl_1_bss_799A = 0;
                HuWinExClose(work->unk28A4);
                HuWinHomeClear(work->unk28A4);
                boss->unk052 = 12;
                boss->unk054 = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 4:
            if (work->unk001C > 20 && work->unk001C < 120 && work->unk001C % 30 == 0) {
                fn_1_814(0x8BB);
            }
            if (++work->unk001C >= 125) {
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 5:
            if (++work->unk001C >= 120) {
                boss->unk052 = 13;
                boss->unk054 = 0;
                pos = boss->unk058;
                Hu3DModelPosSet(boss->unk132, pos.x, pos.y, pos.z);
                Hu3DMotionSpeedSet(boss->unk132, 9.66f);
                Hu3DModelAttrSet(boss->unk132, HU3D_MOTATTR_REV);
                scale = 1.5f;
                Hu3DModelScaleSet(boss->unk132, scale, scale, scale);
                lbl_1_data_E60 = Hu3DGLightCreateV(&lbl_1_data_E10, &lbl_1_data_E1C, &lbl_1_data_E28);
                Hu3DGLightStaticSet(lbl_1_data_E60, TRUE);
                Hu3DGLightSpotSet(lbl_1_data_E60, GX_SP_COS, 30.0f);
                Hu3DGLightInfinitytSet(lbl_1_data_E60);
                lbl_1_data_E64 = fn_1_814(0x8BA);
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 6:
            if (work->unk001C == 30) {
                Hu3DModelAttrReset(boss->unk132, HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_data_E60 >= 0) {
                if (work->unk001C < 20) {
                    t = work->unk001C / 20.0f;
                    Hu3DGLightColorSet(lbl_1_data_E60, lbl_1_data_E2C.r * t, lbl_1_data_E2C.g * t, lbl_1_data_E2C.b * t, lbl_1_data_E2C.a * t);
                } else if (work->unk001C > 260) {
                    t = (work->unk001C - 260) / 40.0f;
                    t = 1.0f - t;
                    Hu3DGLightColorSet(lbl_1_data_E60, lbl_1_data_E2C.r * t, lbl_1_data_E2C.g * t, lbl_1_data_E2C.b * t, lbl_1_data_E2C.a * t);
                } else {
                    t = work->unk001C / 300.0f;
                    t = 0.9f + 0.1f * HuSin(30.0f * (360.0f * t));
                    Hu3DGLightColorSet(lbl_1_data_E60, lbl_1_data_E2C.r * t, lbl_1_data_E2C.g * t, lbl_1_data_E2C.b * t, lbl_1_data_E2C.a * t);
                }
            }
            t = work->unk001C / 300.0f;
            if (work->unk001C % 20 == 0) {
                omVibrate(player->unk014, 10, 6, 6);
                fn_1_21B68(camera, 1, 50, 10.0f, 0.75f, 90.0f);
            }
            scale = 1.5f + 4.0f * t;
            scale += 0.04f * HuSin(200.0f * (360.0f * t));
            Hu3DModelScaleSet(boss->unk020, scale, scale, scale);
            scale = 1.5f + 4.0f * t;
            Hu3DModelScaleSet(boss->unk132, scale, scale, scale);
            if (Hu3DMotionTimeGet(boss->unk020) >= Hu3DMotionMaxTimeGet(boss->unk020)) {
                Hu3DMotionTimeSet(boss->unk020, 65.0f);
            }
            if (work->unk001C == 30) {
                fn_1_814(0x8C7);
            }
            if (work->unk001C == 120) {
                player->unk00C = 0;
            } else if (work->unk001C == 290) {
                player->unk00C = 1;
            }
            work->unk001C++;
            if (work->unk001C == 60) {
                camera->unk10 = lbl_1_data_DB0[1];
                camera->unk1C = lbl_1_data_DE0[1];
                camera->unk0C = 0;
                camera->unk7C = 0.01f;
                camera->unk80 = 0.01f;
            } else if (work->unk001C >= 300) {
                Hu3DModelAttrSet(boss->unk132, HU3D_ATTR_DISPOFF);
                Hu3DGLightKill(lbl_1_data_E60);
                lbl_1_data_E60 = -1;
                fn_1_83C(lbl_1_data_E64);
                lbl_1_data_E64 = -1;
                boss->unk052 = 0;
                boss->unk054 = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 7:
            if (work->unk001C == 20) {
                fn_1_814(0x8BC);
            }
            if (++work->unk001C >= 30) {
                camera->unk10 = lbl_1_data_DB0[2];
                camera->unk1C = lbl_1_data_DE0[2];
                camera->unk0C = 0;
                camera->unk7C = 0.04f;
                camera->unk80 = 0.04f;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 8:
            work->unk001C++;
            if (work->unk001C == 120) {
                fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
                omVibrate(player->unk014, 10, 12, 0);
                pos = boss->unk058;
                pos.y = lbl_1_data_E3C.y;
                fn_1_2DC08(camera->unk04, &pos, 2);
                fn_1_814(0x8C0);
            } else if (work->unk001C == 130) {
                pos = boss->unk058;
                pos.y = lbl_1_data_E3C.y;
                fn_1_2DC08(camera->unk04, &pos, 2);
            } else if (work->unk001C >= 140) {
                boss->unk052 = 14;
                boss->unk054 = 0;
                if (work->unk28A8 >= 0) {
                    fn_1_9F4(work->unk28A8, 100);
                    work->unk28A8 = -1;
                }
                HuWinExOpen(work->unk28A4);
                HuWinMesSet(work->unk28A4, 0x410005);
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 9:
            work->unk001C++;
            if (Hu3DMotionTimeGet(boss->unk020) >= Hu3DMotionMaxTimeGet(boss->unk020)) {
                Hu3DMotionTimeSet(boss->unk020, 20.0f);
            }
            if (work->unk001C >= 90) {
                HuWinExClose(work->unk28A4);
                HuWinHomeClear(work->unk28A4);
                lbl_1_data_E64 = fn_1_814(0x8BE);
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 10:
            t = work->unk001C / 300.0f;
            boss->unk058.y = 55.0f + -555.0f * t;
            boss->unk058.y += 10.0 * HuSin(200.0f * (360.0f * t));
            if (work->unk001C % 10 == 0) {
                fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
            }
            if (work->unk001C % 30 == 0) {
                pos = boss->unk058;
                pos.y = lbl_1_data_E3C.y;
                fn_1_2DC08(camera->unk04, &pos, 2);
                omVibrate(player->unk014, 10, 12, 0);
            }
            if ((work->unk001C + 15) % 30 == 0) {
                omVibrate(player->unk014, 10, 6, 6);
            }
            if (work->unk001C == 10) {
                boss->unk052 = 15;
                boss->unk054 = 0;
            } else if (work->unk001C == 20) {
                Hu3DMotionSpeedSet(stage->unk5B0, 0.3f);
                fn_1_814(0x8BD);
            } else if (work->unk001C == 90) {
                camera->unk10 = lbl_1_data_DB0[3];
                camera->unk1C = lbl_1_data_DE0[3];
                camera->unk0C = 0;
                camera->unk7C = 0.01f;
                camera->unk80 = 0.01f;
                HuWinExOpen(work->unk28A4);
                HuWinMesSet(work->unk28A4, 0x410006);
                boss->unk052 = 15;
                boss->unk054 = 1;
            } else if (work->unk001C == 240) {
                HuWinExClose(work->unk28A4);
                HuWinHomeClear(work->unk28A4);
            }
            if (work->unk001C < 10) {
                if (Hu3DMotionTimeGet(boss->unk020) >= Hu3DMotionMaxTimeGet(boss->unk020)) {
                    Hu3DMotionTimeSet(boss->unk020, 20.0f);
                }
            } else if (work->unk001C < 90) {
                Hu3DMotionSpeedSet(boss->unk020, 0.5f);
            } else if (work->unk001C < 120) {
                Hu3DMotionSpeedSet(boss->unk020, 0.75f);
            } else {
                Hu3DMotionSpeedSet(boss->unk020, 1.0f);
            }
            work->unk001C++;
            if (work->unk001C >= 300) {
                fn_1_83C(lbl_1_data_E64);
                lbl_1_data_E64 = -1;
                fn_1_814(0x8C9);
                Hu3DModelAttrSet(stage->unk5B0, HU3D_ATTR_DISPOFF);
                camera->unk7C = 0.05f;
                camera->unk80 = 0.05f;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 11:
            if (++work->unk001C >= 60) {
                HuWinExOpen(work->unk28A4);
                HuWinMesSet(work->unk28A4, 0x410007);
                fn_1_814(0x8C8);
                boss->unk052 = 16;
                boss->unk054 = 1;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 12:
            if (HuWinStatGet(work->unk28A4) == 0) {
                HuWinExClose(work->unk28A4);
                HuWinHomeClear(work->unk28A4);
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 13:
            if (++work->unk001C >= 30) {
                Hu3DModelAttrSet(stage->unk5B4, HU3D_ATTR_DISPOFF);
                boss->unk052 = 1;
                boss->unk054 = 0;
                player->unk004 = player->unk006 = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 14:
            if (work->unk28AC >= 0) {
                fn_1_83C(work->unk28AC);
                work->unk28AC = -1;
            }
            if (GWSubGameNoGet() < 3) {
                GWSubGameNoSet(3);
            }
            if (!WipeCheckEnd()) {
                mecha->unk004 = 1;
                work->unk001C = 0;
                work->unk0010 = 0;
                ret = TRUE;
                return ret;
            }
            break;
    }
    if (work->unk0010 < 5) {
        bossMtx = fn_1_1010C(boss);
        PSMTXCopy(bossMtx, mtx);
        Hu3DMtxTransGet(mtx, &pos);
        lbl_1_data_E48 = pos;
        mtx[0][3] = 0.0f;
        mtx[1][3] = 0.0f;
        mtx[2][3] = 0.0f;
        mdlMtx = Hu3DData[mainMdl->unk8].mtx;
        PSMTXCopy(mtx, mdlMtx);
        lbl_1_bss_7990 = 0;
    } else if (work->unk0010 >= 5 && work->unk0010 < 6) {
        if (lbl_1_bss_7990 == 0) {
            lbl_1_data_E54.x = -5.0f;
            lbl_1_data_E54.y = 0.0f;
            lbl_1_data_E54.z = -15.0f;
            fn_1_814(0x8C1);
        } else if (lbl_1_bss_7990 < 120) {
            lbl_1_bss_7994 += 6.0f;
            lbl_1_data_E54.y -= 1.5f;
            PSVECAdd(&lbl_1_data_E48, &lbl_1_data_E54, &lbl_1_data_E48);
            if (lbl_1_data_E48.z > -2200.0f && lbl_1_data_E48.y < 55.0f) {
                lbl_1_data_E48.y = 55.0f;
                lbl_1_data_E54.y *= -1.0f;
                fn_1_814(0x8B9);
            }
        } else {
            Hu3DModelAttrSet(mainMdl->unk8, HU3D_ATTR_DISPOFF);
        }
        lbl_1_bss_7990++;
    }
    Hu3DModelPosSet(mainMdl->unk8, lbl_1_data_E48.x, lbl_1_data_E48.y, lbl_1_data_E48.z);
    Hu3DModelRotSet(mainMdl->unk8, lbl_1_bss_7994, lbl_1_bss_7994, 0.0f);
    lbl_1_bss_7998++;
    t = lbl_1_bss_7998 / 60.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * HuSin(90.0f + 90.0f * t));
    if (work->unk0010 >= 6) {
        if (player->unk0A0.z < 500.0f) {
            player->unk09A = 27;
            player->unk09C = 1;
            player->unk090 = fn_1_36EC(0.0f, player->unk090, 0.9f);
            player->unk0AC.y = player->unk090;
            player->unk0A0.z += 5.0f;
        } else {
            player->unk0A0.z = 500.0f;
            player->unk09A = 28;
            player->unk09C = 0;
            player->unk094 = player->unk090 = 180.0f;
            player->unk0AC.y = player->unk090;
        }
    }
    return ret;
}
