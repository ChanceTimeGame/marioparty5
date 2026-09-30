/*
 * m516dll actor.c -- the overlay's collision registry. Functions are in
 * reference order. Line ranges are into
 * build/mp5-asm/m516Dll/asm/REL/m516Dll/actor.s.
 *
 * The unit owns one OMOBJ (lbl_1_bss_50) whose 0x11C work holds two arrays of
 * M516_ACTOR pointers: four characters and 0x43 scenery boxes. Its object
 * function resolves character-vs-character and character-vs-box overlap every
 * frame; the rest of the unit is the registry API the other units call.
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

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x50 */ OMOBJ *lbl_1_bss_50;

/* --- functions (reference order) --- */

/* asm 9-44, 34 insns. Actor object and its 0x11C registry work. */
void fn_1_80C0(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M516_ACTORWORK *work;

    obj = omAddObjEx(objman, 40, 0, 0, -1, fn_1_814C);
    lbl_1_bss_50 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_ACTORWORK), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M516_ACTORWORK));
}

/* asm 47-49, 1 insn. Empty. */
void fn_1_8148(void)
{
}

/* asm 52-57, 4 insns. Actor object init. */
void fn_1_814C(OMOBJ *obj)
{
    obj->objFunc = fn_1_815C;
}

/* asm 60-186, 110 insns. Per-frame collision pass. */
void fn_1_815C(OMOBJ *obj)
{
    M516_ACTORWORK *work = obj->data;
    M516_ACTOR *a;
    M516_ACTOR *pa;
    M516_ACTOR *b;
    M516_ACTOR *pb;
    s32 i;
    s32 j;

    for (i = 0; i < 4; i++) {
        a = work->unk000[i];
        if (a != NULL && a->unk0C == 0) {
            a->unk28.i = 0;
            a->unk2C.i = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if ((pa->unk00 & 1) && pa->unk0C == 0) {
                for (j = i + 1; j < 4; j++) {
                    b = work->unk000[j];
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk00 & 1) && pb->unk0C == 0) {
                            fn_1_8314(a, b);
                        }
                    }
                }
                for (j = 0; j < 0x43; j++) {
                    b = work->unk010[j];
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk00 & 1) && pb->unk0C == 0) {
                            fn_1_86E8(a, b);
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 4; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if (pa->unk14 != NULL) {
                pa->unk14(pa->unk10);
            }
        }
    }
}

/* asm 189-252, 58 insns. Character vs character, retrying across the X wrap. */
s32 fn_1_8314(M516_ACTOR *a, M516_ACTOR *b)
{
    if (fn_1_83FC(a, b, 0.0f)) {
        return 1;
    }
    if (b->unk18->x < -1000.0) {
        if (fn_1_83FC(a, b, 2200.0f)) {
            return 1;
        }
    }
    if (b->unk18->x > 1000.0) {
        if (fn_1_83FC(a, b, -2200.0f)) {
            return 1;
        }
    }
    return 0;
}

/* asm 255-450, 187 insns. Character vs character overlap resolution. */
s32 fn_1_83FC(M516_ACTOR *a, M516_ACTOR *b, f32 dx)
{
    HuVecF *pos = a->unk18;
    HuVecF other;
    f32 mid;
    s32 dir;
    f32 sign;

    other.x = b->unk18->x + dx;
    other.y = b->unk18->y;
    other.z = b->unk18->z;
    if (!(pos->x - a->unk24 > other.x + b->unk24 || pos->x + a->unk24 < other.x - b->unk24 ||
          pos->y > other.y + b->unk20 || pos->y + a->unk20 < other.y)) {
        mid = pos->x + 0.5 * (other.x - pos->x);
        if (pos->x > other.x) {
            dir = 1;
        } else {
            dir = -1;
        }
        sign = dir;
        /* Close enough vertically: push both apart about the midpoint. */
        if (fabs(pos->y - other.y) < 0.25 * (a->unk20 + b->unk20)) {
            pos->x = mid + sign * a->unk24;
            b->unk18->x = b->unk18->x + ((mid - sign * b->unk24) - other.x);
        }
        /* Still overlapping in X: whoever is falling stomps the other. */
        if (fabs(pos->x - other.x) < 0.5 * (a->unk24 + b->unk24)) {
            if (a->unk1C->y < 0.0f) {
                if (pos->y > other.y) {
                    a->unk28.i = 1;
                    a->unk30.o = b->unk10;
                    b->unk2C.i = 1;
                    b->unk30.o = a->unk10;
                }
            }
            if (b->unk1C->y < 0.0f) {
                if (other.y > pos->y) {
                    b->unk28.i = 1;
                    b->unk30.o = a->unk10;
                    a->unk2C.i = 1;
                    a->unk30.o = b->unk10;
                }
            }
        }
        return 1;
    }
    return 0;
}

/* asm 453-519, 61 insns. Character vs box, retrying across the X wrap. */
s32 fn_1_86E8(M516_ACTOR *a, M516_ACTOR *b)
{
    if (fn_1_87DC(a, b, 0.0f)) {
        return 1;
    }
    if (b->unk04 == 2) {
        if (b->unk18->x < -1000.0) {
            if (fn_1_87DC(a, b, 2200.0f)) {
                return 1;
            }
        }
        if (b->unk18->x > 1000.0) {
            if (fn_1_87DC(a, b, -2200.0f)) {
                return 1;
            }
        }
    }
    return 0;
}

