/*
 * m580Dll player.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/player.s.
 */

#include "REL/m580Dll.h"

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

/* The player's sqrtf inlines MSL's algorithm, but the reference pools 0.5 and 3.0
 * as ordinary literals (0x178, 0x180): not libc/math.h's copy, whose static
 * _half/_three would lead .rodata. The host uses the real sqrtf. */
static inline float PlayerSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x130 */ /* s32 lbl_1_rodata_130[2] = { 0x00000000, 0x00000000 }; */
/* 0x138 */ /* s32 lbl_1_rodata_138[2] = { 0x00000000, 0x00000002 }; */
/* 0x140 */ /* float lbl_1_rodata_140 = 0.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = 40.0f; */
/* 0x148 */ /* float lbl_1_rodata_148 = 0.5f; */
/* 0x150 */ /* double lbl_1_rodata_150 = 1; */
/* 0x158 */ /* double lbl_1_rodata_158 = 180; */
/* 0x160 */ /* float lbl_1_rodata_160 = 3.0f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 2.0f; */
/* 0x168 */ /* double lbl_1_rodata_168 = 18; */
/* 0x170 */ /* double lbl_1_rodata_170 = 3.141592653589793; */
/* 0x178 */ /* double lbl_1_rodata_178 = 0.5; */
/* 0x180 */ /* double lbl_1_rodata_180 = 3; */
/* 0x188 */ /* float lbl_1_rodata_188 = 0.017857144f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 1.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 0.98f; */
/* 0x198 */ /* double lbl_1_rodata_198 = 60; */
/* 0x1A0 */ /* double lbl_1_rodata_1A0 = 4503601774854144; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = -800; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = 800; */
/* 0x1B8 */ /* double lbl_1_rodata_1B8 = 120; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 1.5f; */
/* 0x1C8 */ /* double lbl_1_rodata_1C8 = 0.05; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 0; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 350.0f; */
/* 0x1E0 */ /* double lbl_1_rodata_1E0 = 2; */
/* 0x1E8 */ /* double lbl_1_rodata_1E8 = 30; */
/* 0x1F0 */ /* double lbl_1_rodata_1F0 = 0.7; */
/* 0x1F8 */ /* float lbl_1_rodata_1F8 = 0.05f; */
/* 0x1FC */ /* float lbl_1_rodata_1FC = 0.3f; */
/* 0x200 */ /* double lbl_1_rodata_200 = 0.01666666753590107; */
/* 0x208 */ /* double lbl_1_rodata_208 = 1000; */
/* 0x210 */ /* double lbl_1_rodata_210 = 0.03; */
/* 0x218 */ /* float lbl_1_rodata_218 = 1.2f; */
/* 0x21C */ /* float lbl_1_rodata_21C = 0.99f; */
/* 0x220 */ /* float lbl_1_rodata_220 = 120.0f; */
/* 0x224 */ /* float lbl_1_rodata_224 = 0.9f; */
/* 0x228 */ /* float lbl_1_rodata_228 = 45.0f; */
/* 0x230 */ /* double lbl_1_rodata_230 = 100; */
/* 0x238 */ /* double lbl_1_rodata_238 = 15; */
/* 0x240 */ /* double lbl_1_rodata_240 = 80; */
/* 0x248 */ /* float lbl_1_rodata_248 = 66.66667f; */
/* 0x24C */ /* float lbl_1_rodata_24C = 20.000002f; */
/* 0x250 */ /* double lbl_1_rodata_250 = 33.33333507180214; */
/* 0x258 */ /* float lbl_1_rodata_258 = 33.333336f; */
/* 0x260 */ /* double lbl_1_rodata_260 = 200; */
/* 0x268 */ /* float lbl_1_rodata_268 = 0.2f; */
/* 0x270 */ /* double lbl_1_rodata_270 = 70; */
/* 0x278 */ /* double lbl_1_rodata_278 = 20; */
/* 0x280 */ /* double lbl_1_rodata_280 = 0.1; */
/* 0x288 */ /* float lbl_1_rodata_288 = 0.8f; */
/* 0x28C */ /* float lbl_1_rodata_28C = 0.1f; */
/* 0x290 */ /* double lbl_1_rodata_290 = 35; */
/* 0x298 */ /* double lbl_1_rodata_298 = 4; */
/* 0x2A0 */ /* float lbl_1_rodata_2A0 = -16.666668f; */
/* 0x2A4 */ /* float lbl_1_rodata_2A4 = 16.666668f; */
/* 0x2A8 */ /* double lbl_1_rodata_2A8 = -250; */
/* 0x2B0 */ /* double lbl_1_rodata_2B0 = 250; */
/* 0x2B8 */ /* double lbl_1_rodata_2B8 = -1100; */
/* 0x2C0 */ /* double lbl_1_rodata_2C0 = 1100; */
/* 0x2C8 */ /* double lbl_1_rodata_2C8 = 45; */
/* 0x2D0 */ /* double lbl_1_rodata_2D0 = 135; */
/* 0x2D8 */ /* double lbl_1_rodata_2D8 = 225; */
/* 0x2E0 */ /* double lbl_1_rodata_2E0 = 315; */
/* 0x2E8 */ /* double lbl_1_rodata_2E8 = -1000; */
/* 0x2F0 */ /* double lbl_1_rodata_2F0 = -900; */
/* 0x2F8 */ /* double lbl_1_rodata_2F8 = 900; */
/* 0x300 */ /* double lbl_1_rodata_300 = 360; */
/* 0x308 */ /* double lbl_1_rodata_308 = 50; */
/* 0x310 */ /* double lbl_1_rodata_310 = 0.0000152587890625; */
/* 0x318 */ /* float lbl_1_rodata_318 = 60.0f; */
/* 0x31C */ /* float lbl_1_rodata_31C = 300.0f; */
/* 0x320 */ /* float lbl_1_rodata_320 = 50.0f; */
/* 0x328 */ /* double lbl_1_rodata_328 = 300; */
/* 0x330 */ /* double lbl_1_rodata_330 = 1.5; */
/* 0x338 */ /* float lbl_1_rodata_338 = 28.0f; */
/* 0x340 */ /* double lbl_1_rodata_340 = 0.8; */
/* 0x348 */ /* double lbl_1_rodata_348 = -200; */
/* 0x350 */ /* double lbl_1_rodata_350 = 750; */
/* 0x358 */ /* float lbl_1_rodata_358 = 750.0f; */
/* 0x360 */ /* double lbl_1_rodata_360 = -750; */
/* 0x368 */ /* float lbl_1_rodata_368 = -750.0f; */
/* 0x370 */ /* double lbl_1_rodata_370 = 500; */
/* 0x378 */ /* double lbl_1_rodata_378 = -500; */
/* 0x380 */ /* double lbl_1_rodata_380 = 25; */
/* 0x388 */ /* double lbl_1_rodata_388 = 350; */
/* 0x390 */ /* double lbl_1_rodata_390 = 0.6; */
/* 0x398 */ /* double lbl_1_rodata_398 = 42; */
/* 0x3A0 */ /* float lbl_1_rodata_3A0 = 100000.0f; */
/* 0x3A4 */ /* float lbl_1_rodata_3A4 = 360.0f; */

