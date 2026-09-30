/*
 * m504dll ending.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/ending.s.
 */

#include "REL/m504dll.h"

#include "game/audio.h"
#include "game/charman.h"
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
/* 0x5E0 */ /* float lbl_1_rodata_5E0 = 320.0f; */
/* 0x5E4 */ /* float lbl_1_rodata_5E4 = 240.0f; */
/* 0x5E8 */ /* float lbl_1_rodata_5E8 = 325.0f; */
/* 0x5EC */ /* float lbl_1_rodata_5EC = 60.0f; */
/* 0x5F0 */ /* float lbl_1_rodata_5F0 = 245.0f; */
/* 0x5F4 */ /* float lbl_1_rodata_5F4 = 0.0f; */
/* 0x5F8 */ /* float lbl_1_rodata_5F8 = 1.0f; */
/* 0x5FC */ /* float lbl_1_rodata_5FC = 1200.0f; */
/* 0x600 */ /* float lbl_1_rodata_600 = 0.3f; */
/* 0x604 */ /* float lbl_1_rodata_604 = 4.0f; */
/* 0x608 */ /* float lbl_1_rodata_608 = 10.0f; */
/* 0x60C */ /* float lbl_1_rodata_60C = 150.0f; */
/* 0x610 */ /* float lbl_1_rodata_610 = 2.0f; */
/* 0x618 */ /* double lbl_1_rodata_618 = 10; */
/* 0x620 */ /* double lbl_1_rodata_620 = 3.141592653589793; */
/* 0x628 */ /* float lbl_1_rodata_628 = 180.0f; */
/* 0x630 */ /* double lbl_1_rodata_630 = 180; */
/* 0x638 */ /* float lbl_1_rodata_638 = 20.0f; */
/* 0x640 */ /* double lbl_1_rodata_640 = 4503599627370496; */
/* 0x648 */ /* double lbl_1_rodata_648 = 4503601774854144; */

/* --- .data --- */
/* 0x48C8 */ HuVecF lbl_1_data_48C8 = { 0.0f, 0.0f, 3750.0f }; /* winner position at the ending */
/* 0x48D4 */ HuVecF lbl_1_data_48D4 = { 0.0f, 0.0f, 3.6e+03f }; /* chomp position at the ending */
/* 0x48E0 */ HuVecF lbl_1_data_48E0 = { 0.0f, 8.5e+02f, 5.3e+03f }; /* camera eye (unk024) and eye goal (unk00C) at the ending */
/* 0x48EC */ HuVecF lbl_1_data_48EC = { 0.0f, 1.5e+02f, 3.8e+03f }; /* camera target (unk030) and target goal (unk018) */
/* 0x48F8 */ HuVecF lbl_1_data_48F8 = { 0.0f, 8000.0f, 1500.0f }; /* shadow light position (z rewritten) */
/* 0x4904 */ HuVecF lbl_1_data_4904 = { 0.0f, 1.0f, 0.0f }; /* shadow up */
/* 0x4910 */ HuVecF lbl_1_data_4910 = { 0.0f, 0.0f, 0.0f }; /* shadow target (z rewritten) */
/* 0x491C */ HuVecF lbl_1_data_491C[10] = { { -1.5e+02f, 5e+01f, 3.5e+03f }, { -2.5e+02f, 2e+02f, 3.7e+03f }, { 2.5e+02f, 1.5e+02f, 3.5e+03f }, { -2.5e+02f, 1e+02f, 3.4e+03f }, { -1e+02f, 5e+01f, 4e+03f }, { -1.5e+02f, 1e+02f, 4.1e+03f }, { 1e+02f, 1e+02f, 4.1e+03f }, { 3.5e+02f, 5e+01f, 3.9e+03f }, { 4.5e+02f, 1.5e+02f, 3.5e+03f }, { 1e+02f, 1.5e+02f, 3.3e+03f } }; /* flier positions (moved in place) */
/* 0x4994 */ HuVecF lbl_1_data_4994[10] = { { 3e+01f, 1e+01f, 0.0f }, { 3e+01f, 5.0f, 0.0f }, { 3e+01f, -1e+01f, 0.0f }, { 3e+01f, 5.0f, 0.0f }, { 3e+01f, 1e+01f, 0.0f }, { 3e+01f, 1e+01f, 0.0f }, { 3e+01f, -1e+01f, 0.0f }, { 3e+01f, -1e+01f, 0.0f }, { 3e+01f, -5.0f, 0.0f }, { 3e+01f, -5.0f, 0.0f } }; /* flier rotations */
/* 0x4A0C */ HuVecF lbl_1_data_4A0C[10] = { { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f } }; /* flier velocities */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7A20 */ float lbl_1_bss_7A20; /* fn_1_10CEC x (viewport centre) */
/* 0x7A1C */ float lbl_1_bss_7A1C; /* fn_1_10CEC y */
/* 0x7A08 */ s16 lbl_1_bss_7A08[10]; /* ten flier models 0x3E001F..21 (created in state 2) */

