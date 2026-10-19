/*
 * sdroomdll tournament.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/tournament.s.
 */

#include "REL/sdroomdll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "math.h"
#include "humath.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_6A0 = 24.0f; /* 0x6A0 */
static const double lbl_1_rodata_6A8 = 24.0; /* 0x6A8 */
static const double lbl_1_rodata_6B0 = 3.141592653589793; /* 0x6B0 */
static const double lbl_1_rodata_6B8 = 90.0; /* 0x6B8 */
static const double lbl_1_rodata_6C0 = 10.0; /* 0x6C0 */
static const double lbl_1_rodata_6C8 = 180.0; /* 0x6C8 */
static const float lbl_1_rodata_6D0 = -10000.0f; /* 0x6D0 */
static const float lbl_1_rodata_6D4 = 200.0f; /* 0x6D4 */
/* 0x6D8 lbl_1_rodata_6D8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_6E0 = 32.0f; /* 0x6E0 */
static const float lbl_1_rodata_6E4 = 0.0f; /* 0x6E4 */
static const float lbl_1_rodata_6E8 = 406.0f; /* 0x6E8 */
static const float lbl_1_rodata_6EC = 288.0f; /* 0x6EC */
static const float lbl_1_rodata_6F0 = 240.0f; /* 0x6F0 */
static const float lbl_1_rodata_6F4 = 1.0f; /* 0x6F4 */
static const float lbl_1_rodata_6F8 = 48.0f; /* 0x6F8 */
static const float lbl_1_rodata_6FC = 700.0f; /* 0x6FC */
static const float lbl_1_rodata_700 = -50.0f; /* 0x700 */
static const float lbl_1_rodata_704 = -5.0f; /* 0x704 */
static const float lbl_1_rodata_708 = 5.0f; /* 0x708 */
static const float lbl_1_rodata_70C = 1.2f; /* 0x70C */
static const float lbl_1_rodata_710 = 1.3333334f; /* 0x710 */
static const float lbl_1_rodata_714 = 216.0f; /* 0x714 */
static const float lbl_1_rodata_718 = 180.0f; /* 0x718 */
static const float lbl_1_rodata_71C = 0.927f; /* 0x71C */
static const float lbl_1_rodata_720 = 1.03f; /* 0x720 */
static const float lbl_1_rodata_724 = 0.7f; /* 0x724 */
static const float lbl_1_rodata_728 = 40.0f; /* 0x728 */
static const float lbl_1_rodata_72C = 30.0f; /* 0x72C */
static const float lbl_1_rodata_730 = 15000.0f; /* 0x730 */
static const float lbl_1_rodata_734 = 480.0f; /* 0x734 */
static const float lbl_1_rodata_738 = 360.0f; /* 0x738 */
static const double lbl_1_rodata_740 = 1.0; /* 0x740 */
static const double lbl_1_rodata_748 = 0.9; /* 0x748 */
static const double lbl_1_rodata_750 = 0.1; /* 0x750 */
/* 0x758 lbl_1_rodata_758 = 4503599627370496: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_760 = 0.7; /* 0x760 */
static const double lbl_1_rodata_768 = 0.3; /* 0x768 */
static const double lbl_1_rodata_770 = 0.05; /* 0x770 */
static const double lbl_1_rodata_778 = 20.0; /* 0x778 */
static const double lbl_1_rodata_780 = 15.0; /* 0x780 */
static const float lbl_1_rodata_788 = 16.0f; /* 0x788 */
static const double lbl_1_rodata_790 = 5.0; /* 0x790 */
static const float lbl_1_rodata_798 = 50.0f; /* 0x798 */
static const double lbl_1_rodata_7A0 = 4.0; /* 0x7A0 */
static const double lbl_1_rodata_7A8 = 2.0; /* 0x7A8 */
static const float lbl_1_rodata_7B0 = 0.8f; /* 0x7B0 */
static const double lbl_1_rodata_7B8 = 0.8; /* 0x7B8 */
static const double lbl_1_rodata_7C0 = 0.2; /* 0x7C0 */
static const float lbl_1_rodata_7C8 = 320.0f; /* 0x7C8 */
static const float lbl_1_rodata_7CC = 10.0f; /* 0x7CC */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xC34 gap_05_00000C34_bss (0x4): alignment gap */
/* 0xC32 */ s16 lbl_1_bss_C32; /* bracket sprite group */
/* 0xC30 gap_05_00000C30_bss (0x2): lbl_1_bss_C2E[1] */
/* 0xC2E */ s16 lbl_1_bss_C2E[2]; /* [1] is accessed at +2 (dtk gap_05_00000C30) */
/* 0xC22 */ s16 lbl_1_bss_C22[6];
/* 0xC20 */ s16 lbl_1_bss_C20;
/* 0xC1C */ HUPROCESS *lbl_1_bss_C1C;
/* 0xC18 */ HUPROCESS *lbl_1_bss_C18;
/* 0xC14 */ HUPROCESS *lbl_1_bss_C14;
/* 0xC10 */ s32 lbl_1_bss_C10;
/* 0xC0C */ void *lbl_1_bss_C0C;
/* 0xC08 */ ANIMDATA *lbl_1_bss_C08;
/* 0xC04 */ float lbl_1_bss_C04;
/* 0xC02 */ s16 lbl_1_bss_C02;
/* 0xC00 */ s16 lbl_1_bss_C00;

/* --- functions (reference order), .data placed before its first user --- */
/* 1 insns */
void fn_1_1C25C(void) { }

