/*
 * m580Dll score.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/score.s.
 */

#include "REL/m580Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/mgdata.h"
#include "game/mg/score.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x710 */ /* float lbl_1_rodata_710 = 10.0f; */
/* 0x714 */ /* float lbl_1_rodata_714 = 0.0f; */
/* 0x718 */ /* double lbl_1_rodata_718 = 0.1; */
/* 0x720 */ /* double lbl_1_rodata_720 = 1; */
/* 0x728 */ /* double lbl_1_rodata_728 = 0.7; */
/* 0x730 */ /* double lbl_1_rodata_730 = 3.141592653589793; */
/* 0x738 */ /* double lbl_1_rodata_738 = 180; */
/* 0x740 */ /* float lbl_1_rodata_740 = -23.039999f; */
/* 0x744 */ /* float lbl_1_rodata_744 = 23.039999f; */
/* 0x748 */ /* float lbl_1_rodata_748 = 1.5f; */
/* 0x74C */ /* float lbl_1_rodata_74C = 1.0f; */
/* 0x750 */ /* float lbl_1_rodata_750 = 2.88f; */
/* 0x754 */ /* float lbl_1_rodata_754 = -1.0f; */
/* 0x758 */ /* float lbl_1_rodata_758 = -48.0f; */
/* 0x75C */ /* float lbl_1_rodata_75C = 172.8f; */
/* 0x760 */ /* float lbl_1_rodata_760 = 360.0f; */
/* 0x764 */ /* float lbl_1_rodata_764 = 403.19998f; */
/* 0x768 */ /* float lbl_1_rodata_768 = 288.0f; */
/* 0x76C */ /* float lbl_1_rodata_76C = 19.199999f; */
/* 0x770 */ /* float lbl_1_rodata_770 = 806.39996f; */
/* 0x774 */ /* float lbl_1_rodata_774 = 144.0f; */
/* 0x778 */ /* float lbl_1_rodata_778 = 0.5f; */
/* 0x77C */ /* float lbl_1_rodata_77C = 24.0f; */
/* 0x780 */ /* float lbl_1_rodata_780 = -230.40001f; */
/* 0x784 */ /* float lbl_1_rodata_784 = 0.055555556f; */
/* 0x788 */ /* float lbl_1_rodata_788 = 0.95f; */
/* 0x78C */ /* float lbl_1_rodata_78C = -16.0f; */
/* 0x790 */ /* float lbl_1_rodata_790 = 33.75f; */
/* 0x794 */ /* float lbl_1_rodata_794 = 0.041666668f; */
/* 0x798 */ /* double lbl_1_rodata_798 = 1.5; */
/* 0x7A0 */ /* float lbl_1_rodata_7A0 = 90.0f; */
/* 0x7A4 */ /* float lbl_1_rodata_7A4 = 0.80000013f; */
/* 0x7A8 */ /* float lbl_1_rodata_7A8 = 8.333334f; */
/* 0x7AC */ /* float lbl_1_rodata_7AC = 0.017833335f; */
/* 0x7B0 */ /* float lbl_1_rodata_7B0 = 102.0f; */
/* 0x7B4 */ /* float lbl_1_rodata_7B4 = 0.05f; */
/* 0x7B8 */ /* double lbl_1_rodata_7B8 = 4503599627370496; */
/* 0x7C0 */ /* float lbl_1_rodata_7C0 = 48.0f; */
/* 0x7C4 */ /* float lbl_1_rodata_7C4 = 16.0f; */
/* 0x7C8 */ /* float lbl_1_rodata_7C8 = 32.0f; */
/* 0x7CC */ /* float lbl_1_rodata_7CC = -32.0f; */
/* 0x7D0 */ /* double lbl_1_rodata_7D0 = 0; */

