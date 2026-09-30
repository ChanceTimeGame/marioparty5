/*
 * resultDll team.c -- PORTED (fork D, 2026-09-27): the team-mode results screen.
 * Reference: build/mp5-asm/resultDll/asm/REL/resultDll/team.s (compiled -O0).
 * Display only: the coins are credited by Result_AddBonusCoin (result.c), which
 * Result_TeamMain calls after Result_TeamUpdateRank.
 * Naming caveat kept from the symbol map: TeamCoinNum holds STARS, TeamCoinAddNum holds
 * the coins before the minigame and TeamStarNum the coins after it.
 */

/* retail calls Result_SetScoreSprNum / Result_SetBonusSprNum / Hu3D2Dto3D unprototyped: see resultDll.h */
#define RESULT_SPRNUM_NODECL
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

#ifndef __MWERKS__
#include "game/esprite.h"
#include "game/hsfex.h"
#endif

/* team-name messages: file 8 of the message archive; entry 0x2D is the "no name" fallback */
#define MESSNUM_TEAMNAME_BASE 0x80000
#define MESSNUM_TEAMNAME_NONE 0x8002D

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_278 = 1.0f; /* 0x278 */
static const float lbl_1_rodata_27C = -10000.0f; /* 0x27C */
static const float lbl_1_rodata_280 = 400.0f; /* 0x280 */
static const float lbl_1_rodata_284 = 0.0f; /* 0x284 */
static const float lbl_1_rodata_288 = 1.2f; /* 0x288 */
static const float lbl_1_rodata_28C = 360.0f; /* 0x28C */
static const float lbl_1_rodata_290 = 0.5f; /* 0x290 */
static const float lbl_1_rodata_294 = 36.0f; /* 0x294 */
static const float lbl_1_rodata_298 = -22.0f; /* 0x298 */
static const float lbl_1_rodata_29C = 0.37f; /* 0x29C */
static const float lbl_1_rodata_2A0 = 300.0f; /* 0x2A0 */
static const float lbl_1_rodata_2A4 = 255.0f; /* 0x2A4 */
/* 0x2A8 lbl_1_rodata_2A8 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x2B0 lbl_1_rodata_2B0 (0x4): 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_2B8 = 3.141592653589793; /* 0x2B8 */
static const double lbl_1_rodata_2C0 = 90.0; /* 0x2C0 */
static const double lbl_1_rodata_2C8 = 180.0; /* 0x2C8 */
static const double lbl_1_rodata_2D0 = 0.10000000149011612; /* 0x2D0 */
static const float lbl_1_rodata_2D8 = 8.571428f; /* 0x2D8 */
static const double lbl_1_rodata_2E0 = 0.8; /* 0x2E0 */
static const double lbl_1_rodata_2E8 = 1.0; /* 0x2E8 */
static const double lbl_1_rodata_2F0 = 2.0943951023931953; /* 0x2F0 */
static const float lbl_1_rodata_2F8 = 0.2f; /* 0x2F8 */
static const float lbl_1_rodata_2FC = 3.0f; /* 0x2FC */
/* 0x300 lbl_1_rodata_300 (0x10): 0x0000003C 0x0000001E 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x310 lbl_1_rodata_310 (0x8): 0x00000001 0x00000001 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_318 = 8.0f; /* 0x318 */
static const float lbl_1_rodata_31C = 0.0296f; /* 0x31C */
static const float lbl_1_rodata_320 = 0.0148f; /* 0x320 */
static const float lbl_1_rodata_324 = 4.0f; /* 0x324 */
static const float lbl_1_rodata_328 = 0.001f; /* 0x328 */
static const float lbl_1_rodata_32C = 118.0f; /* 0x32C */
static const float lbl_1_rodata_330 = 0.1f; /* 0x330 */
static const float lbl_1_rodata_334 = 2.0f; /* 0x334 */
static const double lbl_1_rodata_338 = 288.0; /* 0x338 */
static const double lbl_1_rodata_340 = 330.0; /* 0x340 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2090 */ static ANIMDATA *RankAnimP;
/* 0x208C */ static ANIMDATA *CrownAnimP;
/* 0x2084 */ static ANIMDATA *TeamBoxAnimP[2];
/* 0x2082 gap_05_00002082_bss (0x2): alignment gap */
/* 0x2080 */ static HUSPRGRPID RankSprGrpId;
/* 0x2078 */ static HUSPRGRPID ScoreSprGrpId[4];
/* 0x2058 */ static HUSPRID ScoreSprId[4][4];
/* 0x2054 */ static HUSPRGRPID BonusSprGrpId[2];
/* 0x2040 */ static HUSPRID BonusSprId[2][5];
/* 0x203E */ static HUSPRGRPID CrownSprGrpId;
/* 0x203C */ static HUSPRGRPID TeamBoxSprGrpId;
/* 0x202C */ u8 lbl_1_bss_202C[0x10]; /* unreferenced (alignment 4) */
/* 0x2024 */ static float CoinRotSpeed[2];
/* 0x201C */ static float StarRotSpeed[2];
/* 0x201A gap_05_0000201A_bss (0x2): alignment gap */
/* 0x2012 */ static s16 ToueiCharNo[4];
/* 0x200E */ static s16 TeamCoinAddNum[2];
/* 0x200A */ static s16 TeamStarNum[2];
/* 0x2006 */ static s16 TeamCoinNum[2];
/* 0x2002 */ static s16 TeamPlayerIdx[2];
/* 0x2000 */ static s16 TeamReqSort;
/* 0x1FFC */ static s16 TeamOrder[2];
/* 0x1FF4 */ static s16 TeamOrigCharNo[4];
/* 0x1FEC */ static s16 TeamPlayerNo[4];
/* 0x1FE4 */ static s16 TeamGrpNo[4];
/* 0x1FDC */ static s32 TeamNameWinId[2];
/* 0x1FD4 */ float lbl_1_bss_1FD4[2];
/* 0x1FBC */ static HuVecF TeamNamePos[2];
/* 0x1FA4 */ HuVecF lbl_1_bss_1FA4[2];
/* 0x1F9C */ static s16 TeamCharNo[2][2];
/* 0x1F98 */ static BOOL TeamFastF;

