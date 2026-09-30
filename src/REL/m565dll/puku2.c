/*
 * m565dll puku2.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/puku2.s.
 */

#include "REL/m565dll.h"

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
/* 0x220 */ /* s32 lbl_1_rodata_220[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x22C */ /* float lbl_1_rodata_22C = 0.0f; */
/* 0x230 */ /* float lbl_1_rodata_230 = 0.01f; */
/* 0x234 */ /* float lbl_1_rodata_234 = 1.0f; */
/* 0x238 */ /* float lbl_1_rodata_238 = 0.5f; */
/* 0x240 */ /* double lbl_1_rodata_240 = 3.141592653589793; */
/* 0x248 */ /* float lbl_1_rodata_248 = 90.0f; */
/* 0x250 */ /* double lbl_1_rodata_250 = 180; */
/* 0x258 */ /* float lbl_1_rodata_258 = 3.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = 1.3f; */
/* 0x260 */ /* float lbl_1_rodata_260 = 65.0f; */
/* 0x264 */ /* float lbl_1_rodata_264 = -90.0f; */
/* 0x268 */ /* float lbl_1_rodata_268 = 180.0f; */
/* 0x270 */ /* double lbl_1_rodata_270 = 4503601774854144; */
/* 0x278 */ /* float lbl_1_rodata_278 = 150.0f; */
/* 0x280 */ /* double lbl_1_rodata_280 = 360; */
/* 0x288 */ /* double lbl_1_rodata_288 = -180; */

/* --- functions (reference order) --- */
/* 29 insns */
void fn_1_8AD0(M565_PUKU2 *puku2, M565_OBJECT *obj)
{
    s32 i;

    memset(puku2, 0, sizeof(M565_PUKU2));
    puku2->unk000 = obj;
    for (i = 0; i < 5; i++) {
        fn_1_8E10(&puku2->unk004[i], puku2);
    }
}

/* 25 insns */
void fn_1_8B44(M565_PUKU2 *puku2)
{
    s32 i;

    for (i = 0; i < 5; i++) {
        fn_1_907C(&puku2->unk004[i]);
    }
    memset(puku2, 0, sizeof(M565_PUKU2));
}

/* 50 insns */
void fn_1_8BA8(M565_PUKU2 *puku2)
{
    s32 i;
    M565_PUKU2OBJ *puku;

    for (i = 0; i < 5; i++) {
        puku = &puku2->unk004[i];
        if (fn_1_90F0(puku) && puku->unk004) {
            Hu3DModelAttrSet(puku->unk008, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(puku->unk00A, HU3D_ATTR_DISPOFF);
            puku->unk004 = 0;
            puku2->unk1D0--;
            if (puku->unk028) {
                puku2->unk1D2--;
            } else {
                puku2->unk1D4--;
            }
        }
    }
}

/* 104 insns */
M565_PUKU2OBJ *fn_1_8C70(M565_PUKU2 *puku2, HuVecF *start, HuVecF *end, float b0, s32 flag)
{
    s32 i;
    M565_PUKU2OBJ *puku;

    for (i = 0; i < 5; i++) {
        puku = &puku2->unk004[i];
        if (!puku->unk004) {
            puku->unk038 = *start;
            puku->unk044 = *end;
            puku->unk010 = *start;
            puku->unk01C = (HuVecF) { 0.0f, 0.0f, 0.0f };
            puku->unk050 = b0;
            puku->unk054 = 0;
            puku->unk028 = flag;
            puku->unk030 = 40;
            puku->unk032 = 100;
            if (flag) {
                Hu3DModelAttrReset(puku->unk008, HU3D_ATTR_DISPOFF);
                Hu3DModelShadowSet(puku->unk008);
            } else {
                Hu3DModelAttrReset(puku->unk00A, HU3D_ATTR_DISPOFF);
                Hu3DModelShadowSet(puku->unk00A);
            }
            puku->unk004 = 1;
            fn_1_90F0(puku);
            puku2->unk1D0++;
            if (flag) {
                puku2->unk1D2++;
            } else {
                puku2->unk1D4++;
            }
            puku2->unk1D6++;
            return puku;
        }
    }
    return NULL;
}

/* 155 insns */
void fn_1_8E10(M565_PUKU2OBJ *puku, M565_PUKU2 *puku2)
{
    HU3DMODELID modelId;
    M565_PUKU2 *owner;
    M565_OBJECT *obj;

    owner = puku2;
    obj = owner->unk000;
    memset(puku, 0, sizeof(M565_PUKU2OBJ));
    puku->unk000 = puku2;
    puku->unk004 = 0;
    puku->unk008 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6B), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.01f, 0.01f, 0.01f);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    puku->unk00C[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x79), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, puku->unk00C[0]);
    puku->unk00A = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x6C), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(modelId, 0.01f, 0.01f, 0.01f);
    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    puku->unk00C[0] = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m565, 0x79), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(modelId, puku->unk00C[0]);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
}

