/*
 * m544dll/stage.c -- the arena, the duellists and the stage actor, their
 * motions, and the stage props. Written from the reference assembly, functions
 * in reference order; line ranges are into
 * build/mp5-asm/m544Dll/asm/REL/m544Dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head D: fn_1_9EF8 (DS_S_WORKINIT), fn_1_A3F0/A410 (DS_S_CHARMOT_IDX, the
 * head-D indexed setters, m543's too), fn_1_A9A4 (DS_S_PADREAD_262), fn_1_AF60
 * (DS_S_MOTIONEXEC: DS_SHIFT_POLL, DS_MOTIONEXEC_NOHANDOVER, three slots on
 * models 32-34), and fn_1_B318..C7C0 with the table lbl_1_data_4A8
 * (DS_S_PROPS_B on models 21-28 with DS_PROPSWING_GO, m546's too) come from
 * the header and sit in the object's second .text section. The motion loader
 * (105, with the actor's motions) and PropSlide (151) are this overlay's own.
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

#include "REL/m544Dll/m544.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_418[12] = {
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

M544_WORK *lbl_1_bss_918;           /* set by fn_1_9EF8 */

/* --- the duel stage framework (REL/duelstage.h), work head D --- */

#define DS_WORK                 M544_WORK
#define DS_STAGEWORK            lbl_1_bss_918
#define DS_CHARMDL              32
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       3
#define DS_PROPTBL              lbl_1_data_4A8
#define DS_PROPEXEC_NUM         5
#define DS_PROPMDL              20
#define DS_PROPSWING_GO
#define DS_PROPSLIDE_OWN
#define DS_FN_WorkInit          fn_1_9EF8
#define DS_FN_CharMotDataIdxSet fn_1_A3F0
#define DS_FN_CharMotIdIdxSet   fn_1_A410
#define DS_FN_PadRead262        fn_1_A9A4
#define DS_FN_MotionExec        fn_1_AF60
#define DS_FN_PropExec          fn_1_B318
#define DS_FN_PropSwingGo       fn_1_B36C
#define DS_FN_PropSwing         fn_1_B384
#define DS_FN_PropSway          fn_1_B990
#define DS_FN_PropPendulum      fn_1_BEDC
#define DS_FN_PropRoll          fn_1_C7C0
#define DS_FN_PropSlide         fn_1_D1CC

