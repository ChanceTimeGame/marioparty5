/*
 * resultDll battle.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/resultDll/asm/REL/resultDll/battle.s.
 */

/* see resultDll.h: retail calls Result_SetBonusSprNum without a prototype here */
#define RESULT_BONUSSPRNUM_NOPROTO
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
#include "humath.h"

/* Retail calls the esp* functions and hsfex.h's Hu3D2Dto3D/Hu3D3Dto2D UNPROTOTYPED
 * (the result register is copied after the void Hu3D2Dto3D calls in BattleCreate);
 * both headers stay out of the GameCube build, as in MP4's resultDll. */
#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_1C0 = -10000.0f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = 400.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = 0.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = 0.5f; /* 0x1CC */
static const double lbl_1_rodata_1D0 = 0.30000001192092896; /* 0x1D0 */
static const double lbl_1_rodata_1D8 = 0.8999999761581421; /* 0x1D8 */
static const float lbl_1_rodata_1E0 = 390.0f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = 36.0f; /* 0x1E4 */
static const float lbl_1_rodata_1E8 = -22.0f; /* 0x1E8 */
static const float lbl_1_rodata_1EC = 0.37f; /* 0x1EC */
static const float lbl_1_rodata_1F0 = 0.001f; /* 0x1F0 */
static const float lbl_1_rodata_1F4 = 0.8f; /* 0x1F4 */
/* 0x1F8 lbl_1_rodata_1F8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_200 = 0.3f; /* 0x200 */
static const double lbl_1_rodata_208 = 1.5; /* 0x208 */
static const double lbl_1_rodata_210 = 1.0; /* 0x210 */
static const float lbl_1_rodata_218 = 10.0f; /* 0x218 */
static const float lbl_1_rodata_21C = 0.7f; /* 0x21C */
static const float lbl_1_rodata_220 = -200.0f; /* 0x220 */
static const float lbl_1_rodata_224 = 1600.0f; /* 0x224 */
static const float lbl_1_rodata_228 = 0.05f; /* 0x228 */
static const float lbl_1_rodata_22C = 190.0f; /* 0x22C */
static const float lbl_1_rodata_230 = 130.0f; /* 0x230 */
static const float lbl_1_rodata_234 = 250.0f; /* 0x234 */
static const float lbl_1_rodata_238 = 0.03f; /* 0x238 */
static const float lbl_1_rodata_23C = 1.0f; /* 0x23C */
static const float lbl_1_rodata_240 = 5.0f; /* 0x240 */
static const float lbl_1_rodata_244 = 0.002f; /* 0x244 */
static const float lbl_1_rodata_248 = 0.005f; /* 0x248 */
static const float lbl_1_rodata_24C = 0.07f; /* 0x24C */
static const float lbl_1_rodata_250 = 2.0f; /* 0x250 */
static const float lbl_1_rodata_254 = 776.0f; /* 0x254 */
static const double lbl_1_rodata_258 = 3.141592653589793; /* 0x258 */
static const double lbl_1_rodata_260 = 90.0; /* 0x260 */
static const double lbl_1_rodata_268 = 180.0; /* 0x268 */
/* 0x270 lbl_1_rodata_270 (0x8): 8 0 -- an aggregate initialiser, write it as a local */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1F94 gap_05_00001F94_bss (0x4): alignment gap */
/* 0x1F90 */ static ANIMDATA *RankAnimP;
/* 0x1F8E gap_05_00001F8E_bss (0x2): alignment gap */
/* 0x1F8C */ static HUSPRGRPID RankSprGrpId;
/* 0x1F84 */ static s16 BattlePlayerNo[4];
/* 0x1F7C */ static s16 BattleRank[4];
/* 0x1F7A */ static s16 lbl_1_bss_1F7A; /* unreferenced */
/* 0x1F72 */ static HUSPRGRPID BonusSprGrpId[4];
/* 0x1F4A */ static HUSPRID BonusSprId[4][5];
/* 0x1F42 */ static s16 BattleCharNo[4];
/* 0x1F38 */ static s16 BattleCoin[5];
/* 0x1F2C */ static HU3DMODELID CoinBagMdlId[6];
/* 0x1F24 */ static HU3DMODELID CoinBagFlatMdlId[4];
/* 0x1D24 */ static HU3DMODELID CoinMdlId[256];
/* 0xD24 */ static float CoinRotYSpeed[4][256];
/* 0x924 */ static float CoinYSpeed[256];
/* 0x524 */ static float CoinYAccel[256];
/* 0x522 */ static HU3DMODELID GuideMdlId;
/* 0x520 */ s16 lbl_1_bss_520; /* unreferenced */
/* 0x51C */ static float GuideSpeed;
/* 0x518 */ static BOOL BattleSkipF;

