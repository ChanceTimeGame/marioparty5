/*
 * m562dll mini_mechakoopa.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/mini_mechakoopa.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
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
static const float lbl_1_rodata_6E8 = 1.0f; /* 0x6E8 */
/* 0x6EC lbl_1_rodata_6EC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6F8 lbl_1_rodata_6F8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_704 = 0.0f; /* 0x704 */
static const double lbl_1_rodata_708 = 180.0; /* 0x708 */
static const double lbl_1_rodata_710 = 3.141592653589793; /* 0x710 */
static const double lbl_1_rodata_718 = 360.0; /* 0x718 */
static const double lbl_1_rodata_720 = -180.0; /* 0x720 */
static const float lbl_1_rodata_728 = 30.0f; /* 0x728 */
static const float lbl_1_rodata_72C = 1000.0f; /* 0x72C */
static const float lbl_1_rodata_730 = 0.25f; /* 0x730 */
static const double lbl_1_rodata_738 = 0.699999988079071; /* 0x738 */
static const double lbl_1_rodata_740 = 0.30000001192092896; /* 0x740 */
static const float lbl_1_rodata_748 = 180.0f; /* 0x748 */
static const float lbl_1_rodata_74C = 34.0f; /* 0x74C */
/* 0x750 lbl_1_rodata_750 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x758 lbl_1_rodata_758 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_760 = 500.0f; /* 0x760 */
static const float lbl_1_rodata_764 = 130.0f; /* 0x764 */
static const float lbl_1_rodata_768 = 1800.0f; /* 0x768 */
static const float lbl_1_rodata_76C = 150.0f; /* 0x76C */
static const float lbl_1_rodata_770 = 90.0f; /* 0x770 */
static const float lbl_1_rodata_774 = 270.0f; /* 0x774 */
static const double lbl_1_rodata_778 = 0.5; /* 0x778 */
static const double lbl_1_rodata_780 = 1.0; /* 0x780 */
static const float lbl_1_rodata_788 = 6.0f; /* 0x788 */
static const float lbl_1_rodata_78C = 0.05f; /* 0x78C */
static const float lbl_1_rodata_790 = 0.95f; /* 0x790 */
static const float lbl_1_rodata_794 = 380.0f; /* 0x794 */
static const float lbl_1_rodata_798 = 50.0f; /* 0x798 */
static const float lbl_1_rodata_79C = 8.0f; /* 0x79C */
static const float lbl_1_rodata_7A0 = 0.15f; /* 0x7A0 */
static const float lbl_1_rodata_7A4 = 0.85f; /* 0x7A4 */
static const float lbl_1_rodata_7A8 = 0.2f; /* 0x7A8 */
static const float lbl_1_rodata_7AC = 0.8f; /* 0x7AC */
static const float lbl_1_rodata_7B0 = 250.0f; /* 0x7B0 */
static const float lbl_1_rodata_7B4 = 0.1f; /* 0x7B4 */
static const float lbl_1_rodata_7B8 = 0.9f; /* 0x7B8 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7840 */ s16 lbl_1_bss_7840[4];

/* --- functions (reference order), .data placed before its first user --- */

#define M562_DATA(n) HuDataSelHeapReadNum(DATANUM(DATA_m562, n), HU_MEMNUM_OVL, HEAP_MODEL)

#define M562_ANGLE(x, z) ((HuAtan((x), (z)) > 180.0) ? (HuAtan((x), (z)) - 360.0) : ((HuAtan((x), (z)) <= -180.0) ? (360.0 + HuAtan((x), (z))) : HuAtan((x), (z))))

/* 102 insns. Mini Mechakoopa pool init: the two master models (walking / flipped) and 34 links. */
void fn_1_177EC(M562_MECHAKOOPA *mecha, M562_WORK *work)
{
    HU3DMODELID modelId;
    s32 i;
    M562_MECHAENTRY *entry;

    memset(mecha, 0, sizeof(M562_MECHAKOOPA));
    mecha->unk000 = work;
    mecha->unk66C = modelId = Hu3DModelCreate(M562_DATA(0x18));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    mecha->unk670 = Hu3DJointMotion(modelId, M562_DATA(0x3B));
    Hu3DMotionSet(modelId, mecha->unk670);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    mecha->unk66E = modelId = Hu3DModelCreate(M562_DATA(0x19));
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    mecha->unk672 = Hu3DJointMotion(modelId, M562_DATA(0x3C));
    Hu3DMotionSet(modelId, mecha->unk672);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    for (i = 0; i < 34; i++) {
        entry = &mecha->unk00C[i];
        fn_1_182B8(entry, mecha);
    }
    mecha->unk676 = -1;
    mecha->unk688 = -1;
}

