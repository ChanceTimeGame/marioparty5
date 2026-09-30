/*
 * m502dll block.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/block.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"


int rand8(void);

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x208 */ /* float lbl_1_rodata_208 = 300.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 0.0f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 480.0f; */
/* 0x214 */ /* float lbl_1_rodata_214 = -300.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 2700.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 600.0f; */
/* 0x220 */ /* double lbl_1_rodata_220 = 4503601774854144; */
/* 0x228 */ /* float lbl_1_rodata_228 = -2700.0f; */
/* 0x22C */ /* float lbl_1_rodata_22C = -3300.0f; */
/* 0x230 */ /* float lbl_1_rodata_230 = -6000.0f; */
/* 0x234 */ /* float lbl_1_rodata_234 = -6600.0f; */
/* 0x238 */ /* float lbl_1_rodata_238 = -9300.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = -9900.0f; */
/* 0x240 */ /* float lbl_1_rodata_240 = 3300.0f; */
/* 0x244 */ /* s16 lbl_1_rodata_244[18] = { 0x0000, 0x0001, 0x0002, 0x0000, 0x0002, 0x0001, 0x0001, 0x0000, 0x0002, 0x0001, 0x0002, 0x0000, 0x0002, 0x0000, 0x0001, 0x0002, 0x0001, 0x0000 }; */
/* 0x268 */ /* s16 lbl_1_rodata_268[4] = { 0x0000, 0x0000, 0x0000, 0x0000 }; */
/* 0x270 */ /* u8 lbl_1_rodata_270[1] = { 0x40 }; */
/* 0x271 */ /* TODO lbl_1_rodata_271 .rodata size=0x2 (0 entries):  */
/* 0x273 */ /* u8 lbl_1_rodata_273[2] = { 0x01, 0x02, 0x03, 0x01, 0x02, 0x04, 0x01, 0x02, 0x04 }; */
/* 0x27C */ /* s16 lbl_1_rodata_27C[6] = { 0x0000, 0x0001, 0x0002, 0x0001, 0x0000, 0x0002 }; */
/* 0x288 */ /* s16 lbl_1_rodata_288[10] = { 0x000A, 0x0009, 0x0001, 0x0002, 0x0003, 0x0004, 0x0005, 0x000A, 0x000A, 0x0000 }; */
/* 0x29C */ /* s32 lbl_1_rodata_29C[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2A8 */ /* s32 lbl_1_rodata_2A8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2B4 */ /* s32 lbl_1_rodata_2B4[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2C0 */ /* s32 lbl_1_rodata_2C0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = 0.4f; */
/* 0x2D0 */ /* float lbl_1_rodata_2D0 = 1.0f; */
/* 0x2D4 */ /* float lbl_1_rodata_2D4 = 0.3f; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 0.7f; */
/* 0x2DC */ /* float lbl_1_rodata_2DC = 255.0f; */
/* 0x2E0 */ /* float lbl_1_rodata_2E0 = 0.2f; */
/* 0x2E4 */ /* float lbl_1_rodata_2E4 = 0.6f; */
/* 0x2E8 */ /* float lbl_1_rodata_2E8 = -9360.0f; */
/* 0x2EC */ /* float lbl_1_rodata_2EC = 0.5f; */
/* 0x2F0 */ /* float lbl_1_rodata_2F0 = 0.25f; */
/* 0x2F4 */ /* float lbl_1_rodata_2F4 = 0.15f; */
/* 0x2F8 */ /* float lbl_1_rodata_2F8 = 6600.0f; */
/* 0x2FC */ /* float lbl_1_rodata_2FC = 0.1f; */
/* 0x300 */ /* float lbl_1_rodata_300 = 30.000002f; */
/* 0x304 */ /* float lbl_1_rodata_304 = 15.000001f; */
/* 0x308 */ /* float lbl_1_rodata_308[2] = { 25.0f, 0.0f }; */

