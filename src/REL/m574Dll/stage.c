/*
 * m574Dll stage.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/stage.s.
 */

#include "REL/m574Dll.h"

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
/* 0xD8 */ /* double lbl_1_rodata_D8 = 150; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 300.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 80.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 240.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 120.0f; */
/* 0xF0 */ /* double lbl_1_rodata_F0 = 10; */
/* 0xF8 */ /* double lbl_1_rodata_F8 = 0.000030517578125; */
/* 0x100 */ /* double lbl_1_rodata_100 = 100; */
/* 0x108 */ /* double lbl_1_rodata_108 = 0.2; */
/* 0x110 */ /* double lbl_1_rodata_110 = 3.141592653589793; */
/* 0x118 */ /* double lbl_1_rodata_118 = 180; */
/* 0x120 */ /* double lbl_1_rodata_120 = 4503601774854144; */
/* 0x128 */ /* float lbl_1_rodata_128 = 0.0f; */
/* 0x130 */ /* double lbl_1_rodata_130 = 0.5; */
/* 0x138 */ /* double lbl_1_rodata_138 = 60; */
/* 0x140 */ /* double lbl_1_rodata_140 = 30; */
/* 0x148 */ /* double lbl_1_rodata_148 = 1; */
/* 0x150 */ /* double lbl_1_rodata_150 = 0.3; */
/* 0x158 */ /* double lbl_1_rodata_158 = 0.1; */
/* 0x160 */ /* float lbl_1_rodata_160 = 1.0f; */
/* 0x168 */ /* double lbl_1_rodata_168 = 0.01666666753590107; */
/* 0x170 */ /* double lbl_1_rodata_170 = 50; */
/* 0x178 */ /* float lbl_1_rodata_178 = 60.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 0.2f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 50.0f; */
/* 0x188 */ /* double lbl_1_rodata_188 = 20; */
/* 0x190 */ /* double lbl_1_rodata_190 = 3; */
/* 0x198 */ /* double lbl_1_rodata_198 = 19; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = 333.33334f; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 22; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 0.0000152587890625; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 18.0f; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 4; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = 0.4; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 54; */
/* 0x1D8 */ /* double lbl_1_rodata_1D8 = 360; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 360.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 0.1f; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 9; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 8.333334f; */
/* 0x1F8 */ /* double lbl_1_rodata_1F8 = 1.666666753590107; */
/* 0x200 */ /* double lbl_1_rodata_200 = -0.5; */
/* 0x208 */ /* float lbl_1_rodata_208 = 0.5f; */
/* 0x210 */ /* double lbl_1_rodata_210 = 300; */
/* 0x218 */ /* float lbl_1_rodata_218 = 40.0f; */
/* 0x220 */ /* double lbl_1_rodata_220 = -1; */
/* 0x228 */ /* float lbl_1_rodata_228 = 12.0f; */
/* 0x22C */ /* float lbl_1_rodata_22C = 270.0f; */
/* 0x230 */ /* float lbl_1_rodata_230 = 90.0f; */
/* 0x234 */ /* float lbl_1_rodata_234 = -1.0f; */
/* 0x238 */ /* float lbl_1_rodata_238 = 30.0f; */
/* 0x23C */ /* float lbl_1_rodata_23C = 0.4f; */
/* 0x240 */ /* float lbl_1_rodata_240 = 13.333334f; */
/* 0x244 */ /* float lbl_1_rodata_244 = 0.05f; */
/* 0x248 */ /* double lbl_1_rodata_248 = 0.05; */
/* 0x250 */ /* float lbl_1_rodata_250 = 200.0f; */
/* 0x254 */ /* float lbl_1_rodata_254 = 5.0f; */
/* 0x258 */ /* double lbl_1_rodata_258 = 0; */
/* 0x260 */ /* double lbl_1_rodata_260 = 5; */
/* 0x268 */ /* double lbl_1_rodata_268 = 0.125; */
/* 0x270 */ /* float lbl_1_rodata_270[2] = { 10.0f, 0.0f }; */

/* --- .data --- */
/* 0x220 */ s32 lbl_1_data_220[4] = { 0x0081000C, 0x0081000D, 0x00810011, 0x00810012 };
/* 0x230 */ s32 lbl_1_data_230[4] = { 0x00810018, 0x00810019, 0x00810018, 0x00810019 };
/* 0x240 */ s32 lbl_1_data_240[4] = { 0x0081000F, 0x00810010, 0x00810014, 0x00810015 };
/* 0x250 */ HuVecF lbl_1_data_250[4] = { { -875.0f, 1e+02f, -4e+01f }, { -445.0f, 1e+02f, -4e+01f }, { 445.0f, 1e+02f, -4e+01f }, { 875.0f, 1e+02f, -4e+01f } };
/* 0x280 */ float lbl_1_data_280[4] = { 60.0f, 300.0f, 60.0f, 300.0f };
/* 0x290 */ char lbl_1_data_290[4][10] = { "furihan", "furihan", "furihan", "furihan" };
/* 0x2B8 */ s32 lbl_1_data_2B8[3] = { 0x00000000, 0x00000001, 0x00000002 };
/* 0x2C4 */ u8 lbl_1_data_2C4[20] = { 0x00, 0x01, 0x00, 0x00, 0x01, 0x01, 0x02, 0x00, 0x01, 0x02, 0x02, 0x01, 0x00, 0x02, 0x01, 0x01, 0x00, 0x02, 0x00, 0x02 };
/* 0x2D8 */ char lbl_1_data_2D8[6][10] = { "slot_L3", "slot_L2", "Slot", "slot_R3", "slot_R2", "slot_R1" };
/* 0x314 */ s32 lbl_1_data_314[2] = { 0x0081000E, 0x00810013 };
/* 0x31C */ char lbl_1_data_31C[14][10] = { "block", "blockL2", "blockL3", "blockL4", "blockL5", "blockLLD", "blockLLU", "blockR5", "blockR4", "blockR3", "blockR2", "blockR1", "blockRRD", "blockRRU" };
/* 0x3A8 */ char lbl_1_data_3A8[4][10] = { "b_ataLL", "b_ataL", "b_ataR", "b_ataRR" };
/* 0x3D0 */ char lbl_1_data_3D0[9][10] = { "kuppa", "10L", "50L", "100L", "10R", "50R", "100R", "baneL", "baneR" };
/* 0x42C */ s32 lbl_1_data_42C[9] = { 0x00810005, 0x00810008, 0x00810009, 0x0081000A, 0x00810008, 0x00810009, 0x0081000A, 0x0081000B, 0x0081000B };
/* 0x450 */ s32 lbl_1_data_450[6] = { 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001 };
/* 0x468 */ s32 lbl_1_data_468[6] = { 0x00000003, 0x00000004, 0x00000005, 0x00000003, 0x00000004, 0x00000005 };
/* 0x480 */ s32 lbl_1_data_480[3] = { 0x0081001B, 0x0081001C, 0x0081001D };
/* 0x48C */ HuVecF lbl_1_data_48C[2] = { { -6.5e+02f, 9.6e+02f, 0.0f }, { 6.5e+02f, 9.6e+02f, 0.0f } };
/* 0x4A4 */ char lbl_1_data_4A4[] = "kuppabomb";
/* 0x4B0 */ HuVecF lbl_1_data_4B0[2] = { { -95.0f, 1215.0f, 1e+03f }, { 95.0f, 1215.0f, 1e+03f } };
/* 0x4C8 */ HuVecF lbl_1_data_4C8[2] = { { 3.0f, 3.0f, -1.0f }, { -3.0f, 3.0f, -1.0f } };
/* 0x4E0 */ /* jumptable_1_data_4E0: fn_1_4EE8 switch; 0x504.. are defined below that function */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x48 */ OMOBJ *lbl_1_bss_48; /* stage object; data is M574_STAGE. dtk sizes this 0x8 */

