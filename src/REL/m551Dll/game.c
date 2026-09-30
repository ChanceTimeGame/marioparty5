/*
 * m551dll/game.c -- the duel: two duellists fight over twelve panels, the
 * panel effects, the computer duellists, and the sequence steps. Written from
 * the reference assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m551Dll/asm/REL/m551Dll/game.s.
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

#include "REL/m551Dll/m551.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void fn_1_5FF4(M551_WORK *work);
int fn_1_117B0(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b);
void fn_1_117CC(MGACTOR *actor, int param);
s16 fn_1_805C(M551_WORK *work);
s16 fn_1_81F4(void);
s16 fn_1_822C(void);
s16 fn_1_828C(void);
s16 fn_1_89B0(void);
s16 fn_1_8CBC(void);
s16 fn_1_8D20(void);
s16 fn_1_8FF4(void);
s16 fn_1_9024(void);
void fn_1_9094(void);
void fn_1_9360(void);
s16 fn_1_9654(s16 player);
void fn_1_9934(void);
s16 fn_1_A078(s16 player, s16 no);
s16 fn_1_A5A4(s16 player, s16 arg);
s16 fn_1_A758(s16 player);
s16 fn_1_ADA4(s16 player, s16 arg);
s16 fn_1_B560(s16 player, s16 arg);
s16 fn_1_BE48(s16 player, s16 arg);
s16 fn_1_C680(s16 player, s16 arg);
s16 fn_1_D6A0(s16 player);
s16 fn_1_E738(void);
int fn_1_EA8C(void);
int fn_1_F814(void);
void fn_1_115B0(void);
void fn_1_11D34(s16 player);
s16 fn_1_11F4C(s16 player);
s16 fn_1_12178(s16 player);
s16 fn_1_12510(s16 player);
s16 fn_1_13384(s16 player);
s16 fn_1_13620(s16 player);
s16 fn_1_13AA4(s16 player);
s16 fn_1_13F68(s16 player);
s16 fn_1_143DC(s16 player);
s16 fn_1_14974(s16 player);
s16 fn_1_14FC4(s16 player);
void fn_1_153A8(void);

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s32 lbl_1_bss_17A04;                /* unreferenced; dtk sizes lbl_1_bss_17A00 8 */
M551_WORK *lbl_1_bss_17A00;         /* set by fn_1_5FF4 */
M551_SPOT lbl_1_bss_179A0[12];
HU3DMODELID lbl_1_bss_1799C[2];
M551_PARTICLEPARAM *lbl_1_bss_17998;

/* --- .data --- */

/* The five hit reactions fn_1_A078 runs, by panel kind. */
s16 (*lbl_1_data_5B0[5])(s16 player, s16 arg) = {
    fn_1_A5A4,
    fn_1_ADA4,
    fn_1_B560,
    fn_1_BE48,
    fn_1_C680
};

/* asm 9-2141, 2074 insns. Init step: the game state, the panels and their kinds, the stage models and both duellists. */
void fn_1_5FF4(M551_WORK *work)
{
    MGACTOR_PARAM param;
    s16 used[12];
    HuVecF center = { 0.0f, 100.0f, 0.0f };
    HuVecF pos;
    float radius = 480.0f;
    s16 kindNum[5] = { 0, 0, 0, 0, 0 };
    s16 kindMax[5] = { 1, 2, 3, 3, 3 };
    s16 i;
    s16 j;
    s16 k;
    s16 n;

    memset(&lbl_1_bss_16CB4, 0, sizeof(M551_GAME));
    memset(lbl_1_bss_16A84, 0, sizeof(lbl_1_bss_16A84));
    memset(lbl_1_bss_16844, 0, sizeof(lbl_1_bss_16844));
    memset(&lbl_1_bss_1679C, 0, sizeof(M551_PAPERMAN));
    memset(lbl_1_bss_3C, 0, sizeof(lbl_1_bss_3C));
    memset(&lbl_1_bss_0, 0, sizeof(M551_ACTORS));
    lbl_1_bss_17A00 = work;
    for(i=0; i<8; i++) {
        lbl_1_bss_16CB4.seF[i] = -1;
    }
    for(i=0; i<12; i++) {
        lbl_1_bss_16CB4.panelKind[i] = -1;
        used[i] = 0;
    }
    lbl_1_bss_16CB4.tpLvl = 0.0f;
    lbl_1_bss_16CB4.ambColor = 1.0f;
    lbl_1_bss_16A84[0].tint = 255.0f;
    lbl_1_bss_16A84[1].tint = 255.0f;
    lbl_1_bss_16A84[0].tpLvl = 1.0f;
    lbl_1_bss_16A84[1].tpLvl = 1.0f;
    lbl_1_bss_16A84[0].panelNo = -1;
    lbl_1_bss_16A84[1].panelNo = -1;
    lbl_1_bss_16A84[0].unk014 = -1;
    lbl_1_bss_16A84[1].unk014 = -1;
    for(i=0; i<12; i++) {
        for(j=0, k=(i*4)+6; j<4; j++, k++) {
            lbl_1_bss_179A0[i].mdlNo[j] = k;
        }
    }
    do {
        do {
            n = frandmod(12);
        } while(used[n] != 0);
        used[n] = 1;
        i = n;
        do {
            k = frandmod(5);
        } while(kindNum[k] >= kindMax[k]);
        kindNum[k]++;
        lbl_1_bss_16844[i].no = k;
        if(k == 0) {
            lbl_1_bss_16CB4.mdlSel = i;
        }
        for(i=0; i<12; i++) {
            if(used[i] == 0) {
                i = 99;
            }
        }
    } while(i != 12);
    for(i=0; i<12; i++) {
        if(lbl_1_bss_16844[i].no == 0) {
            lbl_1_bss_16CB4.centreSpot = i;
        }
    }
    for(i=0; i<12; i++) {
        do {
            k = frandmod(12);
            for(j=0, n=0; j<12; j++) {
                if(lbl_1_bss_16CB4.panelKind[j] == k) {
                    n = 1;
                }
            }
        } while(n != 0);
        lbl_1_bss_16CB4.panelKind[i] = k;
    }
    for(i=0; i<6; i++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 2);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
        if(i == 0) {
            Hu3DModelShadowMapSet(lbl_1_bss_17A00->models[i].modelId);
        } else {
            if(i == 4) {
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 0.5f);
            } else {
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 1.0f);
            }
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[i].modelId, 0.0f);
            Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_MOTATTR_LOOP);
    }
    lbl_1_bss_17A00->models[80].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[24], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_17A00->models[80].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_17A00->models[80].modelId, 1);
    lbl_1_bss_17A00->models[80].pos.x = 0.0f;
    lbl_1_bss_17A00->models[80].pos.y = 0.0f;
    lbl_1_bss_17A00->models[80].pos.z = 0.0f;
    lbl_1_bss_17A00->models[80].rot.x = 0.0f;
    lbl_1_bss_17A00->models[80].rot.y = 0.0f;
    lbl_1_bss_17A00->models[80].rot.z = 0.0f;
    used[0] = 6;
    used[1] = 7;
    used[2] = 8;
    used[3] = 23;
    for(i=6, j=0, k=0; i<=53; i++, j++, k++) {
        if(j >= 4) {
            j = 0;
        }
        pos.x = center.x+radius*cos(M_PI*(30.0f*((i-6)/4))/180.0);
        pos.y = 0.1f+center.y;
        pos.z = center.z+radius*sin(M_PI*(30.0f*((i-6)/4))/180.0);
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[used[j]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        if(j != 0) {
            Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 0);
        } else {
            Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        }
        lbl_1_bss_17A00->models[i].pos.x = pos.x;
        lbl_1_bss_17A00->models[i].pos.y = pos.y;
        lbl_1_bss_17A00->models[i].pos.z = pos.z;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
        if(used[j] == 7 || used[j] == 7) {
            Hu3DModelShadowMapSet(lbl_1_bss_17A00->models[i].modelId);
        }
        if(i == 43) {
            lbl_1_bss_17A00->models[i].pos.x = pos.x;
            lbl_1_bss_17A00->models[i].pos.y = pos.y-26.0f;
            lbl_1_bss_17A00->models[i].pos.z = pos.z;
        }
    }
    for(i=0; i<12; i++) {
        for(j=0; j<=1; j++) {
            Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[j]].modelId, HU3D_ATTR_DISPOFF);
        }
    }
    for(i=54; i<=55; i++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[10], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
        Hu3DModelShadowSet(lbl_1_bss_17A00->models[i].modelId);
        Hu3DModelShadowDispOn(lbl_1_bss_17A00->models[i].modelId);
    }
    for(i=56; i<=57; i++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[9], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 0);
        Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 0.0f);
        Hu3DModelShadowMapSet(lbl_1_bss_17A00->models[i].modelId);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
    }
    for(i=58, j=11; i<=61; i++, j++) {
        if(i == 60) {
            j = 11;
        }
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 0.0f);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
    }
    used[0] = 16;
    used[1] = 16;
    used[2] = 13;
    used[3] = 14;
    used[4] = 15;
    used[5] = 16;
    used[6] = 16;
    used[7] = 13;
    used[8] = 14;
    used[9] = 15;
    for(i=62, j=0; i<=71; i++, j++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[used[j]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        if(j == 16) {
            Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        } else {
            Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        }
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 0.0f);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
    }
    for(i=72, j=17; i<=75; i++, j++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
    }
    for(i=76, j=0; i<=78; i++, j++) {
        lbl_1_bss_17A00->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[21], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_17A00->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_17A00->models[i].modelId, 3);
        Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 0.0f);
        Hu3DMotionTimeSet(lbl_1_bss_17A00->models[i].modelId, 30.0f*j);
        Hu3DModelAttrSet(lbl_1_bss_17A00->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[i].modelId, lbl_1_bss_16CB4.tpLvl);
        lbl_1_bss_17A00->models[i].pos.x = 0.0f;
        lbl_1_bss_17A00->models[i].pos.y = 0.0f;
        lbl_1_bss_17A00->models[i].pos.z = 0.0f;
        lbl_1_bss_17A00->models[i].rot.x = 0.0f;
        lbl_1_bss_17A00->models[i].rot.y = 0.0f;
        lbl_1_bss_17A00->models[i].rot.z = 0.0f;
    }
    lbl_1_bss_17A00->models[79].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_17A00->stageDataTbl[22], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_17A00->models[79].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_17A00->models[79].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_17A00->models[79].modelId, 3);
    Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[79].modelId, lbl_1_bss_16CB4.tpLvl);
    lbl_1_bss_17A00->models[79].pos.x = 0.0f;
    lbl_1_bss_17A00->models[79].pos.y = 0.0f;
    lbl_1_bss_17A00->models[79].pos.z = 0.0f;
    lbl_1_bss_17A00->models[79].rot.x = 0.0f;
    lbl_1_bss_17A00->models[79].rot.y = 0.0f;
    lbl_1_bss_17A00->models[79].rot.z = 0.0f;
    for(i=0, j=0; i<=11; i++, j++) {
        lbl_1_bss_0.colMdlId[i] = lbl_1_bss_17A00->models[lbl_1_bss_179A0[j].mdlNo[3]].modelId;
    }
    lbl_1_bss_0.colMdlId[12] = lbl_1_bss_17A00->models[80].modelId;
    MgActorColMapInit(lbl_1_bss_0.colMdlId, 13, 5);
    param.height = 150.0f;
    param.radius = 35.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0x8000;
    param.narrowHook = fn_1_117B0;
    param.correctHookParam = 0;
    param.correctHook = fn_1_117CC;
    lbl_1_bss_0.player[0] = MgPlayerCreate(lbl_1_bss_17A00->chr[0].no, &param, 4, 1, -1, NULL);
    lbl_1_bss_0.player[0]->actor->pos.x = -200.0f;
    lbl_1_bss_0.player[0]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[0]->actor->pos.z = 0.0f;
    Hu3DModelShadowSet(lbl_1_bss_0.player[0]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[0]->actor->mdlId);
    lbl_1_bss_17A00->models[81].modelId = lbl_1_bss_0.player[0]->actor->mdlId;
    param.param = 1;
    lbl_1_bss_0.player[1] = MgPlayerCreate(lbl_1_bss_17A00->chr[1].no, &param, 4, 1, -1, NULL);
    lbl_1_bss_0.player[1]->actor->pos.x = 200.0f;
    lbl_1_bss_0.player[1]->actor->pos.y = 140.0f;
    lbl_1_bss_0.player[1]->actor->pos.z = 0.0f;
    Hu3DModelShadowSet(lbl_1_bss_0.player[1]->actor->mdlId);
    Hu3DModelShadowDispOn(lbl_1_bss_0.player[1]->actor->mdlId);
    lbl_1_bss_17A00->models[82].modelId = lbl_1_bss_0.player[1]->actor->mdlId;
    Hu3DModelLayerSet(lbl_1_bss_17A00->models[lbl_1_bss_17A00->models[81].modelId].modelId, 2);
    Hu3DModelLayerSet(lbl_1_bss_17A00->models[lbl_1_bss_17A00->models[82].modelId].modelId, 2);
    CharModelStepFxSet(lbl_1_bss_17A00->chr[0].charNo, 0);
    CharModelStepFxSet(lbl_1_bss_17A00->chr[1].charNo, 0);
    CharEffectLayerSet(5);
    fn_1_11D34(0);
    fn_1_11D34(1);
    lbl_1_bss_16A84[0].height = CharModelHeightGet(lbl_1_bss_0.player[0]->charNo);
    lbl_1_bss_16A84[1].height = CharModelHeightGet(lbl_1_bss_0.player[1]->charNo);
    lbl_1_bss_16A84[0].itemHook = CharModelItemHookGet(lbl_1_bss_0.player[0]->charNo, 4, 4);
    lbl_1_bss_16A84[1].itemHook = CharModelItemHookGet(lbl_1_bss_0.player[1]->charNo, 4, 4);
    lbl_1_bss_16A84[0].gravity = lbl_1_bss_0.player[0]->actor->gravity;
    lbl_1_bss_16A84[1].gravity = lbl_1_bss_0.player[1]->actor->gravity;
    fn_1_170B0();
    fn_1_5860(0);
    fn_1_5860(1);
    fn_1_2354();
    fn_1_9360();
    lbl_1_bss_16CB4.mgTimer = fn_1_1A44(0, 60, 0, 292.0f, 64.0f);
}

