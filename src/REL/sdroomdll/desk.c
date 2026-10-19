/*
 * sdroomdll desk.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/desk.s.
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
#include "game/armem.h"
#include "math.h"
#ifndef __MWERKS__
#include "stdio.h" /* retail calls sprintf unprototyped (no crclr); host needs the prototype */
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_9B8 = 0.0f; /* 0x9B8 */
static const double lbl_1_rodata_9C0 = 0.5; /* 0x9C0 */
static const double lbl_1_rodata_9C8 = 10.0; /* 0x9C8 */
static const float lbl_1_rodata_9D0 = 3000.0f; /* 0x9D0 */
static const float lbl_1_rodata_9D4 = 7000.0f; /* 0x9D4 */
static const double lbl_1_rodata_9D8 = 1.0; /* 0x9D8 */
/* 0x9E0 lbl_1_rodata_9E0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_9E8 = -1000.0f; /* 0x9E8 */
static const float lbl_1_rodata_9EC = 210.0f; /* 0x9EC */
static const float lbl_1_rodata_9F0 = 72.0f; /* 0x9F0 */
static const float lbl_1_rodata_9F4 = 48.0f; /* 0x9F4 */
static const float lbl_1_rodata_9F8 = 32.0f; /* 0x9F8 */
static const float lbl_1_rodata_9FC = 296.0f; /* 0x9FC */
static const float lbl_1_rodata_A00 = 16.0f; /* 0xA00 */
static const float lbl_1_rodata_A04 = 354.0f; /* 0xA04 */
static const float lbl_1_rodata_A08 = 464.0f; /* 0xA08 */
static const float lbl_1_rodata_A0C = 240.0f; /* 0xA0C */
static const float lbl_1_rodata_A10 = 280.0f; /* 0xA10 */
static const float lbl_1_rodata_A14 = 320.0f; /* 0xA14 */
static const float lbl_1_rodata_A18 = 1.0f; /* 0xA18 */
static const float lbl_1_rodata_A1C = -1.0f; /* 0xA1C */
static const float lbl_1_rodata_A20 = 54.0f; /* 0xA20 */
static const float lbl_1_rodata_A24 = 224.0f; /* 0xA24 */
static const float lbl_1_rodata_A28 = 5.0f; /* 0xA28 */
static const float lbl_1_rodata_A2C = 20.0f; /* 0xA2C */
static const float lbl_1_rodata_A30 = 15000.0f; /* 0xA30 */
static const float lbl_1_rodata_A34 = 1.2f; /* 0xA34 */
static const float lbl_1_rodata_A38 = -3.5555496f; /* 0xA38 */
static const float lbl_1_rodata_A3C = 256.0f; /* 0xA3C */
static const float lbl_1_rodata_A40 = 192.0f; /* 0xA40 */
static const float lbl_1_rodata_A44 = 0.8f; /* 0xA44 */
static const float lbl_1_rodata_A48 = 8.0f; /* 0xA48 */
static const float lbl_1_rodata_A4C = 288.0f; /* 0xA4C */
static const float lbl_1_rodata_A50 = 160.0f; /* 0xA50 */
static const float lbl_1_rodata_A54 = 151.0f; /* 0xA54 */
static const float lbl_1_rodata_A58 = 10.0f; /* 0xA58 */
static const float lbl_1_rodata_A5C = 1.5f; /* 0xA5C */
static const float lbl_1_rodata_A60 = 75.0f; /* 0xA60 */
static const float lbl_1_rodata_A64 = 0.45f; /* 0xA64 */
static const float lbl_1_rodata_A68 = 50.0f; /* 0xA68 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x19FE */ s16 lbl_1_bss_19FE[7];
/* 0x19EA */ s16 lbl_1_bss_19EA[10];
/* 0x19D6 */ s16 lbl_1_bss_19D6[10];
/* 0x19D4 */ s16 lbl_1_bss_19D4;
/* 0x19D2 */ s16 lbl_1_bss_19D2;
/* 0x19CE */ s16 lbl_1_bss_19CE[2]; /* [1] is accessed at +2 (dtk gap_05_000019D0) */
/* 0x19C8 */ char lbl_1_bss_19C8[0x6]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0x19C2 */ char lbl_1_bss_19C2[0x6]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0x1990 */ char lbl_1_bss_1990[10][5]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0x198E */ s16 lbl_1_bss_198E;
/* 0x198C */ s16 lbl_1_bss_198C;
/* 0x198A */ s16 lbl_1_bss_198A; /* unreferenced (dtk gap_05_0000198A); a guess: an unused variable */
/* 0x1988 */ s16 lbl_1_bss_1988;
/* 0x1984 */ HUPROCESS *lbl_1_bss_1984;
/* 0x1982 gap_05_00001982_bss (0x2): alignment gap */
/* 0x1980 */ s16 lbl_1_bss_1980;

