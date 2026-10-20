/*
 * m574Dll score.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/score.s.
 */

#include "REL/m574Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/gamemes.h"
#include "game/mg/score.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x310 */ /* float lbl_1_rodata_310 = 22.0f; */
/* 0x314 */ /* float lbl_1_rodata_314 = -42.0f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 0.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 1.0f; */
/* 0x320 */ /* double lbl_1_rodata_320 = 1; */
/* 0x328 */ /* double lbl_1_rodata_328 = 0.02; */
/* 0x330 */ /* double lbl_1_rodata_330 = 1.2; */
/* 0x338 */ /* double lbl_1_rodata_338 = 0.04; */
/* 0x340 */ /* double lbl_1_rodata_340 = 4503601774854144; */

/* --- .data --- */
/* 0x570 */ float lbl_1_data_570[2] = { 288.0f, 58.0f }; /* record window position */
/* 0x578 */ s32 lbl_1_data_578[13] = { 500, 1000, 2000, 10, 50, 100, 100, 50, 50, 100, 10, 20, 200 }; /* points per kind (fn_1_77D4/fn_1_7874) */
/* 0x5AC */ char lbl_1_data_5AC[11][4] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "" };
/* Hu3DAnimCreate names, read as [team][digit] (mulli 0x14 + j*4); the symbol is 0x2C
 * with a trailing zero word, so it is declared flat and indexed through this view. */
#define M574_DIGITNAME(team, digit) (((char(*)[5][4])lbl_1_data_5AC)[team][digit])

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x58 */ OMOBJ *lbl_1_bss_58; /* score object; data is M574_SCORE */

/* --- functions (reference order) --- */
/* 34 insns. Called from fn_1_348. */
void fn_1_7130(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M574_SCORE *work;

    obj = omAddObjEx(objman, 70, 1, 0, -1, fn_1_71BC);
    lbl_1_bss_58 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M574_SCORE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M574_SCORE));
}

/* 1 insns */
void fn_1_71B8(void)
{
}

/* 17 insns. Score object init. */
void fn_1_71BC(OMOBJ *obj)
{
    fn_1_7238(obj);
    fn_1_7468(obj);
    obj->objFunc = fn_1_7200;
}

/* 14 insns. Score object main. */
void fn_1_7200(OMOBJ *obj)
{
    fn_1_7328(obj);
    fn_1_75EC(obj);
}

/* 60 insns. Score board model and its digit animations. */
void fn_1_7238(OMOBJ *obj)
{
    M574_SCORE *work = obj->data;
    void *data;
    HU3DMODELID mdlId;
    M574_SCORETEAM *team;
    s32 i;
    s32 j;

    data = HuDataSelHeapReadNum(0x81001F, HU_MEMNUM_OVL, HEAP_MODEL);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x81001E, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    for (i = 0; i < 2; i++) {
        team = &work->unk000[i];
        for (j = 0; j < 5; j++) {
            team->unk010[j] = Hu3DAnimCreate(data, mdlId, M574_DIGITNAME(i, j));
            Hu3DAnimAttrSet(team->unk010[j], 1);
        }
    }
}

/* 80 insns. Digits: count the display up to the score, or blink a bonus value. */
void fn_1_7328(OMOBJ *obj)
{
    M574_SCORE *work = obj->data;
    M574_SCORETEAM *team;
    s32 i;
    s32 blink;
    s32 value;
    s32 j;
    s32 div;

    for (i = 0; i < 2; i++) {
        team = &work->unk000[i];
        if (team->unk008 != 0) {
            team->unk008--;
            blink = ((team->unk008 & 0xF) < 6) ? 0 : 1;
            value = team->unk00C;
        } else {
            blink = 0;
            value = team->unk004;
            value += (team->unk000 - value > 100) ? 40 : 10;
            if (value > team->unk000) {
                value = team->unk000;
            }
            team->unk004 = value;
        }
        if (value > 99999) {
            value = 99999;
        }
        for (div = 10000, j = 0; j < 5; j++) {
            Hu3DAnimBankSet(team->unk010[j], (u16)(blink + (value / div) * 2));
            value %= div;
            div /= 10;
        }
    }
}

