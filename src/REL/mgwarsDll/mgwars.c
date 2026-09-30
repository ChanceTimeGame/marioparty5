/*
 * mgwarsDll mgwars.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgwarsDll/asm/REL/mgwarsDll/mgwars.s.
 */

#include "REL/mgwarsDll.h"


/* Retail mgwars.c calls the audio API without prototypes (implicit int): no extsh on the s16
 * streamNo of HuAudSStreamPauseFadeOut, and the "void" HuAudFXStop / HuAudSStreamFadeOut results are
 * copied like int ones (fn_1_C620, fn_1_108C, fn_1_1148). Keep the header out of the CW build only. */
#ifndef __MWERKS__
#include "game/audio.h"
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const double lbl_1_rodata_10 = 180.0; /* 0x10 */
static const float lbl_1_rodata_18 = 0.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 9.0f; /* 0x1C */
static const float lbl_1_rodata_20 = 1.0f; /* 0x20 */
/* 0x28 lbl_1_rodata_28 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_30 = 40.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 20.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 6000.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 1.2f; /* 0x3C */
static const float lbl_1_rodata_40 = 640.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 480.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 192.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 100.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 256.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 180.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 64.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 24.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 320.0f; /* 0x60 */
static const double lbl_1_rodata_68 = 3.141592653589793; /* 0x68 */
static const double lbl_1_rodata_70 = 0.5; /* 0x70 */
static const float lbl_1_rodata_78 = 121.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 150.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 151.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 120.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 660.0f; /* 0x88 */
static const float lbl_1_rodata_8C = -1.0f; /* 0x8C */
static const double lbl_1_rodata_90 = 360.0; /* 0x90 */
static const float lbl_1_rodata_98 = 661.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 700.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 60.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 241.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 300.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = 0.01f; /* 0xAC */
static const float lbl_1_rodata_B0 = 15.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 10.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 5000.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = -10000.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 350.0f; /* 0xC0 */
/* 0xC4 lbl_1_rodata_C4 (0x10): fn_1_E3C8 fn_1_E450 fn_1_E4D8 fn_1_E560 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_D4 = 30.0f; /* 0xD4 */
static const double lbl_1_rodata_D8 = 900.0; /* 0xD8 */
static const float lbl_1_rodata_E0 = 45.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 240.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 61.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 181.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 2.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 28.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = -28.0f; /* 0xF8 */
static const float lbl_1_rodata_FC = 80.0f; /* 0xFC */
static const float lbl_1_rodata_100 = 90.0f; /* 0x100 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x8 */ MGWARS_WORK lbl_1_bss_8; /* lbl_1_bss_0 points here (fn_1_728C) */
/* 0x4 */ MGWARS_MODEWORK *lbl_1_bss_4; /* = (MGWARS_MODEWORK *)mgModeWork (fn_1_728C) */
/* 0x0 */ MGWARS_WORK *lbl_1_bss_0;

/* --- functions (reference order), .data placed before its first user --- */
/* 49 insns */
void fn_1_A0(s8 *arr, s32 num)
{
    s8 usednum[256];
    s32 i;
    s32 j;
    s32 no;
    for (i = num; i--;) {
        usednum[i] = arr[i];
    }
    for (i = num; i--;) {
        if (i) {
            no = frandmod(i + 1);
        } else {
            no = 0;
        }
        arr[i] = usednum[no];
        for (j = 0; j <= i; j++) {
            if (j != no && j > no) {
                usednum[j - 1] = usednum[j];
            }
        }
    }
}

/* 46 insns */
void fn_1_164(s32 *a, s32 *b, s32 num)
{
    s32 i;
    s32 j;
    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            if (a[i] > a[j]) {
                s32 temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                if (b) {
                    s32 temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }
    }
}

/* 67 insns */
s32 fn_1_21C(float *angle, float end, float speed)
{
    float change;
    float diff = *angle - end;
    change = fmodf(diff, 180.0);
    if (fabsf(change) < speed) {
        *angle = end;
        return TRUE;
    }
    if (change > 0) {
        change -= speed;
    } else {
        change += speed;
    }
    *angle = end + change;
    return FALSE;
}

/* 0x0 */ MGWARS_MG lbl_1_data_0[26] = { { DLL_m501dll, 501 }, { DLL_m502dll, 502 }, { DLL_m503dll, 503 }, { DLL_m504dll, 504 }, { DLL_m563dll, 563 }, { DLL_m564dll, 564 }, { DLL_m565dll, 565 }, { DLL_m576dll, 576 }, { DLL_m505dll, 505 }, { DLL_m506dll, 506 }, { DLL_m507dll, 507 }, { DLL_m509dll, 509 }, { DLL_m510dll, 510 }, { DLL_m579dll, 579 }, { DLL_m511dll, 511 }, { DLL_m512dll, 512 }, { DLL_m513dll, 513 }, { DLL_m514dll, 514 }, { DLL_m515dll, 515 }, { DLL_m566dll, 566 }, { DLL_m535dll, 535 }, { DLL_m536dll, 536 }, { DLL_m537dll, 537 }, { DLL_m538dll, 538 }, { DLL_m539dll, 539 }, { DLL_m540dll, 540 } };
/* 0x9C */ u32 lbl_1_data_9C[5] = { CHARMOT_HSF_c000m1_300, CHARMOT_HSF_c000m1_306, CHARMOT_HSF_c000m1_307, CHARMOT_HSF_c000m1_301, 0 }; /* CharModelMotListCreate list; [1..3] also CharMotionVoiceOnSet */
/* 0xB0 */ HuVecF lbl_1_data_B0[4] = { { -340.0f, 50.0f, -290.0f }, { 340.0f, 50.0f, -290.0f }, { -340.0f, 50.0f, 290.0f }, { 340.0f, 50.0f, 290.0f } };
/* 0xE0 */ HuVecF lbl_1_data_E0[18] = { { 0.0f, 120.0f, -290.0f }, { -440.0f, 120.0f, -220.0f }, { 240.0f, 120.0f, -220.0f }, { -440.0f, 120.0f, 350.0f }, { 240.0f, 120.0f, 350.0f }, { -230.0f, 120.0f, -150.0f }, { 180.0f, 120.0f, -150.0f }, { -440.0f, 120.0f, 200.0f }, { 130.0f, 120.0f, 380.0f }, { -200.0f, 120.0f, -220.0f }, { 200.0f, 120.0f, -220.0f }, { -200.0f, 120.0f, 350.0f }, { 200.0f, 120.0f, 350.0f }, { 0.0f, 930.0f, 0.0f }, { -440.0f, 930.0f, -220.0f }, { 240.0f, 930.0f, -220.0f }, { -440.0f, 930.0f, 350.0f }, { 240.0f, 930.0f, 350.0f } };
/* 0x1B8 */ HuVecF lbl_1_data_1B8[4] = { { -340.0f, 0.0f, -290.0f }, { 340.0f, 0.0f, -290.0f }, { -340.0f, 0.0f, 290.0f }, { 340.0f, 0.0f, 290.0f } };
/* 0x1E8 */ HuVecF lbl_1_data_1E8[19] = { { -160.0f, 0.0f, -280.0f }, { 0.0f, 0.0f, -280.0f }, { 160.0f, 0.0f, -280.0f }, { -240.0f, 0.0f, -140.0f }, { -80.0f, 0.0f, -140.0f }, { 80.0f, 0.0f, -140.0f }, { 240.0f, 0.0f, -140.0f }, { -320.0f, 0.0f, 0.0f }, { -160.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 160.0f, 0.0f, 0.0f }, { 320.0f, 0.0f, 0.0f }, { -240.0f, 0.0f, 140.0f }, { -80.0f, 0.0f, 140.0f }, { 80.0f, 0.0f, 140.0f }, { 240.0f, 0.0f, 140.0f }, { -160.0f, 0.0f, 280.0f }, { 0.0f, 0.0f, 280.0f }, { 160.0f, 0.0f, 280.0f } };
/* 0x2CC */ float lbl_1_data_2CC[3] = { 0.0f, 300.0f, -530.0f };
/* 0x2D8 */ MGWARS_PANEL lbl_1_data_2D8[19] = { /* 0xBE bytes + 2 alignment bytes before 0x398 */
    { { -1, 1, 4, 3, -1, -1 }, -1, -1, 0, 0 },
    { { -1, 2, 5, 4, 0, -1 }, -1, -1, 0, 0 },
    { { -1, -1, 6, 5, 1, -1 }, -1, -1, 0, 0 },
    { { 0, 4, 8, 7, -1, -1 }, -1, -1, 0, 0 },
    { { 1, 5, 9, 8, 3, 0 }, -1, -1, 0, 0 },
    { { 2, 6, 10, 9, 4, 1 }, -1, -1, 0, 0 },
    { { -1, -1, 11, 10, 5, 2 }, -1, -1, 0, 0 },
    { { 3, 8, 12, -1, -1, -1 }, -1, -1, 0, 0 },
    { { 4, 9, 13, 12, 7, 3 }, -1, -1, 0, 0 },
    { { 5, 10, 14, 13, 8, 4 }, -1, -1, 0, 0 },
    { { 6, 11, 15, 14, 9, 5 }, -1, -1, 0, 0 },
    { { -1, -1, -1, 15, 10, 6 }, -1, -1, 0, 0 },
    { { 8, 13, 16, -1, -1, 7 }, -1, -1, 0, 0 },
    { { 9, 14, 17, 16, 12, 8 }, -1, -1, 0, 0 },
    { { 10, 15, 18, 17, 13, 9 }, -1, -1, 0, 0 },
    { { 11, -1, -1, 18, 14, 10 }, -1, -1, 0, 0 },
    { { 13, 17, -1, -1, -1, 12 }, -1, -1, 0, 0 },
    { { 14, 18, -1, -1, 16, 13 }, -1, -1, 0, 0 },
    { { 15, -1, -1, -1, 17, 14 }, -1, -1, 0, 0 }
};
/* 0x398 */ HuVecF lbl_1_data_398[4] = { { -340.0f, 50.0f, 300.0f }, { 340.0f, 50.0f, 300.0f }, { -340.0f, 50.0f, 880.0f }, { 340.0f, 50.0f, 880.0f } };
/* 0x3C8 */ float lbl_1_data_3C8[13] = { -5.0f, -5.0f, 0.0f, -10.0f, -20.0f, -5.0f, -10.0f, 0.0f, -15.0f, -40.0f, -40.0f, -40.0f, -40.0f };
/* 0x3FC */ s32 lbl_1_data_3FC[10][7] = { /* per charNo: voice SE ids (fn_1_1778: [charNo][seNo] -> HuAudFXPlayPan) */
    { 504, 507, 512, 502, 512, 506, 504 },
    { 484, 487, 492, 482, 492, 486, 484 },
    { 604, 607, 612, 602, 612, 606, 604 },
    { 684, 687, 692, 682, 692, 686, 684 },
    { 644, 647, 652, 642, 652, 646, 644 },
    { 444, 447, 452, 442, 452, 446, 444 },
    { 664, 667, 672, 662, 672, 666, 664 },
    { 464, 467, 472, 462, 472, 466, 464 },
    { 624, 627, 632, 622, 632, 626, 624 },
    { 564, 567, 572, 562, 572, 566, 564 }
};

/* 55 insns */
void fn_1_328(void)
{
    u32 tick;
    int statId;
    lbl_1_bss_0->dirRead = FALSE;
    tick = OSGetTick();
    statId = HuDataDirReadAsync(mgDataTbl[lbl_1_bss_0->mgNoDir].dataDir);
    while (!HuDataGetAsyncStat(statId)) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->dirRead = TRUE;
    OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick() - tick));
    OSReport("Finished!\n");
    HuPrcEnd();
    while (TRUE) {
        HuPrcVSleep();
    }
}

/* 37 insns */
void fn_1_404(s32 mgNoDir)
{
    lbl_1_bss_0->mgNoDir = mgNoDir;
    HuDataDirClose(DATA_mgwars);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    if (!fn_1_684(4)) {
        HuPrcChildCreate(fn_1_328, 200, 0x3000, 0, HuPrcCurrentGet());
    } else {
        lbl_1_bss_0->dirRead = TRUE;
    }
}

/* 29 insns */
void fn_1_498(void)
{
    fn_1_C04(lbl_1_bss_0->cameraMotNext, lbl_1_bss_0->cameraMotTime, lbl_1_bss_0->cameraMotArg);
    lbl_1_bss_0->cameraMotNext = -1;
    HuPrcEnd();
}

/* 5 insns */
HUWINID fn_1_50C(void)
{
    return lbl_1_bss_0->winId;
}

/* 18 insns */
void fn_1_520(void)
{
    if (!fn_1_684(0x40)) {
        fn_1_64C(0x40);
        HuWinExOpen(lbl_1_bss_0->winId);
    }
}

/* 23 insns */
void fn_1_568(void)
{
    if (fn_1_684(0x40)) {
        fn_1_668(0x40);
        HuWinExClose(lbl_1_bss_0->winId);
        HuWinHomeClear(lbl_1_bss_0->winId);
    }
}

