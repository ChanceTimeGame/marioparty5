/*
 * m514dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/score.s.
 */

#include "REL/m514Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/flag.h"
#include "game/mg/seqman.h"
#include "datanum/mgconst.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = -48.0f; */
/* 0x3B4 */ /* float lbl_1_rodata_3B4 = 10.0f; */
/* 0x3B8 */ /* float lbl_1_rodata_3B8 = -70.0f; */
/* 0x3BC */ /* float lbl_1_rodata_3BC = 0.0f; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = 60.0f; */
/* 0x3C8 */ /* double lbl_1_rodata_3C8 = 0.1; */
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 1; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = 1.0f; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 0.7; */
/* 0x3E8 */ /* double lbl_1_rodata_3E8 = 0.2; */
/* 0x3F0 */ /* double lbl_1_rodata_3F0 = 0.02; */
/* 0x3F8 */ /* double lbl_1_rodata_3F8 = 1.2; */
/* 0x400 */ /* double lbl_1_rodata_400 = 0.04; */
/* 0x408 */ /* double lbl_1_rodata_408 = 0.5; */
/* 0x410 */ /* double lbl_1_rodata_410 = 4503601774854144; */
/* 0x418 */ /* float lbl_1_rodata_418 = 3.0f; */
/* 0x420 */ /* double lbl_1_rodata_420 = -2500; */

/* --- .data --- */
/* 0x4F8 */ HuVec2f lbl_1_data_4F8 = { 288.0f, 58.0f };
/* 0x500 */ s32 lbl_1_data_500[15] = {
    MGCONST_ANM_marioSmall, MGCONST_ANM_luigiSmall, MGCONST_ANM_peachSmall,
    MGCONST_ANM_yoshiSmall, MGCONST_ANM_warioSmall, MGCONST_ANM_daisySmall,
    MGCONST_ANM_waluigiSmall, MGCONST_ANM_kinopioSmall, MGCONST_ANM_teresaSmall,
    MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaRSmall, MGCONST_ANM_minikoopaGSmall,
    MGCONST_ANM_minikoopaBSmall, MGCONST_ANM_minikoopaSmall, MGCONST_ANM_minikoopaSmall,
};
/* 0x53C */ HuVec2f lbl_1_data_53C[4] = {
    { 102.0f, 58.0f },
    { 102.0f, 108.0f },
    { 102.0f, 158.0f },
    { 102.0f, 208.0f },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x220 */ OMOBJ *lbl_1_bss_220;

/* --- functions (reference order) --- */

/* fn_1_8268, score.c, 38 insns. Unit setup hook: adds the score object. */
void fn_1_8268(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M514_SCORE *work;

    obj = omAddObjEx(objman, 70, 0, 0, -1, fn_1_8304);
    lbl_1_bss_220 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M514_SCORE));
    work->unk0A4 = work->unk0A8 = GWMgRecordGet(5);
}

/* fn_1_8300, score.c, 1 insn. Empty. */
void fn_1_8300(void)
{
}

/* fn_1_8304, score.c, 22 insns. Score object init. */
void fn_1_8304(OMOBJ *obj)
{
    fn_1_83A8(obj);
    if (!_CheckFlag(FLAG_INST_DECA)) {
        fn_1_8D58(obj);
    }
    obj->objFunc = fn_1_835C;
}

/* fn_1_835C, score.c, 19 insns. Score object main. */
void fn_1_835C(OMOBJ *obj)
{
    fn_1_879C(obj);
    if (!_CheckFlag(FLAG_INST_DECA)) {
        fn_1_900C(obj);
    }
}

