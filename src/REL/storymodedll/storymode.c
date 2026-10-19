/*
 * storymodedll storymode.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/storymodedll/asm/REL/storymodedll/storymode.s.
 */

#include "REL/storymodeDll.h"

#ifndef __MWERKS__
/* retail calls the audio API unprototyped here (no extsh on HuAudBGMPlay's / HuAudFXPanning's
   s16 argument); the host keeps the prototypes */
#include "game/audio.h"
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/object.h"
#include "game/process.h"
#include "game/thpmain.h"
#include "game/saveload.h"
#include "game/gamemes.h"
#include "game/board/main.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
/* 0x10 lbl_1_rodata_10 (0xC): 0x00000000 0x00000000 0x44FA0000 -- an aggregate initialiser, write it as a local */
/* 0x1C lbl_1_rodata_1C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x28 lbl_1_rodata_28 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x34 lbl_1_rodata_34 (0xC): 0x00000000 0x00000000 0x44FA0000 -- an aggregate initialiser, write it as a local */
/* 0x40 lbl_1_rodata_40 (0xC): 0x00000000 0x45FA0000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x4C lbl_1_rodata_4C (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x58 lbl_1_rodata_58 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x59 lbl_1_rodata_59 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x5C lbl_1_rodata_5C (0xC): 0x00000000 0x00000000 0x453B8000 -- an aggregate initialiser, write it as a local */
/* 0x68 lbl_1_rodata_68 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
/* 0x74 lbl_1_rodata_74 (0x1): 0x80 -- an aggregate initialiser, write it as a local */
/* 0x75 lbl_1_rodata_75 (0x3): 0x80, 0x80, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_78 = 0.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 640.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 480.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 1.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 20.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 30000.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 1.2f; /* 0x90 */
static const float lbl_1_rodata_94 = 576.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 9.0f; /* 0x98 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x54 gap_05_00000054_bss (0x4): alignment gap */
/* 0x50 */ OMOBJMAN *lbl_1_bss_50;
/* 0x4C */ s32 lbl_1_bss_4C;
/* 0x48 */ s32 lbl_1_bss_48;
/* 0x44 */ OMOBJ *lbl_1_bss_44;
/* 0x40 */ s16 lbl_1_bss_40[2];
/* 0x3E */ s16 lbl_1_bss_3E;
/* 0x3C */ s16 lbl_1_bss_3C;
/* 0x14 */ s32 lbl_1_bss_14[10];
/* 0x10 */ s32 lbl_1_bss_10;
/* 0xC */ s32 lbl_1_bss_C;
/* 0xA gap_05_0000000A_bss (0x2): alignment gap */
/* 0x8 */ s16 lbl_1_bss_8;
/* 0x6 */ s16 lbl_1_bss_6;
/* 0x4 */ s16 lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;

/* --- functions (reference order), .data placed before its first user --- */
/* story board number (GwCommon.storyBoardNo[]) -> its story-board overlay */
#define STORY_BOARD_DLL(boardNo) ((boardNo) == 0 ? DLL_w01sdll : \
    (boardNo) == 1 ? DLL_w02sdll : \
    (boardNo) == 2 ? DLL_w03sdll : \
    (boardNo) == 3 ? DLL_w04sdll : \
    (boardNo) == 4 ? DLL_w05sdll : \
    (boardNo) == 5 ? DLL_w06sdll : DLL_w07sdll)

/* 63 insns */
/* background loader process: fn_1_19C(dir) starts an async read of a data directory */
void fn_1_A0(void)
{
    OSTick tick;

    lbl_1_bss_6 = 0;
    while(1) {
        switch(lbl_1_bss_6) {
            case 0:
                break;
            case 1:
                tick = OSGetTick();
                lbl_1_bss_4 = HuDataDirReadAsync(lbl_1_bss_0);
                while(HuDataGetAsyncStat(lbl_1_bss_4) == 0) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick() - tick));
                OSReport("Finished!\n");
                lbl_1_bss_6 = 2;
                break;
            case 2:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}

/* 8 insns */
void fn_1_19C(s32 dataNum)
{
    lbl_1_bss_6 = 1;
    lbl_1_bss_0 = dataNum;
}

/* 0x1C */ u32 lbl_1_data_1C[7] = { DATA_w01s, DATA_w02s, DATA_w03s, DATA_w04s, DATA_w05s, DATA_w06s, DATA_w07s };

