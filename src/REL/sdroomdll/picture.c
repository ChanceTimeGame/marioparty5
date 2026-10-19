/*
 * sdroomdll picture.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/picture.s.
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

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const double lbl_1_rodata_518 = 1500.0; /* 0x518 */
static const double lbl_1_rodata_520 = -2.0943951023931953; /* 0x520 */
static const float lbl_1_rodata_528 = 200.0f; /* 0x528 */
static const double lbl_1_rodata_530 = 1300.0; /* 0x530 */
static const float lbl_1_rodata_538 = 70.0f; /* 0x538 */
static const double lbl_1_rodata_540 = 190.0; /* 0x540 */
static const double lbl_1_rodata_548 = -0.5235987755982988; /* 0x548 */
static const float lbl_1_rodata_550 = 0.0f; /* 0x550 */
static const float lbl_1_rodata_554 = -110.0f; /* 0x554 */
static const float lbl_1_rodata_558 = 1.2f; /* 0x558 */
static const float lbl_1_rodata_55C = 61.0f; /* 0x55C */
static const float lbl_1_rodata_560 = 830.0f; /* 0x560 */
static const double lbl_1_rodata_568 = 70.0; /* 0x568 */
static const double lbl_1_rodata_570 = 500.0; /* 0x570 */
static const double lbl_1_rodata_578 = 1.0; /* 0x578 */
static const double lbl_1_rodata_580 = 3.141592653589793; /* 0x580 */
static const double lbl_1_rodata_588 = 90.0; /* 0x588 */
static const double lbl_1_rodata_590 = 20.0; /* 0x590 */
static const double lbl_1_rodata_598 = 180.0; /* 0x598 */
static const float lbl_1_rodata_5A0 = 890.0f; /* 0x5A0 */
static const float lbl_1_rodata_5A4 = 831.0f; /* 0x5A4 */
static const float lbl_1_rodata_5A8 = 195.0f; /* 0x5A8 */
static const float lbl_1_rodata_5AC = -1155.0f; /* 0x5AC */
static const float lbl_1_rodata_5B0 = 1.8f; /* 0x5B0 */
/* 0x5B8 lbl_1_rodata_5B8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_5C0 = 156.0f; /* 0x5C0 */
static const float lbl_1_rodata_5C4 = 344.0f; /* 0x5C4 */
static const float lbl_1_rodata_5C8 = -10000.0f; /* 0x5C8 */
static const float lbl_1_rodata_5CC = -120.0f; /* 0x5CC */
static const float lbl_1_rodata_5D0 = 288.0f; /* 0x5D0 */
static const float lbl_1_rodata_5D4 = -1000.0f; /* 0x5D4 */
static const float lbl_1_rodata_5D8 = 5.0f; /* 0x5D8 */
static const float lbl_1_rodata_5DC = 20.0f; /* 0x5DC */
static const float lbl_1_rodata_5E0 = 15000.0f; /* 0x5E0 */
static const float lbl_1_rodata_5E4 = -3.5555496f; /* 0x5E4 */
static const float lbl_1_rodata_5E8 = 72.0f; /* 0x5E8 */
static const float lbl_1_rodata_5EC = 256.0f; /* 0x5EC */
static const float lbl_1_rodata_5F0 = 192.0f; /* 0x5F0 */
static const float lbl_1_rodata_5F4 = 1.0f; /* 0x5F4 */
static const float lbl_1_rodata_5F8 = 128.0f; /* 0x5F8 */
static const float lbl_1_rodata_5FC = 0.2f; /* 0x5FC */
static const float lbl_1_rodata_600 = 0.26666668f; /* 0x600 */
static const float lbl_1_rodata_604 = 6.933334f; /* 0x604 */
static const float lbl_1_rodata_608 = 118.66667f; /* 0x608 */
static const float lbl_1_rodata_60C = 60.0f; /* 0x60C */
static const float lbl_1_rodata_610 = 480.0f; /* 0x610 */
static const float lbl_1_rodata_614 = 0.75f; /* 0x614 */
static const float lbl_1_rodata_618 = 26.0f; /* 0x618 */
static const float lbl_1_rodata_61C = 445.0f; /* 0x61C */
static const double lbl_1_rodata_620 = 0.0; /* 0x620 */
/* 0x628 lbl_1_rodata_628 (0x1C): 0x00000000 0x00000000 0x00000000 0x00000000 0x43700000 0x00000000 0x43200000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_644 = 15.0f; /* 0x644 */
static const double lbl_1_rodata_648 = 10.0; /* 0x648 */
static const float lbl_1_rodata_650 = 275.0f; /* 0x650 */
static const float lbl_1_rodata_654 = 8100.0f; /* 0x654 */
static const float lbl_1_rodata_658 = 406.0f; /* 0x658 */
static const double lbl_1_rodata_660 = 0.1; /* 0x660 */
static const float lbl_1_rodata_668 = 360.0f; /* 0x668 */
static const float lbl_1_rodata_66C = 270.0f; /* 0x66C */
static const float lbl_1_rodata_670 = 2000.0f; /* 0x670 */
static const float lbl_1_rodata_674 = 4000.0f; /* 0x674 */
static const float lbl_1_rodata_678 = 180.0f; /* 0x678 */
/* 0x680 lbl_1_rodata_680 = 4503599627370496: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_688 = 30.0; /* 0x688 */
/* 0x690 lbl_1_rodata_690 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_694 = 255.0f; /* 0x694 */
static const float lbl_1_rodata_698 = 640.0f; /* 0x698 */
static const float lbl_1_rodata_69C = 10.0f; /* 0x69C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0xBFE gap_05_00000BFE_bss (0x2): alignment gap */
/* 0xBF8 */ s16 lbl_1_bss_BF8[3];
/* 0xBF0 */ s16 lbl_1_bss_BF0[4];
typedef struct SdPicSlot_s {
    HU3DMODELID mdl;   /* 0x0 */
    HU3DANIMID anim;   /* 0x2 */
    ANIMDATA *spr;     /* 0x4 */
    void *buf;         /* 0x8: framebuffer copy */
} SDPICSLOT; /* 0xC */
typedef struct SdPicWork_s {
    SDPICSLOT slot[11]; /* [10] = the large view */
    s16 unk84[76];      /* rest of the reference object (unreferenced) */
} SDPICWORK;
/* 0xAD4 */ SDPICWORK lbl_1_bss_AD4;
/* 0xAD2 */ s16 lbl_1_bss_AD2;
/* 0xAD0 */ s16 lbl_1_bss_AD0;
/* 0xAA4 */ SDMACHINEMDL lbl_1_bss_AA4;
/* 0xAA2 gap_05_00000AA2_bss (0x2): alignment gap */
/* 0xAA0 */ s16 lbl_1_bss_AA0;
/* 0xA9E */ s16 lbl_1_bss_A9E;
/* 0xA94 */ char lbl_1_bss_A94[0xA]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0xA90 */ float lbl_1_bss_A90;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x1860 */ OMCAMERAVIEW lbl_1_data_1860 = { { 433.0f, 200.0f, 250.0f }, { 0.0f, 240.0f, 0.0f }, 840.0f };

