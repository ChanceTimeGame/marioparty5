/*
 * m580Dll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/effect.s.
 */

#include "REL/m580Dll.h"

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
/* 0x5C0 */ /* float lbl_1_rodata_5C0 = 0.0f; */
/* 0x5C8 */ /* double lbl_1_rodata_5C8 = 2; */
/* 0x5D0 */ /* double lbl_1_rodata_5D0 = 0.000030517578125; */
/* 0x5D8 */ /* double lbl_1_rodata_5D8 = 5; */
/* 0x5E0 */ /* double lbl_1_rodata_5E0 = 0.0000152587890625; */
/* 0x5E8 */ /* float lbl_1_rodata_5E8 = 30.0f; */
/* 0x5F0 */ /* double lbl_1_rodata_5F0 = 4503601774854144; */
/* 0x5F8 */ /* float lbl_1_rodata_5F8 = 150.0f; */
/* 0x600 */ /* double lbl_1_rodata_600 = 11.25; */
/* 0x608 */ /* double lbl_1_rodata_608 = 360; */
/* 0x610 */ /* double lbl_1_rodata_610 = 22.5; */
/* 0x618 */ /* s32 lbl_1_rodata_618[6] = { 0x3CA3D70A, 0x00000000, 0x00000000, 0x00000000, 0x3CA3D70A, 0x00000000 }; */
/* 0x630 */ /* s32 lbl_1_rodata_630[10] = { 0x00000009, 0x00000001, 0x0000000B, 0x00000001, 0x0000000D, 0x00000001, 0x0000000E, 0x00000001, 0x000000FF, 0x00000000 }; */
/* 0x658 */ /* s32 lbl_1_rodata_658[20] = { 0x00000009, 0x00000001, 0x00000004, 0x00000000, 0x0000000B, 0x00000001, 0x00000005, 0x00000000, 0x0000000D, 0x00000001, 0x00000004, 0x00000000, 0x0000000E, 0x00000001, 0x00000004, 0x00000000, 0x000000FF, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x6A8 */ /* float lbl_1_rodata_6A8 = 205.0f; */
/* 0x6AC */ /* float lbl_1_rodata_6AC = 80.0f; */
/* 0x6B0 */ /* double lbl_1_rodata_6B0 = 0.0625; */
/* 0x6B8 */ /* float lbl_1_rodata_6B8 = 0.5f; */
/* 0x6BC */ /* float lbl_1_rodata_6BC = 1.0f; */
/* 0x6C0 */ /* float lbl_1_rodata_6C0 = 0.0025f; */
/* 0x6C4 */ /* float lbl_1_rodata_6C4 = 96.0f; */
/* 0x6C8 */ /* float lbl_1_rodata_6C8 = 24.0f; */
/* 0x6CC */ /* float lbl_1_rodata_6CC = -0.5f; */
/* 0x6D0 */ /* float lbl_1_rodata_6D0 = -1.0f; */
/* 0x6D4 */ /* float lbl_1_rodata_6D4 = 288.0f; */
/* 0x6D8 */ /* float lbl_1_rodata_6D8 = 350.0f; */
/* 0x6E0 */ /* double lbl_1_rodata_6E0 = 0.2; */
/* 0x6E8 */ /* double lbl_1_rodata_6E8 = 1; */
/* 0x6F0 */ /* double lbl_1_rodata_6F0 = 0; */
/* 0x6F8 */ /* double lbl_1_rodata_6F8 = 0.3; */
/* 0x700 */ /* double lbl_1_rodata_700 = 1.5; */
/* 0x708 */ /* double lbl_1_rodata_708 = 0.1; */

/* --- .data --- */
/* 0x7A0 */ s32 lbl_1_data_7A0[16] = { 0x00860025, 0x00860026, 0x00860027, 0x00860028, 0x00860029, 0x0086002A, 0x0086002B, 0x0086002C, 0x0086002D, 0x0086002E, 0x0086002F, 0x00860030, 0x00860031, 0x00860032, 0x00860025, 0x00860025 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x248 */ OMOBJ *lbl_1_bss_248; /* dtk sized it 0x8: pointer + 4-byte gap */

/* --- functions (reference order) --- */
/* 34 insns. Effect object and its work. */
void fn_1_D7E0(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_EFFECT *work;

    obj = omAddObjEx(objman, 20, 3, 0, -1, fn_1_D86C);
    lbl_1_bss_248 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_EFFECT), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_EFFECT));
}

