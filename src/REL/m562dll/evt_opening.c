/*
 * m562dll evt_opening.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_opening.s.
 */

#include "REL/m562dll.h"

#ifndef __MWERKS__
#include "game/audio.h" /* retail calls CharFXPlay unprototyped (no extsh on the s32 charNo) */
#endif
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
/* 0xAB0 lbl_1_rodata_AB0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_ABC = 180.0f; /* 0xABC */
static const float lbl_1_rodata_AC0 = 0.0f; /* 0xAC0 */
static const float lbl_1_rodata_AC4 = 15.0f; /* 0xAC4 */
static const float lbl_1_rodata_AC8 = 10000.0f; /* 0xAC8 */
static const float lbl_1_rodata_ACC = 360.0f; /* 0xACC */
static const float lbl_1_rodata_AD0 = 30.0f; /* 0xAD0 */
static const float lbl_1_rodata_AD4 = 0.04f; /* 0xAD4 */
static const float lbl_1_rodata_AD8 = 0.03f; /* 0xAD8 */
static const float lbl_1_rodata_ADC = 1.25f; /* 0xADC */
static const float lbl_1_rodata_AE0 = 3.0f; /* 0xAE0 */
static const float lbl_1_rodata_AE4 = 1.0f; /* 0xAE4 */
static const float lbl_1_rodata_AE8 = -1.0f; /* 0xAE8 */
static const float lbl_1_rodata_AEC = 0.9f; /* 0xAEC */
static const float lbl_1_rodata_AF0 = 0.05f; /* 0xAF0 */
static const float lbl_1_rodata_AF4 = 0.06f; /* 0xAF4 */
static const float lbl_1_rodata_AF8 = 60.0f; /* 0xAF8 */
static const float lbl_1_rodata_AFC = 120.0f; /* 0xAFC */
static const float lbl_1_rodata_B00 = 0.55f; /* 0xB00 */
static const float lbl_1_rodata_B04 = 90.0f; /* 0xB04 */
static const float lbl_1_rodata_B08 = 6.0f; /* 0xB08 */
static const double lbl_1_rodata_B10 = 0.25; /* 0xB10 */
static const double lbl_1_rodata_B18 = 3.141592653589793; /* 0xB18 */
static const double lbl_1_rodata_B20 = 180.0; /* 0xB20 */
/* 0xB28 lbl_1_rodata_B28 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0xB30 lbl_1_rodata_B30 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7928 */ HU3DMODELID lbl_1_bss_7928[4];
/* 0x791C */ HuVecF lbl_1_bss_791C;
/* 0x7910 */ float lbl_1_bss_7910[3];
/* 0x7904 */ float lbl_1_bss_7904[3];
/* 0x7902 */ s16 lbl_1_bss_7902;
/* 0x7900 */ s16 lbl_1_bss_7900;

/* --- functions (reference order), .data placed before its first user --- */
/* 0xC30 */ HuVecF lbl_1_data_C30[4] = { { 0.0f, 420.0f, 2040.0f }, { 0.0f, 500.0f, 578.0f }, { 0.0f, 347.9f, 26.0f }, { 0.0f, 1000.0f, 1400.0f } };
/* 0xC60 */ HuVecF lbl_1_data_C60[4] = { { 0.0f, 580.0f, 0.0f }, { 0.0f, 80.0f, 0.0f }, { 0.0f, 346.54f, 21.37f }, { 0.0f, 100.0f, -200.0f } };
/* 0xC90 */ s32 lbl_1_data_C90 = -1;

/* 914 insns. The opening: Bowser's intro, message 0x410000, the floor fire rows light up.
   Skipped (straight to phase 1) when GwSystem.subGameNo >= 0 (retry). Returns 1 when done. */