/* --- .data --- */
/* 0xE98 */ HU3DMODELHOOK lbl_1_data_E98[4] = { fn_1_8904, fn_1_8940, fn_1_897C, fn_1_89B8 };
/* 0xEA8 */ M502_BLOCK *lbl_1_data_EA8[4] = { NULL, NULL, NULL, NULL };
/* 0xEB8 */ s32 lbl_1_data_EB8 = 1;
/* 0xEBC */ HuVecF lbl_1_data_EBC[8] = { { -0.8f, 1.6f, 0.0f }, { -0.2f, 1.6f, 0.0f }, { 0.8f, 1.6f, 0.0f }, { -0.8f, 1.6f, 0.0f }, { -0.4f, 1.6f, 0.0f }, { -0.2f, 1.6f, 0.0f }, { 0.4f, 1.6f, 0.0f }, { 0.8f, 1.6f, 0.0f } };
/* 0xF1C */ HuVecF lbl_1_data_F1C[8] = { { -1.6f, 2.4f, 0.0f }, { -0.1f, 2.8f, 0.0f }, { 1.6f, 2.4f, 0.0f }, { -1.6f, -2.8f, 0.0f }, { -0.8f, 2.4f, 0.0f }, { -1.2f, -2.8f, 0.0f }, { 0.8f, 2.4f, 0.0f }, { 1.2f, 2.8f, 0.0f } };
/* 0xF7C */ HuVecF lbl_1_data_F7C[8] = { { -1.6f, 3.2f, 0.0f }, { -0.1f, 3.6f, 0.0f }, { 1.6f, 3.2f, 0.0f }, { -1.6f, 3.6f, 0.0f }, { -1.2f, -3.2f, 0.0f }, { -1.8f, 3.6f, 0.0f }, { 1.2f, -3.2f, 0.0f }, { 1.8f, 3.6f, 0.0f } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x504C */ float lbl_1_bss_504C;
/* 0x5048 */ s32 lbl_1_bss_5048;

/* --- functions (reference order) --- */
/* 69 insns */
void fn_1_6664(M502_BLOCK *block, s32 idx, M502_PLAYER *player)
{
    s32 i;
    HU3DMODELID modelId;

    memset(block, 0, sizeof(M502_BLOCK));
    block->unk000 = player;
    lbl_1_data_EA8[idx] = block;
    for (i = 0; i < 3; i++) {
        fn_1_8438(&block->unkB68[i], block);
    }
    for (i = 0; i < 2; i++) {
        fn_1_8FDC(&block->unkF1C[i], block);
    }
    block->unkF4C = modelId = Hu3DHookFuncCreate((HU3DMODELHOOK)lbl_1_data_E98[idx]);
    Hu3DModelCameraSet(modelId, lbl_1_data_B60[idx]);
    lbl_1_data_EB8 = 1;
}

/* 36 insns */
void fn_1_6778(M502_BLOCK *block)
{
    s32 i;

    Hu3DModelKill(block->unkF4C);
    for (i = 0; i < 3; i++) {
        fn_1_850C(&block->unkB68[i]);
    }
    for (i = 0; i < 2; i++) {
        fn_1_9028(&block->unkF1C[i]);
    }
    memset(block, 0, sizeof(M502_BLOCK));
}

/* 300 insns */
void fn_1_6808(M502_BLOCK *block)
{
    M502_PLAYER *player;
    M502_CHAR *chr;
    s32 i;
    s32 j;
    s32 k;
    s16 num;
    M502_BLOCKCELL *cell;
    HuVecF pos;
    HuVecF pos2;
    HuVecF pos2D;
    HuVecF pos2D2;

    player = block->unk000;
    chr = &player->unkF58;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 27; j++) {
            if (j % 3 == 0) {
                fn_1_6CFC(i, j / 3, 1, &pos);
                pos2 = pos;
                pos.y += 300.0f;
                pos2.y -= 300.0f;
                Hu3D3Dto2D(&pos, block->unk000->unk1048.unk004, &pos2D);
                Hu3D3Dto2D(&pos2, block->unk000->unk1048.unk004, &pos2D2);
                if (fn_1_6CB8(&pos2D) || fn_1_6CB8(&pos2D2)) {
                    block->unk004[i][j].unk008 = 1;
                    block->unk004[i][j + 1].unk008 = 1;
                    block->unk004[i][j + 2].unk008 = 1;
                }
                else {
                    block->unk004[i][j].unk008 = 0;
                    block->unk004[i][j + 1].unk008 = 0;
                    block->unk004[i][j + 2].unk008 = 0;
                }
            }
            cell = &block->unk004[i][j];
            if (cell->unk00E < 10000) {
                if (--cell->unk00E <= 0) {
                    cell->unk01C = (cell->unk01E == 2) ? 26 : 28;
                    cell->unk01C += (j / 3) % 2 - 12;
                    cell->unk01C += (i == 0) ? 12 : ((i == 1) ? 30 : 48);
                    cell->unk00E = 10000;
                    for (k = 0; k < 2; k++) {
                        if (block->unkF1C[k].unk004 == 0) {
                            fn_1_912C(&block->unkF1C[k], k, &cell->unk010);
                            break;
                        }
                    }
                }
            }
            if (cell->unk00C < 10000) {
                if (--cell->unk00C <= 0) {
                    num = chr->unk078 - cell->unk020;
                    num = (num > 3) ? 3 : ((num < 1) ? 1 : num);
                    fn_1_83AC(block, cell->unk004, i, &cell->unk010, num);
                    if (cell->unk004 != 2) {
                        fn_1_218(fn_1_198(0x62D), (chr->unk010 == 0) ? 40 : ((chr->unk010 == 1) ? 56 : ((chr->unk010 == 2) ? 72 : 88)));
                    }
                    else {
                        fn_1_218(fn_1_198(0x62E), (chr->unk010 == 0) ? 40 : ((chr->unk010 == 1) ? 56 : ((chr->unk010 == 2) ? 72 : 88)));
                    }
                    fn_1_8324(cell);
                    chr->unk070 = 2;
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        fn_1_8594(&block->unkB68[i]);
    }
    for (i = 0; i < 2; i++) {
        fn_1_9058(&block->unkF1C[i]);
    }
}

/* 17 insns */
s32 fn_1_6CB8(HuVecF *pos)
{
    if (pos->y < 0.0f || pos->y >= 480.0f) {
        return 0;
    }
    return 1;
}

/* 72 insns */
void fn_1_6CFC(s16 row, s16 col, s16 x, HuVecF *out)
{
    out->x = -300.0f + 300.0f * x;
    out->y = -(300.0f * col + (2700.0f * row + 600.0f * row));
    out->z = 0.0f;
}

/* 165 insns */
void fn_1_6E1C(HuVecF *pos, s16 *row, s16 *col, s16 *x)
{
    float px;
    float py;
    float pz;
    s16 r;
    s16 c;
    s16 n;

    px = pos->x;
    py = pos->y;
    pz = pos->z;
    r = 0;
    c = 0;
    n = 0;
    r = (py > 0.0f) ? 6 : ((py > -2700.0f) ? 0 : ((py > -3300.0f) ? 3 : ((py > -6000.0f) ? 1 : ((py > -6600.0f) ? 4 : ((py > -9300.0f) ? 2 : ((py > -9900.0f) ? 5 : 7))))));
    n = (300.0f + px) / 300.0f;
    if (r < 3) {
        c = (py + 3300.0f * r) / -300.0f;
        if (c >= 9) {
            c = 0;
            r = (r == 0) ? 3 : ((r == 3) ? 1 : ((r == 1) ? 4 : ((r == 4) ? 2 : ((r == 2) ? 5 : 6))));
        }
    }
    *row = r;
    *col = c;
    *x = n;
}

/* 120 insns */
s32 fn_1_70B0(M502_BLOCK *block, s16 row, s16 col, s16 x, s16 num)
{
    s16 idx;
    s32 result;
    s32 hit;
    s32 i;
    u16 kind;
    M502_BLOCKCELL *cell;

    if (row < 0 || row > 2) {
        return 0;
    }
    result = 0;
    hit = 0;
    for (i = 0; (s16)i < num; i++) {
        idx = x + (col + i) * 3;
        if (idx >= 27) {
            break;
        }
        cell = &block->unk004[row][idx];
        if (cell->unk004 != 0) {
            kind = cell->unk004;
            if (--cell->unk01E <= 0) {
                cell->unk00C = i * 11 + 3;
                cell->unk020 = i;
                hit++;
                result = 1;
            }
            if (kind == 2) {
                if (cell->unk01E > 0) {
                    cell->unk00E = i * 11 + 3;
                    omVibrate(block->unk000->unk004, 20, 6, 6);
                }
                break;
            }
        }
    }
    if ((s16)hit != 0) {
        if ((s16)hit == 1) {
            omVibrate(block->unk000->unk004, 20, 6, 6);
        }
        else if ((s16)hit == 2) {
            omVibrate(block->unk000->unk004, 25, 4, 2);
        }
        else if ((s16)hit == 3) {
            omVibrate(block->unk000->unk004, 30, 12, 0);
        }
    }
    return result;
}

/* 51 insns */
void fn_1_7290(M502_BLOCK *dst, M502_BLOCK *src)
{
    s32 i;
    s32 j;
    M502_BLOCKCELL *d;
    M502_BLOCKCELL *s;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 27; j++) {
            d = &dst->unk004[i][j];
            s = &src->unk004[i][j];
            d->unk004 = s->unk004;
            d->unk006 = s->unk006;
            d->unk008 = s->unk008;
            d->unk010 = s->unk010;
            d->unk01C = s->unk01C;
            d->unk01E = s->unk01E;
            d->unk00C = s->unk00C;
            d->unk00E = s->unk00E;
        }
    }
}

