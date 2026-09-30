/*
 * m502dll opening.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/opening.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

/* CharFXPlay is called with an implicit declaration on the GameCube: retail passes the s32
 * charNo without the extsh a prototype adds. The port compilers need the declaration. */
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/esprite.h"
#include "game/wipe.h"
#include "game/gamemes.h"
#include "game/charman.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x310 */ /* float lbl_1_rodata_310 = 576.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 240.0f; */
/* 0x318 */ /* s32 lbl_1_rodata_318[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x324 */ /* float lbl_1_rodata_324 = 0.0f; */
/* 0x328 */ /* float lbl_1_rodata_328 = 640.0f; */
/* 0x32C */ /* float lbl_1_rodata_32C = 480.0f; */
/* 0x330 */ /* float lbl_1_rodata_330 = 1.0f; */
/* 0x334 */ /* float lbl_1_rodata_334 = 20.0f; */
/* 0x338 */ /* float lbl_1_rodata_338 = 30000.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 1.2f; */
/* 0x340 */ /* float lbl_1_rodata_340 = 16800.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = -150.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 24.0f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 1.04f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 2400.0f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 180.0f; */
/* 0x358 */ /* float lbl_1_rodata_358 = 60.000004f; */
/* 0x35C */ /* float lbl_1_rodata_35C = 3800.0f; */
/* 0x360 */ /* float lbl_1_rodata_360 = 10.0f; */
/* 0x364 */ /* float lbl_1_rodata_364 = 16.0f; */
/* 0x368 */ /* float lbl_1_rodata_368 = 70.0f; */
/* 0x370 */ /* double lbl_1_rodata_370 = 3.141592653589793; */
/* 0x378 */ /* float lbl_1_rodata_378 = 90.0f; */
/* 0x380 */ /* double lbl_1_rodata_380 = 180; */
/* 0x388 */ /* float lbl_1_rodata_388 = 0.75f; */
/* 0x38C */ /* float lbl_1_rodata_38C = 0.016666668f; */
/* 0x390 */ /* float lbl_1_rodata_390 = 0.25f; */
/* 0x394 */ /* float lbl_1_rodata_394 = 0.5f; */
/* 0x398 */ /* float lbl_1_rodata_398 = 320.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 160.0f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 576.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 240.0f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 30.0f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = 8.0f; */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = 72.0f; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = 144.0f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = 64.0f; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = 4503601774854144; */

/* --- .data --- */
/* 0xFE0 */ HuVecF lbl_1_data_FE0 = { 0.0f, -100.0f, -150.0f };   /* player 0 camera, opening fall: arg 1 of fn_1_1CB4 */
/* 0xFEC */ HuVecF lbl_1_data_FEC = { 0.0f, 1.0f, 0.0f };         /* arg 2 */
/* 0xFF8 */ HuVecF lbl_1_data_FF8 = { 0.0f, 1400.0f, -150.5f };   /* arg 3 */
/* 0x1004 */ HuVecF lbl_1_data_1004 = { 0.0f, 300.0f, 3400.0f };  /* players 1-3 camera: arg 1 */
/* 0x1010 */ HuVecF lbl_1_data_1010 = { 0.0f, 1.0f, 0.0f };       /* arg 2 */
/* 0x101C */ HuVecF lbl_1_data_101C = { 0.0f, -70.0f, -150.0f };  /* arg 3 */
/* 0x1028 */ HuVecF lbl_1_data_1028 = { 0.0f, 300.0f, 4550.0f };  /* split-screen camera: arg 1 of fn_1_1E00 */
/* 0x1034 */ HuVecF lbl_1_data_1034 = { 0.0f, 4000.0f, 500.0f };  /* global light position */
/* 0x1040 */ HuVecF lbl_1_data_1040[3] = { { 0.0f, -1.0f, -1.0f }, { 50.0f, 1400.0f, -200.0f }, { -1.0f, -1.0f, -1.0f } }; /* [0] global light direction; [1], [2] unread here */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5064 gap_05_00005064_bss (0x4) -- dtk filler */
/* 0x5060 */ float lbl_1_bss_5060; /* split-screen width factor, 1 -> 0.25 */
/* 0x505C */ float lbl_1_bss_505C; /* split-screen time, 0 -> 1 in 1/60 steps */
/* 0x5058 */ float lbl_1_bss_5058; /* player 0 fall speed */
/* 0x5054 */ float lbl_1_bss_5054; /* written 0.0f, never read here */
/* 0x5050 */ s32 lbl_1_bss_5050;

