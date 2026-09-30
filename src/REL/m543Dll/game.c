/*
 * m543dll/game.c -- the duel: a 45-panel floor the duellists race across while
 * rows of it drop away, the collision against panels, posts and walls, the
 * computer duellists' path search, and the sequence steps. Written from the
 * reference assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m543Dll/asm/REL/m543Dll/game.s.
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

#include "REL/m543Dll/m543.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_3CEC(M543_WORK *work);
s16 fn_1_69BC(s16 player);
s16 fn_1_6CF0(s16 player);
s16 fn_1_71AC(void);
s16 fn_1_7394(s16 no);
s16 fn_1_7704(s16 no);
s16 fn_1_7C18(void);
s32 fn_1_86E4(void);
s32 fn_1_91F8(void);
int fn_1_A308(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_A69C(MGACTOR *actor, int param);
void fn_1_A6B0(void);
void fn_1_D408(s16 player);
s16 fn_1_D9E8(s16 player);
s16 fn_1_E144(s16 player);
s16 fn_1_E340(s16 player);
s16 fn_1_EF58(s16 player);
void fn_1_6534(void);
void fn_1_6770(void);

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s32 lbl_1_bss_15E4;                 /* unreferenced; dtk sizes lbl_1_bss_15E0 8 */
M543_WORK *lbl_1_bss_15E0;          /* set by fn_1_3CEC */

/* --- .data --- */

/* The sixteen walls round the floor: two ends, then the direction they push along. */
typedef struct M543Wall_s {
    /* 0x00 */ float ax;
    /* 0x04 */ float az;
    /* 0x08 */ float bx;
    /* 0x0C */ float bz;
    /* 0x10 */ float nx;
    /* 0x14 */ float nz;
} M543_WALL;                        /* 0x18 */

M543_WALL lbl_1_data_380[16] = {
    { 230.0f, -554.0f, 554.0f, -230.0f, 1.0f, 1.0f },
    { 554.0f, -230.0f, 554.0f, -150.0f, 1.0f, 0.0f },
    { 554.0f, -150.0f, 754.0f, -150.0f, 0.0f, 1.0f },
    { 754.0f, -150.0f, 754.0f, 150.0f, 1.0f, 0.0f },
    { 754.0f, 150.0f, 554.0f, 150.0f, 0.0f, 1.0f },
    { 554.0f, 150.0f, 554.0f, 230.0f, 1.0f, 0.0f },
    { 554.0f, 230.0f, 230.0f, 554.0f, 1.0f, 1.0f },
    { 230.0f, 554.0f, -230.0f, 554.0f, 0.0f, 1.0f },
    { -230.0f, 554.0f, -554.0f, 230.0f, 1.0f, 1.0f },
    { -554.0f, 230.0f, -554.0f, 150.0f, 1.0f, 0.0f },
    { -554.0f, 150.0f, -754.0f, 150.0f, 0.0f, 1.0f },
    { -754.0f, 150.0f, -754.0f, -150.0f, 1.0f, 0.0f },
    { -754.0f, -150.0f, -554.0f, -150.0f, 0.0f, 1.0f },
    { -554.0f, -150.0f, -554.0f, -230.0f, 1.0f, 0.0f },
    { -554.0f, -230.0f, -230.0f, -554.0f, 1.0f, 1.0f },
    { -230.0f, -554.0f, 230.0f, -554.0f, 0.0f, 1.0f }
};

/* The goal posts (0-3) and the wall corners. [0][0] is the finish line's x. */
float lbl_1_data_500[12][2] = {
    { 554.0f, -150.0f },
    { 554.0f, 150.0f },
    { -554.0f, 150.0f },
    { -554.0f, -150.0f },
    { 230.0f, -554.0f },
    { 554.0f, -230.0f },
    { 554.0f, 230.0f },
    { 230.0f, 554.0f },
    { -230.0f, 554.0f },
    { -554.0f, 230.0f },
    { -554.0f, -230.0f },
    { -230.0f, -554.0f }
};

/* Fifteen floor layouts: the panels (by model number) missing from the start, -1 ended. */
s16 lbl_1_data_560[15][21] = {
    { 16, 46, 21, 26, 48, 44, 29, 45, 34, 15, 47, 19, 39, 23, 28, 41, -1, 0, 0, 0, 0 },
    { 15, 19, 43, 25, 48, 31, 35, 16, 46, 21, 51, 52, 45, 24, 29, 45, -1, 0, 0, 0, 0 },
    { 17, 21, 51, 27, 52, 48, 44, 29, 33, 16, 20, 43, 39, 23, 28, 41, -1, 0, 0, 0, 0 },
    { 16, 20, 25, 48, 31, 49, 45, 33, 15, 17, 21, 40, 19, 24, 44, -1, 0, 0, 0, 0, 0 },
    { 15, 42, 46, 21, 26, 48, 30, 34, 51, 27, 32, 38, 18, 39, 31, 44, 29, -1, 0, 0, 0 },
    { 17, 21, 51, 27, 52, 31, 35, 15, 19, 39, 23, 40, 44, 48, 29, -1, 0, 0, 0, 0, 0 },
    { 16, 42, 19, 43, 25, 30, 45, 33, 39, 24, 46, 17, 50, 22, 27, 52, 31, 49, -1, 0, 0 },
    { 17, 21, 26, 48, 26, 44, 29, 33, 16, 20, 47, 51, 52, 43, 39, 23, 40, 31, -1, 0, 0 },
    { 15, 19, 39, 23, 40, 29, 45, 34, 43, 47, 26, 42, 46, 50, 48, 31, 49, -1, 0, 0, 0 },
    { 16, 46, 21, 26, 31, 49, 30, 44, 29, 33, 17, 51, 27, 15, 19, 39, 23, -1, 0, 0, 0 },
    { 16, 20, 43, 24, 40, 28, 41, 45, 34, 15, 25, 46, 47, 51, 27, 32, 38, 18, 23, -1, 0 },
    { 17, 50, 22, 27, 52, 31, 49, 30, 25, 43, 24, 29, 33, 15, 16, 51, 32, 39, 40, -1, 0 },
    { 15, 19, 24, 44, 48, 52, 32, 53, 35, 38, 18, 17, 50, 22, 51, 26, 29, 30, -1, 0, 0 },
    { 17, 21, 47, 25, 44, 29, 45, 34, 16, 26, 31, 53, 15, 38, 18, 23, 28, 41, -1, 0, 0 },
    { 15, 17, 38, 18, 23, 28, 41, 29, 44, 48, 52, 32, 53, 49, 34, 16, 20, 21, 51, 24, -1 }
};

