/*
 * mgtourDll mgtournament.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgtourDll/asm/REL/mgtourDll/mgtournament.s.
 */

#include "REL/mgtourDll.h"

/* Retail calls the audio API unprototyped (implicit int): keep game/audio.h out of the CW build,
 * but keep its msm constants. */
#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#include "msm_grp.h"
#include "msm_se.h"
#include "msm_stream.h"
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* score.c lbl_1_data_920: 0x28 records (field names unknown) */
typedef struct MgTourScoreRec_s {
    s32 num;
    HuVecF vec[3];
} MGTOUR_SCOREREC;

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const double lbl_1_rodata_10 = 180.0; /* 0x10 */
static const double lbl_1_rodata_18 = 360.0; /* 0x18 */
static const float lbl_1_rodata_20 = 180.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 0.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 32.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 200.0f; /* 0x2C */
/* 0x30 lbl_1_rodata_30 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x31 lbl_1_rodata_31 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_34 = 480.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 640.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 10.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 1.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 5.0f; /* 0x44 */
static const double lbl_1_rodata_48 = 0.005; /* 0x48 */
static const double lbl_1_rodata_50 = 1.0; /* 0x50 */
static const float lbl_1_rodata_58 = 6000.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 3.8f; /* 0x5C */
static const float lbl_1_rodata_60 = 2000.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 20.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 60000.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 1.2f; /* 0x6C */
static const float lbl_1_rodata_70 = 28.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 179.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 359.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 1.5f; /* 0x7C */
static const float lbl_1_rodata_80 = 15000.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 40000.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 100.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 30000.0f; /* 0x8C */
/* 0x90 lbl_1_rodata_90 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_98 = 13000.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 25.0f; /* 0x9C */
static const double lbl_1_rodata_A0 = 3.141592653589793; /* 0xA0 */
static const double lbl_1_rodata_A8 = 0.5; /* 0xA8 */
static const float lbl_1_rodata_B0 = 45.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 3.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 29.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 58.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 750.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 150.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 15.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 30.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = -150.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 0.25f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 2.3f; /* 0xD8 */
static const float lbl_1_rodata_DC = 360.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = 350.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = -1.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 0.01f; /* 0xE8 */
static const float lbl_1_rodata_EC = 40.0f; /* 0xEC */
/* 0xF0 lbl_1_rodata_F0 (0xC): 0x00000000 0x45FA0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xFC lbl_1_rodata_FC (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x108 lbl_1_rodata_108 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x114 lbl_1_rodata_114 (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x120 lbl_1_rodata_120 (0xC): 0x00000000 0x42480000 0x457A0000 -- an aggregate initialiser, write it as a local */
/* 0x12C lbl_1_rodata_12C (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_138 = 60.0f; /* 0x138 */
static const float lbl_1_rodata_13C = 1000.0f; /* 0x13C */
static const float lbl_1_rodata_140 = 2.0f; /* 0x140 */
static const float lbl_1_rodata_144 = -10000.0f; /* 0x144 */
static const float lbl_1_rodata_148 = 800.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 300.0f; /* 0x14C */
static const float lbl_1_rodata_150 = -30.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 400.0f; /* 0x154 */
static const float lbl_1_rodata_158 = 430.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 80.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 0.001f; /* 0x160 */
static const double lbl_1_rodata_168 = 25.0; /* 0x168 */
static const float lbl_1_rodata_170 = 4.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 6.5f; /* 0x174 */
static const float lbl_1_rodata_178 = -2.6000001f; /* 0x178 */
static const float lbl_1_rodata_17C = 0.4f; /* 0x17C */
static const float lbl_1_rodata_180 = 14.0f; /* 0x180 */
static const double lbl_1_rodata_188 = 0.001; /* 0x188 */
static const float lbl_1_rodata_190 = 0.017453292f; /* 0x190 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x16820 */ MGTOUR_WORK lbl_1_bss_16820; /* reached through lbl_1_bss_16818 */
/* 0x1681C */ MGTOUR_MODEWORK *lbl_1_bss_1681C; /* = (MGTOUR_MODEWORK *)mgModeWork */
/* 0x16818 */ MGTOUR_WORK *lbl_1_bss_16818; /* = &lbl_1_bss_16820 */
/* 0x16760 */ MGTOUR_CONFETTI lbl_1_bss_16760;
/* 0x0 */ MGTOUR_PAPER lbl_1_bss_0[1000];

/* --- functions (reference order), .data placed before its first user --- */
/* 40 insns */
void fn_1_A0(s8 *a, s8 *b, s8 num)
{
    int i, j;
    for (i = 0; i < num - 1; i++) {
        for (j = i + 1; j < num; j++) {
            if (a[i] > a[j]) {
                s8 temp = a[i];
                a[i] = a[j];
                a[j] = temp;
                if (b) {
                    s8 temp = b[i];
                    b[i] = b[j];
                    b[j] = temp;
                }
            }
        }
    }
}

