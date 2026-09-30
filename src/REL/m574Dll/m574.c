/*
 * m574Dll m574.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m574Dll/asm/REL/m574Dll/m574.s.
 */

#include "REL/m574Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s32 lbl_1_rodata_10[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C */ /* s32 lbl_1_rodata_1C[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x28 */ /* float lbl_1_rodata_28 = 45.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 20.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 10000.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 1.2f; */
/* 0x38 */ /* float lbl_1_rodata_38 = 0.0f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 80.0f; */
/* 0x40 */ /* float lbl_1_rodata_40 = 5000.0f; */
/* 0x44 */ /* float lbl_1_rodata_44 = 0.11111111f; */
/* 0x48 */ /* float lbl_1_rodata_48 = 32.0f; */
/* 0x50 */ /* double lbl_1_rodata_50 = 360; */
/* 0x58 */ /* float lbl_1_rodata_58 = 360.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 180.0f; */

/* --- .data --- */
/* 0x0 */ OMCAMERAVIEW lbl_1_data_0[2] = { /* [0] ObjectSetup, [1] fn_1_3B8 intro move */
    { { 0.0f, 1350.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1180.0f },
    { { 0.0f, 800.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 2750.0f },
};
/* 0x38 */ HuVecF lbl_1_data_38 = { 1e+02f, 8e+02f, -1e+02f }; /* global light position */
/* 0x44 */ HuVecF lbl_1_data_44 = { 0.3f, -0.8f, 0.3f };      /* global light direction */
/* 0x50 */ float lbl_1_data_50[3] = { 20.0f, 45.0f, 1000.0f };  /* light rotation x, y and distance */
/* 0x5C */ GXColor lbl_1_data_5C = { 255, 255, 255, 255 };      /* global light colour */
/* 0x60 */ HuVecF lbl_1_data_60 = { 0.0f, 1e+03f, 1.5e+03f };   /* shadow camera position */
/* 0x6C */ HuVecF lbl_1_data_6C = { 0.0f, 0.0f, 1.0f };         /* shadow camera up */
/* 0x78 */ HuVecF lbl_1_data_78 = { 0.0f, 0.0f, 0.0f };         /* shadow camera target */
/* 0x84 */ MGSEQ_PARAM lbl_1_data_84 = { 60, 1, fn_1_348, fn_1_3B8, fn_1_548, fn_1_54C, fn_1_5A8, fn_1_730, fn_1_82C, fn_1_8E4, fn_1_8E8 };
/* 0xAC */ s32 lbl_1_data_AC[1] = { 0 }; /* dtk folds this unreferenced zero word into lbl_1_data_84 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x34 */ OMOBJMAN *lbl_1_bss_34;   /* the overlay's object manager */
/* 0x30 */ OMOBJ *lbl_1_bss_30;      /* omOutView camera object */
/* 0x2C */ s32 lbl_1_bss_2C;         /* fn_1_AAC calls; CharLoseVoicePlay at 4 */
/* 0x28 */ s32 lbl_1_bss_28;         /* fn_1_3B8 intro step */
/* 0x24 */ s32 lbl_1_bss_24;         /* fn_1_3B8 intro timer */
/* 0x20 */ s32 lbl_1_bss_20;         /* fn_1_797C result: record broken */
/* 0x1E */ s16 lbl_1_bss_1E;         /* seconds left (fn_1_54C), read by fn_1_918 */
/* 0x1C */ HU3DLIGHTID lbl_1_bss_1C; /* global light */
/* 0x18 */ s32 lbl_1_bss_18;         /* HuAudBGMPlay stream id, -1 when none */
/* 0x10 */ s16 lbl_1_bss_10[4];      /* per player: winner charNo or -1 (fn_1_5A8) */
/* 0x8 */ s16 lbl_1_bss_8[4];        /* per player: team 0/1 (fn_1_9FC) */
/* 0x0 */ s16 lbl_1_bss_0[4];        /* per player: charNo (fn_1_9FC) */

/* --- functions (reference order) --- */
/* 170 insns */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF unused0 = { 0.0f, 0.0f, 0.0f };
    HuVecF unused1 = { 0.0f, 0.0f, -1.0f };
    HuVecF target;
    HuVecF pos;
    HU3DLIGHT *light;

    lbl_1_bss_2C = 0;
    lbl_1_bss_20 = 0;
    lbl_1_bss_1E = 60;
    lbl_1_bss_18 = -1;
    lbl_1_bss_34 = omInitObjMan(50, 0x2000);
    omGameSysInit(lbl_1_bss_34);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 10000.0f, 1.2f);
    lbl_1_bss_30 = omAddObjEx(lbl_1_bss_34, 32730, 0, 0, -1, omOutView);
    omCameraViewSet(lbl_1_data_0);
    lbl_1_bss_1C = Hu3DGLightCreateV(&lbl_1_data_38, &lbl_1_data_44, &lbl_1_data_5C);
    Hu3DGLightInfinitytSet(lbl_1_bss_1C);
    light = &Hu3DGlobalLight[lbl_1_bss_1C];
    light->type |= 0x8000;
    target.x = target.y = target.z = 0.0f;
    pos.x = pos.z = 0.0f;
    pos.y = lbl_1_data_50[2];
    mtxRot(mtx, lbl_1_data_50[0], lbl_1_data_50[1], 0.0f);
    PSMTXMultVec(mtx, &pos, &pos);
    Hu3DGLightPosAimSetV(lbl_1_bss_1C, &pos, &target);
    Hu3DShadowCreate(80.0f, 20.0f, 5000.0f);
    Hu3DShadowPosSet(&lbl_1_data_60, &lbl_1_data_6C, &lbl_1_data_78);
    Hu3DShadowColSet(50, 50, 50);
    Hu3DShadowSizeSet(240);
    MgSeqCreate(&lbl_1_data_84);
}