/* 0x1B60 */ OMCAMERAVIEW lbl_1_data_1B60 = { { 0.0f, 100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 500.0f };
/* 0x1B7C */ HuVecF lbl_1_data_1B7C[14] = { { -66.0f, -26.0f, 1.0f }, { 65.0f, -26.0f, -1.0f }, { -133.0f, -15.0f, 1.0f }, { -138.0f, -15.0f, -1.0f }, { 137.0f, -15.0f, 1.0f }, { 132.0f, -15.0f, -1.0f }, { -168.0f, 26.0f, 1.0f }, { -237.0f, 26.0f, -1.0f }, { -36.0f, 26.0f, 1.0f }, { -101.0f, 26.0f, -1.0f }, { 101.0f, 26.0f, 1.0f }, { 35.0f, 26.0f, -1.0f }, { 235.0f, 26.0f, 1.0f }, { 169.0f, 26.0f, -1.0f } };
/* 0x1C24: bracket positions {x, y}: [0..7] seats, [8..15] seats raised, [16..19]/[20..23] round 1
 * winners, [24..25]/[26..27] round 2 winners, [28] final, [29] champion */
/* 0x1C24 */ float lbl_1_data_1C24[30][2] = { { 51.0f, 331.0f }, { 119.0f, 331.0f }, { 185.0f, 331.0f }, { 253.0f, 331.0f }, { 321.0f, 331.0f }, { 389.0f, 331.0f }, { 455.0f, 331.0f }, { 523.0f, 331.0f }, { 51.0f, 269.0f }, { 119.0f, 269.0f }, { 185.0f, 269.0f }, { 253.0f, 269.0f }, { 321.0f, 269.0f }, { 389.0f, 269.0f }, { 455.0f, 269.0f }, { 523.0f, 269.0f }, { 85.0f, 269.0f }, { 219.0f, 269.0f }, { 355.0f, 269.0f }, { 489.0f, 269.0f }, { 85.0f, 228.0f }, { 219.0f, 228.0f }, { 355.0f, 228.0f }, { 489.0f, 228.0f }, { 152.0f, 228.0f }, { 422.0f, 228.0f }, { 152.0f, 187.0f }, { 422.0f, 187.0f }, { 287.0f, 187.0f }, { 287.0f, 172.0f } };

/* 981 insns */
void fn_1_1C260(void)
{
    s16 seat[2];
    HuVec2f size;
    float ofsY;
    s16 winner;
    OMOVLHIS *his;
    s16 i;
    HUWINID winId;
    s16 state;
    s16 seatA;
    s16 padNo;
    u32 mesNo;
    s16 sel;
    HUWIN *winP;
    s16 seatB;

    padNo = GwSdBattle.padNo[0];
    lbl_1_bss_C10 = 0;
    omCameraViewSetMulti(HU3D_CAM2, &lbl_1_data_1B60);
    HuPrcVSleep();
    if (omovlevtno != 4) {
        for (i = 0; i < 8; i++) {
            SDTOUR->round[i] = 0;
        }
        fn_1_1F21C();
        winner = -1;
        lbl_1_bss_C1C = NULL;
        fn_1_1D1B4();
        fn_1_1E51C(seat);
        lbl_1_bss_C1C = HuPrcChildCreate(fn_1_1E154, 1000, 0x3000, 0, HuPrcCurrentGet());
        lbl_1_bss_C1C->property = (void *)((seat[0] << 8) | seat[1]);
    } else {
        winner = GwSdBattle.winnerNo;
        fn_1_1E51C(seat);
        if (seat[0] == 0 && SDTOUR->round[seat[0]] == 2 && (winner == 0 || winner == -1)) {
            fn_1_23280();
            winner = GwSdBattle.winnerNo;
        }
        if (winner == 0 && seat[0] == 0 && GwSdBattle.machine[1].charNo == 32) {
            if (!GwSdCommon.extCharSelF) {
                GwSdCommon.newPart1F = 1;
            }
            GwSdCommon.extCharSelF = 1;
        }
        lbl_1_bss_C1C = HuPrcChildCreate(fn_1_1E154, 1000, 0x3000, 0, HuPrcCurrentGet());
        lbl_1_bss_C1C->property = (void *)((seat[0] << 8) | seat[1]);
        fn_1_1D1B4();
        if (SDTOUR->round[seat[0]] == 0) {
            HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0]][0], lbl_1_data_1C24[seat[0]][1] - 24.0f);
            HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1]][0], lbl_1_data_1C24[seat[1]][1] - 24.0f);
        } else if (SDTOUR->round[seat[0]] == 1) {
            HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0] / 2 + 16][0], lbl_1_data_1C24[seat[0] / 2 + 16][1] - 24.0f);
            HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1] / 2 + 16][0], lbl_1_data_1C24[seat[1] / 2 + 16][1] - 24.0f);
        } else {
            HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0] / 4 + 24][0], lbl_1_data_1C24[seat[0] / 4 + 24][1] - 24.0f);
            HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1] / 4 + 24][0], lbl_1_data_1C24[seat[1] / 4 + 24][1] - 24.0f);
        }
    }
    HuAudSStreamPlay(37);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    while (1) {
        state = fn_1_1E51C(seat);
        if (winner != -1) {
            seatA = seat[winner];
            seatB = seat[winner ^ 1];
            SDTOUR->round[seatA]++;
            state = fn_1_1E51C(seat);
            sel = fn_1_1E6A8();
            if (sel != -1) {
                fn_1_1E880(seatA, seatB, sel);
                if (state == -1) {
                    fn_1_1F960(seatA);
                    his = omOvlHisGet(0);
                    omOvlHisChg(0, his->ovl, 3, his->stat);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    HuAudSStreamAllFadeOut(1000);
                    while (WipeCheckEnd()) {
                        HuPrcVSleep();
                    }
                    fn_1_1DFA8();
                    omOvlReturnEx(0, 1);
                    while (1) {
                        HuPrcVSleep();
                    }
                }
            }
            if (lbl_1_bss_C1C != 0) {
                lbl_1_bss_C1C->property = (void *)1;
            }
            lbl_1_bss_C1C = HuPrcChildCreate(fn_1_1E154, 1000, 0x3000, 0, HuPrcCurrentGet());
            lbl_1_bss_C1C->property = (void *)((seat[0] << 8) | seat[1]);
        }
        if (winner != -1 || omovlevtno != 4) {
            for (i = 1; i <= 10; i++) {
                ofsY = 24.0 * sin(M_PI * (90.0 * (i / 10.0)) / 180.0);
                if (SDTOUR->round[seat[0]] == 0) {
                    HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0]][0], lbl_1_data_1C24[seat[0]][1] - ofsY);
                    HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1]][0], lbl_1_data_1C24[seat[1]][1] - ofsY);
                } else if (SDTOUR->round[seat[0]] == 1) {
                    HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0] / 2 + 16][0], lbl_1_data_1C24[seat[0] / 2 + 16][1] - ofsY);
                    HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1] / 2 + 16][0], lbl_1_data_1C24[seat[1] / 2 + 16][1] - ofsY);
                } else {
                    HuSprPosSet(lbl_1_bss_C32, seat[0] + 15, lbl_1_data_1C24[seat[0] / 4 + 24][0], lbl_1_data_1C24[seat[0] / 4 + 24][1] - ofsY);
                    HuSprPosSet(lbl_1_bss_C32, seat[1] + 15, lbl_1_data_1C24[seat[1] / 4 + 24][0], lbl_1_data_1C24[seat[1] / 4 + 24][1] - ofsY);
                }
                HuPrcVSleep();
            }
        }
        if (seat[0] == 0) {
            mesNo = 0x1C000B;
        } else {
            mesNo = 0x1C000C;
        }
        HuWinMesSet(lbl_1_bss_C2E[1], mesNo);
        HuWinDispOn(lbl_1_bss_C2E[1]);
        while (!(fn_1_4FD0(1 << padNo) & PAD_BUTTON_START)) {
            if (fn_1_4FD0(1 << padNo) & PAD_BUTTON_A) {
                HuAudFXPlay(1);
                lbl_1_bss_C10 = 1;
                HuPrcVSleep();
                fn_1_20300();
                lbl_1_bss_C1C = HuPrcChildCreate(fn_1_1E154, 1000, 0x3000, 0, HuPrcCurrentGet());
                lbl_1_bss_C1C->property = (void *)((seat[0] << 8) | seat[1]);
                HuWinMesSet(lbl_1_bss_C2E[1], mesNo);
                lbl_1_bss_C10 = 0;
                HuPrcVSleep();
            }
            if (fn_1_4FD0(1 << padNo) & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                HuWinMesMaxSizeGet(1, &size, 0x19007C);
                winId = HuWinExCreate(-10000.0f, 200.0f, size.x, size.y, -1);
                HuWinPriSet(winId, 10);
                HuWinExOpen(winId);
                HuWinMesSet(winId, 0x19007C);
                HuWinMesWait(winId);
                winP = &winData[winId];
                winP->padMask = 1 << sdWorkInt[7];
                state = HuWinChoiceGet(winId, -1);
                if (state == 0) {
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    HuAudSStreamAllFadeOut(1000);
                    while (WipeCheckEnd()) {
                        HuPrcVSleep();
                    }
                    his = omOvlHisGet(0);
                    omOvlHisChg(0, his->ovl, 3, his->stat);
                    fn_1_1DFA8();
                    omOvlReturnEx(0, 1);
                    while (1) {
                        HuPrcVSleep();
                    }
                }
                HuWinExClose(winId);
                HuWinExKill(winId);
            }
            HuPrcVSleep();
        }
        if (seat[0] == 0) {
            break;
        }
        winner = fn_1_20038(seat);
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    lbl_1_bss_C10 = 1;
    HuPrcSleep(2);
    fn_1_1DFA8();
    if (seat[0] == 0) {
        GwPlayerConf[0].type = 0;
        GwSdBattle.stageType1 = -1;
        GwSdBattle.machine[0] = GwSdCommon.machine[sdWorkInt[7]];
    } else {
        GwPlayerConf[0].type = 1;
        GwSdBattle.stageType1 = fn_1_1F82C(SDTOUR->charNo[seat[0]]);
        GwPlayerConf[0].dif = 1;
        GwSdBattle.machine[0].charNo = SDTOUR->charNo[seat[0]];
    }
    GwPlayerConf[1].type = 1;
    GwSdBattle.stageType2 = fn_1_1F82C(SDTOUR->charNo[seat[1]]);
    GwPlayerConf[1].dif = 1;
    GwSdBattle.machine[1].charNo = SDTOUR->charNo[seat[1]];
    if (SDTOUR->round[seat[0]] == 2) {
        fn_1_20870(seat);
    }
    fn_1_4238(4);
    while (1) {
        HuPrcVSleep();
    }
}

