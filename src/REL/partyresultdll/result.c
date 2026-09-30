/*
 * partyresultdll result.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/partyresultdll/asm/REL/partyresultdll/result.s.
 */

#include "REL/partyresultdll.h"

#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/saveload.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/hsfex.h"
#include "math.h"

/* Retail result.c calls the HuAud* API unprototyped (implicit int): the discarded results
 * are copied (mr r0,r3 after HuAudSStreamAllFadeOut 0x70A4, mr r4,r3 after HuAudFXStop 0x66CC)
 * and PResResultFinal/FinalTeam/Tie only reach raw=0 without the prototypes. Host: include it. */
#ifndef __MWERKS__
#include "game/audio.h"
#endif

#ifndef __MWERKS__
/* retail calls sprintf unprototyped (no crclr before the call); the host needs the prototypes */
#include <stdio.h>
#include <string.h>
#endif

#include "game/main.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_70 = 1.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 3.0f; /* 0x74 */
static const float lbl_1_rodata_78 = -180.0f; /* 0x78 */
static const float lbl_1_rodata_7C = -70.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 0.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 130.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 80.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 70.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 0.8f; /* 0x90 */
static const float lbl_1_rodata_94 = 288.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 380.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 90.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 320.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 118.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 4.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = 123.0f; /* 0xAC */
static const float lbl_1_rodata_B0 = 40.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 4700.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 5500.0f; /* 0xB8 */
/* 0xC0 lbl_1_rodata_C0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_C8 = 16.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 376.0f; /* 0xCC */
static const double lbl_1_rodata_D0 = 3.141592653589793; /* 0xD0 */
static const double lbl_1_rodata_D8 = 90.0; /* 0xD8 */
static const double lbl_1_rodata_E0 = 20.0; /* 0xE0 */
static const double lbl_1_rodata_E8 = 180.0; /* 0xE8 */
static const double lbl_1_rodata_F0 = 50.0; /* 0xF0 */
static const double lbl_1_rodata_F8 = 370.0; /* 0xF8 */
static const double lbl_1_rodata_100 = 30.0; /* 0x100 */
static const double lbl_1_rodata_108 = 4000.0; /* 0x108 */
static const double lbl_1_rodata_110 = 1.0; /* 0x110 */
static const double lbl_1_rodata_118 = 40.0; /* 0x118 */
static const float lbl_1_rodata_120 = 0.5f; /* 0x120 */
static const float lbl_1_rodata_124 = 10.0f; /* 0x124 */
static const double lbl_1_rodata_128 = 0.1; /* 0x128 */
static const double lbl_1_rodata_130 = 0.9; /* 0x130 */
static const float lbl_1_rodata_138 = 200.0f; /* 0x138 */
static const float lbl_1_rodata_13C = 20.0f; /* 0x13C */
static const float lbl_1_rodata_140 = 180.0f; /* 0x140 */
static const double lbl_1_rodata_148 = 500.0; /* 0x148 */
static const float lbl_1_rodata_150 = 270.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 25.0f; /* 0x154 */
static const float lbl_1_rodata_158 = 30.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 50.0f; /* 0x15C */
static const double lbl_1_rodata_160 = 1.5; /* 0x160 */
static const double lbl_1_rodata_168 = 60.0; /* 0x168 */
static const double lbl_1_rodata_170 = 350.0; /* 0x170 */
static const float lbl_1_rodata_178 = 2.0f; /* 0x178 */
static const double lbl_1_rodata_180 = 100.0; /* 0x180 */
static const double lbl_1_rodata_188 = 25.0; /* 0x188 */
static const double lbl_1_rodata_190 = 360.0; /* 0x190 */
static const double lbl_1_rodata_198 = 120.0; /* 0x198 */
static const double lbl_1_rodata_1A0 = 32.0; /* 0x1A0 */
static const float lbl_1_rodata_1A8 = 8.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 340.0f; /* 0x1AC */
static const double lbl_1_rodata_1B0 = 70.0; /* 0x1B0 */
static const double lbl_1_rodata_1B8 = 170.0; /* 0x1B8 */
static const float lbl_1_rodata_1C0 = 360.0f; /* 0x1C0 */
static const double lbl_1_rodata_1C8 = 1.2; /* 0x1C8 */
static const float lbl_1_rodata_1D0 = 170.0f; /* 0x1D0 */
static const double lbl_1_rodata_1D8 = 0.2; /* 0x1D8 */
static const float lbl_1_rodata_1E0 = 150.0f; /* 0x1E0 */
static const double lbl_1_rodata_1E8 = 0.3; /* 0x1E8 */
static const double lbl_1_rodata_1F0 = 0.7; /* 0x1F0 */
static const float lbl_1_rodata_1F8 = 100.0f; /* 0x1F8 */
static const double lbl_1_rodata_200 = 10.0; /* 0x200 */
static const float lbl_1_rodata_208 = 370.0f; /* 0x208 */
static const float lbl_1_rodata_20C = -10000.0f; /* 0x20C */
static const float lbl_1_rodata_210 = 330.0f; /* 0x210 */
static const float lbl_1_rodata_214 = 300.0f; /* 0x214 */
static const double lbl_1_rodata_218 = 0.5; /* 0x218 */
static const double lbl_1_rodata_220 = 15.0; /* 0x220 */
static const float lbl_1_rodata_228 = 0.6f; /* 0x228 */
static const float lbl_1_rodata_22C = 15.0f; /* 0x22C */
static const double lbl_1_rodata_230 = 1.1111111111111112; /* 0x230 */
static const float lbl_1_rodata_238 = 96.0f; /* 0x238 */
static const float lbl_1_rodata_23C = 1.2f; /* 0x23C */
static const double lbl_1_rodata_240 = 0.114; /* 0x240 */
static const double lbl_1_rodata_248 = 0.299; /* 0x248 */
static const double lbl_1_rodata_250 = 0.587; /* 0x250 */
static const double lbl_1_rodata_258 = 65.0; /* 0x258 */
static const double lbl_1_rodata_260 = 1.3; /* 0x260 */
static const float lbl_1_rodata_268 = 0.1f; /* 0x268 */
static const double lbl_1_rodata_270 = 255.0; /* 0x270 */
static const double lbl_1_rodata_278 = 1.05; /* 0x278 */
static const double lbl_1_rodata_280 = 3.0; /* 0x280 */
/* 0x288 lbl_1_rodata_288 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x290 lbl_1_rodata_290 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_294 = 480.0f; /* 0x294 */
static const float lbl_1_rodata_298 = 640.0f; /* 0x298 */
static const double lbl_1_rodata_2A0 = 160.0; /* 0x2A0 */
static const double lbl_1_rodata_2A8 = 64.0; /* 0x2A8 */
static const float lbl_1_rodata_2B0 = 32.0f; /* 0x2B0 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5E2 */ static HU3DMODELID StageMdlId;
/* 0x5E0 */ static HU3DMODELID GuideMdlId;
/* 0x5CC */ static HU3DMOTID GuideMotId[10];
/* 0x5AC */ static HU3DMODELID PlayerNumMdlId[4][4];
/* 0x58C */ static HU3DANIMID PlayerNumAnimId[4][4];
/* 0x584 */ static HU3DMODELID PlayerStarMdlId[4];
/* 0x57C */ static HU3DMODELID PlayerCoinMdlId[4];
/* 0x57A */ static HU3DMODELID StarMdlId;
/* 0x574 */ static HU3DMODELID BonusStarMdlId[3];
/* 0x56C */ static HU3DMODELID BlockMdlId[4];
/* 0x51C */ static HU3DMODELID NumberMdlId[4][10];
/* 0x51A */ static HUWINID MessWinId;
/* 0x518 */ static HUSPRGRPID WinnerSprGrpId;
/* 0x510 */ static HU3DPARMANID StarEffAnimP[4];
/* 0x50C */ static HUWINID TeamNameWinId[2];
/* 0x508 */ static ANIMDATA *DustAnimP;
/* 0x504 */ static ANIMDATA *CircleAnimP;
/* 0x500 */ static BOOL TeamNameFadeF;
/* 0x4FC */ static HUPROCESS *TeamNameProc;
/* 0x4F8 */ static HUPROCESS *PlayerHoverProc;
/* 0x4F6 gap_05_000004F6_bss (0x2): alignment gap */
/* 0x4F4 */ static s16 BlockNum;
/* 0x4E0 */ static s16 BlockResult[10];
/* 0x4D8 */ static s16 BlockPlayerMode[4];
/* 0x4D4 */ static BOOL BlockMode;
/* 0x4C4 */ static s32 BlockSeNo[4];
/* 0x4C0 */ static void *BonusFadeAddr;
/* 0x4BE gap_05_000004BE_bss (0x2): alignment gap */
/* 0x4B6 */ static s16 BonusFadeSize[4];
/* 0x4A9 */ static u8 CharFXPan[13];
/* 0x49C */ static u8 CharFXVol[13];
/* 0x49A */ static s16 BGFadeTime;
/* 0x498 */ static s16 BonusFadeMode;