/* --- functions (reference order) --- */
#define M574_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M574_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

/* asm 9-50, 40 insns. Stage object and its 0x108C work. */
void fn_1_2028(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M574_STAGE *work;

    obj = omAddObjEx(objman, 20, 33, 3, -1, fn_1_20CC);
    lbl_1_bss_48 = obj;
    obj->stat |= 0x100;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M574_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M574_STAGE));
    obj->work[0] = 0;
}

/* asm 53-55, 1 insn. Empty. */
void fn_1_20C8(void)
{
}

/* asm 58-225, 166 insns. Stage models and the parts' setup. */
void fn_1_20CC(OMOBJ *obj)
{
    HU3DMODELID mdlId;
    M574_STAGE *work;
    M574_COLLOBJ *col;

    work = obj->data;
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 0));
    obj->mdlId[0] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DModelShadowMapSet(mdlId);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 1));
    obj->mdlId[1] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 3);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 2));
    obj->mdlId[2] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 7);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 3));
    obj->mdlId[3] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 7);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 6));
    obj->mdlId[4] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 4));
    obj->mdlId[5] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 3);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m574, 22));
    obj->mdlId[6] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    col = &work->unkF60;
    col->unk00 = 1;
    col->unk04 = 5;
    col->unk08 = 0;
    col->unk0C = 1;
    col->unk10 = obj;
    col->unk14 = NULL;
    col->unk18 = NULL;
    fn_1_8F54(col, mdlId);
    fn_1_8FDC(col);
    fn_1_8B48(col);
    fn_1_2928(obj);
    fn_1_2F8C(obj);
    fn_1_3374(obj);
    fn_1_383C(obj);
    fn_1_448C(obj);
    fn_1_4D28(obj);
    fn_1_5750(obj);
    fn_1_5E5C(obj);
    fn_1_6168(obj);
    Hu3DZClearLayerSet(5);
    obj->objFunc = fn_1_2364;
}

/* asm 228-262, 33 insns. Stage object main. */
void fn_1_2364(OMOBJ *obj)
{
    fn_1_2B88(obj);
    fn_1_3154(obj);
    fn_1_34B0(obj);
    fn_1_3A1C(obj);
    fn_1_4660(obj);
    fn_1_4EE8(obj);
    fn_1_5934(obj);
    fn_1_5ECC(obj);
    fn_1_629C(obj);
    fn_1_26F4(obj);
    obj->work[0]++;
}

/* asm 265-303, 36 insns. Put a model on a named object of the stage model. */
void fn_1_23E8(OMOBJ *obj, s16 mdlId, s32 idx)
{
    M574_STAGE *work = obj->data;
    HU3DMODELID stageMdl = obj->mdlId[4];
    HSFOBJECT *object;

    object = Hu3DModelObjPtrGet(stageMdl, lbl_1_data_3D0[idx]);
    if (object != NULL) {
        Hu3DModelPosSet(mdlId, object->mesh.base.pos.x, object->mesh.base.pos.y, object->mesh.base.pos.z);
    }
}

/* asm 306-347, 39 insns. Position of a named object of the stage model. */
void fn_1_2478(OMOBJ *obj, HuVecF *pos, s32 idx)
{
    M574_STAGE *work = obj->data;
    HU3DMODELID stageMdl = obj->mdlId[4];
    HSFOBJECT *object;

    object = Hu3DModelObjPtrGet(stageMdl, lbl_1_data_3D0[idx]);
    if (object != NULL) {
        pos->x = object->mesh.base.pos.x;
        pos->y = object->mesh.base.pos.y;
        pos->z = object->mesh.base.pos.z;
    }
}

/* asm 350-475, 120 insns. Launch num balls from Bowser toward one side. */
void fn_1_2514(OMOBJ *obj, s32 side, s32 num)
{
    M574_STAGE *work;
    M574_STAGEOBJ *rec;
    s32 i;
    float angle;
    HuVecF pos;
    HuVecF vel;

    work = obj->data;
    rec = &work->unk014;
    pos.x = rec->unk010.x;
    pos.y = rec->unk010.y - 150.0;
    pos.z = 300.0f;
    vel.z = 80.0f;
    for (i = 0; i < num; i++) {
        if (side == 0) {
            angle = 240.0f;
        } else {
            angle = 120.0f;
        }
        angle += 10.0 * M574_FRANDS();
        vel.x = 100.0 * (0.2 * HuSin(angle));
        vel.y = 100.0 * (0.2 * HuCos(angle));
        fn_1_6C2C(&pos, &vel);
    }
}

/* asm 478-629, 141 insns. Resupply a side that has run out of balls. */
void fn_1_26F4(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 i;

    work = obj->data;
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN && fn_1_918() > 1) {
        for (i = 0; i < 2; i++) {
            if (fn_1_6CC8(i)) {
                work->unk000[i] = 120;
            } else if (--work->unk000[i] < 0) {
                fn_1_2514(obj, i, 1);
                work->unk000[i] = 120;
            }
        }
    }
}

