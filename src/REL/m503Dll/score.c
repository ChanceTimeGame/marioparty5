/*
 * m503dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/score.s.
 */

#include "REL/m503dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "datanum/mgconst.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x640 */ /* float lbl_1_rodata_640 = 3.0f; */
/* 0x644 */ /* float lbl_1_rodata_644 = -21.0f; */
/* 0x648 */ /* float lbl_1_rodata_648 = 0.0f; */
/* 0x650 */ /* double lbl_1_rodata_650 = 0.1; */
/* 0x658 */ /* double lbl_1_rodata_658 = 1; */
/* 0x660 */ /* double lbl_1_rodata_660 = 0.7; */

/* --- .data --- */
/* 0x640 */ M503_SCOREPOS lbl_1_data_640[4] = {
    {  55.0f, 59.0f },
    { 175.0f, 59.0f },
    { 401.0f, 59.0f },
    { 521.0f, 59.0f },
};
/* 0x660 */ s32 lbl_1_data_660[15] = {
    MGCONST_ANM_marioSmall, MGCONST_ANM_luigiSmall, MGCONST_ANM_peachSmall,
    MGCONST_ANM_yoshiSmall, MGCONST_ANM_warioSmall, MGCONST_ANM_daisySmall,
    MGCONST_ANM_waluigiSmall, MGCONST_ANM_kinopioSmall, MGCONST_ANM_teresaSmall,
    MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaRSmall, MGCONST_ANM_minikoopaGSmall,
    MGCONST_ANM_minikoopaBSmall, MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaSmall,
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xCC gap_05_000000CC_bss (0x4) -- dtk filler */
/* 0xC8 */ OMOBJ *lbl_1_bss_C8;

/* --- functions (reference order) --- */
/* fn_1_D1B4, score.c, 34 insns. Called from ObjectSetup. */
void fn_1_D1B4(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M503_SCORE *work;

    obj = omAddObjEx(objman, 80, 0, 0, -1, fn_1_D240);
    lbl_1_bss_C8 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M503_SCORE));
}

/* fn_1_D23C, score.c, 1 insn. Close hook, empty. */
void fn_1_D23C(void)
{
}

/* 15 insns */
void fn_1_D240(OMOBJ *obj)
{
    fn_1_D2A4(obj);
    obj->objFunc = fn_1_D27C;
}

/* 10 insns */
void fn_1_D27C(OMOBJ *obj)
{
    fn_1_D4CC(obj);
}

/* fn_1_D2A4, score.c, 138 insns. Builds the four score readouts. */
void fn_1_D2A4(OMOBJ *obj)
{
    s32 i;
    M503_SCORE *work;
    HUSPRGRPID grpId;
    s32 j;
    MGSCORE *score;
    HUSPRGRPID winId;
    ANIMDATA *charAnim;

    work = obj->data;

    for (i = 0; i < 4; i++) {
        winId = MgScoreWinCreate(80, 40);
        work->unk008[i].unk004 = winId;
        MgScoreWinPosSet(winId, lbl_1_data_640[i].unk000, lbl_1_data_640[i].unk004);
        MgScoreWinDispSet(winId, FALSE);
        score = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
        work->unk008[i].unk008 = score;
        MgScoreMaxDigitSet(score, 2);
        MgScoreDispOff(score);
        MgScorePosSet(score, 3.0f + lbl_1_data_640[i].unk000, lbl_1_data_640[i].unk004);
        MgScoreColorSet(score, 255, 216, 21);
        charAnim = HuSprAnimDataRead(lbl_1_data_660[GwPlayerConf[i].charNo]);
        grpId = HuSprGrpCreate(1);
        work->unk008[i].unk006 = grpId;
        HuSprGrpPosSet(grpId, lbl_1_data_640[i].unk000, lbl_1_data_640[i].unk004);
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(charAnim, 50, 0));
        HuSprPosSet(grpId, 0, -21.0f, 0.0f);
        for (j = 0; j < 1; j++) {
            HuSprAttrSet(grpId, j, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grpId, j, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* fn_1_D4CC, score.c, 130 insns. Fade-in, then the digits. */
void fn_1_D4CC(OMOBJ *obj)
{
    M503_SCORE *work = obj->data;
    s32 value;
    HUSPRGRPID grpId;
    MGSCORE *score;
    HUSPRGRPID winId;
    s32 i;
    s32 j;

    switch (work->unk000) {
        case 0:
            if (fn_1_1AE0() != 2) {
                break;
            }
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

/* fn_1_D6D4, score.c, 41 insns. Add to one player's score; 1 point and more play different SE. */
void fn_1_D6D4(s32 no, s32 add)
{
    M503_SCORE *work = lbl_1_bss_C8->data;

    work->unk008[no].unk000 += add;
    if (add == 1) {
        fn_1_2260(0x640, lbl_1_data_640[no].unk000);
    } else {
        fn_1_2260(0x644, lbl_1_data_640[no].unk000);
    }
}

/* 14 insns */
s32 fn_1_D778(s32 no)
{
    OMOBJ *obj = lbl_1_bss_C8;
    M503_SCORE *work = obj->data;

    return work->unk008[no].unk000;
}