/* 0x1D14: opponent id - 32 -> charNo */
/* 0x1D14 */ s16 lbl_1_data_1D14[12] = { 10, 11, 1, 0, 2, 4, 8, 3, 6, 5, 7, 9 };
/* 0x1D2C..0x1D76: per sdWorkInt[3] (game type) an s16 count[3] and three opponent-id lists
 * (rank 3, rank 2, rank 1); the counts and lists are edited in place by fn_1_1F21C */
/* 0x1D2C */ s16 lbl_1_data_1D2C[3] = { 2, 4, 5 };
/* 0x1D32 */ s16 lbl_1_data_1D32[2] = { 32, 33 };
/* 0x1D36 */ s16 lbl_1_data_1D36[4] = { 34, 35, 36, 37 };
/* 0x1D3E */ s16 lbl_1_data_1D3E[5] = { 38, 39, 40, 41, 42 };
/* 0x1D48 */ s16 lbl_1_data_1D48[3] = { 3, 3, 5 };
/* 0x1D4E */ s16 lbl_1_data_1D4E[3] = { 34, 35, 36 };
/* 0x1D54 */ s16 lbl_1_data_1D54[3] = { 32, 33, 38 };
/* 0x1D5A */ s16 lbl_1_data_1D5A[5] = { 37, 39, 40, 41, 42 };
/* 0x1D64 */ s16 lbl_1_data_1D64[3] = { 2, 4, 5 };
/* 0x1D6A: count 2 (lbl_1_data_1D64[0]); dtk split [1] off as lbl_1_data_1D6C (unreferenced) */
/* 0x1D6A */ s16 lbl_1_data_1D6A[2] = { 35, 36 };
/* 0x1D6E */ s16 lbl_1_data_1D6E[4] = { 32, 33, 34, 38 };
/* 0x1D76 */ s16 lbl_1_data_1D76[5] = { 37, 39, 40, 41, 42 };
/* 0x1D80 */ OMCAMERAVIEW lbl_1_data_1D80 = { { 0.0f, 140.0f, -40.0f }, { -23.0f, -69.0f, 0.0f }, 6856.0f };