/* --- functions (reference order), .data placed before its first user --- */
/* 133 insns */
void fn_1_256B4(void)
{
    s16 choice;

    HuWinExOpen(lbl_1_bss_570[0]);
    while (1) {
        if (omovlevtno != 1) {
            fn_1_28104();
        }
        HuWinMesSet(lbl_1_bss_570[0], 0x190006);
        HuWinMesWait(lbl_1_bss_570[0]);
        if (omovlevtno != 1) {
            choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
        } else {
            choice = HuWinChoiceGet(lbl_1_bss_570[0], 1);
        }
        omovlevtno = 0;
        if (choice == 2 || choice == -1) {
            break;
        }
        if (choice == 0) {
            HuWinExClose(lbl_1_bss_570[0]);
            fn_1_25B58();
            HuWinExOpen(lbl_1_bss_570[0]);
        } else if (choice == 1) {
            if (GwSdCommon.partFlag[0] == 0 || GwSdCommon.partFlag[1] == 0 || GwSdCommon.partFlag[2] == 0 || GwSdCommon.partFlag[3] == 0) {
                HuWinMesSet(lbl_1_bss_570[0], 0x190075);
                HuWinMesWait(lbl_1_bss_570[0]);
            } else {
                HuWinMesSet(lbl_1_bss_570[0], 0x190007);
                HuWinMesWait(lbl_1_bss_570[0]);
                choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
                if (choice == 0) {
                    HuPrcSleep(30);
                    fn_1_258C8();
                    fn_1_4238(1);
                }
            }
        }
    }
    HuWinExClose(lbl_1_bss_570[0]);
}

/* 164 insns */
void fn_1_258C8(void)
{
    s16 list[13];
    s16 i;
    s16 j;
    s16 type;
    s16 num;
    GWSDMACHINE *machine;

    GwSdBattle.gameType = 0;
    GwSdBattle.stageNo = 0;
    GwPlayerConf[0].type = 0;
    GwSdBattle.stageType1 = 0;
    GwSdBattle.machine[0].charNo = frandmod(7);
    if (HuPadErr[1] == 0) {
        GwPlayerConf[1].type = 0;
        GwSdBattle.stageType2 = 0;
        for (j = 0; j < 100; j++) {
            i = frandmod(7);
            if (i != GwSdBattle.machine[0].charNo) {
                break;
            }
        }
        if (j == 100) {
            i = GwSdBattle.machine[0].charNo + 1;
        }
        if (i >= 7) {
            i = 0;
        }
        GwSdBattle.machine[1].charNo = i;
    } else {
        GwPlayerConf[1].type = 1;
        GwSdBattle.stageType2 = 1;
        GwPlayerConf[1].dif = 0;
        GwSdBattle.machine[1].charNo = 9;
    }
    for (i = 0; i < 2; i++) {
        GwSdBattle.padNo[i] = i;
        GwPlayerConf[i].padNo = i;
        machine = &GwSdBattle.machine[i];
        for (type = 0; type < 4; type++) {
            for (j = num = 0; j < lbl_1_data_4F4[type]; j++) {
                if (GwSdCommon.partFlag[type] & (1 << j)) {
                    list[num] = j;
                    num++;
                }
            }
            machine->partNo[type] = list[frandmod(num)];
        }
    }
}