/* --- functions (reference order), .data placed before its first user --- */
/* 201 insns */
void Result_TeamMain(void)
{
    s16 i;
    s16 comNum;
    HUWINID winId;
    BOOL endF;
    HUPROCESS *proc;

    endF = FALSE;
    proc = HuPrcCurrentGet();
    Result_Debug();
    for(i = comNum = 0; i < 4; i++) {
        if(GwPlayerConf[i].type != 0) {
            comNum++;
        }
    }
    if(comNum == 4) {
        TeamFastF = TRUE;
    } else {
        TeamFastF = FALSE;
    }
    for(i = 0; i < 2; i++) {
        StarRotSpeed[i] = 1.0f;
        CoinRotSpeed[i] = 1.0f;
    }
    Result_TeamCreate();
    HuPrcChildCreate(Result_TeamCoinMdlMain, 100, 0x2000, 0, proc);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 20);
    HuAudSStreamPlay(49);
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
    Result_TeamCoinCount();
    Result_TeamUpdateRank();
    Result_AddBonusCoin();
    winId = HuWinCreate(-10000, 400, 320, 40, 0);
    HuWinMesSpeedSet(winId, 0);
    HuWinBGTPLvlSet(winId, 0);
    HuWinPriSet(winId, 5);
    HuWinAttrSet(winId, HUWIN_ATTR_ALIGN_CENTER);
    if(!TeamFastF) {
        HuWinMesSet(winId, 0x2000D);
    }
    HuPrcSleep(4);
    while(1) {
        if(TeamFastF) {
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

/* 193 insns */
void Result_TeamCoinMdlMain(void)
{
    float starRot[2];
    float coinRot[2];
    float unusedX;
    float unusedY;
    float unusedZ;
    s16 i;

    unusedX = 0.0f;
    unusedY = 0.0f;
    unusedZ = 0.0f;
    for(i = 0; i < 2; i++) {
        starRot[i] = 0.0f;
        coinRot[i] = 0.0f;
    }
    while(1) {
        if(TeamFastF) {
            Result_FastF = TRUE;
        } else {
            /* retail: no break, the last connected pad decides */
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
        for(i = 0; i < 2; i++) {
            starRot[i] += 1.2f * StarRotSpeed[i];
            if(starRot[i] >= 360.0f) {
                starRot[i] -= 360.0f;
            }
            coinRot[i] += CoinRotSpeed[i];
            if(coinRot[i] >= 360.0f) {
                coinRot[i] -= 360.0f;
            }
        }
        Hu3DModelRotSet(StageMdlId[0], 0.0f, starRot[0], 0.0f);
        Hu3DModelRotSet(StageMdlId[1], 0.0f, starRot[1], 0.0f);
        Hu3DModelRotSet(StageMdlId[2], 0.0f, coinRot[0], 0.0f);
        Hu3DModelRotSet(StageMdlId[3], 0.0f, coinRot[1], 0.0f);
        HuPrcVSleep();
    }
}

/* 0xB58 */ STAGE_MODEL Result_TeamModel[7] = {
    { DATANUM(DATA_result, 22), 0x40000001, 0, -1, -1, 1, 2, { 240.0f, 210.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 22), 0x40000001, 2, 0, -1, 1, 2, { 240.0f, 360.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.6f, 0.6f, 0.6f } },
    { DATANUM(DATA_result, 23), 0x40000001, 0, -1, -1, 1, 2, { 410.0f, 210.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 23), 0x40000001, 2, 2, -1, 1, 2, { 410.0f, 360.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 0.53f, 0.53f, 0.53f } },
    { DATANUM(DATA_result, 24), 0x40000001, 0, -1, -1, 0, 2, { 288.0f, 240.0f, 2500.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
    { DATANUM(DATA_result, 31), 0x40000001, 0, -1, -1, 0, 1, { 300.0f, 800.0f, 1600.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 2.0f, 2.0f } },
    { HU_DATANUM_NONE, 0x00000000, 0, -1, -1, -1, 0, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f } },
};
/* 0xCE0 */ STAGE_SPRITE Result_TeamSprite[4] = {
    { DATANUM(DATA_result, 6), 0, 10, 288.0f, 70.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 10), 0, 20, 288.0f, 180.0f, { 255, 255, 255, 255 } },
    { DATANUM(DATA_result, 11), 0, 20, 288.0f, 330.0f, { 255, 255, 255, 255 } },
    { 0, 0, 0, 0.0f, 0.0f, { 0, 0, 0, 0 } },
};
/* 0xD30 */ static u32 MgTypeBackFileTbl[9] = { DATANUM(DATA_result, 24), DATANUM(DATA_result, 27), DATANUM(DATA_result, 25), DATANUM(DATA_result, 24), DATANUM(DATA_result, 28), DATANUM(DATA_result, 28), DATANUM(DATA_result, 26), DATANUM(DATA_result, 24), DATANUM(DATA_result, 24) };
/* 0xD54 */ static s16 RankPosTbl[2*2] = { 60, 180, 60, 330 }; /* flat: retail indexes [i*2], [i*2+1] */
/* 0xD5C */ static s16 BonusPosTbl[2*2] = { 160, 180, 160, 330 };
/* 0xD64 */ static s16 ScorePosTbl[4*2] = { 330, 210, 330, 360, 500, 210, 500, 360 };
/* 0xD74 */ static s16 CrownPosTbl[2*2] = { 268, 160, 268, 310 };
/* 0xD7C */ static HuVecF ToueiPosTbl[4] = { { 120.0f, 145.0f, 1600.0f }, { 120.0f, 215.0f, 1600.0f }, { 120.0f, 295.0f, 1600.0f }, { 120.0f, 365.0f, 1600.0f } };
/* 0xDAC */ static HuVecF ToueiCharPosTbl[4] = { { 240.0f, 250.0f, 1700.0f }, { 240.0f, 400.0f, 1700.0f }, { 320.0f, 250.0f, 1700.0f }, { 320.0f, 400.0f, 1700.0f } };
/* 0xDDC */ static s16 TeamBoxPosTbl[2*2] = { 420, 150, 420, 300 };
/* 0xDE4 */ static HuVecF ToueiCharScaleTbl[13] = { { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.6f, 0.6f, 0.6f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.7f, 0.7f, 0.7f }, { 0.5f, 0.5f, 0.5f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f }, { 0.6f, 0.6f, 0.6f } };
/* 0xE80 */ static HuVecF ScoreSprPosTbl[4] = { { -52.0f, 0.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 26.0f, 0.0f, 0.0f } };
/* 0xEB0 */ static HuVecF BonusSprPosTbl[4] = { { 12.0f, -25.0f, 0.0f }, { 28.0f, -25.0f, 0.0f }, { 44.0f, -25.0f, 0.0f }, { 60.0f, -25.0f, 0.0f } };
/* 0xEE0 */ static u32 TeamFrameFileTbl[2] = { DATANUM(DATA_result, 10), DATANUM(DATA_result, 11) };

/* 1561 insns */
void Result_TeamCreate(void)
{
    HuVecF pos;
    s16 rank[2];
    s16 memberNum[2];
    s16 i;
    s16 j;
    s16 num0;
    s16 num1;
    s16 dataOfs;
    ANIMDATA *anim;
    ANIMDATA *anim2;
    HUSPRID sprId;
    s32 coin;

    TeamCoinAddNum[0] = TeamCoinAddNum[1] = 0;
    TeamCoinNum[0] = TeamCoinNum[1] = 0;
    TeamPlayerIdx[0] = 0;
    TeamPlayerIdx[1] = 2;
    for(i = memberNum[0] = memberNum[1] = 0; i < 4; i++) {
        TeamGrpNo[i] = GwPlayer[i].grp;
        if(memberNum[TeamGrpNo[i]] == 0) {
            TeamCoinAddNum[TeamGrpNo[i]] += MBPlayerCoinGet(i);
            j = MBPlayerCoinGet(i); /* dead in retail */
            TeamCoinNum[TeamGrpNo[i]] += MBPlayerStarGet(i);
            memberNum[TeamGrpNo[i]]++;
        }
        TeamPlayerNo[TeamPlayerIdx[TeamGrpNo[i]]] = i;
        TeamOrigCharNo[TeamPlayerIdx[TeamGrpNo[i]]++] = GwPlayerConf[i].charNo;
    }
    for(i = 0; i < 4; i++) {
        coin = MBPlayerCoinGet(i);
        OSReport("PlayerNo=%d  CharNo=%d  teamNo=%d  Star=%d  Coin=%d \n", i, GwPlayerConf[i].charNo, GwPlayer[i].grp, MBPlayerStarGet(i), coin);
    }
    TeamOrder[0] = 0;
    TeamOrder[1] = 1;
    rank[0] = 0;
    rank[1] = 1;
    if(TeamCoinNum[0] > TeamCoinNum[1]) {
        TeamReqSort = 0;
    } else if(TeamCoinNum[0] == TeamCoinNum[1]) {
        if(TeamCoinAddNum[0] > TeamCoinAddNum[1]) {
            TeamReqSort = 0;
        } else if(TeamCoinAddNum[0] == TeamCoinAddNum[1]) {
            rank[0] = rank[1] = 0;
            TeamReqSort = 0;
        } else {
            TeamOrder[0] = 1;
            TeamOrder[1] = 0;
            TeamReqSort = 1;
        }
    } else {
        TeamOrder[0] = 1;
        TeamOrder[1] = 0;
        TeamReqSort = 1;
    }
    if(TeamReqSort == 1) {
        Result_TeamSprite[1].dataNum = TeamFrameFileTbl[1];
        Result_TeamSprite[2].dataNum = TeamFrameFileTbl[0];
    }
    Result_TeamModel[4].dataNum = MgTypeBackFileTbl[mgDataTbl[GwSystem.mgNo].type];
    StageSpriteCreate(Result_TeamSprite);
    StageModelCreate(Result_TeamModel);
    Hu3DMotionSpeedSet(StageMdlId[4], 0.5f);
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i = 0; i < 4; i++) {
        ScoreSprGrpId[i] = HuSprGrpCreate(4);
        for(j = 0; j < 4; j++) {
            ScoreSprId[i][j] = HuSprCreate(anim, 0, 0);
            HuSprGrpMemberSet(ScoreSprGrpId[i], j, ScoreSprId[i][j]);
            HuSprPosSet(ScoreSprGrpId[i], j, ScoreSprPosTbl[j].x, ScoreSprPosTbl[j].y);
        }
        HuSprGrpPosSet(ScoreSprGrpId[i], ScorePosTbl[i*2], ScorePosTbl[(i*2)+1]);
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    anim2 = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 8), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i = 0; i < 2; i++) {
        BonusSprGrpId[i] = HuSprGrpCreate(5);
        BonusSprId[i][0] = HuSprCreate(anim2, 10, 0);
        HuSprGrpMemberSet(BonusSprGrpId[i], 0, BonusSprId[i][0]);
        HuSprPosSet(BonusSprGrpId[i], 0, 36.0f, -22.0f);
        for(j = 1; j < 5; j++) {
            BonusSprId[i][j] = HuSprCreate(anim, 0, 0);
            HuSprGrpMemberSet(BonusSprGrpId[i], j, BonusSprId[i][j]);
            HuSprPosSet(BonusSprGrpId[i], j, BonusSprPosTbl[j - 1].x, BonusSprPosTbl[j - 1].y);
        }
        HuSprBankSet(BonusSprGrpId[i], 1, 10);
        HuSprGrpPosSet(BonusSprGrpId[i], BonusPosTbl[i*2], BonusPosTbl[(i*2)+1]);
        HuSprGrpScaleSet(BonusSprGrpId[i], 0.0f, 0.0f);
    }
    CrownAnimP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 9), HU_MEMNUM_OVL, HEAP_MODEL));
    CrownSprGrpId = HuSprGrpCreate(2);
    for(i = 0; i < 2; i++) {
        sprId = HuSprCreate(CrownAnimP, i, 0);
        HuSprGrpMemberSet(CrownSprGrpId, i, sprId);
        HuSprScaleSet(CrownSprGrpId, i, 0.0f, 0.0f);
        HuSprPosSet(CrownSprGrpId, i, CrownPosTbl[i*2], CrownPosTbl[(i*2)+1]);
        HuSprAttrSet(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
    }
    if(TeamReqSort == 1) {
        ToueiCharNo[0] = TeamOrigCharNo[2];
        ToueiCharNo[1] = TeamOrigCharNo[3];
        ToueiCharNo[2] = TeamOrigCharNo[0];
        ToueiCharNo[3] = TeamOrigCharNo[1];
    } else {
        ToueiCharNo[0] = TeamOrigCharNo[0];
        ToueiCharNo[1] = TeamOrigCharNo[1];
        ToueiCharNo[2] = TeamOrigCharNo[2];
        ToueiCharNo[3] = TeamOrigCharNo[3];
    }
    for(i = 0; i < 4; i++) {
        if(i == 0) {
            StageToueiMdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_result, 30), HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            StageToueiMdlId[i] = Hu3DModelLink(StageToueiMdlId[0]);
        }
        Hu3D2Dto3D(&ToueiPosTbl[i], HU3D_CAM1, &pos);
        Hu3DModelScaleSet(StageToueiMdlId[i], 0.37f, 0.37f, 0.37f);
        Hu3DModelLayerSet(StageToueiMdlId[i], 1);
        Hu3DModelPosSetV(StageToueiMdlId[i], &pos);
        Hu3DModelCameraSet(StageToueiMdlId[i], 2);
        dataOfs = ToueiCharNo[i] * 4;
        StageCharMdlId[i] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_result, 32) + dataOfs, HU_MEMNUM_OVL, HEAP_MODEL));
        StageCharMotId[i][0] = Hu3DJointMotion(StageCharMdlId[i], HuDataSelHeapReadNum(DATANUM(DATA_result, 33) + dataOfs, HU_MEMNUM_OVL, HEAP_MODEL));
        StageCharMotId[i][1] = Hu3DJointMotion(StageCharMdlId[i], HuDataSelHeapReadNum(DATANUM(DATA_result, 34) + dataOfs, HU_MEMNUM_OVL, HEAP_MODEL));
        StageCharMotId[i][2] = Hu3DJointMotion(StageCharMdlId[i], HuDataSelHeapReadNum(DATANUM(DATA_result, 35) + dataOfs, HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3D2Dto3D(&ToueiCharPosTbl[i], HU3D_CAM0, &pos);
        Hu3DMotionSet(StageCharMdlId[i], StageCharMotId[i][0]);
        Hu3DModelScaleSet(StageCharMdlId[i], ToueiCharScaleTbl[ToueiCharNo[i]].x, ToueiCharScaleTbl[ToueiCharNo[i]].y, ToueiCharScaleTbl[ToueiCharNo[i]].z);
        Hu3DModelLayerSet(StageCharMdlId[i], 0);
        Hu3DModelPosSetV(StageCharMdlId[i], &pos);
        Hu3DModelAttrSet(StageCharMdlId[i], 0x40000001);
        Hu3DModelCameraSet(StageCharMdlId[i], 1);
    }
    ToueiDispInit(ToueiCharNo);
    RankAnimP = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 5), HU_MEMNUM_OVL, HEAP_MODEL));
    RankSprGrpId = HuSprGrpCreate(2);
    for(i = 0; i < 2; i++) {
        sprId = HuSprCreate(RankAnimP, i, 0);
        HuSprGrpMemberSet(RankSprGrpId, i, sprId);
        HuSprPosSet(RankSprGrpId, i, RankPosTbl[i*2], RankPosTbl[(i*2)+1]);
        HuSprBankSet(RankSprGrpId, i, rank[i]);
    }
    if(TeamReqSort == 0) {
        for(i = num0 = num1 = 0; i < 4; i++) {
            if(TeamGrpNo[i] == 0) {
                TeamCharNo[0][num0] = GwPlayerConf[i].charNo;
                num0++;
            } else if(TeamGrpNo[i] == 1) {
                TeamCharNo[1][num1] = GwPlayerConf[i].charNo;
                num1++;
            }
        }
    } else if(TeamReqSort == 1) {
        for(i = num0 = num1 = 0; i < 4; i++) {
            if(TeamGrpNo[i] == 0) {
                TeamCharNo[1][num0] = GwPlayerConf[i].charNo;
                num0++;
            } else if(TeamGrpNo[i] == 1) {
                TeamCharNo[0][num1] = GwPlayerConf[i].charNo;
                num1++;
            }
        }
    }
    if(TeamReqSort == 1) {
        TeamBoxAnimP[0] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 16), HU_MEMNUM_OVL, HEAP_MODEL));
        TeamBoxAnimP[1] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 15), HU_MEMNUM_OVL, HEAP_MODEL));
    } else {
        TeamBoxAnimP[0] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 15), HU_MEMNUM_OVL, HEAP_MODEL));
        TeamBoxAnimP[1] = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_result, 16), HU_MEMNUM_OVL, HEAP_MODEL));
    }
    TeamBoxSprGrpId = HuSprGrpCreate(2);
    for(i = 0; i < 2; i++) {
        sprId = HuSprCreate(TeamBoxAnimP[i], i, 0);
        HuSprGrpMemberSet(TeamBoxSprGrpId, i, sprId);
        HuSprPosSet(TeamBoxSprGrpId, i, TeamBoxPosTbl[i*2], TeamBoxPosTbl[(i*2)+1]);
        TeamNamePos[i].x = 300.0f;
        TeamNamePos[i].y = TeamBoxPosTbl[(i*2)+1] - 5;
        TeamNameWinId[i] = HuWinCreate(TeamNamePos[i].x, TeamNamePos[i].y, 236, 35, 0);
        HuWinBGTPLvlSet(TeamNameWinId[i], 255.0f);
        HuWinPriSet(TeamNameWinId[i], 0);
        HuWinAttrSet(TeamNameWinId[i], HUWIN_ATTR_ALIGN_CENTER);
        HuWinMesSpeedSet(TeamNameWinId[i], 0);
        HuWinMesSet(TeamNameWinId[i], Result_TeamNameMessGet(TeamCharNo[i][0], TeamCharNo[i][1]));
        lbl_1_bss_1FD4[i] = 0.0f;
        lbl_1_bss_1FA4[i].x = lbl_1_bss_1FA4[i].y = lbl_1_bss_1FA4[i].z = 1.0f;
    }
    Result_SetScoreSprNum(ScoreSprGrpId[0], TeamCoinNum[TeamOrder[0]]);
    Result_SetScoreSprNum(ScoreSprGrpId[1], TeamCoinNum[TeamOrder[1]]);
    Result_SetScoreSprNum(ScoreSprGrpId[2], TeamCoinAddNum[TeamOrder[0]]);
    Result_SetScoreSprNum(ScoreSprGrpId[3], TeamCoinAddNum[TeamOrder[1]]);
}

