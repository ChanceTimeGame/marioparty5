/*
 * m503dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/stage.s.
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

/* Random factors from frand(): signed in [-1, 1) and unsigned in [0, 1). */
#define M503_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M503_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x450 */ /* float lbl_1_rodata_450 = 0.0f; */
/* 0x454 */ /* float lbl_1_rodata_454 = 241.0f; */
/* 0x458 */ /* double lbl_1_rodata_458 = 0.5; */
/* 0x460 */ /* double lbl_1_rodata_460 = 3; */
/* 0x468 */ /* double lbl_1_rodata_468 = 57.295780181884766; */
/* 0x470 */ /* double lbl_1_rodata_470 = 90; */
/* 0x478 */ /* double lbl_1_rodata_478 = 0.0000152587890625; */
/* 0x480 */ /* double lbl_1_rodata_480 = 4503601774854144; */
/* 0x488 */ /* float lbl_1_rodata_488 = 400.0f; */
/* 0x490 */ /* double lbl_1_rodata_490 = -2010.0000000000002; */
/* 0x498 */ /* double lbl_1_rodata_498 = 3410; */
/* 0x4A0 */ /* float lbl_1_rodata_4A0 = -7800.0f; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 1131; */
/* 0x4B0 */ /* double lbl_1_rodata_4B0 = 4213; */
/* 0x4B8 */ /* double lbl_1_rodata_4B8 = 100; */
/* 0x4C0 */ /* double lbl_1_rodata_4C0 = 2; */
/* 0x4C8 */ /* double lbl_1_rodata_4C8 = -7990.000000000001; */
/* 0x4D0 */ /* float lbl_1_rodata_4D0 = 1630.0f; */
/* 0x4D8 */ /* double lbl_1_rodata_4D8 = -7500; */
/* 0x4E0 */ /* double lbl_1_rodata_4E0 = 50; */
/* 0x4E8 */ /* double lbl_1_rodata_4E8 = 0.000030517578125; */
/* 0x4F0 */ /* double lbl_1_rodata_4F0 = -3105; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = -7160.0f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = -4530.0f; */
/* 0x500 */ /* double lbl_1_rodata_500 = -7045; */
/* 0x508 */ /* float lbl_1_rodata_508 = -13800.0f; */
/* 0x50C */ /* float lbl_1_rodata_50C = -14000.0f; */
/* 0x510 */ /* double lbl_1_rodata_510 = 720000; */
/* 0x518 */ /* double lbl_1_rodata_518 = -585; */
/* 0x520 */ /* double lbl_1_rodata_520 = 30; */
/* 0x528 */ /* double lbl_1_rodata_528 = 1; */
/* 0x530 */ /* float lbl_1_rodata_530 = 1.0f; */
/* 0x538 */ /* double lbl_1_rodata_538 = 1.5707963267948966; */
/* 0x540 */ /* float lbl_1_rodata_540 = 200.0f; */
/* 0x548 */ /* double lbl_1_rodata_548 = -185; */
/* 0x550 */ /* double lbl_1_rodata_550 = 0.1; */
/* 0x558 */ /* double lbl_1_rodata_558 = 0.3; */
/* 0x560 */ /* float lbl_1_rodata_560 = 100.0f; */
/* 0x568 */ /* double lbl_1_rodata_568 = 0.02564102564102564; */
/* 0x570 */ /* double lbl_1_rodata_570 = 3.141592653589793; */
/* 0x578 */ /* double lbl_1_rodata_578 = 180; */
/* 0x580 */ /* float lbl_1_rodata_580 = 90.0f; */
/* 0x584 */ /* float lbl_1_rodata_584 = 359.0f; */
/* 0x588 */ /* double lbl_1_rodata_588 = 20; */
/* 0x590 */ /* float lbl_1_rodata_590 = 5.0f; */
/* 0x598 */ /* double lbl_1_rodata_598 = 4503599627370496; */

