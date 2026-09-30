/*
 * m514dll object.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/object.s.
 */

#include "REL/m514Dll.h"

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
/* 0x208 */ /* float lbl_1_rodata_208 = 0.0f; */
/* 0x20C */ /* float lbl_1_rodata_20C = 60.0f; */
/* 0x210 */ /* double lbl_1_rodata_210 = 50; */
/* 0x218 */ /* double lbl_1_rodata_218 = 90; */
/* 0x220 */ /* double lbl_1_rodata_220 = 6; */
/* 0x228 */ /* double lbl_1_rodata_228 = -1000; */
/* 0x230 */ /* double lbl_1_rodata_230 = 4503601774854144; */

/* --- .data --- */
/* 0x300 */ M514_OBJMOT lbl_1_data_300[2] = { { 0x480007, 0.2f, HU3D_MOTATTR_LOOP }, { 0x480008, 0.2f, HU3D_MOTATTR_LOOP } };
/* 0x318 */ M514_OBJMOT lbl_1_data_318[2] = { { 0x48000A, 0.2f, HU3D_MOTATTR_LOOP }, { 0x48000B, 0.2f, HU3D_MOTATTR_LOOP } };
/* 0x330 */ M514_OBJMOT lbl_1_data_330[2] = { { 0x48000D, 0.2f, HU3D_MOTATTR_LOOP }, { 0x48000E, 0.2f, HU3D_MOTATTR_LOOP } };
/* 0x348 */ M514_OBJMOT lbl_1_data_348[2] = { { 0x480010, 0.2f, HU3D_MOTATTR_LOOP }, { 0x480011, 0.2f, HU3D_MOTATTR_LOOP } };
/* 0x360 */ M514_OBJMOT lbl_1_data_360[2] = { { 0x480014, 0.2f, HU3D_MOTATTR_LOOP }, { 0x480015, 0.2f, HU3D_MOTATTR_LOOP } };
/* 0x378 */ HuVecF lbl_1_data_378 = { -1500.0f, 70.0f, -400.0f };
/* 0x384 */ HuVecF lbl_1_data_384 = { -500.0f, 70.0f, -400.0f };
/* 0x390 */ HuVecF lbl_1_data_390 = { 500.0f, 70.0f, -400.0f };
/* 0x39C */ HuVecF lbl_1_data_39C = { 1500.0f, 70.0f, -400.0f };
/* 0x3A8 */ HuVecF lbl_1_data_3A8 = { 2500.0f, 70.0f, -400.0f };
/* 0x3B4 */ M514_OBJDATA lbl_1_data_3B4[6] = {
    { 0, 0, 0x480006, lbl_1_data_300, &lbl_1_data_378, 0.0f, fn_1_4A4C },
    { 1, 1, 0x480009, lbl_1_data_318, &lbl_1_data_384, 0.0f, fn_1_4A4C },
    { 2, 2, 0x48000C, lbl_1_data_330, &lbl_1_data_390, 0.0f, fn_1_4A4C },
    { 3, 3, 0x48000F, lbl_1_data_348, &lbl_1_data_39C, 0.0f, fn_1_4A4C },
    { 4, 4, 0x480013, lbl_1_data_360, &lbl_1_data_3A8, 0.0f, fn_1_4A4C },
    { -1, 0, 0, NULL, NULL, 0.0f, NULL },
};
/* 0x45C */ s32 lbl_1_data_45C[5] = { 0x00480018, 0x0048001B, 0x0048001C, 0x0048001D, 0x0048001E };
/* 0x470 "obj12" is a string literal in fn_1_4A4C; 0x478 is fn_1_4C40's switch jumptable. */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x20C gap_05_0000020C_bss (0x4) -- dtk filler */
/* 0x208 */ OMOBJ *lbl_1_bss_208;
/* 0x188 */ s32 lbl_1_bss_188[32];
/* 0x108 */ s32 lbl_1_bss_108[32];
/* 0xC8 */ HU3DMODELID lbl_1_bss_C8[32];
/* 0x88 */ HU3DMOTID lbl_1_bss_88[32];

/* --- functions (reference order) --- */

/* 53 insns. Controller object, the model caches, then one object per table row. */
void fn_1_4270(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M514_OBJMAN *work;
    M514_OBJDATA *data;

    obj = omAddObjEx(objman, 0x32, 0, 0, -1, fn_1_4348);
    lbl_1_bss_208 = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_OBJMAN), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M514_OBJMAN));
    fn_1_435C();
    for (data = lbl_1_data_3B4; data->unk000 != -1; data++) {
        fn_1_45D4(objman, data);
    }
}

