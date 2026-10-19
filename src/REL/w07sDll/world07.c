/*
 * w07sDll world07.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/w07sDll/asm/REL/w07sDll/world07.s.
 */

#include "REL/w07sDll.h"

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
#include "game/board/com.h"
#include "game/board/roulette.h"
#include "game/board/star.h"

#include "game/sprite.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/gamemes.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/object.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "humath.h"
#include "math.h"

#include "datanum/capsulechar4.h"
#include "datanum/charmot.h"
#include "messnum/board_w07.h"

#define MB7EV_HOU_FLAG MASU_FLAG_BIT(7)

#define MB7_OBJ_MAX 4
#define MB7_BACKOBJ_MAX 12
#define MB7_EFF_MAX 4

#define MB7EV_KOOPAMOT_IDLE 0
#define MB7EV_KOOPAMOT_WALK 1
#define MB7EV_KOOPAMOT_STOMP 2
#define MB7EV_KOOPAMOT_LAUGH 3
#define MB7EV_KOOPAMOT_JUMPSTART 4
#define MB7EV_KOOPAMOT_LOSE 5
#define MB7EV_KOOPAMOT_JUMP 6
#define MB7EV_KOOPAMOT_SPEAK 7
#define MB7EV_KOOPAMOT_HOLD 8
#define MB7EV_KOOPAMOT_MAX 9

typedef struct MB7Ev_Koopa_s {
    u8 unk00[0x1C-0x00];                /* 0x00 */
    float maxTime;                      /* 0x1C */
    float unk20;                        /* 0x20 */
    float unk24;                        /* 0x24 */
    int mdlId[4];                       /* 0x28 */
    int motId[MB7EV_KOOPAMOT_MAX];      /* 0x38 */
    int effMdlId;                       /* 0x5C */
    s32 dataStatId;                     /* 0x60 */
    int motNo;                          /* 0x64 */
    HuVecF pos;                         /* 0x68 */
    HuVecF rot;                         /* 0x74 */
    HuVecF vel;                         /* 0x80 */
} MB7EV_KOOPA;

typedef struct MB7Ev_Player_s {
    int enableF;                        /* 0x00 */
    int unk04;                          /* 0x04 */
    int mode;                           /* 0x08 */
    int masuId;                         /* 0x0C */
    int step;                           /* 0x10 */
    float maxTime;                      /* 0x14 */
    u8 unk18[0x1C-0x18];                /* 0x18 */
    float angleY;                       /* 0x1C */
    s16 motId;                          /* 0x20 */
    u8 unk22[0x2C-0x22];                /* 0x22 */
    HuVecF pos;                         /* 0x2C */
    HuVecF rot;                         /* 0x38 */
    HuVecF vel;                         /* 0x44 */
    u8 unk50[0x5C-0x50];                /* 0x50 */
} MB7EV_PLAYER;

typedef struct MB7Ev_Hou_s {
    int mode;                           /* 0x00 */
    u8 unk04[0x10-0x04];                /* 0x04 */
    float angleY;                       /* 0x10 */
    float angleSpeed;                   /* 0x14 */
    float charge;                       /* 0x18 */
    int fireF;                          /* 0x1C */
    u8 unk20[0x30-0x20];                /* 0x20 */
    int fireEff[4];                     /* 0x30 */
    HuVecF firePos;                     /* 0x40 */
    HuVecF rot;                         /* 0x4C */
    u8 unk58[0x64-0x58];                /* 0x58 */
    HuVecF pos;                         /* 0x64 */
    u8 unk70[0x84-0x70];                /* 0x70 */
} MB7EV_HOU;

typedef struct MB7_Work_s {
    int objMdlId[MB7_OBJ_MAX];              /* 0x00 */
    int backObjMdlId[MB7_BACKOBJ_MAX];      /* 0x10 */
    ANIMDATA *effAnim40;                    /* 0x40 */
    ANIMDATA *effAnim44;                    /* 0x44 */
    HU3DMODELID effMdlId[MB7_EFF_MAX];      /* 0x48 */
    u8 unk50[0x54-0x50];                    /* 0x50 */
    MB7EV_KOOPA koopa;                      /* 0x54 */
    MB7EV_HOU hou;                          /* 0xE0 */
    MB7EV_PLAYER player[GW_PLAYER_MAX];     /* 0x164 */
    u8 unk2D4[0x2DC-0x2D4];                 /* 0x2D4 */
} MB7_WORK;

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2E4 */ static MBMODELID mb7_MainMdlId;
/* 0x2E0 */ static u8 *mb7_SaveWorkP;
/* 0x4 */ static MB7_WORK mb7_Work;
/* 0x0 */ static OMOBJ *mb7_MainObj;