/* 49 insns */
void fn_1_140(s8 *arr, s32 num)
{
    s8 usednum[256];
    int i, j;
    int no;
    for (i = num; i--;) {
        usednum[i] = arr[i];
    }
    for (i = num; i--;) {
        if (i) {
            no = frandmod(i + 1);
        }
        else {
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

/* 130 insns */
BOOL fn_1_204(float *angle, float end, float speed)
{
    float diff = *angle - end;
    float change = fmodf(diff, 180);
    float wrap = fmodf(diff, 360);
    if (fabsf(wrap) > 180.0f) {
        if (change > 0) {
            change = -(180.0f - fabsf(change));
        }
        else {
            change = 180.0f - fabsf(change);
        }
    }
    if (fabsf(change) < speed) {
        *angle = end;
        return TRUE;
    }
    if (change > 0) {
        change -= speed;
    }
    else {
        change += speed;
    }
    *angle = end + change;
    return FALSE;
}

/* 15 insns */
void fn_1_40C(s32 time)
{
    while (time--) {
        HuPrcVSleep();
    }
}

/* 21 insns */
void fn_1_448(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_IN, type, time);
    WipeWait();
}

/* 21 insns */
void fn_1_49C(s32 type, s32 time)
{
    WipeCreate(WIPE_MODE_OUT, type, time);
    WipeWait();
}

/* 0x0 */ unsigned int lbl_1_data_0[10] = { /* character motion DATANUMs for CharModelMotListCreate (0-terminated) */ 0x8C0000, 0x8C0001, 0x8C0032, 0x8C0031, 0x8C0052, 0x8C0036, 0x870099, 0x8C001A, 0x8C002E, 0x0 };
/* 0x28 */ HuVecF lbl_1_data_28[6] = { { -160.0f, 0.0f, 160.0f }, { 0.0f, 0.0f, 160.0f }, { 160.0f, 0.0f, 160.0f }, { 320.0f, 0.0f, 160.0f }, { -180.0f, 31.0f, 420.0f }, { 167.0f, 31.0f, 420.0f } };
/* 0x70 */ HuVecF lbl_1_data_70 = { 0.0f, -300.0f, -7000.0f };
/* 0x7C */ HuVecF lbl_1_data_7C[5] = { { 0.0f, 100.0f, 0.0f }, { -320.0f, 100.0f, 140.0f }, { -420.0f, 100.0f, 140.0f }, { -380.0f, 100.0f, 140.0f }, { 20.0f, 100.0f, 140.0f } };
/* 0xB8 */ MGTOUR_MG lbl_1_data_B8[15] = { { 55, 541, 0 }, { 56, 542, 0 }, { 57, 543, 0 }, { 58, 544, 0 }, { 59, 545, 0 }, { 60, 546, 0 }, { 61, 547, 0 }, { 62, 548, 0 }, { 65, 551, 0 }, { 66, 552, 0 }, { 63, 549, 0 }, { 64, 550, 0 }, { 67, 553, 0 }, { 68, 554, 0 }, { 69, 555, 0 } };
/* 0x114 */ float lbl_1_data_114[3] = { 0.0f, -100.0f, -2000.0f };
/* 0x120 */ GXColor lbl_1_data_120[4] = { { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 160, 160, 255, 0 }, { 128, 192, 255, 0 } };
/* 0x130 */ HU3DPARMANPARAM lbl_1_data_130 = { 60, 0, 1.0f, 10.0f, 5.0f, { 0.0f, -0.4f, 0.0f }, 15.0f, 1.0f, 70.0f, 0.95f, 2, { { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x180 */ float lbl_1_data_180[13] = { -35.0f, -35.0f, -35.0f, -45.0f, -50.0f, -35.0f, -40.0f, -35.0f, -60.0f, -80.0f, -80.0f, -80.0f, -80.0f };
/* 0x1B4 */ float lbl_1_data_1B4[13] = { 0.0f, 0.0f, 1000.0f, 0.0f, -3000.0f, 1000.0f, 0.0f, 0.0f, -8000.0f, -3000.0f, -3000.0f, -3000.0f, -3000.0f };
/* 0x1E8 */ GXColor lbl_1_data_1E8[4] = { { 128, 128, 128, 255 }, { 64, 64, 64, 255 }, { 0, 0, 0, 0 }, { 64, 64, 64, 128 } };
/* 0x1F8 */ HU3DPARMANPARAM lbl_1_data_1F8 = { 40, 0, 0.3f, 30.0f, 10.0f, { 0.0f, -0.2f, 0.0f }, 2.0f, 1.0f, 40.0f, 0.98f, 2, { { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x248 */ s32 lbl_1_data_248[10][4] = { /* per character: voice SE ids, fn_1_674 [charNo][seNo] */ { 0x1F8, 0x200, 0x1FA, 0x1FF }, { 0x1E4, 0x1EC, 0x1E6, 0x1EB }, { 0x25C, 0x264, 0x25E, 0x263 }, { 0x2AC, 0x2B4, 0x2AE, 0x2B3 }, { 0x284, 0x28C, 0x286, 0x28B }, { 0x1BC, 0x1C4, 0x1BE, 0x1C3 }, { 0x298, 0x2A0, 0x29A, 0x29F }, { 0x1D0, 0x1D8, 0x1D2, 0x1D7 }, { 0x270, 0x278, 0x272, 0x277 }, { 0x234, 0x23C, 0x236, 0x23B } };

/* 55 insns */
void fn_1_4F0(void)
{
    u32 tick;
    int statId;
    lbl_1_bss_16818->dirRead = FALSE;
    tick = OSGetTick();
    statId = HuDataDirReadAsync(mgDataTbl[lbl_1_bss_16818->mgNoDir].dataDir);
    while (!HuDataGetAsyncStat(statId)) {
        HuPrcVSleep();
    }
    lbl_1_bss_16818->dirRead = TRUE;
    OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick() - tick));
    OSReport("Finished!\n");
    HuPrcEnd();
    while (1) {
        HuPrcVSleep();
    }
}

/* 37 insns */
void fn_1_5CC(s32 mgNo)
{
    lbl_1_bss_16818->mgNoDir = mgNo;
    HuDataDirClose(DATA_mgtour);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    if (!fn_1_7E4(4)) {
        HuPrcChildCreate(fn_1_4F0, 200, 12288, 0, HuPrcCurrentGet());
    }
    else {
        lbl_1_bss_16818->dirRead = TRUE;
    }
}

/* 5 insns */
HUWINID fn_1_660(void)
{
    return lbl_1_bss_16818->winId;
}

/* 37 insns */
void fn_1_674(MGTOUR_PLAYER *player, s32 seNo)
{
    int pan = (int)(32 * (player->pos.x / 200)) + 64;
    HuAudFXPlayPan(lbl_1_data_248[player->charNo][seNo], pan);
}

/* 18 insns */
void fn_1_708(void)
{
    if (!fn_1_7E4(0x20)) {
        fn_1_7AC(0x20);
        HuWinExOpen(lbl_1_bss_16818->winId);
    }
}

/* 23 insns */
void fn_1_750(void)
{
    if (fn_1_7E4(0x20)) {
        fn_1_7C8(0x20);
        HuWinExClose(lbl_1_bss_16818->winId);
        HuWinHomeClear(lbl_1_bss_16818->winId);
    }
}

/* 7 insns */
void fn_1_7AC(u32 flag)
{
    lbl_1_bss_16818->flag |= flag;
}

/* 7 insns */
void fn_1_7C8(u32 flag)
{
    lbl_1_bss_16818->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_7E4(u32 flag)
{
    return lbl_1_bss_16818->flag & flag;
}

/* 8 insns */
void fn_1_7FC(u32 flag)
{
    lbl_1_bss_1681C->flag |= flag;
}

/* 8 insns */
void fn_1_81C(u32 flag)
{
    lbl_1_bss_1681C->flag &= ~flag;
}

/* 6 insns */
u32 fn_1_83C(u32 flag)
{
    return lbl_1_bss_1681C->flag & flag;
}

/* 7 insns */
void fn_1_854(u32 flag)
{
    lbl_1_bss_16818->mesFlag |= flag;
}

/* 7 insns */
void fn_1_870(u32 flag)
{
    lbl_1_bss_16818->mesFlag &= ~flag;
}

/* 6 insns */
u32 fn_1_88C(u32 flag)
{
    return lbl_1_bss_16818->mesFlag & flag;
}

/* 24 insns */
u32 fn_1_8A4(void)
{
    return mgDataTbl[lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgIdx].nameMes;
}

/* 13 insns */
s32 fn_1_904(s32 i)
{
    return lbl_1_bss_16818->player[lbl_1_bss_16818->order[i]].charNo;
}

/* 13 insns */
s32 fn_1_938(s32 i)
{
    return lbl_1_bss_16818->player[lbl_1_bss_16818->order[i]].no;
}

/* 6 insns */
s32 fn_1_96C(void)
{
    return lbl_1_bss_16818->unk22C;
}

/* 6 insns */
s32 fn_1_984(void)
{
    return lbl_1_bss_16818->unk22D;
}

/* 6 insns */
s32 fn_1_99C(void)
{
    return lbl_1_bss_1681C->winNum;
}

/* 8 insns */
s32 fn_1_9B4(s32 i)
{
    return (s8)lbl_1_bss_16818->player[i].no;
}

/* 16 insns */
s32 fn_1_9D4(s32 i)
{
    if (lbl_1_bss_1681C->winNum <= i) {
        return -1;
    }
    return lbl_1_bss_1681C->winner[i];
}

/* 26 insns */
void fn_1_A14(s32 mdlId, float start, float end)
{
    Hu3DMotionStartEndSet(mdlId, start, end);
    Hu3DMotionTimeSet(mdlId, start);
    Hu3DMotionShapeTimeSet(mdlId, start);
}

/* 71 insns */
void fn_1_A7C(void)
{
    s32 key[4];
    int i;
    int time;
    HuWinDisablePlayerSet(lbl_1_bss_16818->winId, 15);
    while (!fn_1_88C(lbl_1_bss_16818->waitMesFlag)) {
        for (i = 4; i--;) {
            key[i] = -1;
            if (GwPlayerConf[i].type != GW_TYPE_MAN) {
                key[i] = PAD_BUTTON_A;
            }
        }
        HuWinComKeyWait(key[0], key[1], key[2], key[3], 10);
        fn_1_40C(30);
    }
    HuWinDisablePlayerReset(lbl_1_bss_16818->winId, 15);
    HuWinComKeyReset();
    HuPrcEnd();
}

/* 21 insns */
void fn_1_B98(u32 mesFlag)
{
    lbl_1_bss_16818->waitMesFlag = mesFlag;
    HuPrcChildCreate(fn_1_A7C, 200, 12288, 0, HuPrcCurrentGet());
}

/* 17 insns */
void ObjectSetup(void)
{
    _SetFlag(FLAG_MGINST_ON);
    HuPrcChildCreate(fn_1_C30, 200, 12288, 0, HuPrcCurrentGet());
}

/* 75 insns */
void fn_1_C30(void)
{
    BOOL mgF;
    BOOL runF;
    OMOVLHIS *his;
    his = omOvlHisGet(0);
    fn_1_48B4();
    runF = TRUE;
    while (runF) {
        mgF = TRUE;
        switch (his->evtno) {
            case 0:
                fn_1_56C0();
                runF = TRUE;
                break;

            case 1:
                fn_1_6538();
                if (!fn_1_7E4(8)) {
                    fn_1_7450();
                }
                if (fn_1_83C(1)) {
                    mgF = FALSE;
                }
                break;

            case 2:
                fn_1_9094();
                mgF = FALSE;
                break;

            case 3:
                if (fn_1_7E4(2)) {
                    fn_1_A5D8();
                }
                mgF = FALSE;
                runF = FALSE;
                break;
        }
        if (mgF) {
            fn_1_7CB8();
        }
    }
    fn_1_5540();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

/* 18 insns */
void fn_1_D5C(s32 evtno)
{
    OMOVLHIS *his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, evtno, his->stat);
}

/* 16 insns */
void fn_1_DA4(void (*func)(void))
{
    HuPrcChildCreate(func, 100, 4096, 0, HuPrcCurrentGet());
    HuPrcVSleep();
}

/* 380 insns */
void fn_1_DE4(s16 layerNo)
{
    Mtx44 proj;
    Mtx modelview;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    if (Hu3DCameraBit == HU3D_CAM2) {
        C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, 10.0f);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        PSMTXIdentity(modelview);
        GXLoadPosMtxImm(modelview, GX_PNMTX0);
        GXSetCurrentMtx(GX_PNMTX0);
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        GXSetScissor(0, 0, 640, 480);
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
        HuSprTexLoad(lbl_1_bss_16818->fbCopyAnim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_U16, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_C0, GX_CC_TEXC, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2u16(0, 0);
        GXTexCoord2f32(lbl_1_bss_16818->fbCopyX, lbl_1_bss_16818->fbCopyY);
        GXPosition2u16(640, 0);
        GXTexCoord2f32(5.0f + lbl_1_bss_16818->fbCopyX, lbl_1_bss_16818->fbCopyY);
        GXPosition2u16(640, 480);
        GXTexCoord2f32(5.0f + lbl_1_bss_16818->fbCopyX, 5.0f + lbl_1_bss_16818->fbCopyY);
        GXPosition2u16(0, 480);
        GXTexCoord2f32(lbl_1_bss_16818->fbCopyX, 5.0f + lbl_1_bss_16818->fbCopyY);
        GXEnd();
        lbl_1_bss_16818->fbCopyX += 0.005;
        if (lbl_1_bss_16818->fbCopyX >= 1.0) {
            lbl_1_bss_16818->fbCopyX = 0.0f;
        }
        lbl_1_bss_16818->fbCopyY += 0.005;
        if (lbl_1_bss_16818->fbCopyY >= 1.0) {
            lbl_1_bss_16818->fbCopyY = 0.0f;
        }
    }
}

/* 299 insns */
void fn_1_13D4(void)
{
    int mdlId;
    int i;
    lbl_1_bss_16818->stageMdlId[0] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 2));
    lbl_1_bss_16818->stageMdlId[2] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 4));
    lbl_1_bss_16818->stageMdlId[3] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 5));
    lbl_1_bss_16818->stageMdlId[1] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 3));
    lbl_1_bss_16818->stageMdlId[5] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 6));
    lbl_1_bss_16818->stageMdlId[6] = Hu3DModelCreateData(DATANUM(DATA_mgtour, 6));
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[0], 2);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[2], 2);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[3], 2);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[1], 2);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[5], 2);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[6], 2);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[2], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[1], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[6], HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[0], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[2], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[3], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[1], HU3D_CAM4);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[5], HU3D_CAM2);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[6], HU3D_CAM2);
    Hu3DMotionSpeedSet(lbl_1_bss_16818->stageMdlId[1], Hu3DMotionMotionMaxTimeGet(lbl_1_bss_16818->stageMdlId[1]) / 6000.0f);
    lbl_1_bss_16818->reflectMdlId = mdlId = Hu3DModelCreateData(DATANUM(DATA_mgtour, 7));
    lbl_1_bss_16818->stageMdlId[4] = mdlId;
    Hu3DModelLayerSet(mdlId, 3);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DReflectNoSet(1);
    Hu3DModelReflectTypeSet(mdlId, -1);
    Hu3DModelCameraSet(mdlId, HU3D_CAM2);
    for (i = 4; i--;) {
        lbl_1_bss_16818->stageMdlId[12 + i] = mdlId = Hu3DModelCreateData(DATANUM(DATA_mgtour, 8));
        Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelCameraSet(mdlId, HU3D_CAM2);
    }
    lbl_1_bss_16818->stageMdlId[11] = mdlId = Hu3DModelCreateData(DATANUM(DATA_mgtour, 9));
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdlId, 0);
    Hu3DModelCameraSet(mdlId, HU3D_CAM1);
    Hu3DModelPosSetV(mdlId, &lbl_1_data_70);
    Hu3DModelScaleSet(mdlId, 10.0f, 10.0f, 10.0f);
}

