/*
 * m569dll block.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m569dll/asm/REL/m569dll/block.s.
 */

#include "REL/m569dll.h"

#include "game/audio.h"
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
/* Block models by type: number die, operator die. */
const s32 lbl_1_rodata_198[2] = { DATANUM(DATA_m569, 0x0F), DATANUM(DATA_m569, 0x10) };

/* --- .data --- */
/* 0x320 */ /* face sequences by block type: number die faces 0..5 (value - 1); operator die 0 +, 1 -, 2 x (fn_1_86C4) */
u8 lbl_1_data_320[2][6] = { { 0, 1, 2, 3, 4, 5 }, { 0, 2, 0, 1, 0, 2 } };
/* 0x32C */ /* block positions (player.c reads them) */
HuVecF lbl_1_data_32C[3] = { { -2e+02f, 2.7e+02f, -5e+01f }, { 0.0f, 2.7e+02f, -5e+01f }, { 2e+02f, 2.7e+02f, -5e+01f } };
/* 0x350 */ /* block types: number, operator, number (fourth entry unused) */
u8 lbl_1_data_350[4] = { 0, 1, 0, 0 };
/* 0x354 */ HU3DPARMANPARAM lbl_1_data_354 = {
    50, 0,
    5e+01f, 0.0f, 65.0f,
    { 0.0f, -0.195f, 0.0f },
    15.0f, 0.95f, 35.0f, 0.999f,
    4,
    { { 255, 255, 32, 255 }, { 255, 255, 0, 255 }, { 255, 255, 128, 255 }, { 255, 255, 255, 255 } },
    { { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 } }
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x164 gap_05_00000164_bss (0x4) -- dtk filler */
/* 0x158 */ M569_BLOCK *lbl_1_bss_158[3];
/* 0x156 gap_05_00000156_bss (0x2) -- dtk filler */
/* 0x154 */ s16 lbl_1_bss_154;   /* blocks still hittable (3 at start) */
/* 0x150 */ int lbl_1_bss_150;   /* looping SE 0x1D handle, -1 = stopped */

/* --- functions (reference order) --- */

HU3DPARMANID fn_1_74E0(HuVecF *pos)
{
    ANIMDATA *anim;
    void *data;
    HU3DMODELID modelId;
    HU3DPARMANID parManId;

    data = HuDataSelHeapReadNum(DATANUM(DATA_effect, 1), HU_MEMNUM_OVL, HEAP_MODEL);
    anim = HuSprAnimRead(data);
    parManId = Hu3DParManCreate(anim, 50, &lbl_1_data_354);
    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_RANDANGLE | HU3D_PARMAN_ATTR_RANDSPEED100);
    Hu3DParManPosSet(parManId, pos->x, pos->y, pos->z);
    Hu3DParManRotSet(parManId, 0.0f, 0.0f, 0.0f);
    Hu3DParManVecSet(parManId, 0.0f, 0.4f, 0.2f);
    Hu3DParManTimeLimitSet(parManId, 50);
    modelId = Hu3DParManModelIDGet(parManId);
    Hu3DModelLayerSet(modelId, 2);
    Hu3DParticleBlendModeSet(modelId, 0);
    return parManId;
}

void fn_1_75F8(OMOBJ *obj)
{
    M569_BLOCK *work = obj->data;

    work->unk014 += 25;
    if (work->unk014 >= 1080) {
        work->unk004 = 1;
        work->unk018 = 1.0f;
        work->unk014 = 0;
        work->unk028 = 0;
        return;
    }
    if (work->unk028 < 180) {
        work->unk018 = HuSin((float)(work->unk028 % 180));
    } else {
        work->unk018 = 1.0 + 0.5 * HuSin((float)(work->unk028 % 180));
    }
    if (work->unk028 < 360) {
        if (work->unk028 < 180) {
            work->unk028 += 6;
        } else {
            work->unk028 += 18;
        }
        if (work->unk028 > 360) {
            work->unk028 = 360;
        }
    }
}

void fn_1_77D8(OMOBJ *obj)
{
    M569_BLOCK *work = obj->data;

    switch (work->unk004) {
        case 0:
            fn_1_75F8(obj);
            break;
        case 1:
            work->unk01C += 4.0f;
            if (work->unk01C > 360.0f) {
                work->unk01C -= 360.0f;
            }
            work->unk008.y = 270.0 + 5.0 * HuSin(work->unk01C);
            break;
        case 2:
            work->unk004 = 3;
            break;
        case 3:
            work->unk028++;
            Hu3DModelTPLvlSet(obj->mdlId[0], 1.0f - 0.2f * work->unk028);
            if (work->unk028 > 4) {
                work->unk028 = 0;
                fn_1_7F94(obj);
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
                work->unk02C = fn_1_74E0(&work->unk008);
                work->unk004 = 4;
            }
            break;
        case 4:
            break;
        case 5:
            work->unk028++;
            Hu3DModelTPLvlSet(obj->mdlId[1], 1.0f - 0.1f * work->unk028);
            if (work->unk028 == 10) {
                work->unk004 = 6;
            }
            return;
        case 6:
            Hu3DModelKill(obj->mdlId[0]);
            Hu3DModelKill(obj->mdlId[1]);
            if (work->unk02C != -1) {
                Hu3DParManKill(work->unk02C);
            }
            omDelObjEx(objman, obj);
            break;
    }
    if (work->unk004 <= 1) {
        work->unk027++;
        if (work->unk027 == 3) {
            work->unk027 = 0;
            work->unk026++;
            if (work->unk026 == 6) {
                work->unk026 = 0;
            }
            Hu3DMotionTimeSet(obj->mdlId[0], work->unk020[work->unk026]);
        }
    }
    omSetRot(obj, 0.0f, work->unk014, 0.0f);
    omSetTra(obj, work->unk008.x, work->unk008.y, work->unk008.z);
    omSetSca(obj, work->unk018, work->unk018, work->unk018);
}

