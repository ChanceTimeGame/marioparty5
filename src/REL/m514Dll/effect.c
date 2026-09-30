/*
 * m514dll effect.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/effect.s.
 */

#include "REL/m514Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x268 */ /* float lbl_1_rodata_268 = 0.0f; */
/* 0x26C */ /* float lbl_1_rodata_26C = 5.0f; */
/* 0x270 */ /* float lbl_1_rodata_270 = 1.0f; */
/* 0x278 */ /* double lbl_1_rodata_278 = 0.01; */
/* 0x280 */ /* double lbl_1_rodata_280 = 0.5; */
/* 0x288 */ /* float lbl_1_rodata_288 = 24.0f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 270; */
/* 0x298 */ /* double lbl_1_rodata_298 = 0; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 180; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = 3.141592653589793; */
/* 0x2B0 */ /* float lbl_1_rodata_2B0 = 128.0f; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 4503601774854144; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 2; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = 5.625; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 255; */
/* 0x2D8 */ /* float lbl_1_rodata_2D8 = 22.0f; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 300; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = 100; */
/* 0x2F0 */ /* double lbl_1_rodata_2F0 = 0.000030517578125; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = 30; */
/* 0x300 */ /* double lbl_1_rodata_300 = 1; */
/* 0x308 */ /* double lbl_1_rodata_308 = 0.2; */
/* 0x310 */ /* double lbl_1_rodata_310 = 0.0000152587890625; */
/* 0x318 */ /* double lbl_1_rodata_318 = 0.8; */
/* 0x320 */ /* double lbl_1_rodata_320 = 80; */
/* 0x328 */ /* double lbl_1_rodata_328 = 360; */
/* 0x330 */ /* double lbl_1_rodata_330 = 0.95; */
/* 0x338 */ /* double lbl_1_rodata_338 = 0.03; */
/* 0x340 */ /* float lbl_1_rodata_340 = 288.0f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 410.0f; */
/* 0x348 */ /* double lbl_1_rodata_348 = 0.3; */
/* 0x350 */ /* double lbl_1_rodata_350 = 1.5; */
/* 0x358 */ /* double lbl_1_rodata_358 = 0.1; */
/* 0x360 */ /* double lbl_1_rodata_360 = 4000; */
/* 0x368 */ /* double lbl_1_rodata_368 = 0.9; */
/* 0x370 */ /* double lbl_1_rodata_370 = 120; */
/* 0x378 */ /* float lbl_1_rodata_378 = 4.0f; */
/* 0x37C */ /* float lbl_1_rodata_37C = 120.0f; */
/* 0x380 */ /* double lbl_1_rodata_380 = 60; */
/* 0x388 */ /* float lbl_1_rodata_388 = 180.0f; */
/* 0x390 */ /* double lbl_1_rodata_390 = 40; */
/* 0x398 */ /* double lbl_1_rodata_398 = 20; */
/* 0x3A0 */ /* double lbl_1_rodata_3A0 = 50; */
/* 0x3A8 */ /* double lbl_1_rodata_3A8 = 3; */

/* --- .data --- */
/* 0x4D8 */ u32 lbl_1_data_4D8[7] = { 0xFF000000, 0xFF800000, 0xFFFF0000, 0x00FF0000, 0x0080FF00, 0x0000FF00, 0x8000FF00 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x21C gap_05_0000021C_bss (0x4) -- dtk filler */
/* 0x218 */ OMOBJ *lbl_1_bss_218;

/* --- functions (reference order) --- */
/* 34 insns */
void fn_1_5B04(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M514_EFFECT *work;

    obj = omAddObjEx(objman, 60, 4, 0, -1, fn_1_5B90);
    lbl_1_bss_218 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_EFFECT), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M514_EFFECT));
}

/* fn_1_5B8C -- effect.c, 1 insn. empty. */
void fn_1_5B8C(void)
{
}

/* fn_1_5B90 -- effect.c, 23 insns. create the effect models, then run fn_1_5BEC per frame. */
void fn_1_5B90(OMOBJ *obj)
{
    fn_1_5C34(obj);
    fn_1_6588(obj);
    fn_1_6C44(obj);
    fn_1_76D0(obj);
    fn_1_7184(obj);
    obj->objFunc = fn_1_5BEC;
}

