/*
 * m565dll com.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/com.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x290 */ /* float lbl_1_rodata_290 = 60.0f; */
/* 0x294 */ /* float lbl_1_rodata_294 = 30.0f; */
/* 0x298 */ /* float lbl_1_rodata_298 = 10000.0f; */
/* 0x29C */ /* float lbl_1_rodata_29C = 350.0f; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 4503599627370496; */
/* 0x2A8 */ /* float lbl_1_rodata_2A8 = 0.0f; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 180; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 3.141592653589793; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 360; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = -180; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = 120.0f; */
/* 0x2D4 */ /* float lbl_1_rodata_2D4 = 150.0f; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 200.0f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 300.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 400.0f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 190.0f; */
/* 0x2E8 */ /* float lbl_1_rodata_2E8 = 170.0f; */
/* 0x2EC */ /* float lbl_1_rodata_2EC = 130.0f; */
/* 0x2F0 */ /* double lbl_1_rodata_2F0 = 0; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = 0.5; */
/* 0x300 */ /* double lbl_1_rodata_300 = 3; */
/* 0x308 */ /* double lbl_1_rodata_308 = 4503601774854144; */
/* 0x310 */ /* float lbl_1_rodata_310 = 45.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 0.5f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 1.5f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 2.5f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 3.5f; */
/* 0x324 */ /* s32 lbl_1_rodata_324[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x330 */ /* double lbl_1_rodata_330 = 1; */
/* 0x338 */ /* float lbl_1_rodata_338 = -3.0f; */
/* 0x33C */ /* float lbl_1_rodata_33C = 1.0f; */
/* 0x340 */ /* float lbl_1_rodata_340 = 140.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 50.0f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 0.9f; */
/* 0x34C */ /* float lbl_1_rodata_34C = 0.8f; */
/* 0x350 */ /* float lbl_1_rodata_350 = 0.2f; */
/* 0x354 */ /* float lbl_1_rodata_354 = 56.0f; */

/* --- .data --- */
/* per-COM-level (GwPlayerConf[].dif mapped to 0 = hardest .. 3) tuning, indexed by com->unk008 */
/* 0xB28 */ s32 lbl_1_data_B28[4] = { 0x00000002, 0x0000000A, 0x0000000F, 0x00000014 }; /* action-button interval base (unk012) */
/* 0xB38 */ s32 lbl_1_data_B38[4] = { 0x00000000, 0x00000000, 0x000001F4, 0x000003E8 }; /* /10000: mode 0 on a 101/102 cell -> mode 3 */
/* 0xB48 */ s32 lbl_1_data_B48[4] = { 0x00000000, 0x00000000, 0x000001F4, 0x000003E8 }; /* /10000: mode 1 near a puku -> mode 3 */
/* 0xB58 */ s32 lbl_1_data_B58[4] = { 0x00001770, 0x00001388, 0x00000BB8, 0x000007D0 }; /* /10000: mode 2 near a player: action 5 vs 4 */
/* 0xB68 */ s32 lbl_1_data_B68[4] = { 0x000005DC, 0x000009C4, 0x00000DAC, 0x00000FA0 }; /* /10000: mode 3 action 0 */
/* 0xB78 */ s32 lbl_1_data_B78[4] = { 0x000005DC, 0x000009C4, 0x00000DAC, 0x00000FA0 }; /* /10000: mode 3 action 6 (else 5) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7868 */ M565_STAGEGRID *lbl_1_bss_7868[10]; /* fn_1_AB14's fn_1_BE54 output list (lwz [0], lha 0xE/0x10) */
/* 0x7844 */ M565_STAGEGRID *lbl_1_bss_7844[9]; /* candidate cells: fn_1_C368 stw, fn_1_BE54 sorts */
/* 0x7832 */ s16 lbl_1_bss_7832[9]; /* per-candidate sort key, parallel to lbl_1_bss_7844 */
/* 0x7830 */ s16 lbl_1_bss_7830; /* candidate count (< 9) */

/* 60..90 frames */
#define COM_TIME() (60.0f + 30.0f * ((frand() % 10000) / 10000.0f))
/* HuAtan wrapped to (-180, 180] */
#define COM_ANGLE(x, z) (HuAtan((x), (z)) > 180.0 ? HuAtan((x), (z)) - 360.0 : (HuAtan((x), (z)) <= -180.0 ? 360.0 + HuAtan((x), (z)) : HuAtan((x), (z))))

/* --- functions (reference order) --- */
/* 82 insns */
void fn_1_9EAC(M565_COM *com, M565_PLAYER *player)
{
    memset(com, 0, sizeof(M565_COM));
    com->unk000 = player;
    com->unk004 = GwPlayerConf[player->unk008].type;
    com->unk008 = GwPlayerConf[player->unk008].dif == 3 ? 0 : (GwPlayerConf[player->unk008].dif == 2 ? 1 : (GwPlayerConf[player->unk008].dif == 1 ? 2 : 3));
    com->unk012 = lbl_1_data_B28[com->unk008] + frand() % (lbl_1_data_B28[com->unk008] / 2);
}

/* 12 insns */
void fn_1_9FF4(M565_COM *com)
{
    memset(com, 0, sizeof(M565_COM));
}

/* 11 insns */
void fn_1_A024(M565_COM *com)
{
    com->unk01C = 0;
    com->unk020 = 4;
    com->unk014 = 0;
    com->unk016 = 0;
    com->unk018 = 0;
}

