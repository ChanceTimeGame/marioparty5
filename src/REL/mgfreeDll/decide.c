/*
 * mgfreeDll decide.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgfreeDll/asm/REL/mgfreeDll/decide.s.
 */

#include "REL/mgfreeDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/thpmain.h"
#include "math.h"

/* decide.c lbl_1_data_330: window layout records (0x18) */
typedef struct MgFreeWinData_s {
    float x;
    float y;
    float w;
    float h;
    s32 pri;
    s32 attr;
} MGFREE_WINDATA;

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_F8 = 0.0f; /* 0xF8 */
static const float lbl_1_rodata_FC = 1.0f; /* 0xFC */
static const float lbl_1_rodata_100 = 0.9f; /* 0x100 */
static const float lbl_1_rodata_104 = 10.0f; /* 0x104 */
static const double lbl_1_rodata_108 = 3.141592653589793; /* 0x108 */
static const double lbl_1_rodata_110 = 0.5; /* 0x110 */
static const double lbl_1_rodata_118 = 0.1; /* 0x118 */
static const double lbl_1_rodata_120 = 0.9; /* 0x120 */
/* 0x128 lbl_1_rodata_128 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_130 = 33.0f; /* 0x130 */
static const float lbl_1_rodata_134 = 0.7f; /* 0x134 */
/* 0x138 lbl_1_rodata_138 (0x20): 0x0097000F 0x00970010 0x00970011 0x00970012 0x00970013 0x00970014 0x00970015 0x00970016 -- an aggregate initialiser, write it as a local */
/* 0x158 lbl_1_rodata_158 (0x10): 0x00970028 0x00970029 0x00970027 0x00970026 -- an aggregate initialiser, write it as a local */
/* 0x168 lbl_1_rodata_168 (0x10): 0x0097002C 0x0097002D 0x0097002B 0x0097002A -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_178 = 0.5f; /* 0x178 */
static const float lbl_1_rodata_17C = 60.0f; /* 0x17C */
static const float lbl_1_rodata_180 = 20.0f; /* 0x180 */
static const float lbl_1_rodata_184 = 0.125f; /* 0x184 */
static const float lbl_1_rodata_188 = 2.0f; /* 0x188 */
static const float lbl_1_rodata_18C = 0.2f; /* 0x18C */
static const float lbl_1_rodata_190 = 16.0f; /* 0x190 */
static const float lbl_1_rodata_194 = 0.3f; /* 0x194 */
static const float lbl_1_rodata_198 = 0.8f; /* 0x198 */
/* 0x19C lbl_1_rodata_19C (0x28): 0x00000012 0x00000011 0x00000001 0x00000002 0x00000003 0x00000004 0x00000005 0x00000006 0x00000007 0x00000008 -- an aggregate initialiser, write it as a local */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x978 */ MGFREE_DECIDE_WORK lbl_1_bss_978;
/* 0x974 */ MGFREE_DECIDE_WORK *lbl_1_bss_974;
/* 0x966 */ char lbl_1_bss_966[0xE]; /* two sprintf targets at +0 and +6 (fn_1_91A8); size 0xE is the reference symbol's */
/* 0x948 */ char lbl_1_bss_948[3][10]; /* sprintf targets (fn_1_6BC4: +0, +0xA, +0x14) */

/* --- functions (reference order), .data placed before its first user --- */
/* 0x330 */ MGFREE_WINDATA lbl_1_data_330[26] = { /* window x, y, w, h, pri, attr (mulli 0x18) */
    { 342.0f, 191.0f, 120.0f, 32.0f, 150, 0x800 },
    { 150.0f, 255.0f, 260.0f, 32.0f, 150, 0x0 },
    { 416.0f, 255.0f, 260.0f, 32.0f, 150, 0x0 },
    { 150.0f, 287.0f, 260.0f, 32.0f, 150, 0x0 },
    { 416.0f, 287.0f, 260.0f, 32.0f, 150, 0x0 },
    { 150.0f, 319.0f, 260.0f, 32.0f, 150, 0x0 },
    { 416.0f, 319.0f, 260.0f, 32.0f, 150, 0x0 },
    { 150.0f, 351.0f, 260.0f, 32.0f, 150, 0x0 },
    { 416.0f, 351.0f, 260.0f, 32.0f, 150, 0x0 },
    { 150.0f, 255.0f, 260.0f, 32.0f, 190, 0x0 },
    { 416.0f, 255.0f, 260.0f, 32.0f, 190, 0x0 },
    { 150.0f, 287.0f, 260.0f, 32.0f, 190, 0x0 },
    { 416.0f, 287.0f, 260.0f, 32.0f, 190, 0x0 },
    { 150.0f, 319.0f, 260.0f, 32.0f, 190, 0x0 },
    { 416.0f, 319.0f, 260.0f, 32.0f, 190, 0x0 },
    { 150.0f, 351.0f, 260.0f, 32.0f, 190, 0x0 },
    { 416.0f, 351.0f, 260.0f, 32.0f, 190, 0x0 },
    { 470.0f, 397.0f, 200.0f, 32.0f, 190, 0x0 },
    { 288.0f, 420.0f, 500.0f, 35.0f, 150, 0x800 },
    { 288.0f, 314.0f, 460.0f, 40.0f, 110, 0x800 },
    { 288.0f, 140.0f, 300.0f, 32.0f, 90, 0x800 },
    { 288.0f, 240.0f, 300.0f, 32.0f, 90, 0x800 },
    { 288.0f, 340.0f, 300.0f, 32.0f, 90, 0x800 },
    { 288.0f, 145.0f, 300.0f, 64.0f, 90, 0x800 },
    { 288.0f, 245.0f, 300.0f, 64.0f, 90, 0x800 },
    { 288.0f, 345.0f, 300.0f, 64.0f, 90, 0x800 }
};
/* 0x5A0 */ u32 lbl_1_data_5A0[10] = { DATANUM(DATA_mgfree, 46), DATANUM(DATA_mgfree, 47), DATANUM(DATA_mgfree, 48), DATANUM(DATA_mgfree, 49), DATANUM(DATA_mgfree, 50), DATANUM(DATA_mgfree, 51), DATANUM(DATA_mgfree, 52), DATANUM(DATA_mgfree, 53), DATANUM(DATA_mgfree, 54), DATANUM(DATA_mgfree, 55) };

/* 203 insns */
void fn_1_46DC(s32 playerNo, s32 grpId, s32 memberNo, s32 arg3, s32 prio, s32 arg5)
{
    s32 comTbl[4];
    s32 padTbl[4];
    ANIMDATA *anim;

    anim = HuSprAnimDataRead(lbl_1_data_5A0[GwPlayerConf[playerNo].charNo]);
    HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, prio, 0));
    switch (GwCommon.languageNo) {
        case 0:
            comTbl[0] = DATANUM(DATA_mgfree, 29);
            comTbl[1] = DATANUM(DATA_mgfree, 30);
            comTbl[2] = DATANUM(DATA_mgfree, 31);
            comTbl[3] = DATANUM(DATA_mgfree, 32);
            padTbl[0] = DATANUM(DATA_mgfree, 33);
            padTbl[1] = DATANUM(DATA_mgfree, 34);
            padTbl[2] = DATANUM(DATA_mgfree, 35);
            padTbl[3] = DATANUM(DATA_mgfree, 36);
            break;
        case 1:
            comTbl[0] = DATANUM(DATA_mgfree, 58);
            comTbl[1] = DATANUM(DATA_mgfree, 59);
            comTbl[2] = DATANUM(DATA_mgfree, 60);
            comTbl[3] = DATANUM(DATA_mgfree, 61);
            padTbl[0] = DATANUM(DATA_mgfree, 62);
            padTbl[1] = DATANUM(DATA_mgfree, 63);
            padTbl[2] = DATANUM(DATA_mgfree, 64);
            padTbl[3] = DATANUM(DATA_mgfree, 65);
            break;
    }
    if (GwPlayerConf[playerNo].type != 0) {
        switch (GwPlayerConf[playerNo].dif) {
            case 0:
                anim = HuSprAnimDataRead(comTbl[0]);
                break;
            case 1:
                anim = HuSprAnimDataRead(comTbl[1]);
                break;
            case 2:
                anim = HuSprAnimDataRead(comTbl[2]);
                break;
            case 3:
                anim = HuSprAnimDataRead(comTbl[3]);
                break;
        }
        HuSprGrpMemberSet(grpId, arg3, HuSprCreate(anim, arg5, 0));
    } else {
        switch (playerNo) {
            case 0:
                anim = HuSprAnimDataRead(padTbl[0]);
                break;
            case 1:
                anim = HuSprAnimDataRead(padTbl[1]);
                break;
            case 2:
                anim = HuSprAnimDataRead(padTbl[2]);
                break;
            case 3:
                anim = HuSprAnimDataRead(padTbl[3]);
                break;
        }
        HuSprGrpMemberSet(grpId, arg3, HuSprCreate(anim, arg5, 0));
    }
}