static void MB7_ObjectCreate(void);
static void MB7_MainObjUpdate(OMOBJ *obj);
static void MB7Ev_HouPlayerUpdate(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 21 insns */
void ObjectSetup(void)
{
    GWPartyFSet(FALSE);
    MBObjectSetup(MBNO_WORLD_7, MB7_Create, MB7_Kill);
}

/* 142 insns */
void MB7_Create(void)
{
    int boardNo = MBBoardNoGet();

    memset(&mb7_Work, 0, sizeof(MB7_WORK));
    HuAudSndGrpSetSet(MSM_GRP_BD7);
    mb7_SaveWorkP = MBSaveWorkPGet();
    MBMasuCreate(DATANUM(DATA_w07s, 0));
    mb7_MainMdlId = MBModelCreate(DATANUM(DATA_w07s, 1), NULL, FALSE);
    MBModelPosSet(mb7_MainMdlId, 0, 0, 0);
    MBModelAttrSet(mb7_MainMdlId, HU3D_MOTATTR_LOOP);
    MBScrollInit(DATANUM(DATA_w07s, 2), 10690, -631);
    {
        HuVecF cameraPos = { 0, -380, -1030 };
        HuVecF cameraRot = { -30, 0, 0 };
        HuVecF mapCameraPos = { 0, 0, -631 };
        HuVecF mapCameraRot = { -78, 0, 0 };
        MBOpeningViewSet(&cameraRot, &cameraPos, 9950);
        MBMapViewCameraSet(&mapCameraRot, &mapCameraPos, 10690);
    }
    MBLightHookSet(MB7_LightSet, MB7_LightReset);
    MBCapsuleColCreate(DATANUM(DATA_w07s, 3));
    MB7_ObjectCreate();
    HuDataDirClose(DATANUM(DATA_w07s, 0));
    MBMasuWalkPreHookSet(MB7Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB7Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB7Ev_MasuHatena);
    mb7_MainObj = MBAddObj(32768, 0, 0, MB7_MainObjUpdate);
}

/* 0x0 */ static u32 mb7_ObjFileTbl[4] = { DATANUM(DATA_w07s, 4), DATANUM(DATA_w07s, 6), DATANUM(DATA_w07s, 10), DATANUM(DATA_w07s, 11) };
/* 0x10 */ static u32 mb7_BackObjFileTbl[12] = { DATANUM(DATA_w07s, 5), DATANUM(DATA_w07s, 5), DATANUM(DATA_w07s, 7), DATANUM(DATA_w07s, 7), DATANUM(DATA_w07s, 7), DATANUM(DATA_w07s, 7), DATANUM(DATA_w07s, 8), DATANUM(DATA_w07s, 8), DATANUM(DATA_w07s, 9), DATANUM(DATA_w07s, 9), DATANUM(DATA_w07s, 9), DATANUM(DATA_w07s, 9) };
/* 0x40 */ static HuVecF mb7_BackObjPosTbl[12] = { { -615.0f, -315.0f, 645.0f }, { 615.0f, -315.0f, 645.0f }, { -715.0f, -300.0f, -1600.0f }, { 715.0f, -300.0f, -1600.0f }, { -715.0f, -300.0f, -2435.0f }, { 715.0f, -300.0f, -2435.0f }, { -2895.0f, 500.0f, -2030.0f }, { 2895.0f, 500.0f, -2030.0f }, { -2385.0f, 500.0f, -2545.0f }, { 2385.0f, 500.0f, -2545.0f }, { -1245.0f, -400.0f, -300.0f }, { 1245.0f, -400.0f, -300.0f } };
/* 0xD0 */ static float mb7_BackObjRotYTbl[12] = { 30.0f, -30.0f, 0.0f, 0.0f, 0.0f, 0.0f, -45.0f, 45.0f, -45.0f, 45.0f, 45.0f, -45.0f };

/* 251 insns */
static void MB7_ObjectCreate(void)
{
    HuVecF pos = { 0, 0, 0 };
    int i;
    int mdlId;

    for(i=0; i<MB7_OBJ_MAX; i++) {
        mb7_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        mb7_Work.backObjMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_EFF_MAX; i++) {
        mb7_Work.effMdlId[i] = HU3D_MODELID_NONE;
    }
    for(i=0; i<MB7_OBJ_MAX; i++) {
        if(mb7_ObjFileTbl[i]) {
            mdlId = MBModelCreate(mb7_ObjFileTbl[i], NULL, FALSE);
            mb7_Work.objMdlId[i] = mdlId;
            MBModelPosSet(mdlId, 0, 0, 0);
            MBMotionSpeedSet(mdlId, 0);
            MBMotionShapeSpeedSet(mdlId, 0);
        }
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        mdlId = MBModelCreate(mb7_BackObjFileTbl[i], NULL, TRUE);
        mb7_Work.backObjMdlId[i] = mdlId;
        MBModelPosSetV(mdlId, &mb7_BackObjPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb7_BackObjRotYTbl[i], 0);
    }
    mdlId = mb7_Work.objMdlId[0];
    if(mdlId >= 0) {
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_SHAPE_LOOP);
        MBMotionSpeedSet(mdlId, 0.5f);
        MBMotionShapeSpeedSet(mdlId, 0.5f);
    }
    mdlId = mb7_Work.objMdlId[1];
    if(mdlId >= 0) {
        MBModelPosSet(mdlId, 0, 330, -2030);
    }
    for(i=2; i<=3; i++) {
        mdlId = mb7_Work.objMdlId[i];
        if(mdlId >= 0) {
            MBModelDispSet(mdlId, FALSE);
        }
    }
    Hu3DModelLayerSet(MBModelIdGet(mb7_Work.objMdlId[3]), 2);
    for(i=8; i<=12; i++) {
        mdlId = mb7_Work.backObjMdlId[i];
        if(mdlId >= 0) {
            MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
            MBMotionSpeedSet(mdlId, 1);
        }
    }
    mb7_Work.effAnim40 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w07s, 12), HU_MEMNUM_OVL));
    mb7_Work.effAnim44 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w07s, 13), HU_MEMNUM_OVL));
    mb7_Work.effMdlId[0] = MBEffCreate(mb7_Work.effAnim40, 1);
    mb7_Work.effMdlId[1] = MBEffCreate(mb7_Work.effAnim44, 1);
}

