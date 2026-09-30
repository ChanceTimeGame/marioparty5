/*
 * partyresultdll stat.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/partyresultdll/asm/REL/partyresultdll/stat.s.
 */

#include "REL/partyresultdll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/saveload.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/main.h"
#ifndef __MWERKS__
#include "game/hsfex.h" /* retail calls Hu3D2Dto3D unprototyped */
#endif
#include "math.h"
#ifndef __MWERKS__
/* retail calls sprintf unprototyped (no crclr before the call) */
#include <stdio.h>
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_2B8 = 5.0f; /* 0x2B8 */
static const float lbl_1_rodata_2BC = 20.0f; /* 0x2BC */
static const float lbl_1_rodata_2C0 = 15000.0f; /* 0x2C0 */
static const float lbl_1_rodata_2C4 = 1.2f; /* 0x2C4 */
static const float lbl_1_rodata_2C8 = 0.0f; /* 0x2C8 */
static const float lbl_1_rodata_2CC = 0.8f; /* 0x2CC */
static const float lbl_1_rodata_2D0 = 1.0f; /* 0x2D0 */
static const float lbl_1_rodata_2D4 = 288.0f; /* 0x2D4 */
static const float lbl_1_rodata_2D8 = 65.0f; /* 0x2D8 */
static const float lbl_1_rodata_2DC = 90.0f; /* 0x2DC */
static const float lbl_1_rodata_2E0 = 490.0f; /* 0x2E0 */
static const float lbl_1_rodata_2E4 = 465.0f; /* 0x2E4 */
static const float lbl_1_rodata_2E8 = -10000.0f; /* 0x2E8 */
static const float lbl_1_rodata_2EC = 1000.0f; /* 0x2EC */
static const float lbl_1_rodata_2F0 = 16.0f; /* 0x2F0 */
static const float lbl_1_rodata_2F4 = 376.0f; /* 0x2F4 */
static const float lbl_1_rodata_2F8 = -1.0f; /* 0x2F8 */
/* 0x300 lbl_1_rodata_300 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_308 = 0.4f; /* 0x308 */
static const float lbl_1_rodata_30C = 0.2f; /* 0x30C */
static const float lbl_1_rodata_310 = 140.0f; /* 0x310 */
static const float lbl_1_rodata_314 = 6500.0f; /* 0x314 */
static const float lbl_1_rodata_318 = 0.6f; /* 0x318 */
static const float lbl_1_rodata_31C = 210.0f; /* 0x31C */
static const float lbl_1_rodata_320 = 0.45f; /* 0x320 */
static const float lbl_1_rodata_324 = 380.0f; /* 0x324 */
static const float lbl_1_rodata_328 = 70.0f; /* 0x328 */
static const float lbl_1_rodata_32C = 135.0f; /* 0x32C */
static const float lbl_1_rodata_330 = 360.0f; /* 0x330 */
static const float lbl_1_rodata_334 = 118.0f; /* 0x334 */
static const float lbl_1_rodata_338 = 4.0f; /* 0x338 */
static const float lbl_1_rodata_33C = 123.0f; /* 0x33C */
static const float lbl_1_rodata_340 = 40.0f; /* 0x340 */
static const float lbl_1_rodata_344 = 220.0f; /* 0x344 */
static const float lbl_1_rodata_348 = 318.0f; /* 0x348 */
static const float lbl_1_rodata_34C = 132.0f; /* 0x34C */
static const float lbl_1_rodata_350 = 58.0f; /* 0x350 */
static const float lbl_1_rodata_354 = 224.0f; /* 0x354 */
static const double lbl_1_rodata_358 = 5.0; /* 0x358 */
static const double lbl_1_rodata_360 = 99.0; /* 0x360 */
static const double lbl_1_rodata_368 = 438.0; /* 0x368 */
static const double lbl_1_rodata_370 = 1.0; /* 0x370 */
static const float lbl_1_rodata_378 = -57.0f; /* 0x378 */
static const float lbl_1_rodata_37C = 0.95f; /* 0x37C */
static const float lbl_1_rodata_380 = 0.7125f; /* 0x380 */
static const float lbl_1_rodata_384 = 149.0f; /* 0x384 */
static const float lbl_1_rodata_388 = 640.0f; /* 0x388 */
static const double lbl_1_rodata_390 = 20.0; /* 0x390 */
static const double lbl_1_rodata_398 = 640.0; /* 0x398 */
static const double lbl_1_rodata_3A0 = 3.141592653589793; /* 0x3A0 */
static const double lbl_1_rodata_3A8 = 180.0; /* 0x3A8 */
static const float lbl_1_rodata_3B0 = 8.0f; /* 0x3B0 */
static const double lbl_1_rodata_3B8 = 406.0; /* 0x3B8 */
static const double lbl_1_rodata_3C0 = 100.0; /* 0x3C0 */
static const double lbl_1_rodata_3C8 = 660.0; /* 0x3C8 */
static const double lbl_1_rodata_3D0 = 340.0; /* 0x3D0 */
static const double lbl_1_rodata_3D8 = 150.0; /* 0x3D8 */
static const float lbl_1_rodata_3E0 = 655360.0f; /* 0x3E0 */
static const double lbl_1_rodata_3E8 = 10.0; /* 0x3E8 */
static const float lbl_1_rodata_3F0 = 74.0f; /* 0x3F0 */
static const double lbl_1_rodata_3F8 = 74.0; /* 0x3F8 */
static const float lbl_1_rodata_400 = 3.0f; /* 0x400 */
static const double lbl_1_rodata_408 = 1.5; /* 0x408 */
static const float lbl_1_rodata_410 = 27.0f; /* 0x410 */
static const float lbl_1_rodata_414 = 52.0f; /* 0x414 */
static const float lbl_1_rodata_418 = 0.3f; /* 0x418 */
static const float lbl_1_rodata_41C = 134.0f; /* 0x41C */
static const double lbl_1_rodata_420 = 95.33333333333334; /* 0x420 */
static const float lbl_1_rodata_428 = 91.0f; /* 0x428 */
static const float lbl_1_rodata_42C = 515.55554f; /* 0x42C */
static const float lbl_1_rodata_430 = 258.0f; /* 0x430 */
static const float lbl_1_rodata_434 = 1500.0f; /* 0x434 */
static const float lbl_1_rodata_438 = 480.0f; /* 0x438 */
static const double lbl_1_rodata_440 = 1.2; /* 0x440 */
/* 0x448 lbl_1_rodata_448 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x449 lbl_1_rodata_449 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_44C = 10.0f; /* 0x44C */
static const double lbl_1_rodata_450 = 0.005; /* 0x450 */
static const double lbl_1_rodata_458 = 0.0; /* 0x458 */
static const double lbl_1_rodata_460 = 219.0; /* 0x460 */
static const double lbl_1_rodata_468 = 126.0; /* 0x468 */
static const double lbl_1_rodata_470 = 252.0; /* 0x470 */
static const float lbl_1_rodata_478 = 1.1f; /* 0x478 */
static const float lbl_1_rodata_47C = 2.0f; /* 0x47C */
static const float lbl_1_rodata_480 = 0.001f; /* 0x480 */
static const double lbl_1_rodata_488 = 0.5; /* 0x488 */
static const double lbl_1_rodata_490 = 3.0; /* 0x490 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x658 */ static HU3DMODELID ToueiMdlId[4];
/* 0x650 */ static HU3DMODELID CoinMdlId[4];
/* 0x648 */ static HU3DMODELID StarMdlId[4];
/* 0x646 */ static HU3DMODELID StageMdlId;
/* 0x644 */ static HUSPRGRPID HeaderGrpId;
/* 0x63C */ static HUSPRGRPID ScoreGrpId[4];
/* 0x63A */ static HUWINID HelpWinId;
/* 0x638 */ static HUWINID MessWinId;
/* 0x634 */ static ANIMDATA *BackAnimP;
/* 0x630 */ static HUWINID TeamNameWinId[2];
/* 0x62E */ static HUSPRGRPID DetailOverGrpId;
/* 0x62C */ static HUSPRGRPID DetailGrpId;
/* 0x628 */ static float DetailCursorPosX;
/* 0x624 */ static float DetailSelIdx;
/* 0x620 */ static float DetailGrpOfsX;
/* 0x61C */ static float DetailGrpIdxOfsX;
/* 0x618 */ static HU3DMODELID FingerMdlId;
/* 0x614 */ static ANIMDATA *GraphAnimP;
/* 0x60E */ static s16 StatGraphMax[3];
/* 0x60C */ static s16 PlayerSel;
/* 0x608 */ static HUPROCESS *StatModelProc;
/* 0x5F8 */ static HUSPRITE *GraphSprP[4];
/* 0x5F0 */ static double BackScrollY;
/* 0x5E8 */ static double BackScrollX;

