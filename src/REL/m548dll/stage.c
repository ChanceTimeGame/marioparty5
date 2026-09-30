/*
 * m548dll/stage.c -- the arena, the two duellists' models and motions, and
 * five per-frame prop updaters. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m548dll/asm/REL/m548dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head B: fn_1_6104 (DS_S_WORKINIT), fn_1_65E8/660C (DS_S_CHARMOT),
 * fn_1_6890 (DS_S_PADREAD) and fn_1_6D4C (DS_S_CHARMOTION, 5 motions,
 * speedCur -1.0f) and fn_1_6EA0 (DS_S_MOTIONEXEC_B, the 132-instruction driver
 * m542/m547 share) come from the header and sit in the object's second .text
 * section.
 * fn_1_70B0, 7104, 773C, 7C88, 856C and 8F78 (DS_S_PROPS_B, with the table
 * lbl_1_data_5C0) are identical to m547dll's and come from the header too.
 * See NOTES.md for the per-function result.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/gamemes.h"
#include "game/flag.h"
#include "game/printfunc.h"

#include "datadir_enum.h"

#include "REL/m548dll/m548.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_530[12] = {
    { 0.0f, 0.0f, 0.0f },
    { 913.0f, 0.0f, -1177.0f },
    { 993.0f, 0.0f, -1038.0f },
    { 550.0f, 1000.0f, -3250.0f },
    { 593.0f, 312.0f, -1119.0f },
    { -462.0f, 330.0f, -1100.0f },
    { -1000.0f, 40.0f, -2100.0f },
    { -2500.0f, 0.0f, -3900.0f },
    { -1000.0f, 0.0f, -2100.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }

};

/* --- .bss --- */

M548_WORK *lbl_1_bss_5F8;           /* set by fn_1_6104 */

/* --- the duel stage framework (REL/duelstage.h), work head B --- */

#define DS_WORK                 M548_WORK
#define DS_STAGEWORK            lbl_1_bss_5F8
#define DS_CHARMDL              12
#define DS_CHARMOTION_NUM       5
#define DS_CHARMOTION_SPEEDCUR  -1.0f
#define DS_FN_WorkInit          fn_1_6104
#define DS_FN_CharMotDataSet    fn_1_65E8
#define DS_FN_CharMotIdSet      fn_1_660C
#define DS_FN_PadRead           fn_1_6890
#define DS_FN_CharMotionCreate  fn_1_6D4C
#define DS_FN_MotionExecB       fn_1_6EA0
#define DS_PROPTBL              lbl_1_data_5C0
#define DS_PROPEXEC_NUM         5
#define DS_PROPMDL              0
#define DS_FN_PropExec          fn_1_70B0
#define DS_FN_PropSwing         fn_1_7104
#define DS_FN_PropSway          fn_1_773C
#define DS_FN_PropPendulum      fn_1_7C88
#define DS_FN_PropRoll          fn_1_856C
#define DS_FN_PropSlide         fn_1_8F78

/* asm 9-165, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-338, 166 insns. The arena: twelve models, placed from lbl_1_data_530. */
void fn_1_6350(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_5F8->stageNo = stageNo;
    for(i=0; i<12; i++) {
        no = (s16)i;
        id = lbl_1_bss_5F8->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_5F8->stageDataTbl[no], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &lbl_1_data_530[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_5F8->models[no].pos.x = lbl_1_data_530[i].x;
        lbl_1_bss_5F8->models[no].pos.y = lbl_1_data_530[i].y;
        lbl_1_bss_5F8->models[no].pos.z = lbl_1_data_530[i].z;
        lbl_1_bss_5F8->models[no].rot.x = 0.0f;
        lbl_1_bss_5F8->models[no].rot.y = 0.0f;
        lbl_1_bss_5F8->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        if(i == 0) {
            Hu3DModelShadowMapSet(id);
        }
    }
}

/* asm 341-364, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 367-524, 152 insns. The two duellists, 300 apart, facing each other. */
void fn_1_6630(void)
{
    int i;

    for(i=0; i<2; i++) {
        (lbl_1_bss_5F8->models+12)[i].modelId = CharModelCreate(lbl_1_bss_5F8->chr[i].charNo, 1);
        Hu3DModelPosSet((lbl_1_bss_5F8->models+12)[i].modelId, (i*300)-150, 100.0f, 0.0f);
        Hu3DModelRotSet((lbl_1_bss_5F8->models+12)[i].modelId, 0.0f, 90.0f+(180.0f*i), 0.0f);
        if(i != 0) {
            Hu3DModelAttrSet((lbl_1_bss_5F8->models+12)[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet((lbl_1_bss_5F8->models+12)[i].modelId, 1.0f);
            Hu3DMotionTimeSet((lbl_1_bss_5F8->models+12)[i].modelId, 0.0f);
        } else {
            Hu3DModelAttrReset((lbl_1_bss_5F8->models+12)[i].modelId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet((lbl_1_bss_5F8->models+12)[i].modelId, 0.0f);
            Hu3DMotionTimeSet((lbl_1_bss_5F8->models+12)[i].modelId, 25.0f);
        }
    }
}

/*
 * asm 527-3229, 303 + 85 + 132 insns, then the prop table and 21 + 398 +
 * 339 + 569 + 643 + 107 insns of props (DS_S_PROPS_B, shared with m547).
 */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC_B
#define DS_S_PROPS_B
#include "REL/duelstage.h"
