/*
 * m514dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/player.s.
 */

#include "REL/m514Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/mg/seqman.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 200; */
/* 0xD0 */ /* double lbl_1_rodata_D0 = 160; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 5; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 0.0f; */
/* 0xE8 */ /* double lbl_1_rodata_E8 = 0.1; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 90.0f; */
/* 0xF8 */ /* double lbl_1_rodata_F8 = 30; */
/* 0x100 */ /* float lbl_1_rodata_100 = -220.0f; */
/* 0x108 */ /* double lbl_1_rodata_108 = 18; */
/* 0x110 */ /* double lbl_1_rodata_110 = 4503601774854144; */
/* 0x118 */ /* float lbl_1_rodata_118 = -100.0f; */
/* 0x11C */ /* float lbl_1_rodata_11C = 0.1f; */
/* 0x120 */ /* double lbl_1_rodata_120 = 5.000000260770321; */
/* 0x128 */ /* double lbl_1_rodata_128 = 90; */
/* 0x130 */ /* double lbl_1_rodata_130 = -90; */
/* 0x138 */ /* double lbl_1_rodata_138 = 100; */
/* 0x140 */ /* double lbl_1_rodata_140 = 0.15; */
/* 0x148 */ /* double lbl_1_rodata_148 = 3.141592653589793; */
/* 0x150 */ /* double lbl_1_rodata_150 = 180; */
/* 0x158 */ /* float lbl_1_rodata_158 = 10.0f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 0.2f; */
/* 0x160 */ /* float lbl_1_rodata_160 = 9.166667f; */
/* 0x168 */ /* double lbl_1_rodata_168 = 1; */
/* 0x170 */ /* double lbl_1_rodata_170 = 0.5; */
/* 0x178 */ /* float lbl_1_rodata_178 = -0.6666667f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 20.0f; */
/* 0x180 */ /* double lbl_1_rodata_180 = 0.00500000026077032; */
/* 0x188 */ /* double lbl_1_rodata_188 = 0.01666666753590107; */
/* 0x190 */ /* double lbl_1_rodata_190 = 0.98; */
/* 0x198 */ /* double lbl_1_rodata_198 = 48; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 400; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = 0.03333333507180214; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 500; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = -2500; */
/* 0x1C0 */ /* double lbl_1_rodata_1C0 = 0.3333333507180214; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = 3; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 10; */
/* 0x1D8 */ /* double lbl_1_rodata_1D8 = 2; */
/* 0x1E0 */ /* double lbl_1_rodata_1E0 = 50; */
/* 0x1E8 */ /* float lbl_1_rodata_1E8 = 0.5f; */
/* 0x1EC */ /* float lbl_1_rodata_1EC = 1.0f; */
/* 0x1F0 */ /* double lbl_1_rodata_1F0 = 550; */
/* 0x1F8 */ /* double lbl_1_rodata_1F8 = 0.0000152587890625; */
/* 0x200 */ /* float lbl_1_rodata_200[2] = { 60.0f, 0.0f }; */

/* --- .data --- */
/* 0xB8 */ s32 lbl_1_data_B8[8] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0006, 0x008C0031, 0x008C0003, 0x00870021, 0x008C0004 };
/* 0xD8 */ M514_MOTION lbl_1_data_D8[8] = {
    { 0, 0.2f, HU3D_MOTATTR_LOOP },
    { 1, 0.2f, HU3D_MOTATTR_LOOP },
    { 2, 0.2f, HU3D_MOTATTR_LOOP },
    { 3, 0.2f, HU3D_MOTATTR_NONE },
    { 4, 0.2f, HU3D_MOTATTR_NONE },
    { 5, 0.1f, HU3D_MOTATTR_NONE },
    { 6, 0.2f, HU3D_MOTATTR_LOOP },
    { 7, 0.2f, HU3D_MOTATTR_NONE },
};
/* 0x138 */ HuVecF lbl_1_data_138[10] = {
    { -2100.0f, 0.0f, -500.0f }, { -1900.0f, 0.0f, -500.0f }, { -1700.0f, 0.0f, -500.0f }, { -1500.0f, 0.0f, -500.0f },
    { -3200.0f, 0.0f, -500.0f }, { -3000.0f, 0.0f, -500.0f }, { -2800.0f, 0.0f, -500.0f }, { -2600.0f, 0.0f, -500.0f },
    { -3100.0f, 0.0f, 0.0f }, { -2570.0f, 0.0f, 0.0f },
};
/* 0x1B0 */ float lbl_1_data_1B0[16] = { 0.98f, 1.06f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
/* 0x1F0 */ float lbl_1_data_1F0[4] = { 270.0f, 270.0f, 270.0f, 270.0f };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x84 gap_05_00000084_bss (0x4) -- dtk filler */
/* 0x80 */ OMOBJ *lbl_1_bss_80;
/* 0x70 */ OMOBJ *lbl_1_bss_70[4];

/* --- functions (reference order) --- */
/* 65 insns */
void fn_1_1D9C(OMOBJMAN *objman)
{
    OMOBJ *obj;
    s32 i;

    obj = omAddObjEx(objman, 40, 0, 0, 0, fn_1_1EC4);
    lbl_1_bss_80 = obj;
    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_70[i] = omAddObjEx(objman, 30, 1, 8, 0, fn_1_20E0);
        obj->work[0] = i;
        obj->work[1] = GwPlayerConf[i].grp;
        obj->work[2] = i;
        fn_1_1838(i, obj->work[1], GwPlayerConf[i].charNo);
    }
}

