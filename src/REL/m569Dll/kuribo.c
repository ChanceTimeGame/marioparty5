/*
 * m569dll kuribo.c (fork K) -- the big kuribo (fn_1_582C's object: walks in,
 * turns to face the camera, stomps on request) and the 17 background kuribo
 * that bob up and down (fn_1_6DB4's objects). Functions are in reference
 * order; fn_1_5C54 and fn_1_5A9C are inlined into their callers.
 */

#include "REL/m569dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "datadir_enum.h"

#include "math.h"

/* --- .rodata --- */

/* the big kuribo's three joint motions (0: idle, 1: walk, 2: stomp) */
const s32 lbl_1_rodata_F8[3] = {
    DATANUM(DATA_m569, 0x06), DATANUM(DATA_m569, 0x07), DATANUM(DATA_m569, 0x08)
};

/* --- .data --- */

/* the big kuribo's start position */
HuVecF lbl_1_data_238 = { 150.0f, 100.0f, -800.0f };
/* where it walks to before turning to the camera (fn_1_6418 case 3) */
HuVecF lbl_1_data_244 = { 400.0f, 0.0f, 0.0f };
/* the 17 background kuribo's home positions: 9 at z 150, 8 at z 200 */
HuVecF lbl_1_data_250[17] = {
    { -400.0f, -100.0f, 150.0f },
    { -300.0f, -100.0f, 150.0f },
    { -200.0f, -100.0f, 150.0f },
    { -100.0f, -100.0f, 150.0f },
    { 0.0f, -100.0f, 150.0f },
    { 100.0f, -100.0f, 150.0f },
    { 200.0f, -100.0f, 150.0f },
    { 300.0f, -100.0f, 150.0f },
    { 400.0f, -100.0f, 150.0f },
    { -350.0f, -100.0f, 200.0f },
    { -250.0f, -100.0f, 200.0f },
    { -150.0f, -100.0f, 200.0f },
    { -50.0f, -100.0f, 200.0f },
    { 50.0f, -100.0f, 200.0f },
    { 150.0f, -100.0f, 200.0f },
    { 250.0f, -100.0f, 200.0f },
    { 350.0f, -100.0f, 200.0f },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
M569_CROWD *lbl_1_bss_108[18];        /* 0x48; fn_1_6DB4 fills [0..16], [17] is never used */
int lbl_1_bss_104;                    /* the crowd's SE (fn_1_74B0), stopped by fn_1_702C */
int lbl_1_bss_100;                    /* the big kuribo has reached its entry point (fn_1_5D5C) */

/* --- functions (reference order) --- */

M569_KURIBO *fn_1_582C(void)
{
    OMOBJ *obj;
    M569_KURIBO *work;
    HU3DMODELID modelId;
    int i;
    HU3DMOTID motId;

    obj = omAddObjEx(objman, 0x2000, 1, 3, -1, fn_1_5D5C);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, 0x40, HU_MEMNUM_OVL);
    work = obj->data;
    modelId = Hu3DModelCreateData(DATANUM(DATA_m569, 0x05));
    obj->mdlId[0] = modelId;
    for (i = 0; i < 3; i++) {
        motId = Hu3DJointMotionData(modelId, lbl_1_rodata_F8[i]);
        obj->mtnId[i] = motId;
    }
    Hu3DModelShadowSet(modelId);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(modelId, obj->mtnId[1]);
    Hu3DMotionSpeedSet(obj->mdlId[0], 3.0f);
    modelId = Hu3DModelCreateData(DATANUM(DATA_m569, 0x05));
    obj->mdlId[1] = modelId;
    for (i = 0; i < 3; i++) {
        work->unk034[i] = Hu3DJointMotionData(modelId, lbl_1_rodata_F8[i]);
    }
    Hu3DModelAttrSet(modelId, HU3D_ATTR_CULL_FRONT);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(modelId, 1.0f, -1.0f, 1.0f);
    Hu3DMotionSet(modelId, work->unk034[1]);
    Hu3DMotionSpeedSet(obj->mdlId[1], 3.0f);
    work->unk02C = 1;
    work->unk000 = 0;
    work->unk004 = lbl_1_data_238;
    work->unk010.x = work->unk010.y = work->unk010.z = 0.0f;
    work->unk030 = 0.0f;
    return work;
}

