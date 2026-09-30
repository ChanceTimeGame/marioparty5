/*
 * m555dll/game.c -- the duel itself. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m555Dll/asm/REL/m555Dll/game.s.
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
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"

#include "datadir_enum.h"

#include "REL/m555Dll/m555.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"


void fn_1_3010(M555_WORK *work);
s16 fn_1_69C4(M555_WORK *work);
s16 fn_1_6A0C(void);
s16 fn_1_6A60(void);
s16 fn_1_6AF0(void);
s16 fn_1_6DF0(void);
s16 fn_1_6ECC(void);
s16 fn_1_6F3C(void);
s16 fn_1_71B4(void);
s16 fn_1_7364(void);
void fn_1_73A4(void);
void fn_1_7840(void);
void fn_1_78DC(void);
void fn_1_7D88(s16 player);
void fn_1_8928(s16 player);
s16 fn_1_8F4C(s16 player);
void fn_1_90C4(void);
void fn_1_9B8C(void);
void fn_1_A758(void);
void fn_1_CFB8(void);
s16 fn_1_FB2C(void);
s16 fn_1_FD64(void);
s16 fn_1_103D8(s16 player);
s16 fn_1_10E20(void);
s16 fn_1_119EC(void);
void fn_1_11DFC(s16 player);
void fn_1_12CAC(s16 player);
void fn_1_12E04(void);
s16 fn_1_130D8(void);
s16 fn_1_13430(void);
void fn_1_14420(void);
void fn_1_152D8(s16 player);
s16 fn_1_155DC(s16 player);
s16 fn_1_15CF4(s16 player);
s16 fn_1_16104(s16 player);
s16 fn_1_16958(s16 player);
s16 fn_1_171C8(s16 player, float dist);
s16 fn_1_17400(HuVecF pos, float dist, float minZ);
void fn_1_176C4(s16 player);
s16 fn_1_19C0C(s16 player);
s16 fn_1_1A4B0(s16 player);
s16 fn_1_1A6F4(s16 player);
s16 fn_1_1A880(s16 player, s16 mode);

/* --- .bss --- */

s32 lbl_1_bss_3034;                /* unreferenced; dtk sizes lbl_1_bss_3030 8 */
M555_WORK *lbl_1_bss_3030;

char lbl_1_data_2D0[] = "itemhook_sao";

/* asm 9-3771, 3,693 insns. Reset the game state and build every stage model. */
void fn_1_3010(M555_WORK *work)
{
    s16 tbl[50];
    float posX[10];
    DS_PLAYER *pl;
    s16 i;
    s16 j;
    s16 k;

    memset(&lbl_1_bss_1894, 0, sizeof(M555_GAME));
    memset(lbl_1_bss_120C, 0, sizeof(lbl_1_bss_120C));
    memset(&lbl_1_bss_11E4, 0, sizeof(M555_UNK11E4));
    memset(&lbl_1_bss_11C8, 0, sizeof(M555_UNK11C8));
    memset(lbl_1_bss_B88, 0, sizeof(lbl_1_bss_B88));
    memset(&lbl_1_bss_B74, 0, sizeof(M555_UNKB74));
    memset(lbl_1_bss_214, 0, sizeof(lbl_1_bss_214));
    memset(&lbl_1_bss_C, 0, sizeof(M555_UNK0C));
    lbl_1_bss_3030 = work;
    for(i=0; i<12; i++) {
        lbl_1_bss_1894.seF[i] = -1;
    }
    lbl_1_bss_120C[0].unk01A = 1;
    lbl_1_bss_120C[1].unk01A = 1;
    lbl_1_bss_120C[0].unk014 = 5;
    lbl_1_bss_120C[1].unk014 = 5;
    for(i=0, j=0; i<=1; i++, j++) {
        lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 0);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        if(i == 1) {
            Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
        }
    }
    for(i=2, j=0; i<=5; i++, j++) {
        if(i == 2) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[2], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[2].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=6, j=0; i<=9; i++, j++) {
        if(i == 6) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[3], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[6].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=10, j=0; i<=13; i++, j++) {
        if(i == 10) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[4], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[10].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=14, j=0; i<=17; i++, j++) {
        if(i == 14) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[6], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[14].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=18, j=0; i<=21; i++, j++) {
        if(i == 18) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[8], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[18].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=22, j=0; i<=25; i++, j++) {
        if(i == 22) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[9], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[22].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    lbl_1_bss_3030->models[28].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[10], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3030->models[28].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3030->models[28].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_3030->models[28].modelId, 2);
    lbl_1_bss_3030->models[28].pos.x = 0.0f;
    lbl_1_bss_3030->models[28].pos.y = 0.0f;
    lbl_1_bss_3030->models[28].pos.z = 0.0f;
    lbl_1_bss_3030->models[28].rot.x = 0.0f;
    lbl_1_bss_3030->models[28].rot.y = 0.0f;
    lbl_1_bss_3030->models[28].rot.z = 0.0f;
    Hu3DMotionTimeSet(lbl_1_bss_3030->models[28].modelId, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[28].modelId, 0.0f);
    for(i=29, j=0; i<=32; i++, j++) {
        if(i == 29) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[11], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[29].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=96, j=0; i<=97; i++, j++) {
        if(i == 96) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[46], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[96].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 0);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        tbl[0] = Hu3DJointMotion(lbl_1_bss_3030->models[i].modelId, HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x31), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DMotionSet(lbl_1_bss_3030->models[i].modelId, tbl[0]);
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=98, j=0; i<=99; i++, j++) {
        if(i == 98) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[47], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[98].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 0);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        tbl[0] = Hu3DJointMotion(lbl_1_bss_3030->models[i].modelId, HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x32), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DMotionSet(lbl_1_bss_3030->models[i].modelId, tbl[0]);
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    lbl_1_bss_1894.unk144 = Hu3DJointMotion(lbl_1_bss_3030->models[98].modelId, HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x33), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1894.unk146 = Hu3DJointMotion(lbl_1_bss_3030->models[99].modelId, HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x33), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i=33, j=12, k=0; i<=34; i++, j++, k++) {
        lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[j], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 0);
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_3030->models[i].pos.x = -200.0f+(400.0f*k);
        lbl_1_bss_3030->models[i].pos.y = -100.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 180.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.5f);
    }
    for(i=35, j=0; i<=84; i++, j++) {
        if(i == 35) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[14], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[35].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = -10000.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
    }
    for(i=85; i<=87; i++) {
        if(i == 85) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[15], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[85].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
    }
    for(i=88; i<=92; i++) {
        if(i == 88) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[16], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[88].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    lbl_1_bss_3030->models[93].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[17], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3030->models[93].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3030->models[93].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_3030->models[93].modelId, 2);
    lbl_1_bss_3030->models[93].pos.x = 0.0f;
    lbl_1_bss_3030->models[93].pos.y = 0.0f;
    lbl_1_bss_3030->models[93].pos.z = 0.0f;
    lbl_1_bss_3030->models[93].rot.x = 0.0f;
    lbl_1_bss_3030->models[93].rot.y = 0.0f;
    lbl_1_bss_3030->models[93].rot.z = 0.0f;
    Hu3DModelAttrReset(lbl_1_bss_3030->models[93].modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_3030->models[93].modelId, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[93].modelId, 0.0f);
    lbl_1_bss_3030->models[94].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[18], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3030->models[94].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3030->models[94].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_3030->models[94].modelId, 0);
    lbl_1_bss_3030->models[94].pos.x = 0.0f;
    lbl_1_bss_3030->models[94].pos.y = 0.0f;
    lbl_1_bss_3030->models[94].pos.z = 0.0f;
    lbl_1_bss_3030->models[94].rot.x = 0.0f;
    lbl_1_bss_3030->models[94].rot.y = 0.0f;
    lbl_1_bss_3030->models[94].rot.z = 0.0f;
    Hu3DModelAttrReset(lbl_1_bss_3030->models[94].modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_3030->models[94].modelId, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[94].modelId, 0.0f);
    lbl_1_bss_3030->models[95].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[45], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3030->models[95].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3030->models[95].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_3030->models[95].modelId, 0);
    lbl_1_bss_3030->models[95].pos.x = 0.0f;
    lbl_1_bss_3030->models[95].pos.y = 30.0f;
    lbl_1_bss_3030->models[95].pos.z = -200.0f;
    lbl_1_bss_3030->models[95].rot.x = 0.0f;
    lbl_1_bss_3030->models[95].rot.y = 0.0f;
    lbl_1_bss_3030->models[95].rot.z = 0.0f;
    Hu3DModelAttrReset(lbl_1_bss_3030->models[95].modelId, HU3D_ATTR_DISPOFF);
    lbl_1_bss_11E4.unk008 = Hu3DJointMotion(lbl_1_bss_3030->models[95].modelId, HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x30), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(lbl_1_bss_3030->models[95].modelId, lbl_1_bss_11E4.unk008);
    Hu3DModelAttrSet(lbl_1_bss_3030->models[95].modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionTimeSet(lbl_1_bss_3030->models[95].modelId, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[95].modelId, 1.0f);
    Hu3DModelHookSet(lbl_1_bss_3030->models[95].modelId, lbl_1_data_2D0, lbl_1_bss_3030->models[94].modelId);
    tbl[0] = 19;
    tbl[1] = 19;
    tbl[2] = 20;
    tbl[3] = 20;
    tbl[4] = 21;
    tbl[5] = 21;
    tbl[6] = 23;
    tbl[7] = 23;
    tbl[8] = 24;
    tbl[9] = 24;
    for(i=100, j=0; i<=109; i++, j++) {
        lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[tbl[j]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 3);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 180.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    for(i=110; i<=159; i++) {
        if(i == 110) {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[22], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            lbl_1_bss_3030->models[i].modelId = Hu3DModelLink(lbl_1_bss_3030->models[110].modelId);
        }
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 3);
        lbl_1_bss_3030->models[i].pos.x = 0.0f;
        lbl_1_bss_3030->models[i].pos.y = 0.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
    }
    tbl[0] = lbl_1_bss_3030->chr[0].charNo+32;
    tbl[1] = lbl_1_bss_3030->chr[1].charNo+32;
    tbl[2] = 29;
    tbl[3] = 30;
    tbl[4] = 27;
    tbl[5] = 28;
    tbl[6] = 25;
    tbl[7] = 26;
    posX[0] = -568.0f;
    posX[1] = 568.0f;
    posX[2] = -520.0f;
    posX[3] = 520.0f;
    posX[4] = -520.0f;
    posX[5] = 520.0f;
    posX[6] = -520.0f;
    posX[7] = 520.0f;
    for(i=161, j=0; i<=168; i++, j++) {
        lbl_1_bss_3030->models[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[tbl[j]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(lbl_1_bss_3030->models[i].modelId, 1);
        if(i == 167 || i == 168) {
            Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 7);
        } else {
            Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 6);
        }
        lbl_1_bss_3030->models[i].pos.x = posX[j];
        lbl_1_bss_3030->models[i].pos.y = -364.0f;
        lbl_1_bss_3030->models[i].pos.z = 0.0f;
        lbl_1_bss_3030->models[i].rot.x = 0.0f;
        lbl_1_bss_3030->models[i].rot.y = 0.0f;
        lbl_1_bss_3030->models[i].rot.z = 0.0f;
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_ZCMP_OFF);
        if(i == 165 || i == 166) {
            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
        }
    }
    lbl_1_bss_3030->models[160].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_3030->stageDataTbl[31], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_3030->models[160].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_3030->models[160].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_3030->models[160].modelId, 6);
    lbl_1_bss_3030->models[160].pos.x = 0.0f;
    lbl_1_bss_3030->models[160].pos.y = 0.0f;
    lbl_1_bss_3030->models[160].pos.z = 0.0f;
    lbl_1_bss_3030->models[160].rot.x = 0.0f;
    lbl_1_bss_3030->models[160].rot.y = 0.0f;
    lbl_1_bss_3030->models[160].rot.z = 0.0f;
    Hu3DMotionTimeSet(lbl_1_bss_3030->models[160].modelId, 0.0f);
    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[160].modelId, 0.0f);
    pl = &lbl_1_bss_3030->player[0];
    pl->motNo = 0;
    pl->speed = 1.0f;
    pl->time = 0.0f;
    pl->attr = HU3D_MOTATTR_LOOP;
    pl->attrReset = 0;
    pl = &lbl_1_bss_3030->player[1];
    pl->motNo = 0;
    pl->speed = 1.0f;
    pl->time = 0.0f;
    pl->attr = HU3D_MOTATTR_LOOP;
    pl->attrReset = 0;
    fn_1_152D8(0);
    fn_1_152D8(1);
    lbl_1_bss_1894.unk182 = 1;
    lbl_1_bss_1894.unk180 = 0;
    lbl_1_bss_1894.unk184 = 10000.0f;
    lbl_1_bss_1894.unk188 = 23000.0f;
    lbl_1_bss_1894.unk18C = 255;
    lbl_1_bss_1894.unk18D = 255;
    lbl_1_bss_1894.unk18E = 255;
    fn_1_247C();
    fn_1_7840();
    fn_1_78DC();
}

/* asm 3774-3793, 18 insns. Init hook body. */
s16 fn_1_69C4(M555_WORK *work)
{
    s16 result = 1;

    fn_1_3010(work);
    lbl_1_bss_1894.unk00C = 0;
    return result;
}

/* asm 3796-3818, 21 insns. Fade-in hook body. */
s16 fn_1_6A0C(void)
{
    s16 result;

    result = 0;
    result = (s32)fn_1_130D8();
    fn_1_A758();
    fn_1_9B8C();
    fn_1_CFB8();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 1;
    return result;
}

/* asm 3821-3858, 36 insns. Start hook body. */
s16 fn_1_6A60(void)
{
    s16 result;

    result = 0;
    fn_1_FB2C();
    lbl_1_bss_1894.unk000 = 0;
    lbl_1_bss_1894.unk002 = 0;
    lbl_1_bss_1894.unk004 = 0;
    lbl_1_bss_1894.unk006 = 0;
    fn_1_A758();
    fn_1_9B8C();
    fn_1_CFB8();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 2;
    return result;
}