/* 391 insns */
void fn_1_25B58(void)
{
    s16 i;
    s16 ofs;
    s16 dir;

    lbl_1_bss_5B8 = 0.0f;
    Hu3DLayerHookSet(13, fn_1_484C);
    for (i = 1; i <= 10; i++) {
        lbl_1_bss_5B8 = 0.5 * (i / 10.0);
        HuPrcVSleep();
    }
    lbl_1_bss_19D4 = 0;
    lbl_1_bss_1980 = 0;
    fn_1_266A4();
    fn_1_26174();
    lbl_1_bss_19D2 = ofs = 0;
    while (1) {
        dir = 0;
        if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
            ofs--;
            dir = -1;
            if (ofs < 0) {
                if (lbl_1_bss_19D2 != 0) {
                    lbl_1_bss_19D2--;
                } else {
                    dir = 0;
                }
                ofs = 0;
            }
        } else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
            ofs++;
            dir = 1;
            if (ofs >= 5) {
                if (lbl_1_bss_19D2 + 5 < lbl_1_data_4F4[lbl_1_bss_19D4]) {
                    lbl_1_bss_19D2++;
                } else {
                    dir = 0;
                }
                ofs = 4;
            }
        } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            lbl_1_bss_19D4--;
            if (lbl_1_bss_19D4 < 0) {
                lbl_1_bss_19D4 = 3;
            }
            lbl_1_bss_19D2 = ofs = 0;
            dir = -10;
        } else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            lbl_1_bss_19D4++;
            if (lbl_1_bss_19D4 >= 4) {
                lbl_1_bss_19D4 = 0;
            }
            lbl_1_bss_19D2 = ofs = 0;
            dir = 10;
        }
        if (dir != 0) {
            HuAudFXPlay(0);
            lbl_1_bss_1980 = lbl_1_bss_19D2 + ofs;
            fn_1_271EC(lbl_1_bss_19D4, lbl_1_bss_19D2);
            fn_1_279F8(lbl_1_bss_19D4, lbl_1_bss_1980);
            fn_1_27004(lbl_1_bss_19D4);
            fn_1_2709C(lbl_1_bss_19FE[5], lbl_1_bss_19D4);
        }
        CZoomM[3] += HuPadTrigL[0] / 2;
        CZoomM[3] -= HuPadTrigR[0] / 2;
        if (CZoomM[3] < 3000.0f) {
            CZoomM[3] = 3000.0f;
        }
        if (CZoomM[3] > 7000.0f) {
            CZoomM[3] = 7000.0f;
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_A) {
            if (fn_1_414C(lbl_1_bss_19D4, lbl_1_bss_1980) == 0) {
                HuAudFXPlay(1);
                fn_1_27D80(lbl_1_bss_19D4, lbl_1_bss_1980);
            } else {
                HuAudFXPlay(4);
            }
        }
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            break;
        }
        HuPrcVSleep();
    }
    fn_1_264C0();
    fn_1_26DAC();
    for (i = 1; i <= 10; i++) {
        lbl_1_bss_5B8 = 0.5 * (1.0 - i / 10.0);
        HuPrcVSleep();
    }
    Hu3DLayerHookReset(13);
    Hu3DLayerHookReset(5);
    for (i = GwSdCommon.prevPoint = 0; i < 4; i++) {
        GwSdCommon.prevPoint += GwCommon.sdPoint[i];
    }
}

