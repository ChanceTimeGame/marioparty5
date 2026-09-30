/*
 * m576dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m576Dll/asm/REL/m576Dll/stage.s.
 */

#include "REL/m576dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "string.h"

int abs(int n);
void abort(void);

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x158 */ /* float lbl_1_rodata_158 = 280.0f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 0.0f; */
/* 0x160 */ /* double lbl_1_rodata_160 = 0.001; */
/* 0x168 */ /* float lbl_1_rodata_168 = 1.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = 3.0f; */
/* 0x170 */ /* float lbl_1_rodata_170 = 0.5f; */
/* 0x174 */ /* float lbl_1_rodata_174 = 62500.0f; */
/* 0x178 */ /* float lbl_1_rodata_178 = 800.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 10000.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 100.0f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 10000000.0f; */
/* 0x188 */ /* float lbl_1_rodata_188 = 250.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 400.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 8000.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = 66.666664f; */
/* 0x198 */ /* float lbl_1_rodata_198 = 1333.3334f; */
/* 0x19C */ /* float lbl_1_rodata_19C = 200.0f; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 5000.0f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 300.0f; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = 2000.0f; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 4503601774854144; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 230.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 10.0f; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 7.1111116f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 90000.0f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 160.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 60.0f; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 4503599627370496; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 150.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 28900.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 0.01f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 14400.0f; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 500.0f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 450.0f; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0[2] = { 380.0f, 0.0f }; */

/* --- .data --- */
/* 0x3B0 */ M576_COMFUNC lbl_1_data_3B0[9] = { fn_1_C6E4, fn_1_C6E8, fn_1_CB9C, fn_1_D1D8, fn_1_D54C, fn_1_D8E0, fn_1_DBE0, fn_1_DF40, fn_1_E494 }; /* COM state table, index MGPLAYER work[0]; dispatched at 0xC65C */
/* 0x3D4 */ M576_STAGEDEF lbl_1_data_3D4[4] = { { { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 10.0f, 60.0f, 30.0f, 80.0f } }, { { 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0 }, { 5.0f, 40.0f, 25.0f, 65.0f } }, { { 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 15, 0 }, { 1.5f, 25.0f, 20.0f, 50.0f } }, { { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 15, 0 }, { 1.0f, 0.0f, 0.0f, 30.0f } } };
/* 0x494 */ char lbl_1_data_494[] = "ERROR!! | _NaviMapInit : \203I\203u\203W\203F\203N\203g\202\314\220\224\202\315\225K\202\270\210\352\202\302\202\311\202\265\202\304\202\255\202\276\202\263\202\242\201I\201I\012";
/* 0x4DB */ char lbl_1_data_4DB[0x5D] = "ERROR!! | _NaviMapInit : \202`\202h\227p\202\240\202\275\202\350\224\273\222\350\203}\203b\203v\202\315\221S\202\304\202R\212p\214`\203|\203\212\203S\203\223\202\305\223\235\210\352\202\265\202\304\202\255\202\276\202\263\202\242\012";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x35C */ M576_STAGEPLTBL lbl_1_bss_35C; /* per-player stage work; mulli 0x44 */
/* 0x359 gap_05_00000359_bss (0x3) -- dtk filler */
/* 0x358 */ s8 lbl_1_bss_358; /* number of M576_STAGEPL in use (lbz + extsb at 0xC210, 0xC230; stb) */
/* 0x324 */ s32 lbl_1_bss_324[13]; /* 0x34: 4-aligned, retype */
/* 0x320 */ M576_NAVINODE *lbl_1_bss_320; /* navigation map (lbl_1_bss_31C nodes) */
/* 0x31C */ s32 lbl_1_bss_31C; /* navigation node count */
/* 0x318 */ M576_NAVIOPEN *lbl_1_bss_318; /* A* open-list pool (lbl_1_bss_314 entries) */
/* 0x314 */ s32 lbl_1_bss_314; /* open-list pool capacity */
/* 0x310 */ s32 lbl_1_bss_310; /* open-list head index, -1 = empty */

/* --- functions (reference order) --- */
/* 8 insns */
s32 fn_1_6784(HSFOBJECT *obj, HSFFACE *face)
{
    return obj->mesh.material[face->mat & 0xFFF].flags & 0x70000;
}

/* 49 insns */
void fn_1_67A4(s32 *idx, HSFFACE *face, s32 no)
{
    switch (face->type) {
        case 2:
            idx[0] = face->index[0].vertex;
            idx[1] = face->index[1].vertex;
            idx[2] = face->index[2].vertex;
            break;
        case 3:
            if (no & 1) {
                idx[0] = face->index[0].vertex;
                idx[1] = face->index[1].vertex;
                idx[2] = face->index[3].vertex;
            } else {
                idx[0] = face->index[0].vertex;
                idx[1] = face->index[3].vertex;
                idx[2] = face->index[2].vertex;
            }
            break;
        case 4:
            idx[0] = face->strip.data[no].vertex;
            idx[1] = face->strip.data[no + 1].vertex;
            idx[2] = face->strip.data[no + 2].vertex;
            break;
    }
}

/* 53 insns */
BOOL fn_1_6868(HuVecF *a, HuVecF *b)
{
    HuVecF dir;

    VECSubtract(a, b, &dir);
    if (fabsf(dir.y) < 280.0f) {
        dir.y = 0.0f;
    } else {
        return FALSE;
    }
    return VECSquareMag(&dir) < 0.001;
}

/* 476 insns */
BOOL fn_1_693C(M576_NAVINODE *node, M576_NAVINODE *from, HuVecF *vtx, s32 vtx0, s32 vtx1)
{
    HSFFACE *face;
    HuVecF tri2;
    HuVecF tri1;
    HuVecF tri0;
    HuVecF edge1;
    HuVecF edge0;
    s32 idx[3];

    face = node->unk000;
    fn_1_67A4(idx, face, 0);
    edge0 = vtx[vtx0];
    edge1 = vtx[vtx1];
    tri0 = vtx[idx[0]];
    tri1 = vtx[idx[1]];
    tri2 = vtx[idx[2]];
    if (fn_1_6868(&tri0, &edge0)) {
        if (fn_1_6868(&tri1, &edge1)) {
            node->unk044[0] = from;
            return TRUE;
        } else if (fn_1_6868(&tri2, &edge1)) {
            node->unk044[2] = from;
            return TRUE;
        }
    } else if (fn_1_6868(&tri1, &edge0)) {
        if (fn_1_6868(&tri0, &edge1)) {
            node->unk044[0] = from;
            return TRUE;
        } else if (fn_1_6868(&tri2, &edge1)) {
            node->unk044[1] = from;
            return TRUE;
        }
    } else if (fn_1_6868(&tri2, &edge0)) {
        if (fn_1_6868(&tri0, &edge1)) {
            node->unk044[2] = from;
            return TRUE;
        } else if (fn_1_6868(&tri1, &edge1)) {
            node->unk044[1] = from;
            return TRUE;
        }
    }
    return FALSE;
}

