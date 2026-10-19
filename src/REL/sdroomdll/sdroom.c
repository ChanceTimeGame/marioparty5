/*
 * sdroomdll sdroom.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/sdroom.s.
 */

#include "REL/sdroomdll.h"

#ifndef __MWERKS__
#include "game/audio.h"
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/init.h"
#include "game/saveload.h"
#include "game/armem.h"
#include "game/charman.h"
#include "math.h"
#include "humath.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 5.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 20.0f; /* 0x14 */
static const float lbl_1_rodata_18 = 15000.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 1.2f; /* 0x1C */
static const float lbl_1_rodata_20 = 0.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 640.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 480.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 1.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 40.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 30.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 1000.0f; /* 0x38 */
static const float lbl_1_rodata_3C = -1.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 100.0f; /* 0x40 */
/* 0x44 lbl_1_rodata_44 (0xC): 0x00000000 0x43430000 0xC4906000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_50 = 500.0; /* 0x50 */
static const double lbl_1_rodata_58 = 3.141592653589793; /* 0x58 */
static const double lbl_1_rodata_60 = 180.0; /* 0x60 */
static const float lbl_1_rodata_68 = 360.0f; /* 0x68 */
/* 0x70 lbl_1_rodata_70 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_78 = 288.0f; /* 0x78 */
static const double lbl_1_rodata_80 = 64.0; /* 0x80 */
static const double lbl_1_rodata_88 = 120.0; /* 0x88 */
static const double lbl_1_rodata_90 = 1.0; /* 0x90 */
static const double lbl_1_rodata_98 = 90.0; /* 0x98 */
static const double lbl_1_rodata_A0 = 10.0; /* 0xA0 */
static const float lbl_1_rodata_A8 = 180.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = -60.0f; /* 0xAC */
static const float lbl_1_rodata_B0 = 60.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 120.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 195.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = -1155.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 1.8f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 16.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = -10000.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 322.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 0.1f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 50.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 0.05f; /* 0xD8 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x10 */ GWCOMMON lbl_1_bss_10;
/* 0x8 */ s32 lbl_1_bss_8[2];
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x2 gap_05_00000002_bss (0x2): alignment gap */
/* 0x0 */ s16 lbl_1_bss_0;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ OMCAMERAVIEW lbl_1_data_0 = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 7000.0f };
/* 0x1C */ OMCAMERAVIEW lbl_1_data_1C = { { 0.0f, 165.0f, -891.0f }, { 0.0f, 0.0f, 0.0f }, 3267.0f };
/* 0x38 */ OMCAMERAVIEW lbl_1_data_38 = { { 0.0f, 215.0f, -896.0f }, { -3.8f, 0.0f, 0.0f }, 642.0f };
/* 0x54 */ OMCAMERAVIEW lbl_1_data_54 = { { 0.0f, 200.0f, -500.0f }, { 0.0f, 0.0f, 0.0f }, 500.0f };
/* 0x70 */ OMCAMERAVIEW lbl_1_data_70 = { { -433.0f, 200.0f, -250.0f }, { 0.0f, 60.0f, 0.0f }, 500.0f };
/* 0x8C */ OMCAMERAVIEW lbl_1_data_8C = { { -433.0f, 200.0f, 250.0f }, { 0.0f, 120.0f, 0.0f }, 500.0f };
/* 0xA8 */ OMCAMERAVIEW lbl_1_data_A8 = { { 0.0f, 200.0f, -500.0f }, { 0.0f, 0.0f, 0.0f }, 500.0f };
/* 0xC4 */ OMCAMERAVIEW lbl_1_data_C4 = { { 0.0f, 200.0f, -500.0f }, { 0.0f, 0.0f, 0.0f }, 500.0f };
/* 0xE0 */ OMCAMERAVIEW lbl_1_data_E0 = { { 0.0f, 200.0f, 1961.0f }, { 0.0f, 180.0f, 0.0f }, 140.0f };