/* 9 insns */
void fn_1_1EA0(void)
{
    CharModelKill(-1);
}

/* 4 insns */
void fn_1_1EC4(OMOBJ *obj)
{
    obj->objFunc = fn_1_1ED4;
}

/* 131 insns */
void fn_1_1ED4(OMOBJ *obj)
{
    HuVecF *posA;
    HuVecF *posB;
    s32 i;
    s32 j;
    M514_PLAYER *workA;
    M514_PLAYER *workB;
    s32 swap;
    OMOBJ *objA;
    OMOBJ *objB;
    s32 rankA;
    s32 rankB;
    float dz;
    float dx;
    double adx;
    double adz;

    for (i = 0; i < 3; i++) {
        objA = lbl_1_bss_70[i];
        workA = objA->data;
        if (workA->unk068 == 0) {
            continue;
        }
        posA = &workA->unk040;
        rankA = fn_1_95BC(i);
        for (j = i + 1; j < 4; j++) {
            objB = lbl_1_bss_70[j];
            workB = objB->data;
            if (workB->unk068 == 0) {
                continue;
            }
            posB = &workB->unk040;
            dz = posA->z - posB->z;
            adz = fabs(dz);
            if (adz > 200.0) {
                continue;
            }
            dx = posA->x - posB->x;
            adx = fabs(dx);
            if (adx > 160.0) {
                continue;
            }
            rankB = fn_1_95BC(j);
            swap = 0;
            if (rankA < rankB) {
                swap = 1;
            }
            if (rankA == rankB && i > j) {
                swap = 1;
            }
            if (swap == 0) {
                posA->x += 5.0;
                posB->x -= 5.0;
            } else {
                posA->x -= 5.0;
                posB->x += 5.0;
            }
        }
    }
}

/* 122 insns */
void fn_1_20E0(OMOBJ *obj)
{
    M514_PLAYER *work;
    s32 i;
    s32 slot;
    u32 no;
    s32 charNo;
    HU3DMODELID mdlId;
    HU3DMOTID motId;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M514_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = no = obj->work[0];
    work->unk004 = obj->work[1];
    slot = work->unk008 = obj->work[2];
    work->unk00C = charNo = GwPlayerConf[no].charNo;
    work->unk024 = GwPlayerConf[no].dif & 3;
    work->unk020 = GwPlayerConf[no].type;
    work->unk028 = 0;
    mdlId = CharModelCreate(charNo, 2);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 6);
    Hu3DModelShadowSet(mdlId);
    CharEffectLayerSet(6);
    for (i = 0; i < 8; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_B8[i]);
        obj->mtnId[i] = motId;
    }
    CharMotionDataClose(charNo);
    work->unk03C = -1;
    fn_1_3EC0(obj, 0);
    work->unk040 = lbl_1_data_138[slot];
    work->unk04C.x = work->unk04C.y = work->unk04C.z = 0.0f;
    work->unk058 = lbl_1_data_1F0[slot];
    work->unk090 = -1;
    work->unk094 = -1;
    work->unk030 = 0;
    work->unk07C = 0;
    obj->objFunc = fn_1_2338;
}