/* asm 522-661, 132 insns. Character vs box overlap resolution. */
s32 fn_1_87DC(M516_ACTOR *a, M516_ACTOR *b, f32 dx)
{
    HuVecF *pos = a->unk18;
    f32 width = 0.7 * a->unk24;
    HuVecF other;

    other.x = b->unk18->x + dx;
    other.y = b->unk18->y;
    other.z = b->unk18->z;
    if (!(pos->y >= other.y + b->unk24 || pos->y + a->unk20 <= other.y + b->unk2C.f ||
          pos->x - width >= other.x + b->unk28.f || pos->x + width <= other.x + b->unk20)) {
        if (a->unk1C->y < 0.0f && (other.y + b->unk24) - pos->y < 50.0 - a->unk1C->y) {
            pos->y = other.y + b->unk24;
            return 1;
        }
        if (a->unk1C->y > 0.0f && (pos->y + a->unk20) - (other.y + b->unk2C.f) < 50.0 + a->unk1C->y) {
            pos->y = (other.y + b->unk2C.f) - a->unk20;
            return 1;
        }
        if (pos->x > other.x) {
            pos->x = width + (other.x + b->unk28.f);
        } else {
            pos->x = (other.x + b->unk20) - width;
        }
        return 1;
    }
    return 0;
}

/* asm 664-800, 129 insns. Drop a probe box and return the box it lands on. */
s32 fn_1_89EC(HuVecF *pos, f32 width)
{
    OMOBJ *obj = lbl_1_bss_50;
    M516_ACTORWORK *work = obj->data;
    M516_ACTOR probe;
    M516_ACTOR *e;
    M516_ACTOR *p;
    M516_ACTOR *o;
    HuVecF vel = { 0.0f, -1.0f, 0.0f };
    f32 hitX;
    f32 hitY;
    f32 dist;
    f32 best = 100000.0f;
    f32 saveX;
    f32 saveY;
    s32 bestIdx = -1;
    s32 bestId = 0;
    s32 id;
    s32 i;

    hitX = pos->x;
    saveX = hitX;
    hitY = pos->y;
    saveY = hitY;
    probe.unk18 = pos;
    probe.unk1C = &vel;
    probe.unk24 = width;
    probe.unk20 = 1.0f;
    for (i = 0; i < 0x43; i++) {
        e = work->unk010[i];
        if (e != NULL) {
            p = e;
            if ((p->unk00 & 1) && p->unk0C == 0) {
                o = e;
                if (fn_1_86E8(&probe, o)) {
                    dist = fabs(pos->x - o->unk18->x);
                    id = o->unk30.i;
                    if (id == bestId) {
                        if (dist > best) {
                            goto next;
                        }
                    } else if (id == 0) {
                        goto next;
                    }
                    best = dist;
                    bestId = id;
                    hitX = pos->x;
                    hitY = pos->y;
                    bestIdx = i + 4;
                next:
                    pos->x = saveX;
                    pos->y = saveY;
                }
            }
        }
    }
    pos->x = hitX;
    pos->y = hitY;
    return bestIdx;
}

/* asm 803-911, 102 insns. Highest box surface under a point. */
void fn_1_8BF0(HuVecF *pos, HuVecF *out)
{
    OMOBJ *obj;
    M516_ACTORWORK *work;
    M516_ACTOR *e;
    M516_ACTOR *p;
    M516_ACTOR *o;
    f32 limit;
    f32 top;
    f32 boxX;
    s32 i;

    obj = lbl_1_bss_50;
    work = obj->data;
    limit = 10.0 + pos->y;
    out->x = pos->x;
    out->y = 2.0f;
    out->z = pos->z;
    if (fn_1_1838() != 3) {
        out->y = 2.0 + pos->y;
    } else {
        for (i = 0; i < 0x43; i++) {
            e = work->unk010[i];
            if (e != NULL) {
                p = e;
                if ((p->unk00 & 1) && p->unk0C == 0) {
                    o = e;
                    top = o->unk18->y + o->unk24;
                    if (top > limit) {
                        continue;
                    }
                    boxX = o->unk18->x; /* retail: written and never read */
                    if (pos->x < o->unk18->x + o->unk20) {
                        continue;
                    }
                    if (pos->x > o->unk18->x + o->unk28.f) {
                        continue;
                    }
                    top += 2.0;
                    if (top > out->y) {
                        out->y = top;
                    }
                }
            }
        }
    }
}

/* asm 914-949, 30 insns. Register a character; returns its slot or -1. */
s32 fn_1_8D88(M516_ACTOR *actor)
{
    OMOBJ *obj = lbl_1_bss_50;
    M516_ACTORWORK *work = obj->data;
    M516_ACTOR **slot = work->unk000;
    s32 i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot == NULL) {
            *slot = actor;
            return i;
        }
    }
    return -1;
}

/* asm 952-987, 30 insns. Register a box; returns its slot + 4 or -1. */
s32 fn_1_8E00(M516_ACTOR *actor)
{
    OMOBJ *obj = lbl_1_bss_50;
    M516_ACTORWORK *work = obj->data;
    M516_ACTOR **slot = work->unk010;
    s32 i;

    for (i = 0; i < 0x43; i++, slot++) {
        if (*slot == NULL) {
            *slot = actor;
            return i + 4;
        }
    }
    return -1;
}

/* asm 990-1023, 28 insns. Slot -> actor. */
M516_ACTOR *fn_1_8E78(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_50;
    M516_ACTORWORK *work = obj->data;

    if (idx < 0) {
        return NULL;
    }
    if (idx < 4) {
        return work->unk000[idx];
    }
    idx -= 4;
    if (idx < 0x43) {
        return work->unk010[idx];
    }
    return NULL;
}

/* asm 1026-1054, 25 insns. Release a slot. */
void fn_1_8EE8(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_50;
    M516_ACTORWORK *work = obj->data;

    if (idx >= 0) {
        if (idx < 4) {
            work->unk000[idx] = NULL;
        }
        idx -= 4;
        if (idx < 0x43) {
            work->unk010[idx] = NULL;
        }
    }
}