/* 255 insns */
void ObjectSetup(void)
{
    OSReport("******* SDR ObjectSetup *********\n");
    lbl_1_bss_5AC[0] = omInitObjMan(50, 0x2000);
    lbl_1_bss_0 = 0;
    if (omovlevtno == 0) {
        if (SLSaveFlagGet()) {
            SLSdLoad(0, SLCurBoxNoGet(), &GwSdCommon);
        }
        sdWorkInt[0] = 0;
        GwSdBackupNo = -1;
    }
    if (omovlevtno == 4) {
        HuAudAUXSet(4, 1);
    } else {
        HuAudAUXSet(7, 1);
    }
    omSysPauseEnable(0);
    Hu3DCameraCreate(0x3F);
    Hu3DCameraPerspectiveSet(0x3B, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(0x3B, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(HU3D_CAM2, 40.0f, 30.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSetMulti(HU3D_CAM0 | HU3D_CAM1, &lbl_1_data_0);
    omCameraViewSetMulti(HU3D_CAM2, &lbl_1_data_1C);
    lbl_1_bss_568[0] = Hu3DGLightCreate(1000.0f, 1000.0f, 1000.0f, -1.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lbl_1_bss_568[0]);
    lbl_1_bss_568[1] = Hu3DGLightCreate(100.0f, 100.0f, 100.0f, 1.0f, -1.0f, -1.0f, 24, 24, 24);
    Hu3DGLightInfinitytSet(lbl_1_bss_568[1]);
    omAddObjEx(lbl_1_bss_5AC[0], 0, 32, 32, -1, fn_1_1F40);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
    HuPrcChildCreate(fn_1_49C, 1000, 0x3000, 0, lbl_1_bss_5AC[0]);
    HuPrcChildCreate(fn_1_35E8, 10, 0x3000, 0, lbl_1_bss_5AC[0]);
    Hu3DNoSyncSet(1);
    lbl_1_bss_5B8 = 0.0f;
    lbl_1_bss_5C6 = 0;
    if (GwSdCommon.extCharSelF) {
        lbl_1_data_4F4[4] = 11;
    } else {
        lbl_1_data_4F4[4] = 10;
    }
}

/* 0x120 */ u32 lbl_1_data_120[6] = { 0x190031, 0x19002D, 0x19002E, 0x190032, 0x190030, 0x19002F };

/* 1068 insns */
void fn_1_49C(void)
{
    OMCAMERAVIEW view;
    HuVecF unused = { 0.0f, 195.0f, -1155.0f };
    GWSDBACKUP *backup;
    s16 i;
    s16 dir;
    s16 dirNext;
    s32 quitF;
    s16 choice;

    quitF = 0;
    if (omovlevtno == 4) {
        fn_1_1C260();
    }
    if (omovlevtno == 2) {
        if (GwSdBattle.winnerNo == 0) {
            if (sdWorkInt[4] == 0) {
                GwCommon.sdVsWinCnt[sdWorkInt[3]][sdWorkInt[7]]++;
                if (GwCommon.sdVsWinCnt[sdWorkInt[3]][sdWorkInt[7]] > 999) {
                    GwCommon.sdVsWinCnt[sdWorkInt[3]][sdWorkInt[7]] = 999;
                }
            }
        } else if (GwSdBattle.winnerNo == 1) {
            if (sdWorkInt[2] == 1) {
                i = sdWorkInt[7] ^ 1;
                if (sdWorkInt[4] == 0) {
                    GwCommon.sdVsWinCnt[sdWorkInt[3]][i]++;
                    if (GwCommon.sdVsWinCnt[sdWorkInt[3]][i] > 999) {
                        GwCommon.sdVsWinCnt[sdWorkInt[3]][i] = 999;
                    }
                }
            } else {
                backup = &GwSdBackup[GwSdBackupNo];
                SLCommonLoadCopy(&lbl_1_bss_10, backup->slotNo, backup->boxNo);
                if (sdWorkInt[4] == 0) {
                    lbl_1_bss_10.sdVsWinCnt[sdWorkInt[3]][backup->garageNo]++;
                    if (lbl_1_bss_10.sdVsWinCnt[sdWorkInt[3]][backup->garageNo] > 999) {
                        lbl_1_bss_10.sdVsWinCnt[sdWorkInt[3]][backup->garageNo] = 999;
                    }
                }
                SLCommonSaveCopy(&lbl_1_bss_10, backup->slotNo, backup->boxNo);
            }
        }
        GwCommon.sdVsPlayCnt++;
        if (GwCommon.sdVsPlayCnt > 999) {
            GwCommon.sdVsPlayCnt = 999;
        }
        if (sdWorkInt[2] == 2) {
            backup = &GwSdBackup[GwSdBackupNo];
            SLCommonLoadCopy(&lbl_1_bss_10, backup->slotNo, backup->boxNo);
            lbl_1_bss_10.sdVsPlayCnt++;
            if (lbl_1_bss_10.sdVsPlayCnt > 999) {
                lbl_1_bss_10.sdVsPlayCnt = 999;
            }
            SLCommonSaveCopy(&lbl_1_bss_10, backup->slotNo, backup->boxNo);
            if (backup->slotNo == 1) {
                SLSaveSdExec();
            }
        }
    }
    fn_1_18FC();
    dirNext = 0;
    if (omovlevtno == 0) {
        HuAudBGMPlay(41);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_WHITEFADE, 60);
        HuPrcSleep(30);
        Hu3DModelAttrSet(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
        omCameraViewMoveMulti(HU3D_CAM2, &lbl_1_data_38, 90, 0);
        while (WipeCheckEnd()) {
            HuPrcVSleep();
        }
        while (!omCameraViewCheck(HU3D_CAM2)) {
            HuPrcVSleep();
        }
        HuPrcChildCreate(fn_1_154C, 1000, 0x3000, 0, lbl_1_bss_5AC[0]);
        HuWinExOpen(lbl_1_bss_570[0]);
        HuWinMesSet(lbl_1_bss_570[0], 0x190001);
        HuWinMesWait(lbl_1_bss_570[0]);
        if (!GwSdCommon.unkFlag) {
            HuWinMesSet(lbl_1_bss_570[0], 0x190002);
            HuAudFXPlay(0x2EF);
            HuWinMesWait(lbl_1_bss_570[0]);
            GwSdCommon.unkFlag = 1;
            for (i = GwSdCommon.prevPoint = 0; i < 4; i++) {
                GwSdCommon.prevPoint += GwCommon.sdPoint[i];
            }
        }
        lbl_1_bss_8[0] = 0;
        HuWinExClose(lbl_1_bss_570[0]);
        omCameraViewMoveMulti(HU3D_CAM2, &lbl_1_data_54, 60, 0);
        HuPrcSleep(40);
        HuWinExOpen(lbl_1_bss_570[0]);
        lbl_1_bss_56C = 0;
        view = lbl_1_data_54;
        HuWinMesSet(lbl_1_bss_570[0], lbl_1_data_120[lbl_1_bss_56C]);
        HuWinMesWait(lbl_1_bss_570[0]);
        HuWinDispOn(lbl_1_bss_56E);
        HuWinMesSet(lbl_1_bss_56E, 0x20004);
    } else if (omovlevtno == 1) {
        HuAudBGMPlay(41);
        lbl_1_bss_56C = 0;
        view = lbl_1_data_54;
        omCameraViewSetMulti(HU3D_CAM2, &lbl_1_data_38);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        while (WipeCheckEnd()) {
            HuPrcVSleep();
        }
        fn_1_256B4();
        goto reopen;
    } else if (omovlevtno == 2 || omovlevtno == 3) {
        HuAudBGMPlay(41);
        switch (sdWorkInt[7]) {
            case 0:
                lbl_1_bss_56C = 1;
                view = lbl_1_data_70;
                goto garage0;
            case 1:
                lbl_1_bss_56C = 2;
                view = lbl_1_data_8C;
                goto garage1;
            default:
                lbl_1_bss_56C = 5;
                view = lbl_1_data_A8;
                goto garage0;
        }
    } else if (omovlevtno == 4) {
        fn_1_1C260();
        HuAudBGMPlay(41);
    }
    while (1) {
        dir = 0;
        if (fn_1_507C(7) & PAD_BUTTON_LEFT) {
            dir = 1;
        } else if (fn_1_507C(7) & PAD_BUTTON_RIGHT) {
            dir = -1;
        } else if (fn_1_4FD0(7) & PAD_BUTTON_B) {
            dir = 3 - lbl_1_bss_56C;
        }
        if (dirNext) {
            dir = dirNext;
            dirNext = 0;
        }
        if (dir) {
            lbl_1_bss_56C += dir;
            if (lbl_1_bss_56C < 0) {
                lbl_1_bss_56C = 5;
            }
            if (lbl_1_bss_56C > 5) {
                lbl_1_bss_56C = 0;
            }
            view.center.x = 500.0 * -sin(M_PI * (lbl_1_bss_56C * 60) / 180.0);
            view.center.z = 500.0 * -cos(M_PI * (lbl_1_bss_56C * 60) / 180.0);
            view.rot.y = lbl_1_bss_56C * 60;
            if (CRotM[2].y < 0.0f) {
                CRotM[2].y += 360.0f;
            }
            if (CRotM[2].y >= 360.0f) {
                CRotM[2].y -= 360.0f;
            }
            omCameraViewMoveMulti(HU3D_CAM2, &view, 60, 0);
            HuAudFXPlay(0);
            for (i = 0; i < 30; i++) {
                fn_1_17B0();
                if (fn_1_4FD0(7) & PAD_BUTTON_LEFT) {
                    dirNext = 1;
                } else if (fn_1_4FD0(7) & PAD_BUTTON_RIGHT) {
                    dirNext = -1;
                }
                HuPrcVSleep();
            }
            HuWinMesSet(lbl_1_bss_570[0], lbl_1_data_120[lbl_1_bss_56C]);
            HuWinMesWait(lbl_1_bss_570[0]);
        }
        if ((fn_1_4FD0(7) & PAD_BUTTON_A) && !((lbl_1_bss_56C == 0 || lbl_1_bss_56C == 4) && ((fn_1_4FD0(2) & PAD_BUTTON_A) || (fn_1_4FD0(4) & PAD_BUTTON_A)))) {
            HuAudFXPlay(1);
            HuWinDispOff(lbl_1_bss_56E);
            switch (lbl_1_bss_56C) {
                case 0:
                    HuWinExClose(lbl_1_bss_570[0]);
                    omCameraViewMoveMulti(HU3D_CAM2, &lbl_1_data_38, 60, 0);
                    HuPrcSleep(60);
                    fn_1_256B4();
                    break;
                case 1:
                    if (!(lbl_1_bss_5BC[0] & 0x100)) {
                        HuWinMesSet(lbl_1_bss_570[0], 0x190063);
                        HuWinMesWait(lbl_1_bss_570[0]);
                    } else {
                        HuWinExClose(lbl_1_bss_570[0]);
                    garage0:
                        fn_1_5854(0);
                    }
                    break;
                case 2:
                    if (!(lbl_1_bss_5BC[1] & 0x100)) {
                        HuWinMesSet(lbl_1_bss_570[0], 0x190064);
                        HuWinMesWait(lbl_1_bss_570[0]);
                    } else {
                        HuWinExClose(lbl_1_bss_570[0]);
                    garage1:
                        fn_1_5854(1);
                    }
                    break;
                case 5:
                    if (!(lbl_1_bss_5BC[2] & 0x100)) {
                        HuWinMesSet(lbl_1_bss_570[0], 0x190065);
                        HuWinMesWait(lbl_1_bss_570[0]);
                    } else if (!SLSaveFlagGet()) {
                        HuWinMesSet(lbl_1_bss_570[0], 0x19005C);
                        HuWinMesWait(lbl_1_bss_570[0]);
                    } else {
                        HuWinExClose(lbl_1_bss_570[0]);
                        fn_1_13D08();
                    }
                    break;
                case 4:
                    HuWinExClose(lbl_1_bss_570[0]);
                    fn_1_193C0();
                    break;
                case 3:
                    HuWinMesSet(lbl_1_bss_570[0], 0x190005);
                    HuWinMesWait(lbl_1_bss_570[0]);
                    choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
                    if (choice == 0) {
                        HuWinExClose(lbl_1_bss_570[0]);
                        omCameraViewMoveMulti(HU3D_CAM2, &lbl_1_data_E0, 60, 0);
                        HuPrcSleep(60);
                        quitF = 1;
                    }
                    break;
            }
            if (quitF) {
                break;
            }
        reopen:
            omCameraViewMoveMulti(HU3D_CAM2, &view, 60, 0);
            HuPrcVSleep(30);
            HuWinExOpen(lbl_1_bss_570[0]);
            HuWinMesSet(lbl_1_bss_570[0], lbl_1_data_120[lbl_1_bss_56C]);
            HuWinMesWait(lbl_1_bss_570[0]);
            HuWinMesSet(lbl_1_bss_56E, 0x20004);
            HuWinDispOn(lbl_1_bss_56E);
            fn_1_17B0();
        }
        HuPrcVSleep();
    }
    if (SLSaveFlagGet()) {
        SLSdSave(0, SLCurBoxNoGet(), &GwSdCommon);
    }
    HuARDirFree(DATA_sd00);
    HuARDirFree(DATA_sdroom);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    HuAudSStreamAllFadeOut(1000);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    if (RenderMode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }
    omOvlReturnEx(1, 1);
    while (1) {
        HuPrcVSleep();
    }
}

/* 153 insns */
void fn_1_154C(void)
{
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s16 i;

    lbl_1_bss_8[0] = 1;
    grpId = HuSprGrpCreate(1);
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 46), HU_MEMNUM_OVL, HEAP_MODEL)), 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprGrpPosSet(grpId, 0.0f, 0.0f);
    for (i = 1; i <= 10; i++) {
        HuSprPosSet(grpId, 0, 288.0f, 64.0 - 120.0 * (1.0 - sin(M_PI * (90.0 * (i / 10.0)) / 180.0)));
        HuPrcVSleep();
    }
    while (lbl_1_bss_8[0]) {
        HuPrcVSleep();
    }
    for (i = 1; i <= 10; i++) {
        HuSprPosSet(grpId, 0, 288.0f, 64.0 - 120.0 * (1.0 - cos(M_PI * (90.0 * (i / 10.0)) / 180.0)));
        HuPrcVSleep();
    }
    HuSprGrpKill(grpId);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 83 insns */
void fn_1_17B0(void)
{
    float rotY = CRotM[2].y;

    if (rotY < 0.0f) {
        rotY += 360.0f;
    }
    if (rotY >= 360.0f) {
        rotY -= 360.0f;
    }
    if (rotY < 180.0f) {
        Hu3DModelAttrReset(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
        fn_1_7298();
        fn_1_16064();
    } else {
        Hu3DModelAttrSet(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
        fn_1_7320();
        fn_1_16024();
    }
}

/* 401 insns */
void fn_1_18FC(void)
{
    HU3DMODELID modelId;
    HUWIN *win;

    if (omovlevtno == 0) {
        CharDataClose(-1);
        HuAR_DVDtoARAM(DATA_sdroom);
        HuAR_DVDtoARAM(DATA_sd00);
        HuAMemDump();
    }
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[0] = modelId;
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[1] = modelId;
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[2] = modelId;
    Hu3DModelRotSet(modelId, 0.0f, -60.0f, 0.0f);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 24), HU_MEMNUM_OVL, HEAP_MODEL), modelId, "door_a1");
    Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 22), HU_MEMNUM_OVL, HEAP_MODEL), modelId, "garage_a1");
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[3] = modelId;
    Hu3DModelRotSet(modelId, 0.0f, 60.0f, 0.0f);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[4] = modelId;
    Hu3DModelRotSet(modelId, 0.0f, 120.0f, 0.0f);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 23), HU_MEMNUM_OVL, HEAP_MODEL), modelId, "door_a1");
    Hu3DAnimCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 21), HU_MEMNUM_OVL, HEAP_MODEL), modelId, "garage_a1");
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[5] = modelId;
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DMotionTimeSet(modelId, 60.0f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 4), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58C[6] = modelId;
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 17), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_58A = modelId;
    Hu3DModelPosSet(modelId, 0.0f, 195.0f, -1155.0f);
    Hu3DModelScaleSet(modelId, 1.8f, 1.8f, 1.8f);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    lbl_1_bss_584[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 18), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_584[1] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 19), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_584[2] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 20), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, lbl_1_bss_584[0]);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    HuDataDirClose(DATA_sdroom);
    lbl_1_bss_570[0] = HuWinExCreateFrame(16.0f, 360.0f, 544, 68, -1, 1);
    HuWinMesPalSet(lbl_1_bss_570[0], 7, 0, 0, 0);
    HuWinMesSpeedSet(lbl_1_bss_570[0], 0);
    HuWinPriSet(lbl_1_bss_570[0], 50);
    win = &winData[lbl_1_bss_570[0]];
    win->padMask = 7;
    lbl_1_bss_56E = HuWinCreate(-10000.0f, 322.0f, 560, 42, 0);
    HuWinBGTPLvlSet(lbl_1_bss_56E, 0.0f);
    HuWinAttrSet(lbl_1_bss_56E, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSpeedSet(lbl_1_bss_56E, 0);
    HuWinDispOff(lbl_1_bss_56E);
    HuWinPriSet(lbl_1_bss_56E, 50);
    HuSprExecLayerCameraSet(64, HU3D_CAM2, 6);
    fn_1_556C();
    fn_1_13B1C();
    NameEnterInit();
    fn_1_19324();
    fn_1_1C25C();
}