void fn_1_5A9C(OMOBJ *obj, int motNo)
{
    M569_KURIBO *work = obj->data;
    float unused1 = 0.0f;
    float unused0 = 10.0f;
    u32 attr = HU3D_MOTATTR_LOOP;

    if (work->unk02C != motNo) {
        work->unk02C = motNo;
        Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(obj->mdlId[1], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        switch (motNo) {
            case 0:
                Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
                Hu3DMotionSpeedSet(obj->mdlId[1], 1.0f);
                break;
            case 1:
                Hu3DMotionSpeedSet(obj->mdlId[0], 3.0f);
                Hu3DMotionSpeedSet(obj->mdlId[1], 3.0f);
                break;
            case 2:
                Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
                Hu3DMotionSpeedSet(obj->mdlId[1], 1.0f);
                attr = 0;
                break;
        }
        Hu3DModelAttrSet(obj->mdlId[0], attr);
        Hu3DMotionSet(obj->mdlId[0], obj->mtnId[motNo]);
        Hu3DModelAttrSet(obj->mdlId[1], attr);
        Hu3DMotionSet(obj->mdlId[1], obj->mtnId[motNo]);
    }
}

void fn_1_5C54(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;
    float time = Hu3DMotionTimeGet(obj->mdlId[0]);

    switch (work->unk02C) {
        case 1:
            if (time < work->unk030) {
                fn_1_109C(&work->unk004, 0x2CE);
            }
            if (work->unk030 < 20.0f && 20.0f <= time) {
                fn_1_109C(&work->unk004, 0x2CE);
            }
            break;
        case 2:
            if (work->unk030 < 10.0f && 10.0f <= time) {
                fn_1_109C(&work->unk004, 0x2DE);
            }
            break;
    }
    work->unk030 = time;
}

void fn_1_5D5C(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;
    HuVecF target = { 0.0f, 100.0f, -800.0f };

    fn_1_5C54(obj);
    if (lbl_1_bss_100 == 0) {
        if (MgVecApproach(&work->unk004, &target, &work->unk010, 4.0f)) {
            lbl_1_bss_100 = 1;
            obj->work[0] = 0;
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
        }
    } else if (obj->work[0]++ == 5) {
        obj->work[0] = 0;
        obj->objFunc = fn_1_5F48;
    }
    omSetTra(obj, work->unk004.x, work->unk004.y, work->unk004.z);
    omSetRot(obj, work->unk010.x, work->unk010.y, work->unk010.z);
}

void fn_1_5F48(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;

    fn_1_5C54(obj);
    work->unk010.y = MgAngleApproach(work->unk010.y, 0.0f, 10.0f);
    if (0.0f == work->unk010.y) {
        lbl_1_bss_14 = 1;
        Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
        obj->objFunc = fn_1_60F0;
    }
    omSetTra(obj, work->unk004.x, work->unk004.y, work->unk004.z);
    omSetRot(obj, work->unk010.x, work->unk010.y, work->unk010.z);
}

void fn_1_60F0(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;
    HuVecF path[3] = { { 0.0f, 100.0f, -670.0f }, { 0.0f, 0.0f, -600.0f }, { 0.0f, 0.0f, 0.0f } };
    int done;

    fn_1_5C54(obj);
    if (obj->work[2]) {
        obj->work[2]--;
        return;
    }
    if (obj->work[0] == 1) {
        if (obj->work[1] == 0) {
            if (work->unk004.y < 70.0f) {
                obj->work[1] = 1;
                obj->work[2] = 5;
            }
        } else if (obj->work[1] == 1) {
            if (work->unk004.y < 35.0f) {
                obj->work[1] = 2;
                obj->work[2] = 5;
            }
        }
    }
    done = MgVecApproach(&work->unk004, &path[obj->work[0]], &work->unk010, 10.0f);
    if (done) {
        obj->work[0]++;
        if (obj->work[0] == 3) {
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_LOOP);
            obj->work[0] = 0;
            obj->work[1] = 0;
            obj->work[2] = 0;
            obj->objFunc = fn_1_6418;
        }
        if (obj->work[0] == 1) {
            Hu3DMotionSpeedSet(obj->mdlId[0], 3.0f);
            Hu3DMotionSpeedSet(obj->mdlId[1], 3.0f);
            Hu3DModelAttrReset(obj->mdlId[1], HU3D_ATTR_DISPOFF);
        }
    }
    Hu3DModelPosSet(obj->mdlId[1], work->unk004.x, 0.0f, work->unk004.z);
    Hu3DModelRotSetV(obj->mdlId[1], &work->unk010);
    omSetTra(obj, work->unk004.x, work->unk004.y, work->unk004.z);
    omSetRot(obj, work->unk010.x, work->unk010.y, work->unk010.z);
}

