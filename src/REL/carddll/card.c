/*
 * carddll card.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/card.s.
 */

#include "REL/carddll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x168 lbl_1_rodata_168 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x174 lbl_1_rodata_174 (0x30): 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1A4 = 1.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 0.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 150.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = 300.0f; /* 0x1B0 */
static const float lbl_1_rodata_1B4 = 0.5f; /* 0x1B4 */
static const float lbl_1_rodata_1B8 = 10.0f; /* 0x1B8 */
static const float lbl_1_rodata_1BC = -50.0f; /* 0x1BC */
static const float lbl_1_rodata_1C0 = 180.0f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = 90.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = -90.0f; /* 0x1C8 */
/* 0x1D0 lbl_1_rodata_1D0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_1D8 = 98.4375f; /* 0x1D8 */
/* 0x1DC lbl_1_rodata_1DC (0x3C): 0x53, 0x33, 0x5F, 0x63, 0x5F, 0x75, 0x72, 0x61 0x5F, 0x69, 0x74, 0x65, 0x6D, 0x00, 0x00, 0x53 0x33, 0x5F, 0x63, 0x5F, 0x75, 0x72, 0x61, 0x5F 0x65, 0x76, 0x65, 0x6E, 0x74, 0x00, 0x63, 0x5F 0x75, 0x72, 0x61, 0x5F, 0x73, 0x74, 0x61, 0x72 0x00, 0x00, 0x00, 0x00, 0x00, 0x53, 0x33, 0x5F 0x63, 0x5F, 0x75, 0x72, 0x61, 0x5F, 0x72, 0x00 0x00, 0x00, 0x00, 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_218 = 5.0f; /* 0x218 */
static const float lbl_1_rodata_21C = 100.0f; /* 0x21C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xBE4 gap_05_00000BE4_bss (0x4): alignment gap */
/* 0xA54 */ s32 lbl_1_bss_A54[10][10];
/* 0x8C4 */ s32 lbl_1_bss_8C4[10][10];
/* 0x540 */ s8 lbl_1_bss_540[10][10][3][3];
/* 0x478 */ s16 lbl_1_bss_478[10][10];
/* 0x470 */ s16 lbl_1_bss_470[4];
/* 0x468 */ s16 lbl_1_bss_468[4];
/* 0x430 */ s16 lbl_1_bss_430[4][7];
/* 0x3F4 */ s16 lbl_1_bss_3F4[30];
/* 0x3F0 */ s32 lbl_1_bss_3F0;
/* 0x3E4 */ float lbl_1_bss_3E4[3];
/* 0x3D8 */ s32 lbl_1_bss_3D8[3];
/* 0x3C8 */ s32 lbl_1_bss_3C8[4];
/* 0x3BC */ s32 lbl_1_bss_3BC[3];
/* 0x3AC */ s32 lbl_1_bss_3AC[4];
/* 0x39C */ s32 lbl_1_bss_39C[4];
/* 0x398 */ s32 lbl_1_bss_398;
/* 0x394 */ s32 lbl_1_bss_394;
/* 0x330 */ s16 lbl_1_bss_330[50];
/* 0x32C */ s32 lbl_1_bss_32C;
/* 0x328 */ float lbl_1_bss_328;
/* 0x324 */ float lbl_1_bss_324;
/* 0x320 */ s32 lbl_1_bss_320;

