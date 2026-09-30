/*
 * m562dll main.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/main.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/mgdata.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x18 lbl_1_rodata_18 (0xC): 0x00000000 0x450CA000 0xC3FA0000 -- an aggregate initialiser, write it as a local */
/* 0x24 lbl_1_rodata_24 (0xC): 0x00000000 0x450E5000 0xC4898000 -- an aggregate initialiser, write it as a local */
/* 0x30 lbl_1_rodata_30 (0xC): 0x00000000 0x447A0000 0x44AF0000 -- an aggregate initialiser, write it as a local */
/* 0x3C lbl_1_rodata_3C (0xC): 0x00000000 0x42C80000 0xC3480000 -- an aggregate initialiser, write it as a local */
/* 0x48 lbl_1_rodata_48 (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_54 = 30000.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 1000.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 45.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 20.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 50000.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 0.5f; /* 0x68 */
static const float lbl_1_rodata_6C = -10000.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 350.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 15.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 0.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 9.16f; /* 0x7C */
static const float lbl_1_rodata_80 = 1.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 525.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 64.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 60.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 40.0f; /* 0x90 */
/* 0x98 lbl_1_rodata_98 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_A0 = 0.9999999f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 2.0f; /* 0xA4 */
static const double lbl_1_rodata_A8 = 0.5; /* 0xA8 */
static const double lbl_1_rodata_B0 = 3.0; /* 0xB0 */
static const double lbl_1_rodata_B8 = 360.0; /* 0xB8 */
static const float lbl_1_rodata_C0 = 360.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 180.0f; /* 0xC4 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x6010 */ HuVecF lbl_1_bss_6010[256][2];
/* 0x3C10 */ HuVecF lbl_1_bss_3C10[256][3];
/* 0xC10 */ HuVecF lbl_1_bss_C10[256][4];
/* 0x80E */ GXColor lbl_1_bss_80E[256];
/* 0x40E */ GXColor lbl_1_bss_40E[256];
/* 0xE */ GXColor lbl_1_bss_E[256];
/* 0xC */ u16 lbl_1_bss_C;
/* 0xA */ u16 lbl_1_bss_A;
/* 0x8 */ u16 lbl_1_bss_8;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x30 */ HuVecF lbl_1_data_30 = { 0.0f, 3000.0f, 100.0f };
/* 0x3C */ HuVecF lbl_1_data_3C = { 0.0f, 1.0f, 0.0f };
/* 0x48 */ HuVecF lbl_1_data_48 = { 0.0f, 0.0f, 0.0f };