/* 5 insns */
s8 fn_1_5C4(void)
{
    return lbl_1_bss_0->unk8;
}

/* 5 insns */
s16 fn_1_5D8(void)
{
    return lbl_1_bss_0->unkA;
}

/* 19 insns */
s8 fn_1_5EC(s8 *out)
{
    memcpy(out, lbl_1_bss_0->unk14, 4);
    return lbl_1_bss_0->unk18;
}

/* 5 insns */
s8 fn_1_638(void)
{
    return lbl_1_bss_0->unk19;
}

/* 7 insns */
void fn_1_64C(u32 flag)
{
    lbl_1_bss_0->flag |= flag;
}

/* 7 insns */
void fn_1_668(u32 flag)
{
    lbl_1_bss_0->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_684(u32 flag)
{
    return lbl_1_bss_0->flag & flag;
}

/* 8 insns */
void fn_1_69C(u32 flag)
{
    lbl_1_bss_4->flag |= flag;
}

/* 8 insns */
void fn_1_6BC(u32 flag)
{
    lbl_1_bss_4->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_6DC(u32 flag)
{
    return lbl_1_bss_4->flag & flag;
}

/* 13 insns */
void fn_1_6F4(u32 flag)
{
    lbl_1_bss_0->flag &= ~0x10000;
    lbl_1_bss_0->mesFlag |= flag;
}

/* 30 insns */
void fn_1_728(u32 flag)
{
    while (lbl_1_bss_0->flag & 0x10000) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->flag |= 0x10000;
    lbl_1_bss_0->mesFlag &= ~flag;
}

/* 6 insns */
u32 fn_1_7A0(u32 flag)
{
    return lbl_1_bss_0->mesFlag & flag;
}

/* 17 insns */
void ObjectSetup(void)
{
    _SetFlag(FLAG_MGINST_ON);
    HuPrcChildCreate(fn_1_8C8, 200, 0x3000, 0, HuPrcCurrentGet());
}

/* 16 insns */
void fn_1_7FC(void (*func)(void))
{
    HuPrcChildCreate(func, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 35 insns */
void fn_1_83C(s16 cameraMot, float time, s32 arg)
{
    lbl_1_bss_0->cameraMotNext = cameraMot;
    lbl_1_bss_0->cameraMotTime = time;
    lbl_1_bss_0->cameraMotArg = arg;
    HuPrcChildCreate(fn_1_498, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 75 insns */
void fn_1_8C8(void)
{
    BOOL mgF;
    BOOL initF;
    BOOL runF;
    OMOVLHIS *his;
    his = omOvlHisGet(0);
    fn_1_728C();
    runF = TRUE;
    initF = FALSE;
    while (runF) {
        mgF = TRUE;
        switch (his->evtno) {
            case 0:
                fn_1_7E30();
                initF = FALSE;
                break;
            case 1:
                fn_1_8DF0();
                if (!(lbl_1_bss_0->flag & 8)) {
                    fn_1_9BC8();
                    if (lbl_1_bss_4->flag & 4U) {
                        mgF = FALSE;
                    }
                }
                break;
            case 2:
                fn_1_C620();
                mgF = FALSE;
                break;
            case 3:
                mgF = FALSE;
                runF = FALSE;
                break;
        }
        if (!initF) {
            fn_1_796C();
            initF = TRUE;
        }
        if (mgF) {
            fn_1_B614();
            fn_1_C19C();
        }
    }
    fn_1_7CC8();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_9F4(s32 time)
{
    while (time--) {
        HuPrcVSleep();
    }
}

/* 21 insns */
void fn_1_A30(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_IN, type, time);
    WipeWait();
}

/* 21 insns */
void fn_1_A84(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_OUT, type, time);
    WipeWait();
}

/* 23 insns */
void fn_1_AD8(s32 mdlId, float start, float end)
{
    Hu3DMotionStartEndSet(mdlId, start, end);
    Hu3DMotionTimeSet(mdlId, start);
}

/* 52 insns */
s32 fn_1_B34(s32 panel, s32 state)
{
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[6 + panel], HU3D_ATTR_DISPOFF);
    lbl_1_bss_0->mdlId[6 + panel] = lbl_1_bss_0->panelMdlId[panel][state];
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[6 + panel], HU3D_ATTR_DISPOFF);
    return lbl_1_bss_0->mdlId[6 + panel];
}

/* 105 insns */
s32 fn_1_C04(s32 cameraMot, s32 time, s32 arg)
{
    HSFMOTION *motion;
    HU3DMODEL *modelP;
    HU3DMOTION *motP;
    HSFDATA *hsf;
    if (lbl_1_bss_0->cameraMot == cameraMot) {
        return 0;
    }
    lbl_1_bss_0->cameraMotNext = cameraMot;
    if (time != 0) {
        CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM1, time, arg);
    } else {
        modelP = &Hu3DData[lbl_1_bss_0->mdlId[cameraMot]];
        motP = &Hu3DMotion[modelP->motId];
        hsf = motP->hsf;
        motion = hsf->motion;
        if (motion->maxTime < 9.0f) {
            CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM1, motion->maxTime, arg);
        } else {
            CamMotionEx2(lbl_1_bss_0->mdlId[cameraMot], HU3D_CAM1, 1.0f, arg);
        }
    }
    lbl_1_bss_0->cameraMotNext = -1;
    lbl_1_bss_0->cameraMot = cameraMot;
    return 1;
}

/* 57 insns */
void fn_1_DA8(void)
{
    HuVecF target;
    HuVecF up;
    HuVecF pos;
    Hu3DCameraPosGet(HU3D_CAM1, &pos, &up, &target);
    pos.z -= 40.0f;
    Hu3DModelPosSetV(lbl_1_bss_0->mdlId[59], &pos);
    while (lbl_1_bss_0->flag & 0x100) {
        if (lbl_1_bss_0->cameraMotNext >= 0) {
            Hu3DCameraPosGet(HU3D_CAM1, &pos, &up, &target);
            pos.z -= 40.0f;
            Hu3DModelPosSetV(lbl_1_bss_0->mdlId[59], &pos);
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 34 insns */
void fn_1_E8C(void)
{
    lbl_1_bss_0->flag |= 0x100;
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[59], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[59], HU3D_ATTR_DISPOFF);
    HuPrcChildCreate(fn_1_DA8, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 32 insns */
void fn_1_F14(void)
{
    s32 time1;
    s32 time2;
    time1 = 120;
    while (time1--) {
        HuPrcVSleep();
    }
    HuAudJinglePlay(134);
    time2 = 150;
    while (time2--) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->streamNo = HuAudBGMPlay(82);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_F94(void)
{
    HuPrcChildCreate(fn_1_F14, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 32 insns */
void fn_1_FD0(void)
{
    s32 time1;
    s32 time2;
    time1 = 120;
    while (time1--) {
        HuPrcVSleep();
    }
    HuAudJinglePlay(128);
    time2 = 150;
    while (time2--) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->streamNo = HuAudBGMPlay(82);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_1050(void)
{
    HuPrcChildCreate(fn_1_FD0, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 32 insns */
void fn_1_108C(void)
{
    s32 time;
    HuAudSStreamPauseFadeOut(lbl_1_bss_0->streamNo, TRUE, 100);
    HuAudJinglePlay(136);
    time = 280;
    while (time--) {
        HuPrcVSleep();
    }
    HuAudSStreamPauseFadeOut(lbl_1_bss_0->streamNo, FALSE, 1000);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_110C(void)
{
    HuPrcChildCreate(fn_1_108C, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 25 insns */
void fn_1_1148(void)
{
    s32 time;
    HuAudJinglePlay(129);
    time = 300;
    while (time--) {
        HuPrcVSleep();
    }
    HuAudSStreamPauseFadeOut(lbl_1_bss_0->streamNo, FALSE, 1000);
    HuPrcEnd();
}

/* 15 insns */
void fn_1_11AC(void)
{
    HuPrcChildCreate(fn_1_1148, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 49 insns */
void fn_1_11E8(s16 layerNo)
{
    if (Hu3DCameraBit == HU3D_CAM0) {
        Hu3DFbCopyExec(lbl_1_bss_0->fbCopyX, lbl_1_bss_0->fbCopyY, lbl_1_bss_0->fbCopyW, lbl_1_bss_0->fbCopyH, GX_TF_RGB5A3, FALSE,
            lbl_1_bss_0->fbCopyAnim->bmp->data);
    }
}

/* 84 insns */
void fn_1_12AC(s32 cam)
{
    s32 i;
    Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_0->camPos[cam].x, lbl_1_bss_0->camPos[cam].y, lbl_1_bss_0->camPos[cam].z, 0.0f, 1.0f, 0.0f,
        lbl_1_bss_0->camTarget[cam].x, lbl_1_bss_0->camTarget[cam].y, lbl_1_bss_0->camTarget[cam].z);
    for (i = 4; i--;) {
        if (i == cam) {
            Hu3DModelCameraSet(lbl_1_bss_0->player[i].mdlId, HU3D_CAM0 | HU3D_CAM1);
        } else {
            Hu3DModelCameraSet(lbl_1_bss_0->player[i].mdlId, HU3D_CAM1);
        }
    }
}

/* 223 insns */
void fn_1_13FC(void)
{
    s32 i;
    Hu3DCameraCreate(HU3D_CAM0);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 20.0f, 20.0f, 6000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM0, 0, 0, 640, 480);
    lbl_1_bss_0->fbCopyX = 192.0f;
    lbl_1_bss_0->fbCopyY = 100.0f;
    lbl_1_bss_0->fbCopyW = 256.0f;
    lbl_1_bss_0->fbCopyH = 256.0f;
    Hu3DZClearLayerSet(7 + HU3D_LAYER_HOOK_POST);
    if (!lbl_1_bss_0->fbCopyAnim) {
        lbl_1_bss_0->fbCopyAnim = HuSprAnimMake(256, 256, ANIM_BMP_RGB5A3);
        lbl_1_bss_0->fbCopyAnim->bmp->data = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_0->fbCopyAnim->bmp->dataSize, HU_MEMNUM_OVL);
        memset(lbl_1_bss_0->fbCopyAnim->bmp->data, 0, lbl_1_bss_0->fbCopyAnim->bmp->dataSize);
    }
    Hu3DLayerHookSet(6, fn_1_11E8);
    Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_0->camPos[0].x, lbl_1_bss_0->camPos[0].y, lbl_1_bss_0->camPos[0].z, 0.0f, 1.0f, 0.0f,
        lbl_1_bss_0->camTarget[0].x, lbl_1_bss_0->camTarget[0].y, lbl_1_bss_0->camTarget[0].z);
    for (i = 4; i--;) {
        if (i == 0) {
            Hu3DModelCameraSet(lbl_1_bss_0->player[i].mdlId, HU3D_CAM0 | HU3D_CAM1);
        } else {
            Hu3DModelCameraSet(lbl_1_bss_0->player[i].mdlId, HU3D_CAM1);
        }
    }
    HuPrcVSleep();
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[57], HU3D_ATTR_DISPOFF);
    if (lbl_1_bss_0->animId >= 0) {
        Hu3DAnimKill(lbl_1_bss_0->animId);
    }
    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->fbCopyAnim, lbl_1_bss_0->mdlId[57], "mg_shot");
}

/* 45 insns */
void fn_1_1778(MGWARS_PLAYER *player, s32 seNo)
{
    switch (player->no) {
        case 0:
        case 2:
            HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][seNo], 40);
            break;
        case 1:
        case 3:
            HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][seNo], 88);
            break;
    }
}

/* 28 insns */
void fn_1_182C(void)
{
    while (lbl_1_bss_0->seTime--) {
        HuPrcVSleep();
    }
    HuAudFXStop(lbl_1_bss_0->seNo);
    lbl_1_bss_0->seNo = -1;
    HuPrcEnd();
}

/* 48 insns */
void fn_1_189C(s32 seNo, s32 time)
{
    if (lbl_1_bss_0->seNo >= 0) {
        HuAudFXStop(lbl_1_bss_0->seNo);
        HuPrcKill(lbl_1_bss_0->seProc);
    }
    lbl_1_bss_0->seNo = HuAudFXPlay(seNo);
    lbl_1_bss_0->seTime = time;
    lbl_1_bss_0->seProc = HuPrcChildCreate(fn_1_182C, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 73 insns */
void fn_1_195C(void)
{
    Hu3DCameraKill(HU3D_CAM0);
    Hu3DLayerHookSet(7 + HU3D_LAYER_HOOK_POST, NULL);
    Hu3DLayerHookSet(6, NULL);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[57], HU3D_ATTR_DISPOFF);
    if (lbl_1_bss_0->mgIcon[lbl_1_bss_0->mgNum / 2] != 0) {
        if (lbl_1_bss_0->animId >= 0) {
            Hu3DAnimKill(lbl_1_bss_0->animId);
        }
        lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[lbl_1_bss_0->mgNum / 2], lbl_1_bss_0->mdlId[57], "mg_shot");
    }
}

/* 1322 insns */
void fn_1_1A80(void)
{
    s32 i;
    s32 mdlId;
    HSFMOTION *motion;
    s32 j;
    s32 motMdlId;
    HSFDATA *hsf;
    HU3DMOTION *motP;
    HU3DMODEL *modelP;

    lbl_1_bss_0->mdlId[0] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x02));
    lbl_1_bss_0->mdlId[1] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x03));
    lbl_1_bss_0->mdlId[2] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x04));
    lbl_1_bss_0->mdlId[3] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x05));
    lbl_1_bss_0->mdlId[52] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0B));
    lbl_1_bss_0->mdlId[53] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0C));
    lbl_1_bss_0->mdlId[54] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0D));
    lbl_1_bss_0->mdlId[55] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0E));
    lbl_1_bss_0->mdlId[56] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0F));
    lbl_1_bss_0->mdlId[57] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x0A));
    lbl_1_bss_0->mdlId[64] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x17));
    lbl_1_bss_0->mdlId[59] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x12));
    lbl_1_bss_0->mdlId[60] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x13));
    lbl_1_bss_0->mdlId[61] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x14));
    lbl_1_bss_0->mdlId[62] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x15));
    lbl_1_bss_0->mdlId[63] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x16));
    lbl_1_bss_0->mdlId[5] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x08));
    lbl_1_bss_0->mdlId[44] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1D));
    lbl_1_bss_0->mdlId[45] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1E));
    lbl_1_bss_0->mdlId[46] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1F));
    lbl_1_bss_0->mdlId[47] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x20));
    switch (GwCommon.languageNo) {
        case 0:
            lbl_1_bss_0->mdlId[58] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x10));
            lbl_1_bss_0->mdlId[4] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x06));
            lbl_1_bss_0->mdlId[65] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x07));
            break;
        case 1:
            lbl_1_bss_0->mdlId[58] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x3D));
            lbl_1_bss_0->mdlId[4] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x3E));
            lbl_1_bss_0->mdlId[65] = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x3F));
            break;
    }
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[0], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[1], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[2], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[3], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[4], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[5], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[57], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[58], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[64], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[65], 0);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[59], 1);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[60], 7);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[61], 4);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[62], 4);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[63], 4);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[44], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[45], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[46], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[47], 2);
    Hu3DModelLayerSet(lbl_1_bss_0->mdlId[56], 3);
    Hu3DModelLightInfoSet(lbl_1_bss_0->mdlId[0], 1);
    lbl_1_bss_0->unk3A4 = lbl_1_data_1E8[9];
    Hu3DModelPosSet(lbl_1_bss_0->mdlId[57], lbl_1_data_2CC[0], lbl_1_data_2CC[1], lbl_1_data_2CC[2]);
    Hu3DModelPosSet(lbl_1_bss_0->mdlId[56], lbl_1_bss_0->unk3A4.x, 20.0f + lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[3], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[56], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[56], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[57], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[57], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[58], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[58], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[64], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[64], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[65], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[65], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[59], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[59], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[60], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[61], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[61], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[62], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[62], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[63], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[63], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[44], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[45], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[46], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[47], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    motMdlId = lbl_1_bss_0->mdlId[3];
    Hu3DMotionStartEndSet(motMdlId, 0.0f, 180.0f);
    Hu3DMotionTimeSet(motMdlId, 0.0f);
    lbl_1_bss_0->mdlId[66] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x21)), 2);
    lbl_1_bss_0->mdlId[67] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x22)), 2);
    lbl_1_bss_0->mdlId[68] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x23)), 2);
    lbl_1_bss_0->mdlId[69] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x24)), 2);
    lbl_1_bss_0->mdlId[70] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x25)), 2);
    lbl_1_bss_0->mdlId[71] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x26)), 2);
    lbl_1_bss_0->mdlId[72] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x27)), 2);
    lbl_1_bss_0->mdlId[73] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x28)), 2);
    lbl_1_bss_0->mdlId[74] = Hu3DModelCameraCreate(Hu3DMotionCreateData(DATANUM(DATA_mgwars, 0x29)), 2);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[66], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[67], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[68], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[69], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[70], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[71], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[72], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[73], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[74], HU3D_MOTATTR_PAUSE);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[66]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[67]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[68]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[69]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[70]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[71]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[72]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[73]);
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[74]);
    if (lbl_1_bss_0->cameraMot != 66) {
        lbl_1_bss_0->cameraMotNext = 66;
        modelP = &Hu3DData[lbl_1_bss_0->mdlId[66]];
        motP = &Hu3DMotion[modelP->motId];
        hsf = motP->hsf;
        motion = hsf->motion;
        if (motion->maxTime < 9.0f) {
            CamMotionEx2(lbl_1_bss_0->mdlId[66], 2, motion->maxTime, 2);
        } else {
            CamMotionEx2(lbl_1_bss_0->mdlId[66], 2, 1.0f, 2);
        }
        lbl_1_bss_0->cameraMotNext = -1;
        lbl_1_bss_0->cameraMot = 66;
    }
    i = 4;
    while (i--) {
        mdlId = lbl_1_bss_0->mdlId[52 + i];
        Hu3DModelPosSet(mdlId, lbl_1_bss_0->unk3A4.x, lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
        Hu3DModelLayerSet(mdlId, 1);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 19; i++) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x19));
        lbl_1_bss_0->panelMdlId[i][0] = mdlId;
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1A));
        lbl_1_bss_0->panelMdlId[i][1] = mdlId;
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1B));
        lbl_1_bss_0->panelMdlId[i][2] = mdlId;
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x1C));
        lbl_1_bss_0->panelMdlId[i][3] = mdlId;
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x18));
        lbl_1_bss_0->panelMdlId[i][4] = mdlId;
        lbl_1_bss_0->mdlId[6 + i] = lbl_1_bss_0->panelMdlId[i][0];
        j = 5;
        while (j--) {
            mdlId = lbl_1_bss_0->panelMdlId[i][j];
            Hu3DModelPosSet(mdlId, lbl_1_data_1E8[i].x, lbl_1_data_1E8[i].y, lbl_1_data_1E8[i].z);
            Hu3DModelLayerSet(mdlId, 2);
            Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[6 + i], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 19; i++) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x11));
        lbl_1_bss_0->mdlId[25 + i] = mdlId;
        Hu3DModelPosSet(mdlId, lbl_1_data_1E8[i].x, lbl_1_data_1E8[i].y, lbl_1_data_1E8[i].z);
        Hu3DModelLayerSet(mdlId, 2);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    for (i = 0; i < 4; i++) {
        mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0x09));
        lbl_1_bss_0->mdlId[48 + i] = mdlId;
        Hu3DModelPosSet(mdlId, lbl_1_data_1B8[i].x, lbl_1_data_1B8[i].y, lbl_1_data_1B8[i].z);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    }
    i = 75;
    while (i--) {
        switch (i) {
            case 2:
            case 3:
                Hu3DModelCameraSet(lbl_1_bss_0->mdlId[i], 3);
                break;
            default:
                Hu3DModelCameraSet(lbl_1_bss_0->mdlId[i], 2);
                break;
        }
    }
}

