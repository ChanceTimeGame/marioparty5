#include "REL/m506Dll.h"

#include "game/charman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/process.h"
#include "game/sprite.h"
#include "game/mg/score.h"

#include "datanum/m506.h"
#include "datanum/mgconst.h"

/*
 * Written here from the reference assembly; upstream declares this unit
 * NonMatching and ships no source for it. Function names come from upstream's
 * symbols.txt. See NOTES.md for how it was checked.
 */

typedef struct M506Rocket_s {
    HuVecF pos; //0x00
    HuVecF rot; //0x0C
    float speed; //0x18
    int mode; //0x1C
    BOOL startF; //0x20
    BOOL waitF; //0x24
    s16 unk28; //0x28
} M506_ROCKET;

typedef struct M506Starfighter_s {
    HuVecF pos; //0x00
    HuVecF rot; //0x0C
    float speed; //0x18
    int mode; //0x1C
    BOOL startF; //0x20
} M506_STARFIGHTER;

typedef struct M506CamStop_s {
    int mode; //0x00
    float targetY; //0x04
    float speed; //0x08
    float accel; //0x0C
    float decay; //0x10
} M506_CAMSTOP;

typedef struct M506Flow_s {
    M506_WORK *m506Work; //0x00
    M506_WORK *work; //0x04, the same pointer; model ids are read through this one
    OMOBJ *playerObj[M506_PLAYER_MAX]; //0x08
    M506_PLAYER_WORK *player[M506_PLAYER_MAX]; //0x18
    int mode; //0x28
    int unk2C; //0x2C
    int unk30; //0x30
    float time; //0x34
    BOOL humanWinF; //0x38
    int winnerNum; //0x3C
    s32 recordHeight; //0x40
    int humanBest; //0x44
    s8 height[M506_PLAYER_MAX]; //0x48
    s8 maxHeight[M506_PLAYER_MAX]; //0x4C
    s8 winnerChar[M506_PLAYER_MAX]; //0x50
    s8 rank[M506_PLAYER_MAX]; //0x54
    s8 motNo[M506_PLAYER_MAX]; //0x58
    s8 winMotState[M506_PLAYER_MAX]; //0x5C; [0] also steps player 1's start motion
    M506_CAMSTOP camStop[M506_PLAYER_MAX]; //0x60
    u8 unkB0[0x20]; //0xB0
    s8 scoreDispF[M506_PLAYER_MAX]; //0xD0
    u8 unkD4[8]; //0xD4
    s16 recordSprId; //0xDC
    u8 unkDE[8]; //0xDE
    HUSPRGRPID recordWinId; //0xE6
    MGSCORE *recordScore; //0xE8
    MGSCORE *score[M506_PLAYER_MAX]; //0xEC
    float seedPosY; //0xFC
    float seedRot; //0x100
    float moundPosY; //0x104
    float vineY; //0x108
    float vineRotY; //0x10C
    float vineScale; //0x110
    float mameRotX; //0x114
    float mameScale; //0x118
    float p1RotY; //0x11C
    float seedTime; //0x120
    float unk124; //0x124
    int shadowScrollMode; //0x128
    BOOL endF; //0x12C
    M506_ROCKET rocket; //0x130
    M506_STARFIGHTER starfighter[M506_PLAYER_MAX]; //0x15C
    HU3DTEXSCRID mameShadowTexScrId; //0x1EC
    float mameShadowScrollY; //0x1F0
    HU3DMODELID particleMdlId; //0x1F4
    GAMEMESID gameMesId; //0x1F6
    s16 unk1F8[M506_PLAYER_MAX]; //0x1F8
    s16 unk200; //0x200
    HuVecF endPos; //0x204
    int seedMode; //0x210
    HUPROCESS *seedProc; //0x214
} M506_FLOW;

typedef struct M506YCameraView_s {
    float time;
    float start[6]; // hvr x/y/z, pos x/y/z
    float end[6];
} M506_YCAMERA_VIEW;

static u32 LookUpRotLockFlag[13] = {
    0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200, 0x200
};

static float LookUpRotTbl[13][2] = {
    { 180, 135 },
    { 180, 135 },
    { 100, 85 },
    { 88, 43 },
    { 84, 52 },
    { 100, 75 },
    { 72, 27 },
    { 180, 135 },
    { 180, 135 },
    { 180, 135 },
    { 180, 135 },
    { 180, 135 },
    { 180, 135 }
};

static M506_YCAMERA_VIEW YCameraView[3] = {
    { 0, { 90, 12, 2150, 0, 300, 0 }, { 90, 12, 2150, 0, 300, 0 } },
    { 120, { 73, 0, 300, 0, 60, 0 }, { 90, 0, 1500, 0, 150, 0 } },
    { 120, { 90, 0, 1500, 0, 150, 0 }, { 90, 12, 2150, 0, 300, 0 } }
};

// Pairs 0/3/6/9 place each player's score (M506ScoreCreate indexes [i*3]).
static s16 ScorePos[16][2] = {
    { 60, 160 }, { 76, 160 }, { 92, 160 },
    { 200, 160 }, { 216, 160 }, { 232, 160 },
    { 344, 160 }, { 360, 160 }, { 376, 160 },
    { 488, 160 }, { 504, 160 }, { 520, 160 },
    { 120, 160 }, { 260, 160 }, { 404, 160 }, { 548, 160 }
};

static BOOL CameraViewSkipF;
static float ScrollHeight;
static float ScrollAngle;
static BOOL MameShadowF;
static s8 ResultUnkF;
static s8 RecordInitF;
static BOOL SeedInitF;
static float LookUpCurrRot;
static BOOL StartFXFlag;
static float StartFXTime;
static float FlowTime;
M506_YSHADOW_WORK *M506YShadow;
M506_YLIGHT *M506YLight;
M506_YCAMERA_WORK *M506YCamera;
static M506_FLOW M506Flow;

static float RecordScale = 1;

void M506MainUpdate(OMOBJ *obj);
void M506FlowEndWatch(OMOBJ *obj);
void M506FlowModeEnd(OMOBJ *obj);
void M506ObjInit(M506_FLOW *flow);
BOOL M506FlowModeStart(M506_FLOW *flow);
void M506FlowModeStartSetup(M506_FLOW *flow);
void M506FlowMameSetup(M506_FLOW *flow);
BOOL M506ShadowScrollInit(M506_FLOW *flow);
void M506FlowP1Update(M506_FLOW *flow);
void M506FlowModeEndSetup(M506_FLOW *flow);
void M506FlowWinStart(M506_FLOW *flow);
BOOL M506FlowStopCheck(M506_FLOW *flow);
BOOL M506FlowResult(M506_FLOW *flow);
void M506ScoreCreate(M506_FLOW *flow);
void M506ScoreDispUpdate(M506_FLOW *flow);
void M506ScoreKill(M506_FLOW *flow);
void M506MameShadowOff(M506_FLOW *flow);
void M506MameShadowOn(M506_FLOW *flow);
void M506MameShadowScrollOn(M506_FLOW *flow);
void M506MameShadowScrollExec(M506_FLOW *flow);
void M506ParticleCreate(M506_FLOW *flow);
void M506ParticleUpdate(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx);
void M506ParticleStart(M506_FLOW *flow);
void M506ParticleKill(M506_FLOW *flow);
void M506RocketInit(M506_FLOW *flow);
int M506RocketModelUpdate(M506_FLOW *flow);
void M506RocketMove(M506_FLOW *flow);
void M506StarfighterStart(M506_FLOW *flow);
void M506StarfighterModelUpdate(M506_STARFIGHTER *starfighter, HU3DMODELID modelId);
void M506RecordCreate(M506_FLOW *flow);
void M506RecordSet(M506_FLOW *flow);
void M506RecordKill(M506_FLOW *flow);
void M506RecordBlink(M506_FLOW *flow);
void M506RecordBlinkInit(M506_FLOW *flow);
void M506YCameraProjUpdate(void);
void M506YCameraViewUpdate(void);
void M506YCameraSplitCreate(void);
void M506YCameraSplitKill(void);
void M506YLightUpdate(void);
void M506YShadowPosUpdate(void);
void M506YCameraViewSet(int cameraNo, int viewNo);
int M506YCameraViewLerp(int cameraNo, int viewNo);
int M506PointLerp(float *value, float start, float end, float time);
void M506MakeRotMtx(Mtx mtx, HuVecF *rot);
void M506SeedUpdate(void);

