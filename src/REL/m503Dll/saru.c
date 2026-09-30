/*
 * m503dll saru.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/saru.s.
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
/* 0x240 */ /* float lbl_1_rodata_240 = 0.0f; */
/* 0x248 */ /* double lbl_1_rodata_248 = 4; */
/* 0x250 */ /* double lbl_1_rodata_250 = 0.0000152587890625; */
/* 0x258 */ /* double lbl_1_rodata_258 = 3; */
/* 0x260 */ /* float lbl_1_rodata_260 = 0.8f; */
/* 0x268 */ /* double lbl_1_rodata_268 = 4503601774854144; */
/* 0x270 */ /* double lbl_1_rodata_270 = 24; */
/* 0x278 */ /* double lbl_1_rodata_278 = 100; */
/* 0x280 */ /* double lbl_1_rodata_280 = 5; */
/* 0x288 */ /* double lbl_1_rodata_288 = 3.141592653589793; */
/* 0x290 */ /* double lbl_1_rodata_290 = 180; */
/* 0x298 */ /* double lbl_1_rodata_298 = 10; */
/* 0x2A0 */ /* double lbl_1_rodata_2A0 = 300; */
/* 0x2A8 */ /* float lbl_1_rodata_2A8 = 100.0f; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 480; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = 4503599627370496; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 0.000030517578125; */
/* 0x2C8 */ /* float lbl_1_rodata_2C8 = 30.0f; */
/* 0x2CC */ /* float lbl_1_rodata_2CC = 50.0f; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = -470; */
/* 0x2D8 */ /* double lbl_1_rodata_2D8 = 570; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 0.5; */
/* 0x2E8 */ /* float lbl_1_rodata_2E8 = 1.0f; */
/* 0x2F0 */ /* double lbl_1_rodata_2F0 = 1; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = 150; */
/* 0x300 */ /* double lbl_1_rodata_300 = 0.2; */
/* 0x308 */ /* float lbl_1_rodata_308 = 0.2f; */
/* 0x30C */ /* float lbl_1_rodata_30C = 0.016666668f; */
/* 0x310 */ /* float lbl_1_rodata_310 = 26.666668f; */
/* 0x314 */ /* float lbl_1_rodata_314 = 28.333334f; */
/* 0x318 */ /* float lbl_1_rodata_318 = 180.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 150.0f; */
/* 0x320 */ /* double lbl_1_rodata_320 = 30; */
/* 0x328 */ /* double lbl_1_rodata_328 = 50; */
/* 0x330 */ /* float lbl_1_rodata_330 = 90.0f; */
/* 0x338 */ /* double lbl_1_rodata_338 = 12; */
/* 0x340 */ /* float lbl_1_rodata_340 = 0.3f; */
/* 0x344 */ /* float lbl_1_rodata_344 = 10.000001f; */
/* 0x348 */ /* float lbl_1_rodata_348 = 40.000004f; */
/* 0x350 */ /* double lbl_1_rodata_350 = 20; */
/* 0x358 */ /* double lbl_1_rodata_358 = 0.01666666753590107; */
/* 0x360 */ /* double lbl_1_rodata_360 = 1000; */
/* 0x368 */ /* double lbl_1_rodata_368 = 400; */
/* 0x370 */ /* double lbl_1_rodata_370 = 2400; */
/* 0x378 */ /* float lbl_1_rodata_378 = 0.1f; */
/* 0x380 */ /* double lbl_1_rodata_380 = -250; */
/* 0x388 */ /* float lbl_1_rodata_388 = 800.0f; */
/* 0x38C */ /* float lbl_1_rodata_38C = -800.0f; */
/* 0x390 */ /* double lbl_1_rodata_390 = 250; */
/* 0x398 */ /* double lbl_1_rodata_398 = -380; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = -380.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 300.0f; */
/* 0x3A8 */ /* float lbl_1_rodata_3A8 = 6.666667f; */
/* 0x3AC */ /* float lbl_1_rodata_3AC = 120.0f; */
/* 0x3B0 */ /* float lbl_1_rodata_3B0 = 45.0f; */
/* 0x3B8 */ /* double lbl_1_rodata_3B8 = -370; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = 370; */
/* 0x3C8 */ /* double lbl_1_rodata_3C8 = 0; */
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 0.1666666753590107; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = 0.08f; */
/* 0x3DC */ /* float lbl_1_rodata_3DC = 200.0f; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 1600; */
/* 0x3E8 */ /* double lbl_1_rodata_3E8 = 360; */
/* 0x3F0 */ /* double lbl_1_rodata_3F0 = 200; */
/* 0x3F8 */ /* double lbl_1_rodata_3F8 = 1500; */
/* 0x400 */ /* float lbl_1_rodata_400 = 80.0f; */
/* 0x404 */ /* float lbl_1_rodata_404 = 5.0f; */
/* 0x408 */ /* double lbl_1_rodata_408 = 1.3333333730697632; */
/* 0x410 */ /* double lbl_1_rodata_410 = 0.1; */
/* 0x418 */ /* double lbl_1_rodata_418 = 6; */
/* 0x420 */ /* double lbl_1_rodata_420 = 0.98; */
/* 0x428 */ /* double lbl_1_rodata_428 = 2.0000001043081284; */
/* 0x430 */ /* double lbl_1_rodata_430 = -8; */
/* 0x438 */ /* float lbl_1_rodata_438 = 15.0f; */
/* 0x43C */ /* float lbl_1_rodata_43C = 60.0f; */
/* 0x440 */ /* float lbl_1_rodata_440 = 100000.0f; */
/* 0x444 */ /* float lbl_1_rodata_444 = 360.0f; */
/* 0x448 */ /* float lbl_1_rodata_448[2] = { -1.6f, 0.0f }; */

