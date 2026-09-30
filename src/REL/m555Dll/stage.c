/*
 * m555dll/stage.c -- the duel stage framework (REL/duelstage.h), work head D, and
 * this overlay's own stage functions. Written from the reference assembly,
 * functions in reference order; line ranges are into
 * build/mp5-asm/m555Dll/asm/REL/m555Dll/stage.s.
 *
 * From the header: fn_1_1A9A4 (DS_S_WORKINIT), fn_1_1AC04/1AC24
 * (DS_S_CHARMOT_IDX) and fn_1_1B4B0 (DS_S_MOTIONEXEC: DS_SHIFT_POLL,
 * DS_MOTIONEXEC_NOHANDOVER, two slots on models 169-170) -- raw-identical to
 * m541's with symbols masked but for the model base. Own: the duellist model
 * setup fn_1_1AC44, the PadRead-240 fn_1_1AF38 (PadRead-262 without the
 * computer-duellist clear), and the CharMotionCreate-110 fn_1_1B2F8 (two
 * motions, motNoCur -1, speed 1, looping).
 */
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"

#include "REL/m555Dll/m555.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

M555_WORK *lbl_1_bss_3038;

#define DS_WORK                 M555_WORK
#define DS_STAGEWORK            lbl_1_bss_3038
#define DS_CHARMDL              169
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_FN_WorkInit          fn_1_1A9A4
#define DS_FN_CharMotDataIdxSet fn_1_1AC04
#define DS_FN_CharMotIdIdxSet   fn_1_1AC24
#define DS_FN_MotionExec        fn_1_1B4B0

#define DS_S_WORKINIT
#include "REL/duelstage.h"

/* asm 168-174. */
void fn_1_1ABF0(s16 stageNo)
{
    lbl_1_bss_3038->stageNo = stageNo;
}

#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

/* asm 201-393, 189 insns. The two duellists, 300 apart, and their idle motion. */
void fn_1_1AC44(void)
{
    int i;
    DS_PLAYER *pl;

    for(i=0; i<2; i++) {
        (lbl_1_bss_3038->models+DS_CHARMDL)[i].modelId = CharModelCreate(lbl_1_bss_3038->chr[i].charNo, 2);
        Hu3DModelPosSet((lbl_1_bss_3038->models+DS_CHARMDL)[i].modelId, -150.0f+(300.0f*i), 100.0f, 0.0f);
        CharEffectLayerSet(0);
        CharModelFxFlagSet(lbl_1_bss_3038->chr[i].charNo, 0);
        pl = &lbl_1_bss_3038->player[i];
        pl->motNo = 0;
        pl->speed = 1.0f;
        pl->attr = HU3D_MOTATTR_LOOP;
        pl->attrReset = 0;
        pl->time = 0.0f;
    }
    lbl_1_bss_3038->models[DS_CHARMDL].pos.x = -200.0f;
    lbl_1_bss_3038->models[DS_CHARMDL].pos.y = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL].pos.z = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL].rot.x = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL].rot.y = 180.0f;
    lbl_1_bss_3038->models[DS_CHARMDL].rot.z = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].pos.x = 200.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].pos.y = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].pos.z = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].rot.x = 0.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].rot.y = 180.0f;
    lbl_1_bss_3038->models[DS_CHARMDL+1].rot.z = 0.0f;
}

/* asm 396-643, 240 insns. PadRead-262 without the computer-duellist clear. */
void fn_1_1AF38(OMOBJ *obj)
{
    int i;

    for(i=0; i<2; i++) {
        lbl_1_bss_3038->chr[i].btn = HuPadBtn[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].btnDown = HuPadBtnDown[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].btnRep = HuPadBtnRep[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].stkX = (s8)HuPadStkX[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].stkX = (((lbl_1_bss_3038->chr[i].stkX >= 0) ? lbl_1_bss_3038->chr[i].stkX : -lbl_1_bss_3038->chr[i].stkX) < 10) ? 0 : lbl_1_bss_3038->chr[i].stkX;
        lbl_1_bss_3038->chr[i].stkY = (s8)HuPadStkY[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].subStkX = (s8)HuPadSubStkX[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].subStkY = (s8)HuPadSubStkY[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].trigL = HuPadTrigL[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].trigR = HuPadTrigR[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].dStk = HuPadDStk[lbl_1_bss_3038->chr[i].padNo];
        lbl_1_bss_3038->chr[i].dStkRep = HuPadDStkRep[lbl_1_bss_3038->chr[i].padNo];
    }
}

/* asm 646-763, 110 insns. Two motions each, and the state they start in. */
void fn_1_1B2F8(void)
{
    s16 i;
    s16 j;

    for(i=0; i<2; i++) {
        for(j=0; j<2; j++) {
            lbl_1_bss_3038->motId[i][j] = CharMotionCreate(lbl_1_bss_3038->chr[i].charNo, lbl_1_bss_3038->charMotData[i][j]);
        }
    }
    for(i=0; i<2; i++) {
        lbl_1_bss_3038->player[i].motNo = 0;
        lbl_1_bss_3038->player[i].motNoCur = -1;
        lbl_1_bss_3038->player[i].speed = 1.0f;
        lbl_1_bss_3038->player[i].speedCur = 0.0f;
        lbl_1_bss_3038->player[i].attr = HU3D_MOTATTR_LOOP;
        lbl_1_bss_3038->player[i].attrCur = 0;
    }
}

#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

void fn_1_1B868(void)
{
}

void fn_1_1B86C(void)
{
}

void fn_1_1B870(void)
{
}

void fn_1_1B874(void)
{
}

void fn_1_1B878(void)
{
}

void fn_1_1B87C(void)
{
}

void fn_1_1B880(void)
{
}
