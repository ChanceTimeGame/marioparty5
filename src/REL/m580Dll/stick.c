/*
 * m580Dll stick.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/stick.s.
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
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 360; */
/* 0x3D8 */ /* float lbl_1_rodata_3D8 = 0.0f; */
/* 0x3DC */ /* float lbl_1_rodata_3DC = 60.0f; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 180; */
/* 0x3E8 */ /* double lbl_1_rodata_3E8 = 3.141592653589793; */
/* 0x3F0 */ /* double lbl_1_rodata_3F0 = 0.5; */
/* 0x3F8 */ /* double lbl_1_rodata_3F8 = 3; */
/* 0x400 */ /* double lbl_1_rodata_400 = 210; */
/* 0x408 */ /* double lbl_1_rodata_408 = 0.013333334028720856; */
/* 0x410 */ /* double lbl_1_rodata_410 = 1; */
/* 0x418 */ /* float lbl_1_rodata_418 = 1.0f; */
/* 0x420 */ /* double lbl_1_rodata_420 = 60; */
/* 0x428 */ /* double lbl_1_rodata_428 = 30; */
/* 0x430 */ /* double lbl_1_rodata_430 = 0.01666666753590107; */
/* 0x438 */ /* double lbl_1_rodata_438 = 0; */
/* 0x440 */ /* double lbl_1_rodata_440 = 90; */
/* 0x448 */ /* double lbl_1_rodata_448 = 100; */
/* 0x450 */ /* double lbl_1_rodata_450 = 0.3; */
/* 0x458 */ /* double lbl_1_rodata_458 = 0.2; */
/* 0x460 */ /* double lbl_1_rodata_460 = 4503601774854144; */
/* 0x468 */ /* float lbl_1_rodata_468 = 40.0f; */
/* 0x46C */ /* float lbl_1_rodata_46C = 0.1f; */
/* 0x470 */ /* float lbl_1_rodata_470 = 100.0f; */
/* 0x474 */ /* float lbl_1_rodata_474 = 45.0f; */
/* 0x478 */ /* double lbl_1_rodata_478 = 20; */
/* 0x480 */ /* double lbl_1_rodata_480 = 200; */
/* 0x488 */ /* double lbl_1_rodata_488 = 48; */
/* 0x490 */ /* float lbl_1_rodata_490 = 80.0f; */
/* 0x494 */ /* float lbl_1_rodata_494 = 3000.0f; */
/* 0x498 */ /* double lbl_1_rodata_498 = 10; */
/* 0x4A0 */ /* double lbl_1_rodata_4A0 = 0.000030517578125; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 16.66666753590107; */
/* 0x4B0 */ /* double lbl_1_rodata_4B0 = 5.000000260770321; */
/* 0x4B8 */ /* double lbl_1_rodata_4B8 = 0.0000152587890625; */
/* 0x4C0 */ /* float lbl_1_rodata_4C0 = 0.2f; */
/* 0x4C8 */ /* double lbl_1_rodata_4C8 = 800; */
/* 0x4D0 */ /* float lbl_1_rodata_4D0 = 0.4f; */
/* 0x4D4 */ /* float lbl_1_rodata_4D4 = 0.05f; */
/* 0x4D8 */ /* double lbl_1_rodata_4D8 = -180; */
/* 0x4E0 */ /* float lbl_1_rodata_4E0 = -180.0f; */
/* 0x4E4 */ /* float lbl_1_rodata_4E4 = 180.0f; */
/* 0x4E8 */ /* double lbl_1_rodata_4E8 = 500; */
/* 0x4F0 */ /* float lbl_1_rodata_4F0 = 0.045f; */
/* 0x4F4 */ /* float lbl_1_rodata_4F4 = 0.3f; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = 0.035f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = 0.8f; */
/* 0x500 */ /* float lbl_1_rodata_500 = 0.08f; */
/* 0x508 */ /* double lbl_1_rodata_508 = 50; */
/* 0x510 */ /* float lbl_1_rodata_510 = 0.98f; */
/* 0x518 */ /* double lbl_1_rodata_518 = 120; */
/* 0x520 */ /* double lbl_1_rodata_520 = 600; */
/* 0x528 */ /* double lbl_1_rodata_528 = 0.7; */
/* 0x530 */ /* double lbl_1_rodata_530 = 2; */

