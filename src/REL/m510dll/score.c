/*
 * m510dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/score.s.
 */

#include "REL/m510dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "game/mg/score.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "datanum/mgconst.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x410 */ /* float lbl_1_rodata_410 = 14.0f; */
/* 0x414 */ /* float lbl_1_rodata_414 = -32.0f; */
/* 0x418 */ /* float lbl_1_rodata_418 = -8.0f; */
/* 0x41C */ /* float lbl_1_rodata_41C = 0.7f; */
/* 0x420 */ /* float lbl_1_rodata_420 = 524.0f; */
/* 0x424 */ /* float lbl_1_rodata_424 = 60.0f; */
/* 0x428 */ /* float lbl_1_rodata_428 = 505.0f; */
/* 0x42C */ /* float lbl_1_rodata_42C = 526.0f; */
/* 0x430 */ /* float lbl_1_rodata_430 = 1.0f; */
/* 0x434 */ /* float lbl_1_rodata_434 = 288.0f; */
/* 0x438 */ /* float lbl_1_rodata_438 = 64.0f; */
/* 0x43C */ /* float lbl_1_rodata_43C = 278.0f; */
/* 0x440 */ /* float lbl_1_rodata_440 = 0.02f; */
/* 0x444 */ /* float lbl_1_rodata_444 = 1.2f; */
/* 0x448 */ /* float lbl_1_rodata_448 = 0.04f; */

/* --- .data --- */
/* 0x4D8 */ HuVecF lbl_1_data_4D8[4] = {
    { 72.0f, 420.0f, 0.0f },
    { 216.0f, 420.0f, 0.0f },
    { 360.0f, 420.0f, 0.0f },
    { 504.0f, 420.0f, 0.0f },
};

/* --- functions (reference order) --- */
/* fn_1_CE04, score.c, 234 insns. Creates the score display for one layout mode. */
void fn_1_CE04(M510_SCORE *score, u16 mode, s16 idx)
{
    HuVecF pos;
    s16 id;
    MGSCORE *mgScore;

    memset(score, 0, sizeof(M510_SCORE));
    score->unk004 = mode;
    score->unk024 = 0;
    score->unk006 = idx;
    if (mode == 0) {
        score->unk008 = MgScoreWinCreate(112, 40);
        MgScoreWinDispSet(score->unk008, FALSE);
        mgScore = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
        score->unk00C = mgScore;
        MgScoreMaxDigitSet(mgScore, 2);
        MgScoreValueSet(mgScore, 0);
        MgScoreDispOff(mgScore);
        score->unk010 = id = espEntry(DATANUM(DATA_m510, 0x33), 0, 0);
        espDrawNoSet(id, 0);
        espDispOff(id);
        score->unk012 = id = espEntry(MGCONST_ANM_scoreCross, 0, 0);
        espDrawNoSet(id, 0);
        espDispOff(id);
        pos = lbl_1_data_4D8[idx];
        MgScoreWinPosSet(score->unk008, pos.x, pos.y);
        MgScorePosSet(mgScore, 14.0f + pos.x, pos.y);
        espPosSet(score->unk010, -32.0f + pos.x, pos.y);
        espPosSet(score->unk012, -8.0f + pos.x, pos.y);
    } else if (mode == 1) {
        score->unk008 = id = MgScoreWinCreate(72, 40);
        MgScoreWinTPLvlSet(id, 0.7f);
        MgScoreWinPosSet(id, 524.0f, 60.0f);
        MgScoreWinDispSet(score->unk008, FALSE);
        score->unk014 = id = espEntry(MGCONST_ANM_crown, 0, 0);
        espDrawNoSet(id, 0);
        espPosSet(id, 505.0f, 60.0f);
        espDispOff(id);
        mgScore = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, TRUE);
        score->unk00C = mgScore;
        MgScoreValueSet(mgScore, 0);
        MgScorePosSet(mgScore, 526.0f, 60.0f);
        MgScoreMaxDigitSet(mgScore, 2);
        MgScoreColorSet(mgScore, 66, 255, 122);
        MgScoreDispOff(mgScore);
        score->unk020 = 0;
        score->unk018 = 1.0f;
    } else {
        score->unk008 = id = MgScoreWinCreate(64, 48);
        MgScoreWinTPLvlSet(id, 0.7f);
        MgScoreWinPosSet(id, 288.0f, 64.0f);
        MgScoreWinDispSet(score->unk008, FALSE);
        mgScore = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
        score->unk00C = mgScore;
        MgScoreValueSet(mgScore, 0);
        MgScorePosSet(mgScore, 278.0f, 64.0f);
        MgScoreMaxDigitSet(mgScore, 2);
        MgScoreDispOff(mgScore);
    }
}

/* fn_1_D1AC, score.c, 34 insns. Kills the score display. */
void fn_1_D1AC(M510_SCORE *score)
{
    if (score->unk004 == 0) {
        espKill(score->unk012);
        espKill(score->unk010);
        MgScoreKill(score->unk00C);
    } else if (score->unk004 == 1) {
        espKill(score->unk014);
        MgScoreKill(score->unk00C);
    } else {
        MgScoreKill(score->unk00C);
    }
    memset(score, 0, sizeof(M510_SCORE));
}

/* fn_1_D234, score.c, 72 insns. Per-frame: value and the record pulse. */
void fn_1_D234(M510_SCORE *score)
{
    MgScoreValueSet(score->unk00C, score->unk024);
    if (score->unk020 != 0 && score->unk004 == 1) {
        if (score->unk01C == 0) {
            if ((score->unk018 += 0.02f) >= 1.2f) {
                score->unk018 = 1.2f;
                score->unk01C = 1;
            }
        } else {
            if ((score->unk018 -= 0.04f) <= 1.0f) {
                score->unk018 = 1.0f;
                score->unk01C = 0;
            }
        }
    } else {
        score->unk018 = 1.0f;
    }
    MgScoreDigitScaleSet(score->unk00C, score->unk018, score->unk018);
    espScaleSet(score->unk014, score->unk018, score->unk018);
}

/* fn_1_D354, score.c, 72 insns. Shows or hides the score display. */
void fn_1_D354(M510_SCORE *score, s32 disp)
{
    if (score->unk004 == 0) {
        if (disp) {
            MgScoreWinDispSet(score->unk008, TRUE);
            MgScoreDispOn(score->unk00C);
            espDispOn(score->unk010);
            espDispOn(score->unk012);
        } else {
            MgScoreWinDispSet(score->unk008, FALSE);
            MgScoreDispOff(score->unk00C);
            espDispOff(score->unk010);
            espDispOff(score->unk012);
        }
    } else if (score->unk004 == 1) {
        if (disp) {
            MgScoreWinDispSet(score->unk008, TRUE);
            MgScoreDispOn(score->unk00C);
            espDispOn(score->unk014);
        } else {
            MgScoreWinDispSet(score->unk008, FALSE);
            MgScoreDispOff(score->unk00C);
            espDispOff(score->unk014);
        }
    } else {
        if (disp) {
            MgScoreWinDispSet(score->unk008, TRUE);
            MgScoreDispOn(score->unk00C);
        } else {
            MgScoreWinDispSet(score->unk008, FALSE);
            MgScoreDispOff(score->unk00C);
        }
    }
}