/* 123 insns */
void fn_1_735C(M502_BLOCK *block)
{
    s16 used[3];
    s16 order[6][3] = { { 0, 1, 2 }, { 0, 2, 1 }, { 1, 0, 2 }, { 1, 2, 0 }, { 2, 0, 1 }, { 2, 1, 0 } };
    s16 i;
    s16 j;
    s16 pat;

    for (i = 0; i < 3; i++) {
        pat = rand8() % 6;
        used[i] = pat;
        if (i != 0 && used[i] == used[i - 1]) {
            pat = (pat + 3) % 6;
            used[i] = pat;
        }
        for (j = 0; j < 3; j++) {
            fn_1_7548(block, i, j, order[pat][j]);
        }
    }
    fn_1_7BFC(block);
    fn_1_7ECC(block);
}

/* 429 insns */
void fn_1_7548(M502_BLOCK *block, s16 row, s16 col, s16 pattern)
{
    s16 sel[4] = { 0, 0, 0, 0 };
    u8 unused;
    u8 unusedTbl[3] = { 64, 56, 113 };
    u8 selNum[3][3] = { { 1, 2, 3 }, { 1, 2, 4 }, { 1, 2, 4 } };
    s16 i;
    s16 j;
    s16 n;
    u8 rnd;

    unused = unusedTbl[pattern];
    for (i = 0; i < 9; i++) {
        if (i >= 7 && row == 2) {
            block->unk004[row][col + i * 3].unk004 = 2;
            block->unk004[row][col + i * 3].unk01E = 3;
        }
        else {
            block->unk004[row][col + i * 3].unk004 = 1;
            block->unk004[row][col + i * 3].unk01E = 1;
        }
    }
    switch (row) {
        case 0:
            switch (pattern) {
                case 0:
                    rnd = rand8() % 8;
                    sel[0] = rnd + 1;
                    break;
                case 1:
                    rnd = rand8() % 4;
                    sel[0] = rnd + 1;
                    rnd = rand8() % 4;
                    sel[1] = rnd + 5;
                    break;
                case 2:
                    sel[0] = 1;
                    rnd = rand8() % 3;
                    sel[1] = rnd + 2;
                    rnd = rand8() % 4;
                    sel[2] = rnd + 5;
                    break;
            }
            break;
        case 1:
            switch (pattern) {
                case 0:
                    rnd = rand8() % 9;
                    sel[0] = rnd;
                    break;
                case 1:
                    sel[0] = rand8() % 9;
                    do {
                        rnd = rand8() % 9;
                    } while (sel[0] == rnd);
                    sel[1] = rnd;
                    break;
                case 2:
                    sel[0] = rand8() % 9;
                    i = 1;
                    do {
                        rnd = rand8() % 9;
                        for (n = 0, j = 0; n < i; n++) {
                            if (sel[0] != rnd) {
                                j++;
                            }
                        }
                        if (j == i) {
                            sel[i] = rnd;
                            i++;
                        }
                    } while (i != 4);
                    break;
            }
            break;
        case 2:
            switch (pattern) {
                case 0:
                    rnd = rand8() % 10;
                    if (rnd > 1) {
                        rnd = rand8() % 3;
                    }
                    else {
                        rnd = rand8() % 4 + 3;
                    }
                    sel[0] = rnd;
                    break;
                case 1:
                    rnd = rand8() % 3 + 2;
                    sel[0] = rnd;
                    rnd = rand8() % 2 + 5;
                    sel[1] = rnd;
                    break;
                case 2:
                    rnd = rand8() % 3;
                    sel[0] = rnd;
                    rnd = rand8() % 4;
                    for (i = 0, n = 0; i < 4; i++) {
                        if (rnd != i) {
                            sel[n + 1] = i + 3;
                            n++;
                        }
                    }
                    break;
            }
            break;
    }
    for (i = 0; i < selNum[row][pattern]; i++) {
        block->unk004[row][col + sel[i] * 3].unk004 = 2;
        block->unk004[row][col + sel[i] * 3].unk01E = 3;
    }
}


