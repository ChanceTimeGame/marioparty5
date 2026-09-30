/*
 * m503dll opening.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/opening.s.
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

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 0.0f; */
/* 0xB0 */ /* double lbl_1_rodata_B0 = 0.05555555555555555; */
/* 0xB8 */ /* double lbl_1_rodata_B8 = 1; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = 1.0f; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 12; */
/* 0xD0 */ /* double lbl_1_rodata_D0 = 210; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 4503599627370496; */

/* --- .data --- */
/* 0x60 */ M503_CAMVIEW lbl_1_data_60[3] = {
    { { 0.0f, 0.0f, 0.0f }, { -50.0f, 0.0f, 1500.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 100.0f } },
    { { 0.0f, 0.0f, 100.0f }, { -35.0f, 0.0f, 1200.0f } },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2C gap_05_0000002C_bss (0x4) -- dtk filler */
/* 0x28 */ s32 lbl_1_bss_28;

/* --- functions (reference order) --- */
/* 35 insns */
OMOBJFUNC fn_1_2D4C(OMOBJMAN *objman)
{
    M503_CAMVIEW *view = &lbl_1_data_60[0];

    Center = view->unk000;
    CRot.x = view->unk00C.x;
    CRot.y = view->unk00C.y;
    CRot.z = 0.0f;
    CZoom = view->unk00C.z;
    return fn_1_2DD8;
}

/* 42 insns */
void fn_1_2DD8(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    fn_1_430(obj);
    switch (work->unk010) {
        case 0:
            fn_1_2AD4(HuDataSelHeapReadNum(0x3D0004, HU_MEMNUM_OVL, HEAP_MODEL));
            work->unk010 = 1;
            break;
        case 1:
            if (fn_1_2B4C() != 0) {
                break;
            }
            work->unk010 = 2;
        case 2:
            fn_1_5B0(obj);
        default:
            return;
    }
}

/* 80 insns */
OMOBJFUNC fn_1_2E80(OMOBJMAN *objman, OMOBJ *obj)
{
    M503_MAIN *work = obj->data;
    s32 score[4];
    s32 i;
    s32 max;
    s32 s;

    max = 0;
    for (i = 0; i < 4; i++) {
        s = fn_1_D778(i);
        if (s > max) {
            max = s;
        }
        score[i] = s;
    }
    work->unk058 = 0;
    work->unk05C = 0;
    for (i = 0; i < 4; i++) {
        work->unk048[i] = -1;
        if (max == score[i]) {
            work->unk048[i] = work->unk038[i];
            work->unk060[i] = work->unk058++;
        } else {
            work->unk060[i] = work->unk05C++;
        }
    }
    if (max == 0) {
        work->unk070 = 0;
    } else {
        work->unk070 = 1;
    }
    work->unk020 = 1;
    lbl_1_bss_28 = -1;
    return fn_1_2FC0;
}

/* 200 insns */
void fn_1_2FC0(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;
    float t;
    s32 i;
    s16 newCoin;
    s32 coin;

    fn_1_430(obj);
    switch (work->unk020) {
        case 1:
            work->unk024 = 0;
            work->unk020 = 2;
            break;
        case 2:
            if (fn_1_1BFC(2)) {
                lbl_1_data_60[1].unk000 = Center;
                lbl_1_data_60[1].unk00C.x = CRot.x;
                lbl_1_data_60[1].unk00C.y = CRot.y;
                lbl_1_data_60[1].unk00C.z = CZoom;
                work->unk020 = 3;
                work->unk024 = 0;
            }
            break;
        case 3:
            t = (1.0 / 18.0) * (float)work->unk024;
            if (t >= 1.0) {
                t = 1.0f;
                work->unk020 = 4;
                work->unk024 = 0;
            }
            if (work->unk070) {
                fn_1_32E0(1, 2, t);
            }
            break;
        case 4:
            if (!(work->unk024 < 12.0)) {
                if (!work->unk070) {
                    lbl_1_bss_28 = GameMesCreate(2, 2);
                    HuAudJinglePlay(123);
                } else {
                    lbl_1_bss_28 = GameMesCreate(4, 3, work->unk048[0], work->unk048[1], work->unk048[2], work->unk048[3]);
                    HuAudJinglePlay(121);
                    for (i = 0; i < 4; i++) {
                        if (work->unk048[i] >= 0) {
                            coin = GwPlayer[i].mgCoinBonus;
                            newCoin = coin + 10;
                            if (!_CheckFlag(FLAG_MG_PRACTICE)) {
                                GwPlayer[i].mgCoinBonus = newCoin;
                            }
                        }
                    }
                }
                work->unk020 = 5;
                work->unk024 = 0;
            }
            break;
        case 5:
            if (!(work->unk024 < 210.0)) {
                work->unk020 = 6;
                fn_1_5B0(obj);
            }
            break;
    }
}

/* 88 insns */
void fn_1_32E0(s32 from, s32 to, float t)
{
    M503_CAMVIEW *a;
    M503_CAMVIEW *b;
    HuVecF v;

    if (from < 0) {
        if (to < 0) {
            return;
        }
        from = to;
    }
    if (to < 0) {
        to = from;
    }
    a = &lbl_1_data_60[from];
    b = &lbl_1_data_60[to];
    PSVECSubtract(&b->unk000, &a->unk000, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->unk000, &v, &v);
    Center = v;
    PSVECSubtract(&b->unk00C, &a->unk00C, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->unk00C, &v, &v);
    CRot.x = v.x;
    CRot.y = v.y;
    CRot.z = 0.0f;
    CZoom = v.z;
}

