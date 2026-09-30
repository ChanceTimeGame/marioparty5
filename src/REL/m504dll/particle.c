/*
 * m504dll particle.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/particle.s.
 */

#include "REL/m504dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "humath.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x380 */ /* float lbl_1_rodata_380 = 1.5f; */
/* 0x388 */ /* double lbl_1_rodata_388 = 4; */
/* 0x390 */ /* double lbl_1_rodata_390 = 3.141592653589793; */
/* 0x398 */ /* float lbl_1_rodata_398 = 270.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 45.0f; */
/* 0x3A0 */ /* double lbl_1_rodata_3A0 = 180; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 5.0f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = 150.0f; */
/* 0x3B0 */ /* double lbl_1_rodata_3B0 = 2; */
/* 0x3B8 */ /* double lbl_1_rodata_3B8 = 270; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = 22.5; */
/* 0x3C8 */ /* double lbl_1_rodata_3C8 = 4503601774854144; */
/* 0x3D0 */ /* float lbl_1_rodata_3D0 = -1.0f; */
/* 0x3D4 */ /* float lbl_1_rodata_3D4 = 0.0f; */
/* 0x3D8 */ /* double lbl_1_rodata_3D8 = 1; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 0.5; */
/* 0x3E8 */ /* float lbl_1_rodata_3E8 = 0.01f; */
/* 0x3F0 */ /* double lbl_1_rodata_3F0 = 4503599627370496; */

/* --- .data --- */
/* 0x4610 */ M504_EFFECTPARAM lbl_1_data_4610 = {
    0,
    { 0xA0, 0xA0, 0xA0, 0xFF },
    { 0x00, 0x00, 0x00, 0xFF },
    { 0.0f, 2.0f, 1.0f },
    { 0.95f, 0.99f, 0.95f },
    0.0f,
    0.0f,
    1.0f,
    -4.0f,
    0.0f,
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7844 gap_05_00007844_bss (0x4) -- dtk filler */
/* 0x7840 */ M504_EFFECTPARAM *lbl_1_bss_7840;
/* 0x7820 */ s16 lbl_1_bss_7820[16]; /* lha: m507 effect lbl_1_bss_133C twin */

/* --- functions (reference order) --- */
/* m507 fn_1_7720 exact */
void fn_1_D10C(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        lbl_1_bss_7820[i] = -1;
    }
    lbl_1_bss_7840 = NULL;
}

/* m560 effect fn_1_66DC: teardown with fn_1_D10C inlined into its tail */
void fn_1_D15C(void)
{
    if (lbl_1_bss_7840) {
        HuMemDirectFree(lbl_1_bss_7840);
        lbl_1_bss_7840 = NULL;
    }
    fn_1_D10C();
}

/* two interleaved rings of eight (m560 fn_1_6770 shape, m507 fn_1_7770 values) */
void fn_1_D1F0(s16 cameraBit, HuVecF *pos)
{
    float scale = 1.5f;
    s16 i;

    for (i = 0; i < 8; i++) {
        lbl_1_data_4610.vel.x = scale * (4.0 * sin((M_PI * (270.0f + (45.0f * i))) / 180.0));
        lbl_1_data_4610.vel.y = 5.0f;
        lbl_1_data_4610.vel.z = scale * (4.0 * cos((M_PI * (270.0f + (45.0f * i))) / 180.0));
        fn_1_D560(cameraBit, pos->x, pos->y * scale, pos->z, 150.0f, &lbl_1_data_4610);
    }
    for (i = 0; i < 8; i++) {
        lbl_1_data_4610.vel.x = scale * (2.0 * sin((M_PI * (270.0 + (22.5 + (45.0f * i)))) / 180.0));
        lbl_1_data_4610.vel.y = 5.0f;
        lbl_1_data_4610.vel.z = scale * (2.0 * cos((M_PI * (270.0 + (22.5 + (45.0f * i)))) / 180.0));
        fn_1_D560(cameraBit, pos->x, pos->y * scale, pos->z, 150.0f, &lbl_1_data_4610);
    }
}