/* 609 insns */
void fn_1_A050(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    s32 r;

    com->unk044 = 0;
    com->unk048 = 0;
    com->unk04C = 0;
    com->unk050 = 0;
    if (player->unk090 != 0) {
        return;
    }
    cell = &stage->unk004[player->unk08A][player->unk088];
    if (com->unk01C <= 0) {
        fn_1_A024(com);
    }
    if (com->unk020 > 0 && (cell->unk004 == 101 || cell->unk004 == 102)) {
        if (frand() % 10000 < lbl_1_data_B38[com->unk008]) {
            com->unk014 = 0;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 3;
        } else {
            com->unk00C = player->unk080;
            com->unk014 = 1;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 0;
            goto action;
        }
    }
    if (com->unk020 > 1) {
        if (cell->unk034 != 0) {
            if (frand() % 10000 < lbl_1_data_B48[com->unk008]) {
                com->unk014 = 0;
                com->unk016 = 0;
                com->unk01C = COM_TIME();
                com->unk020 = 3;
                goto action;
            } else {
                com->unk014 = 3;
                com->unk016 = 0;
                com->unk01C = COM_TIME();
                com->unk020 = 1;
                goto action;
            }
        } else if (player->unk004->stunType == 5) {
            com->unk014 = 2;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 1;
            goto action;
        }
    }
    if (com->unk020 > 2 && player->unk080 && player->unk084 < 350.0f) {
        if (frand() % 10000 < lbl_1_data_B58[com->unk008]) {
            com->unk00C = player->unk080;
            com->unk014 = 5;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 2;
            goto action;
        } else {
            com->unk00C = player->unk080;
            com->unk014 = 4;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 2;
            goto action;
        }
    }
    if (com->unk020 > 3) {
        r = frand() % 10000;
        if (r < lbl_1_data_B68[com->unk008]) {
            com->unk014 = 0;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 3;
        } else if (r < lbl_1_data_B68[com->unk008] + lbl_1_data_B78[com->unk008]) {
            com->unk014 = 6;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 3;
        } else {
            com->unk00C = player->unk080;
            com->unk014 = 5;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 3;
        }
    }
action:
    switch (com->unk014) {
        case 0:
            if (fn_1_A9D4(com)) {
                com->unk01C = 0;
            }
            break;
        case 1:
            if (fn_1_AB14(com)) {
                com->unk01C = 0;
            }
            break;
        case 2:
            if (fn_1_AEF4(com)) {
                com->unk01C = 0;
            }
            break;
        case 3:
            if (fn_1_AC18(com)) {
                com->unk01C = 0;
            }
            break;
        case 4:
            if (fn_1_AEF4(com)) {
                com->unk01C = 0;
            }
            break;
        case 5:
            if (fn_1_B600(com)) {
                com->unk01C = 0;
            }
            break;
        case 6:
            if (fn_1_B96C(com)) {
                com->unk01C = 0;
            }
            break;
    }
    if (com->unk01C != 0) {
        com->unk01C--;
    }
}

/* 80 insns */
s32 fn_1_A9D4(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    M565_STAGEGRID *target;

    cell = &stage->unk004[player->unk08A][player->unk088];
    if (cell->unk004 != 100 && cell->unk004 != 101) {
        fn_1_C62C(com, &target);
        if (target) {
            com->unk022 = target->unk00E;
            com->unk024 = target->unk010;
            fn_1_CE68(com);
            com->unk014 = 6;
            com->unk016 = 0;
            com->unk01C = COM_TIME();
            com->unk020 = 3;
        }
    }
    return 0;
}

/* 65 insns */
s32 fn_1_AB14(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    s32 result = 0;
    s16 num;

    switch (com->unk016) {
        case 0:
            fn_1_BE54(com, &num, lbl_1_bss_7868);
            if (num != 0) {
                cell = lbl_1_bss_7868[0];
                com->unk022 = cell->unk00E;
                com->unk024 = cell->unk010;
            } else {
                fn_1_BD0C(com);
            }
            com->unk016++;
        case 1:
            if (fn_1_CE68(com)) {
                cell = &stage->unk004[player->unk08A][player->unk088];
                if (cell->unk004 == 100 || cell->unk004 == 101) {
                    result = 1;
                }
                com->unk016 = 0;
            }
            break;
    }
    return result;
}

/* 183 insns */
s32 fn_1_AC18(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    s32 result = 0;
    s32 found;
    HuVecF dir;
    s16 dirNo;
    s16 dx;
    s16 dz;

    switch (com->unk016) {
        case 0:
            found = 0;
            cell = &stage->unk004[player->unk08A][player->unk088];
            if (cell->unk034 != 0 && cell->unk038 && cell->unk038->unk004 != 0) {
                PSVECSubtract(player->unk074, &cell->unk038->unk010, &dir);
                dir.y = 0.0f;
                PSVECNormalize(&dir, &dir);
                fn_1_CBB4(COM_ANGLE(dir.x, dir.z), &dirNo);
                fn_1_CAD8(dirNo, &dx, &dz);
                com->unk022 = player->unk088 + dx * 3;
                com->unk024 = player->unk08A + dz * 3;
                found = 1;
            }
            if (!found) {
                fn_1_BD0C(com);
            }
            com->unk016++;
        case 1:
            if (fn_1_CE68(com)) {
                cell = &stage->unk004[player->unk08A][player->unk088];
                if (cell->unk034 == 0) {
                    result = 1;
                }
                com->unk016 = 0;
            }
            break;
    }
    return result;
}

