/*
 * m553dll/game.c -- the duel: 35 stage objects scattered over an 8x8 grid that
 * the duellists jump onto and stack, the collision that takes or pushes them,
 * the computer duellists' slot search, the end-of-round collapse and the
 * sequence steps. Written from the reference assembly, functions in reference
 * order; line ranges are into
 * build/mp5-asm/m553Dll/asm/REL/m553Dll/game.s.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/flag.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/mg/actman.h"

#include "REL/m553Dll/m553.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_3AE4(M553_WORK *work);
s16 fn_1_6064(M553_WORK *work);
s16 fn_1_6170(void);
s16 fn_1_61A8(void);
s16 fn_1_6218(void);
s16 fn_1_6850(void);
s16 fn_1_6928(void);
s16 fn_1_6964(void);
s16 fn_1_6BDC(void);
s16 fn_1_6C0C(void);
void fn_1_6C64(void);
void fn_1_6F30(void);
s16 fn_1_7300(s16 player);
void fn_1_7368(void);
s16 fn_1_80B8(s16 skip);
s16 fn_1_84C8(void);
s16 fn_1_8948(s16 player);
int fn_1_984C(void);
int fn_1_9A70(void);
int fn_1_B5F4(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_B654(MGACTOR *actor, int param);
void fn_1_B668(void);
void fn_1_C650(s16 player);
s16 fn_1_C92C(s16 player);
s16 fn_1_CA98(s16 player);
s16 fn_1_CC28(s16 player);
void fn_1_D070(s16 player);
void fn_1_D1B8(s16 player);
/* m553.c */
MGTIMER *fn_1_1ABC(int type, int maxTime, int endTime, float x, float y);
void fn_1_1B30(MGTIMER *timer);
BOOL fn_1_1B5C(MGTIMER *timer);
void fn_1_1B84(MGTIMER *timer);
void fn_1_23CC(void);
void fn_1_28D4(HuVecF *pos);
void fn_1_2B4C(HuVecF *pos);
s16 fn_1_1880(float *value, float div, float start, float end);
void fn_1_94C(s16 no);
void fn_1_10F4(void);
void fn_1_14F4(void);
void fn_1_36E4(void);
void fn_1_3714(s16 bgmF, s16 speed);
void fn_1_37DC(s16 no);
void fn_1_3854(s16 no, s16 vol, s16 pan);
void fn_1_3AC4(void);
/* stage.c */
void fn_1_E690(void);

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

u32 lbl_1_bss_1EFC;                 /* unreferenced; dtk sizes lbl_1_bss_1EF8 8 */
M553_WORK *lbl_1_bss_1EF8;          /* set by fn_1_3AE4 */

/*
 * 2400 insns. The duel's init: clear the overlay state, publish the work
 * pointer, build all 136 stage models, create the two duellists' actors,
 * scatter the stage objects over the 8x8 grid and start the timer.
 */
