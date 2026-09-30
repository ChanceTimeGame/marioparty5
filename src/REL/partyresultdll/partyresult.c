/*
 * partyresultdll partyresult.c -- end-of-board results: bonus stars, final standings and
 * tie-break, winner, per-turn stat graphs, then the end-of-board save. Decompiled from
 * retail; functions are in reference order. See games/mp5/src/REL/partyresultdll/NOTES.md.
 *
 * Reached by omOvlGoto from the board (board/main.c DestroyMBObject), so the history index
 * still points at the board's entry; PResMain's omOvlReturnEx(1, 1) lands on mdpartydll.
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
#include "game/hsfex.h"
#include "math.h"


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
static const float lbl_1_rodata_30 = 30.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 1000.0f; /* 0x34 */
static const float lbl_1_rodata_38 = -1.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 0.1f; /* 0x3C */
static const float lbl_1_rodata_40 = 100.0f; /* 0x40 */
static const double lbl_1_rodata_48 = 3.141592653589793; /* 0x48 */
static const double lbl_1_rodata_50 = 180.0; /* 0x50 */
static const double lbl_1_rodata_58 = 1.0; /* 0x58 */
static const float lbl_1_rodata_60 = 0.05f; /* 0x60 */
/* 0x68 lbl_1_rodata_68 = 4503601774854144: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x494 */ static OMOBJ *outview;
/* 0x490 */ OMOBJMAN *objman;
/* 0x48D gap_05_0000048D_bss (0x3): alignment gap */
/* 0x48C */ u8 PResLanguageNo;
/* 0x45C */ u8 lbl_1_bss_45C[0x30]; /* unreferenced (alignment 4) */
/* 0x44C */ HU3DMODELID PResPlayerModelId[8];
/* 0x3FC */ HU3DMOTID PResPlayerMotion[4][10];
/* 0x24 */ PRES_PLAYER PResPlayer[PRES_PLAYER_MAX];
/* 0x1C */ s16 PResPlayerOrder[4];
/* 0x14 */ s16 PResCharNo[4];
/* 0x10 */ BOOL PResTeamF;
/* 0xC */ s32 PResLightId;
/* 0x8 */ u8 lbl_1_bss_8[0x4]; /* unreferenced (alignment 4) */
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x0 */ static u8 lbl_1_bss_0[0x4]; /* dtk pad_05_00000000_bss: unmapped local static, unreferenced */