/* --- .data --- */
/* 0x90 */ s32 lbl_1_data_90[8] = { 0x008700D5, 0x008700D6, 0x008700D7, 0x008700D8, 0x008700D9, 0x008C008E, 0x008C008F, 0x008C0090 };
/* 0xB0 */ M580_MOTPARAM lbl_1_data_B0[9] = {
    { 0, 0, 0.2f, 0x40000001 },
    { 1, 0, 0.2f, 0x40000001 },
    { 2, 0, 0.1f, 0 },
    { 3, 0, 0.1f, 0 },
    { 4, 0, 0.2f, 0 },
    { 5, 0, 0.15f, 0 },
    { 6, 0, 0.2f, 0x40000001 },
    { 6, 0, 0.2f, 0x40000001 },
    { 7, 0, 0.2f, 0 },
};
/* 0x11C */ HuVecF lbl_1_data_11C[4] = { { -5.5e+02f, 0.0f, -1e+02f }, { -2.5e+02f, 0.0f, 1e+02f }, { 2.5e+02f, 0.0f, 1e+02f }, { 5.5e+02f, 0.0f, -1e+02f } };
/* 0x14C */ float lbl_1_data_14C[4] = { 90.0f, 90.0f, 270.0f, 270.0f };
/* 0x15C */ HuVecF lbl_1_data_15C[2] = { { 0.0f, -1e+01f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
/* 0x174 */ HuVecF lbl_1_data_174[2] = { { -1.2e+03f, 0.0f, 0.0f }, { 1.2e+03f, 0.0f, 0.0f } };
/* 0x18C */ HuVecF lbl_1_data_18C[4] = { { -1.4e+02f, 0.0f, 0.0f }, { 1.4e+02f, 0.0f, 0.0f }, { -6e+02f, 0.0f, 0.0f }, { 6e+02f, 0.0f, 0.0f } };
/* 0x1BC */ HuVecF lbl_1_data_1BC[2] = { { 2e+02f, 0.0f, 0.0f }, { -2e+02f, 0.0f, 0.0f } };
/* 0x1D4 */ s32 lbl_1_data_1D4[2] = { 0x0086000B, 0x0086000C };
/* 0x1DC */ s32 lbl_1_data_1DC[2] = { 0x0086000D, 0x0086000E };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x9C */ OMOBJ *lbl_1_bss_9C[5]; /* player objects [0..3] (lwz then ->data); [4] unread by fork Q */
/* 0x9A gap_05_0000009A_bss (0x2) -- dtk filler */
/* 0x98 */ s16 lbl_1_bss_98[2]; /* dtk: s16 + 2-byte gap; use [0] */
/* 0x96 gap_05_00000096_bss (0x2) -- dtk filler */
/* 0x94 */ s16 lbl_1_bss_94[2]; /* dtk: s16 + 2-byte gap; use [0] */
/* 0x64 */ HuVecF lbl_1_bss_64[4]; /* COM idle positions (fn_1_74D4, mulli 0xC) */
/* 0x54 */ float lbl_1_bss_54[4]; /* COM idle rotY (fn_1_74D4, lfs) */
/* 0x50 */ s32 lbl_1_bss_50;

/* --- functions (reference order) --- */
/* 122 insns */
void fn_1_2804(OMOBJMAN *objman)
{
    s32 teamCnt[2] = { 0, 0 };
    s32 teamSlot[2] = { 0, 2 };
    s32 grp[4];
    s32 i;
    s32 bad;
    s32 team;
    OMOBJ *obj;

    bad = 0;
    for (i = 0; i < 4; i++) {
        team = grp[i] = GwPlayerConf[i].grp;
        if (team >= 2) {
            bad = 1;
        }
        else {
            teamCnt[team]++;
        }
    }
    if (teamCnt[0] != 2 || teamCnt[1] != 2) {
        bad = 1;
    }
    if (bad) {
        for (i = 0; i < 4; i++) {
            grp[i] = i >> 1;
        }
    }
    omMakeGroupEx(objman, 0, 4);
    lbl_1_bss_98[0] = -1;
    lbl_1_bss_94[0] = lbl_1_bss_94[1] = -1;
    lbl_1_bss_50 = 0;
    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_9C[i] = omAddObjEx(objman, 50, 2, 8, 0, fn_1_2A10);
        obj->work[0] = i;
        team = obj->work[1] = grp[i];
        obj->work[2] = teamSlot[team]++;
        fn_1_1E14(i, team, GwPlayerConf[i].charNo);
    }
}

/* 9 insns */
void fn_1_29EC(void)
{
    CharModelKill(-1);
}

/* 292 insns */
void fn_1_2A10(OMOBJ *obj)
{
    M580_PLAYER *work;
    M580_EFFECTSHADOW *eff;
    M580_COLLACTOR *coll;
    s32 i;
    s32 no;
    s32 team;
    s32 slot;
    s32 charNo;
    HU3DMODELID mdlId;
    HU3DMODELID linkId;
    char *hook;
    HU3DMOTID motId;

    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_PLAYER), HU_MEMNUM_OVL);
    work = obj->data;
    memset(work, 0, sizeof(M580_PLAYER));
    obj->stat |= OM_STAT_MODELPAUSE;
    work->unk000 = no = obj->work[0];
    work->unk004 = team = obj->work[1];
    work->unk008 = slot = obj->work[2];
    work->unk00C = charNo = GwPlayerConf[no].charNo;
    work->unk02C = GwPlayerConf[no].dif & 3;
    work->unk028 = GwPlayerConf[no].type;
    work->unk030 = 0;
    mdlId = CharModelCreate(charNo, 8);
    obj->mdlId[0] = mdlId;
    Hu3DModelLayerSet(mdlId, 5);
    CharEffectLayerSet(5);
    for (i = 0; i < 8; i++) {
        motId = CharMotionCreate(charNo, lbl_1_data_90[i]);
        obj->mtnId[i] = motId;
        if (i == 6) {
            Hu3DMotionAttrSet(motId, 1);
        }
    }
    CharMotionDataClose(charNo);
    if (lbl_1_bss_98[0] < 0) {
        linkId = lbl_1_bss_98[0] = Hu3DModelCreateData(0x86000A);
    }
    else {
        linkId = Hu3DModelLink(lbl_1_bss_98[0]);
    }
    hook = CharModelItemHookGet(charNo, 8, 2);
    Hu3DModelHookSet(mdlId, hook, linkId);
    linkId = Hu3DModelLink(lbl_1_bss_98[0]);
    hook = CharModelItemHookGet(charNo, 8, 3);
    Hu3DModelHookSet(mdlId, hook, linkId);
    if (lbl_1_bss_94[team] < 0) {
        linkId = lbl_1_bss_94[team] = Hu3DModelCreateData(lbl_1_data_1D4[team]);
    }
    else {
        linkId = Hu3DModelLink(lbl_1_bss_94[team]);
    }
    hook = CharModelItemHookGet(charNo, 8, 0);
    Hu3DModelHookSet(mdlId, hook, linkId);
    mdlId = Hu3DModelCreateData(lbl_1_data_1DC[team]);
    obj->mdlId[1] = mdlId;
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 5);
    work->unk0E0 = 0;
    work->unk0E4 = 0.0f;
    work->unk010 = -1;
    fn_1_7634(obj, 0);
    work->unk074 = lbl_1_data_11C[slot];
    work->unk080.x = work->unk080.y = work->unk080.z = 0.0f;
    work->unk08C = lbl_1_data_14C[slot];
    work->unk09C = ((work->unk008 ^ lbl_1_bss_50) & 1) == 0;
    eff = &work->unk0E8;
    eff->unk000 = 1;
    eff->unk004 = charNo;
    eff->unk008 = team;
    eff->unk00C = &work->unk074;
    eff->unk010 = lbl_1_data_15C;
    eff->unk014 = &work->unk08C;
    fn_1_ED34(eff);
    coll = &work->unk108;
    coll->unk000 = 0;
    coll->unk004 = 7;
    coll->unk008 = 0;
    coll->unk00C = no;
    coll->unk010 = 0;
    coll->unk014 = obj;
    coll->unk018 = (void (*)(void *))fn_1_5A14;
    coll->unk01C = (M580_COLLHITFUNC)fn_1_58D8;
    coll->unk020 = &work->unk074;
    coll->unk024 = &work->unk080;
    coll->unk028 = *coll->unk020;
    coll->unk034 = 40.0f;
    coll->unk038 = 0.5f;
    fn_1_11DC4(coll);
    work->unk068 = 0;
    work->unk0D4 = 1;
    work->unk0D8 = -1;
    obj->objFunc = fn_1_2EA0;
}

