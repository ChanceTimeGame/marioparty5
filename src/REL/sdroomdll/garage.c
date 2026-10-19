/*
 * sdroomdll garage.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/garage.s.
 */

#include "REL/sdroomdll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "string.h"
#ifndef __MWERKS__
/* retail calls sprintf unprototyped (no crclr cr1eq at fn_1_A704); the host needs the varargs prototype */
#include "stdio.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_130 = 61.0f; /* 0x130 */
static const float lbl_1_rodata_134 = 240.0f; /* 0x134 */
static const double lbl_1_rodata_138 = 1450.0; /* 0x138 */
static const double lbl_1_rodata_140 = 3.141592653589793; /* 0x140 */
static const double lbl_1_rodata_148 = 180.0; /* 0x148 */
static const float lbl_1_rodata_150 = 0.0f; /* 0x150 */
/* 0x158 lbl_1_rodata_158 = 4503601774854144: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_160 = 1000.0; /* 0x160 */
static const float lbl_1_rodata_168 = 90.0f; /* 0x168 */
static const double lbl_1_rodata_170 = 170.0; /* 0x170 */
static const float lbl_1_rodata_178 = 1.1f; /* 0x178 */
static const double lbl_1_rodata_180 = 90.0; /* 0x180 */
static const double lbl_1_rodata_188 = 500.0; /* 0x188 */
static const double lbl_1_rodata_190 = 1.0; /* 0x190 */
static const double lbl_1_rodata_198 = 20.0; /* 0x198 */
static const float lbl_1_rodata_1A0 = 601.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 640.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 195.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = -1155.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = 1.8f; /* 0x1B0 */
static const float lbl_1_rodata_1B4 = 156.0f; /* 0x1B4 */
static const float lbl_1_rodata_1B8 = 344.0f; /* 0x1B8 */
static const float lbl_1_rodata_1BC = -10000.0f; /* 0x1BC */
static const float lbl_1_rodata_1C0 = 310.0f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = -1000.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = 352.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = 0.5f; /* 0x1CC */
static const float lbl_1_rodata_1D0 = 288.0f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 5.0f; /* 0x1D4 */
static const float lbl_1_rodata_1D8 = 20.0f; /* 0x1D8 */
static const float lbl_1_rodata_1DC = 15000.0f; /* 0x1DC */
static const float lbl_1_rodata_1E0 = 1.2f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = -3.5555496f; /* 0x1E4 */
static const float lbl_1_rodata_1E8 = 72.0f; /* 0x1E8 */
static const float lbl_1_rodata_1EC = 256.0f; /* 0x1EC */
static const float lbl_1_rodata_1F0 = 192.0f; /* 0x1F0 */
static const float lbl_1_rodata_1F4 = 1.0f; /* 0x1F4 */
static const float lbl_1_rodata_1F8 = 96.0f; /* 0x1F8 */
static const float lbl_1_rodata_1FC = 128.0f; /* 0x1FC */
static const float lbl_1_rodata_200 = 224.0f; /* 0x200 */
static const float lbl_1_rodata_204 = 480.0f; /* 0x204 */
static const float lbl_1_rodata_208 = 0.8f; /* 0x208 */
static const double lbl_1_rodata_210 = 128.0; /* 0x210 */
static const double lbl_1_rodata_218 = 0.8; /* 0x218 */
static const double lbl_1_rodata_220 = 0.2; /* 0x220 */
static const double lbl_1_rodata_228 = 10.0; /* 0x228 */
static const double lbl_1_rodata_230 = 30.0; /* 0x230 */
static const double lbl_1_rodata_238 = 600.0; /* 0x238 */
static const float lbl_1_rodata_240 = 214.0f; /* 0x240 */
static const float lbl_1_rodata_244 = 16.0f; /* 0x244 */
static const float lbl_1_rodata_248 = 354.0f; /* 0x248 */
static const float lbl_1_rodata_24C = 3000.0f; /* 0x24C */
static const float lbl_1_rodata_250 = 7000.0f; /* 0x250 */
static const float lbl_1_rodata_254 = 32.0f; /* 0x254 */
static const float lbl_1_rodata_258 = 332.0f; /* 0x258 */
static const float lbl_1_rodata_25C = 280.0f; /* 0x25C */
static const float lbl_1_rodata_260 = 320.0f; /* 0x260 */
static const float lbl_1_rodata_264 = -1.0f; /* 0x264 */
static const float lbl_1_rodata_268 = 10.0f; /* 0x268 */
static const float lbl_1_rodata_26C = 8.0f; /* 0x26C */
static const float lbl_1_rodata_270 = 15.0f; /* 0x270 */
static const float lbl_1_rodata_274 = 160.0f; /* 0x274 */
static const float lbl_1_rodata_278 = 173.0f; /* 0x278 */
static const float lbl_1_rodata_27C = 48.0f; /* 0x27C */
static const float lbl_1_rodata_280 = 304.0f; /* 0x280 */
static const float lbl_1_rodata_284 = 230.0f; /* 0x284 */
static const float lbl_1_rodata_288 = 424.0f; /* 0x288 */
static const float lbl_1_rodata_28C = 151.0f; /* 0x28C */
static const double lbl_1_rodata_290 = 424.0; /* 0x290 */
static const double lbl_1_rodata_298 = 151.0; /* 0x298 */
static const float lbl_1_rodata_2A0 = 500.0f; /* 0x2A0 */
static const float lbl_1_rodata_2A4 = 1.3f; /* 0x2A4 */
static const float lbl_1_rodata_2A8 = 45.0f; /* 0x2A8 */
static const float lbl_1_rodata_2AC = -42.222218f; /* 0x2AC */
static const float lbl_1_rodata_2B0 = 34.0f; /* 0x2B0 */
static const float lbl_1_rodata_2B4 = 400.0f; /* 0x2B4 */
static const float lbl_1_rodata_2B8 = 300.0f; /* 0x2B8 */
static const double lbl_1_rodata_2C0 = 0.1; /* 0x2C0 */
static const double lbl_1_rodata_2C8 = 0.9; /* 0x2C8 */
static const double lbl_1_rodata_2D0 = 15.0; /* 0x2D0 */
static const float lbl_1_rodata_2D8 = 64.0f; /* 0x2D8 */
static const float lbl_1_rodata_2DC = -48.0f; /* 0x2DC */
static const float lbl_1_rodata_2E0 = -64.0f; /* 0x2E0 */
static const float lbl_1_rodata_2E4 = 24.0f; /* 0x2E4 */
static const float lbl_1_rodata_2E8 = 296.0f; /* 0x2E8 */
static const float lbl_1_rodata_2EC = 226.0f; /* 0x2EC */
static const float lbl_1_rodata_2F0 = 380.0f; /* 0x2F0 */
static const float lbl_1_rodata_2F4 = 152.0f; /* 0x2F4 */
static const float lbl_1_rodata_2F8 = 216.0f; /* 0x2F8 */
static const float lbl_1_rodata_2FC = 38.0f; /* 0x2FC */
static const float lbl_1_rodata_300 = 136.0f; /* 0x300 */
static const float lbl_1_rodata_304 = 18.0f; /* 0x304 */
static const float lbl_1_rodata_308 = 298.0f; /* 0x308 */
static const float lbl_1_rodata_30C = 0.9f; /* 0x30C */
static const float lbl_1_rodata_310 = 284.44446f; /* 0x310 */
static const float lbl_1_rodata_314 = 180.0f; /* 0x314 */
static const float lbl_1_rodata_318 = 250.0f; /* 0x318 */
static const float lbl_1_rodata_31C = 130.0f; /* 0x31C */
static const double lbl_1_rodata_320 = 300.0; /* 0x320 */
static const float lbl_1_rodata_328 = 188.0f; /* 0x328 */
static const float lbl_1_rodata_32C = 238.0f; /* 0x32C */
static const float lbl_1_rodata_330 = 338.0f; /* 0x330 */
static const float lbl_1_rodata_334 = 270.0f; /* 0x334 */
static const float lbl_1_rodata_338 = -68.0f; /* 0x338 */
static const float lbl_1_rodata_33C = -2.0f; /* 0x33C */
static const float lbl_1_rodata_340 = 600.0f; /* 0x340 */
static const float lbl_1_rodata_344 = 361.0f; /* 0x344 */
static const float lbl_1_rodata_348 = 540.0f; /* 0x348 */
static const float lbl_1_rodata_34C = 599.0f; /* 0x34C */
static const double lbl_1_rodata_350 = 288.0; /* 0x350 */
static const double lbl_1_rodata_358 = 640.0; /* 0x358 */
static const float lbl_1_rodata_360 = 210.0f; /* 0x360 */
static const double lbl_1_rodata_368 = 5.0; /* 0x368 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x74A gap_05_0000074A_bss (0x6): alignment gap */
/* 0x736 */ s16 lbl_1_bss_736[10];
/* 0x728 */ s16 lbl_1_bss_728[7];
/* 0x726 */ s16 lbl_1_bss_726;
/* 0x724 */ s16 lbl_1_bss_724;
/* 0x722 */ s16 lbl_1_bss_722;
/* 0x71C */ char lbl_1_bss_71C[0x6]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0x71A */ s16 lbl_1_bss_71A;
/* 0x718 */ s16 lbl_1_bss_718;
/* 0x716 */ s16 lbl_1_bss_716;
/* 0x714 */ s16 lbl_1_bss_714;
/* 0x70E */ s16 lbl_1_bss_70E[3];
/* 0x708 */ s16 lbl_1_bss_708[3];
/* 0x704 */ float lbl_1_bss_704;
/* 0x700 */ float lbl_1_bss_700;
/* 0x6FE */ s16 lbl_1_bss_6FE;
/* 0x6DE */ s16 lbl_1_bss_6DE[16];
/* 0x6D4 */ s16 lbl_1_bss_6D4[5];
/* 0x67C */ SDMACHINEMDL lbl_1_bss_67C[2];
/* 0x678 */ HUPROCESS *lbl_1_bss_678;
/* 0x620 */ HU3DCAMERA lbl_1_bss_620; /* struct copy of Hu3DCamera[3] */
/* 0x608 */ s8 lbl_1_bss_608[24]; /* fn_1_556C stores li -1: signed */
/* 0x606 */ s16 lbl_1_bss_606;
/* 0x604 */ s16 lbl_1_bss_604;
/* 0x600 */ ANIMDATA *lbl_1_bss_600; /* fn_1_6264: HuSprAnimRead result */
/* 0x5F6 */ s16 lbl_1_bss_5F6[5];
/* 0x5F4 */ s16 lbl_1_bss_5F4;
/* 0x5EA */ s16 lbl_1_bss_5EA[5];
/* 0x5E0 */ s16 lbl_1_bss_5E0[5];
/* 0x5DC */ ANIMDATA *lbl_1_bss_5DC;
/* 0x5D6 */ s16 lbl_1_bss_5D6[3];
/* 0x5D0 */ s16 lbl_1_bss_5D0[3];
/* 0x5C8 */ s16 lbl_1_bss_5C8[4];
/* 0x5C6 */ s16 lbl_1_bss_5C6;
/* 0x5C4 */ s16 lbl_1_bss_5C4;
/* 0x5BC */ s16 lbl_1_bss_5BC[4];
/* 0x5B8 */ float lbl_1_bss_5B8;
/* 0x5AC */ OMOBJMAN *lbl_1_bss_5AC[3]; /* only [0] is accessed (omInitObjMan) */
/* 0x58C */ s16 lbl_1_bss_58C[16];
/* 0x58A */ s16 lbl_1_bss_58A;
/* 0x584 */ s16 lbl_1_bss_584[3];
/* 0x570 */ s16 lbl_1_bss_570[10];
/* 0x56E */ s16 lbl_1_bss_56E;
/* 0x56C */ s16 lbl_1_bss_56C;
/* 0x56A gap_05_0000056A_bss (0x2): lbl_1_bss_568[1] */
/* 0x568 */ s16 lbl_1_bss_568[2]; /* [1] is accessed at +2 (dtk gap_05_0000056A) */