/* 0x5C8 */ HuVec2f lbl_1_data_5C8[4] = { { -35.0f, -41.0f }, { 35.0f, -41.0f }, { -35.0f, 41.0f }, { 35.0f, 41.0f } };
/* 0x5E8 */ HuVec2f lbl_1_data_5E8[2] = { { 288.0f, 255.0f }, { 288.0f, 840.0f } };
/* 0x5F8 */ HuVec2f lbl_1_data_5F8[2] = { { 100.0f, 125.0f }, { -300.0f, 125.0f } };
/* 0x608 */ HuVec2f lbl_1_data_608[2] = { { 288.0f, 240.0f }, { 288.0f, 2000.0f } };
/* 0x618 */ HuVec2f lbl_1_data_618[2] = { { 288.0f, 240.0f }, { 288.0f, 2000.0f } };
/* 0x628 */ HuVec2f lbl_1_data_628[2] = { { 288.0f, 240.0f }, { 288.0f, 2000.0f } };
/* 0x638 */ HuVec2f lbl_1_data_638[2] = { { 0.0f, -7.0f }, { 0.0f, 151.0f } };
/* 0x648 */ HuVec2f lbl_1_data_648[8] = { { -135.0f, 5.0f }, { 132.0f, 5.0f }, { -135.0f, 37.0f }, { 132.0f, 37.0f }, { -135.0f, 69.0f }, { 132.0f, 69.0f }, { -135.0f, 101.0f }, { 132.0f, 101.0f } };


/* the 10-frame waits in fn_1_A570: their counters are allocated after every declared local of
 * fn_1_A570 (after fn_1_4A08's inlined one), so they are an inlined function's parameter */
static inline void fn_1_A570_Wait(s32 time)
{
    while (time-- != 0) {
        HuPrcVSleep();
    }
}


/* 198 insns */
/* GUESS: mgfree.c's fn_1_46AC body, inlined here in the reference (a cross-unit inline cannot be,
 * so decide.c carries its own copy; CW emits nothing for an unreferenced static inline) */
static inline u32 fn_1_46AC_inline(s32 listNo)
{
    return mgDataTbl[lbl_1_bss_974->list[listNo].mgIdx].nameMes;
}

void fn_1_4A08(void)
{
    s32 n;
    s32 i;

    n = lbl_1_bss_974->listNum - lbl_1_bss_974->unk104;
    HuSprPosSet(lbl_1_bss_974->grp70, 8, lbl_1_data_648[lbl_1_bss_974->unk106].x, lbl_1_data_648[lbl_1_bss_974->unk106].y);
    if (n <= 8) {
        i = n;
        while (i-- != 0) {
            HuWinDispOn(lbl_1_bss_974->winId[i + 1]);
            if (lbl_1_bss_974->list[lbl_1_bss_974->unk104 + i].unk2 != 0) {
                HuWinMesSet(lbl_1_bss_974->winId[i + 1], fn_1_46AC_inline(lbl_1_bss_974->unk104 + i));
            } else {
                HuWinMesSet(lbl_1_bss_974->winId[i + 1], 0x1F004F);
            }
        }
        for (i = 7; i >= n; i--) {
            HuWinDispOff(lbl_1_bss_974->winId[i + 1]);
        }
    } else {
        i = 8;
        while (i-- != 0) {
            HuWinDispOn(lbl_1_bss_974->winId[i + 1]);
            if (lbl_1_bss_974->list[lbl_1_bss_974->unk104 + i].unk2 != 0) {
                HuWinMesSet(lbl_1_bss_974->winId[i + 1], fn_1_46AC_inline(lbl_1_bss_974->unk104 + i));
            } else {
                HuWinMesSet(lbl_1_bss_974->winId[i + 1], 0x1F004F);
            }
        }
    }
}

/* 11 insns */
void fn_1_4D20(s32 mode)
{
    lbl_1_bss_974->unk0 = mode;
    lbl_1_bss_974->unk2 = 0;
}

/* 5 insns */
s8 fn_1_4D4C(void)
{
    return lbl_1_bss_974->unk107;
}

/* 7 insns */
s32 fn_1_4D60(s32 playerNo)
{
    return lbl_1_bss_974->unk149[playerNo];
}

/* 183 insns */
void fn_1_4D7C(void)
{
    s32 i;
    float scale;

    i = 3;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp7C, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp7C, i + 3, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp7C, i, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp7C, i + 3, 0.9f, 0.9f);
        if (i == lbl_1_bss_974->unk107) {
            HuWinMesPalSet(lbl_1_bss_974->winId[i + 20], 7, 255, 255, 255);
        } else {
            HuWinMesPalSet(lbl_1_bss_974->winId[i + 20], 7, 160, 160, 160);
        }
    }
    fn_1_15B8();
    HuSprTPLvlSet(lbl_1_bss_974->grp7C, (s32)lbl_1_bss_974->unk107, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp7C, lbl_1_bss_974->unk107 + 3, 0.0f);
    for (i = 0; i <= 10; i++) {
        scale = i / 10.0f;
        scale = sin(M_PI * scale / 2.0);
        scale *= 0.1;
        scale += 0.9;
        HuSprScaleSet(lbl_1_bss_974->grp7C, (s32)lbl_1_bss_974->unk107, scale, scale);
        HuPrcVSleep();
    }
}

/* 182 insns */
void fn_1_5058(void)
{
    s32 i;
    float scale;

    i = 3;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp80, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp80, i + 3, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp80, i, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp80, i + 3, 0.9f, 0.9f);
        if (i == lbl_1_bss_974->unk107) {
            HuWinMesPalSet(lbl_1_bss_974->winId[i + 23], 7, 255, 255, 255);
        } else {
            HuWinMesPalSet(lbl_1_bss_974->winId[i + 23], 7, 160, 160, 160);
        }
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp80, (s32)lbl_1_bss_974->unk107, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp80, lbl_1_bss_974->unk107 + 3, 0.0f);
    for (i = 0; i <= 10; i++) {
        scale = i / 10.0f;
        scale = sin(M_PI * scale / 2.0);
        scale *= 0.1;
        scale += 0.9;
        HuSprScaleSet(lbl_1_bss_974->grp80, (s32)lbl_1_bss_974->unk107, scale, scale);
        HuPrcVSleep();
    }
}

/* 0x688 */ HuVec2f lbl_1_data_688[8] = { { -190.0f, 10.0f }, { 190.0f, 10.0f }, { -190.0f, 10.0f }, { 190.0f, 10.0f }, { -140.0f, 10.0f }, { 140.0f, 10.0f }, { 55.0f, 43.0f }, { 145.0f, 43.0f } };
/* 0x6C8 */ HuVec2f lbl_1_data_6C8[16] = { { -132.0f, 10.0f }, { -62.0f, 10.0f }, { 62.0f, 10.0f }, { 132.0f, 10.0f }, { -132.0f, 10.0f }, { -8.0f, 10.0f }, { 62.0f, 10.0f }, { 132.0f, 10.0f }, { -80.0f, 10.0f }, { 80.0f, 10.0f }, { 0.0f, 10.0f }, { 0.0f, 10.0f }, { -100.0f, 10.0f }, { 100.0f, 10.0f }, { 0.0f, 10.0f }, { 0.0f, 10.0f } };
/* 0x748 */ HuVec2f lbl_1_data_748[4] = { { 0.0f, 10.0f }, { -70.0f, 10.0f }, { 0.0f, 10.0f }, { 0.0f, 10.0f } };
/* 0x768 */ HuVec2f lbl_1_data_768[3] = { { 0.0f, -90.0f }, { 0.0f, 10.0f }, { 0.0f, 110.0f } };
/* 0x780 */ s32 lbl_1_data_780[13][4] = { /* player orders (stride 0x10) */
    { 0, 1, 2, 3 },
    { 1, 0, 2, 3 },
    { 2, 0, 1, 3 },
    { 3, 0, 1, 2 },
    { 0, 1, 2, 3 },
    { 0, 2, 1, 3 },
    { 0, 3, 1, 2 },
    { 0, 1, 2, 3 },
    { 0, 2, 1, 3 },
    { 0, 3, 1, 2 },
    { 1, 2, 0, 3 },
    { 1, 3, 0, 2 },
    { 2, 3, 0, 1 }
};