/* 211 insns */
void fn_1_26174(void)
{
    s16 i;
    float scale;

    HuSprGrpPosSet(lbl_1_bss_1988, 0.0f, -1000.0f);
    HuWinDispOff(lbl_1_bss_19FE[0]);
    HuWinDispOff(lbl_1_bss_19FE[1]);
    HuWinDispOff(lbl_1_bss_19FE[2]);
    HuWinDispOff(lbl_1_bss_19FE[5]);
    for (i = 0; i < 10; i++) {
        HuWinDispOff(lbl_1_bss_19EA[i]);
        HuWinDispOff(lbl_1_bss_19D6[i]);
    }
    if (lbl_1_bss_19CE[0] != -1) {
        Hu3DModelScaleSet(lbl_1_bss_19CE[0], 0.0f, 0.0f, 0.0f);
    }
    if (lbl_1_bss_19CE[1] != -1) {
        Hu3DModelScaleSet(lbl_1_bss_19CE[1], 0.0f, 0.0f, 0.0f);
    }
    HuWinExOpen(lbl_1_bss_19FE[3]);
    HuWinExOpen(lbl_1_bss_19FE[4]);
    HuWinExOpen(lbl_1_bss_19FE[6]);
    HuWinDispOn(lbl_1_bss_19FE[0]);
    HuWinDispOn(lbl_1_bss_19FE[1]);
    HuWinDispOn(lbl_1_bss_19FE[2]);
    HuWinDispOn(lbl_1_bss_19FE[5]);
    HuSprGrpPosSet(lbl_1_bss_1988, 0.0f, 0.0f);
    fn_1_271EC(lbl_1_bss_19D4, 0);
    fn_1_27730(210.0f, 72.0f);
    for (i = 0; i < 10; i++) {
        HuWinDispOn(lbl_1_bss_19EA[i]);
        HuWinDispOn(lbl_1_bss_19D6[i]);
    }
    for (i = 1; i <= 10; i++) {
        scale = i / 10.0;
        if (lbl_1_bss_19CE[0] != -1) {
            Hu3DModelScaleSet(lbl_1_bss_19CE[0], scale, scale, scale);
        }
        if (lbl_1_bss_19CE[1] != -1) {
            Hu3DModelScaleSet(lbl_1_bss_19CE[1], scale, scale, scale);
        }
        HuPrcVSleep();
    }
}

/* 121 insns */
void fn_1_264C0(void)
{
    s16 i;
    float scale;

    for (i = 1; i <= 10; i++) {
        scale = 1.0 - i / 10.0;
        if (lbl_1_bss_19CE[0] != -1) {
            Hu3DModelScaleSet(lbl_1_bss_19CE[0], scale, scale, scale);
        }
        if (lbl_1_bss_19CE[1] != -1) {
            Hu3DModelScaleSet(lbl_1_bss_19CE[1], scale, scale, scale);
        }
        HuPrcVSleep();
    }
    HuSprGrpPosSet(lbl_1_bss_1988, 0.0f, -1000.0f);
    for (i = 0; i < 10; i++) {
        HuWinDispOff(lbl_1_bss_19EA[i]);
        HuWinDispOff(lbl_1_bss_19D6[i]);
    }
    HuWinDispOff(lbl_1_bss_19FE[0]);
    HuWinDispOff(lbl_1_bss_19FE[1]);
    HuWinDispOff(lbl_1_bss_19FE[2]);
    HuWinDispOff(lbl_1_bss_19FE[5]);
    HuWinExClose(lbl_1_bss_19FE[3]);
    HuWinExClose(lbl_1_bss_19FE[4]);
    HuWinExClose(lbl_1_bss_19FE[6]);
}

/* 0x2188 */ OMCAMERAVIEW lbl_1_data_2188 = { { 0.0f, 70.0f, 0.0f }, { -30.0f, 0.0f, 0.0f }, 5300.0f };