/* asm 9-1952, 1888 insns. Init step: the floor, the path nodes, the stage and both duellists. */
void fn_1_3CEC(M543_WORK *work)
{
    unsigned int jointMot[3] = { 0x650010, 0x650011, 0x650012 };
    MGACTOR_PARAM param;
    s16 tileLink[40][4] = {
        { -1, -1, -1, -1 },
        { -1, 56, -1, 15 },
        { 56, 57, -1, 16 },
        { 57, -1, -1, 17 },
        { -1, -1, -1, -1 },
        { -1, 38, -1, 18 },
        { 38, 42, 15, 19 },
        { 42, 46, 16, 20 },
        { 46, 50, 17, 21 },
        { 50, -1, -1, 22 },
        { 36, 39, 18, 23 },
        { 39, 43, 19, 24 },
        { 43, 47, 20, 25 },
        { 47, 51, 21, 26 },
        { 51, 54, 22, 27 },
        { 37, 40, 23, 28 },
        { 40, 44, 24, 29 },
        { 44, 48, 25, 30 },
        { 48, 52, 26, 31 },
        { 52, 55, 27, 32 },
        { -1, 41, 28, -1 },
        { 41, 45, 29, 33 },
        { 45, 49, 30, 34 },
        { 49, 53, 31, 35 },
        { 53, -1, 32, -1 },
        { -1, -1, -1, -1 },
        { -1, 58, 33, -1 },
        { 58, 59, 34, -1 },
        { 59, -1, 35, -1 },
        { -1, -1, -1, -1 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    };
    float tilePos[30][2] = {
        { -520.0f, -422.0f },
        { -520.0f, -162.0f },
        { -530.0f, 0.0f },
        { -520.0f, 162.0f },
        { -520.0f, 422.0f },
        { -316.0f, -422.0f },
        { -316.0f, -211.0f },
        { -316.0f, 0.0f },
        { -316.0f, 211.0f },
        { -316.0f, 422.0f },
        { -105.0f, -422.0f },
        { -105.0f, -211.0f },
        { -105.0f, 0.0f },
        { -105.0f, 211.0f },
        { -105.0f, 422.0f },
        { 105.0f, -422.0f },
        { 105.0f, -211.0f },
        { 105.0f, 0.0f },
        { 105.0f, 211.0f },
        { 105.0f, 422.0f },
        { 316.0f, -422.0f },
        { 316.0f, -211.0f },
        { 316.0f, 0.0f },
        { 316.0f, 211.0f },
        { 316.0f, 422.0f },
        { 480.0f, -422.0f },
        { 480.0f, -211.0f },
        { 480.0f, 0.0f },
        { 480.0f, 211.0f },
        { 480.0f, 422.0f }
    };
    s16 i;
    s16 j;
    s16 k;
    s16 rnd;

    memset(&lbl_1_bss_B94, 0, sizeof(M543_GAME));
    memset(lbl_1_bss_8DC, 0, sizeof(lbl_1_bss_8DC));
    memset(lbl_1_bss_33C, 0, sizeof(lbl_1_bss_33C));
    memset(lbl_1_bss_1C, 0, sizeof(lbl_1_bss_1C));
    memset(&lbl_1_bss_0, 0, sizeof(M543_ACTORS));
    lbl_1_bss_15E0 = work;
    for(i=0; i<4; i++) {
        lbl_1_bss_B94.seF[i] = -1;
    }
    for(i=0; i<45; i++) {
        lbl_1_bss_33C[i].activeF = 1;
    }
    rnd = frandmod(1000);
    for(i=1; i<rnd; i++) {
        frandmod(i);
    }
    rnd = frandmod(15);
    for(i=0; i<21; i++) {
        if(lbl_1_data_560[rnd][i] == -1) {
            break;
        }
        lbl_1_bss_33C[lbl_1_data_560[rnd][i]-15].activeF = 0;
    }
    for(i=0; i<4; i++) {
        lbl_1_bss_33C[i+41].activeF = 0;
    }
    for(i=0; i<40; i++) {
        {
            lbl_1_bss_1C[i].pos.x = tilePos[i][0];
            lbl_1_bss_1C[i].pos.y = 100.0f;
            lbl_1_bss_1C[i].pos.z = tilePos[i][1];
        }
        for(j=0; j<4; j++) {
            if(tileLink[i][j] != -1) {
                lbl_1_bss_1C[i].link[j] = tileLink[i][j]-15;
            } else {
                lbl_1_bss_1C[i].link[j] = -1;
            }
        }
    }
    for(i=0; i<7; i++) {
        lbl_1_bss_15E0->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15E0->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15E0->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15E0->models[i].modelId, 0);
        lbl_1_bss_15E0->models[i].pos.x = 0.0f;
        lbl_1_bss_15E0->models[i].pos.y = 0.0f;
        lbl_1_bss_15E0->models[i].pos.z = 0.0f;
        lbl_1_bss_15E0->models[i].rot.x = 0.0f;
        lbl_1_bss_15E0->models[i].rot.y = 0.0f;
        lbl_1_bss_15E0->models[i].rot.z = 0.0f;
        Hu3DModelShadowMapSet(lbl_1_bss_15E0->models[i].modelId);
        Hu3DModelAttrReset(lbl_1_bss_15E0->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[i].modelId, HU3D_MOTATTR_LOOP);
    }
    lbl_1_bss_15E0->models[6].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15E0->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_15E0->models[6].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_15E0->models[6].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_15E0->models[6].modelId, 1);
    lbl_1_bss_15E0->models[6].pos.x = 0.0f;
    lbl_1_bss_15E0->models[6].pos.y = 0.0f;
    lbl_1_bss_15E0->models[6].pos.z = 0.0f;
    lbl_1_bss_15E0->models[6].rot.x = 0.0f;
    lbl_1_bss_15E0->models[6].rot.y = 0.0f;
    lbl_1_bss_15E0->models[6].rot.z = 0.0f;
    Hu3DModelAttrReset(lbl_1_bss_15E0->models[6].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_15E0->models[6].modelId, HU3D_MOTATTR_LOOP);
    for(i=0, j=12; i<3; i++, j++) {
        lbl_1_bss_15E0->models[i+12].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15E0->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[i+12].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15E0->models[i+12].modelId, 1);
        lbl_1_bss_15E0->models[i+12].pos.x = 0.0f;
        lbl_1_bss_15E0->models[i+12].pos.y = 0.0f;
        lbl_1_bss_15E0->models[i+12].pos.z = 0.0f;
        lbl_1_bss_15E0->models[i+12].rot.x = 0.0f;
        lbl_1_bss_15E0->models[i+12].rot.y = 0.0f;
        lbl_1_bss_15E0->models[i+12].rot.z = 0.0f;
    }
    for(i=8, j=8; i<=11; i++, j++) {
        lbl_1_bss_15E0->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15E0->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15E0->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15E0->models[i].modelId, 0);
        lbl_1_bss_15E0->models[i].pos.x = 0.0f;
        lbl_1_bss_15E0->models[i].pos.y = 0.0f;
        lbl_1_bss_15E0->models[i].pos.z = 0.0f;
        lbl_1_bss_15E0->models[i].rot.x = 0.0f;
        lbl_1_bss_15E0->models[i].rot.y = 0.0f;
        lbl_1_bss_15E0->models[i].rot.z = 0.0f;
        if(i != 10 && i != 11) {
            Hu3DModelAttrReset(lbl_1_bss_15E0->models[i].modelId, HU3D_ATTR_DISPOFF);
        }
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[i].modelId, HU3D_MOTATTR_LOOP);
    }
    Hu3DModelAttrSet(lbl_1_bss_15E0->models[8].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_15E0->models[9].modelId, HU3D_ATTR_DISPOFF);
    for(i=0, j=15; i<41; i++, j++) {
        lbl_1_bss_15E0->models[j].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_15E0->stageDataTbl[15], HU_MEMNUM_OVL, HEAP_MODEL));
        for(k=0; k<3; k++) {
            lbl_1_bss_33C[i].motId[k] = Hu3DJointMotion(lbl_1_bss_15E0->models[j].modelId, HuDataSelHeapReadNum(jointMot[k], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        Hu3DModelAttrSet(lbl_1_bss_15E0->models[j].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_15E0->models[j].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_15E0->models[j].modelId, 0);
        Hu3DModelScaleSet(lbl_1_bss_15E0->models[j].modelId, 1.154f, 1.0f, 1.0f);
        Hu3DMotionSet(lbl_1_bss_15E0->models[j].modelId, lbl_1_bss_33C[i].motId[0]);
        Hu3DMotionSpeedSet(lbl_1_bss_15E0->models[j].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_15E0->models[j].modelId, 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_15E0->models[j].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_15E0->models[j].modelId, HU3D_MOTATTR_LOOP);
        lbl_1_bss_15E0->models[j].pos.x = 0.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = 0.0f;
        lbl_1_bss_15E0->models[j].rot.x = 0.0f;
        lbl_1_bss_15E0->models[j].rot.y = 0.0f;
        lbl_1_bss_15E0->models[j].rot.z = 0.0f;
    }
    for(i=15; i<=35; i++) {
        lbl_1_bss_15E0->models[i].rot.x = 0.0f;
        lbl_1_bss_15E0->models[i].rot.y = -90.0f;
        lbl_1_bss_15E0->models[i].rot.z = 0.0f;
    }
    for(i=0, j=15; i<3; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -422.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -211.0f+(211.0f*i);
    }
    for(i=0, j=18; i<5; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -211.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -422.0f+(211.0f*i);
    }
    for(i=0, j=23; i<5; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = 0.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -422.0f+(211.0f*i);
    }
    for(i=0, j=28; i<5; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = 211.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -422.0f+(211.0f*i);
    }
    for(i=0, j=33; i<3; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = 422.0f;
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -211.0f+(211.0f*i);
    }
    for(i=0, j=36; i<2; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -105.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -527.5f;
    }
    for(i=0, j=38; i<4; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -316.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -316.5f;
    }
    for(i=0, j=42; i<4; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -316.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = -105.5f;
    }
    for(i=0, j=46; i<4; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -316.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = 105.5f;
    }
    for(i=0, j=50; i<4; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -316.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = 316.5f;
    }
    for(i=0, j=54; i<2; i++, j++) {
        lbl_1_bss_15E0->models[j].pos.x = -105.5f+(211.0f*i);
        lbl_1_bss_15E0->models[j].pos.y = 100.0f;
        lbl_1_bss_15E0->models[j].pos.z = 527.5f;
    }
    lbl_1_bss_0.colMdlId[0] = lbl_1_bss_15E0->models[12].modelId;
    lbl_1_bss_0.colMdlId[1] = lbl_1_bss_15E0->models[13].modelId;
    lbl_1_bss_0.colMdlId[2] = lbl_1_bss_15E0->models[14].modelId;
    MgActorColMapInit(lbl_1_bss_0.colMdlId, 3, 10);
    param.height = 150.0f;
    param.radius = 35.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0x8000;
    param.narrowHook = fn_1_A308;
    param.correctHookParam = 0;
    param.correctHook = fn_1_A69C;
    lbl_1_bss_0.player[0] = MgPlayerCreate(lbl_1_bss_15E0->chr[0].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[0]->actor->pos.x = -614.0f;
    lbl_1_bss_0.player[0]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[0]->actor->pos.z = -100.0f;
    lbl_1_bss_0.player[0]->actor->rotY = 90.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[0]->actor->mdlId, 1);
    Hu3DModelShadowSet(lbl_1_bss_0.player[0]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[0]->actor->mdlId);
    lbl_1_bss_15E0->models[60].modelId = lbl_1_bss_0.player[0]->actor->mdlId;
    param.param = 1;
    lbl_1_bss_0.player[1] = MgPlayerCreate(lbl_1_bss_15E0->chr[1].no, &param, 1, 1, ~(MGPLAYER_ACTFLAG_JUMP|MGPLAYER_ACTFLAG_PUNCH|MGPLAYER_ACTFLAG_KICK|MGPLAYER_ACTFLAG_HIPDROP|MGPLAYER_ACTFLAG_STUN), NULL);
    lbl_1_bss_0.player[1]->actor->pos.x = -614.0f;
    lbl_1_bss_0.player[1]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[1]->actor->pos.z = 100.0f;
    lbl_1_bss_0.player[1]->actor->rotY = 90.0f;
    Hu3DModelLayerSet(lbl_1_bss_0.player[1]->actor->mdlId, 1);
    Hu3DModelShadowSet(lbl_1_bss_0.player[1]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[1]->actor->mdlId);
    lbl_1_bss_15E0->models[61].modelId = lbl_1_bss_0.player[1]->actor->mdlId;
    CharModelStepFxSet(lbl_1_bss_15E0->chr[0].charNo, 0);
    CharModelStepFxSet(lbl_1_bss_15E0->chr[1].charNo, 0);
    CharEffectLayerSet(2);
    fn_1_D408(0);
    fn_1_D408(1);
    fn_1_10150();
    fn_1_239C();
    fn_1_6770();
    lbl_1_bss_B94.mgTimer = fn_1_1A8C(0, 30, 0, 292.0f, 64.0f);
}

/* asm 1955-2023, 67 insns. Init hook step. */
s16 fn_1_5A6C(M543_WORK *work)
{
    HU3DMODEL *model;
    s16 result;

    result = 1;
    fn_1_3CEC(work);
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    model = &Hu3DData[lbl_1_bss_15E0->models[60].modelId];
    lbl_1_bss_8DC[0].pos = model->pos;
    model = &Hu3DData[lbl_1_bss_15E0->models[61].modelId];
    lbl_1_bss_8DC[1].pos = model->pos;
    return result;
}

/* asm 2026-2041, 14 insns. Fade-in step: the intro. */
s16 fn_1_5B78(void)
{
    s16 result;

    result = 0;
    result = fn_1_86E4();
    fn_1_6770();
    return result;
}

/* asm 2044-2073, 28 insns. Start step. */
s16 fn_1_5BB0(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_B94.mode = 0;
    lbl_1_bss_B94.winMode = 0;
    lbl_1_bss_B94.unk04 = 0;
    lbl_1_bss_B94.timer = 0;
    fn_1_6770();
    return result;
}

/* asm 2076-2491, 391 insns. Main step: the timer, the duellists, the computer, collision. */
s16 fn_1_5C20(void)
{
    HuVecF pos;
    s16 i;
    s16 doneF;
    s16 result;
    s16 endF;
    s32 playerNo;

    result = 0;
    endF = 0;
    switch(lbl_1_bss_B94.mode) {
        case 0:
            fn_1_1B00(lbl_1_bss_B94.mgTimer);
            lbl_1_bss_B94.mode++;

        case 1:
            doneF = fn_1_1B2C(lbl_1_bss_B94.mgTimer);
            for(i=0; i<2; i++) {
                fn_1_69BC(i);
            }
            if(lbl_1_bss_B94.winner == 0 && doneF == 0) {
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_8DC[i].comF) {
                        if(lbl_1_bss_8DC[i].comWait == -1) {
                            fn_1_D9E8(i);
                        } else {
                            lbl_1_bss_8DC[i].comWait--;
                        }
                        if(lbl_1_bss_8DC[i].comWait == 0) {
                            lbl_1_bss_8DC[i].comWait = -1;
                            lbl_1_bss_8DC[i].comTimer = 0;
                        }
                    }
                }
            }
            if(lbl_1_bss_B94.winner != 0 || doneF != 0) {
                lbl_1_bss_8DC[0].padOffF = 1;
                lbl_1_bss_8DC[1].padOffF = 1;
                endF = 1;
            }
            if(endF != 0 || doneF != 0) {
                lbl_1_bss_B94.mode++;
            }
            break;

        case 2:
            fn_1_391C(1, 100);
            fn_1_1B54(lbl_1_bss_B94.mgTimer);
            if(lbl_1_bss_B94.winner) {
                MgSeqWinnerSet(lbl_1_bss_15E0->chr[lbl_1_bss_B94.winner&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                playerNo = lbl_1_bss_15E0->chr[lbl_1_bss_B94.winner&1].no;
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
        if(lbl_1_bss_8DC[i].comF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], lbl_1_bss_8DC[i].stkX, lbl_1_bss_8DC[i].stkY, lbl_1_bss_8DC[i].btnDown, lbl_1_bss_8DC[i].btn);
        }
        if(lbl_1_bss_8DC[i].padOffF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
        }
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_8DC[0].oldPos.x = pos.x;
    lbl_1_bss_8DC[0].oldPos.y = pos.y;
    lbl_1_bss_8DC[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_8DC[1].oldPos.x = pos.x;
    lbl_1_bss_8DC[1].oldPos.y = pos.y;
    lbl_1_bss_8DC[1].oldPos.z = pos.z;
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_8DC[0].pos.x = pos.x;
    lbl_1_bss_8DC[0].pos.y = pos.y;
    lbl_1_bss_8DC[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_8DC[1].pos.x = pos.x;
    lbl_1_bss_8DC[1].pos.y = pos.y;
    lbl_1_bss_8DC[1].pos.z = pos.z;
    fn_1_A6B0();
    pos.x = lbl_1_bss_8DC[0].pos.x;
    pos.y = lbl_1_bss_8DC[0].pos.y;
    pos.z = lbl_1_bss_8DC[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_8DC[1].pos.x;
    pos.y = lbl_1_bss_8DC[1].pos.y;
    pos.z = lbl_1_bss_8DC[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    if(lbl_1_bss_B94.hitF == 0) {
        lbl_1_bss_8DC[0].comTimer = 0;
        lbl_1_bss_8DC[1].comTimer = 0;
    }
    lbl_1_bss_B94.hitF = 0;
    fn_1_71AC();
    fn_1_6770();
    return result;
}

/* asm 2494-2549, 54 insns. Finish step. */
s16 fn_1_623C(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_B94.mode = 0;
    lbl_1_bss_B94.winMode = 0;
    lbl_1_bss_B94.unk04 = 0;
    lbl_1_bss_B94.timer = 0;
    lbl_1_bss_8DC[0].knockMode = 0;
    lbl_1_bss_8DC[1].knockMode = 0;
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    fn_1_71AC();
    fn_1_6770();
    return result;
}

/* asm 2552-2567, 14 insns. Pre-winner step. */
s16 fn_1_6314(void)
{
    s16 result;

    result = 0;
    result = fn_1_91F8();
    fn_1_6770();
    return result;
}

/* asm 2570-2661, 88 insns. Winner step: the winner's pose. */
s16 fn_1_634C(void)
{
    DS_PLAYER *pl;
    HU3DMODEL *model;
    s16 result;

    model = &Hu3DData[lbl_1_bss_15E0->models[(lbl_1_bss_B94.winner&1)+60].modelId];
    result = 0;
    if(lbl_1_bss_15E0->mode[0] == 0) {
        if(lbl_1_bss_B94.winner) {
            pl = &lbl_1_bss_15E0->player[lbl_1_bss_B94.winner&1];
            pl->motNo = 5;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        }
        lbl_1_bss_15E0->mode[0] = 1;
        lbl_1_bss_B94.rotY = model->rot.y;
    }
    fn_1_6770();
    CharModelVoicePanSet(lbl_1_bss_15E0->chr[lbl_1_bss_B94.winner&1].charNo, 64);
    return result;
}

/* asm 2664-2677, 12 insns. Fade-out step. */
s16 fn_1_64AC(void)
{
    s16 result;

    result = 1;
    fn_1_6770();
    return result;
}

/* asm 2680-2703, 22 insns. Close step. */
s16 fn_1_64DC(void)
{
    s16 result;

    result = 1;
    fn_1_3CCC();
    MgActorKill(lbl_1_bss_0.player[0]->actor);
    MgActorKill(lbl_1_bss_0.player[1]->actor);
    return result;
}

/* asm 2706-2852, 143 insns. Unreferenced: fn_1_6770 without the camera, light and shadow. */
void fn_1_6534(void)
{
    s16 i;
    s16 pan;
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    float x;

    modelA = &Hu3DData[lbl_1_bss_15E0->models[60].modelId];
    modelB = &Hu3DData[lbl_1_bss_15E0->models[61].modelId];
    for(i=0; i<=55; i++) {
        Hu3DModelPosSet(lbl_1_bss_15E0->models[i].modelId, lbl_1_bss_15E0->models[i].pos.x, lbl_1_bss_15E0->models[i].pos.y, lbl_1_bss_15E0->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15E0->models[i].modelId, lbl_1_bss_15E0->models[i].rot.x, lbl_1_bss_15E0->models[i].rot.y, lbl_1_bss_15E0->models[i].rot.z);
    }
    x = 0.042666666f*modelA->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15E0->chr[0].charNo, pan);
    x = 0.042666666f*modelB->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15E0->chr[1].charNo, pan);
}

/* asm 2855-3005, 147 insns. Push the stage and panel models, pan the voices, place the camera, light and shadow. */
void fn_1_6770(void)
{
    s16 i;
    s16 pan;
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    float x;

    modelA = &Hu3DData[lbl_1_bss_15E0->models[60].modelId];
    modelB = &Hu3DData[lbl_1_bss_15E0->models[61].modelId];
    for(i=0; i<=55; i++) {
        Hu3DModelPosSet(lbl_1_bss_15E0->models[i].modelId, lbl_1_bss_15E0->models[i].pos.x, lbl_1_bss_15E0->models[i].pos.y, lbl_1_bss_15E0->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_15E0->models[i].modelId, lbl_1_bss_15E0->models[i].rot.x, lbl_1_bss_15E0->models[i].rot.y, lbl_1_bss_15E0->models[i].rot.z);
    }
    x = 0.042666666f*modelA->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15E0->chr[0].charNo, pan);
    x = 0.042666666f*modelB->pos.x;
    pan = 64.0f+x;
    CharModelVoicePanSet(lbl_1_bss_15E0->chr[1].charNo, pan);
    fn_1_91C(0);
    fn_1_10C4();
    fn_1_14C4();
}

/*
 * asm 3008-3222, 205 insns. One duellist's knock-back: on a panel hit, rumble,
 * pan the sound and hold the pad; wait for the actor to land, pause it, run
 * fn_1_6CF0 and let it go. 1 only in the unused mode 6.
 */
s16 fn_1_69BC(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 doneF;
    s16 pan;
    float x;

    pl = &lbl_1_bss_15E0->player[player];
    result = 0;
    doneF = 0;
    switch(lbl_1_bss_8DC[player].mode) {
        case 0:
            if(lbl_1_bss_8DC[player].knockF) {
                omVibrate(lbl_1_bss_15E0->chr[player].no, 20, 12, 0);
                x = 0.042666666f*lbl_1_bss_15E0->models[player+60].pos.x;
                pan = 64.0f+x;
                fn_1_3A5C(1, 126, pan);
                lbl_1_bss_8DC[player].padOffF = 1;
                lbl_1_bss_8DC[player].mode++;
            }
            break;

        case 1:
            if(lbl_1_bss_0.player[player]->mode == 0) {
                lbl_1_bss_8DC[player].mode++;
            }
            break;

        case 2:
            MgPlayerPauseOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_8DC[player].mode++;
            break;

        case 3:
            doneF = fn_1_6CF0(player);
            if(doneF) {
                lbl_1_bss_8DC[player].knockF = 0;
                lbl_1_bss_8DC[player].mode++;
            }
            break;

        case 4:
            MgPlayerPauseOff(lbl_1_bss_0.player[player], &lbl_1_bss_8DC[player].pos);
            lbl_1_bss_8DC[player].hitF = 0;
            lbl_1_bss_8DC[player].mode++;
            break;

        case 5:
            lbl_1_bss_8DC[player].padOffF = 0;
            lbl_1_bss_8DC[player].mode = 0;
            break;

        case 6:
            result = 1;
            break;
    }
    return result;
}

s16 (*lbl_1_data_7F4[2])(s16 no) = { fn_1_7394, fn_1_7704 };

/*
 * asm 3225-3536, 303 insns. Slide player from knockStart to knockEnd over 42
 * frames, then shift into the stumble (motion 3), back to the stand (motion 4)
 * and the idle. 1 when done.
 */
s16 fn_1_6CF0(s16 player)
{
    HuVecF pos;
    HU3DMODEL *model;
    DS_PLAYER *pl;
    s16 result;
    s16 count;

    model = &Hu3DData[lbl_1_bss_15E0->models[player+60].modelId];
    pl = &lbl_1_bss_15E0->player[player];
    result = 0;
    count = 0;
    switch(lbl_1_bss_8DC[player].knockMode) {
        case 0:
            pl->motNo = 2;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_8DC[player].knockTimer = 0;
            lbl_1_bss_8DC[player].knockMode++;
            break;

        case 1:
            count += fn_1_1970(&lbl_1_bss_8DC[player].pos.x, 42.0f, lbl_1_bss_8DC[player].knockStart.x, lbl_1_bss_8DC[player].knockEnd.x);
            count += fn_1_1970(&lbl_1_bss_8DC[player].pos.z, 42.0f, lbl_1_bss_8DC[player].knockStart.z, lbl_1_bss_8DC[player].knockEnd.z);
            lbl_1_bss_8DC[player].knockTimer++;
            pos.x = lbl_1_bss_8DC[player].pos.x;
            pos.y = lbl_1_bss_8DC[player].pos.y;
            pos.z = lbl_1_bss_8DC[player].pos.z;
            MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &pos);
            if(pl->endF || count == 0 || lbl_1_bss_8DC[player].knockTimer >= 42) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 3;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_8DC[player].knockTimer = 0;
                lbl_1_bss_8DC[player].stunF = 1;
                lbl_1_bss_8DC[player].knockMode++;
            }
            break;

        case 2:
            if(lbl_1_bss_8DC[player].knockTimer++ >= 25) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 4;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_8DC[player].stunF = 0;
                lbl_1_bss_8DC[player].knockMode++;
            }
            break;

        case 3:
            if(pl->endF) {
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_8DC[player].knockMode = 0;
                result = 1;
            }
            break;
    }
    model->pos.x = lbl_1_bss_8DC[player].pos.x;
    model->pos.z = lbl_1_bss_8DC[player].pos.z;
    return result;
}