/* 24 insns */
void fn_1_1880(void)
{
    CamMotionExPath(HU3D_CAM4, lbl_1_bss_16818->camMot, lbl_1_bss_16818->camMotNum);
    fn_1_7AC(0x40);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_18E0(void)
{
    fn_1_7C8(0x40);
    fn_1_DA4(fn_1_1880);
}

/* 204 insns */
void fn_1_1938(void)
{
    s8 order[15];
    int i;
    int time;
    int cnt;
    time = -1;
    for (i = lbl_1_bss_16818->mgNum; i--;) {
        order[i] = i;
    }
    fn_1_140(order, lbl_1_bss_16818->mgNum);
    while (fn_1_7E4(0x200)) {
        if (fn_1_7E4(0x80)) {
            fn_1_7C8(0x80);
            if (lbl_1_bss_16818->mgNum >= 10) {
                time = frandmod(lbl_1_bss_16818->mgNum) + 30;
            }
            else if (lbl_1_bss_16818->mgNum >= 7) {
                time = frandmod(lbl_1_bss_16818->mgNum) + 20;
            }
            else if (lbl_1_bss_16818->mgNum >= 4) {
                time = frandmod(lbl_1_bss_16818->mgNum) + 15;
            }
            else {
                time = frandmod(lbl_1_bss_16818->mgNum) + 10;
            }
            cnt = 0;
        }
        if (time >= 0) {
            if (++cnt >= 3) {
                if (time == 0) {
                    Hu3DModelDispOn(lbl_1_bss_16818->stageMdlId[5]);
                    Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[6]);
                    HuAudFXPlay(1191);
                    fn_1_7AC(0x100);
                }
                else {
                    HuAudFXPlay(1190);
                    if (lbl_1_bss_16818->animId >= 0) {
                        Hu3DAnimKill(lbl_1_bss_16818->animId);
                    }
                    lbl_1_bss_16818->animId = Hu3DAnimCreate(lbl_1_bss_16818->mgIcon[order[time % lbl_1_bss_16818->mgNum]], lbl_1_bss_16818->stageMdlId[6], "ukiwa_naka");
                    cnt = 0;
                }
                time--;
            }
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 96 insns */
void fn_1_1C68(void)
{
    if (!fn_1_7E4(0x200)) {
        Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[5]);
        Hu3DModelScaleSet(lbl_1_bss_16818->stageMdlId[5], 3.8f, 3.8f, 1.0f);
        Hu3DModelPosSet(lbl_1_bss_16818->stageMdlId[5], lbl_1_data_114[0], lbl_1_data_114[1], lbl_1_data_114[2]);
        Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[6]);
        Hu3DModelScaleSet(lbl_1_bss_16818->stageMdlId[6], 3.8f, 3.8f, 1.0f);
        Hu3DModelPosSet(lbl_1_bss_16818->stageMdlId[6], lbl_1_data_114[0], lbl_1_data_114[1], lbl_1_data_114[2]);
        fn_1_7AC(0x200);
        HuPrcChildCreate(fn_1_1938, 100, 4096, 0, HuPrcCurrentGet());
    }
}

/* 13 insns */
void fn_1_1DE8(void)
{
    fn_1_7AC(0x80);
    fn_1_7C8(0x100);
}

/* 46 insns */
void fn_1_1E1C(void)
{
    char *path = mgDataTbl[lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgIdx].movie[0];
    HuTHPSprCreateVol(path, 1, 0, 0.0f);
    Hu3DModelMatHookSet(lbl_1_bss_16818->stageMdlId[5], HuTHPMatHook);
}

/* 105 insns */
void fn_1_1ED4(void)
{
    s8 last = lbl_1_bss_1681C->mgOrder[lbl_1_bss_16818->mgNum - 1];
    lbl_1_bss_1681C->round = 0;
    fn_1_140(lbl_1_bss_1681C->mgOrder, lbl_1_bss_16818->mgNum);
    if (lbl_1_bss_1681C->mgOrder[0] == last) {
        lbl_1_bss_1681C->mgOrder[0] = lbl_1_bss_1681C->mgOrder[lbl_1_bss_16818->mgNum / 2];
        lbl_1_bss_1681C->mgOrder[lbl_1_bss_16818->mgNum / 2] = last;
    }
}

/* 237 insns */
void fn_1_2078(void)
{
    int i;
    lbl_1_bss_1681C->flag = 0;
    lbl_1_bss_1681C->round = 0;
    fn_1_750();
    fn_1_D5C(0);
    lbl_1_bss_1681C->camPos.z += 2000.0f;
    Hu3DCameraViewportSet(HU3D_CAM4, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_1681C->camPos, &lbl_1_bss_1681C->camUp, &lbl_1_bss_1681C->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_1681C->camFov, 20.0f, 60000.0f, 1.2f);
    Hu3DCameraKill(HU3D_CAM1);
    fn_1_D29C(0);
    fn_1_7C8(0x40000000);
    for (i = 4; i--;) {
        lbl_1_bss_1681C->playerPos[i] = i;
    }
    fn_1_140(lbl_1_bss_1681C->playerPos, 4);
    Hu3DModelLayerSet(lbl_1_bss_16818->stageMdlId[4], 3);
    Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[4]);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[4], HU3D_CAM2);
    fn_1_A14(lbl_1_bss_16818->stageMdlId[2], 0.0f, 28.0f);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[2], HU3D_MOTATTR_PAUSE);
    fn_1_7C8(0x4000);
    HuTHPClose();
    HuPrcVSleep();
    while (HuTHPProcCheck()) {
        HuPrcVSleep();
    }
}

/* 110 insns */
void fn_1_242C(void)
{
    fn_1_A14(lbl_1_bss_16818->stageMdlId[0], 0.0f, 179.0f);
    Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    Hu3DCameraMotionOn(lbl_1_bss_16818->stageMdlId[0], HU3D_CAM4);
    while (!Hu3DMotionEndCheck(lbl_1_bss_16818->stageMdlId[0])) {
        HuPrcVSleep();
    }
    Hu3DCameraMotionOff(lbl_1_bss_16818->stageMdlId[0]);
    fn_1_A14(lbl_1_bss_16818->stageMdlId[0], 180.0f, 359.0f);
    Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    fn_1_7AC(0x40);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_25E4(void)
{
    fn_1_7C8(0x40);
    fn_1_DA4(fn_1_242C);
}

/* 161 insns */
void fn_1_263C(s32 cameraBit)
{
    int mdlId;
    int i;
    float ofs = 200.0f;
    for (i = 4; i--;) {
        mdlId = lbl_1_bss_16818->stageMdlId[7 + i];
        Hu3DModelPosSet(mdlId, -(1.5f * ofs) + i * ofs, 0.0f, lbl_1_data_1B4[lbl_1_bss_16818->player[i].charNo]);
        Hu3DModelDispOn(mdlId);
        Hu3DModelCameraSet(mdlId, HU3D_CAM1);
        Hu3DModelLayerSet(mdlId, 0);
        mdlId = lbl_1_bss_16818->stageMdlId[12 + i];
        Hu3DModelDispOn(mdlId);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelCameraSet(mdlId, cameraBit);
    }
    Hu3DCameraCreate(HU3D_CAM1);
    Hu3DCameraPerspectiveSet(HU3D_CAM1, 1.2f, 15000.0f, 40000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM1, 0, 0, 640, 480);
    Hu3DCameraPosSet(HU3D_CAM1, 0.0f, 100.0f, 30000.0f, 0.0f, 1.0f, 0.0f, 0.0f, 100.0f, 0.0f);
}

/* 266 insns */
void fn_1_28C0(void)
{
    HuVecF pos, up, target;
    float ofs;
    int i;
    int mdlId;
    fn_1_7AC(0x400);
    Hu3DCameraKill(HU3D_CAM4);
    pos.x = pos.y = 0;
    pos.z = lbl_1_bss_1681C->camPos.z;
    up.x = up.z = 0;
    up.y = 1;
    target.x = target.y = target.z = 0;
    Hu3DCameraCreate(HU3D_CAM1);
    Hu3DCameraViewportSet(HU3D_CAM2, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM2, 0, 0, 640, 480);
    Hu3DCameraPosSetV(HU3D_CAM2, &pos, &up, &target);
    Hu3DCameraPerspectiveSet(HU3D_CAM2, lbl_1_bss_1681C->camFov, 20, 13000, 1.2f);
    ofs = 200;
    for (i = 4; i--;) {
        mdlId = lbl_1_bss_16818->stageMdlId[7 + i];
        Hu3DModelPosSet(mdlId, -(1.5f * ofs) + (i * ofs), 0, lbl_1_data_1B4[lbl_1_bss_16818->player[i].charNo]);
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdlId, HU3D_CAM1);
        Hu3DModelLayerSet(mdlId, 0);
        mdlId = lbl_1_bss_16818->stageMdlId[12 + i];
        Hu3DModelAttrReset(mdlId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(mdlId, 4);
        Hu3DModelCameraSet(mdlId, HU3D_CAM2);
    }
    MgTourCam1Setup();
}

/* 96 insns */
void fn_1_2CE8(void)
{
    int i;
    int mdlId;
    fn_1_7C8(0x400);
    for (i = 4; i--;) {
        mdlId = lbl_1_bss_16818->stageMdlId[7 + i];
        Hu3DModelCameraSet(mdlId, HU3D_CAM4);
        Hu3DModelLayerSet(mdlId, 4);
    }
    Hu3DCameraCreate(HU3D_CAM4);
    Hu3DCameraKill(HU3D_CAM1 | HU3D_CAM2);
    Hu3DCameraViewportSet(HU3D_CAM4, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_1681C->camPos, &lbl_1_bss_1681C->camUp, &lbl_1_bss_1681C->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_1681C->camFov, 20.0f, 60000.0f, 1.2f);
    fn_1_CFEC(0);
}

/* 844 insns */
void fn_1_2E68(void)
{
    HuVecF guidePos;
    HuVecF guideDir;
    HuVecF parVec;
    HuVecF parPos;
    HuVecF moveVec;
    HuVecF movePos;
    MGTOUR_PLAYER *player;
    int state;
    int time;
    int i;
    int parManId;
    BOOL loop;
    int moveParManId;
    ANIMDATA *anim;
    float t;
    float guideRot;
    float parAngle;
    float moveAngle;
    float speed;
    state = 0;
    loop = TRUE;
    player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[lbl_1_bss_16818->unk22C == 0]];
    while (loop) {
        switch (state) {
            case 0:
                if (player->mot != 5) {
                    CharMotionShiftSet(player->charNo, player->motId[5], 0, 5, HU3D_MOTATTR_LOOP);
                    player->mot = 5;
                }
                fn_1_40C(120);
                Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[3], HU3D_MOTATTR_PAUSE);
                time = 25;
                guideRot = 0;
                state = 1000;
                break;

            case 1000:
                t = 1.0f - time / 25.0f;
                t = sin(M_PI * t / 2.0);
                t = sin(M_PI * t / 2.0);
                fn_1_204(&guideRot, 45.0f, 3.0f);
                VECSubtract(&lbl_1_data_7C[3], &lbl_1_data_7C[2], &guideDir);
                VECScale(&guideDir, &guideDir, t);
                VECAdd(&lbl_1_data_7C[2], &guideDir, &guidePos);
                Hu3DModelPosSetV(lbl_1_bss_16818->guideMdlId, &guidePos);
                Hu3DModelRotSet(lbl_1_bss_16818->guideMdlId, 0, guideRot, 0);
                if (--time == 0) {
                    state = 1;
                }
                break;

            case 1:
                if (lbl_1_bss_16818->unk22C != 0) {
                    HuAudFXPlayPan(1192, 48);
                    omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 15, 4, 2);
                    fn_1_A14(lbl_1_bss_16818->stageMdlId[2], 0, 28);
                }
                else {
                    HuAudFXPlayPan(1192, 80);
                    omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 15, 4, 2);
                    fn_1_A14(lbl_1_bss_16818->stageMdlId[2], 29, 58);
                }
                Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[2], HU3D_MOTATTR_PAUSE);
                if (player->mot != 7) {
                    CharMotionShiftSet(player->charNo, player->motId[7], 0, 5, HU3D_MOTATTR_NONE);
                    player->mot = 7;
                }
                fn_1_40C(25);
                state = 2;
                break;

            case 2:
                if (player->mot != 4) {
                    CharMotionShiftSet(player->charNo, player->motId[4], 0, 5, HU3D_MOTATTR_LOOP);
                    player->mot = 4;
                }
                Hu3DMotionAttrSet(player->motId[4], HU3D_ATTR_MOT_RESET_LOCK);
                state = 3;
                break;

            case 3:
                fn_1_40C(30);
                time = 30;
                speed = 750;
                state = 4;
                break;

            case 4:
                speed += 150;
                player->pos.y -= speed / 100;
                Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
                if (--time == 0) {
                    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 0x22), HU_MEMNUM_OVL, HEAP_MODEL));
                    lbl_1_data_130.colorStart[0] = lbl_1_data_120[0];
                    lbl_1_data_130.colorStart[1] = lbl_1_data_120[1];
                    lbl_1_data_130.colorEnd[0] = lbl_1_data_120[2];
                    lbl_1_data_130.colorEnd[1] = lbl_1_data_120[3];
                    parAngle = 0;
                    for (i = 24; i--;) {
                        parAngle += 15;
                        parVec.x = cos(M_PI * parAngle / 180.0);
                        parVec.y = 10;
                        parVec.z = sin(M_PI * parAngle / 180.0);
                        parPos = player->pos;
                        parPos.x += 30 * parVec.x;
                        parPos.z += 30 * parVec.z;
                        parPos.y = -150;
                        VECNormalize(&parVec, &parVec);
                        parManId = Hu3DParManCreate(anim, 30, &lbl_1_data_130);
                        lbl_1_bss_16818->parManId[i] = parManId;
                        Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_RANDTIME70 | HU3D_PARMAN_ATTR_SCALEJITTER | HU3D_PARMAN_ATTR_RANDSCALE70 | HU3D_PARMAN_ATTR_RANDSPEED70);
                        Hu3DParManLayerSet(parManId, 4);
                        Hu3DParManPosSet(parManId, parPos.x, parPos.y, parPos.z);
                        Hu3DParManVecSet(parManId, parVec.x, parVec.y, parVec.z);
                    }
                    if (lbl_1_bss_16818->unk22C != 0) {
                        HuAudFXPlayPan(1193, 48);
                        omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 20, 4, 2);
                    }
                    else {
                        HuAudFXPlayPan(1193, 80);
                        omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 20, 4, 2);
                    }
                    time = 10;
                    state = 5;
                }
                break;

            case 5:
                if (--time == 0) {
                    state = 6;
                }
                moveAngle = 0;
                for (i = 24; i--;) {
                    moveAngle += 15;
                    moveVec.x = cos(M_PI * moveAngle / 180.0);
                    moveVec.y = time;
                    moveVec.z = sin(M_PI * moveAngle / 180.0);
                    movePos = player->pos;
                    movePos.x += 30 * moveVec.x * (1.0f + (10.0f / time) / 4.0f);
                    movePos.z += 30 * moveVec.z * (1.0f + (10.0f / time) / 4.0f);
                    movePos.y = -150;
                    VECNormalize(&moveVec, &moveVec);
                    moveParManId = lbl_1_bss_16818->parManId[i];
                    Hu3DParManPosSet(moveParManId, movePos.x, movePos.y, movePos.z);
                    Hu3DParManVecSet(moveParManId, moveVec.x, moveVec.y, moveVec.z);
                }
                break;

            case 6:
                loop = FALSE;
                break;
        }
        HuPrcVSleep();
    }
    fn_1_7AC(0x800);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_3B98(void)
{
    fn_1_7C8(0x800);
    fn_1_DA4(fn_1_2E68);
}

