/*
 * m542dll/stage.c -- the arena, the duellists' models and motions. Written
 * from the reference assembly, functions in reference order; line ranges are
 * into build/mp5-asm/m542dll/asm/REL/m542dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head B: fn_1_84D0 (DS_S_WORKINIT), fn_1_89DC/8A00 (DS_S_CHARMOT),
 * fn_1_8C94 (DS_S_PADREAD), fn_1_9150 (DS_S_CHARMOTION, 9 motions, speedCur
 * 1.0f) and fn_1_92A4 (DS_S_MOTIONEXEC_B) come from the header and sit in the
 * object's second .text section. See NOTES.md for the per-function result.
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

#include "REL/m542dll/m542.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"



/* --- .bss --- */

M542_WORK *lbl_1_bss_1B38;          /* set by fn_1_84D0 */

/* --- the duel stage framework (REL/duelstage.h), work head B --- */

#define DS_WORK                 M542_WORK
#define DS_STAGEWORK            lbl_1_bss_1B38
#define DS_CHARMDL              32
#define DS_CHARMOTION_NUM       9
#define DS_CHARMOTION_SPEEDCUR  1.0f
#define DS_FN_WorkInit          fn_1_84D0
#define DS_FN_CharMotDataSet    fn_1_89DC
#define DS_FN_CharMotIdSet      fn_1_8A00
#define DS_FN_PadRead           fn_1_8C94
#define DS_FN_CharMotionCreate  fn_1_9150
#define DS_FN_MotionExecB       fn_1_92A4

/* asm 9-165, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-350, 176 insns. The arena: six models, placed from lbl_1_data_3B0; model 4 runs at half speed. */
void fn_1_871C(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_1B38->stageNo = stageNo;
    for(i=0; i<6; i++) {
        no = (s16)i;
        id = lbl_1_bss_1B38->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1B38->stageDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelPosSetV(id, &lbl_1_data_3B0[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        if(i != 0) {
            if(i == 4) {
                Hu3DMotionSpeedSet(id, 0.5f);
            } else {
                Hu3DMotionSpeedSet(id, 1.0f);
            }
            Hu3DMotionTimeSet(id, 0.0f);
            Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        }
        lbl_1_bss_1B38->models[no].pos.x = lbl_1_data_3B0[i].x;
        lbl_1_bss_1B38->models[no].pos.y = lbl_1_data_3B0[i].y;
        lbl_1_bss_1B38->models[no].pos.z = lbl_1_data_3B0[i].z;
        lbl_1_bss_1B38->models[no].rot.x = 0.0f;
        lbl_1_bss_1B38->models[no].rot.y = 0.0f;
        lbl_1_bss_1B38->models[no].rot.z = 0.0f;
        Hu3DModelLayerSet(id, 0);
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
    }
}

/* asm 353-376, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 379-538, 156 insns. The two duellists on their boards, 420 apart. */
void fn_1_8A24(void)
{
    int i;

    for(i=0; i<2; i++) {
        (lbl_1_bss_1B38->models+32)[i].modelId = CharModelCreate(lbl_1_bss_1B38->chr[i].charNo, 2);
        Hu3DModelPosSet((lbl_1_bss_1B38->models+32)[i].modelId, (i*420)-210, 170.0f, 254.0f);
        lbl_1_bss_1B38->models[i+32].pos.x = (i*420)-210;
        lbl_1_bss_1B38->models[i+32].pos.y = 170.0f;
        lbl_1_bss_1B38->models[i+32].pos.z = 254.0f;
        lbl_1_bss_1B38->models[i+32].rot.x = 0.0f;
        lbl_1_bss_1B38->models[i+32].rot.y = 0.0f;
        lbl_1_bss_1B38->models[i+32].rot.z = 0.0f;
        Hu3DModelAttrSet((lbl_1_bss_1B38->models+32)[i].modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet((lbl_1_bss_1B38->models+32)[i].modelId, 1);
        Hu3DModelLayerSet((lbl_1_bss_1B38->models+32)[i].modelId, 0);
    }
}

/* asm 541-1095, 303 + 85 + 132 insns. */
#define DS_S_PADREAD
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC_B
#include "REL/duelstage.h"

/* asm 1098-1100, 1 insns. Object main; empty. */
void fn_1_94B4(OMOBJ *obj)
{
}