/* asm 3861-4071, 192 insns. Main hook body: the duel, then the winner. */
s16 fn_1_6AF0(void)
{
    s16 i;
    s16 done;
    s16 result;
    int playerNo;

    result = 0;
    done = 0;
    lbl_1_bss_1894.unk008++;
    switch(lbl_1_bss_1894.unk000) {
        case 0:
            done = 1;
            done = fn_1_FB2C();
            if(done) {
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 1:
            for(i=0; i<2; i++) {
                if(lbl_1_bss_120C[i].unk052) {
                    fn_1_155DC(i);
                }
            }
            for(i=0; i<2; i++) {
                fn_1_8F4C(i);
            }
            if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk02A) {
                if(lbl_1_bss_1894.unk028 == 0) {
                    if(lbl_1_bss_120C[0].unk014 > lbl_1_bss_120C[1].unk014) {
                        lbl_1_bss_1894.unk028 = 2;
                    } else if(lbl_1_bss_120C[0].unk014 < lbl_1_bss_120C[1].unk014) {
                        lbl_1_bss_1894.unk028 = 1;
                    } else {
                        lbl_1_bss_1894.unk028 = 0;
                    }
                    lbl_1_bss_1894.unk040 = 1;
                }
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 2:
            if(lbl_1_bss_1894.unk028) {
                MgSeqWinnerSet(lbl_1_bss_3030->chr[lbl_1_bss_1894.unk028&1].charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
                playerNo = lbl_1_bss_3030->chr[lbl_1_bss_1894.unk028&1].no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[playerNo].mgCoinBonus = 10;
                }
            } else {
                MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            }
            fn_1_2A48(1, 100);
            result = 1;
            break;
    }
    fn_1_A758();
    fn_1_90C4();
    fn_1_9B8C();
    fn_1_CFB8();
    fn_1_14420();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 3;
    return result;
}

/* asm 4074-4130, 55 insns. Finish hook body. */
s16 fn_1_6DF0(void)
{
    s16 result;

    result = 0;
    lbl_1_bss_1894.unk000 = 0;
    lbl_1_bss_1894.unk002 = 0;
    lbl_1_bss_1894.unk004 = 0;
    lbl_1_bss_1894.unk006 = 0;
    lbl_1_bss_3030->mode[0] = 0;
    lbl_1_bss_120C[0].unk002 = 0;
    lbl_1_bss_120C[1].unk002 = 0;
    fn_1_8F4C(0);
    fn_1_8F4C(1);
    fn_1_A758();
    fn_1_90C4();
    fn_1_9B8C();
    fn_1_CFB8();
    fn_1_14420();
    fn_1_12E04();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 4;
    return result;
}

/* asm 4133-4162, 28 insns. Pre-winner hook body. */
s16 fn_1_6ECC(void)
{
    s16 result;

    result = 0;
    result = (s32)fn_1_13430();
    fn_1_8F4C(0);
    fn_1_8F4C(1);
    fn_1_A758();
    fn_1_90C4();
    fn_1_9B8C();
    fn_1_CFB8();
    fn_1_14420();
    fn_1_12E04();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 5;
    return result;
}

/* asm 4165-4332, 158 insns. Winner hook body. */
s16 fn_1_6F3C(void)
{
    DS_PLAYER *pl;
    s16 result;

    result = 0;
    if(lbl_1_bss_3030->mode[0] == 0) {
        if(lbl_1_bss_1894.unk028) {
            pl = &lbl_1_bss_3030->player[lbl_1_bss_1894.unk028&1];
            pl->motNo = 1;
            pl->speed = 1.0f;
            pl->time = 0.0f;
            pl->attr = 0;
            pl->attrReset = HU3D_MOTATTR_LOOP;
        }
        lbl_1_bss_3030->mode[0] = 1;
    } else if(lbl_1_bss_1894.unk028) {
        if(lbl_1_bss_1894.unk02C == 0) {
            CharFXPlay(lbl_1_bss_3030->chr[lbl_1_bss_1894.unk028&1].charNo, 506);
            lbl_1_bss_1894.unk02C = 1;
        }
        pl = &lbl_1_bss_3030->player[lbl_1_bss_1894.unk028&1];
        if(pl->time >= 38.0f) {
            pl->time = 10.0f;
        }
    }
    if(lbl_1_bss_1894.unk028 == 0) {
        fn_1_119EC();
    }
    if(lbl_1_bss_1894.unk028) {
        fn_1_103D8(lbl_1_bss_1894.unk028>>1);
    }
    if(lbl_1_bss_1894.unk028) {
        fn_1_12CAC(lbl_1_bss_1894.unk028&1);
    }
    if(lbl_1_bss_1894.unk040 && lbl_1_bss_1894.unk028) {
        fn_1_11DFC(lbl_1_bss_1894.unk028&1);
    }
    fn_1_8F4C(0);
    fn_1_8F4C(1);
    fn_1_A758();
    fn_1_CFB8();
    fn_1_12E04();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 6;
    return result;
}

/* asm 4335-4450, 108 insns. Fade-out hook body. */
s16 fn_1_71B4(void)
{
    DS_PLAYER *pl;
    s16 result;

    result = 1;
    if(lbl_1_bss_1894.unk028) {
        pl = &lbl_1_bss_3030->player[lbl_1_bss_1894.unk028&1];
        if(pl->time >= 38.0f) {
            pl->time = 10.0f;
        }
    }
    if(lbl_1_bss_3030->mode[0] == 1) {
        fn_1_2E60(11, 100);
        lbl_1_bss_3030->mode[0] = 2;
    }
    if(lbl_1_bss_1894.unk028 == 0) {
        fn_1_119EC();
    }
    if(lbl_1_bss_1894.unk028) {
        fn_1_12CAC(lbl_1_bss_1894.unk028&1);
    }
    if(lbl_1_bss_1894.unk028) {
        fn_1_103D8(lbl_1_bss_1894.unk028>>1);
    }
    if(lbl_1_bss_1894.unk040 && lbl_1_bss_1894.unk028) {
        fn_1_11DFC(lbl_1_bss_1894.unk028&1);
    }
    fn_1_8F4C(0);
    fn_1_8F4C(1);
    fn_1_A758();
    fn_1_CFB8();
    fn_1_78DC();
    lbl_1_bss_1894.unk00C = 7;
    return result;
}

/* asm 4453-4470, 16 insns. Close hook body. */
s16 fn_1_7364(void)
{
    s16 result;

    result = 1;
    fn_1_2FF0();
    lbl_1_bss_1894.unk00C = 8;
    return result;
}

/* asm 4473-4777, 295 insns. Unreferenced: fn_1_78DC without the camera, light and shadow updates. */
void fn_1_73A4(void)
{
    s16 i;

    lbl_1_bss_3030->models[0].rot.y -= 0.005f;
    for(i=0; i<171; i++) {
        Hu3DModelPosSet(lbl_1_bss_3030->models[i].modelId, lbl_1_bss_3030->models[i].pos.x, lbl_1_bss_3030->models[i].pos.y, lbl_1_bss_3030->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_3030->models[i].modelId, lbl_1_bss_3030->models[i].rot.x, lbl_1_bss_3030->models[i].rot.y, lbl_1_bss_3030->models[i].rot.z);
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_3030->chr[i].charNo == 6) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y, 15.0f+lbl_1_bss_3030->models[i+169].pos.z);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 8) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y-20.0f, lbl_1_bss_3030->models[i+169].pos.z-20.0f);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 7) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, 10.0f+lbl_1_bss_3030->models[i+169].pos.y, lbl_1_bss_3030->models[i+169].pos.z);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 4) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y, 20.0f+lbl_1_bss_3030->models[i+169].pos.z);
        }
    }
}

/* asm 4780-4822, 39 insns. Apply or clear the fog when it changed. */
void fn_1_7840(void)
{
    if(lbl_1_bss_1894.unk182) {
        if(lbl_1_bss_1894.unk180) {
            Hu3DFogSet(lbl_1_bss_1894.unk184, lbl_1_bss_1894.unk188, lbl_1_bss_1894.unk18C, lbl_1_bss_1894.unk18D, lbl_1_bss_1894.unk18E);
        } else {
            Hu3DFogClear();
        }
    }
    lbl_1_bss_1894.unk182 = 0;
}

/* asm 4825-5133, 299 insns. Push every model to Hu3D, nudge the duellists by character, then the camera, light and shadow. */
void fn_1_78DC(void)
{
    s16 i;

    lbl_1_bss_3030->models[0].rot.y -= 0.005f;
    for(i=0; i<171; i++) {
        Hu3DModelPosSet(lbl_1_bss_3030->models[i].modelId, lbl_1_bss_3030->models[i].pos.x, lbl_1_bss_3030->models[i].pos.y, lbl_1_bss_3030->models[i].pos.z);
        Hu3DModelRotSet(lbl_1_bss_3030->models[i].modelId, lbl_1_bss_3030->models[i].rot.x, lbl_1_bss_3030->models[i].rot.y, lbl_1_bss_3030->models[i].rot.z);
    }
    for(i=0; i<2; i++) {
        if(lbl_1_bss_3030->chr[i].charNo == 6) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y, 15.0f+lbl_1_bss_3030->models[i+169].pos.z);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 8) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y-20.0f, lbl_1_bss_3030->models[i+169].pos.z-20.0f);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 7) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, 10.0f+lbl_1_bss_3030->models[i+169].pos.y, lbl_1_bss_3030->models[i+169].pos.z);
        }
        if(lbl_1_bss_3030->chr[i].charNo == 4) {
            Hu3DModelPosSet(lbl_1_bss_3030->models[i+169].modelId, lbl_1_bss_3030->models[i+169].pos.x, lbl_1_bss_3030->models[i+169].pos.y, 20.0f+lbl_1_bss_3030->models[i+169].pos.z);
        }
    }
    fn_1_964(0);
    fn_1_110C();
    fn_1_150C();
}

/* asm 5136-5900, 744 insns. The tilt of duellist player's two models from the sticks. */
void fn_1_7D88(s16 player)
{
    HuVecF *pos;
    HuVecF *pos2;
    HuVecF *rot;
    HuVecF *rot2;
    float step;
    float back;

    pos = &lbl_1_bss_3030->models[player+169].pos;
    pos2 = &lbl_1_bss_3030->models[player+33].pos;
    rot = &lbl_1_bss_3030->models[player+169].rot;
    rot2 = &lbl_1_bss_3030->models[player+33].rot;
    if(lbl_1_bss_120C[player].unk00C && lbl_1_bss_120C[player].unk00E == 0) {
        memset(&lbl_1_bss_3030->chr[player].btn, 0, 20);
    }
    if(lbl_1_bss_3030->chr[player].stkX > 0) {
        step = 6.0f*(lbl_1_bss_3030->chr[player].stkX/56.0f);
        if((lbl_1_bss_120C[player].unk020 += step) > 90.0f) {
            lbl_1_bss_120C[player].unk020 = 90.0f;
        }
    } else if(lbl_1_bss_3030->chr[player].stkX < 0) {
        step = 6.0f*(lbl_1_bss_3030->chr[player].stkX/56.0f);
        if((lbl_1_bss_120C[player].unk020 += step) < -90.0f) {
            lbl_1_bss_120C[player].unk020 = -90.0f;
        }
    }
    if(lbl_1_bss_3030->chr[player].stkY > 0) {
        step = 6.0f*(lbl_1_bss_3030->chr[player].stkY/56.0f);
        if(lbl_1_bss_120C[player].unk01A) {
            step *= -1.0f;
            if((lbl_1_bss_120C[player].unk024 += step) < -90.0f) {
                lbl_1_bss_120C[player].unk024 = -90.0f;
            }
        } else {
            if((lbl_1_bss_120C[player].unk024 += step) > 90.0f) {
                lbl_1_bss_120C[player].unk024 = 90.0f;
            }
        }
    } else if(lbl_1_bss_3030->chr[player].stkY < 0) {
        step = 6.0f*(lbl_1_bss_3030->chr[player].stkY/56.0f);
        if(lbl_1_bss_120C[player].unk01A) {
            step *= -1.0f;
            if((lbl_1_bss_120C[player].unk024 += step) > 90.0f) {
                lbl_1_bss_120C[player].unk024 = 90.0f;
            }
        } else {
            if((lbl_1_bss_120C[player].unk024 += step) < -90.0f) {
                lbl_1_bss_120C[player].unk024 = -90.0f;
            }
        }
    }
    if(lbl_1_bss_3030->chr[player].stkX == 0) {
        if(lbl_1_bss_120C[player].unk020 > 0.0f) {
            if(lbl_1_bss_120C[player].unk020 >= 2.5f) {
                back = -2.5f;
            } else {
                back = -lbl_1_bss_120C[player].unk020;
            }
        } else if(lbl_1_bss_120C[player].unk020 < 0.0f) {
            if(lbl_1_bss_120C[player].unk020 <= -2.5f) {
                back = 2.5f;
            } else {
                back = -lbl_1_bss_120C[player].unk020;
            }
        } else {
            back = 0.0f;
        }
        lbl_1_bss_120C[player].unk020 += back;
    }
    if(lbl_1_bss_3030->chr[player].stkY == 0) {
        if(lbl_1_bss_120C[player].unk024 > 0.0f) {
            if(lbl_1_bss_120C[player].unk024 >= 2.5f) {
                back = -2.5f;
            } else {
                back = -lbl_1_bss_120C[player].unk024;
            }
        } else if(lbl_1_bss_120C[player].unk024 < 0.0f) {
            if(lbl_1_bss_120C[player].unk024 <= -2.5f) {
                back = 2.5f;
            } else {
                back = -lbl_1_bss_120C[player].unk024;
            }
        } else {
            back = 0.0f;
        }
        lbl_1_bss_120C[player].unk024 += back;
    }
    pos->x += 10.0*sin((M_PI*lbl_1_bss_120C[player].unk020)/180.0);
    pos->y += 10.0*sin((M_PI*lbl_1_bss_120C[player].unk024)/180.0);
    pos2->x += 10.0*sin((M_PI*lbl_1_bss_120C[player].unk020)/180.0);
    pos2->y += 10.0*sin((M_PI*lbl_1_bss_120C[player].unk024)/180.0);
    rot->z = -(30.0*sin((M_PI*lbl_1_bss_120C[player].unk020)/180.0));
    rot->x = -(30.0*sin((M_PI*lbl_1_bss_120C[player].unk024)/180.0));
    rot2->z = -(30.0*sin((M_PI*lbl_1_bss_120C[player].unk020)/180.0));
    rot2->x = -(30.0*sin((M_PI*lbl_1_bss_120C[player].unk024)/180.0));
}

/* asm 5903-6308, 393 insns. */
void fn_1_8928(s16 player)
{
    s16 no;
    s16 pan;
    float x;
    float time;

    switch(lbl_1_bss_120C[player].unk010) {
        case 0:
            if(lbl_1_bss_120C[player].unk012) {
                lbl_1_bss_120C[player].unk016 = 0;
                lbl_1_bss_120C[player].unk010++;
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[player+165].modelId, 1.0f);
                omVibrate(lbl_1_bss_3030->chr[player].no, 20, 12, 0);
                no = 5-lbl_1_bss_120C[player].unk014;
                if(no == 4) {
                    x = 0.05818182f*lbl_1_bss_3030->models[player+169].pos.x;
                    pan = 64.0f+x;
                    fn_1_2BD8(player+6, 127, pan);
                }
            }
            break;

        case 1:
            if(Hu3DModelAttrGet(lbl_1_bss_3030->models[player+169].modelId) & HU3D_ATTR_DISPOFF) {
                Hu3DModelAttrReset(lbl_1_bss_3030->models[player+33].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[player+169].modelId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(lbl_1_bss_3030->models[player+33].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[player+169].modelId, HU3D_ATTR_DISPOFF);
            }
            time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[player+165].modelId);
            no = 5-lbl_1_bss_120C[player].unk014;
            if(no != 5 && time >= 14.9f*no) {
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[player+165].modelId, 15.0f*no);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[player+165].modelId, 0.0f);
            }
            if(lbl_1_bss_120C[player].unk016++ >= 120) {
                Hu3DModelAttrReset(lbl_1_bss_3030->models[player+33].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[player+169].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_120C[player].unk012 = 0;
                lbl_1_bss_120C[player].unk010 = 0;
            }
            break;
    }
    no = 5-lbl_1_bss_120C[player].unk014;
    if(no == 4) {
        if(lbl_1_bss_1894.unk00C <= 3) {
            x = 0.05818182f*lbl_1_bss_3030->models[player+33].pos.x;
            pan = 64.0f+x;
            fn_1_2CB0(player+6, pan);
        }
        if(lbl_1_bss_1894.unk00C == 4 && lbl_1_bss_120C[player].unk014 == 1) {
            fn_1_2E60(player+6, 100);
        }
        if(lbl_1_bss_120C[player].unk018++ >= 2) {
            if(Hu3DModelAttrGet(lbl_1_bss_3030->models[player+165].modelId) & HU3D_ATTR_DISPOFF) {
                Hu3DModelAttrReset(lbl_1_bss_3030->models[player+165].modelId, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrSet(lbl_1_bss_3030->models[player+165].modelId, HU3D_ATTR_DISPOFF);
            }
            lbl_1_bss_120C[player].unk018 = 0;
        }
    }
}

/* asm 6311-6409, 94 insns. */
s16 fn_1_8F4C(s16 player)
{
    s16 result;
    s16 pan;
    float x;

    result = 0;
    if((lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk02A) && lbl_1_bss_120C[player].unk00E == 0) {
        memset(&lbl_1_bss_3030->chr[player].btn, 0, 20);
    }
    fn_1_7D88(player);
    fn_1_8928(player);
    if(lbl_1_bss_120C[player].unk014 > 0 && lbl_1_bss_1894.unk00C <= 3 && lbl_1_bss_1894.unk036 == 0) {
        x = 0.05818182f*lbl_1_bss_3030->models[player+33].pos.x;
        pan = 64.0f+x;
        fn_1_2CB0(player+2, pan);
    }
    return result;
}