void fn_1_3AE4(M553_WORK *work)
{
    s16 dataNo[4];
    HuVecF pos;
    MGACTOR_PARAM param;
    s16 i;
    s16 j;
    s16 k;
    s16 slot;
    s16 dupF;

    memset(&lbl_1_bss_70C, 0, sizeof(M553_GAME));
    memset(lbl_1_bss_48C, 0, sizeof(lbl_1_bss_48C));
    memset(&lbl_1_bss_478, 0, sizeof(M553_STATE));
    memset(lbl_1_bss_18, 0, sizeof(lbl_1_bss_18));
    memset(&lbl_1_bss_0, 0, sizeof(M553_ACTORS));
    lbl_1_bss_1EF8 = work;
    for(i=0; i<22; i++) {
        lbl_1_bss_70C.seF[i] = -1;
    }
    lbl_1_bss_70C.scale3C = 0.0f;
    lbl_1_bss_70C.scale40 = 0.0f;
    for(i=0, j=0; i<=1; i++, j++) {
        lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 0);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        if(i == 1) {
            lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
            lbl_1_bss_1EF8->models[i].rot.y = 22.5f;
            lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
            Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.25f);
            Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        }
    }
    lbl_1_bss_1EF8->models[101].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[11], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[101].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_1EF8->models[101].modelId, 1);
    lbl_1_bss_1EF8->models[101].pos.x = 0.0f;
    lbl_1_bss_1EF8->models[101].pos.y = 0.0f;
    lbl_1_bss_1EF8->models[101].pos.z = 0.0f;
    lbl_1_bss_1EF8->models[101].rot.x = 0.0f;
    lbl_1_bss_1EF8->models[101].rot.y = 0.0f;
    lbl_1_bss_1EF8->models[101].rot.z = 0.0f;
    lbl_1_bss_0.colMdlId[0] = lbl_1_bss_1EF8->models[101].modelId;
    MgActorColMapInit(lbl_1_bss_0.colMdlId, 1, 10);
    param.height = 150.0f;
    param.radius = 35.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0;
    param.narrowHook = fn_1_B5F4;
    param.correctHookParam = 0;
    param.correctHook = fn_1_B654;
    lbl_1_bss_0.player[0] = MgPlayerCreate(lbl_1_bss_1EF8->chr[0].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[0]->actor->pos.x = -150.0f;
    lbl_1_bss_0.player[0]->actor->pos.y = 100.0f;
    lbl_1_bss_0.player[0]->actor->pos.z = 0.0f;
    lbl_1_bss_0.player[0]->actor->rotY = 0.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[0]->actor->mdlId, 0);
    Hu3DModelShadowSet(lbl_1_bss_0.player[0]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[0]->actor->mdlId);
    lbl_1_bss_1EF8->models[134].modelId = lbl_1_bss_0.player[0]->actor->mdlId;
    CharModelStepFxSet(lbl_1_bss_1EF8->chr[0].charNo, 2);
    param.param = 1;
    lbl_1_bss_0.player[1] = MgPlayerCreate(lbl_1_bss_1EF8->chr[1].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[1]->actor->pos.x = 150.0f;
    lbl_1_bss_0.player[1]->actor->pos.y = 100.0f;
    lbl_1_bss_0.player[1]->actor->pos.z = 0.0f;
    lbl_1_bss_0.player[1]->actor->rotY = 0.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[1]->actor->mdlId, 0);
    Hu3DModelShadowSet(lbl_1_bss_0.player[1]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[1]->actor->mdlId);
    lbl_1_bss_1EF8->models[135].modelId = lbl_1_bss_0.player[1]->actor->mdlId;
    CharModelStepFxSet(lbl_1_bss_1EF8->chr[1].charNo, 2);
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &lbl_1_bss_0.player[0]->actor->pos);
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &lbl_1_bss_0.player[1]->actor->pos);
    for(i=0x61, j=0; i<=0x62; i++, j++) {
        lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[10], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f, 0.0f, 0.0f);
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.x = -200.0f+(400.0f*j);
        lbl_1_bss_1EF8->models[i].pos.y = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
    }
    for(i=0x63, j=0; i<=0x64; i++, j++) {
        lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[9], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_COLOR_NOUPDATE);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f, 0.0f, 0.0f);
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.x = -200.0f+(400.0f*j);
        lbl_1_bss_1EF8->models[i].pos.y = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
    }
    lbl_1_bss_1EF8->models[2].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[2], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[2].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_1EF8->models[2].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_1EF8->models[2].modelId, 1);
    Hu3DModelShadowMapSet(lbl_1_bss_1EF8->models[2].modelId);
    lbl_1_bss_1EF8->models[2].pos.x = 0.0f;
    lbl_1_bss_1EF8->models[2].pos.y = 0.0f;
    lbl_1_bss_1EF8->models[2].pos.z = 0.0f;
    lbl_1_bss_1EF8->models[2].rot.x = 0.0f;
    lbl_1_bss_1EF8->models[2].rot.y = 0.0f;
    lbl_1_bss_1EF8->models[2].rot.z = 0.0f;
    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[2].modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[2].modelId, 0.25f);
    Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[2].modelId, 0.0f);
    Hu3DModelAttrReset(lbl_1_bss_1EF8->models[2].modelId, HU3D_ATTR_DISPOFF);
    for(i=3; i<=0x25; i++) {
        if(i == 3) {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[3], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelLink(lbl_1_bss_1EF8->models[3].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 5);
        Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 500.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
    }
    for(i=0x26; i<=0x39; i++) {
        if(i == 0x26) {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[4], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelLink(lbl_1_bss_1EF8->models[0x26].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 5);
        Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 500.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
    }
    for(i=0x3a; i<=0x48; i++) {
        if(i == 0x3a) {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[5], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelLink(lbl_1_bss_1EF8->models[0x3a].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 5);
        Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 500.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
    }
    for(i=0x49; i<=0x5c; i++) {
        if(i == 0x49) {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_1EF8->models[i].modelId = Hu3DModelLink(lbl_1_bss_1EF8->models[0x49].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 5);
        Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 500.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
    }
    dataNo[0] = 7;
    dataNo[1] = 7;
    dataNo[2] = 8;
    dataNo[3] = 8;
    for(i=0x5d, j=0; i<=0x60; i++, j++) {
        lbl_1_bss_1EF8->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1EF8->stageDataTbl[dataNo[j]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_1EF8->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_1EF8->models[i].modelId, 5);
        Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[i].modelId, 0.0f);
        lbl_1_bss_1EF8->models[i].pos.x = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.y = 0.0f;
        lbl_1_bss_1EF8->models[i].pos.z = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.x = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.y = 0.0f;
        lbl_1_bss_1EF8->models[i].rot.z = 0.0f;
        if(dataNo[j] == 7) {
            Hu3DModelShadowMapSet(lbl_1_bss_1EF8->models[i].modelId);
        }
    }
    lbl_1_bss_478.numA = frandmod(5)+15;
    lbl_1_bss_478.numB = frandmod(5)+5;
    lbl_1_bss_478.objNum = lbl_1_bss_478.numA+lbl_1_bss_478.numB;
    lbl_1_bss_478.numA = 20;
    lbl_1_bss_478.numB = 15;
    lbl_1_bss_478.objNum = lbl_1_bss_478.numA+lbl_1_bss_478.numB;
    for(i=0; i<lbl_1_bss_478.numA; i++) {
        do {
            slot = frandmod(64);
            for(k=0, dupF=0; k<i; k++) {
                if(slot == lbl_1_bss_18[k].slot) {
                    dupF = 1;
                }
            }
        } while(dupF);
        lbl_1_bss_18[i].activeF = 1;
        lbl_1_bss_18[i].colF = 1;
        lbl_1_bss_18[i].slot = slot;
        lbl_1_bss_18[i].mdlMain = i+0x26;
        lbl_1_bss_18[i].mdlSub = i+0x49;
        lbl_1_bss_18[i].mdlIdle = i+3;
        lbl_1_bss_18[i].typeF = 1;
        lbl_1_bss_18[i].tpLvl = 1.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.z = (100.0f*(slot/8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].pos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].pos.z = (100.0f*(slot/8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].pos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].pos.z = (100.0f*(slot/8))-360.0f;
    }
    for(i=lbl_1_bss_478.numA, j=0; i<lbl_1_bss_478.objNum; i++, j++) {
        do {
            slot = frandmod(64);
            for(k=0, dupF=0; k<i; k++) {
                if(slot == lbl_1_bss_18[k].slot) {
                    dupF = 1;
                }
            }
        } while(dupF);
        lbl_1_bss_18[i].activeF = 1;
        lbl_1_bss_18[i].colF = 1;
        lbl_1_bss_18[i].slot = slot;
        lbl_1_bss_18[i].mdlMain = j+0x3a;
        lbl_1_bss_18[i].mdlSub = -1;
        lbl_1_bss_18[i].mdlIdle = i+3;
        lbl_1_bss_18[i].typeF = 0;
        lbl_1_bss_18[i].tpLvl = 1.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.z = (100.0f*(slot/8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].pos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].pos.z = (100.0f*(slot/8))-360.0f;
    }
    MgPlayerAttrSet(lbl_1_bss_0.player[0], MGPLAYER_ATTR_HEADJUMP_OFF);
    MgPlayerAttrSet(lbl_1_bss_0.player[1], MGPLAYER_ATTR_HEADJUMP_OFF);
    CharEffectLayerSet(2);
    fn_1_C650(0);
    fn_1_C650(1);
    fn_1_E690();
    fn_1_23CC();
    fn_1_6F30();
    lbl_1_bss_70C.mgTimer = fn_1_1ABC(0, 15, 0, 292.0f, 64.0f);
}

/* 67 insns. Init hook: reset, park both pads and latch the duellists' start positions. */
s16 fn_1_6064(M553_WORK *work)
{
    s16 result;
    HU3DMODEL *model;

    result = 1;
    fn_1_3AE4(work);
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    model = &Hu3DData[lbl_1_bss_1EF8->models[0x86].modelId];
    lbl_1_bss_48C[0].pos = model->pos;
    model = &Hu3DData[lbl_1_bss_1EF8->models[0x87].modelId];
    lbl_1_bss_48C[1].pos = model->pos;
    return result;
}

/* 14 insns. Fade-in hook. */
s16 fn_1_6170(void)
{
    s16 result;

    result = 0;
    result = fn_1_984C();
    fn_1_6F30();
    return result;
}

/* 28 insns. Start hook. */
s16 fn_1_61A8(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_70C.mode = 0;
    lbl_1_bss_70C.unk002 = 0;
    lbl_1_bss_70C.unk004 = 0;
    lbl_1_bss_70C.timer = 0;
    fn_1_6F30();
    return result;
}

/*
 * 398 insns. The main hook: run the timer, step each computer duellist, decide
 * the winner off the two stack heights, then push both pads, run the actors and
 * the collision, and put the duellists back where the collision left them.
 */
s16 fn_1_6218(void)
{
    s16 result;
    s16 endF;
    s16 doneF;
    s16 i;
    HuVecF puffPos;
    int playerNo;
    HuVecF pos;

    result = 0;
    endF = 0;
    switch(lbl_1_bss_70C.mode) {
        case 0:
            fn_1_1B30(lbl_1_bss_70C.mgTimer);
            lbl_1_bss_70C.mode++;

        case 1:
            if(HuPadBtn[0] & PAD_BUTTON_Y) {
                puffPos.x = 0.0f;
                puffPos.y = 200.0f;
                puffPos.z = 15.0f;
                fn_1_2B4C(&puffPos);
            }
            doneF = fn_1_1B5C(lbl_1_bss_70C.mgTimer);
            if(lbl_1_bss_478.endF == 0 && doneF == 0) {
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_48C[i].comF) {
                        if(lbl_1_bss_48C[i].comWait <= 0) {
                            fn_1_C92C(i);
                        } else {
                            lbl_1_bss_48C[i].comWait--;
                        }
                    }
                }
            }
            if(lbl_1_bss_478.endF != 0 || doneF != 0) {
                lbl_1_bss_48C[0].padOffF = 1;
                lbl_1_bss_48C[1].padOffF = 1;
                if(lbl_1_bss_478.takenF == 0) {
                    endF = 1;
                }
            }
            if(endF != 0) {
                if(lbl_1_bss_48C[0].stackNum == lbl_1_bss_48C[1].stackNum) {
                    lbl_1_bss_70C.winner = 0;
                } else if(lbl_1_bss_48C[0].stackNum > lbl_1_bss_48C[1].stackNum) {
                    lbl_1_bss_70C.winner = 2;
                } else {
                    lbl_1_bss_70C.winner = 1;
                }
                lbl_1_bss_70C.mode++;
            }
            break;

        case 2:
            fn_1_1B84(lbl_1_bss_70C.mgTimer);
            if(lbl_1_bss_70C.winner) {
                MgSeqWinnerSet(lbl_1_bss_1EF8->chr[lbl_1_bss_70C.winner&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                playerNo = lbl_1_bss_1EF8->chr[lbl_1_bss_70C.winner&1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
            } else {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            }
            fn_1_3714(1, 100);
            result = 1;
            break;
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_48C[i].comF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], lbl_1_bss_48C[i].stkX, lbl_1_bss_48C[i].stkY, lbl_1_bss_48C[i].btnDown, lbl_1_bss_48C[i].btn);
        }
        if(lbl_1_bss_48C[i].padOffF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
        }
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_48C[0].posOld.x = pos.x;
    lbl_1_bss_48C[0].posOld.y = pos.y;
    lbl_1_bss_48C[0].posOld.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_48C[1].posOld.x = pos.x;
    lbl_1_bss_48C[1].posOld.y = pos.y;
    lbl_1_bss_48C[1].posOld.z = pos.z;
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_48C[0].pos.x = pos.x;
    lbl_1_bss_48C[0].pos.y = pos.y;
    lbl_1_bss_48C[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_48C[1].pos.x = pos.x;
    lbl_1_bss_48C[1].pos.y = pos.y;
    lbl_1_bss_48C[1].pos.z = pos.z;
    fn_1_B668();
    fn_1_7368();
    pos.x = lbl_1_bss_48C[0].pos.x;
    pos.y = lbl_1_bss_48C[0].pos.y;
    pos.z = lbl_1_bss_48C[0].pos.z;
    MgActorPosSet(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_48C[1].pos.x;
    pos.y = lbl_1_bss_48C[1].pos.y;
    pos.z = lbl_1_bss_48C[1].pos.z;
    MgActorPosSet(lbl_1_bss_0.player[1]->actor, &pos);
    fn_1_6F30();
    return result;
}

/* 54 insns. Finish hook. */
s16 fn_1_6850(void)
{
    s16 result;

    result = 0;
    fn_1_84C8();
    lbl_1_bss_70C.mode = 0;
    lbl_1_bss_70C.unk002 = 0;
    lbl_1_bss_70C.unk004 = 0;
    lbl_1_bss_70C.timer = 0;
    lbl_1_bss_48C[0].mode = 0;
    lbl_1_bss_48C[1].mode = 0;
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    fn_1_6F30();
    return result;
}

/* 15 insns. Pre-winner hook. */
s16 fn_1_6928(void)
{
    s16 result;

    result = 0;
    result = fn_1_9A70();
    fn_1_B668();
    fn_1_6F30();
    return result;
}

/*
 * 158 insns. Winner hook: pose the winner and the loser once. On a draw both
 * duellists take the lose pose and the lose voice. Every index is winner&1 or
 * (winner&2)>>1, so no path reaches player[-1].
 */
s16 fn_1_6964(void)
{
    s16 result;
    DS_PLAYER *pl;

    result = 0;
    if(lbl_1_bss_1EF8->mode[0] == 0) {
        if(lbl_1_bss_70C.winner != 0) {
            pl = &lbl_1_bss_1EF8->player[lbl_1_bss_70C.winner&1];
            pl->motNo = 3;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_1EF8->player[(lbl_1_bss_70C.winner&2)>>1];
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        } else if(lbl_1_bss_48C[0].stackNum != 0 || lbl_1_bss_48C[1].stackNum != 0) {
            pl = &lbl_1_bss_1EF8->player[0];
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_1EF8->player[1];
            pl->motNo = 4;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            CharLoseVoicePlay(lbl_1_bss_1EF8->chr[0].charNo, lbl_1_bss_1EF8->chr[1].charNo, CHARNO_NONE, CHARNO_NONE);
        }
        lbl_1_bss_1EF8->mode[0] = 1;
    }
    fn_1_6F30();
    if(lbl_1_bss_70C.winner != 0) {
        CharModelVoicePanSet(lbl_1_bss_1EF8->chr[lbl_1_bss_70C.winner&1].charNo, 64);
    }
    return result;
}

/* 12 insns. Fade-out hook. */
s16 fn_1_6BDC(void)
{
    s16 result;

    result = 1;
    fn_1_6F30();
    return result;
}

/* 22 insns. Close hook. */
s16 fn_1_6C0C(void)
{
    s16 result;

    result = 1;
    fn_1_3AC4();
    MgActorKill(lbl_1_bss_0.player[0]->actor);
    MgActorKill(lbl_1_bss_0.player[1]->actor);
    return result;
}

/*
 * 179 insns. Unreferenced: push all 134 model positions and rotations at Hu3D,
 * then set each duellist's voice volume and pan from its model position.
 */
void fn_1_6C64(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 i;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    modelA = &Hu3DData[lbl_1_bss_1EF8->models[0x86].modelId];
    modelB = &Hu3DData[lbl_1_bss_1EF8->models[0x87].modelId];
    for(i=0; i<0x86; i++) {
        Hu3DModelPosSet(lbl_1_bss_1EF8->models[i].modelId, lbl_1_bss_1EF8->models[i].pos.x, lbl_1_bss_1EF8->models[i].pos.y, lbl_1_bss_1EF8->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_1EF8->models[i].modelId, lbl_1_bss_1EF8->models[i].rot.x, lbl_1_bss_1EF8->models[i].rot.y, lbl_1_bss_1EF8->models[i].rot.z);
    }
    volF = 0.020666666f*modelA->pos.z;
    panF = 0.042666666f*modelA->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_1EF8->chr[0].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_1EF8->chr[0].charNo, pan);
    volF = 0.020666666f*modelB->pos.z;
    panF = 0.042666666f*modelB->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_1EF8->chr[1].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_1EF8->chr[1].charNo, pan);
}

/*
 * 244 insns. The per-frame push: park the sky model on camera 0, push all 134
 * model positions and rotations at Hu3D, set both duellists' voice volume and
 * pan, then re-place the camera, the light and the shadow.
 */
void fn_1_6F30(void)
{
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    s16 i;
    float panF;
    float volF;
    s16 vol;
    s16 pan;

    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[0x75].modelId, HU3D_ATTR_ZCMP_OFF);
    Hu3DModelLayerSet(lbl_1_bss_1EF8->models[0x75].modelId, 7);
    lbl_1_bss_1EF8->models[0x75].pos.x = -1100.0f+lbl_1_bss_14->pos.x;
    lbl_1_bss_1EF8->models[0x75].pos.y = 1150.0f+(lbl_1_bss_14->pos.y-953.0f);
    lbl_1_bss_1EF8->models[0x75].pos.z = -800.0f+(lbl_1_bss_14->pos.z-1556.0f);
    modelA = &Hu3DData[lbl_1_bss_1EF8->models[0x86].modelId];
    modelB = &Hu3DData[lbl_1_bss_1EF8->models[0x87].modelId];
    for(i=0; i<0x86; i++) {
        Hu3DModelPosSet(lbl_1_bss_1EF8->models[i].modelId, lbl_1_bss_1EF8->models[i].pos.x, lbl_1_bss_1EF8->models[i].pos.y, lbl_1_bss_1EF8->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_1EF8->models[i].modelId, lbl_1_bss_1EF8->models[i].rot.x, lbl_1_bss_1EF8->models[i].rot.y, lbl_1_bss_1EF8->models[i].rot.z);
    }
    volF = 0.020666666f*modelA->pos.z;
    panF = 0.042666666f*modelA->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_1EF8->chr[0].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_1EF8->chr[0].charNo, pan);
    volF = 0.020666666f*modelB->pos.z;
    panF = 0.042666666f*modelB->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_1EF8->chr[1].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_1EF8->chr[1].charNo, pan);
    fn_1_94C(0);
    fn_1_10F4();
    fn_1_14F4();
}

