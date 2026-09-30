/*
 * m580Dll puck.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/puck.s.
 */

#include "REL/m580Dll.h"

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
/* 0x538 */ /* float lbl_1_rodata_538 = 1.0f; */
/* 0x53C */ /* float lbl_1_rodata_53C = -1.0f; */
/* 0x540 */ /* float lbl_1_rodata_540 = 40.0f; */
/* 0x544 */ /* float lbl_1_rodata_544 = 0.98f; */
/* 0x548 */ /* double lbl_1_rodata_548 = 30; */
/* 0x550 */ /* float lbl_1_rodata_550 = 0.8f; */
/* 0x558 */ /* double lbl_1_rodata_558 = 0.99; */
/* 0x560 */ /* double lbl_1_rodata_560 = 1.3333334028720856; */
/* 0x568 */ /* double lbl_1_rodata_568 = 0; */
/* 0x570 */ /* float lbl_1_rodata_570 = 0.0f; */
/* 0x578 */ /* double lbl_1_rodata_578 = 0.5; */
/* 0x580 */ /* double lbl_1_rodata_580 = 3.333333507180214; */
/* 0x588 */ /* double lbl_1_rodata_588 = 50.00000260770321; */
/* 0x590 */ /* double lbl_1_rodata_590 = 180; */
/* 0x598 */ /* double lbl_1_rodata_598 = 4503601774854144; */
/* 0x5A0 */ /* double lbl_1_rodata_5A0 = 3.141592653589793; */
/* 0x5A8 */ /* double lbl_1_rodata_5A8 = 360; */
/* 0x5B0 */ /* float lbl_1_rodata_5B0 = 360.0f; */
/* 0x5B8 */ /* double lbl_1_rodata_5B8 = 3; */

/* --- .data --- */
/* 0x778 */ char lbl_1_data_778[2][8] = { "goal_L", "goal_R" };
/* 0x788 */ HuVecF lbl_1_data_788 = { 0.0f, 0.0f, 0.0f };
/* 0x794 */ HuVecF lbl_1_data_794 = { 0.0f, 0.0f, 0.0f };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x240 */ OMOBJ *lbl_1_bss_240; /* the puck object; dtk size 0x8 is alignment */

/* sqrtf with 0.5/3.0 pooled as ordinary literals (m574 stage.c StageSqrtF precedent) */
static inline float PuckSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* --- functions (reference order) --- */

/* 40 insns. Puck object and its 0x11C work. */
void fn_1_C8F8(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_PUCK *work;

    obj = omAddObjEx(objman, 40, 0, 0, -1, fn_1_C99C);
    lbl_1_bss_240 = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_PUCK), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_PUCK));
    obj->work[0] = 0;
}

/* 1 insns. Empty. */
void fn_1_C998(void)
{
}

/* 140 insns. Puck init: model, shadow, collision actor, goal obstacles. */
void fn_1_C99C(OMOBJ *obj)
{
    M580_COLLACTOR *hit;
    M580_PUCK *work;
    HU3DMODELID mdlId;
    s32 i;
    HU3DMODELID linkId;
    M580_COLLOBJ *goal;
    HSFOBJECT *hsfObj;

    work = lbl_1_bss_240->data;
    work->unk008 = 1;
    work->unk024 = lbl_1_data_788;
    work->unk030 = lbl_1_data_794;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860009, HU_MEMNUM_OVL, HEAP_MODEL));
    work->unk020 = mdlId;
    Hu3DModelLayerSet(mdlId, 5);
    linkId = Hu3DModelLink(mdlId);
    work->unk022 = linkId;
    Hu3DModelLayerSet(linkId, 1);
    Hu3DModelScaleSet(linkId, 1.0f, -1.0f, 1.0f);
    Hu3DModelAttrSet(linkId, HU3D_ATTR_CULL_FRONT);
    hit = &work->unk05C;
    hit->unk000 = 0;
    hit->unk004 = 10;
    hit->unk008 = 1;
    hit->unk00C = 0;
    hit->unk010 = 0;
    hit->unk014 = obj;
    hit->unk018 = (void (*)(void *))fn_1_CF94;
    hit->unk01C = (M580_COLLHITFUNC)fn_1_D018;
    hit->unk020 = &work->unk024;
    hit->unk024 = &work->unk030;
    hit->unk028 = work->unk024;
    hit->unk034 = 40.0f;
    hit->unk038 = 1.0f;
    fn_1_11DC4(hit);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x860011, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 2; i++) {
        hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_778[i]);
        if (hsfObj != NULL) {
            goal = &work->unk09C[i];
            fn_1_1229C(goal, hsfObj);
            fn_1_122D0(goal);
        }
    }
    obj->objFunc = fn_1_CBCC;
}