/* 15 insns */
void fn_1_70AC(M576_NAVISLOT *slot)
{
    slot->unk000 &= ~3;
    slot->unk008 = 0;
    slot->unk010 = 0.0f;
    slot->unk00C = 0.0f;
}

/* 58 insns */
void fn_1_70E8(M576_STAGEPL *pl)
{
    M576_NAVINODE *node = lbl_1_bss_320;
    M576_NAVIOPEN *open = lbl_1_bss_318;
    s32 num = lbl_1_bss_31C;

    while (num--) {
        fn_1_70AC(&node->unk050[pl->unk004]);
        node++;
    }
    lbl_1_bss_310 = -1;
    num = lbl_1_bss_314;
    while (num--) {
        open->unk008 = 0;
        open++;
    }
}

/* 26 insns */
void fn_1_71D0(M576_STAGEPL *pl)
{
    M576_NAVINODE *node = lbl_1_bss_320;
    s32 num = lbl_1_bss_31C;

    while (num--) {
        node->unk050[pl->unk004].unk004 = 0.0f;
        node++;
    }
}

/* 24 insns */
M576_NAVINODE *fn_1_7238(s32 faceNo)
{
    M576_NAVINODE *node = lbl_1_bss_320;
    s32 num = lbl_1_bss_31C;

    while (num--) {
        if (node->unk004 == faceNo) {
            return node;
        }
        node++;
    }
    return NULL;
}

/* 6 insns */
BOOL fn_1_7298(void)
{
    return lbl_1_bss_310 >= 0;
}

/* 4 insns */
float fn_1_72B0(M576_NAVISLOT *slot)
{
    return slot->unk00C + slot->unk010;
}

/* 42 insns */
void fn_1_72C0(M576_NAVIOPEN *open)
{
    M576_NAVIOPEN *curr = &lbl_1_bss_318[lbl_1_bss_310];
    M576_NAVIOPEN *prev;

    while (TRUE) {
        if (open->unk00C < curr->unk00C) {
            prev = curr->unk000;
            if (prev) {
                prev->unk004 = open;
            } else {
                lbl_1_bss_310 = open->unk00A;
            }
            open->unk000 = prev;
            open->unk004 = curr;
            curr->unk000 = open;
            break;
        } else if (!curr->unk004) {
            curr->unk004 = open;
            open->unk000 = curr;
            open->unk004 = NULL;
            break;
        } else {
            curr = curr->unk004;
        }
    }
}

/* 109 insns */
BOOL fn_1_7368(M576_NAVINODE *node, s32 slotNo)
{
    M576_NAVISLOT *slot = &node->unk050[slotNo];
    M576_NAVIOPEN *open;

    if (lbl_1_bss_310 < 0) {
        return FALSE;
    }
    open = &lbl_1_bss_318[lbl_1_bss_310];
    do {
        if (open->unk010 == node) {
            break;
        }
        open = open->unk004;
    } while (open);
    if (!open) {
        return FALSE;
    }
    open->unk00C = fn_1_72B0(slot);
    if (!open->unk004 && !open->unk000) {
        return TRUE;
    }
    if (open->unk004) {
        open->unk004->unk000 = open->unk000;
    }
    if (open->unk000) {
        open->unk000->unk004 = open->unk004;
    } else {
        lbl_1_bss_310 = open->unk004->unk00A;
    }
    fn_1_72C0(open);
    return TRUE;
}

/* 156 insns */
void fn_1_751C(M576_NAVINODE *node, s32 slotNo)
{
    M576_NAVISLOT *slot = &node->unk050[slotNo];
    M576_NAVIOPEN *open = lbl_1_bss_318;
    s32 i;
    M576_NAVIOPEN *pool;
    s32 j;

    for (i = 0; i < lbl_1_bss_314; i++, open++) {
        if (!open->unk008) {
            break;
        }
    }
    if (i == lbl_1_bss_314) {
        lbl_1_bss_314 += lbl_1_bss_31C / 4;
        pool = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_314 * sizeof(M576_NAVIOPEN), HU_MEMNUM_OVL);
        memset(pool, 0, lbl_1_bss_314 * sizeof(M576_NAVIOPEN));
        memcpy(pool, lbl_1_bss_318, i * sizeof(M576_NAVIOPEN));
        HuMemDirectFree(lbl_1_bss_318);
        lbl_1_bss_318 = pool;
        open = &lbl_1_bss_318[i];
        j = lbl_1_bss_31C;
        while (j--) {
            lbl_1_bss_318[j].unk00A = j;
        }
    }
    open->unk00C = fn_1_72B0(slot);
    open->unk010 = node;
    open->unk008 = 1;
    if (lbl_1_bss_310 < 0) {
        lbl_1_bss_310 = i;
        open->unk000 = NULL;
        open->unk004 = NULL;
    } else {
        fn_1_72C0(open);
    }
}

/* 39 insns */
M576_NAVINODE *fn_1_778C(void)
{
    M576_NAVIOPEN *open;
    M576_NAVIOPEN *next;

    if (lbl_1_bss_310 < 0) {
        return NULL;
    }
    open = &lbl_1_bss_318[lbl_1_bss_310];
    next = open->unk004;
    if (next) {
        next->unk000 = NULL;
        lbl_1_bss_310 = next->unk00A;
    } else {
        lbl_1_bss_310 = -1;
    }
    open->unk008 = 0;
    return open->unk010;
}

/* 91 insns */
void fn_1_7828(M576_STAGEPL *pl, s32 *faceNo, s32 num, float cost, float radius)
{
    M576_NAVINODE *node;
    M576_NAVINODE *other;
    s32 i;
    s32 j;
    HuVecF pos;
    HuVecF dir;
    float dist;

    i = num;
    while (i--) {
        node = fn_1_7238(faceNo[i]);
        if (!node) {
            continue;
        }
        pos = node->unk008;
        other = lbl_1_bss_320;
        j = lbl_1_bss_31C;
        while (j--) {
            VECSubtract(&pos, &other->unk008, &dir);
            dist = VECMag(&dir);
            if (dist < radius) {
                other->unk050[pl->unk004].unk004 += cost * (1.0f - dist / radius);
            }
            other++;
        }
    }
}

/* 16 insns */
float fn_1_7994(M576_NAVINODE *node, HuVecF *pos)
{
    HuVecF dir;

    VECSubtract(&node->unk008, pos, &dir);
    return VECMag(&dir);
}