/* 332 insns */
s32 fn_1_2F28(s32 panel, s32 owner, s32 dir)
{
    s32 num;
    if (panel < 0) {
        return 0;
    }
    if (lbl_1_data_2D8[panel].owner < 0) {
        return 0;
    }
    if (owner == lbl_1_data_2D8[panel].owner) {
        return 1;
    }
    num = fn_1_2F28(lbl_1_data_2D8[panel].link[dir], owner, dir);
    if (num) {
        lbl_1_data_2D8[panel].unk7 = owner;
        return num + 1;
    } else {
        return 0;
    }
}

/* 41 insns */
s32 fn_1_3458(s32 panel, s32 owner)
{
    s32 dir;
    s32 num;
    s32 n;
    lbl_1_data_2D8[panel].unk7 = owner;
    num = 0;
    for (dir = 6; dir--;) {
        n = fn_1_2F28(lbl_1_data_2D8[panel].link[dir], owner, dir);
        if (n != 0) {
            num += n - 1;
        }
    }
    return num;
}

/* 22 insns */
s32 fn_1_34FC(s32 panel)
{
    if (panel < 0) {
        return 0;
    }
    if (lbl_1_data_2D8[panel].owner >= 0) {
        return 1;
    }
    lbl_1_data_2D8[panel].unk8 = 1;
    return 0;
}

/* 160 insns */
void fn_1_3554(s32 panel)
{
    if (panel < 0 || lbl_1_data_2D8[panel].unk9) {
        return;
    }
    lbl_1_data_2D8[panel].unk9 = 1;
    fn_1_34FC(lbl_1_data_2D8[panel].link[0]);
    fn_1_34FC(lbl_1_data_2D8[panel].link[1]);
    fn_1_34FC(lbl_1_data_2D8[panel].link[2]);
    fn_1_34FC(lbl_1_data_2D8[panel].link[3]);
    fn_1_34FC(lbl_1_data_2D8[panel].link[4]);
    fn_1_34FC(lbl_1_data_2D8[panel].link[5]);
}

/* 199 insns */
void fn_1_37D4(void)
{
    s32 i;
    i = 19;
    while (i--) {
        lbl_1_data_2D8[i].unk9 = 0;
        lbl_1_data_2D8[i].unk8 = 0;
    }
    if (lbl_1_data_2D8[9].owner < 0) {
        lbl_1_data_2D8[9].unk8 = 1;
    }
    i = 19;
    while (i--) {
        if (lbl_1_data_2D8[i].owner >= 0) {
            fn_1_3554(i);
        }
    }
}

