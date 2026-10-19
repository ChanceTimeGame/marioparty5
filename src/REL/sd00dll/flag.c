/*
 * sd00dll flag.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/flag.s.
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
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2AC gap_05_000002AC_bss (0x4): alignment gap */
/* 0x284 */ static SDFLAGWORK flagWork;
/* 0x278 */ static s32 flagMode[3];
/* 0x274 */ static float flagRotY;
/* 0x270 */ static float flagScale;
/* 0x26C */ static s32 flagRespawnTimer;
/* 0x268 */ static HSFBUFFER *flag1Vtx;
/* 0x264 */ static HSFBUFFER *flag2Vtx;
/* 0x260 */ static s32 flagRippleTimer;

static s32 FlagNextPosGet(HuVecF *pos);
static s32 FlagPickupCheck(void);
static void FlagRippleInit(void);
static void FlagRippleUpdate(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 76 insns */
void SdFlagInit(void)
{
    s32 i;
    s32 j;
    if(sys->gameType == 1) {
        flagMode[0] = 0;
        flagMode[1] = 0;
        flagMode[2] = 0;
        flagWork.mdlId = -1;
        for(i=0; i<2; i++) {
            flagWork.score[i] = 0;
            for(j=0; j<3; j++) {
                flagWork.sprId[i][j] = -1;
            }
        }
        flagWork.pos = (HuVecF){ 0, 0, 0 };
        flagRespawnTimer = 0;
    }
}

/* 269 insns */
void SdFlagUpdate(void)
{
    if(sys->gameType == 1 && MgSeqModeGet() >= 5) {
        switch(flagMode[0]) {
            case 0:
                if(flagWork.mdlId == -1) {
                    flagWork.mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_sd00, 104), HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelCameraSet(flagWork.mdlId, 3);
                    Hu3DModelAttrSet(flagWork.mdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(flagWork.mdlId, HU3D_MOTATTR_LOOP);
                    FlagRippleInit();
                }
                if(SdFlagPosSet(&flagWork)) {
                    flagMode[0] = 10;
                    flagRotY = 0.0f;
                    flagScale = 0.0f;
                    Hu3DModelScaleSet(flagWork.mdlId, flagScale, flagScale, flagScale);
                    Hu3DModelAttrReset(flagWork.mdlId, HU3D_ATTR_DISPOFF);
                }
                break;
            case 1:
                if(FlagPickupCheck()) {
                    flagMode[0] = 11;
                }
                break;
            case 2:
                Hu3DModelAttrSet(flagWork.mdlId, HU3D_ATTR_DISPOFF);
                if(flagWork.score[0] == 3 || flagWork.score[1] == 3) {
                    flagMode[0] = 99;
                } else {
                    flagMode[0]++;
                }
                break;
            case 3:
                if(SdFlagPosSet(&flagWork)) {
                    flagMode[0] = 10;
                    Hu3DModelAttrReset(flagWork.mdlId, HU3D_ATTR_DISPOFF);
                    flagRotY = 0.0f;
                }
                break;
            case 10:
                flagScale += 0.05f;
                if(flagScale > 1.0f) {
                    flagScale = 1.0f;
                }
                Hu3DModelScaleSet(flagWork.mdlId, flagScale, flagScale, flagScale);
                if(1.0f == flagScale) {
                    flagMode[0] = 1;
                }
                break;
            case 11:
                flagScale -= 0.05f;
                if(flagScale < 0.0f) {
                    flagScale = 0.0f;
                }
                Hu3DModelScaleSet(flagWork.mdlId, flagScale, flagScale, flagScale);
                if(0.0f == flagScale) {
                    flagMode[0] = 2;
                }
                break;
            case 99:
                break;
        }
        SdFlagSprUpdate(&flagWork);
        FlagRippleUpdate();
    }
}

/* 53 insns */
void SdFlagClose(void)
{
    s32 i;
    s32 j;
    if(sys->gameType == 1) {
        if(flagWork.mdlId != -1) {
            Hu3DModelKill(flagWork.mdlId);
        }
        for(i=0; i<2; i++) {
            for(j=0; j<3; j++) {
                if(flagWork.sprId[i][j] != -1) {
                    espKill(flagWork.sprId[i][j]);
                }
            }
        }
    }
}

/* 46 insns */
void SdFlagRotUpdate(void)
{
    Hu3DModelRotSet(flagWork.mdlId, 0.0f, flagRotY, 0.0f);
    flagRotY = (flagRotY < 358.0f) ? 2.0f+flagRotY : 0.0f;
}

/* 56 insns */
s32 SdFlagPosSet(SDFLAGWORK *work)
{
    s32 result = FALSE;
    HuVecF pos = work->pos;
    if(FlagNextPosGet(&pos)) {
        pos.y = SdStageDistCalc(pos);
        if(-10000.0f != pos.y && SdStageRadiusCalc() < pos.y) {
            work->pos = pos;
            Hu3DModelPosSetV(work->mdlId, &work->pos);
            result = TRUE;
        }
    }
    return result;
}

/* 250 insns */
static s32 FlagNextPosGet(HuVecF *pos)
{
    HuVecF p1Pos;
    HuVecF p2Pos;
    HuVecF newPos;
    HuVecF dir;
    SDMACHINE *machine1;
    SDMACHINE *machine2;
    float midX;
    float midZ;
    float slope;
    float distMin;
    float distMax;
    float dist;
    s32 rand;
    s32 result = FALSE;
    machine1 = &sys->machine[0];
    machine2 = &sys->machine[1];
    p1Pos = machine1->pos;
    p2Pos = machine2->pos;
    newPos = *pos;
    p1Pos.y = p2Pos.y = newPos.y = 0.0f;
    if(p1Pos.x != p2Pos.x && p1Pos.z != p2Pos.z) {
        midX = (p1Pos.x+p2Pos.x)/2.0f;
        midZ = (p1Pos.z+p2Pos.z)/2.0f;
        slope = (p1Pos.z-p2Pos.z)/(p1Pos.x-p2Pos.x);
        newPos.x = frandmod(15000);
        newPos.z = midZ+(-(1.0f/slope)*(newPos.x-midX));
        rand = frandmod(100);
        if(rand < 5) {
            distMin = 500.0f;
            distMax = 1000.0f;
        } else if(rand < 40) {
            distMin = 1100.0f;
            distMax = 2000.0f;
        } else if(rand < 85) {
            distMin = 2100.0f;
            distMax = 3000.0f;
        } else {
            distMin = 3100.0f;
            distMax = 50000.0f;
        }
        VECSubtract(&p1Pos, &newPos, &dir);
        dist = VECMag(&dir);
        if(dist >= distMin && dist <= distMax && SdStageEdgeDistGet(newPos) >= 200.0f && !SdStageBaseObjHitCheck(newPos, 100.0f)) {
            *pos = newPos;
            result = TRUE;
            flagRespawnTimer = 0;
        }
    }
    if(!result) {
        if(++flagRespawnTimer > 300) {
            newPos = SdStageRandomPosGet(-200.0f);
            if(!SdStageBaseObjHitCheck(newPos, 100.0f)) {
                *pos = newPos;
                result = TRUE;
                flagRespawnTimer = 0;
            }
        }
    }
    return result;
}

/* 141 insns */
static s32 FlagPickupCheck(void)
{
    SDMACHINE *machine1;
    SDMACHINE *machine2;
    HuVecF p1Pos;
    HuVecF p2Pos;
    HuVecF flagPos;
    HuVecF dir;
    float dist;
    s32 result = 0;
    if(MgSeqModeGet() > 5) {
        return 0;
    }
    machine1 = &sys->machine[0];
    machine2 = &sys->machine[1];
    p1Pos = machine1->pos;
    p2Pos = machine2->pos;
    flagPos = flagWork.pos;
    flagPos.y += 150.0f;
    VECSubtract(&p1Pos, &flagPos, &dir);
    dist = VECMag(&dir);
    if(dist <= 100.0f+machine1->unk358) {
        flagWork.score[0]++;
        result = 1;
    }
    VECSubtract(&p2Pos, &flagPos, &dir);
    dist = VECMag(&dir);
    if(dist <= 100.0f+machine2->unk358) {
        if(result == 0) {
            flagWork.score[1]++;
            result = 2;
        } else {
            flagWork.score[0]--;
            result = -1;
        }
    }
    if(result == 1) {
        SdVibrate(machine1->playerNo, 2, 15);
    }
    if(result == 2) {
        SdVibrate(machine2->playerNo, 2, 15);
    }
    if(result == 1 || result == 2) {
        HuAudFXPlayVolPan(result+0x564, 127, ((result-1)*32)+48);
        SdPlayerSoundPlay(&sys->machine[result-1], 4);
    }
    return result;
}

/* 220 insns */
void SdFlagSprUpdate(SDFLAGWORK *work)
{
    float scale = 0.5f;
    u32 dataNum;
    s32 i;
    dataNum = (sys->gameType == 1) ? DATANUM(DATA_sd00, 159) : DATANUM(DATA_sd00, 160);
    switch(flagMode[1]) {
        case 0:
            for(i=0; i<3; i++) {
                work->sprId[0][i] = espEntry(dataNum, 0, 0);
                espDrawNoSet(work->sprId[0][i], 0);
                espPosSet(work->sprId[0][i], (16.0f+(32.0f*scale))+((69.0f*i)*scale), 40.0f+(32.0f*scale));
                espScaleSet(work->sprId[0][i], scale, scale);
                espDispOff(work->sprId[0][i]);
                work->sprId[1][i] = espEntry(dataNum, 0, 0);
                espDrawNoSet(work->sprId[1][i], 0);
                espPosSet(work->sprId[1][i], (560.0f-(32.0f*scale))-((69.0f*i)*scale), 40.0f+(32.0f*scale));
                espScaleSet(work->sprId[1][i], scale, scale);
                espDispOff(work->sprId[1][i]);
            }
            flagMode[1]++;
            break;
        case 1:
            if(sys->unkB70 == 0 || sys->winnerNo == -1) {
                if(work->score[0] > 0 && work->score[0] <= 3) {
                    espDispOn(work->sprId[0][work->score[0]-1]);
                }
                if(work->score[1] > 0 && work->score[1] <= 3) {
                    espDispOn(work->sprId[1][work->score[1]-1]);
                }
            }
            break;
    }
    for(i=0; i<3; i++) {
        SdSprScissorUpdate(work->sprId[0][i], 0);
        SdSprScissorUpdate(work->sprId[1][i], 1);
    }
}

/* 80 insns */
static void FlagRippleInit(void)
{
    char *nameTbl[2] = { "flag", "flag1" };
    s32 i;
    HSFDATA *hsf;
    HSFBUFFER *vtx;
    s32 j;
    flagRippleTimer = 0;
    flag1Vtx = flag2Vtx = NULL;
    hsf = Hu3DData[flagWork.mdlId].hsf;
    for(i=0; i<hsf->vertexNum; i++) {
        vtx = &hsf->vertex[i];
        for(j=0; j<2; j++) {
            if(strlen(nameTbl[j]) == strlen(vtx->name) && memcmp(nameTbl[j], vtx->name, strlen(nameTbl[j])) == 0) {
                if(j == 0) {
                    flag1Vtx = vtx;
                } else {
                    flag2Vtx = vtx;
                }
            }
        }
    }
}

/* 121 insns */
static void FlagRippleUpdate(void)
{
    float scale;
    float time;
    s32 speed;
    float amp;
    float freq;
    HSFBUFFER *vtx1;
    HSFBUFFER *vtx2;
    s32 i;
    if(!flag1Vtx || !flag2Vtx) {
        return;
    }
    speed = 8;
    amp = 0.2f;
    freq = 24.0f;
    flagRippleTimer -= speed;
    vtx1 = flag1Vtx;
    vtx2 = flag2Vtx;
    for(i=0; i<vtx1->count; i++) {
        scale = amp*(((HuVecF *)vtx1->data)[i].x-10.0f);
        time = flagRippleTimer+((i/2)*freq);
        ((HuVecF *)vtx2->data)[i].z = ((HuVecF *)vtx1->data)[i].z = scale*HuSin(time);
    }
}

/* 9 insns */
HuVecF SdFlagPosGet(void)
{
    return flagWork.pos;
}

/* 14 insns */
s32 SdFlagCheck(void)
{
    s32 result;
    if(flagMode[0] == 1) {
        result = TRUE;
    } else {
        result = FALSE;
    }
    return result;
}

/* 6 insns */
s32 SdFlagDispTimerGet(s32 playerNo)
{
    return flagWork.score[playerNo];
}

/* 38 insns */
void SdFlagSprDispOff(void)
{
    s32 i;
    s32 j;
    for(i=0; i<2; i++) {
        for(j=0; j<3; j++) {
            if(flagWork.sprId[i][j] != -1) {
                espDispOff(flagWork.sprId[i][j]);
            }
        }
    }
}

/* --- .data after the last user --- */
/* 0x19C0 "flag", 0x19C5 "flag1": FlagRippleInit's nameTbl (lbl_1_rodata_1460) */