void fn_1_6418(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;
    float angle;
    float diff;
    double adiff;

    fn_1_5C54(obj);
    switch (obj->work[0]) {
        case 0:
            fn_1_5A9C(obj, 2);
            fn_1_735C();
            lbl_1_bss_14 = 2;
            obj->work[0] = 1;
            obj->work[1] = 0;
            break;
        case 1:
            obj->work[1]++;
            if (obj->work[1] == 25) {
                CharEffectDustCreate(1, 1.0f, &work->unk004);
            }
            if (Hu3DMotionEndCheck(obj->mdlId[0])) {
                obj->work[0] = 2;
                obj->work[1] = 0;
            }
            break;
        case 2:
            if (obj->work[1]++ == 30) {
                fn_1_5A9C(obj, 1);
                obj->work[0] = 3;
                obj->work[1] = 0;
            }
            break;
        case 3:
            obj->work[1]++;
            if (MgVecApproach(&work->unk004, &lbl_1_data_244, &work->unk010, 7.0f)) {
                obj->work[1] = 0;
                obj->work[0] = 4;
            }
            break;
        case 4:
            angle = 180.0 * (atan2(lbl_1_bss_34.pos.x - work->unk004.x, lbl_1_bss_34.pos.z - work->unk004.z) / M_PI);
            if (angle < 0.0f) {
                angle += 360.0f;
            }
            work->unk010.y = MgAngleApproach(work->unk010.y, angle, 10.0f);
            diff = work->unk010.y - angle;
            adiff = fabs(diff);
            if (adiff <= 0.1f) {
                work->unk010.y = angle;
                obj->work[0] = 0;
                fn_1_5A9C(obj, 0);
                work->unk000 = 1;
                obj->objFunc = fn_1_6A48;
            }
            break;
    }
    Hu3DModelPosSetV(obj->mdlId[1], &work->unk004);
    Hu3DModelRotSetV(obj->mdlId[1], &work->unk010);
    omSetTra(obj, work->unk004.x, work->unk004.y, work->unk004.z);
    omSetRot(obj, work->unk010.x, work->unk010.y, work->unk010.z);
}

void fn_1_6A48(OMOBJ *obj)
{
    M569_KURIBO *work = obj->data;

    fn_1_5C54(obj);
    switch (work->unk000) {
        case 1:
            break;
        case 2:
            fn_1_5A9C(obj, 2);
            work->unk000 = 3;
            obj->work[0] = 0;
            break;
        case 3:
            obj->work[0]++;
            if (obj->work[0] == 25) {
                CharEffectDustCreate(1, 1.0f, &work->unk004);
            }
            if (Hu3DMotionEndCheck(obj->mdlId[0])) {
                fn_1_5A9C(obj, 0);
                work->unk000 = 1;
            }
            break;
    }
}