/* 220 insns */
void fn_1_5330(void)
{
    s32 i;

    OSReport("519 Decide\n");
    i = 3;
    while (i-- != 0) {
        HuWinDispOn(lbl_1_bss_974->winId[i + 20]);
    }
    lbl_1_bss_974->unk107 = 0;
    HuSprGrpPosSet(lbl_1_bss_974->grp7C, lbl_1_data_628[0].x, lbl_1_data_628[0].y);
    fn_1_4D7C();
}

/* 219 insns */
void fn_1_56A0(void)
{
    s32 i;

    OSReport("552 Decide\n");
    i = 3;
    while (i-- != 0) {
        HuWinDispOn(lbl_1_bss_974->winId[i + 23]);
    }
    lbl_1_bss_974->unk107 = 0;
    HuSprGrpPosSet(lbl_1_bss_974->grp80, lbl_1_data_628[0].x, lbl_1_data_628[0].y);
    fn_1_5058();
}

/* 254 insns */
void fn_1_5A0C(void)
{
    HuVec2f ofs;
    HuVec2f *pos;
    HuVec2f *pos2;
    s32 i;

    OSReport("2 vs 2 Decide\n");
    pos = lbl_1_data_6C8;
    pos2 = lbl_1_data_688;
    ofs = lbl_1_data_748[0];
    lbl_1_bss_974->unk148 = 0;
    i = 4;
    while (i-- != 0) {
        lbl_1_bss_974->unk149[i] = i;
    }
    HuSprAttrReset(lbl_1_bss_974->grp74, 1, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 1, ofs.x, ofs.y);
    i = 2;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i + 2, 1.0f);
        HuSprPosSet(lbl_1_bss_974->grp78, i + 2, pos2[i].x, pos2[i].y);
        lbl_1_bss_974->pos128[i + 2] = pos2[i];
        HuSprScaleSet(lbl_1_bss_974->grp78, i, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 2, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 4, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 6, 1.0f, 1.0f);
    }
    HuSprAttrSet(lbl_1_bss_974->grp74, 6, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 11, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 7, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 2, pos[i].x, pos[i].y);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 7, pos[i].x, 33.0f + pos[i].y);
    }
    HuSprGrpPosSet(lbl_1_bss_974->grp74, lbl_1_data_608[0].x, lbl_1_data_608[0].y);
}

/* 256 insns */
void fn_1_5E04(void)
{
    HuVec2f ofs;
    HuVec2f *pos;
    HuVec2f *pos2;
    s32 i;

    OSReport("1 vs 3 Decide\n");
    pos = &lbl_1_data_6C8[4];
    pos2 = &lbl_1_data_688[2];
    ofs = lbl_1_data_748[1];
    lbl_1_bss_974->unk148 = 0;
    i = 4;
    while (i-- != 0) {
        lbl_1_bss_974->unk149[i] = i;
    }
    HuSprAttrReset(lbl_1_bss_974->grp74, 1, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 1, ofs.x, ofs.y);
    i = 2;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i + 2, 1.0f);
        HuSprPosSet(lbl_1_bss_974->grp78, i + 2, pos2[i].x, pos2[i].y);
        lbl_1_bss_974->pos128[i + 2] = pos2[i];
        HuSprScaleSet(lbl_1_bss_974->grp78, i, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 2, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 4, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 6, 1.0f, 1.0f);
    }
    HuSprAttrSet(lbl_1_bss_974->grp74, 6, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 11, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 7, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 2, pos[i].x, pos[i].y);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 7, pos[i].x, 33.0f + pos[i].y);
    }
    HuSprGrpPosSet(lbl_1_bss_974->grp74, lbl_1_data_608[0].x, lbl_1_data_608[0].y);
}

/* 279 insns */
void fn_1_6204(void)
{
    HuVec2f ofs;
    HuVec2f *pos;
    HuVec2f *pos2;
    s32 i;

    OSReport("Duel Decide\n");
    pos = &lbl_1_data_6C8[8];
    pos2 = &lbl_1_data_688[4];
    ofs = lbl_1_data_748[2];
    lbl_1_bss_974->unk148 = 0;
    i = 4;
    while (i-- != 0) {
        lbl_1_bss_974->unk149[i] = i;
    }
    HuSprAttrReset(lbl_1_bss_974->grp74, 1, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 1, ofs.x, ofs.y);
    i = 2;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i + 2, 1.0f);
        HuSprPosSet(lbl_1_bss_974->grp78, i + 2, pos2[i].x, pos2[i].y);
        lbl_1_bss_974->pos128[i + 2] = pos2[i];
        HuSprScaleSet(lbl_1_bss_974->grp78, i, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 2, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 4, 1.0f, 1.0f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 6, 1.0f, 1.0f);
    }
    HuSprAttrSet(lbl_1_bss_974->grp74, 6, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 11, HUSPR_ATTR_DISPOFF);
    }
    for (i = 0; i < 2; i++) {
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrReset(lbl_1_bss_974->grp74, i + 7, HUSPR_ATTR_DISPOFF);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 2, pos[i].x, pos[i].y);
        HuSprPosSet(lbl_1_bss_974->grp74, i + 7, pos[i].x, 33.0f + pos[i].y);
    }
    for (i = 2; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 7, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(lbl_1_bss_974->grp74, lbl_1_data_608[0].x, lbl_1_data_608[0].y);
}