/* asm 632-788, 152 insns. Paddles: models and mesh collision. */
void fn_1_2928(OMOBJ *obj)
{
    M574_STAGE *work;
    HSFOBJECT *object;
    HU3DMODELID mdlId;
    M574_COLLOBJ *col;
    s32 i;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        mdlId = Hu3DModelCreateData(lbl_1_data_220[i]);
        obj->mdlId[i + 9] = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelShadowSet(mdlId);
        Hu3DModelPosSetV(mdlId, &lbl_1_data_250[i]);
        work->unk0A8[i].unk008 = work->unk0A8[i].unk00C = lbl_1_data_280[i];
        mdlId = Hu3DModelCreateData(lbl_1_data_240[i]);
        obj->mdlId[i + 17] = mdlId;
        Hu3DModelLayerSet(mdlId, 6);
        Hu3DModelShadowSet(mdlId);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(mdlId, 0.0f);
        mdlId = Hu3DModelCreateData(lbl_1_data_230[i]);
        obj->mdlId[i + 13] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        object = Hu3DModelObjPtrGet(mdlId, lbl_1_data_290[i]);
        if (object != NULL) {
            object->mesh.base.pos.x = lbl_1_data_250[i].x;
            object->mesh.base.pos.y = lbl_1_data_250[i].y;
            object->mesh.base.pos.z = lbl_1_data_250[i].z;
        }
        col = &work->unk0A8[i].unk014;
        col->unk00 = 1;
        col->unk04 = 6;
        col->unk08 = i;
        col->unk0C = 1;
        col->unk10 = obj;
        col->unk14 = NULL;
        col->unk18 = fn_1_2D88;
        fn_1_8F54(col, mdlId);
        fn_1_8FDC(col);
        fn_1_8FDC(col);
        fn_1_8B48(col);
    }
}

/* asm 791-926, 128 insns. Paddles: swing toward the target angle. */
void fn_1_2B88(OMOBJ *obj)
{
    M574_STAGE *work;
    HSFOBJECT *object;
    HU3DMODELID mdlId;
    s32 i;
    M574_PADDLE *paddle;
    float rate;

    work = obj->data;
    for (i = 0; i < 4; i++) {
        paddle = &work->unk0A8[i];
        paddle->unk008 += 0.5 * (paddle->unk00C - paddle->unk008);
        paddle->unk004 = paddle->unk00C - paddle->unk008;
        if (i & 1) {
            paddle->unk004 = -paddle->unk004;
        }
        if (paddle->unk004 < 0.0f) {
            paddle->unk004 = 0.0f;
        }
        paddle->unk004 = paddle->unk004 / 60.0;
        mdlId = obj->mdlId[i + 9];
        Hu3DModelRotSet(mdlId, 0.0f, 0.0f, paddle->unk008);
        mdlId = obj->mdlId[i + 17];
        rate = fn_1_6568(i);
        Hu3DMotionTimeSet(mdlId, 30.0 * (1.0 - rate));
        if (paddle->unk010 == 0 && MgSeqModeGet() == MGSEQ_MODE_FINISH) {
            paddle->unk010 = 1;
            Hu3DModelLayerSet(mdlId, 3);
            mdlId = obj->mdlId[2];
            Hu3DModelLayerSet(mdlId, 3);
        }
        mdlId = obj->mdlId[i + 13];
        object = Hu3DModelObjPtrGet(mdlId, lbl_1_data_290[i]);
        if (object != NULL) {
            object->mesh.base.rot.z = paddle->unk008;
        }
        fn_1_8FDC(&paddle->unk014);
    }
}

/* asm 929-1063, 129 insns. Paddle hit: a swinging paddle bats the ball. */
s32 fn_1_2D88(M574_COLLOBJ *col, M574_COLLACTOR *ball)
{
    M574_STAGE *work;
    M574_PADDLE *paddle;
    s32 i;
    float power;

    work = lbl_1_bss_48->data;
    i = col->unk08;
    paddle = &work->unk0A8[i];
    if (col->unk038->unk18.y > 0.3 && paddle->unk004 >= 0.1) {
        power = 100.0 * ((ball->unk18->x - lbl_1_data_250[i].x) / 2.0);
        if (i & 1) {
            power = -power;
        }
        if (power > 0.1) {
            if (power > 1.0) {
                power = 1.0f;
            }
            ball->unk1C->x = ball->unk1C->x - (1.0f / 60.0f) * (100.0 * (50.0 * col->unk038->unk18.x)) * power;
            ball->unk1C->y -= (1.0f / 60.0f) * (100.0 * (50.0 * col->unk038->unk18.y)) * power;
            if (i & 1) {
                power = -power;
            }
            ball->unk1C->x = ball->unk1C->x + 100.0 * (0.1 * power);
        }
    }
    return 0;
}

/* asm 1066-1185, 114 insns. Bumpers: models and sphere collision. */
void fn_1_2F8C(OMOBJ *obj)
{
    M574_STAGE *work;
    HU3DMODELID mdlId;
    M574_STAGEOBJ *rec;
    M574_COLLOBJ *col;
    s32 i;

    work = obj->data;
    for (i = 0; i < 6; i++) {
        rec = &work->unkB20[i];
        mdlId = Hu3DModelCreateData(lbl_1_data_42C[i + 1]);
        obj->mdlId[i + 21] = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
        fn_1_23E8(obj, mdlId, i + 1);
        fn_1_2478(obj, &rec->unk010, i + 1);
        col = &rec->unk04C;
        col->unk00 = 1;
        col->unk04 = 3;
        col->unk08 = i;
        col->unk0C = 0;
        col->unk10 = obj;
        col->unk14 = NULL;
        col->unk18 = fn_1_3240;
        col->unk01C.pos = &rec->unk010;
        col->unk020.radius = 80.0f;
        fn_1_8B48(col);
    }
}

/* asm 1188-1251, 59 insns. Bumpers: idle loop and recoil. */
void fn_1_3154(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 i;
    M574_STAGEOBJ *rec;
    HU3DMODELID mdlId;
    HuVecF pos;

    work = obj->data;
    for (i = 0; i < 6; i++) {
        rec = &work->unkB20[i];
        mdlId = obj->mdlId[i + 21];
        if (Hu3DMotionEndCheck(mdlId)) {
            Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
            Hu3DMotionTimeSet(mdlId, 0.0f);
        }
        VECScale(&rec->unk01C, &rec->unk01C, 0.2f);
        VECAdd(&rec->unk010, &rec->unk01C, &pos);
        Hu3DModelPosSetV(mdlId, &pos);
    }
}

/* asm 1254-1334, 77 insns. Bumper hit: score, recoil and a sound. */
s32 fn_1_3240(M574_COLLOBJ *col, M574_COLLACTOR *ball)
{
    M574_STAGE *work;
    M574_STAGEOBJ *rec;
    s32 i;
    OMOBJ *obj;
    HU3DMODELID mdlId;

    i = col->unk08;
    obj = lbl_1_bss_48;
    work = obj->data;
    rec = &work->unkB20[i];
    mdlId = obj->mdlId[i + 21];
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DMotionStartEndSet(mdlId, 60.0f, Hu3DMotionMaxTimeGet(mdlId));
    Hu3DMotionTimeSet(mdlId, 60.0f);
    VECNormalize(ball->unk1C, &rec->unk01C);
    VECScale(&rec->unk01C, &rec->unk01C, 50.0f);
    fn_1_77D4(lbl_1_data_450[i], lbl_1_data_468[i]);
    if (ball->unk18->x < 0.0f) {
        fn_1_C10(0x918, ball->unk18);
    } else {
        fn_1_C10(0x919, ball->unk18);
    }
    return 0;
}