/* 1450 insns */
void fn_1_1F40(OMOBJ *obj)
{
    HuVecF pos;
    HuVecF offset;
    HuVecF dir;
    HuVecF yOfs;
    HuVecF offset2;
    HuVecF dir2;
    HuVecF yOfs2;
    float rotZ;
    float rotZ2;
    s8 stickPos;
    s8 stickPos2;

    if (lbl_1_bss_4) {
        CRotM[2].y += 0.1f * HuPadStkX[0];
        CRotM[2].x += 0.1f * HuPadStkY[0];
        CZoomM[2] += HuPadTrigL[0] / 2;
        CZoomM[2] -= HuPadTrigR[0] / 2;
        if (CZoomM[2] < 50.0f) {
            CZoomM[2] = 50.0f;
        }
        pos.x = CenterM[2].x + (CZoomM[2] * (HuSin(CRotM[2].y) * HuCos(CRotM[2].x)));
        pos.y = (CenterM[2].y + (CZoomM[2] * -HuSin(CRotM[2].x)));
        pos.z = (CenterM[2].z + (CZoomM[2] * (HuCos(CRotM[2].y) * HuCos(CRotM[2].x))));
        offset.x = CenterM[2].x - pos.x;
        offset.y = CenterM[2].y - pos.y;
        offset.z = CenterM[2].z - pos.z;
        dir.x = (HuSin(CRotM[2].y) * HuSin(CRotM[2].x));
        dir.y = HuCos(CRotM[2].x);
        dir.z = (HuCos(CRotM[2].y) * HuSin(CRotM[2].x));
        rotZ = CRotM[2].z;
        yOfs.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * HuCos(rotZ))
            + dir.y * (offset.x * offset.y * (1.0f - HuCos(rotZ)) - offset.z * HuSin(rotZ))
            + dir.z * (offset.x * offset.z * (1.0f - HuCos(rotZ)) + offset.y * HuSin(rotZ));

        yOfs.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * HuCos(rotZ))
            + dir.x * (offset.x * offset.y * (1.0f - HuCos(rotZ)) + offset.z * HuSin(rotZ))
            + dir.z * (offset.y * offset.z * (1.0f - HuCos(rotZ)) - offset.x * HuSin(rotZ));

        yOfs.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * HuCos(rotZ))
            + (dir.x * (offset.x * offset.z * (1.0 - HuCos(rotZ)) - offset.y * HuSin(rotZ))
                + dir.y * (offset.y * offset.z * (1.0 - HuCos(rotZ)) + offset.x * HuSin(rotZ)));

        VECCrossProduct(&dir, &offset, &offset);
        VECNormalize(&offset, &offset);
        stickPos = (HuPadSubStkX[0] & 0xF8);
        if (stickPos != 0) {
            CenterM[2].x += 0.05f * (offset.x * stickPos);
            CenterM[2].y += 0.05f * (offset.y * stickPos);
            CenterM[2].z += 0.05f * (offset.z * stickPos);
        }
        VECNormalize(&yOfs, &offset);
        stickPos = -(HuPadSubStkY[0] & 0xF8);
        if (stickPos != 0) {
            CenterM[2].x += 0.05f * (offset.x * stickPos);
            CenterM[2].y += 0.05f * (offset.y * stickPos);
            CenterM[2].z += 0.05f * (offset.z * stickPos);
        }
        CRotM[3].y += 0.1f * HuPadStkX[1];
        CRotM[3].x += 0.1f * HuPadStkY[1];
        CZoomM[3] += HuPadTrigL[1] / 2;
        CZoomM[3] -= HuPadTrigR[1] / 2;
        if (CZoomM[3] < 100.0f) {
            CZoomM[3] = 100.0f;
        }
        pos.x = CenterM[3].x + (CZoomM[3] * (HuSin(CRotM[3].y) * HuCos(CRotM[3].x)));
        pos.y = (CenterM[3].y + (CZoomM[3] * -HuSin(CRotM[3].x)));
        pos.z = (CenterM[3].z + (CZoomM[3] * (HuCos(CRotM[3].y) * HuCos(CRotM[3].x))));
        offset2.x = CenterM[3].x - pos.x;
        offset2.y = CenterM[3].y - pos.y;
        offset2.z = CenterM[3].z - pos.z;
        dir2.x = (HuSin(CRotM[3].y) * HuSin(CRotM[3].x));
        dir2.y = HuCos(CRotM[3].x);
        dir2.z = (HuCos(CRotM[3].y) * HuSin(CRotM[3].x));
        rotZ2 = CRotM[3].z;
        yOfs2.x = dir2.x * (offset2.x * offset2.x + (1.0f - offset2.x * offset2.x) * HuCos(rotZ2))
            + dir2.y * (offset2.x * offset2.y * (1.0f - HuCos(rotZ2)) - offset2.z * HuSin(rotZ2))
            + dir2.z * (offset2.x * offset2.z * (1.0f - HuCos(rotZ2)) + offset2.y * HuSin(rotZ2));

        yOfs2.y = dir2.y * (offset2.y * offset2.y + (1.0f - offset2.y * offset2.y) * HuCos(rotZ2))
            + dir2.x * (offset2.x * offset2.y * (1.0f - HuCos(rotZ2)) + offset2.z * HuSin(rotZ2))
            + dir2.z * (offset2.y * offset2.z * (1.0f - HuCos(rotZ2)) - offset2.x * HuSin(rotZ2));

        yOfs2.z = dir2.z * (offset2.z * offset2.z + (1.0f - offset2.z * offset2.z) * HuCos(rotZ2))
            + (dir2.x * (offset2.x * offset2.z * (1.0 - HuCos(rotZ2)) - offset2.y * HuSin(rotZ2))
                + dir2.y * (offset2.y * offset2.z * (1.0 - HuCos(rotZ2)) + offset2.x * HuSin(rotZ2)));

        VECCrossProduct(&dir2, &offset2, &offset2);
        VECNormalize(&offset2, &offset2);
        stickPos2 = (HuPadSubStkX[1] & 0xF8);
        if (stickPos2 != 0) {
            CenterM[3].x += 0.05f * (offset2.x * stickPos2);
            CenterM[3].y += 0.05f * (offset2.y * stickPos2);
            CenterM[3].z += 0.05f * (offset2.z * stickPos2);
        }
        VECNormalize(&yOfs2, &offset2);
        stickPos2 = -(HuPadSubStkY[1] & 0xF8);
        if (stickPos2 != 0) {
            CenterM[3].x += 0.05f * (offset2.x * stickPos2);
            CenterM[3].y += 0.05f * (offset2.y * stickPos2);
            CenterM[3].z += 0.05f * (offset2.z * stickPos2);
        }
    }
}