/* 107 insns */
void MB7_Kill(void)
{
    int i;

    if(mb7_MainMdlId >= 0) {
        MBModelKill(mb7_MainMdlId);
        mb7_MainMdlId = MB_MODEL_NONE;
    }
    MBCameraModelViewSet(MB_MODEL_NONE, NULL, NULL, -1, 45, 63);
    for(i=0; i<MB7_OBJ_MAX; i++) {
        if(mb7_Work.objMdlId[i] >= 0) {
            MBModelKill(mb7_Work.objMdlId[i]);
        }
        mb7_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        if(mb7_Work.backObjMdlId[i] >= 0) {
            MBModelKill(mb7_Work.backObjMdlId[i]);
        }
        mb7_Work.backObjMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_EFF_MAX; i++) {
        if(mb7_Work.effMdlId[i] >= 0) {
            MBEffKill(mb7_Work.effMdlId[i]);
        }
        mb7_Work.effMdlId[i] = HU3D_MODELID_NONE;
    }
}

/* 26 insns */
static void MB7_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;

    if(MBKillCheck()) {
        if(mb7_MainObj != NULL) {
            omDelObjEx(mbObjMan, mb7_MainObj);
        }
        return;
    }
    camera = MBCameraGet();
}

/* 31 insns */
void MB7_LightSet(void)
{
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DModelLightInfoSet(MBModelIdGet(mb7_MainMdlId), TRUE);
}

/* 1 insns */
void MB7_LightReset(void)
{
}

/* 29 insns */
int MB7Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    u32 flag;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    if(flag & MB7EV_HOU_FLAG) {
        MB7Ev_Hou(playerNo);
    }
}

