/*
 * duelstage.h -- the stage framework every Mario Party 5 duel compiles in.
 *
 * WHAT THIS IS. The fifteen MG_TYPE_KETTOU overlays each split into
 * <name>.c + game.c + stage.c, and stage.c opens with the same small block:
 * a work-struct initialiser that picks the two duellists out of GwPlayerConf,
 * two setters for their motion tables, a pad reader, a motion loader and a
 * per-frame motion driver. As with REL/mgframe.h, the original compiles that
 * block into each overlay's own translation unit, so it cannot be a library.
 * m550dll and m554dll were decompiled separately and these functions came out
 * identical apart from the constants the knobs below supply. This file is that
 * block, lifted once.
 *
 * WHY IT IS A HEADER AND NOT A .c, AND WHY IT IS INCLUDED MORE THAN ONCE. The
 * same as mgframe.h: CodeWarrior's inlining and the object's function order
 * both follow definition order, and every duel puts its own functions between
 * the shared ones (m550's StageModelCreate sits between WorkInit and
 * CharMotDataSet). So an overlay includes this file at each point where the
 * reference object has a shared run, naming the sections it wants:
 *
 *     #define DS_S_WORKINIT
 *     #include "REL/duelstage.h"
 *
 * Every function carries a permanent DS_HAVE_<name> guard, so it is emitted at
 * the first point that asks for it and skipped after. The section selectors are
 * #undef'd on the way out. Within one include, functions come out in this
 * file's order.
 *
 * SECTIONS, in the order this file emits them:
 *
 *   DS_S_WORKINIT      WorkInit
 *   DS_S_CHARMOT       CharMotDataSet, CharMotIdSet
 *   DS_S_CHARMOT_IDX   CharMotDataIdxSet, CharMotIdIdxSet, the head-D indexed
 *                      setters (m544, m543)
 *   DS_S_PADREAD       PadRead
 *   DS_S_PADREAD_262   PadRead262, the DS_CHAR262 pad reader (m545, m544)
 *   DS_S_CHARMOTION    CharMotionCreate
 *   DS_S_MOTIONEXEC    MotionExec
 *   DS_S_MOTIONEXEC_B  MotionExecB, the work-head-B driver (m542, m547, m548)
 *   DS_S_MOTIONEXEC_C  MotionExecC, the work-head-C driver (m545, m546)
 *   DS_S_PROPS_D       MatAlphaSet, then (after PropExec) PropOrbit and
 *                      PropTurn -- the first two runs of the head-D prop tail
 *                      m549 and m553 share (m553 at DS_PROPDMDL 102, m549 36)
 *   DS_S_PROPEXEC      PropExec, the updater runner, at DS_PROPEXEC_NUM entries
 *                      (eight duels; DS_S_PROPS_B emits it too)
 *   DS_S_PROPS_B       the prop table, PropSwingGo (only with DS_PROPSWING_GO),
 *                      PropSwing, PropSway, PropPendulum, PropRoll and
 *                      PropSlide (m547, m548; m545 at DS_PROPMDL 24; m544 at 20
 *                      and m546 at 15, both with PropSwingGo and their own
 *                      PropSlide)
 *   DS_S_EFFECT9STOP   Effect9Stop, at slot DS_EFFECT9STOP_IDX
 *   DS_S_PROPS_D2      PropLight, PropBigOrbit, PropSkyAStop, PropSkyA,
 *                      PropSkyBStop and PropSkyB -- the head-D prop tail's
 *                      third run, after the slot store above
 *
 * KNOBS. Everything an overlay varies is a macro, defined before the include
 * that needs it and left defined. None has a default: a missing knob is an
 * #error, not a silently different function.
 *
 *   DS_WORK            the overlay's work struct type. Its size is what
 *                      WorkInit clears (m550 0xA14, m554 0x814), and the type
 *                      of its effect[] is the effect slot, so this one knob
 *                      also carries the slot size (m550 0x4C, m554 0x3C).
 *   DS_STAGEWORK       the name of the overlay's `DS_WORK *` global, which the
 *                      overlay defines itself where its .bss has it (m550's is
 *                      static, m554's is not).
 *   DS_CHARMDL         model-table index of duellist 0's model; duellist 1 is
 *                      the next. m550 2, m554 0x4E, m548 12, m547 13, m542 32,
 *                      m552 0, m544 32, m545 36, m546 27. (MotionExec,
 *                      MotionExecB, MotionExecC)
 *   DS_MOTIONEXEC_NUM  MotionExec: the player slots it drives, on models
 *                      DS_CHARMDL.. . 2 in m550, m554 and m552; 3 in m544, whose
 *                      head-D work has a third slot for a stage actor.
 *   DS_SHIFT_POLL      MotionExec only. Undefined: a motion shift ends when
 *                      shiftTime counts down to 0 (m550). Defined: case 2 reads
 *                      Hu3DMotionShiftTimeGet into shiftTimeCur and ends a
 *                      non-looping shift at shiftSpeed - 1 (m554).
 *   DS_CHARMOTION_NUM  CharMotionCreate: motions loaded per duellist (m550,
 *                      m554, m548, m545 5; m547 7; m542, m546 9).
 *   DS_CHARMOTION_SPEEDCUR  CharMotionCreate: the applied speed each player
 *                      starts with. 1.0f in m550/m554; m548 and m545 start it
 *                      at -1.0f, so the first motion driver pass always pushes
 *                      the speed.
 *   DS_MOTIONEXEC_NOHANDOVER  MotionExec only.
 *                      Undefined: case 3 takes the shifted-to motion as the
 *                      current one (m550, m554). Defined: case 3 only ends the
 *                      shift (m552).
 *   DS_MOTIONEXEC_C_UNSET  MotionExecC only. Undefined: case 3 only ends the
 *                      shift (m546). Defined: it also unsets the applied motion
 *                      and speed, so the next pass pushes both again (m545).
 *   DS_CHARMOTION_NOSPEED  CharMotionCreate only. Undefined: the requested
 *                      speed starts at 1.0f (m550, m554, m542, m547, m548).
 *                      Defined: it is left as WorkInit cleared it (m545, m546).
 *   DS_CHARMOTION_CLEAR  CharMotionCreate only, the 109-instruction family
 *                      (m552 on head A; m541, m543, m549, m551, m553 on head
 *                      D). Defined: motNo, speed, attr and attrCur start at 0
 *                      as well; NOSPEED is then ignored.
 *   DS_CHARMOTION_CURZERO  With DS_CHARMOTION_CLEAR only. Undefined: motNoCur
 *                      starts at -1 (m552). Defined: it starts at 0 like motNo,
 *                      so the first MotionExec pass does not set motion 0
 *                      (m543; m541 and m551 have the same store).
 *   DS_PROPTBL         the name of the updater table PropExec runs. With
 *                      DS_S_PROPS_B the header defines it (five entries), so it
 *                      lands in .data where the reference has it, between the
 *                      overlay's arena table and PropRoll's jumptable (m548
 *                      lbl_1_data_5C0, m547 lbl_1_data_3EC); with
 *                      DS_S_PROPEXEC alone it names a table the overlay defines
 *                      itself (m550 StageFuncTbl, m553 lbl_1_data_3C0).
 *   DS_PROPEXEC_NUM    PropExec: entries in DS_PROPTBL. 5 in m544, m545, m546,
 *                      m547, m548 and m549; 6 in m553; 7 in m550.
 *   DS_PROPDMDL        DS_S_PROPS_D and DS_S_PROPS_D2: added to every model
 *                      number in the head-D prop tail, whose models are
 *                      DS_PROPDMDL+0x00..+0x1F. m553 102, m549 36 (every m553
 *                      model number is m549's + 0x42).
 *   DS_PROPD_SKYZ      DS_S_PROPS_D2: PropSkyA's start z and y, the only two
 *   DS_PROPD_SKYY      floats in the tail that differ between its two users.
 *                      m553 2500.0f and 300.0f, m549 2800.0f and 800.0f.
 *   DS_EFFECT9STOP_IDX DS_S_EFFECT9STOP: the effect slot it parks. 9 in m550
 *                      and m554, 13 in m549 and m553 -- read off the object,
 *                      not assumed; see the section's comment.
 *   DS_PROPMDL         DS_S_PROPS_B: added to every prop model number (1-8),
 *                      so the props are models DS_PROPMDL+1..DS_PROPMDL+8.
 *                      m547 and m548 0, m545 24, m544 20, m546 15.
 *   DS_PROPSWING_GO    DS_S_PROPS_B. Defined: PropSwing's first wait is 10000
 *                      frames, and DS_FN_PropSwingGo, emitted just before it,
 *                      ends the wait when game code calls it (m544, m546).
 *   DS_PROPROLL_PASSED DS_S_PROPS_B: the name of an int the overlay defines.
 *                      Defined: PropRoll's first pass runs at z=950 and sets
 *                      it; every later pass runs at z=-2100 (m546).
 *   DS_PROPSLIDE_OWN   DS_S_PROPS_B. Defined: PropSlide is not emitted; the
 *                      overlay defines DS_FN_PropSlide itself after the include
 *                      (m544 and m546: a sound pans across with the slide).
 *   DS_FN_<name>       the name each emitted function takes. Overlays with
 *                      upstream names use them (M550WorkInit); the rest use the
 *                      reference's fn_1_XXXX, so fndiff.py still pairs them
 *                      with the reference object by name.
 *
 * THE WORK. Every duel's work struct starts with the same 0x110 bytes, and the
 * effect slots every stage updater uses start with the same 0x3C. Spell them
 * with DS_WORK_HEAD and DS_EFFECT_HEAD at the top of the overlay's own structs;
 * DS_EFFECT is the head on its own, for a duel whose slots are 0x3C.
 *
 * VERIFYING A CHANGE HERE. Every user is compared against the objects dtk
 * splits out of the real RELs, so touching this file means rebuilding every
 * user's three CodeWarrior objects and diffing complete `fndiff.py rfn` dumps
 * (register numbers and data-symbol names included) against copies taken
 * before the edit. The extraction that created this file (2026-09-14) left
 * every function of m550dll and m554dll identical; the dump script and result
 * are recorded in docs/MP5_MINIGAME_PLAN.md Phase 2.
 *
 * See src/REL/m550dll/stage.c and src/REL/m554dll/stage.c.
 */

#ifndef DUELSTAGE_H
#define DUELSTAGE_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/*
 * One entry of the retained-mode model table. The overlay walks it once a frame
 * and pushes pos and rot at Hu3D for every entry whose id is not negative.
 */
typedef struct DuelStageModel_s {
    /* 0x00 */ HU3DMODELID modelId;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
} DS_MODEL;                         /* 0x1C */

