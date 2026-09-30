/*
 * m502dll m502.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/m502.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/gamemes.h"
#include "game/process.h"
#include "game/wipe.h"
#include "game/mg/timer.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s16 lbl_1_rodata_10[4] = { 0x0000, 0x0000, 0x0000, 0x0000 }; */
/* 0x18 */ /* float lbl_1_rodata_18 = 0.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 4.0f; */
/* 0x20 */ /* float lbl_1_rodata_20[2] = { 8.0f, 0.0f }; */

extern M502_WORK lbl_1_bss_0; /* the work block (.bss below); lbl_1_data_0 points at it */

int rand8(void);

/* --- .data --- */
/* 0x0 */ M502_WORK *lbl_1_data_0 = &lbl_1_bss_0;
/* 0x4 */ s32 lbl_1_data_4[1] = { 0 }; /* unreferenced zero word dtk folds into lbl_1_data_0 (size 8); an aggregate so CW keeps it in .data */
/* 0x8 jumptable_1_data_8: fn_1_5DC's switch (13 entries), emitted here by CW */
/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5034 gap_05_00005034_bss (0x4) -- dtk filler */
/* 0x5030 */ s32 lbl_1_bss_5030;
/* 0x502E gap_05_0000502E_bss (0x2) -- dtk filler */
/* 0x502C */ s16 lbl_1_bss_502C;
/* 0x5028 */ s32 lbl_1_bss_5028;
/* 0x5024 */ s32 lbl_1_bss_5024; /* unreferenced word dtk folds into lbl_1_bss_0 (0x5028): the work is 0x5024 (memset 0x5024) */
/* 0x0 */ M502_WORK lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 37 insns */
void ObjectSetup(void)
{
    M502_WORK *work;
    OMOBJMAN *objman;
    OMOBJ *obj;

    work = &lbl_1_bss_0;
    objman = omInitObjMan(0x200, 0x2000);
    omGameSysInit(objman);
    obj = omAddObjEx(objman, 100, 0, 0, -1, fn_1_134);
    obj->data = work;
    fn_1_398(work, objman, obj);
    Hu3DNoSyncSet(1);
}

/* 25 insns */
void fn_1_134(OMOBJ *obj)
{
    M502_WORK *work;

    work = obj->data;
    if (fn_1_5DC(work)) {
        fn_1_504(work);
        omDelObjEx((OMOBJMAN *)HuPrcCurrentGet(), obj);
        omOvlReturnEx(1, 1);
    }
}

/* retail never inlines the audio wrappers into fn_1_504/fn_1_5DC below them */
#pragma dont_inline on
/* 10 insns; donated: m510dll m510.c */
int fn_1_198(int seId)
{
    return HuAudFXPlay(seId);
}

/* 10 insns; donated: m510dll m510.c */
void fn_1_1C0(int seNo)
{
    HuAudFXStop(seNo);
}

/* 12 insns; donated: m510dll m510.c */
void fn_1_1E8(int seNo, s32 speed)
{
    HuAudFXFadeOut(seNo, speed);
}

/* 12 insns; donated: m510dll m510.c */
void fn_1_218(int seNo, s16 pan)
{
    HuAudFXPanning(seNo, pan);
}

/* 22 insns; donated: m510dll m510.c */
void fn_1_248(Vec *pos, Vec *heading, float sndDist, float sndSpeed, float startDis, float frontSurDis, float backSurDis)
{
    HuAudFXListnerSetEX(pos, heading, sndDist, sndSpeed, startDis, frontSurDis, backSurDis);
}

/* 10 insns; donated: m510dll m510.c */
int fn_1_2A0(s16 streamId)
{
    return HuAudSStreamPlay(streamId);
}

/* 12 insns; donated: m510dll m510.c */
void fn_1_2C8(int streamNo, s32 speed)
{
    HuAudSStreamFadeOut(streamNo, speed);
}

/* 8 insns; donated: m510dll m510.c */
void fn_1_2F8(void)
{
    HuAudAllStop();
}

/* 10 insns; donated: m510dll m510.c */
int fn_1_318(s16 streamId)
{
    return HuAudBGMPlay(streamId);
}

/* 10 insns; donated: m510dll m510.c */
int fn_1_340(s16 streamId)
{
    return HuAudJinglePlay(streamId);
}

/* 12 insns; donated: m510dll m510.c */
int fn_1_368(s16 streamId, s16 chanNo)
{
    return HuAudSStreamChanPlay(streamId, chanNo);
}
#pragma dont_inline off