/* 1 insns */
void MB7_MasuStub(void)
{
}

/* 1 insns */
int MB7Ev_MasuWalkPre(int playerNo)
{
}

/* 26 insns */
int MB7Ev_MasuWalkPost(int playerNo)
{
    MASU *masu;
    u32 flag;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    return 0;
}

/* 1049 insns */
void MB7Ev_Hou(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MB7EV_HOU *hou;
    MB7EV_PLAYER *player;
    MASU *masu;
    int emitter;
    int mdlId;
    int i;
    int masuId;
    BOOL endF;
    u32 flag;
    int coin;
    HuVecF pos;
    HuVecF fxPos;
    HuVecF cameraPos;
    HuVecF rot;
    int coinNum[GW_PLAYER_MAX];

    koopa = &mb7_Work.koopa;
    hou = &mb7_Work.hou;
    emitter = -1;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    MB7Ev_KoopaInit();
    MBCameraFocusPlayerSet(-1);
    MBCameraPlayerViewSet(playerNo, NULL, NULL, 1500, -1, 30);
    MBPlayerRotGet(playerNo, &rot);
    if(fabsf2(MB7_AngleDiff(0, rot.y)) > 10) {
        MBPlayerMotionNoShiftSet(playerNo, 2, 0, 8, HU3D_MOTATTR_LOOP);
    } else {
        MBPlayerMotIdleSet(playerNo);
    }
    for(i=0; i<30.0f; i++) {
        MBPlayerRotGet(playerNo, &rot);
        MBAngleMoveTo(&rot.y, 0, 0.15f);
        MBPlayerRotSetV(playerNo, &rot);
        HuPrcVSleep();
    }
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        if(MBPlayerAliveCheck(i)) {
            masuId = GwPlayer[i].masuId;
            masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
            if(masu->flag & MB7EV_HOU_FLAG) {
                player->enableF = 1;
                player->masuId = masuId;
            }
        }
    }
    MB7Ev_HouPlayerUpdate();
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LAUGH);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_STOMP);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_HOLD);
    MB7Ev_KoopaDataClose();
    MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
    MBCameraQuakeSet(18, 200);
    MBAudFXPlay(873);
    for(i=0; i<18.0f; i++) {
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    memset(hou, 0, sizeof(MB7EV_HOU));
    mdlId = mb7_Work.objMdlId[1];
    Hu3DModelObjPosGet(MBModelIdGet(mdlId), "kupa_dream_all-kupa_pos", &pos);
    Hu3DModelObjPosGet(MBModelIdGet(mdlId), "kupa_dream_all-fire_pos", &hou->firePos);
    hou->pos = pos;
    MBMotionSpeedSet(mb7_Work.objMdlId[2], 1);
    MBModelAttrSet(mb7_Work.objMdlId[2], HU3D_MOTATTR_LOOP);
    koopa->pos = pos;
    koopa->pos.z -= 120.00001f;
    MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
    MBModelDispSet(koopa->mdlId[0], TRUE);
    MBCameraFocusPlayerSet(-1);
    cameraPos = pos;
    cameraPos.z += 500;
    MBCameraPosViewSet(&cameraPos, NULL, NULL, 3000, -1, 60);
    MBAudFXPlay(713);
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    MBWinCreate(2, MESSNUM(MESS_BOARD_W07, 9), 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_HOLD, FALSE);
    hou->fireEff[0] = MBEffCreate(mb7_Work.effAnim40, 256);
    MBEffHookSet(hou->fireEff[0], MB7Ev_KoopaFire1Hook);
    Hu3DModelLayerSet(hou->fireEff[0], 2);
    Hu3DModelPosSet(hou->fireEff[0], 0, 0, 0);
    hou->fireEff[1] = MBEffCreate(mb7_Work.effAnim40, 64);
    MBEffHookSet(hou->fireEff[1], MB7Ev_KoopaFire2Hook);
    Hu3DModelLayerSet(hou->fireEff[1], 2);
    Hu3DModelPosSet(hou->fireEff[1], 0, 0.05f, 0.05f);
    hou->fireEff[2] = MBEffCreate(mb7_Work.effAnim40, 64);
    MBEffHookSet(hou->fireEff[2], MB7Ev_KoopaFire3Hook);
    Hu3DModelLayerSet(hou->fireEff[2], 2);
    Hu3DModelPosSet(hou->fireEff[2], 0, -0.05f, -0.05f);
    hou->fireEff[3] = MBEffCreate(mb7_Work.effAnim40, 64);
    MBEffHookSet(hou->fireEff[3], MB7Ev_KoopaFire4Hook);
    Hu3DModelLayerSet(hou->fireEff[3], 2);
    Hu3DModelPosSet(hou->fireEff[3], 0, 0, -0.05f);
    endF = FALSE;
    while(!endF) {
        switch(hou->mode) {
            case 0:
                hou->angleY = 0;
                hou->angleSpeed = 0;
                hou->charge = 0;
                hou->fireF = 0;
                koopa->maxTime = 1;
                hou->mode++;
                emitter = HuAudFXEmiterPlay(1565, &pos);
                /* falls through */

            case 1:
                hou->angleY += hou->angleSpeed;
                if(hou->angleY > -45) {
                    if(hou->angleSpeed > -1) {
                        hou->angleSpeed += -0.02f;
                    }
                } else if(hou->angleY < -90 && hou->angleSpeed < -0.33333334f) {
                    hou->angleSpeed += 0.02f;
                }
                if(hou->angleY > -110) {
                    break;
                }
                hou->fireF = 1;
                hou->angleY = -110;
                hou->angleSpeed = 0;
                hou->mode++;
                HuAudFXStop(emitter);
                emitter = HuAudFXEmiterPlay(1567, &fxPos);
                break;

            case 2:
                HuAudFXEmiterUpDate(emitter, &fxPos);
                hou->charge += 0.05f*(1-hou->charge);
                hou->angleY += hou->angleSpeed;
                if(hou->angleY < 0) {
                    if(hou->angleSpeed < 0.5f) {
                        hou->angleSpeed += 0.01f;
                    }
                } else if(hou->angleY > 95 && hou->angleSpeed > 0.33333334f) {
                    hou->angleSpeed += -0.015000001f;
                }
                if(hou->angleY < 110) {
                    break;
                }
                hou->angleY = 110;
                hou->angleSpeed = 0;
                hou->fireF = 0;
                MBAudFXStop(emitter);
                hou->mode++;
                emitter = HuAudFXEmiterPlay(1565, &pos);
                break;

            case 3:
                hou->charge *= 0.95f;
                hou->angleY += hou->angleSpeed;
                if(hou->angleY > 45) {
                    if(hou->angleSpeed > -1) {
                        hou->angleSpeed += -0.02f;
                    }
                } else if(hou->angleY < 20 && hou->angleSpeed < -0.33333334f) {
                    hou->angleSpeed += 0.02f;
                }
                if(hou->angleY > 0) {
                    break;
                }
                hou->angleY = 0;
                hou->mode++;
                HuAudFXStop(emitter);
                MBAudFXPlay(1566);
                /* falls through */

            case 4:
                endF = TRUE;
                break;
        }
        hou->rot.y = hou->angleY;
        MBModelRotSetV(mdlId, &hou->rot);
        Hu3DModelObjPosGet(MBModelIdGet(mdlId), "kupa_dream_all-kupa_pos", &pos);
        Hu3DModelObjPosGet(MBModelIdGet(mdlId), "kupa_dream_all-fire_pos", &hou->firePos);
        hou->pos = pos;
        koopa->maxTime *= 0.98f;
        pos.x = pos.x+(-60.000004f*koopa->maxTime-60.000004f)*sin(M_PI*hou->rot.y/180);
        pos.z = pos.z+(-60.000004f*koopa->maxTime-60.000004f)*cos(M_PI*hou->rot.y/180);
        MBModelPosSetV(koopa->mdlId[0], &pos);
        MBModelRotSetV(koopa->mdlId[0], &hou->rot);
        if(hou->charge <= 0 || hou->fireF == 0) {
            MBModelDispSet(mb7_Work.objMdlId[2], FALSE);
        } else {
            MBModelDispSet(mb7_Work.objMdlId[2], TRUE);
            MBModelPosSet(mb7_Work.objMdlId[2], hou->firePos.x, hou->firePos.y-60.000004f, hou->firePos.z);
            MBModelRotSetV(mb7_Work.objMdlId[2], &hou->rot);
            MBModelScaleSet(mb7_Work.objMdlId[2], hou->charge, hou->charge, hou->charge);
        }
        fxPos.x = 250.0*(hou->charge*sin(M_PI*hou->rot.y/180));
        fxPos.z = 250.0*(hou->charge*cos(M_PI*hou->rot.y/180));
        fxPos.y = hou->firePos.y;
        MB7Ev_HouPlayerUpdate();
        player = &mb7_Work.player[0];
        for(i=0; i<GW_PLAYER_MAX; i++, player++) {
            if(player->enableF && player->mode < 3) {
                endF = FALSE;
            }
        }
        HuPrcVSleep();
    }
    MBEffKill(hou->fireEff[0]);
    MBEffKill(hou->fireEff[1]);
    MBEffKill(hou->fireEff[2]);
    MBEffKill(hou->fireEff[3]);
    hou->fireEff[0] = hou->fireEff[1] = hou->fireEff[2] = hou->fireEff[3] = -1;
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        coinNum[i] = 0;
        if(player->enableF) {
            coin = MBPlayerCoinGet(i);
            if(coin > 1) {
                coinNum[i] = -(coin >> 1);
            }
        }
    }
    MBCoinAddAllDispExec(coinNum[0], coinNum[1], coinNum[2], coinNum[3], TRUE);
    MBAudFXPlay(713);
    MBWinCreate(2, MESSNUM(MESS_BOARD_W07, 10), 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    cameraPos = pos;
    cameraPos.z -= 80;
    for(i=0; i<100; i++) {
        pos.z += 0.15f*(cameraPos.z-pos.z);
        MBModelPosSetV(koopa->mdlId[0], &pos);
        if(i == 65) {
            MBCameraQuakeSet(18, 50);
            MBAudFXPlay(716);
        }
        HuPrcVSleep();
    }
    MBMotionSpeedSet(koopa->mdlId[0], 0);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        if(player->enableF) {
            player->mode = -1;
        }
    }
    MB7Ev_HouPlayerUpdate();
    MB7Ev_KoopaClose();
    MBCameraFocusPlayerSet(playerNo);
    MBCameraSkipSet(FALSE);
    MBCameraZoomSet(2000);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
}

