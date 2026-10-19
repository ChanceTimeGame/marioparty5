/*
 * sdroomdll garagesave.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sdroomdll/asm/REL/sdroomdll/garagesave.s.
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
#include "game/saveload.h"
#include "game/card.h"
#include "messnum/mpsystem.h"
#include "string.h"
#ifndef __MWERKS__
/* retail calls sprintf unprototyped (no crclr before the call) */
#include "stdio.h"
#endif

#ifdef __MWERKS__
/* retail inlines fn_1_1645C (88 insns) and fn_1_16AB0 but not fn_1_165BC / fn_1_1682C (156/161):
 * the default limit inlines those too; any limit from 150 to 200 reproduces the reference */
#pragma inline_max_size(200)
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_370 = 0.0f; /* 0x370 */
static const float lbl_1_rodata_374 = 61.0f; /* 0x374 */
static const float lbl_1_rodata_378 = 240.0f; /* 0x378 */
static const double lbl_1_rodata_380 = 1450.0; /* 0x380 */
static const double lbl_1_rodata_388 = -1.0471975511965976; /* 0x388 */
static const double lbl_1_rodata_390 = 1000.0; /* 0x390 */
static const float lbl_1_rodata_398 = 90.0f; /* 0x398 */
static const double lbl_1_rodata_3A0 = 170.0; /* 0x3A0 */
static const double lbl_1_rodata_3A8 = 0.5235987755982988; /* 0x3A8 */
static const float lbl_1_rodata_3B0 = -50.0f; /* 0x3B0 */
static const float lbl_1_rodata_3B4 = 1.1f; /* 0x3B4 */
static const double lbl_1_rodata_3B8 = 90.0; /* 0x3B8 */
static const double lbl_1_rodata_3C0 = 500.0; /* 0x3C0 */
static const double lbl_1_rodata_3C8 = 1.0; /* 0x3C8 */
static const double lbl_1_rodata_3D0 = 3.141592653589793; /* 0x3D0 */
static const double lbl_1_rodata_3D8 = 20.0; /* 0x3D8 */
static const double lbl_1_rodata_3E0 = 180.0; /* 0x3E0 */
static const float lbl_1_rodata_3E8 = 195.0f; /* 0x3E8 */
static const float lbl_1_rodata_3EC = -1155.0f; /* 0x3EC */
static const float lbl_1_rodata_3F0 = 1.8f; /* 0x3F0 */
static const double lbl_1_rodata_3F8 = 30.0; /* 0x3F8 */
static const float lbl_1_rodata_400 = 1.0f; /* 0x400 */
static const double lbl_1_rodata_408 = 600.0; /* 0x408 */
static const float lbl_1_rodata_410 = 601.0f; /* 0x410 */
static const float lbl_1_rodata_414 = 640.0f; /* 0x414 */
/* 0x418 lbl_1_rodata_418 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_420 = 156.0f; /* 0x420 */
static const float lbl_1_rodata_424 = 344.0f; /* 0x424 */
static const float lbl_1_rodata_428 = 288.0f; /* 0x428 */
static const float lbl_1_rodata_42C = -1000.0f; /* 0x42C */
static const float lbl_1_rodata_430 = 5.0f; /* 0x430 */
static const float lbl_1_rodata_434 = 20.0f; /* 0x434 */
static const float lbl_1_rodata_438 = 15000.0f; /* 0x438 */
static const float lbl_1_rodata_43C = 1.2f; /* 0x43C */
static const float lbl_1_rodata_440 = -3.5555496f; /* 0x440 */
static const float lbl_1_rodata_444 = 72.0f; /* 0x444 */
static const float lbl_1_rodata_448 = 256.0f; /* 0x448 */
static const float lbl_1_rodata_44C = 192.0f; /* 0x44C */
static const float lbl_1_rodata_450 = 32.0f; /* 0x450 */
static const float lbl_1_rodata_454 = 200.0f; /* 0x454 */
static const float lbl_1_rodata_458 = 544.0f; /* 0x458 */
static const double lbl_1_rodata_460 = 10.0; /* 0x460 */
static const float lbl_1_rodata_468 = -10000.0f; /* 0x468 */
static const float lbl_1_rodata_46C = 280.0f; /* 0x46C */
static const float lbl_1_rodata_470 = 70.0f; /* 0x470 */
static const float lbl_1_rodata_474 = 275.0f; /* 0x474 */
static const float lbl_1_rodata_478 = 446.0f; /* 0x478 */
static const float lbl_1_rodata_47C = -24.444437f; /* 0x47C */
static const float lbl_1_rodata_480 = 34.0f; /* 0x480 */
static const float lbl_1_rodata_484 = 400.0f; /* 0x484 */
static const float lbl_1_rodata_488 = 300.0f; /* 0x488 */
static const float lbl_1_rodata_48C = 45.0f; /* 0x48C */
static const float lbl_1_rodata_490 = 0.8f; /* 0x490 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x978 */ s16 lbl_1_bss_978[20];
/* 0x940 */ u8 lbl_1_bss_940[0x38]; /* unreferenced (alignment 4) */
/* 0x8E8 */ HU3DCAMERA lbl_1_bss_8E8; /* struct copy of Hu3DCamera[3] */
/* 0x79C */ union { GWSDCOMMON sd; u8 size[332]; } lbl_1_bss_79C; /* SLSdLoad target: GWSDCOMMON (0x14A) in a 0x14C object, as dtk sizes it */
/* 0x770 */ SDMACHINEMDL lbl_1_bss_770;
/* 0x76E gap_05_0000076E_bss (0x2): alignment gap */
/* 0x76C */ s16 lbl_1_bss_76C;
/* 0x76A */ s16 lbl_1_bss_76A;
/* 0x768 */ s16 lbl_1_bss_768;
/* 0x762 */ char lbl_1_bss_762[0x6]; /* sprintf buffer -> HuWinInsertMesSet/HuWinMesSet */
/* 0x760 */ s16 lbl_1_bss_760;
/* 0x75E */ s16 lbl_1_bss_75E;
/* 0x754 */ s16 lbl_1_bss_754[5];
/* 0x750 */ s32 lbl_1_bss_750;

