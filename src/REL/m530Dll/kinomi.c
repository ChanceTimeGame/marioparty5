/*
 * m530Dll kinomi.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m530Dll/asm/REL/m530Dll/kinomi.s.
 */

#include "REL/m530Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xD8 */ /* float lbl_1_rodata_D8 = 0.0f; */
/* 0xDC */ /* float lbl_1_rodata_DC = 40.0f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 100.0f; */
/* 0xE8 */ /* double lbl_1_rodata_E8 = 4503601774854144; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 19.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 60.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 80.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 81.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 99.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 20.0f; */
/* 0x108 */ /* float lbl_1_rodata_108 = 39.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 59.0f; */
/* 0x110 */ /* float lbl_1_rodata_110 = 0.4f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 25.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 120.0f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 99999.0f; */

/* --- .data --- */
/* 0x150 */ char lbl_1_data_150[] = "itemhook_f1";
/* 0x15C */ char lbl_1_data_15C[] = "itemhook_f2";
/* 0x168 */ char lbl_1_data_168[] = "itemhook_f3";
/* 0x174 */ char lbl_1_data_174[] = "itemhook_f4";
/* 0x180 */ char lbl_1_data_180[] = "itemhook_f5";
/* 0x18C */ char lbl_1_data_18C[] = "itemhook_f6";
/* 0x198 */ char lbl_1_data_198[] = "itemhook_f7";
/* 0x1A4 */ char lbl_1_data_1A4[] = "itemhook_f8";
/* 0x1B0 */ char lbl_1_data_1B0[] = "itemhook_f9";
/* 0x1BC */ char lbl_1_data_1BC[] = "itemhook_f10";
/* 0x1C9 */ char lbl_1_data_1C9[] = "itemhook_f11";
/* 0x1D6 */ char lbl_1_data_1D6[] = "itemhook_f12";
/* 0x1E3 */ char lbl_1_data_1E3[] = "itemhook_f13";
/* 0x1F0 */ char lbl_1_data_1F0[] = "itemhook_f14";
/* 0x1FD */ char lbl_1_data_1FD[] = "itemhook_f15";
/* 0x20A */ char lbl_1_data_20A[] = "itemhook_f16";
/* 0x217 */ char lbl_1_data_217[] = "itemhook_f17";
/* 0x224 */ char lbl_1_data_224[] = "itemhook_f18";
/* 0x231 */ char lbl_1_data_231[] = "itemhook_f19";
/* 0x23E */ char lbl_1_data_23E[] = "itemhook_f20";
/* 0x24B */ char lbl_1_data_24B[] = "itemhook_f21";
/* 0x258 */ char *lbl_1_data_258[21] = { lbl_1_data_150, lbl_1_data_15C, lbl_1_data_168, lbl_1_data_174, lbl_1_data_180, lbl_1_data_18C, lbl_1_data_198, lbl_1_data_1A4, lbl_1_data_1B0, lbl_1_data_1BC, lbl_1_data_1C9, lbl_1_data_1D6, lbl_1_data_1E3, lbl_1_data_1F0, lbl_1_data_1FD, lbl_1_data_20A, lbl_1_data_217, lbl_1_data_224, lbl_1_data_231, lbl_1_data_23E, lbl_1_data_24B };
/* 0x2AC */ char lbl_1_data_2AC[] = "itemhook_ef";

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xCC */ s32 lbl_1_bss_CC;
/* 0xC4 */ s32 lbl_1_bss_C4[2]; /* 0x8: 4-aligned, retype */
/* 0xC0 */ s32 lbl_1_bss_C0;


