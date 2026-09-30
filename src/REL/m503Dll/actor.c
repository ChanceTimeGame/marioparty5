/*
 * m503dll actor.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/actor.s.
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
/* 0x668 */ /* float lbl_1_rodata_668 = 0.0f; */
/* 0x670 */ /* double lbl_1_rodata_670 = 0.5; */
/* 0x678 */ /* double lbl_1_rodata_678 = 3; */
/* 0x680 */ /* double lbl_1_rodata_680 = 0; */
/* 0x688 */ /* float lbl_1_rodata_688 = -1.0f; */
/* 0x690 */ /* double lbl_1_rodata_690 = 180; */
/* 0x698 */ /* double lbl_1_rodata_698 = 3.141592653589793; */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xD0 */ OMOBJ *lbl_1_bss_D0;

/* --- functions (reference order) --- */
/* 34 insns */
void fn_1_D7B0(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M503_ACTOR *work;

    obj = omAddObjEx(objman, 70, 0, 0, -1, fn_1_D83C);
    lbl_1_bss_D0 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_ACTOR), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M503_ACTOR));
}

/* 1 insns */
void fn_1_D838(void)
{
}

/* 4 insns */
void fn_1_D83C(OMOBJ *obj)
{
    obj->objFunc = fn_1_D84C;
}

/* 94 insns */
void fn_1_D84C(OMOBJ *obj)
{
    M503_ACTOR *work = obj->data;
    M503_ACTORENT *a;
    M503_ACTORENT *pa;
    M503_ACTORENT *b;
    M503_ACTORENT *pb;
    s32 i;
    s32 j;

    for (i = 0; i < 40; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if ((pa->unk000 & 1) && pa->unk00C == 0) {
                for (j = i + 1; j < 40; j++) {
                    b = work->unk000[j];
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk000 & 1) && pb->unk00C == 0) {
                            fn_1_D9C4(a, b);
                        }
                    }
                }
                for (j = 0; j < 8; j++) {
                    b = (M503_ACTORENT *)work->unk0A0[j]; /* retail reuses b for the box */
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk000 & 1)) {
                            switch (pb->unk00C) {
                                case 0:
                                    fn_1_DC6C(a, (M503_ACTORBOX *)b);
                                    break;
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 40; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if (pa->unk014 != NULL) {
                pa->unk014(pa->unk010);
            }
        }
    }
}

/* 170 insns */
s32 fn_1_D9C4(M503_ACTORENT *a, M503_ACTORENT *b)
{
    HuVecF *pa = a->unk018;
    HuVecF *pb = b->unk018;
    float dx = pa->x - pb->x;
    float dz = pa->z - pb->z;
    float dist = sqrtf(dx * dx + dz * dz);
    float sum = a->unk01C + b->unk01C;
    HuVecF mid;

    if (sum > dist) {
        if (0.0 == dist) {
            dx = 0.0f;
            dz = -1.0f;
        } else {
            dx /= dist;
            dz /= dist;
        }
        mid.x = pa->x + 0.5 * (pb->x - pa->x);
        mid.z = pa->z + 0.5 * (pb->z - pa->z);
        dist = 0.5 * sum;
        pa->x = mid.x + dx * dist;
        pa->z = mid.z + dz * dist;
        pb->x = mid.x - dx * dist;
        pb->z = mid.z - dz * dist;
        return 1;
    }
    return 0;
}

/* 177 insns */
s32 fn_1_DC6C(M503_ACTORENT *a, M503_ACTORBOX *b)
{
    float dx = a->unk018->x - b->unk000.unk018->x;
    float dz = a->unk018->z - b->unk000.unk018->z;
    float angle;
    float dist = sqrtf(dx * dx + dz * dz);
    float sum = a->unk01C + b->unk000.unk01C;

    if ((b->unk020 != 0 && dist > sum) || (b->unk020 == 0 && dist < sum)) {
        angle = 180.0 * (atan2(dx, dz) / M_PI);
        a->unk018->x = b->unk000.unk018->x + sum * sin(M_PI * angle / 180.0);
        a->unk018->z = b->unk000.unk018->z + sum * cos(M_PI * angle / 180.0);
        return 1;
    }
    return 0;
}

/* 30 insns */
s32 fn_1_DF30(M503_ACTORENT *ent)
{
    OMOBJ *obj = lbl_1_bss_D0;
    M503_ACTOR *work = obj->data;
    M503_ACTORENT **slot = work->unk000;
    s32 i;

    for (i = 0; i < 40; i++, slot++) {
        if (*slot == NULL) {
            *slot = ent;
            return i;
        }
    }
    return -1;
}

/* 30 insns */
s32 fn_1_DFA8(M503_ACTORBOX *box)
{
    OMOBJ *obj = lbl_1_bss_D0;
    M503_ACTOR *work = obj->data;
    M503_ACTORBOX **slot = work->unk0A0;
    s32 i;

    for (i = 0; i < 8; i++, slot++) {
        if (*slot == NULL) {
            *slot = box;
            return i + 40;
        }
    }
    return -1;
}

/* 25 insns */
void fn_1_E020(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_D0;
    M503_ACTOR *work = obj->data;

    if (idx >= 0) {
        if (idx < 40) {
            work->unk000[idx] = NULL;
        }
        idx -= 40;
        if (idx < 8) {
            work->unk0A0[idx] = NULL;
        }
    }
}