/* 584 insns */
void fn_1_2EA0(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    OMOBJ *partner;
    M580_PLAYER *partnerWork;
    HuVecF prevPos;
    HuVecF target;
    float rot;
    s32 idx;
    s32 padNo;
    s32 btnPad;
    float stkX;
    float stkY;

    partner = fn_1_7818(obj);
    partnerWork = partner->data;
    work->unk018 = 0;
    work->unk01C = 0;
    work->unk020 = 0.0f;
    work->unk024 = 0.0f;
    switch (work->unk068) {
        case 0:
            prevPos = work->unk074;
            if (fn_1_89A8(work->unk008, &work->unk074, &work->unk08C)) {
                PSVECSubtract(&work->unk074, &prevPos, &work->unk080);
                if (work->unk070 == 0 || PSVECMag(&work->unk080) < 1.0) {
                    fn_1_7634(obj, 0);
                }
                else {
                    fn_1_7634(obj, 1);
                }
                fn_1_3B30(obj);
                return;
            }
            idx = work->unk008;
            lbl_1_bss_64[idx] = work->unk074;
            lbl_1_bss_54[idx] = work->unk08C;
            work->unk0E0 = 1;
            work->unk108.unk000 |= 1;
            work->unk068++;
            work->unk06C = 0;
        case 1:
            work->unk068++;
            work->unk06C = 0;
            work->unk09C = ((work->unk008 ^ lbl_1_bss_50) & 1) == 0;
            work->unk030 = 0;
        case 2:
            if (fn_1_1D04() < 2) {
                work->unk068 = 7;
                break;
            }
            if (MgSeqModeGet() == 6) {
                work->unk068 = 7;
                break;
            }
            idx = (work->unk008 & 3) ^ (lbl_1_bss_50 & 1);
            target = lbl_1_bss_64[idx];
            rot = lbl_1_bss_54[idx];
            if (++work->unk06C < 180.0 && !fn_1_4F58(obj, &target, rot, 3.0f)) {
                break;
            }
            work->unk068++;
            work->unk06C = 0;
            work->unk098 = 0;
        case 3:
            if (MgSeqModeGet() == 6) {
                work->unk068 = 7;
                break;
            }
            idx = (work->unk008 & 3) ^ (lbl_1_bss_50 & 1);
            if ((idx & 1) == 0) {
                target = lbl_1_data_18C[work->unk004];
            }
            else {
                target = lbl_1_bss_64[idx];
            }
            rot = lbl_1_bss_54[idx];
            fn_1_4F58(obj, &target, rot, 2.0f);
            if (fn_1_D544()) {
                break;
            }
            work->unk098 = 0;
            if (work->unk09C) {
                work->unk068++;
                work->unk06C = 0;
            }
            else {
                work->unk068 += 2;
                work->unk06C = 0;
            }
        case 4:
            if (MgSeqModeGet() == 6) {
                work->unk068 = 7;
                break;
            }
            if (work->unk028) {
                fn_1_5B94(obj);
            }
            else {
                btnPad = GwPlayerConf[work->unk000].padNo;
                work->unk01C = HuPadBtn[btnPad];
                work->unk018 = HuPadBtnDown[btnPad];
            }
            if (fn_1_D6EC()) {
                break;
            }
            work->unk068++;
            work->unk06C = 0;
        case 5:
            if (++work->unk06C < 18.0) {
                break;
            }
            work->unk068++;
            work->unk06C = 0;
        case 6:
            if (MgSeqModeGet() == 6) {
                work->unk068++;
                break;
            }
            if (fn_1_D544()) {
                work->unk068 = 1;
                work->unk06C = 0;
                if (work->unk000 == 0) {
                    lbl_1_bss_50 ^= 1;
                    HuAudFXPlay(0x965);
                    fn_1_246C(180);
                }
                if (work->unk004 == fn_1_D7B8()) {
                    fn_1_7634(obj, 6);
                    work->unk094 = 1;
                    fn_1_4124(obj, 0x1F8);
                }
                break;
            }
            if (work->unk028) {
                fn_1_5B94(obj);
                break;
            }
            padNo = GwPlayerConf[work->unk000].padNo;
            stkX = HuPadStkX[padNo];
            stkY = -HuPadStkY[padNo];
            work->unk01C = HuPadBtn[padNo];
            work->unk018 = HuPadBtnDown[padNo];
            work->unk020 = 180.0 * (atan2(stkX, stkY) / M_PI);
            work->unk024 = (1.0f / 56.0f) * PlayerSqrtF(stkX * stkX + stkY * stkY);
            if (work->unk024 > 1.0f) {
                work->unk024 = 1.0f;
            }
            break;
        case 7:
            if (MgSeqModeGet() == 5) {
                PSVECScale(&work->unk080, &work->unk080, 0.98f);
                break;
            }
            work->unk068++;
            work->unk06C = 0;
            work->unk090 = 1;
            work->unk0E0 = 0;
        case 8:
            if (++work->unk06C < 10) {
                break;
            }
            fn_1_7634(obj, 0);
            work->unk068 = 0;
            obj->objFunc = fn_1_37C0;
            break;
    }
    if (work->unk010 == 6 && work->unk014 > 60.0) {
        work->unk094 = 0;
    }
    fn_1_4488(obj);
    fn_1_4198(obj);
    PSVECAdd(&work->unk074, &work->unk080, &work->unk074);
    fn_1_3B30(obj);
}

/* .data after jumptable_1_data_1E4 (fn_1_2EA0): defined below it so CW keeps the order */
/* 0x208 */ M580_COMPARAM lbl_1_data_208[4] = {
    { 0.3f, 0.2f, 0.05f, 0.0f, 10, 6 },
    { 0.5f, 0.4f, 0.2f, 0.0f, 9, 4 },
    { 0.7f, 0.6f, 0.5f, 0.15f, 8, 3 },
    { 0.95f, 0.8f, 0.8f, 0.3f, 7, 2 },
};
/* 0x268 */ HuVecF lbl_1_data_268[4] = { { -7e+02f, 0.0f, -4e+02f }, { -7e+02f, 0.0f, 4e+02f }, { 7e+02f, 0.0f, -4e+02f }, { 7e+02f, 0.0f, 4e+02f } };

/* 220 insns */
void fn_1_37C0(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    s32 timer;
    float x;
    s32 ret;

    work->unk018 = 0;
    work->unk01C = 0;
    work->unk020 = 0.0f;
    work->unk024 = 0.0f;
    switch (work->unk068) {
        case 0:
            fn_1_7634(obj, 0);
            work->unk090 = 1;
            work->unk094 = 0;
            work->unk068++;
        case 1:
            PSVECScale(&work->unk080, &work->unk080, 0.98f);
            if (MgSeqModeGet() == 6) {
                break;
            }
            work->unk068++;
            work->unk06C = 0;
        case 2:
            timer = work->unk06C++;
            x = work->unk074.x;
            if ((x > -800.0 && x < 800.0) || timer > 60.0) {
                work->unk108.unk000 &= ~1;
            }
            if (timer > 120.0) {
                work->unk108.unk000 |= 1;
            }
            ret = fn_1_4F58(obj, &lbl_1_data_11C[work->unk008], 0.0f, 1.5f);
            if (ret == 0 && timer < 180.0) {
                break;
            }
            work->unk068++;
            work->unk108.unk000 |= 1;
            fn_1_1EC4(work->unk000);
            break;
        case 3:
            fn_1_4F58(obj, &lbl_1_data_11C[work->unk008], 0.0f, 1.0f);
            if (MgSeqModeGet() != 8) {
                break;
            }
            if (!fn_1_1EE4()) {
                break;
            }
            work->unk0D4 = 0;
            CharModelVoiceVolSet(work->unk00C, 127);
            if (fn_1_1D40(work->unk000) >= 0) {
                fn_1_7634(obj, 7);
                CharFXPlayPan(work->unk00C, 0x1FA, fn_1_2004(&work->unk074));
            }
            else {
                fn_1_7634(obj, 8);
                fn_1_1F34(work->unk000);
            }
            work->unk068++;
            break;
        case 4:
            if (fn_1_774C(obj)) {
                work->unk068++;
            }
            break;
        case 5:
            break;
    }
    PSVECAdd(&work->unk074, &work->unk080, &work->unk074);
    fn_1_3B30(obj);
}

