#include "REL/w05sDll.h"

#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/scroll.h"
#include "game/board/opening.h"
#include "game/board/masu.h"
#include "game/board/branch.h"
#include "game/board/player.h"
#include "game/board/window.h"
#include "game/board/com.h"
#include "game/board/status.h"
#include "game/board/camera.h"
#include "game/board/star.h"
#include "game/board/guide.h"
#include "game/board/coin.h"

#include "game/board/capsule.h"

#include "game/wipe.h"
#include "game/mg/timer.h"

#include "datanum/effect.h"

#include "datanum/w05.h"
#include "messnum/board_w05.h"
#include "messnum/board_capmachine.h"

#define MB5EV_MASU_ROCKET MASU_FLAG_BIT_MULTI(0, 2)
#define MB5EV_MASU_WARP MASU_FLAG_BIT(2)
#define MB5EV_MASU_WARP_JUMP MASU_FLAG_BIT(3)

/* Story Mode board 5 data directory; no datanum header exists for it */
#define W05S_FILE(n) DATANUM(DATA_w05s, n)

typedef struct MB5_Work_s {
    int bgMdlId; //0x00
    int areaBaseMdlId; //0x04
    int bgPillarMdlId; //0x08
    int startMdlId; //0x0C
    int rocketPathMdlId[3]; //0x10
    int launchBMdlId[3]; //0x1C
    int rocketMdlId[3]; //0x28
    int warpBaseMdlId[2]; //0x34
    int arrowMdlId[9]; //0x3C
    int warpMdlId[2]; //0x60
    int warpLayerMdlId[2]; //0x68
    int radarBodyMdlId[2]; //0x70
    int treeMdlId[2]; //0x78
    int rocketLightMdlId[2]; //0x80
} MB5_WORK;

// _prolog/_epilog are the REL's entry points, which only the GameCube's
// loader calls; the port loads each module as a shared library and calls
// ObjectSetup directly. _ctors/_dtors come from the CodeWarrior linker
// and do not exist here. Mario Party 4 guards its equivalents the same way.
#ifdef __MWERKS__
typedef void (*VoidFunc)(void);
extern const VoidFunc _ctors[];
extern const VoidFunc _dtors[];

extern void ObjectSetup(void);

int _prolog(void) {
    const VoidFunc* ctors = _ctors;
    while (*ctors != 0) {
        (**ctors)();
        ctors++;
    }
    ObjectSetup();
    return 0;
}

void _epilog(void) {
    const VoidFunc* dtors = _dtors;
    while (*dtors != 0) {
        (**dtors)();
        dtors++;
    }
}
#endif

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
static MB5_WORK mb5_Work;
static MBMODELID unkMdlId;
static MBMODELID numberMdlId[5];
static HuVecF mb5ev_WarpEndSize;
static ANIMDATA *mb5ev_WarpParmanAnim;
static ANIMDATA *mb5ev_RocketDustAnim;
static HU3DPARMANID mb5ev_WarpParmanId;
static HU3DPARMANID mb5ev_RocketDustParmanId[13];
static OMOBJ *mb5_MainObj;

static void MB5_MainObjUpdate(OMOBJ *obj);

void ObjectSetup(void)
{
    GWPartyFSet(FALSE);
    MBObjectSetup(MBNO_WORLD_5, MB5_Create, MB5_Kill);
}

static int numberFileTbl[10] = { DATANUM(DATA_board, 12), DATANUM(DATA_board, 13), DATANUM(DATA_board, 14), DATANUM(DATA_board, 15), DATANUM(DATA_board, 16), DATANUM(DATA_board, 17), DATANUM(DATA_board, 18), DATANUM(DATA_board, 19), DATANUM(DATA_board, 20), DATANUM(DATA_board, 21) };
static HuVecF mb5ev_RocketPosTbl[3] = { { -1086.0f, 750.0f, -811.0f }, { 0.0f, 750.0f, -1185.0f }, { 1086.0f, 750.0f, -811.0f } };
static HuVecF mb5ev_ArrowPosTbl[9] = { { 1000.0f, 325.0f, 2200.0f }, { -1070.0f, 490.0f, 1100.0f }, { 900.0f, 490.0f, 1265.0f }, { -1500.0f, 490.0f, -55.0f }, { -765.0f, 540.0f, -1025.0f }, { 765.0f, 540.0f, -1025.0f }, { 1500.0f, 490.0f, -55.0f }, { -580.0f, 490.0f, 835.0f }, { 900.0f, 490.0f, 340.0f } };
static HuVecF mb5ev_ArrowRotTbl[9] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, -45.0f, 0.0f }, { 0.0f, 45.0f, 0.0f }, { 0.0f, -115.0f, 0.0f }, { 0.0f, -155.0f, 0.0f }, { 0.0f, 155.0f, 0.0f }, { 0.0f, 115.0f, 0.0f }, { 0.0f, -135.0f, 0.0f }, { 0.0f, 180.0f, 0.0f } };
static HuVecF mb5ev_WarpTogePosTbl[2] = { { -1860.0f, 505.0f, 550.0f }, { 1860.0f, 505.0f, 550.0f } };
static HuVecF mb5ev_RaderBdyPosTbl[2] = { { -1800.0f, 320.0f, 1390.0f }, { 1800.0f, 320.0f, 1390.0f } };
static HuVecF mb5ev_RaderBdyRotTbl[2] = { { 0.0f, 45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f } };
static HuVecF mb5ev_Tree2PosTbl[2] = { { -1180.0f, 320.0f, 2000.0f }, { 1180.0f, 320.0f, 2000.0f } };
static HuVecF mb5ev_Tree2RotTbl[2] = { { 0.0f, -45.0f, 0.0f }, { 0.0f, 45.0f, 0.0f } };
static HuVecF mb5ev_RokPLPosTbl[2] = { { -1400.0f, 615.0f, -515.0f }, { 1400.0f, 615.0f, -515.0f } };
static HuVecF mb5ev_RokPLRotTbl[2] = { { 0.0f, 45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f } };
static HuVecF mb5ev_WarpPosTbl[2] = { { -1860.0f, 315.0f, 550.0f }, { 1860.0f, 315.0f, 550.0f } };
static HuVecF mb5ev_LaunchBPosTbl[3] = { { -800.0f, 700.0f, -525.0f }, { 0.0f, 700.0f, -780.0f }, { 800.0f, 700.0f, -525.0f } };
static HuVecF mb5ev_LaunchBRotTbl[3] = { { 0.0f, 45.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -45.0f, 0.0f } };