/* 91 insns */
void fn_1_398(M502_WORK *work, OMOBJMAN *objman, OMOBJ *obj)
{
    u16 i;

    memset(work, 0, sizeof(M502_WORK));
    work->unk000 = objman;
    work->unk004 = obj;
    work->unk5008 = 0;
    work->unk5014 = _CheckFlag(FLAG_INST_DECA);
    work->unk018 = -1;
    work->unk5018 = -1;
    work->unk501C = -1;
    work->unk5020 = -1;
    fn_1_1350(work);
    fn_1_15C0(&work->unk378);
    for (i = 0; i < 4; i++) {
        fn_1_1690(&work->unk3A4[i], i, work);
    }
    Hu3DLayerHookSet(12, fn_1_27AC);
    fn_1_735C(&work->unk3A4[0].unk008);
    fn_1_7290(&work->unk3A4[1].unk008, &work->unk3A4[0].unk008);
    fn_1_7290(&work->unk3A4[2].unk008, &work->unk3A4[0].unk008);
    fn_1_7290(&work->unk3A4[3].unk008, &work->unk3A4[0].unk008);
    fn_1_9468(&work->unk380, work);
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    work->unk500C = 18000;
    work->unk5010 = NULL;
    lbl_1_bss_5028 = 0;
    lbl_1_bss_502C = 0;
}

/* 54 insns */
void fn_1_504(M502_WORK *work)
{
    u16 i;

    fn_1_95B4(&work->unk380);
    for (i = 0; i < 4; i++) {
        fn_1_1740(&work->unk3A4[i]);
    }
    fn_1_1638(&work->unk378);
    fn_1_13A0(work);
    if (work->unk018 >= 0) {
        GameMesKill(work->unk018);
    }
    GameMesClose();
    if (!lbl_1_data_0->unk5014 && work->unk5010) {
        MgTimerKill(work->unk5010);
        work->unk5010 = NULL;
    }
    memset(work, 0, sizeof(M502_WORK));
    fn_1_2F8();
}

