/*
 * sd00dll rabbit.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/rabbit.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "game/frand.h"
#include "game/esprite.h"
#include "game/mg/seqman.h"
#include "humath.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x494 */ static SDFLAGWORK rabbitBaseModel;
/* 0x434 */ static SDRABBITTRANSFORM rabbitTransform;
/* 0x428 */ static s32 rabbitMode[3];
/* 0x424 */ static s32 rabbitIdleTimer;
/* 0x420 */ static s32 rabbitIdleTimerMax;
/* 0x41C */ static s32 randomMoveTimer;
/* 0x414 */ static s32 rabbitImpactTimer[2];
/* 0x410 */ static s32 rabbitOverridePos;
/* 0x404 */ static s32 rabbitShrinkTimer[3];
/* 0x400 */ float lbl_1_bss_400;
/* 0x3FC */ float lbl_1_bss_3FC;
/* 0x3F8 */ float lbl_1_bss_3F8;
/* 0x3F4 */ float lbl_1_bss_3F4;
/* 0x3F0 */ float lbl_1_bss_3F0;
/* 0x3EC */ float lbl_1_bss_3EC;
/* 0x3E8 */ float lbl_1_bss_3E8;
/* 0x3DC */ static HuVecF rabbitScale;
/* 0x3D4 */ static s32 rabbitEffectFadeTimer[2]; /* dtk sizes it 4 + an unreferenced 0x3D8: [1] is accessed */
/* 0x3D0 */ static s32 rabbitEffectTimer;
/* 0x3CC */ static float rabbitSpeed;
/* 0x3C0 */ static HuVecF rabbitZAxis;
/* 0x2F8 */ static SDRABBITPART rabbitModelData[5];
/* 0x2BC */ static HuVecF rabbitRot[5];
/* 0x2B8 */ static float rabbitFadeTimer;
/* 0x2B4 */ static s32 rabbitDispTimer;
/* 0x2B2 gap_05_000002B2_bss (0x2): alignment gap */
/* 0x2B0 */ static HU3DMODELID rabbitEffectMdlId;

static void RabbitModeMove(void);
static s32 RabbitStageEdgeCheck(HuVecF pos);
static void RabbitRotUpdate(void);
static s32 RabbitImpactDirGet(void);
static s32 RabbitShrinkCheck(void);
static void RabbitEffectCreate(void);
static void RabbitEffectHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
static void RabbitEffectPosSet(void);
static void RabbitEffectUpdate(s32 mode);

/* --- functions (reference order), .data placed before its first user --- */
/* 157 insns */
void SdRabbitInit(void)
{
    s32 i;
    s32 j;
    if(sys->gameType == 2) {
        rabbitMode[0] = 0;
        rabbitMode[1] = 0;
        rabbitMode[2] = 0;
        lbl_1_bss_400 = 0.0f;
        rabbitBaseModel.mdlId = -1;
        for(i=0; i<2; i++) {
            rabbitBaseModel.score[i] = 0;
            for(j=0; j<3; j++) {
                rabbitBaseModel.sprId[i][j] = -1;
            }
        }
        rabbitBaseModel.pos = (HuVecF){ 0, 0, 0 };
        RabbitEffectCreate();
        MTXIdentity(rabbitTransform.mtx);
        rabbitTransform.ofs[0] = (HuVecF){ 62, 0, 69 };
        rabbitTransform.ofs[1] = (HuVecF){ -62, 0, 69 };
        rabbitTransform.ofs[2] = (HuVecF){ 62, 0, -69 };
        randomMoveTimer = 0;
        lbl_1_bss_3F8 = (frandmod(2)) ? 1.0f : -1.0f;
    }
}