/* 146 insns */
void fn_1_3AF0(s32 panel)
{
    s32 i;
    HU3DMODELID mdlId;
    int pan;
    float t;
    HuVecF ofs;
    HuVecF dir;
    HuVecF pos;
    mdlId = lbl_1_bss_0->unk352;
    PSVECSubtract(&lbl_1_data_1E8[panel], &lbl_1_bss_0->unk3A4, &dir);
    pan = 64.0f + 24.0f * (lbl_1_data_1E8[panel].x / 320.0f);
    HuAudFXPlayPan(1213, pan);
    for (i = 0; i < 20; i++) {
        t = i / 20.0f;
        t = sin(M_PI * t / 2);
        t = sin(M_PI * t / 2);
        t = sin(M_PI * t / 2);
        PSVECScale(&dir, &ofs, t);
        PSVECAdd(&lbl_1_bss_0->unk3A4, &ofs, &pos);
        Hu3DModelPosSet(mdlId, pos.x, pos.y, pos.z);
        HuPrcVSleep();
    }
    PSVECAdd(&lbl_1_bss_0->unk3A4, &dir, &lbl_1_bss_0->unk3A4);
    Hu3DModelPosSet(mdlId, lbl_1_bss_0->unk3A4.x, lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
}

/* 270 insns */
void fn_1_3D38(s32 panel, s32 dest)
{
    MGWARS_PANEL *p;
    BOOL found;
    s32 link;
    s8 dir;
    float dist;
    float minDist;
    s32 best;
    HuVecF d;
    p = &lbl_1_data_2D8[panel];
    if (panel == dest) {
        p->unk9 = 1;
        return;
    }
    found = FALSE;
    dir = 6;
    while (dir--) {
        link = p->link[dir];
        if (link >= 0) {
            PSVECSubtract(&lbl_1_data_1E8[link], &lbl_1_data_1E8[dest], &d);
            dist = PSVECSquareMag(&d);
            if (!found || dist < minDist) {
                minDist = dist;
                best = link;
                found = TRUE;
            }
        }
    }
    fn_1_3D38(best, dest);
    p->unk9 = 1;
}

/* 241 insns */
void fn_1_4170(s32 panel)
{
    s32 i;
    MGWARS_PANEL *p;
    s32 cur;
    HU3DMODELID mdlId;
    int pan;
    mdlId = lbl_1_bss_0->mdlId[56];
    if (panel == 9) {
        return;
    }
    i = 19;
    while (i--) {
        lbl_1_data_2D8[i].unk9 = 0;
    }
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    fn_1_3D38(9, panel);
    cur = 9;
    while (cur != panel) {
        p = &lbl_1_data_2D8[cur];
        p->unk9 = 0;
        i = 6;
        while (i--) {
            if (p->link[i] >= 0 && lbl_1_data_2D8[p->link[i]].unk9 != 0) {
                cur = p->link[i];
                break;
            }
        }
        fn_1_3AF0(cur);
    }
    pan = 64.0f + 24.0f * (lbl_1_data_1E8[panel].x / 320.0f);
    HuAudFXPlayPan(1214, pan);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(mdlId, lbl_1_bss_0->unk3A4.x, 20.0f + lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
}

/* 265 insns */
void fn_1_4534(s32 panel, s32 state)
{
    HU3DMODELID mdlId;
    int pan;
    mdlId = lbl_1_bss_0->mdlId[panel + 6];
    switch (lbl_1_bss_0->unk32C[panel]) {
        case 0:
            Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
            lbl_1_bss_0->unk32C[panel] = 1;
            break;
        case 1:
            Hu3DMotionStartEndSet(mdlId, 121.0f, 150.0f);
            Hu3DMotionTimeSet(mdlId, 121.0f);
            Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
            lbl_1_bss_0->unk32C[panel] = 2;
            break;
        case 2:
            if (Hu3DMotionEndCheck(mdlId)) {
                pan = 64.0f + 24.0f * (lbl_1_data_1E8[panel].x / 320.0f);
                HuAudFXPlayPan(1215, pan);
                mdlId = fn_1_B34(panel, state);
                Hu3DMotionStartEndSet(mdlId, 151.0f, 180.0f);
                Hu3DMotionTimeSet(mdlId, 151.0f);
                Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
                lbl_1_bss_0->unk32C[panel] = 3;
                if (lbl_1_data_2D8[panel].owner >= 0) {
                    fn_1_F828(lbl_1_data_2D8[panel].owner);
                }
                if (lbl_1_data_2D8[panel].unk7 >= 0) {
                    fn_1_F808(lbl_1_data_2D8[panel].unk7);
                    switch (lbl_1_data_2D8[panel].unk7) {
                        case 0:
                        case 2:
                            HuAudFXPlayPan(1216, 40);
                            break;
                        case 1:
                        case 3:
                            HuAudFXPlayPan(1217, 88);
                            break;
                    }
                }
            }
            break;
        case 3:
            if (Hu3DMotionEndCheck(mdlId)) {
                Hu3DMotionStartEndSet(mdlId, 0.0f, 120.0f);
                Hu3DMotionTimeSet(mdlId, 0.0f);
                Hu3DMotionTimeSet(mdlId, lbl_1_bss_0->unk36C);
                Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
                lbl_1_bss_0->unk32C[panel] = 4;
            }
            break;
        case 4:
            break;
    }
}

/* 155 insns */
void fn_1_4958(void)
{
    s32 panel;
    HU3DMODELID mdlId;

    fn_1_AD8(lbl_1_bss_0->mdlId[2], 0.0f, 660.0f);
    panel = 19;
    while (panel--) {
        if (lbl_1_bss_4->panelOwner[panel] < 0) {
            mdlId = fn_1_B34(panel, 4);
        } else {
            mdlId = fn_1_B34(panel, lbl_1_bss_4->panelOwner[panel]);
        }
        fn_1_AD8(mdlId, 0.0f, 120.0f);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        lbl_1_bss_0->unk32C[panel] = 4;
    }
}

/* 180 insns */
void fn_1_4BC4(void)
{
    s32 i;
    s32 no;
    s32 camNo;
    s32 j;
    s8 order[4];
    i = 4;
    while (i--) {
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[44 + i], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[44 + i], Hu3DMotionMaxTimeGet(lbl_1_bss_0->mdlId[44 + i]));
        order[i] = i;
    }
    no = 0;
    while (lbl_1_bss_0->flag & 0x400) {
        HuAudFXPlay(1208);
        i = 5;
        while (i--) {
            if (!(lbl_1_bss_0->flag & 0x400)) {
                break;
            }
            HuPrcVSleep();
        }
        camNo = order[no];
        Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_0->camPos[camNo].x, lbl_1_bss_0->camPos[camNo].y, lbl_1_bss_0->camPos[camNo].z, 0.0f, 1.0f, 0.0f,
            lbl_1_bss_0->camTarget[camNo].x, lbl_1_bss_0->camTarget[camNo].y, lbl_1_bss_0->camTarget[camNo].z);
        j = 4;
        while (j--) {
            if (j == camNo) {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM0 | HU3D_CAM1);
            } else {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM1);
            }
        }
        if (Hu3DMotionEndCheck(lbl_1_bss_0->mdlId[44 + order[no]])) {
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[44 + order[no]], 0.0f);
        }
        no++;
        if (no == 4) {
            no = 0;
        }
    }
    HuPrcEnd();
}

/* 21 insns */
void fn_1_4E94(void)
{
    lbl_1_bss_0->flag |= 0x400;
    HuPrcChildCreate(fn_1_4BC4, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 125 insns */
void fn_1_4EE8(void)
{
    s32 camNo;
    s32 no;
    s32 j;
    s32 time;
    no = 0;
    while (lbl_1_bss_0->flag & 0x800) {
        camNo = lbl_1_bss_0->unk14[no];
        Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_0->camPos[camNo].x, lbl_1_bss_0->camPos[camNo].y, lbl_1_bss_0->camPos[camNo].z, 0.0f, 1.0f, 0.0f,
            lbl_1_bss_0->camTarget[camNo].x, lbl_1_bss_0->camTarget[camNo].y, lbl_1_bss_0->camTarget[camNo].z);
        j = 4;
        while (j--) {
            if (j == camNo) {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM0 | HU3D_CAM1);
            } else {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM1);
            }
        }
        time = 120;
        while (time--) {
            if (!(lbl_1_bss_0->flag & 0x800)) {
                break;
            }
            HuPrcVSleep();
        }
        no++;
        if (no == lbl_1_bss_0->unk18) {
            no = 0;
        }
    }
    HuPrcEnd();
}

/* 21 insns */
void fn_1_50DC(void)
{
    lbl_1_bss_0->flag |= 0x800;
    HuPrcChildCreate(fn_1_4EE8, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 420 insns */
void fn_1_5130(void)
{
    s32 i;
    s32 time;
    s32 endTime;
    float t;
    float s;
    HuVecF points[4];
    float vals[4];
    float times[4];
    HuVecF diff;
    HuVecF ofs;
    if (lbl_1_bss_0->guideMidTime != 0) {
        endTime = lbl_1_bss_0->guideTime + lbl_1_bss_0->guideMidTime;
        points[0] = lbl_1_bss_0->guideStart;
        points[1] = lbl_1_bss_0->guideStart;
        points[2] = lbl_1_bss_0->guideMid;
        points[3] = lbl_1_bss_0->guideEnd;
        times[0] = -1.0f;
        times[1] = 0.0f;
        times[2] = lbl_1_bss_0->guideTime;
        times[3] = endTime;
        for (time = 0;; time++) {
            t = time;
            if (endTime == time) {
                lbl_1_bss_0->guidePos = lbl_1_bss_0->guideEnd;
                break;
            }
            if (lbl_1_bss_0->guideTime == time) {
                points[0] = lbl_1_bss_0->guideStart;
                points[1] = lbl_1_bss_0->guideMid;
                points[2] = lbl_1_bss_0->guideEnd;
                points[3] = lbl_1_bss_0->guideEnd;
                times[0] = 0.0f;
                times[1] = lbl_1_bss_0->guideTime;
                times[2] = endTime;
                times[3] = endTime + 1;
            }
            i = 4;
            while (i--) {
                vals[i] = points[i].x;
            }
            lbl_1_bss_0->guidePos.x = InterpolateBMLine(vals, times, t);
            i = 4;
            while (i--) {
                vals[i] = points[i].y;
            }
            lbl_1_bss_0->guidePos.y = InterpolateBMLine(vals, times, t);
            i = 4;
            while (i--) {
                vals[i] = points[i].z;
            }
            lbl_1_bss_0->guidePos.z = InterpolateBMLine(vals, times, t);
            Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
            HuPrcVSleep();
        }
    } else {
        for (time = 0;; time++) {
            t = time;
            if (lbl_1_bss_0->guideTime == time) {
                lbl_1_bss_0->guidePos = lbl_1_bss_0->guideMid;
                break;
            }
            s = t / lbl_1_bss_0->guideTime;
            s = sin(3.141592653589793 * s / 2.0);
            s = sin(3.141592653589793 * s / 2.0);
            PSVECSubtract(&lbl_1_bss_0->guideMid, &lbl_1_bss_0->guideStart, &diff);
            PSVECScale(&diff, &ofs, s);
            PSVECAdd(&lbl_1_bss_0->guideStart, &ofs, &lbl_1_bss_0->guidePos);
            Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
            HuPrcVSleep();
        }
    }
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
    lbl_1_bss_0->flag |= 0x200;
    HuPrcEnd();
}

/* 239 insns */
void fn_1_57C0(s32 posNo, s32 time)
{
    s32 midTime;
    HuVecF mid;
    if (posNo < 18) {
        lbl_1_bss_0->flag &= ~0x200;
        if (time != 0) {
            midTime = 0;
            switch (lbl_1_bss_0->guidePosNo) {
                case 1:
                    mid = lbl_1_data_E0[5];
                    midTime = time * 2 / 3;
                    break;
                case 2:
                    mid = lbl_1_data_E0[6];
                    midTime = time * 2 / 3;
                    break;
                case 3:
                    mid = lbl_1_data_E0[7];
                    midTime = time * 2 / 3;
                    break;
            }
            switch (posNo) {
                case 1:
                    mid = lbl_1_data_E0[5];
                    midTime = time * 2 / 3;
                    break;
                case 2:
                    break;
                case 3:
                    mid = lbl_1_data_E0[7];
                    midTime = time * 70 / 105;
                    break;
            }
            if (time < midTime) {
                OSReport("\225\342\212\324\202\252\217\343\216\350\202\255\202\242\202\253\202\334\202\271\202\361\201I\201I\n");
                abort();
            }
            if (midTime != 0) {
                lbl_1_bss_0->guideEnd = lbl_1_data_E0[posNo];
                lbl_1_bss_0->guideMid = mid;
            } else {
                lbl_1_bss_0->guideMid = lbl_1_data_E0[posNo];
            }
            lbl_1_bss_0->guideMidTime = midTime;
            lbl_1_bss_0->guideStart = lbl_1_bss_0->guidePos;
            lbl_1_bss_0->guideTime = time - midTime;
            HuPrcChildCreate(fn_1_5130, 100, 0x1000, 0, HuPrcCurrentGet());
        } else {
            lbl_1_bss_0->guidePos = lbl_1_data_E0[posNo];
            Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
            lbl_1_bss_0->flag |= 0x200;
        }
        lbl_1_bss_0->guidePosNo = posNo;
    }
}

/* 205 insns */
void fn_1_5B7C(void)
{
    s32 time;
    float s;
    float t;
    HuVecF diff;
    HuVecF ofs;
    for (time = 0;; time++) {
        t = time;
        if (lbl_1_bss_0->guideTime == time) {
            break;
        }
        lbl_1_bss_0->guideRotY = fmodf(lbl_1_bss_0->guideRotY - 20.0f, 360.0f);
        s = t / lbl_1_bss_0->guideTime;
        s = sin(3.141592653589793 * s / 2.0);
        PSVECSubtract(&lbl_1_bss_0->guideMid, &lbl_1_bss_0->guideStart, &diff);
        PSVECScale(&diff, &ofs, s);
        PSVECAdd(&lbl_1_bss_0->guideStart, &ofs, &lbl_1_bss_0->guidePos);
        Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
        Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, lbl_1_bss_0->guideRotY, 0.0f);
        HuPrcVSleep();
    }
    lbl_1_bss_0->guidePos = lbl_1_bss_0->guideMid;
    lbl_1_bss_0->guideRotY = 0.0f;
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guidePos.x, lbl_1_bss_0->guidePos.y, lbl_1_bss_0->guidePos.z);
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, lbl_1_bss_0->guideRotY, 0.0f);
    lbl_1_bss_0->flag |= 0x200;
    HuPrcEnd();
}

