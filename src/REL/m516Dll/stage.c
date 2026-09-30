/*
 * m516dll stage.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m516Dll/asm/REL/m516Dll/stage.s.
 */

#include "REL/m516Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x250 */ /* float lbl_1_rodata_250 = 0.0f; */
/* 0x254 */ /* float lbl_1_rodata_254 = -3000.0f; */
/* 0x258 */ /* float lbl_1_rodata_258 = 3000.0f; */
/* 0x25C */ /* float lbl_1_rodata_25C = -300.0f; */
/* 0x260 */ /* s32 lbl_1_rodata_260[1] = { 0x437A0000 }; */
/* 0x264 */ /* s32 lbl_1_rodata_264[66] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000002, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000002, 0x00000002, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x36C */ /* float lbl_1_rodata_36C = 1.0f; */
/* 0x370 */ /* float lbl_1_rodata_370 = 3.3333335f; */
/* 0x374 */ /* float lbl_1_rodata_374 = 200.0f; */
/* 0x378 */ /* double lbl_1_rodata_378 = 22; */
/* 0x380 */ /* double lbl_1_rodata_380 = 0.0000152587890625; */
/* 0x388 */ /* float lbl_1_rodata_388 = -1050.0f; */
/* 0x390 */ /* double lbl_1_rodata_390 = 100; */
/* 0x398 */ /* float lbl_1_rodata_398 = -50.0f; */
/* 0x39C */ /* float lbl_1_rodata_39C = 50.0f; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = -100.0f; */
/* 0x3A8 */ /* double lbl_1_rodata_3A8 = 4503601774854144; */
/* 0x3B0 */ /* double lbl_1_rodata_3B0 = 2; */
/* 0x3B8 */ /* double lbl_1_rodata_3B8 = 420; */
/* 0x3C0 */ /* double lbl_1_rodata_3C0 = 180; */
/* 0x3C8 */ /* double lbl_1_rodata_3C8 = 0.01666666753590107; */
/* 0x3D0 */ /* double lbl_1_rodata_3D0 = 150; */
/* 0x3D8 */ /* double lbl_1_rodata_3D8 = 240; */
/* 0x3E0 */ /* double lbl_1_rodata_3E0 = 0.04; */
/* 0x3E8 */ /* double lbl_1_rodata_3E8 = 0.1; */
/* 0x3F0 */ /* double lbl_1_rodata_3F0 = 0; */
/* 0x3F8 */ /* float lbl_1_rodata_3F8 = 5.5000005f; */
/* 0x3FC */ /* float lbl_1_rodata_3FC = -8191.0f; */
/* 0x400 */ /* float lbl_1_rodata_400 = 8191.0f; */
/* 0x408 */ /* double lbl_1_rodata_408 = -1100; */
/* 0x410 */ /* double lbl_1_rodata_410 = 1000; */
/* 0x418 */ /* double lbl_1_rodata_418 = 2200; */
/* 0x420 */ /* double lbl_1_rodata_420 = 1100; */
/* 0x428 */ /* float lbl_1_rodata_428 = 8.333334f; */
/* 0x430 */ /* double lbl_1_rodata_430 = 1.666666753590107; */
/* 0x438 */ /* double lbl_1_rodata_438 = 5; */
/* 0x440 */ /* double lbl_1_rodata_440 = 24; */
/* 0x448 */ /* double lbl_1_rodata_448 = 2400; */
/* 0x450 */ /* double lbl_1_rodata_450 = 4503599627370496; */
/* 0x458 */ /* double lbl_1_rodata_458 = 360; */
/* 0x460 */ /* float lbl_1_rodata_460 = 0.1f; */
/* 0x464 */ /* float lbl_1_rodata_464 = 135.0f; */
/* 0x468 */ /* float lbl_1_rodata_468 = 180.0f; */
/* 0x46C */ /* float lbl_1_rodata_46C = 315.0f; */
/* 0x470 */ /* float lbl_1_rodata_470 = -70.0f; */
/* 0x474 */ /* float lbl_1_rodata_474 = 30.000002f; */
/* 0x478 */ /* double lbl_1_rodata_478 = 1.5; */
/* 0x480 */ /* double lbl_1_rodata_480 = 1.3333334028720856; */
/* 0x488 */ /* double lbl_1_rodata_488 = 1.2; */
/* 0x490 */ /* double lbl_1_rodata_490 = 3; */
/* 0x498 */ /* double lbl_1_rodata_498 = 3.141592653589793; */
/* 0x4A0 */ /* float lbl_1_rodata_4A0 = 10.0f; */
/* 0x4A8 */ /* double lbl_1_rodata_4A8 = 1; */
/* 0x4B0 */ /* double lbl_1_rodata_4B0 = 0.05; */
/* 0x4B8 */ /* double lbl_1_rodata_4B8 = 0.000030517578125; */
/* 0x4C0 */ /* double lbl_1_rodata_4C0 = 0.5; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 0.5f; */
/* 0x4D0 */ /* double lbl_1_rodata_4D0 = -0.5; */
/* 0x4D8 */ /* float lbl_1_rodata_4D8 = -0.5f; */
/* 0x4E0 */ /* double lbl_1_rodata_4E0 = 0.3; */
/* 0x4E8 */ /* float lbl_1_rodata_4E8 = 0.3f; */
/* 0x4F0 */ /* double lbl_1_rodata_4F0 = -0.3; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = -0.3f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = 0.05f; */
/* 0x500 */ /* double lbl_1_rodata_500 = 0.0005; */