/* asm 1337-1420, 79 insns. Launchers: models. */
void fn_1_3374(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 i;
    M574_STAGEOBJ *rec;
    HU3DMODELID mdlId;

    work = obj->data;
    for (i = 0; i < 2; i++) {
        rec = &work->unk2A0[i];
        rec->unk000 = 0;
        mdlId = Hu3DModelCreateData(lbl_1_data_42C[i + 7]);
        obj->mdlId[i + 27] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_SHAPE_PAUSE);
        Hu3DMotionTimeSet(mdlId, 0.0f);
        Hu3DMotionShapeTimeSet(mdlId, 0.0f);
        Hu3DModelLayerSet(mdlId, 4);
        fn_1_23E8(obj, mdlId, i + 7);
    }
}

/* asm 1423-1584, 149 insns. Launchers: hold, compress and fire the ball. */
void fn_1_34B0(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 i;
    HU3DMODELID mdlId;
    M574_COLLACTOR *ball;
    M574_STAGEOBJ *rec;

    work = obj->data;
    for (i = 0; i < 2; i++) {
        rec = &work->unk2A0[i];
        mdlId = obj->mdlId[i + 27];
        ball = rec->unk048;
        switch (rec->unk000) {
            case 0:
                break;
            case 1:
                rec->unk000++;
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_SHAPE_PAUSE);
                Hu3DMotionTimeSet(mdlId, 0.0f);
                Hu3DMotionShapeTimeSet(mdlId, 0.0f);
                if (i == 0) {
                    HuAudFXPlay(0x927);
                } else {
                    HuAudFXPlay(0x928);
                }
            case 2:
                rec->unk034 -= 20.0;
                if (Hu3DMotionTimeGet(mdlId) < 3.0) {
                    break;
                }
                rec->unk000++;
                rec->unk034 = 0.0f;
            case 3:
                if (Hu3DMotionTimeGet(mdlId) < 19.0) {
                    break;
                }
                rec->unk000++;
                ball->unk1C->x = 0.0f;
                ball->unk1C->y = 333.33334f;
                ball->unk00 &= ~2;
                ball = NULL;
                rec->unk048 = ball;
                if (i == 0) {
                    HuAudFXPlay(0x929);
                } else {
                    HuAudFXPlay(0x92A);
                }
            case 4:
                if (Hu3DMotionTimeGet(mdlId) < 22.0) {
                    break;
                }
                rec->unk000 = 0;
                break;
        }
        if (ball != NULL) {
            ball->unk1C->x = 0.0f;
            ball->unk1C->y = 0.0f;
            ball->unk18->x = rec->unk010.x;
            ball->unk18->y = rec->unk010.y + rec->unk034;
        }
    }
}

/* asm 1587-1670, 78 insns. Launcher catch (unreferenced hit callback). */
s32 fn_1_3704(M574_COLLOBJ *col, M574_COLLACTOR *ball)
{
    M574_STAGE *work;
    OMOBJ *obj;
    M574_STAGEOBJ *rec;
    M574_COLLSEG *edge;

    if ((ball->unk00 & 2) == 0) {
        obj = lbl_1_bss_48;
        work = obj->data;
        /* fork T: the side as an inline ternary (no local) is what fn_1_47DC's inlined copy needs */
        rec = &work->unk2A0[col->unk08 == 0 ? 0 : 1];
        if (rec->unk000 == 0) {
            rec->unk000++;
            rec->unk048 = ball;
            ball->unk00 |= 2;
            ball->unk1C->x = 0.0f;
            ball->unk1C->y = 0.0f;
            edge = col->unk038;
            rec->unk010.x = edge->unk00.x + 0.5 * (edge->unk0C.x - edge->unk00.x);
            rec->unk010.y = edge->unk00.y + 0.5 * (edge->unk0C.y - edge->unk00.y);
            rec->unk034 = 80.0f;
            return 1;
        }
    }
    return 0;
}

/* asm 1673-1798, 120 insns. Slot machines: reels and models. */
void fn_1_383C(OMOBJ *obj)
{
    s32 symbol;
    HSFOBJECT *object;
    M574_STAGE *work;
    HU3DMODELID stageMdl;
    HU3DMODELID mdlId;
    s32 i;
    s32 j;
    M574_SLOT *slot;

    work = obj->data;
    stageMdl = obj->mdlId[5];
    for (i = 0; i < 2; i++) {
        slot = &work->unk1E8[i];
        slot->unk00C = -1;
        for (j = 0; j < 3; j++) {
            object = Hu3DModelObjPtrGet(stageMdl, lbl_1_data_2D8[j + i * 3]);
            slot->unk050[j] = object;
            symbol = 20.0 * M574_FRANDU();
            slot->unk020[j] = symbol;
            slot->unk02C[j] = slot->unk038[j] = 18.0f * symbol;
        }
        mdlId = Hu3DModelCreateData(lbl_1_data_314[i]);
        obj->mdlId[i + 29] = mdlId;
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
        Hu3DMotionTimeSet(mdlId, 0.0f);
    }
}