/* --- .data --- */
/* 0x310 */ M580_STICKMOT lbl_1_data_310[6] = { { 0x86001F, 0.2f, HU3D_MOTATTR_LOOP }, { -2, 0.0f, 0 } };
/* 0x358 */ M580_STICKMOT lbl_1_data_358[6] = {
    { 0x860016, 0.2f, HU3D_MOTATTR_LOOP },
    { -1, 0.0f, 0 },
    { 0x860017, 0.2f, HU3D_MOTATTR_LOOP },
    { 0x860018, 0.2f, 0 },
    { 0x860019, 0.2f, 0 },
    { 0x86001A, 0.2f, 0 },
};
/* 0x3A0 */ M580_STICKMOT lbl_1_data_3A0[6] = { { 0x860013, 0.2f, HU3D_MOTATTR_LOOP }, { 0x860014, 0.2f, HU3D_MOTATTR_LOOP }, { -2, 0.0f, 0 } };
/* 0x3E8 */ M580_STICKMOT lbl_1_data_3E8[6] = { { 0x86001C, 0.2f, HU3D_MOTATTR_LOOP }, { 0x86001D, 0.2f, HU3D_MOTATTR_LOOP }, { -2, 0.0f, 0 } };
/* 0x430 */ HuVecF lbl_1_data_430 = { 0.0f, 0.0f, 0.0f };
/* 0x43C */ HuVecF lbl_1_data_43C[2] = { { 0.0f, 1000.0f, -3000.0f }, { 0.0f, 100.0f, -70.0f } };
/* 0x454 */ HuVecF lbl_1_data_454 = { -920.0f, 0.0f, 0.0f };
/* 0x460 */ HuVecF lbl_1_data_460 = { 920.0f, 0.0f, 0.0f }; /* dtk printed 920.0f as the string "Df" */
/* 0x46C */ M580_STICKDATA lbl_1_data_46C[6] = {
    { 1, 0, 0, 0, 0x86001E, lbl_1_data_310, lbl_1_data_43C, 0.0f, fn_1_9748 },
    { 1, 0, 1, 0, 0x860015, lbl_1_data_358, &lbl_1_data_454, 90.0f, fn_1_9F44 },
    { 1, 0, 1, 1, 0x860015, lbl_1_data_358, &lbl_1_data_460, 270.0f, fn_1_9F44 },
    { 40, 1, 2, 0, 0x860012, lbl_1_data_3A0, &lbl_1_data_430, 0.0f, fn_1_BAC0 },
    { 5, 0, 3, 0, 0x86001B, lbl_1_data_3E8, &lbl_1_data_430, 0.0f, fn_1_BAC0 },
    { -1, 0, 0, 0, 0, NULL, NULL, 0.0f, NULL },
};
/* 0x544 */ char lbl_1_data_544[50][8] = {
    "kuri1", "kuri2", "kuri3", "kuri4", "kuri5", "kuri6", "kuri7", "kuri8", "kuri9", "kuri10",
    "kuri11", "kuri12", "kuri13", "kuri14", "kuri15", "kuri16", "kuri17", "kuri18", "kuri19", "kuri20",
    "kuri21", "kuri22", "kuri23", "kuri24", "kuri25", "kuri26", "kuri27", "kuri28", "kuri29", "kuri30",
    "kuri31", "kuri32", "kuri33", "kuri34", "kuri35", "kuri36", "kuri37", "kuri38", "kuri39", "kuri40",
    "kuri41", "kuri42", "kuri43", "kuri44", "kuri45", "kuri46", "kuri47", "kuri48", "kuri49", "kuri50"
};
/* 0x6D4 */ char lbl_1_data_6D4[6][8] = { "kame1", "kame2", "kame3", "kame4", "kame5", "kame6" };
/* 0x704 */ char lbl_1_data_704[] = "itemhook_sao";
/* 0x714 jumptable_1_data_714: fn_1_9970's switch */
/* 0x738..0x74C are defined below fn_1_9970, so its jumptable (0x714) is emitted first */
/* 0x758 jumptable_1_data_758: fn_1_BD70's switch */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x238 */ OMOBJ *lbl_1_bss_238[2]; /* [0] the stick manager; dtk size 8, [1] unused */
/* 0x1B8 */ s32 lbl_1_bss_1B8[32]; /* model cache: data numbers */
/* 0x138 */ s32 lbl_1_bss_138[32]; /* motion cache: data numbers */
/* 0xF8 */ HU3DMODELID lbl_1_bss_F8[32]; /* model cache: ids */
/* 0xB8 */ HU3DMOTID lbl_1_bss_B8[32]; /* motion cache: ids */