/* Who the two duellists are (WorkInit), and their pads this frame (PadRead). */
typedef struct DuelStageChar_s {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 charNo;
    /* 0x04 */ s16 dif;             /* GwPlayerConf dif + 1, and 0 for a human */
    /* 0x06 */ s16 padNo;
    /* 0x08 */ u32 btn;
    /* 0x0C */ s32 btnDown;
    /* 0x10 */ s8 stkX;
    /* 0x11 */ s8 stkY;
    /* 0x12 */ u16 btnRep;
    /* 0x14 */ s8 subStkX;
    /* 0x15 */ s8 subStkY;
    /* 0x16 */ u8 trigL;
    /* 0x17 */ u8 trigR;
    /* 0x18 */ u8 dStk;
    /* 0x19 */ u8 dStkRep;
    /* 0x1A */ u8 pad1A[2];
} DS_CHAR;                          /* 0x1C */

/*
 * The same 0x1C as the PadRead-262 family reads it (DS_S_PADREAD_262; heads C
 * and D): only stkX sits before btnRep, and the other bytes follow it one
 * byte later than in DS_CHAR.
 */
typedef struct DuelStageChar262_s {
    /* 0x00 */ s16 no;
    /* 0x02 */ s16 charNo;
    /* 0x04 */ s16 dif;
    /* 0x06 */ s16 padNo;
    /* 0x08 */ u32 btn;
    /* 0x0C */ s32 btnDown;
    /* 0x10 */ s8 stkX;
    /* 0x11 */ u8 pad11;
    /* 0x12 */ u16 btnRep;
    /* 0x14 */ s8 stkY;
    /* 0x15 */ s8 subStkX;
    /* 0x16 */ s8 subStkY;
    /* 0x17 */ u8 trigL;
    /* 0x18 */ u8 trigR;
    /* 0x19 */ u8 dStk;
    /* 0x1A */ u8 dStkRep;
    /* 0x1B */ u8 pad1B;
} DS_CHAR262;                       /* 0x1C */

/*
 * One duellist's model state. The game code writes the requested half of each
 * pair; MotionExec compares it against the applied half and pushes the
 * difference at Hu3D, which is why game code never calls Hu3DMotionSet.
 *
 * DS_PLAYER_HEAD is the part every duel has. Work head B stops there
 * (DS_PLAYERB, 0x24, driven by MotionExecB); head A adds the queued motion
 * and the shift state (DS_PLAYER, 0x54).
 */
#define DS_PLAYER_HEAD \
    /* 0x00 */ s16 motNo;        \
    /* 0x02 */ s16 motNoCur;     \
    /* 0x04 */ float speed;      \
    /* 0x08 */ float speedCur;   \
    /* 0x0C */ float time;       \
    /* 0x10 */ float timeCur;    \
    /* 0x14 */ float maxTime;    \
    /* 0x18 */ u32 attr;         \
    /* 0x1C */ u32 attrCur;      \
    /* 0x20 */ u32 attrReset

typedef struct DuelStagePlayerB_s {
    DS_PLAYER_HEAD;
} DS_PLAYERB;                       /* 0x24 */

typedef struct DuelStagePlayer_s {
    DS_PLAYER_HEAD;
    /* 0x24 */ int endF;
    /* 0x28 */ s16 nextF;
    /* 0x2A */ s16 nextMotNo;
    /* 0x2C */ float nextTime;
    /* 0x30 */ u32 nextAttr;
    /* 0x34 */ u32 nextAttrReset;
    /* 0x38 */ s16 shiftMode;
    /* 0x3A */ s16 shiftMotNo;
    /* 0x3C */ u32 shiftAttr;
    /* 0x40 */ float shiftTime;
    /* 0x44 */ float shiftSpeed;
    /* 0x48 */ float shiftTimeCur;  /* DS_SHIFT_POLL's Hu3DMotionShiftTimeGet */
    /* 0x4C */ float shiftMaxTime;
    /* 0x50 */ u8 unk50[0x04];
} DS_PLAYER;                        /* 0x54 */

/* Head C's slot (DS_S_MOTIONEXEC_C): the head, the end flag and the shift, no queued motion. */
typedef struct DuelStagePlayerC_s {
    DS_PLAYER_HEAD;
    /* 0x24 */ int endF;
    /* 0x28 */ s16 shiftMode;
    /* 0x2A */ s16 shiftMotNo;
    /* 0x2C */ u32 shiftAttr;
    /* 0x30 */ float shiftTime;
    /* 0x34 */ float shiftSpeed;
    /* 0x38 */ float shiftTimeCur;
    /* 0x3C */ float shiftMaxTime;
    /* 0x40 */ u8 unk40[0x04];
} DS_PLAYERC;                       /* 0x44 */

/*
 * The head of every effect slot. The float fields mean different things to
 * different stage updaters, so they are named by offset rather than by role.
 */
#define DS_EFFECT_HEAD \
    /* 0x00 */ int mode;         \
    /* 0x04 */ int timer[3];     \
    /* 0x10 */ int counter;      \
    /* 0x14 */ int unk14;        \
    /* 0x18 */ int subMode;      \
    /* 0x1C */ int doneF;        \
    /* 0x20 */ u8 unk20[0x0C];   \
    /* 0x2C */ float f2C;        \
    /* 0x30 */ float f30;        \
    /* 0x34 */ float f34;        \
    /* 0x38 */ float f38

typedef struct DuelStageEffect_s {
    DS_EFFECT_HEAD;
} DS_EFFECT;                        /* 0x3C */

/*
 * The head-D duels' slot: the same head plus three more floats, which
 * DS_S_PROPS_D's big orbiter uses to hold the arc it hands over to. m549 and
 * m553 both have twenty-one of these filling the work from 0x1C8 to 0x804.
 */
typedef struct DuelStageEffectD_s {
    DS_EFFECT_HEAD;
    /* 0x3C */ float f3C;
    /* 0x40 */ float f40;
    /* 0x44 */ float f44;
    /* 0x48 */ u8 unk48[0x04];
} DS_EFFECTD;                       /* 0x4C */

/*
 * One prop slot of DS_S_PROPS_B, a work-head-B duel's effect[0..4] at work+0xF0.
 * Each updater owns one; effect[0].mode is the arena's state (0 idle .. 4),
 * which PropSwing drives and the other four start and stop on.
 */
typedef struct DuelStagePropB_s {
    /* 0x00 */ int stopF;           /* PropSwing, PropSway and PropPendulum do nothing while set */
    /* 0x04 */ int timer;
    /* 0x08 */ int maxTime;
    /* 0x0C */ int mode;
    /* 0x10 */ u8 unk10[0x10];
    /* 0x20 */ float f20;
    /* 0x24 */ float f24;
    /* 0x28 */ float f28;
    /* 0x2C */ u8 unk2C[0x04];
} DS_PROPB;                         /* 0x30 */

/*
 * The head of every duel's work struct, 0x000..0x110. mode[0] is the sequence
 * sub-state the overlay's seq hooks index their function tables by.
 */
#define DS_WORK_HEAD \
    /* 0x000 */ OMOBJMAN *objman;                  \
    /* 0x004 */ DS_CHAR chr[2];                    \
    /* 0x03C */ DS_MODEL *models;                  \
    /* 0x040 */ unsigned int *charMotData[2];      \
    /* 0x048 */ HU3DMOTID *motId[2];               \
    /* 0x050 */ DS_PLAYER player[2];               \
    /* 0x0F8 */ unsigned int *stageDataTbl;        \
    /* 0x0FC */ s16 stageNo;                       \
    /* 0x0FE */ s16 pad0FE;                        \
    /* 0x100 */ int mode[4]

#endif /* DUELSTAGE_H */


/* The function bodies' own includes, pulled in only by an include that emits code. */
#if defined(DS_S_WORKINIT) || defined(DS_S_CHARMOT) || defined(DS_S_CHARMOT_IDX) || defined(DS_S_PADREAD) || defined(DS_S_PADREAD_262) \
    || defined(DS_S_CHARMOTION) || defined(DS_S_MOTIONEXEC) || defined(DS_S_MOTIONEXEC_B) \
    || defined(DS_S_MOTIONEXEC_C) || defined(DS_S_PROPS_B) || defined(DS_S_PROPEXEC) \
    || defined(DS_S_PROPS_D) || defined(DS_S_PROPS_D2) || defined(DS_S_EFFECT9STOP)
#ifndef DUELSTAGE_BODY_H
#define DUELSTAGE_BODY_H
#include "game/gamework.h"
#include "game/charman.h"
#include "game/pad.h"
#include "string.h"
#endif
#if !defined(DS_WORK) || !defined(DS_STAGEWORK)
#error "duelstage.h: define DS_WORK and DS_STAGEWORK before including a section"
#endif
#endif


/* ===== 1. the work struct and the duellists ===== */
#if defined(DS_S_WORKINIT) && !defined(DS_HAVE_WorkInit)
#define DS_HAVE_WorkInit
#ifndef DS_FN_WorkInit
#error "duelstage.h: DS_S_WORKINIT needs DS_FN_WorkInit"
#endif
/*
 * m550 fn_1_4E8C, m554 fn_1_62F0 -- 147 instructions in all fifteen duels, and
 * instruction-identical to every one of them as spelled here (the assignment
 * inside the compare is what puts i's sign-extension first). It
 * clears the work struct, keeps the model table and stage data list, and works
 * out who the two duellists are.
 *
 * The roster comes out of GwPlayerConf by group: the first player of group 0
 * becomes chr[0] and the first of group 1 chr[1]. The inner loop deliberately
 * does not restart -- it keeps scanning from where it left off -- so a board
 * that put both group-1 players after both group-0 ones still resolves.
 */
void DS_FN_WorkInit(DS_WORK *work, DS_MODEL *models, unsigned int *dataTbl)
{
    s16 i;
    s16 j;
    s16 grp;

    DS_STAGEWORK = work;
    memset(DS_STAGEWORK, 0, sizeof(DS_WORK));
    DS_STAGEWORK->models = models;
    DS_STAGEWORK->stageDataTbl = dataTbl;
    i = 0;
    do {
        for(j=0; j<4; j++) {
            if(i == (grp = GwPlayerConf[j].grp)) {
                DS_STAGEWORK->chr[i].no = j;
                i++;
                if(i >= 2) {
                    break;
                }
            }
        }
    } while(i < 2);
    for(j=0; j<2; j++) {
        DS_STAGEWORK->chr[j].charNo = GwPlayerConf[DS_STAGEWORK->chr[j].no].charNo;
        DS_STAGEWORK->chr[j].padNo = GwPlayerConf[DS_STAGEWORK->chr[j].no].padNo;
        grp = GwPlayerConf[DS_STAGEWORK->chr[j].no].type;
        if(grp != 0) {
            DS_STAGEWORK->chr[j].dif = GwPlayerConf[DS_STAGEWORK->chr[j].no].dif+1;
        }
    }
}
#endif


