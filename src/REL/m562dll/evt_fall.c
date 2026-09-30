/*
 * m562dll evt_fall.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/evt_fall.s.
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
static const float lbl_1_rodata_CD0 = 0.99f; /* 0xCD0 */
static const float lbl_1_rodata_CD4 = 125.0f; /* 0xCD4 */
static const float lbl_1_rodata_CD8 = -500.0f; /* 0xCD8 */
static const float lbl_1_rodata_CDC = 250.0f; /* 0xCDC */
static const float lbl_1_rodata_CE0 = -375.0f; /* 0xCE0 */
static const float lbl_1_rodata_CE4 = 0.04f; /* 0xCE4 */
static const float lbl_1_rodata_CE8 = 3.0f; /* 0xCE8 */
static const float lbl_1_rodata_CEC = 120.0f; /* 0xCEC */
static const float lbl_1_rodata_CF0 = 1.0f; /* 0xCF0 */
static const float lbl_1_rodata_CF4 = 0.0f; /* 0xCF4 */
static const double lbl_1_rodata_CF8 = 0.25; /* 0xCF8 */
static const double lbl_1_rodata_D00 = 2.0; /* 0xD00 */
static const double lbl_1_rodata_D08 = 3.141592653589793; /* 0xD08 */
static const float lbl_1_rodata_D10 = 180.0f; /* 0xD10 */
static const double lbl_1_rodata_D18 = 180.0; /* 0xD18 */
static const float lbl_1_rodata_D20 = 10.0f; /* 0xD20 */
static const float lbl_1_rodata_D24 = 0.95f; /* 0xD24 */
static const float lbl_1_rodata_D28 = 90.0f; /* 0xD28 */
static const float lbl_1_rodata_D2C = 1.5f; /* 0xD2C */
static const float lbl_1_rodata_D30 = -2000.0f; /* 0xD30 */
/* 0xD38 lbl_1_rodata_D38 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x798E gap_05_0000798E_bss (0x2): alignment gap */
/* 0x798C */ s16 lbl_1_bss_798C;
/* 0x7964 */ s16 lbl_1_bss_7964[20];
/* 0x7960 */ M562_STAGETILE *lbl_1_bss_7960;

/* --- functions (reference order), .data placed before its first user --- */
/* 0xD98 */ HuVecF lbl_1_data_D98 = { 0.0f, 1000.0f, 1400.0f };
/* 0xDA4 */ HuVecF lbl_1_data_DA4 = { 0.0f, 100.0f, -200.0f };

/* 478 insns. Phase 3 -> 4 transition: the floor collapses tile by tile, the player falls. Returns 1 when done. */
s32 fn_1_27950(M562_WORK *work)
{
    M562_MAINMDL *mainMdl;
    M562_CAMERA *camera;
    M562_STAGE *stage;
    M562_PLAYER *player;
    M562_PAD *pad;
    M562_KOOPA *koopa;
    M562_KOOPABOSS *boss;
    M562_BACK *back;
    M562_FIRE *fire;
    s32 result;
    float t;
    s32 i;
    s16 ix;
    s16 iz;
    s16 a;
    s16 b;
    s16 tmp;
    s32 subGameNo;
    M562_STAGETILE *tile;

    mainMdl = &work->mainMdl;
    camera = &work->camera[0];
    stage = &work->stage;
    player = &work->player;
    pad = &player->unk06C;
    koopa = &work->koopa;
    boss = &work->koopaboss;
    back = &work->back;
    fire = &work->fire;
    result = 0;
    switch (work->unk0010) {
    case 0:
        back->unk24 = 0;
        back->unk28 = 0;
        subGameNo = GwSystem.subGameNo;
        if (subGameNo >= 3) {
            work->unk001C = 0;
            work->unk0010 = 4;
            break;
        }
        ix = 0.99f * (125.0f + (player->unk0A0.x - -500.0f)) / 250.0f;
        iz = 0.99f * (125.0f + (player->unk0A0.z - -375.0f)) / 250.0f;
        lbl_1_bss_7960 = &stage->unk008[ix + iz * 5];
        for (i = 0; i < 20; i++) {
            lbl_1_bss_7964[i] = i;
        }
        for (i = 0; i < 20; i++) {
            a = frand() % 20;
            b = frand() % 20;
            tmp = lbl_1_bss_7964[a];
            lbl_1_bss_7964[a] = lbl_1_bss_7964[b];
            lbl_1_bss_7964[b] = tmp;
        }
        camera->unk0A = 1;
        camera->unk10 = lbl_1_data_D98;
        camera->unk1C = lbl_1_data_DA4;
        camera->unk0C = 0;
        camera->unk7C = 0.04f;
        camera->unk80 = 0.04f;
        player->unk004 = 0;
        player->unk09A = 26;
        player->unk09C = 1;
        Hu3DMotionSpeedSet(player->unk024, 3.0f);
        lbl_1_bss_798C = 0;
        work->unk001C = 0;
        work->unk0010++;
    case 1:
        if (work->unk28AC < 0) {
            work->unk28AC = fn_1_814(0x8B5);
        }
        t = work->unk001C / 120.0f;
        t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
        Hu3DMotionSpeedSet(back->unk40, 0.25 + 2.0 * sin(M_PI * (180.0f * t) / 180.0));
        Hu3DMotionSpeedSet(player->unk024, 3.0f);
        work->unk001C++;
        if (work->unk001C % 10 == 0) {
            fn_1_21B68(camera, 1, 50, 10.0f, 0.95f, 90.0f);
            omVibrate(player->unk014, 20, 12, 0);
        }
        if (work->unk001C % 5 == 0) {
            if (lbl_1_bss_798C < 20) {
                tile = &stage->unk008[lbl_1_bss_7964[lbl_1_bss_798C]];
                if (tile != lbl_1_bss_7960 && tile != koopa->tile) {
                    fn_1_814(0x8C3);
                    tile->unk04 = 10;
                }
                lbl_1_bss_798C++;
            } else {
                Hu3DMotionSpeedSet(player->unk024, 1.0f);
                work->unk001C = 0;
                work->unk0010++;
            }
        }
        break;
    case 2:
        fn_1_814(0x8C3);
        lbl_1_bss_7960->unk04 = 10;
        player->unk0C4 = 0.0f;
        player->unk004 = 0;
        player->unk09A = 23;
        player->unk09C = 0;
        Hu3DMotionSpeedSet(player->unk024, 1.0f);
        work->unk001C = 0;
        work->unk0010++;
        break;
    case 3:
        work->unk001C++;
        if (work->unk001C == 28) {
            player->unk09A = 0;
            player->unk09C = 0;
        }
        if (work->unk001C >= 30) {
            player->unk0C4 -= 1.5f;
            player->unk0A0.y += player->unk0C4;
            if (player->unk0A0.y < -2000.0f) {
                work->unk001C = 0;
                work->unk0010++;
            }
        }
        break;
    case 4:
        if (++work->unk001C >= 30) {
            WipeCreate(2, 0, 60);
            WipeColorSet(0, 0, 0);
            player->unk004 = player->unk006 = 0;
            work->unk001C = 0;
            work->unk0010++;
        }
        break;
    case 5:
        work->unk001C++;
        if (WipeCheckEnd() == 0) {
            work->unk001C = 0;
            work->unk0010 = 0;
            result = 1;
        }
        break;
    }
    return result;
}