/* 348 insns */
BOOL fn_1_79D4(M576_NAVINODE *node, M576_NAVINODE *from, float cost, HuVecF *goal, s32 slotNo)
{
    M576_NAVISLOT *slot = &node->unk050[slotNo];
    BOOL result = FALSE;

    if (!(slot->unk000 & 1)) {
        result = TRUE;
        slot->unk000 |= 3;
        if (goal) {
            slot->unk010 = slot->unk004 + fn_1_7994(node, goal);
        } else {
            slot->unk010 = slot->unk004;
        }
        slot->unk00C = cost;
        fn_1_751C(node, slotNo);
    } else if (slot->unk000 & 2) {
        if (cost + slot->unk010 < slot->unk00C + slot->unk010) {
            result = TRUE;
            slot->unk00C = cost;
            fn_1_7368(node, slotNo);
        }
    }
    if (result) {
        if (from == node->unk044[0]) {
            slot->unk008 = 0;
        } else if (from == node->unk044[1]) {
            slot->unk008 = 1;
        } else if (from == node->unk044[2]) {
            slot->unk008 = 2;
        }
    }
    return result;
}

/* 55 insns */
void fn_1_7F44(M576_NAVINODE *node, s32 slotNo, HuVecF *goal)
{
    M576_NAVISLOT *slot = &node->unk050[slotNo];
    s32 i;

    if (slot->unk000 & 1) {
        slot->unk000 &= ~2;
        for (i = 0; i < 3; i++) {
            if (node->unk044[i]) {
                /* retail: abs(edge - arrival edge) picks unk038[0] for the same edge */
                fn_1_79D4(node->unk044[i], node, slot->unk00C + node->unk038[abs(i - slot->unk008)], goal, slotNo);
            }
        }
    }
}

/* 415 insns */
void _NaviMapInit(s32 mdlId)
{
    HSFDATA *hsf = Hu3DData[mdlId].hsf;
    HuVecF up;
    HSFOBJECT *obj;
    HSFFACE *face;
    s32 num;
    s32 i;
    M576_NAVINODE *node;
    HuVecF *vtx;
    HuVecF dir;
    s32 idx[3];
    M576_NAVINODE *curr;
    HSFFACE *currFace;
    HuVecF *currVtx;
    s32 currIdx[3];
    M576_NAVINODE *other;
    s32 j;

    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    if (hsf->objectNum != 1) {
        OSReport(lbl_1_data_494);
    }
    obj = hsf->object;
    num = 0;
    face = obj->mesh.face->data;
    i = obj->mesh.face->count;
    while (i--) {
        if (fn_1_6784(obj, face) && !(VECDotProduct((Vec *)face->nbt, &up) < 0.0f)) {
            if (face->type != 2) {
                OSReport(lbl_1_data_4DB);
                abort();
            }
            num++;
        }
        face++;
    }
    lbl_1_bss_31C = num;
    lbl_1_bss_320 = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_31C * sizeof(M576_NAVINODE), HU_MEMNUM_OVL);
    lbl_1_bss_314 = lbl_1_bss_31C;
    lbl_1_bss_318 = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_314 * sizeof(M576_NAVIOPEN), HU_MEMNUM_OVL);
    i = lbl_1_bss_31C;
    while (i--) {
        lbl_1_bss_318[i].unk00A = i;
    }
    obj = hsf->object;
    node = lbl_1_bss_320;
    face = obj->mesh.face->data;
    vtx = obj->mesh.vertex->data;
    num = 0;
    for (i = 0; i < obj->mesh.face->count; i++, face++) {
        if (fn_1_6784(obj, face) && !(VECDotProduct((Vec *)face->nbt, &up) < 0.0f)) {
            fn_1_67A4(idx, face, 0);
            node->unk000 = face;
            node->unk004 = i;
            node->unk008.x = (vtx[idx[0]].x + vtx[idx[1]].x + vtx[idx[2]].x) / 3.0f;
            node->unk008.y = (vtx[idx[0]].y + vtx[idx[1]].y + vtx[idx[2]].y) / 3.0f;
            node->unk008.z = (vtx[idx[0]].z + vtx[idx[1]].z + vtx[idx[2]].z) / 3.0f;
            VECAdd(&vtx[idx[0]], &vtx[idx[1]], &node->unk014);
            VECScale(&node->unk014, &node->unk014, 0.5f);
            VECAdd(&vtx[idx[1]], &vtx[idx[2]], &node->unk020);
            VECScale(&node->unk020, &node->unk020, 0.5f);
            VECAdd(&vtx[idx[2]], &vtx[idx[0]], &node->unk02C);
            VECScale(&node->unk02C, &node->unk02C, 0.5f);
            VECSubtract(&node->unk014, &node->unk020, &dir);
            node->unk038[0] = VECMag(&dir);
            VECSubtract(&node->unk020, &node->unk02C, &dir);
            node->unk038[1] = VECMag(&dir);
            VECSubtract(&node->unk02C, &node->unk014, &dir);
            node->unk038[2] = VECMag(&dir);
            node->unk044[0] = node->unk044[1] = node->unk044[2] = NULL;
            node++;
        }
    }
    curr = lbl_1_bss_320;
    currVtx = obj->mesh.vertex->data;
    i = lbl_1_bss_31C;
    while (i--) {
        currFace = curr->unk000;
        fn_1_67A4(currIdx, currFace, 0);
        other = lbl_1_bss_320;
        j = lbl_1_bss_31C;
        while (j--) {
            if (curr != other) {
                if (!curr->unk044[0] && fn_1_693C(other, curr, currVtx, currIdx[0], currIdx[1])) {
                    curr->unk044[0] = other;
                } else if (!curr->unk044[1] && fn_1_693C(other, curr, currVtx, currIdx[1], currIdx[2])) {
                    curr->unk044[1] = other;
                } else if (!curr->unk044[2] && fn_1_693C(other, curr, currVtx, currIdx[2], currIdx[0])) {
                    curr->unk044[2] = other;
                }
                if (curr->unk044[0] && curr->unk044[1] && curr->unk044[2]) {
                    break;
                }
            }
            other++;
        }
        curr++;
    }
}

/* 2338 insns
 * COM re-plan. Returns the zone (1..4) the player stands in without planning,
 * else picks a plan into unk03C (1 free slot, 2 chase slot leader, 3 chase a
 * player, 4 go to a point 0..4), biases the nav map with penalties (fn_1_7828,
 * inlined), runs A* (fn_1_ABEC / fn_1_B328) and returns 0.
 * unk02E is only ever set to -1 or to a slot no 8..12 (case 1).
 */