/* 28 insns */
void fn_1_22C8(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    float x;

    x = work->unk040.x + 0.0;
    Center.x = Center.x + 0.1 * (x - Center.x);
}

/* 325 insns */
void fn_1_2338(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    HuVecF pos;
    s32 idx;
    u32 turn;
    s32 padNo;

    work->unk010 = 0;
    work->unk014 = 0;
    work->unk018 = 0.0f;
    work->unk01C = 0.0f;
    switch (work->unk030) {
        case 0:
            idx = work->unk000;
            if (fn_1_387C(obj, &lbl_1_data_138[idx + 4], 0.0f, 1) == 0) {
                break;
            }
            work->unk030++;
            work->unk06C = 1;
        case 1:
            if (MgSeqModeGet() != 5) {
                break;
            }
            turn = fn_1_1814();
            if (turn != work->unk000) {
                idx = work->unk000 - turn - 1;
                fn_1_387C(obj, &lbl_1_data_138[idx + 4], 0.0f, 1);
                break;
            }
            work->unk030++;
            work->unk034 = 0;
            fn_1_37CC(obj, 9);
        case 2:
            fn_1_22C8(obj);
            if (fn_1_387C(obj, &lbl_1_data_138[8], 90.0f, 1) == 0) {
                break;
            }
            if (++work->unk034 < 30.0) {
                break;
            }
            work->unk030++;
            work->unk034 = 0;
            work->unk06C = 0;
            work->unk068 = 1;
        case 3:
            fn_1_22C8(obj);
            if (work->unk08C) {
                work->unk030++;
                work->unk034 = 0;
                break;
            }
            if (work->unk020) {
                fn_1_3D6C(obj);
                break;
            }
            padNo = GwPlayerConf[work->unk000].padNo;
            work->unk014 = HuPadBtn[padNo];
            work->unk010 = HuPadBtnDown[padNo];
            break;
        case 4:
            fn_1_22C8(obj);
            if (fn_1_50E4()) {
                break;
            }
            pos.x = work->unk040.x;
            pos.y = 0.0f;
            pos.z = -220.0f;
            work->unk040.y = work->unk04C.y = 0.0f;
            if (fn_1_387C(obj, &pos, 0.0f, 0)) {
                work->unk030++;
                work->unk034 = 0;
            }
            break;
        case 5:
            if (++work->unk034 < 30.0) {
                break;
            }
            fn_1_1824(work->unk000);
            work->unk030++;
            work->unk034 = 0;
            work->unk06C = 1;
            fn_1_9334();
            break;
        case 6:
            if (++work->unk034 < 18.0) {
                break;
            }
            work->unk030++;
        case 7:
            if (MgSeqModeGet() != 7) {
                break;
            }
            work->unk030 = 0;
            obj->objFunc = fn_1_284C;
            break;
    }
    fn_1_2E8C(obj);
    fn_1_2E88(obj);
    PSVECAdd(&work->unk040, &work->unk04C, &work->unk040);
    fn_1_2A88(obj);
    fn_1_3CF8(obj);
}

/* 143 insns */
void fn_1_284C(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    HuVecF pos;

    work->unk010 = 0;
    work->unk014 = 0;
    work->unk018 = 0.0f;
    work->unk01C = 0.0f;
    work->unk04C.x = work->unk04C.y = work->unk04C.z = 0.0f;
    switch (work->unk030) {
        case 0:
            work->unk06C = 0;
            work->unk070 = 0;
            work->unk030++;
        case 1:
            if (fn_1_16EC(work->unk000) >= 0) {
                pos.x = work->unk040.x;
                pos.y = work->unk040.y;
                pos.z = -100.0f;
                if (fn_1_387C(obj, &pos, 0.0f, 0) == 0) {
                    break;
                }
            }
            if (MgSeqModeGet() != 8) {
                break;
            }
            work->unk030++;
            work->unk034 = 0;
            break;
        case 2:
            work->unk058 = fn_1_1BCC(work->unk058, 0.0f, 0.1f);
            if (++work->unk034 < 10) {
                break;
            }
            work->unk030++;
            work->unk034 = 0;
            break;
        case 3:
            work->unk058 = fn_1_1BCC(work->unk058, 0.0f, 0.1f);
            if (++work->unk034 < 20) {
                break;
            }
            if (fn_1_16EC(work->unk000) >= 0) {
                fn_1_3EC0(obj, 3);
            } else {
                fn_1_3EC0(obj, 4);
                fn_1_1890(work->unk000);
            }
            work->unk030++;
            break;
        case 5:
            if (fn_1_3FB8(obj)) {
                work->unk030++;
            }
            break;
        case 6:
            break;
    }
    PSVECAdd(&work->unk040, &work->unk04C, &work->unk040);
    fn_1_2A88(obj);
    fn_1_3CF8(obj);
}

