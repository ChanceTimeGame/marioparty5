/*
 * staffdll staff.c -- the staff roll at the end of a story (storymodedll's won-finale exit).
 * Plays movie/st_movie.thp and scrolls the credits from staffData in HuWin windows over it,
 * then shows the end, end-message and copyright sprites. StaffExit saves (SLSaveStaffExec)
 * and returns two overlay-history levels.
 */

#include "REL/staffDll.h"

#include "game/audio.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/gamework.h"
#include "game/esprite.h"
#include "game/thpmain.h"
#include "game/gamemes.h"
#include "game/saveload.h"
#include "datadir_enum.h"

#define STAFF_END (-1)
#define STAFF_WAIT (-2)  /* arg: tenths of a second */
#define STAFF_KEEP (-3)  /* arg: window that stays for the next block */
#define STAFF_NEXTTYPE (-4)
#define STAFF_TYPE (-5)

/* the roll script per languageNo: message numbers (one window each, up to five) and commands */
static const s32 staffData[2][1024] = {
    {
        -2, 50,
        0x0001006E, 0x00010000,
        -2, 30,
        0x0001006F, 0x00010001,
        -2, 30,
        0x00010070, 0x00010002,
        -2, 30,
        0x00010071, 0x00010003,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010004, 0x00010005, 0x00010006,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010007, 0x00010008,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010009, 0x0001000A,
        -2, 30,
        0x00010072, 0x0001000B,
        -2, 30,
        0x00010073, 0x0001000C, 0x0001000D, 0x0001000E,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001000F, 0x00010010,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010011, 0x00010012,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010013, 0x00010014,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010015, 0x00010016, 0x00010017,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010018, 0x00010019,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001A, 0x0001001B,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001C, 0x0001001D, 0x0001001E,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001F, 0x00010020,
        -2, 30,
        0x00010074, 0x00010021,
        -2, 30,
        0x00010075, 0x00010022,
        -2, 30,
        0x00010076, 0x00010023, 0x00010024, 0x00010025,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010026, 0x00010027,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010028, 0x00010029,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002A, 0x0001002B,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002C, 0x0001002D, 0x0001002E,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002F, 0x00010030, 0x00010031,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010032, 0x00010033,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010034, 0x00010035, 0x00010036,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010037, 0x00010038, 0x00010039,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001003A, 0x0001003B, 0x0001003C,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001003D, 0x0001003E, 0x0001003F,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010040, 0x00010041,
        -2, 30,
        0x00010077, 0x00010042, 0x00010043,
        -2, 30,
        0x00010078, 0x00010044,
        -2, 30,
        0x00010079, 0x00010045,
        -2, 30,
        0x0001007A, 0x00010046,
        -2, 30,
        0x0001007B, 0x00010047, 0x00010048, 0x00010049,
        -2, 30,
        -3, 0,
        0x0001007B, 0x0001004A, 0x0001004B,
        -2, 30,
        0x0001007C, 0x0001004C, 0x0001004D,
        -2, 30,
        0x0001007D, 0x0001004E, 0x0001004F,
        -2, 30,
        0x0001007E, 0x00010050,
        -2, 30,
        0x0001007F, 0x00010052, 0x00010053,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010054, 0x00010055,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010056, 0x00010057, 0x00010058,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010059,
        -2, 30,
        -3, 0,
        0x0001007F, 0x0001005A, 0x0001005B, 0x0001005C,
        -2, 30,
        0x00010081, 0x0001005F, 0x00010060,
        -2, 30,
        0x00010082, 0x00010061, 0x00010066, 0x00010062,
        -2, 30,
        0x00010083, 0x0001005E, 0x0001005D,
        -2, 30,
        0x00010080, 0x00010063,
        -2, 30,
        0x00010084, 0x00010064, 0x00010065,
        -2, 30,
        -1
    },
    {
        -2, 50,
        0x0001006E, 0x00010000,
        -2, 30,
        0x0001006F, 0x00010001,
        -2, 30,
        0x00010070, 0x00010002,
        -2, 30,
        0x00010071, 0x00010003,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010004, 0x00010005, 0x00010006,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010007, 0x00010008,
        -2, 30,
        -3, 0,
        0x00010071, 0x00010009, 0x0001000A,
        -2, 30,
        -5, -24,
        0x00010072, 0x0001000B,
        -2, 30,
        0x00010073, 0x0001000C, 0x0001000D, 0x0001000E,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001000F, 0x00010010,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010011, 0x00010012,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010013, 0x00010014,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010015, 0x00010016, 0x00010017,
        -2, 30,
        -3, 0,
        0x00010073, 0x00010018, 0x00010019,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001A, 0x0001001B,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001C, 0x0001001D, 0x0001001E,
        -2, 30,
        -3, 0,
        0x00010073, 0x0001001F, 0x00010020,
        -2, 30,
        -5, -64,
        0x00010074, 0x00010021,
        -2, 30,
        0x00010075, 0x00010022,
        -2, 30,
        0x00010076, 0x00010023, 0x00010024, 0x00010025,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010026, 0x00010027,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010028, 0x00010029,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002A, 0x0001002B,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002C, 0x0001002D, 0x0001002E,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001002F, 0x00010030, 0x00010031,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010032, 0x00010033,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010034, 0x00010035, 0x00010036,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010037, 0x00010038, 0x00010039,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001003A, 0x0001003B, 0x0001003C,
        -2, 30,
        -3, 0,
        0x00010076, 0x0001003D, 0x0001003E, 0x0001003F,
        -2, 30,
        -3, 0,
        0x00010076, 0x00010040, 0x00010041,
        -2, 30,
        0x00010077, 0x00010042, 0x00010043,
        -2, 30,
        -5, -64,
        0x00010078, 0x00010044,
        -2, 30,
        0x00010079, 0x00010045,
        -2, 30,
        -5, 16,
        0x0001007A, 0x00010046,
        -2, 30,
        0x0001007B, 0x00010047, 0x00010048, 0x00010049,
        -2, 30,
        -3, 0,
        0x0001007B, 0x0001004A, 0x0001004B,
        -2, 30,
        0x0001007C, 0x0001004C, 0x0001004D,
        -2, 30,
        -5, -16,
        0x0001007D, 0x0001004E, 0x0001004F,
        -2, 30,
        0x0001007E, 0x00010050,
        -2, 30,
        -5, -64,
        0x00010085, 0x00010088, 0x00010089, 0x0001008A,
        -2, 30,
        -3, 0,
        0x00010085, 0x0001008B, 0x0001008C,
        -2, 30,
        -5, -64,
        0x00010086, 0x0001008D, 0x0001008E,
        -2, 30,
        0x00010087, 0x0001008F, 0x00010090, 0x00010091,
        -2, 30,
        -3, 0,
        0x00010087, 0x00010092, 0x00010093,
        -2, 30,
        -3, 0,
        0x00010087, 0x00010094, 0x00010095,
        -2, 30,
        -5, -16,
        0x0001007F, 0x00010096, 0x00010097,
        -2, 30,
        -3, 0,
        0x00010052, 0x00010053,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010054, 0x00010055,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010056, 0x00010057, 0x00010058,
        -2, 30,
        -3, 0,
        0x0001007F, 0x00010059,
        -2, 30,
        -3, 0,
        0x0001007F, 0x0001005A, 0x0001005B, 0x0001005C,
        -2, 30,
        0x00010081, 0x0001005F, 0x00010060,
        -2, 30,
        0x00010082, 0x00010061, 0x00010066, 0x00010062,
        -2, 30,
        0x00010083, 0x0001005E, 0x0001005D,
        -2, 30,
        0x00010080, 0x00010063,
        -2, 30,
        -4, 1,
        0x00010084, 0x00010064, 0x00010065,
        -2, 30,
        -1
    },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
static OMOBJ *staffObj;
static OMOBJ *staffOutView;
static OMOBJMAN *objman;
static s16 staffMes;
u8 lbl_1_bss_A0[0x6]; /* unreferenced */
static s32 glightId;
static s32 staffEndSprId;
static s32 staffEndMesSprId;
u8 lbl_1_bss_90[0x4]; /* unreferenced */
static s32 staffCopyrightSprId;
static HUSPRID staffTHPSprId; /* retail names: this holds the sprite group */
static HUSPRGRPID staffTHPSprGId; /* ... and this the THP sprite */
static HUWINID staffWinId[5];
static HuVec2f staffWinSize[5];
static HuVec2f staffWinPos[5];
static s16 staffType;
static s16 staffNextType;
static s32 staffTime;
static s32 staffNo;
static s32 staffLineNo;
u8 lbl_1_bss_14[0x8]; /* unreferenced */
static s32 staffEndF;
static s32 lbl_1_bss_8[3]; /* [0]: the movie / end-sprite sequence; retail leaves 0x10 bytes from staffEndMesTime to staffEndF */
static float staffEndMesTime;

s32 lbl_1_data_0[2] = { -1, 1 }; /* unreferenced */
static s32 staffMode = -1;
static s16 staffWinMoveF[5] = { 0, 0, 0, 0, 0 };

void StaffStub(void) { }

/* 0..1 along a move of accelTime frames speeding up, flatTime at full speed and decelTime
 * slowing down */
float StaffPosGet(float time, float accelTime, float flatTime, float decelTime)
{
    float total = decelTime / 2.0f + (accelTime / 2.0f + flatTime);
    return (time < accelTime) ? ((1.0f + time) / 2.0f * time / accelTime) / total
         : (time < accelTime + flatTime) ? ((1.0f + accelTime) / 2.0f * accelTime / accelTime) / total + (time - accelTime) / total
         : (time < decelTime + (accelTime + flatTime) - 1.0f)
             ? 1.0f - ((1.0f + (decelTime + (accelTime + flatTime) - time - 1.0f)) / 2.0f * (decelTime + (accelTime + flatTime) - 1.0f - time - 1.0f) / (decelTime - 1.0f)) / total
         : 1.0f;
}

void StaffMain(OMOBJ *obj)
{
    s32 langNo;
    s32 lang;
    s32 num;
    s32 i;
    float sx;
    float sy;
    float sumW;
    float sumH;
    float w;
    float h;
    float pos;
    float copyPos;
    float copyPos2;
    s32 flag;
    s32 pressSum;
    s32 player;
    s32 btn;

    langNo = GwCommon.languageNo;
    lang = langNo;
    switch(lang) {
        case 0:
            lang = 0;
            num = 18;
            break;
        case 1:
            lang = 1;
            num = 9;
            break;
    }
    if(lbl_1_bss_8[0] == 0) {
        staffTHPSprId = HuSprGrpCreate(1);
        lbl_1_bss_8[0]++;
    }
    if(lbl_1_bss_8[0] == 1) {
        staffTHPSprGId = HuTHPSprCreateVol("movie/st_movie.thp", 0, 5, 105.0f);
        if(staffTHPSprGId != -1) {
            {
                HuSprGrpMemberSet(staffTHPSprId, 0, staffTHPSprGId);
                HuSprPosSet(staffTHPSprId, 0, 288.0f, 192.0f);
                HuSprGrpDrawNoSet(staffTHPSprId, 127);
                HuSprPriSet(staffTHPSprId, 0, 5);
            }
            lbl_1_bss_8[0]++;
        }
    } else if(lbl_1_bss_8[0] == 2 || lbl_1_bss_8[0] == 3) {
        lbl_1_bss_8[0]++;
    } else if(lbl_1_bss_8[0] == 4) {
        if(HuTHPFrameGet() <= 120 && HuTHPFrameGet() >= 60) {
            espDispOn(staffEndSprId);
        }
        if(HuTHPEndCheck())
        {
            HuTHPClose();
            lbl_1_bss_8[0]++;
        }
    } else if(lbl_1_bss_8[0] == 5) {
        if(!HuTHPProcCheck()) {
            HuSprGrpKill(staffTHPSprId);
            lbl_1_bss_8[0]++;
            staffEndMesTime = 0.0f;
        }
    } else if(lbl_1_bss_8[0] == 6) {
        staffEndMesTime += 1.0f;
        espDispOn(staffEndMesSprId);
        espTPLvlSet(staffEndMesSprId, staffEndMesTime / 120.0f);
        if(staffEndMesTime >= 120.0f) {
            lbl_1_bss_8[0]++;
        }
    } else {
        lbl_1_bss_8[0] == 7;
    }
    if(lbl_1_bss_8[0] >= 4) {
        if(lang == 0) {
            sx = 0.75f;
            sy = 0.75f;
        } else {
            sx = 1.0f;
            sy = 0.75f;
        }
        if(staffMode == -1) {
            if(staffData[lang][staffNo] != STAFF_WAIT) {
                staffMode++;
                staffTime = 0;
            } else {
                staffTime++;
                if(staffTime >= staffData[lang][staffNo + 1] * 60 / 10) {
                    staffMode++;
                    staffTime = 0;
                    staffNo += 2;
                }
            }
        } else if(staffMode == 0) {
            staffLineNo = 0;
            if(staffData[lang][staffNo] == STAFF_NEXTTYPE) {
                staffNo++;
                staffNextType = staffData[lang][staffNo];
                staffNo++;
            } else if(staffData[lang][staffNo] == STAFF_TYPE) {
                staffNo++;
                staffType = staffData[lang][staffNo];
                staffNo++;
            } else {
                sumW = 0.0f;
                sumH = 0.0f;
                for(i = 0; i < 5; i++) {
                    if(staffData[lang][staffNo] < 0) {
                        break;
                    }
                    HuWinMesMaxSizeGet(1, &staffWinSize[i], staffData[lang][staffNo]);
                    staffWinSize[i].y = (i == 0) ? 28 : 28;
                    if(staffWinMoveF[i] == 0) {
                        staffWinId[i] = HuWinCreate(-200.0f, -200.0f, staffWinSize[i].x, staffWinSize[i].y, 1);
                        HuWinBGTPLvlSet(staffWinId[i], 0.0f);
                        HuWinMesSpeedSet(staffWinId[i], 0);
                        HuWinMesSet(staffWinId[i], staffData[lang][staffNo]);
                        HuWinScaleSet(staffWinId[i], sx, sy);
                    }
                    staffLineNo++;
                    staffNo++;
                }
                for(i = 0; i < staffLineNo; i++) {
                    if(i != 0) {
                        w = sx * staffWinSize[i].x;
                    } else {
                        w = 0.0f;
                    }
                    sumW += w;
                    if(i != 0) {
                        h = sy * staffWinSize[i].y;
                    } else {
                        h = 0.0f;
                    }
                    sumH += h;
                }
                for(i = 0; i < staffLineNo; i++) {
                    if(staffWinMoveF[i] != 1) {
                        flag = FALSE;
                        if(staffNextType == 0 && i == 0) {
                            flag = TRUE;
                        }
                        staffWinPos[i].x = (flag) ? 82.28571f : 288.0f - sx * staffWinSize[i].x / 2.0f;
                    }
                    staffWinPos[i].y = (i == 0) ? 346.0
                        : (i == 1) ? 417.0f + 28.0f * (1.0f - sy) - 2.0f * (28.0f * sy) - sumH * 0.5f + sy * staffWinSize[i].y
                        : sy * staffWinSize[i].y / 2.0f + (staffWinPos[i - 1].y + sy * staffWinSize[i - 1].y / 2.0f);
                }
                staffMode++;
                staffTime = 0;
                staffType = 0;
            }
        } else if(staffMode == 1 || staffMode == 3) {
            staffTime++;
            pos = (staffMode == 1) ? StaffPosGet(staffTime, 1.0f, num - num / 2, num / 2) - 1.0f
                : StaffPosGet(staffTime, num, num - num, 1.0f);
            for(i = staffLineNo - 1; i >= 0; i--) {
                if(staffWinMoveF[i] != 1) {
                    HuWinPosSet(staffWinId[i], staffWinPos[i].x - 480.0f * pos, staffWinPos[i].y);
                }
            }
            if(staffTime >= num) {
                staffMode++;
                staffTime = 0;
                if(staffMode == 2) {
                    for(i = 0; i < 5; i++) {
                        staffWinMoveF[i] = 0;
                    }
                }
            }
        } else if(staffMode == 2) {
            if(staffData[lang][staffNo] != STAFF_WAIT) {
                staffMode++;
                staffTime = 0;
            } else {
                staffTime++;
                if(staffTime >= staffData[lang][staffNo + 1] * 60 / 10) {
                    staffMode++;
                    staffTime = 0;
                    staffNo += 2;
                    if(staffData[lang][staffNo] == STAFF_KEEP) {
                        staffNo++;
                        staffWinMoveF[staffData[lang][staffNo]] = 1;
                        staffNo++;
                    }
                }
            }
        } else if(staffMode == 4) {
            for(i = 0; i < staffLineNo; i++) {
                if(staffWinMoveF[i] == 0) {
                    HuWinExKill(staffWinId[i]);
                }
            }
            staffMode = 0;
            if(staffData[lang][staffNo] == STAFF_END) {
                staffNo = 0;
                staffMode = 5;
                staffTime = 0;
            }
        } else if(staffMode == 5) {
            staffTime++;
            copyPos = StaffPosGet(staffTime, 1.0f, 11.0f, 11.0f) - 1.0f;
            espDispOn(staffCopyrightSprId);
            espPosSet(staffCopyrightSprId, (s32)(288.0f - 640.0f * copyPos), 392.0f);
            if(staffTime >= 22) {
                staffMode++;
                staffTime = 0;
            }
        } else if(staffMode == 6) {
            staffTime++;
            if(staffTime >= 1200) {
                staffMode++;
                staffTime = 0;
            }
        } else if(staffMode == 7) {
            staffTime++;
            copyPos2 = StaffPosGet(staffTime, 11.0f, 11.0f, 1.0f);
            espDispOn(staffCopyrightSprId);
            espPosSet(staffCopyrightSprId, (s32)(288.0f - 640.0f * copyPos2), 392.0f);
            if(staffTime >= 22) {
                staffMode++;
                staffTime = 0;
            }
        }
    }
    if(staffEndF == 0) {
        pressSum = 0;
        for(player = 0; player < 10; player++) {
            pressSum += GwCommon.storyPlayNum[player];
        }
        for(player = 0; player < 4; player++) {
            if(GwPlayerConf[player].type == GW_TYPE_MAN) {
                btn = HuPadBtn[GwPlayerConf[player].padNo];
                if((pressSum > 1 && !WipeCheckEnd() && (btn & PAD_BUTTON_START)) || (lbl_1_bss_8[0] >= 7 && (btn & (PAD_BUTTON_START | PAD_BUTTON_A | PAD_BUTTON_B)))) {
                    staffEndF = 1;
                }
            }
        }
        if(omSysExitReq) {
            staffEndF = 1;
        }
        if(staffEndF == 1) {
            HuAudFadeOut((lbl_1_bss_8[0] == 7) ? 3500 : 1250);
            if(HuTHPProcCheck()) {
                HuTHPSetVolume(0, (lbl_1_bss_8[0] == 7) ? 3500 : 1250);
            }
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, (lbl_1_bss_8[0] == 7) ? 120 : 45);
        }
    }
    staffEndF = staffEndF + (staffEndF > 0);
    if(staffEndF > 2 && !WipeCheckEnd()) {
        obj->objFunc = StaffExit;
    }
}