s32 fn_1_869C(M576_STAGEPL *work)
{
    s32 ret;
    s32 zone;
    s32 mode;
    s32 i4;
    s32 i3;
    s32 n3;
    s32 n1;
    s32 i1;
    M576_NAVINODE *goal;
    s32 n2;
    s32 i2;
    s32 attr0;
    s32 freeNum;
    float dist;
    s32 num;
    M576_NAVINODE *best;
    M576_NAVINODE *node;
    s32 n4;
    s32 res3;
    s32 cnt;
    s32 faceNo;
    s32 attr3a;
    s32 attr3b;
    s32 res1;
    s32 attr1;
    s32 no;
    s32 team;
    s32 attr2;
    HuVecF posTbl[4];
    HuVecF slotPos[5];
    M576_NAVINODE *slotNode[5];
    s32 slotNo[5];
    s32 slotTeam[5];
    HuVecF pos;
    s32 faceTbl4[4];
    M576_NAVINODE *nodeTbl[4];
    s32 noTbl[4];
    s32 teamTbl[4];
    s32 faceTbl1[4];
    s32 faceTbl2[3];

    ret = 1;
    zone = fn_1_9EC(lbl_1_bss_324[work->unk000->actor->param]);
    if (zone == 0) {
        attr0 = fn_1_A54(work->unk000->actor->param) & 0x407F;
        if (attr0 & 4) {
            zone = 3;
        } else if (attr0 & 8) {
            zone = 4;
        }
    }
    if (zone != 0) {
        return zone;
    }
    mode = 0;
    freeNum = fn_1_59C();
    if (fn_1_798(&work->unk000) >= 3) {
        mode = 4;
        if (freeNum != 0) {
            fn_1_668(&work->unk000, NULL, &dist);
            if (!(lbl_1_data_3D4[work->unk038].unk00[0x1E] & 8) || dist < 62500.0f) {
                mode = 1;
            }
        }
    } else if (freeNum != 0) {
        mode = 1;
    } else if (mode == 0) { /* retail: always true here */
        num = fn_1_8AC(NULL, NULL);
        if (num >= 3) {
            mode = 2;
        } else {
            mode = 3;
        }
    }
    fn_1_71D0(work);
    work->unk03C = mode;
    switch (work->unk03C) {
    case 4:
        n4 = 0;
        for (i4 = 0; i4 <= 3; i4++) {
            if (i4 != work->unk000->actor->param) {
                faceTbl4[n4] = lbl_1_bss_324[i4];
                    n4++;
            }
        }
        fn_1_7828(work, faceTbl4, n4, 10000.0f, 800.0f);
        if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 1) {
            fn_1_7828(work, &lbl_1_bss_324[4], 4, 10000000.0f, 100.0f);
        }
        best = fn_1_7238(fn_1_174(0, &work->unk010));
        for (i4 = 1; i4 <= 4; i4++) {
            node = fn_1_7238(fn_1_174(i4, &pos));
            /* retail: best/node are not NULL-checked (0x8DB0) */
            if (node->unk050[work->unk004].unk004 < best->unk050[work->unk004].unk004) {
                best = node;
                work->unk010 = pos;
            }
        }
        fn_1_ABEC(work, best, &work->unk010);
        work->unk028 = 250.0f;
        work->unk040 = 0;
        work->unk02C = -1;
        work->unk02E = -1;
        ret = 15;
        break;
    case 3:
        n3 = 0;
        for (i3 = 0; i3 <= 3; i3++) {
            if (i3 == work->unk000->actor->param) {
                continue;
            }
            cnt = fn_1_854(i3);
            teamTbl[n3] = fn_1_9EC(lbl_1_bss_324[i3]);
            switch (teamTbl[n3]) {
            case 1:
                faceNo = fn_1_174(5, NULL);
                break;
            case 2:
                faceNo = fn_1_174(7, NULL);
                break;
            case 0:
                attr3a = fn_1_A54(i3) & 0x407F;
                if (attr3a & 4) {
                    faceNo = fn_1_174(5, NULL);
                    teamTbl[n3] = 3;
                } else if (attr3a & 8) {
                    faceNo = fn_1_174(7, NULL);
                    teamTbl[n3] = 4;
                } else {
                    faceNo = lbl_1_bss_324[i3];
                }
                break;
            }
            if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 8) {
                fn_1_7828(work, &faceNo, 1, 8000.0f / (cnt + 1), 400.0f / (cnt + 1));
            } else {
                fn_1_7828(work, &faceNo, 1, 1333.3334f, 66.666664f);
            }
            if (cnt != 0) {
                fn_1_9A4(i3, &posTbl[n3]);
                nodeTbl[n3] = fn_1_7238(faceNo);
                if (nodeTbl[n3]) {
                    noTbl[n3] = i3;
                    n3++;
                }
            }
        }
        if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 1) {
            fn_1_7828(work, &lbl_1_bss_324[4], 4, 10000000.0f, 100.0f);
        }
        if (n3 == 0) {
            n3 = 0;
            for (i3 = 0; i3 <= 3; i3++) {
                if (i3 == work->unk000->actor->param) {
                    continue;
                }
                teamTbl[n3] = fn_1_9EC(lbl_1_bss_324[i3]);
                fn_1_9A4(i3, &posTbl[n3]);
                switch (teamTbl[n3]) {
                case 1:
                    nodeTbl[n3] = fn_1_7238(fn_1_174(5, NULL));
                    break;
                case 2:
                    nodeTbl[n3] = fn_1_7238(fn_1_174(7, NULL));
                    break;
                case 0:
                    attr3b = fn_1_A54(i3) & 0x407F;
                    if (attr3b & 4) {
                        nodeTbl[n3] = fn_1_7238(fn_1_174(5, NULL));
                        teamTbl[n3] = 3;
                    } else if (attr3b & 8) {
                        nodeTbl[n3] = fn_1_7238(fn_1_174(7, NULL));
                        teamTbl[n3] = 4;
                    } else {
                        nodeTbl[n3] = fn_1_7238(lbl_1_bss_324[i3]);
                    }
                    break;
                }
                if (nodeTbl[n3]) {
                    noTbl[n3] = i3;
                    n3++;
                }
            }
        }
        res3 = fn_1_B328(work, nodeTbl, posTbl, n3);
        work->unk028 = 200.0f;
        work->unk02E = -1;
        if (res3 >= 0) {
            work->unk02C = noTbl[res3];
            work->unk040 = teamTbl[res3];
        } else {
            work->unk02C = -1;
            work->unk040 = 0;
        }
        ret = 90;
        break;
    case 1:
        n1 = 0;
        if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 8) {
            for (i1 = 0; i1 <= 3; i1++) {
                if (i1 != work->unk000->actor->param) {
                    faceTbl1[n1] = lbl_1_bss_324[i1];
                    n1++;
                }
            }
            fn_1_7828(work, faceTbl1, n1, 5000.0f, 400.0f);
        }
        if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 1) {
            fn_1_7828(work, &lbl_1_bss_324[4], 4, 10000000.0f, 100.0f);
        }
        n1 = 0;
        for (i1 = 8; i1 <= 12; i1++) {
            if (fn_1_5F4(i1, NULL) >= 0) {
                continue;
            }
            slotTeam[n1] = fn_1_9EC(lbl_1_bss_324[i1]);
            switch (slotTeam[n1]) {
            case 1:
                slotNode[n1] = fn_1_7238(fn_1_174(5, &slotPos[n1]));
                break;
            case 2:
                slotNode[n1] = fn_1_7238(fn_1_174(7, &slotPos[n1]));
                break;
            case 0:
                attr1 = fn_1_A54(i1) & 0x407F;
                if (attr1 & 4) {
                    slotNode[n1] = fn_1_7238(fn_1_174(5, &slotPos[n1]));
                    slotTeam[n1] = 3;
                } else if (attr1 & 8) {
                    slotNode[n1] = fn_1_7238(fn_1_174(7, &slotPos[n1]));
                    slotTeam[n1] = 4;
                } else {
                    slotNode[n1] = fn_1_7238(lbl_1_bss_324[i1]);
                    fn_1_5F4(i1, &slotPos[n1]);
                }
                break;
            }
            slotNo[n1] = i1;
            if (slotNode[n1]) {
                n1++;
            }
        }
        res1 = fn_1_B328(work, slotNode, slotPos, n1);
        work->unk028 = 100.0f;
        work->unk02C = -1;
        if (res1 >= 0) {
            work->unk040 = slotTeam[res1];
            work->unk02E = slotNo[res1];
        } else {
            work->unk040 = 0;
            work->unk02E = -1;
        }
        ret = 30;
        break;
    case 2:
        /* no is written only if some player owns a slot; mode 2 implies >= 3 owned */
        fn_1_8AC(&no, &work->unk010);
        team = fn_1_9EC(lbl_1_bss_324[no]);
        switch (team) {
        case 1:
            goal = fn_1_7238(fn_1_174(5, &work->unk010));
            break;
        case 2:
            goal = fn_1_7238(fn_1_174(7, &work->unk010));
            break;
        case 0:
            attr2 = fn_1_A54(no) & 0x407F;
            if (attr2 & 4) {
                goal = fn_1_7238(fn_1_174(5, &work->unk010));
                team = 3;
            } else if (attr2 & 8) {
                goal = fn_1_7238(fn_1_174(7, &work->unk010));
                team = 4;
            } else {
                goal = fn_1_7238(lbl_1_bss_324[no]);
            }
            break;
        }
        n2 = 0;
        for (i2 = 0; i2 <= 3; i2++) {
            if (i2 != work->unk000->actor->param && i2 != no) {
                faceTbl2[n2] = lbl_1_bss_324[i2];
                    n2++;
            }
        }
        if (n2 != 0 && (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 8)) {
            fn_1_7828(work, faceTbl2, n2, 2000.0f, 300.0f);
        }
        if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 1) {
            fn_1_7828(work, &lbl_1_bss_324[4], 4, 10000000.0f, 100.0f);
        }
        fn_1_ABEC(work, goal, &work->unk010);
        work->unk028 = 300.0f;
        work->unk02C = no;
        work->unk02E = -1;
        work->unk040 = team;
        ret = 15;
        break;
    }
    work->unk030 = ret;
    work->unk032 = ret;
    return 0;
}