/* 657 insns */
void SdRabbitUpdate(void)
{
    Mtx rotMtx;
    s32 i;
    s32 j;
    s32 k;
    if(sys->gameType == 2 && MgSeqModeGet() >= 5) {
        switch(rabbitMode[0]) {
            case 0:
                if(rabbitBaseModel.mdlId == -1) {
                    rabbitBaseModel.mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 105), HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelCameraSet(rabbitBaseModel.mdlId, 3);
                    Hu3DModelAttrSet(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelLayerSet(rabbitBaseModel.mdlId, 3);
                    if(rabbitBaseModel.mdlId != -1) {
                        for(i=0; i<5; i++) {
                            rabbitModelData[i].mdlId = Hu3DModelLink(rabbitBaseModel.mdlId);
                            Hu3DModelCameraSet(rabbitModelData[i].mdlId, 3);
                            Hu3DModelAttrSet(rabbitModelData[i].mdlId, HU3D_ATTR_DISPOFF);
                            rabbitFadeTimer = 1.0f;
                            Hu3DModelTPLvlSet(rabbitModelData[i].mdlId, (rabbitFadeTimer-((rabbitFadeTimer/5.0f)*i))/4.0f);
                            Hu3DModelLayerSet(rabbitModelData[i].mdlId, 3);
                        }
                        RabbitEffectUpdate(-1);
                    }
                    rabbitDispTimer = 0;
                }
                if(SdFlagPosSet(&rabbitBaseModel)) {
                    rabbitMode[0] = 11;
                    lbl_1_bss_3F4 = 1.0f;
                    lbl_1_bss_3F0 = 2000.0f;
                    Hu3DModelPosSet(rabbitBaseModel.mdlId, rabbitBaseModel.pos.x, rabbitBaseModel.pos.y+lbl_1_bss_3F0, rabbitBaseModel.pos.z);
                    Hu3DModelAttrReset(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
                    for(j=4; j>=0; j--) {
                        rabbitModelData[j].pos = rabbitBaseModel.pos;
                        rabbitRot[j] = (HuVecF){ 0, 0, 0 };
                    }
                }
                break;
            case 1:
                RabbitModeMove();
                RabbitEffectUpdate(0);
                break;
            case 2:
                if(rabbitBaseModel.unk10 != 0) {
                    rabbitMode[0] = 10;
                    lbl_1_bss_3EC = 1.0f;
                    rabbitScale = (HuVecF){ 1, 1, 1 };
                    rabbitShrinkTimer[0] = rabbitShrinkTimer[1] = rabbitShrinkTimer[2] = 0;
                } else {
                    rabbitMode[0] = 3;
                }
                break;
            case 3:
                if(SdFlagPosSet(&rabbitBaseModel)) {
                    if(rabbitBaseModel.unk10 != 0) {
                        rabbitMode[0] = 11;
                        lbl_1_bss_3F0 = 2000.0f;
                        Hu3DModelPosSet(rabbitBaseModel.mdlId, rabbitBaseModel.pos.x, rabbitBaseModel.pos.y+lbl_1_bss_3F0, rabbitBaseModel.pos.z);
                        Hu3DModelAttrReset(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
                    } else if(rabbitOverridePos == 0) {
                        SdImpactSoundStart(0x56B, rabbitBaseModel.pos, 1.0f);
                        rabbitMode[0] = 12;
                        rabbitEffectTimer = 0;
                    }
                    rabbitMode[2] = 1;
                    for(k=4; k>=0; k--) {
                        rabbitModelData[k].pos = rabbitBaseModel.pos;
                        rabbitRot[k] = (HuVecF){ 0, 0, 0 };
                    }
                }
                break;
            case 10:
                if(RabbitShrinkCheck()) {
                    lbl_1_bss_3EC -= 0.02f;
                    if(lbl_1_bss_3EC < 0.0f) {
                        lbl_1_bss_3EC = 0.0f;
                    }
                    Hu3DModelTPLvlSet(rabbitBaseModel.mdlId, lbl_1_bss_3EC);
                    if(0.0f == lbl_1_bss_3EC) {
                        if(rabbitBaseModel.score[0] == 3 || rabbitBaseModel.score[1] == 3) {
                            rabbitMode[0] = 99;
                        } else {
                            rabbitMode[0] = 3;
                        }
                        lbl_1_bss_3F4 = 1.0f;
                        Hu3DModelScaleSet(rabbitBaseModel.mdlId, lbl_1_bss_3F4, lbl_1_bss_3F4, lbl_1_bss_3F4);
                        Hu3DModelAttrSet(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
                        Hu3DModelTPLvlSet(rabbitBaseModel.mdlId, 1.0f);
                        rabbitMode[1] = 0;
                        RabbitEffectUpdate(-1);
                    }
                }
                break;
            case 11:
                Hu3DModelPosSet(rabbitBaseModel.mdlId, rabbitBaseModel.pos.x, rabbitBaseModel.pos.y+lbl_1_bss_3F0, rabbitBaseModel.pos.z);
                lbl_1_bss_3F0 -= 10.0f;
                if(lbl_1_bss_3F0 < 0.0f) {
                    lbl_1_bss_3F0 = 0.0f;
                }
                if(0.0f == lbl_1_bss_3F0) {
                    rabbitBaseModel.unk10 = 0;
                    rabbitMode[0] = 1;
                }
                Hu3DModelRotSet(rabbitBaseModel.mdlId, 0.0f, 0.0f, 0.0f);
                break;
            case 12:
                if(++rabbitEffectTimer == 3) {
                    RabbitEffectPosSet();
                }
                lbl_1_bss_3F4 += 0.05f;
                if(lbl_1_bss_3F4 > 1.0f) {
                    lbl_1_bss_3F4 = 1.0f;
                }
                Hu3DModelScaleSet(rabbitBaseModel.mdlId, lbl_1_bss_3F4, lbl_1_bss_3F4, lbl_1_bss_3F4);
                if(1.0f == lbl_1_bss_3F4) {
                    rabbitMode[0] = 1;
                }
                MTXRotRad(rotMtx, 'y', 0.7853982f);
                MTXConcat(rabbitTransform.mtx, rotMtx, rabbitTransform.mtx);
                MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
                Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
                break;
            case 99:
                break;
        }
        SdFlagSprUpdate(&rabbitBaseModel);
    }
}

/* 73 insns */
void SdRabbitClose(void)
{
    s32 i;
    s32 j;
    if(sys->gameType == 2) {
        if(rabbitBaseModel.mdlId != -1) {
            for(j=0; j<5; j++) {
                Hu3DModelKill(rabbitModelData[j].mdlId);
            }
        }
        if(rabbitBaseModel.mdlId != -1) {
            Hu3DModelKill(rabbitBaseModel.mdlId);
        }
        for(i=0; i<2; i++) {
            for(j=0; j<3; j++) {
                if(rabbitBaseModel.sprId[i][j] != -1) {
                    espKill(rabbitBaseModel.sprId[i][j]);
                }
            }
        }
        Hu3DModelKill(rabbitEffectMdlId);
    }
}

/* 756 insns */
static void RabbitModeMove(void)
{
    Mtx rotMtx;
    Mtx rotMtx2;
    Mtx rotMtx3;
    HuVecF zAxis;
    HuVecF vel;
    HuVecF newPos;
    float speed;
    s32 i;
    s32 moveF = FALSE;
    switch(rabbitMode[2]) {
        case 0:
            rabbitMode[2]++;
            break;
        case 1:
            if(randomMoveTimer == 0) {
                randomMoveTimer = frandmod(12)*10;
            }
            if(sys->machine[0].gunNo == 7 || sys->machine[1].gunNo == 7) {
                MTXRotRad(rotMtx, 'y', MTXDegToRad(randomMoveTimer));
                MTXConcat(rabbitTransform.mtx, rotMtx, rabbitTransform.mtx);
                MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
                Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
                randomMoveTimer = 0;
                moveF = TRUE;
            } else {
                MTXRotRad(rotMtx2, 'y', 0.05235988f);
                MTXConcat(rabbitTransform.mtx, rotMtx2, rabbitTransform.mtx);
                MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
                Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
                if(--randomMoveTimer <= 0) {
                    randomMoveTimer = 0;
                    moveF = TRUE;
                }
            }
            break;
        case 2:
            if(lbl_1_bss_3FC > 1000.0f) {
                moveF = TRUE;
            }
            break;
        case 3:
            if(lbl_1_bss_3FC > 2000.0f) {
                moveF = TRUE;
            }
            break;
        case 4:
            if(rabbitIdleTimer > rabbitIdleTimerMax) {
                moveF = TRUE;
            }
            break;
        case 5:
            if(++rabbitEffectTimer == 3) {
                RabbitEffectPosSet();
            }
            lbl_1_bss_3F4 -= 0.05f;
            if(lbl_1_bss_3F4 < 0.0f) {
                lbl_1_bss_3F4 = 0.0f;
            }
            Hu3DModelScaleSet(rabbitBaseModel.mdlId, lbl_1_bss_3F4, lbl_1_bss_3F4, lbl_1_bss_3F4);
            if(0.0f == lbl_1_bss_3F4) {
                rabbitImpactTimer[0] = rabbitImpactTimer[1] = 0;
                rabbitMode[0] = 2;
                rabbitBaseModel.pos.y = -1000.0f;
                Hu3DModelPosSetV(rabbitBaseModel.mdlId, &rabbitBaseModel.pos);
            }
            MTXRotRad(rotMtx3, 'y', 0.7853982f);
            MTXConcat(rabbitTransform.mtx, rotMtx3, rabbitTransform.mtx);
            MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
            Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
            return;
    }
    if(moveF) {
        lbl_1_bss_3E8 = lbl_1_bss_400;
        lbl_1_bss_400 = (frandmod(3)*2)+3;
        lbl_1_bss_3FC = 0.0f;
        rabbitIdleTimerMax = (frandmod(3)*30)+60;
        rabbitIdleTimer = 0;
        if(rabbitMode[2] == 1) {
            rabbitMode[2]++;
        } else if(sys->machine[0].gunNo == 7 || sys->machine[1].gunNo == 7) {
            rabbitMode[2] = frandmod(3)+1;
        } else {
            rabbitMode[2] = frandmod(4)+1;
            if(rabbitMode[2] == 4) {
                lbl_1_bss_400 = -2.0f;
            }
        }
        if(-2.0f == lbl_1_bss_400 || (lbl_1_bss_3E8 >= 0.0f && lbl_1_bss_400-lbl_1_bss_3E8 >= 2.0f)) {
            SdImpactSoundStart(((rand8()%4)*2)+0x56D, rabbitBaseModel.pos, 1.0f);
        }
        lbl_1_bss_3F8 = (frandmod(2)) ? 1.0f : -1.0f;
    } else {
        if(rabbitMode[2] != 4) {
            speed = (100.0f*(2.0f+lbl_1_bss_400))/60.0f;
            lbl_1_bss_3FC += speed;
            zAxis = (HuVecF){ rabbitTransform.mtx[0][2], rabbitTransform.mtx[1][2], rabbitTransform.mtx[2][2] };
            VECScale(&zAxis, &vel, speed);
            VECAdd(&rabbitBaseModel.pos, &vel, &newPos);
            rabbitSpeed = speed;
            rabbitZAxis = zAxis;
            if(RabbitStageEdgeCheck(newPos)) {
                rabbitBaseModel.pos = newPos;
                rabbitBaseModel.pos.y = SdStageDistCalc(rabbitBaseModel.pos);
                Hu3DModelPosSetV(rabbitBaseModel.mdlId, &rabbitBaseModel.pos);
            } else {
                rabbitMode[2] = 1;
            }
        } else {
            rabbitIdleTimer++;
        }
        if(RabbitImpactDirGet() == -1 && rabbitOverridePos == 0) {
            rabbitMode[2] = 5;
            SdImpactSoundStart(0x569, rabbitBaseModel.pos, 1.0f);
            rabbitEffectTimer = 0;
        }
        RabbitRotUpdate();
    }
    if(rabbitDispTimer == 0) {
        for(i=4; i>=0; i--) {
            if(i == 0) {
                rabbitModelData[i].pos = rabbitBaseModel.pos;
                rabbitRot[i] = rabbitTransform.rot;
            } else {
                rabbitModelData[i].pos = rabbitModelData[i-1].pos;
                rabbitRot[i] = rabbitRot[i-1];
            }
            Hu3DModelPosSet(rabbitModelData[i].mdlId, rabbitModelData[i].pos.x, rabbitModelData[i].pos.y, rabbitModelData[i].pos.z);
            Hu3DModelRotSetV(rabbitModelData[i].mdlId, &rabbitRot[i]);
            Hu3DModelTPLvlSet(rabbitModelData[i].mdlId, (rabbitFadeTimer-((rabbitFadeTimer/5.0f)*i))/4.0f);
            if(rabbitMode[2] != 5) {
                Hu3DModelAttrReset(rabbitModelData[i].mdlId, HU3D_ATTR_DISPOFF);
            }
        }
    }
    rabbitDispTimer++;
    if(rabbitDispTimer == 15) {
        rabbitDispTimer = 0;
    }
}

/* 61 insns */
static s32 RabbitStageEdgeCheck(HuVecF pos)
{
    s32 result = FALSE;
    if(SdStageEdgeDistGet(pos) >= 200.0f && SdStageRadiusCalc() < SdStageDistCalc(pos) && !SdStageBaseObjHitCheck(pos, 69.0f)) {
        result = TRUE;
    }
    return result;
}

/* 172 insns */
static void RabbitRotUpdate(void)
{
    HuVecF corner[3];
    Mtx mtx;
    HuVecF xAxis;
    HuVecF yAxis;
    HuVecF zAxis;
    s32 i;
    for(i=0; i<3; i++) {
        MTXTrans(mtx, rabbitTransform.ofs[i].x, rabbitTransform.ofs[i].y, rabbitTransform.ofs[i].z);
        MTXConcat(rabbitTransform.mtx, mtx, mtx);
        corner[i] = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        VECAdd(&corner[i], &rabbitBaseModel.pos, &corner[i]);
    }
    for(i=0; i<3; i++) {
        corner[i].y = SdStageDistCalc(corner[i]);
    }
    VECSubtract(&corner[0], &corner[2], &zAxis);
    VECNormalize(&zAxis, &zAxis);
    VECSubtract(&corner[1], &corner[0], &xAxis);
    VECNormalize(&xAxis, &xAxis);
    VECCrossProduct(&xAxis, &zAxis, &yAxis);
    VECNormalize(&yAxis, &yAxis);
    VECCrossProduct(&yAxis, &zAxis, &xAxis);
    VECNormalize(&xAxis, &xAxis);
    rabbitTransform.mtx[0][0] = xAxis.x;
    rabbitTransform.mtx[1][0] = xAxis.y;
    rabbitTransform.mtx[2][0] = xAxis.z;
    rabbitTransform.mtx[0][1] = yAxis.x;
    rabbitTransform.mtx[1][1] = yAxis.y;
    rabbitTransform.mtx[2][1] = yAxis.z;
    rabbitTransform.mtx[0][2] = zAxis.x;
    rabbitTransform.mtx[1][2] = zAxis.y;
    rabbitTransform.mtx[2][2] = zAxis.z;
    MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
    Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
}

/* 504 insns */
static s32 RabbitImpactDirGet(void)
{
    SDMACHINE *machine1;
    SDMACHINE *machine2;
    HuVecF p1Pos;
    HuVecF p2Pos;
    HuVecF dir;
    Mtx rotMtx;
    float dist;
    s32 i;
    s32 result = 0;
    machine1 = &sys->machine[0];
    machine2 = &sys->machine[1];
    p1Pos = machine1->pos;
    p2Pos = machine2->pos;
    VECSubtract(&p1Pos, &rabbitBaseModel.pos, &dir);
    dist = VECMag(&dir);
    if(dist <= 300.0f+machine1->unk358) {
        if(0.0f == VECMag(&dir)) {
            dir = (HuVecF){ 1, 1, 1 };
        }
        VECNormalize(&dir, &dir);
        MTXRotRad(rotMtx, 'y', MTXDegToRad(120.0f*lbl_1_bss_3F8));
        MTXMultVec(rotMtx, &dir, &dir);
        MathPlaneRotMtxGet(&dir, NULL, 0.0f, rabbitTransform.mtx);
        MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
        Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
        rabbitImpactTimer[0]++;
        lbl_1_bss_400 = 18.0f;
        result = (rabbitImpactTimer[0] > 30) ? -1 : 1;
    } else {
        rabbitImpactTimer[0] = 0;
        if(HuPadBtn[machine1->unk348] & PAD_BUTTON_B) {
            if(machine1->gunNo == 1 || machine1->gunNo == 5 || machine1->gunNo == 10) {
                if(dist <= 1200.0f+machine1->unk358) {
                    result = (frandmod(3)) ? result : -1;
                }
            } else {
                if(0.0f == VECMag(&dir)) {
                    dir = (HuVecF){ 1, 1, 1 };
                }
                VECNormalize(&dir, &dir);
                MTXRotRad(rotMtx, 'y', MTXDegToRad(90.0f*lbl_1_bss_3F8));
                MTXMultVec(rotMtx, &dir, &dir);
                MathPlaneRotMtxGet(&dir, NULL, 0.0f, rabbitTransform.mtx);
                MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
                Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
                lbl_1_bss_400 = (frandmod(2)) ? 10.0f : 8.0f;
            }
        }
    }
    VECSubtract(&p2Pos, &rabbitBaseModel.pos, &dir);
    dist = VECMag(&dir);
    if(dist <= 300.0f+machine2->unk358) {
        if(0.0f == VECMag(&dir)) {
            dir = (HuVecF){ 1, 1, 1 };
        }
        VECNormalize(&dir, &dir);
        MTXRotRad(rotMtx, 'y', MTXDegToRad(120.0f*lbl_1_bss_3F8));
        MTXMultVec(rotMtx, &dir, &dir);
        MathPlaneRotMtxGet(&dir, NULL, 0.0f, rabbitTransform.mtx);
        MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
        Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
        rabbitImpactTimer[1]++;
        lbl_1_bss_400 = 18.0f;
        result = (rabbitImpactTimer[1] > 30) ? -1 : ((result == 0) ? 1 : result);
    } else {
        rabbitImpactTimer[1] = 0;
        if(HuPadBtn[machine2->unk348] & PAD_BUTTON_B) {
            if(machine2->gunNo == 1 || machine2->gunNo == 5 || machine2->gunNo == 10) {
                if(dist <= 1200.0f+machine2->unk358) {
                    result = (frandmod(3)) ? result : -1;
                }
            } else {
                if(0.0f == VECMag(&dir)) {
                    dir = (HuVecF){ 1, 1, 1 };
                }
                VECNormalize(&dir, &dir);
                MTXRotRad(rotMtx, 'y', MTXDegToRad(90.0f*lbl_1_bss_3F8));
                MTXMultVec(rotMtx, &dir, &dir);
                MathPlaneRotMtxGet(&dir, NULL, 0.0f, rabbitTransform.mtx);
                MathMtxRotGet(rabbitTransform.mtx, &rabbitTransform.rot);
                Hu3DModelRotSetV(rabbitBaseModel.mdlId, &rabbitTransform.rot);
                lbl_1_bss_400 = (frandmod(2)) ? 10.0f : 8.0f;
            }
        }
    }
    if(result == -1) {
        for(i=0; i<5; i++) {
            Hu3DModelAttrSet(rabbitModelData[i].mdlId, HU3D_ATTR_DISPOFF);
        }
    }
    return result;
}

/* 114 insns */
static s32 RabbitShrinkCheck(void)
{
    s32 result = FALSE;
    s32 i;
    if(rabbitShrinkTimer[0]) {
        Hu3DModelAttrReset(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(rabbitBaseModel.mdlId, HU3D_ATTR_DISPOFF);
    }
    if(++rabbitShrinkTimer[1] == 2) {
        rabbitShrinkTimer[0] ^= 1;
        rabbitShrinkTimer[1] = 0;
        rabbitShrinkTimer[2]++;
    }
    if(rabbitShrinkTimer[2] > 11) {
        rabbitScale.x -= 0.03f;
        if(rabbitScale.x < 0.0f) {
            rabbitScale.x = 0.0f;
        }
        rabbitScale.z = rabbitScale.x;
        rabbitScale.y += 0.05f;
        Hu3DModelScaleSetV(rabbitBaseModel.mdlId, &rabbitScale);
        result = TRUE;
    }
    for(i=0; i<5; i++) {
        Hu3DModelAttrSet(rabbitModelData[i].mdlId, HU3D_ATTR_DISPOFF);
    }
    return result;
}

/* 87 insns */
static void RabbitEffectCreate(void)
{
    rabbitEffectMdlId = Hu3DParticleCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 139), HU_MEMNUM_OVL, HEAP_MODEL)), 30);
    Hu3DModelPosSet(rabbitEffectMdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(rabbitEffectMdlId, 0.2f, 0.2f, 0.2f);
    Hu3DModelLayerSet(rabbitEffectMdlId, 5);
    Hu3DModelCameraSet(rabbitEffectMdlId, 3);
    Hu3DParticleTPLvlSet(rabbitEffectMdlId, 0.1f);
    Hu3DParticleScaleSet(rabbitEffectMdlId, 0.0f);
    Hu3DParticleHookSet(rabbitEffectMdlId, RabbitEffectHook);
    RabbitEffectUpdate(1);
    rabbitOverridePos = 0;
    rabbitImpactTimer[0] = rabbitImpactTimer[1] = 0;
}

/* 188 insns */
static void RabbitEffectHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 num;
    float angle;
    float radius;
    num = 0;
    if(rabbitOverridePos) {
        data = particle->data;
        for(i=0; i<particle->maxCnt; i++, data++) {
            data->cameraBit = 3;
            if(0.0f == data->scale) {
                data->pos.x = data->pos.y = data->pos.z = 0.0f;
                angle = ((frand() & 0xFF)*360)/256;
                radius = frand() & 0x1F;
                data->vel.x = radius*HuSin(angle);
                data->vel.y = 50.0f+(frand() & 0x1F);
                data->vel.z = radius*HuCos(angle);
                data->scale = 300.0f;
            }
        }
        data = particle->data;
        for(i=0; i<particle->maxCnt; i++, data++) {
            if(data->scale) {
                VECAdd(&data->vel, &data->pos, &data->pos);
                data->vel.x *= 0.999f;
                data->vel.y -= 3.0f;
                data->vel.z *= 0.999f;
                data->scale -= 3.0f;
                if(data->scale <= 0.0f) {
                    data->scale = 0.0f;
                }
            }
            if(0.0f == data->scale) {
                num++;
            }
        }
        if(num == particle->maxCnt) {
            rabbitOverridePos = 0;
        }
        DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
    }
}

