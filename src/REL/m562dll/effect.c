/*
 * m562dll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/effect.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/hu3d.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_FB8 = 1.5f; /* 0xFB8 */
static const double lbl_1_rodata_FC0 = 28.0; /* 0xFC0 */
static const double lbl_1_rodata_FC8 = 3.141592653589793; /* 0xFC8 */
static const float lbl_1_rodata_FD0 = 270.0f; /* 0xFD0 */
static const float lbl_1_rodata_FD4 = 22.5f; /* 0xFD4 */
static const double lbl_1_rodata_FD8 = 180.0; /* 0xFD8 */
static const float lbl_1_rodata_FE0 = 3.0f; /* 0xFE0 */
static const float lbl_1_rodata_FE4 = 240.0f; /* 0xFE4 */
static const double lbl_1_rodata_FE8 = 22.0; /* 0xFE8 */
static const double lbl_1_rodata_FF0 = 270.0; /* 0xFF0 */
static const double lbl_1_rodata_FF8 = 22.5; /* 0xFF8 */
static const double lbl_1_rodata_1000 = 8.0; /* 0x1000 */
static const float lbl_1_rodata_1008 = 45.0f; /* 0x1008 */
static const float lbl_1_rodata_100C = 2.0f; /* 0x100C */
static const float lbl_1_rodata_1010 = 100.0f; /* 0x1010 */
static const double lbl_1_rodata_1018 = 6.0; /* 0x1018 */
static const double lbl_1_rodata_1020 = 3.5; /* 0x1020 */
static const float lbl_1_rodata_1028 = 1.0f; /* 0x1028 */
static const float lbl_1_rodata_102C = 50.0f; /* 0x102C */
static const double lbl_1_rodata_1030 = 1.5; /* 0x1030 */
static const float lbl_1_rodata_1038 = 72.0f; /* 0x1038 */
static const float lbl_1_rodata_103C = 30.0f; /* 0x103C */
/* 0x1040 lbl_1_rodata_1040 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_1048 = -1.0f; /* 0x1048 */
static const float lbl_1_rodata_104C = 0.0f; /* 0x104C */
static const double lbl_1_rodata_1050 = 1.0; /* 0x1050 */
static const double lbl_1_rodata_1058 = 0.5; /* 0x1058 */
static const float lbl_1_rodata_1060 = 0.01f; /* 0x1060 */
/* 0x1068 lbl_1_rodata_1068 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7A18 */ M562_EFFECTPARAM *lbl_1_bss_7A18; /* HuMemDirectMallocNum(0x20D0): 150 particle parameter records */
/* 0x79F8 */ s16 lbl_1_bss_79F8[16]; /* particle model id per camera */

/*
 * Hit (collision) groups. fn_1_2CE44 tests every pair of entries of a group whose spheres overlap
 * and calls the group's pair callback: a brute-force pass under 10 entries, otherwise a sweep
 * along one axis (fn_1_2D234 edge list, fn_1_2D434 quicksort) whose overlapping clusters are
 * re-tested recursively on the next axis.
 */
/* the (count, list) head shared by M562_HITGROUP and the recursion's sub-lists */
typedef struct M562_HITLIST_s {
    /* 0x00 */ u16 unk00;             /* count */
    /* 0x04 */ M562_HITENTRY *unk04;  /* list */
} M562_HITLIST; /* size 0x8 (GC) */
/* one end of an entry's interval on the sweep axis */
typedef struct M562_HITEDGE_s {
    /* 0x00 */ u16 unk00;             /* 0 = interval start, 1 = interval end */
    /* 0x04 */ float unk04;           /* coordinate */
    /* 0x08 */ M562_HITENTRY *unk08;  /* the entry */
} M562_HITEDGE; /* size 0xC (GC) */
typedef struct M562_HITEDGELIST_s {
    /* 0x00 */ u16 unk00;             /* count */
    /* 0x04 */ M562_HITEDGE *unk04;   /* list */
} M562_HITEDGELIST; /* size 0x8 (GC) */