/* --- functions (reference order), .data placed before its first user --- */
/* 186 insns */
void fn_1_556C(void)
{
    s16 i;
    GWSDMACHINE *machine;

    for (i = 0; i < 2; i++) {
        machine = &GwSdCommon.machine[i];
        if (machine->charNo != -1) {
            Hu3DMotionTimeSet(lbl_1_bss_58C[i + 3], 61.0f);
            Hu3DMotionStartEndSet(lbl_1_bss_58C[i + 3], 61.0f, 240.0f);
            Hu3DModelAttrReset(lbl_1_bss_58C[i + 3], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(lbl_1_bss_58C[i + 3], HU3D_MOTATTR_LOOP);
            fn_1_44E4(&lbl_1_bss_67C[i], machine->partNo[0], machine->partNo[1], machine->partNo[3], 64);
            fn_1_4638(&lbl_1_bss_67C[i], 4);
            fn_1_4534(&lbl_1_bss_67C[i], 1450.0 * -sin(M_PI * (i * 60 + 60) / 180.0), 0.0f, 1450.0 * -cos(M_PI * (i * 60 + 60) / 180.0));
            fn_1_4590(&lbl_1_bss_67C[i], 0.0f, (i + 1) * 60 + 60, 0.0f);
        }
    }
    lbl_1_bss_608[0] = -1;
}

/* 0x1060 */ float lbl_1_data_1060[11] = { -22.0f, -38.0f, -26.0f, -33.0f, 0.0f, 0.0f, 0.0f, -16.0f, -15.0f, -38.0f, -22.0f };
/* 0x10A4 */ char *lbl_1_data_10A4[3] = {
    "chn_tl",
    "chn_tr",
    "chn_hover"
};
/* 0x10B0 */ OMCAMERAVIEW lbl_1_data_10B0[2] = { { { -433.0f, 200.0f, -250.0f }, { 0.0f, 60.0f, 0.0f }, 50.0f }, { { -433.0f, 200.0f, 250.0f }, { 0.0f, 120.0f, 0.0f }, 50.0f } };

/* 644 insns */
void fn_1_5854(s16 a0)
{
    HuVecF pos;
    HUWIN *win;
    GWSDMACHINE *machine;
    s16 i;
    s16 choice;

    sdWorkInt[7] = a0;
    fn_1_6264();
    win = &winData[lbl_1_bss_606];
    win->padMask = 1 << a0;
    win = &winData[lbl_1_bss_570[0]];
    win->padMask = 1 << a0;
    Hu3DModelAttrSet(lbl_1_bss_58C[(a0 ^ 1) + 3], HU3D_ATTR_DISPOFF);
    pos.x = 1000.0 * -sin(M_PI * (a0 * 60 + 60) / 180.0);
    pos.y = 90.0f;
    pos.z = 1000.0 * -cos(M_PI * (a0 * 60 + 60) / 180.0);
    pos.x += 170.0 * -sin(M_PI * (a0 * 60 + 150) / 180.0);
    pos.z += 170.0 * -cos(M_PI * (a0 * 60 + 150) / 180.0);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, a0 * 60 + 70, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.1f, 1.1f, 1.1f);
    machine = &GwSdCommon.machine[a0];
    if (omovlevtno == 2 || omovlevtno == 3) {
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        omCameraViewSetMulti(4, &lbl_1_data_10B0[a0]);
        goto next; /* evtno 2/3: straight into the garage menu (fn_1_73A8) */
    }
    if (machine->charNo == -1) {
        HuAudFXPlay(1289);
        Hu3DMotionTimeSet(lbl_1_bss_58C[a0 + 3], 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_58C[a0 + 3], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_58C[a0 + 3], HU3D_MOTATTR_LOOP);
        HuPrcSleep(60);
        Hu3DMotionStartEndSet(lbl_1_bss_58C[a0 + 3], 61.0f, 240.0f);
    }
    omCameraViewMoveMulti(4, &lbl_1_data_10B0[a0], 60, 0);
    HuPrcSleep(60);
    for (i = 1; i <= 20; i++) {
        pos.y = 90.0 + 500.0 * (1.0 - sin(M_PI * (90.0 * (i / 20.0)) / 180.0));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    HuWinExOpen(lbl_1_bss_606);
    if (GwSdCommon.partFlag[0] == 0 || GwSdCommon.partFlag[1] == 0 || GwSdCommon.partFlag[2] == 0 || GwSdCommon.partFlag[3] == 0) {
        HuWinMesSet(lbl_1_bss_606, 0x190074);
        HuWinMesWait(lbl_1_bss_606);
        HuWinExClose(lbl_1_bss_606);
        goto end;
    }
    HuWinMesSet(lbl_1_bss_606, a0 + 0x190009);
    HuAudFXPlay(751);
    HuWinMesWait(lbl_1_bss_606);
    do {
        if (machine->charNo == -1) {
            HuWinMesSet(lbl_1_bss_606, 0x19000D);
            HuWinMesWait(lbl_1_bss_606);
            choice = HuWinChoiceGet(lbl_1_bss_606, -1);
            if (choice != 0) {
                HuWinExClose(lbl_1_bss_606);
                goto end;
            }
            HuWinExClose(lbl_1_bss_606);
            if (fn_1_8954(a0, 0) == 0) {
                goto end;
            }
            HuAudJinglePlay(126);
            HuWinExOpen(lbl_1_bss_606);
            HuWinInsertMesSet(lbl_1_bss_606, MESSNUM_PTR(&lbl_1_bss_67C[a0]), 0);
            HuWinMesSet(lbl_1_bss_606, 0x19001E);
            for (i = 0; i < 155; i++) {
                HuPrcVSleep();
            }
            HuAudSStreamPauseFadeOut(0, 0, 1000);
            HuWinMesWait(lbl_1_bss_606);
            fn_1_C360(a0, lbl_1_bss_606);
        }
    next:;
    } while (fn_1_73A8(a0));
    HuWinExClose(lbl_1_bss_606);
end:
    win = &winData[lbl_1_bss_570[0]];
    win->padMask = 7;
    for (i = 1; i <= 20; i++) {
        pos.y = 90.0 + 500.0 * (1.0 - cos(M_PI * (90.0 * (i / 20.0)) / 180.0));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    if (machine->charNo == -1) {
        HuAudFXPlay(1289);
        Hu3DMotionTimeSet(lbl_1_bss_58C[a0 + 3], 601.0f);
        Hu3DModelAttrReset(lbl_1_bss_58C[a0 + 3], HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(lbl_1_bss_58C[a0 + 3], 0.0f, 640.0f);
    }
    Hu3DModelPosSet(lbl_1_bss_58A, 0.0f, 195.0f, -1155.0f);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.8f, 1.8f, 1.8f);
    fn_1_7190();
    Hu3DModelAttrReset(lbl_1_bss_58C[(a0 ^ 1) + 3], HU3D_ATTR_DISPOFF);
}

/* 0x10E8 */ float lbl_1_data_10E8[7] = { 0.0f, 70.0f, 0.0f, -30.0f, 0.0f, 0.0f, 5300.0f };
/* 0x1104 */ float lbl_1_data_1104[7] = { 0.0f, 120.0f, 0.0f, -30.0f, 0.0f, 0.0f, 7500.0f };
/* 0x1120 */ float lbl_1_data_1120[7] = { 0.0f, 80.0f, 0.0f, -30.0f, 0.0f, 0.0f, 6500.0f };
/* 0x113C */ float lbl_1_data_113C[7] = { 0.0f, 70.0f, 0.0f, -30.0f, 0.0f, 0.0f, 6800.0f };

/* 971 insns */
void fn_1_6264(void)
{
    HUWINID winId;
    HU3DMODELID modelId;
    ANIMDATA *anim;
    s16 i;
    HUSPRID sprId;
    HUSPRGRPID grpId;

    Hu3DModelAttrSet(lbl_1_bss_58C[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
    lbl_1_bss_606 = HuWinExCreateFrame(156.0f, 344.0f, 400, 94, -1, 1);
    HuWinMesPalSet(lbl_1_bss_606, 7, 0, 0, 0);
    HuWinMesSpeedSet(lbl_1_bss_606, 0);
    HuWinPriSet(lbl_1_bss_606, 50);
    winId = HuWinCreate(-10000.0f, 310.0f, 560, 42, 0);
    lbl_1_bss_604 = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x20004);
    HuWinDispOff(winId);
    grpId = HuSprGrpCreate(23);
    lbl_1_bss_718 = grpId;
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 29)), 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 0.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 30)), 100, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 0.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 31)), 100, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprPosSet(grpId, 2, 0.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 32)), 100, 0);
    HuSprGrpMemberSet(grpId, 3, sprId);
    HuSprPosSet(grpId, 3, 0.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 38)), 55, 0);
    HuSprGrpMemberSet(grpId, 4, sprId);
    HuSprPosSet(grpId, 4, 0.0f, -1000.0f);
    HuSprDrawNoSet(grpId, 4, 64);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 36)), 50, 0);
    HuSprGrpMemberSet(grpId, 5, sprId);
    HuSprPosSet(grpId, 5, 0.0f, -1000.0f);
    HuSprDrawNoSet(grpId, 5, 64);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 33)), 50, 0);
    HuSprGrpMemberSet(grpId, 6, sprId);
    HuSprPosSet(grpId, 6, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 34)), 50, 0);
    HuSprGrpMemberSet(grpId, 7, sprId);
    HuSprPosSet(grpId, 7, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 35)), 50, 0);
    HuSprGrpMemberSet(grpId, 8, sprId);
    HuSprPosSet(grpId, 8, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 39)), 50, 0);
    HuSprGrpMemberSet(grpId, 9, sprId);
    HuSprPosSet(grpId, 9, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 40)), 50, 0);
    HuSprGrpMemberSet(grpId, 10, sprId);
    HuSprPosSet(grpId, 10, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 41)), 50, 0);
    HuSprGrpMemberSet(grpId, 11, sprId);
    HuSprPosSet(grpId, 11, 352.0f, -1000.0f);
    anim = HuSprAnimDataRead(DATANUM(DATA_sdroom, 47));
    sprId = HuSprCreate(anim, 20, 0);
    HuSprGrpMemberSet(grpId, 12, sprId);
    HuSprPosSet(grpId, 12, 352.0f, -1000.0f);
    HuSprColorSet(grpId, 12, 0, 0, 0);
    HuSprTPLvlSet(grpId, 12, 0.5f);
    sprId = HuSprCreate(anim, 20, 0);
    HuSprGrpMemberSet(grpId, 13, sprId);
    HuSprPosSet(grpId, 13, 352.0f, -1000.0f);
    HuSprColorSet(grpId, 13, 0, 0, 0);
    HuSprTPLvlSet(grpId, 13, 0.5f);
    sprId = HuSprCreate(anim, 20, 0);
    HuSprGrpMemberSet(grpId, 14, sprId);
    HuSprPosSet(grpId, 14, 352.0f, -1000.0f);
    HuSprColorSet(grpId, 14, 0, 0, 0);
    HuSprTPLvlSet(grpId, 14, 0.5f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 37)), 50, 0);
    HuSprGrpMemberSet(grpId, 15, sprId);
    HuSprPosSet(grpId, 15, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 48)), 50, 0);
    HuSprGrpMemberSet(grpId, 16, sprId);
    HuSprPosSet(grpId, 16, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 49)), 50, 0);
    HuSprGrpMemberSet(grpId, 17, sprId);
    HuSprPosSet(grpId, 17, 352.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 50)), 20, 0);
    HuSprGrpMemberSet(grpId, 18, sprId);
    HuSprPosSet(grpId, 18, 288.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 51)), 20, 0);
    HuSprGrpMemberSet(grpId, 19, sprId);
    HuSprPosSet(grpId, 19, 288.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 43)), 50, 0);
    HuSprGrpMemberSet(grpId, 20, sprId);
    HuSprPosSet(grpId, 20, 288.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 44)), 50, 0);
    HuSprGrpMemberSet(grpId, 21, sprId);
    HuSprPosSet(grpId, 21, 288.0f, -1000.0f);
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 45)), 50, 0);
    HuSprGrpMemberSet(grpId, 22, sprId);
    HuSprPosSet(grpId, 22, 288.0f, -1000.0f);
    grpId = HuSprGrpCreate(9);
    lbl_1_bss_716 = grpId;
    for (i = 0; i < 8; i++) {
        sprId = HuSprCreate(HuSprAnimDataRead(i + DATANUM(DATA_sdroom, 52)), 30, 0);
        HuSprGrpMemberSet(grpId, i, sprId);
        HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(grpId, i, 0.0f, -1000.0f);
    }
    grpId = HuSprGrpCreate(15);
    lbl_1_bss_714 = grpId;
    sprId = HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_sdroom, 60)), 100, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 0.0f, 0.0f);
    anim = HuSprAnimDataRead(DATANUM(DATA_sdroom, 61));
    for (i = 0; i < 11; i++) {
        sprId = HuSprCreate(anim, 50, i);
        HuSprGrpMemberSet(grpId, i + 1, sprId);
        HuSprPosSet(grpId, i + 1, 0.0f, 0.0f);
    }
    anim = HuSprAnimDataRead(DATANUM(DATA_sdroom, 64));
    for (i = 0; i < 3; i++) {
        sprId = HuSprCreate(anim, 40, i);
        HuSprGrpMemberSet(grpId, i + 12, sprId);
        HuSprPosSet(grpId, i + 12, 0.0f, 0.0f);
    }
    for (i = 0; i < 15; i++) {
        HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpDrawNoSet(grpId, 64);
    anim = HuSprAnimDataRead(DATANUM(DATA_sdroom, 63));
    lbl_1_bss_600 = anim;
    for (i = 0; i < 3; i++) {
        modelId = Hu3DModelCreateData(DATANUM(DATA_sdroom, 62));
        lbl_1_bss_70E[i] = modelId;
        lbl_1_bss_708[i] = Hu3DAnimCreate(anim, modelId, "dummy");
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelCameraSet(modelId, 4);
        Hu3DModelLayerSet(modelId, 6);
        Hu3DModelRotSet(modelId, 0.0f, (sdWorkInt[7] + 1) * 60, 0.0f);
        Hu3DAnimBankSet(lbl_1_bss_708[i], 0);
    }
    Hu3DCameraPerspectiveSet(8, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(8, -3.5555496f, 72.0f, 256.0f, 192.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 22, 76, 204, 184);
    omCameraViewSetMulti(8, (OMCAMERAVIEW *)lbl_1_data_10E8);
    lbl_1_bss_5B8 = 0.0f;
    lbl_1_bss_5C6 = 0;
}

/* 66 insns */
void fn_1_7190(void)
{
    s16 i;

    Hu3DModelAttrReset(lbl_1_bss_58C[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
    HuSprGrpKill(lbl_1_bss_716);
    HuSprGrpKill(lbl_1_bss_718);
    HuSprGrpKill(lbl_1_bss_714);
    HuWinKill(lbl_1_bss_606);
    HuWinKill(lbl_1_bss_604);
    for (i = 0; i < 3; i++) {
        Hu3DModelKill(lbl_1_bss_70E[i]);
    }
    HuMemDirectFree(lbl_1_bss_600);
}

/* 34 insns */
void fn_1_7298(void)
{
    s16 i;
    GWSDMACHINE *machine;

    for (i = 0; i < 2; i++) {
        machine = &GwSdCommon.machine[i];
        if (machine->charNo != -1) {
            fn_1_46C4(&lbl_1_bss_67C[i], 1);
        }
    }
}

/* 34 insns */
void fn_1_7320(void)
{
    s16 i;
    GWSDMACHINE *machine;

    for (i = 0; i < 2; i++) {
        machine = &GwSdCommon.machine[i];
        if (machine->charNo != -1) {
            fn_1_46C4(&lbl_1_bss_67C[i], 0);
        }
    }
}

/* 1239 insns */
s32 fn_1_73A8(s16 a0)
{
    SDMACHINEMDL mdl;
    float scale;
    s16 i;
    s16 cursor;
    s16 j;
    GWSDMACHINE *machine;
    HUPROCESS *proc;
    s32 result;
    s16 choice;

    cursor = 0;
    result = 0;
    for (i = 0; i < 4; i++) {
        mdl.partNo[i] = -1;
    }
    machine = &GwSdCommon.machine[a0];
    fn_1_4D0C(13);
    if (omovlevtno == 2 || omovlevtno == 3) {
        HuSprPosSet(lbl_1_bss_718, 0, 96.0f, 128.0f);
        HuSprPosSet(lbl_1_bss_718, 1, 224.0f, 128.0f);
        HuSprPosSet(lbl_1_bss_718, 2, 352.0f, 128.0f);
        HuSprPosSet(lbl_1_bss_718, 3, 480.0f, 128.0f);
        for (i = 0; i < 4; i++) {
            HuSprScaleSet(lbl_1_bss_718, i, 0.0f, 0.0f);
        }
        goto parts; /* evtno 2/3: back from a VS battle, reopen the parts menu */
    }
    HuWinMesSet(lbl_1_bss_606, 0x19000E);
    HuWinMesWait(lbl_1_bss_606);
    for (i = 0; i < 4; i++) {
        HuSprScaleSet(lbl_1_bss_718, i, 0.8f, 0.8f);
    }
    for (i = 1; i <= 20; i++) {
        scale = 128.0 - 500.0 * (1.0 - sin(M_PI * (90.0 * (i / 20.0)) / 180.0));
        HuSprPosSet(lbl_1_bss_718, 0, 96.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 1, 224.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 2, 352.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 3, 480.0f, scale);
        HuPrcVSleep();
    }
    for (i = 1; i <= 10; i++) {
        scale = 0.8 + 0.2 * sin(M_PI * (90.0 * (i / 10.0)) / 180.0);
        HuSprScaleSet(lbl_1_bss_718, cursor, scale, scale);
        HuPrcVSleep();
    }
    HuWinMesSet(lbl_1_bss_606, cursor + 0x19000F);
    HuWinMesWait(lbl_1_bss_606);
    HuWinMesSet(lbl_1_bss_604, 0x20004);
    HuWinDispOn(lbl_1_bss_604);
    while (1) {
        if ((fn_1_507C(1 << a0) & 1) && cursor > 0) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                scale = 0.8 + 0.2 * cos(M_PI * (90.0 * (i / 10.0)) / 180.0);
                HuSprScaleSet(lbl_1_bss_718, cursor, scale, scale);
                scale = 0.8 + 0.2 * sin(M_PI * (90.0 * (i / 10.0)) / 180.0);
                HuSprScaleSet(lbl_1_bss_718, cursor - 1, scale, scale);
                HuPrcVSleep();
            }
            cursor--;
            HuWinMesSet(lbl_1_bss_606, cursor + 0x19000F);
            HuWinMesWait(lbl_1_bss_606);
        } else if ((fn_1_507C(1 << a0) & 2) && cursor < 3) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                scale = 0.8 + 0.2 * cos(M_PI * (90.0 * (i / 10.0)) / 180.0);
                HuSprScaleSet(lbl_1_bss_718, cursor, scale, scale);
                scale = 0.8 + 0.2 * sin(M_PI * (90.0 * (i / 10.0)) / 180.0);
                HuSprScaleSet(lbl_1_bss_718, cursor + 1, scale, scale);
                HuPrcVSleep();
            }
            cursor++;
            HuWinMesSet(lbl_1_bss_606, cursor + 0x19000F);
            HuWinMesWait(lbl_1_bss_606);
        } else if ((fn_1_4FD0(1 << a0) & 0x100) && cursor == 3) {
            HuAudFXPlay(1);
            HuWinDispOff(lbl_1_bss_604);
            HuWinMesSet(lbl_1_bss_606, 0x190014);
            HuWinMesWait(lbl_1_bss_606);
            choice = HuWinChoiceGet(lbl_1_bss_606, -1);
            if (choice == 0) {
                HuAudFXPlay(1293);
                for (i = 1; i <= 30; i++) {
                    scale = cos(M_PI * (90.0 * (i / 30.0)) / 180.0);
                    Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, 1.0f, scale);
                    Hu3DModelRotSet(lbl_1_bss_67C[a0].bodyMdl, 0.0f, 600.0 * (1.0 - scale) + ((a0 + 1) * 60 + 60), 0.0f);
                    HuPrcVSleep();
                }
                fn_1_4724(&lbl_1_bss_67C[a0]);
                machine->charNo = -1;
                result = 1;
                break;
            }
            HuWinMesSet(lbl_1_bss_606, cursor + 0x19000F);
            HuWinMesWait(lbl_1_bss_606);
            HuWinMesSet(lbl_1_bss_604, 0x20004);
            HuWinDispOn(lbl_1_bss_604);
        } else if (fn_1_4FD0(1 << a0) & 0x100) {
            HuAudFXPlay(1);
            HuWinDispOff(lbl_1_bss_604);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                for (j = 0; j < 4; j++) {
                    if (cursor == j) {
                        HuSprScaleSet(lbl_1_bss_718, j, scale, scale);
                    } else {
                        HuSprScaleSet(lbl_1_bss_718, j, 0.8 * scale, 0.8 * scale);
                    }
                }
                HuPrcVSleep();
            }
            switch (cursor) {
                case 0:
                    HuWinExClose(lbl_1_bss_606);
                    HuAudFXPlay(1293);
                    for (i = 1; i <= 30; i++) {
                        scale = cos(M_PI * (90.0 * (i / 30.0)) / 180.0);
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, 1.0f, scale);
                        Hu3DModelRotSet(lbl_1_bss_67C[a0].bodyMdl, 0.0f, 600.0 * (1.0 - scale) + ((a0 + 1) * 60 + 60), 0.0f);
                        HuPrcVSleep();
                    }
                    fn_1_4724(&lbl_1_bss_67C[a0]);
                    if (fn_1_8954(a0, 1) == 0) {
                        fn_1_44E4(&lbl_1_bss_67C[a0], machine->partNo[0], machine->partNo[1], machine->partNo[3], 64);
                        fn_1_8704(a0);
                        for (i = 1; i <= 30; i++) {
                            scale = sin(M_PI * (90.0 * (i / 30.0)) / 180.0);
                            Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, 1.0f, scale);
                            Hu3DModelRotSet(lbl_1_bss_67C[a0].bodyMdl, 0.0f, 600.0 * (1.0 - scale) + ((a0 + 1) * 60 + 60), 0.0f);
                            HuPrcVSleep();
                        }
                        HuWinExOpen(lbl_1_bss_606);
                    } else {
                        HuWinExOpen(lbl_1_bss_606);
                        fn_1_C360(a0, lbl_1_bss_606);
                    }
                    break;
                case 1:
                    HuWinExClose(lbl_1_bss_606);
                    lbl_1_bss_6D4[0] = machine->partNo[0];
                    lbl_1_bss_6D4[1] = machine->partNo[1];
                    lbl_1_bss_6D4[2] = machine->partNo[2];
                    lbl_1_bss_6D4[3] = machine->partNo[3];
                    lbl_1_bss_6D4[4] = machine->charNo;
                    strcpy(mdl.name, machine->name);
                    mdl.partNo[0] = -1;
                    proc = HuPrcChildCreate(fn_1_88BC, 1000, 0x1000, 0, HuPrcCurrentGet());
                    proc->property = &mdl;
                    fn_1_AFCC(&mdl, 0x2000B);
                    while (!(fn_1_4FD0(1 << a0) & 0x200)) {
                        HuPrcVSleep();
                    }
                    HuAudFXPlay(3);
                    HuPrcKill(proc);
                    fn_1_B8E8(&mdl);
                    fn_1_4724(&mdl);
                    HuWinExOpen(lbl_1_bss_606);
                    break;
                case 2:
                parts:
                    fn_1_C538(a0);
                    break;
            }
            for (i = 1; i <= 10; i++) {
                scale = i / 10.0;
                for (j = 0; j < 4; j++) {
                    if (cursor == j) {
                        HuSprScaleSet(lbl_1_bss_718, j, scale, scale);
                    } else {
                        HuSprScaleSet(lbl_1_bss_718, j, 0.8 * scale, 0.8 * scale);
                    }
                }
                HuPrcVSleep();
            }
            HuWinMesSet(lbl_1_bss_606, cursor + 0x19000F);
            HuWinMesWait(lbl_1_bss_606);
            HuWinMesSet(lbl_1_bss_604, 0x20004);
            HuWinDispOn(lbl_1_bss_604);
        } else if (fn_1_4FD0(1 << a0) & 0x200) {
            HuAudFXPlay(3);
            HuWinDispOff(lbl_1_bss_604);
            break;
        }
        HuPrcVSleep();
    }
    for (i = 1; i <= 20; i++) {
        scale = 128.0 - 500.0 * (1.0 - cos(M_PI * (90.0 * (i / 20.0)) / 180.0));
        HuSprPosSet(lbl_1_bss_718, 0, 96.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 1, 224.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 2, 352.0f, scale);
        HuSprPosSet(lbl_1_bss_718, 3, 480.0f, scale);
        HuPrcVSleep();
    }
    fn_1_4E14();
    return result;
}

