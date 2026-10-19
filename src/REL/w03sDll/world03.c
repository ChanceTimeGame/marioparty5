/*
 * w03sDll world03.c -- Story Mode's board 3 (the party board's "Pirate Dream" map, w03dll,
 * stripped to a dressed-up stage: no rolling rock, pickaxe or scaffold, only the
 * waterfall splash and the one yy_hou event on the ? space).
 */

#include "REL/w03sDll.h"

#include "game/board/main.h"
#include "game/board/effect.h"
#include "game/board/audio.h"
#include "game/board/model.h"
#include "game/board/masu.h"
#include "game/board/scroll.h"
#include "game/board/opening.h"
#include "game/board/capsule.h"
#include "game/board/branch.h"
#include "game/board/camera.h"
#include "game/board/player.h"
#include "game/board/guide.h"
#include "game/board/window.h"
#include "game/board/coin.h"
#include "game/board/roulette.h"
#include "game/board/star.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/gamemes.h"
#include "game/mgdata.h"
#include "game/charman.h"
#include "dolphin/pad.h"

#include "humath.h"

#include "string.h"
#include "msm_grp.h"
#include "math.h"

#include "datanum/board.h"
#include "datanum/charmot.h"
#include "messdir_enum.h"

/* 0x1C8, from the memset in MB3_Create. Offsets named as they are found. */
typedef struct MB3Work_s {
    s32 objMdlId[2];               /* 0x00 */
    ANIMDATA *takiAnim;            /* 0x08 */
    ANIMDATA *splashAnim;          /* 0x0C */
    ANIMDATA *anim3C;              /* 0x10 */
    ANIMDATA *anim40;              /* 0x14 */
    u8 unk18[0x20 - 0x18];
    HU3DMODELID splash1Eff[3];     /* 0x20 */
    HU3DMODELID splash2Eff[3];     /* 0x26 */
    HU3DMODELID eff58;             /* 0x2C */
    HU3DMODELID eff5A;             /* 0x2E */
    HU3DMODELID impactEff;         /* 0x30 */
    HU3DMODELID dustEff;           /* 0x32 */
    u8 unk34[0x1C8 - 0x34];
} MB3_WORK;                        /* 0x1C8 */


/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2CC */ static HU3DMODELID mb3_MainMdlId;
/* 0x104 */ static MB3_WORK mb3_Work;
/* 0x4 */ static u8 mb3_BlueMasuNoTbl[256];
/* 0x0 */ static OMOBJ *mb3_MainObj;

static void MB3_MainObjUpdate(OMOBJ *obj);
static void MB3_Splash1EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix);
static void MB3_Splash2EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix);
static void MB3_ImpactEffUpdate(int mdlId, int count);
static void MB3_ImpactEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix);
static void MB3_ImpactEffPosSet(HuVecF *pos, float angleX, float angleY);

/* --- functions (reference order), .data placed before its first user --- */
void ObjectSetup(void)
{
    GWPartyFSet(FALSE);
    MBObjectSetup(MBNO_WORLD_3, MB3_Create, MB3_Kill);
}

void MB3_Create(void)
{
    int boardNo = MBBoardNoGet();

    memset(&mb3_Work, 0, sizeof(MB3_WORK));
    HuAudSndGrpSetSet(MSM_GRP_BD3);
    MBMasuCreate(DATANUM(DATA_w03s, 0));
    mb3_MainMdlId = MBModelCreate(DATANUM(DATA_w03s, 1), NULL, FALSE);
    MBModelPosSet(mb3_MainMdlId, 0, 0, 0);
    MBModelAttrSet(mb3_MainMdlId, HU3D_MOTATTR_LOOP);
    MBScrollInit(DATANUM(DATA_w03s, 2), 11000, 500);
    {
        HuVecF cameraPos = { 1070, 1465, 1700 };
        HuVecF cameraRot = { -27.5f, 10, 0 };
        HuVecF mapCameraPos = { 900, 0, 600 };
        HuVecF mapCameraRot = { -78, 0, 0 };
        MBOpeningViewSet(&cameraRot, &cameraPos, 7700);
        MBMapViewCameraSet(&mapCameraRot, &mapCameraPos, 11000);
    }
    MBLightHookSet(MB3_LightSet, MB3_LightReset);
    MBCapsuleColCreate(DATANUM(DATA_w03s, 3));

    MB3_ObjectCreate();
    HuDataDirClose(DATA_w03s);
    MBMasuWalkPreHookSet(MB3Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB3Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB3Ev_MasuHatena);
}