/* 80 insns */
void fn_1_2A88(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;

    work->unk038++;
    fn_1_7C10(work->unk090, &work->unk040);
    CharModelVoicePanSet(work->unk00C, fn_1_1960(&work->unk040));
    CharModelVoiceVolSet(work->unk00C, fn_1_19F4(&work->unk040));
    if (work->unk038 % 6 == 0 && 0.0f == work->unk040.y && PSVECMag(&work->unk04C) > (1.0f / 60.0f) * 300.0) {
        fn_1_2D10(obj, work->unk078 = ++work->unk078 & 1);
    }
    if (work->unk03C == 5 && fn_1_3FB8(obj)) {
        fn_1_3EC0(obj, 6);
    }
    if (work->unk070 && fn_1_3FB8(obj)) {
        work->unk070 = 0;
    }
}

/* 82 insns */
void fn_1_2BC8(OMOBJ *obj, HuVecF *out, s32 side)
{
    M514_PLAYER *work = obj->data;
    float ang = work->unk058;

    ang += (side == 0 ? 90.0 : -90.0);

    out->x = work->unk040.x + 100.0 * (0.15 * HuSin(ang));
    out->y = work->unk040.y;
    out->z = work->unk040.z + 100.0 * (0.15 * HuCos(ang));
}

/* 94 insns */
void fn_1_2D10(OMOBJ *obj, s32 side)
{
    M514_PLAYER *work = obj->data;
    HuVecF pos;

    if (work->unk00C != 8) {
        fn_1_2BC8(obj, &pos, side);
        pos.y = 0.0f;
        fn_1_80C0(&pos, 10.0f);
    }
}

/* 0x23C */ M514_JUMP lbl_1_data_23C[3] = {
    { 3, 13.333334f, 16.666668f, 0.5833334f, 1.0f, 6.666667f, 1500.0f },
    { 4, 13.333334f, 16.666668f, 0.5833334f, 1.0f, 6.666667f, 3000.0f },
    { 6, 16.666668f, 16.666668f, 0.75000006f, 1.0f, 8.333334f, 5000.0f },
};
/* 0x290 */ s32 lbl_1_data_290[3] = { 0x000006DA, 0x000006DB, 0x000006DC };

/* 1 insns */
void fn_1_2E88(OMOBJ *obj) { }