/* ===== 2. the duellists' motion tables ===== */
#if defined(DS_S_CHARMOT) && !defined(DS_HAVE_CharMotDataSet)
#define DS_HAVE_CharMotDataSet
#if !defined(DS_FN_CharMotDataSet) || !defined(DS_FN_CharMotIdSet)
#error "duelstage.h: DS_S_CHARMOT needs DS_FN_CharMotDataSet and DS_FN_CharMotIdSet"
#endif
/* m550 fn_1_58F4, m554 fn_1_6C20 -- the two rows of the overlay's motion data table. */
void DS_FN_CharMotDataSet(unsigned int *dataA, unsigned int *dataB)
{
    DS_STAGEWORK->charMotData[0] = dataA;
    DS_STAGEWORK->charMotData[1] = dataB;
}
/* m550 fn_1_5918, m554 fn_1_6C44 -- and where their five motion ids go. */
void DS_FN_CharMotIdSet(HU3DMOTID *idA, HU3DMOTID *idB)
{
    DS_STAGEWORK->motId[0] = idA;
    DS_STAGEWORK->motId[1] = idB;
}
#endif


/* ===== 2b. the head-D indexed motion-table setters ===== */
#if defined(DS_S_CHARMOT_IDX) && !defined(DS_HAVE_CharMotDataIdxSet)
#define DS_HAVE_CharMotDataIdxSet
#if !defined(DS_FN_CharMotDataIdxSet) || !defined(DS_FN_CharMotIdIdxSet)
#error "duelstage.h: DS_S_CHARMOT_IDX needs DS_FN_CharMotDataIdxSet and DS_FN_CharMotIdIdxSet"
#endif
/*
 * m544 fn_1_A3F0, m543 fn_1_FCF4 -- 8 instructions, identical in both (work
 * offsets included). Head D's charMotData[] and motId[] have a slot per player
 * (m544's third is its stage actor), so the setters take the slot.
 */
void DS_FN_CharMotDataIdxSet(s16 no, unsigned int *data)
{
    DS_STAGEWORK->charMotData[no] = data;
}
/* m544 fn_1_A410, m543 fn_1_FD14 -- and where that slot's motion ids go. */
void DS_FN_CharMotIdIdxSet(s16 no, HU3DMOTID *id)
{
    DS_STAGEWORK->motId[no] = id;
}
#endif


/* ===== 3. the pad reader ===== */
#if defined(DS_S_PADREAD) && !defined(DS_HAVE_PadRead)
#define DS_HAVE_PadRead
#ifndef DS_FN_PadRead
#error "duelstage.h: DS_S_PADREAD needs DS_FN_PadRead"
#endif
/*
 * m550 fn_1_5BD8, m554 fn_1_6E80 -- the pad object ObjectSetup adds before
 * anything else exists. It copies the two duellists' controllers into their
 * DS_CHAR once a frame so nothing downstream has to know a pad number, and
 * zeroes the whole block for a COM player -- which is what `dif` non-zero
 * means here.
 *
 * Both sticks get a ten-unit deadzone. The sub-stick and triggers do not.
 */
void DS_FN_PadRead(OMOBJ *obj)
{
    int i;

    for(i=0; i<2; i++) {
        if(DS_STAGEWORK->chr[i].dif != 0) {
            memset(&DS_STAGEWORK->chr[i].btn, 0, 20);
            continue;
        }
        DS_STAGEWORK->chr[i].btn = HuPadBtn[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].btnDown = HuPadBtnDown[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].btnRep = HuPadBtnRep[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].stkX = (s8)HuPadStkX[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].stkX = (((DS_STAGEWORK->chr[i].stkX >= 0) ? DS_STAGEWORK->chr[i].stkX : -DS_STAGEWORK->chr[i].stkX) < 10) ? 0 : DS_STAGEWORK->chr[i].stkX;
        DS_STAGEWORK->chr[i].stkY = (s8)HuPadStkY[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].stkY = (((DS_STAGEWORK->chr[i].stkY >= 0) ? DS_STAGEWORK->chr[i].stkY : -DS_STAGEWORK->chr[i].stkY) < 10) ? 0 : DS_STAGEWORK->chr[i].stkY;
        DS_STAGEWORK->chr[i].subStkX = (s8)HuPadSubStkX[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].subStkY = (s8)HuPadSubStkY[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].trigL = HuPadTrigL[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].trigR = HuPadTrigR[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].dStk = HuPadDStk[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].dStkRep = HuPadDStkRep[DS_STAGEWORK->chr[i].padNo];
    }
}
#endif


/* ===== 3b. the PadRead-262 pad reader ===== */
#if defined(DS_S_PADREAD_262) && !defined(DS_HAVE_PadRead262)
#define DS_HAVE_PadRead262
#ifndef DS_FN_PadRead262
#error "duelstage.h: DS_S_PADREAD_262 needs DS_FN_PadRead262"
#endif
/*
 * m545 fn_1_803C, m544 fn_1_A9A4 -- 262 instructions, identical in both (work
 * offsets included), and with symbol names masked in m541 and m546. PadRead for
 * a work whose chr[] is DS_CHAR262: only the main stick's x axis gets the
 * ten-unit deadzone. Zeroed for a computer duellist.
 */
void DS_FN_PadRead262(OMOBJ *obj)
{
    int i;

    for(i=0; i<2; i++) {
        if(DS_STAGEWORK->chr[i].dif != 0) {
            memset(&DS_STAGEWORK->chr[i].btn, 0, 20);
            continue;
        }
        DS_STAGEWORK->chr[i].btn = HuPadBtn[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].btnDown = HuPadBtnDown[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].btnRep = HuPadBtnRep[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].stkX = (s8)HuPadStkX[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].stkX = (((DS_STAGEWORK->chr[i].stkX >= 0) ? DS_STAGEWORK->chr[i].stkX : -DS_STAGEWORK->chr[i].stkX) < 10) ? 0 : DS_STAGEWORK->chr[i].stkX;
        DS_STAGEWORK->chr[i].stkY = (s8)HuPadStkY[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].subStkX = (s8)HuPadSubStkX[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].subStkY = (s8)HuPadSubStkY[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].trigL = HuPadTrigL[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].trigR = HuPadTrigR[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].dStk = HuPadDStk[DS_STAGEWORK->chr[i].padNo];
        DS_STAGEWORK->chr[i].dStkRep = HuPadDStkRep[DS_STAGEWORK->chr[i].padNo];
    }
}
#endif


/* ===== 4. the duellists' motions ===== */
#if defined(DS_S_CHARMOTION) && !defined(DS_HAVE_CharMotionCreate)
#define DS_HAVE_CharMotionCreate
#if !defined(DS_FN_CharMotionCreate) || !defined(DS_CHARMOTION_NUM) || !defined(DS_CHARMOTION_SPEEDCUR)
#error "duelstage.h: DS_S_CHARMOTION needs DS_FN_CharMotionCreate, DS_CHARMOTION_NUM and DS_CHARMOTION_SPEEDCUR"
#endif
#if defined(DS_CHARMOTION_CURZERO) && !defined(DS_CHARMOTION_CLEAR)
#error "duelstage.h: DS_CHARMOTION_CURZERO needs DS_CHARMOTION_CLEAR"
#endif
/*
 * m550 fn_1_6094, m554 fn_1_733C, m548 fn_1_6D4C (85 instructions), m545
 * fn_1_8454 (75, DS_CHARMOTION_NOSPEED), m552 fn_1_BF98 (109,
 * DS_CHARMOTION_CLEAR), m543 fn_1_10150 (109, DS_CHARMOTION_CLEAR and
 * DS_CHARMOTION_CURZERO on head D) -- DS_CHARMOTION_NUM motions each, and
 * the state they start in. The player slot's size comes from DS_WORK (0x54 on
 * head A, 0x24 on head B, 0x44 on head C).
 */
void DS_FN_CharMotionCreate(void)
{
    s16 i;
    s16 j;

    for(i=0; i<2; i++) {
        for(j=0; j<DS_CHARMOTION_NUM; j++) {
            DS_STAGEWORK->motId[i][j] = CharMotionCreate(DS_STAGEWORK->chr[i].charNo, DS_STAGEWORK->charMotData[i][j]);
        }
    }
    for(i=0; i<2; i++) {
#ifdef DS_CHARMOTION_CLEAR
        DS_STAGEWORK->player[i].motNo = 0;
#endif
#ifdef DS_CHARMOTION_CURZERO
        DS_STAGEWORK->player[i].motNoCur = 0;
#else
        DS_STAGEWORK->player[i].motNoCur = -1;
#endif
#if defined(DS_CHARMOTION_CLEAR)
        DS_STAGEWORK->player[i].speed = 0.0f;
#elif !defined(DS_CHARMOTION_NOSPEED)
        DS_STAGEWORK->player[i].speed = 1.0f;
#endif
        DS_STAGEWORK->player[i].speedCur = DS_CHARMOTION_SPEEDCUR;
#ifdef DS_CHARMOTION_CLEAR
        DS_STAGEWORK->player[i].attr = 0;
        DS_STAGEWORK->player[i].attrCur = 0;
#endif
    }
}
#endif


/* ===== 5. the motion driver ===== */
#if defined(DS_S_MOTIONEXEC) && !defined(DS_HAVE_MotionExec)
#define DS_HAVE_MotionExec
#if !defined(DS_FN_MotionExec) || !defined(DS_CHARMDL) || !defined(DS_MOTIONEXEC_NUM)
#error "duelstage.h: DS_S_MOTIONEXEC needs DS_FN_MotionExec, DS_CHARMDL and DS_MOTIONEXEC_NUM"
#endif
/*
 * m550 fn_1_61E8 (241 instructions), m554 fn_1_7490 (252, DS_SHIFT_POLL), m552
 * fn_1_C14C (237, DS_SHIFT_POLL and DS_MOTIONEXEC_NOHANDOVER on DS_CHARMDL 0),
 * m544 fn_1_AF60 (238, the same on head D with DS_CHARMDL 32 and three slots),
 * m543 fn_1_10304 (the same with DS_CHARMDL 60 and two slots; m541's is
 * DS_CHARMDL 106, m551's 81) --
 * the duellists' motion driver, added as an object by the init hook. The
 * game code sets what it wants on DS_PLAYER and this pushes the difference at
 * Hu3D once a frame: the motion, its speed, its attributes and its time, then
 * a three-step shift, then whatever was queued to follow the current motion
 * once it ends.
 */
