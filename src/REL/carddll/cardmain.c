/*
 * carddll cardmain.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/cardmain.s.
 */

#include "REL/carddll.h"

/* retail calls the audio API unprototyped here (fn_1_CA4: HuAudSStreamVolSet's result copied with mr;
 * fn_1_8D04: no extsh on HuAudFXPanning's pan): keep game/audio.h out of the CW build. */
#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#endif
#include "game/esprite.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
/* 0x10 lbl_1_rodata_10 (0xC): 0x00000000 0x453B8000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x1C lbl_1_rodata_1C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x28 lbl_1_rodata_28 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x34 lbl_1_rodata_34 (0xC): 0x00000000 0x45FA0000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x40 lbl_1_rodata_40 (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4C lbl_1_rodata_4C (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x4D lbl_1_rodata_4D (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_50 = 60.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 20.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 10000.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 0.4f; /* 0x5C */
static const float lbl_1_rodata_60 = -50.0f; /* 0x60 */
static const float lbl_1_rodata_64 = -10.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 0.0f; /* 0x68 */
/* 0x6C lbl_1_rodata_6C (0xC): 0x40A00000 0x40A00000 0x40A00000 -- an aggregate initialiser, write it as a local */
/* 0x78 lbl_1_rodata_78 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x84 lbl_1_rodata_84 (0xC): 0x43900000 0x43700000 0x44BB8000 -- an aggregate initialiser, write it as a local */
/* 0x90 lbl_1_rodata_90 (0xC): 0x43900000 0x43700000 0x44BB8000 -- an aggregate initialiser, write it as a local */
/* 0x9C lbl_1_rodata_9C (0xC): 0x3F800000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xA8 lbl_1_rodata_A8 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B4 = 1.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 150.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 100.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 300.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 180.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 90.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = -90.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 0.5f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 15.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 10.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 2.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = 0.1f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 80.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = -1.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 400.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 240.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 6.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 201.5625f; /* 0xF8 */
static const float lbl_1_rodata_FC = 98.4375f; /* 0xFC */
static const float lbl_1_rodata_100 = 103.125f; /* 0x100 */
/* 0x104 lbl_1_rodata_104 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x110 lbl_1_rodata_110 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_11C = -55.0f; /* 0x11C */
static const float lbl_1_rodata_120 = 55.0f; /* 0x120 */
static const float lbl_1_rodata_124 = -105.0f; /* 0x124 */
static const float lbl_1_rodata_128 = 5.0f; /* 0x128 */
static const float lbl_1_rodata_12C = 0.7f; /* 0x12C */
/* 0x130 lbl_1_rodata_130 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_134 = 640.0f; /* 0x134 */
static const float lbl_1_rodata_138 = 480.0f; /* 0x138 */
static const float lbl_1_rodata_13C = -16777215.0f; /* 0x13C */
static const double lbl_1_rodata_140 = 180.0; /* 0x140 */
static const double lbl_1_rodata_148 = 3.141592653589793; /* 0x148 */
static const float lbl_1_rodata_150 = 0.017453292f; /* 0x150 */
static const float lbl_1_rodata_154 = -30.0f; /* 0x154 */
static const float lbl_1_rodata_158 = -180.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 576.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 9.0f; /* 0x160 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x31C */ OMOBJMAN *lbl_1_bss_31C;
/* 0x318 */ OMOBJ *lbl_1_bss_318;
/* 0x314 */ s32 lbl_1_bss_314;
/* 0x308 */ s16 lbl_1_bss_308[6];
/* 0x2F8 */ s16 lbl_1_bss_2F8[4][2];
/* 0x2C8 */ HuVecF lbl_1_bss_2C8[4];
/* 0x2C4 */ s32 lbl_1_bss_2C4;
/* 0x2BC */ float lbl_1_bss_2BC[2];
/* 0xE4 */ CardGameWork lbl_1_bss_E4;
/* 0xD8 */ HuVecF lbl_1_bss_D8;
/* 0xCC */ HuVecF lbl_1_bss_CC;
/* 0xC8 */ float lbl_1_bss_C8;
/* 0xC4 */ float lbl_1_bss_C4;
/* 0xC0 */ float lbl_1_bss_C0;
/* 0xBC */ float lbl_1_bss_BC;
/* 0xB8 */ s32 lbl_1_bss_B8;
/* 0xB4 */ s32 lbl_1_bss_B4;
/* 0xB0 */ s32 lbl_1_bss_B0;
/* 0xAC */ s32 lbl_1_bss_AC;
/* 0xA8 */ s16 lbl_1_bss_A8[2];
/* 0xA0 */ float lbl_1_bss_A0[2];
/* 0x98 */ s32 lbl_1_bss_98[2];
/* 0x94 */ s32 lbl_1_bss_94;
/* 0x88 */ HuVecF lbl_1_bss_88;
/* 0x84 */ s32 lbl_1_bss_84;
/* 0x80 */ float lbl_1_bss_80;
/* 0x74 */ s32 lbl_1_bss_74[3];
/* 0x72 */ s16 lbl_1_bss_72;
/* 0x70 */ s16 lbl_1_bss_70;
/* 0x6C */ s32 lbl_1_bss_6C;
/* 0x68 */ s32 lbl_1_bss_68;
/* 0x64 */ float lbl_1_bss_64;
/* 0x60 */ s32 lbl_1_bss_60;
/* 0x5F gap_05_0000005F_bss (0x1): alignment gap */
/* 0x5E */ u8 lbl_1_bss_5E;
/* 0x5C */ s16 lbl_1_bss_5C;
/* 0x4C */ s32 lbl_1_bss_4C[4];
/* 0x4A */ s16 lbl_1_bss_4A;
/* 0x48 */ s16 lbl_1_bss_48;
/* 0x20 */ s32 lbl_1_bss_20[10];
/* 0x1C */ s32 lbl_1_bss_1C;
/* 0x18 */ s32 lbl_1_bss_18;
/* 0x14 */ s32 lbl_1_bss_14;
/* 0x8 */ s32 lbl_1_bss_8[3];
/* 0x0 */ s16 lbl_1_bss_0[4];

/* --- functions (reference order), .data placed before its first user --- */
/* 146 insns */
void ObjectSetup(void)
{
    HuVecF shadowPos = { 0.0f, 3000.0f, 500.0f };
    HuVecF shadowUp = { 0.0f, 1.0f, 0.0f };
    HuVecF shadowTarget = { 0.0f, 0.0f, 0.0f };
    HuVecF lightPos = { 0.0f, 8000.0f, 500.0f };
    HuVecF lightDir = { 0.0f, -1.0f, 0.0f };
    GXColor lightColor = { 0xFF, 0xFF, 0xFF, 0xFF };

    lbl_1_bss_31C = omInitObjMan(200, 0x2000);
    omGameSysInit(lbl_1_bss_31C);
    fn_1_30E08();
    lbl_1_bss_314 = Hu3DGLightCreateV(&lightPos, &lightDir, &lightColor);
    Hu3DGLightStaticSet(lbl_1_bss_314, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_314);
    Hu3DShadowCreate(60.0f, 20.0f, 10000.0f);
    Hu3DShadowColSet(0, 0, 0);
    Hu3DShadowTPLvlSet(0.4f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
    fn_1_8C78();
    lbl_1_bss_318 = omAddObjEx(lbl_1_bss_31C, 0, 122, 0, -1, fn_1_2E8);
    lbl_1_bss_318->work[0] = 100;
    lbl_1_bss_5E = 0x80;
    fn_1_850C();
    Hu3DModelAttrSet(lbl_1_bss_5C, HU3D_ATTR_DISPOFF);
    HuWinInit(1);
    fn_1_501B4(0);
    lbl_1_bss_60 = 0;
}

/* 265 insns */
void fn_1_2E8(OMOBJ *obj)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_E4.player[i].unk2C = GwPlayerConf[i].charNo;
        lbl_1_bss_E4.player[i].unk54 = -1;
        lbl_1_bss_E4.player[i].unk56 = -1;
        lbl_1_bss_E4.player[i].unk58 = -1;
        lbl_1_bss_0[i] = -1;
    }
    lbl_1_bss_E4.unk194 = GwCardCommon.boardSize + 7;
    lbl_1_bss_E4.player[0].unk28 = *(u8 *)&GwCardCommon.pedestalF[0];
    lbl_1_bss_E4.player[1].unk28 = *(u8 *)&GwCardCommon.pedestalF[1];
    lbl_1_bss_E4.player[2].unk28 = *(u8 *)&GwCardCommon.pedestalF[2];
    lbl_1_bss_E4.player[3].unk28 = *(u8 *)&GwCardCommon.pedestalF[3];
    fn_1_8EC8(&lbl_1_bss_E4);
    fn_1_392B8();
    fn_1_7304();
    for (i = 0; i < 6; i++) {
        lbl_1_bss_308[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(lbl_1_bss_308[i], 1);
        Hu3DModelPosSet(lbl_1_bss_308[i], -50.0f, -10.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_308[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_308[i], 1);
    }
    Hu3DModelShadowMapSet(lbl_1_bss_308[0]);
    lbl_1_bss_C8 = 0.0f;
    lbl_1_bss_C4 = 0.0f;
    lbl_1_bss_C0 = 0.0f;
    lbl_1_bss_BC = 0.0f;
    lbl_1_bss_B8 = 0;
    lbl_1_bss_B4 = 0;
    lbl_1_bss_AC = 0;
    lbl_1_bss_A8[0] = lbl_1_bss_A8[1] = -1;
    lbl_1_bss_A0[0] = lbl_1_bss_A0[1] = 0.0f;
    lbl_1_bss_98[0] = lbl_1_bss_98[1] = -1;
    lbl_1_bss_94 = 0;
    lbl_1_bss_6C = -1;
    lbl_1_bss_E4.unk170 = 0;
    lbl_1_bss_E4.unk188 = 200;
    lbl_1_bss_E4.unk18C = 300;
    lbl_1_bss_E4.unk190 = 0;
    lbl_1_bss_E4.unk19C = 2;
    lbl_1_bss_E4.unk1D4 = 0;
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
    obj->objFunc = fn_1_70C;
    fn_1_FA24();
    fn_1_2FEF4(&lbl_1_bss_E4);
    fn_1_30B00(&lbl_1_bss_E4, 0);
    fn_1_3EAA0();
}

/* 138 insns */
void fn_1_70C(OMOBJ *obj)
{
    s32 i;

    if (omSysExitReq) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        obj->objFunc = fn_1_934;
    }
    switch (obj->work[0]) {
        case 100:
            if (lbl_1_bss_14 == -1) {
                lbl_1_bss_14 = HuAudBGMPlay(39);
            }
            if (!WipeCheckEnd()) {
                obj->work[0]++;
            }
            break;
        case 101:
            if (fn_1_FB88(&lbl_1_bss_E4)) {
                obj->work[0]++;
            }
            break;
        case 102:
            if (lbl_1_bss_68 = fn_1_AB4(&lbl_1_bss_E4)) {
                if (lbl_1_bss_68 == -1) {
                    obj->work[0] = 104;
                } else {
                    obj->work[0]++;
                }
            }
            break;
        case 103:
            if (fn_1_12E04()) {
                obj->work[0]++;
                for (i = 0; i < 4; i++) {
                    *(u8 *)&GwCardCommon.starNum[i] = (lbl_1_bss_E4.player[i].unk44 + lbl_1_bss_E4.player[i].unk48 * 2);
                    *(u8 *)&GwCardCommon.ztarNum[i] = lbl_1_bss_E4.player[i].unk4C;
                }
                lbl_1_bss_60 = 1;
            }
            break;
        case 104:
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
            obj->objFunc = fn_1_934;
            break;
    }
    fn_1_3F73C();
}