/* 1 insns */
void fn_1_D868(void)
{
}

/* 21 insns. Create the shadow hook, banner and two particle models. */
void fn_1_D86C(OMOBJ *obj)
{
    fn_1_DF28(obj);
    fn_1_E8D0(obj);
    fn_1_D8F8(obj);
    fn_1_DC10(obj);
    obj->objFunc = fn_1_D8C0;
}

/* 14 insns. Per-frame object function. */
void fn_1_D8C0(OMOBJ *obj)
{
    fn_1_DFD8(obj);
    fn_1_E9B8(obj);
}

/* 66 insns. Particle model 0 (hook fn_1_DA00). */
void fn_1_D8F8(OMOBJ *obj)
{
    ANIMDATA *anim;
    HU3DPARTICLEDATA *data;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x860022, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 256);
    obj->mdlId[0] = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_DA00);
    Hu3DModelLayerSet(mdlId, 5);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* 132 insns. Particle hook 0: white puff, fades by 8. */
void fn_1_DA00(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;
    s32 alpha;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->vel.x = 2.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->vel.y = 5.0 + 2.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->vel.z = 2.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->color.r = 255;
                data->color.g = 255;
                data->color.b = 255;
                data->color.a = 128;
                data->scale = 30.0f;
            case 1:
                VECAdd(&data->vel, &data->pos, &data->pos);
                alpha = data->color.a;
                alpha -= 8;
                if (alpha < 0) {
                    alpha = 0;
                    data->scale = 0.0f;
                    data->time = -1;
                }
                data->color.a = alpha;
                break;
        }
    }
}

/* 66 insns. Particle model 1 (hook fn_1_DD18). */
void fn_1_DC10(OMOBJ *obj)
{
    ANIMDATA *anim;
    HU3DPARTICLEDATA *data;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x860021, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 256);
    obj->mdlId[1] = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_DD18);
    Hu3DModelLayerSet(mdlId, 5);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* 132 insns. Particle hook 1: yellow trail, fades by 4. */
void fn_1_DD18(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;
    s32 alpha;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->vel.x = 2.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->vel.y = 5.0 + 2.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->vel.z = 2.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->color.r = 224;
                data->color.g = 224;
                data->color.b = 128;
                data->color.a = 128;
                data->scale = 150.0f;
            case 1:
                VECAdd(&data->vel, &data->pos, &data->pos);
                alpha = data->color.a;
                alpha -= 4;
                if (alpha < 0) {
                    alpha = 0;
                    data->scale = 0.0f;
                    data->time = -1;
                }
                data->color.a = alpha;
                break;
        }
    }
}

/* 44 insns. Shadow hook model and its 7-slot list. */
void fn_1_DF28(OMOBJ *obj)
{
    M580_EFFECT *work = obj->data;
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M580_EFFECTLIST *list;

    work->unk000 = HuSprAnimRead(HuDataSelHeapReadNum(0x860023, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DHookFuncCreate(fn_1_E114);
    obj->mdlId[2] = mdlId;
    Hu3DModelLayerSet(mdlId, 1);
    model = &Hu3DData[mdlId];
    list = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_EFFECTLIST), HU_MEMNUM_OVL);
    model->hookData = list;
    memset(list, 0, sizeof(M580_EFFECTLIST));
}

/* 79 insns. Per frame: shadow alpha, and each shadow's 16-step frame from its rotation. */
void fn_1_DFD8(OMOBJ *obj)
{
    M580_EFFECT *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[2];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M580_EFFECTLIST *list = model->hookData;
    M580_EFFECTSHADOW *shadow;
    float rot;
    s32 frame;
    s32 i;

    rot = fn_1_1970();
    work->unk004 = rot;
    for (i = 0; i < 7; i++) {
        shadow = list->unk000[i];
        if (shadow != NULL) {
            rot = *shadow->unk014;
            rot = fmodf(11.25 + rot, 360.0);
            if (rot < 0.0f) {
                rot += 360.0;
            }
            frame = rot / 22.5;
            if (frame < 0) {
                frame = 0;
            }
            if (frame >= 15) {
                frame = 15;
            }
            shadow->unk01C = frame;
        }
    }
}