/* the best-scored (unk02C) in-bounds cell of the four probes around dirNo +-2
 * (AEF4, B96C). Retail: the fourth probe does not re-index cell, it rescores
 * whichever cell the previous in-bounds probe left (uninitialised if none). */
#define COM_PROBE(dirNo, i)                                                                                  \
    fn_1_CAD8((dirNo + 2 - i) % 8, &dx, &dz);                                                                \
    x = player->unk088 + dx * 3;                                                                             \
    z = player->unk08A + dz * 3;                                                                             \
    if (x >= 0 && x < 10 && z >= 0 && z < 10) {                                                              \
        cell = &stage->unk004[z][x];                                                                         \
        if (best < cell->unk02C) {                                                                           \
            best = cell->unk02C;                                                                             \
            bestCell = cell;                                                                                 \
        }                                                                                                    \
    }                                                                                                        \
    x = player->unk088 + dx;                                                                                 \
    z = player->unk08A + dz;                                                                                 \
    if (x >= 0 && x < 10 && z >= 0 && z < 10) {                                                              \
        cell = &stage->unk004[z][x];                                                                         \
        if (best < cell->unk02C) {                                                                           \
            best = cell->unk02C;                                                                             \
            bestCell = cell;                                                                                 \
        }                                                                                                    \
    }                                                                                                        \
    fn_1_CAD8((dirNo - 2 + i) % 8, &dx, &dz);                                                                \
    x = player->unk088 + dx * 3;                                                                             \
    z = player->unk08A + dz * 3;                                                                             \
    if (x >= 0 && x < 10 && z >= 0 && z < 10) {                                                              \
        cell = &stage->unk004[z][x];                                                                         \
        if (best < cell->unk02C) {                                                                           \
            best = cell->unk02C;                                                                             \
            bestCell = cell;                                                                                 \
        }                                                                                                    \
    }                                                                                                        \
    x = player->unk088 + dx;                                                                                 \
    z = player->unk08A + dz;                                                                                 \
    if (x >= 0 && x < 10 && z >= 0 && z < 10) {                                                              \
        /* retail re-scores the stale `cell` here (never re-indexed); host: skip while it is unset */         \
        if (M565_PC_OK(cell != NULL) && best < cell->unk02C) {                                               \
            best = cell->unk02C;                                                                             \
            bestCell = cell;                                                                                 \
        }                                                                                                    \
    }

/* 451 insns */
s32 fn_1_AEF4(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    M565_STAGEGRID *bestCell;
    s16 best;
    s16 x;
    s16 z;
    s32 i;
    s32 result;
    float dot;
    HuVecF dir;
    HuVecF a;
    HuVecF b;
    s16 dirNo;
    s16 dx;
    s16 dz;

    if (!player->unk080) {
        return 1;
    }
    if (player->unk080->unk090 != 0) {
        return 1;
    }
    result = 0;
    switch (com->unk016) {
        case 0:
            fn_1_BD0C(com);
            if (frand() % 10000 < 7000) {
                PSVECSubtract(player->unk074, player->unk080->unk074, &dir);
                dir.y = 0.0f;
                PSVECNormalize(&dir, &dir);
                fn_1_CBB4(COM_ANGLE(dir.x, dir.z), &dirNo);
                best = 0;
                bestCell = NULL;
                for (i = 0; i < 3; i++) {
                    COM_PROBE(dirNo, i);
                }
                if (bestCell) {
                    com->unk022 = bestCell->unk00E;
                    com->unk024 = bestCell->unk010;
                } else {
                    fn_1_BD0C(com);
                }
            }
            com->unk016++;
        case 1:
            if (fn_1_CE68(com)) {
                com->unk016 = 0;
            }
            if (player->unk080 && player->unk084 < 120.0f) {
                a.x = HuSin(player->unk078->y);
                a.y = 0.0f;
                a.z = HuCos(player->unk078->y);
                b.x = HuSin(player->unk080->unk078->y);
                b.y = 0.0f;
                b.z = HuCos(player->unk080->unk078->y);
                dot = PSVECDotProduct(&a, &b);
                if (dot < 0.0f) {
                    com->unk00C = player->unk080;
                    com->unk014 = 5;
                    com->unk016 = 0;
                    com->unk01C = COM_TIME();
                    com->unk020 = 2;
                }
            }
            break;
    }
    if (com->unk01C <= 0) {
        result = 1;
    }
    return result;
}

