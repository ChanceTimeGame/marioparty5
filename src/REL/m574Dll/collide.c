/*
 * m574Dll collide.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/collide.s.
 */

#include "REL/m574Dll.h"

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
/* 0x348 */ /* float lbl_1_rodata_348 = 0.0f; */
/* 0x350 */ /* double lbl_1_rodata_350 = 0.5; */
/* 0x358 */ /* double lbl_1_rodata_358 = 3; */
/* 0x360 */ /* double lbl_1_rodata_360 = 0; */
/* 0x368 */ /* float lbl_1_rodata_368 = -1.0f; */
/* 0x370 */ /* double lbl_1_rodata_370 = 0.3; */
/* 0x378 */ /* double lbl_1_rodata_378 = -0.3; */
/* 0x380 */ /* double lbl_1_rodata_380 = 100; */
/* 0x388 */ /* double lbl_1_rodata_388 = 100.00000521540642; */
/* 0x390 */ /* float lbl_1_rodata_390 = 100.00001f; */
/* 0x398 */ /* double lbl_1_rodata_398 = 0.8; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 0.5f; */
/* 0x3A8 */ /* double lbl_1_rodata_3A8 = 300; */
/* 0x3B0 */ /* double lbl_1_rodata_3B0 = 40; */
/* 0x3B8 */ /* double lbl_1_rodata_3B8 = -50; */
/* 0x3C0 */ /* float lbl_1_rodata_3C0 = 0.017453292f; */

/* --- .data --- */
/* 0x5D8 */ s32 lbl_1_data_5D8[4] = { 0x00000000, 0x00000001, 0x00000003, 0x00000002 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x60 */ OMOBJ *lbl_1_bss_60;

/* MSL's __fpclassifyf (float.h); isnan() is fpclassify(x) == 1 */
static inline s32 fn_1_FpClassifyF(float value)
{
    switch (*(s32 *)&value & 0x7F800000) {
        case 0x7F800000:
            if ((*(s32 *)&value & 0x7FFFFF) != 0) {
                return 1;
            }
            return 2;
        case 0:
            if ((*(s32 *)&value & 0x7FFFFF) != 0) {
                return 5;
            }
            return 3;
    }
    return 4;
}

/* --- functions (reference order) --- */
/* 34 insns. Collide object and its 0x198 registry work. */
void fn_1_7A48(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M574_COLLWORK *work;

    obj = omAddObjEx(objman, 50, 0, 0, -1, fn_1_7AD4);
    lbl_1_bss_60 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M574_COLLWORK), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M574_COLLWORK));
}

/* 1 insns */
void fn_1_7AD0(void)
{
}

/* 4 insns */
void fn_1_7AD4(OMOBJ *obj)
{
    obj->objFunc = fn_1_7AE4;
}

