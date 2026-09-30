/*
 * m503dll m503.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/m503.s.
 */

#include "REL/m503dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* float lbl_1_rodata_10 = 127.0f; */
/* 0x14 */ /* float lbl_1_rodata_14 = 0.0f; */
/* 0x18 */ /* float lbl_1_rodata_18 = 3000.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 70000.0f; */
/* 0x20 */ /* float lbl_1_rodata_20 = 45.0f; */
/* 0x24 */ /* float lbl_1_rodata_24 = 10.0f; */
/* 0x28 */ /* float lbl_1_rodata_28 = 30000.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 1.2f; */
/* 0x30 */ /* double lbl_1_rodata_30 = 6; */
/* 0x38 */ /* double lbl_1_rodata_38 = 4503599627370496; */
/* 0x40 */ /* float lbl_1_rodata_40 = 0.11111111f; */
/* 0x44 */ /* float lbl_1_rodata_44 = 32.0f; */
/* 0x48 */ /* double lbl_1_rodata_48 = -400; */
/* 0x50 */ /* double lbl_1_rodata_50 = 800; */
/* 0x58 */ /* float lbl_1_rodata_58 = 15.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 112.0f; */
/* 0x60 */ /* double lbl_1_rodata_60 = 0.5; */
/* 0x68 */ /* double lbl_1_rodata_68 = 3; */
/* 0x70 */ /* double lbl_1_rodata_70 = 57.295780181884766; */
/* 0x78 */ /* double lbl_1_rodata_78 = 3.141592653589793; */
/* 0x80 */ /* double lbl_1_rodata_80 = 180; */
/* 0x88 */ /* double lbl_1_rodata_88 = 96; */
/* 0x90 */ /* double lbl_1_rodata_90 = 1.0333333333333334; */
/* 0x98 */ /* double lbl_1_rodata_98 = 360; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 360.0f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 180.0f; */

/* --- .data --- */
/* 0x0 */ HuVecF lbl_1_data_0 = { 100.0f, 800.0f, -100.0f };   /* global light position */
/* 0xC */ HuVecF lbl_1_data_C = { 0.3f, -0.8f, 0.3f };         /* global light direction */
/* 0x18 */ HuVecF lbl_1_data_18 = { 20.0f, 45.0f, 1000.0f };   /* light rotation x, y and distance */
/* 0x24 */ GXColor lbl_1_data_24 = { 255, 255, 255, 255 };     /* global light colour */
/* 0x28 */ s32 lbl_1_data_28[9] = { 0x43480000, 0x453B8000, 0x42C80000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x4C */ float lbl_1_data_4C[4] = { 81.0f, 158.0f, 210.0f, 10000.0f };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x24 */ OMOBJMAN *lbl_1_bss_24;  /* the overlay's object manager */
/* 0x20 */ OMOBJ *lbl_1_bss_20;
/* 0x1C */ OMOBJ *lbl_1_bss_1C;
/* 0x18 */ s32 lbl_1_bss_18;       /* fn_1_1DD8: losers reported so far */
/* 0x16 gap_05_00000016_bss (0x2) -- dtk filler */
/* 0x14 */ HU3DLIGHTID lbl_1_bss_14; /* global light */
/* 0x10 */ s32 lbl_1_bss_10;       /* HuAudBGMPlay stream id, -1 when none */
/* 0xC */ s32 lbl_1_bss_C;         /* HuAudFXPlay(0x3A3) id, -1 when none */
/* 0x8 */ float lbl_1_bss_8;       /* ObjectSetup: 127.0f */
/* 0x6 */ s16 lbl_1_bss_6;
/* 0x4 */ s16 lbl_1_bss_4;
/* 0x0 */ MGTIMER *lbl_1_bss_0;

/* --- functions (reference order) --- */
/* 170 insns */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF target;
    HuVecF pos;
    OMOBJMAN *objman;
    HU3DLIGHT *light;

    lbl_1_bss_10 = -1;
    lbl_1_bss_C = -1;
    lbl_1_bss_8 = 127.0f;
    lbl_1_bss_0 = NULL;
    lbl_1_bss_14 = Hu3DGLightCreateV(&lbl_1_data_0, &lbl_1_data_C, &lbl_1_data_24);
    Hu3DGLightInfinitytSet(lbl_1_bss_14);
    light = &Hu3DGlobalLight[lbl_1_bss_14];
    light->type |= 0x8000;
    target.x = target.y = target.z = 0.0f;
    pos.x = pos.z = 0.0f;
    pos.y = lbl_1_data_18.z;
    mtxRot(mtx, lbl_1_data_18.x, lbl_1_data_18.y, 0.0f);
    PSMTXMultVec(mtx, &pos, &pos);
    Hu3DGLightPosAimSetV(lbl_1_bss_14, &pos, &target);
    objman = omInitObjMan(50, 0x2000);
    lbl_1_bss_24 = objman;
    omGameSysInit(objman);
    lbl_1_bss_18 = 0;
    lbl_1_bss_6 = lbl_1_bss_4 = -1;
    Hu3DFogSet(3000.0f, 70000.0f, 200, 200, 200);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 10.0f, 30000.0f, 1.2f);
    lbl_1_bss_1C = omAddObjEx(objman, 90, 0, 0, -1, fn_1_22FC);
    lbl_1_bss_20 = omAddObjEx(objman, 10, 0, 0, -1, fn_1_348);
    fn_1_D1B4(objman);
    fn_1_D7B0(objman);
    fn_1_C574(objman);
    fn_1_A6FC(objman);
    fn_1_3440(objman);
    fn_1_5810(objman);
}