/* 315 insns: set up the whole scene (phase 1 objects) */
void fn_1_AC4(M562_WORK *work, OMOBJMAN *objman)
{
    HuVec2f size;
    HuVecF heading;

    memset(work, 0, sizeof(M562_WORK));
    work->unk0000 = objman;
    work->unk0014 = 1500;
    work->unk28A0 = -1;
    work->unk28A8 = -1;
    work->unk28AC = -1;
    work->unk0020 = (GwPlayerConf[0].dif == 3) ? 0 : (GwPlayerConf[0].dif == 2) ? 1 : (GwPlayerConf[0].dif == 1) ? 2 : 3;
    fn_1_2253C(&work->light, work);
    fn_1_20CE0(&work->camera[1], 1, 1, work);
    {
        HuVecF pos = { 0.0f, 2250.0f, -500.0f };
        HuVecF *p = &pos;
        work->camera[1].unk10 = work->camera[1].unk34 = *p;
    }
    {
        HuVecF target = { 0.0f, 2277.0f, -1100.0f };
        HuVecF *p = &target;
        work->camera[1].unk1C = work->camera[1].unk40 = *p;
    }
    fn_1_20CE0(&work->camera[0], 2, 1, work);
    {
        HuVecF pos = { 0.0f, 1000.0f, 1400.0f };
        HuVecF *p = &pos;
        work->camera[0].unk10 = work->camera[0].unk34 = *p;
    }
    {
        HuVecF target = { 0.0f, 100.0f, -200.0f };
        HuVecF *p = &target;
        work->camera[0].unk1C = work->camera[0].unk40 = *p;
    }
    {
        HuVecF dir = { 0.0f, 0.0f, -1.0f };
        HuVecF *p = &dir;
        heading = *p;
    }
    fn_1_8C4(&work->camera[0].unk34, &heading, 30000.0f, 1000.0f);
    work->camera[0].unk08 = 0;
    work->camera[0].unk0A = 2;
    fn_1_6B28(&work->player, 0, work);
    CharEffectLayerSet(4);
    fn_1_3808(&work->back, work);
    fn_1_5688(&work->stage, work);
    Hu3DShadowCreate(45.0f, 20.0f, 50000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowSizeSet(240);
    Hu3DShadowPosSet(&lbl_1_data_30, &lbl_1_data_3C, &lbl_1_data_48);
    fn_1_13CFC(&work->fire, work);
    work->fire.unk0004 = 1;
    fn_1_B2E0(&work->koopa, work);
    fn_1_18E88(&work->firering, work);
    work->firering.unk10 = 0;
    Hu3DLayerHookSet(15, fn_1_508C);
    work->unk2864 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    work->unk2868 = HuSprAnimDataRead(DATANUM(DATA_m562, 0x6D));
    fn_1_177EC(&work->mechakoopa, work);
    work->mechakoopa.unk004 = 0;
    fn_1_23ECC(&work->sprite[0], work->player.unk018, work->player.unk08C, 0, work);
    fn_1_23ECC(&work->sprite[1], 15, work->koopaboss.unk018, 1, work);
    work->sprite[0].unk04 = 1;
    work->sprite[1].unk04 = 0;
    HuWinInit(1);
    HuWinMesMaxSizeBetGet(&size, 0x110000, 0x110001);
    work->unk28A4 = HuWinExCreate(-10000.0f, 350.0f, size.x, size.y, -1);
    fn_1_10A4(&work->mainMdl, work);
    fn_1_2DB24();
    fn_1_2EB08();
    Hu3DBGColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    Hu3DNoSyncSet(TRUE);
    fn_1_1330(work, 0);
    m562CtrlNo = 1;
}

/* 61 insns: tear everything down */
void fn_1_FB0(M562_WORK *work)
{
    fn_1_2DB74();
    fn_1_12E0(&work->mainMdl);
    HuWinExClose(work->unk28A4);
    HuWinExKill(work->unk28A4);
    fn_1_24178(&work->sprite[0]); /* retail: sprite[1] (the Bowser gauge) is never killed */
    fn_1_17984(&work->mechakoopa);
    if (!work->unk289C) {
        fn_1_140E4(&work->fire);
        fn_1_B4F8(&work->koopa);
        fn_1_18F5C(&work->firering);
        HuMemDirectFree(work->unk2864);
        work->unk2864 = NULL;
    } else {
        fn_1_10018(&work->koopaboss);
    }
    fn_1_6FBC(&work->player);
    fn_1_5BE4(&work->stage);
    fn_1_41B4(&work->back);
    fn_1_2102C(&work->camera[1]);
    fn_1_2102C(&work->camera[0]);
    fn_1_22620(&work->light);
    if (work->unk28A0 >= 0) {
        GameMesKill(work->unk28A0);
    }
    GameMesClose();
    memset(work, 0, sizeof(M562_WORK));
    HuAudAllStop();
}

/* 143 insns */
void fn_1_10A4(M562_MAINMDL *mdl, M562_WORK *work)
{
    HU3DMODELID modelId;
    M562_WORK *w = work;
    M562_CAMERA *camera = &w->camera[0];

    memset(mdl, 0, sizeof(M562_MAINMDL));
    mdl->unk0 = work;
    mdl->unk4 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m562, 0x21), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelScaleSet(modelId, 15.0f, 15.0f, 15.0f);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    mdl->unk6 = Hu3DJointMotion(modelId, HuDataSelHeapReadNum(DATANUM(DATA_m562, 0x56), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSpeedSet(modelId, 9.16f);
    Hu3DMotionSet(modelId, mdl->unk6);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    mdl->unk8 = modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m562, 0x27), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelScaleSet(modelId, 1.0f, 1.0f, 1.0f);
    Hu3DModelPosSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(modelId, camera->unk04);
    Hu3DModelLayerSet(modelId, 5);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
}

/* 20 insns */
void fn_1_12E0(M562_MAINMDL *mdl)
{
    Hu3DModelKill(mdl->unk8);
    Hu3DMotionKill(mdl->unk6);
    Hu3DModelKill(mdl->unk4);
    memset(mdl, 0, sizeof(M562_MAINMDL));
}

/* 93 insns: per-frame update of every object; returns 1 when the phase is over */
s32 fn_1_1330(M562_WORK *work, s32 arg1)
{
    s32 result = 0;

    result = fn_1_14A4(work);
    if (result && work->unk000C == 4) {
        work->unk0022 = 0;
    }
    fn_1_22690(&work->light);
    fn_1_2105C(&work->camera[0]);
    fn_1_2105C(&work->camera[1]);
    fn_1_427C(&work->back);
    fn_1_5CAC(&work->stage);
    if (!work->unk289C) {
        fn_1_14190(&work->fire);
        fn_1_B578(&work->koopa);
        fn_1_18FC8(&work->firering);
    } else {
        fn_1_11054(&work->koopaboss);
    }
    fn_1_17A28(&work->mechakoopa);
    fn_1_7174(&work->player);
    work->sprite[0].unk2C = work->player.unk08C;
    work->sprite[1].unk2C = work->koopaboss.unk018;
    fn_1_241EC(&work->sprite[0]);
    fn_1_241EC(&work->sprite[1]);
    if (work->player.unk08C <= 0) {
        if (work->unk0024) {
            MgTimerKill(work->unk0024);
            if (!work->unk0024->stopF) {
                work->unk0024->stopF = TRUE;
                work->unk0024->mode = MGTIMER_MODE_ON;
            }
            work->unk0024 = NULL;
        }
        work->unk0022 = 1;
        result = 1;
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN && work->unk0014 != 0) {
        work->unk0014--;
    }
    work->unk0008++;
    return result;
}

/* 147 insns: has the current phase been cleared? */
s32 fn_1_14A4(M562_WORK *work)
{
    M562_FIRE *fire = &work->fire;
    M562_FIRERING *firering = &work->firering;
    M562_FIRERINGSUB *part0 = &firering->unk18[0];
    M562_FIRERINGSUB *part1 = &firering->unk18[1];
    M562_FIRERINGSUB *part2 = &firering->unk18[2];
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    s32 result = 0;
    float t;

    switch (work->unk000E) {
    case 0:
        break;
    case 1:
        if (fire->unk1100 <= 0) {
            result = 1;
        }
        break;
    case 2:
        if (firering->unk04 >= 2 && !work->unk0024) {
            work->unk0024 = MgTimerCreate(MGTIMER_TYPE_NORMAL);
            MgTimerParamSet(work->unk0024, 1800, 0, 0);
            MgTimerPosSet(work->unk0024, 525.0f, 64.0f);
        }
        if (firering->unk04 == 4) {
            if (work->unk0024) {
                MgTimerKill(work->unk0024);
                if (!work->unk0024->stopF) {
                    work->unk0024->stopF = TRUE;
                    work->unk0024->mode = MGTIMER_MODE_ON;
                }
                work->unk0024 = NULL;
            }
            if (firering->unk08 < 60) {
                if (firering->unk08 == 0 && firering->unkCC >= 0) {
                    fn_1_864(firering->unkCC, 1000);
                }
                t = firering->unk08 / 60.0f;
                part0->unk1C.y = part1->unk1C.y = part2->unk1C.y = 40.0f + 1000.0f * t;
                firering->unk08++;
            } else if (firering->unkCC >= 0) {
                fn_1_83C(firering->unkCC);
                firering->unkCC = -1;
            }
            result = 1;
        }
        break;
    case 3:
        if (koopa->mode == 3 && koopa->step >= 7) {
            result = 1;
        }
        break;
    case 4:
        if (boss->unk018 <= 0) {
            result = 1;
        }
        break;
    case 5:
        break;
    }
    return result;
}

/* 368 insns: set phase (0..3) objects up */
void fn_1_16F0(M562_WORK *work, s16 phase)
{
    M562_FIRE *fire = &work->fire;
    M562_FIRERING *firering = &work->firering;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    M562_BACK *back = &work->back;

    if (!work->unk289C && phase == 3) {
        fn_1_140E4(&work->fire);
        fn_1_B4F8(&work->koopa);
        fn_1_18F5C(&work->firering);
        HuMemDirectFree(work->unk2864);
        work->unk2864 = NULL;
        fn_1_F784(&work->koopaboss, work);
        work->unk289C = 1;
    } else if (work->unk289C && phase != 3) {
        fn_1_10018(&work->koopaboss);
        fn_1_13CFC(&work->fire, work);
        work->fire.unk0004 = 1;
        fn_1_B2E0(&work->koopa, work);
        fn_1_18E88(&work->firering, work);
        work->firering.unk10 = 0;
        Hu3DLayerHookSet(15, fn_1_508C);
        work->unk2864 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
        work->unk2868 = HuSprAnimDataRead(DATANUM(DATA_m562, 0x6D));
        work->unk289C = 0;
    }
    switch (phase) {
    case 0:
        m562CtrlNo = 1;
        fire->unk0004 = 1;
        fire->unk0008 = 0;
        firering->unk10 = 0;
        firering->unk14 = 0;
        mecha->unk004 = 0;
        koopa->dispReq = 1;
        koopa->mode = 1;
        koopa->step = 0;
        koopa->unk1C = 0;
        boss->unk010 = 0;
        boss->unk01C = 0;
        camera->unk08 = 0;
        camera->unk0A = 2;
        work->sprite[0].unk04 = 1;
        work->sprite[1].unk04 = 0;
        Hu3DModelAttrReset(back->unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk0E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk10, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk12, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk14, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk20, HU3D_ATTR_DISPOFF);
        MgSeqMaxTimeSet(60);
        break;
    case 1:
        m562CtrlNo = 2;
        fire->unk0004 = 0;
        fire->unk0008 = 0;
        firering->unk14 = 0;
        mecha->unk004 = 0;
        koopa->dispReq = 1;
        koopa->mode = 2;
        koopa->step = 0;
        koopa->unk1C = 0;
        boss->unk010 = 0;
        boss->unk01C = 0;
        camera->unk08 = 0;
        camera->unk0A = 2;
        work->sprite[0].unk04 = 1;
        work->sprite[1].unk04 = 0;
        if (work->unk0024) {
            MgTimerKill(work->unk0024);
            if (!work->unk0024->stopF) {
                work->unk0024->stopF = TRUE;
                work->unk0024->mode = MGTIMER_MODE_ON;
            }
            work->unk0024 = NULL;
        }
        Hu3DModelAttrReset(back->unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk0E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk10, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk12, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk14, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk20, HU3D_ATTR_DISPOFF);
        MgSeqMaxTimeSet(0);
        break;
    case 2:
        m562CtrlNo = 3;
        fire->unk0004 = 0;
        fire->unk0008 = 0;
        firering->unk10 = 0;
        firering->unk14 = 0;
        mecha->unk004 = 1;
        koopa->dispReq = 1;
        koopa->mode = 3;
        koopa->step = 0;
        koopa->unk1C = 0;
        boss->unk010 = 0;
        boss->unk01C = 0;
        camera->unk08 = 0;
        camera->unk0A = 2;
        work->sprite[0].unk04 = 1;
        work->sprite[1].unk04 = 0;
        Hu3DModelAttrReset(back->unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk0E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk10, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk12, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk14, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk1C, HU3D_ATTR_DISPOFF);
        MgSeqMaxTimeSet(300);
        if (work->unk0024) {
            MgTimerKill(work->unk0024);
            if (!work->unk0024->stopF) {
                work->unk0024->stopF = TRUE;
                work->unk0024->mode = MGTIMER_MODE_ON;
            }
            work->unk0024 = NULL;
        }
        break;
    case 3:
        m562CtrlNo = 4;
        fire->unk0004 = 0;
        fire->unk0008 = 0;
        firering->unk10 = 0;
        firering->unk14 = 0;
        mecha->unk004 = 1;
        koopa->dispReq = 0;
        koopa->unk1C = 0;
        boss->unk010 = 1;
        boss->unk01C = 0;
        camera->unk08 = 0;
        camera->unk0A = 3;
        work->sprite[0].unk04 = 1;
        work->sprite[1].unk04 = 1;
        Hu3DModelAttrSet(back->unk0C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk0E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk10, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk12, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(back->unk14, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk1A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk1C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(back->unk20, HU3D_ATTR_DISPOFF);
        MgSeqMaxTimeSet(300);
        break;
    }
}

/* 59 insns: switch the phase's attack objects on/off */
void fn_1_1CB0(M562_WORK *work, s16 phase, s32 flag)
{
    M562_FIRE *fire = &work->fire;
    M562_FIRERING *firering = &work->firering;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    M562_PLAYER *player = &work->player;

    switch (phase) {
    case 0:
        fire->unk0008 = flag;
        firering->unk14 = 0;
        koopa->unk1C = flag;
        boss->unk01C = 0;
        break;
    case 1:
        fire->unk0008 = 0;
        firering->unk14 = flag;
        koopa->unk1C = flag;
        boss->unk01C = 0;
        break;
    case 2:
        fire->unk0008 = 0;
        firering->unk14 = 0;
        koopa->unk1C = flag;
        boss->unk01C = 0;
        break;
    case 3:
        fire->unk0008 = 0;
        firering->unk14 = 0;
        koopa->unk1C = 0;
        boss->unk01C = flag;
        break;
    }
}

/* 110 insns: stop the phase's attacks (end of battle / loss) */
void fn_1_1D9C(M562_WORK *work)
{
    M562_FIRE *fire = &work->fire;
    M562_FIRERING *firering = &work->firering;
    M562_MECHAKOOPA *mecha = &work->mechakoopa;
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *boss = &work->koopaboss;
    M562_SUNBOMB *sunbomb = &boss->unk14C;
    M562_CAMERA *camera = &work->camera[0];
    M562_PLAYER *player = &work->player;
    M562_FIREOBJ *fireObj;
    M562_SUNBOMBOBJ *bomb;
    s32 i;

    switch (work->unk000E) {
    case 1:
        for (i = 0; i < 35; i++) {
            fireObj = &fire->unk000C[i];
            if (fireObj->unk10 < 6) {
                fn_1_162A0(fireObj);
            }
        }
        break;
    case 2:
        firering->unk04 = 4;
        break;
    case 3:
        koopa->step = 1;
        koopa->motNext = 0;
        koopa->motLoop = 1;
        break;
    case 4:
        Hu3DModelAttrSet(boss->unk136, HU3D_ATTR_DISPOFF);
        if (boss->unk124 != 1 && boss->unk124 == 2) {
            boss->unk126 = 0;
            boss->unk124 = 5;
        }
        for (i = 0; i < 5; i++) {
            bomb = &sunbomb->unk004[i];
            if (bomb->unk10 && bomb->unk04 < 4) {
                bomb->unk08 = 0;
                bomb->unk04 = 8;
            } else if (bomb->unk10 && bomb->unk04 >= 4 && bomb->unk04 < 8) {
                bomb->unk08 = 0;
                bomb->unk04 = 9;
            }
        }
        if (boss->unk3F4 >= 0) {
            fn_1_83C(boss->unk3F4);
            boss->unk3F4 = -1;
        }
        break;
    }
}

/* 56 insns: run the current event; advance to the next when it finishes */
s32 fn_1_1F54(M562_WORK *work)
{
    s32 result = 1;

    switch (work->unk0012) {
    case 0:
        result = fn_1_2446C(work);
        break;
    case 1:
        result = fn_1_252B4(work);
        break;
    case 2:
        result = fn_1_260B8(work);
        break;
    case 3:
        result = fn_1_27950(work);
        break;
    case 4:
        result = fn_1_280C8(work);
        break;
    case 5:
        result = fn_1_29DF8(work);
        break;
    }
    if (result) {
        work->unk0012++;
    }
    return result;
}

/* 106 insns: PREMAIN: switch the phase's attacks on */
s32 fn_1_2034(M562_WORK *work)
{
    M562_PLAYER *player = &work->player;
    M562_KOOPA *koopa = &work->koopa;

    player->unk088 = 1;
    player->unk004 = 1;
    switch (work->unk000E) {
    case 1:
        fn_1_1CB0(work, 0, 1);
        break;
    case 2:
        fn_1_1CB0(work, 1, 1);
        break;
    case 3:
        fn_1_1CB0(work, 2, 1);
        break;
    case 4:
        fn_1_1CB0(work, 3, 1);
        break;
    }
    work->unk0022 = 2;
    return 1;
}

/* 2 insns; = m510 fn_1_1308 */
s32 fn_1_21DC(M562_WORK *work)
{
    return 1;
}

/* 900 insns; = m510 fn_1_1338 (dead: debug-draw model hook, never installed) */
void fn_1_21E4(HU3DMODEL *modelP, Mtx *mtx)
{
    s32 i;

    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetZCompLoc(GX_FALSE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_ONE, GX_LO_NOOP);
    GXSetAlphaUpdate(GX_TRUE);
    for (i = 0; i < lbl_1_bss_8; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 2);
        GXPosition3f32(lbl_1_bss_6010[i][0].x, lbl_1_bss_6010[i][0].y, lbl_1_bss_6010[i][0].z);
        GXColor4u8(lbl_1_bss_80E[i].r, lbl_1_bss_80E[i].g, lbl_1_bss_80E[i].b, lbl_1_bss_80E[i].a);
        GXPosition3f32(lbl_1_bss_6010[i][1].x, lbl_1_bss_6010[i][1].y, lbl_1_bss_6010[i][1].z);
        GXColor4u8(lbl_1_bss_80E[i].r, lbl_1_bss_80E[i].g, lbl_1_bss_80E[i].b, lbl_1_bss_80E[i].a);
        GXEnd();
    }
    for (i = 0; i < lbl_1_bss_A; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(lbl_1_bss_3C10[i][0].x, lbl_1_bss_3C10[i][0].y, lbl_1_bss_3C10[i][0].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][1].x, lbl_1_bss_3C10[i][1].y, lbl_1_bss_3C10[i][1].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][2].x, lbl_1_bss_3C10[i][2].y, lbl_1_bss_3C10[i][2].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXPosition3f32(lbl_1_bss_3C10[i][0].x, lbl_1_bss_3C10[i][0].y, lbl_1_bss_3C10[i][0].z);
        GXColor4u8(lbl_1_bss_40E[i].r, lbl_1_bss_40E[i].g, lbl_1_bss_40E[i].b, lbl_1_bss_40E[i].a);
        GXEnd();
    }
    for (i = 0; i < lbl_1_bss_C; i++) {
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
        GXPosition3f32(lbl_1_bss_C10[i][0].x, lbl_1_bss_C10[i][0].y, lbl_1_bss_C10[i][0].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][1].x, lbl_1_bss_C10[i][1].y, lbl_1_bss_C10[i][1].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][2].x, lbl_1_bss_C10[i][2].y, lbl_1_bss_C10[i][2].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][3].x, lbl_1_bss_C10[i][3].y, lbl_1_bss_C10[i][3].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXPosition3f32(lbl_1_bss_C10[i][0].x, lbl_1_bss_C10[i][0].y, lbl_1_bss_C10[i][0].z);
        GXColor4u8(lbl_1_bss_E[i].r, lbl_1_bss_E[i].g, lbl_1_bss_E[i].b, lbl_1_bss_E[i].a);
        GXEnd();
    }
    lbl_1_bss_8 = lbl_1_bss_A = lbl_1_bss_C = 0;
}