/* 39 insns */
void fn_1_19324(void)
{
    lbl_1_data_1860.center.x = 1500.0 * -sin(-2.0943951023931953);
    lbl_1_data_1860.center.y = 200.0f;
    lbl_1_data_1860.center.z = 1500.0 * -cos(-2.0943951023931953);
}

/* 346 insns */
void fn_1_193C0(void)
{
    HuVecF pos;
    s16 i;

    fn_1_19928();
    fn_1_1A17C();
    pos.x = 1300.0 * -sin(-2.0943951023931953);
    pos.y = 70.0f;
    pos.z = 1300.0 * -cos(-2.0943951023931953);
    pos.x += 190.0 * -sin(-0.5235987755982988);
    pos.z += 190.0 * -cos(-0.5235987755982988);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, -110.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.2f, 1.2f, 1.2f);
    Hu3DModelAttrReset(lbl_1_bss_58C[6], HU3D_MOTATTR_PAUSE | 0x40000000);
    Hu3DMotionTimeSet(lbl_1_bss_58C[6], 0.0f);
    HuAudFXPlay(0x50F);
    omCameraViewMoveMulti(4, &lbl_1_data_1860, 60, 0);
    HuPrcSleep(20);
    HuAudFXPlay(0x510);
    HuPrcSleep(40);
    Hu3DModelAttrSet(lbl_1_bss_58C[6], 0x40000001);
    Hu3DMotionStartEndSet(lbl_1_bss_58C[6], 61.0f, 830.0f);
    for(i = 1; i <= 20; i++) {
        pos.y = 70.0 + 500.0 * (1.0 - sin(3.141592653589793 * (90.0 * (i / 20.0)) / 180.0));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    HuWinExOpen(lbl_1_bss_AD2);
    HuWinMesSet(lbl_1_bss_AD2, 0x19000C);
    HuAudFXPlay(0x2EF);
    HuWinMesWait(lbl_1_bss_AD2);
    if(lbl_1_bss_AA0) {
        fn_1_1A958();
    } else {
        fn_1_1B640();
    }
    HuWinExClose(lbl_1_bss_AD2);
    for(i = 1; i <= 20; i++) {
        pos.y = 90.0 + 500.0 * (1.0 - cos(3.141592653589793 * (90.0 * (i / 20.0)) / 180.0));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    HuAudFXPlay(0x510);
    Hu3DModelAttrReset(lbl_1_bss_58C[6], 0x40000001);
    Hu3DMotionStartEndSet(lbl_1_bss_58C[6], 61.0f, 890.0f);
    Hu3DMotionTimeSet(lbl_1_bss_58C[6], 831.0f);
    HuPrcSleep(40);
    HuAudFXPlay(0x50F);
    while(!Hu3DMotionEndCheck(lbl_1_bss_58C[6])) {
        HuPrcVSleep();
    }
    Hu3DModelPosSet(lbl_1_bss_58A, 0.0f, 195.0f, -1155.0f);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.8f, 1.8f, 1.8f);
    fn_1_19FC0();
    fn_1_1C13C();
    HuDataDirClose(0xBC0000);
}

