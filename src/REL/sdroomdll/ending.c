/*
 * sdroomdll ending.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/ending.s.
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
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x7D0 lbl_1_rodata_7D0 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_7D4 = -10000.0f; /* 0x7D4 */
static const float lbl_1_rodata_7D8 = 300.0f; /* 0x7D8 */
static const float lbl_1_rodata_7DC = 400.0f; /* 0x7DC */
static const float lbl_1_rodata_7E0 = 0.0f; /* 0x7E0 */
static const float lbl_1_rodata_7E4 = 310.0f; /* 0x7E4 */
static const double lbl_1_rodata_7E8 = 180.0; /* 0x7E8 */
static const double lbl_1_rodata_7F0 = 310.0; /* 0x7F0 */
static const double lbl_1_rodata_7F8 = 400.0; /* 0x7F8 */
static const double lbl_1_rodata_800 = 3.141592653589793; /* 0x800 */
static const float lbl_1_rodata_808 = 90.0f; /* 0x808 */
static const float lbl_1_rodata_80C = 120.0f; /* 0x80C */
static const float lbl_1_rodata_810 = 364.0f; /* 0x810 */
static const float lbl_1_rodata_814 = -1000.0f; /* 0x814 */
static const double lbl_1_rodata_818 = 300.0; /* 0x818 */
static const float lbl_1_rodata_820 = 2000.0f; /* 0x820 */
static const float lbl_1_rodata_824 = 50.0f; /* 0x824 */
static const double lbl_1_rodata_828 = 100.0; /* 0x828 */
static const float lbl_1_rodata_830 = 0.5f; /* 0x830 */
static const float lbl_1_rodata_834 = -3100.0f; /* 0x834 */
static const float lbl_1_rodata_838 = 148.0f; /* 0x838 */
static const float lbl_1_rodata_83C = 260.0f; /* 0x83C */
static const double lbl_1_rodata_840 = 1.0; /* 0x840 */
static const double lbl_1_rodata_848 = 20.0; /* 0x848 */
static const double lbl_1_rodata_850 = 640.0; /* 0x850 */
static const float lbl_1_rodata_858 = 1.0f; /* 0x858 */
static const float lbl_1_rodata_85C = -90.0f; /* 0x85C */
static const float lbl_1_rodata_860 = 150.0f; /* 0x860 */
static const float lbl_1_rodata_864 = 350.0f; /* 0x864 */
static const double lbl_1_rodata_868 = 90.0; /* 0x868 */
static const double lbl_1_rodata_870 = 60.0; /* 0x870 */
static const float lbl_1_rodata_878 = -500.0f; /* 0x878 */
static const double lbl_1_rodata_880 = 0.3; /* 0x880 */
static const double lbl_1_rodata_888 = 0.7; /* 0x888 */
static const float lbl_1_rodata_890 = 3.0f; /* 0x890 */
static const double lbl_1_rodata_898 = 50.0; /* 0x898 */
static const float lbl_1_rodata_8A0 = 720.0f; /* 0x8A0 */
static const double lbl_1_rodata_8A8 = 0.2; /* 0x8A8 */
static const float lbl_1_rodata_8B0 = -400.0f; /* 0x8B0 */
static const float lbl_1_rodata_8B4 = -310.0f; /* 0x8B4 */
static const double lbl_1_rodata_8B8 = -310.0; /* 0x8B8 */
static const double lbl_1_rodata_8C0 = -400.0; /* 0x8C0 */
static const double lbl_1_rodata_8C8 = 720.0; /* 0x8C8 */
static const float lbl_1_rodata_8D0 = 180.0f; /* 0x8D0 */
static const double lbl_1_rodata_8D8 = 30.0; /* 0x8D8 */
static const double lbl_1_rodata_8E0 = 0.5; /* 0x8E0 */
/* 0x8E8 lbl_1_rodata_8E8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_8F0 = 200.0f; /* 0x8F0 */
static const float lbl_1_rodata_8F4 = 1.5f; /* 0x8F4 */
static const float lbl_1_rodata_8F8 = 4.0f; /* 0x8F8 */
static const float lbl_1_rodata_8FC = 40.0f; /* 0x8FC */
static const float lbl_1_rodata_900 = 30.0f; /* 0x900 */
static const float lbl_1_rodata_904 = 15000.0f; /* 0x904 */
static const float lbl_1_rodata_908 = 1.2f; /* 0x908 */
static const float lbl_1_rodata_90C = 256.0f; /* 0x90C */
static const float lbl_1_rodata_910 = 192.0f; /* 0x910 */
static const float lbl_1_rodata_914 = -50.0f; /* 0x914 */
static const float lbl_1_rodata_918 = -1.0f; /* 0x918 */
static const float lbl_1_rodata_91C = 100.0f; /* 0x91C */
static const float lbl_1_rodata_920 = 1000.0f; /* 0x920 */
static const float lbl_1_rodata_924 = -0.1f; /* 0x924 */
static const float lbl_1_rodata_928 = -190.0f; /* 0x928 */
static const float lbl_1_rodata_92C = -2700.0f; /* 0x92C */
static const float lbl_1_rodata_930 = -180.0f; /* 0x930 */
static const float lbl_1_rodata_934 = -765.0f; /* 0x934 */
static const float lbl_1_rodata_938 = 1935.0f; /* 0x938 */
static const float lbl_1_rodata_93C = 670.0f; /* 0x93C */
static const float lbl_1_rodata_940 = -175.0f; /* 0x940 */
static const float lbl_1_rodata_944 = -2840.0f; /* 0x944 */
static const float lbl_1_rodata_948 = -670.0f; /* 0x948 */
static const float lbl_1_rodata_94C = 0.8f; /* 0x94C */
static const float lbl_1_rodata_950 = -0.8f; /* 0x950 */
static const float lbl_1_rodata_954 = 2.0f; /* 0x954 */
static const float lbl_1_rodata_958 = 5.0f; /* 0x958 */
static const float lbl_1_rodata_95C = -15.0f; /* 0x95C */
static const float lbl_1_rodata_960 = -200.0f; /* 0x960 */
static const float lbl_1_rodata_964 = 15.0f; /* 0x964 */
static const float lbl_1_rodata_968 = 288.0f; /* 0x968 */
static const float lbl_1_rodata_96C = 380.0f; /* 0x96C */
static const float lbl_1_rodata_970 = 332.0f; /* 0x970 */
static const float lbl_1_rodata_974 = 362.0f; /* 0x974 */
static const float lbl_1_rodata_978 = 392.0f; /* 0x978 */
static const double lbl_1_rodata_980 = 10.0; /* 0x980 */
static const float lbl_1_rodata_988 = 10.0f; /* 0x988 */
static const float lbl_1_rodata_98C = 360.0f; /* 0x98C */
static const float lbl_1_rodata_990 = 500.0f; /* 0x990 */
static const float lbl_1_rodata_994 = 0.1f; /* 0x994 */
static const double lbl_1_rodata_998 = 0.800000011920929; /* 0x998 */
static const float lbl_1_rodata_9A0 = -6.5f; /* 0x9A0 */
static const float lbl_1_rodata_9A4 = -2.6000001f; /* 0x9A4 */
static const double lbl_1_rodata_9A8 = 14.0; /* 0x9A8 */
/* 0x9B0 lbl_1_rodata_9B0 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x195E */ s16 lbl_1_bss_195E[17];
/* 0x1958 */ s16 lbl_1_bss_1958[3];
/* 0x194E */ s16 lbl_1_bss_194E[5];
/* 0x194C */ s16 lbl_1_bss_194C;
/* 0x18F4 */ SDMACHINEMDL lbl_1_bss_18F4[2];
/* 0x18F0 */ void *lbl_1_bss_18F0;
/* 0x18EC */ ANIMDATA *lbl_1_bss_18EC;
/* 0x18E4 */ HUPROCESS *lbl_1_bss_18E4[2];
/* 0x18E0 */ HUPROCESS *lbl_1_bss_18E0;
/* 0x18DE gap_05_000018DE_bss (0x2): alignment gap */
/* 0x18DC */ s16 lbl_1_bss_18DC;
/* 0x18D8 */ s32 lbl_1_bss_18D8;
/* 0x18D6 gap_05_000018D6_bss (0x2): alignment gap */
/* 0x18D4 */ s16 lbl_1_bss_18D4;
/* 0x18CC */ ANIMDATA *lbl_1_bss_18CC[2];
/* 0xC4C */ SDCONFETTI lbl_1_bss_C4C[50];
/* 0xC40 */ SDCONFETTISYS lbl_1_bss_C40;
/* 0xC3C */ HUPROCESS *lbl_1_bss_C3C;
/* 0xC38 */ HUPROCESS *lbl_1_bss_C38;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x1DE0 */ OMCAMERAVIEW lbl_1_data_1DE0 = { { 37.0f, -32.0f, -3090.0f }, { -26.0f, 50.0f, 0.0f }, 815.0f };
/* 0x1DFC */ OMCAMERAVIEW lbl_1_data_1DFC = { { 0.0f, 140.0f, -40.0f }, { -10.0f, 0.0f, 0.0f }, 1200.0f };
/* 0x1E18 */ OMCAMERAVIEW lbl_1_data_1E18 = { { 36.0f, -10.0f, -95.0f }, { -41.0f, 154.0f, 0.0f }, 5815.0f };
/* 0x1E34 */ OMCAMERAVIEW lbl_1_data_1E34 = { { 0.0f, 80.0f, -3100.0f }, { -15.0f, 0.0f, 0.0f }, 1610.0f };
/* 0x1E50 */ OMCAMERAVIEW lbl_1_data_1E50[3] = { { { -56.0f, 188.0f, 110.0f }, { 10.0f, -29.0f, 0.0f }, 786.0f }, { { 42.0f, 171.0f, -15.0f }, { -15.0f, -100.0f, 0.0f }, 2122.0f }, { { 42.0f, 171.0f, -15.0f }, { -15.0f, 20.0f, 0.0f }, 2122.0f } };
/* 0x1EA4 */ OMCAMERAVIEW lbl_1_data_1EA4 = { { 240.0f, 77.0f, 350.0f }, { -15.0f, -90.0f, 0.0f }, 1100.0f };
/* 0x1EC0 */ OMCAMERAVIEW lbl_1_data_1EC0 = { { 0.0f, 160.0f, -48.0f }, { -5.0f, -90.0f, 0.0f }, 1780.0f };
/* 0x1EDC */ OMCAMERAVIEW lbl_1_data_1EDC = { { 0.0f, 160.0f, -48.0f }, { -10.0f, 0.0f, 0.0f }, 1780.0f };
/* 0x1EF8 */ OMCAMERAVIEW lbl_1_data_1EF8 = { { -15.0f, 100.0f, -74.0f }, { -3.0f, -68.0f, 0.0f }, 3456.0f };
/* 0x1F14 */ OMCAMERAVIEW lbl_1_data_1F14 = { { -7.0f, 192.0f, -104.0f }, { -3.0f, 312.0f, 0.0f }, 1300.0f };
/* 0x1F30 */ OMCAMERAVIEW lbl_1_data_1F30 = { { 8.0f, 160.0f, -48.0f }, { -15.0f, 0.0f, 0.0f }, 3600.0f };
/* 0x1F4C */ OMCAMERAVIEW lbl_1_data_1F4C = { { 8.0f, 160.0f, -48.0f }, { -10.0f, 0.0f, 0.0f }, 1360.0f };
/* 0x1F68 */ OMCAMERAVIEW lbl_1_data_1F68 = { { 92.0f, 100.0f, -154.0f }, { -10.0f, 44.0f, 0.0f }, 700.0f };
/* 0x1F84 */ OMCAMERAVIEW lbl_1_data_1F84 = { { 0.0f, 140.0f, -40.0f }, { 0.0f, 180.0f, 0.0f }, 3246.0f };
/* 0x1FA0 */ OMCAMERAVIEW lbl_1_data_1FA0 = { { 8.0f, 110.0f, -40.0f }, { -10.0f, 0.0f, 0.0f }, 1070.0f };
/* 0x1FBC */ s16 lbl_1_data_1FBC[12][4] = { { 8, 8, 8, 10 }, { 2, 4, 6, 11 }, { 6, 9, 1, 1 }, { 3, 1, 9, 0 }, { 9, 7, 3, 2 }, { 2, 6, 5, 4 }, { 7, 5, 7, 8 }, { 4, 1, 4, 3 }, { 5, 1, 2, 6 }, { 1, 2, 3, 5 }, { 0, 0, 0, 7 }, { 1, 2, 1, 9 } };
/* 0x201C */ HU3DPARMANPARAM lbl_1_data_201C = { 20, 0, 10.0f, 30.0f, 15.0f, { 0.0f, -0.8f, 0.0f }, 70.0f, 0.95f, 40.0f, 0.97f, 2, { { 255, 255, 255, 255 }, { 255, 255, 64, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 128, 128, 0 }, { 255, 64, 32, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x206C */ HU3DPARMANPARAM lbl_1_data_206C = { 20, 0, 2.0f, 30.0f, 15.0f, { 0.0f, 0.5f, 0.0f }, 20.0f, 0.97f, 50.0f, 1.05f, 2, { { 255, 255, 255, 255 }, { 192, 192, 224, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 160, 160, 160, 0 }, { 160, 160, 160, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x20BC */ HU3DPARMANPARAM lbl_1_data_20BC = { 25, 0, 4.0f, 50.0f, 5.0f, { 0.0f, -1.0f, 0.0f }, 0.0f, 1.0f, 40.0f, 0.98f, 2, { { 255, 255, 0, 255 }, { 255, 128, 128, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 255, 0, 0 }, { 255, 128, 128, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };

/* 1381 insns */
void fn_1_20870(s16 *seat)
{
    HuVecF pos;
    u32 mesNo[3];
    HuVec2f size;
    float posY[2];
    char name[] = "";
    s16 j;
    HUWINID winId;
    s16 i;
    s16 charNo;
    HUWIN *winP;
    int seNo;
    float t;
    float rotX;
    float winPosX;
    float winPosY;

    fn_1_21E04();
    omCameraViewSetMulti(4, &lbl_1_data_1E18);
    HuAudBGMPlay(0x25);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(10);
    omCameraViewMoveMulti(4, &lbl_1_data_1DFC, 100, 2);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuPrcSleep(90);
    for (i = 0; i < 2; i++) {
        if (i == 1) {
            omCameraViewSetMulti(4, &lbl_1_data_1EA4);
        }
        charNo = GwSdBattle.machine[i].charNo;
        mesNo[0] = fn_1_24D20(charNo);
        if (i == 0) {
            mesNo[1] = 0x1C0002;
        } else {
            mesNo[1] = 0x1C0004;
        }
        HuWinInsertMesSizeGet(mesNo[0], 0);
        HuWinMesMaxSizeGet(1, &size, mesNo[1]);
        winId = HuWinExCreate(-10000.0f, 300.0f, size.x, size.y, -1);
        HuWinExOpen(winId);
        HuWinInsertMesSet(winId, mesNo[0], 0);
        fn_1_24758(60);
        HuWinMesSet(winId, mesNo[1]);
        HuAudFXPlay(0x2EE);
        HuWinMesWait(winId);
        HuAudSStreamAllFadeOut(500);
        HuWinExClose(winId);
        HuWinKill(winId);
        if (i == 1) {
            fn_1_4534(&lbl_1_bss_18F4[0], 400.0f, 0.0f, 310.0f);
            fn_1_4590(&lbl_1_bss_18F4[0], 0.0f, 180.0 + 180.0 * (atan2(310.0, 400.0) / 3.141592653589793), 0.0f);
        }
        if (i == 0) {
            HuAudJinglePlay(0x2B);
        } else {
            HuAudBGMPlay(0x4A);
        }
        Hu3DModelAttrSet(lbl_1_bss_195E[3], HU3D_ATTR_DISPOFF);
        fn_1_22EE8(1);
        fn_1_22FB0(1);
        Hu3DGLightColorSet(lbl_1_bss_18DC, 0, 0, 0, 255);
        Hu3DModelAttrSet(lbl_1_bss_195E[5], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_195E[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_195E[6], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_195E[2], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_195E[2], HU3D_MOTATTR_PAUSE);
        omCameraViewSetMulti(4, &lbl_1_data_1E34);
        omCameraViewSetMulti(1, &lbl_1_data_1DE0);
        HuPrcSleep(30);
        Hu3DMotionShapeTimeSet(lbl_1_bss_195E[6], 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_195E[6], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_195E[6], HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_195E[2], HU3D_MOTATTR_PAUSE);
        Hu3DMotionCalc(lbl_1_bss_195E[2]);
        HuAudFXPlay(0x515);
        while (!Hu3DMotionEndCheck(lbl_1_bss_195E[2])) {
            Hu3DModelObjPosGet(lbl_1_bss_195E[2], "daidai01", &pos);
            fn_1_4534(&lbl_1_bss_18F4[i], pos.x, pos.y, pos.z);
            fn_1_46C4(&lbl_1_bss_18F4[i], 1);
            if (Hu3DMotionTimeGet(lbl_1_bss_195E[2]) == 90.0f) {
                seNo = HuAudFXPlay(0x516);
            }
            if (Hu3DMotionTimeGet(lbl_1_bss_195E[2]) == 120.0f) {
                HuAudFXPlay(0x517);
                fn_1_230A0();
            }
            HuPrcVSleep();
        }
        HuAudFXStop(seNo);
        HuAudFXPlay(0x51C);
        Hu3DModelObjPosGet(lbl_1_bss_195E[2], "daidai01", &pos);
        fn_1_4534(&lbl_1_bss_18F4[i], pos.x, pos.y, pos.z);
        HuPrcSleep(30);
        charNo = GwSdBattle.machine[i].charNo;
        if (charNo < 32) {
            mesNo[0] = MESSNUM_PTR(name);
        } else {
            mesNo[0] = charNo + 0x1D0000 - 0x13;
        }
        mesNo[1] = fn_1_24D20(charNo);
        if (charNo < 32) {
            mesNo[2] = MESSNUM_PTR(GwSdBattle.machine[i].name);
        } else {
            mesNo[2] = charNo + 0x1D0000 - 0x1F;
        }
        HuWinInsertMesSizeGet(mesNo[0], 0);
        HuWinInsertMesSizeGet(mesNo[1], 1);
        HuWinInsertMesSizeGet(mesNo[2], 2);
        HuWinMesMaxSizeGet(1, &size, (u32)0x1C0002);
        winId = HuWinCreate(-10000.0f, 364.0f, size.x, size.y, 0);
        HuWinInsertMesSet(winId, mesNo[0], 0);
        HuWinInsertMesSet(winId, mesNo[1], 1);
        HuWinInsertMesSet(winId, mesNo[2], 2);
        HuWinMesSpeedSet(winId, 0);
        HuWinMesSet(winId, 0x1C0003);
        winP = &winData[winId];
        winPosX = winP->pos.x;
        winPosY = winP->pos.y;
        HuWinPosSet(winId, -1000.0f, -1000.0f);
        for (j = 1; j <= 300; j++) {
            t = j / 300.0;
            posY[0] = fn_1_22E40((pos.z + 2000.0f * t) - 50.0f);
            posY[1] = fn_1_22E40(50.0f + (pos.z + 2000.0f * t));
            rotX = 180.0 * (atan2(posY[0] - posY[1], 100.0) / 3.141592653589793);
            pos.y = fn_1_22E40(pos.z + 2000.0f * t);
            fn_1_4534(&lbl_1_bss_18F4[i], pos.x, (posY[0] + posY[1]) / 2.0f, pos.z + 2000.0f * t);
            fn_1_4590(&lbl_1_bss_18F4[i], rotX, 0.0f, 0.0f);
            CenterM[0].z = CenterM[2].z = -3100.0f + 2000.0f * t;
            CenterM[0].y = 148.0f + (posY[0] + posY[1]) / 2.0f;
            CenterM[2].y = 260.0f + (posY[0] + posY[1]) / 2.0f;
            if (j > 60 && j <= 80) {
                t = 1.0 - (j - 60) / 20.0;
                HuWinPosSet(winId, winPosX + 640.0 * t, winPosY);
            }
            fn_1_24B24(&lbl_1_bss_18F4[i], 1.0f);
            HuPrcVSleep();
        }
        fn_1_22FB0(0);
        HuWinKill(winId);
        Hu3DModelAttrReset(lbl_1_bss_195E[3], HU3D_ATTR_DISPOFF);
        fn_1_22EE8(0);
        Hu3DGLightColorSet(lbl_1_bss_18DC, 192, 192, 192, 255);
        omCameraViewSetMulti(4, &lbl_1_data_1EC0);
        omCameraViewSetMulti(1, &lbl_1_data_1E50[0]);
        Hu3DModelRotSet(lbl_1_bss_195E[8], 0.0f, -90.0f, 0.0f);
        Hu3DModelPosSet(lbl_1_bss_195E[8], 0.0f, 150.0f, 350.0f);
        for (j = 1; j <= 60; j++) {
            t = 1.0 - sin(3.141592653589793 * (90.0 * (j / 60.0)) / 180.0);
            fn_1_4534(&lbl_1_bss_18F4[i], 0.0f, 0.0f, -500.0f * t);
            fn_1_4590(&lbl_1_bss_18F4[i], 0.0f, 0.0f, 0.0f);
            fn_1_24B24(&lbl_1_bss_18F4[i], 0.3 + 0.7 * t);
            HuPrcVSleep();
        }
        Hu3DModelAttrReset(lbl_1_bss_195E[16], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_195E[16], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(lbl_1_bss_195E[16], 3.0f);
        Hu3DMotionTimeSet(lbl_1_bss_195E[16], 0.0f);
        Hu3DModelScaleSet(lbl_1_bss_195E[16], 1.0f, 1.0f, 1.0f);
        HuAudFXPlay(0x51D);
        for (j = 1; j <= 50; j++) {
            t = sin(3.141592653589793 * (90.0 * (j / 50.0)) / 180.0);
            fn_1_4590(&lbl_1_bss_18F4[i], 0.0f, 720.0f * t, 0.0f);
            t = 1.0 + 0.2 * t;
            Hu3DModelScaleSet(lbl_1_bss_195E[16], t, 1.0f, t);
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        Hu3DModelAttrSet(lbl_1_bss_195E[16], HU3D_ATTR_DISPOFF);
        while (!omCameraViewCheck(4)) {
            HuPrcVSleep();
        }
    }
    HuAudSStreamAllFadeOut(500);
    HuAudSStreamVolSet(2, 0, 0);
    HuAudJinglePlay(0x25);
    WipeCreate(WIPE_MODE_OUT, 0x81, 10);
    HuPrcVSleep();
    HuAudSStreamVolSet(2, 127, 500);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    omCameraViewSetMulti(1, &lbl_1_data_1EF8);
    omCameraViewSetMulti(4, &lbl_1_data_1EDC);
    fn_1_4534(&lbl_1_bss_18F4[1], -400.0f, 0.0f, -310.0f);
    fn_1_4590(&lbl_1_bss_18F4[1], 0.0f, 180.0 + 180.0 * (atan2(-310.0, -400.0) / 3.141592653589793), 0.0f);
    Hu3DGLightColorSet(lbl_1_bss_18DC, 192, 192, 192, 255);
    Hu3DModelPosSet(lbl_1_bss_195E[8], 0.0f, 400.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_195E[8], 0.0f, 0.0f, 0.0f);
    fn_1_22FB0(0);
    WipeCreate(WIPE_MODE_IN, 0x81, 60);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DModelPosSet(lbl_1_bss_195E[7], 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_195E[7], 0.0f, 0.0f, 0.0f);
    Hu3DParManAttrReset(lbl_1_bss_194E[4], 1);
    for (j = 1; j <= 50; j++) {
        t = j / 50.0;
        Hu3DModelRotSet(lbl_1_bss_195E[8], 0.0f, 720.0 * (1.0 - cos(3.141592653589793 * (180.0f * t) / 180.0)), 0.0f);
        if (j > 30) {
            t = (j - 30) / 20.0;
            Hu3DModelScaleSet(lbl_1_bss_195E[7], t, 1.0f, t);
        }
        HuPrcVSleep();
    }
    Hu3DParManAttrSet(lbl_1_bss_194E[4], 1);
    HuPrcSleep(30);
    HuWinMesMaxSizeGet(1, &size, (u32)0x1C0005);
    HuAudFXPlay(0x2EF);
    winId = HuWinExCreate(-10000.0f, 364.0f, size.x, size.y, -1);
    HuWinExOpen(winId);
    fn_1_24758(60);
    HuWinMesSet(winId, 0x1C0005);
    HuWinMesWait(winId);
    HuWinExClose(winId);
    HuWinKill(winId);
    lbl_1_bss_18D8 = 0;
    HuAudFXPlay(0x518);
    for (j = 1; j <= 30; j++) {
        t = j / 30.0;
        fn_1_4534(&lbl_1_bss_18F4[0], 400.0 * (1.0 - t), 300.0 * sin(3.141592653589793 * (180.0f * t) / 180.0), 310.0 * (1.0 - t));
        t = 0.5 + 0.5 * (1.0 - t);
        fn_1_45E4(&lbl_1_bss_18F4[0], t, t, t);
        HuPrcVSleep();
    }
    fn_1_46C4(&lbl_1_bss_18F4[0], 0);
    HuAudFXPlay(0x518);
    for (j = 1; j <= 30; j++) {
        t = j / 30.0;
        fn_1_4534(&lbl_1_bss_18F4[1], -400.0 * (1.0 - t), 300.0 * sin(3.141592653589793 * (180.0f * t) / 180.0), -310.0 * (1.0 - t));
        t = 0.5 + 0.5 * (1.0 - t);
        fn_1_45E4(&lbl_1_bss_18F4[1], t, t, t);
        HuPrcVSleep();
    }
    fn_1_46C4(&lbl_1_bss_18F4[1], 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 912 insns */
void fn_1_21E04(void)
{
    HU3DMODELID modelId;
    s16 i;
    HU3DPARMANID parManId;
    s16 charNo;
    ANIMDATA *anim;
    HUSPRGRPID grpId;
    HUSPRID sprId;

    modelId = lbl_1_bss_195E[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    modelId = lbl_1_bss_195E[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    lbl_1_bss_195E[2] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    lbl_1_bss_195E[3] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    lbl_1_bss_195E[4] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 5), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    lbl_1_bss_195E[5] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 6), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    Hu3DModelPosSet(modelId, 0.0f, 1.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.0f, 3.0f, 1.0f);
    Hu3DModelLayerSet(modelId, 2);
    modelId = lbl_1_bss_195E[6] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 7), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    lbl_1_bss_195E[7] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 4), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelPosSet(modelId, 0.0f, -1000.0f, 0.0f);
    modelId = lbl_1_bss_195E[8] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 17), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    Hu3DModelPosSet(modelId, 0.0f, 200.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 1.5f, 1.5f, 1.5f);
    lbl_1_bss_195E[9] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATA_sdd1 + sdWorkInt[3] * 3 + sdWorkInt[6] + 10, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelReflectTypeSet(modelId, 2);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_NOCULL | HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    lbl_1_bss_195E[10] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 8), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    lbl_1_bss_195E[11] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 9), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0 | HU3D_CAM2);
    fn_1_22FB0(0);
    lbl_1_bss_195E[12] = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 20), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelScaleSet(modelId, 1.5f, 1.5f, 1.5f);
    for (i = 0; i < 3; i++) {
        modelId = lbl_1_bss_195E[i + 13] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 19), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 4.0f, 0.0f, 4.0f);
        Hu3DModelLayerSet(modelId, 1);
    }
    modelId = lbl_1_bss_195E[16] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 22), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    lbl_1_bss_1958[0] = Hu3DJointMotion(lbl_1_bss_195E[8], HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 18), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1958[1] = Hu3DJointMotion(lbl_1_bss_195E[8], HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 19), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1958[2] = Hu3DJointMotion(lbl_1_bss_195E[8], HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 20), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_195E[8], lbl_1_bss_1958[0]);
    Hu3DModelAttrSet(lbl_1_bss_195E[8], HU3D_MOTATTR_LOOP);
    lbl_1_bss_194C = grpId = HuSprGrpCreate(1);
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 31), HU_MEMNUM_OVL, HEAP_MODEL)), 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprAttrSet(grpId, 0, HUSPR_ATTR_DISPOFF);
    HuSprPriSet(grpId, 0, 100);
    HuDataDirClose(DATA_sdroom);
    HuDataDirClose(DATA_sdd1);
    for (i = 0; i < 2; i++) {
        fn_1_480C(&lbl_1_bss_18F4[i]);
        charNo = GwSdBattle.machine[i].charNo;
        if (charNo < 32) {
            fn_1_42E0(&lbl_1_bss_18F4[i], GwSdBattle.machine[i].partNo[0], GwSdBattle.machine[i].partNo[1], GwSdBattle.machine[i].partNo[3], charNo);
        } else {
            charNo -= 32;
            fn_1_42E0(&lbl_1_bss_18F4[i], lbl_1_data_1FBC[charNo][0], lbl_1_data_1FBC[charNo][1], lbl_1_data_1FBC[charNo][2], lbl_1_data_1FBC[charNo][3]);
        }
        fn_1_4534(&lbl_1_bss_18F4[i], (i * 400) - 200, 0.0f, 0.0f);
        fn_1_4638(&lbl_1_bss_18F4[i], HU3D_CAM0 | HU3D_CAM2);
        fn_1_46C4(&lbl_1_bss_18F4[i], 0);
        Hu3DModelAttrReset(lbl_1_bss_18F4[i].bodyMdl, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_18F4[i].bodyMdl, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    }
    HuDataDirClose(DATA_sd00);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 40.0f, 30.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 256.0f, 192.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM0, 0, 0, 256, 192);
    lbl_1_bss_18F0 = HuMemDirectMallocNum(HEAP_HEAP, GXGetTexBufferSize(256, 192, GX_TF_RGB5A3, GX_FALSE, 0), HU_MEMNUM_OVL);
    Hu3DLayerHookSet(9, fn_1_22C44);
    lbl_1_bss_18EC = anim = HuSprAnimMake(256, 192, 2);
    anim->bmp->data = lbl_1_bss_18F0;
    lbl_1_bss_18D4 = Hu3DAnimCreate(anim, lbl_1_bss_195E[0], "dummy");
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 28), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 2; i++) {
        lbl_1_bss_194E[i] = parManId = Hu3DParManCreate(anim, 200, &lbl_1_data_201C);
        Hu3DParManAttrSet(parManId, 0x69);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
        Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 1);
        Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), HU3D_CAM2);
    }
    lbl_1_bss_194E[4] = parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_20BC);
    Hu3DParManAttrSet(parManId, 0x61);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 1);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), HU3D_CAM2);
    Hu3DParManPosSet(lbl_1_bss_194E[4], 0.0f, 400.0f, -50.0f);
    Hu3DParManVecSet(lbl_1_bss_194E[4], 0.0f, -1.0f, 0.0f);
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 29), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 2; i < 4; i++) {
        lbl_1_bss_194E[i] = parManId = Hu3DParManCreate(anim, 40, &lbl_1_data_206C);
        Hu3DParManAttrSet(parManId, 0x23);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
        Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 1);
        Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), HU3D_CAM0 | HU3D_CAM2);
    }
    Hu3DGLightKill(lbl_1_bss_568[1]);
    lbl_1_bss_18DC = Hu3DGLightCreate(0.0f, 100.0f, 1000.0f, 0.0f, -0.1f, -1.0f, 128, 128, 128);
    Hu3DGLightInfinitytSet(lbl_1_bss_18DC);
    lbl_1_bss_18E4[0] = HuPrcChildCreate(fn_1_248F4, 1000, 0x3000, 0, HuPrcCurrentGet());
    lbl_1_bss_18D8 = 1;
    fn_1_25040();
}