/* 110 insns */
void fn_1_8704(s16 a0)
{
    fn_1_4638(&lbl_1_bss_67C[a0], 4);
    fn_1_4534(&lbl_1_bss_67C[a0], 1450.0 * -sin(M_PI * (a0 * 60 + 60) / 180.0), 0.0f, 1450.0 * -cos(M_PI * (a0 * 60 + 60) / 180.0));
    fn_1_4590(&lbl_1_bss_67C[a0], 0.0f, (a0 + 1) * 60 + 60, 0.0f);
}

/* 38 insns */
void fn_1_88BC(void)
{
    s16 rot;
    HUPROCESS *proc;
    SDMACHINEMDL *machine;

    rot = 0;
    proc = HuPrcCurrentGet();
    machine = proc->property;
    while (1) {
        if (machine->partNo[0] >= 0) {
            Hu3DModelRotSet(machine->bodyMdl, 0.0f, rot, 0.0f);
            rot++;
            if (rot > 360) {
                rot -= 360;
            }
        }
        HuPrcVSleep();
    }
}

/* 1430 insns */
s32 fn_1_8954(s16 a0, s16 a1)
{
    s16 partNo[5];
    float scale;
    float posZ;
    s16 i;
    GWSDMACHINE *gw;
    s16 cursor;
    s16 dir;
    s32 cancelF;
    s16 count;
    s16 choice;

    cancelF = 0;
    Hu3DCameraPerspectiveSet(HU3D_CAM3, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM3, -3.5555496f, 72.0f, 256.0f, 192.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM3, 22, 76, 204, 184);
    omCameraViewSetMulti(HU3D_CAM3, (OMCAMERAVIEW *)lbl_1_data_10E8);
    lbl_1_bss_724 = 0;
    fn_1_4D0C(13);
    lbl_1_bss_726 = lbl_1_bss_722 = cursor = 0;
    gw = &GwSdCommon.machine[a0];
    if (gw->charNo != -1) {
        for (i = 0; i < 4; i++) {
            partNo[i] = gw->partNo[i];
        }
        partNo[i] = gw->charNo;
    } else {
        for (i = 0; i < 5; i++) {
            partNo[i] = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_67C[a0].partNo[i] = -1;
    }
    if (a1 == 0) {
        for (i = 0; i < 5; i++) {
            lbl_1_bss_6D4[i] = -1;
        }
    } else {
        lbl_1_bss_6D4[0] = gw->partNo[0];
        lbl_1_bss_6D4[1] = gw->partNo[1];
        lbl_1_bss_6D4[2] = gw->partNo[2];
        lbl_1_bss_6D4[3] = gw->partNo[3];
        lbl_1_bss_6D4[4] = gw->charNo;
    }
    fn_1_9FAC(a0);
    fn_1_A464();
    lbl_1_bss_724 = fn_1_AF04(lbl_1_bss_726, partNo[0]);
    lbl_1_bss_722 = (lbl_1_bss_724 > 4) ? lbl_1_bss_724 - 4 : 0;
    cursor = lbl_1_bss_724 - lbl_1_bss_722;
    OSReport("top:%d,idx:%d\n", lbl_1_bss_722, lbl_1_bss_724);
    fn_1_AC08(214.0f, 72.0f);
    fn_1_A868(lbl_1_bss_726, lbl_1_bss_722);
    if (a1 == 1) {
        fn_1_AE4C(a0);
        for (i = 1; i <= 10; i++) {
            scale = HuSin(90.0 * (i / 10.0));
            Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
            HuPrcVSleep();
        }
    }
    HuWinMesSet(lbl_1_bss_728[0], 0x190027);
    HuWinDispOn(lbl_1_bss_728[0]);
    while (1) {
        dir = 0;
        if (fn_1_507C(1 << a0) & PAD_BUTTON_UP) {
            cursor--;
            dir = -1;
            if (cursor < 0) {
                if (lbl_1_bss_722 != 0) {
                    lbl_1_bss_722--;
                } else {
                    dir = 0;
                }
                cursor = 0;
            }
        } else if (fn_1_507C(1 << a0) & PAD_BUTTON_DOWN) {
            cursor++;
            dir = 1;
            if (cursor + lbl_1_bss_722 < lbl_1_bss_6FE) {
                if (cursor >= 5) {
                    if (lbl_1_bss_722 + 5 < lbl_1_bss_6FE) {
                        lbl_1_bss_722++;
                    } else {
                        dir = 0;
                    }
                    cursor = 4;
                }
            } else {
                dir = 0;
                cursor--;
            }
        } else if (fn_1_4FD0(1 << a0) & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            lbl_1_bss_726--;
            if (lbl_1_bss_726 >= 0) {
                fn_1_4724(&lbl_1_bss_67C[a0]);
                if (a1 == 0) {
                    lbl_1_bss_6D4[lbl_1_bss_726] = -1;
                }
                if (lbl_1_bss_726 < 4) {
                    lbl_1_bss_67C[a0].partNo[lbl_1_bss_726] = -1;
                }
                fn_1_AE4C(a0);
            }
            HuAudFXPlay(1292);
            lbl_1_bss_724 = fn_1_AF04(lbl_1_bss_726, partNo[lbl_1_bss_726]);
            lbl_1_bss_722 = (lbl_1_bss_724 > 4) ? lbl_1_bss_724 - 4 : 0;
            cursor = lbl_1_bss_724 - lbl_1_bss_722;
            if (lbl_1_bss_726 < 0) {
                if (a1 == 1) {
                    for (i = 1; i <= 10; i++) {
                        scale = HuCos(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
                        HuPrcVSleep();
                    }
                }
                fn_1_A55C();
                cancelF = 1;
                break;
            }
            dir = -10;
        } else if (fn_1_4FD0(1 << a0) & PAD_BUTTON_A) {
            HuAudFXPlay(1);
            i = count = 0;
            for (; i < lbl_1_data_4F4[lbl_1_bss_726]; i++) {
                if (fn_1_3EC0(lbl_1_bss_726, i)) {
                    if (count == lbl_1_bss_724) {
                        break;
                    }
                    count++;
                }
            }
            partNo[lbl_1_bss_726] = i;
            lbl_1_bss_6D4[lbl_1_bss_726] = i;
            HuAudFXPlay(1291);
            lbl_1_bss_6D4[4] = -1;
            fn_1_AE4C(a0);
            lbl_1_bss_726++;
            lbl_1_bss_724 = fn_1_AF04(lbl_1_bss_726, partNo[lbl_1_bss_726]);
            lbl_1_bss_722 = (lbl_1_bss_724 > 4) ? lbl_1_bss_724 - 4 : 0;
            cursor = lbl_1_bss_724 - lbl_1_bss_722;
            if (lbl_1_bss_726 >= 4) {
                if (a1 == 0) {
                    for (i = 1; i <= 10; i++) {
                        scale = HuCos(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
                        HuPrcVSleep();
                    }
                    fn_1_A55C();
                    omCameraViewSetMulti(HU3D_CAM3, (OMCAMERAVIEW *)lbl_1_data_10E8);
                    do {
                        if (NameEnterMain(lbl_1_bss_67C[a0].name, (s16)(1 << a0)) == 0) {
                            goto nameCancel;
                        }
                        fn_1_AFCC(&lbl_1_bss_67C[a0], 0);
                        HuWinExOpen(lbl_1_bss_570[0]);
                        HuWinMesSet(lbl_1_bss_570[0], 0x19001D);
                        HuWinMesWait(lbl_1_bss_570[0]);
                        choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
                        HuWinExClose(lbl_1_bss_570[0]);
                        fn_1_B8E8(&lbl_1_bss_67C[a0]);
                    } while (choice != 0);
                    cancelF = 0;
                    break;
                nameCancel:
                    lbl_1_bss_726 = 3;
                    lbl_1_bss_724 = fn_1_AF04(lbl_1_bss_726, partNo[lbl_1_bss_726]);
                    lbl_1_bss_722 = (lbl_1_bss_724 > 4) ? lbl_1_bss_724 - 4 : 0;
                    cursor = lbl_1_bss_724 - lbl_1_bss_722;
                    fn_1_A464();
                    fn_1_A868(lbl_1_bss_726, lbl_1_bss_722);
                    fn_1_4724(&lbl_1_bss_67C[a0]);
                    if (a1 == 0) {
                        lbl_1_bss_6D4[lbl_1_bss_726] = -1;
                    }
                    fn_1_AE4C(a0);
                    for (i = 1; i <= 10; i++) {
                        scale = HuSin(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
                        HuPrcVSleep();
                    }
                } else {
                    strcpy(lbl_1_bss_67C[a0].name, GwSdCommon.machine[a0].name);
                    for (i = 1; i <= 10; i++) {
                        scale = HuCos(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
                        HuPrcVSleep();
                    }
                    fn_1_A55C();
                    omCameraViewSetMulti(HU3D_CAM3, (OMCAMERAVIEW *)lbl_1_data_10E8);
                    fn_1_AFCC(&lbl_1_bss_67C[a0], 0);
                    HuWinExOpen(lbl_1_bss_570[0]);
                    HuWinMesSet(lbl_1_bss_570[0], 0x19001D);
                    HuWinMesWait(lbl_1_bss_570[0]);
                    choice = HuWinChoiceGet(lbl_1_bss_570[0], -1);
                    HuWinExClose(lbl_1_bss_570[0]);
                    fn_1_B8E8(&lbl_1_bss_67C[a0]);
                    if (choice == 0) {
                        cancelF = 0;
                        break;
                    }
                    lbl_1_bss_726 = 3;
                    lbl_1_bss_724 = fn_1_AF04(lbl_1_bss_726, partNo[lbl_1_bss_726]);
                    lbl_1_bss_722 = (lbl_1_bss_724 > 4) ? lbl_1_bss_724 - 4 : 0;
                    cursor = lbl_1_bss_724 - lbl_1_bss_722;
                    fn_1_A464();
                    fn_1_A868(lbl_1_bss_726, lbl_1_bss_722);
                    fn_1_4724(&lbl_1_bss_67C[a0]);
                    fn_1_AE4C(a0);
                    for (i = 1; i <= 10; i++) {
                        scale = HuSin(90.0 * (i / 10.0));
                        Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, scale, scale);
                        HuPrcVSleep();
                    }
                }
            }
            dir = 10;
        }
        if (dir != 0) {
            HuAudFXPlay(0);
            lbl_1_bss_724 = lbl_1_bss_722 + cursor;
            fn_1_A868(lbl_1_bss_726, lbl_1_bss_722);
            fn_1_A704(lbl_1_bss_728[5], lbl_1_bss_726);
            HuWinMesSet(lbl_1_bss_728[0], lbl_1_bss_726 + 0x190027);
            HuWinMesSet(lbl_1_bss_728[2], 0x20019);
            HuWinPosSet(lbl_1_bss_728[2], 16.0f, 354.0f);
        }
        CZoomM[3] += HuPadTrigL[a0] / 2;
        CZoomM[3] -= HuPadTrigR[a0] / 2;
        if (CZoomM[3] < 3000.0f) {
            CZoomM[3] = 3000.0f;
        }
        if (CZoomM[3] > 7000.0f) {
            CZoomM[3] = 7000.0f;
        }
        HuPrcVSleep();
    }
    fn_1_4724(&lbl_1_bss_67C[a0]);
    HuPrcKill(lbl_1_bss_678);
    if (cancelF == 0) {
        if (a1 == 0) {
            HuAudSStreamPause(0, TRUE);
        }
        gw = &GwSdCommon.machine[a0];
        for (i = 0; i < 4; i++) {
            gw->partNo[i] = lbl_1_bss_6D4[i];
        }
        gw->charNo = 0x40;
        strcpy(gw->name, lbl_1_bss_67C[a0].name);
        fn_1_44E4(&lbl_1_bss_67C[a0], lbl_1_bss_6D4[0], lbl_1_bss_6D4[1], lbl_1_bss_6D4[3], lbl_1_bss_6D4[4]);
        fn_1_4638(&lbl_1_bss_67C[a0], HU3D_CAM2);
        posZ = 1450.0 * -HuCos(a0 * 60 + 60);
        fn_1_4534(&lbl_1_bss_67C[a0], 1450.0 * -HuSin(a0 * 60 + 60), 0.0f, posZ);
        HuAudFXPlay(1290);
        for (i = 1; i <= 30; i++) {
            scale = HuSin(90.0 * (i / 30.0));
            Hu3DModelScaleSet(lbl_1_bss_67C[a0].bodyMdl, scale, 1.0f, scale);
            Hu3DModelRotSet(lbl_1_bss_67C[a0].bodyMdl, 0.0f, 600.0 * (1.0 - scale) + ((a0 + 1) * 60 + 60), 0.0f);
            HuPrcVSleep();
        }
    }
    fn_1_4E14();
    fn_1_A63C();
    HuDataDirClose(DATANUM(DATA_sd00, 0));
    if (cancelF) {
        return 0;
    } else {
        return 1;
    }
}

/* 302 insns */
void fn_1_9FAC(s16 a0)
{
    HUWINID winId;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s16 i;
    ANIMDATA *anim;

    winPrio = 1000;
    winId = HuWinCreate(16.0f, 32.0f, 320, 40, 0);
    lbl_1_bss_728[0] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinDispOff(winId);
    winId = HuWinCreate(16.0f, 354.0f, 320, 88, 0);
    lbl_1_bss_728[2] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x20019);
    HuWinDispOff(lbl_1_bss_728[2]);
    winId = HuWinExCreate(16.0f, 72.0f, 192, 192, -1);
    lbl_1_bss_728[3] = winId;
    HuWinDrawNoSet(winId, 64);
    HuWinMesSpeedSet(winId, 0);
    winId = HuWinExCreate(214.0f, 72.0f, 346, 208, -1);
    lbl_1_bss_728[4] = winId;
    HuWinMesSpeedSet(winId, 0);
    winId = HuWinCreate(332.0f, 240.0f, 126, 48, 0);
    lbl_1_bss_728[5] = winId;
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSpeedSet(winId, 0);
    fn_1_A704(winId, lbl_1_bss_726);
    HuWinDispOff(lbl_1_bss_728[5]);
    winId = HuWinExCreate(214.0f, 280.0f, 346, 146, -1);
    lbl_1_bss_728[6] = winId;
    HuWinMesSpeedSet(winId, 0);
    for (i = 0; i < 10; i++) {
        winId = HuWinCreate(0.0f, 0.0f, 406, 40, 0);
        lbl_1_bss_736[i] = winId;
        HuWinBGTPLvlSet(winId, 0.0f);
        HuWinMesSpeedSet(winId, 0);
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_win, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    grpId = HuSprGrpCreate(3);
    lbl_1_bss_71A = grpId;
    sprId = HuSprCreate(anim, 100, 19);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 320.0f, 240.0f);
    HuSprScaleSet(grpId, 0, 1.0f, -1.0f);
    sprId = HuSprCreate(anim, 100, 19);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 320.0f, 240.0f);
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_win, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    sprId = HuSprCreate(anim, 100, 0);
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprPosSet(grpId, 2, 320.0f, 240.0f);
    HuSprGrpDrawNoSet(grpId, 0);
    lbl_1_bss_678 = HuPrcChildCreate(fn_1_88BC, 1000, 0x1000, 0, HuPrcCurrentGet());
    lbl_1_bss_678->property = &lbl_1_bss_67C[a0];
    HuSprGrpPosSet(lbl_1_bss_71A, -1000.0f, 0.0f);
}

/* 62 insns */
void fn_1_A464(void)
{
    s16 i;

    HuSprAttrSet(lbl_1_bss_71A, 2, HUSPR_ATTR_DISPOFF);
    HuWinExOpen(lbl_1_bss_728[3]);
    HuWinExOpen(lbl_1_bss_728[4]);
    HuWinExOpen(lbl_1_bss_728[6]);
    HuWinDispOn(lbl_1_bss_728[0]);
    HuWinDispOn(lbl_1_bss_728[2]);
    HuWinDispOn(lbl_1_bss_728[5]);
    for (i = 0; i < 10; i++) {
        HuWinDispOn(lbl_1_bss_736[i]);
    }
    HuSprGrpPosSet(lbl_1_bss_71A, 0.0f, 0.0f);
}

/* 56 insns */
void fn_1_A55C(void)
{
    s16 i;

    HuWinDispOff(lbl_1_bss_728[0]);
    HuWinDispOff(lbl_1_bss_728[2]);
    HuWinDispOff(lbl_1_bss_728[5]);
    for (i = 0; i < 10; i++) {
        HuWinDispOff(lbl_1_bss_736[i]);
    }
    HuSprGrpPosSet(lbl_1_bss_71A, -1000.0f, 0.0f);
    HuWinExClose(lbl_1_bss_728[3]);
    HuWinExClose(lbl_1_bss_728[4]);
    HuWinExClose(lbl_1_bss_728[6]);
}

/* 50 insns */
void fn_1_A63C(void)
{
    s16 i;

    HuWinKill(lbl_1_bss_728[0]);
    HuWinKill(lbl_1_bss_728[2]);
    HuWinKill(lbl_1_bss_728[3]);
    HuWinKill(lbl_1_bss_728[4]);
    HuWinKill(lbl_1_bss_728[5]);
    HuWinKill(lbl_1_bss_728[6]);
    for (i = 0; i < 10; i++) {
        HuWinKill(lbl_1_bss_736[i]);
    }
    HuSprGrpKill(lbl_1_bss_71A);
}

/* 89 insns */
void fn_1_A704(HUWINID winId, s16 type)
{
    s16 num;
    s16 i;

    if (type != 4) {
        i = num = 0;
        for (; i < lbl_1_data_4F4[type]; i++) {
            if (GwSdCommon.partFlag[type] & (1 << i)) {
                num++;
            }
        }
    } else {
        num = 11;
    }
    sprintf(lbl_1_bss_71C, "%02d", num);
    sprintf(&lbl_1_bss_71C[3], "%02d", lbl_1_data_4F4[type]);
    HuWinInsertMesSet(winId, MESSNUM_PTR(lbl_1_bss_71C), 0);
    HuWinInsertMesSet(winId, MESSNUM_PTR(&lbl_1_bss_71C[3]), 1);
    HuWinMesSet(winId, 0x19002C);
    HuWinScaleSet(winId, 0.8f, 0.8f);
}

/* 232 insns */
void fn_1_A868(s16 a0, s16 a1)
{
    s16 i;
    SDPARTDATA *part;
    s16 count;
    float ofs;

    part = lbl_1_data_4E0[a0];
    lbl_1_bss_6FE = i = 0;
    for (; i < lbl_1_data_4F4[a0]; i++) {
        if (fn_1_3EC0(a0, i)) {
            lbl_1_bss_6DE[lbl_1_bss_6FE] = i;
            lbl_1_bss_6FE++;
        }
    }
    for (i = 0; i < 5; i++) {
        if (i + a1 >= lbl_1_bss_6FE) {
            HuWinHomeClear(lbl_1_bss_736[i]);
        } else {
            HuWinMesSet(lbl_1_bss_736[i], part[lbl_1_bss_6DE[i + a1]].mesNo);
        }
    }
    if (a1 + 5 < lbl_1_bss_6FE) {
        HuSprAttrReset(lbl_1_bss_71A, 1, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_71A, 1, HUSPR_ATTR_DISPOFF);
    }
    if (a1 > 0) {
        HuSprAttrReset(lbl_1_bss_71A, 0, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_71A, 0, HUSPR_ATTR_DISPOFF);
    }
    if (lbl_1_bss_724 >= 0) {
        HuSprAttrReset(lbl_1_bss_71A, 2, HUSPR_ATTR_DISPOFF);
    } else {
        HuSprAttrSet(lbl_1_bss_71A, 2, HUSPR_ATTR_DISPOFF);
    }
    ofs = lbl_1_bss_724 - a1;
    HuSprPosSet(lbl_1_bss_71A, 2, 10.0f + lbl_1_bss_704, 8.0f + (32.0f + (lbl_1_bss_700 + 32.0f * ofs)));
    i = count = 0;
    for (; i < lbl_1_data_4F4[a0]; i++) {
        if (fn_1_3EC0(a0, i)) {
            if (count == lbl_1_bss_724) {
                break;
            }
            count++;
        }
    }
    part = &lbl_1_data_4E0[a0][i];
    HuWinMesSet(lbl_1_bss_728[6], part->unk4);
}

/* 145 insns */
void fn_1_AC08(float a0, float a1)
{
    s16 i;

    for (i = 0; i < 5; i++) {
        HuWinPosSet(lbl_1_bss_736[i], 16.0f + a0, 16.0f + (a1 + i * 32));
    }
    HuWinPosSet(lbl_1_bss_728[4], a0, a1);
    HuWinPosSet(lbl_1_bss_728[5], 15.0f + (240.0f + a0), 16.0f + (160.0f + a1));
    HuSprPosSet(lbl_1_bss_71A, 0, 173.0f + a0, 16.0f + a1);
    HuSprPosSet(lbl_1_bss_71A, 1, 173.0f + a0, 32.0f + (160.0f + a1));
    HuSprPosSet(lbl_1_bss_71A, 2, 10.0f + a0, 8.0f + (32.0f + (a1 + lbl_1_bss_724 * 32)));
    lbl_1_bss_704 = a0;
    lbl_1_bss_700 = a1;
}

/* 46 insns */
void fn_1_AE4C(s16 a0)
{
    fn_1_4724(&lbl_1_bss_67C[a0]);
    if (lbl_1_bss_6D4[0] != -1) {
        fn_1_42E0(&lbl_1_bss_67C[a0], lbl_1_bss_6D4[0], lbl_1_bss_6D4[1], lbl_1_bss_6D4[3], lbl_1_bss_6D4[4]);
        fn_1_4638(&lbl_1_bss_67C[a0], 8);
    }
}

/* 50 insns */
s16 fn_1_AF04(s16 type, s16 a1)
{
    s16 num;
    s16 i;

    if (a1 < 0) {
        a1 = 0;
    }
    if (type == 4) {
        return a1;
    }
    i = num = 0;
    for (; i < lbl_1_data_4F4[type]; i++) {
        if (i == a1) {
            break;
        }
        if (fn_1_3EC0(type, i)) {
            num++;
        }
    }
    return num;
}

/* 0x1174 */ float lbl_1_data_1174[5][2] = { { 0.0f, -92.0f }, { -88.0f, -28.0f }, { -55.0f, 75.0f }, { 54.0f, 75.0f }, { 88.0f, -28.0f } };
/* 0x119C */ float lbl_1_data_119C[5][2] = { { 0.0f, 0.0f }, { -12.0f, 0.0f }, { -18.0f, 0.0f }, { 20.0f, 0.0f }, { 10.0f, 0.0f } };
/* 0x11C4 */ s16 lbl_1_data_11C4[10] = { 3, 12, -8, 20, -3, 8, -3, 13, 1, 9 };

/* 583 insns */
void fn_1_AFCC(SDMACHINEMDL *machine, u32 mesNo)
{
    s16 out[5];
    HuVecF pos2d;
    HuVecF pos3d;
    HUWINID winId;
    s16 i;
    HUSPRGRPID grpId;
    HUSPRID sprId;
    float scale;
    HU3DMODELID modelId;

    winId = HuWinExCreateFrame(16.0f, 32.0f, 544, 310, -1, 0);
    lbl_1_bss_5F6[0] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 50);
    HuWinDrawNoSet(winId, 64);
    HuWinExOpen(winId);
    winId = HuWinCreate(48.0f, 304.0f, 192, 42, 0);
    lbl_1_bss_5F6[1] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinAttrSet(winId, 0x800);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinMesSet(winId, MESSNUM_PTR(machine->name));
    winId = HuWinCreate(280.0f, 230.0f, 280, 120, 0);
    lbl_1_bss_5F6[2] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinInsertMesSet(winId, lbl_1_bss_6D4[0] + 0x1A0017, 0);
    HuWinInsertMesSet(winId, lbl_1_bss_6D4[1] + 0x1A0001, 1);
    HuWinInsertMesSet(winId, lbl_1_bss_6D4[2] + 0x1A000C, 2);
    HuWinInsertMesSet(winId, lbl_1_bss_6D4[3] + 0x1A0022, 3);
    HuWinMesSet(winId, 0x450008);
    winId = HuWinCreate(-10000.0f, 352.0f, 544, 26, 0);
    lbl_1_bss_5F6[3] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinAttrSet(winId, 0x800);
    HuWinBGTPLvlSet(winId, 0.0f);
    if (mesNo != 0) {
        HuWinMesSet(winId, mesNo);
    }
    HuDataDirClose(DATANUM(DATA_sd00, 0));
    fn_1_C384(lbl_1_bss_6D4[0], lbl_1_bss_6D4[1], lbl_1_bss_6D4[2], lbl_1_bss_6D4[3], out);
    lbl_1_bss_5E0[0] = out[3];
    lbl_1_bss_5E0[1] = out[1];
    lbl_1_bss_5E0[2] = lbl_1_data_11C4[4] + ((lbl_1_data_11C4[5] - lbl_1_data_11C4[4]) - (out[2] - lbl_1_data_11C4[4]));
    OSReport("Toruque:%d\n", lbl_1_bss_5E0[2]);
    lbl_1_bss_5E0[3] = lbl_1_data_11C4[6] + ((lbl_1_data_11C4[7] - lbl_1_data_11C4[6]) - (out[0] - lbl_1_data_11C4[6]));
    lbl_1_bss_5E0[4] = out[4];
    grpId = HuSprGrpCreate(3);
    lbl_1_bss_5F4 = grpId;
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x41), HU_MEMNUM_OVL, HEAP_MODEL)), 30, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x42), HU_MEMNUM_OVL, HEAP_MODEL)), 25, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprAttrSet(grpId, 1, HUSPR_ATTR_LINEAR);
    if (lbl_1_bss_5E0[0] < -50 || lbl_1_bss_5E0[1] < -50 || lbl_1_bss_5E0[2] < -50 || lbl_1_bss_5E0[3] < -50 || lbl_1_bss_5E0[4] < -50) {
        sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x44), HU_MEMNUM_OVL, HEAP_MODEL)), 24, 0);
    } else {
        sprId = HuSprFuncCreate(fn_1_BAA0, 28);
    }
    HuSprGrpMemberSet(grpId, 2, sprId);
    HuSprGrpPosSet(grpId, 424.0f, 151.0f);
    HuSprGrpScaleSet(grpId, 1.0f, 1.0f);
    HuSprGrpDrawNoSet(grpId, 64);
    lbl_1_bss_5DC = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x43), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 5; i++) {
        lbl_1_bss_5EA[i] = modelId = Hu3DModelCreateData(DATANUM(DATA_sdroom, 0x45) + i);
        Hu3DModelCameraSet(modelId, HU3D_CAM2);
        pos2d.x = 424.0 + lbl_1_data_1174[i][0] + lbl_1_data_119C[i][0];
        pos2d.y = 151.0 + lbl_1_data_1174[i][1] + lbl_1_data_119C[i][1];
        pos2d.z = 500.0f;
        Hu3D2Dto3D(&pos2d, HU3D_CAM2, &pos3d);
        Hu3DModelLayerSet(modelId, 6);
        Hu3DModelPosSetV(modelId, &pos3d);
        Hu3DModelRotSet(modelId, 0.0f, (sdWorkInt[7] + 1) * 60, 0.0f);
        Hu3DModelScaleSet(modelId, 1.3f, 1.3f, 1.3f);
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    }
    HuDataDirClose(DATANUM(DATA_sdroom, 0));
    fn_1_4724(machine);
    fn_1_44E4(machine, lbl_1_bss_6D4[0], lbl_1_bss_6D4[1], lbl_1_bss_6D4[3], lbl_1_bss_6D4[4]);
    fn_1_4638(machine, 8);
    fn_1_4590(machine, 0.0f, 45.0f, 0.0f);
    lbl_1_bss_620 = Hu3DCamera[3];
    omCameraViewSetMulti(HU3D_CAM3, (OMCAMERAVIEW *)lbl_1_data_1120);
    Hu3DCameraViewportSet(HU3D_CAM3, -42.222218f, 34.0f, 400.0f, 300.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM3, 22, 34, 311, 272);
    for (i = 1; i <= 10; i++) {
        scale = HuSin(90.0 * (i / 10.0));
        Hu3DModelScaleSet(machine->bodyMdl, scale, scale, scale);
        HuPrcVSleep();
    }
}