/* 41 insns. Pool kill. */
void fn_1_17984(M562_MECHAKOOPA *mecha)
{
    s32 i;
    M562_MECHAENTRY *entry;

    if (mecha->unk676 >= 0) {
        Hu3DGLightKill(mecha->unk676);
    }
    for (i = 0; i < 34; i++) {
        entry = &mecha->unk00C[i];
        fn_1_1848C(entry);
    }
    Hu3DMotionKill(mecha->unk672);
    Hu3DMotionKill(mecha->unk670);
    Hu3DModelKill(mecha->unk66E);
    Hu3DModelKill(mecha->unk66C);
    memset(mecha, 0, sizeof(M562_MECHAKOOPA));
}

/* 0x9F8 */ HuVecF lbl_1_data_9F8 = { 0.0f, 1200.0f, 0.0f };
/* 0xA04 */ HuVecF lbl_1_data_A04 = { 0.0f, -1.0f, 0.01f };
/* 0xA10 */ GXColor lbl_1_data_A10 = { 0xFF, 0x30, 0x00, 0xFF };
/* 0xA11 */ /* lbl_1_data_A11: the last three bytes of the GXColor above (dtk split) */

/* 501 insns. Pool frame: follow unk004 (on/off request from koopa.c / koopaboss.c), aim along
   the thrower's head, run every active Mechakoopa, drive the SE emitter at the oldest one and
   the orange spot light at their centre. */