/* asm 6412-7138, 690 insns. */
void fn_1_90C4(void)
{
    s16 i;
    s16 mdlNo;
    s16 j;
    s16 area;
    s16 cnt;
    s16 rangeX = 354;
    s16 rangeY = 316;
    s16 resetF = 0;
    s16 limit[6] = { 3, 3, 3, 3, 3, 3 };
    float areaTbl[6][4] = {
        { -550.0f, -217.0f, -336.0f, -20.0f },
        { -550.0f, -217.0f, 20.0f, 336.0f },
        { -177.0f, 177.0f, -336.0f, -20.0f },
        { -177.0f, 177.0f, 20.0f, 336.0f },
        { 217.0f, 550.0f, -336.0f, -20.0f },
        { 217.0f, 550.0f, 20.0f, 336.0f }
    };

    lbl_1_bss_11C8.unk002++;
    switch(lbl_1_bss_11C8.unk000) {
        case 0:
            lbl_1_bss_11C8.unk018 = 0;
            lbl_1_bss_11C8.unk006 = 0;
            lbl_1_bss_11C8.unk004 = 30;
            lbl_1_bss_11C8.unk008 = 40;
            lbl_1_bss_11C8.unk00A = 0;
            lbl_1_bss_11C8.unk000++;
            break;

        case 1:
            if(lbl_1_bss_1894.unk028) {
                lbl_1_bss_11C8.unk000 = 4;
            } else if(lbl_1_bss_1894.unk008 >= 1800) {
                lbl_1_bss_11C8.unk000 = 3;
            } else {
                if(lbl_1_bss_11C8.unk00A++ > lbl_1_bss_11C8.unk008) {
                    if(lbl_1_bss_11C8.unk004-- <= 2) {
                        lbl_1_bss_11C8.unk004 = 2;
                    }
                    lbl_1_bss_11C8.unk00A = 0;
                }
                if(lbl_1_bss_11C8.unk006++ > lbl_1_bss_11C8.unk004) {
                    for(i=0; i<50; i++) {
                        if(lbl_1_bss_B88[i].unk000 == 0) {
                            mdlNo = i+35;
                            lbl_1_bss_B88[i].unk000 = 1;
                            lbl_1_bss_B88[i].unk002 = 0;
                            lbl_1_bss_B88[i].unk01C = 1.0f;
                            lbl_1_bss_B88[i].unk00C = 200.0f;
                            do {
                                area = frandmod(6);
                            } while(lbl_1_bss_11C8.unk00C[area] >= limit[area]);
                            lbl_1_bss_11C8.unk00C[area]++;
                            for(j=0, cnt=0; j<6; j++) {
                                if(lbl_1_bss_11C8.unk00C[j] == limit[j]) {
                                    cnt++;
                                }
                            }
                            if(cnt >= 6) {
                                for(j=0; j<6; j++) {
                                    lbl_1_bss_11C8.unk00C[j] = 0;
                                }
                                resetF = 1;
                            }
                            lbl_1_bss_3030->models[mdlNo].pos.x = areaTbl[area][0]+frandmod(rangeX);
                            lbl_1_bss_3030->models[mdlNo].pos.y = areaTbl[area][2]+frandmod(rangeY);
                            lbl_1_bss_3030->models[mdlNo].pos.z = -37000.0f;
                            Hu3DModelAttrReset(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                            Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.0f);
                            Hu3DModelTPLvlSet(lbl_1_bss_3030->models[mdlNo].modelId, lbl_1_bss_B88[i].unk01C);
                            lbl_1_bss_11C8.unk006 = 0;
                            lbl_1_bss_11C8.unk018++;
                            break;
                        }
                    }
                }
            }
            break;

        case 2:
            for(i=0, j=0; i<50; i++) {
                if(lbl_1_bss_B88[i].unk000) {
                    j++;
                    if((lbl_1_bss_B88[i].unk01C -= 0.05f) <= 0.0f) {
                        lbl_1_bss_B88[i].unk01C = 0.0f;
                        lbl_1_bss_B88[i].unk000 = 0;
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[i+35].modelId, HU3D_ATTR_DISPOFF);
                    }
                    Hu3DModelTPLvlSet(lbl_1_bss_3030->models[i+35].modelId, lbl_1_bss_B88[i].unk01C);
                }
            }
            if(j == 0) {
                lbl_1_bss_11C8.unk000 = 4;
            }
            break;

        case 3:
            if(lbl_1_bss_1894.unk028) {
                lbl_1_bss_11C8.unk000 = 4;
            }
            break;

        case 4:
            break;
    }
    for(i=0; i<50; i++) {
        if(lbl_1_bss_B88[i].unk000) {
            mdlNo = i+35;
            lbl_1_bss_3030->models[mdlNo].pos.z += lbl_1_bss_B88[i].unk00C;
            lbl_1_bss_3030->models[mdlNo].rot.x += lbl_1_bss_B88[i].unk010;
            lbl_1_bss_3030->models[mdlNo].rot.y += lbl_1_bss_B88[i].unk014;
            switch(lbl_1_bss_B88[i].unk002) {
                case 0:
                    lbl_1_bss_B88[i].unk002++;
                    break;

                case 1:
                    if(lbl_1_bss_3030->models[mdlNo].pos.z >= 1500.0f) {
                        if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk02A || lbl_1_bss_B74.unk012) {
                            lbl_1_bss_B88[i].unk002++;
                        } else {
                            lbl_1_bss_B88[i].unk000 = 0;
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_11C8.unk018--;
                        }
                    } else if(lbl_1_bss_3030->models[mdlNo].pos.z >= 100.0f) {
                        lbl_1_bss_B88[i].unk01C = 0.3f;
                        Hu3DModelTPLvlSet(lbl_1_bss_3030->models[mdlNo].modelId, lbl_1_bss_B88[i].unk01C);
                    }
                    break;

                case 2:
                    if(lbl_1_bss_3030->models[mdlNo].pos.z >= 1500.0f) {
                        lbl_1_bss_B88[i].unk000 = 0;
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                        lbl_1_bss_11C8.unk018--;
                    }
                    break;
            }
        }
    }
}

/* asm 7141-7924, 755 insns. */
void fn_1_9B8C(void)
{
    s16 mdlNo;
    s16 i;
    float time;
    float speed;
    float speed2;

    if(lbl_1_bss_1894.unk026 == 0 && lbl_1_bss_1894.unk00C >= 2) {
        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[1].modelId, 4.0f);
        lbl_1_bss_1894.unk026 = 1;
    }
    if(lbl_1_bss_1894.unk00C >= 2) {
        speed2 = speed = 300.0f;
    } else {
        speed2 = speed = 100.0f;
    }
    for(mdlNo=85, i=0; mdlNo<=87; mdlNo++, i++) {
        switch(lbl_1_bss_B74.unk000[i]) {
            case 0:
                lbl_1_bss_3030->models[mdlNo].pos.x = 0.0f;
                lbl_1_bss_3030->models[mdlNo].pos.y = 0.0f;
                lbl_1_bss_3030->models[mdlNo].pos.z = -36000.0f+(12000.0f*i);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.5f);
                lbl_1_bss_B74.unk000[i] = 2;
                break;

            case 1:
                if((lbl_1_bss_3030->models[mdlNo].pos.z += speed) >= -36000.0f) {
                    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.5f);
                }
                time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                if(time >= 50.0f) {
                    lbl_1_bss_B74.unk000[i]++;
                }
                break;

            case 2:
                if((lbl_1_bss_3030->models[mdlNo].pos.z += speed) >= 1500.0f) {
                    lbl_1_bss_3030->models[mdlNo].pos.z = -36000.0f;
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                    lbl_1_bss_B74.unk000[i] = 1;
                    if(lbl_1_bss_1894.unk028) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                        lbl_1_bss_3030->models[mdlNo].pos.z = 1500.0f;
                        lbl_1_bss_B74.unk000[i] = 3;
                    } else if(lbl_1_bss_1894.unk008 >= 1760) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                        lbl_1_bss_B74.unk012 = 1;
                        lbl_1_bss_3030->models[mdlNo].pos.z = 1500.0f;
                        lbl_1_bss_B74.unk000[i] = 3;
                    }
                }
                time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                if(time >= 96.0f) {
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                }
                break;

            case 3:
                time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                if(time >= 96.0f) {
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                }
                if((lbl_1_bss_3030->models[mdlNo].pos.z += speed) >= 1500.0f) {
                    Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                    lbl_1_bss_B74.unk000[i]++;
                }
                break;

            case 4:
                break;
        }
    }
    if(lbl_1_bss_B74.unk012) {
        for(mdlNo=88, i=0; mdlNo<=93; mdlNo++, i++) {
            switch(lbl_1_bss_B74.unk006[i]) {
                case 0:
                    lbl_1_bss_3030->models[mdlNo].pos.x = 0.0f;
                    lbl_1_bss_3030->models[mdlNo].pos.y = 0.0f;
                    lbl_1_bss_3030->models[mdlNo].pos.z = -36000.0f-(5000.0f*i);
                    Hu3DModelAttrReset(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                    lbl_1_bss_B74.unk006[i]++;
                    break;

                case 1:
                    if((lbl_1_bss_3030->models[mdlNo].pos.z += 300.0f) >= -36000.0f) {
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.5f);
                    }
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                    if(time >= 50.0f) {
                        lbl_1_bss_B74.unk006[i]++;
                    }
                    break;

                case 2:
                    if((lbl_1_bss_3030->models[mdlNo].pos.z += 300.0f) >= 1500.0f) {
                        lbl_1_bss_B74.unk006[i]++;
                        if(mdlNo == 93) {
                            lbl_1_bss_1894.unk02A = 1;
                        }
                    }
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                    if(time >= 96.0f) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                    }
                    break;

                case 3:
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[mdlNo].modelId);
                    if(time >= 96.0f) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                    }
                    if((lbl_1_bss_3030->models[mdlNo].pos.z += 300.0f) >= 37000.0f) {
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 0.0f);
                    }
                    break;
            }
        }
    }
}

/* asm 7927-10586, 2,584 insns. Runs every live effect in lbl_1_bss_214 by its type and step. */
void fn_1_A758(void)
{
    float time;
    s16 i;
    s16 j;
    s16 k;

    for(i=0; i<100; i++) {
        if(lbl_1_bss_214[i].unk000 == 0) {
            continue;
        }
        switch(lbl_1_bss_214[i].unk006) {
            case 0:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        lbl_1_bss_214[i].unk002 = 1;
                        lbl_1_bss_214[i].unk008 = 100;
                        lbl_1_bss_214[i].unk00A = 0;
                        for(j=0; j<100; j++) {
                            if(lbl_1_bss_214[j].unk000 == 0) {
                                lbl_1_bss_214[j].unk000 = 1;
                                lbl_1_bss_214[j].unk002 = 1;
                                lbl_1_bss_214[j].unk006 = 0;
                                lbl_1_bss_214[j].unk008 = 101;
                                lbl_1_bss_214[j].unk00A = 1;
                                break;
                            }
                        }
                        if(i > j) {
                            break;
                        }

                    case 1:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 1.0f);
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 2:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time >= 49.0f) {
                            lbl_1_bss_214[i].unk002++;
                        }
                        break;

                    case 3:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time >= 97.0f) {
                            Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 50.0f);
                        }
                        if(Hu3DModelAttrGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].modelId) & HU3D_ATTR_DISPOFF) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        } else {
                            Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        }
                        break;

                    case 4:
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_REV);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 50.0f);
                        lbl_1_bss_214[i].unk002++;

                    case 5:
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time <= 2.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk002++;
                        }
                        break;

                    case 6:
                        break;
                }
                break;

            case 1:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        lbl_1_bss_214[i].unk002 = 1;
                        lbl_1_bss_214[i].unk008 = 102;
                        lbl_1_bss_214[i].unk00A = 0;
                        for(j=0; j<100; j++) {
                            if(lbl_1_bss_214[j].unk000 == 0) {
                                lbl_1_bss_214[j].unk000 = 1;
                                lbl_1_bss_214[j].unk002 = 1;
                                lbl_1_bss_214[j].unk006 = 1;
                                lbl_1_bss_214[j].unk008 = 103;
                                lbl_1_bss_214[j].unk00A = 1;
                                break;
                            }
                        }
                        if(i > j) {
                            break;
                        }

                    case 1:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.7f);
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 2:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time >= 98.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk000 = 0;
                            lbl_1_bss_214[i].unk002 = 0;
                        }
                        break;
                }
                break;

            case 2:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        lbl_1_bss_214[i].unk002 = 1;
                        lbl_1_bss_214[i].unk008 = 104;
                        lbl_1_bss_214[i].unk00A = 0;
                        for(j=0; j<100; j++) {
                            if(lbl_1_bss_214[j].unk000 == 0) {
                                lbl_1_bss_214[j].unk000 = 1;
                                lbl_1_bss_214[j].unk002 = 1;
                                lbl_1_bss_214[j].unk006 = 2;
                                lbl_1_bss_214[j].unk008 = 105;
                                lbl_1_bss_214[j].unk00A = 1;
                                break;
                            }
                        }
                        if(i > j) {
                            break;
                        }

                    case 1:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 4.0f);
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 2:
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time >= 97.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk000 = 0;
                            lbl_1_bss_214[i].unk002 = 0;
                        }
                        break;
                }
                break;

            case 3:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        for(j=0, k=0; j<100; j++) {
                            if(lbl_1_bss_214[j].unk000 == 0) {
                                lbl_1_bss_214[j].unk000 = 1;
                                lbl_1_bss_214[j].unk002 = 2;
                                lbl_1_bss_214[j].unk004 = 0;
                                lbl_1_bss_214[j].unk006 = 3;
                                lbl_1_bss_214[j].unk008 = k+110;
                                lbl_1_bss_214[j].unk00A = 0;
                                k++;
                            }
                            if(k >= 50) {
                                break;
                            }
                        }
                        lbl_1_bss_214[i].unk004 = 0;
                        lbl_1_bss_214[i].unk00A = 0;
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 1:
                        if(lbl_1_bss_214[i].unk004++ > 1) {
                            for(j=0, k=0; j<100; j++) {
                                if(lbl_1_bss_214[j].unk000 && lbl_1_bss_214[j].unk004 == 0 && lbl_1_bss_214[j].unk006 == 3 && lbl_1_bss_214[j].unk002 == 2) {
                                    if(lbl_1_bss_214[i].unk00A == 0) {
                                        lbl_1_bss_214[j].unk004 = 1;
                                        lbl_1_bss_214[j].unk00A = k;
                                    } else {
                                        lbl_1_bss_214[j].unk004 = 1;
                                        lbl_1_bss_214[j].unk00A = (lbl_1_bss_214[i].unk00A-1)^1;
                                        k = 1;
                                    }
                                    k++;
                                }
                                if(k >= 2) {
                                    break;
                                }
                            }
                            lbl_1_bss_214[i].unk004 = 0;
                        }
                        break;

                    case 2:
                        if(lbl_1_bss_214[i].unk004 == 0) {
                            break;
                        }
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 8.0f);
                        lbl_1_bss_214[i].unk014 = 0.0f;
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 3:
                        if(Hu3DModelAttrGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].modelId) & HU3D_ATTR_DISPOFF) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        } else {
                            Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        }
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos.z += 10.0f;
                        if((lbl_1_bss_214[i].unk014 += 1.0f) >= 12.5f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk004 = 0;
                            lbl_1_bss_214[i].unk002 = 2;
                        }
                        break;

                    case 4:
                        break;
                }
                break;

            case 4:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        lbl_1_bss_214[i].unk002 = 1;
                        lbl_1_bss_214[i].unk008 = 106;
                        lbl_1_bss_214[i].unk00A = 0;
                        for(j=0; j<100; j++) {
                            if(lbl_1_bss_214[j].unk000 == 0) {
                                lbl_1_bss_214[j].unk000 = 1;
                                lbl_1_bss_214[j].unk002 = 1;
                                lbl_1_bss_214[j].unk006 = 4;
                                lbl_1_bss_214[j].unk008 = 107;
                                lbl_1_bss_214[j].unk00A = 1;
                                break;
                            }
                        }
                        if(i > j) {
                            break;
                        }

                    case 1:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 1.0f);
                        lbl_1_bss_214[i].unk002++;
                        break;

                    case 2:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        if(Hu3DModelAttrGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].modelId) & HU3D_ATTR_DISPOFF) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        } else {
                            Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        }
                        break;

                    case 3:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].rot = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].rot;
                        break;
                }
                break;

            case 6:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        lbl_1_bss_214[i].unk008 = lbl_1_bss_214[i].unk00A+108;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos;
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos.z += 130.0f;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, 8.0f);
                        lbl_1_bss_214[i].unk002++;

                    case 1:
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos.x = lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos.x+(80.0*cos((M_PI*lbl_1_bss_214[i].unk00C)/180.0));
                        lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].pos.y = 30.0f+lbl_1_bss_3030->models[lbl_1_bss_214[i].unk00A+33].pos.y+(80.0*sin((M_PI*lbl_1_bss_214[i].unk010)/180.0));
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId);
                        if(time >= 90.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk000 = 0;
                        }
                        break;
                }
                break;

            case 7:
                switch(lbl_1_bss_214[i].unk002) {
                    case 0:
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[160].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[160].modelId, HU3D_MOTATTR_LOOP);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[160].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[160].modelId, 1.0f);
                        lbl_1_bss_214[i].unk002++;

                    case 1:
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[160].modelId);
                        if(time >= 50.0f) {
                            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[160].modelId, 4.0f);
                            lbl_1_bss_214[i].unk002++;
                        }
                        break;

                    case 2:
                        lbl_1_bss_3030->models[160].pos = lbl_1_bss_8->center;
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[160].modelId);
                        if(time >= 94.0f) {
                            Hu3DMotionTimeSet(lbl_1_bss_3030->models[160].modelId, 50.0f);
                        }
                        break;

                    case 3:
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[160].modelId, 0.5f);
                        lbl_1_bss_1894.unk17C = 4.0f;
                        lbl_1_bss_214[i].unk002++;

                    case 4:
                        if((lbl_1_bss_1894.unk17C -= 0.035f) <= 0.5f) {
                            lbl_1_bss_1894.unk17C = 0.5f;
                        }
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[1].modelId, lbl_1_bss_1894.unk17C);
                        time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[160].modelId);
                        if(time >= 148.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[160].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_214[i].unk002++;
                        }
                        break;
                }
                break;
        }
    }
}