/* 217 insns */
void fn_1_3B30(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    float radius;
    float x;
    float z;
    float ang;

    work->unk070++;
    work->unk014++;
    if (work->unk094 && fn_1_774C(obj)) {
        work->unk094 = 0;
    }
    if (fn_1_D30C(NULL, NULL) == obj) {
        work->unk108.unk000 |= 0x10;
    }
    else {
        work->unk108.unk000 &= ~0x10;
    }
    if (work->unk0E0) {
        if ((work->unk0E4 += 0.05) > 1.0) {
            work->unk0E4 = 1.0f;
        }
    }
    else {
        if ((work->unk0E4 -= 0.05) <= 0.0) {
            work->unk0E4 = 0.0f;
        }
    }
    if (fn_1_D6EC() && !work->unk09C) {
        radius = 350.0f;
        x = work->unk074.x;
        z = work->unk074.z;
        if (PlayerSqrtF(x * x + z * z) < radius) {
            ang = 180.0 * (atan2(x, z) / M_PI);
            work->unk074.x = radius * sin(M_PI * ang / 180.0);
            work->unk074.z = radius * cos(M_PI * ang / 180.0);
        }
    }
    fn_1_3E94(obj);
}

/* 164 insns */
void fn_1_3E94(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    s32 foot;
    s32 charNo;
    HU3DMODELID mdlId;
    char *hookL;
    char *hookR;
    HuVecF posR;
    HuVecF posL;

    foot = 0;
    CharModelVoicePanSet(work->unk00C, fn_1_2004(&work->unk074));
    if (work->unk0D4) {
        CharModelVoiceVolSet(work->unk00C, fn_1_2098(&work->unk074));
    }
    if ((work->unk070 ^ work->unk000) & 1) {
        if (PSVECMag(&work->unk080) > 2.0) {
            charNo = work->unk00C;
            mdlId = obj->mdlId[0];
            hookL = CharModelItemHookGet(charNo, 8, 2);
            hookR = CharModelItemHookGet(charNo, 8, 3);
            Hu3DModelObjPosGet(mdlId, hookL, &posL);
            Hu3DModelObjPosGet(mdlId, hookR, &posR);
            if (posL.y < posR.y) {
                fn_1_EBCC(&posL);
                foot = 1;
            }
            else {
                fn_1_EBCC(&posR);
                foot = 0;
            }
            if (work->unk070 > 30.0 && work->unk0A0 != foot) {
                fn_1_212C(0x961, &work->unk074);
            }
            work->unk0A0 = foot;
        }
    }
    if (MgSeqModeGet() == 5) {
        if (work->unk0C0) {
            work->unk0C4 = 0;
        }
        else if (++work->unk0C4 < 18) {
            work->unk0C0 = work->unk0BC;
        }
        if (!work->unk0BC && work->unk0C0) {
            fn_1_212C(0x967, &work->unk074);
        }
        work->unk0BC = work->unk0C0;
        work->unk0C0 = 0;
        if (work->unk0CC) {
            work->unk0D0 = 0;
        }
        else if (++work->unk0D0 < 18) {
            work->unk0CC = work->unk0C8;
        }
        if (!work->unk0C8 && work->unk0CC) {
            fn_1_212C(0x968, &work->unk074);
        }
        work->unk0C8 = work->unk0CC;
        work->unk0CC = 0;
    }
    if (work->unk0D8 != -1) {
        if (HuAudFXStatusGet(work->unk0D8) == 2) {
            fn_1_2318(work->unk0D8, &work->unk074);
        }
        else {
            work->unk0D8 = -1;
        }
    }
}

/* 29 insns */
void fn_1_4124(OMOBJ *obj, s32 seNo)
{
    M580_PLAYER *work = obj->data;

    /* fork Q's spelling: raw=0 here and in its inlined copy in fn_1_58D8 (fork P's
     * split `pan` local gave a register swap in both) */
    work->unk0D8 = CharFXPlayVolPan(work->unk00C, seNo, fn_1_2098(&work->unk074), fn_1_2004(&work->unk074));
}

/* 157 insns */
void fn_1_4198(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    float speed;
    float motSpeed;
    float vx;
    float vz;

    speed = work->unk024;
    if (work->unk098) {
        return;
    }
    if (fn_1_D544()) {
        return;
    }
    if (fn_1_D6EC() && work->unk09C) {
        return;
    }
    if (obj == fn_1_D30C(NULL, NULL)) {
        speed *= 0.7;
    }
    if (speed > 0.05f && !work->unk090) {
        if (!work->unk0A8) {
            work->unk08C = fn_1_2634(work->unk08C, work->unk020, 0.3f);
        }
        if (!work->unk094) {
            vx = (1.0f / 60.0f) * (1000.0 * (speed * sin(M_PI * work->unk020 / 180.0)));
            vz = (1.0f / 60.0f) * (1000.0 * (speed * cos(M_PI * work->unk020 / 180.0)));
            work->unk080.x = work->unk080.x + 0.03 * (vx - work->unk080.x);
            work->unk080.z = work->unk080.z + 0.03 * (vz - work->unk080.z);
            fn_1_7634(obj, 1);
            motSpeed = 1.2f * speed;
            Hu3DMotionSpeedSet(obj->mdlId[0], motSpeed);
        }
    }
    else {
        if (!work->unk094) {
            fn_1_7634(obj, 0);
        }
        PSVECScale(&work->unk080, &work->unk080, 0.99f);
    }
}

/* 31 insns */
void fn_1_440C(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    work->unk0A4 = 0;
    work->unk0A8 = 0;
    work->unk0AC = 0;
    work->unk0B0 = 0;
    work->unk0B4 = 0;
    work->unk0B8 = 0;
    CharMotionSpeedSet(work->unk00C, 1.0f);
}

