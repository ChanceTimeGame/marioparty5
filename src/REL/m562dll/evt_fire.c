/*
 * m562dll evt_fire.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_fire.s.
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
/* 0xB38 lbl_1_rodata_B38 (0xC): 0x00000000 0x447A0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB44 lbl_1_rodata_B44 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB50 lbl_1_rodata_B50 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB5C lbl_1_rodata_B5C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB68 lbl_1_rodata_B68 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B74 = 0.04f; /* 0xB74 */
static const float lbl_1_rodata_B78 = 0.03f; /* 0xB78 */
static const float lbl_1_rodata_B7C = 120.0f; /* 0xB7C */
static const double lbl_1_rodata_B80 = 0.25; /* 0xB80 */
static const double lbl_1_rodata_B88 = 2.0; /* 0xB88 */
static const double lbl_1_rodata_B90 = 3.141592653589793; /* 0xB90 */
static const float lbl_1_rodata_B98 = 180.0f; /* 0xB98 */
static const double lbl_1_rodata_BA0 = 180.0; /* 0xBA0 */
static const float lbl_1_rodata_BA8 = 0.0f; /* 0xBA8 */
static const float lbl_1_rodata_BAC = 40.0f; /* 0xBAC */
static const float lbl_1_rodata_BB0 = 56.0f; /* 0xBB0 */
static const float lbl_1_rodata_BB4 = 50.0f; /* 0xBB4 */
static const float lbl_1_rodata_BB8 = 0.06f; /* 0xBB8 */
static const float lbl_1_rodata_BBC = 3.0f; /* 0xBBC */
static const float lbl_1_rodata_BC0 = 60.0f; /* 0xBC0 */
static const float lbl_1_rodata_BC4 = 1000.0f; /* 0xBC4 */
static const float lbl_1_rodata_BC8 = 1.0f; /* 0xBC8 */
static const float lbl_1_rodata_BCC = 30.0f; /* 0xBCC */
static const float lbl_1_rodata_BD0 = 0.55f; /* 0xBD0 */
static const float lbl_1_rodata_BD4 = 90.0f; /* 0xBD4 */
static const float lbl_1_rodata_BD8 = 5.0f; /* 0xBD8 */
static const float lbl_1_rodata_BDC = 0.9f; /* 0xBDC */
static const float lbl_1_rodata_BE0 = 10.0f; /* 0xBE0 */
/* 0xBE8 lbl_1_rodata_BE8 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x794C */ HuVecF lbl_1_bss_794C;
/* 0x7940 */ HuVecF lbl_1_bss_7940;
/* 0x7934 */ HuVecF lbl_1_bss_7934;
/* 0x7932 gap_05_00007932_bss (0x2): alignment gap */
/* 0x7930 */ s16 lbl_1_bss_7930;

/* --- functions (reference order), .data placed before its first user --- */
/* 0xCC8 */ HuVecF lbl_1_data_CC8[2] = { { 0.0f, 347.9f, 26.0f }, { 0.0f, 1000.0f, 1400.0f } };
/* 0xCE0 */ HuVecF lbl_1_data_CE0[2] = { { 0.0f, 346.54f, 21.37f }, { 0.0f, 100.0f, -200.0f } };

/* 897 insns. Phase 1 -> 2: Bowser talks (message 0x410001), the three fire rings rise and spread,
   the player walks back to the centre. Returns 1 when done. */
