/*
 * m516dll m516.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m516Dll/asm/REL/m516Dll/m516.s.
 */

#include "REL/m516Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/mg/timer.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s32 lbl_1_rodata_10[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C */ /* s32 lbl_1_rodata_1C[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x28 */ /* float lbl_1_rodata_28 = 0.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 45.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 10.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 30000.0f; */
/* 0x38 */ /* float lbl_1_rodata_38 = 1.2f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 0.11111111f; */
/* 0x40 */ /* float lbl_1_rodata_40 = 32.0f; */
/* 0x48 */ /* double lbl_1_rodata_48 = 360; */
/* 0x50 */ /* float lbl_1_rodata_50 = 360.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 180.0f; */

/* --- .data --- */
/* 0x0 */ HuVecF lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };     /* global light position */
/* 0xC */ HuVecF lbl_1_data_C = { 0.3f, -0.8f, 0.3f };           /* global light direction */
/* 0x18 */ HuVecF lbl_1_data_18 = { 20.0f, 45.0f, 1000.0f };     /* light rotation x, y and distance */
/* 0x24 */ GXColor lbl_1_data_24 = { 255, 255, 255, 255 };       /* global light colour */
/* 0x28 */ s32 lbl_1_data_28[9] = { 0x43480000, 0x453B8000, 0x42C80000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x1C */ OMOBJMAN *lbl_1_bss_1C;   /* the overlay's object manager */
/* 0x18 */ OMOBJ *lbl_1_bss_18;     /* the main object; its data is M516_MAIN */
/* 0x14 */ OMOBJ *lbl_1_bss_14;     /* omOutView */
/* 0x10 */ s32 lbl_1_bss_10;        /* fn_1_1A20: losers reported so far */
/* 0xE gap_05_0000000E_bss (0x2) -- dtk filler */
/* 0xC */ HU3DLIGHTID lbl_1_bss_C;  /* global light */
/* 0x8 */ s32 lbl_1_bss_8;          /* HuAudBGMPlay stream id, -1 when none */
/* 0x6 */ s16 lbl_1_bss_6;          /* "START" GameMes id */
/* 0x4 */ s16 lbl_1_bss_4;          /* "FINISH" GameMes id */
/* 0x0 */ MGTIMER *lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 164 insns */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF unused0 = { 0.0f, 0.0f, 0.0f };
    HuVecF unused1 = { 0.0f, 0.0f, -1.0f };
    HuVecF target;
    HuVecF pos;
    OMOBJMAN *objman;
    HU3DLIGHT *light;

    lbl_1_bss_8 = -1;
    lbl_1_bss_0 = NULL;
    lbl_1_bss_C = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_C);
    light = &Hu3DGlobalLight[lbl_1_bss_C];
    light->type |= 0x8000;
    target.x = target.y = target.z = 0.0f;
    pos.x = pos.z = 0.0f;
    pos.y = lbl_1_data_18.z;
    mtxRot(mtx, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    PSMTXMultVec(mtx, &pos, &pos);
    Hu3DGLightPosAimSetV(lbl_1_bss_C, &pos, &target);
    objman = omInitObjMan(50, 0x2000);
    lbl_1_bss_1C = objman;
    omGameSysInit(objman);
    lbl_1_bss_10 = 0;
    lbl_1_bss_6 = lbl_1_bss_4 = -1;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 10.0f, 30000.0f, 1.2f);
    lbl_1_bss_14 = omAddObjEx(objman, 32730, 0, 0, -1, omOutView);
    lbl_1_bss_18 = omAddObjEx(objman, 10, 0, 0, -1, fn_1_330);
    fn_1_79F8(objman);
    fn_1_80C0(objman);
    fn_1_6F24(objman);
    fn_1_48CC(objman);
    fn_1_254C(objman);
}