/* 0x187C */ OMCAMERAVIEW lbl_1_data_187C = { { 0.0f, 100.0f, 0.0f }, { 330.0f, 0.0f, 0.0f }, 5300.0f };
/* 0x1898 */ HuVecF lbl_1_data_1898 = { 1314.6f, 335.0f, 759.0f };
/* 0x18A4 */ HuVecF lbl_1_data_18A4[2] = { { 1344.6f, 335.0f, 707.0f }, { 1287.1f, 335.0f, 806.6f } };
/* 0x18BC */ HuVecF lbl_1_data_18BC[3] = { { 1314.6f, 335.0f, 759.0f }, { 1344.6f, 220.0f, 707.0f }, { 1287.1f, 220.0f, 806.6f } };
/* 0x18E0 */ HuVecF lbl_1_data_18E0[4] = { { 1344.6f, 335.0f, 707.0f }, { 1287.1f, 335.0f, 806.6f }, { 1344.6f, 220.0f, 707.0f }, { 1287.1f, 220.0f, 806.6f } };
/* 0x1910 */ HuVecF lbl_1_data_1910[5] = { { 1344.6f, 335.0f, 707.0f }, { 1287.1f, 335.0f, 806.6f }, { 1372.1f, 220.0f, 659.4f }, { 1314.6f, 220.0f, 759.0f }, { 1257.1f, 220.0f, 858.5f } };
/* 0x194C */ HuVecF lbl_1_data_194C[6] = { { 1372.1f, 335.0f, 659.4f }, { 1314.6f, 335.0f, 759.0f }, { 1257.1f, 335.0f, 858.5f }, { 1372.1f, 220.0f, 659.4f }, { 1314.6f, 220.0f, 759.0f }, { 1257.1f, 220.0f, 858.5f } };
/* 0x1994 */ HuVecF lbl_1_data_1994[7] = { { 1372.1f, 335.0f, 659.4f }, { 1314.6f, 335.0f, 759.0f }, { 1257.1f, 335.0f, 858.5f }, { 1402.1f, 220.0f, 607.4f }, { 1344.6f, 220.0f, 707.0f }, { 1287.1f, 220.0f, 806.6f }, { 1229.6f, 220.0f, 906.2f } };
/* 0x19E8 */ HuVecF lbl_1_data_19E8[8] = { { 1402.1f, 335.0f, 607.4f }, { 1344.6f, 335.0f, 707.0f }, { 1287.1f, 335.0f, 806.6f }, { 1229.6f, 335.0f, 906.2f }, { 1402.1f, 220.0f, 607.4f }, { 1344.6f, 220.0f, 707.0f }, { 1287.1f, 220.0f, 806.6f }, { 1229.6f, 220.0f, 906.2f } };
/* 0x1A48 */ HuVecF lbl_1_data_1A48[9] = { { 1402.1f, 335.0f, 607.4f }, { 1344.6f, 335.0f, 707.0f }, { 1287.1f, 335.0f, 806.6f }, { 1229.6f, 335.0f, 906.2f }, { 1429.6f, 220.0f, 559.4f }, { 1372.1f, 220.0f, 659.4f }, { 1314.6f, 220.0f, 759.0f }, { 1257.1f, 220.0f, 858.5f }, { 1199.6f, 220.0f, 958.1f } };
/* 0x1AB4 */ HuVecF lbl_1_data_1AB4[10] = { { 1429.6f, 335.0f, 559.8f }, { 1372.1f, 335.0f, 659.4f }, { 1314.6f, 335.0f, 759.0f }, { 1257.1f, 335.0f, 858.5f }, { 1199.6f, 335.0f, 958.1f }, { 1429.6f, 220.0f, 559.4f }, { 1372.1f, 220.0f, 659.4f }, { 1314.6f, 220.0f, 759.0f }, { 1257.1f, 220.0f, 858.5f }, { 1199.6f, 220.0f, 958.1f } };
/* 0x1B2C */ HuVecF *lbl_1_data_1B2C[10] = { &lbl_1_data_1898, lbl_1_data_18A4, lbl_1_data_18BC, lbl_1_data_18E0, lbl_1_data_1910, lbl_1_data_194C, lbl_1_data_1994, lbl_1_data_19E8, lbl_1_data_1A48, lbl_1_data_1AB4 }; /* entry n: n+1 positions */

