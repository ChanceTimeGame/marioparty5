/*
 * m503dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m503Dll/asm/REL/m503Dll/player.s.
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
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 0.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 150.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 40.0f; */
/* 0xF0 */ /* double lbl_1_rodata_F0 = 180; */
/* 0xF8 */ /* double lbl_1_rodata_F8 = 3.141592653589793; */
/* 0x100 */ /* double lbl_1_rodata_100 = 0.5; */
/* 0x108 */ /* double lbl_1_rodata_108 = 3; */
/* 0x110 */ /* float lbl_1_rodata_110 = 0.017857144f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 1.0f; */
/* 0x118 */ /* double lbl_1_rodata_118 = 4503601774854144; */
/* 0x120 */ /* double lbl_1_rodata_120 = 300; */
/* 0x128 */ /* float lbl_1_rodata_128 = 120.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = -200.0f; */
/* 0x130 */ /* double lbl_1_rodata_130 = 85; */
/* 0x138 */ /* double lbl_1_rodata_138 = 170; */
/* 0x140 */ /* double lbl_1_rodata_140 = 10; */
/* 0x148 */ /* double lbl_1_rodata_148 = 150; */
/* 0x150 */ /* float lbl_1_rodata_150 = 1.2f; */
/* 0x158 */ /* double lbl_1_rodata_158 = 50; */
/* 0x160 */ /* float lbl_1_rodata_160 = 0.8f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 0.4f; */
/* 0x168 */ /* float lbl_1_rodata_168 = 30.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = 100.0f; */
/* 0x170 */ /* double lbl_1_rodata_170 = 360; */
/* 0x178 */ /* double lbl_1_rodata_178 = 0; */
/* 0x180 */ /* double lbl_1_rodata_180 = 30; */
/* 0x188 */ /* double lbl_1_rodata_188 = 20; */
/* 0x190 */ /* double lbl_1_rodata_190 = -20; */
/* 0x198 */ /* float lbl_1_rodata_198 = 0.2f; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 4503599627370496; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 1; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 0.7; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 0.05f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 0.3f; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 0.01666666753590107; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = 550; */
/* 0x1D0 */ /* float lbl_1_rodata_1D0 = 0.5f; */
/* 0x1D4 */ /* float lbl_1_rodata_1D4 = 0.45f; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 45.0f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 15.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 10.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 20.0f; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 1.2; */
/* 0x1F0 */ /* float lbl_1_rodata_1F0 = 90.0f; */
/* 0x1F8 */ /* double lbl_1_rodata_1F8 = 100; */
/* 0x200 */ /* double lbl_1_rodata_200 = 3.2; */
/* 0x208 */ /* float lbl_1_rodata_208 = 0.7f; */
/* 0x210 */ /* double lbl_1_rodata_210 = 0.0000152587890625; */
/* 0x218 */ /* double lbl_1_rodata_218 = 4; */
/* 0x220 */ /* double lbl_1_rodata_220 = 190; */
/* 0x228 */ /* double lbl_1_rodata_228 = 240; */
/* 0x230 */ /* float lbl_1_rodata_230 = 60.0f; */
/* 0x234 */ /* float lbl_1_rodata_234 = 100000.0f; */
/* 0x238 */ /* float lbl_1_rodata_238[2] = { 360.0f, 0.0f }; */