/* --- functions (reference order) --- */
/* 248 insns */
void fn_1_45A0(void)
{
    OMOBJ *obj;
    s32 i;
    s32 j;
    s32 temp;

    for (i = 0; i < 21; i++) {
        obj = omAddObjEx(lbl_1_bss_B8, 0x3000, 0, 0, -1, fn_1_5360);
        obj->work[0] = i;
        lbl_1_bss_DC[i].unk01C = Hu3DModelCreateData(DATANUM(DATA_m530, 1));
        Hu3DModelLayerSet(lbl_1_bss_DC[i].unk01C, 2);
        Hu3DModelObjPosGet(lbl_1_bss_44[0], lbl_1_data_258[i], &lbl_1_bss_DC[i].unk004);
        Hu3DModelHookSet(lbl_1_bss_44[0], lbl_1_data_258[i], lbl_1_bss_DC[i].unk01C);
        Hu3D3Dto2D(&lbl_1_bss_DC[i].unk004, lbl_1_data_6C.no, &lbl_1_bss_DC[i].unk010);
        lbl_1_bss_DC[i].unk024 = lbl_1_bss_DC[i].unk004;
        lbl_1_bss_DC[i].unk000 = i;
        lbl_1_bss_DC[i].unk030.x = lbl_1_bss_DC[i].unk030.y = lbl_1_bss_DC[i].unk030.z = 0.0f;
        Hu3DModelAttrSet(lbl_1_bss_DC[i].unk01C, HU3D_ATTR_DISPOFF);
        lbl_1_bss_DC[i].unk01E = -1;
        lbl_1_bss_DC[i].unk020 = -1;
    }
    fn_1_4980(5);
    fn_1_4980(6);
    for (i = 0; i < 4;) {
        temp = frandmod(21);
        if (temp >= 2 && lbl_1_bss_DC[temp].unk03C == 0) {
            fn_1_4980(temp);
            i++;
        }
    }
    fn_1_439C(&lbl_1_bss_DC[0].unk024, &lbl_1_bss_DC[1].unk024, &lbl_1_bss_DC[20].unk024, &lbl_1_bss_D0);
    for (i = 0; i < 2; i++) {
        lbl_1_bss_C4[i] = frandmod(0x3FC) + 0xB4;
    }
    for (i = 0; i < 1; i++) {
        for (j = i + 1; j < 2; j++) {
            if (lbl_1_bss_C4[i] < lbl_1_bss_C4[j]) {
                temp = lbl_1_bss_C4[i];
                lbl_1_bss_C4[i] = lbl_1_bss_C4[j];
                lbl_1_bss_C4[j] = temp;
            }
        }
    }
    lbl_1_bss_CC = 0;
    lbl_1_bss_C0 = 0;
}

/* 38 insns */
void fn_1_4980(s32 idx)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[idx];
    kinomi->unk044 = 0;
    kinomi->unk03C = 2;
    kinomi->unk040 = 4;
    kinomi->unk04C = 0;
    kinomi->unk048 = frandmod(80);
    Hu3DModelAttrSet(kinomi->unk01C, HU3D_MOTATTR_PAUSE);
    Hu3DMotionTimeSet(kinomi->unk01C, 40.0f);
    Hu3DModelAttrReset(kinomi->unk01C, HU3D_ATTR_DISPOFF);
}

/* 26 insns */
s32 fn_1_4A18(void)
{
    s32 i;
    s32 num;
    s32 state;

    for (i = 0, num = 0; i < 21; i++) {
        state = lbl_1_bss_DC[i].unk03C;
        if (state >= 2 && state <= 4) {
            num++;
        }
    }
    return num;
}

/* 29 insns */
void fn_1_4A80(M530_KINOMI *kinomi, float time)
{
    Hu3DMotionTimeSet(kinomi->unk01C, time + 100.0f * kinomi->unk044);
}

/* 46 insns */
void fn_1_4AF4(M530_KINOMI *kinomi, float start, float end)
{
    Hu3DMotionStartEndSet(kinomi->unk01C, start + 100.0f * kinomi->unk044, end + 100.0f * kinomi->unk044);
}