/* asm 1801-2426, 581 insns. Slot machines: spin, stop, pay out. */
void fn_1_3A1C(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 time;
    HSFOBJECT *object;
    s32 match;
    s32 flag;
    s32 i;
    HU3DMODELID mdlId;
    s32 idx;
    s32 j;
    M574_SLOT *slot;
    float angle;
    HU3DMODELID stageMdl;

    work = obj->data;
    stageMdl = obj->mdlId[5];
    for (i = 0; i < 2; i++) {
        slot = &work->unk1E8[i];
        mdlId = obj->mdlId[i + 29];
        switch (slot->unk000) {
            case 0:
                break;
            case 1:
                slot->unk000++;
                slot->unk004 = 0;
                slot->unk010 = 1;
                for (j = 0; j < 3; j++) {
                    slot->unk044[j] = 4.0 + M574_FRANDU();
                    slot->unk014[j] = 0;
                }
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
                Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
                Hu3DMotionTimeSet(mdlId, 0.0f);
                if (i == 0) {
                    slot->unk00C = HuAudFXPlay(0x91F);
                } else {
                    slot->unk00C = HuAudFXPlay(0x920);
                }
                break;
            case 2:
                for (j = 0; j < 3; j++) {
                    if (slot->unk014[j] == 0) {
                        if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
                            time = 60.0 * (3.0 + 0.4 * j);
                        } else {
                            time = 60.0 * (1.0 + 0.4 * j);
                        }
                        if (slot->unk004 > time) {
                            slot->unk014[j] = 1;
                            angle = slot->unk038[j];
                            idx = angle / 18.0f;
                            slot->unk038[j] = 18.0f * idx;
                            switch (j) {
                                case 0:
                                    flag = 0;
                                    break;
                                case 1:
                                    flag = (M574_FRANDU() < 0.5) ? 1 : 0;
                                    break;
                                case 2:
                                    flag = (M574_FRANDU() < 0.5) ? 1 : 0;
                                    break;
                            }
                            if (j != 0 && flag != 0) {
                                match = fn_1_4330(slot->unk038[0]);
                                while (1) {
                                    if (idx >= 20) {
                                        idx = 0;
                                    }
                                    if (lbl_1_data_2C4[idx] == match) {
                                        slot->unk038[j] = 18.0f * idx;
                                        break;
                                    }
                                    idx++;
                                }
                            }
                            if (j == 2) {
                                slot->unk000++;
                                slot->unk004 = 0;
                                if (fn_1_918() <= 1) {
                                    match = fn_1_4330(slot->unk038[0]);
                                    while (1) {
                                        if (idx >= 20) {
                                            idx = 0;
                                        }
                                        if (lbl_1_data_2C4[idx] != match) {
                                            slot->unk038[j] = 18.0f * idx;
                                            break;
                                        }
                                        idx++;
                                    }
                                }
                                break;
                            }
                        } else if (slot->unk004 > 60.0 * (0.2 * j)) {
                            slot->unk038[j] += slot->unk044[j];
                        }
                    }
                }
                slot->unk004++;
                break;
            case 3:
                if (++slot->unk004 < 54.0) {
                    break;
                }
                slot->unk000++;
                slot->unk010 = 0;
                if (i == 0) {
                    HuAudFXStop(slot->unk00C);
                } else {
                    HuAudFXStop(slot->unk00C);
                }
                idx = slot->unk020[0];
                if (idx == slot->unk020[1] && idx == slot->unk020[2]) {
                    fn_1_7874(i, lbl_1_data_2B8[idx]);
                    if (i == 0) {
                        HuAudFXPlay(0x921);
                    } else {
                        HuAudFXPlay(0x922);
                    }
                    slot->unk008 = 60;
                    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionStartEndSet(mdlId, 60.0f, Hu3DMotionMaxTimeGet(mdlId));
                    Hu3DMotionTimeSet(mdlId, 60.0f);
                } else {
                    slot->unk008 = 30;
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
                    Hu3DMotionTimeSet(mdlId, 0.0f);
                }
                break;
            case 4:
                if (--slot->unk008 <= 0) {
                    slot->unk000 = 0;
                    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
                    Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
                    Hu3DMotionTimeSet(mdlId, 0.0f);
                }
                break;
        }
        for (j = 0; j < 3; j++) {
            angle = fmodf(slot->unk038[j], 360.0f);
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            slot->unk038[j] = angle;
            angle = fn_1_CC8(slot->unk02C[j], slot->unk038[j], 0.1f);
            slot->unk02C[j] = angle;
            slot->unk020[j] = fn_1_4330(angle);
            object = slot->unk050[j];
            if (object != NULL) {
                object->mesh.base.rot.x = slot->unk02C[j];
            }
        }
    }
}

/* asm 2429-2480, 46 insns. Reel symbol under an angle. */
s32 fn_1_4330(float angle)
{
    s32 idx;

    angle += 9.0;
    if (angle >= 360.0f) {
        angle -= 360.0f;
    }
    if (angle < 0.0f) {
        angle += 360.0f;
    }
    idx = angle / 18.0f;
    if (idx < 0) {
        idx = 19;
    }
    if (idx >= 20) {
        idx = 0;
    }
    return lbl_1_data_2C4[idx];
}

/* 29 insns */
void fn_1_43E8(OMOBJ *obj, s32 idx)
{
    M574_STAGE *work = obj->data;
    M574_SLOT *slot = &work->unk1E8[idx];

    if (MgSeqModeGet() == 5 && slot->unk000 == 0) {
        slot->unk000++;
    }
}

/* 12 insns */
s32 fn_1_445C(OMOBJ *obj, s32 idx)
{
    M574_STAGE *work = obj->data;
    M574_SLOT *slot = &work->unk1E8[idx];

    return slot->unk010;
}

/* 117 insns */
void fn_1_448C(OMOBJ *obj)
{
    M574_STAGE *work;
    HU3DMODELID mdlId;
    s32 i;
    HSFOBJECT *hsfObj;
    M574_COLLOBJ *col;
    M574_STAGEOBJ *blk;
    s32 n;
    s32 j;

    work = obj->data;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x810017, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[7] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_3A8[i]);
        if (hsfObj != NULL) {
            col = &work->unkF9C[i];
            col->unk00 = 1;
            col->unk04 = 4;
            col->unk08 = i;
            col->unk0C = 1;
            col->unk10 = obj;
            col->unk14 = NULL;
            col->unk18 = fn_1_47DC;
            fn_1_8FA8(col, hsfObj);
            fn_1_8FDC(col);
            fn_1_8B48(col);
        }
    }
    mdlId = obj->mdlId[5];
    n = 0;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 7; i++) {
            blk = &work->unk3B0[n];
            hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_31C[n]);
            blk->unk048 = hsfObj;
            if (hsfObj != NULL) {
                blk->unk010.x = hsfObj->mesh.base.pos.x;
                blk->unk010.y = hsfObj->mesh.base.pos.y;
                blk->unk010.z = 0.0f;
            }
            blk->unk000 = 0;
            blk->unk034 = 0.0f;
            blk->unk03C = blk->unk040 = blk->unk044 = 0.0f;
            blk->unk01C.x = blk->unk01C.y = blk->unk01C.z = 0.0f;
            n++;
        }
    }
}

/* 95 insns */
void fn_1_4660(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 n;
    s32 j;
    s32 i;
    M574_STAGEOBJ *blk;
    HSFOBJECT *hsfObj;

    work = obj->data;
    n = 0;
    for (j = 0; j < 2; j++) {
        for (i = 0; i < 7; i++) {
            blk = &work->unk3B0[n];
            hsfObj = blk->unk048;
            if (hsfObj != NULL) {
                switch (blk->unk000) {
                    case 0:
                        break;
                    case 1:
                        blk->unk01C.y = 8.333334f;
                        blk->unk000++;
                        break;
                    case 2:
                        blk->unk034 += blk->unk01C.y;
                        blk->unk01C.y -= (1.0f / 60.0f) * 100.0;
                        if (blk->unk034 > 0.0f) {
                            break;
                        }
                        blk->unk034 = 0.0f;
                        blk->unk000 = 0;
                        break;
                }
                if (i < 5) {
                    blk->unk040 = blk->unk034;
                }
                else if (j == 0) {
                    blk->unk03C = -blk->unk034;
                }
                else {
                    blk->unk03C = blk->unk034;
                }
                hsfObj->mesh.base.pos.x = blk->unk010.x + blk->unk03C;
                hsfObj->mesh.base.pos.y = blk->unk010.y + blk->unk040;
                blk->unk004++;
                n++;
            }
        }
    }
}

/* fn_1_47DC inlines MSL's sqrtf algorithm with 0.5/3.0 pooled as ordinary literals
 * (0x130/0x190), not math.h's _half/_three statics (m504 player.c precedent). */