OMOBJ *fn_1_7DC0(u8 type, HuVecF *pos)
{
    OMOBJ *obj;
    M569_BLOCK *work;
    HU3DMODELID modelId;
    int i;

    obj = omAddObjEx(objman, 0x2000, 2, 0, OM_GRP_NONE, fn_1_77D8);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M569_BLOCK), HU_MEMNUM_OVL);
    work = obj->data;
    work->unk008 = *pos;
    work->unk000 = type;
    work->unk018 = 0.0f;
    work->unk028 = 0;
    work->unk014 = 0;
    work->unk02C = -1;
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_rodata_198[work->unk000], HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[0] = modelId;
    Hu3DModelPosSetV(modelId, &work->unk008);
    Hu3DModelScaleSet(modelId, work->unk018, work->unk018, work->unk018);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    for (i = 0; i < 6; i++) {
        work->unk020[i] = lbl_1_data_320[type][i];
    }
    work->unk026 = frandmod(6);
    work->unk027 = 0;
    work->unk004 = 0;
    work->unk01C = (int)frandmod(360);
    omSetTra(obj, work->unk008.x, work->unk008.y, work->unk008.z);
    omSetSca(obj, work->unk018, work->unk018, work->unk018);
    return obj;
}

void fn_1_7F94(OMOBJ *obj)
{
    M569_BLOCK *work = obj->data;
    HU3DMODELID modelId;

    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m569, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(modelId, work->unk008.x, 270.0f, work->unk008.z);
    Hu3DModelLayerSet(modelId, 1);
    if (work->unk000 == 0) {
        Hu3DMotionTimeSet(modelId, work->unk020[work->unk026]);
    } else {
        Hu3DMotionTimeSet(modelId, work->unk020[work->unk026] + 6);
    }
    obj->mdlId[1] = modelId;
}

void fn_1_80AC(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        lbl_1_bss_158[i] = NULL;
    }
    lbl_1_bss_150 = -1;
}

void fn_1_80FC(void)
{
    OMOBJ *obj;
    int i;
    u8 type;

    for (i = 0; i < 3; i++) {
        type = lbl_1_data_350[i];
        obj = fn_1_7DC0(type, &lbl_1_data_32C[i]);
        lbl_1_bss_158[i] = obj->data;
    }
    lbl_1_bss_154 = 3;
    lbl_1_bss_150 = HuAudFXPlay(0x1D);
}

void fn_1_833C(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        lbl_1_bss_158[i]->unk004 = 5;
        lbl_1_bss_158[i]->unk028 = 0;
    }
}

void fn_1_839C(int no)
{
    M569_BLOCK **work = &lbl_1_bss_158[no];

    if (lbl_1_bss_158[no]->unk004 == 1) {
        lbl_1_bss_158[no]->unk004 = 2;
        lbl_1_bss_154--;
        if (lbl_1_bss_154 == 0) {
            if (lbl_1_bss_150 != -1) {
                HuAudFXStop(lbl_1_bss_150);
                lbl_1_bss_150 = -1;
            }
            HuAudFXPlay(0x1E);
        } else {
            HuAudFXPlay(0x21);
        }
    }
}

int fn_1_848C(int no)
{
    return lbl_1_bss_158[no]->unk004;
}

int fn_1_84A8(void)
{
    int list[3];
    int num;
    int i;

    num = 0;
    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_158[i]->unk004 == 1) {
            list[num++] = i;
        }
    }
    if (num) {
        return list[frandmod(num)];
    } else {
        return -1;
    }
}

int fn_1_8544(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_158[i] == NULL) {
            return 0;
        }
        if (lbl_1_bss_158[i]->unk004 != 1) {
            return 0;
        }
    }
    return 1;
}

int fn_1_85C0(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_158[i]->unk004 != 4) {
            return 0;
        }
    }
    return 1;
}

void fn_1_8614(void)
{
    int i;

    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_158[i]->unk004 == 1) {
            lbl_1_bss_158[i]->unk004 = 2;
        }
    }
    if (lbl_1_bss_150 != -1) {
        HuAudFXStop(lbl_1_bss_150);
        HuAudFXPlay(0x1E);
        lbl_1_bss_150 = -1;
    }
}

int fn_1_86C4(void)
{
    int result;
    u8 a;
    u8 b;
    u8 op;

    result = 0;
    a = lbl_1_bss_158[0]->unk020[lbl_1_bss_158[0]->unk026] + 1;
    b = lbl_1_bss_158[2]->unk020[lbl_1_bss_158[2]->unk026] + 1;
    op = lbl_1_bss_158[1]->unk020[lbl_1_bss_158[1]->unk026];
    switch (op) {
        case 1:
            result = a - b;
            if (result < 0) {
                result = 0;
            }
            break;
        case 0:
            result = a + b;
            break;
        case 2:
            result = a * b;
            break;
    }
    return result;
}