void MB5_Create(void)
{
    HuVecF openingRot = { -33, 0, 0 };
    HuVecF openingPos = { 0, 1000, 1850 };
    HuVecF mapRot = { -78, 0, 0 };
    HuVecF mapPos = { 100, -150, 700 };
    int boardNo = MBBoardNoGet();
    int i;
    int mdlId;
    for(i=0; i<5; i++) {
        numberMdlId[i] = MBModelCreate(numberFileTbl[i], NULL, FALSE);
        MBModelDispSet(numberMdlId[i], FALSE);
    }
    MBMasuCreate(W05S_FILE(0));
    MBScrollInit(W05S_FILE(0x13), 20000, 0);
    MBLightHookSet(MB5_LightSet, MB5_LightReset);
    MBCapsuleColCreate(W05S_FILE(0x14));
    MBMasuPathCheckHookSet(MB5_MasuPathCheck);
    mb5_Work.bgMdlId = MBModelCreate(W05S_FILE(1), NULL, FALSE);
    mb5_Work.areaBaseMdlId = mdlId = MBModelCreate(W05S_FILE(3), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb5_Work.bgPillarMdlId = mdlId = MBModelCreate(W05S_FILE(2), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb5_Work.startMdlId = mdlId = MBModelCreate(W05S_FILE(4), NULL, FALSE);
    MBMotionSpeedSet(mdlId, 1);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    for(i=0; i<3; i++) {
        mb5_Work.launchBMdlId[i] = mdlId = MBModelCreate(W05S_FILE(8), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb5ev_LaunchBPosTbl[i]);
        MBModelRotSetV(mdlId, &mb5ev_LaunchBRotTbl[i]);
        MBMotionSpeedSet(mdlId, 0);
    }
    for(i=0; i<3; i++) {
        mb5_Work.rocketPathMdlId[i] = mdlId = MBModelCreate(W05S_FILE(9)+i, NULL, FALSE);
        MBMotionSpeedSet(mdlId, 0);
    }
    for(i=0; i<3; i++) {
        mb5_Work.rocketMdlId[i] = mdlId = MBModelCreate(W05S_FILE(12)+i, NULL, FALSE);
        MBMotionSpeedSet(mdlId, 0);
        MBModelPosSetV(mdlId, &mb5ev_RocketPosTbl[i]);
        if(i != 1) {
            MBModelDispSet(mdlId, FALSE);
        }
    }
    for(i=0; i<2; i++) {
        mb5_Work.warpBaseMdlId[i] = mdlId = MBModelCreate(W05S_FILE(15), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb5ev_WarpPosTbl[i]);
        MBMotionSpeedSet(mdlId, 1);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<2; i++) {
        mb5_Work.warpMdlId[i] = mdlId = MBModelCreate(W05S_FILE(18), NULL, TRUE);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBMotionSpeedSet(mdlId, 1);
        MBModelPosSetV(mdlId, &mb5ev_WarpTogePosTbl[i]);
        MBModelDispSet(mdlId, FALSE);
    }
    for(i=0; i<2; i++) {
        mb5_Work.warpLayerMdlId[i] = mdlId = MBModelCreate(W05S_FILE(17), NULL, TRUE);
        MBMotionSpeedSet(mdlId, 0);
        MBModelPosSetV(mdlId, &mb5ev_WarpTogePosTbl[i]);
        MBModelDispSet(mdlId, FALSE);
    }
    for(i=0; i<2; i++) {
        mb5_Work.radarBodyMdlId[i] = mdlId = MBModelCreate(W05S_FILE(5), NULL, TRUE);
        MBModelRotSetV(mdlId, &mb5ev_RaderBdyRotTbl[i]);
        MBModelPosSetV(mdlId, &mb5ev_RaderBdyPosTbl[i]);
        MBMotionSpeedSet(mdlId, 1);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<2; i++) {
        mb5_Work.treeMdlId[i] = mdlId = MBModelCreate(W05S_FILE(6), NULL, TRUE);
        MBModelRotSetV(mdlId, &mb5ev_Tree2RotTbl[i]);
        MBModelPosSetV(mdlId, &mb5ev_Tree2PosTbl[i]);
        MBMotionSpeedSet(mdlId, 1);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<2; i++) {
        mb5_Work.rocketLightMdlId[i] = mdlId = MBModelCreate(W05S_FILE(7), NULL, TRUE);
        MBModelRotSetV(mdlId, &mb5ev_RokPLRotTbl[i]);
        MBModelPosSetV(mdlId, &mb5ev_RokPLPosTbl[i]);
        MBMotionSpeedSet(mdlId, 1);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<9; i++) {
        mb5_Work.arrowMdlId[i] = mdlId = MBModelCreate(W05S_FILE(16), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb5ev_ArrowPosTbl[i]);
        MBModelRotSetV(mdlId, &mb5ev_ArrowRotTbl[i]);
        MBMotionSpeedSet(mdlId, 1);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    MBBranchFlagSet(MB5EV_MASU_WARP_JUMP);
    HuDataDirClose(DATA_w05s);
    MBMasuWalkPreHookSet(MB5Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB5Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB5Ev_MasuHatena);
    MBOpeningViewSet(&openingRot, &openingPos, 9000);
    MBMapViewCameraSet(&mapRot, &mapPos, 12300);
    HuAudSndGrpSetSet(MSM_GRP_BD5);
    mb5_MainObj = MBAddObj(32768, 0, 0, MB5_MainObjUpdate);
}

void MB5_Kill(void)
{
    int i;
    if(unkMdlId >= 0) {
        MBModelKill(unkMdlId);
        unkMdlId = MB_MODEL_NONE;
    }
    for(i=0; i<9; i++) {
        if(mb5_Work.arrowMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.arrowMdlId[i]);
        }
    }
    for(i=0; i<2; i++) {
        if(mb5_Work.warpMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.warpMdlId[i]);
        }
        if(mb5_Work.warpLayerMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.warpLayerMdlId[i]);
        }
    }
    for(i=0; i<3; i++) {
        if(mb5_Work.launchBMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.launchBMdlId[i]);
        }
        if(mb5_Work.rocketPathMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.rocketPathMdlId[i]);
        }
        if(mb5_Work.rocketMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.rocketMdlId[i]);
        }
    }
    if(mb5_Work.areaBaseMdlId != MB_MODEL_NONE) {
        MBModelKill(mb5_Work.areaBaseMdlId);
    }
    for(i=0; i<2; i++) {
        if(mb5_Work.warpBaseMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.warpBaseMdlId[i]);
        }
        if(mb5_Work.radarBodyMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.radarBodyMdlId[i]);
        }
        if(mb5_Work.treeMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.treeMdlId[i]);
        }
        if(mb5_Work.rocketLightMdlId[i] != MB_MODEL_NONE) {
            MBModelKill(mb5_Work.rocketLightMdlId[i]);
        }
    }
    if(mb5_Work.bgMdlId != MB_MODEL_NONE) {
        MBModelKill(mb5_Work.bgMdlId);
    }
    if(mb5_Work.bgPillarMdlId != MB_MODEL_NONE) {
        MBModelKill(mb5_Work.bgPillarMdlId);
    }
    if(mb5_Work.startMdlId != MB_MODEL_NONE) {
        MBModelKill(mb5_Work.startMdlId);
    }
    mb5_MainObj = NULL;
    for(i=0; i<5; i++) {
        if(numberMdlId[i] >= 0) {
            MBModelKill(numberMdlId[i]);
            numberMdlId[i] = MB_MODEL_NONE;
        }
    }
}