/* 639 insns */
int fn_1_5DC(M502_WORK *work)
{
    u16 i;
    M502_PLAYER *player;
    s32 flag;
    u16 j;
    HU3DMODELID modelId;
    s32 value;

    if (omSysExitReq && work->unk008 < 7 && !lbl_1_bss_5028) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        HuAudFadeOut(1000);
        if (work->unk008 == 1) {
            work->unk008 = 8;
            lbl_1_bss_5030 = 1;
        } else {
            lbl_1_bss_5028 = 1;
            lbl_1_bss_502C = 0;
        }
    }
    if (lbl_1_bss_5028) {
        if (++lbl_1_bss_502C >= 60 && !WipeCheckEnd()) {
            work->unk008 = 7;
        }
    }
    switch (work->unk008) {
        case 0:
            work->unk008 = 1;
        case 1:
            if (fn_1_9644(work)) {
                work->unk008 = 2;
            }
            break;
        case 2:
            if (omPauseChk() + omUPauseFlag == 0) {
                if (!lbl_1_data_0->unk5014) {
                    if (work->unk5010) {
                        if (MgTimerDoneCheck(work->unk5010)) {
                            fn_1_FD8(work);
                            work->unk008 = 9;
                        }
                    } else if (work->unk500C <= 1800) {
                        work->unk5010 = MgTimerCreate(0);
                        MgTimerParamSet(work->unk5010, 1800, 0, 0);
                        MgTimerModeOnSet(work->unk5010, 1);
                    }
                } else if (!work->unk5010) {
                    for (i = 0; i < 4; i++) {
                        player = &work->unk3A4[i];
                        MgTimerParamSet(player->unk1314, 0, 5400, 0);
                        MgTimerModeOnSet(player->unk1314, 2);
                    }
                    work->unk5010 = (MGTIMER *)-1;
                }
                if (work->unk500C != 0) {
                    work->unk500C--;
                }
            }
            break;
        case 3:
            if (work->unk018 < 0) {
                work->unk018 = GameMesMgFinishCreate();
            } else {
                if (work->unk5018 >= 0 && GameMesFXPlayCheck(work->unk018)) {
                    fn_1_2C8(work->unk5018, 100);
                    work->unk5018 = -1;
                }
                if (!GameMesStatGet(work->unk018)) {
                    work->unk018 = -1;
                    work->unk010 = 0;
                    work->unk008 = 4;
                }
            }
            break;
        case 4:
            if (work->unk010++ > 120) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                WipeColorSet(255, 255, 255);
                work->unk010 = 0;
                work->unk008 = 5;
            }
            break;
        case 5:
            if (!WipeCheckEnd()) {
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                for (i = 0; i < 4; i++) {
                    fn_1_8F04(&work->unk3A4[i].unk008);
                }
                for (i = 0; i < 4; i++) {
                    for (j = 0; j < 4; j++) {
                        modelId = work->unk3A4[i].unkFD4.unk03C[j];
                        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
                    }
                    fn_1_CAC8(&work->unk3A4[i].unk10CC);
                }
                work->unk008 = 6;
            }
            break;
        case 6:
            if (fn_1_A914(work)) {
                GWMgCoinBonusSet(work->unk5004, 10);
                work->unk008 = 7;
            }
            break;
        case 9:
            if (work->unk018 < 0) {
                work->unk018 = GameMesMgFinishCreate();
            } else {
                if (work->unk5018 >= 0 && GameMesFXPlayCheck(work->unk018)) {
                    fn_1_2C8(work->unk5018, 100);
                    work->unk5018 = -1;
                }
                if (!GameMesStatGet(work->unk018)) {
                    work->unk018 = -1;
                    flag = 0;
                    for (i = 0; i < 4; i++) {
                        if (work->unk3A4[i].unkF58.unk006 == 2) {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) {
                        fn_1_1018(work);
                        work->unk010 = 0;
                        work->unk008 = 4;
                    } else {
                        for (i = 0; i < 4; i++) {
                            work->unk3A4[i].unkF58.unk006 = 3;
                        }
                        work->unk008 = 10;
                    }
                }
            }
            break;
        case 10:
            if (work->unk018 < 0) {
                work->unk018 = GameMesMgDrawCreate();
                work->unk010 = 0;
            } else {
                if (work->unk5018 < 0) {
                    work->unk5018 = fn_1_340(123);
                }
                if (work->unk010 == 0) {
                    CharLoseVoicePlay(work->unk3A4[0].unkF58.unk014, work->unk3A4[1].unkF58.unk014, work->unk3A4[2].unkF58.unk014, work->unk3A4[3].unkF58.unk014);
                }
                if (++work->unk010 >= 210) {
                    work->unk018 = -1;
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
                    work->unk008 = 7;
                }
            }
            break;
        case 11:
            if (work->unk018 < 0) {
                work->unk018 = GameMesMgFinishCreate();
            } else {
                if (work->unk5018 >= 0 && GameMesFXPlayCheck(work->unk018)) {
                    fn_1_2C8(work->unk5018, 100);
                    work->unk5018 = -1;
                }
                if (!GameMesStatGet(work->unk018)) {
                    work->unk018 = -1;
                    work->unk010 = 0;
                    work->unk008 = 12;
                }
            }
            break;
        case 12:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
            work->unk010 = 0;
            work->unk008 = 7;
            for (i = 0; i < 4; i++) {
                player = &work->unk3A4[i];
                value = MgTimerValueGet(player->unk1314);
                if (player->unkF58.unk006 == 2) {
                    GWMgScoreSet(player->unkF58.unk010, value);
                } else {
                    GWMgScoreSet(player->unkF58.unk010, 0);
                }
            }
            break;
        case 7:
            if (!WipeCheckEnd()) {
                for (i = 0; i < 4; i++) {
                    fn_1_8F04(&work->unk3A4[i].unk008);
                }
                return 1;
            }
            break;
        case 8:
            if (lbl_1_bss_5030 && fn_1_9644(work)) {
                lbl_1_bss_5030 = 0;
            }
            if (!WipeCheckEnd()) {
                return 1;
            }
            break;
    }
    flag = 0;
    for (i = 0; i < 4; i++) {
        if (fn_1_17C4(&work->unk3A4[i])) {
            flag = 1;
            if (lbl_1_data_0->unk5014 && MgTimerModeGet(work->unk3A4[i].unk1314) != 2 && work->unk3A4[i].unk1314->stopF == 0) {
                work->unk3A4[i].unk1314->stopF = 1;
                work->unk3A4[i].unk1314->mode = 1;
            }
        }
    }
    if (!lbl_1_data_0->unk5014) {
        if (flag && work->unk008 == 2) {
            work->unk008 = 3;
            work->unk010 = 0;
            if (work->unk5010) {
                MgTimerModeOffSet(work->unk5010);
                MgTimerDispOff(work->unk5010);
            }
            fn_1_FD8(work);
            fn_1_1018(work);
        }
    } else {
        flag = 1;
        for (i = 0; i < 4; i++) {
            if (work->unk5010) {
                if (MgTimerModeGet(work->unk3A4[i].unk1314) != 0) {
                    flag = 0;
                }
            } else {
                flag = 0;
            }
        }
        if (flag && work->unk008 == 2) {
            fn_1_FD8(work);
            work->unk008 = 11;
            work->unk010 = 0;
        }
    }
    if (!lbl_1_data_0->unk5014 && work->unk5008 && work->unk008 <= 5) {
        if (work->unk501C < 0) {
            work->unk501C = fn_1_198(0x631);
        }
        fn_1_1104(work);
    }
    fn_1_9604(&work->unk380);
    return 0;
}

/* .data 0x3C onward is defined below the switch function so CodeWarrior emits
 * fn_1_5DC's jumptable at .data 0x8, where retail has it. */