/* --- functions (reference order), .data placed before its first user --- */
/* 875 insns */
void fn_1_8EC8(CardGameWork *work)
{
    s32 size = work->unk194;
    CardPlayerWork *player = work->player;
    s32 i;
    s32 j;
    float rot;
    HuVecF pos;
    HuVecF base = { 0.0f, 0.0f, 0.0f };
    HuVecF unused[4] = { 0 };

    for (i = 0; i < 4; i++) {
        lbl_1_bss_470[i] = Hu3DModelCreateData(lbl_1_data_B0[GwPlayerConf[i].charNo + 6]);
        lbl_1_bss_468[i] = Hu3DModelCreateData(player[i].unk28 + lbl_1_data_B0[GwPlayerConf[i].charNo * 3 + 0x24]);
        for (j = 0; j < 7; j++) {
            lbl_1_bss_430[i][j] = Hu3DJointMotionData(lbl_1_bss_468[i], lbl_1_data_298[j]);
        }
        Hu3DMotionSet(lbl_1_bss_468[i], lbl_1_bss_430[i][6]);
        Hu3DModelCameraSet(lbl_1_bss_470[i], HU3D_CAM0);
        Hu3DModelCameraSet(lbl_1_bss_468[i], HU3D_CAM0);
        Hu3DModelScaleSet(lbl_1_bss_470[i], 1.0f, 0.0f, 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_468[i], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(lbl_1_bss_470[i], 2);
        Hu3DModelLayerSet(lbl_1_bss_468[i], 2);
        Hu3DModelShadowSet(lbl_1_bss_468[i]);
        Hu3DModelShadowMapSet(lbl_1_bss_470[i]);
    }
    lbl_1_bss_3AC[0] = 0;
    lbl_1_bss_39C[0] = frandmod(size - 2) + 1;
    lbl_1_bss_3AC[1] = size - 1;
    lbl_1_bss_39C[1] = frandmod(size - 2) + 1;
    lbl_1_bss_3AC[2] = frandmod(size - 2) + 1;
    lbl_1_bss_39C[2] = 0;
    lbl_1_bss_3AC[3] = frandmod(size - 2) + 1;
    lbl_1_bss_39C[3] = size - 1;
    fn_1_A520(work);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            lbl_1_bss_478[i][j] = Hu3DModelCreateData(lbl_1_data_B0[lbl_1_bss_A54[i][j]]);
            Hu3DModelCameraSet(lbl_1_bss_478[i][j], HU3D_CAM0);
            pos.x = 150.0f + (300.0f * j + (base.x - 300.0f * size / 2.0f));
            pos.y = base.y - 10.0f;
            pos.z = 150.0f + (300.0f * i + (base.z - 300.0f * size / 2.0f));
            Hu3DModelPosSet(lbl_1_bss_478[i][j], -50.0f + pos.x, pos.y, pos.z);
            Hu3DModelRotSet(lbl_1_bss_478[i][j], 0.0f, 0.0f, 180.0f);
            Hu3DModelAttrSet(lbl_1_bss_478[i][j], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(lbl_1_bss_478[i][j], 2);
            Hu3DModelShadowMapSet(lbl_1_bss_478[i][j]);
            if ((lbl_1_bss_8C4[i][j] & 0xF00) != 0) {
                lbl_1_bss_3F4[lbl_1_bss_3F0] = Hu3DModelCreateData(lbl_1_data_B0[
                    (lbl_1_bss_8C4[i][j] & 0xF) == 15 ? 13
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 12 ? 14
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 3 ? 15
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 11 ? 16
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 13 ? 17
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 7 ? 18
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 14 ? 19
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 10 ? 20
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 9 ? 21
                    : (lbl_1_bss_8C4[i][j] & 0xF) == 5 ? 22
                    : 23]);
                Hu3DModelCameraSet(lbl_1_bss_3F4[lbl_1_bss_3F0], HU3D_CAM0);
                Hu3DModelPosSet(lbl_1_bss_3F4[lbl_1_bss_3F0], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelRotSet(lbl_1_bss_3F4[lbl_1_bss_3F0], 0.0f, 0.0f, 180.0f);
                Hu3DModelAttrSet(lbl_1_bss_3F4[lbl_1_bss_3F0], HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(lbl_1_bss_3F4[lbl_1_bss_3F0], 2);
                lbl_1_bss_3F0++;
            }
            if (i == 0 && j == 0) {
                lbl_1_bss_3E4[0] = pos.x;
                lbl_1_bss_3E4[1] = pos.y;
                lbl_1_bss_3E4[2] = pos.z;
            }
            if (i == 0 && j == lbl_1_bss_39C[0]) {
                pos.z -= 300.0f;
                rot = 0.0f;
                Hu3DModelPosSet(lbl_1_bss_470[0], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelPosSet(lbl_1_bss_468[0], -50.0f + pos.x, pos.y, pos.z);
                player[0].unk0 = 1;
                player[0].unk10 = i;
                player[0].unk14 = j;
                player[0].unk20 = 1;
                player[0].unk24 = 1;
                player[0].unk4 = 1;
                player[0].unk8 = i;
                player[0].unkC = j;
            }
            if (i == size - 1 && j == lbl_1_bss_39C[1]) {
                pos.z += 300.0f;
                rot = 180.0f;
                Hu3DModelPosSet(lbl_1_bss_470[1], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelPosSet(lbl_1_bss_468[1], -50.0f + pos.x, pos.y, pos.z);
                player[1].unk0 = 2;
                player[1].unk10 = i;
                player[1].unk14 = j;
                player[1].unk20 = 1;
                player[1].unk24 = 1;
                player[1].unk4 = 2;
                player[1].unk8 = i;
                player[1].unkC = j;
            }
            if (j == 0 && i == lbl_1_bss_3AC[2]) {
                pos.x -= 300.0f;
                rot = 90.0f;
                Hu3DModelPosSet(lbl_1_bss_470[2], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelPosSet(lbl_1_bss_468[2], -50.0f + pos.x, pos.y, pos.z);
                player[2].unk0 = 3;
                player[2].unk10 = i;
                player[2].unk14 = j;
                player[2].unk20 = 1;
                player[2].unk24 = 1;
                player[2].unk4 = 3;
                player[2].unk8 = i;
                player[2].unkC = j;
            }
            if (j == size - 1 && i == lbl_1_bss_3AC[3]) {
                pos.x += 300.0f;
                rot = -90.0f;
                Hu3DModelPosSet(lbl_1_bss_470[3], -50.0f + pos.x, pos.y, pos.z);
                Hu3DModelPosSet(lbl_1_bss_468[3], -50.0f + pos.x, pos.y, pos.z);
                player[3].unk0 = 4;
                player[3].unk10 = i;
                player[3].unk14 = j;
                player[3].unk20 = 1;
                player[3].unk24 = 1;
                player[3].unk4 = 4;
                player[3].unk8 = i;
                player[3].unkC = j;
            }
        }
    }
}

/* 77 insns */
void fn_1_9C74(HuVecF *out, s32 x, s32 y, s32 a3, s32 a4)
{
    out->x = lbl_1_bss_3E4[0] + 300.0f * y;
    out->y = lbl_1_bss_3E4[1];
    out->z = lbl_1_bss_3E4[2] + 300.0f * x;
    if (a4 == 0) {
        out->x -= 98.4375f;
    }
    else if (a4 == 2) {
        out->x += 98.4375f;
    }
    if (a3 == 0) {
        out->z -= 98.4375f;
    }
    else if (a3 == 2) {
        out->z += 98.4375f;
    }
}

/* 478 insns */
void fn_1_9DA8(HuVecF *out, CardGameWork *work)
{
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    if (player->unk0 != 0) {
        if (player->unk0 == 1) {
            fn_1_9C74(out, player->unk10 - 1, player->unk14, player->unk20, player->unk24);
            player->unk18 = 0.0f;
            player->unk1C = 0.0f;
        }
        else if (player->unk0 == 2) {
            fn_1_9C74(out, player->unk10 + 1, player->unk14, player->unk20, player->unk24);
            player->unk18 = 180.0f;
            player->unk1C = 180.0f;
        }
        else if (player->unk0 == 3) {
            fn_1_9C74(out, player->unk10, player->unk14 - 1, player->unk20, player->unk24);
            player->unk18 = 90.0f;
            player->unk1C = 90.0f;
        }
        else if (player->unk0 == 4) {
            fn_1_9C74(out, player->unk10, player->unk14 + 1, player->unk20, player->unk24);
            player->unk18 = -90.0f;
            player->unk1C = -90.0f;
        }
    }
    else {
        fn_1_9C74(out, player->unk10, player->unk14, player->unk20, player->unk24);
    }
}

/* 401 insns */
void fn_1_A520(CardGameWork *work)
{
    s32 size = work->unk194;
    s32 i;
    s32 j;

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            lbl_1_bss_8C4[i][j] = 0;
        }
    }
    fn_1_B104(size);
    for (i = 1; i < size - 1; i++) {
        for (j = 1; j < size - 1; j++) {
            fn_1_BB70(i, j, size);
        }
    }
    fn_1_C864(work);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            lbl_1_bss_A54[i][j] = (lbl_1_bss_8C4[i][j] & 0x100) ? ((lbl_1_bss_8C4[i][j] & 0x1000) ? 24 : (lbl_1_bss_8C4[i][j] & 0x2000) ? 25 : 26)
                : (lbl_1_bss_8C4[i][j] & 0x200) ? ((lbl_1_bss_8C4[i][j] & 0x1000) ? 27 : (lbl_1_bss_8C4[i][j] & 0x2000) ? 28 : (lbl_1_bss_8C4[i][j] & 0x4000) ? 29 : 30)
                : (lbl_1_bss_8C4[i][j] & 0x400) ? ((lbl_1_bss_8C4[i][j] & 0x1000) ? 33 : (lbl_1_bss_8C4[i][j] & 0x2000) ? 34 : 35)
                : (lbl_1_bss_8C4[i][j] & 0x800) ? 31
                : (lbl_1_bss_8C4[i][j] & 0xF) == 15 ? 13
                : (lbl_1_bss_8C4[i][j] & 0xF) == 12 ? 14
                : (lbl_1_bss_8C4[i][j] & 0xF) == 3 ? 15
                : (lbl_1_bss_8C4[i][j] & 0xF) == 11 ? 16
                : (lbl_1_bss_8C4[i][j] & 0xF) == 13 ? 17
                : (lbl_1_bss_8C4[i][j] & 0xF) == 7 ? 18
                : (lbl_1_bss_8C4[i][j] & 0xF) == 14 ? 19
                : (lbl_1_bss_8C4[i][j] & 0xF) == 10 ? 20
                : (lbl_1_bss_8C4[i][j] & 0xF) == 9 ? 21
                : (lbl_1_bss_8C4[i][j] & 0xF) == 5 ? 22
                : 23;
            fn_1_AB64(i, j, lbl_1_bss_8C4[i][j]);
            if ((lbl_1_bss_8C4[i][j] & 0xF00) != 0) {
                lbl_1_bss_8C4[i][j] |= 0x80;
            }
        }
    }
    lbl_1_bss_398 = 0;
    lbl_1_bss_394 = 0;
    lbl_1_bss_3F0 = 0;
}
#ifdef __MWERKS__
#endif

/* 0x68: jumptable_1_data_68 is fn_1_AB64's switch table */

/* 360 insns */
void fn_1_AB64(s32 a0, s32 a1, s32 a2)
{
    s32 i;
    s32 j;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            lbl_1_bss_540[a0][a1][i][j] = 0;
        }
    }
    switch (a2 & 0xF) {
        case 15:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 15;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 12:
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 12;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            break;
        case 3:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][1] = 3;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 11:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][1] = 11;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 13:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 13;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            break;
        case 7:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 7;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 14:
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 14;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 10:
            lbl_1_bss_540[a0][a1][1][1] = 10;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
        case 9:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][1] = 9;
            lbl_1_bss_540[a0][a1][1][2] = 12;
            break;
        case 5:
            lbl_1_bss_540[a0][a1][0][1] = 3;
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 5;
            break;
        case 6:
            lbl_1_bss_540[a0][a1][1][0] = 12;
            lbl_1_bss_540[a0][a1][1][1] = 6;
            lbl_1_bss_540[a0][a1][2][1] = 3;
            break;
    }
}