/* 0x0 */ static u32 mb3ev_TakiEmitterNo[3] = { HU_DATANUM_NONE, HU_DATANUM_NONE, HU_DATANUM_NONE };
/* 0xC */ static u32 mb3_ObjFileTbl[2] = { DATANUM(DATA_w03s, 6), DATANUM(DATA_w03s, 4) };
/* 0x14 */ static HuVecF mb3ev_TakiEffPosTbl[3] = { { 0.0f, 3345.0f, -1885.0f }, { 0.0f, 1285.0f, -775.0f }, { 0.0f, -35.0f, -185.0f } };

void MB3_ObjectCreate(void)
{
    int i;
    int mdlId;

    for(i=0; i<2; i++) {
        mb3_Work.objMdlId[i] = MB_MODEL_NONE;
        if(mb3_ObjFileTbl[i]) {
            mdlId = MBModelCreate(mb3_ObjFileTbl[i], NULL, FALSE);
            mb3_Work.objMdlId[i] = mdlId;
            MBModelPosSet(mdlId, 0, 0, 0);
            MBMotionSpeedSet(mdlId, 0);
        }
    }
    mdlId = mb3_Work.objMdlId[0];
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mdlId, 1);
    mb3_Work.takiAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x11), HU_MEMNUM_OVL));
    mb3_Work.splashAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x12), HU_MEMNUM_OVL));
    mb3_Work.anim3C = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x14), HU_MEMNUM_OVL));
    mb3_Work.anim40 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x15), HU_MEMNUM_OVL));
    for(i=0; i<3; i++) {
        mb3_Work.splash1Eff[i] = MBEffCreate(mb3_Work.splashAnim, 192);
        MBEffHookSet(mb3_Work.splash1Eff[i], MB3_Splash1EffHook);
        Hu3DModelLayerSet(mb3_Work.splash1Eff[i], 2);
        Hu3DModelPosSetV(mb3_Work.splash1Eff[i], &mb3ev_TakiEffPosTbl[i]);
        mb3_Work.splash2Eff[i] = MBEffCreate(mb3_Work.splashAnim, 48);
        MBEffHookSet(mb3_Work.splash2Eff[i], MB3_Splash2EffHook);
        Hu3DModelLayerSet(mb3_Work.splash2Eff[i], 2);
        Hu3DModelPosSet(mb3_Work.splash2Eff[i], mb3ev_TakiEffPosTbl[i].x,
                        mb3ev_TakiEffPosTbl[i].y, 50 + mb3ev_TakiEffPosTbl[i].z);
        mb3ev_TakiEmitterNo[i] = MBAudFXEmiterSet(1500, &mb3ev_TakiEffPosTbl[i]);
    }
    mb3_Work.eff58 = MBEffCreate(mb3_Work.anim3C, 1);
    mb3_Work.eff5A = MBEffCreate(mb3_Work.anim40, 1);
}

void MB3_Kill(void)
{
    int i;

    if(mb3_MainMdlId >= 0) {
        MBModelKill(mb3_MainMdlId);
        mb3_MainMdlId = MB_MODEL_NONE;
    }
    MBCameraModelViewSet(MB_MODEL_NONE, NULL, NULL, -1, 45, 63);
    for(i=0; i<2; i++) {
        if(mb3_Work.objMdlId[i] >= 0) {
            MBModelKill(mb3_Work.objMdlId[i]);
        }
        mb3_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<3; i++) {
        if(mb3_Work.splash1Eff[i] >= 0) {
            MBEffKill(mb3_Work.splash1Eff[i]);
        }
        mb3_Work.splash1Eff[i] = HU3D_MODELID_NONE;
        if(mb3_Work.splash2Eff[i] >= 0) {
            MBEffKill(mb3_Work.splash2Eff[i]);
        }
        mb3_Work.splash2Eff[i] = HU3D_MODELID_NONE;
    }
    if(mb3_Work.eff58 >= 0) {
        MBEffKill(mb3_Work.eff58);
    }
    if(mb3_Work.eff5A >= 0) {
        MBEffKill(mb3_Work.eff5A);
    }
    mb3_Work.eff58 = mb3_Work.eff5A = HU3D_MODELID_NONE;
}

