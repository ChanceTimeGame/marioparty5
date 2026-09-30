/*
 * m546dll/stage.c -- the arena, the duellists' models and motions, and the
 * five stage props. Written from the reference assembly, functions in
 * reference order; line ranges are into
 * build/mp5-asm/m546Dll/asm/REL/m546Dll/stage.s.
 *
 * Against REL/duelstage.h (docs/MP5_MINIGAME_PLAN.md Phase 2 table), work
 * head C: fn_1_B15C (DS_S_WORKINIT), fn_1_B654/B678 (DS_S_CHARMOT), fn_1_B9B4
 * (DS_S_PADREAD_262), fn_1_BDCC (DS_S_CHARMOTION, 9 motions, speedCur -1.0f,
 * DS_CHARMOTION_NOSPEED), fn_1_BEF8 (DS_S_MOTIONEXEC_C) and fn_1_C250..D6F8
 * with the table lbl_1_data_578 (DS_S_PROPS_B on models 16-23 with
 * DS_PROPSWING_GO and DS_PROPROLL_PASSED) come from the header and sit in the
 * object's second .text section. The arena, the duellists and PropSlide (175,
 * m544's with a lane of its own) are this overlay's own. See NOTES.md for the
 * per-function result.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/frand.h"

#include "REL/m546Dll/m546.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- .data --- */