/* 110 insns */
void fn_1_5EB0(HuVecF pos, float rotY)
{
    float rot;

    lbl_1_bss_0->flag &= ~0x200;
    lbl_1_bss_0->guideStart = pos;
    lbl_1_bss_0->guideMid = pos;
    lbl_1_bss_0->guideMid.y = 120.0f;
    rot = fmod(20.0f * rotY, 360.0);
    lbl_1_bss_0->guideRotY = rot;
    lbl_1_bss_0->guideTime = rotY;
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_bss_0->guideMid.x, lbl_1_bss_0->guideMid.y, lbl_1_bss_0->guideMid.z);
    Hu3DModelRotSet(lbl_1_bss_0->guideMdlId, 0.0f, lbl_1_bss_0->guideRotY, 0.0f);
    HuPrcChildCreate(fn_1_5B7C, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 50 insns */
void fn_1_6068(void)
{
    while (TRUE) {
        if (Hu3DMotionEndCheck(lbl_1_bss_0->mdlId[2])) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    fn_1_AD8(lbl_1_bss_0->mdlId[2], 0.0f, 660.0f);
    HuPrcEnd();
}

/* 41 insns */
void fn_1_6130(void)
{
    fn_1_AD8(lbl_1_bss_0->mdlId[2], 661.0f, 700.0f);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    HuPrcChildCreate(fn_1_6068, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 81 insns */
void fn_1_61D4(void)
{
    s32 time;
    float tpLvl;
    time = 60;
    while (TRUE) {
        if (Hu3DMotionEndCheck(lbl_1_bss_0->unk352)) {
            break;
        }
        HuPrcVSleep();
    }
    while (time--) {
        tpLvl = time / 60.0f;
        Hu3DModelTPLvlSet(lbl_1_bss_0->unk352, tpLvl);
        Hu3DModelTPLvlSet(lbl_1_bss_0->mdlId[56], tpLvl);
        HuPrcVSleep();
    }
    Hu3DModelTPLvlSet(lbl_1_bss_0->unk352, 1.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_0->mdlId[56], 1.0f);
    Hu3DModelAttrSet(lbl_1_bss_0->unk352, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[56], HU3D_ATTR_DISPOFF);
    HuPrcEnd();
}

/* 75 insns */
void fn_1_6318(void)
{
    fn_1_AD8(lbl_1_bss_0->unk352, 241.0f, 300.0f);
    Hu3DModelAttrReset(lbl_1_bss_0->unk352, HU3D_MOTATTR_LOOP);
    fn_1_AD8(lbl_1_bss_0->mdlId[2], 661.0f, 700.0f);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    HuPrcChildCreate(fn_1_6068, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_61D4, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 372 insns */
void fn_1_6444(void)
{
    HuVecF dir;
    HuVecF vec;
    MGWARS_PLAYER *player;
    s32 i;
    s32 doneNum;
    float rotEnd;

    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        switch (lbl_1_bss_0->playerRotMode) {
            case 0:
                player->rotEnd = 0;
                break;
            case 1:
                VECScale(&lbl_1_data_B0[i], &vec, -1.0f);
                VECNormalize(&vec, &dir);
                if (dir.z > 1) {
                    dir.z = 1;
                }
                else if (dir.z < -1) {
                    dir.z = -1;
                }
                rotEnd = acosf(dir.z);
                if (dir.x < 0) {
                    rotEnd = -rotEnd;
                }
                player->rotEnd = (180 * rotEnd) / M_PI;
                break;
            case 2:
                VECSubtract((HuVecF *)lbl_1_data_2CC, &lbl_1_data_B0[i], &vec);
                VECNormalize(&vec, &dir);
                if (dir.z > 1) {
                    dir.z = 1;
                }
                else if (dir.z < -1) {
                    dir.z = -1;
                }
                rotEnd = acosf(dir.z);
                if (dir.x < 0) {
                    rotEnd = -rotEnd;
                }
                player->rotEnd = (180 * rotEnd) / M_PI;
                break;
        }
        if (!fn_1_21C(&player->rot, player->rotEnd, 0.01f)) {
            if (player->mot != 3) {
                CharMotionShiftSet(player->charNo, player->motId[3], 0, 15, HU3D_MOTATTR_LOOP);
                player->mot = 3;
            }
        }
    }
    while (TRUE) {
        doneNum = 0;
        for (player = &lbl_1_bss_0->player[0], i = 4; i--; player++) {
            if (fn_1_21C(&player->rot, player->rotEnd, lbl_1_bss_0->playerRotSpeed)) {
                if (player->mot != 0) {
                    CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_LOOP);
                    player->mot = 0;
                }
                doneNum++;
            }
            Hu3DModelRotSet(player->mdlId, 0, player->rot, 0);
        }
        if (doneNum == 4) {
            break;
        }
        HuPrcVSleep();
    }
    lbl_1_bss_0->flag &= ~0x1000;
    HuPrcEnd();
}

/* 336 insns */
void fn_1_6A14(void)
{
    s8 tbl[19][13];
    s32 i;
    s32 j;
    s32 k;
    s32 t;

    for (i = 19; i--;) {
        for (j = 12; j--;) {
            tbl[i][j] = j % 4;
        }
        tbl[i][12] = 4;
        fn_1_A0(tbl[i], 13);
        for (j = 5; j--;) {
            Hu3DMotionTimeSet(lbl_1_bss_0->panelMdlId[i][j], 60.0f);
            Hu3DModelAttrSet(lbl_1_bss_0->panelMdlId[i][j], HU3D_MOTATTR_PAUSE);
        }
    }
    k = 0;
    while (TRUE) {
        if (k == 13) {
            for (i = 19; i--;) {
                fn_1_A0(tbl[i], 13);
            }
            k = 0;
        }
        for (t = 5; t--;) {
            if (lbl_1_bss_0->flag & 0x2000) {
                break;
            }
            HuPrcVSleep();
        }
        if (lbl_1_bss_0->flag & 0x2000) {
            break;
        }
        for (i = 19; i--;) {
            fn_1_B34(i, tbl[i][k]);
        }
        k++;
    }
    for (i = 19; i--;) {
        for (j = 5; j--;) {
            Hu3DMotionTimeSet(lbl_1_bss_0->panelMdlId[i][j], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_0->panelMdlId[i][j], HU3D_MOTATTR_PAUSE);
        }
        if (lbl_1_bss_4->panelOwner[i] < 0) {
            fn_1_B34(i, 4);
        }
        else {
            fn_1_B34(i, lbl_1_bss_4->panelOwner[i]);
        }
    }
    HuPrcEnd();
}

/* 21 insns */
void fn_1_6F54(void)
{
    lbl_1_bss_0->flag &= ~0x2000;
    HuPrcChildCreate(fn_1_6A14, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 35 insns */
void fn_1_6FA8(s32 mode, float speed)
{
    lbl_1_bss_0->flag |= 0x1000;
    lbl_1_bss_0->playerRotMode = mode;
    lbl_1_bss_0->playerRotSpeed = speed;
    HuPrcChildCreate(fn_1_6444, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 65 insns */
void fn_1_7034(void)
{
    MGWARS_PLAYER *player;
    s32 i;

    while (lbl_1_bss_0->unk36A--) {
        if (lbl_1_bss_0->flag & 0x4000) {
            lbl_1_bss_0->unk36A = -1;
            HuPrcEnd();
            return;
        }
        HuPrcVSleep();
    }
    for (i = 4; i--;) {
        player = &lbl_1_bss_0->player[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    HuPrcEnd();
}

/* 34 insns */
void fn_1_7138(s32 arg)
{
    lbl_1_bss_0->flag &= ~0x4000;
    lbl_1_bss_0->unk36A = arg;
    if (lbl_1_bss_0->unk36A > 0) {
        HuPrcChildCreate(fn_1_7034, 100, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 23 insns */
void fn_1_71C0(void)
{
    while (TRUE) {
        if (Hu3DMotionEndCheck(lbl_1_bss_0->mdlId[58])) {
            break;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[58], HU3D_ATTR_DISPOFF);
    HuPrcEnd();
}

/* 28 insns */
void fn_1_721C(void)
{
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[58], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[58], HU3D_ATTR_DISPOFF);
    HuPrcChildCreate(fn_1_71C0, 100, 0x1000, 0, HuPrcCurrentGet());
}

/* 440 insns */
void fn_1_728C(void)
{
    MGWARS_PLAYER *player;
    s32 i;
    s32 j;
    HU3DMODELID mdlId;
    s32 k;
    HU3DMOTID motId;
    HuVec2f winSize;

    lbl_1_bss_4 = (MGWARS_MODEWORK *)mgModeWork;
    lbl_1_bss_0 = &lbl_1_bss_8;
    lbl_1_bss_0->objman = omInitObjMan(200, 1000);
    HuDataSelHeapReadNum(DATANUM(DATA_instpic, 0), HU_MEMNUM_OVL, HEAP_MODEL);
    Hu3DCameraCreate(HU3D_CAM1);
    Hu3DCameraPerspectiveSet(HU3D_CAM1, 40, 10, 5000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM1, 0, 0, 640, 480);
    lbl_1_bss_0->mgNum = 0;
    for (i = 0; i < 26; i++) {
        for (j = 0; mgDataTbl[j].ovl != lbl_1_data_0[i].ovl; j++) {
            if (mgDataTbl[j].ovl == (u16)DLL_NONE) {
                OSReport("mgwars.c : \202c\202k\202k\202\252\214\251\202\302\202\251\202\350\202\334\202\271\202\361\201I\201I\n");
                abort();
            }
        }
        lbl_1_data_0[i].mgIdx = j;
        if (GWMgUnlockGet(j + 501)) {
            lbl_1_bss_0->mg[lbl_1_bss_0->mgNum] = lbl_1_data_0[i];
            lbl_1_bss_0->mgNum++;
        }
    }
    for (i = 0; i < lbl_1_bss_0->mgNum; i++) {
        lbl_1_bss_0->mg[i].battleF = mgDataTbl[lbl_1_bss_0->mg[i].mgIdx].type == (u8)MG_TYPE_BATTLE;
    }
    lbl_1_bss_0->winId = 0;
    lbl_1_bss_0->cameraMot = -1;
    lbl_1_bss_0->mesFlag = 0;
    lbl_1_bss_0->flag = 0;
    lbl_1_bss_0->cameraMotNext = -1;
    lbl_1_bss_0->cameraMotTime = 0;
    lbl_1_bss_0->cameraMotArg = 0;
    lbl_1_bss_0->fbCopyAnim = NULL;
    lbl_1_bss_0->seNo = -1;
    lbl_1_bss_0->animId = -1;
    lbl_1_bss_0->streamNo = -1;
    for (i = 26; i--;) {
        lbl_1_bss_0->mgIcon[i] = NULL;
    }
    HuWinInit(1);
    HuWinMesMaxSizeBetGet(&winSize, MGWARS_MES(0), MGWARS_MES(30));
    lbl_1_bss_0->winId = HuWinExCreate(-10000, 350, winSize.x, winSize.y, -1);
    Hu3DZClearLayerSet(14);
    fn_1_1A80();
    fn_1_F068();
    for (i = 4; i--;) {
        j = 0;
        for (k = 19; k--;) {
            if (lbl_1_bss_4->panelOwner[k] == i) {
                j++;
            }
        }
        fn_1_F848(i, j);
    }
    for (player = &lbl_1_bss_0->player[0], i = 0; i < 4; i++, player++) {
        player->no = i;
        player->charNo = GwPlayerConf[i].charNo;
        player->padNo = GwPlayerConf[i].padNo;
        player->mdlId = CharModelMotListCreate(player->charNo, CHAR_MODEL1, (unsigned int *)lbl_1_data_9C, player->motId);
        player->mot = -1;
        player->rot = 0;
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[1], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[2], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[3], FALSE);
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelPosSet(player->mdlId, lbl_1_data_B0[i].x, lbl_1_data_B0[i].y, lbl_1_data_B0[i].z);
        Hu3DModelLayerSet(player->mdlId, 3);
        Hu3DModelCameraSet(player->mdlId, HU3D_CAM1);
    }
    mdlId = Hu3DModelCreateData(DATANUM(DATA_mgwars, 0));
    lbl_1_bss_0->guideMdlId = mdlId;
    motId = Hu3DJointMotionData(mdlId, DATANUM(DATA_mgwars, 1));
    Hu3DMotionSet(mdlId, motId);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdlId, 7);
    Hu3DModelCameraSet(mdlId, HU3D_CAM0 | HU3D_CAM1);
    fn_1_57C0(0, 0);
    Hu3DNoSyncSet(1);
}

/* 215 insns */
void fn_1_796C(void)
{
    s32 swap;
    s32 i;
    s16 last;
    ANIMDATA *anim;
    s16 tmp;

    if (lbl_1_bss_4->round == lbl_1_bss_0->mgNum) {
        last = lbl_1_bss_4->mgOrder[lbl_1_bss_0->mgNum - 1];
        lbl_1_bss_4->round = 0;
        fn_1_A0(lbl_1_bss_4->mgOrder, lbl_1_bss_0->mgNum);
        if (last == lbl_1_bss_4->mgOrder[0]) {
            if (lbl_1_bss_0->mgNum > 1) {
                swap = frandmod(lbl_1_bss_0->mgNum - 1) + 1;
            }
            else {
                swap = 1;
            }
            tmp = lbl_1_bss_4->mgOrder[swap];
            lbl_1_bss_4->mgOrder[swap] = last;
            lbl_1_bss_4->mgOrder[0] = tmp;
        }
    }
    if (!(lbl_1_bss_0->flag & 0x80)) {
        for (i = lbl_1_bss_0->mgNum; i--;) {
            anim = HuSprAnimRead(HuDataSelHeapReadNum(mgDataTbl[lbl_1_bss_0->mg[i].mgIdx].instPic[0], HU_MEMNUM_OVL, HEAP_MODEL));
            HuSprAnimLock(anim);
            lbl_1_bss_0->mgIcon[i] = anim;
        }
        if (lbl_1_bss_0->mgNum > 1) {
            lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[frandmod(lbl_1_bss_0->mgNum - 1) + 1], lbl_1_bss_0->mdlId[57], "mg_shot");
        }
        else {
            lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[0], lbl_1_bss_0->mdlId[57], "mg_shot");
        }
        lbl_1_bss_0->flag |= 0x80;
    }
}

/* 90 insns */
void fn_1_7CC8(void)
{
    OMOVLHIS *his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, 0, his->stat);
    HuDataDirClose(DATA_mgwars);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    HuPrcVSleep();
    if (lbl_1_bss_0->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
        lbl_1_bss_0->streamNo = -1;
    }
    if (lbl_1_bss_0->fbCopyAnim) {
        HuSprAnimKill(lbl_1_bss_0->fbCopyAnim);
    }
    GWMgInstFSet(TRUE);
    HuWinExClose(lbl_1_bss_0->winId);
    HuWinExKill(lbl_1_bss_0->winId);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    _ClearFlag(FLAG_INST_NOHISCHG);
    _ClearFlag(FLAG_INST_MGMODE);
    memset(lbl_1_bss_4, 0, sizeof(MGWARS_MODEWORK));
}

/* 916 insns */
void fn_1_7E30(void)
{
    MGWARS_PLAYER *player;
    s32 i;
    s32 j;
    OMOVLHIS *his;
    s32 k;

    _SetFlag(FLAG_INST_NOHISCHG);
    _SetFlag(FLAG_INST_MGMODE);
    lbl_1_bss_4->unk0 = 0;
    his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, 1, his->stat);
    lbl_1_bss_0->streamNo = HuAudBGMPlay(38);
    lbl_1_bss_4->round = lbl_1_bss_0->mgNum;
    lbl_1_bss_4->flag = 0;
    i = lbl_1_bss_0->mgNum;
    while (i--) {
        lbl_1_bss_4->mgOrder[i] = i;
    }
    i = 19;
    while (i--) {
        lbl_1_bss_4->panelOwner[i] = -1;
    }
    i = 4;
    while (i--) {
        j = 0;
        k = 19;
        while (k--) {
            if (lbl_1_bss_4->panelOwner[k] == i) {
                j++;
            }
        }
        fn_1_F848(i, j);
    }
    i = 4;
    while (i--) {
        player = &lbl_1_bss_0->player[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    fn_1_4958();
    fn_1_57C0(0, 0);
    Hu3DModelPosSet(lbl_1_bss_0->guideMdlId, lbl_1_data_E0[13].x, lbl_1_data_E0[13].y, lbl_1_data_E0[13].z);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[4], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[65], 0.0f);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[5], 0.0f);
    Hu3DCameraMotionStart(lbl_1_bss_0->mdlId[74], 2);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[65], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[65], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
    fn_1_6F54();
    fn_1_A30(WIPE_TYPE_PREVTYPE, 60);
    for (player = lbl_1_bss_0->player, i = 0; i < 4; i++, player++) {
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[3], TRUE);
    }
    j = 270;
    while (j--) {
        HuPrcVSleep();
    }
    Hu3DCameraMotionOff(lbl_1_bss_0->mdlId[74]);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[65], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[65], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
    fn_1_C04(66, 30, 2);
    fn_1_189C(925, 180);
    fn_1_5EB0(lbl_1_data_E0[13], 45.0f);
    while (!fn_1_684(0x200)) {
        HuPrcVSleep();
    }
    j = 15;
    while (j--) {
        HuPrcVSleep();
    }
    fn_1_64C(0x2000);
    fn_1_7FC(fn_1_E2D0);
    while (!fn_1_7A0(1)) {
        HuPrcVSleep();
    }
    fn_1_83C(69, 45.0f, 1);
    {
        void (*mesFunc[4])(void) = { fn_1_E3C8, fn_1_E450, fn_1_E4D8, fn_1_E560 };
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
        fn_1_7FC(fn_1_E36C);
        while (!fn_1_7A0(2)) {
            HuPrcVSleep();
        }
        for (i = 0; i < 4; i++) {
            player = &lbl_1_bss_0->player[i];
            fn_1_1778(player, 0);
            fn_1_189C(938, 120);
            omVibrate(player->padNo, 12, 4, 2);
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                player->mot = 1;
            }
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[44 + i], HU3D_MOTATTR_PAUSE);
            fn_1_57C0(i + 9, 60);
            fn_1_7FC(mesFunc[i]);
            j = 150;
            while (j--) {
                HuPrcVSleep();
            }
            if (player->mot != 0) {
                CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
                player->mot = 0;
            }
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[44 + i], HU3D_MOTATTR_LOOP);
        }
    }
    fn_1_568();
    fn_1_64C(1);
}

/* 71 insns */
void fn_1_8C80(void)
{
    s32 keys[4];
    s32 i;
    s32 t;

    HuWinDisablePlayerSet(lbl_1_bss_0->winId, 15);
    while (!fn_1_7A0(lbl_1_bss_0->unk354)) {
        for (i = 4; i--;) {
            keys[i] = -1;
            if (GwPlayerConf[i].type != 0) {
                keys[i] = PAD_BUTTON_A;
            }
        }
        HuWinComKeyWait(keys[0], keys[1], keys[2], keys[3], 10);
        for (t = 30; t--;) {
            HuPrcVSleep();
        }
    }
    HuWinDisablePlayerReset(lbl_1_bss_0->winId, 15);
    HuWinComKeyReset();
    HuPrcEnd();
}

/* 21 insns */
void fn_1_8D9C(s32 arg)
{
    lbl_1_bss_0->unk354 = arg;
    HuPrcChildCreate(fn_1_8C80, 200, 0x3000, 0, HuPrcCurrentGet());
}

/* 886 insns */
void fn_1_8DF0(void)
{
    MGWARS_PLAYER *player;
    int i;
    int winner;
    int panel;
    int count;
    MGWARS_PLAYER *playerP;
    HU3DMODELID mdlId;

    fn_1_AD8(lbl_1_bss_0->mdlId[2], 0, 660);
    panel = 19;
    while (panel--) {
        if (lbl_1_bss_4->panelOwner[panel] < 0) {
            mdlId = fn_1_B34(panel, 4);
        } else {
            mdlId = fn_1_B34(panel, lbl_1_bss_4->panelOwner[panel]);
        }
        fn_1_AD8(mdlId, 0, 120);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        lbl_1_bss_0->unk32C[panel] = 4;
    }
    count = 0;
    if (fn_1_6DC(1)) {
        OSReport("\203o\203g\203\213\203Q\201[\203\200\201I\201I\n");
        i = 4;
        while (i--) {
            OSReport("\t Player %d = Rank %d\n", i, GWMgCoinBonusGet(i));
            if (GWMgCoinBonusGet(i) == 0) {
                winner = i;
                count++;
            }
        }
    } else {
        OSReport("VS 4 \203Q\201[\203\200\201I\201I\n");
        i = 4;
        while (i--) {
            OSReport("\t Player %d = Coin %d\n", i, GWMgCoinBonusGet(i));
            if (GWMgCoinBonusGet(i) >= 10) {
                winner = i;
                count++;
            }
        }
    }
    if (fn_1_6DC(2)) {
        lbl_1_bss_0->flag |= 0x10;
    }
    if (count != 1) {
        lbl_1_bss_0->streamNo = HuAudBGMPlay(82);
        lbl_1_bss_0->flag |= 8;
    } else {
        if (lbl_1_bss_0->flag & 0x10) {
            fn_1_1050();
        } else {
            HuPrcChildCreate(fn_1_F14, 100, 0x1000, 0, HuPrcCurrentGet());
        }
        lbl_1_bss_0->unk8 = winner;
    }
    if (lbl_1_bss_0->flag & 8) {
        fn_1_C04(66, 60, 2);
        fn_1_57C0(0, 0);
    } else {
        fn_1_57C0(winner + 14, 0);
        fn_1_6FA8(1, 180.0f);
        fn_1_C04(winner + 70, 60, 2);
        lbl_1_bss_0->player[winner].rot = 0;
        Hu3DModelRotSet(lbl_1_bss_0->player[winner].mdlId, 0, lbl_1_bss_0->player[winner].rot, 0);
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[winner + 44], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[winner + 44], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[5], Hu3DMotionMaxTimeGet(lbl_1_bss_0->mdlId[5]));
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    WipeWait();
    for (playerP = lbl_1_bss_0->player, i = 0; i < 4; i++, playerP++) {
        CharMotionVoiceOnSet(playerP->charNo, lbl_1_data_9C[3], TRUE);
    }
    if (lbl_1_bss_0->flag & 8) {
        i = 4;
        while (i--) {
            player = &lbl_1_bss_0->player[i];
            fn_1_1778(player, 2);
            if (player->mot != 2) {
                CharMotionShiftSet(player->charNo, player->motId[2], 0, 15, HU3D_MOTATTR_NONE);
                player->mot = 2;
            }
        }
    } else {
        fn_1_5EB0(lbl_1_data_E0[winner + 14], 45.0f);
        while (!(lbl_1_bss_0->flag & 0x200)) {
            HuPrcVSleep();
        }
        player = &lbl_1_bss_0->player[winner];
        HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][1], 64);
        fn_1_189C(938, 120);
        if (player->mot != 1) {
            CharMotionShiftSet(player->charNo, player->motId[1], 0, 15, HU3D_MOTATTR_NONE);
            player->mot = 1;
        }
    }
    if (lbl_1_bss_0->flag & 8) {
        fn_1_7FC(fn_1_E87C);
        while (!(lbl_1_bss_0->mesFlag & 0x400)) {
            HuPrcVSleep();
        }
    } else {
        fn_1_7FC(fn_1_E908);
        count = 180;
        while (count--) {
            HuPrcVSleep();
        }
        player = &lbl_1_bss_0->player[winner];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 15, HU3D_MOTATTR_NONE);
            player->mot = 0;
        }
        if (GwPlayerConf[winner].type != 0) {
            fn_1_8D9C(0x1000);
        }
        fn_1_7FC(fn_1_E9A0);
        while (!(lbl_1_bss_0->mesFlag & 0x1000)) {
            HuPrcVSleep();
        }
    }
    lbl_1_bss_0->flag |= 0x4000;
    HuPrcVSleep();
}
#ifdef __MWERKS__
#endif