/* 0x3C */ s32 lbl_1_data_3C[141] = { 0x003C0000, 0x003C0001, 0x003C0002, 0x003C0003, 0x003C0004, 0x003C0005, 0x003C0006, 0x003C0007, 0x003C0008, 0x003C0009, 0x003C000A, 0x003C000B, 0x003C000C, 0x003C000D, 0x003C000E, 0x003C000F, 0x003C0010, 0x003C0011, 0x003C0012, 0x003C0013, 0x003C0014, 0x003C0015, 0x003C0016, 0x003C0017, 0x003C0018, 0x003C0019, 0x003C001A, 0x003C001B, 0x003C001C, 0x003C001D, 0x003C001E, 0x003C001F, 0x003C0020, 0x003C0021, 0x003C0022, 0x003C0023, 0x003C0024, 0x003C0025, 0x003C0026, 0x003C0027, 0x003C0028, 0x003C0029, 0x003C002A, 0x003C002B, 0x003C002C, 0x003C002D, 0x003C002E, 0x003C002F, 0x003C0030, 0x003C0031, 0x003C0032, 0x003C0033, 0x003C0034, 0x003C0035, 0x003C0036, 0x003C0037, 0x003C0038, 0x003C0039, 0x003C003A, 0x003C003B, 0x003C003C, 0x003C003D, 0x003C003E, 0x003C003F, 0x003C0040, 0x003C0041, 0x003C0042, 0x003C0043, 0x003C0044, 0x003C0045, 0x003C0046, 0x003C0047, 0x003C0048, 0x003C0049, 0x003C004A, 0x003C004B, 0x003C004C, 0x003C004D, 0x003C004E, 0x003C004F, 0x003C0050, 0x003C0051, 0x003C0052, 0x003C0053, 0x003C0054, 0x003C0055, 0x003C0056, 0x003C0057, 0x003C0058, 0x003C0059, 0x003C005A, 0x003C005B, 0x003C005C, 0x003C005D, 0x003C005E, 0x003C005F, 0x003C0060, 0x003C0061, 0x003C0062, 0x003C0063, 0x003C0064, 0x003C0065, 0x003C0066, 0x003C0067, 0x003C0068, 0x003C0069, 0x003C006A, 0x003C006B, 0x003C006C, 0x003C006D, 0x003C006E, 0x003C006F, 0x003C0070, 0x003C0071, 0x003C0072, 0x003C0073, 0x003C0074, 0x003C0075, 0x003C0075, 0x003C0076, 0x003C0077, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0078, 0x003C0079, 0x003C007A, 0x003C007B, 0x003C007C, 0x003C007D, 0x003C007E, 0x003C007F, 0x003C0080, 0x003C0081, 0x003C0082, 0x003C0083, 0x003C0084 };
/* 0x270 */ char lbl_1_data_270[] = "model-sky";
/* 0x27A */ char lbl_1_data_27A[] = "model-tenzyou";
/* 0x288 */ char lbl_1_data_288[] = "model-dokan";
/* 0x294 */ char lbl_1_data_294[] = "model-kabe03";
/* 0x2A1 */ char lbl_1_data_2A1[] = "model-hasira";
/* 0x2AE */ char lbl_1_data_2AE[] = "model-kabe00";
/* 0x2BB */ char lbl_1_data_2BB[] = "model-kabe01";
/* 0x2C8 */ char lbl_1_data_2C8[] = "model-kabe02";
/* 0x2D5 */ char lbl_1_data_2D5[] = "model-kabe04";
/* 0x2E2 */ char lbl_1_data_2E2[] = "model-yuka00";
/* 0x2EF */ char lbl_1_data_2EF[] = "model-yuka01";
/* 0x2FC */ char lbl_1_data_2FC[] = "model-yuka02";
/* 0x309 */ char lbl_1_data_309[] = "layer1-b100";
/* 0x315 */ char lbl_1_data_315[] = "layer1-b101";
/* 0x321 */ char lbl_1_data_321[] = "layer1-b110";
/* 0x32D */ char lbl_1_data_32D[] = "layer1-b111";
/* 0x339 */ char lbl_1_data_339[] = "layer1-b120";
/* 0x345 */ char lbl_1_data_345[] = "layer1-b121";
/* 0x351 */ char lbl_1_data_351[] = "layer1-b130";
/* 0x35D */ char lbl_1_data_35D[] = "layer1-b131";
/* 0x369 */ char lbl_1_data_369[] = "layer1-b132";
/* 0x375 */ char lbl_1_data_375[] = "layer1-b133";
/* 0x381 */ char lbl_1_data_381[] = "layer1-b134";
/* 0x38D */ char lbl_1_data_38D[] = "layer1-b135";
/* 0x399 */ char lbl_1_data_399[] = "layer1-b140";
/* 0x3A5 */ char lbl_1_data_3A5[] = "layer1-b141";
/* 0x3B1 */ char lbl_1_data_3B1[] = "layer1-b142";
/* 0x3BD */ char lbl_1_data_3BD[] = "layer1-b143";
/* 0x3C9 */ char lbl_1_data_3C9[] = "layer1-b144";
/* 0x3D5 */ char lbl_1_data_3D5[] = "layer1-b145";
/* 0x3E1 */ char lbl_1_data_3E1[] = "layer2-b200";
/* 0x3ED */ char lbl_1_data_3ED[] = "layer2-b201";
/* 0x3F9 */ char lbl_1_data_3F9[] = "layer2-b210";
/* 0x405 */ char lbl_1_data_405[] = "layer2-b211";
/* 0x411 */ char lbl_1_data_411[] = "layer2-b220";
/* 0x41D */ char lbl_1_data_41D[] = "layer2-b221";
/* 0x429 */ char lbl_1_data_429[] = "layer2-b230";
/* 0x435 */ char lbl_1_data_435[] = "layer2-b231";
/* 0x441 */ char lbl_1_data_441[] = "layer2-b232";
/* 0x44D */ char lbl_1_data_44D[] = "layer2-b233";
/* 0x459 */ char lbl_1_data_459[] = "layer2-b234";
/* 0x465 */ char lbl_1_data_465[] = "layer2-b235";
/* 0x471 */ char lbl_1_data_471[] = "layer2-b240";
/* 0x47D */ char lbl_1_data_47D[] = "layer2-b241";
/* 0x489 */ char lbl_1_data_489[] = "layer2-b242";
/* 0x495 */ char lbl_1_data_495[] = "layer2-b243";
/* 0x4A1 */ char lbl_1_data_4A1[] = "layer2-b244";
/* 0x4AD */ char lbl_1_data_4AD[] = "layer2-b245";
/* 0x4B9 */ char lbl_1_data_4B9[] = "layer3-b300";
/* 0x4C5 */ char lbl_1_data_4C5[] = "layer3-b301";
/* 0x4D1 */ char lbl_1_data_4D1[] = "layer3-b310";
/* 0x4DD */ char lbl_1_data_4DD[] = "layer3-b311";
/* 0x4E9 */ char lbl_1_data_4E9[] = "layer3-b320";
/* 0x4F5 */ char lbl_1_data_4F5[] = "layer3-b321";
/* 0x501 */ char lbl_1_data_501[] = "layer3-b330";
/* 0x50D */ char lbl_1_data_50D[] = "layer3-b331";
/* 0x519 */ char lbl_1_data_519[] = "layer3-b332";
/* 0x525 */ char lbl_1_data_525[] = "layer3-b333";
/* 0x531 */ char lbl_1_data_531[] = "layer3-b334";
/* 0x53D */ char lbl_1_data_53D[] = "layer3-b335";
/* 0x549 */ char lbl_1_data_549[] = "layer3-b340";
/* 0x555 */ char lbl_1_data_555[] = "layer3-b341";
/* 0x561 */ char lbl_1_data_561[] = "layer3-b342";
/* 0x56D */ char lbl_1_data_56D[] = "layer3-b343";
/* 0x579 */ char lbl_1_data_579[] = "layer3-b344";
/* 0x585 */ char lbl_1_data_585[] = "layer3-b345";
/* 0x591 */ char lbl_1_data_591[] = "m502te00-00";
/* 0x59D */ char lbl_1_data_59D[] = "m502te00-01";
/* 0x5A9 */ char lbl_1_data_5A9[] = "m502te00-02";
/* 0x5B5 */ char lbl_1_data_5B5[] = "m502te00-03";
/* 0x5C1 */ char lbl_1_data_5C1[] = "m502te00-04";
/* 0x5CD */ char lbl_1_data_5CD[] = "m502te00-05";
/* 0x5D9 */ char lbl_1_data_5D9[] = "m502te00-06";
/* 0x5E5 */ char lbl_1_data_5E5[] = "m502te00-07";
/* 0x5F1 */ char lbl_1_data_5F1[] = "m502te10-00";
/* 0x5FD */ char lbl_1_data_5FD[] = "m502te10-01";
/* 0x609 */ char lbl_1_data_609[] = "m502te10-02";
/* 0x615 */ char lbl_1_data_615[] = "m502te10-03";
/* 0x621 */ char lbl_1_data_621[] = "m502te10-04";
/* 0x62D */ char lbl_1_data_62D[] = "m502te10-05";
/* 0x639 */ char lbl_1_data_639[] = "m502te10-06";
/* 0x645 */ char lbl_1_data_645[] = "m502te10-07";
/* 0x651 */ char lbl_1_data_651[] = "m502te20-00";
/* 0x65D */ char lbl_1_data_65D[] = "m502te20-01";
/* 0x669 */ char lbl_1_data_669[] = "m502te20-02";
/* 0x675 */ char lbl_1_data_675[] = "m502te20-03";
/* 0x681 */ char lbl_1_data_681[] = "m502te20-04";
/* 0x68D */ char lbl_1_data_68D[] = "m502te20-05";
/* 0x699 */ char lbl_1_data_699[] = "m502te20-06";
/* 0x6A5 */ char lbl_1_data_6A5[] = "m502te20-07";
/* 0x6B1 */ char lbl_1_data_6B1[] = "m502ie00-00";
/* 0x6BD */ char lbl_1_data_6BD[] = "m502ie00-01";
/* 0x6C9 */ char lbl_1_data_6C9[] = "m502ie00-02";
/* 0x6D5 */ char lbl_1_data_6D5[] = "m502ie00-03";
/* 0x6E1 */ char lbl_1_data_6E1[] = "m502ie00-04";
/* 0x6ED */ char lbl_1_data_6ED[] = "m502ie00-05";
/* 0x6F9 */ char lbl_1_data_6F9[] = "m502ie00-06";
/* 0x705 */ char lbl_1_data_705[] = "m502ie00-07";
/* 0x711 */ char lbl_1_data_711[] = "m502ie10-00";
/* 0x71D */ char lbl_1_data_71D[] = "m502ie10-01";
/* 0x729 */ char lbl_1_data_729[] = "m502ie10-02";
/* 0x735 */ char lbl_1_data_735[] = "m502ie10-03";
/* 0x741 */ char lbl_1_data_741[] = "m502ie10-04";
/* 0x74D */ char lbl_1_data_74D[] = "m502ie10-05";
/* 0x759 */ char lbl_1_data_759[] = "m502ie10-06";
/* 0x765 */ char lbl_1_data_765[] = "m502ie10-07";
/* 0x771 */ char lbl_1_data_771[] = "m502ie20-00";
/* 0x77D */ char lbl_1_data_77D[] = "m502ie20-01";
/* 0x789 */ char lbl_1_data_789[] = "m502ie20-02";
/* 0x795 */ char lbl_1_data_795[] = "m502ie20-03";
/* 0x7A1 */ char lbl_1_data_7A1[] = "m502ie20-04";
/* 0x7AD */ char lbl_1_data_7AD[] = "m502ie20-05";
/* 0x7B9 */ char lbl_1_data_7B9[] = "m502ie20-06";
/* 0x7C5 */ char lbl_1_data_7C5[] = "m502ie20-07";
/* 0x7D1 */ char lbl_1_data_7D1[] = "m502we00_2-cyl3_1";
/* 0x7E3 */ char lbl_1_data_7E3[] = "m502we15-cyl2_1_2_2_2";
/* 0x7F9 */ char lbl_1_data_7F9[] = "m502we02_3-cube1";
/* 0x80A */ char lbl_1_data_80A[] = "m502dbg-obj5";
/* 0x817 */ char lbl_1_data_817[] = "m502bg-obj6";
/* 0x823 */ char lbl_1_data_823[] = "m502ke00-poly1_1";
/* 0x834 */ char lbl_1_data_834[] = "layer1-b451";
/* 0x840 */ char lbl_1_data_840[] = "layer1-b452";
/* 0x84C */ char lbl_1_data_84C[] = "layer1-b453";
/* 0x858 */ char lbl_1_data_858[] = "layer1-b454";
/* 0x864 */ char lbl_1_data_864[] = "layer1-b455";
/* 0x870 */ char lbl_1_data_870[] = "m502we06-m502we06";
/* 0x882 */ char lbl_1_data_882[] = "m502we07-m502we07";
/* 0x894 */ char lbl_1_data_894[] = "m502we08-m502we08";
/* 0x8A6 */ char lbl_1_data_8A6[] = "m502we12-m502we06";
/* 0x8B8 */ void *lbl_1_data_8B8[162] = { &lbl_1_data_270, &lbl_1_data_27A, &lbl_1_data_288, &lbl_1_data_294, &lbl_1_data_2A1, &lbl_1_data_2AE, &lbl_1_data_2BB, &lbl_1_data_2C8, &lbl_1_data_2D5, &lbl_1_data_2E2, &lbl_1_data_2EF, &lbl_1_data_2FC, &lbl_1_data_309, &lbl_1_data_315, &lbl_1_data_321, &lbl_1_data_32D, &lbl_1_data_339, &lbl_1_data_345, &lbl_1_data_351, &lbl_1_data_35D, &lbl_1_data_369, &lbl_1_data_375, &lbl_1_data_381, &lbl_1_data_38D, &lbl_1_data_399, &lbl_1_data_3A5, &lbl_1_data_3B1, &lbl_1_data_3BD, &lbl_1_data_3C9, &lbl_1_data_3D5, &lbl_1_data_3E1, &lbl_1_data_3ED, &lbl_1_data_3F9, &lbl_1_data_405, &lbl_1_data_411, &lbl_1_data_41D, &lbl_1_data_429, &lbl_1_data_435, &lbl_1_data_441, &lbl_1_data_44D, &lbl_1_data_459, &lbl_1_data_465, &lbl_1_data_471, &lbl_1_data_47D, &lbl_1_data_489, &lbl_1_data_495, &lbl_1_data_4A1, &lbl_1_data_4AD, &lbl_1_data_4B9, &lbl_1_data_4C5, &lbl_1_data_4D1, &lbl_1_data_4DD, &lbl_1_data_4E9, &lbl_1_data_4F5, &lbl_1_data_501, &lbl_1_data_50D, &lbl_1_data_519, &lbl_1_data_525, &lbl_1_data_531, &lbl_1_data_53D, &lbl_1_data_549, &lbl_1_data_555, &lbl_1_data_561, &lbl_1_data_56D, &lbl_1_data_579, &lbl_1_data_585, &lbl_1_data_591, &lbl_1_data_59D, &lbl_1_data_5A9, &lbl_1_data_5B5, &lbl_1_data_5C1, &lbl_1_data_5CD, &lbl_1_data_5D9, &lbl_1_data_5E5, &lbl_1_data_5F1, &lbl_1_data_5FD, &lbl_1_data_609, &lbl_1_data_615, &lbl_1_data_621, &lbl_1_data_62D, &lbl_1_data_639, &lbl_1_data_645, &lbl_1_data_651, &lbl_1_data_65D, &lbl_1_data_669, &lbl_1_data_675, &lbl_1_data_681, &lbl_1_data_68D, &lbl_1_data_699, &lbl_1_data_6A5, &lbl_1_data_6B1, &lbl_1_data_6BD, &lbl_1_data_6C9, &lbl_1_data_6D5, &lbl_1_data_6E1, &lbl_1_data_6ED, &lbl_1_data_6F9, &lbl_1_data_705, &lbl_1_data_711, &lbl_1_data_71D, &lbl_1_data_729, &lbl_1_data_735, &lbl_1_data_741, &lbl_1_data_74D, &lbl_1_data_759, &lbl_1_data_765, &lbl_1_data_771, &lbl_1_data_77D, &lbl_1_data_789, &lbl_1_data_795, &lbl_1_data_7A1, &lbl_1_data_7AD, &lbl_1_data_7B9, &lbl_1_data_7C5, &lbl_1_data_7D1, &lbl_1_data_7E3, &lbl_1_data_7D1, &lbl_1_data_7F9, &lbl_1_data_7F9, &lbl_1_data_80A, &lbl_1_data_817, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_823, &lbl_1_data_834, &lbl_1_data_840, &lbl_1_data_84C, &lbl_1_data_858, &lbl_1_data_864, &lbl_1_data_870, &lbl_1_data_882, &lbl_1_data_894, &lbl_1_data_8A6, &lbl_1_data_8A6, &lbl_1_data_8A6, &lbl_1_data_8A6, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000, (void *)0x00000000 };
/* 0xB40 */ HuVecF lbl_1_data_B40 = { 0.0f, 4000.0f, 500.0f };
/* 0xB4C */ HuVecF lbl_1_data_B4C = { 0.0f, -1.0f, -1.0f };
/* 0xB58 */ GXColor lbl_1_data_B58 = { 255, 255, 255, 255 };

