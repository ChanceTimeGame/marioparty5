/*
 * m530Dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m530Dll/asm/REL/m530Dll/player.s.
 */

#include "REL/m530Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/esprite.h"
#include "game/hsfex.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x120 */ /* float lbl_1_rodata_120 = 2.4444444f; */
/* 0x124 */ /* float lbl_1_rodata_124 = 0.0f; */
/* 0x128 */ /* float lbl_1_rodata_128 = 0.125f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 90.0f; */
/* 0x130 */ /* float lbl_1_rodata_130 = 490.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 50.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 214.0f; */
/* 0x140 */ /* double lbl_1_rodata_140 = 4503601774854144; */
/* 0x148 */ /* float lbl_1_rodata_148 = 59.0f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 60.0f; */
/* 0x150 */ /* float lbl_1_rodata_150 = 109.0f; */
/* 0x154 */ /* float lbl_1_rodata_154 = 30.0f; */
/* 0x158 */ /* float lbl_1_rodata_158 = 1.0f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 119.0f; */
/* 0x160 */ /* float lbl_1_rodata_160 = 3.0f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 360.0f; */
/* 0x168 */ /* s32 lbl_1_rodata_168[4] = { 0x00000050, 0x0000003C, 0x0000001E, 0x00000000 }; */
/* 0x178 */ /* float lbl_1_rodata_178 = 7.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 40.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 0.6f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 110.0f; */
/* 0x188 */ /* float lbl_1_rodata_188 = 940.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = -600.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 500.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = -150.0f; */
/* 0x198 */ /* float lbl_1_rodata_198 = 150.0f; */
/* 0x19C */ /* float lbl_1_rodata_19C = 1000.0f; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 180; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 3.141592653589793; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 164.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 3000.0f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 12.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 5.0f; */

/* --- .data --- */
/* 0x2E8 */ HuVecF lbl_1_data_2E8[2] = { { -4.5e+02f, 0.0f, 5.5e+02f }, { 4.5e+02f, 0.0f, 5.5e+02f } };
/* 0x300 */ HuVecF lbl_1_data_300 = { 0.0f, 5.7e+02f, -1e+02f };
/* 0x30C */ s32 lbl_1_data_30C[2] = { 0x0058000D, 0x0058000E };
/* 0x314 */ HuVecF lbl_1_data_314[2] = { { 243.0f, 143.0f, 0.0f }, { 333.0f, 143.0f, 0.0f } };
/* 0x32C */ s32 lbl_1_data_32C[2] = { 0x0058000A, 0x0058000B };
/* 0x334 */ char lbl_1_data_334[] = "itemhook_b";
/* 0x340 */ s32 lbl_1_data_340[2] = { 0x00580008, 0x00580009 };
/* 0x348 */ HuVecF lbl_1_data_348[2] = { { -1700.0f, 0.0f, 245.0f }, { 1700.0f, 0.0f, 245.0f } }; /* catcher start pos by side */
/* 0x360 */ HuVecF lbl_1_data_360[2] = { { -2e+02f, 0.0f, 245.0f }, { 2e+02f, 0.0f, 245.0f } };
/* 0x378 */ HuVecF lbl_1_data_378[2] = { { 0.0f, 9e+01f, 0.0f }, { 0.0f, -9e+01f, 0.0f } };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xDC */ M530_KINOMI lbl_1_bss_DC[21]; /* 0x690; type owned by fork K */
/* 0xD0 */ HuVecF lbl_1_bss_D0; /* plane normal (kinomi fn_1_439C) */

/* --- functions (reference order) --- */
/* 133 insns. Thrower init (fn_1_F4C, role 0). */
void fn_1_6D7C(OMOBJ *obj)
{
    M530_PLAYER *work;
    s16 side;
    HU3DMODELID mdlId;
    s16 espId;

    work = obj->data;
    side = work->grp;
    mdlId = CharModelMotListCreate(work->charNo, 2, lbl_1_data_C0, obj->mtnId);
    obj->mdlId[0] = mdlId;
    work->pos = lbl_1_data_2E8[side];
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    Hu3DModelShadowSet(mdlId);
    CharMotionSet(work->charNo, obj->mtnId[10]);
    CharMotionSpeedSet(work->charNo, 2.4444444f);
    Hu3DSubMotionSet(mdlId, obj->mtnId[9], 0.0f);
    Hu3DMotionShiftSpeedSet(mdlId, 2.4444444f);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x58000C, HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[2] = mdlId;
    work->unk034 = CharModelItemHookGet(work->charNo, 2, 1);
    Hu3DModelHookSet(obj->mdlId[0], work->unk034, mdlId);
    Hu3DMotionSpeedSet(mdlId, 2.4444444f);
    work->unk058 = lbl_1_data_314[side];
    espId = espEntry(lbl_1_data_30C[side], 0x100, 0);
    espDrawNoSet(espId, 0);
    espPosSet(espId, work->unk058.x, work->unk058.y);
    espDispOff(espId);
    work->unk054 = espId;
    fn_1_8398(&work->unk058, &work->unk064);
    fn_1_825C(obj);
    fn_1_7304(obj);
    work->unk044 = -1;
    work->unk03C = 0;
    work->unk040 = 0;
    obj->objFunc = fn_1_6F90;
}

