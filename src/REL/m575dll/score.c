/*
 * m575dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/score.s.
 */

#include "REL/m575dll.h"

#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xC8 */ /* float lbl_1_rodata_C8 = 70.0f; */
/* 0xCC */ /* float lbl_1_rodata_CC = 60.0f; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 84.0f; */
/* 0xD4 */ /* float lbl_1_rodata_D4 = 38.0f; */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 62.0f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 502.0f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 516.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 470.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8[2] = { 494.0f, 0.0f }; */

/* --- functions (reference order) --- */
void fn_1_3A7C(M575_SCORE *score, u16 side, M575_TEAM *team)
{
    MGSCORE *mgScore;
    s16 espId;

    memset(score, 0, sizeof(M575_SCORE));
    score->unk000 = team;
    score->unk004 = side;
    score->unk010 = 0;
    score->unk006 = MgScoreWinCreate(112, 40);
    MgScoreWinDispSet(score->unk006, FALSE);
    score->unk008 = mgScore = MgScoreCreate(0x960031, -1, TRUE);
    MgScoreMaxDigitSet(mgScore, 2);
    MgScoreValueSet(mgScore, 0);
    MgScoreDispOff(mgScore);
    score->unk00C = espId = espEntry(0x820019, 0, 0);
    espDrawNoSet(espId, 0);
    espDispOff(espId);
    score->unk00E = espId = espEntry(0x960046, 0, 0);
    espDrawNoSet(espId, 0);
    espDispOff(espId);
    if (side == 0) {
        MgScoreWinPosSet(score->unk006, 70.0f, 60.0f);
        MgScoreWinColorSet(score->unk006, 250, 0, 30);
        MgScorePosSet(mgScore, 84.0f, 60.0f);
        espPosSet(score->unk00C, 38.0f, 60.0f);
        espPosSet(score->unk00E, 62.0f, 60.0f);
    } else {
        MgScoreWinPosSet(score->unk006, 502.0f, 60.0f);
        MgScoreWinColorSet(score->unk006, 0, 50, 250);
        MgScorePosSet(mgScore, 516.0f, 60.0f);
        espPosSet(score->unk00C, 470.0f, 60.0f);
        espPosSet(score->unk00E, 494.0f, 60.0f);
    }
}

void fn_1_3CD8(M575_SCORE *score)
{
    espKill(score->unk00E);
    espKill(score->unk00C);
    MgScoreKill(score->unk008);
    memset(score, 0, sizeof(M575_SCORE));
}

void fn_1_3D28(M575_SCORE *score)
{
    MgScoreValueSet(score->unk008, score->unk010);
}

void fn_1_3D5C(M575_SCORE *score, s32 disp)
{
    if (disp) {
        MgScoreWinDispSet(score->unk006, TRUE);
        MgScoreDispOn(score->unk008);
        espDispOn(score->unk00C);
        espDispOn(score->unk00E);
    } else {
        MgScoreWinDispSet(score->unk006, FALSE);
        MgScoreDispOff(score->unk008);
        espDispOff(score->unk00C);
        espDispOff(score->unk00E);
    }
}