/* 110 insns */
void fn_1_B8E8(SDMACHINEMDL *machine)
{
    s16 i;
    float scale;

    for (i = 1; i <= 10; i++) {
        scale = HuCos(90.0 * (i / 10.0));
        Hu3DModelScaleSet(machine->bodyMdl, scale, scale, scale);
        HuPrcVSleep();
    }
    HuSprGrpKill(lbl_1_bss_5F4);
    for (i = 0; i < 5; i++) {
        Hu3DModelKill(lbl_1_bss_5EA[i]);
    }
    HuSprAnimKill(lbl_1_bss_5DC);
    HuWinKill(lbl_1_bss_5F6[1]);
    HuWinKill(lbl_1_bss_5F6[2]);
    HuWinKill(lbl_1_bss_5F6[3]);
    HuWinExClose(lbl_1_bss_5F6[0]);
    HuWinKill(lbl_1_bss_5F6[0]);
    Hu3DCamera[3] = lbl_1_bss_620;
}

/* 560 insns */
void fn_1_BAA0(HUSPRITE *sp)
{
    Mtx mtx;
    HuVecF pos;
    GXColor color;
    float range;
    float t;
    s16 i;

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    color.r = 0xFD;
    color.g = 0xFF;
    color.b = 0;
    color.a = 0xFF;
    GXSetChanAmbColor(GX_COLOR0A0, color);
    GXSetChanMatColor(GX_COLOR0A0, color);
    color.a = sp->a;
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetNumTevStages(1);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT0, GX_DF_CLAMP, GX_AF_SPOT);
    if (sp->attr & HUSPR_ATTR_ADDCOL) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    } else if (sp->attr & HUSPR_ATTR_INVCOL) {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVDSTCLR, GX_LO_NOOP);
    } else {
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    }
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    PSMTXScale(mtx, sp->scale.x, sp->scale.y, 1.0f);
    mtxTransCat(mtx, sp->pos.x, sp->pos.y, 0.0f);
    PSMTXConcat(*sp->groupMtx, mtx, mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    HuSprTexLoad(lbl_1_bss_5DC, 0, GX_TEXMAP0, GX_CLAMP, GX_CLAMP, GX_LINEAR);
    for (i = 0; i < 5; i++) {
        GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
        GXPosition3f32(0.0f, 8.0f, 0.0f);
        GXTexCoord2f32(0.0f, 0.0f);
        range = lbl_1_data_11C4[i * 2 + 1] - lbl_1_data_11C4[i * 2];
        t = lbl_1_bss_5E0[i] - lbl_1_data_11C4[i * 2];
        pos.x = 0.1 * lbl_1_data_1174[i][0] + 0.9 * lbl_1_data_1174[i][0] * (t / range);
        pos.y = 0.1 * lbl_1_data_1174[i][1] + 0.9 * lbl_1_data_1174[i][1] * (t / range);
        GXPosition3f32(pos.x, 8.0f + pos.y, 0.0f);
        GXTexCoord2f32(0.0f, 1.0f);
        if (i < 4) {
            range = lbl_1_data_11C4[(i + 1) * 2 + 1] - lbl_1_data_11C4[(i + 1) * 2];
            t = lbl_1_bss_5E0[i + 1] - lbl_1_data_11C4[(i + 1) * 2];
            pos.x = 0.1 * lbl_1_data_1174[i + 1][0] + 0.9 * lbl_1_data_1174[i + 1][0] * (t / range);
            pos.y = 0.1 * lbl_1_data_1174[i + 1][1] + 0.9 * lbl_1_data_1174[i + 1][1] * (t / range);
        } else {
            range = lbl_1_data_11C4[1] - lbl_1_data_11C4[0];
            t = lbl_1_bss_5E0[0] - lbl_1_data_11C4[0];
            pos.x = 0.1 * lbl_1_data_1174[0][0] + 0.9 * lbl_1_data_1174[0][0] * (t / range);
            pos.y = 0.1 * lbl_1_data_1174[0][1] + 0.9 * lbl_1_data_1174[0][1] * (t / range);
        }
        GXPosition3f32(pos.x, 8.0f + pos.y, 0.0f);
        GXTexCoord2f32(1.0f, 1.0f);
        GXEnd();
    }
}