/* 667 insns */
void fn_1_B104(s32 size)
{
    s32 i;
    s32 r;

    lbl_1_bss_8C4[0][0] = 10;
    lbl_1_bss_8C4[size - 1][0] = 9;
    lbl_1_bss_8C4[0][size - 1] = 6;
    lbl_1_bss_8C4[size - 1][size - 1] = 5;
    for (i = 1; i < size - 1; i++) {
        lbl_1_bss_8C4[0][i] |= (lbl_1_bss_8C4[0][i - 1] & 8) ? 4 : 0;
        if (lbl_1_bss_8C4[0][i] == 0) {
            lbl_1_bss_8C4[0][i] |= 2;
        }
        else {
            lbl_1_bss_8C4[0][i] |= (frandmod(2) << 1);
        }
        if (i == size - 2) {
            lbl_1_bss_8C4[0][i] |= (lbl_1_bss_8C4[0][size - 1] & 4) ? 8 : 0;
        }
        else if (lbl_1_bss_8C4[0][i] == 4) {
            r = frandmod(3);
            if (r == 0) {
                lbl_1_bss_8C4[0][i] |= 0xA;
            }
            else if (r == 1) {
                lbl_1_bss_8C4[0][i] |= 8;
            }
            else {
                lbl_1_bss_8C4[0][i] |= 2;
            }
        }
        else if (lbl_1_bss_8C4[0][i] == 2) {
            lbl_1_bss_8C4[0][i] |= 8;
        }
        else {
            lbl_1_bss_8C4[0][i] |= (frandmod(2) << 3);
        }
    }
    for (i = 1; i < size - 1; i++) {
        lbl_1_bss_8C4[size - 1][i] |= (lbl_1_bss_8C4[size - 1][i - 1] & 8) ? 4 : 0;
        if (lbl_1_bss_8C4[size - 1][i] == 0) {
            lbl_1_bss_8C4[size - 1][i] |= 1;
        }
        else {
            lbl_1_bss_8C4[size - 1][i] |= frandmod(2);
        }
        if (i == size - 2) {
            lbl_1_bss_8C4[size - 1][i] |= (lbl_1_bss_8C4[size - 1][size - 1] & 4) ? 8 : 0;
        }
        else if (lbl_1_bss_8C4[size - 1][i] == 4) {
            r = frandmod(3);
            if (r == 0) {
                lbl_1_bss_8C4[size - 1][i] |= 9;
            }
            else if (r == 1) {
                lbl_1_bss_8C4[size - 1][i] |= 8;
            }
            else {
                lbl_1_bss_8C4[size - 1][i] |= 1;
            }
        }
        else if (lbl_1_bss_8C4[size - 1][i] == 1) {
            lbl_1_bss_8C4[size - 1][i] |= 8;
        }
        else {
            lbl_1_bss_8C4[size - 1][i] |= (frandmod(2) << 3);
        }
    }
    for (i = 1; i < size - 1; i++) {
        lbl_1_bss_8C4[i][0] |= (lbl_1_bss_8C4[i - 1][0] & 2) ? 1 : 0;
        if (lbl_1_bss_8C4[i][0] == 0) {
            lbl_1_bss_8C4[i][0] |= 8;
        }
        else {
            lbl_1_bss_8C4[i][0] |= (frandmod(2) << 3);
        }
        if (i == size - 2) {
            lbl_1_bss_8C4[i][0] |= (lbl_1_bss_8C4[size - 1][0] & 1) ? 2 : 0;
        }
        else if (lbl_1_bss_8C4[i][0] == 1) {
            r = frandmod(3);
            if (r == 0) {
                lbl_1_bss_8C4[i][0] |= 0xA;
            }
            else if (r == 1) {
                lbl_1_bss_8C4[i][0] |= 2;
            }
            else {
                lbl_1_bss_8C4[i][0] |= 8;
            }
        }
        else if (lbl_1_bss_8C4[i][0] == 8) {
            lbl_1_bss_8C4[i][0] |= 2;
        }
        else {
            lbl_1_bss_8C4[i][0] |= (frandmod(2) << 1);
        }
    }
    for (i = 1; i < size - 1; i++) {
        lbl_1_bss_8C4[i][size - 1] |= (lbl_1_bss_8C4[i - 1][size - 1] & 2) ? 1 : 0;
        if (lbl_1_bss_8C4[i][size - 1] == 0) {
            lbl_1_bss_8C4[i][size - 1] |= 4;
        }
        else {
            lbl_1_bss_8C4[i][size - 1] |= (frandmod(2) << 2);
        }
        if (i == size - 2) {
            lbl_1_bss_8C4[i][size - 1] |= (lbl_1_bss_8C4[size - 1][size - 1] & 1) ? 2 : 0;
        }
        else if (lbl_1_bss_8C4[i][size - 1] == 1) {
            r = frandmod(3);
            if (r == 0) {
                lbl_1_bss_8C4[i][size - 1] |= 6;
            }
            else if (r == 1) {
                lbl_1_bss_8C4[i][size - 1] |= 2;
            }
            else {
                lbl_1_bss_8C4[i][size - 1] |= 4;
            }
        }
        else if (lbl_1_bss_8C4[i][size - 1] == 4) {
            lbl_1_bss_8C4[i][size - 1] |= 2;
        }
        else {
            lbl_1_bss_8C4[i][size - 1] |= (frandmod(2) << 1);
        }
    }
}