/* asm 10589-13478, 2781 insns. The background props: four groups of models driven by lbl_1_bss_C. */
void fn_1_CFB8(void)
{
    s16 unused = 0;
    s16 grpTbl[3][2] = { { 2, 0 }, { 6, 4 }, { 10, 8 } };
    s16 posTbl[4][4] = {
        { 3000, 1000, 2000, -1000 },
        { 3000, -4000, 2000, -1000 },
        { 1000, -500, 500, 1000 },
        { 1000, -500, 100, -2000 }
    };
    float time;
    float speedB;
    float speed;
    float speed2;
    float speedB2;
    float speedB3;
    s16 i;
    s16 j;
    s16 idx;
    s16 r;
    s16 k;

    if(lbl_1_bss_1894.unk00C >= 2) {
        speed2 = speed = 200.0f;
    } else {
        speed2 = speed = 66.666664f;
    }
    switch(lbl_1_bss_C.unk204) {
        case 0:
            for(i=18, j=0; i<=21; i++, j++) {
                lbl_1_bss_3030->models[i].pos.x = 0.0f;
                lbl_1_bss_3030->models[i].pos.y = 0.0f;
                lbl_1_bss_3030->models[i].pos.z = 0.0f;
                lbl_1_bss_3030->models[i].rot.x = 0.0f;
                lbl_1_bss_3030->models[i].rot.y = 90.0f*j;
                lbl_1_bss_3030->models[i].rot.z = 0.0f;
                Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 1);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 25.0f*j);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.5f);
            }
            for(i=22, j=0; i<=25; i++, j++) {
                lbl_1_bss_3030->models[i].pos.x = 0.0f;
                lbl_1_bss_3030->models[i].pos.y = 0.0f;
                lbl_1_bss_3030->models[i].pos.z = 0.0f;
                lbl_1_bss_3030->models[i].rot.x = 0.0f;
                lbl_1_bss_3030->models[i].rot.y = 45.0f+(90.0f*j);
                lbl_1_bss_3030->models[i].rot.z = 0.0f;
                Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 1);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 25.0f*j);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.5f);
            }
            lbl_1_bss_C.unk204++;

        case 1:
            for(i=18; i<=25; i++) {
                lbl_1_bss_3030->models[i].rot.y -= 0.01f;
            }
            break;
    }
    switch(lbl_1_bss_C.unk124) {
        case 0:
            for(i=14, j=0; i<=17; i++, j++) {
                lbl_1_bss_3030->models[i].pos.x = frandmod(1500)-750.0f;
                lbl_1_bss_3030->models[i].pos.y = frandmod(1500)-750.0f;
                lbl_1_bss_3030->models[i].pos.z = -37000.0f+(9000.0f*j);
                Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 50.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
            }
            lbl_1_bss_C.unk124++;

        case 1:
            for(i=14, j=0; i<=17; i++, j++) {
                time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[i].modelId);
                if(time >= 97.0f) {
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 50.0f);
                }
                if((lbl_1_bss_3030->models[i].pos.z += speed) >= 1500.0f) {
                    lbl_1_bss_3030->models[i].pos.x = frandmod(1500)-750.0f;
                    lbl_1_bss_3030->models[i].pos.y = frandmod(1500)-750.0f;
                    lbl_1_bss_3030->models[i].pos.z = -37000.0f;
                    Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                    Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
                    if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 1800) {
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            break;
    }
    switch(lbl_1_bss_C.unk008) {
        case 0:
            for(i=2, j=0; i<=13; i++, j++) {
                Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
            }
            for(k=0; k<10; k++) {
                idx = frandmod(3);
                for(i=grpTbl[idx][0], j=grpTbl[idx][1]; j<=grpTbl[idx][1]+3; i++, j++) {
                    if(lbl_1_bss_C.unk01C[j].unk00 == 0) {
                        lbl_1_bss_C.unk01C[j].unk00 = 1;
                        lbl_1_bss_C.unk01C[j].unk02 = 0;
                        lbl_1_bss_C.unk01C[j].unk08 = frandmod(360);
                        idx = frandmod(4);
                        r = frandmod(posTbl[idx][0])+posTbl[idx][1];
                        lbl_1_bss_3030->models[i].pos.x = r;
                        r = frandmod(posTbl[idx][2])+posTbl[idx][3];
                        lbl_1_bss_3030->models[i].pos.y = r;
                        lbl_1_bss_3030->models[i].pos.z = -37000.0f+(4000.0f*k);
                        lbl_1_bss_C.unk01C[j].unk04 = lbl_1_bss_3030->models[i].pos.y;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 50.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
                        break;
                    }
                }
            }
            lbl_1_bss_C.unk008++;

        case 1:
            if(lbl_1_bss_1894.unk00C >= 2) {
                lbl_1_bss_C.unk00A = 10;
            } else {
                lbl_1_bss_C.unk00A = frandmod(10)+60;
            }
            lbl_1_bss_C.unk008++;

        case 2:
            if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 1800) {
                lbl_1_bss_C.unk008++;
                break;
            }
            if(lbl_1_bss_C.unk00A-- <= 0) {
                do {
                    idx = frandmod(3);
                } while(lbl_1_bss_C.unk00C[idx]);
                lbl_1_bss_C.unk00C[idx] = 1;
                if(lbl_1_bss_C.unk00C[0] && lbl_1_bss_C.unk00C[1] && lbl_1_bss_C.unk00C[2]) {
                    lbl_1_bss_C.unk00C[0] = lbl_1_bss_C.unk00C[1] = lbl_1_bss_C.unk00C[2] = 0;
                }
                for(i=grpTbl[idx][0], j=grpTbl[idx][1]; j<=grpTbl[idx][1]+3; i++, j++) {
                    if(lbl_1_bss_C.unk01C[j].unk00 == 0) {
                        lbl_1_bss_C.unk01C[j].unk00 = 1;
                        lbl_1_bss_C.unk01C[j].unk02 = 0;
                        lbl_1_bss_C.unk01C[j].unk08 = frandmod(360);
                        do {
                            idx = frandmod(4);
                        } while(lbl_1_bss_C.unk012[idx]);
                        lbl_1_bss_C.unk012[idx] = 1;
                        if(lbl_1_bss_C.unk012[0] && lbl_1_bss_C.unk012[1] && lbl_1_bss_C.unk012[2] && lbl_1_bss_C.unk012[3]) {
                            lbl_1_bss_C.unk012[0] = lbl_1_bss_C.unk012[1] = lbl_1_bss_C.unk012[2] = lbl_1_bss_C.unk012[3] = 0;
                        }
                        r = frandmod(posTbl[idx][0])+posTbl[idx][1];
                        lbl_1_bss_3030->models[i].pos.x = r;
                        r = frandmod(posTbl[idx][2])+posTbl[idx][3];
                        lbl_1_bss_3030->models[i].pos.y = r;
                        lbl_1_bss_3030->models[i].pos.z = -37000.0f;
                        lbl_1_bss_C.unk01C[j].unk04 = lbl_1_bss_3030->models[i].pos.y;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
                        break;
                    }
                }
                lbl_1_bss_C.unk008 = 1;
            }
            break;

        case 3:
            break;
    }
    for(i=2, j=0; i<=13; i++, j++) {
        if(lbl_1_bss_C.unk01C[j].unk00) {
            switch(lbl_1_bss_C.unk01C[j].unk02) {
                case 0:
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[i].modelId);
                    if(time >= 97.0f) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 50.0f);
                    }
                    lbl_1_bss_C.unk01C[j].unk08 += 0.5f;
                    if((lbl_1_bss_3030->models[i].pos.z += speed) >= 1500.0f) {
                        if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 1800) {
                            lbl_1_bss_C.unk01C[j].unk02++;
                        } else {
                            lbl_1_bss_C.unk01C[j].unk00 = 0;
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                            Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                        }
                    }
                    break;

                case 1:
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[i].modelId);
                    if(time >= 97.0f) {
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 50.0f);
                    }
                    if((lbl_1_bss_3030->models[i].pos.z += speed) >= 1500.0f) {
                        lbl_1_bss_C.unk01C[j].unk00 = 0;
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                    }
                    break;
            }
        }
    }
    switch(lbl_1_bss_C.unk10C) {
        case 0:
            lbl_1_bss_3030->models[28].pos.x = 16000.0f;
            lbl_1_bss_3030->models[28].pos.y = 1000.0f;
            lbl_1_bss_3030->models[28].pos.z = -30000.0f;
            lbl_1_bss_3030->models[28].rot.x = 0.0f;
            lbl_1_bss_3030->models[28].rot.y = -90.0f;
            lbl_1_bss_3030->models[28].rot.z = 0.0f;
            Hu3DModelAttrReset(lbl_1_bss_3030->models[28].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_3030->models[28].modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(lbl_1_bss_3030->models[28].modelId, 2);
            Hu3DMotionTimeSet(lbl_1_bss_3030->models[28].modelId, 0.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[28].modelId, 2.0f);
            for(i=29, j=0; i<=32; i++, j++) {
                Hu3DModelLayerSet(lbl_1_bss_3030->models[i].modelId, 2);
            }
            lbl_1_bss_C.unk10C++;

        case 1:
            if(lbl_1_bss_1894.unk00C >= 2) {
                speedB2 = speedB = 50.0f;
            } else {
                speedB2 = speedB = 10.0f;
            }
            lbl_1_bss_3030->models[28].pos.x -= 19.0f;
            lbl_1_bss_3030->models[28].pos.y;
            lbl_1_bss_3030->models[28].pos.z += speedB;
            if(lbl_1_bss_C.unk10E++ >= 30.0f) {
                for(i=29, j=0; i<=32; i++, j++) {
                    if(lbl_1_bss_C.unk114[j].unk00 == 0) {
                        lbl_1_bss_C.unk114[j].unk00 = 1;
                        lbl_1_bss_C.unk114[j].unk02 = 0;
                        lbl_1_bss_3030->models[i].pos.x = 150.0f+lbl_1_bss_3030->models[28].pos.x;
                        lbl_1_bss_3030->models[i].pos.y = lbl_1_bss_3030->models[28].pos.y;
                        lbl_1_bss_3030->models[i].pos.z = lbl_1_bss_3030->models[28].pos.z;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
                        break;
                    }
                }
                lbl_1_bss_C.unk10E = 0;
            }
            if(lbl_1_bss_3030->models[28].pos.z >= 36000.0f) {
                Hu3DModelAttrSet(lbl_1_bss_3030->models[28].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_C.unk10C++;
            }
            break;

        case 2:
            break;

        case 3:
            lbl_1_bss_3030->models[28].pos.x -= 10.0f;
            if(lbl_1_bss_C.unk10E++ >= 30.0f) {
                for(i=29, j=0; i<=32; i++, j++) {
                    if(lbl_1_bss_C.unk114[j].unk00 == 0) {
                        lbl_1_bss_C.unk114[j].unk00 = 1;
                        lbl_1_bss_C.unk114[j].unk02 = 0;
                        lbl_1_bss_3030->models[i].pos.x = 150.0f+lbl_1_bss_3030->models[28].pos.x;
                        lbl_1_bss_3030->models[i].pos.y = lbl_1_bss_3030->models[28].pos.y;
                        lbl_1_bss_3030->models[i].pos.z = lbl_1_bss_3030->models[28].pos.z;
                        Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
                        break;
                    }
                }
                lbl_1_bss_C.unk10E = 0;
            }
            break;
    }
    for(i=29, j=0; i<=32; i++, j++) {
        if(lbl_1_bss_C.unk114[j].unk00) {
            switch(lbl_1_bss_C.unk114[j].unk02) {
                case 0:
                    if(lbl_1_bss_1894.unk00C >= 2) {
                        speedB3 = speedB = 50.0f;
                    } else {
                        speedB3 = speedB = 10.0f;
                    }
                    lbl_1_bss_3030->models[i].pos.z += speedB;
                    time = Hu3DMotionTimeGet(lbl_1_bss_3030->models[i].modelId);
                    if(time >= 97.0f) {
                        lbl_1_bss_C.unk114[j].unk00 = 0;
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                    }
                    break;
            }
        }
    }
    switch(lbl_1_bss_C.unk128) {
        case 0:
            for(i=96, j=0; i<=99; i++, j++) {
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionTimeSet(lbl_1_bss_3030->models[i].modelId, 0.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[i].modelId, 1.0f);
            }
            lbl_1_bss_C.unk128++;

        case 1:
            if(lbl_1_bss_1894.unk00C >= 1) {
                lbl_1_bss_C.unk128++;
            }
            break;

        case 2:
            lbl_1_bss_C.unk12A = 200;
            lbl_1_bss_C.unk128++;
            break;

        case 3:
            if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 1800) {
                lbl_1_bss_C.unk128 = 3;
                break;
            }
            if(lbl_1_bss_C.unk12A-- <= 0) {
                do {
                    j = frandmod(4);
                    i = j+96;
                } while(lbl_1_bss_C.unk13C[j]);
                lbl_1_bss_C.unk13C[j] = 1;
                if(lbl_1_bss_C.unk13C[0] && lbl_1_bss_C.unk13C[1] && lbl_1_bss_C.unk13C[2] && lbl_1_bss_C.unk13C[3]) {
                    lbl_1_bss_C.unk13C[0] = lbl_1_bss_C.unk13C[1] = lbl_1_bss_C.unk13C[2] = lbl_1_bss_C.unk13C[3] = 0;
                }
                if(lbl_1_bss_C.unk144[j].unk00 == 0) {
                    idx = frandmod(2);
                    lbl_1_bss_C.unk144[j].unk00 = 1;
                    lbl_1_bss_C.unk144[j].unk02 = 0;
                    if(idx) {
                        lbl_1_bss_3030->models[i].pos.x = 600.0f+frandmod(100);
                    } else {
                        lbl_1_bss_3030->models[i].pos.x = frandmod(100)-700.0f;
                    }
                    lbl_1_bss_3030->models[i].pos.y = frandmod(1000)-500.0f;
                    lbl_1_bss_3030->models[i].pos.z = -30000.0f;
                    lbl_1_bss_C.unk144[j].unk08 = lbl_1_bss_3030->models[i].pos.y;
                    lbl_1_bss_C.unk144[j].unk0C = 0.0f;
                    if(idx) {
                        lbl_1_bss_3030->models[i].rot.y = 225.0f;
                    } else {
                        lbl_1_bss_3030->models[i].rot.y = 135.0f;
                    }
                    Hu3DModelAttrReset(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_C.unk128 = 1;
            }
            break;

        case 4:
            break;
    }
    for(i=96, j=0; i<=99; i++, j++) {
        if(lbl_1_bss_C.unk144[j].unk00) {
            switch(lbl_1_bss_C.unk144[j].unk02) {
                case 0:
                    lbl_1_bss_C.unk144[j].unk0C += 3.0f;
                    lbl_1_bss_3030->models[i].pos.y = lbl_1_bss_C.unk144[j].unk08+(50.0*sin((M_PI*lbl_1_bss_C.unk144[j].unk0C)/180.0));
                    if((lbl_1_bss_3030->models[i].pos.z += 50.0f) >= 1500.0f) {
                        idx = frandmod(2);
                        if(idx) {
                            lbl_1_bss_3030->models[i].rot.y = 225.0f;
                            lbl_1_bss_3030->models[i].pos.x = 600.0f+frandmod(100);
                        } else {
                            lbl_1_bss_3030->models[i].rot.y = 135.0f;
                            lbl_1_bss_3030->models[i].pos.x = frandmod(100)-700.0f;
                        }
                        lbl_1_bss_3030->models[i].pos.y = frandmod(1000)-500.0f;
                        lbl_1_bss_3030->models[i].pos.z = -30000.0f;
                        lbl_1_bss_C.unk144[j].unk08 = lbl_1_bss_3030->models[i].pos.y;
                        lbl_1_bss_C.unk144[j].unk0C = 0.0f;
                        if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 1200) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_3030->models[i].pos.z = 1500.0f;
                            lbl_1_bss_C.unk144[j].unk02 = 2;
                        }
                    }
                    if(lbl_1_bss_1894.unk028 || lbl_1_bss_1894.unk008 >= 2000) {
                        lbl_1_bss_C.unk144[j].unk10 = lbl_1_bss_3030->models[i].rot.y;
                        lbl_1_bss_C.unk144[j].unk02++;
                    }
                    break;

                case 1:
                    lbl_1_bss_C.unk144[j].unk0C += 3.0f;
                    lbl_1_bss_3030->models[i].pos.y = lbl_1_bss_C.unk144[j].unk08+(50.0*sin((M_PI*lbl_1_bss_C.unk144[j].unk0C)/180.0));
                    if((lbl_1_bss_3030->models[i].pos.z += 50.0f) >= 1500.0f) {
                        lbl_1_bss_C.unk144[j].unk14 += 0.3f;
                        lbl_1_bss_3030->models[i].pos.z += lbl_1_bss_C.unk144[j].unk14;
                        if(lbl_1_bss_3030->models[i].pos.z >= 50000.0f) {
                            Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                            lbl_1_bss_C.unk144[j].unk02++;
                        }
                    }
                    break;

                case 2:
                    break;
            }
        }
    }
}