/* 1683 insns */
void fn_1_9BC8(void)
{
    s32 i;
    MGWARS_PLAYER *player;
    s32 panelNo;
    s32 time;
    s32 num;
    s32 dirNo;
    s32 playerNo;
    s32 a;
    MGWARS_PANEL *panelP;
    s32 b;
    s32 stkX;
    s32 stkY;
    s32 zeroNum;
    float t;
    s32 score[19];
    s32 panelTbl[19];
    s32 zeroTbl[19];
    s32 lostF[4];
    HuVecF pos;
    HuVecF dir;
    HuVecF ofs;
    s32 pan2;
    s32 padNo;
    s32 blink;
    s32 doneNum;
    OMOVLHIS *his;
    s32 tmp2;
    s32 tmp1;
    s32 k;
    s32 pan;
    HU3DMODELID cursorMdl;
    HU3DMODELID boardMdl;

    playerNo = fn_1_5C4();
    lbl_1_bss_0->unk352 = lbl_1_bss_0->mdlId[52 + playerNo];
    Hu3DModelAttrReset(lbl_1_bss_0->unk352, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[56], HU3D_ATTR_DISPOFF);
    fn_1_AD8(lbl_1_bss_0->unk352, 0, 240);
    switch (playerNo) {
        case 0:
            fn_1_AD8(lbl_1_bss_0->mdlId[56], 0, 60);
            break;
        case 1:
            fn_1_AD8(lbl_1_bss_0->mdlId[56], 61, 120);
            break;
        case 2:
            fn_1_AD8(lbl_1_bss_0->mdlId[56], 121, 180);
            break;
        case 3:
            fn_1_AD8(lbl_1_bss_0->mdlId[56], 181, 240);
            break;
    }
    i = 19;
    while (i--) {
        lbl_1_data_2D8[i].owner = lbl_1_bss_4->panelOwner[i];
        lbl_1_data_2D8[i].unk7 = lbl_1_data_2D8[i].owner;
    }
    fn_1_6FA8(1, 2.0f);
    fn_1_C04(68, 60, 1);
    fn_1_7FC(fn_1_E9FC);
    while (!(lbl_1_bss_0->mesFlag & 0x2000)) {
        HuPrcVSleep();
    }
    fn_1_F860();
    if (lbl_1_bss_0->flag & 0x10) {
        i = 19;
        while (i--) {
            if (playerNo != lbl_1_data_2D8[i].owner) {
                lbl_1_data_2D8[i].unk8 = 1;
            }
        }
    } else {
        fn_1_37D4();
    }
    if (!(lbl_1_bss_0->flag & 0x10)) {
        num = 0;
        zeroNum = 0;
        i = 19;
        while (i--) {
            if (lbl_1_data_2D8[i].unk8) {
                score[num] = fn_1_3458(i, playerNo);
                panelTbl[num] = i;
                if (score[num] == 0) {
                    zeroTbl[zeroNum] = i;
                    zeroNum++;
                }
                num++;
            }
        }
        if (num != zeroNum) {
            i = zeroNum;
            while (i--) {
                lbl_1_data_2D8[zeroTbl[i]].unk8 = 0;
            }
        }
        i = 19;
        while (i--) {
            lbl_1_data_2D8[i].unk7 = lbl_1_data_2D8[i].owner;
        }
    }
    i = 19;
    while (i--) {
        if (lbl_1_data_2D8[i].unk8) {
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[25 + i], HU3D_ATTR_DISPOFF);
        }
    }
    if (GwPlayerConf[playerNo].type != 0) {
        if (lbl_1_bss_0->flag & 0x10) {
            num = 0;
            i = 19;
            while (i--) {
                if (lbl_1_data_2D8[i].unk8) {
                    score[num] = fn_1_3458(i, playerNo);
                    panelTbl[num] = i;
                    num++;
                }
            }
            i = 19;
            while (i--) {
                lbl_1_data_2D8[i].unk7 = lbl_1_data_2D8[i].owner;
            }
        }
        for (a = 0; a < num - 1; a++) {
            for (b = a + 1; b < num; b++) {
                if (score[a] > score[b]) {
                    tmp1 = score[a];
                    score[a] = score[b];
                    score[b] = tmp1;
                    tmp2 = panelTbl[a];
                    panelTbl[a] = panelTbl[b];
                    panelTbl[b] = tmp2;
                }
            }
        }
        i = 19;
        while (i--) {
            lbl_1_data_2D8[i].unk7 = lbl_1_data_2D8[i].owner;
        }
        panelNo = panelTbl[num - 1];
        fn_1_4170(panelNo);
    } else {
        panelNo = 9;
        padNo = GwPlayerConf[playerNo].padNo;
        panelP = &lbl_1_data_2D8[panelNo];
        cursorMdl = lbl_1_bss_0->mdlId[56];
        blink = 0;
        do {
            HuPrcVSleep();
            dirNo = -1;
            stkX = HuPadStkX[padNo];
            stkY = HuPadStkY[padNo];
            if (stkX > 28.0f) {
                stkX = 1;
            } else if (stkX < -28.0f) {
                stkX = 2;
            } else {
                stkX = 0;
            }
            if (stkY > 28.0f) {
                stkY = 1;
            } else if (stkY < -28.0f) {
                stkY = 2;
            } else {
                stkY = 0;
            }
            switch ((stkX << 4) | stkY) {
                case 0x01:
                    dirNo = 0;
                    break;
                case 0x02:
                    dirNo = 3;
                    break;
                case 0x10:
                    dirNo = 1;
                    break;
                case 0x11:
                    dirNo = 0;
                    break;
                case 0x12:
                    dirNo = 2;
                    break;
                case 0x20:
                    dirNo = 4;
                    break;
                case 0x21:
                    dirNo = 5;
                    break;
                case 0x22:
                    dirNo = 3;
                    break;
            }
            if (dirNo >= 0 && panelP->link[dirNo] >= 0) {
                Hu3DModelAttrSet(cursorMdl, HU3D_ATTR_DISPOFF);
                blink = 0;
                panelNo = panelP->link[dirNo];
                panelP = &lbl_1_data_2D8[panelNo];
                boardMdl = lbl_1_bss_0->unk352;
                PSVECSubtract(&lbl_1_data_1E8[panelNo], &lbl_1_bss_0->unk3A4, &dir);
                pan = 64.0f + 24.0f * (lbl_1_data_1E8[panelNo].x / 320.0f);
                HuAudFXPlayPan(1213, pan);
                for (k = 0; k < 20; k++) {
                    t = k / 20.0f;
                    t = sin(M_PI * t / 2.0);
                    t = sin(M_PI * t / 2.0);
                    t = sin(M_PI * t / 2.0);
                    PSVECScale(&dir, &ofs, t);
                    PSVECAdd(&lbl_1_bss_0->unk3A4, &ofs, &pos);
                    Hu3DModelPosSet(boardMdl, pos.x, pos.y, pos.z);
                    HuPrcVSleep();
                }
                PSVECAdd(&lbl_1_bss_0->unk3A4, &dir, &lbl_1_bss_0->unk3A4);
                Hu3DModelPosSet(boardMdl, lbl_1_bss_0->unk3A4.x, lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
            }
            if (blink == 3) {
                Hu3DModelAttrReset(cursorMdl, HU3D_ATTR_DISPOFF);
                Hu3DModelPosSet(cursorMdl, lbl_1_bss_0->unk3A4.x, 20.0f + lbl_1_bss_0->unk3A4.y, lbl_1_bss_0->unk3A4.z);
            } else {
                blink++;
            }
        } while (!(HuPadBtnDown[padNo] & PAD_BUTTON_A) || !panelP->unk8);
        pan2 = 64.0f + 24.0f * (lbl_1_data_1E8[panelNo].x / 320.0f);
        HuAudFXPlayPan(1214, pan2);
    }
    fn_1_568();
    i = 19;
    while (i--) {
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[25 + i], HU3D_ATTR_DISPOFF);
    }
    fn_1_3458(panelNo, playerNo);
    i = 4;
    while (i--) {
        lostF[i] = 0;
    }
    i = 19;
    while (i--) {
        if (lbl_1_data_2D8[i].unk7 != lbl_1_data_2D8[i].owner) {
            lbl_1_bss_0->unk32C[i] = 0;
            if (lbl_1_data_2D8[i].owner >= 0) {
                lostF[lbl_1_data_2D8[i].owner] = 1;
            }
        }
        lbl_1_bss_4->panelOwner[i] = lbl_1_data_2D8[i].unk7;
    }
    time = 270;
    lbl_1_bss_0->unk36C = Hu3DMotionTimeGet(lbl_1_bss_0->mdlId[6]);
    fn_1_6318();
    while (TRUE) {
        time--;
        fn_1_4534(panelNo, lbl_1_bss_4->panelOwner[panelNo]);
        if (lbl_1_bss_0->unk32C[panelNo] == 4) {
            break;
        }
        lbl_1_bss_0->unk36C++;
        lbl_1_bss_0->unk36C = lbl_1_bss_0->unk36C % 120;
        HuPrcVSleep();
    }
    lbl_1_data_2D8[panelNo].unk7 = lbl_1_data_2D8[panelNo].owner;
    do {
        time--;
        doneNum = 0;
        lbl_1_bss_0->unkA = 1;
        i = 19;
        while (i--) {
            if (lbl_1_data_2D8[i].unk7 != lbl_1_data_2D8[i].owner) {
                fn_1_4534(i, lbl_1_bss_4->panelOwner[i]);
                lbl_1_bss_0->unkA++;
            }
            if (lbl_1_bss_0->unk32C[i] == 4) {
                doneNum++;
            }
        }
        lbl_1_bss_0->unk36C++;
        lbl_1_bss_0->unk36C = lbl_1_bss_0->unk36C % 120;
        HuPrcVSleep();
    } while (doneNum != 19);
    fn_1_189C(938, 120);
    i = 4;
    while (i--) {
        player = &lbl_1_bss_0->player[i];
        if (playerNo == i) {
            omVibrate(player->padNo, 12, 4, 2);
            switch (player->no) {
                case 0:
                case 2:
                    HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][3], 40);
                    break;
                case 1:
                case 3:
                    HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][3], 88);
                    break;
            }
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                player->mot = 1;
            }
        } else if (lostF[i]) {
            omVibrate(player->padNo, 12, 4, 2);
            switch (player->no) {
                case 0:
                case 2:
                    HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][4], 40);
                    break;
                case 1:
                case 3:
                    HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][4], 88);
                    break;
            }
            if (player->mot != 2) {
                CharMotionShiftSet(player->charNo, player->motId[2], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                player->mot = 2;
            }
        }
    }
    if (time < 150) {
        time = 150;
    }
    if (GwPlayerConf[playerNo].type != 0) {
        fn_1_8D9C(0x80000);
    }
    fn_1_7FC(fn_1_EA84);
    while (!(lbl_1_bss_0->mesFlag & 0x80000)) {
        time--;
        HuPrcVSleep();
    }
    fn_1_568();
    while (time > 0) {
        time--;
        HuPrcVSleep();
    }
    i = 4;
    while (i--) {
        player = &lbl_1_bss_0->player[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0.0f, 15.0f, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    time = 0; /* reused as the free-panel count (r28 in the reference) */
    i = 19;
    while (i--) {
        if (lbl_1_bss_4->panelOwner[i] == -1) {
            time++;
        }
    }
    if (time == 0) {
        his = omOvlHisGet(0);
        omOvlHisChg(0, his->ovl, 2, his->stat);
        lbl_1_bss_4->flag |= 4;
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[44 + playerNo], HU3D_MOTATTR_LOOP);
    fn_1_F884();
}

/* 738 insns */
void fn_1_B614(void)
{
    s32 time;
    MGWARS_PLAYER *player;
    s32 target;
    s32 mdlId;
    s32 found;
    s32 wait;
    u8 battleF;
    float scale;

    target = lbl_1_bss_4->mgOrder[lbl_1_bss_4->round];
    wait = 5;
    if (fn_1_684(1)) {
        fn_1_83C(66, 60.0f, 0);
        fn_1_57C0(0, 120);
    } else if (fn_1_684(8)) {
        fn_1_83C(66, 10.0f, 0);
        fn_1_57C0(0, 0);
    } else {
        fn_1_57C0(0, 120);
        lbl_1_bss_0->cameraMotNext = 66;
        lbl_1_bss_0->cameraMotTime = 80.0f;
        lbl_1_bss_0->cameraMotArg = 1;
        HuPrcChildCreate(fn_1_498, 100, 0x1000, 0, HuPrcCurrentGet());
        HuPrcVSleep();
        time = 60;
        while (time--) {
            HuPrcVSleep();
        }
    }
    while (!fn_1_684(0x200)) {
        HuPrcVSleep();
    }
    if (target < lbl_1_bss_0->mgNum / 2) {
        target += lbl_1_bss_0->mgNum;
    }
    if (target < 10) {
        target += (10 / lbl_1_bss_0->mgNum) * lbl_1_bss_0->mgNum;
    }
    fn_1_6FA8(2, 2.0f);
    HuPrcChildCreate(fn_1_E674, 100, 0x1000, 0, HuPrcCurrentGet());
    HuPrcVSleep();
    while (!fn_1_7A0(0x80)) {
        HuPrcVSleep();
    }
    fn_1_568();
    mdlId = lbl_1_bss_0->mdlId[57];
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelScaleSet(mdlId, 1.0f, 0.0f, 1.0f);
    HuAudFXPlay(1207);
    time = 20;
    while (time--) {
        scale = HuCos(90.0f * (time / 20.0f));
        scale = sin(M_PI * scale / 2);
        scale = sin(M_PI * scale / 2);
        Hu3DModelScaleSet(mdlId, 1.0f, scale, 1.0f);
        HuPrcVSleep();
    }
    target += lbl_1_bss_0->mgNum;
    for (time = 0; time <= target; time++) {
        HuAudFXPlay(1208);
        if (lbl_1_bss_0->animId >= 0) {
            Hu3DAnimKill(lbl_1_bss_0->animId);
        }
        lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[time % lbl_1_bss_0->mgNum], lbl_1_bss_0->mdlId[57], "mg_shot");
        fn_1_9F4(wait);
    }
    HuAudFXPlay(1209);
    fn_1_AD8(lbl_1_bss_0->mdlId[2], 661.0f, 700.0f);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[2], HU3D_MOTATTR_LOOP);
    HuPrcChildCreate(fn_1_6068, 100, 0x1000, 0, HuPrcCurrentGet());
    fn_1_7FC(fn_1_E6FC);
    while (!fn_1_7A0(0x100)) {
        HuPrcVSleep();
    }
    found = FALSE;
    for (time = 0; time < 19; time++) {
        if (lbl_1_bss_4->panelOwner[time] >= 0) {
            found = !((lbl_1_bss_4->unk0 + 1) % 10);
            break;
        }
    }
    if (found) {
        fn_1_110C();
        fn_1_721C();
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
        fn_1_AD8(lbl_1_bss_0->mdlId[3], 181.0f, 300.0f);
        fn_1_189C(938, 120);
        time = 4;
        while (time--) {
            player = &lbl_1_bss_0->player[time];
            omVibrate(player->padNo, 15, 4, 2);
            fn_1_1778(player, 6);
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0, 15, HU3D_MOTATTR_NONE);
                player->mot = 1;
            }
        }
        fn_1_7138(180);
        fn_1_7FC(fn_1_E5E8);
        while (!fn_1_7A0(0x40)) {
            HuPrcVSleep();
        }
        fn_1_64C(0x4000);
        HuPrcVSleep();
        lbl_1_bss_4->unk0 = 0;
        fn_1_69C(2);
    } else {
        fn_1_6BC(2);
    }
    if (lbl_1_bss_4->unk0 + 1 >= 10) {
        lbl_1_bss_4->unk0 = 0;
    }
    battleF = lbl_1_bss_0->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].battleF;
    if (battleF) {
        fn_1_69C(1);
    } else {
        fn_1_6BC(1);
    }
}

