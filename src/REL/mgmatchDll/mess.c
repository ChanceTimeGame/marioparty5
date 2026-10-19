/*
 * mgmatchDll mess.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgmatchDll/asm/REL/mgmatchDll/mess.s.
 */

#include "REL/mgmatchDll.h"

/* Retail mg* units call the audio API unprototyped (mgtour/mgwars): keep game/audio.h out of
 * the CW build; the host keeps its prototypes. */
#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#include "msm_grp.h"
#include "msm_se.h"
#include "msm_stream.h"
#endif

#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "messnum/syshelp.h"
#ifndef __MWERKS__
#include "stdio.h" /* retail calls sprintf unprototyped (no crclr) */
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_310 = -10000.0f; /* 0x310 */
static const float lbl_1_rodata_314 = 380.0f; /* 0x314 */
static const float lbl_1_rodata_318 = 0.0f; /* 0x318 */

/* --- functions (reference order), .data placed before its first user --- */
/* 25 insns */
void fn_1_15F24(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(1);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_56, 64);
    HuWinMesSet(winId, MGMATCH_MESS(0));
    HuWinMesWait(winId);
    fn_1_924(1);
    HuPrcEnd();
}

/* 0xE40 */ s8 lbl_1_data_E40[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9 }; /* charNo -> CHARANAME message (read lbz+extsb) */

/* 36 insns */
void fn_1_15F88(void)
{
    HUWINID winId = fn_1_458();
    char strBuf[16];
    fn_1_940(2);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_56, 40);
    sprintf(strBuf, "%d", fn_1_510());
    HuWinMesSet(winId, MGMATCH_MESS(1));
    HuWinInsertMesSet(winId, MESSNUM_PTR(strBuf), 0);
    HuWinMesWait(winId);
    fn_1_924(2);
    HuPrcEnd();
}

/* 26 insns */
void fn_1_16018(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(4);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_56, 40);
    HuWinMesSet(winId, MGMATCH_MESS(5));
    HuWinMesWait(winId);
    fn_1_924(4);
    HuPrcEnd();
}

/* 28 insns */
void fn_1_16080(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(8);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(6));
    HuWinInsertMesSet(winId, fn_1_528(), 0);
    HuWinMesWait(winId);
    fn_1_924(8);
    HuPrcEnd();
}

/* 62 insns */
void fn_1_160F0(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x10);
    fn_1_898(6);
    fn_1_46C();
    while (1) {
        int choice, mode;
        mode = 0;
        HuWinMesSet(winId, MGMATCH_MESS(7));
        HuWinMesWait(winId);
        choice = HuWinChoiceGet(winId, -1);
        if (choice < 0) {
            choice = 1;
        }
        if (choice == 1) {
            HuWinMesSet(winId, MGMATCH_MESS(8));
            HuWinMesWait(winId);
            if (HuWinChoiceGet(winId, -1) == 0) {
                fn_1_87C(2);
            }
            else {
                mode = 1;
            }
        }
        else if (choice == 2) {
            fn_1_87C(4);
        }
        if (mode == 0) {
            break;
        }
    }
    fn_1_924(0x10);
    HuPrcEnd();
}

/* 26 insns */
void fn_1_161E8(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x20);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_57, 40);
    HuWinMesSet(winId, MGMATCH_MESS(9));
    HuWinMesWait(winId);
    fn_1_924(0x20);
    HuPrcEnd();
}

/* 201 insns */
void fn_1_16250(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x40);
    fn_1_46C();
    switch (fn_1_59C()) {
        case MGMATCH_GAMETYPE_4P:
            HuWinMesSet(winId, MGMATCH_MESS(10));
            HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_588()].charNo], 0);
            break;

        case MGMATCH_GAMETYPE_2VS2:
            HuWinMesSet(winId, MGMATCH_MESS(11));
            if (fn_1_588() == 0) {
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(0)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(1)].charNo], 1);
            }
            else {
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(2)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(3)].charNo], 1);
            }
            break;

        case MGMATCH_GAMETYPE_1VS3:
            if (fn_1_588() == 0) {
                HuWinMesSet(winId, MGMATCH_MESS(10));
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(0)].charNo], 0);
            }
            else {
                HuWinMesSet(winId, MGMATCH_MESS(12));
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(1)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(2)].charNo], 1);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(3)].charNo], 2);
            }
            break;
    }
    HuWinMesWait(winId);
    fn_1_924(0x40);
    HuPrcEnd();
}