/* 50 insns: append pos to the COM path, growing it by 10 points when full */
void fn_1_AB24(M576_STAGEPL *work, HuVecF *pos)
{
    HuVecF *path;

    work->unk008[work->unk00C] = *pos;
    work->unk00C++;
    if (work->unk00E == work->unk00C) {
        work->unk00E += 10;
        path = HuMemDirectMallocNum(HEAP_MODEL, work->unk00E * sizeof(HuVecF), HU_MEMNUM_OVL);
        memcpy(path, work->unk008, work->unk00C * sizeof(HuVecF));
        HuMemDirectFree(work->unk008);
        work->unk008 = path;
    }
}

/*
 * 463 insns: A* from the player's current face to goal, heuristic toward
 * goalPos; on success rebuilds work->unk008 (edge midpoints, goal first) and
 * leaves unk00C = last index.
 */
void fn_1_ABEC(M576_STAGEPL *work, M576_NAVINODE *goal, HuVecF *goalPos)
{
    M576_NAVINODE *start;
    s32 best;
    s32 i;
    float dist;
    float min;
    M576_NAVINODE *node;
    M576_NAVINODE *cur;
    BOOL found;
    M576_NAVISLOT *slot;
    s32 edge;
    HuVecF dir;

    fn_1_70E8(work);
    start = fn_1_7238(lbl_1_bss_324[work->unk000->actor->param]);
    if (!start) {
        return;
    }
    start->unk050[work->unk004].unk000 |= 3;
    start->unk050[work->unk004].unk010 = 0.0f;
    start->unk050[work->unk004].unk00C = 0.0f;
    best = -1;
    for (i = 0; i < 3; i++) {
        if (!start->unk044[i]) {
            best = i;
            break;
        }
        MgActorPosGet((MGACTOR *)work, &dir);
        PSVECSubtract(&(&start->unk014)[i], &dir, &dir);
        dist = PSVECSquareMag(&dir);
        if (best < 0 || min > dist) {
            min = dist;
            best = i;
        }
    }
    if (best < 0) {
        best = 0;
    }
    start->unk050[work->unk004].unk008 = best;
    fn_1_751C(start, work->unk004);
    found = FALSE;
    while (fn_1_7298() && !found) {
        cur = fn_1_778C();
        if (cur == goal) {
            found = TRUE;
        } else {
            fn_1_7F44(cur, work->unk004, goalPos);
        }
    }
    if (found) {
        work->unk00C = 0;
        for (node = goal; start != node; node = node->unk044[edge]) {
            slot = &node->unk050[work->unk004];
            edge = slot->unk008;
            fn_1_AB24(work, &(&node->unk014)[edge]);
        }
        work->unk00C--;
    }
}

/*
 * 492 insns: A* from the player's current face to the nearest of num goal
 * nodes; on success work->unk010 = points[hit], path rebuilt as in fn_1_ABEC.
 * Returns the goal index, -1 if no start face or no goal reached.
 */