static void MB5_MainObjUpdate(OMOBJ *obj)
{
    if(MBKillCheck() || mb5_MainObj == NULL) {
        omDelObj(mbObjMan, obj);
        mb5_MainObj = NULL;
        return;
    }
}

void MB5_LightSet(void)
{
    HuVecF pos;
    HuVecF dir;
    GXColor color;
    int gLightId;
    
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(255, 255, 255);
    pos.x = -2700;
    pos.y = 4700;
    pos.z = 2300;
    dir.x = 2700;
    dir.y = -4700;
    dir.z = -2300;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    gLightId = Hu3DGLightCreate(pos.x, pos.y, pos.z, dir.x, dir.y, dir.z, color.r, color.g, color.b);
    Hu3DGLightInfinitytSet(gLightId);
}

void MB5_LightReset(void)
{
    
}

void MB5Ev_Warp(int playerNo);
void MB5Ev_Rocket(int playerNo);

int MB5Ev_MasuHatena(int playerNo)
{
    s16 masuId = GwPlayer[playerNo].masuId;
    MASU *masuP = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    u32 flag = masuP->flag & MASU_FLAG_MAP;
    if(flag & MB5EV_MASU_WARP) {
        MB5Ev_Warp(playerNo);
    }
    if(flag & MB5EV_MASU_ROCKET) {
        u32 no = flag & MB5EV_MASU_ROCKET;
        if(no == 2) {
            MB5Ev_Rocket(playerNo);
        }
    }
}

int MB5_MasuStub()
{
    return FALSE;
}

int MB5Ev_MasuWalkPre(int playerNo)
{
    return FALSE;
}

int MB5Ev_MasuWalkPost(int playerNo)
{
    s16 masuId = GwPlayer[playerNo].masuId;
    MASU *masuP = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    u32 flag = masuP->flag & MASU_FLAG_MAP;
    int type = MBMasuTypeGet(MASU_LAYER_DEFAULT, masuId);
    return FALSE;
}

void MB5Ev_WarpParticleCreate(HuVecF pos);
void MB5Ev_WarpPlayerShrink(int playerNo);
void MB5Ev_WarpPlayerGrow(int playerNo);

