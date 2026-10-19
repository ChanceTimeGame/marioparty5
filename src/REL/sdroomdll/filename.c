/*
 * sdroomdll filename.c -- machine name entry: fileseldll's NameEnter* (filename.c) with the
 * room's own sprites/messages, the garage windows (lbl_1_bss_570[0] / lbl_1_bss_56E), the pad
 * mask helpers fn_1_4FD0/fn_1_507C, 8 default names, and the name written to the caller's buffer.
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
#include "math.h"
#include "msm_se.h"
#include "humath.h"
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_498 = 288.0f; /* 0x498 */
static const float lbl_1_rodata_49C = 186.0f; /* 0x49C */
static const double lbl_1_rodata_4A0 = 1.0; /* 0x4A0 */
static const double lbl_1_rodata_4A8 = 3.141592653589793; /* 0x4A8 */
static const double lbl_1_rodata_4B0 = 90.0; /* 0x4B0 */
static const double lbl_1_rodata_4B8 = 10.0; /* 0x4B8 */
static const double lbl_1_rodata_4C0 = 180.0; /* 0x4C0 */
static const float lbl_1_rodata_4C8 = 400.0f; /* 0x4C8 */
static const float lbl_1_rodata_4CC = 196.0f; /* 0x4CC */
static const float lbl_1_rodata_4D0 = 61.0f; /* 0x4D0 */
static const float lbl_1_rodata_4D4 = 0.0f; /* 0x4D4 */
static const float lbl_1_rodata_4D8 = -1.0f; /* 0x4D8 */
static const float lbl_1_rodata_4DC = 1.0f; /* 0x4DC */
static const double lbl_1_rodata_4E0 = 0.5; /* 0x4E0 */
static const double lbl_1_rodata_4E8 = 3.0; /* 0x4E8 */
static const float lbl_1_rodata_4F0 = 409600.0f; /* 0x4F0 */
static const double lbl_1_rodata_4F8 = 0.1; /* 0x4F8 */
static const float lbl_1_rodata_500 = 55.0f; /* 0x500 */
static const double lbl_1_rodata_508 = 0.8; /* 0x508 */
/* 0x510 lbl_1_rodata_510 = 4503601774854144: int->float conversion constant, compiler-generated */

typedef struct NameKeyboard_s {
    s16 x;
    s16 y;
    u16 val;
} NAMEKEYBOARD;

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xA8C */ static HUSPRGRPID nameGrpId;
/* 0xA8A */ static s16 nameKeyboardNum;
/* 0xA88 */ s16 lbl_1_bss_A88;
/* 0xA00 */ static char nameDefault[8][17];
/* 0x9D4 */ static u16 nameMesTemp[22];
/* 0x9D2 */ static s16 nameCharNo;
/* 0x9A0 */ static char nameMes[50];