/* --- .data --- */
/* 0x7E0 */ HuVec2f lbl_1_data_7E0[2] = { { 47.0f, 59.0f }, { 529.0f, 59.0f } };
/* 0x7F0 */ HuVec2f lbl_1_data_7F0 = { 288.0f, 55.0f };
/* 0x7F8 */ s32 lbl_1_data_7F8[11][4] = {
    { 0x00230010, 0, 0, 0 },
    { 0x00230011, 0, 0, 0 },
    { 0x00230012, 0, 0, 0 },
    { 0x00230013, 0, 0, 0 },
    { 0x00230014, 0, 0, 0 },
    { 0x00230015, 0, 0, 0 },
    { 0x00230016, 0, 0, 0 },
    { 0x00230017, 0, 0, 0 },
    { 0x00230018, 0, 0, 0 },
    { 0x00230019, 0, 0, 0 },
    { 0x0023004E, 0, 0, 0 },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x250 */ OMOBJ *lbl_1_bss_250; /* the score object; dtk size 0x8 is alignment */

/* --- functions (reference order) --- */

/* 34 insns. Score object and its 0x4DC work. */
void fn_1_EE34(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_SCORE *work;

    obj = omAddObjEx(objman, 80, 0, 0, -1, fn_1_EEC0);
    lbl_1_bss_250 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_SCORE));
}

/* 1 insns. Empty. */
void fn_1_EEBC(void)
{
}

/* 19 insns. Score object init. */
void fn_1_EEC0(OMOBJ *obj)
{
    fn_1_EF4C(obj);
    fn_1_F254(obj);
    fn_1_108DC(obj);
    obj->objFunc = fn_1_EF0C;
}

/* 16 insns. Score object per frame. */
void fn_1_EF0C(OMOBJ *obj)
{
    fn_1_F0B8(obj);
    fn_1_F758(obj);
    fn_1_10C44(obj);
}

/* 91 insns. Team score windows. */
void fn_1_EF4C(OMOBJ *obj)
{
    s32 i;
    MGSCORE *score;
    HUSPRGRPID gid;
    M580_SCORE *work;

    work = obj->data;
    for (i = 0; i < 2; i++) {
        gid = MgScoreWinCreate(64, 40);
        work->unk024[i].unk004 = gid;
        MgScoreWinPosSet(gid, lbl_1_data_7E0[i].x, lbl_1_data_7E0[i].y);
        MgScoreWinDispSet(gid, FALSE);
        if (i == 0) {
            MgScoreWinColorSet(gid, 160, 64, 64);
        } else {
            MgScoreWinColorSet(gid, 64, 64, 160);
        }
        score = MgScoreCreate(0x960031, -1, TRUE);
        work->unk024[i].unk008 = score;
        MgScoreMaxDigitSet(score, 2);
        MgScoreDispOff(score);
        MgScorePosSet(score, lbl_1_data_7E0[i].x - 10.0f, lbl_1_data_7E0[i].y);
        MgScoreColorSet(score, 255, 216, 21);
        MgScorePriSet(score, 10);
    }
}

/* 103 insns. Team score windows per frame: fade in, then show the goals. */
void fn_1_F0B8(OMOBJ *obj)
{
    M580_SCORE *work;
    s32 i;
    MGSCORE *score;
    s32 value;
    HUSPRGRPID gid;

    work = obj->data;
    switch (work->unk000) {
        case 0:
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk000++;
            work->unk004 = 0.0f;
            for (i = 0; i < 2; i++) {
                gid = work->unk024[i].unk004;
                MgScoreWinDispSet(gid, TRUE);
                score = work->unk024[i].unk008;
                MgScoreDispOn(score);
            }
        case 1:
            if ((work->unk004 += 0.1) >= 1.0) {
                work->unk000++;
            }
            for (i = 0; i < 2; i++) {
                gid = work->unk024[i].unk004;
                MgScoreWinTPLvlSet(gid, 0.7 * work->unk004);
                score = work->unk024[i].unk008;
                MgScoreTPLvlSet(score, work->unk004);
            }
            break;
        case 2:
            break;
    }
    for (i = 0; i < 2; i++) {
        value = work->unk024[i].unk000;
        if (value > 99) {
            value = 99;
        }
        score = work->unk024[i].unk008;
        MgScoreValueSet(score, value);
    }
}