/* 180 insns */
void fn_1_7BFC(M502_BLOCK *block)
{
    s32 hard[3][2];
    u8 flag[2];
    u16 kindTbl[2][3] = { { 0, 1, 2 }, { 1, 0, 2 } };
    s16 unusedTbl[9] = { 10, 9, 1, 2, 3, 4, 5, 10, 10 };
    s32 i;
    s32 row;
    s32 k;
    s32 cnt;
    u16 kind;

    flag[0] = rand8() % 2;
    flag[1] = rand8() % 2;
    for (i = 0; i < 3; i++) {
        hard[i][0] = hard[i][1] = 0;
    }
    for (row = 0; row < 3; row++, flag[1] ^= 1) {
        for (i = 0; i < 9; i++) {
            kind = kindTbl[flag[1]][i % 3];
            cnt = 0;
            for (k = 0; k < 3; k++) {
                if (block->unk004[row][i * 3 + k].unk004 != 2) {
                    block->unk004[row][i * 3 + k].unk006 = kind;
                    if (i != 0) {
                        cnt++;
                    }
                }
                else {
                    block->unk004[row][i * 3 + k].unk006 = 4;
                }
            }
            if (cnt == 3 && hard[row][0] == 0) {
                hard[row][0] = row + 1;
                hard[row][1] = i;
            }
        }
    }
    for (row = 0; row < 3; row++) {
        if (hard[row][0] != 0) {
            for (i = 0; i < 3; i++) {
                block->unk004[hard[row][0] - 1][hard[row][1] * 3 + i].unk006 = 3;
            }
        }
    }
}