void DS_FN_MotionExec(OMOBJ *obj)
{
    DS_PLAYER *pl;
    s16 mdlNo;
    s16 i;

    for(i=0; i<DS_MOTIONEXEC_NUM; i++) {
        pl = &DS_STAGEWORK->player[i];
        mdlNo = i+DS_CHARMDL;
        if(pl->motNo != pl->motNoCur) {
            Hu3DMotionSet(DS_STAGEWORK->models[mdlNo].modelId, DS_STAGEWORK->motId[i][pl->motNo]);
            pl->motNoCur = pl->motNo;
            pl->maxTime = Hu3DMotionMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        }
        if(pl->speed != pl->speedCur) {
            Hu3DMotionSpeedSet(DS_STAGEWORK->models[mdlNo].modelId, pl->speed);
            pl->speedCur = pl->speed;
        }
        if(pl->attr != pl->attrCur) {
            Hu3DModelAttrSet(DS_STAGEWORK->models[mdlNo].modelId, pl->attr);
            pl->attrCur = pl->attr;
        }
        if(pl->attrReset) {
            Hu3DModelAttrReset(DS_STAGEWORK->models[mdlNo].modelId, pl->attrReset);
            pl->attrReset = ~pl->attrReset;
            pl->attrCur = pl->attr = pl->attr&pl->attrReset;
            pl->attrReset = 0;
        }
        if(pl->time != pl->timeCur) {
            Hu3DMotionTimeSet(DS_STAGEWORK->models[mdlNo].modelId, pl->time);
        }
        switch(pl->shiftMode) {
            case 0:
                break;

            case 1:
                Hu3DMotionShiftSet(DS_STAGEWORK->models[mdlNo].modelId, DS_STAGEWORK->motId[i][pl->shiftMotNo], pl->shiftTime, pl->shiftSpeed, pl->shiftAttr);
                pl->shiftMaxTime = Hu3DMotionShiftMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
                pl->shiftMode = 2;
                break;

            case 2:
#ifdef DS_SHIFT_POLL
                pl->shiftTimeCur = Hu3DMotionShiftTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
                if(!(pl->shiftAttr & HU3D_MOTATTR_LOOP) && pl->shiftTimeCur >= pl->shiftSpeed-1.0f) {
                    pl->shiftMode = 3;
                }
#else
                pl->shiftTime -= 1.0f;
                if(pl->shiftTime <= 0.0f) {
                    pl->shiftMode = 3;
                }
#endif
                break;

            case 3:
#ifdef DS_MOTIONEXEC_NOHANDOVER
                pl->shiftMode = 0;
#else
                pl->maxTime = Hu3DMotionMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
                pl->timeCur = pl->time;
                pl->shiftMode = 0;
                pl->motNo = pl->motNoCur = pl->shiftMotNo;
#endif
                break;
        }
        pl->time = Hu3DMotionTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        pl->timeCur = pl->time;
        pl->endF = Hu3DMotionEndCheck(DS_STAGEWORK->models[mdlNo].modelId);
        if(pl->endF && pl->nextF) {
            pl->endF = 0;
            pl->nextF = 0;
            pl->motNo = pl->nextMotNo;
            pl->time = pl->nextTime;
            pl->attr = pl->nextAttr;
            pl->attrReset = pl->nextAttrReset;
        }
    }
}
#endif


/* ===== 5b. the work-head-B motion driver ===== */
#if defined(DS_S_MOTIONEXEC_B) && !defined(DS_HAVE_MotionExecB)
#define DS_HAVE_MotionExecB
#if !defined(DS_FN_MotionExecB) || !defined(DS_CHARMDL)
#error "duelstage.h: DS_S_MOTIONEXEC_B needs DS_FN_MotionExecB and DS_CHARMDL"
#endif
/*
 * m548 fn_1_6EA0, m547 fn_1_933C, m542 fn_1_92A4 -- 132 instructions, identical
 * but for DS_CHARMDL. MotionExec without the shift and queued-motion state: an
 * attribute reset simply clears all three attribute words.
 */
void DS_FN_MotionExecB(OMOBJ *obj)
{
    DS_PLAYERB *pl;
    s16 mdlNo;
    s16 i;

    for(i=0; i<2; i++) {
        pl = &DS_STAGEWORK->player[i];
        mdlNo = i+DS_CHARMDL;
        if(pl->motNo != pl->motNoCur) {
            Hu3DMotionSet(DS_STAGEWORK->models[mdlNo].modelId, DS_STAGEWORK->motId[i][pl->motNo]);
            pl->motNoCur = pl->motNo;
            pl->maxTime = Hu3DMotionMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        }
        if(pl->speed != pl->speedCur) {
            Hu3DMotionSpeedSet(DS_STAGEWORK->models[mdlNo].modelId, pl->speed);
            pl->speedCur = pl->speed;
        }
        if(pl->attr != pl->attrCur) {
            Hu3DModelAttrSet(DS_STAGEWORK->models[mdlNo].modelId, pl->attr);
            pl->attrCur = pl->attr;
        }
        if(pl->attrReset) {
            Hu3DModelAttrReset(DS_STAGEWORK->models[mdlNo].modelId, pl->attrReset);
            pl->attrCur = pl->attr = pl->attrReset = 0;
        }
        if(pl->time != pl->timeCur) {
            Hu3DMotionTimeSet(DS_STAGEWORK->models[mdlNo].modelId, pl->time);
        }
        pl->time = Hu3DMotionTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        pl->timeCur = pl->time;
    }
}
#endif


/* ===== 5c. the work-head-C motion driver ===== */
#if defined(DS_S_MOTIONEXEC_C) && !defined(DS_HAVE_MotionExecC)
#define DS_HAVE_MotionExecC
#if !defined(DS_FN_MotionExecC) || !defined(DS_CHARMDL)
#error "duelstage.h: DS_S_MOTIONEXEC_C needs DS_FN_MotionExecC and DS_CHARMDL"
#endif
/*
 * m545 fn_1_8580 (220 instructions, DS_MOTIONEXEC_C_UNSET), m546 fn_1_BEF8
 * (214) -- identical but for DS_CHARMDL and case 3. DS_S_MOTIONEXEC's shift
 * with DS_SHIFT_POLL's end test, MotionExecB's attribute reset, and no queued
 * motion; the work's player[] is DS_PLAYERC.
 */
void DS_FN_MotionExecC(OMOBJ *obj)
{
    DS_PLAYERC *pl;
    s16 mdlNo;
    s16 i;

    for(i=0; i<2; i++) {
        pl = &DS_STAGEWORK->player[i];
        mdlNo = i+DS_CHARMDL;
        if(pl->motNo != pl->motNoCur) {
            Hu3DMotionSet(DS_STAGEWORK->models[mdlNo].modelId, DS_STAGEWORK->motId[i][pl->motNo]);
            pl->motNoCur = pl->motNo;
            pl->maxTime = Hu3DMotionMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        }
        if(pl->speed != pl->speedCur) {
            Hu3DMotionSpeedSet(DS_STAGEWORK->models[mdlNo].modelId, pl->speed);
            pl->speedCur = pl->speed;
        }
        if(pl->attr != pl->attrCur) {
            Hu3DModelAttrSet(DS_STAGEWORK->models[mdlNo].modelId, pl->attr);
            pl->attrCur = pl->attr;
        }
        if(pl->attrReset) {
            Hu3DModelAttrReset(DS_STAGEWORK->models[mdlNo].modelId, pl->attrReset);
            pl->attrCur = pl->attr = pl->attrReset = 0;
        }
        if(pl->time != pl->timeCur) {
            Hu3DMotionTimeSet(DS_STAGEWORK->models[mdlNo].modelId, pl->time);
        }
        switch(pl->shiftMode) {
            case 0:
                break;

            case 1:
                Hu3DMotionShiftSet(DS_STAGEWORK->models[mdlNo].modelId, DS_STAGEWORK->motId[i][pl->shiftMotNo], pl->shiftTime, pl->shiftSpeed, pl->shiftAttr);
                pl->shiftMaxTime = Hu3DMotionShiftMaxTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
                pl->shiftMode = 2;
                break;

            case 2:
                pl->shiftTimeCur = Hu3DMotionShiftTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
                if(!(pl->shiftAttr & HU3D_MOTATTR_LOOP) && pl->shiftTimeCur >= pl->shiftSpeed-1.0f) {
                    pl->shiftMode = 3;
                }
                break;

            case 3:
                pl->shiftMode = 0;
#ifdef DS_MOTIONEXEC_C_UNSET
                pl->motNoCur = -1;
                pl->speedCur = -1.0f;
#endif
                break;
        }
        pl->time = Hu3DMotionTimeGet(DS_STAGEWORK->models[mdlNo].modelId);
        pl->timeCur = pl->time;
        pl->endF = Hu3DMotionEndCheck(DS_STAGEWORK->models[mdlNo].modelId);
    }
}
#endif


/* ===== 5d. the head-D prop tail, first run: the material-alpha setter ===== */
#if defined(DS_S_PROPS_D) && !defined(DS_HAVE_MatAlphaSet)
#define DS_HAVE_MatAlphaSet
#ifndef DS_FN_MatAlphaSet
#error "duelstage.h: DS_S_PROPS_D needs DS_FN_MatAlphaSet"
#endif
/*
 * m553 fn_1_EBFC, m549 fn_1_12E18 -- 26 instructions, sym-masked diff 0 (a leaf
 * with no calls and no globals). Set every material's invAlpha on one model.
 * It takes the Hu3D model id, not a model-table index as m550's M550MatAlphaSet
 * does, and the light updater calls it at four sites which CodeWarrior inlines.
 *
 * This is the first of DS_S_PROPS_D's two runs; the second (5g) is the two
 * updaters after PropExec. See section 7 for why the set needs two selectors.
 */
void DS_FN_MatAlphaSet(int modelId, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}
#endif


/* ===== 5e. the prop updater runner (eight duels) ===== */
/*
 * m548 fn_1_70B0, m547 fn_1_954C, m544 fn_1_B318, m545 fn_1_88F0, m546
 * fn_1_C250, m549 fn_1_12E80, m550 fn_1_65AC, m553 fn_1_EC64 -- one
 * 21-instruction function across eight overlays. Sym-masked against m548's,
 * each differs in exactly one line, the loop bound: 5 in m544/m545/m546/m547/
 * m548/m549, 7 in m550, 6 in m553. DS_S_PROPS_B always emits it (and defines
 * the five-entry table below); m550 and m553 take DS_S_PROPEXEC on its own and
 * define their own table, so DS_PROPTBL names a table the overlay defines there
 * and the header defines here.
 *
 * One caveat for a future user: DS_HAVE_PropExec below guards the table as well
 * as the function, so the table is emitted by the FIRST include that asks for
 * PropExec. Every current user is fine -- a DS_S_PROPS_B user takes both in one
 * include, and m550/m553 take DS_S_PROPEXEC alone -- but an overlay that took
 * DS_S_PROPEXEC in an early include and DS_S_PROPS_B in a later one would get
 * the function from the first and no table from the second.
 */
#if (defined(DS_S_PROPEXEC) || defined(DS_S_PROPS_B)) && !defined(DS_HAVE_PropExec)
#define DS_HAVE_PropExec
#if !defined(DS_PROPTBL) || !defined(DS_PROPEXEC_NUM) || !defined(DS_FN_PropExec)
#error "duelstage.h: PropExec needs DS_PROPTBL, DS_PROPEXEC_NUM and DS_FN_PropExec"
#endif
#ifdef DS_S_PROPS_B
void DS_FN_PropSwing(void);
void DS_FN_PropSway(void);
void DS_FN_PropPendulum(void);
void DS_FN_PropRoll(void);
void DS_FN_PropSlide(void);

