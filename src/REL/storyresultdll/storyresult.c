/*
 * storyresultdll storyresult.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/storyresultdll/asm/REL/storyresultdll/storyresult.s.
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
#include "game/charman.h"
#include "game/saveload.h"
#include "game/init.h"
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
static const float lbl_1_rodata_30 = 100.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 30000.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 1000.0f; /* 0x38 */
static const float lbl_1_rodata_3C = -0.5f; /* 0x3C */
static const float lbl_1_rodata_40 = -1.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 0.6f; /* 0x44 */
static const float lbl_1_rodata_48 = 0.2f; /* 0x48 */
static const float lbl_1_rodata_4C = 0.1f; /* 0x4C */
static const double lbl_1_rodata_50 = 3.141592653589793; /* 0x50 */
static const double lbl_1_rodata_58 = 180.0; /* 0x58 */
static const double lbl_1_rodata_60 = 1.0; /* 0x60 */
static const float lbl_1_rodata_68 = 0.05f; /* 0x68 */
/* 0x70 lbl_1_rodata_70 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x50 */ static OMOBJ *outViewObj;
/* 0x4C */ OMOBJMAN *objman;
/* 0x4B gap_05_0000004B_bss (0x1): alignment gap */
/* 0x4A */ static u8 LanguageNo;
/* 0x48 */ s16 PResDiff;
/* 0x46 */ HU3DMODELID CharMdlId;
/* 0x34 */ u8 lbl_1_bss_34[0x12]; /* unreferenced (alignment 4) */
/* 0x32 */ static HU3DMOTID CharMotId;
/* 0x30 */ HU3DMODELID CapsuleMdlId;
/* 0x20 */ SRANKWORK SRankWork;
/* 0xC */ u8 lbl_1_bss_C[0x14]; /* unreferenced (alignment 4) */
/* 0x8 */ s32 PResGLight;
/* 0x4 */ u8 lbl_1_bss_4[0x4]; /* unreferenced (alignment 4) */
/* 0x0 */ static s32 debugCamOnF;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ static OMCAMERAVIEW CameraView1 = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 7000.0f };
/* 0x1C */ static OMCAMERAVIEW CameraView2 = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 8400.0f };

