/*
 * m541dll/stage.c -- the duel stage framework (REL/duelstage.h), work head D, and
 * this overlay's few own stage functions: the stage number store and eight empty
 * functions. Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m541Dll/asm/REL/m541Dll/stage.s.
 *
 * Every function but fn_1_19CFC and the empty ones comes from the header and sits
 * in the object's second .text section: fn_1_19AB0 (DS_S_WORKINIT), fn_1_19D10/16C74
 * (DS_S_CHARMOT_IDX), fn_1_19D54 (DS_S_PADREAD_262), fn_1_1A16C (DS_S_CHARMOTION:
 * 8 motions, DS_CHARMOTION_CLEAR and DS_CHARMOTION_CURZERO) and fn_1_1A320
 * (DS_S_MOTIONEXEC: DS_SHIFT_POLL, DS_MOTIONEXEC_NOHANDOVER, two slots on
 * models 106-107). m543 and m551 have the same stage.c with other constants.
 */
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"

#include "REL/m541Dll/m541.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

M541_WORK *lbl_1_bss_3738;

#define DS_WORK                 M541_WORK
#define DS_STAGEWORK            lbl_1_bss_3738
#define DS_CHARMDL              106
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       8
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_CHARMOTION_CURZERO
#define DS_FN_WorkInit          fn_1_19AB0
#define DS_FN_CharMotDataIdxSet fn_1_19D10
#define DS_FN_CharMotIdIdxSet   fn_1_19D30
#define DS_FN_PadRead262        fn_1_19D54
#define DS_FN_CharMotionCreate  fn_1_1A16C
#define DS_FN_MotionExec        fn_1_1A320

#define DS_S_WORKINIT
#include "REL/duelstage.h"

void fn_1_19CFC(s16 stageNo)
{
    lbl_1_bss_3738->stageNo = stageNo;
}

#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

void fn_1_19D50(void)
{
}

#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

void fn_1_1A6D8(void)
{
}

void fn_1_1A6DC(void)
{
}

void fn_1_1A6E0(void)
{
}

void fn_1_1A6E4(void)
{
}

void fn_1_1A6E8(void)
{
}

void fn_1_1A6EC(void)
{
}

void fn_1_1A6F0(void)
{
}