void MB5Ev_Warp(int playerNo)
{
    int i; //r31
    int j; //r29
    s16 masuId; //r27
    s16 nextMasuId; //r28
    MASU *masuP; //r26
    
    float speed; //f31
    float scaleSpeed; //f30
    
    int choice; //sp+0x14
    HuVecF playerPos; //sp+0x48
    HuVecF destPos; //sp+0x3C
    HuVecF scale; //sp+0x30
    u32 flag; //sp+0x10
    s16 jumpMasuId[2]; //sp+0xC
    BOOL acceptF; //sp+0x8
    
    choice = 0;
    acceptF = FALSE;
    masuId = GwPlayer[playerNo].masuId;
    masuP = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masuP->flag & MASU_FLAG_MAP;
    MBPlayerPosFixFlagSet(FALSE);
    MBPlayerMotionNoShiftSet(playerNo, MB_PLAYER_MOT_IDLE, 0, 8, HU3D_MOTATTR_LOOP);
    HuPrcSleep(10);
    HuPrcSleep(10);
    jumpMasuId[0] = MBMasuFlagMatchFindLink(MASU_LAYER_DEFAULT, masuId, MB5EV_MASU_WARP_JUMP);
    GwPlayer[playerNo].masuIdPrev = GwPlayer[playerNo].masuId;
    GwPlayer[playerNo].masuIdNext = jumpMasuId[0];
    MBPlayerMasuWalk(playerNo, TRUE);
    GwPlayer[playerNo].masuId = jumpMasuId[0];
    HuPrcSleep(10);
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    HuPrcSleep(5);
    MBCameraPlayerViewSet(playerNo, NULL, NULL, 3200, -1, 30);
    MBCameraMotionWait();
    HuPrcSleep(30);
    omVibrate(playerNo, 120, 6, 6);
    MBPlayerPosGet(playerNo, &playerPos);
    MB5Ev_WarpParticleCreate(playerPos);
    scale.x = scale.z  = 1;
    scale.y = 0;
    scaleSpeed = 0.01f;
    for(i=0; i<2; i++) {
        MBModelDispSet(mb5_Work.warpMdlId[i], TRUE);
    }
    for(i=0, speed=1; i<90; i++) {
        speed += 0.3f;
        if((scale.y += scaleSpeed) >= 1) {
            scale.y = 1;
        }
        for(j=0; j<2; j++) {
            MBMotionSpeedSet(mb5_Work.warpMdlId[j], speed);
            MBModelScaleSetV(mb5_Work.warpMdlId[j], &scale);
        }
        if(i == 20) {
            HuAudFXPlay(MSM_SE_BD5_09);
        }
        HuPrcVSleep();
    }
    scale.y = 1;
    for(i=0; i<2; i++) {
        MBModelDispSet(mb5_Work.warpMdlId[i], FALSE);
        MBModelDispSet(mb5_Work.warpLayerMdlId[i], TRUE);
        MBMotionSpeedSet(mb5_Work.warpLayerMdlId[i], 1.1f);
        MBMotionTimeSet(mb5_Work.warpLayerMdlId[i], 0);
    }
    MB5Ev_WarpPlayerShrink(playerNo);
    HuPrcSleep(90);
    Hu3DParManKill(mb5ev_WarpParmanId);
    HuSprAnimKill(mb5ev_WarpParmanAnim);
    mb5ev_WarpParmanAnim = NULL;
    jumpMasuId[1] = MBMasuFlagMatchFindLink(MASU_LAYER_DEFAULT, jumpMasuId[0], MB5EV_MASU_WARP_JUMP);
    MBMasuPosGet(MASU_LAYER_DEFAULT, jumpMasuId[1], &destPos);
    MBPlayerPosSetV(playerNo, &destPos);
    MBCameraPlayerViewSet(playerNo, NULL, NULL, -1, -1, 60);
    MBCameraMotionWait();
    MBPlayerRotateStart(playerNo, 0, 1);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, MB_PLAYER_MOT_IDLE, 0, 8, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    MB5Ev_WarpParticleCreate(destPos);
    omVibrate(playerNo, 120, 6, 6);
    for(i=0; i<70; i++) {
        if(i == 40) {
            HuAudFXPlay(MSM_SE_BD5_10);
        }
        HuPrcVSleep();
    }
    HuPrcSleep(10);
    for(i=0; i<2; i++) {
        MBModelAttrSet(mb5_Work.warpLayerMdlId[i], HU3D_MOTATTR_REV);
        MBMotionSpeedSet(mb5_Work.warpLayerMdlId[i], 1.1f);
    }
    MB5Ev_WarpPlayerGrow(playerNo);
    HuPrcSleep(10);
    for(i=0; i<2; i++) {
        MBModelAttrReset(mb5_Work.warpLayerMdlId[i], HU3D_MOTATTR_REV);
        MBMotionSpeedSet(mb5_Work.warpLayerMdlId[i], 0);
        MBMotionTimeSet(mb5_Work.warpLayerMdlId[i], 0);
        MBModelDispSet(mb5_Work.warpLayerMdlId[i], FALSE);
        MBModelDispSet(mb5_Work.warpMdlId[i], TRUE);
        MBMotionSpeedSet(mb5_Work.warpMdlId[i], speed);
        MBModelAttrSet(mb5_Work.warpMdlId[i], HU3D_MOTATTR_REV);
    }
    scale.y -= 0.05f;
    for(i=0; i<60.0f; i++) {
        speed -= 0.2f;
        if((scale.y -= scaleSpeed*2) <= 0) {
            scale.y = 0;
        }
        for(j=0; j<2; j++) {
            MBMotionSpeedSet(mb5_Work.warpMdlId[j], speed);
            MBModelScaleSetV(mb5_Work.warpMdlId[j], &scale);
        }
        HuPrcVSleep();
    }
    MBCameraPlayerViewSet(playerNo, NULL, NULL, -1, -1, 6);
    MBCameraMotionWait();
    nextMasuId = MBMasuFlagMatchFindLink(MASU_LAYER_DEFAULT, jumpMasuId[1], MB5EV_MASU_WARP);
    MBPlayerPosFixCurr(nextMasuId, FALSE);
    GwPlayer[playerNo].masuIdPrev = jumpMasuId[1];
    GwPlayer[playerNo].masuIdNext = nextMasuId;
    MBPlayerMasuWalk(playerNo, TRUE);
    GwPlayer[playerNo].masuId = nextMasuId;
    MBCameraSkipSet(TRUE);
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    Hu3DParManKill(mb5ev_WarpParmanId);
    HuSprAnimKill(mb5ev_WarpParmanAnim);
    mb5ev_WarpParmanAnim = NULL;
    for(i=0; i<2; i++) {
        MBModelAttrReset(mb5_Work.warpMdlId[i], HU3D_MOTATTR_REV);
    }
    MBPlayerPosFixFlagSet(TRUE);
}