s32 fn_1_2446C(M562_WORK *work)
{
    M562_MAINMDL *mainMdl;
    M562_CAMERA *camera;
    M562_PLAYER *player;
    M562_KOOPA *koopa;
    M562_KOOPABOSS *boss;
    M562_PAD *pad;
    M562_BACK *back;
    M562_FIRE *fire;
    s32 result;
    float t;
    s32 i;
    HU3DMODELID mdl;
    M562_FIREOBJ *entry;
    s16 row;
    HuVecF dir;

    mainMdl = &work->mainMdl;
    camera = &work->camera[0];
    player = &work->player;
    koopa = &work->koopa;
    boss = &work->koopaboss;
    pad = &player->unk06C;
    back = &work->back;
    fire = &work->fire;
    result = 0;
    switch (work->unk0010) {
    case 0:
        fn_1_16F0(work, 0);
        lbl_1_bss_0->unk28B0 = fn_1_814(0x8CA);
        if (GWSubGameNoGet() >= 0) {
            back->unk24 = 1;
            back->unk28 = 0;
            player->unk09A = 28;
            player->unk09C = 0;
            player->unk094 = player->unk090 = 180.0f;
            player->unk0AC.y = player->unk090;
            result = 1;
            break;
        }
        player->unk09A = 30;
        player->unk09C = 0;
        work->sprite[0].unk04 = 0;
        for (i = 0; i < 35; i++) {
            entry = &fire->unk000C[i];
            Hu3DModelAttrSet(entry->unk1C, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(entry->unk2E, HU3D_ATTR_DISPOFF);
        }
        back->unk24 = 0;
        back->unk28 = 0;
        Hu3DModelAttrSet(mainMdl->unk4, HU3D_ATTR_DISPOFF);
        for (i = 0; i < 3; i++) {
            mdl = Hu3DModelLink(mainMdl->unk4);
            lbl_1_bss_7928[i] = mdl;
            Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
            Hu3DModelScaleSet(mdl, 15.0f, 15.0f, 15.0f);
            Hu3DModelCameraSet(mdl, camera->unk04);
            Hu3DModelLayerSet(mdl, 4);
            Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
            Hu3DMotionSet(mdl, mainMdl->unk6);
            Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_7910[i] = 360.0f * t;
            t = (frand() % 10000) / 10000.0f;
            lbl_1_bss_7904[i] = 30.0f * t;
        }
        camera->unk0A = 1;
        camera->unk10 = camera->unk34 = lbl_1_data_C30[0];
        camera->unk1C = camera->unk40 = lbl_1_data_C60[0];
        camera->unk0C = 0;
        camera->unk10 = lbl_1_data_C30[1];
        camera->unk1C = lbl_1_data_C60[1];
        camera->unk7C = 0.04f;
        camera->unk80 = 0.03f;
        lbl_1_data_C90 = fn_1_814(0x8B5);
        Hu3DMotionSpeedSet(back->unk40, 1.25f);
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 1:
        Hu3DMotionTimeSet(player->unk024, 0.0f);
        if (work->unk001C++ > 180) {
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 2:
        if (work->unk001C == 5) {
            CharFXPlay(player->unk018, 0x9E);
        }
        if (++work->unk001C >= 30) {
            player->unk09A = 26;
            player->unk09C = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 3:
        Hu3DMotionSpeedSet(player->unk024, 3.0f);
        if (++work->unk001C >= 40) {
            Hu3DMotionSpeedSet(player->unk024, 1.0f);
            player->unk09A = 1;
            player->unk09C = 1;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 4:
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = -1.0f;
        if (fn_1_AD98(player, &dir, 0.9f)) {
            player->unk094 = player->unk090 = 180.0f;
            player->unk09A = 0;
            player->unk09C = 1;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 5:
        if (++work->unk001C >= 30) {
            camera->unk0C = 0;
            camera->unk10 = lbl_1_data_C30[2];
            camera->unk1C = lbl_1_data_C60[2];
            camera->unk7C = 0.05f;
            camera->unk80 = 0.06f;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 6:
        t = work->unk001C / 60.0f;
        if (work->unk001C++ > 60) {
            camera->unk10 = lbl_1_data_C30[2];
            camera->unk1C = lbl_1_data_C60[2];
            fn_1_814(0x8C2);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 7:
        if (work->unk001C < 20) {
            back->unk24 = 1;
            back->unk28 = 1;
        } else {
            back->unk24 = 1;
            back->unk28 = 0;
        }
        work->unk001C++;
        if (work->unk001C > 60) {
            back->unk28 = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 8:
        HuWinExOpen(work->unk28A4);
        HuWinMesSet(work->unk28A4, 0x410000);
        koopa->motNext = 5;
        koopa->motLoop = 1;
        koopa->motShiftNext = 30;
        koopa->step = 10;
        fn_1_814(0x8B3);
        lbl_1_bss_7900 = 0;
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 9:
        if (HuWinStatGet(work->unk28A4) == 2) {
            lbl_1_bss_7900 = 0;
        } else if (HuWinStatGet(work->unk28A4) == 1) {
            if (++lbl_1_bss_7900 == 5) {
                koopa->motCur = 0;
                koopa->motNext = 5;
                koopa->motLoop = 1;
            }
        } else if (HuWinStatGet(work->unk28A4) == 0) {
            lbl_1_bss_7900 = 0;
            koopa->motNext = 0;
            koopa->motLoop = 1;
            player->unk09A = 26;
            player->unk09C = 1;
            camera->unk0C = 0;
            camera->unk10 = lbl_1_data_C30[3];
            camera->unk1C = lbl_1_data_C60[3];
            camera->unk7C = 0.06f;
            camera->unk80 = 0.06f;
            HuWinExClose(work->unk28A4);
            HuWinHomeClear(work->unk28A4);
            lbl_1_bss_7902 = -1;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 10:
        Hu3DMotionSpeedSet(player->unk024, 3.0f);
        t = work->unk001C / 120.0f;
        row = t * ((fire->unk1100 + 2) / 3);
        row = (row > (fire->unk1100 + 2) / 3) ? (fire->unk1100 + 2) / 3 : ((row < 0) ? 0 : row);
        if (row != lbl_1_bss_7902 && fire->unk000C[row * 3].unk10 != 7) {
            fn_1_814(0x8B7);
            fn_1_21B68(camera, 1, 50, 30.0f, 0.55f, 90.0f);
            omVibrate(player->unk014, 10, 12, 0);
        }
        lbl_1_bss_7902 = row;
        for (i = 0; i < 3; i++) {
            entry = &fire->unk000C[i + row * 3];
            if (entry->unk10 != 7 && i + row * 3 < 35) {
                Hu3DModelAttrReset(entry->unk1C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(entry->unk2E, HU3D_ATTR_DISPOFF);
                lbl_1_bss_791C = (HuVecF) { entry->unk44.x, 0.0f, entry->unk44.z };
                Hu3DModelPosSet(lbl_1_bss_7928[i], lbl_1_bss_791C.x, lbl_1_bss_791C.y, lbl_1_bss_791C.z);
                Hu3DModelAttrReset(lbl_1_bss_7928[i], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(lbl_1_bss_7928[i], HU3D_ATTR_DISPOFF);
            }
            Hu3DModelRotSet(lbl_1_bss_7928[i], lbl_1_bss_7904[i], lbl_1_bss_7910[i], 0.0f);
            lbl_1_bss_7910[i] += 6.0f;
        }
        if (++work->unk001C > 120) {
            Hu3DMotionSpeedSet(player->unk024, 1.0f);
            player->unk09A = 28;
            player->unk09C = 0;
            for (i = 0; i < 3; i++) {
                Hu3DModelAttrSet(lbl_1_bss_7928[i], HU3D_ATTR_DISPOFF);
            }
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 11:
        t = work->unk001C / 30.0f;
        Hu3DMotionSpeedSet(back->unk40, 0.25 + HuSin(90.0f + 90.0f * t));
        if (work->unk001C++ > 30) {
            for (i = 0; i < 3; i++) {
                Hu3DModelKill(lbl_1_bss_7928[i]);
            }
            fn_1_864(lbl_1_data_C90, 1000);
            lbl_1_data_C90 = -1;
            if (GWSubGameNoGet() < 0) {
                GWSubGameNoSet(0);
            }
            work->unk001C = 0;
            work->sprite[0].unk04 = 1;
            result = 1;
        }
        break;
    }
    return result;
}