/* 597 insns */
void fn_1_4488(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    OMOBJ *partner;
    M580_PLAYER *partnerWork;
    OMOBJ *owner;
    s32 canHit;
    float reach;
    float magSq;
    float mag;
    float ang; /* hit range, then rotY, then the aim heading */
    float speed; /* shot speed, also the lead time */
    HuVecF puckPos;
    HuVecF aim;
    HuVecF puckVel;

    reach = 120.0f;
    work->unk108.unk000 &= ~4;
    if (fn_1_D544()) {
        fn_1_440C(obj);
        return;
    }
    if (fn_1_D6EC() && work->unk09C) {
        fn_1_4DDC(obj);
        return;
    }
    if (work->unk0A4) {
        work->unk0A4--;
    }
    if (work->unk0B8) {
        work->unk0B8--;
    }
    if (work->unk0AC) {
        work->unk0AC--;
    }
    if (work->unk0B4) {
        work->unk0B4--;
        PSVECScale(&work->unk080, &work->unk080, 0.9f);
        work->unk108.unk000 |= 4;
    }
    if (work->unk010 == 2 && work->unk014 > 60) {
        work->unk094 = 0;
    }
    partner = fn_1_7818(obj);
    partnerWork = partner->data;
    owner = fn_1_D30C(&puckPos, &puckVel);
    magSq = puckVel.x * puckVel.x + puckVel.z * puckVel.z;
    mag = PlayerSqrtF(magSq);
    if (owner != obj) {
        work->unk0A4 = 0;
        work->unk0A8 = 0;
        work->unk0B0 = 0;
        if (work->unk0B8 == 0) {
            canHit = 0;
            if (work->unk0AC == 0) {
                ang = 45.0f;
                canHit = 1;
            }
            else {
                ang = 120.0f;
                canHit = 1;
            }
            if (owner != NULL && owner->work[0] >= 4) {
                canHit = 0;
            }
            if (canHit && fn_1_D054(&work->unk074, work->unk08C, ang, reach)) {
                owner = fn_1_D390(NULL, 1.0f, NULL, obj);
                work->unk0A4 = 30;
                fn_1_7634(obj, 4);
                work->unk094 = 1;
            }
        }
        if (work->unk0B4 == 0 && owner != obj && (work->unk018 & 0x200)) {
            fn_1_7634(obj, 5);
            work->unk094 = 1;
        }
        if (work->unk010 == 5 && work->unk014 == 12) {
            work->unk080.x = (1.0f / 60.0f) * (100.0 * (15.0 * sin(M_PI * work->unk08C / 180.0)));
            work->unk080.z = (1.0f / 60.0f) * (100.0 * (15.0 * cos(M_PI * work->unk08C / 180.0)));
            work->unk0B4 = 18;
        }
    }
    while (owner == obj) {
        if (fn_1_7A6C(obj, &puckPos) > 80.0 + reach) {
            owner = fn_1_D390(NULL, 1.0f, NULL, NULL);
            break;
        }
        {
            work->unk0B0++;
            ang = work->unk08C;
            puckPos.x = work->unk074.x + reach * sin(M_PI * ang / 180.0);
            puckPos.y = work->unk074.y;
            puckPos.z = work->unk074.z + reach * cos(M_PI * ang / 180.0);
            puckVel.x = puckVel.y = puckVel.z = 0.0f;
            if (work->unk010 != 2) {
                if (work->unk018 & 0x200) {
                    fn_1_7634(obj, 2);
                    work->unk094 = 1;
                }
            }
            else {
                PSVECScale(&work->unk080, &work->unk080, 0.98f);
                if (work->unk014 < 24) {
                    if (CharMotionTimeGet(work->unk00C) >= 15.0) {
                        CharMotionSpeedSet(work->unk00C, 0.0f);
                    }
                }
                else {
                    CharMotionSpeedSet(work->unk00C, 1.0f);
                }
                if (work->unk014 == 28) {
                    work->unk0B8 = 12;
                    ang = work->unk08C;
                    speed = 66.66667f;
                    puckVel.x = speed * sin(M_PI * ang / 180.0);
                    puckVel.y = 20.000002f;
                    puckVel.z = speed * cos(M_PI * ang / 180.0);
                    owner = fn_1_D390(NULL, 1.0f, NULL, NULL);
                    omVibrate(work->unk000, 20, 6, 6);
                }
            }
            if (owner != NULL && (work->unk01C & 0x400)) {
                fn_1_7634(obj, 3);
                work->unk094 = 1;
            }
            if (owner != NULL) {
                if (!work->unk0A8) {
                    if (work->unk0A4 == 0 && (work->unk01C & 0x100)) {
                        work->unk0A8 = 1;
                    }
                }
                else {
                    if (work->unk0A8 == 1) {
                        fn_1_7634(obj, 3);
                        work->unk094 = 1;
                    }
                    speed = fn_1_7A6C(obj, &partnerWork->unk074) / 33.33333507180214;
                    aim.x = partnerWork->unk074.x + partnerWork->unk080.x * speed;
                    aim.y = partnerWork->unk074.y;
                    aim.z = partnerWork->unk074.z + partnerWork->unk080.z * speed;
                    ang = fn_1_79C4(obj, &aim);
                    work->unk08C = fn_1_2634(work->unk08C, ang, 0.3f);
                    work->unk0A8++;
                }

            }
            if (owner != NULL && work->unk010 == 3 && work->unk014 == 13) {
                work->unk0B8 = 12;
                partnerWork->unk0AC = 90;
                ang = work->unk08C;
                speed = 33.333336f;
                puckVel.x = speed * sin(M_PI * ang / 180.0);
                puckVel.z = speed * cos(M_PI * ang / 180.0);
                owner = fn_1_D390(NULL, 1.0f, NULL, NULL);
                omVibrate(work->unk000, 12, 6, 6);
            }
            fn_1_D390(&puckPos, 0.3f, &puckVel, owner);
        }
        break;
    }
    if (owner != obj) {
        work->unk0A4 = 0;
        work->unk0A8 = 0;
    }
}

/* 95 insns */
void fn_1_4DDC(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_PLAYER *partnerWork;
    OMOBJ *partner;
    OMOBJ *owner;
    float rot;
    float reach;
    HuVecF puckPos;
    HuVecF puckVel;

    reach = 120.0f;
    partner = fn_1_7818(obj);
    partnerWork = partner->data;
    if (work->unk018 & 0x100) {
        fn_1_7634(obj, 4);
        work->unk094 = 1;
        if (fn_1_D714(obj)) {
            work->unk0A8 = 1;
            partnerWork->unk0AC = 90;
        }
    }
    owner = fn_1_D30C(&puckPos, &puckVel);
    if (owner == obj) {
        rot = work->unk08C;
        puckPos.x = work->unk074.x + reach * sin(M_PI * rot / 180.0);
        puckPos.y = work->unk074.y;
        puckPos.z = work->unk074.z + reach * cos(M_PI * rot / 180.0);
        puckVel.x = puckVel.y = puckVel.z = 0.0f;
        fn_1_D390(&puckPos, 0.3f, &puckVel, obj);
    }
}

/* 363 insns */
s32 fn_1_4F58(OMOBJ *obj, HuVecF *target, float rot, float speed)
{
    M580_PLAYER *work = obj->data;
    float dx;
    float dz;
    float dist;
    float tmp; /* motion speed, then the heading to the target */
    float vx;
    float vz;
    float k;

    if (obj == fn_1_D30C(NULL, NULL)) {
        speed *= 0.7;
    }
    work->unk098 = 1;
    dx = target->x - work->unk074.x;
    dz = target->z - work->unk074.z;
    dist = PlayerSqrtF(dx * dx + dz * dz);
    if (dist < 200.0) {
        speed = 0.5f;
        if (dist < 100.0) {
            speed = 0.2f;
        }
    }
    if (dist < 70.0) {
        if (!work->unk094) {
            if (dist < 20.0) {
                fn_1_7634(obj, 0);
            }
            else {
                fn_1_7634(obj, 1);
                tmp = 0.5f;
                Hu3DMotionSpeedSet(obj->mdlId[0], tmp);
            }
        }
        work->unk074.x = work->unk074.x + 0.1 * dx;
        work->unk074.z = work->unk074.z + 0.1 * dz;
        PSVECScale(&work->unk080, &work->unk080, 0.8f);
        work->unk08C = fn_1_2634(work->unk08C, rot, 0.1f);
        if (dist > 35.0) {
            return 0;
        }
        if (fn_1_2750(work->unk08C, rot) > 4.0) {
            return 0;
        }
        if (PSVECMag(&work->unk080) > 2.0) {
            return 0;
        }
        work->unk080.x = work->unk080.z = 0.0f;
        work->unk08C = rot;
        work->unk098 = 0;
        return 1;
    }
    if (!work->unk094) {
        fn_1_7634(obj, 1);
        tmp = 0.8f * speed;
        Hu3DMotionSpeedSet(obj->mdlId[0], tmp);
    }
    tmp = 180.0 * (atan2(dx, dz) / M_PI);
    work->unk08C = fn_1_2634(work->unk08C, tmp, 0.3f);
    vx = (1.0f / 60.0f) * (1000.0 * (speed * sin(M_PI * work->unk08C / 180.0)));
    vz = (1.0f / 60.0f) * (1000.0 * (speed * cos(M_PI * work->unk08C / 180.0)));
    k = 0.1f;
    work->unk080.x = work->unk080.x + k * (vx - work->unk080.x);
    if (fn_1_5504(obj)) {
        if (work->unk074.z < 0.0f) {
            vz = -16.666668f;
        }
        else {
            vz = 16.666668f;
        }
        k = 0.2f;
    }
    work->unk080.z = work->unk080.z + k * (vz - work->unk080.z);
    return 0;
}

