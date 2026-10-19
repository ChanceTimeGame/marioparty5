/*
 * carddll dice.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/dice.s.
 */

#include "REL/carddll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/esprite.h"
#include "game/frand.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_5A8 = 600.0f; /* 0x5A8 */
static const float lbl_1_rodata_5AC = 0.0f; /* 0x5AC */
static const float lbl_1_rodata_5B0 = 100.0f; /* 0x5B0 */
static const float lbl_1_rodata_5B4 = -50.0f; /* 0x5B4 */
static const float lbl_1_rodata_5B8 = 4.0f; /* 0x5B8 */
static const float lbl_1_rodata_5BC = 2.0f; /* 0x5BC */
static const float lbl_1_rodata_5C0 = 3.0f; /* 0x5C0 */
/* 0x5C8 lbl_1_rodata_5C8 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x5D0 lbl_1_rodata_5D0 (0xC): 0x43900000 0x43700000 0x44BB8000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5DC = 10.0f; /* 0x5DC */
static const float lbl_1_rodata_5E0 = 15.0f; /* 0x5E0 */
static const float lbl_1_rodata_5E4 = 400.0f; /* 0x5E4 */
static const float lbl_1_rodata_5E8 = 210.0f; /* 0x5E8 */
static const float lbl_1_rodata_5EC = 5.0f; /* 0x5EC */
static const float lbl_1_rodata_5F0 = 1.0f; /* 0x5F0 */
static const float lbl_1_rodata_5F4 = 0.1f; /* 0x5F4 */
static const float lbl_1_rodata_5F8 = 0.015f; /* 0x5F8 */
static const double lbl_1_rodata_600 = 0.02; /* 0x600 */
static const float lbl_1_rodata_608 = 350.0f; /* 0x608 */
/* 0x60C lbl_1_rodata_60C (0xC): 0x3F99999A 0x3F99999A 0x3F99999A -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_618 = 300.0f; /* 0x618 */
static const float lbl_1_rodata_61C = 45.0f; /* 0x61C */
static const float lbl_1_rodata_620 = 0.4f; /* 0x620 */
static const float lbl_1_rodata_624 = 0.02f; /* 0x624 */
static const float lbl_1_rodata_628 = 79.0f; /* 0x628 */
static const float lbl_1_rodata_62C = 102.0f; /* 0x62C */
static const float lbl_1_rodata_630 = 0.06666667f; /* 0x630 */
static const float lbl_1_rodata_634 = 0.05f; /* 0x634 */
/* 0x638 lbl_1_rodata_638 (0xC): 0x3EB33333 0x3EB33333 0x3EB33333 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_644 = 1000.0f; /* 0x644 */
static const float lbl_1_rodata_648 = 180.0f; /* 0x648 */
/* 0x64C lbl_1_rodata_64C (0xC): 0x43F28000 0x43CA8000 0x447A0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_658 = 128.0f; /* 0x658 */
static const float lbl_1_rodata_65C = 480.0f; /* 0x65C */
static const float lbl_1_rodata_660 = 360.4f; /* 0x660 */
static const float lbl_1_rodata_664 = 484.0f; /* 0x664 */
static const float lbl_1_rodata_668 = 336.0f; /* 0x668 */
static const float lbl_1_rodata_66C = 492.0f; /* 0x66C */
static const float lbl_1_rodata_670 = 500.0f; /* 0x670 */
static const float lbl_1_rodata_674 = 516.0f; /* 0x674 */
static const float lbl_1_rodata_678 = 362.0f; /* 0x678 */
static const float lbl_1_rodata_67C = 512.0f; /* 0x67C */
static const float lbl_1_rodata_680 = 528.0f; /* 0x680 */
static const float lbl_1_rodata_684 = 0.45f; /* 0x684 */
static const float lbl_1_rodata_688 = -10.0f; /* 0x688 */
static const float lbl_1_rodata_68C = 8.0f; /* 0x68C */
static const float lbl_1_rodata_690 = 0.0625f; /* 0x690 */
static const float lbl_1_rodata_694 = 360.0f; /* 0x694 */
/* 0x698 lbl_1_rodata_698 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6A4 lbl_1_rodata_6A4 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6B0 lbl_1_rodata_6B0 (0xC): 0x00000000 0x00000000 0xC2C80000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_6BC = -1.0f; /* 0x6BC */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1298 */ s32 lbl_1_bss_1298[4];
/* 0x1270 */ s32 lbl_1_bss_1270[10];
/* 0x1248 */ float lbl_1_bss_1248[10];
/* 0x1220 */ s32 lbl_1_bss_1220[10];
/* 0x11F8 */ float lbl_1_bss_11F8[10];
/* 0x11F4 */ s16 lbl_1_bss_11F4;
/* 0x11F0 */ s32 lbl_1_bss_11F0;
/* 0x11EC */ s32 lbl_1_bss_11EC;
/* 0x11EA gap_05_000011EA_bss (0x2): alignment gap */
/* 0x11E8 */ s16 lbl_1_bss_11E8;
/* 0x11E6 */ s16 lbl_1_bss_11E6;
/* 0x11E4 */ s16 lbl_1_bss_11E4;
/* 0x11E2 */ s16 lbl_1_bss_11E2;
/* 0x11E0 */ s16 lbl_1_bss_11E0;
/* 0x11DC */ s32 lbl_1_bss_11DC;
/* 0x11D8 */ s32 lbl_1_bss_11D8;
/* 0x11CC */ float lbl_1_bss_11CC[3];
/* 0x11C0 */ s16 lbl_1_bss_11C0[6];
/* 0x11BE */ s16 lbl_1_bss_11BE;
/* 0x11BA */ s16 lbl_1_bss_11BA[2]; /* [1] at 0x11BC is used; dtk sizes it 2 and calls 0x11BC a gap */
/* 0x11B8 */ s16 lbl_1_bss_11B8;

