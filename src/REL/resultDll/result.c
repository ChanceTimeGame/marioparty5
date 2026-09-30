/*
 * resultDll result.c -- minigame results after every ordinary board minigame: the
 * results screen, the payout (Result_AddBonusCoin, Battle pot split in Result_GetCoin),
 * coinTotalMg, the per-turn starStat/coinStat record and the per-turn board save
 * (Result_BoardSave). Decompiled from retail; functions are in reference order.
 *
 * How control arrives: mgcall.c goes to instdll, which rewrites its own history slot to
 * resultdll before calling the minigame, so the minigame's omOvlReturn lands here and
 * our omOvlReturnEx(1, 1) lands back on the board. See games/mp5/src/REL/resultdll/NOTES.md.
 */

#include "REL/resultDll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/saveload.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/board/player.h"
#include "math.h"

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif


/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
/* 0x10 lbl_1_rodata_10 (0x1): 0x14 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_14 = 20.0f; /* 0x14 */
static const float lbl_1_rodata_18 = 15000.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 1.2f; /* 0x1C */
static const float lbl_1_rodata_20 = 0.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 640.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 480.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 1.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 100.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 1000.0f; /* 0x34 */
static const float lbl_1_rodata_38 = -0.5f; /* 0x38 */
static const float lbl_1_rodata_3C = -1.0f; /* 0x3C */
static const float lbl_1_rodata_40 = -10000.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 400.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 360.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 0.5f; /* 0x4C */
static const float lbl_1_rodata_50 = -52.0f; /* 0x50 */
static const float lbl_1_rodata_54 = -26.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 26.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 30.0f; /* 0x5C */
static const float lbl_1_rodata_60 = -22.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 36.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 12.0f; /* 0x68 */
static const float lbl_1_rodata_6C = -25.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 28.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 44.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 60.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 0.37f; /* 0x7C */
/* 0x80 lbl_1_rodata_80 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_88 = 75.0f; /* 0x88 */
/* 0x8C lbl_1_rodata_8C (0x14): 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_A0 = 3.141592653589793; /* 0xA0 */
static const double lbl_1_rodata_A8 = 90.0; /* 0xA8 */
static const double lbl_1_rodata_B0 = 180.0; /* 0xB0 */
static const double lbl_1_rodata_B8 = 0.10000000149011612; /* 0xB8 */
static const float lbl_1_rodata_C0 = 8.571428f; /* 0xC0 */
static const double lbl_1_rodata_C8 = 0.8; /* 0xC8 */
static const double lbl_1_rodata_D0 = 1.0; /* 0xD0 */
static const double lbl_1_rodata_D8 = 2.0943951023931953; /* 0xD8 */
static const float lbl_1_rodata_E0 = 0.2f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 3.0f; /* 0xE4 */
/* 0xE8 lbl_1_rodata_E8 (0x10): 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
/* 0xF8 lbl_1_rodata_F8 (0x10): 0x00000078 0x0000005A 0x0000003C 0x0000001E -- an aggregate initialiser, write it as a local */
/* 0x108 lbl_1_rodata_108 (0x10): 0x00000001 0x00000001 0x00000001 0x00000001 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_118 = 0.0296f; /* 0x118 */
static const float lbl_1_rodata_11C = 0.0148f; /* 0x11C */
static const float lbl_1_rodata_120 = 4.0f; /* 0x120 */
static const float lbl_1_rodata_124 = 0.001f; /* 0x124 */
static const float lbl_1_rodata_128 = 8.0f; /* 0x128 */
/* 0x12C lbl_1_rodata_12C (0x2): 0xFFFF -- an aggregate initialiser, write it as a local */
/* 0x12E lbl_1_rodata_12E (0x2): 0xFFFF -- an aggregate initialiser, write it as a local */
/* 0x130 lbl_1_rodata_130 (0x2): 0x0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_134 = 0.7f; /* 0x134 */
static const float lbl_1_rodata_138 = 0.3f; /* 0x138 */
static const float lbl_1_rodata_13C = 0.6f; /* 0x13C */
static const float lbl_1_rodata_140 = 0.1f; /* 0x140 */
static const float lbl_1_rodata_144 = 0.25f; /* 0x144 */
/* 0x148 lbl_1_rodata_148 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x19C gap_05_0000019C_bss (0x4): alignment gap */
/* 0x198 */ static OMOBJ *outview;
/* 0x194 */ OMOBJMAN *objman;
/* 0x192 gap_05_00000192_bss (0x2): alignment gap */
/* 0x190 */ s16 Result_MgNo;
/* 0x18C */ BOOL Result_BgReadEndF;
/* 0x188 */ BOOL Result_FastF;
/* 0x186 gap_05_00000186_bss (0x2): alignment gap */
/* 0x184 */ s16 Result_RandomCoinPlayer;
/* 0x180 */ static ANIMDATA *RankAnimP;
/* 0xE4 */ u8 lbl_1_bss_E4[0x9C]; /* unreferenced (alignment 4) */
/* 0xE0 */ static ANIMDATA *CrownAnimP;
/* 0xDE gap_05_000000DE_bss (0x2): alignment gap */
/* 0xCE */ static HUSPRGRPID ScoreSprGrpId[8];
/* 0x8E */ static HUSPRID ScoreSprId[8][4];
/* 0x8C */ static HUSPRGRPID CrownSprGrpId;
/* 0x8A */ static HUSPRGRPID RankSprGrpId;
/* 0x82 */ static s16 PlayerOrder[4];
/* 0x7A */ static s16 PlayerRank[4];
/* 0x78 */ s16 lbl_1_bss_78; /* unreferenced */
/* 0x70 */ static HUSPRGRPID BonusSprGrpId[4];
/* 0x48 */ static HUSPRID BonusSprId[4][5];
/* 0x38 */ static float StarRotSpeed[4];
/* 0x28 */ static float CoinRotSpeed[4];
/* 0x20 */ static s16 Result_CharNo[4];
/* 0x18 */ static s16 PlayerRankStart[4];
/* 0x10 */ static s16 PlayerRankEnd[4];
/* 0x8 */ static s16 ToueiPlayerOrder[4];
/* 0x4 */ BOOL Result_AllComF;
/* 0x0 */ BOOL Result_ReqSort;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ static OMCAMERAVIEW ToueiCameraView = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1600.0f };
/* 0x1C */ static OMCAMERAVIEW MainCameraView = { { 0.0f, 200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1600.0f };
/* 0x38 */ static OMCAMERAVIEW FGCameraView = { { 0.0f, 200.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1600.0f };
/* 0x54 */ STAGE_MODEL Result_PartyModel[11] = {
    { DATANUM(DATA_result, 22), 0x40000001, 0, -1, -1, 1, 2, { 250.0f, 150.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 22), 0x40000001, 2, 0, -1, 1, 2, { 250.0f, 225.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 22), 0x40000001, 2, 0, -1, 1, 2, { 250.0f, 300.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 22), 0x40000001, 2, 0, -1, 1, 2, { 250.0f, 375.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 23), 0x40000001, 0, -1, -1, 1, 2, { 420.0f, 150.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 4, -1, 1, 2, { 420.0f, 225.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 4, -1, 1, 2, { 420.0f, 300.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 4, -1, 1, 2, { 420.0f, 375.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 24), 0x40000001, 0, -1, -1, 0, 2, { 288.0f, 240.0f, 2500.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
    { DATANUM(DATA_result, 31), 0x40000001, 0, -1, -1, 0, 1, { 300.0f, 800.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f, 2.0f } },
    { HU_DATANUM_NONE, 0x00000000, 0, -1, -1, -1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
};
/* 0x2BC */ STAGE_MODEL Result_StoryModel[7] = {
    { DATANUM(DATA_result, 23), 0x40000001, 0, -1, -1, 1, 2, { 340.0f, 150.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 0, -1, 1, 2, { 340.0f, 225.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 0, -1, 1, 2, { 340.0f, 300.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 0, -1, 1, 2, { 340.0f, 375.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 28), 0x40000001, 0, -1, -1, 0, 2, { 288.0f, 240.0f, 2500.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
    { DATANUM(DATA_result, 31), 0x40000001, 0, -1, -1, 0, 1, { 300.0f, 800.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f, 2.0f } },
    { HU_DATANUM_NONE, 0x00000000, 0, -1, -1, -1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
};
/* 0x444 */ STAGE_SPRITE Result_Sprite[6] = {
    { DATANUM(DATA_result, 6), 0, 60, 288.0f, 70.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 13), 0, 20, 288.0f, 150.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 13), 0, 20, 288.0f, 225.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 13), 0, 20, 288.0f, 300.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 13), 0, 20, 288.0f, 375.0f, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0.0f, 0.0f, { 0, 0, 0, 0 } },
};

/* 349 insns */
void ObjectSetup(void)
{
    s32 i;
    s32 lightId;
    GXColor unusedColor = { 20 };

    OSReport("******* RESULT ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    Result_MgNo = GwSystem.mgNo;
    for(i = 0; i < GW_PLAYER_MAX; i++) {
        GwPlayerConf[i].grp = GwPlayer[i].grp;
    }
    if(_CheckFlag(FLAG_MG_CIRCUIT)) {
        omOvlReturnEx(1, 1);
        return;
    }
    if(GWPartyFGet() == FALSE) {
        omOvlReturnEx(1, 1);
        return;
    }
    switch(mgDataTbl[GwSystem.mgNo].type) {
        case MG_TYPE_KUPA:
        case MG_TYPE_KETTOU:
        case MG_TYPE_DONKEY:
            omOvlReturnEx(1, 1);
            return;
    }
    if(Result_MgNo <= -1) {
        Result_MgNo = 0;
    }
    HuDataDirClose(mgDataTbl[Result_MgNo].dataDir);
    Hu3DCameraCreate(HU3D_CAM0|HU3D_CAM1|HU3D_CAM2);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 20, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM0, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(HU3D_CAM1, 20, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM1, 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(HU3D_CAM2, 20, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM2, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM2, 0, 0, 640, 480);
    omCameraViewSetMulti(HU3D_CAM0, &ToueiCameraView);
    omCameraViewSetMulti(HU3D_CAM1, &MainCameraView);
    omCameraViewSetMulti(HU3D_CAM2, &FGCameraView);
    outview = omAddObjEx(objman, 32730, 100, 50, -1, omOutViewMulti);
    outview->work[0] = 3;
    lightId = Hu3DGLightCreate(0, 100, 1000, 0, -0.5f, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Result_FastF = FALSE;
    if(mgDataTbl[GwSystem.mgNo].type != MG_TYPE_BATTLE) {
        if(GWTeamFGet()) {
            HuPrcChildCreate(Result_TeamMain, 100, 12288, 0, objman);
        } else {
            HuPrcChildCreate(Result_Main, 100, 12288, 0, objman);
        }
    } else {
        HuPrcChildCreate(Result_BattleMain, 100, 12288, 0, objman);
    }
    HuWinInit(1);
    Result_RandomCoinPlayer = frandmod(4);
}

/* 213 insns */
void Result_Main(void)
{
    s16 i;
    s16 comNum;
    HUWINID winId;
    BOOL doneF;
    HUPROCESS *process;

    doneF = FALSE;
    process = HuPrcCurrentGet();
    Result_Debug();
    for(i = comNum = 0; i < GW_PLAYER_MAX; i++) {
        if(GwPlayerConf[i].type != GW_TYPE_MAN) {
            comNum++;
        }
    }
    if(comNum == GW_PLAYER_MAX) {
        Result_AllComF = TRUE;
    } else {
        Result_AllComF = FALSE;
    }
    for(i = 0; i < GW_PLAYER_MAX; i++) {
        StarRotSpeed[i] = 1.0f;
        CoinRotSpeed[i] = 1.0f;
    }
    if(GWPartyFGet() == FALSE) {
        Result_StoryCreate();
    } else {
        Result_PartyCreate();
    }
    HuPrcChildCreate(Result_CoinMdlMain, 100, 8192, 0, objman);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    HuAudSStreamPlay(49);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATA_result);
    Result_BgReadEndF = FALSE;
    HuPrcChildCreate(Result_BgRead, 100, 12288, 0, objman);
    HuPrcSleep(10);
    if(!Result_FastF) {
        HuPrcSleep(20);
    }
    Result_CoinCount();
    Result_AddBonusCoin();
    Result_UpdateRank();
    winId = HuWinCreate(-10000, 400, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, 0x800);
    if(!Result_AllComF) {
        HuWinMesSet(winId, 0x2000D);
    }
    HuPrcSleep(4);
    while(1) {
        if(Result_AllComF) {
            doneF = TRUE;
        } else {
            for(i = 0; i < GW_PLAYER_MAX; i++) {
                if(HuPadStatGet(i) == 0 && (HuPadBtnDown[i] & PAD_BUTTON_A)) {
                    doneF = TRUE;
                    break;
                }
            }
        }
        if(doneF) {
            break;
        }
        HuPrcVSleep();
    }
    HuWinKill(winId);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    Result_BoardSave();
    ToueiDispClose();
    omSysPauseEnable(TRUE);
    HuDataDirClose(DATA_result);
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while(1) {
        HuPrcVSleep();
    }
}

/* 285 insns */
void Result_CoinMdlMain(void)
{
    s16 i;
    float coinRot[4];
    float starRot[4];
    float unused;

    unused = 0.0f;
    Result_ReqSort = FALSE;
    for(i = 0; i < GW_PLAYER_MAX; i++) {
        coinRot[i] = 0.0f;
        starRot[i] = 0.0f;
    }
    while(1) {
        if(Result_AllComF) {
            Result_FastF = TRUE;
        } else {
            for(i = 0; i < GW_PLAYER_MAX; i++) {
                if(HuPadStatGet(i) == 0) {
                    if(HuPadBtn[i] & PAD_BUTTON_A) {
                        Result_FastF = TRUE;
                    } else {
                        Result_FastF = FALSE;
                    }
                }
            }
        }
        for(i = 0; i < GW_PLAYER_MAX; i++) {
            coinRot[i] += 1.2f * CoinRotSpeed[i];
            if(coinRot[i] >= 360.0f) {
                coinRot[i] -= 360.0f;
            }
            starRot[i] += StarRotSpeed[i];
            if(starRot[i] >= 360.0f) {
                starRot[i] -= 360.0f;
            }
        }
        if(GWPartyFGet() == FALSE) {
            Hu3DModelRotSet(StageMdlId[0], 0, starRot[0], 0);
            Hu3DModelRotSet(StageMdlId[1], 0, starRot[1], 0);
            Hu3DModelRotSet(StageMdlId[2], 0, starRot[2], 0);
            Hu3DModelRotSet(StageMdlId[3], 0, starRot[3], 0);
        } else {
            Hu3DModelRotSet(StageMdlId[0], 0, coinRot[0], 0);
            Hu3DModelRotSet(StageMdlId[1], 0, coinRot[1], 0);
            Hu3DModelRotSet(StageMdlId[2], 0, coinRot[2], 0);
            Hu3DModelRotSet(StageMdlId[3], 0, coinRot[3], 0);
            Hu3DModelRotSet(StageMdlId[4], 0, starRot[0], 0);
            Hu3DModelRotSet(StageMdlId[5], 0, starRot[1], 0);
            Hu3DModelRotSet(StageMdlId[6], 0, starRot[2], 0);
            Hu3DModelRotSet(StageMdlId[7], 0, starRot[3], 0);
        }
        HuPrcVSleep();
    }
}

/* 0x4E4 */ static u32 MgTypeBackFileTbl[9] = { DATANUM(DATA_result, 24), DATANUM(DATA_result, 27), DATANUM(DATA_result, 25), DATANUM(DATA_result, 24), DATANUM(DATA_result, 28), DATANUM(DATA_result, 28), DATANUM(DATA_result, 26), DATANUM(DATA_result, 24), DATANUM(DATA_result, 24) };
/* 0x508 */ static s16 ScorePosTbl[8 * 2] = { 340, 150, 340, 225, 340, 300, 340, 375, 510, 150, 510, 225, 510, 300, 510, 375 };
/* 0x528 */ static s16 RankPosTbl[4 * 2] = { 60, 150, 60, 225, 60, 300, 60, 375 };
/* 0x538 */ static s16 CrownPosTbl[4 * 2] = { 134, 110, 134, 185, 134, 260, 134, 335 };
/* 0x548 */ static s16 BonusPosTbl[4 * 2] = { 170, 150, 170, 225, 170, 300, 170, 375 };
/* 0x558 */ static HuVecF ToueiPosTbl[4] = { { 133.0f, 150.0f, 1600.0f }, { 133.0f, 225.0f, 1600.0f }, { 133.0f, 300.0f, 1600.0f }, { 133.0f, 375.0f, 1600.0f } };
/* 0x588 */ static HuVecF ToueiCharPosTbl[4] = { { 240.0f, 250.0f, 1700.0f }, { 240.0f, 400.0f, 1700.0f }, { 320.0f, 250.0f, 1700.0f }, { 320.0f, 400.0f, 1700.0f } };
/* 0x5B8 */ static HuVecF ToueiCharScaleTbl[13] = { { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.6f, 0.6f, 0.6f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.5f, 0.5f, 0.5f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f } };

/* 1147 insns */
void Result_PartyCreate(void)
{
    s16 i;
    ANIMDATA *anim;
    s16 fileOfs;
    HUSPRID sprId;
    ANIMDATA *anim2;
    ANIMDATA *anim3;
    HuVecF pos;
    s16 coinNum[5];

    Result_PartyModel[8].dataNum = MgTypeBackFileTbl[mgDataTbl[Result_MgNo].type];
    StageSpriteCreate(Result_Sprite);
    StageModelCreate(Result_PartyModel);
    Hu3DMotionSpeedSet(StageMdlId[8], 0.5f);
    anim = HuSprAnimDataRead(DATANUM(DATA_result, 1));
    for(i = 0; i < 8; i++) {
        ScoreSprGrpId[i] = HuSprGrpCreate(4);
        ScoreSprId[i][0] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 0, ScoreSprId[i][0]);
        HuSprPosSet(ScoreSprGrpId[i], 0, -52, 0);
        ScoreSprId[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 1, ScoreSprId[i][1]);
        HuSprPosSet(ScoreSprGrpId[i], 1, -26, 0);
        ScoreSprId[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 2, ScoreSprId[i][2]);
        HuSprPosSet(ScoreSprGrpId[i], 2, 0, 0);
        ScoreSprId[i][3] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 3, ScoreSprId[i][3]);
        HuSprPosSet(ScoreSprGrpId[i], 3, 26, 0);
        HuSprGrpPosSet(ScoreSprGrpId[i], ScorePosTbl[i * 2], ScorePosTbl[(i * 2) + 1]);
        Result_SetScoreSprNum(ScoreSprGrpId[i], 0);
    }
    Result_SetupPlayer();
    Result_GetCoin(coinNum);
    anim = HuSprAnimDataRead(DATANUM(DATA_result, 3));
    anim2 = HuSprAnimDataRead(DATANUM(DATA_result, 7));
    anim3 = HuSprAnimDataRead(DATANUM(DATA_result, 8));
    for(i = 0; i < 4; i++) {
        BonusSprGrpId[i] = HuSprGrpCreate(5);
        if(coinNum[PlayerOrder[i]] < 100) {
            BonusSprId[i][0] = HuSprCreate(anim2, 10, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
            HuSprPosSet(BonusSprGrpId[i], 0, 30, -22);
        } else {
            BonusSprId[i][0] = HuSprCreate(anim3, 10, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
            HuSprPosSet(BonusSprGrpId[i], 0, 36, -22);
        }
        BonusSprId[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 1, BonusSprId[i][1]);
        HuSprPosSet(BonusSprGrpId[i], 1, 12, -25);
        HuSprBankSet(BonusSprGrpId[i], 1, 10);
        BonusSprId[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 2, BonusSprId[i][2]);
        HuSprPosSet(BonusSprGrpId[i], 2, 28, -25);
        BonusSprId[i][3] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 3, BonusSprId[i][3]);
        HuSprPosSet(BonusSprGrpId[i], 3, 44, -25);
        BonusSprId[i][4] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 4, BonusSprId[i][4]);
        HuSprPosSet(BonusSprGrpId[i], 4, 60, -25);
        HuSprGrpPosSet(BonusSprGrpId[i], BonusPosTbl[i * 2], BonusPosTbl[(i * 2) + 1]);
        HuSprGrpScaleSet(BonusSprGrpId[i], 0, 0);
    }
    CrownAnimP = HuSprAnimDataRead(DATANUM(DATA_result, 9));
    CrownSprGrpId = HuSprGrpCreate(4);
    for(i = 0; i < 4; i++) {
        sprId = HuSprCreate(CrownAnimP, i, 0);
        HuSprGrpMemberSet(CrownSprGrpId, i, sprId);
        HuSprScaleSet(CrownSprGrpId, i, 0, 0);
        HuSprPosSet(CrownSprGrpId, i, CrownPosTbl[i * 2], CrownPosTbl[(i * 2) + 1]);
        HuSprAttrSet(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
    }
    RankAnimP = HuSprAnimDataRead(DATANUM(DATA_result, 5));
    RankSprGrpId = HuSprGrpCreate(4);
    for(i = 0; i < 4; i++) {
        sprId = HuSprCreate(RankAnimP, i, 0);
        HuSprGrpMemberSet(RankSprGrpId, i, sprId);
        HuSprPosSet(RankSprGrpId, i, RankPosTbl[i * 2], RankPosTbl[(i * 2) + 1]);
    }
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            StageToueiMdlId[0] = Hu3DModelCreateData(DATANUM(DATA_result, 30));
        } else {
            StageToueiMdlId[i] = Hu3DModelLink(StageToueiMdlId[0]);
        }
        Hu3D2Dto3D(&ToueiPosTbl[i], HU3D_CAM1, &pos);
        Hu3DModelScaleSet(StageToueiMdlId[i], 0.37f, 0.37f, 0.37f);
        Hu3DModelLayerSet(StageToueiMdlId[i], 1);
        Hu3DModelPosSetV(StageToueiMdlId[i], &pos);
        Hu3DModelCameraSet(StageToueiMdlId[i], HU3D_CAM1);
        Result_CharNo[i] = GwPlayerConf[PlayerOrder[i]].charNo;
        ToueiPlayerOrder[PlayerOrder[i]] = i;
        fileOfs = Result_CharNo[i] * 4;
        StageCharMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 32) + fileOfs);
        StageCharMotId[i][0] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 33) + fileOfs);
        StageCharMotId[i][1] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 34) + fileOfs);
        StageCharMotId[i][2] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 35) + fileOfs);
        Hu3D2Dto3D(&ToueiCharPosTbl[i], HU3D_CAM0, &pos);
        Hu3DMotionSet(StageCharMdlId[i], StageCharMotId[i][0]);
        Hu3DModelScaleSet(StageCharMdlId[i], ToueiCharScaleTbl[Result_CharNo[i]].x, ToueiCharScaleTbl[Result_CharNo[i]].y, ToueiCharScaleTbl[Result_CharNo[i]].z);
        Hu3DModelLayerSet(StageCharMdlId[i], 0);
        Hu3DModelPosSetV(StageCharMdlId[i], &pos);
        Hu3DModelAttrSet(StageCharMdlId[i], 0x40000001);
        Hu3DModelCameraSet(StageCharMdlId[i], HU3D_CAM0);
    }
    ToueiDispInit(Result_CharNo);
    for(i = 0; i < 4; i++) {
        Result_SetScoreSprNum(ScoreSprGrpId[i], MBPlayerStarGet(PlayerOrder[i]));
        Result_SetScoreSprNum(ScoreSprGrpId[i + 4], MBPlayerCoinGet(PlayerOrder[i]));
        PlayerRankStart[i] = MBPlayerRankGet(i);
    }
    for(i = 0; i < 4; i++) {
        HuSprBankSet(RankSprGrpId, i, PlayerRankStart[PlayerOrder[i]]);
    }
}

/* 1164 insns */
void Result_StoryCreate(void)
{
    s16 i;
    ANIMDATA *anim;
    s16 fileOfs;
    HUSPRID sprId;
    ANIMDATA *anim2;
    ANIMDATA *anim3;
    HuVecF pos;
    HuVecF pos2D;
    s16 coinNum[5];

    for(i = 0; i < 4; i++) {
        Result_Sprite[i + 1].dataNum = DATANUM(DATA_result, 14);
    }

    Result_StoryModel[4].dataNum = MgTypeBackFileTbl[mgDataTbl[Result_MgNo].type];
    StageSpriteCreate(Result_Sprite);
    StageModelCreate(Result_StoryModel);
    Hu3DMotionSpeedSet(StageMdlId[4], 0.5f);
    anim = HuSprAnimDataRead(DATANUM(DATA_result, 1));
    for(i = 4; i < 8; i++) {
        ScoreSprGrpId[i] = HuSprGrpCreate(4);
        ScoreSprId[i][0] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 0, ScoreSprId[i][0]);
        HuSprPosSet(ScoreSprGrpId[i], 0, -52, 0);
        ScoreSprId[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 1, ScoreSprId[i][1]);
        HuSprPosSet(ScoreSprGrpId[i], 1, -26, 0);
        ScoreSprId[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 2, ScoreSprId[i][2]);
        HuSprPosSet(ScoreSprGrpId[i], 2, 0, 0);
        ScoreSprId[i][3] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(ScoreSprGrpId[i], 3, ScoreSprId[i][3]);
        HuSprPosSet(ScoreSprGrpId[i], 3, 26, 0);
        HuSprGrpPosSet(ScoreSprGrpId[i], ScorePosTbl[i * 2] - 75, ScorePosTbl[(i * 2) + 1]);
        Result_SetScoreSprNum(ScoreSprGrpId[i], 0);
    }
    Result_SetupPlayer();
    Result_GetCoin(coinNum);
    anim = HuSprAnimDataRead(DATANUM(DATA_result, 3));
    anim2 = HuSprAnimDataRead(DATANUM(DATA_result, 7));
    anim3 = HuSprAnimDataRead(DATANUM(DATA_result, 8));
    for(i = 0; i < 4; i++) {
        BonusSprGrpId[i] = HuSprGrpCreate(5);
        if(coinNum[PlayerOrder[i]] < 100) {
            BonusSprId[i][0] = HuSprCreate(anim2, 10, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
            HuSprPosSet(BonusSprGrpId[i], 0, 30, -22);
        } else {
            BonusSprId[i][0] = HuSprCreate(anim3, 10, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
            HuSprPosSet(BonusSprGrpId[i], 0, 36, -22);
        }
        BonusSprId[i][1] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 1, BonusSprId[i][1]);
        HuSprPosSet(BonusSprGrpId[i], 1, 12, -25);
        BonusSprId[i][2] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 2, BonusSprId[i][2]);
        HuSprPosSet(BonusSprGrpId[i], 2, 28, -25);
        BonusSprId[i][3] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 3, BonusSprId[i][3]);
        HuSprPosSet(BonusSprGrpId[i], 3, 44, -25);
        BonusSprId[i][4] = HuSprCreate(anim, 0, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 4, BonusSprId[i][4]);
        HuSprPosSet(BonusSprGrpId[i], 4, 60, -25);
        HuSprGrpPosSet(BonusSprGrpId[i], BonusPosTbl[i * 2] + 75, BonusPosTbl[(i * 2) + 1]);
        HuSprGrpScaleSet(BonusSprGrpId[i], 0, 0);
    }
    CrownAnimP = HuSprAnimDataRead(DATANUM(DATA_result, 9));
    CrownSprGrpId = HuSprGrpCreate(4);
    for(i = 0; i < 4; i++) {
        sprId = HuSprCreate(CrownAnimP, i, 0);
        HuSprGrpMemberSet(CrownSprGrpId, i, sprId);
        HuSprScaleSet(CrownSprGrpId, i, 0, 0);
        HuSprPosSet(CrownSprGrpId, i, CrownPosTbl[i * 2] + 75, CrownPosTbl[(i * 2) + 1]);
        HuSprAttrSet(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
    }
    RankAnimP = HuSprAnimDataRead(DATANUM(DATA_result, 5));
    RankSprGrpId = HuSprGrpCreate(4);
    for(i = 0; i < 4; i++) {
        sprId = HuSprCreate(RankAnimP, i, 0);
        HuSprGrpMemberSet(RankSprGrpId, i, sprId);
        HuSprPosSet(RankSprGrpId, i, RankPosTbl[i * 2] + 70, RankPosTbl[(i * 2) + 1]);
    }
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            StageToueiMdlId[0] = Hu3DModelCreateData(DATANUM(DATA_result, 30));
        } else {
            StageToueiMdlId[i] = Hu3DModelLink(StageToueiMdlId[0]);
        }
        pos2D.x = ToueiPosTbl[i].x + 75;
        pos2D.y = ToueiPosTbl[i].y;
        pos2D.z = ToueiPosTbl[i].z;
        Hu3D2Dto3D(&pos2D, HU3D_CAM1, &pos);
        Hu3DModelScaleSet(StageToueiMdlId[i], 0.37f, 0.37f, 0.37f);
        Hu3DModelLayerSet(StageToueiMdlId[i], 1);
        Hu3DModelPosSetV(StageToueiMdlId[i], &pos);
        Hu3DModelCameraSet(StageToueiMdlId[i], HU3D_CAM1);
        Result_CharNo[i] = GwPlayerConf[PlayerOrder[i]].charNo;
        ToueiPlayerOrder[PlayerOrder[i]] = i;
        fileOfs = Result_CharNo[i] * 4;
        StageCharMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 32) + fileOfs);
        StageCharMotId[i][0] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 33) + fileOfs);
        StageCharMotId[i][1] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 34) + fileOfs);
        StageCharMotId[i][2] = Hu3DJointMotionData(StageCharMdlId[i], DATANUM(DATA_result, 35) + fileOfs);
        Hu3D2Dto3D(&ToueiCharPosTbl[i], HU3D_CAM0, &pos);
        Hu3DMotionSet(StageCharMdlId[i], StageCharMotId[i][0]);
        Hu3DModelScaleSet(StageCharMdlId[i], ToueiCharScaleTbl[Result_CharNo[i]].x, ToueiCharScaleTbl[Result_CharNo[i]].y, ToueiCharScaleTbl[Result_CharNo[i]].z);
        Hu3DModelLayerSet(StageCharMdlId[i], 0);
        Hu3DModelPosSetV(StageCharMdlId[i], &pos);
        Hu3DModelAttrSet(StageCharMdlId[i], 0x40000001);
        Hu3DModelCameraSet(StageCharMdlId[i], HU3D_CAM0);
    }
    ToueiDispInit(Result_CharNo);
    for(i = 0; i < 4; i++) {
        Result_SetScoreSprNum(ScoreSprGrpId[i + 4], MBPlayerCoinGet(PlayerOrder[i]));
        PlayerRankStart[i] = MBPlayerRankGet(i);
    }
    for(i = 0; i < 4; i++) {
        HuSprBankSet(RankSprGrpId, i, PlayerRankStart[PlayerOrder[i]]);
    }
}