/* 214 insns */
static void MB7Ev_HouPlayerUpdate(void)
{
    MB7EV_HOU *hou;
    MB7EV_PLAYER *player;
    int i;
    MASU *masu;
    float absDiff;

    hou = &mb7_Work.hou;
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        if(player->enableF == 0) {
            continue;
        }
        masu = MBMasuGet(MASU_LAYER_DEFAULT, player->masuId);
        switch(player->mode) {
            case 0:
                player->motId = MBPlayerMotionCreate(i, CHARMOT_HSF_c000m1_321);
                MBPlayerPosGet(i, &player->pos);
                MBPlayerRotGet(i, &player->rot);
                player->unk04 = -1;
                player->mode++;
                break;

            case 1:
                if(hou->charge < 0.8f) {
                    break;
                }
                absDiff = fabsf2(MB7_AngleDiff(180.0 * (atan2(player->pos.x - hou->pos.x,
                                                             player->pos.z - hou->pos.z) / M_PI),
                                               hou->angleY));
                if(absDiff > 10) {
                    break;
                }
                omVibrate(i, 12, 4, 2);
                MBPlayerMotionNoShiftSet(i, player->motId, 0, 8, HU3D_MOTATTR_LOOP);
                MBPlayerWinLoseVoicePlay(i, 1, 505);
                player->vel.y = 32.666668f;
                player->step = 0;
                player->mode++;
                /* falls through */

            case 2:
                player->vel.y += -0.8166667f;
                PSVECAdd(&player->pos, &player->vel, &player->pos);
                if(player->pos.y > masu->pos.y) {
                    break;
                }
                player->pos.y = masu->pos.y;
                player->vel.y *= -0.7f;
                player->step++;
                omVibrate(i, 12, 4, 2);
                if(player->step >= 2) {
                    player->vel.y = 0;
                    player->mode++;
                    MBPlayerMotionNoShiftSet(i, 6, 0, 8, HU3D_MOTATTR_LOOP);
                }
                break;

            case 3:
                break;

            case -1:
                MBPlayerMotionNoSet(i, 1, HU3D_MOTATTR_LOOP);
                MBPlayerMotionKill(i, player->motId);
                player->motId = -1;
                player->rot.y = 0;
                break;
        }
        MBPlayerPosSetV(i, &player->pos);
        MBPlayerRotSetV(i, &player->rot);
    }
}