void fn_1_17A28(M562_MECHAKOOPA *mecha)
{
    Mtx mtx;
    HuVecF lightPos;
    HuVecF sum;
    HuVecF dir;
    GXColor color;
    float scale;
    float angle;
    s16 best;
    s32 i;
    M562_MECHAENTRY *entry;
    M562_WORK *work;
    M562_KOOPA *koopa;
    M562_KOOPABOSS *boss;

    work = mecha->unk000;
    koopa = &work->koopa;
    boss = &work->koopaboss;
    if (mecha->unk674 == 0 && mecha->unk688 >= 0) {
        fn_1_83C(mecha->unk688);
        mecha->unk688 = -1;
    }
    if (mecha->unk004 != 0 && mecha->unk008 == 0) {
        mecha->unk008 = 1;
    } else if (mecha->unk004 == 0 && mecha->unk008 != 0) {
        if (mecha->unk674 != 0) {
            for (i = 0; i < 34; i++) {
                entry = &mecha->unk00C[i];
                if (entry->unk0C != 0) {
                    Hu3DModelAttrSet(entry->unk06, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(entry->unk08, HU3D_ATTR_DISPOFF);
                    entry->unk0C = 0;
                }
            }
            mecha->unk674 = 0;
        }
        if (mecha->unk676 >= 0) {
            Hu3DGLightKill(mecha->unk676);
            mecha->unk676 = -1;
        }
        mecha->unk008 = 0;
    }
    if (mecha->unk008 != 0) {
        if (work->unk000E == 3) {
            Hu3DModelObjMtxGet(koopa->model, "g000m0-ns_hed", mtx);
            angle = koopa->angle;
        } else if (boss->unk000) {
            Hu3DModelObjMtxGet(boss->unk020, "g000mSP-head", mtx);
            /* retail reads a float at koopaboss+0x40, which is inside the motion array (unk022[15..16]); the
               value is only kept when the head matrix gives no direction */
            angle = *(float *)&boss->unk022[15];
        }
        dir.x = mtx[0][0];
        dir.y = 0.0f;
        dir.z = mtx[2][0];
        if (dir.x || dir.z) {
            PSVECNormalize(&dir, &dir);
            angle = M562_ANGLE(dir.x, dir.z);
        }
        mecha->unk678 = angle;
        {
            HuVecF zero = { 0.0f, 0.0f, 0.0f };
            HuVecF *src = &zero;
            mecha->unk67C = *src;
        }
        best = 0;
        {
            HuVecF zero = { 0.0f, 0.0f, 0.0f };
            HuVecF *src = &zero;
            sum = *src;
        }
        for (i = 0; i < 34; i++) {
            entry = &mecha->unk00C[i];
            if (entry->unk0C != 0) {
                fn_1_184D4(entry);
                sum.x += entry->unk20.x;
                sum.y += entry->unk20.y;
                sum.z += entry->unk20.z;
                if (best < entry->unk04) {
                    best = entry->unk04;
                    mecha->unk67C = entry->unk20;
                }
            }
        }
        if (mecha->unk674 != 0) {
            if (mecha->unk688 < 0) {
                if (work->unk000E == 3) {
                    mecha->unk688 = fn_1_934(0x8A5, &mecha->unk67C);
                } else {
                    mecha->unk688 = fn_1_934(0x8AD, &mecha->unk67C);
                }
            } else {
                fn_1_964(mecha->unk688, &mecha->unk67C);
            }
        }
        if (mecha->unk674 != 0) {
            color = lbl_1_data_A10;
            if (mecha->unk676 < 0) {
                mecha->unk676 = Hu3DGLightCreateV(&lbl_1_data_9F8, &lbl_1_data_A04, &lbl_1_data_A10);
                Hu3DGLightStaticSet(mecha->unk676, TRUE);
                Hu3DGLightSpotSet(mecha->unk676, GX_SP_COS, 30.0f);
                Hu3DGLightInfinitytSet(mecha->unk676);
            }
            if (mecha->unk676 >= 0) {
                lightPos.x = sum.x / mecha->unk674;
                lightPos.y = 1000.0f;
                lightPos.z = sum.z / mecha->unk674;
                scale = (work->unk0008 % 4) / 4.0f;
                scale = 0.7f + 0.3f * HuSin(180.0f * scale);
                scale *= mecha->unk674 / 34.0f;
                color.r = lbl_1_data_A10.r * scale;
                color.g = lbl_1_data_A10.g * scale;
                color.b = lbl_1_data_A10.b * scale;
                color.a = 0xFF;
                Hu3DGLightPosSetV(mecha->unk676, &lightPos, &lbl_1_data_A04);
                Hu3DGLightColorSet(mecha->unk676, color.r, color.g, color.b, color.a);
            }
        } else if (mecha->unk676 >= 0) {
            Hu3DGLightColorSet(mecha->unk676, 0, 0, 0, 0);
            Hu3DGLightKill(mecha->unk676);
            mecha->unk676 = -1;
        }
    }
}

/* 47 insns. Launch one Mechakoopa from pos heading angle (koopa.c / koopaboss.c); returns it, or
   NULL when all 34 are out. Alternates the model variant. */
M562_MECHAENTRY *fn_1_181FC(M562_MECHAKOOPA *mecha, HuVecF *pos, float angle)
{
    s32 i;
    M562_MECHAENTRY *entry;
    M562_MECHAENTRY *result;

    result = NULL;
    for (i = 0; i < 34; i++) {
        entry = &mecha->unk00C[i];
        if (entry->unk0C == 0) {
            fn_1_18D28(entry, pos, angle, lbl_1_bss_7840[0] & 1);
            lbl_1_bss_7840[0]++;
            result = entry;
            break;
        }
    }
    return result;
}

/* 117 insns. One Mechakoopa: links of both masters, hidden. */
void fn_1_182B8(M562_MECHAENTRY *entry, M562_MECHAKOOPA *mecha)
{
    HU3DMODELID modelId;
    M562_MECHAKOOPA *m;
    M562_WORK *work;
    M562_CAMERA *camera;

    m = mecha;
    work = m->unk000;
    camera = &work->camera[0];
    memset(entry, 0, sizeof(M562_MECHAENTRY));
    entry->unk00 = mecha;
    entry->unk06 = modelId = Hu3DModelLink(m->unk66C);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(modelId, m->unk670);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
    entry->unk08 = modelId = Hu3DModelLink(m->unk66E);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionSet(modelId, m->unk672);
    Hu3DMotionSpeedSet(modelId, 1.0f);
    Hu3DModelAttrReset(modelId, HU3D_MOTATTR_LOOP);
}

/* 18 insns. One Mechakoopa kill. */
void fn_1_1848C(M562_MECHAENTRY *entry)
{
    Hu3DModelKill(entry->unk08);
    Hu3DModelKill(entry->unk06);
    memset(entry, 0, sizeof(M562_MECHAENTRY));
}

/* 533 insns. One Mechakoopa frame over 32 frames: a hop from its start along its own heading
   (phase 3: blended towards the thrower's current heading) that lands and grows; registers a hit
   sphere in koopa's (phase 3) or koopaboss's (phase 4) hit group. Returns 1 when done. */
s32 fn_1_184D4(M562_MECHAENTRY *entry)
{
    HuVecF dir;
    HuVecF pos;
    HuVecF a;
    HuVecF b;
    float t;
    float height;
    float dist;
    float scale;
    float base;
    s16 maxTime;
    s32 ret;
    M562_MECHAKOOPA *mecha;
    M562_WORK *work;
    M562_KOOPA *koopa;

    mecha = entry->unk00;
    work = mecha->unk000;
    koopa = &work->koopa;
    ret = 0;
    if (entry->unk0C == 0) {
        Hu3DModelAttrSet(entry->unk06, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(entry->unk08, HU3D_ATTR_DISPOFF);
        return 1;
    }
    maxTime = 32;
    if (work->unk000E == 3) {
        dist = 500.0f;
        base = 130.0f;
    } else {
        dist = 1800.0f;
        base = 150.0f;
    }
    t = (float)entry->unk04 / maxTime;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    if (work->unk000E == 3) {
        dist *= t;
        dir.x = HuSin(entry->unk10);
        dir.y = 0.0f;
        dir.z = HuCos(entry->unk10);
        PSVECScale(&dir, &dir, dist);
        PSVECAdd(&entry->unk14, &dir, &a);
        dir.x = HuSin(mecha->unk678);
        dir.y = 0.0f;
        dir.z = HuCos(mecha->unk678);
        PSVECScale(&dir, &dir, dist);
        PSVECAdd(&entry->unk14, &dir, &b);
        pos.x = a.x * (t * t) + b.x * (1.0f - t * t);
        pos.z = a.z * (t * t) + b.z * (1.0f - t * t);
        height = 90.0f + 270.0f * t;
        height = (height > 270.0f) ? 270.0f : ((height < 90.0f) ? 90.0f : height);
        pos.y = 0.5 * (1.0 + HuSin(height));
        pos.y = base + pos.y * (entry->unk14.y - base);
        scale = 6.0f * (0.05f + 0.95f * (t * t));
    } else {
        dir.x = HuSin(entry->unk10);
        dir.y = 0.0f;
        dir.z = HuCos(entry->unk10);
        dist *= t;
        PSVECScale(&dir, &dir, dist);
        PSVECAdd(&entry->unk14, &dir, &pos);
        height = 90.0f + 380.0f * t;
        height = (height > 270.0f) ? 270.0f : ((height < 90.0f) ? 90.0f : height);
        pos.y = 0.5 * (1.0 + HuSin(height));
        pos.y = base + pos.y * ((entry->unk14.y - 50.0f) - base);
        scale = 8.0f * (0.15f + 0.85f * t);
    }
    entry->unk20 = pos;
    Hu3DModelPosSet(entry->unk06, pos.x, pos.y, pos.z);
    Hu3DModelPosSet(entry->unk08, pos.x, pos.y, pos.z);
    Hu3DModelScaleSet(entry->unk06, scale, scale, scale);
    Hu3DModelScaleSet(entry->unk08, scale, scale, scale);
    if (entry->unk2C != 0) {
        Hu3DModelAttrReset(entry->unk06, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(entry->unk08, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrSet(entry->unk06, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(entry->unk08, HU3D_ATTR_DISPOFF);
    }
    if (work->unk000E == 3) {
        fn_1_2CE8C(&work->unk286C[1], 4, 0, &pos, 50.0f * (0.2f + 0.8f * t), NULL);
    } else if (work->unk000E == 4) {
        fn_1_2CE8C(&work->unk286C[2], 4, 0, &pos, 250.0f * (0.1f + 0.9f * t), NULL);
        pos.y = 50.0f;
        fn_1_2CE8C(&work->unk286C[2], 4, 0, &pos, 250.0f * (0.1f + 0.9f * t), NULL);
    }
    if (++entry->unk04 >= maxTime) {
        Hu3DModelAttrSet(entry->unk06, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(entry->unk08, HU3D_ATTR_DISPOFF);
        entry->unk0C = 0;
        mecha->unk674--;
        ret = 1;
    }
    return ret;
}

/* 88 insns. Start one Mechakoopa at pos. */
void fn_1_18D28(M562_MECHAENTRY *entry, HuVecF *pos, float angle, s32 variant)
{
    M562_MECHAKOOPA *mecha;
    M562_WORK *work;

    mecha = entry->unk00;
    work = mecha->unk000;
    if (entry->unk0C == 0) {
        entry->unk20 = *pos;
        entry->unk14 = entry->unk20;
        entry->unk10 = angle;
        entry->unk0C = 1;
        entry->unk2C = variant;
        Hu3DModelPosSet(entry->unk06, pos->x, pos->y, pos->z);
        Hu3DModelPosSet(entry->unk08, pos->x, pos->y, pos->z);
        Hu3DModelScaleSet(entry->unk06, 0.0f, 0.0f, 0.0f);
        Hu3DModelScaleSet(entry->unk08, 0.0f, 0.0f, 0.0f);
        Hu3DMotionTimeSet(entry->unk06, 0.0f);
        Hu3DMotionTimeSet(entry->unk08, 0.0f);
        entry->unk04 = 0;
        mecha->unk674++;
    }
}