void M506MainCreate(OMOBJ *obj)
{
    M506_WORK *work = obj->data;

    M506Create(work);
    obj->objFunc = M506MainUpdate;
}

void M506FlowEndWatch(OMOBJ *obj)
{
    M506_WORK *work = obj->data;
    BOOL result;

    if(!M506ExitCheck(obj)) {
        result = M506FlowUpdate(work);
        if(result) {
            obj->objFunc = M506FlowModeEnd;
        }
    }
}

void M506ObjShadowMapSet(int playerNo, int height)
{
    M506_WORK *m506Work = M506MainObj->data;
    M506_WORK *work = m506Work;

    Hu3DModelShadowMapSet(work->mameMdlId[playerNo][height-1]);
}

void M506ObjShadowMapReset(int playerNo, int newHeight, int height)
{
    M506_WORK *m506Work = M506MainObj->data;
    M506_WORK *work = m506Work;
    int i;

    for(i=newHeight; i<height; i++) {
        Hu3DModelShadowMapObjReset(work->mameMdlId[playerNo][i]);
    }
}

void M506MainUpdate(OMOBJ *obj)
{
    M506_FLOW *flow;
    int i;
    BOOL result = FALSE;
    BOOL exitF = FALSE;

    flow = &M506Flow;
    exitF = M506ExitCheck(obj);
    switch(obj->work[2]) {
        case 0:
            Hu3DBGColorSet(0, 0, 0);
            flow->m506Work = obj->data;
            flow->work = flow->m506Work;
            for(i=0; i<M506_PLAYER_MAX; i++) {
                flow->playerObj[i] = M506PlayerObj[i];
                flow->player[i] = flow->playerObj[i]->data;
            }
            flow->seedMode = 0;
            flow->seedProc = HuPrcChildCreate(M506SeedUpdate, 100, 12288, 0, M506ObjMan);
            FlowTime = 0;
            M506ObjInit(flow);
            M506RecordCreate(flow);
            M506RecordSet(flow);
            M506ModelUpdate(flow->m506Work);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
            StartFXFlag = FALSE;
            StartFXTime = 0;
            flow->mode = 0;
            flow->unk2C = 0;
            flow->unk30 = 0;
            flow->time = 0;
            obj->work[2] = 1;
            break;

        case 1:
            if(!StartFXFlag) {
                StartFXTime += 1;
                if(StartFXTime >= 50) {
                    HuAudFXPlay(0x66B);
                    StartFXFlag = TRUE;
                }
            }
            if(!WipeCheckEnd()) {
                flow->seedMode = 1;
                obj->work[2] = 2;
            }
            break;

        case 2:
            result = M506FlowModeStart(flow);
            M506FlowMameSetup(flow);
            M506ModelUpdate(flow->m506Work);
            if(result) {
                obj->work[2] = 3;
            }
            break;

        case 3:
            if(exitF == TRUE) {
                break;
            }
            M506ParticleKill(&M506Flow);
            obj->work[2] = 0;
            obj->objFunc = M506FlowEndWatch;
            break;
    }
}

void M506ObjInit(M506_FLOW *flow)
{
    int i;
    M506_YCAMERA *camera;

    flow->mode = 0;
    flow->seedTime = 0;
    flow->winMotState[0] = 0;
    flow->shadowScrollMode = 0;
    flow->endF = FALSE;
    flow->gameMesId = GAMEMES_ID_NONE;
    M506YCamera->splitTime = 0;
    M506YCameraProjUpdate();
    if(!CameraViewSkipF) {
        for(i=0; i<M506_PLAYER_MAX; i++) {
            camera = &M506YCamera->camera[i];
            if(i == 0) {
                M506YCameraViewSet(i, 1);
            } else {
                M506YCameraViewSet(i, 0);
            }
        }
    }
    M506FlowModeStartSetup(flow);
    M506RocketInit(flow);
    flow->rocket.waitF = FALSE;
    flow->rocket.unk28 = 0;
    M506StarfighterStart(flow);
    M506MameShadowOff(flow);
    M506ParticleCreate(flow);
    for(i=0; i<M506_PLAYER_MAX; i++) {
        flow->unk1F8[i] = 0;
    }
    flow->unk200 = 0;
}

BOOL M506FlowModeStart(M506_FLOW *flow)
{
    int i;
    BOOL scrollDoneF = FALSE;

    switch(flow->mode) {
        case 0:
            if(flow->seedMode == 3) {
                flow->unk30 = 0;
                flow->time = 0;
                flow->mode = 1;
            }
            break;

        case 1:
            flow->time += 1;
            if(flow->time >= 30) {
                M506MameShadowOn(flow);
                LookUpCurrRot = LookUpRotTbl[flow->player[0]->charNo][0];
                Hu3DModelAttrReset(flow->work->moundMdlId, HU3D_MOTATTR_PAUSE);
                flow->unk30 = 0;
                flow->time = 0;
                flow->mode = 2;
            }
            break;

        case 2:
            M506YCameraViewLerp(0, 1);
            M506MameShadowScrollExec(flow);
            flow->vineRotY += 3;
            flow->vineScale += 0.008333334f;
            flow->vineY += 5.4166665f;
            LookUpCurrRot -= (LookUpRotTbl[flow->player[0]->charNo][0]-LookUpRotTbl[flow->player[0]->charNo][1])/120;
            if(flow->vineRotY >= 360) {
                flow->vineRotY = 360;
            }
            if(flow->vineScale >= 1) {
                flow->vineScale = 1;
            }
            if(flow->vineY >= 0) {
                flow->vineY = 0;
            }
            if(LookUpCurrRot <= LookUpRotTbl[flow->player[0]->charNo][1]) {
                LookUpCurrRot = LookUpRotTbl[flow->player[0]->charNo][1];
            }
            if(flow->vineY >= -108.333374f) {
                M506ShadowScrollInit(flow);
            }
            if(0 == flow->vineY) {
                flow->vineRotY = 0;
                flow->vineScale = 1;
                flow->vineY = 0;
                LookUpCurrRot = LookUpRotTbl[flow->player[0]->charNo][1];
                flow->mode = 3;
            }
            if(flow->player[0]->charNo != CHARNO_TERESA) {
                Hu3DMotionForceSet(flow->playerObj[0]->mdlId[0], "ske_head", LookUpRotLockFlag[flow->player[0]->charNo], LookUpCurrRot);
            }
            break;

        case 3:
            scrollDoneF = M506ShadowScrollInit(flow);
            flow->time += 1;
            if(flow->time >= 15) {
                M506YCameraViewSet(0, 2);
                flow->unk30 = 0;
                flow->mameScale = 1;
                flow->mode = 4;
            }
            break;

        case 4:
            M506ShadowScrollInit(flow);
            M506FlowP1Update(flow);
            M506YCameraViewLerp(0, 2);
            M506YCamera->splitTime += 0.008333334f;
            if(M506YCamera->splitTime >= 1) {
                M506YCamera->splitTime = 1;
            }
            M506YCameraProjUpdate();
            if(flow->player[0]->charNo != CHARNO_TERESA) {
                LookUpCurrRot += (LookUpRotTbl[flow->player[0]->charNo][0]-LookUpRotTbl[flow->player[0]->charNo][1])/60;
                if(LookUpCurrRot >= LookUpRotTbl[flow->player[0]->charNo][0]) {
                    LookUpCurrRot = LookUpRotTbl[flow->player[0]->charNo][0];
                }
                Hu3DMotionForceSet(flow->playerObj[0]->mdlId[0], "ske_head", LookUpRotLockFlag[flow->player[0]->charNo], LookUpCurrRot);
            }
            if(M506YCamera->splitTime >= 1) {
                for(i=0; i<3; i++) {
                    espDispOn(M506YCamera->splitSprId[i]);
                }
                Hu3DBGColorSet(0, 127, 255);
                if(flow->player[0]->charNo != CHARNO_TERESA) {
                    Hu3DMotionNoMotReset(flow->playerObj[0]->mdlId[0], "ske_head", LookUpRotLockFlag[flow->player[0]->charNo]);
                }
                Hu3DModelAttrSet(flow->work->seedMdlId, HU3D_ATTR_DISPOFF);
                flow->mode = 5;
            }
            break;

        case 5:
            flow->mode = 0;
            return TRUE;
    }
    return FALSE;
}