void fn_1_2CEF4(M562_HITGROUP *group, M562_HITLIST *list, u16 axis, u16 nextAxis, u16 nextAxis2);
void fn_1_2D234(u16 axis, M562_HITEDGELIST *edges, M562_HITLIST *list);
void fn_1_2D3F0(M562_HITEDGELIST *edges);
void fn_1_2D434(M562_HITEDGE *edge, s16 lo, s16 hi);
u16 fn_1_2D8FC(M562_HITEDGE *edge, s16 lo, s16 hi);

/* --- functions (reference order), .data placed before its first user --- */
/* 31 insns */
void fn_1_2CD6C(M562_HITGROUP *group, s16 max)
{
    memset(group, 0, sizeof(M562_HITGROUP));
    group->unk00 = 0;
    group->unk0C = max;
    group->unk04 = HuMemDirectMallocNum(HEAP_HEAP, max * sizeof(M562_HITENTRY), HU_MEMNUM_OVL);
    memset(group->unk04, 0, max * sizeof(M562_HITENTRY));
}

/* 21 insns */
void fn_1_2CDE8(M562_HITGROUP *group)
{
    if (group->unk04) {
        HuMemDirectFree(group->unk04);
        group->unk00 = 0;
    }
    memset(group, 0, sizeof(M562_HITGROUP));
}

/* 2 insns */
void fn_1_2CE3C(M562_HITGROUP *group, M562_HITFUNC func)
{
    group->unk08 = func;
}

/* 18 insns */
void fn_1_2CE44(M562_HITGROUP *group)
{
    fn_1_2CEF4(group, (M562_HITLIST *)group, 2, 1, 0);
    group->unk00 = 0;
}

/* 26 insns */
void fn_1_2CE8C(M562_HITGROUP *group, u16 kind, s32 flags, HuVecF *pos, float radius, void *owner)
{
    M562_HITENTRY *entry;

    if (group->unk00 < group->unk0C) {
        entry = &group->unk04[group->unk00];
        entry->unk00 = kind;
        entry->unk08 = owner;
        entry->unk0C = *pos;
        entry->unk18 = radius;
        entry->unk04 = flags;
        group->unk00++;
    }
}

/* 208 insns */
void fn_1_2CEF4(M562_HITGROUP *group, M562_HITLIST *list, u16 axis, u16 nextAxis, u16 nextAxis2)
{
    M562_HITFUNC func;
    s32 lastF;
    s32 j;
    M562_HITENTRY *entryA;
    M562_HITENTRY *entryB;
    u16 countB;
    u16 axisA;
    u16 axisB;
    u16 open;
    u16 countA;
    M562_HITEDGE *edge;
    s32 i;
    float dist;
    u16 axisNone;
    M562_HITEDGELIST edges;
    M562_HITLIST sub;
    HuVecF diff;

    if (list->unk00 < 10 || axis == 3) {
        if (group->unk08) {
            for (i = 0; i < list->unk00; i++) {
                for (j = i + 1; j < list->unk00; j++) {
                    entryA = &list->unk04[i];
                    entryB = &list->unk04[j];
                    PSVECSubtract(&entryA->unk0C, &entryB->unk0C, &diff);
                    dist = PSVECMag(&diff);
                    if (dist <= entryA->unk18 + entryB->unk18) {
                        func = group->unk08;
                        func(entryA, entryB);
                    }
                }
            }
        }
    }
    else {
        fn_1_2D234(axis, &edges, list);
        fn_1_2D3F0(&edges);
        sub.unk00 = 0;
        sub.unk04 = HuMemDirectMallocNum(HEAP_HEAP, list->unk00 * sizeof(M562_HITENTRY), HU_MEMNUM_OVL);
        memset(sub.unk04, 0, list->unk00 * sizeof(M562_HITENTRY));
        open = 0;
        countA = 0;
        countB = 0;
        axisA = nextAxis;
        axisB = nextAxis2;
        axisNone = 3;
        lastF = 0;
        for (i = 0; i < edges.unk00; i++) {
            edge = &edges.unk04[i];
            if (edge->unk00 == 0) {
                open++;
                if (sub.unk00 < list->unk00) {
                    sub.unk04[sub.unk00] = *edge->unk08;
                    sub.unk00++;
                }
                if (edge->unk08->unk04 != 0) {
                    countB++;
                }
                else {
                    countA++;
                }
            }
            else {
                open--;
                if (countA == 0) {
                    sub.unk00--;
                }
                if (edge->unk08->unk04 != 0) {
                    countB--;
                }
                else {
                    countA--;
                }
                if (open == 0) {
                    if (i < edges.unk00 - 1) {
                        lastF = 1;
                    }
                    if (lastF) {
                        if (axis == 2) {
                            axisA = 1;
                            axisB = 0;
                        }
                        else if (axis == 1) {
                            axisA = 2;
                            axisB = 0;
                        }
                        else if (axis == 0) {
                            axisA = 2;
                            axisB = 1;
                        }
                    }
                    if (sub.unk00 != 0) {
                        fn_1_2CEF4(group, &sub, axisA, axisB, 3);
                    }
                    sub.unk00 = 0;
                }
            }
        }
        if (sub.unk04) {
            HuMemDirectFree(sub.unk04);
            sub.unk00 = 0;
        }
        if (edges.unk04) {
            HuMemDirectFree(edges.unk04);
            edges.unk00 = 0;
        }
    }
}