/* asm 3539-3668, 122 insns. Run each placed panel's current motion routine (lbl_1_data_7F4). */
s16 fn_1_71AC(void)
{
    s16 result;
    s16 i;

    result = 0;
    for(i=0; i<41; i++) {
        if(lbl_1_bss_33C[i].activeF) {
            switch(lbl_1_bss_33C[i].mode) {
                case 0:
                    lbl_1_bss_33C[i].motSel = lbl_1_bss_33C[i].motSelOld = 1;
                    lbl_1_bss_33C[i].motMode = 2;
                    lbl_1_bss_33C[i].unk0E = 0;
                    lbl_1_bss_33C[i].mode++;

                case 1:
                    if(lbl_1_bss_33C[i].motSel != lbl_1_bss_33C[i].motSelOld) {
                        lbl_1_bss_33C[i].motMode = 0;
                    }
                    lbl_1_bss_33C[i].motSelOld = lbl_1_bss_33C[i].motSel;
                    lbl_1_data_7F4[lbl_1_bss_33C[i].motSel](i);
                    break;
            }
        }
    }
    return result;
}

/* asm 3671-3899, 220 insns. Panel no sinks (motion 0) with a dust wave, then rests on motion 2. 1 once rested. */
s16 fn_1_7394(s16 no)
{
    HuVecF pos;
    s16 mdlNo;
    s16 result;

    result = 0;
    mdlNo = no+15;
    switch(lbl_1_bss_33C[no].motMode) {
        case 0:
            Hu3DMotionSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motId[0]);
            Hu3DMotionSpeedSet(lbl_1_bss_15E0->models[mdlNo].modelId, 1.0f);
            lbl_1_bss_33C[no].motTime = 0.0f;
            Hu3DMotionTimeSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motTime);
            Hu3DModelAttrReset(lbl_1_bss_15E0->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
            pos.x = lbl_1_bss_15E0->models[mdlNo].pos.x;
            pos.y = 100.0f;
            pos.z = lbl_1_bss_15E0->models[mdlNo].pos.z;
            if(no < 21) {
                fn_1_2898(&pos, 1);
            } else {
                fn_1_2898(&pos, 0);
            }
            lbl_1_bss_33C[no].motMode++;

        case 1:
            lbl_1_bss_33C[no].motTime = Hu3DMotionTimeGet(lbl_1_bss_15E0->models[mdlNo].modelId);
            if(Hu3DMotionEndCheck(lbl_1_bss_15E0->models[mdlNo].modelId)) {
                Hu3DMotionSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motId[2]);
                Hu3DModelAttrSet(lbl_1_bss_15E0->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_15E0->models[mdlNo].modelId, 1.0f);
                Hu3DMotionTimeSet(lbl_1_bss_15E0->models[mdlNo].modelId, 0.0f);
                lbl_1_bss_33C[no].motTime = 0.0f;
                lbl_1_bss_33C[no].motMode++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 3902-4130, 220 insns. Panel no rises back (motion 1) with a dust wave, then stops on motion 0. 1 once stopped. */
s16 fn_1_7704(s16 no)
{
    HuVecF pos;
    s16 mdlNo;
    s16 result;

    result = 0;
    mdlNo = no+15;
    switch(lbl_1_bss_33C[no].motMode) {
        case 0:
            Hu3DMotionSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motId[1]);
            Hu3DMotionSpeedSet(lbl_1_bss_15E0->models[mdlNo].modelId, 1.0f);
            lbl_1_bss_33C[no].motTime = 0.0f;
            Hu3DMotionTimeSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motTime);
            Hu3DModelAttrReset(lbl_1_bss_15E0->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
            pos.x = lbl_1_bss_15E0->models[mdlNo].pos.x;
            pos.y = 100.0f;
            pos.z = lbl_1_bss_15E0->models[mdlNo].pos.z;
            if(no < 21) {
                fn_1_2898(&pos, 1);
            } else {
                fn_1_2898(&pos, 0);
            }
            lbl_1_bss_33C[no].motMode++;

        case 1:
            lbl_1_bss_33C[no].motTime = Hu3DMotionTimeGet(lbl_1_bss_15E0->models[mdlNo].modelId);
            if(Hu3DMotionEndCheck(lbl_1_bss_15E0->models[mdlNo].modelId)) {
                Hu3DMotionSet(lbl_1_bss_15E0->models[mdlNo].modelId, lbl_1_bss_33C[no].motId[0]);
                Hu3DMotionSpeedSet(lbl_1_bss_15E0->models[mdlNo].modelId, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_15E0->models[mdlNo].modelId, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_15E0->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                lbl_1_bss_33C[no].motTime = 0.0f;
                lbl_1_bss_33C[no].motMode++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 4133-4243, 105 insns. Unreferenced (fn_1_86E4 inlines it): shake the camera centre round four offsets. */
void fn_1_7A74(void)
{
    s16 unusedA = 0;
    s16 unusedB = 0;
    float ofs[4][2] = { { 8.0f, 0.0f }, { -8.0f, 0.0f }, { 0.0f, 8.0f }, { 0.0f, -8.0f } };

    switch(lbl_1_bss_B94.shakeMode) {
        case 0:
            lbl_1_bss_B94.camPos.x = 0.0f;
            lbl_1_bss_B94.camPos.z = 0.0f;
            lbl_1_bss_B94.shakeCnt = 0;
            lbl_1_bss_B94.shakeMode++;
            break;

        case 1:
            lbl_1_bss_18->center.x += ofs[lbl_1_bss_B94.shakeNo][0];
            lbl_1_bss_18->center.z += ofs[lbl_1_bss_B94.shakeNo][1];
            if(++lbl_1_bss_B94.shakeCnt >= 2) {
                if(++lbl_1_bss_B94.shakeNo >= 4) {
                    lbl_1_bss_B94.shakeNo = 0;
                }
                lbl_1_bss_B94.shakeMode = 0;
            }
            break;
    }
}

/*
 * asm 4246-4968, 691 insns. Every 26 frames drop the next of nine panel rows
 * with a rumble; run the dropping panels down and back up. 1 once all nine
 * rows have gone.
 */
s16 fn_1_7C18(void)
{
    s16 result = 0;
    s16 rowTbl[9][7] = {
        { 18, 19, 20, -1, 0, 0, 0 },
        { 26, 30, 34, 38, -1, 0, 0 },
        { 13, 14, 15, 16, 17, -1, 0 },
        { 22, 25, 29, 33, 37, 40, -1 },
        { 8, 9, 10, 11, 12, -1, 0 },
        { 21, 24, 28, 32, 36, 39, -1 },
        { 3, 4, 5, 6, 7, -1, 0 },
        { 23, 27, 31, 35, -1, 0, 0 },
        { 0, 1, 2, -1, 0, 0, 0 }
    };
    s16 vib[9] = { 15, 15, 15, 15, 15, 15, 15, 18, 25 };
    s16 i;
    s16 doneCnt;

    if(lbl_1_bss_B94.dropTimer++ > 25) {
        lbl_1_bss_B94.dropTimer = 0;
        if(lbl_1_bss_B94.dropRow < 9) {
            for(i=0;; i++) {
                if(rowTbl[lbl_1_bss_B94.dropRow][i] == -1) {
                    break;
                }
                lbl_1_bss_33C[rowTbl[lbl_1_bss_B94.dropRow][i]].dropF = 1;
            }
            fn_1_39E4(3);
            switch(lbl_1_bss_B94.dropRow) {
                case 0:
                case 1:
                case 2:
                    omVibrate(lbl_1_bss_15E0->chr[0].no, vib[lbl_1_bss_B94.dropRow], 6, 6);
                    omVibrate(lbl_1_bss_15E0->chr[1].no, vib[lbl_1_bss_B94.dropRow], 6, 6);
                    break;

                case 3:
                case 4:
                case 5:
                    omVibrate(lbl_1_bss_15E0->chr[0].no, vib[lbl_1_bss_B94.dropRow], 4, 2);
                    omVibrate(lbl_1_bss_15E0->chr[1].no, vib[lbl_1_bss_B94.dropRow], 4, 2);
                    break;

                case 6:
                case 7:
                case 8:
                    omVibrate(lbl_1_bss_15E0->chr[0].no, vib[lbl_1_bss_B94.dropRow], 12, 0);
                    omVibrate(lbl_1_bss_15E0->chr[1].no, vib[lbl_1_bss_B94.dropRow], 12, 0);
                    break;
            }
        }
        if(++lbl_1_bss_B94.dropRow >= 9) {
            result = 1;
        }
    }
    for(i=0; i<41; i++) {
        if(lbl_1_bss_33C[i].dropF) {
            doneCnt = 0;
            switch(lbl_1_bss_33C[i].dropMode) {
                case 0:
                    lbl_1_bss_33C[i].dropMode++;

                case 1:
                    doneCnt += fn_1_7394(i);
                    if(doneCnt) {
                        lbl_1_bss_33C[i].motMode = 0;
                        lbl_1_bss_33C[i].dropMode++;
                    }
                    break;

                case 2:
                    doneCnt += fn_1_7704(i);
                    if(doneCnt) {
                        lbl_1_bss_33C[i].dropF = 0;
                        lbl_1_bss_33C[i].motMode = 0;
                        lbl_1_bss_33C[i].dropMode = 0;
                    }
                    break;
            }
        }
    }
    return result;
}

/*
 * asm 4971-5710, 709 insns. The intro: music, the whistle, the camera shaking
 * while the rows drop, the camera running to the start line, then to the
 * duel's camera, and the panels that are gone laid flat. 1 when done.
 */
s32 fn_1_86E4(void)
{
    float speed;
    s32 result;
    s16 count;
    s16 i;
    s16 mdlNo;

    result = 0;
    count = 0;
    switch(lbl_1_bss_B94.mode) {
        case 0:
            fn_1_38EC();
            lbl_1_bss_B94.mode++;

        case 1:
            if(lbl_1_bss_B94.timer++ > 60) {
                fn_1_39E4(2);
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 2:
            fn_1_7A74();
            if(lbl_1_bss_B94.timer++ > 30) {
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 3:
            fn_1_7A74();
            fn_1_7C18();
            if(lbl_1_bss_B94.timer++ > 35) {
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 4:
            fn_1_7A74();
            speed = 250.0f;
            fn_1_1850(&lbl_1_bss_18->center.x, speed, 500.0f, -654.0f);
            count = fn_1_7C18();
            if(count) {
                lbl_1_bss_B94.mode++;
            }
            break;

        case 5:
            fn_1_7A74();
            speed = 250.0f;
            count = fn_1_1850(&lbl_1_bss_18->center.x, speed, 500.0f, -654.0f);
            fn_1_7C18();
            if(lbl_1_bss_B94.timer++ > 35 && count == 0) {
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 6:
            if(lbl_1_bss_B94.timer++ > 60) {
                lbl_1_bss_B94.camPos.x = lbl_1_bss_18->center.x;
                lbl_1_bss_B94.camPos.z = lbl_1_bss_18->center.z;
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 7:
            speed = 30.0f;
            count = fn_1_1850(&lbl_1_bss_18->center.x, speed, lbl_1_bss_B94.camPos.x, lbl_1_data_1D8[1].center.x);
            count += fn_1_1850(&lbl_1_bss_18->center.z, speed, lbl_1_bss_B94.camPos.z, lbl_1_data_1D8[1].center.z);
            count += fn_1_1850(&lbl_1_bss_18->rot.x, speed, lbl_1_data_1D8[0].rot.x, lbl_1_data_1D8[1].rot.x);
            count += fn_1_1850(&lbl_1_bss_18->zoom, speed, lbl_1_data_1D8[0].zoom, lbl_1_data_1D8[1].zoom);
            if(count == 0) {
                for(i=0, mdlNo=15; i<45; i++, mdlNo++) {
                    if(lbl_1_bss_33C[i].activeF == 0) {
                        lbl_1_bss_15E0->models[mdlNo].pos.y = 0.0f;
                    }
                }
                lbl_1_bss_B94.mode++;
            }
            break;

        case 8:
            result = 1;
            break;
    }
    return result;
}

/*
 * asm 5713-6740, 987 insns. Pre-winner step: lower the stepped-on panels row
 * by row, then walk the winner to the finish post and turn the camera to them.
 */
s32 fn_1_91F8(void)
{
    HU3DMODEL *model = &Hu3DData[lbl_1_bss_15E0->models[(lbl_1_bss_B94.winner&1)+60].modelId];
    DS_PLAYER *pl = &lbl_1_bss_15E0->player[lbl_1_bss_B94.winner&1];
    s32 result = 0;
    s16 count = 0;
    s16 rowTbl[5][12] = {
        { 18, 19, 20, 26, 30, 34, 38, -1, 0, 0, 0, 0 },
        { 13, 14, 15, 16, 17, 22, 25, 29, 33, 37, 40, -1 },
        { 8, 9, 10, 11, 12, 21, 24, 28, 32, 36, 39, -1 },
        { 3, 4, 5, 6, 7, 23, 27, 31, 35, -1, 0, 0 },
        { 0, 1, 2, -1, 0, 0, 0, 0, 0, 0, 0, 0 }
    };
    s16 pan5[5] = { 316, 105, -105, -316, -480 };
    HuVecF pos;
    s16 i;
    s16 total;
    s16 no;
    s16 pan;
    s16 player;
    float x;
    float speed;
    float dx;
    float dz;
    float dist;

    switch(lbl_1_bss_B94.mode) {
        case 0:
            if(lbl_1_bss_B94.timer++ > 30) {
                for(i=0; i<41; i++) {
                    lbl_1_bss_33C[i].motMode = 0;
                }
                omVibrate(lbl_1_bss_15E0->chr[0].no, 30, 12, 0);
                omVibrate(lbl_1_bss_15E0->chr[1].no, 30, 12, 0);
                x = 0.042666666f*pan5[0];
                pan = 64.0f+x;
                fn_1_3A5C(3, 126, pan);
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.dropRow = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 1:
            i = 0;
            total = 0;
            count = 0;
            do {
                if(lbl_1_bss_33C[rowTbl[lbl_1_bss_B94.dropRow][i]].activeF && lbl_1_bss_33C[rowTbl[lbl_1_bss_B94.dropRow][i]].motSel == 1) {
                    no = rowTbl[lbl_1_bss_B94.dropRow][i];
                    count += fn_1_7394(no);
                    total++;
                }
                i++;
            } while(rowTbl[lbl_1_bss_B94.dropRow][i] != -1);
            if(count == total) {
                if(++lbl_1_bss_B94.dropRow >= 5) {
                    lbl_1_bss_B94.dropTimer = 0;
                    lbl_1_bss_B94.mode++;
                } else {
                    i = 0;
                    total = 0;
                    do {
                        if(lbl_1_bss_33C[rowTbl[lbl_1_bss_B94.dropRow][i]].activeF && lbl_1_bss_33C[rowTbl[lbl_1_bss_B94.dropRow][i]].motSel == 1) {
                            total++;
                        }
                        i++;
                    } while(rowTbl[lbl_1_bss_B94.dropRow][i] != -1);
                    if(total) {
                        omVibrate(lbl_1_bss_15E0->chr[0].no, 30, 12, 0);
                        omVibrate(lbl_1_bss_15E0->chr[1].no, 30, 12, 0);
                        x = 0.042666666f*pan5[lbl_1_bss_B94.dropRow];
                        pan = 64.0f+x;
                        fn_1_3A5C(3, 126, pan);
                    }
                }
            }
            break;

        case 2:
            if(lbl_1_bss_B94.timer++ > 90) {
                lbl_1_bss_B94.timer = 0;
                lbl_1_bss_B94.mode++;
            }
            break;

        case 3:
            if(lbl_1_bss_B94.winner == 0) {
                lbl_1_bss_B94.mode = 5;
            } else {
                lbl_1_bss_B94.mode = 4;
            }
            break;

        case 4:
            speed = 30.0f;
            count += fn_1_1850(&lbl_1_bss_18->center.x, speed, lbl_1_data_1D8[1].center.x, model->pos.x);
            count += fn_1_1850(&lbl_1_bss_18->center.y, speed, lbl_1_data_1D8[1].center.y, 70.0f+model->pos.y);
            count += fn_1_1850(&lbl_1_bss_18->center.z, speed, lbl_1_data_1D8[1].center.z, model->pos.z);
            count += fn_1_1850(&lbl_1_bss_18->rot.x, speed, lbl_1_data_1D8[1].rot.x, -18.0f);
            count += fn_1_1850(&lbl_1_bss_18->zoom, speed, lbl_1_data_1D8[1].zoom, 500.0f);
            if(count == 0) {
                lbl_1_bss_B94.mode++;
            }
            break;

        case 5:
            result = 1;
            break;
    }
    if(lbl_1_bss_B94.winner) {
        switch(lbl_1_bss_B94.winMode) {
            case 0:
                lbl_1_bss_B94.winMode++;
                break;

            case 1:
                MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
                MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
                player = lbl_1_bss_B94.winner&1;
                lbl_1_bss_8DC[player].chasePos.x = 654.0f;
                lbl_1_bss_8DC[player].chasePos.z = 0.0f;
                lbl_1_bss_8DC[player].chaseSpeed = 7.0f;
                lbl_1_bss_8DC[player].chaseRadius = 0.0f;
                dx = 654.0f-model->pos.x;
                dz = -model->pos.z;
                dist = sqrt((dx*dx)+(dz*dz));
                count = fn_1_E144(player);
                MgActorExec();
                if(dist < 20.0f) {
                    lbl_1_bss_B94.rotY = model->rot.y;
                    lbl_1_bss_B94.winMode++;
                }
                break;

            case 2:
                speed = 30.0f;
                count = fn_1_1850(&model->rot.y, speed, lbl_1_bss_B94.rotY, 0.0f);
                if(count == 0) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 8.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                    lbl_1_bss_B94.winMode++;
                }
                break;

            case 3:
                break;
        }
    }
    for(i=0; i<2; i++) {
        switch(lbl_1_bss_8DC[i].knockMode) {
            case 0:
                pl = &lbl_1_bss_15E0->player[i];
                if(pl->motNo == 2 || pl->motNo == 3 || pl->motNo == 4) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 8.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                }
                lbl_1_bss_8DC[i].knockMode++;
                break;

            case 1:
                break;
        }
    }
    return result;
}

/*
 * asm 6743-6857, 105 insns. Unreferenced (fn_1_A308 and fn_1_A6B0 inline it):
 * while the duellists touch, a computer duellist's patience runs out after 40
 * frames (it waits 80 and the other stops) and resets after 180.
 */
void fn_1_A164(void)
{
    if(lbl_1_bss_8DC[0].stunF == 0) {
        if(lbl_1_bss_8DC[0].comF) {
            lbl_1_bss_8DC[0].comTimer++;
        }
        if(lbl_1_bss_8DC[0].comTimer > 40) {
            lbl_1_bss_8DC[0].comWait = 80;
            lbl_1_bss_8DC[1].comWait = -1;
            lbl_1_bss_8DC[1].comTimer = 0;
        }
        if(lbl_1_bss_8DC[0].comTimer > 180) {
            lbl_1_bss_8DC[0].comWait = -1;
            lbl_1_bss_8DC[0].comTimer = 0;
        }
    } else {
        lbl_1_bss_8DC[0].comTimer = 0;
    }
    if(lbl_1_bss_8DC[1].stunF == 0) {
        if(lbl_1_bss_8DC[1].comF) {
            lbl_1_bss_8DC[1].comTimer++;
        }
        if(lbl_1_bss_8DC[1].comTimer > 40) {
            lbl_1_bss_8DC[1].comWait = 80;
            lbl_1_bss_8DC[0].comWait = -1;
            lbl_1_bss_8DC[0].comTimer = 0;
        }
        if(lbl_1_bss_8DC[1].comTimer > 180) {
            lbl_1_bss_8DC[1].comWait = -1;
            lbl_1_bss_8DC[1].comTimer = 0;
        }
    } else {
        lbl_1_bss_8DC[1].comTimer = 0;
    }
    lbl_1_bss_B94.hitF = 1;
}

/* asm 6860-7104, 229 insns. The duellists' collision hook: on a body-body hit, fn_1_A164. The distance is unused. */
int fn_1_A308(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    s16 unused;
    float dist;
    HuVecF d;
    float mag;

    unused = 0;
    switch(b->type) {
        case 0:
            if(a->paramB == 0) {
                d.x = lbl_1_bss_8DC[0].pos.x-lbl_1_bss_8DC[1].pos.x;
                d.z = lbl_1_bss_8DC[0].pos.z-lbl_1_bss_8DC[1].pos.z;
                mag = (d.x*d.x)+(d.z*d.z);
                dist = sqrt(mag);
                fn_1_A164();
            }
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            break;
    }
    return 0;
}

/* asm 7107-7113, 5 insns. The actors' correction hook: reads the actor's param and does nothing. */
void fn_1_A69C(MGACTOR *actor, int param)
{
    int unused;

    unused = actor->param;
}

/*
 * asm 7116-10133, 2902 insns. Collision after the actors moved: every raised
 * panel a duellist runs into knocks them back off its nearest edge (and wakes
 * the panel), the duellists push each other apart, the four posts and the
 * sixteen walls push them out, anything outside the floor snaps back, and the
 * first past x=554 wins.
 */
void fn_1_A6B0(void)
{
    float c;
    float a;
    float b;
    float reach;
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    float x;
    float tz;
    s16 unused;
    s16 order[4];
    float knockX[2];
    float knockZ[2];
    float scale[4][2];
    float edge[4][4];
    s16 i;
    s16 j;
    s16 k;
    s16 side;
    s16 mdlNo;
    s16 hitF;
    s16 doneF;
    s16 wallF;
    s16 postF;
    s16 pan;
    float px;
    float pz;
    float radius;
    float dx;
    float dz;
    float push;
    float dist;
    float rotY;
    float tx;
    float s;

    wallF = 0;
    postF = 0;
    unused = 0;
    radius = 25.0f;
    for(j=0; j<2; j++) {
        knockX[j] = 0.0f;
        knockZ[j] = 0.0f;
    }
    reach = 40.0f+radius;
    for(i=0, mdlNo=15; i<41; i++, mdlNo++) {
        if(lbl_1_bss_33C[i].activeF == 0) {
            continue;
        }
        if(mdlNo < 36) {
            minX = lbl_1_bss_15E0->models[mdlNo].pos.x-25.0f;
            minZ = lbl_1_bss_15E0->models[mdlNo].pos.z-80.5f;
            maxX = 25.0f+lbl_1_bss_15E0->models[mdlNo].pos.x;
            maxZ = 80.5f+lbl_1_bss_15E0->models[mdlNo].pos.z;
            a = 1.0f;
            b = 0.0f;
        } else {
            minX = lbl_1_bss_15E0->models[mdlNo].pos.x-80.5f;
            minZ = lbl_1_bss_15E0->models[mdlNo].pos.z-25.0f;
            maxX = 80.5f+lbl_1_bss_15E0->models[mdlNo].pos.x;
            maxZ = 25.0f+lbl_1_bss_15E0->models[mdlNo].pos.z;
            a = 0.0f;
            b = 1.0f;
        }
        for(j=0, hitF=0; j<2; j++) {
            a = 1.0f;
            b = 1.0f;
            if(lbl_1_bss_8DC[j].pos.x+(reach*a) >= minX && lbl_1_bss_8DC[j].pos.x-(reach*a) <= maxX
                && lbl_1_bss_8DC[j].pos.z+(reach*b) >= minZ && lbl_1_bss_8DC[j].pos.z-(reach*b) <= maxZ) {
                hitF = 1;
                lbl_1_bss_33C[i].owner = j;
                if(lbl_1_bss_8DC[j].pos.x+(radius*a) >= minX && lbl_1_bss_8DC[j].pos.x-(radius*a) <= maxX
                    && lbl_1_bss_8DC[j].pos.z+(radius*b) >= minZ && lbl_1_bss_8DC[j].pos.z-(radius*b) <= maxZ) {
                    lbl_1_bss_8DC[j].knockF = 1;
                    lbl_1_bss_8DC[j].hitF = 1;
                    edge[0][0] = minX;
                    edge[0][1] = minZ;
                    edge[0][2] = maxX;
                    edge[0][3] = minZ;
                    edge[1][0] = maxX;
                    edge[1][1] = minZ;
                    edge[1][2] = maxX;
                    edge[1][3] = maxZ;
                    edge[2][0] = maxX;
                    edge[2][1] = maxZ;
                    edge[2][2] = minX;
                    edge[2][3] = maxZ;
                    edge[3][0] = minX;
                    edge[3][1] = maxZ;
                    edge[3][2] = minX;
                    edge[3][3] = minZ;
                    scale[0][0] = 1.0f;
                    scale[0][1] = 1.0f;
                    scale[1][0] = 1.0f;
                    scale[1][1] = 1.0f;
                    scale[2][0] = 1.0f;
                    scale[2][1] = 1.0f;
                    scale[3][0] = 1.0f;
                    scale[3][1] = 1.0f;
                    push = 1.0f;
                    rotY = lbl_1_bss_0.player[j]->actor->rotY;
                    if(rotY <= 45.0f && rotY > -45.0f) {
                        order[0] = 0;
                        order[3] = 2;
                        if(rotY <= 45.0f && rotY > 0.0f) {
                            order[1] = 3;
                            order[2] = 1;
                        }
                        if(rotY <= 0.0f && rotY > -45.0f) {
                            order[1] = 1;
                            order[2] = 3;
                        }
                    }
                    if(rotY <= 135.0f && rotY > 45.0f) {
                        order[0] = 3;
                        order[3] = 1;
                        if(rotY <= 135.0f && rotY > 90.0f) {
                            order[1] = 2;
                            order[2] = 0;
                        }
                        if(rotY <= 90.0f && rotY > 45.0f) {
                            order[1] = 0;
                            order[2] = 2;
                        }
                    }
                    if(rotY <= -45.0f && rotY > -135.0f) {
                        order[0] = 1;
                        order[3] = 3;
                        if(rotY <= -45.0f && rotY > -90.0f) {
                            order[1] = 0;
                            order[2] = 2;
                        }
                        if(rotY <= -90.0f && rotY > -135.0f) {
                            order[1] = 2;
                            order[2] = 0;
                        }
                    }
                    if(rotY <= -135.0f || rotY > 135.0f) {
                        order[0] = 2;
                        order[3] = 0;
                        if(rotY <= -135.0f) {
                            order[1] = 1;
                            order[2] = 3;
                        }
                        if(rotY > 135.0f) {
                            order[1] = 3;
                            order[2] = 1;
                        }
                    }
                    for(k=0, doneF=0; k<4; k++) {
                        side = order[k];
                        if(lbl_1_bss_8DC[j].pos.x+(radius*scale[side][0]) >= minX && lbl_1_bss_8DC[j].pos.x-(radius*scale[side][0]) <= maxX
                            && lbl_1_bss_8DC[j].pos.z+(radius*scale[side][1]) >= minZ && lbl_1_bss_8DC[j].pos.z-(radius*scale[side][1]) <= maxZ) {
                            dx = edge[side][0]-edge[side][2];
                            dz = edge[side][1]-edge[side][3];
                            a = (dx*dx)+(dz*dz);
                            b = -1.0f*((dx*(edge[side][0]-lbl_1_bss_8DC[j].pos.x))+(dz*(edge[side][1]-lbl_1_bss_8DC[j].pos.z)));
                            c = b/a;
                            px = (dx*c)+edge[side][0];
                            pz = (dz*c)+edge[side][1];
                            dx = lbl_1_bss_8DC[j].pos.x-px;
                            dz = lbl_1_bss_8DC[j].pos.z-pz;
                            dist = sqrt((dx*dx)+(dz*dz));
                            if(dist < radius) {
                                if(dist <= 1.0f) {
                                    dist = 1.0f;
                                }
                                s = (1.0f+radius)/dist;
                                dx = push*(dx*s);
                                dz = push*(dz*s);
                                lbl_1_bss_8DC[j].pos.x = px+dx;
                                lbl_1_bss_8DC[j].pos.z = pz+dz;
                                if(doneF == 0) {
                                    switch(side) {
                                        case 0:
                                            knockZ[j] = -1.0f;
                                            break;

                                        case 1:
                                            knockX[j] = 1.0f;
                                            break;

                                        case 2:
                                            knockZ[j] = 1.0f;
                                            break;

                                        case 3:
                                            knockX[j] = -1.0f;
                                            break;
                                    }
                                    doneF = 1;
                                }
                            }
                        }
                    }
                }
            }
        }
        if(hitF && lbl_1_bss_33C[i].motMode == 2) {
            lbl_1_bss_33C[i].motSel = 0;
            if(lbl_1_bss_33C[i].motSel != lbl_1_bss_33C[i].motSelOld) {
                omVibrate(lbl_1_bss_15E0->chr[lbl_1_bss_33C[i].owner].no, 10, 4, 2);
                lbl_1_bss_8DC[0].panelF[i] = 1;
                lbl_1_bss_8DC[1].panelF[i] = 1;
                x = 0.042666666f*lbl_1_bss_15E0->models[mdlNo].pos.x;
                pan = 64.0f+x;
                fn_1_3A5C(0, 126, pan);
            }
        } else if(lbl_1_bss_33C[i].motMode == 2) {
            lbl_1_bss_33C[i].motSel = 1;
        }
    }
    for(j=0; j<2; j++) {
        if(knockX[j] || knockZ[j]) {
            lbl_1_bss_8DC[j].knockStart = lbl_1_bss_8DC[j].pos;
            lbl_1_bss_8DC[j].knockEnd = lbl_1_bss_8DC[j].pos;
            if(knockX[j]) {
                lbl_1_bss_8DC[j].knockEnd.x = lbl_1_bss_8DC[j].pos.x+(30.0f*knockX[j]);
            }
            if(knockZ[j]) {
                lbl_1_bss_8DC[j].knockEnd.z = lbl_1_bss_8DC[j].pos.z+(30.0f*knockZ[j]);
            }
        }
    }
    for(j=0; j<2; j++) {
        if(lbl_1_bss_8DC[j^1].hitF) {
            dx = lbl_1_bss_8DC[j^1].pos.x-lbl_1_bss_8DC[j].pos.x;
            dz = lbl_1_bss_8DC[j^1].pos.z-lbl_1_bss_8DC[j].pos.z;
            dist = sqrt((dx*dx)+(dz*dz));
            if(dist < 70.0f) {
                if(dist <= 1.0f) {
                    dist = 1.0f;
                }
                s = 70.0f/dist;
                dx *= s;
                dz *= s;
                lbl_1_bss_8DC[j].pos.x = lbl_1_bss_8DC[j^1].pos.x-dx;
                lbl_1_bss_8DC[j].pos.z = lbl_1_bss_8DC[j^1].pos.z-dz;
                fn_1_A164();
            }
        }
        for(i=0; i<4; i++) {
            dx = lbl_1_data_500[i][0]-lbl_1_bss_8DC[j].pos.x;
            dz = lbl_1_data_500[i][1]-lbl_1_bss_8DC[j].pos.z;
            dist = sqrt((dx*dx)+(dz*dz));
            if(dist < 1.0f+radius) {
                if(dist <= 1.0f) {
                    dist = 1.0f;
                }
                s = (1.0f+radius)/dist;
                dx *= s;
                dz *= s;
                lbl_1_bss_8DC[j].pos.x = lbl_1_data_500[i][0]-dx;
                lbl_1_bss_8DC[j].pos.z = lbl_1_data_500[i][1]-dz;
                postF = 1;
            }
        }
        dx = lbl_1_bss_8DC[j].pos.x;
        dz = lbl_1_bss_8DC[j].pos.z;
        if(!((-dx)+dz > -784.0f && dx < 554.0f && dx+dz < 784.0f && dz < 554.0f && (-dx)+dz < 784.0f && dx > -554.0f && dx+dz > -784.0f && dz > -554.0f)
            && !(dx > -754.0f && dz > -150.0f && dz < 150.0f)
            && !(dx < 754.0f && dz > -150.0f && dz < 150.0f)) {
            lbl_1_bss_8DC[j].pos.x = lbl_1_bss_8DC[j].oldPos.x;
            lbl_1_bss_8DC[j].pos.z = lbl_1_bss_8DC[j].oldPos.z;
        }
        dx = lbl_1_bss_8DC[j].pos.x;
        dz = lbl_1_bss_8DC[j].pos.z;
        for(i=0; i<16; i++) {
            if(lbl_1_data_380[i].ax < lbl_1_data_380[i].bx) {
                dx = lbl_1_data_380[i].ax;
                px = lbl_1_data_380[i].bx;
            } else {
                dx = lbl_1_data_380[i].bx;
                px = lbl_1_data_380[i].ax;
            }
            if(lbl_1_data_380[i].az < lbl_1_data_380[i].bz) {
                dz = lbl_1_data_380[i].az;
                pz = lbl_1_data_380[i].bz;
            } else {
                dz = lbl_1_data_380[i].bz;
                pz = lbl_1_data_380[i].az;
            }
            if(lbl_1_bss_8DC[j].pos.x+(radius*lbl_1_data_380[i].nx) >= dx && lbl_1_bss_8DC[j].pos.x-(radius*lbl_1_data_380[i].nx) <= px
                && lbl_1_bss_8DC[j].pos.z+(radius*lbl_1_data_380[i].nz) >= dz && lbl_1_bss_8DC[j].pos.z-(radius*lbl_1_data_380[i].nz) <= pz) {
                dx = lbl_1_data_380[i].ax-lbl_1_data_380[i].bx;
                dz = lbl_1_data_380[i].az-lbl_1_data_380[i].bz;
                a = (dx*dx)+(dz*dz);
                b = -1.0f*((dx*(lbl_1_data_380[i].ax-lbl_1_bss_8DC[j].pos.x))+(dz*(lbl_1_data_380[i].az-lbl_1_bss_8DC[j].pos.z)));
                c = b/a;
                px = (dx*c)+lbl_1_data_380[i].ax;
                pz = (dz*c)+lbl_1_data_380[i].az;
                dx = lbl_1_bss_8DC[j].pos.x-px;
                dz = lbl_1_bss_8DC[j].pos.z-pz;
                dist = sqrt((dx*dx)+(dz*dz));
                if(dist < radius) {
                    if(dist <= 1.0f) {
                        dist = 1.0f;
                    }
                    push = 1.0f;
                    tx = lbl_1_bss_8DC[j].pos.x;
                    tz = lbl_1_bss_8DC[j].pos.z;
                    switch(i) {
                        case 0:
                            if((-tx)+tz < -784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 1:
                            if(tx > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 5:
                            if(tx > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 6:
                            if(tx+tz > 784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 7:
                            if(tz > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 8:
                            if((-tx)+tz > 784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 9:
                            if(tx < -554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 13:
                            if(tx < -554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 14:
                            if(tx+tz < -784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 15:
                            if(tz < -554.0f) {
                                push = -1.0f;
                            }
                            break;
                    }
                    wallF = 1;
                    s = (1.0f+radius)/dist;
                    dx = push*(dx*s);
                    dz = push*(dz*s);
                    lbl_1_bss_8DC[j].pos.x = px+dx;
                    lbl_1_bss_8DC[j].pos.z = pz+dz;
                }
            }
        }
        dx = lbl_1_bss_8DC[j].pos.x;
        dz = lbl_1_bss_8DC[j].pos.z;
        for(i=0; i<16; i++) {
            if(lbl_1_data_380[i].ax < lbl_1_data_380[i].bx) {
                dx = lbl_1_data_380[i].ax;
                px = lbl_1_data_380[i].bx;
            } else {
                dx = lbl_1_data_380[i].bx;
                px = lbl_1_data_380[i].ax;
            }
            if(lbl_1_data_380[i].az < lbl_1_data_380[i].bz) {
                dz = lbl_1_data_380[i].az;
                pz = lbl_1_data_380[i].bz;
            } else {
                dz = lbl_1_data_380[i].bz;
                pz = lbl_1_data_380[i].az;
            }
            if(lbl_1_bss_8DC[j].pos.x+(radius*lbl_1_data_380[i].nx) >= dx && lbl_1_bss_8DC[j].pos.x-(radius*lbl_1_data_380[i].nx) <= px
                && lbl_1_bss_8DC[j].pos.z+(radius*lbl_1_data_380[i].nz) >= dz && lbl_1_bss_8DC[j].pos.z-(radius*lbl_1_data_380[i].nz) <= pz) {
                dx = lbl_1_data_380[i].ax-lbl_1_data_380[i].bx;
                dz = lbl_1_data_380[i].az-lbl_1_data_380[i].bz;
                a = (dx*dx)+(dz*dz);
                b = -1.0f*((dx*(lbl_1_data_380[i].ax-lbl_1_bss_8DC[j].pos.x))+(dz*(lbl_1_data_380[i].az-lbl_1_bss_8DC[j].pos.z)));
                c = b/a;
                px = (dx*c)+lbl_1_data_380[i].ax;
                pz = (dz*c)+lbl_1_data_380[i].az;
                dx = lbl_1_bss_8DC[j].pos.x-px;
                dz = lbl_1_bss_8DC[j].pos.z-pz;
                dist = sqrt((dx*dx)+(dz*dz));
                if(dist < radius) {
                    if(dist <= 1.0f) {
                        dist = 1.0f;
                    }
                    push = 1.0f;
                    tx = lbl_1_bss_8DC[j].pos.x;
                    tz = lbl_1_bss_8DC[j].pos.z;
                    switch(i) {
                        case 0:
                            if((-tx)+tz < -784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 1:
                            if(tx > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 5:
                            if(tx > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 6:
                            if(tx+tz > 784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 7:
                            if(tz > 554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 8:
                            if((-tx)+tz > 784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 9:
                            if(tx < -554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 13:
                            if(tx < -554.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 14:
                            if(tx+tz < -784.0f) {
                                push = -1.0f;
                            }
                            break;

                        case 15:
                            if(tz < -554.0f) {
                                push = -1.0f;
                            }
                            break;
                    }
                    wallF = 1;
                    s = (1.0f+radius)/dist;
                    dx = push*(dx*s);
                    dz = push*(dz*s);
                    lbl_1_bss_8DC[j].pos.x = px+dx;
                    lbl_1_bss_8DC[j].pos.z = pz+dz;
                }
            }
        }
        if(lbl_1_bss_B94.winner == 0 && lbl_1_data_500[0][0] < lbl_1_bss_8DC[j].pos.x) {
            lbl_1_bss_B94.winner = j|((j^1)<<1);
        }
    }
}

/* Per duellist: each of the four directions as a node-index step, and the order they are tried in (fn_1_D9E8 rewrites both). */
s16 lbl_1_data_8A0[2][4] = { { 5, -1, 1, -5 }, { 5, -1, 1, -5 } };
s16 lbl_1_data_8B0[2][4] = { { 3, 0, 1, 2 }, { 3, 0, 1, 2 } };

/* asm 10136-10519, 376 insns. A computer duellist's settings by difficulty, and its start node. */
void fn_1_D408(s16 player)
{
    float walkSpeed[4] = { 7.2f, 8.0f, 9.0f, 10.285714f };
    float dirWeight[4][5] = {
        { 25.0f, 25.0f, 25.0f, 25.0f, 10.0f },
        { 25.0f, 25.0f, 15.0f, 35.0f, 15.0f },
        { 20.0f, 20.0f, 5.0f, 55.0f, 20.0f },
        { 15.0f, 15.0f, 10.0f, 60.0f, 30.0f }
    };
    float stepSpeed[4] = { 2.88f, 3.6f, 4.8f, 7.2f };
    s16 tryChance[4] = { 50, 40, 30, 15 };
    s16 stepWaitMax[4] = { 20, 15, 10, 3 };

    if(lbl_1_bss_15E0->chr[player].dif != 0) {
        lbl_1_bss_8DC[player].comF = 1;
        lbl_1_bss_8DC[player].comLevel = lbl_1_bss_15E0->chr[player].dif-1;
        lbl_1_bss_8DC[player].walkSpeed = walkSpeed[lbl_1_bss_8DC[player].comLevel];
        lbl_1_bss_8DC[player].chaseRadius = 11.0f;
        lbl_1_bss_8DC[player].dirWeight[0] = dirWeight[lbl_1_bss_8DC[player].comLevel][0];
        lbl_1_bss_8DC[player].dirWeight[1] = dirWeight[lbl_1_bss_8DC[player].comLevel][1];
        lbl_1_bss_8DC[player].dirWeight[2] = dirWeight[lbl_1_bss_8DC[player].comLevel][2];
        lbl_1_bss_8DC[player].dirWeight[3] = dirWeight[lbl_1_bss_8DC[player].comLevel][3];
        lbl_1_bss_8DC[player].dirBonus = dirWeight[lbl_1_bss_8DC[player].comLevel][4];
        lbl_1_bss_8DC[player].tryChance = tryChance[lbl_1_bss_8DC[player].comLevel];
        lbl_1_bss_8DC[player].stepSpeed = stepSpeed[lbl_1_bss_8DC[player].comLevel];
        lbl_1_bss_8DC[player].stepWaitMax = stepWaitMax[lbl_1_bss_8DC[player].comLevel];
        lbl_1_bss_8DC[player].tileF[0] = -1;
        lbl_1_bss_8DC[player].tileF[4] = -1;
        lbl_1_bss_8DC[player].tileF[25] = -1;
        lbl_1_bss_8DC[player].tileF[29] = -1;
        lbl_1_bss_8DC[player].panelF[21] = 1;
        lbl_1_bss_8DC[player].panelF[22] = 1;
        lbl_1_bss_8DC[player].panelF[39] = 1;
        lbl_1_bss_8DC[player].panelF[40] = 1;
        if(player == 0) {
            lbl_1_bss_8DC[player].curTile = frandmod(2)+1;
        } else if(player == 1) {
            if(lbl_1_bss_8DC[0].curTile == 1) {
                lbl_1_bss_8DC[1].curTile = frandmod(2)+2;
            } else if(lbl_1_bss_8DC[0].curTile == 2) {
                lbl_1_bss_8DC[1].curTile = 3;
            } else {
                lbl_1_bss_8DC[1].curTile = frandmod(3)+1;
            }
        }
        lbl_1_bss_8DC[player].nextTile = lbl_1_bss_8DC[player].prevTile = lbl_1_bss_8DC[player].curTile;
    }
}

/*
 * asm 10522-11019, 471 insns. A computer duellist: walk to its node, pick the
 * next (fn_1_EF58), try the panel in the way (fn_1_E340), and at the last row
 * make for node 27 and the finish. The direction order is re-rolled from the
 * weights after every node.
 */
s16 fn_1_D9E8(s16 player)
{
    s16 result = 0;
    s16 ret = 0;
    s16 roll[4];
    s16 weight[4] = { -1, 1, -5, 5 };
    s16 usedF[4] = { 0, 0, 0, 0 };
    s16 bonus[4] = { 0, 0, 0, 0 };
    s16 best[2];
    s16 i;
    s16 j;

    lbl_1_bss_8DC[player].stkX = 0;
    lbl_1_bss_8DC[player].stkY = 0;
    lbl_1_bss_8DC[player].btnDown = 0;
    lbl_1_bss_8DC[player].btn = 0;
    switch(lbl_1_bss_8DC[player].comMode) {
        case 0:
            lbl_1_bss_8DC[player].chasePos = lbl_1_bss_1C[lbl_1_bss_8DC[player].nextTile].pos;
            lbl_1_bss_8DC[player].chaseSpeed = lbl_1_bss_8DC[player].walkSpeed;
            lbl_1_bss_8DC[player].comMode++;

        case 1:
            ret = fn_1_E144(player);
            if(ret == 0) {
                break;
            }
            if(lbl_1_bss_8DC[player].curTile == 26 || lbl_1_bss_8DC[player].curTile == 27 || lbl_1_bss_8DC[player].curTile == 28) {
                lbl_1_bss_8DC[player].comMode = 3;
                break;
            }
            ret = fn_1_EF58(player);
            if(ret == 2) {
                lbl_1_bss_8DC[player].comMode = 2;
            } else if(ret == 1) {
                lbl_1_bss_8DC[player].chasePos = lbl_1_bss_1C[lbl_1_bss_8DC[player].nextTile].pos;
                lbl_1_bss_8DC[player].chaseSpeed = lbl_1_bss_8DC[player].walkSpeed;
                if((lbl_1_bss_8DC[player].comLevel == 2 || lbl_1_bss_8DC[player].comLevel == 3) && lbl_1_bss_8DC[player].curTile >= 15) {
                    switch(lbl_1_bss_8DC[player].curTile) {
                        case 15:
                        case 16:
                        case 20:
                        case 21:
                        case 25:
                        case 26:
                            bonus[1] = lbl_1_bss_8DC[player].dirBonus;
                            break;

                        case 18:
                        case 19:
                        case 23:
                        case 24:
                        case 28:
                        case 29:
                            bonus[0] = lbl_1_bss_8DC[player].dirBonus;
                            break;
                    }
                }
                for(i=0; i<4; i++) {
                    for(j=0; j<4; j++) {
                        if(usedF[j] == 0) {
                            roll[j] = frandmod(lbl_1_bss_8DC[player].dirWeight[j]+bonus[j]);
                        } else {
                            roll[j] = -1;
                        }
                    }
                    for(j=0, best[0]=0, best[1]=0; j<4; j++) {
                        if(roll[j] >= best[0]) {
                            best[0] = roll[j];
                            best[1] = j;
                        }
                    }
                    usedF[best[1]] = 1;
                    lbl_1_data_8B0[player][i] = best[1];
                }
                for(i=0; i<4; i++) {
                    lbl_1_data_8A0[player][i] = weight[lbl_1_data_8B0[player][i]];
                }
            }
            break;

        case 2:
            ret = fn_1_E340(player);
            if(ret) {
                lbl_1_bss_8DC[player].comMode = 1;
            }
            break;

        case 3:
            lbl_1_bss_8DC[player].chasePos = lbl_1_bss_1C[27].pos;
            lbl_1_bss_8DC[player].chaseSpeed = lbl_1_bss_8DC[player].walkSpeed;
            ret = fn_1_E144(player);
            if(ret) {
                lbl_1_bss_8DC[player].comMode++;
            }
            break;

        case 4:
            lbl_1_bss_8DC[player].chasePos.x = 654.0f;
            lbl_1_bss_8DC[player].chasePos.z = 0.0f;
            lbl_1_bss_8DC[player].chaseSpeed = lbl_1_bss_8DC[player].walkSpeed;
            ret = fn_1_E144(player);
            break;
    }
    return result;
}

/* asm 11022-11157, 127 insns. Steer player at chasePos (4 off to its own side); 1 on arrival. */
s16 fn_1_E144(s16 player)
{
    HuVecF pos;
    s16 result;
    s16 ret;

    result = 0;
    ret = 0;
    switch(lbl_1_bss_8DC[player].chaseMode) {
        case 0:
            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_8DC[player].chaseMode++;
            break;

        case 1:
            pos = lbl_1_bss_8DC[player].chasePos;
            if(player == 0) {
                pos.x += 4.0f;
                pos.z += 4.0f;
            } else {
                pos.x -= 4.0f;
                pos.z -= 4.0f;
            }
            ret = MgPlayerVecChase(lbl_1_bss_0.player[player], &pos, lbl_1_bss_8DC[player].chaseSpeed, lbl_1_bss_8DC[player].chaseRadius);
            if(ret) {
                result = 1;
            }
            break;

        case 2:
            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
            lbl_1_bss_8DC[player].chaseMode = 0;
            result = 1;
            break;
    }
    return result;
}

/*
 * asm 11160-11960, 774 insns. A computer duellist tries the panel ahead: a
 * short step at it (a full one on a raised panel, by chance), a wait, then it
 * either gives up on that panel or marks it walkable, and steps back to its node.
 */
s16 fn_1_E340(s16 player)
{
    float scale = 0.0f;
    s16 result = 0;
    s16 ret = 0;
    float dirOfs[4][4] = {
        { 0.0f, -40.0f, 0.0f, -40.0f },
        { 0.0f, 40.0f, 0.0f, 40.0f },
        { -40.0f, 0.0f, -40.0f, 0.0f },
        { 40.0f, 0.0f, 40.0f, 0.0f }
    };
    s16 rnd;

    switch(lbl_1_bss_8DC[player].stepMode) {
        case 0:
            if(lbl_1_bss_33C[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]]].activeF) {
                rnd = frandmod(101);
                if(rnd < lbl_1_bss_8DC[player].tryChance) {
                    scale = 1.0f;
                }
            }
            lbl_1_bss_8DC[player].chasePos.x = (lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].pos.x+dirOfs[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]][0])+(scale*dirOfs[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]][2]);
            lbl_1_bss_8DC[player].chasePos.z = (lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].pos.z+dirOfs[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]][1])+(scale*dirOfs[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]][3]);
            lbl_1_bss_8DC[player].chaseSpeed = (5.0f*scale)+lbl_1_bss_8DC[player].stepSpeed;
            lbl_1_bss_8DC[player].stepTimer = 0;
            lbl_1_bss_8DC[player].stepPos = lbl_1_bss_8DC[player].chasePos;
            lbl_1_bss_8DC[player].stepMode++;

        case 1:
            ret = fn_1_E144(player);
            if(ret == 0) {
                if(lbl_1_bss_8DC[player].stepTimer++ >= 90) {
                    ret = 1;
                }
            }
            if(lbl_1_bss_8DC[player].knockF) {
                ret = 1;
            }
            if(ret) {
                lbl_1_bss_8DC[player].stepWait = 0;
                lbl_1_bss_8DC[player].stepMode++;
            }
            break;

        case 2:
            if(lbl_1_bss_8DC[player].stepWait++ > lbl_1_bss_8DC[player].stepWaitMax) {
                lbl_1_bss_8DC[player].stepMode++;
            }
            break;

        case 3:
            if(lbl_1_bss_33C[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]]].activeF) {
                lbl_1_bss_8DC[player].panelF[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]]] = 1;
                lbl_1_bss_8DC[player].dirNo = -1;
                lbl_1_bss_8DC[player].stepMode++;
            } else {
                lbl_1_bss_8DC[player].panelF[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][lbl_1_bss_8DC[player].dirNo]]] = 2;
                lbl_1_bss_8DC[player].pathMode++;
                lbl_1_bss_8DC[player].stepMode = 0;
                result = 1;
            }
            break;

        case 4:
            lbl_1_bss_8DC[player].chasePos.x = lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].pos.x;
            lbl_1_bss_8DC[player].chasePos.z = lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].pos.z;
            lbl_1_bss_8DC[player].chaseSpeed = lbl_1_bss_8DC[player].stepSpeed;
            ret = fn_1_E144(player);
            if(ret) {
                lbl_1_bss_8DC[player].stepMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/*
 * asm 11963-12712, 719 insns. A computer duellist's next node: first list the
 * open directions (2 at once for an untried panel ahead), then mark the node
 * dead-ended or not and move on. 1 with nextTile set, 2 to try a panel.
 */
s16 fn_1_EF58(s16 player)
{
    s16 result;
    s16 blocked;
    s16 i;
    s16 cnt;
    s16 next;

    result = 0;
    blocked = 0;
    switch(lbl_1_bss_8DC[player].pathMode) {
        case 0:
            for(i=0, lbl_1_bss_8DC[player].dirNo=-1, lbl_1_bss_8DC[player].altDirNo=0, lbl_1_bss_8DC[player].openNum=0; i<4; i++) {
                next = lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][i];
                if(next != lbl_1_bss_8DC[player].prevTile && lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][i]] != -1 && next >= 0 && next <= 29) {
                    if(lbl_1_bss_8DC[player].panelF[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][i]]] == 0) {
                        if(lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][i]] < 41) {
                            lbl_1_bss_8DC[player].dirNo = i;
                            result = 2;
                            return result;
                        }
                        lbl_1_bss_8DC[player].dirNo = i;
                    } else if(lbl_1_bss_8DC[player].panelF[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[lbl_1_data_8B0[player][i]]] == 2) {
                        if(lbl_1_bss_8DC[player].prevTile != lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][i]) {
                            lbl_1_bss_8DC[player].altDirNo = i;
                        }
                        lbl_1_bss_8DC[player].openDir[lbl_1_bss_8DC[player].openNum] = i;
                        lbl_1_bss_8DC[player].openNum++;
                    }
                }
            }
            lbl_1_bss_8DC[player].pathMode++;
            break;

        case 1:
            if(lbl_1_bss_8DC[player].dirNo != -1) {
                lbl_1_bss_8DC[player].blockedF = 0;
            } else {
                lbl_1_bss_8DC[player].blockedF = 1;
            }
            for(i=0; i<4; i++) {
                if(lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[i] == -1) {
                    blocked++;
                } else if(lbl_1_bss_8DC[player].panelF[lbl_1_bss_1C[lbl_1_bss_8DC[player].curTile].link[i]] == 1) {
                    blocked++;
                }
            }
            cnt = 0;
            next = 0;
            if(blocked >= 3) {
                lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile] = 3;
                lbl_1_bss_8DC[player].blockedF = 1;
            } else if(blocked == 2) {
                if(lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][lbl_1_bss_8DC[player].altDirNo]] == 2) {
                    lbl_1_bss_8DC[player].blockedF = 1;
                }
                lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile] = 2;
                if(lbl_1_bss_8DC[player].blockedF) {
                    lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile] = 3;
                }
            } else if(blocked <= 1) {
                if(lbl_1_bss_8DC[player].blockedF) {
                    for(i=0, cnt=0; i<lbl_1_bss_8DC[player].openNum; i++) {
                        if(lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][lbl_1_bss_8DC[player].openDir[i]]] != 3) {
                            if(cnt == 0) {
                                next = lbl_1_bss_8DC[player].openDir[i];
                            }
                            cnt++;
                        }
                    }
                    lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile] = 3;
                } else {
                    lbl_1_bss_8DC[player].tileF[lbl_1_bss_8DC[player].curTile] = 1;
                }
            }
            if(lbl_1_bss_8DC[player].dirNo != -1) {
                lbl_1_bss_8DC[player].nextTile = lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][lbl_1_bss_8DC[player].dirNo];
            } else if(lbl_1_bss_8DC[player].blockedF) {
                if(cnt) {
                    lbl_1_bss_8DC[player].nextTile = lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][next];
                } else if(blocked >= 3) {
                    lbl_1_bss_8DC[player].nextTile = lbl_1_bss_8DC[player].prevTile;
                } else {
                    lbl_1_bss_8DC[player].nextTile = lbl_1_bss_8DC[player].curTile+lbl_1_data_8A0[player][lbl_1_bss_8DC[player].altDirNo];
                }
            }
            lbl_1_bss_8DC[player].prevTile = lbl_1_bss_8DC[player].curTile;
            lbl_1_bss_8DC[player].curTile = lbl_1_bss_8DC[player].nextTile;
            lbl_1_bss_8DC[player].curTile == lbl_1_bss_8DC[player].nextTile;
            lbl_1_bss_8DC[player].pathMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* Unreferenced: m544's arena positions (its lbl_1_data_418) after one float. */
float lbl_1_data_8FC[25] = {
    0.0f, 0.0f, 0.0f, 0.0f, 913.0f,
    0.0f, -1177.0f, 993.0f, 0.0f, -1038.0f,
    550.0f, 1000.0f, -3250.0f, 593.0f, 312.0f,
    -1119.0f, -462.0f, 330.0f, -1100.0f, -1000.0f,
    40.0f, -2100.0f, -2500.0f, 0.0f, -3900.0f
};