/* asm 13481-13629, 142 insns. */
s16 fn_1_FB2C(void)
{
    HuVecF *pos;
    s16 result;

    pos = &lbl_1_bss_3030->models[95].pos;
    result = 0;
    switch(lbl_1_bss_11E4.unk000) {
        case 0:
            lbl_1_bss_11E4.unk010 = 2.5f;
            lbl_1_bss_11E4.unk014 = -4.0f;
            lbl_1_bss_11E4.unk01C = -0.15f;
            lbl_1_bss_11E4.unk020 = 0.1f;
            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[33].modelId, 3.0f);
            Hu3DMotionSpeedSet(lbl_1_bss_3030->models[34].modelId, 3.0f);
            lbl_1_bss_11E4.unk000++;

        case 1:
            pos->x += lbl_1_bss_11E4.unk010;
            pos->y += lbl_1_bss_11E4.unk014;
            lbl_1_bss_11E4.unk010 += lbl_1_bss_11E4.unk01C;
            lbl_1_bss_11E4.unk014 += lbl_1_bss_11E4.unk020;
            if(pos->x < -1000.0f) {
                Hu3DModelHookReset(lbl_1_bss_3030->models[95].modelId);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[94].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[95].modelId, HU3D_ATTR_DISPOFF);
                lbl_1_bss_11E4.unk000++;
            }
            break;

        case 2:
            result = 1;
            break;
    }
    return result;
}

/* asm 13632-14063, 413 insns. */
s16 fn_1_FD64(void)
{
    s16 i;
    s16 cnt;
    s16 pan;
    HuVecF *pos;
    s16 result;
    float x;
    float div;

    pos = &lbl_1_bss_3030->models[95].pos;
    result = 0;
    cnt = 0;
    pos->y = 20.0*sin((M_PI*lbl_1_bss_11E4.unk00C)/180.0);
    lbl_1_bss_11E4.unk00C += 2.5f;
    switch(lbl_1_bss_11E4.unk000) {
        case 0:
            lbl_1_bss_3030->models[33].pos.x = -200.0f;
            lbl_1_bss_3030->models[33].pos.y = -100.0f;
            lbl_1_bss_3030->models[33].pos.z = 1400.0f;
            lbl_1_bss_3030->models[34].pos.x = 200.0f;
            lbl_1_bss_3030->models[34].pos.y = -100.0f;
            lbl_1_bss_3030->models[34].pos.z = 1400.0f;
            lbl_1_bss_11E4.unk000++;

        case 1:
            if(lbl_1_bss_11E4.unk004++ > 120) {
                lbl_1_bss_11E4.unk004 = 0;
                lbl_1_bss_11E4.unk000++;
            }
            break;

        case 2:
            div = 90.0f;
            cnt += fn_1_1898(&lbl_1_bss_3030->models[33].pos.z, div, 1400.0f, 0.0f);
            cnt += fn_1_1898(&lbl_1_bss_3030->models[34].pos.z, div, 1400.0f, 0.0f);
            if(cnt == 0) {
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[94].modelId, 1.0f);
                Hu3DModelAttrReset(lbl_1_bss_3030->models[94].modelId, HU3D_MOTATTR_LOOP);
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 0;
                        lbl_1_bss_214[i].unk008 = 0;
                        break;
                    }
                }
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 1;
                        lbl_1_bss_214[i].unk008 = 0;
                        break;
                    }
                }
                omVibrate(lbl_1_bss_3030->chr[0].no, 140, 6, 6);
                omVibrate(lbl_1_bss_3030->chr[1].no, 140, 6, 6);
                x = 0.05818182f*lbl_1_bss_3030->models[33].pos.x;
                pan = 64.0f+x;
                fn_1_2BD8(2, 127, pan);
                x = 0.05818182f*lbl_1_bss_3030->models[34].pos.x;
                pan = 64.0f+x;
                fn_1_2BD8(3, 127, pan);
                lbl_1_bss_11E4.unk004 = 0;
                lbl_1_bss_11E4.unk000++;
            }
            break;

        case 3:
            if(lbl_1_bss_11E4.unk004 == 1 || lbl_1_bss_11E4.unk004 == 60) {
                fn_1_2B10(0);
            } else if(lbl_1_bss_11E4.unk004 == 120) {
                fn_1_2B10(1);
            }
            if(lbl_1_bss_11E4.unk004++ > 140) {
                fn_1_2D40(2, 8000);
                fn_1_2D40(3, 8000);
                lbl_1_bss_11E4.unk004 = 0;
                result = 1;
            }
            break;
    }
    lbl_1_bss_3030->models[169].pos = lbl_1_bss_3030->models[33].pos;
    lbl_1_bss_3030->models[170].pos = lbl_1_bss_3030->models[34].pos;
    return result;
}

/* asm 14066-14738, 658 insns. */
s16 fn_1_103D8(s16 player)
{
    HuVecF *pos = &lbl_1_bss_3030->models[player+33].pos;
    HuVecF *rot = &lbl_1_bss_3030->models[player+33].rot;
    s16 result = 1;
    float shake[8][2] = {
        { 2.0f, 0.0f }, { 2.0f, 0.0f }, { -2.0f, 0.0f }, { -2.0f, 0.0f },
        { 0.0f, 2.0f }, { 0.0f, 2.0f }, { 0.0f, -2.0f }, { 0.0f, -2.0f }
    };
    HuVecF sparkPos;
    s16 i;
    s16 pan;
    float x;

    switch(lbl_1_bss_1894.unk002) {
        case 0:
            lbl_1_bss_120C[player].unk03C = -0.012f;
            lbl_1_bss_120C[player].unk040 = 0.015f;
            lbl_1_bss_120C[player].unk008 = 0;
            omVibrate(lbl_1_bss_3030->chr[player].no, 2000, 6, 6);
            fn_1_2B10(8);
            fn_1_2D40(player+2, 0);
            x = 0.05818182f*lbl_1_bss_3030->models[player+169].pos.x;
            pan = 64.0f+x;
            CharFXPlayVolPan(lbl_1_bss_3030->chr[player].charNo, 0x1F9, 127, pan);
            lbl_1_bss_1894.unk002++;

        case 1:
            lbl_1_bss_120C[player].unk030 += lbl_1_bss_120C[player].unk03C;
            lbl_1_bss_120C[player].unk034 += lbl_1_bss_120C[player].unk040;
            pos->y += lbl_1_bss_120C[player].unk030;
            pos->z += lbl_1_bss_120C[player].unk034;
            if(lbl_1_bss_120C[player].unk008++ > 30) {
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 && lbl_1_bss_214[i].unk006 == 0 && player == lbl_1_bss_214[i].unk00A) {
                        lbl_1_bss_214[i].unk002 = 4;
                    }
                    if(lbl_1_bss_214[i].unk000 && lbl_1_bss_214[i].unk006 == 3 && lbl_1_bss_214[i].unk002 == 1) {
                        lbl_1_bss_214[i].unk00A = player+1;
                    }
                    if(lbl_1_bss_214[i].unk000 && lbl_1_bss_214[i].unk006 == 4 && player == lbl_1_bss_214[i].unk00A) {
                        Hu3DModelAttrSet(lbl_1_bss_3030->models[lbl_1_bss_214[i].unk008].modelId, HU3D_ATTR_DISPOFF);
                        lbl_1_bss_214[i].unk002 = 3;
                    }
                }
                lbl_1_bss_120C[player].unk008 = 0;
                lbl_1_bss_1894.unk002 = 4;
            }
            break;

        case 4:
            lbl_1_bss_120C[player].unk030 += lbl_1_bss_120C[player].unk03C;
            lbl_1_bss_120C[player].unk034 += lbl_1_bss_120C[player].unk040;
            pos->y += lbl_1_bss_120C[player].unk030;
            pos->z += lbl_1_bss_120C[player].unk034;
            if(lbl_1_bss_120C[player].unk008++ >= 48) {
                lbl_1_bss_120C[player].unk03C = -0.08f;
                lbl_1_bss_120C[player].unk040 = 0.08f;
                lbl_1_bss_120C[player].unk008 = 0;
                lbl_1_bss_1894.unk002++;
            }
            break;

        case 5:
            lbl_1_bss_120C[player].unk030 += lbl_1_bss_120C[player].unk03C;
            lbl_1_bss_120C[player].unk034 += lbl_1_bss_120C[player].unk040;
            pos->y += lbl_1_bss_120C[player].unk030;
            pos->z += lbl_1_bss_120C[player].unk034;
            if(pos->y <= -1000.0f) {
                omVibrate(lbl_1_bss_3030->chr[player].no, 1, 6, 6);
                fn_1_2E60(player+2, 1000);
                lbl_1_bss_1894.unk002++;
            }
            break;

        case 6:
            lbl_1_bss_120C[player].unk030 += lbl_1_bss_120C[player].unk03C;
            lbl_1_bss_120C[player].unk034 += lbl_1_bss_120C[player].unk040;
            pos->y += lbl_1_bss_120C[player].unk030;
            pos->z += lbl_1_bss_120C[player].unk034;
            if(pos->y <= -6000.0f) {
                lbl_1_bss_1894.unk002++;
            }
            break;

        case 7:
            result = 0;
            break;
    }
    sparkPos = *pos;
    sparkPos.y -= 20.5f;
    sparkPos.z += 112.0f;
    fn_1_25D8(&sparkPos);
    lbl_1_bss_3030->models[player+33].pos.y += shake[lbl_1_bss_1894.unk178][0];
    lbl_1_bss_3030->models[player+33].pos.y += shake[lbl_1_bss_1894.unk178][1];
    if(++lbl_1_bss_1894.unk178 >= 8) {
        lbl_1_bss_1894.unk178 = 0;
    }
    lbl_1_bss_3030->models[player+169].pos = lbl_1_bss_3030->models[player+33].pos;
    return result;
}

int lbl_1_data_33C[2] = { 0, 0 };

/* asm 14741-15525, 755 insns. */
s16 fn_1_10E20(void)
{
    s16 result;
    s16 cnt;
    s16 com;
    s16 i;

    HuVecF vec;

    result = 0;
    cnt = 0;
    com = 0;
    for(i=0; i<2; i++) {
        if(lbl_1_data_33C[i] == 0) {
            lbl_1_bss_120C[i].unk308.x = -200.0f+(400.0f*i);
            lbl_1_bss_120C[i].unk308.y = 0.0f;
            lbl_1_bss_120C[i].unk2FC = 0;
            lbl_1_bss_120C[i].unk2FE = 0;
            lbl_1_bss_120C[i].unk320 = 5.0f;
            lbl_1_bss_120C[i].unk324 = 56.0f;
            lbl_1_bss_120C[i].unk302 = 0;
            lbl_1_bss_120C[i].unk304 = 0;
            lbl_1_bss_120C[i].unk00E = 1;
            lbl_1_bss_1894.unk148 = 0;
            lbl_1_data_33C[i] = 1;
        }
        memset(&lbl_1_bss_3030->chr[i].btn, 0, 20);
        lbl_1_bss_120C[i].unk334 = 0;
        lbl_1_bss_120C[i].unk338 = 0;
        lbl_1_bss_120C[i].unk33C = 0;
        lbl_1_bss_120C[i].unk340 = 0;
        switch(lbl_1_bss_120C[i].unk00A) {
            case 0:
                com = fn_1_16958(i);
                if(com) {
                    cnt++;
                }
                break;
        }
        lbl_1_bss_3030->chr[i].btn = lbl_1_bss_120C[i].unk334;
        lbl_1_bss_3030->chr[i].btnDown = lbl_1_bss_120C[i].unk338;
        lbl_1_bss_3030->chr[i].stkX = lbl_1_bss_120C[i].unk33C;
        lbl_1_bss_3030->chr[i].stkY = lbl_1_bss_120C[i].unk340;
        if(lbl_1_bss_120C[i].unk00A == 0 && lbl_1_bss_3030->models[i+169].pos.x == lbl_1_bss_120C[i].unk044.x && lbl_1_bss_3030->models[i+169].pos.y == lbl_1_bss_120C[i].unk044.y) {
            lbl_1_bss_120C[i].unk050++;
        } else {
            lbl_1_bss_120C[i].unk050 = 0;
        }
        if(i == 0) {
            if(lbl_1_bss_120C[i].unk050 >= 60 && lbl_1_bss_1894.unk034 != 0) {
                lbl_1_bss_120C[i].unk308.x += 50.0f;
                lbl_1_bss_120C[i].unk308.y += 50.0f;
            } else {
                lbl_1_bss_120C[i].unk308.x = -200.0f;
                lbl_1_bss_120C[i].unk308.y = 0.0f;
            }
        }
        lbl_1_bss_120C[i].unk044 = lbl_1_bss_3030->models[i+169].pos;
    }
    vec.x = ((-200.0f-lbl_1_bss_3030->models[33].pos.x) > 0.0f) ? (-200.0f-lbl_1_bss_3030->models[33].pos.x) : (-1.0f*(-200.0f-lbl_1_bss_3030->models[33].pos.x));
    vec.y = (-lbl_1_bss_3030->models[33].pos.y > 0.0f) ? -lbl_1_bss_3030->models[33].pos.y : (-1.0f*-lbl_1_bss_3030->models[33].pos.y);
    vec.z = sqrt((vec.x*vec.x)+(vec.y*vec.y));
    if(vec.z <= 30.0f) {
        vec.x = ((200.0f-lbl_1_bss_3030->models[34].pos.x) > 0.0f) ? (200.0f-lbl_1_bss_3030->models[34].pos.x) : (-1.0f*(200.0f-lbl_1_bss_3030->models[34].pos.x));
        vec.y = (-lbl_1_bss_3030->models[34].pos.y > 0.0f) ? -lbl_1_bss_3030->models[34].pos.y : (-1.0f*-lbl_1_bss_3030->models[34].pos.y);
        vec.z = sqrt((vec.x*vec.x)+(vec.y*vec.y));
        if(vec.z <= 30.0f) {
            cnt = 2;
        }
    }
    if(cnt == 2) {
        lbl_1_bss_120C[0].unk00E = 0;
        lbl_1_bss_120C[1].unk00E = 0;
        lbl_1_bss_1894.unk148 = 1;
        result = 1;
    } else {
        lbl_1_bss_120C[0].unk00E = 1;
        lbl_1_bss_120C[1].unk00E = 1;
        lbl_1_bss_1894.unk148 = 0;
    }
    return result;
}

/* asm 15528-15801, 260 insns. */
s16 fn_1_119EC(void)
{
    s16 i;
    HuVecF *pos;
    s16 result;

    result = 0;
    switch(lbl_1_bss_1894.unk002) {
        case 0:
            for(i=0; i<2; i++) {
                lbl_1_bss_120C[i].unk03C = -0.07f;
                lbl_1_bss_120C[i].unk040 = 0.05f;
            }
            lbl_1_bss_1894.unk002++;

        case 1:
            for(i=0; i<2; i++) {
                pos = &lbl_1_bss_3030->models[i+33].pos;
                lbl_1_bss_120C[i].unk030 += lbl_1_bss_120C[i].unk03C;
                lbl_1_bss_120C[i].unk034 += lbl_1_bss_120C[i].unk040;
                pos->y += lbl_1_bss_120C[i].unk030;
                pos->z += lbl_1_bss_120C[i].unk034;
                lbl_1_bss_3030->models[i+169].pos = lbl_1_bss_3030->models[i+33].pos;
            }
            if(pos->y <= -1000.0f) {
                fn_1_2E60(2, 1000);
                fn_1_2E60(3, 1000);
                lbl_1_bss_1894.unk002++;
            }
            break;

        case 2:
            for(i=0; i<2; i++) {
                pos = &lbl_1_bss_3030->models[i+33].pos;
                lbl_1_bss_120C[i].unk030 += lbl_1_bss_120C[i].unk03C;
                lbl_1_bss_120C[i].unk034 += lbl_1_bss_120C[i].unk040;
                pos->y += lbl_1_bss_120C[i].unk030;
                pos->z += lbl_1_bss_120C[i].unk034;
                lbl_1_bss_3030->models[i+169].pos = lbl_1_bss_3030->models[i+33].pos;
            }
            if(pos->y <= -6000.0f) {
                lbl_1_bss_1894.unk002++;
            }
            break;

        case 3:
            result = 1;
            break;
    }
    return result;
}

