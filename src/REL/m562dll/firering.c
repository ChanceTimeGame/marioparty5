/*
 * m562dll firering.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/firering.s.
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
static const float lbl_1_rodata_7C0 = 650.0f; /* 0x7C0 */
static const float lbl_1_rodata_7C4 = 60.0f; /* 0x7C4 */
static const float lbl_1_rodata_7C8 = 120.0f; /* 0x7C8 */
static const double lbl_1_rodata_7D0 = 3.141592653589793; /* 0x7D0 */
static const double lbl_1_rodata_7D8 = 180.0; /* 0x7D8 */
static const float lbl_1_rodata_7E0 = 40.0f; /* 0x7E0 */
static const float lbl_1_rodata_7E4 = 380.0f; /* 0x7E4 */
static const float lbl_1_rodata_7E8 = 450.0f; /* 0x7E8 */
static const float lbl_1_rodata_7EC = 200.0f; /* 0x7EC */
static const float lbl_1_rodata_7F0 = 1.0f; /* 0x7F0 */
/* 0x7F8 lbl_1_rodata_7F8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_800 = 150.0f; /* 0x800 */
static const float lbl_1_rodata_804 = 300.0f; /* 0x804 */
static const float lbl_1_rodata_808 = 360.0f; /* 0x808 */
static const float lbl_1_rodata_80C = 0.4f; /* 0x80C */
static const float lbl_1_rodata_810 = 0.6f; /* 0x810 */
static const float lbl_1_rodata_814 = 0.5f; /* 0x814 */
static const float lbl_1_rodata_818 = 420.0f; /* 0x818 */
static const float lbl_1_rodata_81C = 800.0f; /* 0x81C */
static const float lbl_1_rodata_820 = -420.0f; /* 0x820 */
static const float lbl_1_rodata_824 = 75.0f; /* 0x824 */
static const float lbl_1_rodata_828 = -190.0f; /* 0x828 */
static const float lbl_1_rodata_82C = -610.0f; /* 0x82C */
static const float lbl_1_rodata_830 = 190.0f; /* 0x830 */
static const float lbl_1_rodata_834 = 610.0f; /* 0x834 */
static const float lbl_1_rodata_838 = 0.0f; /* 0x838 */
static const float lbl_1_rodata_83C = 50.0f; /* 0x83C */
static const float lbl_1_rodata_840 = 20.0f; /* 0x840 */
static const double lbl_1_rodata_848 = 1.0; /* 0x848 */
/* 0x850 lbl_1_rodata_850 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_85C = 3.0f; /* 0x85C */
/* 0x860 lbl_1_rodata_860 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x861 lbl_1_rodata_861 (0x3): 0xE0, 0xE0, 0xE0 -- an aggregate initialiser, write it as a local */
/* 0x864 lbl_1_rodata_864 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x865 lbl_1_rodata_865 (0x3): 0xE0, 0xD0, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_868 = 36.0f; /* 0x868 */
static const float lbl_1_rodata_86C = 0.25f; /* 0x86C */
static const double lbl_1_rodata_870 = 0.699999988079071; /* 0x870 */
static const double lbl_1_rodata_878 = 0.30000001192092896; /* 0x878 */
static const float lbl_1_rodata_880 = 180.0f; /* 0x880 */
static const float lbl_1_rodata_884 = 0.75f; /* 0x884 */
static const float lbl_1_rodata_888 = 80.0f; /* 0x888 */
static const float lbl_1_rodata_88C = 140.0f; /* 0x88C */
static const float lbl_1_rodata_890 = 2.0f; /* 0x890 */
static const float lbl_1_rodata_894 = 1000.0f; /* 0x894 */
/* 0x898 lbl_1_rodata_898 = 4503599627370496: int->float conversion constant, compiler-generated */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x786C */ M562_FRPATH lbl_1_bss_786C; /* fork G: control-point path of fn_1_1C418/fn_1_1D9F8 */
/* 0x7860 */ HuVecF lbl_1_bss_7860; /* ring 0 centre saved by fn_1_1B9D4 (fork F: was float[3]) */
/* 0x7854 */ HuVecF lbl_1_bss_7854; /* ring 1 centre */
/* 0x7848 */ HuVecF lbl_1_bss_7848; /* ring 2 centre */

