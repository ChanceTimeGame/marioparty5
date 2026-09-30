/*
 * m545dll/stage.c -- the arena, the duellists' models and motions, and the
 * five stage props. Written from the reference assembly, functions in
 * reference order; line ranges are into
 * build/mp5-asm/m545Dll/asm/REL/m545Dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head C: fn_1_77EC (DS_S_WORKINIT), fn_1_7CE4/7D08 (DS_S_CHARMOT), fn_1_803C
 * (DS_S_PADREAD_262), fn_1_8454 (DS_S_CHARMOTION, 5 motions, speedCur -1.0f,
 * DS_CHARMOTION_NOSPEED), fn_1_8580 (DS_S_MOTIONEXEC_C, DS_MOTIONEXEC_C_UNSET)
 * and fn_1_88F0..A7B8 with the table lbl_1_data_3A0 (DS_S_PROPS_B on models
 * 25-32) come from the header and sit in the object's second .text section.
 * See NOTES.md for the per-function result.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/frand.h"

#include "REL/m545Dll/m545.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_310[12] = {
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

M545_WORK *lbl_1_bss_9B8;           /* set by fn_1_77EC */

/* --- the duel stage framework (REL/duelstage.h), work head C --- */

#define DS_WORK                 M545_WORK
#define DS_STAGEWORK            lbl_1_bss_9B8
#define DS_CHARMOTION_NUM       5
#define DS_CHARMOTION_SPEEDCUR  -1.0f
#define DS_CHARMOTION_NOSPEED
#define DS_CHARMDL              36
#define DS_MOTIONEXEC_C_UNSET
#define DS_FN_WorkInit          fn_1_77EC
#define DS_FN_CharMotDataSet    fn_1_7CE4
#define DS_FN_CharMotIdSet      fn_1_7D08
#define DS_FN_PadRead262        fn_1_803C
#define DS_FN_CharMotionCreate  fn_1_8454
#define DS_FN_MotionExecC       fn_1_8580
#define DS_PROPTBL              lbl_1_data_3A0
#define DS_PROPEXEC_NUM         5
#define DS_PROPMDL              24
#define DS_FN_PropExec          fn_1_88F0
#define DS_FN_PropSwing         fn_1_8944
#define DS_FN_PropSway          fn_1_8F7C
#define DS_FN_PropPendulum      fn_1_94C8
#define DS_FN_PropRoll          fn_1_9DAC
#define DS_FN_PropSlide         fn_1_A7B8

/* asm 1-128, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 129-266, 171 insns. The arena: twelve models from stageDataTbl[7..18], placed from lbl_1_data_310. */
void fn_1_7A38(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_9B8->stageNo = stageNo;
    for(i=0; i<12; i++) {
        no = i+24;
        id = lbl_1_bss_9B8->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum((lbl_1_bss_9B8->stageDataTbl+7)[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelLayerSet(id, 0);
        Hu3DModelPosSetV(id, &lbl_1_data_310[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_9B8->models[no].pos.x = lbl_1_data_310[i].x;
        lbl_1_bss_9B8->models[no].pos.y = lbl_1_data_310[i].y;
        lbl_1_bss_9B8->models[no].pos.z = lbl_1_data_310[i].z;
        lbl_1_bss_9B8->models[no].rot.x = 0.0f;
        lbl_1_bss_9B8->models[no].rot.y = 0.0f;
        lbl_1_bss_9B8->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        if(i == 0) {
            Hu3DModelShadowMapSet(id);
        }
    }
}

/* asm 267-280, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 281-422, 196 insns. The two duellists, 300 apart, and their idle motion. */
void fn_1_7D2C(void)
{
    int i;
    M545_PLAYER *pl;

    for(i=0; i<2; i++) {
        (lbl_1_bss_9B8->models+36)[i].modelId = CharModelCreate(lbl_1_bss_9B8->chr[i].charNo, 1);
        Hu3DModelPosSet((lbl_1_bss_9B8->models+36)[i].modelId, -150.0f+(300.0f*i), 100.0f, 0.0f);
        CharModelFxFlagSet(lbl_1_bss_9B8->chr[i].charNo, 1);
        Hu3DModelLayerSet(lbl_1_bss_9B8->models[i+36].modelId, 2);
        Hu3DModelShadowSet((lbl_1_bss_9B8->models+36)[i].modelId);
        CharModelStepFxSet(lbl_1_bss_9B8->chr[i].charNo, 1);
        lbl_1_bss_9B8->models[i+36].pos.x = -150.0f+(300.0f*i);
        lbl_1_bss_9B8->models[i+36].pos.y = 100.0f;
        lbl_1_bss_9B8->models[i+36].pos.z = 0.0f;
        lbl_1_bss_9B8->models[i+36].rot.x = 0.0f;
        lbl_1_bss_9B8->models[i+36].rot.y = 0.0f;
        lbl_1_bss_9B8->models[i+36].rot.z = 0.0f;
        pl = &lbl_1_bss_9B8->player[i];
        pl->motNo = 0;
        pl->speed = 1.0f;
        pl->attr = HU3D_MOTATTR_LOOP;
        pl->attrReset = 0;
        pl->time = 0.0f;
    }
}

/* asm 423-898, 262 + 75 + 220 insns. */
#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC_C
#include "REL/duelstage.h"

/*
 * asm 899-3506, the prop table and 21 + 398 + 339 + 569 + 643 + 107 insns of
 * props (DS_S_PROPS_B, m547's and m548's on models 25-32).
 */
#define DS_S_PROPS_B
#include "REL/duelstage.h"