/* --- functions (reference order), .data placed before its first user --- */
/* 123 insns */
void fn_1_13B1C(void)
{
    GWSDMACHINE *src;
    float posZ;
    if(GwSdBackupNo == -1) {
        lbl_1_bss_770.bodyMdl = HU3D_MODELID_NONE;
        Hu3DMotionTimeSet(lbl_1_bss_58C[2], 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_58C[2], 0x40000002);
    } else {
        Hu3DMotionTimeSet(lbl_1_bss_58C[2], 61.0f);
        Hu3DModelAttrReset(lbl_1_bss_58C[2], 0x40000002);
        Hu3DModelAttrSet(lbl_1_bss_58C[2], 0x40000001);
        Hu3DMotionStartEndSet(lbl_1_bss_58C[2], 61.0f, 240.0f);
        src = &GwSdBackup[GwSdBackupNo].machine;
        fn_1_44E4(&lbl_1_bss_770, src->partNo[0], src->partNo[1], src->partNo[3], 0x40);
        fn_1_4638(&lbl_1_bss_770, 4);
        posZ = 1450.0*-cos(-60.0*M_PI/180.0);
        fn_1_4534(&lbl_1_bss_770, 1450.0*-sin(-60.0*M_PI/180.0), 0.0f, posZ);
        fn_1_4590(&lbl_1_bss_770, 0.0f, 0.0f, 0.0f);
    }
}

/* 0x1518 */ OMCAMERAVIEW lbl_1_data_1518 = { { 433.0f, 200.0f, -250.0f }, { 0.0f, 300.0f, 0.0f }, 50.0f };