/* 450 insns */
void fn_1_266A4(void)
{
    HUWINID winId;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s16 i;
    ANIMDATA *anim;

    winPrio = 1000;
    fn_1_3F00();
    winId = HuWinCreate(48.0f, 32.0f, 320, 40, 0);
    lbl_1_bss_19FE[0] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x190026);
    winId = HuWinCreate(296.0f, 32.0f, 258, 40, 0);
    lbl_1_bss_19FE[1] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    fn_1_27004(lbl_1_bss_19D4);
    winId = HuWinCreate(16.0f, 354.0f, 320, 88, 0);
    lbl_1_bss_19FE[2] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x20018);
    winId = HuWinExCreate(16.0f, 72.0f, 192, 192, -1);
    lbl_1_bss_19FE[3] = winId;
    HuWinDrawNoSet(winId, 64);
    HuWinMesSpeedSet(winId, 0);
    winId = HuWinExCreate(210.0f, 72.0f, 346, 208, -1);
    lbl_1_bss_19FE[4] = winId;
    HuWinMesSpeedSet(winId, 0);
    winId = HuWinCreate(464.0f, 240.0f, 126, 48, 0);
    lbl_1_bss_19FE[5] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    fn_1_2709C(winId, lbl_1_bss_19D4);
    winId = HuWinExCreate(210.0f, 280.0f, 346, 146, -1);
    lbl_1_bss_19FE[6] = winId;
    HuWinMesSpeedSet(winId, 0);
    for (i = 0; i < 10; i++) {
        winId = HuWinCreate(0.0f, 0.0f, 406, 40, 0);
        lbl_1_bss_19EA[i] = winId;
        HuWinBGTPLvlSet(winId, 0.0f);
        HuWinMesSpeedSet(winId, 0);
        winId = HuWinCreate(0.0f, 0.0f, 94, 40, 0);
        lbl_1_bss_19D6[i] = winId;
        HuWinBGTPLvlSet(winId, 0.0f);
        HuWinMesSpeedSet(winId, 0);
    }
    lbl_1_bss_19CE[0] = lbl_1_bss_19CE[1] = -1;
    lbl_1_bss_1984 = HuPrcChildCreate(fn_1_26F0C, 1000, 0x1000, 0, HuPrcCurrentGet());
    fn_1_279F8(0, 0);
    Hu3DModelAttrSet(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
    anim = HuSprAnimDataRead(DATANUM(DATA_win, 2));
    grpId = HuSprGrpCreate(5);
    lbl_1_bss_1988 = grpId;
    sprId = HuSprCreate(anim, 100, 19);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 320.0f, 240.0f);
    HuSprScaleSet(grpId, 0, 1.0f, -1.0f);
    sprId = HuSprCreate(anim, 100, 19);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 320.0f, 240.0f);
    anim = HuSprAnimDataRead(DATANUM(DATA_win, 1));
    sprId = HuSprCreate(anim, 100, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprPosSet(grpId, 2, 320.0f, 240.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 50)), 20, 0);
    HuSprGrpMemberSet(grpId, 3, sprId);
    HuSprPosSet(grpId, 3, 32.0f, 54.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 51)), 20, 0);
    HuSprGrpMemberSet(grpId, 4, sprId);
    HuSprPosSet(grpId, 4, 224.0f, 54.0f);
    HuSprGrpDrawNoSet(grpId, 0);
    Hu3DCameraPerspectiveSet(8, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(8, -3.5555496f, 72.0f, 256.0f, 192.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 22, 76, 204, 184);
    omCameraViewSetMulti(8, &lbl_1_data_2188);
    HuDataDirClose(DATA_sdroom);
}