void MB5Ev_RocketDustCreate(HuVecF pos);
u32 MB5_EventMasuFlagGet(int no, u32 flag);

void MB5Ev_Rocket(int playerNo)
{
    s16 no; //r31
    s16 i; //r30
    s16 j; //r28
    s16 countdownNum; //r27
    s16 overlapNum; //r25
    s16 masuId; //r24
    MASU *rocketMasuP; //r26
    int seNo1; //r23
    int seNo2; //r22
    s16 numTime; //r21
    s16 numAlpha; //r20
    int playerMdlId; //r19
    int pathMdlId; //r18
    s16 rocketMasuId; //r17
    u32 flagNo;
    
    
    float time; //f31
    float numScale; //f30
    float t; //f29
    float startTime; //f28
    float dustTime; //f27
    float numScaleSpeed; //f26
    
    HuVecF overlapPos[GW_PLAYER_MAX]; //sp+0x104
    Mtx hookMtx; //sp+0xD4
    Mtx masuMtx; //sp+0xA4
    HuVecF playerPos; //sp+0x98
    HuVecF pos; //sp+0x8C
    HuVecF rocketPos; //sp+0x80
    HuVecF cameraRot; //sp+0x74
    HuVecF cameraPos; //sp+0x68
    HuVecF startPos; //sp+0x5C
    
    HuVecF rocketMasuPos; //sp+0x50
    
    s16 overlapPlayer[GW_PLAYER_MAX]; //sp+0x30
    int rocketMdlId; //sp+0x2C
    float zoom; //sp+0x28
    u32 flag; //sp+0x24
    MASU *masuP; //sp+0x1C
    MASU *rocketBaseMasuP; //sp+0x18
    MBCAMERA *cameraP; //sp+0x14
    s16 numAlphaSpeed; //sp+0x8
    
    static HuVecF rocketEndPos[3] = {
        { -1086, 750, -811 },
        { 0, 750, -1185 },
        { 1086, 750, -811 }
    };
    static char *rocketHookTbl[3] = {
        "rockRhook",
        "rockGhook",
        "rockBhook"
    };
    static HuVecF rocketStartPos[3] = {
        { -1086, 1180, -811 },
        { 0, 1180, -1185 },
        { 1086, 1180, -811 }
    };
    static playerRotTbl[3] = { 45, 0, -45 };
    
    cameraP = MBCameraGet();
    masuId = GwPlayer[playerNo].masuId;
    masuP = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masuP->flag & MASU_FLAG_MAP;
    flagNo = flag & MB5EV_MASU_ROCKET;
    MBPlayerPosFixFlagSet(FALSE);
    countdownNum = 3;
    numAlphaSpeed = 4;
    numScaleSpeed = 1.0f/60.0f;
    switch(flagNo) {
        case 1:
            MBPlayerRotateStart(playerNo, 225, 15);
            while(!MBPlayerRotateCheck(playerNo)) {
                HuPrcVSleep();
            }
            break;
            
        case 2:
            MBPlayerRotateStart(playerNo, 180, 15);
            while(!MBPlayerRotateCheck(playerNo)) {
                HuPrcVSleep();
            }
            break;
        
        case 3:
            MBPlayerRotateStart(playerNo, 135, 15);
            while(!MBPlayerRotateCheck(playerNo)) {
                HuPrcVSleep();
            }
            break;
    }
    no = flagNo-1;
    MBPlayerPosGet(playerNo, &startPos);
    for(i=overlapNum=0; i<GW_PLAYER_MAX; i++) {
        if(i != playerNo && MBPlayerAliveCheck(i) && masuId == GwPlayer[i].masuId) {
            overlapPlayer[overlapNum] = i;
            MBPlayerPosGet(i, &overlapPos[i]);
            overlapNum++;
        }
    }
    MBWinCreate(MBWIN_TYPE_RESULT, MESS_BOARD_W05_ROCKET_START, HUWIN_SPEAKER_NONE);
    MBTopWinWait();
    MBTopWinKill();
    MBCameraPlayerViewSet(playerNo, NULL, NULL, 3200, -1, 30);
    MBCameraMotionWait();
    pathMdlId = MBModelIdGet(mb5_Work.rocketPathMdlId[no]);
    MBMotionSpeedSet(mb5_Work.rocketPathMdlId[no], 1);
    MBMotionTimeSet(mb5_Work.rocketPathMdlId[no], 1);
    MBMotionSpeedSet(mb5_Work.launchBMdlId[no], 1);
    MBMotionTimeSet(mb5_Work.launchBMdlId[no], 1);
    rocketMdlId = MBModelIdGet(mb5_Work.rocketMdlId[no]);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 1);
    MBMotionTimeSet(mb5_Work.rocketMdlId[no], 0);
    playerMdlId = MBPlayerModelGet(playerNo);
    seNo1 = HuAudFXPlay(MSM_SE_BD5_15);
    for(i=0; i<80; i++) {
        Hu3DModelObjMtxGet(pathMdlId, rocketHookTbl[no], hookMtx);
        MTXTransApply(hookMtx, masuMtx, 0, 3, 0);
        MBMasuMtxSet(masuId, masuMtx);
        MBPlayerPosSet(playerNo, hookMtx[0][3], hookMtx[1][3], hookMtx[2][3]);
        for(j=0; j<overlapNum; j++) {
            MBPlayerPosGet(overlapPlayer[j], &overlapPos[j]);
            overlapPos[j].x += hookMtx[0][3]-startPos.x;
            overlapPos[j].y += hookMtx[1][3]-startPos.y;
            overlapPos[j].z += hookMtx[2][3]-startPos.z;
            MBPlayerPosSetV(overlapPlayer[j], &overlapPos[j]);
        }
        startPos.x = hookMtx[0][3];
        startPos.y = hookMtx[1][3];
        startPos.z = hookMtx[2][3];
        HuPrcVSleep();
    }
    HuAudFXStop(seNo1);
    seNo1 = MSM_SENO_NONE;
    HuAudFXPlay(MSM_SE_BD5_16);
    HuPrcSleep(10);
    MBPlayerPosGet(playerNo, &playerPos);
    rocketPos = rocketStartPos[no];
    HuAudFXPlay(MSM_SE_BD5_01);
    HuPrcSleep(30);
    MBPlayerMotionNoShiftSet(playerNo, MB_PLAYER_MOT_WALK, 0, 8, HU3D_MOTATTR_LOOP);
    for(i=0; i<60.0f; i++) {
        if(MBMotionTimeGet(mb5_Work.rocketMdlId[no]) >= 150) {
            MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 0);
        }
        t = i/60.0f;
        pos.x = playerPos.x+((rocketPos.x-playerPos.x)*t);
        pos.y = playerPos.y+((rocketPos.y-playerPos.y)*t);
        pos.z = playerPos.z+((rocketPos.z-playerPos.z)*t);
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    MBPlayerRotateStart(playerNo, playerRotTbl[no], 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, MB_PLAYER_MOT_IDLE, 0, 8, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 1);
    while(1) {
        time = MBMotionTimeGet(mb5_Work.rocketMdlId[no]);
        if(time >= 200) {
            MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 0);
            break;
        }
        if(time == 160) {
            HuAudFXPlay(MSM_SE_BD5_01);
        } else if(time  == 190) {
            HuAudFXPlay(MSM_SE_BD5_13);
        }
        HuPrcVSleep();
    }
    MBModelAttrSet(mb5_Work.launchBMdlId[no], HU3D_MOTATTR_REV);
    MBMotionSpeedSet(mb5_Work.launchBMdlId[no], 1.3f);
    MBModelAttrSet(mb5_Work.rocketPathMdlId[no], HU3D_MOTATTR_REV);
    MBMotionSpeedSet(mb5_Work.rocketPathMdlId[no], 1.3f);
    while(1) {
        time = MBMotionTimeGet(mb5_Work.launchBMdlId[no]);
        if(time > 0) {
            Hu3DModelObjMtxGet(pathMdlId, rocketHookTbl[no], hookMtx);
            MTXTransApply(hookMtx, masuMtx, 0, -3, 0);
            MBMasuMtxSet(masuId, masuMtx);
            for(j=0; j<overlapNum; j++) {
                MBPlayerPosGet(overlapPlayer[j], &overlapPos[j]);
                overlapPos[j].x += hookMtx[0][3]-startPos.x;
                overlapPos[j].y += hookMtx[1][3]-startPos.y;
                overlapPos[j].z += hookMtx[2][3]-startPos.z;
                MBPlayerPosSetV(overlapPlayer[j], &overlapPos[j]);
            }
            startPos.x = hookMtx[0][3];
            startPos.y = hookMtx[1][3];
            startPos.z = hookMtx[2][3];
            if(time <= 80) {
                if(seNo1 == MSM_SENO_NONE) {
                    seNo1 = HuAudFXPlay(MSM_SE_BD5_15);
                }
            }
        } else {
            HuAudFXStop(seNo1);
            HuAudFXPlay(MSM_SE_BD5_16);
            break;
        }
        HuPrcVSleep();
    }
    HuPrcSleep(40);
    pos.y += 170;
    pos.z += 200;
    while(1) {
        HuAudFXPlay(MSM_SE_BD5_17);
        MBModelDispSet(numberMdlId[countdownNum], TRUE);
        MBModelRotSet(numberMdlId[countdownNum], -33, 0, 0);
        MBModelPosSetV(numberMdlId[countdownNum], &pos);
        MBModelScaleSet(numberMdlId[countdownNum], 1.5f, 1.5f, 1.5f);
        MBModelAlphaSet(numberMdlId[countdownNum], 255);
        for(numTime=0, numScale=1.5f, numAlpha=255; numTime<=60; numTime++) {
            numScale += numScaleSpeed;
            numAlpha -= numAlphaSpeed;
            MBModelScaleSet(numberMdlId[countdownNum], numScale, numScale, numScale);
            MBModelAlphaSet(numberMdlId[countdownNum], numAlpha);
            HuPrcVSleep();
        }
        MBModelDispSet(numberMdlId[countdownNum], FALSE);
        countdownNum--;
        HuPrcSleep(5);
        if(countdownNum <= 0) {
            break;
        }
        HuPrcVSleep();
    }
    MBModelDispSet(playerMdlId, FALSE);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 1);
    seNo2 = HuAudFXPlay(MSM_SE_BD5_02);
    MBPlayerPosGet(playerNo, &startPos);
    startPos.y -= 400;
    MB5Ev_RocketDustCreate(startPos);
    omVibrate(playerNo, 160, 4, 2);
    HuPrcSleep(180);
    HuAudFXStop(seNo2);
    startTime = MBMotionTimeGet(mb5_Work.rocketMdlId[no]);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 0);
    MBModelDispSet(mb5_Work.rocketMdlId[no], FALSE);
    rocketMasuId = MBMasuFlagFind(MASU_LAYER_DEFAULT, 0x10, 0x10);
    MBMasuPosGet(MASU_LAYER_DEFAULT, rocketMasuId, &pos);
    zoom = MBCameraZoomGet();
    MBCameraSkipSet(FALSE);
    MBCameraViewNoSet(GwSystem.turnPlayerNo, MB_CAMERA_VIEW_WALK);
    MBCameraMotionWait();
    MBStarScrollCreate(&playerPos, &pos, 180);
    MBCameraSkipSet(FALSE);
    MBCameraMotionWait();
    MBCameraSkipSet(TRUE);
    MBStarScrollStart();
    while(!MBStarScrollDoneCheck()) {
        HuPrcVSleep();
    }
    for(i=0; i<13; i++) {
        Hu3DParManKill(mb5ev_RocketDustParmanId[i]);
        mb5ev_RocketDustParmanId[i] = HU3D_PARMANID_NONE;
    }
    mb5ev_RocketDustAnim = NULL;
    MBModelPosSet(playerMdlId, pos.x, pos.y+430, pos.z);
    MBCameraRotGet(&cameraRot);
    cameraRot.x += 15;
    MBCameraPosTargetGet(&cameraPos);
    MBCameraPlayerViewSet(playerNo, &cameraRot, NULL, 3400, -1, 150);
    MBModelRotSet(mb5_Work.rocketMdlId[no], 0, -playerRotTbl[no], 0);
    MBModelDispSet(mb5_Work.rocketMdlId[no], TRUE);
    MBModelPosSetV(mb5_Work.rocketMdlId[no], &pos);
    MBModelAttrSet(mb5_Work.rocketMdlId[no], HU3D_MOTATTR_REV);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 1);
    seNo2 = HuAudFXPlay(MSM_SE_BD5_03);
    omVibrate(playerNo, 160, 4, 2);
    while(1) {
        dustTime = MBMotionTimeGet(mb5_Work.rocketMdlId[no]);
        if(dustTime <= 210) {
            break;
        }
        if(280.0f == dustTime) {
            HuAudFXFadeOut(seNo2, 2500);
        }
        if(fabs(startTime-dustTime) >= 60 && -1 != startTime) {
            MB5Ev_RocketDustCreate(pos);
            startTime = -1;
        }
        cameraPos.y += 5;
        MBCameraPosSetV(&cameraPos);
        HuPrcVSleep();
    }
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 0);
    MBWinCreate(MBWIN_TYPE_RESULT, MESS_BOARD_W05_ROCKET_END, HUWIN_SPEAKER_NONE);
    MBTopWinWait();
    MBTopWinKill();
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    WipeWait();
    MBModelDispSet(mb5_Work.rocketMdlId[no], FALSE);
    MBStarScrollKill();
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    rocketBaseMasuP = MBMasuGet(MASU_LAYER_DEFAULT, rocketMasuId);
    rocketMasuP = MBMasuGet(MASU_LAYER_DEFAULT, rocketBaseMasuP->linkTbl[0]);
    MBMasuPosGet(MASU_LAYER_DEFAULT, rocketMasuP->linkTbl[0], &rocketMasuPos);
    MBPlayerPosSetV(playerNo, &rocketMasuPos);
    GwPlayer[playerNo].masuId = rocketMasuP->linkTbl[0];
    MBPlayerPosFixCurr(rocketMasuP->linkTbl[0], TRUE);
    MBPlayerRotateStart(playerNo, 0, 1);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, MB_PLAYER_MOT_IDLE, 0, 8, HU3D_MOTATTR_LOOP);
    MBCameraSkipSet(FALSE);
    MBCameraViewNoSet(GwSystem.turnPlayerNo, MB_CAMERA_VIEW_ZOOMOUT);
    MBCameraMotionWait();
    MBCameraSkipSet(TRUE);
    MBCameraZoomSet(2200);
    MBModelDispSet(playerMdlId, TRUE);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        MBCameraSkipSet(FALSE);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    MBMasuMtxSet(masuId, NULL);
    MBModelAttrReset(mb5_Work.launchBMdlId[no], HU3D_MOTATTR_REV);
    MBMotionSpeedSet(mb5_Work.launchBMdlId[no], 0);
    MBMotionTimeSet(mb5_Work.launchBMdlId[no], 0);
    MBModelAttrReset(mb5_Work.rocketPathMdlId[no], HU3D_MOTATTR_REV);
    MBMotionSpeedSet(mb5_Work.rocketPathMdlId[no], 0);
    MBMotionTimeSet(mb5_Work.rocketPathMdlId[no], 0);
    MBMotionSpeedSet(mb5_Work.rocketMdlId[no], 0);
    MBMotionTimeSet(mb5_Work.rocketMdlId[no], 0);
    MBModelPosSetV(mb5_Work.rocketMdlId[no], &rocketEndPos[no]);
    MBModelRotSet(mb5_Work.rocketMdlId[no], 0, 0, 0);
    MBModelAttrReset(mb5_Work.rocketMdlId[no], HU3D_MOTATTR_REV);
    MBModelDispSet(mb5_Work.rocketMdlId[no], TRUE);
    for(i=0; i<13; i++) {
        Hu3DParManKill(mb5ev_RocketDustParmanId[i]);
        mb5ev_RocketDustParmanId[i] = HU3D_PARMANID_NONE;
    }
    mb5ev_RocketDustAnim = NULL;
    HuAudFXStop(seNo2);
    seNo2 = MSM_SENO_NONE;
    MBPlayerPosFixFlagSet(TRUE);
}