/* 9 insns */
void fn_1_C360(s16 a0, HUWINID winId)
{
    float f;
    s32 i;
    s32 j;
}

/* 109 insns */
void fn_1_C384(s16 a0, s16 a1, s16 a2, s16 a3, s16 *out)
{
    s8 *point[4];

    point[0] = lbl_1_data_4E0[0][a0].unkD;
    point[1] = lbl_1_data_4E0[1][a1].unkD;
    point[2] = lbl_1_data_4E0[2][a2].unkD;
    point[3] = lbl_1_data_4E0[3][a3].unkD;
    out[0] = 5 + point[1][0] + point[2][0];
    out[1] = 5 + point[1][1] + point[0][0] + point[2][1] + point[3][1];
    out[2] = 5 + point[1][2] + point[2][2];
    out[3] = 4 + point[0][2] + point[3][0];
    out[4] = 5 + point[0][1];
    OSReport("Point %d,%d,%d,%d,%d\n", out[0], out[1], out[2], out[3], out[4]);
}

/* 1537 insns */
void fn_1_C538(s16 a0)
{
    s16 partNo[3];
    GWSDMACHINE *machine;
    s32 result;
    s16 mask;
    s16 tutNo;
    s16 i;
    float t;

    if (omovlevtno == 3 || omovlevtno == 2) {
        HuSprPosSet(lbl_1_bss_718, 4, 224.0f, 128.0f);
        HuSprScaleSet(lbl_1_bss_718, 4, 0.0f, 0.0f);
        HuSprPosSet(lbl_1_bss_718, 5, 352.0f, 128.0f);
        HuSprScaleSet(lbl_1_bss_718, 5, 0.0f, 0.0f);
        tutNo = (omovlevtno == 3) ? 1 : 0;
        omovlevtno = 0;
        HuWinDispOn(lbl_1_bss_606);
        HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
        HuWinMesWait(lbl_1_bss_606);
        HuSprPosSet(lbl_1_bss_718, 4, 224.0f, 128.0f);
        HuSprPosSet(lbl_1_bss_718, 5, 352.0f, 128.0f);
        if (tutNo == 0) {
            HuSprScaleSet(lbl_1_bss_718, 4, 1.0f, 1.0f);
            HuSprScaleSet(lbl_1_bss_718, 5, 0.8f, 0.8f);
        } else {
            HuSprScaleSet(lbl_1_bss_718, 4, 0.8f, 0.8f);
            HuSprScaleSet(lbl_1_bss_718, 5, 1.0f, 1.0f);
        }
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
        while (WipeCheckEnd()) {
            HuPrcVSleep();
        }
        for (i = 0; i < 2; i++) {
            if (GwSdCommon.machine[i].charNo != -1) {
                GwSdCommon.machine[i].charNo = 0x40;
            }
        }
        if (GwSdBackup[GwSdBackupNo].machine.charNo != -1)
        {
            GwSdBackup[GwSdBackupNo].machine.charNo = 0x40;
        }
    } else {
        HuSprScaleSet(lbl_1_bss_718, 4, 0.8f, 0.8f);
        HuSprScaleSet(lbl_1_bss_718, 5, 0.8f, 0.8f);
        for (i = 1; i <= 10; i++) {
            t = 128.0 - 500.0 * (1.0 - HuSin(90.0 * (i / 10.0)));
            HuSprPosSet(lbl_1_bss_718, 4, 224.0f, t);
            HuSprPosSet(lbl_1_bss_718, 5, 352.0f, t);
            HuPrcVSleep();
        }
        tutNo = 0;
        for (i = 1; i <= 10; i++) {
            t = 0.8 + 0.2 * HuSin(90.0 * (i / 10.0));
            HuSprScaleSet(lbl_1_bss_718, 4, t, t);
            HuPrcVSleep();
        }
        HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
        HuWinMesWait(lbl_1_bss_606);
    }
    HuWinMesSet(lbl_1_bss_604, 0x20004);
    HuWinDispOn(lbl_1_bss_604);
    while (1) {
        if ((fn_1_507C(1 << a0) & PAD_BUTTON_LEFT) && tutNo > 0) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                t = 0.8 + 0.2 * HuCos(90.0 * (i / 10.0));
                HuSprScaleSet(lbl_1_bss_718, tutNo + 4, t, t);
                t = 0.8 + 0.2 * HuSin(90.0 * (i / 10.0));
                HuSprScaleSet(lbl_1_bss_718, tutNo + 3, t, t);
                HuPrcVSleep();
            }
            tutNo--;
            HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
            HuWinMesWait(lbl_1_bss_606);
        } else if ((fn_1_507C(1 << a0) & PAD_BUTTON_RIGHT) && tutNo < 1) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                t = 0.8 + 0.2 * HuCos(90.0 * (i / 10.0));
                HuSprScaleSet(lbl_1_bss_718, tutNo + 4, t, t);
                t = 0.8 + 0.2 * HuSin(90.0 * (i / 10.0));
                HuSprScaleSet(lbl_1_bss_718, tutNo + 5, t, t);
                HuPrcVSleep();
            }
            tutNo++;
            HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
            HuWinMesWait(lbl_1_bss_606);
        } else if (fn_1_4FD0(1 << a0) & PAD_BUTTON_A) {
            HuWinDispOff(lbl_1_bss_604);
            HuAudFXPlay(1);
            if (tutNo == 0) {
                mask = 0;
                i = mask;
                if (GwSdCommon.machine[0].charNo != -1 && HuPadStatGet(0) != -1) {
                    i++;
                    mask |= 1;
                }
                if (GwSdCommon.machine[1].charNo != -1 && HuPadStatGet(1) != -1) {
                    i++;
                    mask |= 2;
                }
                if (GwSdBackupNo != -1 && HuPadStatGet(2) != -1) {
                    i++;
                    mask |= 4;
                }
                if (i >= 2) {
                    for (i = 1; i <= 15; i++) {
                        t = HuCos(90.0 * (i / 15.0));
                        HuSprScaleSet(lbl_1_bss_718, 5, 0.8 * t, 0.8 * t);
                        t = HuSin(90.0 * (i / 15.0));
                        HuSprPosSet(lbl_1_bss_718, 4, 224.0f + 64.0f * t, 128.0f + -48.0f * t);
                        HuPrcVSleep();
                    }
                    while (1) {
                        HuWinMesSet(lbl_1_bss_606, 0x190073);
                        result = fn_1_12940(mask, partNo, fn_1_DD3C);
                        if (result == 0) {
                            break;
                        }
                        HuWinExClose(lbl_1_bss_606);
                        for (i = 1; i <= 10; i++) {
                            t = HuCos(90.0 * (i / 10.0));
                            HuSprScaleSet(lbl_1_bss_718, 4, t, t);
                            HuPrcVSleep();
                        }
                        if (partNo[0] != -1) {
                            GwSdCommon.machine[0].charNo = partNo[0];
                        }
                        if (partNo[1] != -1) {
                            GwSdCommon.machine[1].charNo = partNo[1];
                        }
                        if (partNo[2] != -1) {
                            GwSdBackup[GwSdBackupNo].machine.charNo = partNo[2];
                        }
                        fn_1_DF94(a0, mask);
                        if (partNo[0] != -1) {
                            GwSdCommon.machine[0].charNo = 0x40;
                        }
                        if (partNo[1] != -1) {
                            GwSdCommon.machine[1].charNo = 0x40;
                        }
                        if (partNo[2] != -1) {
                            GwSdBackup[GwSdBackupNo].machine.charNo = 0x40;
                        }
                        for (i = 1; i <= 10; i++) {
                            t = HuSin(90.0 * (i / 10.0));
                            HuSprScaleSet(lbl_1_bss_718, 4, t, t);
                            HuPrcVSleep();
                        }
                        HuWinExOpen(lbl_1_bss_606);
                    }
                    for (i = 1; i <= 10; i++) {
                        t = HuCos(90.0 * (i / 10.0));
                        HuSprPosSet(lbl_1_bss_718, 4, 224.0f + 64.0f * t, 128.0f + -48.0f * t);
                        t = HuSin(90.0 * (i / 10.0));
                        HuSprScaleSet(lbl_1_bss_718, 5, 0.8 * t, 0.8 * t);
                        HuPrcVSleep();
                    }
                    tutNo = 0;
                    HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
                    HuWinMesWait(lbl_1_bss_606);
                } else {
                    mask = 0;
                    i = mask;
                    if (GwSdCommon.machine[0].charNo != -1) {
                        i++;
                        mask |= 1;
                    }
                    if (GwSdCommon.machine[1].charNo != -1) {
                        i++;
                        mask |= 2;
                    }
                    if (GwSdBackupNo != -1) {
                        i++;
                        mask |= 4;
                    }
                    HuAudFXPlay(0x2F0);
                    if (i <= 1) {
                        HuWinMesSet(lbl_1_bss_606, 0x190013);
                    } else {
                        if (a0 == 0) {
                            if (mask == 7) {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x190083, 0);
                            } else if (mask == 3) {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x190080, 0);
                            } else {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x190081, 0);
                            }
                        } else {
                            if (mask == 7) {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x190082, 0);
                            } else if (mask == 3) {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x19007F, 0);
                            } else {
                                HuWinInsertMesSet(lbl_1_bss_606, 0x190081, 0);
                            }
                        }
                        HuWinMesSet(lbl_1_bss_606, 0x19007E);
                    }
                    HuWinMesWait(lbl_1_bss_606);
                    HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
                    HuWinMesWait(lbl_1_bss_606);
                }
            } else {
                for (i = 1; i <= 10; i++) {
                    t = HuCos(90.0 * (i / 10.0));
                    HuSprScaleSet(lbl_1_bss_718, 4, 0.8 * t, 0.8 * t);
                    t = HuSin(90.0 * (i / 10.0));
                    HuSprPosSet(lbl_1_bss_718, 5, 352.0f + -64.0f * t, 128.0f + -48.0f * t);
                    HuPrcVSleep();
                }
                while (1) {
                    machine = &GwSdCommon.machine[a0];
                    HuWinMesSet(lbl_1_bss_606, 0x190073);
                    result = fn_1_12940(1 << a0, partNo, fn_1_DD3C);
                    if (result == 0) {
                        break;
                    }
                    if (partNo[a0] != -1) {
                        machine->charNo = partNo[a0];
                    }
                    fn_1_113F8(a0);
                }
                for (i = 1; i <= 10; i++) {
                    t = HuSin(90.0 * (i / 10.0));
                    HuSprScaleSet(lbl_1_bss_718, 4, 0.8 * t, 0.8 * t);
                    t = HuCos(90.0 * (i / 10.0));
                    HuSprPosSet(lbl_1_bss_718, 5, 352.0f + -64.0f * t, 128.0f + -48.0f * t);
                    HuPrcVSleep();
                }
                machine->charNo = 0x40;
                tutNo = 1;
                HuWinMesSet(lbl_1_bss_606, tutNo + 0x190015);
                HuWinMesWait(lbl_1_bss_606);
            }
            HuWinMesSet(lbl_1_bss_604, 0x20004);
            HuWinDispOn(lbl_1_bss_604);
        } else if (fn_1_4FD0(1 << a0) & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            HuWinDispOff(lbl_1_bss_604);
            for (i = 1; i <= 10; i++) {
                t = 128.0 - 500.0 * (1.0 - HuCos(90.0 * (i / 10.0)));
                HuSprPosSet(lbl_1_bss_718, 4, 224.0f, t);
                HuSprPosSet(lbl_1_bss_718, 5, 352.0f, t);
                HuPrcVSleep();
            }
            return;
        }
        HuPrcVSleep();
    }
}

/* 150 insns */
void fn_1_DD3C(s16 *partNo, s16 a1)
{
    s16 no;
    GWSDMACHINE *machine;
    s32 hook;

    no = sdWorkInt[7];
    machine = &GwSdCommon.machine[no];
    fn_1_4724(&lbl_1_bss_67C[no]);
    if (a1 != 0) {
        hook = partNo[no];
    } else {
        hook = 0x40;
    }
    fn_1_44E4(&lbl_1_bss_67C[no], machine->partNo[0], machine->partNo[1], machine->partNo[3], hook);
    fn_1_4638(&lbl_1_bss_67C[no], 4);
    fn_1_4534(&lbl_1_bss_67C[no], 1450.0 * -HuSin(no * 60 + 60), 0.0f, 1450.0 * -HuCos(no * 60 + 60));
    fn_1_4590(&lbl_1_bss_67C[no], 0.0f, (no + 1) * 60 + 60, 0.0f);
}