void fn_1_6D9C(M569_KURIBO *work)
{
    if (work->unk000 == 1) {
        work->unk000 = 2;
    }
}

void fn_1_6DB4(void)
{
    int i;
    OMOBJ *obj;
    HU3DMODELID modelId;
    HU3DMOTID motId;
    int time;

    for (i = 0; i < 17; i++) {
        obj = omAddObjEx(objman, 0x2000, 1, 1, -1, fn_1_702C);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, 0x40, HU_MEMNUM_OVL);
        lbl_1_bss_108[i] = obj->data;
        if (i == 4) {
            modelId = Hu3DModelCreateData(DATANUM(DATA_m569, 0x09));
        } else if (i == 3) {
            modelId = Hu3DModelCreateData(DATANUM(DATA_m569, 0x0B));
        } else {
            modelId = Hu3DModelCreateData(DATANUM(DATA_m569, 0x0D));
        }
        obj->mdlId[0] = modelId;
        motId = Hu3DJointMotionData(modelId, DATANUM(DATA_m569, 0x0E));
        obj->mtnId[0] = motId;
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DMotionSet(modelId, obj->mtnId[0]);
        time = frandmod(Hu3DMotionMaxTimeGet(modelId));
        Hu3DMotionTimeSet(modelId, time);
        lbl_1_bss_108[i]->unk00C = lbl_1_data_250[i];
        lbl_1_bss_108[i]->unk018.x = 0.0f;
        lbl_1_bss_108[i]->unk018.y = 0.0f;
        lbl_1_bss_108[i]->unk018.z = 0.0f;
        lbl_1_bss_108[i]->unk000 = 0;
        lbl_1_bss_108[i]->unk004 = 0;
    }
}

void fn_1_702C(OMOBJ *obj)
{
    M569_CROWD *work = obj->data;

    switch (work->unk000) {
        case 1:
            work->unk004 += 8;
            if (work->unk008) {
                work->unk018.x = 5.0 * sin(M_PI * (float)(work->unk004 % 180) / 180.0);
            } else {
                work->unk018.y = 5.0 * sin(M_PI * (float)(work->unk004 % 180) / 180.0);
            }
            if (obj->work[0]++ == 90) {
                HuAudFXStop(lbl_1_bss_104);
                obj->work[0] = 0;
                work->unk000 = 0;
            }
            break;
        case 2:
            work->unk004 += 8;
            if (work->unk008) {
                work->unk018.x = 5.0 * sin(M_PI * (float)(work->unk004 % 180) / 180.0);
            } else {
                work->unk018.y = 5.0 * sin(M_PI * (float)(work->unk004 % 180) / 180.0);
            }
            break;
    }
    omSetRot(obj, 0.0f, 180.0f, 0.0f);
    omSetTra(obj, work->unk00C.x + work->unk018.x, work->unk00C.y + work->unk018.y, work->unk00C.z);
}

void fn_1_735C(void)
{
    int i;

    for (i = 0; i < 17; i++) {
        if (lbl_1_bss_108[i]->unk000 == 0) {
            lbl_1_bss_108[i]->unk000 = 1;
            lbl_1_bss_108[i]->unk004 += frandmod(90) * 8;
            lbl_1_bss_108[i]->unk008 = frandmod(2);
        }
    }
}

void fn_1_741C(void)
{
    int i;

    for (i = 0; i < 17; i++) {
        if (lbl_1_bss_108[i]->unk000 == 0) {
            lbl_1_bss_108[i]->unk000 = 2;
            lbl_1_bss_108[i]->unk008 = frandmod(2);
        }
    }
}

void fn_1_74B0(void)
{
    lbl_1_bss_104 = HuAudFXPlay(0x39D);
}