/* 219 insns */
s32 fn_1_B600(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    s32 result;
    float dist;

    if (!com->unk00C) {
        return 1;
    }
    if (com->unk00C->unk090 != 0) {
        return 1;
    }
    result = 0;
    switch (com->unk016) {
        case 0:
            if (frand() % 10000 < 7000) {
                com->unk022 = com->unk00C->unk088;
                com->unk024 = com->unk00C->unk08A;
            } else {
                fn_1_BD0C(com);
            }
            com->unk012 = (lbl_1_data_B28[com->unk008] + frand() % (lbl_1_data_B28[com->unk008] / 2)) / 2;
            com->unk016++;
        case 1:
            if (fn_1_CE68(com)) {
                com->unk016 = 0;
                if (com->unk01C <= 0) {
                    result = 1;
                }
                if (com->unk008 == 3 && player->unk084 > 150.0f) {
                    result = 1;
                } else if (com->unk008 == 2 && player->unk084 > 200.0f) {
                    result = 1;
                } else if (com->unk008 == 1 && player->unk084 > 300.0f) {
                    result = 1;
                } else if (com->unk008 == 0 && player->unk084 > 400.0f) {
                    result = 1;
                }
            }
            if (player->unk080) {
                dist = com->unk008 == 0 ? 190.0f : (com->unk008 == 1 ? 170.0f : (com->unk008 == 2 ? 150.0f : 130.0f));
                if (player->unk084 < dist) {
                    com->unk040 = 1;
                    if (com->unk012-- <= 0) {
                        com->unk044 |= PAD_BUTTON_B;
                        com->unk012 = lbl_1_data_B28[com->unk008] + frand() % (lbl_1_data_B28[com->unk008] / 2);
                    }
                }
            }
            break;
    }
    return result;
}

/* 232 insns */
s32 fn_1_B96C(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    M565_STAGEGRID *bestCell;
    s16 best;
    s16 x;
    s16 z;
    s32 i;
    s32 result;
    s16 dirNo;
    s16 dx;
    s16 dz;

    result = 0;
    switch (com->unk016) {
        case 0:
            fn_1_BD0C(com);
            com->unk016++;
        case 1:
            if (fn_1_CE68(com)) {
                if (com->unk01C <= 0) {
                    result = 1;
                    break;
                }
                fn_1_CBB4(player->unk078->y, &dirNo);
                best = 0;
                bestCell = NULL;
                for (i = 0; i < 3; i++) {
                    COM_PROBE(dirNo, i);
                }
                if (bestCell) {
                    com->unk022 = bestCell->unk00E;
                    com->unk024 = bestCell->unk010;
                } else {
                    fn_1_BD0C(com);
                }
            }
            if (player->unk080 && player->unk080->unk090 == 0 && player->unk084 < 150.0f) {
                com->unk00C = player->unk080;
                com->unk014 = 4;
                com->unk016 = 0;
                com->unk020 = 2;
            }
            break;
    }
    return result;
}

/* 82 insns */
void fn_1_BD0C(M565_COM *com)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *cell;
    M565_STAGEGRID *bestCell;
    s16 best;
    s32 i;
    s16 x;
    s16 z;

    cell = bestCell = NULL;
    best = 0;
    for (i = 0; i < 8; i++) {
        x = frand() % 7 - 3 + player->unk088;
        z = frand() % 7 - 3 + player->unk08A;
        if (x >= 0 && x < 10 && z >= 0 && z < 10) {
            cell = &stage->unk004[z][x];
            if (best < cell->unk02C) {
                best = cell->unk02C;
                bestCell = cell;
            }
        }
    }
    if (bestCell) {
        com->unk022 = bestCell->unk00E;
        com->unk024 = bestCell->unk010;
    }
}

/* 229 insns */
void fn_1_BE54(M565_COM *com, s16 *count, M565_STAGEGRID **out)
{
    M565_PLAYER *player = com->unk000;
    M565_OBJECT *obj = player->unk000;
    M565_STAGE *stage = &obj->unk2E4;
    M565_STAGEGRID *a;
    M565_STAGEGRID *b;
    s32 i;
    s32 j;

    lbl_1_bss_7830 = 0;
    fn_1_C1E8(com, 100);
    fn_1_C1E8(com, 101);
    for (i = 0; i < lbl_1_bss_7830; i++) {
        for (j = i + 1; j < lbl_1_bss_7830; j++) {
            a = lbl_1_bss_7844[i];
            b = lbl_1_bss_7844[j];
            if (a->unk004 != 100 && b->unk004 == 100) {
                M565_STAGEGRID *tc = lbl_1_bss_7844[i];
                s16 tk;
                lbl_1_bss_7844[i] = lbl_1_bss_7844[j];
                lbl_1_bss_7844[j] = tc;
                tk = lbl_1_bss_7832[i];
                lbl_1_bss_7832[i] = lbl_1_bss_7832[j];
                lbl_1_bss_7832[j] = tk;
            } else if (a->unk004 == b->unk004) {
                if (a->unk02C < b->unk02C) {
                    M565_STAGEGRID *tc = lbl_1_bss_7844[i];
                    s16 tk;
                    lbl_1_bss_7844[i] = lbl_1_bss_7844[j];
                    lbl_1_bss_7844[j] = tc;
                    tk = lbl_1_bss_7832[i];
                    lbl_1_bss_7832[i] = lbl_1_bss_7832[j];
                    lbl_1_bss_7832[j] = tk;
                } else if (a->unk02C == b->unk02C && lbl_1_bss_7832[i] > lbl_1_bss_7832[j]) {
                    M565_STAGEGRID *tc = lbl_1_bss_7844[i];
                    s16 tk;
                    lbl_1_bss_7844[i] = lbl_1_bss_7844[j];
                    lbl_1_bss_7844[j] = tc;
                    tk = lbl_1_bss_7832[i];
                    lbl_1_bss_7832[i] = lbl_1_bss_7832[j];
                    lbl_1_bss_7832[j] = tk;
                }
            }
        }
    }
    for (i = 0; i < lbl_1_bss_7830; i++) {
        out[i] = lbl_1_bss_7844[i];
    }
    *count = lbl_1_bss_7830;
}