void M506FlowModeStartSetup(M506_FLOW *flow)
{
    int i;

    flow->seedPosY = 200;
    flow->seedRot = 0;
    flow->moundPosY = 10;
    flow->vineY = -650;
    flow->vineRotY = 0;
    flow->vineScale = 0;
    flow->mameRotX = 0;
    flow->mameScale = 0;
    flow->p1RotY = 120;
    Hu3DModelAttrReset(flow->work->seedMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelRotSet(flow->work->moundMdlId, 0, 0, 0);
    Hu3DModelAttrReset(flow->work->moundMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(flow->work->moundMdlId, HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(flow->work->moundMdlId, 0.5f);
    Hu3DMotionTimeSet(flow->work->moundMdlId, 0);
    Hu3DModelAttrSet(flow->work->moundMdlId, HU3D_MOTATTR_PAUSE);
    M506FlowMameSetup(flow);
    for(i=0; i<M506_PLAYER_MAX; i++) {
        omSetTra(flow->playerObj[i], -64.5f, 0, 179.5f);
        omSetRot(flow->playerObj[i], 0, 0, 0);
    }
    omSetRot(flow->playerObj[0], 0, flow->p1RotY, 0);
}

void M506FlowMameSetup(M506_FLOW *flow)
{
    int i;

    Hu3DModelPosSet(flow->work->seedMdlId, 0, flow->seedPosY, 0);
    Hu3DModelRotSet(flow->work->seedMdlId, flow->seedRot, flow->seedRot, 0);
    Hu3DModelPosSet(flow->work->moundMdlId, 0, flow->moundPosY, 0);
    for(i=0; i<2; i++) {
        Hu3DModelPosSet(flow->work->mameVineMdlId[0][i], 0, flow->vineY-(600.0f*i), 0);
        Hu3DModelRotSet(flow->work->mameVineMdlId[0][i], 0, flow->vineRotY, 0);
        Hu3DModelScaleSet(flow->work->mameVineMdlId[0][i], flow->vineScale, 1, flow->vineScale);
    }
    Hu3DModelRotSet(flow->work->mameMdlId[0][0], flow->mameRotX, -20+(40.0f*flow->work->mameSide[0][0]), 0);
    Hu3DModelScaleSet(flow->work->mameMdlId[0][0], flow->mameScale, flow->mameScale, flow->mameScale);
}

BOOL M506ShadowScrollInit(M506_FLOW *flow)
{
    switch(flow->shadowScrollMode) {
        case 0:
            flow->mameScale += 0.06666667f;
            if(flow->mameScale >= 1) {
                ScrollHeight = 2;
                ScrollAngle = 0;
                flow->mameScale = 1;
                flow->shadowScrollMode++;
            }
            if(!MameShadowF) {
                M506MameShadowScrollOn(flow);
                MameShadowF = TRUE;
            }
            break;

        case 1:
            ScrollHeight -= 0.033333335f;
            if(ScrollHeight < 0) {
                ScrollHeight = 0;
                flow->shadowScrollMode++;
                MameShadowF = FALSE;
                return TRUE;
            }
            ScrollAngle += 16;
            flow->mameRotX = ScrollHeight*HuSin(ScrollAngle);
            break;
    }
    return FALSE;
}

void M506FlowP1Update(M506_FLOW *flow)
{
    OMOBJ *obj = M506PlayerObj[0];
    float time = 0;

    switch(flow->winMotState[0]) {
        case 0:
            if(flow->player[0]->charNo != CHARNO_TERESA) {
                Hu3DMotionTimeSet(obj->mdlId[0], 0);
                Hu3DMotionSpeedSet(obj->mdlId[0], 1);
                Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[6], 0, 4, HU3D_ATTR_NONE);
            }
            flow->winMotState[0]++;
            break;

        case 1:
            if(flow->player[0]->charNo != CHARNO_TERESA) {
                time = Hu3DMotionTimeGet(obj->mdlId[0]);
                if(time >= 58) {
                    Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[0], 0, 4, HU3D_MOTATTR_LOOP);
                    flow->winMotState[0]++;
                }
            } else {
                flow->winMotState[0]++;
            }
            break;
    }
    flow->p1RotY -= 2;
    if(flow->p1RotY < 0) {
        flow->p1RotY = 0;
    }
    omSetRot(flow->playerObj[0], 0, flow->p1RotY, 0);
}

void M506FlowModeEnd(OMOBJ *obj)
{
    M506_FLOW *flow;
    int i;
    BOOL result = FALSE;
    BOOL exitF = FALSE;

    flow = &M506Flow;
    exitF = M506ExitCheck(obj);
    switch(obj->work[2]) {
        case 0:
            flow->m506Work = obj->data;
            flow->work = flow->m506Work;
            for(i=0; i<M506_PLAYER_MAX; i++) {
                flow->playerObj[i] = M506PlayerObj[i];
                flow->player[i] = flow->playerObj[i]->data;
            }
            flow->endF = TRUE;
            M506FlowModeEndSetup(flow);
            M506ModelUpdate(flow->m506Work);
            M506ScoreCreate(flow);
            M506RecordBlinkInit(flow);
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            obj->work[2] = 1;
            break;

        case 1:
            M506ModelUpdate(flow->m506Work);
            if(!WipeCheckEnd()) {
                HuAudFXPlay(0x1D);
                obj->work[2] = 2;
            }
            break;

        case 2:
            result = M506FlowStopCheck(flow);
            M506ModelUpdate(flow->m506Work);
            if(result) {
                for(i=0; i<M506_PLAYER_MAX; i++) {
                    flow->scoreDispF[i] = TRUE;
                }
                flow->mode = 0;
                flow->unk30 = 0;
                flow->time = 0;
                if(_CheckFlag(FLAG_INST_DECA)) {
                    obj->work[2] = 6;
                } else {
                    obj->work[2] = 3;
                }
            }
            M506ScoreDispUpdate(flow);
            break;

        case 3:
            M506ModelUpdate(flow->m506Work);
            flow->time += 1;
            if(flow->time >= 30) {
                flow->unk30 = 0;
                flow->time = 0;
                obj->work[2] = 4;
            }
            break;

        case 4:
            M506ModelUpdate(flow->m506Work);
            result = M506FlowResult(flow);
            M506RecordBlink(flow);
            if(result) {
                obj->work[2] = 5;
            }
            break;

        case 5:
            M506RecordBlink(flow);
            if((FlowTime += 1) >= 210) {
                obj->work[2] = 6;
            }
            break;

        case 6:
            M506ModelUpdate(flow->m506Work);
            if(!_CheckFlag(FLAG_INST_DECA)) {
                M506RecordBlink(flow);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
                obj->work[2] = 7;
            } else {
                flow->time += 1;
                if(flow->time >= 60) {
                    for(i=0; i<M506_PLAYER_MAX; i++) {
                        int score = flow->height[i]*3;
                        GwPlayer[i].mgScore = score;
                    }
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
                    flow->unk30 = 0;
                    flow->time = 0;
                    obj->work[2] = 7;
                }
            }
            break;

        case 7:
            M506ModelUpdate(flow->m506Work);
            if(!_CheckFlag(FLAG_INST_DECA)) {
                M506RecordBlink(flow);
            }
            if(!WipeCheckEnd()) {
                obj->work[2] = 8;
            }
            break;

        case 8:
            if(exitF == TRUE) {
                break;
            }
            obj->work[2] = 0;
            HuAudFadeOut(1000);
            obj->objFunc = M506Exit;
            break;
    }
}

void M506FlowModeEndSetup(M506_FLOW *flow)
{
    s8 rank[M506_PLAYER_MAX];
    int charNo[M506_PLAYER_MAX];
    int i;
    int best;
    int j;
    int humanBest;
    M506_YCAMERA *camera;
    M506_CAMSTOP *camStop;
    float posX;
    float posYOfs;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        charNo[i] = flow->player[i]->charNo;
    }
    flow->recordHeight = flow->m506Work->recordVal/3;
    best = 0;
    humanBest = 0;
    flow->winnerNum = 0;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        flow->maxHeight[i] = flow->player[i]->height;
        flow->height[i] = flow->player[i]->newHeight;
        flow->winnerChar[i] = -1;
        rank[i] = -1;
    }
    best = 0;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(flow->height[i] > best) {
            best = flow->height[i];
            flow->winnerNum = 1;
            rank[i] = 0;
            for(j=0; j<i; j++) {
                rank[j] = -1;
            }
        } else if(flow->height[i] == best && best != 0) {
            flow->winnerNum++;
            rank[i] = 0;
        }
    }
    for(i=0; i<M506_PLAYER_MAX; i++) {
        flow->rank[i] = rank[i];
    }
    humanBest = 0;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(flow->height[i] > humanBest && rank[i] == 0 && GwPlayerConf[flow->player[i]->no].type == GW_TYPE_MAN) {
            humanBest = flow->height[i];
        }
    }
    flow->humanBest = humanBest;
    flow->humanWinF = FALSE;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(rank[i] == 0 && GwPlayerConf[flow->player[i]->no].type == GW_TYPE_MAN) {
            flow->humanWinF = TRUE;
            break;
        }
    }
    for(i=0; i<M506_PLAYER_MAX; i++) {
        flow->winMotState[i] = 0;
        if(rank[i] == -1) {
            flow->motNo[i] = 5;
        } else if(rank[i] == 0) {
            flow->motNo[i] = 4;
        }
    }
    best = 0;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(rank[i] != -1) {
            flow->winnerChar[best] = charNo[i];
            best++;
        }
    }
    for(i=0; i<M506_PLAYER_MAX; i++) {
        camStop = &flow->camStop[i];
        if(flow->height[i] < 1) {
            camStop->targetY = 300;
        } else {
            camStop->targetY = 100+(300.0f*flow->height[i]);
        }
        camStop->mode = 0;
        camStop->speed = 0;
        camStop->accel = 0.4f;
        camStop->decay = 0.01f;
    }
    M506YCamera->splitTime = 1;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        camera = &M506YCamera->camera[i];
        camera->hvr.x = 90;
        camera->hvr.y = 12;
        camera->hvr.z = 2150;
        camera->pos.x = 0;
        camera->pos.y = 300;
        camera->pos.z = 0;
    }
    M506YCameraUpdate();
    M506YCameraProjUpdate();
    {
    float endPosX[2] = { -64.5f, 64.5f };
    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(flow->height[i] == 0) {
            posX = endPosX[0];
        } else {
            posX = endPosX[flow->work->mameSide[i][flow->height[i]-1]];
        }
        if(flow->height[i] == 0) {
            posYOfs = 0;
        } else {
            posYOfs = 60;
        }
        flow->endPos.x = posX;
        flow->endPos.y = (300.0f*flow->height[i])+posYOfs;
        flow->endPos.z = 179.5f;
        omSetTra(flow->playerObj[i], flow->endPos.x, flow->endPos.y, flow->endPos.z);
        omSetRot(flow->playerObj[i], 0, 0, 0);
    }
    }
    M506RocketInit(flow);
    for(i=0; i<M506_PLAYER_MAX; i++) {
        Hu3DModelAttrSet(flow->work->starfighterMdlId[i], HU3D_ATTR_DISPOFF);
    }
    M506StarfighterStart(flow);
}