/* asm 2144-2249, 102 insns. Init hook: settle both duellists on their start marks. */
s16 fn_1_805C(M551_WORK *work)
{
    s16 result;
    int i;
    HuVecF pos;

    result = 1;
    fn_1_5FF4(work);
    for(i=0; i<10; i++) {
        MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
        MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
        pos.x = -200.0f;
        pos.y = 110.0f;
        pos.z = 0.0f;
        MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
        pos.x = 200.0f;
        pos.y = 110.0f;
        pos.z = 0.0f;
        MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
        MgActorExec();
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].pos = pos;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].pos = pos;
    return result;
}

/* asm 2252-2267, 14 insns. Fade-in hook. */
s16 fn_1_81F4(void)
{
    s16 result;

    result = 0;
    result = fn_1_EA8C();
    fn_1_9360();
    return result;
}

/* asm 2270-2295, 24 insns. Start hook. */
s16 fn_1_822C(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_16CB4.mode = 0;
    lbl_1_bss_16CB4.unk02 = 0;
    lbl_1_bss_16CB4.unk04 = 0;
    fn_1_9360();
    return result;
}

/* asm 2298-2780, 457 insns. The main hook. */
s16 fn_1_828C(void)
{
    s16 result;
    s16 doneF;
    s16 i;
    int playerNo;
    HuVecF pos;

    result = 0;
    doneF = 1;
    switch(lbl_1_bss_16CB4.mode) {
        case 0:
            fn_1_1AB8(lbl_1_bss_16CB4.mgTimer);
            lbl_1_bss_16CB4.mode++;
            break;

        case 1:
            for(i=0; i<2; i++) {
                if(lbl_1_bss_16A84[i].comF) {
                    fn_1_11F4C(i);
                }
                doneF *= fn_1_9654(i);
            }
            if(fn_1_1AE4(lbl_1_bss_16CB4.mgTimer)) {
                lbl_1_bss_16CB4.timeUpF = 1;
            }
            if(doneF) {
                lbl_1_bss_16A84[0].stopF = 1;
                lbl_1_bss_16A84[1].stopF = 1;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_16CB4.winner == 0) {
                fn_1_5C24(1, 100);
            }
            lbl_1_bss_16CB4.timer = 0;
            lbl_1_bss_16CB4.mode++;
            break;

        case 3:
            if(lbl_1_bss_16CB4.timer++ > 30) {
                if(lbl_1_bss_16CB4.winner == 0) {
                    fn_1_1B0C(lbl_1_bss_16CB4.mgTimer);
                }
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[81].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[82].modelId, HU3D_ATTR_DISPOFF);
                if(lbl_1_bss_16CB4.winner) {
                    MgSeqWinnerSet(lbl_1_bss_17A00->chr[lbl_1_bss_16CB4.winner&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                    playerNo = lbl_1_bss_17A00->chr[lbl_1_bss_16CB4.winner&1].no;
                    if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                        GwPlayer[playerNo].mgCoinBonus = 10;
                    }
                } else {
                    MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                }
                result = 1;
            }
            break;
    }
    fn_1_9360();
    for(i=0; i<2; i++) {
        if(lbl_1_bss_16A84[i].comF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], lbl_1_bss_16A84[i].stkX, lbl_1_bss_16A84[i].stkY, lbl_1_bss_16A84[i].btnDown, lbl_1_bss_16A84[i].btn);
        }
        if(lbl_1_bss_16A84[i].stopF) {
            MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
        }
    }
    fn_1_9934();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].oldPos.x = pos.x;
    lbl_1_bss_16A84[0].oldPos.y = pos.y;
    lbl_1_bss_16A84[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].oldPos.x = pos.x;
    lbl_1_bss_16A84[1].oldPos.y = pos.y;
    lbl_1_bss_16A84[1].oldPos.z = pos.z;
    MgActorExec();
    fn_1_115B0();
    for(i=0; i<2; i++) {
        if(lbl_1_bss_16A84[i].attrF || lbl_1_bss_16A84[i].hitF) {
            MgActorPosGet(lbl_1_bss_0.player[i]->actor, &pos);
            pos.x = lbl_1_bss_16A84[i].oldPos.x;
            pos.z = lbl_1_bss_16A84[i].oldPos.z;
            MgActorPosUpdate(lbl_1_bss_0.player[i]->actor, &pos);
        }
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].pos.x = pos.x;
    lbl_1_bss_16A84[0].pos.y = pos.y;
    lbl_1_bss_16A84[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].pos.x = pos.x;
    lbl_1_bss_16A84[1].pos.y = pos.y;
    lbl_1_bss_16A84[1].pos.z = pos.z;
    fn_1_153A8();
    pos.x = lbl_1_bss_16A84[0].pos.x;
    pos.y = lbl_1_bss_16A84[0].pos.y;
    pos.z = lbl_1_bss_16A84[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_16A84[1].pos.x;
    pos.y = lbl_1_bss_16A84[1].pos.y;
    pos.z = lbl_1_bss_16A84[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    for(i=0; i<2; i++) {
        Hu3DModelPosSet(lbl_1_bss_17A00->models[i+81].modelId, lbl_1_bss_16A84[i].pos.x, lbl_1_bss_16A84[i].pos.y, lbl_1_bss_16A84[i].pos.z);
    }
    return result;
}

/* asm 2783-2982, 195 insns. Finish hook. */
s16 fn_1_89B0(void)
{
    s16 result;
    int i;
    HuVecF pos;

    result = 0;
    lbl_1_bss_16CB4.mode = 0;
    lbl_1_bss_16CB4.unk02 = 0;
    lbl_1_bss_16CB4.unk04 = 0;
    lbl_1_bss_16CB4.timer = 0;
    if(lbl_1_bss_16CB4.winner) {
        fn_1_A758(lbl_1_bss_16CB4.winner&1);
    }
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].oldPos.x = pos.x;
    lbl_1_bss_16A84[0].oldPos.y = pos.y;
    lbl_1_bss_16A84[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].oldPos.x = pos.x;
    lbl_1_bss_16A84[1].oldPos.y = pos.y;
    lbl_1_bss_16A84[1].oldPos.z = pos.z;
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].pos.x = pos.x;
    lbl_1_bss_16A84[0].pos.y = pos.y;
    lbl_1_bss_16A84[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].pos.x = pos.x;
    lbl_1_bss_16A84[1].pos.y = pos.y;
    lbl_1_bss_16A84[1].pos.z = pos.z;
    fn_1_153A8();
    pos.x = lbl_1_bss_16A84[0].pos.x;
    pos.y = lbl_1_bss_16A84[0].pos.y;
    pos.z = lbl_1_bss_16A84[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_16A84[1].pos.x;
    pos.y = lbl_1_bss_16A84[1].pos.y;
    pos.z = lbl_1_bss_16A84[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    for(i=0; i<2; i++) {
        Hu3DModelPosSet(lbl_1_bss_17A00->models[i+81].modelId, lbl_1_bss_16A84[i].pos.x, lbl_1_bss_16A84[i].pos.y, lbl_1_bss_16A84[i].pos.z);
    }
    fn_1_9360();
    return result;
}

/* asm 2985-3012, 25 insns. Pre-winner hook. */
s16 fn_1_8CBC(void)
{
    s16 result;

    result = 0;
    if(lbl_1_bss_16CB4.winner) {
        fn_1_A758(lbl_1_bss_16CB4.winner&1);
    }
    result = fn_1_F814();
    fn_1_9360();
    return result;
}

/* asm 3015-3201, 181 insns. Winner hook: pose both duellists. */
s16 fn_1_8D20(void)
{
    DS_PLAYER *pl;
    HU3DMODEL *model;
    s16 result;

    model = &Hu3DData[lbl_1_bss_17A00->models[(lbl_1_bss_16CB4.winner&1)+81].modelId];
    result = 0;
    if(lbl_1_bss_17A00->mode[0] == 0) {
        if(lbl_1_bss_16CB4.winner != 0) {
            pl = &lbl_1_bss_17A00->player[lbl_1_bss_16CB4.winner&1];
            pl->motNo = 9;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_17A00->player[(lbl_1_bss_16CB4.winner&2)>>1];
            pl->motNo = 10;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        } else {
            pl = &lbl_1_bss_17A00->player[0];
            pl->motNo = 10;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            pl = &lbl_1_bss_17A00->player[1];
            pl->motNo = 10;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            CharLoseVoicePlay(lbl_1_bss_17A00->chr[0].charNo, lbl_1_bss_17A00->chr[1].charNo, CHARNO_NONE, CHARNO_NONE);
        }
        lbl_1_bss_17A00->mode[0] = 1;
        lbl_1_bss_16CB4.rotYEnd = model->rot.y;
    }
    fn_1_9360();
    if(lbl_1_bss_16CB4.winner != 0) {
        CharModelVoiceVolSet(lbl_1_bss_17A00->chr[lbl_1_bss_16CB4.winner&1].charNo, 127);
        CharModelVoicePanSet(lbl_1_bss_17A00->chr[lbl_1_bss_16CB4.winner&1].charNo, 64);
    }
    return result;
}

/* asm 3204-3217, 12 insns. */
s16 fn_1_8FF4(void)
{
    s16 result;

    result = 1;
    fn_1_9360();
    return result;
}

/* asm 3220-3250, 28 insns. Close hook. */
s16 fn_1_9024(void)
{
    s16 result;

    result = 1;
    fn_1_5FD4();
    MgActorKill(lbl_1_bss_0.player[0]->actor);
    MgActorKill(lbl_1_bss_0.player[1]->actor);
    if(lbl_1_bss_1679C.activeF) {
        fn_1_43CC();
    }
    return result;
}

/* asm 3253-3435, 179 insns. Push the model table, then the duellists' voice volume and pan. Unreferenced. */
void fn_1_9094(void)
{
    HU3DMODEL *modelA;
    HU3DMODEL *modelB;
    s16 i;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    modelA = &Hu3DData[lbl_1_bss_17A00->models[81].modelId];
    modelB = &Hu3DData[lbl_1_bss_17A00->models[82].modelId];
    for(i=0; i<81; i++) {
        Hu3DModelPosSet(lbl_1_bss_17A00->models[i].modelId, lbl_1_bss_17A00->models[i].pos.x, lbl_1_bss_17A00->models[i].pos.y, lbl_1_bss_17A00->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_17A00->models[i].modelId, lbl_1_bss_17A00->models[i].rot.x, lbl_1_bss_17A00->models[i].rot.y, lbl_1_bss_17A00->models[i].rot.z);
    }
    volF = 0.026956521f*modelA->pos.z;
    panF = 0.055652175f*modelA->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_17A00->chr[0].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_17A00->chr[0].charNo, pan);
    volF = 0.026956521f*modelB->pos.z;
    panF = 0.055652175f*modelB->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_17A00->chr[1].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_17A00->chr[1].charNo, pan);
}

/* asm 3438-3631, 189 insns. The per-frame push: models, voices, paper, camera, light and shadow. */
void fn_1_9360(void)
{
    HU3DMODEL *modelB;
    HU3DMODEL *modelA;
    s16 i;
    float panF;
    float volF;
    s16 vol;
    s16 pan;

    modelA = &Hu3DData[lbl_1_bss_17A00->models[81].modelId];
    modelB = &Hu3DData[lbl_1_bss_17A00->models[82].modelId];
    for(i=0; i<81; i++) {
        Hu3DModelPosSet(lbl_1_bss_17A00->models[i].modelId, lbl_1_bss_17A00->models[i].pos.x, lbl_1_bss_17A00->models[i].pos.y, lbl_1_bss_17A00->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_17A00->models[i].modelId, lbl_1_bss_17A00->models[i].rot.x, lbl_1_bss_17A00->models[i].rot.y, lbl_1_bss_17A00->models[i].rot.z);
    }
    volF = 0.026956521f*modelA->pos.z;
    panF = 0.055652175f*modelA->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_17A00->chr[0].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_17A00->chr[0].charNo, pan);
    volF = 0.026956521f*modelB->pos.z;
    panF = 0.055652175f*modelB->pos.x;
    vol = 111.0f+volF;
    pan = 64.0f+panF;
    CharModelVoiceVolSet(lbl_1_bss_17A00->chr[1].charNo, vol);
    CharModelVoicePanSet(lbl_1_bss_17A00->chr[1].charNo, pan);
    if(lbl_1_bss_1679C.activeF) {
        fn_1_4CB0();
    }
    fn_1_91C(0);
    fn_1_10C4();
    fn_1_14C4();
}