void (*DS_PROPTBL[5])(void) = { DS_FN_PropSwing, DS_FN_PropSway, DS_FN_PropPendulum, DS_FN_PropRoll, DS_FN_PropSlide };
#endif

/* The stage object: run every prop updater in the table, once a frame. */
void DS_FN_PropExec(OMOBJ *obj)
{
    int i;

    for(i=0; i<DS_PROPEXEC_NUM; i++) {
        DS_PROPTBL[i]();
    }
}
#endif


/* ===== 5f. the stage props (work heads B and C, m544 on D) ===== */
#if defined(DS_S_PROPS_B) && !defined(DS_HAVE_PropsB)
#define DS_HAVE_PropsB
#if !defined(DS_PROPMDL) || !defined(DS_FN_PropSwing) || !defined(DS_FN_PropSway) \
    || !defined(DS_FN_PropPendulum) || !defined(DS_FN_PropRoll) || !defined(DS_FN_PropSlide)
#error "duelstage.h: DS_S_PROPS_B needs DS_PROPMDL and DS_FN_PropSwing, PropSway, PropPendulum, PropRoll, PropSlide"
#endif
#if defined(DS_PROPSWING_GO) && !defined(DS_FN_PropSwingGo)
#error "duelstage.h: DS_PROPSWING_GO needs DS_FN_PropSwingGo"
#endif
/*
 * m548 fn_1_70B0..fn_1_8F78, m547 fn_1_954C..fn_1_B414 -- 2,077 instructions,
 * identical in both (work offsets included) but for the names. m545's
 * fn_1_88F0..fn_1_A7B8 are the same but for the work offsets (its DS_PROPB
 * effect[5] is at 0x130, not 0xF0) and DS_PROPMDL. m544's (fn_1_B318..C7C0,
 * effect[5] at 0x1C8, DS_PROPMDL 20) and m546's (fn_1_C250..D6F8, m545's
 * offsets, DS_PROPMDL 15) add PropSwingGo; m546's PropRoll adds
 * DS_PROPROLL_PASSED; both write their own PropSlide. The overlay's DS_WORK has
 * DS_PROPB effect[5] and at least DS_PROPMDL+9 models; the props are models
 * DS_PROPMDL+1..+8. PropExec, above, runs the table once a frame.
 */
#ifdef DS_PROPSWING_GO
/* m544 fn_1_B36C, m546 fn_1_C2A4 -- 6 instructions. End PropSwing's first wait. */
void DS_FN_PropSwingGo(void)
{
    DS_STAGEWORK->effect[0].timer = 0;
}
#endif

/*
 * PropSwing (m548 fn_1_7104, m547 fn_1_95A0), 398 instructions; 387 with
 * DS_PROPSWING_GO (m544 fn_1_B384, m546 fn_1_C2BC).
 * effect[0], model 3: the arena's swinging prop and
 * its state machine. Waits 180-299 frames (the first wait 10000 frames, or
 * until PropSwingGo, with DS_PROPSWING_GO), eases its motion up and down, then
 * swings to a new heading over maxTime frames.
 */
void DS_FN_PropSwing(void)
{
    DS_MODEL *mdl = &DS_STAGEWORK->models[DS_PROPMDL+3];

    if(DS_STAGEWORK->effect[0].stopF != 0) {
        return;
    }
    switch(DS_STAGEWORK->effect[0].mode) {
        case 0:
#ifdef DS_PROPSWING_GO
            DS_STAGEWORK->effect[0].timer = 10000;
#else
            DS_STAGEWORK->effect[0].timer = (rand8()%120)+180;
#endif
            DS_STAGEWORK->effect[0].mode = 1;
            DS_STAGEWORK->effect[0].f24 = 0.4f;
            Hu3DMotionSpeedSet(mdl->modelId, DS_STAGEWORK->effect[0].f24);
            mdl->rot.y = -60.0f;
            break;

        case 1:
            if(DS_STAGEWORK->effect[0].timer-- < 0) {
                DS_STAGEWORK->effect[0].mode++;
                DS_STAGEWORK->effect[0].timer = 0;
                DS_STAGEWORK->effect[0].f20 = mdl->rot.y;
                DS_STAGEWORK->effect[0].maxTime = 120;
                DS_STAGEWORK->effect[0].f24 = (rand8()%10)+30;
                if(DS_STAGEWORK->effect[0].f20 > -45.0f) {
                    DS_STAGEWORK->effect[0].f24 = -DS_STAGEWORK->effect[0].f24;
                }
            }
            break;

        case 2:
            DS_STAGEWORK->effect[0].timer++;
            Hu3DMotionSpeedSet(mdl->modelId, 0.4+(0.5*sin((M_PI*((DS_STAGEWORK->effect[0].timer*90)/40))/180.0)));
            if(DS_STAGEWORK->effect[0].timer == 40) {
                DS_STAGEWORK->effect[0].timer = 0;
                DS_STAGEWORK->effect[0].mode++;
            }
            break;

        case 3:
            DS_STAGEWORK->effect[0].timer++;
            Hu3DMotionSpeedSet(mdl->modelId, 0.8+(0.2*sin((M_PI*((DS_STAGEWORK->effect[0].timer*180)/DS_STAGEWORK->effect[0].maxTime))/180.0)));
            mdl->rot.y = DS_STAGEWORK->effect[0].f20+(DS_STAGEWORK->effect[0].f24*sin((M_PI*((DS_STAGEWORK->effect[0].timer*90)/DS_STAGEWORK->effect[0].maxTime))/180.0));
            if(DS_STAGEWORK->effect[0].timer == DS_STAGEWORK->effect[0].maxTime) {
                mdl->rot.y = DS_STAGEWORK->effect[0].f20+DS_STAGEWORK->effect[0].f24;
                DS_STAGEWORK->effect[0].mode++;
                DS_STAGEWORK->effect[0].timer = 0;
            }
            break;

        case 4:
            DS_STAGEWORK->effect[0].timer++;
            Hu3DMotionSpeedSet(mdl->modelId, 0.8-(0.4*sin((M_PI*((DS_STAGEWORK->effect[0].timer*90)/40))/180.0)));
            if(DS_STAGEWORK->effect[0].timer == 40) {
                DS_STAGEWORK->effect[0].timer = (rand8()%120)+180;
                DS_STAGEWORK->effect[0].mode = 1;
            }
            break;
    }
}

/*
 * PropSway (m548 fn_1_773C, m547 fn_1_9BD8), 339 instructions.
 * effect[1], models 1 and 2: two props that sway
 * about 30 degrees while the arena is in play (states 2-4), each at its own
 * rate, and settle once it reaches state 4.
 */
void DS_FN_PropSway(void)
{
    DS_MODEL *mdlA = &DS_STAGEWORK->models[DS_PROPMDL+1];
    DS_MODEL *mdlB = &DS_STAGEWORK->models[DS_PROPMDL+2];

    if(DS_STAGEWORK->effect[1].stopF != 0) {
        return;
    }
    mdlA->rot.y = 30.0f;
    mdlB->rot.y = 30.0f;
    switch(DS_STAGEWORK->effect[1].mode) {
        case 0:
            if(DS_STAGEWORK->effect[0].mode == 2) {
                DS_STAGEWORK->effect[1].timer = 0;
                DS_STAGEWORK->effect[1].mode++;
                DS_STAGEWORK->effect[1].f20 = 20.0f;
                DS_STAGEWORK->effect[1].f24 = 5.0f;
                DS_STAGEWORK->effect[1].f28 = -5.0f;
            }
            break;

        case 1:
            DS_STAGEWORK->effect[1].timer++;
            mdlA->rot.y = 30.0+(DS_STAGEWORK->effect[1].f20*sin((M_PI*(DS_STAGEWORK->effect[1].timer*DS_STAGEWORK->effect[1].f24))/180.0));
            mdlB->rot.y = 30.0+(DS_STAGEWORK->effect[1].f20*sin((M_PI*(DS_STAGEWORK->effect[1].timer*DS_STAGEWORK->effect[1].f28))/180.0));
            if(DS_STAGEWORK->effect[0].mode == 4) {
                DS_STAGEWORK->effect[1].mode++;
                DS_STAGEWORK->effect[1].maxTime = 0;
            }
            break;

        case 2:
            DS_STAGEWORK->effect[1].timer++;
            DS_STAGEWORK->effect[1].maxTime++;
            if(DS_STAGEWORK->effect[1].maxTime > 40) {
                DS_STAGEWORK->effect[1].maxTime = 40;
            }
            DS_STAGEWORK->effect[1].f20 = 20.0-(20.0*sin((M_PI*((DS_STAGEWORK->effect[1].maxTime*90)/40))/180.0));
            mdlA->rot.y = 30.0+(DS_STAGEWORK->effect[1].f20*sin((M_PI*(DS_STAGEWORK->effect[1].timer*DS_STAGEWORK->effect[1].f24))/180.0));
            mdlB->rot.y = 30.0+(DS_STAGEWORK->effect[1].f20*sin((M_PI*(DS_STAGEWORK->effect[1].timer*DS_STAGEWORK->effect[1].f28))/180.0));
            if(DS_STAGEWORK->effect[0].mode == 1) {
                DS_STAGEWORK->effect[1].mode = 0;
            }
            break;
    }
}

/*
 * PropPendulum (m548 fn_1_7C88, m547 fn_1_A124), 569 instructions.
 * effect[2], models 4 and 5: a pendulum. Model 4
 * swings about x; model 5, turned 45 degrees about y, tilts with it about z
 * through a matrix. The swing grows with the arena's state and dies away at
 * state 4 until it is back at rest.
 */