/* 681 insns */
void fn_1_BB70(s32 a0, s32 a1, s32 a2)
{
    s32 r;
    s32 k;
    s32 m;
    lbl_1_bss_8C4[a0][a1] |= (lbl_1_bss_8C4[a0 - 1][a1] & 2) ? 1 : 0;
    lbl_1_bss_8C4[a0][a1] |= (lbl_1_bss_8C4[a0][a1 - 1] & 8) ? 4 : 0;
    if (a1 == a2 - 2) {
        lbl_1_bss_8C4[a0][a1] |= (lbl_1_bss_8C4[a0][a2 - 1] & 4) ? 8 : 0;
    } else {
        lbl_1_bss_8C4[a0][a1] |= frandmod(2) << 3;
    }
    if (lbl_1_bss_8C4[a0][a1] == 0) {
        r = frandmod(4);
        if (r == 0) {
            lbl_1_bss_8C4[a0][a1] |= 0xD;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        } else if (r == 1) {
            lbl_1_bss_8C4[a0][a1] |= 5;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
        } else if (r == 2) {
            lbl_1_bss_8C4[a0][a1] |= 9;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        } else {
            lbl_1_bss_8C4[a0][a1] |= 0xC;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        }
    } else if (lbl_1_bss_8C4[a0][a1] == 1) {
        r = frandmod(3);
        if (r == 0) {
            lbl_1_bss_8C4[a0][a1] |= 0xC;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        } else if (r == 1) {
            lbl_1_bss_8C4[a0][a1] |= 4;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
        } else {
            lbl_1_bss_8C4[a0][a1] |= 8;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        }
    } else if (lbl_1_bss_8C4[a0][a1] == 4) {
        r = frandmod(3);
        if (r == 0) {
            lbl_1_bss_8C4[a0][a1] |= 9;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        } else if (r == 1) {
            lbl_1_bss_8C4[a0][a1] |= 1;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
        } else {
            lbl_1_bss_8C4[a0][a1] |= 8;
            lbl_1_bss_8C4[a0][a1 + 1] |= 4;
        }
    } else if (lbl_1_bss_8C4[a0][a1] == 8) {
        r = frandmod(3);
        if (r == 0) {
            lbl_1_bss_8C4[a0][a1] |= 5;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
        } else if (r == 1) {
            lbl_1_bss_8C4[a0][a1] |= 1;
            lbl_1_bss_8C4[a0 - 1][a1] |= 2;
        } else {
            lbl_1_bss_8C4[a0][a1] |= 4;
            lbl_1_bss_8C4[a0][a1 - 1] |= 8;
        }
    }
    if (a0 == a2 - 2) {
        lbl_1_bss_8C4[a0][a1] |= (lbl_1_bss_8C4[a2 - 1][a1] & 1) ? 2 : 0;
    } else if (lbl_1_bss_8C4[a0][a1] == 5 || lbl_1_bss_8C4[a0][a1] == 9) {
        lbl_1_bss_8C4[a0][a1] |= 2;
    } else {
        lbl_1_bss_8C4[a0][a1] |= frandmod(2) << 1;
    }
    if (a1 == a2 - 2) {
        k = 0;
        r = 0;
        for (;;) {
            if (r == 0) {
                if (lbl_1_bss_8C4[a0][k] & 2) {
                    break;
                }
                k++;
                if (k == a2) {
                    r = frandmod(a2) + 1;
                    k = 0;
                }
            } else if (frandmod(5) == 0) {
                lbl_1_bss_8C4[a0][k] |= 2;
                lbl_1_bss_8C4[a0 + 1][k] |= 1;
                k++;
                r--;
                if (k == a2) {
                    k = 0;
                }
                if (r == 0) {
                    break;
                }
            }
        }
    }
    if (a0 == a2 - 2) {
        m = 0;
        r = 0;
        for (;;) {
            if (r == 0) {
                if (lbl_1_bss_8C4[m][a1] & 8) {
                    break;
                }
                m++;
                if (m == a2) {
                    r = frandmod(a2) + 1;
                    m = 0;
                }
            } else if (frandmod(5) == 0) {
                lbl_1_bss_8C4[m][a1] |= 8;
                lbl_1_bss_8C4[m][a1 + 1] |= 4;
                m++;
                r--;
                if (m == a2) {
                    m = 0;
                }
                if (r == 0) {
                    break;
                }
            }
        }
    }
}