/* 165 insns. Goal overlay digit sprites. */
void fn_1_F254(OMOBJ *obj)
{
    M580_SCORE *work;
    M580_SCOREOVL *ovl;
    s32 i;
    s32 j;
    s32 k;

    work = obj->data;
    ovl = &work->unk03C;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 20; j++) {
            for (k = 0; k < 2; k++) {
                if (lbl_1_data_7F8[j % 10][k]) {
                    ovl->unk0D0[i][j].unk000[k] = espEntry(lbl_1_data_7F8[j % 10][k], 49, 0);
                    espAttrSet(ovl->unk0D0[i][j].unk000[k], HUSPR_ATTR_LINEAR);
                    espDispOff(ovl->unk0D0[i][j].unk000[k]);
                } else {
                    ovl->unk0D0[i][j].unk000[k] = -1;
                }
            }
        }
    }
    for (k = 0; k < 2; k++) {
        if (lbl_1_data_7F8[10][k]) {
            ovl->unk490.unk000[k] = espEntry(lbl_1_data_7F8[10][k], 49, 0);
            espAttrSet(ovl->unk490.unk000[k], HUSPR_ATTR_LINEAR);
            espDispOff(ovl->unk490.unk000[k]);
        } else {
            ovl->unk490.unk000[k] = -1;
        }
    }
    for (i = 0; i < 2; i++) {
        ovl->unk020[i].unk000[0] = -1;
        ovl->unk020[i].unk000[1] = -1;
    }
    ovl->unk020[2].unk000[0] = -1;
    ovl->unk020[2].unk000[1] = -1;
    ovl->unk020[3].unk000[0] = -1;
    ovl->unk020[3].unk000[1] = -1;
    HuDataDirClose(lbl_1_data_7F8[0][0]);
}

/* 86 insns. m433 M433ScoreOvlSprUpdate, exact. */
void fn_1_F4E8(M580_SCOREOVLSPR *ovlspr)
{
    int i;
    for (i = 0; i < 2; i++) {
        float ofsX, ofsY;
        if (ovlspr->unk000[i] < 0) {
            continue;
        }
        espDispOn(ovlspr->unk000[i]);
        ofsX = HuCos(ovlspr->unk028) * (ovlspr->unk004[i] * ovlspr->unk01C);
        ofsY = HuSin(ovlspr->unk028) * (ovlspr->unk004[i] * ovlspr->unk01C);
        espPosSet(ovlspr->unk000[i], ovlspr->unk00C + ofsX, ovlspr->unk010 + ofsY);
        espZRotSet(ovlspr->unk000[i], ovlspr->unk028);
        espScaleSet(ovlspr->unk000[i], ovlspr->unk01C, ovlspr->unk020);
        espTPLvlSet(ovlspr->unk000[i], ovlspr->unk024);
    }
}

/* 70 insns. m433 M433ScoreOvlValueSet, exact. */
void fn_1_F640(M580_SCORESPRNUM *sprNum, M580_SCOREOVLSPR *ovlspr, u32 num)
{
    u32 digit1 = num % 10;
    u32 digit2 = num / 10;
    if (digit2 == 0) {
        ovlspr->unk000[0] = sprNum[digit1].unk000[0];
        ovlspr->unk000[1] = -1;
        ovlspr->unk004[0] = 0;
    } else {
        ovlspr->unk000[0] = sprNum[digit2 + 10].unk000[0];
        ovlspr->unk000[1] = sprNum[digit1].unk000[0];
        ovlspr->unk004[0] = -23.039999f;
        ovlspr->unk004[1] = 23.039999f;
    }
    ovlspr->unk00C = ovlspr->unk010 = 0;
    ovlspr->unk014 = ovlspr->unk018 = 0;
    ovlspr->unk01C = ovlspr->unk020 = 1.5f;
    ovlspr->unk024 = 1.0f;
    ovlspr->unk028 = 0;
}