/* 96 insns */
void fn_1_934(OMOBJ *obj)
{
    s32 i;

    if (lbl_1_bss_20[0] == 0 && lbl_1_bss_60) {
        HuAudFXFadeOut(lbl_1_bss_20[9], 1000);
    }
    lbl_1_bss_20[0]++;
    if (WipeCheckEnd()) {
        return;
    }
    if (lbl_1_bss_20[0] > 100) {
        HuAudAllStop();
    } else {
        return;
    }
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_0[i] != -1) {
            Hu3DLLightKill(lbl_1_bss_468[i], lbl_1_bss_0[i]);
        }
    }
    fn_1_34CC8(&lbl_1_bss_E4);
    fn_1_3678C(&lbl_1_bss_E4);
    Hu3DModelKill(lbl_1_bss_5C);
    fn_1_F24C();
    Hu3DModelAllKill();
    fn_1_30910();
    Hu3DLightAllKill();
    HuDataDirClose(DATA_card);
    if (lbl_1_bss_60) {
        omOvlGotoEx(DLL_rescarddll, 1, 0, 0);
    } else {
        omOvlReturnEx(1, 1);
    }
}
#ifdef __MWERKS__
#endif

/* 124 insns */
s32 fn_1_AB4(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 result = 0;

    switch (work->unk188) {
        case 200:
            fn_1_CA4(work);
            break;
        case 201:
            if (fn_1_2930C(work)) {
                if (work->unk1D0 == 0) {
                    result = 1;
                } else {
                    work->unk188 = 200;
                }
            }
            break;
        case 202:
            if (lbl_1_bss_68 = fn_1_187FC(work, lbl_1_bss_6C)) {
                if (lbl_1_bss_68 != -1) {
                    work->unk188 = 200;
                    lbl_1_bss_6C = -1;
                    espDrawNoSet(lbl_1_bss_F9E[0], 0);
                    espDrawNoSet(lbl_1_bss_F9E[1], 0);
                } else {
                    result = -1;
                }
            }
            break;
        case 203:
            if (fn_1_1B2F0(work)) {
                work->unk188 = 200;
                work->unk18C = 300;
                work->unk19C = 2;
            }
            break;
        case 204:
            if (fn_1_198F4(work)) {
                work->unk188 = 200;
            }
            break;
        case 205:
            if (fn_1_1AB2C(work)) {
                work->unk188 = 200;
            }
            break;
        case 206:
            if (fn_1_32D70(work)) {
                player = &work->player[work->unk174[work->unk170]];
                if (!(player->unk50 & 0x1000)) {
                    fn_1_4FBC8(work, 59);
                }
                work->unk188 = 200;
            }
            break;
    }
    fn_1_8894();
    fn_1_8B84(work);
    fn_1_358F8(work);
    return result;
}