static void StatFingerPosSet(s16 playerSel);
static void StatScorePosSet(s16 playerSel, float x, float y);
static void StatDetailPosSet(float x, float y);
static void StatModelUpdate(void);
static void StatBackDraw(s16 layerNo);
static void StatGraphDraw(HUSPRITE *sp);
static BOOL StatLinePosGet(HuVec2f *p0, HuVec2f *d0, HuVec2f *p1, HuVec2f *d1, HuVec2f *out);
static void StatLineNorm(HuVec2f *in, HuVec2f *out);
static void StatLineScale(HuVec2f *in, HuVec2f *out, float scale);
static void StatLineTrans(HuVec2f *a, HuVec2f *b, HuVec2f *out);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x210 */ static OMCAMERAVIEW StatView = { { 0.0f, 110.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 6500.0f };

/* 414 insns */
void PResStatCreate(void)
{
    s16 boardNo;
    s16 i;
    s16 charNo;
    s16 turnNo;
    HU3DMODELID modelId;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    ANIMDATA *animP;
    s32 board;

    board = GwSystem.boardNo;
    boardNo = board;
    if (boardNo < 0 || boardNo >= 7) {
        boardNo = 0;
    }
    Hu3DCameraPerspectiveSet(HU3D_CAM0 | HU3D_CAM2, 5.0f, 20.0f, 15000.0f, 1.2f);
    omCameraViewSetMulti(HU3D_CAM0 | HU3D_CAM2, &StatView);
    HuPrcVSleep();
    for (i = 0; i < 4; i++) {
        charNo = PResCharNo[i];
        modelId = PResPlayerModelId[i];
        Hu3DModelPosSet(modelId, (i * 150) - 225, 0.0f, 0.0f);
        Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
        CharMotionSet(charNo, PResPlayerMotion[i][0]);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(modelId, HU3D_CAM0);
        if (charNo == 8) {
            Hu3DModelScaleSet(modelId, 0.8f, 0.8f, 0.8f);
        } else if (charNo == 9) {
            Hu3DModelScaleSet(modelId, 0.8f, 0.8f, 0.8f);
        } else {
            Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
        }
        Hu3DModelLayerSet(modelId, 0);
    }
    modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x31));
    StageMdlId = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    grpId = HuSprGrpCreate(4);
    HeaderGrpId = grpId;
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2B));
    sprId = HuSprCreate(animP, 95, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 288.0f, 65.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x21) + boardNo);
    sprId = HuSprCreate(animP, 100, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 90.0f, 65.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2A));
    sprId = HuSprCreate(animP, 100, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprPosSet(grpId, 2, 490.0f, 65.0f);
    turnNo = (GwSystem.turnMax - 10) / 5;
    if (turnNo < 0 || turnNo > 8) {
        turnNo = 0;
    }
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2C));
    sprId = HuSprCreate(animP, 95, turnNo);
    HuSprGrpMemberSet(grpId, 3, sprId);
    HuSprPosSet(grpId, 3, 465.0f, 65.0f);
    if (PResTeamF == FALSE) {
        PResStatRankCreate();
    } else {
        PResStatRankTeamCreate();
    }
    PResStatDetailCreate();
    BackAnimP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x1A) + boardNo);
    HelpWinId = HuWinCreate(-10000.0f, 1000.0f, 560, 42, 0);
    HuWinBGTPLvlSet(HelpWinId, 0.0f);
    HuWinAttrSet(HelpWinId, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSpeedSet(HelpWinId, 0);
    HuWinMesSet(HelpWinId, 0x2000A);
    MessWinId = HuWinExCreateFrame(16.0f, 376.0f, 544, 64, -1, 0);
    HuWinMesSpeedSet(MessWinId, 0);
    HuSprExecLayerCameraSet(64, HU3D_CAM2, 0);
    Hu3DLayerHookSet(1, StatBackDraw);
    HuPrcVSleep();
    ToueiDispInit(ToueiMdlId);
    StatModelProc = HuPrcChildCreate(StatModelUpdate, 1000, 0x2000, 0, objman);
    Hu3DGLightPosSet(PResLightId, 1000.0f, 1000.0f, 1000.0f, -1.0f, -1.0f, -1.0f);
}