void M506FlowWinStart(M506_FLOW *flow)
{
    int i;
    OMOBJ *obj;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        obj = M506PlayerObj[i];
        switch(flow->winMotState[i]) {
            case 0:
                Hu3DMotionSpeedSet(obj->mdlId[0], 1);
                Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[flow->motNo[i]], 0, 4, HU3D_ATTR_NONE);
                flow->winMotState[i]++;
                break;

            case 1:
                break;
        }
    }
}

BOOL M506FlowStopCheck(M506_FLOW *flow)
{
    int stopNum;
    int j;
    M506_YCAMERA *camera;
    int i;
    M506_CAMSTOP *camStop;
    float dist;
    float speed;

    stopNum = 0;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        camera = &M506YCamera->camera[i];
        camStop = &flow->camStop[i];
        if(camera->pos.y < camStop->targetY) {
            if(camStop->mode == 0) {
                camStop->speed += camStop->accel-(camStop->speed*camStop->decay);
                dist = 0;
                speed = camStop->speed;
                for(j=0; j<32; j++) {
                    dist += speed;
                    speed *= 0.9f;
                }
                if(dist > camStop->targetY-camera->pos.y) {
                    camStop->mode = 1;
                }
            } else if(camStop->mode == 1) {
                camStop->speed *= 0.9f;
            }
            camera->pos.y += camStop->speed;
            if(camera->pos.y > camStop->targetY) {
                camera->pos.y = camStop->targetY;
            }
        } else {
            if(flow->scoreDispF[i] == FALSE) {
                s16 panTbl[M506_PLAYER_MAX] = { 40, 56, 72, 88 };
                HuAudFXPlayPan(0x21, panTbl[i]);
            }
            flow->scoreDispF[i] = TRUE;
            stopNum++;
        }
    }
    if(stopNum == M506_PLAYER_MAX) {
        HuAudFXPlay(0x1E);
        return TRUE;
    }
    return FALSE;
}

BOOL M506FlowResult(M506_FLOW *flow)
{
    int i;

    switch(flow->mode) {
        case 0:
            ResultUnkF = 0;
            flow->gameMesId = GAMEMES_ID_NONE;
            if(flow->humanBest > flow->recordHeight) {
                flow->gameMesId = GameMesRecordCreate(flow->humanBest*3);
                flow->mode = 1;
                flow->m506Work->recordVal = flow->humanBest*3;
                M506RecordSet(flow);
                GWMgRecordSet(0, flow->humanBest*3);
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    HuAudJinglePlay(0x86);
                }
            } else {
                flow->mode = 2;
            }
            break;

        case 1:
            if(GameMesStatGet(flow->gameMesId) == 0) {
                if(flow->gameMesId >= 0) {
                    GameMesKill(flow->gameMesId);
                }
                flow->mode = 2;
            }
            break;

        case 2:
            M506FlowWinStart(flow);
            FlowTime += 1;
            flow->gameMesId = GAMEMES_ID_NONE;
            if(flow->winnerNum == 0) {
                flow->gameMesId = GameMesMgDrawCreate();
                HuAudJinglePlay(0x7B);
                CharLoseVoicePlay(flow->player[0]->charNo, flow->player[1]->charNo, flow->player[2]->charNo, flow->player[3]->charNo);
            } else {
                flow->gameMesId = GameMesMgWinnerCreate(flow->winnerChar[0], flow->winnerChar[1], flow->winnerChar[2], flow->winnerChar[3]);
                if(flow->humanWinF == FALSE) {
                    HuAudJinglePlay(0x79);
                } else if(flow->humanWinF == TRUE) {
                    HuAudJinglePlay(0x79);
                }
                for(i=0; i<M506_PLAYER_MAX; i++) {
                    if(flow->rank[i] == 0 && !_CheckFlag(FLAG_MG_PRACTICE)) {
                        GwPlayer[i].mgCoinBonus = 10;
                    }
                }
            }
            flow->mode = 3;
            break;

        case 3:
            M506FlowWinStart(flow);
            FlowTime += 1;
            if(GameMesStatGet(flow->gameMesId) == 0) {
                flow->mode = 0;
                return TRUE;
            }
            break;
    }
    return FALSE;
}