/* 148 insns */
void fn_1_C614(s32 a0)
{
    s32 i;
    s32 r;
    lbl_1_bss_3D8[0] = lbl_1_bss_3D8[1] = lbl_1_bss_3D8[2] = 0;
    lbl_1_bss_3C8[0] = lbl_1_bss_3C8[1] = lbl_1_bss_3C8[2] = lbl_1_bss_3C8[3] = 0;
    lbl_1_bss_3BC[0] = lbl_1_bss_3BC[1] = lbl_1_bss_3BC[2] = 0;
    for (i = 0; i < a0; i++) {
        r = frandmod(100);
        if (r < 50) {
            lbl_1_bss_3D8[0]++;
        } else if (r < 80) {
            lbl_1_bss_3D8[1]++;
        } else {
            lbl_1_bss_3D8[2]++;
        }
    }
    for (i = 0; i < a0; i++) {
        r = frandmod(100);
        if (r < 10) {
            lbl_1_bss_3C8[0]++;
        } else if (r < 40) {
            lbl_1_bss_3C8[1]++;
        } else if (r < 70) {
            lbl_1_bss_3C8[2]++;
        } else {
            lbl_1_bss_3C8[3]++;
        }
    }
    for (i = 0; i < a0; i++) {
        r = frandmod(100);
        if (r < 60) {
            lbl_1_bss_3BC[0]++;
        } else if (r < 80) {
            lbl_1_bss_3BC[1]++;
        } else {
            lbl_1_bss_3BC[2]++;
        }
    }
}