/* 1 insns. Empty. */
void fn_1_4344(void)
{
}

/* 4 insns. Controller object init. */
void fn_1_4348(OMOBJ *obj)
{
    obj->objFunc = fn_1_4358;
}

/* 1 insns. Empty. */
void fn_1_4358(OMOBJ *obj)
{
}

/* 39 insns. Clear the model and motion caches. */
void fn_1_435C(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        lbl_1_bss_188[i] = -1;
        lbl_1_bss_C8[i] = -1;
    }
    for (i = 0; i < 32; i++) {
        lbl_1_bss_108[i] = -1;
        lbl_1_bss_88[i] = -1;
    }
}

/* 59 insns. Model by data number: link a cached one or create and cache it. */
HU3DMODELID fn_1_43F8(s32 dataNum)
{
    s32 i;
    s32 cached;
    HU3DMODELID mdlId;

    for (i = 0; i < 32; i++) {
        cached = lbl_1_bss_188[i];
        if (cached == -1) {
            break;
        }
        if (dataNum == cached) {
            mdlId = lbl_1_bss_C8[i];
            return Hu3DModelLink(mdlId);
        }
    }
    if (i < 32) {
        mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_188[i] = dataNum;
        lbl_1_bss_C8[i] = mdlId;
        return mdlId;
    }
    return -1;
}

/* 60 insns. Motion by data number: return a cached one or load and cache it. */
HU3DMOTID fn_1_44E4(HU3DMODELID mdlId, s32 dataNum)
{
    s32 i;
    s32 cached;
    HU3DMOTID motId;

    for (i = 0; i < 32; i++) {
        cached = lbl_1_bss_108[i];
        if (cached == -1) {
            break;
        }
        if (dataNum == cached) {
            return lbl_1_bss_88[i];
        }
    }
    if (i < 32) {
        motId = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_108[i] = dataNum;
        lbl_1_bss_88[i] = motId;
        return motId;
    }
    return -1;
}

/* 183 insns. One scenery object from a table row. */
void fn_1_45D4(OMOBJMAN *objman, M514_OBJDATA *data)
{
    OMOBJ *obj;
    M514_OBJECT *work;
    s32 i;
    HU3DMODELID mdlId;
    M514_OBJMOT *mot;
    s32 dataNum;

    obj = omAddObjEx(objman, 0x32, 3, 2, 0, data->unk018);
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_OBJECT), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M514_OBJECT));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = data;
    work->unk010 = -1;
    work->unk014 = -1;
    work->unk018 = -1;
    for (i = 0; i < 3; i++) {
        obj->mdlId[i] = -1;
    }
    for (i = 0; i < 2; i++) {
        obj->mtnId[i] = -1;
    }
    mdlId = fn_1_43F8(data->unk008);
    obj->mdlId[0] = mdlId;
    mot = data->unk00C;
    for (i = 0; i < 2; i++, mot++) {
        dataNum = mot->unk000;
        if (dataNum == -2) {
            break;
        }
        if (dataNum != -1) {
            obj->mtnId[i] = fn_1_44E4(mdlId, dataNum);
        }
    }
    work->unk01C = *data->unk010;
    work->unk034.y = data->unk014;
    Hu3DModelLayerSet(mdlId, 4);
    fn_1_48B0(obj);
}

/* 23 insns. Push the work position and rotation to the model. */
void fn_1_48B0(OMOBJ *obj)
{
    M514_OBJECT *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    Hu3DModelPosSetV(mdlId, &work->unk01C);
    Hu3DModelRotSetV(mdlId, &work->unk034);
}

/* 54 insns. Switch to motion motNo (0 or 1), blending unless none was set. */
void fn_1_490C(OMOBJ *obj, s32 motNo)
{
    M514_OBJECT *work = obj->data;
    M514_OBJMOT *mot;
    HU3DMODELID mdlId;
    HU3DMOTID motId;

    if (work->unk010 != motNo && motNo < 2) {
        motId = obj->mtnId[motNo];
        if (motId != -1) {
            mot = &work->unk000->unk00C[motNo];
            mdlId = obj->mdlId[0];
            if (work->unk010 < 0) {
                Hu3DMotionSet(mdlId, motId);
                Hu3DModelAttrSet(mdlId, mot->unk008);
            } else {
                Hu3DMotionShiftSet(mdlId, motId, 0.0f, 60.0f * mot->unk004, mot->unk008);
            }
            work->unk010 = motNo;
        }
    }
}