/* 27 insns */
void fn_1_6F90(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    if (work->mode == 1) {
        fn_1_74B0(obj);
        work->unk038 = 0;
        work->mode = 2;
        obj->objFunc = fn_1_6FFC;
    }
    fn_1_7224(obj);
}

/* 138 insns */
void fn_1_6FFC(OMOBJ *obj)
{
    M530_PLAYER *work;
    s32 no;
    s16 vol;
    s16 pan;

    work = obj->data;
    no = work->no;
    fn_1_1A50(&work->pos, &vol, &pan);
    CharModelVoicePanSet(work->charNo, pan);
    CharModelVoiceVolSet(work->charNo, vol);
    fn_1_8398(&work->unk058, &work->unk064);
    if (MgSeqModeGet() == 6) {
        work->unk038 = 0;
        obj->objFunc = fn_1_7674;
        return;
    }
    fn_1_7224(obj);
    if (MgSeqModeGet() == 5) {
        if (work->comF) {
            fn_1_7900(obj);
        } else {
            work->unk058.x = work->unk058.x + 0.125f * HuPadStkX[work->padNo];
            work->unk058.y = work->unk058.y - 0.125f * HuPadStkY[work->padNo];
        }
        if (work->unk058.x < 90.0f) {
            work->unk058.x = 90.0f;
        }
        if (work->unk058.x > 490.0f) {
            work->unk058.x = 490.0f;
        }
        if (work->unk058.y < 50.0f) {
            work->unk058.y = 50.0f;
        }
        if (work->unk058.y > 214.0f) {
            work->unk058.y = 214.0f;
        }
        espPosSet(work->unk054, work->unk058.x, work->unk058.y);
        fn_1_825C(obj);
    }
}

/* 56 insns */
void fn_1_7224(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    switch (work->mode) {
        case 0:
            if (CharMotionEndCheck(work->charNo)) {
                work->mode = 1;
            }
            break;
        case 1:
            if (!work->comF && MgSeqModeGet() == 5 && (HuPadBtnDown[work->padNo] & PAD_BUTTON_A)) {
                fn_1_74B0(obj);
            }
            break;
        case 2:
            if (CharMotionEndCheck(work->charNo)) {
                fn_1_7304(obj);
                work->mode = 0;
            }
            break;
    }
}

/* 107 insns. Loads the next projectile into the thrower's hand. */
void fn_1_7304(OMOBJ *obj)
{
    M530_PLAYER *work;
    HU3DMODELID mdlId;
    OMOBJ *shotObj;
    M530_SHOT *shot;

    work = obj->data;
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_32C[work->grp], HU_MEMNUM_OVL, HEAP_MODEL));
    shotObj = omAddObjEx(lbl_1_bss_B8, 0x2000, 1, 0, -1, fn_1_7DD0);
    shotObj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M530_SHOT), HU_MEMNUM_OVL);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdlId, 2);
    Hu3DModelHookSet(obj->mdlId[2], lbl_1_data_334, mdlId);
    shotObj->mdlId[0] = mdlId;
    shot = shotObj->data;
    shot->unk000 = work->no;
    shot->unk028 = -1;
    shot->unk030 = 1;
    shot->unk034 = mdlId;
    work->unk070 = shot;
    CharMotionTimeSet(work->charNo, 0.0f);
    CharMotionStartEndSet(work->charNo, 0.0f, 59.0f);
    Hu3DMotionTimeSet(obj->mdlId[2], 0.0f);
    Hu3DMotionStartEndSet(obj->mdlId[2], 0.0f, 59.0f);
    Hu3DMotionShiftStartEndSet(obj->mdlId[0], 0.0f, 59.0f);
    Hu3DMotionShiftTimeSet(obj->mdlId[0], 0.0f);
}