/* 1098 insns. Goal overlay per frame (m433 M433ScoreUpdate's overlay half). */
void fn_1_F758(OMOBJ *obj)
{
    float t;
    float ofsX;
    float radius;
    float velX;
    M580_SCOREOVLSPR *ovlspr;
    M580_SCORESPRNUM *sprNum;
    M580_SCOREOVL *ovl;
    M580_SCORE *work;
    s32 i;
    s32 j;

    work = obj->data;
    ovl = &work->unk03C;
    velX = 2.88f;
    if (ovl->unk01C == 0) {
        ovlspr = &ovl->unk020[0];
    } else {
        ovlspr = &ovl->unk020[1];
        velX *= -1.0f;
    }
    switch (ovl->unk000) {
        case 0:
            break;

        case 1:
            fn_1_F640(&ovl->unk0D0[0][0], &ovl->unk020[0], ovl->unk00C[0]);
            fn_1_F640(&ovl->unk0D0[1][0], &ovl->unk020[1], ovl->unk00C[1]);
            fn_1_F640(&ovl->unk490, &ovl->unk020[2], 0);
            fn_1_F640(&ovl->unk0D0[2][0], &ovl->unk020[3], ovl->unk014[ovl->unk01C]);
            ofsX = -48.0f;
            ovl->unk020[0].unk00C = 172.8f;
            ovl->unk020[0].unk010 = 360.0f - ofsX;
            ovl->unk020[1].unk00C = 403.19998f;
            ovl->unk020[1].unk010 = 360.0f - ofsX;
            ovl->unk020[2].unk00C = 288.0f;
            ovl->unk020[2].unk010 = 360.0f - ofsX;
            ovl->unk020[0].unk024 = ovl->unk020[1].unk024 = ovl->unk020[2].unk024 = 0.0f;
            ofsX = ofsX / 19.199999f;
            ovl->unk020[0].unk018 = ofsX;
            ovl->unk020[1].unk018 = ofsX;
            ovl->unk020[2].unk018 = ofsX;
            ovl->unk020[3].unk00C = 806.39996f;
            ovl->unk020[3].unk010 = 144.0f;
            ovl->unk020[3].unk01C += 0.5f;
            ovl->unk020[3].unk020 -= 0.5f;
            ovl->unk020[3].unk014 = (403.19998f - ovl->unk020[3].unk00C) / 24.0f;
            ovl->unk020[3].unk018 = (360.0f - ovl->unk020[3].unk010) / 24.0f;
            if (ovl->unk01C == 0) {
                ovl->unk020[3].unk00C = -230.40001f;
                ovl->unk020[3].unk014 *= -1.0f;
            }
            ovl->unk000++;
            ovl->unk004 = 0;
            break;

        case 2:
            t = ovl->unk020[0].unk024;
            t += 0.055555556f;
            if (t > 0.95f) {
                t = 1.0f;
            }
            ovl->unk020[2].unk024 = t;
            ovl->unk020[1].unk024 = t;
            ovl->unk020[0].unk024 = t;
            ovl->unk020[0].unk010 += ovl->unk020[0].unk018;
            ovl->unk020[1].unk010 += ovl->unk020[1].unk018;
            ovl->unk020[2].unk010 += ovl->unk020[2].unk018;
            ovl->unk020[3].unk00C += ovl->unk020[3].unk014;
            ovl->unk020[3].unk010 += ovl->unk020[3].unk018;
            if (ovl->unk004 >= 19.199999f) {
                ovlspr->unk014 = velX;
                ovlspr->unk018 = -16.0f;
                ovl->unk000++;
                ovl->unk008 = 0;
                HuAudFXPlay(0x964);
            }
            break;

        case 3:
            if (ovl->unk004 <= 24.0f) {
                ovl->unk020[3].unk00C += ovl->unk020[3].unk014;
                ovl->unk020[3].unk010 += ovl->unk020[3].unk018;
            }
            if (ovl->unk008 < 24.0f) {
                ovl->unk008++;
                t = 33.75f * ovl->unk008;
                radius = 0.041666668f * ovl->unk008;
                radius = 0.5f * (1.0f - (radius * radius));
                if (ovl->unk008 == 24.0f) {
                    radius = 0.0f;
                }
                ovl->unk020[3].unk01C = 1.5 + (radius * HuCos(t));
                ovl->unk020[3].unk020 = 1.5 + (radius * HuSin((t - 90.0f)));
            }
            ovlspr->unk01C = ovl->unk020[3].unk020;
            ovlspr->unk020 = ovl->unk020[3].unk01C;
            ovlspr->unk00C += ovlspr->unk014;
            ovlspr->unk010 += ovlspr->unk018;
            ovlspr->unk018 += 0.80000013f;
            ovlspr->unk028 += 8.333334f;
            ovlspr->unk024 -= 0.017833335f;
            if (ovlspr->unk024 < 0.0f) {
                ovlspr->unk024 = 0.0f;
            }
            if (ovl->unk004 >= 102.0f) {
                ovl->unk000++;
                ovl->unk004 = 0;
            }
            break;

        case 4:
            t = ovl->unk020[3].unk024;
            t -= 0.055555556f;
            if (t < 0.05f) {
                t = 0.0f;
                ovl->unk000++;
                ovl->unk004 = 0;
            }
            ovl->unk020[3].unk024 = t;
            ovl->unk020[2].unk024 = t;
            ovl->unk020[1].unk024 = t;
            ovl->unk020[0].unk024 = t;
            break;

        default:
            for (i = 0; i < 2; i++) {
                ovl->unk020[i].unk000[0] = -1;
                ovl->unk020[i].unk000[1] = -1;
            }
            ovl->unk020[2].unk000[0] = -1;
            ovl->unk020[2].unk000[1] = -1;
            ovl->unk020[3].unk000[0] = -1;
            ovl->unk020[3].unk000[1] = -1;
            ovl->unk000 = 0;
            break;
    }
    for (i = 0; i < 3; i++) {
        sprNum = &ovl->unk0D0[i][0];
        for (j = 0; j < 20; j++, sprNum++) {
            if (sprNum->unk000[0] >= 0) {
                espDispOff(sprNum->unk000[0]);
            }
            if (sprNum->unk000[1] >= 0) {
                espDispOff(sprNum->unk000[1]);
            }
        }
    }
    sprNum = &ovl->unk490;
    if (sprNum->unk000[0] >= 0) {
        espDispOff(sprNum->unk000[0]);
    }
    if (sprNum->unk000[1] >= 0) {
        espDispOff(sprNum->unk000[1]);
    }
    fn_1_F4E8(&ovl->unk020[0]);
    fn_1_F4E8(&ovl->unk020[1]);
    fn_1_F4E8(&ovl->unk020[2]);
    fn_1_F4E8(&ovl->unk020[3]);
    ovl->unk004++;
}