/* --- functions (reference order), .data placed before its first user --- */
/* 179 insns */
void Result_BattleMain(void)
{
    s16 i;
    HUWINID winId;
    s16 comNum;
    BOOL endF;
    HUPROCESS *proc;

    endF = FALSE;
    proc = HuPrcCurrentGet();
    Result_Debug();
    for(i = comNum = 0; i < 4; i++) {
        if(GwPlayerConf[i].type != GW_TYPE_MAN) {
            comNum++;
        }
    }
    if(comNum == 4) {
        BattleSkipF = TRUE;
    } else {
        BattleSkipF = FALSE;
    }
    Result_BattleCreate();
    HuPrcChildCreate(Result_BattleCoinMdlMain, 100, 0x2000, 0, proc);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    HuAudSStreamPlay(91);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    HuDataDirClose(DATA_result);
    Result_BgReadEndF = FALSE;
    HuPrcChildCreate(Result_BgRead, 100, 0x3000, 0, proc);
    HuPrcSleep(10);
    if(!Result_FastF) {
        HuPrcSleep(20);
    }
    Result_BattleStart();
    Result_BattleAddCoin();
    Result_BattleAddRandomCoin();
    Result_BattleShowBonus();
    Result_AddBonusCoin();
    winId = HuWinCreate(-10000.0f, 400.0f, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    if(!BattleSkipF) {
        HuWinMesSet(winId, 0x2000D);
    }
    HuPrcSleep(4);
    while(1) {
        if(BattleSkipF) {
            endF = TRUE;
        } else {
            for(i = 0; i < 4; i++) {
                if(HuPadStatGet(i) == 0 && (HuPadBtnDown[i] & PAD_BUTTON_A)) {
                    endF = TRUE;
                    break;
                }
            }
        }
        if(endF) {
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

/* 57 insns */
void Result_BattleCoinMdlMain(void)
{
    s16 i;
    HuVecF pos;

    pos.z = 0.0f;
    pos.y = 0.0f;
    pos.x = 0.0f;
    while(1) {
        if(BattleSkipF) {
            Result_FastF = TRUE;
        } else {
            for(i = 0; i < 4; i++) {
                if(HuPadStatGet(i) == 0) {
                    if(HuPadBtn[i] & PAD_BUTTON_A) {
                        Result_FastF = TRUE;
                    } else {
                        Result_FastF = FALSE;
                    }
                }
            }
        }
        HuPrcVSleep();
    }
}

/* 0x7F0 */ STAGE_MODEL Result_BattleModel[3] = {
    { DATANUM(DATA_result, 24), 0x40000001, 0, -1, -1, 0, 2, { 288.0f, 240.0f, 2500.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
    { DATANUM(DATA_result, 31), 0x40000001, 0, -1, -1, 0, 1, { 300.0f, 800.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f, 2.0f } },
    { HU_DATANUM_NONE, 0x00000000, 0, -1, -1, -1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
};
/* 0x898 */ STAGE_SPRITE Result_BattleSprite[6] = {
    { DATANUM(DATA_result, 6), 0, 10, 288.0f, 70.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 12), 0, 20, 108.0f, -1050.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 12), 0, 20, 228.0f, -850.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 12), 0, 20, 348.0f, -550.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 12), 0, 20, 468.0f, -250.0f, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0.0f, 0.0f, { 0, 0, 0, 0 } },
};
/* 0x910 */ static s16 RankPosTbl[4 * 2] = { 108, -1170, 228, -970, 348, -670, 468, -370 };
/* 0x920 */ static s16 BonusPosTbl[4 * 2] = { 93, 300, 213, 300, 333, 300, 453, 300 };
/* 0x930 */ static HuVecF ToueiPosTbl[4] = { { 105.0f, -1110.0f, 1600.0f }, { 227.0f, -910.0f, 1600.0f }, { 347.0f, -610.0f, 1600.0f }, { 467.0f, -310.0f, 1600.0f } };
/* 0x960 */ static HuVecF ToueiRotTbl[4] = { { 0.0f, 5.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, -5.0f, 0.0f }, { 0.0f, -10.0f, 0.0f } };
/* 0x990 */ static HuVecF ToueiCharPosTbl[4] = { { 240.0f, 250.0f, 1700.0f }, { 240.0f, 400.0f, 1700.0f }, { 320.0f, 250.0f, 1700.0f }, { 320.0f, 400.0f, 1700.0f } };
/* 0x9C0 */ static HuVecF ToueiCharScaleTbl[13] = { { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.6f, 0.6f, 0.6f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.5f, 0.5f, 0.5f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f } };
/* 0xA5C */ static HuVecF CoinBagPosTbl[4] = { { 108.0f, 220.0f, 1600.0f }, { 228.0f, 220.0f, 1600.0f }, { 348.0f, 220.0f, 1600.0f }, { 468.0f, 220.0f, 1600.0f } };
/* 0xA8C */ static HuVecF GuideEndPos = { 926.0f, 220.0f, 1600.0f };
/* 0xA98 */ static HuVecF CoinBagScaleTbl[4] = { { 0.8f, 0.8f, 0.8f }, { 0.6f, 0.6f, 0.6f }, { 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, 0.5f } };
/* 0xAC8 */ static float CoinMaxPosYTbl[4] = { 310.0f, 330.0f, 360.0f, 360.0f };
/* 0xAD8 */ static HuVecF BonusSprPosTbl[4] = { { 12.0f, -25.0f, 0.0f }, { 28.0f, -25.0f, 0.0f }, { 44.0f, -25.0f, 0.0f }, { 60.0f, -25.0f, 0.0f } };

/* 1008 insns */
void Result_BattleCreate(void)
{
    s16 i;
    s16 j;
    s16 fileOfs;
    HUSPRID sprId;
    ANIMDATA *numAnim;
    ANIMDATA *coinAnim;
    HuVecF pos;
    HuVecF pos2D;

    StageSpriteCreate(Result_BattleSprite);
    StageModelCreate(Result_BattleModel);
    Hu3DMotionSpeedSet(StageMdlId[0], 0.5f);
    espTPLvlSet(StageSprId[0], 0.3f);
    for(i = 1; i < 5; i++) {
        espScaleSet(StageSprId[i], 0.9f, 0.9f);
    }
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            CoinBagMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 18));
        } else if(i == 3 || i == 2) {
            CoinBagMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 18));
        } else {
            CoinBagMdlId[i] = Hu3DModelLink(CoinBagMdlId[0]);
        }
        Hu3D2Dto3D(&CoinBagPosTbl[i], HU3D_CAM2, &pos);
        Hu3DModelScaleSet(CoinBagMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(CoinBagMdlId[i], 2);
        Hu3DModelPosSetV(CoinBagMdlId[i], &pos);
        Hu3DModelCameraSet(CoinBagMdlId[i], HU3D_CAM2);
        Hu3DModelAttrSet(CoinBagMdlId[i], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    }
    CoinBagFlatMdlId[0] = CoinBagFlatMdlId[1] = HU3D_MODELID_NONE;
    for(i = 2; i < 4; i++) {
        CoinBagFlatMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 21));
        pos2D = CoinBagPosTbl[i];
        pos2D.y = 390.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(CoinBagFlatMdlId[i], &pos);
        Hu3DModelScaleSet(CoinBagFlatMdlId[i], CoinBagScaleTbl[i].x, CoinBagScaleTbl[i].y, CoinBagScaleTbl[i].z);
        Hu3DModelLayerSet(CoinBagFlatMdlId[i], 2);
        Hu3DModelCameraSet(CoinBagFlatMdlId[i], HU3D_CAM2);
        Hu3DModelAttrSet(CoinBagFlatMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(CoinBagFlatMdlId[i], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    }
    numAnim = HuSprAnimDataRead(DATANUM(DATA_result, 3));
    coinAnim = HuSprAnimDataRead(DATANUM(DATA_result, 8));
    for(i = 0; i < 4; i++) {
        BonusSprGrpId[i] = HuSprGrpCreate(5);
        BonusSprId[i][0] = HuSprCreate(coinAnim, 10, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
        HuSprPosSet(BonusSprGrpId[i], 0, 36.0f, -22.0f);
        for(j = 1; j < 5; j++) {
            BonusSprId[i][j] = HuSprCreate(numAnim, 0, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], j, BonusSprId[i][j]);
            HuSprPosSet(BonusSprGrpId[i], j, BonusSprPosTbl[j - 1].x, BonusSprPosTbl[j - 1].y);
        }
        HuSprBankSet(BonusSprGrpId[i], 1, 10);
        HuSprGrpPosSet(BonusSprGrpId[i], BonusPosTbl[i * 2], BonusPosTbl[i * 2 + 1]);
        HuSprGrpScaleSet(BonusSprGrpId[i], 0.0f, 0.0f);
    }
    Result_BattleSetupPlayer();
    RankAnimP = HuSprAnimDataRead(DATANUM(DATA_result, 5));
    RankSprGrpId = HuSprGrpCreate(4);
    for(i = 0; i < 4; i++) {
        sprId = HuSprCreate(RankAnimP, i, 0);
        HuSprGrpMemberSet(RankSprGrpId, i, sprId);
        HuSprPosSet(RankSprGrpId, i, RankPosTbl[i * 2], RankPosTbl[i * 2 + 1]);
        HuSprPriSet(RankSprGrpId, i, 15);
        HuSprBankSet(RankSprGrpId, i, BattleRank[i]);
    }
    HuSprGrpDrawNoSet(RankSprGrpId, 64);
    HuSprExecLayerCameraSet(64, HU3D_CAM1, 1);
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
        Hu3DModelRotSetV(StageToueiMdlId[i], &ToueiRotTbl[i]);
        BattleCharNo[i] = GwPlayerConf[BattlePlayerNo[i]].charNo;
        fileOfs = BattleCharNo[i] * 4;
        StageCharMdlId[i] = Hu3DModelCreateData(fileOfs + DATANUM(DATA_result, 32));
        StageCharMotId[i][0] = Hu3DJointMotionData(StageCharMdlId[i], fileOfs + DATANUM(DATA_result, 33));
        StageCharMotId[i][1] = Hu3DJointMotionData(StageCharMdlId[i], fileOfs + DATANUM(DATA_result, 34));
        StageCharMotId[i][2] = Hu3DJointMotionData(StageCharMdlId[i], fileOfs + DATANUM(DATA_result, 35));
        Hu3D2Dto3D(&ToueiCharPosTbl[i], HU3D_CAM0, &pos);
        Hu3DMotionSet(StageCharMdlId[i], StageCharMotId[i][0]);
        Hu3DModelScaleSet(StageCharMdlId[i], ToueiCharScaleTbl[BattleCharNo[i]].x, ToueiCharScaleTbl[BattleCharNo[i]].y, ToueiCharScaleTbl[BattleCharNo[i]].z);
        Hu3DModelLayerSet(StageCharMdlId[i], 0);
        Hu3DModelPosSetV(StageCharMdlId[i], &pos);
        Hu3DModelAttrSet(StageCharMdlId[i], HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(StageCharMdlId[i], HU3D_CAM0);
    }
    ToueiDispInit(BattleCharNo);
    for(i = 0; i < 256; i++) {
        if(i == 0) {
            CoinMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_result, 23));
        } else {
            CoinMdlId[i] = Hu3DModelLink(CoinMdlId[0]);
        }
        Hu3DModelAttrSet(CoinMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(CoinMdlId[i], HU3D_CAM2);
        Hu3DModelLayerSet(CoinMdlId[i], 1);
        CoinYAccel[i] = 0.001f;
        Hu3DModelScaleSet(CoinMdlId[i], 0.5f, 0.5f, 0.5f);
        CoinYSpeed[i] = 0.0f;
    }
    GuideMdlId = Hu3DModelCreateData(DATANUM(DATA_result, 85));
    Hu3DModelAttrSet(GuideMdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(GuideMdlId, HU3D_CAM2);
    Hu3D2Dto3D(&GuideEndPos, HU3D_CAM2, &pos);
    Hu3DModelPosSetV(GuideMdlId, &pos);
    Hu3DModelLayerSet(GuideMdlId, 1);
    Hu3DModelScaleSet(GuideMdlId, 0.8f, 0.8f, 0.8f);
    Result_GetCoin(BattleCoin);
}