/* --- .data --- */
/* 0x1E0 */ M503_SARUDATA lbl_1_data_1E0[9] = {
    { 0x003D0005, 1, 0, 2, fn_1_6044 },
    { 0x003D0006, 1, 0, 2, fn_1_6044 },
    { 0x003D0007, 1, 0, 2, fn_1_6044 },
    { 0x003D0008, 1, 0, 2, fn_1_6044 },
    { 0x003D0009, 5, 1, 11, fn_1_6458 },
    { 0x003D000A, 5, 1, 11, fn_1_6458 },
    { 0x003D000B, 5, 1, 11, fn_1_6458 },
    { 0x003D000C, 5, 1, 11, fn_1_6458 },
    { 0x003D000D, 1, 2, 11, fn_1_6458 },
};
/* 0x270 */ s32 lbl_1_data_270[3][11] = {
    { 0x003D000E, 0x003D000F },
    { 0x003D0010, 0x003D0011, 0x003D0012, 0x003D0013, 0x003D0014, 0x003D0015, 0x003D0016, 0x003D0017, 0x003D0018, 0x003D0019, 0x003D001A },
    { 0x003D001B, 0x003D001C, 0x003D001D, 0x003D001E, 0x003D001F, 0x003D0020, 0x003D0021, 0x003D0022, 0x003D0023, 0x003D0024, 0x003D0025 },
};
/* 0x2F4 */ M503_SARUMOT lbl_1_data_2F4[2] = { { 0.2f, 0x40000001 }, { 0.2f, 0x40000001 } };
/* 0x304 */ M503_SARUMOT lbl_1_data_304[11] = { { 0.1f, 0x40000001 }, { 0.1f, 0x40000001 }, { 0.1f, 0x40000001 }, { 0.1f, 0 }, { 0.1f, 0x40000001 }, { 0.1f, 0x40000001 }, { 0.1f, 0 }, { 0.1f, 0 }, { 0.1f, 0 }, { 0.1f, 0x40000001 }, { 0.1f, 0 } };
/* 0x35C */ HuVecF lbl_1_data_35C[4] = { { -820.0f, 55.0f, -740.0f }, { 820.0f, 55.0f, -740.0f }, { 820.0f, 55.0f, 820.0f }, { -820.0f, 55.0f, 820.0f } };
/* 0x38C */ HuVecF lbl_1_data_38C[4] = { { -370.0f, 90.0f, -325.0f }, { 370.0f, 90.0f, -325.0f }, { 370.0f, 90.0f, 400.0f }, { -370.0f, 90.0f, 400.0f } };
/* 0x3BC */ float lbl_1_data_3BC[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
/* 0x3CC */ HuVecF lbl_1_data_3CC[4] = { { -510.0f, 265.0f, -380.0f }, { 510.0f, 265.0f, -380.0f }, { 520.0f, 265.0f, 390.0f }, { -520.0f, 265.0f, 390.0f } };
/* 0x3FC */ float lbl_1_data_3FC[4] = { 45.0f, 315.0f, 225.0f, 135.0f };
/* 0x40C */ s32 lbl_1_data_40C[5] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000003 };
/* 0x420 */ HuVecF lbl_1_data_420 = { 0.0f, 0.0f, 0.0f }; /* shadow offset (particle fn_1_CB48) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xB4 gap_05_000000B4_bss (0x4) -- dtk filler */
/* 0xB0 */ OMOBJ *lbl_1_bss_B0;
/* 0x9C */ OMOBJ *lbl_1_bss_9C[5]; /* rows 0..3 monkeys, NULL-terminated */
/* 0x44 */ OMOBJ *lbl_1_bss_44[22]; /* crowd monkeys, NULL-terminated (21 + NULL) */
/* 0x40 */ s32 lbl_1_bss_40;

/* --- functions (reference order) --- */
/* 335 insns */
void fn_1_5810(OMOBJMAN *objman)
{
    s16 motCache[3][11];
    s16 cnt5[5];
    s16 cnt4[4];
    M503_SARUDATA *data;
    s32 n9C;
    s32 n44;
    s32 i;
    HU3DMODELID mdlId;
    s32 k;
    s32 *motData;
    s32 slot;
    OMOBJ *obj;
    M503_SARU *work;
    HU3DMODELID baseMdl;
    s32 j;
    s32 num;
    s16 *cache;

    data = lbl_1_data_1E0;
    n9C = 0;
    n44 = 0;
    lbl_1_bss_B0 = omAddObjEx(objman, 0x32, 0, 0, -1, fn_1_5D50);
    for (k = 0; k < 4; k++) {
        cnt4[k] = 0;
    }
    for (k = 0; k < 5; k++) {
        cnt5[k] = 0;
    }
    for (i = 0; i < 3; i++) {
        for (k = 0; k < 11; k++) {
            motCache[i][k] = -1;
        }
    }
    for (i = 0; i < 9; i++, data++) {
        num = data->unk004;
        if (i >= 4 && i <= 7) {
            num++;
        }
        for (j = 0; j < num; j++) {
            obj = omAddObjEx(objman, 0x28, 1, data->unk008, 0, data->unk00C);
            obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_SARU), HU_MEMNUM_OVL);
            work = obj->data;
            memset(work, 0, sizeof(M503_SARU));
            obj->stat |= OM_STAT_MODELPAUSE;
            work->unk000 = i;
            work->unk008 = j;
            work->unk00C = -1;
            work->unk034 = -1;
            work->unk010 = 0;
            work->unk044.x = work->unk044.y = work->unk044.z = 0.0f;
            if (j == 0) {
                baseMdl = Hu3DModelCreateData(data->unk000);
                mdlId = baseMdl;
            } else {
                mdlId = Hu3DModelLink(baseMdl);
            }
            obj->mdlId[0] = mdlId;
            motData = lbl_1_data_270[data->unk006];
            cache = motCache[data->unk006];
            for (k = 0; k < data->unk008; motData++, cache++, k++) {
                if (*cache < 0) {
                    *cache = Hu3DJointMotionData(mdlId, *motData);
                }
                obj->mtnId[k] = *cache;
            }
            if (i < 4) {
                work->unk064 = i;
                lbl_1_bss_9C[n9C++] = obj;
                Hu3DModelLayerSet(mdlId, 7);
                slot = 4.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                for (k = 0; k < 4; k++, slot++) {
                    if (slot >= 4) {
                        slot = 0;
                    }
                    if (cnt4[slot] == 0) {
                        break;
                    }
                }
                cnt4[slot]++;
                work->unk05C = slot;
            } else {
                if (i == 8) {
                    work->unk004 = 4;
                } else {
                    work->unk004 = 4.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                    slot = 3.0 * ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF));
                    for (k = 0; k < 4; k++, slot++) {
                        if (slot >= 4) {
                            slot = 0;
                        }
                        if (cnt5[slot] < 5) {
                            break;
                        }
                    }
                    cnt5[slot]++;
                    work->unk004 = slot;
                }
                work->unk064 = i - 4;
                Hu3DModelScaleSet(mdlId, 0.8f, 0.8f, 0.8f);
                Hu3DModelLayerSet(mdlId, 7);
                if (work->unk064 < 4 && j == num - 1) {
                    work->unk008 = 0;
                    obj->objFunc = fn_1_5F50;
                } else {
                    lbl_1_bss_44[n44++] = obj;
                }
            }
        }
    }
    lbl_1_bss_9C[n9C] = NULL;
    lbl_1_bss_44[n44] = NULL;
}