static void MB3_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;

    if(MBKillCheck()) {
        if(mb3_MainObj != NULL) {
            omDelObjEx(mbObjMan, mb3_MainObj);
        }
        return;
    }
    camera = MBCameraGet();
}

static void MB3_Splash1EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    static HuVecF radius = { 250, 250, 250 };
    MBEFFECTDATA *data;
    int i;
    float rate;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>3);
        }
        effP->count = 1;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            data->time++;
            continue;
        }
        if(data->time == 0) {
            data->time++;
            data->rot.z = 360*MBEffRandF();
            rate = MBEffRandF();
            data->color.r = 160+(70*rate);
            data->color.g = 200+(40*rate);
            data->color.b = 180+(55*rate);
            data->vel.x = 1.6666666f*(0.8f*MBEffSRandF());
            data->vel.z = 1.6666666f+(1.6666666f*(2*MBEffRandF()));
            data->vel.y = 6.6666665f+(1.6666666f*(4*MBEffRandF()));
            data->parManId = effP->num>>3;
            data->pos.x = radius.x*MBEffSRandF();
            data->pos.z = 100*(0.3f*MBEffSRandF());
            data->pos.y = 100*(0.5f*MBEffRandF());
            data->color.a = 180+(70*MBEffRandF());
            data->scale = 60+(40*MBEffRandF());
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 10) {
            if(data->color.a >= 20) {
                data->color.a -= 20;
            }
            data->scale += 5.0f;
        }
    }
}

static void MB3_Splash2EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    static HuVecF radius = { 250, 250, 250 };
    MBEFFECTDATA *data;
    int i;
    float rate;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>1);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            data->time++;
            continue;
        }
        if(data->time == 0) {
            data->time++;
            data->rot.z = 360*MBEffRandF();
            rate = MBEffRandF();
            data->color.r = data->color.g = data->color.b = 255;
            data->vel.x = 1.6666666f*(0.8f*MBEffSRandF());
            data->vel.z = 1.6666666f+(1.6666666f*(4*MBEffRandF()));
            data->vel.y = 4.1666665f+(1.6666666f*(2.5f*MBEffRandF()));
            data->parManId = effP->num>>1;
            data->pos.x = radius.x*MBEffSRandF();
            data->pos.z = (100*(0.3f*MBEffSRandF()))-50;
            data->pos.y = 50+(100*(1.5f*MBEffRandF()));
            data->color.a = 20+(20*MBEffRandF());
            data->scale = 120+(50*MBEffRandF());
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 10) {
            if(data->color.a >= 10) {
                data->color.a -= 10;
            }
            data->scale += 5.0f;
        }
    }
}

void MB3_LightSet(void)
{
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DModelLightInfoSet(MBModelIdGet(mb3_MainMdlId), TRUE);
}

void MB3_LightReset(void)
{
}

int MB3Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    u32 flag;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    if(flag & MASU_FLAG_BIT(13)) {
        MB3Ev_HatenaYYHou(playerNo);
    }
}

void MB3_Stub(void)
{
}

int MB3Ev_MasuWalkPre(int playerNo)
{
}

int MB3Ev_MasuWalkPost(int playerNo)
{
    return 0;
}

