/*
 * storyresultdll rank.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/storyresultdll/asm/REL/storyresultdll/rank.s.
 */

#include "REL/storyresultDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "messdir_enum.h"
#include "math.h"
#include "humath.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_78 = 10.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 510.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 44.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 0.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 288.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 90.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 122.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 88.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 8400.0f; /* 0x98 */
static const float lbl_1_rodata_9C = -10000.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 404.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 0.9f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 1.5f; /* 0xA8 */
static const float lbl_1_rodata_AC = 50.0f; /* 0xAC */
static const double lbl_1_rodata_B0 = 180.0; /* 0xB0 */
static const double lbl_1_rodata_B8 = 3.141592653589793; /* 0xB8 */
static const float lbl_1_rodata_C0 = 0.5f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 8510.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 0.8f; /* 0xC8 */
static const float lbl_1_rodata_CC = 1.1f; /* 0xCC */
static const float lbl_1_rodata_D0 = 1.0f; /* 0xD0 */
/* 0xD8 lbl_1_rodata_D8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_E0 = 1.5; /* 0xE0 */
static const double lbl_1_rodata_E8 = 7.0; /* 0xE8 */
static const double lbl_1_rodata_F0 = 90.0; /* 0xF0 */
static const double lbl_1_rodata_F8 = 30.0; /* 0xF8 */
static const double lbl_1_rodata_100 = 60.0; /* 0x100 */
static const double lbl_1_rodata_108 = 1.0; /* 0x108 */
static const double lbl_1_rodata_110 = 0.5; /* 0x110 */
static const double lbl_1_rodata_118 = 360.0; /* 0x118 */
static const double lbl_1_rodata_120 = 20.0; /* 0x120 */
static const double lbl_1_rodata_128 = 5.0; /* 0x128 */
/* 0x130 lbl_1_rodata_130 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x131 lbl_1_rodata_131 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_134 = 480.0f; /* 0x134 */
static const float lbl_1_rodata_138 = 640.0f; /* 0x138 */
static const double lbl_1_rodata_140 = 0.005; /* 0x140 */
static const double lbl_1_rodata_148 = 0.0; /* 0x148 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x94 gap_05_00000094_bss (0x4): alignment gap */
/* 0x92 */ static HUSPRGRPID RankBarGrpId;
/* 0x90 */ static HUSPRGRPID RankBoardNameGrpId;
/* 0x8E */ static s16 RankStoryWin;
/* 0x8C */ static s16 RankHelpWin;
/* 0x82 */ static s16 RankBoardModelId[5];
/* 0x78 */ static s16 RankModelId[5];
/* 0x70 */ static s16 RankEffModelId[4];
/* 0x6C */ static ANIMDATA *BackAnim;
/* 0x6A gap_05_0000006A_bss (0x2): alignment gap */
/* 0x68 */ static s16 RankParmanId;
/* 0x60 */ static double BackScrollY;
/* 0x58 */ static double BackScrollX;

/* sprite.h leaves it commented out (WipeImage); m502dll/stage.c declares it the same way */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