/* 88 insns */
void fn_1_26DAC(void)
{
    s16 i;

    for (i = 0; i < 7; i++) {
        HuWinKill(lbl_1_bss_19FE[i]);
    }
    for (i = 0; i < 10; i++) {
        HuWinKill(lbl_1_bss_19EA[i]);
        HuWinKill(lbl_1_bss_19D6[i]);
    }
    HuPrcKill(lbl_1_bss_1984);
    Hu3DModelAttrReset(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
    HuSprGrpKill(lbl_1_bss_1988);
    if (lbl_1_bss_19CE[0] != -1) {
        Hu3DModelKill(lbl_1_bss_19CE[0]);
    }
    if (lbl_1_bss_19CE[1] != -1) {
        Hu3DModelKill(lbl_1_bss_19CE[1]);
    }
}

/* 62 insns */
void fn_1_26F0C(void)
{
    s16 rot = 0;

    while (1) {
        if (lbl_1_bss_19CE[0] >= 0) {
            Hu3DModelRotSet(lbl_1_bss_19CE[0], 0.0f, rot, 0.0f);
            if (lbl_1_bss_19CE[1] >= 0) {
                Hu3DModelRotSet(lbl_1_bss_19CE[1], 0.0f, rot, 0.0f);
            }
            rot += 2;
            if (rot > 360) {
                rot -= 360;
            }
        }
        HuPrcVSleep();
    }
}

/* 0x21A4 */ u32 lbl_1_data_21A4[4] = { DATANUM(DATA_donkey, 34), DATANUM(DATA_donkey, 36), DATANUM(DATA_donkey, 35), DATANUM(DATA_donkey, 37) };

/* 38 insns */
void fn_1_27004(s16 a0)
{
    sprintf(lbl_1_bss_19C8, "%03d", GwCommon.sdPoint[a0]);
    HuWinInsertMesSet(lbl_1_bss_19FE[1], MESSNUM_PTR(lbl_1_bss_19C8), 0);
    HuWinMesSet(lbl_1_bss_19FE[1], lbl_1_data_21A4[a0]);
}

/* 84 insns */
void fn_1_2709C(HUWINID winId, s16 type)
{
    s16 num;
    s16 i;

    for (i = num = 0; i < lbl_1_data_4F4[type]; i++) {
        if (GwSdCommon.partFlag[type] & (1 << i)) {
            num++;
        }
    }
    sprintf(lbl_1_bss_19C2, "%02d", num);
    sprintf(&lbl_1_bss_19C2[3], "%02d", lbl_1_data_4F4[type]);
    HuWinInsertMesSet(winId, MESSNUM_PTR(lbl_1_bss_19C2), 0);
    HuWinInsertMesSet(winId, MESSNUM_PTR(&lbl_1_bss_19C2[3]), 1);
    HuWinMesSet(winId, 0x19002C);
    HuWinScaleSet(winId, 0.8f, 0.8f);
}

/* 337 insns */
void fn_1_271EC(s16 a0, s16 a1)
{
    SDPARTDATA *part;
    s16 i;
    s16 status;
    float ofs;

    part = lbl_1_data_4E0[a0];
    part += a1;
    for (i = 0; i < 5; i++) {
        if (i + a1 > lbl_1_data_4F4[a0]) {
            HuWinHomeClear(lbl_1_bss_19EA[i]);
            HuWinHomeClear(lbl_1_bss_19D6[i]);
        } else {
            HuWinMesPalSet(lbl_1_bss_19EA[i], 7, 255, 255, 255);
            HuWinMesPalSet(lbl_1_bss_19D6[i], 7, 255, 255, 255);
            status = fn_1_414C(a0, a1 + i);
            if (status == 1) {
                HuWinMesSet(lbl_1_bss_19EA[i], 0x450007);
                HuWinHomeClear(lbl_1_bss_19D6[i]);
            } else {
                if (status == 2) {
                    HuWinMesPalSet(lbl_1_bss_19EA[i], 7, 0, 0, 0);
                    HuWinMesPalSet(lbl_1_bss_19D6[i], 7, 0, 0, 0);
                } else if (status == 3) {
                    HuWinMesPalSet(lbl_1_bss_19EA[i], 7, 192, 32, 32);
                    HuWinMesPalSet(lbl_1_bss_19D6[i], 7, 192, 32, 32);
                }
                HuWinMesSet(lbl_1_bss_19EA[i], part->mesNo);
                sprintf(lbl_1_bss_1990[i], "%02d", part->point);
                HuWinMesSet(lbl_1_bss_19D6[i], MESSNUM_PTR(lbl_1_bss_1990[i]));
            }
            part++;
        }
    }
    HuWinMesSet(lbl_1_bss_19FE[0], a0 + 0x190027);
    if (a1 + 5 < lbl_1_data_4F4[a0]) {
        HuSprAttrReset(lbl_1_bss_1988, 1, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_1988, 1, HUSPR_ATTR_DISPOFF);
    }
    if (a1 > 0) {
        HuSprAttrReset(lbl_1_bss_1988, 0, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_1988, 0, HUSPR_ATTR_DISPOFF);
    }
    if (lbl_1_bss_1980 >= 0) {
        HuSprAttrReset(lbl_1_bss_1988, 2, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_1988, 2, HUSPR_ATTR_DISPOFF);
    }
    ofs = lbl_1_bss_1980 - a1;
    HuSprPosSet(lbl_1_bss_1988, 2, lbl_1_bss_198E + 10, 8.0f + (32.0f + (lbl_1_bss_198C + 32.0f * ofs)));
    status = fn_1_414C(a0, lbl_1_bss_1980);
    if (status == 1) {
        HuWinHomeClear(lbl_1_bss_19FE[6]);
    } else {
        part = &lbl_1_data_4E0[a0][lbl_1_bss_1980];
        HuWinMesSet(lbl_1_bss_19FE[6], part->unk4);
    }
}

/* 178 insns */
void fn_1_27730(float a0, float a1)
{
    s16 i;

    for (i = 0; i < 5; i++) {
        HuWinPosSet(lbl_1_bss_19EA[i], 16.0f + a0, 16.0f + (a1 + i * 32));
        HuWinPosSet(lbl_1_bss_19D6[i], 288.0f + a0, 16.0f + (a1 + i * 32));
    }
    HuWinPosSet(lbl_1_bss_19FE[4], a0, a1);
    HuWinPosSet(lbl_1_bss_19FE[5], 8.0f + (240.0f + a0), 16.0f + (160.0f + a1));
    HuSprPosSet(lbl_1_bss_1988, 0, 151.0f + a0, 16.0f + a1);
    HuSprPosSet(lbl_1_bss_1988, 1, 151.0f + a0, 32.0f + (160.0f + a1));
    HuSprPosSet(lbl_1_bss_1988, 2, 10.0f + a0, 8.0f + (32.0f + (a1 + lbl_1_bss_1980 * 32)));
    lbl_1_bss_198E = a0;
    lbl_1_bss_198C = a1;
}

/* 226 insns */
void fn_1_279F8(s16 a0, s16 a1)
{
    SDPARTDATA *part;
    void *data;
    HU3DMODELID modelId;

    part = lbl_1_data_4E0[a0];
    part += a1;
    omCameraViewSetMulti(8, &lbl_1_data_2188);
    if (lbl_1_bss_19CE[0] != -1) {
        Hu3DModelHookReset(lbl_1_bss_19CE[0]);
        Hu3DModelKill(lbl_1_bss_19CE[0]);
    }
    if (lbl_1_bss_19CE[1] != -1) {
        Hu3DModelKill(lbl_1_bss_19CE[1]);
    }
    lbl_1_bss_19CE[0] = lbl_1_bss_19CE[1] = -1;
    if (fn_1_414C(a0, a1) == 1) {
        return;
    }
    if (HuARDirCheck(part->unk8)) {
        data = HuAR_ARAMtoMRAMFileRead(part->unk8, HU_MEMNUM_OVL, HEAP_MODEL);
    } else {
        data = HuDataSelHeapReadNum(part->unk8, HU_MEMNUM_OVL, HEAP_MODEL);
    }
    modelId = Hu3DModelCreate(data);
    lbl_1_bss_19CE[0] = modelId;
    Hu3DModelCameraSet(modelId, 8);
    if (lbl_1_bss_19D4 == 2) {
        Hu3DModelScaleSet(modelId, 1.5f, 1.5f, 1.5f);
    }
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_SHAPE_LOOP);
    if (lbl_1_bss_19D4 == 2 && a1 == 10) {
        modelId = Hu3DModelCreateData(DATANUM(DATA_sdroom, 17));
        lbl_1_bss_19CE[1] = modelId;
        Hu3DModelCameraSet(modelId, 8);
        Hu3DModelPosSet(modelId, 0.0f, 75.0f, 0.0f);
        Hu3DModelScaleSet(modelId, 0.45f, 0.45f, 0.45f);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelLayerSet(lbl_1_bss_19CE[0], 1);
    }
    if (lbl_1_bss_19D4 == 1 && a1 != 7 && a1 != 9) {
        Hu3DModelPosSet(lbl_1_bss_19CE[0], 0.0f, 50.0f, 0.0f);
        modelId = Hu3DModelLink(modelId);
        lbl_1_bss_19CE[1] = modelId;
        Hu3DModelCameraSet(modelId, 8);
        Hu3DModelScaleSet(modelId, -1.0f, 1.0f, 1.0f);
        Hu3DModelPosSet(modelId, 0.0f, 50.0f, 0.0f);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_CULL_FRONT);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_SHAPE_LOOP);
    }
}