/* --- .data --- */
/* 0x520 */ M503_STAGECOL lbl_1_data_520[5] = {
    { { -470.0f, 0.0f, -425.0f }, 250.0f, 0 },
    { { 470.0f, 0.0f, -425.0f }, 250.0f, 0 },
    { { 470.0f, 0.0f, 500.0f }, 300.0f, 0 },
    { { -470.0f, 0.0f, 500.0f }, 300.0f, 0 },
    { { 0.0f, 0.0f, 0.0f }, 450.0f, 1 },
};
/* 0x584 */ HuVecF lbl_1_data_584[7] = {
    { 3047.0f, -13048.0f, -6562.0f },
    { 3277.0f, -13048.0f, -6402.0f },
    { 3578.0f, -13048.0f, -6650.0f },
    { 3748.0f, -13048.0f, -6505.0f },
    { 4066.0f, -13048.0f, -6593.0f },
    { 2849.0f, -13048.0f, -6445.0f },
    { 2660.0f, -13048.0f, -6633.0f },
};
/* 0x5D8 */ HuVecF lbl_1_data_5D8[7] = {
    { -3731.0f, -13048.0f, -6562.0f },
    { -3465.0f, -13048.0f, -6402.0f },
    { -3130.0f, -13048.0f, -6650.0f },
    { -2923.0f, -13048.0f, -6505.0f },
    { -2651.0f, -13048.0f, -6593.0f },
    { -3946.0f, -13048.0f, -6445.0f },
    { -4129.0f, -13048.0f, -6633.0f },
};
/* 0x62C */ s8 lbl_1_data_62C[16] = { 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 4, 0, 1, 0, 1 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xBC gap_05_000000BC_bss (0x4) -- dtk filler */
/* 0xB8 */ OMOBJ *lbl_1_bss_B8;

void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

/*
 * A grid cell's colour is stored as four bytes (fn_1_B888) and read back as one
 * word for GXColor1u32 (fn_1_BA9C). The word is RGBA only on a big-endian host,
 * so the host packs it numerically.
 */
#define M503_CELLCOLOR(cell) GXColor1u32(*(u32 *)&(cell)->unk00C)

/*
 * Retail converts grid coordinates with CodeWarrior's __cvt_fp2unsigned, which
 * saturates: negative and NaN give 0, >= 2^32 gives 0xFFFFFFFF. A plain host
 * float->u32 cast of a negative value is undefined, so the host reproduces the
 * saturation explicitly.
 */
#define M503_F2U(d) (d)

/* --- functions (reference order) --- */
/* fn_1_A6FC stage 36 insns. Stage object and its M503_STAGE work. */
void fn_1_A6FC(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M503_STAGE *work;

    obj = omAddObjEx(objman, 20, 11, 0, -1, fn_1_A790);
    lbl_1_bss_B8 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M503_STAGE));
    obj->work[0] = 0;
}

/* fn_1_A78C stage 1 insns */
void fn_1_A78C(void)
{
}

/* fn_1_A790 stage 102 insns. Stage models, the grid hook and five collision cylinders. */
void fn_1_A790(OMOBJ *obj)
{
    M503_STAGE *work;
    HU3DMODELID mdlId;
    M503_ACTORBOX *rec;
    M503_STAGECOL *col;
    s32 i;

    work = obj->data;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m503, 0));
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m503, 1));
    obj->mdlId[1] = mdlId;
    Hu3DModelLayerSet(mdlId, 5);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m503, 2));
    obj->mdlId[2] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    fn_1_AA0C(obj);
    mdlId = Hu3DHookFuncCreate(fn_1_BA9C);
    obj->mdlId[10] = mdlId;
    Hu3DModelLayerSet(mdlId, 1);
    fn_1_B9D0(mdlId);
    rec = work->unk000;
    col = lbl_1_data_520;
    for (i = 0; i < 5; i++, rec++, col++) {
        rec->unk000.unk000 = 1;
        rec->unk000.unk004 = 2;
        rec->unk000.unk008 = i;
        rec->unk000.unk00C = 0;
        rec->unk000.unk010 = obj;
        rec->unk000.unk014 = NULL;
        rec->unk000.unk018 = &col->unk000;
        rec->unk000.unk01C = col->unk00C;
        rec->unk020 = col->unk010;
        fn_1_DFA8(rec);
    }
    obj->objFunc = fn_1_A928;
}

/* fn_1_A928 stage 57 insns. Stage per-frame update. */
void fn_1_A928(OMOBJ *obj)
{
    HU3DMODELID mdlId;

    fn_1_AD34(obj);
    fn_1_AE8C(obj);
    fn_1_B888(obj);
    mdlId = obj->mdlId[0];
    if (Hu3DMotionEndCheck(mdlId)) {
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 241.0f, Hu3DMotionMaxTimeGet(mdlId));
    }
    mdlId = obj->mdlId[1];
    if (Hu3DMotionEndCheck(mdlId)) {
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 241.0f, Hu3DMotionMaxTimeGet(mdlId));
    }
    obj->work[0]++;
}