/* --- functions (reference order), .data placed before its first user --- */
/* 53 insns */
void fn_1_18E88(M562_FIRERING *firering, M562_WORK *work)
{
    M562_WORK *workP = work;
    s32 i;
    M562_FIRERINGSUB *sub;

    memset(firering, 0, sizeof(M562_FIRERING));
    firering->unk00 = work;
    firering->unk10 = 0;
    firering->unkCC = -1;
    firering->unkB8 = HuSprAnimRead(HuDataSelHeapReadNum(0x75006A, HU_MEMNUM_OVL, HEAP_MODEL));
    firering->unkBC = HuSprAnimRead(HuDataSelHeapReadNum(0x75006B, HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 3; i++) {
        sub = &firering->unk18[i];
        fn_1_19790(sub, i, firering);
    }
}

/* 27 insns */
void fn_1_18F5C(M562_FIRERING *firering)
{
    M562_WORK *work = firering->unk00;
    s32 i;

    for (i = 0; i < 3; i++) {
        fn_1_19A3C(&firering->unk18[i]);
    }
    memset(firering, 0, sizeof(M562_FIRERING));
}

/* 340 insns */
void fn_1_18FC8(M562_FIRERING *firering)
{
    M562_WORK *work;
    M562_PLAYER *player;
    s32 i;
    M562_FIRERINGSUB *sub;
    float ang;
    float radius;
    float t;
    HuVecF pos;

    work = firering->unk00;
    player = &work->player;
    if (firering->unk14 == 0) {
        if (firering->unk04 == 4) {
            firering->unk04 = 4;
        }
        else if (firering->unk04 >= 1) {
            firering->unk04 = 1;
        }
    }
    switch (firering->unk04) {
    case 0:
        radius = 650.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        fn_1_19518(firering);
        firering->unk0C = 0;
        firering->unk08 = 0;
        firering->unk04 = 1;
    case 1:
        if (firering->unk14 != 0) {
            if (firering->unkCC >= 0) {
                fn_1_83C(firering->unkCC);
                firering->unkCC = -1;
            }
            firering->unk08 = 0;
            firering->unk04 = 2;
        }
        break;
    case 2:
        if (firering->unkCC < 0) {
            firering->unkCC = fn_1_814(0x8A2);
        }
        t = firering->unk08 / 60.0f;
        radius = 450.0f + 200.0f * (1.0f - t);
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        if (++firering->unk08 >= 60) {
            MgTimerModeOnSet(work->unk0024, 1);
            firering->unk08 = 0;
            firering->unk04 = 3;
            firering->unk0A = 0;
            firering->unk06 = 0;
        }
        break;
    case 3:
        if (firering->unkCC < 0) {
            firering->unkCC = fn_1_814(0x8A2);
        }
        if (fn_1_19694(firering, firering->unkC0[firering->unk0C]) != 0) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            firering->unk0C++;
            if (firering->unk0C >= 6) {
                firering->unk0C = 0;
                firering->unk08 = 0;
                firering->unk04 = 4;
            }
            else if (firering->unkCC >= 0) {
                fn_1_83C(firering->unkCC);
                firering->unkCC = -1;
            }
        }
        break;
    case 4:
        break;
    }
    for (i = 0; i < 3; i++) {
        sub = &firering->unk18[i];
        if (firering->unk10 != 0) {
            sub->unk08 = 1;
        }
        else {
            sub->unk08 = 0;
        }
        fn_1_19A98(sub);
        if (sub->unk0C != 0 && firering->unk04 != 4 && work->unk000C == 4 && fn_1_1A728(sub) != 0) {
            if ((player->unk004 == 1 || player->unk004 == 2) && player->unk010 == 0) {
                player->unk00A = 0;
                player->unk006 = 0;
                player->unk008 = 0;
                player->unk004 = 4;
            }
        }
    }
}

/* 95 insns */
void fn_1_19518(M562_FIRERING *firering)
{
    M562_WORK *work;
    s32 i;
    s32 hard;
    s32 j;
    s16 pattern;
    s32 used;

    work = firering->unk00;
    for (i = 0; i < 6; i++) {
        hard = 0;
        do {
            if (work->unk0020 == 0) {
                if (i == 1 || i == 3 || i == 4 || i == 5) {
                    hard = 1;
                }
            }
            else if (work->unk0020 == 1) {
                if (i == 3 || i == 4 || i == 5) {
                    hard = 1;
                }
            }
            else if (work->unk0020 == 2) {
                if (i == 4 || i == 5) {
                    hard = 1;
                }
            }
            else if (i == 5) {
                hard = 1;
            }
            if (hard) {
                pattern = frand() % 5 + 5;
            }
            else {
                pattern = frand() % 5;
            }
            used = 0;
            for (j = 0; j < i; j++) {
                if (firering->unkC0[j] == pattern) {
                    used = 1;
                    break;
                }
            }
        } while (used);
        firering->unkC0[i] = pattern;
    }
}