/* 26 insns. Unreferenced, and both arms of its test are empty. */
s16 fn_1_7300(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 unused;

    pl = &lbl_1_bss_1EF8->player[player];
    result = 0;
    unused = 0;
    if(lbl_1_bss_48C[player].unk000) {
    } else {
    }
    return result;
}

/*
 * 852 insns. Step every live stage object. Those with typeF set run one
 * three-state machine and the rest run another; both raise the object (0), hold
 * while the duellist stands on it (1), and retire it on the motion's last frame
 * (2). Afterwards raise the "nothing left alive" flag, mirror the "a slot is
 * taken" flag, and drive the round sequencer.
 */
void fn_1_7368(void)
{
    s16 unk08;
    s16 unk0A;
    s16 anyLive;
    s16 anyTaken;
    s16 i;
    s16 pan;
    s16 vol;
    float maxTime;
    float time;
    float volF;
    float panF;

    unk08 = unk0A = anyLive = anyTaken = 0;
    for(i=0; i<lbl_1_bss_478.objNum; i++) {
        if(lbl_1_bss_18[i].activeF == 0) {
            continue;
        }
        anyLive = 1;
        if(lbl_1_bss_18[i].takenF) {
            lbl_1_bss_48C[0].slotF[lbl_1_bss_18[i].slot] = 1;
            lbl_1_bss_48C[1].slotF[lbl_1_bss_18[i].slot] = 1;
            anyTaken = 1;
        }
        if(lbl_1_bss_18[i].typeF) {
            switch(lbl_1_bss_18[i].state) {
            case 0:
                if(lbl_1_bss_18[i].takenF == 0) {
                    break;
                }
                Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, 1.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].modelId, 1.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].modelId, 0.0f);
                lbl_1_bss_48C[lbl_1_bss_18[i].duellist].stackMdl[lbl_1_bss_48C[lbl_1_bss_18[i].duellist].stackNum] = lbl_1_bss_18[i].mdlMain;
                lbl_1_bss_48C[lbl_1_bss_18[i].duellist].stackNum++;
                volF = 0.020666666f*lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].pos.z;
                panF = 0.042666666f*lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_3854(0, vol, pan);
                lbl_1_bss_18[i].state++;
                break;

            case 1:
                if(lbl_1_bss_0.player[lbl_1_bss_18[i].duellist]->actor->velY >= 0.0f && lbl_1_bss_48C[lbl_1_bss_18[i].duellist].pos.y >= 250.0f) {
                    lbl_1_bss_0.player[lbl_1_bss_18[i].duellist]->actor->velY = 0.0f;
                    lbl_1_bss_48C[lbl_1_bss_18[i].duellist].pos.y = 250.0f;
                } else {
                    lbl_1_bss_48C[lbl_1_bss_18[i].duellist].tookF = 0;
                    lbl_1_bss_18[i].state++;
                }
                break;

            case 2:
                maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId)-1.0f;
                time = Hu3DMotionTimeGet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId);
                if(Hu3DMotionEndCheck(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId) && maxTime <= time) {
                    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlSub].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_18[i].activeF = 0;
                }
                break;
            }
        } else {
            switch(lbl_1_bss_18[i].state) {
            case 0:
                if(lbl_1_bss_18[i].takenF == 0) {
                    break;
                }
                Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, 1.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, 0.0f);
                lbl_1_bss_48C[lbl_1_bss_18[i].duellist].unk048++;
                volF = 0.020666666f*lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.z;
                panF = 0.042666666f*lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_3854(1, vol, pan);
                lbl_1_bss_18[i].state++;
                lbl_1_bss_18[i].colF = 0;
                break;

            case 1:
                if(lbl_1_bss_0.player[lbl_1_bss_18[i].duellist]->actor->velY >= 0.0f) {
                    lbl_1_bss_0.player[lbl_1_bss_18[i].duellist]->actor->velY = 0.0f;
                    lbl_1_bss_48C[lbl_1_bss_18[i].duellist].pos.y = 250.0f;
                } else {
                    lbl_1_bss_48C[lbl_1_bss_18[i].duellist].tookF = 0;
                    lbl_1_bss_18[i].state++;
                }
                break;

            case 2:
                maxTime = Hu3DMotionMaxTimeGet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId)-2.0f;
                time = Hu3DMotionTimeGet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId);
                if(maxTime <= time) {
                    Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_18[i].activeF = 0;
                }
                break;
            }
        }
    }
    if(anyLive == 0) {
        lbl_1_bss_478.endF = 1;
    }
    if(anyTaken) {
        lbl_1_bss_478.takenF = 1;
    } else {
        lbl_1_bss_478.takenF = 0;
    }
    fn_1_80B8(0);
}