/* 39 insns */
s32 fn_1_5504(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    if (work->unk074.z < -250.0) {
        return 0;
    }
    if (work->unk074.z > 250.0) {
        return 0;
    }
    if (work->unk074.x < -1100.0) {
        return 1;
    }
    if (work->unk074.x > 1100.0) {
        return 1;
    }
    return 0;
}

/* 89 insns. In the goal-mouth strip and facing the boards. */
s32 fn_1_55A0(OMOBJ *obj)
{
    M580_PLAYER *work;

    if (fn_1_5504(obj)) {
        work = obj->data;
        if (work->unk074.x < 0.0f) {
            if (work->unk08C < 45.0) {
                return 0;
            }
            if (work->unk08C > 135.0) {
                return 0;
            }
            return 1;
        } else {
            if (work->unk08C < 225.0) {
                return 0;
            }
            if (work->unk08C > 315.0) {
                return 0;
            }
            return 1;
        }
    }
    return 0;
}

/* 27 insns. TRUE while the puck is behind a goal line (|x| > 1000). */
s32 fn_1_5704(void)
{
    HuVecF pos;

    fn_1_D30C(&pos, NULL);
    if (pos.x < -1000.0) {
        return 1;
    }
    if (pos.x > 1000.0) {
        return 1;
    }
    return 0;
}

/* 51 insns */
s32 fn_1_5770(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    if (work->unk074.z < -250.0) {
        return 0;
    }
    if (work->unk074.z > 250.0) {
        return 0;
    }
    if (work->unk074.x > -1000.0 && work->unk074.x < -800.0) {
        return 1;
    }
    if (work->unk074.x > 800.0 && work->unk074.x < 1000.0) {
        return 1;
    }
    return 0;
}

/* 39 insns */
s32 fn_1_583C(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    if (work->unk074.z < -250.0) {
        return 0;
    }
    if (work->unk074.z > 250.0) {
        return 0;
    }
    if (work->unk074.x < -900.0) {
        return 1;
    }
    if (work->unk074.x > 900.0) {
        return 1;
    }
    return 0;
}

/* 79 insns. Collision hit callback (M580_COLLACTOR.unk01C). */
s32 fn_1_58D8(M580_COLLACTOR *self, M580_COLLACTOR *other)
{
    OMOBJ *obj = self->unk014;
    M580_PLAYER *work = obj->data;
    OMOBJ *otherObj;
    M580_PLAYER *otherWork;

    if (other->unk000 & 4) {
        if (obj == fn_1_D30C(NULL, NULL)) {
            fn_1_D390(NULL, 1.0f, NULL, NULL);
            work->unk0B8 = 30;
        }
        omVibrate(work->unk000, 20, 12, 0);
        fn_1_4124(obj, 0x1FC);
        if (other->unk008 == 0) {
            otherObj = other->unk014;
            otherWork = otherObj->data;
            omVibrate(otherWork->unk000, 20, 12, 0);
        }
    }
    switch ((s32)other->unk008) {
        case 0:
        case 2:
            work->unk0C0 = 1;
            break;
        case 3:
            work->unk0CC = 1;
            break;
    }
    return 1;
}

/* 96 insns. Collision post callback (M580_COLLACTOR.unk018): place the models. */
void fn_1_5A14(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    HU3DMODELID mdlId;

    work->unk08C = fmodf(work->unk08C, 360.0f);
    if (work->unk08C < 0.0) {
        work->unk08C += 360.0;
    }
    mdlId = obj->mdlId[0];
    Hu3DModelPosSetV(mdlId, &work->unk074);
    Hu3DModelRotSet(mdlId, 0.0f, work->unk08C, 0.0f);
    mdlId = obj->mdlId[1];
    if (work->unk0E4 > 0.0) {
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSetV(mdlId, &work->unk074);
        Hu3DModelScaleSet(mdlId, work->unk0E4, 1.0f, work->unk0E4);
    } else {
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    }
    work->unk108.unk028 = work->unk074;
    fn_1_1908(&work->unk074);
}

/* 52 insns. COM input, once per frame. */
void fn_1_5B94(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];

    work->unk098 = 0;
    if (work->unk038 != 0) {
        work->unk038--;
    }
    switch (work->unk030) {
        case 0:
            work->unk030++;
            work->unk03C = -1;
            work->unk050 = -1;
            fn_1_5C64(obj, fn_1_6548);
        case 1:
            work->unk03C = fn_1_78B4(obj);
            work->unk04C(obj);
            break;
    }
}

/* 19 insns */
void fn_1_5C64(OMOBJ *obj, M580_COMFUNC func)
{
    M580_PLAYER *work = obj->data;

    work->unk04C = func;
    work->unk054 = 0;
    work->unk058 = 0;
    work->unk05C = 0.0f;
    work->unk060 = 0;
    work->unk064 = 0;
}


/* 457 insns. COM: steer toward target; TRUE once there. */
s32 fn_1_5CB0(OMOBJ *obj, HuVecF *target, float rotY, float speed)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    HuVecF pos = *target;
    HuVecF puckPos;
    HuVecF aim;
    float dx;
    float dz;
    float dist;
    s32 idx;

    if (work->unk03C != 1) {
        if (fn_1_5704() && fn_1_5770(obj)) {
            if (fn_1_583C(obj)) {
                pos = work->unk074;
                pos.x = 0.0f;
            } else {
                idx = (work->unk074.x < 0.0f) ? 0 : 2;
                if (work->unk074.z > 0.0f) {
                    idx++;
                }
                pos = lbl_1_data_268[idx];
            }
        }
    }
    dx = pos.x - work->unk074.x;
    dz = pos.z - work->unk074.z;
    dist = PlayerSqrtF(dx * dx + dz * dz);
    if (dist > 100.0) {
        aim.x = pos.x - 50.0 * sin(M_PI * work->unk08C / 180.0);
        aim.y = pos.y;
        aim.z = pos.z - 50.0 * cos(M_PI * work->unk08C / 180.0);
        work->unk020 = fn_1_79C4(obj, &aim);
        work->unk024 = speed;
    } else if (dist < 50.0) {
        work->unk020 = rotY;
        if (dist > 20.0) {
            work->unk024 = 0.0f;
        } else {
            work->unk024 = 0.1f;
        }
        return 1;
    } else {
        work->unk020 = fn_1_79C4(obj, &pos);
        work->unk024 = 0.5 * speed;
    }
    if (fn_1_55A0(obj)) {
        if (work->unk08C < 180.0) {
            work->unk020 += 30.0;
        } else {
            work->unk020 -= 30.0;
        }
    }
    return 0;
}

/* 31 insns. Mode changed: restart through the dispatcher. */
s32 fn_1_63D4(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    if (work->unk03C != work->unk050) {
        fn_1_5C64(obj, fn_1_6450);
        return 1;
    }
    return 0;
}

/* 62 insns. COM mode dispatcher. */
void fn_1_6450(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMFUNC func;

    switch (work->unk03C) {
        case 0:
            func = fn_1_6754;
            break;
        case 1:
            func = fn_1_6878;
            break;
        case 2:
            func = fn_1_6D84;
            break;
        case 3:
            func = fn_1_6FC4;
            break;
        default:
            func = fn_1_74D4;
            break;
    }
    fn_1_5C64(obj, func);
    work->unk050 = work->unk03C;
    work->unk04C(obj);
}