void M506ScoreCreate(M506_FLOW *flow)
{
    int i;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        flow->scoreDispF[i] = FALSE;
        flow->score[i] = MgScoreCreate(MGCONST_ANM_scoreBlue, MGCONST_ANM_unitBlueSmall, FALSE);
        MgScoreMaxDigitSet(flow->score[i], 3);
        MgScoreScaleSet(flow->score[i], 1, 1);
        MgScoreValueSet(flow->score[i], 0);
        MgScorePosSet(flow->score[i], (ScorePos[i*3][0]-20.0f)-8.0f, 12.0f+ScorePos[i*3][1]);
        MgScoreZRotSet(flow->score[i], 0);
        MgScoreTPLvlSet(flow->score[i], 1);
        MgScoreColorSet(flow->score[i], 255, 255, 255);
        MgScoreDigitWidthSet(flow->score[i], 18);
        MgScorePriSet(flow->score[i], 256);
        MgScoreDispOff(flow->score[i]);
        HuSprBankSet(flow->score[i]->grpId, 5, 1);
    }
}

void M506ScoreDispUpdate(M506_FLOW *flow)
{
    int i;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(flow->scoreDispF[i] == FALSE) {
            MgScoreDispOff(flow->score[i]);
        } else if(flow->scoreDispF[i] == TRUE) {
            MgScoreValueSet(flow->score[i], flow->height[i]*3);
            MgScoreDispOn(flow->score[i]);
        }
    }
}

void M506ScoreKill(M506_FLOW *flow)
{
    int i;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        if(flow->score[i]) {
            MgScoreKill(flow->score[i]);
        }
    }
}

