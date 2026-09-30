/*
 * m574Dll player.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/player.s.
 */

#include "REL/m574Dll.h"

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
/* 0x60 */ /* s32 lbl_1_rodata_60[2] = { 0x00000000, 0x00000000 }; */
/* 0x68 */ /* s32 lbl_1_rodata_68[2] = { 0x00000000, 0x00000002 }; */
/* 0x70 */ /* float lbl_1_rodata_70 = 0.0f; */
/* 0x74 */ /* float lbl_1_rodata_74 = 1.2f; */
/* 0x78 */ /* double lbl_1_rodata_78 = 144; */
/* 0x80 */ /* double lbl_1_rodata_80 = 12; */
/* 0x88 */ /* double lbl_1_rodata_88 = 4503601774854144; */
/* 0x90 */ /* float lbl_1_rodata_90 = 0.05f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 1.0f; */
/* 0x98 */ /* double lbl_1_rodata_98 = 0; */
/* 0xA0 */ /* double lbl_1_rodata_A0 = 30; */
/* 0xA8 */ /* double lbl_1_rodata_A8 = 1; */
/* 0xB0 */ /* double lbl_1_rodata_B0 = 0.0000152587890625; */
/* 0xB8 */ /* float lbl_1_rodata_B8 = 120.0f; */
/* 0xC0 */ /* double lbl_1_rodata_C0 = 33.33333507180214; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 15; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 60.0f; */

/* --- .data --- */
/* 0xB0 */ s32 lbl_1_data_B0[5] = { 0x008C0000, 0x008C0001, 0x008C004C, 0x008C0006, 0x008C0031 };
/* 0xC4 */ M574_MOTPARAM lbl_1_data_C4[5] = { { 0, 0, 0.2f, 0x40000001 }, { 1, 0, 0.1f, 0x40000001 }, { 2, 0, 0.2f, 0 }, { 3, 0, 0.2f, 0 }, { 4, 0, 0.2f, 0 } };
/* 0x100 */ HuVecF lbl_1_data_100[4] = { { -1.1e+03f, 0.0f, 0.0f }, { -2.2e+02f, 0.0f, 0.0f }, { 2.2e+02f, 0.0f, 0.0f }, { 1.1e+03f, 0.0f, 0.0f } };
/* 0x130 */ HuVecF lbl_1_data_130[4] = { { -9e+02f, 5e+01f, 0.0f }, { -4.2e+02f, 5e+01f, 0.0f }, { 4.2e+02f, 5e+01f, 0.0f }, { 9e+02f, 5e+01f, 0.0f } };
/* 0x160 */ float lbl_1_data_160[4] = { 90.0f, 270.0f, 90.0f, 270.0f };
/* 0x170 jumptable_1_data_170 (fn_1_1264), 0x190 jumptable_1_data_190 (fn_1_1588) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x38 */ OMOBJ *lbl_1_bss_38[4];

/* --- functions (reference order) --- */
/* 107 insns. Called from ObjectSetup: teams and the four player objects. */
void fn_1_E98(OMOBJMAN *objman)
{
    s32 teams[4];
    s32 count[2] = { 0, 0 };
    s32 slot[2] = { 0, 2 };
    s32 team;
    OMOBJ *obj;
    s32 i;
    s32 invalid;

    invalid = FALSE;
    for (i = 0; i < 4; i++) {
        team = GwPlayerConf[i].grp;
        teams[i] = team;
        if (team >= 2) {
            invalid = TRUE;
        } else {
            count[team]++;
        }
    }
    if (count[0] != 2 || count[1] != 2) {
        invalid = TRUE;
    }
    if (invalid) {
        for (i = 0; i < 4; i++) {
            teams[i] = i >> 1;
        }
    }
    omMakeGroupEx(objman, 0, 4);
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_38[i] = omAddObjEx(objman, 40, 1, 5, 0, fn_1_1068);
        obj->work[0] = i;
        team = teams[i];
        obj->work[1] = team;
        obj->work[2] = slot[team]++;
        fn_1_9FC(i, team, GwPlayerConf[i].charNo);
    }
}

/* 9 insns */
void fn_1_1044(void)
{
    CharModelKill(-1);
}

/* 127 insns. Player object init. */
void fn_1_1068(OMOBJ *obj)
{
    M574_PLAYER *work;
    s32 i;
    HU3DMODELID mdlId;
    s32 no;
    s32 charNo;
    s32 slot;
    HU3DMOTID motId;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M574_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M574_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = no = obj->work[0];
    work->unk004 = obj->work[1];
    work->unk008 = slot = obj->work[2];
    work->unk00C = charNo = GwPlayerConf[no].charNo;
    work->unk028 = GwPlayerConf[no].dif & 3;
    work->unk024 = GwPlayerConf[no].type;
    work->unk02C = 0;
    mdlId = CharModelCreate(charNo, 2);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 6);
    Hu3DModelShadowSet(mdlId);
    CharEffectLayerSet(6);
    for (i = 0; i < 5; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_B0[i]);
        obj->mtnId[i] = motId;
    }
    CharMotionDataClose(charNo);
    work->unk010 = -1;
    fn_1_1D54(obj, 2);
    work->unk048 = lbl_1_data_100[slot];
    work->unk054.x = work->unk054.y = work->unk054.z = 0.0f;
    Hu3DModelScaleSet(mdlId, 1.2f, 1.2f, 1.2f);
    work->unk06C = lbl_1_data_160[slot];
    work->unk038 = 0;
    obj->objFunc = fn_1_1264;
}