s32 fn_1_B328(M576_STAGEPL *work, M576_NAVINODE **nodes, HuVecF *points, s32 num)
{
    M576_NAVINODE *start;
    s32 best;
    s32 i;
    float dist;
    float min;
    BOOL found;
    M576_NAVINODE *node;
    M576_NAVINODE *goal;
    M576_NAVINODE *cur;
    M576_NAVISLOT *slot;
    s32 edge;
    HuVecF dir;

    fn_1_70E8(work);
    start = fn_1_7238(lbl_1_bss_324[work->unk000->actor->param]);
    if (!start) {
        return -1;
    }
    start->unk050[work->unk004].unk000 |= 3;
    start->unk050[work->unk004].unk010 = 0.0f;
    start->unk050[work->unk004].unk00C = 0.0f;
    best = -1;
    for (i = 0; i < 3; i++) {
        if (!start->unk044[i]) {
            best = i;
            break;
        }
        MgActorPosGet((MGACTOR *)work, &dir);
        PSVECSubtract(&(&start->unk014)[i], &dir, &dir);
        dist = PSVECSquareMag(&dir);
        if (best < 0 || min > dist) {
            min = dist;
            best = i;
        }
    }
    if (best < 0) {
        best = 0;
    }
    start->unk050[work->unk004].unk008 = best;
    fn_1_751C(start, work->unk004);
    found = FALSE;
    best = -1;
    while (fn_1_7298() && !found) {
        cur = fn_1_778C();
        i = num;
        while (i--) {
            if (cur == nodes[i]) {
                work->unk010 = points[i];
                goal = nodes[i];
                found = TRUE;
                best = i;
            }
        }
        if (!found) {
            fn_1_7F44(cur, work->unk004, NULL);
        }
    }
    if (!found) {
        return -1;
    }
    work->unk00C = 0;
    for (node = goal; start != node; node = node->unk044[edge]) {
        slot = &node->unk050[work->unk004];
        edge = slot->unk008;
        fn_1_AB24(work, &(&node->unk014)[edge]);
    }
    work->unk00C--;
    return best;
}

/* 7 insns: set the COM state (lbl_1_data_3B0 index) */
void fn_1_BAD8(M576_STAGEPL *work, s32 state)
{
    work->unk000->work[0] = state;
    work->unk000->work[1] = 0;
}

/* 6 insns: = m571 fn_1_8478 */
void fn_1_BAF4(s32 no, s32 face)
{
    lbl_1_bss_324[no] = face;
}

/*
 * COM AI helpers. CodeWarrior auto-inlines fn_1_BB0C / fn_1_BC74 into
 * fn_1_BD94, fn_1_C31C and the state handlers fn_1_C6E8 .. ; the out-of-line
 * copies are never called.
 */

/* 90 insns: if playerNo is within sqrt(range) (and 230 in y), chase it (state 1) */
BOOL fn_1_BB0C(M576_STAGEPL *work, s32 playerNo, float range)
{
    HuVecF playerPos;
    HuVecF dir;
    HuVecF pos;
    float dist;

    MgActorPosGet(work->unk000->actor, &pos);
    fn_1_9A4(playerNo, &playerPos);
    PSVECSubtract(&playerPos, &pos, &dir);
    if (fabsf(dir.y) > 230.0f) {
        return FALSE;
    }
    dir.y = 0.0f;
    dist = PSVECSquareMag(&dir);
    if (dist < range) {
        fn_1_BAD8(work, 1);
        fn_1_9A4(playerNo, &playerPos);
        work->unk010 = playerPos;
        work->unk02C = playerNo;
        work->unk030 = 15;
        work->unk032 = work->unk030;
        return TRUE;
    }
    return FALSE;
}

/* 72 insns: chase target; jump when stuck for more than 5 frames */
BOOL fn_1_BC74(M576_STAGEPL *work, HuVecF *target, float radius)
{
    HuVecF dir;
    float dist;

    if (MgPlayerVecChase(work->unk000, target, 10.0f, radius)) {
        return TRUE;
    }
    if (work->unk032 - work->unk030 > 5) {
        PSVECSubtract(&work->unk01C, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        dist = PSVECSquareMag(&dir);
        if ((work->unk000->actor->colGroundAttr & 0x407F) && !MgPlayerModeAttrCheck(work->unk000, MGPLAYER_MODEATTR_AIR)) {
            if ((work->unk000->actor->colGroundAttr & 0xBF80) || dist < 7.1111116f) {
                MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP);
            }
        }
    }
    return FALSE;
}

/*
 * 246 insns: choose the next COM action. Returns 5 (random, per difficulty),
 * 0 (path/slot/target reset), or fn_1_869C's plan result consumed here.
 */
s32 fn_1_BD94(M576_STAGEPL *work)
{
    s32 result;
    BOOL reset;
    HuVecF pos;

    if ((&lbl_1_data_3D4[work->unk038].unk00[10])[frandmod(10)]) {
        result = 5;
        work->unk030 = lbl_1_data_3D4[work->unk038].unk20[2];
    } else {
        switch (fn_1_869C(work)) {
        case 0:
            work->unk00C--;
            result = 0;
            break;
        case 1:
            fn_1_174(12, &pos);
            goto check;
        case 2:
            fn_1_174(13, &pos);
            goto check;
        case 3:
            fn_1_174(12, &pos);
            goto check;
        case 4:
            fn_1_174(13, &pos);
        check:
            reset = TRUE;
            switch (work->unk03C) {
            case 1:
                if (!MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
                    if (work->unk02E >= 0) {
                        if (lbl_1_bss_324[work->unk02E] >= 0) {
                            fn_1_5F4(work->unk02E, &work->unk010);
                            reset = FALSE;
                        }
                    } else if (fn_1_668(&work->unk000, &work->unk010, NULL)) {
                        /* retail: -1 (no free slot) is also taken as found */
                        reset = FALSE;
                    }
                    result = 0;
                    work->unk040 = 0;
                    work->unk00C = -1;
                    work->unk030 = 20;
                }
                break;
            case 2:
            case 3:
                if (work->unk02C >= 0 && fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                    reset = FALSE;
                }
                break;
            }
            if (reset) {
                result = 0;
                work->unk040 = 0;
                work->unk00C = -1;
                work->unk010 = pos;
                work->unk030 = 10;
            }
            break;
        }
        /* retail: dead store, overwritten below */
        work->unk032 = work->unk032 * lbl_1_data_3D4[work->unk038].unk20[0];
    }
    work->unk032 = work->unk030;
    /* retail: result is uninitialised when fn_1_869C returns outside 0..4, and
       when unk03C is 2/3 and fn_1_BB0C succeeds (GC returns the caller's r30) */
    return result;
}

/* 32 insns */
void fn_1_C16C(s32 mdlId)
{
    s32 i;

    _NaviMapInit(mdlId);
    lbl_1_bss_358 = 0;
    memset(lbl_1_bss_324, 0, sizeof(lbl_1_bss_324));
    i = 13;
    while (i--) {
        lbl_1_bss_324[i] = -1;
    }
}