/* 399 insns */
void fn_1_4BAC(M530_KINOMI *kinomi, s16 mot)
{
    Hu3DModelAttrReset(kinomi->unk01C, HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(kinomi->unk01C, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(kinomi->unk01C, HU3D_MOTATTR_REV);
    switch (mot) {
        case 0:
            fn_1_4AF4(kinomi, 0.0f, 19.0f);
            fn_1_4A80(kinomi, 0.0f);
            Hu3DModelAttrReset(kinomi->unk01C, HU3D_ATTR_DISPOFF);
            break;
        case 1:
            if ((s32)frandmod(2) == 0) {
                fn_1_4AF4(kinomi, 60.0f, 80.0f);
                fn_1_4A80(kinomi, 60.0f);
            }
            else {
                Hu3DModelAttrSet(kinomi->unk01C, HU3D_MOTATTR_REV);
                fn_1_4AF4(kinomi, 60.0f, 80.0f);
                fn_1_4A80(kinomi, 80.0f);
            }
            break;
        case 2:
            fn_1_4AF4(kinomi, 81.0f, 99.0f);
            fn_1_4A80(kinomi, 81.0f);
            break;
        case 3:
            fn_1_4AF4(kinomi, 20.0f, 39.0f);
            fn_1_4A80(kinomi, 20.0f);
            break;
        case 4:
            fn_1_4AF4(kinomi, 40.0f, 59.0f);
            fn_1_4A80(kinomi, 40.0f);
            break;
    }
}

/* 29 insns */
void fn_1_51E8(M530_KINOMI *kinomi)
{
    if (kinomi->unk044 == 1) {
        kinomi->unk01E = Hu3DModelCreateData(DATANUM(DATA_m530, 5));
        Hu3DModelAttrSet(kinomi->unk01E, HU3D_MOTATTR_LOOP);
        Hu3DModelHookSet(kinomi->unk01C, lbl_1_data_2AC, kinomi->unk01E);
    }
}

/* 21 insns */
void fn_1_525C(M530_KINOMI *kinomi)
{
    if (kinomi->unk01E != -1) {
        Hu3DModelHookObjReset(kinomi->unk01C, lbl_1_data_2AC);
        Hu3DModelKill(kinomi->unk01E);
        kinomi->unk01E = -1;
    }
}

/* 27 insns */
void fn_1_52B0(M530_KINOMI *kinomi)
{
    if (kinomi->unk020 == -1) {
        kinomi->unk020 = Hu3DModelCreateData(DATANUM(DATA_m530, 2));
        Hu3DModelPosSet(kinomi->unk020, kinomi->unk024.x, 0.0f, kinomi->unk024.z);
    }
}

/* 17 insns */
void fn_1_531C(M530_KINOMI *kinomi)
{
    if (kinomi->unk020 != -1) {
        Hu3DModelKill(kinomi->unk020);
        kinomi->unk020 = -1;
    }
}

/* 273 insns */
void fn_1_5360(OMOBJ *obj)
{
    s32 idx;
    M530_KINOMI *kinomi;

    idx = obj->work[0];
    kinomi = &lbl_1_bss_DC[obj->work[0]];
    if (kinomi->unk03C == 0) {
        return;
    }
    if (kinomi->unk03C == 2) {
        fn_1_57A4(obj);
    }
    switch (kinomi->unk03C) {
        case 0:
            break;
        case 1:
            fn_1_5BD4(obj);
            break;
        case 2:
            break;
        case 3:
            if (kinomi->unk040 == 4) {
                kinomi->unk03C = 4;
            }
            else {
                kinomi->unk03C = 5;
            }
            kinomi->unk04C = 0;
            break;
        case 4:
            if (kinomi->unk04C++ == 0) {
                fn_1_4BAC(kinomi, 1);
                fn_1_52B0(kinomi);
            }
            else if (Hu3DMotionEndCheck(kinomi->unk01C)) {
                kinomi->unk04C = 0;
                kinomi->unk03C = 5;
                Hu3DModelAttrReset(kinomi->unk01C, HU3D_MOTATTR_REV);
                Hu3DModelAttrSet(kinomi->unk01C, HU3D_MOTATTR_PAUSE);
            }
            break;
        case 5:
            fn_1_5E50(obj);
            break;
        case 6:
            fn_1_5FE8(obj);
            break;
        case 7:
            if (kinomi->unk04C++ >= 120) {
                kinomi->unk03C = 8;
                kinomi->unk04C = 0;
            }
            break;
        case 8:
            kinomi->unk04C++;
            if (kinomi->unk04C % 2) {
                Hu3DModelAttrSet(kinomi->unk01C, HU3D_ATTR_DISPOFF);
            }
            else {
                Hu3DModelAttrReset(kinomi->unk01C, HU3D_ATTR_DISPOFF);
            }
            if (kinomi->unk04C >= 20) {
                kinomi->unk03C = 9;
                kinomi->unk04C = 0;
            }
            break;
        case 9:
            fn_1_61A8(obj);
            break;
        case 10:
            fn_1_6280(obj);
            break;
    }
}

/* 268 insns */
void fn_1_57A4(OMOBJ *obj)
{
    s32 idx;
    M530_KINOMI *kinomi;

    idx = obj->work[0];
    kinomi = &lbl_1_bss_DC[obj->work[0]];
    if (MgSeqModeGet() < 5) {
        return;
    }
    switch (kinomi->unk040) {
        case 1:
            kinomi->unk048++;
            if (Hu3DMotionEndCheck(kinomi->unk01C)) {
                kinomi->unk048 = 0;
                kinomi->unk040 = 2;
            }
            break;
        case 2:
            if (kinomi->unk048++ >= 10) {
                fn_1_4BAC(kinomi, 3);
                kinomi->unk048 = 0;
                kinomi->unk040 = 3;
            }
            break;
        case 3:
            if (Hu3DMotionEndCheck(kinomi->unk01C)) {
                kinomi->unk048 = 0;
                kinomi->unk040 = 4;
                fn_1_51E8(kinomi);
            }
            break;
        case 4:
            if (MgSeqModeGet() != 8 && kinomi->unk048++ >= 160) {
                fn_1_4BAC(kinomi, 4);
                kinomi->unk048 = 0;
                kinomi->unk040 = 5;
                fn_1_525C(kinomi);
            }
            break;
        case 5:
            if (Hu3DMotionEndCheck(kinomi->unk01C)) {
                kinomi->unk048 = 0;
                kinomi->unk040 = 6;
            }
            break;
        case 6:
            if (kinomi->unk048++ >= 120) {
                kinomi->unk03C = 3;
                kinomi->unk048 = 0;
            }
            break;
    }
}

/* 159 insns */
void fn_1_5BD4(OMOBJ *obj)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[obj->work[0]];
    kinomi->unk03C = 2;
    kinomi->unk040 = 1;
    kinomi->unk04C = 0;
    kinomi->unk048 = 0;
    kinomi->unk024 = kinomi->unk004;
    kinomi->unk01E = -1;
    kinomi->unk020 = -1;
    kinomi->unk044 = 0;
    if ((u32)MgSeqTimerValueGet() < lbl_1_bss_C4[lbl_1_bss_CC]) {
        lbl_1_bss_CC++;
        kinomi->unk044 = 1;
    }
    if (MgSeqModeGet() == 8) {
        kinomi->unk044 = 1;
    }
    fn_1_4BAC(kinomi, 0);
    Hu3DMotionCalc(kinomi->unk01C);
    Hu3DModelPosSet(kinomi->unk01C, 0.0f, 0.0f, 0.0f);
    Hu3DModelHookSet(lbl_1_bss_44[0], lbl_1_data_258[kinomi->unk000], kinomi->unk01C);
}

/* 102 insns */
void fn_1_5E50(OMOBJ *obj)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[obj->work[0]];
    if (kinomi->unk04C++ == 0) {
        Hu3DModelHookObjReset(lbl_1_bss_44[0], lbl_1_data_258[kinomi->unk000]);
        kinomi->unk024 = kinomi->unk004;
        kinomi->unk030.y = 0.0f;
        Hu3DModelPosSetV(kinomi->unk01C, &kinomi->unk024);
        fn_1_52B0(kinomi);
        fn_1_1B78(&kinomi->unk024, 0x79C);
        return;
    }
    kinomi->unk030.y += 0.4f;
    kinomi->unk024.y -= kinomi->unk030.y;
    if (kinomi->unk024.y <= 25.0f) {
        kinomi->unk024.y = 25.0f;
        kinomi->unk04C = 0;
        if (kinomi->unk040 == 4) {
            kinomi->unk03C = 6;
        }
        else {
            kinomi->unk03C = 7;
            fn_1_6358(kinomi);
        }
    }
    Hu3DModelPosSetV(kinomi->unk01C, &kinomi->unk024);
}