/* 289 insns */
void fn_1_C19C(void)
{
    OMOVLHIS *his;
    s32 time;
    s32 mgNo;

    fn_1_7FC(fn_1_E784);
    while (!fn_1_7A0(0x200)) {
        HuPrcVSleep();
    }
    if (fn_1_684(2)) {
        his = omOvlHisGet(0);
        omOvlHisChg(0, his->ovl, 3, his->stat);
        return;
    }
    fn_1_568();
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[64], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[64], HU3D_ATTR_DISPOFF);
    fn_1_83C(67, 90.0f, 2);
    time = 60;
    while (time--) {
        HuPrcVSleep();
    }
    if (lbl_1_bss_0->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
        lbl_1_bss_0->streamNo = -1;
    }
    fn_1_404(lbl_1_bss_0->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgIdx);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 30);
    WipeWait();
    while (!lbl_1_bss_0->dirRead) {
        HuPrcVSleep();
    }
    GwSystem.mgNo = lbl_1_bss_0->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgNo - 501;
    mgNo = lbl_1_bss_0->mg[lbl_1_bss_4->mgOrder[lbl_1_bss_4->round]].mgNo;
    GWMgUnlockSet(mgNo);
    GwSystem.mgNo = mgNo - 501;
    lbl_1_bss_4->round++;
    lbl_1_bss_4->unk0++;
    if (fn_1_684(4)) {
        GWMgInstFSet(TRUE);
    } else {
        GWMgInstFSet(FALSE);
    }
    omOvlCallEx(DLL_instdll, 1, 0, 0);
    while (TRUE) {
        HuPrcVSleep();
    }
}