void DS_FN_PropPendulum(void)
{
    Mtx mtx;
    Mtx rotMtx;
    DS_MODEL *mdlA = &DS_STAGEWORK->models[DS_PROPMDL+4];
    DS_MODEL *mdlB = &DS_STAGEWORK->models[DS_PROPMDL+5];

    if(DS_STAGEWORK->effect[2].stopF != 0) {
        return;
    }
    PSMTXIdentity(mtx);
    PSMTXRotRad(rotMtx, 'y', -0.7853982f);
    PSMTXConcat(mtx, rotMtx, mtx);
    mdlA->rot.y = 30.0f;
    switch(DS_STAGEWORK->effect[2].mode) {
        case 0:
            mdlB->rot.y = -45.0f;
            if(DS_STAGEWORK->effect[0].mode == 2) {
                DS_STAGEWORK->effect[2].f20 = 10.0f;
                DS_STAGEWORK->effect[2].f24 = 5.0f;
                DS_STAGEWORK->effect[2].timer = 0;
                DS_STAGEWORK->effect[2].mode++;
            }
            break;

        case 1:
            DS_STAGEWORK->effect[2].timer++;
            DS_STAGEWORK->effect[2].f24 = 5.0+(5.0*sin((M_PI*((DS_STAGEWORK->effect[2].timer*90)/40))/180.0));
            mdlA->rot.x = DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0);
            PSMTXRotRad(rotMtx, 'z', 0.017453292f*(DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0)));
            PSMTXConcat(mtx, rotMtx, mtx);
            Hu3DMtxRotGet(mtx, &mdlB->rot);
            if(DS_STAGEWORK->effect[0].mode == 3) {
                DS_STAGEWORK->effect[2].f24 = 10.0f;
                DS_STAGEWORK->effect[2].mode++;
            }
            break;

        case 2:
            DS_STAGEWORK->effect[2].timer++;
            mdlA->rot.x = DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0);
            PSMTXRotRad(rotMtx, 'z', 0.017453292f*(DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0)));
            PSMTXConcat(mtx, rotMtx, mtx);
            Hu3DMtxRotGet(mtx, &mdlB->rot);
            if(DS_STAGEWORK->effect[0].mode == 4) {
                DS_STAGEWORK->effect[2].mode++;
                DS_STAGEWORK->effect[2].maxTime = 0;
            }
            break;

        case 3:
            DS_STAGEWORK->effect[2].maxTime++;
            DS_STAGEWORK->effect[2].timer++;
            if(DS_STAGEWORK->effect[2].maxTime > 40) {
                DS_STAGEWORK->effect[2].maxTime = 40;
            }
            DS_STAGEWORK->effect[2].f20 = 10.0-(5.0*sin((M_PI*((DS_STAGEWORK->effect[2].maxTime*90)/40))/180.0));
            mdlA->rot.x = DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0);
            PSMTXRotRad(rotMtx, 'z', 0.017453292f*(DS_STAGEWORK->effect[2].f20*sin((M_PI*(DS_STAGEWORK->effect[2].timer*DS_STAGEWORK->effect[2].f24))/180.0)));
            PSMTXConcat(mtx, rotMtx, mtx);
            Hu3DMtxRotGet(mtx, &mdlB->rot);
            for(;;) {
                if(!(mdlA->rot.x >= 360.0f)) {
                    break;
                }
                mdlA->rot.x -= 360.0f;
            }
            if(DS_STAGEWORK->effect[0].mode == 1) {
                if(mdlA->rot.x >= 359.0f || mdlA->rot.x <= 1.0f) {
                    DS_STAGEWORK->effect[2].f20 = 0.0f;
                    mdlA->rot.x = 0.0f;
                    mdlB->rot.x = 0.0f;
                    mdlB->rot.y = -45.0f;
                    mdlB->rot.z = 0.0f;
                    DS_STAGEWORK->effect[2].mode = 0;
                }
            }
            break;
    }
    for(;;) {
        if(!(mdlA->rot.x >= 360.0f)) {
            break;
        }
        mdlA->rot.x -= 360.0f;
    }
}

/*
 * PropRoll (m548 fn_1_856C, m547 fn_1_AA08), 643 instructions.
 * effect[3], models 6 and 8: a rolling prop (model 8
 * follows 40 below it) that crosses from x=-1000 while spinning, eases through
 * a slow middle stretch and leaves past x=1000. Its first pass depends on
 * whether f20 is still zero; later passes start at state 4.
 */
void DS_FN_PropRoll(void)
{
    DS_MODEL *mdlA = &DS_STAGEWORK->models[DS_PROPMDL+6];
    DS_MODEL *mdlB = &DS_STAGEWORK->models[DS_PROPMDL+8];

    switch(DS_STAGEWORK->effect[3].mode) {
        case 0:
            if(DS_STAGEWORK->effect[0].mode == 2) {
                DS_STAGEWORK->effect[3].timer = 0;
                if(0.0f == DS_STAGEWORK->effect[3].f20) {
                    DS_STAGEWORK->effect[3].mode++;
                    DS_STAGEWORK->effect[3].timer = 0;
                    DS_STAGEWORK->effect[3].f20 = 15.0f;
                    DS_STAGEWORK->effect[3].f28 = ((rand8()%16)*25)-650;
                    mdlA->rot.z = 0.0f;
                    mdlA->pos.x = -1000.0f;
                } else {
                    DS_STAGEWORK->effect[3].mode = 4;
                    DS_STAGEWORK->effect[3].f20 = 10.0f;
                    DS_STAGEWORK->effect[3].f28 = ((rand8()%16)*25)-650;
                    mdlA->rot.z = 0.0f;
                    mdlA->pos.x = -1000.0f;
                }
#ifdef DS_PROPROLL_PASSED
                if(DS_PROPROLL_PASSED) {
                    mdlA->pos.z = -2100.0f;
                } else {
                    mdlA->pos.z = 950.0f;
                    DS_PROPROLL_PASSED = 1;
                }
#endif
                DS_STAGEWORK->effect[3].f24 = (250.0f*DS_STAGEWORK->effect[3].f20)/360.0f;
            }
            break;

        case 1:
            mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
            mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
            if(mdlA->pos.x >= DS_STAGEWORK->effect[3].f28) {
                DS_STAGEWORK->effect[3].mode++;
            }
            break;

        case 2:
            DS_STAGEWORK->effect[3].timer++;
            DS_STAGEWORK->effect[3].f20 = 7.5+(7.5*cos((M_PI*DS_STAGEWORK->effect[3].timer)/180.0));
            DS_STAGEWORK->effect[3].f24 = (250.0f*DS_STAGEWORK->effect[3].f20)/360.0f;
            mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
            mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
            if(DS_STAGEWORK->effect[3].timer >= 90) {
                DS_STAGEWORK->effect[3].mode++;
            }
            break;

        case 3:
            DS_STAGEWORK->effect[3].timer++;
            if(DS_STAGEWORK->effect[3].timer >= 180) {
                DS_STAGEWORK->effect[3].timer = 180;
            }
            DS_STAGEWORK->effect[3].f20 = 7.5-(7.5*cos((M_PI*DS_STAGEWORK->effect[3].timer)/180.0));
            DS_STAGEWORK->effect[3].f24 = (250.0f*DS_STAGEWORK->effect[3].f20)/360.0f;
            if(mdlA->pos.x < 1000.0f) {
                mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
                mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
            } else if(DS_STAGEWORK->effect[0].mode == 1) {
                DS_STAGEWORK->effect[3].mode = 0;
            }
            break;

        case 4:
            DS_STAGEWORK->effect[3].timer++;
            if(DS_STAGEWORK->effect[3].timer >= 20) {
                mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
                mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
                if(mdlA->pos.x >= DS_STAGEWORK->effect[3].f28) {
                    DS_STAGEWORK->effect[3].mode++;
                    DS_STAGEWORK->effect[3].timer = 0;
                }
            }
            break;

        case 5:
            DS_STAGEWORK->effect[3].timer++;
            DS_STAGEWORK->effect[3].f20 = 10.0*cos((M_PI*DS_STAGEWORK->effect[3].timer)/180.0);
            DS_STAGEWORK->effect[3].f24 = (250.0f*DS_STAGEWORK->effect[3].f20)/360.0f;
            mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
            mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
            if(DS_STAGEWORK->effect[3].timer == 90) {
                DS_STAGEWORK->effect[3].mode++;
                DS_STAGEWORK->effect[3].timer = 0;
            }
            break;

        case 6:
            if(DS_STAGEWORK->effect[0].mode == 2) {
                DS_STAGEWORK->effect[3].mode++;
            }
            break;

        case 7:
            DS_STAGEWORK->effect[3].timer++;
            if(DS_STAGEWORK->effect[3].timer >= 150) {
                DS_STAGEWORK->effect[3].timer = 150;
            }
            if(DS_STAGEWORK->effect[3].timer >= 60) {
                DS_STAGEWORK->effect[3].f20 = 10.0*sin((M_PI*(DS_STAGEWORK->effect[3].timer-60))/180.0);
                DS_STAGEWORK->effect[3].f24 = (250.0f*DS_STAGEWORK->effect[3].f20)/360.0f;
                if(mdlA->pos.x < 1000.0f) {
                    if(DS_STAGEWORK->effect[3].timer >= 70) {
                        mdlA->rot.z -= DS_STAGEWORK->effect[3].f20;
                    }
                    mdlA->pos.x += DS_STAGEWORK->effect[3].f24;
                } else if(DS_STAGEWORK->effect[0].mode == 1) {
                    DS_STAGEWORK->effect[3].mode = 0;
                    DS_STAGEWORK->effect[3].f20 = 0.0f;
                }
            }
            break;
    }
    mdlB->pos.x = mdlA->pos.x;
    mdlB->pos.y = mdlA->pos.y-40.0f;
    mdlB->pos.z = mdlA->pos.z;
}

#ifndef DS_PROPSLIDE_OWN
/*
 * PropSlide (m548 fn_1_8F78, m547 fn_1_B414), 107 instructions.
 * effect[4], model 7: once the arena reaches state 2
 * it slides from x=-2000 to x=2000 over 200 frames, then waits for state 1.
 *
 */
void DS_FN_PropSlide(void)
{
    DS_MODEL *mdl = &DS_STAGEWORK->models[DS_PROPMDL+7];

    switch(DS_STAGEWORK->effect[4].mode) {
        case 0:
            if(DS_STAGEWORK->effect[0].mode == 2) {
                DS_STAGEWORK->effect[4].mode++;
                DS_STAGEWORK->effect[4].timer = 0;
                Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            }
            break;

        case 1:
            DS_STAGEWORK->effect[4].timer++;
            mdl->pos.x = ((DS_STAGEWORK->effect[4].timer*4000)/200)-2000;
            if(DS_STAGEWORK->effect[4].timer == 200) {
                DS_STAGEWORK->effect[4].mode++;
            }
            break;

        case 2:
            if(DS_STAGEWORK->effect[0].mode == 1) {
                DS_STAGEWORK->effect[4].mode = 0;
            }
            break;
    }
}
#endif
#endif


/* ===== 5g. the head-D prop tail, second run: the first two updaters ===== */
#if defined(DS_S_PROPS_D) && !defined(DS_HAVE_PropOrbit)
#define DS_HAVE_PropOrbit
#if !defined(DS_PROPDMDL) || !defined(DS_FN_PropOrbit) || !defined(DS_FN_PropTurn)
#error "duelstage.h: DS_S_PROPS_D needs DS_PROPDMDL, DS_FN_PropOrbit and DS_FN_PropTurn"
#endif
/*
 * m553 fn_1_ECB8, m549 fn_1_12ED4 -- 238 instructions, sym-masked diff 4: the
 * nine-int model table only. Nine props parked at their own position and scale,
 * each bobbing on a sine. Three counters drive them: one advances the orbit a
 * thousandth of a degree every sixteen frames, one restarts the motion every
 * hundred, and one advances the bob a degree every four. Slots 0..8.
 */