/* --- .data --- */
/* 0x138 */ char lbl_1_data_138[6][10] = { "block_LA", "block_LB", "block_LC", "block_RA", "block_RB", "block_RC" };
/* 0x174 */ M516_STAGEPROP lbl_1_data_174[4] = {
    { 0x004A0006, 4, 0.2f, { -2500.0f, 1000.0f, -3000.0f }, { 2500.0f, 1800.0f, -3000.0f } },
    { 0x004A0007, 4, 0.0f, { -1600.0f, 0.0f, 0.0f }, { 350.0f, 0.0f, 0.0f } },
    { 0x004A0008, 4, 0.0f, { -2400.0f, 0.0f, 0.0f }, { -950.0f, 0.0f, 0.0f } },
    { 0x004A0009, 4, 0.0f, { -2700.0f, 0.0f, 0.0f }, { -2100.0f, 0.0f, 0.0f } },
};
/* 0x204 */ HuVecF lbl_1_data_204[3] = {
    { -1000.0f, -150.0f, -650.0f },
    { -650.0f, -150.0f, -650.0f },
    { 800.0f, -150.0f, -650.0f },
};
/* 0x228 */ HuVecF lbl_1_data_228[3] = {
    { -600.0f, 150.0f, 150.0f },
    { 300.0f, 150.0f, 150.0f },
    { 600.0f, 150.0f, 150.0f },
};
/* 0x24C */ s32 lbl_1_data_24C[4] = { 0x000006E9, 0x000006EA, 0x000006EB, 0x000006EC };
/* 0x25C */ s32 lbl_1_data_25C[4] = { 0x000006ED, 0x000006EE, 0x000006EF, 0x000006F0 };
/* 0x26C */ HuVecF lbl_1_data_26C[2] = {
    { -4000.0f, -100.0f, -5000.0f },
    { 4000.0f, -100.0f, -100.0f },
};
/* 0x284 */ GXColor lbl_1_data_284 = { 255, 255, 255, 255 };
/* 0x288 */ float lbl_1_data_288[2][3] = {
    { 0.04f, 0.0f, 0.0f },
    { 0.0f, 0.04f, 0.0f },
};
/* 0x2A0 */ char lbl_1_data_2A0[4][8] = { "Chara1", "Chara2", "Chara3", "Chara4" };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x3C gap_05_0000003C_bss (0x4) -- dtk filler */
/* 0x38 */ OMOBJ *lbl_1_bss_38;      /* stage object; data is M516_STAGE */