static inline float StageSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* 339 insns */
s32 fn_1_47DC(M574_COLLOBJ *self, M574_COLLACTOR *ball)
{
    M574_STAGE *work;
    M574_STAGEOBJ *blk;
    s32 idx;
    s32 slot;
    s32 team;
    float dx;
    float dy;

    work = lbl_1_bss_48->data;
    idx = self->unk08;
    slot = -1;
    team = idx < 2 ? 0 : 1;
    if (idx >= 1 && idx <= 2) {
        if (!(self->unk038->unk18.y > -0.5)) {
            dx = self->unk038->unk00.x - ball->unk18->x;
            slot = dx / 100.0;
            if (slot < 0) {
                slot = 0;
            }
            if (slot > 4) {
                slot = 4;
            }
            fn_1_77D4(team, 10);
            if (ball->unk18->x < 0.0f) {
                fn_1_C10(0x916, ball->unk18);
            }
            else {
                fn_1_C10(0x917, ball->unk18);
            }
        }
    }
    else {
        if (self->unk038->unk18.y > 0.5) {
            dx = (self->unk038->unk00.x + self->unk038->unk0C.x) / 2.0f - ball->unk18->x;
            dy = (self->unk038->unk00.y + self->unk038->unk0C.y) / 2.0f - ball->unk18->y;
            if (StageSqrtF(dx * dx + dy * dy) < 300.0 && fn_1_3704(self, ball)) {
                return 1;
            }
        }
        if ((idx != 0 || !(self->unk038->unk18.x < 0.5)) && (idx != 3 || !(self->unk038->unk18.x > -0.5))) {
            dx = self->unk038->unk00.y;
            if (dx > self->unk038->unk0C.y) {
                dx = self->unk038->unk0C.y;
            }
            dx = ball->unk18->y - dx;
            slot = dx / 100.0;
            if (slot < 0) {
                slot = 0;
            }
            if (slot >= 2) {
                slot = -1;
            }
            else {
                slot += 5;
                fn_1_77D4(team, 11);
                if (ball->unk18->x < 0.0f) {
                    fn_1_C10(0x916, ball->unk18);
                }
                else {
                    fn_1_C10(0x917, ball->unk18);
                }
            }
        }
    }
    if (slot >= 0) {
        blk = &work->unk3B0[slot + team * 7];
        if (blk->unk000 == 0) {
            blk->unk000++;
            if (slot < 5) {
                fn_1_5680(&blk->unk010);
            }
        }
    }
    return 0;
}

/* 112 insns */
void fn_1_4D28(OMOBJ *obj)
{
    M574_STAGE *work = obj->data;
    s32 i;
    M574_STAGEOBJ *p;
    HU3DMODELID mdlId;
    s32 j;
    HU3DMOTID motId;
    M574_COLLOBJ *col;
    HU3DMODELID baseMdl;

    for (i = 0; i < 2; i++) {
        p = &work->unkE50[i];
        if (i == 0) {
            baseMdl = Hu3DModelCreate(HuDataSelHeapReadNum(0x81001A, HU_MEMNUM_OVL, HEAP_MODEL));
            mdlId = baseMdl;
            for (j = 0; j < 3; j++) {
                motId = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(lbl_1_data_480[j], HU_MEMNUM_OVL, HEAP_MODEL));
                obj->mtnId[j] = motId;
            }
        }
        else {
            mdlId = Hu3DModelLink(baseMdl);
        }
        obj->mdlId[i + 31] = mdlId;
        Hu3DMotionSet(mdlId, obj->mtnId[0]);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelShadowSet(mdlId);
        p->unk000 = 0;
        p->unk010 = lbl_1_data_48C[i];
        p->unk03C = p->unk040 = p->unk044 = 1.0f;
        col = &p->unk04C;
        col->unk00 = 1;
        col->unk04 = 2;
        col->unk08 = i;
        col->unk0C = 0;
        col->unk10 = obj;
        col->unk14 = NULL;
        col->unk18 = fn_1_5628;
        col->unk01C.pos = &p->unk010;
        col->unk020.radius = 40.0f;
        fn_1_8B48(col);
    }
}