/* 26 insns. Nonzero once the motion has ended and no blend is pending. */
s32 fn_1_49E4(OMOBJ *obj)
{
    HU3DMODELID mdlId = obj->mdlId[0];

    if (Hu3DMotionEndCheck(mdlId) && Hu3DMotionShiftIDGet(mdlId) < 0) {
        return 1;
    }
    return 0;
}

/* 125 insns. Row object init: shadow, idle motion, the base model and extras. */
void fn_1_4A4C(OMOBJ *obj)
{
    M514_OBJECT *work = obj->data;
    HU3DMODELID mdlId;
    HSFOBJECT *hsfObj;

    mdlId = obj->mdlId[0];
    Hu3DModelShadowSet(mdlId);
    fn_1_490C(obj, 0);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_45C[work->unk000->unk004], HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[1] = mdlId;
    Hu3DModelPosSet(mdlId, work->unk01C.x, work->unk01C.y, work->unk01C.z - 50.0);
    Hu3DModelLayerSet(mdlId, 4);
    if (work->unk000->unk000 == 3) {
        mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x480012, HU_MEMNUM_OVL, HEAP_MODEL));
        obj->mdlId[2] = mdlId;
        Hu3DModelPosSet(mdlId, work->unk01C.x, work->unk01C.y, work->unk01C.z);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(mdlId, 4);
    }
    if (work->unk000->unk000 == 4) {
        mdlId = obj->mdlId[0];
        hsfObj = Hu3DModelObjPtrGet(mdlId, "obj12");
        if (hsfObj != NULL) {
            hsfObj->flags |= 0x400;
        }
    }
    obj->objFunc = fn_1_4C40;
}

/* 297 insns. Row object main: wait for play, idle, react when passed, reset. */
void fn_1_4C40(OMOBJ *obj)
{
    M514_OBJMAN *man = lbl_1_bss_208->data;
    M514_OBJECT *work = obj->data;
    HU3DMODELID mdlId;

    switch (work->unk004) {
        case 0:
            work->unk004++;
        case 1:
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk004++;
        case 2:
            work->unk004++;
            work->unk044 = fn_1_1814();
            fn_1_490C(obj, 0);
        case 3:
            if (fn_1_95F4(fn_1_1814()) < work->unk01C.x) {
                break;
            }
            work->unk004++;
            work->unk008 = 0;
            fn_1_490C(obj, 1);
            switch (work->unk000->unk000) {
                case 0:
                    work->unk014 = HuAudFXPlay(0x2CF);
                    break;
                case 1:
                    work->unk014 = HuAudFXPlay(0x2C4);
                    break;
                case 2:
                    work->unk014 = HuAudFXPlay(0x2D4);
                    break;
                case 3:
                    work->unk014 = HuAudFXPlay(0x2D7);
                    work->unk004 = 5;
                    man->unk000 = 1;
                    break;
                case 4:
                    break;
            }
            break;
        case 4:
            if (work->unk044 != fn_1_1814()) {
                work->unk004 = 2;
            }
            break;
        case 5:
            if (++work->unk008 < 90.0) {
                break;
            }
            work->unk004++;
            work->unk008 = 0;
            mdlId = obj->mdlId[2];
            Hu3DMotionTimeSet(mdlId, 0.0f);
            Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
            work->unk018 = HuAudFXPlay(0x6DE);
        case 6:
            if (++work->unk008 < 6.0) {
                break;
            }
            work->unk004++;
            mdlId = obj->mdlId[0];
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        case 7:
            mdlId = obj->mdlId[2];
            if (!Hu3DMotionEndCheck(mdlId)) {
                break;
            }
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
            work->unk004++;
            man->unk000 = 0;
        case 8:
            if (Center.x > -1000.0) {
                break;
            }
            work->unk004 = 2;
            mdlId = obj->mdlId[0];
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
            break;
    }
    PSVECAdd(&work->unk01C, &work->unk028, &work->unk01C);
    if (work->unk014 != -1) {
        if (HuAudFXStatusGet(work->unk014) == 2) {
            fn_1_1AF4(work->unk014, &work->unk01C);
        } else {
            work->unk014 = -1;
        }
    }
    if (work->unk018 != -1) {
        if (HuAudFXStatusGet(work->unk018) == 2) {
            fn_1_1AF4(work->unk018, &work->unk01C);
        } else {
            work->unk018 = -1;
        }
    }
    fn_1_48B0(obj);
}

/* 10 insns. The controller's flag: 1 while a type-3 object's sequence runs. */
s32 fn_1_50E4(void)
{
    M514_OBJMAN *work = lbl_1_bss_208->data;

    return work->unk000;
}