/* 54 insns; = m510 fn_1_2148 */
void fn_1_2FF4(HuVecF *start, HuVecF *end, GXColor *color)
{
    if (lbl_1_bss_8 < 256) {
        lbl_1_bss_6010[lbl_1_bss_8][0] = *start;
        lbl_1_bss_6010[lbl_1_bss_8][1] = *end;
        lbl_1_bss_80E[lbl_1_bss_8] = *color;
        lbl_1_bss_8++;
    }
}

/* 92 insns; = m510 fn_1_2220 */
void fn_1_30CC(HuVecF *pos, float size, GXColor *color)
{
    if (lbl_1_bss_A < 256) {
        HuVecF p0;
        HuVecF p1;
        HuVecF p2;

        p0.x = pos->x;
        p0.y = pos->y;
        p0.z = pos->z - size;
        p1.x = pos->x + size;
        p1.y = pos->y;
        p1.z = pos->z + size;
        p2.x = pos->x - size;
        p2.y = pos->y;
        p2.z = pos->z + size;
        lbl_1_bss_3C10[lbl_1_bss_A][0] = p0;
        lbl_1_bss_3C10[lbl_1_bss_A][1] = p1;
        lbl_1_bss_3C10[lbl_1_bss_A][2] = p2;
        lbl_1_bss_40E[lbl_1_bss_A] = *color;
        lbl_1_bss_A++;
    }
}