/* 199 insns */
void ObjectSetup(void)
{
    OSReport("******* PRES ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    omSysPauseEnable(FALSE);
    LanguageNo = GWLanguageGet();
    if(GwCommon.storyNo != -1 && GWPlayerCoinGet(0) <= 0) {
        omOvlGotoEx(DLL_storymodedll, 1, 0, 0);
        return;
    }
    Hu3DCameraCreate(HU3D_CAM0 | HU3D_CAM1 | HU3D_CAM2);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(HU3D_CAM1 | HU3D_CAM2, 5.0f, 100.0f, 30000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1 | HU3D_CAM2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSetMulti(HU3D_CAM0, &CameraView1);
    omCameraViewSetMulti(HU3D_CAM1 | HU3D_CAM2, &CameraView2);
    PResGLight = Hu3DGLightCreate(0.0f, 100.0f, 1000.0f, 0.0f, -0.5f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(PResGLight);
    outViewObj = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
    outViewObj->work[0] = HU3D_CAM0 | HU3D_CAM1;
    omAddObjEx(objman, 0, 32, 32, -1, DebugCamUpdate);
    HuAudSStreamPlay(27);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
    HuPrcChildCreate(PResExec, 1000, 0x3000, 0, objman);
}

/* 51 insns */
void PResExec(void)
{
    GXSetPixelFmt(GX_PF_RGBA6_Z24, GX_ZC_LINEAR);
    PResCreate();
    SRankCreate();
    SRankExec();
    if(RenderMode->aa) {
        GXSetPixelFmt(GX_PF_RGB565_Z16, GX_ZC_LINEAR);
    } else {
        GXSetPixelFmt(GX_PF_RGB8_Z24, GX_ZC_LINEAR);
    }
    if(!_CheckFlag(FLAG_MG_PRACTICE)) {
        GwPlayer[0].mgCoinBonus = 0;
    }
    _ClearFlag(FLAG_BOARD_SAVEINIT);
    SLSaveStoryExec();
    if(GwCommon.storyNo == 0) {
        omOvlReturnEx(1, 1);
    } else {
        omOvlGotoEx(DLL_storymodedll, 1, 0, 0);
    }
    while(1) {
        HuPrcVSleep();
    }
}

/* 454 insns */
void PResCreate(void)
{
    s16 i;
    s16 rank;
    s16 charNo;
    HU3DMODELID modelId;
    s16 boardNo;
    s32 boardRank;

    charNo = GwPlayerConf[0].charNo;
    if(GwCommon.storyNo == -1) {
        SRankWork.diff = 0;
        SRankWork.totalRank = 4;
        SRankWork.boardNum = 1;
        for(i = 0; i < 5; i++) {
            if(i > 3) {
                boardRank = 3;
            } else {
                boardRank = i;
            }
            SRankWork.boardRank[i] = boardRank;
            GwCommon.storyBoardNo[i] = i;
        }
    } else {
        OSReport("%d\n", GwSystem.turnNo);
        if(GwPlayerConf[0].dif == 0) {
            if(GwSystem.turnNo <= 2) {
                rank = 3;
            } else if(GwSystem.turnNo <= 5) {
                rank = 2;
            } else if(GwSystem.turnNo <= 10) {
                rank = 1;
            } else {
                rank = 0;
            }
        } else if(GwPlayerConf[0].dif == 1) {
            if(GwSystem.turnNo <= 3) {
                rank = 3;
            } else if(GwSystem.turnNo <= 6) {
                rank = 2;
            } else if(GwSystem.turnNo <= 12) {
                rank = 1;
            } else {
                rank = 0;
            }
        } else if(GwPlayerConf[0].dif == 2) {
            if(GwSystem.turnNo <= 4) {
                rank = 3;
            } else if(GwSystem.turnNo <= 8) {
                rank = 2;
            } else if(GwSystem.turnNo <= 13) {
                rank = 1;
            } else {
                rank = 0;
            }
        } else if(GwPlayerConf[0].dif == 3) {
            if(GwSystem.turnNo <= 5) {
                rank = 3;
            } else if(GwSystem.turnNo <= 9) {
                rank = 2;
            } else if(GwSystem.turnNo <= 14) {
                rank = 1;
            } else {
                rank = 0;
            }
        }
        PResDiff = rank;
        boardNo = GwCommon.storyBoardNo[GwCommon.storyNo];
        if(GwCommon.charStoryRank[boardNo][charNo] < PResDiff) {
            GwCommon.charStoryRank[boardNo][charNo] = PResDiff;
        }
        GwCommon.storyRank[GwCommon.storyNo] = rank;
        GwCommon.charStoryPlayNum[boardNo][charNo]++;
        if(GwCommon.charStoryPlayNum[boardNo][charNo] > 999) {
            GwCommon.charStoryPlayNum[boardNo][charNo] = 999;
        }
        GwCommon.storyNo++;
        SRankWork.diff = GwPlayerConf[0].dif;
        SRankWork.boardNum = GwCommon.storyNo;
        for(i = 0; i < 5; i++) {
            SRankWork.boardRank[i] = 0;
        }
        for(i = rank = 0; i < GwCommon.storyNo; i++) {
            SRankWork.boardRank[i] = GwCommon.storyRank[i];
            rank += GwCommon.storyRank[i];
            OSReport("Rank %d\n", rank);
        }
        if(rank <= 4) {
            SRankWork.totalRank = 0;
        } else if(rank <= 9) {
            SRankWork.totalRank = 1;
        } else if(rank <= 12) {
            SRankWork.totalRank = 2;
        } else if(rank <= 14) {
            SRankWork.totalRank = 3;
        } else {
            SRankWork.totalRank = 4;
        }
        for(i = 0; i < 7; i++) {
            OSReport("Rank Map%d:%d\n", i, GwCommon.charStoryRank[i][charNo]);
        }
        OSReport("Total Rank %d\n", SRankWork.totalRank);
    }
    CharMdlId = modelId = CharModelCreate(charNo, 2);
    CharMotId = CharMotionCreate(charNo, DATANUM(DATA_mariomot, 0));
    CharMotionSet(charNo, CharMotId);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    CapsuleMdlId = modelId = Hu3DModelCreateData(DATANUM(DATA_storyresult, 15));
    Hu3DModelCameraSet(modelId, HU3D_CAM2);
    Hu3DModelScaleSet(modelId, 0.6f, 0.6f, 0.2f);
    modelId = Hu3DModelCreateData(DATANUM(DATA_storyresult, 16));
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DReflectMapSet(HuDataSelHeapReadNum(DATANUM(DATA_storyresult, 24), HU_MEMNUM_OVL, HEAP_MODEL));
}

/* 728 insns */
void DebugCamUpdate(OMOBJ *obj)
{
    HuVecF pos;
    HuVecF offset;
    HuVecF dir;
    HuVecF yOfs;
    float rotZ;
    s8 stickPos;

    if(debugCamOnF) {
        CRotM[2].y += 0.1f * HuPadStkX[0];
        CRotM[2].x += 0.1f * HuPadStkY[0];
        CZoomM[2] += HuPadTrigL[0] / 2;
        CZoomM[2] -= HuPadTrigR[0] / 2;
        if(CZoomM[2] < 100.0f) {
            CZoomM[2] = 100.0f;
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
        if(stickPos != 0) {
            CenterM[2].x += 0.05f * (offset.x * stickPos);
            CenterM[2].y += 0.05f * (offset.y * stickPos);
            CenterM[2].z += 0.05f * (offset.z * stickPos);
        }
        VECNormalize(&yOfs, &offset);
        stickPos = -(HuPadSubStkY[0] & 0xF8);
        if(stickPos != 0) {
            CenterM[2].x += 0.05f * (offset.x * stickPos);
            CenterM[2].y += 0.05f * (offset.y * stickPos);
            CenterM[2].z += 0.05f * (offset.z * stickPos);
        }
    }
}
