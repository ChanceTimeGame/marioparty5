/*
 * m541dll/game.c -- the duel. Written from the reference assembly, functions
 * in reference order; line ranges are into
 * build/mp5-asm/m541Dll/asm/REL/m541Dll/game.s.
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
#include "game/mg/colman.h"

#include "REL/m541Dll/m541.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_2AD4(M541_WORK *work);
s16 fn_1_5C98(M541_WORK *work);
s16 fn_1_5DA4(void);
s16 fn_1_5DD8(void);
s16 fn_1_5E48(void);
s16 fn_1_6728(void);
s16 fn_1_6BF0(void);
s16 fn_1_6C38(void);
s16 fn_1_6E20(void);
s16 fn_1_6E50(void);
void fn_1_6EA8(void);
void fn_1_72D8(void);
void fn_1_758C(void);
s16 fn_1_7850(s16 player);
s16 fn_1_7DE8(s16 player);
s16 fn_1_832C(s16 player);
s16 fn_1_B4E0(s16 player);
s16 fn_1_92FC(s16 recF);
void fn_1_A884(void);
s16 fn_1_A9B8(s16 no, s16 arg, float x, float z);
s16 fn_1_DDCC(void);
int fn_1_E0A4(void);
int fn_1_E900(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_E91C(MGACTOR *actor, int param);
void fn_1_E930(void);
void fn_1_11710(s16 player);
void fn_1_11B7C(void);
s16 fn_1_11BF8(s16 player);
s16 fn_1_11DE8(s16 player);
s16 fn_1_12008(s16 num);
s16 fn_1_12830(void);
void fn_1_12F40(void);
s16 fn_1_14714(s16 player);
s16 fn_1_14EB0(s16 player);
s16 fn_1_187F8(void);
void fn_1_194B4(void);
s16 fn_1_19738(s16 no, float x, float z);

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s32 lbl_1_bss_3734;                 /* unreferenced; dtk sizes lbl_1_bss_3730 8 */
M541_WORK *lbl_1_bss_3730;
M541_MOVERMDL lbl_1_bss_36A4[23];
s32 lbl_1_bss_36A0;

/* --- .data --- */

float lbl_1_data_368[8][4] = {
    { 230.0f, -554.0f, 554.0f, -230.0f },
    { 554.0f, -230.0f, 554.0f, 230.0f },
    { 554.0f, 230.0f, 230.0f, 554.0f },
    { 230.0f, 554.0f, -230.0f, 554.0f },
    { -230.0f, 554.0f, -554.0f, 230.0f },
    { -554.0f, 230.0f, -554.0f, -230.0f },
    { -554.0f, -230.0f, -230.0f, -554.0f },
    { -230.0f, -554.0f, 230.0f, -554.0f }
};

/* Wall lines a*x+b*z+c = 0, one per side of the octagon. */
float lbl_1_data_3E8[8][3] = {
    { -1.0f, 1.0f, 784.0f }, { 1.0f, 0.0f, -554.0f }, { 1.0f, 1.0f, -784.0f }, { 0.0f, 1.0f, -554.0f },
    { -1.0f, 1.0f, -784.0f }, { 1.0f, 0.0f, 554.0f }, { 1.0f, 1.0f, 784.0f }, { 0.0f, 1.0f, 554.0f }
};

/* 3185 insns. Init step: clear the state, build the stage, platforms and duellists. */
void fn_1_2AD4(M541_WORK *work)
{
    MGACTOR_PARAM param;
    s16 tbl[10];
    float angle[8];
    s16 i;
    s16 j;
    float r;
    float a1;
    float a2;

    memset(&lbl_1_bss_2734, 0, sizeof(M541_GAME));
    memset(lbl_1_bss_2614, 0, sizeof(lbl_1_bss_2614));
    memset(&lbl_1_bss_45C, 0, sizeof(M541_BIG));
    memset(&lbl_1_bss_2F0, 0, sizeof(M541_STAGE));
    memset(lbl_1_bss_20, 0, sizeof(lbl_1_bss_20));
    memset(&lbl_1_bss_0, 0, sizeof(M541_ACTORS));
    lbl_1_bss_3730 = work;
    for(i=0; i<4; i++) {
        lbl_1_bss_2734.seF[i] = -1;
    }
    lbl_1_bss_2614[0].tint = 255.0f;
    lbl_1_bss_2614[1].tint = 255.0f;
    for(i=0; i<23; i++) {
        lbl_1_bss_36A4[i].mdlNo[0] = (i*3)+36;
        lbl_1_bss_36A4[i].mdlNo[1] = (i*3)+37;
        lbl_1_bss_36A4[i].mdlNo[2] = (i*3)+38;
    }
    lbl_1_bss_2F0.speed = 4.0f;
    for(i=0; i<10; i++) {
        lbl_1_bss_45C.recTimer[i] = frandmod(180)+240;
        lbl_1_bss_45C.recPick[i] = frandmod(8);
    }
    for(i=15, j=0; i<23; i++, j++) {
        lbl_1_bss_45C.pos[i].x = lbl_1_data_368[j][0];
        lbl_1_bss_45C.pos[i].y = 0.0f;
        lbl_1_bss_45C.pos[i].z = lbl_1_data_368[j][1];
    }
    for(i=0; i<15; i++) {
        lbl_1_bss_45C.recPlace[i].x = 10.0f*frandmod(36);
        lbl_1_bss_45C.recPlace[i].y = 50.0f+(10.0f*frandmod(45));
        lbl_1_bss_45C.recPlace[i].z = frandmod(360);
    }
    for(i=0; i<6; i++) {
        lbl_1_bss_3730->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[i].modelId, 1);
        if(i == 3 || i == 4) {
            Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 4);
        } else {
            Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 1);
        }
        lbl_1_bss_3730->models[i].pos.x = 0.0f;
        lbl_1_bss_3730->models[i].pos.y = 0.0f;
        lbl_1_bss_3730->models[i].pos.z = 0.0f;
        lbl_1_bss_3730->models[i].rot.x = 0.0f;
        lbl_1_bss_3730->models[i].rot.y = 0.0f;
        lbl_1_bss_3730->models[i].rot.z = 0.0f;
        if(i == 0) {
            Hu3DModelShadowMapSet(lbl_1_bss_3730->models[i].modelId);
        } else {
            if(i == 4) {
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 0.5f);
            } else {
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 1.0f);
            }
            Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
            Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
    }
    lbl_1_bss_3730->models[105].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[11], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3730->models[105].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3730->models[105].modelId, 1);
    lbl_1_bss_3730->models[105].pos.x = 0.0f;
    lbl_1_bss_3730->models[105].pos.y = 0.0f;
    lbl_1_bss_3730->models[105].pos.z = 0.0f;
    lbl_1_bss_3730->models[105].rot.x = 0.0f;
    lbl_1_bss_3730->models[105].rot.y = 0.0f;
    lbl_1_bss_3730->models[105].rot.z = 0.0f;
    tbl[0] = 6;
    tbl[1] = 7;
    tbl[2] = 10;
    for(i=0; i<23; i++) {
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[tbl[0]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, 4);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.y = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.z = 0.0f;
        if(i < 15) {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, 0.6f, 0.6f, 0.6f);
        } else {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, 0.8f, 0.8f, 0.8f);
        }
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[tbl[1]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 4);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.z = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].rot.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].rot.y = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].rot.z = 0.0f;
        if(i < 15) {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 0.6f, 0.6f, 0.6f);
        } else {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 0.8f, 0.8f, 0.8f);
        }
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[tbl[2]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF|HU3D_ATTR_MOTION_OFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, 3);
        Hu3DModelShadowSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId);
        Hu3DModelShadowDispOff(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId);
        Hu3DModelTPLvlSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, 1.0f);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.y = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.z = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].rot.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].rot.y = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
        if(i < 15) {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, 0.6f, 0.6f, 0.6f);
        } else {
            Hu3DModelScaleSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId, 0.8f, 0.8f, 0.8f);
        }
    }
    for(i=0; i<1; i++) {
        lbl_1_bss_20[i].activeF = 1;
        r = frandmod(360);
        lbl_1_bss_20[i].angle = r;
        lbl_1_bss_20[0].angle = 90.0f;
        lbl_1_bss_20[i].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[i].angle/180.0);
        lbl_1_bss_20[i].vel.y = 0.0f;
        lbl_1_bss_20[i].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[i].angle/180.0);
        a1 = frandmod(360);
        a2 = frandmod(360);
        r = frandmod(300);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x = r*cos(M_PI*a1/180.0);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z = r*sin(M_PI*a2/180.0);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[0].mdlNo[0]].pos.x = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[0].mdlNo[0]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[0].mdlNo[0]].pos.z = 0.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos;
        Hu3DModelAttrReset(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowDispOn(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId);
        tbl[0] = frandmod(90);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, tbl[0]);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 2.0f);
        lbl_1_bss_20[i].tpLvl = 1.0f;
        lbl_1_bss_20[i].dispF = 1;
        lbl_1_bss_2F0.spawnNum++;
    }
    angle[0] = 292.0f;
    angle[1] = 337.0f;
    angle[2] = 22.0f;
    angle[3] = 67.0f;
    angle[4] = 112.0f;
    angle[5] = 157.0f;
    angle[6] = 202.0f;
    angle[7] = 247.0f;
    for(i=15, j=0; i<23; i++, j++) {
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x = lbl_1_data_368[j][0];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z = lbl_1_data_368[j][1];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.x = lbl_1_data_368[j][0];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos.z = lbl_1_data_368[j][1];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.x = lbl_1_data_368[j][0];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.y = 200.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos.z = lbl_1_data_368[j][1];
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.x = -20.0f;
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.y = 270.0f+(-angle[j]);
        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowDispOn(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].modelId);
        tbl[0] = frandmod(90);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, tbl[0]);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].modelId, 2.0f);
    }
    for(i=6, j=0; i<=15; i++, j++) {
        lbl_1_bss_3730->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[8], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 3);
        Hu3DModelScaleSet(lbl_1_bss_3730->models[i].modelId, 0.66f, 0.66f, 0.66f);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        lbl_1_bss_3730->models[i].pos.x = 0.0f;
        lbl_1_bss_3730->models[i].pos.y = 200.0f;
        lbl_1_bss_3730->models[i].pos.z = 0.0f;
        lbl_1_bss_3730->models[i].rot.x = 0.0f;
        lbl_1_bss_3730->models[i].rot.y = 0.0f;
        lbl_1_bss_3730->models[i].rot.z = 0.0f;
        lbl_1_bss_2F0.scale2[j].x = 0.5f;
        lbl_1_bss_2F0.scale2[j].y = 1.0f;
        lbl_1_bss_2F0.scale2[j].z = 1.0f;
    }
    for(i=16, j=0; i<=25; i++, j++) {
        lbl_1_bss_3730->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[9], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 3);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        lbl_1_bss_3730->models[i].pos.x = 0.0f;
        lbl_1_bss_3730->models[i].pos.y = 200.0f;
        lbl_1_bss_3730->models[i].pos.z = 0.0f;
        lbl_1_bss_3730->models[i].rot.x = 0.0f;
        lbl_1_bss_3730->models[i].rot.y = 0.0f;
        lbl_1_bss_3730->models[i].rot.z = 0.0f;
        lbl_1_bss_2F0.scale[j].x = 1.0f;
        lbl_1_bss_2F0.scale[j].y = 1.0f;
        lbl_1_bss_2F0.scale[j].z = 1.0f;
    }
    for(i=26, j=0; i<=27; i++, j++) {
        lbl_1_bss_3730->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[8], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 3);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
        lbl_1_bss_3730->models[i].pos.x = 0.0f;
        lbl_1_bss_3730->models[i].pos.y = 0.0f;
        lbl_1_bss_3730->models[i].pos.z = 0.0f;
        lbl_1_bss_3730->models[i].rot.x = 0.0f;
        lbl_1_bss_3730->models[i].rot.y = 0.0f;
        lbl_1_bss_3730->models[i].rot.z = 0.0f;
        lbl_1_bss_2F0.scale2[j].x = 1.0f;
        lbl_1_bss_2F0.scale2[j].y = 1.0f;
        lbl_1_bss_2F0.scale2[j].z = 1.0f;
    }
    for(i=28, j=0; i<=35; i++, j++) {
        lbl_1_bss_3730->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3730->stageDataTbl[9], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3730->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3730->models[i].modelId, 3);
        Hu3DModelScaleSet(lbl_1_bss_3730->models[i].modelId, 0.5f, 1.0f, 0.46f);
        Hu3DModelAttrReset(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_MOTATTR_LOOP);
        tbl[0] = frandmod(90);
        Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, tbl[0]);
        Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 3.0f);
        lbl_1_bss_3730->models[i].pos.x = lbl_1_data_368[j][0];
        lbl_1_bss_3730->models[i].pos.y = 199.0f;
        lbl_1_bss_3730->models[i].pos.z = lbl_1_data_368[j][1]-1.0f;
        lbl_1_bss_3730->models[i].rot.x = 0.0f;
        lbl_1_bss_3730->models[i].rot.y = 0.0f;
        lbl_1_bss_3730->models[i].rot.z = 0.0f;
    }
    lbl_1_bss_3730->models[28].rot.x = 0.0f;
    lbl_1_bss_3730->models[28].rot.y = 45.0f;
    lbl_1_bss_3730->models[28].rot.z = 0.0f;
    lbl_1_bss_3730->models[29].rot.x = 0.0f;
    lbl_1_bss_3730->models[29].rot.y = 0.0f;
    lbl_1_bss_3730->models[29].rot.z = 0.0f;
    lbl_1_bss_3730->models[30].rot.x = 0.0f;
    lbl_1_bss_3730->models[30].rot.y = 315.0f;
    lbl_1_bss_3730->models[30].rot.z = 0.0f;
    lbl_1_bss_3730->models[31].rot.x = 0.0f;
    lbl_1_bss_3730->models[31].rot.y = 270.0f;
    lbl_1_bss_3730->models[31].rot.z = 0.0f;
    lbl_1_bss_3730->models[32].rot.x = 0.0f;
    lbl_1_bss_3730->models[32].rot.y = 225.0f;
    lbl_1_bss_3730->models[32].rot.z = 0.0f;
    lbl_1_bss_3730->models[33].rot.x = 0.0f;
    lbl_1_bss_3730->models[33].rot.y = 180.0f;
    lbl_1_bss_3730->models[33].rot.z = 0.0f;
    lbl_1_bss_3730->models[34].rot.x = 0.0f;
    lbl_1_bss_3730->models[34].rot.y = 135.0f;
    lbl_1_bss_3730->models[34].rot.z = 0.0f;
    lbl_1_bss_3730->models[35].rot.x = 0.0f;
    lbl_1_bss_3730->models[35].rot.y = 90.0f;
    lbl_1_bss_3730->models[35].rot.z = 0.0f;
    lbl_1_bss_0.colMdlId[0] = lbl_1_bss_3730->models[105].modelId;
    MgActorColMapInit(lbl_1_bss_0.colMdlId, 1, 10);
    param.height = 150.0f;
    param.radius = 40.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0x8000;
    param.narrowHook = fn_1_E900;
    param.correctHookParam = 0;
    param.correctHook = fn_1_E91C;
    lbl_1_bss_0.player[0] = MgPlayerCreate(lbl_1_bss_3730->chr[0].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[0]->actor->pos.x = -300.0f;
    lbl_1_bss_0.player[0]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[0]->actor->pos.z = -300.0f;
    lbl_1_bss_0.player[0]->actor->rotY = 45.0f;
    Hu3DModelShadowSet(lbl_1_bss_0.player[0]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[0]->actor->mdlId);
    lbl_1_bss_3730->models[106].modelId = lbl_1_bss_0.player[0]->actor->mdlId;
    param.param = 1;
    lbl_1_bss_0.player[1] = MgPlayerCreate(lbl_1_bss_3730->chr[1].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[1]->actor->pos.x = 300.0f;
    lbl_1_bss_0.player[1]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[1]->actor->pos.z = 300.0f;
    lbl_1_bss_0.player[1]->actor->rotY = -135.0f;
    Hu3DModelShadowSet(lbl_1_bss_0.player[1]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[1]->actor->mdlId);
    lbl_1_bss_3730->models[107].modelId = lbl_1_bss_0.player[1]->actor->mdlId;
    Hu3DModelLayerSet(lbl_1_bss_0.player[1]->actor->mdlId, 2);
    Hu3DModelLayerSet(lbl_1_bss_0.player[0]->actor->mdlId, 2);
    CharModelStepFxSet(lbl_1_bss_3730->chr[0].charNo, 0);
    CharModelStepFxSet(lbl_1_bss_3730->chr[1].charNo, 0);
    CharEffectLayerSet(5);
    fn_1_11710(0);
    fn_1_11710(1);
    lbl_1_bss_2614[0].itemHook = CharModelItemHookGet(lbl_1_bss_0.player[0]->charNo, 1, 4);
    lbl_1_bss_2614[1].itemHook = CharModelItemHookGet(lbl_1_bss_0.player[1]->charNo, 1, 4);
    fn_1_1A16C();
    fn_1_2280(0);
    fn_1_2280(1);
    fn_1_758C();
    lbl_1_bss_2734.mgTimer = fn_1_1970(0, 60, 0, 292.0f, 64.0f);
}

/* 67 insns. Init hook. */
s16 fn_1_5C98(M541_WORK *work)
{
    s16 result;
    HU3DMODEL *model;

    result = 1;
    fn_1_2AD4(work);
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    model = &Hu3DData[lbl_1_bss_3730->models[106].modelId];
    lbl_1_bss_2614[0].pos = model->pos;
    model = &Hu3DData[lbl_1_bss_3730->models[107].modelId];
    lbl_1_bss_2614[1].pos = model->pos;
    return result;
}

/* 13 insns. Fade-in hook. */
s16 fn_1_5DA4(void)
{
    s16 result;

    result = 0;
    fn_1_DDCC();
    fn_1_758C();
    return result;
}

/* 28 insns. Start hook. */
s16 fn_1_5DD8(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_2734.mode = 0;
    lbl_1_bss_2734.unk02 = 0;
    lbl_1_bss_2734.unk04 = 0;
    lbl_1_bss_2734.timer = 0;
    fn_1_758C();
    return result;
}

/* 568 insns. Main hook. */
s16 fn_1_5E48(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 result;
    s16 doneF;
    s16 timeUpF;
    s16 i;
    int playerNo;
    HuVecF pos;

    modelA = &Hu3DData[lbl_1_bss_3730->models[106].modelId];
    modelB = &Hu3DData[lbl_1_bss_3730->models[107].modelId];
    result = 0;
    doneF = 1;
    lbl_1_bss_45C.frame++;
    switch(lbl_1_bss_2734.mode) {
        case 0:
            fn_1_19E4(lbl_1_bss_2734.mgTimer);
            lbl_1_bss_2734.mode++;

        case 1:
            timeUpF = fn_1_1A10(lbl_1_bss_2734.mgTimer);
            fn_1_11B7C();
            if(lbl_1_bss_2734.winner == 0 && timeUpF == 0) {
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_2614[i].comF) {
                        fn_1_11BF8(i);
                    }
                }
            }
            doneF *= fn_1_7850(0);
            doneF *= fn_1_7850(1);
            if(lbl_1_bss_2734.winner || timeUpF) {
                lbl_1_bss_2614[0].stopF = 1;
                lbl_1_bss_2614[1].stopF = 1;
                doneF = 1;
            }
            if(doneF || (timeUpF && lbl_1_bss_2614[0].mode == 0 && lbl_1_bss_2614[1].mode == 0)) {
                if(lbl_1_bss_2734.winner == 0) {
                    fn_1_2644(1, 100);
                }
                lbl_1_bss_2734.mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_2734.winner == 0) {
                fn_1_1A38(lbl_1_bss_2734.mgTimer);
            }
            if(lbl_1_bss_2734.winner) {
                MgSeqWinnerSet(lbl_1_bss_3730->chr[lbl_1_bss_2734.winner&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                playerNo = lbl_1_bss_3730->chr[lbl_1_bss_2734.winner&1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
            } else {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            }
            result = 1;
            break;
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_2614[i].comF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], lbl_1_bss_2614[i].stkX, lbl_1_bss_2614[i].stkY, lbl_1_bss_2614[i].btnDown, lbl_1_bss_2614[i].btn);
        }
        if(lbl_1_bss_2614[i].stopF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
        }
    }
    fn_1_A884();
    fn_1_92FC(1);
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_2614[0].oldPos.x = pos.x;
    lbl_1_bss_2614[0].oldPos.y = pos.y;
    lbl_1_bss_2614[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_2614[1].oldPos.x = pos.x;
    lbl_1_bss_2614[1].oldPos.y = pos.y;
    lbl_1_bss_2614[1].oldPos.z = pos.z;
    lbl_1_bss_2614[0].rotY = modelA->rot.y;
    lbl_1_bss_2614[1].rotY = modelB->rot.y;
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_2614[0].pos.x = pos.x;
    lbl_1_bss_2614[0].pos.y = pos.y;
    lbl_1_bss_2614[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_2614[1].pos.x = pos.x;
    lbl_1_bss_2614[1].pos.y = pos.y;
    lbl_1_bss_2614[1].pos.z = pos.z;
    fn_1_E930();
    for(i=0; i<2; i++) {
        if((s32)lbl_1_bss_2614[i].pos.x > 700 || (s32)lbl_1_bss_2614[i].pos.x < -700 || (s32)lbl_1_bss_2614[i].pos.z > 700 || (s32)lbl_1_bss_2614[i].pos.z < -700) {
            lbl_1_bss_2614[0].pos = lbl_1_bss_2614[0].oldPos;
            lbl_1_bss_2614[1].pos = lbl_1_bss_2614[1].oldPos;
            Hu3DModelPosSet(lbl_1_bss_3730->models[106].modelId, lbl_1_bss_2614[0].pos.x, lbl_1_bss_2614[0].pos.y, lbl_1_bss_2614[0].pos.z);
            Hu3DModelPosSet(lbl_1_bss_3730->models[107].modelId, lbl_1_bss_2614[1].pos.x, lbl_1_bss_2614[1].pos.y, lbl_1_bss_2614[1].pos.z);
            Hu3DModelRotSet(lbl_1_bss_3730->models[106].modelId, 0.0f, lbl_1_bss_2614[0].rotY, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_3730->models[107].modelId, 0.0f, lbl_1_bss_2614[1].rotY, 0.0f);
            lbl_1_bss_0.player[0]->actor->rotY = lbl_1_bss_2614[0].rotY;
            lbl_1_bss_0.player[1]->actor->rotY = lbl_1_bss_2614[1].rotY;
            lbl_1_bss_2614[0].vel.x = 0.0f;
            lbl_1_bss_2614[0].vel.z = 0.0f;
            lbl_1_bss_2614[1].vel.x = 0.0f;
            lbl_1_bss_2614[1].vel.z = 0.0f;
        }
    }
    pos.x = lbl_1_bss_2614[0].pos.x;
    pos.y = lbl_1_bss_2614[0].pos.y;
    pos.z = lbl_1_bss_2614[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_2614[1].pos.x;
    pos.y = lbl_1_bss_2614[1].pos.y;
    pos.z = lbl_1_bss_2614[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    if(lbl_1_bss_2734.winner == 0) {
        fn_1_6EA8();
    }
    fn_1_758C();
    return result;
}

/* 306 insns. Finish hook. */
s16 fn_1_6728(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 result;
    int i;
    HuVecF pos;

    modelA = &Hu3DData[lbl_1_bss_3730->models[106].modelId];
    modelB = &Hu3DData[lbl_1_bss_3730->models[107].modelId];
    result = 0;
    lbl_1_bss_2734.mode = 0;
    lbl_1_bss_2734.unk02 = 0;
    lbl_1_bss_2734.unk04 = 0;
    lbl_1_bss_2734.timer = 0;
    fn_1_7850(0);
    fn_1_7850(1);
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_2614[0].oldPos.x = pos.x;
    lbl_1_bss_2614[0].oldPos.y = pos.y;
    lbl_1_bss_2614[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_2614[1].oldPos.x = pos.x;
    lbl_1_bss_2614[1].oldPos.y = pos.y;
    lbl_1_bss_2614[1].oldPos.z = pos.z;
    lbl_1_bss_2614[0].rotY = modelA->rot.y;
    lbl_1_bss_2614[1].rotY = modelB->rot.y;
    MgActorExec();
    for(i=0; i<2; i++) {
        if((s32)lbl_1_bss_2614[i].pos.x > 700 || (s32)lbl_1_bss_2614[i].pos.x < -700 || (s32)lbl_1_bss_2614[i].pos.z > 700 || (s32)lbl_1_bss_2614[i].pos.z < -700) {
            lbl_1_bss_2614[0].pos = lbl_1_bss_2614[0].oldPos;
            lbl_1_bss_2614[1].pos = lbl_1_bss_2614[1].oldPos;
            Hu3DModelPosSet(lbl_1_bss_3730->models[106].modelId, lbl_1_bss_2614[0].pos.x, lbl_1_bss_2614[0].pos.y, lbl_1_bss_2614[0].pos.z);
            Hu3DModelPosSet(lbl_1_bss_3730->models[107].modelId, lbl_1_bss_2614[1].pos.x, lbl_1_bss_2614[1].pos.y, lbl_1_bss_2614[1].pos.z);
            Hu3DModelRotSet(lbl_1_bss_3730->models[106].modelId, 0.0f, lbl_1_bss_2614[0].rotY, 0.0f);
            Hu3DModelRotSet(lbl_1_bss_3730->models[107].modelId, 0.0f, lbl_1_bss_2614[1].rotY, 0.0f);
            lbl_1_bss_0.player[0]->actor->rotY = lbl_1_bss_2614[0].rotY;
            lbl_1_bss_0.player[1]->actor->rotY = lbl_1_bss_2614[1].rotY;
            lbl_1_bss_2614[0].vel.x = 0.0f;
            lbl_1_bss_2614[0].vel.z = 0.0f;
        }
    }
    pos.x = lbl_1_bss_2614[0].pos.x;
    pos.y = lbl_1_bss_2614[0].pos.y;
    pos.z = lbl_1_bss_2614[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_2614[1].pos.x;
    pos.y = lbl_1_bss_2614[1].pos.y;
    pos.z = lbl_1_bss_2614[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    fn_1_758C();
    return result;
}

/* 18 insns. Pre-winner hook. */
s16 fn_1_6BF0(void)
{
    s16 result;

    result = 0;
    fn_1_7850(0);
    fn_1_7850(1);
    result = fn_1_E0A4();
    fn_1_758C();
    return result;
}

/* 122 insns. Winner hook. */
s16 fn_1_6C38(void)
{
    DS_PLAYER *pl;
    s16 result;

    result = 0;
    if(lbl_1_bss_3730->mode[0] == 0) {
        if(lbl_1_bss_2734.winner != 0) {
            pl = &lbl_1_bss_3730->player[lbl_1_bss_2734.winner&1];
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        } else {
            pl = &lbl_1_bss_3730->player[0];
            pl->motNo = 7;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_3730->player[1];
            pl->motNo = 7;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            CharLoseVoicePlay(lbl_1_bss_3730->chr[0].charNo, lbl_1_bss_3730->chr[1].charNo, CHARNO_NONE, CHARNO_NONE);
        }
        lbl_1_bss_3730->mode[0] = 1;
    }
    fn_1_758C();
    if(lbl_1_bss_2734.winner != 0) {
        CharModelVoicePanSet(lbl_1_bss_3730->chr[lbl_1_bss_2734.winner&1].charNo, 64);
    }
    return result;
}

/* 12 insns. */
s16 fn_1_6E20(void)
{
    s16 result;

    result = 1;
    fn_1_758C();
    return result;
}

/* 22 insns. Close hook. */
s16 fn_1_6E50(void)
{
    s16 result;

    result = 1;
    fn_1_2AB4();
    MgActorKill(lbl_1_bss_0.player[0]->actor);
    MgActorKill(lbl_1_bss_0.player[1]->actor);
    return result;
}

/* 268 insns. Move the fifteen platforms along their headings. */
void fn_1_6EA8(void)
{
    s16 i;

    for(i=0; i<15; i++) {
        if(lbl_1_bss_20[i].activeF) {
            if(lbl_1_bss_2F0.speed <= 10.0f) {
                lbl_1_bss_20[i].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[i].angle/180.0);
                lbl_1_bss_20[i].vel.y = 0.0f;
                lbl_1_bss_20[i].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[i].angle/180.0);
            }
            if(lbl_1_bss_20[i].stopF) {
                lbl_1_bss_20[i].vel.x = 0.0f;
                lbl_1_bss_20[i].vel.z = 0.0f;
            }
            lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x += lbl_1_bss_20[i].vel.x;
            lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z += lbl_1_bss_20[i].vel.z;
            lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos;
            lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos;
            lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].rot.y = 90.0f+(-lbl_1_bss_20[i].angle);
        }
    }
    if((lbl_1_bss_2F0.speed += 0.002f) > 10.0f) {
        lbl_1_bss_2F0.speed = 10.0f;
    }
}

/* 173 insns. Unreferenced: push the model table and the duellists' voice pan. */
void fn_1_72D8(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 i;
    s16 j;
    float panF;
    s16 pan;

    modelA = &Hu3DData[lbl_1_bss_3730->models[106].modelId];
    modelB = &Hu3DData[lbl_1_bss_3730->models[107].modelId];
    for(i=0; i<106; i++) {
        Hu3DModelPosSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_3730->models[i].pos.x, lbl_1_bss_3730->models[i].pos.y, lbl_1_bss_3730->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_3730->models[i].rot.x, lbl_1_bss_3730->models[i].rot.y, lbl_1_bss_3730->models[i].rot.z);
    }
    for(i=16, j=0; i<=25; i++, j++) {
        Hu3DModelScaleSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_2F0.scale[j].x, lbl_1_bss_2F0.scale[j].y, lbl_1_bss_2F0.scale[j].z);
    }
    panF = 0.055652175f*modelA->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_3730->chr[0].charNo, pan);
    panF = 0.055652175f*modelB->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_3730->chr[1].charNo, pan);
}