/* 79 insns */
void fn_1_3BF0(void)
{
    float angle = 0.0f;
    float ofs;
    HuVecF target;
    while (fn_1_7E4(0x4000)) {
        ofs = sin(M_PI * angle / 180.0);
        target = lbl_1_bss_16818->camTarget;
        target.y += 5.0f * ofs;
        Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_16818->camPos, &lbl_1_bss_1681C->camUp, &target);
        angle += 2.3f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 46 insns */
void fn_1_3D2C(void)
{
    lbl_1_bss_16818->camPos = lbl_1_bss_1681C->camPos;
    lbl_1_bss_16818->camTarget = lbl_1_bss_1681C->camTarget;
    fn_1_7AC(0x4000);
    fn_1_DA4(fn_1_3BF0);
}

/* 447 insns */
void fn_1_3DE4(void)
{
    HuVecF dir;
    HuVecF aimPos;
    MGTOUR_PLAYER *player;
    int i;
    int doneNum;
    float rotEnd;
    for (player = &lbl_1_bss_16818->player[0], i = 0; i < 4; i++, player++) {
        switch (lbl_1_bss_16818->playerRotMode) {
            case 0:
                player->rotEnd = 0;
                break;

            case 1:
                aimPos = lbl_1_bss_16818->guidePos;
                aimPos.z += 350;
                VECSubtract(&aimPos, &player->pos, &aimPos);
                aimPos.y = 0;
                VECNormalize(&aimPos, &dir);
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
        if (!fn_1_204(&player->rot, player->rotEnd, 0.01f)) {
            if (player->mot != 1) {
                CharMotionShiftSet(player->charNo, player->motId[1], 0, 5, HU3D_MOTATTR_LOOP);
                player->mot = 1;
            }
        }
    }
    while (1) {
        doneNum = 0;
        for (player = &lbl_1_bss_16818->player[0], i = 4; i--; player++) {
            if (fn_1_204(&player->rot, player->rotEnd, lbl_1_bss_16818->playerRotSpeed)) {
                if (player->mot != 0) {
                    CharMotionShiftSet(player->charNo, player->motId[0], 0, 5, HU3D_MOTATTR_LOOP);
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
    fn_1_7AC(0x1000);
    HuPrcEnd();
}

/* 35 insns */
void fn_1_44E0(s32 mode, float speed)
{
    fn_1_7C8(0x1000);
    lbl_1_bss_16818->playerRotMode = mode;
    lbl_1_bss_16818->playerRotSpeed = speed;
    fn_1_DA4(fn_1_3DE4);
}

/* 188 insns */
void fn_1_456C(void)
{
    HuVecF basePos;
    HuVecF pos;
    float ofs;
    int angle;
    int mdlId;
    int parManId;
    ANIMDATA *anim;
    s32 charNo;
    mdlId = lbl_1_bss_16818->stageMdlId[4];
    angle = 0;
    basePos = lbl_1_data_28[lbl_1_bss_16818->unk22C + 4];
    charNo = lbl_1_bss_16818->unk22D;
    basePos.y += 25.0f + (40.0f + CharModelHeightGet(charNo));
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 0x23), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_data_1F8.colorStart[0] = lbl_1_data_1E8[0];
    lbl_1_data_1F8.colorStart[1] = lbl_1_data_1E8[1];
    lbl_1_data_1F8.colorEnd[0] = lbl_1_data_1E8[2];
    lbl_1_data_1F8.colorEnd[1] = lbl_1_data_1E8[3];
    parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_1F8);
    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_SCALEJITTER | HU3D_PARMAN_ATTR_RANDSCALE90 | HU3D_PARMAN_ATTR_RANDSPEED70);
    Hu3DParManLayerSet(parManId, 4);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), HU3D_PARTICLE_BLEND_ADDCOL);
    while (fn_1_7E4(0x2000)) {
        ofs = sin(M_PI * angle / 180.0);
        pos = basePos;
        pos.y += 25.0f * ofs;
        Hu3DModelPosSetV(mdlId, &pos);
        Hu3DParManPosSet(parManId, pos.x, pos.y, pos.z);
        angle++;
        angle %= 360;
        HuPrcVSleep();
    }
    Hu3DParManAttrSet(parManId, HU3D_PARMAN_ATTR_TIMEUP);
    HuPrcEnd();
}

/* 22 insns */
void fn_1_485C(void)
{
    fn_1_7AC(0x2000);
    fn_1_DA4(fn_1_456C);
}

/* 803 insns */
void fn_1_48B4(void)
{
    MGTOUR_PLAYER *player;
    int i;
    HU3DMODELID guideMdlId;
    int mgIdx;
    HU3DMOTID guideMotId;
    OMOVLHIS *his;
    ANIMDATA *anim;

    his = omOvlHisGet(0);
    lbl_1_bss_1681C = (MGTOUR_MODEWORK *)mgModeWork;
    lbl_1_bss_16818 = &lbl_1_bss_16820;
    {
        HuVecF lightPos = { 0, 8000, 0 };
        HuVecF lightUp = { 0, 0, 1 };
        HuVecF lightTarget = { 0, 0, 0 };
        HuVecF lightDir = { 0, -1, 0 };
        HuVecF light2Pos = { 0, 50, 4000 };
        HuVecF light2Dir = { 0, 0, -1 };
        int lightId;
        lbl_1_bss_16818->objman = omInitObjMan(200, 1000);
        HuDataSelHeapReadNum(DATANUM(DATA_instpic, 0), HU_MEMNUM_OVL, HEAP_MODEL);
        Hu3DCameraCreate(HU3D_CAM4);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, 60, 20, 30000, 1.2f);
        Hu3DCameraViewportSet(HU3D_CAM4, 0, 0, 640, 480, 0, 1);
        Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
        lightId = Hu3DGLightCreate(0, 1000, 1000, 0, -1, -1, 255, 255, 255);
        Hu3DGLightStaticSet(lightId, TRUE);
        Hu3DGLightPosSetV(lightId, &lightPos, &lightDir);
        lightId = Hu3DGLightCreate(0, 1000, 1000, 0, -1, -1, 128, 128, 128);
        Hu3DGLightStaticSet(lightId, TRUE);
        Hu3DGLightPosSetV(lightId, &light2Pos, &light2Dir);
    }
    lbl_1_bss_16818->mgNum = 0;
    for (i = 0; i < 15; i++) {
        for (mgIdx = 0; mgDataTbl[mgIdx].ovl != lbl_1_data_B8[i].ovl; mgIdx++) {
            if (mgDataTbl[mgIdx].ovl == (u16)DLL_NONE) {
                OSReport("mgtournament.c : \202c\202k\202k\202\252\214\251\202\302\202\251\202\350\202\334\202\271\202\361\201I\201I\n");
                abort();
            }
        }
        lbl_1_data_B8[i].mgIdx = mgIdx;
        if (GWMgUnlockGet(mgIdx + 501)) {
            lbl_1_bss_16818->mgTbl[lbl_1_bss_16818->mgNum] = lbl_1_data_B8[i];
            lbl_1_bss_16818->mgNum++;
        }
    }
    Hu3DParManInit();
    lbl_1_bss_16818->unk120 = -1;
    lbl_1_bss_16818->winId = 0;
    lbl_1_bss_16818->mesFlag = 0;
    lbl_1_bss_16818->flag = 0;
    lbl_1_bss_16818->unk22C = -1;
    lbl_1_bss_16818->unk22D = -1;
    lbl_1_bss_16818->order[0] = -1;
    lbl_1_bss_16818->order[1] = -1;
    lbl_1_bss_16818->streamNo = MSM_STREAMNO_NONE;
    lbl_1_bss_16818->animId = -1;
    lbl_1_bss_16818->seNo = MSM_SENO_NONE;
    lbl_1_bss_16818->playerRotMode = 0;
    lbl_1_bss_16818->playerRotSpeed = 2;
    {
        HuVec2f winSize;

        HuWinInit(1);
        HuWinMesMaxSizeBetGet(&winSize, MESSNUM(MESS_MGMODE_TO, 0), MESSNUM(MESS_MGMODE_TO, 14));
        lbl_1_bss_16818->winId = HuWinExCreateFrame(-10000, 360, winSize.x, winSize.y, HUWIN_SPEAKER_NONE, 1);
        HuWinMesPalSet(lbl_1_bss_16818->winId, 7, 0, 0, 0);
    }
    fn_1_13D4();
    if (!fn_1_7E4(0x200)) {
        Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[5]);
        Hu3DModelScaleSet(lbl_1_bss_16818->stageMdlId[5], 3.8f, 3.8f, 1);
        Hu3DModelPosSet(lbl_1_bss_16818->stageMdlId[5], lbl_1_data_114[0], lbl_1_data_114[1], lbl_1_data_114[2]);
        Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[6]);
        Hu3DModelScaleSet(lbl_1_bss_16818->stageMdlId[6], 3.8f, 3.8f, 1);
        Hu3DModelPosSet(lbl_1_bss_16818->stageMdlId[6], lbl_1_data_114[0], lbl_1_data_114[1], lbl_1_data_114[2]);
        fn_1_7AC(0x200);
        HuPrcChildCreate(fn_1_1938, 100, 4096, 0, HuPrcCurrentGet());
    }
    fn_1_C434(lbl_1_bss_16818->stageMdlId);
    lbl_1_bss_16818->fbCopyAnim = HuSprAnimDataRead(DATANUM(DATA_mgtour, 15));
    Hu3DLayerHookSet(0, fn_1_DE4);
    lbl_1_bss_16818->fbCopyX = 0;
    lbl_1_bss_16818->fbCopyY = 0;
    if (his->evtno == 0) {
        _SetFlag(FLAG_INST_NOHISCHG);
        _SetFlag(FLAG_INST_MGMODE);
        for (i = 4; i--;) {
            lbl_1_bss_1681C->playerPos[i] = i;
        }
        fn_1_140(lbl_1_bss_1681C->playerPos, 4);
    }
    else {
        Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_1681C->camPos, &lbl_1_bss_1681C->camUp, &lbl_1_bss_1681C->camTarget);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_1681C->camFov, 20, 30000, 1.2f);
    }
    for (player = &lbl_1_bss_16818->player[0], i = 0; i < GW_PLAYER_MAX; i++, player++) {
        player->no = i;
        player->charNo = GwPlayerConf[player->no].charNo;
        player->padNo = GwPlayerConf[player->no].padNo;
        player->mdlId = CharModelMotListCreate(player->charNo, CHAR_MODEL1, lbl_1_data_0, player->motId);
        player->mot = -1;
        player->pos = lbl_1_data_28[lbl_1_bss_1681C->playerPos[i]];
        player->rot = 0;
        player->rotEnd = 0;
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[2], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[3], FALSE);
        CharMotionVoiceOnSet(player->charNo, lbl_1_data_0[4], FALSE);
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 5, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelDispOff(player->mdlId);
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelLayerSet(player->mdlId, 4);
        Hu3DModelCameraSet(player->mdlId, HU3D_CAM4);
        lbl_1_bss_16818->stageMdlId[i + 7] = player->mdlId;
    }
    {
        HuVecF guidePos = lbl_1_data_7C[0];
        guideMdlId = Hu3DModelCreateData(DATANUM(DATA_mgtour, 0));
        lbl_1_bss_16818->guideMdlId = guideMdlId;
        lbl_1_bss_16818->guidePos = guidePos;
        guideMotId = Hu3DJointMotionData(guideMdlId, DATANUM(DATA_mgtour, 1));
        Hu3DMotionSet(guideMdlId, guideMotId);
        Hu3DModelAttrSet(guideMdlId, HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(guideMdlId, 5);
        Hu3DModelCameraSet(guideMdlId, HU3D_CAM4);
        Hu3DModelPosSet(guideMdlId, guidePos.x, guidePos.y, guidePos.z);
    }
    for (i = lbl_1_bss_16818->mgNum; i--;) {
        anim = HuSprAnimDataRead(mgDataTbl[lbl_1_bss_16818->mgTbl[i].mgIdx].instPic[0]);
        HuSprAnimLock(anim);
        lbl_1_bss_16818->mgIcon[i] = anim;
    }
    for (i = 18; i--;) {
        Hu3DCameraMotionOff(lbl_1_bss_16818->stageMdlId[i]);
    }
    lbl_1_bss_16818->seNo = HuAudFXPlay(927);
}

