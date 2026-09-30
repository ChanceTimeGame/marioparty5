/*
 * m562dll evt_ending.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_ending.s.
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
/* 0xE20 lbl_1_rodata_E20 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE2C lbl_1_rodata_E2C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_E38 = 0.04f; /* 0xE38 */
static const float lbl_1_rodata_E3C = 10000.0f; /* 0xE3C */
static const float lbl_1_rodata_E40 = 3.0f; /* 0xE40 */
static const float lbl_1_rodata_E44 = 0.02f; /* 0xE44 */
static const float lbl_1_rodata_E48 = 180.0f; /* 0xE48 */
static const float lbl_1_rodata_E4C = 10.0f; /* 0xE4C */
static const float lbl_1_rodata_E50 = 0.95f; /* 0xE50 */
static const float lbl_1_rodata_E54 = 90.0f; /* 0xE54 */
static const float lbl_1_rodata_E58 = 13.0f; /* 0xE58 */
static const float lbl_1_rodata_E5C = 300.0f; /* 0xE5C */
static const float lbl_1_rodata_E60 = -100.0f; /* 0xE60 */
static const double lbl_1_rodata_E68 = 80.0; /* 0xE68 */
static const double lbl_1_rodata_E70 = 3.141592653589793; /* 0xE70 */
static const float lbl_1_rodata_E78 = 200.0f; /* 0xE78 */
static const float lbl_1_rodata_E7C = 360.0f; /* 0xE7C */
static const double lbl_1_rodata_E80 = 180.0; /* 0xE80 */
static const float lbl_1_rodata_E88 = 0.01f; /* 0xE88 */
static const float lbl_1_rodata_E8C = 48.0f; /* 0xE8C */
static const float lbl_1_rodata_E90 = 0.0f; /* 0xE90 */
static const float lbl_1_rodata_E94 = 22000.0f; /* 0xE94 */
static const float lbl_1_rodata_E98 = 1.0f; /* 0xE98 */
static const float lbl_1_rodata_E9C = 0.3f; /* 0xE9C */
static const float lbl_1_rodata_EA0 = 0.6f; /* 0xEA0 */
static const float lbl_1_rodata_EA4 = 0.55f; /* 0xEA4 */
static const float lbl_1_rodata_EA8 = 0.25f; /* 0xEA8 */
static const double lbl_1_rodata_EB0 = 2500.0; /* 0xEB0 */
static const float lbl_1_rodata_EB8 = 0.5f; /* 0xEB8 */
static const double lbl_1_rodata_EC0 = 200.0; /* 0xEC0 */
static const double lbl_1_rodata_EC8 = 90.0; /* 0xEC8 */
static const float lbl_1_rodata_ED0 = 30.0f; /* 0xED0 */
static const float lbl_1_rodata_ED4 = 5.5f; /* 0xED4 */
static const float lbl_1_rodata_ED8 = -5.0f; /* 0xED8 */
static const float lbl_1_rodata_EDC = 0.1f; /* 0xEDC */
static const float lbl_1_rodata_EE0 = 100.0f; /* 0xEE0 */
static const float lbl_1_rodata_EE4 = 0.9f; /* 0xEE4 */
static const float lbl_1_rodata_EE8 = 120.0f; /* 0xEE8 */
static const float lbl_1_rodata_EEC = 56.0f; /* 0xEEC */
static const float lbl_1_rodata_EF0 = -1.0f; /* 0xEF0 */
static const float lbl_1_rodata_EF4 = 50.0f; /* 0xEF4 */
static const float lbl_1_rodata_EF8 = 23900.0f; /* 0xEF8 */
static const double lbl_1_rodata_F00 = 2000.0; /* 0xF00 */
static const float lbl_1_rodata_F08 = 1000.0f; /* 0xF08 */
static const float lbl_1_rodata_F0C = 5.0f; /* 0xF0C */
static const float lbl_1_rodata_F10 = 0.7f; /* 0xF10 */
static const double lbl_1_rodata_F18 = 1500.0; /* 0xF18 */
static const float lbl_1_rodata_F20 = 4.0f; /* 0xF20 */
/* 0xF28 lbl_1_rodata_F28 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0xF30 lbl_1_rodata_F30 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x79EC */ HuVecF lbl_1_bss_79EC;
/* 0x79E0 */ HuVecF lbl_1_bss_79E0;
/* 0x79D4 */ HuVecF lbl_1_bss_79D4;
/* 0x79C8 */ HuVecF lbl_1_bss_79C8;
/* 0x79BC */ HuVecF lbl_1_bss_79BC;
/* 0x79B0 */ HuVecF lbl_1_bss_79B0;
/* 0x79A4 */ HuVecF lbl_1_bss_79A4;
/* 0x79A0 */ s32 lbl_1_bss_79A0;