static void RankObjRotExec(void);
static void RankBackDraw(s16 layerNo);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x88 */ static HuVecF RankPosTbl[6] = { { 88.0f, 340.0f, 8400.0f }, { 188.0f, 205.0f, 8400.0f }, { 288.0f, 340.0f, 8400.0f }, { 388.0f, 205.0f, 8400.0f }, { 488.0f, 340.0f, 8400.0f }, { 288.0f, 250.0f, 4400.0f } };
/* 0xD0 */ static HU3DPARMANPARAM RankParmanParam = {
    10, 0,
    50.0f,
    10.0f,
    90.0f,
    { 0.0f, -0.05f, 0.0f },
    15.0f,
    0.9f,
    8.0f,
    0.95f,
    2,
    { { 255, 255, 255, 255 }, { 255, 255, 64, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 128, 128, 0 }, { 255, 64, 32, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};

/* 682 insns */
void SRankCreate(void)
{
    HUWIN *winP;
    HuVecF pos2D;
    HuVecF pos;
    s16 i;
    HU3DMODELID modelId;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s16 winW;
    s16 boardNo;
    s16 rotZ;

    BackAnim = HuSprAnimDataRead(DATANUM(DATA_storyresult, 1));
    winW = 352;
    RankStoryWin = HuWinCreate(10.0f + (510.0f - winW), 44.0f, winW, 94, 0);
    winP = &winData[RankStoryWin];
    HuWinBGTPLvlSet(RankStoryWin, 0.0f);
    HuWinPriSet(RankStoryWin, 200);
    HuWinMesSpeedSet(RankStoryWin, 0);
    HuWinDrawNoSet(RankStoryWin, 64);
    HuWinInsertMesSet(RankStoryWin, GwPlayerConf[0].charNo, 0);
    HuWinInsertMesSet(RankStoryWin, MESSNUM(MESS_STORYMODE_SYS, 12) + SRankWork.diff, 1);
    HuWinInsertMesSet(RankStoryWin, MESSNUM(MESS_STORYMODE_SYS, 16) + SRankWork.totalRank, 2);
    HuWinMesSet(RankStoryWin, MESSNUM(MESS_STORYMODE_SYS, 11));
    RankBarGrpId = grpId = HuSprGrpCreate(1);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_storyresult, 0)), 300, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprGrpDrawNoSet(grpId, 64);
    HuSprPosSet(grpId, 0, 288.0f, 90.0f);
    Hu3DLayerHookSet(0, RankBackDraw);
    HuPrcVSleep();
    ToueiDispInit();
    pos2D.x = 122.0f;
    pos2D.y = 88.0f;
    pos2D.z = 8400.0f;
    Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
    Hu3DModelPosSetV(CapsuleMdlId, &pos);
    Hu3DModelLayerSet(CapsuleMdlId, 1);
    RankHelpWin = HuWinCreate(-10000.0f, 404.0f, 560, 41, 0);
    HuWinBGTPLvlSet(RankHelpWin, 0.0f);
    HuWinAttrSet(RankHelpWin, HUWIN_ATTR_ALIGN_CENTER);
    HuWinMesSpeedSet(RankHelpWin, 0);
    HuWinDispOff(RankHelpWin);
    HuWinMesSet(RankHelpWin, MESSNUM(MESS_SYSHELP, 10));
    RankBoardNameGrpId = grpId = HuSprGrpCreate(5);
    for(i = 0; i < 5; i++) {
        boardNo = GwCommon.storyBoardNo[i];
        if(SRankWork.boardNum > i) {
            modelId = Hu3DModelCreateData(boardNo + DATANUM(DATA_storyresult, 17));
        } else {
            modelId = Hu3DModelCreateData(DATANUM(DATA_storyresult, 10));
        }
        RankBoardModelId[i] = modelId;
        Hu3D2Dto3D(&RankPosTbl[i], HU3D_CAM2, &pos);
        Hu3DModelPosSetV(modelId, &pos);
        Hu3DModelLayerSet(modelId, 0);
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        Hu3DModelScaleSet(modelId, 0.9f, 0.9f, 0.9f);
        if(SRankWork.boardNum < i) {
            RankModelId[i] = HU3D_MODELID_NONE;
        } else {
            modelId = Hu3DModelCreateData(DATANUM(DATA_storyresult, 14) - SRankWork.boardRank[i]);
            RankModelId[i] = modelId;
            Hu3D2Dto3D(&RankPosTbl[i], HU3D_CAM2, &pos);
            Hu3DModelPosSetV(modelId, &pos);
            Hu3DModelLayerSet(modelId, 1);
            Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelCameraSet(modelId, HU3D_CAM2);
            Hu3DModelScaleSet(modelId, 1.5f, 1.5f, 1.5f);
            if(SRankWork.boardNum - 1 <= i) {
                Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
            }
        }
        sprId = HuSprCreate(HuSprAnimDataRead(boardNo + DATANUM(DATA_storyresult, 2)), 100, 0);
        HuSprGrpMemberSet(grpId, i, sprId);
        HuSprPosSet(grpId, i, RankPosTbl[i].x, 50.0f + RankPosTbl[i].y);
        if(SRankWork.boardNum - 1 <= i) {
            HuSprScaleSet(grpId, i, 0.0f, 0.0f);
        }
    }
    HuSprGrpDrawNoSet(grpId, 64);
    modelId = RankBoardModelId[SRankWork.boardNum - 1];
    Hu3D2Dto3D(&RankPosTbl[5], HU3D_CAM2, &pos);
    Hu3DModelPosSetV(modelId, &pos);
    Hu3DModelLayerSet(modelId, 1);
    modelId = RankModelId[SRankWork.boardNum - 1];
    Hu3DModelPosSetV(modelId, &pos);
    Hu3DModelLayerSet(modelId, 2);
    HuSprDrawNoSet(grpId, SRankWork.boardNum - 1, 0);
    for(i = 1; i < 5; i++) {
        if(SRankWork.boardNum > i) {
            modelId = Hu3DModelCreateData(DATANUM(DATA_storyresult, 9));
            RankEffModelId[i - 1] = modelId;
            pos2D = RankPosTbl[i - 1];
            VECSubtract(&pos2D, &RankPosTbl[i], &pos2D);
            rotZ = HuAtan(pos2D.x, pos2D.y);
            pos2D = RankPosTbl[i - 1];
            VECAdd(&pos2D, &RankPosTbl[i], &pos2D);
            VECScale(&pos2D, &pos2D, 0.5f);
            pos2D.z = 8510.0f;
            Hu3D2Dto3D(&pos2D, HU3D_CAM2, &pos);
            Hu3DModelPosSetV(modelId, &pos);
            Hu3DModelLayerSet(modelId, 0);
            Hu3DModelCameraSet(modelId, HU3D_CAM2);
            Hu3DModelScaleSet(modelId, 0.8f, 1.1f, 1.0f);
            Hu3DModelRotSet(modelId, 0.0f, 0.0f, rotZ);
            if(SRankWork.boardNum - 1 == i) {
                Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
            }
        }
    }
    RankParmanId = Hu3DParManCreate(HuSprAnimDataRead(DATANUM(DATA_effect, 5)), 200, &RankParmanParam);
    Hu3DParManAttrSet(RankParmanId, 293);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(RankParmanId), 1);
    Hu3DParManRotSet(RankParmanId, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(RankParmanId), 3);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(RankParmanId), HU3D_CAM2);
    Hu3D2Dto3D(&RankPosTbl[5], HU3D_CAM2, &pos);
    /* retail: modelId is whatever the loops above left in it (the last effect model, or
       the current board's rank model); it is re-placed at the centre slot */
    Hu3DModelPosSetV(modelId, &pos);
    Hu3DParManPosSet(RankParmanId, pos.x, pos.y, pos.z);
    HuSprExecLayerCameraSet(64, HU3D_CAM2, 1);
}