/* 438 insns */
void ObjectSetup(void)
{
    HuVecF camPos = { 0.0f, 0.0f, 2000.0f };
    HuVecF camUp = { 0.0f, 1.0f, 0.0f };
    HuVecF camTarget = { 0.0f, 0.0f, 0.0f };
    HuVecF camPos2 = { 0.0f, 0.0f, 2000.0f };
    HuVecF lightPos = { 0.0f, 8000.0f, 500.0f };
    HuVecF lightDir = { 0.0f, -1.0f, 0.0f };
    GXColor lightColor = { 255, 255, 255, 255 };
    HuVecF lightPos2 = { 0.0f, 0.0f, 3000.0f };
    HuVecF lightDir2 = { 0.0f, 0.0f, -1.0f };
    GXColor lightColor2 = { 128, 128, 128, 255 };
    OMOVL ovl;
    OMOBJ *obj;
    s32 i;

    for(i = 0; i < 7; i++) {
        HuDataDirClose(lbl_1_data_1C[i]);
    }
    lbl_1_bss_50 = omInitObjMan(200, 0x2000);
    if(GwCommon.storyNo != -2 && GwCommon.storyNo < 5) {
        HuPrcVSleep();
        HuPrcChildCreate(fn_1_A0, 100, 0x3000, 0, lbl_1_bss_50);
    }
    omSystemKeyCheckSetup(lbl_1_bss_50);
    omSysPauseEnable(FALSE);
    if(mgPauseExitF) {
        obj = omAddObjEx(lbl_1_bss_50, 0x7FDC, 0, 0, -1, GameMesExitCheck);
        omSetStatBit(obj, OM_STAT_NOPAUSE | OM_STAT_SPRPAUSE);
    }
    if(_CheckFlag(FLAG_BOARD_SAVEINIT)) {
        if(GwCommon.storyNo < 5) {
            omOvlHisChg(0, DLL_storyresultdll, 0, 0);
            ovl = STORY_BOARD_DLL(GwCommon.storyBoardNo[GwCommon.storyNo]);
        }
        omOvlCallEx(ovl, 1, 0, 0);
    } else {
        Hu3DCameraCreate(1);
        Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f);
        Hu3DCameraPosSetV(1, &camPos, &camUp, &camTarget);
        Hu3DCameraCreate(2);
        Hu3DCameraViewportSet(2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(2, 20.0f, 20.0f, 30000.0f, 1.2f);
        Hu3DCameraPosSetV(2, &camPos2, &camUp, &camTarget);
        Hu3DCameraCreate(4);
        Hu3DCameraViewportSet(4, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraPerspectiveSet(4, 20.0f, 20.0f, 30000.0f, 1.2f);
        Hu3DCameraPosSetV(4, &camPos2, &camUp, &camTarget);
        lbl_1_bss_40[0] = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
        Hu3DGLightStaticSet(lbl_1_bss_40[0], TRUE);
        Hu3DGLightInfinitytSet(lbl_1_bss_40[0]);
        lbl_1_bss_40[1] = Hu3DGLightCreateV(&lightPos2, &lightDir2, &lightColor2);
        Hu3DGLightStaticSet(lbl_1_bss_40[1], TRUE);
        Hu3DGLightInfinitytSet(lbl_1_bss_40[1]);
        lbl_1_bss_44 = omAddObjEx(lbl_1_bss_50, 0, 108, 0, -1, fn_1_894);
        lbl_1_bss_44->work[0] = 0;
    }
}

/* 265 insns */
void fn_1_894(OMOBJ *obj)
{
    s32 mode;
    s32 boardNo;

    lbl_1_bss_48 = 0;
    if(GwCommon.storyNo == -2) {
        mode = 0;
        lbl_1_bss_48 = -1;
    } else if(GwCommon.storyNo == -3) {
        mode = 100;
    } else if(GwCommon.storyNo == 5) {
        mode = 300;
        lbl_1_bss_48 = -2;
    } else if(GwCommon.storyNo < 6) {
        mode = 200;
    } else if(GwPlayer[0].mgCoinBonus != 0) {
        mode = 400;
        lbl_1_bss_48 = 1;
        if(GwCommon.storyPlayNum[GwPlayerConf[0].charNo] < 999) {
            GwCommon.storyPlayNum[GwPlayerConf[0].charNo]++;
        }
    } else {
        mode = 300;
        lbl_1_bss_48 = -2;
    }
    if(mode != 300) {
        boardNo = (GwCommon.storyNo < -1) ? GwCommon.storyBoardNo[0] : GwCommon.storyBoardNo[GwCommon.storyNo];
    } else {
        boardNo = 7;
    }
    lbl_1_bss_3E = Hu3DModelCreateData(DATA_storymode + (mode == 0 ? 91 : 0));
    Hu3DModelCameraSet(lbl_1_bss_3E, 1);
    Hu3DModelPosSet(lbl_1_bss_3E, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_3E, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrSet(lbl_1_bss_3E, 0x40000001);
    Hu3DModelLayerSet(lbl_1_bss_3E, 1);
    if(mode == 100 || mode == 200 || mode == 300) {
        lbl_1_bss_3C = Hu3DModelCreateData(DATA_storymode + boardNo + 1);
        Hu3DModelCameraSet(lbl_1_bss_3C, 1);
        Hu3DModelPosSet(lbl_1_bss_3C, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_3C, 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_3C, 1);
        if(mode == 100 || mode == 200) {
            Hu3DModelAttrSet(lbl_1_bss_3C, 1);
            Hu3DModelScaleSet(lbl_1_bss_3C, 0.0f, 0.0f, 0.0f);
        }
    }
    fn_1_13E8();
    fn_1_1230();
    HuDataDirClose(DATA_storymode);
    if(mode == 0) {
        WipeColorSet(0, 0, 0);
    } else {
        WipeColorSet(255, 255, 255);
    }
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 120);
    obj->objFunc = fn_1_CB8;
}

/* 118 insns */
void fn_1_CB8(OMOBJ *obj)
{
    s32 time;
    s32 result;

    if(omSysExitReq) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        obj->objFunc = fn_1_E90;
        lbl_1_bss_4C = -1;
    }
    switch((s32)obj->work[0]) {
        case 0:
            if(lbl_1_bss_10 == -1) {
                lbl_1_bss_10 = HuAudBGMPlay(lbl_1_bss_C);
            }
            if(!WipeCheckEnd()) {
                obj->work[0]++;
            }
            break;
        case 1:
            result = fn_1_2448();
            if(result != 0) {
                obj->work[0]++;
                lbl_1_bss_4C = (lbl_1_bss_48 > 0) ? -1 : result;
            }
            break;
        case 2:
            if(lbl_1_bss_48 == -1) {
                WipeColorSet(0, 0, 0);
                time = 1;
            } else {
                HuAudSStreamFadeOut(lbl_1_bss_10, 1000);
                WipeColorSet(255, 255, 255);
                if(lbl_1_bss_48 == 1) {
                    time = 180;
                    HuAudFXPlay(0x583);
                } else {
                    time = 120;
                }
            }
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, time);
            obj->objFunc = fn_1_E90;
            break;
    }
}