/* 3410 insns */
s32 fn_1_CA4(CardGameWork *work)
{
    HuVecF pos;
    HuVecF dir;
    CardPlayerWork *player;
    s32 i;
    s32 j;
    s32 k;
    s32 num;
    s16 mdl;
    s32 ret;
    s32 result;
    s16 statusMdl;
    s16 mdl2;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    fn_1_5A00(work);
    switch (work->unk18C) {
        case 0x12C:
            if (fn_1_30FA4(work->unk19C, work) != 0) {
                if (work->unk19C == 2) {
                    lbl_1_bss_B0 = fn_1_5710(work, work->unk170, 0);
                    if (lbl_1_bss_B0 != 0 && player->unk0 == 0) {
                        fn_1_9DA8(&lbl_1_bss_88, work);
                        lbl_1_bss_84 = lbl_1_bss_B0;
                        lbl_1_bss_80 = 1.0f;
                        lbl_1_bss_74[0] = work->unk1B0[0];
                        if (lbl_1_bss_B0 >= 2) {
                            lbl_1_bss_74[1] = work->unk1B0[1];
                            if (lbl_1_bss_B0 >= 3) {
                                lbl_1_bss_74[2] = work->unk1B0[2];
                            }
                        }
                        player->unk50 |= 0x100;
                    }
                    if (player->unk50 & 0x80) {
                        work->unk18C = 0x138;
                        fn_1_9DA8(&pos, work);
                        pos.x += -50.0f;
                        pos.y += 150.0f;
                        {
                            HuVecF scale = { 5.0f, 5.0f, 5.0f };
                            PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &dir);
                            PSVECNormalize(&dir, &dir);
                            PSVECScale(&dir, &dir, 100.0f);
                            PSVECAdd(&dir, &pos, &pos);
                            statusMdl = fn_1_3ED3C(1, pos);
                            fn_1_3F6B0(1, statusMdl, scale);
                        }
                        work->unk1A4 = 0;
                    } else {
                        work->unk18C = 0x12D;
                    }
                } else if (work->unk19C == 3) {
                    work->unk18C = 0x12F;
                }
            }
            break;
        case 0x12D:
            if (lbl_1_bss_B4 == 0) {
                if (fn_1_182E0(work) != 0) {
                    lbl_1_bss_B4 = 1;
                    work->unk18C = 0x134;
                    lbl_1_bss_B8 = 0;
                }
            } else {
                work->unk18C = 0x134;
            }
            break;
        case 0x12E:
            if (fn_1_393C4(work) != 0) {
                lbl_1_bss_2C4 = 0;
                lbl_1_bss_2BC[0] = 0.0f;
                work->unk18C = 0x12C;
                work->unk19C = 3;
                work->unk1A0 = 1;
                player->unk50 &= ~0x400;
                fn_1_30B00(work, 1);
                lbl_1_bss_B8 = 0;
                lbl_1_bss_48 = 0;
            }
            break;
        case 0x12F:
            fn_1_9DA8(&lbl_1_bss_D8, work);
            if (player->unk0 != 0) {
                lbl_1_bss_BC = 300.0f;
                work->unk184--;
                work->unk18C = 0x131;
                player->unk0 = 0;
            } else {
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    fn_1_502E0(0x11);
                }
                if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_Y) {
                    fn_1_50460();
                    work->unk188 = 0xCD;
                    fn_1_7E28();
                    fn_1_30B00(work, -1);
                    player->unk50 |= 0x40;
                    HuAudFXPlay(0x3FB);
                    HuAudSStreamVolSet(0, 0x60, 0x1F4);
                    break;
                }
                if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_TRIGGER_R) {
                    fn_1_50460();
                    work->unk188 = 0xCC;
                    fn_1_7E28();
                    fn_1_30B00(work, -1);
                    player->unk50 |= 0x40;
                    HuAudFXPlay(0x3FB);
                    HuAudSStreamVolSet(0, 0x60, 0x1F4);
                    break;
                }
                if (player->unk50 & 0x40) {
                    fn_1_30B00(work, 1);
                    player->unk50 &= ~0x40;
                }
                fn_1_7E98(player);
                fn_1_77D0(&lbl_1_bss_D8, work);
                if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 1)
                    && (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_UP)) {
                    if (work->unk1A0 != 0 || (work->unk1A0 == 0 && 0.0f != player->unk1C)) {
                        if (180.0f != player->unk18) {
                            HuAudFXPlay(0);
                        }
                        player->unk18 = 180.0f;
                    }
                } else if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 2)
                    && (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_DOWN)) {
                    if (work->unk1A0 != 0 || (work->unk1A0 == 0 && 180.0f != player->unk1C)) {
                        if (0.0f != player->unk18) {
                            HuAudFXPlay(0);
                        }
                        player->unk18 = 0.0f;
                    }
                } else if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 4)
                    && (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_LEFT)) {
                    if (work->unk1A0 != 0 || (work->unk1A0 == 0 && 90.0f != player->unk1C)) {
                        if (-90.0f != player->unk18) {
                            HuAudFXPlay(0);
                        }
                        player->unk18 = -90.0f;
                    }
                } else if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 8)
                    && (HuPadDStkRep[work->unk174[work->unk170]] & PAD_BUTTON_RIGHT)) {
                    if (work->unk1A0 != 0 || (work->unk1A0 == 0 && -90.0f != player->unk1C)) {
                        if (90.0f != player->unk18) {
                            HuAudFXPlay(0);
                        }
                        player->unk18 = 90.0f;
                    }
                }
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, player->unk18, 0.0f);
                if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                    fn_1_50460();
                    work->unk184--;
                    fn_1_41EC(work);
                    player->unk1C = player->unk18;
                    work->unk1A0 = 0;
                    fn_1_7E28();
                }
            }
            lbl_1_bss_CC.x = lbl_1_bss_D8.x;
            lbl_1_bss_CC.z = lbl_1_bss_D8.z;
            break;
        case 0x130:
            fn_1_9DA8(&lbl_1_bss_D8, work);
            if (180.0f == player->unk18) {
                if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 3) {
                    player->unk18 = 180.0f;
                    player->unk1C = 180.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 6) {
                    player->unk18 = -90.0f;
                    player->unk1C = -90.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 10) {
                    player->unk18 = 90.0f;
                    player->unk1C = 90.0f;
                } else {
                    work->unk18C = 0x12F;
                }
            } else if (0.0f == player->unk18) {
                if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 3) {
                    player->unk18 = 0.0f;
                    player->unk1C = 0.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 5) {
                    player->unk18 = -90.0f;
                    player->unk1C = -90.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 9) {
                    player->unk18 = 90.0f;
                    player->unk1C = 90.0f;
                } else {
                    work->unk18C = 0x12F;
                }
            } else if (-90.0f == player->unk18) {
                if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 12) {
                    player->unk18 = -90.0f;
                    player->unk1C = -90.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 9) {
                    player->unk18 = 180.0f;
                    player->unk1C = 180.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 10) {
                    player->unk18 = 0.0f;
                    player->unk1C = 0.0f;
                } else {
                    work->unk18C = 0x12F;
                }
            } else if (90.0f == player->unk18) {
                if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 12) {
                    player->unk18 = 90.0f;
                    player->unk1C = 90.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 5) {
                    player->unk18 = 180.0f;
                    player->unk1C = 180.0f;
                } else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 6) {
                    player->unk18 = 0.0f;
                    player->unk1C = 0.0f;
                } else {
                    work->unk18C = 0x12F;
                }
            }
            if (work->unk18C != 0x12F) {
                work->unk184--;
                fn_1_41EC(work);
            }
            lbl_1_bss_CC.x = lbl_1_bss_D8.x;
            lbl_1_bss_CC.z = lbl_1_bss_D8.z;
            break;
        case 0x131:
            if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x10) {
                work->unk18C = 0x132;
            } else {
                work->unk188 = 0xC9;
            }
            break;
        case 0x132:
            if (lbl_1_bss_4A == 0) {
                lbl_1_bss_20[0] = (lbl_1_bss_48 == 0) ? 0x3EF : 0x3F0;
                fn_1_8D04(lbl_1_bss_20[0], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[0] = 0;
                lbl_1_bss_48 ^= 1;
                lbl_1_bss_4A = 1;
            }
            fn_1_30B00(work, 1);
            pos = lbl_1_bss_CC;
            pos.x += 100.0f;
            fn_1_31788(&pos);
            if (lbl_1_bss_C8 <= lbl_1_bss_BC) {
                pos.x = lbl_1_bss_D8.x;
                pos.y = lbl_1_bss_D8.y;
                pos.z = lbl_1_bss_D8.z;
                if (180.0f == player->unk18) {
                    pos.z -= lbl_1_bss_C8;
                    Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_C0, player->unk18, 0.0f);
                } else if (0.0f == player->unk18) {
                    pos.z += lbl_1_bss_C8;
                    Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_C0, player->unk18, 0.0f);
                } else if (-90.0f == player->unk18) {
                    pos.x -= lbl_1_bss_C8;
                    Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, player->unk18, lbl_1_bss_C0);
                } else if (90.0f == player->unk18) {
                    pos.x += lbl_1_bss_C8;
                    Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, player->unk18, lbl_1_bss_C0);
                }
                fn_1_5248(work);
                num = fn_1_5710(work, work->unk170, 0);
                lbl_1_bss_B0 = num;
                if (num == 0) {
                    if (lbl_1_bss_C8 < lbl_1_bss_BC / 2.0f) {
                        lbl_1_bss_C4 += (lbl_1_bss_94 != 0) ? 15.0f : 10.0f;
                        if (90.0f == player->unk18) {
                            lbl_1_bss_C0 += 2.0f;
                        } else {
                            lbl_1_bss_C0 -= 2.0f;
                        }
                    } else if (lbl_1_bss_C8 > lbl_1_bss_BC / 2.0f) {
                        lbl_1_bss_C4 -= (lbl_1_bss_94 != 0) ? 15.0f : 10.0f;
                        if (90.0f == player->unk18) {
                            lbl_1_bss_C0 -= 2.0f;
                        } else {
                            lbl_1_bss_C0 += 2.0f;
                        }
                    }
                    pos.y += lbl_1_bss_C4;
                } else {
                    if (lbl_1_bss_C8 < lbl_1_bss_BC / 2.0f) {
                        lbl_1_bss_C4 += 15.0f;
                        if (90.0f == player->unk18) {
                            lbl_1_bss_C0 += 2.0f;
                        } else {
                            lbl_1_bss_C0 -= 2.0f;
                        }
                    } else if (lbl_1_bss_C8 > lbl_1_bss_BC / 2.0f) {
                        lbl_1_bss_C4 -= 15.0f;
                        if (90.0f == player->unk18) {
                            lbl_1_bss_C0 -= 2.0f;
                        } else {
                            lbl_1_bss_C0 += 2.0f;
                        }
                        if (0.0f == lbl_1_bss_A0[1]) {
                            fn_1_8D04(0x3F4, lbl_1_bss_468[work->unk174[work->unk170]], 1);
                        }
                        for (k = 0; k < lbl_1_bss_B0; k++) {
                            if (0.0f != Hu3DData[lbl_1_bss_468[work->unk1B0[k]]].scale.y) {
                                mdl = lbl_1_bss_468[work->unk1B0[k]];
                                lbl_1_bss_98[1] = work->unk1B0[k];
                                break;
                            }
                        }
                        lbl_1_bss_A0[1] += 0.1f;
                        if (lbl_1_bss_A0[1] > 1.0f) {
                            lbl_1_bss_A0[1] = 1.0f;
                        }
                        Hu3DModelScaleSet(mdl, 1.0f, 1.0f - lbl_1_bss_A0[1], 1.0f);
                        lbl_1_bss_A8[1] = mdl;
                        if (work->player[lbl_1_bss_98[1]].unk50 & 4) {
                            HuVecF scale = { 1.0f, 1.0f, 1.0f };
                            scale.y -= lbl_1_bss_A0[1];
                            fn_1_3F6B0(4, work->player[lbl_1_bss_98[1]].unk56, scale);
                        }
                        if (work->player[lbl_1_bss_98[1]].unk58 != -1) {
                            Hu3DModelScaleSet(work->player[lbl_1_bss_98[1]].unk58, 1.0f, 1.0f - lbl_1_bss_A0[1], 1.0f);
                        }
                        work->player[lbl_1_bss_98[1]].unk50 |= 0x200;
                    }
                    pos.y += lbl_1_bss_C4;
                }
                Hu3DModelPosSet(lbl_1_bss_468[work->unk174[work->unk170]], -50.0f + pos.x, pos.y, pos.z);
                lbl_1_bss_C8 += lbl_1_bss_BC / 20.0f;
                if (lbl_1_bss_0[work->unk174[work->unk170]] != -1) {
                    Hu3DLLightPosSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_0[work->unk174[work->unk170]],
                        -50.0f + pos.x, 80.0f + pos.y, 100.0f + pos.z, 0.0f, 0.0f, -1.0f);
                }
                lbl_1_bss_CC.x = pos.x;
                lbl_1_bss_CC.z = pos.z;
                if (player->unk50 & 2) {
                    pos.x += -50.0f;
                    fn_1_3F3D8(3, player->unk56, pos);
                } else if (player->unk50 & 4) {
                    pos.x += -50.0f;
                    fn_1_3F3D8(4, player->unk56, pos);
                }
            } else {
                lbl_1_bss_20[0] = (player->unk28 == 0) ? 0x3F1 : ((player->unk28 == 1) ? 0x3F1 : 0x3F1);
                fn_1_8D04(lbl_1_bss_20[0], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[0] = 0;
                lbl_1_bss_4A = 0;
                if (work->unk184 == 0) {
                    if (lbl_1_bss_A8[1] != -1) {
                        work->unk18C = 0x137;
                        work->unk1A4 = 0;
                    } else {
                        work->unk18C = 0x133;
                    }
                } else {
                    work->unk18C = 0x130;
                    if (lbl_1_bss_A8[1] != -1) {
                        lbl_1_bss_A8[0] = lbl_1_bss_A8[1];
                        lbl_1_bss_A8[1] = -1;
                        lbl_1_bss_A0[0] = lbl_1_bss_A0[1];
                        lbl_1_bss_A0[1] = 0.0f;
                        lbl_1_bss_98[0] = lbl_1_bss_98[1];
                        lbl_1_bss_98[1] = -1;
                        lbl_1_bss_AC = 1;
                    }
                    lbl_1_bss_94 = 0;
                }
                lbl_1_bss_C8 = 0.0f;
                lbl_1_bss_C4 = 0.0f;
                lbl_1_bss_C0 = 0.0f;
                Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_C0, player->unk18, 0.0f);
            }
            if (work->unk18C == 0x132 && GwPlayerConf[work->unk174[work->unk170]].type != 0) {
                for (i = 0; i < 4; i++) {
                    if (GwPlayerConf[i].type == 0 && (HuPadBtnDown[i] & PAD_BUTTON_START)) {
                        lbl_1_bss_6C = i;
                        work->unk188 = 0xCA;
                        espDrawNoSet(lbl_1_bss_F9E[0], 0x40);
                        espDrawNoSet(lbl_1_bss_F9E[1], 0x40);
                        HuAudFXPlay(0x3FA);
                        HuAudSStreamVolSet(0, 0x60, 0x1F4);
                        break;
                    }
                }
            }
            break;
        case 0x133:
            if (!(player->unk50 & 0x1000)) {
                work->unk18C = 0x12C;
                work->unk19C = 2;
                work->unk170++;
                if (work->unk170 == 4) {
                    work->unk170 = 0;
                }
            } else {
                work->unk18C = 0x136;
            }
            if (player->unk50 & 2) {
                fn_1_3F278(3, player->unk56);
                player->unk56 = -1;
            } else if ((player->unk50 & 4) && work->unk1D4 != 20) {
                fn_1_3F278(4, player->unk56);
                player->unk56 = -1;
            }
            player->unk50 &= 0xFFC0;
            if (work->unk1D4 == 20) {
                player->unk50 |= 4;
                work->unk1D4 = -1;
            }
            lbl_1_bss_B4 = 0;
            fn_1_30B00(work, -1);
            break;
        case 0x134:
            if (!(player->unk50 & 0x8000) && work->unk1D0 == 1 && player->unk30 == 4) {
                fn_1_36828();
                pos = (HuVecF){ 288.0f, 240.0f, 1500.0f };
                lbl_1_bss_64 = 400.0f;
                pos.y -= lbl_1_bss_64;
                fn_1_36A70(&pos);
                work->unk18C = 0x135;
            } else {
                if (lbl_1_bss_B4 == 1) {
                    if (player->unk50 & 4) {
                        fn_1_4FBC8(work, 0x25);
                    }
                    lbl_1_bss_B4 = -1;
                }
                work->unk18C = 0x12E;
            }
            break;
        case 0x135:
            lbl_1_bss_64 -= 10.0f;
            if (lbl_1_bss_64 < 0.0f) {
                lbl_1_bss_64 = 0.0f;
            }
            pos = (HuVecF){ 288.0f, 240.0f, 1500.0f };
            pos.y -= lbl_1_bss_64;
            fn_1_36A70(&pos);
            if (240.0f == lbl_1_bss_64) {
                HuAudFXPlay(0x42A);
            }
            if (lbl_1_bss_64 <= 6.0f) {
                fn_1_36B10(1);
            }
            if (0.0f == lbl_1_bss_64) {
                fn_1_4FBC8(work, 0x34);
                work->unk188 = 0xCE;
                work->unk18C = 0x134;
            }
            break;
        case 0x136:
            result = fn_1_345B4(work);
            if (result != 0) {
                work->unk18C = 0x12C;
                work->unk19C = 2;
                if (result == 1) {
                    fn_1_4FBC8(work, 0x3B);
                    work->unk170++;
                    if (work->unk170 == 4) {
                        work->unk170 = 0;
                    }
                }
            }
            break;
        case 0x137:
            fn_1_9DA8(&pos, work);
            if (work->unk1A4 == 0) {
                if (lbl_1_bss_B0 == 1) {
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[105], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    Hu3DModelScaleSet(lbl_1_bss_72, 1.0f, 0.0f, 1.0f);
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                    lbl_1_bss_A0[0] = 0.0f;
                    work->unk1A4 = 1;
                } else if (lbl_1_bss_B0 == 2) {
                    lbl_1_bss_72 = work->player[work->unk1B0[0]].unk54;
                    lbl_1_bss_70 = work->unk1B0[0];
                    if (lbl_1_bss_72 == -1) {
                        lbl_1_bss_72 = work->player[work->unk1B0[1]].unk54;
                        lbl_1_bss_70 = work->unk1B0[1];
                    }
                    if (lbl_1_bss_72 != -1) {
                        Hu3DModelShadowReset(lbl_1_bss_72);
                        Hu3DAnimModelKill(lbl_1_bss_72);
                        Hu3DModelKill(lbl_1_bss_72);
                        work->player[lbl_1_bss_70].unk54 = -1;
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_72 == work->player[i].unk54) {
                                work->player[i].unk54 = -1;
                            }
                        }
                    }
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[106], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    work->player[work->unk1B0[1]].unk54 = lbl_1_bss_72;
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[1]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_luiji");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                } else if (lbl_1_bss_B0 == 3) {
                    lbl_1_bss_72 = work->player[work->unk1B0[0]].unk54;
                    lbl_1_bss_70 = work->unk1B0[0];
                    if (lbl_1_bss_72 == -1) {
                        lbl_1_bss_72 = work->player[work->unk1B0[1]].unk54;
                        lbl_1_bss_70 = work->unk1B0[1];
                        if (lbl_1_bss_72 == -1) {
                            lbl_1_bss_72 = work->player[work->unk1B0[2]].unk54;
                            lbl_1_bss_70 = work->unk1B0[2];
                        }
                    }
                    if (lbl_1_bss_72 != -1) {
                        Hu3DModelShadowReset(lbl_1_bss_72);
                        Hu3DAnimModelKill(lbl_1_bss_72);
                        Hu3DModelKill(lbl_1_bss_72);
                        work->player[lbl_1_bss_70].unk54 = -1;
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_72 == work->player[i].unk54) {
                                work->player[i].unk54 = -1;
                            }
                        }
                    }
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[107], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    work->player[work->unk1B0[1]].unk54 = lbl_1_bss_72;
                    work->player[work->unk1B0[2]].unk54 = lbl_1_bss_72;
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[1]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_luiji");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[2]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_peach");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                }
                if (lbl_1_bss_B0 != 1) {
                    lbl_1_bss_AC = 0;
                    lbl_1_bss_A8[0] = lbl_1_bss_A8[1] = -1;
                    lbl_1_bss_A0[0] = lbl_1_bss_A0[1] = 0.0f;
                    lbl_1_bss_94 = 0;
                    work->player[work->unk1B0[0]].unk50 |= 0x80;
                    work->unk18C = 0x133;
                }
            } else {
                lbl_1_bss_A0[0] += 0.1f;
                if (lbl_1_bss_A0[0] > 1.0f) {
                    lbl_1_bss_A0[0] = 1.0f;
                }
                lbl_1_bss_72 = work->player[work->unk1B0[0]].unk54;
                Hu3DModelScaleSet(lbl_1_bss_72, 1.0f, lbl_1_bss_A0[0], 1.0f);
                if (1.0f == lbl_1_bss_A0[0]) {
                    lbl_1_bss_AC = 0;
                    lbl_1_bss_A8[0] = lbl_1_bss_A8[1] = -1;
                    lbl_1_bss_A0[0] = lbl_1_bss_A0[1] = 0.0f;
                    lbl_1_bss_94 = 0;
                    work->player[work->unk1B0[0]].unk50 |= 0x80;
                    work->unk18C = 0x133;
                }
            }
            break;
        case 0x138:
            fn_1_9DA8(&pos, work);
            work->unk1A4++;
            if (work->unk1A4 == 10) {
                for (j = 0; j < lbl_1_bss_B0; j++) {
                    if (0.0f != Hu3DData[lbl_1_bss_468[work->unk1B0[j]]].scale.y) {
                        mdl2 = lbl_1_bss_468[work->unk1B0[j]];
                        work->player[work->unk1B0[j]].unk50 |= 0x200;
                        if (work->player[work->unk1B0[j]].unk50 & 4) {
                            HuVecF scale = { 1.0f, 0.0f, 1.0f };
                            fn_1_3F6B0(4, work->player[work->unk1B0[j]].unk56, scale);
                        }
                        break;
                    }
                }
                Hu3DModelScaleSet(mdl2, 1.0f, 0.0f, 1.0f);
                if (lbl_1_bss_B0 == 1) {
                    lbl_1_bss_72 = player->unk54;
                    if (lbl_1_bss_72 != -1) {
                        Hu3DModelShadowReset(lbl_1_bss_72);
                        Hu3DAnimModelKill(lbl_1_bss_72);
                        Hu3DModelKill(lbl_1_bss_72);
                        player->unk54 = -1;
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_72 == work->player[i].unk54) {
                                work->player[i].unk54 = -1;
                            }
                        }
                    }
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[105], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                } else if (lbl_1_bss_B0 == 2) {
                    lbl_1_bss_72 = player->unk54;
                    if (lbl_1_bss_72 != -1) {
                        Hu3DModelShadowReset(lbl_1_bss_72);
                        Hu3DAnimModelKill(lbl_1_bss_72);
                        Hu3DModelKill(lbl_1_bss_72);
                        player->unk54 = -1;
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_72 == work->player[i].unk54) {
                                work->player[i].unk54 = -1;
                            }
                        }
                    }
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[106], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    work->player[work->unk1B0[1]].unk54 = lbl_1_bss_72;
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[1]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_luiji");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                } else if (lbl_1_bss_B0 == 3) {
                    lbl_1_bss_72 = player->unk54;
                    if (lbl_1_bss_72 != -1) {
                        Hu3DModelShadowReset(lbl_1_bss_72);
                        Hu3DAnimModelKill(lbl_1_bss_72);
                        Hu3DModelKill(lbl_1_bss_72);
                        player->unk54 = -1;
                        for (i = 0; i < 4; i++) {
                            if (lbl_1_bss_72 == work->player[i].unk54) {
                                work->player[i].unk54 = -1;
                            }
                        }
                    }
                    lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[107], HU_MEMNUM_OVL, HEAP_MODEL));
                    work->player[work->unk1B0[0]].unk54 = lbl_1_bss_72;
                    Hu3DModelCameraSet(lbl_1_bss_72, 1);
                    Hu3DModelLayerSet(lbl_1_bss_72, 2);
                    Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                    work->player[work->unk1B0[1]].unk54 = lbl_1_bss_72;
                    work->player[work->unk1B0[2]].unk54 = lbl_1_bss_72;
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[0]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[1]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_luiji");
                    Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[work->unk1B0[2]].unk2C + 0x6D], HU_MEMNUM_OVL), lbl_1_bss_72, "s_peach");
                    Hu3DModelShadowSet(lbl_1_bss_72);
                }
            }
            if (work->unk1A4 >= 20) {
                lbl_1_bss_A0[0] += 0.1f;
                if (lbl_1_bss_A0[0] > 1.0f) {
                    lbl_1_bss_A0[0] = 1.0f;
                }
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, lbl_1_bss_A0[0], 1.0f);
                if (player->unk50 & 4) {
                    HuVecF scale = { 1.0f, 1.0f, 1.0f };
                    scale.y = lbl_1_bss_A0[0];
                    fn_1_3F6B0(4, player->unk56, scale);
                }
                if (1.0f == lbl_1_bss_A0[0]) {
                    player->unk50 &= ~0x200;
                    lbl_1_bss_A0[0] = 0.0f;
                    player->unk50 &= ~0x80;
                    work->unk18C = 0x12D;
                }
            }
            break;
    }
    return ret;
}