/* 112 insns */
void fn_1_5FE8(OMOBJ *obj)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[obj->work[0]];
    if (kinomi->unk04C++ == 0) {
        fn_1_4BAC(kinomi, 2);
        fn_1_525C(kinomi);
    }
    else if (Hu3DMotionEndCheck(kinomi->unk01C)) {
        kinomi->unk03C = 9;
        kinomi->unk04C = 0;
    }
}

/* 54 insns */
void fn_1_61A8(OMOBJ *obj)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[obj->work[0]];
    Hu3DModelHookObjReset(lbl_1_bss_44[0], lbl_1_data_258[kinomi->unk000]);
    Hu3DModelAttrSet(kinomi->unk01C, HU3D_ATTR_DISPOFF);
    fn_1_525C(kinomi);
    fn_1_531C(kinomi);
    kinomi->unk03C = 0;
    kinomi->unk040 = 0;
    kinomi->unk04C = 0;
}

/* 54 insns */
void fn_1_6280(OMOBJ *obj)
{
    M530_KINOMI *kinomi;

    kinomi = &lbl_1_bss_DC[obj->work[0]];
    if (kinomi->unk04C % 2) {
        Hu3DModelAttrSet(kinomi->unk01C, HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrReset(kinomi->unk01C, HU3D_ATTR_DISPOFF);
    }
    kinomi->unk04C++;
    if (kinomi->unk04C >= 20.0f) {
        kinomi->unk03C = 9;
        kinomi->unk04C = 0;
    }
}

/* 42 insns */
void fn_1_6358(M530_KINOMI *kinomi)
{
    OMOBJ *obj;
    HU3DMODELID modelId;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m530, 6));
    obj = omAddObjEx(lbl_1_bss_B8, 0x3000, 1, 0, -1, fn_1_6400);
    obj->mdlId[0] = modelId;
    Hu3DModelLayerSet(modelId, 3);
    omSetTra(obj, kinomi->unk024.x, kinomi->unk024.y, kinomi->unk024.z);
}