/* 689 insns */
void fn_1_13D08(void)
{
    HuVecF pos;
    HUWIN *win;
    u32 mesId;
    s16 i;
    s16 choice;
    BOOL cancelF;
    float scale;

    cancelF = FALSE;
    fn_1_147CC();
    win = &winData[lbl_1_bss_75E];
    win->padMask = 4;
    pos.x = 1000.0*-sin(-60.0*M_PI/180.0);
    pos.y = 90.0f;
    pos.z = 1000.0*-cos(-60.0*M_PI/180.0);
    pos.x += 170.0*-sin(30.0*M_PI/180.0);
    pos.z += 170.0*-cos(30.0*M_PI/180.0);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, -50.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.1f, 1.1f, 1.1f);
    if(lbl_1_bss_770.bodyMdl == HU3D_MODELID_NONE) {
        HuAudFXPlay(0x509);
        Hu3DMotionTimeSet(lbl_1_bss_58C[2], 0.0f);
        Hu3DModelAttrReset(lbl_1_bss_58C[2], 0x40000002);
        Hu3DModelAttrSet(lbl_1_bss_58C[2], 0x40000001);
        HuPrcSleep(60);
        Hu3DMotionStartEndSet(lbl_1_bss_58C[2], 61.0f, 240.0f);
    }
    omCameraViewMoveMulti(HU3D_CAM2, &lbl_1_data_1518, 60, 0);
    HuPrcSleep(60);
    for(i=1; i<=20; i++) {
        pos.y = 90.0+(500.0*(1.0-sin(M_PI*(90.0*(i/20.0))/180.0)));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    HuWinExOpen(lbl_1_bss_75E);
    HuWinMesSet(lbl_1_bss_75E, 0x19000B);
    HuAudFXPlay(0x2EF);
    HuWinMesWait(lbl_1_bss_75E);
    choice = -1;
    if(lbl_1_bss_770.bodyMdl == HU3D_MODELID_NONE) {
        HuWinMesSet(lbl_1_bss_75E, 0x190019);
        HuWinMesWait(lbl_1_bss_75E);
        choice = HuWinChoiceGet(lbl_1_bss_75E, -1);
        if(choice != 0) {
            goto end;
        }
    } else {
        HuWinMesSet(lbl_1_bss_75E, 0x19004F);
        HuWinMesWait(lbl_1_bss_75E);
        choice = HuWinChoiceGet(lbl_1_bss_75E, -1);
        if(choice != 0) {
            goto end;
        }
    }
    if(choice == 0) {
        retry:
        HuWinMesSet(lbl_1_bss_75E, 0x190059);
        HuWinMesWait(lbl_1_bss_75E);
        choice = HuWinChoiceGet(lbl_1_bss_75E, -1);
        if(choice != 0) {
            lbl_1_bss_750 = FALSE;
        } else {
            lbl_1_bss_750 = TRUE;
            HuWinMesSet(lbl_1_bss_75E, 0x19005A);
            HuWinMesWait(lbl_1_bss_75E);
            while(!(fn_1_4FD0(4) & PAD_BUTTON_A)) {
                if(fn_1_4FD0(4) & PAD_BUTTON_B) {
                    HuAudFXPlay(3);
                    cancelF = TRUE;
                    goto end;
                }
                HuPrcVSleep();
            }
            HuAudFXPlay(1);
            choice = HuCardCheck() & 2;
            if(choice == 2) {
                HuWinInsertMesSet(lbl_1_bss_75E, 0x190068, 0);
            } else {
                HuWinMesSet(lbl_1_bss_75E, 0x19007B);
                HuWinMesWait(lbl_1_bss_75E);
                goto retry;
            }
            HuWinMesSet(lbl_1_bss_75E, 0x19004E);
            HuWinMesWait(lbl_1_bss_75E);
            HuPrcSleep(60);
        }
        choice = fn_1_14B04();
        if(choice == -2) {
            HuWinMesSet(lbl_1_bss_75E, 0x19007A);
            HuWinMesWait(lbl_1_bss_75E);
            goto retry;
        }
        if(choice == -1) {
            goto end;
        }
        if(lbl_1_bss_76C == 0) {
            mesId = 0x190050;
            if(choice == 3) {
                HuWinInsertMesSet(lbl_1_bss_75E, 0x190069, 0);
            } else if(choice & 1) {
                mesId = 0x19007D;
            } else if(choice & 2) {
                HuWinInsertMesSet(lbl_1_bss_75E, 0x190068, 0);
            }
            HuWinMesSet(lbl_1_bss_75E, mesId);
            HuWinMesWait(lbl_1_bss_75E);
            cancelF = TRUE;
            goto end;
        }
        if(lbl_1_bss_76A == 0 && (choice & 1)) {
            HuWinMesSet(lbl_1_bss_75E, 0x19007D);
            HuWinMesWait(lbl_1_bss_75E);
        } else if(lbl_1_bss_768 == 0 && (choice & 2)) {
            HuWinInsertMesSet(lbl_1_bss_75E, 0x190068, 0);
            HuWinMesSet(lbl_1_bss_75E, 0x190050);
            HuWinMesWait(lbl_1_bss_75E);
        }
    }
    fn_1_15060();
    end:
    HuWinExClose(lbl_1_bss_75E);
    for(i=1; i<=20; i++) {
        pos.y = 90.0+(500.0*(1.0-cos(M_PI*(90.0*(i/20.0))/180.0)));
        Hu3DModelPosSetV(lbl_1_bss_58A, &pos);
        HuPrcVSleep();
    }
    Hu3DModelPosSet(lbl_1_bss_58A, 0.0f, 195.0f, -1155.0f);
    Hu3DModelRotSet(lbl_1_bss_58A, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(lbl_1_bss_58A, 1.8f, 1.8f, 1.8f);
    if(lbl_1_bss_770.bodyMdl == HU3D_MODELID_NONE || cancelF) {
        if(cancelF && lbl_1_bss_770.bodyMdl != HU3D_MODELID_NONE) {
            HuAudFXPlay(0x50D);
            for(i=1; i<=30; i++) {
                scale = cos(M_PI*(90.0*(i/30.0))/180.0);
                Hu3DModelScaleSet(lbl_1_bss_770.bodyMdl, scale, 1.0f, scale);
                Hu3DModelRotSet(lbl_1_bss_770.bodyMdl, 0.0f, 600.0*(1.0-scale), 0.0f);
                HuPrcVSleep();
            }
            fn_1_4724(&lbl_1_bss_770);
            lbl_1_bss_770.bodyMdl = HU3D_MODELID_NONE;
            cancelF = FALSE;
            GwSdBackupNo = -1;
        }
        HuAudFXPlay(0x509);
        Hu3DMotionTimeSet(lbl_1_bss_58C[2], 601.0f);
        Hu3DModelAttrReset(lbl_1_bss_58C[2], 0x40000001);
        Hu3DMotionStartEndSet(lbl_1_bss_58C[2], 0.0f, 640.0f);
    }
    fn_1_14A60();
}

/* 0x1534 */ OMCAMERAVIEW lbl_1_data_1534 = { { 0.0f, 70.0f, 0.0f }, { -30.0f, 0.0f, 0.0f }, 5300.0f };

/* 165 insns */
void fn_1_147CC(void)
{
    HUSPRGRPID grpId;
    HUSPRID sprId;
    Hu3DModelAttrSet(lbl_1_bss_58C[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
    fn_1_7320();
    lbl_1_bss_75E = HuWinExCreateFrame(156, 344, 400, 94, HUWIN_SPEAKER_NONE, 1);
    HuWinMesPalSet(lbl_1_bss_75E, 7, 0, 0, 0);
    HuWinMesSpeedSet(lbl_1_bss_75E, 0);
    HuWinPriSet(lbl_1_bss_75E, 50);
    grpId = HuSprGrpCreate(2);
    lbl_1_bss_978[0] = grpId;
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x32), HU_MEMNUM_OVL, HEAP_MODEL)), 20, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 288, -1000);
    sprId = HuSprCreate(HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_sdroom, 0x33), HU_MEMNUM_OVL, HEAP_MODEL)), 20, 0);
    HuSprGrpMemberSet(grpId, 1, sprId);
    HuSprPosSet(grpId, 1, 288, -1000);
    Hu3DCameraPerspectiveSet(HU3D_CAM3, 5, 20, 15000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM3, -3.5555496f, 72, 256, 192, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM3, 22, 76, 204, 184);
    omCameraViewSetMulti(HU3D_CAM3, &lbl_1_data_1534);
}

