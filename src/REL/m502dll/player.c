/*
 * m502dll player.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/player.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

/*
 * Retail's player.c saw no CharFXPlay prototype: fn_1_4A1C passes the s32
 * charNo with no extsh. It is the only game/audio.h function this unit calls,
 * so the matching build leaves the header out; the host needs the prototype.
 */
#include "game/charman.h"
#include "game/process.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x138 */ /* float lbl_1_rodata_138 = 0.0f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 1.0f; */
/* 0x140 */ /* float lbl_1_rodata_140 = 4.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = -9420.0f; */
/* 0x148 */ /* float lbl_1_rodata_148 = -36.5f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 150.0f; */
/* 0x150 */ /* float lbl_1_rodata_150 = -2.4333334f; */
/* 0x154 */ /* float lbl_1_rodata_154 = 0.9f; */
/* 0x158 */ /* float lbl_1_rodata_158 = -4.866667f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 0.8f; */
/* 0x160 */ /* float lbl_1_rodata_160 = -0.24333334f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 60.0f; */
/* 0x168 */ /* float lbl_1_rodata_168 = 280.0f; */
/* 0x170 */ /* double lbl_1_rodata_170 = 4503601774854144; */
/* 0x178 */ /* float lbl_1_rodata_178 = 2.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 1300.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 15.0f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 10.0f; */
/* 0x188 */ /* float lbl_1_rodata_188 = -90.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = -300.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 300.0f; */
/* 0x194 */ /* float lbl_1_rodata_194 = 90.0f; */
/* 0x198 */ /* s32 lbl_1_rodata_198[4] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1A8 */ /* double lbl_1_rodata_1A8 = -26.66666805744171; */
/* 0x1B0 */ /* double lbl_1_rodata_1B0 = -120.0000062584877; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = -750.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 1.35f; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = 0.016666668f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 8.0f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 220.0f; */
/* 0x1CC */ /* float lbl_1_rodata_1CC = 145.0f; */
/* 0x1D0 */ /* s32 lbl_1_rodata_1D0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 70.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 4550.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 3500.0f; */

/* --- .data --- */
/* 0xC38 */ s32 lbl_1_data_C38[7] = { 0x00000001, 0x00020003, 0x00040005, 0x00060007, 0x00080009, 0x00000000, 0x00000000 };
/* 0xC54 */ unsigned int lbl_1_data_C54[13][11] = { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x00870055, 0x008C0008, 0x008C0009, 0x008C000A, 0x008C001D, 0x008C0007, 0x00330000, 0x00330001, 0x00330002, 0x00330003, 0x00330004, 0x002E0055, 0x00330008, 0x00330009, 0x0033000A, 0x0033001D, 0x00330007, 0x00B70000, 0x00B70001, 0x00B70002, 0x00B70003, 0x00B70004, 0x00B20055, 0x00B70008, 0x00B70009, 0x00B7000A, 0x00B7001D, 0x00B70007, 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED0003, 0x00ED0004, 0x00E80055, 0x00ED0008, 0x00ED0009, 0x00ED000A, 0x00ED001D, 0x00ED0007, 0x00E60000, 0x00E60001, 0x00E60002, 0x00E60003, 0x00E60004, 0x00E10055, 0x00E60008, 0x00E60009, 0x00E6000A, 0x00E6001D, 0x00E60007, 0x00170000, 0x00170001, 0x00170002, 0x00170003, 0x00170004, 0x00120055, 0x00170008, 0x00170009, 0x0017000A, 0x0017001D, 0x00170007, 0x00E00000, 0x00E00001, 0x00E00002, 0x00E00003, 0x00E00004, 0x00DB0055, 0x00E00008, 0x00E00009, 0x00E0000A, 0x00E0001D, 0x00E00007, 0x002D0000, 0x002D0001, 0x002D0002, 0x002D0003, 0x002D0004, 0x00280055, 0x002D0008, 0x002D0009, 0x002D000A, 0x002D001D, 0x002D0007, 0x00C90000, 0x00C90001, 0x00C90002, 0x00C90003, 0x00C90004, 0x00C40055, 0x00C90008, 0x00C90009, 0x00C9000A, 0x00C9001D, 0x00C90007, 0x00B00000, 0x00B00001, 0x00B00002, 0x00B00003, 0x00B00004, 0x009C0055, 0x00B00008, 0x00B00009, 0x00B0000A, 0x00B0001D, 0x00B00007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x00870055, 0x008C0008, 0x008C0009, 0x008C000A, 0x008C001D, 0x008C0007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x00870055, 0x008C0008, 0x008C0009, 0x008C000A, 0x008C001D, 0x008C0007, 0x008C0000, 0x008C0001, 0x008C0002, 0x008C0003, 0x008C0004, 0x00870055, 0x008C0008, 0x008C0009, 0x008C000A, 0x008C001D, 0x008C0007 };
/* 0xE90 */ float lbl_1_data_E90 = -9300.0f;
/* 0xE94 */ float lbl_1_data_E94 = -8850.0f;