/* 204 insns */
void fn_1_16574(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x80);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_55, 40);
    switch (fn_1_59C()) {
        case MGMATCH_GAMETYPE_4P:
            HuWinMesSet(winId, MGMATCH_MESS(13));
            HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_624()].charNo], 0);
            break;

        case MGMATCH_GAMETYPE_2VS2:
            HuWinMesSet(winId, MGMATCH_MESS(14));
            if (fn_1_588() == 0) {
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(0)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(1)].charNo], 1);
            }
            else {
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(2)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(3)].charNo], 1);
            }
            break;

        case MGMATCH_GAMETYPE_1VS3:
            if (fn_1_588() == 0) {
                HuWinMesSet(winId, MGMATCH_MESS(13));
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(0)].charNo], 0);
            }
            else {
                HuWinMesSet(winId, MGMATCH_MESS(15));
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(1)].charNo], 0);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(2)].charNo], 1);
                HuWinInsertMesSet(winId, lbl_1_data_E40[GwPlayerConf[fn_1_5B0(3)].charNo], 2);
            }
            break;
    }
    HuWinMesWait(winId);
    fn_1_924(0x80);
    HuPrcEnd();
}

/* 79 insns */
void fn_1_168A4(void)
{
    HUWINID winId = fn_1_458();
    char strBuf[56];
    s32 place;
    s32 num;
    fn_1_940(0x100);
    fn_1_46C();
    fn_1_64C(&place, &num, 0);
    HuAudFXPlayPan(MSM_SE_GUIDE_55, 40);
    HuWinMesSet(winId, MGMATCH_MESS(16));
    switch (GwCommon.languageNo) {
        case 0:
            sprintf(strBuf, "%d", place);
            break;

        case 1:
            switch (place) {
                case 2:
                    sprintf(strBuf, "second");
                    break;

                case 3:
                    sprintf(strBuf, "third");
                    break;
            }
            break;
    }
    HuWinInsertMesSet(winId, MESSNUM_PTR(strBuf), 0);
    if (num == 2) {
        HuWinInsertMesSet(winId, MGMATCH_MESS(25), 1);
    }
    else {
        HuWinInsertMesSet(winId, MGMATCH_MESS(26), 1);
    }
    HuWinMesWait(winId);
    fn_1_924(0x100);
    HuPrcEnd();
}

/* 26 insns */
void fn_1_169E0(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x200);
    fn_1_46C();
    HuAudFXPlayPan(MSM_SE_GUIDE_56, 40);
    HuWinMesSet(winId, MGMATCH_MESS(17));
    HuWinMesWait(winId);
    fn_1_924(0x200);
    HuPrcEnd();
}

/* 31 insns */
void fn_1_16A48(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x400);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(18));
    HuWinMesWait(winId);
    if (HuWinChoiceGet(winId, -1) == 0) {
        fn_1_87C(0x10);
    }
    fn_1_924(0x400);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_16AC4(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x800);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(19));
    HuWinMesWait(winId);
    fn_1_924(0x800);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_16B20(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x800000);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(20));
    HuWinMesWait(winId);
    fn_1_924(0x800000);
    HuPrcEnd();
}

/* 32 insns */
void fn_1_16B7C(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x1000000);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(21));
    HuWinInsertMesSet(winId, lbl_1_data_E40[fn_1_638()], 0);
    HuWinMesWait(winId);
    fn_1_924(0x1000000);
    HuPrcEnd();
}

/* 32 insns */
void fn_1_16BFC(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x2000000);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(22));
    HuWinInsertMesSet(winId, lbl_1_data_E40[fn_1_638()], 0);
    HuWinMesWait(winId);
    fn_1_924(0x2000000);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_16C7C(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x4000000);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(23));
    HuWinMesWait(winId);
    fn_1_924(0x4000000);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_16CD8(void)
{
    HUWINID winId = fn_1_458();
    fn_1_940(0x8000000);
    fn_1_46C();
    HuWinMesSet(winId, MGMATCH_MESS(24));
    HuWinMesWait(winId);
    fn_1_924(0x8000000);
    HuPrcEnd();
}

/* 93 insns */
void fn_1_16D34(void)
{
    int i;
    HUWINID winId;
    int num;
    fn_1_940(0x1000);
    for (num = 0, i = 0; i < GW_PLAYER_MAX; i++) {
        if (GwPlayerConf[i].type != GW_TYPE_MAN) {
            num++;
        }
    }
    if (num == GW_PLAYER_MAX) {
        fn_1_924(0x1000);
        HuPrcEnd();
        return;
    }
    winId = HuWinCreate(HUWIN_POS_CENTER, 380, 400, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSet(winId, MESS_SYSHELP_PARTYRESULT_END);
    HuWinMesWait(winId);
    while (1) {
        for (num = 0, i = 0; i < GW_PLAYER_MAX; i++) {
            if (HuPadBtnDown[i] & PAD_BUTTON_A) {
                HuAudFXPlay(MSM_SE_CMN_01);
                num = GW_PLAYER_MAX;
                break;
            }
        }
        if (num == GW_PLAYER_MAX) {
            break;
        }
        HuPrcVSleep();
    }
    HuWinKill(winId);
    fn_1_924(0x1000);
    HuPrcEnd();
}