/* 982 insns */
void fn_1_C864(CardGameWork *work)
{
    s32 i;
    s32 j;
    s32 size;
    s32 r;
    s32 a;
    s32 b;
    s32 c;
    size = work->unk194;
    a = 0;
    b = 0;
    c = 0;
    for (;;) {
        work->unk1C8 = 0;
        work->unk1CC = 0;
        work->unk1D0 = 0;
        fn_1_D7BC(work);
        fn_1_DC9C(work);
        fn_1_E17C(work);
        a = work->unk1C8;
        b = work->unk1CC;
        c = work->unk1D0;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_8C4[lbl_1_bss_3AC[i]][lbl_1_bss_39C[i]] & 0x100) {
                a--;
            } else if (lbl_1_bss_8C4[lbl_1_bss_3AC[i]][lbl_1_bss_39C[i]] & 0x200) {
                b--;
            } else if (lbl_1_bss_8C4[lbl_1_bss_3AC[i]][lbl_1_bss_39C[i]] & 0x400) {
                c--;
            }
        }
        lbl_1_bss_8C4[lbl_1_bss_3AC[0]][lbl_1_bss_39C[0]] &= 0xFF;
        lbl_1_bss_8C4[lbl_1_bss_3AC[1]][lbl_1_bss_39C[1]] &= 0xFF;
        lbl_1_bss_8C4[lbl_1_bss_3AC[2]][lbl_1_bss_39C[2]] &= 0xFF;
        lbl_1_bss_8C4[lbl_1_bss_3AC[3]][lbl_1_bss_39C[3]] &= 0xFF;
        if (a < size || b < size || c < size) {
            for (i = 0; i < 10; i++) {
                for (j = 0; j < 10; j++) {
                    lbl_1_bss_8C4[i][j] &= 0xFF;
                }
            }
        } else {
            break;
        }
    }
    do {
        i = frandmod(size);
        j = frandmod(size);
        if ((lbl_1_bss_8C4[i][j] & 0x100) && a > size) {
            lbl_1_bss_8C4[i][j] &= 0xFF;
            a--;
        }
        if ((lbl_1_bss_8C4[i][j] & 0x200) && b > size) {
            lbl_1_bss_8C4[i][j] &= 0xFF;
            b--;
        }
        if ((lbl_1_bss_8C4[i][j] & 0x400) && c > size) {
            lbl_1_bss_8C4[i][j] &= 0xFF;
            c--;
        }
    } while (a != size || b != size || c != size);
    work->unk1C8 = a;
    work->unk1CC = b;
    work->unk1D0 = c;
    fn_1_C614(size);
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (lbl_1_bss_8C4[i][j] & 0x100) {
                r = frandmod(3);
                if (r == 0) {
                    if (lbl_1_bss_3D8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3D8[0]--;
                    } else if (lbl_1_bss_3D8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3D8[1]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3D8[2]--;
                    }
                } else if (r == 1) {
                    if (lbl_1_bss_3D8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3D8[1]--;
                    } else if (lbl_1_bss_3D8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3D8[0]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3D8[2]--;
                    }
                } else {
                    if (lbl_1_bss_3D8[2] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3D8[2]--;
                    } else if (lbl_1_bss_3D8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3D8[0]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3D8[1]--;
                    }
                }
            } else if (lbl_1_bss_8C4[i][j] & 0x200) {
                r = frandmod(4);
                if (r == 0) {
                    if (lbl_1_bss_3C8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3C8[0]--;
                    } else if (lbl_1_bss_3C8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3C8[1]--;
                    } else if (lbl_1_bss_3C8[2] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3C8[2]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x8000;
                        lbl_1_bss_3C8[3]--;
                    }
                } else if (r == 1) {
                    if (lbl_1_bss_3C8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3C8[1]--;
                    } else if (lbl_1_bss_3C8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3C8[0]--;
                    } else if (lbl_1_bss_3C8[2] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3C8[2]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x8000;
                        lbl_1_bss_3C8[3]--;
                    }
                } else if (r == 2) {
                    if (lbl_1_bss_3C8[2] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3C8[2]--;
                    } else if (lbl_1_bss_3C8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3C8[0]--;
                    } else if (lbl_1_bss_3C8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3C8[1]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x8000;
                        lbl_1_bss_3C8[3]--;
                    }
                } else {
                    if (lbl_1_bss_3C8[3] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x8000;
                        lbl_1_bss_3C8[3]--;
                    } else if (lbl_1_bss_3C8[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3C8[0]--;
                    } else if (lbl_1_bss_3C8[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3C8[1]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3C8[2]--;
                    }
                }
            } else if (lbl_1_bss_8C4[i][j] & 0x400) {
                r = frandmod(3);
                if (r == 0) {
                    if (lbl_1_bss_3BC[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3BC[0]--;
                    } else if (lbl_1_bss_3BC[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3BC[1]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3BC[2]--;
                    }
                } else if (r == 1) {
                    if (lbl_1_bss_3BC[1] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3BC[1]--;
                    } else if (lbl_1_bss_3BC[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3BC[0]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3BC[2]--;
                    }
                } else {
                    if (lbl_1_bss_3BC[2] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x4000;
                        lbl_1_bss_3BC[2]--;
                    } else if (lbl_1_bss_3BC[0] > 0) {
                        lbl_1_bss_8C4[i][j] |= 0x1000;
                        lbl_1_bss_3BC[0]--;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x2000;
                        lbl_1_bss_3BC[1]--;
                    }
                }
            }
        }
    }
}

/* 312 insns */
void fn_1_D7BC(CardGameWork *work)
{
    s32 i;
    s32 j;
    s32 size;
    s32 r;
    s32 start;
    size = work->unk194;
    j = 0;
    start = 1;
    for (i = start; i < size - 1; i++) {
        r = frandmod(3);
        if (r == 0) {
            if (!(lbl_1_bss_8C4[j][i - 1] & 0x100)) {
                lbl_1_bss_8C4[j][i] |= 0x100;
                work->unk1C8++;
            } else if (frandmod(2)) {
                if (work->unk1CC < size) {
                    lbl_1_bss_8C4[j][i] |= 0x200;
                    work->unk1CC++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x400;
                    work->unk1D0++;
                }
            } else {
                if (work->unk1D0 < size) {
                    lbl_1_bss_8C4[j][i] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x200;
                    work->unk1CC++;
                }
            }
        } else if (r == 1) {
            if (!(lbl_1_bss_8C4[j][i - 1] & 0x200)) {
                lbl_1_bss_8C4[j][i] |= 0x200;
                work->unk1CC++;
            } else if (frandmod(2)) {
                if (work->unk1C8 < size) {
                    lbl_1_bss_8C4[j][i] |= 0x100;
                    work->unk1C8++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x400;
                    work->unk1D0++;
                }
            } else {
                if (work->unk1D0 < size) {
                    lbl_1_bss_8C4[j][i] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x100;
                    work->unk1C8++;
                }
            }
        } else {
            if (!(lbl_1_bss_8C4[j][i - 1] & 0x400)) {
                lbl_1_bss_8C4[j][i] |= 0x400;
                work->unk1D0++;
            } else if (frandmod(2)) {
                if (work->unk1C8 < size) {
                    lbl_1_bss_8C4[j][i] |= 0x100;
                    work->unk1C8++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x200;
                    work->unk1CC++;
                }
            } else {
                if (work->unk1CC < size) {
                    lbl_1_bss_8C4[j][i] |= 0x200;
                    work->unk1CC++;
                } else {
                    lbl_1_bss_8C4[j][i] |= 0x100;
                    work->unk1C8++;
                }
            }
        }
    }
    for (i = start; i < size - 1; i++) {
        if (lbl_1_bss_8C4[j][i] & 0x400) {
            lbl_1_bss_8C4[j][i] &= ~0x400;
        }
    }
    work->unk1D0 = 0;
}

/* 312 insns */
void fn_1_DC9C(CardGameWork *work)
{
    s32 i;
    s32 j;
    s32 size;
    s32 r;
    s32 start;
    size = work->unk194;
    start = 1;
    j = 0;
    for (i = start; i < size - 1; i++) {
        r = frandmod(3);
        if (r == 0) {
            if (!(lbl_1_bss_8C4[i - 1][j] & 0x100)) {
                lbl_1_bss_8C4[i][j] |= 0x100;
                work->unk1C8++;
            } else if (frandmod(2)) {
                if (work->unk1CC < size) {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                }
            } else {
                if (work->unk1D0 < size) {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                }
            }
        } else if (r == 1) {
            if (!(lbl_1_bss_8C4[i - 1][j] & 0x200)) {
                lbl_1_bss_8C4[i][j] |= 0x200;
                work->unk1CC++;
            } else if (frandmod(2)) {
                if (work->unk1C8 < size) {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                }
            } else {
                if (work->unk1D0 < size) {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                }
            }
        } else {
            if (!(lbl_1_bss_8C4[i - 1][j] & 0x400)) {
                lbl_1_bss_8C4[i][j] |= 0x400;
                work->unk1D0++;
            } else if (frandmod(2)) {
                if (work->unk1C8 < size) {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                }
            } else {
                if (work->unk1CC < size) {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                }
            }
        }
    }
    for (i = start; i < size - 1; i++) {
        if (lbl_1_bss_8C4[i][j] & 0x400) {
            lbl_1_bss_8C4[i][j] &= ~0x400;
        }
    }
    work->unk1D0 = 0;
}

/* 623 insns */
void fn_1_E17C(CardGameWork *work)
{
    s32 i;
    s32 j;
    s32 size;
    s32 r;
    s32 startI;
    s32 startJ;
    s32 endI;
    s32 endJ;
    size = work->unk194;
    startI = 1;
    startJ = 1;
    endI = size;
    endJ = size;
    for (i = startI; i < endI; i++) {
        for (j = startJ; j < endJ; j++) {
            if (i == size - 1 && j == size - 1) {
                break;
            }
            r = frandmod(3);
            if (r == 0) {
                if (!(lbl_1_bss_8C4[i - 1][j] & 0x100)) {
                    if (!(lbl_1_bss_8C4[i][j - 1] & 0x100)) {
                        lbl_1_bss_8C4[i][j] |= 0x100;
                        work->unk1C8++;
                    } else if (lbl_1_bss_8C4[i - 1][j] & 0x200) {
                        lbl_1_bss_8C4[i][j] |= 0x400;
                        work->unk1D0++;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x200;
                        work->unk1CC++;
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x100) {
                    if (frandmod(2)) {
                        if (work->unk1CC < size) {
                            lbl_1_bss_8C4[i][j] |= 0x200;
                            work->unk1CC++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x400;
                            work->unk1D0++;
                        }
                    } else {
                        if (work->unk1D0 < size) {
                            lbl_1_bss_8C4[i][j] |= 0x400;
                            work->unk1D0++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x200;
                            work->unk1CC++;
                        }
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x200) {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                }
            } else if (r == 1) {
                if (!(lbl_1_bss_8C4[i - 1][j] & 0x200)) {
                    if (!(lbl_1_bss_8C4[i][j - 1] & 0x200)) {
                        lbl_1_bss_8C4[i][j] |= 0x200;
                        work->unk1CC++;
                    } else if (lbl_1_bss_8C4[i - 1][j] & 0x100) {
                        lbl_1_bss_8C4[i][j] |= 0x400;
                        work->unk1D0++;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x100;
                        work->unk1C8++;
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x200) {
                    if (frandmod(2)) {
                        if (work->unk1C8 < size) {
                            lbl_1_bss_8C4[i][j] |= 0x100;
                            work->unk1C8++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x400;
                            work->unk1D0++;
                        }
                    } else {
                        if (work->unk1D0 < size) {
                            lbl_1_bss_8C4[i][j] |= 0x400;
                            work->unk1D0++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x100;
                            work->unk1C8++;
                        }
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x100) {
                    lbl_1_bss_8C4[i][j] |= 0x400;
                    work->unk1D0++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                }
            } else {
                if (!(lbl_1_bss_8C4[i - 1][j] & 0x400)) {
                    if (!(lbl_1_bss_8C4[i][j - 1] & 0x400)) {
                        lbl_1_bss_8C4[i][j] |= 0x400;
                        work->unk1D0++;
                    } else if (lbl_1_bss_8C4[i - 1][j] & 0x100) {
                        lbl_1_bss_8C4[i][j] |= 0x200;
                        work->unk1CC++;
                    } else {
                        lbl_1_bss_8C4[i][j] |= 0x100;
                        work->unk1C8++;
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x400) {
                    if (frandmod(2)) {
                        if (work->unk1C8 < size) {
                            lbl_1_bss_8C4[i][j] |= 0x100;
                            work->unk1C8++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x200;
                            work->unk1CC++;
                        }
                    } else {
                        if (work->unk1CC < size) {
                            lbl_1_bss_8C4[i][j] |= 0x200;
                            work->unk1CC++;
                        } else {
                            lbl_1_bss_8C4[i][j] |= 0x100;
                            work->unk1C8++;
                        }
                    }
                } else if (lbl_1_bss_8C4[i][j - 1] & 0x100) {
                    lbl_1_bss_8C4[i][j] |= 0x200;
                    work->unk1CC++;
                } else {
                    lbl_1_bss_8C4[i][j] |= 0x100;
                    work->unk1C8++;
                }
            }
        }
    }
    for (i = startI; i < endI; i++) {
        for (j = startJ; j < endJ; j++) {
            if ((i == size - 1 || j == size - 1) && (lbl_1_bss_8C4[i][j] & 0x400)) {
                lbl_1_bss_8C4[i][j] &= ~0x400;
                work->unk1D0--;
            }
        }
    }
}

/* 371 insns */
s32 fn_1_EB38(s32 x, s32 y)
{
    s32 result = 0;
    char names[4][15] = { "S3_c_ura_item", "S3_c_ura_event", "c_ura_star", "S3_c_ura_r" };
    s32 animNo;
    s32 nameNo;
    if (lbl_1_bss_398 == 0) {
        animNo = ((lbl_1_bss_8C4[x][y] & 0xF) == 15) ? 0
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 12) ? 1
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 3) ? 2
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 11) ? 3
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 13) ? 4
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 7) ? 5
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 14) ? 6
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 10) ? 7
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 9) ? 8
            : ((lbl_1_bss_8C4[x][y] & 0xF) == 5) ? 9 : 10;
        nameNo = (lbl_1_bss_8C4[x][y] & 0x100) ? 0
            : (lbl_1_bss_8C4[x][y] & 0x200) ? 1
            : (lbl_1_bss_8C4[x][y] & 0x400) ? 2 : 3;
        lbl_1_bss_330[lbl_1_bss_394] = Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[animNo + 91], HU_MEMNUM_OVL), lbl_1_bss_478[x][y], names[nameNo]);
        lbl_1_bss_394++;
        lbl_1_bss_398 = 1;
        fn_1_F2A8(0, 0, 0);
    } else if (fn_1_F2A8(2, x, y)) {
        lbl_1_bss_398 = 0;
        result = 1;
    }
    return result;
}