/* Random factors from frand(): signed in [-1, 1) and unsigned in [0, 1). */
#define M516_FRANDS() ((1.0 / 32768) * (float)(s32)((frand() & 0xFFFF) - 32768))
#define M516_FRANDU() ((1.0 / 65536) * (float)(s32)(frand() & 0xFFFF))

/* --- functions (reference order) --- */
/* asm 9-46, 36 insns. Stage object and its M516_STAGE work. */
void fn_1_48CC(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M516_STAGE *work;

    obj = omAddObjEx(objman, 20, 134, 0, -1, fn_1_4960);
    lbl_1_bss_38 = obj;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M516_STAGE));
    obj->work[0] = 0;
}

/* 1 insns */
void fn_1_495C(void)
{
}

/* 230 insns. Stage object init. */
void fn_1_4960(OMOBJ *obj)
{
    M516_STAGE *work;
    M516_ACTOR *act;
    HU3DMODELID mdlId;
    HSFOBJECT *hsfObj;
    s32 i;

    work = obj->data;
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 0));
    obj->mdlId[0] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 4);
    for (i = 0; i < 3; i++) {
        hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_138[i]);
        work->unk4C[i] = hsfObj;
        work->unk64[i] = 0.0f;
        if (hsfObj != NULL) {
            work->unk80[i] = hsfObj->mesh.base.pos.y;
            work->unk8C[i] = hsfObj->mesh.base.pos.z;
            work->unk98[i] = 0.0f;
        }
        hsfObj = Hu3DModelObjPtrGet(mdlId, lbl_1_data_138[i + 3]);
        work->unk4C[i + 3] = hsfObj;
        hsfObj != NULL;
    }
    work->unk00.x = 0.0f;
    work->unk00.y = 0.0f;
    work->unk00.z = 0.0f;
    act = &work->unk0C;
    act->unk00 = 1;
    act->unk04 = 1;
    act->unk08 = 0;
    act->unk0C = 0;
    act->unk10 = obj;
    act->unk14 = 0;
    act->unk18 = &work->unk00;
    act->unk1C = NULL;
    act->unk20 = -3000.0f;
    act->unk24 = 0.0f;
    act->unk28.f = 3000.0f;
    act->unk2C.f = -300.0f;
    act->unk30.i = 0;
    act->unk38 = 0;
    act->unk3C = 0;
    fn_1_8E00(act);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 1));
    obj->mdlId[1] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 2));
    obj->mdlId[2] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 3));
    obj->mdlId[3] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 5));
    obj->mdlId[122] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DModelLayerSet(mdlId, 0);
    mdlId = Hu3DModelCreateData(DATANUM(DATA_m516, 4));
    obj->mdlId[123] = mdlId;
    Hu3DModelLayerSet(mdlId, 4);
    fn_1_4DB4(obj);
    fn_1_59EC(obj);
    fn_1_5C70(obj);
    fn_1_5F6C(obj);
    fn_1_6154(obj);
    fn_1_6870(obj);
    fn_1_6C54(obj);
    obj->objFunc = fn_1_4CF8;
}

/* 47 insns. Stage object main. */
void fn_1_4CF8(OMOBJ *obj)
{
    HU3DMODELID mdlId;

    mdlId = obj->mdlId[1];
    if (Hu3DMotionEndCheck(mdlId)) {
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(mdlId, 250.0f, Hu3DMotionMaxTimeGet(mdlId));
    }
    fn_1_51C4(obj);
    fn_1_5AC4(obj);
    fn_1_5D2C(obj);
    fn_1_601C(obj);
    fn_1_6234(obj);
    fn_1_69A4(obj);
    fn_1_6CF4(obj);
    obj->work[0]++;
}

