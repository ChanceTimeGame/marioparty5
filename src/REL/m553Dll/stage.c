/*
 * m553dll/stage.c -- the eight duelstage.h sections m553 takes and this
 * overlay's own arena creator. Functions in reference order; line ranges are
 * into build/mp5-asm/m553Dll/asm/REL/m553Dll/stage.s.
 *
 * Everything except fn_1_DBF0 (the arena) and fn_1_E274 (empty) now comes from
 * REL/duelstage.h: the five framework sections, PropExec (DS_S_PROPEXEC, eight
 * duels), the slot-13 store (DS_S_EFFECT9STOP), and the head-D prop tail this
 * overlay shares with m549 (DS_S_PROPS_D and DS_S_PROPS_D2, which straddle the
 * store because the reference emits it between the second and third updater).
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

#include "REL/m553Dll/m553.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* --- forward declarations, asm address order --- */

void fn_1_ECB8(void);
void fn_1_F070(void);
void fn_1_F2A8(void);
void fn_1_F7D8(void);
void fn_1_102BC(void);
void fn_1_10550(void);

/* --- .data --- */

/* data_3B8 -- the two joint motions fn_1_DBF0 gives models 129 and 131. */
unsigned int lbl_1_data_3B8[2] = { DATANUM(DATA_m553, 0x19), DATANUM(DATA_m553, 0x1A) };

/* data_3C0 -- the six prop updaters fn_1_EC64 runs every frame. */
static void (*lbl_1_data_3C0[6])(void) = {
    fn_1_ECB8,
    fn_1_F070,
    fn_1_F2A8,
    fn_1_F7D8,
    fn_1_102BC,
    fn_1_10550
};

/* --- .bss --- */

M553_WORK *lbl_1_bss_1F00;

/* --- the duel stage framework (REL/duelstage.h) --- */

#define DS_WORK                 M553_WORK
#define DS_STAGEWORK            lbl_1_bss_1F00
#define DS_CHARMDL              134
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       5
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_CHARMOTION_CURZERO
#define DS_EFFECT9STOP_IDX      13
#define DS_PROPTBL              lbl_1_data_3C0
#define DS_PROPEXEC_NUM         6
#define DS_PROPDMDL             102
#define DS_PROPD_SKYZ           2500.0f
#define DS_PROPD_SKYY           300.0f
#define DS_FN_WorkInit          fn_1_D9A4
#define DS_FN_CharMotDataIdxSet fn_1_E234
#define DS_FN_CharMotIdIdxSet   fn_1_E254
#define DS_FN_PadRead262        fn_1_E278
#define DS_FN_CharMotionCreate  fn_1_E690
#define DS_FN_MotionExec        fn_1_E844
#define DS_FN_MatAlphaSet       fn_1_EBFC
#define DS_FN_PropExec          fn_1_EC64
#define DS_FN_PropOrbit         fn_1_ECB8
#define DS_FN_PropTurn          fn_1_F070
#define DS_FN_Effect9Stop       fn_1_F290
#define DS_FN_PropLight         fn_1_F2A8
#define DS_FN_PropBigOrbit      fn_1_F7D8
#define DS_FN_PropSkyAStop      fn_1_10270
#define DS_FN_PropSkyA          fn_1_102BC
#define DS_FN_PropSkyBStop      fn_1_10504
#define DS_FN_PropSkyB          fn_1_10550

/* ===== decoded functions, asm address order ===== */

/* fn_1_D9A4 */
#define DS_S_WORKINIT
#include "REL/duelstage.h"

/*
 * fn_1_DBF0 -- the arena. Six runs of models off StageWork->stageDataTbl, most
 * created once and linked for the repeats, all parked with DISPOFF for the prop
 * updaters to bring in: 102-110 the nine orbiters, 111-112 the two sky props,
 * 113-116 the four turning ones, 117 the light, 118 the big orbiter, 119-128
 * its ten trailing models, 129-132 the jointed pair, and 133.
 *
 * The last run sets DISPOFF on models[129 + k*2 + j] BEFORE creating it, so on
 * the first pass through each pair it reads a model id that has not been
 * written yet, as retail does.
 */
void fn_1_DBF0(s16 stageNo)
{
    HU3DMOTID motId[2] = { 0, 0 };
    M553_MODEL *mdl;
    HU3DMODELID linkId;
    int i;
    int j;

    for(i=0; i<3; i++) {
        mdl = &lbl_1_bss_1F00->models[(i*3)+102];
        for(j=0; j<3; j++, mdl++) {
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1F00->stageDataTbl[i+12], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink(linkId);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1F00->models[i+111];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1F00->stageDataTbl+15+i), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
        Hu3DModelCameraSet(mdl->modelId, 1);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelLayerSet(mdl->modelId, 7);
        mdl = &lbl_1_bss_1F00->models[(i*2)+113];
        for(j=0; j<2; j++, mdl++) {
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1F00->stageDataTbl+17+i), HU_MEMNUM_OVL, HEAP_MODEL));
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
        int mdlNo[2] = { 117, 118 };
        int dataNo[2] = { 19, 20 };

        mdl = &lbl_1_bss_1F00->models[mdlNo[i]];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1F00->stageDataTbl[dataNo[i]], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        if(i < 1) {
            Hu3DModelLayerSet(mdl->modelId, 4);
        } else {
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
    for(i=0; i<10; i++) {
        mdl = &lbl_1_bss_1F00->models[i+119];
        if(i == 0) {
            linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1F00->stageDataTbl[21], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(linkId);
        }
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, 1);
        Hu3DModelLayerSet(mdl->modelId, 4);
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1F00->models[(i*2)+129];
        for(j=0; j<2; j++, mdl++) {
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            if(j == 0) {
                linkId = mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(*(lbl_1_bss_1F00->stageDataTbl+22+i), HU_MEMNUM_OVL, HEAP_MODEL));
                motId[i] = Hu3DJointMotion(mdl->modelId, HuDataSelHeapReadNum(lbl_1_data_3B8[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelScaleSet(mdl->modelId, 2.2f, 2.2f, 2.2f);
            } else {
                mdl->modelId = Hu3DModelLink(linkId);
                Hu3DModelScaleSet(mdl->modelId, 1.0f, 1.0f, 1.0f);
            }
            Hu3DMotionSet(mdl->modelId, motId[i]);
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            Hu3DModelCameraSet(mdl->modelId, 1);
            Hu3DModelLayerSet(mdl->modelId, 1);
        }
    }
    mdl = &lbl_1_bss_1F00->models[133];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_bss_1F00->stageDataTbl[24], HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(mdl->modelId, 50.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
    Hu3DModelCameraSet(mdl->modelId, 1);
    Hu3DModelLayerSet(mdl->modelId, 4);
}

/* fn_1_E234, fn_1_E254 */
#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

void fn_1_E274(void)
{
}

/* fn_1_E278, fn_1_E690, fn_1_E844 */
#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

/* fn_1_EBFC, fn_1_EC64, fn_1_ECB8, fn_1_F070 */
#define DS_S_PROPS_D
#define DS_S_PROPEXEC
#include "REL/duelstage.h"

/* fn_1_F290 -- park the arena light (effect slot 13, not 9). */
#define DS_S_EFFECT9STOP
#include "REL/duelstage.h"

/* fn_1_F2A8, fn_1_F7D8, fn_1_10270, fn_1_102BC, fn_1_10504, fn_1_10550 */
#define DS_S_PROPS_D2
#include "REL/duelstage.h"