/* --- functions (reference order), .data placed before its first user --- */
/* 479 insns */
s32 fn_1_325F4(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 type;
    s32 result;
    HuVecF pos;
    HuVecF dir;
    HuVecF pos2d;

    result = 0;
    player = &work->player[work->unk174[work->unk170]];
    type = (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x100) ? 0
        : (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x200) ? 1
        : (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x400) ? 2
        : -1;
    if (type == -1) {
        return 1;
    }
    switch (lbl_1_bss_1298[0]) {
        case 0:
            if (type == 2) {
                lbl_1_bss_1220[0] = 0;
                lbl_1_bss_11F8[9] = 600.0f;
                PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &dir);
                dir.y = 0.0f;
                PSVECNormalize(&dir, &dir);
                PSVECScale(&dir, &dir, 100.0f);
                fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
                pos.x += -50.0f;
                pos.y += lbl_1_bss_11F8[9];
                PSVECAdd(&dir, &pos, &pos);
                lbl_1_bss_11F0 = (type == 0) ? 0x13 : (type == 1) ? 0x14 : 0x15;
                lbl_1_bss_11F4 = fn_1_3ED3C(lbl_1_bss_11F0, pos);
                fn_1_3F594(lbl_1_bss_11F0, 0, 4.0f);
                lbl_1_bss_1298[0] = 1;
            } else {
                fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
                pos.x += -50.0f;
                lbl_1_bss_11EC = (type == 0) ? 0x16 : (type == 1) ? 0x17 : 0x18;
                fn_1_3ED3C(lbl_1_bss_11EC, pos);
                fn_1_3F594(lbl_1_bss_11EC, 0, 2.0f);
                lbl_1_bss_1298[0] = 2;
                fn_1_8D04(0x441, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            break;
        case 1:
            if (lbl_1_bss_1220[0] < 50) {
                lbl_1_bss_1220[0]++;
                lbl_1_bss_11F8[9] = 600.0f - 4.0f * (3.0f * lbl_1_bss_1220[0]);
            }
            PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &dir);
            dir.y = 0.0f;
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, 100.0f);
            fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
            pos.x += -50.0f;
            pos.y += lbl_1_bss_11F8[9];
            PSVECAdd(&dir, &pos, &pos);
            fn_1_3F3D8(lbl_1_bss_11F0, lbl_1_bss_11F4, pos);
            Hu3D3Dto2D(&pos, 1, &pos2d);
            if (lbl_1_bss_20[0] == 0 && pos2d.y >= 0.0f) {
                fn_1_8D04(0x3FE, lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_20[0] = 1;
            }
            if (lbl_1_bss_1220[0] == 50) {
                fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
                pos.x += -50.0f;
                lbl_1_bss_11EC = (type == 0) ? 0x16 : (type == 1) ? 0x17 : 0x18;
                fn_1_3ED3C(lbl_1_bss_11EC, pos);
                fn_1_3F594(lbl_1_bss_11EC, 0, 3.0f);
                lbl_1_bss_1220[0]++;
                fn_1_8D04(0x441, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            if (fn_1_3F714(lbl_1_bss_11F0, 0)) {
                fn_1_3F278(lbl_1_bss_11F0, lbl_1_bss_11F4);
                lbl_1_bss_1298[0]++;
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            if (fn_1_3F714(lbl_1_bss_11EC, 0)) {
                lbl_1_bss_1298[0] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 305 insns */
s32 fn_1_32D70(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    s32 mode;
    s32 i;
    HuVecF pos = { 288.0f, 240.0f, 1500.0f };

    switch (lbl_1_bss_1298[0]) {
        case 0:
            lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
            fn_1_4FBC8(work, 0x36);
            fn_1_36B10(0);
            mode = (player->unk3C != -1) ? frandmod(3) : frandmod(4);
            if (mode == 0) {
                player->unk50 |= 0x800;
            } else if (mode == 1) {
                player->unk50 |= 0x1000;
            } else if (mode == 2) {
                player->unk50 |= 0x2000;
            } else {
                player->unk50 |= 0x4000;
            }
            lbl_1_bss_1298[0]++;
            break;
        case 1:
            mode = (player->unk50 & 0x800) ? 0 : (player->unk50 & 0x1000) ? 2 : (player->unk50 & 0x2000) ? 3 : 1;
            if (fn_1_33234(mode)) {
                fn_1_36B10(1);
                if (mode == 0) {
                    fn_1_4FBC8(work, 0x37);
                } else if (mode == 2) {
                    fn_1_4FBC8(work, 0x39);
                } else if (mode == 3) {
                    fn_1_4FBC8(work, 0x3A);
                } else {
                    fn_1_4FBC8(work, 0x38);
                }
                lbl_1_bss_1298[0] = 10;
                fn_1_36B10(0);
                lbl_1_bss_1248[8] = 0.0f;
                lbl_1_bss_1248[9] = 0.0f;
            }
            break;
        case 2:
            if (player->unk50 & 0x800) {
                if (fn_1_337C8(work)) {
                    lbl_1_bss_1298[0]++;
                }
            } else if (player->unk50 & 0x1000) {
                if (fn_1_33C94(work)) {
                    lbl_1_bss_1298[0]++;
                }
            } else if (player->unk50 & 0x2000) {
                if (fn_1_34DA4(work)) {
                    player->unk50 &= ~0x2000;
                    lbl_1_bss_1298[0]++;
                }
            } else if (player->unk50 & 0x4000) {
                if (fn_1_34E24(work)) {
                    player->unk50 &= ~0x4000;
                    lbl_1_bss_1298[0]++;
                }
            }
            break;
        case 3:
            lbl_1_bss_1298[0] = 0;
            result = 1;
            work->unk188 = 200;
            for (i = 0; i < 4; i++) {
                work->player[i].unk50 |= 0x8000;
            }
            break;
        case 10:
            lbl_1_bss_1248[8] += 10.0f;
            pos.y -= lbl_1_bss_1248[8];
            fn_1_36A70(&pos);
            lbl_1_bss_1248[9] += 15.0f;
            Hu3DModelRotSet(fn_1_36A60(), 0.0f, lbl_1_bss_1248[9], 0.0f);
            if (lbl_1_bss_1248[8] >= 400.0f) {
                fn_1_36B78();
                lbl_1_bss_1298[0] = 2;
            }
            break;
    }
    return result;
}

/* 357 insns */
s32 fn_1_33234(s32 type)
{
    s32 result = 0;

    switch (lbl_1_bss_1298[1]) {
        case 0:
            lbl_1_bss_11E8 = espEntry(lbl_1_data_2B4[type + 0x15], 0, 0);
            espDrawNoSet(lbl_1_bss_11E8, 0);
            espPosSet(lbl_1_bss_11E8, 210.0f, 100.0f);
            lbl_1_bss_1248[0] = 5.0f;
            espScaleSet(lbl_1_bss_11E8, 1.0f + lbl_1_bss_1248[0], 1.0f + lbl_1_bss_1248[0]);
            lbl_1_bss_1248[1] = 0.0f;
            espTPLvlSet(lbl_1_bss_11E8, lbl_1_bss_1248[1]);
            lbl_1_bss_1298[1]++;
            break;
        case 1:
            lbl_1_bss_1248[0] -= 0.1f;
            if (lbl_1_bss_1248[0] < 0.0f) {
                lbl_1_bss_1248[0] = 0.0f;
            }
            if (lbl_1_bss_20[0] == 0 && 0.0f == lbl_1_bss_1248[0]) {
                HuAudFXPlay(0x42B);
                lbl_1_bss_20[0] = 1;
            }
            espScaleSet(lbl_1_bss_11E8, 1.0f + lbl_1_bss_1248[0], 1.0f + lbl_1_bss_1248[0]);
            lbl_1_bss_1248[1] += 0.015f;
            if (lbl_1_bss_1248[1] > 1.0f) {
                lbl_1_bss_1248[1] = 1.0f;
            }
            espTPLvlSet(lbl_1_bss_11E8, lbl_1_bss_1248[1]);
            if (0.0f == lbl_1_bss_1248[0] && 1.0f == lbl_1_bss_1248[1]) {
                lbl_1_bss_1270[0] = 30;
                lbl_1_bss_1298[1]++;
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            lbl_1_bss_1270[0]--;
            if (lbl_1_bss_1270[0] == 0) {
                lbl_1_bss_1248[0] = 1.0f;
                lbl_1_bss_1248[1] = 0.0f;
                lbl_1_bss_1248[2] = 1.0f;
                lbl_1_bss_1298[1]++;
            }
            break;
        case 3:
            lbl_1_bss_1248[0] -= 0.02;
            if (lbl_1_bss_1248[0] < 0.0f) {
                lbl_1_bss_1248[0] = 0.0f;
            }
            espScaleSet(lbl_1_bss_11E8, lbl_1_bss_1248[0], lbl_1_bss_1248[0]);
            lbl_1_bss_1248[1] += 10.0f;
            if (lbl_1_bss_1248[1] > 350.0f) {
                lbl_1_bss_1248[1] = 0.0f;
            }
            espZRotSet(lbl_1_bss_11E8, lbl_1_bss_1248[1]);
            lbl_1_bss_1248[2] -= 0.02;
            if (lbl_1_bss_1248[2] < 0.0f) {
                lbl_1_bss_1248[2] = 0.0f;
                espKill(lbl_1_bss_11E8);
                lbl_1_bss_1298[1] = 0;
                result = 1;
            }
            if (result == 0) {
                espTPLvlSet(lbl_1_bss_11E8, lbl_1_bss_1248[2]);
            }
            break;
    }
    return result;
}

/* 307 insns */
s32 fn_1_337C8(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    HuVecF pos;
    HuVecF dir;
    s16 no;

    fn_1_9DA8(&pos, work);
    switch (lbl_1_bss_1298[1]) {
        case 0:
            lbl_1_bss_11E2 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[0x39], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(lbl_1_bss_11E2, 1);
            Hu3DModelPosSet(lbl_1_bss_11E2, -50.0f + pos.x, 300.0f + pos.y, pos.z);
            Hu3DModelRotSet(lbl_1_bss_11E2, 0.0f, 45.0f, 0.0f);
            Hu3DModelScaleSet(lbl_1_bss_11E2, 0.4f, 0.4f, 0.4f);
            Hu3DModelAttrSet(lbl_1_bss_11E2, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(lbl_1_bss_11E2, 0.0f);
            lbl_1_bss_1270[0] = 0;
            pos.x += -50.0f;
            pos.y += 300.0f;
            {
                HuVecF scale = { 1.2f, 1.2f, 1.2f };
                PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &dir);
                PSVECNormalize(&dir, &dir);
                PSVECScale(&dir, &dir, 100.0f);
                PSVECAdd(&dir, &pos, &pos);
                no = fn_1_3ED3C(1, pos);
                fn_1_3F6B0(1, no, scale);
            }
            lbl_1_bss_1298[1]++;
            break;
        case 1:
            lbl_1_bss_1270[0]++;
            if (lbl_1_bss_1270[0] == 12) {
                Hu3DModelAttrReset(lbl_1_bss_11E2, HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_1270[0] == 60) {
                lbl_1_bss_1270[0] = 0;
                lbl_1_bss_1248[0] = 0.4f;
                lbl_1_bss_1298[1]++;
                fn_1_8D04(0x31A, lbl_1_bss_11E2, 1);
            }
            break;
        case 2:
            lbl_1_bss_1270[0] += 10;
            lbl_1_bss_1248[0] -= 0.02f;
            if (lbl_1_bss_1248[0] < 0.0f) {
                lbl_1_bss_1248[0] = 0.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_11E2, -50.0f + pos.x, (300.0f + pos.y) - lbl_1_bss_1270[0], pos.z);
            Hu3DModelScaleSet(lbl_1_bss_11E2, lbl_1_bss_1248[0], lbl_1_bss_1248[0], lbl_1_bss_1248[0]);
            if (lbl_1_bss_1270[0] == 300) {
                Hu3DModelKill(lbl_1_bss_11E2);
                lbl_1_bss_1298[1] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 584 insns */
s32 fn_1_33C94(CardGameWork *work)
{
    s32 result = 0;
    s32 i;
    s32 x;
    s32 y;
    s32 a3;
    s32 a4;
    HuVecF pos;

    switch (lbl_1_bss_1298[1]) {
        case 0:
            fn_1_351C4(work->unk174[work->unk170]);
            if (fn_1_393C4(work)) {
                work->unk1BC = work->unk184;
                work->unk184 = 0;
                lbl_1_bss_C48[0] = 0;
                lbl_1_bss_C48[1] = 0;
                lbl_1_bss_1298[1]++;
            }
            break;
        case 1:
            lbl_1_bss_11E6 = espEntry(lbl_1_data_2B4[0x19], 0, 0);
            espDrawNoSet(lbl_1_bss_11E6, 0);
            espPriSet(lbl_1_bss_11E6, 0xF0);
            lbl_1_bss_1270[0] = 200;
            espPosSet(lbl_1_bss_11E6, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            lbl_1_bss_11E4 = espEntry(lbl_1_data_2B4[0x1A], 0, 0);
            espDrawNoSet(lbl_1_bss_11E4, 0);
            espPriSet(lbl_1_bss_11E4, 0xE0);
            espBankSet(lbl_1_bss_11E4, work->unk1BC - 1);
            lbl_1_bss_11E0 = espEntry(lbl_1_data_2B4[0x23], 0, 0);
            espDrawNoSet(lbl_1_bss_11E0, 0);
            espPriSet(lbl_1_bss_11E0, 0xF0);
            espPosSet(lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            espPosSet(lbl_1_bss_11E4, 102.0f, 79.0f);
            lbl_1_bss_1248[0] = 0.0f;
            espScaleSet(lbl_1_bss_11E4, lbl_1_bss_1248[0], 1.0f);
            for (i = 0; i < 4; i++) {
                if (i != work->unk174[work->unk170]) {
                    work->player[i].unk58 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[0x76], HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelCameraSet(work->player[i].unk58, 1);
                    Hu3DModelLayerSet(work->player[i].unk58, 2);
                    x = work->player[i].unk10;
                    y = work->player[i].unk14;
                    a3 = work->player[i].unk20;
                    a4 = work->player[i].unk24;
                    if (work->player[i].unk0 == 1) {
                        x--;
                    } else if (work->player[i].unk0 == 2) {
                        x++;
                    } else if (work->player[i].unk0 == 3) {
                        y--;
                    } else if (work->player[i].unk0 == 4) {
                        y++;
                    }
                    fn_1_9C74(&pos, x, y, a3, a4);
                    Hu3DModelPosSet(work->player[i].unk58, -50.0f + pos.x, pos.y, pos.z);
                    Hu3DModelScaleSet(work->player[i].unk58, 1.0f, 0.0f, 1.0f);
                }
            }
            lbl_1_bss_5E = 0;
            lbl_1_bss_1248[1] = 0.0f;
            lbl_1_bss_1298[1]++;
            HuAudFXPlay(0x432);
            break;
        case 2:
            lbl_1_bss_1270[0] -= 5;
            if (lbl_1_bss_1270[0] < 0) {
                lbl_1_bss_1270[0] = 0;
            }
            espPosSet((work->unk1BC != 1) ? lbl_1_bss_11E6 : lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            lbl_1_bss_1248[1] += 0.06666667f;
            if (lbl_1_bss_1248[1] > 1.0f) {
                lbl_1_bss_1248[1] = 1.0f;
            }
            for (i = 0; i < 4; i++) {
                if (i != work->unk174[work->unk170] && !(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(work->player[i].unk58, 1.0f, lbl_1_bss_1248[1], 1.0f);
                }
            }
            if (lbl_1_bss_1270[0] == 0) {
                if (0.0f == lbl_1_bss_1248[0]) {
                    HuAudFXPlay(0x433);
                }
                lbl_1_bss_1248[0] += 0.05f;
                if (lbl_1_bss_1248[0] > 1.0f) {
                    lbl_1_bss_1248[0] = 1.0f;
                    lbl_1_bss_1270[0] = 60;
                    lbl_1_bss_1298[1]++;
                }
                espScaleSet(lbl_1_bss_11E4, lbl_1_bss_1248[0], 1.0f);
            }
            lbl_1_bss_5E = (lbl_1_bss_5E <= 140) ? lbl_1_bss_5E + 10 : 150;
            fn_1_305B4(work, lbl_1_bss_5E);
            break;
        case 3:
            lbl_1_bss_1270[0]--;
            if (lbl_1_bss_1270[0] == 0) {
                lbl_1_bss_1270[0] = 0;
                lbl_1_bss_1298[1]++;
            }
            break;
        case 4:
            lbl_1_bss_1270[0] += 5;
            if (lbl_1_bss_1270[0] > 200) {
                lbl_1_bss_1270[0] = 200;
                lbl_1_bss_1298[1] = 0;
                result = 1;
            }
            espPosSet((work->unk1BC != 1) ? lbl_1_bss_11E6 : lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            espPosSet(lbl_1_bss_11E4, 102.0f, 79.0f - lbl_1_bss_1270[0]);
            break;
    }
    return result;
}

/* 453 insns */
s32 fn_1_345B4(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    s32 i;

    switch (lbl_1_bss_1298[1]) {
        case 0:
            work->unk1BC--;
            if (work->unk1BC > 0) {
                lbl_1_bss_1270[0] = 200;
                espPosSet((work->unk1BC != 1) ? lbl_1_bss_11E6 : lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
                espPosSet(lbl_1_bss_11E4, 102.0f, 79.0f);
                espBankSet(lbl_1_bss_11E4, work->unk1BC - 1);
                lbl_1_bss_1248[0] = 0.0f;
                espScaleSet(lbl_1_bss_11E4, lbl_1_bss_1248[0], 1.0f);
                lbl_1_bss_1298[1]++;
            } else {
                lbl_1_bss_5E = 150;
                lbl_1_bss_1248[0] = 1.0f;
                lbl_1_bss_1298[1] = 4;
                HuAudFXPlay(0x434);
            }
            break;
        case 1:
            lbl_1_bss_1270[0] -= 5;
            if (lbl_1_bss_1270[0] < 0) {
                lbl_1_bss_1270[0] = 0;
            }
            espPosSet((work->unk1BC != 1) ? lbl_1_bss_11E6 : lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            if (lbl_1_bss_1270[0] == 0) {
                if (0.0f == lbl_1_bss_1248[0]) {
                    HuAudFXPlay(0x433);
                }
                lbl_1_bss_1248[0] += 0.05f;
                if (lbl_1_bss_1248[0] > 1.0f) {
                    lbl_1_bss_1248[0] = 1.0f;
                    lbl_1_bss_1270[0] = 60;
                    lbl_1_bss_1298[1]++;
                }
                espScaleSet(lbl_1_bss_11E4, lbl_1_bss_1248[0], 1.0f);
            }
            break;
        case 2:
            lbl_1_bss_1270[0]--;
            if (lbl_1_bss_1270[0] == 0) {
                lbl_1_bss_1270[0] = 0;
                lbl_1_bss_1298[1]++;
            }
            break;
        case 3:
            lbl_1_bss_1270[0] += 5;
            if (lbl_1_bss_1270[0] > 200) {
                lbl_1_bss_1270[0] = 200;
                lbl_1_bss_1298[1] = 0;
                result = -1;
            }
            espPosSet((work->unk1BC != 1) ? lbl_1_bss_11E6 : lbl_1_bss_11E0, 210.0f, 79.0f - lbl_1_bss_1270[0]);
            espPosSet(lbl_1_bss_11E4, 102.0f, 79.0f - lbl_1_bss_1270[0]);
            break;
        case 4:
            lbl_1_bss_5E = (lbl_1_bss_5E >= 10) ? lbl_1_bss_5E - 10 : 0;
            fn_1_305B4(work, lbl_1_bss_5E);
            lbl_1_bss_1248[0] -= 0.06666667f;
            if (lbl_1_bss_1248[0] < 0.0f) {
                lbl_1_bss_1248[0] = 0.0f;
            }
            for (i = 0; i < 4; i++) {
                if (i != work->unk174[work->unk170] && !(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(work->player[i].unk58, 1.0f, lbl_1_bss_1248[0], 1.0f);
                }
            }
            if (lbl_1_bss_5E == 0) {
                player->unk50 &= ~0x1000;
                espKill(lbl_1_bss_11E6);
                espKill(lbl_1_bss_11E4);
                espKill(lbl_1_bss_11E0);
                for (i = 0; i < 4; i++) {
                    if (i != work->unk174[work->unk170]) {
                        Hu3DModelKill(work->player[i].unk58);
                        work->player[i].unk58 = -1;
                    }
                }
                lbl_1_bss_1298[1] = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 55 insns */
void fn_1_34CC8(CardGameWork *work)
{
    s32 i;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    if (player->unk50 & 0x1000) {
        espKill(lbl_1_bss_11E6);
        espKill(lbl_1_bss_11E4);
        espKill(lbl_1_bss_11E0);
        for (i = 0; i < 4; i++) {
            if (i != work->unk174[work->unk170]) {
                Hu3DModelKill(work->player[i].unk58);
                work->player[i].unk58 = -1;
            }
        }
    }
}

/* 32 insns */
s32 fn_1_34DA4(CardGameWork *work)
{
    s32 result = 0;

    fn_1_351C4(work->unk174[work->unk170]);
    if (fn_1_393C4(work)) {
        lbl_1_bss_C48[0] = 0;
        lbl_1_bss_C48[1] = 0;
        result = 1;
    }
    return result;
}

/* 232 insns */
s32 fn_1_34E24(CardGameWork *work)
{
    s32 result = 0;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    s32 num;
    s32 rnd;
    s16 no;
    HuVecF pos2d;
    HuVecF pos;
    HuVecF scale = { 0.35f, 0.35f, 0.35f };

    num = 0;
    if (player->unk34 != -1) {
        num++;
        if (player->unk38 != -1) {
            num++;
            if (player->unk3C != -1) {
                num++;
            }
        }
    }
    Hu3DCamera[1] = Hu3DCamera[0];
    Hu3DZClearLayerSet(15);
    switch (lbl_1_bss_1298[1]) {
        case 0:
            if (num == 0) {
                pos2d.x = ((float (*)[2])lbl_1_data_548)[work->unk170][0];
                pos2d.y = ((float (*)[2])lbl_1_data_548)[work->unk170][1];
            } else if (num == 1) {
                pos2d.x = ((float (*)[2])lbl_1_data_568)[work->unk170][0];
                pos2d.y = ((float (*)[2])lbl_1_data_568)[work->unk170][1];
            } else {
                pos2d.x = ((float (*)[2])lbl_1_data_588)[work->unk170][0];
                pos2d.y = ((float (*)[2])lbl_1_data_588)[work->unk170][1];
            }
            pos2d.z = 1000.0f;
            Hu3D2Dto3D(&pos2d, 1, &pos);
            pos.x -= 3.0f;
            no = fn_1_3ED3C(1, pos);
            fn_1_3F6B0(1, no, scale);
            fn_1_3F658(1, no, 7);
            fn_1_3F380(1, no, 2);
            lbl_1_bss_1270[0] = 0;
            lbl_1_bss_1298[1]++;
            break;
        case 1:
            lbl_1_bss_1270[0]++;
            if (lbl_1_bss_1270[0] == 12) {
                rnd = frandmod(100);
                (&player->unk34)[num] = (rnd < 50) ? 0 : (rnd < 80) ? 1 : 2;
                fn_1_2FFAC(work);
                lbl_1_bss_1270[0] = 0;
                lbl_1_bss_1298[1]++;
            }
            break;
        case 2:
            lbl_1_bss_1270[0]++;
            if (lbl_1_bss_1270[0] == 40) {
                lbl_1_bss_1298[1] = 0;
                if (num == 3) {
                    result = 1;
                }
            }
            break;
    }
    Hu3DLayerHookSet(15, NULL);
    return result;
}

/* 67 insns */
void fn_1_351C4(s32 playerNo)
{
    if (GwPlayerConf[playerNo].type != 0) {
        HuPadBtnDown[playerNo] = 0;
        HuPadDStkRep[playerNo] = 0;
        lbl_1_bss_C48[0]++;
        lbl_1_bss_C48[0] %= 350;
        if (lbl_1_bss_C48[0] > frandmod(300) + 31) {
            HuPadBtnDown[playerNo] = PAD_BUTTON_A;
            lbl_1_bss_C48[0] = 0;
        }
    }
}

/* 394 insns */
void fn_1_352D0(CardGameWork *work)
{
    s32 x;
    s32 y;
    s32 flag;
    s32 n;
    s32 tbl[30];
    s32 cnt[3]; /* [0] candidates counted, [1] the cnt[1], [2] candidates walked */

    n = 0;
    flag = 0;
    if (work->unk1D0 <= 2) {
        cnt[0] = 0;
        for (x = 0; x < work->unk194; x++) {
            for (y = 0; y < work->unk194; y++) {
                if (!(lbl_1_bss_8C4[x][y] & 0x10) && !(lbl_1_bss_8C4[x][y] & 0xF00)
                    && (work->player[0].unk8 != x || work->player[0].unkC != y)
                    && (work->player[1].unk8 != x || work->player[1].unkC != y)
                    && (work->player[2].unk8 != x || work->player[2].unkC != y)
                    && (work->player[3].unk8 != x || work->player[3].unkC != y)) {
                    flag = 0;
                    if (x == 0) {
                        if (lbl_1_bss_8C4[x + 1][y] & 0x400) {
                            flag = 1;
                        }
                    } else if (lbl_1_bss_8C4[x - 1][y] & 0x400) {
                        flag = 1;
                    }
                    if (x == work->unk194 - 1) {
                        if (lbl_1_bss_8C4[x - 1][y] & 0x400) {
                            flag = 1;
                        }
                    } else if (lbl_1_bss_8C4[x + 1][y] & 0x400) {
                        flag = 1;
                    }
                    if (y == 0) {
                        if (lbl_1_bss_8C4[x][y + 1] & 0x400) {
                            flag = 1;
                        }
                    } else if (lbl_1_bss_8C4[x][y - 1] & 0x400) {
                        flag = 1;
                    }
                    if (y == work->unk194 - 1) {
                        if (lbl_1_bss_8C4[x][y - 1] & 0x400) {
                            flag = 1;
                        }
                    } else if (lbl_1_bss_8C4[x][y + 1] & 0x400) {
                        flag = 1;
                    }
                    if (flag && n < 30) {
                        tbl[n] = cnt[0];
                        n++;
                    }
                    cnt[0]++;
                }
            }
        }
        if (cnt[0] != 0) {
            cnt[1] = frandmod(cnt[0]);
            if (n > 0 && frandmod(2) != 0) {
                cnt[1] = tbl[frandmod(n)];
            }
            cnt[2] = 0;
            for (x = 0; x < work->unk194; x++) {
                for (y = 0; y < work->unk194; y++) {
                    if (!(lbl_1_bss_8C4[x][y] & 0x10) && !(lbl_1_bss_8C4[x][y] & 0xF00)
                        && (work->player[0].unk8 != x || work->player[0].unkC != y)
                        && (work->player[1].unk8 != x || work->player[1].unkC != y)
                        && (work->player[2].unk8 != x || work->player[2].unkC != y)
                        && (work->player[3].unk8 != x || work->player[3].unkC != y)) {
                        if (cnt[1] == cnt[2]) {
                            HuVecF pos;

                            lbl_1_bss_8C4[x][y] |= 0x800;
                            Hu3DModelShadowMapObjReset(lbl_1_bss_478[x][y]);
                            Hu3DModelKill(lbl_1_bss_478[x][y]);
                            lbl_1_bss_478[x][y] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[0x1F], HU_MEMNUM_OVL, HEAP_MODEL));
                            Hu3DModelCameraSet(lbl_1_bss_478[x][y], 1);
                            fn_1_9C74(&pos, x, y, 1, 1);
                            Hu3DModelPosSet(lbl_1_bss_478[x][y], -50.0f + pos.x, pos.y, pos.z);
                            Hu3DModelRotSet(lbl_1_bss_478[x][y], 0.0f, 0.0f, 180.0f);
                            Hu3DModelLayerSet(lbl_1_bss_478[x][y], 2);
                            Hu3DModelShadowMapSet(lbl_1_bss_478[x][y]);
                            work->unk1D4 = 1;
                            x = y = work->unk194;
                        } else {
                            cnt[2]++;
                        }
                    }
                }
            }
        } else {
            work->unk1D4 = -1;
        }
    }
}

/* 933 insns */
void fn_1_358F8(CardGameWork *work)
{
    float x;
    float y;
    HuVecF pos = { 485.0f, 405.0f, 1000.0f };

    switch (lbl_1_bss_11DC) {
        case 0:
            if (work->unk188 == 0xCA || work->unk188 == 0xCC || work->unk188 == 0xCD) {
                lbl_1_bss_11D8 = work->unk188;
                lbl_1_bss_11DC++;
            }
            break;
        case 1:
            lbl_1_bss_11C0[0] = espEntry(lbl_1_data_2B4[0x22], 0, 0);
            espDrawNoSet(lbl_1_bss_11C0[0], 0x40);
            lbl_1_bss_11CC[0] = 128.0f;
            x = 480.0f;
            y = 360.4f;
            espPosSet(lbl_1_bss_11C0[0], x, y + lbl_1_bss_11CC[0]);
            lbl_1_bss_11CC[1] = 0.0f;
            espTPLvlSet(lbl_1_bss_11C0[0], lbl_1_bss_11CC[1]);
            espPriSet(lbl_1_bss_11C0[0], 0x1F0);
            lbl_1_bss_11C0[1] = espEntry(lbl_1_data_2B4[7], 0, 0);
            espDrawNoSet(lbl_1_bss_11C0[1], 0x40);
            espPriSet(lbl_1_bss_11C0[1], 0x1E0);
            if (work->unk194 == 10) {
                espBankSet(lbl_1_bss_11C0[1], work->unk1D0 / 10 + 3);
                x = 484.0f;
                y = 336.0f;
                if (work->unk1D0 / 10 == 0) {
                    espDispOff(lbl_1_bss_11C0[1]);
                }
            } else {
                espBankSet(lbl_1_bss_11C0[1], work->unk1D0 + 3);
                x = 492.0f;
                y = 336.0f;
            }
            espPosSet(lbl_1_bss_11C0[1], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[1], lbl_1_bss_11CC[1]);
            lbl_1_bss_11C0[2] = espEntry(lbl_1_data_2B4[7], 0, 0);
            espDrawNoSet(lbl_1_bss_11C0[2], 0x40);
            espPriSet(lbl_1_bss_11C0[2], 0x1E0);
            if (work->unk194 == 10) {
                espBankSet(lbl_1_bss_11C0[2], work->unk1D0 % 10 + 3);
                if (work->unk1D0 / 10 == 0) {
                    x = 492.0f;
                    y = 336.0f;
                } else {
                    x = 500.0f;
                    y = 336.0f;
                }
            } else {
                espBankSet(lbl_1_bss_11C0[2], work->unk194 + 3);
                x = 516.0f;
                y = 362.0f;
            }
            espPosSet(lbl_1_bss_11C0[2], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[2], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                lbl_1_bss_11C0[3] = espEntry(lbl_1_data_2B4[7], 0, 0);
                espDrawNoSet(lbl_1_bss_11C0[3], 0x40);
                espBankSet(lbl_1_bss_11C0[3], 4);
                espPriSet(lbl_1_bss_11C0[3], 0x1E0);
                x = 512.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[3], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[3], lbl_1_bss_11CC[1]);
                lbl_1_bss_11C0[4] = espEntry(lbl_1_data_2B4[7], 0, 0);
                espDrawNoSet(lbl_1_bss_11C0[4], 0x40);
                espBankSet(lbl_1_bss_11C0[4], 3);
                espPriSet(lbl_1_bss_11C0[4], 0x1E0);
                x = 528.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[4], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[4], lbl_1_bss_11CC[1]);
            }
            fn_1_36828();
            lbl_1_bss_11CC[2] = 128.0f;
            pos.y += lbl_1_bss_11CC[2];
            fn_1_36A70(&pos);
            Hu3DModelScaleSet(fn_1_36A60(), 0.45f, 0.45f, 0.45f);
            Hu3DModelRotSet(fn_1_36A60(), 0.0f, -10.0f, 0.0f);
            lbl_1_bss_11DC++;
            break;
        case 2:
            lbl_1_bss_11CC[0] -= 8.0f;
            if (lbl_1_bss_11CC[0] < 0.0f) {
                lbl_1_bss_11CC[0] = 0.0f;
            }
            x = 480.0f;
            y = 360.4f;
            espPosSet(lbl_1_bss_11C0[0], x, y + lbl_1_bss_11CC[0]);
            lbl_1_bss_11CC[1] += 0.0625f;
            if (lbl_1_bss_11CC[1] > 1.0f) {
                lbl_1_bss_11CC[1] = 1.0f;
            }
            espTPLvlSet(lbl_1_bss_11C0[0], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                x = 484.0f;
                y = 336.0f;
            } else {
                x = 492.0f;
                y = 336.0f;
            }
            espPosSet(lbl_1_bss_11C0[1], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[1], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                if (work->unk1D0 / 10 == 0) {
                    x = 492.0f;
                    y = 336.0f;
                } else {
                    x = 500.0f;
                    y = 336.0f;
                }
            } else {
                x = 516.0f;
                y = 362.0f;
            }
            espPosSet(lbl_1_bss_11C0[2], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[2], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                x = 512.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[3], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[3], lbl_1_bss_11CC[1]);
                x = 528.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[4], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[4], lbl_1_bss_11CC[1]);
            }
            lbl_1_bss_11CC[2] -= 8.0f;
            pos.y += lbl_1_bss_11CC[2];
            fn_1_36A70(&pos);
            if (0.0f == lbl_1_bss_11CC[0] && 1.0f == lbl_1_bss_11CC[1]) {
                lbl_1_bss_11DC++;
            }
            break;
        case 3:
            if (work->unk188 != lbl_1_bss_11D8) {
                lbl_1_bss_11DC++;
            }
            break;
        case 4:
            lbl_1_bss_11CC[0] += 8.0f;
            if (lbl_1_bss_11CC[0] > 128.0f) {
                lbl_1_bss_11CC[0] = 128.0f;
            }
            espPosSet(lbl_1_bss_11C0[0], 480.0f, 360.0f + lbl_1_bss_11CC[0]);
            lbl_1_bss_11CC[1] -= 0.0625f;
            if (lbl_1_bss_11CC[1] < 0.0f) {
                lbl_1_bss_11CC[1] = 0.0f;
            }
            espTPLvlSet(lbl_1_bss_11C0[0], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                x = 484.0f;
                y = 336.0f;
            } else {
                x = 492.0f;
                y = 336.0f;
            }
            espPosSet(lbl_1_bss_11C0[1], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[1], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                if (work->unk1D0 / 10 == 0) {
                    x = 492.0f;
                    y = 336.0f;
                } else {
                    x = 500.0f;
                    y = 336.0f;
                }
            } else {
                x = 516.0f;
                y = 362.0f;
            }
            espPosSet(lbl_1_bss_11C0[2], x, y + lbl_1_bss_11CC[0]);
            espTPLvlSet(lbl_1_bss_11C0[2], lbl_1_bss_11CC[1]);
            if (work->unk194 == 10) {
                x = 512.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[3], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[3], lbl_1_bss_11CC[1]);
                x = 528.0f;
                y = 362.0f;
                espPosSet(lbl_1_bss_11C0[4], x, y + lbl_1_bss_11CC[0]);
                espTPLvlSet(lbl_1_bss_11C0[4], lbl_1_bss_11CC[1]);
            }
            lbl_1_bss_11CC[2] += 8.0f;
            pos.y += lbl_1_bss_11CC[2];
            fn_1_36A70(&pos);
            if (128.0f == lbl_1_bss_11CC[0] && 0.0f == lbl_1_bss_11CC[1]) {
                espKill(lbl_1_bss_11C0[0]);
                espKill(lbl_1_bss_11C0[1]);
                espKill(lbl_1_bss_11C0[2]);
                if (work->unk194 == 10) {
                    espKill(lbl_1_bss_11C0[3]);
                    espKill(lbl_1_bss_11C0[4]);
                }
                fn_1_36B78();
                lbl_1_bss_11DC = 0;
            }
            break;
    }
}

/* 39 insns */
void fn_1_3678C(CardGameWork *work)
{
    if (lbl_1_bss_11DC == 3) {
        espKill(lbl_1_bss_11C0[0]);
        espKill(lbl_1_bss_11C0[1]);
        espKill(lbl_1_bss_11C0[2]);
        if (work->unk194 == 10) {
            espKill(lbl_1_bss_11C0[3]);
            espKill(lbl_1_bss_11C0[4]);
        }
        fn_1_36B78();
    }
}

/* 142 insns */
void fn_1_36828(void)
{
    HuVecF pos = { 0.0f, 0.0f, 0.0f };
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF target = { 0.0f, 0.0f, -100.0f };

    Hu3DZClearLayerSet(15);
    lbl_1_bss_11BE = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[0x77], HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_11BA[0] = Hu3DJointMotion(lbl_1_bss_11BE, HuDataSelHeapReadNum(lbl_1_data_B0[0x78], HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_11BA[1] = Hu3DJointMotion(lbl_1_bss_11BE, HuDataSelHeapReadNum(lbl_1_data_B0[0x79], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_11BE, lbl_1_bss_11BA[0]);
    Hu3DModelCameraSet(lbl_1_bss_11BE, 2);
    Hu3DCameraPosSetV(2, &pos, &up, &target);
    Hu3DModelLayerSet(lbl_1_bss_11BE, 7);
    Hu3DModelAttrSet(lbl_1_bss_11BE, HU3D_MOTATTR_LOOP);
    lbl_1_bss_11B8 = Hu3DLLightCreate(lbl_1_bss_11BE, 0.0f, 0.0f, 100.0f, 0.0f, 0.0f, -1.0f, 0x30, 0x30, 0x30);
    Hu3DLLightStaticSet(lbl_1_bss_11BE, lbl_1_bss_11B8, TRUE);
    Hu3DLLightInfinitytSet(lbl_1_bss_11BE, lbl_1_bss_11B8);
}

/* 4 insns */
s16 fn_1_36A60(void)
{
    return lbl_1_bss_11BE;
}

/* 40 insns */
void fn_1_36A70(HuVecF *pos)
{
    HuVecF pos3d;

    Hu3D2Dto3D(pos, 2, &pos3d);
    Hu3DModelPosSetV(lbl_1_bss_11BE, &pos3d);
    Hu3DLLightPosSet(lbl_1_bss_11BE, lbl_1_bss_11B8, pos3d.x, pos3d.y, 100.0f + pos3d.z, 0.0f, 0.0f, -1.0f);
}

/* 26 insns */
void fn_1_36B10(s32 a0)
{
    Hu3DMotionShiftSet(lbl_1_bss_11BE, lbl_1_bss_11BA[a0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
}

/* 34 insns */
void fn_1_36B78(void)
{
    Hu3DLLightKill(lbl_1_bss_11BE, lbl_1_bss_11B8);
    Hu3DMotionSet(lbl_1_bss_11BE, -1);
    Hu3DMotionKill(lbl_1_bss_11BA[0]);
    Hu3DMotionKill(lbl_1_bss_11BA[1]);
    Hu3DModelKill(lbl_1_bss_11BE);
    Hu3DLayerHookSet(15, NULL);
}