/* 96 insns */
void fn_1_C1E8(M565_COM *com, s16 kind)
{
    M565_PLAYER *player = com->unk000;
    s32 dz;
    s32 dx;
    s16 x;
    s16 z;

    for (dz = 0; dz < 5 && lbl_1_bss_7830 < 9; dz++) {
        for (dx = 0; dx < 5 && lbl_1_bss_7830 < 9; dx++) {
            if (dz != 0) {
                x = player->unk088 + dx;
                z = player->unk08A - dz;
            }
            fn_1_C368(com, x, z, kind);
            if (dx != 0) {
                x = player->unk088 - dx;
                z = player->unk08A - dz;
                fn_1_C368(com, x, z, kind);
            }
        }
        for (dx = 0; dx < 5 && lbl_1_bss_7830 < 9; dx++) {
            if (dz != 0) {
                x = player->unk088 + dx;
                z = player->unk08A + dz;
                fn_1_C368(com, x, z, kind);
            }
            if (dx != 0) {
                x = player->unk088 - dx;
                z = player->unk08A + dz;
                fn_1_C368(com, x, z, kind);
            }
        }
    }
}

/* 177 insns */
/* Record the cell [row][col] as a candidate when its kind matches: appends to the
 * lbl_1_bss_7844 / lbl_1_bss_7832 list (at most 9) with its grid distance from the player. */
void fn_1_C368(M565_COM *com, s16 col, s16 row, s16 kind)
{
    M565_PLAYER *player;
    M565_OBJECT *obj;
    M565_STAGE *stage;
    M565_STAGEGRID *cell;
    double dist;

    player = com->unk000;
    obj = player->unk000;
    stage = &obj->unk2E4;
    if (col >= 0 && col < 10 && row >= 0 && row < 10) {
        cell = &stage->unk004[row][col];
        if (lbl_1_bss_7830 < 9 && cell->unk004 == kind) {
            lbl_1_bss_7844[lbl_1_bss_7830] = cell;
            dist = (player->unk088 - col) * (player->unk088 - col) + (player->unk08A - row) * (player->unk08A - row);
            lbl_1_bss_7832[lbl_1_bss_7830] = sqrt(dist);
            lbl_1_bss_7830++;
        }
    }
}

/* 231 insns */
/* The nearest standable cell (kind 100/101) in the player's facing direction, fanning
 * out +-4 of the 8 directions, first one step away, then two; NULL if none. */
void fn_1_C62C(M565_COM *com, M565_STAGEGRID **out)
{
    M565_PLAYER *player;
    M565_OBJECT *obj;
    M565_STAGE *stage;
    s32 found;
    s16 d;
    s32 i;
    s16 col;
    s16 row;
    M565_STAGEGRID *cell;
    s16 dx;
    s16 dz;
    s16 dir;

    player = com->unk000;
    obj = player->unk000;
    stage = &obj->unk2E4;
    fn_1_CBB4(player->unk078->y, &dir);
    found = 0;
    for (i = 0; i < 5; i++) {
        d = (dir + i) % 8;
        fn_1_CAD8(d, &dx, &dz);
        col = player->unk088 + dx;
        row = player->unk08A + dz;
        if (col >= 0 && col < 10 && row >= 0 && row < 10) {
            cell = &stage->unk004[row][col];
            if (cell->unk004 == 100 || cell->unk004 == 101) {
                *out = cell;
                found = 1;
                return;
            }
        }
        d = (dir - i) % 8;
        fn_1_CAD8(d, &dx, &dz);
        col = player->unk088 + dx;
        row = player->unk08A + dz;
        if (col >= 0 && col < 10 && row >= 0 && row < 10) {
            cell = &stage->unk004[row][col];
            if (cell->unk004 == 100 || cell->unk004 == 101) {
                *out = cell;
                found = 1;
                return;
            }
        }
    }
    for (i = 0; i < 5 && !found; i++) {
        d = (dir + i) % 8;
        fn_1_CAD8(d, &dx, &dz);
        col = player->unk088 + dx * 2;
        row = player->unk08A + dz * 2;
        if (col >= 0 && col < 10 && row >= 0 && row < 10) {
            cell = &stage->unk004[row][col];
            if (cell->unk004 == 100 || cell->unk004 == 101) {
                *out = cell;
                found = 1;
                return;
            }
        }
        d = (dir - i) % 8;
        fn_1_CAD8(d, &dx, &dz);
        col = player->unk088 + dx * 2;
        row = player->unk08A + dz * 2;
        if (col >= 0 && col < 10 && row >= 0 && row < 10) {
            cell = &stage->unk004[row][col];
            if (cell->unk004 == 100 || cell->unk004 == 101) {
                *out = cell;
                found = 1;
                return;
            }
        }
    }
    *out = NULL;
}

/* 68 insns */
/* (dx, dz) step -> direction 0..7 (8 = none); inverse of fn_1_CAD8. No caller in m565. */
void fn_1_C9C8(s16 dx, s16 dz, s16 *dir)
{
    *dir = 8;
    if (dz == 1) {
        switch (dx) {
            case -1:
                *dir = 5;
                break;
            case 0:
                *dir = 4;
                break;
            case 1:
                *dir = 3;
                break;
        }
    }
    else if (dz == -1) {
        switch (dx) {
            case -1:
                *dir = 7;
                break;
            case 0:
                *dir = 0;
                break;
            case 1:
                *dir = 1;
                break;
        }
    }
    else if (dz == 0) {
        switch (dx) {
            case -1:
                *dir = 6;
                break;
            case 0:
                *dir = 8;
                break;
            case 1:
                *dir = 2;
                break;
        }
    }
}