/* 28 insns. MGSEQ init hook: every unit's create function. */
void fn_1_348(s16 mode, s16 frameNo)
{
    fn_1_7130(lbl_1_bss_34);
    fn_1_7A48(lbl_1_bss_34);
    fn_1_2028(lbl_1_bss_34);
    fn_1_E98(lbl_1_bss_34);
    fn_1_6650(lbl_1_bss_34);
    MgSeqModeNext();
}

/* 100 insns. MGSEQ intro hook: BGM, camera move, then MgSeqModeNext. */
void fn_1_3B8(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_28 = 0;
        lbl_1_bss_24 = 0;
    }
    if (lbl_1_bss_18 == -1 && frameNo >= 18) {
        lbl_1_bss_18 = HuAudBGMPlay(0x54);
    }
    switch (lbl_1_bss_28) {
        case 0:
            if (++lbl_1_bss_24 < 30) {
                break;
            }
            lbl_1_bss_28++;
            omCameraViewMove(&lbl_1_data_0[1], 90, 1);
        case 1:
            if (!omCameraViewCheck(1)) {
                break;
            }
            lbl_1_bss_28++;
            lbl_1_bss_24 = 0;
        case 2:
            if (++lbl_1_bss_24 < 90) {
                break;
            }
            lbl_1_bss_28++;
            MgSeqModeNext();
            break;
        case 3:
            break;
    }
}

/* 1 insns */
void fn_1_548(s16 mode, s16 frameNo)
{
}

/* 23 insns. MGSEQ main hook: seconds left. */
void fn_1_54C(s16 mode, s16 frameNo)
{
    lbl_1_bss_1E = 60 - frameNo / 60;
    if (lbl_1_bss_1E < 0) {
        lbl_1_bss_1E = 0;
    }
}

/* 98 insns. MGSEQ finish hook: the team with the higher score wins; a tie has no winner. */
void fn_1_5A8(s16 mode, s16 frameNo)
{
    s32 i;
    s32 score0;
    s32 score1;
    u16 winner;

    if (frameNo == 0) {
        if (lbl_1_bss_18 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_18, 100);
            lbl_1_bss_18 = -1;
        }
        lbl_1_bss_1E = 0;
        score0 = fn_1_7948(0);
        score1 = fn_1_7948(1);
        for (i = 0; i < 4; i++) {
            lbl_1_bss_10[i] = -1;
            if ((score0 > score1 && lbl_1_bss_8[i] == 0) || (score0 < score1 && lbl_1_bss_8[i] == 1)) {
                lbl_1_bss_10[i] = lbl_1_bss_0[i];
            }
        }
        winner = MgSeqWinnerSet(lbl_1_bss_10[0], lbl_1_bss_10[1], lbl_1_bss_10[2], lbl_1_bss_10[3]);
        lbl_1_bss_20 = fn_1_797C();
    }
}