#define M_PI 3.141592653589793

#define M580_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M580_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

/* MSL's sqrtf algorithm with 0.5/3.0 pooled as ordinary literals (0x3F0/0x3F8), not
 * math.h's _half/_three statics (m504 player.c precedent). The host uses the real sqrtf. */
static inline float StickSqrtF(float x)
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

static inline float StickAngleMod(float angle)
{
    return fmod(angle, 360.0);
}

/* --- functions (reference order) --- */
/* 63 insns. Manager object, model caches, audience model, then one group per table row. */
void fn_1_8A64(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_STICKMAN *work;
    M580_STICKDATA *data;

    obj = omAddObjEx(objman, 0x3C, 0, 0, -1, fn_1_8B64);
    lbl_1_bss_238[0] = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_STICKMAN), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_STICKMAN));
    fn_1_8C08();
    work->unk008 = Hu3DModelCreate(HuDataSelHeapReadNum(0x860007, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(work->unk008, 5);
    for (data = lbl_1_data_46C; data->unk000 != -1; data++) {
        fn_1_8E80(objman, data);
    }
}

/* 1 insns */
void fn_1_8B60(void)
{
}

/* 13 insns */
void fn_1_8B64(OMOBJ *obj)
{
    M580_STICKMAN *work = obj->data;

    work->unk000 = 0;
    work->unk004 = 0;
    obj->objFunc = fn_1_8B98;
}

/* 28 insns. Latch fn_1_D544() once it is set. */
void fn_1_8B98(OMOBJ *obj)
{
    M580_STICKMAN *work = obj->data;

    switch (work->unk000) {
        case 0:
            if (fn_1_D544()) {
                break;
            }
            work->unk000++;
        case 1:
            work->unk004 = fn_1_D544();
            break;
    }
}

/* 39 insns. Clear the model and motion caches (m514 object.c fn_1_435C). */
void fn_1_8C08(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_1B8[i] = -1;
        lbl_1_bss_F8[i] = -1;
    }
    for (i = 0; i < 32; i++) {
        lbl_1_bss_138[i] = -1;
        lbl_1_bss_B8[i] = -1;
    }
}

/* 59 insns. Model by data number: link a cached one or create and cache it (m514 fn_1_43F8). */
HU3DMODELID fn_1_8CA4(s32 dataNum)
{
    s32 i;
    s32 cached;
    HU3DMODELID mdlId;

    for (i = 0; i < 32; i++) {
        cached = lbl_1_bss_1B8[i];
        if (cached == -1) {
            break;
        }
        if (dataNum == cached) {
            mdlId = lbl_1_bss_F8[i];
            return Hu3DModelLink(mdlId);
        }
    }
    if (i < 32) {
        mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_1B8[i] = dataNum;
        lbl_1_bss_F8[i] = mdlId;
        return mdlId;
    }
    return -1;
}

/* 60 insns. Motion by data number: return a cached one or load and cache it (m514 fn_1_44E4). */
HU3DMOTID fn_1_8D90(HU3DMODELID mdlId, s32 dataNum)
{
    s32 i;
    s32 cached;
    HU3DMOTID motId;

    for (i = 0; i < 32; i++) {
        cached = lbl_1_bss_138[i];
        if (cached == -1) {
            break;
        }
        if (dataNum == cached) {
            return lbl_1_bss_B8[i];
        }
    }
    if (i < 32) {
        motId = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_138[i] = dataNum;
        lbl_1_bss_B8[i] = motId;
        return motId;
    }
    return -1;
}