/* 150 insns. Shadow hook: indirect-warp TEV setup, then draw each registered shadow. */
void fn_1_E114(HU3DMODEL *model, Mtx *mtx)
{
    static const float lbl_1_rodata_618[2][3] = { { 0.02f, 0.0f, 0.0f }, { 0.0f, 0.02f, 0.0f } };
    static const GXVtxDescList lbl_1_rodata_630[] = {
        { GX_VA_POS, GX_DIRECT },
        { GX_VA_CLR0, GX_DIRECT },
        { GX_VA_TEX0, GX_DIRECT },
        { GX_VA_TEX1, GX_DIRECT },
        { GX_VA_NULL, GX_NONE },
    };
    static const GXVtxAttrFmtList lbl_1_rodata_658[] = {
        { GX_VA_POS, GX_POS_XYZ, GX_F32, 0 },
        { GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0 },
        { GX_VA_TEX0, GX_TEX_ST, GX_F32, 0 },
        { GX_VA_TEX1, GX_TEX_ST, GX_F32, 0 },
        { GX_VA_NULL, GX_POS_XY, GX_U8, 0 },
    };
    OMOBJ *obj = lbl_1_bss_248;
    M580_EFFECT *work = obj->data;
    M580_EFFECTLIST *list = model->hookData;
    M580_EFFECTSHADOW *shadow;
    s32 i;

    HuSprTexLoad(work->unk000, 0, GX_TEXMAP1, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumIndStages(1);
    GXSetIndTexMtx(GX_ITM_0, (float(*)[3])lbl_1_rodata_618, 0);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(2);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX1, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
    GXSetCullMode(GX_CULL_NONE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXClearVtxDesc();
    GXSetVtxDescv((GXVtxDescList *)lbl_1_rodata_630);
    GXSetVtxAttrFmtv(GX_VTXFMT0, (GXVtxAttrFmtList *)lbl_1_rodata_658);
    for (i = 0; i < 7; i++) {
        shadow = list->unk000[i];
        fn_1_E36C(shadow, mtx);
    }
    GXSetTevDirect(GX_TEVSTAGE0);
    GXSetNumIndStages(0);
}

/* 345 insns. Draw one shadow quad under its owner. */
void fn_1_E36C(M580_EFFECTSHADOW *shadow, Mtx *mtx)
{
    HuVecF pos;
    Mtx m;
    OMOBJ *obj;
    M580_EFFECT *work;
    float u0;
    float u1;
    float tp;
    s32 a0;
    s32 a1;

    if (shadow != NULL && shadow->unk01C != -1 && shadow->unk000 != 0) {
        pos.x = shadow->unk00C->x + shadow->unk010->x;
        pos.y = -shadow->unk00C->y + shadow->unk010->y;
        pos.z = shadow->unk00C->z + shadow->unk010->z;
        MTXScale(m, 205.0f, 205.0f, 80.0f);
        MTXTransApply(m, m, pos.x, pos.y, pos.z);
        MTXConcat(*mtx, m, m);
        GXLoadPosMtxImm(m, GX_PNMTX0);
        HuSprTexLoad(shadow->unk018, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
        u0 = shadow->unk01C / 16.0;
        u1 = (shadow->unk01C + 1) / 16.0;
        MTXScale(m, 0.5f, 0.5f, 1.0f);
        MTXTransApply(m, m, 0.0025f * pos.x, 0.0025f * pos.z, 0.0f);
        GXLoadTexMtxImm(m, GX_TEXMTX0, GX_MTX2x4);
        obj = lbl_1_bss_248;
        work = obj->data;
        tp = work->unk004;
        a0 = 96.0f * tp;
        a1 = 24.0f * tp;
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(-0.5f, 0.0f, 0.0f);
        GXColor4u8(0, 0, 0, a0);
        GXTexCoord2f32(u0, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        GXPosition3f32(0.5f, 0.0f, 0.0f);
        GXColor4u8(0, 0, 0, a0);
        GXTexCoord2f32(u1, 0.0f);
        GXTexCoord2f32(1.0f, 0.0f);
        GXPosition3f32(0.5f, -1.0f, 1.0f);
        GXColor4u8(0, 0, 0, a1);
        GXTexCoord2f32(u1, 1.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXPosition3f32(-0.5f, -1.0f, 1.0f);
        GXColor4u8(0, 0, 0, a1);
        GXTexCoord2f32(u0, 1.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        GXEnd();
    }
}

/* 58 insns. Banner sprite and its state. */
void fn_1_E8D0(OMOBJ *obj)
{
    M580_EFFECT *work = obj->data;
    M580_EFFECTBANNER *p = &work->unk008;
    ANIMDATA *anim;
    HUSPRGRPID grpId;
    s16 memberNo;

    p->unk000 = 0;
    p->unk004 = 0;
    p->unk008 = 0.0f;
    p->unk010 = 0.0f;
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x860024, HU_MEMNUM_OVL, HEAP_MODEL));
    grpId = HuSprGrpCreate(1);
    p->unk00C = grpId;
    HuSprGrpPosSet(grpId, 288.0f, 350.0f);
    memberNo = 0;
    HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 10, 0));
    HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
}

/* 133 insns. Per-frame banner fade and pulse. */
void fn_1_E9B8(OMOBJ *obj)
{
    M580_EFFECT *work = obj->data;
    M580_EFFECTBANNER *p = &work->unk008;
    HUSPRGRPID grpId = p->unk00C;
    s16 memberNo = 0;

    if (p->unk000 != 0) {
        if ((p->unk008 += 0.2) > 1.0) {
            p->unk008 = 1.0f;
        }
        HuSprTPLvlSet(grpId, memberNo, p->unk008);
        HuSprAttrReset(grpId, memberNo, HUSPR_ATTR_DISPOFF);
    } else if ((p->unk008 -= 0.2) <= 0.0) {
        p->unk008 = 0.0f;
        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprTPLvlSet(grpId, memberNo, p->unk008);
    }
    switch (p->unk004) {
        case 0:
            if (p->unk000 == 0) {
                break;
            }
            p->unk004++;
        case 1:
            if ((p->unk010 += 0.3) < 1.5) {
                break;
            }
            p->unk004++;
            break;
        case 2:
            if ((p->unk010 -= 0.1) > 1.0) {
                break;
            }
            p->unk004++;
            p->unk010 = 1.0f;
            break;
        case 3:
            if (p->unk000 == 0) {
                p->unk004 = 0;
            }
            break;
    }
    HuSprScaleSet(grpId, memberNo, p->unk010, p->unk010);
}

/* 42 insns. Emit one particle 0 at pos. */
void fn_1_EBCC(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_248;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DPARTICLE *particle = Hu3DData[mdlId].hookData;
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

/* 48 insns. Emit one particle 1 at pos (accel is stored, the hook ignores it). */
void fn_1_EC74(HuVecF *pos, HuVecF *accel)
{
    OMOBJ *obj = lbl_1_bss_248;
    HU3DMODELID mdlId = obj->mdlId[1];
    HU3DPARTICLE *particle = Hu3DData[mdlId].hookData;
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time < 0) {
            data->time = 0;
            data->pos = *pos;
            data->accel = *accel;
            break;
        }
    }
}

/* 49 insns. Register a shadow in the first free of 7 slots (never released). */
void fn_1_ED34(M580_EFFECTSHADOW *shadow)
{
    OMOBJ *obj = lbl_1_bss_248;
    HU3DMODELID mdlId = obj->mdlId[2];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M580_EFFECTLIST *list = model->hookData;
    M580_EFFECTSHADOW **slot = list->unk000;
    s32 i;

    for (i = 0; i < 7; i++, slot++) {
        if (*slot == NULL) {
            *slot = shadow;
            shadow->unk018 = HuSprAnimRead(HuDataSelHeapReadNum(lbl_1_data_7A0[shadow->unk004], HU_MEMNUM_OVL, HEAP_MODEL));
            shadow->unk01C = -1;
            break;
        }
    }
}

/* 15 insns. Banner on/off request. */
void fn_1_EDF8(s32 on)
{
    OMOBJ *obj = lbl_1_bss_248;
    M580_EFFECT *work = obj->data;
    M580_EFFECTBANNER *p = &work->unk008;

    p->unk000 = on;
}