/* 260 insns. Lays out the 3x22 blocks from a shuffled kind table. */
void fn_1_4DB4(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    s32 blockNo = 0;
    HU3DMODELID srcMdl = -1;
    HU3DMODELID srcShadow = -1;
    s32 kind[3][22] = {
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        { 1, 1, 1, 1, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };
    M516_STAGESUB *block;
    M516_ACTOR *act;
    HuVecF pos;
    HU3DMODELID mdlId;
    HU3DMODELID shadowId;
    s32 *row;
    s32 i;
    s32 j;
    s32 sel;
    s32 tmp;

    work->unk70 = -1;
    work->unk74 = 0;
    work->unk78 = 1.0f;
    work->unk7C = (1.0f / 60.0f) * 200;
    work->unkA4 = 200.0f;
    for (i = 0; i < 3; i++) {
        row = kind[i];
        for (j = 10; j < 22; j++) {
            row[j] = 0;
        }
        for (j = 0; j < 22; j++) {
            sel = 22 * M516_FRANDU();
            tmp = row[sel];
            row[sel] = row[j];
            row[j] = tmp;
        }
    }
    for (i = 0; i < 3; i++) {
        pos.x = -1050.0f;
        pos.y = work->unk80[i];
        pos.z = work->unk8C[i];
        row = kind[i];
        for (j = 0; j < 22; j++, blockNo++) {
            block = &work->unkA8[blockNo];
            block->unk0C = row[j];
            block->unk14 = pos;
            block->unk38 = pos.y;
            block->unk3C = i;
            switch (block->unk0C) {
            case 1:
                block->unk08 = 1;
                break;
            case 2:
                block->unk08 = 10;
                break;
            default:
                block->unk08 = 0;
                break;
            }
            if (srcMdl == -1) {
                srcMdl = Hu3DModelCreateData(DATANUM(DATA_m516, 13));
                mdlId = srcMdl;
            } else {
                mdlId = Hu3DModelLink(srcMdl);
            }
            obj->mdlId[blockNo + 6] = mdlId;
            block->unk10 = mdlId;
            Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DModelLayerSet(mdlId, 4);
            Hu3DModelPosSetV(mdlId, &pos);
            pos.x += 100.0;
            if (block->unk0C != 0) {
                if (srcShadow == -1) {
                    srcShadow = Hu3DModelCreateData(DATANUM(DATA_m516, 14));
                    shadowId = srcShadow;
                } else {
                    shadowId = Hu3DModelLink(srcShadow);
                }
                block->unk12 = shadowId;
                Hu3DModelAttrSet(shadowId, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(shadowId, HU3D_MOTATTR_PAUSE);
                Hu3DModelLayerSet(shadowId, 4);
            } else {
                block->unk12 = -1;
            }
            act = &block->unk4C;
            act->unk00 = 1;
            act->unk04 = 2;
            act->unk08 = blockNo;
            act->unk0C = 0;
            act->unk10 = obj;
            act->unk14 = 0;
            act->unk18 = &block->unk14;
            act->unk1C = &block->unk20;
            act->unk20 = -50.0f;
            act->unk24 = 0.0f;
            act->unk28.f = 50.0f;
            act->unk2C.f = -100.0f;
            act->unk30.i = 1;
            act->unk34 = 0;
            act->unk38 = 0;
            act->unk3C = 0;
            fn_1_8E00(act);
        }
    }
}

/* 522 insns. Per-frame block scroll, hit response and sound. */
void fn_1_51C4(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    s32 i;
    M516_STAGESUB *block;
    HSFOBJECT *hsfObj;
    s32 pitch;
    float speed;
    float level;

    if (fn_1_1838() != 1) {
        work->unkA4 -= 2.0;
        if (work->unkA4 < 0.0f) {
            work->unkA4 = 0.0f;
        }
    }
    if ((work->unk74 += 1) > work->unk78) {
        work->unk74 = 0;
        work->unk78 = 420.0 + (s32)(180 * M516_FRANDU());
        speed = (1.0f / 60.0f) * (150 + 180 * M516_FRANDU());
        if (work->unk7C > 0.0f) {
            speed = -speed;
        }
        work->unk7C = speed;
    }
    for (i = 0; i < 3; i++) {
        if (fn_1_1850() == 2) {
            if (work->unk74 < work->unk78 - 240.0) {
                if (i & 1) {
                    speed = work->unk7C;
                } else {
                    speed = -work->unk7C;
                }
            } else {
                speed = 0.0f;
            }
        } else {
            work->unk74 = 0;
            speed = 0.0f;
        }
        work->unk98[i] += 0.04 * (speed - work->unk98[i]);
    }
    level = fabs(work->unk98[0]);
    if (level < 0.1) {
        level = 0.0f;
    }
    if (0.0 != level) {
        if (work->unk70 == -1) {
            work->unk70 = HuAudFXPlay(0x6F1);
        } else {
            float maxSpeed = (1.0f / 60.0f) * 330;

            pitch = -8191.0f + 8191.0f * (level / maxSpeed);
            if (pitch < -8191) {
                pitch = -8191;
            }
            if (pitch > 0) {
                pitch = 0;
            }
            HuAudFXPitchSet(work->unk70, pitch);
        }
    } else {
        if (work->unk70 != -1) {
            HuAudFXFadeOut(work->unk70, 1000);
            work->unk70 = -1;
        }
    }
    for (i = 0; i < 3; i++) {
        work->unk64[i] += work->unk98[i];
        speed = fmodf(work->unk64[i], 100.0f);
        if (speed < 0.0f) {
            speed += 100.0;
        }
        hsfObj = work->unk4C[i];
        if (hsfObj != NULL) {
            hsfObj->mesh.base.pos.x = -1100.0 + speed;
        }
        hsfObj = work->unk4C[i + 3];
        if (hsfObj != NULL) {
            hsfObj->mesh.base.pos.x = 1000.0 + speed;
        }
    }
    for (i = 0; i < 66; i++) {
        block = &work->unkA8[i];
        speed = work->unk98[block->unk3C];
        block->unk20.x = speed;
        block->unk14.x += speed;
        if (speed < 0.0f && block->unk14.x < -1100.0) {
            block->unk14.x += 2200.0;
        }
        if (speed > 0.0f && block->unk14.x > 1100.0) {
            block->unk14.x -= 2200.0;
        }
        switch (block->unk00) {
        case 0:
            if (block->unk4C.unk38 != 0) {
                switch (block->unk0C) {
                case 1:
                case 2:
                    fn_1_800C(block->unk4C.unk3C, 1);
                    fn_1_5EDC(&block->unk14);
                    block->unk20.y = (1.0f / 60.0f) * 500;
                    block->unk00 = 1;
                    fn_1_1B8C(7, &block->unk14);
                    break;
                default:
                    block->unk20.y = (1.0f / 60.0f) * 500;
                    Hu3DModelAttrSet(block->unk10, HU3D_ATTR_DISPOFF);
                    fn_1_5B6C(&block->unk14);
                    block->unk00 = 3;
                    fn_1_1B8C(lbl_1_data_24C[block->unk4C.unk34], &block->unk14);
                    break;
                }
            }
            break;
        case 1:
            block->unk14.y += block->unk20.y;
            block->unk20.y -= (1.0f / 60.0f) * 100.0;
            if (block->unk20.y < 0.0f && block->unk08 <= 1) {
                Hu3DModelAttrSet(block->unk10, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(block->unk12, HU3D_ATTR_DISPOFF);
            }
            if (!(block->unk14.y > block->unk38)) {
                block->unk14.y = block->unk38;
                if ((block->unk08 -= 1) > 0) {
                    block->unk00 = 0;
                } else {
                    block->unk4C.unk30.i = 0;
                    block->unk00 = 2;
                }
            }
            break;
        case 2:
            if (block->unk4C.unk38 != 0) {
                fn_1_1B8C(lbl_1_data_25C[block->unk4C.unk34], &block->unk14);
            }
            break;
        case 3:
            block->unk4C.unk00 &= ~1;
            block->unk00 -= 1;
            break;
        }
        block->unk4C.unk38 = 0;
        block->unk4C.unk3C = 0;
        Hu3DModelPosSet(block->unk10, block->unk14.x, block->unk14.y + work->unkA4, block->unk14.z);
        if (block->unk12 != -1) {
            Hu3DModelPosSet(block->unk12, block->unk14.x, block->unk14.y + work->unkA4, block->unk14.z);
        }
    }
}

/* 54 insns */
void fn_1_59EC(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    HU3DMODELID topMdlId;
    s32 i;
    HU3DMODELID mdlId;

    for (i = 0; i < 12; i++) {
        if (i == 0) {
            topMdlId = Hu3DModelCreateData(0x4A000F);
            mdlId = topMdlId;
        } else {
            mdlId = Hu3DModelLink(topMdlId);
        }
        obj->mdlId[i + 98] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 4);
        work->unk24C0[i] = 0;
    }
}

/* 42 insns */
void fn_1_5AC4(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (work->unk24C0[i]) {
            mdlId = obj->mdlId[i + 98];
            if (Hu3DMotionEndCheck(mdlId)) {
                Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
                work->unk24C0[i] = 0;
            }
        }
    }
}

/* 65 insns */
void fn_1_5B6C(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_38;
    M516_STAGE *work = obj->data;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (!work->unk24C0[i]) {
            work->unk24C0[i] = 1;
            mdlId = obj->mdlId[i + 98];
            Hu3DModelPosSetV(mdlId, pos);
            Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(mdlId, 0.0f);
            break;
        }
    }
}