s32 fn_1_252B4(M562_WORK *work)
{
    M562_LIGHT *light;
    M562_MAINMDL *mainMdl;
    M562_CAMERA *camera;
    M562_PLAYER *player;
    M562_PAD *pad;
    M562_KOOPA *koopa;
    M562_KOOPABOSS *boss;
    M562_FIRERING *firering;
    M562_FIRERINGSUB *ring0;
    M562_FIRERINGSUB *ring1;
    M562_FIRERINGSUB *ring2;
    M562_BACK *back;
    M562_FIRE *fire;
    s32 result;
    float t;
    float dist;
    HuVecF dir;
    HuVecF target;

    light = &work->light;
    mainMdl = &work->mainMdl;
    camera = &work->camera[0];
    player = &work->player;
    pad = &player->unk06C;
    koopa = &work->koopa;
    boss = &work->koopaboss;
    firering = &work->firering;
    ring0 = &firering->unk18[0];
    ring1 = &firering->unk18[1];
    ring2 = &firering->unk18[2];
    back = &work->back;
    fire = &work->fire;
    result = 0;
    switch (work->unk0010) {
    case 0:
        back->unk24 = 1;
        back->unk28 = 0;
        fn_1_16F0(work, 1);
        lbl_1_bss_794C = ring0->unk1C;
        lbl_1_bss_7940 = ring1->unk1C;
        lbl_1_bss_7934 = ring2->unk1C;
        ring0->unk1C = ring1->unk1C = ring2->unk1C = (HuVecF) { 0.0f, 1000.0f, 0.0f };
        player->unk09A = 1;
        player->unk09C = 1;
        if (GWSubGameNoGet() >= 1) {
            camera->unk0A = 1;
            camera->unk10 = lbl_1_data_CC8[1];
            camera->unk1C = lbl_1_data_CE0[1];
            camera->unk0C = 0;
            camera->unk7C = 0.04f;
            camera->unk80 = 0.04f;
            work->unk001C = 0;
            work->unk0010 = 10;
            break;
        }
        camera->unk0A = 1;
        camera->unk10 = lbl_1_data_CC8[0];
        camera->unk1C = lbl_1_data_CE0[0];
        camera->unk0C = 0;
        camera->unk7C = 0.04f;
        camera->unk80 = 0.03f;
        work->unk0010++;
    case 1:
        t = work->unk001C / 120.0f;
        fn_1_22694(light, 1, t);
        fn_1_4748(back, 1, t);
        Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * sin(M_PI * (180.0f * t) / 180.0));
        if (work->unk001C < 60) {
            if (work->unk28AC < 0) {
                work->unk28AC = fn_1_814(0x8B5);
            }
        } else if (work->unk001C == 60) {
            if (work->unk28AC >= 0) {
                fn_1_864(work->unk28AC, 3000);
            }
        }
        target = (HuVecF) { 0.0f, 0.0f, 0.0f };
        PSVECSubtract(&target, &player->unk0A0, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dist > 40.0f) {
            PSVECNormalize(&dir, &dir);
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            pad->unk10 = 56.0f * dir.x;
            pad->unk11 = 56.0f * -dir.z;
            fn_1_7D58(player);
        } else {
            player->unk09A = 0;
            player->unk09C = 1;
        }
        if (work->unk001C++ > 120 && dist <= 50.0f) {
            player->unk0A0 = (HuVecF) { 0.0f, 0.0f, 0.0f };
            player->unk09A = 0;
            player->unk09C = 1;
            player->unk094 = player->unk090 = 0.0f;
            player->unk0AC.y = player->unk090;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 2:
        HuWinExOpen(work->unk28A4);
        HuWinMesSet(work->unk28A4, 0x410001);
        koopa->motNext = 5;
        koopa->motShiftNext = 30;
        koopa->motLoop = 1;
        koopa->step = 10;
        fn_1_814(0x8C5);
        lbl_1_bss_7930 = 0;
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 3:
        if (HuWinStatGet(work->unk28A4) == 2) {
            lbl_1_bss_7930 = 0;
        } else if (HuWinStatGet(work->unk28A4) == 1) {
            if (++lbl_1_bss_7930 == 5) {
                koopa->motCur = 0;
                koopa->motNext = 5;
                koopa->motLoop = 1;
            }
        } else if (HuWinStatGet(work->unk28A4) == 0) {
            lbl_1_bss_7930 = 0;
            koopa->motNext = 0;
            koopa->motLoop = 1;
            player->unk09A = 26;
            player->unk09C = 1;
            camera->unk0C = 0;
            camera->unk10 = lbl_1_data_CC8[1];
            camera->unk1C = lbl_1_data_CE0[1];
            camera->unk7C = 0.06f;
            camera->unk80 = 0.06f;
            HuWinExClose(work->unk28A4);
            HuWinHomeClear(work->unk28A4);
            firering->unk10 = 1;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 4:
        Hu3DMotionSpeedSet(player->unk024, 3.0f);
        t = work->unk001C / 60.0f;
        ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f + 1000.0f * (1.0f - t);
        if (work->unk001C == 20 && firering->unkCC < 0) {
            firering->unkCC = fn_1_814(0x8A2);
        }
        if (++work->unk001C > 60) {
            fn_1_21B68(camera, 1, 50, 30.0f, 0.55f, 90.0f);
            omVibrate(player->unk014, 10, 12, 0);
            Hu3DMotionSpeedSet(player->unk024, 1.0f);
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 5:
        t = work->unk001C / 60.0f;
        pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
        if (work->unk001C >= 10) {
            if (work->unk001C == 10) {
                pad->unk0C = 256;
            }
            pad->unk08 = 256;
        }
        fn_1_7D58(player);
        ring0->unk1C.x = lbl_1_bss_794C.x * t;
        ring0->unk1C.z = lbl_1_bss_794C.z * t;
        ring1->unk1C.x = lbl_1_bss_7940.x * t;
        ring1->unk1C.z = lbl_1_bss_7940.z * t;
        ring2->unk1C.x = lbl_1_bss_7934.x * t;
        ring2->unk1C.z = lbl_1_bss_7934.z * t;
        if (++work->unk001C > 60) {
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            player->unk004 = 0;
            player->unk006 = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 6:
        player->unk09A = 28;
        player->unk09C = 0;
        if (++work->unk001C > 30) {
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 7:
        if (work->unk28AC >= 0) {
            fn_1_83C(work->unk28AC);
            work->unk28AC = -1;
        }
        if (GWSubGameNoGet() < 1) {
            GWSubGameNoSet(1);
        }
        player->unk004 = player->unk006 = 0;
        work->unk0010 = 0;
        result = 1;
        break;
    case 10:
        t = work->unk001C / 120.0f;
        fn_1_22694(light, 1, t);
        fn_1_4748(back, 1, t);
        Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * sin(M_PI * (180.0f * t) / 180.0));
        if (work->unk001C < 60) {
            if (work->unk28AC < 0) {
                work->unk28AC = fn_1_814(0x8B5);
            }
        } else if (work->unk001C == 60) {
            if (work->unk28AC >= 0) {
                fn_1_864(work->unk28AC, 3000);
            }
        }
        koopa->motNext = 0;
        koopa->motLoop = 1;
        target = (HuVecF) { 0.0f, 0.0f, 0.0f };
        PSVECSubtract(&target, &player->unk0A0, &dir);
        dir.y = 0.0f;
        dist = PSVECMag(&dir);
        if (dist > 5.0f) {
            PSVECNormalize(&dir, &dir);
            pad->unk08 = pad->unk0C = pad->unk10 = pad->unk11 = 0;
            pad->unk10 = 56.0f * dir.x;
            pad->unk11 = 56.0f * -dir.z;
            fn_1_7D58(player);
        } else {
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 1.0f;
            if (fn_1_AD98(player, &dir, 0.9f)) {
                player->unk09A = 0;
                player->unk09C = 1;
            }
        }
        work->unk001C++;
        if (work->unk001C > 120 && dist <= 10.0f) {
            player->unk0A0 = (HuVecF) { 0.0f, 0.0f, 0.0f };
            player->unk094 = player->unk090 = 0.0f;
            player->unk0AC.y = player->unk090;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 11:
        dir.x = 0.0f;
        dir.y = 0.0f;
        dir.z = 1.0f;
        if (fn_1_AD98(player, &dir, 0.9f)) {
            player->unk09A = 26;
            player->unk09C = 1;
            firering->unk10 = 1;
            work->unk001C = 0;
            work->unk0010 = 4;
        }
        break;
    }
    return result;
}