/* 37 insns */
void MB7Ev_KoopaInit(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    int i;

    memset(koopa, 0, sizeof(MB7EV_KOOPA));
    koopa->motNo = -1;
    koopa->mdlId[0] = koopa->mdlId[1] = koopa->mdlId[2] = koopa->mdlId[3] = MB_MODEL_NONE;
    for(i=0; i<MB7EV_KOOPAMOT_MAX; i++) {
        koopa->motId[i] = -1;
    }
    koopa->dataStatId = MBDataDirReadAsync(DATA_capsulechar4);
}

/* 31 insns */
void MB7Ev_KoopaCreate(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    MBDataAsyncWait(koopa->dataStatId);
    koopa->mdlId[0] = MBModelCreate(CAPSULECHAR4_HSF_koopa, NULL, TRUE);
    MBModelDispSet(koopa->mdlId[0], FALSE);
    HuPrcVSleep();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_IDLE);
    MB7Ev_KoopaMotionNoSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    HuPrcVSleep();
}

/* 0x130 */ static u32 mb7ev_KupaMotFileTbl[9] = { DATANUM(DATA_capsulechar4, 1), DATANUM(DATA_capsulechar4, 2), DATANUM(DATA_capsulechar4, 3), DATANUM(DATA_capsulechar4, 4), DATANUM(DATA_capsulechar4, 5), DATANUM(DATA_capsulechar4, 7), DATANUM(DATA_capsulechar4, 6), DATANUM(DATA_capsulechar4, 13), DATANUM(DATA_capsulechar4, 16) };