/* asm 15804-16761, 940 insns. */
void fn_1_11DFC(s16 player)
{
    HuVecF ofs;
    s16 unk0C;
    s16 unk0A;
    s16 mdlNo;
    s16 i;
    s16 j;

    ofs = lbl_1_bss_3030->models[player+169].pos;
    unk0A = 0;
    unk0C = 28;
    for(mdlNo=96, i=0, j=0; mdlNo<=99; mdlNo++, i++, j=i%2) {
        switch(lbl_1_bss_1894.unk084[i].unk02) {
            case 0:
                if(lbl_1_bss_1894.unk084[i].unk06++ >= 30.0f) {
                    lbl_1_bss_1894.unk084[i].unk06 = 0;
                    lbl_1_bss_1894.unk084[i].unk02++;
                }
                break;

            case 1:
                switch(i) {
                    case 0:
                        lbl_1_bss_1894.unk084[i].unk0C = 0.0f;
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 60.0f);
                        lbl_1_bss_3030->models[mdlNo].pos.x = -900.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.y = 0.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.z = 400.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.x = 15.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.y = 135.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.z = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk18 = 2.0f;
                        lbl_1_bss_1894.unk084[i].unk1C = 0.5f;
                        lbl_1_bss_1894.unk084[i].unk20 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk24 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk28 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk2C = 0.0f;
                        break;

                    case 1:
                        lbl_1_bss_1894.unk084[i].unk0C = 135.0f;
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 60.0f);
                        lbl_1_bss_3030->models[mdlNo].pos.x = -400.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.y = -750.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.z = 400.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.x = 0.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.y = 135.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.z = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk18 = 0.5f;
                        lbl_1_bss_1894.unk084[i].unk1C = 2.0f;
                        lbl_1_bss_1894.unk084[i].unk20 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk24 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk28 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk2C = 0.0f;
                        break;

                    case 2:
                        lbl_1_bss_1894.unk084[i].unk0C = 45.0f;
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.5f);
                        lbl_1_bss_3030->models[mdlNo].pos.x = 800.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.y = 0.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.z = 400.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.x = 0.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.y = 225.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.z = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk18 = -2.0f;
                        lbl_1_bss_1894.unk084[i].unk1C = 0.5f;
                        lbl_1_bss_1894.unk084[i].unk20 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk24 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk28 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk2C = 0.0f;
                        break;

                    case 3:
                        lbl_1_bss_1894.unk084[i].unk0C = 180.0f;
                        Hu3DMotionTimeSet(lbl_1_bss_3030->models[mdlNo].modelId, 50.0f);
                        Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.5f);
                        lbl_1_bss_3030->models[mdlNo].pos.x = 900.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.y = -150.0f;
                        lbl_1_bss_3030->models[mdlNo].pos.z = 400.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.x = 0.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.y = 225.0f;
                        lbl_1_bss_3030->models[mdlNo].rot.z = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk18 = -2.0f;
                        lbl_1_bss_1894.unk084[i].unk1C = -0.5f;
                        lbl_1_bss_1894.unk084[i].unk20 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk24 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk28 = 0.0f;
                        lbl_1_bss_1894.unk084[i].unk2C = 0.0f;
                        break;
                }
                lbl_1_bss_3030->models[mdlNo].pos.x += ofs.x;
                lbl_1_bss_3030->models[mdlNo].pos.y += ofs.y;
                lbl_1_bss_1894.unk084[i].unk08 = lbl_1_bss_3030->models[mdlNo].pos.y;
                Hu3DModelAttrReset(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_3030->models[mdlNo].modelId, HU3D_MOTATTR_LOOP);
                Hu3DMotionSpeedSet(lbl_1_bss_3030->models[mdlNo].modelId, 1.0f);
                lbl_1_bss_1894.unk084[i].unk02++;
                break;

            case 2:
                switch(i) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        break;
                }
                lbl_1_bss_1894.unk084[i].unk0C += 3.0f;
                lbl_1_bss_3030->models[mdlNo].pos.x += lbl_1_bss_1894.unk084[i].unk18;
                lbl_1_bss_1894.unk084[i].unk08 += lbl_1_bss_1894.unk084[i].unk1C;
                lbl_1_bss_3030->models[mdlNo].pos.y = lbl_1_bss_1894.unk084[i].unk08+(50.0*sin((M_PI*lbl_1_bss_1894.unk084[i].unk0C)/180.0));
                if(lbl_1_bss_1894.unk084[i].unk06++ >= 240.0f) {
                    lbl_1_bss_1894.unk084[i].unk02++;
                }
                break;

            case 3:
                switch(i) {
                    case 0:
                    case 1:
                    case 2:
                    case 3:
                        break;
                }
                lbl_1_bss_1894.unk084[i].unk0C += 3.0f;
                lbl_1_bss_3030->models[mdlNo].pos.y = lbl_1_bss_1894.unk084[i].unk08+(50.0*sin((M_PI*lbl_1_bss_1894.unk084[i].unk0C)/180.0));
                break;
        }
    }
}

/* asm 16764-16854, 86 insns. */
void fn_1_12CAC(s16 player)
{
    switch(lbl_1_bss_1894.unk160) {
        case 0:
            lbl_1_bss_1894.unk160++;
        case 1:
            lbl_1_bss_1894.unk164 += 2.5f;
            lbl_1_bss_3030->models[player+33].pos.y = lbl_1_bss_1894.unk154.y+(10.0*sin((M_PI*lbl_1_bss_1894.unk164)/180.0));
            lbl_1_bss_3030->models[player+169].pos = lbl_1_bss_3030->models[player+33].pos;
            break;
    }
}

/* asm 16857-17050, 181 insns. */
void fn_1_12E04(void)
{
    float div;
    s16 i;
    s16 j;
    s16 count;
    float start[10];
    float end[10];

    count = 0;
    start[0] = -568.0f;
    start[1] = 568.0f;
    start[2] = -520.0f;
    start[3] = 520.0f;
    start[4] = -520.0f;
    start[5] = 520.0f;
    start[6] = -520.0f;
    start[7] = 520.0f;
    end[0] = -868.0f;
    end[1] = 868.0f;
    end[2] = -820.0f;
    end[3] = 820.0f;
    end[4] = -820.0f;
    end[5] = 820.0f;
    end[6] = -820.0f;
    end[7] = 820.0f;
    switch(lbl_1_bss_1894.unk02E) {
        case 0:
            if(lbl_1_bss_1894.unk030++ > 30) {
                lbl_1_bss_1894.unk02E++;
            }
            break;

        case 1:
            div = 120.0f;
            for(i=161, j=0; i<=168; i++, j++) {
                count += fn_1_1898(&lbl_1_bss_3030->models[i].pos.x, div, start[j], end[j]);
            }
            if(count == 0) {
                for(i=161, j=0; i<=168; i++, j++) {
                    Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_1894.unk02E++;
            }
            break;

        case 2:
            for(i=161, j=0; i<=168; i++, j++) {
                Hu3DModelAttrSet(lbl_1_bss_3030->models[i].modelId, HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

/* asm 17053-17287, 214 insns. */
s16 fn_1_130D8(void)
{
    s16 i;
    s16 result;
    s16 doneF;

    result = 0;
    doneF = 0;
    switch(lbl_1_bss_1894.unk000) {
        case 0:
            fn_1_2B10(10);
            fn_1_2B10(11);
            lbl_1_bss_1894.unk000++;
        case 1:
            doneF = fn_1_FD64();
            if(doneF) {
                lbl_1_bss_11E4.unk000 = 0;
                lbl_1_bss_1894.unk000++;
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 2;
                        break;
                    }
                }
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 3;
                        break;
                    }
                }
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 4;
                        break;
                    }
                }
                for(i=0; i<100; i++) {
                    if(lbl_1_bss_214[i].unk000 == 0) {
                        lbl_1_bss_214[i].unk000 = 1;
                        lbl_1_bss_214[i].unk002 = 0;
                        lbl_1_bss_214[i].unk006 = 7;
                        break;
                    }
                }
                omVibrate(lbl_1_bss_3030->chr[0].no, 30, 4, 2);
                omVibrate(lbl_1_bss_3030->chr[1].no, 30, 4, 2);
                fn_1_2A18();
                result = 1;
            }
            break;
    }
    return result;
}