/* 76 insns: register a COM player; NULL once 4 are registered */
M576_STAGEPL *fn_1_C1EC(MGPLAYER *player)
{
    M576_STAGEPL *work;

    if (lbl_1_bss_358 >= 4) {
        return NULL;
    }
    work = &lbl_1_bss_35C.unk000[lbl_1_bss_358];
    work->unk000 = player;
    MgPlayerAttrSet(work->unk000, MGPLAYER_ATTR_COMSTK);
    work->unk004 = lbl_1_bss_358;
    work->unk00C = 0;
    work->unk00E = 30;
    work->unk008 = HuMemDirectMallocNum(HEAP_MODEL, work->unk00E * sizeof(HuVecF), HU_MEMNUM_OVL);
    work->unk03C = 1;
    work->unk02E = -1;
    work->unk02C = -1;
    work->unk030 = 0;
    work->unk032 = 0;
    work->unk034 = 0;
    work->unk036 = 0;
    work->unk038 = GwPlayerConf[player->playerNo].dif;
    lbl_1_bss_358++;
    return work;
}

/* 242 insns: per-frame COM update of one registered player */
void fn_1_C31C(M576_STAGEPL *work)
{
    s32 i;
    s32 num;
    float range;

    if (work->unk034 > 0) {
        work->unk034--;
    } else {
        for (i = 0; i <= 3; i++) {
            if (i == work->unk000->actor->param) {
                continue;
            }
            if (fn_1_424(i)) {
                continue;
            }
            num = fn_1_854(i);
            if (work->unk03C == 4) {
                range = 160.0f;
            } else if (num >= 3) {
                range = 280.0f;
            } else {
                range = 100.0f + 60.0f * num;
            }
            range *= range;
            if (fn_1_BB0C(work, i, range)) {
                break;
            }
        }
        work->unk034 = lbl_1_data_3D4[work->unk038].unk20[3] + frandmod(20) - 10.0f;
    }
    if (work->unk030 > 0) {
        work->unk030--;
    } else {
        switch (fn_1_BD94(work)) {
        case 0:
            fn_1_BAD8(work, 2);
            break;
        case 3:
            fn_1_BAD8(work, 5);
            break;
        case 4:
            fn_1_BAD8(work, 6);
            break;
        case 5:
            fn_1_BAD8(work, 0);
            break;
        }
    }
    lbl_1_data_3B0[work->unk000->work[0]](work);
    work->unk01C = work->unk000->actor->pos;
}

/* 1 insns */
void fn_1_C6E4(M576_STAGEPL *work) { }

/* 301 insns */
void fn_1_C6E8(M576_STAGEPL *work)
{
    HuVecF target;
    HuVecF dir;
    HuVecF pos;
    BOOL ok;
    BOOL far;
    float dist;

    fn_1_9A4(work->unk02C, &target);
    fn_1_BC74(work, &target, 150.0f);
    if (work->unk036 > 0) {
        work->unk036--;
        return;
    }
    if (work->unk03C != 2 && work->unk03C != 3 && fn_1_424(work->unk02C)) {
        work->unk030 = 0;
        return;
    }
    MgActorPosGet(work->unk000->actor, &pos);
    PSVECSubtract(&target, &pos, &dir);
    if (fabsf(dir.y) > 230.0f) {
        work->unk030 = 0;
        return;
    }
    far = FALSE;
    if (work->unk000->actor->colGroundAttr & 0x407F) {
        if (fabsf(dir.y) > 150.0f) {
            far = TRUE;
        }
    }
    ok = !far;
    (ok) ? 150.0f : 10.0f; /* retail: result discarded */
    dir.y = 0.0f;
    dist = PSVECSquareMag(&dir);
    if (!ok) {
        return;
    }
    if (dist < 28900.0f) {
        if (lbl_1_data_3D4[work->unk038].unk00[frandmod(10)]) {
            MgPlayerVecChase(work->unk000, &target, 0.0f, 0.01f);
            if ((work->unk000->actor->colGroundAttr & 0x407F) && !MgPlayerModeAttrCheck(work->unk000, MGPLAYER_MODEATTR_AIR)) {
                MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_PUNCH);
            } else if (work->unk000->actor->velY < work->unk000->actor->gravity) {
                if ((lbl_1_data_3D4[work->unk038].unk00[0x1E] & 4) && (&lbl_1_data_3D4[work->unk038].unk00[0x14])[frandmod(10)] && dist < 14400.0f) {
                    MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_HIPDROP);
                }
                if (lbl_1_data_3D4[work->unk038].unk00[0x1E] & 2) {
                    MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_KICK);
                }
            }
        }
        work->unk036 = lbl_1_data_3D4[work->unk038].unk20[1];
    }
}

/* 399 insns */
void fn_1_CB9C(M576_STAGEPL *work)
{
    HuVecF target;
    HuVecF dir;
    float radius;
    s32 mode;

    if (work->unk00C < 0) {
        target = work->unk010;
    } else {
        target = work->unk008[work->unk00C];
        PSVECSubtract(&target, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        if (PSVECSquareMag(&dir) < work->unk028) {
            /* retail: dead re-test, and unk00C 0 -> -1 reads unk008[-1] (0xCCB0) */
            if (work->unk00C < 0) {
                target = work->unk010;
            } else {
                work->unk00C--;
                target = work->unk008[work->unk00C];
            }
        }
    }
    switch (work->unk040) {
    case 0:
        radius = 10.0f;
        if (work->unk00C < 2) {
            switch (work->unk03C) {
            case 2:
            case 3:
                radius = 150.0f;
                break;
            }
        }
        if (fn_1_BC74(work, &target, radius)) {
            work->unk00C--;
        }
        break;
    case 1:
        mode = 3;
        goto move;
    case 2:
        mode = 4;
        goto move;
    case 3:
        mode = 7;
        goto move;
    case 4:
        mode = 8;
    move:
        if (work->unk00C >= 0) {
            if (fn_1_BC74(work, &target, 10.0f)) {
                work->unk00C--;
            }
        } else {
            if (fn_1_BC74(work, &target, 10.0f)) {
                work->unk000->work[0] = mode;
                work->unk000->work[1] = 0;
                work->unk041 = 0;
                return;
            }
        }
        break;
    }
    if (work->unk02C >= 0 && work->unk00C < 2) {
        fn_1_BB0C(work, work->unk02C, 90000.0f);
    }
}

/* 221 insns */
void fn_1_D1D8(M576_STAGEPL *work)
{
    HuVecF dir;
    HuVecF pos;
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        fn_1_174(9, &work->unk010);
        work->unk041 = 1;
        PSVECSubtract(&work->unk010, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        if (PSVECSquareMag(&dir) < 100.0f) {
            work->unk041 = 3;
            break;
        }
    case 1:
        work->unk030 = 1;
        fn_1_1BC(&pos);
        if (pos.y > 500.0f) {
            break;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 2;
        }
        break;
    case 2:
        work->unk030 = 2;
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        work->unk030 = 2;
        if ((work->unk000->actor->colGroundAttr & 0x407F) && work->unk000->mode == MGPLAYER_MODE_WALK) {
            work->unk000->work[0] = 5;
            work->unk000->work[1] = 0;
            work->unk041 = 0;
        }
        break;
    }
}

/* 229 insns */
void fn_1_D54C(M576_STAGEPL *work)
{
    HuVecF dir;
    HuVecF pos;
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        fn_1_174(10, &work->unk010);
        work->unk041 = 1;
        PSVECSubtract(&work->unk010, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        if (PSVECSquareMag(&dir) < 100.0f) {
            work->unk041 = 3;
            break;
        }
    case 1:
        work->unk030 = 1;
        if (!fn_1_234(&pos)) {
            break;
        }
        if (pos.x > 450.0f || pos.x < 380.0f) {
            break;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 2;
        }
        break;
    case 2:
        work->unk030 = 1;
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        work->unk030 = 1;
        if ((work->unk000->actor->colGroundAttr & 0x407F) && work->unk000->mode == MGPLAYER_MODE_WALK) {
            work->unk000->work[0] = 6;
            work->unk000->work[1] = 0;
            work->unk041 = 0;
        }
        break;
    }
}

/* 192 insns */
void fn_1_D8E0(M576_STAGEPL *work)
{
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        if (!(work->unk000->actor->colGroundAttr & 4)) {
            return;
        }
        fn_1_174(6, &work->unk010);
        work->unk041 = 1;
    case 1:
        if (!(work->unk000->actor->colGroundAttr & 4)) {
            return;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 2;
        }
        break;
    case 2:
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 100.0f)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        if (work->unk000->actor->colGroundAttr & 0x407F) {
            work->unk030 = 0;
            return;
        }
        break;
    }
    work->unk030 = 1;
}