/* fn_1_5BEC -- effect.c, 18 insns. per-frame object function. */
void fn_1_5BEC(OMOBJ *obj)
{
    fn_1_5CD4(obj);
    fn_1_6644(obj);
    fn_1_6D7C(obj);
    fn_1_77BC(obj);
}

/* fn_1_5C34 -- effect.c, 40 insns. rainbow model and its work. */
void fn_1_5C34(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M514_EFFECT0WORK *work;

    mdlId = Hu3DHookFuncCreate(fn_1_5DE4);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 6);
    model = &Hu3DData[mdlId];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_EFFECT0WORK), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M514_EFFECT0WORK));
}

/* fn_1_5CD4 -- effect.c, 68 insns. per-frame rainbow update. */
void fn_1_5CD4(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT0WORK *work = model->hookData;
    M514_EFFECT0 *p = work->unk000;
    s32 i;

    for (i = 0; i < 3; i++, p++) {
        switch (p->unk000) {
            case 1:
                p->unk000++;
                p->unk018 = 0.0f;
                p->unk01C = p->unk020 = 5.0f;
                p->unk028 = 1.0f;
                break;
            case 0:
                break;
            case 2:
                break;
            case 3:
                if ((p->unk014 -= 0.01) > 0.0f) {
                    break;
                }
                p->unk000 = 0;
                break;
        }
    }
}

/* fn_1_5DE4 -- effect.c, 489 insns. rainbow draw hook: 24 segments x 6 bands. */
void fn_1_5DE4(HU3DMODEL *model, Mtx *cameraMtx)
{
    M514_EFFECT0WORK *work = model->hookData;
    M514_EFFECT0 *p = work->unk000;
    Mtx m;
    u32 colA[7];
    u32 colB[7];
    HuVecF mid;
    HuVecF dir;
    u8 *col;
    s32 i;
    s32 j;
    s32 k;
    s32 alphaA;
    s32 alphaB;
    u32 c0;
    u32 c1;
    u32 c2;
    u32 c3;
    float len;
    float width;
    float ang;
    float ang0;
    float ang1;
    float scale;
    float t;
    float s;
    float step;
    float r0;
    float r1;
    float x0;
    float y0;
    float x1;
    float y1;
    float x2;
    float y2;
    float x3;
    float y3;

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
    memcpy(colA, lbl_1_data_4D8, sizeof(colA));
    memcpy(colB, lbl_1_data_4D8, sizeof(colB));
    for (i = 0; i < 3; i++, p++) {
        if (p->unk000 < 2) {
            continue;
        }
        mid.x = p->unk02C.x + 0.5 * (p->unk038.x - p->unk02C.x);
        mid.y = 0.0f;
        mid.z = p->unk02C.z + 0.5 * (p->unk038.z - p->unk02C.z);
        scale = p->unk028;
        dir.x = p->unk038.x - mid.x;
        dir.y = p->unk038.y - mid.y;
        dir.z = p->unk038.z - mid.z;
        len = PSVECMag(&dir);
        width = p->unk00C;
        step = p->unk01C / 24.0f;
        PSMTXIdentity(m);
        PSMTXTrans(m, mid.x, mid.y, mid.z);
        PSMTXConcat(*cameraMtx, m, m);
        GXLoadPosMtxImm(m, 0);
        for (k = 0, ang = 0.0f; k < 24; k++, ang += step) {
            ang0 = 270.0 + (ang + p->unk018);
            ang1 = ang0 + step;
            if (0.0 != p->unk01C) {
                t = 180.0 * (ang / p->unk01C);
            } else {
                t = 0.0f;
            }
            s = sin(M_PI * t / 180.0);
            alphaA = 128.0f * s * p->unk014;
            s = sin(M_PI * (t + step) / 180.0);
            alphaB = 128.0f * s * p->unk014;
            for (j = 0; j < 7; j++) {
                col = (u8 *)&colA[j];
                col[3] = alphaA;
                col = (u8 *)&colB[j];
                col[3] = alphaB;
            }
            GXBegin(GX_QUADS, GX_VTXFMT0, 24);
            for (j = 0; j < 6; j++) {
                r0 = len - width * j;
                if (r0 < 0.0f) {
                    r0 = 0.0f;
                }
                r1 = r0 - width;
                if (r1 < 0.0f) {
                    r1 = 0.0f;
                }
                y0 = scale * (r0 * cos(M_PI * ang0 / 180.0));
                x0 = r0 * sin(M_PI * ang0 / 180.0);
                GXPosition3f32(x0, y0, 0.0f);
                GXColor1u32(colA[j]);
                y1 = scale * (r0 * cos(M_PI * ang1 / 180.0));
                x1 = r0 * sin(M_PI * ang1 / 180.0);
                GXPosition3f32(x1, y1, 0.0f);
                GXColor1u32(colB[j]);
                y2 = scale * (r1 * cos(M_PI * ang1 / 180.0));
                x2 = r1 * sin(M_PI * ang1 / 180.0);
                GXPosition3f32(x2, y2, 0.0f);
                GXColor1u32(colB[j + 1]);
                y3 = scale * (r1 * cos(M_PI * ang0 / 180.0));
                x3 = r1 * sin(M_PI * ang0 / 180.0);
                GXPosition3f32(x3, y3, 0.0f);
                GXColor1u32(colA[j + 1]);
            }
        }
    }
}