/* 0xB08 */ static float CoinDropPosXTbl[4] = { 108.0f, 228.0f, 348.0f, 468.0f };

/* 432 insns */
void Result_BattleStart(void)
{
    s16 i;
    HUSPRITE *sprP;
    HU3DMODEL *modelP;
    HUSPRGRP *grpP;
    BOOL endF;
    HUSPRGRPID grpId;
    float tpLvl;
    float speed;
    HuVecF pos2D;
    float scale[4];
    BOOL openF[4];
    BOOL dropF[4];

    tpLvl = 0.3f;
    endF = FALSE;
    for(i = 0; i < 4; i++) {
        dropF[i] = FALSE;
        scale[i] = 0.0f;
        openF[i] = FALSE;
    }
    while(1) {
        speed = (Result_FastF) ? 1.5 : 1.0;
        GuideSpeed = 10.0f * speed;
        modelP = &Hu3DData[GuideMdlId];
        Hu3D3Dto2D(&modelP->pos, HU3D_CAM2, &pos2D);
        pos2D.x -= 0.7f * GuideSpeed;
        for(i = 3; i > -1; i--) {
            if(!dropF[i] && pos2D.x <= CoinDropPosXTbl[i]) {
                dropF[i] = TRUE;
            }
        }
        if(pos2D.x <= -200.0f) {
            endF = TRUE;
        }
        pos2D.z = 1600.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &modelP->pos);
        for(i = 0; i < 4; i++) {
            if(dropF[i]) {
                modelP = &Hu3DData[CoinBagMdlId[i]];
                scale[i] += 0.05f;
                if(scale[i] >= CoinBagScaleTbl[BattleRank[i]].x) {
                    scale[i] = CoinBagScaleTbl[BattleRank[i]].x;
                }
                Hu3DModelScaleSet(CoinBagMdlId[i], scale[i], scale[i], scale[i]);
                Hu3D3Dto2D(&modelP->pos, HU3D_CAM2, &pos2D);
                pos2D.y += 0.5f * GuideSpeed;
                if(pos2D.y > 390.0f) {
                    pos2D.y = 390.0f;
                    if((BattleRank[i] == 2 || BattleRank[i] == 3) && !openF[i]) {
                        Hu3DModelAttrReset(CoinBagMdlId[i], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                        openF[i] = TRUE;
                    }
                }
                pos2D.z = 1600.0f;
                Hu3D2Dto3D(&pos2D, HU3D_CAM2, &modelP->pos);
            }
        }
        for(i = 0; i < 4; i++) {
            modelP = &Hu3DData[StageToueiMdlId[i]];
            Hu3D3Dto2D(&modelP->pos, HU3D_CAM1, &pos2D);
            pos2D.y += GuideSpeed;
            if(pos2D.y > 190.0f) {
                pos2D.y = 190.0f;
            }
            pos2D.z = 1600.0f;
            Hu3D2Dto3D(&pos2D, HU3D_CAM1, &modelP->pos);
        }
        for(i = 0; i < 4; i++) {
            grpP = &HuSprGrpData[RankSprGrpId];
            sprP = &HuSprData[grpP->sprId[i]];
            sprP->pos.y += GuideSpeed;
            if(sprP->pos.y > 130.0f) {
                sprP->pos.y = 130.0f;
            }
        }
        grpId = espGrpIDGet();
        for(i = 1; i < 5; i++) {
            grpP = &HuSprGrpData[grpId];
            sprP = &HuSprData[grpP->sprId[i]];
            sprP->pos.y += GuideSpeed;
            if(sprP->pos.y > 250.0f) {
                sprP->pos.y = 250.0f;
            }
        }
        if(endF) {
            while(1) {
                tpLvl += 0.03f;
                if(tpLvl >= 1.0f) {
                    espTPLvlSet(StageSprId[0], 1.0f);
                    return;
                }
                espTPLvlSet(StageSprId[0], tpLvl);
                HuPrcVSleep();
            }
        }
        HuPrcVSleep();
    }
}