extern M502_WORK *lbl_1_data_0; /* m502.c: { &lbl_1_bss_0, 0 } (fork A spells it) */

/* --- functions (reference order) --- */
/* 170 insns */
void fn_1_38E0(M502_CHAR *chr, s32 no, M502_PLAYER *player)
{
    M502_WORK *work;
    M502_BLOCK *block;
    OMOBJ *obj;
    u16 i;
    HU3DMOTID motId;

    work = player->unk000;
    block = &player->unk008;
    obj = NULL;
    memset(chr, 0, sizeof(M502_CHAR));
    chr->unk000 = player;
    chr->unk010 = no;
    chr->unk018 = GwPlayerConf[chr->unk010].grp;
    chr->unk014 = GwPlayerConf[chr->unk010].charNo;
    obj = omAddObjEx(work->unk000, 100, 1, 11, -1, NULL);
    chr->unk01C = obj;
    chr->unk020 = 0;
    obj->mdlId[0] = CharModelCreate(chr->unk014, 2);
    CharModelStepFxSet(chr->unk014, 0);
    CharEffectLayerSet(4);
    for (i = 0; i < 11; i++) {
        obj->mtnId[i] = motId = CharMotionCreate(chr->unk014, lbl_1_data_C54[chr->unk014][i]);
        CharMotionSet(chr->unk014, obj->mtnId[i]);
    }
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelCameraSet(obj->mdlId[0], lbl_1_data_B60[no]);
    omSetTra(obj, 0.0f, 0.0f, 0.0f);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
    fn_1_6400(&chr->unk024, no, chr);
    chr->unk060 = 1;
    CharMotionUpdateSet(chr->unk014, lbl_1_data_C54[0][4], 0);
    CharMotionUpdateSet(chr->unk014, lbl_1_data_C54[0][3], 0);
}

/* 27 insns */
void fn_1_3B88(M502_CHAR *chr)
{
    fn_1_6478(&chr->unk024);
    if (chr->unk01C) {
        CharModelKill(chr->unk014);
        omDelObjEx(HuPrcCurrentGet(), chr->unk01C);
        chr->unk01C = NULL;
    }
    memset(chr, 0, sizeof(M502_CHAR));
}

/* 87 insns */
s32 fn_1_3BF4(M502_CHAR *chr)
{
    M502_WORK *work;
    s32 ret;

    work = chr->unk000->unk000;
    if (work->unk008 == 7) {
        chr->unk020 = 0;
    }
    ret = 0;
    if (chr->unk020) {
        fn_1_64B8(&chr->unk024);
    } else {
        chr->unk024.unk01C = chr->unk024.unk020 = chr->unk024.unk024 = 0;
    }
    switch (chr->unk004) {
        case 0:
            CharModelVoicePanSet(chr->unk014, 64);
            if (work->unk008 >= 2 && work->unk008 != 8) {
                chr->unk020 = 1;
                chr->unk004 = 1;
            }
            break;
        case 1:
            CharModelVoicePanSet(chr->unk014, (chr->unk010 == 0) ? 40 : (chr->unk010 == 1) ? 56 : (chr->unk010 == 2) ? 72 : 88);
            if (fn_1_3D50(chr)) {
                ret = 1;
            }
            break;
        case 2:
            fn_1_3D50(chr);
            break;
    }
    return ret;
}