/* 23 insns. Start the goal overlay: new scores and the scoring team. */
void fn_1_10880(u32 score0, u32 score1, u32 team)
{
    OMOBJ *obj;
    M580_SCORE *work;
    M580_SCOREOVL *ovl;

    obj = lbl_1_bss_250;
    work = obj->data;
    ovl = &work->unk03C;
    ovl->unk000 = 1;
    ovl->unk00C[0] = ovl->unk014[0];
    ovl->unk00C[1] = ovl->unk014[1];
    ovl->unk014[0] = score0;
    ovl->unk014[1] = score1;
    ovl->unk01C = team;
}

/* 218 insns. Match timer window. */
void fn_1_108DC(OMOBJ *obj)
{
    MGSCORE *score;
    M580_SCORE *work;
    HUSPRGRPID grpId;
    s32 i;
    s32 time;
    HUSPRGRPID gid;
    ANIMDATA *anim;

    work = obj->data;
    switch (mgMatchMaxScore) {
        case 1:
            time = 3600;
            break;
        case 2:
            time = 10800;
            break;
        case 3:
            time = 18000;
            break;
        default:
            time = 10800;
            break;
    }
    work->unk010 = time;
    gid = MgScoreWinCreate(136, 32);
    work->unk014 = gid;
    MgScoreWinPosSet(gid, lbl_1_data_7F0.x, lbl_1_data_7F0.y);
    MgScoreWinDispSet(gid, FALSE);
    score = MgScoreCreate(0x960030, -1, TRUE);
    work->unk018 = score;
    MgScoreMaxDigitSet(score, 1);
    MgScoreDispOff(score);
    MgScorePosSet(score, lbl_1_data_7F0.x - 48.0f, lbl_1_data_7F0.y);
    MgScoreColorSet(score, 255, 255, 255);
    MgScorePriSet(score, 10);
    score = MgScoreCreate(0x960030, -1, TRUE);
    work->unk01C = score;
    MgScoreMaxDigitSet(score, 2);
    MgScoreDispOff(score);
    MgScorePosSet(score, lbl_1_data_7F0.x - 16.0f, lbl_1_data_7F0.y);
    MgScoreColorSet(score, 255, 255, 255);
    MgScorePriSet(score, 10);
    score = MgScoreCreate(0x960030, -1, TRUE);
    work->unk020 = score;
    MgScoreMaxDigitSet(score, 2);
    MgScoreDispOff(score);
    MgScorePosSet(score, 32.0f + lbl_1_data_7F0.x, lbl_1_data_7F0.y);
    MgScoreColorSet(score, 255, 255, 255);
    MgScorePriSet(score, 10);
    grpId = HuSprGrpCreate(2);
    work->unk016 = grpId;
    HuSprGrpPosSet(grpId, lbl_1_data_7F0.x, lbl_1_data_7F0.y);
    anim = work->unk018->digitAnim;
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(anim, 50, 10));
    HuSprPosSet(grpId, 0, -32.0f, 0.0f);
    HuSprColorSet(grpId, 0, 255, 255, 255);
    HuSprGrpMemberSet(grpId, 1, HuSprCreate(anim, 50, 11));
    HuSprPosSet(grpId, 1, 16.0f, 0.0f);
    HuSprColorSet(grpId, 1, 255, 255, 255);
    for (i = 0; i < 2; i++) {
        HuSprAttrSet(grpId, i, HUSPR_ATTR_NOANIM);
        HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF);
    }
}