HuVecF lbl_1_data_4E8[12] = {
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

M546_WORK *lbl_1_bss_15298;         /* set by fn_1_B15C */

/* --- the duel stage framework (REL/duelstage.h), work head C --- */

#define DS_WORK                 M546_WORK
#define DS_STAGEWORK            lbl_1_bss_15298
#define DS_CHARMOTION_NUM       9
#define DS_CHARMOTION_SPEEDCUR  -1.0f
#define DS_CHARMOTION_NOSPEED
#define DS_CHARMDL              27
#define DS_PROPTBL              lbl_1_data_578
#define DS_PROPEXEC_NUM         5
#define DS_PROPMDL              15
#define DS_PROPSWING_GO
#define DS_PROPROLL_PASSED      lbl_1_bss_15290
#define DS_PROPSLIDE_OWN
#define DS_FN_WorkInit          fn_1_B15C
#define DS_FN_CharMotDataSet    fn_1_B654
#define DS_FN_CharMotIdSet      fn_1_B678
#define DS_FN_PadRead262        fn_1_B9B4
#define DS_FN_CharMotionCreate  fn_1_BDCC
#define DS_FN_MotionExecC       fn_1_BEF8
#define DS_FN_PropExec          fn_1_C250
#define DS_FN_PropSwingGo       fn_1_C2A4
#define DS_FN_PropSwing         fn_1_C2BC
#define DS_FN_PropSway          fn_1_C8C8
#define DS_FN_PropPendulum      fn_1_CE14
#define DS_FN_PropRoll          fn_1_D6F8
#define DS_FN_PropSlide         fn_1_E14C

/* asm 9-165, 147 insns. */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-343, 171 insns. The arena: twelve models from stageDataTbl[9..20] at 15-26, placed from lbl_1_data_4E8. */
void fn_1_B3A8(s16 stageNo)
{
    s16 i;
    HU3DMODELID id;
    s16 no;

    lbl_1_bss_15298->stageNo = stageNo;
    for(i=0; i<12; i++) {
        no = i+15;
        id = lbl_1_bss_15298->models[no].modelId = Hu3DModelCreate(HuDataSelHeapReadNum((lbl_1_bss_15298->stageDataTbl+9)[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(id, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(id, 1);
        Hu3DModelLayerSet(id, 0);
        Hu3DModelPosSetV(id, &lbl_1_data_4E8[i]);
        Hu3DModelRotSet(id, 0.0f, 0.0f, 0.0f);
        Hu3DMotionSpeedSet(id, 0.0f);
        Hu3DMotionTimeSet(id, 0.0f);
        Hu3DModelAttrSet(id, HU3D_MOTATTR_LOOP);
        lbl_1_bss_15298->models[no].pos.x = lbl_1_data_4E8[i].x;
        lbl_1_bss_15298->models[no].pos.y = lbl_1_data_4E8[i].y;
        lbl_1_bss_15298->models[no].pos.z = lbl_1_data_4E8[i].z;
        lbl_1_bss_15298->models[no].rot.x = 0.0f;
        lbl_1_bss_15298->models[no].rot.y = 0.0f;
        lbl_1_bss_15298->models[no].rot.z = 0.0f;
        Hu3DModelAttrReset(id, HU3D_ATTR_DISPOFF);
        if(i == 0) {
            Hu3DModelShadowMapSet(id);
        }
    }
}

/* asm 346-369, 9 + 9 insns. */
#define DS_S_CHARMOT
#include "REL/duelstage.h"

/* asm 372-573, 198 insns. The two duellists, 300 apart, and their idle motion. */
void fn_1_B69C(void)
{
    int i;
    M546_PLAYER *pl;

    for(i=0; i<2; i++) {
        (lbl_1_bss_15298->models+27)[i].modelId = CharModelCreate(lbl_1_bss_15298->chr[i].charNo, 1);
        Hu3DModelPosSet((lbl_1_bss_15298->models+27)[i].modelId, -150.0f+(300.0f*i), 100.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_15298->models[i+27].modelId, 2);
        Hu3DModelShadowSet((lbl_1_bss_15298->models+27)[i].modelId);
        CharModelFxFlagSet(lbl_1_bss_15298->chr[i].charNo, 1);
        CharEffectLayerSet(3);
        CharModelStepFxSet(lbl_1_bss_15298->chr[i].charNo, 1);
        lbl_1_bss_15298->models[i+27].pos.x = -150.0f+(300.0f*i);
        lbl_1_bss_15298->models[i+27].pos.y = 100.0f;
        lbl_1_bss_15298->models[i+27].pos.z = -200.0f;
        lbl_1_bss_15298->models[i+27].rot.x = 0.0f;
        lbl_1_bss_15298->models[i+27].rot.y = 0.0f;
        lbl_1_bss_15298->models[i+27].rot.z = 0.0f;
        pl = &lbl_1_bss_15298->player[i];
        pl->motNo = 0;
        pl->speed = 1.0f;
        pl->attr = HU3D_MOTATTR_LOOP;
        pl->attrReset = 0;
        pl->time = 0.0f;
    }
}

/*
 * asm 576-3213, 262 + 75 + 214 insns, then the prop table and 21 + 6 + 387 +
 * 339 + 569 + 661 insns of props.
 */
#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC_C
#define DS_S_PROPS_B
#include "REL/duelstage.h"

/*
 * asm 3216-3402, 175 insns. PropSlide (effect[4], model 22) as m544 has it:
 * a sound pans across with it until the pre-winner step (game.c) moves
 * slideSeMode on. Its first pass runs in front at z=950 and on layer 6, later
 * passes behind at z=-2100 on layer 0.
 */
void fn_1_E14C(void)
{
    DS_MODEL *mdl;
    s16 pan;

    mdl = &lbl_1_bss_15298->models[DS_PROPMDL+7];
    switch(lbl_1_bss_15298->effect[4].mode) {
        case 0:
            if(lbl_1_bss_15298->effect[0].mode == 2) {
                lbl_1_bss_15298->effect[4].mode++;
                lbl_1_bss_15298->effect[4].timer = 0;
                Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                if(lbl_1_bss_15294) {
                    mdl->pos.z = -2100.0f;
                    Hu3DModelLayerSet(mdl->modelId, 0);
                } else {
                    mdl->pos.z = 950.0f;
                    lbl_1_bss_15294 = 1;
                    Hu3DModelLayerSet(mdl->modelId, 6);
                }
                switch(lbl_1_bss_14C40.slideSeMode) {
                    case 0:
                        fn_1_56EC(6, 127, 36);
                        break;

                    case 1:
                        fn_1_5804(6);
                        lbl_1_bss_14C40.slideSeMode++;
                        break;
                }
            }
            break;

        case 1:
            lbl_1_bss_15298->effect[4].timer++;
            if(lbl_1_bss_14C40.slideSeMode != 1) {
                pan = ((lbl_1_bss_15298->effect[4].timer*64)/200)+32;
                fn_1_5774(6, pan);
            }
            mdl->pos.x = ((lbl_1_bss_15298->effect[4].timer*4000)/200)-2000;
            if(lbl_1_bss_15298->effect[4].timer == 200) {
                lbl_1_bss_15298->effect[4].mode++;
            }
            break;

        case 2:
            if(lbl_1_bss_15298->effect[0].mode == 1) {
                lbl_1_bss_15298->effect[4].mode = 0;
            }
            break;
    }
}