/* 41 insns */
void fn_1_14A60(void)
{
    Hu3DModelAttrReset(lbl_1_bss_58C[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[3], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_58C[6], HU3D_ATTR_DISPOFF);
    fn_1_7298();
    HuWinKill(lbl_1_bss_75E);
    HuSprGrpKill(lbl_1_bss_978[0]);
}

/* 0x1550 */ OMCAMERAVIEW lbl_1_data_1550 = { { 0.0f, 80.0f, 0.0f }, { -30.0f, 0.0f, 0.0f }, 6500.0f };

/* 343 insns */
s16 fn_1_14B04(void)
{
    u64 serialNo;
    s16 boxNo;
    s16 i;
    s16 result = 0;
    lbl_1_bss_76C = lbl_1_bss_76A = lbl_1_bss_768 = 0;
    if(SLSaveFlagGet()) {
        for(boxNo=0; boxNo<3; boxNo++) {
            if(boxNo == SLCurBoxNoGet()) {
                continue;
            }
            if(strncmp((char *)&saveBuf[0][SLBoxDataOffsetGet(boxNo)], "SAVE", 4) != 0) {
                continue;
            }
            SLSdLoad(0, boxNo, &lbl_1_bss_79C.sd);
            for(i=0; i<2; i++) {
                if(lbl_1_bss_79C.sd.machine[i].charNo != -1) {
                    GwSdBackup[lbl_1_bss_76C].machine = lbl_1_bss_79C.sd.machine[i];
                    GwSdBackup[lbl_1_bss_76C].slotNo = 0;
                    GwSdBackup[lbl_1_bss_76C].boxNo = boxNo;
                    lbl_1_bss_76A++;
                    lbl_1_bss_76C++;
                }
            }
        }
        result = 1;
    } else {
        return 0;
    }
    lbl_1_bss_760 = 1;
    if(lbl_1_bss_750 && fn_1_165BC(1) == CARD_RESULT_READY) {
        CARDGetSerialNo(1, &serialNo);
        if(SLSerialNo[0] == serialNo) {
            return -2;
        }
        if(fn_1_16B58(1)) {
            for(boxNo=0; boxNo<3; boxNo++) {
                if(strncmp((char *)&saveBuf[1][SLBoxDataOffsetGet(boxNo)], "SAVE", 4) != 0) {
                    continue;
                }
                SLSdLoad(1, boxNo, &lbl_1_bss_79C.sd);
                for(i=0; i<2; i++) {
                    if(lbl_1_bss_79C.sd.machine[i].charNo != -1) {
                        GwSdBackup[lbl_1_bss_76C].machine = lbl_1_bss_79C.sd.machine[i];
                        GwSdBackup[lbl_1_bss_76C].slotNo = 1;
                        GwSdBackup[lbl_1_bss_76C].boxNo = boxNo;
                        GwSdBackup[lbl_1_bss_76C].garageNo = i;
                        lbl_1_bss_768++;
                        lbl_1_bss_76C++;
                    }
                }
            }
        }
        result |= 2;
    } else {
        HuCardUnMount(1);
    }
    OSReport("==>%d\n", lbl_1_bss_76C);
    return result;
}

/* 544 insns */
void fn_1_15060(void)
{
    SDMACHINEMDL machine;
    GWSDMACHINE *src;
    s16 no;
    s16 i;
    s16 dir;
    float t;
    float posZ;
    fn_1_4D0C(13);
    fn_1_480C(&machine);
    no = 0;
    fn_1_158E0();
    fn_1_15BD0(&GwSdBackup[no].machine, &machine);
    fn_1_15F58(no+1);
    HuWinMesSet(lbl_1_bss_75E, 0x19005D);
    HuWinMesWait(lbl_1_bss_75E);
    HuSprPosSet(lbl_1_bss_978[0], 0, 32, 200);
    HuSprPosSet(lbl_1_bss_978[0], 1, 544, 200);
    HuSprTPLvlSet(lbl_1_bss_978[0], 0, 0);
    HuSprTPLvlSet(lbl_1_bss_978[0], 1, 0);
    for(i=1; i<=10; i++) {
        t = i/10.0;
        if(no != 0) {
            HuSprTPLvlSet(lbl_1_bss_978[0], 0, t);
        }
        if(no < lbl_1_bss_76C-1) {
            HuSprTPLvlSet(lbl_1_bss_978[0], 1, t);
        }
        HuPrcVSleep();
    }
    while(!(fn_1_4FD0(4) & PAD_BUTTON_A)) {
        if(fn_1_4FD0(4) & PAD_BUTTON_B) {
            HuAudFXPlay(3);
            goto close;
        }
        dir = 0;
        if((fn_1_507C(4) & PAD_BUTTON_LEFT) && no != 0) {
            dir = -1;
        } else if((fn_1_507C(4) & PAD_BUTTON_RIGHT) && no < lbl_1_bss_76C-1) {
            dir = 1;
        }
        if(dir != 0) {
            if(no+dir == 0 || no == 0 || lbl_1_bss_76C-1 == no+dir || no == lbl_1_bss_76C-1) {
                HuAudFXPlay(0);
                for(i=1; i<=10; i++) {
                    t = i/10.0;
                    if(no+dir == 0) {
                        HuSprTPLvlSet(lbl_1_bss_978[0], 0, 1.0-t);
                    }
                    if(no == 0) {
                        HuSprTPLvlSet(lbl_1_bss_978[0], 0, t);
                    }
                    if(lbl_1_bss_76C-1 == no+dir) {
                        HuSprTPLvlSet(lbl_1_bss_978[0], 1, 1.0-t);
                    }
                    if(no == lbl_1_bss_76C-1) {
                        HuSprTPLvlSet(lbl_1_bss_978[0], 1, t);
                    }
                    HuPrcVSleep();
                }
            }
            no += dir;
            fn_1_15BD0(&GwSdBackup[no].machine, &machine);
            fn_1_15F58(no+1);
        }
        HuPrcVSleep();
    }
    HuAudFXPlay(1);
    GwSdBackupNo = no;
    if(lbl_1_bss_770.bodyMdl != HU3D_MODELID_NONE) {
        HuAudFXPlay(0x50D);
        for(i=1; i<=30; i++) {
            t = cos(M_PI*(90.0*(i/30.0))/180.0);
            Hu3DModelScaleSet(lbl_1_bss_770.bodyMdl, t, 1.0f, t);
            Hu3DModelRotSet(lbl_1_bss_770.bodyMdl, 0.0f, 600.0*(1.0-t), 0.0f);
            HuPrcVSleep();
        }
        fn_1_4724(&lbl_1_bss_770);
    }
    src = &GwSdBackup[no].machine;
    fn_1_44E4(&lbl_1_bss_770, src->partNo[0], src->partNo[1], src->partNo[3], 0x40);
    fn_1_4638(&lbl_1_bss_770, 4);
    posZ = 1450.0*-cos(-60.0*M_PI/180.0);
    fn_1_4534(&lbl_1_bss_770, 1450.0*-sin(-60.0*M_PI/180.0), 0.0f, posZ);
    fn_1_4590(&lbl_1_bss_770, 0.0f, 0.0f, 0.0f);
    HuAudFXPlay(0x50A);
    for(i=1; i<=30; i++) {
        t = sin(M_PI*(90.0*(i/30.0))/180.0);
        Hu3DModelScaleSet(lbl_1_bss_770.bodyMdl, t, 1.0f, t);
        Hu3DModelRotSet(lbl_1_bss_770.bodyMdl, 0.0f, 600.0*(1.0-t), 0.0f);
        HuPrcVSleep();
    }
    close:
    for(i=1; i<=10; i++) {
        t = 1.0-(i/10.0);
        if(no != 0) {
            HuSprTPLvlSet(lbl_1_bss_978[0], 0, t);
        }
        if(no < lbl_1_bss_76C-1) {
            HuSprTPLvlSet(lbl_1_bss_978[0], 1, t);
        }
        HuPrcVSleep();
    }
    fn_1_15E00(&machine);
    fn_1_4E14();
}

/* 188 insns */
void fn_1_158E0(void)
{
    HUWINID winId;
    winId = HuWinExCreateFrame(32, 32, 512, 276, HUWIN_SPEAKER_NONE, 0);
    lbl_1_bss_754[0] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 50);
    HuWinDrawNoSet(winId, 64);
    HuWinExOpen(winId);
    winId = HuWinCreate(-10000, 32, 544, 26, 0);
    lbl_1_bss_754[1] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinAttrSet(winId, 0x800);
    HuWinBGTPLvlSet(winId, 0);
    winId = HuWinCreate(280, 70, 280, 172, 0);
    lbl_1_bss_754[2] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinBGTPLvlSet(winId, 0);
    winId = HuWinCreate(-10000, 275, 544, 26, 0);
    lbl_1_bss_754[3] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinAttrSet(winId, 0x800);
    HuWinBGTPLvlSet(winId, 0);
    HuWinMesSet(winId, 0x20004);
    winId = HuWinCreate(446, 32, 120, 26, 0);
    lbl_1_bss_754[4] = winId;
    HuWinMesSpeedSet(winId, 0);
    HuWinPriSet(winId, 40);
    HuWinBGTPLvlSet(winId, 0);
    lbl_1_bss_8E8 = Hu3DCamera[3];
    omCameraViewSetMulti(HU3D_CAM3, &lbl_1_data_1550);
    Hu3DCameraViewportSet(HU3D_CAM3, -24.444437f, 34, 400, 300, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM3, 37, 34, 311, 282);
}