/* asm 9-165, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-343, 171 insns. The arena: twelve models from stageDataTbl[13..24] at 20-31, placed from lbl_1_data_418. */
void fn_1_A144(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_918->stageNo = stageNo;
    for(i=0; i<12; i++) {
        no = i+20;
        id = lbl_1_bss_918->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum((lbl_1_bss_918->stageDataTbl+13)[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelLayerSet(id, 0);
        Hu3DModelPosSetV(id, &lbl_1_data_418[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_918->models[no].pos.x = lbl_1_data_418[i].x;
        lbl_1_bss_918->models[no].pos.y = lbl_1_data_418[i].y;
        lbl_1_bss_918->models[no].pos.z = lbl_1_data_418[i].z;
        lbl_1_bss_918->models[no].rot.x = 0.0f;
        lbl_1_bss_918->models[no].rot.y = 0.0f;
        lbl_1_bss_918->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        if(i == 0) {
            Hu3DModelShadowMapSet(id);
        }
    }
}

/* asm 346-367, 8 + 8 insns. */
#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

/*
 * asm 370-722, 349 insns. The two duellists, 300 apart, and the stage actor
 * behind them; then all three placed. Retail sets the layer of models[i], not
 * the duellist's model.
 */
void fn_1_A430(void)
{
    int i;
    DS_PLAYER *pl;

    for(i=0; i<2; i++) {
        (lbl_1_bss_918->models+32)[i].modelId = CharModelCreate(lbl_1_bss_918->chr[i].charNo, 1);
        Hu3DModelPosSet((lbl_1_bss_918->models+32)[i].modelId, -150.0f+(300.0f*i), 100.0f, 0.0f);
        CharModelFxFlagSet(lbl_1_bss_918->chr[i].charNo, 1);
        Hu3DModelLayerSet(lbl_1_bss_918->models[i].modelId, 0);
        Hu3DModelShadowSet((lbl_1_bss_918->models+32)[i].modelId);
        CharModelStepFxSet(lbl_1_bss_918->chr[i].charNo, 1);
        CharModelFxFlagSet(lbl_1_bss_918->chr[i].charNo, 0);
        pl = &lbl_1_bss_918->player[i];
        pl->motNo = 4;
        pl->speed = 1.0f;
        pl->attr = HU3D_MOTATTR_LOOP;
        pl->attrReset = 0;
        pl->time = 0.0f;
    }
    lbl_1_bss_918->models[34].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_918->stageDataTbl[25], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_918->models[34].modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_918->models[34].modelId, 1);
    Hu3DModelLayerSet(lbl_1_bss_918->models[34].modelId, 2);
    Hu3DModelShadowSet(lbl_1_bss_918->models[34].modelId);
    Hu3DModelAmbSet(lbl_1_bss_918->models[34].modelId, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(lbl_1_bss_918->models[34].modelId, HU3D_ATTR_DISPOFF);
    pl = &lbl_1_bss_918->player[2];
    pl->motNo = 0;
    pl->speed = 1.0f;
    pl->attr = HU3D_MOTATTR_LOOP;
    pl->attrReset = 0;
    pl->time = 0.0f;
    lbl_1_bss_918->models[32].pos.x = -300.0f;
    lbl_1_bss_918->models[32].pos.y = 100.0f;
    lbl_1_bss_918->models[32].pos.z = -240.0f;
    lbl_1_bss_918->models[32].rot.x = 0.0f;
    lbl_1_bss_918->models[32].rot.y = 90.0f;
    lbl_1_bss_918->models[32].rot.z = 0.0f;
    lbl_1_bss_918->models[33].pos.x = 300.0f;
    lbl_1_bss_918->models[33].pos.y = 100.0f;
    lbl_1_bss_918->models[33].pos.z = -240.0f;
    lbl_1_bss_918->models[33].rot.x = 0.0f;
    lbl_1_bss_918->models[33].rot.y = -90.0f;
    lbl_1_bss_918->models[33].rot.z = 0.0f;
    lbl_1_bss_918->models[34].pos.x = -0.0f;
    lbl_1_bss_918->models[34].pos.y = 100.0f;
    lbl_1_bss_918->models[34].pos.z = -400.0f;
    lbl_1_bss_918->models[34].rot.x = 0.0f;
    lbl_1_bss_918->models[34].rot.y = 0.0f;
    lbl_1_bss_918->models[34].rot.z = 0.0f;
}

/* asm 725-996, 262 insns. */
#define DS_S_PADREAD_262
#include "REL/duelstage.h"

/*
 * asm 999-1113, 105 insns. Seven motions per duellist, the actor's four joint
 * motions, and all three slots' applied motion and speed unset.
 */
void fn_1_ADBC(void)
{
    s16 i;
    s16 j;

    for(i=0; i<2; i++) {
        for(j=0; j<7; j++) {
            lbl_1_bss_918->motId[i][j] = CharMotionCreate(lbl_1_bss_918->chr[i].charNo, lbl_1_bss_918->charMotData[i][j]);
        }
    }
    for(i=0; i<4; i++) {
        lbl_1_bss_918->motId[2][i] = Hu3DJointMotion(lbl_1_bss_918->models[34].modelId, HuDataSelHeapReadNum(lbl_1_bss_918->charMotData[2][i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    for(i=0; i<3; i++) {
        lbl_1_bss_918->player[i].motNoCur = -1;
        lbl_1_bss_918->player[i].speedCur = -1.0f;
    }
}

/* asm 1116-3399, 238 + 21 + 6 + 387 + 339 + 569 + 643 insns. */
#define DS_S_MOTIONEXEC
#define DS_S_PROPS_B
#include "REL/duelstage.h"

/*
 * asm 3402-3562, 151 insns. PropSlide (effect[4], model 27) as DS_S_PROPS_B
 * has it, with a sound that pans across with it until the pre-winner step
 * (game.c) moves slideSeMode on.
 */
void fn_1_D1CC(void)
{
    DS_MODEL *mdl;
    s16 pan;

    mdl = &lbl_1_bss_918->models[DS_PROPMDL+7];
    switch(lbl_1_bss_918->effect[4].mode) {
        case 0:
            if(lbl_1_bss_918->effect[0].mode == 2) {
                lbl_1_bss_918->effect[4].mode++;
                lbl_1_bss_918->effect[4].timer = 0;
                Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                switch(lbl_1_bss_D0.slideSeMode) {
                    case 0:
                        fn_1_4098(0, 127, 36);
                        break;

                    case 1:
                        fn_1_425C(0);
                        lbl_1_bss_D0.slideSeMode++;
                        break;
                }
            }
            break;

        case 1:
            lbl_1_bss_918->effect[4].timer++;
            if(lbl_1_bss_D0.slideSeMode != 1) {
                pan = ((lbl_1_bss_918->effect[4].timer*64)/200)+32;
                fn_1_4120(0, pan);
            }
            mdl->pos.x = ((lbl_1_bss_918->effect[4].timer*4000)/200)-2000;
            if(lbl_1_bss_918->effect[4].timer == 200) {
                lbl_1_bss_918->effect[4].mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_918->effect[0].mode == 1) {
                lbl_1_bss_918->effect[4].mode = 0;
            }
            break;
    }
}