/* 422 insns */
void fn_1_19928(void)
{
    HUWIN *winP;
    HUSPRGRPID grp;
    HUSPRID spr;
    s16 win;
    HU3DMODELID mdl;
    s16 i;

    lbl_1_bss_AA0 = i = 0;
    for(; i < 10; i++) {
        if(GwSdCommon.picture[i].number != 0xFFFF) {
            lbl_1_bss_AA0++;
        }
    }
    Hu3DModelAttrSet(lbl_1_bss_58C[1], 1);
    Hu3DModelAttrSet(lbl_1_bss_58C[5], 1);
    Hu3DModelAttrSet(lbl_1_bss_58C[3], 1);
    Hu3DModelAttrSet(lbl_1_bss_58C[4], 1);
    Hu3DModelAttrSet(lbl_1_bss_58C[2], 1);
    fn_1_7320();
    fn_1_16064();
    lbl_1_bss_AD2 = HuWinExCreateFrame(156.0f, 344.0f, 400, 94, -1, 1);
    winP = &winData[lbl_1_bss_AD2];
    winP->padMask = 1;
    HuWinMesPalSet(lbl_1_bss_AD2, 7, 0, 0, 0);
    HuWinMesSpeedSet(lbl_1_bss_AD2, 0);
    HuWinPriSet(lbl_1_bss_AD2, 0x32);
    for(i = 0; i < 3; i++) {
        win = HuWinCreate(-10000.0f, i * 0x1A + 10, 0x240, 0x2A, 0);
        lbl_1_bss_BF8[i] = win;
        HuWinMesSpeedSet(win, 0);
        HuWinPriSet(win, 0x28);
        HuWinDrawNoSet(win, 0x60);
        HuWinAttrSet(win, 0x800);
        HuWinBGTPLvlSet(win, 0.0f);
    }
    if(lbl_1_bss_AA0) {
        for(i = 0; i < lbl_1_bss_AA0; i++) {
            mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0xBE0005, 0x10000000, 2));
            lbl_1_bss_AD4.slot[i].mdl = mdl;
            Hu3DModelCameraSet(mdl, 4);
            Hu3DModelPosSetV(mdl, &lbl_1_data_1B2C[lbl_1_bss_AA0 - 1][i]);
            Hu3DModelRotSet(mdl, 0.0f, -120.0f, 0.0f);
            lbl_1_bss_AD4.slot[i].buf = HuMemDirectMallocNum(2, GXGetTexBufferSize(0x80, 0x80, 5, 0, 0), 0x10000000);
            lbl_1_bss_AD4.slot[i].spr = HuSprAnimMake(0x80, 0x80, 2);
            lbl_1_bss_AD4.slot[i].spr->bmp->data = lbl_1_bss_AD4.slot[i].buf;
            lbl_1_bss_AD4.slot[i].anim = Hu3DAnimCreate(lbl_1_bss_AD4.slot[i].spr, mdl, "picture");
        }
        mdl = Hu3DModelCreate(HuDataSelHeapReadNum(0xBE0005, 0x10000000, 2));
        lbl_1_bss_AD4.slot[10].mdl = mdl;
        Hu3DModelCameraSet(mdl, 4);
        Hu3DModelAttrSet(mdl, 1);
        Hu3DModelPosSetV(mdl, &lbl_1_data_1B2C[lbl_1_bss_AA0 - 1][i]);
        Hu3DModelRotSet(mdl, 0.0f, -120.0f, 0.0f);
        lbl_1_bss_AD4.slot[10].buf = HuMemDirectMallocNum(2, GXGetTexBufferSize(0x1E0, 0x1E0, 5, 0, 0), 0x10000000);
        lbl_1_bss_AD4.slot[10].spr = HuSprAnimMake(0x1E0, 0x1E0, 2);
        lbl_1_bss_AD4.slot[10].spr->bmp->data = lbl_1_bss_AD4.slot[10].buf;
        lbl_1_bss_AD4.slot[10].anim = Hu3DAnimCreate(lbl_1_bss_AD4.slot[10].spr, mdl, "picture");
    }
    fn_1_480C(&lbl_1_bss_AA4);
    grp = HuSprGrpCreate(1);
    lbl_1_bss_BF0[0] = grp;
    spr = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(0xE70001, 0x10000000, 2)), 0x32, 0);
    HuSprGrpMemberSet(grp, 0, spr);
    HuSprPosSet(grp, 0, 288.0f, -1000.0f);
    Hu3DCameraPerspectiveSet(8, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(8, -3.5555496f, 72.0f, 256.0f, 192.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(8, 0x16, 0x4C, 0xCC, 0xB8);
    omCameraViewSetMulti(8, &lbl_1_data_187C);
    HuSprExecLayerCameraSet(0x60, 1, 4);
}

/* 111 insns */
void fn_1_19FC0(void)
{
    s16 i;

    if(lbl_1_bss_AA0) {
        for(i = 0; i < lbl_1_bss_AA0; i++) {
            Hu3DModelKill(lbl_1_bss_AD4.slot[i].mdl);
            Hu3DAnimKill(lbl_1_bss_AD4.slot[i].anim);
            HuMemDirectFree(lbl_1_bss_AD4.slot[i].buf);
        }
        Hu3DModelKill(lbl_1_bss_AD4.slot[10].mdl);
        Hu3DAnimKill(lbl_1_bss_AD4.slot[10].anim);
        HuMemDirectFree(lbl_1_bss_AD4.slot[10].buf);
    }
    Hu3DModelAttrReset(lbl_1_bss_58C[1], 1);
    Hu3DModelAttrReset(lbl_1_bss_58C[5], 1);
    Hu3DModelAttrReset(lbl_1_bss_58C[3], 1);
    Hu3DModelAttrReset(lbl_1_bss_58C[4], 1);
    Hu3DModelAttrReset(lbl_1_bss_58C[2], 1);
    fn_1_7298();
    fn_1_16024();
    HuWinKill(lbl_1_bss_AD2);
    HuSprGrpKill(lbl_1_bss_BF0[0]);
    for(i = 0; i < 3; i++) {
        HuWinKill(lbl_1_bss_BF8[i]);
    }
    fn_1_4724(&lbl_1_bss_AA4);
    Hu3DLayerHookReset(12);
    Hu3DLayerHookReset(4);
}

/* 235 insns */
void fn_1_1A17C(void)
{
    SDMACHINEMDL machine;
    char buf[12];
    GWSDPICTURE *pic;
    GWSDMACHINE *mach;
    float sx, sy;

    if(lbl_1_bss_AA0) {
        lbl_1_bss_A90 = 0.0f;
        Hu3DLayerHookSet(12, fn_1_1A850);
        Hu3DCameraPerspectiveSet(1, 5.0f, 20.0f, 15000.0f, 1.2f);
        Hu3DCameraViewportSet(1, 0.0f, 0.0f, 128.0f, 128.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(1, 0, 0, 0x80, 0x80);
        omCameraViewSetMulti(1, &lbl_1_data_187C);
        sx = 0.2f;
        sy = 0.26666668f;
        for(lbl_1_bss_A9E = 0; lbl_1_bss_A9E < lbl_1_bss_AA0; lbl_1_bss_A9E++) {
            pic = &GwSdCommon.picture[lbl_1_bss_A9E];
            mach = &pic->machine;
            sprintf(buf, "%d", pic->number);
            HuWinInsertMesSet(lbl_1_bss_BF8[0], MESSNUM_PTR(buf), 0);
            HuWinMesSet(lbl_1_bss_BF8[0], 0x190033);
            HuWinPosSet(lbl_1_bss_BF8[0], 0.0f, 0.0f);
            HuWinScaleSet(lbl_1_bss_BF8[0], sx, sy);
            HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->type + 0x190035, 1);
            HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->diff + 0x190038, 2);
            HuWinMesSet(lbl_1_bss_BF8[1], 0x190034);
            HuWinPosSet(lbl_1_bss_BF8[1], 0.0f, 6.933334f);
            HuWinScaleSet(lbl_1_bss_BF8[1], sx, sy);
            HuWinMesSet(lbl_1_bss_BF8[2], MESSNUM_PTR(mach->name));
            HuWinPosSet(lbl_1_bss_BF8[2], 0.0f, 118.66667f);
            HuWinScaleSet(lbl_1_bss_BF8[2], sx, sy);
            fn_1_42E0(&machine, mach->partNo[0], mach->partNo[1], mach->partNo[3], mach->charNo);
            fn_1_4638(&machine, 1);
            fn_1_4590(&machine, 0.0f, 60.0f, 0.0f);
            HuPrcSleep(2);
            fn_1_4724(&machine);
        }
        lbl_1_bss_A9E = -1;
    }
}