static void TeamNameMain(void);
static void TeamNamePosUpdate(void);
static void DispStatTotal(void);
static void StatNumSet(s16 slot, s16 num);
static void ResultBonusExec(s16 bonusNo);
static void BlockPlayerProc(void);
static void BlockProc(void);
static void BonusFadeCreate(HU3DMODELID modelId, s16 num, HuVecF *posTbl);
static void BonusFadeFbCopy(s16 layerNo);
static void BonusFadeEffHook(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
static void BGFilter(s16 layerNo);
static void PlayerHover(void);
static void ResultCharFXUpdate(s16 playerNo);
static s32 ResultCharFXPlay(s16 charNo, s16 seNo);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x98 */ static OMCAMERAVIEW MainResultView = { { 0.0f, 120.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1240.0f };
/* 0xB4 */ static OMCAMERAVIEW FinalResultView = { { 45.0f, 100.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 960.0f };
/* 0xD0 */ static HuVecF GuideCenterPos = { 0.0f, 120.0f, 700.0f };
/* 0xDC */ static HuVecF GuideLeftPos = { -320.0f, 50.0f, 0.0f };
/* 0xE8 */ static HuVecF PlayerPosTbl[4] = { { -180.0f, -70.0f, 0.0f }, { -30.0f, -70.0f, 0.0f }, { 120.0f, -70.0f, 0.0f }, { 270.0f, -70.0f, 0.0f } };
/* 0x118 */ static HU3DPARMANPARAM StarEffParManParam = {
    100, 0, 1.0f, 25.0f, 30.0f,
    { 0.0f, -0.03f, 0.0f },
    1.0f, 1.0f, 50.0f, 0.98f,
    4,
    { { 255, 255, 255, 255 }, { 235, 90, 140, 255 }, { 140, 180, 255, 255 }, { 70, 240, 155, 255 } },
    { { 255, 255, 255, 0 }, { 235, 90, 140, 0 }, { 140, 180, 255, 0 }, { 70, 240, 155, 0 } }
};

/* 982 insns */
void PResResultCreate(void)
{
    s16 i;
    s16 j;
    HU3DMODELID modelId;
    HU3DPARMANID parManId;
    ANIMDATA *animP;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s16 charNo;
    HU3DMODEL *modelP;
    float posX;

    modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 3));
    StageMdlId = modelId;
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 3.0f);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelLayerSet(modelId, 0);
    GuideMdlId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 11));
    Hu3DModelCameraSet(GuideMdlId, HU3D_CAM2);
    Hu3DModelLayerSet(GuideMdlId, 1);
    GuideMotId[0] = Hu3DJointMotionData(GuideMdlId, DATANUM(DATA_partyresult, 12));
    GuideMotId[1] = Hu3DJointMotionData(GuideMdlId, DATANUM(DATA_partyresult, 13));
    GuideMotId[2] = Hu3DJointMotionData(GuideMdlId, DATANUM(DATA_partyresult, 14));
    Hu3DMotionSet(GuideMdlId, GuideMotId[0]);
    Hu3DModelAttrSet(GuideMdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSetV(GuideMdlId, &GuideCenterPos);
    if(PResTeamF) {
        posX = -180.0f;
        for(i = 0; i < 4; i++) {
            PlayerPosTbl[i].x = posX;
            PlayerPosTbl[i].y = -70.0f;
            PlayerPosTbl[i].z = 0.0f;
            posX += 130.0f;
            if(i == 1) {
                posX += 80.0f;
            }
        }
    }
    for(i = 0; i < 4; i++) {
        modelId = PResPlayerModelId[i];
        charNo = PResCharNo[i];
        CharMotionSet(charNo, PResPlayerMotion[i][0]);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(modelId, 1);
        modelP = &Hu3DData[modelId];
        MTXTrans(modelP->mtx, 0.0f, 70.0f, 0.0f);
    }
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 4));
            PlayerStarMdlId[i] = modelId;
        } else {
            PlayerStarMdlId[i] = Hu3DModelLink(modelId);
        }
        Hu3DModelCameraSet(PlayerStarMdlId[i], HU3D_CAM2);
        Hu3DModelAttrSet(PlayerStarMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(PlayerStarMdlId[i], 1);
    }
    StarMdlId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 5));
    Hu3DModelAttrSet(StarMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(StarMdlId, HU3D_MOTATTR_LOOP|HU3D_MOTATTR_PAUSE);
    Hu3DMotionAttrSet(Hu3DMotionIDGet(StarMdlId), 1);
    Hu3DModelLayerSet(StarMdlId, 1);
    Hu3DModelCameraSet(StarMdlId, HU3D_CAM2);
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 6));
            PlayerCoinMdlId[i] = modelId;
        } else {
            PlayerCoinMdlId[i] = Hu3DModelLink(modelId);
        }
        Hu3DModelCameraSet(PlayerCoinMdlId[i], HU3D_CAM2);
        Hu3DModelAttrSet(PlayerCoinMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(PlayerCoinMdlId[i], 1);
    }
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0));
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            if(i == 0 && j == 0) {
                modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 10));
                PlayerNumMdlId[i][j] = modelId;
            } else {
                PlayerNumMdlId[i][j] = Hu3DModelLink(modelId);
            }
            PlayerNumAnimId[i][j] = Hu3DAnimCreate(animP, PlayerNumMdlId[i][j], "test");
            Hu3DModelCameraSet(PlayerNumMdlId[i][j], HU3D_CAM2);
            Hu3DModelAttrSet(PlayerNumMdlId[i][j], HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(PlayerNumMdlId[i][j], 1);
        }
    }
    for(i = 0; i < 3; i++) {
        BonusStarMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_partyresult, 7) + i);
        Hu3DModelAttrSet(BonusStarMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(BonusStarMdlId[i], HU3D_CAM1|HU3D_CAM2);
        Hu3DModelLayerSet(BonusStarMdlId[i], 1);
    }
    for(i = 0; i < 4; i++) {
        BlockMdlId[i] = Hu3DModelCreateData(DATANUM(DATA_partyresult, 15));
        Hu3DModelAttrSet(BlockMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(BlockMdlId[i], HU3D_CAM2);
        Hu3DMotionSpeedSet(BlockMdlId[i], 0.8f);
        Hu3DModelLayerSet(BlockMdlId[i], 1);
        for(j = 0; j < 10; j++) {
            if(i == 0) {
                NumberMdlId[i][j] = Hu3DModelCreateData(DATANUM(DATA_partyresult, 16) + j);
            } else {
                NumberMdlId[i][j] = Hu3DModelLink(NumberMdlId[0][j]);
            }
            Hu3DModelAttrSet(NumberMdlId[i][j], HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(NumberMdlId[i][j], HU3D_CAM2);
            Hu3DModelAttrSet(NumberMdlId[i][j], HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(NumberMdlId[i][j], 1);
        }
    }
    grpId = HuSprGrpCreate(2);
    WinnerSprGrpId = grpId;
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 1));
    for(i = 0; i < 2; i++) {
        sprId = HuSprCreate(animP, 100 - i, 0);
        HuSprGrpMemberSet(grpId, i, sprId);
        HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF|HUSPR_ATTR_LINEAR);
    }
    HuSprAttrSet(grpId, 1, HUSPR_ATTR_ADDCOL);
    HuSprGrpPosSet(grpId, 288.0f, 380.0f);
    DustAnimP = HuSprAnimDataRead(DATANUM(DATA_effect, 4));
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 2));
    for(i = 0; i < 4; i++) {
        parManId = StarEffAnimP[i] = Hu3DParManCreate(animP, 200, &StarEffParManParam);
        Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_TIMEUP|HU3D_PARMAN_ATTR_RANDSPEED70|HU3D_PARMAN_ATTR_RANDSCALE70|HU3D_PARMAN_ATTR_SCALEJITTER);
        Hu3DParManRotSet(parManId, 90.0f, 0.0f, 0.0f);
        Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
        Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 2);
        Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), HU3D_CAM2);
    }
    CircleAnimP = HuSprAnimDataRead(DATANUM(DATA_effect, 5));
    HuSprAnimLock(CircleAnimP);
    if(PResTeamF) {
        for(i = 0; i < 2; i++) {
            TeamNameWinId[i] = HuWinCreate(320.0f, (i * 100) + 100, 236, 42, 0);
            HuWinBGTPLvlSet(TeamNameWinId[i], 0.0f);
            HuWinPriSet(TeamNameWinId[i], 500);
            HuWinAttrSet(TeamNameWinId[i], HUWIN_ATTR_ALIGN_CENTER);
            HuWinMesSpeedSet(TeamNameWinId[i], 0);
            sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_partyresult, 40) + i), 600, 0);
            HuWinSprSet(TeamNameWinId[i], sprId, 118.0f, 4.0f);
            HuWinMesSet(TeamNameWinId[i], PResTeamNameMesGet(PResCharNo[i * 2], PResCharNo[(i * 2) + 1]));
            HuWinCenterPosSet(TeamNameWinId[i], 123.0f, 40.0f);
            HuWinScaleSet(TeamNameWinId[i], 0.8f, 0.8f);
            HuWinDispOff(TeamNameWinId[i]);
        }
    }
    PlayerHoverProc = HuPrcChildCreate(PlayerHover, 1000, 8192, 0, objman);
    Hu3DFogSet(4700.0f, 5500.0f, 160, 160, 96);
    omCameraViewSetMulti(HU3D_CAM1|HU3D_CAM2, &MainResultView);
}

/* 387 insns */
void PResResultMain(void)
{
    s16 i;
    s16 j;
    HUWIN *winP;
    float t;
    HuVecF pos;

    HuAudBGMPlay(21);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    MessWinId = HuWinExCreateFrame(16.0f, 376.0f, 544, 64, -1, 0);
    winP = &winData[MessWinId];
    winP->padMask = 1;
    HuWinExOpen(MessWinId);
    HuWinMesSet(MessWinId, 0x90001);
    HuAudFXPlay(751);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    for(i = 1; i <= 20; i++) {
        VECSubtract(&GuideLeftPos, &GuideCenterPos, &pos);
        VECScale(&pos, &pos, HuSin(90.0 * (i / 20.0)));
        VECAdd(&GuideCenterPos, &pos, &pos);
        pos.y += 50.0 * HuSin(180.0 * (i / 20.0));
        Hu3DModelPosSetV(GuideMdlId, &pos);
        Hu3DModelRotSet(GuideMdlId, 0.0f, 370.0 * (i / 20.0), 0.0f);
        HuPrcVSleep();
    }
    for(i = 1; i <= 45; i++) {
        for(j = 0; j < 4; j++) {
            if(i >= j * 3 && i <= (j * 3) + 30) {
                t = (i - (j * 3)) / 30.0;
                Hu3DModelPosSet(PResPlayerModelId[j], PlayerPosTbl[j].x, PlayerPosTbl[j].y, PlayerPosTbl[j].z - (4000.0 * (1.0 - t)));
                ResultCharFXUpdate(j);
                Hu3DModelRotSet(PResPlayerModelId[j], 40.0 * (1.0 - t), 0.0f, 0.0f);
                Hu3DModelScaleSet(PResPlayerModelId[j], 1.0f, 1.0f, 1.0f);
                Hu3DModelLayerSet(PResPlayerModelId[j], 0);
            }
        }
        if(i == 30 && PResTeamF) {
            TeamNameProc = HuPrcChildCreate(TeamNameMain, 1000, 8192, 0, objman);
        }
        HuPrcVSleep();
    }
    for(j = 0; j < 4; j++) {
        Hu3DModelLayerSet(PResPlayerModelId[j], 1);
    }
    DispStatTotal();
    if(GWBonusStarFGet()) {
        ResultBonusExec(0);
        ResultBonusExec(1);
        ResultBonusExec(2);
    }
    if(!PResTeamF) {
        PResResultFinal();
    } else {
        PResResultFinalTeam();
    }
    PResBtnAWait();
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    PResResultKill();
    HuWinExKill(MessWinId);
    Hu3DFogClear();
}

/* 182 insns */
void PResResultKill(void)
{
    s16 i;
    s16 j;
    HU3DMODEL *modelP;

    Hu3DModelKill(StageMdlId);
    Hu3DModelKill(GuideMdlId);
    for(i = 0; i < 4; i++) {
        modelP = &Hu3DData[PResPlayerModelId[i]];
        MTXIdentity(modelP->mtx);
    }
    for(i = 0; i < 4; i++) {
        Hu3DModelKill(PlayerStarMdlId[i]);
    }
    Hu3DModelKill(StarMdlId);
    for(i = 0; i < 4; i++) {
        Hu3DModelKill(PlayerCoinMdlId[i]);
    }
    for(i = 0; i < 4; i++) {
        for(j = 0; j < 4; j++) {
            Hu3DModelKill(PlayerNumMdlId[i][j]);
        }
    }
    for(i = 0; i < 3; i++) {
        Hu3DModelKill(BonusStarMdlId[i]);
    }
    for(i = 0; i < 4; i++) {
        Hu3DModelKill(BlockMdlId[i]);
        for(j = 0; j < 10; j++) {
            Hu3DModelKill(NumberMdlId[i][j]);
        }
    }
    HuSprGrpKill(WinnerSprGrpId);
    for(i = 0; i < 4; i++) {
        Hu3DParManKill(StarEffAnimP[i]);
    }
    HuSprAnimKill(CircleAnimP);
    if(PResTeamF) {
        for(i = 0; i < 2; i++) {
            HuWinKill(TeamNameWinId[i]);
        }
        HuPrcKill(TeamNameProc);
    }
    Hu3DLayerHookReset(1);
    HuPrcKill(PlayerHoverProc);
}

/* 152 insns */
static void TeamNameMain(void)
{
    s16 i;
    s16 j;
    float tpLvl;
    HUWIN *winP;

    while(1) {
        TeamNameFadeF = FALSE;
        for(j = 0; j < 2; j++) {
            HuWinDispOn(TeamNameWinId[j]);
        }
        for(i = 1; i <= 20; i++) {
            tpLvl = i / 20.0;
            /* retail bug: j runs 1..2, so it skips TeamNameWinId[0] and reads one past the
             * end (TeamNameWinId[2] is StarEffAnimP[0] in the GC .bss layout) */
            for(j = 1; j <= 2; j++) {
                winP = &winData[TeamNameWinId[j]];
                HuSprTPLvlSet(winP->grpId, 2, tpLvl);
                HuSprTPLvlSet(winP->grpId, 3, tpLvl);
            }
            TeamNamePosUpdate();
            HuPrcVSleep();
        }
        while(!TeamNameFadeF) {
            TeamNamePosUpdate();
            HuPrcVSleep();
        }
        for(i = 1; i <= 30; i++) {
            tpLvl = 1.0 - (i / 30.0);
            for(j = 1; j <= 2; j++) {
                winP = &winData[TeamNameWinId[j]];
                HuSprTPLvlSet(winP->grpId, 2, tpLvl);
                HuSprTPLvlSet(winP->grpId, 3, tpLvl);
            }
            TeamNamePosUpdate();
            HuPrcVSleep();
        }
        for(j = 0; j < 2; j++) {
            HuWinDispOff(TeamNameWinId[j]);
        }
        while(TeamNameFadeF) {
            HuPrcVSleep();
        }
    }
}