/* 16 insns */
void fn_1_FD8(M502_WORK *work)
{
    u16 i;

    for (i = 0; i < 4; i++) {
        work->unk3A4[i].unkF58.unk020 = 0;
    }
}

/* 59 insns */
void fn_1_1018(M502_WORK *work)
{
    s16 list[4] = { 0, 0, 0, 0 };
    s16 num;
    u16 i;

    num = 0;
    for (i = 0; i < 4; i++) {
        if (work->unk3A4[i].unkF58.unk006 == 2) {
            list[num++] = i;
        }
    }
    if (num > 1) {
        work->unk5004 = list[rand8() % num];
    } else {
        work->unk5004 = list[0];
    }
}

/* 147 insns */
void fn_1_1104(M502_WORK *work)
{
    u16 level;
    float speed;
    u16 i;
    M502_CHAR *chr;

    level = work->unk014 < 30 ? 0 : (work->unk014 < 150 ? 1 : 2);
    speed = level == 0 ? 0.0f : (level == 1 ? 4.0f : 8.0f);
    for (i = 0; i < 4; i++) {
        chr = &work->unk3A4[i].unkF58;
        if (chr->unk006 == 2) {
            if (level == 1 && work->unk014 % 6 == 0) {
                omVibrate(i, 2, 6, 6);
            }
            if (level == 2 && work->unk014 % 6 == 0) {
                omVibrate(i, 4, 4, 2);
            }
            if ((work->unk014 / 2) & 1) {
                chr->unk000->unk1048.unk01C.y += speed;
                chr->unk000->unk1048.unk010.y += speed;
                chr->unk000->unk1048.unk034.y += speed;
                chr->unk000->unk1048.unk028.y += speed;
            } else {
                chr->unk000->unk1048.unk01C.y -= speed;
                chr->unk000->unk1048.unk010.y -= speed;
                chr->unk000->unk1048.unk034.y -= speed;
                chr->unk000->unk1048.unk028.y -= speed;
            }
        }
    }
    work->unk014++;
}

