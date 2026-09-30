/*
 * m580Dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/stage.s.
 */

#include "REL/m580Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3A8 */ /* double lbl_1_rodata_3A8 = 180; */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = 0.0f; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = 120.0f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = 180.0f; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = 4503601774854144; */
/* 0x3C8 */ /* double lbl_1_rodata_3C8 = 90; */

/* --- .data --- */
/* 0x298 */ char lbl_1_data_298[5][10] = { "wall", "post_R", "post_L", "post_R_C", "post_L_C" }; /* collision object names (fn_1_83FC) */
/* 0x2CC */ s32 lbl_1_data_2CC[5] = { 12, 8, 8, 4, 4 }; /* M580_COLLOBJ.unk004 per name */
/* 0x2E0 */ char lbl_1_data_2E0[6][8] = { "1p", "2p", "3p", "4p", "k_red", "k_blue" }; /* fn_1_89A8 start-position objects */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xB0 */ OMOBJ *lbl_1_bss_B0; /* stage object; player.c fn_1_8358 stores it (dtk size 8: trailing section pad) */

/* --- functions (reference order) --- */
/* 182 insns. Stage object: models, goal model (fn_1_8710), collision records. */
void fn_1_83FC(OMOBJ *obj)
{
    M580_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;
    HSFOBJECT *hsfObj;
    M580_COLLOBJ *col;

    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860000, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[0] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 6);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860001, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[1] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 4);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860002, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[2] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 3);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860003, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[3] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 2);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860004, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[4] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860005, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[5] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860006, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[6] = mdlId;
    Hu3DModelLayerSet(mdlId, 1);
    Hu3DZClearLayerSet(1);
    Hu3DBGColorSet(178, 178, 178);
    fn_1_8710(obj);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860010, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[9] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 5; i++) {
        hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_298[i]);
        if (hsfObj != NULL) {
            col = &work->unk00C[i];
            col->unk000 = 1;
            col->unk004 = lbl_1_data_2CC[i];
            col->unk008 = 3;
            col->unk00C = i;
            col->unk010 = 10;
            col->unk014 = obj;
            col->unk018 = NULL;
            col->unk01C = NULL;
            fn_1_1229C(col, hsfObj);
            fn_1_122D0(col);
            fn_1_11E3C(col);
        }
    }
    obj->objFunc = fn_1_86D4;
}

/* 15 insns */
void fn_1_86D4(OMOBJ *obj)
{
    fn_1_87A4(obj);
    obj->work[0]++;
}

/* 37 insns. Goal model (mdlId[7]). */
void fn_1_8710(OMOBJ *obj)
{
    M580_STAGE *work = obj->data;
    HU3DMODELID mdlId;

    work->unk000 = 0;
    work->unk004 = 0;
    work->unk008 = -1;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860008, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[7] = mdlId;
    Hu3DModelAttrSet(mdlId, 0x40000001);
    Hu3DModelLayerSet(mdlId, 2);
}

/* 129 insns. Goal model motion: 0 idle (0..120), 1/2 = fn_1_D7B8() + 1 for 180 frames after a goal. */
void fn_1_87A4(OMOBJ *obj)
{
    M580_STAGE *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[7];
    s32 motNo = 0;

    switch (work->unk000) {
        case 0:
            if (MgSeqModeGet() != MGSEQ_MODE_MAIN) {
                break;
            }
            work->unk000++;
        case 1:
            if (fn_1_D544()) {
                break;
            }
            work->unk000++;
        case 2:
            if (!fn_1_D544()) {
                break;
            }
            work->unk000++;
            work->unk004 = 0;
        case 3:
            if (MgSeqModeGet() != MGSEQ_MODE_MAIN) {
                break;
            }
            motNo = fn_1_D7B8() + 1;
            if (!(++work->unk004 < 180.0)) {
                work->unk000 = 0;
            }
            break;
    }
    if (work->unk008 != motNo) {
        work->unk008 = motNo;
        switch (motNo) {
            case 0:
                Hu3DMotionStartEndSet(mdlId, 0.0f, 120.0f);
                Hu3DMotionTimeSet(mdlId, 0.0f);
                break;
            case 1:
                Hu3DMotionStartEndSet(mdlId, 120.0f, 180.0f);
                Hu3DMotionTimeSet(mdlId, 120.0f);
                break;
            case 2:
                Hu3DMotionStartEndSet(mdlId, 180.0f, Hu3DMotionMaxTimeGet(mdlId));
                Hu3DMotionTimeSet(mdlId, 180.0f);
                break;
        }
    }
}

/* 47 insns. Start position/facing of object lbl_1_data_2E0[no] ("1p".."4p",
 * "k_red", "k_blue") in mdlId[5]; returns 1 while its motion still plays. */
s32 fn_1_89A8(s32 no, HuVecF *pos, float *rotY)
{
    OMOBJ *obj = lbl_1_bss_B0;
    HU3DMODELID mdlId = obj->mdlId[5];
    HSFOBJECT *hsfObj;

    hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_2E0[no]);
    if (hsfObj != NULL) {
        pos->x = hsfObj->mesh.curr.pos.x;
        pos->y = hsfObj->mesh.curr.pos.y;
        pos->z = hsfObj->mesh.curr.pos.z;
        *rotY = 90.0 + hsfObj->mesh.curr.rot.y;
    }
    return !Hu3DMotionEndCheck(mdlId);
}