/* 56 insns */
void fn_1_330(OMOBJ *obj)
{
    M516_MAIN *work;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M516_MAIN), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M516_MAIN));
    work->unk000 = 0;
    work->unk004 = 0;
    work->unk010 = 0;
    work->unk014 = 0;
    work->unk018 = 0;
    work->unk01C = 0;
    work->unk020 = 0;
    work->unk024 = 0;
    work->unk008 = 0;
    work->unk00C = 0;
    work->unk058 = 1;
    work->unk048[0] = work->unk048[1] = work->unk048[2] = work->unk048[3] = -1;
    work->unk05C = 0;
    work->unk060 = 0;
    obj->objFunc = fn_1_654;
}

/* 69 insns */
void fn_1_410(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;

    work->unk004++;
    work->unk014++;
    work->unk01C++;
    work->unk024++;
    if (lbl_1_bss_8 == -1 && work->unk000 == 1U && work->unk014 == 18) {
        lbl_1_bss_8 = HuAudBGMPlay(84);
    }
    if (omSysExitReq && work->unk000 != 5U) {
        work->unk000 = 4;
        if (lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 1000);
            lbl_1_bss_8 = -1;
        }
        HuAudFadeOut(1000);
        fn_1_524(obj);
    }
}

/* 76 insns */
void fn_1_524(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;

    if (work->unk008 == 0) {
        switch (work->unk000) {
            case 0:
                WipeCreate(1, 5, 60);
                work->unk000 = 1;
                work->unk014 = 0;
                obj->objFunc = fn_1_1F04(lbl_1_bss_1C);
                break;
            case 1:
                work->unk000 = 2;
                work->unk01C = 0;
                obj->objFunc = fn_1_EF8;
                break;
            case 2:
                work->unk000 = 3;
                work->unk024 = 0;
                obj->objFunc = fn_1_2108(lbl_1_bss_1C, obj);
                break;
            case 3:
            case 4:
                work->unk008 = 1;
                work->unk000 = 5;
                obj->objFunc = fn_1_970;
                break;
            case 5:
            default:
                work->unk000 = 5;
                obj->objFunc = fn_1_CA8;
                break;
        }
        work->unk004 = 0;
    }
}

/* 199 insns */
void fn_1_654(OMOBJ *obj)
{
    fn_1_410(obj);
    fn_1_524(obj);
}

/* 206 insns */
void fn_1_970(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;

    fn_1_410(obj);
    if (!WipeCheckEnd()) {
        WipeCreate(2, 6, 60);
        work->unk008 = 0;
        fn_1_524(obj);
    }
}

/* 148 insns */
void fn_1_CA8(OMOBJ *obj)
{
    fn_1_410(obj);
    if (!WipeCheckEnd()) {
        fn_1_6F80();
        fn_1_495C();
        fn_1_2600();
        fn_1_8148();
        fn_1_7A80();
        GameMesClose();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

/* 189 insns */
void fn_1_EF8(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;

    fn_1_410(obj);
    switch (work->unk018) {
        case 0:
            lbl_1_bss_6 = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_START);
            work->unk018 = 1;
            work->unk01C = 0;
            break;
        case 1:
            if (!GameMesStatGet(lbl_1_bss_6) && work->unk008 == 0) {
                lbl_1_bss_0 = MgTimerCreate(0);
                MgTimerParamSet(lbl_1_bss_0, 1800, 0, 0);
                MgTimerModeOnSet(lbl_1_bss_0, 1);
                work->unk018 = 2;
                work->unk01C = 0;
                obj->objFunc = fn_1_11EC;
            }
            break;
    }
}

/* 177 insns */
void fn_1_11EC(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;
    s32 done = FALSE;

    fn_1_410(obj);
    if (MgTimerDoneCheck(lbl_1_bss_0)) {
        done = TRUE;
    }
    if (fn_1_6D78() <= 0) {
        done = TRUE;
    }
    if (done) {
        lbl_1_bss_4 = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_FINISH);
        if (lbl_1_bss_8 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_8, 100);
            lbl_1_bss_8 = -1;
        }
        work->unk018 = 3;
        work->unk01C = 0;
        if (work->unk008 == 0) {
            obj->objFunc = fn_1_14B0;
        }
    }
}