/* 197 insns. One object per count of a table row. */
void fn_1_8E80(OMOBJMAN *objman, M580_STICKDATA *data)
{
    OMOBJ *obj;
    M580_STICK *work;
    s32 j;
    M580_STICKMOT *mot;
    HU3DMODELID mdlId;
    s32 i;
    s32 dataNum;

    for (i = 0; i < data->unk000; i++) {
        obj = omAddObjEx(objman, 0x3C, 6, 6, 0, data->unk020);
        work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_STICK), HU_MEMNUM_OVL);
        obj->data = work;
        memset(work, 0, sizeof(M580_STICK));
        obj->stat |= OM_STAT_MODELPAUSE;
        work->unk000 = data;
        work->unk004 = data->unk00C + i;
        work->unk018 = -1;
        for (j = 0; j < 6; j++) {
            obj->mdlId[j] = -1;
        }
        for (j = 0; j < 6; j++) {
            obj->mtnId[j] = -1;
        }
        if (data->unk004) {
            mdlId = fn_1_8CA4(data->unk010);
        } else {
            mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(data->unk010, HU_MEMNUM_OVL, HEAP_MODEL));
        }
        obj->mdlId[0] = mdlId;
        mot = data->unk014;
        for (j = 0; j < 6; j++, mot++) {
            dataNum = mot->unk000;
            if (dataNum == -2) {
                break;
            }
            if (dataNum != -1) {
                obj->mtnId[j] = fn_1_8D90(mdlId, dataNum);
            }
        }
        work->unk028 = *data->unk018;
        work->unk040.y = data->unk01C;
        Hu3DModelLayerSet(mdlId, 5);
    }
}

/* 86 insns. Push position and rotation to the model and its shadow/hook. */
void fn_1_9194(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    work->unk040.y = StickAngleMod(work->unk040.y);
    work->unk040.x = work->unk040.z = 0.0f;
    Hu3DModelPosSetV(mdlId, &work->unk028);
    Hu3DModelRotSetV(mdlId, &work->unk040);
    mdlId = obj->mdlId[2];
    if (mdlId == -1) {
        mdlId = obj->mdlId[1];
    }
    if (mdlId != -1) {
        Hu3DModelPosSet(mdlId, work->unk028.x, -work->unk028.y, work->unk028.z);
        Hu3DModelRotSetV(mdlId, &work->unk040);
        work->unk088.unk028 = work->unk028;
    }
    if (work->unk020 && fn_1_943C(obj)) {
        work->unk020 = 0;
    }
    work->unk01C++;
}

/* 84 insns. Switch to motion motNo (< 6) on the model and its mirror. */
void fn_1_92EC(OMOBJ *obj, s32 motNo)
{
    M580_STICK *work = obj->data;
    M580_STICKMOT *mot;
    HU3DMODELID mdlId;
    HU3DMOTID motId;

    if (work->unk018 != motNo && motNo < 6) {
        motId = obj->mtnId[motNo];
        work->unk01C = 0;
        if (motId != -1) {
            mot = &work->unk000->unk014[motNo];
            mdlId = obj->mdlId[0];
            if (work->unk018 < 0) {
                Hu3DMotionSet(mdlId, motId);
                Hu3DModelAttrSet(mdlId, mot->unk008);
                mdlId = obj->mdlId[1];
                if (mdlId != -1) {
                    Hu3DMotionSet(mdlId, motId);
                    Hu3DModelAttrSet(mdlId, mot->unk008);
                }
            } else {
                Hu3DMotionShiftSet(mdlId, motId, 0.0f, 60.0f * mot->unk004, mot->unk008);
                mdlId = obj->mdlId[1];
                if (mdlId != -1) {
                    Hu3DMotionShiftSet(mdlId, motId, 0.0f, 60.0f * mot->unk004, mot->unk008);
                }
            }
            work->unk018 = motNo;
        }
    }
}

/* 26 insns. Nonzero once the motion has ended and no blend is pending (m503 saru fn_1_9B00). */
s32 fn_1_943C(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];

    if (Hu3DMotionEndCheck(mdlId) && Hu3DMotionShiftIDGet(mdlId) < 0) {
        return 1;
    }
    return 0;
}