/* 58 insns */
void fn_1_348(OMOBJ *obj)
{
    M503_MAIN *work;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_MAIN), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M503_MAIN));
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
    work->unk070 = 2;
    work->unk048[0] = work->unk048[1] = work->unk048[2] = work->unk048[3] = -1;
    work->unk074 = 0;
    work->unk078 = 0;
    work->unk07C = 0;
    obj->objFunc = fn_1_6D0;
}

/* 96 insns */
void fn_1_430(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    work->unk004++;
    work->unk014++;
    work->unk01C++;
    work->unk024++;
    if (work->unk00C == 0) {
        if (work->unk000 == 1U && work->unk014 > 6.0) {
            WipeCreate(1, 5, 60);
            work->unk00C = 1;
        }
    } else if (work->unk000 == 1U && work->unk014 == 24) {
        lbl_1_bss_10 = HuAudBGMPlay(81);
        lbl_1_bss_C = HuAudFXPlay(0x3A3);
    }
    if (omSysExitReq && work->unk000 != 5U) {
        work->unk000 = 4;
        if (lbl_1_bss_10 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_10, 1000);
            lbl_1_bss_10 = -1;
        }
        HuAudFadeOut(1000);
        fn_1_5B0(obj);
    }
}

/* 72 insns */
void fn_1_5B0(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    if (work->unk008 == 0) {
        switch (work->unk000) {
            case 0:
                work->unk000 = 1;
                work->unk014 = 0;
                obj->objFunc = fn_1_2D4C(lbl_1_bss_24);
                break;
            case 1:
                work->unk000 = 2;
                work->unk01C = 0;
                obj->objFunc = fn_1_10A4;
                break;
            case 2:
                work->unk000 = 3;
                work->unk024 = 0;
                obj->objFunc = fn_1_2E80(lbl_1_bss_24, obj);
                break;
            case 3:
            case 4:
                work->unk008 = 1;
                work->unk000 = 5;
                obj->objFunc = fn_1_A38;
                break;
            case 5:
            default:
                work->unk000 = 5;
                obj->objFunc = fn_1_DF4;
                break;
        }
        work->unk004 = 0;
    }
}

/* 218 insns */
void fn_1_6D0(OMOBJ *obj)
{
    fn_1_430(obj);
    fn_1_5B0(obj);
}

/* 239 insns */
void fn_1_A38(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    fn_1_430(obj);
    if (!WipeCheckEnd()) {
        WipeCreate(2, 6, 60);
        if (lbl_1_bss_C != -1) {
            HuAudFXFadeOut(lbl_1_bss_C, 1000);
            lbl_1_bss_C = -1;
        }
        work->unk008 = 0;
        fn_1_5B0(obj);
    }
}

/* 172 insns */
void fn_1_DF4(OMOBJ *obj)
{
    fn_1_430(obj);
    if (!WipeCheckEnd()) {
        fn_1_C598();
        fn_1_A78C();
        fn_1_5D4C();
        fn_1_34F4();
        fn_1_D838();
        fn_1_D23C();
        GameMesClose();
        HuAudFadeOut(1);
        omOvlReturnEx(1, 1);
    }
}