/* 893 insns */
void fn_1_1D1B4(void)
{
    s16 seat[2];
    HuVecF pos2d;
    HuVecF pos3d;
    HU3DMODEL *modelP;
    HUWINID winId;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    ANIMDATA *anim;
    s16 i;
    s16 bank;
    HU3DMODELID modelId;

    lbl_1_bss_C2E[0] = winId = HuWinCreate(-10000.0f, 32.0f, 576, 42, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinInsertMesSet(winId, sdWorkInt[3] + 0x190035, 1);
    HuWinInsertMesSet(winId, sdWorkInt[6] + 0x190038, 2);
    HuWinMesSet(winId, 0x190034);
    lbl_1_bss_C2E[1] = winId = HuWinCreate(-10000.0f, 406.0f, 576, 42, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSet(winId, 0x1C000B);
    HuWinDispOff(winId);
    lbl_1_bss_C32 = grpId = HuSprGrpCreate(25);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdd1, 23)), 20, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 288.0f, 240.0f);
    anim = HuSprAnimDataRead(DATANUM(DATA_sdd1, 24));
    for (i = 0; i < 2; i++) {
        sprId = HuSprCreate(anim, 20, 0);
        HuSprGrpMemberSet(grpId, i + 1, sprId);
        HuSprPosSet(grpId, i + 1, 288.0f + lbl_1_data_1B7C[i].x, 240.0f + lbl_1_data_1B7C[i].y);
        HuSprScaleSet(grpId, i + 1, lbl_1_data_1B7C[i].z, 1.0f);
        HuSprAttrSet(grpId, i + 1, HUSPR_ATTR_ADDCOL | HUSPR_ATTR_DISPOFF);
        HuSprColorSet(grpId, i + 1, 255, 12, 32);
    }
    anim = HuSprAnimDataRead(DATANUM(DATA_sdd1, 25));
    for (i = 0; i < 4; i++) {
        sprId = HuSprCreate(anim, 20, 0);
        HuSprGrpMemberSet(grpId, i + 3, sprId);
        HuSprPosSet(grpId, i + 3, 288.0f + lbl_1_data_1B7C[i + 2].x, 240.0f + lbl_1_data_1B7C[i + 2].y);
        HuSprScaleSet(grpId, i + 3, lbl_1_data_1B7C[i + 2].z, 1.0f);
        HuSprAttrSet(grpId, i + 3, HUSPR_ATTR_ADDCOL | HUSPR_ATTR_DISPOFF);
        HuSprColorSet(grpId, i + 3, 255, 12, 32);
    }
    anim = HuSprAnimDataRead(DATANUM(DATA_sdd1, 26));
    for (i = 0; i < 8; i++) {
        sprId = HuSprCreate(anim, 20, 0);
        HuSprGrpMemberSet(grpId, i + 7, sprId);
        HuSprPosSet(grpId, i + 7, 288.0f + lbl_1_data_1B7C[i + 6].x, 240.0f + lbl_1_data_1B7C[i + 6].y);
        HuSprScaleSet(grpId, i + 7, lbl_1_data_1B7C[i + 6].z, 1.0f);
        HuSprAttrSet(grpId, i + 7, HUSPR_ATTR_ADDCOL | HUSPR_ATTR_DISPOFF);
        HuSprColorSet(grpId, i + 7, 255, 12, 32);
    }
    fn_1_1E6A8();
    fn_1_1E51C(seat);
    anim = HuSprAnimDataRead(DATANUM(DATA_sdd1, 27));
    for (i = 0; i < 8; i++) {
        sprId = HuSprCreate(anim, 20, 0);
        HuSprGrpMemberSet(grpId, i + 15, sprId);
        if (SDTOUR->round[i] == 0) {
            HuSprPosSet(grpId, i + 15, lbl_1_data_1C24[i][0], lbl_1_data_1C24[i][1]);
        } else if (SDTOUR->round[i] == 1) {
            HuSprPosSet(grpId, i + 15, lbl_1_data_1C24[i / 2 + 16][0], lbl_1_data_1C24[i / 2 + 16][1]);
        } else {
            HuSprPosSet(grpId, i + 15, lbl_1_data_1C24[i / 4 + 24][0], lbl_1_data_1C24[i / 4 + 24][1]);
        }
        HuSprAttrSet(grpId, i + 15, HUSPR_ATTR_LINEAR);
        if (i == 0) {
            HuSprBankSet(grpId, i + 15, SDTOUR->charNo[i]);
        } else {
            bank = SDTOUR->charNo[i] - 32;
            HuSprBankSet(grpId, i + 15, lbl_1_data_1D14[bank]);
        }
    }
    lbl_1_bss_C20 = Hu3DModelCreateData(sdWorkInt[3] * 3 + DATA_sdd1 + sdWorkInt[6] + 10);
    Hu3DModelReflectTypeSet(lbl_1_bss_C20, 2);
    Hu3DModelCameraSet(lbl_1_bss_C20, HU3D_CAM2);
    pos2d.x = lbl_1_data_1C24[29][0];
    pos2d.y = lbl_1_data_1C24[29][1] - 48.0f;
    pos2d.z = 700.0f;
    Hu3D2Dto3D(&pos2d, HU3D_CAM2, &pos3d);
    Hu3DModelPosSetV(lbl_1_bss_C20, &pos3d);
    modelP = &Hu3DData[lbl_1_bss_C20];
    PSMTXTrans(modelP->mtx, 0.0f, -50.0f, 0.0f);
    mtxRotCat(modelP->mtx, -5.0f, 0.0f, 5.0f);
    lbl_1_bss_C22[0] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 0));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    lbl_1_bss_C22[1] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 1));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    lbl_1_bss_C22[2] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 2));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    lbl_1_bss_C22[3] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 3));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    lbl_1_bss_C22[4] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 5));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    lbl_1_bss_C22[5] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdd1, 21));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    lbl_1_bss_C0C = HuMemDirectMallocNum(HEAP_HEAP, GXGetTexBufferSize(480, 360, GX_TF_RGB5A3, GX_FALSE, 0), HU_MEMNUM_OVL);
    Hu3DLayerHookSet(2, fn_1_1E090);
    lbl_1_bss_C08 = anim = HuSprAnimMake(480, 360, 2);
    anim->bmp->data = lbl_1_bss_C0C;
    HuSprExecLayerCameraSet(74, 1, 10);
    sprId = HuSprCreate(lbl_1_bss_C08, 20, 0);
    HuSprGrpMemberSet(grpId, 23, sprId);
    HuSprAttrSet(grpId, 23, HUSPR_ATTR_LINEAR);
    HuSprPosSet(grpId, 23, 288.0f, 240.0f);
    HuSprScaleSet(grpId, 23, 1.2f, 1.3333334f);
    HuSprColorSet(grpId, 23, 96, 96, 96);
    HuSprDrawNoSet(grpId, 23, 74);
    sprId = HuSprCreate(lbl_1_bss_C08, 19, 0);
    HuSprGrpMemberSet(grpId, 24, sprId);
    HuSprAttrSet(grpId, 24, HUSPR_ATTR_LINEAR);
    HuSprPosSet(grpId, 24, 216.0f, 180.0f);
    HuSprScaleSet(grpId, 24, 0.927f, 1.03f);
    HuSprExecLayerCameraSet(75, 1, 8);
    HuSprDrawNoSet(grpId, 24, 75);
    HuSprTPLvlSet(grpId, 24, 0.7f);
    Hu3DAnimCreate(anim, lbl_1_bss_C22[0], "dummy");
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 40.0f, 30.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 480.0f, 360.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM0, 0, 0, 480, 360);
    omCameraViewSetMulti(HU3D_CAM0, &lbl_1_data_1D80);
    lbl_1_bss_C14 = HuPrcChildCreate(fn_1_1E2E0, 1000, 0x3000, 0, HuPrcCurrentGet());
    lbl_1_bss_C18 = HuPrcChildCreate(fn_1_1E0EC, 1000, 0x3000, 0, HuPrcCurrentGet());
}