/* --- functions (reference order) --- */
/* 1022 insns */
s32 fn_1_118E8(M504_WORK *work)
{
    s32 done;
    M504_PLAYER *player = &work->unk040[work->unk1214].unk008;
    M504_WANWAN *wanwan = &work->unk040[work->unk1214].unk0DC;
    M504_CAMERA *camera = &work->unk040[work->unk1214].unk3BC;
    s16 *modelId = work->unk012;
    s32 i;
    float time;
    float maxTime;
    float bob;

    done = 0;
    switch (work->unk00A) {
    case 0:
        lbl_1_bss_7A20 = 320.0f;
        lbl_1_bss_7A1C = 240.0f;
        fn_1_10CEC(work, lbl_1_bss_7A20, lbl_1_bss_7A1C);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeColorSet(255, 255, 255);
        for (i = 0; i < 4; i++) {
            if (work->unk040[i].unk15C.unk05C >= 0) {
                fn_1_63C(work->unk040[i].unk15C.unk05C, 1000);
                work->unk040[i].unk15C.unk05C = -1;
            }
        }
        work->unk010 = 0;
        work->unk00A++;
        break;
    case 1:
        if (++work->unk010 >= 60) {
            work->unk010 = 60;
        }
        if (work->unk1214 == 0) {
            lbl_1_bss_7A20 = 320.0f + (325.0f * work->unk010) / 60.0f;
            lbl_1_bss_7A1C = 240.0f + (245.0f * work->unk010) / 60.0f;
        } else if (work->unk1214 == 1) {
            lbl_1_bss_7A20 = 320.0f - (325.0f * work->unk010) / 60.0f;
            lbl_1_bss_7A1C = 240.0f + (245.0f * work->unk010) / 60.0f;
        } else if (work->unk1214 == 2) {
            lbl_1_bss_7A20 = 320.0f + (325.0f * work->unk010) / 60.0f;
            lbl_1_bss_7A1C = 240.0f - (245.0f * work->unk010) / 60.0f;
        } else {
            lbl_1_bss_7A20 = 320.0f - (325.0f * work->unk010) / 60.0f;
            lbl_1_bss_7A1C = 240.0f - (245.0f * work->unk010) / 60.0f;
        }
        fn_1_10CEC(work, lbl_1_bss_7A20, lbl_1_bss_7A1C);
        if (WipeCheckEnd()) {
            break;
        }
        if (work->unk010 < 60) {
            break;
        }
        work->unk010 = 0;
        work->unk00A++;
    case 2:
        Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk040[0].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk040[1].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk040[2].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk040[3].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk040[work->unk1214].unk008.unk018->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk040[work->unk1214].unk15C.unk006, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk040[work->unk1214].unk15C.unk01C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk040[work->unk1214].unk15C.unk01E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(work->unk040[work->unk1214].unk15C.unk020, HU3D_ATTR_DISPOFF);
        work->unk1218 = 1;
        CharModelVoicePanSet(player->unk010, 64);
        camera->unk030 = lbl_1_data_48EC;
        camera->unk018 = camera->unk030;
        camera->unk024 = lbl_1_data_48E0;
        camera->unk00C = camera->unk024;
        player->unk018->trans.x = lbl_1_data_48C8.x;
        player->unk018->trans.y = lbl_1_data_48C8.y;
        player->unk018->trans.z = lbl_1_data_48C8.z;
        player->unk018->rot.y = 0.0f;
        Hu3DModelPosSetV(wanwan->unk00C, &lbl_1_data_48D4);
        Hu3DModelRotSet(wanwan->unk00C, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSet(wanwan->unk00C, wanwan->unk00E[0]);
        Hu3DMotionSpeedSet(wanwan->unk00C, 1.0f);
        Hu3DMotionTimeSet(wanwan->unk00C, 0.0f);
        Hu3DModelAttrSet(wanwan->unk00C, HU3D_MOTATTR_LOOP);
        for (i = 0; i < 4; i++) {
            Hu3DMotionSet(work->unk040[i].unk008.unk018->mdlId[0], work->unk040[i].unk008.unk018->mtnId[0]);
        }
        Hu3DMotionSpeedSet(player->unk018->mdlId[0], 1.0f);
        Hu3DMotionTimeSet(player->unk018->mdlId[0], 0.0f);
        Hu3DModelAttrSet(player->unk018->mdlId[0], HU3D_MOTATTR_LOOP);
        lbl_1_data_48F8.z = 1200.0f + player->unk018->trans.z;
        lbl_1_data_4910.z = player->unk018->trans.z;
        Hu3DShadowMultiPosSet(&lbl_1_data_48F8, &lbl_1_data_4904, &lbl_1_data_4910, lbl_1_data_45E0[work->unk1214]);
        for (i = 0; i < 10; i++) {
            HU3DMODELID model;
            if (i % 3 == 0) {
                model = Hu3DModelCreate(HuDataSelHeapReadNum(0x3E001F, HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_7A08[i] = model;
            } else if (i % 3 == 1) {
                model = Hu3DModelCreate(HuDataSelHeapReadNum(0x3E0020, HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_7A08[i] = model;
            } else {
                model = Hu3DModelCreate(HuDataSelHeapReadNum(0x3E0021, HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_7A08[i] = model;
            }
            Hu3DModelAttrReset(lbl_1_bss_7A08[i], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_7A08[i], HU3D_MOTATTR_LOOP);
            Hu3DModelPosSetV(lbl_1_bss_7A08[i], &lbl_1_data_491C[i]);
            Hu3DModelRotSetV(lbl_1_bss_7A08[i], &lbl_1_data_4994[i]);
            Hu3DModelScaleSet(lbl_1_bss_7A08[i], 0.3f, 0.3f, 0.3f);
            Hu3DModelCameraSet(lbl_1_bss_7A08[i], lbl_1_data_45E0[work->unk1214]);
            Hu3DMotionSpeedSet(lbl_1_bss_7A08[i], 4.0f);
            Hu3DMotionTimeSet(lbl_1_bss_7A08[i], 10.0f * i);
            Hu3DModelShadowSet(lbl_1_bss_7A08[i]);
        }
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        work->unk00A++;
        break;
    case 3:
        if (WipeCheckEnd()) {
            break;
        }
        work->unk1220 = GameMesMgWinnerCreate(player->unk010, -1, -1, -1);
        Hu3DMotionShiftSet(player->unk018->mdlId[0], player->unk018->mtnId[9], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
        Hu3DMotionShiftSet(wanwan->unk00C, wanwan->unk00E[8], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
        work->unk010 = 0;
        work->unk00A++;
        break;
    case 4:
        if (work->unk1230 < 0) {
            work->unk1230 = fn_1_794(0x79);
        }
        if (++work->unk010 >= 209) {
            work->unk1220 = -1;
            work->unk010 = 0;
            work->unk00A++;
        }
        break;
    default:
        work->unk010 = 0;
        done = 1;
        break;
    }
    maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_7A08[0]);
    for (i = 0; i < 10; i++) {
        time = Hu3DMotionTimeGet(lbl_1_bss_7A08[i]);
        if (time < 1.0f) {
            if (lbl_1_data_491C[i].x < 0.0f) {
                lbl_1_data_4A0C[i].x = 4.0f * ((rand8() % 6) - 3);
            } else {
                lbl_1_data_4A0C[i].x = 4.0f * ((rand8() % 6) - 4);
            }
            if (lbl_1_data_491C[i].y < 150.0f) {
                lbl_1_data_4A0C[i].y = 2.0f * ((rand8() % 6) - 3);
            } else {
                lbl_1_data_4A0C[i].y = 2.0f * ((rand8() % 6) - 4);
            }
            PSVECScale(&lbl_1_data_4A0C[i], &lbl_1_data_4A0C[i], 2.0f / maxTime);
        }
        PSVECAdd(&lbl_1_data_491C[i], &lbl_1_data_4A0C[i], &lbl_1_data_491C[i]);
        bob = 10.0 * sin(M_PI * (180.0f + (180.0f * time) / maxTime) / 180.0);
        if (lbl_1_data_491C[i].y < 20.0f) {
            lbl_1_data_491C[i].y = 20.0f;
        }
        Hu3DModelPosSet(lbl_1_bss_7A08[i], lbl_1_data_491C[i].x, bob + lbl_1_data_491C[i].y, lbl_1_data_491C[i].z);
    }
    return done;
}

/* 35 insns */
void fn_1_128E0(M504_WORK *work)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        Hu3DModelAttrSet(lbl_1_bss_7A08[i], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_7A08[i], HU3D_ATTR_DISPOFF);
        Hu3DModelKill(lbl_1_bss_7A08[i]);
    }
}