/* fn_1_6588 -- effect.c, 47 insns. particle model and its work. */
void fn_1_6588(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M514_EFFECT1 *work;

    mdlId = Hu3DHookFuncCreate(fn_1_68EC);
    obj->mdlId[1] = mdlId;
    Hu3DModelLayerSet(mdlId, 6);
    model = &Hu3DData[mdlId];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_EFFECT1), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M514_EFFECT1));
    work->unk000 = HuSprAnimRead(HuDataSelHeapReadNum(0x480020, HU_MEMNUM_OVL, HEAP_MODEL));
}

/* fn_1_6644 -- effect.c, 170 insns. per-frame particle update: shrink, fall, cycle colour, fade. */
void fn_1_6644(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[1];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT1 *work = model->hookData;
    M514_EFFECT1DATA *p;
    s32 i;
    u8 *col;
    s32 a;
    s32 t;
    float ang;

    for (i = 0; i < 256; i++) {
        p = &work->unk004[i];
        if (p->unk000) {
            p->unk014 -= 0.5;
            p->unk018.y += 2.0;
            col = (u8 *)&p->unk010;
            a = col[3] - 6;
            col[3] = a;
            t = p->unk004++ & 0x1F;
            ang = 5.625 * (float)t;
            col[0] = 255.0 * sin(M_PI * ang / 180.0);
            t = p->unk008++ & 0x1F;
            ang = 5.625 * (float)t;
            col[1] = 255.0 * sin(M_PI * ang / 180.0);
            t = p->unk00C++ & 0x1F;
            ang = 5.625 * (float)t;
            col[2] = 255.0 * sin(M_PI * ang / 180.0);
            if (p->unk014 <= 0.0f || a <= 0) {
                p->unk000 = 0;
            }
        }
    }
}

/* fn_1_68EC -- effect.c, 214 insns. particle draw hook: one textured quad each. */
void fn_1_68EC(HU3DMODEL *model, Mtx *cameraMtx)
{
    M514_EFFECT1 *work = model->hookData;
    M514_EFFECT1DATA *p;
    s32 i;
    u32 col;
    float size;
    float x;
    float y;

    HuSprTexLoad(work->unk000, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_OR);
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
    GXLoadPosMtxImm(*cameraMtx, 0);
    for (i = 0; i < 256; i++) {
        p = &work->unk004[i];
        if (p->unk000) {
            col = p->unk010;
            size = p->unk014;
            x = p->unk018.x;
            y = p->unk018.y;
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            GXPosition3f32(x - size, y - size, 0.0f);
            GXColor1u32(col);
            GXTexCoord2f32(0.0f, 0.0f);
            GXPosition3f32(x + size, y - size, 0.0f);
            GXColor1u32(col);
            GXTexCoord2f32(1.0f, 0.0f);
            GXPosition3f32(x + size, y + size, 0.0f);
            GXColor1u32(col);
            GXTexCoord2f32(1.0f, 1.0f);
            GXPosition3f32(x - size, y + size, 0.0f);
            GXColor1u32(col);
            GXTexCoord2f32(0.0f, 1.0f);
        }
    }
}