/* 201 insns. Before and during play. */
void fn_1_1264(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;
    s32 padNo;
    float stick[2];

    work->unk014 = 0;
    work->unk018 = 0;
    work->unk01C = 0.0f;
    work->unk020 = 0.0f;
    switch (work->unk038) {
        case 0:
            work->unk038++;
            work->unk044 = 0;
        case 1:
            if (++work->unk044 < 144.0) {
                break;
            }
            work->unk038++;
            work->unk044 = 0;
            work->unk03C = 2;
        case 2:
            work->unk018 = PAD_BUTTON_A;
            if (++work->unk044 < 12.0) {
                break;
            }
            work->unk038++;
            work->unk044 = 0;
        case 3:
            if (++work->unk044 < 12.0) {
                break;
            }
            if (--work->unk03C > 0) {
                work->unk038--;
                work->unk044 = 0;
                break;
            }
            work->unk038++;
        case 4:
            if (MgSeqModeGet() != 5) {
                break;
            }
            work->unk038++;
        case 5:
            if (MgSeqModeGet() != 5) {
                work->unk038++;
                work->unk03C = 0;
                work->unk070 = 1;
                break;
            }
            if (work->unk024) {
                fn_1_19AC(obj);
                break;
            }
            padNo = GwPlayerConf[work->unk000].padNo;
            stick[1] = 0.0f;
            stick[0] = 0.0f;
            work->unk018 = HuPadBtn[padNo];
            work->unk014 = HuPadBtnDown[padNo];
            break;
        case 6:
            if (++work->unk03C < 10) {
                break;
            }
            work->unk038++;
            fn_1_1D54(obj, 0);
        case 7:
            if (MgSeqModeGet() == 7) {
                work->unk038 = 0;
                obj->objFunc = fn_1_1588;
            }
            break;
    }
    fn_1_1830(obj);
    fn_1_182C(obj);
    PSVECAdd(&work->unk048, &work->unk054, &work->unk048);
    fn_1_17A0(obj);
    fn_1_1938(obj);
}

/* 134 insns. After play: turn to camera, win/lose motion. */
void fn_1_1588(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;

    work->unk014 = 0;
    work->unk018 = 0;
    work->unk01C = 0.0f;
    work->unk020 = 0.0f;
    work->unk054.x = work->unk054.y = work->unk054.z = 0.0f;
    switch (work->unk038) {
        case 0:
            work->unk070 = 0;
            work->unk074 = 0;
            work->unk038++;
        case 1:
            fn_1_182C(obj);
            if (MgSeqModeGet() == 7) {
                break;
            }
            work->unk038++;
            work->unk03C = 0;
            fn_1_1D54(obj, 1);
            break;
        case 2:
            fn_1_182C(obj);
            work->unk06C = fn_1_CC8(work->unk06C, 0.0f, 0.05f);
            if (++work->unk03C < 20) {
                break;
            }
            work->unk038++;
            work->unk03C = 0;
            fn_1_1D54(obj, 0);
            break;
        case 3:
            fn_1_182C(obj);
            work->unk06C = fn_1_CC8(work->unk06C, 0.0f, 0.05f);
            if (++work->unk03C < 20) {
                break;
            }
            if (fn_1_928(work->unk000) >= 0) {
                fn_1_1D54(obj, 3);
            } else {
                fn_1_1D54(obj, 4);
                fn_1_AAC(work->unk000);
            }
            work->unk038++;
            break;
        case 4:
            break;
        case 5:
            if (fn_1_1E4C(obj)) {
                work->unk038++;
            }
            break;
        case 6:
            break;
    }
    PSVECAdd(&work->unk048, &work->unk054, &work->unk048);
    fn_1_17A0(obj);
    fn_1_1938(obj);
}

/* 0x1AC */ s32 lbl_1_data_1AC[4] = { 36, 60, 68, 92 };

/* 35 insns */
void fn_1_17A0(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;

    work->unk040++;
    CharModelVoicePanSet(work->unk00C, lbl_1_data_1AC[work->unk008]);
    if (work->unk074 && fn_1_1E4C(obj)) {
        work->unk074 = 0;
    }
}

/* 1 insns */
void fn_1_182C(OMOBJ *obj)
{
}