/* 47 insns */
void fn_1_5C70(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    HU3DMODELID topMdlId;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 12; i++) {
        if (i == 0) {
            topMdlId = Hu3DModelCreateData(0x4A0010);
            mdlId = topMdlId;
        } else {
            mdlId = Hu3DModelLink(topMdlId);
        }
        obj->mdlId[i + 110] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(mdlId, 4);
    }
}

/* 108 insns */
void fn_1_5D2C(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 12; i++) {
        sub = &work->unk24F0[i];
        mdlId = obj->mdlId[i + 110];
        switch (sub->unk00) {
        case 0:
            break;

        case 1:
            sub->unk00++;
            sub->unk08 = 0;
            Hu3DModelPosSetV(mdlId, &sub->unk14);
            Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
            break;

        case 2:
            sub->unk14.y += 5.0;
            Hu3DModelPosSetV(mdlId, &sub->unk14);
            Hu3DModelRotSet(mdlId, 0.0f, sub->unk08 * 20, 0.0f);
            if (++sub->unk08 < 24.0) {
                break;
            }
            sub->unk00 = 0;
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
            break;
        }
    }
}

/* 36 insns */
void fn_1_5EDC(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_38;
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    s32 i;

    for (i = 0; i < 12; i++) {
        sub = &work->unk24F0[i];
        if (sub->unk00 == 0) {
            sub->unk00++;
            sub->unk14 = *pos;
            break;
        }
    }
}