/* 63 insns. MGSEQ pre-winner hook: waits for the balls to settle, record jingle. */
void fn_1_730(s16 mode, s16 frameNo)
{
    s32 i;

    if (frameNo == 0) {
        for (i = 0; fn_1_6CC8(0) || fn_1_6CC8(1);) {
            if (omSysExitReq) {
                break;
            }
            if (++i > 300) {
                break;
            }
            HuPrcVSleep();
        }
    }
    if (frameNo == 90 && lbl_1_bss_20 != 0 && !_CheckFlag(FLAG_MG_PRACTICE)) {
        HuAudJinglePlay(0x86);
    }
    if ((lbl_1_bss_20 == 0 || _CheckFlag(FLAG_MG_PRACTICE)) && frameNo >= 90) {
        MgSeqModeNext();
    }
}

/* 46 insns. MGSEQ winner hook: 10 bonus coins to each winner (not in practice). */
void fn_1_82C(s16 mode, s16 frameNo)
{
    s32 i;

    if (frameNo == 0) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_10[i] >= 0) {
                GWMgCoinBonusSet(i, GWMgCoinBonusGet(i) + 10);
            }
        }
    }
}

/* 1 insns */
void fn_1_8E4(s16 mode, s16 frameNo)
{
}

/* 12 insns. MGSEQ close hook: every unit's close function. */
void fn_1_8E8(s16 mode, s16 frameNo)
{
    fn_1_20C8();
    fn_1_66F0();
    fn_1_1044();
    fn_1_7AD0();
    fn_1_71B8();
}

/* 4 insns */
s32 fn_1_918(void)
{
    return lbl_1_bss_1E;
}

/* 6 insns */
s32 fn_1_928(s32 no)
{
    return lbl_1_bss_10[no];
}

/* 47 insns. 1 if the team won, -1 if it lost, 0 on a tie. */
s32 fn_1_940(u32 team)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_10[i] >= 0) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (team == lbl_1_bss_8[i]) {
            return (lbl_1_bss_10[i] >= 0) ? 1 : -1;
        }
    }
    /* Retail has no return here: r3 still holds `team` (this spelling emits no
     * code). Unreachable while every team has a member. */
    return team;
}

/* 14 insns */
void fn_1_9FC(s32 no, s32 team, s32 charNo)
{
    no &= 3;
    lbl_1_bss_8[no] = (s16)team;
    lbl_1_bss_0[no] = (s16)charNo;
}

/* 30 insns. Unreferenced: the charNo of the idx-th member of a team, or -1. */
s32 fn_1_A34(u32 team, u32 idx)
{
    s32 n = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (team == lbl_1_bss_8[i]) {
            if (idx == n) {
                return lbl_1_bss_0[i];
            }
            n++;
        }
    }
    return -1;
}

/* 29 insns */
void fn_1_AAC(s32 no)
{
    if (++lbl_1_bss_2C == 4) {
        CharLoseVoicePlay(lbl_1_bss_0[0], lbl_1_bss_0[1], lbl_1_bss_0[2], lbl_1_bss_0[3]);
    }
}

/* 23 insns. Unreferenced: pan (32..96) for a screen x. */
s32 fn_1_B20(float x)
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

/* 37 insns. Unreferenced: pan for a 3D position. */
s32 fn_1_B7C(HuVecF *pos)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_B20(out.x);
}

/* 46 insns. Positional HuAudFXPlayPan. */
s32 fn_1_C10(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayPan(seNo, fn_1_B7C(pos));
}

/* 71 insns */
float fn_1_CC8(float cur, float target, float rate)
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
float fn_1_DE4(float from, float to)
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