/* --- .data --- */
/* 0xA8 */ s32 lbl_1_data_A8[8] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0006, 0x008C0007, 0x008C0028, 0x008C0026, 0x008C0027 };
/* 0xC8 */ M503_PLAYERMOT lbl_1_data_C8[10] = {
    { 0, -1, 0.2f, HU3D_MOTATTR_LOOP },
    { 1, -1, 0.2f, HU3D_MOTATTR_LOOP },
    { 2, -1, 0.2f, HU3D_MOTATTR_LOOP },
    { 3, -1, 0.2f, HU3D_MOTATTR_NONE },
    { 4, -1, 0.2f, HU3D_MOTATTR_NONE },
    { 0, 5, 0.2f, HU3D_MOTATTR_NONE },
    { 0, 6, 0.2f, HU3D_MOTATTR_LOOP },
    { 1, 6, 0.2f, HU3D_MOTATTR_LOOP },
    { 2, 7, 0.2f, HU3D_MOTATTR_LOOP },
    { 0, 5, 0.2f, HU3D_MOTATTR_REV },
};
/* 0x140 */ HuVecF lbl_1_data_140[4] = { { -300.0f, 0.0f, 0.0f }, { -100.0f, 0.0f, 0.0f }, { 100.0f, 0.0f, 0.0f }, { 300.0f, 0.0f, 0.0f } };
/* 0x170 */ M503_PLAYERCOM lbl_1_data_170[4] = {
    { 0.3f, 40.0f, 120.0f, 60, 60, 480, 0.65f },
    { 0.8f, 60.0f, 180.0f, 51, 51, 300, 0.8f },
    { 0.9f, 70.0f, 200.0f, 48, 48, 240, 0.85f },
    { 1.0f, 100.0f, 300.0f, 42, 42, 180, 0.9f },
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x30 */ OMOBJ *lbl_1_bss_30[4]; /* 0x10: 4-aligned, retype */

/* --- functions (reference order) --- */
/* 45 insns */
void fn_1_3440(OMOBJMAN *objman)
{
    OMOBJ *obj;
    s32 i;

    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_30[i] = omAddObjEx(objman, 30, 1, 8, 0, fn_1_3518);
        obj->work[0] = i;
        obj->work[1] = GwPlayerConf[i].grp;
        obj->work[2] = i;
    }
}

/* 9 insns */
void fn_1_34F4(void)
{
    CharModelKill(-1);
}

/* 170 insns */
void fn_1_3518(OMOBJ *obj)
{
    M503_PLAYER *work;
    M503_ACTORENT *hit;
    s32 i;
    s32 no;
    s32 slot;
    HU3DMODELID mdlId;
    s32 charNo;
    s32 ret;
    HU3DMOTID motId;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M503_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M503_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = no = obj->work[0];
    work->unk004 = obj->work[1];
    slot = work->unk008 = obj->work[2];
    charNo = GwPlayerConf[no].charNo;
    work->unk00C = charNo;
    fn_1_1D98(no, work->unk004, work->unk00C);
    work->unk02C = GwPlayerConf[no].dif & 3;
    work->unk028 = GwPlayerConf[no].type;
    work->unk030 = 0;
    mdlId = CharModelCreate(charNo, 8);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 3);
    for (i = 0; i < 8; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_A8[i]);
        obj->mtnId[i] = motId;
    }
    CharMotionDataClose(charNo);
    work->unk010 = -1;
    fn_1_4E94(obj, 0);
    ret = CharNpcDustVoiceOffSet(mdlId, obj->mtnId[1], 0);
    ret = CharNpcDustVoiceOffSet(mdlId, obj->mtnId[2], 1);
    ret = CharNpcDustVoiceOffSet(mdlId, obj->mtnId[7], 0);
    CharModelStepFxSet(charNo, 2);
    obj->trans.x = work->unk05C.x = lbl_1_data_140[slot].x;
    obj->trans.y = work->unk05C.y = lbl_1_data_140[slot].y;
    obj->trans.z = work->unk05C.z = lbl_1_data_140[slot].z;
    work->unk068.x = work->unk068.y = work->unk068.z = 0.0f;
    work->unk074 = 0.0f;
    hit = &work->unk08C;
    hit->unk000 = 1;
    hit->unk004 = 0;
    hit->unk008 = no;
    hit->unk00C = 0;
    hit->unk010 = obj;
    hit->unk014 = fn_1_47C8;
    hit->unk018 = &work->unk05C;
    hit->unk01C = 150.0f;
    fn_1_DF30(hit);
    work->unk04C = 0;
    work->unk050 = 0;
    work->unk080 = 1;
    obj->objFunc = fn_1_37C0;
}