/* 111 insns */
void fn_1_2D234(u16 axis, M562_HITEDGELIST *edges, M562_HITLIST *list)
{
    u16 i;
    float center;
    float radius;
    M562_HITENTRY *entry;

    edges->unk00 = (u16)(list->unk00 * 2);
    edges->unk04 = HuMemDirectMallocNum(HEAP_HEAP, edges->unk00 * sizeof(M562_HITEDGE), HU_MEMNUM_OVL);
    memset(edges->unk04, 0, edges->unk00 * sizeof(M562_HITEDGE));
    for (i = 0; i < list->unk00; i++) {
        entry = &list->unk04[i];
        radius = entry->unk18;
        center = (axis == 0) ? entry->unk0C.x : ((axis == 1) ? entry->unk0C.y : entry->unk0C.z);
        edges->unk04[i * 2].unk00 = 0;
        edges->unk04[i * 2].unk04 = center - radius;
        edges->unk04[i * 2].unk08 = entry;
        edges->unk04[i * 2 + 1].unk00 = 1;
        edges->unk04[i * 2 + 1].unk04 = center + radius;
        edges->unk04[i * 2 + 1].unk08 = entry;
    }
}

/* 17 insns */
void fn_1_2D3F0(M562_HITEDGELIST *edges)
{
    fn_1_2D434(edges->unk04, 0, (s16)edges->unk00 - 1);
}

/* 306 insns: quicksort by coordinate (CW inlined its own recursion twice) */
void fn_1_2D434(M562_HITEDGE *edge, s16 lo, s16 hi)
{
    s16 pivot;

    if (lo < hi) {
        pivot = fn_1_2D8FC(edge, lo, hi);
        fn_1_2D434(edge, lo, pivot - 1);
        fn_1_2D434(edge, pivot + 1, hi);
    }
}

/* 138 insns */
u16 fn_1_2D8FC(M562_HITEDGE *edge, s16 lo, s16 hi)
{
    s16 i;
    s16 j;
    float pivot;
    u16 kind;
    float value;
    M562_HITENTRY *entry;

    i = lo - 1;
    j = hi;
    pivot = edge[hi].unk04;
    while (1) {
        while (edge[++i].unk04 < pivot) { }
        while (i < --j && pivot < edge[j].unk04) { }
        if (i >= j) {
            break;
        }
        kind = edge[i].unk00;
        value = edge[i].unk04;
        entry = edge[i].unk08;
        edge[i].unk00 = edge[j].unk00;
        edge[i].unk04 = edge[j].unk04;
        edge[i].unk08 = edge[j].unk08;
        edge[j].unk00 = kind;
        edge[j].unk04 = value;
        edge[j].unk08 = entry;
    }
    kind = edge[i].unk00;
    value = edge[i].unk04;
    entry = edge[i].unk08;
    edge[i].unk00 = edge[hi].unk00;
    edge[i].unk04 = edge[hi].unk04;
    edge[i].unk08 = edge[hi].unk08;
    edge[hi].unk00 = kind;
    edge[hi].unk04 = value;
    edge[hi].unk08 = entry;
    return i;
}