/* 66 insns. Drives the slot's stage object from the A button. */
void fn_1_1830(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;
    float t;

    if (work->unk018 & PAD_BUTTON_A) {
        fn_1_6478(work->unk008, 1.0f);
    } else if (work->unk020 > 0.0) {
        fn_1_6478(work->unk008, work->unk020);
    } else {
        fn_1_6478(work->unk008, 0.0f);
    }
    if (work->unk010 == 2 && CharMotionShiftIDGet(work->unk00C) < 0) {
        t = fn_1_6568(work->unk008);
        CharMotionTimeSet(work->unk00C, 30.0 * (1.0 - t));
    }
}

/* 29 insns */
void fn_1_1938(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;
    HU3DMODELID mdlId = obj->mdlId[0];

    Hu3DModelPosSetV(mdlId, &work->unk048);
    Hu3DModelRotSet(mdlId, 0.0f, work->unk06C, 0.0f);
}

/* 0x1BC */ M574_COMPARAM lbl_1_data_1BC[4] = {
    { 400.0f, 18, 16, 9, 9, 0.7f },
    { 350.0f, 19, 15, 8, 8, 0.75f },
    { 320.0f, 21, 14, 7, 7, 0.8f },
    { 300.0f, 24, 13, 6, 6, 0.85f },
};
/* 0x21C */ s32 lbl_1_data_21C[1] = { 0 }; /* dtk folds this unreferenced zero word into lbl_1_data_1BC */

/* 202 insns. COM: pick the nearest ball on our side and hold A for a while. */
void fn_1_19AC(OMOBJ *obj)
{
    M574_PLAYER *work;
    M574_COMPARAM *param;
    s32 ballNo;
    HuVecF *home;
    HuVecF vel;

    work = obj->data;
    param = &lbl_1_data_1BC[work->unk028];
    home = &lbl_1_data_130[work->unk008];
    switch (work->unk02C) {
        case 0:
            if ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) > param->unk14) {
                break;
            }
            ballNo = fn_1_6D7C(work->unk004, home, 0.0f, 120.0f, param->unk00);
            if (ballNo < 0) {
                break;
            }
            fn_1_70B0(ballNo, NULL, &vel);
            if (PSVECMag(&vel) > 33.33333507180214) {
                work->unk034 = 1;
            } else {
                work->unk034 = 0;
            }
            work->unk02C++;
            if (work->unk034) {
                work->unk030 = param->unk0C;
            } else {
                work->unk030 = param->unk04;
            }
            if ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) > param->unk14) {
                work->unk030 += (s32)(12.0 * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF)));
            }
        case 1:
            work->unk018 = PAD_BUTTON_A;
            if (--work->unk030 > 0) {
                break;
            }
            work->unk02C++;
            if (work->unk034) {
                work->unk030 = param->unk10;
            } else {
                work->unk030 = param->unk08;
            }
            if ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) > param->unk14) {
                work->unk030 += (s32)(15.0 * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF)));
            }
        case 2:
            if (--work->unk030 > 0) {
                break;
            }
            work->unk02C = 0;
            break;
    }
}

/* 32 insns. The other player object on the same team. */
OMOBJ *fn_1_1CD4(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;
    u32 team = work->unk004;
    OMOBJ *other;
    s32 i;

    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_38[i];
        if (other != obj) {
            work = other->data;
            if (work->unk004 == team) {
                return other;
            }
        }
    }
    return NULL;
}

/* 62 insns. Set a lbl_1_data_C4 motion. */
void fn_1_1D54(OMOBJ *obj, u32 motNo)
{
    M574_PLAYER *work = obj->data;
    float shift;

    if (work->unk010 != motNo && motNo < 5) {
        if (work->unk010 < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_C4[motNo].unk04;
        }
        work->unk010 = motNo;
        CharMotionShiftSet(work->unk00C, obj->mtnId[lbl_1_data_C4[motNo].unk00], 0.0f, shift, lbl_1_data_C4[motNo].unk08);
    }
}

/* 27 insns */
BOOL fn_1_1E4C(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;

    if (CharMotionEndCheck(work->unk00C) && CharMotionShiftIDGet(work->unk00C) < 0) {
        return TRUE;
    }
    return FALSE;
}

/* 7 insns */
s32 fn_1_1EB8(OMOBJ *obj)
{
    M574_PLAYER *work = obj->data;

    return work->unk000;
}

/* 21 insns */
BOOL fn_1_1ED4(OMOBJ *obj, HuVecF *pos, float *rotY)
{
    M574_PLAYER *work = obj->data;

    if (pos != NULL) {
        *pos = work->unk048;
    }
    if (rotY != NULL) {
        *rotY = work->unk06C;
    }
    return TRUE;
}

/* 29 insns. TRUE if the team has a human player. */
s32 fn_1_1F28(u32 team)
{
    OMOBJ *obj;
    M574_PLAYER *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_38[i];
        work = obj->data;
        if (work->unk004 == team && work->unk024 == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 35 insns. Rumble the pads of a team. */
void fn_1_1F9C(u32 team)
{
    OMOBJ *obj;
    M574_PLAYER *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_38[i];
        work = obj->data;
        if (work->unk004 == team) {
            omVibrate(work->unk000, 15, 6, 6);
        }
    }
}