/* 510 insns */
void fn_1_41EC(CardGameWork *work)
{
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    if (180.0f == player->unk18) {
        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
            if (lbl_1_bss_8C4[player->unk10 - 1][player->unk14] & 0x40) {
                player->unk10 = player->unk10 - 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 300.0f;
            } else {
                player->unk10 = player->unk10 - 1;
                player->unk20 = 2;
                work->unk18C = 305;
                lbl_1_bss_BC = 201.5625f;
            }
        } else {
            player->unk20 = player->unk20 - 1;
            if (player->unk20 >= 0) {
                work->unk18C = 306;
                lbl_1_bss_BC = 98.4375f;
            } else if (lbl_1_bss_8C4[player->unk10 - 1][player->unk14] & 0x40) {
                player->unk10 = player->unk10 - 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 201.5625f;
            } else {
                player->unk10 = player->unk10 - 1;
                player->unk20 = 2;
                work->unk18C = 305;
                lbl_1_bss_BC = 103.125f;
            }
        }
    } else if (0.0f == player->unk18) {
        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
            if (lbl_1_bss_8C4[player->unk10 + 1][player->unk14] & 0x40) {
                player->unk10 = player->unk10 + 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 300.0f;
            } else {
                player->unk10 = player->unk10 + 1;
                player->unk20 = 0;
                work->unk18C = 305;
                lbl_1_bss_BC = 201.5625f;
            }
        } else {
            player->unk20 = player->unk20 + 1;
            if (player->unk20 <= 2) {
                work->unk18C = 306;
                lbl_1_bss_BC = 98.4375f;
            } else if (lbl_1_bss_8C4[player->unk10 + 1][player->unk14] & 0x40) {
                player->unk10 = player->unk10 + 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 201.5625f;
            } else {
                player->unk10 = player->unk10 + 1;
                player->unk20 = 0;
                work->unk18C = 305;
                lbl_1_bss_BC = 103.125f;
            }
        }
    } else if (-90.0f == player->unk18) {
        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
            if (lbl_1_bss_8C4[player->unk10][player->unk14 - 1] & 0x40) {
                player->unk14 = player->unk14 - 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 300.0f;
            } else {
                player->unk14 = player->unk14 - 1;
                player->unk24 = 2;
                work->unk18C = 305;
                lbl_1_bss_BC = 201.5625f;
            }
        } else {
            player->unk24 = player->unk24 - 1;
            if (player->unk24 >= 0) {
                work->unk18C = 306;
                lbl_1_bss_BC = 98.4375f;
            } else if (lbl_1_bss_8C4[player->unk10][player->unk14 - 1] & 0x40) {
                player->unk14 = player->unk14 - 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 201.5625f;
            } else {
                player->unk14 = player->unk14 - 1;
                player->unk24 = 2;
                work->unk18C = 305;
                lbl_1_bss_BC = 103.125f;
            }
        }
    } else if (90.0f == player->unk18) {
        if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x40) {
            if (lbl_1_bss_8C4[player->unk10][player->unk14 + 1] & 0x40) {
                player->unk14 = player->unk14 + 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 300.0f;
            } else {
                player->unk14 = player->unk14 + 1;
                player->unk24 = 0;
                work->unk18C = 305;
                lbl_1_bss_BC = 201.5625f;
            }
        } else {
            player->unk24 = player->unk24 + 1;
            if (player->unk24 <= 2) {
                work->unk18C = 306;
                lbl_1_bss_BC = 98.4375f;
            } else if (lbl_1_bss_8C4[player->unk10][player->unk14 + 1] & 0x40) {
                player->unk14 = player->unk14 + 1;
                player->unk20 = 1;
                player->unk24 = 1;
                work->unk18C = 306;
                lbl_1_bss_BC = 201.5625f;
            } else {
                player->unk14 = player->unk14 + 1;
                player->unk24 = 0;
                work->unk18C = 305;
                lbl_1_bss_BC = 103.125f;
            }
        }
    }
    Hu3DModelRotSet(lbl_1_bss_468[work->unk174[work->unk170]], 0.0f, player->unk18, 0.0f);
}