/* A owns lbl_1_data_0 (m502 .data) and B owns lbl_1_data_B60 (camera .data). */
extern M502_WORK *lbl_1_data_0;
extern s32 lbl_1_data_B60[8];

/* --- functions (reference order) --- */

/* opening.c fn_1_9468, 83 insns. Create the three hidden split-screen divider sprites. */
void fn_1_9468(M502_OPENING *opening, M502_WORK *work)
{
    memset(opening, 0, sizeof(M502_OPENING));
    opening->unk000 = work;
    opening->unk01C[0] = espEntry(DATANUM(DATA_m502, 0x90), 12, 0);
    espDispOff(opening->unk01C[0]);
    espDrawNoSet(opening->unk01C[0], 0);
    espPosSet(opening->unk01C[0], 576.0f, 240.0f);
    espAttrSet(opening->unk01C[0], HUSPR_ATTR_NOANIM);
    opening->unk01C[1] = espEntry(DATANUM(DATA_m502, 0x90), 12, 0);
    espDispOff(opening->unk01C[1]);
    espDrawNoSet(opening->unk01C[1], 0);
    espPosSet(opening->unk01C[1], 576.0f, 240.0f);
    espAttrSet(opening->unk01C[1], HUSPR_ATTR_NOANIM);
    opening->unk01C[2] = espEntry(DATANUM(DATA_m502, 0x90), 12, 0);
    espDispOff(opening->unk01C[2]);
    espDrawNoSet(opening->unk01C[2], 0);
    espPosSet(opening->unk01C[2], 576.0f, 240.0f);
    espAttrSet(opening->unk01C[2], HUSPR_ATTR_NOANIM);
}

/* opening.c fn_1_95B4, 20 insns. Kill the divider sprites. */
void fn_1_95B4(M502_OPENING *opening)
{
    espKill(opening->unk01C[0]);
    espKill(opening->unk01C[1]);
    espKill(opening->unk01C[2]);
    memset(opening, 0, sizeof(M502_OPENING));
}

/* opening.c fn_1_9604, 16 insns. Show the divider sprites. */
void fn_1_9604(M502_OPENING *opening)
{
    espDispOn(opening->unk01C[0]);
    espDispOn(opening->unk01C[1]);
    espDispOn(opening->unk01C[2]);
}