/* fn_1_6C44 -- effect.c, 78 insns. wave model, work and 16-step sin/cos table. */
void fn_1_6C44(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M514_EFFECT2 *work;
    s32 i;
    float ang;

    mdlId = Hu3DHookFuncCreate(fn_1_6ED4);
    obj->mdlId[2] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    model = &Hu3DData[mdlId];
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_EFFECT2), HU_MEMNUM_OVL);
    model->hookData = work;
    memset(work, 0, sizeof(M514_EFFECT2));
    for (i = 0, ang = 0.0f; i < 16; i++, ang += 22.0f) {
        work->unk3800[i] = sin(M_PI * ang / 180.0);
        work->unk3840[i] = cos(M_PI * ang / 180.0);
    }
}

/* fn_1_6D7C -- effect.c, 86 insns. per-frame ring update: fade in, hold, fade out. */
void fn_1_6D7C(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[2];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT2 *work = model->hookData;
    M514_EFFECT2DATA *p = work->unk000;
    u8 *col;
    s32 i;

    for (i = 0; i < 512; i++, p++) {
        switch (p->unk000) {
            case 0:
                break;
            case 1:
                p->unk000++;
                p->unk00C = 0;
            case 2:
                col = (u8 *)&p->unk00C;
                if ((col[3] += 4) < 0x30) {
                    break;
                }
                p->unk000++;
                p->unk004 = 0;
                col[3] = 0x30;
            case 3:
                if (++p->unk004 < 300.0) {
                    break;
                }
                p->unk000++;
            case 4:
                col = (u8 *)&p->unk00C;
                if ((col[3] -= 1) > 4) {
                    break;
                }
                p->unk000 = 0;
                break;
        }
    }
}

/* fn_1_6ED4 -- effect.c, 172 insns. ring draw hook. */
void fn_1_6ED4(HU3DMODEL *model, Mtx *cameraMtx)
{
    M514_EFFECT2 *work = model->hookData;
    M514_EFFECT2DATA *p = work->unk000;
    float *sinTbl = work->unk3800;
    float *cosTbl = work->unk3840;
    Mtx m;
    float radius;
    float x;
    float z;
    float x0;
    float z0;
    s32 i;
    s32 j;
    u32 col;

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
    for (i = 0; i < 512; i++, p++) {
        if (p->unk000 >= 2) {
            radius = p->unk008;
            col = p->unk00C;
            PSMTXIdentity(m);
            PSMTXTrans(m, p->unk010.x, p->unk010.y, p->unk010.z);
            PSMTXConcat(*cameraMtx, m, m);
            GXLoadPosMtxImm(m, 0);
            GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, 18);
            GXPosition3f32(0.0f, 0.0f, 0.0f);
            GXColor1u32(col);
            for (j = 0; j < 16; j++) {
                z = radius * cosTbl[j];
                x = radius * sinTbl[j];
                GXPosition3f32(x, 0.0f, z);
                GXColor1u32(col);
            }
            z0 = cosTbl[0] * radius;
            x0 = sinTbl[0] * radius;
            GXPosition3f32(x0, 0.0f, z0);
            GXColor1u32(col);
        }
    }
}

/* fn_1_7184 -- effect.c, 66 insns. particle model (hook fn_1_728C). */
void fn_1_7184(OMOBJ *obj)
{
    ANIMDATA *anim;
    HU3DPARTICLEDATA *data;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    s32 i;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x480021, HU_MEMNUM_OVL, HEAP_MODEL));
    mdlId = Hu3DParticleCreate(anim, 128);
    obj->mdlId[3] = mdlId;
    particle = Hu3DData[mdlId].hookData;
    Hu3DParticleBlendModeSet(mdlId, 0);
    Hu3DParticleHookSet(mdlId, fn_1_728C);
    Hu3DModelLayerSet(mdlId, 5);
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        data->time = -1;
        data->scale = 0.0f;
    }
}