void M506MameShadowOff(M506_FLOW *flow)
{
    Hu3DModelAttrSet(flow->work->mameShadowMdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(flow->work->mameShadowMdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(flow->work->mameShadowMdlId[0], 0);
    Hu3DMotionSpeedSet(flow->work->mameShadowMdlId[0], 0.5f);
    flow->mameShadowScrollY = 0;
    flow->mameShadowTexScrId = Hu3DTexScrollCreate(flow->work->mameShadowMdlId[0], "I8m506sdw01");
    Hu3DTexScrollPosSet(flow->mameShadowTexScrId, 0, flow->mameShadowScrollY, 0);
    Hu3DModelAttrSet(flow->work->glowShadowMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(flow->work->glowShadowMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(flow->work->glowShadowMdlId, 0);
    Hu3DMotionSpeedSet(flow->work->glowShadowMdlId, 1);
}

void M506MameShadowOn(M506_FLOW *flow)
{
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(flow->work->mameShadowMdlId[0], HU3D_MOTATTR_PAUSE);
}

void M506MameShadowScrollOn(M506_FLOW *flow)
{
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(flow->work->glowShadowMdlId, HU3D_MOTATTR_PAUSE);
}

void M506MameShadowScrollExec(M506_FLOW *flow)
{
    flow->mameShadowScrollY += 0.0033333334f;
    if(flow->mameShadowScrollY > 0.4f) {
        flow->mameShadowScrollY = 0.4f;
    }
    Hu3DTexScrollPosSet(flow->mameShadowTexScrId, 0, flow->mameShadowScrollY, 0);
}

void M506ParticleCreate(M506_FLOW *flow)
{
    ANIMDATA *anim;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;
    int i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(M506_ANM_cloud, HU_MEMNUM_OVL, HEAP_MODEL));
    flow->particleMdlId = Hu3DParticleCreate(anim, 32);
    particleP = Hu3DData[flow->particleMdlId].hookData;
    Hu3DParticleBlendModeSet(flow->particleMdlId, 1);
    Hu3DParticleHookSet(flow->particleMdlId, M506ParticleUpdate);
    Hu3DModelLayerSet(flow->particleMdlId, 6);
    Hu3DModelPosSet(flow->particleMdlId, 0, 0, 0);
    Hu3DParticleColSet(flow->particleMdlId, 0x80, 0x40, 0x20);
    for(particleDataP = particleP->data, i=0; i<particleP->maxCnt; i++, particleDataP++) {
        particleDataP->time = 0;
        particleDataP->scale = 0;
        particleDataP->color.a = 0;
    }
}

// The particle fields are reused: time is the state, parManId a start delay
// and accel.x the alpha.
void M506ParticleUpdate(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *particleDataP = particleP->data;
    int i;
    float radius = 0;
    float angle = 0;
    float randA;
    float randB;

    for(i=0; i<particleP->maxCnt; i++, particleDataP++) {
        switch(particleDataP->time) {
            case 0:
                break;

            case 1:
                particleDataP->parManId = frandmod(16);
                particleDataP->accel.x = 0;
                particleDataP->color.a = 0;
                particleDataP->color.r = 0xE0;
                particleDataP->color.g = 0x80;
                particleDataP->color.b = 0x40;
                particleDataP->scale = 0;
                particleDataP->zRot = 0;
                randB = (s32)(frandmod(300)+1)/100.0f;
                particleDataP->pos.x = ((s32)(frandmod(300)+1)/100.0f)-randB;
                particleDataP->pos.y = 10;
                randB = (s32)(frandmod(300)+1)/100.0f;
                particleDataP->pos.z = ((s32)(frandmod(300)+1)/100.0f)-randB;
                radius = 0.25f;
                randA = (s32)(frandmod(20)+1)/100.0f;
                randB = (s32)(frandmod(20)+1)/100.0f;
                particleDataP->vel.x = ((radius*HuCos(angle))+randB)-randA;
                randB = (s32)(frandmod(10)+1)/100.0f;
                particleDataP->vel.y = (0.3f+((s32)(frandmod(10)+1)/100.0f))-randB;
                randB = (s32)(frandmod(20)+1)/100.0f;
                randA = (s32)(frandmod(20)+1)/100.0f;
                particleDataP->vel.z = ((radius*HuSin(angle))+randA)-randB;
                angle += 360.0f/particleP->maxCnt;
                particleDataP->time++;

            case 2:
                if(--particleDataP->parManId < 0) {
                    particleDataP->time++;
                }
                break;

            case 3:
            case 4:
                particleDataP->scale += 0.3f;
                particleDataP->pos.x += particleDataP->vel.x;
                particleDataP->pos.y += particleDataP->vel.y;
                particleDataP->pos.z += particleDataP->vel.z;
                if(particleDataP->time == 3) {
                    particleDataP->accel.x += 0.125f;
                    if(particleDataP->accel.x >= 1) {
                        particleDataP->time++;
                        particleDataP->accel.x = 1;
                    }
                } else if(particleDataP->time == 4) {
                    particleDataP->accel.x -= 0.010416667f;
                    if(particleDataP->accel.x <= 0) {
                        particleDataP->accel.x = 0;
                    }
                }
                particleDataP->color.a = 64.0f*particleDataP->accel.x;
                if(particleDataP->time == 4 && particleDataP->accel.x <= 0) {
                    particleDataP->time = 0;
                }
                break;
        }
    }
}

void M506ParticleStart(M506_FLOW *flow)
{
    HU3DPARTICLE *particleP = Hu3DData[flow->particleMdlId].hookData;
    HU3DPARTICLEDATA *particleDataP = particleP->data;
    int i;

    for(i=0; i<particleP->maxCnt; i++, particleDataP++) {
        particleDataP->time = 1;
    }
}

void M506ParticleKill(M506_FLOW *flow)
{
    Hu3DModelKill(flow->particleMdlId);
}

void M506RocketInit(M506_FLOW *flow)
{
    M506_ROCKET *rocket = &flow->rocket;

    rocket->pos.x = 600;
    rocket->pos.y = 11100;
    rocket->pos.z = -2500;
    rocket->rot.x = 0;
    rocket->rot.y = 0;
    rocket->rot.z = 90;
    if(flow->endF == FALSE) {
        rocket->speed = 5;
    } else if(flow->endF == TRUE) {
        rocket->speed = 7.5f;
    }
    rocket->mode = 0;
    rocket->startF = FALSE;
}

void M506RocketUpdate(void)
{
    int i;
    M506_FLOW *flow;
    M506_ROCKET *rocket;
    int result = 0;
    M506_YCAMERA *camera;

    flow = &M506Flow;
    rocket = &flow->rocket;
    if(flow->endF == FALSE && flow->work->rocketCamBit == 0) {
        for(i=0; i<M506_PLAYER_MAX; i++) {
            if(flow->player[i]->newHeight == 30) {
                flow->work->rocketCamBit |= M506CameraBit[i];
            }
        }
    }
    if(!rocket->startF) {
        if(flow->endF == FALSE) {
            for(i=0; i<M506_PLAYER_MAX; i++) {
                if(flow->player[i]->newHeight == 35) {
                    rocket->startF = TRUE;
                    rocket->waitF = TRUE;
                    break;
                }
            }
        } else if(flow->endF == TRUE && rocket->waitF == TRUE) {
            for(i=0; i<M506_PLAYER_MAX; i++) {
                camera = &M506YCamera->camera[i];
                if(camera->pos.y >= 9900) {
                    rocket->startF = TRUE;
                    break;
                }
            }
        }
    }
    switch(rocket->mode) {
        case 0:
            if(rocket->startF) {
                rocket->mode++;
            }
            break;

        case 1:
            result = M506RocketModelUpdate(flow);
            if(result) {
                rocket->mode++;
            }
            break;

        case 2:
            break;
    }
}

int M506RocketModelUpdate(M506_FLOW *flow)
{
    M506_ROCKET *rocket = &flow->rocket;
    HuVecF dir;
    Mtx rotMtx;

    M506RocketMove(flow);
    dir.x = 0;
    dir.y = rocket->speed;
    dir.z = 0;
    M506MakeRotMtx(rotMtx, &rocket->rot);
    MTXMultVec(rotMtx, &dir, &dir);
    rocket->pos.x += dir.x;
    rocket->pos.y += dir.y;
    rocket->pos.z += dir.z;
    Hu3DModelPosSet(flow->work->rocketMdlId, rocket->pos.x, rocket->pos.y, rocket->pos.z);
    Hu3DModelRotSet(flow->work->rocketMdlId, rocket->rot.x, rocket->rot.y, rocket->rot.z);
    return 0;
}

void M506RocketMove(M506_FLOW *flow)
{
    static float rotTbl[6] = { 0, 90, 15, 30, 10, 45 };
    M506_ROCKET *rocket = &flow->rocket;

    if(flow->endF == FALSE) {
        rocket->rot.x += (rotTbl[2]-rotTbl[0])/200;
        rocket->rot.z += (rotTbl[3]-rotTbl[1])/200;
    } else if(flow->endF == TRUE) {
        rocket->rot.x += (rotTbl[4]-rotTbl[0])/200;
        rocket->rot.z += (rotTbl[5]-rotTbl[1])/200;
    }
}

void M506StarfighterStart(M506_FLOW *flow)
{
    M506_STARFIGHTER *starfighter;
    int i;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        starfighter = &flow->starfighter[i];
        starfighter->pos.x = 700;
        starfighter->pos.y = 15300;
        starfighter->pos.z = -2500;
        starfighter->rot.x = -45;
        starfighter->rot.y = 0;
        starfighter->rot.z = 135;
        starfighter->speed = 16;
        starfighter->mode = 0;
        starfighter->startF = FALSE;
        M506StarfighterModelUpdate(starfighter, flow->work->starfighterMdlId[i]);
        Hu3DModelAttrSet(flow->work->starfighterMdlId[i], HU3D_ATTR_DISPOFF);
    }
}

void M506StarfighterUpdate(void)
{
    M506_STARFIGHTER *starfighter;
    M506_FLOW *flow;
    int i;

    flow = &M506Flow;
    for(i=0; i<M506_PLAYER_MAX; i++) {
        starfighter = &flow->starfighter[i];
        if(!starfighter->startF && flow->player[i]->newHeight == 50 && !flow->player[i]->upJumpF) {
            Hu3DModelAttrReset(flow->work->starfighterMdlId[i], HU3D_ATTR_DISPOFF);
            starfighter->startF = TRUE;
        }
        switch(starfighter->mode) {
            case 0:
                if(starfighter->startF) {
                    starfighter->mode++;
                }
                break;

            case 1:
                M506StarfighterModelUpdate(starfighter, flow->work->starfighterMdlId[i]);
                break;
        }
    }
}

void M506StarfighterModelUpdate(M506_STARFIGHTER *starfighter, HU3DMODELID modelId)
{
    HuVecF dir;
    Mtx rotMtx;

    dir.x = 0;
    dir.y = starfighter->speed;
    dir.z = 0;
    M506MakeRotMtx(rotMtx, &starfighter->rot);
    MTXMultVec(rotMtx, &dir, &dir);
    starfighter->pos.x += dir.x;
    starfighter->pos.y += dir.y;
    starfighter->pos.z += dir.z;
    Hu3DModelPosSet(modelId, starfighter->pos.x, starfighter->pos.y, starfighter->pos.z);
    Hu3DModelRotSet(modelId, starfighter->rot.x, starfighter->rot.y, starfighter->rot.z);
}

void M506RecordCreate(M506_FLOW *flow)
{
    if(!_CheckFlag(FLAG_INST_DECA)) {
        flow->recordSprId = espEntry(M506_ANM_crown, 0, 0);
        espDispOff(flow->recordSprId);
        espPriSet(flow->recordSprId, 16);
        espPosSet(flow->recordSprId, 236, 420);
        espScaleSet(flow->recordSprId, 1, 1);
        espAttrSet(flow->recordSprId, HUSPR_ATTR_NOANIM);
        espDispOn(flow->recordSprId);
        flow->recordScore = MgScoreCreate(MGCONST_ANM_scoreTime, MGCONST_ANM_unitSmall, FALSE);
        MgScoreMaxDigitSet(flow->recordScore, 3);
        MgScoreScaleSet(flow->recordScore, 1, 1);
        MgScoreValueSet(flow->recordScore, 0);
        MgScorePosSet(flow->recordScore, 258, 420);
        MgScoreZRotSet(flow->recordScore, 0);
        MgScoreTPLvlSet(flow->recordScore, 1);
        MgScoreColorSet(flow->recordScore, 0x42, 0xFF, 0x7A);
        MgScoreDigitWidthSet(flow->recordScore, 16);
        MgScoreDispOn(flow->recordScore);
        flow->recordWinId = MgScoreWinCreate(0x90, 0x28);
        MgScoreWinColorSet(flow->recordWinId, 0, 0, 0);
        MgScoreWinTPLvlSet(flow->recordWinId, 0.7f);
        MgScoreWinPosSet(flow->recordWinId, 288, 420);
        MgScoreWinDispSet(flow->recordWinId, TRUE);
    }
}

void M506RecordSet(M506_FLOW *flow)
{
    if(!_CheckFlag(FLAG_INST_DECA)) {
        MgScoreValueSet(flow->recordScore, flow->m506Work->recordVal);
    }
}

void M506RecordKill(M506_FLOW *flow)
{
    if(!_CheckFlag(FLAG_INST_DECA)) {
        espKill(flow->recordSprId);
        if(flow->recordScore) {
            MgScoreKill(flow->recordScore);
        }
    }
}

// Upstream's symbols name the scale recordScale$725, a function static, yet
// M506RecordBlinkInit writes the same object; a file static behaves the same.
void M506RecordBlink(M506_FLOW *flow)
{
    if(!_CheckFlag(FLAG_INST_DECA) && flow->humanBest > flow->recordHeight) {
        if(RecordInitF == 0) {
            RecordScale += 0.02f;
            if(RecordScale >= 1.2f) {
                RecordScale = 1.2f;
                RecordInitF = 1;
            }
        } else if(RecordInitF == 1) {
            RecordScale -= 0.04f;
            if(RecordScale <= 1) {
                RecordScale = 1;
                RecordInitF = 0;
            }
        }
        espScaleSet(flow->recordSprId, RecordScale, RecordScale);
        MgScoreDigitScaleSet(flow->recordScore, RecordScale, RecordScale);
    }
}

void M506RecordBlinkInit(M506_FLOW *flow)
{
    if(!_CheckFlag(FLAG_INST_DECA)) {
        RecordInitF = 0;
        RecordScale = 1;
    }
}

void fn_1_9EC4(void)
{
}

void fn_1_9EC8(void)
{
}

void fn_1_9ECC(void)
{
}

void M506Debug(char *str, ...)
{
}

void M506YCameraInit(void)
{
    int i;
    M506_YCAMERA *camera;

    M506YCamera = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M506_YCAMERA_WORK), HU_MEMNUM_OVL);
    if(M506YCamera == NULL) {
        OSReport("M506YCameraInit Error...\n");
        return;
    }
    for(i=0; i<M506_PLAYER_MAX; i++) {
        camera = &M506YCamera->camera[i];
        camera->bit = M506CameraBit[i];
        Hu3DCameraCreate(camera->bit);
        camera->center.x = 0;
        camera->center.y = 0;
        camera->center.z = 0;
        camera->target.x = 0;
        camera->target.y = 0;
        camera->target.z = 0;
        camera->hvr.x = 90;
        camera->hvr.y = 0;
        camera->hvr.z = 2000;
        camera->unk4C = 0;
        camera->pos.x = 0;
        camera->pos.y = 300;
        camera->pos.z = 0;
        camera->fov = 30;
    }
    M506YCamera->splitTime = 1;
    M506YCamera->unk1D4 = FALSE;
    M506YCameraSplitCreate();
    M506YCameraUpdate();
    M506YCameraProjUpdate();
}