/* 63 insns */
s32 fn_1_19694(M562_FIRERING *firering, s16 pattern)
{
    s32 result = 0;

    switch (pattern) {
    case 0:
        result = fn_1_1A804(firering);
        break;
    case 1:
        result = fn_1_1AC94(firering);
        break;
    case 2:
        result = fn_1_1AFB4(firering);
        break;
    case 3:
        result = fn_1_1B4FC(firering);
        break;
    case 4:
        result = fn_1_1B9D4(firering);
        break;
    case 5:
        result = fn_1_1BD6C(firering);
        break;
    case 6:
        result = fn_1_1C418(firering);
        break;
    case 7:
        result = fn_1_1CCC4(firering);
        break;
    case 8:
        result = fn_1_1D320(firering);
        break;
    case 9:
        result = fn_1_1D9F8(firering);
        break;
    }
    return result;
}

/* 171 insns */
void fn_1_19790(M562_FIRERINGSUB *sub, s16 index, M562_FIRERING *firering)
{
    M562_FIRERING *parent;
    M562_WORK *work;
    HuVecF *src;
    M562_CAMERA *camera;
    s32 i;
    HU3DPARTICLEDATA *particleDataP;
    s16 modelId;
    HU3DPARTICLE *particleP;

    parent = firering;
    work = parent->unk00;
    camera = &work->camera[0];
    memset(sub, 0, sizeof(M562_FIRERINGSUB));
    sub->unk00 = firering;
    {
        HuVecF zero = { 0.0f, 0.0f, 0.0f };
        src = &zero;
        sub->unk1C = *src;
    }
    sub->unk2C = 800.0f;
    sub->unk16 = 80;
    sub->unk30 = -1;
    sub->unk08 = sub->unk0C = 0;
    sub->unk14 = index;
    sub->unk28 = 360.0f / sub->unk16 / 3.0f * index;

    modelId = Hu3DParticleCreate(parent->unkB8, 80);
    sub->unk10 = modelId;
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DParticleHookSet(modelId, fn_1_1A6E8);
    Hu3DParticleBlendModeSet(modelId, 0);
    Hu3DParticleAnimModeSet(modelId, 0);
    particleP = Hu3DData[modelId].hookData;
    particleP->emitCnt = 0;
    particleP->work = NULL;
    particleP->count = 1;
    for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; particleDataP++, i++) {
        particleDataP->scale = 0.0f;
    }

    modelId = Hu3DParticleCreate(parent->unkBC, 160);
    sub->unk12 = modelId;
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DParticleHookSet(modelId, fn_1_1A6E8);
    Hu3DParticleBlendModeSet(modelId, 0);
    Hu3DParticleAnimModeSet(modelId, 0);
    particleP = Hu3DData[modelId].hookData;
    particleP->emitCnt = 0;
    particleP->work = NULL;
    particleP->count = 1;
    for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; particleDataP++, i++) {
        particleDataP->scale = 0.0f;
    }
}

/* 23 insns */
void fn_1_19A3C(M562_FIRERINGSUB *sub)
{
    if (sub->unk30 >= 0) {
        Hu3DGLightKill(sub->unk30);
    }
    Hu3DModelKill(sub->unk12);
    Hu3DModelKill(sub->unk10);
    memset(sub, 0, sizeof(M562_FIRERINGSUB));
}

/* lbl_1_data_A8C..AA8 are DEFINED after fn_1_1D9F8 (fork G): the reference .data has jumptable_1_data_A58
   (fn_1_1D9F8's switch) before them, and CW emits a switch table when its function is compiled. */
extern HuVecF lbl_1_data_A8C;
extern HuVecF lbl_1_data_A98;
extern GXColor lbl_1_data_AA4;
extern GXColor lbl_1_data_AA8;