/* 241 insns */
void fn_1_7ECC(M502_BLOCK *block)
{
    s32 row;
    s32 col;
    s32 idx;
    s32 base;
    HuVecF pos;

    for (row = 0; row < 3; row++) {
        if (row == 0) {
            base = 12;
        }
        else if (row == 1) {
            base = 30;
        }
        else {
            base = 48;
        }
        for (col = 0; col < 27; col++) {
            idx = 0;
            switch (block->unk004[row][col].unk006) {
                case 0:
                    idx = col % 6 / 3;
                    break;
                case 1:
                    idx = col % 6 / 3 + 2;
                    break;
                case 2:
                    idx = col % 6 / 3 + 4;
                    break;
                case 3:
                    idx = col % 3 + 6 + (col % 6 / 3) * 3;
                    break;
                case 4:
                    idx = col % 6 / 3 + 12;
                    break;
            }
            idx += base;
            block->unk004[row][col].unk01C = idx;
            fn_1_6CFC(row, col / 3, col % 3, &pos);
            block->unk004[row][col].unk010 = pos;
            block->unk004[row][col].unk008 = 1;
            block->unk004[row][col].unk00C = 10000;
            block->unk004[row][col].unk00E = 10000;
        }
    }
}

/* 37 insns */
void fn_1_8290(M502_BLOCK *block)
{
    s32 row;
    s32 col;

    for (row = 0; row < 3; row++) {
        for (col = 0; col < 27; col++) {
            if (block->unk004[row][col].unk01C != 0) {
                fn_1_8324(&block->unk004[row][col]);
            }
        }
    }
}