/* 519 insns */
void PResStatRankCreate(void)
{
    HuVecF pos2D;
    HuVecF pos3D;
    char str[16];
    s16 order[4];
    s16 rank[4];
    s16 pos[4];
    s16 i;
    s16 j;
    HUSPRGRPID grpId;
    HU3DMODELID modelId;
    HUSPRID sprId;
    ANIMDATA *animP;

    PResResultOrderGet(order, rank, pos);
    for (j = 0; j < 4; j++) {
        modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x30));
        ToueiMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.4f, 0.4f, 0.2f);
        pos2D.x = 140.0f;
        pos2D.y = (pos[j] * 75) + 150;
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
    }
    for (j = 0; j < 4; j++) {
        modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x04));
        StarMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.6f, 0.6f, 0.6f);
        pos2D.x = 210.0f;
        pos2D.y = (pos[j] * 75) + 150;
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
        modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x06));
        CoinMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.45f, 0.45f, 0.45f);
        pos2D.x = 380.0f;
        pos2D.y = (pos[j] * 75) + 150;
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
    }
    for (i = 0; i < 4; i++) {
        grpId = HuSprGrpCreate(13);
        ScoreGrpId[i] = grpId;
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x32) + rank[i]);
        sprId = HuSprCreate(animP, 100, 0);
        HuSprGrpMemberSet(grpId, 0, sprId);
        HuSprPosSet(grpId, 0, 288.0f, (pos[i] * 75) + 150);
        HuSprDrawNoSet(grpId, 0, 64);
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2E));
        sprId = HuSprCreate(animP, 95, 0);
        HuSprGrpMemberSet(grpId, 1, sprId);
        HuSprPosSet(grpId, 1, 70.0f, (pos[i] * 75) + 150);
        HuSprAnimNoSetPause(grpId, 1, rank[i]);
        if (pos[i] == 0) {
            animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2D));
            sprId = HuSprCreate(animP, 90, 0);
            HuSprGrpMemberSet(grpId, 2, sprId);
            HuSprPosSet(grpId, 2, 140.0f, (pos[i] * 75) + 105);
        }
        sprintf(str, "%0d   ", PResPlayer[i].unk004);
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2F));
        for (j = 0; j < 4; j++) {
            if (j != 0 && str[j - 1] == ' ') {
                break;
            }
            sprId = HuSprCreate(animP, 95, 0);
            HuSprGrpMemberSet(grpId, j + 3, sprId);
            HuSprPosSet(grpId, j + 3, (j * 24) + 250, (pos[i] * 75) + 150);
            if (j == 0) {
                HuSprBankSet(grpId, 3, 10);
            } else {
                HuSprBankSet(grpId, j + 3, str[j - 1] & 0xF);
            }
        }
        sprintf(str, "%0d    ", PResPlayer[i].unk006);
        for (j = 0; j < 5; j++) {
            if (j != 0 && str[j - 1] == ' ') {
                break;
            }
            sprId = HuSprCreate(animP, 95, 0);
            HuSprGrpMemberSet(grpId, j + 8, sprId);
            HuSprPosSet(grpId, j + 8, (j * 24) + 420, (pos[i] * 75) + 150);
            if (j == 0) {
                HuSprBankSet(grpId, 8, 10);
            } else {
                HuSprBankSet(grpId, j + 8, str[j - 1] & 0xF);
            }
        }
    }
}

/* 686 insns */
void PResStatRankTeamCreate(void)
{
    HuVecF pos2D;
    HuVecF pos3D;
    char str[16];
    s16 slot[4];
    s16 rank[2];
    s16 i;
    s16 j;
    s16 teamNo;
    HUSPRGRPID grpId;
    HU3DMODELID modelId;
    HUSPRID sprId;
    ANIMDATA *animP;

    PResResultTeamOrderGet(rank);
    if (rank[0] == 0) {
        for (j = 0; j < 4; j++) {
            slot[j] = j;
        }
    } else {
        for (j = 0; j < 2; j++) {
            slot[j] = j + 2;
        }
        for (j = 0; j < 2; j++) {
            slot[j + 2] = j;
        }
    }
    for (j = 0; j < 4; j++) {
        modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x30));
        ToueiMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.4f, 0.4f, 0.2f);
        pos2D.x = 140.0f;
        pos2D.y = 180 + ((slot[j] / 2) * 150) + ((slot[j] & 1) ? 36 : -36);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
    }
    for (j = 0; j < 2; j++) {
        modelId = Hu3DModelCreate((void *)HuDataSelHeapReadNum(DATANUM(DATA_partyresult, 0x04), HU_MEMNUM_OVL, HEAP_MODEL));
        StarMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.6f, 0.6f, 0.6f);
        pos2D.x = 210.0f;
        pos2D.y = (j * 150) + 210;
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
        modelId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x06));
        CoinMdlId[j] = modelId;
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.45f, 0.45f, 0.45f);
        pos2D.x = 380.0f;
        pos2D.y = (j * 150) + 210;
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos3D);
        Hu3DModelPosSetV(modelId, &pos3D);
    }
    for (i = 0; i < 2; i++) {
        teamNo = rank[i];
        grpId = HuSprGrpCreate(13);
        ScoreGrpId[i] = grpId;
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x36) + teamNo);
        sprId = HuSprCreate(animP, 100, 0);
        HuSprGrpMemberSet(grpId, 0, sprId);
        HuSprPosSet(grpId, 0, 288.0f, (i * 150) + 180);
        HuSprDrawNoSet(grpId, 0, 64);
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2E));
        sprId = HuSprCreate(animP, 95, 0);
        HuSprGrpMemberSet(grpId, 1, sprId);
        HuSprPosSet(grpId, 1, 70.0f, (i * 150) + 180);
        HuSprAnimNoSetPause(grpId, 1, i);
        if (i == 0) {
            animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2D));
            sprId = HuSprCreate(animP, 90, 0);
            HuSprGrpMemberSet(grpId, 2, sprId);
            HuSprPosSet(grpId, 2, 70.0f, 135.0f);
        }
        sprintf(str, "%0d    ", PResPlayer[teamNo * 2].unk004 + PResPlayer[(teamNo * 2) + 1].unk004);
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2F));
        for (j = 0; j < 5; j++) {
            if (j != 0 && str[j - 1] == ' ') {
                break;
            }
            sprId = HuSprCreate(animP, 95, 0);
            HuSprGrpMemberSet(grpId, j + 3, sprId);
            HuSprPosSet(grpId, j + 3, (j * 24) + 250, (i * 150) + 210);
            if (j == 0) {
                HuSprBankSet(grpId, 3, 10);
            } else {
                HuSprBankSet(grpId, j + 3, str[j - 1] & 0xF);
            }
        }
        sprintf(str, "%0d    ", PResPlayer[teamNo * 2].unk006 + PResPlayer[(teamNo * 2) + 1].unk006);
        for (j = 0; j < 5; j++) {
            if (j != 0 && str[j - 1] == ' ') {
                break;
            }
            sprId = HuSprCreate(animP, 95, 0);
            HuSprGrpMemberSet(grpId, j + 8, sprId);
            HuSprPosSet(grpId, j + 8, (j * 24) + 420, (i * 150) + 210);
            if (j == 0) {
                HuSprBankSet(grpId, 8, 10);
            } else {
                HuSprBankSet(grpId, j + 8, str[j - 1] & 0xF);
            }
        }
    }
    for (j = 0; j < 2; j++) {
        teamNo = rank[j];
        TeamNameWinId[j] = HuWinCreate(360.0f, (j * 150) + 190, 236, 42, 0);
        HuWinBGTPLvlSet(TeamNameWinId[j], 0.0f);
        HuWinPriSet(TeamNameWinId[j], 500);
        HuWinAttrSet(TeamNameWinId[j], HUWIN_ATTR_ALIGN_CENTER);
        HuWinMesSpeedSet(TeamNameWinId[j], 0);
        sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x28) + teamNo), 600, 0);
        HuWinSprSet(TeamNameWinId[j], sprId, 118.0f, 4.0f);
        HuWinMesSet(TeamNameWinId[j], PResTeamNameMesGet(PResCharNo[teamNo * 2], PResCharNo[(teamNo * 2) + 1]));
        HuWinCenterPosSet(TeamNameWinId[j], 123.0f, 40.0f);
    }
}