/* 44 insns */
void fn_1_5F6C(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    M516_STAGEPROP *prop;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 4; i++) {
        sub = &work->unk2B80[i];
        prop = &lbl_1_data_174[i];
        mdlId = Hu3DModelCreateData(prop->unk00);
        obj->mdlId[i + 124] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, prop->unk04);
    }
}

/* 78 insns */
void fn_1_601C(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    M516_STAGEPROP *prop;
    HU3DMODELID mdlId;
    s32 i;
    float t;

    t = (float)obj->work[0] / 2400.0;
    for (i = 0; i < 4; i++) {
        sub = &work->unk2B80[i];
        prop = &lbl_1_data_174[i];
        mdlId = obj->mdlId[i + 124];
        sub->unk14.x = prop->unk0C.x + t * (prop->unk18.x - prop->unk0C.x);
        sub->unk14.y = prop->unk0C.y + t * (prop->unk18.y - prop->unk0C.y);
        sub->unk14.z = prop->unk0C.z + t * (prop->unk18.z - prop->unk0C.z);
        sub->unk2C.y += prop->unk08;
        Hu3DModelPosSetV(mdlId, &sub->unk14);
        Hu3DModelRotSetV(mdlId, &sub->unk2C);
    }
}

/* 56 insns */
void fn_1_6154(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    HU3DMODELID topMdlId;
    HU3DMODELID mdlId;
    HU3DMOTID motId;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (i == 0) {
            topMdlId = Hu3DModelCreateData(0x4A000B);
            mdlId = topMdlId;
            motId = Hu3DJointMotionData(mdlId, 0x4A000C);
        } else {
            mdlId = Hu3DModelLink(topMdlId);
        }
        obj->mdlId[i + 128] = mdlId;
        Hu3DMotionSet(mdlId, motId);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(mdlId, 0);
    }
}