/* 113 insns. Releases the held projectile toward the aim point. */
void fn_1_74B0(OMOBJ *obj)
{
    M530_PLAYER *work;
    M530_SHOT *shot;
    HuVecF dir;

    work = obj->data;
    shot = work->unk070;
    shot->unk030 = 0;
    shot->unk02C = 0;
    CharMotionTimeSet(work->charNo, 60.0f);
    CharMotionStartEndSet(work->charNo, 60.0f, 109.0f);
    Hu3DMotionTimeSet(obj->mdlId[2], 60.0f);
    Hu3DMotionStartEndSet(obj->mdlId[2], 60.0f, 109.0f);
    Hu3DMotionShiftStartEndSet(obj->mdlId[0], 60.0f, 109.0f);
    Hu3DMotionShiftTimeSet(obj->mdlId[0], 60.0f);
    Hu3DMotionCalc(obj->mdlId[0]);
    Hu3DMotionCalc(obj->mdlId[2]);
    Hu3DModelObjPosGet(obj->mdlId[0], lbl_1_data_334, &shot->unk004);
    Hu3DModelHookObjReset(obj->mdlId[2], lbl_1_data_334);
    PSVECSubtract(&work->unk064, &shot->unk004, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &shot->unk010, 30.0f);
    Hu3DModelPosSetV(shot->unk034, &shot->unk004);
    omVibrate(work->no, 12, 6, 6);
    work->unk038 = 0;
    work->mode = 2;
    if (work->grp == 0) {
        HuAudFXPlay(0x798);
    } else {
        HuAudFXPlay(0x799);
    }
}

/* 53 insns */
void fn_1_7674(OMOBJ *obj)
{
    M530_PLAYER *work;
    HuVecF pos;

    work = obj->data;
    if (work->unk038 == 0) {
        Hu3DModelObjPosGet(obj->mdlId[0], work->unk034, &pos);
        CharEffectSmokeCreate(lbl_1_data_6C.no, &pos);
        Hu3DModelAttrSet(obj->mdlId[2], HU3D_ATTR_DISPOFF);
        Hu3DSubMotionReset(obj->mdlId[0]);
        CharMotionSpeedSet(work->charNo, 1.0f);
        fn_1_10E8(obj, 0);
    }
    work->unk038++;
    if (work->unk038 == 60) {
        work->unk038 = 0;
        obj->objFunc = fn_1_7748;
    }
}

/* 110 insns */
void fn_1_7748(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    if (work->unk038++ == 0) {
        CharModelAttrReset(work->charNo, HU3D_MOTATTR_PAUSE);
        CharModelAttrReset(work->charNo, HU3D_MOTATTR_LOOP);
        CharMotionSet(work->charNo, obj->mtnId[11]);
        if (work->grp == 0) {
            CharMotionTimeSet(work->charNo, 0.0f);
            CharMotionStartEndSet(work->charNo, 0.0f, 59.0f);
        } else {
            CharMotionTimeSet(work->charNo, 60.0f);
            CharMotionStartEndSet(work->charNo, 60.0f, 119.0f);
        }
        return;
    }
    if (0.0f != work->rot.y) {
        if (work->grp == 0) {
            work->rot.y -= 3.0f;
            if (work->rot.y <= 0.0f) {
                work->rot.y = 0.0f;
            }
        } else {
            work->rot.y += 3.0f;
            if (work->rot.y >= 360.0f) {
                work->rot.y = 0.0f;
            }
        }
        omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    }
}

/* 54 insns. COM thrower. */
void fn_1_7900(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    if (work->unk044 != -1) {
        if (lbl_1_bss_DC[work->unk044].unk040 != 4) {
            work->unk03C = 0;
        }
        if (lbl_1_bss_DC[work->unk044].unk03C != 2) {
            work->unk03C = 0;
        }
    }
    switch (work->unk03C) {
        case 0:
            fn_1_79D8(obj);
            break;
        case 1:
            fn_1_7AFC(obj);
            break;
        case 2:
            fn_1_7BEC(obj);
            break;
    }
}

