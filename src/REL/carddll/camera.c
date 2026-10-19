/*
 * carddll camera.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/camera.s.
 */

#include "REL/carddll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_518 = 0.0f; /* 0x518 */
static const float lbl_1_rodata_51C = 640.0f; /* 0x51C */
static const float lbl_1_rodata_520 = 480.0f; /* 0x520 */
static const float lbl_1_rodata_524 = 1.0f; /* 0x524 */
static const float lbl_1_rodata_528 = 20.0f; /* 0x528 */
static const float lbl_1_rodata_52C = 30000.0f; /* 0x52C */
static const float lbl_1_rodata_530 = 1.2f; /* 0x530 */
static const float lbl_1_rodata_534 = 300.0f; /* 0x534 */
static const float lbl_1_rodata_538 = 5000.0f; /* 0x538 */
static const float lbl_1_rodata_53C = 150.0f; /* 0x53C */
static const float lbl_1_rodata_540 = 100.0f; /* 0x540 */
static const float lbl_1_rodata_544 = 1500.0f; /* 0x544 */
static const float lbl_1_rodata_548 = 3000.0f; /* 0x548 */
static const float lbl_1_rodata_54C = 1000.0f; /* 0x54C */
static const float lbl_1_rodata_550 = 2500.0f; /* 0x550 */
static const float lbl_1_rodata_554 = 500.0f; /* 0x554 */
static const float lbl_1_rodata_558 = 2000.0f; /* 0x558 */
static const float lbl_1_rodata_55C = 180.0f; /* 0x55C */
static const float lbl_1_rodata_560 = -90.0f; /* 0x560 */
static const float lbl_1_rodata_564 = 200.0f; /* 0x564 */
static const float lbl_1_rodata_568 = 1800.0f; /* 0x568 */
static const float lbl_1_rodata_56C = 80.0f; /* 0x56C */
static const float lbl_1_rodata_570 = 50.0f; /* 0x570 */
static const float lbl_1_rodata_574 = 4000.0f; /* 0x574 */
static const float lbl_1_rodata_578 = 0.6f; /* 0x578 */
static const float lbl_1_rodata_57C = 60.0f; /* 0x57C */
/* 0x580 lbl_1_rodata_580 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_588 = 120.0f; /* 0x588 */
static const double lbl_1_rodata_590 = 3.141592653589793; /* 0x590 */
static const float lbl_1_rodata_598 = 90.0f; /* 0x598 */
static const double lbl_1_rodata_5A0 = 180.0; /* 0x5A0 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x11B4 */ s32 lbl_1_bss_11B4;
/* 0x11B0 */ s32 lbl_1_bss_11B0;
/* 0x11AC */ float lbl_1_bss_11AC;
/* 0x11A8 */ float lbl_1_bss_11A8;
/* 0x119C */ HuVecF lbl_1_bss_119C;
/* 0x1190 */ HuVecF lbl_1_bss_1190;
/* 0x1184 */ HuVecF lbl_1_bss_1184;
/* 0x1178 */ HuVecF lbl_1_bss_1178;
/* 0x1174 */ s32 lbl_1_bss_1174;
/* 0x1168 */ s32 lbl_1_bss_1168[3];

/* --- functions (reference order), .data placed before its first user --- */
/* 0x7B8 */ HuVecF lbl_1_data_7B8 = { -50.0f, 3000.0f, 3000.0f };
/* 0x7C4 */ HuVecF lbl_1_data_7C4 = { 0.0f, 1.0f, 0.0f };
/* 0x7D0 */ HuVecF lbl_1_data_7D0 = { -50.0f, 0.0f, 0.0f };