/* 1836 insns */
void fn_1_C620(void)
{
    s32 i;
    MGWARS_PLAYER *player;
    s32 winner;
    s32 time;
    OMOVLHIS *his;
    s32 j;
    s32 count[4];

    count[0] = count[1] = count[2] = count[3] = 0;
    i = 19;
    while (i--) {
        if (lbl_1_bss_4->panelOwner[i] >= 0) {
            count[lbl_1_bss_4->panelOwner[i]]++;
        }
    }
    lbl_1_bss_0->unk19 = count[0];
    for (i = 1; i < 4; i++) {
        if (lbl_1_bss_0->unk19 < count[i]) {
            lbl_1_bss_0->unk19 = count[i];
        }
    }
    lbl_1_bss_0->unk18 = 0;
    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_0->unk19 == count[i]) {
            lbl_1_bss_0->unk14[lbl_1_bss_0->unk18] = i;
            lbl_1_bss_0->unk18++;
        }
    }
    for (i = lbl_1_bss_0->unk18; i < 4; i++) {
        lbl_1_bss_0->unk14[i] == (s8)-1; /* retail bug: a compare, not the intended store */
    }
    i = 4;
    while (i--) {
        lbl_1_bss_0->camTarget[i] = lbl_1_data_B0[i];
        lbl_1_bss_0->camPos[i] = lbl_1_data_398[i];
        lbl_1_bss_0->camTarget[i].y += lbl_1_data_3C8[lbl_1_bss_0->player[i].charNo] + (CharModelHeightGet(lbl_1_bss_0->player[i].charNo) - 40.0f);
        lbl_1_bss_0->camPos[i].y += lbl_1_data_3C8[lbl_1_bss_0->player[i].charNo] + (CharModelHeightGet(lbl_1_bss_0->player[i].charNo) - 40.0f);
    }
    fn_1_83C(66, 80.0f, 2);
    fn_1_57C0(0, 120);
    fn_1_6FA8(0, 2.0f);
    HuAudFXPlay(16);
    fn_1_7FC(fn_1_EB5C);
    while (!(lbl_1_bss_0->mesFlag & 0x4000)) {
        HuPrcVSleep();
    }
    while (lbl_1_bss_0->cameraMotNext != -1) {
        HuPrcVSleep();
    }
    fn_1_7FC(fn_1_EBB8);
    while (!(lbl_1_bss_0->mesFlag & 0x8000)) {
        HuPrcVSleep();
    }
    HuAudSStreamPauseFadeOut(lbl_1_bss_0->streamNo, TRUE, 100);
    lbl_1_bss_0->seNo37C = HuAudFXPlay(31);
    lbl_1_bss_0->seNo380 = HuAudFXPlay(33);
    fn_1_568();
    Hu3DCameraCreate(HU3D_CAM0);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 20.0f, 20.0f, 6000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM0, 0, 0, 640, 480);
    lbl_1_bss_0->fbCopyX = 192.0f;
    lbl_1_bss_0->fbCopyY = 100.0f;
    lbl_1_bss_0->fbCopyW = 256.0f;
    lbl_1_bss_0->fbCopyH = 256.0f;
    Hu3DZClearLayerSet(15);
    if (lbl_1_bss_0->fbCopyAnim == 0) {
        lbl_1_bss_0->fbCopyAnim = HuSprAnimMake(256, 256, ANIM_BMP_RGB5A3);
        lbl_1_bss_0->fbCopyAnim->bmp->data = HuMemDirectMallocNum(HEAP_MODEL, lbl_1_bss_0->fbCopyAnim->bmp->dataSize, HU_MEMNUM_OVL);
        memset(lbl_1_bss_0->fbCopyAnim->bmp->data, 0, lbl_1_bss_0->fbCopyAnim->bmp->dataSize);
    }
    Hu3DLayerHookSet(6, fn_1_11E8);
    fn_1_12AC(0);
    HuPrcVSleep();
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[57], HU3D_ATTR_DISPOFF);
    if (lbl_1_bss_0->animId >= 0) {
        Hu3DAnimKill(lbl_1_bss_0->animId);
    }
    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->fbCopyAnim, lbl_1_bss_0->mdlId[57], "mg_shot");
    fn_1_E8C();
    Hu3DModelAttrReset(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
    fn_1_6F54();
    fn_1_4E94();
    Hu3DModelAttrSet(lbl_1_bss_0->mdlId[0], HU3D_ATTR_DISPOFF);
    time = 120;
    while (time--) {
        HuPrcVSleep();
    }
    fn_1_7FC(fn_1_EC1C);
    while (!(lbl_1_bss_0->mesFlag & 0x10000)) {
        HuPrcVSleep();
    }
    lbl_1_bss_0->flag &= ~0x400;
    HuPrcVSleep();
    HuPrcVSleep();
    fn_1_AD8(lbl_1_bss_0->mdlId[3], 181.0f, 300.0f);
    HuAudFXPlay(32);
    HuAudFXStop(lbl_1_bss_0->seNo37C);
    HuAudFXStop(lbl_1_bss_0->seNo380);
    if (lbl_1_bss_0->unk18 != 1) {
        fn_1_C04(69, 20, 2);
        fn_1_50DC();
        lbl_1_bss_0->flag |= 0x2000;
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
        i = lbl_1_bss_0->unk18;
        while (i--) {
            switch (lbl_1_bss_0->unk14[i]) {
                case 0:
                case 2:
                    HuAudFXPlayPan(1219, 40);
                    break;
                case 1:
                case 3:
                    HuAudFXPlayPan(1219, 88);
                    break;
            }
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 48], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 48], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 48], 0.0f);
        }
        fn_1_189C(925, -1);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
        time = 30;
        while (time--) {
            HuPrcVSleep();
        }
        fn_1_7FC(fn_1_ECA0);
        while (!(lbl_1_bss_0->mesFlag & 0x20000)) {
            HuPrcVSleep();
        }
        fn_1_568();
        i = lbl_1_bss_0->unk18;
        while (i--) {
            player = &lbl_1_bss_0->player[lbl_1_bss_0->unk14[i]];
            fn_1_1778(player, 5);
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                player->mot = 1;
            }
        }
        fn_1_11AC();
    } else {
        winner = lbl_1_bss_0->unk14[0];
        Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_0->camPos[winner].x, lbl_1_bss_0->camPos[winner].y, lbl_1_bss_0->camPos[winner].z, 0.0f, 1.0f, 0.0f,
            lbl_1_bss_0->camTarget[winner].x, lbl_1_bss_0->camTarget[winner].y, lbl_1_bss_0->camTarget[winner].z);
        for (j = 4; j--;) {
            if (j == winner) {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM0 | HU3D_CAM1);
            } else {
                Hu3DModelCameraSet(lbl_1_bss_0->player[j].mdlId, HU3D_CAM1);
            }
        }
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[winner + 44], HU3D_MOTATTR_LOOP);
        lbl_1_bss_0->flag |= 0x2000;
        switch (winner) {
            case 0:
            case 2:
                HuAudFXPlayPan(1219, 40);
                break;
            case 1:
            case 3:
                HuAudFXPlayPan(1219, 88);
                break;
        }
        fn_1_189C(925, -1);
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[winner + 48], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[winner + 48], HU3D_ATTR_DISPOFF);
        Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[winner + 48], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[60], HU3D_ATTR_DISPOFF);
        time = 30;
        while (time--) {
            HuPrcVSleep();
        }
        fn_1_7FC(fn_1_ECA0);
        while (!(lbl_1_bss_0->mesFlag & 0x20000)) {
            HuPrcVSleep();
        }
        fn_1_568();
        player = &lbl_1_bss_0->player[winner];
        if (player->mot != 1) {
            CharMotionShiftSet(player->charNo, player->motId[1], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
            player->mot = 1;
        }
        HuAudFXPlayPan(lbl_1_data_3FC[player->charNo][5], 64);
        fn_1_11AC();
        fn_1_C04(winner + 70, 30, 1);
        switch (winner) {
            case 0:
                fn_1_57C0(1, 60);
                break;
            case 1:
                fn_1_57C0(2, 30);
                break;
            case 2:
                fn_1_57C0(3, 105);
                break;
            case 3:
                fn_1_57C0(4, 60);
                break;
        }
    }
    i = 4;
    while (i--) {
        player = &lbl_1_bss_0->player[lbl_1_bss_0->unk14[i]];
        if (player->mot != 1) {
            CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[2], TRUE);
            if (player->mot != 2) {
                CharMotionShiftSet(player->charNo, player->motId[2], 0.0f, 15.0f, HU3D_MOTATTR_NONE);
                player->mot = 2;
            }
        }
    }
    lbl_1_bss_0->flag &= ~0x100;
    HuPrcVSleep();
    time = 300;
    while (time--) {
        HuPrcVSleep();
    }
    fn_1_7FC(fn_1_EED8);
    while (!(lbl_1_bss_0->mesFlag & 0x40000)) {
        HuPrcVSleep();
    }
    his = omOvlHisGet(0);
    lbl_1_bss_0->seTime = 0;
    if (lbl_1_bss_0->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
        lbl_1_bss_0->streamNo = -1;
    }
    if (lbl_1_bss_0->flag & 0x20) {
        omOvlHisChg(0, his->ovl, 0, his->stat);
        fn_1_568();
        time = 30;
        while (time--) {
            HuPrcVSleep();
        }
        fn_1_A84(WIPE_TYPE_WHITEFADE, 60);
        if (lbl_1_bss_0->unk18 != 1) {
            lbl_1_bss_0->flag &= ~0x800;
            HuPrcVSleep();
        }
        Hu3DCameraKill(HU3D_CAM0);
        Hu3DLayerHookSet(15, NULL);
        Hu3DLayerHookSet(6, NULL);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[57], HU3D_ATTR_DISPOFF);
        if (lbl_1_bss_0->mgIcon[lbl_1_bss_0->mgNum / 2] != 0) {
            if (lbl_1_bss_0->animId >= 0) {
                Hu3DAnimKill(lbl_1_bss_0->animId);
            }
            lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgIcon[lbl_1_bss_0->mgNum / 2], lbl_1_bss_0->mdlId[57], "mg_shot");
        }
        i = 4;
        while (i--) {
            player = &lbl_1_bss_0->player[lbl_1_bss_0->unk14[i]];
            CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[1], FALSE);
            CharMotionVoiceOnSet(player->charNo, lbl_1_data_9C[2], FALSE);
        }
        i = 4;
        while (i--) {
            Hu3DModelAttrSet(lbl_1_bss_0->mdlId[i + 44], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[i + 44], 0.0f);
        }
        i = lbl_1_bss_0->unk18;
        while (i--) {
            Hu3DModelAttrSet(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 44], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 48], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[lbl_1_bss_0->unk14[i] + 48], 0.0f);
        }
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[59], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_0->mdlId[59], HU3D_ATTR_DISPOFF);
        fn_1_AD8(lbl_1_bss_0->mdlId[3], 0.0f, 180.0f);
        lbl_1_bss_0->flag &= ~0x20;
        Hu3DModelAttrReset(lbl_1_bss_0->mdlId[0], HU3D_ATTR_DISPOFF);
    } else {
        omOvlHisChg(0, his->ovl, 3, his->stat);
    }
    fn_1_568();
}