/* 216 insns */
void fn_1_DBE0(M576_STAGEPL *work)
{
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        if (!(work->unk000->actor->colGroundAttr & 8)) {
            return;
        }
        fn_1_174(11, &work->unk010);
        work->unk041 = 1;
    case 1:
        if (!(work->unk000->actor->colGroundAttr & 8)) {
            return;
        }
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            fn_1_174(8, &work->unk010);
            work->unk041 = 2;
        }
        break;
    case 2:
        if (!(work->unk000->actor->colGroundAttr & 8)) {
            return;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 100.0f)) {
            work->unk041 = 4;
        }
        break;
    case 4:
        if (work->unk000->actor->colGroundAttr & 0x407F) {
            work->unk030 = 0;
            return;
        }
        break;
    }
    work->unk030 = 1;
}

/* 341 insns */
void fn_1_DF40(M576_STAGEPL *work)
{
    HuVecF dir;
    HuVecF pos;
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (lbl_1_bss_324[work->unk02C] != -1 || fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        fn_1_174(9, &work->unk010);
        work->unk041 = 1;
        PSVECSubtract(&work->unk010, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        if (PSVECSquareMag(&dir) < 100.0f) {
            work->unk041 = 3;
            break;
        }
    case 1:
        work->unk030 = 1;
        fn_1_1BC(&pos);
        if (pos.y > 500.0f) {
            break;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 2;
        }
        break;
    case 2:
        work->unk030 = 2;
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        work->unk030 = 2;
        if ((work->unk000->actor->colGroundAttr & 0x407F) && work->unk000->mode == MGPLAYER_MODE_WALK) {
            work->unk041 = 4;
        }
        break;
    case 4:
        work->unk030 = 2;
        switch (work->unk03C) {
        case 2:
        case 3:
            if (work->unk02C >= 0) {
                fn_1_9A4(work->unk02C, &work->unk010);
                if (fn_1_BB0C(work, work->unk02C, 90000.0f)) { } /* retail: result unused */
            }
            break;
        case 1:
            if (work->unk02E >= 0) {
                fn_1_5F4(work->unk02E, &work->unk010);
            }
            break;
        }
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk000->work[0] = 5;
            work->unk000->work[1] = 0;
            work->unk041 = 0;
        }
        break;
    }
}

/* 349 insns */
void fn_1_E494(M576_STAGEPL *work)
{
    HuVecF dir;
    HuVecF pos;
    BOOL done;

    done = FALSE;
    switch (work->unk03C) {
    case 2:
    case 3:
        if (work->unk02C >= 0) {
            if (lbl_1_bss_324[work->unk02C] != -1 || fn_1_BB0C(work, work->unk02C, 90000.0f)) {
                done = TRUE;
            }
        }
        break;
    case 1:
        if (work->unk02E >= 0 && fn_1_5F4(work->unk02E, NULL) >= 0) {
            done = TRUE;
        }
        break;
    }
    if (done) {
        work->unk030 = 0;
        work->unk041 = 0;
        return;
    }
    switch (work->unk041) {
    case 0:
        fn_1_174(10, &work->unk010);
        work->unk041 = 1;
        PSVECSubtract(&work->unk010, &work->unk000->actor->pos, &dir);
        dir.y = 0.0f;
        if (PSVECSquareMag(&dir) < 100.0f) {
            work->unk041 = 3;
            break;
        }
    case 1:
        work->unk030 = 1;
        if (!fn_1_234(&pos)) {
            break;
        }
        if (pos.x > 450.0f || pos.x < 380.0f) {
            break;
        }
        if (work->unk000->mode == MGPLAYER_MODE_JUMP || MgPlayerModeLandSet(work->unk000, MGPLAYER_MODE_JUMP)) {
            work->unk041 = 2;
        }
        break;
    case 2:
        work->unk030 = 1;
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk041 = 3;
        }
        break;
    case 3:
        work->unk030 = 1;
        if ((work->unk000->actor->colGroundAttr & 0x407F) && work->unk000->mode == MGPLAYER_MODE_WALK) {
            work->unk041 = 4;
        }
        break;
    case 4:
        work->unk030 = 2;
        switch (work->unk03C) {
        case 2:
        case 3:
            if (work->unk02C >= 0) {
                fn_1_9A4(work->unk02C, &work->unk010);
                if (fn_1_BB0C(work, work->unk02C, 90000.0f)) { } /* retail: result unused */
            }
            break;
        case 1:
            if (work->unk02E >= 0) {
                fn_1_5F4(work->unk02E, &work->unk010);
            }
            break;
        }
        if (MgPlayerVecChase(work->unk000, &work->unk010, 10.0f, 10.0f)) {
            work->unk000->work[0] = 6;
            work->unk000->work[1] = 0;
            work->unk041 = 0;
        }
        break;
    }
}