/* 55 insns */
/* direction -7..7 (negative wraps: dir and dir - 8 agree) -> grid step (dx, dz) */
void fn_1_CAD8(s16 dir, s16 *dx, s16 *dz)
{
    switch (dir) {
        case 0:
            *dx = 0;
            *dz = -1;
            break;
        case 1:
        case -7:
            *dx = 1;
            *dz = -1;
            break;
        case 2:
        case -6:
            *dx = 1;
            *dz = 0;
            break;
        case 3:
        case -5:
            *dx = 1;
            *dz = 1;
            break;
        case 4:
        case -4:
            *dx = 0;
            *dz = 1;
            break;
        case 5:
        case -3:
            *dx = -1;
            *dz = 1;
            break;
        case 6:
        case -2:
            *dx = -1;
            *dz = 0;
            break;
        case 7:
        case -1:
            *dx = -1;
            *dz = -1;
            break;
        default:
            *dx = 0;
            *dz = 0;
            break;
    }
}

/* 137 insns */
/* facing angle (degrees, -180..180) -> direction 0..7 in 45-degree sectors */
void fn_1_CBB4(float rot, s16 *dir)
{
    float angle;
    float step;

    step = 45.0f;
    angle = rot;

    *dir = 8;
    if (angle < 0.5f * step && angle > 0.5f * -step) {
        *dir = 4;
    }
    else if (angle <= 0.5f * -step && angle > 1.5f * -step) {
        *dir = 5;
    }
    else if (angle <= 1.5f * -step && angle > 2.5f * -step) {
        *dir = 6;
    }
    else if (angle <= 2.5f * -step && angle > 3.5f * -step) {
        *dir = 7;
    }
    else if (angle < 1.5f * step && angle >= 0.5f * step) {
        *dir = 3;
    }
    else if (angle < 2.5f * step && angle >= 1.5f * step) {
        *dir = 2;
    }
    else if (angle < 3.5f * step && angle >= 2.5f * step) {
        *dir = 1;
    }
    else {
        *dir = 0;
    }
}

/* 36 insns */
/* another player standing on cell, or NULL */
M565_PLAYER *fn_1_CDD8(M565_COM *com, M565_STAGEGRID *cell)
{
    M565_PLAYER *player;
    M565_OBJECT *obj;
    s32 i;
    M565_PLAYER *other;

    player = com->unk000;
    obj = player->unk000;
    for (i = 0; i < 4; i++) {
        other = &obj->unk008[i];
        if (other != player && cell->unk00E == other->unk088 && cell->unk010 == other->unk08A) {
            return other;
        }
    }
    return NULL;
}

static inline HuVecF fn_1_VecZero(void)
{
    HuVecF v = { 0.0f, 0.0f, 0.0f };
    return v;
}

#define COM_ABS(x) ((x) >= 0 ? (x) : -(x))
#define COM_SIGN(x) ((x) < 0 ? -1 : 1)
#define COM_GOALMAX 10
#define COM_CLAMP(x, lo, hi) ((x) > (hi) ? (hi) : ((x) < (lo) ? (lo) : (x)))
#define COM_STANDABLE(cell) ((cell)->unk004 == 100 || (cell)->unk004 == 101)
#define COM_INGRID(col, row) ((col) >= 0 && (col) < 10 && (row) >= 0 && (row) < 10)

/* 1459 insns */
/* One frame of COM movement toward the goal cell (unk022, unk024): walk (state 0), jump
 * (states 1/2, set up by fn_1_E714), then the stick output. Returns 1 when it has
 * arrived or cannot go further. */