/* 148 insns */
s32 fn_1_3D50(M502_CHAR *chr)
{
    M502_WORK *work;
    M502_STAGE *stage;
    s32 ret;
    s16 spC;
    s16 spA;
    s16 sp8;

    work = chr->unk000->unk000;
    stage = &chr->unk000->unkFD4;
    ret = 0;
    fn_1_561C(chr, &spC, &spA, &sp8);
    switch (chr->unk006) {
        case 0:
            if (fn_1_402C(chr) && spA > 0) {
                chr->unk006 = 1;
            }
            break;
        case 1:
            if (fn_1_3FA0(chr) && spA <= 0) {
                chr->unk006 = 0;
            }
            break;
        case 2:
            fn_1_40D8(chr);
            break;
        case 3:
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[10], 0.0f, 4.0f, 0);
            chr->unk006 = 4;
            break;
        case 4:
            break;
    }
    if (chr->unk006 < 2 && chr->unk01C->trans.y < -9420.0f) {
        fn_1_218(fn_1_198(0x630), (chr->unk010 == 0) ? 40 : (chr->unk010 == 1) ? 56 : (chr->unk010 == 2) ? 72 : 88);
        fn_1_3298(stage);
        chr->unk006 = 2;
        chr->unk00A = 0;
        chr->unk00C = 0;
        chr->unk06C = -36.5f;
        chr->unk074 = 0;
        ret = 1;
        if (work->unk5008 == 0) {
            work->unk014 = 0;
            work->unk5008 = 1;
        }
    }
    if (chr->unk006 < 2) {
        switch (work->unk008) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 7:
            case 8:
            case 9:
            case 11:
            case 12:
                fn_1_5510(chr);
                break;
            case 4:
            case 5:
            case 6:
            case 10:
                break;
        }
    }
    return ret;
}

