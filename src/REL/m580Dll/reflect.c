/*
 * m580Dll reflect.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/reflect.s.
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
/* 0x7D8 */ /* float lbl_1_rodata_7D8 = 0.0f; */
/* 0x7E0 */ /* double lbl_1_rodata_7E0 = 0.5; */
/* 0x7E8 */ /* double lbl_1_rodata_7E8 = 3; */
/* 0x7F0 */ /* double lbl_1_rodata_7F0 = 0; */
/* 0x7F8 */ /* float lbl_1_rodata_7F8 = -1.0f; */
/* 0x7FC */ /* float lbl_1_rodata_7FC = 0.1f; */
/* 0x800 */ /* float lbl_1_rodata_800 = 0.5f; */
/* 0x808 */ /* double lbl_1_rodata_808 = 100; */
/* 0x810 */ /* double lbl_1_rodata_810 = 100.00000521540642; */
/* 0x818 */ /* float lbl_1_rodata_818 = 100.00001f; */
/* 0x820 */ /* double lbl_1_rodata_820 = 0.8; */
/* 0x828 */ /* double lbl_1_rodata_828 = 50; */
/* 0x830 */ /* float lbl_1_rodata_830 = 0.017453292f; */

/* --- .data --- */
/* 0x8A8 */ s32 lbl_1_data_8A8[4] = { 0x00000000, 0x00000001, 0x00000003, 0x00000002 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x258 */ OMOBJ *lbl_1_bss_258;

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
/* 34 insns. Collide object and its 0xA0 registry work. */
void fn_1_110A0(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_COLLWORK *work;

    obj = omAddObjEx(objman, 70, 0, 0, -1, fn_1_1112C);
    lbl_1_bss_258 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_COLLWORK), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_COLLWORK));
}

/* 1 insns */
void fn_1_11128(void)
{
}

/* 4 insns */
void fn_1_1112C(OMOBJ *obj)
{
    obj->objFunc = fn_1_1113C;
}

