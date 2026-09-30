/*
 * m551dll/stage.c -- the duel stage framework (REL/duelstage.h), work head D, and
 * this overlay's few own stage functions: the stage number store and eight empty
 * functions. Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m551Dll/asm/REL/m551Dll/stage.s.
 *
 * Every function but fn_1_16C40 and the empty ones comes from the header and sits
 * in the object's second .text section: fn_1_169F4 (DS_S_WORKINIT), fn_1_16C54/16C74
 * (DS_S_CHARMOT_IDX), fn_1_16C98 (DS_S_PADREAD_262), fn_1_170B0 (DS_S_CHARMOTION:
 * 14 motions, DS_CHARMOTION_CLEAR and DS_CHARMOTION_CURZERO) and fn_1_17264
 * (DS_S_MOTIONEXEC: DS_SHIFT_POLL, DS_MOTIONEXEC_NOHANDOVER, two slots on
 * models 81-82). m541 and m543 have the same stage.c with other constants.
 */
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"

#include "REL/m551Dll/m551.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

M551_WORK *lbl_1_bss_17A08;

#define DS_WORK                 M551_WORK
#define DS_STAGEWORK            lbl_1_bss_17A08
#define DS_CHARMDL              81
#define DS_SHIFT_POLL
#define DS_MOTIONEXEC_NOHANDOVER
#define DS_MOTIONEXEC_NUM       2
#define DS_CHARMOTION_NUM       14
#define DS_CHARMOTION_SPEEDCUR  0.0f
#define DS_CHARMOTION_CLEAR
#define DS_CHARMOTION_CURZERO
#define DS_FN_WorkInit          fn_1_169F4
#define DS_FN_CharMotDataIdxSet fn_1_16C54
#define DS_FN_CharMotIdIdxSet   fn_1_16C74
#define DS_FN_PadRead262        fn_1_16C98
#define DS_FN_CharMotionCreate  fn_1_170B0
#define DS_FN_MotionExec        fn_1_17264

#define DS_S_WORKINIT
#include "REL/duelstage.h"

void fn_1_16C40(s16 stageNo)
{
    lbl_1_bss_17A08->stageNo = stageNo;
}

#define DS_S_CHARMOT_IDX
#include "REL/duelstage.h"

void fn_1_16C94(void)
{
}

#define DS_S_PADREAD_262
#define DS_S_CHARMOTION
#define DS_S_MOTIONEXEC
#include "REL/duelstage.h"

void fn_1_1761C(void)
{
}

void fn_1_17620(void)
{
}

void fn_1_17624(void)
{
}

void fn_1_17628(void)
{
}

void fn_1_1762C(void)
{
}

void fn_1_17630(void)
{
}

void fn_1_17634(void)
{
}