/* 197 insns. Match timer per frame: fade in, count down, fade out. */
void fn_1_10C44(OMOBJ *obj)
{
    M580_SCORE *work;
    s32 i;
    s32 value;
    s32 time;
    HUSPRGRPID grpId;

    work = obj->data;
    switch (work->unk008) {
        case 0:
            if (MgSeqModeGet() != 3) {
                break;
            }
            work->unk008++;
            work->unk00C = 0.0f;
            MgScoreWinDispSet(work->unk014, TRUE);
            MgScoreDispOn(work->unk018);
            MgScoreDispOn(work->unk01C);
            MgScoreDispOn(work->unk020);
            grpId = work->unk016;
            for (i = 0; i < 2; i++) {
                HuSprAttrReset(grpId, i, HUSPR_ATTR_DISPOFF);
            }
        case 1:
            if ((work->unk00C += 0.1) < 1.0) {
                break;
            }
            work->unk008++;
            work->unk00C = 1.0f;
        case 2:
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk008++;
        case 3:
            if (--work->unk010 > 0) {
                break;
            }
            work->unk008++;
        case 4:
            if ((work->unk00C -= 0.1) <= 0.0) {
                work->unk008++;
                work->unk00C = 0.0f;
                MgScoreWinDispSet(work->unk014, FALSE);
                MgScoreDispOff(work->unk018);
                MgScoreDispOff(work->unk01C);
                MgScoreDispOff(work->unk020);
                grpId = work->unk016;
                for (i = 0; i < 2; i++) {
                    HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF);
                }
            }
            break;
        case 5:
            break;
    }
    MgScoreWinTPLvlSet(work->unk014, 0.7 * work->unk00C);
    MgScoreTPLvlSet(work->unk018, work->unk00C);
    MgScoreTPLvlSet(work->unk01C, work->unk00C);
    MgScoreTPLvlSet(work->unk020, work->unk00C);
    grpId = work->unk016;
    for (i = 0; i < 2; i++) {
        HuSprTPLvlSet(grpId, i, work->unk00C);
    }
    time = work->unk010;
    value = time / 3600;
    time -= value * 3600;
    MgScoreValueSet(work->unk018, value);
    value = time / 60;
    MgScoreValueSet(work->unk01C, value);
    value = time % 60;
    MgScoreValueSet(work->unk020, value * 100 / 60);
}

/* 45 insns. Add goals to a team (99 max) and start the goal overlay. */
void fn_1_10F58(s32 team, s32 add)
{
    M580_SCORE *work;
    M580_SCORETEAM *t;

    if (MgSeqModeGet() == 5) {
        work = lbl_1_bss_250->data;
        t = &work->unk024[team];
        add += t->unk000;
        if (add > 99) {
            add = 99;
        }
        t->unk000 = add;
        fn_1_10880(work->unk024[0].unk000, work->unk024[1].unk000, team);
    }
}

/* 14 insns. A team's goals. */
s32 fn_1_1100C(s32 team)
{
    OMOBJ *obj;
    M580_SCORE *work;

    obj = lbl_1_bss_250;
    work = obj->data;
    return work->unk024[team].unk000;
}

/* 2 insns. */
s32 fn_1_11044(void)
{
    return 0;
}

/* 21 insns. Time left; forced to 0 once the sequence is in mode 6. */
s32 fn_1_1104C(void)
{
    OMOBJ *obj;
    M580_SCORE *work;

    obj = lbl_1_bss_250;
    work = obj->data;
    if (MgSeqModeGet() == 6) {
        work->unk010 = 0;
    }
    return work->unk010;
}