s32 fn_1_CE68(M565_COM *com)
{
    HuVecF toOther;
    HuVecF stick;
    HuVecF toTarget;
    HuVecF span;
    M565_OBJECT *obj;
    M565_STAGEGRID *cellA;
    M565_STAGEGRID *cellB;
    float toLen;
    M565_PLAYER *player;
    M565_STAGE *stage;
    M565_STAGEGRID *cur;
    M565_STAGEGRID *goal;
    M565_STAGEGRID *next;
    s16 dx;
    s16 dz;
    s16 sx;
    s16 sz;
    s32 done;
    float scale;
    float spanLen;
    float range;

    player = com->unk000;
    obj = player->unk000;
    stage = &obj->unk2E4;
    if (!COM_INGRID(com->unk022, com->unk024)) {
        /* retail clamps to 0..10 (row from the column value, kept): [10] is past the grid.
         * Host: clamp to 9 so `goal` stays inside stage->unk004. */
        com->unk022 = COM_CLAMP(com->unk022, 0, COM_GOALMAX);
        com->unk024 = COM_CLAMP(com->unk022, 0, COM_GOALMAX);
    }
    cur = &stage->unk004[player->unk08A][player->unk088];
    goal = &stage->unk004[com->unk024][com->unk022];
    dx = com->unk022 - player->unk088;
    dz = com->unk024 - player->unk08A;
    done = 0;
    sx = sz = 0;
    stick = (HuVecF){ 0.0f, 0.0f, 0.0f };
    switch (com->unk018) {
        case 0:
            if (dx == 0 && dz == 0) {
                done = 1;
                break;
            }
            if (COM_ABS(dx) && COM_ABS(dz)) {
                sx = COM_SIGN(dx);
                sz = COM_SIGN(dz);
            }
            else if (COM_ABS(dx) > COM_ABS(dz)) {
                sx = COM_SIGN(dx);
            }
            else {
                sz = COM_SIGN(dz);
            }
            if (goal->unk034 != 0 && cur->unk034 == 0 && COM_STANDABLE(cur)) {
                if (sqrt(dx * dx + dz * dz) <= 1.0) {
                    done = 1;
                    break;
                }
            }
            if (!COM_STANDABLE(cur)) {
                fn_1_C62C(com, &cellA);
                if (cellA) {
                    if (player->unk074->y < -3.0f) {
                        fn_1_E714(com, cellA, 1123);
                    }
                    else {
                        fn_1_E534(com, cellA, &stick, 1125);
                    }
                }
            }
            if (COM_INGRID(player->unk088 + sx, player->unk08A + sz)) {
                next = &stage->unk004[player->unk08A + sz][player->unk088 + sx];
                if (COM_STANDABLE(next)) {
                    if (COM_ABS(sx) && COM_ABS(sz)) {
                        cellA = &stage->unk004[player->unk08A][player->unk088 + sx];
                        cellB = &stage->unk004[player->unk08A + sz][player->unk088];
                        if (!COM_STANDABLE(cellA) && !COM_STANDABLE(cellB)) {
                            if (player->unk004->mode == 0) {
                                fn_1_E714(com, next, 1145);
                            }
                            else {
                                done = 1;
                            }
                        }
                        else if (!COM_STANDABLE(cellA) && COM_STANDABLE(cellB)) {
                            fn_1_E534(com, cellB, &stick, 1153);
                        }
                        else if (COM_STANDABLE(cellA) && !COM_STANDABLE(cellB)) {
                            fn_1_E534(com, cellA, &stick, 1156);
                        }
                        else {
                            fn_1_E534(com, next, &stick, 1161);
                        }
                    }
                    else {
                        fn_1_E534(com, next, &stick, 1167);
                    }
                    break;
                }
                if (COM_ABS(sx) == COM_ABS(sz) && sx != 0 && sz != 0) {
                    if (COM_INGRID(player->unk088 + sx, player->unk08A)) {
                        next = &stage->unk004[player->unk08A][player->unk088 + sx];
                        if (COM_STANDABLE(next)) {
                            fn_1_E534(com, next, &stick, 1180);
                            break;
                        }
                    }
                    if (COM_INGRID(player->unk088, player->unk08A + sz)) {
                        next = &stage->unk004[player->unk08A + sz][player->unk088];
                        if (COM_STANDABLE(next)) {
                            fn_1_E534(com, next, &stick, 1188);
                            break;
                        }
                    }
                }
                if (COM_INGRID(player->unk088 + sx * 2, player->unk08A + sz * 2) && next->unk004 != 0) {
                    next = &stage->unk004[player->unk08A + sz * 2][player->unk088 + sx * 2];
                    if (COM_STANDABLE(next) && player->unk004->mode == 0) {
                        fn_1_E714(com, next, 1200);
                        break;
                    }
                }
                if (COM_ABS(sx) == COM_ABS(sz) && sx != 0 && sz != 0 && COM_ABS(dx) >= 2) {
                    if (COM_INGRID(player->unk088 + sx * 2, player->unk08A)) {
                        next = &stage->unk004[player->unk08A][player->unk088 + sx * 2];
                        if (COM_STANDABLE(next) && player->unk004->mode == 0) {
                            fn_1_E714(com, next, 1212);
                            break;
                        }
                    }
                    if (COM_INGRID(player->unk088, player->unk08A + sz * 2) && COM_ABS(dz) >= 2) {
                        next = &stage->unk004[player->unk08A + sz * 2][player->unk088];
                        if (COM_STANDABLE(next) && player->unk004->mode == 0) {
                            fn_1_E714(com, next, 1220);
                            break;
                        }
                    }
                }
                if (cur->unk004 == 102 && next->unk004 != 1 && next->unk004 != 0) {
                    if (player->unk074->y < 30.0f && player->unk004->mode == 0) {
                        fn_1_E714(com, next, 1229);
                    }
                    else {
                        fn_1_E534(com, next, &stick, 1231);
                    }
                    break;
                }
                done = 1;
                break;
            }
            done = 1;
            break;
        case 1:
            cellA = &stage->unk004[player->unk08A][player->unk088];
            cellB = &stage->unk004[com->unk028][com->unk026];
            PSVECSubtract(&cellB->unk018, player->unk074, &toTarget);
            PSVECSubtract(&cellB->unk018, &cellA->unk018, &span);
            toTarget.y = span.y = 0.0f;
            toLen = PSVECMag(&toTarget);
            spanLen = PSVECMag(&span);
            if (toLen < spanLen || !COM_STANDABLE(cellA)) {
                com->unk044 |= PAD_BUTTON_A;
                com->unk018 = 2;
            }
            next = &stage->unk004[com->unk028][com->unk026];
            fn_1_E534(com, next, &stick, 1265);
            break;
        case 2:
            cellA = &stage->unk004[com->unk028][com->unk026];
            if (cellA->unk004 == 1 || cellA->unk004 == 0 || cellA->unk004 == 102) {
                if (COM_STANDABLE(cur)) {
                    com->unk026 = player->unk088;
                    com->unk028 = player->unk08A;
                }
                else {
                    fn_1_C62C(com, &cellB);
                    if (cellB) {
                        com->unk026 = cellB->unk00E;
                        com->unk028 = cellB->unk010;
                    }
                }
            }
            if ((s16)player->unk088 == com->unk026 && (s16)player->unk08A == com->unk028 && player->unk08C < 30.0f
                && player->unk004->mode != 1) {
                com->unk018 = 0;
                break;
            }
            if (com->unk02C == 0) {
                if (player->unk004->mode == 1) {
                    com->unk02C = 1;
                }
                else {
                    com->unk044 |= PAD_BUTTON_A;
                }
            }
            next = &stage->unk004[com->unk028][com->unk026];
            fn_1_E534(com, next, &stick, 1310);
            if ((s16)com->unk026 == player->unk088 && (s16)com->unk028 == player->unk08A) {
                scale = player->unk08C / 30.0f;
                scale = COM_CLAMP(scale, 0.0f, 1.0f);
            }
            else {
                scale = 1.0f;
            }
            stick.x *= scale;
            stick.y *= scale;
            com->unk050 |= PAD_BUTTON_A;
            if (player->unk080) {
                range = com->unk008 == 0 ? 150.0f : (com->unk008 == 1 ? 140.0f : 120.0f);
                if (player->unk084 < range) {
                    if (com->unk012-- <= 0) {
                        com->unk044 |= PAD_BUTTON_B;
                        com->unk012 = lbl_1_data_B28[com->unk008] + frand() % (lbl_1_data_B28[com->unk008] / 2);
                    }
                }
            }
            break;
    }
    if (dx == 0 && dz == 0 && player->unk08C < 50.0f) {
        done = 1;
    }
    if (com->unk040 != 0 && player->unk080 && player->unk080->unk090 == 0) {
        PSVECSubtract(player->unk080->unk074, player->unk074, &toOther);
        toOther.y = 0.0f;
        if (toOther.x || toOther.z) {
            PSVECNormalize(&toOther, &toOther);
        }
        stick.x = toOther.x;
        stick.y = toOther.z;
        scale = player->unk084 / 30.0f;
        scale = COM_CLAMP(scale, 0.0f, 1.0f);
        stick.x *= scale;
        stick.y *= scale;
    }
    scale = com->unk008 == 0 ? 1.0f : (com->unk008 == 1 ? 1.0f : (com->unk008 == 2 ? 0.9f : 0.8f));
    scale = com->unk018 == 0 ? scale : 1.0f;
    stick.x *= scale;
    stick.y *= scale;
    com->unk038 = 0.8f * com->unk038 + 0.2f * stick.x;
    com->unk03C = 0.8f * com->unk03C + 0.2f * stick.y;
    com->unk048 = (s8)(56.0f * com->unk038);
    com->unk04C = (s8)(56.0f * -com->unk03C);
    com->unk040 = 0;
    return done;
}