/* 788 insns */
void fn_1_19A98(M562_FIRERINGSUB *sub)
{
    M562_FIRERING *firering = sub->unk00;
    M562_WORK *work = firering->unk00;
    M562_CAMERA *camera = &work->camera[0];
    HuVecF lightPos;
    GXColor color1 = { 0xFF, 0xE0, 0xE0, 0xE0 };
    GXColor color2 = { 0xFF, 0xE0, 0xD0, 0xFF };
    GXColor lightColor;
    HU3DPARTICLE *particleP;
    HU3DPARTICLE *particle2P;
    HU3DPARTICLEDATA *particleDataP;
    HU3DPARTICLEDATA *particleData2P;
    HU3DPARTICLE *clearP;
    HU3DPARTICLEDATA *clearDataP;
    s32 i;
    float t;
    float ang;

    if (sub->unk08 != 0 && sub->unk0C == 0) {
        sub->unk30 = Hu3DGLightCreateV(&lbl_1_data_A8C, &lbl_1_data_A98, &lbl_1_data_AA4);
        Hu3DGLightStaticSet(sub->unk30, TRUE);
        Hu3DGLightSpotSet(sub->unk30, GX_SP_COS, 36.0f);
        sub->unk0C = 1;
        sub->unk18 = 0;
    }
    else if (sub->unk08 == 0 && sub->unk0C != 0) {
        clearP = Hu3DData[sub->unk10].hookData;
        for (clearDataP = clearP->data, i = 0; i < clearP->maxCnt; clearDataP++, i++) {
            clearDataP->scale = 0.0f;
        }
        clearP = Hu3DData[sub->unk12].hookData;
        for (clearDataP = clearP->data, i = 0; i < clearP->maxCnt; clearDataP++, i++) {
            clearDataP->scale = 0.0f;
        }
        sub->unk0C = 0;
    }
    if (sub->unk0C == 0) {
        if (sub->unk30 >= 0) {
            if (sub->unk18 > 0) {
                t = sub->unk18 / 120.0f;
                Hu3DGLightColorSet(sub->unk30, lbl_1_data_AA8.r * t, lbl_1_data_AA8.g * t, lbl_1_data_AA8.b * t, lbl_1_data_AA8.a * t);
                sub->unk18--;
            }
            else if (sub->unk18 == 0) {
                Hu3DGLightKill(sub->unk30);
                sub->unk30 = -1;
            }
        }
        return;
    }
    if (sub->unk18 < 120 && sub->unk30 >= 0) {
        t = sub->unk18 / 120.0f;
        Hu3DGLightColorSet(sub->unk30, lbl_1_data_AA8.r * t, lbl_1_data_AA8.g * t, lbl_1_data_AA8.b * t, lbl_1_data_AA8.a * t);
        sub->unk18++;
    }
    else if (sub->unk18 >= 120) {
        lightColor = lbl_1_data_AA8;
        t = (work->unk0008 % 4) / 4.0f;
        t = 0.7f + 0.3f * HuSin(180.0f * t);
        lightColor.r = lbl_1_data_AA8.r * t;
        Hu3DGLightColorSet(sub->unk30, lightColor.r, lightColor.g, lightColor.b, lightColor.a);
    }
    t = sub->unk2C / 800.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    t = 0.25f + 0.75f * t;
    sub->unk16 = 80.0f * t;
    particleP = Hu3DData[sub->unk10].hookData;
    particleDataP = particleP->data;
    particle2P = Hu3DData[sub->unk12].hookData;
    particleData2P = particle2P->data;
    for (i = 0; i < particleP->maxCnt; i++) {
        if (i >= sub->unk16) {
            particleDataP->scale = 0.0f;
            particleDataP++;
            particleData2P->scale = 0.0f;
            particleData2P++;
            particleData2P->scale = 0.0f;
            particleData2P++;
            continue;
        }
        ang = sub->unk28 + i * (360.0f / sub->unk16);
        particleDataP->cameraBit = camera->unk04;
        particleDataP->pos.x = sub->unk1C.x + sub->unk2C * HuSin(ang);
        particleDataP->pos.y = 40.0f + sub->unk1C.y;
        particleDataP->pos.z = sub->unk1C.z + sub->unk2C * HuCos(ang);
        particleDataP->scale = (i & 1) ? 120.0f : 140.0f;
        particleDataP->color = color1;
        particleDataP++;

        ang = sub->unk28 + 2.0f * i * (360.0f / (sub->unk16 * 2));
        particleData2P->cameraBit = camera->unk04;
        particleData2P->pos.x = sub->unk1C.x + sub->unk2C * HuSin(ang);
        particleData2P->pos.y = 40.0f + sub->unk1C.y;
        particleData2P->pos.z = sub->unk1C.z + sub->unk2C * HuCos(ang);
        particleData2P->scale = 50.0f;
        particleData2P->color = color2;
        particleData2P++;

        ang = sub->unk28 + (1.0f + 2.0f * i) * (360.0f / (sub->unk16 * 2));
        particleData2P->cameraBit = camera->unk04;
        particleData2P->pos.x = sub->unk1C.x + sub->unk2C * HuSin(ang);
        particleData2P->pos.y = 40.0f + sub->unk1C.y;
        particleData2P->pos.z = sub->unk1C.z + sub->unk2C * HuCos(ang);
        particleData2P->scale = 80.0f;
        particleData2P->color = color2;
        particleData2P++;
    }
    t = (sub->unk2C - 190.0f) / 610.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    lightPos = sub->unk1C;
    lightPos.y += 1000.0f * t;
    Hu3DGLightPosSetV(sub->unk30, &lightPos, &lbl_1_data_A98);
    sub->unk28 -= 0.5f;
    sub->unk04++;
}

/* 16 insns */
void fn_1_1A6E8(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *particleDataP = particleP->data;

    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}