/* asm 3634-3828, 184 insns. One duellist's round: wait for a panel, run its effect, stop at the end. */
s16 fn_1_9654(s16 player)
{
    s16 result;

    result = 0;
    switch(lbl_1_bss_16A84[player].mode) {
        case 0:
            if(lbl_1_bss_16A84[player].hitF) {
                if(lbl_1_bss_16844[lbl_1_bss_16A84[player].panelNo].doneF) {
                    lbl_1_bss_16A84[player].mode++;
                }
            } else if(lbl_1_bss_16CB4.winner || lbl_1_bss_16CB4.timeUpF) {
                lbl_1_bss_16A84[player].stopF = 1;
                lbl_1_bss_16A84[player].mode = 2;
            }
            break;

        case 1:
            if(fn_1_A078(player, lbl_1_bss_16844[lbl_1_bss_16A84[player].panelNo].no)) {
                if(lbl_1_bss_16844[lbl_1_bss_16A84[player].panelNo].no) {
                    lbl_1_bss_16844[lbl_1_bss_16A84[player].panelNo].mode = 0;
                    lbl_1_bss_16844[lbl_1_bss_16A84[player].panelNo].doneF = 0;
                    lbl_1_bss_16A84[player].hitF = 0;
                    lbl_1_bss_16A84[player].panelNo = -1;
                }
                lbl_1_bss_16A84[player].mode = 0;
                if(lbl_1_bss_16CB4.winner || lbl_1_bss_16CB4.timeUpF) {
                    lbl_1_bss_16A84[player].stopF = 1;
                    lbl_1_bss_16A84[player].mode = 2;
                }
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 3831-4312, 465 insns. Move each panel toward the height its mode asks for. */
void fn_1_9934(void)
{
    s16 i;
    float diff;
    float dist;

    for(i=0; i<12; i++) {
        if((s16)lbl_1_bss_16844[i].mode != lbl_1_bss_16844[i].modeOld) {
            switch(lbl_1_bss_16844[i].mode) {
                case 0:
                    lbl_1_bss_16844[i].destY = 100.1f;
                    lbl_1_bss_16844[i].speedY = 1.8f;
                    break;

                case 1:
                    lbl_1_bss_16844[i].destY = 96.5f;
                    if(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y >= 96.5f) {
                        lbl_1_bss_16844[i].speedY = -1.8f;
                    } else {
                        lbl_1_bss_16844[i].speedY = 1.8f;
                    }
                    break;

                case 2:
                    lbl_1_bss_16844[i].destY = 82.1f;
                    lbl_1_bss_16844[i].speedY = -1.8f;
                    Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 1.5f);
                    Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                    break;
            }
            lbl_1_bss_16844[i].moveF = 1;
            lbl_1_bss_16844[i].modeOld = lbl_1_bss_16844[i].mode;
            lbl_1_bss_16844[i].unk06 = 0;
        }
        if(lbl_1_bss_16844[i].moveF) {
            if(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y-lbl_1_bss_16844[i].destY > 0.0f) {
                diff = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y-lbl_1_bss_16844[i].destY;
            } else {
                diff = -1.0f*(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y-lbl_1_bss_16844[i].destY);
            }
            dist = diff;
            lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y += lbl_1_bss_16844[i].speedY;
            lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].pos.y += lbl_1_bss_16844[i].speedY;
            lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.y += lbl_1_bss_16844[i].speedY;
            if(dist <= 2.0f) {
                lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[1]].pos.y = lbl_1_bss_16844[i].destY;
                lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].pos.y = lbl_1_bss_16844[i].destY;
                lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.y = lbl_1_bss_16844[i].destY;
                lbl_1_bss_16844[i].moveF = 0;
                lbl_1_bss_16844[i].doneF = 1;
            }
        }
    }
    for(i=0; i<12; i++) {
        if(lbl_1_bss_16844[i].mode == 1) {
            lbl_1_bss_16844[i].mode = 0;
        }
    }
}

/* asm 4315-4660, 331 insns. A duellist has landed on a panel: stop, sink, then run the panel's effect. */
s16 fn_1_A078(s16 player, s16 no)
{
    s16 result = 0;
    s16 argTbl[2][5] = {
        { 0, 54, 0, 58, 62 },
        { 0, 55, 0, 60, 67 }
    };
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    switch(lbl_1_bss_16A84[player].hitMode) {
        case 0:
            lbl_1_bss_16A84[player].stopF = 1;
            lbl_1_bss_16A84[player].panelHit[lbl_1_bss_16A84[player].panelNo]++;
            if(no == 0) {
                volF = 0.026956521f*lbl_1_bss_17A00->models[player+81].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[player+81].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(7, vol, pan);
            }
            lbl_1_bss_16A84[player].hitMode++;
            break;

        case 1:
            if(lbl_1_bss_0.player[player]->mode == 0) {
                if(no == 0) {
                    fn_1_5C24(1, 1000);
                }
                lbl_1_bss_16A84[player].hitMode++;
            }
            break;

        case 2:
            lbl_1_bss_0.player[player]->actor->gravity = 0.0f;
            lbl_1_bss_16A84[player].hitMode++;
            break;

        case 3:
            if(lbl_1_bss_16A84[player].hitTimer++ > 20) {
                if(no != 0) {
                    Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].hitMode++;
            }
            if(no == 0) {
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].hitMode++;
            }
            break;

        case 4:
            if(lbl_1_data_5B0[no](player, argTbl[player][no])) {
                if(no != 0) {
                    lbl_1_bss_0.player[player]->actor->gravity = lbl_1_bss_16A84[player].gravity;
                    MgPlayerAttrReset(lbl_1_bss_0.player[player], MGPLAYER_ATTR_STUNOFF);
                    MgPlayerAttrReset(lbl_1_bss_0.player[player^1], MGPLAYER_ATTR_HEADJUMP_OFF);
                }
                lbl_1_bss_16A84[player].hitMode++;
            }
            break;

        case 5:
            lbl_1_bss_16A84[player].stopF = 0;
            lbl_1_bss_16A84[player].hitMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* asm 4663-4776, 109 insns. Panel kind 0, the win: rain paper over the centre and declare the winner. */
s16 fn_1_A5A4(s16 player, s16 arg)
{
    s16 result;
    HuVecF *posP;
    HuVecF tmp;
    HuVecF pos;

    result = 0;
    switch(lbl_1_bss_16A84[player].effMode) {
        case 0:
            tmp.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.x;
            tmp.y = 1000.0f;
            tmp.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.z;
            pos = tmp;
            posP = &pos;
            fn_1_41C8(lbl_1_bss_17A00, 72, posP);
            lbl_1_bss_16A84[player].effMode++;
            break;

        case 1:
            lbl_1_bss_16A84[player].hitTimer = 0;
            lbl_1_bss_16A84[player].effMode = 0;
            lbl_1_bss_16CB4.winner = player|((player^1)<<1);
            result = 1;
            break;
    }
    return result;
}

/* asm 4779-5196, 403 insns. The winner's spotlight: dim the light and the stage, fade in the beams. */
s16 fn_1_A758(s16 player)
{
    HuVecF pos;
    s16 result;
    s16 i;
    int time;
    s16 step;
    float speed;
    float tpSpeed;
    s16 doneNum;

    result = 0;
    doneNum = 0;
    switch(lbl_1_bss_16A84[player].fadeMode) {
        case 0:
            pos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.x;
            pos.y = 0.0f;
            pos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.z;
            for(i=76; i<=78; i++) {
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[i].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[i].modelId, 1.0f);
                lbl_1_bss_17A00->models[i].pos.x = pos.x;
                lbl_1_bss_17A00->models[i].pos.y = pos.y;
                lbl_1_bss_17A00->models[i].pos.z = pos.z;
            }
            Hu3DModelAttrReset(lbl_1_bss_17A00->models[79].modelId, HU3D_ATTR_DISPOFF);
            lbl_1_bss_17A00->models[79].pos.x = pos.x;
            lbl_1_bss_17A00->models[79].pos.y = pos.y;
            lbl_1_bss_17A00->models[79].pos.z = pos.z;
            fn_1_1B0C(lbl_1_bss_16CB4.mgTimer);
            lbl_1_bss_16CB4.modelAmb = 1.0f;
            lbl_1_bss_16A84[player].fadeMode++;

        case 1:
            time = 60;
            step = 200/time;
            if((lbl_1_bss_34->color.r -= step) <= 55) {
                lbl_1_bss_34->color.r = 55;
                doneNum++;
            }
            if((lbl_1_bss_34->color.g -= step) <= 55) {
                lbl_1_bss_34->color.g = 55;
                doneNum++;
            }
            if((lbl_1_bss_34->color.b -= step) <= 55) {
                lbl_1_bss_34->color.b = 55;
                doneNum++;
            }
            if((lbl_1_bss_34->color.a -= step) <= 55) {
                lbl_1_bss_34->color.a = 55;
                doneNum++;
            }
            speed = 0.3f/time;
            lbl_1_bss_16CB4.modelAmb += 2.0f*speed;
            if((lbl_1_bss_16CB4.ambColor -= speed) <= 0.7f) {
                lbl_1_bss_16CB4.modelAmb -= 2.0f*speed;
                lbl_1_bss_16CB4.ambColor = 0.7f;
                doneNum++;
            }
            Hu3DModelAmbSet(lbl_1_bss_17A00->models[player+81].modelId, lbl_1_bss_16CB4.modelAmb, lbl_1_bss_16CB4.modelAmb, lbl_1_bss_16CB4.modelAmb);
            Hu3DAmbColorSet(lbl_1_bss_16CB4.ambColor, lbl_1_bss_16CB4.ambColor, lbl_1_bss_16CB4.ambColor);
            tpSpeed = 1.0f/(time*2);
            if((lbl_1_bss_16CB4.tpLvl += tpSpeed) >= 1.0f) {
                lbl_1_bss_16CB4.tpLvl = 1.0f;
                doneNum++;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[76].modelId, lbl_1_bss_16CB4.tpLvl);
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[77].modelId, lbl_1_bss_16CB4.tpLvl);
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[78].modelId, lbl_1_bss_16CB4.tpLvl);
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[79].modelId, lbl_1_bss_16CB4.tpLvl);
            if(doneNum >= 6) {
                lbl_1_bss_16A84[player].fadeMode++;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].fadeMode++;
            break;
    }
    return result;
}