HuVecF lbl_1_data_2AC[3] = { { 30.0f, 45.0f, 0.0f }, { 30.0f, 0.0f, 0.0f }, { 30.0f, -45.0f, 0.0f } };

static HU3DPARMANPARAM mb5ev_WarpEffParam = {
    70,
    0,
    1.5f,
    150,
    90,
    { 0, 0.15f, 0 },
    1.0f,
    1.0f,
    16.0f,
    1.0f,
    1,
    {
        { 255, 255, 255, 255 },
    },
    {
        { 255, 255, 255, 0 },
    },
};

void MB5Ev_WarpParticleCreate(HuVecF pos)
{
    void *animFile;
    animFile = HuDataReadNum(EFFECT_ANM_circle, HU_MEMNUM_OVL);
    mb5ev_WarpParmanAnim = HuSprAnimRead(animFile);
    HuDataDirClose(DATA_effect);
    mb5ev_WarpParmanId = Hu3DParManCreate(mb5ev_WarpParmanAnim, 256, &mb5ev_WarpEffParam);
    Hu3DParManAttrSet(mb5ev_WarpParmanId, HU3D_PARMAN_ATTR_RANDSCALE70|HU3D_PARMAN_ATTR_RANDANGLE);
    Hu3DParManRotSet(mb5ev_WarpParmanId, 0, 90, 0);
    Hu3DParManPosSet(mb5ev_WarpParmanId, pos.x, pos.y, pos.z);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(mb5ev_WarpParmanId), 5);
    Hu3DParManTimeLimitSet(mb5ev_WarpParmanId, 120);
}