void fn_1_1A528(s16 a0)
{
    GWSDPICTURE *pic;
    GWSDMACHINE *mach;
    float sx, sy;

    Hu3DCameraPerspectiveSet(1, 5.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 480.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 0x1E0, 0x1E0);
    omCameraViewSetMulti(1, &lbl_1_data_187C);
    pic = &GwSdCommon.picture[a0];
    mach = &pic->machine;
    sx = 0.75f;
    sy = 1.0f;
    sprintf(lbl_1_bss_A94, "%d", pic->number);
    HuWinInsertMesSet(lbl_1_bss_BF8[0], MESSNUM_PTR(lbl_1_bss_A94), 0);
    HuWinMesSet(lbl_1_bss_BF8[0], 0x190033);
    HuWinPosSet(lbl_1_bss_BF8[0], 0.0f, 0.0f);
    HuWinScaleSet(lbl_1_bss_BF8[0], sx, sy);
    HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->type + 0x190035, 1);
    HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->diff + 0x190038, 2);
    HuWinMesSet(lbl_1_bss_BF8[1], 0x190034);
    HuWinPosSet(lbl_1_bss_BF8[1], 0.0f, 26.0f);
    HuWinScaleSet(lbl_1_bss_BF8[1], sx, sy);
    HuWinMesSet(lbl_1_bss_BF8[2], MESSNUM_PTR(mach->name));
    HuWinPosSet(lbl_1_bss_BF8[2], 0.0f, 445.0f);
    HuWinScaleSet(lbl_1_bss_BF8[2], sx, sy);
    fn_1_4724(&lbl_1_bss_AA4);
    fn_1_42E0(&lbl_1_bss_AA4, mach->partNo[0], mach->partNo[1], mach->partNo[3], mach->charNo);
    fn_1_4638(&lbl_1_bss_AA4, 1);
    fn_1_4590(&lbl_1_bss_AA4, 0.0f, 60.0f, 0.0f);
    lbl_1_bss_A9E = 0x12;
}