/* 181 insns. Per-frame pass: actor vs actor, actor vs mesh, NaN restore, then callbacks. */
void fn_1_1113C(OMOBJ *obj)
{
    M580_COLLWORK *work = obj->data;
    M580_COLLACTOR *a;
    M580_COLLACTOR *pa;
    M580_COLLACTOR *b;
    M580_COLLACTOR *pb;
    M580_COLLACTOR *pc;
    s32 i;
    s32 j;

    for (i = 0; i < 20; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if ((pa->unk000 & 1) && pa->unk010 == 0) {
                for (j = i + 1; j < 20; j++) {
                    b = work->unk000[j];
                    if (b != NULL) {
                        pb = b;
                        if ((pb->unk000 & 1) && pb->unk010 == 0 && (pa->unk004 & pb->unk004)) {
                            fn_1_11410(a, b);
                        }
                    }
                }
                if (!(pa->unk000 & 2)) {
                    for (j = 0; j < 20; j++) {
                        b = (M580_COLLACTOR *)work->unk050[j]; /* retail reuses b for the mesh */
                        if (b != NULL) {
                            pb = b;
                            if ((pb->unk000 & 1) && (pa->unk004 & pb->unk004)) {
                                switch (pb->unk010) {
                                    case 10:
                                        fn_1_11880(a, (M580_COLLOBJ *)b);
                                        break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for (i = 0; i < 20; i++) {
        a = work->unk000[i];
        if (a != NULL) {
            pa = a;
            if (pa->unk010 == 0) {
                pc = a;
                if (fn_1_FpClassifyF(pc->unk020->x) == 1 || fn_1_FpClassifyF(pc->unk020->z) == 1) {
                    *pc->unk020 = pc->unk028;
                }
            }
            if (pa->unk018 != NULL) {
                pa->unk018(pa->unk014);
            }
        }
    }
}

/* 284 insns. Actor vs actor: push both apart about the midpoint, nudge velocities. */
s32 fn_1_11410(M580_COLLACTOR *a, M580_COLLACTOR *b)
{
    HuVecF *pa = a->unk020;
    HuVecF *pb = b->unk020;
    float dx = pa->x - pb->x;
    float dz = pa->z - pb->z;
    float dist = sqrtf(dx * dx + dz * dz);
    float sum = a->unk034 + b->unk034;
    float k;
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
        if (!(a->unk008 == 0 && b->unk008 == 1 && (a->unk000 & 0x10))
            && !(b->unk008 == 0 && a->unk008 == 1 && (b->unk000 & 0x10))) {
            k = 0.1f;
            if ((b->unk000 & 4) && !(a->unk000 & 8)) {
                k = 0.5f;
            }
            a->unk024->x = a->unk024->x + a->unk038 * (k * (dx * dist));
            a->unk024->z += a->unk038 * (k * (dz * dist));
            k = 0.1f;
            if ((a->unk000 & 4) && !(b->unk000 & 8)) {
                k = 0.5f;
            }
            b->unk024->x = b->unk024->x - b->unk038 * (k * (dx * dist));
            b->unk024->z -= b->unk038 * (k * (dz * dist));
        }
        if (a->unk01C != NULL) {
            a->unk01C(a, b);
        }
        if (b->unk01C != NULL) {
            b->unk01C(b, a);
        }
        return 1;
    }
    return 0;
}

/* 337 insns. Actor vs segment mesh: swept crossing test, push out, reflect velocity. */
s32 fn_1_11880(M580_COLLACTOR *a, M580_COLLOBJ *b)
{
    HuVecF *pos;
    HuVecF *prev;
    M580_COLLSEG *seg;
    float d;
    float dPos;
    float dPrev;
    float radius;
    float e0x;
    float e0z;
    float e1x;
    float e1z;
    float scale;
    float mag;
    HuVecF t;
    s32 hit;
    s32 i;

    hit = 0;
    seg = b->unk024;
    prev = &a->unk028;
    pos = a->unk020;
    radius = a->unk034;
    for (i = 0; i < b->unk020; i++, seg++) {
        dPrev = seg->unk024 + (seg->unk018.x * prev->x + seg->unk018.z * prev->z);
        if (dPrev < 0.0f) {
            continue;
        }
        e0x = pos->x - seg->unk018.x * radius;
        e0z = pos->z - seg->unk018.z * radius;
        d = seg->unk024 + (seg->unk018.x * e0x + seg->unk018.z * e0z);
        dPos = seg->unk024 + (seg->unk018.x * pos->x + seg->unk018.z * pos->z);
        if (d >= 0.0f && dPos >= 0.0f) {
            continue;
        }
        dPos = -dPos;
        d = dPrev + dPos;
        if (0.0 == d) {
            continue;
        }
        t.x = pos->x + dPos * (prev->x - pos->x) / d;
        t.z = pos->z + dPos * (prev->z - pos->z) / d;
        e0x = t.x - seg->unk000.x;
        e0z = t.z - seg->unk000.z;
        e1x = t.x - seg->unk00C.x;
        e1z = t.z - seg->unk00C.z;
        if (e0x * e1x + e0z * e1z > 0.0f) {
            continue;
        }
        t.x = pos->x + 100.0 * (3.0 * seg->unk018.x);
        t.z = pos->z + 100.0 * (3.0 * seg->unk018.z);
        dPrev = seg->unk024 + (seg->unk018.x * t.x + seg->unk018.z * t.z);
        d = dPrev + dPos;
        if (0.0 == d) {
            continue;
        }
        pos->x = pos->x + (dPos * (t.x - pos->x) / d + seg->unk018.x * radius);
        pos->z = pos->z + (dPos * (t.z - pos->z) / d + seg->unk018.z * radius);
        hit = 1;
        if (a->unk01C != NULL) {
            a->unk01C(a, b);
        }
        if (b->unk01C != NULL) {
            b->unk03C = seg;
            if (b->unk01C(b, a)) {
                continue;
            }
        }
        mag = VECMag(a->unk024);
        if (0.0 == mag) {
            continue;
        }
        if (mag > 100.00000521540642) {
            mag = 100.00001f;
        }
        VECReflect(a->unk024, &seg->unk018, &t);
        if (fn_1_FpClassifyF(t.x) == 1 || fn_1_FpClassifyF(t.z) == 1) {
            continue;
        }
        scale = 0.8 * mag;
        a->unk024->x = t.x * scale;
        a->unk024->z = t.z * scale;
    }
    return hit;
}

/* 30 insns. Register an actor; returns its slot or -1. */
s32 fn_1_11DC4(M580_COLLACTOR *actor)
{
    OMOBJ *obj = lbl_1_bss_258;
    M580_COLLWORK *work = obj->data;
    M580_COLLACTOR **slot = work->unk000;
    s32 i;

    for (i = 0; i < 20; i++, slot++) {
        if (*slot == NULL) {
            *slot = actor;
            return i;
        }
    }
    return -1;
}

/* 30 insns. Register a mesh; returns its slot + 20 or -1. */
s32 fn_1_11E3C(M580_COLLOBJ *o)
{
    OMOBJ *obj = lbl_1_bss_258;
    M580_COLLWORK *work = obj->data;
    M580_COLLOBJ **slot = work->unk050;
    s32 i;

    for (i = 0; i < 20; i++, slot++) {
        if (*slot == NULL) {
            *slot = o;
            return i + 20;
        }
    }
    return -1;
}

/* 25 insns. Release a slot. */
void fn_1_11EB4(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_258;
    M580_COLLWORK *work = obj->data;

    if (idx >= 0) {
        if (idx < 20) {
            work->unk000[idx] = NULL;
        }
        idx -= 20;
        if (idx < 20) {
            work->unk050[idx] = NULL; /* retail: also runs for actor slots, idx negative */
        }
    }
}

/* 28 insns. Slot -> actor or mesh. */
void *fn_1_11F18(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_258;
    M580_COLLWORK *work = obj->data;

    if (idx < 0) {
        return NULL;
    }
    if (idx < 20) {
        return work->unk000[idx];
    }
    idx -= 20;
    if (idx < 20) {
        return work->unk050[idx];
    }
    return NULL;
}

/* 176 insns. Build a mesh: one edge per HSF quad, from its first face edge below y 50. */
void fn_1_11F88(M580_COLLOBJ *b, HSFOBJECT *objs, s32 num)
{
    HSFOBJECT *object;
    HSFFACE *face;
    HuVecF *vtx;
    HuVecF *v0;
    HuVecF *v1;
    M580_COLLEDGE *edge;
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
    size = quadNum * sizeof(M580_COLLEDGE);
    edge = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk02C = edge;
    memset(edge, 0, size);
    size = quadNum * sizeof(M580_COLLSEG);
    b->unk024 = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    memset(b->unk024, 0, size);
    b->unk028 = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    memset(b->unk028, 0, size);
    b->unk030 = num;
    size = b->unk030 * sizeof(HSFTRANSFORM *);
    xf = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk034 = xf;
    memset(xf, 0, size);
    size = b->unk030 * sizeof(Mtx);
    mtx = HuMemDirectMallocNum(HEAP_HEAP, size, HU_MEMNUM_OVL);
    b->unk038 = mtx;
    memset(mtx, 0, size);
    object = objs;
    n = num;
    b->unk020 = 0;
    while (n--) {
        if (object->type == HSF_OBJ_MESH) {
            vtx = object->mesh.vertex->data;
            face = object->mesh.face->data;
            size = object->mesh.face->count;
            while (size--) {
                if (face->type == HSF_FACE_QUAD) {
                    for (k = 0; k < 4; k++) {
                        k1 = (k + 1) & 3;
                        v0 = &vtx[face->index[lbl_1_data_8A8[k]].vertex];
                        v1 = &vtx[face->index[lbl_1_data_8A8[k1]].vertex];
                        if (v0->y < 50.0 && v1->y < 50.0) {
                            edge->unk000.x = v0->x;
                            edge->unk000.z = v0->z;
                            edge->unk00C.x = v1->x;
                            edge->unk00C.z = v1->z;
                            edge->unk018 = mtx;
                            edge++;
                            b->unk020++;
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

/* 21 insns. Build a mesh from every object of a model. */
void fn_1_12248(M580_COLLOBJ *b, s16 mdlId)
{
    HSFDATA *hsf = Hu3DData[mdlId].hsf;

    fn_1_11F88(b, hsf->object, hsf->objectNum);
}

/* 13 insns. Build a mesh from one object. */
void fn_1_1229C(M580_COLLOBJ *b, HSFOBJECT *obj)
{
    fn_1_11F88(b, obj, 1);
}

/* 254 insns. Per-frame: rebuild object matrices, transform edges into the other segment buffer. */
void fn_1_122D0(M580_COLLOBJ *b)
{
    Mtx tmp;
    Mtx rot;
    Mtx m;
    HSFTRANSFORM **xf;
    Mtx *mtx;
    M580_COLLEDGE *edge;
    M580_COLLSEG *seg;
    double dz;
    double dx;
    double len;
    s32 i;

    xf = b->unk034;
    mtx = b->unk038;
    edge = b->unk02C;
    seg = b->unk028;
    b->unk028 = b->unk024;
    b->unk024 = seg;
    for (i = 0; i < b->unk030; i++) {
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
    for (i = 0; i < b->unk020; i++) {
        MTXMultVec(*edge->unk018, &edge->unk000, &seg->unk000);
        MTXMultVec(*edge->unk018, &edge->unk00C, &seg->unk00C);
        dz = seg->unk00C.z - seg->unk000.z;
        dx = seg->unk00C.x - seg->unk000.x;
        len = sqrt(dz * dz + dx * dx);
        if (0.0 != len) {
            dz /= len;
            dx /= len;
        }
        seg->unk018.x = -dz;
        seg->unk018.y = 0.0f;
        seg->unk018.z = dx;
        seg->unk024 = -(-dz * seg->unk000.x + dx * seg->unk000.z);
        seg++;
        edge++;
    }
}

/* 36 insns. Is pos on the inner side of every segment? */
s32 fn_1_126C8(M580_COLLOBJ *b, HuVecF *pos)
{
    M580_COLLSEG *seg = b->unk024;
    float d;
    s32 i;

    for (i = 0; i < b->unk020; i++, seg++) {
        d = seg->unk024 + (seg->unk018.x * pos->x + seg->unk018.z * pos->z);
        if (d < 0.0f) {
            return 0;
        }
    }
    return 1;
}