/* 20 insns (m575 effect.c fn_1_E478) */
void fn_1_2DB24(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        lbl_1_bss_79F8[i] = -1;
    }
    lbl_1_bss_7A18 = NULL;
}

/* 37 insns (m575 effect.c fn_1_E4C8) */
void fn_1_2DB74(void)
{
    if (lbl_1_bss_7A18) {
        HuMemDirectFree(lbl_1_bss_7A18);
        lbl_1_bss_7A18 = NULL;
    }
    fn_1_2DB24();
}

/* 0xFF8 */ M562_EFFECTPARAM lbl_1_data_FF8 = { 0, { 0xA0, 0xA0, 0xA0, 0xFF }, { 0x00, 0x00, 0x00, 0xFF }, { 0.0f, 2.0f, 1.0f }, { 0.95f, 0.99f, 0.95f }, 0.0f, 0.0f, 1.0f, -4.0f, 0.0f };

/* 638 insns: a ring of particles around pos (type 2: 16 + 16, type 0: 8 + 8, type 1: 8 + 5 half-alpha) */
void fn_1_2DC08(s16 cameraBit, HuVecF *pos, s16 type)
{
    s16 i;
    float scale = 1.5f;

    if (type == 2) {
        for (i = 0; i < 16; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (28.0 * sin(M_PI * (270.0f + 22.5f * i) / 180.0));
            lbl_1_data_FF8.unk00C.y = 3.0f;
            lbl_1_data_FF8.unk00C.z = scale * (28.0 * cos(M_PI * (270.0f + 22.5f * i) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 240.0f, &lbl_1_data_FF8);
        }
        for (i = 0; i < 16; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (22.0 * sin(M_PI * (270.0 + (22.5 + 22.5f * i)) / 180.0));
            lbl_1_data_FF8.unk00C.y = 3.0f;
            lbl_1_data_FF8.unk00C.z = scale * (22.0 * cos(M_PI * (270.0 + (22.5 + 22.5f * i)) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 240.0f, &lbl_1_data_FF8);
        }
    }
    else if (type == 0) {
        for (i = 0; i < 8; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (8.0 * sin(M_PI * (270.0f + 45.0f * i) / 180.0));
            lbl_1_data_FF8.unk00C.y = 2.0f;
            lbl_1_data_FF8.unk00C.z = scale * (8.0 * cos(M_PI * (270.0f + 45.0f * i) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 100.0f, &lbl_1_data_FF8);
        }
        for (i = 0; i < 8; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (6.0 * sin(M_PI * (270.0 + (22.5 + 45.0f * i)) / 180.0));
            lbl_1_data_FF8.unk00C.y = 2.0f;
            lbl_1_data_FF8.unk00C.z = scale * (6.0 * cos(M_PI * (270.0 + (22.5 + 45.0f * i)) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 100.0f, &lbl_1_data_FF8);
        }
    }
    else if (type == 1) {
        lbl_1_data_FF8.unk004.a = 0x80;
        for (i = 0; i < 8; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (3.5 * sin(M_PI * (270.0f + 45.0f * i) / 180.0));
            lbl_1_data_FF8.unk00C.y = 1.0f;
            lbl_1_data_FF8.unk00C.z = scale * (3.5 * cos(M_PI * (270.0f + 45.0f * i) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 50.0f, &lbl_1_data_FF8);
        }
        for (i = 0; i < 5; i++) {
            lbl_1_data_FF8.unk00C.x = scale * (1.5 * sin(M_PI * (270.0 + (22.5 + 72.0f * i)) / 180.0));
            lbl_1_data_FF8.unk00C.y = 1.0f;
            lbl_1_data_FF8.unk00C.z = scale * (1.5 * cos(M_PI * (270.0 + (22.5 + 72.0f * i)) / 180.0));
            fn_1_2E600(cameraBit, pos->x, pos->y * scale, pos->z, 30.0f, &lbl_1_data_FF8);
        }
        lbl_1_data_FF8.unk004.a = 0xFF;
    }
}

/* 169 insns (m575 effect.c fn_1_E6E4) */
s16 fn_1_2E600(s16 arg0, float arg2, float arg3, float arg4, float arg5, M562_EFFECTPARAM *arg1)
{
    s16 cameraNo;
    s16 index;
    s16 cameraBit;
    s16 result;
    HU3DMODEL *modelP;
    M562_EFFECTPARAM *paramP;
    s16 modelId;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    fn_1_2E8A4();
    result = -1;
    cameraNo = 0;
    cameraBit = 1;
    for (; cameraNo < 16; cameraNo++, cameraBit = (s16)(cameraBit << 1)) {
        if (((cameraBit & arg0) != 0) && (Hu3DCamera[cameraNo].fov != -1.0f)) {
            modelId = lbl_1_bss_79F8[cameraNo];
            if (modelId == -1) {
                return -1;
            }
            modelP = &Hu3DData[modelId];
            particleP = modelP->hookData;
            paramP = particleP->work;
            particleDataP = &particleP->data[particleP->emitCnt];
            index = particleP->emitCnt;
            for (; index < particleP->maxCnt; index++, particleDataP++) {
                if (!particleDataP->scale) {
                    break;
                }
            }
            if (index >= particleP->maxCnt) {
                particleDataP = particleP->data;
                for (index = 0; index < particleP->maxCnt; index++, particleDataP++) {
                    if (!particleDataP->scale) {
                        break;
                    }
                }
            }
            if (index != particleP->maxCnt) {
                paramP[index] = *arg1;
                particleDataP->cameraBit = arg0;
                particleDataP->pos.x = arg2;
                particleDataP->pos.y = arg3;
                particleDataP->pos.z = arg4;
                particleDataP->vel = arg1->unk00C;
                particleDataP->color = arg1->unk004;
                particleDataP->scaleBase = arg5;
                particleDataP->scale = arg5;
                particleDataP->time = 0;
                particleDataP->parManId = -1;
                particleP->emitCnt = index;
                result = index;
            }
        }
    }
    return result;
}

/* 153 insns (m575 effect.c fn_1_E988, data 0x750070) */
void fn_1_2E8A4(void)
{
    s16 cameraNo;
    s16 i;
    void *data;
    ANIMDATA *anim;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    anim = NULL;
    for (cameraNo = 0; cameraNo < 16; cameraNo++) {
        if (Hu3DCamera[cameraNo].fov != -1.0f) {
            if (lbl_1_bss_79F8[cameraNo] != -1) {
                particleP = Hu3DData[lbl_1_bss_79F8[cameraNo]].hookData;
                if (particleP->anim != 0) {
                    anim = particleP->anim;
                }
            }
            else {
                if (!anim) {
                    data = HuDataSelHeapReadNum(0x750070, HU_MEMNUM_OVL, HEAP_MODEL);
                    anim = HuSprAnimRead(data);
                }
                lbl_1_bss_79F8[cameraNo] = Hu3DParticleCreate(anim, 0x96);
                Hu3DModelLayerSet(lbl_1_bss_79F8[cameraNo], 4);
                Hu3DParticleHookSet(lbl_1_bss_79F8[cameraNo], fn_1_2ED2C);
                Hu3DModelCameraSet(lbl_1_bss_79F8[cameraNo], 1 << cameraNo);
                if (!lbl_1_bss_7A18) {
                    lbl_1_bss_7A18 = HuMemDirectMallocNum(HEAP_HEAP, 0x96 * sizeof(M562_EFFECTPARAM), HU_MEMNUM_OVL);
                }
                Hu3DParticleBlendModeSet(lbl_1_bss_79F8[cameraNo], 0);
                particleP = Hu3DData[lbl_1_bss_79F8[cameraNo]].hookData;
                particleP->emitCnt = 0;
                particleP->work = lbl_1_bss_7A18;
                particleP->count = 1;
                for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                    particleDataP->scale = 0.0f;
                }
            }
        }
    }
}

/* 137 insns (m575 effect.c fn_1_EBEC, data 0x750070) */
void fn_1_2EB08(void)
{
    s16 cameraNo;
    void *data;
    ANIMDATA *anim;
    s16 i;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    anim = NULL;
    for (cameraNo = 0; cameraNo < 16; cameraNo++) {
        if ((Hu3DCamera[cameraNo].fov != -1.0f) && (lbl_1_bss_79F8[cameraNo] == -1)) {
            if (!anim) {
                data = HuDataSelHeapReadNum(0x750070, HU_MEMNUM_OVL, HEAP_MODEL);
                anim = HuSprAnimRead(data);
            }
            lbl_1_bss_79F8[cameraNo] = Hu3DParticleCreate(anim, 0x96);
            Hu3DModelLayerSet(lbl_1_bss_79F8[cameraNo], 4);
            Hu3DParticleHookSet(lbl_1_bss_79F8[cameraNo], fn_1_2ED2C);
            Hu3DModelCameraSet(lbl_1_bss_79F8[cameraNo], 1 << cameraNo);
            if (!lbl_1_bss_7A18) {
                lbl_1_bss_7A18 = HuMemDirectMallocNum(HEAP_HEAP, 0x96 * sizeof(M562_EFFECTPARAM), HU_MEMNUM_OVL);
            }
            Hu3DParticleBlendModeSet(lbl_1_bss_79F8[cameraNo], 0);
            particleP = Hu3DData[lbl_1_bss_79F8[cameraNo]].hookData;
            particleP->emitCnt = 0;
            particleP->work = lbl_1_bss_7A18;
            particleP->count = 1;
            for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                particleDataP->scale = 0.0f;
            }
        }
    }
}

/* 304 insns (m575 effect.c fn_1_EE10): HU3DPARTICLEHOOK */
void fn_1_2ED2C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *particleDataP;
    M562_EFFECTPARAM *paramP;
    s16 i;
    s16 color;
    double scale;

    paramP = particleP->work;
    if (particleP->count == 0) {
        for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
            particleDataP->scale = 0.0f;
        }
    }
    for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
        if (particleDataP->scale) {
            particleDataP->vel.x *= paramP[i].unk018.x;
            particleDataP->vel.y *= paramP[i].unk018.y;
            particleDataP->vel.z *= paramP[i].unk018.z;
            VECAdd(&particleDataP->vel, &particleDataP->pos, &particleDataP->pos);
            particleDataP->vel.y += paramP[i].unk024;

            color = particleDataP->color.r + (paramP[i].unk034 * (paramP[i].unk008.r - paramP[i].unk004.r));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.r = color;

            color = particleDataP->color.g + (paramP[i].unk034 * (paramP[i].unk008.g - paramP[i].unk004.g));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.g = color;

            color = particleDataP->color.b + (paramP[i].unk034 * (paramP[i].unk008.b - paramP[i].unk004.b));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.b = color;

            color = particleDataP->color.a + paramP[i].unk030;
            if (color < 1) {
                particleDataP->scale = 0.0f;
            }
            particleDataP->color.a = color;

            if (particleDataP->scale) {
                if (paramP[i].unk000 & 1) {
                    if ((particleDataP->time + i) & 1) {
                        scale = 1.0;
                    }
                    else {
                        scale = 0.5;
                    }
                    particleDataP->scale = particleDataP->scaleBase * scale;
                }
                else {
                    particleDataP->scale = particleDataP->scaleBase;
                }
                particleDataP->scaleBase += paramP[i].unk02C;
                if (particleDataP->scaleBase <= 0.01f) {
                    particleDataP->scale = 0.0f;
                }
            }
            particleDataP->time++;
        }
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}