/* 0xB18 */ static HuVecF CoinStartPosTbl[4] = { { 108.0f, -100.0f, 1600.0f }, { 228.0f, -100.0f, 1600.0f }, { 348.0f, -100.0f, 1600.0f }, { 468.0f, -100.0f, 1600.0f } };

/* 434 insns */
void Result_BattleAddCoin(void)
{
    int i;
    int k;
    int j;
    HU3DMODEL *modelP;
    s32 coinNum;
    float speed;
    s16 unusedB[4][256];
    s16 unusedA[4][256];
    s32 coinSlot[256];
    float rotSpeed[256];
    HuVecF pos2D;
    HuVecF pos;
    s32 dropNum[4];
    s32 unusedC[4];
    s32 delay[4];
    s16 landNum[4];
    s32 unusedD;
    s32 unusedE;
    s32 unusedF;

    unusedD = 0;
    unusedE = 0;
    unusedF = 0;
    coinNum = 0;
    for(i = 0; i < 4; i++) {
        coinNum += BattleCoin[i];
        dropNum[i] = 0;
        unusedC[i] = 0;
        delay[i] = 0;
        landNum[i] = 0;
        for(j = 0; j < 256; j++) {
            unusedB[i][j] = 0;
            unusedA[i][j] = 0;
            CoinRotYSpeed[i][j] = 0.0f;
        }
    }
    while(1) {
        speed = (Result_FastF) ? 1.5 : 1.0;
        for(i = 0; i < 4; i++) {
            if(--delay[i] <= 0 && BattleCoin[i] > 0 && dropNum[i] < BattleCoin[i]) {
                for(k = 0; k < 256; k++) {
                    if(Hu3DModelAttrGet(CoinMdlId[k]) & HU3D_ATTR_DISPOFF) {
                        Hu3DModelAttrReset(CoinMdlId[k], HU3D_ATTR_DISPOFF);
                        Hu3D2Dto3D(&CoinStartPosTbl[i], HU3D_CAM1, &pos);
                        Hu3DModelPosSetV(CoinMdlId[k], &pos);
                        rotSpeed[k] = 5.0f;
                        CoinYSpeed[k] = 10.0f;
                        delay[i] = 6;
                        dropNum[i]++;
                        coinSlot[k] = i;
                        break;
                    }
                }
            }
        }
        for(i = 0; i < 256; i++) {
            if(!(Hu3DModelAttrGet(CoinMdlId[i]) & HU3D_ATTR_DISPOFF)) {
                modelP = &Hu3DData[CoinMdlId[i]];
                Hu3D3Dto2D(&modelP->pos, HU3D_CAM1, &pos2D);
                pos2D.y += speed * CoinYSpeed[i];
                CoinYSpeed[i] += 0.002f * speed;
                pos2D.z = 1600.0f;
                Hu3D2Dto3D(&pos2D, HU3D_CAM1, &modelP->pos);
                modelP->rot.y += rotSpeed[i];
                if(pos2D.y >= CoinMaxPosYTbl[BattleRank[coinSlot[i]]]) {
                    HuAudFXPlay(7);
                    if(BattleRank[coinSlot[i]] == 3 && landNum[coinSlot[i]] == 0) {
                        Hu3DModelAttrSet(CoinBagMdlId[coinSlot[i]], HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(CoinBagFlatMdlId[coinSlot[i]], HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(CoinBagFlatMdlId[coinSlot[i]], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                    }
                    if(BattleRank[coinSlot[i]] == 2 && landNum[coinSlot[i]] == 0) {
                        Hu3DModelAttrSet(CoinBagMdlId[coinSlot[i]], HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(CoinBagFlatMdlId[coinSlot[i]], HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(CoinBagFlatMdlId[coinSlot[i]], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                    }
                    CharEffectCoinGlowCreate(4, &modelP->pos);
                    Hu3DModelAttrSet(CoinMdlId[i], HU3D_ATTR_DISPOFF);
                    landNum[coinSlot[i]]++;
                    coinNum--;
                }
            }
        }
        if(coinNum <= 0) {
            break;
        }
        HuPrcVSleep();
    }
    for(i = 0; i < 256; i++) {
        CoinYAccel[i] = 0.005f;
        Hu3DModelScaleSet(CoinMdlId[i], 0.5f, 0.5f, 0.5f);
        Hu3DModelAttrSet(CoinMdlId[i], HU3D_ATTR_DISPOFF);
        CoinYSpeed[i] = 0.0f;
    }
    HuPrcSleep(20);
}

/* 0xB48 */ static float CoinRandomPosXTbl[4] = { 108.0f, 228.0f, 348.0f, 468.0f };

/* 392 insns */
void Result_BattleAddRandomCoin(void)
{
    int i;
    int k;
    int activeNum;
    HU3DMODEL *modelP;
    s16 landNum;
    HU3DMODEL *guideP;
    BOOL dropStartF;
    BOOL endF;
    float speed;
    s16 delay[256];
    HuVecF pos2D;
    HuVecF pos;

    activeNum = 0;
    landNum = 0;
    dropStartF = FALSE;
    endF = FALSE;
    for(i = 0; i < 256; i++) {
        delay[i] = 8;
    }
    while(1) {
        speed = (Result_FastF) ? 1.5 : 1.0;
        GuideSpeed = 10.0f * speed;
        guideP = &Hu3DData[GuideMdlId];
        Hu3D3Dto2D(&guideP->pos, HU3D_CAM1, &pos2D);
        pos2D.x += 0.7f * GuideSpeed;
        pos2D.z = 1600.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM1, &guideP->pos);
        if(pos2D.x >= CoinRandomPosXTbl[Result_RandomCoinPlayer] - 0.07f * GuideSpeed && !dropStartF) {
            for(i = 0; i < BattleCoin[4]; i++) {
                for(k = 0; k < 256; k++) {
                    if(Hu3DModelAttrGet(CoinMdlId[k]) & HU3D_ATTR_DISPOFF) {
                        Hu3DModelAttrReset(CoinMdlId[k], HU3D_ATTR_DISPOFF);
                        pos = guideP->pos;
                        pos.x -= 2.0f;
                        Hu3DModelPosSetV(CoinMdlId[k], &pos);
                        CoinRotYSpeed[Result_RandomCoinPlayer][k] = 5.0f;
                        CoinYSpeed[k] = 2.0f;
                        activeNum++;
                        break;
                    }
                }
            }
            dropStartF = TRUE;
        }
        if(dropStartF) {
            for(i = 0; i < 256; i++) {
                if(!(Hu3DModelAttrGet(CoinMdlId[i]) & HU3D_ATTR_DISPOFF)) {
                    if(i == 0 || (i != 0 && delay[i - 1] <= 0)) {
                        modelP = &Hu3DData[CoinMdlId[i]];
                        Hu3D3Dto2D(&modelP->pos, HU3D_CAM1, &pos2D);
                        pos2D.y += CoinYSpeed[i];
                        CoinYSpeed[i] += 0.3f;
                        pos2D.z = 1600.0f;
                        Hu3D2Dto3D(&pos2D, HU3D_CAM1, &modelP->pos);
                        modelP->rot.y += CoinRotYSpeed[Result_RandomCoinPlayer][i];
                        if(pos2D.y >= CoinMaxPosYTbl[BattleRank[Result_RandomCoinPlayer]]) {
                            HuAudFXPlay(7);
                            if(BattleRank[Result_RandomCoinPlayer] == 3 && landNum == 0) {
                                Hu3DModelAttrSet(CoinBagMdlId[Result_RandomCoinPlayer], HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrReset(CoinBagFlatMdlId[Result_RandomCoinPlayer], HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrReset(CoinBagFlatMdlId[Result_RandomCoinPlayer], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                            }
                            if(BattleRank[Result_RandomCoinPlayer] == 2 && landNum == 0) {
                                Hu3DModelAttrSet(CoinBagMdlId[Result_RandomCoinPlayer], HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrReset(CoinBagFlatMdlId[Result_RandomCoinPlayer], HU3D_ATTR_DISPOFF);
                                Hu3DModelAttrReset(CoinBagFlatMdlId[Result_RandomCoinPlayer], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                            }
                            landNum++;
                            CharEffectCoinGlowCreate(4, &modelP->pos);
                            Hu3DModelAttrSet(CoinMdlId[i], HU3D_ATTR_DISPOFF);
                            activeNum--;
                        }
                        delay[i]--;
                    }
                }
            }
            if(activeNum == 0 && pos2D.x > 776.0f) {
                endF = TRUE;
            }
        }
        if(endF) {
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
}

/* 373 insns */
void Result_BattleShowBonus(void)
{
    s16 i;
    s16 time;
    s16 maxTime;
    s16 j;
    s16 endNum;
    s16 coinNum;
    float scale;
    s32 unused[4];

    for(i = 0; i < 4; i++) {
        if(Result_RandomCoinPlayer == i) {
            Result_SetBonusSprNum(BonusSprGrpId[i], BattleCoin[4] + BattleCoin[i]);
        } else {
            Result_SetBonusSprNum(BonusSprGrpId[i], BattleCoin[i]);
        }
        unused[i] = 0;
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for(time = 0; time <= maxTime; time++) {
        scale = HuSin((90.0 / maxTime) * time);
        for(i = 0; i < 4; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for(i = 0; i < 4; i++) {
        HuSprGrpScaleSet(BonusSprGrpId[i], 1.0f, 1.0f);
    }
    if(!Result_FastF) {
        HuPrcSleep(15);
    }
    for(i = 0; i < 4; i++) {
        if(Result_RandomCoinPlayer == i) {
            coinNum = BattleCoin[4] + BattleCoin[i];
        } else {
            coinNum = BattleCoin[i];
        }
        if(coinNum != 0) {
            Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][1], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
            PlayerFXPlay(BattlePlayerNo[i], 504);
        } else {
            Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][2], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
        }
    }
    while(1) {
        for(i = endNum = 0; i < 4; i++) {
            if(Result_CharMotEnd(i)) {
                endNum++;
            }
        }
        if(endNum >= 4) {
            for(i = 0; i < 4; i++) {
                Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            break;
        }
        HuPrcVSleep();
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for(time = 0; time <= maxTime; time++) {
        scale = HuCos((90.0 / maxTime) * time);
        for(i = 0; i < 4; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 5; j++) {
            HuSprAttrSet(BonusSprGrpId[i], j, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* 139 insns */
void Result_BattleSetupPlayer(void)
{
    s16 i;
    s16 j;
    s16 k;
    s16 temp;
    s16 rank;
    s16 bonusJ;
    s16 bonusI;

    for(i = 0; i < 4; i++) {
        for(j = rank = 0; j < 4; j++) {
            if(i != j) {
                bonusJ = GwPlayer[j].mgCoinBonus;
                bonusI = GwPlayer[i].mgCoinBonus;
                if(bonusI > bonusJ) {
                    rank++;
                }
            }
        }
        BattleRank[i] = rank;
        BattlePlayerNo[i] = i;
    }
    for(k = 1; k < 4; k++) {
        for(i = 0; i < 4 - k; i++) {
            if(BattleRank[i] > BattleRank[i + 1]) {
                temp = BattleRank[i];
                BattleRank[i] = BattleRank[i + 1];
                BattleRank[i + 1] = temp;
                temp = BattlePlayerNo[i];
                BattlePlayerNo[i] = BattlePlayerNo[i + 1];
                BattlePlayerNo[i + 1] = temp;
            }
        }
    }
}