/* 177 insns. The per-frame push: models, voice pan, camera, light and shadow. */
void fn_1_758C(void)
{
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    s16 i;
    s16 j;
    float panF;
    s16 pan;

    modelA = &Hu3DData[lbl_1_bss_3730->models[106].modelId];
    modelB = &Hu3DData[lbl_1_bss_3730->models[107].modelId];
    for(i=0; i<106; i++) {
        Hu3DModelPosSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_3730->models[i].pos.x, lbl_1_bss_3730->models[i].pos.y, lbl_1_bss_3730->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_3730->models[i].rot.x, lbl_1_bss_3730->models[i].rot.y, lbl_1_bss_3730->models[i].rot.z);
    }
    for(i=16, j=0; i<=25; i++, j++) {
        Hu3DModelScaleSet(lbl_1_bss_3730->models[i].modelId, lbl_1_bss_2F0.scale[j].x, lbl_1_bss_2F0.scale[j].y, lbl_1_bss_2F0.scale[j].z);
    }
    panF = 0.055652175f*modelA->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_3730->chr[0].charNo, pan);
    panF = 0.055652175f*modelB->pos.x;
    pan = 64.0f+panF;
    CharModelVoicePanSet(lbl_1_bss_3730->chr[1].charNo, pan);
    fn_1_91C(0);
    fn_1_10C4();
    fn_1_14C4();
}

/* 358 insns. One duellist's round: wait to be hit, react, then stop or carry on. */
s16 fn_1_7850(s16 player)
{
    DS_PLAYER *pl;
    s16 result;

    pl = &lbl_1_bss_3730->player[player];
    result = 0;
    switch(lbl_1_bss_2614[player].mode) {
        case 0:
            if(lbl_1_bss_2614[player].hitType && lbl_1_bss_2734.winner == 0) {
                if(lbl_1_bss_2614[player].hitType == 2) {
                    fn_1_1A38(lbl_1_bss_2734.mgTimer);
                    lbl_1_bss_2734.winner = (player^1)|(player<<1);
                }
                lbl_1_bss_2614[player].stopF = 1;
                lbl_1_bss_2614[player].mode++;
            } else if(lbl_1_bss_2734.winner) {
                lbl_1_bss_2614[player].mode = 6;
            }
            break;

        case 1:
            if(lbl_1_bss_0.player[player]->mode == 0) {
                lbl_1_bss_2614[player].mode++;
            }
            break;

        case 2:
            MgPlayerPauseOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_2614[player].mode++;
            break;

        case 3:
            if(lbl_1_bss_2614[player].hitType == 1) {
                if(fn_1_7DE8(player)) {
                    lbl_1_bss_2614[player].mode++;
                }
            } else {
                if(lbl_1_bss_2614[player].hitMode == 1) {
                    lbl_1_bss_2614[player].hitMode = 0;
                    lbl_1_bss_2614[player].hitResult = 1;
                    if(lbl_1_bss_2734.winner == 0) {
                        omVibrate(lbl_1_bss_3730->chr[player].no, 30, 12, 0);
                    }
                } else if(lbl_1_bss_2614[player].hitMode == 2) {
                    pl->time = 12.0f;
                    lbl_1_bss_2614[player].hitMode = 0;
                    lbl_1_bss_2614[player].hitResult = 2;
                    if(lbl_1_bss_2734.winner == 0) {
                        omVibrate(lbl_1_bss_3730->chr[player].no, 30, 12, 0);
                    }
                } else if(lbl_1_bss_2614[player].hitMode == 3 || lbl_1_bss_2614[player].hitMode == 3) {
                    pl->motNo = -1;
                    lbl_1_bss_2614[player].hitMode = 0;
                    lbl_1_bss_2614[player].hitResult = 0;
                }
                if(fn_1_832C(player)) {
                    lbl_1_bss_2614[player].mode++;
                }
                if(lbl_1_bss_2614[player].hitType == 2) {
                    lbl_1_bss_2734.winner = (player^1)|(player<<1);
                }
            }
            break;

        case 4:
            MgPlayerPauseOff(lbl_1_bss_0.player[player], &lbl_1_bss_2614[player].pos);
            lbl_1_bss_2614[player].mode++;
            break;

        case 5:
            if(lbl_1_bss_2734.winner) {
                lbl_1_bss_2614[player].mode++;
            } else {
                lbl_1_bss_2614[player].stopF = 0;
                lbl_1_bss_2614[player].hitType = 0;
                lbl_1_bss_2614[player].mode = 0;
            }
            break;

        case 6:
            result = 1;
            break;
    }
    return result;
}