/* 131 insns. COM face-off: wait for the drop, press A. */
void fn_1_6548(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];

    switch (work->unk054) {
        case 0:
            work->unk054++;
        case 1:
            if (fn_1_D544()) {
                break;
            }
            work->unk054++;
            work->unk058 = 6;
        case 2:
            if (work->unk09C && --work->unk058 <= 0) {
                work->unk018 |= PAD_BUTTON_A;
                work->unk01C |= PAD_BUTTON_A;
                work->unk058 = param->unk10 + (s32)(param->unk14 * ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF)));
            }
            if (fn_1_D6EC()) {
                break;
            }
            work->unk054++;
            work->unk058 = 0;
        case 3:
            if (++work->unk058 < 30.0) {
                break;
            }
            fn_1_5C64(obj, fn_1_6450);
            break;
    }
}

/* 73 insns. COM mode 0: the puck is loose. */
void fn_1_6754(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    OMOBJ *holder;
    s32 retarget;

    if (fn_1_63D4(obj)) {
        return;
    }
    retarget = 0;
    if (work->unk0AC) {
        retarget = 1;
    }
    if (++work->unk058 > 30) {
        work->unk058 = 0;
        retarget = 1;
    }
    if (retarget) {
        holder = fn_1_D30C(&work->unk040, NULL);
    }
    fn_1_5CB0(obj, &work->unk040, 0.0f, 1.0f);
}

/* 323 insns. COM mode 1: this player holds the puck. */
void fn_1_6878(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    OMOBJ *partner = fn_1_7818(obj);
    M580_PLAYER *partnerWork = partner->data;
    HuVecF puckPos;
    HuVecF aim;
    HuVecF puckVel;
    OMOBJ *holder = fn_1_D30C(&puckPos, &puckVel);
    OMOBJ *target;
    float myDist;
    float partnerDist;
    s32 flag;
    float goalX;

    if (fn_1_63D4(obj)) {
        return;
    }
    if (work->unk010 == 3) {
        return;
    }
    if (work->unk054 == 0) {
        while (++work->unk058 < 30) {
            if (work->unk058 == 1) {
                if (work->unk004 == 0 && work->unk074.x < 0.0f) {
                    break;
                }
                if (work->unk004 == 1 && work->unk074.x > 0.0f) {
                    break;
                }
                target = fn_1_7E48(work->unk004 ^ 1, NULL, &work->unk074, work->unk08C, 60.0f, 300.0f, 1);
                if (target == NULL) {
                    break;
                }
                fn_1_8194(target, &work->unk040, NULL);
            }
            work->unk020 = 180.0 + fn_1_79C4(obj, &work->unk040);
            work->unk024 = 1.0f;
            return;
        }
        work->unk054++;
        work->unk058 = 0;
    }
    myDist = fn_1_7A6C(obj, &lbl_1_data_174[work->unk004 ^ 1]);
    partnerDist = fn_1_7A6C(partner, &lbl_1_data_174[work->unk004 ^ 1]);
    flag = 0;
    if (myDist > 100.0 + partnerDist) {
        flag = 1;
    }
    if (fn_1_7E48(work->unk004 ^ 1, NULL, &work->unk074, work->unk08C, 50.0f, 300.0 + 100.0 * (1.5 * param->unk00), 1) != NULL) {
        flag = 1;
    }
    if (work->unk0A4) {
        flag = 0;
    }
    if (flag && (1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) < param->unk08 && fn_1_7BE4(obj, &partnerWork->unk074, 28.0f)) {
        work->unk018 |= PAD_BUTTON_A;
        work->unk01C |= PAD_BUTTON_A;
        return;
    }
    if (work->unk010 != 2) {
        flag = 0;
        goalX = lbl_1_data_1BC[work->unk004].x;
        if (goalX > 0.0f) {
            if (work->unk074.x >= goalX - 50.0) {
                flag = 1;
            }
        } else {
            if (work->unk074.x <= 50.0 + goalX) {
                flag = 1;
            }
        }
        if (flag) {
            work->unk018 |= PAD_BUTTON_B;
            work->unk01C |= PAD_BUTTON_B;
            work->unk040 = lbl_1_data_174[work->unk004 ^ 1];
        } else {
            aim.x = goalX;
            aim.y = work->unk074.y;
            aim.z = 0.8 * work->unk074.z;
            fn_1_5CB0(obj, &aim, lbl_1_data_14C[work->unk008], 1.0f);
            work->unk020 += 15.0;
        }
    } else {
        work->unk020 = fn_1_79C4(obj, &work->unk040);
        work->unk024 = 0.5f;
    }
}

/* 144 insns. COM mode 2: the partner holds the puck. */
void fn_1_6D84(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    OMOBJ *partner = fn_1_7818(obj);
    M580_PLAYER *partnerWork = partner->data;
    HuVecF puckPos;
    HuVecF pos;
    HuVecF puckVel;
    OMOBJ *holder = fn_1_D30C(&puckPos, &puckVel);
    float z;

    if (fn_1_63D4(obj)) {
        return;
    }
    pos = partnerWork->unk074;
    pos.x += (partnerWork->unk080.x < 0.0f) ? -200.0 : 200.0;
    if (pos.x > 750.0) {
        pos.x = 750.0f;
    }
    if (pos.x < -750.0) {
        pos.x = -750.0f;
    }
    z = (pos.z < 0.0f) ? 500.0 : -500.0;
    pos.z = pos.z + 0.8 * (z - pos.z);
    fn_1_5CB0(obj, &pos, 180.0 + partnerWork->unk08C, 1.0f);
}

/* 324 insns. COM mode 3: the other team holds the puck. */
void fn_1_6FC4(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    OMOBJ *partner = fn_1_7818(obj);
    M580_PLAYER *partnerWork = partner->data;
    HuVecF puckPos;
    HuVecF pos;
    HuVecF puckVel;
    OMOBJ *holder = fn_1_D30C(&puckPos, &puckVel);
    float myDist;
    float partnerDist;
    s32 chase;

    if (work->unk03C != 0) {
        if (work->unk03C == 2) {
            if (partnerWork->unk0B0 > 30.0 && fn_1_63D4(obj)) {
                return;
            }
        } else if (fn_1_63D4(obj)) {
            return;
        }
    }
    if (work->unk054 == 0) {
        work->unk054++;
        work->unk060 = ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) < param->unk00) ? 0 : 1;
    }
    myDist = fn_1_7A6C(obj, &puckPos);
    partnerDist = fn_1_7A6C(partner, &puckPos);
    chase = 0;
    if (work->unk060 == 0) {
        if (myDist < partnerDist) {
            chase = 1;
        }
    } else {
        chase = 1;
    }
    if (chase) {
        if (--work->unk058 <= 0) {
            work->unk064 = ((1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) < param->unk04) ? 0 : 1;
            work->unk058 = 60;
        }
        if ((work->unk05C -= param->unk04) < 0.0) {
            work->unk05C = 2.0f;
            work->unk040 = puckPos;
        }
        fn_1_5CB0(obj, &work->unk040, 0.0f, 1.0f);
        if (work->unk064) {
            work->unk020 += 25.0;
        }
        if (myDist < 350.0 && work->unk038 == 0 && (1.0 / 65536.0) * (float)((s32)frand() & 0xFFFF) < param->unk0C) {
            work->unk01C |= PAD_BUTTON_B;
            work->unk018 |= PAD_BUTTON_B;
            work->unk038 = 120;
        }
        if (work->unk038 < 60.0) {
            work->unk020 += 15.0;
        }
    } else {
        pos = lbl_1_data_174[work->unk004];
        pos.x = pos.x + 0.6 * (puckPos.x - pos.x);
        pos.z = pos.z + 0.6 * (puckPos.z - pos.z);
        fn_1_5CB0(obj, &pos, lbl_1_data_14C[work->unk008], 1.0f);
    }
}