/* 73 insns. COM: wait, then pick a target. */
void fn_1_79D8(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;
    HuVecF d;
    s32 wait[4] = { 80, 60, 30, 0 };
    s32 idx;

    if (work->unk040++ > wait[work->dif]) {
        idx = fn_1_6B80(&work->unk064, work->dif);
        if (idx != -1) {
            work->unk040 = 0;
            work->unk044 = idx;
            work->unk048 = lbl_1_bss_DC[idx].unk010;
            PSVECSubtract(&work->unk048, &work->unk058, &d);
            d.z = 0.0f;
            if ((s32)PSVECMag(&d) == 0) {
                work->unk03C = 2;
            } else {
                work->unk03C = 1;
            }
        }
    }
}

/* 60 insns. COM: move the cursor toward the target. */
void fn_1_7AFC(OMOBJ *obj)
{
    M530_PLAYER *work;
    HuVecF d;
    float dist;

    work = obj->data;
    PSVECSubtract(&work->unk048, &work->unk058, &d);
    d.z = 0.0f;
    dist = PSVECMag(&d);
    if ((s32)dist == 0) {
        work->unk03C = 2;
    } else {
        PSVECNormalize(&d, &d);
        PSVECScale(&d, &d, 7.0f);
        if (PSVECMag(&d) > dist) {
            work->unk058 = work->unk048;
        } else {
            PSVECAdd(&work->unk058, &d, &work->unk058);
        }
    }
}

/* 121 insns. COM: throw (fn_1_74B0 inlined). */
void fn_1_7BEC(OMOBJ *obj)
{
    M530_PLAYER *work = obj->data;

    if (work->mode == 1) {
        fn_1_74B0(obj);
        work->unk03C = 0;
    }
}

/* 137 insns. Projectile object. */
void fn_1_7DD0(OMOBJ *obj)
{
    M530_SHOT *shot;
    HuVecF prev;
    float scale;
    s32 idx;

    shot = obj->data;
    if (shot->unk030 == 0) {
        shot->unk02C++;
        if (shot->unk02C == 100) {
            Hu3DModelKill(obj->mdlId[0]);
            omDelObjEx(lbl_1_bss_B8, obj);
            return;
        }
        if (shot->unk02C > 60) {
            scale = (100 - shot->unk02C) / 40.0f;
            omSetSca(obj, scale, scale, scale);
            if (scale <= 0.6f) {
                Hu3DModelKill(obj->mdlId[0]);
                omDelObjEx(lbl_1_bss_B8, obj);
                return;
            }
        }
        prev = shot->unk004;
        PSVECAdd(&shot->unk004, &shot->unk010, &shot->unk004);
        omSetTra(obj, shot->unk004.x, shot->unk004.y, shot->unk004.z);
        idx = fn_1_6518(&shot->unk004, 110.0f);
        if (idx != -1) {
            fn_1_1B78(&shot->unk004, 0x79A);
            shot->unk028 = idx;
            fn_1_66D8(idx);
            shot->unk02C = 0;
            obj->objFunc = fn_1_7FF4;
        } else if (fn_1_80C4(&prev, &shot->unk004)) {
            shot->unk02C = 0;
            fn_1_1B78(&shot->unk004, 0x79B);
            obj->objFunc = fn_1_7FF4;
        } else if (fn_1_81DC(&shot->unk004)) {
            shot->unk02C = 0;
            fn_1_1B78(&shot->unk004, 0x79B);
            obj->objFunc = fn_1_7FF4;
            return;
        }
    }
}

/* 52 insns */
void fn_1_7FF4(OMOBJ *obj)
{
    M530_SHOT *shot = obj->data;

    obj->work[0]++;
    if (obj->work[0] < 3) {
        PSVECAdd(&shot->unk004, &shot->unk010, &shot->unk004);
        omSetTra(obj, shot->unk004.x, shot->unk004.y, shot->unk004.z);
    }
    if (shot->unk02C++ == 0) {
        Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    } else if (Hu3DMotionEndCheck(obj->mdlId[0])) {
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(lbl_1_bss_B8, obj);
    }
}

/* 70 insns. Did the step from..to cross the back plane inside the target ring? */
s32 fn_1_80C4(HuVecF *from, HuVecF *to)
{
    HuVecF cross;
    HuVecF d;

    if (!fn_1_4458(&lbl_1_bss_D0, &lbl_1_bss_DC[0].unk004, from, to, &cross)) {
        return 0;
    }
    if (fn_1_4414(&lbl_1_bss_D0, &lbl_1_bss_DC[0].unk004, from) < 0.0f) {
        return 0;
    }
    if (fn_1_4414(&lbl_1_bss_D0, &lbl_1_bss_DC[0].unk004, to) > 0.0f) {
        return 0;
    }
    PSVECSubtract(&cross, &lbl_1_data_300, &d);
    if (PSVECMag(&d) <= 940.0f) {
        return 1;
    }
    return 0;
}