void fn_1_1A850(s16 layerNo)
{
    if(Hu3DCameraNo == 0 && lbl_1_bss_A9E >= 0) {
        if(lbl_1_bss_A9E >= 0 && lbl_1_bss_A9E < 10) {
            Hu3DFbCopyExec(0, 0, 0x80, 0x80, 5, 0, lbl_1_bss_AD4.slot[lbl_1_bss_A9E].buf);
        } else {
            if(0.0 != lbl_1_bss_A90) {
                fn_1_1BDF8(lbl_1_bss_A90);
            }
            Hu3DFbCopyExec(0, 0, 0x1E0, 0x1E0, 5, 0, lbl_1_bss_AD4.slot[10].buf);
        }
        Hu3DZClear();
    }
}

void fn_1_1A958(void)
{
    OMCAMERAVIEW view = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 240.0f, 0.0f }, 160.0f };
    HuVecF pos2d;
    HuVecF *posTbl;
    GWSDPICTURE *pic;
    GWSDMACHINE *mach;
    s16 win;
    s16 dy;
    s16 sel;
    s16 dx;
    s16 i;
    float sy, dz;
    float sc, sx;

    Hu3D3Dto2D(lbl_1_data_1B2C[lbl_1_bss_AA0 - 1], 4, &pos2d);
    HuSprPosSet(lbl_1_bss_BF0[0], 0, pos2d.x - 20.0f, pos2d.y - 15.0f);
    for(i = 1; i <= 10; i++) {
        sc = i / 10.0;
        HuSprScaleSet(lbl_1_bss_BF0[0], 0, sc, sc);
        HuPrcVSleep();
    }
    win = HuWinCreate(-10000.0f, 275.0f, 0x220, 0x1A, 0);
    lbl_1_bss_AD0 = win;
    HuWinMesSpeedSet(win, 0);
    HuWinPriSet(win, 0x28);
    HuWinAttrSet(win, 0x800);
    HuWinBGTPLvlSet(win, 0.0f);
    HuWinMesSet(win, 0x20004);
    sel = 0;
    HuWinMesSet(lbl_1_bss_AD2, 0x19005E);
    while(1) {
        posTbl = lbl_1_data_1B2C[lbl_1_bss_AA0 - 1];
        dy = 0;
        dx = dy;
        if(HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
            for(i = lbl_1_bss_AA0 - 1; i >= 0; i--) {
                if(posTbl[sel].z > posTbl[i].z && posTbl[sel].y == posTbl[i].y) {
                    break;
                }
            }
            if(i >= 0) {
                sel = i;
                dx = -1;
            }
        } else if(HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
            for(i = 0; i < lbl_1_bss_AA0; i++) {
                if(posTbl[sel].z < posTbl[i].z && posTbl[sel].y == posTbl[i].y) {
                    break;
                }
            }
            if(i != lbl_1_bss_AA0) {
                sel = i;
                dx = 1;
            }
        }
        if(HuPadDStkRep[0] & PAD_BUTTON_UP) {
            for(i = 0; i < lbl_1_bss_AA0; i++) {
                dz = posTbl[sel].z - posTbl[i].z;
                if(dz * dz < 8100.0f && posTbl[sel].y < posTbl[i].y) {
                    break;
                }
            }
            if(i != lbl_1_bss_AA0) {
                sel = i;
                dy = -1;
            }
        } else if(HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
            for(i = 0; i < lbl_1_bss_AA0; i++) {
                dz = posTbl[sel].z - posTbl[i].z;
                if(dz * dz < 8100.0f && posTbl[sel].y > posTbl[i].y) {
                    break;
                }
            }
            if(i != lbl_1_bss_AA0) {
                sel = i;
                dy = 1;
            }
        }
        if(dx != 0 || dy != 0) {
            HuAudFXPlay(0);
            Hu3D3Dto2D(&lbl_1_data_1B2C[lbl_1_bss_AA0 - 1][sel], 4, &pos2d);
            HuSprPosSet(lbl_1_bss_BF0[0], 0, pos2d.x - 20.0f, pos2d.y - 15.0f);
        }
        if(HuPadBtnDown[0] & PAD_BUTTON_A) {
            if(GwSdCommon.picture[sel].number != 0xFFFF) {
                HuAudFXPlay(1);
                HuWinDispOff(lbl_1_bss_AD0);
                HuWinExClose(lbl_1_bss_AD2);
                Hu3DCameraPerspectiveSet(1, 5.0f, 20.0f, 15000.0f, 1.2f);
                Hu3DCameraViewportSet(1, 0.0f, 0.0f, 480.0f, 480.0f, 0.0f, 1.0f);
                Hu3DCameraScissorSet(1, 0, 0, 0x1E0, 0x1E0);
                omCameraViewSetMulti(1, &lbl_1_data_187C);
                pic = &GwSdCommon.picture[sel];
                mach = &pic->machine;
                sx = 0.75f;
                sy = 1.0f;
                sprintf(lbl_1_bss_A94, "%d", pic->number);
                HuWinInsertMesSet(lbl_1_bss_BF8[0], MESSNUM_PTR(lbl_1_bss_A94), 0);
                HuWinMesSet(lbl_1_bss_BF8[0], 0x190033);
                HuWinPosSet(lbl_1_bss_BF8[0], 0.0f, 0.0f);
                HuWinScaleSet(lbl_1_bss_BF8[0], sx, sy);
                HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->type + 0x190035, 1);
                HuWinInsertMesSet(lbl_1_bss_BF8[1], pic->diff + 0x190038, 2);
                HuWinMesSet(lbl_1_bss_BF8[1], 0x190034);
                HuWinPosSet(lbl_1_bss_BF8[1], 0.0f, 26.0f);
                HuWinScaleSet(lbl_1_bss_BF8[1], sx, sy);
                HuWinMesSet(lbl_1_bss_BF8[2], MESSNUM_PTR(mach->name));
                HuWinPosSet(lbl_1_bss_BF8[2], 0.0f, 445.0f);
                HuWinScaleSet(lbl_1_bss_BF8[2], sx, sy);
                fn_1_4724(&lbl_1_bss_AA4);
                fn_1_42E0(&lbl_1_bss_AA4, mach->partNo[0], mach->partNo[1], mach->partNo[3], mach->charNo);
                fn_1_4638(&lbl_1_bss_AA4, 1);
                fn_1_4590(&lbl_1_bss_AA4, 0.0f, 60.0f, 0.0f);
                lbl_1_bss_A9E = 0x12;
                view.center = lbl_1_data_1B2C[lbl_1_bss_AA0 - 1][sel];
                omCameraViewMoveMulti(4, &view, 0x1E, 0);
                for(i = 1; i <= 10; i++) {
                    sc = 1.0 - i / 10.0;
                    HuSprScaleSet(lbl_1_bss_BF0[0], 0, sc, sc);
                    HuPrcVSleep();
                }
                Hu3DModelAttrSet(lbl_1_bss_AD4.slot[sel].mdl, 1);
                Hu3DModelAttrReset(lbl_1_bss_AD4.slot[10].mdl, 1);
                Hu3DModelPosSetV(lbl_1_bss_AD4.slot[10].mdl, &lbl_1_data_1B2C[lbl_1_bss_AA0 - 1][sel]);
                HuPrcSleep(20);
                HuWinPosSet(lbl_1_bss_AD0, -10000.0f, 406.0f);
                HuWinMesSet(lbl_1_bss_AD0, 0x2001A);
                HuWinDispOn(lbl_1_bss_AD0);
                fn_1_1B72C(sel);
                HuWinMesSet(lbl_1_bss_AD0, 0x20004);
                HuWinDispOff(lbl_1_bss_AD0);
                omCameraViewMoveMulti(4, &lbl_1_data_1860, 0x1E, 0);
                for(i = 1; i <= 10; i++) {
                    sc = i / 10.0;
                    HuSprScaleSet(lbl_1_bss_BF0[0], 0, sc, sc);
                    HuPrcVSleep();
                }
                Hu3DModelAttrReset(lbl_1_bss_AD4.slot[sel].mdl, 1);
                Hu3DModelAttrSet(lbl_1_bss_AD4.slot[10].mdl, 1);
                HuPrcSleep(20);
                HuWinPosSet(lbl_1_bss_AD0, -10000.0f, 275.0f);
                HuWinDispOn(lbl_1_bss_AD0);
                lbl_1_bss_A90 = 0.0f;
                HuWinExOpen(lbl_1_bss_AD2);
                HuWinMesSet(lbl_1_bss_AD2, 0x19005E);
            } else {
                HuAudFXPlay(4);
            }
        }
        if(HuPadBtnDown[0] & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            break;
        }
        HuPrcVSleep();
    }
    HuWinKill(lbl_1_bss_AD0);
    for(i = 1; i <= 10; i++) {
        sc = 1.0 - i / 10.0;
        HuSprScaleSet(lbl_1_bss_BF0[0], 0, sc, sc);
        HuPrcVSleep();
    }
}