/* 287 insns */
void fn_1_37C0(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    s32 padNo;
    float stkX;
    float stkY;

    work->unk018 = 0;
    work->unk01C = 0;
    work->unk020 = 0.0f;
    work->unk024 = 0.0f;
    switch (work->unk04C) {
        case 0:
            if (++work->unk050 < 10) {
                break;
            }
            work->unk08C.unk01C = 40.0f;
            work->unk04C++;
        case 1:
            work->unk05C.x = lbl_1_data_140[work->unk008].x;
            work->unk05C.z = lbl_1_data_140[work->unk008].z;
            if (fn_1_1AE0() != 2) {
                break;
            }
            work->unk04C++;
        case 2:
            if (fn_1_1AE0() != 2) {
                work->unk04C++;
                work->unk050 = 0;
                work->unk078 = 1;
                break;
            }
            if (work->unk028) {
                fn_1_48C8(obj);
                break;
            }
            padNo = GwPlayerConf[work->unk000].padNo;
            stkX = HuPadStkX[padNo];
            stkY = -HuPadStkY[padNo];
            work->unk01C = HuPadBtn[padNo];
            work->unk018 = HuPadBtnDown[padNo];
            work->unk020 = 180.0 * (atan2(stkX, stkY) / M_PI);
            work->unk024 = (1.0f / 56.0f) * sqrtf(stkX * stkX + stkY * stkY);
            if (work->unk024 > 1.0f) {
                work->unk024 = 1.0f;
            }
            break;
        case 3:
            if (++work->unk050 < 20) {
                break;
            }
            work->unk04C++;
            fn_1_4E94(obj, 0);
        case 4:
            if (fn_1_1AE0() == 3 && fn_1_1CB0()) {
                work->unk04C = 0;
                obj->objFunc = fn_1_3C3C;
            }
            break;
    }
    work->unk068.x = work->unk068.y = work->unk068.z = 0.0f;
    fn_1_4658(obj);
    fn_1_443C(obj);
    work->unk05C.y = fn_1_BFE8(work->unk05C.x, work->unk05C.z);
    PSVECAdd(&work->unk05C, &work->unk068, &work->unk05C);
    fn_1_4380(obj);
}

/* 465 insns */
void fn_1_3C3C(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    OMOBJ *other;
    u32 *tbl;
    u32 num;
    float dx;
    float dz;
    float dist;
    float diff;
    HuVecF pos;

    work->unk018 = 0;
    work->unk01C = 0;
    work->unk020 = 0.0f;
    work->unk024 = 0.0f;
    work->unk068.x = work->unk068.y = work->unk068.z = 0.0f;
    switch (work->unk04C) {
        case 0:
            fn_1_1B70(work->unk000);
            work->unk078 = 0;
            work->unk07C = 0;
            work->unk04C++;
        case 1:
            fn_1_443C(obj);
            if (fn_1_1AF8()) {
                work->unk04C++;
                work->unk050 = 0;
            }
            break;
        case 2:
            if (++work->unk050 > 300.0) {
                work->unk08C.unk000 &= ~1;
            }
            if (!fn_1_1B10()) {
                dx = 0.0f;
                dz = 0.0f;
                num = fn_1_1CE8();
            } else if (fn_1_1B40(work->unk000) >= 0) {
                dx = 0.0f;
                dz = 120.0f;
                num = fn_1_1CE8();
            } else {
                dx = 0.0f;
                dz = -200.0f;
                num = fn_1_1D00();
            }
            tbl = fn_1_1D18();
            dist = 85.0 * (num - 1);
            dx += -dist + 170.0 * tbl[work->unk000];
            dx -= work->unk05C.x;
            dz -= work->unk05C.z;
            dist = sqrtf(dx * dx + dz * dz);
            if (dist > 10.0) {
                if (dist > 150.0) {
                    work->unk024 = 1.2f;
                } else if (dist > 50.0) {
                    work->unk024 = 0.8f;
                } else {
                    work->unk024 = 0.4f;
                }
                work->unk020 = 180.0 * (atan2(dx, dz) / M_PI);
                other = fn_1_53D4(&work->unk05C, work->unk020, 30.0f, 100.0f);
                if (other != NULL && other != obj) {
                    fn_1_5708(other, &pos, 0);
                    dx = pos.x - work->unk05C.x;
                    dz = pos.z - work->unk05C.z;
                    diff = work->unk020 - 180.0 * (atan2(dx, dz) / M_PI);
                    diff = fmodf(diff, 360.0f);
                    if (diff < 0.0) {
                        diff += 360.0;
                    }
                    work->unk020 += (diff < 30.0) ? 20.0 : -20.0;
                }
                fn_1_443C(obj);
                fn_1_1BA0(work->unk000, 0);
            } else {
                fn_1_1BA0(work->unk000, 1);
                if (fn_1_1BFC(1)) {
                    work->unk04C++;
                    work->unk050 = 0;
                }
            }
            break;
        case 3:
            work->unk020 = 0.0f;
            work->unk024 = 0.2f;
            fn_1_443C(obj);
            if (++work->unk050 < 8) {
                break;
            }
            work->unk04C++;
            work->unk050 = 0;
            fn_1_1BA0(work->unk000, 2);
            break;
        case 4:
            fn_1_443C(obj);
            if (!fn_1_1BFC(2)) {
                break;
            }
            if (++work->unk050 < 20) {
                break;
            }
            work->unk080 = 0;
            CharModelVoiceVolSet(work->unk00C, 127);
            if (fn_1_1B10() && fn_1_1B40(work->unk000) >= 0) {
                fn_1_4E94(obj, 3);
            } else {
                fn_1_4E94(obj, 4);
                fn_1_1DD8(work->unk000);
            }
            work->unk04C++;
            break;
        case 5:
            if (fn_1_5038(obj)) {
                fn_1_1C80(work->unk000);
            }
            break;
    }
    work->unk05C.y = fn_1_BFE8(work->unk05C.x, work->unk05C.z);
    PSVECAdd(&work->unk05C, &work->unk068, &work->unk05C);
    fn_1_4380(obj);
}

