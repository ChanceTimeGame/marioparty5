/*
 * m516dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m516Dll/asm/REL/m516Dll/score.s.
 */

#include "REL/m516Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "datanum/mgconst.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x530 */ /* float lbl_1_rodata_530 = 22.0f; */
/* 0x534 */ /* float lbl_1_rodata_534 = -38.0f; */
/* 0x538 */ /* float lbl_1_rodata_538 = 0.0f; */
/* 0x53C */ /* float lbl_1_rodata_53C = -15.0f; */
/* 0x540 */ /* float lbl_1_rodata_540 = 4.0f; */
/* 0x548 */ /* double lbl_1_rodata_548 = 0.1; */

/* --- .data --- */
/* 0x2C0 */ M516_SCOREPOS lbl_1_data_2C0[4] = {
    {  71.0f, 59.0f },
    { 191.0f, 59.0f },
    { 385.0f, 59.0f },
    { 505.0f, 59.0f },
};
/* 0x2E0 */ s32 lbl_1_data_2E0[15] = {
    MGCONST_ANM_marioSmall, MGCONST_ANM_luigiSmall, MGCONST_ANM_peachSmall,
    MGCONST_ANM_yoshiSmall, MGCONST_ANM_warioSmall, MGCONST_ANM_daisySmall,
    MGCONST_ANM_waluigiSmall, MGCONST_ANM_kinopioSmall, MGCONST_ANM_teresaSmall,
    MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaRSmall, MGCONST_ANM_minikoopaGSmall,
    MGCONST_ANM_minikoopaBSmall, MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaSmall,
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x4C gap_05_0000004C_bss (0x4) -- dtk filler */
/* 0x48 */ OMOBJ *lbl_1_bss_48;

/* --- functions (reference order) --- */

/* fn_1_79F8, score.c, 34 insns. Called from ObjectSetup. */
void fn_1_79F8(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M516_SCORE *work;

    obj = omAddObjEx(objman, 60, 0, 0, -1, fn_1_7A84);
    lbl_1_bss_48 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M516_SCORE));
}

/* fn_1_7A80, score.c, 1 insn. Empty, unreferenced. */
void fn_1_7A80(void)
{
}

/* fn_1_7A84, score.c, 15 insns. Score object init. */
void fn_1_7A84(OMOBJ *obj)
{
    fn_1_7AE8(obj);
    obj->objFunc = fn_1_7AC0;
}

/* fn_1_7AC0, score.c, 10 insns. Score object main. */
void fn_1_7AC0(OMOBJ *obj)
{
    fn_1_7E04(obj);
}

/* fn_1_7AE8, score.c, 199 insns. Builds the four score readouts. */
void fn_1_7AE8(OMOBJ *obj)
{
    M516_SCORE *work = obj->data;
    ANIMDATA *anim;
    ANIMDATA *charAnim;
    ANIMDATA *unitAnim;
    HUSPRGRPID winId;
    HUSPRGRPID grpId;
    MGSCORE *score;
    s32 i;
    s32 j;

    anim = HuSprAnimDataRead(DATANUM(DATA_m516, 0x12));
    unitAnim = HuSprAnimDataRead(DATANUM(DATA_mgconst, 0x30));
    for (i = 0; i < 4; i++) {
        winId = MgScoreWinCreate(112, 40);
        work->unk08[i].unk04 = winId;
        MgScoreWinPosSet(winId, lbl_1_data_2C0[i].x, lbl_1_data_2C0[i].y);
        MgScoreWinDispSet(winId, FALSE);
        score = MgScoreCreate(DATANUM(DATA_mgconst, 0x31), -1, TRUE);
        work->unk08[i].unk08 = score;
        MgScoreMaxDigitSet(score, 2);
        MgScoreDispOff(score);
        MgScorePosSet(score, 22.0f + lbl_1_data_2C0[i].x, lbl_1_data_2C0[i].y);
        MgScoreColorSet(score, 255, 216, 21);
        MgScorePriSet(score, 10);
        charAnim = HuSprAnimDataRead(lbl_1_data_2E0[GwPlayerConf[i].charNo]);
        grpId = HuSprGrpCreate(3);
        work->unk08[i].unk06 = grpId;
        HuSprGrpPosSet(grpId, lbl_1_data_2C0[i].x, lbl_1_data_2C0[i].y);
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(charAnim, 50, 0));
        HuSprPosSet(grpId, 0, -38.0f, 0.0f);
        HuSprGrpMemberSet(grpId, 1, HuSprCreate(anim, 50, 0));
        HuSprPosSet(grpId, 1, -15.0f, 0.0f);
        HuSprGrpMemberSet(grpId, 2, HuSprCreate(unitAnim, 50, 0));
        HuSprPosSet(grpId, 2, 4.0f, 0.0f);
        HuSprBankSet(grpId, 2, 15);
        HuSprColorSet(grpId, 2, 255, 255, 255);
        for (j = 0; j < 3; j++) {
            HuSprAttrSet(grpId, j, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grpId, j, HUSPR_ATTR_DISPOFF);
        }
    }
}

/* fn_1_7E04, score.c, 130 insns. Fade-in, then the digits. */
void fn_1_7E04(OMOBJ *obj)
{
    M516_SCORE *work = obj->data;
    s32 value;
    HUSPRGRPID grpId;
    MGSCORE *score;
    HUSPRGRPID winId;
    s32 i;
    s32 j;

    switch (work->unk00) {
        case 0:
            if (fn_1_1850() != 2) {
                break;
            }
            work->unk00++;
            work->unk04 = 0.0f;
            for (i = 0; i < 4; i++) {
                winId = work->unk08[i].unk04;
                MgScoreWinDispSet(winId, TRUE);
                score = work->unk08[i].unk08;
                MgScoreDispOn(score);
                grpId = work->unk08[i].unk06;
                for (j = 0; j < 3; j++) {
                    HuSprAttrReset(grpId, j, HUSPR_ATTR_DISPOFF);
                }
            }
        case 1:
            if ((work->unk04 += 0.1) >= 1.0) {
                work->unk00++;
            }
            for (i = 0; i < 4; i++) {
                winId = work->unk08[i].unk04;
                MgScoreWinTPLvlSet(winId, 0.7 * work->unk04);
                score = work->unk08[i].unk08;
                MgScoreTPLvlSet(score, work->unk04);
                grpId = work->unk08[i].unk06;
                for (j = 0; j < 3; j++) {
                    HuSprTPLvlSet(grpId, j, work->unk04);
                }
            }
            break;
        case 2:
            break;
    }
    for (i = 0; i < 4; i++) {
        grpId = work->unk08[i].unk06;
        value = work->unk08[i].unk00;
        if (value > 99) {
            value = 99;
        }
        score = work->unk08[i].unk08;
        MgScoreValueSet(score, value);
    }
}

/* fn_1_800C, score.c, 31 insns. Add to one player's score. */
void fn_1_800C(OMOBJ *obj, s32 add)
{
    M516_SCORE *work = lbl_1_bss_48->data;
    s32 no;

    if (obj != NULL) {
        no = fn_1_485C(obj);
        work->unk08[no].unk00 += add;
    }
}

/* fn_1_8088, score.c, 14 insns. */
s32 fn_1_8088(s32 no)
{
    OMOBJ *obj = lbl_1_bss_48;
    M516_SCORE *work = obj->data;

    return work->unk08[no].unk00;
}