/* 140 insns */
void fn_1_15BD0(GWSDMACHINE *src, SDMACHINEMDL *machine)
{
    s16 i;
    float scale;
    HUWINID winId;
    HuWinMesSet(lbl_1_bss_754[1], (u32)src->name);
    if(machine->partNo[0] != -1) {
        for(i=1; i<=10; i++) {
            scale = 1.0-(i/10.0);
            fn_1_45E4(machine, scale, scale, scale);
            HuPrcVSleep();
        }
        fn_1_4724(machine);
    }
    winId = lbl_1_bss_754[2];
    HuWinInsertMesSet(winId, src->partNo[0]+0x1A0017, 0);
    HuWinInsertMesSet(winId, src->partNo[1]+0x1A0001, 1);
    HuWinInsertMesSet(winId, src->partNo[2]+0x1A000C, 2);
    HuWinInsertMesSet(winId, src->partNo[3]+0x1A0022, 3);
    HuWinMesSet(winId, 0x450008);
    fn_1_44E4(machine, src->partNo[0], src->partNo[1], src->partNo[3], 0x40);
    fn_1_4638(machine, 8);
    fn_1_4590(machine, 0.0f, 45.0f, 0.0f);
    for(i=1; i<=10; i++) {
        scale = i/10.0;
        fn_1_45E4(machine, scale, scale, scale);
        HuPrcVSleep();
    }
}

/* 86 insns */
void fn_1_15E00(SDMACHINEMDL *machine)
{
    s16 i;
    float scale;
    for(i=1; i<=10; i++) {
        scale = 1.0-(i/10.0);
        fn_1_45E4(machine, scale, scale, scale);
        HuPrcVSleep();
    }
    fn_1_4724(machine);
    HuWinKill(lbl_1_bss_754[1]);
    HuWinKill(lbl_1_bss_754[2]);
    HuWinKill(lbl_1_bss_754[3]);
    HuWinKill(lbl_1_bss_754[4]);
    Hu3DCamera[3] = lbl_1_bss_8E8;
    HuWinExClose(lbl_1_bss_754[0]);
    HuWinKill(lbl_1_bss_754[0]);
}

/* 51 insns */
void fn_1_15F58(s16 a0)
{
    HUWINID winId = lbl_1_bss_754[4];
    sprintf(lbl_1_bss_762, "%02d", a0);
    sprintf(lbl_1_bss_762+3, "%02d", lbl_1_bss_76C);
    HuWinInsertMesSet(winId, (u32)lbl_1_bss_762, 0);
    HuWinInsertMesSet(winId, (u32)(lbl_1_bss_762+3), 1);
    HuWinMesSet(winId, 0x19002C);
    HuWinScaleSet(winId, 0.8f, 0.8f);
}

/* 16 insns */
void fn_1_16024(void)
{
    if(lbl_1_bss_770.bodyMdl != HU3D_MODELID_NONE) {
        fn_1_46C4(&lbl_1_bss_770, TRUE);
    }
}