/* 47 insns */
void fn_1_4380(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;

    work->unk054++;
    work->unk014 -= 1.0;
    CharModelVoicePanSet(work->unk00C, fn_1_1EB0(&work->unk05C));
    if (work->unk080 != 0) {
        CharModelVoiceVolSet(work->unk00C, fn_1_1F44(&work->unk05C));
    }
    if (work->unk07C != 0 && fn_1_5038(obj)) {
        work->unk07C = 0;
    }
}

/* 135 insns */
void fn_1_443C(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    s32 motA;
    s32 motB;
    s32 motC;
    float spd;
    float lim;
    float rate;

    spd = work->unk024;
    motA = 0;
    motB = 1;
    motC = 2;
    if (work->unk084) {
        spd *= 0.7;
        motA = 6;
        motB = 7;
        motC = 8;
    }
    if (spd > 0.05f && work->unk078 == 0 && work->unk07C == 0) {
        work->unk074 = fn_1_2B7C(work->unk074, work->unk020, 0.3f);
        work->unk068.x = (1.0f / 60.0f) * (550.0 * (spd * sin(3.141592653589793 * work->unk020 / 180.0)));
        work->unk068.z = (1.0f / 60.0f) * (550.0 * (spd * cos(3.141592653589793 * work->unk020 / 180.0)));
        if (fn_1_5104(obj)) {
            lim = 0.5f;
            if (work->unk010 == motC) {
                lim = 0.45f;
            }
            if (spd > lim) {
                fn_1_4E94(obj, motC);
                rate = spd;
            } else {
                fn_1_4E94(obj, motB);
                rate = spd / lim;
            }
            Hu3DMotionSpeedSet(obj->mdlId[0], rate);
        }
    } else if (work->unk07C == 0) {
        fn_1_4E94(obj, motA);
    }
}

/* 92 insns */
void fn_1_4658(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    OMOBJ *saru;
    HU3DMODELID mdlId;
    char *hook;

    if (work->unk078 != 0) {
        if (work->unk084 != 0) {
            fn_1_575C(obj, 0);
            fn_1_4E94(obj, 9);
            work->unk07C = 1;
        }
        return;
    }
    if (work->unk07C == 0 && (work->unk018 & PAD_BUTTON_A)) {
        if (work->unk084 != 0) {
            fn_1_575C(obj, 1);
            fn_1_4E94(obj, 9);
            work->unk07C = 1;
            fn_1_1FD8(0x63F, &work->unk05C);
        } else {
            saru = fn_1_9D18(&work->unk05C, work->unk074, 45.0f, 100.0f);
            if (saru != NULL) {
                mdlId = fn_1_A368(saru, obj);
                if (mdlId >= 0) {
                    work->unk084 = 1;
                    work->unk088 = saru;
                    hook = CharModelItemHookGet(work->unk00C, 8, 0);
                    Hu3DModelHookSet(obj->mdlId[0], hook, mdlId);
                    fn_1_4E94(obj, 5);
                    work->unk07C = 1;
                    fn_1_1FD8(0x63E, &work->unk05C);
                }
            }
        }
    }
}

