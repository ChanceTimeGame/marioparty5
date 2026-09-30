/*
 * m552dll/stage.c -- the arena, the duellists' models and motions. Written
 * from the reference assembly, functions in reference order; line ranges are
 * into build/mp5-asm/m552dll/asm/REL/m552dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head A: fn_1_B33C (DS_S_WORKINIT), fn_1_B810/B834 (DS_S_CHARMOT), fn_1_BADC
 * (DS_S_PADREAD), fn_1_BF98 (DS_S_CHARMOTION, 2 motions, DS_CHARMOTION_CLEAR)
 * and fn_1_C14C (DS_S_MOTIONEXEC, DS_SHIFT_POLL and DS_MOTIONEXEC_NOHANDOVER)
 * come from the header and sit in the object's second .text section. See
 * NOTES.md for the per-function result.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"

#include "REL/m552dll/m552.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_568[6] = {
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f },
    { 0.0f, -100.0f, 0.0f }
};

/* --- .bss --- */

M552_WORK *lbl_1_bss_4A28;          /* set by fn_1_B33C */

/* --- the duel stage framework (REL/duelstage.h), work head A --- */

#define DS_WORK                 M552_WORK
#define DS_STAGEWORK            lbl_1_bss_4A28
#define DS_CHARMDL              0
#define DS_MOTIONEXEC_NUM       2
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_CHARMOTION_NUM       2
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_FN_WorkInit          fn_1_B33C
#define DS_FN_CharMotDataSet    fn_1_B810
#define DS_FN_CharMotIdSet      fn_1_B834
#define DS_FN_PadRead           fn_1_BADC
#define DS_FN_CharMotionCreate  fn_1_BF98
#define DS_FN_MotionExec        fn_1_C14C

/* asm 1-128, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 129-256, 162 insns. The arena: six models from stageDataTbl[0..5] at 2-7, placed from lbl_1_data_568. */
void fn_1_B588(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_4A28->stageNo = stageNo;
    for(i=0; i<6; i++) {
        no = i+2;
        id = lbl_1_bss_4A28->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_4A28->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &lbl_1_data_568[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 1.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_4A28->models[no].pos.x = lbl_1_data_568[i].x;
        lbl_1_bss_4A28->models[no].pos.y = lbl_1_data_568[i].y;
        lbl_1_bss_4A28->models[no].pos.z = lbl_1_data_568[i].z;
        lbl_1_bss_4A28->models[no].rot.x = 0.0f;
        lbl_1_bss_4A28->models[no].rot.y = 0.0f;
        lbl_1_bss_4A28->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
}

/* asm 257-270, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 271-391, 161 insns. The two duellists, facing each other across the arena. */
void fn_1_B858(void)
{
    int i;

    for(i=0; i<2; i++) {
        lbl_1_bss_4A28->models[i].modelId = CharModelCreate(lbl_1_bss_4A28->chr[i].charNo, 1);
        Hu3DModelPosSet(lbl_1_bss_4A28->models[i].modelId, (i*500)-250, 0.0f, 0.0f);
        lbl_1_bss_4A28->models[i].pos.x = (i*700)-350;
        lbl_1_bss_4A28->models[i].pos.y = 0.0f;
        lbl_1_bss_4A28->models[i].pos.z = 500.0f;
        lbl_1_bss_4A28->models[i].rot.x = 0.0f;
        lbl_1_bss_4A28->models[i].rot.y = (i*30)+165;
        lbl_1_bss_4A28->models[i].rot.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_4A28->models[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(lbl_1_bss_4A28->models[i].modelId, 1);
        Hu3DModelLayerSet(lbl_1_bss_4A28->models[i].modelId, 0);
        Hu3DModelAttrReset(lbl_1_bss_4A28->models[i].modelId, HU3D_ATTR_DISPOFF);
    }
}

/* asm 392-946, 303 + 109 + 237 insns. */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"