/* asm 5199-5705, 495 insns. Panel kind 1: a weight drops on the duellist, who staggers off. */
s16 fn_1_ADA4(s16 player, s16 mdlNo)
{
    HU3DMODEL *model;
    DS_PLAYER *pl;
    s16 result;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    model = &Hu3DData[lbl_1_bss_17A00->models[player+81].modelId];
    pl = &lbl_1_bss_17A00->player[player];
    result = 0;
    switch(lbl_1_bss_16A84[player].effMode) {
        case 0:
            lbl_1_bss_17A00->models[mdlNo].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo].pos.y = 1200.0f;
            lbl_1_bss_17A00->models[mdlNo].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            lbl_1_bss_16A84[player].tpLvl = 1.0f;
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[mdlNo].modelId, lbl_1_bss_16A84[player].tpLvl);
            Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_16A84[player].velY = -40.0f;
            lbl_1_bss_16A84[player].effMode++;
            break;

        case 1:
            if(pl->endF) {
                volF = 0.026956521f*lbl_1_bss_17A00->models[mdlNo].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[mdlNo].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(3, vol, pan);
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 2:
            lbl_1_bss_17A00->models[mdlNo].pos.y += lbl_1_bss_16A84[player].velY;
            if(lbl_1_bss_17A00->models[mdlNo].pos.y <= 100.0f) {
                lbl_1_bss_17A00->models[mdlNo].pos.y = 100.0f;
                fn_1_29DC(&lbl_1_bss_17A00->models[mdlNo].pos);
                model->pos.y += 1.0f;
                pl->motNo = 11;
                pl->speed = 0.0f;
                pl->time = 10.0f;
                pl->attr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                omVibrate(lbl_1_bss_17A00->chr[player].no, 20, 12, 0);
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 3:
            if(lbl_1_bss_16A84[player].hitTimer++ > 30) {
                fn_1_3270(&lbl_1_bss_17A00->models[mdlNo].pos);
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 4:
            if(lbl_1_bss_16A84[player].hitTimer++ > 5) {
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 5:
            if((lbl_1_bss_16A84[player].tpLvl -= 0.05f) <= 0.0f) {
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_16A84[player].tpLvl = 1.0f;
                lbl_1_bss_16A84[player].effMode++;
                pl->speed = 2.0f;
            }
            Hu3DModelTPLvlSet(lbl_1_bss_17A00->models[mdlNo].modelId, lbl_1_bss_16A84[player].tpLvl);
            break;

        case 6:
            if(pl->endF) {
                model->pos.y -= 1.0f;
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 7:
            if(pl->shiftMode == 3) {
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_16A84[player].effMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 5708-6286, 570 insns. Panel kind 2: a spring launches the duellist up and back down. */
s16 fn_1_B560(s16 player, s16 arg)
{
    HuVecF pos;
    DS_PLAYER *pl;
    s16 result;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    pl = &lbl_1_bss_17A00->player[player];
    result = 0;
    MgActorPosGet(lbl_1_bss_0.player[player]->actor, &pos);
    lbl_1_bss_16A84[player].pos.x = pos.x;
    lbl_1_bss_16A84[player].pos.y = pos.y;
    lbl_1_bss_16A84[player].pos.z = pos.z;
    switch(lbl_1_bss_16A84[player].effMode) {
        case 0:
            pl->shiftMode = 1;
            pl->shiftMotNo = 8;
            pl->shiftTime = 0.0f;
            pl->shiftSpeed = 8.0f;
            pl->shiftAttr = HU3D_MOTATTR_LOOP;
            pl->attrReset = 0;
            Hu3DModelAttrReset(lbl_1_bss_17A00->models[player+56].modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[player+56].modelId, 1.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[player+56].modelId, 0.0f);
            lbl_1_bss_17A00->models[player+56].pos = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[1]].pos;
            Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[1]].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
            lbl_1_bss_16A84[player].velY = 44.72f;
            omVibrate(lbl_1_bss_17A00->chr[player].no, 20, 12, 0);
            volF = 0.026956521f*lbl_1_bss_17A00->models[player+56].pos.z;
            panF = 0.055652175f*lbl_1_bss_17A00->models[player+56].pos.x;
            vol = 111.0f+volF;
            pan = 64.0f+panF;
            fn_1_5D64(4, vol, pan);
            lbl_1_bss_16A84[player].effMode++;
            break;

        case 1:
            lbl_1_bss_16A84[player].pos.y += lbl_1_bss_16A84[player].velY;
            lbl_1_bss_16A84[player].velY -= 1.0f;
            if(lbl_1_bss_16A84[player].velY <= 0.0f) {
                lbl_1_bss_16A84[player].velY = 0.0f;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].pos.y += lbl_1_bss_16A84[player].velY;
            lbl_1_bss_16A84[player].velY -= 1.0f;
            if(lbl_1_bss_16A84[player].pos.y <= 125.0f) {
                pl->shiftMode = 1;
                pl->shiftMotNo = 5;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_16A84[player].pos.y = 125.0f;
                omVibrate(lbl_1_bss_17A00->chr[player].no, 20, 12, 0);
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 3:
            if(pl->shiftMode == 3) {
                pl->motNo = 4;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = 0;
                pl->attrReset = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 4:
            if(pl->endF) {
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_16A84[player].effMode = 0;
                lbl_1_bss_16A84[player].hitTimer = 0;
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[player+56].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[player+56].modelId, 0.0f);
                Hu3DMotionTimeSet(lbl_1_bss_17A00->models[player+56].modelId, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[1]].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].panelNo].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                result = 1;
            }
            break;
    }
    pos.x = lbl_1_bss_16A84[player].pos.x;
    pos.y = lbl_1_bss_16A84[player].pos.y;
    pos.z = lbl_1_bss_16A84[player].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[player]->actor, &pos);
    return result;
}

/* asm 6289-6825, 526 insns. Panel kind 3: the duellist is caught in a blast and flashes. */
s16 fn_1_BE48(s16 player, s16 mdlNo)
{
    HuVecF pos;
    DS_PLAYER *pl;
    s16 result;
    float speedA;
    float speedB;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    pl = &lbl_1_bss_17A00->player[player];
    result = 0;
    speedA = 4.0f;
    speedB = 4.0f;
    switch(lbl_1_bss_16A84[player].effMode) {
        case 0:
            pl->motNo = 7;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_16A84[player].effMode++;
            break;

        case 1:
            if(pl->time >= 10.0f) {
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo].modelId, speedA);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo].modelId, 0.0f);
                Hu3DModelObjPosGet(lbl_1_bss_17A00->models[player+81].modelId, lbl_1_bss_16A84[player].itemHook, &pos);
                lbl_1_bss_17A00->models[mdlNo].pos.x = pos.x;
                lbl_1_bss_17A00->models[mdlNo].pos.y = pos.y;
                lbl_1_bss_17A00->models[mdlNo].pos.z = pos.z-50.0f;
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, speedB);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, 0.0f);
                lbl_1_bss_17A00->models[mdlNo+1].pos.x = pos.x;
                lbl_1_bss_17A00->models[mdlNo+1].pos.y = pos.y;
                lbl_1_bss_17A00->models[mdlNo+1].pos.z = pos.z-20.0f;
                omVibrate(lbl_1_bss_17A00->chr[player].no, 70, 12, 0);
                volF = 0.026956521f*lbl_1_bss_17A00->models[player+56].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[player+56].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(5, vol, pan);
                lbl_1_bss_16A84[player].unk03E = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 2:
            Hu3DModelObjPosGet(lbl_1_bss_17A00->models[player+81].modelId, lbl_1_bss_16A84[player].itemHook, &pos);
            lbl_1_bss_17A00->models[mdlNo].pos.x = pos.x;
            lbl_1_bss_17A00->models[mdlNo].pos.y = pos.y;
            lbl_1_bss_17A00->models[mdlNo].pos.z = pos.z-50.0f;
            lbl_1_bss_17A00->models[mdlNo+1].pos.x = pos.x;
            lbl_1_bss_17A00->models[mdlNo+1].pos.y = pos.y;
            lbl_1_bss_17A00->models[mdlNo+1].pos.z = pos.z-50.0f;
            if(lbl_1_bss_16A84[player].hitTimer++ == 0) {
                fn_1_5958(player, 0.25f);
            } else if(lbl_1_bss_16A84[player].hitTimer > 3) {
                if(lbl_1_bss_16A84[player].hitTimer <= 6) {
                    fn_1_5AC8(player);
                } else {
                    lbl_1_bss_16A84[player].unk03E = 0;
                    lbl_1_bss_16A84[player].hitTimer = 0;
                }
            }
            if(pl->time >= 80.0f) {
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_ATTR_DISPOFF);
                fn_1_5AC8(player);
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 3:
            if(pl->endF) {
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].effMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 6828-7875, 1032 insns. Panel kind 4: a chain of five effect models over the duellist. */
s16 fn_1_C680(s16 player, s16 mdlNo)
{
    DS_PLAYER *pl;
    float speedA;
    float speedB;
    s16 result;
    float time;
    s16 timeI;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    pl = &lbl_1_bss_17A00->player[player];
    speedA = 2.5f;
    speedB = 1.25f;
    result = 0;
    switch(lbl_1_bss_16A84[player].effMode) {
        case 0:
            lbl_1_bss_17A00->models[mdlNo+2].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo+2].pos.y = 25.0f+(100.0f+lbl_1_bss_16A84[player].height);
            lbl_1_bss_17A00->models[mdlNo+2].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            lbl_1_bss_17A00->models[mdlNo+3].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo+3].pos.y = 25.0f+(100.0f+lbl_1_bss_16A84[player].height);
            lbl_1_bss_17A00->models[mdlNo+3].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            lbl_1_bss_17A00->models[mdlNo+4].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo+4].pos.y = 25.0f+(100.0f+lbl_1_bss_16A84[player].height);
            lbl_1_bss_17A00->models[mdlNo+4].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            lbl_1_bss_17A00->models[mdlNo].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo].pos.y = 25.0f+(100.0f+lbl_1_bss_16A84[player].height);
            lbl_1_bss_17A00->models[mdlNo].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            lbl_1_bss_17A00->models[mdlNo+1].pos.x = lbl_1_bss_0.player[player]->actor->pos.x;
            lbl_1_bss_17A00->models[mdlNo+1].pos.y = 25.0f+(100.0f+lbl_1_bss_16A84[player].height);
            lbl_1_bss_17A00->models[mdlNo+1].pos.z = lbl_1_bss_0.player[player]->actor->pos.z;
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+2].modelId, speedA);
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+3].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+4].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo+2].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo+3].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo+4].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, 75.0f);
            Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo+2].modelId, HU3D_ATTR_DISPOFF);
            pl->motNo = 6;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_16A84[player].effMode++;
            break;

        case 1:
            if(pl->endF) {
                lbl_1_bss_16A84[player].effMode++;
                omVibrate(lbl_1_bss_17A00->chr[player].no, 120, 6, 6);
                volF = 0.026956521f*lbl_1_bss_17A00->models[player+56].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[player+56].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(6, vol, pan);
            }
            break;

        case 2:
            if(Hu3DMotionTimeGet(lbl_1_bss_17A00->models[mdlNo+2].modelId) >= 80.0f && lbl_1_bss_16A84[player].motF == 0) {
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo].modelId, speedB);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                lbl_1_bss_16A84[player].motF = 1;
            }
            if(Hu3DMotionEndCheck(lbl_1_bss_17A00->models[mdlNo+2].modelId)) {
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+2].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+3].modelId, speedA);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo+3].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_16A84[player].motF = 0;
                lbl_1_bss_16A84[player].unk03E = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 3:
            fn_1_5958(player, 0.983f);
            if(Hu3DMotionTimeGet(lbl_1_bss_17A00->models[mdlNo].modelId) >= 13.0f && lbl_1_bss_16A84[player].motF == 0) {
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, speedB);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_MOTATTR_LOOP);
                lbl_1_bss_16A84[player].motF = 1;
            }
            if(Hu3DMotionEndCheck(lbl_1_bss_17A00->models[mdlNo+3].modelId)) {
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+3].modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[mdlNo+4].modelId, speedA);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[mdlNo+4].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_16A84[player].unk03E = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 4:
            fn_1_5958(player, 0.983f);
            time = Hu3DMotionTimeGet(lbl_1_bss_17A00->models[mdlNo+4].modelId);
            if(time >= 50.0f) {
                timeI = Hu3DMotionTimeGet(lbl_1_bss_17A00->models[mdlNo].modelId);
                if(timeI%25 >= 24 || timeI%25 <= 1) {
                    Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                }
                timeI = Hu3DMotionTimeGet(lbl_1_bss_17A00->models[mdlNo+1].modelId);
                if(timeI%25 >= 24 || timeI%25 <= 1) {
                    Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_ATTR_DISPOFF);
                }
            }
            if(Hu3DMotionEndCheck(lbl_1_bss_17A00->models[mdlNo+4].modelId)) {
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+4].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17A00->models[mdlNo+1].modelId, HU3D_ATTR_DISPOFF);
                pl->shiftMode = 1;
                pl->shiftMotNo = 0;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 8.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].effMode++;
            }
            break;

        case 5:
            if(pl->shiftMode == 3) {
                pl->motNo = 0;
                pl->speed = 1.0f;
                pl->time = 0.0f;
                pl->attr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
                fn_1_5AC8(player);
                lbl_1_bss_16A84[player].hitTimer = 0;
                lbl_1_bss_16A84[player].motF = 0;
                lbl_1_bss_16A84[player].effMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 7878-8979, 1062 insns. Walk one duellist to its start mark and turn it to face the panels. */
s16 fn_1_D6A0(s16 player)
{
    DS_PLAYER *pl;
    s16 result;
    s16 doneF;
    float speed;
    float mag;
    float x;
    float z;
    s16 angle;
    s16 negF;
    float div;

    pl = &lbl_1_bss_17A00->player[player];
    result = 0;
    doneF = 0;
    speed = 7.0f;
    switch(lbl_1_bss_16CB4.walkMode[player]) {
        case 0:
            lbl_1_bss_16A84[player].chasePos.x = -200.0f+400.0f*player;
            lbl_1_bss_16A84[player].chasePos.z = 0.0f;
            lbl_1_bss_16A84[player].vel.x = lbl_1_bss_16A84[player].chasePos.x-lbl_1_bss_16A84[player].pos.x;
            lbl_1_bss_16A84[player].vel.z = lbl_1_bss_16A84[player].chasePos.z-lbl_1_bss_16A84[player].pos.z;
            mag = sqrt(lbl_1_bss_16A84[player].vel.x*lbl_1_bss_16A84[player].vel.x+lbl_1_bss_16A84[player].vel.z*lbl_1_bss_16A84[player].vel.z);
            if(mag) {
                lbl_1_bss_16CB4.walkMotF[player] = 1;
                pl->shiftMode = 1;
                pl->shiftMotNo = 1;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 4.0f;
                pl->shiftAttr = HU3D_MOTATTR_LOOP;
                pl->attrReset = 0;
            }
            lbl_1_bss_16CB4.walkStage = 1;
            lbl_1_bss_16CB4.walkMode[player]++;

        case 1:
            lbl_1_bss_16A84[player].vel.x = lbl_1_bss_16A84[player].chasePos.x-lbl_1_bss_16A84[player].pos.x;
            lbl_1_bss_16A84[player].vel.z = lbl_1_bss_16A84[player].chasePos.z-lbl_1_bss_16A84[player].pos.z;
            mag = sqrt(lbl_1_bss_16A84[player].vel.x*lbl_1_bss_16A84[player].vel.x+lbl_1_bss_16A84[player].vel.z*lbl_1_bss_16A84[player].vel.z);
            if(mag) {
                mag = speed/mag;
                lbl_1_bss_16A84[player].vel.x *= mag;
                lbl_1_bss_16A84[player].vel.z *= mag;
                if(lbl_1_bss_16CB4.walkTimer >= 30) {
                    if(player == 0) {
                        lbl_1_bss_16A84[player].vel.z += 3.0f;
                    } else {
                        lbl_1_bss_16A84[player].vel.z -= 3.0f;
                    }
                    mag = sqrt(lbl_1_bss_16A84[player].vel.x*lbl_1_bss_16A84[player].vel.x+lbl_1_bss_16A84[player].vel.z*lbl_1_bss_16A84[player].vel.z);
                    if(mag) {
                        mag = speed/mag;
                    } else {
                        mag = 0.0f;
                    }
                    lbl_1_bss_16A84[player].vel.x *= mag;
                    lbl_1_bss_16A84[player].vel.z *= mag;
                }
                x = 180.0*(acos(lbl_1_bss_16A84[player].vel.x/(0.1f+speed))/M_PI);
                z = 180.0*(asin(lbl_1_bss_16A84[player].vel.z/(0.1f+speed))/M_PI);
                if(z < 0.0f) {
                    x = 360.0f-x;
                }
                lbl_1_bss_16A84[player].rotY = 90.0f+(-x);
                if(lbl_1_bss_16CB4.walkTimer >= 180 && player == 0) {
                    lbl_1_bss_16A84[player].vel.x = 0.0f;
                    lbl_1_bss_16A84[player].vel.z = 0.0f;
                }
                lbl_1_bss_16A84[player].pos.x += lbl_1_bss_16A84[player].vel.x;
                lbl_1_bss_16A84[player].pos.z += lbl_1_bss_16A84[player].vel.z;
                lbl_1_bss_0.player[player]->actor->rotY = lbl_1_bss_16A84[player].rotY;
                x = lbl_1_bss_16A84[player].chasePos.x-lbl_1_bss_16A84[player].pos.x;
                z = lbl_1_bss_16A84[player].chasePos.z-lbl_1_bss_16A84[player].pos.z;
                mag = sqrt(x*x+z*z);
            }
            if(mag < 2.0f+speed) {
                lbl_1_bss_16A84[player].rotY = lbl_1_bss_0.player[player]->actor->rotY;
                angle = lbl_1_bss_0.player[player]->actor->rotY;
                angle = angle%360;
                if(angle != 0) {
                    if(angle < 0) {
                        angle = angle*-1;
                        negF = 1;
                    } else {
                        negF = 0;
                    }
                    if(angle > 180) {
                        angle = 360-angle;
                    } else {
                        angle = angle*-1;
                    }
                    if(negF) {
                        angle = angle*-1;
                    }
                }
                lbl_1_bss_16CB4.walkRotY[player] = lbl_1_bss_0.player[player]->actor->rotY+angle;
                if(player == 0) {
                    lbl_1_bss_16CB4.walkStage = 2;
                }
                lbl_1_bss_16CB4.walkMode[player]++;
            }
            break;

        case 2:
            div = 30.0f;
            doneF = fn_1_1850(&lbl_1_bss_0.player[player]->actor->rotY, div, lbl_1_bss_16A84[player].rotY, lbl_1_bss_16CB4.walkRotY[player]);
            if(doneF == 0) {
                if(lbl_1_bss_16CB4.walkMotF[player]) {
                    pl->shiftMode = 1;
                    pl->shiftMotNo = 0;
                    pl->shiftTime = 0.0f;
                    pl->shiftSpeed = 4.0f;
                    pl->shiftAttr = HU3D_MOTATTR_LOOP;
                    pl->attrReset = 0;
                }
                lbl_1_bss_16CB4.walkMode[player]++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/* asm 8982-9202, 213 insns. Step both walks, with the actors holding still. */
s16 fn_1_E738(void)
{
    s16 result;
    s16 doneNum;
    s16 i;
    HuVecF pos;

    result = 0;
    doneNum = 0;
    MgPlayerPadSet(lbl_1_bss_0.player[0], 0, 0, 0, 0);
    MgPlayerPadSet(lbl_1_bss_0.player[1], 0, 0, 0, 0);
    fn_1_9934();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].oldPos.x = pos.x;
    lbl_1_bss_16A84[0].oldPos.y = pos.y;
    lbl_1_bss_16A84[0].oldPos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].oldPos.x = pos.x;
    lbl_1_bss_16A84[1].oldPos.y = pos.y;
    lbl_1_bss_16A84[1].oldPos.z = pos.z;
    MgActorExec();
    MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
    lbl_1_bss_16A84[0].pos.x = pos.x;
    lbl_1_bss_16A84[0].pos.y = pos.y;
    lbl_1_bss_16A84[0].pos.z = pos.z;
    MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
    lbl_1_bss_16A84[1].pos.x = pos.x;
    lbl_1_bss_16A84[1].pos.y = pos.y;
    lbl_1_bss_16A84[1].pos.z = pos.z;
    for(i=0; i<2; i++) {
        doneNum += fn_1_D6A0(i);
        if(lbl_1_bss_16CB4.walkMode[i] >= 2) {
            lbl_1_bss_16A84[i].pos = lbl_1_bss_16A84[i].oldPos;
        }
    }
    if(doneNum >= 2) {
        result = 1;
    }
    fn_1_153A8();
    pos.x = lbl_1_bss_16A84[0].pos.x;
    pos.y = lbl_1_bss_16A84[0].pos.y;
    pos.z = lbl_1_bss_16A84[0].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
    pos.x = lbl_1_bss_16A84[1].pos.x;
    pos.y = lbl_1_bss_16A84[1].pos.y;
    pos.z = lbl_1_bss_16A84[1].pos.z;
    MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
    for(i=0; i<2; i++) {
        Hu3DModelPosSet(lbl_1_bss_17A00->models[i+81].modelId, lbl_1_bss_16A84[i].pos.x, lbl_1_bss_16A84[i].pos.y, lbl_1_bss_16A84[i].pos.z);
    }
    return result;
}

/* asm 9205-10095, 866 insns. Fade-in: raise the stage, swing the camera in, spin the panel roulette. */
int fn_1_EA8C(void)
{
    int result = 0;
    s16 doneNum = 0;
    float riseTbl[6][3] = {
        { 74.0f, 100.0f, 5.0f },
        { 100.0f, 85.0f, 5.0f },
        { 85.0f, 100.0f, 5.0f },
        { 100.0f, 95.0f, 5.0f },
        { 95.0f, 100.0f, 5.0f },
        { -1.0f, 0.0f, 0.0f }
    };
    s16 i;
    float speed;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    switch(lbl_1_bss_16CB4.mode) {
        case 0:
            fn_1_5BF4();
            lbl_1_bss_16CB4.mode++;

        case 1:
            if(lbl_1_bss_16CB4.timer++ > 30) {
                for(i=0; i<12; i++) {
                    Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                    Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                }
                volF = 0.026956521f*lbl_1_bss_17A00->models[43].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[43].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(1, vol, pan);
                lbl_1_bss_16CB4.timer = 0;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 2:
            doneNum = fn_1_1850(&lbl_1_bss_17A00->models[43].pos.y, riseTbl[lbl_1_bss_16CB4.unk02][2], riseTbl[lbl_1_bss_16CB4.unk02][0], riseTbl[lbl_1_bss_16CB4.unk02][1]);
            if(doneNum == 0) {
                lbl_1_bss_16CB4.unk02++;
                if(riseTbl[lbl_1_bss_16CB4.unk02][0] < 0.0f) {
                    lbl_1_bss_16CB4.unk02 = 0;
                    lbl_1_bss_16CB4.mode++;
                }
            }
            break;

        case 3:
            if(lbl_1_bss_16CB4.timer++ > 30) {
                lbl_1_bss_16CB4.timer = 0;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 4:
            speed = 30.0f;
            doneNum += fn_1_1850(&lbl_1_bss_38->center.x, speed, lbl_1_data_368[0].center.x, lbl_1_data_368[1].center.x);
            doneNum += fn_1_1850(&lbl_1_bss_38->center.y, speed, lbl_1_data_368[0].center.y, lbl_1_data_368[1].center.y);
            doneNum += fn_1_1850(&lbl_1_bss_38->center.z, speed, lbl_1_data_368[0].center.z, lbl_1_data_368[1].center.z);
            doneNum += fn_1_1850(&lbl_1_bss_38->rot.x, speed, lbl_1_data_368[0].rot.x, lbl_1_data_368[1].rot.x);
            doneNum += fn_1_1850(&lbl_1_bss_38->rot.y, speed, lbl_1_data_368[0].rot.y, lbl_1_data_368[1].rot.y);
            doneNum += fn_1_1850(&lbl_1_bss_38->zoom, speed, lbl_1_data_368[0].zoom, lbl_1_data_368[1].zoom);
            if(doneNum == 0) {
                lbl_1_bss_16CB4.unk02 = frandmod(3);
                if(lbl_1_bss_16CB4.unk02 != 2) {
                    lbl_1_bss_16CB4.spinStart = lbl_1_bss_16CB4.spinPanel = frandmod(12);
                } else {
                    lbl_1_bss_16CB4.spinPanel = lbl_1_bss_16CB4.panelKind[0];
                    lbl_1_bss_16CB4.spinStart = -1;
                    lbl_1_bss_16CB4.spinIdx = 0;
                }
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, 2.0f);
                Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, 0.0f);
                volF = 0.026956521f*lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(2, vol, pan);
                lbl_1_bss_16CB4.spinCnt = 1;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 5:
            if(lbl_1_bss_16CB4.timer++ > 5) {
                if(lbl_1_bss_16CB4.unk02 == 0) {
                    if(++lbl_1_bss_16CB4.spinPanel > 11) {
                        lbl_1_bss_16CB4.spinPanel = 0;
                    }
                } else if(lbl_1_bss_16CB4.unk02 == 1) {
                    if(--lbl_1_bss_16CB4.spinPanel < 0) {
                        lbl_1_bss_16CB4.spinPanel = 11;
                    }
                } else {
                    lbl_1_bss_16CB4.spinIdx++;
                    if(lbl_1_bss_16CB4.spinIdx < 12) {
                        lbl_1_bss_16CB4.spinPanel = lbl_1_bss_16CB4.panelKind[lbl_1_bss_16CB4.spinIdx];
                    } else {
                        lbl_1_bss_16CB4.spinPanel = 0;
                        lbl_1_bss_16CB4.spinStart = 0;
                    }
                }
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, 2.0f);
                Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].modelId, 0.0f);
                volF = 0.026956521f*lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].pos.z;
                panF = 0.055652175f*lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.spinPanel].mdlNo[2]].pos.x;
                vol = 111.0f+volF;
                pan = 64.0f+panF;
                fn_1_5D64(2, vol, pan);
                lbl_1_bss_16CB4.timer = 0;
                if(++lbl_1_bss_16CB4.spinCnt >= 12) {
                    lbl_1_bss_16CB4.mode++;
                }
            }
            break;

        case 6:
            if(lbl_1_bss_16CB4.timer++ > 50) {
                for(i=0; i<12; i++) {
                    Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 2.0f);
                    Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                }
                fn_1_5CEC(2);
                lbl_1_bss_16CB4.timer = 0;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 7:
            if(lbl_1_bss_16CB4.timer++ > 50) {
                for(i=0; i<12; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionSpeedSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                    Hu3DMotionTimeSet(lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[2]].modelId, 0.0f);
                }
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 8:
            result = 1;
            break;
    }
    return result;
}