/* 1029 insns */
void PResStatDetailCreate(void)
{
    char str[16];
    s16 i;
    s16 j;
    s16 k;
    s16 step;
    s16 graphNum;
    s32 value;
    s16 digitNum;
    HUSPRID sprId;
    s16 memberNo;
    s16 *graphP;
    HUSPRGRPID grpId;
    HUSPRITE *sp;
    ANIMDATA *animP;

    for (i = 0; i < 4; i++) {
        PResPlayer[i].unk010[0] = PResPlayer[i].unk004;
        PResPlayer[i].unk010[1] = PResPlayer[i].unk006;
    }
    grpId = HuSprGrpCreate(21);
    DetailOverGrpId = grpId;
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x38));
    sprId = HuSprCreate(animP, 150, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 288.0f, 220.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x39));
    sprId = HuSprCreate(animP, 90, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 318.0f, 220.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3C));
    sprId = HuSprCreate(animP, 80, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprPosSet(grpId, 2, 132.0f, 220.0f);
    HuSprColorSet(grpId, 2, 255, 247, 127);
    if (PResTeamF) {
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x42));
        sprId = HuSprCreate(animP, 100, 0);
        HuSprGrpMemberSet(grpId, 20, sprId);
        HuSprPosSet(grpId, 20, 58.0f, 224.0f);
    }
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3E));
    sprId = HuSprCreate(animP, 110, 0);
    HuSprGrpMemberSet(grpId, 3, sprId);
    HuSprPosSet(grpId, 3, 318.0f, 220.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3D));
    sprId = HuSprCreate(animP, 110, 0);
    HuSprGrpMemberSet(grpId, 4, sprId);
    HuSprPosSet(grpId, 4, 318.0f, 220.0f);
    j = (PResTeamF) ? 2 : 4;
    for (i = 0; i < j; i++) {
        sprId = HuSprFuncCreate(StatGraphDraw, i + 105);
        HuSprGrpMemberSet(grpId, i + 5, sprId);
        HuSprPosSet(grpId, i + 5, 318.0f, 220.0f);
        sp = &HuSprData[sprId];
        GraphSprP[i] = sp;
        sp->work[0] = i;
        sp->work[1] = 0;
    }
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x41));
    if (PResPlayer[0].unk024 <= 20) {
        step = 5;
    } else {
        step = 10;
    }
    graphNum = PResPlayer[0].unk024 + 1;
    for (i = 0; i < (graphNum / step) + 1; i++) {
        sprId = HuSprCreate(animP, 107, 0);
        HuSprGrpMemberSet(grpId, i + 9, sprId);
        HuSprPosSet(grpId, i + 9, 5.0 + (99.0 + (438.0 * ((float)(i * step) / ((float)graphNum - 1.0)))), 220.0f);
    }
    StatGraphMax[0] = StatGraphMax[1] = 0;
    for (i = 0; i < 4; i++) {
        graphNum = PResPlayer[i].unk024 + 2;
        PResPlayer[i].unk026[0][graphNum - 1] = PResPlayer[i].unk004;
        PResPlayer[i].unk026[1][graphNum - 1] = PResPlayer[i].unk006;
    }
    if (PResTeamF) {
        for (j = 0; j < graphNum; j++) {
            for (i = 0; i < 4; i += 2) {
                PResPlayer[i].unk026[0][j] += PResPlayer[i + 1].unk026[0][j];
                PResPlayer[i].unk026[1][j] += PResPlayer[i + 1].unk026[1][j];
            }
        }
    }
    for (i = 0; i < 4; i++) {
        graphP = PResPlayer[i].unk026[0];
        for (j = 0; j < graphNum; j++, graphP++) {
            if (StatGraphMax[0] < *graphP) {
                StatGraphMax[0] = *graphP;
            }
        }
        graphP = PResPlayer[i].unk026[1];
        for (j = 0; j < graphNum; j++, graphP++) {
            if (StatGraphMax[1] < *graphP) {
                StatGraphMax[1] = *graphP;
            }
        }
    }
    OSReport("Max %d:%d\n", StatGraphMax[0], StatGraphMax[1]);
    GraphAnimP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3F));
    HuSprGrpDrawNoSet(grpId, 64);
    DetailCursorPosX = DetailSelIdx = DetailGrpOfsX = DetailGrpIdxOfsX = 0.0f;
    grpId = HuSprGrpCreate(161);
    DetailGrpId = grpId;
    if (PResTeamF == FALSE) {
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3A));
    } else {
        animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x3B));
    }
    sprId = HuSprCreate(animP, 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 318.0f, 220.0f);
    animP = HuSprAnimDataRead(DATANUM(DATA_partyresult, 0x2F));
    memberNo = 1;
    for (i = 0; i < 10; i++) {
        if (PResTeamF == FALSE) {
            for (j = 0; j < 4; j++) {
                value = PResPlayer[j].unk010[i];
                if (value < 0) {
                    value = 0;
                }
                sprintf(str, "%03d   ", value);
                for (k = digitNum = 0; k < 3; k++) {
                    if (str[k] == ' ') {
                        break;
                    }
                    if (str[k] == '0' && digitNum == 0 && k != 2) {
                        continue;
                    }
                    digitNum++;
                    sprId = HuSprCreate(animP, 95 - k, 0);
                    HuSprGrpMemberSet(grpId, memberNo, sprId);
                    HuSprPosSet(grpId, memberNo, -57.0f + ((i * 74) + (k * 20) + 22), (j * 53) + 156);
                    HuSprScaleSet(grpId, memberNo, 0.95f, 1.0f);
                    HuSprBankSet(grpId, memberNo, str[k] & 0xF);
                    HuSprColorSet(grpId, memberNo, 250, 220, 163);
                    HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_LINEAR);
                    memberNo++;
                }
            }
        } else {
            for (j = 0; j < 2; j++) {
                value = PResPlayer[j * 2].unk010[i] + PResPlayer[(j * 2) + 1].unk010[i];
                if (value < 0) {
                    value = 0;
                }
                if (value < 1000) {
                    sprintf(str, "%03d   ", value);
                    for (k = digitNum = 0; k < 3; k++) {
                        if (str[k] == ' ') {
                            break;
                        }
                        if (str[k] == '0' && digitNum == 0 && k != 2) {
                            continue;
                        }
                        digitNum++;
                        sprId = HuSprCreate(animP, 95 - k, 0);
                        HuSprGrpMemberSet(grpId, memberNo, sprId);
                        HuSprPosSet(grpId, memberNo, -57.0f + ((i * 74) + (k * 20) + 22), (j * 53 * 2) + 182);
                        HuSprScaleSet(grpId, memberNo, 0.95f, 1.0f);
                        HuSprBankSet(grpId, memberNo, str[k] & 0xF);
                        HuSprColorSet(grpId, memberNo, 250, 220, 163);
                        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_LINEAR);
                        memberNo++;
                    }
                } else {
                    sprintf(str, "%04d    ", value);
                    for (k = digitNum = 0; k < 4; k++) {
                        if (str[k] == ' ') {
                            break;
                        }
                        if (str[k] == '0' && digitNum == 0 && k != 2) {
                            continue;
                        }
                        digitNum++;
                        sprId = HuSprCreate(animP, 95 - k, 0);
                        HuSprGrpMemberSet(grpId, memberNo, sprId);
                        HuSprPosSet(grpId, memberNo, -57.0f + ((i * 74) + (k * 15) + 18), (j * 53 * 2) + 182);
                        HuSprScaleSet(grpId, memberNo, 0.7125f, 1.0f);
                        HuSprBankSet(grpId, memberNo, str[k] & 0xF);
                        HuSprColorSet(grpId, memberNo, 250, 220, 163);
                        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_LINEAR);
                        memberNo++;
                    }
                }
            }
        }
    }
    HuSprGrpDrawNoSet(grpId, 64);
    HuSprGrpPosSet(grpId, 149.0f, 0.0f);
    HuSprGrpScissorSet(grpId, 95, 91, 516, 258);
    FingerMdlId = Hu3DModelCreateData(DATANUM(DATA_partyresult, 0x40));
    Hu3DModelCameraSet(FingerMdlId, HU3D_CAM2);
    Hu3DModelAttrSet(FingerMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(FingerMdlId, HU3D_MOTATTR_LOOP);
}