/* 447 insns */
void SRankExec(void)
{
    HuVecF posA;
    HuVecF posB;
    HuVecF pos;
    float t;
    s16 i;
    HU3DMODELID modelId;
    s16 rankNo;

    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    WipeWait();
    rankNo = SRankWork.boardNum - 1;
    modelId = RankModelId[rankNo];
    Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(modelId, HU3D_CAM1);
    HuAudFXPlay(1407);
    for(i = 1; i <= 30; i++) {
        t = 1.5 + 7.0 * HuCos(90.0 * (i / 30.0));
        Hu3DModelScaleSet(modelId, t, t, 1.5f);
        CapsuleGlowTPLvl = HuSin(90.0 * (i / 30.0));
        if(i == 29) {
            Hu3DParManTimeLimitSet(RankParmanId, 5);
            Hu3DParManAttrReset(RankParmanId, 1);
        }
        HuPrcVSleep();
    }
    if(PResDiff == 3) {
        HuAudFXPlay(1405);
    } else {
        HuAudFXPlay(1406);
    }
    Hu3DModelCameraSet(modelId, HU3D_CAM1 | HU3D_CAM2);
    for(i = 1; i <= 60; i++) {
        CapsuleGlowTPLvl = HuCos(90.0 * (i / 60.0));
        HuPrcVSleep();
    }
    HuPrcSleep(60);
    for(i = 1; i <= 30; i++) {
        t = HuSin(90.0 * (i / 30.0));
        modelId = RankBoardModelId[rankNo];
        Hu3D2Dto3D(&RankPosTbl[5], HU3D_CAM2, &posA);
        Hu3D2Dto3D(&RankPosTbl[rankNo], HU3D_CAM2, &posB);
        VECScale(&posA, &posA, 1.0 - t);
        VECScale(&posB, &posB, t);
        VECAdd(&posA, &posB, &pos);
        Hu3DModelPosSetV(modelId, &pos);
        modelId = RankModelId[rankNo];
        Hu3DModelPosSetV(modelId, &pos);
        HuPrcVSleep();
    }
    for(i = 1; i <= 30; i++) {
        t = HuSin(90.0 * (i / 30.0));
        HuSprScaleSet(RankBoardNameGrpId, rankNo, t, t);
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    if(SRankWork.boardNum > 1) {
        rankNo = SRankWork.boardNum - 1;
        modelId = RankEffModelId[rankNo - 1];
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        for(i = 1; i < 30; i++) {
            t = 0.5 * (i / 30.0);
            posA = RankPosTbl[rankNo - 1];
            posB = RankPosTbl[rankNo];
            VECScale(&posA, &posA, 1.0 - t);
            VECScale(&posB, &posB, t);
            VECAdd(&posA, &posB, &posA);
            posA.z = 8510.0f;
            Hu3D2Dto3D(&posA, HU3D_CAM2, &pos);
            Hu3DModelPosSetV(modelId, &pos);
            HuPrcVSleep();
        }
    }
    HuWinDispOn(RankHelpWin);
    HuPrcChildCreate(RankObjRotExec, 1000, 0x3000, 0, objman);
    while((HuPadBtnDown[0] & PAD_BUTTON_A) == 0) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    WipeWait();
}

/* 184 insns */
static void RankObjRotExec(void)
{
    float ofs[5];
    float rot;
    s16 i;
    s16 time;

    while(1) {
        i = frandmod(60) + 120;
        HuPrcSleep(i);
        for(i = 0; i < 5; i++) {
            ofs[i] = (s32)frandmod(10) + 10;
        }
        for(time = 1; time <= 20; time++) {
            for(i = 0; i < 5; i++) {
                rot = ofs[i] + 360.0 * (1.0 - HuCos(90.0 * (time / 20.0)));
                if(RankModelId[i] == HU3D_MODELID_NONE) {
                    break;
                }
                Hu3DModelRotSet(RankModelId[i], 0.0f, rot, 0.0f);
            }
            HuPrcVSleep();
        }
        for(time = 1; time <= 5; time++) {
            for(i = 0; i < 5; i++) {
                rot = ofs[i] * (1.0 - HuSin(90.0 * (time / 5.0)));
                if(RankModelId[i] == HU3D_MODELID_NONE) {
                    break;
                }
                Hu3DModelRotSet(RankModelId[i], 0.0f, rot, 0.0f);
            }
            HuPrcVSleep();
        }
    }
}

/* 376 insns */
static void RankBackDraw(s16 layerNo)
{
    GXColor color = { 255, 255, 255, 255 };
    Mtx44 proj;
    Mtx modelview;

    if(Hu3DCameraNo == 2) {
        DispZClear();
        MTXOrtho(proj, 0, 480, 0, 640, 0, 10);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        MTXIdentity(modelview);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXSetViewport(0, 0, 640, 480, 0, 1);
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
        HuSprTexLoad(BackAnim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
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
        if(BackScrollX >= 1.0) {
            BackScrollX = 0.0;
        }
        BackScrollY += 0.005;
        if(BackScrollY >= 1.0) {
            BackScrollY = 0.0;
        }
    }
}