// Retail frees the camera work before M506YCameraSplitKill reads its sprite
// ids back out of it. HuMem does not clear or reuse a freed block before the
// next allocation, so the ids are still intact; kept as-is.
void M506YCameraClose(void)
{
    M506_FLOW *flow = &M506Flow;

    HuMemDirectFree(M506YCamera);
    M506ScoreKill(flow);
    M506YCameraSplitKill();
    M506RecordKill(flow);
    M506ParticleKill(flow);
    if(flow->gameMesId >= 0) {
        GameMesKill(flow->gameMesId);
    }
}

void fn_1_A1C4(void)
{
}

void M506YCameraUpdate(void)
{
    static HuVecF up = { 0, 1, 0 };
    static HuVecF forward = { 0, 0, 1 };
    int i;
    M506_YCAMERA *camera;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        camera = &M506YCamera->camera[i];
        camera->target.x = camera->pos.x;
        camera->target.y = camera->pos.y;
        camera->target.z = camera->pos.z;
        camera->center.x = camera->target.x+(camera->hvr.z*HuCos(camera->hvr.y)*HuCos(camera->hvr.x));
        camera->center.y = camera->target.y+(camera->hvr.z*HuSin(camera->hvr.y));
        camera->center.z = camera->target.z+(camera->hvr.z*HuCos(camera->hvr.y)*HuSin(camera->hvr.x));
        VECSubtract(&camera->target, &camera->center, &camera->dir);
        VECNormalize(&camera->dir, &camera->dir);
        VECCrossProduct(&up, &camera->dir, &camera->upDir);
        VECNormalize(&camera->upDir, &camera->upDir);
        VECCrossProduct(&camera->dir, &camera->upDir, &camera->up);
        VECNormalize(&camera->up, &camera->up);
        Hu3DCameraPosSet(camera->bit, camera->center.x, camera->center.y, camera->center.z,
            camera->up.x, camera->up.y, camera->up.z,
            camera->target.x, camera->target.y, camera->target.z);
    }
}

void M506YCameraProjUpdate(void)
{
    int i;
    M506_YCAMERA *camera;

    M506YCameraViewUpdate();
    for(i=0; i<M506_PLAYER_MAX; i++) {
        camera = &M506YCamera->camera[i];
        Hu3DCameraPerspectiveSet(camera->bit, camera->fov, 20, 30000, camera->aspect);
        Hu3DCameraViewportSet(camera->bit, camera->viewportX, 0, camera->viewportW, 480, 0, 1);
        Hu3DCameraScissorSet(camera->bit, camera->scissorX, 0, camera->scissorW, 480);
    }
}

// splitTime 0 -> 1 slides the single full-screen view into four 160px strips.
void M506YCameraViewUpdate(void)
{
    M506_YCAMERA *camera;
    int scissorW;
    float t = M506YCamera->splitTime;
    float w;

    camera = &M506YCamera->camera[0];
    camera->aspect = (151+(425*(1-t)))/480;
    camera->viewportX = 0;
    camera->viewportW = 160+(480*(1-t));
    if(t < 0.33333334f) {
        camera->scissorX = 0;
        camera->scissorW = (int)camera->viewportW-2.0f;
    } else if(t < 1) {
        camera->scissorX = 0;
        camera->scissorW = camera->viewportW-2;
    } else {
        camera->scissorX = 0;
        camera->scissorW = camera->viewportW;
    }

    camera = &M506YCamera->camera[1];
    camera->aspect = 0.28541666f;
    camera->viewportX = 160;
    camera->viewportW = 160;
    if(t < 1) {
        w = 160*((t-0.6666667f)/0.33333334f);
        camera->scissorX = 160+(160-w);
        camera->scissorW = w;
    } else {
        camera->scissorX = 161;
        camera->scissorW = 158;
    }

    camera = &M506YCamera->camera[2];
    camera->aspect = 0.28541666f;
    camera->viewportX = 320;
    camera->viewportW = 160;
    if(t < 0.6666667f) {
        w = 160*((t-0.33333334f)/0.33333334f);
        camera->scissorX = 320+(160-w);
        camera->scissorW = w;
    } else {
        camera->scissorX = 321;
        camera->scissorW = 158;
    }

    camera = &M506YCamera->camera[3];
    camera->aspect = 0.31458333f;
    camera->viewportX = 480;
    camera->viewportW = 160;
    if(t < 0.33333334f) {
        scissorW = 160*(t/0.33333334f);
        camera->scissorX = 640-scissorW;
        camera->scissorW = 640-camera->scissorX;
    } else {
        camera->scissorX = 481;
        camera->scissorW = 159;
    }
}

void M506YCameraSplitCreate(void)
{
    float posX[3] = { 144, 288, 432 };
    int i;

    for(i=0; i<3; i++) {
        M506YCamera->splitSprId[i] = espEntry(M506_ANM_split, 0, 0);
        espDispOff(M506YCamera->splitSprId[i]);
        espPriSet(M506YCamera->splitSprId[i], 258);
        espPosSet(M506YCamera->splitSprId[i], 0, 240);
        espPosSet(M506YCamera->splitSprId[i], posX[i], 240);
        espScaleSet(M506YCamera->splitSprId[i], 0.6f, 1);
        espAttrSet(M506YCamera->splitSprId[i], HUSPR_ATTR_NOANIM);
    }
}

void M506YCameraSplitKill(void)
{
    int i;

    for(i=0; i<3; i++) {
        espKill(M506YCamera->splitSprId[i]);
    }
}

void fn_1_AAE0(void)
{
}

void M506YLightInit(void)
{
    Hu3DLighInit();
    M506YLight = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M506_YLIGHT), HU_MEMNUM_OVL);
    if(M506YLight == NULL) {
        OSReport("M506YLightInit Error...\n");
        return;
    }
    M506YLight->hvr.x = 60;
    M506YLight->hvr.y = 50;
    M506YLight->hvr.z = 1000;
    M506YLight->unk10.x = 0;
    M506YLight->unk10.y = 0;
    M506YLight->unk10.z = 0;
    M506YLight->color.r = 232;
    M506YLight->color.g = 232;
    M506YLight->color.b = 232;
    M506YLight->color.a = 255;
    M506YLight->target.x = 0;
    M506YLight->target.y = 20000;
    M506YLight->target.z = -1000;
    M506YLight->center.x = 0;
    M506YLight->center.y = 0;
    M506YLight->center.z = 0;
    M506YLight->pos = M506YLight->target;
    VECSubtract(&M506YLight->center, &M506YLight->target, &M506YLight->dir);
    M506YLight->lightId = Hu3DGLightCreateV(&M506YLight->pos, &M506YLight->dir, &M506YLight->color);
    M506YLightUpdate();
    Hu3DGLightStaticSet(M506YLight->lightId, TRUE);
    Hu3DGLightInfinitytSet(M506YLight->lightId);
}