/* 64 insns */
void fn_1_47C8(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    float r;

    Hu3DModelPosSetV(obj->mdlId[0], &work->unk05C);
    Hu3DModelRotSet(obj->mdlId[0], 0.0f, work->unk074, 0.0f);
    switch (work->unk00C) {
        case 2:
        case 5:
            r = 15.0f;
            break;
        case 8:
            r = 10.0f;
            break;
        default:
            r = 20.0f;
            break;
    }
    if (work->unk084 != 0) {
        r += 10.0;
    }
    fn_1_C424(work->unk05C.x, work->unk05C.z, r);
}

/* 371 insns */
void fn_1_48C8(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    M503_PLAYERCOM *com = &lbl_1_data_170[work->unk02C];
    BOOL changed = FALSE;
    float dist;
    float mag = com->unk018;
    HuVecF pos;
    float dx;
    float dz;
    float ang;

    if (work->unk034 != work->unk084) {
        work->unk034 = work->unk084;
        changed = TRUE;
    }
    if (work->unk084 == 0) {
        if (changed) {
            work->unk030 = com->unk010;
        }
        if (work->unk030 <= 0) {
            if (work->unk038 != NULL) {
                if (!fn_1_A080(work->unk038, NULL, NULL) || work->unk03C > com->unk014) {
                    work->unk038 = NULL;
                }
            }
            if (work->unk038 == NULL) {
                work->unk038 = fn_1_9D18(&work->unk05C, work->unk074, com->unk004, com->unk008);
                work->unk03C = 0;
            }
            if (work->unk038 != NULL) {
                fn_1_A080(work->unk038, &pos, NULL);
                work->unk018 |= PAD_BUTTON_A;
            } else {
                ang = 1.2 * (float)work->unk054;
                ang += 90.0f * (u32)work->unk000;
                pos.x = 100.0 * (3.2 * sin(3.141592653589793 * ang / 180.0));
                pos.z = 100.0 * (3.2 * cos(3.141592653589793 * ang / 180.0));
                mag = 0.7f;
            }
        }
    } else {
        work->unk038 = NULL;
        if (changed) {
            work->unk030 = com->unk00C;
            if ((1.0 / 65536.0) * (float)(s32)(frand() & 0xFFFF) <= com->unk000) {
                fn_1_A080(work->unk088, NULL, &work->unk040);
            } else {
                fn_1_A338(4.0 * ((1.0 / 65536.0) * (float)(s32)(frand() & 0xFFFF)), &work->unk040);
            }
        }
        if (work->unk030 <= 0) {
            pos = work->unk040;
            dx = pos.x - work->unk05C.x;
            dz = pos.z - work->unk05C.z;
            dist = sqrtf(dx * dx + dz * dz);
            if ((pos.z < 0.0f && dist < 190.0) || (pos.z >= 0.0f && dist < 240.0)) {
                work->unk018 |= PAD_BUTTON_A;
            }
        }
    }
    if (work->unk030 <= 0) {
        dx = pos.x - work->unk05C.x;
        dz = pos.z - work->unk05C.z;
        work->unk020 = 180.0 * (atan2(dx, dz) / 3.141592653589793);
        work->unk024 = mag;
    } else {
        work->unk030--;
    }
    work->unk03C++;
}