/* 103 insns */
void fn_1_30E08(void)
{
    Hu3DCameraCreate(1);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 20.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraPosSetV(1, &lbl_1_data_7B8, &lbl_1_data_7C4, &lbl_1_data_7D0);
    Hu3DCameraCreate(2);
    Hu3DCameraViewportSet(2, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(2, 20.0f, 20.0f, 30000.0f, 1.2f);
    Hu3DCameraPosSetV(2, &lbl_1_data_7B8, &lbl_1_data_7C4, &lbl_1_data_7D0);
    lbl_1_bss_11B4 = 0;
    lbl_1_bss_11B0 = 0;
}

/* 475 insns */
s32 fn_1_30FA4(s32 mode, void *arg)
{
    HuVecF posStart;
    HuVecF pos;
    HuVecF targetStart;
    HuVecF target;
    CardGameWork *work;
    CardPlayerWork *player;
    HuVecF *vec;
    s32 ret;

    ret = 0;
    if (mode < 9 && arg != 0) {
        work = arg;
        player = &work->player[work->unk174[work->unk170]];
    }
    if (lbl_1_bss_11B4 == 0) {
        fn_1_31AC0(&posStart, &targetStart);
        switch (mode) {
            case 0:
            default:
                pos.x = 300.0f;
                pos.y = 5000.0f + (work->unk194 - 6) * 800;
                pos.z = 5000.0f;
                target.x = pos.x;
                target.y = 0.0f;
                target.z = 0.0f;
                break;
            case 1:
                fn_1_9C74(&target, player->unk10, player->unk14, 1, 1);
                target.x += 150.0f;
                target.y += 100.0f;
                pos.x = target.x;
                pos.y = 1500.0f + target.y;
                pos.z = 3000.0f + target.z;
                break;
            case 2:
                fn_1_9DA8(&target, work);
                target.x += 100.0f;
                pos.x = target.x;
                pos.y = 1000.0f + target.y;
                pos.z = 2500.0f + target.z;
                break;
            case 3:
            case 8:
                fn_1_9DA8(&target, work);
                target.x += 100.0f;
                pos.x = 500.0f + target.x;
                pos.y = 1500.0f + target.y;
                pos.z = 2000.0f + target.z;
                break;
            case 4:
                fn_1_9DA8(&target, work);
                if (180.0f == player->unk18) {
                    target.z -= 100.0f;
                } else if (0.0f == player->unk18) {
                    target.z += 100.0f;
                } else if (-90.0f == player->unk18) {
                    target.x -= 100.0f;
                } else {
                    target.x += 100.0f;
                }
                target.y += 200.0f;
                pos.x = target.x;
                pos.y = 500.0f + target.y;
                pos.z = 1800.0f + target.z;
                break;
            case 5:
                fn_1_9C74(&target, player->unk10, player->unk14, 1, 1);
                target.x += 20.0f;
                pos.x = target.x;
                pos.y = 2500.0f + target.y;
                pos.z = 100.0f + target.z;
                break;
            case 6:
                fn_1_9C74(&target, player->unk10, player->unk14, 1, 1);
                target.x += 80.0f;
                pos.x = target.x;
                pos.y = 2500.0f + target.y;
                pos.z = 100.0f + target.z;
                break;
            case 7:
                fn_1_9DA8(&target, work);
                target.x += 100.0f;
                target.y += 300.0f;
                pos.x = target.x;
                pos.y = 100.0f + target.y;
                pos.z = 2500.0f + target.z;
                break;
            case 9:
                vec = arg;
                target.x = vec->x;
                target.y = vec->y;
                target.z = vec->z;
                target.y += 300.0f;
                pos.x = target.x;
                pos.y = 50.0f + target.y;
                pos.z = 2500.0f + target.z;
                break;
            case 10:
                vec = arg;
                target.x = vec->x;
                target.y = vec->y;
                target.z = vec->z;
                target.y += 300.0f;
                pos.x = target.x;
                pos.y = 2500.0f + target.y;
                pos.z = 100.0f + target.z;
                break;
            case 11:
                vec = arg;
                target.x = vec->x;
                target.y = vec->y;
                target.z = vec->z;
                target.x += 100.0f;
                target.y += 300.0f;
                pos.x = target.x;
                pos.y = 2500.0f + target.y;
                pos.z = 4000.0f + target.z;
                break;
        }
        fn_1_317F0(&posStart, &pos, &targetStart, &target);
        lbl_1_bss_11B4 = 1;
    } else if (mode == 5 || mode == 6) {
        if (fn_1_31F84()) {
            lbl_1_bss_11B4 = 0;
            ret = 1;
        }
    } else if (mode == 8) {
        if (fn_1_319D4(lbl_1_bss_11A8)) {
            lbl_1_bss_11B4 = 0;
            ret = 1;
        } else {
            lbl_1_bss_11A8 -= 0.6f;
            if (lbl_1_bss_11A8 < 60.0f) {
                lbl_1_bss_11A8 = 60.0f;
            }
        }
    } else if (fn_1_318E4()) {
        lbl_1_bss_11B4 = 0;
        ret = 1;
    }
    return ret;
}

/* 30 insns */
void fn_1_31710(HuVecF *pos)
{
    lbl_1_data_7B8.x = pos->x;
    lbl_1_data_7B8.y = pos->y;
    lbl_1_data_7B8.z = pos->z;
    Hu3DCameraPosSetV(1, &lbl_1_data_7B8, &lbl_1_data_7C4, &lbl_1_data_7D0);
}

/* 26 insns */
void fn_1_31788(HuVecF *target)
{
    lbl_1_data_7D0.x = target->x;
    lbl_1_data_7D0.z = target->z;
    Hu3DCameraPosSetV(1, &lbl_1_data_7B8, &lbl_1_data_7C4, &lbl_1_data_7D0);
}

/* 61 insns */
void fn_1_317F0(HuVecF *posStart, HuVecF *posEnd, HuVecF *targetStart, HuVecF *targetEnd)
{
    lbl_1_bss_119C = *posStart;
    lbl_1_bss_1190 = *posEnd;
    lbl_1_bss_1184 = *targetStart;
    lbl_1_bss_1178 = *targetEnd;
    lbl_1_data_7B8 = *posStart;
    lbl_1_data_7D0 = *targetStart;
    lbl_1_bss_11AC = 0.0f;
    lbl_1_bss_11A8 = 120.0f;
}

/* 60 insns */
s32 fn_1_318E4(void)
{
    s32 ret = 0;

    lbl_1_bss_11AC += 1.0f;
    if (fn_1_31C60(lbl_1_bss_11AC / 60.0f, &lbl_1_data_7C4)) {
        lbl_1_bss_11AC = 0.0f;
        lbl_1_data_7B8 = lbl_1_bss_1190;
        lbl_1_data_7D0 = lbl_1_bss_1178;
        ret = 1;
    }
    return ret;
}

/* 59 insns */
s32 fn_1_319D4(float speed)
{
    s32 ret = 0;

    lbl_1_bss_11AC += 1.0f;
    if (fn_1_31C60(lbl_1_bss_11AC / speed, &lbl_1_data_7C4)) {
        lbl_1_bss_11AC = 0.0f;
        lbl_1_data_7B8 = lbl_1_bss_1190;
        lbl_1_data_7D0 = lbl_1_bss_1178;
        ret = 1;
    }
    return ret;
}

/* 17 insns */
void fn_1_31AC0(HuVecF *pos, HuVecF *target)
{
    *pos = lbl_1_data_7B8;
    *target = lbl_1_data_7D0;
}

/* 87 insns */
void fn_1_31B04(float t, HuVecF *start, HuVecF *end, HuVecF *out)
{
    float s;

    if (1.0f < t) {
        t = 1.0f;
    }
    s = sin(M_PI * (90.0f * t) / 180.0) * sin(M_PI * (90.0f * t) / 180.0);
    out->x = start->x + s * (end->x - start->x);
    out->y = start->y + s * (end->y - start->y);
    out->z = start->z + s * (end->z - start->z);
}

/* 201 insns */
s32 fn_1_31C60(float t, HuVecF *up)
{
    HuVecF pos;
    HuVecF target;

    fn_1_31B04(t, &lbl_1_bss_119C, &lbl_1_bss_1190, &pos);
    fn_1_31B04(t, &lbl_1_bss_1184, &lbl_1_bss_1178, &target);
    Hu3DCameraPosSetV(1, &pos, up, &target);
    if (1.0f <= t) {
        return 1;
    }
    return 0;
}

/* 80 insns */
s32 fn_1_31F84(void)
{
    s32 ret = 0;

    lbl_1_bss_11AC += 1.0f;
    if (fn_1_3224C(lbl_1_bss_11AC / 60.0f, &lbl_1_data_7C4, lbl_1_bss_11B0)) {
        lbl_1_bss_11AC = 0.0f;
        lbl_1_data_7B8 = lbl_1_bss_1190;
        lbl_1_data_7D0 = lbl_1_bss_1178;
        if (lbl_1_bss_11B0 != 0) {
            lbl_1_bss_11B0 = 0;
            ret = 1;
        } else {
            lbl_1_bss_11B0++;
        }
    }
    return ret;
}

/* 98 insns */
void fn_1_320C4(float t, HuVecF *start, HuVecF *end, HuVecF *out, s32 mode)
{
    float s;

    if (1.0f < t) {
        t = 1.0f;
    }
    s = sin(M_PI * (90.0f * t) / 180.0) * sin(M_PI * (90.0f * t) / 180.0);
    if (mode == 0) {
        out->x = start->x + s * (end->x - start->x);
        out->y = start->y;
        out->z = start->z;
    } else {
        out->x = end->x;
        out->y = start->y + s * (end->y - start->y);
        out->z = start->z + s * (end->z - start->z);
    }
}

/* 234 insns */
s32 fn_1_3224C(float t, HuVecF *up, s32 mode)
{
    HuVecF pos;
    HuVecF target;

    fn_1_320C4(t, &lbl_1_bss_119C, &lbl_1_bss_1190, &pos, mode);
    fn_1_320C4(t, &lbl_1_bss_1184, &lbl_1_bss_1178, &target, mode);
    Hu3DCameraPosSetV(1, &pos, up, &target);
    if (1.0f <= t) {
        return 1;
    }
    return 0;
}