/* fn_1_728C -- effect.c, 273 insns. particle hook. */
void fn_1_728C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data = particle->data;
    s32 i;

    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->pos.x += 100.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->pos.y += 30.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->pos.z += 100.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->accel.x = 2.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->accel.y = 1.0 + 0.2 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->accel.z = 0.8 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
                data->scale = 80.0 + 30.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->zRot = 360.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                data->color.a = 200;
            case 1:
                data->scale += 5.0f;
                data->color.a -= 2;
                if (data->color.a > 240) {
                    data->time = -1;
                    data->scale = 0.0f;
                } else {
                    data->pos.x += data->accel.x;
                    data->pos.y += data->accel.y;
                    data->pos.z += data->accel.z;
                    data->accel.x *= 0.95;
                    data->accel.y -= 0.03;
                    data->accel.z *= 0.95;
                }
                break;
        }
    }
}

/* fn_1_76D0 -- effect.c, 59 insns. banner sprite and its state. */
void fn_1_76D0(OMOBJ *obj)
{
    M514_EFFECT *work = obj->data;
    M514_EFFECT *p = work;
    ANIMDATA *anim;
    HUSPRGRPID grpId;
    s16 memberNo;

    p->unk000 = 0;
    p->unk008 = 0.0f;
    p->unk010 = 0.0f;
    p->unk014 = p->unk016 = -1;
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x48001F, HU_MEMNUM_OVL, HEAP_MODEL));
    grpId = HuSprGrpCreate(1);
    p->unk00C = grpId;
    HuSprGrpPosSet(grpId, 288.0f, 410.0f);
    memberNo = 0;
    HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 10, 0));
    HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
}

/* fn_1_77BC -- effect.c, 143 insns. per-frame banner update. */
void fn_1_77BC(OMOBJ *obj)
{
    M514_EFFECT *work = obj->data;
    M514_EFFECT *p = work;
    HUSPRGRPID grpId = p->unk00C;
    s16 memberNo = 0;

    if (p->unk014 >= 0) {
        if ((p->unk008 += 0.2) > 1.0) {
            p->unk008 = 1.0f;
        }
        HuSprTPLvlSet(grpId, memberNo, p->unk008);
        HuSprAttrReset(grpId, memberNo, HUSPR_ATTR_DISPOFF);
        if (p->unk016 != p->unk014) {
            p->unk000 = 1;
            p->unk010 = 0.0f;
        }
    } else if ((p->unk008 -= 0.2) <= 0.0) {
        p->unk008 = 0.0f;
        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprTPLvlSet(grpId, memberNo, p->unk008);
    }
    switch (p->unk000) {
        case 0:
            break;
        case 1:
            if ((p->unk010 += 0.3) < 1.5) {
                break;
            }
            p->unk000++;
            break;
        case 2:
            if ((p->unk010 -= 0.1) > 1.0) {
                break;
            }
            p->unk000 = 0;
            p->unk010 = 1.0f;
            break;
    }
    HuSprScaleSet(grpId, memberNo, p->unk010, p->unk010);
    if (p->unk014 != p->unk016) {
        if (p->unk014 >= 0) {
            HuSprBankSet(grpId, memberNo, p->unk014);
        }
        p->unk016 = p->unk014;
    }
}

/* fn_1_79F8 -- effect.c, 71 insns. claim a trail slot; returns its index or -1. */
s32 fn_1_79F8(HuVecF *pos, float size)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT0 *work = model->hookData;
    M514_EFFECT0 *p = work;
    s32 i;

    for (i = 0; i < 3; i++, p++) {
        if (p->unk000 == 0) {
            p->unk000++;
            p->unk008 = 1;
            p->unk02C = *pos;
            p->unk038 = *pos;
            p->unk00C = p->unk010 = size;
            p->unk014 = 1.0f;
            p->unk01C = p->unk020 = 5.0f;
            p->unk024 = 0.0f;
            p->unk028 = 1.0f;
            return i;
        }
    }
    return -1;
}

