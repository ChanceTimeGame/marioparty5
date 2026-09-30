/*
 * mgtourDll mess.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgtourDll/asm/REL/mgtourDll/mess.s.
 */

#include "REL/mgtourDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* score.c lbl_1_data_920: 0x28 records (field names unknown) */
typedef struct MgTourScoreRec_s {
    s32 num;
    HuVecF vec[3];
} MGTOUR_SCOREREC;

/* --- functions (reference order), .data placed before its first user --- */
/* 25 insns */
void fn_1_FBD0(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(1);
    fn_1_708();
    HuAudFXPlayPan(MSM_SE_GUIDE_56, 40);
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 0));
    HuWinMesWait(winId);
    fn_1_854(1);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_FC34(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(2);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 1));
    HuWinMesWait(winId);
    fn_1_854(2);
    HuPrcEnd();
}

/* 0xC18 */ s8 lbl_1_data_C18[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9, 9, 9 };

/* 43 insns */
void fn_1_FC90(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(4);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 2));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(0)], 0);
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(1)], 1);
    HuWinMesWait(winId);
    fn_1_854(4);
    HuPrcEnd();
}

/* 43 insns */
void fn_1_FD3C(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(8);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 3));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(0)], 0);
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(1)], 1);
    HuWinMesWait(winId);
    fn_1_854(8);
    HuPrcEnd();
}

/* 43 insns */
void fn_1_FDE8(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x10);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 4));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(0)], 0);
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(1)], 1);
    HuWinMesWait(winId);
    fn_1_854(0x10);
    HuPrcEnd();
}

/* 43 insns */
void fn_1_FE94(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x20);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 5));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(0)], 0);
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(1)], 1);
    HuWinMesWait(winId);
    fn_1_854(0x20);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_FF40(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x40);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 6));
    HuWinMesWait(winId);
    fn_1_854(0x40);
    HuPrcEnd();
}

/* 31 insns */
void fn_1_FF9C(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x80);
    fn_1_708();
    HuAudFXPlayPan(MSM_SE_GUIDE_55, 64);
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 7));
    HuWinInsertMesSet(winId, fn_1_8A4(), 0);
    HuWinMesWait(winId);
    fn_1_854(0x80);
    HuPrcEnd();
}

/* 62 insns */
void fn_1_10018(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x100);
    fn_1_7C8(6);
    fn_1_708();
    while (1) {
        int choice, mode;
        mode = 0;
        HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 8));
        HuWinMesWait(winId);
        choice = HuWinChoiceGet(winId, -1);
        if (choice < 0) {
            choice = 1;
        }
        if (choice == 1) {
            HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 9));
            HuWinMesWait(winId);
            if (HuWinChoiceGet(winId, -1) == 0) {
                fn_1_7AC(2);
            }
            else {
                mode = 1;
            }
        }
        else if (choice == 2) {
            fn_1_7AC(4);
        }
        if (mode == 0) {
            break;
        }
    }
    fn_1_854(0x100);
    HuPrcEnd();
}

/* 26 insns */
void fn_1_10110(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x200);
    fn_1_708();
    HuAudFXPlayPan(MSM_SE_GUIDE_57, 40);
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 10));
    HuWinMesWait(winId);
    fn_1_854(0x200);
    HuPrcEnd();
}

/* 33 insns */
void fn_1_10178(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x400);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 11));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_904(fn_1_96C())], 0);
    HuWinMesWait(winId);
    fn_1_854(0x400);
    HuPrcEnd();
}

/* 35 insns */
void fn_1_101FC(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x800);
    fn_1_708();
    HuAudFXPlayPan(MSM_SE_GUIDE_55, 40);
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 12));
    HuWinInsertMesSet(winId, lbl_1_data_C18[fn_1_984()], 0);
    HuWinMesWait(winId);
    fn_1_854(0x800);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_10288(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x1000);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 13));
    HuWinMesWait(winId);
    fn_1_854(0x1000);
    HuPrcEnd();
}

/* 31 insns */
void fn_1_102E4(void)
{
    HUWINID winId = fn_1_660();
    fn_1_870(0x2000);
    fn_1_708();
    HuWinMesSet(winId, MESSNUM(MESS_MGMODE_TO, 14));
    HuWinMesWait(winId);
    if (HuWinChoiceGet(winId, -1) == 0) {
        fn_1_7AC(0x10);
    }
    fn_1_854(0x2000);
    HuPrcEnd();
}

