/*
 * m543dll/stage.c -- the duel stage framework (REL/duelstage.h), work head D, and
 * this overlay's few own stage functions: the stage number store and eight empty
 * functions. Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m543Dll/asm/REL/m543Dll/stage.s.
 *
 * Every function but fn_1_FCE0 and the empty ones comes from the header and sits
 * in the object's second .text section: fn_1_FA94 (DS_S_WORKINIT), fn_1_FCF4/FD14
 * (DS_S_CHARMOT_IDX), fn_1_FD38 (DS_S_PADREAD_262), fn_1_10150 (DS_S_CHARMOTION:
 * 7 motions, DS_CHARMOTION_CLEAR and DS_CHARMOTION_CURZERO) and fn_1_10304
 * (DS_S_MOTIONEXEC: DS_SHIFT_POLL, DS_MOTIONEXEC_NOHANDOVER, two slots on
 * models 60-61). m541 and m551 have the same stage.c with other constants.
 */
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"

#include "REL/m543Dll/m543.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

M543_WORK *lbl_1_bss_15E8;

#define DS_WORK                 M543_WORK
#define DS_STAGEWORK            lbl_1_bss_15E8
#define DS_CHARMDL              60
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       7
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_CHARMOTION_CURZERO
#define DS_FN_WorkInit          fn_1_FA94
#define DS_FN_CharMotDataIdxSet fn_1_FCF4
#define DS_FN_CharMotIdIdxSet   fn_1_FD14
#define DS_FN_PadRead262        fn_1_FD38
#define DS_FN_CharMotionCreate  fn_1_10150
#define DS_FN_MotionExec        fn_1_10304

#define DS_S_WORKINIT
#include "REL/duelstage.h"

void fn_1_FCE0(s16 stageNo)
{
    lbl_1_bss_15E8->stageNo = stageNo;
}

#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

void fn_1_FD34(void)
{
}

#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

void fn_1_106BC(void)
{
}

void fn_1_106C0(void)
{
}

void fn_1_106C4(void)
{
}

void fn_1_106C8(void)
{
}

void fn_1_106CC(void)
{
}

void fn_1_106D0(void)
{
}

void fn_1_106D4(void)
{
}