/* 1 insns */
void fn_1_5D4C(void) { }

/* 4 insns */
void fn_1_5D50(OMOBJ *obj)
{
    obj->objFunc = fn_1_5D60;
}

/* 124 insns */
void fn_1_5D60(OMOBJ *obj)
{
    float angle[4];
    s32 i;
    OMOBJ *o;
    M503_SARU *work;
    s32 idx;
    HuVecF *base;
    float a;

    lbl_1_bss_40 = 0;
    for (i = 0; i < 4; i++) {
        angle[i] = lbl_1_data_3BC[i] - 24.0;
    }
    for (i = 0; i < 21; i++) {
        o = lbl_1_bss_44[i];
        if (o == NULL) {
            break;
        }
        work = o->data;
        if (work->unk068 == 0) {
            lbl_1_bss_40++;
            continue;
        }
        idx = work->unk06C;
        a = angle[idx];
        base = &lbl_1_data_35C[idx];
        work->unk074.x = base->x + 100.0 * (5.0 * sin(M_PI * a / 180.0));
        work->unk074.y = base->y;
        work->unk074.z = base->z + 100.0 * (5.0 * cos(M_PI * a / 180.0));
        work->unk070 = 1;
        a += 10.0;
        angle[idx] = a;
    }
}

/* 40 insns */
void fn_1_5F50(OMOBJ *obj)
{
    M503_SARU *work = obj->data;

    obj->trans.x = work->unk038.x = lbl_1_data_3CC[work->unk064].x;
    obj->trans.y = work->unk038.y = lbl_1_data_3CC[work->unk064].y;
    obj->trans.z = work->unk038.z = lbl_1_data_3CC[work->unk064].z;
    work->unk050 = lbl_1_data_3FC[work->unk064];
    obj->objFunc = fn_1_5FF0;
}

/* 21 insns */
void fn_1_5FF0(OMOBJ *obj)
{
    M503_SARU *work = obj->data;

    fn_1_9A04(obj, 9);
    fn_1_98D0(obj);
    work->unk030++;
}

/* 42 insns */
void fn_1_6044(OMOBJ *obj)
{
    M503_SARU *work = obj->data;

    obj->trans.x = work->unk038.x = lbl_1_data_38C[work->unk000].x;
    obj->trans.y = work->unk038.y = lbl_1_data_38C[work->unk000].y;
    obj->trans.z = work->unk038.z = lbl_1_data_38C[work->unk000].z;
    work->unk050 = lbl_1_data_3BC[work->unk000];
    work->unk010 = 0;
    obj->objFunc = fn_1_60EC;
}

/* 183 insns */
void fn_1_60EC(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    float time;

    switch (work->unk010) {
    case 0:
        work->unk010++;
        fn_1_9A04(obj, 0);
    case 1:
        if (fn_1_1AE0() != 2) {
            break;
        }
        work->unk010++;
        work->unk014 = 300.0 + (180.0 * work->unk05C + (s32)(frand() & 0x3F));
    case 2:
        if (fn_1_1AE0() != 2) {
            work->unk010 = 4;
            break;
        }
        if (--work->unk014 > 0) {
            break;
        }
        if (fn_1_63C8(obj) == 0) {
            work->unk014 = 180;
            break;
        }
        fn_1_9A04(obj, 1);
        fn_1_1FD8(0x642, &work->unk038);
        work->unk058 = 1;
        work->unk060 = 100.0f;
        work->unk010++;
        work->unk014 = 120;
        break;
    case 3:
        if (fn_1_1AE0() != 2) {
            work->unk010 = 4;
            break;
        }
        if (Hu3DMotionShiftIDGet(mdlId) == -1) {
            time = Hu3DMotionTimeGet(mdlId);
            if (time < work->unk060) {
                fn_1_1FD8(0x642, &work->unk038);
            }
            work->unk060 = time;
        }
        if (--work->unk014 > 0) {
            break;
        }
        fn_1_9A04(obj, 0);
        work->unk058 = 0;
        work->unk010--;
        work->unk014 = 480.0 + (s32)(frand() & 0xFF);
        break;
    case 4:
        fn_1_9A04(obj, 0);
        work->unk058 = 0;
        work->unk010++;
        break;
    case 5:
        break;
    }
    fn_1_98D0(obj);
    work->unk030++;
}

/* 36 insns */
s32 fn_1_63C8(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    OMOBJ *o;
    s32 n = 0;
    M503_SARU *other;
    s32 i;
    u32 row;

    for (i = 0; i < 21; i++) {
        o = lbl_1_bss_44[i];
        if (o == NULL) {
            break;
        }
        other = o->data;
        if (other->unk068 == 0) {
            row = other->unk064;
            if (work->unk000 == row) {
                n++;
            }
        }
    }
    return n;
}