/* fn_1_7B14 -- effect.c, 30 insns. release a trail slot (unreferenced). */
void fn_1_7B14(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT0 *work = model->hookData;
    M514_EFFECT0 *p;

    if (idx >= 0 && idx < 3) {
        p = &work[idx];
        p->unk000 = 0;
    }
}

/* fn_1_7B8C -- effect.c, 33 insns. end a live trail slot. */
void fn_1_7B8C(s32 idx)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT0 *work = model->hookData;
    M514_EFFECT0 *p;

    if (idx >= 0 && idx < 3) {
        p = &work[idx];
        if (p->unk000 != 0) {
            p->unk000 = 3;
        }
    }
}

/* fn_1_7C10 -- effect.c, 171 insns. follow a trail slot to pos. */
void fn_1_7C10(s32 idx, HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT0 *work = model->hookData;
    M514_EFFECT0 *p;
    s32 flag = 0;

    if (idx >= 0 && idx < 3) {
        p = &work[idx];
        if (pos->y < p->unk038.y) {
            flag = 1;
        }
        if (p->unk024 < pos->y) {
            p->unk024 = pos->y;
        }
        p->unk038.x += 0.1 * (pos->x - p->unk038.x);
        p->unk038.y += 0.1 * (pos->y - p->unk038.y);
        p->unk038.z = pos->z;
        p->unk028 = 1.0 - (p->unk038.x - p->unk02C.x) / 4000.0;
        p->unk00C = p->unk010 * (0.9 * (1.0 + (1.0 - p->unk028)));
        if (p->unk020 < 120.0 && !flag) {
            if ((p->unk020 += 4.0f) > 120.0) {
                p->unk020 = 120.0f;
            }
        } else if (0.0 != p->unk024) {
            p->unk020 = 120.0 + 60.0 * ((p->unk024 - pos->y) / p->unk024);
        }
        p->unk01C += 0.2 * (p->unk020 - p->unk01C);
        if (p->unk01C > 180.0) {
            p->unk01C = 180.0f;
        }
        if (--p->unk008 <= 0) {
            p->unk008 = 2;
            fn_1_7EBC(pos);
        }
    }
}

/* fn_1_7EBC -- effect.c, 129 insns. spawn one sparkle near pos. */
void fn_1_7EBC(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[1];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT1 *work = model->hookData;
    M514_EFFECT1DATA *p;
    s32 i;

    for (i = 0; i < 256; i++) {
        p = &work->unk004[i];
        if (p->unk000 == 0) {
            p->unk000 = 1;
            p->unk004 = frand();
            p->unk008 = frand();
            p->unk00C = frand();
            p->unk010 = -1;
            p->unk014 = 40.0 + 20.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
            p->unk018.x = pos->x + 30.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768)) - 50.0;
            p->unk018.y = pos->y + 50.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
            p->unk018.z = pos->z - 100.0;
            break;
        }
    }
}

/* fn_1_80C0 -- effect.c, 48 insns. spawn one ring at pos. */
void fn_1_80C0(HuVecF *pos, float size)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[2];
    HU3DMODEL *model = &Hu3DData[mdlId];
    M514_EFFECT2 *work = model->hookData;
    M514_EFFECT2DATA *p = work->unk000;
    s32 i;

    for (i = 0; i < 512; i++, p++) {
        if (p->unk000 == 0) {
            p->unk000++;
            p->unk010.x = pos->x;
            p->unk010.y = pos->y + 3.0;
            p->unk010.z = pos->z;
            p->unk008 = size;
            break;
        }
    }
}

/* fn_1_8180 -- effect.c, 42 insns. emit one particle at pos. */
void fn_1_8180(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_218;
    HU3DMODELID mdlId = obj->mdlId[3];
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

/* fn_1_8228 -- effect.c, 16 insns. request a banner bank (<0 hides). */
void fn_1_8228(s32 bank)
{
    OMOBJ *obj = lbl_1_bss_218;
    M514_EFFECT *work = obj->data;
    M514_EFFECT *p = work;

    p->unk014 = (s16)bank;
}