/* --- functions (reference order), .data placed before its first user --- */
/* 0xEA8 */ HuVecF lbl_1_data_EA8[5] = { { 0.0f, 800.0f, 1400.0f }, { 0.0f, 468.0f, 810.0f }, { 0.0f, 1796.0f, 873.0f }, { 0.0f, 1072.0f, 739.0f }, { 0.0f, 400.0f, 1280.0f } };
/* 0xEE4 */ HuVecF lbl_1_data_EE4[5] = { { 0.0f, 100.0f, -200.0f }, { 0.0f, 210.0f, -1111.0f }, { 0.0f, 483.0f, -1111.0f }, { 0.0f, 483.0f, -1111.0f }, { 0.0f, 85.0f, 7.0f } };
/* 0xF20 */ HuVecF lbl_1_data_F20 = { 0.0f, 0.0f, 500.0f };
/* 0xF2C */ HuVecF lbl_1_data_F2C = { 0.0f, 0.0f, 0.0f };
/* 0xF38 */ s32 lbl_1_data_F38 = 1;
/* 0xF3C */ HuVecF lbl_1_data_F3C = { 0.0f, -3800.0f, -26000.0f };
/* 0xF48 */ HuVecF lbl_1_data_F48 = { -680.0f, 370.0f, -2100.0f };
/* 0xF54 */ s32 lbl_1_data_F54 = 1;
/* 0xF58 */ HuVecF lbl_1_data_F58 = { 680.0f, 370.0f, -2100.0f };
/* 0xF64 */ s32 lbl_1_data_F64 = 1;

/* Bowser defeated: he is blasted into the sky with two debris pieces, the player walks off; last
   step writes the only result of the overlay (GwPlayer[0].mgCoinBonus = 10). Returns 1 when done. */