/* 242 insns. Puck per frame. */
void fn_1_CBCC(OMOBJ *obj)
{
    M580_PUCK *work;
    s32 i;
    s16 mdlId;

    work = obj->data;
    mdlId = work->unk020;
    switch (work->unk014) {
        case 0:
            break;
        case 1:
            if (work->unk00C != 0) {
                break;
            }
            work->unk014++;
            work->unk01C = 0;
        case 2:
            /* retail: scales the position, not the velocity (drifts the dead puck toward the origin) */
            PSVECScale(&work->unk024, &work->unk024, 0.98f);
            if (++work->unk01C < 30.0) {
                break;
            }
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk014++;
            work->unk008 = 0;
            work->unk05C.unk000 |= 1;
            fn_1_D68C();
        case 3:
            for (i = 0; i < 2; i++) {
                if (fn_1_126C8(&work->unk09C[i], &work->unk024)) {
                    work->unk014++;
                    work->unk01C = 0;
                    work->unk008 = 1;
                    work->unk03C = NULL;
                    work->unk040 = 0;
                    work->unk010 = i ^ 1;
                    fn_1_10F58(work->unk010, 1);
                }
            }
            if (MgSeqModeGet() != 5) {
                PSVECScale(&work->unk030, &work->unk030, 0.8f);
            }
            break;
        case 4:
            work->unk03C = NULL;
            work->unk040 = 0;
            PSVECScale(&work->unk030, &work->unk030, 0.8f);
            break;
    }
    if (work->unk00C == 0) {
        if (work->unk03C != NULL) {
            work->unk040++;
        }
        work->unk030.x *= 0.99;
        work->unk030.y -= 1.3333334028720856;
        work->unk030.z *= 0.99;
        PSVECAdd(&work->unk024, &work->unk030, &work->unk024);
        if (work->unk024.y < 0.0) {
            work->unk024.y = 0.0f;
            work->unk030.y = 0.5 * work->unk030.y;
            if (work->unk030.y < 3.333333507180214) {
                work->unk030.y = 0.0f;
            }
        } else if (work->unk008 == 0) {
            if (PSVECMag(&work->unk030) > 50.00000260770321) {
                fn_1_EC74(&work->unk024, &work->unk030);
            }
        }
    }
    if (++work->unk048 > 180.0) {
        work->unk044 = 0;
    }
    if (MgSeqModeGet() == 5) {
        fn_1_EDF8(work->unk044);
    } else {
        fn_1_EDF8(0);
    }
    if (MgSeqModeGet() == 5 && work->unk000 == 0 && work->unk004 != 0) {
        fn_1_212C(0x963, &work->unk024);
    }
    work->unk000 = work->unk004;
    work->unk004 = 0;
    work->unk018++;
}

/* 33 insns. Collision actor post-pass: place the models. */
void fn_1_CF94(OMOBJ *obj)
{
    M580_PUCK *work = obj->data;

    if (work->unk00C == 0) {
        Hu3DModelPosSetV(work->unk020, &work->unk024);
        fn_1_1908(&work->unk024);
    }
    Hu3DModelPosSet(work->unk022, work->unk024.x, -work->unk024.y, work->unk024.z);
    work->unk05C.unk028 = work->unk024;
}

/* 15 insns. Collision actor hit callback. */
s32 fn_1_D018(M580_COLLACTOR *self, M580_COLLACTOR *other)
{
    OMOBJ *obj = self->unk014;
    M580_PUCK *work = obj->data;

    if (other->unk008 == 3) {
        work->unk004 = 1;
    }
    return 1;
}