/* 376 insns */
void fn_1_6234(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    HU3DMODELID mdlId;
    s32 i;
    float rotY;
    float angle;
    float angleMod;
    float angleNew;

    for (i = 0; i < 3; i++) {
        sub = &work->unk2DB0[i];
        mdlId = obj->mdlId[i + 128];
        switch (sub->unk00) {
        case 0:
            sub->unk00++;
            sub->unk08 = 240.0 + (s32)(240.0 * M516_FRANDU());
            sub->unk14 = lbl_1_data_204[i];
            sub->unk20.y = 0.0f;
            sub->unk38 = 360.0 * M516_FRANDU();
            /* fallthrough */

        case 1:
            sub->unk2C.x = fn_1_1D34(sub->unk2C.x, 0.0f, 0.1f);
            if (--sub->unk08 > 0) {
                break;
            }
            rotY = sub->unk38;
            if (rotY < 135.0f) {
                break;
            }
            if (rotY > 180.0f && rotY < 315.0f) {
                break;
            }
            sub->unk08 = 5;
            sub->unk00++;
            /* fallthrough */

        case 2:
            sub->unk2C.x = fn_1_1D34(sub->unk2C.x, -70.0f, 0.1f);
            if (--sub->unk08 > 0) {
                break;
            }
            sub->unk00++;
            sub->unk20.y = 30.000002f;
            fn_1_6814(&sub->unk14);
            /* fallthrough */

        case 3:
            sub->unk2C.x += 1.5;
            sub->unk20.y -= 1.3333334028720856;
            if (sub->unk20.y > 0.0f) {
                break;
            }
            if (sub->unk14.y > lbl_1_data_204[i].y) {
                break;
            }
            fn_1_6814(&sub->unk14);
            sub->unk14.y = lbl_1_data_204[i].y;
            sub->unk20.y = 0.0f;
            sub->unk00 = 1;
            sub->unk08 = 240.0 + (s32)(240.0 * M516_FRANDU());
            break;
        }
        angle = 1.2 + sub->unk38;
        angleMod = fmod(angle, 360.0);
        angleNew = angleMod;
        sub->unk38 = angleNew;
        if (sub->unk38 < 0.0) {
            sub->unk38 += 360.0;
        }
        sub->unk20.x = (lbl_1_data_204[i].x + 100.0 * (3.0 * sin(3.141592653589793 * sub->unk38 / 180.0))) - sub->unk14.x;
        sub->unk20.z = (lbl_1_data_204[i].z + 100.0 * cos(3.141592653589793 * sub->unk38 / 180.0)) - sub->unk14.z;
        rotY = 180.0 * (atan2(sub->unk20.x, sub->unk20.z) / 3.141592653589793);
        sub->unk2C.y = fn_1_1D34(sub->unk2C.y, rotY, 0.1f);
        PSVECAdd(&sub->unk14, &sub->unk20, &sub->unk14);
        Hu3DModelPosSetV(mdlId, &sub->unk14);
        Hu3DModelRotSetV(mdlId, &sub->unk2C);
    }
}

/* 23 insns */
void fn_1_6814(HuVecF *pos)
{
    HuVecF sprayPos;

    sprayPos.x = pos->x;
    sprayPos.y = -100.0f;
    sprayPos.z = pos->z;
    fn_1_78B8(&sprayPos, 10.0f);
}

/* 77 insns */
void fn_1_6870(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    HU3DMODELID topMdlId;
    HU3DMODELID mdlId;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (i == 0) {
            topMdlId = Hu3DModelCreateData(0x4A000A);
            mdlId = topMdlId;
        } else {
            mdlId = Hu3DModelLink(topMdlId);
        }
        obj->mdlId[i + 131] = mdlId;
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionTimeSet(mdlId, M516_FRANDU() * (Hu3DMotionMaxTimeGet(mdlId) - 1.0));
        Hu3DModelLayerSet(mdlId, 4);
    }
}