/* 105 insns */
void fn_1_4E94(OMOBJ *obj, u32 motNo)
{
    M503_PLAYER *work = obj->data;
    u32 ovlAttr = 0;
    HU3DMODELID mdlId = obj->mdlId[0];
    float shift;
    u32 attr;
    s16 ovl;

    if (work->unk010 != motNo && motNo < 10) {
        if (work->unk010 < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_C8[motNo].unk004;
        }
        work->unk010 = motNo;
        attr = lbl_1_data_C8[motNo].unk008;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_REV | HU3D_MOTATTR_OVL_LOOP | HU3D_MOTATTR_OVL_REV);
        CharMotionShiftSet(work->unk00C, obj->mtnId[lbl_1_data_C8[motNo].unk000], 0.0f, shift, attr);
        ovl = lbl_1_data_C8[motNo].unk002;
        if (ovl >= 0) {
            Hu3DMotionOverlaySet(mdlId, obj->mtnId[ovl]);
            work->unk014 = Hu3DMotionOverlayMaxTimeGet(mdlId);
            if (attr & HU3D_MOTATTR_LOOP) {
                ovlAttr |= HU3D_MOTATTR_OVL_LOOP;
            }
            if (attr & HU3D_MOTATTR_REV) {
                ovlAttr |= HU3D_MOTATTR_OVL_REV;
            }
            Hu3DModelAttrSet(mdlId, ovlAttr);
        } else {
            Hu3DMotionOverlayReset(mdlId);
        }
    }
}

/* 51 insns */
BOOL fn_1_5038(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;

    if (work->unk010 == -1) {
        return TRUE;
    }
    if (lbl_1_data_C8[work->unk010].unk002 >= 0) {
        if (work->unk014 <= 0.0) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    if (CharMotionEndCheck(work->unk00C) && CharMotionShiftIDGet(work->unk00C) < 0) {
        return TRUE;
    }
    return FALSE;
}

/* 24 insns */
BOOL fn_1_5104(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;
    BOOL ret = FALSE;

    if (CharMotionShiftIDGet(work->unk00C) < 0) {
        ret = TRUE;
    }
    return ret;
}

/* 149 insns */
BOOL fn_1_5164(OMOBJ *obj, u32 motNo)
{
    BOOL ret = FALSE;

    if (fn_1_5038(obj)) {
        fn_1_4E94(obj, motNo);
        ret = TRUE;
    }
    return ret;
}

/* 7 insns */
s32 fn_1_53B8(OMOBJ *obj)
{
    M503_PLAYER *work = obj->data;

    return work->unk000;
}

/* 205 insns */
OMOBJ *fn_1_53D4(HuVecF *pos, float dir, float fov, float range)
{
    OMOBJ *best = NULL;
    float bestDist = 100000.0f;
    s32 i;
    OMOBJ *obj;
    M503_PLAYER *work;
    float dx;
    float dy;
    float dz;
    float ang;
    float t;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_30[i];
        work = obj->data;
        dx = work->unk05C.x - pos->x;
        dy = work->unk05C.y - pos->y;
        dz = work->unk05C.z - pos->z;
        if (fov < 180.0) {
            ang = 180.0 * (atan2(dx, dz) / 3.141592653589793);
            t = fmod(ang - dir, 360.0);
            ang = t;
            if (ang < 0.0f) {
                ang += 360.0f;
            }
            if (ang > fov && ang < 360.0f - fov) {
                continue;
            }
        }
        ang = sqrtf(dz * dz + (dx * dx + dy * dy));
        if (ang > range) {
            continue;
        }
        if (ang < bestDist) {
            bestDist = ang;
            best = obj;
        }
    }
    return best;
}

/* 21 insns */
s32 fn_1_5708(OMOBJ *obj, HuVecF *pos, float *rot)
{
    M503_PLAYER *work = obj->data;

    if (pos != NULL) {
        *pos = work->unk05C;
    }
    if (rot != NULL) {
        *rot = work->unk074;
    }
    return work->unk084;
}

/* 45 insns */
BOOL fn_1_575C(OMOBJ *obj, s32 arg)
{
    M503_PLAYER *work = obj->data;
    char *hook;
    HU3DMODELID mdlId = obj->mdlId[0];
    HuVecF pos;

    if (work->unk084 == 0) {
        return FALSE;
    }
    hook = CharModelItemHookGet(work->unk00C, 8, 0);
    Hu3DModelHookObjReset(mdlId, hook);
    Hu3DModelObjPosGet(mdlId, hook, &pos);
    fn_1_A438(work->unk088, &pos, arg);
    work->unk084 = 0;
    return TRUE;
}