/* 53 insns */
static void TeamNamePosUpdate(void)
{
    s16 i;
    HuVecF pos;
    HuVecF pos2D;

    for(i = 0; i < 2; i++) {
        VECAdd(&PlayerPosTbl[i * 2], &PlayerPosTbl[(i * 2) + 1], &pos);
        VECScale(&pos, &pos, 0.5f);
        Hu3D3Dto2D(&pos, HU3D_CAM2, &pos2D);
        HuWinPosSet(TeamNameWinId[i], pos2D.x, pos2D.y - 10.0f);
    }
}

/* 1140 insns */
static void DispStatTotal(void)
{
    HuVecF pos[4];
    s16 num;
    s16 i;
    s16 j;
    s16 k;
    float t;

    HuWinMesSet(MessWinId, 0x90002);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    if (PResTeamF == FALSE) {
        num = 4;
        for (i = 0; i < 4; i++) {
            Hu3DParManColorSet(StarEffAnimP[i], 0);
            Hu3DParManAttrReset(StarEffAnimP[i], 1);
            pos[i] = PlayerPosTbl[i];
            pos[i].y += 70.0f;
        }
    } else {
        num = 2;
        for (i = 0; i < 2; i++) {
            Hu3DParManColorSet(StarEffAnimP[i], 0);
            Hu3DParManAttrReset(StarEffAnimP[i], 1);
            pos[i] = PlayerPosTbl[i];
            pos[i].x = PlayerPosTbl[i * 2].x + ((PlayerPosTbl[(i * 2) + 1].x - PlayerPosTbl[i * 2].x) / 2.0f);
            pos[i].y += 70.0f;
        }
    }
    /* stars grow in */
    for (i = 1; i <= 20; i++) {
        for (j = 0; j < num; j++) {
            Hu3DModelAttrReset(PlayerStarMdlId[j], HU3D_ATTR_DISPOFF);
            t = 0.1 + (0.9 * (i / 20.0));
            Hu3DModelScaleSet(PlayerStarMdlId[j], t, t, t);
            t = HuSin(90.0 * (i / 20.0));
            Hu3DModelPosSet(PlayerStarMdlId[j], pos[j].x, (200.0f * t) + (70.0f + pos[j].y), pos[j].z);
            Hu3DParManPosSet(StarEffAnimP[j], pos[j].x, (200.0f * t) + (70.0f + pos[j].y), pos[j].z - 20.0f);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < num; i++) {
        if (PResTeamF == FALSE) {
            StatNumSet(i, PResPlayer[i].unk004);
        } else {
            StatNumSet(i, PResPlayer[i * 2].unk004 + PResPlayer[(i * 2) + 1].unk004);
        }
        for (j = 0; j < 4; j++) {
            Hu3DModelRotSet(PlayerNumMdlId[i][j], 0.0f, 180.0f, 0.0f);
        }
    }
    /* star count flips round */
    for (i = 1; i <= 20; i++) {
        t = 180.0 * (1.0 - HuSin(90.0 * (i / 20.0)));
        for (j = 0; j < num; j++) {
            for (k = 0; k < 4; k++) {
                Hu3DModelRotSet(PlayerNumMdlId[j][k], 0.0f, t, 0.0f);
            }
            Hu3DModelRotSet(PlayerStarMdlId[j], 0.0f, 180.0f + t, 0.0f);
        }
        if (i == 10) {
            HuAudFXPlay(0x3E4);
        }
        HuPrcVSleep();
    }
    HuWinKeyWaitEntry(MessWinId);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    /* stars fly out */
    for (i = 1; i <= 20; i++) {
        t = 500.0 * (1.0 - HuCos(90.0 * (i / 20.0)));
        for (j = 0; j < num; j++) {
            for (k = 0; k < 4; k++) {
                Hu3DModelPosSet(PlayerNumMdlId[j][k], pos[j].x, t + (270.0f + pos[j].y), pos[j].z);
            }
            Hu3DModelPosSet(PlayerStarMdlId[j], pos[j].x, t + (270.0f + pos[j].y), pos[j].z);
            Hu3DParManPosSet(StarEffAnimP[j], pos[j].x, t + (270.0f + pos[j].y), pos[j].z - 20.0f);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < num; j++) {
        Hu3DModelAttrSet(PlayerStarMdlId[j], HU3D_ATTR_DISPOFF);
    }
    HuWinMesSet(MessWinId, 0x90003);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    /* coins grow in */
    for (i = 1; i <= 20; i++) {
        for (j = 0; j < num; j++) {
            Hu3DModelAttrReset(PlayerCoinMdlId[j], HU3D_ATTR_DISPOFF);
            t = 0.1 + (0.9 * (i / 20.0));
            Hu3DModelScaleSet(PlayerCoinMdlId[j], t, t, t);
            t = HuSin(90.0 * (i / 20.0));
            Hu3DModelPosSet(PlayerCoinMdlId[j], pos[j].x, (200.0f * t) + (70.0f + pos[j].y), pos[j].z);
            Hu3DParManPosSet(StarEffAnimP[j], pos[j].x, (200.0f * t) + (70.0f + pos[j].y), pos[j].z - 20.0f);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < num; i++) {
        if (PResTeamF == FALSE) {
            StatNumSet(i, PResPlayer[i].unk006);
        } else {
            StatNumSet(i, PResPlayer[i * 2].unk006 + PResPlayer[(i * 2) + 1].unk006);
        }
        for (j = 0; j < 4; j++) {
            Hu3DModelRotSet(PlayerNumMdlId[i][j], 0.0f, 180.0f, 0.0f);
        }
    }
    /* coin count flips round */
    for (i = 1; i <= 20; i++) {
        t = 180.0 * (1.0 - HuSin(90.0 * (i / 20.0)));
        for (j = 0; j < num; j++) {
            for (k = 0; k < 4; k++) {
                Hu3DModelRotSet(PlayerNumMdlId[j][k], 0.0f, t, 0.0f);
            }
            Hu3DModelRotSet(PlayerCoinMdlId[j], 0.0f, 180.0f + t, 0.0f);
        }
        if (i == 10) {
            HuAudFXPlay(0x3E5);
        }
        HuPrcVSleep();
    }
    HuWinKeyWaitEntry(MessWinId);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    /* coins fly out */
    for (i = 1; i <= 20; i++) {
        t = 500.0 * (1.0 - HuCos(90.0 * (i / 20.0)));
        for (j = 0; j < num; j++) {
            for (k = 0; k < 4; k++) {
                Hu3DModelPosSet(PlayerNumMdlId[j][k], pos[j].x, t + (270.0f + pos[j].y), pos[j].z);
            }
            Hu3DModelPosSet(PlayerCoinMdlId[j], pos[j].x, t + (270.0f + pos[j].y), pos[j].z);
            Hu3DParManPosSet(StarEffAnimP[j], pos[j].x, t + (270.0f + pos[j].y), pos[j].z - 20.0f);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < num; j++) {
        Hu3DModelAttrSet(PlayerCoinMdlId[j], HU3D_ATTR_DISPOFF);
        Hu3DParManAttrSet(StarEffAnimP[j], 1);
    }
}

/* 178 insns */
static void StatNumSet(s16 slot, s16 num)
{
    char str[8];
    u8 len;
    s16 i;
    float x;
    HU3DMODEL *modelP;

    if (num < 0 || num > 9999) {
        num = 0;
    }
    sprintf(str, "%d", num);
    len = strlen(str);
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrSet(PlayerNumMdlId[slot][i], HU3D_ATTR_DISPOFF);
    }
    x = -((len * 30) / 2 - 15);
    for (i = 0; i < len; i++) {
        Hu3DAnimBankSet(PlayerNumAnimId[slot][i], (u16)(str[i] & 0xF));
        Hu3DModelAttrReset(PlayerNumMdlId[slot][i], HU3D_ATTR_DISPOFF);
        modelP = &Hu3DData[PlayerNumMdlId[slot][i]];
        PSMTXTrans(modelP->mtx, x, 0.0f, 25.0f);
        modelP = &Hu3DData[PlayerStarMdlId[slot]];
        if (modelP->attr & HU3D_ATTR_DISPOFF) {
            modelP = &Hu3DData[PlayerCoinMdlId[slot]];
        }
        Hu3DModelPosSetV(PlayerNumMdlId[slot][i], &modelP->pos);
        Hu3DModelScaleSet(PlayerNumMdlId[slot][i], 0.8f, 0.8f, 0.8f);
        x += 30.0f;
    }
}

/* 0x170 */ static u32 BonusStarMessTbl[5][3] = {
    { 0x00090004, 0x0009000B, 0x0009000E }, /* [0] intro, per bonus */
    { 0x00090005, 0x0009000C, 0x0009000F }, /* [1] two players tied */
    { 0x00090006, 0x0009000D, 0x00090010 }, /* [2] three players tied */
    { 0x00090007, 0x00090007, 0x00090007 }, /* [3] all four tied: no award */
    { 0x0009001B, 0x0009001C, 0x0009001D }  /* [4] nobody qualifies (best figure 0) */
};

/* 1902 insns */
static void ResultBonusExec(s16 bonusNo)
{
    HuVecF posTbl[4];
    HuVecF winPos[4];
    HuVecF starPos;
    s16 win[4];
    s16 motF[4];
    s16 i;
    s16 j;
    s16 n;
    s16 winNo;
    s16 teamNo;
    u32 max;
    s32 seNo;
    float t;
    float z;
    float y;

    Hu3DParManColorSet(StarEffAnimP[0], bonusNo + 1);
    if (PResTeamF == FALSE) {
        HuWinMesSet(MessWinId, BonusStarMessTbl[0][bonusNo]);
    } else {
        HuWinMesSet(MessWinId, bonusNo + 0x90022);
    }
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    for (i = 0; i < 4; i++) {
        posTbl[i] = PlayerPosTbl[i];
    }
    starPos.x = PlayerPosTbl[0].x + ((PlayerPosTbl[3].x - PlayerPosTbl[0].x) / 2.0f);
    starPos.y = 70.0f + (270.0f + PlayerPosTbl[0].y);
    starPos.z = PlayerPosTbl[0].z;
    Hu3DModelPosSetV(BonusStarMdlId[bonusNo], &starPos);
    Hu3DParManPosSet(StarEffAnimP[0], starPos.x, starPos.y, starPos.z - 50.0f);
    seNo = HuAudFXPlay(0x3E6);
    HuAudFXPlay(0x1F);
    /* the bonus star appears */
    for (i = 1; i <= 20; i++) {
        Hu3DModelAttrReset(BonusStarMdlId[bonusNo], HU3D_ATTR_DISPOFF);
        t = 1.5 * (1.0 - HuCos(90.0 * (i / 20.0)));
        Hu3DModelScaleSet(BonusStarMdlId[bonusNo], t, t, t);
        if (i == 10) {
            Hu3DParManAttrReset(StarEffAnimP[0], 1);
        }
        HuPrcVSleep();
    }
    /* and circles over the players */
    for (i = 1; i <= 120; i++) {
        if (i < 60) {
            t = 180.0 * (1.0 - HuCos(90.0 * (i / 60.0)));
        } else {
            t = 180.0 + (180.0 * HuSin(90.0 * ((i - 60) / 60.0)));
        }
        z = (starPos.z + (100.0 * HuCos(t))) - 100.0;
        y = starPos.y + (40.0 * HuSin(2.0f * t));
        Hu3DModelPosSet(BonusStarMdlId[bonusNo], starPos.x + (350.0 * HuSin(t)), y, z);
        z = ((starPos.z + (100.0 * HuCos(t))) - 100.0) - 50.0;
        Hu3DParManPosSet(StarEffAnimP[0], starPos.x + (350.0 * HuSin(t)), starPos.y, z);
        Hu3DModelRotSet(BonusStarMdlId[bonusNo], 0.0f, 25.0 * -HuSin(360.0 * (i / 120.0)), 0.0f);
        HuAudFXPanning(seNo, 64 + (s32)(32.0 * HuSin(t)));
        HuPrcVSleep();
    }
    /* team mode: the partner's figure is added to the even (first) slot of the team; the copy is changed */
    if (PResTeamF != FALSE) {
        for (i = max = 0; i < 4; i += 2) {
            PResPlayer[i].unk00A[bonusNo] += PResPlayer[i + 1].unk00A[bonusNo];
            PResPlayer[i + 1].unk00A[bonusNo] = 0;
        }
    }
    for (i = max = 0; i < 4; i++) {
        if (PResPlayer[i].unk00A[bonusNo] >= max) {
            max = PResPlayer[i].unk00A[bonusNo];
        }
    }
    if (max != 0) {
        for (i = n = 0; i < 4; i++) {
            if (max == PResPlayer[i].unk00A[bonusNo]) {
                win[n++] = i;
            }
        }
    } else {
        /* nobody qualifies: no bonus star */
        HuPrcSleep(60);
        n = 0;
        if (PResTeamF == FALSE) {
            HuWinMesSet(MessWinId, BonusStarMessTbl[4][bonusNo]);
        } else {
            HuWinMesSet(MessWinId, bonusNo + 0x9001F);
        }
        HuAudFXPlay(0x20);
        HuAudFXPlay(0x2F0);
        for (i = 0; i < 4; i++) {
            CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        for (i = 1; i <= 20; i++) {
            t = 1.5 * (1.0 - HuSin(90.0 * (i / 20.0)));
            Hu3DModelScaleSet(BonusStarMdlId[bonusNo], t, t, t);
            if (i == 5) {
                Hu3DParManAttrSet(StarEffAnimP[0], 1);
            }
            if (i == 10) {
                HuAudFXStop(seNo);
                for (j = 0; j < 4; j++) {
                    CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(BonusStarMdlId[bonusNo], HU3D_ATTR_DISPOFF);
        return;
    }
    HuPrcSleep(30);
    HuAudFXPlay(0x20);
    if (PResTeamF == FALSE) {
        if (n == 2) {
            HuWinMesSet(MessWinId, BonusStarMessTbl[1][bonusNo]);
            HuAudFXPlay(0x2EF);
            PResComInputWait(MessWinId);
            HuWinMesWait(MessWinId);
        } else if (n == 3) {
            HuWinMesSet(MessWinId, BonusStarMessTbl[2][bonusNo]);
            HuAudFXPlay(0x2EF);
            PResComInputWait(MessWinId);
            HuWinMesWait(MessWinId);
        } else if (n == 4) {
            /* all four tied: no bonus star */
            HuWinMesSet(MessWinId, BonusStarMessTbl[3][bonusNo]);
            HuAudFXPlay(0x2EF);
            for (i = 0; i < 4; i++) {
                CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            PResComInputWait(MessWinId);
            HuWinMesWait(MessWinId);
            for (i = 1; i <= 20; i++) {
                t = 1.5 * (1.0 - HuSin(90.0 * (i / 20.0)));
                Hu3DModelScaleSet(BonusStarMdlId[bonusNo], t, t, t);
                if (i == 5) {
                    Hu3DParManAttrSet(StarEffAnimP[0], 1);
                }
                if (i == 10) {
                    HuAudFXStop(seNo);
                    for (j = 0; j < 4; j++) {
                        CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                }
                HuPrcVSleep();
            }
            Hu3DModelAttrSet(BonusStarMdlId[bonusNo], HU3D_ATTR_DISPOFF);
            return;
        }
        HuAudFXStop(seNo);
        for (i = 0; i < n; i++) {
            winPos[i] = posTbl[win[i]];
            winPos[i].y += 340.0f;
        }
        BonusFadeCreate(BonusStarMdlId[bonusNo], n, winPos);
        for (i = 0; i < n; i++) {
            HuWinInsertMesSet(MessWinId, PResCharNo[win[i]], (s32)i);
        }
        if (n == 1) {
            HuWinMesSet(MessWinId, 0x90008);
        } else if (n == 2) {
            HuWinMesSet(MessWinId, 0x90009);
        } else if (n == 3) {
            HuWinMesSet(MessWinId, 0x9000A);
        }
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuPrcSleep(30);
        /* a star drops onto each winner */
        for (j = 1; j <= 30; j++) {
            for (i = 0; i < n; i++) {
                t = j / 30.0;
                Hu3DModelAttrReset(PlayerStarMdlId[i], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(PlayerStarMdlId[i], posTbl[win[i]].x, 70.0 + (100.0 + (posTbl[win[i]].y + (170.0 * HuCos(90.0f * t)))), posTbl[win[i]].z);
                Hu3DParManPosSet(StarEffAnimP[i], posTbl[win[i]].x, 70.0 + (100.0 + (posTbl[win[i]].y + (170.0 * HuCos(90.0f * t)))), posTbl[win[i]].z - 20.0f);
                Hu3DModelRotSet(PlayerStarMdlId[i], 0.0f, 360.0f * t, 0.0f);
                t = 1.2 * HuCos(90.0f * t);
                Hu3DModelScaleSet(PlayerStarMdlId[i], t, t, t);
                if (j == 10) {
                    Hu3DParManAttrSet(StarEffAnimP[i], 1);
                }
            }
            if (j == 20) {
                motF[0] = motF[1] = motF[2] = motF[3] = 0;
                for (i = 0; i < n; i++) {
                    ResultCharFXPlay(PResCharNo[win[i]], 0x1F8);
                    CharMotionShiftSet(PResCharNo[win[i]], PResPlayerMotion[win[i]][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    motF[win[i]] = 1;
                }
                for (i = 0; i < 4; i++) {
                    if (motF[i] == 0) {
                        CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                }
            }
            HuPrcVSleep();
        }
        HuPrcSleep(60);
        for (i = 0; i < 4; i++) {
            CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
        HuPrcSleep(8);
        /* the award: +1 star to each winner, in the local PResPlayer copy only */
        for (i = 0; i < n; i++) {
            PResPlayer[win[i]].unk004++;
        }
    } else {
        if (n > 1) {
            /* the teams are tied: no bonus star */
            HuWinMesSet(MessWinId, 0x9001E);
            HuAudFXPlay(0x2EF);
            for (i = 0; i < 4; i++) {
                CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            PResComInputWait(MessWinId);
            HuWinMesWait(MessWinId);
            for (i = 1; i <= 20; i++) {
                t = 1.5 * (1.0 - HuSin(90.0 * (i / 20.0)));
                Hu3DModelScaleSet(BonusStarMdlId[bonusNo], t, t, t);
                if (i == 5) {
                    Hu3DParManAttrSet(StarEffAnimP[0], 1);
                }
                if (i == 10) {
                    HuAudFXStop(seNo);
                    for (j = 0; j < 4; j++) {
                        CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                }
                HuPrcVSleep();
            }
            Hu3DModelAttrSet(BonusStarMdlId[bonusNo], HU3D_ATTR_DISPOFF);
            return;
        }
        HuAudFXStop(seNo);
        winNo = win[0];
        winPos[0].x = PlayerPosTbl[winNo].x + ((PlayerPosTbl[winNo + 1].x - PlayerPosTbl[winNo].x) / 2.0f);
        winPos[0].y = 70.0f + (270.0f + posTbl[0].y);
        winPos[0].z = posTbl[0].z;
        BonusFadeCreate(BonusStarMdlId[bonusNo], 1, winPos);
        HuWinInsertMesSet(MessWinId, PResTeamNameMesGet(PResCharNo[winNo], PResCharNo[winNo + 1]), 0);
        HuWinMesSet(MessWinId, 0x90008);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuPrcSleep(30);
        for (j = 1; j <= 30; j++) {
            t = j / 30.0;
            Hu3DModelAttrReset(PlayerStarMdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(PlayerStarMdlId[0], winPos[0].x, (winPos[0].y - 170.0f) + (170.0 * HuCos(90.0f * t)), winPos[0].z);
            Hu3DParManPosSet(StarEffAnimP[0], winPos[0].x, (winPos[0].y - 170.0f) + (170.0 * HuCos(90.0f * t)), winPos[0].z - 20.0f);
            Hu3DModelRotSet(PlayerStarMdlId[0], 0.0f, 360.0f * t, 0.0f);
            t = 1.2 * HuCos(90.0f * t);
            Hu3DModelScaleSet(PlayerStarMdlId[0], t, t, t);
            if (j == 10) {
                Hu3DParManAttrSet(StarEffAnimP[0], 1);
            }
            if (j == 20) {
                teamNo = winNo & 2;
                for (i = 0; i < 2; i++) {
                    CharMotionShiftSet(PResCharNo[teamNo + i], PResPlayerMotion[teamNo + i][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    ResultCharFXPlay(PResCharNo[teamNo + i], 0x1F8);
                }
                teamNo = (winNo & 2) ^ 2;
                for (i = 0; i < 2; i++) {
                    CharMotionShiftSet(PResCharNo[teamNo + i], PResPlayerMotion[teamNo + i][3], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            HuPrcVSleep();
        }
        HuPrcSleep(60);
        for (i = 0; i < 4; i++) {
            CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
        HuPrcSleep(8);
        /* the award: +1 star to the team's first slot (it holds the team sum), local copy only */
        PResPlayer[winNo].unk004++;
    }
}

/* 922 insns */
void PResResultFinal(void)
{
    s16 i;
    s16 j;
    s16 winner;
    s32 seNo;
    s16 tieNum;
    s16 time;
    s32 streamNo;
    float scale;
    float speed;
    HuVecF rot[4];
    HuVecF centerPos;
    HuVecF pos;
    s16 order[4];
    s16 rank[4];
    s16 posNo[4];

    centerPos.x = PlayerPosTbl[0].x + (PlayerPosTbl[3].x - PlayerPosTbl[0].x) / 2;
    centerPos.y = PlayerPosTbl[0].y;
    centerPos.z = PlayerPosTbl[0].z;
    for (i = 0; i < 4; i++) {
        rot[i].x = (s32)frandmod(10) - 5;
        rot[i].y = (s32)frandmod(10) - 5;
        rot[i].z = (s32)frandmod(10) - 5;
    }
    tieNum = PResResultOrderGet(order, rank, posNo);
    HuWinMesSet(MessWinId, 0x90011);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    HuAudSStreamPauseFadeOut(0, TRUE, 500);
    HuWinMesSet(MessWinId, 0x90012);
    streamNo = HuAudJinglePlay(0x46);
    for (i = 0, speed = 1.0f; i < 60; i++) {
        Hu3DMotionSpeedSet(StageMdlId, speed);
        speed += 0.1;
        if (i == 20) {
            seNo = HuAudFXPlay(0x3E9);
            for (j = 0; j < 4; j++) {
                CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][5], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
        HuPrcVSleep();
    }
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    HuWinExClose(MessWinId);
    omCameraViewMoveMulti(4, &FinalResultView, 10, 1);
    if (tieNum > 1) {
        HuPrcSleep(60);
        HuWinExOpen(MessWinId);
        HuWinMesSet(MessWinId, 0x90013);
        HuAudFXPlay(0x2EF);
        HuAudSStreamFadeOut(streamNo, 1000);
        HuAudSStreamPause(0, FALSE);
        omCameraViewMoveMulti(4, &MainResultView, 30, 0);
        for (i = 0; i < 30; i++) {
            Hu3DMotionSpeedSet(StageMdlId, speed);
            if (i == 10) {
                for (j = 0; j < 4; j++) {
                    CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
                HuAudFXStop(seNo);
            }
            speed -= 0.2;
            HuPrcVSleep();
        }
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuWinMesSet(MessWinId, 0x90014);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        order[0] = PResResultTie();
        PResPlayer[order[0]].unk008 = 1;
        HuWinMesSet(MessWinId, 0x90016);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuAudSStreamAllFadeOut(500);
        HuWinExClose(MessWinId);
        omCameraViewMoveMulti(4, &FinalResultView, 10, 1);
        HuAudJinglePlay(0x46);
        for (i = 0; i < 60; i++) {
            Hu3DMotionSpeedSet(StageMdlId, speed);
            speed += 0.1;
            if (i == 20) {
                seNo = HuAudFXPlay(0x3E9);
                for (j = 0; j < 4; j++) {
                    CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][5], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            HuPrcVSleep();
        }
        HuPrcSleep(60);
        for (j = 0; j < 60; j++) {
            for (i = 0; i < 4; i++) {
                if (j < i * 5 || j > i * 5 + 30 || i == order[0]) {
                    continue;
                }
                if (j == i * 5) {
                    CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    HuAudFXPlay(0x3EA);
                }
                scale = j - i * 5;
                Hu3DModelPosSet(PResPlayerModelId[i], PlayerPosTbl[i].x, PlayerPosTbl[i].y, PlayerPosTbl[i].z - 150.0f * scale);
                Hu3DModelRotSet(PResPlayerModelId[i], scale * rot[i].x, scale * rot[i].y, scale * rot[i].z);
                ResultCharFXUpdate(i);
                scale = 0.3 + 0.7 * (1.0 - scale / 30.0);
                Hu3DModelScaleSet(PResPlayerModelId[i], scale, scale, scale);
                Hu3DModelLayerSet(PResPlayerModelId[i], 0);
                if (j == i * 5 + 30) {
                    Hu3DModelAttrSet(PResPlayerModelId[i], HU3D_ATTR_DISPOFF);
                }
            }
            HuPrcVSleep();
        }
    } else {
        for (i = 3; i >= 1; i--) {
            time = frandmod(60) + 60;
            HuPrcSleep(time);
            winner = order[i];
            CharMotionShiftSet(PResCharNo[winner], PResPlayerMotion[winner][6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            HuAudFXPlay(0x3EA);
            for (j = 1; j <= 30; j++) {
                Hu3DModelPosSet(PResPlayerModelId[winner], PlayerPosTbl[winner].x, PlayerPosTbl[winner].y, PlayerPosTbl[winner].z - (j * 150));
                ResultCharFXUpdate(winner);
                scale = 0.3 + 0.7 * (1.0 - j / 30.0);
                Hu3DModelScaleSet(PResPlayerModelId[winner], scale, scale, scale);
                Hu3DModelRotSet(PResPlayerModelId[winner], j * rot[winner].x, j * rot[winner].y, j * rot[winner].z);
                Hu3DModelLayerSet(PResPlayerModelId[winner], 0);
                HuPrcVSleep();
            }
            Hu3DModelAttrSet(PResPlayerModelId[winner], HU3D_ATTR_DISPOFF);
        }
    }
    HuWinExOpen(MessWinId);
    HuWinInsertMesSet(MessWinId, PResCharNo[order[0]], 0);
    HuWinMesSet(MessWinId, 0x90017);
    winner = order[0];
    for (j = 0; j < 4; j++) {
        CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
    }
    for (i = 1; i <= 60; i++) {
        scale = i / 60.0;
        PSVECSubtract(&centerPos, &PlayerPosTbl[winner], &pos);
        PSVECScale(&pos, &pos, sin(M_PI * (90.0f * scale) / 180.0));
        PSVECAdd(&PlayerPosTbl[winner], &pos, &pos);
        Hu3DModelPosSetV(PResPlayerModelId[winner], &pos);
        ResultCharFXUpdate(winner);
        speed -= 0.1;
        Hu3DMotionSpeedSet(StageMdlId, speed);
        if (i == 30) {
            HuAudFXStop(seNo);
        }
        HuPrcVSleep();
    }
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    HuAudSStreamAllFadeOut(500);
    HuAudBGMPlay(0x47);
    HuWinExClose(MessWinId);
    PResResultWinnerExec(CharModelHeightGet(PResCharNo[winner]), winner, -1);
    PResBtnAWait();
}

/* 766 insns */
int PResResultTie(void)
{
    s16 i;
    s16 winner;
    s16 j;
    HUWINID winId;
    s16 num;
    s16 max;
    s16 playerNo;
    s16 retry;
    s16 k;
    HUPROCESS *proc;
    float t;
    HuVecF centerPos;
    HuVecF vec;
    HuVecF pos;
    s16 order[4];
    s16 rank[4];
    s16 posNo[4];

    centerPos.x = PlayerPosTbl[0].x + (PlayerPosTbl[3].x - PlayerPosTbl[0].x) / 2;
    centerPos.y = 70.0f + (100.0f + PlayerPosTbl[0].y);
    centerPos.z = PlayerPosTbl[0].z;
    retry = 0;
    while (1) {
        for (i = 0; i < 10; i++) {
            BlockResult[i] = i + 1;
        }
        for (i = 0; i < 50; i++) {
            j = frandmod(10);
            k = frandmod(10);
            max = BlockResult[j];
            BlockResult[j] = BlockResult[k];
            BlockResult[k] = max;
        }
        if (PResTeamF == FALSE) {
            num = PResResultOrderGet(order, rank, posNo);
            break;
        }
        num = 4;
        for (i = 0; i < 4; i++) {
            order[i] = i;
        }
        if (BlockResult[0] + BlockResult[1] != BlockResult[2] + BlockResult[3]) {
            break;
        }
        if (++retry >= 100) {
            if ((s32)frandmod(100) < 50) {
                BlockResult[0] = 8;
                BlockResult[1] = 9;
                BlockResult[2] = 6;
                BlockResult[3] = 5;
            } else {
                BlockResult[0] = 5;
                BlockResult[1] = 7;
                BlockResult[2] = 6;
                BlockResult[3] = 9;
            }
            break;
        }
    }
    HuAudFXPlay(0x35C);
    HuAudFXPlay(0x2F9);
    for (j = 1; j <= 10; j++) {
        t = j / 10.0;
        for (i = 0; i < num; i++) {
            playerNo = order[i];
            Hu3DModelAttrReset(BlockMdlId[playerNo], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(BlockMdlId[playerNo], HU3D_MOTATTR_LOOP);
            pos = PlayerPosTbl[playerNo];
            pos.y += 370.0f;
            PSVECSubtract(&pos, &centerPos, &vec);
            PSVECScale(&vec, &vec, sin(M_PI * (90.0f * t) / 180.0));
            PSVECAdd(&centerPos, &vec, &vec);
            Hu3DModelPosSetV(BlockMdlId[playerNo], &vec);
        }
        HuPrcVSleep();
    }
    BlockNum = 0;
    BlockMode = FALSE;
    for (i = 0; i < num; i++) {
        proc = HuPrcChildCreate(BlockPlayerProc, 1000, 0x2000, 0, objman);
        proc->property = (void *)(s32)order[i];
        BlockPlayerMode[i] = 0;
        BlockSeNo[order[i]] = HuAudFXPlay(0x2F7);
    }
    winId = HuWinCreate(-10000.0f, 330.0f, 560, 42, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinPriSet(winId, 10);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSpeedSet(winId, 0);
    if (PResTeamF != FALSE) {
        HuWinPosSet(winId, 40.0f, 300.0f);
    }
    HuWinMesSet(winId, 0x20009);
    while (BlockNum < num) {
        HuPrcVSleep();
    }
    HuWinKill(winId);
    if (PResTeamF == FALSE) {
        for (i = max = 0; i < num; i++) {
            if (max < BlockResult[order[i]]) {
                winner = order[i];
                max = BlockResult[winner];
            }
        }
        HuWinInsertMesSet(MessWinId, PResCharNo[winner], 0);
        HuWinMesSet(MessWinId, 0x90015);
        ResultCharFXPlay(PResCharNo[winner], 0x1F8);
        CharMotionShiftSet(PResCharNo[winner], PResPlayerMotion[winner][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        for (i = 0; i < 4; i++) {
            if (i != winner) {
                CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][3], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
            }
        }
        HuPrcSleep(60);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
    } else {
        if (BlockResult[0] + BlockResult[1] > BlockResult[2] + BlockResult[3]) {
            winner = 0;
        } else {
            winner = 1;
        }
        HuWinInsertMesSet(MessWinId, PResCharNo[winner * 2], 0);
        HuWinInsertMesSet(MessWinId, PResCharNo[winner * 2 + 1], 1);
        HuWinInsertMesSet(MessWinId, PResTeamNameMesGet(PResCharNo[winner * 2], PResCharNo[winner * 2 + 1]), 2);
        HuWinMesSet(MessWinId, 0x90019);
        if (winner == 0) {
            ResultCharFXPlay(PResCharNo[0], 0x1F8);
            ResultCharFXPlay(PResCharNo[1], 0x1F8);
            CharMotionShiftSet(PResCharNo[0], PResPlayerMotion[0][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[1], PResPlayerMotion[1][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[2], PResPlayerMotion[2][3], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[3], PResPlayerMotion[3][3], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
        } else {
            ResultCharFXPlay(PResCharNo[2], 0x1F8);
            ResultCharFXPlay(PResCharNo[3], 0x1F8);
            CharMotionShiftSet(PResCharNo[0], PResPlayerMotion[0][3], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[1], PResPlayerMotion[1][3], 0.0f, 16.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[2], PResPlayerMotion[2][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            CharMotionShiftSet(PResCharNo[3], PResPlayerMotion[3][2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
        HuPrcSleep(60);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
    }
    BlockMode = TRUE;
    for (i = 0; i < 4; i++) {
        CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
    }
    return winner;
}

/* 235 insns */
static void BlockPlayerProc(void)
{
    s16 playerNo;
    s16 i;
    HUPROCESS *proc;
    float t;
    float height;
    HuVecF pos;

    proc = HuPrcCurrentGet();
    playerNo = (s32)proc->property;
    if (GwPlayerConf[PResPlayerOrder[playerNo]].type == 0) {
        while (!(HuPadBtnDown[GwPlayerConf[PResPlayerOrder[playerNo]].padNo] & PAD_BUTTON_A)) {
            HuPrcVSleep();
        }
    } else {
        i = frandmod(30) + 30;
        HuPrcSleep(i);
    }
    CharMotionShiftSet(PResCharNo[playerNo], PResPlayerMotion[playerNo][1], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
    for (i = 1; i <= 30; i++) {
        t = i / 30.0;
        pos = PlayerPosTbl[playerNo];
        height = 300.0f - CharModelHeightGet(PResCharNo[playerNo]);
        pos.y += height * sin(M_PI * (180.0f * t) / 180.0);
        Hu3DModelPosSetV(PResPlayerModelId[playerNo], &pos);
        ResultCharFXUpdate(playerNo);
        if (i >= 12 && i <= 15) {
            pos = PlayerPosTbl[playerNo];
            pos.y += (i - 7) * 5 + 370;
            Hu3DModelPosSetV(BlockMdlId[playerNo], &pos);
            if (i == 15) {
                HuAudFXStop(BlockSeNo[playerNo]);
                HuAudFXPlay(0x2FA);
                proc = HuPrcChildCreate(BlockProc, 1000, 0x2000, 0, objman);
                proc->property = (void *)(s32)playerNo;
            }
        }
        HuPrcVSleep();
    }
    CharMotionShiftSet(PResCharNo[playerNo], PResPlayerMotion[playerNo][0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 0x1AC */ static HU3DPARMANPARAM BlockDustParManParam = {
    30, 0, 20.0f, 10.0f, 180.0f,
    { 0.0f, 0.0f, 0.0f },
    6.0f, 0.97f, 50.0f, 1.03f,
    2,
    { { 255, 255, 255, 255 }, { 192, 192, 192, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 255, 255, 0 }, { 192, 192, 192, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};

/* 810 insns */
static void BlockProc(void)
{
    HU3DMODEL *modelP;
    s16 i;
    s16 j;
    s16 playerNo;
    HU3DPARMANID parManId;
    s16 sum;
    s16 partner;
    HUPROCESS *proc;
    float t;
    double bounce;
    HuVecF vec;
    HuVecF pos;
    HuVecF centerPos;
    HU3DMODELID mdlId[2];

    proc = HuPrcCurrentGet();
    playerNo = (s32)proc->property;
    modelP = &Hu3DData[BlockMdlId[playerNo]];
    parManId = Hu3DParManCreate(DustAnimP, 50, &BlockDustParManParam);
    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_TIMEUP | HU3D_PARMAN_ATTR_RANDSPEED70 | HU3D_PARMAN_ATTR_RANDSCALE70);
    Hu3DParManRotSet(parManId, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 2);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), HU3D_CAM2);
    Hu3DParManPosSet(parManId, modelP->pos.x, modelP->pos.y, 50.0f + modelP->pos.z);
    Hu3DParManTimeLimitSet(parManId, 2);
    Hu3DParManAttrReset(parManId, HU3D_PARMAN_ATTR_TIMEUP);
    HuPrcSleep(3);
    Hu3DModelAttrSet(BlockMdlId[playerNo], HU3D_ATTR_DISPOFF);
    HuPrcSleep(10);
    if (BlockResult[playerNo] > 9) {
        mdlId[0] = NumberMdlId[playerNo][BlockResult[playerNo] / 10];
        Hu3DModelAttrReset(mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(mdlId[0], modelP->pos.x - 40.0f, modelP->pos.y, modelP->pos.z);
        mdlId[1] = NumberMdlId[playerNo][BlockResult[playerNo] % 10];
        Hu3DModelAttrReset(mdlId[1], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(mdlId[1], 40.0f + modelP->pos.x, modelP->pos.y, modelP->pos.z);
    } else {
        mdlId[0] = NumberMdlId[playerNo][BlockResult[playerNo]];
        Hu3DModelAttrReset(mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(mdlId[0], modelP->pos.x, modelP->pos.y, modelP->pos.z);
        mdlId[1] = -1;
    }
    for (j = 1; j <= 20; j++) {
        t = j / 20.0;
        for (i = 0; i < 2; i++) {
            if (mdlId[i] == -1) {
                continue;
            }
            Hu3DModelRotSet(mdlId[i], 0.0f, 360.0f * t, 0.0f);
            Hu3DModelScaleSet(mdlId[i], 0.5 + 0.5 * t, 0.5 + 0.5 * t, 0.5 + 0.5 * t);
            if (mdlId[1] == -1) {
                Hu3DModelPosSet(mdlId[i], modelP->pos.x, modelP->pos.y - 50.0 * (1.0 - cos(M_PI * (90.0f * t) / 180.0)), modelP->pos.z);
            } else {
                Hu3DModelPosSet(mdlId[i], modelP->pos.x - 40.0f + i * 80, modelP->pos.y - 50.0 * (1.0 - cos(M_PI * (90.0f * t) / 180.0)), modelP->pos.z);
            }
        }
        HuPrcVSleep();
    }
    if (PResTeamF != FALSE) {
        partner = playerNo ^ 1;
        BlockPlayerMode[playerNo] = 2;
        while (BlockPlayerMode[partner] != 2) {
            HuPrcVSleep();
        }
        HuPrcSleep(30);
        centerPos = PlayerPosTbl[playerNo];
        centerPos.x = (PlayerPosTbl[playerNo].x + PlayerPosTbl[partner].x) / 2;
        centerPos.y = modelP->pos.y - 50.0f;
        for (j = 0; j < 10; j++) {
            t = j / 10.0;
            for (i = 0; i < 2; i++) {
                if (mdlId[i] == -1) {
                    continue;
                }
                pos = modelP->pos;
                pos.y -= 50.0f;
                if (mdlId[1] != -1) {
                    pos.x += i * 80 - 40;
                }
                PSVECSubtract(&centerPos, &pos, &vec);
                PSVECScale(&vec, &vec, sin(M_PI * (90.0f * t) / 180.0));
                PSVECAdd(&pos, &vec, &vec);
                Hu3DModelPosSetV(mdlId[i], &vec);
            }
            HuPrcVSleep();
        }
        Hu3DModelAttrSet(mdlId[0], HU3D_ATTR_DISPOFF);
        if (mdlId[1] != -1) {
            Hu3DModelAttrSet(mdlId[1], HU3D_ATTR_DISPOFF);
        }
        sum = BlockResult[playerNo] + BlockResult[partner];
        if (playerNo & 1) {
            if (sum >= 10) {
                mdlId[0] = NumberMdlId[playerNo][sum / 10];
                Hu3DModelAttrReset(mdlId[0], HU3D_ATTR_DISPOFF);
                vec = centerPos;
                vec.x -= 40.0f;
                Hu3DModelPosSetV(mdlId[0], &vec);
            }
        } else {
            mdlId[0] = NumberMdlId[playerNo][sum % 10];
            Hu3DModelAttrReset(mdlId[0], HU3D_ATTR_DISPOFF);
            vec = centerPos;
            if (sum >= 10) {
                vec.x += 40.0f;
            }
            Hu3DModelPosSetV(mdlId[0], &vec);
        }
        HuAudFXPlay(0x3ED);
        for (j = 1; j <= 15; j++) {
            bounce = 0.2 * sin(M_PI * (180.0 + 360.0 * (j / 15.0)) / 180.0);
            t = 0.3 + 0.7 * sin(M_PI * (90.0 * (j / 15.0)) / 180.0) + bounce;
            Hu3DModelScaleSet(mdlId[0], t, t, t);
            HuPrcVSleep();
        }
    }
    BlockNum++;
    while (BlockMode == FALSE) {
        HuPrcVSleep();
    }
    for (j = 1; j <= 10; j++) {
        t = cos(M_PI * (90.0 * (j / 10.0)) / 180.0);
        for (i = 0; i < 10; i++) {
            Hu3DModelTPLvlSet(NumberMdlId[playerNo][i], t);
            Hu3DModelScaleSet(NumberMdlId[playerNo][i], 1.0 + 0.5 * (1.0 - t), 1.0 + 0.5 * (1.0 - t), 1.0 + 0.5 * (1.0 - t));
        }
        HuPrcVSleep();
    }
    Hu3DParManKill(parManId);
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 0x1FC */ static s8 WinnerRotXTbl[13] = { 0, 15, 0, 35, 25, 0, 0, 0, 0, 20, 20, 20, 20 };

/* 1108 insns */
void PResResultWinnerExec(float height, s16 winner, s16 winner2)
{
    HuVecF winner2Pos;
    HuVecF winnerPos;
    HuVecF starPos;
    float t;
    float radius;
    float rotY;
    float zoom;
    float centerY;
    float pan;
    s32 seNo;
    s16 i;
    s16 j;
    s16 charNo;
    s16 boardNo;
    s16 starSum;
    s32 board;
    HU3DMODEL *modelP;

    Hu3DParManColorSet(StarEffAnimP[0], 0);
    Hu3DParManAttrReset(StarEffAnimP[0], 1);
    zoom = CZoomM[2];
    centerY = CenterM[2].y;
    Hu3DModelAttrReset(StarMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(StarMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelScaleSet(StarMdlId, 0.6f, 0.6f, 0.6f);
    modelP = &Hu3DData[PResPlayerModelId[winner]];
    winnerPos = modelP->pos;
    if (winner2 != -1) {
        modelP = &Hu3DData[PResPlayerModelId[winner2]];
        winner2Pos = modelP->pos;
    }
    seNo = HuAudFXPlay(1003);
    for (i = 1; i <= 180; i++) {
        if (i < 90) {
            t = 0.5 * (1.0 - HuCos(90.0 * (i / 90.0)));
        } else {
            t = 0.5 + 0.5 * HuSin(90.0 * ((i - 90) / 90.0));
        }
        CRotM[2].x = 30.0 * -HuSin(330.0f * t);
        rotY = 2.0f * (360.0f * t);
        t = i / 180.0;
        CZoomM[2] = zoom - 270.0f * t;
        CenterM[2].y = centerY + ((height - 150.0f) / 2 * t);
        radius = 350.0 * (1.0 - t);
        starPos.x = CenterM[2].x - radius * (HuSin(rotY) * HuCos(CRotM[2].x));
        starPos.y = CenterM[2].y - radius * -HuSin(CRotM[2].x);
        starPos.z = CenterM[2].z - radius * (HuCos(rotY) * HuCos(CRotM[2].x));
        starPos.y += 150.0f * t;
        starPos.z -= 100.0f * t;
        pan = (radius / 350.0) * (32.0 * (HuSin(rotY) * HuCos(CRotM[2].x)));
        HuAudFXPanning(seNo, (int)pan + 64);
        Hu3DModelPosSetV(StarMdlId, &starPos);
        Hu3DParManPosSet(StarEffAnimP[0], starPos.x, starPos.y, starPos.z - 20.0f);
        if (i == 60) {
            CharMotionShiftSet(PResCharNo[winner], PResPlayerMotion[winner][4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            if (winner2 != -1) {
                CharMotionShiftSet(PResCharNo[winner2], PResPlayerMotion[winner2][4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            }
        }
        if (i > 60) {
            t = (i - 60) / 120.0;
            charNo = PResCharNo[winner];
            Hu3DModelRotSet(PResPlayerModelId[winner], t * WinnerRotXTbl[charNo], 0.0f, 0.0f);
            modelP = &Hu3DData[PResPlayerModelId[winner]];
            if (charNo == 3) {
                modelP->pos.y = winnerPos.y + 15.0f * t;
            } else if (charNo == 6) {
                modelP->pos.y = winnerPos.y - 10.0f * t;
            }
            modelP->pos.z = winnerPos.z - 70.0 * HuSin(t * WinnerRotXTbl[charNo]);
            if (winner2 != -1) {
                charNo = PResCharNo[winner2];
                Hu3DModelRotSet(PResPlayerModelId[winner2], t * WinnerRotXTbl[charNo], 0.0f, 0.0f);
                modelP = &Hu3DData[PResPlayerModelId[winner2]];
                if (charNo == 3) {
                    modelP->pos.y = winner2Pos.y + 15.0f * t;
                } else if (charNo == 6) {
                    modelP->pos.y = winner2Pos.y - 10.0f * t;
                }
                modelP->pos.z = winner2Pos.z - 70.0 * HuSin(t * WinnerRotXTbl[charNo]);
            }
        }
        HuPrcVSleep();
    }
    Hu3DLayerHookSet(1, BGFilter);
    Hu3DModelAttrReset(StarMdlId, HU3D_MOTATTR_PAUSE);
    HuAudFXStop(seNo);
    HuAudFXPlay(1004);
    HuPrcSleep(30);
    HuSprAttrReset(WinnerSprGrpId, 0, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(WinnerSprGrpId, 1, HUSPR_ATTR_DISPOFF);
    for (j = 1; j <= 40; j++) {
        HuSprTPLvlSet(WinnerSprGrpId, 0, j / 40.0);
        HuSprTPLvlSet(WinnerSprGrpId, 1, 1.0 - j / 40.0);
        HuPrcVSleep();
    }
    board = GwSystem.boardNo;
    boardNo = board;
    GwCommon.playNum[boardNo]++;
    if (GwCommon.playNum[boardNo] > 9999) {
        GwCommon.playNum[boardNo] = 9999;
    }
    charNo = PResCharNo[winner];
    if (GwPlayerConf[PResPlayerOrder[winner]].type == GW_TYPE_MAN) {
        GwCommon.charPlayNum[boardNo][charNo]++;
        if (GwCommon.charPlayNum[boardNo][charNo] > 999) {
            GwCommon.charPlayNum[boardNo][charNo] = 999;
        }
    }
    if (winner2 != -1) {
        charNo = PResCharNo[winner2];
        if (GwPlayerConf[PResPlayerOrder[winner2]].type == GW_TYPE_MAN) {
            GwCommon.charPlayNum[boardNo][charNo]++;
            if (GwCommon.charPlayNum[boardNo][charNo] > 999) {
                GwCommon.charPlayNum[boardNo][charNo] = 999;
            }
        }
        for (i = 0; i < 4; i += 2) {
            for (starSum = 0, j = i; j < i + 2; j++) {
                starSum += PResPlayer[j].unk004;
            }
            for (j = i; j < i + 2; j++) {
                charNo = PResCharNo[j];
                if (GwPlayerConf[PResPlayerOrder[j]].type == GW_TYPE_MAN) {
                    if (GwCommon.boardMaxStar[boardNo][charNo] < starSum) {
                        GwCommon.boardMaxStar[boardNo][charNo] = starSum;
                    }
                    if (GwCommon.boardMaxCoin[boardNo][charNo] < GwPlayer[PResPlayerOrder[j]].coinMax) {
                        GwCommon.boardMaxCoin[boardNo][charNo] = GwPlayer[PResPlayerOrder[j]].coinMax;
                    }
                }
            }
        }
    } else {
        for (j = 0; j < 4; j++) {
            charNo = GwPlayerConf[j].charNo;
            if (GwPlayerConf[j].type == GW_TYPE_MAN) {
                if (GwCommon.boardMaxStar[boardNo][charNo] < PResPlayer[j].unk004) {
                    GwCommon.boardMaxStar[boardNo][charNo] = PResPlayer[j].unk004;
                }
                if (GwCommon.boardMaxCoin[boardNo][charNo] < GwPlayer[j].coinMax) {
                    GwCommon.boardMaxCoin[boardNo][charNo] = GwPlayer[j].coinMax;
                }
            }
        }
    }
}

/* 190 insns */
int PResResultOrderGet(s16 *order, s16 *rank, s16 *pos)
{
    s16 i;
    s16 j;
    s16 num;
    s16 temp;
    s16 idx[4];
    s32 key[4];

    for (i = 0; i < 4; i++) {
        idx[i] = i;
        key[i] = PResPlayer[i].unk004 + PResPlayer[i].unk008;
        key[i] <<= 16;
        key[i] |= PResPlayer[i].unk006;
    }
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3 - i; j++) {
            if (key[idx[j]] < key[idx[j + 1]]) {
                temp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < 4; i++) {
        order[i] = idx[i];
    }
    for (i = j = 0; i < 3; i++) {
        if (key[idx[i]] != key[idx[i + 1]]) {
            rank[idx[i]] = j;
            j++;
        } else {
            rank[idx[i]] = j;
        }
    }
    rank[idx[i]] = j;
    for (i = j = 0; i < 4; i++, j++) {
        pos[idx[i]] = j;
    }
    for (i = num = 0; i < 4; i++) {
        if (rank[i] == 0) {
            num++;
        }
    }
    return num;
}

/* 882 insns */
void PResResultFinalTeam(void)
{
    s16 i;
    s16 j;
    s16 playerNo;
    s32 seNo;
    s16 height;
    s16 tieNum;
    s16 time;
    s32 streamNo;
    float speed;
    float scale;
    HuVecF rot[4];
    HuVecF centerPos;
    HuVecF pos;
    s16 rank[2];

    centerPos.x = PlayerPosTbl[0].x + (PlayerPosTbl[3].x - PlayerPosTbl[0].x) / 2;
    centerPos.y = PlayerPosTbl[0].y;
    centerPos.z = PlayerPosTbl[0].z;
    for (i = 0; i < 4; i++) {
        rot[i].x = (s32)frandmod(10) - 5;
        rot[i].y = (s32)frandmod(10) - 5;
        rot[i].z = (s32)frandmod(10) - 5;
    }
    tieNum = PResResultTeamOrderGet(rank);
    HuWinMesSet(MessWinId, 0x90011);
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    HuAudSStreamPauseFadeOut(0, TRUE, 500);
    HuWinMesSet(MessWinId, 0x90012);
    streamNo = HuAudJinglePlay(0x46);
    for (i = 0, speed = 1.0f; i < 60; i++) {
        Hu3DMotionSpeedSet(StageMdlId, speed);
        speed += 0.1;
        if (i == 10) {
            seNo = HuAudFXPlay(0x3E9);
        }
        if (i == 20) {
            for (j = 0; j < 4; j++) {
                CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][5], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
        HuPrcVSleep();
    }
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    TeamNameFadeF = TRUE;
    HuWinExClose(MessWinId);
    omCameraViewMoveMulti(4, &FinalResultView, 10, 1);
    if (tieNum > 1) {
        HuPrcSleep(60);
        HuWinExOpen(MessWinId);
        HuWinMesSet(MessWinId, 0x90018);
        HuAudFXPlay(0x2EF);
        HuAudSStreamFadeOut(streamNo, 1000);
        HuAudSStreamPause(0, FALSE);
        TeamNameFadeF = FALSE;
        omCameraViewMoveMulti(4, &MainResultView, 30, 0);
        for (i = 0; i < 30; i++) {
            Hu3DMotionSpeedSet(StageMdlId, speed);
            speed -= 0.2;
            if (i == 20) {
                HuAudFXStop(seNo);
                for (j = 0; j < 4; j++) {
                    CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            HuPrcVSleep();
        }
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuWinMesSet(MessWinId, 0x90014);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        rank[0] = PResResultTie();
        PResPlayer[rank[0] * 2].unk008 = 1;
        PResPlayer[rank[0] * 2 + 1].unk008 = 1;
        HuWinMesSet(MessWinId, 0x90016);
        PResComInputWait(MessWinId);
        HuWinMesWait(MessWinId);
        HuAudSStreamAllFadeOut(500);
        TeamNameFadeF = TRUE;
        HuWinExClose(MessWinId);
        omCameraViewMoveMulti(4, &FinalResultView, 10, 1);
        HuAudJinglePlay(0x46);
        for (i = 0; i < 60; i++) {
            Hu3DMotionSpeedSet(StageMdlId, speed);
            speed += 0.1;
            if (i == 10) {
                seNo = HuAudFXPlay(0x3E9);
            }
            if (i == 20) {
                HuAudFXPlay(0x3EA);
                for (j = 0; j < 4; j++) {
                    CharMotionShiftSet(PResCharNo[j], PResPlayerMotion[j][5], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            HuPrcVSleep();
        }
    }
    time = frandmod(60) + 60;
    HuPrcSleep(time);
    for (j = 0; j < 60; j++) {
        for (i = 0; i < 4; i++) {
            if (j < i * 5 || j > i * 5 + 30 || rank[0] == GwPlayerConf[PResPlayerOrder[i]].grp) {
                continue;
            }
            if (j == i * 5) {
                HuAudFXPlay(0x3EA);
                CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][6], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            scale = j - i * 5;
            Hu3DModelPosSet(PResPlayerModelId[i], PlayerPosTbl[i].x, PlayerPosTbl[i].y, PlayerPosTbl[i].z - 150.0f * scale);
            Hu3DModelRotSet(PResPlayerModelId[i], scale * rot[i].x, scale * rot[i].y, scale * rot[i].z);
            ResultCharFXUpdate(i);
            scale = 0.3 + 0.7 * (1.0 - scale / 30.0);
            Hu3DModelScaleSet(PResPlayerModelId[i], scale, scale, scale);
            Hu3DModelLayerSet(PResPlayerModelId[i], 0);
            if (j == i * 5 + 30) {
                Hu3DModelAttrSet(PResPlayerModelId[i], HU3D_ATTR_DISPOFF);
            }
        }
        if (j == 30) {
            HuAudFXStop(seNo);
        }
        HuPrcVSleep();
    }
    HuWinExOpen(MessWinId);
    HuWinInsertMesSet(MessWinId, PResCharNo[rank[0] * 2], 0);
    HuWinInsertMesSet(MessWinId, PResCharNo[rank[0] * 2 + 1], 1);
    HuWinInsertMesSet(MessWinId, PResTeamNameMesGet(PResCharNo[rank[0] * 2], PResCharNo[rank[0] * 2 + 1]), 2);
    HuWinMesSet(MessWinId, 0x9001A);
    for (j = 1; j <= 60; j++) {
        scale = j / 60.0;
        for (i = 0; i < 2; i++) {
            playerNo = i + rank[0] * 2;
            pos = centerPos;
            pos.x += i * 140 - 70;
            PSVECSubtract(&pos, &PlayerPosTbl[playerNo], &pos);
            PSVECScale(&pos, &pos, sin(M_PI * (90.0f * scale) / 180.0));
            PSVECAdd(&PlayerPosTbl[playerNo], &pos, &pos);
            Hu3DModelPosSetV(PResPlayerModelId[playerNo], &pos);
            ResultCharFXUpdate(playerNo);
        }
        speed -= 0.1;
        Hu3DMotionSpeedSet(StageMdlId, speed);
        if (j == 50) {
            for (i = 0; i < 4; i++) {
                CharMotionShiftSet(PResCharNo[i], PResPlayerMotion[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
        }
        HuPrcVSleep();
    }
    PResComInputWait(MessWinId);
    HuWinMesWait(MessWinId);
    HuAudSStreamAllFadeOut(500);
    HuAudBGMPlay(0x47);
    HuWinExClose(MessWinId);
    i = CharModelHeightGet(PResCharNo[rank[0] * 2]);
    j = CharModelHeightGet(PResCharNo[rank[0] * 2 + 1]);
    if (i > j) {
        height = i;
    } else {
        height = j;
    }
    PResResultWinnerExec(height, rank[0] * 2, rank[0] * 2 + 1);
    PResBtnAWait();
}

/* 106 insns */
int PResResultTeamOrderGet(s16 *rank)
{
    s16 i;
    s32 key[2];

    for (i = 0; i < 2; i++) {
        key[i] = PResPlayer[i * 2].unk004 + PResPlayer[i * 2 + 1].unk004;
        key[i] += PResPlayer[i * 2].unk008 + PResPlayer[i * 2 + 1].unk008;
        key[i] <<= 16;
        key[i] |= PResPlayer[i * 2].unk006 + PResPlayer[i * 2 + 1].unk006;
    }
    if (key[0] > key[1]) {
        rank[0] = 0;
        rank[1] = 1;
    } else if (key[0] < key[1]) {
        rank[0] = 1;
        rank[1] = 0;
    } else {
        rank[0] = 0;
        rank[1] = 0;
        return 2;
    }
    return 1;
}

/* 412 insns */
static void BonusFadeCreate(HU3DMODELID modelId, s16 num, HuVecF *posTbl)
{
    HuVecF pos2D;
    HU3DPARTICLE *particleP[4];
    HU3DMODELID particleMdlId[4];
    HU3DMODEL *modelP;
    HU3DMODEL *particleMdlP;
    s16 i;
    s16 j;
    float t;

    modelP = &Hu3DData[modelId];
    BonusFadeAddr = HuMemDirectMallocNum(HEAP_HEAP, GXGetTexBufferSize(192, 192, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    Hu3D3Dto2D(&modelP->pos, HU3D_CAM1, &pos2D);
    pos2D.x *= 1.1111111111111112;
    BonusFadeSize[0] = pos2D.x - 96.0f;
    BonusFadeSize[1] = pos2D.y - 96.0f;
    BonusFadeSize[2] = 192;
    BonusFadeSize[3] = 192;
    Hu3DLayerHookSet(9, BonusFadeFbCopy);
    HuPrcVSleep();
    Hu3DLayerHookReset(9);
    for (i = 0; i < num; i++) {
        particleMdlId[i] = Hu3DParticleCreate(CircleAnimP, 1100);
        Hu3DModelLayerSet(particleMdlId[i], 2);
        Hu3DModelCameraSet(particleMdlId[i], HU3D_CAM2);
        Hu3DParticleHookSet(particleMdlId[i], BonusFadeEffHook);
        particleMdlP = &Hu3DData[particleMdlId[i]];
        particleP[i] = particleMdlP->hookData;
        particleP[i]->pos = modelP->pos;
        particleP[i]->unk_10 = posTbl[i];
    }
    BonusFadeMode = 0;
    HuPrcVSleep();
    BonusFadeMode = 1;
    HuPrcVSleep();
    BonusFadeMode = 2;
    HuAudFXPlay(0x3E7);
    for (i = 0; i < 15; i++) {
        Hu3DModelTPLvlSet(modelId, 1.0 - (i / 15.0));
        if (i == 10) {
            Hu3DParManAttrSet(StarEffAnimP[0], 1);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    BonusFadeMode = 0;
    HuPrcSleep(30);
    BonusFadeMode = 3;
    for (i = 0; i < num; i++) {
        particleP[i]->dataCnt = 0;
    }
    HuPrcSleep(40);
    BonusFadeMode = 4;
    HuAudFXPlay(0x3E8);
    for (i = 0; i < num; i++) {
        Hu3DModelAttrReset(PlayerStarMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelPosSetV(PlayerStarMdlId[i], &posTbl[i]);
        Hu3DModelRotSet(PlayerStarMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(PlayerStarMdlId[i], 1.2f, 1.2f, 1.2f);
        particleP[i]->dataCnt = 0;
    }
    for (j = 1; j <= 30; j++) {
        t = j / 30.0;
        for (i = 0; i < num; i++) {
            Hu3DModelScaleSet(PlayerStarMdlId[i], 1.2 * t, 1.2 * t, 1.2 * t);
            if (j == 15) {
                Hu3DParManAttrReset(StarEffAnimP[i], 1);
                Hu3DParManColorSet(StarEffAnimP[i], 0);
                Hu3DParManPosSet(StarEffAnimP[i], posTbl[i].x, posTbl[i].y, posTbl[i].z - 20.0f);
            }
        }
        HuPrcVSleep();
    }
    for (i = 0; i < num; i++) {
        Hu3DModelKill(particleMdlId[i]);
    }
    HuMemDirectFree(BonusFadeAddr);
}

/* layer 9 hook, installed for one frame: copy the 192x192 screen area round the bonus star */
static void BonusFadeFbCopy(s16 layerNo)
{
    if (Hu3DCameraNo == 1) {
        Hu3DFbCopyExec(BonusFadeSize[0], BonusFadeSize[1], BonusFadeSize[2], BonusFadeSize[3], GX_TF_RGB565, 0, BonusFadeAddr);
    }
}

static void BonusFadeEffHook(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HuVecF dir;
    s16 time;
    u8 r;
    u8 g;
    u8 b;
    s16 sumR;
    s16 sumG;
    s16 sumB;
    u8 *texel;
    s32 xx;
    s32 yy;
    s16 cnt;
    s16 x;
    s16 y;
    s16 col;
    s16 i;
    HU3DPARTICLEDATA *dataP;

    if (particleP->count == 0) {
        for (dataP = particleP->data, i = 0; i < particleP->maxCnt; i++, dataP++) {
            dataP->scale = 0.0f;
        }
    }
    if (BonusFadeMode == 1) {
        /* one particle per 6x6 block of the copy's central 96x96 window, coloured with the
         * average of the block's bright texels */
        dataP = particleP->data;
        for (y = 0; y < 192; y += 6) {
            for (x = 0; x < 192; x += 6) {
                if (y < 48 || y > 144 || x < 48 || x > 144) {
                    continue;
                }
                cnt = sumR = sumG = sumB = 0;
                for (yy = y; yy < y + 6; yy++) {
                    for (xx = x; xx < x + 6; xx++) {
                        /* RGB565 texel (xx, yy) of the GX-tiled copy: 4x4 texel tiles, 48 tiles a row */
                        texel = (u8 *)BonusFadeAddr + ((yy >> 2) * 0x600) + ((xx >> 2) << 5) + ((xx & 3) << 1) + (((yy & 3) << 2) << 1);
                        col = (texel[0] << 8) | texel[1];
                        r = (col >> 8) & 0xF8;
                        g = (col >> 3) & 0xFC;
                        b = (col << 3) & 0xF8;
                        if (0.114 * b + (0.299 * r + 0.587 * g) < 65.0) {
                            continue;
                        }
                        sumR += r;
                        sumG += g;
                        sumB += b;
                        cnt++;
                    }
                }
                if (cnt != 0) {
                    dataP->color.r = sumR / cnt;
                    dataP->color.g = sumG / cnt;
                    dataP->color.b = sumB / cnt;
                    dataP->pos = particleP->pos;
                    dataP->pos.x += 1.3 * (x - 96);
                    dataP->pos.y += 1.3 * (-y + 96);
                    dataP->pos.z += 30.0f;
                    dataP->vel = dataP->accel = dataP->pos;
                    dataP->scale = 0.1f;
                    dataP->speedDecay = (s32)frandmod(10) - 5;
                    dataP->speedDecay += (dataP->speedDecay < 0.0f) ? -5 : 5;
                    dataP->colorIdx = (s32)frandmod(10) - 5;
                    dataP->colorIdx += (dataP->colorIdx < 0.0f) ? -5 : 5;
                    dataP->scaleBase = (s32)frandmod(10);
                    dataP->time = 0;
                    dataP++;
                }
            }
        }
        DCFlushRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
        particleP->dataCnt = 0;
    } else if (BonusFadeMode == 2) {
        /* grow */
        for (dataP = particleP->data, i = 0; i < particleP->maxCnt; i++, dataP++) {
            if (dataP->scale <= 0.0f) {
                continue;
            }
            if (dataP->scale < 15.0f) {
                dataP->scale += 1.0f;
            }
        }
        particleP->dataCnt++;
    } else if (BonusFadeMode == 3) {
        /* fly towards the target (unk_10), each particle starting scaleBase frames late */
        if (particleP->dataCnt <= 40) {
            for (dataP = particleP->data, i = 0; i < particleP->maxCnt; i++, dataP++) {
                if (dataP->scale <= 0.0f) {
                    continue;
                }
                if (particleP->dataCnt < dataP->scaleBase) {
                    continue;
                }
                if (particleP->dataCnt > 30.0f + dataP->scaleBase) {
                    continue;
                }
                {
                    time = particleP->dataCnt - dataP->scaleBase;
                    PSVECSubtract(&particleP->unk_10, &particleP->pos, &dir);
                    PSVECScale(&dir, &dir, HuSin(90.0 * (time / 30.0)));
                    PSVECAdd(&dataP->vel, &dir, &dataP->accel);
                    col = dataP->color.r + 5;
                    if (col > 255) {
                        dataP->color.r = 255;
                    } else {
                        dataP->color.r = col;
                    }
                    col = dataP->color.g + 5;
                    if (col > 255) {
                        dataP->color.g = 255;
                    } else {
                        dataP->color.g = col;
                    }
                    col = dataP->color.b + 5;
                    if (col > 255) {
                        dataP->color.b = 255;
                    } else {
                        dataP->color.b = col;
                    }
                }
            }
            DCFlushRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
            particleP->dataCnt++;
        }
    } else if (BonusFadeMode == 4) {
        /* fade out */
        if (particleP->dataCnt <= 30) {
            for (dataP = particleP->data, i = 0; i < particleP->maxCnt; i++, dataP++) {
                if (dataP->scale <= 0.0f) {
                    continue;
                }
                {
                    dataP->color.a = 255.0 * (1.0 - HuSin(90.0 * (particleP->dataCnt / 30.0)));
                    dataP->scale *= 1.05;
                }
            }
            DCFlushRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
            particleP->dataCnt++;
        }
    }
    /* every mode: wobble round the base position (accel) */
    for (dataP = particleP->data, i = 0; i < particleP->maxCnt; i++, dataP++) {
        if (dataP->scale <= 0.0f) {
            continue;
        }
        {
            dataP->pos.x = dataP->accel.x + (3.0 * HuSin(dataP->time * dataP->speedDecay));
            dataP->pos.y = dataP->accel.y + (3.0 * HuCos(dataP->time * dataP->colorIdx));
            dataP->pos.z = dataP->accel.z;
            dataP->time++;
        }
    }
}

/* 244 insns */
static void BGFilter(s16 layerNo)
{
    GXColor color = { 0, 0, 0, 0 };
    Mtx44 proj;
    Mtx modelview;
    if (Hu3DCameraNo == 2) {
        MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        MTXIdentity(modelview);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        GXSetScissor(0, 0, 640, 480);
        GXSetCullMode(GX_CULL_NONE);
        GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
        GXSetAlphaUpdate(GX_FALSE);
        GXSetColorUpdate(GX_TRUE);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetCullMode(GX_CULL_NONE);
        color.a = 160.0 * (BGFadeTime / 30.0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2u16(0, 0);
        GXPosition2u16(640, 0);
        GXPosition2u16(640, 480);
        GXPosition2u16(0, 480);
        GXEnd();
        BGFadeTime++;
        if (BGFadeTime > 30) {
            BGFadeTime = 30;
        }
    }
}

/* 66 insns */
static void PlayerHover(void)
{
    s16 i;
    HU3DMODEL *modelP;

    while(1) {
        for(i = 0; i < 4; i++) {
            modelP = &Hu3DData[PResPlayerModelId[i]];
            if(PResPlayerMotion[i][5] == Hu3DMotionIDGet(PResPlayerModelId[i])) {
                modelP->pos.y = (PlayerPosTbl[i].y + (((GlobalCounter + i) & 2) * 2)) - 2.0f;
            }
        }
        HuPrcVSleep();
    }
}

/* 94 insns */
static void ResultCharFXUpdate(s16 playerNo)
{
    HU3DMODEL *modelP;
    float pan;
    HuVecF pos;
    HuVecF pos2D;

    modelP = &Hu3DData[PResPlayerModelId[playerNo]];
    pos = modelP->pos;
    Hu3D3Dto2D(&pos, HU3D_CAM2, &pos2D);
    pan = (pos2D.x - 288.0f) / 288.0f;
    pan = 64.0 + (32.0 * pan);
    if(pan < 32.0f) {
        pan = 32.0f;
    }
    if(pan > 96.0f) {
        pan = 96.0f;
    }
    CharFXPan[PResCharNo[playerNo]] = pan;
    CharFXVol[PResCharNo[playerNo]] = 127;
}

/* 24 insns */
static s32 ResultCharFXPlay(s16 charNo, s16 seNo)
{
    return CharFXPlayVolPan((s32)charNo, seNo, CharFXVol[charNo], CharFXPan[charNo]);
}

