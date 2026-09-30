/*
 * m510dll pad.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/pad.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .data --- */
/* 0x3C8 */ s16 lbl_1_data_3C8[4] = { 15, 43, 18, 10 };

/*
 * fn_1_87A8 indexes the 30-entry plan with 30 - work->unk2508. If the count has
 * already reached 0 when the AI reads it, retail reads index 30: the high half of
 * M510_PAD.unk06C (padNo, 0..3) on big-endian, i.e. 0 ("take"). The host layout
 * and byte order differ, so reproduce retail's value instead of the read.
 */
#define M510_PADPLAN(ai, no) ((ai)->unk02C[no])

/* --- functions (reference order) --- */
/* 28 insns */
void fn_1_8184(M510_PAD *pad, s32 playerNo, M510_PLAYERMODEL *owner)
{
    memset(pad, 0, sizeof(M510_PAD));
    pad->unk000 = owner;
    pad->unk06C = GwPlayerConf[playerNo].padNo;
    fn_1_8420(&pad->unk004, pad);
}

/* 16 insns */
void fn_1_81F4(M510_PAD *pad)
{
    fn_1_8778(&pad->unk004);
    memset(pad, 0, sizeof(M510_PAD));
}

/* 123 insns */
void fn_1_8234(M510_PAD *pad)
{
    if (pad->unk004.unk008 != 0) {
        fn_1_87A8(&pad->unk004);
    }
    else {
        pad->unk070 = HuPadBtn[pad->unk06C];
        pad->unk074 = HuPadBtnDown[pad->unk06C];
        pad->unk07A = HuPadBtnRep[pad->unk06C];
        pad->unk078 = HuPadStkX[pad->unk06C];
        pad->unk078 = (((pad->unk078 >= 0) ? pad->unk078 : -pad->unk078) < 10) ? 0 : pad->unk078;
        pad->unk079 = HuPadStkY[pad->unk06C];
        pad->unk079 = (((pad->unk079 >= 0) ? pad->unk079 : -pad->unk079) < 10) ? 0 : pad->unk079;
        pad->unk07C = HuPadSubStkX[pad->unk06C];
        pad->unk07D = HuPadSubStkY[pad->unk06C];
        pad->unk07E = HuPadTrigL[pad->unk06C];
        pad->unk07F = HuPadTrigR[pad->unk06C];
        pad->unk080 = HuPadDStk[pad->unk06C];
        pad->unk081 = HuPadDStkRep[pad->unk06C];
    }
}

/* 214 insns */
void fn_1_8420(M510_PADAI *ai, M510_PAD *pad)
{
    M510_PAD *owner = pad;
    M510_PLAYERMODEL *pm = owner->unk000;
    s16 num;
    s16 r;
    s16 a;
    s16 b;
    s16 tmp;
    s32 i;

    memset(ai, 0, sizeof(M510_PADAI));
    ai->unk000 = pad;
    ai->unk008 = GwPlayerConf[pm->unk008].type;
    ai->unk010 = (GwPlayerConf[pm->unk008].dif == 3) ? 0 : (GwPlayerConf[pm->unk008].dif == 2) ? 1 : (GwPlayerConf[pm->unk008].dif == 1) ? 2 : 3;
    num = 0;
    switch (ai->unk010) {
        case 0:
            num = frand() % 6 + 18;
            break;
        case 1:
            num = (frand() & 3) + 14;
            break;
        case 2:
            num = frand() % 5 + 9;
            break;
        default:
            num = frand() % 5 + 4;
            break;
    }
    for (i = 0; i < 30; i++) {
        if (i < num) {
            ai->unk02C[i] = 1;
        }
        else {
            r = frand() % 10000;
            ai->unk02C[i] = 0;
            switch (ai->unk010) {
                case 0:
                    if (r < 1500) {
                        ai->unk02C[i] = 2;
                    }
                    break;
                case 1:
                    if (r < 3000) {
                        ai->unk02C[i] = 2;
                    }
                    break;
                case 2:
                    if (r < 4000) {
                        ai->unk02C[i] = 2;
                    }
                    break;
                default:
                    if (r < 5000) {
                        ai->unk02C[i] = 2;
                    }
                    break;
            }
        }
    }
    for (i = 0; i < 120; i++) {
        a = i % 30;
        b = frand() % 30;
        tmp = ai->unk02C[a];
        ai->unk02C[a] = ai->unk02C[b];
        ai->unk02C[b] = tmp;
    }
    ai->unk00C = 0;
}

/* 12 insns */
void fn_1_8778(M510_PADAI *ai)
{
    memset(ai, 0, sizeof(M510_PADAI));
}

/* 132 insns */
void fn_1_87A8(M510_PADAI *ai)
{
    M510_PAD *pad = ai->unk000;
    M510_PLAYERMODEL *pm = pad->unk000;
    M510_PLAYER *player = pm->unk000;
    M510_WORK *work = player->unk000;
    M510_PITCH *pitch = &player->unk118;
    s16 no = 30 - work->unk2508;

    pad->unk074 = 0;
    switch (ai->unk004) {
        case 0:
            if (pitch->unk004 == 3) {
                ai->unk006 = lbl_1_data_3C8[pitch->unk020];
                ai->unk006 += frand() % 3 - 1;
                if (M510_PADPLAN(ai, no) == 0) {
                    ai->unk006 = 0;
                    ai->unk004 = 2;
                }
                else if (M510_PADPLAN(ai, no) == 2) {
                    if (pitch->unk020 == 1) {
                        ai->unk006 -= frand() % 7 + 7;
                    }
                    else {
                        ai->unk006 += frand() % 7 + 7;
                    }
                    ai->unk004 = 1;
                }
                else {
                    ai->unk004 = 1;
                }
            }
            break;
        case 1:
            if (ai->unk006-- <= 0) {
                pm->unk02C.unk074 |= 0x100;
                ai->unk006 = 0;
                ai->unk004 = 2;
            }
            break;
        case 2:
            if (pitch->unk004 == 5) {
                ai->unk006 = 0;
                ai->unk004 = 0;
            }
            break;
    }
}