/* 16 insns */
void fn_1_16064(void)
{
    if(lbl_1_bss_770.bodyMdl != HU3D_MODELID_NONE) {
        fn_1_46C4(&lbl_1_bss_770, FALSE);
    }
}
/* 238 insns */
s16 fn_1_160A4(s16 messId)
{
    u32 mesId;
    s16 choice = -1;
    u32 insertMes = 0;
    BOOL choiceF = FALSE;
    HUWINID winId = lbl_1_bss_75E;
    switch(messId) {
        case 0:
            mesId = 0x19007B;
            break;
        case 1:
            mesId = 0x190052;
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            break;
        case 2:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = MESS_MPSYSTEM_CARD_INSSPACE;
            break;
        case 3:
            mesId = MESS_MPSYSTEM_CARD_INSSPACE;
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            break;
        case 4:
            mesId = MESS_MPSYSTEM_CARD_FULL;
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            break;
        case 5:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = 0x190053;
            choiceF = TRUE;
            break;
        case 6:
            mesId = 0x190054;
            break;
        case 7:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = MESS_MPSYSTEM_CARD_WRONGDEVICE;
            break;
        case 8:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = MESS_MPSYSTEM_CARD_INVALID;
            break;
        case 9:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = MESS_MPSYSTEM_CARD_SERIAL_INVALID;
            break;
        case 10:
            mesId = MESS_MPSYSTEM_NOSAVE_CHOICE;
            choiceF = TRUE;
            break;
        case 11:
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            mesId = 0x3001F;
            break;
        case 12:
            mesId = MESS_MPSYSTEM_CARD_FORMAT_UNMOUNT;
            HuWinInsertMesSizeGet(0x190067+lbl_1_bss_760, 0);
            insertMes = 0x190067+lbl_1_bss_760;
            break;
    }
    if(insertMes) {
        HuWinInsertMesSet(winId, insertMes, 0);
    }
    HuWinAttrSet(winId, HUWIN_ATTR_NOCANCEL);
    HuWinMesSet(winId, mesId);
    HuWinMesWait(winId);
    if(choiceF) {
        if(messId == 5) {
            HuWinInsertMesSet(winId, 0x190067+lbl_1_bss_760, 0);
            HuWinMesSet(winId, 0x190055);
            HuWinMesWait(winId);
        }
        choice = HuWinChoiceGet(winId, -1);
    }
    if(messId == 11) {
        while(!(fn_1_4FD0(4) & PAD_BUTTON_A)) {
            HuPrcVSleep();
        }
        HuAudFXPlay(MSM_SE_CMN_02);
    }
    return choice;
}