/* 58 insns */
void fn_1_1DFA8(void)
{
    s16 i;

    HuSprGrpKill(lbl_1_bss_C32);
    HuWinKill(lbl_1_bss_C2E[0]);
    HuWinKill(lbl_1_bss_C2E[1]);
    Hu3DModelKill(lbl_1_bss_C20);
    HuPrcKill(lbl_1_bss_C18);
    for (i = 0; i < 6; i++) {
        Hu3DModelKill(lbl_1_bss_C22[i]);
    }
    HuSprAnimKill(lbl_1_bss_C08);
    HuMemDirectFree(lbl_1_bss_C0C);
    HuPrcKill(lbl_1_bss_C14);
    Hu3DLayerHookReset(2);
    Hu3DLayerHookReset(10);
}

/* 23 insns */
void fn_1_1E090(s16 layerNo)
{
    if (Hu3DCameraNo == 0) {
        Hu3DFbCopyExec(0, 0, 480, 360, GX_TF_RGB5A3, 0, lbl_1_bss_C0C);
        Hu3DZClear();
    }
}

/* 26 insns */
void fn_1_1E0EC(void)
{
    float rotY = 0.0f;

    while (1) {
        Hu3DModelRotSet(lbl_1_bss_C20, 0.0f, rotY, 0.0f);
        rotY += 1.0;
        HuPrcVSleep();
    }
}