/* 23 insns */
void fn_1_22C44(s16 layerNo)
{
    if (Hu3DCameraNo == 0) {
        Hu3DFbCopyExec(0, 0, 256, 192, GX_TF_RGB5A3, 0, lbl_1_bss_18F0);
        Hu3DZClear();
    }
}

/* 104 insns */
void fn_1_22CA0(void)
{
    HuVecF pos;
    pos.x = 0.0f;
    pos.y = -190.0f;
    pos.z = -3100.0f;
    while (1) {
        pos.x += HuPadStkX[1] / 5;
        if (HuPadBtn[1] & PAD_BUTTON_A) {
            pos.y += 1.0f;
        }
        if (HuPadBtn[1] & PAD_BUTTON_B) {
            pos.y -= 1.0f;
        }
        pos.z += HuPadStkY[1] / 5;
        fn_1_4534(&lbl_1_bss_18F4[0], pos.x, pos.y, pos.z);
        if (HuPadBtnDown[1] & PAD_BUTTON_X) {
            OSReport("%f,%f,%f\n", pos.x, pos.y, pos.z);
        }
        HuPrcVSleep();
    }
}

/* 42 insns */
float fn_1_22E40(float a0)
{
    float t;
    if (a0 < -2700.0f) {
        return -180.0f;
    }
    if (a0 > -765.0f) {
        return 0.0f;
    }
    t = 1.0 - (a0 - -2700.0f) / 1935.0f;
    return -180.0f * t;
}