/* 464 insns */
void fn_1_4EE8(OMOBJ *obj)
{
    M574_STAGE *work;
    s32 i;
    M574_STAGEOBJ *p;
    HU3DMODELID mdlId;
    HuVecF *home;
    float rotY;

    work = obj->data;
    for (i = 0; i < 2; i++) {
        p = &work->unkE50[i];
        mdlId = obj->mdlId[i + 31];
        home = &lbl_1_data_48C[i];
        rotY = 0.0f;
        switch (p->unk000) {
            case 0:
                p->unk000++;
                p->unk010.x += 150.0 * M574_FRANDS();
                p->unk034 = 0.0f;
                Hu3DMotionSet(mdlId, obj->mtnId[0]);
            case 1:
                if (MgSeqModeGet() != 5) {
                    break;
                }
                p->unk000++;
                p->unk034 = ((s32)frand() & 1) ? -1.0 : 1.0;
                Hu3DMotionShiftSet(mdlId, obj->mtnId[1], 0.0f, 12.0f, HU3D_MOTATTR_LOOP);
            case 2:
                if (MgSeqModeGet() != 5) {
                    p->unk000 = 8;
                    p->unk034 = 0.0f;
                    Hu3DMotionShiftSet(mdlId, obj->mtnId[0], 0.0f, 12.0f, HU3D_MOTATTR_LOOP);
                    break;
                }
                if (p->unk034 < 0.0f) {
                    if (p->unk010.x > home->x - 180.0) {
                        rotY = 270.0f;
                    }
                    else {
                        p->unk034 = 1.0f;
                    }
                }
                else {
                    if (p->unk010.x < 180.0 + home->x) {
                        rotY = 90.0f;
                    }
                    else {
                        p->unk034 = -1.0f;
                    }
                }
                break;
            case 3:
                p->unk01C.y = p->unk01C.y - (1.0f / 60.0f) * 100.0;
                if (p->unk010.y + p->unk01C.y > home->y) {
                    break;
                }
                p->unk010.y = home->y;
                p->unk01C.y = 0.0f;
                if (fn_1_445C(obj, i)) {
                    break;
                }
                p->unk000++;
                p->unk004 = 0;
                Hu3DMotionShiftSet(mdlId, obj->mtnId[0], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                break;
            case 4:
                if (++p->unk004 < 30.0) {
                    break;
                }
                p->unk000 = 2;
                p->unk034 = ((s32)frand() & 1) ? -1.0 : 1.0;
                Hu3DMotionShiftSet(mdlId, obj->mtnId[1], 0.0f, 12.0f, HU3D_MOTATTR_LOOP);
                break;
            case 5:
                if ((p->unk040 = p->unk040 - 0.2) > 0.4) {
                    break;
                }
                p->unk040 = 0.4f;
                p->unk000++;
            case 6:
                if (fn_1_445C(obj, i)) {
                    break;
                }
                p->unk000++;
            case 7:
                if ((p->unk040 += 0.1) < 1.0) {
                    break;
                }
                p->unk040 = 1.0f;
                p->unk000 = 4;
                p->unk004 = 0;
                Hu3DMotionShiftSet(mdlId, obj->mtnId[0], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                break;
            case 8:
                break;
        }
        if ((p->unk000 == 2 || p->unk000 == 4) && p->unk038 != 0) {
            p->unk004 = 0;
            p->unk034 = 0.0f;
            fn_1_43E8(obj, i);
            Hu3DMotionShiftSet(mdlId, obj->mtnId[2], 0.0f, 12.0f, HU3D_MOTATTR_LOOP);
            if (p->unk038 == 1) {
                p->unk000 = 5;
                fn_1_77D4(i, 7);
                if (p->unk010.x < 0.0f) {
                    fn_1_C10(0x92B, &p->unk010);
                    return;
                }
                fn_1_C10(0x92C, &p->unk010);
                return;
            }
            p->unk000 = 3;
            p->unk01C.y = 13.333334f;
            fn_1_77D4(i, 8);
            if (p->unk010.x < 0.0f) {
                fn_1_C10(0x91A, &p->unk010);
                return;
            }
            fn_1_C10(0x91B, &p->unk010);
            return;
        }
        p->unk038 = 0;
        p->unk028.y = fn_1_CC8(p->unk028.y, rotY, 0.05f);
        p->unk01C.x = p->unk01C.x + 0.05 * ((1.0f / 60.0f) * (150.0 * p->unk034) - p->unk01C.x);
        PSVECAdd(&p->unk010, &p->unk01C, &p->unk010);
        Hu3DModelPosSet(mdlId, p->unk010.x, p->unk010.y - 20.0, p->unk010.z);
        Hu3DModelRotSetV(mdlId, &p->unk028);
        Hu3DModelScaleSetV(mdlId, (HuVecF *)&p->unk03C);
    }
}

/* .data after the jumptable (0x4E0) */
/* 0x504 */ char lbl_1_data_504[] = "m548time";
/* 0x510 */ float lbl_1_data_510[10][2] = {
    { -0.25f, -0.125f },
    { -0.25f, 0.0f },
    { -0.25f, 0.125f },
    { -0.25f, 0.25f },
    { -0.25f, 0.375f },
    { -0.25f, 0.5f },
    { -0.25f, 0.625f },
    { -0.25f, 0.75f },
    { 0.0f, -0.125f },
    { 0.0f, 0.0f },
};
/* 0x560 */ s32 lbl_1_data_560[4] = { 0x923, 0x924, 0x925, 0x926 };

/* 22 insns */
s32 fn_1_5628(M574_COLLOBJ *self, M574_COLLACTOR *ball)
{
    s32 idx;
    OMOBJ *obj;
    M574_STAGE *work;
    M574_STAGEOBJ *p;

    idx = self->unk08;
    obj = lbl_1_bss_48;
    work = obj->data;
    p = &work->unkE50[idx];
    p->unk038 = 1;
    return 0;
}

/* 52 insns */
void fn_1_5680(HuVecF *pos)
{
    OMOBJ *obj;
    M574_STAGE *work;
    M574_STAGEOBJ *p;
    s32 i;
    float dist;

    obj = lbl_1_bss_48;
    work = obj->data;
    for (i = 0; i < 2; i++) {
        p = &work->unkE50[i];
        dist = fabs(p->unk010.x - pos->x);
        if (dist < 50.0) {
            p->unk038 = 2;
        }
    }
}

/* 121 insns */
void fn_1_5750(OMOBJ *obj)
{
    M574_STAGE *work;
    M574_STAGEOBJ *bomb;
    HU3DMODELID mdlId;
    M574_COLLOBJ *col;
    HSFOBJECT *hsfObj;

    work = obj->data;
    bomb = &work->unk014;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x810005, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[8] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
    Hu3DModelLayerSet(mdlId, 4);
    fn_1_23E8(obj, mdlId, 0);
    fn_1_2478(obj, &bomb->unk010, 0);
    col = &bomb->unk04C;
    col->unk00 = 1;
    col->unk04 = 1;
    col->unk08 = 100;
    col->unk0C = 0;
    col->unk10 = obj;
    col->unk14 = NULL;
    col->unk18 = fn_1_5D64;
    col->unk01C.pos = &bomb->unk010;
    col->unk020.radius = 200.0f;
    fn_1_8B48(col);
    bomb->unk000 = 0;
    bomb->unk038 = 0;
    bomb->unk01C.x = bomb->unk01C.y = bomb->unk01C.z = 0.0f;
    hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_4A4);
    bomb->unk048 = hsfObj;
    if (hsfObj != NULL) {
        bomb->unk03C = hsfObj->mesh.base.pos.x;
        bomb->unk040 = hsfObj->mesh.base.pos.y;
        bomb->unk044 = hsfObj->mesh.base.pos.z;
    }
}

/* Launches the five bomb shards: 5 x ball fn_1_6C2C. */
static inline void fn_1_5934_Burst(OMOBJ *obj, s32 team)
{
    M574_STAGE *work;
    M574_STAGEOBJ *bomb;
    HuVecF pos;
    HuVecF vel;
    float angle;
    s32 i;

    work = obj->data;
    bomb = &work->unk014;
    pos.x = bomb->unk010.x;
    pos.y = bomb->unk010.y - 150.0;
    pos.z = 300.0f;
    vel.z = 80.0f;
    for (i = 0; i < 5; i++) {
        if (team == 0) {
            angle = 240.0f;
        }
        else {
            angle = 120.0f;
        }
        angle += 10.0 * M574_FRANDS();
        vel.x = 100.0 * (0.2 * sin(M_PI * angle / 180.0));
        vel.y = 100.0 * (0.2 * cos(M_PI * angle / 180.0));
        fn_1_6C2C(&pos, &vel);
    }
}

/* 268 insns */
void fn_1_5934(OMOBJ *obj)
{
    M574_STAGE *work;
    M574_STAGEOBJ *bomb;
    HU3DMODELID mdlId;
    HSFOBJECT *hsfObj;

    work = obj->data;
    bomb = &work->unk014;
    mdlId = obj->mdlId[8];
    switch (bomb->unk000) {
        case 0:
            if (bomb->unk038 == 0) {
                break;
            }
            if (MgSeqModeGet() != 5) {
                break;
            }
            bomb->unk000++;
            bomb->unk004 = 0;
            fn_1_77D4(bomb->unk00C, 6);
            HuAudFXPlay(0x91C);
            HuAudFXPlay(0x91E);
            work->unk00C--;
            fn_1_63B0(&lbl_1_data_4B0[0], &lbl_1_data_4C8[0], work->unk00C);
            fn_1_63B0(&lbl_1_data_4B0[1], &lbl_1_data_4C8[1], work->unk00C);
        case 1:
            if (work->unk00C > 0) {
                if (++bomb->unk004 >= 4) {
                    bomb->unk000--;
                    bomb->unk004 = 0;
                }
                break;
            }
            bomb->unk000++;
            bomb->unk004 = 0;
        case 2:
            if (++bomb->unk004 < 60.0) {
                break;
            }
            fn_1_5934_Burst(obj, bomb->unk00C);
            bomb->unk000++;
            bomb->unk004 = 0;
        case 3:
            if (++bomb->unk004 < 60.0) {
                break;
            }
            bomb->unk000 = 0;
            bomb->unk004 = 0;
            work->unk00C = 5;
            break;
    }
    if (Hu3DMotionEndCheck(mdlId)) {
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 0.0f, 60.0f);
        Hu3DMotionTimeSet(mdlId, 0.0f);
    }
    bomb->unk038 = 0;
    PSVECScale(&bomb->unk01C, &bomb->unk01C, 0.2f);
    hsfObj = bomb->unk048;
    if (hsfObj != NULL) {
        hsfObj->mesh.base.pos.x = bomb->unk03C + bomb->unk01C.x;
        hsfObj->mesh.base.pos.y = bomb->unk040 + bomb->unk01C.y;
    }
}