/* 99 insns */
void fn_1_1E154(void)
{
    u16 seat[2];
    HUPROCESS *process;
    float scale;
    u16 angle;
    u16 prop;

    process = HuPrcCurrentGet();
    scale = 1.0f;
    prop = (u32)process->property;
    seat[0] = prop >> 8;
    seat[1] = prop & 0xFF;
    angle = 0;
    process->property = NULL;
    while (1) {
        if (lbl_1_bss_C10 != 0) {
            break;
        }
        scale = 0.9 + 0.1 * cos(M_PI * angle / 180.0);
        HuSprScaleSet(lbl_1_bss_C32, seat[0] + 15, scale, scale);
        HuSprScaleSet(lbl_1_bss_C32, seat[1] + 15, scale, scale);
        if (angle + 2 >= 360 && process->property != 0) {
            break;
        }
        angle += 2;
        if (angle > 360) {
            angle -= 360;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
    HuPrcVSleep();
}

/* 143 insns */
void fn_1_1E2E0(void)
{
    float rotX;
    float rotY;
    float zoom;
    float angleX;
    float angleY;
    float angleZoom;

    rotX = lbl_1_data_1D80.rot.x;
    rotY = lbl_1_data_1D80.rot.y;
    zoom = lbl_1_data_1D80.zoom;
    angleX = frandmod(360);
    angleY = frandmod(360);
    angleZoom = frandmod(360);
    while (1) {
        CRotM[0].x = rotX + 10.0 * sin(M_PI * angleX / 180.0);
        CRotM[0].y = rotY + angleY;
        CZoomM[0] = 0.7 * zoom + 0.3 * (zoom * sin(M_PI * angleZoom / 180.0));
        angleX += 0.1;
        if (angleX > 360.0f) {
            angleX -= 360.0f;
        }
        angleY += 0.05;
        if (angleY > 360.0f) {
            angleY -= 360.0f;
        }
        angleZoom += 0.1;
        if (angleZoom > 360.0f) {
            angleZoom -= 360.0f;
        }
        HuPrcVSleep();
    }
}

/* 99 insns */
s16 fn_1_1E51C(s16 *seat)
{
    s16 i;
    s16 j;
    s16 num;

    for (i = 0; i < 8; i += 2) {
        if (SDTOUR->round[i] == 0 && SDTOUR->round[i + 1] == 0) {
            seat[0] = i;
            seat[1] = i + 1;
            break;
        }
    }
    if (i != 8) {
        return 0;
    }
    for (i = 0; i < 8; i += 4) {
        num = j = 0;
        for (; j < 4; j++) {
            if (SDTOUR->round[i + j] == 1) {
                seat[num] = i + j;
                num++;
            }
        }
        if (num >= 2) {
            break;
        }
    }
    if (i != 8) {
        return 1;
    }
    for (i = num = 0; i < 8; i++) {
        if (SDTOUR->round[i] == 2) {
            seat[num] = i;
            num++;
        }
    }
    if (num == 2) {
        return 2;
    }
    return -1;
}

/* 118 insns */
s16 fn_1_1E6A8(void)
{
    s16 i;
    s16 sel;

    sel = -1;
    for (i = 0; i < 8; i++) {
        if (SDTOUR->round[i] != 0) {
            if (HuSprAttrGet(lbl_1_bss_C32, i + 7) & HUSPR_ATTR_DISPOFF) {
                sel = i + 7;
            }
            HuSprAttrReset(lbl_1_bss_C32, i + 7, HUSPR_ATTR_DISPOFF);
        }
        if (SDTOUR->round[i] > 1) {
            if (HuSprAttrGet(lbl_1_bss_C32, i / 2 + 3) & HUSPR_ATTR_DISPOFF) {
                sel = i / 2 + 3;
            }
            HuSprAttrReset(lbl_1_bss_C32, i / 2 + 3, HUSPR_ATTR_DISPOFF);
        }
        if (SDTOUR->round[i] > 2) {
            if (HuSprAttrGet(lbl_1_bss_C32, i / 4 + 1) & HUSPR_ATTR_DISPOFF) {
                sel = i / 4 + 1;
            }
            HuSprAttrReset(lbl_1_bss_C32, i / 4 + 1, HUSPR_ATTR_DISPOFF);
        }
    }
    return sel;
}

/* 615 insns */
void fn_1_1E880(s16 winner, s16 loser, s16 sprNo)
{
    float tpLvl;
    float posX;
    float posY;
    s16 i;
    s16 round;
    s32 seNo;

    HuAudFXPlay(0x51A);
    for (i = 1; i <= 20; i++) {
        tpLvl = sin(M_PI * (90.0 * (i / 20.0)) / 180.0);
        HuSprTPLvlSet(lbl_1_bss_C32, sprNo, tpLvl);
        HuPrcVSleep();
    }
    for (i = 1; i <= 15; i++) {
        tpLvl = 24.0 * (1.0 - i / 15.0);
        if (SDTOUR->round[loser] == 0) {
            HuSprPosSet(lbl_1_bss_C32, loser + 15, lbl_1_data_1C24[loser][0], lbl_1_data_1C24[loser][1] - tpLvl);
        } else if (SDTOUR->round[loser] == 1) {
            HuSprPosSet(lbl_1_bss_C32, loser + 15, lbl_1_data_1C24[loser / 2 + 16][0], lbl_1_data_1C24[loser / 2 + 16][1] - tpLvl);
        } else {
            HuSprPosSet(lbl_1_bss_C32, loser + 15, lbl_1_data_1C24[loser / 4 + 24][0], lbl_1_data_1C24[loser / 4 + 24][1] - tpLvl);
        }
        HuPrcVSleep();
    }
    seNo = HuAudFXPlay(0x51B);
    round = SDTOUR->round[winner] - 1;
    for (i = 1; i <= 15; i++) {
        tpLvl = i / 15.0;
        if (round == 0) {
            posX = lbl_1_data_1C24[winner][0];
            posX += tpLvl * (lbl_1_data_1C24[winner + 8][0] - posX);
            posY = lbl_1_data_1C24[winner][1] - 16.0f;
            posY += tpLvl * (lbl_1_data_1C24[winner + 8][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        } else if (round == 1) {
            posX = lbl_1_data_1C24[winner / 2 + 16][0];
            posX += tpLvl * (lbl_1_data_1C24[winner / 2 + 20][0] - posX);
            posY = lbl_1_data_1C24[winner / 2 + 16][1] - 16.0f;
            posY += tpLvl * (lbl_1_data_1C24[winner / 2 + 20][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        } else {
            posX = lbl_1_data_1C24[winner / 4 + 24][0];
            posX += tpLvl * (lbl_1_data_1C24[winner / 4 + 26][0] - posX);
            posY = lbl_1_data_1C24[winner / 4 + 24][1] - 16.0f;
            posY += tpLvl * (lbl_1_data_1C24[winner / 4 + 26][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        }
        HuPrcVSleep();
    }
    for (i = 1; i <= 15; i++) {
        tpLvl = i / 15.0;
        if (round == 0) {
            posX = lbl_1_data_1C24[winner + 8][0];
            posX += tpLvl * (lbl_1_data_1C24[winner / 2 + 16][0] - posX);
            posY = lbl_1_data_1C24[winner + 8][1];
            posY += tpLvl * (lbl_1_data_1C24[winner / 2 + 16][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        } else if (round == 1) {
            posX = lbl_1_data_1C24[winner / 2 + 20][0];
            posX += tpLvl * (lbl_1_data_1C24[winner / 4 + 24][0] - posX);
            posY = lbl_1_data_1C24[winner / 2 + 20][1];
            posY += tpLvl * (lbl_1_data_1C24[winner / 4 + 24][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        } else {
            posX = lbl_1_data_1C24[winner / 4 + 26][0];
            posX += tpLvl * (lbl_1_data_1C24[28][0] - posX);
            posY = lbl_1_data_1C24[winner / 4 + 26][1];
            posY += tpLvl * (lbl_1_data_1C24[28][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
        }
        HuPrcVSleep();
    }
    if (round == 2) {
        for (i = 1; i <= 5; i++) {
            tpLvl = i / 5.0;
            posX = lbl_1_data_1C24[winner / 4 + 28][0];
            posX += tpLvl * (lbl_1_data_1C24[29][0] - posX);
            posY = lbl_1_data_1C24[winner / 4 + 28][1];
            posY += tpLvl * (lbl_1_data_1C24[29][1] - posY);
            HuSprPosSet(lbl_1_bss_C32, winner + 15, posX, posY);
            HuPrcVSleep();
        }
    }
    HuAudFXStop(seNo);
}

/* 348 insns */
void fn_1_1F21C(void)
{
    s16 list[12];
    s16 *list3;
    s16 *list2;
    s16 *list1;
    s16 *num;
    s16 i;
    s16 j;
    s16 charNo;

    charNo = SDTOUR->charNo[0] = GwSdCommon.machine[sdWorkInt[7]].charNo;
    for (i = 1; i < 8; i++) {
        SDTOUR->charNo[i] = 43;
    }
    if (sdWorkInt[3] == 0) {
        list3 = lbl_1_data_1D32;
        list2 = lbl_1_data_1D36;
        list1 = lbl_1_data_1D3E;
        num = lbl_1_data_1D2C;
    } else if (sdWorkInt[3] == 1) {
        list3 = lbl_1_data_1D4E;
        list2 = lbl_1_data_1D54;
        list1 = lbl_1_data_1D5A;
        num = lbl_1_data_1D48;
    } else {
        list3 = lbl_1_data_1D6A;
        list2 = lbl_1_data_1D6E;
        list1 = lbl_1_data_1D76;
        num = lbl_1_data_1D64;
    }
    for (i = 0; i < num[0]; i++) {
        if (charNo == lbl_1_data_1D14[list3[i] - 32]) {
            for (j = i; j < num[0]; j++) {
                list3[j] = list3[j + 1];
            }
            num[0]--;
            break;
        }
    }
    for (i = 0; i < num[1]; i++) {
        if (charNo == lbl_1_data_1D14[list2[i] - 32]) {
            for (j = i; j < num[1]; j++) {
                list2[j] = list2[j + 1];
            }
            num[1]--;
            break;
        }
    }
    for (i = 0; i < num[2]; i++) {
        if (charNo == lbl_1_data_1D14[list1[i] - 32]) {
            for (j = i; j < num[2]; j++) {
                list1[j] = list1[j + 1];
            }
            num[2]--;
            break;
        }
    }
    if (sdWorkInt[6] == 0) {
        fn_1_1F78C(list1, num[2]);
        SDTOUR->charNo[frandmod(2) + 4] = list1[0];
        SDTOUR->charNo[frandmod(2) + 6] = list1[1];
    } else if (sdWorkInt[6] == 1) {
        fn_1_1F78C(list2, num[1]);
        fn_1_1F78C(list1, num[2]);
        if (list2[0] == 32 && !GwSdCommon.extCharSelF) {
            list[0] = list2[1];
        } else {
            list[0] = list2[0];
        }
        list[1] = list1[0];
        list[2] = list1[1];
        fn_1_1F78C(list, 3);
        SDTOUR->charNo[frandmod(2) + 2] = list[0];
        SDTOUR->charNo[frandmod(2) + 4] = list[1];
        SDTOUR->charNo[frandmod(2) + 6] = list[2];
    } else {
        fn_1_1F78C(list3, num[0]);
        fn_1_1F78C(list2, num[1]);
        fn_1_1F78C(list1, num[2]);
        SDTOUR->charNo[1] = list1[0];
        list[0] = list3[0];
        list[1] = list2[0];
        list[2] = list2[1];
        if (num[0] >= 2 && num[1] >= 3) {
            list[3] = frandmod(2) == 0 ? list3[1] : list2[2];
        } else if (num[0] >= 2) {
            list[3] = list3[1];
        } else {
            list[3] = list2[2];
        }
        list[4] = list1[1];
        list[5] = list1[2];
        fn_1_1F78C(list, 6);
        for (i = 0; i < 6; i++) {
            SDTOUR->charNo[i + 2] = list[i];
        }
    }
    for (i = 0; i < 8; i++) {
        OSReport("%d:%d\n", i, SDTOUR->charNo[i]);
    }
}

/* 40 insns */
void fn_1_1F78C(s16 *list, s16 num)
{
    s16 i;
    s16 a;
    s16 b;
    s16 tmp;

    if (num != 1) {
        for (i = 0; i < 100; i++) {
            a = frandmod(num);
            b = frandmod(num);
            tmp = list[a];
            list[a] = list[b];
            list[b] = tmp;
        }
    }
}

/* 77 insns */
s16 fn_1_1F82C(s16 charNo)
{
    s16 *list3;
    s16 *list2;
    s16 *num;
    s16 i;

    if (charNo == 43) {
        return 0;
    }
    if (sdWorkInt[3] == 0) {
        list3 = lbl_1_data_1D32;
        list2 = lbl_1_data_1D36;
        num = lbl_1_data_1D2C;
    } else if (sdWorkInt[3] == 1) {
        list3 = lbl_1_data_1D4E;
        list2 = lbl_1_data_1D54;
        num = lbl_1_data_1D48;
    } else {
        list3 = lbl_1_data_1D6A;
        list2 = lbl_1_data_1D6E;
        num = lbl_1_data_1D64;
    }
    for (i = 0; i < num[0]; i++) {
        if (charNo == list3[i]) {
            return 3;
        }
    }
    for (i = 0; i < num[1]; i++) {
        if (charNo == list2[i]) {
            return 2;
        }
    }
    return 1;
}

/* 438 insns */
void fn_1_1F960(s16 winner)
{
    GWSDCOMMON *sdCommon;
    HU3DMODEL *modelP;
    float scale;
    s16 i;
    s16 padNo;
    s32 allF;

    modelP = &Hu3DData[lbl_1_bss_C20];
    padNo = GwSdBattle.padNo[0];
    sdCommon = &GwSdCommon;
    Hu3DModelAttrReset(lbl_1_bss_C22[5], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(lbl_1_bss_C22[5], modelP->pos.x, modelP->pos.y, modelP->pos.z - 50.0f);
    if (lbl_1_bss_C1C != 0) {
        lbl_1_bss_C1C->property = (void *)1;
    }
    HuAudFXPlay(0x51E);
    for (i = 1; i <= 10; i++) {
        scale = 4.0 * sin(M_PI * (90.0 * (i / 10.0)) / 180.0);
        Hu3DModelScaleSet(lbl_1_bss_C22[5], scale, scale, scale);
        HuPrcVSleep();
    }
    for (i = 1; i <= 5; i++) {
        scale = 2.0 + 2.0 * cos(M_PI * (90.0 * (i / 5.0)) / 180.0);
        Hu3DModelScaleSet(lbl_1_bss_C22[5], scale, scale, scale);
        HuPrcVSleep();
    }
    if (winner == 0) {
        if (sdCommon->battleEasyWinF && sdCommon->battleNormalWinF && sdCommon->battleHardWinF && sdCommon->flagEasyWinF && sdCommon->flagNormalWinF && sdCommon->flagHardWinF && sdCommon->rabbitEasyWinF && sdCommon->rabbitNormalWinF && sdCommon->rabbitHardWinF) {
            allF = 1;
        } else {
            allF = 0;
        }
        if (sdWorkInt[3] == 0 && sdWorkInt[6] == 0) {
            sdCommon->battleEasyWinF = 1;
        }
        if (sdWorkInt[3] == 0 && sdWorkInt[6] == 1) {
            sdCommon->battleNormalWinF = 1;
        }
        if (sdWorkInt[3] == 0 && sdWorkInt[6] == 2) {
            sdCommon->battleHardWinF = 1;
        }
        if (sdWorkInt[3] == 1 && sdWorkInt[6] == 0) {
            sdCommon->flagEasyWinF = 1;
        }
        if (sdWorkInt[3] == 1 && sdWorkInt[6] == 1) {
            sdCommon->flagNormalWinF = 1;
        }
        if (sdWorkInt[3] == 1 && sdWorkInt[6] == 2) {
            sdCommon->flagHardWinF = 1;
        }
        if (sdWorkInt[3] == 2 && sdWorkInt[6] == 0) {
            sdCommon->rabbitEasyWinF = 1;
        }
        if (sdWorkInt[3] == 2 && sdWorkInt[6] == 1) {
            sdCommon->rabbitNormalWinF = 1;
        }
        if (sdWorkInt[3] == 2 && sdWorkInt[6] == 2) {
            sdCommon->rabbitHardWinF = 1;
        }
        if (sdCommon->battleHardWinF) {
            GwCommon.unkSdFlag = 1;
        }
        if (sdCommon->flagHardWinF) {
            GwCommon.unkSdFlag2 = 1;
        }
        if (sdCommon->battleEasyWinF && sdCommon->battleNormalWinF && sdCommon->battleHardWinF && sdCommon->flagEasyWinF && sdCommon->flagNormalWinF && sdCommon->flagHardWinF && sdCommon->rabbitEasyWinF && sdCommon->rabbitNormalWinF && sdCommon->rabbitHardWinF && allF == 0) {
            sdCommon->newPart2F = 1;
        }
    }
    HuWinMesSet(lbl_1_bss_C2E[1], 0x2000B);
    HuWinDispOn(lbl_1_bss_C2E[1]);
    GwSdCommon.picNo++;
    if (GwSdCommon.picNo > 999) {
        GwSdCommon.picNo = 0;
    }
    while (!(fn_1_4FD0(1 << padNo) & PAD_BUTTON_B)) {
        HuPrcVSleep();
    }
}

/* 178 insns */
s16 fn_1_20038(s16 *seat)
{
    s16 rank[2];
    s16 i;
    s16 diff;

    for (i = 0; i < 2; i++) {
        rank[i] = fn_1_1F82C(SDTOUR->charNo[seat[i]]);
    }
    diff = rank[0] - rank[1];
    if (diff == 0) {
        return frandmod(2);
    }
    if (diff == 1) {
        return frandmod(10) < 7 ? 0 : 1;
    }
    if (diff == 2) {
        return frandmod(10) < 9 ? 0 : 1;
    }
    if (diff == 3) {
        return frandmod(100) < 95 ? 0 : 1;
    }
    if (diff == -1) {
        return frandmod(10) < 7 ? 1 : 0;
    }
    if (diff == -2) {
        return frandmod(10) < 9 ? 1 : 0;
    }
    if (diff == -3) {
        return frandmod(100) < 95 ? 1 : 0;
    }
    return -1;
}

/* 280 insns */
void fn_1_20300(void)
{
    float scale;
    HUPROCESS *process;
    s16 dir;
    HUWINID winId;
    s16 i;
    s16 padNo;

    padNo = GwSdBattle.padNo[0];
    lbl_1_bss_C02 = 1;
    for (i = 0; i < 8; i++) {
        HuSprScaleSet(lbl_1_bss_C32, i + 15, 0.8f, 0.8f);
    }
    lbl_1_bss_C04 = 1.0f;
    process = HuPrcChildCreate(fn_1_20760, 1500, 0x2000, 0, HuPrcCurrentGet());
    lbl_1_bss_C00 = 0;
    HuWinMesSet(lbl_1_bss_C2E[1], 0x20004);
    while (1) {
        dir = 0;
        if ((fn_1_507C(1 << padNo) & PAD_BUTTON_LEFT) && lbl_1_bss_C02 > 1) {
            dir = -1;
        } else if ((fn_1_507C(1 << padNo) & PAD_BUTTON_RIGHT) && lbl_1_bss_C02 < 7) {
            dir = 1;
        }
        if (dir != 0) {
            HuAudFXPlay(0);
            lbl_1_bss_C00 = 1;
            for (i = 1; i <= 10; i++) {
                scale = 0.8 + (lbl_1_bss_C04 - 0.8) * (1.0 - i / 10.0);
                HuSprScaleSet(lbl_1_bss_C32, lbl_1_bss_C02 + 15, scale, scale);
                scale = 0.8 + 0.2 * (i / 10.0);
                HuSprScaleSet(lbl_1_bss_C32, lbl_1_bss_C02 + 15 + dir, scale, scale);
                HuPrcVSleep();
            }
            lbl_1_bss_C02 += dir;
            lbl_1_bss_C00 = 0;
        } else if (fn_1_4FD0(1 << padNo) & PAD_BUTTON_A) {
            HuAudFXPlay(1);
            winId = HuWinCreate(-10000.0f, 320.0f, 512, 94, 0);
            HuWinMesSpeedSet(winId, 0);
            HuWinPriSet(winId, 10);
            HuWinMesSet(winId, SDTOUR->charNo[lbl_1_bss_C02] + 0x1DFFE0);
            HuWinMesWait(winId);
            HuWinKill(winId);
        } else if (fn_1_4FD0(1 << padNo) & PAD_BUTTON_B) {
            break;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(3);
    HuPrcKill(process);
    for (i = 0; i < 8; i++) {
        HuSprScaleSet(lbl_1_bss_C32, i + 15, 1.0f, 1.0f);
    }
}

/* 68 insns */
void fn_1_20760(void)
{
    float angle = 0.0f;

    while (1) {
        if (lbl_1_bss_C00 == 0) {
            lbl_1_bss_C04 = 0.8 + 0.2 * cos(M_PI * angle / 180.0);
            HuSprScaleSet(lbl_1_bss_C32, lbl_1_bss_C02 + 15, lbl_1_bss_C04, lbl_1_bss_C04);
            angle += 10.0f;
            if (angle > 360.0f) {
                angle -= 360.0f;
            }
        } else {
            angle = 0.0f;
        }
        HuPrcVSleep();
    }
}

/* --- .data after the last user --- */
/* 0x1DAC */ s32 lbl_1_data_1DAC[12] = { 0x190060, 0x190061, 0x1, 0x0, 0x2, 0x4, 0x8, 0x3, 0x6, 0x5, 0x7, 0x9 };