/*
 * asm 10098-12056, 1895 insns. Pre-winner: the winner walks to the centre
 * panel and turns to face the camera, the loser runs out of its way, and the
 * camera closes in.
 */
int fn_1_F814(void)
{
    HU3DMODEL *winModel;
    HU3DMODEL *loseModel;
    DS_PLAYER *winPl;
    DS_PLAYER *losePl;
    int result;
    s16 moveNum;
    s16 doneF;
    s16 winNo;
    s16 loseNo;
    s16 negF;
    s16 i;
    s16 angle;
    float x;
    float z;
    float dist;
    float speed;
    HuVecF pos;

    winModel = &Hu3DData[lbl_1_bss_17A00->models[(lbl_1_bss_16CB4.winner&1)+81].modelId];
    loseModel = &Hu3DData[lbl_1_bss_17A00->models[(lbl_1_bss_16CB4.winner>>1)+81].modelId];
    winPl = &lbl_1_bss_17A00->player[lbl_1_bss_16CB4.winner&1];
    losePl = &lbl_1_bss_17A00->player[(lbl_1_bss_16CB4.winner&1)^1];
    result = 0;
    moveNum = 0;
    doneF = 0;
    winNo = lbl_1_bss_16CB4.winner&1;
    loseNo = lbl_1_bss_16CB4.winner>>1;
    negF = 0;
    switch(lbl_1_bss_16CB4.mode) {
        case 0:
            for(i=0; i<2; i++) {
                if(lbl_1_bss_0.player[i]->mode != MGPLAYER_MODE_WALK) {
                    moveNum++;
                }
                moveNum = moveNum+MgPlayerModeAttrCheck(lbl_1_bss_0.player[i], MGPLAYER_MODEATTR_SQUISH|MGPLAYER_MODEATTR_SQUISH_HARD);
                MgPlayerPadSet(lbl_1_bss_0.player[i], 0, 0, 0, 0);
            }
            MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
            lbl_1_bss_16A84[0].oldPos.x = pos.x;
            lbl_1_bss_16A84[0].oldPos.y = pos.y;
            lbl_1_bss_16A84[0].oldPos.z = pos.z;
            MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
            lbl_1_bss_16A84[1].oldPos.x = pos.x;
            lbl_1_bss_16A84[1].oldPos.y = pos.y;
            lbl_1_bss_16A84[1].oldPos.z = pos.z;
            MgActorExec();
            MgActorPosGet(lbl_1_bss_0.player[0]->actor, &pos);
            lbl_1_bss_16A84[0].pos.x = pos.x;
            lbl_1_bss_16A84[0].pos.y = pos.y;
            lbl_1_bss_16A84[0].pos.z = pos.z;
            MgActorPosGet(lbl_1_bss_0.player[1]->actor, &pos);
            lbl_1_bss_16A84[1].pos.x = pos.x;
            lbl_1_bss_16A84[1].pos.y = pos.y;
            lbl_1_bss_16A84[1].pos.z = pos.z;
            fn_1_153A8();
            pos.x = lbl_1_bss_16A84[0].pos.x;
            pos.y = lbl_1_bss_16A84[0].pos.y;
            pos.z = lbl_1_bss_16A84[0].pos.z;
            MgActorPosUpdate(lbl_1_bss_0.player[0]->actor, &pos);
            pos.x = lbl_1_bss_16A84[1].pos.x;
            pos.y = lbl_1_bss_16A84[1].pos.y;
            pos.z = lbl_1_bss_16A84[1].pos.z;
            MgActorPosUpdate(lbl_1_bss_0.player[1]->actor, &pos);
            for(i=0; i<2; i++) {
                Hu3DModelPosSet(lbl_1_bss_17A00->models[i+81].modelId, lbl_1_bss_16A84[i].pos.x, lbl_1_bss_16A84[i].pos.y, lbl_1_bss_16A84[i].pos.z);
            }
            if(moveNum == 0 && lbl_1_bss_16CB4.timer++ >= 30) {
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[81].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17A00->models[82].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_16CB4.timer = 0;
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 1:
            if(lbl_1_bss_16CB4.winner) {
                x = lbl_1_bss_16D94[0].pos.x;
                lbl_1_bss_16A84[winNo].vel.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.x-winModel->pos.x;
                lbl_1_bss_16A84[winNo].vel.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.z-winModel->pos.z;
                x = sqrt(lbl_1_bss_16A84[winNo].vel.x*lbl_1_bss_16A84[winNo].vel.x+lbl_1_bss_16A84[winNo].vel.z*lbl_1_bss_16A84[winNo].vel.z);
                if(x >= 10.0f) {
                    x = 4.0f/x;
                    lbl_1_bss_16A84[winNo].vel.x *= x;
                    lbl_1_bss_16A84[winNo].vel.z *= x;
                    x = 180.0*(acos(lbl_1_bss_16A84[winNo].vel.x/4.1f)/M_PI);
                    z = 180.0*(asin(lbl_1_bss_16A84[winNo].vel.z/4.1f)/M_PI);
                    if(z < 0.0f) {
                        x = 360.0f-x;
                    }
                    lbl_1_bss_16A84[winNo].rotY = x;
                    lbl_1_bss_16A84[winNo].rotY = 90.0f+(-lbl_1_bss_16A84[winNo].rotY);
                    winPl->shiftMode = 1;
                    winPl->shiftMotNo = 1;
                    winPl->shiftTime = 0.0f;
                    winPl->shiftSpeed = 4.0f;
                    winPl->shiftAttr = HU3D_MOTATTR_LOOP;
                    winPl->attrReset = 0;
                } else {
                    lbl_1_bss_16A84[winNo].vel.x = 0.0f;
                    lbl_1_bss_16A84[winNo].vel.z = 0.0f;
                    lbl_1_bss_16A84[winNo].rotY = lbl_1_bss_0.player[winNo]->actor->rotY;
                }
                x = loseModel->pos.x-winModel->pos.x;
                z = loseModel->pos.z-winModel->pos.z;
                dist = sqrt(x*x+z*z);
                if(dist <= 150.0f || (dist <= 350.0f && z >= 0.0f)) {
                    lbl_1_bss_16A84[loseNo].vel.x = -loseModel->pos.x;
                    lbl_1_bss_16A84[loseNo].vel.z = -loseModel->pos.z;
                    x = sqrt(lbl_1_bss_16A84[loseNo].vel.x*lbl_1_bss_16A84[loseNo].vel.x+lbl_1_bss_16A84[loseNo].vel.z*lbl_1_bss_16A84[loseNo].vel.z);
                    if(x) {
                        x = 7.0f/x;
                    } else {
                        x = 0.0f;
                    }
                    lbl_1_bss_16A84[loseNo].vel.x *= x;
                    lbl_1_bss_16A84[loseNo].vel.z *= x;
                    x = 180.0*(acos(lbl_1_bss_16A84[loseNo].vel.x/7.1f)/M_PI);
                    z = 180.0*(asin(lbl_1_bss_16A84[loseNo].vel.z/7.1f)/M_PI);
                    if(z < 0.0f) {
                        x = 360.0f-x;
                    }
                    lbl_1_bss_16A84[loseNo].rotY = x;
                    lbl_1_bss_16A84[loseNo].rotY = 90.0f+(-lbl_1_bss_16A84[loseNo].rotY);
                    losePl->shiftMode = 1;
                    losePl->shiftMotNo = 1;
                    losePl->shiftTime = 0.0f;
                    losePl->shiftSpeed = 4.0f;
                    losePl->shiftAttr = HU3D_MOTATTR_LOOP;
                    losePl->attrReset = 0;
                    lbl_1_bss_16CB4.loseRunF = 1;
                }
                lbl_1_bss_16CB4.mode++;
            } else {
                lbl_1_bss_16CB4.mode = 5;
            }
            break;

        case 2:
            winModel->pos.x += lbl_1_bss_16A84[winNo].vel.x;
            winModel->pos.z += lbl_1_bss_16A84[winNo].vel.z;
            winModel->rot.y = lbl_1_bss_16A84[winNo].rotY;
            x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.x-winModel->pos.x;
            z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.centreSpot].mdlNo[0]].pos.z-winModel->pos.z;
            x = sqrt(x*x+z*z);
            if(x < 10.0f) {
                lbl_1_bss_16A84[winNo].rotYStart = winModel->rot.y;
                angle = winModel->rot.y;
                angle = angle%360;
                if(angle != 0) {
                    if(angle < 0) {
                        angle = angle*-1;
                        negF = 1;
                    } else {
                        negF = 0;
                    }
                    if(angle > 180) {
                        angle = 360-angle;
                    } else {
                        angle = angle*-1;
                    }
                    if(negF) {
                        angle = angle*-1;
                    }
                }
                lbl_1_bss_16CB4.rotYEnd = winModel->rot.y+angle;
                if((!lbl_1_bss_16A84[winNo].vel.x && !lbl_1_bss_16A84[winNo].vel.z && lbl_1_bss_16A84[winNo].rotYStart-lbl_1_bss_16CB4.rotYEnd > 0.0f) ? lbl_1_bss_16A84[winNo].rotYStart-lbl_1_bss_16CB4.rotYEnd : -1.0f*(lbl_1_bss_16A84[winNo].rotYStart-lbl_1_bss_16CB4.rotYEnd) >= 4.0f) {
                    winPl->shiftMode = 1;
                    winPl->shiftMotNo = 1;
                    winPl->shiftTime = 0.0f;
                    winPl->shiftSpeed = 4.0f;
                    winPl->shiftAttr = HU3D_MOTATTR_LOOP;
                    winPl->attrReset = 0;
                }
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 3:
            if(lbl_1_bss_16CB4.winner) {
                speed = 30.0f;
                doneF = fn_1_1850(&winModel->rot.y, speed, lbl_1_bss_16A84[winNo].rotYStart, lbl_1_bss_16CB4.rotYEnd);
                if(doneF == 0) {
                    winPl->shiftMode = 1;
                    winPl->shiftMotNo = 0;
                    winPl->shiftTime = 0.0f;
                    winPl->shiftSpeed = 4.0f;
                    winPl->shiftAttr = 0;
                    winPl->attrReset = HU3D_MOTATTR_LOOP;
                    lbl_1_bss_16CB4.mode++;
                }
            }
            break;

        case 4:
            speed = 30.0f;
            doneF += fn_1_1850(&lbl_1_bss_38->center.x, speed, lbl_1_data_368[1].center.x, winModel->pos.x);
            doneF += fn_1_1850(&lbl_1_bss_38->center.y, speed, lbl_1_data_368[1].center.y, 70.0f+winModel->pos.y);
            doneF += fn_1_1850(&lbl_1_bss_38->center.z, speed, lbl_1_data_368[1].center.z, winModel->pos.z);
            doneF += fn_1_1850(&lbl_1_bss_38->rot.x, speed, lbl_1_data_368[1].rot.x, -18.0f);
            doneF += fn_1_1850(&lbl_1_bss_38->zoom, speed, lbl_1_data_368[1].zoom, 600.0f);
            if(doneF == 0) {
                lbl_1_bss_16CB4.mode = 7;
            }
            break;

        case 5:
            moveNum = fn_1_E738();
            if(moveNum) {
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 6:
            if(lbl_1_bss_16CB4.endTimer++ > 60) {
                lbl_1_bss_16CB4.mode++;
            }
            break;

        case 7:
            result = 1;
            break;
    }
    if(lbl_1_bss_16CB4.loseRunF) {
        loseModel->pos.x += lbl_1_bss_16A84[loseNo].vel.x;
        loseModel->pos.z += lbl_1_bss_16A84[loseNo].vel.z;
        loseModel->rot.y = lbl_1_bss_16A84[loseNo].rotY;
        for(i=0, doneF=0; i<12; i++) {
            x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.x-loseModel->pos.x;
            z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.z-loseModel->pos.z;
            dist = sqrt(x*x+z*z);
            if(dist < 106.0f) {
                doneF = 1;
            }
        }
        if(doneF == 0) {
            if((loseModel->pos.y -= 10.0f) <= 100.0f) {
                loseModel->pos.y = 100.0f;
            }
        }
        x = -loseModel->pos.x;
        z = -loseModel->pos.z;
        x = sqrt(x*x+z*z);
        if(x < 20.0f) {
            losePl->shiftMode = 1;
            losePl->shiftMotNo = 0;
            losePl->shiftTime = 0.0f;
            losePl->shiftSpeed = 4.0f;
            losePl->shiftAttr = 0;
            losePl->attrReset = HU3D_MOTATTR_LOOP;
            lbl_1_bss_16CB4.loseRunF = 0;
        }
    }
    return result;
}

/* asm 12059-12193, 128 insns. A stomping duellist cannot be stunned or headjumped until it lands. */
void fn_1_115B0(void)
{
    s16 i;

    for(i=0; i<2; i++) {
        if(lbl_1_bss_0.player[i]->mode == MGPLAYER_MODE_HIPDROP) {
            MgPlayerAttrSet(lbl_1_bss_0.player[i], MGPLAYER_ATTR_STUNOFF);
            MgPlayerAttrSet(lbl_1_bss_0.player[i^1], MGPLAYER_ATTR_HEADJUMP_OFF);
            lbl_1_bss_16A84[i].attrF = 1;
            if(lbl_1_bss_16A84[i].hitF) {
                lbl_1_bss_16A84[i].attrF = 0;
            }
        } else if(lbl_1_bss_0.player[i]->mode == MGPLAYER_MODE_WALK) {
            if(lbl_1_bss_16A84[i].hitF) {
                lbl_1_bss_16A84[i].attrF = 0;
            }
            if(lbl_1_bss_16A84[i].attrF && !lbl_1_bss_16A84[i].hitF) {
                MgPlayerAttrReset(lbl_1_bss_0.player[i], MGPLAYER_ATTR_STUNOFF);
                MgPlayerAttrReset(lbl_1_bss_0.player[i^1], MGPLAYER_ATTR_HEADJUMP_OFF);
                lbl_1_bss_16A84[i].attrF = 0;
            }
        }
    }
}

/* asm 12196-12205, 7 insns. The duellists' narrow-phase hook: nothing is ever reported. */
int fn_1_117B0(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
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

/* asm 12208-12563, 346 insns. The duellists' correction hook: a stomp that lands near a panel's centre hits it. */
void fn_1_117CC(MGACTOR *actor, int param)
{
    int playerNo;
    HU3DMODEL *model;
    s16 panelNo;
    float dx;
    float dz;
    float dist;
    float volF;
    float panF;
    s16 pan;
    s16 vol;

    playerNo = actor->param;
    model = &Hu3DData[lbl_1_bss_17A00->models[playerNo+81].modelId];
    if(actor->colMesh <= 11 && model->pos.y > 132.0f) {
        panelNo = actor->colMesh;
        if(panelNo != lbl_1_bss_16A84[playerNo^1].panelNo) {
            if(lbl_1_bss_0.player[playerNo]->mode == MGPLAYER_MODE_HIPDROP && lbl_1_bss_0.player[playerNo]->subMode == 3 && lbl_1_bss_16CB4.winner == 0 && lbl_1_bss_16CB4.timeUpF == 0) {
                dx = lbl_1_bss_17A00->models[lbl_1_bss_179A0[panelNo].mdlNo[0]].pos.x-model->pos.x;
                dz = lbl_1_bss_17A00->models[lbl_1_bss_179A0[panelNo].mdlNo[0]].pos.z-model->pos.z;
                dist = sqrt(dx*dx+dz*dz);
                if(dist <= 71.0f) {
                    if(dist == lbl_1_bss_16A84[playerNo].nearDist) {
                        volF = 0.026956521f*lbl_1_bss_17A00->models[playerNo+81].pos.z;
                        panF = 0.055652175f*lbl_1_bss_17A00->models[playerNo+81].pos.x;
                        vol = 111.0f+volF;
                        pan = 64.0f+panF;
                        fn_1_5D64(0, vol, pan);
                        lbl_1_bss_16844[panelNo].mode = 2;
                        lbl_1_bss_16A84[playerNo].hitF = 1;
                        lbl_1_bss_16A84[playerNo].panelNo = panelNo;
                        lbl_1_bss_16A84[playerNo].nearDist = -1.0f;
                    }
                    lbl_1_bss_16A84[playerNo].nearDist = dist;
                } else {
                    lbl_1_bss_16844[panelNo].mode = 1;
                }
            } else if(lbl_1_bss_16844[panelNo].mode != 2 && lbl_1_bss_0.player[playerNo]->mode != MGPLAYER_MODE_HIPDROP) {
                lbl_1_bss_16844[panelNo].mode = 1;
            }
        }
    }
}

/* asm 12566-12702, 134 insns. A computer duellist's settings, by difficulty. */
void fn_1_11D34(s16 player)
{
    float speedTbl[4] = { 7.2f, 8.0f, 9.0f, 10.285714f };
    s16 retryTbl[4] = { 40, 20, 15, 0 };
    s16 markTbl[4] = { 95, 85, 50, 0 };
    s16 unkTbl[4] = { 20, 35, 40, 60 };

    if(lbl_1_bss_17A00->chr[player].dif != 0) {
        lbl_1_bss_16A84[player].comF = 1;
        lbl_1_bss_16A84[player].comDif = lbl_1_bss_17A00->chr[player].dif-1;
        lbl_1_bss_16A84[player].comRetryChance = retryTbl[lbl_1_bss_16A84[player].comDif];
        lbl_1_bss_16A84[player].comMarkChance = markTbl[lbl_1_bss_16A84[player].comDif];
        lbl_1_bss_16A84[player].chaseSpeed = speedTbl[lbl_1_bss_16A84[player].comDif];
        lbl_1_bss_16A84[player].goTypeChance = unkTbl[lbl_1_bss_16A84[player].comDif];
    }
}

/* asm 12705-12853, 139 insns. A computer duellist's frame: think, then run what it chose. */
s16 fn_1_11F4C(s16 player)
{
    s16 result;

    result = 0;
    lbl_1_bss_16A84[player].btn = 0;
    lbl_1_bss_16A84[player].btnDown = 0;
    lbl_1_bss_16A84[player].stkX = 0;
    lbl_1_bss_16A84[player].stkY = 0;
    if(lbl_1_bss_16A84[player].stopF == 0) {
        switch(lbl_1_bss_16A84[player].comMode) {
            case 0:
                lbl_1_bss_16A84[player].comMode = fn_1_12178(player);
                break;

            case 1:
                if(fn_1_12510(player)) {
                    lbl_1_bss_16A84[player].comMode = 0;
                }
                break;

            case 2:
                if(fn_1_13384(player)) {
                    lbl_1_bss_16A84[player].comMode = 0;
                }
                break;

            case 3:
                if(fn_1_13620(player)) {
                    lbl_1_bss_16A84[player].comMode = 0;
                }
                break;

            case 4:
                if(fn_1_143DC(player)) {
                    lbl_1_bss_16A84[player].comMode = 0;
                }
                break;

            case 5:
                if(fn_1_14974(player)) {
                    lbl_1_bss_16A84[player].comMode = 0;
                }
                break;

            case 6:
                break;
        }
        fn_1_14FC4(player);
    }
    return result;
}

/* asm 12856-13102, 230 insns. A computer duellist decides what to do next and which panel to go for. */
s16 fn_1_12178(s16 player)
{
    s16 result;
    s16 rand;
    s16 i;

    result = 0;
    rand = 0;
    switch(lbl_1_bss_16A84[player].thinkMode) {
        case 0:
            lbl_1_bss_16A84[player].unk0A6 = 0;
            rand = frandmod(100)+1;
            if(rand < 85) {
                lbl_1_bss_16A84[player].thinkMode = 3;
            } else {
                rand = frandmod(2)+1;
                lbl_1_bss_16A84[player].thinkMode = rand;
            }
            break;

        case 1:
            result = 4;
            lbl_1_bss_16A84[player].thinkMode = 0;
            break;

        case 2:
            result = 5;
            lbl_1_bss_16A84[player].thinkMode = 0;
            break;

        case 3:
            for(i=0; i<12; i++) {
                if(lbl_1_bss_16A84[player].panelHit[i] == 0 && lbl_1_bss_16A84[player^1].panelHit[i] != 0) {
                    rand = frandmod(100)+1;
                    if(rand > lbl_1_bss_16A84[player].comMarkChance) {
                        lbl_1_bss_16A84[player].panelHit[i] = 1;
                    }
                }
            }
            lbl_1_bss_16A84[player].lastPanel = lbl_1_bss_16A84[player].targetPanel;
            do {
                lbl_1_bss_16A84[player].targetPanel = frandmod(12);
                for(i=0, rand=0; i<12; i++) {
                    if(lbl_1_bss_16A84[player].panelHit[i] == 0) {
                        rand = 1;
                    }
                }
            } while(rand && lbl_1_bss_16A84[player].panelHit[lbl_1_bss_16A84[player].targetPanel] && (rand = frandmod(100)+1) >= lbl_1_bss_16A84[player].comRetryChance/lbl_1_bss_16A84[player].panelHit[lbl_1_bss_16A84[player].targetPanel]);
            lbl_1_bss_16A84[player].thinkMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* asm 13105-14050, 925 insns. A computer duellist goes for its target panel and stomps it. */
s16 fn_1_12510(s16 player)
{
    s16 result;
    s16 doneF;
    s16 rand;
    float dx;
    float dz;
    float dist;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_16A84[player].goMode) {
        case 0:
            lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
            lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
            lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
            lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
            lbl_1_bss_16A84[player].chaseRadius = 150.0f;
            lbl_1_bss_16A84[player].goMode++;
            break;

        case 1:
            if(lbl_1_bss_16A84[player].goType == 0) {
                if(lbl_1_bss_16A84[player].avoidF == 0 && lbl_1_bss_16A84[player].goMode == 1) {
                    dx = lbl_1_bss_16A84[player].pos.x-lbl_1_bss_16A84[player^1].pos.x;
                    dz = lbl_1_bss_16A84[player].pos.z-lbl_1_bss_16A84[player^1].pos.z;
                    dist = sqrt(dx*dx+dz*dz);
                    if(dist < 150.0f) {
                        rand = frandmod(100)+1;
                        if(rand < lbl_1_bss_16A84[player].goTypeChance) {
                            lbl_1_bss_16A84[player].goType = frandmod(2)+1;
                        } else {
                            rand = frandmod(100)+1;
                            if(rand < 50) {
                                lbl_1_bss_16A84[player].avoidF = 1;
                            }
                        }
                    }
                }
                lbl_1_bss_16A84[player].chaseRadius = 150.0f;
                doneF = fn_1_13384(player);
                if(doneF) {
                    lbl_1_bss_16A84[player].goTimer = 0;
                    lbl_1_bss_16A84[player].avoidF = 0;
                    lbl_1_bss_16A84[player].goMode++;
                } else if(lbl_1_bss_16A84[player].goTimer++ >= 360) {
                    lbl_1_bss_16A84[player].avoidF = 0;
                }
            }
            if(lbl_1_bss_16A84[player^1].unk014 == lbl_1_bss_16A84[player].targetPanel && lbl_1_bss_16A84[player^1].panelHit[lbl_1_bss_16A84[player].targetPanel] != 0) {
                lbl_1_bss_16A84[player].goType = 0;
                lbl_1_bss_16A84[player].goMode = 0;
                lbl_1_bss_16A84[player].stkOnF = 0;
                lbl_1_bss_16A84[player].chaseMode = 0;
                lbl_1_bss_16A84[player].panelHit[lbl_1_bss_16A84[player].targetPanel]++;
                result = 1;
                break;
            }
            switch(lbl_1_bss_16A84[player].goType) {
                case 1:
                    if(fn_1_143DC(player)) {
                        lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                        lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                        lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                        lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                        lbl_1_bss_16A84[player].goType = 0;
                    }
                    break;

                case 2:
                    if(fn_1_14974(player)) {
                        lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                        lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                        lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                        lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                        lbl_1_bss_16A84[player].goType = 0;
                    }
                    break;
            }
            if(lbl_1_bss_16A84[player].goType != 0 && lbl_1_bss_16844[lbl_1_bss_16A84[player^1].panelNo].doneF) {
                lbl_1_bss_16A84[player].kickMode = 0;
                lbl_1_bss_16A84[player].punchMode = 0;
                lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.x;
                lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16A84[player].targetPanel].mdlNo[0]].pos.z;
                lbl_1_bss_16A84[player].goType = 0;
                lbl_1_bss_16A84[player].avoidF = 1;
            }
            break;

        case 2:
            doneF = fn_1_13AA4(player);
            if(doneF) {
                lbl_1_bss_16A84[player].goMode++;
            }
            break;

        case 3:
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].goMode++;
            break;

        case 4:
            if(lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_HIPDROP) {
                lbl_1_bss_16A84[player].goMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 14053-14227, 167 insns. A computer duellist runs to chasePos, then on to arrivePos if one is queued. */
s16 fn_1_13384(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_16A84[player].chaseMode) {
        case 0:
            MgPlayerComStkOn(lbl_1_bss_0.player[player]);
            lbl_1_bss_16A84[player].stkOnF = 1;
            lbl_1_bss_16A84[player].chaseMode++;
            break;

        case 1:
            doneF = MgPlayerVecChase(lbl_1_bss_0.player[player], &lbl_1_bss_16A84[player].chasePos, lbl_1_bss_16A84[player].chaseSpeed, lbl_1_bss_16A84[player].chaseRadius);
            if(doneF) {
                if(lbl_1_bss_16A84[player].arriveF == 1) {
                    lbl_1_bss_16A84[player].chasePos = lbl_1_bss_16A84[player].arrivePos;
                    lbl_1_bss_16A84[player].chaseRadius = lbl_1_bss_16A84[player].arriveRadius;
                    lbl_1_bss_16A84[player].arriveF = 0;
                } else {
                    lbl_1_bss_16A84[player].chaseMode++;
                }
            }
            break;

        case 2:
            MgPlayerComStkOff(lbl_1_bss_0.player[player]);
            lbl_1_bss_16A84[player].stkOnF = 0;
            lbl_1_bss_16A84[player].chaseMode = 0;
            result = 1;
            break;
    }
    return result;
}

/* asm 14230-14529, 289 insns. A computer duellist jumps toward goalPos. */
s16 fn_1_13620(s16 player)
{
    s16 result;
    HuVecF dir;

    result = 0;
    switch(lbl_1_bss_16A84[player].jumpMode) {
        case 0:
            PSVECSubtract(&lbl_1_bss_16A84[player].goalPos, &lbl_1_bss_16A84[player].pos, &dir);
            dir.x /= 46.0f;
            dir.z /= 46.0f;
            dir.x *= 5.6f;
            dir.z *= 5.6f;
            if(dir.x > 72.0f) {
                dir.x = 72.0f;
            }
            if(dir.x < -72.0f) {
                dir.x = -72.0f;
            }
            if(dir.z > 72.0f) {
                dir.z = 72.0f;
            }
            if(dir.z < -72.0f) {
                dir.z = -72.0f;
            }
            lbl_1_bss_16A84[player].jumpStkX = dir.x;
            lbl_1_bss_16A84[player].jumpStkY = dir.z;
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].jumpTimer = 0;
            lbl_1_bss_16A84[player].jumpMode++;
            break;

        case 1:
            lbl_1_bss_16A84[player].btn |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            if(lbl_1_bss_16A84[player].jumpTimer++ > 10) {
                lbl_1_bss_16A84[player].jumpTimer = 0;
                lbl_1_bss_16A84[player].jumpMode++;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            if(lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_JUMP) {
                lbl_1_bss_16A84[player].stkX = 0;
                lbl_1_bss_16A84[player].stkY = 0;
                lbl_1_bss_16A84[player].jumpMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 14532-14848, 305 insns. A computer duellist jumps toward goalPos. */
s16 fn_1_13AA4(s16 player)
{
    s16 result;
    HuVecF dir;

    result = 0;
    switch(lbl_1_bss_16A84[player].jumpMode) {
        case 0:
            PSVECSubtract(&lbl_1_bss_16A84[player].goalPos, &lbl_1_bss_16A84[player].pos, &dir);
            dir.x /= 23.0f;
            dir.z /= 23.0f;
            dir.x *= 5.6f;
            dir.z *= 5.6f;
            if(dir.x > 72.0f) {
                dir.x = 72.0f;
            }
            if(dir.x < -72.0f) {
                dir.x = -72.0f;
            }
            if(dir.z > 72.0f) {
                dir.z = 72.0f;
            }
            if(dir.z < -72.0f) {
                dir.z = -72.0f;
            }
            lbl_1_bss_16A84[player].jumpStkX = dir.x;
            lbl_1_bss_16A84[player].jumpStkY = -dir.z;
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].jumpTimer = 0;
            lbl_1_bss_16A84[player].jumpMode++;
            break;

        case 1:
            if(MgPlayerModeAttrCheck(lbl_1_bss_0.player[player], MGPLAYER_MODEATTR_AIR)) {
                lbl_1_bss_16A84[player].btn |= PAD_BUTTON_A;
                lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
                lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
                if(lbl_1_bss_16A84[player].jumpTimer++ > 10) {
                    lbl_1_bss_16A84[player].jumpMode++;
                }
            } else {
                lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_A;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            if(lbl_1_bss_16A84[player].jumpTimer++ > 23) {
                lbl_1_bss_16A84[player].stkX = 0;
                lbl_1_bss_16A84[player].stkY = 0;
                lbl_1_bss_16A84[player].jumpMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 14851-15146, 285 insns. A computer duellist jumps toward goalPos. */
s16 fn_1_13F68(s16 player)
{
    s16 result;
    HuVecF dir;

    result = 0;
    switch(lbl_1_bss_16A84[player].jumpMode) {
        case 0:
            PSVECSubtract(&lbl_1_bss_16A84[player].goalPos, &lbl_1_bss_16A84[player].pos, &dir);
            dir.x /= 60.0f;
            dir.z /= 60.0f;
            dir.x *= 5.6f;
            dir.z *= 5.6f;
            if(dir.x > 72.0f) {
                dir.x = 72.0f;
            }
            if(dir.x < -72.0f) {
                dir.x = -72.0f;
            }
            if(dir.z > 72.0f) {
                dir.z = 72.0f;
            }
            if(dir.z < -72.0f) {
                dir.z = -72.0f;
            }
            lbl_1_bss_16A84[player].jumpStkX = dir.x;
            lbl_1_bss_16A84[player].jumpStkY = -dir.z;
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].jumpTimer = 0;
            lbl_1_bss_16A84[player].jumpMode++;
            break;

        case 1:
            lbl_1_bss_16A84[player].btn |= PAD_BUTTON_A;
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            if(lbl_1_bss_16A84[player].jumpTimer++ > 10) {
                lbl_1_bss_16A84[player].jumpMode++;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].stkX = lbl_1_bss_16A84[player].jumpStkX;
            lbl_1_bss_16A84[player].stkY = lbl_1_bss_16A84[player].jumpStkY;
            if(lbl_1_bss_16A84[player].jumpTimer++ > 20) {
                lbl_1_bss_16A84[player].stkX = 0;
                lbl_1_bss_16A84[player].stkY = 0;
                lbl_1_bss_16A84[player].jumpMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 15149-15523, 358 insns. A computer duellist runs at its rival and punches. */
s16 fn_1_143DC(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_16A84[player].punchMode) {
        case 0:
            lbl_1_bss_16A84[player].chaseRadius = 90.0f;
            lbl_1_bss_16A84[player].punchTimer = 0;
            lbl_1_bss_16A84[player].punchMode++;
            break;

        case 1:
            if(lbl_1_bss_16A84[player].arriveF == 0) {
                lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_16A84[player^1].pos.x;
                lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_16A84[player^1].pos.z;
            }
            lbl_1_bss_16A84[player].punchTimer++;
            doneF = fn_1_13384(player);
            if(doneF) {
                lbl_1_bss_16A84[player].stuckTimer = 0;
                lbl_1_bss_16A84[player].punchMode++;
            } else if(lbl_1_bss_16A84[player].stuckTimer >= 50 || lbl_1_bss_16A84[player].punchTimer >= 180) {
                MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                lbl_1_bss_16A84[player].stkOnF = 0;
                lbl_1_bss_16A84[player].chaseMode = 0;
                lbl_1_bss_16A84[player].stuckTimer = 0;
                lbl_1_bss_16A84[player].punchMode++;
            }
            break;

        case 2:
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_B;
            lbl_1_bss_16A84[player].punchMode++;
            break;

        case 3:
            if(lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_PUNCH) {
                lbl_1_bss_16A84[player].punchMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 15526-15946, 404 insns. A computer duellist runs at its rival, jumps and kicks. */
s16 fn_1_14974(s16 player)
{
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_16A84[player].kickMode) {
        case 0:
            lbl_1_bss_16A84[player].chaseRadius = 200.0f;
            lbl_1_bss_16A84[player].kickTimer = 0;
            lbl_1_bss_16A84[player].kickMode++;
            break;

        case 1:
            if(lbl_1_bss_16A84[player].arriveF == 0) {
                lbl_1_bss_16A84[player].chasePos.x = lbl_1_bss_16A84[player^1].pos.x;
                lbl_1_bss_16A84[player].chasePos.z = lbl_1_bss_16A84[player^1].pos.z;
            }
            lbl_1_bss_16A84[player].kickTimer++;
            doneF = fn_1_13384(player);
            if(doneF) {
                lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_16A84[player^1].pos.x;
                lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_16A84[player^1].pos.z;
                lbl_1_bss_16A84[player].kickMode++;
            } else if(lbl_1_bss_16A84[player].kickTimer >= 180) {
                MgPlayerComStkOff(lbl_1_bss_0.player[player]);
                lbl_1_bss_16A84[player].stkOnF = 0;
                lbl_1_bss_16A84[player].chaseMode = 0;
                lbl_1_bss_16A84[player].goalPos.x = lbl_1_bss_16A84[player^1].pos.x;
                lbl_1_bss_16A84[player].goalPos.z = lbl_1_bss_16A84[player^1].pos.z;
                lbl_1_bss_16A84[player].kickMode++;
            }
            break;

        case 2:
            doneF = fn_1_13F68(player);
            if(doneF) {
                lbl_1_bss_16A84[player].kickMode++;
            }
            break;

        case 3:
            lbl_1_bss_16A84[player].btnDown |= PAD_BUTTON_B;
            lbl_1_bss_16A84[player].kickMode++;
            break;

        case 4:
            if(lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_KICK) {
                lbl_1_bss_16A84[player].kickMode = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 15949-16204, 249 insns. A computer duellist held on one spot for a second detours through the centre. */
s16 fn_1_14FC4(s16 player)
{
    s16 result;

    result = 0;
    switch(lbl_1_bss_16A84[player].arriveF) {
        case 0:
            if(lbl_1_bss_16A84[player].stuckNo != -1 && lbl_1_bss_16A84[player].stuckNo == lbl_1_bss_16A84[player].stuckNoOld && lbl_1_bss_16A84[player].chaseMode == 1
                && lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_HIT && lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_KNOCKBACK
                && lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_SQUISH && lbl_1_bss_0.player[player]->mode != MGPLAYER_MODE_SQUISH_HARD) {
                if(lbl_1_bss_16A84[player].stuckTimer++ > 60) {
                    lbl_1_bss_16A84[player].arrivePos = lbl_1_bss_16A84[player].chasePos;
                    lbl_1_bss_16A84[player].arriveRadius = lbl_1_bss_16A84[player].chaseRadius;
                    lbl_1_bss_16A84[player].chasePos.x = 0.0f;
                    lbl_1_bss_16A84[player].chasePos.y = lbl_1_bss_16A84[player].arrivePos.y;
                    lbl_1_bss_16A84[player].chasePos.z = 0.0f;
                    lbl_1_bss_16A84[player].chaseRadius = 300.0f;
                    lbl_1_bss_16A84[player].stuckTimer = 0;
                    lbl_1_bss_16A84[player].arriveF++;
                }
            } else {
                lbl_1_bss_16A84[player].stuckTimer = 0;
            }
            lbl_1_bss_16A84[player].stuckNoOld = lbl_1_bss_16A84[player].stuckNo;
            lbl_1_bss_16A84[player].stuckNo = -1;
            break;

        case 1:
            lbl_1_bss_16A84[player].chasePos.x = 0.0f;
            lbl_1_bss_16A84[player].chasePos.y = lbl_1_bss_16A84[player].arrivePos.y;
            lbl_1_bss_16A84[player].chasePos.z = 0.0f;
            lbl_1_bss_16A84[player].chaseRadius = 300.0f;
            break;
    }
    return result;
}

/*
 * asm 16207-17702, 1427 insns. The duellists' collision: push each out of the
 * raised panels it is not standing on, back inside the eight walls, and, while
 * they walk to their marks, apart from each other.
 *
 * The second wall classification reads x and z after the first push has
 * overwritten them with the push vector; retail does the same.
 */
void fn_1_153A8(void)
{
    float wallSign[8];
    s16 wallList[8];
    s16 player;
    s16 hitNum;
    s16 i;
    s16 wallNum;
    float x;
    float z;
    float dist;
    float scale;
    float t2;
    float len2;
    float cx;
    float cz;
    float t;
    HU3DMODEL *model[2];
    float radius = 45.0f;
    float panelR = 67.0f;
    float stepH = 32.0f;
    float wall[8][4] = {
        { 230.0f, -554.0f, 554.0f, -230.0f },
        { 554.0f, -230.0f, 554.0f, 230.0f },
        { 554.0f, 230.0f, 230.0f, 554.0f },
        { 230.0f, 554.0f, -230.0f, 554.0f },
        { -230.0f, 554.0f, -554.0f, 230.0f },
        { -554.0f, 230.0f, -554.0f, -230.0f },
        { -554.0f, -230.0f, -230.0f, -554.0f },
        { -230.0f, -554.0f, 230.0f, -554.0f }
    };

    for(player=0; player<2; player++) {
        hitNum = 0;
        for(i=0; i<12; i++) {
            x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.x-lbl_1_bss_16A84[player].pos.x;
            z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.z-lbl_1_bss_16A84[player].pos.z;
            dist = sqrt(x*x+z*z);
            if(dist < radius+panelR) {
                if(i == lbl_1_bss_16A84[player^1].unk014 || stepH+lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.y > lbl_1_bss_16A84[player].pos.y) {
                    if(dist) {
                        scale = (radius+panelR)/dist;
                    } else {
                        scale = 0.0f;
                    }
                    x *= scale;
                    z *= scale;
                    lbl_1_bss_16A84[player].pos.x = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.x-x;
                    lbl_1_bss_16A84[player].pos.z = lbl_1_bss_17A00->models[lbl_1_bss_179A0[i].mdlNo[3]].pos.z-z;
                    lbl_1_bss_16A84[player].stuckNo = i;
                } else {
                    hitNum++;
                    lbl_1_bss_16A84[player].unk014 = i;
                }
            }
            if(hitNum == 0) {
                lbl_1_bss_16A84[player].unk014 = -1;
            }
        }
        x = lbl_1_bss_16A84[player].pos.x;
        z = lbl_1_bss_16A84[player].pos.z;
        wallNum = 0;
        for(i=0; i<8; i++) {
            wallSign[i] = 1.0f;
            switch(i) {
                case 0:
                    if(-x+z < -784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 1:
                    if(x > 554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 2:
                    if(x+z > 784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 3:
                    if(z > 554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 4:
                    if(-x+z > 784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 5:
                    if(x < -554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 6:
                    if(x+z < -784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 7:
                    if(z < -554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;
            }
        }
        for(i=0; i<wallNum; i++) {
            x = wall[wallList[i]][0]-wall[wallList[i]][2];
            z = wall[wallList[i]][1]-wall[wallList[i]][3];
            len2 = x*x+z*z;
            t = -1.0f*(x*(wall[wallList[i]][0]-lbl_1_bss_16A84[player].pos.x)+z*(wall[wallList[i]][1]-lbl_1_bss_16A84[player].pos.z));
            if(len2) {
                t2 = t/len2;
            } else {
                t2 = 0.0f;
            }
            cx = x*t2+wall[wallList[i]][0];
            cz = z*t2+wall[wallList[i]][1];
            x = lbl_1_bss_16A84[player].pos.x-cx;
            z = lbl_1_bss_16A84[player].pos.z-cz;
            dist = sqrt(x*x+z*z);
            if(dist) {
                scale = radius/dist;
            } else {
                scale = 0.0f;
            }
            x = x*scale*wallSign[wallList[i]];
            z = z*scale*wallSign[wallList[i]];
            lbl_1_bss_16A84[player].pos.x = cx+x;
            lbl_1_bss_16A84[player].pos.z = cz+z;
        }
        wallNum = 0;
        for(i=0; i<8; i++) {
            wallSign[i] = 1.0f;
            switch(i) {
                case 0:
                    if(-x+z < -784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 1:
                    if(x > 554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 2:
                    if(x+z > 784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 3:
                    if(z > 554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 4:
                    if(-x+z > 784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 5:
                    if(x < -554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 6:
                    if(x+z < -784.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;

                case 7:
                    if(z < -554.0f) {
                        wallSign[i] = -1.0f;
                        wallList[wallNum] = i;
                        wallNum++;
                    }
                    break;
            }
        }
        for(i=0; i<8; i++) {
            x = wall[i][0]-wall[i][2];
            z = wall[i][1]-wall[i][3];
            len2 = x*x+z*z;
            t = -1.0f*(x*(wall[i][0]-lbl_1_bss_16A84[player].pos.x)+z*(wall[i][1]-lbl_1_bss_16A84[player].pos.z));
            if(len2) {
                t2 = t/len2;
            } else {
                t2 = 0.0f;
            }
            cx = x*t2+wall[i][0];
            cz = z*t2+wall[i][1];
            x = lbl_1_bss_16A84[player].pos.x-cx;
            z = lbl_1_bss_16A84[player].pos.z-cz;
            dist = sqrt(x*x+z*z);
            if(dist < radius) {
                if(dist) {
                    scale = radius/dist;
                } else {
                    scale = 0.0f;
                }
                x = x*scale*wallSign[i];
                z = z*scale*wallSign[i];
                lbl_1_bss_16A84[player].pos.x = cx+x;
                lbl_1_bss_16A84[player].pos.z = cz+z;
            }
        }
    }
    if(lbl_1_bss_16CB4.walkStage) {
        model[0] = &Hu3DData[lbl_1_bss_17A00->models[81].modelId];
        model[1] = &Hu3DData[lbl_1_bss_17A00->models[82].modelId];
        x = model[1]->pos.x-model[0]->pos.x;
        z = model[1]->pos.z-model[0]->pos.z;
        dist = sqrt(x*x+z*z);
        if(dist < 75.0f) {
            if(dist <= 1.0f) {
                dist = 1.0f;
            }
            scale = 70.0f/dist;
            x *= scale;
            z *= scale;
            if(lbl_1_bss_16CB4.walkStage == 1) {
                model[0]->pos.x = model[1]->pos.x-x;
                model[0]->pos.z = model[1]->pos.z-z;
            } else {
                model[1]->pos.x = model[0]->pos.x+x;
                model[1]->pos.z = model[0]->pos.z+z;
            }
            lbl_1_bss_16CB4.walkTimer++;
        } else {
            lbl_1_bss_16CB4.walkTimer = 0;
        }
    }
}

/* Twenty-five floats nothing reads. */
float lbl_1_data_684[25] = {
    0.0f, 0.0f, 0.0f, 0.0f, 913.0f,
    0.0f, -1177.0f, 993.0f, 0.0f, -1038.0f,
    550.0f, 1000.0f, -3250.0f, 593.0f, 312.0f,
    -1119.0f, -462.0f, 330.0f, -1100.0f, -1000.0f,
    40.0f, -2100.0f, -2500.0f, 0.0f, -3900.0f
};