/* 592 insns */
void fn_1_2E8C(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    M514_JUMP *jump;
    float dist;

    if (work->unk074 != 0) {
        return;
    }
    switch (work->unk07C) {
        case 0:
            if (work->unk06C != 0) {
                break;
            }
            work->unk07C++;
            work->unk080 = 0;
            work->unk084 = 0;
        case 1:
            if (++work->unk080 < 18.0) {
                break;
            }
            work->unk07C++;
            work->unk080 = 0;
            work->unk05C = 0.2f;
        case 2:
            dist = 9.166667f;
            work->unk04C.x = work->unk04C.x + 0.1 * (dist - work->unk04C.x);
            if (work->unk040.x > lbl_1_data_138[9].x - 100.0) {
                fn_1_8228(0);
                work->unk064 = 1;
            }
            if (work->unk040.x < lbl_1_data_138[9].x) {
                fn_1_3EC0(obj, 2);
                work->unk05C = work->unk05C + 0.1 * (1.0 - work->unk05C);
                dist = work->unk05C * lbl_1_data_1B0[work->unk00C];
                Hu3DMotionSpeedSet(obj->mdlId[0], dist);
                break;
            }
            work->unk07C++;
            work->unk080 = 0;
        case 3:
            jump = &lbl_1_data_23C[work->unk084];
            work->unk04C.x *= 0.5;
            if (++work->unk080 < jump->unk00) {
                break;
            }
            work->unk07C++;
            work->unk088 = 1;
            work->unk04C.x = jump->unk04;
            work->unk04C.y = jump->unk08;
            work->unk060 = -0.6666667f;
            fn_1_3EC0(obj, 5);
            work->unk090 = fn_1_79F8(&work->unk040, 20.0f);
            work->unk094 = HuAudFXPlay(lbl_1_data_290[work->unk084]);
            fn_1_37CC(obj, 0);
            break;
        case 4:
            jump = &lbl_1_data_23C[work->unk084];
            if (work->unk04C.y >= 0.0f) {
                work->unk060 = work->unk060 - 0.3 * (1.0f / 60.0f);
            } else {
                work->unk060 = work->unk060 - 1.0 * (1.0f / 60.0f);
            }
            work->unk04C.x *= 0.98;
            work->unk04C.y += work->unk060;
            if (work->unk010 & (((work->unk084 & 1) == 0) ? 0x100 : 0x200)) {
                work->unk04C.x += jump->unk0C;
                if (work->unk04C.y > 0.0f) {
                    work->unk04C.y += jump->unk10;
                } else {
                    work->unk04C.y += jump->unk14;
                }
                fn_1_1870(work->unk000);
            }
            if (work->unk04C.y > 0.0f) {
                break;
            }
            if (work->unk040.y > 0.0f) {
                break;
            }
            work->unk040.y = 0.0f;
            work->unk04C.x = work->unk04C.y = 0.0f;
            work->unk088 = 0;
            CharModelLandDustCreate(work->unk00C, &work->unk040);
            fn_1_3EC0(obj, 7);
            fn_1_2D10(obj, work->unk084 & 1);
            fn_1_7B8C(work->unk090);
            work->unk090 = -1;
            HuAudFXFadeOut(work->unk094, 125);
            work->unk094 = -1;
            HuAudFXPlay(0x21);
            if (++work->unk084 < 3) {
                fn_1_8228(work->unk084 & 1);
                work->unk07C--;
                work->unk080 = 0;
                break;
            }
            fn_1_37CC(obj, work->unk084);
            fn_1_2D10(obj, work->unk084 & 1);
            fn_1_8228(-1);
            work->unk07C++;
            work->unk080 = 0;
        case 5:
            work->unk04C.x *= 0.5;
            if (++work->unk080 < 10) {
                break;
            }
            work->unk07C++;
            work->unk080 = 0;
            work->unk064 = 0;
            work->unk04C.x = 0.0f;
            fn_1_3EC0(obj, 0);
            break;
        case 6:
            if (++work->unk080 < 48.0) {
                break;
            }
            work->unk07C++;
            work->unk08C = 1;
        case 7:
            break;
    }
    if (work->unk040.y > 400.0) {
        work->unk060 = work->unk060 - 2.0 * (1.0f / 60.0f);
    }
    if (work->unk040.y > 500.0) {
        work->unk060 = work->unk060 - 2.0 * (1.0f / 60.0f);
    }
    if (work->unk064 != 0) {
        dist = work->unk040.x - -2500.0;
        if (dist < 0.0f) {
            dist = 0.0f;
        }
        fn_1_9570(work->unk004, dist);
        if (work->unk084 < 3) {
            jump = &lbl_1_data_23C[work->unk084];
            if (dist > jump->unk18) {
                work->unk060 = work->unk060 - 20.0 * (1.0f / 60.0f);
            }
        }
    }
}

/* 0x2BC */ M514_COMTIME lbl_1_data_2BC[4] = {
    { 6.0f, 1.2f, 9.66f, 0.9f },
    { 4.2f, 3.0f, 6.9f, 3.0f },
    { 3.6f, 3.6f, 6.3f, 3.0f },
    { 3.0f, 4.8f, 5.28f, 3.0f },
};
/* 0x2FC: unreferenced zero word; dtk folds it into lbl_1_data_2BC's size (0x44) */
s32 lbl_1_data_2FC[1] = { 0 };

/* 44 insns */
void fn_1_37CC(OMOBJ *obj, s32 type)
{
    M514_PLAYER *work = obj->data;
    s32 no = work->unk000;

    switch (type) {
        case 0:
        case 1:
        case 2:
            omVibrate(no, 10, 6, 6);
            break;
        case 3:
            omVibrate(no, 12, 12, 0);
            break;
        case 9:
            omVibrate(no, 20, 12, 0);
            break;
    }
}

