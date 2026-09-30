/*
 * m577Dll effect.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m577Dll/asm/REL/m577Dll/effect.s.
 */

#include "REL/m577Dll.h"

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
/* 0x200 */ /* float lbl_1_rodata_200 = 0.0f; */
/* 0x204 */ /* float lbl_1_rodata_204 = 100.0f; */
/* 0x208 */ /* float lbl_1_rodata_208 = 10000.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 0.5f; */
/* 0x210 */ /* float lbl_1_rodata_210 = 30.0f; */
/* 0x214 */ /* float lbl_1_rodata_214 = 3.0f; */
/* 0x218 */ /* float lbl_1_rodata_218 = 150.0f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 6.0f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 255.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = 1.0f; */
/* 0x228 */ /* double lbl_1_rodata_228 = 4503601774854144; */

/* --- functions (reference order) --- */
/* 82 insns. Create the particle emitter for one camera; data hooked to fn_1_B730. */
void fn_1_B5D4(M577_EFFECT *eff, u16 cameraBit, HuVecF *pos)
{
    ANIMDATA *anim;
    HU3DMODELID mdlId;
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 num;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x84001F, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 31);
    Hu3DModelLayerSet(mdlId, 4);
    Hu3DParticleHookSet(mdlId, fn_1_B730);
    Hu3DModelCameraSet(mdlId, cameraBit);
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleColSet(mdlId, 255, 255, 255);
    Hu3DParticleScaleSet(mdlId, 0.0f);
    eff->unk00C = mdlId;
    eff->unk004 = anim;
    eff->unk000 = Hu3DData[mdlId].hookData;
    eff->unk000->emitCnt = 0;
    eff->unk000->work = eff;
    data = eff->unk000->data;
    num = eff->unk000->maxCnt;
    for (i = 0; i < num; i++, data++) {
        data->scale = 0.0f;
        data->time = 0;
        data->parManId = 0;
    }
    eff->unk008 = pos;
}

/* 1 insn. */
void fn_1_B71C(M577_EFFECT *eff)
{
}

/* 4 insns. */
void fn_1_B720(M577_EFFECT *eff, s32 mode)
{
    eff->unk000->emitCnt = (s16)mode;
}

/* 157 insns. Particle hook: while emitCnt is set, emit one particle a frame at *eff->unk008. */
void fn_1_B730(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M577_EFFECT *eff;
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 num;
    float t;
    float alpha;
    u8 a;

    if (particle->emitCnt != 0) {
        data = particle->data;
        num = particle->maxCnt;
        for (i = 0; i < num; i++, data++) {
            if (data->parManId == 0) {
                eff = particle->work;
                data->parManId = 1;
                data->pos = *eff->unk008;
                data->pos.x += 100.0f * ((s32)frandmod(10001) / 10000.0f - 0.5f);
                data->pos.y += 30.0f;
                data->pos.z -= 3.0f;
                data->color.r = 255;
                data->color.g = 255;
                data->color.b = 255;
                data->color.a = 255;
                break;
            }
        }
    }
    data = particle->data;
    num = particle->maxCnt;
    for (i = 0; i < num; i++, data++) {
        if (data->parManId != 0) {
            data->time++;
            t = data->time / 30.0f;
            data->scale = 150.0f * t;
            data->pos.z += 6.0f;
            alpha = 255.0f * (1.0f - t);
            a = alpha;
            data->color.a = alpha;
            if (data->time == 30) {
                data->scale = 0.0f;
                data->time = 0;
                data->parManId = 0;
            }
        }
    }
}