static void PResPlayerCreate(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ GXColor lbl_1_data_0 = { 0x14, 0x00, 0x00, 0x00 };
/* 0x4 */ static OMCAMERAVIEW StageCameraView = { { 0.0f, 250.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 7000.0f };
/* 0x20 */ static OMCAMERAVIEW MainCameraView = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1600.0f };
/* 0x3C */ static OMCAMERAVIEW GuideCameraView = { { 0.0f, 150.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 140.0f };
/* 0x58 */ static u32 BoardDataDir[6] = { DATA_w01, DATA_w02, DATA_w03, DATA_w04, DATA_w07, 0x00000000 };

/* 204 insns */
void ObjectSetup(void)
{
    s16 i;

    OSReport("******* PRES ObjectSetup *********\n");
    objman = omInitObjMan(50, 8192);
    for(i = 0; BoardDataDir[i] != 0; i++) {
        HuDataDirClose(BoardDataDir[i]);
    }
    omSysPauseEnable(FALSE);
    PResLanguageNo = GWLanguageGet();
    Hu3DCameraCreate(HU3D_CAM0|HU3D_CAM1|HU3D_CAM2);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 5, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0, 0, 640, 480, 0, 1);
    Hu3DCameraPerspectiveSet(HU3D_CAM1|HU3D_CAM2, 30, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1|HU3D_CAM2, 0, 0, 640, 480, 0, 1);
    omCameraViewSetMulti(HU3D_CAM0, &StageCameraView);
    omCameraViewSetMulti(HU3D_CAM1, &MainCameraView);
    omCameraViewSetMulti(HU3D_CAM2, &MainCameraView);
    PResLightId = Hu3DGLightCreate(0, 1000, 1000, 0, -1, -1, 255, 255, 255);
    Hu3DGLightInfinitytSet(PResLightId);
    outview = omAddObjEx(objman, 32730, 0, 0, -1, omOutViewMulti);
    outview->work[0] = 3;
    omAddObjEx(objman, 0, 32, 32, -1, CameraMove);
    Hu3DBGColorSet(0, 0, 0);
    HuWinInit(1);
    HuPrcChildCreate(PResMain, 1000, 12288, 0, objman);
}

/* 16 insns */
void PResMain(void)
{
    PResPlayerCreate();
    PResResultCreate();
    PResResultMain();
    PResStatCreate();
    PResStatMain();
    _ClearFlag(FLAG_BOARD_SAVEINIT);
    SLSaveBoardEndExec();
    omOvlReturnEx(1, 1);
    while(1) {
        HuPrcVSleep();
    }
}

/* 27 insns */
void PResExit(void)
{
    while(omSysExitReq == FALSE) {
        HuPrcVSleep();
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    HuAudSStreamAllFadeOut(1000);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    omOvlReturnEx(1, 1);
    while(1) {
        HuPrcVSleep();
    }
}

#define PRES_GWPLAYER_BYTE3(gw) (((s8 *)(gw))[3])

/* 325 insns */
static void PResPlayerCreate(void)
{
    s16 i;
    s16 j;
    GWPLAYER *gwPlayer;
    PRES_PLAYER *player;
    s16 charNo;
    HU3DMODELID modelId;

    PResTeamF = GwSystem.teamF;
    if(PResTeamF) {
        for(i = j = 0; i < 4; i++) {
            if(GwPlayerConf[i].grp == 0) {
                PResPlayerOrder[j++] = i;
            }
        }
        for(i = 0; i < 4; i++) {
            if(GwPlayerConf[i].grp != 0) {
                PResPlayerOrder[j++] = i;
            }
        }
    } else {
        for(i = 0; i < 4; i++) {
            PResPlayerOrder[i] = i;
        }
    }
    for(i = 0; i < 4; i++) {
        gwPlayer = &GwPlayer[PResPlayerOrder[i]];
        player = &PResPlayer[i];
        player->unk000 = gwPlayer->charNo;
        player->unk002 = PResPlayerOrder[i];
        player->unk004 = gwPlayer->star;
        player->unk006 = gwPlayer->coin;
        player->unk024 = GwSystem.turnMax;
        player->unk00A[0] = gwPlayer->coinTotalMg;
        player->unk00A[1] = gwPlayer->coinMax;
        player->unk00A[2] = gwPlayer->hatenaMasuNum;
        player->unk026[0][0] = PRES_GWPLAYER_BYTE3(gwPlayer);
        player->unk026[1][0] = 10;
        for(j = 1; j < player->unk024; j++) {
            player->unk026[0][j] = *(u16 *)&gwPlayer->starStat[j];
            player->unk026[1][j] = *(u16 *)&gwPlayer->coinStat[j];
        }
        player->unk026[0][j] = gwPlayer->star;
        player->unk026[1][j] = gwPlayer->coin;
        player->unk010[0] = gwPlayer->star;
        player->unk010[1] = gwPlayer->coin;
        player->unk010[2] = gwPlayer->coinTotalMg;
        player->unk010[3] = gwPlayer->coinMax;
        player->unk010[4] = gwPlayer->blueMasuNum;
        player->unk010[5] = gwPlayer->redMasuNum;
        player->unk010[6] = gwPlayer->capsuleMasuNum;
        player->unk010[7] = gwPlayer->hatenaMasuNum;
        player->unk010[8] = gwPlayer->kupaMasuNum;
        player->unk010[9] = gwPlayer->donkeyMasuNum;
    }
    for(i = 0; i < 4; i++) {
        PResPlayer[i].unk008 = 0;
    }
    for(i = 0; i < 4; i++) {
        charNo = PResPlayer[i].unk000;
        PResCharNo[i] = charNo;
        modelId = CharModelCreate(charNo, 2);
        PResPlayerModelId[i] = modelId;
        PResPlayerMotion[i][0] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_480);
        PResPlayerMotion[i][1] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_303);
        PResPlayerMotion[i][2] = CharMotionCreate(charNo, CHAR_HSF_c000m1_526);
        PResPlayerMotion[i][3] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_487);
        PResPlayerMotion[i][4] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_306);
        PResPlayerMotion[i][5] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_483);
        PResPlayerMotion[i][6] = CharMotionCreate(charNo, CHARMOT_HSF_c000m1_354);
        Hu3DMotionAttrSet(PResPlayerMotion[i][2], 1);
        CharMotionSet(charNo, PResPlayerMotion[i][0]);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    }
}

/* 728 insns */
void CameraMove(OMOBJ *obj)
{
    HuVecF pos;
    HuVecF offset;
    HuVecF dir;
    HuVecF yOfs;
    float rotZ;
    s8 stickPos;

    if(lbl_1_bss_4) {
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