/* 23 insns */
void fn_1_6400(OMOBJ *obj)
{
    if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(lbl_1_bss_B8, obj);
    }
}

/* 47 insns */
s32 fn_1_645C(HuVecF *pos, float range)
{
    s32 i;
    HuVecF dir;

    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk03C < 2 || lbl_1_bss_DC[i].unk03C > 7) {
            continue;
        }
        PSVECSubtract(pos, &lbl_1_bss_DC[i].unk024, &dir);
        if (PSVECMag(&dir) <= range) {
            return i;
        }
    }
    return -1;
}

/* 47 insns */
s32 fn_1_6518(HuVecF *pos, float range)
{
    s32 i;
    HuVecF dir;

    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk03C < 2 || lbl_1_bss_DC[i].unk03C >= 7) {
            continue;
        }
        PSVECSubtract(pos, &lbl_1_bss_DC[i].unk024, &dir);
        if (PSVECMag(&dir) <= range) {
            return i;
        }
    }
    return -1;
}

/* 65 insns */
s32 fn_1_65D4(HuVecF *pos, float range)
{
    s32 i;
    HuVecF dir;

    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk03C < 2 || lbl_1_bss_DC[i].unk03C > 7 || lbl_1_bss_DC[i].unk024.y - pos->y > 120.0f) {
            continue;
        }
        PSVECSubtract(pos, &lbl_1_bss_DC[i].unk024, &dir);
        dir.y = 0.0f;
        if (PSVECMag(&dir) <= range) {
            return i;
        }
    }
    return -1;
}

