/*
 * m549dll/stage.c -- W1/W2 DRAFT, written outside games/ (m553's workflow).
 *
 * Seventeen of this unit's nineteen functions come from REL/duelstage.h; only
 * the 401-instruction arena creator and the 1-instruction empty are local. The
 * knob values were measured in build/mp5-duelstage/20260915-m549-w0/FINDINGS.md.
 *
 * Two traps this unit sets, both recorded in that notebook:
 *   - the joint-motion table reads m553's data directory, DATA_m553, not
 *     DATA_m549 (0x006F0019/1A; DATADIR(m553) is index 111, m549's is 107);
 *   - the updater table has FIVE entries and leaves the light updater out, so
 *     DS_PROPEXEC_NUM is 5 while the tail is the same nine functions as m553's.
 */
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/frand.h"
#include "game/pad.h"

#include "datadir_enum.h"

#include "REL/m549Dll/m549.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- forward declarations, asm address order --- */

void fn_1_12ED4(void);
void fn_1_1328C(void);
void fn_1_139F4(void);
void fn_1_144D8(void);
void fn_1_1476C(void);

/* --- .data --- */

/* data_528 -- the two joint motions fn_1_11E0C gives models 63 and 65. Retail
 * reads them out of m553's directory, not this overlay's. */
unsigned int lbl_1_data_528[2] = { DATANUM(DATA_m553, 0x19), DATANUM(DATA_m553, 0x1A) };

/* data_530 -- the five prop updaters fn_1_12E80 runs every frame. The light
 * updater (fn_1_134C4) is deliberately absent; nothing references it. */
static void (*lbl_1_data_530[5])(void) = {
    fn_1_12ED4,
    fn_1_1328C,
    fn_1_139F4,
    fn_1_144D8,
    fn_1_1476C
};

/* --- .bss --- */

M549_WORK *lbl_1_bss_1608;

/* --- the duel stage framework (REL/duelstage.h) --- */

#define DS_WORK                 M549_WORK
#define DS_STAGEWORK            lbl_1_bss_1608
#define DS_CHARMDL              68
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       10
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_CHARMOTION_CURZERO
#define DS_EFFECT9STOP_IDX      13
#define DS_PROPTBL              lbl_1_data_530
#define DS_PROPEXEC_NUM         5
#define DS_PROPDMDL             36
#define DS_PROPD_SKYZ           2800.0f
#define DS_PROPD_SKYY           800.0f
#define DS_FN_WorkInit          fn_1_11BC0
#define DS_FN_CharMotDataIdxSet fn_1_12450
#define DS_FN_CharMotIdIdxSet   fn_1_12470
#define DS_FN_PadRead262        fn_1_12494
#define DS_FN_CharMotionCreate  fn_1_128AC
#define DS_FN_MotionExec        fn_1_12A60
#define DS_FN_MatAlphaSet       fn_1_12E18
#define DS_FN_PropExec          fn_1_12E80
#define DS_FN_PropOrbit         fn_1_12ED4
#define DS_FN_PropTurn          fn_1_1328C
#define DS_FN_Effect9Stop       fn_1_134AC
#define DS_FN_PropLight         fn_1_134C4
#define DS_FN_PropBigOrbit      fn_1_139F4
#define DS_FN_PropSkyAStop      fn_1_1448C
#define DS_FN_PropSkyA          fn_1_144D8
#define DS_FN_PropSkyBStop      fn_1_14720
#define DS_FN_PropSkyB          fn_1_1476C

/* ===== decoded functions, asm address order ===== */

/* fn_1_11BC0 */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/*
 * fn_1_11E0C -- the arena. m553's fn_1_DBF0 with three constant shifts: every
 * model number is 0x42 lower, every stageDataTbl index is 3 lower, and four
 * camera/layer values differ (runs 1, 3 and 5 use layer 2 where m553 uses 1,
 * and the first sky prop uses camera 2 where m553 uses 1). The addressing forms
 * are m553's: subscript where it scales after adding, pointer arithmetic where
 * it scales first.
 *
 * The last run sets DISPOFF on models[63 + k*2 + j] BEFORE creating it, so on
 * the first pass through each pair it reads a model id that has not been
 * written yet, as retail does.
 */
void fn_1_11E0C(s16 stageNo)
{
    HU3DMOTID motId[2] = { 0, 0 };
    M549_MODEL *mdl;
    HU3DMODELID linkId;
    int i;
    int j;

    for(i=0; i<3; i++) {
        mdl = &lbl_1_bss_1608->models[(i*3)+36];
        for(j=0; j<3; j++, mdl++) {
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1608->stageDataTbl[i+9], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink(linkId);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 2);
        }
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1608->models[i+45];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1608->stageDataTbl+12+i), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
        Hu3DModelCameraSet(mdl->modelId, 2);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelLayerSet(mdl->modelId, 7);
        mdl = &lbl_1_bss_1608->models[(i*2)+47];
        for(j=0; j<2; j++, mdl++) {
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1608->stageDataTbl+14+i), HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink(linkId);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelLayerSet(mdl->modelId, 3);
        }
    }
    for(i=0; i<2; i++) {
        int mdlNo[2] = { 51, 52 };
        int dataNo[2] = { 16, 17 };

        mdl = &lbl_1_bss_1608->models[mdlNo[i]];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1608->stageDataTbl[dataNo[i]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        if(i < 1) {
            Hu3DModelLayerSet(mdl->modelId, 4);
        } else {
            Hu3DModelLayerSet(mdl->modelId, 2);
        }
    }
    for(i=0; i<10; i++) {
        mdl = &lbl_1_bss_1608->models[i+53];
        if(i == 0) {
            linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1608->stageDataTbl[18], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(linkId);
        }
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        Hu3DModelLayerSet(mdl->modelId, 4);
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1608->models[(i*2)+63];
        for(j=0; j<2; j++, mdl++) {
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1608->stageDataTbl+19+i), HU_MEMNUM_OVL, HEAP_MODEL));
                motId[i] = Hu3DJointMotion(mdl->modelId, HuDataSelHeapReadNum(lbl_1_data_528[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelScaleSet(mdl->modelId, 2.2f, 2.2f, 2.2f);
            } else {
                mdl->modelId = Hu3DModelLink(linkId);
                Hu3DModelScaleSet(mdl->modelId, 1.0f, 1.0f, 1.0f);
            }
            Hu3DMotionSet(mdl->modelId, motId[i]);
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 2);
        }
    }
    mdl = &lbl_1_bss_1608->models[67];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1608->stageDataTbl[21], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(mdl->modelId, 50.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
    Hu3DModelCameraSet(mdl->modelId, 1);
    Hu3DModelLayerSet(mdl->modelId, 4);
}

/* fn_1_12450, fn_1_12470 */
#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

void fn_1_12490(void)
{
}

/* fn_1_12494, fn_1_128AC, fn_1_12A60 */
#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

/* fn_1_12E18, fn_1_12E80, fn_1_12ED4, fn_1_1328C */
#define DS_S_PROPS_D
#define DS_S_PROPEXEC
#include "REL/duelstage.h"

/* fn_1_134AC -- park the arena light (effect slot 13, not 9). */
#define DS_S_EFFECT9STOP
#include "REL/duelstage.h"

/* fn_1_134C4, fn_1_139F4, fn_1_1448C, fn_1_144D8, fn_1_14720, fn_1_1476C */
#define DS_S_PROPS_D2
#include "REL/duelstage.h"