/* 33 insns. Position and rotation Y of a named object of the audience model. */
void fn_1_94A4(char *name, HuVecF *pos, float *rotY)
{
    OMOBJ *obj = lbl_1_bss_238[0];
    M580_STICKMAN *man = obj->data;
    HSFOBJECT *hsfObj = Hu3DModelObjPtrGet(man->unk008, name);

    if (hsfObj != NULL) {
        pos->x = hsfObj->mesh.base.pos.x;
        pos->y = hsfObj->mesh.base.pos.y;
        pos->z = hsfObj->mesh.base.pos.z;
        *rotY = hsfObj->mesh.base.rot.y;
    }
}

/* 42 insns. Yaw from the object to pos, degrees. */
float fn_1_9528(OMOBJ *obj, HuVecF *pos)
{
    M580_STICK *work = obj->data;
    float dx = pos->x - work->unk028.x;
    float dz = pos->z - work->unk028.z;

    return 180.0 * (atan2(dx, dz) / M_PI);
}

/* 94 insns. XZ distance from the object to pos. */
float fn_1_95D0(OMOBJ *obj, HuVecF *pos)
{
    M580_STICK *work = obj->data;
    float dx = pos->x - work->unk028.x;
    float dz = pos->z - work->unk028.z;

    return StickSqrtF(dx * dx + dz * dz);
}

/* 138 insns. Hook arm init. */
void fn_1_9748(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    HU3DMODELID mdlId;

    mdlId = fn_1_8CA4(0x860020);
    obj->mdlId[2] = mdlId;
    Hu3DModelLayerSet(mdlId, 1);
    fn_1_92EC(obj, 0);
    obj->objFunc = fn_1_9970;
}

/* 373 insns. Hook arm: lower, hand the puck in, raise; swing the arm. */
void fn_1_9970(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    HU3DMODELID hookMdlId = obj->mdlId[2];
    s32 mode;
    float t;
    HuVecF pos;
    HuVecF dir;

    switch (work->unk008) {
        case 0:
            work->unk008++;
            work->unk010 = 0;
            work->unk050 = 0.0f;
            Hu3DModelHookSet(mdlId, lbl_1_data_704, fn_1_D56C());
        case 1:
            if (++work->unk010 < 210.0) {
                break;
            }
            work->unk008++;
        case 2:
            if ((work->unk050 += 0.8 * (1.0f / 60)) < 1.0) {
                break;
            }
            work->unk050 = 1.0f;
            work->unk008++;
            work->unk010 = 0;
        case 3:
            if (++work->unk010 < 60.0) {
                break;
            }
            work->unk008++;
            Hu3DModelHookObjReset(mdlId, lbl_1_data_704);
            fn_1_D654();
            HuAudFXPlay(0x960);
        case 4:
            if (++work->unk010 < 30.0) {
                break;
            }
            work->unk008++;
        case 5:
            mode = MgSeqModeGet();
            if (mode != 5 && mode != 6) {
                break;
            }
            work->unk008++;
        case 6:
            if ((work->unk050 -= 1.0 * (1.0f / 60)) > 0.0) {
                break;
            }
            work->unk050 = 0.0f;
            work->unk008++;
        case 7:
            if (!fn_1_D544()) {
                break;
            }
            work->unk008++;
            work->unk010 = 0;
        case 8:
            if (fn_1_1D04() < 2) {
                break;
            }
            if (++work->unk010 < 60.0) {
                break;
            }
            work->unk008 = 2;
            Hu3DModelHookSet(mdlId, lbl_1_data_704, fn_1_D56C());
            break;
    }
    t = work->unk050;
    t = sin(M_PI * (90.0 * t) / 180.0);
    if (0.0 == t) {
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(hookMdlId, HU3D_ATTR_DISPOFF);
    } else {
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(hookMdlId, HU3D_ATTR_DISPOFF);
    }
    PSVECSubtract(&work->unk000->unk018[1], &work->unk000->unk018[0], &dir);
    PSVECScale(&dir, &dir, t);
    PSVECAdd(&work->unk000->unk018[0], &dir, &work->unk028);
    work->unk04C = StickAngleMod(1.0 + work->unk04C);
    if (work->unk04C < 0.0) {
        work->unk04C += 360.0;
    }
    pos.x = work->unk028.x + 100.0 * (0.3 * sin(M_PI * work->unk04C / 180.0));
    pos.y = work->unk028.y + 100.0 * (0.2 * sin(M_PI * work->unk04C / 180.0));
    pos.z = work->unk028.z + 100.0 * (0.2 * cos(M_PI * work->unk04C / 180.0));
    Hu3DModelPosSetV(mdlId, &pos);
    Hu3DModelRotSetV(mdlId, &work->unk040);
    Hu3DModelPosSet(hookMdlId, pos.x, -pos.y, pos.z);
    Hu3DModelRotSetV(hookMdlId, &work->unk040);
    Hu3DModelObjPosGet(mdlId, lbl_1_data_704, &pos);
    fn_1_D60C(&pos);
}