/* 537 insns */
s32 fn_1_49E4(CardGameWork *work)
{
    s32 i;
    s32 result;
    CardPlayerWork *player;
    HuVecF pos;

    result = 0;
    player = &work->player[work->unk174[work->unk170]];
    pos = lbl_1_bss_88;
    if (player->unk50 & 0x100) {
        lbl_1_bss_80 -= 0.1f;
        if (lbl_1_bss_80 < 0.0f) {
            lbl_1_bss_80 = 0.0f;
        }
        Hu3DModelScaleSet(lbl_1_bss_468[lbl_1_bss_74[0]], 1.0f, 1.0f - lbl_1_bss_80, 1.0f);
        if (work->player[lbl_1_bss_74[0]].unk50 & 4) {
            HuVecF scale = { 1.0f, 1.0f, 1.0f };
            scale.y -= lbl_1_bss_80;
            fn_1_3F6B0(4, work->player[lbl_1_bss_74[0]].unk56, scale);
        }
        if (work->player[lbl_1_bss_74[0]].unk58 != -1) {
            Hu3DModelScaleSet(work->player[lbl_1_bss_74[0]].unk58, 1.0f, 1.0f - lbl_1_bss_80, 1.0f);
            work->player[lbl_1_bss_74[0]].unk50 &= ~0x80;
        }
        lbl_1_bss_94 = 1;
        if (lbl_1_bss_84 == 1) {
            lbl_1_bss_72 = work->player[lbl_1_bss_74[0]].unk54;
            Hu3DModelScaleSet(lbl_1_bss_72, 1.0f, lbl_1_bss_80, 1.0f);
        }
        if (0.0f == lbl_1_bss_80) {
            work->player[lbl_1_bss_74[0]].unk50 &= ~0x200;
            if (lbl_1_bss_84 == 1) {
                lbl_1_bss_72 = work->player[lbl_1_bss_74[0]].unk54;
                if (lbl_1_bss_72 != -1) {
                    Hu3DModelShadowReset(lbl_1_bss_72);
                    Hu3DAnimModelKill(lbl_1_bss_72);
                    Hu3DModelKill(lbl_1_bss_72);
                    work->player[lbl_1_bss_74[0]].unk54 = -1;
                    for (i = 0; i < 4; i++) {
                        if (lbl_1_bss_72 == work->player[i].unk54) {
                            work->player[i].unk54 = -1;
                        }
                    }
                }
            } else if (lbl_1_bss_84 == 2) {
                lbl_1_bss_72 = work->player[lbl_1_bss_74[0]].unk54;
                if (lbl_1_bss_72 != -1) {
                    Hu3DModelShadowReset(lbl_1_bss_72);
                    Hu3DAnimModelKill(lbl_1_bss_72);
                    Hu3DModelKill(lbl_1_bss_72);
                    work->player[lbl_1_bss_74[0]].unk54 = -1;
                    for (i = 0; i < 4; i++) {
                        if (lbl_1_bss_72 == work->player[i].unk54) {
                            work->player[i].unk54 = -1;
                        }
                    }
                }
                lbl_1_bss_72 = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[105], HU_MEMNUM_OVL, HEAP_MODEL));
                work->player[lbl_1_bss_74[1]].unk54 = lbl_1_bss_72;
                Hu3DModelCameraSet(lbl_1_bss_72, 1);
                Hu3DModelLayerSet(lbl_1_bss_72, 2);
                Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[lbl_1_bss_74[1]].unk2C + 109], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                Hu3DModelShadowSet(lbl_1_bss_72);
            } else if (lbl_1_bss_84 == 3) {
                lbl_1_bss_72 = work->player[lbl_1_bss_74[0]].unk54;
                if (lbl_1_bss_72 != -1) {
                    Hu3DModelShadowReset(lbl_1_bss_72);
                    Hu3DAnimModelKill(lbl_1_bss_72);
                    Hu3DModelKill(lbl_1_bss_72);
                    work->player[lbl_1_bss_74[0]].unk54 = -1;
                    for (i = 0; i < 4; i++) {
                        if (lbl_1_bss_72 == work->player[i].unk54) {
                            work->player[i].unk54 = -1;
                        }
                    }
                }
                lbl_1_bss_72 = Hu3DModelCreate((void *)HuDataSelHeapReadNum(lbl_1_data_B0[106], HU_MEMNUM_OVL, HEAP_MODEL));
                work->player[lbl_1_bss_74[1]].unk54 = lbl_1_bss_72;
                Hu3DModelCameraSet(lbl_1_bss_72, 1);
                Hu3DModelLayerSet(lbl_1_bss_72, 2);
                Hu3DModelPosSet(lbl_1_bss_72, -50.0f + pos.x, pos.y, pos.z);
                work->player[lbl_1_bss_74[2]].unk54 = lbl_1_bss_72;
                Hu3DAnimCreate((void *)HuDataReadNum(lbl_1_data_B0[work->player[lbl_1_bss_74[1]].unk2C + 109], HU_MEMNUM_OVL), lbl_1_bss_72, "s_mario");
                Hu3DAnimCreate(HuDataReadNum(lbl_1_data_B0[work->player[lbl_1_bss_74[2]].unk2C + 109], HU_MEMNUM_OVL), lbl_1_bss_72, "s_luiji");
                Hu3DModelShadowSet(lbl_1_bss_72);
            }
            player->unk50 &= ~0x100;
            result = 1;
        }
    } else {
        result = 1;
    }
    return result;
}