/* 112 insns */
void fn_1_6458(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    M503_ACTORENT *actor;
    M503_SARUSHADOW *ring;

    obj->trans.x = work->unk038.x = 300.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
    obj->trans.y = work->unk038.y = 0.0f;
    obj->trans.z = work->unk038.z = 300.0 * ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768));
    work->unk050 = 0.0f;
    actor = &work->unk0A8;
    actor->unk000 = 1;
    actor->unk004 = 1;
    actor->unk008 = 0;
    actor->unk00C = 0;
    actor->unk010 = obj;
    actor->unk014 = fn_1_98D0;
    actor->unk018 = &work->unk038;
    actor->unk01C = 30.0f;
    fn_1_DF30(actor);
    ring = &work->unk0C8;
    ring->unk000 = 0;
    ring->unk004 = 50.0f;
    ring->unk008 = &work->unk038;
    ring->unk00C = &lbl_1_data_420;
    fn_1_D134(ring);
    work->unk010 = 0;
    obj->objFunc = fn_1_6618;
}

/* 381 insns */
void fn_1_6618(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float dx;
    float dz;
    float dist;
    float amb;
    float h;
    M503_SARU *other;
    OMOBJ *o;
    HU3DMODELID mdlId;

    dx = -470.0 - work->unk038.x;
    dz = 570.0 - work->unk038.z;
    dist = sqrtf(dx * dx + dz * dz);
    if (dist > 300.0) {
        amb = 1.0f;
    } else {
        amb = 1.0 - (300.0 - dist) / 150.0;
        if (amb < 0.2) {
            amb = 0.2f;
        }
    }
    Hu3DModelAmbSet(obj->mdlId[0], amb, amb, amb);
    if (work->unk080) {
        fn_1_6C0C(obj, 7);
    }
    if (work->unk068) {
        fn_1_6C0C(obj, 8);
    }
    if (!work->unk080 && work->unk010 != 8 && !work->unk088 && work->unk000 != 8) {
        o = lbl_1_bss_9C[work->unk064];
        other = o->data;
        if (other->unk058) {
            work->unk0A8.unk000 |= 1;
            fn_1_6C0C(obj, 6);
        }
    }
    switch (work->unk010) {
    case 0:
        fn_1_9A04(obj, 0);
        mdlId = obj->mdlId[0];
        Hu3DMotionTimeSet(mdlId, ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF)) * (Hu3DMotionMaxTimeGet(mdlId) - 1.0));
        if (work->unk000 == 8) {
            fn_1_6C0C(obj, 3);
        } else {
            fn_1_6C0C(obj, 1);
        }
        break;
    case 1:
        if (fn_1_6F8C(obj)) {
            fn_1_6C0C(obj, 2);
        }
        break;
    case 2:
        fn_1_6F94(obj);
        if (fn_1_1AE0() == 2) {
            if (++work->unk014 >= (work->unk008 + 1) * 10) {
                fn_1_6C0C(obj, 4);
            }
        }
        break;
    case 3:
        if (fn_1_6FC4(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    case 4:
        if (fn_1_1AE0() != 2) {
            fn_1_6C0C(obj, 9);
            break;
        }
        if (fn_1_721C(obj)) {
            if (((s32)frand() & 0x3F) == 0) {
                fn_1_6C0C(obj, 5);
            } else if (((s32)frand() & 0x3F) == 0) {
                fn_1_6C0C(obj, 10);
            }
        }
        break;
    case 5:
        if (fn_1_780C(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    case 6:
        if (fn_1_7A78(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    case 7:
        if (fn_1_7C8C(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    case 8:
        if (fn_1_7D6C(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    case 9:
        fn_1_82B4(obj);
        break;
    case 10:
        if (fn_1_8AD8(obj)) {
            fn_1_6C0C(obj, 4);
        }
        break;
    }
    if (!work->unk080) {
        if (!work->unk088 && !work->unk068) {
            h = fn_1_BFE8(work->unk038.x, work->unk038.z);
            work->unk038.y = work->unk038.y + 0.5 * (h - work->unk038.y);
        }
        PSVECAdd(&work->unk038, &work->unk044, &work->unk038);
    }
    work->unk030++;
}

/* 0x458 */ HuVecF lbl_1_data_458[4] = { { -700.0f, 300.0f, 0.0f }, { 700.0f, 300.0f, 0.0f }, { 0.0f, 300.0f, 700.0f }, { 0.0f, 0.0f, 0.0f } };
/* 0x488 */ float lbl_1_data_488[3] = { 90.0f, 270.0f, 180.0f };
/* 0x494 */ float lbl_1_data_494[5] = { 90.0f, 90.0f, 50.0f, 90.0f, 180.0f };
/* 0x4A8 */ float lbl_1_data_4A8[5] = { 320.0f, 320.0f, 200.0f, 320.0f, 350.0f };
/* 0x4BC */ s32 lbl_1_data_4BC[5] = { 180, 180, 180, 60, 90 };
/* 0x4D0 */ float lbl_1_data_4D0[5] = { 0.2f, 5.0f, 0.2f, 0.2f, -1.0f };
/* 0x4E4 */ float lbl_1_data_4E4[5] = { 5.0000005f, 3.3333335f, 2.5000002f, 3.3333335f, 5.8333335f };
/* 0x4F8 */ float lbl_1_data_4F8[5] = { 10.000001f, 6.666667f, 5.0000005f, 6.666667f, 10.833334f };
/* 0x50C */ float lbl_1_data_50C[4] = { 200.0f, 200.0f, 250.0f, 250.0f };

/* 20 insns */
void fn_1_6C0C(OMOBJ *obj, s32 action)
{
    M503_SARU *work = obj->data;

    if (work->unk010 != action) {
        work->unk010 = action;
        work->unk014 = 0;
        work->unk018 = 0;
        work->unk01C = 0;
        work->unk024 = 0;
        work->unk028 = 0;
    }
}

/* 18 insns */
void fn_1_6C5C(OMOBJ *obj, float x, float z, float rate)
{
    M503_SARU *work = obj->data;

    work->unk044.x += rate * (x - work->unk044.x);
    work->unk044.z += rate * (z - work->unk044.z);
}

/* 70 insns */
void fn_1_6CA4(OMOBJ *obj, float angle, float speed, float rate)
{
    fn_1_6C5C(obj, speed * HuSin(angle), speed * HuCos(angle), rate);
}

/* 35 insns */
void fn_1_6DBC(OMOBJ *obj, float rate)
{
    M503_SARU *work = obj->data;
    float angle;

    angle = HuAtan(work->unk044.x, work->unk044.z);
    work->unk050 = fn_1_2B7C(work->unk050, angle, rate);
}

/* 81 insns */
void fn_1_6E48(OMOBJ *obj, float speed, float rate)
{
    M503_SARU *work = obj->data;
    float angle = work->unk050;
    float x;
    float z;

    z = (1.0f / 60.0f) * speed * cos(M_PI * angle / 180.0);
    x = (1.0f / 60.0f) * speed * sin(M_PI * angle / 180.0);

    fn_1_6C5C(obj, x, z, rate);
}

/* 2 insns */
s32 fn_1_6F8C(OMOBJ *obj)
{
    return 1;
}

/* 12 insns */
s32 fn_1_6F94(OMOBJ *obj)
{
    fn_1_9A04(obj, 0);
    return 0;
}

/* 150 insns */
s32 fn_1_6FC4(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    s32 idx;
    HU3DMODELID mdlId = obj->mdlId[0];
    float angle;
    float radius;

    switch (work->unk018) {
    case 0:
        work->unk018++;
        work->unk044.x = work->unk044.y = work->unk044.z = 0.0f;
        work->unk088 = 1;
        work->unk0A8.unk000 &= ~1;
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        break;
    case 1:
        if (fn_1_1D30() > 10) {
            break;
        }
        work->unk018++;
        work->unk024 = 0;
        work->unk028 = 0;
        idx = 3.0 * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF));
        angle = lbl_1_data_488[idx];
        radius = 26.666668f;
        work->unk08C.y = 28.333334f;
        work->unk08C.x = radius * sin(M_PI * angle / 180.0);
        work->unk08C.z = radius * cos(M_PI * angle / 180.0);
        work->unk038 = lbl_1_data_458[idx];
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        work->unk034 = fn_1_1FD8(0x643, &work->unk038);
    case 2:
        if (fn_1_961C(obj)) {
            work->unk0A8.unk000 |= 1;
            return 1;
        }
        break;
    }
    return 0;
}

/* 380 insns */
s32 fn_1_721C(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    OMOBJ *player;
    float dx;
    float dz;
    float dist;
    float angle;
    float radius;
    HuVecF pos;

    switch (work->unk018) {
    case 0:
        player = fn_1_53D4(&work->unk038, work->unk050, lbl_1_data_494[work->unk004], lbl_1_data_4A8[work->unk004]);
        if (player == NULL) {
            player = fn_1_53D4(&work->unk038, work->unk050, 180.0f, 150.0f);
            if (player == NULL) {
                fn_1_8EA0(obj);
                return 1;
            }
        }
        work->unk018++;
        work->unk024 = 0;
        work->unk028 = 0;
    case 1:
        radius = lbl_1_data_4A8[work->unk004];
        player = fn_1_53D4(&work->unk038, work->unk050, 180.0f, 30.0 + radius);
        if (player == NULL) {
            work->unk018--;
            return 1;
        }
        dx = work->unk038.x;
        dz = work->unk038.z;
        dist = sqrtf(dx * dx + dz * dz);
        if (dist < 50.0 + radius) {
            fn_1_5708(player, &pos, 0);
            dx = work->unk038.x - pos.x;
            dz = work->unk038.z - pos.z;
            dist = (30.0 + radius) - sqrtf(dx * dx + dz * dz);
            dist /= 5.0;
            if (work->unk008 & 1) {
                dist = -dist;
            }
            angle = dist + 180.0 * (atan2(dx, dz) / M_PI);
            dist = 30.0 + radius;
        } else {
            angle = 180.0 * (atan2(-dx, -dz) / M_PI);
            if (work->unk008 & 1) {
                angle += 90.0f;
            } else {
                angle -= 90.0f;
            }
            pos = work->unk038;
            dist = 100.0f;
        }
        work->unk098.x = pos.x + dist * sin(M_PI * angle / 180.0);
        work->unk098.z = pos.z + dist * cos(M_PI * angle / 180.0);
        work->unk0A4 = 0.0f;
        fn_1_9210(obj);
    }
    return 0;
}

/* 155 insns */
s32 fn_1_780C(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float target;

    switch (work->unk018) {
    case 0:
        work->unk018++;
        work->unk01C = 0;
        work->unk020 = frand() & 1;
        fn_1_9A04(obj, 0);
        break;
    case 1:
        if (++work->unk01C < 12.0) {
            break;
        }
        work->unk018++;
        if (work->unk020 == 0) {
            fn_1_9A04(obj, 6);
        } else {
            fn_1_9A04(obj, 7);
        }
        break;
    case 2:
        if (fn_1_9B00(obj)) {
            work->unk018++;
            work->unk01C = 0;
            fn_1_9A04(obj, 0);
        }
        break;
    case 3:
        if (++work->unk01C < 12.0) {
            break;
        }
        return 1;
    }
    target = (work->unk020 == 0) ? 0 : 180;
    work->unk050 = fn_1_2B7C(work->unk050, target, 0.2f);
    fn_1_6C5C(obj, 0.0f, 0.0f, 0.3f);
    return 0;
}

/* 133 insns */
s32 fn_1_7A78(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    OMOBJ *other;
    M503_SARU *otherWork;
    float angle;
    float dx;
    float dz;

    if (work->unk000 == 8) {
        return 1;
    }
    other = lbl_1_bss_9C[work->unk064];
    otherWork = other->data;
    switch (work->unk018) {
    case 0:
        work->unk018++;
        fn_1_9A04(obj, 8);
        break;
    case 1:
        if (fn_1_9B00(obj)) {
            work->unk018++;
            fn_1_9A04(obj, 9);
        }
        break;
    case 2:
        if (otherWork->unk058 == 0) {
            work->unk018++;
            fn_1_9A04(obj, 10);
        }
        break;
    case 3:
        if (fn_1_9B00(obj)) {
            return 1;
        }
        break;
    }
    dx = otherWork->unk038.x - work->unk038.x;
    dz = otherWork->unk038.z - work->unk038.z;
    angle = 180.0 * (atan2(dx, dz) / M_PI);
    work->unk050 = fn_1_2B7C(work->unk050, angle, 0.2f);
    fn_1_6C5C(obj, 0.0f, 0.0f, 0.3f);
    return 0;
}

/* 56 insns */
s32 fn_1_7C8C(OMOBJ *obj)
{
    M503_SARU *work = obj->data;

    if (work->unk080 == 0) {
        return 1;
    }
    switch (work->unk018) {
    case 0:
        work->unk018++;
        work->unk01C = 0;
        fn_1_9A04(obj, 4);
        break;
    case 1:
        if (++work->unk01C >= lbl_1_data_4BC[work->unk004]) {
            work->unk018++;
            work->unk01C = 0;
            fn_1_9A04(obj, 5);
        }
        break;
    case 2:
        break;
    }
    return 0;
}

/* 338 insns */
#define M503_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M503_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

s32 fn_1_7D6C(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float angle;
    float speed;
    float dx;
    float dz;

    switch (work->unk018) {
        case 0:
            if (work->unk070 == 0) {
                break;
            }
            work->unk018++;
            work->unk024 = 0;
            work->unk028 = 0;
            dx = work->unk074.x - work->unk038.x;
            dz = work->unk074.z - work->unk038.z;
            angle = HuAtan(dx, dz);
            speed = 10.000001f;
            work->unk08C.y = 40.000004f;
            work->unk08C.x = speed * HuSin(angle);
            work->unk08C.z = speed * HuCos(angle);
        case 1:
            if (work->unk088 == 0) {
                work->unk0C8.unk000 = 1;
            }
            if (fn_1_961C(obj)) {
                work->unk018++;
                work->unk01C = 0;
                work->unk024 = 0;
                work->unk028 = 0;
            }
            break;
        case 2:
            work->unk098 = work->unk074;
            work->unk0A4 = lbl_1_data_3BC[work->unk06C];
            fn_1_9210(obj);
            if (fn_1_1AE0() != 2) {
                break;
            }
            if (fn_1_1D30() <= 2) {
                break;
            }
            if (++work->unk01C < 480.0) {
                break;
            }
            if (lbl_1_bss_40 >= 8) {
                break;
            }
            if (lbl_1_bss_40 >= 3 && 100.0 * M503_FRANDU() > lbl_1_data_4D0[work->unk004]) {
                break;
            }
            work->unk018++;
            work->unk024 = 0;
            work->unk028 = 0;
            work->unk068 = 0;
            lbl_1_bss_40++;
            angle = lbl_1_data_3BC[work->unk06C] + 20.0 * M503_FRANDS();
            speed = (1.0f / 60) * (1000.0 + 400.0 * M503_FRANDU());
            work->unk08C.y = (1.0f / 60) * (2400.0 + 400.0 * M503_FRANDU());
            work->unk08C.x = speed * HuSin(angle);
            work->unk08C.z = speed * HuCos(angle);
            work->unk034 = fn_1_1FD8(0x641, &work->unk038);
            break;
        case 3:
            if (work->unk088 != 0) {
                work->unk0C8.unk000 = 0;
            }
            if (fn_1_961C(obj)) {
                work->unk0A8.unk000 |= 1;
                return 1;
            }
            break;
    }
    return 0;
}

s32 fn_1_82B4(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float x;
    float z;
    float vx;
    float vz;
    float speed;
    float dist;
    OMOBJ *hit;

    if (work->unk018 == 0) {
        if (++work->unk01C < work->unk008 * 10) {
            fn_1_6C5C(obj, 0.0f, 0.0f, 0.1f);
            return 0;
        }
        work->unk018++;
        work->unk098 = work->unk038;
        x = work->unk038.x;
        z = work->unk038.z;
        if (x < 0.0f) {
            if (x > -250.0 && (work->unk008 & 1)) {
                work->unk098.x = 800.0f;
            } else {
                work->unk098.x = -800.0f;
            }
        } else if (x < 250.0 && (work->unk008 & 1)) {
            work->unk098.x = -800.0f;
        } else {
            work->unk098.x = 800.0f;
        }
        if (z < 0.0f) {
            if (z < -380.0) {
                work->unk098.z = -380.0f;
            }
        } else if (z > 300.0) {
            work->unk098.z = 300.0f;
        }
        x = work->unk098.x - work->unk038.x;
        z = work->unk098.z - work->unk038.z;
        work->unk0A4 = HuAtan(x, z);
    }
    vx = vz = 0.0f;
    speed = 6.666667f;
    x = work->unk038.x;
    z = work->unk038.z;
    dist = sqrtf(x * x + z * z);
    hit = fn_1_53D4(&work->unk038, 0.0f, 180.0f, 120.0f);
    if (hit != NULL || dist < 300.0) {
        if (fn_1_1BFC(2) == 0) {
            hit = fn_1_53D4(&work->unk038, work->unk0A4, 45.0f, 120.0f);
            if (hit != NULL) {
                work->unk0A4 += 20.0;
            }
            vx = speed * HuSin(work->unk0A4);
            vz = speed * HuCos(work->unk0A4);
        }
    } else {
        if (x < 0.0f) {
            if (x > -370.0) {
                vx = -speed;
            }
        } else if (x < 370.0) {
            vx = speed;
        }
        if (z < 0.0f) {
            if (z < -380.0) {
                vz = speed;
            }
        } else if (z > 300.0) {
            vz = -speed;
        }
        if (vx != 0.0 || vz != 0.0) {
            work->unk0A4 = HuAtan(vx, vz);
        }
    }
    fn_1_6C5C(obj, vx, vz, 0.1f);
    x = work->unk044.x;
    z = work->unk044.z;
    if (sqrtf(x * x + z * z) < (1.0f / 60) * 10.0) {
        work->unk050 = fn_1_2B7C(work->unk050, 0.0f, 0.08f);
        fn_1_9A04(obj, 0);
    } else {
        fn_1_6DBC(obj, 0.08f);
        fn_1_9A04(obj, 1);
    }
    return 0;
}

s32 fn_1_8AD8(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    OMOBJ *hit;
    float angle;
    float speed;
    float dx;
    float dz;
    HuVecF pos;

    switch (work->unk018) {
        case 0:
            work->unk018++;
            hit = fn_1_53D4(&work->unk038, work->unk050, 180.0f, 200.0f);
            if (hit != NULL) {
                fn_1_5708(hit, &pos, 0);
                dx = work->unk038.x - pos.x;
                dz = work->unk038.z - pos.z;
                angle = HuAtan(dx, dz);
                speed = (1.0f / 60) * (300.0 + 400.0 * M503_FRANDU());
                work->unk08C.y = (1.0f / 60) * (1600.0 + 400.0 * M503_FRANDU());
            } else {
                angle = 360.0 * M503_FRANDU();
                speed = (1.0f / 60) * (200.0 + 200.0 * M503_FRANDU());
                work->unk08C.y = (1.0f / 60) * (1500.0 + 400.0 * M503_FRANDU());
            }
            work->unk08C.x = speed * HuSin(angle);
            work->unk08C.z = speed * HuCos(angle);
        case 1:
            if (fn_1_961C(obj)) {
                return 1;
            }
            break;
    }
    return 0;
}

s32 fn_1_8EA0(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float x;
    float z;
    float dist;
    float angle;

    fn_1_9A04(obj, 1);
    x = work->unk044.x;
    z = work->unk044.z;
    dist = sqrtf(x * x + z * z);
    x = work->unk038.x;
    z = work->unk038.z;
    angle = HuAtan(x, z);
    angle += 80.0f + 5.0f * work->unk008;
    fn_1_6CA4(obj, angle, 1.3333334f, 0.1f);
    fn_1_6DBC(obj, 0.2f);
    return 0;
}

/* 259 insns */
/*
 * Walk toward unk098; settle and return 1 once within 10 units. The steering block
 * is fork I's fn_1_6CA4 + fn_1_6DBC written out by hand: calling the two inline
 * helpers (either spelling) is masked=0 but raw=36 -- CW colours the inlined
 * locals in the opposite order to retail. Named locals declared in the order
 * below reproduce retail's registers (raw=0). J's fn_1_8EA0 has the same block.
 */
s32 fn_1_9210(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    s32 motNo = 0;
    s32 result = 0;
    float dx = work->unk098.x - work->unk038.x;
    float dz = work->unk098.z - work->unk038.z;
    float dist = sqrtf(dx * dx + dz * dz);
    float speed;
    float angle;
    M503_SARU *work3;
    float rotAngle;
    M503_SARU *work2;
    float x;
    float z;

    if (dist < 10.0) {
        work->unk044.x = work->unk044.z = 0.0f;
        work->unk038.x += 0.1 * dx;
        work->unk038.z += 0.1 * dz;
        work->unk050 = fn_1_2B7C(work->unk050, work->unk0A4, 0.1f);
        result = 1;
    } else {
        if (dist < 50.0) {
            motNo = 1;
            speed = lbl_1_data_4E4[work->unk004];
        } else {
            motNo = 2;
            speed = lbl_1_data_4F8[work->unk004];
        }
        angle = 180.0 * (atan2(dx, dz) / M_PI);
        z = speed * cos(M_PI * angle / 180.0);
        x = speed * sin(M_PI * angle / 180.0);
        work2 = obj->data;
        work2->unk044.x += 0.1f * (x - work2->unk044.x);
        work2->unk044.z += 0.1f * (z - work2->unk044.z);
        work3 = obj->data;
        rotAngle = 180.0 * (atan2(work3->unk044.x, work3->unk044.z) / M_PI);
        work3->unk050 = fn_1_2B7C(work3->unk050, rotAngle, 0.1f);
    }
    fn_1_9A04(obj, motNo);
    return result;
}

/* 173 insns */
s32 fn_1_961C(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    float y;
    float angle;

    switch (work->unk024) {
    case 0:
        work->unk024++;
        work->unk028 = 0;
        fn_1_9A04(obj, 0);
    case 1:
        angle = 180.0 * (atan2(work->unk08C.x, work->unk08C.z) / M_PI);
        work->unk050 = fn_1_2B7C(work->unk050, angle, 0.3f);
        if (++work->unk028 < 6.0) {
            break;
        }
        work->unk024++;
        work->unk088 = 1;
        work->unk044 = work->unk08C;
        fn_1_9A04(obj, 3);
        break;
    case 2:
        work->unk044.x *= 0.98;
        work->unk044.y -= 2.0000001043081284; /* retail double: 120.0 * (double)(1.0f / 60.0f) */
        work->unk044.z *= 0.98;
        if (work->unk044.y > 0.0f) {
            break;
        }
        if (work->unk068) {
            y = lbl_1_data_35C[work->unk06C].y;
        } else {
            y = fn_1_BFE8(work->unk038.x, work->unk038.z);
        }
        if (work->unk038.y > y) {
            break;
        }
        work->unk038.y = y;
        work->unk044.x = work->unk044.y = work->unk044.z = 0.0f;
        work->unk088 = 0;
        work->unk024++;
        work->unk028 = 0;
        fn_1_9A04(obj, 0);
        break;
    case 3:
        if (++work->unk028 < 6.0) {
            break;
        }
        return 1;
    }
    return 0;
}

/* 77 insns */
void fn_1_98D0(OMOBJ *obj)
{
    M503_SARU *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    HuVecF pos;

    if (work->unk080) {
        work->unk034 = -1;
        return;
    }
    pos = work->unk038;
    if (work->unk034 != -1) {
        if (HuAudFXStatusGet(work->unk034) == 2) {
            fn_1_210C(work->unk034, &pos);
        } else {
            work->unk034 = -1;
        }
    }
    if (work->unk000 < 4) {
        (void)0; /* retail keeps an empty then-block here: bge body; b end */
    } else {
        pos.y += -8.0;
        if (!work->unk068 && !work->unk088) {
            fn_1_C424(work->unk038.x, work->unk038.z, 15.0f);
        }
    }
    Hu3DModelPosSetV(mdlId, &pos);
    Hu3DModelRotSet(mdlId, 0.0f, work->unk050, 0.0f);
}

/* 63 insns */
void fn_1_9A04(OMOBJ *obj, s32 motNo)
{
    M503_SARU *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    M503_SARUMOT *mot;

    if (work->unk00C != motNo) {
        if (work->unk000 < 4) {
            if (motNo >= 2) {
                return;
            }
            mot = lbl_1_data_2F4;
        } else {
            if (motNo >= 11) {
                return;
            }
            mot = lbl_1_data_304;
        }
        if (work->unk00C < 0) {
            Hu3DMotionSet(mdlId, obj->mtnId[motNo]);
            Hu3DModelAttrSet(mdlId, mot[motNo].unk004);
        } else {
            Hu3DMotionShiftSet(mdlId, obj->mtnId[motNo], 0.0f, 60.0f * mot[motNo].unk000, mot[motNo].unk004);
        }
        work->unk00C = motNo;
    }
}

/* 26 insns */
s32 fn_1_9B00(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];

    if (Hu3DMotionEndCheck(mdlId) && Hu3DMotionShiftIDGet(mdlId) < 0) {
        return 1;
    }
    return 0;
}

/* 22 insns */
s32 fn_1_9B68(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];

    if (Hu3DMotionShiftIDGet(mdlId) < 0) {
        return 1;
    }
    return 0;
}

/* 82 insns */
s32 fn_1_9BC0(OMOBJ *obj, s32 motNo)
{
    if (fn_1_9B00(obj)) {
        fn_1_9A04(obj, motNo);
        return 1;
    }
    return 0;
}

/* 4 insns */
s32 fn_1_9D08(void)
{
    return lbl_1_bss_40;
}

/* 218 insns */
OMOBJ *fn_1_9D18(HuVecF *pos, float rotY, float range, float maxDist)
{
    OMOBJ *best = NULL;
    float bestDist = 100000.0f;
    OMOBJ *obj;
    s32 i;
    M503_SARU *work;
    float dx;
    float dz;
    float dy;
    float value;

    for (i = 0; i < 21; i++) {
        obj = lbl_1_bss_44[i];
        if (obj == NULL) {
            break;
        }
        work = obj->data;
        if (work->unk068 || work->unk080 || !(work->unk0A8.unk000 & 1)) {
            continue;
        }
        dx = work->unk038.x - pos->x;
        dy = work->unk038.y - pos->y;
        dz = work->unk038.z - pos->z;
        if (range < 180.0) {
            value = 180.0 * (atan2(dx, dz) / M_PI);
            value = fmodf(value - rotY, 360.0f);
            if (value < 0.0f) {
                value += 360.0f;
            }
            if (value > range && value < 360.0f - range) {
                continue;
            }
        }
        value = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (value > maxDist) {
            continue;
        }
        if (value < bestDist) {
            bestDist = value;
            best = obj;
        }
    }
    return best;
}

/* 174 insns */
s32 fn_1_A080(OMOBJ *obj, HuVecF *pos, HuVecF *goal)
{
    M503_SARU *work = obj->data;
    float dist;
    float bestDist = 100000.0f;
    s32 goalNo = -1;
    s32 i;
    float dx;
    float dz;

    if (pos != NULL) {
        *pos = work->unk038;
    }
    if (goal != NULL) {
        if (work->unk000 != 8) {
            goalNo = work->unk064;
        } else {
            for (i = 0; i < 4; i++) {
                dx = lbl_1_data_38C[i].x - work->unk038.x;
                dz = lbl_1_data_38C[i].z - work->unk038.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (dist < bestDist) {
                    bestDist = dist;
                    goalNo = i;
                }
            }
            if (goalNo < 0) {
                goalNo = 0;
            }
        }
        *goal = lbl_1_data_38C[goalNo];
    }
    if (work->unk068) {
        return 0;
    }
    if (work->unk080) {
        return 0;
    }
    if (!(work->unk0A8.unk000 & 1)) {
        return 0;
    }
    return 1;
}

/* 12 insns */
void fn_1_A338(s32 goalNo, HuVecF *goal)
{
    *goal = lbl_1_data_38C[goalNo & 3];
}

/* 52 insns */
HU3DMODELID fn_1_A368(OMOBJ *obj, OMOBJ *player)
{
    M503_SARU *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, -1.6f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    work->unk080 = 1;
    work->unk070 = 0;
    work->unk088 = 0;
    work->unk084 = player;
    work->unk0A8.unk000 &= ~1;
    return mdlId;
}

/* 177 insns */
void fn_1_A438(OMOBJ *obj, HuVecF *pos, s32 check)
{
    M503_SARU *work = obj->data;
    s32 kind;
    HU3DMODELID mdlId = obj->mdlId[0];
    s32 i;
    s32 goalNo;
    float dx;
    float dz;
    float dist;

    work->unk038 = *pos;
    Hu3DModelPosSetV(mdlId, &work->unk038);
    work->unk044.x = work->unk044.y = work->unk044.z = 0.0f;
    fn_1_5708(work->unk084, NULL, &work->unk050);
    work->unk080 = 0;
    work->unk0A8.unk000 |= 1;
    if (check) {
        for (i = 0; i < 4; i++) {
            kind = work->unk000;
            goalNo = work->unk064;
            if (kind == 8 || goalNo == i) {
                dx = lbl_1_data_38C[i].x - work->unk038.x;
                dz = lbl_1_data_38C[i].z - work->unk038.z;
                dist = sqrtf(dx * dx + dz * dz);
                if (dist > lbl_1_data_50C[i]) {
                    continue;
                }
                work->unk068 = 1;
                work->unk06C = i;
                work->unk0A8.unk000 &= ~1;
                fn_1_D6D4(fn_1_53B8(work->unk084), lbl_1_data_40C[goalNo]);
                break;
            }
        }
    }
}