/* 29 insns */
void fn_1_907C(M565_PUKU2OBJ *puku)
{
    s32 i;

    for (i = 0; i < 1; i++) {
        Hu3DMotionKill(puku->unk00C[i]);
    }
    Hu3DModelKill(puku->unk00A);
    Hu3DModelKill(puku->unk008);
    memset(puku, 0, sizeof(M565_PUKU2OBJ));
}

#define M565_CLAMP01(x) ((x) > 1.0f ? 1.0f : ((x) < 0.0f ? 0.0f : (x)))
#define M565_ABS(x) ((x) >= 0.0f ? (x) : -(x))

/* 630 insns */
s32 fn_1_90F0(M565_PUKU2OBJ *puku)
{
    M565_PUKU2 *puku2;
    M565_OBJECT *obj;
    M565_STAGE *stage;
    HuVecF dir;
    HuVecF hit;
    HuVecF pos;
    float t;
    float s;
    float fall;
    float h;
    float scale;

    puku2 = puku->unk000;
    obj = puku2->unk000;
    stage = &obj->unk2E4;
    if (!puku->unk004) {
        return 0;
    }
    PSVECSubtract(&puku->unk044, &puku->unk038, &dir);
    dir.y = 0.0f;
    t = (float)puku->unk054 / (float)(puku->unk032 + puku->unk030 * 2);
    h = (puku->unk010.y > 0.0f) ? puku->unk010.y / puku->unk050 : 0.0f;
    fall = (puku->unk054 < puku->unk030) ? 0.0f : ((puku->unk054 > puku->unk030 + puku->unk032) ? 1.0f : (float)(puku->unk054 - puku->unk030) / (float)puku->unk032);
    t = M565_CLAMP01(t);
    h = M565_CLAMP01(h);
    fall = M565_CLAMP01(fall);
    if (t < 0.5f) {
        s = t / 0.5f;
        pos.y = puku->unk038.y + (puku->unk050 - puku->unk038.y) * HuSin(90.0f * s);
        s = t * h;
        pos.x = puku->unk038.x + dir.x * s;
        pos.z = puku->unk038.z + dir.z * s;
    } else {
        s = (t - 0.5f) / 0.5f;
        pos.y = puku->unk044.y + (puku->unk050 - puku->unk044.y) * HuSin(90.0f + 90.0f * s);
        s = 0.5f + (0.5f - (1.0f - t) * h);
        pos.x = puku->unk038.x + dir.x * s;
        pos.z = puku->unk038.z + dir.z * s;
    }
    s = (t < 0.5f) ? M565_ABS(puku->unk010.y) / M565_ABS(puku->unk038.y) : M565_ABS(puku->unk010.y) / M565_ABS(puku->unk044.y);
    s = (puku->unk010.y < 0.0f) ? s : 0.0f;
    s = s * (s * s);
    s = 1.0f - M565_CLAMP01(s);
    if (puku->unk028) {
        scale = 3.0f * s;
    } else {
        scale = 1.3f * s;
    }
    Hu3DModelScaleSet(puku->unk008, scale, scale, scale);
    Hu3DModelScaleSet(puku->unk00A, scale, scale, scale);
    if (t >= 0.5f) {
        if (pos.y <= 0.0f && !puku->unk02C) {
            hit = pos;
            fn_1_5EB0(stage, &hit, puku->unk028, NULL);
            if (obj->unk3824) {
                Hu3DMotionSpeedSet(obj->unk3820, 1.0f);
                obj->unk3824 = 0;
            }
        }
        if (pos.y < 65.0f) {
            Hu3DModelShadowReset(puku->unk008);
            Hu3DModelShadowReset(puku->unk00A);
        }
    }
    if (!puku->unk02C) {
        puku->unk010 = pos;
        Hu3DModelPosSet(puku->unk008, puku->unk010.x, puku->unk010.y, puku->unk010.z);
        Hu3DModelPosSet(puku->unk00A, puku->unk010.x, puku->unk010.y, puku->unk010.z);
    }
    PSVECNormalize(&dir, &dir);
    puku->unk01C.y = HuAtan(dir.x, dir.z);
    if (!puku->unk02C) {
        puku->unk01C.x = -90.0f + 180.0f * fall;
    }
    Hu3DModelRotSet(puku->unk008, puku->unk01C.x, puku->unk01C.y, puku->unk01C.z);
    Hu3DModelRotSet(puku->unk00A, puku->unk01C.x, puku->unk01C.y, puku->unk01C.z);
    if (!puku->unk02C) {
        fn_1_9AC8(puku);
    }
    if (puku->unk02C) {
        Hu3DMotionSpeedSet(puku->unk008, 0.0f);
        Hu3DMotionSpeedSet(puku->unk00A, 0.0f);
        if (puku->unk028) {
            if (puku->unk058 & 1) {
                Hu3DModelAttrSet(puku->unk008, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(puku->unk008, HU3D_ATTR_DISPOFF);
            }
        } else {
            if (puku->unk058 & 1) {
                Hu3DModelAttrSet(puku->unk00A, HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(puku->unk00A, HU3D_ATTR_DISPOFF);
            }
        }
        if (--puku->unk058 == 0) {
            return 1;
        }
    }
    puku->unk054++;
    if (puku->unk054 >= puku->unk032 + puku->unk030 * 2) {
        return 1;
    }
    return 0;
}

#define M565_ANGLE180(a) ((a) > 180.0 ? (a) - 360.0 : ((a) <= -180.0 ? 360.0 + (a) : (a)))

/* 249 insns */
void fn_1_9AC8(M565_PUKU2OBJ *puku)
{
    s32 i;
    M565_PUKU2 *puku2;
    M565_OBJECT *obj;
    M565_WORK *work;
    M565_PLAYER *player;
    float dist;
    float range;
    float angle;
    HuVecF d;
    HuVecF mid;
    M565_STAGE *stage;
    float vol;
    float pan;
    s32 seId;

    puku2 = puku->unk000;
    obj = puku2->unk000;
    work = obj->unk000;
    stage = &obj->unk2E4;
    for (i = 0; i < 4; i++) {
        player = &obj->unk008[i];
        PSVECSubtract(player->unk074, &puku->unk010, &d);
        dist = PSVECMag(&d);
        if (!player->unk090 && player->unk004->stunTime <= 0.0f) {
            range = puku->unk028 ? 150.0f : 65.0f;
            if (dist < range) {
                d.y = 0.0f;
                angle = 0.0f;
                /* retail normalises only the zero vector (NaN angle); host keeps angle 0 */
                if (!d.x && !d.z && M565_PC_OK(0)) {
                    PSVECNormalize(&d, &d);
                    angle = M565_ANGLE180(HuAtan(d.x, d.z));
                }
                fn_1_89D4(player, angle, 1);
                if (work->unk3870 && !player->unk090) {
                    omVibrate(player->unk008, 30, 12, 0);
                }
                mid.x = 0.5f * (player->unk074->x + puku->unk010.x);
                mid.y = 0.5f * (player->unk074->y + puku->unk010.y);
                mid.z = 0.5f * (player->unk074->z + puku->unk010.z);
                Hu3DModelPosSet(player->unk0A0, mid.x, mid.y, mid.z);
                if (MgSeqModeGet() == 5) {
                    fn_1_A10(player->unk074, &vol, &pan);
                    seId = fn_1_C18(0x8DC);
                    fn_1_CC8(seId, vol);
                    fn_1_C98(seId, pan);
                }
            }
        }
    }
}