/* 34 insns */
void fn_1_8324(M502_BLOCKCELL *cell)
{
    cell->unk004 = 0;
    cell->unk006 = 0;
    cell->unk008 = 0;
    cell->unk010 = (HuVecF) { 0.0f, 0.0f, 0.0f };
    cell->unk01C = 0;
    cell->unk01E = 0;
    cell->unk00C = 10000;
    cell->unk00E = 10000;
}

/* 35 insns */
void fn_1_83AC(M502_BLOCK *block, s16 type, s16 row, HuVecF *pos, u16 kind)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        if (block->unkB68[i].unk004 == 0) {
            fn_1_876C(&block->unkB68[i], type, row, pos, kind);
            break;
        }
    }
}

/* 53 insns */
void fn_1_8438(M502_BLOCKSHARD *shard, M502_BLOCK *block)
{
    M502_WORKMODEL *res = &block->unk000->unk000->unk01C;
    s32 i;

    memset(shard, 0, sizeof(M502_BLOCKSHARD));
    shard->unk000 = block;
    for (i = 0; i < 8; i++) {
        shard->unk12C[i] = 0;
        shard->unk00C[i] = (HuVecF) { 0.0f, 0.0f, 0.0f };
    }
}

/* 34 insns */
void fn_1_850C(M502_BLOCKSHARD *shard)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        if (shard->unk12C[i] != 0) {
            Hu3DModelKill(shard->unk12C[i]);
            shard->unk12C[i] = 0;
        }
    }
    memset(shard, 0, sizeof(M502_BLOCKSHARD));
}

/* 118 insns */
void fn_1_8594(M502_BLOCKSHARD *shard)
{
    s32 i;

    switch (shard->unk004) {
        case 0:
            break;
        case 1:
            for (i = 0; i < 8; i++) {
                shard->unk0CC[i].y -= 0.4f;
                PSVECAdd(&shard->unk06C[i], &shard->unk0CC[i], &shard->unk06C[i]);
                PSVECAdd(&shard->unk06C[i], &shard->unk00C[i], &shard->unk00C[i]);
            }
            if (shard->unk006++ > 60) {
                shard->unk004 = 2;
            }
            break;
        case 2:
            for (i = 0; i < 8; i++) {
                shard->unk00C[i] = (HuVecF) { 0.0f, 0.0f, 0.0f };
                shard->unk06C[i] = (HuVecF) { 0.0f, 0.0f, 0.0f };
                shard->unk12C[i] = 0;
            }
            shard->unk004 = 0;
            shard->unk006 = 0;
            shard->unk008 = 0;
            break;
    }
}

/* 102 insns */
void fn_1_876C(M502_BLOCKSHARD *shard, s16 type, s16 row, HuVecF *pos, u16 kind)
{
    s16 mdlIdx;
    M502_WORKMODEL *res = &shard->unk000->unk000->unk000->unk01C;
    s32 base;
    s32 i;

    if (type == 2) {
        base = row == 0 ? 90 : row == 1 ? 98 : 106;
    }
    else {
        base = row == 0 ? 66 : row == 1 ? 74 : 82;
    }
    for (i = 0; i < 8; i++) {
        shard->unk12C[i] = mdlIdx = base + i;
        shard->unk00C[i] = *pos;
        shard->unk0CC[i] = *(kind == 3 ? &lbl_1_data_F7C[i] : kind == 2 ? &lbl_1_data_F1C[i] : &lbl_1_data_EBC[i]);
        shard->unk008 = 1;
    }
    shard->unk004 = 1;
    shard->unk006 = 0;
}

/* 15 insns */
void fn_1_8904(HU3DMODEL *modelP, Mtx *mtx)
{
    fn_1_89F4(lbl_1_data_EA8[0], modelP, mtx);
}

