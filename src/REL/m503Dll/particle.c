/*
 * m503dll particle.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/particle.s.
 */

#include "REL/m503dll.h"

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
/* 0x5A0 */ /* float lbl_1_rodata_5A0 = 0.0f; */
/* 0x5A8 */ /* double lbl_1_rodata_5A8 = 0.8; */
/* 0x5B0 */ /* double lbl_1_rodata_5B0 = 0.000030517578125; */
/* 0x5B8 */ /* double lbl_1_rodata_5B8 = 5; */
/* 0x5C0 */ /* double lbl_1_rodata_5C0 = 0.5; */
/* 0x5C8 */ /* double lbl_1_rodata_5C8 = 0.0000152587890625; */
/* 0x5D0 */ /* double lbl_1_rodata_5D0 = 200; */
/* 0x5D8 */ /* double lbl_1_rodata_5D8 = 40; */
/* 0x5E0 */ /* double lbl_1_rodata_5E0 = 360; */
/* 0x5E8 */ /* float lbl_1_rodata_5E8 = 10.0f; */
/* 0x5F0 */ /* double lbl_1_rodata_5F0 = -14000; */
/* 0x5F8 */ /* double lbl_1_rodata_5F8 = 0.9; */
/* 0x600 */ /* double lbl_1_rodata_600 = 0.05; */
/* 0x608 */ /* double lbl_1_rodata_608 = 4503601774854144; */
/* 0x610 */ /* double lbl_1_rodata_610 = 3.141592653589793; */
/* 0x618 */ /* double lbl_1_rodata_618 = 180; */
/* 0x620 */ /* float lbl_1_rodata_620 = 11.0f; */
/* 0x628 */ /* double lbl_1_rodata_628 = 0.6; */
/* 0x630 */ /* double lbl_1_rodata_630 = 2; */
/* 0x638 */ /* double lbl_1_rodata_638 = 300; */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xC4 gap_05_000000C4_bss (0x4) -- dtk filler */
/* 0xC2 */ s16 lbl_1_bss_C2;
/* 0xC0 */ s16 lbl_1_bss_C0;

/* --- functions (reference order) --- */
/* 9 insns */
void fn_1_C574(OMOBJMAN *objman)
{
    fn_1_C59C();
    fn_1_C9FC();
}

/* 1 insns */
void fn_1_C598(void) { }

/* 66 insns */
void fn_1_C59C(void)
{
    ANIMDATA *anim;
    HU3DPARTICLEDATA *data;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x3D0027, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 128);
    lbl_1_bss_C2 = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_C6A4);
    Hu3DModelLayerSet(mdlId, 1);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* 214 insns */
void fn_1_C6A4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->accel.x = 0.8 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->accel.y = 5.0 + 0.5 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->accel.z = 0.8 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->scale = 200.0 + 40.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->zRot = 360.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->color.a = 180;
            case 1:
                data->scale += 10.0f;
                data->color.a -= 2;
                if (data->pos.y < -14000.0 || data->scale <= 0.0f || data->color.a > 240) {
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

/* 83 insns */
void fn_1_C9FC(void)
{
    HU3DMODEL *model;
    M503_PARTICLE *work;
    s32 i;
    float ang;

    lbl_1_bss_C0 = Hu3DHookFuncCreate(fn_1_CB48);
    Hu3DModelLayerSet(lbl_1_bss_C0, 6);
    model = &Hu3DData[lbl_1_bss_C0];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_PARTICLE), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M503_PARTICLE));
    for (i = 0, ang = 0.0f; i < 32; i++, ang += 11.0f) {
        work->unk0A0[i] = sin(M_PI * ang / 180.0);
        work->unk120[i] = cos(M_PI * ang / 180.0);
    }
}

/* 181 insns */
void fn_1_CB48(HU3DMODEL *model, Mtx *mtx)
{
    M503_PARTICLE *work = model->hookData;
    float *sinTbl = work->unk0A0;
    float *cosTbl = work->unk120;
    M503_SARUSHADOW *p;
    HuVecF pos;
    Mtx m;
    float radius;
    float x;
    float z;
    float x0;
    float z0;
    s32 i;
    s32 j;

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (i = 0; i < 40; i++) {
        p = work->unk000[i];
        if (p != NULL) {
            if (p->unk000) {
                radius = p->unk004;
                PSVECAdd(p->unk008, p->unk00C, &pos);
                PSMTXIdentity(m);
                PSMTXTrans(m, pos.x, pos.y, pos.z);
                PSMTXConcat(*mtx, m, m);
                GXLoadPosMtxImm(m, 0);
                GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 34);
                GXPosition3f32(0.0f, 0.0f, 0.0f);
                GXColor1u32(0xA0);
                for (j = 0; j < 32; j++) {
                    z = radius * cosTbl[j];
                    x = radius * sinTbl[j];
                    GXPosition3f32(x, 0.0f, z);
                    GXColor1u32(0x10);
                }
                z0 = cosTbl[0] * radius;
                x0 = sinTbl[0] * radius;
                GXPosition3f32(x0, 0.0f, z0);
                GXColor1u32(0x10);
            }
        }
    }
}

/* 37 insns */
void fn_1_CE1C(HuVecF *pos)
{
    HU3DPARTICLE *particle = Hu3DData[lbl_1_bss_C2].hookData;
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

/* 161 insns */
void fn_1_CEB0(HuVecF *pos)
{
    HU3DPARTICLE *particle = Hu3DData[lbl_1_bss_C2].hookData;
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time < 0) {
            data->time = 1;
            data->pos = *pos;
            data->accel.x = 0.6 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
            data->accel.y = 2.0 + 0.5 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
            data->accel.z = 0.6 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
            data->scale = 300.0 + 40.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
            data->zRot = 360.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
            data->color.a = 160;
            break;
        }
    }
}

/* 32 insns */
void fn_1_D134(M503_SARUSHADOW *shadow)
{
    HU3DMODEL *model = &Hu3DData[lbl_1_bss_C0];
    M503_PARTICLE *work = model->hookData;
    M503_SARUSHADOW **slot = work->unk000;
    s32 i;

    for (i = 0; i < 40; i++, slot++) {
        if (*slot == NULL) {
            *slot = shadow;
            return;
        }
    }
}