/*
 * 260 insns. The round sequencer: count the round's frames, and at the 300th
 * (then the 600th) start a wave -- wake every unclaimed stage object's idle
 * motion (1), then after 60 frames freeze them again and re-roll each
 * computer's slot choice (2). Returns 1 on the frame a wave ends.
 */
s16 fn_1_80B8(s16 skip)
{
    s16 result = 0;
    s16 time[2] = { 300, 600 };
    s16 i;

    lbl_1_bss_478.timer++;
    switch(lbl_1_bss_478.state) {
    case 0:
        if(lbl_1_bss_478.timer == time[lbl_1_bss_478.step]) {
            lbl_1_bss_478.state++;
            lbl_1_bss_478.step++;
        }
        if(skip) {
            lbl_1_bss_478.state++;
        }
        if(lbl_1_bss_478.state == 1) {
            fn_1_37DC(2);
        }
        break;

    case 1:
        for(i=0; i<lbl_1_bss_478.objNum; i++) {
            if(lbl_1_bss_18[i].activeF == 0) {
                continue;
            }
            if(lbl_1_bss_18[i].takenF) {
                continue;
            }
            Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, 1.0f);
            Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, 0.0f);
        }
        lbl_1_bss_478.wait = 0;
        lbl_1_bss_478.state++;
        break;

    case 2:
        if(lbl_1_bss_478.wait++ >= 60) {
            for(i=0; i<lbl_1_bss_478.objNum; i++) {
                if(lbl_1_bss_18[i].activeF == 0) {
                    continue;
                }
                if(lbl_1_bss_18[i].takenF) {
                    continue;
                }
                Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlIdle].modelId, 0.0f);
            }
            if(skip) {
                lbl_1_bss_478.timer = 0;
            } else {
                fn_1_D070(0);
                fn_1_D070(1);
            }
            lbl_1_bss_478.state = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/*
 * 288 insns. The end-of-round teardown: fade every live stage object in over
 * 0.05 a frame (0/1), hold 60 frames then burst it with dust and the break
 * sound (2), fade it back out (3) and park it (4). Returns 1 once every live
 * object has reached state 4.
 */
s16 fn_1_84C8(void)
{
    s16 result;
    s16 doneNum;
    s16 i;
    s16 liveNum;
    HuVecF pos;

    result = 0;
    doneNum = 0;
    i = 0;
    liveNum = 0;
    for(; i<lbl_1_bss_478.numA; i++) {
        if(lbl_1_bss_18[i].activeF == 0) {
            continue;
        }
        liveNum++;
        switch(lbl_1_bss_18[i].fadeState) {
        case 0:
            Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelTPLvlSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, 0.0f);
            lbl_1_bss_18[i].fadeWait = 0;
            lbl_1_bss_18[i].tpLvl = 0.0f;
            lbl_1_bss_18[i].fadeState++;
        case 1:
            if((lbl_1_bss_18[i].tpLvl += 0.05f) >= 1.0f) {
                lbl_1_bss_18[i].tpLvl = 1.0f;
                lbl_1_bss_18[i].fadeState++;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, lbl_1_bss_18[i].tpLvl);
            break;

        case 2:
            if(lbl_1_bss_18[i].fadeWait++ > 60) {
                pos = lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].pos;
                fn_1_28D4(&pos);
                if(lbl_1_bss_70C.breakF == 0) {
                    fn_1_37DC(0x15);
                    lbl_1_bss_70C.breakF = 1;
                }
                lbl_1_bss_18[i].fadeState++;
            }
            break;

        case 3:
            if((lbl_1_bss_18[i].tpLvl -= 0.05f) <= 0.0f) {
                Hu3DModelAttrSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_18[i].tpLvl = 0.0f;
                lbl_1_bss_18[i].fadeState++;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_1EF8->models[lbl_1_bss_18[i].mdlMain].modelId, lbl_1_bss_18[i].tpLvl);
            break;

        case 4:
            doneNum++;
            break;
        }
    }
    if(doneNum >= liveNum) {
        result = 1;
    }
    return result;
}

/*
 * 961 insns. One duellist's walk back to its home spot at x=-+150. Mode 0 aims
 * at the home position and shifts the walk motion in, mode 1 steps `speed`
 * units a frame toward it and faces the step, and on arrival turns the model to
 * the nearest whole turn; mode 2 spins it there with fn_1_1880 and parks the
 * idle motion; mode 3 reports done. Mode 0 falls through into mode 1.
 */