/* 35 insns */
s32 fn_1_3FA0(M502_CHAR *chr)
{
    s32 ret = 0;

    switch (chr->unk008) {
        case 0:
            fn_1_44B8(chr);
            break;
        case 3:
            fn_1_4A1C(chr);
            break;
        case 4:
            if (fn_1_4E70(chr)) {
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 43 insns */
s32 fn_1_402C(M502_CHAR *chr)
{
    s32 ret = 0;

    switch (chr->unk008) {
        case 0:
            fn_1_44B8(chr);
            break;
        case 1:
            fn_1_46CC(chr);
            break;
        case 2:
            fn_1_4874(chr);
            break;
        case 3:
            fn_1_4A1C(chr);
            break;
        case 4:
            if (fn_1_4E70(chr)) {
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 248 insns */
void fn_1_40D8(M502_CHAR *chr)
{
    M502_PLAYER *player;
    M502_WORK *work;
    M502_STAGE *stage;
    float t;

    player = chr->unk000;
    work = player->unk000;
    stage = &player->unkFD4;
    switch (chr->unk00A) {
        case 0:
            t = ((lbl_1_data_E90 - chr->unk01C->trans.y >= 0.0f) ? (lbl_1_data_E90 - chr->unk01C->trans.y) : -(lbl_1_data_E90 - chr->unk01C->trans.y)) / 150.0f;
            t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
            if (chr->unk01C->trans.y < lbl_1_data_E90) {
                chr->unk06C -= -2.4333334f * t;
                chr->unk06C *= 0.9f;
            } else {
                chr->unk06C += -4.866667f * t;
                chr->unk06C *= 0.8f;
            }
            chr->unk06C -= -0.24333334f * t;
            chr->unk01C->trans.y += chr->unk06C;
            if (chr->unk06C > 0.0f && chr->unk074 == 0) {
                Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[9], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                chr->unk074 = 1;
            }
            if (lbl_1_data_0->unk5014 == 0 && chr->unk00C++ > 180) {
                chr->unk01C->trans.y = lbl_1_data_E90;
                chr->unk00C = 0;
                chr->unk00A++;
                fn_1_218(fn_1_198(0x632), (chr->unk010 == 0) ? 40 : (chr->unk010 == 1) ? 56 : (chr->unk010 == 2) ? 72 : 88);
            }
            break;
        case 1:
            chr->unk00C++;
            t = 0.8f * (chr->unk00C / 60.0f);
            fn_1_2E08(stage, t);
            chr->unk01C->trans.y += 280.0f * t;
            if (chr->unk00C > 60) {
                chr->unk00C = 0;
                chr->unk00A++;
            }
            break;
        case 2:
            break;
    }
}

/* 133 insns */
void fn_1_44B8(M502_CHAR *chr)
{
    Hu3DMotionSpeedSet(chr->unk01C->mdlId[0], 1.0f);
    if (chr->unk006 == 0) {
        if (chr->unk024.unk024 < 0 && chr->unk060 > 0) {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk060--;
            chr->unk008 = 1;
        } else if (chr->unk024.unk024 > 0 && chr->unk060 < 2) {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk060++;
            chr->unk008 = 2;
        }
    }
    if (chr->unk024.unk020 & PAD_BUTTON_A) {
        Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[3], 0.0f, 2.0f, 0);
        chr->unk068 = 1300.0f;
        chr->unk00C = 0;
        chr->unk008 = 3;
        chr->unk064 = 0;
        chr->unk054 = 0;
    }
    if (chr->unk01C->rot.y < 0.0f) {
        chr->unk01C->rot.y += 15.0f;
    }
    if (chr->unk01C->rot.y > 0.0f) {
        chr->unk01C->rot.y -= 15.0f;
    }
}

/* 106 insns */
void fn_1_46CC(M502_CHAR *chr)
{
    chr->unk01C->trans.x -= 10.0f;
    chr->unk01C->rot.y -= 15.0f;
    chr->unk01C->rot.y = (chr->unk01C->rot.y < -90.0f) ? -90.0f : chr->unk01C->rot.y;
    if (chr->unk024.unk024 > 0 && chr->unk060 < 2) {
        chr->unk060++;
        chr->unk008 = 2;
    } else if (chr->unk01C->trans.x < -300.0f + 300.0f * chr->unk060) {
        if (chr->unk024.unk024 < 0 && chr->unk060 > 0) {
            chr->unk060--;
        } else {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk008 = 0;
        }
    }
}

/* 106 insns */
void fn_1_4874(M502_CHAR *chr)
{
    chr->unk01C->trans.x += 10.0f;
    chr->unk01C->rot.y += 15.0f;
    chr->unk01C->rot.y = (chr->unk01C->rot.y > 90.0f) ? 90.0f : chr->unk01C->rot.y;
    if (chr->unk024.unk024 < 0 && chr->unk060 > 0) {
        chr->unk060--;
        chr->unk008 = 1;
    } else if (chr->unk01C->trans.x > -300.0f + 300.0f * chr->unk060) {
        if (chr->unk024.unk024 > 0 && chr->unk060 < 2) {
            chr->unk060++;
        } else {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk008 = 0;
        }
    }
}

/* 277 insns */
void fn_1_4A1C(M502_CHAR *chr)
{
    if (chr->unk00C == 6) {
        if (chr->unk024.unk01C & PAD_BUTTON_A) {
            chr->unk064 = 1;
        }
        else {
            chr->unk064 = 0;
        }
    }
    if (chr->unk064) {
        chr->unk068 += -1600.0 * (1.0f / 60.0f);
    }
    else {
        chr->unk068 += -7200.0 * (1.0f / 60.0f);
    }
    chr->unk068 = (chr->unk068 < -750.0f) ? -750.0f : chr->unk068;
    chr->unk01C->trans.y += 1.35f * ((1.0f / 60.0f) * chr->unk068);
    fn_1_5384(chr);
    if (chr->unk00C >= 1 && (chr->unk024.unk020 & (PAD_BUTTON_A | PAD_TRIGGER_L)) && chr->unk01C->trans.y > chr->unk058) {
        Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[6], 0.0f, 8.0f, HU3D_MOTATTR_NONE);
        chr->unk00C = 0;
        chr->unk008 = 4;
        chr->unk00A = 0;
        chr->unk05C = chr->unk01C->trans.y;
    }
    if (chr->unk054 && chr->unk01C->trans.y <= chr->unk058) {
        chr->unk01C->trans.y = chr->unk058;
        if (chr->unk024.unk024 < 0 && chr->unk060 > 0 && chr->unk006 == 0) {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk060--;
            chr->unk054 = 0;
            chr->unk008 = 1;
        }
        else if (chr->unk024.unk024 > 0 && chr->unk060 < 2 && chr->unk006 == 0) {
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            chr->unk060++;
            chr->unk054 = 0;
            chr->unk008 = 2;
        }
        else if (chr->unk01C->trans.y <= chr->unk058) {
            HuVecF pos;
            Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
            pos = (HuVecF) { chr->unk01C->trans.x, chr->unk01C->trans.y - 10.0f, chr->unk01C->trans.z };
            CharModelLandDustCreate(chr->unk014, &pos);
            CharFXPlay(chr->unk014, 150);
            chr->unk054 = 0;
            chr->unk008 = 0;
        }
    }
    if (chr->unk01C->rot.y < 0.0f) {
        chr->unk01C->rot.y += 15.0f;
    }
    if (chr->unk01C->rot.y > 0.0f) {
        chr->unk01C->rot.y -= 15.0f;
    }
    chr->unk00C++;
}

/* 325 insns */
s32 fn_1_4E70(M502_CHAR *chr)
{
    s16 x;
    s16 y;
    s16 z;
    float dist;
    s16 n;
    s32 ret = 0;

    switch (chr->unk00A) {
        case 0:
            if (++chr->unk00C >= 15 && Hu3DMotionEndCheck(chr->unk01C->mdlId[0])) {
                chr->unk00A = 1;
            }
            break;
        case 1:
            if (chr->unk070) {
                chr->unk070--;
            }
            else {
                chr->unk01C->trans.y += -36.5f;
            }
            fn_1_5384(chr);
            if (chr->unk054 && chr->unk01C->trans.y <= chr->unk058) {
                chr->unk01C->trans.y = chr->unk058;
                chr->unk00A = 2;
                fn_1_561C(chr, &x, &y, &z);
                dist = (chr->unk05C - chr->unk01C->trans.y >= 0.0f) ? chr->unk05C - chr->unk01C->trans.y : -(chr->unk05C - chr->unk01C->trans.y);
                n = (dist > 220.0f) ? 3 : (dist > 145.0f) ? 2 : 1;
                chr->unk078 = n;
                if (fn_1_70B0(&chr->unk000->unk008, x, y, z, n)) {
                    chr->unk054 = 0;
                    chr->unk00A = 3;
                }
                else {
                    Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[8], 0.0f, 0.0f, HU3D_MOTATTR_NONE);
                }
            }
            break;
        case 2:
            if (Hu3DMotionEndCheck(chr->unk01C->mdlId[0])) {
                if (chr->unk024.unk024 < 0 && chr->unk060 > 0 && chr->unk006 == 0) {
                    Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                    chr->unk060--;
                    chr->unk054 = 0;
                    chr->unk008 = 1;
                }
                else if (chr->unk024.unk024 > 0 && chr->unk060 < 2 && chr->unk006 == 0) {
                    Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[2], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                    chr->unk060++;
                    chr->unk054 = 0;
                    chr->unk008 = 2;
                }
                else if (chr->unk01C->trans.y <= chr->unk058) {
                    Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[0], 0.0f, 4.0f, HU3D_MOTATTR_LOOP);
                    chr->unk054 = 0;
                    chr->unk008 = 0;
                }
            }
            break;
        case 3:
            if (chr->unk070) {
                chr->unk070--;
            }
            else {
                chr->unk01C->trans.y += -36.5f;
            }
            fn_1_5384(chr);
            if (chr->unk054 && chr->unk01C->trans.y <= chr->unk058) {
                chr->unk01C->trans.y = chr->unk058;
                Hu3DMotionShiftSet(chr->unk01C->mdlId[0], chr->unk01C->mtnId[8], 0.0f, 0.0f, HU3D_MOTATTR_NONE);
                ret = 1;
                chr->unk00A = 2;
            }
            break;
    }
    if (chr->unk01C->rot.y < 0.0f) {
        chr->unk01C->rot.y += 15.0f;
    }
    if (chr->unk01C->rot.y > 0.0f) {
        chr->unk01C->rot.y -= 15.0f;
    }
    chr->unk00C++;
    return ret;
}

/* 99 insns */
void fn_1_5384(M502_CHAR *chr)
{
    s16 x;
    s16 y;
    s16 z;
    HuVecF pos = (HuVecF) { 0.0f, 0.0f, 0.0f };
    M502_BLOCK *block = &chr->unk000->unk008;
    M502_BLOCKCELL *cell;

    if (chr->unk054 == 0) {
        fn_1_561C(chr, &x, &y, &z);
        if (x < 3) {
            cell = &block->unk004[x][z + y * 3];
            if (cell->unk004 != 0 && cell->unk00C >= 10000) {
                fn_1_6CFC(x, y, z, &pos);
                chr->unk054 = 1;
                chr->unk058 = pos.y;
            }
        }
        else if (x == 7) {
            chr->unk054 = 1;
            chr->unk058 = 300.0f * (s16)(chr->unk01C->trans.y / 300.0f);
        }
    }
}

/* 67 insns */
void fn_1_5510(M502_CHAR *chr)
{
    chr->unk000->unk1048.unk028.x = chr->unk000->unk1048.unk034.x = chr->unk000->unk1048.unk010.x = chr->unk000->unk1048.unk01C.x = chr->unk01C->trans.x;
    if (chr->unk01C->trans.y > lbl_1_data_E94) {
        chr->unk000->unk1048.unk01C.y = chr->unk01C->trans.y - 70.0f;
        chr->unk000->unk1048.unk010.y = 300.0f + chr->unk01C->trans.y;
    }
    else {
        chr->unk000->unk1048.unk01C.y = lbl_1_data_E94 - 70.0f;
        chr->unk000->unk1048.unk010.y = 300.0f + lbl_1_data_E94;
    }
    if (chr->unk006 == 0) {
        chr->unk000->unk1048.unk010.z = 4550.0f;
    }
    else {
        chr->unk000->unk1048.unk010.z = 3500.0f;
    }
}

/* 102 insns */
void fn_1_561C(M502_CHAR *chr, s16 *x, s16 *y, s16 *z)
{
    HuVecF pos;

    pos.x = chr->unk01C->trans.x;
    pos.y = chr->unk01C->trans.y;
    pos.z = chr->unk01C->trans.z;
    pos.y -= 150.0f;
    pos.x = 300.0f * (s16)(pos.x / 300.0f);
    pos.y = 300.0f * (s16)(pos.y / 300.0f);
    pos.z = 300.0f * (s16)(pos.z / 300.0f);
    fn_1_6E1C(&pos, x, y, z);
}

/* 25 insns */
void fn_1_57B4(M502_INPUTCOM *com, s32 playerNo, M502_INPUT *in)
{
    memset(com, 0, sizeof(M502_INPUTCOM));
    com->unk000 = in;
    com->unk00C = GwPlayerConf[playerNo].type;
}

/* 12 insns */
void fn_1_5818(M502_INPUTCOM *com)
{
    memset(com, 0, sizeof(M502_INPUTCOM));
}

/* 38 insns */
void fn_1_5848(M502_INPUTCOM *com)
{
    M502_INPUT *in = com->unk000;
    M502_CHAR *chr = in->unk000;

    if (com->unk00C != 0 && chr->unk004 == 1) {
        in->unk01C = in->unk020 = in->unk024 = 0;
        if (com->unk004 == 0) {
            fn_1_58E0(com);
        }
        else if (com->unk004 == 1) {
            fn_1_5EB8(com);
        }
    }
}