/* 18 insns */
static void RabbitEffectPosSet(void)
{
    rabbitOverridePos = 1;
    Hu3DModelPosSetV(rabbitEffectMdlId, &rabbitBaseModel.pos);
}

/* 236 insns */
static void RabbitEffectUpdate(s32 mode)
{
    u8 rTbl[8] = { 0xFF, 0x96, 0x46, 0xC8, 0x5A, 0xAA, 0x96, 0x5A };
    u8 gTbl[8] = { 0xFF, 0x78, 0x46, 0x8C, 0xAA, 0x8C, 0xB4, 0x50 };
    u8 bTbl[8] = { 0xFF, 0x64, 0x5A, 0x50, 0xBE, 0x6E, 0xB4, 0x64 };
    s32 stageNo;
    s32 i;
    u8 r;
    u8 g;
    u8 b;
    s32 stageF;
    stageF = FALSE;
    if(sys->stageNo >= 1 && sys->stageNo <= 7) {
        stageF = TRUE;
    }
    stageNo = (stageF) ? sys->stageNo : 0;
    if(mode == 0) {
        if(stageNo > 0) {
            if(rabbitEffectFadeTimer[1] <= 60) {
                rabbitEffectFadeTimer[0]++;
                if(rabbitEffectFadeTimer[0] >= 40) {
                    rabbitEffectFadeTimer[0] = 0;
                    rabbitEffectFadeTimer[1]++;
                }
            }
            r = 255-(((255-rTbl[stageNo])*rabbitEffectFadeTimer[1])/60);
            g = 255-(((255-gTbl[stageNo])*rabbitEffectFadeTimer[1])/60);
            b = 255-(((255-bTbl[stageNo])*rabbitEffectFadeTimer[1])/60);
            LightColorSet(rabbitBaseModel.mdlId, 255, r, g, b);
            for(i=0; i<5; i++) {
                LightColorSet(rabbitModelData[i].mdlId, 255, r, g, b);
            }
        }
    } else if(mode == 1) {
        Hu3DParticleColSet(rabbitEffectMdlId, rTbl[stageNo], gTbl[stageNo], bTbl[stageNo]);
    } else if(mode == -1) {
        rabbitEffectFadeTimer[0] = rabbitEffectFadeTimer[1] = 0;
        LightColorSet(rabbitBaseModel.mdlId, 255, rTbl[0], gTbl[0], bTbl[0]);
        for(i=0; i<5; i++) {
            LightColorSet(rabbitModelData[i].mdlId, 255, rTbl[0], gTbl[0], bTbl[0]);
        }
    }
}