/* 96 insns */
void fn_1_5540(void)
{
    if (lbl_1_bss_16818->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_16818->streamNo, 1000);
        lbl_1_bss_16818->streamNo = MSM_STREAMNO_NONE;
    }
    HuDataDirClose(DATA_mgtour);
    HuDataDirClose(DATA_instpic);
    CharModelDataClose(CHARNO_NONE);
    fn_1_C76C();
    HuTHPClose();
    GWMgInstFSet(TRUE);
    fn_1_D5C(0);
    HuWinExClose(lbl_1_bss_16818->winId);
    HuWinExKill(lbl_1_bss_16818->winId);
    if (lbl_1_bss_16818->seNo >= 0) {
        HuAudFXStop(lbl_1_bss_16818->seNo);
        lbl_1_bss_16818->seNo = MSM_SENO_NONE;
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    _ClearFlag(FLAG_INST_NOHISCHG);
    _ClearFlag(FLAG_INST_MGMODE);
    memset(lbl_1_bss_1681C, 0, sizeof(MGTOUR_MODEWORK));
}

/* 926 insns */
void fn_1_56C0(void)
{
    int i;
    MGTOUR_PLAYER *player;
    int mdlId;
    int k;
    int j;
    OMOVLHIS *his;
    float near;
    float far;
    float fov;
    int seNo;
    char *movie;

    his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, 1, his->stat);
    fn_1_7C8(0);
    lbl_1_bss_16818->mesFlag = 0;
    fn_1_7AC(1);
    for (i = lbl_1_bss_16818->mgNum; i--;) {
        lbl_1_bss_1681C->mgOrder[i] = i;
    }
    lbl_1_bss_1681C->round = lbl_1_bss_16818->mgNum;
    fn_1_1ED4();
    movie = mgDataTbl[lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgIdx].movie[0];
    HuTHPSprCreateVol(movie, 1, 0, 0);
    Hu3DModelMatHookSet(lbl_1_bss_16818->stageMdlId[5], HuTHPMatHook);
    for (player = &lbl_1_bss_16818->player[0], i = 0; i < GW_PLAYER_MAX; i++, player++) {
        player->pos = lbl_1_data_28[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 5, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        Hu3DModelDispOn(player->mdlId);
        Hu3DModelPosSet(player->mdlId, player->pos.x, player->pos.y, player->pos.z);
        Hu3DModelLayerSet(player->mdlId, 4);
        Hu3DModelCameraSet(player->mdlId, HU3D_CAM4);
    }
    lbl_1_bss_1681C->winNum = 0;
    {
        s32 charNo[4];
        s32 playerNo[4];
        for (i = 4; i--;) {
            playerNo[i] = lbl_1_bss_1681C->playerPos[i];
            charNo[i] = lbl_1_bss_16818->player[i].charNo;
        }
        fn_1_C7BC(playerNo, charNo);
    }
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        for (j = 0; j < 10; j++) {
            GwMgDecaScore[i].mgScore[j] = 0;
        }
        GwMgDecaScore[i].charNo = lbl_1_bss_16818->player[i].charNo;
        GwMgDecaScore[i].finalScore = 0;
    }
    lbl_1_bss_16818->guidePos = lbl_1_data_7C[1];
    Hu3DModelDispOn(lbl_1_bss_16818->guideMdlId);
    Hu3DModelPosSetV(lbl_1_bss_16818->guideMdlId, &lbl_1_bss_16818->guidePos);
    Hu3DModelRotSet(lbl_1_bss_16818->guideMdlId, 0, 30, 0);
    if (lbl_1_bss_16818->seNo <= 0) {
        lbl_1_bss_16818->seNo = HuAudFXPlay(927);
    }
    lbl_1_bss_16818->streamNo = HuAudBGMPlay(MSM_STREAM_MGTOUR);
    fn_1_25E4();
    fn_1_448(WIPE_TYPE_PREVTYPE, 60);
    fn_1_40C(45);
    for (i = 4; i--;) {
        omVibrate(GwPlayerConf[i].padNo, 15, 4, 2);
    }
    HuAudFXPlayPan(1187, 40);
    HuAudFXPlayPan(1187, 88);
    while (!fn_1_7E4(0x40)) {
        HuPrcVSleep();
    }
    Hu3DCameraPosGet(HU3D_CAM4, &lbl_1_bss_1681C->camPos, &lbl_1_bss_1681C->camUp, &lbl_1_bss_1681C->camTarget);
    Hu3DCameraPerspectiveGet(HU3D_CAM4, &fov, &near, &far);
    lbl_1_bss_1681C->camFov = fov;
    fn_1_3D2C();
    fn_1_44E0(1, 2);
    while (!fn_1_7E4(0x1000)) {
        HuPrcVSleep();
    }
    fn_1_DA4(fn_1_FBD0);
    while (!fn_1_88C(1)) {
        HuPrcVSleep();
    }
    fn_1_DA4(fn_1_FC34);
    while (!fn_1_88C(2)) {
        HuPrcVSleep();
    }
    fn_1_44E0(0, 2);
    while (!fn_1_7E4(0x1000)) {
        HuPrcVSleep();
    }
    fn_1_40C(30);
    fn_1_750();
    fn_1_49C(WIPE_TYPE_WHITEFADE, 60);
    fn_1_7AC(0x400);
    Hu3DCameraKill(HU3D_CAM4);
    {
        HuVecF target;
        HuVecF up;
        HuVecF pos;
        pos.x = pos.y = 0;
        pos.z = lbl_1_bss_1681C->camPos.z;
        up.x = up.z = 0;
        up.y = 1;
        target.x = target.y = target.z = 0;
        Hu3DCameraCreate(HU3D_CAM1);
        Hu3DCameraViewportSet(HU3D_CAM2, 0, 0, 640, 480, 0, 1);
        Hu3DCameraScissorSet(HU3D_CAM2, 0, 0, 640, 480);
        Hu3DCameraPosSetV(HU3D_CAM2, &pos, &up, &target);
        Hu3DCameraPerspectiveSet(HU3D_CAM2, lbl_1_bss_1681C->camFov, 20, 13000, 1.2f);
    }
    {
        float ofs = 200;
        for (k = 4; k--;) {
            mdlId = lbl_1_bss_16818->stageMdlId[k + 7];
            Hu3DModelPosSet(mdlId, -(1.5f * ofs) + (k * ofs), 0, lbl_1_data_1B4[lbl_1_bss_16818->player[k].charNo]);
            Hu3DModelDispOn(mdlId);
            Hu3DModelCameraSet(mdlId, HU3D_CAM1);
            Hu3DModelLayerSet(mdlId, 0);
            mdlId = lbl_1_bss_16818->stageMdlId[k + 12];
            Hu3DModelDispOn(mdlId);
            Hu3DModelLayerSet(mdlId, 4);
            Hu3DModelCameraSet(mdlId, HU3D_CAM2);
        }
    }
    Hu3DCameraCreate(HU3D_CAM1);
    Hu3DCameraPerspectiveSet(HU3D_CAM1, 1.2f, 15000, 40000, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM1, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM1, 0, 0, 640, 480);
    Hu3DCameraPosSet(HU3D_CAM1, 0, 100, 30000, 0, 1, 0, 0, 100, 0);
    Hu3DModelDispOff(lbl_1_bss_16818->stageMdlId[5]);
    Hu3DModelDispOn(lbl_1_bss_16818->stageMdlId[6]);
    Hu3DModelDispOn(lbl_1_bss_16818->stageMdlId[4]);
    fn_1_C804();
    fn_1_D820(1, lbl_1_bss_16818->player);
    fn_1_CFEC(1);
    seNo = HuAudFXPlay(1188);
    fn_1_D61C(2);
    fn_1_448(WIPE_TYPE_PREVTYPE, 60);
    while (!fn_1_D630()) {
        HuPrcVSleep();
    }
    HuAudFXStop(seNo);
    fn_1_40C(30);
}