/* 97 insns. Record window. */
void fn_1_7468(OMOBJ *obj)
{
    M574_SCORE *work = obj->data;
    ANIMDATA *anim;
    MGSCORE *score;
    HUSPRGRPID grpId;
    HUSPRGRPID winId;

    work->unk038 = 0;
    work->unk040 = GWMgRecordGet(9);
    work->unk044 = winId = MgScoreWinCreate(120, 40);
    MgScoreWinPosSet(winId, lbl_1_data_570[0], lbl_1_data_570[1]);
    score = MgScoreCreate(0x960030, -1, 1);
    work->unk048 = score;
    MgScoreMaxDigitSet(score, 5);
    MgScorePosSet(score, lbl_1_data_570[0] - 22.0f, lbl_1_data_570[1]);
    MgScoreColorSet(score, 66, 255, 122);
    MgScoreValueSet(score, work->unk040);
    grpId = HuSprGrpCreate(1);
    work->unk046 = grpId;
    HuSprGrpPosSet(grpId, lbl_1_data_570[0], lbl_1_data_570[1]);
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x960045, HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(anim, 50, 0));
    HuSprPosSet(grpId, 0, -42.0f, 0.0f);
}

/* 122 insns. Record window: pulse after a new record. */
void fn_1_75EC(OMOBJ *obj)
{
    M574_SCORE *work = obj->data;
    float scale = 1.0f;

    switch (work->unk038) {
        case 0:
            break;
        case 1:
            if (MgSeqModeGet() == 7) {
                work->unk038++;
            }
            break;
        case 2:
            if (MgSeqFrameNoGet() >= 90) {
                work->unk038++;
                work->unk03C = 0;
                MgScoreValueSet(work->unk048, work->unk040);
            }
            break;
        case 3:
            scale = 1.0 + 0.02 * (float)++work->unk03C;
            if (work->unk03C >= 10) {
                work->unk038++;
                work->unk03C = 0;
            }
            break;
        case 4:
            scale = 1.2 - 0.04 * (float)++work->unk03C;
            if (work->unk03C >= 5) {
                work->unk038--;
                work->unk03C = 0;
            }
            break;
    }
    if (work->unk038 != 0) {
        MgScoreDigitScaleSet(work->unk048, scale, scale);
        HuSprScaleSet(work->unk046, 0, scale, scale);
    }
}

/* 40 insns. Adds lbl_1_data_578[kind] to a team's score (main mode only). */
void fn_1_77D4(s32 team, s32 kind)
{
    M574_SCORE *work;
    M574_SCORETEAM *t;
    s32 value;

    if (MgSeqModeGet() == 5) {
        work = lbl_1_bss_58->data;
        t = &work->unk000[team];
        value = lbl_1_data_578[kind];
        value += t->unk000;
        if (value > 99999) {
            value = 99999;
        }
        t->unk000 = value;
    }
}

/* 53 insns. Blinks lbl_1_data_578[kind] for 60 frames, then adds it (fn_1_77D4 inlined). */
void fn_1_7874(s32 team, s32 kind)
{
    M574_SCORE *work;
    M574_SCORETEAM *t;

    if (MgSeqModeGet() == 5) {
        work = lbl_1_bss_58->data;
        t = &work->unk000[team];
        t->unk00C = lbl_1_data_578[kind];
        t->unk008 = 60;
        fn_1_77D4(team, kind);
    }
}

/* 13 insns */
s32 fn_1_7948(s32 team)
{
    OMOBJ *obj = lbl_1_bss_58;
    M574_SCORE *work = obj->data;

    return work->unk000[team].unk000;
}

/* 51 insns. New record check: best score of a winning team with a player still in. */
s32 fn_1_797C(void)
{
    M574_SCORE *work = lbl_1_bss_58->data;
    s32 best = 0;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (fn_1_940(i) != -1 && fn_1_1F28(i) != 0 && work->unk000[i].unk000 > best) {
            best = work->unk000[i].unk000;
        }
    }
    if (best > work->unk040) {
        MgSeqRecordSet(best);
        GWMgRecordSet(9, best);
        work->unk040 = best;
        work->unk038 = 1;
        return 1;
    }
    return 0;
}