void DS_FN_PropOrbit(void)
{
    int mdlNo[9] = {
        DS_PROPDMDL+0x00, DS_PROPDMDL+0x01, DS_PROPDMDL+0x02, DS_PROPDMDL+0x03,
        DS_PROPDMDL+0x04, DS_PROPDMDL+0x05, DS_PROPDMDL+0x06, DS_PROPDMDL+0x07,
        DS_PROPDMDL+0x1F
    };
    HuVecF pos[9] = {
        { -2300.0f, -1000.0f, -3200.0f },
        { 4500.0f, -900.0f, -7700.0f },
        { -4100.0f, -500.0f, -7700.0f },
        { 2300.0f, -1000.0f, -2800.0f },
        { 900.0f, -200.0f, -5700.0f },
        { -2400.0f, -1000.0f, -4700.0f },
        { 1600.0f, -700.0f, -3900.0f },
        { -1600.0f, -1000.0f, -5800.0f },
        { -100.0f, -1100.0f, -11200.0f }
    };
    float scale[9] = { 2.0f, 1.5f, 1.5f, 1.0f, 1.0f, 1.2f, 1.8f, 1.5f, 1.5f };
    DS_EFFECTD *eff;
    DS_MODEL *mdl;
    int i;
    int j;

    for(i=0; i<9; i++) {
        eff = &DS_STAGEWORK->effect[i];
        mdl = &DS_STAGEWORK->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            eff->timer[1] = 0;
            eff->timer[2] = 0;
            mdl->pos.x = pos[i].x;
            mdl->pos.z = pos[i].z;
            mdl->pos.y = pos[i].y;
            eff->f34 = i*40;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelScaleSet(mdl->modelId, scale[i], scale[i], scale[i]);
        }
        for(j=0; j<3; j++) {
            eff->timer[j]++;
            switch(j) {
                case 0:
                    if(eff->timer[j] >= 16) {
                        eff->timer[j] = 0;
                        eff->f2C += 0.001;
                    }
                    break;

                case 1:
                    if(eff->timer[j] >= 100) {
                        eff->timer[j] = 0;
                        Hu3DMotionTimeSet(mdl->modelId, 50.0f);
                    }
                    break;

                case 2:
                    if(eff->timer[j] >= 4) {
                        eff->timer[j] = 0;
                        eff->f34 += 1.0f;
                    }
                    break;
            }
        }
        mdl->pos.y = pos[i].y+(200.0*sin((M_PI*eff->f34)/180.0));
    }
}

/*
 * m553 fn_1_F070, m549 fn_1_1328C -- 136 instructions, sym-masked diff 4: the
 * four-int model table only. Four slowly turning props, each started once and
 * then wound back to 75 degrees whenever it passes -45. Model 0 of the table
 * turns with them, half as fast again. Slots 9..12.
 */
void DS_FN_PropTurn(void)
{
    int mdlNo[4] = { DS_PROPDMDL+0x0B, DS_PROPDMDL+0x0D, DS_PROPDMDL+0x0C, DS_PROPDMDL+0x0E };
    int i;
    DS_EFFECTD *eff;
    DS_MODEL *mdl;

    for(i=0; i<4; i++) {
        eff = &DS_STAGEWORK->effect[i+9];
        mdl = &DS_STAGEWORK->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            mdl->pos.x = 0.0f;
            mdl->pos.y = 0.0f;
            mdl->pos.z = 0.0f;
            mdl->rot.y = (i*30)-15;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, i*25);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
        }
        eff->timer[0]++;
        mdl->rot.y -= 0.01;
        if(mdl->rot.y <= -45.0f) {
            mdl->rot.y = 75.0f;
        }
    }
    mdl = DS_STAGEWORK->models;
    mdl->rot.y -= 0.005f;
}
#endif


/* ===== 6. an effect slot's stop ===== */
#if defined(DS_S_EFFECT9STOP) && !defined(DS_HAVE_Effect9Stop)
#define DS_HAVE_Effect9Stop
#if !defined(DS_FN_Effect9Stop) || !defined(DS_EFFECT9STOP_IDX)
#error "duelstage.h: DS_S_EFFECT9STOP needs DS_FN_Effect9Stop and DS_EFFECT9STOP_IDX"
#endif
/*
 * m550 fn_1_6D8C, m554 fn_1_7F68, m549 fn_1_134AC, m553 fn_1_F290 -- park one
 * slot by setting its first timer to -1. The slot index is NOT the same in all
 * four, and the store's offset is the only place it or the slot size shows.
 * CodeWarrior addresses &work->effect[i+K] as `mulli (i+K), <slot>` then
 * `addi <array base>`, so the base is readable off the object and the index is
 * (store - 4 - base) / slot: m550 (1064-4-0x178)/0x4C = 9, m554
 * (1412-4-0x364)/0x3C = 9, m549 and m553 (1448-4-0x1C8)/0x4C = 13. In m550
 * that slot is the arena light, whose updater hides the model on -1; in m549
 * and m553 it is the light DS_S_PROPS_D's PropLight drives.
 */
void DS_FN_Effect9Stop(void)
{
    DS_STAGEWORK->effect[DS_EFFECT9STOP_IDX].timer[0] = -1;
}
#endif


/* ===== 7. the head-D prop tail, third run: the four remaining updaters ===== */
/*
 * DS_S_PROPS_D covers nine functions and 1,766 instructions shared by m549 and
 * m553, but it needs two selectors: in both overlays the slot-13 store above
 * sits between the second and third updater, and one include emits in this
 * file's fixed order. So m553's tail is
 *
 *     DS_S_PROPS_D + DS_S_PROPEXEC   MatAlphaSet (5d), PropExec (5e),
 *                                    PropOrbit and PropTurn (5g)
 *     DS_S_EFFECT9STOP               the slot-13 store (6)
 *     DS_S_PROPS_D2                  PropLight .. PropSkyB (7)
 *
 * and m549's is the same. Every model number is one base apart (m553's is
 * m549's + 0x42: DS_PROPDMDL 0x66 against 0x24), and beyond that only the
 * PropExec count (6 against 5) and PropSkyA's two floats differ. The work
 * offsets are already equal, so DS_WORK carries them.
 */
#if defined(DS_S_PROPS_D2) && !defined(DS_HAVE_PropLight)
#define DS_HAVE_PropLight
#if !defined(DS_PROPDMDL) || !defined(DS_PROPD_SKYZ) || !defined(DS_PROPD_SKYY) \
    || !defined(DS_FN_MatAlphaSet) || !defined(DS_FN_PropLight) || !defined(DS_FN_PropBigOrbit) \
    || !defined(DS_FN_PropSkyAStop) || !defined(DS_FN_PropSkyA) || !defined(DS_FN_PropSkyBStop) || !defined(DS_FN_PropSkyB)
#error "duelstage.h: DS_S_PROPS_D2 needs DS_PROPDMDL, DS_PROPD_SKYZ, DS_PROPD_SKYY and DS_FN_MatAlphaSet, PropLight, PropBigOrbit, PropSkyAStop, PropSkyA, PropSkyBStop, PropSkyB"
#endif
/*
 * m553 fn_1_F2A8, m549 fn_1_134C4 -- 332 instructions, sym-masked diff 4: the
 * one-int model literal only. The light over the arena. It rocks through two
 * degrees on a 360-frame cycle and flickers: sixteen frames dimming to 0.6,
 * then a randomised 64-123 frame hold at full, and every third and sixth time
 * round a six-frame drop instead. The alpha goes into the model's materials
 * through MatAlphaSet, which CodeWarrior inlines at all four call sites --
 * which is why this is 332 instructions against m550's 254. Slot 13.
 */
void DS_FN_PropLight(void)
{
    int mdlNo[1] = { DS_PROPDMDL+0x0F };
    DS_EFFECTD *eff = &DS_STAGEWORK->effect[13];
    DS_MODEL *mdl = &DS_STAGEWORK->models[mdlNo[0]];

    if(eff->timer[0] < -1) {
        return;
    }
    if(eff->timer[0] == -1) {
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        eff->timer[0]--;
        return;
    }
    if(eff->mode == 0) {
        eff->mode = 1;
        eff->timer[0] = 0;
        eff->timer[1] = 0;
        eff->timer[2] = 0;
        eff->counter = 0;
        eff->subMode = 0;
        mdl->pos.x = -1100.0f;
        mdl->pos.y = 1150.0f;
        mdl->pos.z = -800.0f;
        mdl->rot.x = 0.0f;
        mdl->rot.z = 0.0f;
        Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        eff->f2C = 1.0f;
        DS_FN_MatAlphaSet(mdl->modelId, eff->f2C);
        return;
    }
    eff->timer[0] = (eff->timer[0]+1)%360;
    mdl->rot.z = 2.0*sin((M_PI*eff->timer[0])/180.0);
    switch(eff->subMode) {
        case 0:
            eff->timer[1]++;
            eff->f2C = 1.0-(0.4*sin((M_PI*((eff->timer[1]*90)/16))/180.0));
            DS_FN_MatAlphaSet(mdl->modelId, eff->f2C);
            if(eff->timer[1] == 16) {
                eff->timer[1] = 0;
                eff->timer[2] = (rand8()%60)+64;
                eff->subMode++;
            }
            break;

        case 1:
            if(eff->timer[1]++ >= eff->timer[2]) {
                DS_FN_MatAlphaSet(mdl->modelId, 1.0f);
                eff->counter = (eff->counter+1)%6;
                if(eff->counter == 1 || eff->counter == 4) {
                    eff->subMode = 0;
                } else {
                    eff->subMode++;
                }
                eff->timer[1] = 0;
            }
            break;

        case 2:
            if(eff->timer[1]++ >= 6) {
                DS_FN_MatAlphaSet(mdl->modelId, 0.6f);
                eff->subMode = 0;
                eff->timer[1] = 0;
            }
            break;
    }
}

/*
 * m553 fn_1_F7D8, m549 fn_1_139F4 -- 678 instructions, sym-masked diff 4: the
 * six-int model table only. Five more orbiting props. Four of them circle a
 * fixed centre; the first swings round the arena, and once it passes 180
 * degrees it hands over to an arc: the code records where it was and what
 * heading it had, then walks it round a 600-unit circle at 1.5 degrees a frame
 * for 240 frames before returning it to the orbit at a tenth of its old speed.
 * Ten trailing models follow it, one released every fifteen frames from a ring
 * buffer. Slots 14..18.
 *
 * Retail divides: `(3.0f*f34)/4.0f` is raw-identical and `*0.25f` is not, even
 * though CodeWarrior folds the divide to the same 0.25f literal -- it schedules
 * the constant loads around the multiplies instead of hoisting them. m550's
 * equivalent line really is `*0.25f`, so the two overlays' sources differ here.
 */