/* 80 insns; = m510 fn_1_2390 */
void fn_1_323C(HuVecF *p0, HuVecF *p1, HuVecF *p2, HuVecF *p3, GXColor *color)
{
    if (lbl_1_bss_C < 256) {
        lbl_1_bss_C10[lbl_1_bss_C][0] = *p0;
        lbl_1_bss_C10[lbl_1_bss_C][1] = *p1;
        lbl_1_bss_C10[lbl_1_bss_C][2] = *p2;
        lbl_1_bss_C10[lbl_1_bss_C][3] = *p3;
        lbl_1_bss_E[lbl_1_bss_C] = *color;
        lbl_1_bss_C++;
    }
}

/* 220 insns; = m510 fn_1_24D0 */
void fn_1_337C(Quaternion *out, HuVecF *from, HuVecF *to)
{
    Quaternion q;
    HuVecF cross;
    float dot;
    float s;

    PSVECCrossProduct(from, to, &cross);
    dot = PSVECDotProduct(from, to);
    if (((dot >= 0.0f) ? dot : -dot) < 0.9999999f) {
        s = sqrtf(2.0f * (1.0f + dot));
        q.x = cross.x / s;
        q.y = cross.y / s;
        q.z = cross.z / s;
        q.w = s / 2.0f;
    } else if (dot < 0.0f) {
        q.x = 0.0f;
        q.y = 1.0f;
        q.z = 0.0f;
        q.w = 0.0f;
    } else {
        q.x = 0.0f;
        q.y = 0.0f;
        q.z = 0.0f;
        q.w = 1.0f;
    }
    *out = q;
}

/* 71 insns; = m510 fn_1_2840 */
float fn_1_36EC(float cur, float target, float rate)
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

/* --- .data after the last user --- */
/* 0x54 */ s16 lbl_1_data_54[6] = { 2, 5, 15, 8, 0, 0 };