/* 174 insns */
s32 fn_1_5248(CardGameWork *work)
{
    s32 result;
    s32 done;

    result = 0;
    done = fn_1_49E4(work);
    if (lbl_1_bss_AC) {
        lbl_1_bss_A0[0] -= 0.1f;
        if (lbl_1_bss_A0[0] < 0.0f) {
            lbl_1_bss_A0[0] = 0.0f;
        }
        Hu3DModelScaleSet(lbl_1_bss_A8[0], 1.0f, 1.0f - lbl_1_bss_A0[0], 1.0f);
        if (work->player[lbl_1_bss_98[0]].unk50 & 4) {
            HuVecF scale = { 1.0f, 1.0f, 1.0f };
            scale.y -= lbl_1_bss_A0[0];
            fn_1_3F6B0(4, work->player[lbl_1_bss_98[0]].unk56, scale);
        }
        if (work->player[lbl_1_bss_98[0]].unk58 != -1) {
            Hu3DModelScaleSet(work->player[lbl_1_bss_98[0]].unk58, 1.0f, 1.0f - lbl_1_bss_A0[0], 1.0f);
        }
        if (0.0f == lbl_1_bss_A0[0]) {
            work->player[lbl_1_bss_98[0]].unk50 &= ~0x200;
            lbl_1_bss_AC = 0;
            lbl_1_bss_A8[0] = -1;
            lbl_1_bss_98[0] = -1;
        }
        lbl_1_bss_94 = 1;
    }
    if (lbl_1_bss_AC == 0 && done) {
        result = 1;
    }
    return result;
}

/* 132 insns */
void fn_1_5500(CardGameWork *work)
{
    s32 i;
    s32 j;

    lbl_1_bss_AC = 0;
    lbl_1_bss_A8[0] = lbl_1_bss_A8[1] = -1;
    lbl_1_bss_A0[0] = lbl_1_bss_A0[1] = 0.0f;
    lbl_1_bss_98[0] = lbl_1_bss_98[1] = -1;
    lbl_1_bss_94 = 0;
    for (i = 0; i < 4; i++) {
        Hu3DModelScaleSet(lbl_1_bss_468[i], 1.0f, 1.0f, 1.0f);
        Hu3DModelAttrReset(lbl_1_bss_468[i], HU3D_ATTR_DISPOFF);
        lbl_1_bss_72 = work->player[i].unk54;
        if (lbl_1_bss_72 != -1) {
            Hu3DModelShadowReset(lbl_1_bss_72);
            Hu3DAnimModelKill(lbl_1_bss_72);
            Hu3DModelKill(lbl_1_bss_72);
            work->player[i].unk54 = -1;
            for (j = 0; j < 4; j++) {
                if (lbl_1_bss_72 == work->player[j].unk54) {
                    work->player[j].unk54 = -1;
                }
            }
        }
        work->player[i].unk50 &= ~0x80;
        work->player[i].unk50 &= ~0x100;
        work->player[i].unk50 &= ~0x200;
    }
}

/* 188 insns */
s32 fn_1_5710(CardGameWork *work, s32 order, s32 n)
{
    CardPlayerWork *player;
    CardPlayerWork *other;
    s32 x;
    s32 y;
    s32 i;
    s32 before;
    s32 after;
    s32 sx;
    s32 sy;
    s32 count;
    s32 tmp;

    player = &work->player[work->unk174[order]];
    x = player->unk10;
    y = player->unk14;
    sx = player->unk20;
    sy = player->unk24;
    if (n > 0) {
        if (180.0f == player->unk18) {
            x++;
            if (lbl_1_bss_8C4[x][y] & 0x40) {
                sx = 1;
            } else {
                sx = 0;
            }
        } else if (0.0f == player->unk18) {
            x--;
            if (lbl_1_bss_8C4[x][y] & 0x40) {
                sx = 1;
            } else {
                sx = 2;
            }
        } else if (-90.0f == player->unk18) {
            y++;
            if (lbl_1_bss_8C4[x][y] & 0x40) {
                sy = 1;
            } else {
                sy = 0;
            }
        } else if (90.0f == player->unk18) {
            y--;
            if (lbl_1_bss_8C4[x][y] & 0x40) {
                sy = 1;
            } else {
                sy = 2;
            }
        }
    }
    count = 0;
    before = 0;
    after = 0;
    for (i = 0; i < 4; i++) {
        if (i == order) {
            continue;
        }
        other = &work->player[work->unk174[i]];
        if (x == other->unk10 && y == other->unk14 && sx == other->unk20 && sy == other->unk24 && other->unk0 == 0) {
            work->unk1B0[count] = work->unk174[i];
            count++;
            if (i < order) {
                before++;
            } else if (i > order) {
                after++;
            }
        }
    }
    if (n == 2) {
        return count;
    }
    if (before > 0 && after > 0) {
        if (before == 1 && after == 1) {
            tmp = work->unk1B0[0];
            work->unk1B0[0] = work->unk1B0[1];
            work->unk1B0[1] = tmp;
        } else if (before == 2 && after == 1) {
            tmp = work->unk1B0[2];
            work->unk1B0[2] = work->unk1B0[1];
            work->unk1B0[1] = work->unk1B0[0];
            work->unk1B0[0] = tmp;
        } else if (before == 1 && after == 2) {
            tmp = work->unk1B0[0];
            work->unk1B0[0] = work->unk1B0[1];
            work->unk1B0[1] = work->unk1B0[2];
            work->unk1B0[2] = tmp;
        }
    }
    return count;
}

/* 553 insns */
void fn_1_5A00(CardGameWork *work)
{
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    s32 delay = 30;

    if (GwPlayerConf[work->unk174[work->unk170]].type) {
        HuPadBtnDown[work->unk174[work->unk170]] = 0;
        HuPadDStkRep[work->unk174[work->unk170]] = 0;
        switch (work->unk18C) {
            case 301:
                delay = 100;
                if (++lbl_1_bss_B8 >= delay) {
                    HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                    lbl_1_bss_B8 = 0;
                }
                break;
            case 302:
                if (++lbl_1_bss_B8 >= delay) {
                    if (player->unk50 & 0x20) {
                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                        lbl_1_bss_B8 = 0;
                    } else {
                        if (player->unk34 != -1) {
                            if (fn_1_25624(work)) {
                                if (player->unk38 != -1) {
                                    if (player->unk3C != -1) {
                                        if (player->unk34 == 0 && player->unk38 == 0 && player->unk3C == 0) {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                        } else if (player->unk34 == 0 || player->unk38 == 0 || player->unk3C == 0) {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                        } else {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                        }
                                    } else if (player->unk34 == 0 && player->unk38 == 0) {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                    } else if (player->unk34 == 0 || player->unk38 == 0) {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                    } else {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                    }
                                } else if (player->unk34 == 0) {
                                    HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                } else {
                                    HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                }
                            } else {
                                HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                if (player->unk38 != -1) {
                                    if (player->unk3C != -1) {
                                        if (player->unk34 == 0 && player->unk38 == 0 && player->unk3C == 0) {
                                            if (fn_1_21028(work) == 0) {
                                                HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                            } else {
                                                HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                            }
                                        } else {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                        }
                                    } else if (player->unk34 == 0 && player->unk38 == 0) {
                                        if (fn_1_21028(work) == 0) {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                        } else {
                                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                        }
                                    } else {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                    }
                                } else if (player->unk34 == 0) {
                                    if (fn_1_21028(work) == 0) {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                                    } else {
                                        HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                    }
                                } else {
                                    HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_B;
                                }
                            }
                        } else {
                            HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                        }
                        lbl_1_bss_B8 = 0;
                    }
                }
                break;
            case 303:
                lbl_1_bss_B8++;
                lbl_1_bss_B8 = lbl_1_bss_B8 % 300;
                if (player->unk0) {
                    if (work->unk174[work->unk170] == 0 && lbl_1_bss_B8 >= delay) {
                        HuPadDStkRep[0] = 4;
                        lbl_1_bss_B8 = 0;
                    } else if (work->unk174[work->unk170] == 1 && lbl_1_bss_B8 >= delay) {
                        HuPadDStkRep[1] = 8;
                        lbl_1_bss_B8 = 0;
                    } else if (work->unk174[work->unk170] == 2 && lbl_1_bss_B8 >= delay) {
                        HuPadDStkRep[2] = 2;
                        lbl_1_bss_B8 = 0;
                    } else if (work->unk174[work->unk170] == 3 && lbl_1_bss_B8 >= delay) {
                        HuPadDStkRep[3] = 1;
                        lbl_1_bss_B8 = 0;
                    }
                } else if (lbl_1_bss_B8 == delay) {
                    HuPadDStkRep[work->unk174[work->unk170]] = fn_1_62A4(work);
                } else if (lbl_1_bss_B8 == delay * 2) {
                    HuPadBtnDown[work->unk174[work->unk170]] = PAD_BUTTON_A;
                    lbl_1_bss_B8 = 0;
                    lbl_1_bss_C3C = 0;
                }
                break;
        }
    }
}

