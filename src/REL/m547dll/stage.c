/*
 * m547dll/stage.c -- the arena, the duellists' models and motions, and the
 * five stage props. Written from the reference assembly, functions in
 * reference order; line ranges are into
 * build/mp5-asm/m547dll/asm/REL/m547dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head B: fn_1_86B8 (DS_S_WORKINIT), fn_1_8B9C/8BC0 (DS_S_CHARMOT),
 * fn_1_8D2C (DS_S_PADREAD), fn_1_91E8 (DS_S_CHARMOTION, 7 motions, speedCur
 * 1.0f), fn_1_933C (DS_S_MOTIONEXEC_B) and fn_1_954C..B414 with the table
 * lbl_1_data_3EC (DS_S_PROPS_B, m548's props) come from the header and sit in
 * the object's second .text section. See NOTES.md for the per-function result.
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
#include "game/gamemes.h"
#include "game/flag.h"

#include "datadir_enum.h"

#include "REL/m547dll/m547.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_350[13] = {
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
    { 0.0f, 0.0f, 0.0f },
    { 0.0f, 0.0f, 0.0f }
};

/* --- .bss --- */

M547_WORK *lbl_1_bss_6E8;           /* set by fn_1_86B8 */

/* --- the duel stage framework (REL/duelstage.h), work head B --- */

#define DS_WORK                 M547_WORK
#define DS_STAGEWORK            lbl_1_bss_6E8
#define DS_CHARMDL              13
#define DS_CHARMOTION_NUM       7
#define DS_CHARMOTION_SPEEDCUR  1.0f
#define DS_FN_WorkInit          fn_1_86B8
#define DS_FN_CharMotDataSet    fn_1_8B9C
#define DS_FN_CharMotIdSet      fn_1_8BC0
#define DS_FN_PadRead           fn_1_8D2C
#define DS_FN_CharMotionCreate  fn_1_91E8
#define DS_FN_MotionExecB       fn_1_933C
#define DS_PROPTBL              lbl_1_data_3EC
#define DS_PROPEXEC_NUM         5
#define DS_PROPMDL              0
#define DS_FN_PropExec          fn_1_954C
#define DS_FN_PropSwing         fn_1_95A0
#define DS_FN_PropSway          fn_1_9BD8
#define DS_FN_PropPendulum      fn_1_A124
#define DS_FN_PropRoll          fn_1_AA08
#define DS_FN_PropSlide         fn_1_B414

/* asm 9-165, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-338, 166 insns. The arena: thirteen models, placed from lbl_1_data_350. */
void fn_1_8904(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_6E8->stageNo = stageNo;
    for(i=0; i<13; i++) {
        no = (s16)i;
        id = lbl_1_bss_6E8->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_6E8->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &lbl_1_data_350[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_6E8->models[no].pos.x = lbl_1_data_350[i].x;
        lbl_1_bss_6E8->models[no].pos.y = lbl_1_data_350[i].y;
        lbl_1_bss_6E8->models[no].pos.z = lbl_1_data_350[i].z;
        lbl_1_bss_6E8->models[no].rot.x = 0.0f;
        lbl_1_bss_6E8->models[no].rot.y = 0.0f;
        lbl_1_bss_6E8->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        if(i == 0) {
            Hu3DModelShadowMapSet(id);
        }
    }
}

/* asm 341-364, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 367-452, 82 insns. The two duellists, 200 apart. */
void fn_1_8BE4(void)
{
    int i;

    for(i=0; i<2; i++) {
        (lbl_1_bss_6E8->models+13)[i].modelId = CharModelCreate(lbl_1_bss_6E8->chr[i].charNo, 1);
        Hu3DModelPosSet((lbl_1_bss_6E8->models+13)[i].modelId, (i*200)-100, 100.0f, 0.0f);
        Hu3DModelAttrSet((lbl_1_bss_6E8->models+13)[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet((lbl_1_bss_6E8->models+13)[i].modelId, 1);
        Hu3DModelLayerSet((lbl_1_bss_6E8->models+13)[i].modelId, 0);
    }
}

/*
 * asm 455-3157, 303 + 85 + 132 insns, then the prop table and 21 + 398 +
 * 339 + 569 + 643 + 107 insns of props (DS_S_PROPS_B, shared with m548).
 */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC_B
#define DS_S_PROPS_B
#include "REL/duelstage.h"