/* asm 17290-18353, 1,020 insns. fn_1_12CAC is inlined at all five calls. */
s16 fn_1_13430(void)
{
    float speed;
    float start;
    DS_PLAYER *pl;
    s16 i;
    s16 done;
    s16 result;
    s16 pitch;
    s16 pan;
    HuVecF diff;

    result = 0;
    done = 0;
    if(lbl_1_bss_1894.unk000 >= 2) {
        if(lbl_1_bss_3030->mode[0] == 0) {
            if(lbl_1_bss_1894.unk028 != 0) {
                pl = &lbl_1_bss_3030->player[lbl_1_bss_1894.unk028&1];
                pl->shiftMode = 1;
                pl->shiftMotNo = 1;
                pl->shiftTime = 0.0f;
                pl->shiftSpeed = 4.0f;
                pl->shiftAttr = 0;
                pl->attrReset = HU3D_MOTATTR_LOOP;
            }
            lbl_1_bss_3030->mode[0] = 1;
        } else if(lbl_1_bss_1894.unk028 != 0) {
            pl = &lbl_1_bss_3030->player[lbl_1_bss_1894.unk028&1];
            if(pl->shiftMode == 0 && pl->time >= 38.0f) {
                pl->time = 10.0f;
            }
        }
    }
    switch(lbl_1_bss_1894.unk000) {
        case 0:
            lbl_1_bss_1894.unk148 = 1;
            lbl_1_bss_1894.unk14A = 1;
            lbl_1_bss_1894.unk006 = 0;
            lbl_1_bss_1894.unk000++;
        case 1:
            if(lbl_1_bss_1894.unk028 == 0) {
                done = fn_1_10E20();
            } else {
                done = 1;
            }
            if(lbl_1_bss_1894.unk006++ > 100 && done) {
                if(lbl_1_bss_1894.unk028 != 0) {
                    for(i=0; i<100; i++) {
                        if(lbl_1_bss_214[i].unk000 != 0 && lbl_1_bss_214[i].unk006 == 7) {
                            lbl_1_bss_214[i].unk002++;
                            break;
                        }
                    }
                }
                lbl_1_bss_1894.unk036 = 1;
                lbl_1_bss_1894.unk038 = 0.05818182f*lbl_1_bss_3030->models[(lbl_1_bss_1894.unk028&1)+33].pos.x;
                lbl_1_bss_1894.unk03C = lbl_1_bss_1894.unk038;
                lbl_1_bss_1894.unk154 = lbl_1_bss_3030->models[(lbl_1_bss_1894.unk028&1)+33].pos;
                lbl_1_bss_1894.unk168 = lbl_1_bss_8->pos;
                lbl_1_bss_1894.unk006 = 120;
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 2:
            if(lbl_1_bss_1894.unk028 == 0) {
                fn_1_119EC();
            }
            if(lbl_1_bss_1894.unk028 != 0) {
                speed = 120.0f;
                if(lbl_1_bss_8->rot.y >= 90.0f) {
                    fn_1_12CAC(lbl_1_bss_1894.unk028&1);
                }
                if(lbl_1_bss_1894.unk006-- >= 0) {
                    lbl_1_bss_1894.unk006 = 0;
                }
                pitch = lbl_1_bss_1894.unk006*66;
                fn_1_2D40((lbl_1_bss_1894.unk028&1)+2, pitch);
                start = lbl_1_bss_1894.unk038;
                fn_1_1898(&lbl_1_bss_1894.unk03C, speed, start, 64.0f);
                pan = lbl_1_bss_1894.unk03C;
                fn_1_2CB0((lbl_1_bss_1894.unk028&1)+2, pan);
                done += fn_1_1898(&lbl_1_bss_8->center.x, speed, lbl_1_data_150[1].center.x, lbl_1_bss_1894.unk154.x);
                done += fn_1_1898(&lbl_1_bss_8->center.y, speed, lbl_1_data_150[1].center.y, 40.0f+lbl_1_bss_1894.unk154.y);
                done += fn_1_1898(&lbl_1_bss_8->center.z, speed, lbl_1_data_150[1].center.z, lbl_1_bss_1894.unk154.z);
                done += fn_1_1898(&lbl_1_bss_8->rot.x, speed, lbl_1_data_150[1].rot.x, -15.0f);
                done += fn_1_1898(&lbl_1_bss_8->rot.y, speed, 0.0f, 180.0f);
                done += fn_1_1898(&lbl_1_bss_8->zoom, speed, lbl_1_data_150[1].zoom, 700.0f);
                diff.x = lbl_1_bss_8->pos.x-lbl_1_bss_1894.unk168.x;
                diff.y = lbl_1_bss_8->pos.y-lbl_1_bss_1894.unk168.y;
                diff.z = lbl_1_bss_8->pos.z-lbl_1_bss_1894.unk168.z;
            } else {
                speed = 120.0f;
                done += fn_1_1898(&lbl_1_bss_8->rot.y, speed, 0.0f, 180.0f);
            }
            if(done == 0) {
                lbl_1_bss_1894.unk006 = 0;
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 3:
            if(lbl_1_bss_1894.unk028 == 0) {
                fn_1_119EC();
            }
            if(lbl_1_bss_1894.unk028 != 0) {
                fn_1_12CAC(lbl_1_bss_1894.unk028&1);
            }
            if(done == 0) {
                lbl_1_bss_1894.unk006 = 0;
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 4:
            if(lbl_1_bss_1894.unk028 == 0) {
                fn_1_119EC();
            }
            if(lbl_1_bss_1894.unk028 != 0) {
                fn_1_12CAC(lbl_1_bss_1894.unk028&1);
            }
            if(lbl_1_bss_1894.unk040 != 0 && lbl_1_bss_1894.unk028 != 0) {
                fn_1_11DFC(lbl_1_bss_1894.unk028&1);
            }
            if(lbl_1_bss_1894.unk006++ > 60) {
                lbl_1_bss_1894.unk006 = 0;
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 5:
            if(lbl_1_bss_1894.unk028 == 0) {
                fn_1_119EC();
            }
            if(lbl_1_bss_1894.unk028 != 0) {
                fn_1_12CAC(lbl_1_bss_1894.unk028&1);
            }
            if(done == 0) {
                lbl_1_bss_1894.unk000++;
            }
            break;

        case 6:
            if(lbl_1_bss_1894.unk028 == 0) {
                result = fn_1_119EC();
            }
            if(lbl_1_bss_1894.unk028 != 0) {
                fn_1_12CAC(lbl_1_bss_1894.unk028&1);
            }
            result = 1;
            break;
    }
    if(lbl_1_bss_1894.unk028 != 0) {
        fn_1_103D8(lbl_1_bss_1894.unk028>>1);
    }
    return result;
}

/* asm 18356-19335, 942 insns. */
void fn_1_14420(void)
{
    HuVecF vec[5];
    float unused;
    float radius;
    float radiusAdd;
    float amp;
    float limit;
    float scale;
    float dist;
    float panX;
    HuVecF *pos1;
    HuVecF *pos0;
    s16 i;
    s16 k;
    s16 pan;
    s16 j;
    HuVecF *shadow0;
    HuVecF *shadow1;
    s16 mdlNo;

    unused = 50.0f;
    radius = 80.0f;
    radiusAdd = 50.0f;
    pos0 = &lbl_1_bss_3030->models[33].pos;
    pos1 = &lbl_1_bss_3030->models[34].pos;
    shadow0 = &lbl_1_bss_3030->models[169].pos;
    shadow1 = &lbl_1_bss_3030->models[170].pos;
    if(lbl_1_bss_1894.unk148 == 0) {
        amp = 20.0f;
        vec[0].x = pos0->x-pos1->x;
        vec[0].y = pos0->y-pos1->y;
        dist = sqrt(vec[0].x*vec[0].x+vec[0].y*vec[0].y);
        vec[1].x = vec[0].x/(0.1f+dist);
        vec[1].y = vec[0].y/(0.1f+dist);
        vec[2].x = 180.0*(acos(vec[1].x)/M_PI);
        vec[2].y = 180.0*(asin(vec[1].y)/M_PI);
        if(vec[2].y < 0.0f) {
            vec[2].x = 360.0f-vec[2].x;
        }
        vec[2].y = (sin((M_PI*vec[2].x)/180.0) > 0.0) ? sin((M_PI*vec[2].x)/180.0) : -1.0*sin((M_PI*vec[2].x)/180.0);
        vec[2].y = radius+(vec[2].y*amp);
        limit = 2.0f*vec[2].y;
        if(dist < limit) {
            if(dist) {
                scale = vec[2].y/dist;
            } else {
                scale = 0.0f;
            }
            vec[0].x *= scale;
            vec[0].y *= scale;
            vec[1] = *pos0;
            vec[2] = *pos1;
            vec[1].x = (pos0->x+pos1->x)/2.0f;
            vec[1].y = (pos0->y+pos1->y)/2.0f;
            pos1->x = vec[1].x-vec[0].x;
            pos1->y = vec[1].y-vec[0].y;
            shadow1->x = vec[1].x-vec[0].x;
            shadow1->y = vec[1].y-vec[0].y;
            pos0->x = vec[1].x+vec[0].x;
            pos0->y = vec[1].y+vec[0].y;
            shadow0->x = vec[1].x+vec[0].x;
            shadow0->y = vec[1].y+vec[0].y;
            if(lbl_1_bss_1894.unk034 == 0 && lbl_1_bss_1894.unk00C <= 4) {
                panX = 0.05818182f*vec[1].x;
                pan = 64.0f+panX;
                fn_1_2BD8(9, 127, pan);
            }
            lbl_1_bss_1894.unk032++;
            lbl_1_bss_1894.unk034 = 1;
        } else {
            lbl_1_bss_1894.unk032 = 0;
            lbl_1_bss_1894.unk034 = 0;
        }
        for(i=0; i<2; i++) {
            pos0 = &lbl_1_bss_3030->models[i+169].pos;
            pos1 = &lbl_1_bss_3030->models[i+33].pos;
            if(lbl_1_bss_120C[i].unk012 == 0 && lbl_1_bss_1894.unk028 == 0) {
                for(j=0; j<50; j++) {
                    mdlNo = j+35;
                    if(lbl_1_bss_B88[j].unk000 != 0 && lbl_1_bss_3030->models[mdlNo].pos.z >= -121.0f && lbl_1_bss_3030->models[mdlNo].pos.z <= 121.0f) {
                        vec[0].x = lbl_1_bss_3030->models[mdlNo].pos.x-pos1->x;
                        vec[0].y = lbl_1_bss_3030->models[mdlNo].pos.y-(30.0f+pos1->y);
                        dist = sqrt(vec[0].x*vec[0].x+vec[0].y*vec[0].y);
                        if(dist < radius+radiusAdd) {
                            if(--lbl_1_bss_120C[i].unk014 <= 0) {
                                lbl_1_bss_1894.unk028 = (i<<1)|(i^1);
                                fn_1_2E60(i+6, 1000);
                            }
                            if(0.0f == dist) {
                                vec[1].x = 0.0f;
                                vec[1].y = 0.0f;
                            } else {
                                vec[1].x = vec[0].x/(0.1f+dist);
                                vec[1].y = vec[0].y/(0.1f+dist);
                                vec[2].x = 180.0*(acos(vec[1].x)/M_PI);
                                vec[2].y = 180.0*(asin(vec[1].y)/M_PI);
                                if(vec[2].y < 0.0f) {
                                    vec[2].x = 360.0f-vec[2].x;
                                }
                                vec[1].x = pos1->x+(radius*cos((M_PI*vec[2].x)/180.0));
                                vec[1].y = (30.0f+pos1->y)+(radius*sin((M_PI*vec[2].y)/180.0));
                            }
                            for(k=0; k<100; k++) {
                                if(lbl_1_bss_214[k].unk000 == 0) {
                                    lbl_1_bss_214[k].unk000 = 1;
                                    lbl_1_bss_214[k].unk002 = 0;
                                    lbl_1_bss_214[k].unk006 = 6;
                                    lbl_1_bss_214[k].unk00A = i;
                                    lbl_1_bss_214[k].unk00C = vec[2].x;
                                    lbl_1_bss_214[k].unk010 = vec[2].y;
                                    break;
                                }
                            }
                            panX = 0.05818182f*vec[1].x;
                            pan = 64.0f+panX;
                            fn_1_2BD8(5, 127, pan);
                            panX = 0.05818182f*lbl_1_bss_3030->models[i+169].pos.x;
                            pan = 64.0f+panX;
                            CharFXPlayVolPan(lbl_1_bss_3030->chr[i].charNo, 0x1FD, 127, pan);
                            lbl_1_bss_120C[i].unk012 = 1;
                            break;
                        } else if(dist < 80.0f+(radius+radiusAdd)) {
                            panX = 0.05818182f*lbl_1_bss_3030->models[j+35].pos.x;
                            pan = 64.0f+panX;
                            fn_1_2BD8(4, 127, pan);
                        }
                    }
                }
            }
            if(lbl_1_bss_1894.unk14A == 0) {
                if(pos1->x > 530.0f) {
                    pos0->x = 530.0f;
                    pos1->x = 530.0f;
                }
                if(pos1->x < -530.0f) {
                    pos0->x = -530.0f;
                    pos1->x = -530.0f;
                }
                if(30.0f+pos1->y > 316.0f) {
                    pos0->y = 286.0f;
                    pos1->y = 286.0f;
                }
                if(30.0f+pos1->y < -316.0f) {
                    pos0->y = -346.0f;
                    pos1->y = -346.0f;
                }
            }
        }
    }
}

/* asm 19338-19533, 193 insns. The computer duellist's difficulty table. */
void fn_1_152D8(s16 player)
{
    float t0[4] = { 10.0f, 25.0f, 40.0f, 56.0f };
    float t1[4] = { 0.0f, 20.0f, 40.0f, 56.0f };
    float t2[4] = { -30000.0f, -30000.0f, -30000.0f, -30000.0f };
    float t3[4] = { 25.0f, 25.0f, 2.0f, 1.0f };
    float t4[4] = { 30.0f, 20.0f, 0.0f, 0.0f };
    float t5[4] = { 30.0f, 5.0f, 0.0f, 0.0f };

    if(lbl_1_bss_3030->chr[player].dif != 0) {
        lbl_1_bss_120C[player].unk052 = 1;
        lbl_1_bss_120C[player].unk054 = lbl_1_bss_3030->chr[player].dif-1;
        lbl_1_bss_120C[player].unk320 = t0[lbl_1_bss_120C[player].unk054];
        lbl_1_bss_120C[player].unk324 = t1[lbl_1_bss_120C[player].unk054];
        lbl_1_bss_120C[player].unk328 = t2[lbl_1_bss_120C[player].unk054];
        lbl_1_bss_120C[player].unk32C = t3[lbl_1_bss_120C[player].unk054];
        lbl_1_bss_120C[player].unk32E = t4[lbl_1_bss_120C[player].unk054];
        lbl_1_bss_120C[player].unk330 = t5[lbl_1_bss_120C[player].unk054];
    }
}

#define M555_ABS(x) ((x) > 0.0f) ? (x) : (-1.0f*(x))

/* asm 19536-20005, 454 insns. The computer duellist: pick a move and turn it into pad input. */
s16 fn_1_155DC(s16 player)
{
    s16 result;
    s16 rand;
    s16 ret;

    ret = 0;
    result = 0;
    lbl_1_bss_120C[player].unk334 = 0;
    lbl_1_bss_120C[player].unk338 = 0;
    lbl_1_bss_120C[player].unk33C = 0;
    lbl_1_bss_120C[player].unk340 = 0;
    switch(lbl_1_bss_120C[player].unk056) {
        case 0:
            lbl_1_bss_120C[player].unk056++;
        case 1:
            result = lbl_1_bss_120C[player].unk05E = fn_1_17400(lbl_1_bss_3030->models[player+33].pos, 130.0f, -10000.0f);
            result = fn_1_1A880(player, result);
            if(result) {
                rand = frandmod(100);
                if(rand < lbl_1_bss_120C[player].unk32E) {
                    lbl_1_bss_120C[player].unk05C = 0;
                    lbl_1_bss_120C[player].unk056 = 4;
                } else {
                    fn_1_176C4(player);
                    lbl_1_bss_120C[player].unk056 = 2;
                }
            } else {
                if(lbl_1_bss_120C[player].unk054 == 3 && lbl_1_bss_1894.unk008 > 600) {
                    lbl_1_bss_120C[player].unk32C = 0;
                }
                rand = frandmod(100);
                if(rand < lbl_1_bss_120C[player].unk32C) {
                    result = fn_1_1A4B0(player);
                    if(result) {
                        lbl_1_bss_120C[player].unk302 = 1;
                        lbl_1_bss_120C[player].unk304 = 1;
                        lbl_1_bss_120C[player].unk056 = 3;
                    }
                } else {
                    rand = frandmod(100);
                    if(rand < lbl_1_bss_120C[player].unk330) {
                        result = fn_1_1A6F4(player);
                        if(result) {
                            lbl_1_bss_120C[player].unk056 = 5;
                        }
                    }
                }
            }
            break;

        case 2:
            if(fn_1_171C8(player, 50.0f)) {
                if(!fn_1_17400(lbl_1_bss_3030->models[player+33].pos, 230.0f, -10000.0f)) {
                    lbl_1_bss_120C[player].unk2FC = 1;
                    lbl_1_bss_120C[player].unk2FE = 1;
                } else if(fn_1_19C0C(player)) {
                    lbl_1_bss_120C[player].unk2FC = 1;
                    lbl_1_bss_120C[player].unk2FE = 1;
                }
            }
            result = fn_1_16104(player);
            if(result) {
                lbl_1_bss_120C[player].unk056 = 1;
            }
            break;

        case 3:
            result = fn_1_16104(player);
            if(result) {
                lbl_1_bss_120C[player].unk302 = 0;
                lbl_1_bss_120C[player].unk304 = 0;
                lbl_1_bss_120C[player].unk056 = 1;
            }
            break;

        case 4:
            if(lbl_1_bss_120C[player].unk05C++ > 60) {
                lbl_1_bss_120C[player].unk05C = 0;
                lbl_1_bss_120C[player].unk056 = 1;
            }
            break;

        case 5:
            result = fn_1_16104(player);
            if(result) {
                lbl_1_bss_120C[player].unk056 = 6;
            }
            break;

        case 6:
            if(lbl_1_bss_120C[player].unk05C++ > 60) {
                lbl_1_bss_120C[player].unk05C = 0;
                lbl_1_bss_120C[player].unk056 = 1;
            }
            break;
    }
    lbl_1_bss_3030->chr[player].btn = lbl_1_bss_120C[player].unk334;
    lbl_1_bss_3030->chr[player].btnDown = lbl_1_bss_120C[player].unk338;
    lbl_1_bss_3030->chr[player].stkX = lbl_1_bss_120C[player].unk33C;
    lbl_1_bss_3030->chr[player].stkY = lbl_1_bss_120C[player].unk340;
    return ret;
}

/* asm 20008-20288, 260 insns. Unreferenced: steer the stick toward (unk2F0, unk2F4), y then x. */
s16 fn_1_15CF4(s16 player)
{
    HuVecF diff;
    HuVecF absDiff;
    float flip;
    float dir;
    s16 result;
    s16 doneNum;
    s16 mdlNo;

    result = 0;
    doneNum = 0;
    mdlNo = player+169;
    diff.x = lbl_1_bss_120C[player].unk2F0.x-lbl_1_bss_3030->models[mdlNo].pos.x;
    diff.y = lbl_1_bss_120C[player].unk2F0.y-lbl_1_bss_3030->models[mdlNo].pos.y;
    absDiff.x = M555_ABS(diff.x);
    absDiff.y = M555_ABS(diff.y);
    switch(lbl_1_bss_120C[player].unk2E8) {
        case 0:
            if(absDiff.y >= 20.0f) {
                (lbl_1_bss_120C[player].unk01A) ? (flip = -1.0f) : (flip = 1.0f);
                (diff.y > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk340 = flip*(dir*lbl_1_bss_120C[player].unk320);
            } else {
                lbl_1_bss_120C[player].unk2E8++;
            }
            break;

        case 1:
            doneNum++;
            break;
    }
    switch(lbl_1_bss_120C[player].unk2EA) {
        case 0:
            if(absDiff.x >= 20.0f) {
                (diff.x > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk33C = dir*lbl_1_bss_120C[player].unk320;
            } else {
                lbl_1_bss_120C[player].unk2EA++;
            }
            break;

        case 1:
            doneNum++;
            break;
    }
    if(doneNum >= 2) {
        lbl_1_bss_120C[player].unk2E8 = 0;
        lbl_1_bss_120C[player].unk2EA = 0;
        result = 1;
    }
    return result;
}

/* asm 20291-20861, 533 insns. Steer the stick toward (unk308, unk30C) from model player+169, y then x, then let the stick fall back. */
s16 fn_1_16104(s16 player)
{
    HuVecF diff;
    HuVecF absDiff;
    float flip;
    float dir;
    s16 result;
    s16 doneNum;
    s16 mdlNo;

    result = 0;
    doneNum = 0;
    mdlNo = player+169;
    diff.x = lbl_1_bss_120C[player].unk308.x-lbl_1_bss_3030->models[mdlNo].pos.x;
    diff.y = lbl_1_bss_120C[player].unk308.y-lbl_1_bss_3030->models[mdlNo].pos.y;
    absDiff.x = M555_ABS(diff.x);
    absDiff.y = M555_ABS(diff.y);
    switch(lbl_1_bss_120C[player].unk2FC) {
        case 0:
            if(absDiff.y >= 20.0f) {
                (lbl_1_bss_120C[player].unk01A) ? (flip = -1.0f) : (flip = 1.0f);
                (diff.y > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk340 = flip*(dir*lbl_1_bss_120C[player].unk320);
            } else {
                lbl_1_bss_120C[player].unk2FC++;
            }
            break;

        case 1:
            if((M555_ABS(lbl_1_bss_120C[player].unk024) >= 6.0f) && lbl_1_bss_120C[player].unk304 == 0) {
                (lbl_1_bss_120C[player].unk01A) ? (flip = -1.0f) : (flip = 1.0f);
                (lbl_1_bss_120C[player].unk024 > 0.0f) ? (dir = -1.0f) : (dir = 1.0f);
                lbl_1_bss_120C[player].unk340 = flip*(dir*lbl_1_bss_120C[player].unk324);
            } else {
                lbl_1_bss_120C[player].unk2FC++;
                doneNum++;
            }
            break;

        case 2:
            doneNum++;
            break;
    }
    switch(lbl_1_bss_120C[player].unk2FE) {
        case 0:
            if(absDiff.x >= 20.0f) {
                (diff.x > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk33C = dir*lbl_1_bss_120C[player].unk320;
            } else {
                lbl_1_bss_120C[player].unk2FE++;
            }
            break;

        case 1:
            if((M555_ABS(lbl_1_bss_120C[player].unk020) >= 6.0f) && lbl_1_bss_120C[player].unk302 == 0) {
                (lbl_1_bss_120C[player].unk020 > 0.0f) ? (dir = -1.0f) : (dir = 1.0f);
                lbl_1_bss_120C[player].unk33C = dir*lbl_1_bss_120C[player].unk324;
            } else {
                lbl_1_bss_120C[player].unk2FE++;
                doneNum++;
            }
            break;

        case 2:
            doneNum++;
            break;
    }
    if(doneNum >= 2) {
        lbl_1_bss_120C[player].unk2FC = 0;
        lbl_1_bss_120C[player].unk2FE = 0;
        result = 1;
    } else if(lbl_1_bss_1894.unk032 >= 120) {
        lbl_1_bss_120C[player].unk2FC = 0;
        lbl_1_bss_120C[player].unk2FE = 0;
        result = 1;
    }
    return result;
}

/* asm 20864-21442, 540 insns. fn_1_16104 from model player+33, without the timeout. */
s16 fn_1_16958(s16 player)
{
    HuVecF diff;
    HuVecF absDiff;
    float flip;
    float dir;
    s16 result;
    s16 doneNum;
    s16 mdlNo;

    result = 0;
    doneNum = 0;
    mdlNo = player+33;
    diff.x = lbl_1_bss_120C[player].unk308.x-lbl_1_bss_3030->models[mdlNo].pos.x;
    diff.y = lbl_1_bss_120C[player].unk308.y-lbl_1_bss_3030->models[mdlNo].pos.y;
    absDiff.x = M555_ABS(diff.x);
    absDiff.y = M555_ABS(diff.y);
    switch(lbl_1_bss_120C[player].unk2FC) {
        case 0:
            if(absDiff.y >= 20.0f) {
                (lbl_1_bss_120C[player].unk01A) ? (flip = -1.0f) : (flip = 1.0f);
                (diff.y > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk340 = flip*(dir*lbl_1_bss_120C[player].unk320);
            } else {
                lbl_1_bss_120C[player].unk2FC++;
            }
            break;

        case 1:
            if((M555_ABS(lbl_1_bss_120C[player].unk024) >= 6.0f) && lbl_1_bss_120C[player].unk304 == 0) {
                (lbl_1_bss_120C[player].unk01A) ? (flip = -1.0f) : (flip = 1.0f);
                (lbl_1_bss_120C[player].unk024 > 0.0f) ? (dir = -1.0f) : (dir = 1.0f);
                lbl_1_bss_120C[player].unk340 = flip*(dir*lbl_1_bss_120C[player].unk324);
            } else {
                lbl_1_bss_120C[player].unk2FC++;
            }
            break;

        case 2:
            if(absDiff.y >= 20.0f) {
                lbl_1_bss_120C[player].unk2FC = 0;
            } else {
                doneNum++;
            }
            break;
    }
    switch(lbl_1_bss_120C[player].unk2FE) {
        case 0:
            if(absDiff.x >= 20.0f) {
                (diff.x > 0.0f) ? (dir = 1.0f) : (dir = -1.0f);
                lbl_1_bss_120C[player].unk33C = dir*lbl_1_bss_120C[player].unk320;
            } else {
                lbl_1_bss_120C[player].unk2FE++;
            }
            break;

        case 1:
            if((M555_ABS(lbl_1_bss_120C[player].unk020) >= 6.0f) && lbl_1_bss_120C[player].unk302 == 0) {
                (lbl_1_bss_120C[player].unk020 > 0.0f) ? (dir = -1.0f) : (dir = 1.0f);
                lbl_1_bss_120C[player].unk33C = dir*lbl_1_bss_120C[player].unk324;
            } else {
                lbl_1_bss_120C[player].unk2FE++;
            }
            break;

        case 2:
            if(absDiff.x >= 20.0f) {
                lbl_1_bss_120C[player].unk2FE = 0;
            } else {
                doneNum++;
            }
            break;
    }
    if(doneNum >= 2) {
        lbl_1_bss_120C[player].unk2FC = 0;
        lbl_1_bss_120C[player].unk2FE = 0;
        result = 1;
    }
    return result;
}

/* asm 21445-21593, 142 insns. Whether model player+33 is at least dist from (unk314, unk318). */
s16 fn_1_171C8(s16 player, float dist)
{
    float diff[2];
    float len;
    s16 result;

    result = 0;
    diff[0] = lbl_1_bss_120C[player].unk314.x-lbl_1_bss_3030->models[player+33].pos.x;
    diff[1] = lbl_1_bss_120C[player].unk314.y-lbl_1_bss_3030->models[player+33].pos.y;
    len = sqrt((diff[0]*diff[0])+(diff[1]*diff[1]));
    if(len >= dist) {
        result = 1;
    }
    return result;
}

/* asm 21596-21781, 177 insns. Whether any live object (bss_B88) above minZ and at most 121 in z is within dist of pos, 30 up. */
s16 fn_1_17400(HuVecF pos, float dist, float minZ)
{
    HuVecF diff;
    float len;
    s16 result;
    s16 i;
    s16 mdlNo;

    result = 0;
    for(i=0; i<50; i++) {
        mdlNo = i+35;
        if(lbl_1_bss_B88[i].unk000 != 0 && lbl_1_bss_3030->models[mdlNo].pos.z > minZ && lbl_1_bss_3030->models[mdlNo].pos.z <= 121.0f) {
            diff.x = lbl_1_bss_3030->models[mdlNo].pos.x-pos.x;
            diff.y = lbl_1_bss_3030->models[mdlNo].pos.y-(30.0f+pos.y);
            len = sqrt((diff.x*diff.x)+(diff.y*diff.y));
            if(len < dist) {
                result = 1;
            }
        }
    }
    return result;
}

/* asm 21784-24263, 2386 insns. */
void fn_1_176C4(s16 player)
{
    HuVecF end;
    HuVecF pos;
    HuVecF cpos;
    HuVecF dir;
    HuVecF v;
    HuVecF w;
    float dist;
    float cosv;
    float t;
    float u;
    float limit = 180.0f;
    s16 count = 0;
    HuVecF wall[4] = {
        { 1.0f, 0.0f, -531.0f },
        { 1.0f, 0.0f, 531.0f },
        { 0.0f, 1.0f, -317.0f },
        { 0.0f, 1.0f, 317.0f }
    };
    float c;
    float wc;
    float scale;
    float zs;
    float a;
    float b;
    float wa;
    float wb;
    float angle;
    s16 i;
    s16 j;
    s16 flagX;
    s16 flagY;
    s16 k;
    s16 mdlNo;

    for(i=0; i<36; i++) {
        lbl_1_bss_120C[player].unk210[i] = 2000.0f;
        lbl_1_bss_120C[player].unk060[i].x = 0.0f;
        lbl_1_bss_120C[player].unk060[i].y = 0.0f;
        lbl_1_bss_120C[player].unk060[i].z = 0.0f;
        lbl_1_bss_120C[player].unk2A0[i] = -1;
    }
    pos = lbl_1_bss_3030->models[player+33].pos;
    pos.y += 30.0f;
    for(i=0, angle=0.0f; i<8; i++, angle+=45.0f) {
        end.x = pos.x+(10.0*cos((M_PI*angle)/180.0));
        end.y = pos.y+(10.0*sin((M_PI*angle)/180.0));
        dir.x = end.x-pos.x;
        dir.y = end.y-pos.y;
        a = end.y-pos.y;
        b = pos.x-end.x;
        c = (-a*pos.x)-(b*pos.y);
        for(j=0; j<50; j++) {
            mdlNo = j+35;
            cpos = lbl_1_bss_3030->models[mdlNo].pos;
            if(lbl_1_bss_B88[j].unk000 != 0 && cpos.z > -13000.0f && cpos.z < 150.0f) {
                v.x = cpos.x-pos.x;
                v.y = cpos.y-pos.y;
                flagX = 0;
                flagY = 0;
                if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                    if(v.x > 0.0f) {
                        flagX = 1;
                    }
                } else if(90.0f == angle || 270.0f == angle) {
                    flagX = 1;
                } else if(v.x < 0.0f) {
                    flagX = 1;
                }
                if(angle > 0.0f && angle < 180.0f) {
                    if(v.y > 0.0f) {
                        flagY = 1;
                    }
                } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                    flagY = 1;
                } else if(v.y < 0.0f) {
                    flagY = 1;
                }
                dist = sqrt(v.x*v.x+v.y*v.y);
                if(flagX && flagY) {
                    cosv = dir.x*dir.x+dir.y*dir.y;
                    t = -1.0f*((dir.x*(end.x-cpos.x))+(dir.y*(end.y-cpos.y)));
                    if(cosv) {
                        u = t/cosv;
                    } else {
                        u = 0.0f;
                    }
                    v.x = end.x+(dir.x*u);
                    v.y = end.y+(dir.y*u);
                    w.x = cpos.x-v.x;
                    w.y = cpos.y-v.y;
                    dist = sqrt(w.x*w.x+w.y*w.y);
                    if(v.x >= -530.0f && v.x <= 530.0f && v.y >= -316.0f && v.y <= 316.0f && dist < limit) {
                        w.x = v.x-pos.x;
                        w.y = v.y-pos.y;
                        dist = sqrt(w.x*w.x+w.y*w.y);
                        flagX = angle;
                        if(flagX%90) {
                            scale = sqrt(200.0);
                        } else {
                            scale = 10.0f;
                        }
                        if(cpos.z/200.0f > 0.0f) {
                            zs = cpos.z/200.0f;
                        } else {
                            zs = -1.0f*(cpos.z/200.0f);
                        }
                        if(!(zs > 50.0f+(15.0f+(dist/scale)))) {
                            if(lbl_1_bss_120C[player].unk210[i] >= dist) {
                                w.x = v.x-pos.x;
                                w.y = v.y-pos.y;
                                dist = sqrt(w.x*w.x+w.y*w.y);
                                if(dist) {
                                    scale = (dist-150.0f)/dist;
                                } else {
                                    scale = 0.0f;
                                }
                                v.y -= 30.0f;
                                lbl_1_bss_120C[player].unk060[i] = v;
                                lbl_1_bss_120C[player].unk210[i] = dist;
                                lbl_1_bss_120C[player].unk2A0[i] = 0;
                            }
                        }
                    }
                }
            }
        }
        pos = lbl_1_bss_3030->models[player+33].pos;
        pos.y += 30.0f;
        end.x = pos.x+(10.0*cos((M_PI*angle)/180.0));
        end.y = pos.y+(10.0*sin((M_PI*angle)/180.0));
        dir.x = end.x-pos.x;
        dir.y = end.y-pos.y;
        a = end.y-pos.y;
        b = pos.x-end.x;
        c = (-a*pos.x)-(b*pos.y);
        for(k=0; k<4; k++) {
            wa = wall[k].x;
            wb = wall[k].y;
            wc = wall[k].z;
            if(sqrt(a*a+b*b) && sqrt(wa*wa+wb*wb)) {
                cosv = ((a*wa)+(b*wb))/(sqrt(a*a+b*b)*sqrt(wa*wa+wb*wb));
            } else {
                cosv = 0.0f;
            }
            if(cosv < 0.984f && cosv > -0.984f) {
                if(a && b && wa && wb) {
                    v.x = wa*(-b/a);
                    v.y = -1.0f*(wa*(-c/a));
                    v.x += wb;
                    v.y -= wc;
                    if(v.x) {
                        w.y = v.y/v.x;
                    } else {
                        w.y = 0.0f;
                    }
                    w.x = ((-wb*w.y)-wc)/wa;
                } else if(!a && b && wa && wb) {
                    w.y = -c/b;
                    w.x = ((-wb*w.y)-wc)/wa;
                } else if(a && !b && wa && wb) {
                    w.x = -c/a;
                    w.y = ((-wa*w.x)-wc)/wb;
                } else if(a && b && !wa && wb) {
                    w.y = -wc/wb;
                    w.x = ((-b*w.y)-c)/a;
                } else if(a && b && wa && !wb) {
                    w.x = -wc/wa;
                    w.y = ((-a*w.x)-c)/b;
                } else if(!a && b && wa && !wb) {
                    w.y = -c/b;
                    w.x = -wc/wa;
                } else if(a && !b && !wa && wb) {
                    w.x = -c/a;
                    w.y = -wc/wb;
                }
                v.x = w.x-pos.x;
                v.y = w.y-pos.y;
                flagX = 0;
                flagY = 0;
                if((angle >= 0.0f && angle < 90.0f) || (angle > 270.0f && angle <= 360.0f)) {
                    if(v.x > 0.0f) {
                        flagX = 1;
                    }
                } else if(90.0f == angle || 270.0f == angle) {
                    flagX = 1;
                } else if(v.x < 0.0f) {
                    flagX = 1;
                }
                if(angle > 0.0f && angle < 180.0f) {
                    if(v.y > 0.0f) {
                        flagY = 1;
                    }
                } else if(0.0f == angle || 180.0f == angle || 360.0f == angle) {
                    flagY = 1;
                } else if(v.y < 0.0f) {
                    flagY = 1;
                }
                if(w.x >= -531.0f && w.x <= 531.0f && w.y >= -317.0f && w.y <= 317.0f && flagX && flagY) {
                    v.x = w.x-pos.x;
                    v.y = w.y-pos.y;
                    dist = sqrt(v.x*v.x+v.y*v.y);
                    if(lbl_1_bss_120C[player].unk210[i] >= dist) {
                        w.y -= 30.0f;
                        lbl_1_bss_120C[player].unk060[i] = w;
                        lbl_1_bss_120C[player].unk210[i] = dist;
                        lbl_1_bss_120C[player].unk2A0[i] = 1;
                    }
                }
            } else {
                count++;
            }
        }
    }
    for(i=0, j=0, dist=0.0f; i<8; i++) {
        if(lbl_1_bss_120C[player].unk210[i] > dist && lbl_1_bss_120C[player].unk210[i] != 2000.0f) {
            dist = lbl_1_bss_120C[player].unk210[i];
            j = i;
        }
    }
    if((int)lbl_1_bss_120C[player].unk060[j].x < -630 || (int)lbl_1_bss_120C[player].unk060[j].x > 630
        || (int)lbl_1_bss_120C[player].unk060[j].y < -416 || (int)lbl_1_bss_120C[player].unk060[j].y > 416) {
        return;
    }
    lbl_1_bss_120C[player].unk2F0 = lbl_1_bss_120C[player].unk060[j];
    lbl_1_bss_120C[player].unk308 = lbl_1_bss_120C[player].unk060[j];
    lbl_1_bss_120C[player].unk314 = lbl_1_bss_3030->models[player+33].pos;
    angle = 45.0f*j;
}

/* asm 24266-24841, 553 insns. */
s16 fn_1_19C0C(s16 player)
{
    HuVecF b;
    HuVecF a;
    HuVecF c;
    HuVecF d;
    HuVecF p;
    HuVecF e;
    HuVecF min;
    HuVecF max;
    float t;
    float unk;
    float lenSq;
    float u;
    float len;
    float radius;
    s16 mdlNo;
    s16 i;
    s16 result;

    result = 0;
    radius = 130.0f;
    unk = 0.0f;
    a = lbl_1_bss_3030->models[player+33].pos;
    a.y += 30.0f;
    b = lbl_1_bss_120C[player].unk308;
    d.x = b.x-a.x;
    d.y = b.y-a.y;
    len = sqrt(d.x*d.x+d.z*d.z);
    len /= 300.0f;
    b.x = a.x+(d.x*len);
    b.y = a.y+(d.y*len);
    d.x = b.x-a.x;
    d.y = b.y-a.y;
    (a.x > b.x) ? (max.x = a.x, min.x = b.x) : (max.x = b.x, min.x = a.x);
    (a.y > b.y) ? (max.y = a.y, min.y = b.y) : (max.y = b.y, min.y = a.y);
    max.x += radius;
    min.x -= radius;
    max.y += radius;
    min.y -= radius;
    for(i=0; i<50; i++) {
        mdlNo = i+35;
        c = lbl_1_bss_3030->models[mdlNo].pos;
        if(lbl_1_bss_B88[i].unk000 != 0 && c.z >= -12000.0f && c.x <= max.x && c.x >= min.x && c.y <= max.y && c.y >= min.y) {
            lenSq = d.x*d.x+d.y*d.y;
            t = -1.0f*((d.x*(b.x-c.x))+(d.y*(b.y-c.y)));
            if(lenSq) {
                u = t/lenSq;
            } else {
                u = 0.0f;
            }
            p.x = b.x+(d.x*u);
            p.y = b.y+(d.y*u);
            e.x = c.x-p.x;
            e.y = c.y-p.y;
            len = sqrt(e.x*e.x+e.y*e.y);
            if(len < radius) {
                e.x = p.x-a.x;
                e.y = p.y-a.y;
                len = sqrt(e.x*e.x+e.y*e.y);
                if(len <= 300.0f) {
                    result = 1;
                }
            }
        }
    }
    return result;
}

/* asm 24844-24993, 145 insns. */
s16 fn_1_1A4B0(s16 player)
{
    HuVecF center;
    HuVecF pos;
    float dist;
    float angle;
    s16 result;
    s16 i;

    result = 0;
    i = 0;
    center = lbl_1_bss_3030->models[player+169].pos;
    do {
        angle = frandmod(360);
        dist = 50.0f+frandmod(200);
        pos.x = center.x+(dist*cos((M_PI*angle)/180.0));
        pos.y = center.y+(dist*sin((M_PI*angle)/180.0));
        if(pos.x <= 530.0f && pos.x >= -530.0f && 30.0f+pos.y <= 316.0f && 30.0f+pos.y >= -316.0f) {
            lbl_1_bss_120C[player].unk308 = pos;
            result = 1;
            break;
        }
    } while(i++ < 20);
    return result;
}

/* asm 24996-25100, 99 insns. */
s16 fn_1_1A6F4(s16 player)
{
    HuVecF pos;
    s16 i;
    s16 result;

    result = 0;
    for(i=0; i<50; i++) {
        pos = lbl_1_bss_3030->models[i+35].pos;
        if(lbl_1_bss_B88[i].unk000 != 0 && pos.z < -10000.0f && pos.z > -16000.0f && pos.x <= 530.0f && pos.x >= -530.0f && 30.0f+pos.y <= 316.0f && 30.0f+pos.y >= -316.0f) {
            lbl_1_bss_120C[player].unk308 = pos;
            result = 1;
            break;
        }
    }
    return result;
}

/* asm 25103-25179, 73 insns. */
s16 fn_1_1A880(s16 player, s16 mode)
{
    s16 mdlNo;
    s16 result;

    result = 0;
    mdlNo = player+169;
    if(mode == 0) {
        if(lbl_1_bss_3030->models[mdlNo].pos.x <= 100.0f && lbl_1_bss_3030->models[mdlNo].pos.x >= -100.0f
            && lbl_1_bss_3030->models[mdlNo].pos.y <= 100.0f && lbl_1_bss_3030->models[mdlNo].pos.y >= -150.0f) {
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}

/* Unreferenced. */
float lbl_1_data_37C[25] = {
    0.0f, 0.0f, 0.0f, 0.0f, 913.0f, 0.0f, -1177.0f, 993.0f, 0.0f, -1038.0f, 550.0f, 1000.0f, -3250.0f,
    593.0f, 312.0f, -1119.0f, -462.0f, 330.0f, -1100.0f, -1000.0f, 40.0f, -2100.0f, -2500.0f, 0.0f, -3900.0f
};