/* 120 insns */
/* Walk toward cell: stick = XZ unit vector from the player to the cell centre. Special
 * case at the player's row 8 between columns 4 and 5: cut through row 7 if both of its
 * cells stand, otherwise jump (fn_1_E714) when walking. Returns 1. */
s32 fn_1_E534(M565_COM *com, M565_STAGEGRID *cell, HuVecF *stick, s32 line)
{
    HuVecF dir;
    M565_PLAYER *player;
    M565_OBJECT *obj;
    M565_STAGE *stage;
    M565_STAGEGRID *target;
    M565_STAGEGRID *c74;
    M565_STAGEGRID *c75;

    player = com->unk000;
    obj = player->unk000;
    stage = &obj->unk2E4;
    target = cell;
    com->unk034 = line;
    c74 = &stage->unk004[7][4];
    c75 = &stage->unk004[7][5];
    if (player->unk08A == 8 && player->unk088 == 4 && cell->unk010 == 8 && cell->unk00E == 5) {
        if (COM_STANDABLE(c74) && COM_STANDABLE(c75)) {
            target = c74;
        }
        else if (player->unk004->mode == 0) {
            fn_1_E714(com, cell, 1407);
        }
    }
    else if (player->unk08A == 8 && player->unk088 == 5 && cell->unk010 == 8 && cell->unk00E == 4) {
        if (COM_STANDABLE(c74) && COM_STANDABLE(c75)) {
            target = c75;
        }
        else if (player->unk004->mode == 0) {
            fn_1_E714(com, cell, 1416);
        }
    }
    PSVECSubtract(&target->unk018, player->unk074, &dir);
    dir.y = 0.0f;
    if (dir.x || dir.z) {
        PSVECNormalize(&dir, &dir);
    }
    stick->x = dir.x;
    stick->y = dir.z;
    return 1;
}

/* 11 insns */
/* start a jump to cell (state 1). Returns 1. */
s32 fn_1_E714(M565_COM *com, M565_STAGEGRID *cell, s32 line)
{
    com->unk026 = cell->unk00E;
    com->unk028 = cell->unk010;
    com->unk018 = 1;
    com->unk02C = 0;
    com->unk030 = line;
    return 1;
}