/* 212 insns */
void fn_1_10A4(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    fn_1_430(obj);
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
                obj->objFunc = fn_1_13F4;
            }
            break;
    }
}

/* 192 insns */
void fn_1_13F4(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;
    s32 done = FALSE;

    fn_1_430(obj);
    if (MgTimerDoneCheck(lbl_1_bss_0)) {
        done = TRUE;
    }
    if (done) {
        lbl_1_bss_4 = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_FINISH);
        if (lbl_1_bss_10 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_10, 100);
        }
        work->unk018 = 3;
        work->unk01C = 0;
        if (work->unk008 == 0) {
            obj->objFunc = fn_1_16F4;
        }
    }
}

/* 239 insns */
void fn_1_16F4(OMOBJ *obj)
{
    M503_MAIN *work = obj->data;

    if (lbl_1_bss_0 != NULL) {
        MgTimerKill(lbl_1_bss_0);
        lbl_1_bss_0 = NULL;
    }
    fn_1_430(obj);
    if (fn_1_1CB0() && work->unk074 == 0x1111) {
        work->unk018 = 4;
        work->unk01C = 0;
        fn_1_5B0(obj);
    }
}

/* 6 insns */
u32 fn_1_1AB0(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk000;
}

/* 6 insns */
u32 fn_1_1AC8(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk010;
}

/* 6 insns */
u32 fn_1_1AE0(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk018;
}

/* 6 insns */
u32 fn_1_1AF8(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk020;
}

/* 6 insns */
u32 fn_1_1B10(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk070;
}

/* 6 insns */
void fn_1_1B28(u32 flag)
{
    ((M503_MAIN *)lbl_1_bss_20->data)->unk070 = flag;
}

/* 12 insns */
s32 fn_1_1B40(s32 no)
{
    M503_MAIN *work = lbl_1_bss_20->data;
    return work->unk048[no];
}

/* 12 insns */
void fn_1_1B70(s32 no)
{
    ((M503_MAIN *)lbl_1_bss_20->data)->unk074 |= 1 << ((no & 3) * 4);
}

/* 23 insns */
void fn_1_1BA0(s32 no, u32 val)
{
    M503_MAIN *work = lbl_1_bss_20->data;
    s32 shift = (no & 3) * 4;
    work->unk078 &= ~(0xF << shift);
    work->unk078 |= val << shift;
}

/* 33 insns */
s32 fn_1_1BFC(s32 val)
{
    u32 flag = ((M503_MAIN *)lbl_1_bss_20->data)->unk078;

    switch (val) {
        case 0:
            return flag == 0;
        case 1:
            return flag == 0x1111;
        case 2:
            return flag == 0x2222;
    }
    return 0;
}

/* 12 insns */
void fn_1_1C80(s32 no)
{
    ((M503_MAIN *)lbl_1_bss_20->data)->unk07C |= 1 << ((no & 3) * 4);
}

/* 14 insns */
BOOL fn_1_1CB0(void)
{
    return !GameMesStatGet(lbl_1_bss_4);
}

/* 6 insns */
s32 fn_1_1CE8(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk058;
}

/* 6 insns */
u32 fn_1_1D00(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk05C;
}

/* 6 insns */
u32 *fn_1_1D18(void)
{
    return ((M503_MAIN *)lbl_1_bss_20->data)->unk060;
}

/* 26 insns */
s32 fn_1_1D30(void)
{
    if (lbl_1_bss_0 == NULL) {
        return 30;
    }
    return MgTimerValueGet(lbl_1_bss_0) / 60;
}

/* 16 insns */
void fn_1_1D98(s32 no, s32 arg1, s32 charNo)
{
    M503_MAIN *work = lbl_1_bss_20->data;
    no &= 3;
    work->unk028[no] = arg1;
    work->unk038[no] = charNo;
}

/* 31 insns */
void fn_1_1DD8(s32 no)
{
    M503_MAIN *work = lbl_1_bss_20->data;

    if (++lbl_1_bss_18 == 4) {
        CharLoseVoicePlay(work->unk038[0], work->unk038[1], work->unk038[2], work->unk038[3]);
    }
}

/* 23 insns */
s32 fn_1_1E54(float x)
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
s32 fn_1_1EB0(HuVecF *pos, s32 camId)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_1E54(out.x);
}