/* 232 insns */
void fn_1_E90(OMOBJ *obj)
{
    s32 stage;
    OMOVL ovl;

    if(WipeCheckEnd()) {
        return;
    }
    HuAudAllStop();
    Hu3DModelAllKill();
    Hu3DLightAllKill();
    if(lbl_1_bss_48 == -1) {
        omOvlReturnEx(0, 1);
        GwCommon.storyNo = -3;
        return;
    }
    if(lbl_1_bss_48 == -2) {
        HuTHPClose();
        while(HuTHPProcCheck()) {
            HuPrcVSleep();
        }
    }
    if(lbl_1_bss_4C == -1) {
        if(lbl_1_bss_48 == 1) {
            omOvlGotoEx(DLL_staffdll, 1, 0, 0);
            return;
        }
        if(GwCommon.storyNo < 5) {
            SLSaveStoryExec();
        }
        if(GwCommon.storyNo == 6) {
            GwCommon.storyNo = 5;
        }
        omOvlReturnEx(1, 1);
        return;
    }
    stage = (GwCommon.storyNo < -1) ? 0 : GwCommon.storyNo;
    if(stage < 5) {
        MBPartySaveInit(GwCommon.storyBoardNo[stage]);
        MBStorySaveInit(GwSystem.mgPack, 0);
        omOvlHisChg(0, DLL_storyresultdll, 0, 0);
        ovl = STORY_BOARD_DLL(GwCommon.storyBoardNo[stage]);
        if(GwCommon.storyNo != -2 && GwCommon.storyNo < 5) {
            while(lbl_1_bss_6 != 2) {
                HuPrcVSleep();
            }
        }
    } else {
        omOvlHisChg(0, DLL_storymodedll, 0, 0);
        if(stage == 5) {
            GwSystem.subGameNo = -1;
        }
        ovl = DLL_m562dll;
        GWMgUnlockSet(562);
    }
    omOvlCallEx(ovl, 1, 0, 0);
    if(GwCommon.storyNo < -1) {
        GwCommon.storyNo = 0;
    } else if(GwCommon.storyNo == 5) {
        GwCommon.storyNo = 6;
    }
}

/* 20 insns */
void fn_1_1230(void)
{
    s32 i;

    for(i = 0; i < 10; i++) {
        lbl_1_bss_14[i] = 0;
    }
    lbl_1_bss_10 = -1;
}

/* 90 insns */
/* play seNo panned to model mdlId's screen position (bit 15 set: re-pan the last 0x580 voice);
   returns the voice, -1 when off screen */
s16 fn_1_1280(s16 seNo, s16 mdlId, s16 cameraBit)
{
    HuVecF pos;
    HuVecF pos2D;
    s32 pan;
    s16 voice;

    pos = Hu3DData[mdlId].pos;
    Hu3D3Dto2D(&pos, cameraBit, &pos2D);
    if(pos2D.x < 0.0f || pos2D.x > 576.0f) {
        return -1;
    }
    if(pos2D.y < 0.0f || pos2D.y > 480.0f) {
        return -1;
    }
    pan = (s32)(pos2D.x / 9.0f) + 32;
    if(!(seNo & 0x8000)) {
        voice = HuAudFXPlay(seNo & 0x7FF);
        if(seNo == 0x580) {
            lbl_1_bss_8 = voice;
        }
    } else {
        voice = lbl_1_bss_8;
    }
    HuAudFXPanning(voice, pan);
    return voice;
}