/* 105 insns. Per-frame pass: actor vs actor, actor vs obstacle, then callbacks. */
void fn_1_7AE4(OMOBJ *obj)
{
    M574_COLLWORK *work = obj->data;
    M574_COLLACTOR *a;
    M574_COLLACTOR *pa;
    M574_COLLACTOR *b;
    M574_COLLACTOR *pb;
    s32 i;
    s32 j;

    for (i = 0; i < 82; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if ((pa->unk00 & 1) && pa->unk0C == 0) {
                for (j = i + 1; j < 82; j++) {
                    b = work->unk000[j];
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk00 & 1) && pb->unk0C == 0) {
                            fn_1_7C88(a, b);
                        }
                    }
                }
                if (!(pa->unk00 & 2)) {
                    for (j = 0; j < 20; j++) {
                        b = (M574_COLLACTOR *)work->unk148[j]; /* retail reuses b for the obstacle */
                        if (b != NULL) {
                            pb = b;
                            if (pb->unk00 & 1) {
                                switch (pb->unk0C) {
                                    case 0:
                                        fn_1_7FD8(a, (M574_COLLOBJ *)b);
                                        break;
                                    case 1:
                                        fn_1_87B8(a, (M574_COLLOBJ *)b);
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 82; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if (pa->unk14 != NULL) {
                pa->unk14(pa->unk10);
            }
        }
    }
}

/* 212 insns. Actor vs actor: push both apart about the midpoint, nudge velocities. */
s32 fn_1_7C88(M574_COLLACTOR *a, M574_COLLACTOR *b)
{
    HuVecF *pa = a->unk18;
    HuVecF *pb = b->unk18;
    float dx = pa->x - pb->x;
    float dy = pa->y - pb->y;
    float dist = sqrtf(dx * dx + dy * dy);
    float sum = a->unk2C + b->unk2C;
    HuVecF mid;

    if (sum > dist) {
        if (0.0 == dist) {
            dx = 0.0f;
            dy = -1.0f;
        } else {
            dx /= dist;
            dy /= dist;
        }
        mid.x = pa->x + 0.5 * (pb->x - pa->x);
        mid.y = pa->y + 0.5 * (pb->y - pa->y);
        dist = 0.5 * sum;
        pa->x = mid.x + dx * dist;
        pa->y = mid.y + dy * dist;
        pb->x = mid.x - dx * dist;
        pb->y = mid.y - dy * dist;
        a->unk1C->x = a->unk1C->x + 0.3 * (dx * dist);
        a->unk1C->y += 0.3 * (dy * dist);
        b->unk1C->x = b->unk1C->x + -0.3 * (dx * dist);
        b->unk1C->y += -0.3 * (dy * dist);
        return 1;
    }
    return 0;
}

/* 181 insns. Actor vs circle obstacle: push the actor out to the rim. */
s32 fn_1_7FD8(M574_COLLACTOR *a, M574_COLLOBJ *b)
{
    HuVecF *pa = a->unk18;
    HuVecF *pb = b->unk01C.pos;
    float dx = pa->x - pb->x;
    float dy = pa->y - pb->y;
    float dist = sqrtf(dx * dx + dy * dy);
    float sum = a->unk2C + b->unk020.radius;

    if (sum > dist) {
        if (b->unk18 != NULL) {
            b->unk18(b, a);
        }
        if (0.0 == dist) {
            dx = 0.0f;
            dy = -1.0f;
        } else {
            dx /= dist;
            dy /= dist;
        }
        pa->x = pb->x + dx * sum;
        pa->y = pb->y + dy * sum;
        a->unk1C->x = a->unk1C->x + 100.0 * (0.5 * dx);
        a->unk1C->y += 100.0 * (0.5 * dy);
        return 1;
    }
    return 0;
}

/* 323 insns. Actor vs segment list: swept crossing test, push out, reflect velocity. */
s32 fn_1_82AC(M574_COLLACTOR *a, M574_COLLOBJ *b, M574_COLLSEG *seg, HuVecF *prev)
{
    HuVecF *pos;
    float d;
    float dPos;
    float dPrev;
    float radius;
    float e0x;
    float e0y;
    float e1x;
    float e1y;
    float scale;
    float mag;
    HuVecF t;
    s32 hit;
    s32 i;

    hit = 0;
    pos = a->unk18;
    radius = a->unk2C;
    for (i = 0; i < b->unk01C.num; i++, seg++) {
        dPrev = seg->unk24 + (seg->unk18.x * prev->x + seg->unk18.y * prev->y);
        if (dPrev < 0.0f) {
            continue;
        }
        e0x = pos->x - seg->unk18.x * radius;
        e0y = pos->y - seg->unk18.y * radius;
        d = seg->unk24 + (seg->unk18.x * e0x + seg->unk18.y * e0y);
        dPos = seg->unk24 + (seg->unk18.x * pos->x + seg->unk18.y * pos->y);
        if (d >= 0.0f && dPos >= 0.0f) {
            continue;
        }
        dPos = -dPos;
        d = dPrev + dPos;
        if (0.0f == d) {
            continue;
        }
        t.x = pos->x + dPos * (prev->x - pos->x) / d;
        t.y = pos->y + dPos * (prev->y - pos->y) / d;
        e0x = t.x - seg->unk00.x;
        e0y = t.y - seg->unk00.y;
        e1x = t.x - seg->unk0C.x;
        e1y = t.y - seg->unk0C.y;
        if (e0x * e1x + e0y * e1y > 0.0f) {
            continue;
        }
        t.x = pos->x + 100.0 * (3.0 * seg->unk18.x);
        t.y = pos->y + 100.0 * (3.0 * seg->unk18.y);
        dPrev = seg->unk24 + (seg->unk18.x * t.x + seg->unk18.y * t.y);
        d = dPrev + dPos;
        if (0.0f == d) {
            continue;
        }
        pos->x = pos->x + (dPos * (t.x - pos->x) / d + seg->unk18.x * radius);
        pos->y = pos->y + (dPos * (t.y - pos->y) / d + seg->unk18.y * radius);
        hit = 1;
        if (b->unk18 != NULL) {
            b->unk038 = seg;
            if (b->unk18(b, a)) {
                continue;
            }
        }
        mag = VECMag(a->unk1C);
        if (mag > 100.00000521540642) {
            mag = 100.00001f;
        }
        VECReflect(a->unk1C, &seg->unk18, &t);
        if (fn_1_FpClassifyF(t.x) == 1 || fn_1_FpClassifyF(t.y) == 1) {
            continue;
        }
        scale = 0.8 * mag;
        a->unk1C->x = t.x * scale;
        a->unk1C->y = t.y * scale;
    }
    return hit;
}

/* 198 insns. Actor vs mesh obstacle; kind 6 retries from a raised point near the crossed segment. */
s32 fn_1_87B8(M574_COLLACTOR *a, M574_COLLOBJ *b)
{
    M574_COLLSEG *seg;
    float d;
    float dx;
    float dy;
    HuVecF p;
    s32 i;
    s32 side;

    if (b->unk04 == 6) {
        if (a->unk18->x < 0.0f) {
            side = 0;
        } else {
            side = 1;
        }
        if ((b->unk08 >> 1) == side) {
            seg = b->unk020.seg;
            p.x = a->unk20.x;
            p.y = a->unk20.y;
            p.z = 0.0f;
            for (i = 0; i < b->unk01C.num; i++, seg++) {
                d = seg->unk24 + (seg->unk18.x * p.x + seg->unk18.y * p.y);
                if (d < 0.0f) {
                    break;
                }
            }
            if (i < b->unk01C.num) {
                dx = (seg->unk00.x + seg->unk0C.x) / 2.0f - p.x;
                dy = (seg->unk00.y + seg->unk0C.y) / 2.0f - p.y;
                if (sqrtf(dx * dx + dy * dy) < 300.0) {
                    p.y += 40.0;
                    if (fn_1_82AC(a, b, b->unk020.seg, &p) == 0) {
                        return fn_1_82AC(a, b, b->unk024, &p);
                    }
                    return 1;
                }
            }
        }
    }
    return fn_1_82AC(a, b, b->unk020.seg, &a->unk20);
}

/* 30 insns. Register an actor; returns its slot or -1. */
s32 fn_1_8AD0(M574_COLLACTOR *actor)
{
    OMOBJ *obj = lbl_1_bss_60;
    M574_COLLWORK *work = obj->data;
    M574_COLLACTOR **slot = work->unk000;
    s32 i;

    for (i = 0; i < 82; i++, slot++) {
        if (*slot == NULL) {
            *slot = actor;
            return i;
        }
    }
    return -1;
}

/* 30 insns. Register an obstacle; returns its slot + 0x52 or -1. */
s32 fn_1_8B48(M574_COLLOBJ *o)
{
    OMOBJ *obj = lbl_1_bss_60;
    M574_COLLWORK *work = obj->data;
    M574_COLLOBJ **slot = work->unk148;
    s32 i;

    for (i = 0; i < 20; i++, slot++) {
        if (*slot == NULL) {
            *slot = o;
            return i + 82;
        }
    }
    return -1;
}

/* 25 insns. Release a slot. */
void fn_1_8BC0(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_60;
    M574_COLLWORK *work = obj->data;

    if (idx >= 0) {
        if (idx < 82) {
            work->unk000[idx] = NULL;
        }
        idx -= 82;
        if (idx < 20) {
            work->unk148[idx] = NULL; /* retail: also runs for actor slots, idx negative */
        }
    }
}

/* 28 insns. Slot -> actor or obstacle. */
void *fn_1_8C24(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_60;
    M574_COLLWORK *work = obj->data;

    if (idx < 0) {
        return NULL;
    }
    if (idx < 82) {
        return work->unk000[idx];
    }
    idx -= 82;
    if (idx < 20) {
        return work->unk148[idx];
    }
    return NULL;
}

/* 176 insns. Build a mesh obstacle: one edge per HSF quad, from its first face edge above z -50. */
void fn_1_8C94(M574_COLLOBJ *b, HSFOBJECT *objs, s32 num)
{
    HSFOBJECT *object;
    HSFFACE *face;
    HuVecF *vtx;
    HuVecF *v0;
    HuVecF *v1;
    M574_COLLEDGE *edge;
    HSFTRANSFORM **xf;
    Mtx *mtx;
    s32 size;
    s32 n;
    s32 k;
    s32 k1;
    s32 quadNum;

    quadNum = 0;
    object = objs;
    n = num;
    while (n--) {
        if (object->type == HSF_OBJ_MESH) {
            face = object->mesh.face->data;
            size = object->mesh.face->count;
            while (size--) {
                if (face->type == HSF_FACE_QUAD) {
                    quadNum++;
                }
                face++;
            }
        }
        object++;
    }
    size = quadNum * sizeof(M574_COLLEDGE);
    edge = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk028 = edge;
    memset(edge, 0, size);
    size = quadNum * sizeof(M574_COLLSEG);
    b->unk020.seg = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    memset(b->unk020.seg, 0, size);
    b->unk024 = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    memset(b->unk024, 0, size);
    b->unk02C = num;
    size = b->unk02C * sizeof(HSFTRANSFORM *);
    xf = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk030 = xf;
    memset(xf, 0, size);
    size = b->unk02C * sizeof(Mtx);
    mtx = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk034 = mtx;
    memset(mtx, 0, size);
    object = objs;
    n = num;
    b->unk01C.num = 0;
    while (n--) {
        if (object->type == HSF_OBJ_MESH) {
            vtx = object->mesh.vertex->data;
            face = object->mesh.face->data;
            size = object->mesh.face->count;
            while (size--) {
                if (face->type == HSF_FACE_QUAD) {
                    for (k = 0; k < 4; k++) {
                        k1 = (k + 1) & 3;
                        v0 = &vtx[face->index[lbl_1_data_5D8[k]].vertex];
                        v1 = &vtx[face->index[lbl_1_data_5D8[k1]].vertex];
                        if (v0->z > -50.0 && v1->z > -50.0) {
                            edge->unk00.x = v0->x;
                            edge->unk00.y = v0->y;
                            edge->unk0C.x = v1->x;
                            edge->unk0C.y = v1->y;
                            edge->unk18 = mtx;
                            edge++;
                            b->unk01C.num++;
                            break;
                        }
                    }
                }
                face++;
            }
        }
        *xf = &object->mesh.base;
        xf++;
        mtx++;
        object++;
    }
}

/* 21 insns. Build a mesh obstacle from every object of a model. */
void fn_1_8F54(M574_COLLOBJ *b, s16 mdlId)
{
    HSFDATA *hsf = Hu3DData[mdlId].hsf;

    fn_1_8C94(b, hsf->object, hsf->objectNum);
}

/* 13 insns. Build a mesh obstacle from one object. */
void fn_1_8FA8(M574_COLLOBJ *b, HSFOBJECT *obj)
{
    fn_1_8C94(b, obj, 1);
}

/* 254 insns. Per-frame: rebuild object matrices, transform edges into the other segment buffer. */
void fn_1_8FDC(M574_COLLOBJ *b)
{
    Mtx tmp;
    Mtx rot;
    Mtx m;
    HSFTRANSFORM **xf;
    Mtx *mtx;
    M574_COLLEDGE *edge;
    M574_COLLSEG *seg;
    double dy;
    double dx;
    double len;
    s32 i;

    xf = b->unk030;
    mtx = b->unk034;
    edge = b->unk028;
    seg = b->unk024;
    b->unk024 = b->unk020.seg;
    b->unk020.seg = seg;
    for (i = 0; i < b->unk02C; i++) {
        MTXRotRad(rot, 'z', MTXDegToRad((*xf)->rot.z));
        MTXRotRad(tmp, 'y', MTXDegToRad((*xf)->rot.y));
        MTXConcat(rot, tmp, m);
        MTXRotRad(rot, 'x', MTXDegToRad((*xf)->rot.x));
        MTXConcat(m, rot, tmp);
        MTXTrans(rot, (*xf)->pos.x, (*xf)->pos.y, (*xf)->pos.z);
        MTXConcat(rot, tmp, m);
        MTXScale(rot, (*xf)->scale.x, (*xf)->scale.y, (*xf)->scale.z);
        MTXConcat(m, rot, *mtx);
        xf++;
        mtx++;
    }
    for (i = 0; i < b->unk01C.num; i++) {
        MTXMultVec(*edge->unk18, &edge->unk00, &seg->unk00);
        MTXMultVec(*edge->unk18, &edge->unk0C, &seg->unk0C);
        dy = seg->unk0C.y - seg->unk00.y;
        dx = seg->unk0C.x - seg->unk00.x;
        len = sqrt(dy * dy + dx * dx);
        if (0.0 != len) {
            dy /= len;
            dx /= len;
        }
        seg->unk18.x = -dy;
        seg->unk18.y = dx;
        seg->unk18.z = 0.0f;
        seg->unk24 = -(-dy * seg->unk00.x + dx * seg->unk00.y);
        seg++;
        edge++;
    }
}