/* fn_1_AA0C stage 202 insns. Seven linked models, each aimed from lbl_1_data_584[i] to lbl_1_data_5D8[i]. */
void fn_1_AA0C(OMOBJ *obj)
{
    HuVecF dir;
    HuVecF rot;
    s32 i;
    HU3DMODELID baseId;
    HU3DMODELID mdlId;

    for (i = 0; i < 7; i++) {
        if (i == 0) {
            baseId = Hu3DModelCreateData(DATANUM(DATA_m503, 3));
            mdlId = baseId;
        } else {
            mdlId = Hu3DModelLink(baseId);
        }
        obj->mdlId[i + 3] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 2);
        dir.x = lbl_1_data_5D8[i].x - lbl_1_data_584[i].x;
        dir.y = lbl_1_data_5D8[i].y - lbl_1_data_584[i].y;
        dir.z = lbl_1_data_5D8[i].z - lbl_1_data_584[i].z;
        rot.x = 57.29578f * atan2(-dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
        rot.y = 90.0 + 57.29578f * atan2(dir.x, dir.z);
        rot.z = 0.0f;
        Hu3DModelRotSetV(mdlId, &rot);
        Hu3DMotionTimeSet(mdlId, M503_FRANDU() * Hu3DMotionMaxTimeGet(mdlId));
    }
}

/* fn_1_AD34 stage 86 insns. Slide the seven models from lbl_1_data_584 to lbl_1_data_5D8 over 400 frames, then hide them. */
void fn_1_AD34(OMOBJ *obj)
{
    HuVecF pos;
    s32 time;
    s32 i;
    HU3DMODELID mdlId;
    float t;
    HuVecF *from;
    HuVecF *to;

    time = obj->work[0];
    if (time > 400) {
    } else if (time == 400) {
        for (i = 0; i < 7; i++) {
            mdlId = obj->mdlId[i + 3];
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        }
    } else {
        t = time / 400.0f;
        from = lbl_1_data_584;
        to = lbl_1_data_5D8;
        for (i = 0; i < 7; i++, from++, to++) {
            mdlId = obj->mdlId[i + 3];
            pos.x = from->x + t * (to->x - from->x);
            pos.y = from->y + t * (to->y - from->y);
            pos.z = from->z + t * (to->z - from->z);
            Hu3DModelPosSetV(mdlId, &pos);
        }
    }
}

/* fn_1_AE8C stage 37 insns. Stage effect spawns, keyed by lbl_1_data_62C. */
void fn_1_AE8C(OMOBJ *obj)
{
    s32 i;

    if (obj->work[0] < 2) {
        for (i = 0; i < 16; i++) {
            fn_1_AF20(lbl_1_data_62C[i & 0xF], 0);
        }
    }
    fn_1_AF20(lbl_1_data_62C[obj->work[0] & 0xF], 1);
}

/* fn_1_AF20 stage 214 insns. One effect at a random point of spawn area `type`. */
void fn_1_AF20(s32 type, s32 mode)
{
    HuVecF pos;
    float t;

    switch (type) {
        case 0:
            pos.x = -2010.0000000000002 + 3410.0 * M503_FRANDU();
            pos.z = -7800.0f;
            break;
        case 1:
            t = 1131.0 * M503_FRANDU();
            pos.x = 4213.0 + t;
            if (0.0f != t) {
                t = 100.0 * (2.0 * (t / 1131.0));
            }
            pos.z = -7990.000000000001 + t;
            break;
        case 2:
            pos.x = 1630.0f;
            pos.z = -7500.0 + 50.0 * M503_FRANDS();
            break;
        case 3:
            pos.x = -3105.0 + 50.0 * M503_FRANDS();
            pos.z = -7160.0f;
            break;
        case 4:
            pos.x = -4530.0f;
            pos.z = -7045.0 + 50.0 * M503_FRANDS();
            break;
    }
    if (mode == 0) {
        pos.y = -13800.0f;
        fn_1_CEB0(&pos);
    } else {
        pos.y = -14000.0f;
        fn_1_CE1C(&pos);
    }
}