void StaffInit(OMOBJ *obj)
{
    staffEndSprId = espEntry(DATANUM(DATA_staff, 0), 10, 0);
    espDispOff(staffEndSprId);
    espPosSet(staffEndSprId, 288.0f, 192.0f);
    espDrawNoSet(staffEndSprId, 127);
    staffEndMesSprId = espEntry(DATANUM(DATA_staff, 1), 8, 0);
    espDispOff(staffEndMesSprId);
    espTPLvlSet(staffEndMesSprId, 0.0f);
    espPosSet(staffEndMesSprId, 291.0f, 200.0f);
    espDrawNoSet(staffEndMesSprId, 0);
    staffCopyrightSprId = espEntry(DATANUM(DATA_staff, 2), 5, 0);
    espDispOff(staffCopyrightSprId);
    espDrawNoSet(staffCopyrightSprId, 0);
    espPosSet(staffCopyrightSprId, 288.0f, 392.0f);
    espAttrSet(staffCopyrightSprId, HUSPR_ATTR_LINEAR);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    obj->objFunc = StaffMain;
}

void ObjectSetup(void)
{
    OSReport("******* Staff ObjectSetup *********\n");
    objman = omInitObjMan(600, 8192);
    omGameSysInit(objman);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 25000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    CZoom = 4000.0f;
    Center.x = 1800.0f;
    Center.y = -150.0f;
    Center.z = 0.0f;
    CRot.x = -40.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    {
        HuVecF lightPos = { 0.0f, 5000.0f, 0.0f };
        HuVecF lightDir = { 0.0f, -1.0f, -0.5f };
        GXColor lightColor = { 255, 255, 255, 255 };
        glightId = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    }
    Hu3DGLightStaticSet(glightId, TRUE);
    Hu3DGLightInfinitytSet(glightId);
    staffMes = -1;
    staffOutView = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    staffOutView->work[0] = 1;
    staffObj = omAddObjEx(objman, 0, 0, 0, -1, StaffInit);
}

void StaffExit(OMOBJ *obj)
{
    if(WipeCheckEnd()) {
        return;
    }
    HuTHPClose();
    while(HuTHPProcCheck()) {
        HuPrcVSleep();
    }
    if(staffMes >= 0) {
        GameMesKill(staffMes);
    }
    GameMesClose();
    HuAudAllStop();
    SLSaveStaffExec();
    omOvlReturnEx(2, 1);
    while(1) {
        HuPrcVSleep();
    }
}