/* GwPlayer.coinBattle read through an inline accessor (retail: the lha lands in a
 * callee-saved temp and is re-extended at the use, the GWMgCoinGet pattern). gamework.h
 * has no accessor for this field. */
static inline s16 GWCoinBattleGet(s32 playerNo)
{
    return GwPlayer[playerNo].coinBattle;
}

/* 633 insns */
void Result_CoinCount(void)
{
    s16 seNum = 0;
    s32 doneF[4] = { 0, 0, 0, 0 };
    float coinRot[4];
    s16 coinNum[5];
    float scale;
    float addTime;
    float speed;
    s16 i;
    s16 j;
    s16 time;
    s16 maxTime;
    s16 crownTime;

    Result_GetCoin(coinNum);
    for (i = 0; i < 4; i++) {
        Result_SetBonusSprNum(BonusSprGrpId[i], coinNum[PlayerOrder[i]]);
        if (coinNum[PlayerOrder[i]] != 0) {
            doneF[i] = 1;
        }
        coinRot[i] = 0.0f;
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for (time = 0; time <= maxTime; time++) {
        scale = HuSin((90.0 / maxTime) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        HuSprGrpScaleSet(BonusSprGrpId[i], 1.0f, 1.0f);
    }
    for (crownTime = 0; crownTime <= 14;) {
        for (i = 0; i < 4; i++) {
            if (GWMgCoinBonusGet(PlayerOrder[i]) >= 10) {
                HuSprAttrReset(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
            }
            HuSprScaleSet(CrownSprGrpId, i, 0.1f + HuSin((120.0f / 14.0f) * crownTime) * (0.8 * (1.0 / sin((M_PI * 2) / 3))),
                0.1f + 0.8 * (HuSin((120.0f / 14.0f) * crownTime) * (1.0 / sin((M_PI * 2) / 3))));
        }
        crownTime += (Result_FastF) ? 2 : 1;
        HuPrcVSleep();
    }
    if (!Result_FastF) {
        HuPrcSleep(15);
    }
    for (i = time = 0; i < 4; i++) {
        time += coinNum[i];
    }
    time = 0;
    speed = time;
    addTime = speed;
    time = 0;
    while (1) {
        addTime += (Result_FastF) ? 1.0f : 0.2f;
        speed = (Result_FastF) ? 1.0f : 0.2f;
        time = addTime;
        for (i = maxTime = 0; i < 4; i++) {
            coinRot[i] += speed;
            if (coinNum[PlayerOrder[i]] - time < 0) {
                StarRotSpeed[i] = 1.0f;
                doneF[i] = 0;
                maxTime++;
                Result_SetBonusSprNum(BonusSprGrpId[i], 0);
                Result_SetScoreSprNum(ScoreSprGrpId[i + 4], coinNum[PlayerOrder[i]] + MBPlayerCoinGet(PlayerOrder[i]));
            } else {
                if (doneF[i] && coinRot[i] >= 1.0f) {
                    HuAudFXPlay(7);
                    coinRot[i] = 0.0f;
                    seNum++;
                }
                Result_SetBonusSprNum(BonusSprGrpId[i], coinNum[PlayerOrder[i]] - time);
                Result_SetScoreSprNum(ScoreSprGrpId[i + 4], time + MBPlayerCoinGet(PlayerOrder[i]));
                StarRotSpeed[i] = 3.0f;
            }
        }
        if (maxTime == 4) {
            break;
        }
        HuPrcVSleep();
    }
    if (maxTime < 30) {
        HuPrcSleep(30 - maxTime);
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for (time = 0; time <= maxTime; time++) {
        scale = HuCos((90.0 / maxTime) * time);
        for (i = 0; i < 4; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
            HuSprScaleSet(CrownSprGrpId, i, scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 5; j++) {
            HuSprAttrSet(BonusSprGrpId[i], j, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrSet(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
    }
}

/* 739 insns */
void Result_UpdateRank(void)
{
    float scale[4];
    HuVecF pos;
    HuVecF pos2D;
    s32 digit[3];
    s32 seNo[4] = { -1, -1, -1, -1 };
    s32 delay[4] = { 120, 90, 60, 30 };
    s32 shrinkF[4] = { 1, 1, 1, 1 };
    s32 sameF[4];
    s32 motF[4];
    s16 toueiMdlId[4];
    s16 doneF[4];
    s16 order[4];
    s16 coin[4];
    float speed;
    s16 i;
    s16 j;
    s16 doneNum;
    s16 time;
    s16 step;
    s16 startF;
    s32 rankF;
    s32 num;

    rankF = 0;
    for (i = 0; i < 4; i++) {
        PlayerRankEnd[i] = MBPlayerRankGet(i);
        order[i] = PlayerOrder[i];
        coin[i] = MBPlayerCoinGet(PlayerOrder[i]);
        scale[i] = 0.37f;
        toueiMdlId[i] = StageToueiMdlId[i];
        doneF[i] = 0;
        motF[i] = 0;
    }
    Result_SetupPlayer();
    for (i = 0; i < 4; i++) {
        if (order[i] == PlayerOrder[i]) {
            sameF[i] = 1;
        } else {
            sameF[i] = 0;
        }
    }
    /* retail: i is always 4 here, so this early exit is dead */
    if (i == -1) {
        Result_ReqSort = 1;
        return;
    }
    doneNum = 0;
    startF = 0;
    time = 0;
    while (1) {
        speed = (Result_FastF) ? 0.0296f : 0.0148f;
        step = (Result_FastF) ? 2 : 1;
        if (Result_FastF) {
            time += 3;
        } else {
            time += 1;
        }
        for (i = 3; i > -1; i--) {
            if (startF == 0) {
                startF = 1;
            }
            if (!sameF[i]) {
                if (time % 2) {
                    for (j = 0; j < 3; j++) {
                        digit[j] = frandmod(10);
                        if (digit[j] == 0) {
                            digit[j] = frandmod(9) + 1;
                        }
                    }
                    num = digit[0] * 100 + digit[1] * 10 + digit[2];
                    if (GWPartyFGet() != FALSE) {
                        Result_SetScoreSprNum(ScoreSprGrpId[i], num);
                    }
                    Result_SetScoreSprNum(ScoreSprGrpId[i + 4], num);
                    StarRotSpeed[i] = 4.0f;
                    CoinRotSpeed[i] = 4.0f;
                }
                if (shrinkF[i]) {
                    if ((scale[i] -= speed) <= 0.0f) {
                        scale[i] = 0.001f;
                        StageToueiMdlId[i] = toueiMdlId[ToueiPlayerOrder[PlayerOrder[i]]];
                        if (GWPartyFGet() == FALSE) {
                            pos2D.x = 75.0f + ToueiPosTbl[i].x;
                            pos2D.y = ToueiPosTbl[i].y;
                            pos2D.z = ToueiPosTbl[i].z;
                            Hu3D2Dto3D(&pos2D, HU3D_CAM1, &pos);
                        } else {
                            Hu3D2Dto3D(&ToueiPosTbl[i], HU3D_CAM1, &pos);
                        }
                        Hu3DModelScaleSet(StageToueiMdlId[i], scale[i], scale[i], scale[i]);
                        Hu3DModelPosSetV(StageToueiMdlId[i], &pos);
                        shrinkF[i] = 0;
                    }
                } else if ((delay[i] -= step) <= 0) {
                    if ((scale[i] += speed) >= 0.37f) {
                        /* retail: a comparison where an assignment was meant; the scale is
                         * left just above 0.37 */
                        0.37f == scale[i];
                        if (GWPartyFGet() != FALSE) {
                            Result_SetScoreSprNum(ScoreSprGrpId[i], MBPlayerStarGet(PlayerOrder[i]));
                        }
                        Result_SetScoreSprNum(ScoreSprGrpId[i + 4], MBPlayerCoinGet(PlayerOrder[i]));
                        StarRotSpeed[i] = 1.0f;
                        CoinRotSpeed[i] = 1.0f;
                        sameF[i] = 1;
                    }
                }
                Hu3DModelScaleSet(StageToueiMdlId[i], scale[i], scale[i], scale[i]);
            } else {
                doneF[i] = 1;
            }
        }
        i = 0;
        doneNum = 0;
        for (; i < 4; i++) {
            doneNum += doneF[i];
        }
        if (doneNum >= 4 && rankF == 0) {
            for (i = 0; i < 4; i++) {
                if (PlayerRankStart[i] > PlayerRankEnd[i]) {
                    Hu3DMotionShiftSet(StageCharMdlId[ToueiPlayerOrder[i]], StageCharMotId[ToueiPlayerOrder[i]][1], 0.0f, 8.0f, 0);
                    PlayerFXPlay(i, 0x1F8);
                    motF[ToueiPlayerOrder[i]] = 1;
                } else if (PlayerRankStart[i] < PlayerRankEnd[i]) {
                    Hu3DMotionShiftSet(StageCharMdlId[ToueiPlayerOrder[i]], StageCharMotId[ToueiPlayerOrder[i]][2], 0.0f, 8.0f, 0);
                    motF[ToueiPlayerOrder[i]] = 1;
                }
                HuSprBankSet(RankSprGrpId, i, PlayerRankEnd[PlayerOrder[i]]);
            }
            rankF = 1;
        }
        for (i = doneNum = 0; i < 4; i++) {
            if (rankF && motF[i] && Result_CharMotEnd(i)) {
                Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                motF[i] = 0;
            }
            doneNum += motF[i];
        }
        if (rankF && doneNum <= 0) {
            break;
        }
        HuPrcVSleep();
    }
    Result_ReqSort = 1;
}

/* 96 insns */
void Result_SetScoreSprNum(HUSPRGRPID grpId, s16 num)
{
    s16 no;
    s16 bank;

    if (num > 999) {
        num = 999;
    }
    no = 0;
    HuSprBankSet(grpId, no, 10);
    HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
    no++;
    bank = num / 100;
    if (bank != 0) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
        no++;
    }
    num -= bank * 100;
    bank = num / 10;
    if (bank != 0 || no == 2) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
        no++;
    }
    num -= bank * 10;
    HuSprBankSet(grpId, no, num);
    HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
    no++;
    for (bank = no; bank < 4; bank++) {
        HuSprAttrSet(grpId, bank, HUSPR_ATTR_DISPOFF);
    }
}

/* 96 insns */
void Result_SetBonusSprNum(HUSPRGRPID grpId, s16 num)
{
    s16 no;
    s16 bank;

    if (num > 999) {
        num = 999;
    }
    no = 1;
    HuSprBankSet(grpId, no, 10);
    HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
    no++;
    bank = num / 100;
    if (bank != 0) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
        no++;
    }
    num -= bank * 100;
    bank = num / 10;
    if (bank != 0 || no == 3) {
        HuSprBankSet(grpId, no, bank);
        HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
        no++;
    }
    num -= bank * 10;
    HuSprBankSet(grpId, no, num);
    HuSprAttrReset(grpId, no, HUSPR_ATTR_DISPOFF);
    no++;
    for (bank = no; bank < 5; bank++) {
        HuSprAttrSet(grpId, bank, HUSPR_ATTR_DISPOFF);
    }
}

/* 116 insns */
void Result_SetupPlayer(void)
{
    s16 i;
    s16 j;

    for (i = 0; i < 4; i++) {
        PlayerRank[i] = MBPlayerRankGet(i);
        PlayerOrder[i] = i;
    }
    for (j = 1; j < 4; j++) {
        for (i = 0; i < 4 - j; i++) {
            if (PlayerRank[i] > PlayerRank[i + 1]) {
                s16 temp = PlayerRank[i];
                PlayerRank[i] = PlayerRank[i + 1];
                PlayerRank[i + 1] = temp;
                temp = PlayerOrder[i];
                PlayerOrder[i] = PlayerOrder[i + 1];
                PlayerOrder[i + 1] = temp;
            }
        }
    }
}

/* 0x654 */ static u32 MBDataDir[3] = { DATA_w01, DATA_w02, DATA_w03 };

/* 41 insns */
void Result_BgRead(void)
{
    s32 statId;

    if (!_CheckFlag(FLAG_BOARD_SAVEINIT)) {
        Result_BgReadEndF = TRUE;
        HuPrcEnd();
        while (1) {
            HuPrcVSleep();
        }
    }
    statId = HuDataDirReadAsync(MBDataDir[GwSystem.boardNo]);
    if (statId != -1) {
        while (!HuDataGetAsyncStat(statId)) {
            HuPrcVSleep();
        }
    }
    Result_BgReadEndF = TRUE;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 582 insns */
void Result_AddBonusCoin(void)
{
    s16 coinNum[5];
    s16 rank[4];
    s16 sortRank[4];
    s16 order[4];
    s16 coin = 0;
    s16 teamPlayer[2] = { -1, -1 };
    s16 teamCoin[2] = { 0, 0 };
    s16 i;
    s16 j;
    s16 k;
    s16 count;
    s16 temp;
    s16 randomPlayer;

    for (i = 0; i < 5; i++) {
        coinNum[i] = 0;
    }
    if (mgDataTbl[GwSystem.mgNo].type == 3) {
        for (i = 0; i < 4; i++) {
            for (j = count = 0; j < 4; j++) {
                if (i != j && GWMgCoinBonusGet(i) > GWMgCoinBonusGet(j)) {
                    count++;
                }
            }
            sortRank[i] = rank[i] = count;
            order[i] = i;
        }
        for (k = 1; k < 4; k++) {
            for (i = 0; i < 4 - k; i++) {
                if (sortRank[i] > sortRank[i + 1]) {
                    temp = sortRank[i];
                    sortRank[i] = sortRank[i + 1];
                    sortRank[i + 1] = temp;
                    temp = order[i];
                    order[i] = order[i + 1];
                    order[i + 1] = temp;
                }
            }
        }
        for (i = 0; i < 4; i++) {
            if (Result_RandomCoinPlayer == i) {
                randomPlayer = order[i];
            }
        }
        Result_GetCoin(coinNum);
        if (GWTeamFGet()) {
            for (i = 0; i < 4; i++) {
                coin = coinNum[rank[i]];
                if (randomPlayer == i) {
                    coin += coinNum[4];
                }
                teamCoin[GwPlayer[i].grp] += coin;
            }
            for (i = 0; i < 2; i++) {
                if (teamPlayer[i] == -1) {
                    for (j = 0; j < 4; j++) {
                        if (i == GwPlayer[j].grp) {
                            teamPlayer[i] = j;
                            break;
                        }
                    }
                }
            }
            for (i = 0; i < 2; i++) {
                GWPlayerCoinAdd(teamPlayer[i], teamCoin[i]);
                GwPlayer[teamPlayer[i]].coinTotalMg += teamCoin[i];
                if (GwPlayer[teamPlayer[i]].coinTotalMg > 9999) {
                    GwPlayer[teamPlayer[i]].coinTotalMg = 9999;
                }
            }
            for (i = 0; i < 4; i++) {
                GWMgCoinBonusSet(i, 0);
                GWMgCoinSet(i, 0);
            }
        } else {
            for (i = 0; i < 4; i++) {
                coin = coinNum[rank[i]];
                if (randomPlayer == i) {
                    coin += coinNum[4];
                }
                GWPlayerCoinAdd(i, coin);
                GWMgCoinBonusSet(i, 0);
                GWMgCoinSet(i, 0);
                GwPlayer[i].coinTotalMg += coin;
                if (GwPlayer[i].coinTotalMg > 9999) {
                    GwPlayer[i].coinTotalMg = 9999;
                }
            }
        }
    } else {
        Result_GetCoin(coinNum);
        if (GWTeamFGet()) {
            for (i = 0; i < 4; i++) {
                teamCoin[GwPlayer[i].grp] += coinNum[i];
            }
            for (i = 0; i < 2; i++) {
                if (teamPlayer[i] == -1) {
                    for (j = 0; j < 4; j++) {
                        if (i == GwPlayer[j].grp) {
                            teamPlayer[i] = j;
                            break;
                        }
                    }
                }
            }
            for (i = 0; i < 2; i++) {
                GWPlayerCoinAdd(teamPlayer[i], teamCoin[i]);
                GwPlayer[teamPlayer[i]].coinTotalMg += teamCoin[i];
                if (GwPlayer[teamPlayer[i]].coinTotalMg > 9999) {
                    GwPlayer[teamPlayer[i]].coinTotalMg = 9999;
                }
            }
            for (i = 0; i < 4; i++) {
                GWMgCoinBonusSet(i, 0);
                GWMgCoinSet(i, 0);
            }
        } else {
            for (i = 0; i < 4; i++) {
                GWPlayerCoinAdd(i, coinNum[i]);
                GWMgCoinBonusSet(i, 0);
                GWMgCoinSet(i, 0);
                GwPlayer[i].coinTotalMg += coinNum[i];
                if (GwPlayer[i].coinTotalMg > 9999) {
                    GwPlayer[i].coinTotalMg = 9999;
                }
            }
        }
    }
}

/* 390 insns */
void Result_GetCoin(s16 *coinNum)
{
    float scale[4];
    s16 coinBonus[4];
    s16 rank[4];
    s16 i;
    s16 j;
    s16 temp;
    s16 mgType;
    u32 coinBattle;
    u32 coin;
    u32 coinMul;

    mgType = mgDataTbl[GwSystem.mgNo].type;
    switch (mgType) {
        case 3:
            for (i = coinBattle = 0; i < 4; i++) {
                coinBattle += GWCoinBattleGet(i);
            }
            coinBonus[0] = coinBonus[1] = coinBonus[2] = coinBonus[3] = 0;
            rank[0] = rank[1] = rank[2] = rank[3] = 0;
            for (i = 0; i < 4; i++) {
                coinBonus[i] = GWMgCoinBonusGet(i);
            }
            for (i = 0; i < 4; i++) {
                for (j = i + 1; j < 4; j++) {
                    if (coinBonus[i] > coinBonus[j]) {
                        temp = coinBonus[i];
                        coinBonus[i] = coinBonus[j];
                        coinBonus[j] = temp;
                    }
                }
            }
            rank[0] = 0;
            temp = 0;
            for (i = 1; i < 4; i++) {
                if (coinBonus[i] != coinBonus[i - 1]) {
                    temp++;
                }
                rank[i] = temp;
            }
            scale[0] = scale[1] = scale[2] = scale[3] = 0.0f;
            if (rank[0] == 0 && rank[1] == 1 && rank[2] == 2 && rank[3] == 3) {
                scale[0] = 0.7f;
                scale[1] = 0.3f;
            } else if (rank[0] == 0 && rank[1] == 0 && rank[2] == 1 && rank[3] == 2) {
                scale[0] = 0.5f;
                scale[1] = 0.5f;
            } else if (rank[0] == 0 && rank[1] == 0 && rank[2] == 1 && rank[3] == 1) {
                scale[0] = 0.5f;
                scale[1] = 0.5f;
            } else if (rank[0] == 0 && rank[1] == 0 && rank[2] == 0 && rank[3] == 1) {
                scale[0] = 0.3f;
                scale[1] = 0.3f;
                scale[2] = 0.3f;
            } else if (rank[0] == 0 && rank[1] == 1 && rank[2] == 1 && rank[3] == 2) {
                scale[0] = 0.6f;
                scale[1] = 0.2f;
                scale[2] = 0.2f;
            } else if (rank[0] == 0 && rank[1] == 1 && rank[2] == 1 && rank[3] == 1) {
                scale[0] = 0.7f;
                scale[1] = 0.1f;
                scale[2] = 0.1f;
                scale[3] = 0.1f;
            } else if (rank[0] == 0 && rank[1] == 1 && rank[2] == 2 && rank[3] == 2) {
                scale[0] = 0.7f;
                scale[1] = 0.3f;
            } else if (rank[0] == 0 && rank[1] == 0 && rank[2] == 0 && rank[3] == 0) {
                scale[0] = 0.25f;
                scale[1] = 0.25f;
                scale[2] = 0.25f;
                scale[3] = 0.25f;
            }
            for (i = coin = 0; i < 4; i++) {
                coinMul = coinBattle * scale[i];
                coinNum[i] = coinMul;
                coin += coinMul;
            }
            if (coin < coinBattle) {
                coinNum[4] = coinBattle - coin;
            } else {
                coinNum[4] = 0;
            }
            break;

        default:
            for (i = 0; i < 4; i++) {
                coin = GWMgCoinBonusGet(i) + GWMgCoinGet(i);
                coinNum[i] = coin;
            }
            break;
    }
}

/* 32 insns */
BOOL Result_CharMotEnd(s16 playerNo)
{
    if (Hu3DMotionShiftIDGet(StageCharMdlId[playerNo]) == HU3D_MOTID_NONE && Hu3DMotionEndCheck(StageCharMdlId[playerNo])) {
        return TRUE;
    }
    return FALSE;
}

/* 64 insns */
void Result_BoardSave(void)
{
    s16 i;
    s16 turnNo;

    turnNo = GwSystem.turnNo;
    for (i = 0; i < 4; i++) {
        ((u16 *)GwPlayer[i].starStat)[turnNo - 1] = GwPlayer[i].star;
        ((u16 *)GwPlayer[i].coinStat)[turnNo - 1] = GwPlayer[i].coin;
    }
    SLSaveBoardTurnExec();
    if (!SLSaveFlagGet()) {
        GwSystem.saveMode = GW_SAVEMODE_NONE;
    }
}

/* 135 insns */
void Result_Debug(void)
{
    int i;
    s16 total;
    s16 coinNum[5];
    s16 rank[4];

    if (mgDataTbl[GwSystem.mgNo].type != 3) {
        OSReport("\n");
        OSReport("--------------Result BonusCoin-------------- \n");
        for (i = 0; i < 4; i++) {
            coinNum[i] = GWMgCoinBonusGet(i) + GWMgCoinGet(i);
            OSReport("Player=%d  BonusCoin=%d \n", i, coinNum[i]);
        }
        OSReport("-------------------------------------------- \n");
        OSReport("\n");
    } else {
        OSReport("\n");
        OSReport("--------------BATTLE_MINIGAME------------- \n");
        OSReport("--------------Result GetCoin-------------- \n");
        Result_GetCoin(coinNum);
        for (i = total = 0; i < 5; i++) {
            total += coinNum[i];
        }
        OSReport("TotalCoin=%d \n", total);
        for (i = 0; i < 4; i++) {
            rank[i] = GWMgCoinBonusGet(i);
            OSReport("Player=%d  Rank=%d  GetCoin=%d \n", i, rank[i], coinNum[rank[i]]);
        }
        OSReport("RandomCoin=%d \n", coinNum[4]);
        OSReport("-------------------------------------------- \n");
        OSReport("\n");
    }
}