/* 0x11FC */ float lbl_1_data_11FC[8][4] = { { -33.777767f, 64.0f, 405.33334f, 304.0f }, { 328.88892f, 40.0f, 284.44446f, 192.0f }, { 328.88892f, 202.0f, 284.44446f, 192.0f }, { -32.0f, 0.0f, 426.6667f, 288.0f }, { 256.0f, 0.0f, 426.6667f, 288.0f }, { 24.0f, 64.0f, 256.0f, 304.0f }, { 296.0f, 64.0f, 256.0f, 144.0f }, { 296.0f, 226.0f, 256.0f, 144.0f } };
/* 0x127C */ float lbl_1_data_127C[3][2] = { { 248.0f, 352.0f }, { 520.0f, 192.0f }, { 520.0f, 354.0f } };
/* 0x1294 */ float lbl_1_data_1294[2][2] = { { 64.0f, 200.0f }, { 512.0f, 200.0f } };
/* 0x12A4 */ u32 lbl_1_data_12A4[8] = { DATANUM(DATA_donkey, 59), DATANUM(DATA_donkey, 60), DATANUM(DATA_donkey, 61), DATANUM(DATA_donkey, 62), DATANUM(DATA_donkey, 63), DATANUM(DATA_donkey, 64), DATANUM(DATA_donkey, 65), DATANUM(DATA_donkey, 66) };
/* 0x12C4 */ s32 lbl_1_data_12C4[8] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x0 };

/* 3353 insns */
void fn_1_DF94(s16 a0, u8 a1)
{
    SDMACHINEMDL mdl[3];
    HUWINID win[7];
    GWSDMACHINE *machine[3];
    s16 order[3];
    float unk10;
    float unkC;
    s16 unk8;
    float scale;
    float posX;
    float posY;
    s16 i;
    s16 j;
    s16 sel;
    s16 move;
    GWSDMACHINE *mp;
    s16 no;
    s32 dir;
    s32 dir2;

    sel = 0;
    move = 0;
    unk8 = 0;
    sdWorkInt[7] = a0;
    for (i = 0; i < 2; i++) {
        mp = &GwSdCommon.machine[i];
        if (mp->charNo != -1 && a0 != i) {
            fn_1_46C4(&lbl_1_bss_67C[i], 0);
        }
    }
    win[0] = HuWinCreate(24.0f, 64.0f, 0x100, 0x130, 0);
    HuWinMesSpeedSet(win[0], 0);
    HuWinDrawNoSet(win[0], 0x40);
    win[1] = HuWinCreate(296.0f, 64.0f, 0x100, 0x90, 0);
    HuWinMesSpeedSet(win[1], 0);
    HuWinDrawNoSet(win[1], 0x40);
    win[2] = HuWinCreate(296.0f, 226.0f, 0x100, 0x90, 0);
    HuWinMesSpeedSet(win[2], 0);
    HuWinDrawNoSet(win[2], 0x40);
    win[3] = HuWinCreate(-10000.0f, 380.0f, 0x230, 0x2A, 0);
    HuWinBGTPLvlSet(win[3], 0.0f);
    HuWinAttrSet(win[3], 0x800);
    HuWinMesSpeedSet(win[3], 0);
    HuWinMesSet(win[3], 0x20004);
    win[4] = HuWinCreate(24.0f, 64.0f, 0x100, 0x2A, 0);
    HuWinMesSpeedSet(win[4], 0);
    HuWinBGTPLvlSet(win[4], 0.0f);
    HuWinAttrSet(win[4], 0x801);
    win[5] = HuWinCreate(296.0f, 64.0f, 0x100, 0x2A, 0);
    HuWinMesSpeedSet(win[5], 0);
    HuWinBGTPLvlSet(win[5], 0.0f);
    HuWinAttrSet(win[5], 0x801);
    win[6] = HuWinCreate(296.0f, 226.0f, 0x100, 0x2A, 0);
    HuWinMesSpeedSet(win[6], 0);
    HuWinBGTPLvlSet(win[6], 0.0f);
    HuWinAttrSet(win[6], 0x801);
    HuSprPosSet(lbl_1_bss_718, 12, 152.0f, 216.0f);
    HuSprScaleSet(lbl_1_bss_718, 12, 32.0f, 38.0f);
    HuSprPosSet(lbl_1_bss_718, 13, 424.0f, 136.0f);
    HuSprScaleSet(lbl_1_bss_718, 13, 32.0f, 18.0f);
    HuSprPosSet(lbl_1_bss_718, 14, 424.0f, 298.0f);
    HuSprScaleSet(lbl_1_bss_718, 14, 32.0f, 18.0f);
    if (a0 == 0) {
        order[0] = 0;
        order[1] = 1;
        order[2] = 2;
    } else {
        order[0] = 1;
        order[1] = 0;
        order[2] = 2;
    }
    machine[0] = &GwSdCommon.machine[0];
    machine[1] = &GwSdCommon.machine[1];
    if (GwSdBackupNo != -1) {
        machine[2] = &GwSdBackup[GwSdBackupNo].machine;
    } else {
        machine[2] = (GWSDMACHINE *)lbl_1_bss_608;
    }
    for (i = 0; i < 3; i++) {
        mp = machine[order[i]];
        if (mp != 0 && (a1 & (1 << order[i]))) {
            fn_1_44E4(&mdl[i], mp->partNo[0], mp->partNo[1], mp->partNo[3], mp->charNo);
            fn_1_4638(&mdl[i], 8 << i);
            if (i > 0) {
                dir = -1;
            } else {
                dir = 1;
            }
            fn_1_4590(&mdl[i], 0.0f, dir * 45, 0.0f);
            fn_1_45E4(&mdl[i], 0.9f, 0.9f, 0.9f);
            HuWinMesSet(win[i + 4], (u32)mp->name);
        } else {
            fn_1_480C(&mdl[i]);
        }
    }
    if (omovlevtno != 2) {
        sdWorkInt[1] = 0;
        if (a1 & (1 << order[1])) {
            sdWorkInt[2] = 1;
        }
        if (!(a1 & (1 << order[1]))) {
            sdWorkInt[2] = 2;
        }
        sdWorkInt[3] = 0;
        sdWorkInt[4] = 0;
        sdWorkInt[5] = 0;
    }
restart:
    unk10 = 284.44446f;
    unkC = 192.0f;
    Hu3DCameraPerspectiveSet(0x38, 5.0f, 20.0f, 15000.0f, 1.2f);
    omCameraViewSetMulti(8, (OMCAMERAVIEW *)lbl_1_data_10E8);
    omCameraViewSetMulti(0x30, (OMCAMERAVIEW *)&lbl_1_data_1104);
    Hu3DCameraViewportSet(8, lbl_1_data_11FC[0][0], lbl_1_data_11FC[0][1], lbl_1_data_11FC[0][2], lbl_1_data_11FC[0][3], 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 0x1F, 0x44, 0x114, 0x128);
    Hu3DCameraViewportSet(0x10, lbl_1_data_11FC[1][0], lbl_1_data_11FC[1][1], lbl_1_data_11FC[1][2], lbl_1_data_11FC[1][3], 0.0f, 1.0f);
    Hu3DCameraScissorSet(0x10, 0x14A, 0x42, 0x11A, 0x8A);
    Hu3DCameraViewportSet(0x20, lbl_1_data_11FC[2][0], lbl_1_data_11FC[2][1], lbl_1_data_11FC[2][2], lbl_1_data_11FC[2][3], 0.0f, 1.0f);
    Hu3DCameraScissorSet(0x20, 0x14A, 0xE4, 0x11A, 0x8A);
    HuSprScaleSet(lbl_1_bss_718, 15, 1.0f, 1.0f);
    if (omovlevtno == 2) {
        omovlevtno = 0;
        for (j = 0; j < 3; j++) {
            HuSprAttrSet(lbl_1_bss_718, j + 12, 4);
            HuWinBGTPLvlSet(win[j], 0.0f);
            HuWinDispOff(win[j + 4]);
            if (j != sdWorkInt[1] && j != sdWorkInt[2]) {
                fn_1_45E4(&mdl[j], 0.0f, 0.0f, 0.0f);
                HuSprTPLvlSet(lbl_1_bss_718, order[j] + 9, 0.0f);
            }
        }
        Hu3DCameraScissorSet(8, 0, 0, 0x280, 0x1E0);
        Hu3DCameraScissorSet(0x10, 0, 0, 0x280, 0x1E0);
        Hu3DCameraScissorSet(0x20, 0, 0, 0x280, 0x1E0);
        for (j = 0; j < 2; j++) {
            no = (&sdWorkInt[1])[j];
            Hu3DCameraViewportSet(8 << no, lbl_1_data_11FC[j + 3][0], lbl_1_data_11FC[j + 3][1], lbl_1_data_11FC[j + 3][2], lbl_1_data_11FC[j + 3][3], 0.0f, 1.0f);
            HuSprPosSet(lbl_1_bss_718, order[no] + 9, lbl_1_data_1294[j][0], lbl_1_data_1294[j][1]);
        }
        HuSprPosSet(lbl_1_bss_718, 15, 288.0f, 180.0f);
        HuSprPosSet(lbl_1_bss_718, sdWorkInt[3] + 6, 64.0f, 250.0f);
        HuSprPosSet(lbl_1_bss_718, sdWorkInt[4] + 16, 130.0f, 250.0f);
        for (i = 0; i < 8; i++) {
            HuSprPosSet(lbl_1_bss_716, i, 288.0f, 250.0f);
        }
        HuSprAttrReset(lbl_1_bss_716, sdWorkInt[5], 4);
        HuSprPosSet(lbl_1_bss_718, 18, 224.0f, 250.0f);
        HuSprPosSet(lbl_1_bss_718, 19, 352.0f, 250.0f);
        if (sdWorkInt[5] != 0) {
            HuSprTPLvlSet(lbl_1_bss_718, 18, 1.0f);
        } else {
            HuSprTPLvlSet(lbl_1_bss_718, 18, 0.0f);
        }
        if (sdWorkInt[5] < 7) {
            HuSprTPLvlSet(lbl_1_bss_718, 19, 1.0f);
        } else {
            HuSprTPLvlSet(lbl_1_bss_718, 19, 0.0f);
        }
        HuWinPosSet(win[3], -10000.0f, 310.0f);
        HuWinDispOn(lbl_1_bss_606);
        WipeCreate(1, 0, 60);
        while (WipeCheckEnd()) {
            HuPrcVSleep();
        }
        goto stage;
    }
    for (i = 0; i < 3; i++) {
        if (i > 0) {
            dir2 = -1;
        } else {
            dir2 = 1;
        }
        fn_1_4590(&mdl[i], 0.0f, dir2 * 45, 0.0f);
    }
    for (j = 0; j < 3; j++) {
        HuWinDispOff(win[j + 4]);
    }
    for (i = 1; i <= 10; i++) {
        scale = i / 10.0;
        for (j = 0; j < 3; j++) {
            HuWinBGTPLvlSet(win[j], 1.0f);
            HuWinScaleSet(win[j], 1.0f, scale);
            HuSprPosSet(lbl_1_bss_718, order[j] + 9, lbl_1_data_127C[j][0], lbl_1_data_127C[j][1]);
            HuSprScaleSet(lbl_1_bss_718, order[j] + 9, 1.0f, scale);
            HuSprTPLvlSet(lbl_1_bss_718, order[j] + 9, 1.0f);
            fn_1_45E4(&mdl[j], scale, scale, scale);
            HuSprAttrSet(lbl_1_bss_718, j + 12, 4);
        }
        HuPrcVSleep();
    }
    for (j = 0; j < 3; j++) {
        HuWinDispOn(win[j + 4]);
    }
    sel = sdWorkInt[2];
    for (i = 0; i < 3; i++) {
        HuSprAttrReset(lbl_1_bss_718, i + 12, 4);
    }
    HuSprAttrSet(lbl_1_bss_718, 12, 4);
    HuSprAttrSet(lbl_1_bss_718, sel + 12, 4);
    while (!(fn_1_4FD0(1 << a0) & 0x100)) {
        if (fn_1_4FD0(1 << a0) & 0x200) {
            HuAudFXPlay(3);
            goto cancel;
        }
        move = -1;
        if ((fn_1_507C(1 << a0) & 8) && sel == 2 && (a1 & (1 << order[1]))) {
            move = 1;
        } else if ((fn_1_507C(1 << a0) & 4) && sel == 1 && (a1 & (1 << order[2]))) {
            move = 2;
        }
        if (move != -1) {
            HuAudFXPlay(0);
            sel = move;
            for (i = 0; i < 3; i++) {
                HuSprAttrReset(lbl_1_bss_718, i + 12, 4);
            }
            HuSprAttrSet(lbl_1_bss_718, 12, 4);
            HuSprAttrSet(lbl_1_bss_718, sel + 12, 4);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    sdWorkInt[1] = 0;
    sdWorkInt[2] = sel;
    HuWinDispOff(win[3]);
    for (j = 0; j < 3; j++) {
        HuSprAttrSet(lbl_1_bss_718, j + 12, 4);
        HuWinDispOff(win[j + 4]);
    }
    for (i = 1; i <= 20; i++) {
        scale = 1.0 - i / 20.0;
        for (j = 0; j < 3; j++) {
            HuWinBGTPLvlSet(win[j], scale);
            if (j != sdWorkInt[1] && j != sdWorkInt[2]) {
                if (machine[j]->charNo != -1) {
                    if (j == 0) {
                        fn_1_45E4(&mdl[j], 0.9 * scale, 0.9 * scale, 0.9 * scale);
                    } else {
                        fn_1_45E4(&mdl[j], scale, scale, scale);
                    }
                }
                HuSprTPLvlSet(lbl_1_bss_718, order[j] + 9, scale);
            }
        }
        HuPrcVSleep();
    }
    Hu3DCameraScissorSet(8, 0, 0, 0x280, 0x1E0);
    Hu3DCameraScissorSet(0x10, 0, 0, 0x280, 0x1E0);
    Hu3DCameraScissorSet(0x20, 0, 0, 0x280, 0x1E0);
    omCameraViewMoveMulti(0x38, (OMCAMERAVIEW *)&lbl_1_data_113C, 20, 0);
    for (i = 1; i <= 20; i++) {
        scale = i / 20.0;
        for (j = 0; j < 2; j++) {
            no = (&sdWorkInt[1])[j];
            Hu3DCameraViewportSet(8 << no,
                lbl_1_data_11FC[no][0] + scale * (lbl_1_data_11FC[j + 3][0] - lbl_1_data_11FC[no][0]),
                lbl_1_data_11FC[no][1] + scale * (lbl_1_data_11FC[j + 3][1] - lbl_1_data_11FC[no][1]),
                lbl_1_data_11FC[no][2] + scale * (lbl_1_data_11FC[j + 3][2] - lbl_1_data_11FC[no][2]),
                lbl_1_data_11FC[no][3] + scale * (lbl_1_data_11FC[j + 3][3] - lbl_1_data_11FC[no][3]),
                0.0f, 1.0f);
            posX = lbl_1_data_127C[no][0];
            posX = posX + scale * (lbl_1_data_1294[j][0] - posX);
            posY = lbl_1_data_127C[no][1];
            posY = posY + scale * (lbl_1_data_1294[j][1] - posY);
            HuSprPosSet(lbl_1_bss_718, order[no] + 9, posX, posY);
        }
        HuSprPosSet(lbl_1_bss_718, 15, 288.0f, 180.0 - 300.0 * (1.0 - scale));
        HuPrcVSleep();
    }
    HuAudFXPlay(0x514);
    HuWinExOpen(lbl_1_bss_606);
type:
    sel = sdWorkInt[3];
    for (j = 0; j < 3; j++) {
        HuSprPosSet(lbl_1_bss_718, j + 6, 188.0f + j * 100, 250.0f);
    }
    for (i = 1; i <= 20; i++) {
        scale = i / 20.0;
        for (j = 0; j < 3; j++) {
            if (sel == j) {
                HuSprScaleSet(lbl_1_bss_718, j + 6, scale, scale);
            } else {
                HuSprScaleSet(lbl_1_bss_718, j + 6, 0.8 * scale, 0.8 * scale);
            }
        }
        HuPrcVSleep();
    }
    HuWinPosSet(win[3], -10000.0f, 310.0f);
    HuWinDispOn(win[3]);
    HuWinMesSet(lbl_1_bss_606, sel + 0x19001F);
    while (!(fn_1_4FD0(1 << a0) & 0x100)) {
        if (fn_1_4FD0(1 << a0) & 0x200) {
            HuAudFXPlay(3);
            HuWinExClose(lbl_1_bss_606);
            HuWinDispOff(win[3]);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                for (j = 0; j < 3; j++) {
                    if (sel == j) {
                        HuSprScaleSet(lbl_1_bss_718, j + 6, scale, scale);
                    } else {
                        HuSprScaleSet(lbl_1_bss_718, j + 6, 0.8 * scale, 0.8 * scale);
                    }
                }
                HuPrcVSleep();
            }
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                HuSprScaleSet(lbl_1_bss_718, 15, scale, scale);
                for (j = 0; j < 3; j++) {
                    if (j == sdWorkInt[1] || j == sdWorkInt[2]) {
                        HuSprScaleSet(lbl_1_bss_718, order[j] + 9, scale, scale);
                        fn_1_45E4(&mdl[j], scale, scale, scale);
                    }
                }
                HuPrcVSleep();
            }
            HuSprPosSet(lbl_1_bss_718, 15, 0.0f, -1000.0f);
            HuWinPosSet(win[3], -10000.0f, 380.0f);
            HuWinDispOn(win[3]);
            goto restart;
        }
        move = 0;
        if ((fn_1_507C(1 << a0) & 1) && sel != 0) {
            move = -1;
        } else if ((fn_1_507C(1 << a0) & 2) && sel < 2) {
            move = 1;
        }
        if (move != 0) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - 0.2 * (i / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 6, scale, scale);
                scale = 0.8 + 0.2 * (i / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 6 + move, scale, scale);
                HuPrcVSleep();
            }
            sel += move;
            HuWinMesSet(lbl_1_bss_606, sel + 0x19001F);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    HuWinHomeClear(lbl_1_bss_606);
    sdWorkInt[3] = sel;
    for (i = 1; i <= 10; i++) {
        scale = i / 10.0;
        for (j = 0; j < 3; j++) {
            if (sel != j) {
                HuSprScaleSet(lbl_1_bss_718, j + 6, 0.8 * (1.0 - scale), 0.8 * (1.0 - scale));
            } else {
                posX = 188.0f + j * 100;
                posX = posX + (64.0f - posX) * scale;
                HuSprPosSet(lbl_1_bss_718, j + 6, posX, 250.0f);
            }
        }
        HuPrcVSleep();
    }
rule:
    HuSprPosSet(lbl_1_bss_718, 16, 238.0f, 250.0f);
    HuSprPosSet(lbl_1_bss_718, 17, 338.0f, 250.0f);
    sel = sdWorkInt[4];
    for (i = 1; i <= 20; i++) {
        scale = i / 20.0;
        for (j = 0; j < 2; j++) {
            if (sel == j) {
                HuSprScaleSet(lbl_1_bss_718, j + 16, scale, scale);
            } else {
                HuSprScaleSet(lbl_1_bss_718, j + 16, 0.8 * scale, 0.8 * scale);
            }
        }
        HuPrcVSleep();
    }
    HuWinMesSet(lbl_1_bss_606, sel + 0x190044);
    while (!(fn_1_4FD0(1 << a0) & 0x100)) {
        if (fn_1_4FD0(1 << a0) & 0x200) {
            HuAudFXPlay(3);
            HuWinHomeClear(lbl_1_bss_606);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                for (j = 0; j < 2; j++) {
                    if (sel == j) {
                        HuSprScaleSet(lbl_1_bss_718, j + 16, scale, scale);
                    } else {
                        HuSprScaleSet(lbl_1_bss_718, j + 16, 0.8 * scale, 0.8 * scale);
                    }
                }
                HuPrcVSleep();
            }
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                HuSprScaleSet(lbl_1_bss_718, sdWorkInt[3] + 6, scale, scale);
                HuPrcVSleep();
            }
            goto type;
        }
        move = 0;
        if ((fn_1_507C(1 << a0) & 1) && sel != 0) {
            move = -1;
        } else if ((fn_1_507C(1 << a0) & 2) && sel < 1) {
            move = 1;
        }
        if (move != 0) {
            HuAudFXPlay(0);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - 0.2 * (i / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 16, scale, scale);
                scale = 0.8 + 0.2 * (i / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 16 + move, scale, scale);
                HuPrcVSleep();
            }
            sel += move;
            HuWinMesSet(lbl_1_bss_606, sel + 0x190044);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    HuWinHomeClear(lbl_1_bss_606);
    sdWorkInt[4] = sel;
    for (i = 1; i <= 10; i++) {
        scale = i / 10.0;
        for (j = 0; j < 2; j++) {
            if (sel != j) {
                HuSprScaleSet(lbl_1_bss_718, j + 16, 0.8 * (1.0 - scale), 0.8 * (1.0 - scale));
            } else {
                posX = 238.0f + j * 100;
                posX = posX + (130.0f - posX) * scale;
                HuSprPosSet(lbl_1_bss_718, j + 16, posX, 250.0f);
            }
        }
        HuPrcVSleep();
    }
    sel = sdWorkInt[5];
    for (i = 0; i < 8; i++) {
        HuSprPosSet(lbl_1_bss_716, i, 288.0f, 250.0f);
    }
    HuSprPosSet(lbl_1_bss_718, 18, 224.0f, 250.0f);
    HuSprPosSet(lbl_1_bss_718, 19, 352.0f, 250.0f);
    HuSprTPLvlSet(lbl_1_bss_718, 18, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_718, 19, 0.0f);
    HuSprAttrReset(lbl_1_bss_716, sel, 4);
    HuSprTPLvlSet(lbl_1_bss_716, sel, 1.0f);
    for (i = 1; i <= 20; i++) {
        scale = i / 20.0;
        HuSprScaleSet(lbl_1_bss_716, sel, scale, scale);
        if (sel != 0) {
            HuSprTPLvlSet(lbl_1_bss_718, 18, scale);
        }
        if (sel < 7) {
            HuSprTPLvlSet(lbl_1_bss_718, 19, scale);
        }
        HuPrcVSleep();
    }