s32 fn_1_29DF8(M562_WORK *work)
{
    M562_MAINMDL *mainMdl = &work->mainMdl;
    M562_CAMERA *camera = &work->camera[0];
    M562_STAGE *stage = &work->stage;
    M562_PLAYER *player = &work->player;
    M562_PAD *pad = &player->unk06C;
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    M562_BACK *back = &work->back;
    M562_FIRE *fire = &work->fire;
    s32 ret = FALSE;
    float t;
    float scale;
    float dist;
    HuVecF *zero1P;
    HuVecF *zero2P;
    s16 mdlId;
    HuVecF dir;
    HuVecF pos;

    switch (work->unk0010) {
        case 0:
            fn_1_1D9C(work);
            player->unk004 = player->unk006 = 0;
            Hu3DModelAttrReset(stage->unk5B4, HU3D_ATTR_DISPOFF);
            camera->unk0A = 1;
            camera->unk10 = lbl_1_data_EA8[0];
            camera->unk1C = lbl_1_data_EE4[0];
            camera->unk0C = 0;
            camera->unk7C = 0.04f;
            camera->unk80 = 0.04f;
            lbl_1_bss_79EC = boss->unk058;
            lbl_1_data_F38 = 1;
            lbl_1_bss_79A0 = 0;
            lbl_1_bss_79E0 = lbl_1_data_F48;
            {
                HuVecF zero = { 0.0f, 0.0f, 0.0f };
                zero1P = &zero;
            }
            lbl_1_bss_79D4 = *zero1P;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79C8.x = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79C8.y = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79C8.z = 3.0f * t;
            lbl_1_data_F54 = 1;
            lbl_1_bss_79BC = lbl_1_data_F58;
            {
                HuVecF zero = { 0.0f, 0.0f, 0.0f };
                zero2P = &zero;
            }
            lbl_1_bss_79B0 = *zero2P;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79A4.x = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79A4.y = 3.0f * t;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_79A4.z = 3.0f * t;
            lbl_1_data_F64 = 1;
            work->unk001C = 0;
            work->unk0010++;
        case 1:
            if (++work->unk001C >= 90) {
                camera->unk0A = 1;
                camera->unk10 = lbl_1_data_EA8[1];
                camera->unk1C = lbl_1_data_EE4[1];
                camera->unk0C = 0;
                camera->unk7C = 0.02f;
                camera->unk80 = 0.02f;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 2:
            if (work->unk28AC < 0) {
                work->unk28AC = fn_1_814(0x8B5);
            }
            t = work->unk001C / 180.0f;
            fn_1_4748(back, 4, t);
            if (work->unk001C % 30 == 0) {
                fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
                omVibrate(player->unk014, 10, 12, 0);
            }
            work->unk001C++;
            if (work->unk001C >= 180) {
                camera->unk0A = 1;
                camera->unk10 = lbl_1_data_EA8[2];
                camera->unk1C = lbl_1_data_EE4[2];
                camera->unk0C = 0;
                camera->unk7C = 0.02f;
                camera->unk80 = 0.02f;
                fn_1_A6C(0x7C);
                boss->unk052 = 17;
                boss->unk054 = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 3:
            if (Hu3DMotionTimeGet(boss->unk020) >= Hu3DMotionMaxTimeGet(boss->unk020)) {
                Hu3DMotionTimeSet(boss->unk020, 13.0f);
            }
            t = work->unk001C / 300.0f;
            if (work->unk001C % 20 == 0) {
                fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
                omVibrate(player->unk014, 10, 12, 0);
            }
            if (work->unk001C == 60) {
                pos = boss->unk058;
                pos.y = -100.0f;
                fn_1_2DC08(camera->unk04, &pos, 2);
            }
            boss->unk058.z += 80.0 * HuSin(200.0f * (360.0f * t));
            work->unk001C++;
            if (work->unk001C >= 300) {
                t = (frand() % 10000) / 10000.0f;
                lbl_1_data_F2C.x = 3.0f * t;
                t = (frand() % 10000) / 10000.0f;
                lbl_1_data_F2C.y = 3.0f * t;
                t = (frand() % 10000) / 10000.0f;
                lbl_1_data_F2C.z = 3.0f * t;
                boss->unk052 = 10;
                boss->unk054 = 0;
                camera->unk0A = 1;
                camera->unk10 = lbl_1_data_EA8[3];
                camera->unk1C = lbl_1_data_EE4[3];
                camera->unk0C = 0;
                camera->unk7C = 0.01f;
                camera->unk80 = 0.01f;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 4:
            if (lbl_1_data_F38) {
                if (Hu3DMotionTimeGet(boss->unk020) >= Hu3DMotionMaxTimeGet(boss->unk020)) {
                    Hu3DMotionTimeSet(boss->unk020, 48.0f);
                }
                dist = (lbl_1_data_F3C.z - boss->unk058.z >= 0.0f) ? (lbl_1_data_F3C.z - boss->unk058.z) : -(lbl_1_data_F3C.z - boss->unk058.z);
                t = dist / 22000.0f;
                t = 1.0f - ((t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t));
                if (t < 0.3f) {
                    if (work->unk001C % 15 == 0) {
                        fn_1_21B68(camera, 1, 50, 10.0f, 0.95f * (1.0f - t), 90.0f);
                        omVibrate(player->unk014, 10, 12, 0);
                    }
                } else if (t < 0.6f) {
                    if (work->unk001C % 20 == 0) {
                        fn_1_21B68(camera, 1, 50, 10.0f, 0.55f, 90.0f);
                        omVibrate(player->unk014, 10, 4, 2);
                    }
                } else {
                    if (work->unk001C % 30 == 0) {
                        fn_1_21B68(camera, 1, 50, 10.0f, 0.25f, 90.0f);
                        omVibrate(player->unk014, 10, 6, 6);
                    }
                }
                pos.x = 2500.0 * HuSin(10.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
                pos.y = (t < 0.5f) ? 200.0 * HuSin(90.0 * (t / 0.5f)) : 200.0 + (lbl_1_data_F3C.y - 200.0f) * HuSin(90.0f * ((t - 0.5f) / 0.5f));
                pos.y += 2500.0 * HuCos(10.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
                boss->unk058.x = pos.x;
                boss->unk058.y = lbl_1_bss_79EC.y + pos.y;
                boss->unk058.z -= 30.0f + 30.0f * t;
                scale = 5.5f + -5.0f * t;
                Hu3DModelScaleSet(boss->unk020, scale, scale, scale);
                if (t > 0.1f) {
                    PSVECAdd(&boss->unk064, &lbl_1_data_F2C, &boss->unk064);
                }
                if (dist < 100.0f || boss->unk058.z < lbl_1_data_F3C.z) {
                    Hu3DModelAttrSet(boss->unk020, HU3D_ATTR_DISPOFF);
                    lbl_1_data_F38 = 0;
                }
            }
            if (work->unk001C == 180) {
                fn_1_814(0x8C7);
            }
            if (work->unk001C == 300) {
                camera->unk0A = 1;
                camera->unk10 = lbl_1_data_EA8[4];
                camera->unk1C = lbl_1_data_EE4[4];
                camera->unk0C = 0;
                camera->unk7C = 0.02f;
                camera->unk80 = 0.02f;
                if (work->unk28AC >= 0) {
                    fn_1_864(work->unk28AC, 5000);
                }
            }
            work->unk001C++;
            if (!lbl_1_data_F38 && work->unk001C >= 300) {
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 5:
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 1.0f;
            if (fn_1_AD98(player, &dir, 0.9f)) {
                player->unk09A = 24;
                player->unk09C = 0;
                work->unk001C = 0;
                work->unk0010++;
            }
            break;
        case 6:
            if (work->unk28AC >= 0) {
                fn_1_83C(work->unk28AC);
                work->unk28AC = -1;
            }
            t = work->unk001C / 120.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            fn_1_4748(back, 4, 1.0f - t);
            if (++work->unk001C >= 300) {
                GWMgCoinBonusSet(0, 10);
                player->unk004 = 0;
                player->unk006 = 0;
                work->unk001C = 0;
                work->unk0010 = 0;
                ret = TRUE;
                return ret;
            }
            break;
    }
    if (work->unk0010 < 4) {
        PSVECSubtract(&lbl_1_data_F20, &player->unk0A0, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dist > 30.0f) {
            PSVECNormalize(&dir, &dir);
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            pad->unk10 = 56.0f * dir.x;
            pad->unk11 = 56.0f * -dir.z;
            fn_1_7D58(player);
        } else {
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = -1.0f;
            fn_1_AD98(player, &dir, 0.9f);
        }
    }
    if (work->unk0010 >= 2) {
        if (lbl_1_bss_79A0 == 510) {
            pos = lbl_1_data_F48;
            fn_1_2DC08(camera->unk04, &pos, 2);
            pos.y = 50.0f;
            fn_1_2DC08(camera->unk04, &pos, 2);
            fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
            omVibrate(player->unk014, 10, 12, 0);
            fn_1_814(0x8C4);
        } else if (lbl_1_bss_79A0 == 520) {
            pos = lbl_1_data_F58;
            fn_1_2DC08(camera->unk04, &pos, 2);
            pos.y = 50.0f;
            fn_1_2DC08(camera->unk04, &pos, 2);
            fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
            omVibrate(player->unk014, 10, 12, 0);
            fn_1_814(0x8C4);
        } else if (lbl_1_bss_79A0 == 570) {
            Hu3DMotionSpeedSet(back->unk12, 0.1f);
        } else if (lbl_1_bss_79A0 == 580) {
            Hu3DMotionSpeedSet(back->unk14, 0.1f);
        }
        if (lbl_1_bss_79A0 > 510 && lbl_1_data_F54) {
            mdlId = back->unk12;
            dist = (lbl_1_data_F3C.z - lbl_1_bss_79E0.z >= 0.0f) ? (lbl_1_data_F3C.z - lbl_1_bss_79E0.z) : -(lbl_1_data_F3C.z - lbl_1_bss_79E0.z);
            t = dist / 23900.0f;
            t = 1.0f - ((t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t));
            lbl_1_bss_79E0.x = lbl_1_data_F48.x + 2000.0 * HuSin(3.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
            lbl_1_bss_79E0.y = (t < 0.5f) ? 200.0 * HuSin(90.0 * (t / 0.5f)) : 200.0 + (lbl_1_data_F3C.y - 1000.0f) * HuSin(90.0f * ((t - 0.5f) / 0.5f));
            lbl_1_bss_79E0.y += 2000.0 * HuCos(3.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
            lbl_1_bss_79E0.y += lbl_1_data_F48.y;
            lbl_1_bss_79E0.z -= 5.0f + 200.0f * t;
            lbl_1_bss_79D4.x += lbl_1_bss_79C8.x * (0.3f + 0.7f * t);
            lbl_1_bss_79D4.y += lbl_1_bss_79C8.y * (0.3f + 0.7f * t);
            lbl_1_bss_79D4.z += lbl_1_bss_79C8.z * (0.3f + 0.7f * t);
            Hu3DModelPosSet(mdlId, lbl_1_bss_79E0.x, lbl_1_bss_79E0.y, lbl_1_bss_79E0.z);
            scale = 1.0f - t;
            Hu3DModelScaleSet(mdlId, scale, scale, scale);
            Hu3DModelRotSet(mdlId, lbl_1_bss_79D4.x, lbl_1_bss_79D4.y, lbl_1_bss_79D4.z);
            if (dist < 100.0f || lbl_1_bss_79E0.z < lbl_1_data_F3C.z) {
                Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
                lbl_1_data_F54 = 0;
            }
        }
        if (lbl_1_bss_79A0 > 520 && lbl_1_data_F64) {
            mdlId = back->unk14;
            dist = (lbl_1_data_F3C.z - lbl_1_bss_79BC.z >= 0.0f) ? (lbl_1_data_F3C.z - lbl_1_bss_79BC.z) : -(lbl_1_data_F3C.z - lbl_1_bss_79BC.z);
            t = dist / 23900.0f;
            t = 1.0f - ((t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t));
            lbl_1_bss_79BC.x = lbl_1_data_F58.x + 1500.0 * HuSin(4.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
            lbl_1_bss_79BC.y = (t < 0.5f) ? 200.0 * HuSin(90.0 * (t / 0.5f)) : 200.0 + (lbl_1_data_F3C.y - 1000.0f) * HuSin(90.0f * ((t - 0.5f) / 0.5f));
            lbl_1_bss_79BC.y += 1500.0 * HuCos(4.0f * (360.0f * t)) * HuSin(180.0f * (1.0f - (1.0f - t) * (1.0f - t)));
            lbl_1_bss_79BC.y += lbl_1_data_F58.y;
            lbl_1_bss_79BC.z -= 5.0f + 200.0f * t;
            lbl_1_bss_79B0.x += lbl_1_bss_79A4.x * (0.3f + 0.7f * t);
            lbl_1_bss_79B0.y += lbl_1_bss_79A4.y * (0.3f + 0.7f * t);
            lbl_1_bss_79B0.z += lbl_1_bss_79A4.z * (0.3f + 0.7f * t);
            Hu3DModelPosSet(mdlId, lbl_1_bss_79BC.x, lbl_1_bss_79BC.y, lbl_1_bss_79BC.z);
            scale = 1.0f - t;
            Hu3DModelScaleSet(mdlId, scale, scale, scale);
            Hu3DModelRotSet(mdlId, lbl_1_bss_79B0.x, lbl_1_bss_79B0.y, lbl_1_bss_79B0.z);
            if (dist < 100.0f || lbl_1_bss_79BC.z < lbl_1_data_F3C.z) {
                Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
                lbl_1_data_F64 = 0;
            }
        }
        lbl_1_bss_79A0++;
    }
    return ret;
}