/* 337 insns. Hit type 1: the duellist is knocked over and a star model circles its head. */
s16 fn_1_7DE8(s16 player)
{
    DS_PLAYER *pl;
    float offZ;
    s16 result;
    HuVecF pos;

    pl = &lbl_1_bss_3730->player[player];
    offZ = -30.0f;
    result = 0;
    switch(lbl_1_bss_2614[player].hitMode) {
        case 0:
            if(lbl_1_bss_2734.winner == 0) {
                omVibrate(lbl_1_bss_3730->chr[player].no, 30, 6, 6);
            }
            pl->motNo = 5;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_2614[player].hitMode++;
            break;

        case 1:
            if(pl->time > 10.0f) {
                Hu3DModelAttrReset(lbl_1_bss_3730->models[player+26].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3730->models[player+26].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[player+26].modelId, 4.0f);
                Hu3DModelObjPosGet(lbl_1_bss_3730->models[player+106].modelId, lbl_1_bss_2614[player].itemHook, &pos);
                lbl_1_bss_3730->models[player+26].pos.x = pos.x;
                lbl_1_bss_3730->models[player+26].pos.y = pos.y;
                lbl_1_bss_3730->models[player+26].pos.z = pos.z+offZ;
                lbl_1_bss_2614[player].hitMode++;
            }
            break;

        case 2:
            Hu3DModelObjPosGet(lbl_1_bss_3730->models[player+106].modelId, lbl_1_bss_2614[player].itemHook, &pos);
            lbl_1_bss_3730->models[player+26].pos.x = pos.x;
            lbl_1_bss_3730->models[player+26].pos.y = pos.y;
            lbl_1_bss_3730->models[player+26].pos.z = pos.z+offZ;
            if(pl->time >= 80.0f) {
                Hu3DModelAttrReset(lbl_1_bss_3730->models[player+26].modelId, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_3730->models[player+26].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                lbl_1_bss_2614[player].hitMode++;
            }
            break;

        case 3:
            if(pl->endF) {
                lbl_1_bss_2614[player].hitMode++;
            }
            break;

        case 4:
            pl->motNo = 0;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            lbl_1_bss_2614[player].hitMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* 1012 insns. Hit type 2: the duellist is flattened, flashes, and is thrown in two hops. */
s16 fn_1_832C(s16 player)
{
    HU3DMODEL *model;
    DS_PLAYER *pl;
    float offZ;
    s16 result;
    s16 doneF;
    HuVecF pos;
    HuVecF dir;
    float volF;
    float panF;
    s16 vol;
    s16 pan;

    model = &Hu3DData[lbl_1_bss_3730->models[player+106].modelId];
    pl = &lbl_1_bss_3730->player[player];
    offZ = -30.0f;
    result = 0;
    doneF = 0;
    switch(lbl_1_bss_2614[player].hitResult) {
        case 0:
            omVibrate(lbl_1_bss_3730->chr[player].no, 30, 12, 0);
            volF = 0.026956521f*model->pos.z;
            panF = 0.055652175f*model->pos.x;
            vol = 111.0f+volF;
            pan = 64.0f+panF;
            fn_1_2644(1, 100);
            fn_1_27C8(3, vol, pan);
            pl->motNo = 5;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_2614[player].hitResult++;
            break;

        case 1:
            if(pl->time > 10.0f) {
                Hu3DModelAttrReset(lbl_1_bss_3730->models[player+26].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3730->models[player+26].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[player+26].modelId, 4.0f);
                Hu3DModelObjPosGet(lbl_1_bss_3730->models[player+106].modelId, lbl_1_bss_2614[player].itemHook, &pos);
                lbl_1_bss_3730->models[player+26].pos.x = pos.x;
                lbl_1_bss_3730->models[player+26].pos.y = pos.y;
                lbl_1_bss_3730->models[player+26].pos.z = pos.z+offZ;
                lbl_1_bss_2614[player].flashTimer = 0;
                lbl_1_bss_2614[player].unk012 = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 2:
            Hu3DModelObjPosGet(lbl_1_bss_3730->models[player+106].modelId, lbl_1_bss_2614[player].itemHook, &pos);
            lbl_1_bss_3730->models[player+26].pos.x = pos.x;
            lbl_1_bss_3730->models[player+26].pos.y = pos.y;
            lbl_1_bss_3730->models[player+26].pos.z = pos.z+offZ;
            if(lbl_1_bss_2614[player].flashTimer++ == 0) {
                fn_1_2378(player, 0.25f);
            } else if(lbl_1_bss_2614[player].flashTimer > 3) {
                if(lbl_1_bss_2614[player].flashTimer <= 6) {
                    fn_1_24E8(player);
                } else {
                    lbl_1_bss_2614[player].unk012 = 0;
                    lbl_1_bss_2614[player].flashTimer = 0;
                }
            }
            if(pl->time >= 86.0f) {
                fn_1_24E8(player);
                fn_1_2378(player, 0.25f);
                pl->shiftMode = 1;
                pl->shiftMotNo = 2;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 10.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                Hu3DModelAttrReset(lbl_1_bss_3730->models[player+26].modelId, HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_3730->models[player+26].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[player+26].modelId, 0.0f);
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 3:
            if(pl->shiftMode == 3) {
                doneF = fn_1_B4E0(player);
                if(doneF == 0) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 3;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 8.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                    lbl_1_bss_2614[player].hitResult = 9;
                } else {
                    dir.x = lbl_1_bss_2734.jumpFrom.x-lbl_1_bss_2614[player].pos.x;
                    dir.z = lbl_1_bss_2734.jumpFrom.z-lbl_1_bss_2614[player].pos.z;
                    lbl_1_bss_2734.jumpVel.x = dir.x/20.0f;
                    lbl_1_bss_2734.jumpVel.y = 10.0f;
                    lbl_1_bss_2734.jumpVel.z = dir.z/20.0f;
                    lbl_1_bss_2734.jumpGravity = 1.0f;
                    dir.x = lbl_1_bss_2734.jumpTo.x-lbl_1_bss_2734.jumpFrom.x;
                    dir.z = lbl_1_bss_2734.jumpTo.z-lbl_1_bss_2734.jumpFrom.z;
                    lbl_1_bss_2734.hopVel.x = dir.x/16.0f;
                    lbl_1_bss_2734.hopVel.y = 8.0f;
                    lbl_1_bss_2734.hopVel.z = dir.z/16.0f;
                    lbl_1_bss_2734.jumpCnt = 0;
                    lbl_1_bss_2614[player].hitResult++;
                }
            }
            break;

        case 4:
            lbl_1_bss_2614[player].pos.x += lbl_1_bss_2734.jumpVel.x;
            lbl_1_bss_2614[player].pos.y += lbl_1_bss_2734.jumpVel.y;
            lbl_1_bss_2614[player].pos.z += lbl_1_bss_2734.jumpVel.z;
            lbl_1_bss_2734.jumpVel.y -= lbl_1_bss_2734.jumpGravity;
            model->pos = lbl_1_bss_2614[player].pos;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &lbl_1_bss_2614[player].pos);
            if(++lbl_1_bss_2734.jumpCnt >= 10) {
                lbl_1_bss_2734.jumpVel.y = 0.0f;
                lbl_1_bss_2734.jumpCnt = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 5:
            lbl_1_bss_2614[player].pos.x += lbl_1_bss_2734.jumpVel.x;
            lbl_1_bss_2614[player].pos.y += lbl_1_bss_2734.jumpVel.y;
            lbl_1_bss_2614[player].pos.z += lbl_1_bss_2734.jumpVel.z;
            lbl_1_bss_2734.jumpVel.y -= lbl_1_bss_2734.jumpGravity;
            model->pos = lbl_1_bss_2614[player].pos;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &lbl_1_bss_2614[player].pos);
            if(++lbl_1_bss_2734.jumpCnt >= 10) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 2;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 10.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_2734.jumpCnt = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 6:
            lbl_1_bss_2614[player].pos.x += lbl_1_bss_2734.hopVel.x;
            lbl_1_bss_2614[player].pos.y += lbl_1_bss_2734.hopVel.y;
            lbl_1_bss_2614[player].pos.z += lbl_1_bss_2734.hopVel.z;
            lbl_1_bss_2734.hopVel.y -= lbl_1_bss_2734.jumpGravity;
            model->pos = lbl_1_bss_2614[player].pos;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &lbl_1_bss_2614[player].pos);
            if(++lbl_1_bss_2734.jumpCnt >= 8) {
                lbl_1_bss_2734.hopVel.y = 0.0f;
                lbl_1_bss_2734.jumpCnt = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 7:
            lbl_1_bss_2614[player].pos.x += lbl_1_bss_2734.hopVel.x;
            lbl_1_bss_2614[player].pos.y += lbl_1_bss_2734.hopVel.y;
            lbl_1_bss_2614[player].pos.z += lbl_1_bss_2734.hopVel.z;
            lbl_1_bss_2734.hopVel.y -= lbl_1_bss_2734.jumpGravity;
            model->pos = lbl_1_bss_2614[player].pos;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &lbl_1_bss_2614[player].pos);
            if(++lbl_1_bss_2734.jumpCnt >= 8) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 2;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 10.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_2614[player].pos.y = 100.0f;
                model->pos.y = 100.0f;
                lbl_1_bss_2734.jumpCnt = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 8:
            if(pl->shiftMode == 3) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 3;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_2614[player].hitResult++;
            }
            break;

        case 9:
            lbl_1_bss_2614[player].hitResult = 0;
            result = 1;
            break;
    }
    return result;
}

/* 2619 insns. The beam event: pick a chain of platforms at widening ranges, then zap between them. */
s16 fn_1_92FC(s16 recF)
{
    s16 result = 0;
    float rangeTbl[11][2] = {
        { 0.0f, 0.0f },
        { 400.0f, 650.0f },
        { 350.0f, 600.0f },
        { 300.0f, 550.0f },
        { 250.0f, 500.0f },
        { 200.0f, 450.0f },
        { 150.0f, 400.0f },
        { 100.0f, 350.0f },
        { 50.0f, 300.0f },
        { 0.0f, 250.0f },
        { 0.0f, 200.0f }
    };
    s16 i;
    s16 j;
    s16 k;
    s16 foundF;
    s16 pick;
    float x;
    float z;
    float dist;

    switch(lbl_1_bss_2F0.mode) {
        case 0:
            if(recF) {
                lbl_1_bss_2F0.timer = lbl_1_bss_45C.recTimer[lbl_1_bss_2F0.round];
            } else {
                lbl_1_bss_2F0.timer = 120;
            }
            lbl_1_bss_2F0.round++;
            lbl_1_bss_2F0.mode++;
            break;

        case 1:
            if(lbl_1_bss_2F0.timer-- < 0) {
                lbl_1_bss_2F0.timer = 0;
                lbl_1_bss_2F0.mode++;
            }
            if(recF) {
                lbl_1_bss_45C.recTimerCnt++;
            }
            break;

        case 2:
            if(recF) {
                lbl_1_bss_45C.recPickCnt++;
            }
            for(i=0; i<10; i++) {
                lbl_1_bss_2F0.list[i] = -1;
            }
            if(recF) {
                pick = lbl_1_bss_45C.recPick[lbl_1_bss_2F0.round];
            } else {
                pick = frandmod(8);
            }
            lbl_1_bss_2F0.list[0] = pick+15;
            for(j=1; j<=lbl_1_bss_2F0.round; j++) {
                for(i=0; i<15; i++) {
                    for(k=0, foundF=0; k<10; k++) {
                        if(lbl_1_bss_2F0.list[k] == i) {
                            foundF = 1;
                        }
                    }
                    if(foundF == 0 && lbl_1_bss_20[i].activeF) {
                        x = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j-1]].mdlNo[0]].pos.x;
                        z = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j-1]].mdlNo[0]].pos.z;
                        dist = sqrt(x*x+z*z);
                        if(rangeTbl[lbl_1_bss_2F0.round][0] < dist && rangeTbl[lbl_1_bss_2F0.round][1] > dist) {
                            lbl_1_bss_2F0.list[j] = i;
                            lbl_1_bss_2F0.dist[j-1] = dist;
                            x = 180.0*(acos(x/(0.1f+dist))/M_PI);
                            z = 180.0*(asin(z/(0.1f+dist))/M_PI);
                            if(z < 0.0f) {
                                x = 360.0f-x;
                            }
                            lbl_1_bss_2F0.angle[j-1] = x;
                            break;
                        }
                    }
                }
                if(lbl_1_bss_2F0.list[j] == -1) {
                    foundF = 1;
                    break;
                }
            }
            if(foundF) {
                break;
            }
            for(i=15; i<23; i++) {
                if(recF == 0) {
                    i = ((lbl_1_bss_2F0.list[0]-11)%8)+15;
                }
                if(lbl_1_bss_2F0.list[0] != i) {
                    x = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[lbl_1_bss_2F0.round]].mdlNo[0]].pos.x;
                    z = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[lbl_1_bss_2F0.round]].mdlNo[0]].pos.z;
                    dist = sqrt(x*x+z*z);
                    if(rangeTbl[lbl_1_bss_2F0.round][0] < dist && rangeTbl[lbl_1_bss_2F0.round][1] > dist) {
                        lbl_1_bss_2F0.list[lbl_1_bss_2F0.round+1] = i;
                        lbl_1_bss_2F0.dist[lbl_1_bss_2F0.round] = dist;
                        x = 180.0*(acos(x/(0.1f+dist))/M_PI);
                        z = 180.0*(asin(z/(0.1f+dist))/M_PI);
                        if(z < 0.0f) {
                            x = 360.0f-x;
                        }
                        lbl_1_bss_2F0.angle[lbl_1_bss_2F0.round] = x;
                        break;
                    }
                }
            }
            for(i=0; i<=lbl_1_bss_2F0.round+1; i++) {
                if(lbl_1_bss_2F0.list[i] == -1) {
                    i = 99;
                    for(j=0; j<10; j++) {
                        lbl_1_bss_2F0.list[j] = -1;
                    }
                }
            }
            if(lbl_1_bss_2F0.list[0] != -1) {
                lbl_1_bss_2F0.mode++;
            }
            break;

        case 3:
            for(i=0; i<lbl_1_bss_2F0.round+2; i++) {
                lbl_1_bss_3730->models[i+6].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[i]].mdlNo[0]].pos;
                lbl_1_bss_3730->models[i+6].pos.z -= 1.0f;
                Hu3DModelAttrReset(lbl_1_bss_3730->models[i+6].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3730->models[i+6].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3730->models[i+6].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i+6].modelId, 4.0f);
            }
            for(i=1; i<lbl_1_bss_2F0.round+1; i++) {
                lbl_1_bss_20[lbl_1_bss_2F0.list[i]].stopF = 1;
                lbl_1_bss_20[lbl_1_bss_2F0.list[i]].savedVel = lbl_1_bss_20[lbl_1_bss_2F0.list[i]].vel;
                lbl_1_bss_20[lbl_1_bss_2F0.list[i]].vel.x = 0.0f;
                lbl_1_bss_20[lbl_1_bss_2F0.list[i]].vel.y = 0.0f;
                lbl_1_bss_20[lbl_1_bss_2F0.list[i]].vel.z = 0.0f;
            }
            if(recF) {
                lbl_1_bss_2F0.timer = 60;
            } else {
                lbl_1_bss_2F0.timer = 120;
            }
            if(lbl_1_bss_2734.winner == 0) {
                omVibrate(lbl_1_bss_3730->chr[0].no, lbl_1_bss_2F0.timer/2, 6, 6);
                omVibrate(lbl_1_bss_3730->chr[1].no, lbl_1_bss_2F0.timer/2, 6, 6);
            }
            fn_1_270C(0);
            lbl_1_bss_2F0.mode++;
            break;

        case 4:
            if(lbl_1_bss_2F0.timer-- < 0) {
                for(i=0; i<lbl_1_bss_2F0.round+1; i++) {
                    lbl_1_bss_3730->models[i+16].pos = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[i]].mdlNo[0]].pos;
                    lbl_1_bss_3730->models[i+16].pos.y -= 1.0f;
                    lbl_1_bss_3730->models[i+16].pos.z -= 1.0f;
                    Hu3DModelAttrReset(lbl_1_bss_3730->models[i+16].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_3730->models[i+16].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionTimeSet(lbl_1_bss_3730->models[i+16].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i+16].modelId, 3.0f);
                    lbl_1_bss_3730->models[i+16].rot.y = 90.0f+(-lbl_1_bss_2F0.angle[i]);
                    lbl_1_bss_2F0.scale[i].x = 0.7f;
                    lbl_1_bss_2F0.scale[i].z = lbl_1_bss_2F0.dist[i]/1000.0f;
                }
                lbl_1_bss_2F0.beamF = 1;
                if(recF) {
                    lbl_1_bss_2F0.timer = 120;
                } else {
                    lbl_1_bss_2F0.timer = 120;
                }
                if(lbl_1_bss_2734.winner == 0) {
                    omVibrate(lbl_1_bss_3730->chr[0].no, lbl_1_bss_2F0.timer/2, 12, 0);
                    omVibrate(lbl_1_bss_3730->chr[1].no, lbl_1_bss_2F0.timer/2, 12, 0);
                }
                fn_1_29EC(0);
                fn_1_270C(2);
                lbl_1_bss_2F0.mode++;
            }
            break;

        case 5:
            if(lbl_1_bss_2F0.timer-- < 0) {
                for(i=6; i<=25; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_3730->models[i].modelId, 0.0f);
                }
                for(i=1; i<lbl_1_bss_2F0.round+1; i++) {
                    lbl_1_bss_20[lbl_1_bss_2F0.list[i]].stopF = 0;
                    lbl_1_bss_20[lbl_1_bss_2F0.list[i]].vel = lbl_1_bss_20[lbl_1_bss_2F0.list[i]].savedVel;
                }
                fn_1_29EC(2);
                lbl_1_bss_2F0.beamF = 0;
                lbl_1_bss_2F0.mode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 77 insns. Every 300 frames after the first 600, spawn another platform, up to fifteen. */