/* 31 insns */
void MB7Ev_KoopaMotionCreate(int motNo)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    if(koopa->motId[motNo] < 0) {
        koopa->motId[motNo] = MBMotionCreate(koopa->mdlId[0], mb7ev_KupaMotFileTbl[motNo]);
    }
}

/* 14 insns */
void MB7Ev_KoopaDataClose(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    HuDataDirClose(koopa->dataStatId);
}

/* 35 insns */
void MB7Ev_KoopaMotionNoSet(int motNo, BOOL loopF)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    u32 attr = HU3D_MOTATTR_NONE;

    if(loopF) {
        attr = HU3D_MOTATTR_LOOP;
        if(motNo == koopa->motNo) {
            return;
        }
    }
    MBMotionNoSet(koopa->mdlId[0], koopa->motId[motNo], attr);
    koopa->motNo = motNo;
}

/* 41 insns */
void MB7Ev_KoopaMotionShiftSet(int motNo, BOOL loopF)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    u32 attr = HU3D_MOTATTR_NONE;

    if(loopF) {
        attr = HU3D_MOTATTR_LOOP;
        if(motNo == koopa->motNo) {
            return;
        }
    }
    MBMotionShiftSet(koopa->mdlId[0], koopa->motId[motNo], 0, 8, attr);
    koopa->motNo = motNo;
}

/* 22 insns */
BOOL MB7Ev_KoopaMotionCheck(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    if(MBMotionShiftIDGet(koopa->mdlId[0]) >= 0) {
        return FALSE;
    }
    return MBMotionEndCheck(koopa->mdlId[0]);
}

/* 33 insns */
void MB7Ev_KoopaClose(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    int i;

    for(i=0; i<4; i++) {
        if(koopa->mdlId[i] >= 0) {
            MBModelKill(koopa->mdlId[i]);
        }
        koopa->mdlId[i] = MB_MODEL_NONE;
    }
}