/* 55 insns */
s32 fn_1_1A728(M562_FIRERINGSUB *sub)
{
    M562_FIRERING *firering;
    M562_WORK *work;
    M562_PLAYER *player;
    s32 result;
    float dist;
    HuVecF dir;

    firering = sub->unk00;
    work = firering->unk00;
    player = &work->player;
    result = 0;
    VECSubtract(&player->unk0A0, &sub->unk1C, &dir);
    dir.y = 0.0f;
    dist = VECMag(&dir);
    if (dist >= sub->unk2C - 50.0f && dist <= 50.0f + sub->unk2C && player->unk0A0.y < 50.0f) {
        result = 1;
    }
    return result;
}

/* 292 insns */
s32 fn_1_1A804(M562_FIRERING *firering)
{
    s32 result;
    s32 i;
    M562_FIRERINGSUB *sub;
    float radius;
    float ang;
    float t;
    HuVecF pos;

    result = 0;
    switch (firering->unk06) {
    case 0:
        radius = 450.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        firering->unk0A = 0;
        firering->unk06++;
    case 1:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= 1.0f - t;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
        }
        if (firering->unk0A++ >= 150) {
            firering->unk0A = 0;
            firering->unk06++;
        }
        break;
    case 2:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= t;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
        }
        if (++firering->unk0A >= 150) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 200 insns */