/* 893 insns */
u16 fn_1_62A4(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 x;
    s32 y;
    s32 i;
    u16 result;
    s32 dir;
    s32 found;

#define CELL lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24]
    result = 0;
    found = 0;
    player = &work->player[work->unk174[work->unk170]];
    if (lbl_1_bss_C3C && (dir = fn_1_21028(work)) != 0) {
        result = (dir == 1) ? 8 : (dir == 2) ? 4 : (dir == 3) ? 1 : 2;
        return result;
    }
    for (i = 0; i < 2; i++) {
        if ((CELL & 1) && player->unk10 - i > 0 && (lbl_1_bss_8C4[player->unk10 - (i + 1)][player->unk14] & 0xF00)
            && !(lbl_1_bss_8C4[player->unk10 - (i + 1)][player->unk14] & 0x800) && (lbl_1_bss_8C4[player->unk10][player->unk14] & 1)) {
            if (lbl_1_bss_8C4[player->unk10 - (i + 1)][player->unk14] & 0x400) {
                result = 8;
                found = 1;
                if (frandmod(2)) {
                    break;
                }
            } else if (found == 0) {
                result = 8;
                found = -1;
            }
        }
        if ((CELL & 2) && player->unk10 + i < work->unk194 - 1 && (lbl_1_bss_8C4[1 + i + player->unk10][player->unk14] & 0xF00)
            && !(lbl_1_bss_8C4[1 + i + player->unk10][player->unk14] & 0x800) && (lbl_1_bss_8C4[player->unk10][player->unk14] & 2)) {
            if (lbl_1_bss_8C4[1 + i + player->unk10][player->unk14] & 0x400) {
                result = 4;
                found = 1;
                if (frandmod(2)) {
                    break;
                }
            } else if (found == 0) {
                result = 4;
                found = -1;
            }
        }
        if ((CELL & 4) && player->unk14 - i > 0 && (lbl_1_bss_8C4[player->unk10][player->unk14 - (i + 1)] & 0xF00)
            && !(lbl_1_bss_8C4[player->unk10][player->unk14 - (i + 1)] & 0x800) && (lbl_1_bss_8C4[player->unk10][player->unk14] & 4)) {
            if (lbl_1_bss_8C4[player->unk10][player->unk14 - (i + 1)] & 0x400) {
                result = 1;
                found = 1;
                if (frandmod(2)) {
                    break;
                }
            } else if (found == 0) {
                result = 1;
                found = -1;
            }
        }
        if ((CELL & 8) && player->unk14 + i < work->unk194 - 1 && (lbl_1_bss_8C4[player->unk10][1 + i + player->unk14] & 0xF00)
            && !(lbl_1_bss_8C4[player->unk10][1 + i + player->unk14] & 0x800) && (lbl_1_bss_8C4[player->unk10][player->unk14] & 8)) {
            if (lbl_1_bss_8C4[player->unk10][1 + i + player->unk14] & 0x400) {
                result = 2;
                found = 1;
                if (frandmod(2)) {
                    break;
                }
            } else if (found == 0) {
                result = 2;
                found = -1;
            }
        }
        if (found == 1) {
            break;
        }
        if (found == -1 && frandmod(2)) {
            break;
        }
    }
    if (found == 0) {
        for (x = 0; x < work->unk194 - 1; x++) {
            for (y = 0; y < work->unk194 - 1; y++) {
                if (lbl_1_bss_8C4[x][y] & 0xF00) {
                    if (frandmod(2)) {
                        if (x < player->unk10) {
                            if (CELL & 1) {
                                result = 8;
                            } else {
                                result = fn_1_7098(work, x, y, 0);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else if (x > player->unk10) {
                            if (CELL & 2) {
                                result = 4;
                            } else {
                                result = fn_1_7098(work, x, y, 0);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else if (y < player->unk14) {
                            if (CELL & 4) {
                                result = 1;
                            } else {
                                result = fn_1_7098(work, x, y, 1);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else {
                            if (CELL & 8) {
                                result = 2;
                            } else {
                                result = fn_1_7098(work, x, y, 1);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        }
                    } else {
                        if (y < player->unk14) {
                            if (CELL & 4) {
                                result = 1;
                            } else {
                                result = fn_1_7098(work, x, y, 1);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else if (y > player->unk14) {
                            if (CELL & 8) {
                                result = 2;
                            } else {
                                result = fn_1_7098(work, x, y, 1);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else if (x < player->unk10) {
                            if (CELL & 1) {
                                result = 8;
                            } else {
                                result = fn_1_7098(work, x, y, 0);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        } else {
                            if (CELL & 2) {
                                result = 4;
                            } else {
                                result = fn_1_7098(work, x, y, 0);
                            }
                            if (frandmod(2)) {
                                if (lbl_1_bss_8C4[x][y] & 0x400) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                } else if (frandmod(2)) {
                                    x = work->unk194 - 1;
                                    y = work->unk194 - 1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
#undef CELL
    return result;
}

/* 155 insns */
u16 fn_1_7098(CardGameWork *work, s32 x, s32 y, s32 axis)
{
    CardPlayerWork *player;
    u16 result;

    result = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (axis) {
        case 0:
            if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 4) {
                result = 1;
            }
            if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 8) {
                if (result == 1) {
                    result = (y < player->unk14) ? 1 : (y > player->unk14) ? 2 : frandmod(2) ? 1 : 2;
                } else {
                    result = 2;
                }
            }
            break;
        case 1:
            if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 1) {
                result = 8;
            }
            if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 2) {
                if (result == 8) {
                    result = (x < player->unk10) ? 8 : (x > player->unk10) ? 4 : frandmod(2) ? 8 : 4;
                } else {
                    result = 4;
                }
            }
            break;
    }
    return result;
}

/* 307 insns */
void fn_1_7304(void)
{
    s32 i;
    HuVecF pos;

    for (i = 0; i < 4; i++) {
        lbl_1_bss_2F8[i][0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[64], HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_2F8[i][1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[65], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(lbl_1_bss_2F8[i][0], 1);
        Hu3DModelCameraSet(lbl_1_bss_2F8[i][1], 1);
        if (i == 0) {
            pos.x = -50.0f;
            pos.y = 180.0f;
            pos.z = -55.0f;
            lbl_1_bss_2C8[i].x = 0.0f;
            lbl_1_bss_2C8[i].y = 0.0f;
            lbl_1_bss_2C8[i].z = 0.0f;
        } else if (i == 1) {
            pos.x = -50.0f;
            pos.y = 180.0f;
            pos.z = 55.0f;
            lbl_1_bss_2C8[i].x = 0.0f;
            lbl_1_bss_2C8[i].y = 180.0f;
            lbl_1_bss_2C8[i].z = 0.0f;
        } else if (i == 2) {
            pos.x = -105.0f;
            pos.y = 180.0f;
            pos.z = 0.0f;
            lbl_1_bss_2C8[i].x = 0.0f;
            lbl_1_bss_2C8[i].y = 90.0f;
            lbl_1_bss_2C8[i].z = 0.0f;
        } else {
            pos.x = 5.0f;
            pos.y = 180.0f;
            pos.z = 0.0f;
            lbl_1_bss_2C8[i].x = 0.0f;
            lbl_1_bss_2C8[i].y = -90.0f;
            lbl_1_bss_2C8[i].z = 0.0f;
        }
        Hu3DModelPosSetV(lbl_1_bss_2F8[i][0], &pos);
        Hu3DModelPosSetV(lbl_1_bss_2F8[i][1], &pos);
        Hu3DModelRotSetV(lbl_1_bss_2F8[i][0], &lbl_1_bss_2C8[i]);
        Hu3DModelRotSetV(lbl_1_bss_2F8[i][1], &lbl_1_bss_2C8[i]);
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][1], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(lbl_1_bss_2F8[i][0], 3);
        Hu3DModelLayerSet(lbl_1_bss_2F8[i][1], 3);
        Hu3DModelScaleSet(lbl_1_bss_2F8[i][0], 0.7f, 0.7f, 0.7f);
        Hu3DModelScaleSet(lbl_1_bss_2F8[i][1], 0.7f, 0.7f, 0.7f);
    }
    lbl_1_bss_2C4 = 0;
    lbl_1_bss_2BC[0] = 0.0f;
}

/* 395 insns */
void fn_1_77D0(HuVecF *pos, CardGameWork *work)
{
    CardPlayerWork *player;
    s32 i;
    HuVecF temp;

    player = &work->player[work->unk174[work->unk170]];
    if (lbl_1_bss_2C4 == 0) {
        lbl_1_bss_2BC[0] += 2.0f;
        if (lbl_1_bss_2BC[0] >= 20.0f) {
            lbl_1_bss_2C4 = 1;
        }
    }
    else {
        lbl_1_bss_2BC[0] -= 2.0f;
        if (lbl_1_bss_2BC[0] <= 0.0f) {
            lbl_1_bss_2C4 = 0;
        }
    }
    for (i = 0; i < 4; i++) {
        temp = *pos;
        if (i == 0) {
            temp.x += -50.0f;
            temp.y += 180.0f;
            temp.z += -55.0f - lbl_1_bss_2BC[0];
        }
        else if (i == 1) {
            temp.x += -50.0f;
            temp.y += 180.0f;
            temp.z += 55.0f + lbl_1_bss_2BC[0];
        }
        else if (i == 2) {
            temp.x += -50.0f + (-55.0f - lbl_1_bss_2BC[0]);
            temp.y += 180.0f;
        }
        else {
            temp.x += -50.0f + (55.0f + lbl_1_bss_2BC[0]);
            temp.y += 180.0f;
        }
        Hu3DModelPosSetV(lbl_1_bss_2F8[i][0], &temp);
        Hu3DModelPosSetV(lbl_1_bss_2F8[i][1], &temp);
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][1], HU3D_ATTR_DISPOFF);
    }
    if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 1) != 0
        && (work->unk1A0 != 0 || (work->unk1A0 == 0 && 0.0f != player->unk1C))) {
        if (180.0f == player->unk18) {
            Hu3DModelAttrReset(lbl_1_bss_2F8[0][0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(lbl_1_bss_2F8[0][1], HU3D_ATTR_DISPOFF);
        }
    }
    if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 2) != 0
        && (work->unk1A0 != 0 || (work->unk1A0 == 0 && 180.0f != player->unk1C))) {
        if (0.0f == player->unk18) {
            Hu3DModelAttrReset(lbl_1_bss_2F8[1][0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(lbl_1_bss_2F8[1][1], HU3D_ATTR_DISPOFF);
        }
    }
    if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 4) != 0
        && (work->unk1A0 != 0 || (work->unk1A0 == 0 && 90.0f != player->unk1C))) {
        if (-90.0f == player->unk18) {
            Hu3DModelAttrReset(lbl_1_bss_2F8[2][0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(lbl_1_bss_2F8[2][1], HU3D_ATTR_DISPOFF);
        }
    }
    if ((lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] & 8) != 0
        && (work->unk1A0 != 0 || (work->unk1A0 == 0 && -90.0f != player->unk1C))) {
        if (90.0f == player->unk18) {
            Hu3DModelAttrReset(lbl_1_bss_2F8[3][0], HU3D_ATTR_DISPOFF);
        }
        else {
            Hu3DModelAttrReset(lbl_1_bss_2F8[3][1], HU3D_ATTR_DISPOFF);
        }
    }
}

/* 11 insns */
void fn_1_7DFC(void)
{
    lbl_1_bss_2C4 = 0;
    lbl_1_bss_2BC[0] = 0.0f;
}

/* 28 insns */
void fn_1_7E28(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_2F8[i][1], HU3D_ATTR_DISPOFF);
    }
}

/* 413 insns */
void fn_1_7E98(CardPlayerWork *player)
{
    if (180.0f == player->unk18) {
        if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 14 || lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 12) {
            player->unk18 = frandmod(2) ? -90.0f : 90.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 6) {
            player->unk18 = -90.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 10) {
            player->unk18 = 90.0f;
        }
    }
    else if (0.0f == player->unk18) {
        if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 13 || lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 12) {
            player->unk18 = frandmod(2) ? -90.0f : 90.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 5) {
            player->unk18 = -90.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 9) {
            player->unk18 = 90.0f;
        }
    }
    else if (-90.0f == player->unk18) {
        if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 11 || lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 3) {
            player->unk18 = frandmod(2) ? 180.0f : 0.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 9) {
            player->unk18 = 180.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 10) {
            player->unk18 = 0.0f;
        }
    }
    else if (90.0f == player->unk18) {
        if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 7 || lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 3) {
            player->unk18 = frandmod(2) ? 180.0f : 0.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 5) {
            player->unk18 = 180.0f;
        }
        else if (lbl_1_bss_540[player->unk10][player->unk14][player->unk20][player->unk24] == 6) {
            player->unk18 = 0.0f;
        }
    }
}

/* 23 insns */
void fn_1_850C(void)
{
    lbl_1_bss_5C = Hu3DHookFuncCreate(fn_1_8568);
    Hu3DModelLayerSet(lbl_1_bss_5C, 5);
    Hu3DModelCameraSet(lbl_1_bss_5C, HU3D_CAM0);
}

/* 203 insns */
void fn_1_8568(HU3DMODEL *modelP, Mtx *mtx)
{
    GXColor color = { 0, 0, 0, 0 };
    Mtx44 proj;

    color.a = lbl_1_bss_5E;
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -16777215.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    MTXIdentity(*mtx);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetNumChans(1);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3s16(0, 0, 0);
    GXPosition3s16(640, 0, 0);
    GXPosition3s16(640, 480, 0);
    GXPosition3s16(0, 480, 0);
    GXEnd();
}

/* 188 insns */
void fn_1_8894(void)
{
    HuVecF dir;
    Mtx rotMtx;
    float angleY;
    float angleX;

    VECSubtract(&Hu3DCamera[0].target, &Hu3DCamera[0].pos, &dir);
    VECNormalize(&dir, &dir);
    angleY = 180.0 * (atan2(dir.x, dir.z) / M_PI);
    Hu3DModelAttrReset(lbl_1_bss_308[2], HU3D_ATTR_DISPOFF);
    lbl_1_bss_4C[0] = 0;
    Hu3DModelAttrReset(lbl_1_bss_308[3], HU3D_ATTR_DISPOFF);
    lbl_1_bss_4C[1] = 0;
    Hu3DModelAttrReset(lbl_1_bss_308[4], HU3D_ATTR_DISPOFF);
    lbl_1_bss_4C[2] = 0;
    Hu3DModelAttrReset(lbl_1_bss_308[5], HU3D_ATTR_DISPOFF);
    lbl_1_bss_4C[3] = 0;
    MTXRotDeg(rotMtx, 'y', -angleY);
    MTXMultVec(rotMtx, &dir, &dir);
    angleX = 180.0 * (atan2(dir.y, dir.z) / M_PI);
    if (angleX <= -30.0f) {
        return;
    }
    if (angleY >= 0.0f && angleY <= 90.0f) {
        Hu3DModelAttrSet(lbl_1_bss_308[2], HU3D_ATTR_DISPOFF);
        lbl_1_bss_4C[0] = 1;
    }
    if (angleY <= 0.0f && angleY >= -90.0f) {
        Hu3DModelAttrSet(lbl_1_bss_308[3], HU3D_ATTR_DISPOFF);
        lbl_1_bss_4C[1] = 1;
    }
    if (angleY >= 90.0f && angleY <= 180.0f) {
        Hu3DModelAttrSet(lbl_1_bss_308[4], HU3D_ATTR_DISPOFF);
        lbl_1_bss_4C[2] = 1;
    }
    if (angleY <= -90.0f && angleY >= -180.0f) {
        Hu3DModelAttrSet(lbl_1_bss_308[5], HU3D_ATTR_DISPOFF);
        lbl_1_bss_4C[3] = 1;
    }
}

/* 61 insns */
void fn_1_8B84(CardGameWork *work)
{
    switch (work->unk188) {
        case 0xC8:
        case 0xCC:
            Hu3DModelAttrReset(lbl_1_bss_308[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_308[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_308[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(lbl_1_bss_308[5], HU3D_ATTR_DISPOFF);
            break;
        case 0xCD:
            if (lbl_1_bss_4C[2] == 0) {
                Hu3DModelAttrReset(lbl_1_bss_308[4], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_4C[3] == 0) {
                Hu3DModelAttrReset(lbl_1_bss_308[5], HU3D_ATTR_DISPOFF);
            }
            break;
    }
}

/* 35 insns */
void fn_1_8C78(void)
{
    s32 i;

    lbl_1_bss_4A = 0;
    lbl_1_bss_48 = 0;
    for (i = 0; i < 10; i++) {
        lbl_1_bss_20[i] = 0;
    }
    lbl_1_bss_8[0] = lbl_1_bss_8[1] = 0;
    lbl_1_bss_14 = -1;
}

/* 97 insns */
s32 fn_1_8D04(s32 seNo, s16 mdlId, s16 a2)
{
    s32 pan;
    s32 seId;
    HuVecF pos;
    HuVecF out;

    pos = Hu3DData[mdlId].pos;
    Hu3D3Dto2D(&pos, a2, &out);
    if (out.x < 0.0f || out.x > 576.0f) {
        return -1;
    }
    if (out.y < 0.0f || out.y > 480.0f) {
        return -1;
    }
    pan = (s32)(out.x / 9.0f) + 32;
    if ((seNo & 0x8000) == 0) {
        seId = HuAudFXPlay(seNo & 0x7FF);
        if (seNo == 0x40B || seNo == 0x40C || seNo == 0x353 || seNo == 0x43A || seNo == 0x446 || seNo == 0x456) {
            lbl_1_bss_18 = seId;
        }
    }
    else {
        seId = lbl_1_bss_18;
    }
    HuAudFXPanning(seId, pan);
    return seId;
}

/* 16 insns */
s32 fn_1_8E88(void)
{
    CardGameWork *work = &lbl_1_bss_E4;
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];

    return player->unk50;
}