/* --- .data after jumptable_1_data_714 --- */
/* 0x738 */ HuVecF lbl_1_data_738 = { 0.0f, -10.0f, 0.0f };
/* 0x744 */ s32 lbl_1_data_744[2] = { 0x86000B, 0x86000C };
/* 0x74C */ char lbl_1_data_74C[] = "itemhook_L";

/* 199 insns. Goalie stick init: hook, effect, collision entry, idle motion. */
void fn_1_9F44(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    s32 idx = work->unk004;
    HU3DMODELID mdlId = obj->mdlId[0];
    M580_EFFECTSHADOW *eff;
    M580_COLLACTOR *coll;
    HU3DMODELID hookMdlId;

    obj->work[0] = idx + 4;
    work->unk04C = work->unk000->unk01C;
    work->unk054 = 0;
    hookMdlId = fn_1_8CA4(lbl_1_data_744[idx]);
    Hu3DModelHookSet(mdlId, lbl_1_data_74C, hookMdlId);
    eff = &work->unk068;
    eff->unk000 = 1;
    eff->unk004 = 13;
    eff->unk008 = idx;
    eff->unk00C = &work->unk028;
    eff->unk010 = &lbl_1_data_738;
    eff->unk014 = &work->unk040.y;
    fn_1_ED34(eff);
    coll = &work->unk088;
    coll->unk000 = 8;
    coll->unk004 = 10;
    coll->unk008 = 2;
    coll->unk00C = idx;
    coll->unk010 = 0;
    coll->unk014 = obj;
    coll->unk018 = (void (*)(void *))fn_1_9194;
    coll->unk01C = NULL;
    coll->unk020 = &work->unk028;
    coll->unk024 = &work->unk034;
    coll->unk028 = work->unk028;
    coll->unk034 = 40.0f;
    coll->unk038 = 0.1f;
    fn_1_11DC4(coll);
    fn_1_92EC(obj, 0);
    obj->objFunc = fn_1_A260;
}