/* 41 insns */
void fn_1_F104(s32 a0, s32 a1)
{
    lbl_1_bss_330[lbl_1_bss_394] = Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[32], HU_MEMNUM_OVL), lbl_1_bss_478[a0][a1], "S3_c029");
    lbl_1_bss_394++;
}

/* 41 insns */
void fn_1_F1A8(s32 a0, s32 a1)
{
    lbl_1_bss_330[lbl_1_bss_394] = Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[32], HU_MEMNUM_OVL), lbl_1_bss_478[a0][a1], "S3_c028");
    lbl_1_bss_394++;
}

/* 23 insns */
void fn_1_F24C(void)
{
    s32 i;
    for (i = 0; i < lbl_1_bss_394; i++) {
        Hu3DAnimKill(lbl_1_bss_330[i]);
    }
}

/* 479 insns */
s32 fn_1_F2A8(s32 a0, s32 a1, s32 a2)
{
    HuVecF pos;
    s16 id;
    s32 result = 0;
    if (a0 == 0) {
        lbl_1_bss_32C = 1;
        lbl_1_bss_324 = 0.0f;
        lbl_1_bss_320 = 0;
        result = 1;
    } else if (lbl_1_bss_32C == 0) {
        if (a0 == 1) {
            lbl_1_bss_328 -= 10.0f;
            if (lbl_1_bss_328 < 0.0f) {
                lbl_1_bss_328 = 180.0f;
                lbl_1_bss_32C = 2;
            } else {
                Hu3DModelRotSet(lbl_1_bss_478[a1][a2], 0.0f, 0.0f, lbl_1_bss_328);
            }
        } else {
            lbl_1_bss_328 += 10.0f;
            if (lbl_1_bss_328 > 180.0f) {
                lbl_1_bss_328 = 0.0f;
                lbl_1_bss_32C = 2;
            } else {
                Hu3DModelRotSet(lbl_1_bss_478[a1][a2], 0.0f, 0.0f, -lbl_1_bss_328);
            }
        }
    } else {
        pos.x = lbl_1_bss_3E4[0] + 300.0f * a2;
        pos.y = lbl_1_bss_3E4[1];
        pos.z = lbl_1_bss_3E4[2] + 300.0f * a1;
        Hu3DModelPosSet(lbl_1_bss_478[a1][a2], -50.0f + pos.x, pos.y + lbl_1_bss_324, pos.z);
        if (lbl_1_bss_32C == 1) {
            lbl_1_bss_324 += 5.0f;
            if (lbl_1_bss_324 > 100.0f) {
                lbl_1_bss_324 = 100.0f;
                lbl_1_bss_32C = 0;
                if (a0 == 1) {
                    lbl_1_bss_328 = 180.0f;
                } else {
                    lbl_1_bss_328 = 0.0f;
                }
                if ((lbl_1_bss_8C4[a1][a2] & 0x400) && !(lbl_1_bss_8C4[a1][a2] & 0x10)) {
                    HuAudSStreamVolSet(0, 0, 1000);
                    if (lbl_1_bss_8C4[a1][a2] & 0x1000) {
                        fn_1_8D04(0x402, lbl_1_bss_478[a1][a2], 1);
                    } else if (lbl_1_bss_8C4[a1][a2] & 0x2000) {
                        fn_1_8D04(0x403, lbl_1_bss_478[a1][a2], 1);
                    } else if (lbl_1_bss_8C4[a1][a2] & 0x4000) {
                        fn_1_8D04(0x404, lbl_1_bss_478[a1][a2], 1);
                    }
                } else if ((lbl_1_bss_8C4[a1][a2] & 0x200) && !(lbl_1_bss_8C4[a1][a2] & 0x10)) {
                    if (lbl_1_bss_8C4[a1][a2] & 0xC000) {
                        fn_1_8D04(0x451, lbl_1_bss_478[a1][a2], 1);
                    } else {
                        fn_1_8D04(0x3F6, lbl_1_bss_478[a1][a2], 1);
                    }
                } else {
                    fn_1_8D04(0x3F6, lbl_1_bss_478[a1][a2], 1);
                }
            }
        } else {
            lbl_1_bss_324 -= 5.0f;
            if (lbl_1_bss_324 < 0.0f) {
                lbl_1_bss_8C4[a1][a2] |= 0x10;
                lbl_1_bss_324 = 0.0f;
                result = 1;
            }
            if (lbl_1_bss_320 == 0 && lbl_1_bss_324 <= 5.0f) {
                pos.x += -50.0f;
                pos.y += 1.0f;
                id = fn_1_3ED3C(0, pos);
                lbl_1_bss_320 = 1;
                fn_1_8D04(0x454, lbl_1_bss_478[a1][a2], 1);
            }
        }
    }
    return result;
}