static void MB3Ev_HatenaYYHou(int playerNo)
{
    u32 flag;
    int playerTbl[4];
    HuVecF pos;
    HuVecF vel;
    HuVecF vec;
    HuVecF rot;
    Mtx mtxB;
    Mtx mtxA;
    MASU *masu;
    s16 masuId;
    int i;
    int mdlId;
    int hooMdlId;
    int count;
    int frame;
    int warpId;
    MASU *masuP;
    int liveF;
    int n;
    int masuNum;
    float scale;
    float time;
    float grav;
    float angle;

    frame = 0;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerMotIdleSet(playerNo);
    flag = (u16)masu->flag;
    mdlId = MBModelCreate(BOARD_HSF_effExplode, NULL, FALSE);
    MBModelLayerSet(mdlId, 6);
    MBModelDispSet(mdlId, FALSE);
    playerTbl[0] = playerTbl[1] = playerTbl[2] = playerTbl[3] = -1;
    count = 0;
    liveF = 1;
    mb3_Work.impactEff = MBEffCreate(mb3_Work.anim40, 32);
    MBEffAttrSet(mb3_Work.impactEff, MB_EFFECT_ATTR_UPAUSE);
    MBEffHookSet(mb3_Work.impactEff, MB3_ImpactEffHook);
    Hu3DModelLayerSet(mb3_Work.impactEff, 3);
    if(liveF != 0) {
        hooMdlId = mb3_Work.objMdlId[1];
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        MBPlayerPosGet(playerNo, &pos);
        Hu3DModelObjPosGet(MBModelIdGet(mb3_Work.objMdlId[1]), "yy_hou2-thook", &vel);
        vel.y += 200;
        VECSubtract(&vel, &pos, &vel);
        time = 0.6f;
        grav = -4900;
        vel.x /= time;
        vel.z /= time;
        vel.y = (vel.y/time)-((0.5f*time)*grav);
        VECScale(&vel, &vel, 0.016666668f);
        time *= 60;
        grav *= 0.0002777778f;
        MBPlayerRotSet(playerNo, 0, HuAtan(vel.x, vel.z), 0);
        for(i=0; i<3; i++) {
            HuPrcVSleep();
        }
        for(i=0; i<(int)time; i++) {
            vel.y += grav;
            VECAdd(&pos, &vel, &pos);
            MBPlayerPosSetV(playerNo, &pos);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 5, 0, 0, 0);
        time = 30;
        scale = 1;
        for(i=0; i<(int)time; i++) {
            pos.y += -200/time;
            scale *= 0.95f;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerScaleSet(playerNo, scale, scale, scale);
            HuPrcVSleep();
        }
        warpId = -1;
        for(i=0; i<masu->linkNum; i++) {
            warpId = masu->linkTbl[i];
            masuP = MBMasuGet(MASU_LAYER_DEFAULT, warpId);
            if(masuP->linkNum == 0) {
                break;
            }
            warpId = -1;
        }
        if(warpId < 0) {
            warpId = masuId;
        }
        MBCameraFocusSet(-1);
        MBMotionSpeedSet(hooMdlId, 1);
        MBMotionTimeSet(hooMdlId, 0);
        MBAudFXPlay(0x5DF);
        for(i=0; i<MBMotionMaxTimeGet(hooMdlId)-10; i++) {
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 0, 0x40000001);
        MBPlayerPosGet(playerNo, &pos);
        MBPlayerWinLoseVoicePlay(playerNo, 1, 0x1F9);
        angle = 0;
        vel.x = HuSin(210)*HuCos(60);
        vel.y = HuSin(60);
        vel.z = HuCos(210)*HuCos(60);
        VECScale(&vel, &vec, 200);
        VECAdd(&pos, &vec, &vec);
        MB3_ImpactEffPosSet(&vec, 60, 200);
        MBAudFXPlay(0x5E0);
        omVibrate(playerNo, 12, 4, 2);
        VECScale(&vel, &vel, 33.333332f);
        MBCameraQuakeSet(18, 500);
        for(i=0; i<30.0f; i++) {
            angle += 18;
            PSMTXRotRad(mtxB, 'Y', 0.017453292f*angle);
            PSMTXRotRad(mtxA, 'X', 0.5235988f);
            PSMTXConcat(mtxA, mtxB, mtxB);
            PSMTXRotRad(mtxA, 'Y', 3.6651914f);
            PSMTXConcat(mtxA, mtxB, mtxB);
            Hu3DMtxRotGet(mtxB, &rot);
            MBPlayerRotSetV(playerNo, &rot);
            VECAdd(&pos, &vel, &pos);
            MBPlayerPosSetV(playerNo, &pos);
            scale += 0.3f*(1-scale);
            MBPlayerScaleSet(playerNo, scale, scale, scale);
            HuPrcVSleep();
        }
        MBPlayerScaleSet(playerNo, 1, 1, 1);
        i = (int)(3*MBEffRandF())+1;
        warpId = masuId;
        n = 0;
        masuNum = MBMasuNumGet(MASU_LAYER_DEFAULT);
        if(masuNum > 255) {
            masuNum = 255;
        }
        for(i=1; i<=masuNum; i++) {
            if(MBMasuTypeGet(MASU_LAYER_DEFAULT, i) == MASU_TYPE_BLUE) {
                mb3_BlueMasuNoTbl[n++] = i;
            }
        }
        n = (int)(n*MBEffRandF());
        warpId = mb3_BlueMasuNoTbl[n];
        count = 0;
        for(i=0; i<4; i++) {
            if(warpId == GwPlayer[i].masuId && MBPlayerAliveCheck(i)) {
                playerTbl[i] = i;
                count++;
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        MBMotionSpeedSet(mb3_Work.objMdlId[1], 0);
        MBMotionTimeSet(mb3_Work.objMdlId[1], 0);
        MBPlayerDispSet2(playerNo, FALSE);
        MBEffKill(mb3_Work.impactEff);
        mb3_Work.impactEff = mb3_Work.dustEff = -1;
        MBPlayerPosFixWarp(playerNo, warpId, TRUE);
        MBCameraFocusMasuSet(warpId);
        MBCameraSkipSet(0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        MBPlayerDispSet2(playerNo, TRUE);
        masu = MBMasuGet(MASU_LAYER_DEFAULT, warpId);
        pos.x = masu->pos.x;
        pos.y = masu->pos.y;
        pos.z = masu->pos.z;
        pos.y += 1000;
        vel.x = vel.z = 0;
        vel.y = -5;
        MBPlayerRotSet(playerNo, 0, 0, 0);
        MBPlayerScaleSet(playerNo, 1, 1, 1);
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 0, 0);
        while(pos.y > masu->pos.y) {
            if(pos.y-masu->pos.y < 200 && MBPlayerMotionNoGet(playerNo) != 5) {
                MBPlayerMotionNoShiftSet(playerNo, 5, 0, 0, 0);
                frame = 0;
                if(count != 0) {
                    MBModelDispSet(mdlId, TRUE);
                    MBMotionTimeSet(mdlId, 0);
                }
            }
            MBPlayerPosSetV(playerNo, &pos);
            MB3_ImpactEffUpdate(mdlId, frame);
            frame++;
            HuPrcVSleep();
            VECAdd(&pos, &vel, &pos);
            vel.y += grav;
        }
        GwPlayer[playerNo].masuId = warpId;
        do {
            MB3_ImpactEffUpdate(mdlId, frame);
            frame++;
            HuPrcVSleep();
        } while(MBPlayerMotionEndCheck(playerNo) == 0);
        MBPlayerMotIdleSet(playerNo);
        for(i=0; i<30; i++) {
            frame++;
            MB3_ImpactEffUpdate(mdlId, frame);
            HuPrcVSleep();
        }
        if(count != 0) {
            MBModelDispSet(mdlId, FALSE);
            for(i=0; i<4; i++) {
                if(playerTbl[i] >= 0) {
                    MBPlayerMotionNoSet(i, 6, 0x40000001);
                }
            }
            for(i=0; i<4; i++) {
                if(playerTbl[i] >= 0) {
                    MBCoinAddDispExec(i, -5, TRUE);
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        for(i=0; i<4; i++) {
            if(playerTbl[i] >= 0) {
                MBPlayerMotionNoSet(i, 1, 0x40000001);
            }
        }
        MBMotionSpeedSet(mb3_Work.objMdlId[1], 0);
        MBMotionTimeSet(mb3_Work.objMdlId[1], 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
    }
    MBModelKill(mdlId);
}

static void MB3_ImpactEffUpdate(int mdlId, int count)
{
    HuVecF outPos;
    HuVecF pos = { 0, 0, -500 };
    Mtx mtx;
    float t;
    float scale;

    PSMTXInverse(Hu3DCameraMtx, mtx);
    PSMTXMultVec(mtx, &pos, &outPos);
    mtx[0][3] = mtx[1][3] = mtx[2][3] = 0;
    t = count/30.0f;
    scale = (1+(5*t))+(0.5*HuSin(16*(360*t)));
    scale *= 0.4f;
    MBModelPosSetV(mdlId, &outPos);
    MBModelMtxSet(mdlId, &mtx);
    MBModelScaleSet(mdlId, scale, scale, scale);
}

static void MB3_ImpactEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;

    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.x *= 0.9f;
        data->vel.y *= 0.9f;
        data->vel.z *= 0.9f;
        data->scale += 6.0f;
        data->color.a *= 0.98f;
        if(data->time < 24.0f) {
            data->color.a = 0.9f*data->color.a;
        }
        if(--data->time == 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        }
    }
}

static void MB3_ImpactEffPosSet(HuVecF *pos, float angleX, float angleY)
{
    MBEFFECT *effP = Hu3DData[mb3_Work.impactEff].hookData;
    HuVecF dir;
    HuVecF vec;
    Mtx mtx;
    Mtx mtxY;
    MBEFFECTDATA *data;
    int i;
    u32 num;
    float rate;
    float speed;

    PSMTXRotRad(mtx, 'X', 0.017453292f*angleX);
    PSMTXRotRad(mtxY, 'Y', 0.017453292f*angleY);
    PSMTXConcat(mtx, mtxY, mtx);
    PSMTXTransApply(mtx, mtx, pos->x, pos->y, pos->z);
    data = effP->data;
    num = 32;
    for(i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time = 60*(0.7f+(0.5f*MBEffRandF()));
        rate = 360*MBEffSRandF();
        dir.x = HuCos(rate);
        dir.y = HuSin(rate);
        dir.z = 0.5f;
        VECScale(&dir, &vec, 20);
        PSMTXMultVec(mtx, &vec, &data->pos);
        speed = 13.333333f+(1.6666666f*(7*MBEffRandF()));
        VECScale(&dir, &vec, speed);
        PSMTXMultVecSR(mtx, &vec, &data->vel);
        data->rot.z = 360*MBEffRandF();
        data->scale = 20+(20*MBEffRandF());
        data->color.a = 100+(80*MBEffRandF());
        rate = MBEffRandF();
        data->color.r = 150+(70*rate);
        data->color.g = 144+(70*rate);
        data->color.b = 140+(70*rate);
        num--;
        if(num < 1) {
            break;
        }
    }
}

float MB3_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3)
{
    float mag = VECMag(vec3);
    if(mag > 0) {
        mag = ((vec3->x*(vec1->x-vec2->x))+(vec3->y*(vec1->y-vec2->y))+(vec3->z*(vec1->z-vec2->z)))/mag;
    }
    return mag;
}

unsigned int MB3Ev_BitGet(int outMask, unsigned int inMask)
{
    unsigned int bitIn;
    int i;
    unsigned int result;
    int bitOut;

    outMask &= inMask;
    result = 0;
    bitOut = bitIn = (1 << 0);

    for(i=0; i<32; i++) {
        if(inMask & bitIn) {
            if(outMask & bitIn) {
                result |= bitOut;
            }
            bitOut <<= 1;
        }
        bitIn <<= 1;
    }
    return result;
}

unsigned int MB3Ev_MasuFlagGet(int outMask, unsigned int inMask)
{
    unsigned int bitIn;
    int i;
    int bitOut;
    unsigned int result;

    bitIn = bitOut = (1 << 0);
    result = 0;
    for(i=0; i<32; i++) {
        if(inMask & bitIn) {
            if(outMask & bitOut) {
                result |= bitIn;
            }
            bitOut <<= 1;
        }
        bitIn <<= 1;
    }
    return result;
}