stage:
    sel = sdWorkInt[5];
    HuWinMesSet(lbl_1_bss_606, lbl_1_data_12A4[sel]);
    while (!(fn_1_4FD0(1 << a0) & 0x100)) {
        if (fn_1_4FD0(1 << a0) & 0x200) {
            HuAudFXPlay(3);
            HuWinHomeClear(lbl_1_bss_606);
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                HuSprTPLvlSet(lbl_1_bss_716, sel, scale);
                if (sel != 0) {
                    HuSprTPLvlSet(lbl_1_bss_718, 18, scale);
                }
                if (sel < 7) {
                    HuSprTPLvlSet(lbl_1_bss_718, 19, scale);
                }
                HuPrcVSleep();
            }
            for (i = 1; i <= 10; i++) {
                scale = 1.0 - i / 10.0;
                HuSprScaleSet(lbl_1_bss_718, sdWorkInt[4] + 16, scale, scale);
                HuPrcVSleep();
            }
            goto rule;
        }
        move = 0;
        if ((fn_1_507C(1 << a0) & 1) && sel != 0) {
            move = -1;
        } else if ((fn_1_507C(1 << a0) & 2) && sel < 7) {
            move = 1;
        }
        if (move != 0) {
            HuAudFXPlay(0);
            HuSprAttrReset(lbl_1_bss_716, sel, 4);
            HuSprAttrReset(lbl_1_bss_716, sel + move, 4);
            HuSprPriSet(lbl_1_bss_716, sel, 0x23);
            HuSprPriSet(lbl_1_bss_716, sel + move, 0x1E);
            for (i = 1; i <= 10; i++) {
                scale = i / 10.0;
                HuSprTPLvlSet(lbl_1_bss_716, sel + move, scale);
                if (sel + move == 0) {
                    HuSprTPLvlSet(lbl_1_bss_718, 18, 1.0 - scale);
                } else if (sel == 0) {
                    HuSprTPLvlSet(lbl_1_bss_718, 18, scale);
                }
                if (sel + move >= 7) {
                    HuSprTPLvlSet(lbl_1_bss_718, 19, 1.0 - scale);
                } else if (sel == 7) {
                    HuSprTPLvlSet(lbl_1_bss_718, 19, scale);
                }
                HuPrcVSleep();
            }
            HuSprAttrSet(lbl_1_bss_716, sel, 4);
            sel += move;
            HuWinMesSet(lbl_1_bss_606, lbl_1_data_12A4[sel]);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(2);
    HuPrcSleep(60);
    sdWorkInt[5] = sel;
    GwSdBattle.gameType = sdWorkInt[3];
    GwSdBattle.stageNo = lbl_1_data_12C4[sdWorkInt[5]];
    if (sdWorkInt[4] == 0) {
        GwPlayerConf[0].type = GwPlayerConf[1].type = 0;
        GwSdBattle.stageType1 = GwSdBattle.stageType2 = -1;
    } else {
        GwPlayerConf[0].type = GwPlayerConf[1].type = 1;
        GwPlayerConf[0].dif = GwPlayerConf[1].dif = 1;
        GwSdBattle.stageType1 = GwSdBattle.stageType2 = 1;
    }
    for (i = 0; i < 2; i++) {
        j = order[(&sdWorkInt[1])[i]];
        if (j < 2) {
            GwSdBattle.machine[i] = GwSdCommon.machine[j];
        } else {
            GwSdBattle.machine[i] = GwSdBackup[GwSdBackupNo].machine;
        }
        GwSdBattle.padNo[i] = j;
        GwPlayerConf[i].padNo = j;
    }
    fn_1_4238(2);
    while (1) {
        HuPrcVSleep();
    }
cancel:
    for (j = 0; j < 3; j++) {
        HuWinDispOff(win[j + 4]);
    }
    for (i = 1; i <= 10; i++) {
        scale = 1.0 - i / 10.0;
        for (j = 0; j < 3; j++) {
            HuWinScaleSet(win[j], 1.0f, scale);
            HuSprPosSet(lbl_1_bss_718, order[j] + 9, lbl_1_data_127C[j][0], lbl_1_data_127C[j][1]);
            HuSprScaleSet(lbl_1_bss_718, order[j] + 9, 1.0f, scale);
            fn_1_45E4(&mdl[j], scale, scale, scale);
        }
        HuPrcVSleep();
    }
    for (i = 0; i < 7; i++) {
        HuWinKill(win[i]);
    }
    for (i = 0; i < 3; i++) {
        HuSprPosSet(lbl_1_bss_718, i + 9, 0.0f, -1000.0f);
    }
    for (i = 0; i < 3; i++) {
        HuSprAttrSet(lbl_1_bss_718, i + 12, 4);
    }
    HuSprPosSet(lbl_1_bss_718, 15, 0.0f, -1000.0f);
    for (i = 0; i < 3; i++) {
        HuSprPosSet(lbl_1_bss_718, i + 6, 0.0f, -1000.0f);
    }
    for (i = 0; i < 2; i++) {
        HuSprPosSet(lbl_1_bss_718, i + 16, 0.0f, -1000.0f);
    }
    for (i = 0; i < 8; i++) {
        HuSprPosSet(lbl_1_bss_716, i, 0.0f, -1000.0f);
    }
    fn_1_4724(&mdl[0]);
    fn_1_4724(&mdl[1]);
    fn_1_4724(&mdl[2]);
    for (i = 0; i < 2; i++) {
        mp = &GwSdCommon.machine[i];
        if (mp->charNo != -1) {
            fn_1_46C4(&lbl_1_bss_67C[i], 1);
        }
    }
}

