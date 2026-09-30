/*
 * m516dll effect.c -- the overlay's own GX-immediate effect object. Functions
 * are in reference order. Reference assembly:
 * build/mp5-asm/m516Dll/asm/REL/m516Dll/effect.s.
 *
 * The object owns two Hu3D hook-func models:
 *   mdlId[0] -> fn_1_7164, 8 camera-facing textured quads (M516_EFFECT)
 *   mdlId[1] -> fn_1_75E8, 4 flat 32-gon rings  (M516_RINGWORK)
 */

#include "REL/m516Dll.h"

#include "game/data.h"
#include "game/memory.h"
#include "game/sprite.h"

#include "math.h"

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x44 gap_05_00000044_bss (0x4) -- dtk filler */
/* 0x40 */ OMOBJ *lbl_1_bss_40;

/* --- functions (reference order) --- */

/* fn_1_6F24 -- effect.c, 23 insns. ObjectSetup hook: create the effect object. */
void fn_1_6F24(OMOBJMAN *objman)
{
    lbl_1_bss_40 = omAddObjEx(objman, 0x32, 2, 0, -1, fn_1_6F84);
    fn_1_6F84(lbl_1_bss_40);
}

/* fn_1_6F80 -- effect.c, 1 insn. empty, unreferenced. */
void fn_1_6F80(void)
{
}

/* fn_1_6F84 -- effect.c, 17 insns. create both hook models, then run fn_1_6FC8 per frame. */
void fn_1_6F84(OMOBJ *obj)
{
    fn_1_6FF0(obj);
    fn_1_74B0(obj);
    obj->objFunc = fn_1_6FC8;
}

/* fn_1_6FC8 -- effect.c, 10 insns. per-frame object function. */
void fn_1_6FC8(OMOBJ *obj)
{
    fn_1_70AC(obj);
}

/* fn_1_6FF0 -- effect.c, 47 insns. quad-effect model and its work. */
void fn_1_6FF0(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M516_EFFECT *work;

    mdlId = Hu3DHookFuncCreate(fn_1_7164);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 0);
    model = &Hu3DData[mdlId];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_EFFECT), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M516_EFFECT));
    work->unk000 = HuSprAnimRead(HuDataSelHeapReadNum(0x4A0011, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* fn_1_70AC -- effect.c, 46 insns. per-frame quad update: grow, fade, expire. */
void fn_1_70AC(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M516_EFFECT *work = model->hookData;
    M516_EFFECTDATA *p;
    u8 *col;
    s32 a;
    s32 i;

    for (i = 0; i < 8; i++) {
        p = &work->unk004[i];
        if (p->unk00) {
            p->unk08 += 5.0;
            col = (u8 *)&p->unk04;
            a = col[3] - 4;
            col[3] = a;
            if (a <= 0) {
                p->unk00 = 0;
            }
        }
    }
}

/* fn_1_7164 -- effect.c, 211 insns. quad-effect draw hook. */
void fn_1_7164(HU3DMODEL *model, Mtx *cameraMtx)
{
    M516_EFFECT *work = model->hookData;
    M516_EFFECTDATA *p;
    Mtx m;
    s32 i;
    u32 col;
    float size;

    HuSprTexLoad(work->unk000, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 8; i++) {
        p = &work->unk004[i];
        if (p->unk00) {
            col = p->unk04;
            size = p->unk08;
            PSMTXIdentity(m);
            PSMTXTrans(m, p->unk0C.x, p->unk0C.y, p->unk0C.z);
            PSMTXConcat(*cameraMtx, m, m);
            GXLoadPosMtxImm(m, 0);
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(-size, 0.0f, -size);
            GXColor1u32(col);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(size, 0.0f, -size);
            GXColor1u32(col);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(size, 0.0f, size);
            GXColor1u32(col);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(-size, 0.0f, size);
            GXColor1u32(col);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
}

/* fn_1_74B0 -- effect.c, 78 insns. ring model, work and 32-step sin/cos table. */
void fn_1_74B0(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M516_RINGWORK *work;
    s32 i;
    float ang;

    mdlId = Hu3DHookFuncCreate(fn_1_75E8);
    obj->mdlId[1] = mdlId;
    Hu3DModelLayerSet(mdlId, 5);
    model = &Hu3DData[mdlId];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_RINGWORK), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M516_RINGWORK));
    for (i = 0, ang = 0.0f; i < 32; i++, ang += 11.0f) {
        work->unk010[i] = sin(M_PI * ang / 180.0);
        work->unk090[i] = cos(M_PI * ang / 180.0);
    }
}

/* fn_1_75E8 -- effect.c, 180 insns. ring draw hook. */
void fn_1_75E8(HU3DMODEL *model, Mtx *cameraMtx)
{
    M516_RINGWORK *work = model->hookData;
    float *sinTbl = work->unk010;
    float *cosTbl = work->unk090;
    M516_RING *p;
    Mtx m;
    float radius;
    float x;
    float z;
    float x0;
    float z0;
    s32 i;
    s32 j;

    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    for (i = 0; i < 4; i++) {
        p = work->unk000[i];
        if (p != NULL) {
            if (p->unk00) {
                radius = p->unk04;
                PSMTXIdentity(m);
                PSMTXTrans(m, p->unk08->x, p->unk08->y, p->unk08->z);
                PSMTXConcat(*cameraMtx, m, m);
                GXLoadPosMtxImm(m, 0);
                GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 34);
                GXPosition3f32(0.0f, 0.0f, 0.0f);
                GXColor1u32(0x80);
                for (j = 0; j < 32; j++) {
                    z = radius * cosTbl[j];
                    x = radius * sinTbl[j];
                    GXPosition3f32(x, 0.0f, z);
                    GXColor1u32(8);
                }
                z0 = cosTbl[0] * radius;
                x0 = sinTbl[0] * radius;
                GXPosition3f32(x0, 0.0f, z0);
                GXColor1u32(8);
            }
        }
    }
}

/* fn_1_78B8 -- effect.c, 45 insns. spawn one quad effect. */
void fn_1_78B8(HuVecF *pos, float size)
{
    OMOBJ *obj = lbl_1_bss_40;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M516_EFFECT *work = model->hookData;
    M516_EFFECTDATA *p;
    s32 i;

    for (i = 0; i < 8; i++) {
        p = &work->unk004[i];
        if (!p->unk00) {
            p->unk00 = 1;
            p->unk04 = -1;
            p->unk08 = size;
            p->unk0C = *pos;
            break;
        }
    }
}

/* fn_1_796C -- effect.c, 35 insns. register a ring. */
void fn_1_796C(M516_RING *ring)
{
    OMOBJ *obj = lbl_1_bss_40;
    HU3DMODELID mdlId = obj->mdlId[1];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M516_RINGWORK *work = model->hookData;
    M516_RING **slot = work->unk000;
    s32 i;

    for (i = 0; i < 4; i++, slot++) {
        if (*slot == NULL) {
            *slot = ring;
            break;
        }
    }
}