/* 20 insns */
void fn_1_1350(M502_WORK *work)
{
    M502_WORKMODEL *model;

    model = &work->unk01C;
    memset(model, 0, sizeof(M502_WORKMODEL));
    fn_1_13F0(model);
    fn_1_14C0(model);
}

/* 20 insns */
void fn_1_13A0(M502_WORK *work)
{
    M502_WORKMODEL *model;

    model = &work->unk01C;
    fn_1_147C(model);
    fn_1_1564(model);
    memset(model, 0, sizeof(M502_WORKMODEL));
}

/* 35 insns */
void fn_1_13F0(M502_WORKMODEL *model)
{
    model->unk350 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    model->unk354 = HuSprAnimRead(HuDataSelHeapReadNum(0x21000A, HU_MEMNUM_OVL, HEAP_MODEL));
    model->unk358 = HuSprAnimRead(HuDataSelHeapReadNum(0x21000C, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 17 insns */
void fn_1_147C(M502_WORKMODEL *model)
{
    if (model->unk350) {
        HuMemDirectFree(model->unk350);
        model->unk350 = NULL;
    }
}

/* 41 insns */
void fn_1_14C0(M502_WORKMODEL *model)
{
    s32 i;
    HU3DMODELID modelId;

    for (i = 0; i < 141; i++) {
        model->unk000[i] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_3C[i], HU_MEMNUM_OVL, HEAP_MODEL));
        model->unk11C[i] = lbl_1_data_8B8[i];
        Hu3DModelAttrSet(model->unk000[i], HU3D_ATTR_DISPOFF);
    }
}

/* 23 insns */
void fn_1_1564(M502_WORKMODEL *model)
{
    s32 i;

    for (i = 0; i < 141; i++) {
        Hu3DModelKill(model->unk000[i]);
        model->unk000[i] = 0;
    }
}

/* 30 insns; donated: m510dll light.c */
void fn_1_15C0(M502_LIGHT *light, void *work)
{
    memset(light, 0, sizeof(M502_LIGHT));
    light->unk000 = work;
    light->unk004 = Hu3DGLightCreateV(&lbl_1_data_B40, &lbl_1_data_B4C, &lbl_1_data_B58);
    Hu3DGLightStaticSet(light->unk004, TRUE);
    Hu3DGLightInfinitytSet(light->unk004);
}

/* 21 insns; donated: m510dll light.c */
void fn_1_1638(M502_LIGHT *light)
{
    if (light->unk004 != 0) {
        Hu3DGLightKill(light->unk004);
        light->unk004 = 0;
    }
    memset(light, 0, sizeof(M502_LIGHT));
}

/* 1 insns */
void fn_1_168C(void)
{
}

/* 44 insns */
void fn_1_1690(M502_PLAYER *player, s32 playerNo, M502_WORK *work)
{
    M502_WORK *work2;

    work2 = work;
    memset(player, 0, sizeof(M502_PLAYER));
    player->unk000 = work;
    player->unk004 = playerNo;
    fn_1_38E0(&player->unkF58, playerNo, player);
    fn_1_21B8(&player->unkFD4, playerNo, player);
    fn_1_6664(&player->unk008, playerNo, player);
    fn_1_1830(&player->unk1048, playerNo, player);
    fn_1_C468(&player->unk10CC, player);
    player->unk1314 = NULL;
}

/* 33 insns */
void fn_1_1740(M502_PLAYER *player)
{
    if (player->unk000->unk5014 && player->unk1314) {
        MgTimerKill(player->unk1314);
    }
    fn_1_C4F0(&player->unk10CC);
    fn_1_1A60(&player->unk1048);
    fn_1_2704(&player->unkFD4);
    fn_1_3B88(&player->unkF58);
    fn_1_6778(&player->unk008);
    memset(player, 0, sizeof(M502_PLAYER));
}

/* 27 insns */
int fn_1_17C4(M502_PLAYER *player)
{
    int ret;

    fn_1_6808(&player->unk008);
    ret = 0;
    if (fn_1_3BF4(&player->unkF58)) {
        ret = 1;
    }
    fn_1_C554(&player->unk10CC);
    fn_1_27A8(&player->unkFD4);
    fn_1_1A90(&player->unk1048);
    return ret;
}