/* 88 insns. COM default mode (-1: nobody can play the puck): go home. */
void fn_1_74D4(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    M580_COMPARAM *param = &lbl_1_data_208[work->unk02C];
    s32 idx;

    if (work->unk03C == -1) {
        work->unk058 = 0;
    }
    if (++work->unk058 > 42.0 && fn_1_63D4(obj)) {
        return;
    }
    idx = (work->unk008 & 3) ^ (lbl_1_bss_50 & 1);
    fn_1_5CB0(obj, &lbl_1_bss_64[idx], lbl_1_bss_54[idx], 1.0f);
}

/* 70 insns. Set a lbl_1_data_B0 motion. */
void fn_1_7634(OMOBJ *obj, u32 motNo)
{
    M580_PLAYER *work = obj->data;
    float shift;
    u32 attr;
    HU3DMOTID motId;

    if (work->unk010 != motNo && motNo < 9) {
        if (work->unk010 < 0) {
            shift = 0.0f;
        } else {
            shift = 60.0f * lbl_1_data_B0[motNo].unk04;
        }
        work->unk010 = motNo;
        work->unk014 = 0;
        motId = obj->mtnId[lbl_1_data_B0[motNo].unk00];
        attr = lbl_1_data_B0[motNo].unk08;
        CharMotionShiftSet(work->unk00C, motId, 0.0f, shift, attr);
        CharMotionSpeedSet(work->unk00C, 1.0f);
    }
}

/* 27 insns */
BOOL fn_1_774C(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    if (CharMotionEndCheck(work->unk00C) && CharMotionShiftIDGet(work->unk00C) < 0) {
        return TRUE;
    }
    return FALSE;
}

/* 24 insns */
BOOL fn_1_77B8(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    BOOL ret = FALSE;

    if (CharMotionShiftIDGet(work->unk00C) < 0) {
        ret = TRUE;
    }
    return ret;
}

/* 39 insns. The other player object on the same team (cached). */
OMOBJ *fn_1_7818(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;
    u32 team;
    s32 i;
    OMOBJ *other;
    M580_PLAYER *otherWork;

    if (work->unk0DC != NULL) {
        return work->unk0DC;
    }
    team = work->unk004;
    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_9C[i];
        if (other != obj) {
            otherWork = other->data;
            if (otherWork->unk004 == team) {
                work->unk0DC = other;
                return other;
            }
        }
    }
    return NULL;
}

/* 68 insns. COM mode: -1 no play, 0 loose puck, 1 we hold it, 2 partner holds it, 3 opponent holds it. */
s32 fn_1_78B4(OMOBJ *obj)
{
    OMOBJ *holder;

    if (fn_1_D544()) {
        return -1;
    }
    holder = fn_1_D30C(NULL, NULL);
    if (holder == NULL) {
        return 0;
    }
    if (holder == obj) {
        return 1;
    }
    if (holder->work[0] >= 4) {
        return -1;
    }
    if (holder == fn_1_7818(obj)) {
        return 2;
    }
    return 3;
}

/* 42 insns. Direction from the player to pos, degrees. */
float fn_1_79C4(OMOBJ *obj, HuVecF *pos)
{
    M580_PLAYER *work = obj->data;
    float dx = pos->x - work->unk074.x;
    float dz = pos->z - work->unk074.z;

    return 180.0 * (atan2(dx, dz) / M_PI);
}

/* 94 insns. XZ distance from the player to pos. */
float fn_1_7A6C(OMOBJ *obj, HuVecF *pos)
{
    M580_PLAYER *work = obj->data;
    float dx = pos->x - work->unk074.x;
    float dz = pos->z - work->unk074.z;

    return PlayerSqrtF(dx * dx + dz * dz);
}

/* 146 insns. TRUE if no opponent stands in the way toward pos. */
s32 fn_1_7BE4(OMOBJ *obj, HuVecF *pos, float fov)
{
    M580_PLAYER *work = obj->data;
    OMOBJ *blocker = fn_1_7E48(work->unk004 ^ 1, NULL, &work->unk074, fn_1_79C4(obj, pos), fov, 350.0 + fn_1_7A6C(obj, pos), 1);

    if (blocker != NULL) {
        return 0;
    }
    return 1;
}

/* 7 insns */
s32 fn_1_7E2C(OMOBJ *obj)
{
    M580_PLAYER *work = obj->data;

    return work->unk000;
}

/* 211 insns. Nearest (or farthest) team player within maxDist and within fov of rotY. */
OMOBJ *fn_1_7E48(u32 team, OMOBJ *exclude, HuVecF *pos, float rotY, float fov, float maxDist, s32 nearest)
{
    OMOBJ *nearObj = NULL;
    OMOBJ *farObj = NULL;
    float nearDist = 100000.0f;
    float farDist = 0.0f;
    s32 i;
    OMOBJ *other;
    M580_PLAYER *otherWork;
    float dx;
    float dz;
    float value;

    for (i = 0; i < 4; i++) {
        other = lbl_1_bss_9C[i];
        if (other == exclude) {
            continue;
        }
        otherWork = other->data;
        if (otherWork->unk004 != team) {
            continue;
        }
        dx = otherWork->unk074.x - pos->x;
        dz = otherWork->unk074.z - pos->z;
        if (fov < 180.0) {
            value = 180.0 * (atan2(dx, dz) / M_PI);
            value = fmodf(value - rotY, 360.0f);
            if (value < 0.0f) {
                value += 360.0f;
            }
            if (value > fov && value < 360.0f - fov) {
                continue;
            }
        }
        value = PlayerSqrtF(dx * dx + dz * dz);
        if (value > maxDist) {
            continue;
        }
        if (value < nearDist) {
            nearDist = value;
            nearObj = other;
        }
        if (value > farDist) {
            farDist = value;
            farObj = other;
        }
    }
    if (nearest) {
        return nearObj;
    }
    return farObj;
}

/* 49 insns. Player position / rotY; zeros for a non-player. Reads obj->work[0] before the NULL result is used (retail). */
s32 fn_1_8194(OMOBJ *obj, HuVecF *pos, float *rotY)
{
    M580_PLAYER *work;
    s32 invalid = 0;

    if (obj == NULL) {
        invalid = 1;
    }
    if (obj->work[0] >= 4) {
        invalid = 1;
    }
    if (pos != NULL) {
        if (!invalid) {
            work = obj->data;
            *pos = work->unk074;
        } else {
            pos->x = pos->y = pos->z = 0.0f;
        }
    }
    if (rotY != NULL) {
        if (!invalid) {
            work = obj->data;
            *rotY = work->unk08C;
        } else {
            *rotY = 0.0f;
        }
    }
    return 1;
}

/* 29 insns. TRUE if the team has a human player. */
s32 fn_1_8258(u32 team)
{
    OMOBJ *obj;
    M580_PLAYER *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_9C[i];
        work = obj->data;
        if (work->unk004 == team && work->unk028 == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

/* 35 insns. Rumble the pads of a team. */
void fn_1_82CC(u32 team)
{
    OMOBJ *obj;
    M580_PLAYER *work;
    s32 i;

    for (i = 0; i < 4; i++) {
        obj = lbl_1_bss_9C[i];
        work = obj->data;
        if (work->unk004 == team) {
            omVibrate(work->unk000, 15, 6, 6);
        }
    }
}

/* 40 insns. Create the stage object (stage.c fn_1_83FC) and its M580_STAGE work. */
void fn_1_8358(OMOBJMAN *objman)
{
    OMOBJ *obj;
    M580_STAGE *work;

    obj = omAddObjEx(objman, 30, 10, 1, -1, fn_1_83FC);
    lbl_1_bss_B0 = obj;
    obj->stat |= OM_STAT_MODELPAUSE;
    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_STAGE), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_STAGE));
    obj->work[0] = 0;
}

/* 1 insns */
void fn_1_83F8(void)
{
}