/* 225 insns */
void fn_1_27D80(s16 a0, s16 a1)
{
    SDPARTDATA *part;
    GWSDCOMMON *common;
    HUWIN *winP;
    s16 choice;

    part = &lbl_1_data_4E0[a0][a1];
    common = &GwSdCommon;
    HuWinExOpen(lbl_1_bss_570[0]);
    winP = &winData[lbl_1_bss_570[0]];
    winP->choiceEndSe = -1;
    winP->padMask = 1;
    HuWinInsertMesSet(lbl_1_bss_570[0], part->mesNo, 0);
    HuWinMesSet(lbl_1_bss_570[0], 0x190008);
    HuWinMesWait(lbl_1_bss_570[0]);
    choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
    if (choice == 0) {
        HuAudFXPlay(1288);
        GwCommon.sdPoint[a0] -= part->point;
        fn_1_27004(a0);
        fn_1_3E8C(a0, a1);
        fn_1_2709C(lbl_1_bss_19FE[5], lbl_1_bss_19D4);
        if (fn_1_414C(3, 11) == 1 && (common->partFlag[0] & 0x7FF) == 0x7FF && (common->partFlag[1] & 0x7FF) == 0x7FF
            && (common->partFlag[2] & 0x7FF) == 0x7FF && (common->partFlag[3] & 0x7FF) == 0x7FF) {
            common->newPart3F = 1;
        }
        fn_1_3F00();
        fn_1_271EC(a0, lbl_1_bss_19D2);
        HuPrcSleep(20);
    } else if (choice == 1) {
        HuAudFXPlay(2);
    }
    winP->choiceEndSe = 2;
    HuWinExClose(lbl_1_bss_570[0]);
}

/* 120 insns */
void fn_1_28104(void)
{
    char buf[16];
    s16 total;
    s16 i;

    for (i = total = 0; i < 4; i++) {
        total += GwCommon.sdPoint[i];
    }
    if (total > GwSdCommon.prevPoint) {
        sprintf(buf, "%d", total - GwSdCommon.prevPoint);
        HuWinInsertMesSet(lbl_1_bss_570[0], MESSNUM_PTR(buf), 0);
        HuWinMesSet(lbl_1_bss_570[0], 0x190003);
        HuAudFXPlay(751);
        HuWinMesWait(lbl_1_bss_570[0]);
        GwSdCommon.prevPoint = total;
    }
    if (GwSdCommon.newPart1F || GwSdCommon.newPart2F || (!(GwSdCommon.partFlag[3] & 0x1800) && GwSdCommon.newPart3F)) {
        HuWinMesSet(lbl_1_bss_570[0], 0x190004);
        HuAudFXPlay(751);
        HuWinMesWait(lbl_1_bss_570[0]);
        GwSdCommon.newPart1F = GwSdCommon.newPart2F = GwSdCommon.newPart3F = 0;
    }
}

