/*
 * m516dll camera.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m516Dll/asm/REL/m516Dll/camera.s.
 */

#include "REL/m516Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"


/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x58 */ /* float lbl_1_rodata_58 = 0.0f; */
/* 0x60 */ /* double lbl_1_rodata_60 = 102; */
/* 0x68 */ /* double lbl_1_rodata_68 = 0.007246376811594203; */
/* 0x70 */ /* double lbl_1_rodata_70 = 1; */
/* 0x78 */ /* float lbl_1_rodata_78 = 1.0f; */
/* 0x80 */ /* double lbl_1_rodata_80 = 4503599627370496; */
/* 0x88 */ /* double lbl_1_rodata_88 = 0.05555555555555555; */
/* 0x90 */ /* double lbl_1_rodata_90 = 12; */
/* 0x98 */ /* double lbl_1_rodata_98 = 210; */

/* --- .data --- */
/* 0x50 */ M516_CAMVIEW lbl_1_data_50[3] = {
    { { 0.0f, 230.0f, 0.0f }, { -2.0f, 0.0f, 250.0f } },
    { { 0.0f, 600.0f, 0.0f }, { -2.5f, 0.0f, 1950.0f } },
    { { 0.0f, 800.0f, 0.0f }, { -2.5f, 0.0f, 2500.0f } },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x24 gap_05_00000024_bss (0x4) -- dtk filler */
/* 0x20 */ s32 lbl_1_bss_20;

/* --- functions (reference order) --- */
/* 35 insns */
OMOBJFUNC fn_1_1F04(OMOBJMAN *objman)
{
    M516_CAMVIEW *view = &lbl_1_data_50[0];

    Center = view->center;
    CRot.x = view->rot.x;
    CRot.y = view->rot.y;
    CRot.z = 0.0f;
    CZoom = view->rot.z;
    return fn_1_1F90;
}

/* 94 insns */
void fn_1_1F90(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;
    float t;

    fn_1_410(obj);
    switch (work->unk010) {
        case 0:
            work->unk010 = 1;
            work->unk014 = 0;
            break;
        case 1:
            if (!(work->unk014 < 102.0)) {
                work->unk010 = 2;
                work->unk014 = 0;
            }
            break;
        case 2:
            t = (1.0 / 138.0) * (float)work->unk014;
            if (t >= 1.0) {
                t = 1.0f;
            }
            fn_1_23EC(0, 1, t);
            if (!(t < 1.0)) {
                work->unk010 = 3;
                work->unk014 = 0;
            }
            break;
        case 3:
            fn_1_524(obj);
        default:
            return;
    }
}

/* 47 insns */
OMOBJFUNC fn_1_2108(OMOBJMAN *objman, OMOBJ *obj)
{
    M516_MAIN *work = obj->data;
    s32 unused = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (fn_1_8088(i)) {
            work->unk048[i] = work->unk038[i];
        } else {
            work->unk048[i] = -1;
        }
    }
    work->unk058 = 0;
    work->unk020 = 1;
    lbl_1_bss_20 = -1;
    return fn_1_21C4;
}

/* 138 insns */
void fn_1_21C4(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;
    float t;
    s32 i;
    s32 total;
    s32 score;
    s16 newCoin;
    s32 coin;

    fn_1_410(obj);
    switch (work->unk020) {
        case 1:
            work->unk024 = 0;
            work->unk020 = 2;
            break;
        case 2:
            t = (1.0 / 18.0) * (float)work->unk024;
            if (t >= 1.0) {
                t = 1.0f;
                work->unk020 = 3;
                work->unk024 = 0;
            }
            fn_1_23EC(1, 2, t);
            break;
        case 3:
            if (!(work->unk024 < 12.0)) {
                work->unk020 = 4;
                work->unk024 = 0;
                total = 0;
                for (i = 0; i < 4; i++) {
                    if (work->unk048[i] >= 0) {
                        score = fn_1_8088(i);
                        total += score;
                        coin = GwPlayer[i].mgCoin;
                        newCoin = score + coin;
                        GwPlayer[i].mgCoin = newCoin;
                    }
                }
                if (total > 0) {
                    HuAudJinglePlay(121);
                } else {
                    HuAudJinglePlay(123);
                }
            }
            break;
        case 4:
            if (!(work->unk024 < 210.0)) {
                work->unk020 = 5;
                fn_1_524(obj);
            }
            break;
    }
}

/* 88 insns */
void fn_1_23EC(s32 from, s32 to, float t)
{
    M516_CAMVIEW *a;
    M516_CAMVIEW *b;
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
    a = &lbl_1_data_50[from];
    b = &lbl_1_data_50[to];
    PSVECSubtract(&b->center, &a->center, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->center, &v, &v);
    Center = v;
    PSVECSubtract(&b->rot, &a->rot, &v);
    PSVECScale(&v, &v, t);
    PSVECAdd(&a->rot, &v, &v);
    CRot.x = v.x;
    CRot.y = v.y;
    CRot.z = 0.0f;
    CZoom = v.z;
}