/* 776 insns */
void MB7Ev_KoopaFire1Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF dir;
    HuVecF pos;
    HuVecF vec;
    float value;
    float rate;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>3);
        }
        effP->count = 1;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = -0.15f;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&dir, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            value = rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF())));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->parManId = 20;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate);
            if(data->pos.y > 0) {
                data->pos.y *= 1+(3*MBEffRandF());
            }
            PSVECAdd(&pos, &data->pos, &data->pos);
            data->accel.x = 100+(80*MBEffRandF());
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(30+(30*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.95f;
        data->vel.z *= 0.95f;
        if(data->pos.y > pos.y+(50*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(90*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 683 insns */
void MB7Ev_KoopaFire2Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF dir;
    HuVecF pos;
    HuVecF vec;
    float value;
    float rate;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = -0.15f;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&dir, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            value = MBEffRandF();
            data->color.r = data->color.g = data->color.b = 255;
            data->color.r = 128+(127*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            value = rate*(1.3333334f+(1.6666666f*(1.2f*MBEffRandF())));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate);
            if(data->pos.y > 0) {
                data->pos.y *= 1+(2*MBEffRandF());
            }
            PSVECAdd(&pos, &data->pos, &data->pos);
            data->accel.x = rate*(50+(70*MBEffRandF()));
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(40+(60*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 1.088889f*data->accel.y;
        data->vel.x *= 0.95f;
        data->vel.z *= 0.95f;
        if(data->pos.y > pos.y+(50*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 859 insns */
void MB7Ev_KoopaFire3Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF vel;
    HuVecF pos;
    HuVecF firePos;
    HuVecF dir;
    HuVecF vec;
    float value;
    float rate;
    float power;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = 0;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&vel, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    firePos = hou->firePos;
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            power = HuSin(90*MBEffRandF());
            value = (0.7f+(0.3f*power))*(rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF()))));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->vel.y += rate*(-2.5f-(1.6666666f*MBEffRandF()));
            value = 1-(0.7f*power);
            PSVECScale(&dir, &vel, 1.6666666f*(7*(value*rate)));
            PSVECAdd(&vel, &data->vel, &data->vel);
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate*power);
            PSVECScale(&dir, &vel, 100*(1.8f*(power*hou->charge)));
            PSVECAdd(&firePos, &data->pos, &data->pos);
            PSVECAdd(&vel, &data->pos, &data->pos);
            data->accel.x = 80+(80*MBEffRandF());
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(30+(30*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.98f;
        data->vel.z *= 0.98f;
        if(data->pos.y > pos.y+(50*0.6f*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(50*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 862 insns */
void MB7Ev_KoopaFire4Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF vel;
    HuVecF pos;
    HuVecF firePos;
    HuVecF dir;
    HuVecF vec;
    float value;
    float rate;
    float power;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = 0;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&vel, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    firePos = hou->firePos;
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            power = HuSin(90*MBEffRandF());
            value = (0.7f+(0.3f*power))*(rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF()))));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->vel.y += rate*(-2.1666665f-(1.6666666f*MBEffRandF()));
            value = 1-(0.7f*power);
            PSVECScale(&dir, &vel, 1.6666666f*(7*(value*rate)));
            PSVECAdd(&vel, &data->vel, &data->vel);
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate*power);
            PSVECScale(&dir, &vel, 100*(1.8f*(power*hou->charge)));
            PSVECAdd(&firePos, &data->pos, &data->pos);
            PSVECAdd(&vel, &data->pos, &data->pos);
            data->accel.x = rate*(50+(60*MBEffRandF()));
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(40+(40*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.98f;
        data->vel.z *= 0.98f;
        if(data->pos.y > pos.y+(50*0.6f*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(50*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 47 insns */
float MB7_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3)
{
    float mag = VECMag(vec3);
    if(mag > 0) {
        mag = ((vec3->x*(vec1->x-vec2->x))+(vec3->y*(vec1->y-vec2->y))+(vec3->z*(vec1->z-vec2->z)))/mag;
    }
    return mag;
}

/* 45 insns */
float MB7_AngleDiff(float start, float end)
{
    float angle = fmodf(end-start, 360);
    if(angle < 0) {
        angle += 360;
    }
    if(angle > 180) {
        angle -= 360;
    }
    return angle;
}

/* 30 insns */
unsigned int MB7Ev_BitGet(int outMask, unsigned int inMask)
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

/* 29 insns */
unsigned int MB7Ev_MasuFlagGet(int outMask, unsigned int inMask)
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