/* 32 insns */
s32 fn_1_81DC(HuVecF *pos)
{
    if (pos->z > -600.0f) {
        return 0;
    }
    if (pos->y > 500.0f) {
        return 0;
    }
    if (pos->x < -150.0f || pos->x > 150.0f) {
        return 0;
    }
    return 1;
}

/* 79 insns. Faces the thrower at the aim point; sub-motion by cursor height. */
void fn_1_825C(OMOBJ *obj)
{
    M530_PLAYER *work;
    float ang;
    float dx;
    float t;
    float dz;

    work = obj->data;
    dx = work->unk064.x - work->pos.x;
    dz = work->unk058.z - (1000.0f + work->pos.z);
    ang = HuAtan(dx, dz);
    if (ang < 0.0f) {
        ang += 360.0f;
    }
    work->rot.y = ang;
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    t = (214.0f - work->unk058.y) / 164.0f;
    Hu3DSubMotionTimeSet(obj->mdlId[0], t);
}

/* 39 insns. Screen cursor -> point on the plane. */
void fn_1_8398(HuVecF *cursor, HuVecF *out)
{
    HuVecF pos;
    HuVecF world;

    pos = *cursor;
    pos.z = 3000.0f;
    Hu3D2Dto3D(&pos, lbl_1_data_6C.no, &world);
    fn_1_4458(&lbl_1_bss_D0, &lbl_1_bss_DC[0].unk004, &lbl_1_data_6C.pos, &world, out);
}

/* 104 insns. Catcher init (fn_1_F4C, role 1). */
void fn_1_8434(OMOBJ *obj)
{
    M530_PLAYER *work;
    HU3DMODELID mdlId;

    work = obj->data;
    mdlId = CharModelMotListCreate(work->charNo, 2, lbl_1_data_C0, obj->mtnId);
    obj->mdlId[0] = mdlId;
    work->pos = lbl_1_data_348[work->grp];
    work->rot = lbl_1_data_378[work->grp];
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    work->unk084 = work->rot.y;
    work->unk088 = 0;
    work->unk044 = -1;
    work->unk03C = 0;
    work->unk074 = 0;
    work->unk040 = 0;
    Hu3DModelShadowSet(mdlId);
    CharModelAttrSet(work->charNo, HU3D_MOTATTR_LOOP);
    CharMotionSet(work->charNo, obj->mtnId[5]);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_340[work->grp], HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[1] = mdlId;
    work->unk034 = CharModelItemHookGet(work->charNo, 2, 0);
    Hu3DModelHookSet(obj->mdlId[0], work->unk034, mdlId);
    obj->objFunc = fn_1_85D4;
}

/* 66 insns. Catcher: step in until effect fn_1_8E2C reports contact. */
void fn_1_85D4(OMOBJ *obj)
{
    M530_PLAYER *work;
    HuVecF pos;

    work = obj->data;
    pos = work->pos;
    if (work->grp == 0) {
        pos.x += 12.0f;
    } else {
        pos.x -= 12.0f;
    }
    if (fn_1_8E2C(work, &pos)) {
        HuAudFXPlay(0x7A0);
        fn_1_10E8(obj, 6);
        fn_1_8848();
        omVibrate(work->no, 12, 12, 0);
        obj->objFunc = fn_1_86DC;
    } else {
        work->pos = pos;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
}

/* 72 insns. Catcher: walk back to lbl_1_data_360[side]. */
void fn_1_86DC(OMOBJ *obj)
{
    M530_PLAYER *work;
    s32 done;

    work = obj->data;
    done = 0;
    if (work->grp == 0) {
        work->pos.x -= 5.0f;
        if (work->pos.x < lbl_1_data_360[work->grp].x) {
            done = 1;
        }
    } else {
        work->pos.x += 5.0f;
        if (work->pos.x > lbl_1_data_360[work->grp].x) {
            done = 1;
        }
    }
    if (done) {
        work->pos.x = lbl_1_data_360[work->grp].x;
        fn_1_10E8(obj, 7);
        obj->objFunc = fn_1_87FC;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
}

/* 19 insns */
void fn_1_87FC(OMOBJ *obj)
{
    if (MgSeqModeGet() == 3) {
        fn_1_10E8(obj, 3);
        obj->objFunc = fn_1_8958;
    }
}