/* fn_1_83A8, score.c, 253 insns. Builds the four score readouts. */
void fn_1_83A8(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    ANIMDATA *charAnim;
    ANIMDATA *anim;
    HUSPRGRPID winId;
    HUSPRGRPID grpId;
    s32 j;
    MGSCORE *score;
    s32 i;

    for (i = 0; i < 4; i++) {
        work->unk00C[i].unk004 = i;
        work->unk00C[i].unk014 = lbl_1_data_53C[i];
        work->unk00C[i].unk01C = lbl_1_data_53C[i];
        winId = MgScoreWinCreate(176, 40);
        work->unk00C[i].unk008 = winId;
        MgScoreWinPosSet(winId, lbl_1_data_53C[i].x, lbl_1_data_53C[i].y);
        MgScoreWinDispSet(winId, FALSE);
        score = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, FALSE);
        work->unk00C[i].unk00C = score;
        MgScoreMaxDigitSet(score, 3);
        MgScoreDispOff(score);
        MgScorePosSet(score, -48.0f + lbl_1_data_53C[i].x, lbl_1_data_53C[i].y);
        MgScoreColorSet(score, 255, 216, 21);
        score = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, TRUE);
        work->unk00C[i].unk010 = score;
        MgScoreMaxDigitSet(score, 2);
        MgScoreDispOff(score);
        MgScorePosSet(score, 10.0f + lbl_1_data_53C[i].x, lbl_1_data_53C[i].y);
        MgScoreColorSet(score, 255, 216, 21);
        charAnim = HuSprAnimDataRead(lbl_1_data_500[GwPlayerConf[i].charNo]);
        anim = HuSprAnimDataRead(DATANUM(DATA_m514, 0x22));
        grpId = HuSprGrpCreate(3);
        work->unk00C[i].unk00A = grpId;
        HuSprGrpPosSet(grpId, lbl_1_data_53C[i].x, lbl_1_data_53C[i].y);
        HuSprGrpMemberSet(grpId, 0, HuSprCreate(charAnim, 50, 0));
        HuSprPosSet(grpId, 0, -70.0f, 0.0f);
        HuSprGrpMemberSet(grpId, 1, HuSprCreate(score->digitAnim, 50, 12));
        HuSprPosSet(grpId, 1, 0.0f, 0.0f);
        HuSprColorSet(grpId, 1, 255, 216, 21);
        HuSprGrpMemberSet(grpId, 2, HuSprCreate(anim, 50, 2));
        HuSprPosSet(grpId, 2, 60.0f, 0.0f);
        HuSprColorSet(grpId, 2, 255, 216, 21);
        for (j = 0; j < 3; j++) {
            HuSprAttrSet(grpId, j, HUSPR_ATTR_NOANIM);
            HuSprAttrSet(grpId, j, HUSPR_ATTR_DISPOFF);
        }
    }
    fn_1_8C7C(obj);
}

/* fn_1_879C, score.c, 238 insns. Fade-in, digits, slide to rank slot. */
void fn_1_879C(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    s32 j;
    s32 value;
    HUSPRGRPID grpId;
    s32 i;

    switch (work->unk000) {
        case 0:
            if (MgSeqModeGet() != MGSEQ_MODE_MAIN) {
                break;
            }
            work->unk000++;
            work->unk008 = 0.0f;
            for (i = 0; i < 4; i++) {
                MgScoreWinDispSet(work->unk00C[i].unk008, TRUE);
                MgScoreDispOn(work->unk00C[i].unk00C);
                MgScoreDispOn(work->unk00C[i].unk010);
                grpId = work->unk00C[i].unk00A;
                for (j = 0; j < 3; j++) {
                    HuSprAttrReset(grpId, j, HUSPR_ATTR_DISPOFF);
                }
            }
        case 1:
            if ((work->unk008 += 0.1) >= 1.0) {
                work->unk008 = 1.0f;
                work->unk000++;
            }
            for (i = 0; i < 4; i++) {
                MgScoreWinTPLvlSet(work->unk00C[i].unk008, 0.7 * work->unk008);
                MgScoreTPLvlSet(work->unk00C[i].unk00C, work->unk008);
                MgScoreTPLvlSet(work->unk00C[i].unk010, work->unk008);
                grpId = work->unk00C[i].unk00A;
                for (j = 0; j < 3; j++) {
                    HuSprTPLvlSet(grpId, j, work->unk008);
                }
            }
            break;
        case 2:
            break;
    }
    for (i = 0; i < 4; i++) {
        float x;
        float y;

        grpId = work->unk00C[i].unk00A;
        value = work->unk00C[i].unk000 / 100;
        if (value > 999) {
            value = 999;
        }
        MgScoreValueSet(work->unk00C[i].unk00C, value);
        value = work->unk00C[i].unk000 % 100;
        MgScoreValueSet(work->unk00C[i].unk010, value);
        work->unk00C[i].unk014.x += 0.2 * (work->unk00C[i].unk01C.x - work->unk00C[i].unk014.x);
        work->unk00C[i].unk014.y += 0.2 * (work->unk00C[i].unk01C.y - work->unk00C[i].unk014.y);
        x = work->unk00C[i].unk014.x;
        y = work->unk00C[i].unk014.y;
        MgScoreWinPosSet(work->unk00C[i].unk008, x, y);
        MgScorePosSet(work->unk00C[i].unk00C, -48.0f + x, y);
        MgScorePosSet(work->unk00C[i].unk010, 10.0f + x, y);
        HuSprGrpPosSet(work->unk00C[i].unk00A, x, y);
    }
}