/* m507 fn_1_7AE8 exact */
s16 fn_1_D560(s16 arg0, float arg2, float arg3, float arg4, float arg5, M504_EFFECTPARAM *arg1)
{
    s16 cameraNo;
    s16 index;
    s16 cameraBit;
    s16 result;
    HU3DMODEL *modelP;
    M504_EFFECTPARAM *paramP;
    s16 modelId;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    fn_1_D804();
    result = -1;
    cameraNo = 0;
    cameraBit = 1;
    for (; cameraNo < 16; cameraNo++, cameraBit = (s16)(cameraBit << 1)) {
        if (((cameraBit & arg0) != 0) && (Hu3DCamera[cameraNo].fov != -1.0f)) {
            modelId = lbl_1_bss_7820[cameraNo];
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
                particleDataP->vel = arg1->vel;
                particleDataP->color = arg1->colorStart;
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

/* m507 fn_1_7D8C */
void fn_1_D804(void)
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
            if (lbl_1_bss_7820[cameraNo] != -1) {
                particleP = Hu3DData[lbl_1_bss_7820[cameraNo]].hookData;
                if (particleP->anim != 0) {
                    anim = particleP->anim;
                }
            }
            else {
                if (!anim) {
                    data = HuDataSelHeapReadNum(0x3E0049, HU_MEMNUM_OVL, HEAP_MODEL);
                    anim = HuSprAnimRead(data);
                }
                lbl_1_bss_7820[cameraNo] = Hu3DParticleCreate(anim, 0x96);
                Hu3DModelLayerSet(lbl_1_bss_7820[cameraNo], 4);
                Hu3DParticleHookSet(lbl_1_bss_7820[cameraNo], fn_1_DC8C);
                Hu3DModelCameraSet(lbl_1_bss_7820[cameraNo], 1 << cameraNo);
                if (!lbl_1_bss_7840) {
                    lbl_1_bss_7840 = HuMemDirectMallocNum(HEAP_HEAP, 0x20D0, HU_MEMNUM_OVL);
                }
                Hu3DParticleBlendModeSet(lbl_1_bss_7820[cameraNo], 0);
                particleP = Hu3DData[lbl_1_bss_7820[cameraNo]].hookData;
                particleP->emitCnt = 0;
                particleP->work = lbl_1_bss_7840;
                particleP->count = 1;
                for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                    particleDataP->scale = 0.0f;
                }
            }
        }
    }
}

/* m507 fn_1_7FF0 */
void fn_1_DA68(void)
{
    s16 cameraNo;
    void *data;
    ANIMDATA *anim;
    s16 i;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    anim = NULL;
    for (cameraNo = 0; cameraNo < 16; cameraNo++) {
        if ((Hu3DCamera[cameraNo].fov != -1.0f) && (lbl_1_bss_7820[cameraNo] == -1)) {
            if (!anim) {
                data = HuDataSelHeapReadNum(0x3E0049, HU_MEMNUM_OVL, HEAP_MODEL);
                anim = HuSprAnimRead(data);
            }
            lbl_1_bss_7820[cameraNo] = Hu3DParticleCreate(anim, 0x96);
            Hu3DModelLayerSet(lbl_1_bss_7820[cameraNo], 4);
            Hu3DParticleHookSet(lbl_1_bss_7820[cameraNo], fn_1_DC8C);
            Hu3DModelCameraSet(lbl_1_bss_7820[cameraNo], 1 << cameraNo);
            if (!lbl_1_bss_7840) {
                lbl_1_bss_7840 = HuMemDirectMallocNum(HEAP_HEAP, 0x20D0, HU_MEMNUM_OVL);
            }
            Hu3DParticleBlendModeSet(lbl_1_bss_7820[cameraNo], 0);
            particleP = Hu3DData[lbl_1_bss_7820[cameraNo]].hookData;
            particleP->emitCnt = 0;
            particleP->work = lbl_1_bss_7840;
            particleP->count = 1;
            for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                particleDataP->scale = 0.0f;
            }
        }
    }
}

/* m507 fn_1_8214 exact: HU3DPARTICLEHOOK */
void fn_1_DC8C(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *particleDataP;
    M504_EFFECTPARAM *paramP;
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
            particleDataP->vel.x *= paramP[i].speedDecay.x;
            particleDataP->vel.y *= paramP[i].speedDecay.y;
            particleDataP->vel.z *= paramP[i].speedDecay.z;
            VECAdd(&particleDataP->vel, &particleDataP->pos, &particleDataP->pos);
            particleDataP->vel.y += paramP[i].accelY;

            color = particleDataP->color.r + (paramP[i].colorStep * (paramP[i].colorEnd.r - paramP[i].colorStart.r));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.r = color;

            color = particleDataP->color.g + (paramP[i].colorStep * (paramP[i].colorEnd.g - paramP[i].colorStart.g));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.g = color;

            color = particleDataP->color.b + (paramP[i].colorStep * (paramP[i].colorEnd.b - paramP[i].colorStart.b));
            if (color < 0) {
                color = 0;
            }
            else if (color > 255) {
                color = 255;
            }
            particleDataP->color.b = color;

            color = particleDataP->color.a + paramP[i].alphaStep;
            if (color < 1) {
                particleDataP->scale = 0.0f;
            }
            particleDataP->color.a = color;

            if (particleDataP->scale) {
                if (paramP[i].flags & 1) {
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
                particleDataP->scaleBase += paramP[i].scaleDecay;
                if (particleDataP->scaleBase <= 0.01f) {
                    particleDataP->scale = 0.0f;
                }
            }
            particleDataP->time++;
        }
    }
    DCStoreRangeNoSync(particleP->data, particleP->maxCnt * sizeof(HU3DPARTICLEDATA));
}
