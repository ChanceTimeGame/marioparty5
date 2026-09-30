/*
 * m502dll input.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/input.s;
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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x1E8 */ /* s32 lbl_1_rodata_1E8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1F4 */ /* float lbl_1_rodata_1F4 = 150.0f; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 300.0f; */
/* 0x200 */ /* double lbl_1_rodata_200 = 4503601774854144; */

/* --- functions (reference order) --- */
/* 374 insns */
void fn_1_58E0(M502_INPUTCOM *com)
{
    M502_INPUT *in = com->unk000;
    M502_CHAR *chr = in->unk000;
    M502_BLOCK *block = &chr->unk000->unk008;
    s32 dif = GwPlayerConf[chr->unk010].dif;
    s32 count[3] = { 0, 0, 0 };
    s32 cand[3];
    s16 row;
    s16 y;
    s16 x;
    s32 i;
    s32 min;
    s32 num;
    s32 r;

    switch (com->unk006) {
        case 0:
            if (com->unk012 == 0) {
                fn_1_6250(com, &row, &y, &x);
                if (row >= 3) {
                    return;
                }
                for (i = 0; i < 3; i++) {
                    if (block->unk004[row][i].unk004 == 2) {
                        count[i]++;
                    }
                    if (block->unk004[row][i + 3].unk004 == 2) {
                        count[i]++;
                    }
                    if (block->unk004[row][i + 6].unk004 == 2) {
                        count[i]++;
                    }
                }
                min = 99999;
                for (i = 0; i < 3; i++) {
                    if (min > count[i]) {
                        min = count[i];
                    }
                }
                num = 0;
                for (i = 0; i < 3; i++) {
                    if (min == count[i]) {
                        cand[num] = i;
                        num++;
                    }
                }
                r = rand8() % 200;
                com->unk010 = 0;
                if (num == 1) {
                    com->unk010 = cand[0];
                }
                else if (num == 2) {
                    if (chr->unk010 == 0) {
                        if (r <= 20) {
                            com->unk010 = cand[0];
                        }
                        else {
                            com->unk010 = cand[1];
                        }
                    }
                    else if (chr->unk010 == 1) {
                        if (r <= 130) {
                            com->unk010 = cand[0];
                        }
                        else {
                            com->unk010 = cand[1];
                        }
                    }
                    else if (chr->unk010 == 2) {
                        if (r <= 70) {
                            com->unk010 = cand[0];
                        }
                        else {
                            com->unk010 = cand[1];
                        }
                    }
                    else {
                        if (r <= 180) {
                            com->unk010 = cand[0];
                        }
                        else {
                            com->unk010 = cand[1];
                        }
                    }
                }
                else if (num == 3) {
                    if (chr->unk010 == 0) {
                        if (r <= 66) {
                            com->unk010 = cand[0];
                        }
                        else if (r <= 132) {
                            com->unk010 = cand[1];
                        }
                        else {
                            com->unk010 = cand[2];
                        }
                    }
                    else if (chr->unk010 == 1) {
                        if (r <= 20) {
                            com->unk010 = cand[0];
                        }
                        else if (r <= 40) {
                            com->unk010 = cand[1];
                        }
                        else {
                            com->unk010 = cand[2];
                        }
                    }
                    else if (chr->unk010 == 2) {
                        if (r <= 20) {
                            com->unk010 = cand[0];
                        }
                        else if (r <= 180) {
                            com->unk010 = cand[1];
                        }
                        else {
                            com->unk010 = cand[2];
                        }
                    }
                    else {
                        if (r <= 160) {
                            com->unk010 = cand[0];
                        }
                        else if (r <= 180) {
                            com->unk010 = cand[1];
                        }
                        else {
                            com->unk010 = cand[2];
                        }
                    }
                }
                r = rand8() % 100;
                switch (dif) {
                    case 0:
                        if (r >= 10) {
                            com->unk010 = r % 3;
                        }
                        break;
                    case 1:
                        if (r >= 40) {
                            com->unk010 = r % 3;
                        }
                        break;
                    case 2:
                        if (r >= 100) {
                            com->unk010 = r % 3;
                        }
                        break;
                    case 3:
                        if (r >= 100) {
                            com->unk010 = r % 3;
                        }
                        break;
                }
                if (chr->unk060 < com->unk010) {
                    in->unk024 = 1;
                }
                if (chr->unk060 > com->unk010) {
                    in->unk024 = -1;
                }
                com->unk012 = 1;
            }
            com->unk006++;
            break;
        case 1:
            if (chr->unk060 != com->unk010) {
                if (chr->unk060 < com->unk010) {
                    chr->unk024.unk024 = 1;
                }
                if (chr->unk060 > com->unk010) {
                    chr->unk024.unk024 = -1;
                }
            }
            if (chr->unk008 == 0) {
                com->unk006 = 0;
                com->unk004++;
            }
            break;
    }
}