void fn_1_1B640(void)
{
    s16 win;

    win = HuWinCreate(-10000.0f, 275.0f, 0x220, 0x1A, 0);
    lbl_1_bss_AD0 = win;
    HuWinMesSpeedSet(win, 0);
    HuWinPriSet(win, 0x28);
    HuWinAttrSet(win, 0x800);
    HuWinBGTPLvlSet(win, 0.0f);
    HuWinMesSet(win, 0x2000B);
    HuWinMesSet(lbl_1_bss_AD2, 0x19005F);
    while(!(HuPadBtnDown[0] & 0x200)) {
        HuPrcVSleep();
    }
    HuWinKill(lbl_1_bss_AD0);
}

void fn_1_1B72C(s16 a0)
{
    HuVecF rot = lbl_1_data_187C.rot;
    HuVecF cur;
    HuVec2f size;
    HUWIN *winP;
    float zoom;
    float t;
    s16 win;
    s16 choice;
    s16 i;

    zoom = lbl_1_data_187C.zoom;
    while(!(HuPadBtnDown[0] & PAD_BUTTON_B)) {
        if(HuPadBtnDown[0] & PAD_BUTTON_X) {
            HuWinMesMaxSizeGet(1, &size, 0x190066);
            win = HuWinExCreate(-10000.0f, 200.0f, size.x, size.y, -1);
            winP = &winData[win];
            winP->padMask = 1;
            HuWinPriSet(win, 10);
            HuWinExOpen(win);
            HuWinMesSet(win, 0x190066);
            HuWinMesWait(win);
            choice = HuWinChoiceGet(win, -1);
            if(choice == 0) {
                HuWinExClose(win);
                HuWinKill(win);
                HuAudFXPlay(6);
                fn_1_1BCD4(a0);
                return;
            }
            HuWinExClose(win);
            HuWinKill(win);
        }
        if(HuPadStkX[0] & 0xF0) {
            rot.y += 0.1 * HuPadStkX[0];
            if(rot.y > 360.0f) {
                rot.y -= 360.0f;
            }
            if(rot.y < 0.0f) {
                rot.y += 360.0f;
            }
        }
        if(HuPadStkY[0] & 0xF0) {
            rot.x += 0.1 * HuPadStkY[0];
            if(rot.x > 360.0f) {
                rot.x = 360.0f;
            }
            if(rot.x < 270.0f) {
                rot.x = 270.0f;
            }
        }
        zoom += HuPadTrigL[0];
        zoom -= HuPadTrigR[0];
        if(zoom < lbl_1_data_187C.zoom - 2000.0f) {
            zoom = lbl_1_data_187C.zoom - 2000.0f;
        }
        if(zoom > 4000.0f + lbl_1_data_187C.zoom) {
            zoom = 4000.0f + lbl_1_data_187C.zoom;
        }
        CRotM[0] = rot;
        CZoomM[0] = zoom;
        HuPrcVSleep();
    }
    HuAudFXPlay(3);
    if(rot.x != lbl_1_data_187C.rot.x || rot.y != lbl_1_data_187C.rot.y) {
        if(rot.y > 180.0f) {
            rot.y -= 360.0f;
        }
        for(i = 1; i <= 10; i++) {
            t = i / 10.0;
            cur.x = rot.x + t * (lbl_1_data_187C.rot.x - rot.x);
            cur.y = rot.y + t * (lbl_1_data_187C.rot.y - rot.y);
            cur.z = rot.z;
            CRotM[0] = cur;
            CZoomM[0] = zoom + t * (lbl_1_data_187C.zoom - zoom);
            HuPrcVSleep();
        }
    }
}