/* 697 insns */
void Result_TeamCoinCount(void)
{
    s16 coinNum[5]; /* Result_GetCoin writes [4] (the Battle remainder) only in Battle mode */
    s32 seF[2] = { 0, 0 };
    float seRot[2];
    s16 addNum[2];
    s16 countNum[2];
    float scale;
    float addTime;
    float addSpeed;
    s16 i;
    s16 time;
    s16 maxTime;
    s16 crownTime;
    s16 j;

    addNum[0] = addNum[1] = 0;
    for(i = 0; i < 4; i++) {
        coinNum[i] = 0;
    }
    Result_GetCoin(coinNum);
    for(i = 0; i < 4; i++) {
        addNum[TeamGrpNo[i]] += coinNum[i];
    }
    for(i = 0; i < 2; i++) {
        Result_SetBonusSprNum(BonusSprGrpId[i], addNum[TeamOrder[i]]);
        if(addNum[TeamOrder[i]] > 0) {
            seF[i] = 1;
        }
        seRot[i] = 0.0f;
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for(time = 0; time <= maxTime; time++) {
        scale = HuSin((90.0 / maxTime) * time);
        for(i = 0; i < 2; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
        }
        HuPrcVSleep();
    }
    for(i = 0; i < 2; i++) {
        HuSprGrpScaleSet(BonusSprGrpId[i], 1.0f, 1.0f);
    }
    for(crownTime = 0; crownTime <= 14;) {
        for(i = 0; i < 2; i++) {
            if(addNum[TeamOrder[i]] >= 10) {
                HuSprAttrReset(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
            }
            HuSprScaleSet(CrownSprGrpId, i, 0.1f + HuSin((120.0f / 14.0f) * crownTime) * (0.8 * (1.0 / sin((M_PI * 2) / 3))),
                0.1f + 0.8 * (HuSin((120.0f / 14.0f) * crownTime) * (1.0 / sin((M_PI * 2) / 3))));
        }
        crownTime += (Result_FastF) ? 2 : 1;
        HuPrcVSleep();
    }
    if(!Result_FastF) {
        HuPrcSleep(15);
    }
    for(i = time = 0; i < 2; i++) {
        countNum[i] = addNum[i];
        time += addNum[i];
    }
    time = 0;
    addTime = addSpeed = time;
    time = 0;
    while(1) {
        addTime += (Result_FastF) ? 1.0f : 0.2f;
        addSpeed = (Result_FastF) ? 1.0f : 0.2f;
        time = addTime;
        for(i = maxTime = 0; i < 2; i++) {
            seRot[i] += addSpeed;
            if(countNum[TeamOrder[i]] - time <= 0) {
                CoinRotSpeed[i] = 1.0f;
                seF[i] = 0;
                maxTime++;
                Result_SetBonusSprNum(BonusSprGrpId[i], 0);
                TeamStarNum[TeamOrder[i]] = addNum[TeamOrder[i]] + TeamCoinAddNum[TeamOrder[i]];
                Result_SetScoreSprNum(ScoreSprGrpId[i + 2], TeamStarNum[TeamOrder[i]]);
            } else {
                if(seF[i] && seRot[i] >= 1.0f) {
                    HuAudFXPlay(7);
                    seRot[i] = 0.0f;
                }
                Result_SetBonusSprNum(BonusSprGrpId[i], countNum[TeamOrder[i]] - time);
                Result_SetScoreSprNum(ScoreSprGrpId[i + 2], time + TeamCoinAddNum[TeamOrder[i]]);
                CoinRotSpeed[i] = 3.0f;
            }
        }
        if(maxTime == 2) {
            break;
        }
        HuPrcVSleep();
    }
    if(maxTime < 30) {
        HuPrcSleep(30 - maxTime);
    }
    maxTime = (Result_FastF) ? 3 : 10;
    for(time = 0; time <= maxTime; time++) {
        scale = HuCos((90.0 / maxTime) * time);
        for(i = 0; i < 2; i++) {
            HuSprGrpScaleSet(BonusSprGrpId[i], scale, scale);
            HuSprScaleSet(CrownSprGrpId, i, scale, scale);
        }
        HuPrcVSleep();
    }
    for(i = 0; i < 2; i++) {
        for(j = 0; j < 5; j++) {
            HuSprAttrSet(BonusSprGrpId[i], j, HUSPR_ATTR_DISPOFF);
        }
        HuSprAttrSet(CrownSprGrpId, i, HUSPR_ATTR_DISPOFF);
    }
}

/* 0xF1E */ static s16 TopWinMotTbl[4] = { 2, 2, 1, 1 };
/* 0xF26 */ static s16 BottomWinMotTbl[4] = { 1, 1, 2, 2 };

/* 1155 insns */
void Result_TeamUpdateRank(void)
{
    s32 digit[3];
    s32 waitTime[4] = { 60, 30, 0, 0 };
    s32 motF[4];
    float tpLvl[2];
    float boxScale[2];
    float frameTPLvl[2];
    s32 fadeF[2] = { 1, 1 };
    HUSPRITE *frameSprP;
    s16 unused;
    s16 i;
    s16 sum;
    s16 other;
    BOOL motStartF;
    HUSPRITE *sprP;
    s16 j;
    s16 time;
    HUSPRGRP *grpP;
    s32 winGrp;
    s32 num;
    BOOL doneF;
    s16 speed;
    s16 espGrpId;
    float step;

    motStartF = FALSE;
    doneF = FALSE;
    espGrpId = espGrpIDGet();
    if(TeamReqSort == 0) {
        winGrp = 1;
    } else if(TeamReqSort == 1) {
        winGrp = 0;
    }
    for(i = 0; i < 2; i++) {
        tpLvl[i] = 0.37f;
        boxScale[i] = 1.0f;
        frameTPLvl[i] = 1.0f;
        frameSprP = &HuSprData[HuSprGrpData[espGrpId].sprId[StageSprId[i]]];
    }
    for(i = 0; i < 4; i++) {
        motF[i] = 0;
    }
    if(TeamStarNum[TeamOrder[1]] == TeamStarNum[TeamOrder[0]] && TeamCoinNum[1] == TeamCoinNum[0]) {
        HuSprBankSet(RankSprGrpId, 0, 0);
        HuSprBankSet(RankSprGrpId, 1, 0);
        if(TeamCoinAddNum[0] != TeamCoinAddNum[1]) {
            for(i = 2; i < 4; i++) {
                Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][TopWinMotTbl[i]], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                motF[i] = 1;
            }
            for(i = 0; i < 4; i++) {
                if(winGrp == GwPlayer[i].grp) {
                    PlayerFXPlay(i, 504);
                }
            }
            motStartF = TRUE;
            while(1) {
                sum = 0;
                for(i = 2; i < 4; i++) {
                    if(motStartF && motF[i] && Result_CharMotEnd(i)) {
                        motF[i] = 0;
                    }
                    sum += motF[i];
                }
                if(motStartF && sum <= 0) {
                    for(i = 0; i < 4; i++) {
                        Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                    break;
                }
                HuPrcVSleep();
            }
        }
        (void)0; /* a no-code statement: retail keeps the jump after the loop unthreaded */
    } else if(TeamCoinNum[TeamOrder[0]] > TeamCoinNum[TeamOrder[1]] || (TeamCoinNum[TeamOrder[0]] == TeamCoinNum[TeamOrder[1]] && TeamStarNum[TeamOrder[0]] > TeamStarNum[TeamOrder[1]])) {
        HuSprBankSet(RankSprGrpId, 0, 0);
        HuSprBankSet(RankSprGrpId, 1, 1);
        if(TeamOrder[0] == 0 && TeamOrder[1] == 1 && TeamCoinAddNum[0] == TeamCoinAddNum[1] && TeamCoinNum[TeamOrder[0]] == TeamCoinNum[TeamOrder[1]]) {
            for(i = 2; i < 4; i++) {
                Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][BottomWinMotTbl[i]], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                motF[i] = 1;
            }
            motStartF = TRUE;
            while(1) {
                for(i = sum = 0; i < 4; i++) {
                    if(motStartF && motF[i] && Result_CharMotEnd(i)) {
                        motF[i] = 0;
                    }
                    sum += motF[i];
                }
                if(motStartF && sum <= 0) {
                    for(i = 0; i < 4; i++) {
                        Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                    }
                    break;
                }
                HuPrcVSleep();
            }
        }
        (void)0; /* a no-code statement: retail keeps the jump after the loop unthreaded */
    } else {
        sum = TeamOrder[0];
        TeamOrder[0] = TeamOrder[1];
        TeamOrder[1] = sum;
        sum = 0;
        unused = 0;
        time = 0;
        while(1) {
            step = (Result_FastF) ? 0.0296f : 0.0148f;
            speed = (Result_FastF) ? 2 : 1;
            if(Result_FastF) {
                time += 3;
            } else {
                time += 1;
            }
            if(!doneF) {
                for(i = 1; i > -1; i--) {
                    if(time % 2) {
                        for(j = 0; j < 3; j++) {
                            digit[j] = frandmod(10);
                            if(digit[j] == 0) {
                                digit[j] = frandmod(9) + 1;
                            }
                        }
                        num = digit[0] * 100 + digit[1] * 10 + digit[2];
                        Result_SetScoreSprNum(ScoreSprGrpId[i], num);
                        Result_SetScoreSprNum(ScoreSprGrpId[i + 2], num);
                        CoinRotSpeed[i] = 4.0f;
                        StarRotSpeed[i] = 4.0f;
                    }
                    if(fadeF[i]) {
                        if((tpLvl[i] -= step) <= 0.0f) {
                            tpLvl[i] = 0.001f;
                            fadeF[i] = 0;
                            if(i != 0) {
                                Result_TeamUpdateOrder();
                            }
                            Result_TeamSetTPLvl(i, tpLvl[i]);
                        }
                        if((boxScale[i] -= 3.0f * step) <= 0.0f) {
                            boxScale[i] = 0.0f;
                        }
                        HuSprScaleSet(TeamBoxSprGrpId, i, boxScale[i], 1.0f);
                        grpP = &HuSprGrpData[TeamBoxSprGrpId];
                        sprP = &HuSprData[grpP->sprId[i]];
                        HuWinPosSet(TeamNameWinId[i], sprP->pos.x - 118.0f * sprP->scale.x, TeamNamePos[i].y);
                        HuWinScaleSet(TeamNameWinId[i], boxScale[i], 1.0f);
                        if((frameTPLvl[i] -= 3.0f * step) <= 0.1f) {
                            frameTPLvl[i] = 0.1f;
                        }
                        espTPLvlSet(StageSprId[i + 1], frameTPLvl[i]);
                    } else {
                        if((waitTime[i] -= speed) <= 0) {
                            if((tpLvl[i] += step) >= 0.37f) {
                                tpLvl[i] = 0.37f;
                                Result_SetScoreSprNum(ScoreSprGrpId[i], TeamCoinNum[TeamOrder[i]]);
                                Result_SetScoreSprNum(ScoreSprGrpId[i + 2], TeamStarNum[TeamOrder[i]]);
                                CoinRotSpeed[i] = 1.0f;
                                StarRotSpeed[i] = 1.0f;
                                Result_TeamSetTPLvl(i, tpLvl[i]);
                                if(i == 0) {
                                    doneF = TRUE;
                                }
                            }
                            if(i == 0) {
                                other = 1;
                            } else if(i != 0) {
                                other = 0;
                            }
                            if((boxScale[other] += 3.0f * step) >= 1.0f) {
                                boxScale[other] = 1.0f;
                            }
                            HuSprScaleSet(TeamBoxSprGrpId, other, boxScale[other], 1.0f);
                            grpP = &HuSprGrpData[TeamBoxSprGrpId];
                            sprP = &HuSprData[grpP->sprId[other]];
                            HuWinPosSet(TeamNameWinId[other], sprP->pos.x - 118.0f * sprP->scale.x, TeamNamePos[other].y);
                            HuWinScaleSet(TeamNameWinId[other], boxScale[other], 1.0f);
                            if((frameTPLvl[other] += 2.0f * step) >= 1.0f) {
                                frameTPLvl[other] = 1.0f;
                            }
                            /* retail bug: the level is frameTPLvl[i], not [other] */
                            espTPLvlSet(StageSprId[other + 1], frameTPLvl[i]);
                        }
                    }
                    Result_TeamSetTPLvl(i, tpLvl[i]);
                }
            } else if(!motStartF) {
                HuSprBankSet(RankSprGrpId, 0, 0);
                HuSprBankSet(RankSprGrpId, 1, 1);
                for(i = 0; i < 4; i++) {
                    Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][TopWinMotTbl[i]], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
                    if(winGrp == GwPlayer[i].grp) {
                        PlayerFXPlay(i, 504);
                    }
                    motF[i] = 1;
                }
                motStartF = TRUE;
            }
            for(i = sum = 0; i < 4; i++) {
                if(motStartF && motF[i] && Result_CharMotEnd(i)) {
                    motF[i] = 0;
                }
                sum += motF[i];
            }
            if(motStartF && sum <= 0) {
                for(i = 0; i < 4; i++) {
                    Hu3DMotionShiftSet(StageCharMdlId[i], StageCharMotId[i][0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
                }
                break;
            }
            HuPrcVSleep();
        }
    }
}

/* 43 insns */
void Result_TeamSetTPLvl(s16 teamNo, float tpLvl)
{
    if(teamNo != 0) {
        Hu3DModelScaleSet(StageToueiMdlId[3], tpLvl, tpLvl, tpLvl);
        Hu3DModelScaleSet(StageToueiMdlId[2], tpLvl, tpLvl, tpLvl);
    } else {
        Hu3DModelScaleSet(StageToueiMdlId[1], tpLvl, tpLvl, tpLvl);
        Hu3DModelScaleSet(StageToueiMdlId[0], tpLvl, tpLvl, tpLvl);
    }
}

/* 207 insns */
void Result_TeamUpdateOrder(void)
{
    HuVecF pos2;
    HuVecF pos1;
    HuVecF namePos;
    HU3DMODELID mdlId[4];
    int i;

    for(i = 0; i < 4; i++) {
        mdlId[i] = StageToueiMdlId[i];
    }
    StageToueiMdlId[0] = mdlId[2];
    StageToueiMdlId[1] = mdlId[3];
    StageToueiMdlId[2] = mdlId[0];
    StageToueiMdlId[3] = mdlId[1];
    Hu3D2Dto3D(&ToueiPosTbl[0], HU3D_CAM1, &pos1);
    Hu3D2Dto3D(&ToueiPosTbl[1], HU3D_CAM1, &pos2);
    Hu3DModelPosSetV(StageToueiMdlId[0], &pos1);
    Hu3DModelPosSetV(StageToueiMdlId[1], &pos2);
    Hu3D2Dto3D(&ToueiPosTbl[2], HU3D_CAM1, &pos1);
    Hu3D2Dto3D(&ToueiPosTbl[3], HU3D_CAM1, &pos2);
    Hu3DModelPosSetV(StageToueiMdlId[2], &pos1);
    Hu3DModelPosSetV(StageToueiMdlId[3], &pos2);
    HuSprPosSet(TeamBoxSprGrpId, 0, TeamBoxPosTbl[2], TeamBoxPosTbl[3]);
    HuSprPosSet(TeamBoxSprGrpId, 1, TeamBoxPosTbl[0], TeamBoxPosTbl[1]);
    namePos = TeamNamePos[0];
    TeamNamePos[0] = TeamNamePos[1];
    TeamNamePos[1] = namePos;
    for(i = 0; i < 2; i++) {
        HuWinPosSet(TeamNameWinId[i], TeamNamePos[i].x, TeamNamePos[i].y);
    }
    espPosSet(StageSprId[2], 288.0, 180.0);
    espPosSet(StageSprId[1], 288.0, 330.0);
}

/* 0xF2E */ static s8 TeamNoTbl[9 * 10] = { /* flat: retail indexes [charNo1 * 10 + charNo2] */
    -1, 0, 1, 2, 3, 4, 5, 6, 7, 8,
    -1, -1, 9, 10, 11, 12, 13, 14, 15, 16,
    -1, -1, -1, 17, 18, 19, 20, 21, 22, 23,
    -1, -1, -1, -1, 24, 25, 26, 27, 28, 29,
    -1, -1, -1, -1, -1, 30, 31, 32, 33, 34,
    -1, -1, -1, -1, -1, -1, 35, 36, 37, 38,
    -1, -1, -1, -1, -1, -1, -1, 39, 40, 41,
    -1, -1, -1, -1, -1, -1, -1, -1, 42, 43,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 44
};

/* 60 insns */
u32 Result_TeamNameMessGet(s16 charNo1, s16 charNo2)
{
    s32 teamNo;

    if(charNo1 > 9 || charNo2 > 9) {
        return MESSNUM_TEAMNAME_NONE;
    }
    if(charNo1 < charNo2) {
        teamNo = TeamNoTbl[charNo1 * 10 + charNo2];
    } else {
        teamNo = TeamNoTbl[charNo2 * 10 + charNo1];
    }
    OSReport("%d:%d->%d\n", charNo1, charNo2, teamNo);
    if(teamNo == -1) {
        return MESSNUM_TEAMNAME_NONE;
    }
    return teamNo + MESSNUM_TEAMNAME_BASE;
}