/* 50 insns */
void fn_1_22EE8(s32 a0)
{
    s16 lightId;
    if (a0) {
        Hu3DModelAttrReset(lbl_1_bss_195E[10], HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(lbl_1_bss_195E[10], HU3D_ATTR_DISPOFF);
        lightId = Hu3DModelLightIdGet(lbl_1_bss_195E[10], "d1_p-inf_light3");
        Hu3DGLightColorSet(lightId, 0, 0, 0, 255);
        lightId = Hu3DModelLightIdGet(lbl_1_bss_195E[10], "d1_p-inf_light4");
        Hu3DGLightColorSet(lightId, 0, 0, 0, 255);
    }
}

/* 60 insns */
void fn_1_22FB0(s32 a0)
{
    if (a0) {
        Hu3DMotionTimeSet(lbl_1_bss_195E[1], Hu3DMotionTimeGet(lbl_1_bss_195E[11]));
        Hu3DModelAttrReset(lbl_1_bss_195E[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_195E[1], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(lbl_1_bss_195E[11], HU3D_ATTR_DISPOFF);
    } else {
        Hu3DMotionTimeSet(lbl_1_bss_195E[11], Hu3DMotionTimeGet(lbl_1_bss_195E[1]));
        Hu3DModelAttrReset(lbl_1_bss_195E[11], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_195E[11], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(lbl_1_bss_195E[1], HU3D_ATTR_DISPOFF);
    }
}

/* 120 insns */
void fn_1_230A0(void)
{
    s16 i;
    for (i = 0; i < 2; i++) {
        if (i & 1) {
            Hu3DParManPosSet(lbl_1_bss_194E[i], 670.0f, -175.0f, -2840.0f);
        } else {
            Hu3DParManPosSet(lbl_1_bss_194E[i], -670.0f, -175.0f, -2840.0f);
        }
        Hu3DParManTimeLimitSet(lbl_1_bss_194E[i], 120);
        Hu3DParManAttrReset(lbl_1_bss_194E[i], 1);
    }
    Hu3DParManVecSet(lbl_1_bss_194E[0], 0.8f, 1.0f, 0.0f);
    Hu3DParManVecSet(lbl_1_bss_194E[1], -0.8f, 1.0f, 0.0f);
    Hu3DParManVecSet(lbl_1_bss_194E[2], 0.8f, 1.0f, 0.0f);
    Hu3DParManVecSet(lbl_1_bss_194E[3], -0.8f, 1.0f, 0.0f);
}

/* 190 insns */
void fn_1_23280(void)
{
    s16 i;
    s16 loseF = 0;
    fn_1_21E04();
    fn_1_22EE8(0);
    fn_1_22FB0(0);
    Hu3DModelAttrSet(lbl_1_bss_195E[6], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_195E[0], HU3D_CAM2);
    fn_1_4638(&lbl_1_bss_18F4[0], HU3D_CAM2);
    fn_1_4638(&lbl_1_bss_18F4[1], HU3D_CAM2);
    lbl_1_bss_18E0 = HuPrcChildCreate(fn_1_245F0, 1000, 0x3000, 0, HuPrcCurrentGet());
    if (GwSdBattle.winnerNo == -1) {
        fn_1_23578();
        loseF = 1;
    }
    HuAudJinglePlay(0x47);
    fn_1_23ABC(loseF);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_C3C) {
        HuPrcKill(lbl_1_bss_C3C);
    }
    HuPrcKill(lbl_1_bss_18E4[0]);
    Hu3DLayerHookReset(9);
    if (lbl_1_bss_C38) {
        HuPrcKill(lbl_1_bss_C38);
    }
    for (i = 0; i < 17; i++) {
        Hu3DModelKill(lbl_1_bss_195E[i]);
    }
    for (i = 0; i < 3; i++) {
        Hu3DMotionKill(lbl_1_bss_1958[i]);
    }
    fn_1_4724(&lbl_1_bss_18F4[0]);
    fn_1_4724(&lbl_1_bss_18F4[1]);
    HuSprGrpKill(lbl_1_bss_194C);
    fn_1_2515C();
    HuPrcKill(lbl_1_bss_18E0);
}

/* 337 insns */
void fn_1_23578(void)
{
    char str2[8];
    char str1[8];
    HuVec2f size;
    s16 health[2];
    HUWINID winId;
    s16 winNo;
    HUWIN *winP;
    u32 mesNo;
    s32 charNo;
    s16 i;

    HuAudBGMPlay(0x25);
    omCameraViewSetMulti(1, &lbl_1_data_1F14);
    omCameraViewSetMulti(4, &lbl_1_data_1F30);
    for (i = 0; i < 2; i++) {
        fn_1_4534(&lbl_1_bss_18F4[i], (i * 600) - 300, 0.0f, 0.0f);
        fn_1_46C4(&lbl_1_bss_18F4[i], 1);
    }
    Hu3DModelPosSet(lbl_1_bss_195E[8], 0.0f, 200.0f, 0.0f);
    Hu3DModelAttrSet(lbl_1_bss_195E[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_195E[4], HU3D_ATTR_DISPOFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    HuPrcSleep(10);
    omCameraViewMoveMulti(4, &lbl_1_data_1F4C, 90, 2);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    health[0] = sdHealthLoss[0];
    health[1] = sdHealthLoss[1];
    if (health[0] == health[1]) {
        if (frandmod(0)) {
            health[0]++;
        } else {
            health[1]++;
        }
    }
    if (sdWorkInt[3] == 0) {
        health[0] = 50 - health[0];
        health[1] = 50 - health[1];
    } else {
        health[0] = health[0] + 50;
        health[1] = health[1] + 50;
    }
    if (health[0] > health[1]) {
        winNo = 0;
    } else {
        winNo = 1;
    }
    sprintf(str1, "%d", health[0]);
    sprintf(str2, "%d", health[1]);
    charNo = GwSdBattle.machine[winNo].charNo;
    mesNo = fn_1_24D20(charNo);
    HuWinInsertMesSizeGet(MESSNUM_PTR(str1), 0);
    HuWinInsertMesSizeGet(MESSNUM_PTR(str2), 1);
    HuWinInsertMesSizeGet(winNo + 0x1C000E, 2);
    HuWinInsertMesSizeGet(mesNo, 3);
    HuWinMesMaxSizeBetGet(&size, 0x1C0006, 0x1C0007);
    winId = HuWinExCreate(-10000.0f, 364.0f, size.x, size.y, -1);
    HuWinInsertMesSet(winId, MESSNUM_PTR(str1), 0);
    HuWinInsertMesSet(winId, MESSNUM_PTR(str2), 1);
    HuWinInsertMesSet(winId, winNo + 0x1C000E, 2);
    HuWinInsertMesSet(winId, mesNo, 3);
    HuWinExOpen(winId);
    fn_1_24758(60);
    HuWinMesSet(winId, 0x1C0006);
    HuAudFXPlay(0x2EF);
    HuWinMesWait(winId);
    fn_1_24758(60);
    HuWinMesSet(winId, 0x1C0007);
    winP = &winData[winId];
    while (winP->stat != 2) {
        HuPrcVSleep();
    }
    while (winP->stat != 1) {
        HuPrcVSleep();
    }
    HuAudFXPlay(0x2EE);
    HuWinMesWait(winId);
    GwSdBattle.winnerNo = winNo;
    Hu3DModelAttrReset(lbl_1_bss_195E[5], HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(lbl_1_bss_195E[5], 1.0f, 2.0f, 1.0f);
    Hu3DModelPosSet(lbl_1_bss_195E[5], (winNo * 600) - 300, 5.0f, 0.0f);
    if (winNo == 0) {
        HuAudFXPlay(0x51F);
    } else {
        HuAudFXPlay(0x520);
    }
    HuWinExClose(winId);
    HuWinKill(winId);
    HuPrcSleep(60);
    HuAudSStreamAllFadeOut(1000);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 717 insns */
void fn_1_23ABC(s32 a0)
{
    HUWINID winIdTbl[3];
    HuVec2f size;
    char str[8];
    HUWINID winId;
    s16 i;
    s16 winNo;
    s16 choice;
    s16 charNo;
    u32 mesNo;

    omCameraViewSetMulti(1, &lbl_1_data_1F68);
    if (a0) {
        omCameraViewSetMulti(4, &lbl_1_data_1FA0);
    } else {
        omCameraViewSetMulti(4, &lbl_1_data_1F84);
    }
    winNo = GwSdBattle.winnerNo;
    charNo = GwSdBattle.machine[winNo].charNo;
    fn_1_4534(&lbl_1_bss_18F4[winNo], 200.0f, 0.0f, 0.0f);
    fn_1_4590(&lbl_1_bss_18F4[winNo], 0.0f, -15.0f, 0.0f);
    fn_1_46C4(&lbl_1_bss_18F4[winNo], 1);
    fn_1_46C4(&lbl_1_bss_18F4[winNo ^ 1], 0);
    Hu3DModelPosSet(lbl_1_bss_195E[9], -200.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(lbl_1_bss_195E[9], 0.0f, 15.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_195E[9], 3.0f, 3.0f, 3.0f);
    Hu3DModelPosSet(lbl_1_bss_195E[8], 0.0f, 200.0f, 0.0f);
    Hu3DMotionSet(lbl_1_bss_195E[8], lbl_1_bss_1958[2]);
    Hu3DModelAttrSet(lbl_1_bss_195E[8], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_195E[5], HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(lbl_1_bss_195E[5], 1.5f, 2.0f, 1.5f);
    Hu3DModelPosSet(lbl_1_bss_195E[5], 0.0f, 5.0f, 0.0f);
    Hu3DModelAttrSet(lbl_1_bss_195E[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_195E[9], HU3D_ATTR_DISPOFF);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    if (a0 == 0) {
        HuPrcSleep(10);
        omCameraViewMoveMulti(4, &lbl_1_data_1FA0, 80, 2);
        while (WipeCheckEnd()) {
            HuPrcVSleep();
        }
    }
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    Hu3DModelAttrSet(lbl_1_bss_195E[3], HU3D_ATTR_DISPOFF);
    sprintf(str, "%d", GwSdCommon.picNo + 1);
    if (charNo < 32) {
        mesNo = MESSNUM_PTR(GwSdBattle.machine[winNo].name);
    } else {
        mesNo = charNo + 0x1D0000 - 0x13;
    }
    HuSprPosSet(lbl_1_bss_194C, 0, 288.0f, 380.0f);
    HuSprAttrReset(lbl_1_bss_194C, 0, HUSPR_ATTR_DISPOFF);
    for (i = 1; i <= 20; i++) {
        HuSprTPLvlSet(lbl_1_bss_194C, 0, i / 20.0);
        HuPrcVSleep();
    }
    winId = HuWinCreate(-10000.0f, 332.0f, 512, 42, 0);
    winIdTbl[0] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 50);
    HuWinInsertMesSet(winId, MESSNUM_PTR(str), 0);
    HuWinMesSet(winId, 0x1C0008);
    HuPrcSleep(5);
    winId = HuWinCreate(-10000.0f, 362.0f, 512, 42, 0);
    winIdTbl[1] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinPriSet(winId, 50);
    HuWinMesSpeedSet(winId, 0);
    HuWinInsertMesSet(winId, sdWorkInt[3] + 0x190035, 1);
    HuWinInsertMesSet(winId, sdWorkInt[6] + 0x190038, 2);
    HuWinMesSet(winId, 0x1C0009);
    HuPrcSleep(5);
    winId = HuWinCreate(-10000.0f, 392.0f, 512, 42, 0);
    winIdTbl[2] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 50);
    HuWinInsertMesSet(winId, mesNo, 3);
    HuWinMesSet(winId, 0x1C000A);
    lbl_1_bss_C3C = HuPrcChildCreate(fn_1_24D6C, 1000, 0x3000, 0, HuPrcCurrentGet());
    while (!(fn_1_4FD0(3) & PAD_BUTTON_A)) {
        HuPrcVSleep();
    }
    for (i = 0; i < 3; i++) {
        HuWinKill(winIdTbl[i]);
    }
    for (i = 1; i <= 10; i++) {
        HuSprTPLvlSet(lbl_1_bss_194C, 0, 1.0 - i / 10.0);
        HuPrcVSleep();
    }
    if (winNo == 0) {
        HuWinMesMaxSizeGet(2, &size, (u32)0x1C0010, (u32)0x1C0011);
        winId = HuWinExCreate(-10000.0f, 364.0f, size.x, size.y, -1);
        HuWinExOpen(winId);
        fn_1_24758(60);
        HuWinMesSet(winId, 0x1C0010);
        HuWinMesWait(winId);
        choice = HuWinChoiceGet(winId, -1);
        if (choice == 0) {
            for (i = 0; i < 10; i++) {
                if (GwSdCommon.picture[i].number == 0xFFFF) {
                    HuAudFXPlay(0x519);
                    GwSdCommon.picture[i].machine = GwSdBattle.machine[winNo];
                    GwSdCommon.picture[i].type = sdWorkInt[3];
                    GwSdCommon.picture[i].diff = sdWorkInt[6];
                    GwSdCommon.picture[i].number = GwSdCommon.picNo + 1;
                    break;
                }
            }
            if (i == 10) {
                HuWinMesSet(winId, 0x1C0011);
                fn_1_24758(60);
                HuWinMesWait(winId);
                choice = HuWinChoiceGet(winId, -1);
                if (choice == 0) {
                    GwSdCommon.picture[0].number = 0xFFFF;
                    fn_1_1C13C();
                    GwSdCommon.picture[9].machine = GwSdBattle.machine[winNo];
                    GwSdCommon.picture[9].type = sdWorkInt[3];
                    GwSdCommon.picture[9].diff = sdWorkInt[6];
                    GwSdCommon.picture[9].number = GwSdCommon.picNo + 1;
                    HuAudFXPlay(0x519);
                }
            }
        }
        HuWinExClose(winId);
        HuWinKill(winId);
    }
}

/* 0x2148 */ s16 lbl_1_data_2148[12] = { 10, 11, 1, 0, 2, 4, 8, 3, 6, 5, 7, 9 };

/* 90 insns */
void fn_1_245F0(void)
{
    s16 charNo;
    HU3DTEXANIM *texAnim;
    s16 i;

    charNo = GwSdBattle.machine[0].charNo;
    if (charNo >= 32) {
        charNo = lbl_1_data_2148[charNo - 32];
    }
    lbl_1_bss_18CC[0] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 32) + charNo, HU_MEMNUM_OVL, HEAP_MODEL));
    charNo = GwSdBattle.machine[1].charNo;
    if (charNo >= 32) {
        charNo = lbl_1_data_2148[charNo - 32];
    }
    lbl_1_bss_18CC[1] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdd1, 32) + charNo, HU_MEMNUM_OVL, HEAP_MODEL));
    texAnim = &Hu3DTexAnimData[lbl_1_bss_18D4];
    i = 0;
    while (1) {
        if (GwSdBattle.winnerNo == -1) {
            texAnim->anim = lbl_1_bss_18CC[i & 1];
        } else {
            texAnim->anim = lbl_1_bss_18CC[GwSdBattle.winnerNo & 1];
        }
        i++;
        HuPrcSleep(60);
    }
}

/* 38 insns */
void fn_1_24758(s16 a0)
{
    if (lbl_1_bss_C38) {
        HuPrcKill(lbl_1_bss_C38);
        lbl_1_bss_C38 = NULL;
    } else {
        lbl_1_bss_C38 = HuPrcChildCreate(fn_1_247F0, 1000, 0x3000, 0, HuPrcCurrentGet());
        lbl_1_bss_C38->property = (void *)(s32)a0;
    }
}

/* 65 insns */
void fn_1_247F0(void)
{
    HUPROCESS *process;
    s16 time;

    process = HuPrcCurrentGet();
    time = (u16)(s32)process->property;
    time -= 10;
    if (time < 0) {
        time = 10;
    }
    if (Hu3DMotionIDGet(lbl_1_bss_195E[8]) != lbl_1_bss_1958[1]) {
        Hu3DMotionShiftSet(lbl_1_bss_195E[8], lbl_1_bss_1958[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    }
    HuPrcSleep(time - 10);
    Hu3DMotionShiftSet(lbl_1_bss_195E[8], lbl_1_bss_1958[0], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
    lbl_1_bss_C38 = NULL;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 140 insns */
void fn_1_248F4(void)
{
    HU3DMODEL *modelP;
    float y;

    while (1) {
        modelP = &Hu3DData[8];
        Hu3DModelPosSet(lbl_1_bss_195E[12], modelP->pos.x, 5.0f, modelP->pos.z);
        modelP = &Hu3DData[lbl_1_bss_18F4[0].bodyMdl];
        if (!(modelP->attr & HU3D_ATTR_DISPOFF)) {
            if (lbl_1_bss_18D8) {
                y = 15.0f + (modelP->pos.y - lbl_1_bss_18F4[0].ofsY);
            } else {
                y = 15.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_195E[13], modelP->pos.x, y, modelP->pos.z);
            Hu3DModelRotSetV(lbl_1_bss_195E[13], &modelP->rot);
            Hu3DModelAttrReset(lbl_1_bss_195E[13], HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(lbl_1_bss_195E[13], HU3D_ATTR_DISPOFF);
        }
        modelP = &Hu3DData[lbl_1_bss_18F4[1].bodyMdl];
        if (!(modelP->attr & HU3D_ATTR_DISPOFF)) {
            if (lbl_1_bss_18D8) {
                y = 15.0f + (modelP->pos.y - lbl_1_bss_18F4[0].ofsY);
            } else {
                y = 15.0f;
            }
            Hu3DModelPosSet(lbl_1_bss_195E[14], modelP->pos.x, y, modelP->pos.z);
            Hu3DModelRotSetV(lbl_1_bss_195E[14], &modelP->rot);
            Hu3DModelAttrReset(lbl_1_bss_195E[14], HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(lbl_1_bss_195E[14], HU3D_ATTR_DISPOFF);
        }
        modelP = &Hu3DData[9];
        if (!(modelP->attr & HU3D_ATTR_DISPOFF)) {
            Hu3DModelPosSet(lbl_1_bss_195E[15], modelP->pos.x, 5.0f, modelP->pos.z);
        }
        HuPrcVSleep();
    }
}

/* 127 insns */
void fn_1_24B24(SDMACHINEMDL *machine, float a1)
{
    HU3DMODEL *modelP;
    HSFOBJECT *obj;
    s16 i;

    for (i = 0; i < 4; i++) {
        if (machine->tireMdl[i] == -1) {
            continue;
        }
        modelP = &Hu3DData[machine->tireMdl[i]];
        if (machine->partNo[1] == 2 || machine->partNo[1] == 5 || machine->partNo[1] == 6 || machine->partNo[1] == 7 || machine->partNo[1] == 9) {
            modelP->motWork.time += 2.0f * a1;
            if (modelP->motWork.time >= Hu3DMotionMaxTimeGet(machine->tireMdl[i])) {
                modelP->motWork.time = 0.0f;
            }
            Hu3DMotionCalc(lbl_1_bss_195E[machine->tireMdl[i]]);
        } else {
            if (i & 1) {
                obj = Hu3DModelObjPtrGet(machine->tireMdl[i], "chn_tr");
            } else {
                obj = Hu3DModelObjPtrGet(machine->tireMdl[i], "chn_tl");
            }
            obj->mesh.base.rot.x += 4.0f * a1;
            if (obj->mesh.base.rot.x > 360.0f) {
                obj->mesh.base.rot.x -= 360.0f;
            }
        }
    }
}

/* 19 insns */
u32 fn_1_24D20(s16 no)
{
    if (no < 32) {
        if (no > 9) {
            return 0x190060;
        }
        return no;
    }
    return lbl_1_data_1DAC[no - 32];
}

/* 21 insns */
void fn_1_24D6C(void)
{
    HuVecF pos;

    pos.x = 200.0f;
    pos.y = 500.0f;
    pos.z = 0.0f;
    while (1) {
        fn_1_25198(&pos, 1);
        fn_1_24F14();
        HuPrcVSleep();
    }
}

/* 0x216E */ GXColor lbl_1_data_216E[4] = { { 255, 64, 64, 255 }, { 255, 255, 0, 255 }, { 0, 128, 255, 255 }, { 64, 255, 64, 255 } };

/* 85 insns */
void fn_1_24DC0(HU3DMODEL *modelP, Mtx *mtx)
{
    HU3DMODEL *mdl;
    s32 i;
    HSFOBJECT *obj;
    HSFDATA *hsf;
    SDCONFETTI *piece;
    s32 j;
    HSFMATERIAL *material;
    Mtx m;

    Hu3DModelObjDrawInit();
    mdl = &Hu3DData[lbl_1_bss_C40.mdl];
    hsf = mdl->hsf;
    obj = Hu3DModelObjPtrGet(lbl_1_bss_C40.mdl, "m569_ef2");
    for (i = 0; i < 50; i++) {
        piece = &lbl_1_bss_C4C[i];
        if (piece->active) {
            mtxRot(m, piece->rot.x, piece->rot.y, piece->rot.z);
            mtxTransCat(m, piece->pos.x, piece->pos.y, piece->pos.z);
            mtxScaleCat(m, 1.5f, 1.5f, 1.5f);
            PSMTXConcat(*mtx, m, m);
            Hu3DModelObjPtrDraw(lbl_1_bss_C40.mdl, obj, m);
            for (j = 0, material = hsf->material; j < hsf->materialNum; j++, material++) {
                material->color[0] = piece->color.r;
                material->color[1] = piece->color.g;
                material->color[2] = piece->color.b;
            }
        }
    }
}

/* 75 insns */
void fn_1_24F14(void)
{
    s32 i;
    SDCONFETTI *piece;

    if (lbl_1_bss_C40.num != 0) {
        for (i = 0; i < 50; i++) {
            piece = &lbl_1_bss_C4C[i];
            if (!piece->active) {
                continue;
            }
            if (piece->landed) {
                piece->time++;
                if (piece->time > 3) {
                    piece->landed = piece->active = 0;
                    lbl_1_bss_C40.num--;
                }
            } else {
                PSVECAdd(&piece->pos, &piece->vel, &piece->pos);
                PSVECAdd(&piece->rot, &piece->rotVel, &piece->rot);
                if (piece->pos.y <= lbl_1_bss_C40.floorY) {
                    piece->pos.y = lbl_1_bss_C40.floorY;
                    piece->rot.x = -90.0f;
                    piece->rot.z = 0.0f;
                    piece->landed = 1;
                }
            }
        }
    }
}

/* 71 insns */
void fn_1_25040(void)
{
    s32 i;

    lbl_1_bss_C40.mdl = Hu3DModelCreateData(DATANUM(DATA_sdd1, 30));
    Hu3DModelCameraSet(lbl_1_bss_C40.mdl, 1);
    Hu3DModelAttrSet(lbl_1_bss_C40.mdl, HU3D_ATTR_DISPOFF);
    lbl_1_bss_C40.hook = Hu3DHookFuncCreate(fn_1_24DC0);
    Hu3DModelCameraSet(lbl_1_bss_C40.hook, 5);
    Hu3DModelLayerSet(lbl_1_bss_C40.hook, 1);
    lbl_1_bss_C40.floorY = 0.1f;
    lbl_1_bss_C40.num = 0;
    for (i = 0; i < 50; i++) {
        lbl_1_bss_C4C[i].active = 0;
        lbl_1_bss_C4C[i].landed = 0;
    }
}

/* 15 insns */
void fn_1_2515C(void)
{
    Hu3DModelKill(lbl_1_bss_C40.mdl);
    Hu3DModelKill(lbl_1_bss_C40.hook);
}

/* 327 insns */
void fn_1_25198(HuVecF *pos, s32 a1)
{
    s32 num;
    s32 i;
    SDCONFETTI *piece;
    float angleX;
    float speed;
    float angleY;

    for (num = 0, i = 0; i < 50; i++) {
        if (num == a1) {
            break;
        }
        piece = &lbl_1_bss_C4C[i];
        if (piece->active) {
            continue;
        }
        piece->active = 1;
        num++;
        lbl_1_bss_C40.num++;
        speed = frandmod(15000) / 100.0f;
        angleX = frandmod(360);
        angleY = frandmod(360);
        piece->pos.x = pos->x + speed * (sin(M_PI * angleY / 180.0) * cos(M_PI * angleX / 180.0));
        piece->pos.y = pos->y + speed * -sin(M_PI * angleX / 180.0);
        piece->pos.z = pos->z + speed * (cos(M_PI * angleY / 180.0) * cos(M_PI * angleX / 180.0));
        piece->vel.x = 0.8f * (((float)frandmod(201) - 100.0) / 100.0);
        piece->vel.y = -6.5f * (frandmod(100) / 100.0f);
        if (piece->vel.y > -2.6000001f) {
            piece->vel.y = -2.6000001f;
        }
        piece->vel.z = 0.5 * (((float)frandmod(201) - 100.0) / 100.0);
        piece->rot.x = piece->rot.y = piece->rot.z = 0.0f;
        piece->rotVel.x = 14.0 * (((float)frandmod(201) - 100.0) / 100.0);
        piece->rotVel.y = 14.0 * (((float)frandmod(201) - 100.0) / 100.0);
        piece->rotVel.z = 14.0 * (((float)frandmod(201) - 100.0) / 100.0);
        piece->color = lbl_1_data_216E[frandmod(4)];
        piece->time = 0;
    }
}

