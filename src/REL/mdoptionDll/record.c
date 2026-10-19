/*
 * mdoptiondll record.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mdoptiondll/asm/REL/mdoptiondll/record.s.
 */

#include "REL/mdoptionDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "msm_se.h"
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x678 lbl_1_rodata_678 (0x20): 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0x698 lbl_1_rodata_698 (0x20): 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_6B8 = -116.0f; /* 0x6B8 */
static const float lbl_1_rodata_6BC = -59.0f; /* 0x6BC */
static const float lbl_1_rodata_6C0 = 1.0f; /* 0x6C0 */
static const float lbl_1_rodata_6C4 = 0.75f; /* 0x6C4 */
static const float lbl_1_rodata_6C8 = 235.0f; /* 0x6C8 */
static const float lbl_1_rodata_6CC = 26.0f; /* 0x6CC */
static const float lbl_1_rodata_6D0 = 58.0f; /* 0x6D0 */
static const float lbl_1_rodata_6D4 = 116.0f; /* 0x6D4 */
static const float lbl_1_rodata_6D8 = 0.0f; /* 0x6D8 */
static const float lbl_1_rodata_6DC = 0.85f; /* 0x6DC */
static const float lbl_1_rodata_6E0 = 293.0f; /* 0x6E0 */
static const float lbl_1_rodata_6E4 = -230.0f; /* 0x6E4 */
static const float lbl_1_rodata_6E8 = -80.0f; /* 0x6E8 */
static const float lbl_1_rodata_6EC = 5.0f; /* 0x6EC */
/* 0x6F0 lbl_1_rodata_6F0 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x6F8 lbl_1_rodata_6F8 (0x20): 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0x718 lbl_1_rodata_718 (0x20): 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7EC */ MDREC_SNDWORK lbl_1_bss_7EC;
/* 0x7E8 */ MDREC_SNDWORK *lbl_1_bss_7E8;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x2AD0 */ MDREC_SNDITEM lbl_1_data_2AD0[5] = {
    { 0, 2, 0x0021001D }, { 0, 69, 0x00210020 }, { 0, 3, 0x0021001E }, { 0, 4, 0x0021001F },
    { -1, -1, 0xFFFFFFFF }
};
/* 0x2AF8 */ MDREC_SNDITEM lbl_1_data_2AF8[15] = {
    { 0, 13, 0x00210029 }, { 0, 12, 0x00210028 }, { 0, 5, 0x00210021 }, { 0, 6, 0x00210022 },
    { 0, 7, 0x00210023 }, { 0, 8, 0x00210024 }, { 0, 9, 0x00210025 }, { 0, 10, 0x00210026 },
    { 0, 11, 0x00210027 }, { 0, 21, 0x00210031 }, { 0, 70, 0x00210032 }, { 0, 71, 0x00210033 },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2B70 */ MDREC_SNDITEM lbl_1_data_2B70[15] = {
    { 0, 14, 0x0021002A }, { 0, 15, 0x0021002B }, { 0, 16, 0x0021002C }, { 0, 17, 0x0021002D },
    { 0, 18, 0x0021002E }, { 0, 19, 0x0021002F }, { 0, 76, 0x00210034 }, { 0, 20, 0x00210030 },
    { 2, 127, 0x00210036 }, { 2, 128, 0x00210037 }, { 2, 132, 0x00210038 }, { 2, 138, 0x00210039 },
    { 2, 139, 0x0021003A }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2BE8 */ MDREC_SNDITEM lbl_1_data_2BE8[15] = {
    { 0, 28, 0x00210046 }, { 0, 29, 0x00210042 }, { 0, 24, 0x0021003D }, { 0, 25, 0x0021003E },
    { 0, 26, 0x0021003F }, { 2, 140, 0x00210045 }, { 0, 30, 0x00210041 }, { 0, 64, 0x0021005B },
    { 0, 87, 0x00210061 }, { 0, 65, 0x0021005C }, { 2, 124, 0x00210065 }, { 0, 31, 0x00210043 },
    { 0, 32, 0x00210044 }, { 0, 27, 0x00210040 }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2C60 */ MDREC_SNDITEM lbl_1_data_2C60[15] = {
    { 0, 48, 0x0021004B }, { 0, 49, 0x0021004C }, { 0, 50, 0x0021004D }, { 0, 51, 0x0021004E },
    { 0, 52, 0x0021004F }, { 0, 53, 0x00210050 }, { 0, 54, 0x00210051 }, { 0, 55, 0x00210052 },
    { 0, 60, 0x00210057 }, { 0, 57, 0x00210054 }, { 0, 58, 0x00210055 }, { 0, 62, 0x00210059 },
    { 2, 131, 0x00210066 }, { 0, 59, 0x00210056 }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2CD8 */ MDREC_SNDITEM lbl_1_data_2CD8[15] = {
    { 0, 63, 0x0021005A }, { 0, 61, 0x00210058 }, { 0, 66, 0x0021005D }, { 0, 67, 0x0021005E },
    { 0, 68, 0x0021005F }, { 0, 75, 0x00210060 }, { 2, 121, 0x00210062 }, { 2, 122, 0x00210063 },
    { 2, 123, 0x00210064 }, { 2, 134, 0x00210068 }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2D50 */ MDREC_SNDITEM lbl_1_data_2D50[15] = {
    { 0, 35, 0x00210069 }, { 0, 36, 0x0021006A }, { 0, 37, 0x0021006B }, { 0, 38, 0x0021006C },
    { 0, 72, 0x0021006D }, { 2, 129, 0x0021006E }, { 2, 135, 0x0021006F }, { 2, 136, 0x00210070 },
    { 0, 39, 0x00210071 }, { 0, 40, 0x00210072 }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2DC8 */ MDREC_SNDITEM lbl_1_data_2DC8[15] = {
    { 0, 41, 0x00210075 }, { 2, 126, 0x0021007C }, { 2, 133, 0x00210067 }, { 0, 44, 0x00210077 },
    { 0, 45, 0x00210078 }, { 0, 46, 0x00210079 }, { 2, 137, 0x0021007B }, { 0, 43, 0x00210076 },
    { 0, 74, 0x0021007A }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2E40 */ MDREC_SNDITEM lbl_1_data_2E40[15] = {
    { 1, 502, 0x00210083 }, { 1, 503, 0x00210084 }, { 1, 504, 0x00210085 }, { 1, 505, 0x00210086 },
    { 1, 506, 0x00210087 }, { 1, 507, 0x00210088 }, { 1, 508, 0x00210089 }, { 1, 509, 0x0021008A },
    { 1, 511, 0x0021008B }, { 1, 512, 0x0021008C }, { 1, 513, 0x0021008D }, { 1, 514, 0x0021008E },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2EB8 */ MDREC_SNDITEM lbl_1_data_2EB8[15] = {
    { 1, 713, 0x002100BB }, { 1, 714, 0x002100BC }, { 1, 715, 0x002100BD }, { 1, 716, 0x002100BE },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2F30 */ MDREC_SNDITEM lbl_1_data_2F30[15] = {
    { 1, 731, 0x00210091 }, { 1, 732, 0x00210092 }, { 1, 733, 0x00210093 }, { 1, 719, 0x00210094 },
    { 1, 720, 0x00210095 }, { 1, 721, 0x00210096 }, { 1, 724, 0x00210097 }, { 1, 725, 0x00210098 },
    { 1, 726, 0x00210099 }, { 1, 708, 0x0021009A }, { 1, 709, 0x0021009B }, { 1, 710, 0x0021009C },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x2FA8 */ MDREC_SNDITEM lbl_1_data_2FA8[15] = {
    { 1, 740, 0x0021009F }, { 1, 741, 0x002100A0 }, { 1, 742, 0x002100A1 }, { 1, 743, 0x002100A2 },
    { 1, 744, 0x002100A3 }, { 1, 745, 0x002100A4 }, { 1, 746, 0x002100A5 }, { 1, 747, 0x002100A6 },
    { 1, 748, 0x002100A7 }, { 1, 749, 0x002100A8 }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x3020 */ MDREC_SNDITEM lbl_1_data_3020[15] = {
    { 1, 703, 0x002100AD }, { 1, 705, 0x002100AE }, { 1, 727, 0x002100AF }, { 1, 728, 0x002100B0 },
    { 1, 799, 0x002100B1 }, { 1, 775, 0x002100B2 }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x3098 */ MDREC_SNDITEM lbl_1_data_3098[15] = {
    { 1, 25, 0x002100C9 }, { 1, 26, 0x002100CA }, { 1, 27, 0x002100CB }, { 1, 28, 0x002100CC },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF },
    { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }, { -1, -1, 0xFFFFFFFF }
};
/* 0x3110 */ MDREC_SNDLIST lbl_1_data_3110[24] = {
    { 0, 0, lbl_1_data_2AD0, 0x00210001, -1, 1 }, /* 0 */
    { 0, 0, lbl_1_data_2AF8, 0x00210002, 0x00210007, 1 }, /* 1 */
    { 0, 0, lbl_1_data_2B70, 0x00210002, 0x00210008, 1 }, /* 2 */
    { 0, 0, lbl_1_data_2BE8, 0x00210003, -1, 1 }, /* 3 */
    { 0, 0, lbl_1_data_2C60, 0x00210004, 0x00210007, 1 }, /* 4 */
    { 0, 0, lbl_1_data_2CD8, 0x00210004, 0x00210008, 1 }, /* 5 */
    { 0, 0, lbl_1_data_2D50, 0x00210004, 0x00210009, 1 }, /* 6 */
    { 0, 0, lbl_1_data_2DC8, 0x00210005, -1, 1 }, /* 7 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x0021000C, 1 }, /* 8 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x0021000D, 1 }, /* 9 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x0021000E, 1 }, /* 10 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x0021000F, 1 }, /* 11 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210010, 1 }, /* 12 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210011, 1 }, /* 13 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210012, 1 }, /* 14 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210013, 1 }, /* 15 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210014, 1 }, /* 16 */
    { 0, 0, lbl_1_data_2E40, 0x00210006, 0x00210015, 1 }, /* 17 */
    { 0, 0, lbl_1_data_2EB8, 0x00210006, 0x00210017, 1 }, /* 18 */
    { 0, 0, lbl_1_data_2F30, 0x00210006, 0x00210018, 1 }, /* 19 */
    { 0, 0, lbl_1_data_2FA8, 0x00210006, 0x00210019, 1 }, /* 20 */
    { 0, 0, lbl_1_data_3020, 0x00210006, 0x0021001A, 1 }, /* 21 */
    { 0, 0, lbl_1_data_3098, 0x00210006, 0x0021001B, 1 }, /* 22 */
    { -1, 0, NULL, -1, -1, 0 }, /* 23 */
};

/* 124 insns */
void fn_1_1A278(void)
{
    int i; //r31
    int j; //r30
    int boardNum; //r29
    MDREC_SNDLIST *list; //r28
    int storyNum; //r27
    memset(&lbl_1_bss_7EC, 0, sizeof(MDREC_SNDWORK));
    lbl_1_bss_7E8 = &lbl_1_bss_7EC;
    for(i=0; lbl_1_data_3110[i].unk0 != -1; i++) {
        list = &lbl_1_data_3110[i];
        for(j=0; list->item[j].type != -1; j++);
        list->num = j;
    }
    lbl_1_bss_7E8->listNum = i;
    storyNum = 0;
    for(i=storyNum; i<7; i++) {
        storyNum += GwCommon.storyPlayNum[i];
    }
    lbl_1_data_3110[3].enable = (storyNum != 0) ? TRUE : FALSE;
    for(i=0, boardNum=0; i<7; i++) {
        if(GwCommon.playNum[i] != 0) {
            boardNum++;
        }
    }
    lbl_1_data_3110[1].enable = (boardNum == 7) ? TRUE : FALSE;
    lbl_1_data_3110[2].enable = (boardNum == 7) ? TRUE : FALSE;
    lbl_1_data_3110[7].enable = (GwSdCommon.battleEasyWinF+GwSdCommon.battleNormalWinF != 0) ? TRUE : FALSE;
    lbl_1_bss_7E8->fxNo = lbl_1_bss_7E8->streamNo = -1;
}

/* 214 insns */
void fn_1_1A468(int dir)
{
    MDREC_SNDLIST *list = &lbl_1_data_3110[lbl_1_bss_7E8->listNo]; //r31
    int num = list->num; //r30
    int prevCursor = lbl_1_bss_7E8->cursor; //r26
    switch(dir) {
        case 0:
            if(lbl_1_bss_7E8->cursor >= 2) {
                lbl_1_bss_7E8->cursor -= 2;
            }
            break;

        case 1:
            if(lbl_1_bss_7E8->cursor < num-2) {
                lbl_1_bss_7E8->cursor += 2;
            }
            break;

        case 2:
            if(lbl_1_bss_7E8->cursor%2 != 0) {
                lbl_1_bss_7E8->cursor--;
            }
            break;

        case 3:
            if(lbl_1_bss_7E8->cursor%2 == 0 && lbl_1_bss_7E8->cursor < num-1) {
                lbl_1_bss_7E8->cursor++;
            }
            break;

        case 4:
        case 5:
            if(dir == 4) {
                lbl_1_bss_7E8->listNo = (lbl_1_bss_7E8->listNo != 0) ? lbl_1_bss_7E8->listNo-1 : lbl_1_bss_7E8->listNum-1;
            } else {
                lbl_1_bss_7E8->listNo = (lbl_1_bss_7E8->listNo < lbl_1_bss_7E8->listNum-1) ? lbl_1_bss_7E8->listNo+1 : 0;
            }
            list = &lbl_1_data_3110[lbl_1_bss_7E8->listNo];
            lbl_1_bss_7E8->top = lbl_1_bss_7E8->cursor = list->unk0;
            break;
    }
    if(lbl_1_bss_7E8->cursor < lbl_1_bss_7E8->top) {
        lbl_1_bss_7E8->top -= 2;
    }
    if(lbl_1_bss_7E8->cursor > lbl_1_bss_7E8->top+13) {
        lbl_1_bss_7E8->top += 2;
    }
    if(dir >= 4) {
        fn_1_A930(8);
    } else if(prevCursor != lbl_1_bss_7E8->cursor) {
        fn_1_A930(2);
    }
}

/* 370 insns */
void fn_1_1A7C0(void)
{
    HuVec2f *grpScale; //r31
    MDMESS_WORK *mess; //r30
    MDREC_SNDLIST *list; //r29
    int i; //r28
    HUSPRGRPID grpId; //r27
    HuVec2f *grpPos; //r26
    SYS *sysWorkP; //r25
    MDREC_SNDITEM *item; //r24
    int ofs; //r23
    MDSPRITE_WORK *sprite; //r22
    sysWorkP = sysP;
    sprite = sysWorkP->sprite;
    grpId = sprite->grpId[0];
    mess = sysWorkP->mess;
    grpPos = MdSpriteGrpPosGet(sysWorkP->sprite, 0);
    grpScale = MdSpriteGrpScaleGet(sysP->sprite, 0);
    list = &lbl_1_data_3110[lbl_1_bss_7E8->listNo];
    {
    u32 mesL[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    u32 mesR[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    float posX = -116; //f31
    float posY = -59; //f30
    HuSprAttrReset(grpId, 3, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(grpId, 4, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 5, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 6, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 7, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 8, HUSPR_ATTR_DISPOFF);
    ofs = lbl_1_bss_7E8->cursor-lbl_1_bss_7E8->top;
    HuSprAttrReset(grpId, 2, HUSPR_ATTR_DISPOFF);
    HuSprScaleSet(grpId, 2, 1, 1);
    HuSprTPLvlSet(grpId, 2, 0.75f);
    HuSprPosSet(grpId, 2, posX+(235.0f*(ofs%2)), posY+(26.0f*(ofs/2)));
    MdMessWinAttrSet(mess, 2, HUWIN_ATTR_ALIGN_CENTER);
    if(list->insertMes == -1) {
        MdMessWinMesSet(mess, 2, list->mes);
    } else {
        MdMessWinInsertMesSet(mess, 2, list->mes, list->insertMes);
    }
    for(i=0; i<14; i++) {
        item = &list->item[lbl_1_bss_7E8->top+i];
        if(item->type == -1) {
            break;
        }
        if(list->enable) {
            if(i%2 == 0) {
                mesL[i/2] = item->mes;
            } else {
                mesR[i/2] = item->mes;
            }
        } else {
            if(i%2 == 0) {
                mesL[i/2] = 0x1F0050;
            } else {
                mesR[i/2] = 0x1F0050;
            }
        }
    }
    MdMessWinClose(mess, 4);
    MdMessWinClose(mess, 5);
    MdMessHelpWinCreate(mess, 4, 0x1F003E, 58, 116, 260, 180, 0, 0);
    MdMessWinScaleSet(mess, 4, 0.85f*grpScale->x, grpScale->y);
    MdMessHelpWinCreate(mess, 5, 0x1F003E, 293, 116, 260, 180, 0, 0);
    MdMessWinScaleSet(mess, 5, 0.85f*grpScale->x, grpScale->y);
    MdMessWinInsertMultiMesSet(mess, 4, 0x1F003E, mesL);
    MdMessWinSpeedSet(mess, 4, 0);
    MdMessWinPosSet(mess, 4, (-230*grpScale->x)+grpPos->x, (-80*grpScale->y)+grpPos->y);
    MdMessWinInsertMultiMesSet(mess, 5, 0x1F003E, mesR);
    MdMessWinSpeedSet(mess, 5, 0);
    MdMessWinPosSet(mess, 5, (5*grpScale->x)+grpPos->x, (-80*grpScale->y)+grpPos->y);
    }
}

/* 313 insns */
void fn_1_1AD88(void)
{
    HuVec2f *grpScale; //r31
    MDMESS_WORK *mess; //r30
    MDREC_SNDLIST *list; //r29
    int i; //r28
    HUSPRGRPID grpId; //r26
    HuVec2f *grpPos; //r27
    SYS *sysWorkP; //r25
    MDREC_SNDITEM *item; //r24
    int ofs; //r23
    MDSPRITE_WORK *sprite; //r22
    sysWorkP = sysP;
    sprite = sysWorkP->sprite;
    grpId = sprite->grpId[0];
    mess = sysWorkP->mess;
    grpPos = MdSpriteGrpPosGet(sysWorkP->sprite, 0);
    grpScale = MdSpriteGrpScaleGet(sysP->sprite, 0);
    list = &lbl_1_data_3110[lbl_1_bss_7E8->listNo];
    {
    u32 mesL[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    u32 mesR[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
    float posX = -116; //f31
    float posY = -59; //f30
    HuSprAttrReset(grpId, 3, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(grpId, 4, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 5, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 6, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 7, HUSPR_ATTR_DISPOFF);
    HuSprAttrSet(grpId, 8, HUSPR_ATTR_DISPOFF);
    ofs = lbl_1_bss_7E8->cursor-lbl_1_bss_7E8->top;
    HuSprPosSet(grpId, 2, posX+(235.0f*(ofs%2)), posY+(26.0f*(ofs/2)));
    if(list->insertMes == -1) {
        MdMessWinMesSet(mess, 2, list->mes);
    } else {
        MdMessWinInsertMesSet(mess, 2, list->mes, list->insertMes);
    }
    for(i=0; i<14; i++) {
        item = &list->item[lbl_1_bss_7E8->top+i];
        if(item->type == -1) {
            break;
        }
        if(list->enable) {
            if(i%2 == 0) {
                mesL[i/2] = item->mes;
            } else {
                mesR[i/2] = item->mes;
            }
        } else {
            if(i%2 == 0) {
                mesL[i/2] = 0x1F0050;
            } else {
                mesR[i/2] = 0x1F0050;
            }
        }
    }
    MdMessWinHomeClear(mess, 4);
    MdMessWinInsertMultiMesSet(mess, 4, 0x1F003E, mesL);
    MdMessWinPosSet(mess, 4, (-230*grpScale->x)+grpPos->x, (-80*grpScale->y)+grpPos->y);
    MdMessWinSpeedSet(mess, 4, 0);
    MdMessWinHomeClear(mess, 5);
    MdMessWinInsertMultiMesSet(mess, 5, 0x1F003E, mesR);
    MdMessWinPosSet(mess, 5, (5*grpScale->x)+grpPos->x, (-80*grpScale->y)+grpPos->y);
    MdMessWinSpeedSet(mess, 5, 0);
    MdMessWinScaleSet(mess, 4, 0.85f*grpScale->x, grpScale->y);
    MdMessWinScaleSet(mess, 5, 0.85f*grpScale->x, grpScale->y);
    }
}

/* 10 insns */
void fn_1_1B26C(void)
{
    fn_1_1B418();
    fn_1_A930(0);
}

/* 0x3350 */ s16 lbl_1_data_3350[10] = { 502, 482, 602, 682, 642, 442, 662, 462, 622, 562 };

/* 97 insns */
void fn_1_1B294(void)
{
    MDREC_SNDLIST *list = &lbl_1_data_3110[lbl_1_bss_7E8->listNo]; //r30
    MDREC_SNDITEM *item = &list->item[lbl_1_bss_7E8->cursor]; //r31
    s16 fxNo; //r29
    fn_1_1B418();
    if(!list->enable) {
        HuAudFXPlay(MSM_SE_CMN_05);
        return;
    }
    lbl_1_bss_7E8->playType = item->type;
    if(item->type == MDREC_SND_BGM) {
        lbl_1_bss_7E8->streamNo = HuAudBGMPlay(item->no);
    } else if(item->type == MDREC_SND_FX) {
        if(lbl_1_bss_7E8->listNo >= 8 && lbl_1_bss_7E8->listNo < 18) {
            fxNo = item->no+(lbl_1_data_3350[lbl_1_bss_7E8->listNo-8]-502);
        } else {
            fxNo = item->no;
        }
        lbl_1_bss_7E8->fxNo = HuAudFXPlay(fxNo);
    } else if(item->type == MDREC_SND_JINGLE) {
        lbl_1_bss_7E8->streamNo = HuAudJinglePlay(item->no);
    }
}

/* 64 insns */
void fn_1_1B418(void)
{
    int i; //r31
    if(lbl_1_bss_7E8->playType == MDREC_SND_BGM || lbl_1_bss_7E8->playType == MDREC_SND_JINGLE) {
        i = 0;
        HuAudSStreamAllFadeOut(100);
        if(lbl_1_bss_7E8->streamNo != -1) {
            while(HuAudSStreamStatGet(lbl_1_bss_7E8->streamNo) != 0) {
                if(i >= 30) {
                    HuAudSStreamAllStop();
                    break;
                }
                i++;
                HuPrcVSleep();
            }
        }
    } else if(lbl_1_bss_7E8->playType == MDREC_SND_FX) {
        HuAudFXFadeOut(lbl_1_bss_7E8->fxNo, 100);
        for(i=0; i<7; i++) {
            HuPrcVSleep();
        }
    }
    HuPrcVSleep();
}