/* 220 insns */
void fn_1_14B0(OMOBJ *obj)
{
    M516_MAIN *work = obj->data;

    if (lbl_1_bss_0 != NULL) {
        MgTimerKill(lbl_1_bss_0);
        lbl_1_bss_0 = NULL;
    }
    fn_1_410(obj);
    if (fn_1_1940() && work->unk05C == 0x1111) {
        work->unk018 = 4;
        work->unk01C = 0;
        fn_1_524(obj);
    }
}

/* 6 insns */
u32 fn_1_1820(void)
{
    return ((M516_MAIN *)lbl_1_bss_18->data)->unk000;
}

/* 6 insns */
u32 fn_1_1838(void)
{
    return ((M516_MAIN *)lbl_1_bss_18->data)->unk010;
}

/* 6 insns */
u32 fn_1_1850(void)
{
    return ((M516_MAIN *)lbl_1_bss_18->data)->unk018;
}

/* 6 insns */
u32 fn_1_1868(void)
{
    return ((M516_MAIN *)lbl_1_bss_18->data)->unk020;
}

/* 6 insns */
s32 fn_1_1880(void)
{
    return ((M516_MAIN *)lbl_1_bss_18->data)->unk058;
}

/* 6 insns */
void fn_1_1898(s32 arg0)
{
    ((M516_MAIN *)lbl_1_bss_18->data)->unk058 = arg0;
}

/* 12 insns */
s32 fn_1_18B0(s32 no)
{
    M516_MAIN *work = lbl_1_bss_18->data;
    return work->unk048[no];
}

/* 12 insns */
void fn_1_18E0(s32 no)
{
    ((M516_MAIN *)lbl_1_bss_18->data)->unk05C |= 1 << ((no & 3) * 4);
}

/* 12 insns */
void fn_1_1910(s32 no)
{
    ((M516_MAIN *)lbl_1_bss_18->data)->unk060 |= 1 << ((no & 3) * 4);
}

/* 14 insns */
BOOL fn_1_1940(void)
{
    return !GameMesStatGet(lbl_1_bss_4);
}

/* 26 insns */
s32 fn_1_1978(void)
{
    if (lbl_1_bss_0 == NULL) {
        return 30;
    }
    return MgTimerValueGet(lbl_1_bss_0) / 60;
}

/* 16 insns */
void fn_1_19E0(s32 no, s32 arg1, s32 charNo)
{
    M516_MAIN *work = lbl_1_bss_18->data;
    no &= 3;
    work->unk028[no] = arg1;
    work->unk038[no] = charNo;
}

/* 31 insns */
void fn_1_1A20(s32 no)
{
    M516_MAIN *work = lbl_1_bss_18->data;

    if (++lbl_1_bss_10 == 4) {
        CharLoseVoicePlay(work->unk038[0], work->unk038[1], work->unk038[2], work->unk038[3]);
    }
}

/* 23 insns */
s32 fn_1_1A9C(float x)
{
    s32 pan;
    x *= (64.0f / 576.0f);
    pan = 32.0f + x;
    if (pan < 32) {
        pan = 32;
    }
    if (pan > 96) {
        pan = 96;
    }
    return pan;
}

/* 37 insns */
s32 fn_1_1AF8(HuVecF *pos, s32 camId)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_1A9C(out.x);
}

/* 53 insns */
s32 fn_1_1B8C(s32 seNo, HuVecF *pos)
{
    s32 pan = fn_1_1AF8(pos, 1);

    if (pan == -1) {
        return -1;
    }
    return HuAudFXPlayPan(seNo, pan);
}

/* 53 insns */
void fn_1_1C60(s32 seId, HuVecF *pos)
{
    s32 pan;

    if (seId != -1 && HuAudFXStatusGet(seId) == 2) {
        pan = fn_1_1AF8(pos, 1);
        if (pan != -1) {
            HuAudFXPanning(seId, pan);
        }
    }
}

/* 71 insns */
float fn_1_1D34(float cur, float target, float rate)
{
    float d;
    float e;
    float r;

    d = fmod(target - cur, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    e = fmod(cur + rate * r, 360.0);
    r = e;
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* 45 insns */
float fn_1_1E50(float from, float to)
{
    float d;
    float r;

    d = fmod(to - from, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    return r;
}