/* 328 insns */
void fn_1_6660(void)
{
    HuVec2f ofs;
    HuVec2f *pos;
    HuVec2f *pos2;
    s32 i;

    OSReport("Story Decide\n");
    pos = &lbl_1_data_6C8[12];
    pos2 = &lbl_1_data_688[6];
    ofs = lbl_1_data_748[3];
    lbl_1_bss_974->unk107 = 1;
    HuSprAttrReset(lbl_1_bss_974->grp74, 1, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 1, ofs.x, ofs.y);
    i = 2;
    while (i-- != 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp78, i + 2, 1.0f);
        HuSprPosSet(lbl_1_bss_974->grp78, i + 2, pos2[i].x, pos2[i].y);
        lbl_1_bss_974->pos128[i + 2] = pos2[i];
        HuSprScaleSet(lbl_1_bss_974->grp78, i, 0.7f, 0.7f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 2, 0.7f, 0.7f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 4, 0.7f, 0.7f);
        HuSprScaleSet(lbl_1_bss_974->grp78, i + 6, 0.7f, 0.7f);
    }
    HuSprAttrReset(lbl_1_bss_974->grp74, 2, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(lbl_1_bss_974->grp74, 7, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 2, pos[0].x, pos[0].y);
    HuSprPosSet(lbl_1_bss_974->grp74, 7, pos[0].x, 33.0f + pos[0].y);
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 11, HUSPR_ATTR_DISPOFF);
    }
    HuSprAttrReset(lbl_1_bss_974->grp74, 6, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(lbl_1_bss_974->grp74, lbl_1_bss_974->unk107 + 11, HUSPR_ATTR_DISPOFF);
    HuSprPosSet(lbl_1_bss_974->grp74, 6, pos[1].x, pos[1].y);
    HuSprPosSet(lbl_1_bss_974->grp74, 11, pos[1].x, 33.0f + pos[1].y);
    HuSprPosSet(lbl_1_bss_974->grp74, 12, pos[1].x, 33.0f + pos[1].y);
    HuSprPosSet(lbl_1_bss_974->grp74, 13, pos[1].x, 33.0f + pos[1].y);
    HuSprPosSet(lbl_1_bss_974->grp74, 14, pos[1].x, 33.0f + pos[1].y);
    for (i = 1; i < 4; i++) {
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 2, HUSPR_ATTR_DISPOFF);
        HuSprAttrSet(lbl_1_bss_974->grp74, i + 7, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(lbl_1_bss_974->grp74, lbl_1_data_608[0].x, lbl_1_data_608[0].y);
}

/* 17 insns */
void fn_1_6B80(s32 *cursor, s32 *unk8, s32 *unkC)
{
    *cursor = lbl_1_bss_974->cursor;
    *unk8 = lbl_1_bss_974->unk106;
    *unkC = lbl_1_bss_974->unk104;
}

/* 1271 insns */
void fn_1_6BC4(s32 mode, s32 cursor, s32 unk8, s32 unkC)
{
    s32 i;
    s32 grpId;
    s32 memberNo;
    ANIMDATA *anim;
    s32 winId;

    lbl_1_bss_974 = &lbl_1_bss_978;
    lbl_1_bss_974->unk0 = 0;
    lbl_1_bss_974->unk2 = 0;
    lbl_1_bss_974->cursor = cursor;
    lbl_1_bss_974->unk102 = 0;
    lbl_1_bss_974->unk106 = unk8;
    lbl_1_bss_974->unk104 = unkC;
    lbl_1_bss_974->unk107 = 0;
    lbl_1_bss_974->listNum = 0;
    lbl_1_bss_974->unk148 = 0;
    for (i = 0; i < 26; i++) {
        winId = HuWinExCreateFrame(lbl_1_data_330[i].x - lbl_1_data_330[i].w / 2, lbl_1_data_330[i].y - lbl_1_data_330[i].h / 2,
            lbl_1_data_330[i].w, lbl_1_data_330[i].h, -1, 0);
        lbl_1_bss_974->winId[i] = winId;
        HuWinMesSpeedSet(winId, 0);
        HuWinBGTPLvlSet(winId, 0.0f);
        HuWinPriSet(winId, lbl_1_data_330[i].pri);
        if (lbl_1_data_330[i].attr != 0) {
            HuWinAttrSet(winId, lbl_1_data_330[i].attr);
        }
        HuWinDispOff(winId);
    }
    HuWinCenterPosSet(lbl_1_bss_974->winId[0], lbl_1_data_330[0].w / 2, lbl_1_data_330[0].h / 2);
    HuWinCenterPosSet(lbl_1_bss_974->winId[17], 0.0f, lbl_1_data_330[17].h / 2);
    HuWinMesSet(lbl_1_bss_974->winId[18], 0x20022);
    HuWinMesSet(lbl_1_bss_974->winId[19], 0x20022);
    HuWinMesSet(lbl_1_bss_974->winId[20], 0xE0002);
    HuWinMesSet(lbl_1_bss_974->winId[21], 0xE0001);
    HuWinMesSet(lbl_1_bss_974->winId[22], 0xE0003);
    HuWinMesSet(lbl_1_bss_974->winId[23], 0xE0004);
    HuWinMesSet(lbl_1_bss_974->winId[24], 0xE0005);
    HuWinMesSet(lbl_1_bss_974->winId[25], 0xE0006);
    sprintf(lbl_1_bss_948[0], "%5d", GwCommon.mgRecord[8]);
    sprintf(lbl_1_bss_948[1], "%5d", GwCommon.mgRecord[10]);
    sprintf(lbl_1_bss_948[2], "%5d", GwCommon.mgRecord[11]);
    HuWinInsertMesSet(lbl_1_bss_974->winId[23], MESSNUM_PTR(lbl_1_bss_948[0]), 0);
    HuWinInsertMesSet(lbl_1_bss_974->winId[24], MESSNUM_PTR(lbl_1_bss_948[1]), 1);
    HuWinInsertMesSet(lbl_1_bss_974->winId[25], MESSNUM_PTR(lbl_1_bss_948[2]), 2);
    HuWinDispOn(lbl_1_bss_974->winId[18]);

    grpId = HuSprGrpCreate(8);
    lbl_1_bss_974->grp6C = grpId;
    for (i = 0; i < 4; i++) {
        fn_1_46DC(i, grpId, i, i + 4, 400, 390);
        HuSprPosSet(grpId, i, lbl_1_data_5C8[i].x, lbl_1_data_5C8[i].y);
        HuSprPosSet(grpId, i + 4, lbl_1_data_5C8[i].x, 33.0f + lbl_1_data_5C8[i].y);
    }
    if (mode) {
        HuSprGrpPosSet(grpId, lbl_1_data_5F8[1].x, lbl_1_data_5F8[1].y);
    } else {
        HuSprGrpPosSet(grpId, lbl_1_data_5F8[0].x, lbl_1_data_5F8[0].y);
    }

    {
    s32 tbl138[8] = { DATANUM(DATA_mgfree, 15), DATANUM(DATA_mgfree, 16), DATANUM(DATA_mgfree, 17), DATANUM(DATA_mgfree, 18),
        DATANUM(DATA_mgfree, 19), DATANUM(DATA_mgfree, 20), DATANUM(DATA_mgfree, 21), DATANUM(DATA_mgfree, 22) };
    grpId = HuSprGrpCreate(9);
    lbl_1_bss_974->grp70 = grpId;
    for (i = 0; i < 8; i++) {
        memberNo = i;
        anim = HuSprAnimDataRead(tbl138[i]);
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 200, 0));
        HuSprPosSet(grpId, memberNo, 0.0f, 60.0f);
        HuSprAttrSet(grpId, memberNo, HUSPR_ATTR_DISPOFF);
    }
    anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 23));
    HuSprGrpMemberSet(grpId, 8, HuSprCreate(anim, 180, 0));
    HuSprPosSet(grpId, 8, lbl_1_data_648[2].x, lbl_1_data_648[2].y);
    if (mode) {
        HuSprGrpPosSet(grpId, lbl_1_data_5E8[1].x, lbl_1_data_5E8[1].y);
    } else {
        HuSprGrpPosSet(grpId, lbl_1_data_5E8[0].x, lbl_1_data_5E8[0].y);
    }
    HuSprGrpDrawNoSet(grpId, 64);
    }
    {
    HuVec2f *pos6C8 = lbl_1_data_6C8;
    HuVec2f *pos688 = lbl_1_data_688;
    HuVec2f pos748 = lbl_1_data_748[0];
    s32 dataNum[4];
    grpId = HuSprGrpCreate(15);
    lbl_1_bss_974->grp74 = grpId;
    anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 24));
    HuSprGrpMemberSet(grpId, 0, HuSprCreate(anim, 140, 0));
    HuSprPosSet(grpId, 0, 0.0f, 20.0f);
    switch (GwCommon.languageNo) {
        case 0:
            anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 25));
            break;
        case 1:
            anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 67));
            break;
    }
    HuSprGrpMemberSet(grpId, 1, HuSprCreate(anim, 115, 0));
    HuSprPosSet(grpId, 1, pos748.x, pos748.y);
    for (i = 0; i < 4; i++) {
        fn_1_46DC(i, grpId, i + 2, i + 7, 130, 120);
        HuSprPosSet(grpId, i + 2, pos6C8[i].x, pos6C8[i].y);
        HuSprPosSet(grpId, i + 7, pos6C8[i].x, 33.0f + pos6C8[i].y);
    }
    switch (GwCommon.languageNo) {
        case 0:
            dataNum[0] = DATANUM(DATA_mgfree, 29);
            dataNum[1] = DATANUM(DATA_mgfree, 30);
            dataNum[2] = DATANUM(DATA_mgfree, 31);
            dataNum[3] = DATANUM(DATA_mgfree, 32);
            break;
        case 1:
            dataNum[0] = DATANUM(DATA_mgfree, 58);
            dataNum[1] = DATANUM(DATA_mgfree, 59);
            dataNum[2] = DATANUM(DATA_mgfree, 60);
            dataNum[3] = DATANUM(DATA_mgfree, 61);
            break;
    }
    HuSprGrpMemberSet(grpId, 6, HuSprCreate(HuSprAnimDataRead(DATANUM(DATA_mgfree, 56)), 130, 0));
    HuSprGrpMemberSet(grpId, 11, HuSprCreate(HuSprAnimDataRead(dataNum[0]), 120, 0));
    HuSprGrpMemberSet(grpId, 12, HuSprCreate(HuSprAnimDataRead(dataNum[1]), 120, 0));
    HuSprGrpMemberSet(grpId, 13, HuSprCreate(HuSprAnimDataRead(dataNum[2]), 120, 0));
    HuSprGrpMemberSet(grpId, 14, HuSprCreate(HuSprAnimDataRead(dataNum[3]), 120, 0));
    HuSprAttrSet(grpId, 6, HUSPR_ATTR_DISPOFF);
    for (i = 0; i < 4; i++) {
        HuSprAttrSet(grpId, i + 11, HUSPR_ATTR_DISPOFF);
    }
    HuSprGrpPosSet(grpId, lbl_1_data_608[1].x, lbl_1_data_608[1].y);
    HuWinDispOff(lbl_1_bss_974->winId[19]);
    HuSprGrpDrawNoSet(grpId, 0);
    }

    grpId = HuSprGrpCreate(6);
    lbl_1_bss_974->grp7C = grpId;
    i = 3;
    while (i-- != 0) {
        memberNo = i;
        anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 26));
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 100, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_768[i].x, lbl_1_data_768[i].y);
    }
    i = 3;
    while (i-- != 0) {
        memberNo = i + 3;
        anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 27));
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 100, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_768[i].x, lbl_1_data_768[i].y);
        HuSprTPLvlSet(grpId, memberNo, 0.0f);
    }
    HuSprGrpPosSet(grpId, lbl_1_data_628[1].x, lbl_1_data_628[1].y);
    HuSprGrpDrawNoSet(grpId, 0);

    grpId = HuSprGrpCreate(6);
    lbl_1_bss_974->grp80 = grpId;
    i = 3;
    while (i-- != 0) {
        memberNo = i;
        anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 26));
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 100, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_768[i].x, lbl_1_data_768[i].y);
    }
    i = 3;
    while (i-- != 0) {
        memberNo = i + 3;
        anim = HuSprAnimDataRead(DATANUM(DATA_mgfree, 27));
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 100, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_768[i].x, lbl_1_data_768[i].y);
        HuSprTPLvlSet(grpId, memberNo, 0.0f);
    }
    HuSprGrpPosSet(grpId, lbl_1_data_628[1].x, lbl_1_data_628[1].y);
    HuSprGrpDrawNoSet(grpId, 0);

    {
    s32 tbl158[4] = { DATANUM(DATA_mgfree, 40), DATANUM(DATA_mgfree, 41), DATANUM(DATA_mgfree, 39), DATANUM(DATA_mgfree, 38) };
    s32 tbl168[4] = { DATANUM(DATA_mgfree, 44), DATANUM(DATA_mgfree, 45), DATANUM(DATA_mgfree, 43), DATANUM(DATA_mgfree, 42) };
    HuVec2f *pos688 = lbl_1_data_688;
    grpId = HuSprGrpCreate(8);
    lbl_1_bss_974->grp78 = grpId;
    i = 4;
    while (i-- != 0) {
        lbl_1_bss_974->unk108[i] = 0;
        lbl_1_bss_974->proc[i] = 0;
    }
    i = 2;
    while (i-- != 0) {
        memberNo = i;
        anim = HuSprAnimDataRead(tbl158[i]);
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 160, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_638[i].x, lbl_1_data_638[i].y);
        memberNo = i + 4;
        anim = HuSprAnimDataRead(tbl168[i]);
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 160, 0));
        HuSprPosSet(grpId, memberNo, lbl_1_data_638[i].x, lbl_1_data_638[i].y);
        HuSprTPLvlSet(grpId, memberNo, 0.0f);
        lbl_1_bss_974->pos128[i] = lbl_1_data_638[i];
    }
    i = 2;
    while (i-- != 0) {
        memberNo = i + 2;
        anim = HuSprAnimDataRead(tbl158[i + 2]);
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 110, 0));
        HuSprPosSet(grpId, memberNo, pos688[i].x, pos688[i].y);
        HuSprTPLvlSet(grpId, memberNo, 0.0f);
        memberNo = i + 6;
        anim = HuSprAnimDataRead(tbl168[i + 2]);
        HuSprGrpMemberSet(grpId, memberNo, HuSprCreate(anim, 110, 0));
        HuSprPosSet(grpId, memberNo, pos688[i].x, pos688[i].y);
        HuSprTPLvlSet(grpId, memberNo, 0.0f);
        lbl_1_bss_974->pos128[i + 2] = pos688[i];
    }
    if (mode) {
        HuSprGrpPosSet(grpId, lbl_1_data_618[1].x, lbl_1_data_618[1].y);
    } else {
        HuSprGrpPosSet(grpId, lbl_1_data_618[0].x, lbl_1_data_618[0].y);
    }
    HuSprGrpDrawNoSet(grpId, 0);
    }
    HuSprExecLayerSet(64, 1);
    fn_1_91A8();
    if (mode) {
        HuWinDispOff(lbl_1_bss_974->winId[0]);
        HuWinDispOff(lbl_1_bss_974->winId[17]);
        HuWinDispOff(lbl_1_bss_974->winId[18]);
        HuWinDispOff(lbl_1_bss_974->winId[1]);
        HuWinDispOff(lbl_1_bss_974->winId[2]);
        HuWinDispOff(lbl_1_bss_974->winId[3]);
        HuWinDispOff(lbl_1_bss_974->winId[4]);
        HuWinDispOff(lbl_1_bss_974->winId[5]);
        HuWinDispOff(lbl_1_bss_974->winId[6]);
        HuWinDispOff(lbl_1_bss_974->winId[7]);
        HuWinDispOff(lbl_1_bss_974->winId[8]);
    }
    HuPrcChildCreate(fn_1_A570, 200, 0x2000, 0, HuPrcCurrentGet());
    fn_1_15B8();
}