static HU3DPARMANPARAM mb5ev_RocketDustEffParam = {
    30,
    0,
    1.0f,
    180,
    0,
    { 0, -0.2f, 0 },
    10.0f,
    0.8f,
    200.0f,
    1.0f,
    4,
    {
        { 255, 255, 255, 80 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
    {
        { 255, 255, 255, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
    },
};

void MB5Ev_RocketDustCreate(HuVecF pos)
{
    int i;
    void *animFile;
    animFile = HuDataReadNum(EFFECT_ANM_landDust, HU_MEMNUM_OVL);
    mb5ev_RocketDustAnim = HuSprAnimRead(animFile);
    HuDataDirClose(DATA_effect);
    mb5ev_RocketDustParmanId[0] = Hu3DParManCreate(mb5ev_RocketDustAnim, 128, &mb5ev_RocketDustEffParam);
    Hu3DParManRotSet(mb5ev_RocketDustParmanId[0], 0, 0, 0);
    Hu3DParManPosSet(mb5ev_RocketDustParmanId[0], pos.x, pos.y, pos.z);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(mb5ev_RocketDustParmanId[0]), 5);
    Hu3DParManTimeLimitSet(mb5ev_RocketDustParmanId[0], 90);
    for(i=1; i<13; i++) {
        mb5ev_RocketDustParmanId[i] = Hu3DParManCreate(mb5ev_RocketDustAnim, 128, &mb5ev_RocketDustEffParam);
        Hu3DParManRotSet(mb5ev_RocketDustParmanId[i], 0, 30.0f*i, 0);
        Hu3DParManPosSet(mb5ev_RocketDustParmanId[i], pos.x, pos.y, pos.z);
        Hu3DModelLayerSet(Hu3DParManModelIDGet(mb5ev_RocketDustParmanId[i]), 5);
        Hu3DParManTimeLimitSet(mb5ev_RocketDustParmanId[i], 90);
    }
}

void MB5Ev_WarpPlayerShrink(int playerNo)
{
    HuVecF scale = { 1, 1, 1 };
    float alpha = 255;
    MBMODELID mdlId = MBPlayerModelGet(playerNo);
    float speed = 0.04f;
    float alphaSpeed = alpha*speed;
    while(1) {
        scale.x -= speed;
        scale.y += speed;
        scale.z += speed;
        alpha -= alphaSpeed;
        if(scale.x < 0) {
            mb5ev_WarpEndSize = scale;
            MBModelScaleSet(mdlId, 0, 0, 0);
            MBModelDispSet(mdlId, FALSE);
            break;
        }
        MBModelScaleSet(mdlId, scale.x, scale.y, scale.z);
        HuPrcVSleep();
    }
}

void MB5Ev_WarpPlayerGrow(int playerNo)
{
    
    float alpha = 255;
    MBMODELID mdlId = MBPlayerModelGet(playerNo);
    float speed = 0.04f;
    float alphaSpeed = alpha*speed;
    HuVecF scale = mb5ev_WarpEndSize;
    MBModelScaleSet(mdlId, mb5ev_WarpEndSize.x, mb5ev_WarpEndSize.y, mb5ev_WarpEndSize.z);
    MBModelDispSet(mdlId, TRUE);
    while(1) {
        scale.x += speed;
        scale.y -= speed;
        scale.z -= speed;
        alpha += alphaSpeed;
        if(scale.x > 1) {
            MBModelScaleSet(mdlId, 1, 1, 1);
            break;
        }
        MBModelScaleSet(mdlId, scale.x, scale.y, scale.z);
        HuPrcVSleep();
    }
}

int MB5_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    return -1;
}