/* 62 insns */
s32 fn_1_5D64(M574_COLLOBJ *self, M574_COLLACTOR *ball)
{
    OMOBJ *obj;
    M574_STAGE *work;
    M574_STAGEOBJ *bomb;
    HU3DMODELID mdlId;

    obj = lbl_1_bss_48;
    work = obj->data;
    bomb = &work->unk014;
    mdlId = obj->mdlId[8];
    if (bomb->unk000 == 0) {
        bomb->unk038 = 1;
        bomb->unk00C = ball->unk18->x < 0.0f ? 0 : 1;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 60.0f, Hu3DMotionMaxTimeGet(mdlId));
        Hu3DMotionTimeSet(mdlId, 60.0f);
        PSVECNormalize(ball->unk1C, &bomb->unk01C);
        PSVECScale(&bomb->unk01C, &bomb->unk01C, 50.0f);
    }
    return 0;
}

/* 28 insns */
void fn_1_5E5C(OMOBJ *obj)
{
    M574_STAGE *work;
    HU3DMODELID mdlId;

    work = obj->data;
    mdlId = obj->mdlId[8];
    work->unk008 = Hu3DTexScrollCreate(mdlId, lbl_1_data_504);
    work->unk00C = 5;
    work->unk010 = 5.0f;
}

/* 167 insns */
void fn_1_5ECC(OMOBJ *obj)
{
    M574_STAGE *work;
    float diff;
    float u;
    float v;
    float frac;
    s32 n;

    work = obj->data;
    diff = fmodf(work->unk00C - work->unk010, 10.0f);
    if (diff < 0.0) {
        diff += 10.0;
    }
    if (diff > 5.0) {
        diff -= 10.0;
    }
    diff = fmodf(work->unk010 + 0.1 * diff, 10.0f);
    if (diff < 0.0) {
        diff += 10.0;
    }
    work->unk010 = diff;
    n = 0.5 + diff;
    frac = 0.125 * (diff - n);
    if (n > 9) {
        n = 0;
    }
    if (n < 0) {
        n = 0;
    }
    u = lbl_1_data_510[n][0];
    v = frac + lbl_1_data_510[n][1];
    Hu3DTexScrollPosSet(work->unk008, u, v, 0.0f);
}

/* 77 insns */
void fn_1_6168(OMOBJ *obj)
{
    M574_STAGE *work;
    ANIMDATA *anim;
    s32 i;
    HU3DMODELID mdlId;
    HU3DPARTICLE *particle;
    s32 j;
    HU3DPARTICLEDATA *data;

    work = obj->data;
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x810020, HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 5; i++) {
        mdlId = Hu3DParticleCreate(anim, 8);
        work->unk09C[i] = mdlId;
        particle = Hu3DData[mdlId].hookData;
        Hu3DParticleBlendModeSet(mdlId, 0);
        Hu3DParticleHookSet(mdlId, fn_1_62A0);
        Hu3DModelLayerSet(mdlId, 7);
        Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
        Hu3DParticleAnimModeSet(mdlId, 4 - i);
        data = particle->data;
        for (j = 0; j < particle->maxCnt; j++, data++) {
            data->time = -1;
            data->scale = 0.0f;
        }
    }
}

/* 1 insns */
void fn_1_629C(OMOBJ *obj) { }

/* 68 insns */
void fn_1_62A0(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;

    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        switch (data->time) {
            case 0:
                data->time++;
                data->scale = 200.0f;
                data->color.a = 180;
            case 1:
                data->scale -= 10.0f;
                data->color.a -= 4;
                if (data->scale <= 0.0f || data->color.a > 240) {
                    data->time = -1;
                    data->scale = 0.0f;
                }
                else {
                    PSVECAdd(&data->pos, &data->accel, &data->pos);
                }
                break;
        }
    }
}

/* 50 insns */
void fn_1_63B0(HuVecF *pos, HuVecF *accel, s32 n)
{
    M574_STAGE *work;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s32 i;

    work = lbl_1_bss_48->data;
    particle = Hu3DData[work->unk09C[4 - n]].hookData;
    data = particle->data;
    for (i = 0; i < particle->maxCnt; i++, data++) {
        if (data->time < 0) {
            data->time = 0;
            data->pos = *pos;
            data->accel = *accel;
            break;
        }
    }
}

/* 60 insns */
void fn_1_6478(s32 idx, float value)
{
    M574_STAGE *work;
    M574_PADDLE *gauge;
    float ofs;

    work = lbl_1_bss_48->data;
    gauge = &work->unk0A8[idx];
    if (value - gauge->unk000 > 0.2) {
        HuAudFXPlay(lbl_1_data_560[idx]);
    }
    gauge->unk000 = value;
    ofs = 60.0 * value;
    if (idx & 1) {
        ofs = -ofs;
    }
    gauge->unk00C = ofs + lbl_1_data_280[idx];
}

/* 58 insns */
float fn_1_6568(s32 idx)
{
    M574_STAGE *work;
    M574_PADDLE *gauge;
    float value;

    work = lbl_1_bss_48->data;
    gauge = &work->unk0A8[idx];
    if (idx & 1) {
        value = lbl_1_data_280[idx] - gauge->unk008;
    }
    else {
        value = gauge->unk008 - lbl_1_data_280[idx];
    }
    value = value / 60.0;
    if (value < 0.0f) {
        value = 0.0f;
    }
    if (value > 1.0f) {
        value = 1.0f;
    }
    return value;
}

