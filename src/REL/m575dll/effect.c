/*
 * m575dll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/effect.s.
 */

#include "REL/m575dll.h"

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

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x6D0 */ /* float lbl_1_rodata_6D0 = 3.0f; */
/* 0x6D4 */ /* float lbl_1_rodata_6D4 = 10000.0f; */
/* 0x6D8 */ /* float lbl_1_rodata_6D8 = 360.0f; */
/* 0x6E0 */ /* double lbl_1_rodata_6E0 = 4; */
/* 0x6E8 */ /* double lbl_1_rodata_6E8 = 3.141592653589793; */
/* 0x6F0 */ /* double lbl_1_rodata_6F0 = 180; */
/* 0x6F8 */ /* float lbl_1_rodata_6F8 = 0.0f; */
/* 0x6FC */ /* float lbl_1_rodata_6FC = 300.0f; */
/* 0x700 */ /* double lbl_1_rodata_700 = 4503599627370496; */
/* 0x708 */ /* float lbl_1_rodata_708 = -1.0f; */
/* 0x710 */ /* double lbl_1_rodata_710 = 1; */
/* 0x718 */ /* double lbl_1_rodata_718 = 0.5; */
/* 0x720 */ /* float lbl_1_rodata_720 = 0.01f; */
/* 0x728 */ /* double lbl_1_rodata_728 = 4503601774854144; */

/* --- .data --- */
/* 0x3A0 */ M575_EFFECTPARAM lbl_1_data_3A0 = {
    0,
    { 0xA0, 0xA0, 0xA0, 0xB0 },
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
/* 0x7BB8 */ M575_EFFECTPARAM *lbl_1_bss_7BB8; /* lwz/stw; HuMemDirectMallocNum(0x20D0) */
/* 0x7B98 */ s16 lbl_1_bss_7B98[16]; /* lha/sth: particle model id per camera */

/* --- functions (reference order) --- */
/* two-step toggle on obj->memberNo (lhz 0xE): 0 -> 1, 1 -> 0 and returns 1 */
s32 fn_1_E424(OMOBJ *obj)
{
    s32 result = 0;

    switch (obj->memberNo) {
        case 0:
            obj->memberNo++;
            break;
        case 1:
            obj->memberNo = 0;
            result = 1;
            break;
    }
    return result;
}

/* m504 particle fn_1_D10C exact */
void fn_1_E478(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        lbl_1_bss_7B98[i] = -1;
    }
    lbl_1_bss_7BB8 = NULL;
}

/* m504 particle fn_1_D15C exact */
void fn_1_E4C8(void)
{
    if (lbl_1_bss_7BB8) {
        HuMemDirectFree(lbl_1_bss_7BB8);
        lbl_1_bss_7BB8 = NULL;
    }
    fn_1_E478();
}

/* one particle in a random horizontal direction */
void fn_1_E55C(s16 cameraBit, HuVecF *pos)
{
    float angle;
    float scale = 3.0f;

    angle = (frand() % 10000) / 10000.0f;
    angle *= 360.0f;
    lbl_1_data_3A0.unk00C.x = scale * (4.0 * sin((M_PI * angle) / 180.0));
    lbl_1_data_3A0.unk00C.y = scale * (4.0 * cos((M_PI * angle) / 180.0));
    lbl_1_data_3A0.unk00C.z = 0.0f;
    fn_1_E6E4(cameraBit, pos->x, pos->y * scale, pos->z, 300.0f, &lbl_1_data_3A0);
}

