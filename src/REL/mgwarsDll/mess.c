/*
 * mgwarsDll mess.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgwarsDll/asm/REL/mgwarsDll/mess.s.
 */

#include "REL/mgwarsDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- functions (reference order), .data placed before its first user --- */
/* 39 insns */
void fn_1_E2D0(void)
{
    HUWINID winId = fn_1_50C();
    int choice;
    fn_1_728(0x1);
    fn_1_520();
    HuAudFXPlayPan(757, 64);
    HuWinMesSet(winId, MGWARS_MES(0));
    HuWinMesWait(winId);
    choice = HuWinChoiceGet(winId, -1);
    if (choice == 0) {
        HuWinMesSet(winId, MGWARS_MES(27));
        HuWinMesWait(winId);
    }
    fn_1_6F4(0x1);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_E36C(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x2);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(10));
    HuWinMesWait(winId);
    fn_1_6F4(0x2);
    HuPrcEnd();
}

/* 0x658 */ s8 lbl_1_data_658[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9 };

/* 34 insns */
void fn_1_E3C8(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x4);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(11));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[0].charNo], 0);
    HuWinMesWait(winId);
    fn_1_6F4(0x4);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E450(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x8);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(12));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[1].charNo], 1);
    HuWinMesWait(winId);
    fn_1_6F4(0x8);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E4D8(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x10);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(13));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[2].charNo], 2);
    HuWinMesWait(winId);
    fn_1_6F4(0x10);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E560(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x20);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(14));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[3].charNo], 3);
    HuWinMesWait(winId);
    fn_1_6F4(0x20);
    HuPrcEnd();
}

/* 35 insns */
void fn_1_E5E8(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x40);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(18));
    HuWinMesWait(winId);
    HuWinMesSet(winId, MGWARS_MES(19));
    HuWinMesWait(winId);
    HuWinMesSet(winId, MGWARS_MES(20));
    HuWinMesWait(winId);
    fn_1_6F4(0x40);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E674(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x80);
    fn_1_520();
    if (fn_1_684(0x1)) {
        HuWinMesSet(winId, MGWARS_MES(1));
        HuWinMesWait(winId);
    } else {
        HuWinMesSet(winId, MGWARS_MES(8));
        HuWinMesWait(winId);
    }
    fn_1_6F4(0x80);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E6FC(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x100);
    fn_1_520();
    if (fn_1_684(0x1)) {
        HuWinMesSet(winId, MGWARS_MES(2));
        HuWinMesWait(winId);
    } else {
        HuWinMesSet(winId, MGWARS_MES(9));
        HuWinMesWait(winId);
    }
    fn_1_6F4(0x100);
    HuPrcEnd();
}

/* 62 insns */
void fn_1_E784(void)
{
    HUWINID winId = fn_1_50C();
    int choice;
    int loopF;
    fn_1_728(0x200);
    fn_1_668(0x6);
    fn_1_520();
    do {
        loopF = FALSE;
        HuWinMesSet(winId, MGWARS_MES(3));
        HuWinMesWait(winId);
        choice = HuWinChoiceGet(winId, -1);
        if (choice < 0) {
            choice = 1;
        }
        if (choice == 1) {
            HuWinMesSet(winId, MGWARS_MES(4));
            HuWinMesWait(winId);
            if (HuWinChoiceGet(winId, -1) == 0) {
                fn_1_64C(0x2);
            } else {
                loopF = TRUE;
            }
        } else if (choice == 2) {
            fn_1_64C(0x4);
        }
    } while (loopF);
    fn_1_6F4(0x200);
    HuPrcEnd();
}

/* 35 insns */
void fn_1_E87C(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x400);
    fn_1_520();
    HuAudFXPlayPan(758, 64);
    if (fn_1_684(0x10)) {
        HuWinMesSet(winId, MGWARS_MES(30));
    } else {
        HuWinMesSet(winId, MGWARS_MES(5));
    }
    HuWinMesWait(winId);
    fn_1_6F4(0x400);
    HuPrcEnd();
}

/* 38 insns */
void fn_1_E908(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x800);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(6));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[fn_1_5C4()].charNo], 0);
    HuWinMesWait(winId);
    fn_1_6F4(0x800);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_E9A0(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x1000);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(7));
    HuWinMesWait(winId);
    fn_1_6F4(0x1000);
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E9FC(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x2000);
    fn_1_520();
    if (fn_1_684(0x10)) {
        HuWinMesSet(winId, MGWARS_MES(16));
        HuWinMesWait(winId);
    } else {
        HuWinMesSet(winId, MGWARS_MES(15));
        HuWinMesWait(winId);
    }
    fn_1_6F4(0x2000);
    HuPrcEnd();
}

/* 54 insns */
void fn_1_EA84(void)
{
    HUWINID winId = fn_1_50C();
    char str[32];
    fn_1_728(0x80000);
    fn_1_520();
    sprintf(str, "%d", fn_1_5D8());
    switch (fn_1_5C4()) {
        case 0:
        case 1:
        case 2:
        case 3:
            break;
    }
    HuWinMesSet(winId, MGWARS_MES(17));
    HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[fn_1_5C4()].charNo], 0);
    HuWinInsertMesSet(winId, MESSNUM_PTR(str), 1);
    HuWinMesWait(winId);
    fn_1_6F4(0x80000);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_EB5C(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x4000);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(21));
    HuWinMesWait(winId);
    fn_1_6F4(0x4000);
    HuPrcEnd();
}

/* 25 insns */
void fn_1_EBB8(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x8000);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(22));
    HuWinMesWait(winId);
    fn_1_6F4(0x8000);
    HuPrcEnd();
}

/* 33 insns */
void fn_1_EC1C(void)
{
    HUWINID winId = fn_1_50C();
    char str[32];
    fn_1_728(0x10000);
    fn_1_520();
    sprintf(str, "%2d", fn_1_638());
    HuWinMesSet(winId, MGWARS_MES(23));
    HuWinInsertMesSet(winId, MESSNUM_PTR(str), 0);
    HuWinMesWait(winId);
    fn_1_6F4(0x10000);
    HuPrcEnd();
}

/* 142 insns */
void fn_1_ECA0(void)
{
    HUWINID winId = fn_1_50C();
    s8 player[4];
    fn_1_728(0x20000);
    fn_1_520();
    HuAudFXPlayPan(756, 64);
    switch (fn_1_5EC(player)) {
        case 1:
            HuWinMesSet(winId, MGWARS_MES(24));
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[0]].charNo], 0);
            HuWinMesWait(winId);
            break;
        case 2:
            HuWinMesSet(winId, MGWARS_MES(28));
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[0]].charNo], 0);
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[1]].charNo], 1);
            HuWinMesWait(winId);
            break;
        case 3:
            HuWinMesSet(winId, MGWARS_MES(29));
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[0]].charNo], 0);
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[1]].charNo], 1);
            HuWinInsertMesSet(winId, lbl_1_data_658[GwPlayerConf[player[2]].charNo], 2);
            HuWinMesWait(winId);
            break;
    }
    fn_1_6F4(0x20000);
    HuPrcEnd();
}

/* 38 insns */
void fn_1_EED8(void)
{
    HUWINID winId = fn_1_50C();
    fn_1_728(0x40000);
    fn_1_520();
    HuWinMesSet(winId, MGWARS_MES(25));
    HuWinMesWait(winId);
    if (HuWinChoiceGet(winId, -1) == 0) {
        fn_1_64C(0x20);
    } else {
        HuWinMesSet(winId, MGWARS_MES(26));
        HuWinMesWait(winId);
    }
    fn_1_6F4(0x40000);
    HuPrcEnd();
}

