/*
 * m576dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m576Dll/asm/REL/m576Dll/score.s.
 */

#include "REL/m576dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "game/mg/score.h"
#include "datanum/mgconst.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 14.0f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = -21.0f; */
/* 0x200 */ /* float lbl_1_rodata_200 = 0.0f; */
/* 0x208 */ /* double lbl_1_rodata_208 = 0.1; */
/* 0x210 */ /* double lbl_1_rodata_210 = 1; */
/* 0x218 */ /* double lbl_1_rodata_218 = 0.7; */

/* --- .data --- */
/* 0x538 */ M576_SCOREPOS lbl_1_data_538[4] = {
    {  55.0f, 59.0f },
    { 175.0f, 59.0f },
    { 401.0f, 59.0f },
    { 521.0f, 59.0f },
};
/* 0x558 */ s32 lbl_1_data_558[15] = { 0x00830011, 0x00830012, 0x00830013, 0x00830014, 0x00830015, 0x00830016, 0x00830017, 0x00830018, 0x00830019, 0x0083001A, 0x0083001B, 0x0083001C, 0x0083001D, 0x0083001A, 0x0083001A };

/* --- .bss --- */
/* 0x470 */ OMOBJ *lbl_1_bss_470;

/* --- functions (reference order) ---
 * m503's score.c with three differences: no wrapper process (fn_1_EA90 builds and
 * then installs fn_1_ECC4 itself), a one-digit score at x+14 created with FALSE, and
 * no wait on the game's start state before the fade-in. */

/* fn_1_EA08, 34 insns. Called from m576.c. */
void fn_1_EA08(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M576_SCORE *work;

    obj = omAddObjEx(objman, 20, 0, 0, -1, fn_1_EA90);
    lbl_1_bss_470 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M576_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M576_SCORE));
}

/* fn_1_EA90, 141 insns. Builds the four score readouts, then runs fn_1_ECC4. */
void fn_1_EA90(OMOBJ *obj)
{
    s32 i;
    M576_SCORE *work;
    s32 j;
    HUSPRGRPID grpId;
    MGSCORE *score;
    HUSPRGRPID winId;
    ANIMDATA *charAnim;

    work = obj->data;

    for (i = 0; i < 4; i++) {
        winId = MgScoreWinCreate(80, 40);
        work->unk008[i].unk004 = winId;
        MgScoreWinPosSet(winId, lbl_1_data_538[i].unk000, lbl_1_data_538[i].unk004);
        MgScoreWinDispSet(winId, FALSE);
        score = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, FALSE);
        work->unk008[i].unk008 = score;
        MgScoreMaxDigitSet(score, 1);
        MgScoreDispOff(score);
        MgScorePosSet(score, 14.0f + lbl_1_data_538[i].unk000, lbl_1_data_538[i].unk004);
        MgScoreColorSet(score, 255, 216, 21);
        charAnim = HuSprAnimDataRead(lbl_1_data_558[GwPlayerConf[i].charNo]);
        grpId = HuSprGrpCreate(1);
        work->unk008[i].unk006 = grpId;
        HuSprGrpPosSet(grpId, lbl_1_data_538[i].unk000, lbl_1_data_538[i].unk004);
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(charAnim, 0, 0));
        HuSprPosSet(grpId, 0, -21.0f, 0.0f);
        for (j = 0; j < 1; j++) {
            HuSprAttrSet(grpId, j, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grpId, j, HUSPR_ATTR_DISPOFF);
        }
    }
    obj->objFunc = fn_1_ECC4;
}

/* fn_1_ECC4, 127 insns. Fade-in, then the digits. */
void fn_1_ECC4(OMOBJ *obj)
{
    M576_SCORE *work = obj->data;
    s32 value;
    HUSPRGRPID grpId;
    MGSCORE *score;
    HUSPRGRPID winId;
    s32 i;
    s32 j;

    switch (work->unk000) {
        case 0:
            work->unk000++;
            work->unk004 = 0.0f;
            for (i = 0; i < 4; i++) {
                winId = work->unk008[i].unk004;
                MgScoreWinDispSet(winId, TRUE);
                score = work->unk008[i].unk008;
                MgScoreDispOn(score);
                grpId = work->unk008[i].unk006;
                for (j = 0; j < 1; j++) {
                    HuSprAttrReset(grpId, j, HUSPR_ATTR_DISPOFF);
                }
            }
        case 1:
            if ((work->unk004 += 0.1) >= 1.0) {
                work->unk000++;
            }
            for (i = 0; i < 4; i++) {
                winId = work->unk008[i].unk004;
                MgScoreWinTPLvlSet(winId, 0.7 * work->unk004);
                score = work->unk008[i].unk008;
                MgScoreTPLvlSet(score, work->unk004);
                grpId = work->unk008[i].unk006;
                for (j = 0; j < 1; j++) {
                    HuSprTPLvlSet(grpId, j, work->unk004);
                }
            }
            break;
        case 2:
            break;
    }
    for (i = 0; i < 4; i++) {
        grpId = work->unk008[i].unk006;
        value = work->unk008[i].unk000;
        if (value > 99) {
            value = 99;
        }
        score = work->unk008[i].unk008;
        MgScoreValueSet(score, value);
    }
}

/* fn_1_EEC0, 14 insns. One more point for player `no`. */
void fn_1_EEC0(s32 no)
{
    M576_SCORE *work = lbl_1_bss_470->data;

    work->unk008[no].unk000++;
}

/* fn_1_EEF8, 14 insns. One point fewer for player `no`. */
void fn_1_EEF8(s32 no)
{
    M576_SCORE *work = lbl_1_bss_470->data;

    work->unk008[no].unk000--;
}