void fn_1_A884(void)
{
    s16 doneF;

    doneF = 0;
    switch(lbl_1_bss_2F0.spawnMode) {
        case 0:
            if(lbl_1_bss_2F0.spawnTimer >= 600 && lbl_1_bss_2F0.spawnTimer%300 == 0 && lbl_1_bss_2F0.spawnNum < 15) {
                lbl_1_bss_2F0.spawnMode++;
            }
            break;

        case 1:
            doneF = fn_1_A9B8(lbl_1_bss_2F0.spawnNum, 1, 0.0f, 0.0f);
            if(doneF) {
                lbl_1_bss_2F0.spawnNum++;
                lbl_1_bss_2F0.spawnMode = 0;
            }
            break;
    }
    lbl_1_bss_2F0.spawnTimer++;
}

/* 714 insns. Place platform no (type 0 random near x/z, 1 recorded, 2 clear of the others) and raise it. */
s16 fn_1_A9B8(s16 no, s16 type, float x, float z)
{
    M541_MODEL *mdlA;
    M541_MODEL *mdlB;
    M541_MODEL *mdlC;
    s16 result;
    s16 doneNum;
    s16 tries;
    s16 i;
    float angle;
    float radius;
    float dist;
    float len2;
    float time;
    HuVecF d;

    mdlA = &lbl_1_bss_3730->models[lbl_1_bss_36A4[no].mdlNo[0]];
    mdlB = &lbl_1_bss_3730->models[lbl_1_bss_36A4[no].mdlNo[1]];
    mdlC = &lbl_1_bss_3730->models[lbl_1_bss_36A4[no].mdlNo[2]];
    result = 0;
    doneNum = 0;
    tries = 0;
    switch(lbl_1_bss_20[no].spawnMode) {
        case 0:
            if(type == 0) {
                angle = 10.0f*frandmod(36);
                radius = 1.0f+frandmod(8);
                radius = 10.0f*radius;
                angle = frandmod(360);
                lbl_1_bss_20[no].angle = angle;
                mdlA->pos.x = x+radius*cos(M_PI*angle/180.0);
                mdlA->pos.y = 0.0f;
                mdlA->pos.z = z+radius*sin(M_PI*angle/180.0);
            } else if(type == 1) {
                angle = lbl_1_bss_45C.recPlace[no].x;
                radius = lbl_1_bss_45C.recPlace[no].y;
                lbl_1_bss_20[no].angle = lbl_1_bss_45C.recPlace[no].z;
                mdlA->pos.x = x+radius*cos(M_PI*angle/180.0);
                mdlA->pos.y = 0.0f;
                mdlA->pos.z = z+radius*sin(M_PI*angle/180.0);
            } else if(type == 2) {
                angle = frandmod(360);
                lbl_1_bss_20[no].angle = angle;
                do {
                    angle = frandmod(360);
                    dist = 61.0f+frandmod(120);
                    mdlA->pos.x = dist*cos(M_PI*angle/180.0);
                    mdlA->pos.y = 0.0f;
                    mdlA->pos.z = dist*sin(M_PI*angle/180.0);
                    tries++;
                    for(i=0, doneNum=0; i<15; i++) {
                        if(lbl_1_bss_20[i].dispF) {
                            d.x = mdlA->pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x;
                            d.z = mdlA->pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z;
                            len2 = d.x*d.x+d.z*d.z;
                            dist = sqrt(len2);
                            if(dist < 61.0f && tries < 10000) {
                                doneNum = 1;
                                break;
                            }
                        }
                    }
                } while(doneNum);
            }
            mdlB->pos = mdlA->pos;
            mdlC->pos = mdlA->pos;
            Hu3DModelAttrReset(mdlA->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(mdlB->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdlB->modelId, HU3D_MOTATTR_LOOP);
            time = frandmod(90);
            Hu3DMotionTimeSet(mdlB->modelId, time);
            Hu3DMotionSpeedSet(mdlB->modelId, 2.0f);
            lbl_1_bss_3730->models[lbl_1_bss_36A4[no].mdlNo[0]].rot.y = 90.0f+(-lbl_1_bss_20[no].angle);
            Hu3DModelTPLvlSet(mdlA->modelId, lbl_1_bss_20[no].tpLvl);
            Hu3DModelTPLvlSet(mdlC->modelId, lbl_1_bss_20[no].tpLvl);
            Hu3DModelShadowDispOn(mdlC->modelId);
            lbl_1_bss_20[no].dispF = 1;
            lbl_1_bss_20[no].spawnMode++;
            break;

        case 1:
            doneNum += fn_1_1850(&mdlA->pos.y, 90.0f, 0.0f, 200.0f);
            doneNum += fn_1_1850(&mdlB->pos.y, 90.0f, 0.0f, 200.0f);
            doneNum += fn_1_1850(&mdlC->pos.y, 90.0f, 0.0f, 200.0f);
            if((lbl_1_bss_20[no].tpLvl += 0.012f) >= 1.0f) {
                lbl_1_bss_20[no].tpLvl = 1.0f;
            } else {
                doneNum = 1;
            }
            Hu3DModelTPLvlSet(mdlA->modelId, lbl_1_bss_20[no].tpLvl);
            Hu3DModelTPLvlSet(mdlC->modelId, lbl_1_bss_20[no].tpLvl);
            if(doneNum == 0) {
                lbl_1_bss_20[no].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[no].angle/180.0);
                lbl_1_bss_20[no].vel.y = 0.0f;
                lbl_1_bss_20[no].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[no].angle/180.0);
                lbl_1_bss_20[no].activeF = 1;
                lbl_1_bss_20[no].spawnMode = 1;
                result = 1;
            }
            break;
    }
    return result;
}

/* 2619 insns. CPU jump search: casts twenty rays around the direction away
   from the opponent, clips them against the walls and the movers, and picks a
   clear landing spot. */
s16 fn_1_B4E0(s16 player)
{
    float rayX;
    float rayZ;
    float projX;
    float projZ;
    float c1;
    float c2;
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    float boxXMin;
    float boxZMin;
    float boxXMax;
    float boxZMax;
    float dot;
    float angle;
    float dist;
    float len;
    float x0;
    float z0;
    float dx;
    float dz;
    float ix;
    float iz;
    float a2;
    float b2;
    float a1;
    float b1;
    float normAngle;
    float rayAngle;
    s16 i;
    s16 j;
    s16 k;
    s16 result;
    HU3DMODEL *modelOpp;
    HU3DMODEL *modelSelf;
    float wallDist[20];
    float moverDist[20];
    s16 order[20];
    s16 orderB[20];
    HuVecF hit[20];

    modelOpp = &Hu3DData[lbl_1_bss_3730->models[(player^1)+106].modelId];
    modelSelf = &Hu3DData[lbl_1_bss_3730->models[player+106].modelId];
    result = 0;
    boxXMin = modelOpp->pos.x-150.0f;
    boxXMax = 150.0f+modelOpp->pos.x;
    boxZMin = modelOpp->pos.z-110.0f;
    boxZMax = 300.0f+modelOpp->pos.z;
    if(modelSelf->pos.x >= boxXMin && modelSelf->pos.x <= boxXMax && modelSelf->pos.z >= boxZMin && modelSelf->pos.z <= boxZMax) {
        x0 = modelSelf->pos.x-modelOpp->pos.x;
        z0 = modelSelf->pos.z-modelOpp->pos.z;
        dist = sqrt(x0*x0+z0*z0);
        x0 = 180.0*(acos(x0/(0.1f+dist))/M_PI);
        z0 = 180.0*(asin(z0/(0.1f+dist))/M_PI);
        if(z0 < 0.0f) {
            x0 = 360.0f-x0;
        }
        angle = x0;
        for(i=0; i<20; i++) {
            wallDist[i] = 2000.0f;
            moverDist[i] = 2000.0f;
            order[i] = i;
            orderB[i] = i;
        }
        x0 = modelSelf->pos.x;
        z0 = modelSelf->pos.z;
        i = 15;
        for(rayAngle=angle-100.0f, k=0; rayAngle<100.0f+angle; rayAngle+=10.0f, k++) {
            rayX = x0+10.0*cos(M_PI*rayAngle/180.0);
            rayZ = z0+10.0*sin(M_PI*rayAngle/180.0);
            a1 = rayZ-z0;
            b1 = x0-rayX;
            c1 = (-a1*x0)-(b1*z0);
            for(j=0; j<lbl_1_bss_45C.idxNum[i]-1; j++) {
                if(lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x < lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x) {
                    minX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                    maxX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x;
                } else {
                    minX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x;
                    maxX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                }
                if(lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z < lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z) {
                    minZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                    maxZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                } else {
                    minZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                    maxZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                }
                a2 = lbl_1_data_3E8[j][0];
                b2 = lbl_1_data_3E8[j][1];
                c2 = lbl_1_data_3E8[j][2];
                len = sqrt(a1*a1+b1*b1)*sqrt(a2*a2+b2*b2);
                if(len) {
                    dot = ((a1*a2)+(b1*b2))/len;
                } else {
                    dot = 0.0f;
                }
                if(0.0f != dot) {
                    if(a1 && b1 && a2 && b2) {
                        dx = a2*(-b1/a1);
                        dz = -1.0f*(a2*(-c1/a1));
                        dx = dx+b2;
                        dz = dz-c2;
                        if(dx) {
                            iz = dz/dx;
                        } else {
                            iz = 0.0f;
                        }
                        ix = ((-b2*iz)-c2)/a2;
                    } else if(!a1 && b1 && a2 && b2) {
                        iz = -c1/b1;
                        ix = ((-b2*iz)-c2)/a2;
                    } else if(a1 && !b1 && a2 && b2) {
                        ix = -c1/a1;
                        iz = ((-a2*ix)-c2)/b2;
                    } else if(a1 && b1 && !a2 && b2) {
                        iz = -c2/b2;
                        ix = ((-b1*iz)-c1)/a1;
                    } else if(a1 && b1 && a2 && !b2) {
                        ix = -c2/a2;
                        iz = ((-a1*ix)-c1)/b1;
                    } else if(!a1 && b1 && a2 && !b2) {
                        iz = -c1/b1;
                        ix = -c2/a2;
                    } else if(a1 && !b1 && !a2 && b2) {
                        ix = -c1/a1;
                        iz = -c2/b2;
                    }
                    if(ix >= minX && ix <= maxX && iz >= minZ && iz <= maxZ) {
                        dx = ix-x0;
                        dz = iz-z0;
                        minX = 0.0f;
                        minZ = 0.0f;
                        normAngle = rayAngle;
                        if(rayAngle < 0.0f) {
                            normAngle = 360.0f+rayAngle;
                        }
                        if((normAngle >= 0.0f && normAngle < 90.0f) || (normAngle > 270.0f && normAngle <= 360.0f)) {
                            if(dx > 0.0f) {
                                minX = 1.0f;
                            }
                        } else if(90.0f == normAngle || 270.0f == normAngle) {
                            minX = 1.0f;
                        } else if(dx < 0.0f) {
                            minX = 1.0f;
                        }
                        if(normAngle > 0.0f && normAngle < 180.0f) {
                            if(dz > 0.0f) {
                                minZ = 1.0f;
                            }
                        } else if(0.0f == normAngle || 180.0f == normAngle || 360.0f == normAngle) {
                            minZ = 1.0f;
                        } else if(dz < 0.0f) {
                            minZ = 1.0f;
                        }
                        if(minX && minZ) {
                            dx = sqrt(dx*dx+dz*dz);
                            if(dx < wallDist[k]) {
                                wallDist[k] = dx;
                                hit[k].x = ix;
                                hit[k].z = iz;
                            }
                        }
                    }
                } else {
                    wallDist[k] = 0.0f;
                }
            }
            for(j=0; j<lbl_1_bss_2F0.spawnNum; j++) {
                ix = rayX-x0;
                iz = rayZ-z0;
                b2 = ix*ix+iz*iz;
                c2 = -1.0f*((ix*(rayX-lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x))+(iz*(rayZ-lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z)));
                if(b2) {
                    a2 = c2/b2;
                } else {
                    a2 = 0.0f;
                }
                projX = rayX+(ix*a2);
                projZ = rayZ+(iz*a2);
                dx = projX-x0;
                dz = projZ-z0;
                minX = 0.0f;
                minZ = 0.0f;
                normAngle = rayAngle;
                if(rayAngle < 0.0f) {
                    normAngle = 360.0f+rayAngle;
                }
                if((normAngle >= 0.0f && normAngle < 90.0f) || (normAngle > 270.0f && normAngle <= 360.0f)) {
                    if(dx > 0.0f) {
                        minX = 1.0f;
                    }
                } else if(90.0f == normAngle || 270.0f == normAngle) {
                    minX = 1.0f;
                } else if(dx < 0.0f) {
                    minX = 1.0f;
                }
                if(normAngle > 0.0f && normAngle < 180.0f) {
                    if(dz > 0.0f) {
                        minZ = 1.0f;
                    }
                } else if(0.0f == normAngle || 180.0f == normAngle || 360.0f == normAngle) {
                    minZ = 1.0f;
                } else if(dz < 0.0f) {
                    minZ = 1.0f;
                }
                if(minX && minZ) {
                    ix = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-projX;
                    iz = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-projZ;
                    dist = sqrt(ix*ix+iz*iz);
                    if(dist < 70.0f) {
                        dist = sqrt(dx*dx+dz*dz);
                        if(dist <= moverDist[k]) {
                            moverDist[k] = dist;
                        }
                    }
                }
            }
        }
        for(i=0; i<20; i++) {
            for(j=i; j<20; j++) {
                if(wallDist[i] <= wallDist[j] && 2000.0f != wallDist[j]) {
                    dot = wallDist[i];
                    wallDist[i] = wallDist[j];
                    wallDist[j] = dot;
                    k = order[i];
                    order[i] = order[j];
                    order[j] = k;
                }
            }
        }
        dot = 0.0f;
        for(i=0; i<20; i++) {
            if(moverDist[order[i]] >= 150.0f) {
                rayAngle = (angle-100.0f)+(10.0f*order[i]);
                x0 = modelSelf->pos.x+150.0*cos(M_PI*rayAngle/180.0);
                z0 = modelSelf->pos.z+150.0*sin(M_PI*rayAngle/180.0);
                if((-x0)+z0 > -784.0f && x0 < 554.0f && x0+z0 < 784.0f && z0 < 554.0f && (-x0)+z0 < 784.0f && x0 > -554.0f && x0+z0 > -784.0f && z0 > -554.0f) {
                    if(!(x0 >= boxXMin && x0 <= boxXMax && z0 >= boxZMin && z0 <= boxZMax)) {
                        break;
                    }
                }
            }
        }
        if(i >= 20) {
            dot = 1.0f;
        }
        if(1.0f == dot) {
            for(i=0; i<20; i++) {
                rayAngle = (angle-100.0f)+(10.0f*order[i]);
                x0 = modelSelf->pos.x+150.0*cos(M_PI*rayAngle/180.0);
                z0 = modelSelf->pos.z+150.0*sin(M_PI*rayAngle/180.0);
                if((-x0)+z0 > -784.0f && x0 < 554.0f && x0+z0 < 784.0f && z0 < 554.0f && (-x0)+z0 < 784.0f && x0 > -554.0f && x0+z0 > -784.0f && z0 > -554.0f) {
                    if(!(x0 >= boxXMin && x0 <= boxXMax && z0 >= boxZMin && z0 <= boxZMax)) {
                        break;
                    }
                }
            }
            dot = 0.0f;
            if(i >= 20) {
                dot = 1.0f;
            }
        }
        if(1.0f == dot) {
            for(i=0; i<20; i++) {
                rayAngle = (angle-100.0f)+(10.0f*order[i]);
                x0 = modelSelf->pos.x+150.0*cos(M_PI*rayAngle/180.0);
                z0 = modelSelf->pos.z+150.0*sin(M_PI*rayAngle/180.0);
                if((-x0)+z0 > -784.0f && x0 < 554.0f && x0+z0 < 784.0f && z0 < 554.0f && (-x0)+z0 < 784.0f && x0 > -554.0f && x0+z0 > -784.0f && z0 > -554.0f) {
                    break;
                }
            }
            dot = 0.0f;
            if(i >= 20) {
                dot = 1.0f;
            }
        }
        if(1.0f != dot) {
            lbl_1_bss_2734.jumpFrom.x = modelSelf->pos.x+100.0*cos(M_PI*rayAngle/180.0);
            lbl_1_bss_2734.jumpFrom.z = modelSelf->pos.z+100.0*sin(M_PI*rayAngle/180.0);
            lbl_1_bss_2734.jumpTo.x = lbl_1_bss_2734.jumpFrom.x+50.0*cos(M_PI*rayAngle/180.0);
            lbl_1_bss_2734.jumpTo.z = lbl_1_bss_2734.jumpFrom.z+50.0*sin(M_PI*rayAngle/180.0);
            result = 1;
        } else {
            lbl_1_bss_2734.jumpFrom.x = 0.0f;
            lbl_1_bss_2734.jumpFrom.z = 0.0f;
            lbl_1_bss_2734.jumpTo.x = 0.0f;
            lbl_1_bss_2734.jumpTo.z = 0.0f;
            result = 0;
        }
        for(i=0; i<2; i++) {
            if((s32)lbl_1_bss_2734.jumpFrom.x > 700 || (s32)lbl_1_bss_2734.jumpFrom.x < -700 || (s32)lbl_1_bss_2734.jumpFrom.z > 700 || (s32)lbl_1_bss_2734.jumpFrom.z < -700
                || (s32)lbl_1_bss_2734.jumpTo.x > 700 || (s32)lbl_1_bss_2734.jumpTo.x < -700 || (s32)lbl_1_bss_2734.jumpTo.z > 700 || (s32)lbl_1_bss_2734.jumpTo.z < -700) {
                lbl_1_bss_2734.jumpFrom.x = 0.0f;
                lbl_1_bss_2734.jumpFrom.z = 0.0f;
                lbl_1_bss_2734.jumpTo.x = 0.0f;
                lbl_1_bss_2734.jumpTo.z = 0.0f;
                result = 0;
            }
        }
    } else {
        result = 0;
    }
    return result;
}