/* 966 insns */
void fn_1_6538(void)
{
    s32 charNo[4];
    s32 playerPos[4];
    MGTOUR_PLAYER *player;
    int i;
    MGTOUR_PLAYER *resetPlayer;
    int num;
    int winIdx;
    char *movie;
    switch (lbl_1_bss_1681C->winNum) {
        case 0:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[0];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[1];
            break;
        case 1:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[2];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[3];
            break;
        case 2:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[!lbl_1_bss_1681C->winner[0]];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[(lbl_1_bss_1681C->winner[1] == 0) + 2];
            break;
        case 3:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[0]];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[1] + 2];
            break;
    }
    for (i = 0; i < 2; i++, resetPlayer++) {
        resetPlayer = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[i]];
        resetPlayer->pos = lbl_1_data_28[i + 4];
        if (resetPlayer->mot != 0) {
            CharMotionShiftSet(resetPlayer->charNo, resetPlayer->motId[0], 0, 5, HU3D_MOTATTR_LOOP);
            resetPlayer->mot = 0;
        }
        Hu3DModelDispOn(resetPlayer->mdlId);
        Hu3DModelPosSet(resetPlayer->mdlId, resetPlayer->pos.x, resetPlayer->pos.y, resetPlayer->pos.z);
    }
    lbl_1_bss_16818->guidePos = lbl_1_data_7C[2];
    Hu3DModelPosSetV(lbl_1_bss_16818->guideMdlId, &lbl_1_bss_16818->guidePos);
    Hu3DModelRotSet(lbl_1_bss_16818->guideMdlId, 0, 0, 0);
    Hu3DCameraMotionOff(lbl_1_bss_16818->stageMdlId[0]);
    fn_1_A14(lbl_1_bss_16818->stageMdlId[0], 180, 359);
    Hu3DModelAttrReset(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_16818->stageMdlId[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
    movie = mgDataTbl[lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgIdx].movie[0];
    HuTHPSprCreateVol(movie, 1, 0, 0);
    Hu3DModelMatHookSet(lbl_1_bss_16818->stageMdlId[5], HuTHPMatHook);
    for (i = 4; i--;) {
        playerPos[i] = lbl_1_bss_1681C->playerPos[i];
        charNo[i] = lbl_1_bss_16818->player[i].charNo;
    }
    fn_1_C7BC(playerPos, charNo);
    fn_1_3D2C();
    num = 0;
    for (i = 2; i--;) {
        OSReport("\t[Player %d : No %d] = Coin %d\n", i, lbl_1_bss_16818->order[i], MgTourCoinBonusGet(lbl_1_bss_16818->order[i]));
        if (MgTourCoinBonusGet(lbl_1_bss_16818->order[i]) >= 10) {
            winIdx = i;
            num++;
        }
    }
    if (num != 1) {
        lbl_1_bss_16818->streamNo = HuAudBGMPlay(35);
        fn_1_448(5, 60);
        fn_1_7AC(8);
        player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[0]];
        fn_1_674(player, 1);
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0, 5, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[1]];
        fn_1_674(player, 1);
        if (player->mot != 3) {
            CharMotionShiftSet(player->charNo, player->motId[3], 0, 5, HU3D_MOTATTR_NONE);
            player->mot = 3;
        }
        num = 180;
        fn_1_DA4(fn_1_10110);
        if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != GW_TYPE_MAN && GwPlayerConf[lbl_1_bss_16818->order[1]].type != GW_TYPE_MAN) {
            fn_1_B98(0x200);
        }
        while (!fn_1_88C(0x200)) {
            HuPrcVSleep();
            num--;
        }
        if (num > 0) {
            fn_1_40C(num);
        }
        fn_1_750();
        fn_1_49C(6, 60);
        player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[0]];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 0, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[1]];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 0, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
        fn_1_28C0();
        fn_1_D61C(6);
        while (!fn_1_D630()) {
            HuPrcVSleep();
        }
        fn_1_448(5, 60);
    }
    else {
        lbl_1_bss_16818->unk22C = (s8)winIdx;
        fn_1_448(5, 60);
    }
}

/* 538 insns */
void fn_1_7450(void)
{
    MGTOUR_PLAYER *player;
    int i;
    OMOVLHIS *his;
    HuAudJinglePlay(134);
    fn_1_DA4(fn_1_10178);
    if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != GW_TYPE_MAN && GwPlayerConf[lbl_1_bss_16818->order[1]].type != GW_TYPE_MAN) {
        fn_1_B98(0x400);
    }
    while (!fn_1_88C(0x400)) {
        HuPrcVSleep();
    }
    player = &lbl_1_bss_16818->player[lbl_1_bss_16818->order[lbl_1_bss_16818->unk22C]];
    fn_1_674(player, 0);
    if (player->mot != 2) {
        CharMotionShiftSet(player->charNo, player->motId[2], 0, 5, HU3D_MOTATTR_NONE);
        player->mot = 2;
    }
    fn_1_3B98();
    fn_1_40C(120);
    fn_1_750();
    while (!fn_1_7E4(0x800)) {
        HuPrcVSleep();
    }
    lbl_1_bss_16818->streamNo = HuAudBGMPlay(35);
    for (i = 4; i--;) {
        player = &lbl_1_bss_16818->player[i];
        if (player->mot != 0) {
            CharMotionShiftSet(player->charNo, player->motId[0], 0, 5, HU3D_MOTATTR_LOOP);
            player->mot = 0;
        }
    }
    fn_1_49C(6, 60);
    fn_1_28C0();
    fn_1_448(5, 60);
    fn_1_D61C(10);
    while (!fn_1_D630()) {
        HuPrcVSleep();
    }
    lbl_1_bss_1681C->winner[lbl_1_bss_1681C->winNum] = lbl_1_bss_16818->unk22C;
    lbl_1_bss_1681C->winNum++;
    if (lbl_1_bss_1681C->winNum == 4) {
        fn_1_D61C(8);
        while (!fn_1_D630()) {
            HuPrcVSleep();
        }
        fn_1_7FC(1);
        fn_1_D5C(2);
    }
}