/* 174 insns. Is the puck within radius of pos, and within +-range degrees of angle? */
s32 fn_1_D054(HuVecF *pos, float angle, float range, float radius)
{
    M580_PUCK *work;
    float dx;
    float dz;
    float ang;

    work = lbl_1_bss_240->data;
    if (work->unk008 != 0) {
        return 0;
    }
    dx = work->unk024.x - pos->x;
    dz = work->unk024.z - pos->z;
    if (range < 180.0) {
        ang = 180.0 * (atan2(dx, dz) / M_PI);
        ang = fmodf(ang - angle, 360.0f);
        if (ang < 0.0f) {
            ang += 360.0f;
        }
        if (ang > range && ang < 360.0f - range) {
            return 0;
        }
    }
    ang = PuckSqrtF(dx * dx + dz * dz);
    if (ang > radius) {
        return 0;
    }
    return 1;
}

/* 33 insns. Puck position/velocity; returns the last toucher, NULL when dead. */
OMOBJ *fn_1_D30C(HuVecF *pos, HuVecF *vel)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    if (pos != NULL) {
        *pos = work->unk024;
    }
    if (vel != NULL) {
        *vel = work->unk030;
    }
    if (work->unk008 != 0) {
        return NULL;
    }
    return work->unk03C;
}

/* 109 insns. Hit the puck: pull toward pos by t, set velocity, record toucher. */
OMOBJ *fn_1_D390(HuVecF *pos, float t, HuVecF *vel, OMOBJ *player)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    if (work->unk008 != 0) {
        work->unk03C = NULL;
        work->unk040 = 0;
        return NULL;
    }
    if (pos != NULL) {
        work->unk024.x = work->unk024.x + t * (pos->x - work->unk024.x);
        work->unk024.y = work->unk024.y + t * (pos->y - work->unk024.y);
        work->unk024.z = work->unk024.z + t * (pos->z - work->unk024.z);
    }
    if (vel != NULL) {
        work->unk030 = *vel;
        if (pos != NULL && (0.0 != vel->x || 0.0 != vel->z)) {
            fn_1_212C(0x962, pos);
        }
    }
    if (player != NULL) {
        if (work->unk03C != player) {
            if (work->unk03C == NULL || work->unk040 > 5) {
                work->unk03C = player;
                work->unk040 = 0;
            }
        }
    } else {
        work->unk03C = NULL;
        work->unk040 = 0;
    }
    return work->unk03C;
}

/* 10 insns. Is the puck dead? */
s32 fn_1_D544(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    return work->unk008;
}

/* 40 insns. Pick the puck up: hold, stop, hide at the origin. */
s16 fn_1_D56C(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    work->unk014 = 1;
    work->unk00C = 1;
    work->unk03C = NULL;
    work->unk05C.unk000 &= ~1;
    work->unk030.x = work->unk030.y = work->unk030.z = 0.0f;
    Hu3DModelPosSet(work->unk020, 0.0f, 0.0f, 0.0f);
    return work->unk020;
}

/* 18 insns. Place a held puck. */
void fn_1_D60C(HuVecF *pos)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    if (work->unk00C != 0) {
        work->unk024 = *pos;
    }
}

/* 14 insns. Release the puck. */
void fn_1_D654(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    if (work->unk00C != 0) {
        work->unk00C = 0;
    }
}

/* 24 insns. Reset the per-player touch counts and set the hot flag. */
void fn_1_D68C(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;
    s32 i;

    work->unk044 = 1;
    work->unk048 = 0;
    for (i = 0; i < 4; i++) {
        work->unk04C[i] = 0;
    }
}

/* 10 insns. Hot flag. */
s32 fn_1_D6EC(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    return work->unk044;
}

/* 41 insns. Count a touch by player; the fifth clears the hot flag. */
s32 fn_1_D714(OMOBJ *player)
{
    M580_PUCK *work = lbl_1_bss_240->data;
    s32 playerNo = fn_1_7E2C(player);

    if (work->unk044 == 0) {
        return 0;
    }
    work->unk03C = player;
    work->unk040 = 0;
    if (++work->unk04C[playerNo] >= 5) {
        work->unk044 = 0;
        return 1;
    }
    return 0;
}

/* 10 insns. Scoring team. */
s32 fn_1_D7B8(void)
{
    M580_PUCK *work = lbl_1_bss_240->data;

    return work->unk010;
}