/* fn_1_B278 stage 388 insns. Fill the stage buffer's two height grids with cosine falloffs. */
void fn_1_B278(HU3DMODEL *modelP, float amp)
{
    M503_STAGEBUF *buf;
    M503_STAGECELL *cell;
    s32 j;
    s32 i;
    float dx;
    float dz;
    float t;
    float v;
    float maxDist;

    buf = modelP->hookData;
    maxDist = sqrtf(720000.0);
    for (i = 0; i < 40; i++) {
        for (j = 0; j < 40; j++) {
            cell = &buf->unk2B4[i][j];
            dx = -585.0 + 30.0 * j;
            dz = -585.0 + 30.0 * i;
            t = sqrtf(dx * dx + dz * dz) / maxDist;
            if (t > 1.0) {
                t = 1.0f;
            }
            v = amp * -cos(M_PI / 2 * t);
            cell->unk000 = cell->unk004 = v;
            cell->unk008 = 0.0f;
            *(u32 *)&cell->unk00C = -1;
        }
    }
    maxDist = 200.0f;
    for (i = 0; i < 13; i++) {
        for (j = 0; j < 13; j++) {
            dx = -185.0 + 30.0 * j;
            dz = -185.0 + 30.0 * i;
            t = sqrtf(dx * dx + dz * dz) / maxDist;
            if (t > 1.0) {
                t = 1.0f;
            }
            v = cos(M_PI / 2 * t);
            buf->unk010[i][j] = v;
        }
    }
}

/* fn_1_B888, stage.c, 82 insns. Eases every grid cell's height toward rest + dent, clears the dent, shades the cell by it. */
void fn_1_B888(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M503_STAGEBUF *buf;
    s32 j;
    s32 i;
    s32 v;
    M503_STAGECELL *cell;
    GXColor *color;
    float rest;
    float dent;

    mdlId = obj->mdlId[10];
    model = &Hu3DData[mdlId];
    buf = model->hookData;
    for (i = 0; i < 40; i++) {
        for (j = 0; j < 40; j++) {
            cell = &buf->unk2B4[i][j];
            color = &cell->unk00C;
            rest = cell->unk004;
            dent = cell->unk008;
            cell->unk000 += 0.1 * ((rest + dent) - cell->unk000);
            cell->unk008 = 0.0f;
            v = (s32)(dent / 0.3) + 255;
            if (v > 255) {
                v = 255;
            }
            if (v < 200) {
                v = 200;
            }
            color->r = v;
            color->g = v;
            color->b = v;
            color->a = 255;
        }
    }
}

/* fn_1_B9D0, stage.c, 51 insns. Allocates the grid buffer as the hook model's hookData. */
void fn_1_B9D0(HU3DMODELID mdlId)
{
    HU3DMODEL *model;
    M503_STAGEBUF *buf;

    model = &Hu3DData[mdlId];
    buf = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_STAGEBUF), HU_MEMNUM_OVL);
    model->hookData = buf;
    memset(buf, 0, sizeof(M503_STAGEBUF));
    buf->unk000 = HuSprAnimDataRead(DATANUM(DATA_m503, 0x26));
    buf->unk004 = 0.0f;
    buf->unk008 = 0.0f;
    buf->unk00C = 0.0f;
    fn_1_B278(model, 100.0f);
}

/* fn_1_BA9C, stage.c, 339 insns. Hook draw: the 39x39 quad grid. */
void fn_1_BA9C(HU3DMODEL *model, Mtx *mtx)
{
    M503_STAGEBUF *buf;
    s32 j;
    s32 i;
    M503_STAGECELL *cell;
    float x;
    float z;
    float u;
    float v;
    Mtx m;

    buf = model->hookData;
    HuSprTexLoad(buf->unk000, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    PSMTXIdentity(m);
    PSMTXTrans(m, buf->unk004, buf->unk008, buf->unk00C);
    PSMTXConcat(*mtx, m, m);
    GXLoadPosMtxImm(m, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LESS, GX_TRUE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_AND, GX_LEQUAL, 255);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ZERO, GX_LO_COPY);
    GXSetNumChans(1);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    for (i = 0; i < 39; i++) {
        for (j = 0; j < 39; j++) {
            x = -585.0 + 30.0 * j;
            z = -585.0 + 30.0 * i;
            u = 0.02564102564102564 * j;
            v = 0.02564102564102564 * i;
            GXBegin(GX_QUADS, GX_VTXFMT0, 4);
            cell = &buf->unk2B4[i][j];
            GXPosition3f32(x, cell->unk000, z);
            M503_CELLCOLOR(cell);
            GXTexCoord2f32(u, v);
            cell = &buf->unk2B4[i][j + 1];
            GXPosition3f32(x + 30.0, cell->unk000, z);
            M503_CELLCOLOR(cell);
            GXTexCoord2f32(u + 0.02564102564102564, v);
            cell = &buf->unk2B4[i + 1][j + 1];
            GXPosition3f32(x + 30.0, cell->unk000, z + 30.0);
            M503_CELLCOLOR(cell);
            GXTexCoord2f32(u + 0.02564102564102564, v + 0.02564102564102564);
            cell = &buf->unk2B4[i + 1][j];
            GXPosition3f32(x, cell->unk000, z + 30.0);
            M503_CELLCOLOR(cell);
            GXTexCoord2f32(u, v + 0.02564102564102564);
        }
    }
}