/* --- functions (reference order), .data placed before its first user --- */
/* 0x15F0 */ static NAMEKEYBOARD keyboardMain[] = {
    { 65, 80, 'A' },
    { 95, 80, 'B' },
    { 125, 80, 'C' },
    { 155, 80, 'D' },
    { 185, 80, 'E' },
    { 215, 80, 'F' },
    { 245, 80, 'G' },
    { 275, 80, 'H' },
    { 305, 80, 'I' },
    { 335, 80, 'J' },
    { 365, 80, 'K' },
    { 395, 80, 'L' },
    { 425, 80, 'M' },
    { 455, 80, 'N' },
    { 65, 110, 'O' },
    { 95, 110, 'P' },
    { 125, 110, 'Q' },
    { 155, 110, 'R' },
    { 185, 110, 'S' },
    { 215, 110, 'T' },
    { 245, 110, 'U' },
    { 275, 110, 'V' },
    { 305, 110, 'W' },
    { 335, 110, 'X' },
    { 365, 110, 'Y' },
    { 395, 110, 'Z' },
    { 425, 110, ' ' },
    { 455, 110, ' ' },
    { 65, 140, 'a' },
    { 95, 140, 'b' },
    { 125, 140, 'c' },
    { 155, 140, 'd' },
    { 185, 140, 'e' },
    { 215, 140, 'f' },
    { 245, 140, 'g' },
    { 275, 140, 'h' },
    { 305, 140, 'i' },
    { 335, 140, 'j' },
    { 365, 140, 'k' },
    { 395, 140, 'l' },
    { 425, 140, 'm' },
    { 455, 140, 'n' },
    { 65, 170, 'o' },
    { 95, 170, 'p' },
    { 125, 170, 'q' },
    { 155, 170, 'r' },
    { 185, 170, 's' },
    { 215, 170, 't' },
    { 245, 170, 'u' },
    { 275, 170, 'v' },
    { 305, 170, 'w' },
    { 335, 170, 'x' },
    { 365, 170, 'y' },
    { 395, 170, 'z' },
    { 425, 170, 194 },
    { 455, 170, 195 },
    { 81, 246, 0x100 },
    { 141, 246, 0x200 },
    { 277, 244, 0x400 },
    { 407, 243, 0x500 },
    { 0, 0, 0 },
};

static NAMEKEYBOARD keyboardNumSpc[] = {
    { 125, 80, '1' },
    { 155, 80, '2' },
    { 185, 80, '3' },
    { 215, 80, '4' },
    { 245, 80, '5' },
    { 275, 80, '6' },
    { 305, 80, '7' },
    { 335, 80, '8' },
    { 365, 80, '9' },
    { 395, 80, '0' },
    { 425, 80, 134 },
    { 125, 110, '[' },
    { 155, 110, '\\' },
    { 185, 110, '~' },
    { 215, 110, 127 },
    { 245, 110, '<' },
    { 275, 110, '=' },
    { 305, 110, '_' },
    { 335, 110, ']' },
    { 365, 110, '^' },
    { 395, 110, 130 },
    { 425, 110, 133 },
    { 125, 140, 0xE00|3 },
    { 155, 140, 0xE00|4 },
    { 185, 140, 0xE00|5 },
    { 215, 140, 0xE00|6 },
    { 245, 140, 0xE00|9 },
    { 275, 140, 0xE00|7 },
    { 305, 140, 0xE00|1 },
    { 335, 140, 0xE00|11 },
    { 365, 140, ';' },
    { 395, 140, ':' },
    { 425, 140, '}' },
    { 81, 246, 0x100 },
    { 141, 246, 0x200 },
    { 277, 244, 0x400 },
    { 407, 243, 0x500 },
    { 0, 0, 0 },
};

/* 0x1844 */ /* {layout, anim file number} pairs: the odd entries are DATANUMs kept in a pointer slot */
static NAMEKEYBOARD *keyboardTbl[3*2] = {
    keyboardMain,
    (NAMEKEYBOARD *)DATANUM(DATA_sdroom, 25),
    keyboardNumSpc,
    (NAMEKEYBOARD *)DATANUM(DATA_sdroom, 26),
};

