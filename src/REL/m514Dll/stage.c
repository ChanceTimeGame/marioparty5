/*
 * m514dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/stage.s.
 */

#include "REL/m514Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

#include "datadir_enum.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x238 */ /* double lbl_1_rodata_238 = 0.013; */
/* 0x240 */ /* double lbl_1_rodata_240 = 1; */
/* 0x248 */ /* float lbl_1_rodata_248 = 1.0f; */
/* 0x24C */ /* float lbl_1_rodata_24C = 2.0f; */
/* 0x250 */ /* float lbl_1_rodata_250 = 0.0f; */
/* 0x254 */ /* float lbl_1_rodata_254 = -15.0f; */
/* 0x258 */ /* float lbl_1_rodata_258 = -240.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = 15.0f; */
/* 0x260 */ /* float lbl_1_rodata_260[2] = { 230.0f, 0.0f }; */

/* --- .data --- */
/* 0x4A0 */ M514_FOGPARAM lbl_1_data_4A0[3] = {   /* [0] layers 0 and 4, [1] layer 3, [2] layer 2 */
    { 20.0f, 7700.0f, { 255, 255, 238, 0 } },
    { 20.0f, 15000.0f, { 255, 255, 238, 0 } },
    { 20.0f, 25000.0f, { 255, 255, 238, 0 } },
};
/* 0x4C4 */ HuVecF lbl_1_data_4C4 = { -4644.0f, -1228.0f, -4732.0f };  /* fn_1_8180 position */
/* 0x4D0 */ u32 lbl_1_data_4D0 = 0x42FF7A80;  /* fn_1_585C quad colour, RGBA8 as a word */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x214 */ float lbl_1_bss_214;  /* fog end scale, 2.0 falling to 1.0 */
/* 0x210 */ OMOBJ *lbl_1_bss_210;  /* the stage object; its data is M514_STAGE */

/* --- functions (reference order) --- */
/* stage.c fn_1_510C, 44 insns. Unit setup: the stage object, its fog and background. */
void fn_1_510C(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M514_STAGE *work;

    obj = omAddObjEx(objman, 20, 6, 0, -1, fn_1_51C0);
    lbl_1_bss_210 = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M514_STAGE));
    fn_1_5744(objman);
    obj->work[0] = 0;
}

/* stage.c fn_1_51BC, 1 insns. Unit close hook. */
void fn_1_51BC(void)
{
}

/* stage.c fn_1_51C0, 107 insns. Stage object init: five stage models, then the quad hook. */
void fn_1_51C0(OMOBJ *obj)
{
    M514_STAGE *work = obj->data;
    HU3DMODELID modelId;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m514, 0x00));
    obj->mdlId[0] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelShadowMapSet(modelId);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m514, 0x01));
    obj->mdlId[1] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(modelId, 4);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m514, 0x02));
    obj->mdlId[2] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelLayerSet(modelId, 3);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m514, 0x03));
    obj->mdlId[3] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(modelId, 2);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m514, 0x04));
    obj->mdlId[4] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(modelId, 1);
    Hu3DModelShadowMapSet(modelId);
    if (!_CheckFlag(FLAG_INST_DECA)) {
        fn_1_57F0(obj);
    }
    obj->objFunc = fn_1_536C;
}

/* stage.c fn_1_536C, 49 insns. Stage object main: fog clears, a fn_1_8180 effect every fourth frame. */
void fn_1_536C(OMOBJ *obj)
{
    if ((obj->work[0] & 3) == 0) {
        fn_1_8180(&lbl_1_data_4C4);
    }
    if ((lbl_1_bss_214 -= 0.013) < 1.0) {
        lbl_1_bss_214 = 1.0f;
    }
    if (!_CheckFlag(FLAG_INST_DECA)) {
        fn_1_5858(obj);
    }
    obj->work[0]++;
}

/* stage.c fn_1_5430, 43 insns. Fog for one lbl_1_data_4A0 entry; inlined into the four layer hooks below. */
void fn_1_5430(GXFogType type, s32 no)
{
    M514_FOGPARAM *fog = &lbl_1_data_4A0[no];
    float fov;
    float near;
    float far;

    Hu3DCameraPerspectiveGet(1, &fov, &near, &far);
    GXSetFog(type, fog->unk000, fog->unk004 * lbl_1_bss_214, near, far, fog->unk008);
}

/* stage.c fn_1_54DC, 38 insns. Layer 4 hook. */
void fn_1_54DC(s16 layerNo)
{
    fn_1_5430(GX_FOG_PERSP_LIN, 0);
}

/* stage.c fn_1_5574, 39 insns. Layer 3 hook. */
void fn_1_5574(s16 layerNo)
{
    fn_1_5430(GX_FOG_PERSP_LIN, 1);
}

/* stage.c fn_1_5610, 39 insns. Layer 2 hook. */
void fn_1_5610(s16 layerNo)
{
    fn_1_5430(GX_FOG_PERSP_LIN, 2);
}

/* stage.c fn_1_56AC, 38 insns. Layer 0 hook: fog off. */
void fn_1_56AC(s16 layerNo)
{
    fn_1_5430(GX_FOG_NONE, 0);
}

/* stage.c fn_1_5744, 43 insns. Background colour, fog and the layer hooks. */
void fn_1_5744(OMOBJMAN *objman)
{
    M514_FOGPARAM *fog = &lbl_1_data_4A0[0];

    lbl_1_bss_214 = 2.0f;
    Hu3DBGColorSet(fog->unk008.r, fog->unk008.g, fog->unk008.b);
    Hu3DFogSet(fog->unk000, fog->unk004, fog->unk008.r, fog->unk008.g, fog->unk008.b);
    Hu3DLayerHookSet(0, fn_1_56AC);
    Hu3DLayerHookSet(2, fn_1_5610);
    Hu3DLayerHookSet(3, fn_1_5574);
    Hu3DLayerHookSet(4, fn_1_54DC);
}

/* stage.c fn_1_57F0, 26 insns. The fn_1_585C quad, on layer 5 (not in a decathlon). */
void fn_1_57F0(OMOBJ *obj)
{
    M514_STAGE *work = obj->data;
    HU3DMODELID modelId;

    work->unk000 = fn_1_9794();
    modelId = Hu3DHookFuncCreate(fn_1_585C);
    obj->mdlId[5] = modelId;
    Hu3DModelLayerSet(modelId, 5);
}

/* stage.c fn_1_5858, 1 insns. */
void fn_1_5858(OMOBJ *obj)
{
}

/* stage.c fn_1_585C, 170 insns. Model hook: a flat quad at x = work->unk000. */
void fn_1_585C(HU3DMODEL *model, Mtx *mtx)
{
    OMOBJ *obj = lbl_1_bss_210;
    M514_STAGE *work = obj->data;
    Mtx m;

    PSMTXIdentity(m);
    PSMTXTrans(m, work->unk000, 0.0f, 0.0f);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(-15.0f, 1.0f, -240.0f);
    GXColor1u32(lbl_1_data_4D0);
    GXPosition3f32(15.0f, 1.0f, -240.0f);
    GXColor1u32(lbl_1_data_4D0);
    GXPosition3f32(15.0f, 1.0f, 230.0f);
    GXColor1u32(lbl_1_data_4D0);
    GXPosition3f32(-15.0f, 1.0f, 230.0f);
    GXColor1u32(lbl_1_data_4D0);
    GXEnd();
}