/* 182 insns. Opening: start the music, run the platform roulette, then raise seven more platforms. */
s16 fn_1_DDCC(void)
{
    DS_PLAYER *pl0 = &lbl_1_bss_3730->player[0];
    DS_PLAYER *pl1 = &lbl_1_bss_3730->player[1];
    s16 result = 0;
    s16 doneF = 1;
    float unusedTbl[8][4] = {
        { 0.0f, -200.0f, 200.0f, -120.0f },
        { -200.0f, 100.0f, 0.0f, 220.0f },
        { 300.0f, 0.0f, -300.0f, 0.0f },
        { 0.0f, -300.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f, 0.0f }
    };
    s16 i;

    switch(lbl_1_bss_2734.mode) {
        case 0:
            fn_1_2614();
            fn_1_270C(1);
            lbl_1_bss_2734.mode++;
            break;

        case 1:
            fn_1_92FC(0);
            if(lbl_1_bss_2F0.mode == 5) {
                pl0->motNo = 4;
                pl0->speed = 1.0f;
                pl0->time = 0.0f;
                pl0->attr = 0;
                pl0->attrReset = HU3D_MOTATTR_LOOP;
                pl1->motNo = 4;
                pl1->speed = 1.0f;
                pl1->time = 0.0f;
                pl1->attr = 0;
                pl1->attrReset = HU3D_MOTATTR_LOOP;
                pl0->nextF = 1;
                pl0->nextMotNo = 0;
                pl0->nextTime = 1.0f;
                pl0->nextAttr = HU3D_MOTATTR_LOOP;
                pl0->nextAttrReset = 0;
                pl1->nextF = 1;
                pl1->nextMotNo = 0;
                pl1->nextTime = 1.0f;
                pl1->nextAttr = HU3D_MOTATTR_LOOP;
                pl1->nextAttrReset = 0;
                lbl_1_bss_2734.mode++;
            }
            break;

        case 2:
            if(fn_1_92FC(0)) {
                lbl_1_bss_2F0.round = 0;
                lbl_1_bss_2734.mode++;
            }
            break;

        case 3:
            for(i=0; i<7; i++) {
                doneF *= fn_1_A9B8(lbl_1_bss_2F0.spawnNum+i, 2, 0.0f, 0.0f);
            }
            if(doneF) {
                lbl_1_bss_2F0.spawnNum += 7;
                lbl_1_bss_2734.mode++;
            }
            break;
        case 4:
            break;
    }
    return result;
}

/* 535 insns. Finish: sink the platforms, turn the winner to the camera and close in. */
int fn_1_E0A4(void)
{
    HU3DMODEL *model = &Hu3DData[lbl_1_bss_3730->models[(lbl_1_bss_2734.winner&1)+106].modelId];
    DS_PLAYER *pl = &lbl_1_bss_3730->player[lbl_1_bss_2734.winner&1];
    int result = 0;
    s16 doneNum = 0;
    s16 i;
    s16 dispNum;
    M541_MODEL *mdlA;
    M541_MODEL *mdlB;
    M541_MODEL *mdlC;
    float speed;

    switch(lbl_1_bss_2734.mode) {
        case 0:
            for(i=6; i<=35; i++) {
                Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
            }
            for(i=15; i<23; i++) {
                lbl_1_bss_20[i].tpLvl = 1.0f;
                lbl_1_bss_20[i].dispF = 1;
            }
            for(i=0; i<23; i++) {
                if(lbl_1_bss_20[i].dispF) {
                    mdlA = &lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]];
                    lbl_1_bss_20[i].vel.y = 200.0f;
                    lbl_1_bss_20[i].tpLvl = 1.0f;
                }
            }
            fn_1_29EC(0);
            fn_1_29EC(1);
            fn_1_29EC(2);
            lbl_1_bss_2734.mode++;
            break;

        case 1:
            for(i=0, dispNum=0; i<23; i++) {
                if(lbl_1_bss_20[i].dispF) {
                    dispNum++;
                    mdlA = &lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]];
                    mdlB = &lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[1]];
                    mdlC = &lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[2]];
                    speed = 60.0f;
                    doneNum += fn_1_1850(&mdlA->pos.y, speed, lbl_1_bss_20[i].vel.y, 0.0f);
                    doneNum += fn_1_1850(&mdlB->pos.y, speed, lbl_1_bss_20[i].vel.y, 0.0f);
                    doneNum += fn_1_1850(&mdlC->pos.y, speed, lbl_1_bss_20[i].vel.y, 0.0f);
                    if((lbl_1_bss_20[i].tpLvl -= 0.02f) <= 0.0f) {
                        lbl_1_bss_20[i].tpLvl = 0.0f;
                    } else {
                        doneNum = 1;
                    }
                    Hu3DModelTPLvlSet(mdlA->modelId, lbl_1_bss_20[i].tpLvl);
                    Hu3DModelTPLvlSet(mdlB->modelId, lbl_1_bss_20[i].tpLvl);
                    Hu3DModelTPLvlSet(mdlC->modelId, lbl_1_bss_20[i].tpLvl);
                    if(doneNum == 0) {
                        lbl_1_bss_20[i].activeF = 0;
                        lbl_1_bss_20[i].dispF = 0;
                        Hu3DModelAttrSet(mdlA->modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(mdlB->modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(mdlC->modelId, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            if(dispNum == 0 || lbl_1_bss_36A0++ > 80) {
                for(i=6; i<=104; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_3730->models[i].modelId, HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_2734.mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_2734.winner != 0) {
                if(model->rot.y <= 1.0f && model->rot.y >= -1.0f) {
                    lbl_1_bss_2734.mode = 4;
                } else {
                    lbl_1_bss_2734.rotYEnd = model->rot.y;
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 1;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 4.0f;
                    pl->shiftAttr = 0;
                    pl->attrReset = HU3D_MOTATTR_LOOP;
                    lbl_1_bss_2734.mode = 3;
                }
            } else {
                lbl_1_bss_2734.mode = 5;
            }
            break;

        case 3:
            speed = 30.0f;
            doneNum += fn_1_1850(&model->rot.y, speed, lbl_1_bss_2734.rotYEnd, 0.0f);
            if(doneNum == 0) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 4.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_2734.mode++;
            }
            break;

        case 4:
            speed = 30.0f;
            doneNum += fn_1_1850(&lbl_1_bss_1C->center.x, speed, lbl_1_data_1F8[1].center.x, model->pos.x);
            doneNum += fn_1_1850(&lbl_1_bss_1C->center.y, speed, lbl_1_data_1F8[1].center.y, 70.0f+model->pos.y);
            doneNum += fn_1_1850(&lbl_1_bss_1C->center.z, speed, lbl_1_data_1F8[1].center.z, model->pos.z);
            doneNum += fn_1_1850(&lbl_1_bss_1C->rot.x, speed, lbl_1_data_1F8[1].rot.x, -18.0f);
            doneNum += fn_1_1850(&lbl_1_bss_1C->zoom, speed, lbl_1_data_1F8[1].zoom, 500.0f);
            if(doneNum == 0) {
                lbl_1_bss_2734.mode++;
            }
            break;

        case 5:
            result = 1;
            break;
    }
    return result;
}

/* 7 insns. The duellists' narrow-phase hook: nothing is ever reported. */
int fn_1_E900(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    switch(b->type) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
    }
    return 0;
}

/* 5 insns. The duellists' correction hook: reads the player number and does nothing. */
void fn_1_E91C(MGACTOR *actor, int param)
{
    int unused;

    unused = actor->param;
}

/*
 * 2936 insns. Per-frame collision: platforms bounce off each other and off the
 * eight walls; a duellist touching a platform, the beam between the linked
 * platforms, or a wall is pushed back and marked hit (hitType 2).
 */
void fn_1_E930(void)
{
    s16 unused0 = 0;
    s16 unused1 = 0;
    s16 unused2 = 0;
    float t;
    float sign;
    float tx;
    float tz;
    float scale;
    float radius = 30.0f;
    float moverR = 30.000002f;
    float pushOfs = 10.0f;
    float wallAngle[8] = { 90.0f, 180.0f, -90.0f, 0.0f, 90.0f, -180.0f, -90.0f, 0.0f };
    s16 i;
    s16 j;
    float dx;
    float dz;
    float dist;
    float nz;
    float nx;

    for(i=0; i<15; i++) {
        if(lbl_1_bss_20[i].activeF && !lbl_1_bss_20[i].stopF) {
            for(j=0; j<15; j++) {
                if(lbl_1_bss_20[j].activeF && i != j) {
                    dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x;
                    dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z;
                    dist = sqrt(dx*dx+dz*dz);
                    if(dist < radius+moverR) {
                        if(dist <= 1.0f) {
                            dist = 1.0f;
                        }
                        scale = (10.0f+(radius+moverR))/dist;
                        dx *= scale;
                        dz *= scale;
                        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-dx;
                        lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-dz;
                        dist = sqrt(((lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x)*(lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x))+((lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z)*(lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z)));
                        if(dist <= 1.0f) {
                            dist = 1.0f;
                        }
                        nz = nx = 0.0f;
                        nz = (lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z)/dist;
                        nx = (lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x)/dist;
                        if(nz == 0.0f && nx == 0.0f) {
                            nz = 1.0f;
                            nx = 0.0f;
                        }
                        dx = (nx*lbl_1_bss_20[j].vel.x)+(nz*lbl_1_bss_20[j].vel.z);
                        dz = (nz*(-lbl_1_bss_20[i].vel.x))+(nx*lbl_1_bss_20[i].vel.z);
                        tx = (nx*lbl_1_bss_20[i].vel.x)+(nz*lbl_1_bss_20[i].vel.z);
                        tz = (nz*(-lbl_1_bss_20[j].vel.x))+(nx*lbl_1_bss_20[j].vel.z);
                        lbl_1_bss_20[i].vel.x = (dx*nx)-(dz*nz);
                        lbl_1_bss_20[i].vel.z = (dz*nx)+(dx*nz);
                        lbl_1_bss_20[j].vel.x = (tx*nx)-(tz*nz);
                        lbl_1_bss_20[j].vel.z = (tz*nx)+(tx*nz);
                        dx = sqrt((lbl_1_bss_20[i].vel.x*lbl_1_bss_20[i].vel.x)+(lbl_1_bss_20[i].vel.z*lbl_1_bss_20[i].vel.z));
                        dz = sqrt((lbl_1_bss_20[j].vel.x*lbl_1_bss_20[j].vel.x)+(lbl_1_bss_20[j].vel.z*lbl_1_bss_20[j].vel.z));
                        if(dx) {
                            dx = lbl_1_bss_2F0.speed/dx;
                        } else {
                            dx = 0.0f;
                        }
                        if(dz) {
                            dz = lbl_1_bss_2F0.speed/dz;
                        } else {
                            dz = 0.0f;
                        }
                        lbl_1_bss_20[i].vel.x *= dx;
                        lbl_1_bss_20[i].vel.z *= dx;
                        lbl_1_bss_20[j].vel.x *= dz;
                        lbl_1_bss_20[j].vel.z *= dz;
                        dx = 180.0*(acos(lbl_1_bss_20[i].vel.x/(0.1f+lbl_1_bss_2F0.speed))/M_PI);
                        dz = 180.0*(asin(lbl_1_bss_20[i].vel.z/(0.1f+lbl_1_bss_2F0.speed))/M_PI);
                        if(dz < 0.0f) {
                            dx = 360.0f-dx;
                        }
                        lbl_1_bss_20[i].angle = dx;
                        lbl_1_bss_20[i].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[i].angle/180.0);
                        lbl_1_bss_20[i].vel.y = 0.0f;
                        lbl_1_bss_20[i].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[i].angle/180.0);
                        if(lbl_1_bss_20[j].stopF == 0) {
                            dx = 180.0*(acos(lbl_1_bss_20[j].vel.x/(0.1f+lbl_1_bss_2F0.speed))/M_PI);
                            dz = 180.0*(asin(lbl_1_bss_20[j].vel.z/(0.1f+lbl_1_bss_2F0.speed))/M_PI);
                            if(dz < 0.0f) {
                                dx = 360.0f-dx;
                            }
                            lbl_1_bss_20[j].angle = dx;
                            lbl_1_bss_20[j].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[j].angle/180.0);
                            lbl_1_bss_20[j].vel.y = 0.0f;
                            lbl_1_bss_20[j].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[j].angle/180.0);
                        }
                    }
                }
            }
            dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x;
            dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z;
            for(j=0; j<8; j++) {
                dx = lbl_1_data_368[j][0]-lbl_1_data_368[j][2];
                dz = lbl_1_data_368[j][1]-lbl_1_data_368[j][3];
                nz = dx*dx+dz*dz;
                nx = -1.0f*((dx*(lbl_1_data_368[j][0]-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x))+(dz*(lbl_1_data_368[j][1]-lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z)));
                if(nz) {
                    t = nx/nz;
                } else {
                    t = 0.0f;
                }
                tx = (dx*t)+lbl_1_data_368[j][0];
                tz = (dz*t)+lbl_1_data_368[j][1];
                dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x-tx;
                dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z-tz;
                dist = sqrt(dx*dx+dz*dz);
                if(dist < moverR) {
                    if(dist <= 1.0f) {
                        dist = 1.0f;
                    }
                    scale = moverR/dist;
                    dx *= scale;
                    dz *= scale;
                    lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.x = tx+dx;
                    lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos.z = tz+dz;
                    lbl_1_bss_20[i].angle = 360.0f-lbl_1_bss_20[i].angle;
                    lbl_1_bss_20[i].angle += wallAngle[j];
                    if(lbl_1_bss_20[i].angle >= 360.0f) {
                        lbl_1_bss_20[i].angle -= 360.0f;
                    }
                    lbl_1_bss_20[i].vel.x = lbl_1_bss_2F0.speed*cos(M_PI*lbl_1_bss_20[i].angle/180.0);
                    lbl_1_bss_20[i].vel.y = 0.0f;
                    lbl_1_bss_20[i].vel.z = lbl_1_bss_2F0.speed*sin(M_PI*lbl_1_bss_20[i].angle/180.0);
                }
            }
        }
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_2614[i].hitType != 2) {
            for(j=0; j<15; j++) {
                if(lbl_1_bss_20[j].activeF) {
                    dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.x-lbl_1_bss_2614[i].pos.x;
                    dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[j].mdlNo[0]].pos.z-lbl_1_bss_2614[i].pos.z;
                    dist = sqrt(dx*dx+dz*dz);
                    if(dist < radius+moverR) {
                        if(dist <= 1.0f) {
                            dist = 1.0f;
                        }
                        scale = (radius+moverR)/dist;
                        dx *= scale;
                        dz *= scale;
                        lbl_1_bss_2614[i].hitType = 2;
                    }
                }
            }
            if(lbl_1_bss_2F0.beamF) {
                for(j=0; j<lbl_1_bss_2F0.round+1; j++) {
                    if(lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x < lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.x) {
                        dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x;
                        tx = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.x;
                    } else {
                        dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.x;
                        tx = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x;
                    }
                    if(lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z < lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.z) {
                        dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z;
                        tz = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.z;
                    } else {
                        dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.z;
                        tz = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z;
                    }
                    if(radius+lbl_1_bss_2614[i].pos.x >= dx && lbl_1_bss_2614[i].pos.x-radius <= tx && radius+lbl_1_bss_2614[i].pos.z >= dz && lbl_1_bss_2614[i].pos.z-radius <= tz) {
                        dx = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.x;
                        dz = lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z-lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j+1]].mdlNo[0]].pos.z;
                        nz = dx*dx+dz*dz;
                        nx = -1.0f*((dx*(lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x-lbl_1_bss_2614[i].pos.x))+(dz*(lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z-lbl_1_bss_2614[i].pos.z)));
                        if(nz) {
                            t = nx/nz;
                        } else {
                            t = 0.0f;
                        }
                        tx = (dx*t)+lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.x;
                        tz = (dz*t)+lbl_1_bss_3730->models[lbl_1_bss_36A4[lbl_1_bss_2F0.list[j]].mdlNo[0]].pos.z;
                        dx = lbl_1_bss_2614[i].pos.x-tx;
                        dz = lbl_1_bss_2614[i].pos.z-tz;
                        dist = sqrt(dx*dx+dz*dz);
                        if(dist < radius+pushOfs) {
                            lbl_1_bss_2614[i].hitType = 2;
                        }
                    }
                }
            }
            dx = lbl_1_bss_2614[i].pos.x;
            dz = lbl_1_bss_2614[i].pos.z;
            sign = -1.0f;
            if((-dx)+dz > -784.0f && dx < 554.0f && dx+dz < 784.0f && dz < 554.0f && (-dx)+dz < 784.0f && dx > -554.0f && dx+dz > -784.0f && dz > -554.0f) {
                sign = 1.0f;
            }
            for(j=0; j<8; j++) {
                dx = lbl_1_data_368[j][0]-lbl_1_data_368[j][2];
                dz = lbl_1_data_368[j][1]-lbl_1_data_368[j][3];
                nz = dx*dx+dz*dz;
                nx = -1.0f*((dx*(lbl_1_data_368[j][0]-lbl_1_bss_2614[i].pos.x))+(dz*(lbl_1_data_368[j][1]-lbl_1_bss_2614[i].pos.z)));
                if(nz) {
                    t = nx/nz;
                } else {
                    t = 0.0f;
                }
                tx = (dx*t)+lbl_1_data_368[j][0];
                tz = (dz*t)+lbl_1_data_368[j][1];
                dx = lbl_1_bss_2614[i].pos.x-tx;
                dz = lbl_1_bss_2614[i].pos.z-tz;
                dist = sqrt(dx*dx+dz*dz);
                if(dist < radius) {
                    if(dist <= 1.0f) {
                        dist = 1.0f;
                    }
                    scale = (20.0f+radius)/dist;
                    dx = sign*(dx*scale);
                    dz = sign*(dz*scale);
                    lbl_1_bss_2614[i].pos.x = tx+dx;
                    lbl_1_bss_2614[i].pos.z = tz+dz;
                    lbl_1_bss_2614[i].hitType = 2;
                }
            }
        }
    }
    if(lbl_1_bss_2734.winner == 0 && lbl_1_bss_2614[0].hitType == 2 && lbl_1_bss_2614[1].hitType == 2) {
        i = frandmod(2);
        lbl_1_bss_2614[i].hitType = 2;
        lbl_1_bss_2614[i^1].hitType = 0;
    }
}