/* m504 particle fn_1_D560 exact */
s16 fn_1_E6E4(s16 arg0, float arg2, float arg3, float arg4, float arg5, M575_EFFECTPARAM *arg1)
{
    s16 cameraNo;
    s16 index;
    s16 cameraBit;
    s16 result;
    HU3DMODEL *modelP;
    M575_EFFECTPARAM *paramP;
    s16 modelId;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    fn_1_E988();
    result = -1;
    cameraNo = 0;
    cameraBit = 1;
    for (; cameraNo < 16; cameraNo++, cameraBit = (s16)(cameraBit << 1)) {
        if (((cameraBit & arg0) != 0) && (Hu3DCamera[cameraNo].fov != -1.0f)) {
            modelId = lbl_1_bss_7B98[cameraNo];
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

/* m504 particle fn_1_D804 with data 0x82001A */
void fn_1_E988(void)
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
            if (lbl_1_bss_7B98[cameraNo] != -1) {
                particleP = Hu3DData[lbl_1_bss_7B98[cameraNo]].hookData;
                if (particleP->anim != 0) {
                    anim = particleP->anim;
                }
            }
            else {
                if (!anim) {
                    data = HuDataSelHeapReadNum(0x82001A, HU_MEMNUM_OVL, HEAP_MODEL);
                    anim = HuSprAnimRead(data);
                }
                lbl_1_bss_7B98[cameraNo] = Hu3DParticleCreate(anim, 0x96);
                Hu3DModelLayerSet(lbl_1_bss_7B98[cameraNo], 4);
                Hu3DParticleHookSet(lbl_1_bss_7B98[cameraNo], fn_1_EE10);
                Hu3DModelCameraSet(lbl_1_bss_7B98[cameraNo], 1 << cameraNo);
                if (!lbl_1_bss_7BB8) {
                    lbl_1_bss_7BB8 = HuMemDirectMallocNum(HEAP_HEAP, 0x20D0, HU_MEMNUM_OVL);
                }
                Hu3DParticleBlendModeSet(lbl_1_bss_7B98[cameraNo], 0);
                particleP = Hu3DData[lbl_1_bss_7B98[cameraNo]].hookData;
                particleP->emitCnt = 0;
                particleP->work = lbl_1_bss_7BB8;
                particleP->count = 1;
                for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                    particleDataP->scale = 0.0f;
                }
            }
        }
    }
}

/* m504 particle fn_1_DA68 with data 0x82001A */
void fn_1_EBEC(void)
{
    s16 cameraNo;
    void *data;
    ANIMDATA *anim;
    s16 i;
    HU3DPARTICLE *particleP;
    HU3DPARTICLEDATA *particleDataP;

    anim = NULL;
    for (cameraNo = 0; cameraNo < 16; cameraNo++) {
        if ((Hu3DCamera[cameraNo].fov != -1.0f) && (lbl_1_bss_7B98[cameraNo] == -1)) {
            if (!anim) {
                data = HuDataSelHeapReadNum(0x82001A, HU_MEMNUM_OVL, HEAP_MODEL);
                anim = HuSprAnimRead(data);
            }
            lbl_1_bss_7B98[cameraNo] = Hu3DParticleCreate(anim, 0x96);
            Hu3DModelLayerSet(lbl_1_bss_7B98[cameraNo], 4);
            Hu3DParticleHookSet(lbl_1_bss_7B98[cameraNo], fn_1_EE10);
            Hu3DModelCameraSet(lbl_1_bss_7B98[cameraNo], 1 << cameraNo);
            if (!lbl_1_bss_7BB8) {
                lbl_1_bss_7BB8 = HuMemDirectMallocNum(HEAP_HEAP, 0x20D0, HU_MEMNUM_OVL);
            }
            Hu3DParticleBlendModeSet(lbl_1_bss_7B98[cameraNo], 0);
            particleP = Hu3DData[lbl_1_bss_7B98[cameraNo]].hookData;
            particleP->emitCnt = 0;
            particleP->work = lbl_1_bss_7BB8;
            particleP->count = 1;
            for (particleDataP = particleP->data, i = 0; i < particleP->maxCnt; i++, particleDataP++) {
                particleDataP->scale = 0.0f;
            }
        }
    }
}

/* m504 particle fn_1_DC8C exact: HU3DPARTICLEHOOK */
void fn_1_EE10(HU3DMODEL *modelP, HU3DPARTICLE *particleP, Mtx mtx)
{
    HU3DPARTICLEDATA *particleDataP;
    M575_EFFECTPARAM *paramP;
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