/* 172 insns */
void fn_1_69A4(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    HU3DMODELID mdlId;
    s32 i;
    float rotY;

    for (i = 0; i < 3; i++) {
        sub = &work->unk2F54[i];
        mdlId = obj->mdlId[i + 131];
        switch (sub->unk00) {
        case 0:
            sub->unk00++;
            sub->unk08 = 0;
            sub->unk14 = lbl_1_data_228[i];
            /* fallthrough */

        case 1:
            sub->unk20.x += 0.05 * M516_FRANDS();
            sub->unk20.z += 0.05 * M516_FRANDS();
            if (sub->unk20.x > 0.5) {
                sub->unk20.x = 0.5f;
            }
            if (sub->unk20.x < -0.5) {
                sub->unk20.x = -0.5f;
            }
            if (sub->unk20.z > 0.3) {
                sub->unk20.z = 0.3f;
            }
            if (sub->unk20.z < -0.3) {
                sub->unk20.z = -0.3f;
            }
            break;
        }
        rotY = 180.0 + 180.0 * (atan2(sub->unk20.x, sub->unk20.z) / 3.141592653589793);
        sub->unk2C.y = fn_1_1D34(sub->unk2C.y, rotY, 0.05f);
        PSVECAdd(&sub->unk14, &sub->unk20, &sub->unk14);
        Hu3DModelPosSetV(mdlId, &sub->unk14);
        Hu3DModelRotSetV(mdlId, &sub->unk2C);
    }
}

/* 40 insns */
void fn_1_6C54(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;

    work->unk30F8 = work->unk30FC = 0.0f;
    Hu3DWaterCreate(2, HU3D_WATER_ANIM_NONE, NULL, NULL, FALSE, &lbl_1_data_26C[0], &lbl_1_data_26C[1]);
    Hu3DWaterPadYSet(-100.0f);
    Hu3DWaterGlowSet(8, &lbl_1_data_284);
    Hu3DWaterIndTexMtxSet(lbl_1_data_288);
}

/* 33 insns */
void fn_1_6CF4(OMOBJ *obj)
{
    M516_STAGE *work = obj->data;

    work->unk30F8 += 0.0005;
    work->unk30FC += 0.0005;
    Hu3DWaterTexPosSet(work->unk30F8, work->unk30FC, 0.0f);
}

/* 29 insns */
s32 fn_1_6D78(void)
{
    OMOBJ *obj = lbl_1_bss_38;
    M516_STAGE *work = obj->data;
    M516_STAGESUB *sub;
    s32 cnt;
    s32 i;

    cnt = 0;
    for (i = 0; i < 66; i++) {
        sub = &work->unkA8[i];
        if (sub->unk00 != 2) {
            cnt++;
        }
    }
    return cnt;
}

/* 42 insns */
BOOL fn_1_6DEC(s32 no, HuVecF *pos, float *rotY)
{
    OMOBJ *obj = lbl_1_bss_38;
    HSFOBJECT *object;
    HU3DMODELID mdlId;

    mdlId = obj->mdlId[123];
    object = Hu3DModelObjPtrGet(mdlId, lbl_1_data_2A0[no]);
    if (object != NULL) {
        pos->x = object->mesh.curr.pos.x;
        pos->y = object->mesh.curr.pos.y;
        pos->z = object->mesh.curr.pos.z;
        *rotY = object->mesh.curr.rot.y;
    }
    return Hu3DMotionEndCheck(mdlId) == 0;
}

/* 36 insns */
float fn_1_6E94(float x)
{
    OMOBJ *obj = lbl_1_bss_38;
    M516_STAGE *work = obj->data;
    s32 idx;

    idx = (x + 0.5 * work->unk80[0]) / work->unk80[0];
    if (idx < 0) {
        idx = 0;
    }
    if (idx >= 3) {
        return 0.0f;
    }
    return work->unk98[idx];
}