/* 88 insns */
s32 fn_1_1645C(s16 slotNo)
{
    s16 result;
    HuWinInsertMesSet(lbl_1_bss_75E, 0x190067+slotNo, 0);
    HuWinMesSet(lbl_1_bss_75E, 0x190076);
    HuPrcSleep(30);
    if(UnMountCnt & (1 << slotNo)) {
        fn_1_160A4(12);
        UnMountCnt = 0;
        return CARD_RESULT_READY;
    }
    result = HuCardFormat(slotNo);
    SLSerialNo[slotNo] = 0;
    if(result == CARD_RESULT_FATAL_ERROR) {
        fn_1_160A4(6);
        fn_1_160A4(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
        return CARD_RESULT_NOCARD;
    }
    if(result == CARD_RESULT_WRONGDEVICE) {
        fn_1_160A4(7);
        return result;
    }
    CARDGetSerialNo(slotNo, &SLSerialNo[slotNo]);
    return result;
}

/* 156 insns */
s32 fn_1_165BC(s16 slotNo)
{
    s32 result = HuCardMount(slotNo);
    if(result == CARD_RESULT_WRONGDEVICE) {
        fn_1_160A4(7);
        return result;
    }
    if(result == CARD_RESULT_FATAL_ERROR) {
        fn_1_160A4(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
        return CARD_RESULT_NOCARD;
    }
    if(result == CARD_RESULT_BROKEN) {
        result = HuCardSectorSizeGet(slotNo);
        if(result > 0 && result != SAVE_SECTOR_SIZE) {
            fn_1_160A4(8);
            return CARD_RESULT_WRONGDEVICE;
        }
        UnMountCnt = 0;
        result = fn_1_160A4(5);
        if(result == 0) {
            result = fn_1_1645C(slotNo);
            return result;
        }
        return CARD_RESULT_FATAL_ERROR;
    }
    result = HuCardSectorSizeGet(slotNo);
    if(result < 0) {
        fn_1_160A4(1);
        return result;
    }
    if(result != SAVE_SECTOR_SIZE) {
        fn_1_160A4(8);
        return CARD_RESULT_WRONGDEVICE;
    }
    return CARD_RESULT_READY;
}

/* 161 insns */
s32 fn_1_1682C(u8 slotNo)
{
    s32 result = fn_1_165BC(slotNo);
    if(result < 0) {
        return result;
    }
    result = HuCardOpen(slotNo, SLSaveFileName, &curFileInfo);
    if(result == CARD_RESULT_NOFILE) {
        return CARD_RESULT_NOFILE;
    }
    if(result == CARD_RESULT_WRONGDEVICE) {
        fn_1_160A4(7);
        return CARD_RESULT_FATAL_ERROR;
    }
    if(result == CARD_RESULT_FATAL_ERROR) {
        fn_1_160A4(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
        return CARD_RESULT_NOCARD;
    }
    if(result == CARD_RESULT_BROKEN) {
        result = HuCardSectorSizeGet(slotNo);
        if(result > 0 && result != SAVE_SECTOR_SIZE) {
            fn_1_160A4(8);
            return CARD_RESULT_WRONGDEVICE;
        }
        UnMountCnt = 0;
        result = fn_1_160A4(5);
        if(result == 0) {
            result = fn_1_1645C(slotNo);
            return result;
        }
        return CARD_RESULT_NOFILE;
    }
    return CARD_RESULT_READY;
}

/* 28 insns */
s32 fn_1_16AB0(s32 length, void *addr)
{
    s32 result = HuCardRead(&curFileInfo, addr, length, 0);
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
    } else if(result < 0) {
        fn_1_160A4(1);
    }
    return result;
}

/* 14 insns */
s32 fn_1_16B20(void)
{
    s32 result = HuCardClose(&curFileInfo);
    return result;
}

/* 411 insns */
s32 fn_1_16B58(u8 slotNo)
{
    s32 boxStat[3];
    OSTime time;
    char numStr[8];
    s32 prevSlotNo;
    u16 *checkSum;
    BOOL iconBrokenF;
    s32 result;
    s32 winId;
    s32 i;
    result = fn_1_1682C(slotNo);
    if(result < 0) {
        goto fail;
    }
    CARDGetSerialNo(slotNo, &SLSerialNo[slotNo]);
    result = fn_1_16AB0(SAVE_BUF_SIZE, &saveBuf[slotNo][0]);
    SLFileClose();
    if(result < 0) {
        goto fail;
    }
    winId = lbl_1_bss_75E;
    if(strncmp((char *)&saveBuf[curSlotNo][0], "ERASE", 5) == 0) {
        time = OSGetTime();
        SLSaveDataMake(TRUE, &time);
        for(i=0; i<3; i++) {
            SLSaveEmptyMark(slotNo, i);
        }
        goto success;
    }
    checkSum = (u16 *)&saveBuf[slotNo][SAVE_ICONBANNER_CHECKSUM_OFS];
    iconBrokenF = FALSE;
    for(i=0; i<3; i++) {
        boxStat[i] = 0;
    }
    if(*checkSum != SLCheckSumSlotGet(slotNo, 0, SAVE_ICONBANNER_CHECKSUM_OFS)) {
        OSReport("IconBanner Area Broken!\n");
        time = OSGetTime();
        SLSaveDataSlotMake(slotNo, FALSE, &time);
        iconBrokenF = TRUE;
    }
    for(i=0; i<3; i++) {
        if(strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i)], "SAVE", 4) == 0 || strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i+3)], "SAVE", 4) == 0) {
            if(!SLCheckSumBoxSlotCheck(slotNo, i)) {
                OSReport("Box%d Broken!\n", i);
                SLBoxBackupSlotLoad(slotNo, i);
                if(!SLCheckSumBoxSlotCheck(slotNo, i)) {
                    SLSaveEmptyMark(slotNo, i);
                    boxStat[i] = 2;
                } else {
                    boxStat[i] = 1;
                }
            }
        } else if(strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i)], "EMPT", 4) != 0 && strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i+3)], "EMPT", 4) != 0) {
            boxStat[i] = 3;
            SLSaveEmptyMark(slotNo, i);
        } else if(strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i)], "EMPT", 4) == 0 || strncmp((char *)&saveBuf[slotNo][SLBoxDataOffsetGet(i+3)], "EMPT", 4) == 0) {
            SLSaveEmptyMark(slotNo, i);
        }
    }
    if(iconBrokenF || boxStat[0] || boxStat[1] || boxStat[2]) {
        HuWinExOpen(winId);
        if(boxStat[0] != 2 && boxStat[0] != 3 && boxStat[1] != 2 && boxStat[1] != 3 && boxStat[2] != 2 && boxStat[2] != 3) {
            HuWinInsertMesSet(winId, 0x190067+slotNo, 0);
            HuWinMesSet(winId, 0x30034);
            HuWinMesWait(winId);
        } else {
            for(i=0; i<3; i++) {
                sprintf(numStr, "%d", i+1);
                if(boxStat[i] == 1) {
                    HuWinInsertMesSet(winId, (u32)numStr, 0);
                    HuWinInsertMesSet(winId, 0x190067+slotNo, 1);
                    HuWinMesSet(winId, 0x190058);
                    HuWinMesWait(winId);
                } else if(boxStat[i] == 2) {
                    HuWinInsertMesSet(winId, (u32)numStr, 0);
                    HuWinInsertMesSet(winId, 0x190067+slotNo, 1);
                    HuWinMesSet(winId, 0x190057);
                    HuWinMesWait(winId);
                } else if(boxStat[i] == 3) {
                    HuWinInsertMesSet(winId, 0x190067+slotNo, 0);
                    HuWinInsertMesSet(winId, (u32)numStr, 1);
                    HuWinMesSet(winId, 0x190079);
                    HuWinMesWait(winId);
                }
            }
        }
        prevSlotNo = curSlotNo;
        curSlotNo = slotNo;
        result = fn_1_171C4(slotNo);
        curSlotNo = prevSlotNo;
        if(result == FALSE) {
            goto fail;
        }
    }
    success:
    HuCardUnMount(slotNo);
    return TRUE;
    fail:
    HuCardUnMount(slotNo);
    return FALSE;
}