void fn_1_1BCD4(s16 a0)
{
    s16 j;
    u16 *buf;
    s32 i;

    for(j = 1; j <= 30; j++) {
        lbl_1_bss_A90 = j / 30.0;
        HuPrcVSleep();
    }
    buf = lbl_1_bss_AD4.slot[a0].buf;
    for(i = 0; i < 0x4000; i++, buf++) {
        *buf = 0x8000;
    }
    DCFlushRange(lbl_1_bss_AD4.slot[a0].buf, 0x8000);
    GwSdCommon.picture[a0].number = 0xFFFF;
}

void fn_1_1BDF8(float a0)
{
    GXColor color = { 0, 0, 0, 0 };
    GXColor *colorP;
    Mtx44 proj;
    Mtx mtx;

    color.a = 255.0f * a0;
    C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    PSMTXIdentity(mtx);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 0x280, 0x1E0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetAlphaUpdate(GX_FALSE);
    GXSetColorUpdate(GX_TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition2s16(0, 0);
    GXPosition2s16(640, 0);
    GXPosition2s16(640, 480);
    GXPosition2s16(0, 480);
}

void fn_1_1C13C(void)
{
    GWSDPICTURE *pic;
    s16 i, j;

    for(i = 8; i >= 0; i--) {
        pic = &GwSdCommon.picture[i];
        if(pic->number == 0xFFFF) {
            for(j = i; j < 9; j++) {
                GwSdCommon.picture[j] = GwSdCommon.picture[j + 1];
            }
            GwSdCommon.picture[9].number = 0xFFFF;
        }
    }
}