/* 35 insns */
HuVecF SdRabbitPosGet(void)
{
    HuVecF temp;
    if(rabbitMode[2] == 5) {
        temp = rabbitBaseModel.pos;
        temp.y = -1000.0f;
        return temp;
    } else {
        return rabbitBaseModel.pos;
    }
}

/* 14 insns */
s32 SdRabbitCheck(void)
{
    s32 result;
    if(rabbitMode[0] == 1) {
        result = TRUE;
    } else {
        result = FALSE;
    }
    return result;
}

/* 24 insns */
void SdRabbitPlayerCheck(s32 playerNo)
{
    if(rabbitMode[0] == 1) {
        rabbitMode[0]++;
        rabbitBaseModel.score[playerNo]++;
        rabbitBaseModel.unk10 = 1;
    }
}

/* 4 insns */
s32 SdRabbitDoneCheck(void)
{
    return rabbitBaseModel.unk10;
}

/* 6 insns */
s32 SdRabbitDispTimerGet(s32 playerNo)
{
    return rabbitBaseModel.score[playerNo];
}

/* 4 insns */
float SdRabbitSpeedGet(void)
{
    return rabbitSpeed;
}

/* 9 insns */
void SdRabbitZAxisGet(HuVecF *axis)
{
    *axis = rabbitZAxis;
}

/* 38 insns */
void SdRabbitSprDispOff(void)
{
    s32 i;
    s32 j;
    for(i=0; i<2; i++) {
        for(j=0; j<3; j++) {
            if(rabbitBaseModel.sprId[i][j] != -1) {
                espDispOff(rabbitBaseModel.sprId[i][j]);
            }
        }
    }
}