/* 26 insns */
s32 fn_1_66D8(s32 idx)
{
    if (lbl_1_bss_DC[idx].unk03C != 2) {
        return 0;
    }
    if (lbl_1_bss_DC[idx].unk040 < 4) {
        return 0;
    }
    lbl_1_bss_DC[idx].unk03C = 3;
    return 1;
}

/* 74 insns */
void fn_1_6740(void)
{
    s32 i;
    s32 num;
    s32 sel;
    s32 list[21];

    if (lbl_1_bss_C0++ >= 10) {
        for (i = 0, num = 0; i < 21; i++) {
            if (lbl_1_bss_DC[i].unk03C == 0) {
                list[num++] = i;
            }
        }
        if (num != 0) {
            if (fn_1_4A18() < 7) {
                sel = list[frandmod(num)];
                lbl_1_bss_DC[sel].unk03C = 1;
                lbl_1_bss_C0 = 0;
            }
        }
    }
}

/* 57 insns */
void fn_1_6868(void)
{
    s32 i;
    s32 num;
    s32 sel;
    s32 list[21];

    if (lbl_1_bss_C0++ >= 4) {
        for (i = 0, num = 0; i < 21; i++) {
            if (lbl_1_bss_DC[i].unk03C == 0) {
                list[num++] = i;
            }
        }
        if (num != 0) {
            sel = list[frandmod(num)];
            lbl_1_bss_DC[sel].unk03C = 1;
            lbl_1_bss_C0 = 0;
        }
    }
}

/* 13 insns */
void fn_1_694C(s32 idx)
{
    lbl_1_bss_DC[idx].unk04C = 0;
    lbl_1_bss_DC[idx].unk03C = 9;
}

/* 13 insns */
void fn_1_6980(s32 idx)
{
    lbl_1_bss_DC[idx].unk04C = 0;
    lbl_1_bss_DC[idx].unk03C = 8;
}

/* 36 insns */
void fn_1_69B4(void)
{
    s32 i;

    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk03C != 0 && lbl_1_bss_DC[i].unk03C != 9) {
            lbl_1_bss_DC[i].unk04C = 0;
            lbl_1_bss_DC[i].unk03C = 10;
        }
    }
}

/* 79 insns */
s32 fn_1_6A44(HuVecF *pos)
{
    s32 i;
    s32 best;
    float minDist;
    float dist;
    HuVecF bestPos;
    HuVecF dir;

    minDist = 99999.0f;
    best = -1;
    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk040 == 0 || lbl_1_bss_DC[i].unk040 >= 5) {
            continue;
        }
        PSVECSubtract(&lbl_1_bss_DC[i].unk024, pos, &dir);
        dist = PSVECMag(&dir);
        if (lbl_1_bss_DC[i].unk044 == 1) {
            dist = 0.0f;
        }
        if (dist < minDist) {
            best = i;
            minDist = dist;
            bestPos = lbl_1_bss_DC[i].unk024;
        }
    }
    return best;
}

/* 52 insns */
s32 fn_1_6B80(HuVecF *pos, s16 dif)
{
    s32 i;
    s32 num;
    s32 list[21];

    num = 0;
    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk040 != 0 && lbl_1_bss_DC[i].unk040 < 5 && lbl_1_bss_DC[i].unk03C == 2) {
            list[num++] = i;
        }
    }
    if (num == 0) {
        return -1;
    }
    return list[frandmod(num)];
}

/* 75 insns */
s32 fn_1_6C50(s32 mode, s32 exclude)
{
    s32 i;
    s32 num;
    s32 list[21];

    num = 0;
    for (i = 0; i < 21; i++) {
        if (lbl_1_bss_DC[i].unk03C < 4 || lbl_1_bss_DC[i].unk03C > 5 || lbl_1_bss_DC[i].unk040 < 4) {
            continue;
        }
        if (mode <= 1) {
            if (lbl_1_bss_DC[i].unk03C == 4) {
                continue;
            }
        }
        else if (lbl_1_bss_DC[i].unk040 != 4) {
            continue;
        }
        if (i == exclude) {
            continue;
        }
        list[num++] = i;
    }
    if (num == 0) {
        return -1;
    }
    return list[frandmod(num)];
}