/* 15 insns */
void fn_1_8940(HU3DMODEL *modelP, Mtx *mtx)
{
    fn_1_89F4(lbl_1_data_EA8[1], modelP, mtx);
}

/* 15 insns */
void fn_1_897C(HU3DMODEL *modelP, Mtx *mtx)
{
    fn_1_89F4(lbl_1_data_EA8[2], modelP, mtx);
}

/* 15 insns */
void fn_1_89B8(HU3DMODEL *modelP, Mtx *mtx)
{
    fn_1_89F4(lbl_1_data_EA8[3], modelP, mtx);
}

/* 252 insns */
void fn_1_89F4(M502_BLOCK *block, HU3DMODEL *modelP, Mtx *mtx)
{
    s32 playerNo;
    float scale;
    Mtx objMtx;
    M502_PLAYER *player = block->unk000;
    M502_WORK *work = player->unk000;
    M502_WORKMODEL *res = &player->unk000->unk01C;
    M502_LIGHT *light = &player->unk000->unk378;
    M502_STAGE *stage = &player->unkFD4;
    M502_LIGHT *light2;
    u8 col;
    float ambStage;
    float ambBlock;
    HU3DMODELID mdlId;
    s32 i;
    s32 j;
    M502_BLOCKCELL *cell;
    M502_BLOCKSHARD *shard;

    if (block) {
        playerNo = player->unk004;
        if (work->unk008 != 6) {
            Hu3DModelObjDrawInit();
            light2 = &player->unk000->unk378;
            scale = 1.0f;
            if (lbl_1_data_EB8) {
                fn_1_8DE4(block, &scale);
            }
            ambStage = 0.3f + 0.3f * scale;
            ambBlock = 0.7f + 0.3f * scale;
            col = 255.0f * (0.2f + 0.6f * scale);
            if (lbl_1_data_EB8) {
                Hu3DGLightColorSet(light2->unk004, col, col, col, col);
            }
            for (i = 0; i < 8; i++) {
                mdlId = res->unk000[stage->unk044[i]];
                if (lbl_1_data_EB8) {
                    Hu3DModelAmbSet(mdlId, ambStage, ambStage, ambStage);
                }
                MTXTrans(objMtx, 0.0f, 0.0f, 0.0f);
                MTXConcat(*mtx, objMtx, objMtx);
                Hu3DModelObjDraw(mdlId, stage->unk054[i], objMtx);
            }
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 27; j++) {
                    cell = &block->unk004[i][j];
                    if (cell->unk008 != 0 && cell->unk004 != 0) {
                        MTXTrans(objMtx, cell->unk010.x, cell->unk010.y, cell->unk010.z);
                        MTXConcat(*mtx, objMtx, objMtx);
                        mdlId = res->unk000[cell->unk01C];
                        if (lbl_1_data_EB8) {
                            Hu3DModelAmbSet(mdlId, ambBlock, ambBlock, ambBlock);
                        }
                        Hu3DModelObjDraw(mdlId, res->unk11C[cell->unk01C], objMtx);
                    }
                }
            }
            for (i = 0; i < 3; i++) {
                shard = &block->unkB68[i];
                if (shard->unk008 != 0) {
                    for (j = 0; j < 8; j++) {
                        MTXTrans(objMtx, shard->unk00C[j].x, shard->unk00C[j].y, shard->unk00C[j].z);
                        MTXConcat(*mtx, objMtx, objMtx);
                        mdlId = res->unk000[shard->unk12C[j]];
                        if (lbl_1_data_EB8) {
                            Hu3DModelAmbSet(mdlId, ambBlock, ambBlock, ambBlock);
                        }
                        Hu3DModelObjDraw(mdlId, res->unk11C[shard->unk12C[j]], objMtx);
                    }
                }
            }
            if (lbl_1_data_EB8) {
                Hu3DGLightColorSet(light->unk004, 255, 255, 255, 255);
            }
        }
    }
}