/* 1560 insns. Goalie stick main: guard the goal, catch the puck, shoot it at a player. */
void fn_1_A260(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    HuVecF *basePos = work->unk000->unk018;
    float radius = 100.0f;
    OMOBJ *owner;
    OMOBJ *player;
    float dist;
    float angle;
    float gain;
    float rate;
    float vx;
    float vz;
    HuVecF puckPos;
    HuVecF target;
    HuVecF puckVel;

    owner = fn_1_D30C(&puckPos, &puckVel);
    dist = fn_1_95D0(obj, &puckPos);
    switch (work->unk008) {
        case 0:
            if (fn_1_89A8(work->unk004 + 4, &work->unk028, &work->unk040.y)) {
                return;
            }
            fn_1_92EC(obj, 0);
            work->unk088.unk000 |= 1;
            work->unk008++;
        case 1:
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk008++;
            work->unk010 = work->unk014 = 0;
        case 2:
            if (MgSeqModeGet() == 6) {
                work->unk008++;
                break;
            }
            if (work->unk014) {
                work->unk014--;
            }
            if (work->unk014 == 0 && owner != obj) {
                if (fn_1_D054(&work->unk028, work->unk040.y, 45.0f, 20.0 + radius)) {
                    owner = fn_1_D390(NULL, 1.0f, NULL, obj);
                    if (owner == obj) {
                        work->unk010 = 0;
                        fn_1_92EC(obj, 3);
                        work->unk020 = 1;
                    }
                }
                if (owner != obj) {
                    if ((work->unk004 == 0 && puckPos.x < work->unk028.x - 200.0)
                        || (work->unk004 == 1 && puckPos.x > 200.0 + work->unk028.x)) {
                        work->unk04C = work->unk000->unk01C;
                    } else {
                        work->unk04C = fn_1_9528(obj, &puckPos);
                    }
                }
            }
            if (owner == obj) {
                angle = work->unk040.y - 30.0;
                puckPos.x = work->unk028.x + radius * sin(M_PI * angle / 180.0);
                puckPos.y = work->unk028.y;
                puckPos.z = work->unk028.z + radius * cos(M_PI * angle / 180.0);
                puckVel.x = puckVel.y = puckVel.z = 0.0f;
                angle = work->unk040.y;
                if (work->unk018 != 4) {
                    if (++work->unk010 > 48.0) {
                        fn_1_92EC(obj, 4);
                        work->unk020 = 1;
                        player = fn_1_7E48(work->unk004, NULL, &work->unk028, work->unk000->unk01C, 80.0f, 3000.0f, (frand() & 1) == 0);
                        if (player != NULL) {
                            fn_1_8194(player, &target, NULL);
                            work->unk04C = fn_1_9528(obj, &target);
                        } else {
                            work->unk04C += 10.0 * M580_FRANDS();
                        }
                    } else {
                        work->unk04C = work->unk000->unk01C;
                    }
                } else if (work->unk01C == 13) {
                    work->unk014 = 18;
                    gain = 1000.0 * (1.0f / 60) + 300.0 * (1.0f / 60) * M580_FRANDU();
                    puckVel.x = gain * sin(M_PI * angle / 180.0);
                    puckVel.z = gain * cos(M_PI * angle / 180.0);
                    work->unk020 = 1;
                    owner = NULL;
                }
                owner = fn_1_D390(&puckPos, 0.2f, &puckVel, owner);
            } else {
                target = *basePos;
                if (dist > 800.0) {
                    target.z += 0.3 * puckPos.z;
                    gain = 0.4f;
                    rate = 0.05f;
                } else {
                    target.z = puckPos.z;
                    if (target.z < -180.0) {
                        target.z = -180.0f;
                    }
                    if (target.z > 180.0) {
                        target.z = 180.0f;
                    }
                    if (dist > 500.0) {
                        gain = 0.4f;
                        rate = 0.045f;
                    } else {
                        gain = 0.3f;
                        rate = 0.035f;
                    }
                }
                if (!work->unk020) {
                    if (fn_1_95D0(obj, &target) > 30.0) {
                        vx = target.x - work->unk028.x;
                        vz = target.z - work->unk028.z;
                        angle = 180.0 * (atan2(vx, vz) / M_PI);
                        vx = (1.0f / 60) * (100.0 * (10.0 * (gain * sin(M_PI * angle / 180.0))));
                        vz = (1.0f / 60) * (100.0 * (10.0 * (gain * cos(M_PI * angle / 180.0))));
                        fn_1_92EC(obj, 2);
                        work->unk054 = 48;
                    } else {
                        vx = vz = 0.0f;
                        if (--work->unk054 < 0) {
                            fn_1_92EC(obj, 0);
                        }
                    }
                } else {
                    vx = vz = 0.0f;
                    work->unk054 = 0;
                }
                work->unk034.x += rate * (vx - work->unk034.x);
                work->unk034.z += rate * (vz - work->unk034.z);
            }
            break;
        case 3:
            if (MgSeqModeGet() == 6) {
                break;
            }
            target = *basePos;
            gain = 0.8f;
            rate = 0.08f;
            if (fn_1_95D0(obj, &target) > 50.0) {
                vx = target.x - work->unk028.x;
                vz = target.z - work->unk028.z;
                angle = work->unk04C = 180.0 * (atan2(vx, vz) / M_PI);
                vx = (1.0f / 60) * (100.0 * (10.0 * (gain * sin(M_PI * angle / 180.0))));
                vz = (1.0f / 60) * (100.0 * (10.0 * (gain * cos(M_PI * angle / 180.0))));
                fn_1_92EC(obj, 2);
                work->unk054 = 48;
            } else {
                vx = vz = 0.0f;
                work->unk04C = work->unk000->unk01C;
                if (--work->unk054 < 0) {
                    fn_1_92EC(obj, 0);
                }
            }
            work->unk034.x += rate * (vx - work->unk034.x);
            work->unk034.z += rate * (vz - work->unk034.z);
            if (MgSeqModeGet() == 8) {
                work->unk008++;
                work->unk04C = 0.0f;
                if (fn_1_1D58(work->unk004) == 1) {
                    fn_1_92EC(obj, 5);
                }
            }
            break;
        case 4:
            break;
    }
    work->unk040.y = fn_1_2634(work->unk040.y, work->unk04C, 0.05f);
    PSVECScale(&work->unk034, &work->unk034, 0.98f);
    PSVECAdd(&work->unk028, &work->unk034, &work->unk028);
}