/* 553 insns */
void fn_1_35E8(void)
{
    HuVecF pos;
    HuVecF target;
    HuVecF up;
    HuVecF dir;
    HuVecF offset;
    float rotX;
    float rotY;
    float rotZ;
    u8 i;

    while (1) {
        for (i = 0; i < 6; i++) {
            rotX = CRotM[i].x;
            rotY = CRotM[i].y;
            rotZ = CRotM[i].z;
            pos.x = CenterM[i].x + (CZoomM[i] * (HuSin(rotY) * HuCos(rotX)));
            pos.y = CenterM[i].y + (CZoomM[i] * -HuSin(rotX));
            pos.z = CenterM[i].z + (CZoomM[i] * (HuCos(rotY) * HuCos(rotX)));
            target.x = CenterM[i].x;
            target.y = CenterM[i].y;
            target.z = CenterM[i].z;
            up.x = HuSin(rotY) * HuSin(rotX);
            up.y = HuCos(rotX);
            up.z = HuCos(rotY) * HuSin(rotX);
            dir.x = HuSin(rotY) * HuSin(rotX);
            dir.y = HuCos(rotX);
            dir.z = HuCos(rotY) * HuSin(rotX);
            VECSubtract(&pos, &target, &offset);
            VECNormalize(&offset, &offset);
            up.x = dir.x * (offset.x * offset.x + (1.0f - offset.x * offset.x) * HuCos(rotZ))
                + dir.y * (offset.x * offset.y * (1.0f - HuCos(rotZ)) - offset.z * HuSin(rotZ))
                + dir.z * (offset.x * offset.z * (1.0f - HuCos(rotZ)) + offset.y * HuSin(rotZ));
            up.y = dir.y * (offset.y * offset.y + (1.0f - offset.y * offset.y) * HuCos(rotZ))
                + dir.x * (offset.x * offset.y * (1.0f - HuCos(rotZ)) + offset.z * HuSin(rotZ))
                + dir.z * (offset.y * offset.z * (1.0f - HuCos(rotZ)) - offset.x * HuSin(rotZ));
            up.z = dir.z * (offset.z * offset.z + (1.0f - offset.z * offset.z) * HuCos(rotZ))
                + (dir.x * (offset.x * offset.z * (1.0 - HuCos(rotZ)) - offset.y * HuSin(rotZ))
                    + dir.y * (offset.y * offset.z * (1.0 - HuCos(rotZ)) + offset.x * HuSin(rotZ)));
            VECNormalize(&up, &up);
            Hu3DCameraPosSetV(1 << i, &pos, &up, &target);
        }
        HuPrcVSleep();
    }
}