/* 167 insns */
void fn_1_7FA0(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[0];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 4, 1.0f);
    while (lbl_1_bss_974->unk108[0]-- != 0) {
        t = lbl_1_bss_974->unk108[0] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.2f * t;
        scale += 1.0f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 4, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 4, pos->x, pos->y - 16.0f * t);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 4, 0.0f);
    if (lbl_1_bss_974->cursor - 1 <= 0) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 0.0f);
    } else {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 1.0f);
    }
    lbl_1_bss_974->proc[0] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_823C(void)
{
    lbl_1_bss_974->unk108[0] = 8;
    if (lbl_1_bss_974->proc[0] == 0) {
        lbl_1_bss_974->proc[0] = HuPrcChildCreate(fn_1_7FA0, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 211 insns */
void fn_1_82B4(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[1];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 5, 1.0f);
    while (lbl_1_bss_974->unk108[1]-- != 0) {
        t = lbl_1_bss_974->unk108[1] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.2f * t;
        scale += 1.0f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 5, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 5, pos->x, pos->y + 16.0f * t);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 5, 0.0f);
    if (lbl_1_bss_974->listNum & 1) {
        if (lbl_1_bss_974->cursor == lbl_1_bss_974->listNum - 1) {
            HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
        } else {
            HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
        }
    } else if (lbl_1_bss_974->listNum <= lbl_1_bss_974->cursor + 2) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
    } else {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
    }
    lbl_1_bss_974->proc[1] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_8600(void)
{
    lbl_1_bss_974->unk108[1] = 8;
    if (lbl_1_bss_974->proc[1] == 0) {
        lbl_1_bss_974->proc[1] = HuPrcChildCreate(fn_1_82B4, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 149 insns */
void fn_1_8678(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[2];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 2, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 6, 1.0f);
    while (lbl_1_bss_974->unk108[2]-- != 0) {
        t = lbl_1_bss_974->unk108[2] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.2f * t;
        scale += 1.0f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 6, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 6, pos->x - 16.0f * t, pos->y);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 2, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 6, 0.0f);
    lbl_1_bss_974->proc[2] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_88CC(void)
{
    lbl_1_bss_974->unk108[2] = 8;
    if (lbl_1_bss_974->proc[2] == 0) {
        lbl_1_bss_974->proc[2] = HuPrcChildCreate(fn_1_8678, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 149 insns */
void fn_1_8944(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[3];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 3, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 7, 1.0f);
    while (lbl_1_bss_974->unk108[3]-- != 0) {
        t = lbl_1_bss_974->unk108[3] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.2f * t;
        scale += 1.0f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 7, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 7, pos->x + 16.0f * t, pos->y);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 3, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 7, 0.0f);
    lbl_1_bss_974->proc[3] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_8B98(void)
{
    lbl_1_bss_974->unk108[3] = 8;
    if (lbl_1_bss_974->proc[3] == 0) {
        lbl_1_bss_974->proc[3] = HuPrcChildCreate(fn_1_8944, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 149 insns */
void fn_1_8C10(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[2];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 2, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 6, 1.0f);
    while (lbl_1_bss_974->unk108[2]-- != 0) {
        t = lbl_1_bss_974->unk108[2] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.3f * t;
        scale += 0.7f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 6, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 6, pos->x - 16.0f * t, pos->y);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 2, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 6, 0.0f);
    lbl_1_bss_974->proc[2] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_8E64(void)
{
    lbl_1_bss_974->unk108[2] = 8;
    if (lbl_1_bss_974->proc[2] == 0) {
        lbl_1_bss_974->proc[2] = HuPrcChildCreate(fn_1_8C10, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 149 insns */
void fn_1_8EDC(void)
{
    HuVec2f *pos;
    float t;
    float scale;

    pos = &lbl_1_bss_974->pos128[3];
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 3, 0.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 7, 1.0f);
    while (lbl_1_bss_974->unk108[3]-- != 0) {
        t = lbl_1_bss_974->unk108[3] / 8.0f;
        t *= 2.0f;
        if (t >= 1.0f) {
            t = 2.0f - t;
        }
        t = sin(M_PI * t / 2.0);
        scale = 0.3f * t;
        scale += 0.7f;
        HuSprScaleSet(lbl_1_bss_974->grp78, 7, scale, scale);
        HuSprPosSet(lbl_1_bss_974->grp78, 7, pos->x + 16.0f * t, pos->y);
        HuPrcVSleep();
    }
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 3, 1.0f);
    HuSprTPLvlSet(lbl_1_bss_974->grp78, 7, 0.0f);
    lbl_1_bss_974->proc[3] = 0;
    HuPrcEnd();
}

/* 30 insns */
void fn_1_9130(void)
{
    lbl_1_bss_974->unk108[3] = 8;
    if (lbl_1_bss_974->proc[3] == 0) {
        lbl_1_bss_974->proc[3] = HuPrcChildCreate(fn_1_8EDC, 200, 0x1000, 0, HuPrcCurrentGet());
    }
}

/* 622 insns */
void fn_1_91A8(void)
{
    s32 i;
    s32 unlockNum;
    s32 j;
    s32 k;
    s32 num;

    lbl_1_bss_974->unk102 = lbl_1_bss_974->cursor;
    i = 0;
    lbl_1_bss_974->listNum = i;
    unlockNum = 0;
    for (; mgDataTbl[i].ovl != 0xFFFF; i++) {
        if (mgDataTbl[i].type == fn_1_218() && !(mgDataTbl[i].flag & MG_FLAG_SPECIAL)) {
            lbl_1_bss_974->list[lbl_1_bss_974->listNum].mgIdx = i;
            lbl_1_bss_974->list[lbl_1_bss_974->listNum].unk2 = GWMgUnlockGet(i + 501);
            if (lbl_1_bss_974->list[lbl_1_bss_974->listNum].unk2 != 0) {
                unlockNum++;
            }
            lbl_1_bss_974->listNum++;
        }
    }
    OSReport("Type = %d\n", fn_1_218());
    OSReport("\203~\203j\203Q\201[\203\200\220\224 %d\n", lbl_1_bss_974->listNum);
    HuWinDispOn(lbl_1_bss_974->winId[0]);
    HuWinMesSet(lbl_1_bss_974->winId[0], fn_1_244());
    sprintf(lbl_1_bss_966, "%2d", unlockNum);
    sprintf(lbl_1_bss_966 + 6, "%2d", lbl_1_bss_974->listNum);
    HuWinScaleSet(lbl_1_bss_974->winId[17], 0.8f, 0.8f);
    HuWinDispOn(lbl_1_bss_974->winId[17]);
    HuWinMesSet(lbl_1_bss_974->winId[17], 0xE000F);
    HuWinInsertMesSet(lbl_1_bss_974->winId[17], MESSNUM_PTR(lbl_1_bss_966), 0);
    HuWinInsertMesSet(lbl_1_bss_974->winId[17], MESSNUM_PTR(lbl_1_bss_966 + 6), 1);
    num = lbl_1_bss_974->listNum - lbl_1_bss_974->unk104;
    HuSprPosSet(lbl_1_bss_974->grp70, 8, lbl_1_data_648[lbl_1_bss_974->unk106].x, lbl_1_data_648[lbl_1_bss_974->unk106].y);
    if (num <= 8) {
        j = num;
        while (j-- != 0) {
            HuWinDispOn(lbl_1_bss_974->winId[j + 1]);
            if (lbl_1_bss_974->list[lbl_1_bss_974->unk104 + j].unk2 != 0) {
                HuWinMesSet(lbl_1_bss_974->winId[j + 1], fn_1_46AC_inline(lbl_1_bss_974->unk104 + j));
            } else {
                HuWinMesSet(lbl_1_bss_974->winId[j + 1], 0x1F004F);
            }
        }
        for (j = 7; j >= num; j--) {
            HuWinDispOff(lbl_1_bss_974->winId[j + 1]);
        }
    } else {
        j = 8;
        while (j-- != 0) {
            HuWinDispOn(lbl_1_bss_974->winId[j + 1]);
            if (lbl_1_bss_974->list[lbl_1_bss_974->unk104 + j].unk2 != 0) {
                HuWinMesSet(lbl_1_bss_974->winId[j + 1], fn_1_46AC_inline(lbl_1_bss_974->unk104 + j));
            } else {
                HuWinMesSet(lbl_1_bss_974->winId[j + 1], 0x1F004F);
            }
        }
    }
    for (k = 0; k < 8; k++) {
        HuSprAttrSet(lbl_1_bss_974->grp70, k, HUSPR_ATTR_DISPOFF);
    }
    i = fn_1_218();
    switch (i) {
        case MG_TYPE_4P:
            HuSprAttrReset(lbl_1_bss_974->grp70, 0, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_1VS3:
            HuSprAttrReset(lbl_1_bss_974->grp70, 1, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_2VS2:
            HuSprAttrReset(lbl_1_bss_974->grp70, 2, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_BATTLE:
            HuSprAttrReset(lbl_1_bss_974->grp70, 3, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_KETTOU:
            HuSprAttrReset(lbl_1_bss_974->grp70, 4, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_KUPA:
            HuSprAttrReset(lbl_1_bss_974->grp70, 5, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_DONKEY:
            HuSprAttrReset(lbl_1_bss_974->grp70, 6, HUSPR_ATTR_DISPOFF);
            break;
        case MG_TYPE_LAST:
            HuSprAttrReset(lbl_1_bss_974->grp70, 7, HUSPR_ATTR_DISPOFF);
            break;
    }
    if (lbl_1_bss_974->listNum <= 8) {
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 0.0f);
        HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
    } else {
        if (lbl_1_bss_974->unk104 - 1 <= 0) {
            HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 0.0f);
        } else {
            HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 1.0f);
        }
        if (lbl_1_bss_974->listNum & 1) {
            if (lbl_1_bss_974->unk104 >= lbl_1_bss_974->listNum - 7) {
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
            } else {
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
            }
        } else {
            if (lbl_1_bss_974->unk104 >= lbl_1_bss_974->listNum - 8) {
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 0.0f);
            } else {
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
            }
        }
    }
    HuSprPosSet(lbl_1_bss_974->grp70, 8, lbl_1_data_648[lbl_1_bss_974->unk106].x, lbl_1_data_648[lbl_1_bss_974->unk106].y);
}
#ifdef __MWERKS__
#endif

/* 101 insns */
void fn_1_9B60(void)
{
    s32 i;
    s32 time;

    time = 5;
    HuWinDispOn(lbl_1_bss_974->winId[0]);
    for (i = 0; i < time; i++) {
        HuWinScaleSet(lbl_1_bss_974->winId[0], fn_1_2B4(1.0f, 0.0f, (float)i / time), fn_1_2B4(1.0f, 0.0f, (float)i / time));
        HuPrcVSleep();
    }
    HuWinScaleSet(lbl_1_bss_974->winId[0], 1.0f, 1.0f);
    HuPrcEnd();
}

/* 70 insns */
void fn_1_9CF4(void)
{
    s32 i;
    float ofs;
    float t;

    HuSprGrpPosSet(lbl_1_bss_974->grp6C, lbl_1_data_5F8[1].x, lbl_1_data_5F8[1].y);
    i = 60;
    while (i-- != 0) {
        t = i / 60.0f;
        ofs = t * (lbl_1_data_5F8[1].x - lbl_1_data_5F8[0].x);
        HuSprGrpPosSet(lbl_1_bss_974->grp6C, lbl_1_data_5F8[0].x + ofs, lbl_1_data_5F8[0].y);
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 151 insns */
void fn_1_9E0C(void)
{
    s32 winNo[10] = { 18, 17, 1, 2, 3, 4, 5, 6, 7, 8 };
    MGFREE_WINDATA *win;
    s32 i;
    s32 time;
    float t;
    float ofs;

    i = 10;
    while (i-- != 0) {
        HuWinDispOn(lbl_1_bss_974->winId[winNo[i]]);
    }
    time = 60;
    while (time-- != 0) {
        t = time / 60.0f;
        ofs = t * (lbl_1_data_5E8[1].y - lbl_1_data_5E8[0].y);
        HuSprGrpPosSet(lbl_1_bss_974->grp70, lbl_1_data_5E8[0].x, lbl_1_data_5E8[0].y + ofs);
        HuSprGrpPosSet(lbl_1_bss_974->grp78, lbl_1_data_618[0].x, lbl_1_data_618[0].y + ofs);
        i = 10;
        while (i-- != 0) {
            win = &lbl_1_data_330[winNo[i]];
            HuWinPosSet(lbl_1_bss_974->winId[winNo[i]], win->x - win->w / 2.0f, ofs + (win->y - win->h / 2.0f));
        }
        HuPrcVSleep();
    }
    HuPrcEnd();
}

/* 31 insns */
void fn_1_A068(void)
{
    HuPrcChildCreate(fn_1_9B60, 200, 0x1000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_9CF4, 200, 0x1000, 0, HuPrcCurrentGet());
    HuPrcChildCreate(fn_1_9E0C, 200, 0x1000, 0, HuPrcCurrentGet());
}

/* 220 insns */
void fn_1_A0E4(void)
{
    s32 i;
    s32 time;
    s32 wait;
    float scale;

    time = 5;
    scale = 0.0f;
    for (i = 0; i < time; i++) {
        HuWinScaleSet(lbl_1_bss_974->winId[0], fn_1_2B4(0.0f, 1.0f, (float)i / time), fn_1_2B4(0.0f, 1.0f, (float)i / time));
        HuPrcVSleep();
    }
    HuWinScaleSet(lbl_1_bss_974->winId[0], 0.0f, 0.0f);
    HuWinDispOff(lbl_1_bss_974->winId[0]);
    wait = 15;
    while (wait-- != 0) {
        HuPrcVSleep();
    }
    lbl_1_bss_974->unk102 = lbl_1_bss_974->cursor = 0;
    lbl_1_bss_974->unk106 = 0;
    lbl_1_bss_974->unk104 = 0;
    fn_1_91A8();
    fn_1_15B8();
    HuWinDispOn(lbl_1_bss_974->winId[0]);
    HuAudFXPlay(1268);
    for (i = 0; i < time; i++) {
        HuWinScaleSet(lbl_1_bss_974->winId[0], fn_1_2B4(1.0f, 0.0f, (float)i / time), fn_1_2B4(1.0f, 0.0f, (float)i / time));
        HuPrcVSleep();
    }
    HuWinScaleSet(lbl_1_bss_974->winId[0], 1.0f, 1.0f);
    HuPrcEnd();
}

/* 23 insns */
void fn_1_A454(void)
{
    s32 i;
    HuPrcChildCreate(fn_1_A0E4, 200, 0x2000, 0, HuPrcCurrentGet());
    i = 5;
    while (i-- != 0) {
        HuPrcVSleep();
    }
}

/* 11 insns */
s32 fn_1_A4B0(void)
{
    return lbl_1_bss_974->list[lbl_1_bss_974->cursor].mgIdx;
}

/* 26 insns */
s32 fn_1_A4DC(void)
{
    if (lbl_1_bss_974->list[lbl_1_bss_974->cursor].unk2 == 0) {
        return -1;
    }
    return fn_1_A4B0();
}

/* 11 insns */
s32 fn_1_A544(void)
{
    return lbl_1_bss_974->unk0 == 1;
}
#ifdef __MWERKS__
#endif
#ifdef __MWERKS__
#endif

/* 3412 insns */
void fn_1_A570(void)
{
    s16 dir;
    s16 delta;
    s32 timer;
    s32 i;

    while (1) {
        switch (lbl_1_bss_974->unk0) {
            case 0:
                fn_1_4D20(1);
                break;
            case 2:
                if (lbl_1_bss_974->cursor >= 2) {
                    lbl_1_bss_974->cursor -= 2;
                    fn_1_4D20(6);
                }
                else {
                    fn_1_4D20(1);
                }
                break;
            case 3:
                if (lbl_1_bss_974->listNum & 1) {
                    lbl_1_bss_974->cursor += 2;
                    if (lbl_1_bss_974->cursor > lbl_1_bss_974->listNum - 1) {
                        lbl_1_bss_974->cursor = lbl_1_bss_974->listNum - 1;
                    }
                }
                else if (lbl_1_bss_974->listNum > lbl_1_bss_974->cursor + 2) {
                    lbl_1_bss_974->cursor += 2;
                }
                if (lbl_1_bss_974->cursor != lbl_1_bss_974->unk102) {
                    fn_1_4D20(6);
                }
                else {
                    fn_1_4D20(1);
                }
                break;
            case 4:
                if (lbl_1_bss_974->cursor >= 1 && (lbl_1_bss_974->cursor & 1)) {
                    lbl_1_bss_974->cursor--;
                    fn_1_4D20(6);
                }
                else {
                    fn_1_4D20(1);
                }
                break;
            case 5:
                if (lbl_1_bss_974->listNum > lbl_1_bss_974->cursor + 1 && (lbl_1_bss_974->cursor & 1) == 0) {
                    lbl_1_bss_974->cursor++;
                    fn_1_4D20(6);
                }
                else {
                    fn_1_4D20(1);
                }
                break;
            case 6:
                switch (lbl_1_bss_974->unk2) {
                    case 0:
                        delta = lbl_1_bss_974->cursor - lbl_1_bss_974->unk102;
                        dir = 0;
                        switch (lbl_1_bss_974->unk106) {
                            case 0:
                                if (delta < 0) {
                                    if (delta == -1) {
                                        lbl_1_bss_974->unk106 = 1;
                                        dir = -1;
                                    }
                                    else {
                                        dir = -1;
                                    }
                                }
                                else {
                                    lbl_1_bss_974->unk106 += delta;
                                }
                                break;
                            case 1:
                                if (delta < 0) {
                                    if (delta == -1) {
                                        lbl_1_bss_974->unk106 = 0;
                                    }
                                    else {
                                        dir = -1;
                                    }
                                }
                                else {
                                    lbl_1_bss_974->unk106 += delta;
                                }
                                break;
                            case 6:
                                if (delta > 0) {
                                    if (delta == 1) {
                                        lbl_1_bss_974->unk106 = 7;
                                    }
                                    else {
                                        dir++;
                                    }
                                }
                                else {
                                    lbl_1_bss_974->unk106 += delta;
                                }
                                break;
                            case 7:
                                if (delta > 0) {
                                    if (delta == 1) {
                                        lbl_1_bss_974->unk106 = 6;
                                        dir++;
                                    }
                                    else {
                                        dir++;
                                    }
                                }
                                else {
                                    lbl_1_bss_974->unk106 += delta;
                                }
                                break;
                            default:
                                lbl_1_bss_974->unk106 += delta;
                                break;
                        }
                        fn_1_15B8();
                        HuAudFXPlay(MSM_SE_CMN_01);
                        lbl_1_bss_974->unk2 = 1;
                        break;
                    case 1:
                        switch (dir) {
                            case -1:
                                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
                                fn_1_823C();
                                lbl_1_bss_974->unk104 -= 2;
                                goto scroll;
                            case 1:
                                HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 1.0f);
                                fn_1_8600();
                                lbl_1_bss_974->unk104 += 2;
                            scroll:
                                fn_1_4A08();
                                break;
                            case 0:
                                HuSprPosSet(lbl_1_bss_974->grp70, 8, lbl_1_data_648[lbl_1_bss_974->unk106].x, lbl_1_data_648[lbl_1_bss_974->unk106].y);
                                break;
                        }
                        timer = 5;
                        lbl_1_bss_974->unk2 = 2;
                        break;
                    case 2:
                        timer--;
                        if (timer == 0) {
                            lbl_1_bss_974->unk102 = lbl_1_bss_974->cursor;
                            fn_1_4D20(1);
                        }
                        break;
                }
                break;
            case 7: {
                HuVec2f *pos;
                s32 j;
                s32 no;
                HuAudFXPlay(MSM_SE_CMN_01);
                lbl_1_bss_974->unk148--;
                if (lbl_1_bss_974->unk148 < 0) {
                    lbl_1_bss_974->unk148 = 2;
                }
                pos = lbl_1_data_6C8;
                for (j = 0; j < 4; j++) {
                    lbl_1_bss_974->unk149[j] = lbl_1_data_780[lbl_1_bss_974->unk148 + 4][j];
                    no = lbl_1_bss_974->unk149[j];
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[j].x, pos[j].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[j].x, 33.0f + pos[j].y);
                }
                fn_1_88CC();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 8: {
                HuVec2f *pos;
                s32 j;
                s32 no;
                HuAudFXPlay(MSM_SE_CMN_01);
                lbl_1_bss_974->unk148++;
                if (lbl_1_bss_974->unk148 >= 3) {
                    lbl_1_bss_974->unk148 = 0;
                }
                pos = lbl_1_data_6C8;
                for (j = 0; j < 4; j++) {
                    lbl_1_bss_974->unk149[j] = lbl_1_data_780[lbl_1_bss_974->unk148 + 4][j];
                    no = lbl_1_bss_974->unk149[j];
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[j].x, pos[j].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[j].x, 33.0f + pos[j].y);
                }
                fn_1_8B98();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 9: {
                HuVec2f *pos;
                s32 j;
                s32 no;
                HuAudFXPlay(MSM_SE_CMN_01);
                lbl_1_bss_974->unk148--;
                if (lbl_1_bss_974->unk148 < 0) {
                    lbl_1_bss_974->unk148 = 3;
                }
                pos = &lbl_1_data_6C8[4];
                for (j = 0; j < 4; j++) {
                    lbl_1_bss_974->unk149[j] = lbl_1_data_780[lbl_1_bss_974->unk148][j];
                    no = lbl_1_bss_974->unk149[j];
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[j].x, pos[j].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[j].x, 33.0f + pos[j].y);
                }
                fn_1_88CC();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 10: {
                HuVec2f *pos;
                s32 j;
                s32 no;
                HuAudFXPlay(MSM_SE_CMN_01);
                lbl_1_bss_974->unk148++;
                if (lbl_1_bss_974->unk148 >= 4) {
                    lbl_1_bss_974->unk148 = 0;
                }
                pos = &lbl_1_data_6C8[4];
                for (j = 0; j < 4; j++) {
                    lbl_1_bss_974->unk149[j] = lbl_1_data_780[lbl_1_bss_974->unk148][j];
                    no = lbl_1_bss_974->unk149[j];
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[j].x, pos[j].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[j].x, 33.0f + pos[j].y);
                }
                fn_1_8B98();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 11: {
                HuVec2f *pos;
                s32 no;
                lbl_1_bss_974->unk148--;
                if (lbl_1_bss_974->unk148 < 0) {
                    lbl_1_bss_974->unk148 = 5;
                }
                HuAudFXPlay(MSM_SE_CMN_01);
                for (i = 0; i < 4; i++) {
                    lbl_1_bss_974->unk149[i] = lbl_1_data_780[lbl_1_bss_974->unk148 + 7][i];
                }
                pos = &lbl_1_data_6C8[8];
                for (i = 0; i < 2; i++) {
                    no = lbl_1_bss_974->unk149[i];
                    HuSprAttrReset(lbl_1_bss_974->grp74, no + 2, 4);
                    HuSprAttrReset(lbl_1_bss_974->grp74, no + 7, 4);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[i].x, pos[i].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[i].x, 33.0f + pos[i].y);
                }
                for (i = 2; i < 4; i++) {
                    no = lbl_1_bss_974->unk149[i];
                    HuSprAttrSet(lbl_1_bss_974->grp74, no + 2, 4);
                    HuSprAttrSet(lbl_1_bss_974->grp74, no + 7, 4);
                }
                fn_1_88CC();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 12: {
                HuVec2f *pos;
                s32 j;
                s32 no;
                HuAudFXPlay(MSM_SE_CMN_01);
                lbl_1_bss_974->unk148++;
                if (lbl_1_bss_974->unk148 >= 6) {
                    lbl_1_bss_974->unk148 = 0;
                }
                for (j = 0; j < 4; j++) {
                    lbl_1_bss_974->unk149[j] = lbl_1_data_780[lbl_1_bss_974->unk148 + 7][j];
                }
                pos = &lbl_1_data_6C8[8];
                for (j = 0; j < 2; j++) {
                    no = lbl_1_bss_974->unk149[j];
                    HuSprAttrReset(lbl_1_bss_974->grp74, no + 2, 4);
                    HuSprAttrReset(lbl_1_bss_974->grp74, no + 7, 4);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 2, pos[j].x, pos[j].y);
                    HuSprPosSet(lbl_1_bss_974->grp74, no + 7, pos[j].x, 33.0f + pos[j].y);
                }
                for (j = 2; j < 4; j++) {
                    no = lbl_1_bss_974->unk149[j];
                    HuSprAttrSet(lbl_1_bss_974->grp74, no + 2, 4);
                    HuSprAttrSet(lbl_1_bss_974->grp74, no + 7, 4);
                }
                fn_1_8B98();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 13: {
                s32 j;
                lbl_1_bss_974->unk107--;
                if (GwCommon.m562VeryHardUnlock) {
                    if (lbl_1_bss_974->unk107 < 0) {
                        lbl_1_bss_974->unk107 = 3;
                    }
                }
                else if (lbl_1_bss_974->unk107 < 0) {
                    lbl_1_bss_974->unk107 = 2;
                }
                HuAudFXPlay(MSM_SE_CMN_01);
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(lbl_1_bss_974->grp74, j + 11, 4);
                }
                HuSprAttrReset(lbl_1_bss_974->grp74, lbl_1_bss_974->unk107 + 11, 4);
                fn_1_8E64();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 14: {
                s32 j;
                lbl_1_bss_974->unk107++;
                if (GwCommon.m562VeryHardUnlock) {
                    if (lbl_1_bss_974->unk107 >= 4) {
                        lbl_1_bss_974->unk107 = 0;
                    }
                }
                else if (lbl_1_bss_974->unk107 >= 3) {
                    lbl_1_bss_974->unk107 = 0;
                }
                HuAudFXPlay(MSM_SE_CMN_01);
                for (j = 0; j < 4; j++) {
                    HuSprAttrSet(lbl_1_bss_974->grp74, j + 11, 4);
                }
                HuSprAttrReset(lbl_1_bss_974->grp74, lbl_1_bss_974->unk107 + 11, 4);
                fn_1_9130();
                fn_1_A570_Wait(10);
                fn_1_4D20(1);
                break;
            }
            case 15:
                if (lbl_1_bss_974->unk107 > 0) {
                    HuAudFXPlay(MSM_SE_CMN_01);
                    lbl_1_bss_974->unk107--;
                    fn_1_4D7C();
                }
                fn_1_4D20(1);
                break;
            case 16:
                if (lbl_1_bss_974->unk107 < 2) {
                    HuAudFXPlay(MSM_SE_CMN_01);
                    lbl_1_bss_974->unk107++;
                    fn_1_4D7C();
                }
                fn_1_4D20(1);
                break;
            case 17:
                if (lbl_1_bss_974->unk107 > 0) {
                    HuAudFXPlay(MSM_SE_CMN_01);
                    lbl_1_bss_974->unk107--;
                    fn_1_5058();
                }
                fn_1_4D20(1);
                break;
            case 18:
                if (lbl_1_bss_974->unk107 < 2) {
                    HuAudFXPlay(MSM_SE_CMN_01);
                    lbl_1_bss_974->unk107++;
                    fn_1_5058();
                }
                fn_1_4D20(1);
                break;
            case 19: {
                MGDATA *mg;
                s32 unlockNo;
                mg = &mgDataTbl[fn_1_A4B0()];
                unlockNo = fn_1_A4B0() + 501;
                switch (mg->type) {
                    case MG_TYPE_2VS2:
                        fn_1_5A0C();
                        break;
                    case MG_TYPE_1VS3:
                        fn_1_5E04();
                        break;
                    case MG_TYPE_KETTOU:
                        fn_1_6204();
                        break;
                    case MG_TYPE_LAST:
                        fn_1_6660();
                        break;
                    case MG_TYPE_4P:
                    case MG_TYPE_DONKEY:
                        break;
                }
                fn_1_4D20(1);
                break;
            }
            case 20:
                if (fn_1_A4DC() + 501 == 519) {
                    fn_1_5330();
                }
                else if (fn_1_A4DC() + 501 == 552) {
                    fn_1_56A0();
                }
                fn_1_4D20(1);
                break;
            case 21:
                HuSprGrpPosSet(lbl_1_bss_974->grp74, lbl_1_data_608[1].x, lbl_1_data_608[1].y);
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 0, 1.0f);
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 1, 1.0f);
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 2, 0.0f);
                HuSprTPLvlSet(lbl_1_bss_974->grp78, 3, 0.0f);
                HuWinDispOff(lbl_1_bss_974->winId[19]);
                fn_1_4D20(1);
                break;
            case 22: {
                s32 k;
                k = 3;
                while (k-- != 0) {
                    HuWinDispOff(lbl_1_bss_974->winId[k + 20]);
                }
                HuSprGrpPosSet(lbl_1_bss_974->grp7C, lbl_1_data_628[1].x, lbl_1_data_628[1].y);
                k = 3;
                while (k-- != 0) {
                    HuWinDispOff(lbl_1_bss_974->winId[k + 23]);
                }
                HuSprGrpPosSet(lbl_1_bss_974->grp80, lbl_1_data_628[1].x, lbl_1_data_628[1].y);
                fn_1_4D20(1);
                break;
            }
        }
        HuPrcVSleep();
    }
}

