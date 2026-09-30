/*
 * m534dll particle effects. Functions are in reference order. Line ranges are
 * into build/mp5-asm/m534Dll/asm/REL/m534Dll/effect.s.
 * fn_1_64EC and fn_1_69E4 are HU3DPARTICLEHOOKs.
 */

#include "REL/m534Dll.h"

#include "game/data.h"
#include "game/frand.h"
#include "game/sprite.h"

#include "math.h"

/* --- .bss --- */

s16 lbl_1_bss_50;                 /* particle model (fn_1_681C) */
s16 lbl_1_bss_52;                 /* particle model (fn_1_633C); dtk sizes this 0x6 */

/* asm 9-19, 9 insns. Called from ObjectSetup; objman is not read. */
void fn_1_6314(OMOBJMAN *objman)
{
    fn_1_633C();
    fn_1_681C();
}

/* asm 22-24, 1 insn. Empty. */
void fn_1_6338(void)
{
}

/* asm 27-101, 71 insns. Dust particles (hook fn_1_64EC). */
void fn_1_633C(void)
{
    ANIMDATA *anim;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x5C000C, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 128);
    lbl_1_bss_52 = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleColSet(mdlId, 218, 203, 158);
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_64EC);
    Hu3DModelLayerSet(mdlId, 6);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* asm 104-146, 37 insns. Emit one dust particle at pos. */
void fn_1_6458(HuVecF *pos)
{
    HU3DPARTICLE *particle = Hu3DData[lbl_1_bss_52].hookData;
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time < 0) {
            data->time = 0;
            data->pos = *pos;
            break;
        }
    }
}

/* asm 149-361, 204 insns. Particle hook. */
void fn_1_64EC(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->accel.x = 0.8 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->accel.y = 0.1 + 0.2 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->accel.z = 0.8 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->scale = 10.0 + 40.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->zRot = 0.0f;
                data->color.a = 180;
            case 1:
                data->scale += 8.0f;
                data->zRot += (double)(float)(M_PI / 360);
                data->color.a -= 2;
                if (data->pos.y < -200.0 || data->scale <= 0.0f || data->color.a > 240) {
                    data->time = -1;
                    data->scale = 0.0f;
                } else {
                    data->pos.x += data->accel.x;
                    data->pos.y += data->accel.y;
                    data->pos.z += data->accel.z;
                    data->accel.x *= 0.9;
                    data->accel.y -= 0.05;
                    data->accel.z *= 0.9;
                }
                break;
        }
    }
}

/* asm 364-438, 71 insns. Spray particles (hook fn_1_69E4). */
void fn_1_681C(void)
{
    ANIMDATA *anim;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x5C000D, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 512);
    lbl_1_bss_50 = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleColSet(mdlId, 218, 203, 158);
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_69E4);
    Hu3DModelLayerSet(mdlId, 0);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* asm 441-489, 43 insns. Emit one spray particle at pos with velocity vel. */
void fn_1_6938(HuVecF *pos, HuVecF *vel)
{
    HU3DPARTICLE *particle = Hu3DData[lbl_1_bss_50].hookData;
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time < 0) {
            data->time = 0;
            data->pos = *pos;
            data->accel = *vel;
            break;
        }
    }
}

/* asm 492-626, 126 insns. Particle hook. */
void fn_1_69E4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->scale = 5.0 + 5.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->zRot = 0.0f;
                data->color.a = 50;
            case 1:
                data->scale += 0.1;
                if (data->pos.y < -100.0 || data->scale <= 0.0f || data->color.a > 240) {
                    data->time = -1;
                    data->scale = 0.0f;
                } else {
                    data->pos.x += data->accel.x;
                    data->pos.y += data->accel.y;
                    data->pos.z += data->accel.z;
                    data->accel.x *= 0.88;
                    data->accel.y -= 0.15;
                    data->accel.z *= 0.88;
                }
                break;
        }
    }
}