s16 fn_1_8948(s16 player)
{
    HU3DMODEL *model = &Hu3DData[lbl_1_bss_1EF8->models[player+0x86].modelId];
    DS_PLAYER *pl = &lbl_1_bss_1EF8->player[player];
    s16 result = 0;
    s16 count = 0;
    HuVecF home[2] = { { -150.0f, 0.0f, 0.0f }, { 150.0f, 0.0f, 0.0f } };
    float speed = 7.0f;
    s16 deg;
    s16 negF;
    float mag;
    float dist;
    float div;
    float rotY;
    float dx;
    float dz;

    switch(lbl_1_bss_48C[player].mode) {
        case 0:
            lbl_1_bss_70C.s018[player+2] = 0;
            lbl_1_bss_48C[player].vel.x = home[player].x-model->pos.x;
            lbl_1_bss_48C[player].vel.z = home[player].z-model->pos.z;
            mag = (lbl_1_bss_48C[player].vel.x*lbl_1_bss_48C[player].vel.x)+(lbl_1_bss_48C[player].vel.z*lbl_1_bss_48C[player].vel.z);
            dist = sqrt(mag);
            if(dist != 0.0f) {
                lbl_1_bss_70C.s018[player+2] = 1;
                pl->shiftMode = 1;
                pl->shiftMotNo = 1;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 4.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
            }
            lbl_1_bss_70C.sepMode = 1;
            lbl_1_bss_48C[player].mode++;

        case 1:
            lbl_1_bss_48C[player].vel.x = home[player].x-model->pos.x;
            lbl_1_bss_48C[player].vel.z = home[player].z-model->pos.z;
            mag = (lbl_1_bss_48C[player].vel.x*lbl_1_bss_48C[player].vel.x)+(lbl_1_bss_48C[player].vel.z*lbl_1_bss_48C[player].vel.z);
            dist = sqrt(mag);
            if(dist != 0.0f) {
                dist = speed/dist;
                lbl_1_bss_48C[player].vel.x *= dist;
                lbl_1_bss_48C[player].vel.z *= dist;
                if(lbl_1_bss_70C.sepCnt >= 30) {
                    if(player == 0) {
                        lbl_1_bss_48C[player].vel.z += 3.0f;
                    } else {
                        lbl_1_bss_48C[player].vel.z -= 3.0f;
                    }
                    mag = (lbl_1_bss_48C[player].vel.x*lbl_1_bss_48C[player].vel.x)+(lbl_1_bss_48C[player].vel.z*lbl_1_bss_48C[player].vel.z);
                    dist = sqrt(mag);
                    if(dist != 0.0f) {
                        dist = speed/dist;
                    } else {
                        dist = 0.0f;
                    }
                    lbl_1_bss_48C[player].vel.x *= dist;
                    lbl_1_bss_48C[player].vel.z *= dist;
                }
                rotY = 180.0*(acos(lbl_1_bss_48C[player].vel.x/(0.1f+speed))/M_PI);
                if((float)(180.0*(asin(lbl_1_bss_48C[player].vel.z/(0.1f+speed))/M_PI)) < 0.0f) {
                    rotY = 360.0f-rotY;
                }
                lbl_1_bss_48C[player].rotY = 90.0f+-rotY;
                model->pos.x += lbl_1_bss_48C[player].vel.x;
                model->pos.z += lbl_1_bss_48C[player].vel.z;
                model->rot.y = lbl_1_bss_48C[player].rotY;
                dx = home[player].x-model->pos.x;
                dz = home[player].z-model->pos.z;
                dist = sqrt((dx*dx)+(dz*dz));
            }
            if(dist < 2.0f+speed) {
                lbl_1_bss_48C[player].rotY = model->rot.y;
                deg = (s16)model->rot.y%360;
                if(deg != 0) {
                    if(deg < 0) {
                        deg = deg*-1;
                        negF = 1;
                    } else {
                        negF = 0;
                    }
                    if(deg > 180) {
                        deg = 360-deg;
                    } else {
                        deg = deg*-1;
                    }
                    if(negF) {
                        deg = deg*-1;
                    }
                }
                lbl_1_bss_70C.f008[player] = model->rot.y+deg;
                if(player == 0) {
                    lbl_1_bss_70C.sepMode = 2;
                }
                lbl_1_bss_48C[player].mode++;
            }
            break;

        case 2:
            div = 30.0f;
            count = fn_1_1880(&model->rot.y, div, lbl_1_bss_48C[player].rotY, lbl_1_bss_70C.f008[player]);
            if(count == 0) {
                if(lbl_1_bss_70C.s018[player+2]) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 4.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                }
                lbl_1_bss_48C[player].pos = model->pos;
                lbl_1_bss_48C[player].mode++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/*
 * 137 insns. The fade-in sequence: SE, a 90-frame hold, ease camera 0's zoom
 * from lbl_1_data_190[0] to [1], a 50-frame hold, one forced wave, a 60-frame
 * hold, then start the BGM. Returns 1 on the last step.
 */
int fn_1_984C(void)
{
    int result;
    s16 count;
    float div;

    result = 0;
    count = 0;
    switch(lbl_1_bss_70C.mode) {
        case 0:
            fn_1_37DC(0x12);
            lbl_1_bss_70C.mode++;

        case 1:
            if(lbl_1_bss_70C.timer++ >= 90) {
                lbl_1_bss_70C.timer = 0;
                lbl_1_bss_70C.mode++;
            }
            break;

        case 2:
            div = 50.0f;
            count += fn_1_1880(&lbl_1_bss_14->zoom, div, lbl_1_data_190[0].zoom, lbl_1_data_190[1].zoom);
            if(count == 0) {
                lbl_1_bss_70C.mode++;
            }
            break;

        case 3:
            if(lbl_1_bss_70C.timer++ >= 50) {
                lbl_1_bss_70C.timer = 0;
                lbl_1_bss_70C.mode++;
            }
            break;

        case 4:
            count = fn_1_80B8(1);
            if(count != 0) {
                lbl_1_bss_70C.mode++;
            }
            break;

        case 5:
            if(lbl_1_bss_70C.timer++ >= 60) {
                lbl_1_bss_70C.mode++;
            }
            break;

        case 6:
            fn_1_36E4();
            result = 1;
            break;
    }
    return result;
}

/*
 * 1761 insns. The pre-winner sequence: a 14-case switch on lbl_1_bss_70C.mode
 * that plays out the stacked-block collapse. It counts the rows down
 * (s018[0]), shakes every block and both duellists through a four-step offset
 * table, drops the camera and the shadow a row at a time, grows the four ring
 * models, then poses both duellists and finally swings the camera onto the
 * winner. Returns 1 only from case 13.
 */
int fn_1_9A70(void)
{
    int result = 0;
    s16 done = 0;
    s16 cnt = 0;
    HU3DMODEL *model[2];
    HuVecF pos;
    float shake[4][2] = { { 4.0f, 0.0f }, { -4.0f, 0.0f }, { 0.0f, 4.0f }, { 0.0f, -4.0f } };
    float div;
    s16 i;
    s16 j;
    s16 k;

    model[0] = &Hu3DData[lbl_1_bss_1EF8->models[0x86].modelId];
    model[1] = &Hu3DData[lbl_1_bss_1EF8->models[0x87].modelId];
    switch(lbl_1_bss_70C.mode) {
    case 0:
        done = fn_1_84C8();
        if(done) {
            lbl_1_bss_70C.mode++;
        }
        break;

    case 1:
        for(i=0; i<2; i++) {
            done += fn_1_8948(i);
        }
        div = 30.0f;
        cnt += fn_1_1880(&lbl_1_bss_14->rot.x, div, lbl_1_data_190[1].rot.x, -24.0f);
        cnt += fn_1_1880(&lbl_1_bss_14->zoom, div, lbl_1_data_190[1].zoom, 917.0f);
        if(done == 2 && cnt == 0) {
            lbl_1_bss_70C.timer = 0;
            if(lbl_1_bss_48C[0].stackNum || lbl_1_bss_48C[1].stackNum) {
                lbl_1_bss_70C.mode++;
            } else {
                lbl_1_bss_70C.mode = 7;
            }
        }
        break;

    case 2:
        if(lbl_1_bss_70C.timer++ > 120) {
            lbl_1_bss_70C.timer = 0;
            lbl_1_bss_70C.mode++;
        }
        break;

    case 3:
        if(lbl_1_bss_48C[0].stackNum || lbl_1_bss_48C[1].stackNum) {
            fn_1_37DC(3);
        }
        lbl_1_bss_70C.s018[0] = lbl_1_bss_70C.s018[1] = 0;
        lbl_1_bss_70C.f008[0] = lbl_1_bss_70C.f008[1] = lbl_1_bss_14->center.y;
        lbl_1_bss_70C.f008[2] = lbl_1_bss_70C.f008[3] = lbl_1_bss_C->target.y;
        lbl_1_bss_70C.mode++;

    case 4:
        lbl_1_bss_70C.s018[1]++;
        for(i=0; i<2; i++) {
            lbl_1_bss_48C[i].pos = model[i]->pos;
            if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[i].stackNum && (lbl_1_bss_70C.s018[1]%2) == 0) {
                pos.x = (-10.0f*i)+(5.0f+lbl_1_bss_48C[i].pos.x);
                pos.y = 85.0f;
                pos.z = 30.0f+lbl_1_bss_48C[i].pos.z;
                fn_1_2B4C(&pos);
            }
        }
        if(lbl_1_bss_70C.timer++ >= 20) {
            for(i=0; i<2; i++) {
                for(j=0; j<lbl_1_bss_48C[i].stackNum; j++) {
                    pos.x = model[i]->pos.x;
                    pos.y = 100.0f+(-100.0f*j);
                    pos.z = 15.0f+model[i]->pos.z;
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.x = pos.x;
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.y = pos.y;
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.z = pos.z;
                    Hu3DModelTPLvlSet(lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].modelId, 1.0f);
                    if(j) {
                        Hu3DModelAttrReset(lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].modelId, HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrReset(lbl_1_bss_1EF8->models[i+0x5D].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_1EF8->models[i+0x5F].modelId, HU3D_ATTR_DISPOFF);
                    }
                }
                lbl_1_bss_1EF8->models[i+0x5D].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
                lbl_1_bss_1EF8->models[i+0x5F].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
            }
            for(i=0; i<2; i++) {
                if(lbl_1_bss_48C[i].stackNum) {
                    omVibrate(lbl_1_bss_1EF8->chr[i].no, 10, 12, 0);
                }
            }
            if(lbl_1_bss_48C[0].stackNum || lbl_1_bss_48C[1].stackNum) {
                fn_1_37DC(4);
            }
            lbl_1_bss_70C.shakeF = 0;
            lbl_1_bss_70C.mode++;
            lbl_1_bss_70C.timer++;
        }
        break;

    case 5:
        div = 30.0f;
        i = 0;
        k = 0;
        for(; i<2; i++) {
            if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[i].stackNum) {
                for(j=0; j<lbl_1_bss_48C[i].stackNum; j++) {
                    pos.x = (100.0f+(-100.0f*j))+(100.0f*lbl_1_bss_70C.s018[0]);
                    pos.y = 100.0f+pos.x;
                    done += fn_1_1880(&lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.y, div, pos.x, pos.y);
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.x += shake[lbl_1_bss_70C.shakeNo][0];
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.z += shake[lbl_1_bss_70C.shakeNo][1];
                }
                pos.x = 100.0f+(100.0f*lbl_1_bss_70C.s018[0]);
                pos.y = 100.0f+pos.x;
                done += fn_1_1880(&model[i]->pos.y, div, pos.x, pos.y);
                model[i]->pos.x += shake[lbl_1_bss_70C.shakeNo][0];
                model[i]->pos.z += shake[lbl_1_bss_70C.shakeNo][1];
            } else {
                k++;
            }
            lbl_1_bss_1EF8->models[i+0x5D].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
            lbl_1_bss_1EF8->models[i+0x5F].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
        }
        if(++lbl_1_bss_70C.shakeF >= 2) {
            if(++lbl_1_bss_70C.shakeNo >= 4) {
                lbl_1_bss_70C.shakeNo = 0;
            }
            lbl_1_bss_70C.shakeF = 0;
        }
        if(k < 2) {
            done += fn_1_1880(&lbl_1_bss_14->center.y, div, lbl_1_bss_70C.f008[0], lbl_1_bss_70C.f008[1]);
            done += fn_1_1880(&lbl_1_bss_C->target.y, div, lbl_1_bss_70C.f008[2], lbl_1_bss_70C.f008[3]);
        }
        if(done == 0) {
            lbl_1_bss_70C.timer = 0;
            lbl_1_bss_70C.s018[0]++;
            lbl_1_bss_70C.mode++;
            if(k < 2) {
                if(lbl_1_bss_70C.s018[0] >= 1) {
                    lbl_1_bss_70C.f008[0] = lbl_1_bss_14->center.y;
                    lbl_1_bss_70C.f008[1] = 100.0f+lbl_1_bss_14->center.y;
                }
                if(lbl_1_bss_70C.s018[0] >= 5) {
                    lbl_1_bss_70C.f008[2] = lbl_1_bss_C->target.y;
                    lbl_1_bss_70C.f008[3] = 100.0f+lbl_1_bss_C->target.y;
                }
            }
            if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[0].stackNum || lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[1].stackNum) {
                fn_1_37DC(20);
            }
            if(k >= 2) {
                lbl_1_bss_70C.mode = 7;
            }
        }
        break;

    case 6:
        lbl_1_bss_70C.s018[1]++;
        i = 0;
        k = 0;
        for(; i<2; i++) {
            if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[i].stackNum) {
                if((lbl_1_bss_70C.s018[1]%2) == 0) {
                    pos.x = (-10.0f*i)+(5.0f+lbl_1_bss_48C[i].pos.x);
                    pos.y = 85.0f;
                    pos.z = 30.0f+lbl_1_bss_48C[i].pos.z;
                    fn_1_2B4C(&pos);
                }
                for(j=0; j<lbl_1_bss_48C[i].stackNum; j++) {
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.x += shake[lbl_1_bss_70C.shakeNo][0];
                    lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[j]].pos.z += shake[lbl_1_bss_70C.shakeNo][1];
                }
                model[i]->pos.x += shake[lbl_1_bss_70C.shakeNo][0];
                model[i]->pos.z += shake[lbl_1_bss_70C.shakeNo][1];
                if(++lbl_1_bss_70C.shakeF >= 2) {
                    if(++lbl_1_bss_70C.shakeNo >= 4) {
                        lbl_1_bss_70C.shakeNo = 0;
                    }
                    lbl_1_bss_70C.shakeF = 0;
                }
            }
            lbl_1_bss_1EF8->models[i+0x5D].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
            lbl_1_bss_1EF8->models[i+0x5F].pos = lbl_1_bss_1EF8->models[lbl_1_bss_48C[i].stackMdl[0]].pos;
        }
        if(lbl_1_bss_70C.timer++ >= 10) {
            i = 0;
            k = 0;
            for(; i<2; i++) {
                if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[i].stackNum) {
                    omVibrate(lbl_1_bss_1EF8->chr[i].no, 10, 12, 0);
                }
            }
            if(lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[0].stackNum || lbl_1_bss_70C.s018[0] < lbl_1_bss_48C[1].stackNum) {
                if(lbl_1_bss_70C.s018[0] <= 12) {
                    fn_1_37DC(lbl_1_bss_70C.s018[0]+4);
                } else {
                    fn_1_37DC(16);
                }
            }
            lbl_1_bss_70C.mode = 5;
        }
        break;

    case 7:
        if(lbl_1_bss_70C.timer++ > 60) {
            if(lbl_1_bss_48C[0].stackNum || lbl_1_bss_48C[1].stackNum) {
                lbl_1_bss_70C.mode = 12;
            } else {
                lbl_1_bss_70C.mode++;
            }
        }
        break;

    case 8:
        for(i=0x61, j=0; i<=0x64; i++, j++) {
            if(i == 0x63) {
                j = 0;
            }
            lbl_1_bss_1EF8->models[i].pos.x = model[j]->pos.x;
            lbl_1_bss_1EF8->models[i].pos.z = model[j]->pos.z;
            Hu3DModelAttrReset(lbl_1_bss_1EF8->models[i].modelId, HU3D_ATTR_DISPOFF);
        }
        fn_1_37DC(17);
        lbl_1_bss_70C.mode++;
        break;

    case 9:
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[0x61].modelId, lbl_1_bss_70C.scale40, 1.0f, lbl_1_bss_70C.scale40);
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[0x62].modelId, lbl_1_bss_70C.scale40, 1.0f, lbl_1_bss_70C.scale40);
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[0x63].modelId, lbl_1_bss_70C.scale3C, 1.0f, lbl_1_bss_70C.scale3C);
        Hu3DModelScaleSet(lbl_1_bss_1EF8->models[0x64].modelId, lbl_1_bss_70C.scale3C, 1.0f, lbl_1_bss_70C.scale3C);
        lbl_1_bss_70C.scale40 += 0.15f;
        lbl_1_bss_70C.scale3C += 0.15f;
        if(lbl_1_bss_70C.scale40 >= 1.5f) {
            lbl_1_bss_1EF8->player[0].shiftMode = 1;
            lbl_1_bss_1EF8->player[0].shiftMotNo = 2;
            lbl_1_bss_1EF8->player[0].shiftTime = 0.0f;
            lbl_1_bss_1EF8->player[0].shiftSpeed = 8.0f;
            lbl_1_bss_1EF8->player[0].shiftAttr = 0;
            lbl_1_bss_1EF8->player[0].attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_1EF8->player[1].shiftMode = 1;
            lbl_1_bss_1EF8->player[1].shiftMotNo = 2;
            lbl_1_bss_1EF8->player[1].shiftTime = 0.0f;
            lbl_1_bss_1EF8->player[1].shiftSpeed = 8.0f;
            lbl_1_bss_1EF8->player[1].shiftAttr = 0;
            lbl_1_bss_1EF8->player[1].attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_70C.s018[3] = 0;
            lbl_1_bss_70C.mode++;
        }
        break;

    case 10:
        if(lbl_1_bss_70C.s018[3]++ >= 25) {
            Hu3DModelShadowDispOff(lbl_1_bss_0.player[0]->actor->mdlId);
            Hu3DModelShadowDispOff(lbl_1_bss_0.player[1]->actor->mdlId);
            Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[0x86].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_1EF8->models[0x87].modelId, 0.0f);
            fn_1_37DC(19);
            lbl_1_bss_70C.mode++;
        }
        break;

    case 11:
        model[0]->pos.y -= 10.0f;
        model[1]->pos.y -= 10.0f;
        if(model[0]->pos.y <= -1000.0f) {
            lbl_1_bss_70C.mode++;
        }
        break;

    case 12:
        if(lbl_1_bss_70C.winner) {
            div = 30.0f;
            done += fn_1_1880(&lbl_1_bss_14->center.x, div, lbl_1_data_190[1].center.x, model[lbl_1_bss_70C.winner&1]->pos.x);
            done += fn_1_1880(&lbl_1_bss_14->center.y, div, lbl_1_bss_70C.f008[0], 70.0f+model[lbl_1_bss_70C.winner&1]->pos.y);
            done += fn_1_1880(&lbl_1_bss_14->center.z, div, lbl_1_data_190[1].center.z, model[lbl_1_bss_70C.winner&1]->pos.z);
            done += fn_1_1880(&lbl_1_bss_14->zoom, div, 917.0f, 500.0f);
        }
        if(done == 0) {
            lbl_1_bss_70C.mode++;
        }
        break;

    case 13:
        result = 1;
        break;
    }
    return result;
}