/* 230 insns */
void fn_1_5EB8(M502_INPUTCOM *com)
{
    M502_INPUT *in = com->unk000;
    M502_CHAR *chr = in->unk000;
    M502_BLOCK *block = &chr->unk000->unk008;
    s32 dif = GwPlayerConf[chr->unk010].dif;
    s16 row;
    s16 y;
    s16 x;
    s32 r;

    switch (com->unk006) {
        case 0:
            r = (rand8() % 100) / 20;
            switch (dif) {
                case 0:
                    com->unk00A = r + 15;
                    break;
                case 1:
                    com->unk00A = r + 11;
                    break;
                case 2:
                    com->unk00A = r + 8;
                    break;
                case 3:
                    com->unk00A = r + 4;
                    break;
            }
            com->unk006++;
            com->unk008 = 0;
            break;
        case 1:
            if (++com->unk008 >= com->unk00A) {
                in->unk020 |= PAD_BUTTON_A;
                in->unk01C |= PAD_BUTTON_A;
                fn_1_6250(com, &row, &y, &x);
                com->unk00A = 7;
                com->unk006++;
                com->unk008 = 0;
                if (row >= 3) {
                    break;
                }
                if (y > 0) {
                    com->unk012 = 0;
                }
                r = rand8() % 100;
                switch (dif) {
                    case 0:
                        com->unk00A = 7;
                        break;
                    case 1:
                        if (r < 50) {
                            com->unk00A = 7;
                        }
                        else {
                            com->unk00A = 15;
                        }
                        break;
                    case 2:
                        if (block->unk004[row][x + y * 3].unk004 == 2) {
                            if (r < 40) {
                                com->unk00A = 15;
                            }
                            else {
                                com->unk00A = 7;
                            }
                        }
                        else {
                            if (r < 40) {
                                com->unk00A = 15;
                            }
                            else {
                                com->unk00A = 30;
                            }
                        }
                        break;
                    case 3:
                        if (block->unk004[row][x + y * 3].unk004 == 2) {
                            if (r < 10) {
                                com->unk00A = 15;
                            }
                            else {
                                com->unk00A = 7;
                            }
                        }
                        else {
                            if (r < 10) {
                                com->unk00A = 15;
                            }
                            else {
                                com->unk00A = 30;
                            }
                        }
                        break;
                }
            }
            break;
        case 2:
            if (com->unk00A != 7) {
                in->unk01C |= PAD_BUTTON_A;
            }
            if (++com->unk008 >= com->unk00A) {
                in->unk020 |= PAD_BUTTON_A;
                com->unk006++;
                com->unk008 = 0;
            }
            break;
        case 3:
            if (chr->unk008 == 0) {
                com->unk006 = 0;
                if (chr->unk006 == 0) {
                    com->unk004 = 0;
                }
            }
            break;
    }
}

/* 108 insns */
void fn_1_6250(M502_INPUTCOM *com, s16 *row, s16 *y, s16 *x)
{
    M502_INPUT *in = com->unk000;
    M502_CHAR *chr = in->unk000;
    HuVecF pos;

    pos.x = chr->unk01C->trans.x;
    pos.y = chr->unk01C->trans.y;
    pos.z = chr->unk01C->trans.z;
    pos.y -= 150.0f;
    pos.x = 300.0f * (s16)(pos.x / 300.0f);
    pos.y = 300.0f * (s16)(pos.y / 300.0f);
    pos.z = 300.0f * (s16)(pos.z / 300.0f);
    fn_1_6E1C(&pos, row, y, x);
}

/* 30 insns */
void fn_1_6400(M502_INPUT *in, s32 idx, M502_CHAR *chr)
{
    memset(in, 0, sizeof(M502_INPUT));
    in->unk000 = chr;
    in->unk018 = GwPlayerConf[idx].padNo;
    fn_1_57B4(&in->unk004, idx, in);
}

/* 16 insns */
void fn_1_6478(M502_INPUT *in)
{
    fn_1_5818(&in->unk004);
    memset(in, 0, sizeof(M502_INPUT));
}

/* 107 insns */
void fn_1_64B8(M502_INPUT *in)
{
    if (in->unk004.unk00C) {
        fn_1_5848(&in->unk004);
    }
    else {
        in->unk01C = HuPadBtn[in->unk018];
        in->unk020 = HuPadBtnDown[in->unk018];
        in->unk026 = HuPadBtnRep[in->unk018];
        in->unk024 = HuPadStkX[in->unk018];
        in->unk024 = (((in->unk024 >= 0) ? in->unk024 : -in->unk024) < 10) ? 0 : in->unk024;
        in->unk028 = HuPadStkY[in->unk018];
        in->unk029 = HuPadSubStkX[in->unk018];
        in->unk02A = HuPadSubStkY[in->unk018];
        in->unk02B = HuPadTrigL[in->unk018];
        in->unk02C = HuPadTrigR[in->unk018];
        in->unk02D = HuPadDStk[in->unk018];
        in->unk02E = HuPadDStkRep[in->unk018];
    }
}