/* 1789 insns */
void PResStatMain(void)
{
    float t;
    s16 i;
    s16 j;
    u32 mess;
    s16 graphType;
    s16 comF;
    s16 grpNum;
    grpNum = (PResTeamF != FALSE) ? 2 : 4;
    for (i = 0; i < 4; i++) {
        StatScorePosSet(i, 640.0f, 0.0f);
    }
    StatDetailPosSet(640.0f, 0.0f);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for (j = 1; j < 25; j++) {
        for (i = 0; i < 4; i++) {
            if (j - i < 0) {
                continue;
            }
            if (j - i > 20.0) {
                continue;
            }
            t = (j - i) / 20.0;
            StatScorePosSet(i, 640.0 * (1.0 - HuSin(90.0f * t)), 0.0f);
        }
        HuWinPosSet(HelpWinId, 8.0f, 406.0 + (100.0 * HuCos(90.0f * t)));
        HuPrcVSleep();
    }
scorePage:
    for (i = 0; i < 4; i++) {
        if (GwPlayerConf[i].type == 0) {
            break;
        }
    }
    if (i == 4) {
        comF = TRUE;
    }
    else {
        comF = FALSE;
    }
    PResBtnAWait();
    HuAudFXPlay(1);
    for (j = 1; j <= 20; j++) {
        t = j / 20.0;
        for (i = 0; i < 4; i++) {
            StatScorePosSet(i, 640.0 * (1.0 - HuCos(90.0f * t)), 0.0f);
        }
        HuWinPosSet(HelpWinId, 8.0f, 406.0 + (100.0 * HuSin(90.0f * t)));
        HuPrcVSleep();
    }
    HuWinMesSet(HelpWinId, 0x2001B);
    for (j = 1; j <= 20; j++) {
        t = j / 20.0;
        StatDetailPosSet(660.0 * (1.0 - HuSin(90.0f * t)), 0.0f);
        HuWinPosSet(HelpWinId, 8.0f, 340.0 + (150.0 * HuCos(90.0f * t)));
        HuPrcVSleep();
    }
    HuWinHomeClear(MessWinId);
    HuWinExOpen(MessWinId);
detailPage:
    HuWinMesSet(MessWinId, 655360.0f + DetailSelIdx + DetailGrpIdxOfsX);
    if (comF) {
        HuPrcSleep(30);
    }
    while (!(HuPadBtnDown[0] & PAD_BUTTON_A) && comF == FALSE) {
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            HuWinExClose(MessWinId);
            for (j = 1; j <= 20; j++) {
                t = j / 20.0;
                StatDetailPosSet(660.0 * (1.0 - HuCos(90.0f * t)), 0.0f);
                HuWinPosSet(HelpWinId, 8.0f, 340.0 + (150.0 * HuSin(90.0f * t)));
                HuPrcVSleep();
            }
            HuWinMesSet(HelpWinId, 0x2000A);
            for (j = 1; j <= 20; j++) {
                t = j / 20.0;
                for (i = 0; i < 4; i++) {
                    StatScorePosSet(i, 640.0 * (1.0 - HuSin(90.0f * t)), 0.0f);
                }
                HuWinPosSet(HelpWinId, 8.0f, 406.0 + (100.0 * HuCos(90.0f * t)));
                HuPrcVSleep();
            }
            goto scorePage;
        }
        else if (HuPadDStk[0] & PAD_BUTTON_LEFT) {
            if (0.0f == DetailSelIdx) {
                if (DetailGrpIdxOfsX > 0.0f) {
                    HuAudFXPlay(0);
                    for (i = 1; i <= 10; i++) {
                        t = i / 10.0;
                        DetailGrpOfsX = (74.0f * -DetailGrpIdxOfsX) + (74.0 * HuSin(90.0f * t));
                        StatDetailPosSet(0.0f, 0.0f);
                        HuPrcVSleep();
                    }
                    DetailGrpIdxOfsX -= 1.0f;
                    DetailGrpOfsX = 74.0f * -DetailGrpIdxOfsX;
                    HuWinMesSet(MessWinId, 655360.0f + DetailSelIdx + DetailGrpIdxOfsX);
                }
            }
            else {
                HuAudFXPlay(0);
                for (i = 1; i <= 10; i++) {
                    t = i / 10.0;
                    DetailCursorPosX = (74.0f * DetailSelIdx) - (74.0 * HuSin(90.0f * t));
                    StatDetailPosSet(0.0f, 0.0f);
                    HuPrcVSleep();
                }
                DetailSelIdx -= 1.0f;
                DetailCursorPosX = 74.0f * DetailSelIdx;
                HuWinMesSet(MessWinId, 655360.0f + DetailSelIdx + DetailGrpIdxOfsX);
            }
        }
        else if (HuPadDStk[0] & PAD_BUTTON_RIGHT) {
            if (DetailSelIdx >= 5.0f) {
                if (DetailGrpIdxOfsX <= 3.0f) {
                    HuAudFXPlay(0);
                    for (i = 1; i <= 10; i++) {
                        t = i / 10.0;
                        DetailGrpOfsX = (74.0f * -DetailGrpIdxOfsX) - (74.0 * HuSin(90.0f * t));
                        StatDetailPosSet(0.0f, 0.0f);
                        HuPrcVSleep();
                    }
                    DetailGrpIdxOfsX += 1.0f;
                    DetailGrpOfsX = 74.0f * -DetailGrpIdxOfsX;
                    HuWinMesSet(MessWinId, 655360.0f + DetailSelIdx + DetailGrpIdxOfsX);
                }
            }
            else {
                HuAudFXPlay(0);
                for (i = 1; i <= 10; i++) {
                    t = i / 10.0;
                    DetailCursorPosX = (74.0f * DetailSelIdx) + (74.0 * HuSin(90.0f * t));
                    StatDetailPosSet(0.0f, 0.0f);
                    HuPrcVSleep();
                }
                DetailSelIdx += 1.0f;
                DetailCursorPosX = 74.0f * DetailSelIdx;
                HuWinMesSet(MessWinId, 655360.0f + DetailSelIdx + DetailGrpIdxOfsX);
            }
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    graphType = 0;
    PlayerSel = 0;
    HuWinHomeClear(MessWinId);
    for (i = 0; i < grpNum; i++) {
        GraphSprP[i]->work[1] = graphType;
    }
    HuWinMesSet(HelpWinId, 0x2001C);
    HuSprTPLvlSet(DetailOverGrpId, 3, 1.0f);
    HuSprTPLvlSet(DetailOverGrpId, 4, 0.0f);
    Hu3DModelAttrReset(FingerMdlId, HU3D_ATTR_DISPOFF);
    for (j = 0; j < grpNum; j++) {
        HuSprPriSet(DetailOverGrpId, j + 5, 106);
    }
    HuSprPriSet(DetailOverGrpId, (PlayerSel / 2) + 5, 105);
    StatFingerPosSet(PlayerSel);
    for (i = 1; i <= 20; i++) {
        t = i / 20.0;
        HuSprGrpTPLvlSet(DetailGrpId, 1.0 - t);
        HuSprTPLvlSet(DetailOverGrpId, 2, 1.0 - t);
        Hu3DModelScaleSet(FingerMdlId, 1.5 * t, 1.5 * t, 1.5 * t);
        HuPrcVSleep();
    }
    if (PResTeamF == FALSE) {
        mess = GwPlayerConf[PlayerSel].charNo;
    }
    else {
        mess = PResTeamNameMesGet(PResCharNo[PlayerSel & 2], PResCharNo[(PlayerSel & 2) + 1]);
    }
    HuWinInsertMesSet(MessWinId, mess, 0);
    HuWinMesSet(MessWinId, 0xA000A + graphType);
    if (comF) {
        HuPrcSleep(30);
    }
    while (!(HuPadBtnDown[0] & PAD_BUTTON_A) && comF == FALSE) {
        if (HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            HuWinHomeClear(MessWinId);
            for (i = 1; i <= 20; i++) {
                t = i / 20.0;
                HuSprGrpTPLvlSet(DetailGrpId, t);
                HuSprTPLvlSet(DetailOverGrpId, 2, t);
                t = 1.0 - t;
                Hu3DModelScaleSet(FingerMdlId, 1.5 * t, 1.5 * t, 1.5 * t);
                HuPrcVSleep();
            }
            HuWinMesSet(HelpWinId, 0x2001B);
            goto detailPage;
        }
        if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
            HuAudFXPlay(0);
            if (graphType == 0) {
                HuSprPriSet(DetailOverGrpId, 3, 110);
                HuSprPriSet(DetailOverGrpId, 4, 111);
                HuSprTPLvlSet(DetailOverGrpId, 4, 1.0f);
            }
            else {
                HuSprPriSet(DetailOverGrpId, 3, 111);
                HuSprPriSet(DetailOverGrpId, 4, 110);
                HuSprTPLvlSet(DetailOverGrpId, 3, 1.0f);
            }
            for (i = 1; i <= 20; i++) {
                t = i / 20.0;
                if (graphType == 0) {
                    HuSprTPLvlSet(DetailOverGrpId, 3, 1.0 - t);
                }
                else {
                    HuSprTPLvlSet(DetailOverGrpId, 4, 1.0 - t);
                }
                for (j = 0; j < grpNum; j++) {
                    HuSprTPLvlSet(DetailOverGrpId, j + 5, 1.0 - t);
                }
                HuPrcVSleep();
            }
            graphType ^= 1;
            for (i = 0; i < grpNum; i++) {
                GraphSprP[i]->work[1] = graphType;
            }
            if (PResTeamF == FALSE) {
                mess = GwPlayerConf[PlayerSel].charNo;
            }
            else {
                mess = PResTeamNameMesGet(PResCharNo[PlayerSel & 2], PResCharNo[(PlayerSel & 2) + 1]);
            }
            HuWinInsertMesSet(MessWinId, mess, 0);
            HuWinMesSet(MessWinId, 0xA000A + graphType);
            for (i = 1; i <= 10; i++) {
                t = i / 10.0;
                for (j = 0; j < grpNum; j++) {
                    HuSprTPLvlSet(DetailOverGrpId, j + 5, t);
                }
                HuPrcVSleep();
            }
        }
        if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
            HuAudFXPlay(0);
            PlayerSel--;
            if (PlayerSel < 0) {
                PlayerSel = 3;
            }
            if (PResTeamF == FALSE) {
                for (j = 0; j < 4; j++) {
                    HuSprPriSet(DetailOverGrpId, j + 5, 106);
                }
                HuSprPriSet(DetailOverGrpId, PlayerSel + 5, 105);
                mess = GwPlayerConf[PlayerSel].charNo;
            }
            else {
                HuSprPriSet(DetailOverGrpId, ((PlayerSel / 2) ^ 1) + 5, 106);
                HuSprPriSet(DetailOverGrpId, (PlayerSel / 2) + 5, 105);
                mess = PResTeamNameMesGet(PResCharNo[PlayerSel & 2], PResCharNo[(PlayerSel & 2) + 1]);
            }
            StatFingerPosSet(PlayerSel);
            HuWinInsertMesSet(MessWinId, mess, 0);
            HuWinMesSet(MessWinId, 0xA000A + graphType);
        }
        else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
            HuAudFXPlay(0);
            PlayerSel++;
            if (PlayerSel >= 4) {
                PlayerSel = 0;
            }
            if (PResTeamF == FALSE) {
                for (j = 0; j < 4; j++) {
                    HuSprPriSet(DetailOverGrpId, j + 5, 106);
                }
                HuSprPriSet(DetailOverGrpId, PlayerSel + 5, 105);
                mess = GwPlayerConf[PlayerSel].charNo;
            }
            else {
                HuSprPriSet(DetailOverGrpId, ((PlayerSel / 2) ^ 1) + 5, 106);
                HuSprPriSet(DetailOverGrpId, (PlayerSel / 2) + 5, 105);
                mess = PResTeamNameMesGet(PResCharNo[PlayerSel & 2], PResCharNo[(PlayerSel & 2) + 1]);
            }
            StatFingerPosSet(PlayerSel);
            HuWinInsertMesSet(MessWinId, mess, 0);
            HuWinMesSet(MessWinId, 0xA000A + graphType);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 38 insns */
static void StatFingerPosSet(s16 playerSel)
{
    HuVecF pos2D;
    HuVecF pos;
    pos2D.x = 27.0f;
    pos2D.y = (playerSel * 53) + 118;
    pos2D.z = 6500.0f;
    Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
    Hu3DModelPosSetV(FingerMdlId, &pos);
}

/* 404 insns */
static void StatScorePosSet(s16 playerSel, float x, float y)
{
    HuVecF pos2D;
    HuVecF pos;
    s16 order[4];
    s16 rank[4];
    s16 posNo[4];
    s16 teamIdx[4];
    s16 i;
    s32 ofsY;
    if (PResTeamF == FALSE) {
        PResResultOrderGet(order, rank, posNo);
        pos2D.x = 140.0f + x;
        pos2D.y = y + ((playerSel * 75) + 150);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(ToueiMdlId[order[playerSel]], &pos);
        Hu3DModelScaleSet(ToueiMdlId[order[playerSel]], 0.4f, 0.4f, 0.2f);
        pos2D.x = 210.0f + x;
        pos2D.y = y + ((playerSel * 75) + 150);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(StarMdlId[order[playerSel]], &pos);
        pos2D.x = 380.0f + x;
        pos2D.y = y + ((playerSel * 75) + 150);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(CoinMdlId[order[playerSel]], &pos);
        HuSprGrpPosSet(ScoreGrpId[order[playerSel]], x, y);
    }
    else if (playerSel < 2) {
        PResResultTeamOrderGet(order);
        if (order[0] == 0) {
            for (i = 0; i < 4; i++) {
                teamIdx[i] = i;
            }
        }
        else {
            for (i = 0; i < 2; i++) {
                teamIdx[i] = i + 2;
            }
            for (i = 0; i < 2; i++) {
                teamIdx[i + 2] = i;
            }
        }
        for (i = 0; i < 2; i++) {
            pos2D.x = 140.0f + x;
            if (teamIdx[i] & 1) {
                ofsY = 36;
            }
            else {
                ofsY = -36;
            }
            ofsY = (playerSel * 150) + ofsY;
            pos2D.y = y + (ofsY + 180);
            pos2D.z = 6500.0f;
            Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
            Hu3DModelPosSetV(ToueiMdlId[teamIdx[i + (playerSel * 2)]], &pos);
            Hu3DModelScaleSet(ToueiMdlId[teamIdx[i + (playerSel * 2)]], 0.4f, 0.4f, 0.2f);
        }
        pos2D.x = 210.0f + x;
        pos2D.y = y + ((playerSel * 150) + 210);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(StarMdlId[playerSel], &pos);
        pos2D.x = 380.0f + x;
        pos2D.y = y + ((playerSel * 150) + 210);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(CoinMdlId[playerSel], &pos);
        HuSprGrpPosSet(ScoreGrpId[playerSel], x, y);
        HuWinPosSet(TeamNameWinId[playerSel], 360.0f + x, y + ((playerSel * 150) + 190));
    }
}

/* 241 insns */
static void StatDetailPosSet(float x, float y)
{
    HuVecF pos2D;
    HuVecF pos;
    float sx;
    float sy;
    float w;
    float h;
    s16 i;
    for (i = 0; i < 4; i++) {
        pos2D.x = 52.0f + x;
        pos2D.y = y + ((i * 53) + 143);
        pos2D.z = 6500.0f;
        Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
        Hu3DModelPosSetV(ToueiMdlId[i], &pos);
        Hu3DModelScaleSet(ToueiMdlId[i], 0.3f, 0.3f, 0.3f);
    }
    HuSprGrpPosSet(DetailOverGrpId, x, y);
    HuSprPosSet(DetailOverGrpId, 2, 134.0f + DetailCursorPosX, 220.0f);
    HuSprGrpPosSet(DetailGrpId, (149.0f + x) + DetailGrpOfsX, y);
    sx = 95.33333333333334 + x;
    sy = 91.0f + y;
    w = 515.55554f;
    h = 258.0f;
    if (sx < 0.0f) {
        w += sx;
        sx = 0.0f;
    }
    else if (sx > 640.0f) {
        HuSprGrpPosSet(DetailGrpId, 1500.0f, 0.0f);
        return;
    }
    if (sx + w > 640.0f) {
        w = 640.0f - sx;
    }
    if (sy < 0.0f) {
        h += sy;
        sy = 0.0f;
    }
    else if (sy > 480.0f) {
        return;
    }
    if (sy + h > 480.0f) {
        h = 480.0f - sy;
    }
    if (w <= 0.0f || h <= 0.0f) {
        HuSprGrpPosSet(DetailGrpId, 1500.0f, 0.0f);
    }
    else {
        HuSprGrpScissorSet(DetailGrpId, sx, sy, w, h);
    }
}

/* 112 insns */
static void StatModelUpdate(void)
{
    float coinRot = 0.0f;
    float starRot = 0.0f;
    s16 i;
    s16 num;
    while (1) {
        num = (PResTeamF) ? 2 : 4;
        for (i = 0; i < num; i++) {
            Hu3DModelRotSet(StarMdlId[i], 0.0f, starRot, 0.0f);
            Hu3DModelRotSet(CoinMdlId[i], 0.0f, coinRot, 0.0f);
        }
        coinRot += 1.0f;
        if (coinRot > 360.0f) {
            coinRot -= 360.0f;
        }
        starRot += 1.2;
        if (starRot > 360.0f) {
            starRot -= 360.0f;
        }
        Hu3DGLightPosSet(PResLightId, 0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f);
        HuPrcVSleep();
    }
}

/* 375 insns */
static void StatBackDraw(s16 layerNo)
{
    Mtx44 proj;
    Mtx modelview;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    if (Hu3DCameraNo == 1) {
        C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        PSMTXIdentity(modelview);
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
        HuSprTexLoad(BackAnimP, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2u16(0, 0);
        GXTexCoord2f32(BackScrollX, BackScrollY);
        GXPosition2u16(640, 0);
        GXTexCoord2f32(5.0 + BackScrollX, BackScrollY);
        GXPosition2u16(640, 480);
        GXTexCoord2f32(5.0 + BackScrollX, 5.0 + BackScrollY);
        GXPosition2u16(0, 480);
        GXTexCoord2f32(BackScrollX, 5.0 + BackScrollY);
        GXEnd();
        BackScrollX += 0.005;
        if (BackScrollX >= 1.0) {
            BackScrollX = 0.0;
        }
        BackScrollY += 0.005;
        if (BackScrollY >= 1.0) {
            BackScrollY = 0.0;
        }
    }
}

/* 0x257 */ GXColor lbl_1_data_257[6] = {
    { 0xDA, 0x32, 0x80, 0xFF },
    { 0x1E, 0xD7, 0x4B, 0xFF },
    { 0xF5, 0x91, 0x0F, 0xFF },
    { 0x0C, 0xC1, 0xF2, 0xFF },
    { 0xFF, 0x0C, 0x0C, 0xFF },
    { 0x0C, 0x0C, 0xFF, 0xFF }
};

/* 996 insns */
static void StatGraphDraw(HUSPRITE *sp)
{
    Mtx mtx;
    HuVec2f p[4];
    HuVec2f o[3];
    HuVec2f d[3];
    HuVec2f n[3];
    HuVec2f vtx[4];
    GXColor color;
    float alpha;
    s16 *data;
    s16 i;
    s16 num;
    s16 type;
    s16 playerNo;
    playerNo = sp->work[0];
    type = sp->work[1];
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    color.r = color.g = color.b = color.a = 0xFF;
    GXSetChanAmbColor(GX_COLOR0A0, color);
    GXSetChanMatColor(GX_COLOR0A0, color);
    if (PResTeamF == FALSE) {
        if (PlayerSel == playerNo) {
            alpha = ((GlobalCounter & 7) < 6) ? 1 : 0;
        }
        else {
            alpha = 1.0f;
        }
        color.r = lbl_1_data_257[playerNo].r;
        color.g = lbl_1_data_257[playerNo].g;
        color.b = lbl_1_data_257[playerNo].b;
    }
    else {
        if (PlayerSel / 2 == playerNo) {
            alpha = ((GlobalCounter & 7) < 6) ? 1 : 0;
        }
        else {
            alpha = 1.0f;
        }
        color.r = lbl_1_data_257[playerNo + 4].r;
        color.g = lbl_1_data_257[playerNo + 4].g;
        color.b = lbl_1_data_257[playerNo + 4].b;
    }
    color.a = alpha * sp->a;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    if (sp->attr & HUSPR_ATTR_ADDCOL) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    }
    else if (sp->attr & HUSPR_ATTR_INVCOL) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
    }
    else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    PSMTXScale(mtx, sp->scale.x, sp->scale.y, 1.0f);
    mtxTransCat(mtx, sp->pos.x - 219.0, 126.0 + sp->pos.y, 0.0f);
    PSMTXConcat(*sp->groupMtx, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    HuSprTexLoad(GraphAnimP, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    if (PResTeamF == FALSE) {
        data = PResPlayer[playerNo].unk026[type];
        num = PResPlayer[playerNo].unk024 + 2;
    }
    else {
        data = PResPlayer[playerNo * 2].unk026[type];
        num = PResPlayer[playerNo * 2].unk024 + 2;
    }
    for (i = 0; i < num - 1; i++, data++) {
        p[1].x = 5.0 + (438.0 * ((float)i / ((float)num - 1.0)));
        p[1].y = (252.0 * -(data[0] / (3.0f + (1.1f * StatGraphMax[type])))) - 5.0;
        if (i != 0) {
            p[0].x = 5.0 + (438.0 * ((float)(i - 1) / ((float)num - 1.0)));
            p[0].y = (252.0 * -(data[-1] / (3.0f + (1.1f * StatGraphMax[type])))) - 5.0;
        }
        else {
            p[0].x = p[1].x - 2.0f;
            p[0].y = p[1].y;
        }
        if (i + 1 < num) {
            p[2].x = 5.0 + (438.0 * ((float)(i + 1) / ((float)num - 1.0)));
            p[2].y = (252.0 * -(data[1] / (3.0f + (1.1f * StatGraphMax[type])))) - 5.0;
        }
        else {
            p[2].x = 2.0f + p[1].x;
            p[2].y = p[1].y;
        }
        if (i + 2 < num) {
            p[3].x = 5.0 + (438.0 * ((float)(i + 2) / ((float)num - 1.0)));
            p[3].y = (252.0 * -(data[2] / (3.0f + (1.1f * StatGraphMax[type])))) - 5.0;
        }
        else {
            p[3].x = 2.0f + p[2].x;
            p[3].y = p[2].y;
        }
        d[0].x = p[1].x - p[0].x;
        d[0].y = p[1].y - p[0].y;
        n[0].x = -d[0].y;
        n[0].y = d[0].x;
        d[1].x = p[2].x - p[1].x;
        d[1].y = p[2].y - p[1].y;
        n[1].x = -d[1].y;
        n[1].y = d[1].x;
        d[2].x = p[3].x - p[2].x;
        d[2].y = p[3].y - p[2].y;
        n[2].x = -d[2].y;
        n[2].y = d[2].x;
        StatLineNorm(&n[0], &n[0]);
        StatLineScale(&n[0], &n[0], 2.0f);
        StatLineTrans(&p[0], &n[0], &o[0]);
        StatLineNorm(&n[1], &n[1]);
        StatLineScale(&n[1], &n[1], 2.0f);
        StatLineTrans(&p[1], &n[1], &o[1]);
        StatLineNorm(&n[2], &n[2]);
        StatLineScale(&n[2], &n[2], 2.0f);
        StatLineTrans(&p[2], &n[2], &o[2]);
        if (StatLinePosGet(&o[0], &d[0], &o[1], &d[1], &vtx[0]) == FALSE) {
            vtx[0] = o[1];
        }
        if (StatLinePosGet(&o[1], &d[1], &o[2], &d[2], &vtx[1]) == FALSE) {
            vtx[1] = o[2];
        }
        StatLineScale(&n[0], &n[0], -1.0f);
        StatLineTrans(&p[0], &n[0], &o[0]);
        StatLineScale(&n[1], &n[1], -1.0f);
        StatLineTrans(&p[1], &n[1], &o[1]);
        StatLineScale(&n[2], &n[2], -1.0f);
        StatLineTrans(&p[2], &n[2], &o[2]);
        if (StatLinePosGet(&o[0], &d[0], &o[1], &d[1], &vtx[3]) == FALSE) {
            vtx[3] = o[1];
        }
        if (StatLinePosGet(&o[1], &d[1], &o[2], &d[2], &vtx[2]) == FALSE) {
            vtx[2] = o[2];
        }
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(vtx[0].x, vtx[0].y, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(vtx[1].x, vtx[1].y, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(vtx[2].x, vtx[2].y, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(vtx[3].x, vtx[3].y, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}

/* 97 insns */
static BOOL StatLinePosGet(HuVec2f *p0, HuVec2f *d0, HuVec2f *p1, HuVec2f *d1, HuVec2f *out)
{
    float t1;
    float den;
    float t0;
    BOOL result = TRUE;
    t0 = (d0->x * (p1->y - p0->y)) - (d0->y * (p1->x - p0->x));
    den = (d1->x * d0->y) - (d1->y * d0->x);
    if (HuAbs(den) > 0.001f) {
        t0 /= (d1->x * d0->y) - (d1->y * d0->x);
    }
    else {
        return FALSE;
    }
    if (0.0 != d0->x) {
        t1 = ((p1->x + (t0 * d1->x)) - p0->x) / d0->x;
    }
    else {
        t1 = ((p1->y + (t0 * d1->y)) - p0->y) / d0->y;
    }
    out->x = p0->x + (t1 * d0->x);
    out->y = p0->y + (t1 * d0->y);
    return TRUE;
}

/* 78 insns */
static void StatLineNorm(HuVec2f *in, HuVec2f *out)
{
    float mag = HuMagVec2F(in);
    out->x = in->x / mag;
    out->y = in->y / mag;
}

/* 7 insns */
static void StatLineScale(HuVec2f *in, HuVec2f *out, float scale)
{
    out->x = in->x * scale;
    out->y = in->y * scale;
}

/* 9 insns */
static void StatLineTrans(HuVec2f *a, HuVec2f *b, HuVec2f *out)
{
    out->x = a->x + b->x;
    out->y = a->y + b->y;
}