/* 233 insns */
s32 fn_1_171C4(u8 slotNo)
{
    s32 result;
    s32 winId;
    SLCheckSumBoxAllSet();
    SLSaveBackup();
    repeat:
    result = fn_1_1682C(slotNo);
    if(result == CARD_RESULT_NOFILE) {
        if(!fn_1_17900(slotNo)) {
            fn_1_160A4(9);
            goto fail;
        }
        result = fn_1_17568(slotNo);
        if(result < 0) {
            goto fail;
        }
        CARDGetSerialNo(slotNo, &SLSerialNo[slotNo]);
    } else if(result == CARD_RESULT_NOCARD) {
        goto fail;
    } else if(result < 0) {
        goto fail;
    } else {
        if(!fn_1_17900(slotNo)) {
            fn_1_160A4(9);
            goto fail;
        }
        result = fn_1_17800(slotNo);
        if(result == CARD_RESULT_NOCARD) {
            fn_1_160A4(0);
        } else if(result == CARD_RESULT_WRONGDEVICE) {
            fn_1_160A4(7);
        } else if(result == CARD_RESULT_BROKEN) {
            result = HuCardSectorSizeGet(slotNo);
            if(result > 0 && result != SAVE_SECTOR_SIZE) {
                fn_1_160A4(8);
                goto fail;
            } else {
                UnMountCnt = 0;
                result = fn_1_160A4(5);
                if(result == 0) {
                    result = fn_1_1645C(slotNo);
                    if(result == CARD_RESULT_READY) {
                        goto repeat;
                    } else {
                        return FALSE;
                    }
                } else {
                    result = CARD_RESULT_BROKEN;
                }
            }
        } else if(result < 0) {
            fn_1_160A4(1);
        }
    }
    SLFileClose();
    if(result >= 0) {
        HuCardUnMount(slotNo);
        return TRUE;
    }
    fail:
    winId = lbl_1_bss_75E;
    HuWinAttrSet(winId, HUWIN_ATTR_NOCANCEL);
    HuWinInsertMesSet(winId, 0x190067+slotNo, 0);
    HuWinMesSet(winId, 0x190077);
    HuWinMesWait(winId);
    result = HuWinChoiceGet(winId, -1);
    if(result != 0) {
        HuWinInsertMesSet(winId, 0x190067+slotNo, 0);
        HuWinMesSet(winId, 0x19005A);
        HuWinMesWait(winId);
        while(!(HuPadBtnDown[2] & PAD_BUTTON_A)) {
            HuPrcVSleep();
        }
        HuAudFXPlay(MSM_SE_CMN_02);
        goto repeat;
    }
    HuCardUnMount(slotNo);
    return FALSE;
}

/* 166 insns */
s32 fn_1_17568(s16 slotNo)
{
    s32 result;
    u32 byteNotUsed;
    u32 filesNotUsed;
    void *eraseBuf;
    if(!SLSaveFlagGet()) {
        return CARD_RESULT_READY;
    }
    result = fn_1_165BC(slotNo);
    if(result < 0) {
        return result;
    }
    result = HuCardSectorSizeGet(slotNo);
    if(result < 0 && result != SAVE_SECTOR_SIZE) {
        fn_1_160A4(8);
        return CARD_RESULT_FATAL_ERROR;
    }
    result = HuCardFreeSpaceGet(slotNo, &byteNotUsed, &filesNotUsed);
    if(filesNotUsed == 0 && byteNotUsed < SAVE_BUF_SIZE) {
        fn_1_160A4(4);
        return CARD_RESULT_INSSPACE;
    }
    if(filesNotUsed == 0) {
        fn_1_160A4(2);
        return CARD_RESULT_INSSPACE;
    }
    if(byteNotUsed < SAVE_BUF_SIZE) {
        fn_1_160A4(3);
        return CARD_RESULT_INSSPACE;
    }
    HuWinInsertMesSet(lbl_1_bss_75E, 0x190067+slotNo, 0);
    HuWinMesSet(lbl_1_bss_75E, 0x190078);
    HuWinMesWait(lbl_1_bss_75E);
    result = HuCardCreate(slotNo, SLSaveFileName, SAVE_BUF_SIZE, &curFileInfo);
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
        return CARD_RESULT_NOCARD;
    }
    if(result < 0) {
        fn_1_160A4(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    eraseBuf = HuMemDirectMalloc(HEAP_HEAP, SAVE_BUF_SIZE);
    memset(eraseBuf, SAVE_BUF_SIZE, 0); /* retail: value/size swapped, clears nothing */
    memcpy(eraseBuf, SLEraseStr, 6);
    result = HuCardWrite(&curFileInfo, eraseBuf, SAVE_BUF_SIZE, 0);
    if(result == CARD_RESULT_READY) {
        result = HuCardWrite(&curFileInfo, &saveBuf[slotNo][0], SAVE_BUF_SIZE, 0);
    }
    HuMemDirectFree(eraseBuf);
    if(result == CARD_RESULT_NOCARD) {
        fn_1_160A4(0);
        return CARD_RESULT_NOCARD;
    }
    if(result < 0) {
        fn_1_160A4(1);
        return CARD_RESULT_FATAL_ERROR;
    }
    result = SLStatSet(FALSE);
    if(result < 0) {
        return result;
    }
    return CARD_RESULT_READY;
}

/* 64 insns */
s32 fn_1_17800(s16 slotNo)
{
    s32 result;
    if(!SLSaveFlagGet()) {
        return CARD_RESULT_READY;
    }
    HuWinInsertMesSet(lbl_1_bss_75E, 0x190067+slotNo, 0);
    HuWinMesSet(lbl_1_bss_75E, 0x190078);
    HuWinMesWait(lbl_1_bss_75E);
    HuPrcSleep(60);
    CARDGetSerialNo(slotNo, &SLSerialNo[slotNo]);
    result = HuCardWrite(&curFileInfo, &saveBuf[slotNo][0], SAVE_BUF_SIZE, 0);
    if(result == CARD_RESULT_READY) {
        result = SLStatSet(FALSE);
    }
    return result;
}

/* 53 insns */
s32 fn_1_17900(s16 slotNo)
{
    u64 serialNo;
    if(SLSerialNo[slotNo] == 0) {
        return TRUE;
    } else {
        s32 result = CARDGetSerialNo(slotNo, &serialNo);
        if(result < 0) {
            return TRUE;
        }
        if(SLSerialNo[slotNo] != serialNo) {
            return FALSE;
        } else {
            return TRUE;
        }
    }
}