s32 fn_1_1AC94(M562_FIRERING *firering)
{
    s32 result;
    s32 i;
    M562_FIRERINGSUB *sub;
    float ang;
    float radius;
    float t;
    HuVecF pos;

    result = 0;
    switch (firering->unk06) {
    case 0:
        radius = 450.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        firering->unk0A = 0;
        firering->unk06++;
    case 1:
        radius = 450.0f;
        t = firering->unk0A / 300.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            ang -= 360.0f * t;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
        }
        if (++firering->unk0A >= 300) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 338 insns */
s32 fn_1_1AFB4(M562_FIRERING *firering)
{
    s32 result;
    s32 i;
    M562_FIRERINGSUB *sub;
    float radius;
    float ang;
    float t;
    HuVecF pos;

    result = 0;
    switch (firering->unk06) {
    case 0:
        radius = 450.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        firering->unk0A = 0;
        firering->unk06++;
    case 1:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= 0.4f + 0.6f * (1.0f - t);
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f * (0.5f + 0.5f * (1.0f - t));
        }
        if (firering->unk0A++ >= 150) {
            firering->unk0A = 0;
            firering->unk06++;
        }
        break;
    case 2:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= 0.4f + 0.6f * t;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f * (0.5f + 0.5f * t);
        }
        if (++firering->unk0A >= 150) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 310 insns */
s32 fn_1_1B4FC(M562_FIRERING *firering)
{
    s32 result;
    s32 i;
    M562_FIRERINGSUB *sub;
    float radius;
    float ang;
    float t;
    HuVecF pos;

    result = 0;
    switch (firering->unk06) {
    case 0:
        radius = 450.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        firering->unk0A = 0;
        firering->unk06++;
    case 1:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= 1.0f - t;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f + 420.0f * t;
        }
        if (firering->unk0A++ >= 150) {
            firering->unk0A = 0;
            firering->unk06++;
        }
        break;
    case 2:
        radius = 450.0f;
        t = firering->unk0A / 150.0f;
        radius *= t;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 800.0f + -420.0f * t;
        }
        if (++firering->unk0A >= 150) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 230 insns */
s32 fn_1_1B9D4(M562_FIRERING *firering)
{
    M562_FIRERINGSUB *sub0;
    M562_FIRERINGSUB *sub1;
    M562_FIRERINGSUB *sub2;
    s32 result;
    s32 i;
    M562_FIRERINGSUB *sub;
    float t;
    float radius;
    float ang;
    HuVecF pos;

    sub0 = &firering->unk18[0];
    sub1 = &firering->unk18[1];
    sub2 = &firering->unk18[2];
    result = 0;
    switch (firering->unk06) {
    case 0:
        radius = 450.0f;
        for (i = 0; i < 3; i++) {
            sub = &firering->unk18[i];
            ang = 60.0f + 120.0f * i;
            pos.x = radius * HuSin(ang);
            pos.y = 40.0f;
            pos.z = radius * HuCos(ang);
            sub->unk1C = pos;
            sub->unk2C = 380.0f;
        }
        lbl_1_bss_7860 = sub0->unk1C;
        lbl_1_bss_7854 = sub1->unk1C;
        lbl_1_bss_7848 = sub2->unk1C;
        firering->unk0A = 0;
        firering->unk06++;
    case 1:
        t = firering->unk0A / 150.0f;
        sub0->unk1C.z = lbl_1_bss_7860.z + -lbl_1_bss_7860.z * t;
        sub1->unk1C.z = lbl_1_bss_7854.z + -lbl_1_bss_7854.z * t;
        sub2->unk1C.z = lbl_1_bss_7848.z + -lbl_1_bss_7848.z * t;
        if (firering->unk0A++ >= 150) {
            firering->unk0A = 0;
            firering->unk06++;
        }
        break;
    case 2:
        t = firering->unk0A / 150.0f;
        sub0->unk1C.z = lbl_1_bss_7860.z * t;
        sub1->unk1C.z = lbl_1_bss_7854.z * t;
        sub2->unk1C.z = lbl_1_bss_7848.z * t;
        if (++firering->unk0A >= 150) {
            firering->unk0A = 0;
            firering->unk06 = 0;
            result = 1;
        }
        break;
    }
    return result;
}

/* 427 insns */
s32 fn_1_1BD6C(M562_FIRERING *firering)
{
    float t;
    M562_FIRERINGSUB *ring0 = &firering->unk18[0];
    M562_FIRERINGSUB *ring1 = &firering->unk18[1];
    M562_FIRERINGSUB *ring2 = &firering->unk18[2];
    s32 result = 0;

    switch (firering->unk06) {
        case 0: {
            float radius = 450.0f;
            s32 i;
            for (i = 0; i < 3; i++) {
                M562_FIRERINGSUB *ring = &firering->unk18[i];
                float angle = 60.0f + 120.0f * i;
                HuVecF pos;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
                ring->unk2C = 380.0f;
            }
            lbl_1_bss_7860 = ring0->unk1C;
            lbl_1_bss_7854 = ring1->unk1C;
            lbl_1_bss_7848 = ring2->unk1C;
            firering->unk0A = 0;
            firering->unk06++;
        }
        case 1:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 380.0f + 420.0f * t;
            ring1->unk2C = 380.0f + -190.0f * t;
            ring2->unk2C = 380.0f + -190.0f * t;
            ring0->unk1C.x = lbl_1_bss_7860.x + -lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z + -lbl_1_bss_7860.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 2:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 800.0f + -610.0f * t;
            ring2->unk2C = 190.0f + 610.0f * t;
            ring1->unk2C = 190.0f;
            ring0->unk1C.x = lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z * t;
            ring2->unk1C.x = lbl_1_bss_7848.x + -lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z + -lbl_1_bss_7848.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 3:
            t = firering->unk0A / 75.0f;
            ring2->unk2C = 800.0f + -610.0f * t;
            ring1->unk2C = 190.0f + 610.0f * t;
            ring0->unk2C = 190.0f;
            ring2->unk1C.x = lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z * t;
            ring1->unk1C.x = lbl_1_bss_7854.x + -lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z + -lbl_1_bss_7854.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 4:
            t = firering->unk0A / 75.0f;
            ring2->unk2C = 190.0f + 190.0f * t;
            ring1->unk2C = 800.0f + -420.0f * t;
            ring0->unk2C = 190.0f + 190.0f * t;
            ring1->unk1C.x = lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 555 insns */
s32 fn_1_1C418(M562_FIRERING *firering)
{
    float t;
    HuVecF pos;
    M562_FIRERINGSUB *ring0 = &firering->unk18[0];
    M562_FIRERINGSUB *ring1 = &firering->unk18[1];
    M562_FIRERINGSUB *ring2 = &firering->unk18[2];
    s32 result = 0;

    switch (firering->unk06) {
        case 0: {
            float radius = 450.0f;
            s32 i;
            for (i = 0; i < 3; i++) {
                M562_FIRERINGSUB *ring = &firering->unk18[i];
                float angle = 60.0f + 120.0f * i;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
                ring->unk2C = 380.0f;
            }
            fn_1_1E9C8(&lbl_1_bss_786C);
            pos.x = ring1->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring2->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring1->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring2->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring0->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring0->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring0->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring1->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            firering->unk0A = 0;
            firering->unk06++;
        }
        case 1:
            t = firering->unk0A / 60.0f;
            ring1->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 0, 2, t);
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 3, t);
            ring0->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 4, t);
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 2:
            t = firering->unk0A / 60.0f;
            ring1->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 2, t);
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 3, 4, t);
            ring0->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 5, t);
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 3:
            t = firering->unk0A / 60.0f;
            ring1->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 2, t);
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 4, t);
            ring0->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 5, 7, t);
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 4:
            t = firering->unk0A / 60.0f;
            ring1->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 4, t);
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 7, t);
            ring0->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 1, 2, t);
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 5:
            t = firering->unk0A / 60.0f;
            ring1->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 6, t);
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 1, 2, t);
            ring0->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 4, t);
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 60) {
                firering->unk0A = 0;
                firering->unk06 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 407 insns */
s32 fn_1_1CCC4(M562_FIRERING *firering)
{
    float t;
    M562_FIRERINGSUB *ring0 = &firering->unk18[0];
    M562_FIRERINGSUB *ring1 = &firering->unk18[1];
    M562_FIRERINGSUB *ring2 = &firering->unk18[2];
    s32 result = 0;

    switch (firering->unk06) {
        case 0: {
            float radius = 450.0f;
            s32 i;
            for (i = 0; i < 3; i++) {
                M562_FIRERINGSUB *ring = &firering->unk18[i];
                float angle = 60.0f + 120.0f * i;
                HuVecF pos;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
                ring->unk2C = 380.0f;
            }
            lbl_1_bss_7860 = ring0->unk1C;
            lbl_1_bss_7854 = ring1->unk1C;
            lbl_1_bss_7848 = ring2->unk1C;
            firering->unk0A = 0;
            firering->unk06++;
        }
        case 1:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 380.0f;
            ring1->unk2C = 380.0f + 420.0f * t;
            ring2->unk2C = 380.0f;
            ring1->unk1C.x = lbl_1_bss_7854.x + -lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z + -lbl_1_bss_7854.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 2:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 380.0f + 420.0f * t;
            ring1->unk2C = 800.0f + -420.0f * t;
            ring2->unk2C = 380.0f;
            ring0->unk1C.x = lbl_1_bss_7860.x + -lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z + -lbl_1_bss_7860.z * t;
            ring1->unk1C.x = lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 3:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 800.0f + -420.0f * t;
            ring1->unk2C = 380.0f;
            ring2->unk2C = 380.0f + 420.0f * t;
            ring0->unk1C.x = lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z * t;
            ring2->unk1C.x = lbl_1_bss_7848.x + -lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z + -lbl_1_bss_7848.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 4:
            t = firering->unk0A / 75.0f;
            ring0->unk2C = 380.0f;
            ring1->unk2C = 380.0f;
            ring2->unk2C = 800.0f + -420.0f * t;
            ring2->unk1C.x = lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z * t;
            if (firering->unk0A++ >= 75) {
                firering->unk0A = 0;
                firering->unk06 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 438 insns */
s32 fn_1_1D320(M562_FIRERING *firering)
{
    float t;
    M562_FIRERINGSUB *ring0 = &firering->unk18[0];
    M562_FIRERINGSUB *ring1 = &firering->unk18[1];
    M562_FIRERINGSUB *ring2 = &firering->unk18[2];
    s32 result = 0;

    switch (firering->unk06) {
        case 0: {
            float radius = 450.0f;
            s32 i;
            for (i = 0; i < 3; i++) {
                M562_FIRERINGSUB *ring = &firering->unk18[i];
                float angle = 60.0f + 120.0f * i;
                HuVecF pos;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
                ring->unk2C = 380.0f;
            }
            lbl_1_bss_7860 = ring0->unk1C;
            lbl_1_bss_7854 = ring1->unk1C;
            lbl_1_bss_7848 = ring2->unk1C;
            firering->unk0A = 0;
            firering->unk06++;
        }
        case 1:
            t = firering->unk0A / 60.0f;
            ring0->unk2C = 380.0f + 420.0f * t;
            ring1->unk2C = 380.0f + 420.0f * t;
            ring2->unk2C = 380.0f + 420.0f * t;
            ring0->unk1C.x = lbl_1_bss_7860.x + -lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z + -lbl_1_bss_7860.z * t;
            ring1->unk1C.x = lbl_1_bss_7854.x + -lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z + -lbl_1_bss_7854.z * t;
            ring2->unk1C.x = lbl_1_bss_7848.x + -lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z + -lbl_1_bss_7848.z * t;
            if (firering->unk0A++ >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 2:
            t = firering->unk0A / 60.0f;
            ring1->unk2C = 800.0f + -610.0f * t;
            ring1->unk1C.x = lbl_1_bss_7854.x * t;
            ring1->unk1C.z = lbl_1_bss_7854.z * t;
            if (firering->unk0A++ >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 3:
            t = firering->unk0A / 60.0f;
            ring0->unk2C = 800.0f + -610.0f * t;
            ring0->unk1C.x = lbl_1_bss_7860.x * t;
            ring0->unk1C.z = lbl_1_bss_7860.z * t;
            ring1->unk2C = 190.0f + 190.0f * t;
            if (firering->unk0A++ >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 4:
            t = firering->unk0A / 60.0f;
            ring2->unk2C = 800.0f + -610.0f * t;
            ring2->unk1C.x = lbl_1_bss_7848.x * t;
            ring2->unk1C.z = lbl_1_bss_7848.z * t;
            ring0->unk2C = 190.0f + 190.0f * t;
            if (firering->unk0A++ >= 60) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 5:
            t = firering->unk0A / 60.0f;
            ring2->unk2C = 190.0f + 190.0f * t;
            if (firering->unk0A++ >= 60) {
                firering->unk0A = 0;
                firering->unk06 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 1012 insns */
s32 fn_1_1D9F8(M562_FIRERING *firering)
{
    float t;
    float radius;
    float angle;
    s32 i;
    M562_FIRERINGSUB *ring;
    HuVecF pos;
    M562_FIRERINGSUB *ring0 = &firering->unk18[0];
    M562_FIRERINGSUB *ring1 = &firering->unk18[1];
    M562_FIRERINGSUB *ring2 = &firering->unk18[2];
    s32 result = 0;

    switch (firering->unk06) {
        case 0:
            radius = 450.0f;
            for (i = 0; i < 3; i++) {
                ring = &firering->unk18[i];
                angle = 60.0f + 120.0f * i;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
                ring->unk2C = 380.0f;
            }
            fn_1_1E9C8(&lbl_1_bss_786C);
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring1->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring0->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring1->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring0->unk1C.x;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring0->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring0->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = ring0->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = ring2->unk1C.z;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = ring2->unk1C.x;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            pos.x = 0.0f;
            pos.y = 0.0f;
            pos.z = 0.0f;
            fn_1_1E9F8(&lbl_1_bss_786C, &pos);
            firering->unk0A = 0;
            firering->unk06++;
        case 1:
            radius = 450.0f;
            t = firering->unk0A / 50.0f;
            radius *= 1.0f - t;
            for (i = 0; i < 3; i++) {
                ring = &firering->unk18[i];
                angle = 60.0f + 120.0f * i;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
            }
            if (firering->unk0A++ >= 50) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 2:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 0, 1, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 3:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 1, 2, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 4:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 2, 3, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 5:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 3, 4, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 6:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 4, 5, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 7:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 5, 6, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 8:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 6, 7, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 9:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 7, 8, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 10:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 8, 9, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 11:
            t = firering->unk0A / 20.0f;
            ring2->unk1C = fn_1_1EBBC(&lbl_1_bss_786C, 9, 10, t);
            ring1->unk1C = ring2->unk1C;
            ring0->unk1C = ring1->unk1C;
            ring0->unk1C.y = ring1->unk1C.y = ring2->unk1C.y = 40.0f;
            if (++firering->unk0A >= 20) {
                firering->unk0A = 0;
                firering->unk06++;
            }
            break;
        case 12:
            radius = 450.0f;
            t = firering->unk0A / 50.0f;
            radius *= t;
            for (i = 0; i < 3; i++) {
                ring = &firering->unk18[i];
                angle = 60.0f + 120.0f * i;
                pos.x = radius * HuSin(angle);
                pos.y = 40.0f;
                pos.z = radius * HuCos(angle);
                ring->unk1C = pos;
            }
            if (++firering->unk0A >= 50) {
                firering->unk0A = 0;
                firering->unk06 = 0;
                result = 1;
            }
            break;
    }
    return result;
}

/* 0xA8C */ HuVecF lbl_1_data_A8C = { 0.0f, 7000.0f, 0.0f };
/* 0xA98 */ HuVecF lbl_1_data_A98 = { 0.0f, -1.0f, 0.02f };
/* 0xAA4 */ GXColor lbl_1_data_AA4 = { 0, 0, 0, 0 };
/* 0xAA8 */ GXColor lbl_1_data_AA8 = { 160, 32, 0, 255 };

/* 12 insns */
void fn_1_1E9C8(M562_FRPATH *path)
{
    memset(path, 0, sizeof(M562_FRPATH));
}

/* 16 insns */
void fn_1_1E9F8(M562_FRPATH *path, HuVecF *pos)
{
    if (path->unk90 < 12) {
        path->unk00[path->unk90] = *pos;
        path->unk90++;
    }
}

/* 97 insns */
HuVecF fn_1_1EA38(M562_FRPATH *path, float t)
{
    HuVecF delta;
    HuVecF out;
    float step;
    s16 idx;
    float frac;

    if (t >= 1.0f) {
        t = fmod(t, 1.0);
    }
    step = 1.0f / (path->unk90 - 1);
    idx = t / step;
    VECSubtract(&path->unk00[idx + 1], &path->unk00[idx], &delta);
    frac = (t - step * idx) / step;
    VECScale(&delta, &delta, frac);
    VECAdd(&path->unk00[idx], &delta, &out);
    return out;
}

/* 160 insns */
HuVecF fn_1_1EBBC(M562_FRPATH *path, s16 start, s16 end, float t)
{
    float step = 1.0f / (path->unk90 - 1);
    float startT = start * step;
    float endT = end * step;
    float pathT = startT + t * (endT - startT);
    return fn_1_1EA38(path, pathT);
}