/* 1271 insns */
void fn_1_7CB8(void)
{
    s32 mgNo;
    s32 mgIdx;

    if (lbl_1_bss_1681C->round == lbl_1_bss_16818->mgNum) {
        fn_1_1ED4();
    }
    mgNo = lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgNo;
    mgIdx = lbl_1_bss_16818->mgTbl[lbl_1_bss_1681C->mgOrder[lbl_1_bss_1681C->round]].mgIdx;
    switch (lbl_1_bss_1681C->winNum) {
        case 0:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[0];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[1];
            GwPlayerConf[lbl_1_bss_1681C->playerPos[0]].grp = 0;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[1]].grp = 1;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[2]].grp = 2;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[3]].grp = 2;
            if (!fn_1_7E4(8)) {
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 15, 4, 2);
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 15, 4, 2);
                fn_1_DA4(fn_1_FC90);
                if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
                    fn_1_B98(4);
                }
                while (!fn_1_88C(4)) {
                    HuPrcVSleep();
                }
            }
            break;
        case 1:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[2];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[3];
            GwPlayerConf[lbl_1_bss_1681C->playerPos[0]].grp = 2;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[1]].grp = 2;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[2]].grp = 0;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[3]].grp = 1;
            if (!fn_1_7E4(8)) {
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 15, 4, 2);
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 15, 4, 2);
                fn_1_DA4(fn_1_FD3C);
                if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
                    fn_1_B98(8);
                }
                while (!fn_1_88C(8)) {
                    HuPrcVSleep();
                }
            }
            break;
        case 2:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[!lbl_1_bss_1681C->winner[0]];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[!lbl_1_bss_1681C->winner[1] + 2];
            GwPlayerConf[lbl_1_bss_16818->order[0]].grp = 0;
            GwPlayerConf[lbl_1_bss_16818->order[1]].grp = 1;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[0]]].grp = 2;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[1] + 2]].grp = 2;
            if (!fn_1_7E4(8)) {
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 15, 4, 2);
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 15, 4, 2);
                fn_1_DA4(fn_1_FDE8);
                if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
                    fn_1_B98(0x10);
                }
                while (!fn_1_88C(0x10)) {
                    HuPrcVSleep();
                }
            }
            break;
        case 3:
            lbl_1_bss_16818->order[0] = lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[0]];
            lbl_1_bss_16818->order[1] = lbl_1_bss_1681C->playerPos[lbl_1_bss_1681C->winner[1] + 2];
            GwPlayerConf[lbl_1_bss_16818->order[0]].grp = 0;
            GwPlayerConf[lbl_1_bss_16818->order[1]].grp = 1;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[!lbl_1_bss_1681C->winner[0]]].grp = 2;
            GwPlayerConf[lbl_1_bss_1681C->playerPos[!lbl_1_bss_1681C->winner[1] + 2]].grp = 2;
            if (!fn_1_7E4(8)) {
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[0]].padNo, 15, 4, 2);
                omVibrate(GwPlayerConf[lbl_1_bss_16818->order[1]].padNo, 15, 4, 2);
                fn_1_DA4(fn_1_FE94);
                if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
                    fn_1_B98(0x20);
                }
                while (!fn_1_88C(0x20)) {
                    HuPrcVSleep();
                }
            }
            break;
    }
    if (!fn_1_7E4(8)) {
        lbl_1_bss_1681C->round--;
        fn_1_D61C(6);
        while (!fn_1_D630()) {
            HuPrcVSleep();
        }
        lbl_1_bss_1681C->round++;
        fn_1_40C(60);
    }
    fn_1_DA4(fn_1_FF40);
    if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
        fn_1_B98(0x40);
    }
    while (!fn_1_88C(0x40)) {
        HuPrcVSleep();
    }
    if (fn_1_7E4(0x20)) {
        fn_1_7C8(0x20);
        HuWinExClose(lbl_1_bss_16818->winId);
        HuWinHomeClear(lbl_1_bss_16818->winId);
    }
    fn_1_7AC(0x80);
    fn_1_7C8(0x100);
    fn_1_D418(0);
    fn_1_D61C(4);
    while (!fn_1_D630()) {
        HuPrcVSleep();
    }
    while (!fn_1_7E4(0x100)) {
        HuPrcVSleep();
    }
    fn_1_DA4(fn_1_FF9C);
    if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
        fn_1_B98(0x80);
    }
    while (!fn_1_88C(0x80)) {
        HuPrcVSleep();
    }
    fn_1_DA4(fn_1_10018);
    if (GwPlayerConf[lbl_1_bss_16818->order[0]].type != 0 && GwPlayerConf[lbl_1_bss_16818->order[1]].type != 0) {
        fn_1_B98(0x100);
    }
    while (!fn_1_88C(0x100)) {
        HuPrcVSleep();
    }
    if (fn_1_7E4(2)) {
        if (fn_1_7E4(0x20)) {
            fn_1_7C8(0x20);
            HuWinExClose(lbl_1_bss_16818->winId);
            HuWinHomeClear(lbl_1_bss_16818->winId);
        }
        fn_1_D5C(3);
        return;
    }
    fn_1_5CC(mgIdx);
    if (lbl_1_bss_16818->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_16818->streamNo, 1000);
        lbl_1_bss_16818->streamNo = -1;
    }
    if (lbl_1_bss_16818->seNo >= 0) {
        HuAudFXStop(lbl_1_bss_16818->seNo);
        lbl_1_bss_16818->seNo = -1;
    }
    fn_1_49C(6, 60);
    lbl_1_bss_1681C->round++;
    HuTHPClose();
    HuPrcVSleep();
    while (!lbl_1_bss_16818->dirRead) {
        HuPrcVSleep();
    }
    while (HuTHPProcCheck()) {
        HuPrcVSleep();
    }
    GwSystem.mgNo = mgNo - GW_MGNO_BASE;
    GWMgUnlockSet(mgNo);
    GwSystem.mgNo = mgNo - GW_MGNO_BASE;
    if (fn_1_7E4(4)) {
        GWMgInstFSet(TRUE);
    }
    else {
        GWMgInstFSet(FALSE);
    }
    fn_1_C76C();
    omOvlCallEx(DLL_instdll, 1, 0, 0);
    while (1) {
        HuPrcVSleep();
    }
}

/* 1361 insns */
void fn_1_9094(void)
{
    HuVecF paperVec[2];
    s32 rank[4];
    s32 order[4];
    HuVecF camPos;
    HuVecF camTarget;
    HuVecF reflectPos;
    MGTOUR_PLAYER *player;
    MGTOUR_PLAYER *winner;
    s32 side;
    s32 reflectMdlId;

    if (fn_1_9D4(0) == 0) {
        order[0] = 0;
        order[2] = 1;
    }
    else {
        order[0] = 1;
        order[2] = 0;
    }
    if (fn_1_9D4(1) == 0) {
        order[1] = 2;
        order[3] = 3;
    }
    else {
        order[1] = 3;
        order[3] = 2;
    }
    if (fn_1_9D4(2) == 0) {
        rank[2] = order[2];
        rank[3] = order[3];
    }
    else {
        rank[2] = order[3];
        rank[3] = order[2];
    }
    if (fn_1_9D4(3) == 0) {
        rank[0] = order[0];
        rank[1] = order[1];
    }
    else {
        rank[0] = order[1];
        rank[1] = order[0];
    }
    winner = &lbl_1_bss_16818->player[lbl_1_bss_1681C->playerPos[rank[0]]];
    side = lbl_1_bss_16818->unk22C;
    lbl_1_bss_16818->unk22D = winner->charNo;
    if (lbl_1_bss_16818->streamNo >= 0) {
        HuAudSStreamFadeOut(lbl_1_bss_16818->streamNo, 1000);
        lbl_1_bss_16818->streamNo = -1;
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    fn_1_2CE8();
    camPos = lbl_1_data_28[side + 4];
    camTarget = lbl_1_data_28[side + 4];
    camTarget.y += 25.0f + (lbl_1_data_180[winner->charNo] + CharModelHeightGet(winner->charNo));
    camPos.z += 800;
    camPos.y = 300 + camTarget.y;
    Hu3DCameraViewportSet(HU3D_CAM4, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
    Hu3DCameraPosSetV(HU3D_CAM4, &camPos, &lbl_1_bss_1681C->camUp, &camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_1681C->camFov, 20, 60000, 1.2f);
    lbl_1_bss_16818->camPos = camPos;
    lbl_1_bss_16818->camTarget = camTarget;
    Hu3DModelAttrReset(winner->mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(winner->mdlId, HU3D_CAM4);
    Hu3DModelLayerSet(winner->mdlId, 4);
    Hu3DModelPosSet(winner->mdlId, winner->pos.x, winner->pos.y, winner->pos.z);
    lbl_1_bss_16818->guidePos = lbl_1_data_7C[4];
    Hu3DModelPosSetV(lbl_1_bss_16818->guideMdlId, &lbl_1_bss_16818->guidePos);
    if (side == 0) {
        Hu3DModelRotSet(lbl_1_bss_16818->guideMdlId, 0, -30, 0);
    }
    else {
        Hu3DModelRotSet(lbl_1_bss_16818->guideMdlId, 0, 30, 0);
    }
    reflectMdlId = lbl_1_bss_16818->stageMdlId[4];
    reflectPos = lbl_1_data_28[side + 4];
    reflectPos.y += 200;
    Hu3DModelCameraSet(reflectMdlId, HU3D_CAM4);
    Hu3DModelPosSetV(reflectMdlId, &reflectPos);
    fn_1_485C();
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    WipeWait();
    paperVec[0].x = lbl_1_data_28[side + 4].x - 400;
    paperVec[0].y = 430 + lbl_1_data_28[side + 4].y;
    paperVec[0].z = 80 + lbl_1_data_28[side + 4].z;
    paperVec[1].x = 400 + lbl_1_data_28[side + 4].x;
    paperVec[1].y = 430 + lbl_1_data_28[side + 4].y;
    paperVec[1].z = 80 + lbl_1_data_28[side + 4].z;
    fn_1_A6BC(paperVec);
    HuAudFXPlayPan(lbl_1_data_248[winner->charNo][2], 64);
    if (winner->mot != 2) {
        CharMotionShiftSet(winner->charNo, winner->motId[2], 0, 5, HU3D_MOTATTR_NONE);
        winner->mot = 2;
    }
    GameMesMgWinnerCreate(winner->charNo, -1, -1, -1);
    HuAudSStreamPlay(MSM_STREAM_JNGL_MGCIRCUIT_WIN);
    fn_1_40C(225);
    fn_1_DA4(fn_1_10288);
    while (!fn_1_88C(0x1000)) {
        HuPrcVSleep();
    }
    fn_1_750();
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
    WipeWait();
    fn_1_A910();
    fn_1_7C8(0x2000);
    Hu3DCameraViewportSet(HU3D_CAM4, 0, 0, 640, 480, 0, 1);
    Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_1681C->camPos, &lbl_1_bss_1681C->camUp, &lbl_1_bss_1681C->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_1681C->camFov, 20, 60000, 1.2f);
    lbl_1_bss_16818->camPos = lbl_1_bss_1681C->camPos;
    lbl_1_bss_16818->camTarget = lbl_1_bss_1681C->camTarget;
    fn_1_CB8C(rank);
    fn_1_D29C(1);
    fn_1_263C(HU3D_CAM4);
    Hu3DModelAttrSet(lbl_1_bss_16818->guideMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelCameraSet(lbl_1_bss_16818->stageMdlId[4], HU3D_CAM2);
    player = &lbl_1_bss_16818->player[lbl_1_bss_1681C->playerPos[rank[0]]];
    player->mot = -1;
    if (player->mot != 2) {
        CharMotionSet(player->charNo, player->motId[2]);
        player->mot = 2;
    }
    Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_LOOP);
    player = &lbl_1_bss_16818->player[lbl_1_bss_1681C->playerPos[rank[1]]];
    player->mot = -1;
    if (player->mot != 0) {
        CharMotionShiftSet(player->charNo, player->motId[0], 0, 0, HU3D_MOTATTR_LOOP);
        player->mot = 0;
    }
    player = &lbl_1_bss_16818->player[lbl_1_bss_1681C->playerPos[rank[2]]];
    player->mot = -1;
    if (player->mot != 3) {
        CharMotionSet(player->charNo, player->motId[3]);
        player->mot = 3;
    }
    Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_LOOP);
    player = &lbl_1_bss_16818->player[lbl_1_bss_1681C->playerPos[rank[3]]];
    player->mot = -1;
    if (player->mot != 3) {
        CharMotionSet(player->charNo, player->motId[3]);
        player->mot = 3;
    }
    Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_LOOP);
    HuPrcVSleep();
    HuPrcVSleep();
    HuPrcVSleep();
    HuPrcVSleep();
    HuPrcVSleep();
    HuPrcVSleep();
    fn_1_D820(0, lbl_1_bss_16818->player);
    lbl_1_bss_16818->streamNo = HuAudBGMPlay(MSM_STREAM_MGTOUR_END);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
    WipeWait();
    fn_1_DA4(fn_1_102E4);
    while (!fn_1_88C(0x2000)) {
        HuPrcVSleep();
    }
    if (fn_1_7E4(0x10)) {
        if (lbl_1_bss_16818->streamNo >= 0) {
            HuAudSStreamFadeOut(lbl_1_bss_16818->streamNo, 1000);
            lbl_1_bss_16818->streamNo = -1;
        }
        if (lbl_1_bss_16818->seNo >= 0) {
            HuAudFXStop(lbl_1_bss_16818->seNo);
            lbl_1_bss_16818->seNo = -1;
        }
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        WipeWait();
        fn_1_2078();
    }
    else {
        fn_1_D5C(3);
    }
}