/* 283 insns. A computer duellist's settings by difficulty, and the eight walls as path row 15. */
void fn_1_11710(s16 player)
{
    float speedTbl[4] = { 7.2f, 8.0f, 9.0f, 10.285714f };
    s16 hurryTbl[4][2] = { { 120, 60 }, { 540, 180 }, { 1500, 300 }, { 3600, 60 } };
    s16 stepTbl[4][2] = { { 7, 7 }, { 6, 6 }, { 2, 2 }, { 1, 1 } };
    s16 i;
    s16 rand;

    if(lbl_1_bss_3730->chr[player].dif != 0) {
        lbl_1_bss_2614[player].comF = 1;
        lbl_1_bss_2614[player].comDif = lbl_1_bss_3730->chr[player].dif-1;
        lbl_1_bss_2614[player].turnRateBase = speedTbl[lbl_1_bss_2614[player].comDif];
        lbl_1_bss_2614[player].chaseRadius = 11.0f;
        rand = hurryTbl[lbl_1_bss_2614[player].comDif][0]+frandmod(hurryTbl[lbl_1_bss_2614[player].comDif][1]);
        lbl_1_bss_2614[player].thinkSlowStep = rand;
        lbl_1_bss_2614[player].thinkTime = 10;
        rand = stepTbl[lbl_1_bss_2614[player].comDif][1]+frandmod(stepTbl[lbl_1_bss_2614[player].comDif][1]);
        lbl_1_bss_2614[player].thinkTimeAdd = rand;
    }
    for(i=0, lbl_1_bss_45C.idxNum[15]=0; i<8; i++) {
        lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].x = lbl_1_data_368[i][0];
        lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].y = 0.0f;
        lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].z = lbl_1_data_368[i][1];
        lbl_1_bss_45C.idx[15][i] = i;
        lbl_1_bss_45C.idxNum[15]++;
    }
    lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].x = lbl_1_data_368[0][0];
    lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].y = 0.0f;
    lbl_1_bss_45C.vtx[15][lbl_1_bss_45C.idxNum[15]].z = lbl_1_data_368[0][1];
    lbl_1_bss_45C.idx[15][i] = i;
    lbl_1_bss_45C.idxNum[15]++;
}

/* 31 insns. Platform path prediction: seed 29 steps once, then advance one step a frame. */
void fn_1_11B7C(void)
{
    switch(lbl_1_bss_45C.predMode) {
        case 0:
            fn_1_12008(29);
            lbl_1_bss_45C.predMode++;

        case 1:
            lbl_1_bss_45C.step++;
            fn_1_12830();
            break;
    }
}

/* 124 insns. A computer duellist's frame: think every thinkTime frames, then chase. */
s16 fn_1_11BF8(s16 player)
{
    s16 result;

    result = 0;
    lbl_1_bss_2614[player].stkX = 0;
    lbl_1_bss_2614[player].stkY = 0;
    lbl_1_bss_2614[player].btnDown = 0;
    lbl_1_bss_2614[player].btn = 0;
    switch(lbl_1_bss_2614[player].comMode) {
        case 0:
            lbl_1_bss_2614[player].comMode++;
            lbl_1_bss_2614[player].thinkTimer = player*5;

        case 1:
            if(lbl_1_bss_2614[player].thinkTimer++ >= lbl_1_bss_2614[player].thinkTime) {
                fn_1_14EB0(player);
                lbl_1_bss_2614[player].thinkTimer = 0;
                if(lbl_1_bss_45C.step > lbl_1_bss_2614[player].thinkSlowStep) {
                    lbl_1_bss_2614[player].thinkTime += lbl_1_bss_2614[player].thinkTimeAdd;
                }
            }
            fn_1_11DE8(player);
            break;
    }
    return result;
}

/* 136 insns. A computer duellist walks to its chase target. */
s16 fn_1_11DE8(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_2614[player].chaseMode) {
        case 0:
            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_2614[player].chaseMode++;
            break;

        case 1:
            if((s32)lbl_1_bss_2614[player].vel.x > 700 || (s32)lbl_1_bss_2614[player].vel.x < -700 || (s32)lbl_1_bss_2614[player].vel.z > 700 || (s32)lbl_1_bss_2614[player].vel.z < -700) {
                return 0;
            }
            doneF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_2614[player].vel, lbl_1_bss_2614[player].turnRate, lbl_1_bss_2614[player].chaseRadius);
            break;

        case 2:
            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
            lbl_1_bss_2614[player].chaseMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* 522 insns. Seed the platform path rings with num simulated steps. */
s16 fn_1_12008(s16 num)
{
    s16 result;
    s16 i;
    s16 j;

    result = 0;
    for(i=0, lbl_1_bss_45C.num=0; i<15; i++) {
        if(lbl_1_bss_20[i].activeF) {
            lbl_1_bss_45C.pos[i] = lbl_1_bss_3730->models[lbl_1_bss_36A4[i].mdlNo[0]].pos;
            lbl_1_bss_45C.vel[i] = lbl_1_bss_20[i].vel;
            lbl_1_bss_45C.angle[i] = lbl_1_bss_20[i].angle;
            lbl_1_bss_45C.num++;
        }
        lbl_1_bss_45C.idxNum[i] = 0;
    }
    lbl_1_bss_45C.speed = lbl_1_bss_2F0.speed;
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        lbl_1_bss_45C.vtx[i][0] = lbl_1_bss_45C.pos[i];
        lbl_1_bss_45C.idx[i][lbl_1_bss_45C.idxNum[i]] = 0;
        lbl_1_bss_45C.idxNum[i]++;
    }
    for(i=0; i<num; i++) {
        fn_1_194B4();
        fn_1_187F8();
        for(j=0; j<lbl_1_bss_45C.num; j++) {
            lbl_1_bss_45C.hitF[j] = 0;
        }
        fn_1_12F40();
        for(j=0; j<lbl_1_bss_45C.num; j++) {
            if(lbl_1_bss_45C.speed <= 10.0f) {
                lbl_1_bss_45C.vel[j].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[j]/180.0);
                lbl_1_bss_45C.vel[j].y = 0.0f;
                lbl_1_bss_45C.vel[j].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[j]/180.0);
            }
            if(lbl_1_bss_45C.stopF[j]) {
                lbl_1_bss_45C.vel[j].x = 0.0f;
                lbl_1_bss_45C.vel[j].y = 0.0f;
                lbl_1_bss_45C.vel[j].z = 0.0f;
            }
            lbl_1_bss_45C.pos[j].x += lbl_1_bss_45C.vel[j].x;
            lbl_1_bss_45C.pos[j].y += lbl_1_bss_45C.vel[j].y;
            lbl_1_bss_45C.pos[j].z += lbl_1_bss_45C.vel[j].z;
            lbl_1_bss_45C.vtx[j][i] = lbl_1_bss_45C.pos[j];
            if(lbl_1_bss_45C.hitF[j] && i) {
                lbl_1_bss_45C.idx[j][lbl_1_bss_45C.idxNum[j]] = i;
                lbl_1_bss_45C.idxNum[j]++;
            }
        }
        if((lbl_1_bss_45C.speed += 0.002f) > 10.0f) {
            lbl_1_bss_45C.speed = 10.0f;
        }
    }
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        if(lbl_1_bss_45C.hitF[i]) {
            lbl_1_bss_45C.lastHitF[i] = 1;
        } else {
            lbl_1_bss_45C.idx[i][lbl_1_bss_45C.idxNum[i]] = num-1;
            lbl_1_bss_45C.idxNum[i]++;
            lbl_1_bss_45C.lastHitF[i] = 0;
        }
    }
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        lbl_1_bss_45C.head[i] = num;
        if(lbl_1_bss_45C.head[i] >= 30) {
            lbl_1_bss_45C.head[i] = 0;
        }
        lbl_1_bss_45C.tail[i] = lbl_1_bss_45C.head[i]+1;
        if(lbl_1_bss_45C.tail[i] >= 30) {
            lbl_1_bss_45C.tail[i] = 0;
        }
    }
    return result;
}

/* 452 insns. Advance the platform path rings by one step. */
s16 fn_1_12830(void)
{
    s16 result;
    s16 i;
    s16 j;

    result = 0;
    fn_1_194B4();
    fn_1_187F8();
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        lbl_1_bss_45C.hitF[i] = 0;
    }
    fn_1_12F40();
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        if(lbl_1_bss_45C.speed <= 10.0f) {
            lbl_1_bss_45C.vel[i].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[i]/180.0);
            lbl_1_bss_45C.vel[i].y = 0.0f;
            lbl_1_bss_45C.vel[i].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[i]/180.0);
        }
        if(lbl_1_bss_45C.stopF[i]) {
            lbl_1_bss_45C.vel[i].x = 0.0f;
            lbl_1_bss_45C.vel[i].y = 0.0f;
            lbl_1_bss_45C.vel[i].z = 0.0f;
        }
        lbl_1_bss_45C.pos[i].x += lbl_1_bss_45C.vel[i].x;
        lbl_1_bss_45C.pos[i].y += lbl_1_bss_45C.vel[i].y;
        lbl_1_bss_45C.pos[i].z += lbl_1_bss_45C.vel[i].z;
        lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.head[i]] = lbl_1_bss_45C.pos[i];
        if(lbl_1_bss_45C.hitF[i]) {
            if(lbl_1_bss_45C.lastHitF[i]) {
                lbl_1_bss_45C.idxNum[i]++;
            }
            lbl_1_bss_45C.idx[i][lbl_1_bss_45C.idxNum[i]-1] = lbl_1_bss_45C.head[i];
            lbl_1_bss_45C.lastHitF[i] = 1;
        } else {
            if(lbl_1_bss_45C.lastHitF[i]) {
                lbl_1_bss_45C.idxNum[i]++;
            }
            lbl_1_bss_45C.idx[i][lbl_1_bss_45C.idxNum[i]-1] = lbl_1_bss_45C.head[i];
            lbl_1_bss_45C.lastHitF[i] = 0;
        }
    }
    if((lbl_1_bss_45C.speed += 0.002f) > 10.0f) {
        lbl_1_bss_45C.speed = 10.0f;
    }
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        lbl_1_bss_45C.idx[i][0] = lbl_1_bss_45C.tail[i];
        if(lbl_1_bss_45C.idx[i][0] == lbl_1_bss_45C.idx[i][1]) {
            for(j=1; j<lbl_1_bss_45C.idxNum[i]; j++) {
                lbl_1_bss_45C.idx[i][j-1] = lbl_1_bss_45C.idx[i][j];
            }
            lbl_1_bss_45C.idxNum[i]--;
        }
        if(++lbl_1_bss_45C.head[i] >= 30) {
            lbl_1_bss_45C.head[i] = 0;
        }
        lbl_1_bss_45C.tail[i] = lbl_1_bss_45C.head[i]+1;
        if(lbl_1_bss_45C.tail[i] >= 30) {
            lbl_1_bss_45C.tail[i] = 0;
        }
    }
    return result;
}

/*
 * 1525 insns. The platforms against each other and the walls: push a pair
 * apart and swap their velocities along the line between them, and reflect a
 * platform off any of the eight walls it reaches.
 */