/* 37 insns */
s32 fn_1_1F44(HuVecF *pos)
{
    float z;
    s32 vol;

    z = (pos->z - -400.0) / 800.0;
    z *= 15.0f;
    vol = 112.0f + z;
    if (vol < 112) {
        vol = 112;
    }
    if (vol > 127) {
        vol = 127;
    }
    return vol;
}

/* 77 insns */
s32 fn_1_1FD8(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayVolPan(seNo, fn_1_1F44(pos), fn_1_1EB0(pos, 1));
}

/* 85 insns */
void fn_1_210C(s32 seId, HuVecF *pos)
{
    if (seId != -1 && HuAudFXStatusGet(seId) == 2) {
        HuAudFXPanning(seId, fn_1_1EB0(pos, 1));
        HuAudFXVolSet(seId, fn_1_1F44(pos));
    }
}

/* 39 insns */
void fn_1_2260(s32 seNo, float x)
{
    HuAudFXPlayPan(seNo, fn_1_1E54(x));
}

/* 22 insns */
void fn_1_22FC(OMOBJ *obj)
{
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_CAMERA), HU_MEMNUM_OVL);
    memset(obj->data, 0, sizeof(M503_CAMERA));
    obj->objFunc = fn_1_2354;
}

/* 398 insns */
void fn_1_2354(OMOBJ *obj)
{
    M503_CAMERA *work = obj->data;
    HuVecF pos;
    HuVecF target;
    HuVecF up;
    HuVecF dir;
    float rotX;
    float rotY;
    float rotZ;

    fn_1_2A08(obj);
    if (work->unk000 != 0) {
        fn_1_298C(obj);
        if (!Hu3DMotionEndCheck(work->unk00A)) {
            return;
        }
        Hu3DModelKill(work->unk00A);
        Hu3DCameraPosGet(1, &pos, &up, &target);
        Center = target;
        dir.x = pos.x - target.x;
        dir.y = pos.y - target.y;
        dir.z = pos.z - target.z;
        CRot.x = 57.29578f * atan2(-dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
        CRot.y = 57.29578f * atan2(dir.x, dir.z);
        CRot.z = 0.0f;
        CZoom = sqrtf((dir.z * dir.z) + ((dir.x * dir.x) + (dir.y * dir.y)));
        work->unk000 = 0;
    }
    rotX = CRot.x;
    rotY = CRot.y;
    rotZ = CRot.z;
    pos.x = Center.x + (CZoom * (HuSin(rotY) * HuCos(rotX)));
    pos.y = Center.y + (CZoom * -HuSin(rotX));
    pos.z = Center.z + (CZoom * (HuCos(rotY) * HuCos(rotX)));
    target.x = Center.x;
    target.y = Center.y;
    target.z = Center.z;
    up.x = HuSin(rotY) * HuSin(rotX);
    up.y = HuCos(rotX);
    up.z = HuCos(rotY) * HuSin(rotX);
    Hu3DCameraPosSet(1, pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
}

/* 31 insns */
void fn_1_298C(OMOBJ *obj)
{
    M503_CAMERA *work = obj->data;
    float time = Hu3DMotionTimeGet(work->unk00A);

    if (Hu3DMotionTimeGet(work->unk00A) > lbl_1_data_4C[work->unk004]) {
        work->unk004++;
        HuAudFXPlay(0x63D);
    }
}

/* 51 insns */
void fn_1_2A08(OMOBJ *obj)
{
    M503_CAMERA *work = obj->data;

    if (work->unk004 >= 3) {
        if (lbl_1_bss_8 > 96.0) {
            lbl_1_bss_8 -= 1.0333333333333334;
        }
        if (lbl_1_bss_C != -1) {
            HuAudFXVolSet(lbl_1_bss_C, (s32)lbl_1_bss_8);
        }
    }
}

/* 30 insns */
void fn_1_2AD4(void *data)
{
    OMOBJ *obj = lbl_1_bss_1C;
    M503_CAMERA *work = obj->data;

    work->unk008 = Hu3DMotionCreate(data);
    work->unk00A = Hu3DModelCameraCreate(work->unk008, 1);
    Hu3DCameraMotionStart(work->unk00A, 1);
    work->unk000 = 1;
    work->unk004 = 0;
}

/* 12 insns */
s32 fn_1_2B4C(void)
{
    OMOBJ *obj = lbl_1_bss_1C;
    M503_CAMERA *work = obj->data;

    return work->unk000;
}

/* 71 insns */
float fn_1_2B7C(float cur, float target, float rate)
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
float fn_1_2C98(float from, float to)
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