/* fn_1_8B54, score.c, 74 insns. Ranks the players by score (bubble sort). */
void fn_1_8B54(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    s32 order[4];
    s32 i;
    s32 j;
    s32 a;
    s32 b;
    s32 tmp;

    for (i = 0; i < 4; i++) {
        work->unk00C[i].unk004 = i;
        order[i] = i;
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            a = order[j];
            b = order[j + 1];
            if (work->unk00C[a].unk000 < work->unk00C[b].unk000) {
                tmp = work->unk00C[a].unk004;
                work->unk00C[a].unk004 = work->unk00C[b].unk004;
                work->unk00C[b].unk004 = tmp;
                tmp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = tmp;
            }
        }
    }
}

/* fn_1_8C7C, score.c, 55 insns. Sprite priority from rank. */
void fn_1_8C7C(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    s32 i;
    s16 prio;
    HUSPRGRPID grpId;

    for (i = 0; i < 4; i++) {
        prio = work->unk00C[i].unk004 * 2 + 50;
        fn_1_9300(work->unk00C[i].unk008, prio + 1);
        MgScorePriSet(work->unk00C[i].unk00C, prio);
        MgScorePriSet(work->unk00C[i].unk010, prio);
        grpId = work->unk00C[i].unk00A;
        HuSprPriSet(grpId, 0, prio);
        HuSprPriSet(grpId, 1, prio);
        HuSprPriSet(grpId, 2, prio);
    }
}

/* fn_1_8D58, score.c, 173 insns. Builds the record readout. */
void fn_1_8D58(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    ANIMDATA *crownAnim;
    ANIMDATA *anim;
    HUSPRGRPID winId;
    HUSPRGRPID grpId;
    MGSCORE *score;

    work->unk09C = 0;
    work->unk0AC = winId = MgScoreWinCreate(176, 40);
    MgScoreWinPosSet(winId, lbl_1_data_4F8.x, lbl_1_data_4F8.y);
    score = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, FALSE);
    work->unk0B0 = score;
    MgScoreMaxDigitSet(score, 3);
    MgScorePosSet(score, -48.0f + lbl_1_data_4F8.x, lbl_1_data_4F8.y);
    MgScoreColorSet(score, 66, 255, 122);
    score = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, TRUE);
    work->unk0B4 = score;
    MgScoreMaxDigitSet(score, 2);
    MgScorePosSet(score, 10.0f + lbl_1_data_4F8.x, lbl_1_data_4F8.y);
    MgScoreColorSet(score, 66, 255, 122);
    grpId = HuSprGrpCreate(3);
    work->unk0AE = grpId;
    HuSprGrpPosSet(grpId, lbl_1_data_4F8.x, lbl_1_data_4F8.y);
    crownAnim = HuSprAnimDataRead(MGCONST_ANM_crown);
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(crownAnim, 50, 0));
    HuSprPosSet(grpId, 0, -70.0f, 0.0f);
    HuSprGrpMemberSet(grpId, 1, HuSprCreate(score->digitAnim, 50, 12));
    HuSprPosSet(grpId, 1, 0.0f, 0.0f);
    HuSprColorSet(grpId, 1, 66, 255, 122);
    anim = HuSprAnimDataRead(DATANUM(DATA_m514, 0x22));
    HuSprGrpMemberSet(grpId, 2, HuSprCreate(anim, 50, 2));
    HuSprPosSet(grpId, 2, 60.0f, 0.0f);
    HuSprColorSet(grpId, 2, 66, 255, 122);
    fn_1_9258(obj);
}

/* fn_1_900C, score.c, 147 insns. Record readout: wait, then pulse. */
void fn_1_900C(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    float scale = 1.0f;

    switch (work->unk09C) {
        case 0:
            break;
        case 1:
            if (MgSeqModeGet() == MGSEQ_MODE_PREWIN) {
                work->unk09C++;
            }
            break;
        case 2:
            if (MgSeqFrameNoGet() >= 90) {
                work->unk09C++;
                work->unk0A0 = 0;
                fn_1_9258(obj);
            }
            break;
        case 3:
            scale = 1.0 + 0.02 * (float)++work->unk0A0;
            if (work->unk0A0 >= 10) {
                work->unk09C++;
                work->unk0A0 = 0;
            }
            break;
        case 4:
            scale = 1.2 - 0.04 * (float)++work->unk0A0;
            if (work->unk0A0 >= 5) {
                work->unk09C--;
                work->unk0A0 = 0;
            }
            break;
    }
    if (work->unk09C != 0) {
        MgScoreDigitScaleSet(work->unk0B0, scale, scale);
        MgScoreDigitScaleSet(work->unk0B4, scale, scale);
        HuSprScaleSet(work->unk0AE, 0, scale, scale);
        HuSprScaleSet(work->unk0AE, 1, scale, scale);
        HuSprScaleSet(work->unk0AE, 2, 1.0 + 0.5 * (scale - 1.0), scale);
    }
}