/* opening.c fn_1_9644, 1204 insns. The opening: player 0 drops in, then the screen splits. Returns 1 when done. */
int fn_1_9644(M502_WORK *work)
{
    M502_CHAR *chr;
    M502_OPENING *opening;
    M502_STAGE *stage;
    M502_PLAYER *player;
    s32 i;
    float t;

    chr = &work->unk3A4[0].unkF58;
    opening = &work->unk380;
    stage = &work->unk3A4[0].unkFD4;
    switch (work->unk00C) {
    case 0:
        Hu3DGLightPosSetV(work->unk378.unk004, &lbl_1_data_1034, &lbl_1_data_1040[0]);
        Hu3DModelAttrSet(work->unk3A4[1].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk3A4[2].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(work->unk3A4[3].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f);
        Hu3DCameraScissorSet(1, 0, 0, 640, 480);
        fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_FE0, &lbl_1_data_FEC, &lbl_1_data_FF8);
        Hu3DCameraViewportSet(2, 640.0f, 0.0f, 0.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(2, 20.0f, 20.0f, 30000.0f, 0.0f);
        Hu3DCameraScissorSet(2, 640, 0, 0, 480);
        fn_1_1CB4(&work->unk3A4[1].unk1048, &lbl_1_data_1004, &lbl_1_data_1010, &lbl_1_data_101C);
        Hu3DCameraViewportSet(4, 640.0f, 0.0f, 0.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(4, 20.0f, 20.0f, 30000.0f, 0.0f);
        Hu3DCameraScissorSet(4, 320, 0, 0, 480);
        fn_1_1CB4(&work->unk3A4[2].unk1048, &lbl_1_data_1004, &lbl_1_data_1010, &lbl_1_data_101C);
        Hu3DCameraViewportSet(8, 640.0f, 0.0f, 0.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(8, 20.0f, 20.0f, 30000.0f, 0.0f);
        Hu3DCameraScissorSet(8, 640, 0, 0, 480);
        fn_1_1CB4(&work->unk3A4[3].unk1048, &lbl_1_data_1004, &lbl_1_data_1010, &lbl_1_data_101C);
        chr->unk01C->trans.y = 16800.0f;
        Hu3DMotionSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[4]);
        Hu3DData[chr->unk01C->mdlId[0]].motAttr &= ~HU3D_MOTATTR_LOOP;
        Hu3DMotionTimeSet(chr->unk01C->mdlId[0], 0.0f);
        Hu3DMotionSpeedSet(chr->unk01C->mdlId[0], 0.0f);
        for (i = 0; i < 4; i++) {
            chr = &work->unk3A4[i].unkF58;
            chr->unk01C->trans.z = -150.0f;
        }
        work->unk00C = 1;
        break;
    case 1:
        if (!WipeCheckEnd()) {
            lbl_1_bss_5058 = 24.0f;
            fn_1_198(0x636);
            work->unk00C = 2;
        }
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        lbl_1_bss_5058 *= 1.04f;
        if (chr->unk01C->trans.y >= 2400.0f) {
            if (lbl_1_bss_5058 >= 180.0f) {
                lbl_1_bss_5058 = 180.0f;
            }
        } else if (lbl_1_bss_5058 >= 60.000004f) {
            lbl_1_bss_5058 = 60.000004f;
        }
        chr->unk01C->trans.y -= lbl_1_bss_5058;
        if (work->unk00C == 2) {
            if (chr->unk01C->trans.y < 3800.0f) {
                fn_1_1E00(&work->unk3A4[0].unk1048, &lbl_1_data_1004, &lbl_1_data_1010, &lbl_1_data_101C);
                lbl_1_bss_5054 = 0.0f;
                work->unk00C = 3;
            }
            break;
        }
        if (work->unk00C == 3) {
            if (chr->unk01C->trans.y < 0.0f) {
                chr->unk01C->trans.y = 0.0f;
                {
                    HuVecF dustPos;
                    HuVecF pos = { 0.0f, 0.0f, 0.0f };
                    HuVecF *src;
                    pos.x = chr->unk01C->trans.x;
                    pos.y = chr->unk01C->trans.y - 10.0f;
                    pos.z = chr->unk01C->trans.z;
                    src = &pos;
                    dustPos = *src;
                    CharModelLandDustCreate(chr->unk014, &dustPos);
                }
                CharFXPlay(chr->unk014, 0x96);
                Hu3DModelAttrReset(chr->unk01C->mdlId[0], HU3D_MOTATTR_LOOP);
                Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[4], 0.0f, 0.0f, HU3D_MOTATTR_NONE);
                Hu3DMotionSpeedSet(chr->unk01C->mdlId[0], 1.0f);
                work->unk00C = 4;
                fn_1_198(0x21);
            }
        } else {
            if (work->unk00C == 4 && Hu3DMotionEndCheck(chr->unk01C->mdlId[0])) {
                Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[0], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
                work->unk00C = 5;
            }
            chr->unk01C->trans.y = 0.0f;
        }
        if (fn_1_1E64(&work->unk3A4[0].unk1048, 70.0f, &lbl_1_data_1010)) {
            lbl_1_bss_5054 = 0.0f;
            fn_1_1CB4(&work->unk3A4[0].unk1048, &lbl_1_data_1004, &lbl_1_data_1010, &lbl_1_data_101C);
            lbl_1_bss_505C = 0.0f;
            Hu3DModelAttrReset(work->unk3A4[1].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk3A4[2].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(work->unk3A4[3].unkF58.unk01C->mdlId[0], HU3D_ATTR_DISPOFF);
            work->unk00C = 6;
        }
        break;
    case 6:
        lbl_1_bss_5060 = HuSin(90.0f * lbl_1_bss_505C);
        lbl_1_bss_5060 = 1.0f - 0.75f * (lbl_1_bss_5060 * lbl_1_bss_5060);
        lbl_1_bss_505C += 1.0f / 60.0f;
        if (lbl_1_bss_505C >= 1.0f) {
            lbl_1_bss_5060 = 0.25f;
            work->unk00C = 7;
        }
        Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f * lbl_1_bss_5060, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f * lbl_1_bss_5060);
        Hu3DCameraScissorSet(1, 0, 0, 640.0f * lbl_1_bss_5060, 480);
        Hu3DCameraViewportSet(16, 0.0f, 0.0f, 640.0f * lbl_1_bss_5060, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(16, 20.0f, 20.0f, 30000.0f, 1.2f * lbl_1_bss_5060);
        Hu3DCameraScissorSet(16, 0, 0, 640.0f * lbl_1_bss_5060, 480);
        for (i = 0; i < 3; i++) {
            t = (0.5f + 0.25f * i) - lbl_1_bss_5060;
            if (t < 0.0f) {
                t = 0.0f;
            }
            if (t > 0.25f) {
                t = 0.25f;
            }
            Hu3DCameraViewportSet(lbl_1_data_B60[i + 1], (320.0f + 160.0f * i) - 640.0f * t, 0.0f, 640.0f * t, 480.0f, 0.0f, 1.0f);
            Hu3DCameraPerspectiveSet(lbl_1_data_B60[i + 1], 20.0f, 20.0f, 30000.0f, 1.2f * t);
            Hu3DCameraScissorSet(lbl_1_data_B60[i + 1], (320.0f + 160.0f * i) - 640.0f * t, 0, 640.0f * t, 480);
            Hu3DCameraViewportSet(lbl_1_data_B60[i + 5], (320.0f + 160.0f * i) - 640.0f * t, 0.0f, 640.0f * t, 480.0f, 0.0f, 1.0f);
            Hu3DCameraPerspectiveSet(lbl_1_data_B60[i + 5], 20.0f, 20.0f, 30000.0f, 1.2f * t);
            Hu3DCameraScissorSet(lbl_1_data_B60[i + 5], (320.0f + 160.0f * i) - 640.0f * t, 0, 640.0f * t, 480);
            t = lbl_1_bss_5060;
            if (t < 0.25f + 0.25f * i) {
                t = 0.25f + 0.25f * i;
            }
            espPosSet(opening->unk01C[i], 576.0f * t, 240.0f);
            fn_1_1E00(&work->unk3A4[0].unk1048, &lbl_1_data_1028, &lbl_1_data_1010, &lbl_1_data_101C);
            fn_1_1E00(&work->unk3A4[1].unk1048, &lbl_1_data_1028, &lbl_1_data_1010, &lbl_1_data_101C);
            fn_1_1E00(&work->unk3A4[2].unk1048, &lbl_1_data_1028, &lbl_1_data_1010, &lbl_1_data_101C);
            fn_1_1E00(&work->unk3A4[3].unk1048, &lbl_1_data_1028, &lbl_1_data_1010, &lbl_1_data_101C);
        }
        break;
    case 7:
        fn_1_1E64(&work->unk3A4[0].unk1048, 30.0f, &lbl_1_data_1010);
        fn_1_1E64(&work->unk3A4[1].unk1048, 30.0f, &lbl_1_data_1010);
        fn_1_1E64(&work->unk3A4[2].unk1048, 30.0f, &lbl_1_data_1010);
        fn_1_1E64(&work->unk3A4[3].unk1048, 30.0f, &lbl_1_data_1010);
        if (work->unk018 < 0) {
            work->unk018 = GameMesMgStartCreate();
            if (lbl_1_data_0->unk5014) {
                for (i = 0; i < 4; i++) {
                    player = &work->unk3A4[i];
                    player->unk1314 = MgTimerCreate(2);
                    MgTimerPosSet(player->unk1314, 8.0f + (72.0f + 144.0f * player->unk004), 64.0f);
                    MgTimerDigitColorSet(player->unk1314, 255, 255, 255);
                    MgTimerParamSet(player->unk1314, 0, 0, 0);
                    MgTimerModeOnSet(player->unk1314, 0);
                }
            }
        } else {
            if (work->unk5018 < 0) {
                work->unk5018 = fn_1_318(0x3C);
            }
            if (!GameMesStatGet(work->unk018)) {
                work->unk008 = 2;
                work->unk00C = 0;
                work->unk018 = -1;
                return 1;
            }
        }
        break;
    }
    return 0;
}