void M506YLightClose(void)
{
    HuMemDirectFree(M506YLight);
}

void M506YLightUpdate(void)
{
    M506YLight->center.x = M506YLight->unk10.x;
    M506YLight->center.y = M506YLight->unk10.y;
    M506YLight->center.z = M506YLight->unk10.z;
    M506YLight->target.x = M506YLight->center.x+(M506YLight->hvr.z*HuCos(M506YLight->hvr.y)*HuCos(M506YLight->hvr.x));
    M506YLight->target.y = M506YLight->center.y+(M506YLight->hvr.z*HuSin(M506YLight->hvr.y));
    M506YLight->target.z = M506YLight->center.z+(M506YLight->hvr.z*HuCos(M506YLight->hvr.y)*HuSin(M506YLight->hvr.x));
    M506YLight->pos = M506YLight->target;
    VECSubtract(&M506YLight->center, &M506YLight->target, &M506YLight->dir);
    VECNormalize(&M506YLight->dir, &M506YLight->dir);
    Hu3DGLightPosSetV(M506YLight->lightId, &M506YLight->pos, &M506YLight->dir);
    Hu3DGLightColorSet(M506YLight->lightId, M506YLight->color.r, M506YLight->color.g, M506YLight->color.b, M506YLight->color.a);
}

void M506YShadowInit(void)
{
    int i;
    M506_YSHADOW *shadow;

    M506YShadow = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M506_YSHADOW_WORK), HU_MEMNUM_OVL);
    if(M506YShadow == NULL) {
        OSReport("M506YShadowInit Error...\n");
        return;
    }
    Hu3DShadowMultiCreate(30, 20, 30000, M506CameraBit[0]|M506CameraBit[1]|M506CameraBit[2]|M506CameraBit[3]);
    for(i=0; i<M506_PLAYER_MAX; i++) {
        shadow = &M506YShadow->shadow[i];
        shadow->bit = M506CameraBit[i];
        shadow->tpLvl = 0.3f;
        shadow->hvr.x = -70;
        shadow->hvr.y = 50;
        shadow->hvr.z = 2000;
        shadow->center.x = 0;
        shadow->center.y = 0;
        shadow->center.z = 0;
    }
    M506YShadowPosUpdate();
}

void M506YShadowClose(void)
{
    HuMemDirectFree(M506YShadow);
}

void M506YShadowPosUpdate(void)
{
    static HuVecF up = { 0, 1, 0 };
    static HuVecF forward = { 0, 0, 1 };
    int i;
    M506_YSHADOW *shadow;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        shadow = &M506YShadow->shadow[i];
        shadow->target.x = shadow->center.x;
        shadow->target.y = shadow->center.y;
        shadow->target.z = shadow->center.z;
        shadow->pos.x = shadow->target.x+(shadow->hvr.z*HuCos(shadow->hvr.y)*HuCos(shadow->hvr.x));
        shadow->pos.y = shadow->target.y+(shadow->hvr.z*HuSin(shadow->hvr.y));
        shadow->pos.z = shadow->target.z+(shadow->hvr.z*HuCos(shadow->hvr.y)*HuSin(shadow->hvr.x));
        VECSubtract(&shadow->target, &shadow->pos, &shadow->forward);
        VECNormalize(&shadow->forward, &shadow->forward);
        VECCrossProduct(&up, &shadow->forward, &shadow->upDir);
        VECNormalize(&shadow->upDir, &shadow->upDir);
        VECCrossProduct(&shadow->forward, &shadow->upDir, &shadow->up);
        VECNormalize(&shadow->up, &shadow->up);
        Hu3DShadowMultiTPLvlSet(shadow->tpLvl, shadow->bit);
        Hu3DShadowMultiPosSet(&shadow->pos, &shadow->up, &shadow->target, shadow->bit);
    }
}

void M506YShadowUpdate(void)
{
    int i;
    M506_YSHADOW *shadow;

    for(i=0; i<M506_PLAYER_MAX; i++) {
        shadow = &M506YShadow->shadow[i];
        shadow->center.x = M506PlayerObj[i]->trans.x;
        shadow->center.y = M506PlayerObj[i]->trans.y;
        shadow->center.z = M506PlayerObj[i]->trans.z;
    }
    M506YShadowPosUpdate();
}

void M506YCameraViewSet(int cameraNo, int viewNo)
{
    M506_YCAMERA_VIEW *view = &YCameraView[viewNo];
    float *start = view->start;
    M506_YCAMERA *camera = &M506YCamera->camera[cameraNo];

    camera->hvr.x = start[0];
    camera->hvr.y = start[1];
    camera->hvr.z = start[2];
    camera->pos.x = start[3];
    camera->pos.y = start[4];
    camera->pos.z = start[5];
    M506YCameraUpdate();
}

int M506YCameraViewLerp(int cameraNo, int viewNo)
{
    M506_YCAMERA_VIEW *view = &YCameraView[viewNo];
    float *start = view->start;
    float *end = view->end;
    M506_YCAMERA *camera = &M506YCamera->camera[cameraNo];
    int result = 0;
    float time = view->time;

    result += M506PointLerp(&camera->hvr.x, start[0], end[0], time);
    result += M506PointLerp(&camera->hvr.y, start[1], end[1], time);
    result += M506PointLerp(&camera->hvr.z, start[2], end[2], time);
    result += M506PointLerp(&camera->pos.x, start[3], end[3], time);
    result += M506PointLerp(&camera->pos.y, start[4], end[4], time);
    result += M506PointLerp(&camera->pos.z, start[5], end[5], time);
    M506YCameraUpdate();
    return result;
}

int M506PointLerp(float *value, float start, float end, float time)
{
    if(*value == end) {
        return 0;
    }
    *value += (end-start)/time;
    if((start > end && *value < end) || (start < end && *value > end)) {
        *value = end;
        return 0;
    }
    return 1;
}

void M506MakeRotMtx(Mtx mtx, HuVecF *rot)
{
    Mtx rotZ;
    Mtx rotY;
    Mtx rotX;

    MTXRotRad(rotX, 'x', 0.017453292f*rot->x);
    MTXRotRad(rotY, 'y', 0.017453292f*rot->y);
    MTXRotRad(rotZ, 'z', 0.017453292f*rot->z);
    MTXConcat(rotZ, rotX, mtx);
    MTXConcat(mtx, rotY, mtx);
}

void M506SeedUpdate(void)
{
    M506_FLOW *flow = &M506Flow;
    float fallSpeed = 0;

    while(1) {
        switch(flow->seedMode) {
            case 0:
                break;

            case 1:
                SeedInitF = FALSE;
                flow->seedMode = 2;
                break;

            case 2:
                flow->seedTime += 0.016666668f;
                fallSpeed = 3*flow->seedTime;
                flow->seedPosY -= fallSpeed;
                flow->seedRot += 2.1f;
                if(!SeedInitF && flow->seedPosY < 93.5f) {
                    M506ParticleStart(flow);
                    SeedInitF = TRUE;
                }
                if(flow->seedPosY < 13.5f) {
                    flow->seedPosY = 13.5f;
                    SeedInitF = FALSE;
                    flow->seedMode = 3;
                }
                Hu3DModelPosSet(flow->work->seedMdlId, 0, flow->seedPosY, 0);
                Hu3DModelRotSet(flow->work->seedMdlId, flow->seedRot, flow->seedRot, 0);
                break;

            case 3:
                break;
        }
        HuPrcVSleep();
    }
}