/* fn_1_9258, score.c, 42 insns. Shows the record value. */
void fn_1_9258(OMOBJ *obj)
{
    M514_SCORE *work = obj->data;
    s32 value;

    value = work->unk0A4 / 100;
    if (value > 999) {
        value = 999;
    }
    MgScoreValueSet(work->unk0B0, value);
    value = work->unk0A4 % 100;
    MgScoreValueSet(work->unk0B4, value);
    work->unk0A8 = work->unk0A4;
}

/* fn_1_9300, score.c, 13 insns. */
void fn_1_9300(HUSPRGRPID grpId, s16 prio)
{
    HuSprPriSet(grpId, 0, prio);
}

/* fn_1_9334, score.c, 143 insns. Re-ranks and retargets the readouts. */
void fn_1_9334(void)
{
    OMOBJ *obj = lbl_1_bss_220;
    M514_SCORE *work = obj->data;
    s32 i;

    fn_1_8B54(obj);
    fn_1_8C7C(obj);
    for (i = 0; i < 4; i++) {
        work->unk00C[i].unk01C = lbl_1_data_53C[work->unk00C[i].unk004];
    }
}

/* fn_1_9570, score.c, 19 insns. Sets one player's score from a distance. */
void fn_1_9570(s32 no, float value)
{
    M514_SCORE *work = lbl_1_bss_220->data;

    work->unk00C[no].unk000 = 3.0f * value;
}

/* fn_1_95BC, score.c, 14 insns. */
s32 fn_1_95BC(s32 no)
{
    OMOBJ *obj = lbl_1_bss_220;
    M514_SCORE *work = obj->data;

    return work->unk00C[no].unk000;
}

/* fn_1_95F4, score.c, 37 insns. Score back to a distance. */
float fn_1_95F4(s32 no)
{
    OMOBJ *obj = lbl_1_bss_220;
    M514_SCORE *work = obj->data;
    float dist;

    dist = -2500.0 + work->unk00C[no].unk000 / 3.0f;
    return dist;
}

/* fn_1_9688, score.c, 67 insns. */
float fn_1_9688(void)
{
    OMOBJ *obj = lbl_1_bss_220;
    M514_SCORE *work = obj->data;
    s32 max = 0;
    s32 maxNo = 0;
    s32 i;
    float pos;
    float dist;

    for (i = 0; i < 4; i++) {
        if (max < work->unk00C[i].unk000) {
            max = work->unk00C[i].unk000;
            maxNo = i;
        }
    }
    pos = fn_1_4238(maxNo);
    dist = -2500.0 + max / 3.0f;
    return pos + 0.5 * (dist - pos);
}

/* fn_1_9794, score.c, 35 insns. The record as a distance. */
float fn_1_9794(void)
{
    OMOBJ *obj = lbl_1_bss_220;
    M514_SCORE *work = obj->data;
    float dist;

    dist = -2500.0 + work->unk0A8 / 3.0f;
    return dist;
}

/* fn_1_9820, score.c, 53 insns. Checks for and stores a new record. */
s32 fn_1_9820(void)
{
    M514_SCORE *work = lbl_1_bss_220->data;
    s32 max = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (fn_1_1704(i) != -1 && fn_1_41C4(i) != 0 && work->unk00C[i].unk000 > max) {
            max = work->unk00C[i].unk000;
        }
    }
    if (max > work->unk0A4) {
        MgSeqRecordSet(max);
        GWMgRecordSet(5, max);
        work->unk0A4 = max;
        work->unk09C = 1;
        return 1;
    }
    return 0;
}

/* fn_1_98F4, score.c, 26 insns. Writes the scores to GwPlayer[].mgScore. */
void fn_1_98F4(void)
{
    M514_SCORE *work = lbl_1_bss_220->data;
    s32 i;
    s32 value;

    for (i = 0; i < 4; i++) {
        value = work->unk00C[i].unk000;
        GwPlayer[i].mgScore = value;
    }
}