/* fn_1_BFE8, stage.c, 105 insns. Ground height at (x, z): centre plus four samples 50 units out, averaged, + 20. */
float fn_1_BFE8(float x, float z)
{
    float angle;
    float h;
    float dx;
    float dz;

    angle = 0.0f;
    h = 0.0f;
    h = fn_1_C18C(x, z);
    for (angle = 0.0f; angle < 359.0f; angle += 90.0f) {
        dx = 100.0 * (0.5 * sin(M_PI * angle / 180.0));
        dz = 100.0 * (0.5 * cos(M_PI * angle / 180.0));
        h += fn_1_C18C(x + dx, z + dz);
    }
    return 20.0 + h / 5.0f;
}

/* fn_1_C18C, stage.c, 166 insns. Grid height at (x, z), interpolated. */
float fn_1_C18C(float x, float z)
{
    OMOBJ *obj;
    HU3DMODELID mdlId;
    HU3DMODEL *model;
    M503_STAGEBUF *buf;
    u32 ix;
    u32 iz;
    float h00;
    float h01;
    float h10;
    float h11;

    obj = lbl_1_bss_B8;
    mdlId = obj->mdlId[10];
    model = &Hu3DData[mdlId];
    buf = model->hookData;
    x -= -585.0;
    ix = M503_F2U(x / 30.0);
    if (ix >= 39) {
        return 0.0f;
    }
    z -= -585.0;
    iz = M503_F2U(z / 30.0);
    if (iz >= 39) {
        return 0.0f;
    }
    x = (x - 30.0 * (float)ix) / 30.0;
    z = (z - 30.0 * (float)iz) / 30.0;
    h00 = buf->unk2B4[iz][ix].unk000;
    h01 = buf->unk2B4[iz][ix + 1].unk000;
    h10 = buf->unk2B4[iz + 1][ix].unk000;
    h11 = buf->unk2B4[iz + 1][ix + 1].unk000;
    h00 += x * ((h01 - h00) / 30.0);
    h10 += x * ((h11 - h10) / 30.0);
    return h00 + z * ((h10 - h00) / 30.0);
}

/* fn_1_C424, stage.c, 84 insns. Presses the 13x13 dent kernel into the grid around (x, z). */
void fn_1_C424(float x, float z, float depth)
{
    u32 j;
    u32 i;
    u32 ix;
    u32 iz;
    OMOBJ *obj;
    HU3DMODEL *model;
    M503_STAGEBUF *buf;
    M503_STAGECELL (*cells)[40];
    float (*kernel)[13];
    u32 cx;
    u32 cz;
    HU3DMODELID mdlId;
    float w;

    obj = lbl_1_bss_B8;
    mdlId = obj->mdlId[10];
    model = &Hu3DData[mdlId];
    buf = model->hookData;
    cells = buf->unk2B4;
    kernel = buf->unk010;
    ix = M503_F2U((x - -585.0) / 30.0);
    ix -= 6;
    iz = M503_F2U((z - -585.0) / 30.0);
    iz -= 6;
    for (i = 0; i < 13; i++) {
        cz = iz + i;
        if (cz >= 40) {
            continue;
        }
        for (j = 0; j < 13; j++) {
            cx = ix + j;
            if (cx >= 40) {
                continue;
            }
            w = kernel[i][j];
            cells[cz][cx].unk008 -= depth * w;
        }
    }
}