void fn_1_12F40(void)
{
    s16 i;
    s16 j;
    float dx;
    float dz;
    float nz;
    float dist;
    float len2;
    float nx;
    float spdI2;
    float spdJ2;
    float wallX;
    float t;
    float tangJ;
    float scale;
    float radius = 30.0f;
    float margin = 30.000002f;
    float angleTbl[8] = { 90.0f, 180.0f, -90.0f, 0.0f, 90.0f, -180.0f, -90.0f, 0.0f };

    for(i=0; i<lbl_1_bss_45C.num; i++) {
        if(lbl_1_bss_45C.stopF[i] == 0) {
            for(j=0; j<lbl_1_bss_45C.num; j++) {
                if(i != j) {
                    dx = lbl_1_bss_45C.pos[j].x-lbl_1_bss_45C.pos[i].x;
                    dz = lbl_1_bss_45C.pos[j].z-lbl_1_bss_45C.pos[i].z;
                    dist = sqrt(dx*dx+dz*dz);
                    if(dist < radius+margin) {
                        if(dist <= 1.0f) {
                            dist = 1.0f;
                        }
                        scale = (10.0f+(radius+margin))/dist;
                        dx *= scale;
                        dz *= scale;
                        lbl_1_bss_45C.pos[i].x = lbl_1_bss_45C.pos[j].x-dx;
                        lbl_1_bss_45C.pos[i].z = lbl_1_bss_45C.pos[j].z-dz;
                        len2 = ((lbl_1_bss_45C.pos[j].x-lbl_1_bss_45C.pos[i].x)*(lbl_1_bss_45C.pos[j].x-lbl_1_bss_45C.pos[i].x))+((lbl_1_bss_45C.pos[j].z-lbl_1_bss_45C.pos[i].z)*(lbl_1_bss_45C.pos[j].z-lbl_1_bss_45C.pos[i].z));
                        dist = sqrt(len2);
                        if(dist <= 1.0f) {
                            dist = 1.0f;
                        }
                        nz = nx = 0.0f;
                        nz = (lbl_1_bss_45C.pos[j].z-lbl_1_bss_45C.pos[i].z)/dist;
                        nx = (lbl_1_bss_45C.pos[j].x-lbl_1_bss_45C.pos[i].x)/dist;
                        if(nz == 0.0f && nx == 0.0f) {
                            nz = 1.0f;
                            nx = 0.0f;
                        }
                        dx = (lbl_1_bss_45C.vel[j].x*nx)+(lbl_1_bss_45C.vel[j].z*nz);
                        dz = (-lbl_1_bss_45C.vel[i].x*nz)+(lbl_1_bss_45C.vel[i].z*nx);
                        wallX = (lbl_1_bss_45C.vel[i].x*nx)+(lbl_1_bss_45C.vel[i].z*nz);
                        tangJ = (-lbl_1_bss_45C.vel[j].x*nz)+(lbl_1_bss_45C.vel[j].z*nx);
                        lbl_1_bss_45C.vel[i].x = (dx*nx)-(dz*nz);
                        lbl_1_bss_45C.vel[i].z = (dz*nx)+(dx*nz);
                        lbl_1_bss_45C.vel[j].x = (wallX*nx)-(tangJ*nz);
                        lbl_1_bss_45C.vel[j].z = (tangJ*nx)+(wallX*nz);
                        spdI2 = (lbl_1_bss_45C.vel[i].x*lbl_1_bss_45C.vel[i].x)+(lbl_1_bss_45C.vel[i].z*lbl_1_bss_45C.vel[i].z);
                        dx = sqrt(spdI2);
                        spdJ2 = (lbl_1_bss_45C.vel[j].x*lbl_1_bss_45C.vel[j].x)+(lbl_1_bss_45C.vel[j].z*lbl_1_bss_45C.vel[j].z);
                        dz = sqrt(spdJ2);
                        if(dx) {
                            dx = lbl_1_bss_45C.speed/dx;
                        } else {
                            dx = 0.0f;
                        }
                        if(dz) {
                            dz = lbl_1_bss_45C.speed/dz;
                        } else {
                            dz = 0.0f;
                        }
                        lbl_1_bss_45C.vel[i].x *= dx;
                        lbl_1_bss_45C.vel[i].z *= dx;
                        lbl_1_bss_45C.vel[j].x *= dz;
                        lbl_1_bss_45C.vel[j].z *= dz;
                        dx = 180.0*(acos(lbl_1_bss_45C.vel[i].x/(0.1f+lbl_1_bss_45C.speed))/M_PI);
                        dz = 180.0*(asin(lbl_1_bss_45C.vel[i].z/(0.1f+lbl_1_bss_45C.speed))/M_PI);
                        if(dz < 0.0f) {
                            dx = 360.0f-dx;
                        }
                        lbl_1_bss_45C.angle[i] = dx;
                        lbl_1_bss_45C.vel[i].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[i]/180.0);
                        lbl_1_bss_45C.vel[i].y = 0.0f;
                        lbl_1_bss_45C.vel[i].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[i]/180.0);
                        if(lbl_1_bss_45C.stopF[j] == 0) {
                            dx = 180.0*(acos(lbl_1_bss_45C.vel[j].x/(0.1f+lbl_1_bss_45C.speed))/M_PI);
                            dz = 180.0*(asin(lbl_1_bss_45C.vel[j].z/(0.1f+lbl_1_bss_45C.speed))/M_PI);
                            if(dz < 0.0f) {
                                dx = 360.0f-dx;
                            }
                            lbl_1_bss_45C.angle[j] = dx;
                            lbl_1_bss_45C.vel[j].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[j]/180.0);
                            lbl_1_bss_45C.vel[j].y = 0.0f;
                            lbl_1_bss_45C.vel[j].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[j]/180.0);
                            lbl_1_bss_45C.hitF[j] = 1;
                        }
                        lbl_1_bss_45C.hitF[i] = 1;
                    }
                }
            }
            dx = lbl_1_bss_45C.pos[i].x;
            dz = lbl_1_bss_45C.pos[i].z;
            for(j=0; j<8; j++) {
                dx = lbl_1_data_368[j][0]-lbl_1_data_368[j][2];
                dz = lbl_1_data_368[j][1]-lbl_1_data_368[j][3];
                nz = dx*dx+dz*dz;
                nx = -1.0f*((dx*(lbl_1_data_368[j][0]-lbl_1_bss_45C.pos[i].x))+(dz*(lbl_1_data_368[j][1]-lbl_1_bss_45C.pos[i].z)));
                if(nz) {
                    t = nx/nz;
                } else {
                    t = 0.0f;
                }
                wallX = (dx*t)+lbl_1_data_368[j][0];
                tangJ = (dz*t)+lbl_1_data_368[j][1];
                dx = lbl_1_bss_45C.pos[i].x-wallX;
                dz = lbl_1_bss_45C.pos[i].z-tangJ;
                dist = sqrt(dx*dx+dz*dz);
                if(dist < margin) {
                    if(dist <= 1.0f) {
                        dist = 1.0f;
                    }
                    scale = margin/dist;
                    dx *= scale;
                    dz *= scale;
                    lbl_1_bss_45C.pos[i].x = wallX+dx;
                    lbl_1_bss_45C.pos[i].z = tangJ+dz;
                    lbl_1_bss_45C.angle[i] = 360.0f-lbl_1_bss_45C.angle[i];
                    lbl_1_bss_45C.angle[i] += angleTbl[j];
                    if(lbl_1_bss_45C.angle[i] >= 360.0f) {
                        lbl_1_bss_45C.angle[i] -= 360.0f;
                    }
                    lbl_1_bss_45C.vel[i].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[i]/180.0);
                    lbl_1_bss_45C.vel[i].y = 0.0f;
                    lbl_1_bss_45C.vel[i].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[i]/180.0);
                    lbl_1_bss_45C.hitF[i] = 1;
                }
            }
        }
    }
}

/* 487 insns. Whether duellist `player` is touching any platform's trail. */
s16 fn_1_14714(s16 player)
{
    float radius;
    s16 result;
    s16 i;
    s16 j;
    float minX;
    float maxX;
    float minZ;
    float maxZ;
    float dx;
    float dz;
    float len2;
    float t;
    float num;
    float dist;
    float margin;

    radius = 30.0f;
    margin = 30.000002f;
    result = 0;
    for(i=0; i<lbl_1_bss_45C.num; i++) {
        for(j=0; j<lbl_1_bss_45C.idxNum[i]-1; j++) {
            if(lbl_1_bss_45C.vtx[i][j].x < lbl_1_bss_45C.vtx[i][j+1].x) {
                minX = lbl_1_bss_45C.vtx[i][j].x;
                maxX = lbl_1_bss_45C.vtx[i][j+1].x;
            } else {
                minX = lbl_1_bss_45C.vtx[i][j+1].x;
                maxX = lbl_1_bss_45C.vtx[i][j].x;
            }
            if(lbl_1_bss_45C.vtx[i][j].z < lbl_1_bss_45C.vtx[i][j+1].z) {
                minZ = lbl_1_bss_45C.vtx[i][j].z;
                maxZ = lbl_1_bss_45C.vtx[i][j+1].z;
            } else {
                minZ = lbl_1_bss_45C.vtx[i][j+1].z;
                maxZ = lbl_1_bss_45C.vtx[i][j].z;
            }
            if(radius+lbl_1_bss_2614[player].pos.x >= minX && lbl_1_bss_2614[player].pos.x-radius <= maxX && radius+lbl_1_bss_2614[player].pos.z >= minZ && lbl_1_bss_2614[player].pos.z-radius <= maxZ) {
                dx = lbl_1_bss_45C.vtx[i][j].x-lbl_1_bss_45C.vtx[i][j+1].x;
                dz = lbl_1_bss_45C.vtx[i][j].z-lbl_1_bss_45C.vtx[i][j+1].z;
                len2 = dx*dx+dz*dz;
                if(len2 == 0.0f) {
                    len2 = 1.0f;
                }
                num = -1.0f*((dx*(lbl_1_bss_45C.vtx[i][j].x-lbl_1_bss_2614[player].pos.x))+(dz*(lbl_1_bss_45C.vtx[i][j].z-lbl_1_bss_2614[player].pos.z)));
                t = num/len2;
                minX = lbl_1_bss_45C.vtx[i][j].x+(dx*t);
                minZ = lbl_1_bss_45C.vtx[i][j].z+(dz*t);
                dx = lbl_1_bss_2614[player].pos.x-minX;
                dz = lbl_1_bss_2614[player].pos.z-minZ;
                dist = sqrt(dx*dx+dz*dz);
                if(dist < radius+margin) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

/* 3666 insns. A computer duellist's escape: cast 36 rays from it, find where
   each meets the wall polylines (or the octagon while the beam is up), and
   head for one of the far hits. */
s16 fn_1_14EB0(s16 player)
{
    float step;
    float rayX;
    float rayZ;
    float cosA;
    float sinA;
    float c;
    float c2;
    float maxX;
    float maxZ;
    float backDist = 60.0f;
    float unused2C = 30.0f;
    float unused28 = 30.000002f;
    float radius = 90.0f;
    float off;
    float lenN;
    float len2;
    float len;
    float abs1;
    float abs2;
    float abs3;
    float dx;
    float dz;
    float px;
    float pz;
    float a;
    float b;
    float angle;
    float d;
    float a2;
    float b2;
    float fx;
    float fz;
    float x;
    float z;
    s16 i;
    s16 j;
    s16 k;
    s16 hitF;
    s16 cnt;
    s16 touchF;
    s16 touchNum;
    s16 result;
    s16 unused198[36];
    s16 list[36];
    s16 wallF[36];
    s16 pair[36][2];
    HuVecF hit[36];
    float dist[36][2];

    result = 0;
    touchNum = 0;
    for(i=0; i<36; i++) {
        dist[i][0] = 2000.0f;
        dist[i][1] = 2000.0f;
        unused198[i] = 0;
        wallF[i] = 0;
    }
    px = lbl_1_bss_2614[player].pos.x;
    pz = lbl_1_bss_2614[player].pos.z;
    for(angle=0.0f, k=0, step=10.0f; angle<360.0f; angle+=step, k++) {
        rayX = px+10.0*cos(M_PI*angle/180.0);
        rayZ = pz+10.0*sin(M_PI*angle/180.0);
        cosA = cos(M_PI*angle/180.0);
        sinA = sin(M_PI*angle/180.0);
        a = rayZ-pz;
        b = px-rayX;
        c = (-a*px)-(b*pz);
        lenN = sqrt(a*a+b*b);
        x = px-rayX;
        z = pz-rayZ;
        len2 = sqrt(x*x+z*z);
        for(i=0; i<17; i++) {
            off = 0.0f;
            if(i == lbl_1_bss_45C.num) {
                i = 15;
            } else if(i == 16) {
                if(lbl_1_bss_45C.routeF == 0 && lbl_1_bss_2F0.beamF == 0) {
                    break;
                }
                off = 1.0f;
            }
            for(j=0; j<lbl_1_bss_45C.idxNum[i]-1; j++) {
                hitF = 0;
                touchF = 0;
                if(i != 15) {
                x = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                z = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                fx = 0.0f;
                fz = 0.0f;
                dx = x-px;
                dz = z-pz;
                if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                    if(dx+radius > 0.0f) {
                        fx = 1.0f;
                    }
                } else if(90.0f == angle || 270.0f == angle) {
                    fx = 1.0f;
                } else if(dx-radius < 0.0f) {
                    fx = 1.0f;
                }
                if(angle > 0.0f && angle < 180.0f) {
                    if(dz+radius > 0.0f) {
                        fz = 1.0f;
                    }
                } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                    fz = 1.0f;
                } else if(dz-radius < 0.0f) {
                    fz = 1.0f;
                }
                d = sqrt(dx*dx+dz*dz);
                if(d <= radius) {
                    touchNum++;
                    touchF = 1;
                }
                if(fx && fz && d > radius) {
                    if(c+((a*x)+(b*z)) > 0.0f) {
                        abs1 = c+((a*x)+(b*z));
                    } else {
                        abs1 = -1.0f*(c+((a*x)+(b*z)));
                    }
                    d = abs1;
                    if(lenN) {
                        d = d/lenN;
                    } else {
                        d = 0.0f;
                    }
                    if(radius >= d) {
                        d = sqrt((x-px)*(x-px)+(z-pz)*(z-pz));
                        if(d < dist[k][0]) {
                            dist[k][0] = d;
                            if(len2) {
                                d = d/len2;
                            } else {
                                d = 0.0f;
                            }
                            hit[k].x = x;
                            hit[k].z = z;
                            pair[k][0] = i;
                            pair[k][1] = j;
                            hitF = 1;
                        }
                    }
                }
                x = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x;
                z = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                fx = 0.0f;
                fz = 0.0f;
                dx = x-px;
                dz = z-pz;
                if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                    if(dx+radius > 0.0f) {
                        fx = 1.0f;
                    }
                } else if(90.0f == angle || 270.0f == angle) {
                    fx = 1.0f;
                } else if(dx-radius < 0.0f) {
                    fx = 1.0f;
                }
                if(angle > 0.0f && angle < 180.0f) {
                    if(dz+radius > 0.0f) {
                        fz = 1.0f;
                    }
                } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                    fz = 1.0f;
                } else if(dz-radius < 0.0f) {
                    fz = 1.0f;
                }
                d = sqrt(dx*dx+dz*dz);
                if(d <= radius) {
                    touchNum++;
                    touchF = 1;
                }
                if(fx && fz && d > radius) {
                    if(c+((a*x)+(b*z)) > 0.0f) {
                        abs2 = c+((a*x)+(b*z));
                    } else {
                        abs2 = -1.0f*(c+((a*x)+(b*z)));
                    }
                    d = abs2;
                    if(lenN) {
                        d = d/lenN;
                    } else {
                        d = 0.0f;
                    }
                    if(radius >= d) {
                        d = sqrt((x-px)*(x-px)+(z-pz)*(z-pz));
                        if(d < dist[k][0]) {
                            dist[k][0] = d;
                            if(len2) {
                                d = d/len2;
                            } else {
                                d = 0.0f;
                            }
                            hit[k].x = x;
                            hit[k].z = z;
                            pair[k][0] = i;
                            pair[k][1] = j;
                            hitF++;
                        }
                    }
                }
                if(touchF) {
                    x = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x-lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                    z = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z-lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                    x *= 0.5f;
                    z *= 0.5f;
                    x += lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                    z += lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                    fx = 0.0f;
                    fz = 0.0f;
                    dx = x-px;
                    dz = z-pz;
                    if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                        if(dx+radius > 0.0f) {
                            fx = 1.0f;
                        }
                    } else if(90.0f == angle || 270.0f == angle) {
                        fx = 1.0f;
                    } else if(dx-radius < 0.0f) {
                        fx = 1.0f;
                    }
                    if(angle > 0.0f && angle < 180.0f) {
                        if(dz+radius > 0.0f) {
                            fz = 1.0f;
                        }
                    } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                        fz = 1.0f;
                    } else if(dz-radius < 0.0f) {
                        fz = 1.0f;
                    }
                    d = sqrt(dx*dx+dz*dz);
                    if(fx && fz && d > radius) {
                        if(c+((a*x)+(b*z)) > 0.0f) {
                            abs3 = c+((a*x)+(b*z));
                        } else {
                            abs3 = -1.0f*(c+((a*x)+(b*z)));
                        }
                        d = abs3;
                        if(lenN) {
                            d = d/lenN;
                        } else {
                            d = 0.0f;
                        }
                        dx = sqrt((x-px)*(x-px)+(z-pz)*(z-pz));
                        if(dx-0.5f >= d) {
                            d = dx;
                            if(d < dist[k][0]) {
                                dist[k][0] = d;
                                if(len2) {
                                    d = d/len2;
                                } else {
                                    d = 0.0f;
                                }
                                hit[k].x = x;
                                hit[k].z = z;
                                pair[k][0] = i;
                                pair[k][1] = j;
                            }
                        }
                    }
                }
                }
                if(hitF || touchF) {
                    wallF[i] = 1;
                }
                if(lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x < lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x) {
                    fx = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                    maxX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x;
                } else {
                    fx = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x;
                    maxX = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                }
                if(lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z < lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z) {
                    fz = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                    maxZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                } else {
                    fz = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                    maxZ = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                }
                if(i != 15) {
                    x = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].x;
                    z = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j]].z;
                    dx = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].x+off;
                    dz = lbl_1_bss_45C.vtx[i][lbl_1_bss_45C.idx[i][j+1]].z;
                    a2 = dz-z;
                    b2 = x-dx;
                    c2 = (-a2*x)-(b2*z);
                } else {
                    a2 = lbl_1_data_3E8[j][0];
                    b2 = lbl_1_data_3E8[j][1];
                    c2 = lbl_1_data_3E8[j][2];
                }
                len = sqrt(a*a+b*b)*sqrt(a2*a2+b2*b2);
                if(len) {
                    off = ((a*a2)+(b*b2))/len;
                } else {
                    off = 0.0f;
                }
                if(off < 0.984f && off > -0.984f) {
                    if(a && b && a2 && b2) {
                        dx = a2*(-b/a);
                        dz = -1.0f*(a2*(-c/a));
                        dx = dx+b2;
                        dz = dz-c2;
                        if(dx) {
                            z = dz/dx;
                        } else {
                            z = 0.0f;
                        }
                        x = ((-b2*z)-c2)/a2;
                    } else if(!a && b && a2 && b2) {
                        z = -c/b;
                        x = ((-b2*z)-c2)/a2;
                    } else if(a && !b && a2 && b2) {
                        x = -c/a;
                        x = x; /* no code; evens x's register weight with z so x takes f31 */
                        z = ((-a2*x)-c2)/b2;
                    } else if(a && b && !a2 && b2) {
                        z = -c2/b2;
                        x = ((-b*z)-c)/a;
                    } else if(a && b && a2 && !b2) {
                        x = -c2/a2;
                        z = ((-a*x)-c)/b;
                    } else if(!a && b && a2 && !b2) {
                        z = -c/b;
                        x = -c2/a2;
                    } else if(a && !b && !a2 && b2) {
                        x = -c/a;
                        z = -c2/b2;
                    }
                    if(x >= fx && x <= maxX && z >= fz && z <= maxZ) {
                        dx = x-px;
                        dz = z-pz;
                        fx = 0.0f;
                        fz = 0.0f;
                        if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                            if(dx > 0.0f) {
                                fx = 1.0f;
                            }
                        } else if(90.0f == angle || 270.0f == angle) {
                            fx = 1.0f;
                        } else if(dx < 0.0f) {
                            fx = 1.0f;
                        }
                        if(angle > 0.0f && angle < 180.0f) {
                            if(dz > 0.0f) {
                                fz = 1.0f;
                            }
                        } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                            fz = 1.0f;
                        } else if(dz < 0.0f) {
                            fz = 1.0f;
                        }
                        if(fx && fz) {
                            dx = sqrt(dx*dx+dz*dz);
                            if(dx < dist[k][0]) {
                                dist[k][0] = dx;
                                hit[k].x = x;
                                hit[k].z = z;
                                pair[k][0] = i;
                                pair[k][1] = j;
                            }
                        }
                    }
                }
            }
        }
    }
    i = 0;
    j = 0;
    hitF = 0;
    cnt = 0;
    fx = dist[0][0];
    maxX = dist[0][0];
    for(; i<k; i++) {
        if((s32)hit[i].x < 700 && (s32)hit[i].x > -700 && (s32)hit[i].z < 700 && (s32)hit[i].z > -700 && 2000.0f != dist[i][0]) {
            if(fx <= dist[i][0]) {
                fx = dist[i][0];
                j = i;
            }
            if(maxX >= dist[i][0]) {
                maxX = dist[i][0];
            }
            if(dist[i][0] >= 600.0f) {
                list[cnt] = i;
                cnt++;
            }
        } else {
            dist[i][0] = -1.0f;
            hitF++;
            return 0;
        }
    }
    if(cnt) {
        i = frandmod(cnt);
        j = list[i];
    }
    if(dist[lbl_1_bss_2614[player].escapeNo][0] >= 350.0f) {
        j = lbl_1_bss_2614[player].escapeNo;
    }
    lbl_1_bss_2614[player].escapeNo = j;
    lbl_1_bss_2614[player].escapePos.x = hit[j].x;
    lbl_1_bss_2614[player].escapePos.z = hit[j].z;
    lbl_1_bss_2614[player].escapeDist = fx;
    lbl_1_bss_2614[player].escapeWallNo = pair[j][0];
    px -= lbl_1_bss_2614[player].escapePos.x;
    pz -= lbl_1_bss_2614[player].escapePos.z;
    if(lbl_1_bss_2614[player].escapeDist) {
        rayX = backDist/lbl_1_bss_2614[player].escapeDist;
    } else {
        rayX = 0.0f;
    }
    px *= rayX;
    pz *= rayX;
    if((s32)(px+lbl_1_bss_2614[player].escapePos.x) > 700 || (s32)(px+lbl_1_bss_2614[player].escapePos.x) < -700 || (s32)(pz+lbl_1_bss_2614[player].escapePos.z) > 700 || (s32)(pz+lbl_1_bss_2614[player].escapePos.z) < -700) {
        return 0;
    }
    lbl_1_bss_2614[player].vel.x = px+lbl_1_bss_2614[player].escapePos.x;
    lbl_1_bss_2614[player].vel.y = 200.0f;
    lbl_1_bss_2614[player].vel.z = pz+lbl_1_bss_2614[player].escapePos.z;
    if(maxX >= 300.0f) {
        lbl_1_bss_2614[player].turnRate = 0.01f;
    } else {
        lbl_1_bss_2614[player].turnRate = lbl_1_bss_2614[player].turnRateBase;
    }
    return result;
}