/* 1362 insns */
void fn_1_113F8(s16 a0)
{
    HuVecF basePos;
    HuVecF pos;
    GWSDCOMMON *common;
    HUWINID winId;
    HU3DMODELID mdlId;
    s16 num;
    s16 difNum;
    s16 dir;
    s16 sel;
    s16 j;
    s16 i;
    float t;
    float posX;
    float posY;

    common = &GwSdCommon;
    sdWorkInt[7] = a0;
    if (omovlevtno != 3) {
        sdWorkInt[6] = 0;
        sdWorkInt[3] = 0;
    }
    winId = HuWinCreate(-10000.0f, 310.0f, 0x230, 0x2A, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x20004);
restart:
    sel = sdWorkInt[3];
    if (common->flagHardWinF) {
        num = 3;
    } else if (common->battleHardWinF) {
        num = 2;
    } else {
        num = 1;
    }
    for (i = 0; i < num; i++) {
        HuSprPosSet(lbl_1_bss_718, i + 6, 288.0f - ((num * 100) / 2 - 50) + i * 100, 270.0f);
    }
    for (j = 1; j <= 20; j++) {
        t = j / 20.0;
        for (i = 0; i < num; i++) {
            if (sel == i) {
                HuSprScaleSet(lbl_1_bss_718, i + 6, t, t);
            } else {
                HuSprScaleSet(lbl_1_bss_718, i + 6, 0.8 * t, 0.8 * t);
            }
        }
        HuPrcVSleep();
    }
    HuWinMesSet(lbl_1_bss_606, sel + 0x19001F);
    while (!(fn_1_4FD0(1 << a0) & PAD_BUTTON_A)) {
        if (fn_1_4FD0(1 << a0) & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            goto exit;
        }
        dir = 0;
        if ((fn_1_507C(1 << a0) & PAD_BUTTON_LEFT) && sel != 0) {
            dir = -1;
        } else if ((fn_1_507C(1 << a0) & PAD_BUTTON_RIGHT) && sel < num - 1) {
            dir = 1;
        }
        if (dir != 0) {
            HuAudFXPlay(0);
            for (j = 1; j <= 10; j++) {
                t = 1.0 - 0.2 * (j / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 6, t, t);
                t = 0.8 + 0.2 * (j / 10.0);
                HuSprScaleSet(lbl_1_bss_718, 6 + sel + dir, t, t);
                if (j == 5) {
                    HuWinMesSet(lbl_1_bss_606, 0x19001F + sel + dir);
                }
                HuPrcVSleep();
            }
            sel += dir;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    sdWorkInt[3] = sel;
    for (j = 1; j <= 10; j++) {
        t = j / 10.0;
        for (i = 0; i < num; i++) {
            if (sel == i) {
                posX = 288.0f - ((num * 100) / 2 - 50) + i * 100;
                posX += (288.0f - posX) * t;
                posY = 270.0f + -68.0f * t;
                HuSprPosSet(lbl_1_bss_718, i + 6, posX, posY);
            } else {
                HuSprScaleSet(lbl_1_bss_718, i + 6, 0.8 * (1.0 - t), 0.8 * (1.0 - t));
            }
        }
        HuPrcVSleep();
    }
    sel = sdWorkInt[6] = 0;
    difNum = 2;
    if (sdWorkInt[3] == 0 && common->battleNormalWinF) {
        difNum = 3;
    }
    if (sdWorkInt[3] == 1 && common->flagNormalWinF) {
        difNum = 3;
    }
    if (sdWorkInt[3] == 2 && common->rabbitNormalWinF) {
        difNum = 3;
    }
    for (i = 0; i < difNum; i++) {
        HuSprPosSet(lbl_1_bss_718, i + 20, 288.0f - ((difNum * 100) / 2 - 50) + i * 100, 270.0f);
    }
    for (j = 1; j <= 20; j++) {
        t = j / 20.0;
        for (i = 0; i < difNum; i++) {
            if (sel == i) {
                HuSprScaleSet(lbl_1_bss_718, i + 20, t, t);
            } else {
                HuSprScaleSet(lbl_1_bss_718, i + 20, 0.8 * t, 0.8 * t);
            }
        }
        HuPrcVSleep();
    }
    sel = sdWorkInt[6];
    HuWinMesSet(lbl_1_bss_606, sel + 0x190046);
    while (!(fn_1_4FD0(1 << a0) & PAD_BUTTON_A)) {
        if (fn_1_4FD0(1 << a0) & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            for (j = 1; j <= 10; j++) {
                t = 1.0 - j / 10.0;
                for (i = 0; i < difNum; i++) {
                    if (sel == i) {
                        HuSprScaleSet(lbl_1_bss_718, i + 20, t, t);
                    } else {
                        HuSprScaleSet(lbl_1_bss_718, i + 20, 0.8 * t, 0.8 * t);
                    }
                }
                HuPrcVSleep();
            }
            for (j = 1; j <= 10; j++) {
                t = 1.0 - j / 10.0;
                HuSprScaleSet(lbl_1_bss_718, sdWorkInt[3] + 6, t, t);
                HuPrcVSleep();
            }
            goto restart;
        }
        dir = 0;
        if ((fn_1_507C(1 << a0) & PAD_BUTTON_LEFT) && sel != 0) {
            dir = -1;
        } else if ((fn_1_507C(1 << a0) & PAD_BUTTON_RIGHT) && sel < difNum - 1) {
            dir = 1;
        }
        if (dir != 0) {
            HuAudFXPlay(0);
            for (j = 1; j <= 10; j++) {
                t = 1.0 - 0.2 * (j / 10.0);
                HuSprScaleSet(lbl_1_bss_718, sel + 20, t, t);
                t = 0.8 + 0.2 * (j / 10.0);
                HuSprScaleSet(lbl_1_bss_718, 20 + sel + dir, t, t);
                if (j == 5) {
                    HuWinMesSet(lbl_1_bss_606, 0x190046 + sel + dir);
                }
                HuPrcVSleep();
            }
            sel += dir;
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    sdWorkInt[6] = sel;
    for (j = 1; j <= 10; j++) {
        t = j / 10.0;
        for (i = 0; i < difNum; i++) {
            if (sel == i) {
                posX = 288.0f - ((difNum * 100) / 2 - 50) + i * 100;
                posX += (288.0f - posX) * t;
                posY = 270.0f + -2.0f * t;
                HuSprPosSet(lbl_1_bss_718, i + 20, posX, posY);
            } else {
                HuSprScaleSet(lbl_1_bss_718, i + 20, 0.8 * (1.0 - t), 0.8 * (1.0 - t));
            }
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(0x50E);
    mdlId = lbl_1_bss_58C[a0 + 3];
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DMotionStartEndSet(mdlId, 61.0f, 600.0f);
    Hu3DMotionTimeSet(mdlId, 361.0f);
    Hu3DModelObjPosGet(mdlId, "cyl61", &basePos);
    while (Hu3DMotionTimeGet(mdlId) < 599.0f) {
        Hu3DModelObjPosGet(mdlId, "cyl61", &pos);
        fn_1_4534(&lbl_1_bss_67C[a0], 1450.0 * -HuSin(a0 * 60 + 60), pos.y - basePos.y, 1450.0 * -HuCos(a0 * 60 + 60));
        if (Hu3DMotionTimeGet(mdlId) == 540.0f) {
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
            HuAudFadeOut(1000);
        }
        HuPrcVSleep();
    }
    GwSdBattle.gameType = sdWorkInt[3];
    GwSdBattle.stageNo = 0;
    GwPlayerConf[0].type = 1;
    GwPlayerConf[1].type = 0;
    GwSdBattle.stageType1 = -1;
    GwSdBattle.stageType2 = 1;
    GwPlayerConf[1].dif = 1;
    GwSdBattle.machine[0] = GwSdCommon.machine[a0];
    GwSdBattle.machine[1] = GwSdCommon.machine[a0];
    GwSdBattle.padNo[0] = a0;
    GwPlayerConf[0].padNo = a0;
    GwSdBattle.padNo[1] = 3;
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
    Hu3DModelKill(lbl_1_bss_58C[0]);
    Hu3DModelKill(lbl_1_bss_58C[3]);
    Hu3DModelKill(lbl_1_bss_58C[4]);
    Hu3DModelKill(lbl_1_bss_58A);
    fn_1_4724(&lbl_1_bss_67C[0]);
    fn_1_4724(&lbl_1_bss_67C[1]);
    HuWinKill(winId);
    HuSprGrpKill(lbl_1_bss_718);
    HuWinKill(lbl_1_bss_606);
    lbl_1_bss_5B8 = 0.0f;
    Hu3DLayerHookReset(13);
    fn_1_1C260();
    while (1) {
        HuPrcVSleep();
    }
exit:
    HuWinKill(winId);
    for (j = 1; j <= 10; j++) {
        t = 1.0 - j / 10.0;
        for (i = 0; i < 3; i++) {
            if (sdWorkInt[3] == i) {
                HuSprScaleSet(lbl_1_bss_718, i + 6, t, t);
            } else {
                HuSprScaleSet(lbl_1_bss_718, i + 6, 0.8 * t, 0.8 * t);
            }
        }
        HuPrcVSleep();
    }
}

/* 0x12EC */ float lbl_1_data_12EC[10][2] = { { -150.0f, -40.0f }, { -75.0f, -40.0f }, { 0.0f, -40.0f }, { 75.0f, -40.0f }, { 150.0f, -40.0f }, { -150.0f, 40.0f }, { -75.0f, 40.0f }, { 0.0f, 40.0f }, { 75.0f, 40.0f }, { 150.0f, 40.0f } };
/* 0x133C */ float lbl_1_data_133C[11][2] = { { -175.0f, -40.0f }, { -105.0f, -40.0f }, { -35.0f, -40.0f }, { 35.0f, -40.0f }, { 105.0f, -40.0f }, { 175.0f, -40.0f }, { -140.0f, 40.0f }, { -70.0f, 40.0f }, { 0.0f, 40.0f }, { 70.0f, 40.0f }, { 140.0f, 40.0f } };
/* 0x1394 */ float (*lbl_1_data_1394[2])[2] = { lbl_1_data_12EC, lbl_1_data_133C }; /* {x, y} pairs: 10 and 11 */
/* 0x139C */ s16 lbl_1_data_139C[21][9] = { { 0, 0, 0, 0, 0, 1, 0, 5, 6 }, { 0, 0, 0, -1, 0, 1, 4, 5, 6 }, { 0, 0, 0, -1, 0, 1, 4, 5, 6 }, { 0, 0, 0, -1, 0, 1, 4, 5, 6 }, { 0, 0, 0, -1, 0, 0, 4, 5, 0 }, { 0, -5, -4, 0, 0, 1, 0, 0, 0 }, { -6, -5, -4, -1, 0, 1, 0, 0, 0 }, { -6, -5, -4, -1, 0, 1, 0, 0, 0 }, { -6, -5, -4, -1, 0, 1, 0, 0, 0 }, { -6, -5, 0, -1, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 1, 0, 6, 6 }, { 0, 0, 0, -1, 0, 1, 5, 6, 6 }, { 0, 0, 0, -1, 0, 1, 5, 6, 6 }, { 0, 0, 0, -1, 0, 1, 5, 6, 6 }, { 0, 0, 0, -1, 0, 1, 5, 6, 6 }, { 0, 0, 0, -1, 0, 0, 5, 5, 0 }, { -6, -6, -5, 0, 0, 1, 0, 0, 0 }, { -6, -6, -5, -1, 0, 1, 0, 0, 0 }, { -6, -6, -5, -1, 0, 1, 0, 0, 0 }, { -6, -6, -5, -1, 0, 1, 0, 0, 0 }, { -6, -6, -5, -1, 0, 0, 0, 0, 0 } };

/* 850 insns */
s32 fn_1_12940(s16 a0, s16 *partNo, void (*func)(s16 *, s16))
{
    HuVecF pos2D;
    HuVecF pos3D;
    s16 cursor[3];
    void (*callback)(s16 *, s16);
    HUPROCESS *process;
    s16 total;
    s16 dy;
    HUWINID winId;
    s32 result;
    s16 padBit;
    s16 m;
    s16 dx;
    s16 cur;
    s16 ext;
    s16 k;
    s16 i;
    s16 step;
    s16 num;
    float t;

    callback = func;
    ext = GwSdCommon.extCharSelF ? 1 : 0;
    num = ext + 10;
    if (ext == 0) {
        HuSprAttrSet(lbl_1_bss_714, 11, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(lbl_1_bss_714, 0, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 3; i++) {
        HuSprAttrSet(lbl_1_bss_714, i + 12, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < num; i++) {
        HuSprPosSet(lbl_1_bss_714, i + 1, lbl_1_data_1394[ext][i][0], lbl_1_data_1394[ext][i][1]);
        HuSprAttrReset(lbl_1_bss_714, i + 1, HUSPR_ATTR_DISPOFF);
    }
    for (i = 1; i <= 20; i++) {
        t = i / 20.0;
        HuSprGrpPosSet(lbl_1_bss_714, 288.0 + 640.0 * (1.0 - HuSin(90.0f * t)), 210.0f);
        HuPrcVSleep();
    }
    for (i = total = 0; i < 3; i++) {
        if (a0 & (1 << i)) {
            lbl_1_bss_5D0[i] = i;
            total++;
        } else {
            lbl_1_bss_5D0[i] = -1;
        }
        cursor[i] = i;
        lbl_1_bss_5D6[i] = -1;
    }
    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_5D0[i] != -1) {
            pos2D.x = 288.0f + lbl_1_data_1394[ext][i][0] - 32.0f;
            pos2D.y = 210.0f + lbl_1_data_1394[ext][i][1] - 32.0f;
            pos2D.z = 500.0f;
            Hu3D2Dto3D(&pos2D, 4, &pos3D);
            Hu3DModelPosSetV(lbl_1_bss_70E[i], &pos3D);
            Hu3DAnimAttrSet(lbl_1_bss_708[i], 1);
            Hu3DModelAttrReset(lbl_1_bss_70E[i], HU3D_ATTR_DISPOFF);
            Hu3DAnmNoSet(lbl_1_bss_708[i], lbl_1_bss_5D0[i]);
        }
    }
    result = 1;
    winId = HuWinCreate(-10000.0f, 310.0f, 0x230, 0x28, 0);
    HuWinBGTPLvlSet(winId, 0.0f);
    HuWinAttrSet(winId, 0x800);
    HuWinMesSpeedSet(winId, 0);
    HuWinMesSet(winId, 0x20004);
    while (1) {
        for (i = 0; i < 3; i++) {
            if (lbl_1_bss_5D0[i] == -1) {
                continue;
            }
            padBit = 1 << lbl_1_bss_5D0[i];
            if (lbl_1_bss_5D6[i] == -2) {
                continue;
            }
            if (lbl_1_bss_5D6[i] != -1) {
                if (fn_1_4FD0(padBit) & PAD_BUTTON_B) {
                    HuAudFXPlay(3);
                    process = HuPrcChildCreate(fn_1_138D0, 1000, 0x1000, 0, HuPrcCurrentGet());
                    process->property = (void *)(s32)((i << 8) | lbl_1_bss_5D6[i]);
                    Hu3DModelAttrReset(lbl_1_bss_70E[i], HU3D_ATTR_DISPOFF);
                    lbl_1_bss_5D6[i] = -2;
                }
                continue;
            }
            cur = cursor[i];
            dx = dy = 0;
            if (fn_1_507C(padBit) & PAD_BUTTON_LEFT) {
                dx = -1;
            } else if (fn_1_507C(padBit) & PAD_BUTTON_RIGHT) {
                dx = 1;
            }
            if (fn_1_507C(padBit) & PAD_BUTTON_UP) {
                dy = -1;
            } else if (fn_1_507C(padBit) & PAD_BUTTON_DOWN) {
                dy = 1;
            }
            if (dx != 0 || dy != 0) {
                step = 4 + dy * 3 + dx;
                step = lbl_1_data_139C[cur + ext * 10][step];
                for (k = 0; k < 3; k++) {
                    if (k != i && lbl_1_bss_5D0[k] != -1 && cur + step == cursor[k]) {
                        break;
                    }
                }
                if (k != 3) {
                    if (dy == 0) {
                        for (k = 1; k < 5; k++) {
                            for (m = 0; m < 3; m++) {
                                if (m != i && lbl_1_bss_5D0[m] != -1 && cursor[m] == cur + k * dx) {
                                    break;
                                }
                            }
                            if (m == 3) {
                                step = dx * k;
                                break;
                            }
                            if (lbl_1_data_139C[cur + (ext * 10 + dx * k)][dx + 4] == 0) {
                                step = 0;
                                break;
                            }
                        }
                    } else {
                        step = 0;
                    }
                }
                if (step != 0) {
                    HuAudFXPlay(0);
                    cur += step;
                    cursor[i] = cur;
                    pos2D.x = 288.0f + lbl_1_data_1394[ext][cur][0] - 32.0f;
                    pos2D.y = 210.0f + lbl_1_data_1394[ext][cur][1] - 32.0f;
                    pos2D.z = 500.0f;
                    Hu3D2Dto3D(&pos2D, 4, &pos3D);
                    Hu3DModelPosSetV(lbl_1_bss_70E[i], &pos3D);
                }
            }
            if (fn_1_4FD0(padBit) & PAD_BUTTON_A) {
                HuAudFXPlay(1);
                process = HuPrcChildCreate(fn_1_13688, 999, 0x1000, 0, HuPrcCurrentGet());
                process->property = (void *)(s32)((i << 8) | cur);
                Hu3DModelAttrSet(lbl_1_bss_70E[i], HU3D_ATTR_DISPOFF);
                lbl_1_bss_5D6[i] = -2;
            } else if (i == sdWorkInt[7] && (fn_1_4FD0(padBit) & PAD_BUTTON_B)) {
                HuAudFXPlay(3);
                Hu3DModelAttrSet(lbl_1_bss_70E[0], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_70E[1], HU3D_ATTR_DISPOFF);
                result = 0;
                break;
            }
        }
        if (result == 0) {
            break;
        }
        for (i = k = 0; i < 3; i++) {
            if (lbl_1_bss_5D6[i] >= 0) {
                k++;
            }
        }
        if (k == total) {
            result = 1;
            break;
        }
        HuPrcVSleep();
    }
    HuWinKill(winId);
    for (i = 0; i < 3; i++) {
        if (lbl_1_bss_5D0[i] == -1) {
            partNo[i] = -1;
        } else {
            partNo[i] = lbl_1_bss_5D6[i];
        }
    }
    for (i = k = 0; i < 3; i++) {
        Hu3DModelAttrSet(lbl_1_bss_70E[i], HU3D_ATTR_DISPOFF);
    }
    if (callback != 0) {
        callback(partNo, result);
    }
    for (i = 1; i <= 20; i++) {
        t = i / 20.0;
        HuSprGrpPosSet(lbl_1_bss_714, 288.0 + (result ? -1 : 1) * (640.0 * (1.0 - HuCos(90.0f * t))), 210.0f);
        HuPrcVSleep();
    }
    for (i = 0; i < 15; i++) {
        HuSprAttrSet(lbl_1_bss_714, i, HUSPR_ATTR_DISPOFF);
    }
    return result;
}

/* 146 insns */
void fn_1_13688(void)
{
    s16 ext;
    HUPROCESS *process;
    s32 property;
    s16 i;
    s16 partNo;
    s16 no;
    float t;

    process = HuPrcCurrentGet();
    property = (s32)process->property;
    no = (property >> 8) & 0xFF;
    partNo = property & 0xFF;
    ext = GwSdCommon.extCharSelF ? 1 : 0;
    HuSprAttrReset(lbl_1_bss_714, no + 12, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_714, no + 12, lbl_1_data_1394[ext][partNo][0], lbl_1_data_1394[ext][partNo][1] - 16.0f);
    HuSprBankSet(lbl_1_bss_714, no + 12, lbl_1_bss_5D0[no]);
    for (i = 1; i <= 10; i++) {
        t = i / 10.0;
        t = HuSin(90.0f * t) + 0.2 * HuSin(180.0f * t);
        HuSprScaleSet(lbl_1_bss_714, no + 12, t, t);
        HuPrcVSleep();
    }
    lbl_1_bss_5D6[no] = partNo;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 147 insns */
void fn_1_138D0(void)
{
    s16 ext;
    HUPROCESS *process;
    s32 property;
    s16 i;
    s16 partNo;
    s16 no;
    float t;

    process = HuPrcCurrentGet();
    property = (s32)process->property;
    no = (property >> 8) & 0xFF;
    partNo = property & 0xFF;
    ext = GwSdCommon.extCharSelF ? 1 : 0;
    HuSprPosSet(lbl_1_bss_714, no + 12, lbl_1_data_1394[ext][partNo][0], lbl_1_data_1394[ext][partNo][1] - 16.0f);
    HuSprBankSet(lbl_1_bss_714, no + 12, lbl_1_bss_5D0[no]);
    for (i = 1; i <= 5; i++) {
        t = i / 5.0;
        t = HuCos(90.0f * t) + 0.2 * HuSin(180.0f * t);
        HuSprScaleSet(lbl_1_bss_714, no + 12, t, t);
        HuPrcVSleep();
    }
    HuSprAttrSet(lbl_1_bss_714, no + 12, HUSPR_ATTR_DISPOFF);
    lbl_1_bss_5D6[no] = -1;
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