void NameEnterInit(void)
{
    s16 i;
    HUSPRGRPID grpId;
    char *mes;
    s16 j;
    HUSPRID sprId;
    ANIMDATA *animP;
    
    nameGrpId = grpId = HuSprGrpCreate(5);
    animP = HuSprAnimDataRead(DATANUM(DATA_sdroom, 27));
    sprId = HuSprCreate(animP, 45, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprColorSet(grpId, 0, 255, 255, 0);
    HuSprDispOff(grpId, 0);
    animP = HuSprAnimDataRead(DATANUM(DATA_sdroom, 28));
    sprId = HuSprCreate(animP, 45, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprColorSet(grpId, 1, 255, 255, 0);
    HuSprDispOff(grpId, 1);
    for(nameKeyboardNum = 0; keyboardTbl[nameKeyboardNum*2]; nameKeyboardNum++) {
        animP = HuSprAnimDataRead((unsigned int)keyboardTbl[(nameKeyboardNum*2)+1]);
        sprId = HuSprCreate(animP, 50, 0);
        HuSprGrpMemberSet(grpId, nameKeyboardNum+2, sprId);
        HuSprDispOff(grpId, nameKeyboardNum+2);
    }
    HuSprGrpPosSet(grpId, 288, 186);
    lbl_1_bss_A88 = 0;
    for(i=0; i<8; i++) {
        for(j=0; j<17; j++) {
            nameDefault[i][j] = 0;
        }
    }
    for(i=0; i<8; i++) {
        mes = HuWinMesPtrGet(0x19006B+i);
        for(j=0; *mes; mes++) {
            if(*mes >= '0') {
                nameDefault[i][j++] = *mes;
            }
        }
    }
}

s32 NameEnterMain(char *name, s32 padNo)
{
    NAMEKEYBOARD *keyboard;
    s16 i;
    s16 keyNo;
    s16 tempIdx;
    s16 keyboardNo;
    s16 cursorIdx;
    HUWINID nameWinId;
    s16 prevKeyNo;
    s16 prevKeyboard;
    s32 result;
    s16 prevCharNo;
    
    float cursorX;
    float cursorY;
    float moveX;
    float moveY;
    float normX;
    float normY;
    float scale;
    float cursorMag;
    float prevCursorMag;
    float normMag;
    
    keyboardNo = prevKeyboard = 0;
    keyNo = 0;
    cursorIdx = 0;
    nameCharNo = 0;
    nameMes[0] = '\0';
    HuSprDispOn(nameGrpId, keyboardNo+2);
    HuSprDispOn(nameGrpId, cursorIdx);
    keyboard = keyboardTbl[keyboardNo*2];
    HuSprPosSet(nameGrpId, cursorIdx, keyboard[keyNo].x-260, keyboard[keyNo].y-131);
    for(i=1; i<=10; i++) {
        scale = 1-HuSin((i/10.0)*90);
        HuSprGrpPosSet(nameGrpId, 288, 186-(400*scale));
        HuPrcVSleep();
    }
    HuWinExOpen(lbl_1_bss_570[0]);
    HuWinMesSet(lbl_1_bss_570[0], 0x190062);
    HuWinMesSet(lbl_1_bss_56E, 0x20003);
    HuWinDispOn(lbl_1_bss_56E);
    nameWinId = HuWinCreate(196, 61, 176, 26, 0);
    HuWinBGTPLvlSet(nameWinId, 0);
    HuWinMesSpeedSet(nameWinId, 0);
    HuWinPriSet(nameWinId, 40);
    while(1) {
        moveX = moveY =  0;
        if(fn_1_507C(padNo) & PAD_BUTTON_LEFT) {
            moveX = -1;
        } else if(fn_1_507C(padNo) & PAD_BUTTON_RIGHT) {
            moveX = 1;
        }
        if(fn_1_507C(padNo) & PAD_BUTTON_UP) {
            moveY = -1;
        } else if(fn_1_507C(padNo) & PAD_BUTTON_DOWN) {
            moveY = 1;
        }
        if(moveX || moveY) {
            scale = HuMagPoint2D(moveX, moveY);
            normX = moveX/scale;
            normY = moveY/scale;
            prevCursorMag = 409600;
            prevKeyNo = -1;
            for(i=0; keyboard[i].val; i++) {
                if(i != keyNo) {
                    cursorX = keyboard[i].x-keyboard[keyNo].x;
                    cursorY = keyboard[i].y-keyboard[keyNo].y;
                    cursorMag = HuMagPoint2D(cursorX, cursorY);
                    cursorX /= cursorMag;
                    cursorY /= cursorMag;
                    normMag = HuMagPoint2D(cursorX-normX, cursorY-normY);
                    if(keyboard[keyNo].val >= 0x100 && keyboard[keyNo].val <= 0x500 &&
                        keyboard[i].val >= 0x100 && keyboard[i].val <= 0x500 &&
                        normMag < 0.1 && cursorMag < 55+prevCursorMag) {
                            prevCursorMag = cursorMag;
                            prevKeyNo = i;
                        } else if(normMag < 0.8 && cursorMag < prevCursorMag) {
                            prevCursorMag = cursorMag;
                            prevKeyNo = i;
                        }
                }
            }
            if(prevKeyNo != -1) {
                HuAudFXPlay(MSM_SE_CMN_01);
                keyNo = prevKeyNo;
                if(keyboard[keyNo].val == 0x400 || keyboard[keyNo].val == 0x500) {
                    HuSprDispOff(nameGrpId, 0);
                    HuSprDispOn(nameGrpId, 1);
                    cursorIdx = 1;
                } else {
                    HuSprDispOn(nameGrpId, 0);
                    HuSprDispOff(nameGrpId, 1);
                    cursorIdx = 0;
                }
            }
        }
        if(fn_1_4FD0(padNo) & PAD_BUTTON_START) {
            HuAudFXPlay(MSM_SE_CMN_01);
            for(keyNo=0; keyboard[keyNo].val && keyboard[keyNo].val != 0x500; keyNo++);
            HuSprDispOff(nameGrpId, 0);
            HuSprDispOn(nameGrpId, 1);
            cursorIdx = 1;
            i = NameEnterClose(nameWinId);
            if(i) {
                nameCharNo = i;
                prevCharNo = i;
                for(i=tempIdx=0; i<prevCharNo; tempIdx++, i++) {
                    if(nameMes[i+1] == 0x80 || nameMes[i+1] == 0x81) {
                        nameMesTemp[tempIdx] = (nameMes[i] << 8)|nameMes[i+1];
                        nameCharNo--;
                        i++;
                    } else {
                        nameMesTemp[tempIdx] = nameMes[i];
                    }
                }
            }
        } else if(fn_1_4FD0(padNo) & PAD_BUTTON_A) {
            if((keyboard[keyNo].val < 0x100 || keyboard[keyNo].val > 0x500) && nameCharNo < 8) {
                nameMesTemp[nameCharNo] = keyboard[keyNo].val;
                nameCharNo++;
                for(i=tempIdx=0; i<nameCharNo; i++) {
                    if(nameMesTemp[i] > 255) {
                        nameMes[tempIdx++] = nameMesTemp[i] >> 8;
                        nameMes[tempIdx++] = nameMesTemp[i];
                    } else {
                        nameMes[tempIdx++] = nameMesTemp[i];
                    }
                }
                nameMes[tempIdx] = 0;
                HuWinMesSet(nameWinId, MESSNUM_PTR(nameMes));
                if(nameCharNo >= 8) {
                    for(keyNo=0; keyboard[keyNo].val && keyboard[keyNo].val != 0x500; keyNo++);
                    HuSprDispOff(nameGrpId, 0);
                    HuSprDispOn(nameGrpId, 1);
                    cursorIdx = 1;
                    goto sePlay;
                } else {
                    goto sePlay;
                }
            } else {
                if(keyboard[keyNo].val == 0x100) {
                    keyboardNo = 0;
                } else if(keyboard[keyNo].val == 0x200) {
                    keyboardNo = 1;
                } else if(keyboard[keyNo].val == 0x300) {
                    keyboardNo = 2;
                } else if(keyboard[keyNo].val == 0x400) {
                    goto cancel;
                } else if(keyboard[keyNo].val == 0x500) {
                    HuAudFXPlay(MSM_SE_CMN_03);
                    if(NameEnterClose(nameWinId)) {
                        HuPrcSleep(30);
                    }
                    i = 0;
                    while(1) {
                        name[i] = nameMes[i];
                        if(nameMes[i] == 0) {
                            break;
                        }
                        i++;
                    }
                    result = 1;
                    break;
                }
                sePlay:
                HuAudFXPlay(MSM_SE_CMN_02);
            }
        }
        else if(fn_1_4FD0(padNo) & PAD_BUTTON_B) {
            cancel:
            nameCharNo--;
            if(nameCharNo < 0) {
                result = 0;
                break;
            }
            HuAudFXPlay(MSM_SE_CMN_04);
            for(i=tempIdx=0; i<nameCharNo; i++) {
                if(nameMesTemp[i] > 255) {
                    nameMes[tempIdx++] = nameMesTemp[i] >> 8;
                    nameMes[tempIdx++] = nameMesTemp[i];
                } else {
                    nameMes[tempIdx++] = nameMesTemp[i];
                }
            }
            nameMes[tempIdx] = 0;
            HuWinMesSet(nameWinId, MESSNUM_PTR(nameMes));
        } else if(fn_1_4FD0(padNo) & PAD_TRIGGER_R) {
            keyboardNo++;
            if(keyboardNo >= nameKeyboardNum) {
                keyboardNo = 0;
            }
            for(keyNo=0; keyboard[keyNo].val; keyNo++) {
                if(keyboard[keyNo].val == ((keyboardNo+1)*256)) {
                    break;
                }
            }
            cursorIdx = 0;
        } else if(fn_1_4FD0(padNo) & PAD_TRIGGER_L) {
            keyboardNo--;
            if(keyboardNo < 0) {
                keyboardNo = nameKeyboardNum-1;
            }
            for(keyNo=0; keyboard[keyNo].val; keyNo++) {
                if(keyboard[keyNo].val == ((keyboardNo+1)*256)) {
                    break;
                }
            }
            cursorIdx = 0;
        }
        if(keyboardNo != prevKeyboard) {
            tempIdx = keyboard[keyNo].val;
            HuSprDispOff(nameGrpId, prevKeyboard+2);
            
            keyboard = keyboardTbl[keyboardNo*2];
            HuSprDispOn(nameGrpId, keyboardNo+2);
            for(keyNo=0; keyboard[keyNo].val; keyNo++) {
                if(tempIdx == keyboard[keyNo].val) {
                    break;
                }
            }
            
            HuSprDispOn(nameGrpId, 0);
            HuSprDispOff(nameGrpId, 1);
            HuSprPosSet(nameGrpId, cursorIdx, keyboard[keyNo].x-260, keyboard[keyNo].y-131);
            prevKeyboard = keyboardNo;
        }
        HuSprPosSet(nameGrpId, cursorIdx, keyboard[keyNo].x-260, keyboard[keyNo].y-131);
        HuPrcVSleep();
    }
    HuWinHomeClear(lbl_1_bss_56E);
    HuWinHomeClear(lbl_1_bss_570[0]);
    HuWinExClose(lbl_1_bss_570[0]);
    HuWinDispOff(lbl_1_bss_56E);
    HuWinKill(nameWinId);
    for(i=1; i<=10; i++) {
        scale = 1-HuCos((i/10.0)*90);
        HuSprGrpPosSet(nameGrpId, 288, 186-(400*scale));
        HuPrcVSleep();
    }
    HuSprDispOff(nameGrpId, 0);
    HuSprDispOff(nameGrpId, 1);
    HuSprDispOff(nameGrpId, keyboardNo+2);
    HuPrcVSleep();
    return result;
}

s16 NameEnterClose(HUWINID winId)
{
    s16 i;
    s16 len;
    for(i=len=0; nameMes[i]; i++) {
        if(nameMes[i] && nameMes[i] != ' ') {
            len++;
        }
    }
    if(len == 0) {
        strcpy(nameMes, nameDefault[frandmod(8)]);
        HuWinMesSet(winId, MESSNUM_PTR(nameMes));
        return strlen(nameMes);
    } else {
        return 0;
    }
}