/* 287 insns */
BOOL fn_1_387C(OMOBJ *obj, HuVecF *target, float rotY, s32 useX)
{
    M514_PLAYER *work = obj->data;
    float dx;
    float dz;
    float dist;
    float scale;
    float ang;

    work->unk074 = 1;
    if (useX) {
        dx = target->x - work->unk040.x;
    } else {
        dx = 0.0f;
    }
    dz = target->z - work->unk040.z;
    dist = sqrtf(dx * dx + dz * dz);
    if (dist < 10.0) {
        fn_1_3EC0(obj, 0);
        if (useX) {
            work->unk040.x = work->unk040.x + 0.1 * dx;
        }
        work->unk040.z = work->unk040.z + 0.1 * dz;
        work->unk04C.x = work->unk04C.y = work->unk04C.z = 0.0f;
        work->unk058 = fn_1_1BCC(work->unk058, rotY, 0.1f);
        if (dist > 1.0) {
            return FALSE;
        }
        if (fn_1_1CE8(work->unk058, rotY) > 2.0) {
            return FALSE;
        }
        if (useX) {
            work->unk040.x = target->x;
        }
        work->unk040.y = target->y;
        work->unk040.z = target->z;
        work->unk058 = rotY;
        work->unk074 = 0;
        return TRUE;
    }
    if (dist < 50.0) {
        fn_1_3EC0(obj, 1);
        scale = 0.5f;
    } else {
        fn_1_3EC0(obj, 2);
        scale = 1.0f;
    }
    ang = 180.0 * (atan2(dx, dz) / M_PI);
    work->unk058 = fn_1_1BCC(work->unk058, ang, 0.2f);
    work->unk04C.x = (1.0f / 60.0f) * (550.0 * (scale * sin(M_PI * work->unk058 / 180.0)));
    work->unk04C.z = (1.0f / 60.0f) * (550.0 * (scale * cos(M_PI * work->unk058 / 180.0)));
    if (!useX) {
        work->unk04C.x = 0.0f;
    }
    return FALSE;
}

/* 29 insns */
void fn_1_3CF8(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    Hu3DModelPosSetV(mdlId, &work->unk040);
    Hu3DModelRotSet(mdlId, 0.0f, work->unk058, 0.0f);
}

/* 85 insns */
void fn_1_3D6C(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    M514_COMTIME *param = &lbl_1_data_2BC[work->unk024];

    switch (work->unk028) {
        case 0:
            work->unk028++;
            work->unk02C = param->unk00 + param->unk04 * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF));
        case 1:
            if (--work->unk02C > 0) {
                break;
            }
            work->unk010 = 0x300;
            work->unk014 = 0x300;
            work->unk02C = param->unk08 + param->unk0C * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF));
            break;
    }
}

/* 62 insns */
void fn_1_3EC0(OMOBJ *obj, u32 motNo)
{
    M514_PLAYER *work = obj->data;
    float shift;

    if (work->unk03C != motNo && motNo < 8) {
        if (work->unk03C < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_D8[motNo].unk04;
        }
        work->unk03C = motNo;
        CharMotionShiftSet(work->unk00C, obj->mtnId[lbl_1_data_D8[motNo].unk00], 0.0f, shift, lbl_1_data_D8[motNo].unk08);
    }
}

/* 27 insns */
BOOL fn_1_3FB8(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;

    if (CharMotionEndCheck(work->unk00C) && CharMotionShiftIDGet(work->unk00C) < 0) {
        return TRUE;
    }
    return FALSE;
}

/* 24 insns */
BOOL fn_1_4024(OMOBJ *obj)
{
    M514_PLAYER *work = obj->data;
    BOOL ret = FALSE;

    if (CharMotionShiftIDGet(work->unk00C) < 0) {
        ret = TRUE;
    }
    return ret;
}

/* 80 insns */
BOOL fn_1_4084(OMOBJ *obj, u32 motNo)
{
    BOOL ret = FALSE;

    if (fn_1_3FB8(obj)) {
        fn_1_3EC0(obj, motNo);
        ret = TRUE;
    }
    return ret;
}

/* 29 insns */
BOOL fn_1_41C4(u32 grp)
{
    OMOBJ *obj;
    M514_PLAYER *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_70[i];
        work = obj->data;
        if (work->unk004 == grp && work->unk020 == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 14 insns */
float fn_1_4238(s32 no)
{
    OMOBJ *obj = lbl_1_bss_70[no];
    M514_PLAYER *work = obj->data;

    return work->unk040.x;
}