void DS_FN_PropBigOrbit(void)
{
    int mdlNo[6] = {
        DS_PROPDMDL+0x10, DS_PROPDMDL+0x1B, DS_PROPDMDL+0x1D,
        DS_PROPDMDL+0x1C, DS_PROPDMDL+0x1E, DS_PROPDMDL+0x11
    };
    float radius[5] = { 3000.0f, 700.0f, 700.0f, 500.0f, 500.0f };
    float angle[5] = { 90.0f, 180.0f, 0.0f, 90.0f, 270.0f };
    float speed[5] = { 0.3f, 0.5f, 0.5f, 0.5f, 0.5f };
    HuVecF pos[2] = { { 1600.0f, -300.0f, -3900.0f }, { -1600.0f, -600.0f, -5800.0f } };
    DS_EFFECTD *eff;
    DS_MODEL *mdl;
    DS_MODEL *sub;
    int i;

    for(i=0; i<5; i++) {
        eff = &DS_STAGEWORK->effect[i+14];
        mdl = &DS_STAGEWORK->models[mdlNo[i]];
        if(eff->mode == 0) {
            eff->mode = 1;
            eff->timer[0] = 0;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            if(i == 0) {
                Hu3DMotionSpeedSet(mdl->modelId, 2.0f);
            } else {
                Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            if(i >= 3) {
                Hu3DModelScaleSet(mdl->modelId, 2.0f, 2.0f, 2.0f);
            }
            eff->f2C = radius[i];
            eff->f30 = angle[i];
            eff->f34 = speed[i];
        }
        eff->f30 += eff->f34;
        if(i == 0) {
            if(eff->f30 > 270.0f) {
                eff->f30 = 0.0f;
                eff->doneF = 0;
            }
            if(eff->f30 > 0.0f && eff->f30 <= 90.0f) {
                eff->f30 -= (3.0f*eff->f34)/4.0f;
            }
        }
        if(eff->f34 >= 0.0f) {
            mdl->rot.y = 90.0f+eff->f30;
        } else {
            mdl->rot.y = 270.0f+eff->f30;
        }
        switch(i) {
            case 0:
                if(eff->subMode == 0) {
                    mdl->pos.x = eff->f2C*sin((M_PI*eff->f30)/180.0);
                    mdl->pos.z = eff->f2C*cos((M_PI*eff->f30)/180.0);
                    mdl->pos.y = -200.0+((5000.0*sin((M_PI*15.0)/180.0))*sin((M_PI*(180.0f+eff->f30))/180.0));
                    mdl->rot.x = 15.0*sin((M_PI*(90.0f+eff->f30))/180.0);
                    if(eff->doneF == 0 && eff->f30 > 180.0f) {
                        eff->subMode++;
                        eff->f3C = mdl->pos.x+(600.0*cos((M_PI*(90.0f+mdl->rot.x))/180.0));
                        eff->f40 = mdl->pos.y+(600.0*sin((M_PI*(90.0f+mdl->rot.x))/180.0));
                        eff->f44 = (90.0f+mdl->rot.x)-180.0f;
                        eff->counter = 0;
                        eff->f34 = 0.0f;
                        eff->doneF = 1;
                    }
                } else {
                    eff->f44 -= 1.5;
                    mdl->rot.x -= 1.5;
                    mdl->pos.x = eff->f3C+(600.0*cos((M_PI*eff->f44)/180.0));
                    mdl->pos.y = eff->f40+(600.0*sin((M_PI*eff->f44)/180.0));
                    if(eff->counter++ >= 239) {
                        eff->f34 = 0.3f;
                        eff->subMode = 0;
                    }
                }
                eff->timer[0]++;
                if(eff->timer[0] >= 15) {
                    eff->timer[0] = 0;
                    sub = &DS_STAGEWORK->models[mdlNo[5]+eff->timer[1]];
                    Hu3DModelAttrReset(sub->modelId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(sub->modelId, 0.0f);
                    Hu3DMotionSpeedSet(sub->modelId, 1.0f);
                    if(eff->subMode == 0) {
                        sub->pos.x = eff->f2C*sin((M_PI*(eff->f30-eff->f34))/180.0);
                        sub->pos.z = eff->f2C*cos((M_PI*(eff->f30-eff->f34))/180.0);
                        sub->pos.y = -200.0+((5000.0*sin((M_PI*15.0)/180.0))*sin((M_PI*(180.0f+(eff->f30-eff->f34)))/180.0));
                    } else {
                        sub->pos.x = eff->f3C+(600.0*cos((M_PI*(1.5f+eff->f44))/180.0));
                        sub->pos.y = eff->f40+(600.0*sin((M_PI*(1.5f+eff->f44))/180.0));
                        sub->pos.z = mdl->pos.z;
                    }
                    Hu3DModelPosSetV(sub->modelId, &sub->pos);
                    eff->timer[1] = (eff->timer[1]+1)%10;
                }
                break;

            case 1:
            case 2:
                mdl->pos.x = pos[0].x+(eff->f2C*sin((M_PI*eff->f30)/180.0));
                mdl->pos.z = pos[0].z+(eff->f2C*cos((M_PI*eff->f30)/180.0));
                mdl->pos.y = pos[0].y;
                break;

            case 3:
            case 4:
                mdl->pos.x = pos[1].x+(eff->f2C*sin((M_PI*eff->f30)/180.0));
                mdl->pos.z = pos[1].z+(eff->f2C*cos((M_PI*eff->f30)/180.0));
                mdl->pos.y = pos[1].y;
                break;
        }
    }
}

/* m553 fn_1_10270, m549 fn_1_1448C -- 19 instructions; the model only. */
void DS_FN_PropSkyAStop(void)
{
    DS_STAGEWORK->effect[19].timer[0] = -1;
    Hu3DModelAttrSet(DS_STAGEWORK->models[DS_PROPDMDL+0x09].modelId, HU3D_ATTR_DISPOFF);
}

/*
 * m553 fn_1_102BC, m549 fn_1_144D8 -- 146 instructions, sym-masked diff 14: the
 * model, and the only two floats in the whole tail that differ (m553 2500.0f
 * and 300.0f, m549 2800.0f and 800.0f). One prop that crosses the sky. It waits
 * 800 frames, appears at the far left, drifts right at 5 a frame with its
 * motion looping by hand from frame 51, and once past 4000 waits a randomised
 * 600-720 frames before coming round again. PropSkyAStop parks it. Slot 19.
 */
void DS_FN_PropSkyA(void)
{
    int mdlNo[1] = { DS_PROPDMDL+0x09 };
    DS_EFFECTD *prop = &DS_STAGEWORK->effect[19];
    DS_MODEL *mdl = &DS_STAGEWORK->models[DS_PROPDMDL+0x09];

    if(prop->timer[0] < -1) {
        return;
    }
    if(prop->timer[0] == -1) {
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        prop->timer[0]--;
    }
    if(prop->mode == 0) {
        if(prop->timer[0]++ > 800) {
            prop->mode = 1;
            prop->timer[0] = 0;
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(mdl->modelId, 50.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.5f);
            Hu3DModelScaleSet(mdl->modelId, 2.0f, 2.0f, 2.0f);
            mdl->pos.x = -2000.0f;
            mdl->pos.z = DS_PROPD_SKYZ;
            mdl->pos.y = DS_PROPD_SKYY;
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        }
    }
    if(prop->mode == 1) {
        prop->timer[0]++;
        if(prop->timer[0] >= 99) {
            Hu3DMotionTimeSet(mdl->modelId, 51.0f);
            prop->timer[0] = 0;
        }
        mdl->pos.x += 5.0f;
        if(mdl->pos.x > 4000.0f) {
            prop->mode = 2;
            prop->timer[0] = 0;
            prop->timer[1] = ((rand8()%5)*30)+600;
        }
    }
    if(prop->mode == 2) {
        if(prop->timer[0]++ >= prop->timer[1]) {
            mdl->pos.x = -2000.0f;
            prop->mode = 1;
        }
    }
}

/* m553 fn_1_10504, m549 fn_1_14720 -- 19 instructions; the model only. */
void DS_FN_PropSkyBStop(void)
{
    Hu3DModelAttrSet(DS_STAGEWORK->models[DS_PROPDMDL+0x0A].modelId, HU3D_ATTR_DISPOFF);
    DS_STAGEWORK->effect[20].mode = -1;
}

/*
 * m553 fn_1_10550, m549 fn_1_1476C -- 172 instructions, sym-masked diff 4: the
 * one-int model literal only. The other sky prop, on a fixed 22.5-degree
 * heading at 14.85 a frame. It starts 13000 units out, crosses to z = 2000,
 * then waits a randomised 300-510 frames and comes back in at one of four x
 * positions. PropSkyBStop parks it by setting the mode to -1. Slot 20.
 */
void DS_FN_PropSkyB(void)
{
    int mdlNo[1] = { DS_PROPDMDL+0x0A };
    DS_EFFECTD *prop = &DS_STAGEWORK->effect[20];
    DS_MODEL *mdl = &DS_STAGEWORK->models[mdlNo[0]];

    if(prop->mode < 0) {
        return;
    }
    switch(prop->mode) {
        case 0:
            if(prop->timer[0]++ > 300) {
                prop->timer[0] = -200;
                prop->mode = 1;
                Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                Hu3DMotionSpeedSet(mdl->modelId, 0.25f);
                mdl->pos.x = -4356.0f;
                mdl->pos.z = -13000.0f;
                mdl->pos.y = 0.0f;
                Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            }
            break;

        case 1:
            prop->timer[0]++;
            if(prop->timer[0] >= 200) {
                prop->timer[0] = 0;
                Hu3DMotionTimeSet(mdl->modelId, 51.0f);
            }
            mdl->pos.x += 14.85*sin((M_PI*22.5)/180.0);
            mdl->pos.z += 14.85*cos((M_PI*22.5)/180.0);
            if(mdl->pos.z >= 2000.0f) {
                prop->mode = 2;
                prop->timer[0] = 0;
                prop->timer[1] = ((rand8()%8)*30)+300;
            }
            break;

        case 2:
            if(prop->timer[0]++ >= prop->timer[1]) {
                prop->mode = 1;
                Hu3DMotionTimeSet(mdl->modelId, 0.0f);
                mdl->pos.x = ((rand8()%4)*500)-4356;
                mdl->pos.z = -13000.0f;
                prop->timer[0] = -200;
            }
            break;
    }
}
#endif


/* Section selectors are per-include; clear them on the way out. */
#undef DS_S_WORKINIT
#undef DS_S_CHARMOT
#undef DS_S_CHARMOT_IDX
#undef DS_S_PADREAD
#undef DS_S_PADREAD_262
#undef DS_S_CHARMOTION
#undef DS_S_MOTIONEXEC
#undef DS_S_MOTIONEXEC_B
#undef DS_S_MOTIONEXEC_C
#undef DS_S_PROPS_B
#undef DS_S_PROPEXEC
#undef DS_S_PROPS_D
#undef DS_S_PROPS_D2
#undef DS_S_EFFECT9STOP