/*
 * 815 insns. A computer route: after the recorded wait, chain platforms whose
 * spacing fits this step's band, hold them still while the route line shows,
 * then release them.
 */
s16 fn_1_187F8(void)
{
    s16 result = 0;
    float bandTbl[11][2] = {
        { 0.0f, 0.0f },
        { 400.0f, 650.0f },
        { 350.0f, 600.0f },
        { 300.0f, 550.0f },
        { 250.0f, 500.0f },
        { 200.0f, 450.0f },
        { 150.0f, 400.0f },
        { 100.0f, 350.0f },
        { 50.0f, 300.0f },
        { 0.0f, 250.0f },
        { 0.0f, 200.0f }
    };
    s16 first;
    s16 i;
    s16 n;
    s16 k;
    s16 foundF;
    float dx;
    float dz;
    float dist;

    switch(lbl_1_bss_45C.routeMode) {
        case 0:
            lbl_1_bss_45C.routeTimer = lbl_1_bss_45C.recTimer[lbl_1_bss_45C.routeLen];
            lbl_1_bss_45C.routeLen++;
            lbl_1_bss_45C.routeMode++;
            break;

        case 1:
            if(lbl_1_bss_45C.routeTimer-- < 0) {
                lbl_1_bss_45C.routeTimer = 0;
                lbl_1_bss_45C.routeMode++;
            }
            lbl_1_bss_45C.waitCnt++;
            break;

        case 2:
            lbl_1_bss_45C.routeCnt++;
            for(i=0; i<10; i++) {
                lbl_1_bss_45C.route[i] = -1;
            }
            first = lbl_1_bss_45C.recPick[lbl_1_bss_45C.routeLen];
            lbl_1_bss_45C.route[0] = first+15;
            for(n=1; n<=lbl_1_bss_45C.routeLen; n++) {
                for(i=0; i<lbl_1_bss_45C.num; i++) {
                    for(k=0, foundF=0; k<10; k++) {
                        if(lbl_1_bss_45C.route[k] == i) {
                            foundF = 1;
                        }
                    }
                    if(foundF == 0) {
                        dx = lbl_1_bss_45C.pos[i].x-lbl_1_bss_45C.pos[lbl_1_bss_45C.route[n-1]].x;
                        dz = lbl_1_bss_45C.pos[i].z-lbl_1_bss_45C.pos[lbl_1_bss_45C.route[n-1]].z;
                        dist = sqrt(dx*dx+dz*dz);
                        if(bandTbl[lbl_1_bss_45C.routeLen][0] < dist && bandTbl[lbl_1_bss_45C.routeLen][1] > dist) {
                            lbl_1_bss_45C.route[n] = i;
                            break;
                        }
                    }
                }
                if(lbl_1_bss_45C.route[n] == -1) {
                    foundF = 1;
                    break;
                }
            }
            if(foundF == 0) {
                for(i=15; i<23; i++) {
                    if(lbl_1_bss_45C.route[0] != i) {
                        dx = lbl_1_bss_45C.pos[i].x-lbl_1_bss_45C.pos[lbl_1_bss_45C.route[lbl_1_bss_45C.routeLen]].x;
                        dz = lbl_1_bss_45C.pos[i].z-lbl_1_bss_45C.pos[lbl_1_bss_45C.route[lbl_1_bss_45C.routeLen]].z;
                        dist = sqrt(dx*dx+dz*dz);
                        if(bandTbl[lbl_1_bss_45C.routeLen][0] < dist && bandTbl[lbl_1_bss_45C.routeLen][1] > dist) {
                            lbl_1_bss_45C.route[lbl_1_bss_45C.routeLen+1] = i;
                            break;
                        }
                    }
                }
                for(i=0; i<=lbl_1_bss_45C.routeLen+1; i++) {
                    if(lbl_1_bss_45C.route[i] == -1) {
                        i = 99;
                        for(n=0; n<10; n++) {
                            lbl_1_bss_45C.route[n] = -1;
                        }
                    }
                }
                if(lbl_1_bss_45C.route[0] != -1) {
                    lbl_1_bss_45C.routeMode++;
                }
            }
            break;

        case 3:
            for(i=1; i<lbl_1_bss_45C.routeLen+1; i++) {
                lbl_1_bss_45C.stopF[lbl_1_bss_45C.route[i]] = 1;
                lbl_1_bss_45C.velSave[lbl_1_bss_45C.route[i]] = lbl_1_bss_45C.vel[lbl_1_bss_45C.route[i]];
                lbl_1_bss_45C.vel[lbl_1_bss_45C.route[i]].x = 0.0f;
                lbl_1_bss_45C.vel[lbl_1_bss_45C.route[i]].y = 0.0f;
                lbl_1_bss_45C.vel[lbl_1_bss_45C.route[i]].z = 0.0f;
            }
            lbl_1_bss_45C.routeTimer = 60;
            lbl_1_bss_45C.routeMode++;
            break;

        case 4:
            if(lbl_1_bss_45C.routeTimer-- < 0) {
                for(i=0; i<=lbl_1_bss_45C.routeLen+1; i++) {
                    lbl_1_bss_45C.vtx[16][i] = lbl_1_bss_45C.pos[lbl_1_bss_45C.route[i]];
                    lbl_1_bss_45C.idx[16][i] = i;
                }
                lbl_1_bss_45C.idxNum[16] = lbl_1_bss_45C.routeLen+2;
                lbl_1_bss_45C.routeF = 1;
                lbl_1_bss_45C.routeTimer = 120;
                lbl_1_bss_45C.routeMode++;
            }
            break;

        case 5:
            if(lbl_1_bss_45C.routeTimer-- < 0) {
                for(i=1; i<lbl_1_bss_45C.routeLen+1; i++) {
                    lbl_1_bss_45C.stopF[lbl_1_bss_45C.route[i]] = 0;
                    lbl_1_bss_45C.vel[lbl_1_bss_45C.route[i]] = lbl_1_bss_45C.velSave[lbl_1_bss_45C.route[i]];
                }
                lbl_1_bss_45C.routeF = 0;
                lbl_1_bss_45C.routeMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 161 insns. Every five seconds after the first ten, add a platform (up to fifteen). */
void fn_1_194B4(void)
{
    s16 doneF = 0;
    s16 i;

    switch(lbl_1_bss_45C.spawnMode) {
        case 0:
            if(lbl_1_bss_45C.spawnTimer >= 600 && lbl_1_bss_45C.spawnTimer%300 == 0 && lbl_1_bss_45C.num < 15) {
                lbl_1_bss_45C.spawnMode++;
            }
            break;

        case 1:
            doneF = fn_1_19738(lbl_1_bss_45C.num, 0.0f, 0.0f);
            if(doneF) {
                for(i=0; i<30; i++) {
                    lbl_1_bss_45C.vtx[lbl_1_bss_45C.num][i] = lbl_1_bss_45C.pos[lbl_1_bss_45C.num];
                }
                lbl_1_bss_45C.idx[lbl_1_bss_45C.num][0] = 0;
                lbl_1_bss_45C.idx[lbl_1_bss_45C.num][1] = 29;
                lbl_1_bss_45C.idxNum[lbl_1_bss_45C.num] = 2;
                lbl_1_bss_45C.lastHitF[lbl_1_bss_45C.num] = 0;
                lbl_1_bss_45C.head[lbl_1_bss_45C.num] = 29;
                lbl_1_bss_45C.tail[lbl_1_bss_45C.num] = 0;
                lbl_1_bss_45C.num++;
                lbl_1_bss_45C.spawnMode = 0;
            }
            break;
    }
    lbl_1_bss_45C.spawnTimer++;
}

/* 222 insns. Place platform `no` from its recorded heading and radius, then after 1.5 seconds set it moving. */
s16 fn_1_19738(s16 no, float x, float z)
{
    s16 result = 0;
    float angle;
    float radius;

    switch(lbl_1_bss_45C.placeMode[no]) {
        case 0:
            lbl_1_bss_45C.placeF[no] = 1;
            angle = lbl_1_bss_45C.recPlace[no].x;
            radius = lbl_1_bss_45C.recPlace[no].y;
            lbl_1_bss_45C.pos[no].x = x+radius*cos(M_PI*angle/180.0);
            lbl_1_bss_45C.pos[no].y = 0.0f;
            lbl_1_bss_45C.pos[no].z = z+radius*sin(M_PI*angle/180.0);
            lbl_1_bss_45C.placeTimer[no] = 0;
            lbl_1_bss_45C.placeMode[no]++;
            break;

        case 1:
            lbl_1_bss_45C.placeTimer[no]++;
            if(lbl_1_bss_45C.placeTimer[no] >= 90) {
                lbl_1_bss_45C.angle[no] = lbl_1_bss_45C.recPlace[no].z;
                lbl_1_bss_45C.vel[no].x = lbl_1_bss_45C.speed*cos(M_PI*lbl_1_bss_45C.angle[no]/180.0);
                lbl_1_bss_45C.vel[no].y = 0.0f;
                lbl_1_bss_45C.vel[no].z = lbl_1_bss_45C.speed*sin(M_PI*lbl_1_bss_45C.angle[no]/180.0);
                lbl_1_bss_45C.placeF[no] = 0;
                lbl_1_bss_45C.placeMode[no] = 1;
                result = 1;
            }
            break;
    }
    return result;
}

/* Twenty-five floats nothing reads. */
float lbl_1_data_48C[25] = {
    0.0f, 0.0f, 0.0f, 0.0f, 913.0f,
    0.0f, -1177.0f, 993.0f, 0.0f, -1038.0f,
    550.0f, 1000.0f, -3250.0f, 593.0f, 312.0f,
    -1119.0f, -462.0f, 330.0f, -1100.0f, -1000.0f,
    40.0f, -2100.0f, -2500.0f, 0.0f, -3900.0f
};