/* 24 insns. The actors' narrow-collision hook: count a landing on the duellist. */
int fn_1_B5F4(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    s16 unused;

    unused = 0;
    switch(b->type) {
        case 0:
            lbl_1_bss_48C[b->paramB].hitCnt++;
            lbl_1_bss_70C.hitF = 1;
            break;
        case 6:
            break;
    }
    return 0;
}

/* 5 insns. The actors' correct hook; it reads one field and does nothing. */
void fn_1_B654(MGACTOR *actor, int param)
{
    int unused;

    unused = actor->param;
}

/*
 * 1018 insns. The per-frame duellist/stage-object collision, called from the
 * main hook (fn_1_6218) and the pre-winner hook (fn_1_6928). For each duellist,
 * walk the live stage objects: one whose collision flag is still set, whose
 * model's 100-unit box the duellist is standing in, and which the duellist is
 * falling onto from the right height, is taken -- credited to that duellist,
 * its collision flag cleared, and the duellist bounced to y=250. An object that
 * is not taken pushes the duellist out of whichever of its four side faces it
 * has crossed. Afterwards each duellist is clamped to a 580-unit circle about
 * the origin, and while game.sepMode is set the two duellist models are held 70
 * units apart.
 */
void fn_1_B668(void)
{
    float rad = 35.0f;
    s16 unused2 = 0;
    s16 unused1 = 0;
    s16 unused0 = 0;
    float mul;
    float dot;
    float len2;
    HU3DMODEL *mdl[2];
    HuVecF max;
    HuVecF min;
    HuVecF pos;
    s16 clamped = 0;
    s16 pushed = 0;
    M553_FACE face[6] = {
        { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 50.0f } },
        { { 0.0f, 0.0f, 1.0f }, { 50.0f, 0.0f, 0.0f } },
        { { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, -50.0f } },
        { { 0.0f, 0.0f, 1.0f }, { -50.0f, 0.0f, 0.0f } },
        { { 0.0f, -1.0f, 0.0f }, { 0.0f, -50.0f, 0.0f } },
        { { 0.0f, 1.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } }
    };
    HuVecF *dpos;
    float dx;
    float dz;
    float dist;
    float tmp;
    float cx;
    float cz;
    float push;
    s16 i;
    s16 j;
    s16 k;
    s16 hit;

    for(i=0; i<2; i++) {
        dpos = &lbl_1_bss_48C[i].pos;
        for(j=0; j<lbl_1_bss_478.objNum; j++) {
            if(lbl_1_bss_18[j].colF == 0) {
                continue;
            }
            if(lbl_1_bss_48C[i].tookF != 0) {
                continue;
            }
            pos = lbl_1_bss_1EF8->models[lbl_1_bss_18[j].mdlMain].pos;
            hit = 1;
            tmp = 400.0f-(150.0f+dpos->y);
            if(tmp <= 0.0f && tmp >= -20.0f) {
                min.x = pos.x-50.0f;
                max.x = 50.0f+pos.x;
                min.z = pos.z-50.0f;
                max.z = 50.0f+pos.z;
                if(min.x <= dpos->x && max.x >= dpos->x && min.z <= dpos->z && max.z >= dpos->z && lbl_1_bss_0.player[i]->actor->velY > 0.0f) {
                    lbl_1_bss_0.player[i]->actor->velY = 0.0f;
                    dpos->y = 250.0f;
                    lbl_1_bss_18[j].takenF = 1;
                    lbl_1_bss_18[j].duellist = i;
                    lbl_1_bss_18[j].colF = 0;
                    lbl_1_bss_48C[i].tookF = 1;
                    hit = 0;
                }
            }
            if(hit == 0) {
                continue;
            }
            for(k=0; k<4; k++) {
                min.x = (pos.x+face[k].ofs.x)-(50.0f*face[k].axis.x);
                max.x = (pos.x+face[k].ofs.x)+(50.0f*face[k].axis.x);
                min.z = (pos.z+face[k].ofs.z)-(50.0f*face[k].axis.z);
                max.z = (pos.z+face[k].ofs.z)+(50.0f*face[k].axis.z);
                hit = 0;
                switch(k) {
                case 0:
                    if(dpos->z-10.0f > min.z) {
                        hit = 1;
                    }
                    break;
                case 1:
                    if(dpos->x-10.0f > min.x) {
                        hit = 1;
                    }
                    break;
                case 2:
                    if(10.0f+dpos->z < min.z) {
                        hit = 1;
                    }
                    break;
                case 3:
                    if(10.0f+dpos->x < min.x) {
                        hit = 1;
                    }
                    break;
                }
                if(dpos->x+rad >= min.x && dpos->x-rad <= max.x && dpos->z+rad >= min.z && dpos->z-rad <= max.z) {
                    dx = max.x-min.x;
                    dz = max.z-min.z;
                    len2 = (dx*dx)+(dz*dz);
                    dot = -1.0f*((dx*(max.x-dpos->x))+(dz*(max.z-dpos->z)));
                    if(len2 != 0.0f) {
                        tmp = dot/len2;
                    } else {
                        tmp = 0.0f;
                    }
                    cx = max.x+(dx*tmp);
                    cz = max.z+(dz*tmp);
                    dx = dpos->x-cx;
                    dz = dpos->z-cz;
                    dist = sqrt((dx*dx)+(dz*dz));
                    mul = 1.0f;
                    if(dist < rad) {
                        tmp = 400.0f-(150.0f+dpos->y);
                        if(tmp <= 0.0f) {
                            if(lbl_1_bss_0.player[i]->actor->velY > 0.0f && tmp >= -20.0f) {
                                lbl_1_bss_0.player[i]->actor->velY = 0.0f;
                                dpos->y = 250.0f;
                                lbl_1_bss_18[j].takenF = 1;
                                lbl_1_bss_18[j].colF = 0;
                                lbl_1_bss_18[j].duellist = i;
                                lbl_1_bss_48C[i].tookF = 1;
                            } else if(hit) {
                                if(dist <= 1.0f) {
                                    dist = 1.0f;
                                }
                                push = (1.0f+rad)/dist;
                                dx = mul*(dx*push);
                                dz = mul*(dz*push);
                                dpos->x = cx+dx;
                                dpos->z = cz+dz;
                                if(i == 0) {
                                    pushed = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        dx = -lbl_1_bss_48C[i].pos.x;
        dz = -lbl_1_bss_48C[i].pos.z;
        dist = sqrt((dx*dx)+(dz*dz));
        if(dist > 580.0f) {
            push = 580.0f/dist;
            dx = dx*push;
            dz = dz*push;
            lbl_1_bss_48C[i].pos.x = -dx;
            lbl_1_bss_48C[i].pos.z = -dz;
            clamped = 1;
        }
    }
    if(lbl_1_bss_70C.sepMode != 0) {
        mdl[0] = &Hu3DData[lbl_1_bss_1EF8->models[0x86].modelId];
        mdl[1] = &Hu3DData[lbl_1_bss_1EF8->models[0x87].modelId];
        dx = mdl[1]->pos.x-mdl[0]->pos.x;
        dz = mdl[1]->pos.z-mdl[0]->pos.z;
        dist = sqrt((dx*dx)+(dz*dz));
        if(dist < 70.0f) {
            if(dist <= 1.0f) {
                dist = 1.0f;
            }
            push = 70.0f/dist;
            dx = dx*push;
            dz = dz*push;
            if(lbl_1_bss_70C.sepMode == 1) {
                mdl[0]->pos.x = mdl[1]->pos.x-dx;
                mdl[0]->pos.z = mdl[1]->pos.z-dz;
            } else {
                mdl[1]->pos.x = mdl[0]->pos.x+dx;
                mdl[1]->pos.z = mdl[0]->pos.z+dz;
            }
            lbl_1_bss_70C.sepCnt++;
        } else {
            lbl_1_bss_70C.sepCnt = 0;
        }
    }
}

/*
 * 183 insns. Seed one computer duellist's difficulty from five tables indexed by
 * its difficulty row, then give it a first slot to aim at.
 */
void fn_1_C650(s16 player)
{
    float accelTbl[4] = { 6.0f, 6.5454545f, 8.0f, 10.285714f };
    float speedTbl[4] = { 6.5454545f, 7.2f, 9.0f, 12.0f };
    s16 waitTbl[4] = { 14, 11, 8, 6 };
    s16 probTbl[4] = { 2, 35, 40, 50 };
    s16 randTbl[4] = { 1, 5, 10, 100 };

    if(lbl_1_bss_1EF8->chr[player].dif != 0) {
        lbl_1_bss_48C[player].comF = 1;
        lbl_1_bss_48C[player].dif = lbl_1_bss_1EF8->chr[player].dif-1;
        lbl_1_bss_48C[player].unk0A0 = accelTbl[lbl_1_bss_48C[player].dif];
        lbl_1_bss_48C[player].chaseVelZ = accelTbl[lbl_1_bss_48C[player].dif];
        lbl_1_bss_48C[player].chaseRadius = speedTbl[lbl_1_bss_48C[player].dif];
        lbl_1_bss_48C[player].waitMax = waitTbl[lbl_1_bss_48C[player].dif];
        lbl_1_bss_48C[player].prob = probTbl[lbl_1_bss_48C[player].dif];
        lbl_1_bss_48C[player].randMax = randTbl[lbl_1_bss_48C[player].dif];
        fn_1_D070(player);
    }
}

/*
 * 91 insns. One computer duellist's outer step: clear its pad, pick a slot on
 * the first pass and then run the chase/jump machine, restarting it each time
 * that reports done.
 */
s16 fn_1_C92C(s16 player)
{
    s16 result;
    s16 endF;

    result = 0;
    endF = 0;
    lbl_1_bss_48C[player].stkX = 0;
    lbl_1_bss_48C[player].stkY = 0;
    lbl_1_bss_48C[player].btnDown = 0;
    lbl_1_bss_48C[player].btn = 0;
    switch(lbl_1_bss_48C[player].state) {
        case 0:
            lbl_1_bss_48C[player].state++;

        case 1:
            fn_1_D1B8(player);
            lbl_1_bss_48C[player].state++;

        case 2:
            endF = fn_1_CC28(player);
            if(endF != 0) {
                lbl_1_bss_48C[player].state = 1;
            }
            break;
    }
    return result;
}

/* 100 insns. Walk one computer duellist to its chosen slot. Returns 1 on arrival. */
s16 fn_1_CA98(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_48C[player].chaseState) {
        case 0:
            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_48C[player].chaseState++;
            break;

        case 1:
            doneF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_48C[player].chasePos, lbl_1_bss_48C[player].chaseVelZ, lbl_1_bss_48C[player].chaseRadius);
            if(doneF != 0) {
                lbl_1_bss_48C[player].chaseState++;
            }
            break;

        case 2:
            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
            lbl_1_bss_48C[player].chaseState = 0;
            result = 1;
            break;
    }
    return result;
}

/*
 * 274 insns. One computer duellist's jump machine. Case 0 inlines the whole of
 * fn_1_CA98's chase; once there it presses A, holds it for the difficulty's
 * wait, and reports done. A duellist that has been landed on 60 times while
 * game.hitF is set gives up and restarts.
 */
s16 fn_1_CC28(s16 player)
{
    s16 result;
    s16 chaseEndF;

    result = 0;
    chaseEndF = 0;
    switch(lbl_1_bss_48C[player].comState) {
        case 0:
            chaseEndF = fn_1_CA98(player);
            if(chaseEndF != 0) {
                lbl_1_bss_48C[player].comState++;
            } else {
                if(lbl_1_bss_48C[player].hitCnt >= 60) {
                    lbl_1_bss_48C[player].hitCnt = 0;
                    lbl_1_bss_48C[player].comState = 4;
                }
                if(lbl_1_bss_70C.hitF == 0) {
                    lbl_1_bss_48C[player].hitCnt = 0;
                }
            }
            break;

        case 1:
            if(lbl_1_bss_0.player[player]->mode == 0) {
                lbl_1_bss_48C[player].btnDown |= PAD_BUTTON_A;
                lbl_1_bss_48C[player].waitCnt = 0;
                lbl_1_bss_48C[player].comState++;
            }
            break;

        case 2:
            lbl_1_bss_48C[player].btn |= PAD_BUTTON_A;
            if(lbl_1_bss_48C[player].waitCnt++ >= lbl_1_bss_48C[player].waitMax) {
                lbl_1_bss_48C[player].waitCnt = 0;
                lbl_1_bss_48C[player].comState++;
            }
            break;

        case 3:
            if(lbl_1_bss_48C[player].waitCnt++ >= lbl_1_bss_48C[player].waitMax) {
                lbl_1_bss_48C[player].comState = 0;
                result = 1;
            }
            break;

        case 4:
            lbl_1_bss_48C[player].comState = 0;
            result = 1;
            break;
    }
    return result;
}

/*
 * 82 insns. Mark the slots this computer duellist will not consider: every slot
 * with no live stage object on it is written off with the difficulty's
 * probability, so a harder computer rules out fewer of them.
 */
void fn_1_D070(s16 player)
{
    s16 i;
    s16 j;
    s16 foundF;
    s16 roll;

    for(i=0; i<64; i++) {
        if(lbl_1_bss_48C[player].slotF[i] == 0) {
            j = 0;
            foundF = 0;
            for(; j<lbl_1_bss_478.objNum; j++) {
                if(lbl_1_bss_18[j].activeF != 0 && i == lbl_1_bss_18[j].slot) {
                    foundF = 1;
                    break;
                }
            }
            if(foundF == 0) {
                roll = frandmod(100);
                if(roll < lbl_1_bss_48C[player].prob) {
                    lbl_1_bss_48C[player].slotF[i] = 1;
                }
            }
        }
    }
}

/*
 * 507 insns. Pick the computer duellist's next slot. The four corners are always
 * ruled out. A zero roll takes a purely random free slot; otherwise it takes the
 * free slot nearest the duellist. The grid is 8x8 at 100-unit spacing centred on
 * -360.
 */
void fn_1_D1B8(s16 player)
{
    s16 i;
    s16 slot;
    s16 bestSlot;
    s16 foundF;
    s16 randF;
    float dx;
    float dz;
    float dist;
    float nearest;

    randF = 0;
    foundF = 0;
    lbl_1_bss_48C[player].slotF[0] = 1;
    lbl_1_bss_48C[player].slotF[7] = 1;
    lbl_1_bss_48C[player].slotF[56] = 1;
    lbl_1_bss_48C[player].slotF[63] = 1;
    slot = frandmod(lbl_1_bss_48C[player].randMax);
    if(slot == 0) {
        do {
            foundF++;
            slot = frandmod(64);
            randF = 1;
        } while((randF == 0 && foundF < 100) || (lbl_1_bss_48C[player].slotF[slot] != 0 && foundF < 100));
        lbl_1_bss_48C[player].chasePos.x = (100.0f*(slot%8))-360.0f;
        lbl_1_bss_48C[player].chasePos.z = (100.0f*(slot/8))-360.0f;
        lbl_1_bss_48C[player].slotF[slot] = 1;
        lbl_1_bss_48C[player].slotNo = slot;
    } else {
        i = 0;
        foundF = 0;
        nearest = 10000.0f;
        for(; i<64; i++) {
            if(lbl_1_bss_48C[player].slotF[i] == 0) {
                dx = lbl_1_bss_48C[player].pos.x-((100.0f*(i%8))-360.0f);
                dz = lbl_1_bss_48C[player].pos.z-((100.0f*(i/8))-360.0f);
                dist = sqrt((dx*dx)+(dz*dz));
                if(nearest >= dist) {
                    foundF = 1;
                    nearest = dist;
                    bestSlot = i;
                }
            }
        }
        if(foundF == 0) {
            slot = frandmod(64);
            lbl_1_bss_48C[player].chasePos.x = (100.0f*(slot%8))-360.0f;
            lbl_1_bss_48C[player].chasePos.z = (100.0f*(slot/8))-360.0f;
            lbl_1_bss_48C[player].slotF[slot] = 1;
            lbl_1_bss_48C[player].slotNo = slot;
        } else {
            lbl_1_bss_48C[player].chasePos.x = (100.0f*(bestSlot%8))-360.0f;
            lbl_1_bss_48C[player].chasePos.z = (100.0f*(bestSlot/8))-360.0f;
            lbl_1_bss_48C[player].slotF[bestSlot] = 1;
            lbl_1_bss_48C[player].slotNo = bestSlot;
        }
    }
}