/* 172 insns. Audience member init: place on the stand's named object, random phase. */
void fn_1_BAC0(OMOBJ *obj)
{
    M580_STICK *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    switch (work->unk000->unk008) {
        case 2:
            fn_1_94A4(lbl_1_data_544[work->unk004], &work->unk028, &work->unk040.y);
            break;
        case 3:
            fn_1_94A4(lbl_1_data_6D4[work->unk004], &work->unk028, &work->unk040.y);
            break;
    }
    fn_1_92EC(obj, 1);
    Hu3DMotionTimeSet(mdlId, M580_FRANDU() * (Hu3DMotionMaxTimeGet(mdlId) - 1.0));
    obj->objFunc = fn_1_BD70;
}

/* 738 insns. Audience member main: idle, cheer on a goal, wave at the end. */
void fn_1_BD70(OMOBJ *obj)
{
    M580_STICKMAN *man = lbl_1_bss_238[0]->data;
    M580_STICK *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];
    float speed;

    switch (work->unk008) {
        case 0:
            work->unk008++;
            work->unk010 = 120.0 + (s32)(180.0 * M580_FRANDU());
        case 1:
            if (--work->unk010 > 0) {
                break;
            }
            work->unk008++;
            work->unk010 = 60.0 + (s32)(600.0 * M580_FRANDU());
            fn_1_92EC(obj, 0);
        case 2:
            if (--work->unk010 <= 0) {
                work->unk008++;
                work->unk010 = 1;
                break;
            }
            if (MgSeqModeGet() == 6) {
                work->unk008++;
                work->unk010 = (work->unk004 & 7) * 5;
                work->unk024 = 1;
            }
            if (!man->unk004) {
                break;
            }
            work->unk008++;
            work->unk010 = (work->unk004 & 7) * 5;
        case 3:
            if (--work->unk010 > 0) {
                break;
            }
            fn_1_92EC(obj, 1);
            work->unk008++;
            work->unk010 = 120;
        case 4:
            if (work->unk024) {
                break;
            }
            if (--work->unk010 > 0) {
                break;
            }
            work->unk008++;
            if (!man->unk004) {
                work->unk008 = 2;
                work->unk010 = 60.0 + (s32)(600.0 * M580_FRANDU());
                fn_1_92EC(obj, 0);
                break;
            }
        case 5:
            if (man->unk004) {
                break;
            }
            work->unk008++;
            work->unk010 = 30.0 + (s32)(120.0 * M580_FRANDU());
        case 6:
            if (work->unk024) {
                break;
            }
            if (--work->unk010 > 0) {
                break;
            }
            work->unk008 = 2;
            work->unk010 = 120.0 + (s32)(600.0 * M580_FRANDU());
            fn_1_92EC(obj, 0);
            break;
    }
    if (work->unk018 == 0) {
        speed = 1.0f;
    } else {
        switch (work->unk000->unk008) {
            case 2:
                speed = man->unk004 ? 1.0 : 0.7;
                break;
            case 3:
                speed = man->unk004 ? 2.0 : 1.0;
                break;
            default:
                speed = 1.0f;
                break;
        }
    }
    Hu3DMotionSpeedSet(mdlId, speed);
    fn_1_9194(obj);
}