/* 72 insns */
void fn_1_8DE4(M502_BLOCK *block, float *out)
{
    M502_PLAYER *player = block->unk000;
    M502_CHAR *chr = &player->unkF58;
    float t;

    if (chr->unk01C->trans.y < lbl_1_bss_504C) {
        t = (chr->unk01C->trans.y - lbl_1_bss_504C) / (-9360.0f - lbl_1_bss_504C);
        t = t > 1.0f ? 1.0f : t < 0.0f ? 0.0f : t;
        t = 1.0f - t;
    }
    else {
        t = 1.0f;
    }
    *out = t;
}

/* 54 insns */
void fn_1_8F04(M502_BLOCK *block)
{
    M502_PLAYER *player = block->unk000;
    M502_WORKMODEL *res = &player->unk000->unk01C;
    M502_LIGHT *light = &player->unk000->unk378;
    M502_STAGE *stage = &player->unkFD4;
    s32 i;
    HU3DMODELID mdlId;

    for (i = 0; i < 8; i++) {
        mdlId = res->unk000[stage->unk044[i]];
        if (lbl_1_data_EB8) {
            Hu3DModelAmbSet(mdlId, 1.0f, 1.0f, 1.0f);
        }
        Hu3DGLightColorSet(light->unk004, 255, 255, 255, 255);
    }
    lbl_1_data_EB8 = 0;
}

/* 19 insns */
void fn_1_8FDC(M502_BLOCKEFFECT *effect, M502_BLOCK *block)
{
    memset(effect, 0, sizeof(M502_BLOCKEFFECT));
    effect->unk000 = block;
    effect->unk014 = 0;
}

/* 12 insns */
void fn_1_9028(M502_BLOCKEFFECT *effect)
{
    memset(effect, 0, sizeof(M502_BLOCKEFFECT));
}

/* 53 insns */
void fn_1_9058(M502_BLOCKEFFECT *effect)
{
    M502_WORKMODEL *res = &effect->unk000->unk000->unk000->unk01C;
    float time;
    float maxTime;

    switch (effect->unk004) {
        case 0:
            break;
        case 1:
            time = Hu3DData[res->unk000[effect->unk014]].motShapeWork.time;
            maxTime = Hu3DMotionShapeMaxTimeGet(res->unk000[effect->unk014]);
            if (time >= maxTime) {
                Hu3DModelAttrSet(res->unk000[effect->unk014], HU3D_ATTR_DISPOFF);
                effect->unk004 = 0;
            }
            break;
    }
}

/* 207 insns */
void fn_1_912C(M502_BLOCKEFFECT *effect, s32 idx, HuVecF *pos)
{
    M502_WORKMODEL *res = &effect->unk000->unk000->unk000->unk01C;
    s32 playerNo = effect->unk000->unk000->unk004;
    HuVecF p = *pos;
    s32 y = pos->y;

    effect->unk014 = playerNo * 2 + 0x79 + idx;
    Hu3DModelAttrReset(res->unk000[effect->unk014], HU3D_ATTR_DISPOFF);
    Hu3DMotionShapeSpeedSet(res->unk000[effect->unk014], 1.0f);
    Hu3DMotionShapeTimeSet(res->unk000[effect->unk014], 0.0f);
    Hu3DModelCameraSet(res->unk000[effect->unk014], lbl_1_data_B60[playerNo]);
    if (pos->y > -2700.0f) {
        effect->unk008.x = 0.5f;
        effect->unk008.y = 0.5f;
        effect->unk008.z = 0.0f;
    }
    else if (pos->y > -6000.0f) {
        y = y - 3300.0f;
        effect->unk008.x = 0.25f;
        effect->unk008.y = 0.15f;
        effect->unk008.z = 0.15f;
    }
    else {
        y = y - 6600.0f;
        effect->unk008.x = 0.2f;
        effect->unk008.y = 0.0f;
        effect->unk008.z = 0.1f;
    }
    y = y / 300.0f;
    if (y % 2 != 0) {
        p.x -= 30.000002f;
    }
    else {
        p.x += 15.000001f;
    }
    p.y += 25.0f;
    Hu3DModelPosSet(res->unk000[effect->unk014], p.x, p.y, p.z);
    Hu3DModelAmbSet(res->unk000[effect->unk014], effect->unk008.x, effect->unk008.y, effect->unk008.z);
    effect->unk004 = 1;
    effect->unk006 = 0;
}