/* 1 insns */
void fn_1_A5D8(void) { }

/* 26 insns */
void fn_1_A5DC(void)
{
    int time = 120;
    while (lbl_1_bss_16760.active) {
        if (--time == 0) {
            lbl_1_bss_16760.spawnF = 0;
        }
        fn_1_B318();
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 30 insns */
float fn_1_A644(void)
{
    s32 rnd = frandmod(201) - 100;
    float value = rnd;
    value /= 100.0f;
    return value;
}

/* 0x35C */ HuVecF lbl_1_data_35C[4] = { { 255.0f, 191.25f, 204.0f }, { 255.0f, 255.0f, 153.0f }, { 178.5f, 255.0f, 255.0f }, { 153.0f, 255.0f, 191.25f } };
/* 0x38C */ HuVecF lbl_1_data_38C[4] = { { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f } };

/* 149 insns */
void fn_1_A6BC(HuVecF *vec)
{
    memset(&lbl_1_bss_16760, 0, sizeof(lbl_1_bss_16760));
    lbl_1_bss_16760.active = 1;
    lbl_1_bss_16760.num = 0;
    lbl_1_bss_16760.spawnF = 1;
    lbl_1_bss_16760.unk20 = 1.0f;
    lbl_1_bss_16760.mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 10), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_16760.mdlId[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 11), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_16760.mdlId[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 12), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_16760.mdlId[3] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_mgtour, 13), HU_MEMNUM_OVL, HEAP_MODEL));
    sprintf(lbl_1_bss_16760.name[0], "%s", "m546-kami01");
    sprintf(lbl_1_bss_16760.name[1], "%s", "m546-kami02");
    sprintf(lbl_1_bss_16760.name[2], "%s", "m546-kami03");
    sprintf(lbl_1_bss_16760.name[3], "%s", "m546-kami04");
    lbl_1_bss_16760.pos[0] = vec[0];
    lbl_1_bss_16760.pos[1] = vec[1];
    lbl_1_bss_16760.unk24 = 10;
    lbl_1_bss_16760.unk26 = 1;
    lbl_1_bss_16760.hookMdlId = Hu3DHookFuncCreate(fn_1_B678);
    Hu3DModelCameraSet(lbl_1_bss_16760.hookMdlId, HU3D_CAM4);
    Hu3DModelLayerSet(lbl_1_bss_16760.hookMdlId, 6);
    HuPrcChildCreate(fn_1_A5DC, 100, 4096, 0, HuPrcCurrentGet());
}

/* 15 insns */
void fn_1_A910(void)
{
    lbl_1_bss_16760.active = 0;
    Hu3DModelKill(lbl_1_bss_16760.hookMdlId);
}

/* 627 insns */
void fn_1_A94C(void)
{
    s16 i;
    float angle;
    s16 color;

    for (i = 0; i < 1000; i++) {
        if (lbl_1_bss_0[i].active != 0) {
            continue;
        }
        lbl_1_bss_0[i].active = 1;
        lbl_1_bss_0[i].unk4 = 136 + frandmod(30);
        lbl_1_bss_16760.unk20 += 0.001f;
        lbl_1_bss_0[i].unk3C = lbl_1_bss_16760.unk20;
        lbl_1_bss_0[i].unk8 = 1;
        angle = 360.0f * fn_1_A644();
        lbl_1_bss_0[i].pos.x = lbl_1_bss_16760.pos[lbl_1_bss_16760.num].x + 25.0 * sin(M_PI * angle / 180.0);
        lbl_1_bss_0[i].pos.y = lbl_1_bss_16760.pos[lbl_1_bss_16760.num].y;
        lbl_1_bss_0[i].pos.z = lbl_1_bss_16760.pos[lbl_1_bss_16760.num].z + 25.0 * cos(M_PI * angle / 180.0);
        lbl_1_bss_0[i].unk24.x = 0.0f;
        lbl_1_bss_0[i].unk24.y = 0.0f;
        lbl_1_bss_0[i].unk24.z = 0.0f;
        if (lbl_1_bss_16760.num != 0) {
            lbl_1_bss_0[i].unk18.x = 3.0f * (fn_1_A644() - 4.0f);
        } else {
            lbl_1_bss_0[i].unk18.x = 3.0f * (4.0f + fn_1_A644());
        }
        lbl_1_bss_0[i].unk18.y = -1.0f * (6.5f * fn_1_A644());
        if (lbl_1_bss_0[i].unk18.y > 0.0f) {
            lbl_1_bss_0[i].unk18.y *= -1.0f;
        }
        if (lbl_1_bss_0[i].unk18.y > -6.5f * 0.4f) {
            lbl_1_bss_0[i].unk18.y = -6.5f * 0.4f;
        }
        lbl_1_bss_0[i].unk18.z = 0.4f * fn_1_A644();
        lbl_1_bss_0[i].unk30.x = 14.0f * fn_1_A644();
        lbl_1_bss_0[i].unk30.y = 14.0f * fn_1_A644();
        lbl_1_bss_0[i].unk30.z = 14.0f * fn_1_A644();
        color = frandmod(4);
        lbl_1_bss_0[i].unk6 = color;
        lbl_1_bss_0[i].unk44[0] = lbl_1_data_35C[color].x;
        lbl_1_bss_0[i].unk44[1] = lbl_1_data_35C[color].y;
        lbl_1_bss_0[i].unk44[2] = lbl_1_data_35C[color].z;
        color = frandmod(4);
        lbl_1_bss_0[i].unk44[3] = lbl_1_data_38C[color].x;
        lbl_1_bss_0[i].unk44[4] = lbl_1_data_38C[color].y;
        lbl_1_bss_0[i].unk44[5] = lbl_1_data_38C[color].z;
        lbl_1_bss_0[i].unk40 = 1.0f;
        lbl_1_bss_16760.unk2A++;
        lbl_1_bss_16760.num = !lbl_1_bss_16760.num;
        if (lbl_1_bss_16760.unk28++ >= lbl_1_bss_16760.unk26) {
            break;
        }
    }
}

/* 216 insns */
void fn_1_B318(void)
{
    s16 i;
    float x;
    float z;

    if (lbl_1_bss_16760.active == 0) {
        return;
    }
    for (i = 0; i < 1000; i++) {
        if (lbl_1_bss_0[i].active == 0) {
            continue;
        }
        if (lbl_1_bss_0[i].unk8 != 0) {
            lbl_1_bss_0[i].pos.x += lbl_1_bss_0[i].unk18.x;
            lbl_1_bss_0[i].pos.y += lbl_1_bss_0[i].unk18.y;
            lbl_1_bss_0[i].pos.z += lbl_1_bss_0[i].unk18.z;
            lbl_1_bss_0[i].unk24.x += lbl_1_bss_0[i].unk30.x;
            lbl_1_bss_0[i].unk24.y += lbl_1_bss_0[i].unk30.y;
            lbl_1_bss_0[i].unk24.z += lbl_1_bss_0[i].unk30.z;
            if (fabsf(lbl_1_bss_0[i].unk18.x) > 0.001) {
                lbl_1_bss_0[i].unk18.x -= lbl_1_bss_0[i].unk18.x / 40.0f;
            }
        }
        x = lbl_1_bss_0[i].pos.x;
        z = lbl_1_bss_0[i].pos.z;
    }
    if (lbl_1_bss_16760.spawnF != 0) {
        if (lbl_1_bss_16760.unk24-- <= 0 && lbl_1_bss_16760.unk2A < 1000) {
            lbl_1_bss_16760.unk24 = frandmod(2) + 1;
            lbl_1_bss_16760.unk26 = 1;
            lbl_1_bss_16760.unk28 = 0;
            fn_1_A94C();
        }
    }
}

/* 147 insns */
void fn_1_B678(HU3DMODEL *model, Mtx *mtx)
{
    Mtx drawMtx;
    Mtx work;
    s16 i;

    if (lbl_1_bss_16760.active == 0) {
        return;
    }
    Hu3DModelObjDrawInit();
    for (i = 0; i < 1000; i++) {
        if (lbl_1_bss_0[i].active == 0) {
            continue;
        }
        MTXRotRad(work, 'z', MTXDegToRad(lbl_1_bss_0[i].unk24.z));
        MTXRotRad(drawMtx, 'x', MTXDegToRad(lbl_1_bss_0[i].unk24.x));
        MTXConcat(work, drawMtx, drawMtx);
        MTXRotRad(work, 'y', MTXDegToRad(lbl_1_bss_0[i].unk24.y));
        MTXConcat(work, drawMtx, drawMtx);
        MTXTrans(work, lbl_1_bss_0[i].pos.x, lbl_1_bss_0[i].pos.y, lbl_1_bss_0[i].pos.z);
        MTXConcat(work, drawMtx, drawMtx);
        MTXConcat(*mtx, drawMtx, drawMtx);
        Hu3DModelTPLvlSet(lbl_1_bss_16760.mdlId[lbl_1_bss_0[i].unk6], lbl_1_bss_0[i].unk40);
        Hu3DModelObjDraw(lbl_1_bss_16760.mdlId[lbl_1_bss_0[i].unk6], lbl_1_bss_16760.name[lbl_1_bss_0[i].unk6], drawMtx);
    }
}

