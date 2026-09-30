/*
 * m577Dll m577.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m577Dll/asm/REL/m577Dll/m577.s.
 */

#include "REL/m577Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/wipe.h"
#include "game/mg/seqman.h"

#include "math.h"
#include "game/charman.h"
#include "game/esprite.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ const u16 lbl_1_rodata_10[4] = { 1, 2, 4, 8 }; /* camera bits (fork B: 0x3D48 lhz) */
/* 0x18 */ /* float lbl_1_rodata_18 = -30.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 30.0f; */
/* 0x20 */ /* float lbl_1_rodata_20 = 150.0f; */
/* 0x28 */ /* double lbl_1_rodata_28 = -20; */
/* 0x30 */ /* double lbl_1_rodata_30 = 1; */
/* 0x38 */ /* double lbl_1_rodata_38 = 3.141592653589793; */
/* 0x40 */ /* float lbl_1_rodata_40 = 90.0f; */
/* 0x48 */ /* double lbl_1_rodata_48 = 180; */
/* 0x50 */ /* double lbl_1_rodata_50 = 16000; */
/* 0x58 */ /* float lbl_1_rodata_58 = -1.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 1.0f; */
/* 0x60 */ /* float lbl_1_rodata_60 = 640.0f; */
/* 0x64 */ /* float lbl_1_rodata_64 = 320.0f; */
/* 0x68 */ /* double lbl_1_rodata_68 = 4503601774854144; */
/* 0x70 */ /* float lbl_1_rodata_70 = 0.0f; */
/* 0x74 */ /* float lbl_1_rodata_74 = 5.0f; */
/* 0x78 */ /* float lbl_1_rodata_78 = 60.0f; */
/* 0x7C */ /* float lbl_1_rodata_7C = 180.0f; */
/* 0x80 */ /* float lbl_1_rodata_80 = 100.0f; */
/* 0x84 */ /* float lbl_1_rodata_84 = 250.0f; */
/* 0x88 */ /* float lbl_1_rodata_88 = -250.0f; */
/* 0x8C */ /* float lbl_1_rodata_8C = 15.0f; */
/* 0x90 */ /* float lbl_1_rodata_90 = 20.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = 40000.0f; */
/* 0x98 */ /* float lbl_1_rodata_98 = 1.2f; */
/* 0x9C */ /* float lbl_1_rodata_9C = 480.0f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 0.5f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 4000.0f; */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 0.6f; */
/* 0xAC */ /* float lbl_1_rodata_AC = 300.0f; */
/* 0xB0 */ /* float lbl_1_rodata_B0 = 1000.0f; */
/* 0xB4 */ /* float lbl_1_rodata_B4 = 0.9f; */
/* 0xB8 */ /* s32 lbl_1_rodata_B8[3] = { 0x00000000, 0x3F800000, 0x00000000 }; */
/* 0xC4 */ /* s32 lbl_1_rodata_C4[3] = { 0x00000000, 0x45FA0000, 0x00000000 }; */
/* 0xD0 */ /* s32 lbl_1_rodata_D0[3] = { 0x3DCCCCCD, 0x00000000, 0x00000000 }; */
/* 0xDC */ /* float lbl_1_rodata_DC = 3000.0f; */
/* 0xE0 */ /* float lbl_1_rodata_E0 = 360.0f; */
/* 0xE4 */ /* float lbl_1_rodata_E4 = 800.0f; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 288.0f; */
/* 0xEC */ /* float lbl_1_rodata_EC = 240.0f; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = -16000.0f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 0.05f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 0.99f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 400.0f; */
/* 0x100 */ /* double lbl_1_rodata_100 = 0.5; */
/* 0x108 */ /* double lbl_1_rodata_108 = 3; */
/* 0x110 */ /* float lbl_1_rodata_110 = 0.98f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 40.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 0.8f; */
/* 0x11C */ /* s16 lbl_1_rodata_11C[3] = { 0x0019, 0x003C, 0x0064 }; */
/* 0x122 */ /* s16 lbl_1_rodata_122[3] = { 0x0023, 0x0046, 0x0064 }; */
/* 0x128 */ /* float lbl_1_rodata_128 = -400.0f; */
/* 0x130 */ /* double lbl_1_rodata_130 = 30; */
/* 0x138 */ /* float lbl_1_rodata_138 = 1680.0f; */
/* 0x13C */ /* s16 lbl_1_rodata_13C[4] = { 0x0003, 0x0002, 0x0001, 0x0001 }; */
/* 0x144 */ /* s16 lbl_1_rodata_144[4] = { 0x0000, 0x0001, 0x0002, 0x0000 }; */
/* 0x14C */ /* float lbl_1_rodata_14C = 10.0f; */
/* 0x150 */ /* float lbl_1_rodata_150 = 22.5f; */
/* 0x154 */ /* float lbl_1_rodata_154 = 55.0f; */
/* 0x158 */ /* float lbl_1_rodata_158 = 80.0f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 16.25f; */
/* 0x160 */ /* float lbl_1_rodata_160 = 57.38f; */
/* 0x164 */ /* float lbl_1_rodata_164 = 0.3f; */
/* 0x168 */ /* float lbl_1_rodata_168 = -10.0f; */
/* 0x16C */ /* float lbl_1_rodata_16C = -9.0f; */
/* 0x170 */ /* float lbl_1_rodata_170 = -8.5f; */
/* 0x174 */ /* float lbl_1_rodata_174 = 9.0f; */
/* 0x178 */ /* float lbl_1_rodata_178 = 8.5f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 0.1f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 0.2f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 0.25f; */
/* 0x188 */ /* float lbl_1_rodata_188 = -0.3f; */
/* 0x18C */ /* float lbl_1_rodata_18C = 75.0f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 0.97f; */
/* 0x198 */ /* double lbl_1_rodata_198 = 273.94686980565; */
/* 0x1A0 */ /* float lbl_1_rodata_1A0 = -180.0f; */
/* 0x1A4 */ /* float lbl_1_rodata_1A4 = 700.0f; */
/* 0x1A8 */ /* float lbl_1_rodata_1A8 = 48.0f; */
/* 0x1AC */ /* float lbl_1_rodata_1AC = 16.0f; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 8191.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = -20000.0f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 20000.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 3.0f; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = -10000.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 10000.0f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8 = 1.5f; */
/* 0x1D0 */ /* double lbl_1_rodata_1D0 = 19.7118514397737; */
/* 0x1D8 */ /* float lbl_1_rodata_1D8 = 0.000001f; */
/* 0x1DC */ /* float lbl_1_rodata_1DC = 72.0f; */
/* 0x1E0 */ /* float lbl_1_rodata_1E0 = 120.0f; */
/* 0x1E4 */ /* float lbl_1_rodata_1E4 = 276.0f; */

/* --- .data --- */
/* 0x0 */ MGSEQ_PARAM lbl_1_data_0 = { 300, 0, fn_1_1F4, fn_1_314, fn_1_798, fn_1_7EC, fn_1_B0C, fn_1_BF8, fn_1_1600, fn_1_1790, fn_1_17CC };
/* 0x28 */ s32 lbl_1_data_28[13][9] = { 0x008C0000, 0x00870076, 0x00870075, 0x008C000A, 0x008C0009, 0x00870074, 0x008C0030, 0x008C0031, 0x008C0001, 0x00330000, 0x002E0076, 0x002E0075, 0x0033000A, 0x00330009, 0x002E0074, 0x00330030, 0x00330031, 0x00330001, 0x00B70000, 0x00B20076, 0x00B20075, 0x00B7000A, 0x00B70009, 0x00B20074, 0x00B70030, 0x00B70031, 0x00B70001, 0x00ED0000, 0x00E80076, 0x00E80075, 0x00ED000A, 0x00ED0009, 0x00E80074, 0x00ED0030, 0x00ED0031, 0x00ED0001, 0x00E60000, 0x00E10076, 0x00E10075, 0x00E6000A, 0x00E60009, 0x00E10074, 0x00E60030, 0x00E60031, 0x00E60001, 0x00170000, 0x00120076, 0x00120075, 0x0017000A, 0x00170009, 0x00120074, 0x00170030, 0x00170031, 0x00170001, 0x00E00000, 0x00DB0076, 0x00DB0075, 0x00E0000A, 0x00E00009, 0x00DB0074, 0x00E00030, 0x00E00031, 0x00E00001, 0x002D0000, 0x00280076, 0x00280075, 0x002D000A, 0x002D0009, 0x00280074, 0x002D0030, 0x002D0031, 0x002D0001, 0x00C90000, 0x00C40076, 0x00C40075, 0x00C9000A, 0x00C90009, 0x00C40074, 0x00C90030, 0x00C90031, 0x00C90001, 0x00B00000, 0x009C0076, 0x009C0075, 0x00B0000A, 0x00B00009, 0x009C0074, 0x00B00030, 0x00B00031, 0x00B00001, 0x00B00000, 0x009C0076, 0x009C0075, 0x00B0000A, 0x00B00009, 0x009C0074, 0x00B00030, 0x00B00031, 0x00B00001, 0x00B00000, 0x009C0076, 0x009C0075, 0x00B0000A, 0x00B00009, 0x009C0074, 0x00B00030, 0x00B00031, 0x00B00001, 0x00B00000, 0x009C0076, 0x009C0075, 0x00B0000A, 0x00B00009, 0x009C0074, 0x00B00030, 0x00B00031, 0x00B00001 };
/* 0x1FC */ s32 lbl_1_data_1FC[25] = { 0x00840000, 0x00840001, 0x00840002, 0x00840003, 0x00840004, 0x00840005, 0x00840006, 0x00840007, 0x00840008, 0x00840009, 0x0084000A, 0x0084000B, 0x0084000C, 0x00840011, 0x0084000D, 0x0084000E, 0x0084000F, 0x00840010, 0x00840012, 0x00840013, 0x00840014, 0x00840015, 0x00840016, 0x00840017, 0x00840018 };
/* 0x260 */ s32 lbl_1_data_260[4] = { 0x00840019, 0x0084001A, 0x0084001B, 0x0084001C };
/* 0x270 */ float lbl_1_data_270[2][6] = { 0.0f, 0.0f, -974.0f, 90.0f, 21.0f, 7840.0f, 0.0f, 0.0f, 1118.0f, 270.0f, 20.0f, 5010.0f };
/* 0x2A0 */ s32 lbl_1_data_2A0[2] = { 0x00000000, 0x00000000 };
/* 0x2A8 */ s32 lbl_1_data_2A8[13] = { 0x000001FD, 0x000001E9, 0x00000261, 0x000002B1, 0x00000289, 0x000001C1, 0x0000029D, 0x000001D5, 0x00000275, 0x00000239, 0x0000024D, 0x00000225, 0x00000211 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x10 */ OMOBJMAN *lbl_1_bss_10;
/* 0xC */ OMOBJ *lbl_1_bss_C; /* ->data is M577_WORK (fork B: 0x34F8) */
/* 0x8 */ s32 lbl_1_bss_8; /* HuAudBGMPlay id */
/* 0x0 */ s32 lbl_1_bss_0[2]; /* HuAudFXPlay ids */

/* --- functions (reference order) --- */
/* 85 insns. */
void ObjectSetup(void)
{
    OMOBJ *obj;
    M577_WORK *work;
    s32 i;

    lbl_1_bss_10 = omInitObjMan(10, 0x2000);
    omGameSysInit(lbl_1_bss_10);
    obj = omAddObjEx(lbl_1_bss_10, 0x65, 0, 0, -1, fn_1_1BC8);
    lbl_1_bss_C = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M577_WORK), HU_MEMNUM_OVL);
    work = obj->data;
    work->unk1B66 = 0;
    fn_1_1DD8(work);
    fn_1_1D50(work);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_10, 0x64, 1, 9, 0, fn_1_1870);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M577_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
        work->unk000[i] = obj->data;
    }
    fn_1_1CF4(work);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(TRUE);
    MgSeqCreate(&lbl_1_data_0);
}

/* 72 insns. MGSEQ init hook. */
void fn_1_1F4(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;

    work->unk1B66 = 0;
    work->unk1B60 = 0;
    fn_1_286C(work);
    fn_1_3AB8(work);
    fn_1_1FEC(&work->unkA58);
    work->unk920[0].unk00C = lbl_1_data_270[0][3];
    work->unk920[0].unk010 = lbl_1_data_270[0][4];
    work->unk920[0].unk014 = lbl_1_data_270[0][5];
    work->unk920[0].unk000.x = lbl_1_data_270[0][0];
    work->unk920[0].unk000.y = lbl_1_data_270[0][1];
    work->unk920[0].unk000.z = lbl_1_data_270[0][2];
    work->unk920[1].unk00C = lbl_1_data_270[0][3];
    work->unk920[1].unk010 = lbl_1_data_270[0][4];
    work->unk920[1].unk014 = lbl_1_data_270[0][5];
    work->unk920[1].unk000.x = lbl_1_data_270[0][0];
    work->unk920[1].unk000.y = lbl_1_data_270[0][1];
    work->unk920[1].unk000.z = lbl_1_data_270[0][2];
    MgSeqModeNext();
}

/* 289 insns. MGSEQ start hook: camera sweep over the course, then open the split screen. */
void fn_1_314(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;
    M577_CART *cart;
    float t;
    float angle;
    float y;
    float z;

    switch (work->unk1B60) {
    case 0:
        MgSeqModeChangeOff();
        work->unk1B64 = 0;
        work->unk1B62 = 0;
        cart = work->unk010[0].unk000[0]->unk020;
        cart->unk020.y -= -30.0f;
        cart->unk040->unk000.y -= 30.0f;
        Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
        Hu3DModelPosSetV(cart->unk060, &cart->unk020);
        Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
        Hu3DModelPosSetV(cart->unk040->unk02C, &cart->unk040->unk000);
        HuAudFXPlay(0x940);
        work->unk1B60++;
    case 1:
        work->unk1B62++;
        if (work->unk1B62 == 150) {
            work->unk1B60++;
        }
        t = work->unk1B62 / 150.0f;
        angle = -20.0 * (1.0 - HuSin(90.0f * t));
        z = 16000.0 * -HuSin(angle);
        y = 16000.0 * HuCos(angle) - 16000.0;
        work->unk920[0].unk000.y = y + lbl_1_data_270[0][1];
        work->unk920[0].unk000.z = z + lbl_1_data_270[0][2];
        work->unk920[0].unk010 = angle + lbl_1_data_270[0][4];
        if (work->unk1B62 > 60 && work->unk1B62 <= 90) {
            cart = work->unk010[0].unk000[0]->unk020;
            cart->unk020.y += -1.0f;
            cart->unk040->unk000.y += 1.0f;
            Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
            Hu3DModelPosSetV(cart->unk060, &cart->unk020);
            Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
            Hu3DModelPosSetV(cart->unk040->unk02C, &cart->unk040->unk000);
        }
        break;
    case 2:
        work->unk1B62 = 0;
        work->unk1B60++;
    case 3:
        work->unk1B62++;
        if (work->unk1B62 == 30) {
            work->unk1B60++;
        }
        t = work->unk1B62 / 30.0f;
        work->unkA58.unk000 = 640.0f * (1.0f - t) + 320.0f * t;
        break;
    case 4:
        espAttrReset(work->unk1B58, 4);
        espAttrReset(work->unk1B5A, 4);
        espAttrReset(work->unk1B5C, 4);
        work->unk1B62 = 0;
        work->unk1B60++;
    case 5:
        work->unk1B62++;
        if (work->unk1B62 == 30) {
            work->unk1B60++;
        }
        break;
    case 6:
        lbl_1_bss_8 = HuAudBGMPlay(0x34);
        Hu3DModelAttrSet(work->unk990[0].unk00C, 1);
        Hu3DModelAttrSet(work->unk990[1].unk00C, 1);
        MgSeqModeNext();
        break;
    }
    fn_1_2044(&work->unkA58);
}

/* 21 insns. */
void fn_1_798(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;

    switch (work->unk1B64) {
    case 0:
        work->unk1B60 = 0;
        work->unk1B64++;
    case 1:
        break;
    }
}

/* 200 insns. MGSEQ main hook: start both teams, stop when one reaches the goal. */
void fn_1_7EC(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;
    M577_TEAM *team;
    float rate0;
    float rate1;

    switch (work->unk1B60) {
    case 0:
        Hu3DModelAttrReset(work->unk990[0].unk010, 0x40000002);
        Hu3DModelAttrReset(work->unk990[1].unk010, 0x40000002);
        HuAudFXPlayPan(0x941, 48);
        fn_1_26C0(&work->unk0A8, fn_1_B3CC, &work->unk990[1].unk058);
        work->unk990[1].unk058 = 0;
        work->unk010[0].unk02C = fn_1_72D0;
        work->unk010[1].unk02C = fn_1_7D24;
        work->unk1B64 = 0;
        work->unk1B66 = 1;
        work->unk1B60++;
    case 1:
        team = &work->unk010[0];
        rate0 = team->unk03C / team->unk028->unk008;
        team = &work->unk010[1];
        rate1 = team->unk03C / team->unk028->unk008;
        if (rate0 >= 1.0f || rate1 >= 1.0f) {
            if (rate0 >= 1.0f && rate1 >= 1.0f) {
                Hu3DModelAttrReset(work->unk990[0].unk012, 0x40000002);
                Hu3DModelAttrReset(work->unk990[1].unk012, 0x40000002);
                HuAudFXPlayPan(0x941, 48);
                fn_1_26C0(&work->unk0A8, fn_1_B3CC, &work->unk990[1].unk05A);
                work->unk990[1].unk05A = 0;
                if (rate0 > rate1) {
                    work->unk1B5E = 0;
                    work->unk010[work->unk1B5E ^ 1].unk04A = 1;
                } else if (rate1 < rate0) {
                    /* retail: same test as above, so a trio lead on the same frame is a draw */
                    work->unk1B5E = 1;
                    work->unk010[work->unk1B5E ^ 1].unk04A = 1;
                } else {
                    work->unk1B5E = -1;
                    work->unk010[0].unk02C = fn_1_9380;
                    work->unk010[1].unk02C = fn_1_9C08;
                    work->unk010[0].unk04A = 1;
                    work->unk010[1].unk04A = 1;
                }
            } else {
                if (rate0 >= 1.0f) {
                    work->unk1B5E = 0;
                    Hu3DModelAttrReset(work->unk990[0].unk012, 0x40000002);
                    Hu3DModelAttrReset(work->unk990[0].unk056, 0x40000002);
                    Hu3DModelAttrReset(work->unk990[0].unk056, 1);
                    HuAudFXPlayPan(0x941, 48);
                } else {
                    work->unk1B5E = 1;
                    Hu3DModelAttrReset(work->unk990[1].unk012, 0x40000002);
                    Hu3DModelAttrReset(work->unk990[1].unk056, 0x40000002);
                    Hu3DModelAttrReset(work->unk990[1].unk056, 1);
                    fn_1_26C0(&work->unk0A8, fn_1_B3CC, &work->unk990[1].unk05A);
                    work->unk990[1].unk05A = 0;
                }
                work->unk010[work->unk1B5E ^ 1].unk04A = 1;
            }
            work->unk1B66 = 0;
            MgSeqModeNext();
        }
        break;
    }
}

/* 59 insns. MGSEQ finish hook: winners. */
void fn_1_B0C(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;

    switch (work->unk1B64) {
    case 0:
        work->unk1B66 = 0;
        if (work->unk1B5E < 0) {
            MgSeqWinnerSet(-1, -1, -1, -1);
        } else if (work->unk1B5E == 0) {
            MgSeqWinnerSet(work->unk010[0].unk000[0]->unk03A, -1, -1, -1);
        } else {
            MgSeqWinnerSet(work->unk010[1].unk000[0]->unk03A, work->unk010[1].unk000[1]->unk03A, work->unk010[1].unk000[2]->unk03A, -1);
        }
        HuAudSStreamFadeOut(lbl_1_bss_8, 1000);
        work->unk1B60 = 0;
        work->unk1B64++;
    case 1:
        break;
    }
}

/* 642 insns. MGSEQ finish hook: result presentation. */
void fn_1_BF8(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;
    M577_TEAM *team;
    s32 i;
    M577_PLAYER *player;
    float t;

    switch (work->unk1B60) {
    case 0:
        MgSeqModeChangeOff();
        work->unk1B64 = 0;
        if (work->unk1B5E < 0) {
            work->unk1B60 = 1;
            work->unk010[0].unk04A = 1;
            work->unk010[1].unk04A = 1;
        } else {
            work->unk1B60 = 4;
        }
        break;
    case 1:
        if (work->unk010[0].unk02C == fn_1_703C && work->unk010[1].unk02C == fn_1_703C) {
            for (i = 0; i < 4; i++) {
                player = work->unk000[i];
                player->unk034 = 1;
                CharMotionShiftSet(player->unk03A, player->unk018->mtnId[8], 0.0f, 5.0f, 0x40000001);
            }
            work->unk1B62 = 0;
            work->unk1B60++;
        }
        break;
    case 2:
        work->unk1B62++;
        if (work->unk1B62 == 60) {
            work->unk1B60++;
        }
        t = work->unk1B62 / 60.0f;
        for (i = 0; i < 4; i++) {
            player = work->unk000[i];
            player->unk00C.y = 180.0f * t;
            Hu3DModelRotSetV(player->unk036, &player->unk00C);
            omSetRot(player->unk018, player->unk00C.x, player->unk00C.y, player->unk00C.z);
        }
        break;
    case 3:
        MgSeqModeNext();
        break;
    case 4:
        if (work->unk010[work->unk1B5E ^ 1].unk02C == fn_1_703C) {
            if (work->unk1B5E == 0) {
                if (work->unk010[0].unk02C == fn_1_9380) {
                    work->unk1B60++;
                }
            } else if (work->unk010[1].unk02C == fn_1_9C08) {
                work->unk1B60++;
            }
        }
        break;
    case 5:
        for (i = 0; i < 4; i++) {
            player = work->unk000[i];
            player->unk034 = 1;
        }
        WipeColorSet(255, 255, 255);
        WipeCreate(2, 0, 60);
        work->unk1B64 = 0;
        work->unk1B60++;
    case 6:
        if (!WipeCheckEnd()) {
            work->unk1B60++;
        }
        break;
    case 7:
        team = &work->unk010[work->unk1B5E ^ 1];
        for (i = 0; i < team->unk042; i++) {
            Hu3DModelAttrSet(team->unk00C[i]->unk05C, 1);
            Hu3DModelAttrSet(team->unk00C[i]->unk060, 1);
        }
        if (work->unk1B5E == 1) {
            Hu3DModelAttrSet(team->unk00C[0]->unk040->unk028, 1);
            Hu3DModelAttrSet(team->unk00C[0]->unk040->unk02C, 1);
        }
        Hu3DModelAttrSet(team->unk01C->unk004, 1);
        Hu3DModelAttrSet(team->unk01C->unk006, 1);
        Hu3DModelAttrSet(team->unk01C->unk008, 1);
        Hu3DModelAttrSet(team->unk01C->unk00A, 1);
        Hu3DModelAttrSet(team->unk01C->unk00C, 1);
        Hu3DModelAttrSet(team->unk01C->unk00E, 1);
        Hu3DModelAttrSet(team->unk01C->unk010, 1);
        Hu3DModelAttrSet(team->unk01C->unk012, 1);
        Hu3DModelAttrSet(team->unk01C->unk014, 1);
        Hu3DModelAttrSet(team->unk01C->unk016, 1);
        Hu3DModelAttrSet(team->unk01C->unk018, 1);
        Hu3DModelAttrSet(team->unk01C->unk01A, 1);
        Hu3DModelAttrSet(team->unk01C->unk01C, 1);
        Hu3DModelAttrSet(team->unk01C->unk01E, 1);
        Hu3DModelAttrSet(team->unk01C->unk020, 1);
        Hu3DModelAttrSet(team->unk01C->unk038, 1);
        Hu3DModelAttrSet(team->unk01C->unk03A, 1);
        for (i = 0; i < 11; i++) {
            Hu3DModelAttrSet(team->unk01C->unk022[i], 1);
        }
        team = &work->unk010[work->unk1B5E];
        Hu3DModelAttrSet(team->unk01C->unk004, 1);
        Hu3DModelAttrSet(team->unk01C->unk006, 1);
        Hu3DModelAttrSet(team->unk01C->unk008, 1);
        Hu3DModelAttrSet(team->unk01C->unk00A, 1);
        Hu3DModelAttrSet(team->unk01C->unk00C, 1);
        Hu3DModelAttrSet(team->unk01C->unk00E, 1);
        Hu3DModelAttrSet(team->unk01C->unk010, 1);
        Hu3DModelAttrSet(team->unk01C->unk012, 1);
        Hu3DModelAttrSet(team->unk01C->unk014, 1);
        Hu3DModelAttrSet(team->unk01C->unk016, 1);
        Hu3DModelAttrSet(team->unk01C->unk018, 1);
        Hu3DModelAttrSet(team->unk01C->unk01A, 1);
        Hu3DModelAttrSet(team->unk01C->unk01C, 1);
        Hu3DModelAttrSet(team->unk01C->unk01E, 1);
        Hu3DModelAttrSet(team->unk01C->unk020, 1);
        Hu3DModelAttrSet(team->unk01C->unk038, 1);
        Hu3DModelAttrSet(team->unk01C->unk03A, 1);
        for (i = 0; i < 11; i++) {
            Hu3DModelAttrSet(team->unk01C->unk022[i], 1);
        }
        espAttrSet(work->unk1B58, 4);
        espAttrSet(work->unk1B5A, 4);
        espAttrSet(work->unk1B5C, 4);
        Hu3DModelAttrReset(work->unk1B68[13], 1);
        Hu3DModelRotSet(work->unk1B68[11], 0.0f, 180.0f, 0.0f);
        if (work->unk1B5E == 0) {
            work->unkA58.unk000 = 640.0f;
            team->unk02C = fn_1_A36C;
            team->unk000[0]->unk020->unk020.x = 0.0f;
            team->unk000[0]->unk020->unk040->unk000.x = 100.0f;
            Hu3DModelPosSetV(team->unk00C[0]->unk05C, &team->unk00C[0]->unk020);
            Hu3DModelPosSetV(team->unk00C[0]->unk040->unk028, &team->unk00C[0]->unk040->unk000);
            fn_1_AA4C(work);
            fn_1_2E08(&work->unkC04[0]);
        } else {
            work->unkA58.unk000 = 0.0f;
            team->unk02C = fn_1_A5CC;
            team->unk000[0]->unk020->unk020.x = 250.0f;
            team->unk000[1]->unk020->unk020.x = 0.0f;
            team->unk000[2]->unk020->unk020.x = -250.0f;
            Hu3DModelPosSetV(team->unk00C[0]->unk05C, &team->unk00C[0]->unk020);
            Hu3DModelPosSetV(team->unk00C[1]->unk05C, &team->unk00C[1]->unk020);
            Hu3DModelPosSetV(team->unk00C[2]->unk05C, &team->unk00C[2]->unk020);
            fn_1_AA4C(work);
            for (i = 0; i < 120; i++) {
                fn_1_2E08(&work->unkC04[1]);
                fn_1_2E08(&work->unkC04[2]);
            }
        }
        Hu3DCameraPerspectiveSet(lbl_1_rodata_10[work->unk1B5E], 15.0f, 20.0f, 40000.0f, 1.2f);
        Hu3DCameraViewportSet(lbl_1_rodata_10[work->unk1B5E], 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(lbl_1_rodata_10[work->unk1B5E], 0, 0, 640, 480);
        fn_1_2044(&work->unkA58);
        team->unk018->unk00C = lbl_1_data_270[1][3];
        team->unk018->unk010 = lbl_1_data_270[1][4];
        team->unk018->unk014 = lbl_1_data_270[1][5];
        team->unk018->unk000.x = lbl_1_data_270[1][0];
        team->unk018->unk000.y = lbl_1_data_270[1][1];
        team->unk018->unk000.z = lbl_1_data_270[1][2];
        for (i = 0; i < team->unk042; i++) {
            if (team->unk000[i]->unk03A == 3) {
                team->unk000[i]->unk000.z -= 100.0f;
                Hu3DModelPosSetV(team->unk000[i]->unk036, &team->unk000[i]->unk000);
                omSetTra(team->unk000[i]->unk018, team->unk000[i]->unk000.x, team->unk000[i]->unk000.y, team->unk000[i]->unk000.z);
            }
        }
        WipeCreate(1, 0, 60);
        work->unk1B60++;
    case 8:
        fn_1_B26C(work);
        if (!WipeCheckEnd()) {
            MgSeqModeNext();
        }
        break;
    }
}

/*
 * .data 0x31C..0x392 follows the two switch jumptables (0x2DC fn_1_314, 0x2F8 fn_1_BF8),
 * so these are defined after fn_1_BF8.
 */
/* 0x31C */ char lbl_1_data_31C[] = "mark03";
/* 0x323 */ char lbl_1_data_323[] = "mark00";
/* 0x32C */ float lbl_1_data_32C[11][2] = { { -8.12679958f, -449.322998f }, { -11.2950001f, 158.764801f }, { -16.8069992f, -784.302002f }, { -21.9995003f, 398.871399f }, { -27.7329998f, -281.359985f }, { -36.1194992f, 449.917389f }, { -51.4510002f, 42.5299988f }, { -58.6049995f, 17.1205006f }, { -67.7900009f, 122.051598f }, { -71.5715027f, -360.485992f }, { -79.3560028f, 265.965607f } };
/* 0x384 */ char lbl_1_data_384[] = "mark02";
/* 0x38B */ char lbl_1_data_38B[] = "mark01";

/* 100 insns. MGSEQ close hook: result motions, coin bonus, lose voices. */
void fn_1_1600(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;
    M577_PLAYER *player;
    s32 i;
    s32 num;

    fn_1_B26C(work);
    switch (work->unk1B64) {
    case 0:
        if (work->unk1B5E < 0) {
            for (i = 0; i < 4; i++) {
                player = work->unk000[i];
                CharMotionShiftSet(player->unk03A, player->unk018->mtnId[7], 0.0f, 5.0f, 0);
            }
            CharLoseVoicePlay(work->unk000[0]->unk03A, work->unk000[1]->unk03A, work->unk000[2]->unk03A, work->unk000[3]->unk03A);
        } else {
            if (work->unk1B5E == 0) {
                num = 1;
            } else {
                num = 3;
            }
            for (i = 0; i < num; i++) {
                player = work->unk010[work->unk1B5E].unk000[i];
                GWMgCoinBonusSet(player->unk038, 10);
                CharMotionShiftSet(player->unk03A, player->unk018->mtnId[6], 0.0f, 5.0f, 0);
            }
        }
        work->unk1B64++;
    case 1:
        break;
    }
}

/* 15 insns. */
void fn_1_1790(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;

    fn_1_B26C(work);
}

/* 41 insns. MGSEQ exit hook. */
void fn_1_17CC(s16 mode, s16 frameNo)
{
    M577_WORK *work = lbl_1_bss_C->data;
    s32 i;

    fn_1_225C(&work->unkA58);
    if (work->unk1B58 >= 0) {
        espKill(work->unk1B58);
    }
    if (work->unk1B5A >= 0) {
        espKill(work->unk1B5A);
    }
    if (work->unk1B5C >= 0) {
        espKill(work->unk1B5C);
    }
    for (i = 0; i < 5; i++) {
        fn_1_B71C(&work->unk1B04[i]);
    }
}

/* 180 insns. Player object init (installed by ObjectSetup). */
void fn_1_1870(OMOBJ *obj)
{
    M577_PLAYER *player = obj->data;
    M577_WORK *work = lbl_1_bss_C->data;
    s32 i;

    player->unk038 = obj->work[0];
    player->unk03A = GwPlayerConf[player->unk038].charNo;
    player->unk03C = GwPlayerConf[player->unk038].grp;
    player->unk03E = GwPlayerConf[player->unk038].padNo;
    player->unk044 = GwPlayerConf[player->unk038].type;
    player->unk046 = GwPlayerConf[player->unk038].dif;
    player->unk018 = obj;
    work->unk000[player->unk038] = player;
    obj->mdlId[0] = CharModelCreate(player->unk03A, 8);
    player->unk036 = obj->mdlId[0];
    for (i = 0; i < 9; i++) {
        obj->mtnId[i] = CharMotionCreate(player->unk03A, lbl_1_data_28[player->unk03A][i]);
    }
    CharMotionSet(player->unk03A, obj->mtnId[2]);
    CharModelAttrSet(player->unk03A, 0x40000002);
    player->unk028 = CharMotionMaxTimeGet(player->unk03A);
    player->unk02C = 0.5f;
    CharMotionTimeSet(player->unk03A, player->unk028 * player->unk02C);
    CharMotionUpdateSet(player->unk03A, 0x8C000A, FALSE);
    CharMotionUpdateSet(player->unk03A, 0x8C0001, FALSE);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    CharEffectLayerSet(4);
    CharMotionDataClose(player->unk03A);
    player->unk024 = NULL;
    player->unk020 = NULL;
    player->unk04A = 0;
    player->unk00C.x = 0.0f;
    player->unk00C.y = 0.0f;
    player->unk00C.z = 0.0f;
    player->unk000.x = 0.0f;
    player->unk000.y = 0.0f;
    player->unk000.z = 0.0f;
    Hu3DModelPosSetV(player->unk036, &player->unk000);
    omSetTra(player->unk018, player->unk000.x, player->unk000.y, player->unk000.z);
    Hu3DModelRotSetV(player->unk036, &player->unk00C);
    omSetRot(player->unk018, player->unk00C.x, player->unk00C.y, player->unk00C.z);
    player->unk050 = 0;
    player->unk034 = 0;
    obj->objFunc = fn_1_1B40;
}

/* 33 insns. Player object main: run the state func while play is active. */
void fn_1_1B40(OMOBJ *obj)
{
    M577_PLAYER *player = obj->data;
    M577_WORK *work = lbl_1_bss_C->data;

    if (work->unk1B66 != 0 && player->unk01C->unk044 != 2 && player->unk024) {
        player->unk024(player);
    }
}

/* 1 insn. Unreferenced, empty. */
void fn_1_1BC4(void)
{
}

/* 33 insns. Main object init (installed by ObjectSetup). */
void fn_1_1BC8(OMOBJ *obj)
{
    M577_WORK *work = lbl_1_bss_C->data;

    fn_1_263C(&work->unk0A8, work->unk0B0, M577_NODE_MAX);
    work->unk1B5E = -1;
    fn_1_B498(&work->unk1AC8);
    work->unk010[0].unk02C = fn_1_703C;
    work->unk010[1].unk02C = fn_1_703C;
    obj->objFunc = fn_1_1C4C;
}

/* 41 insns. Main object main. */
void fn_1_1C4C(OMOBJ *obj)
{
    M577_WORK *work = lbl_1_bss_C->data;

    work->unk010[0].unk02C(&work->unk010[0]);
    work->unk010[1].unk02C(&work->unk010[1]);
    fn_1_579C(&work->unk990[0]);
    fn_1_579C(&work->unk990[1]);
    fn_1_AA4C(work);
    fn_1_2E08(&work->unkC04[0]);
    fn_1_2E08(&work->unkC04[1]);
    fn_1_2E08(&work->unkC04[2]);
    fn_1_23CC(&work->unk920[0]);
    fn_1_23CC(&work->unk920[1]);
    fn_1_B134(work);
    fn_1_278C(&work->unk0A8);
}

/* 1 insn. Unreferenced, empty. */
void fn_1_1CF0(void)
{
}

/* 23 insns. Clear the model and motion caches. */
void fn_1_1CF4(M577_WORK *work)
{
    s32 i;

    for (i = 0; i < 25; i++) {
        work->unk1B68[i] = -1;
    }
    for (i = 0; i < 4; i++) {
        work->unk1B9A[i] = -1;
    }
}

/* 34 insns. Stage light; work is not read. */
void fn_1_1D50(M577_WORK *work)
{
    HU3DLIGHTID light;

    light = Hu3DGLightCreate(0.0f, 4000.0f, 0.0f, 0.0f, -1.0f, -1.0f, 127, 127, 127);
    Hu3DGLightInfinitytSet(light);
}

/* 133 insns. Both Hu3D cameras and the two M577_VIEWs. */
void fn_1_1DD8(M577_WORK *work)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        Hu3DCameraCreate(lbl_1_rodata_10[i]);
        Hu3DCameraPerspectiveSet(lbl_1_rodata_10[i], 15.0f, 20.0f, 40000.0f, 0.6f);
        Hu3DCameraPosSet(lbl_1_rodata_10[i],
            0.0f, 300.0f, 1000.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 150.0f, 0.0f);
        fn_1_2364(&work->unk920[i], lbl_1_rodata_10[i]);
        work->unk920[i].unk00C = lbl_1_data_270[i][3];
        work->unk920[i].unk010 = lbl_1_data_270[i][4];
        work->unk920[i].unk014 = lbl_1_data_270[i][5];
        work->unk920[i].unk000.x = lbl_1_data_270[i][0];
        work->unk920[i].unk000.y = lbl_1_data_270[i][1];
        work->unk920[i].unk000.z = lbl_1_data_270[i][2];
    }
}

/* 22 insns. */
void fn_1_1FEC(M577_SPLIT *split)
{
    split->unk000 = 640.0f;
    split->unk004 = 0.0f;
    split->unk00A = 0;
    fn_1_2044(split);
}

/* 134 insns. Viewports, scissors and aspect from the divider. */
void fn_1_2044(M577_SPLIT *split)
{
    float aspect;
    s32 i;
    u32 w;

    i = 0;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], 0.0f, 0.0f, split->unk000, 480.0f, 0.0f, 1.0f);
    i++;
    Hu3DCameraViewportSet(lbl_1_rodata_10[i], split->unk000, 0.0f, 640.0f - split->unk000, 480.0f, 0.0f, 1.0f);

    i = 0;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], 0, 0, split->unk000, 480);
    i++;
    w = 640.0f - split->unk000;
    Hu3DCameraScissorSet(lbl_1_rodata_10[i], split->unk000, 0, w, 480);

    i = 0;
    aspect = 0.9f * split->unk000 / 480.0f;
    if (aspect < 0.0f) {
        aspect = 0.0f;
    }
    Hu3DCameraPerspectiveSet(lbl_1_rodata_10[i], 15.0f, 20.0f, 40000.0f, aspect);
    i++;
}

/* 1 insn. Empty (called from the exit hook). */
void fn_1_225C(M577_SPLIT *split)
{
}

/* 65 insns. Unreferenced: multi-shadow for both cameras. */
void fn_1_2260(void)
{
    s16 cameraBit;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF pos = { 0.0f, 8000.0f, 0.0f };
    HuVecF target = { 0.1f, 0.0f, 0.0f };

    cameraBit = lbl_1_rodata_10[0] | lbl_1_rodata_10[1];
    Hu3DShadowMultiCreate(15.0f, 20.0f, 40000.0f, cameraBit);
    Hu3DShadowMultiPosSet(&pos, &up, &target, cameraBit);
    Hu3DShadowMultiSizeSet(48, cameraBit);
    Hu3DShadowMultiColSet(255, 0, 0, cameraBit);
}

/* 26 insns. */
void fn_1_2364(M577_VIEW *view, s16 cameraBit)
{
    view->unk000.x = 0.0f;
    view->unk000.y = 0.0f;
    view->unk000.z = 0.0f;
    view->unk00C = 0.0f;
    view->unk010 = 0.0f;
    view->unk014 = 3000.0f;
    view->unk034 = cameraBit;
}

/* 156 insns. Wrap angles, compute the eye, Hu3DCameraPosSet. */
void fn_1_23CC(M577_VIEW *view)
{
    HuVecF pos;

    while (view->unk00C > 360.0f) {
        view->unk00C -= 360.0f;
    }
    while (view->unk00C < 0.0f) {
        view->unk00C += 360.0f;
    }
    while (view->unk010 > 360.0f) {
        view->unk010 -= 360.0f;
    }
    while (view->unk010 < 0.0f) {
        view->unk010 += 360.0f;
    }
    pos.x = view->unk000.x + view->unk014 * HuCos(view->unk010) * HuCos(view->unk00C);
    pos.y = view->unk000.y + view->unk014 * HuSin(view->unk010);
    pos.z = view->unk000.z + view->unk014 * HuCos(view->unk010) * HuSin(view->unk00C);
    Hu3DCameraPosSet(view->unk034,
        pos.x, pos.y, pos.z,
        0.0f, 1.0f, 0.0f,
        view->unk000.x, view->unk000.y, view->unk000.z);
}

/* 33 insns. Link num pool nodes into the free list. */
void fn_1_263C(M577_LIST *list, M577_NODE *pool, s32 num)
{
    s32 i;

    list->unk000 = NULL;
    list->unk004 = pool;
    for (i = 0; i < num - 1; i++, pool++) {
        pool->unk000 = NULL;
        pool->unk004 = pool + 1;
        pool->unk00C = NULL;
        pool->unk010 = NULL;
        pool->unk008 = list;
    }
    pool->unk000 = NULL;
    pool->unk004 = NULL;
    pool->unk00C = NULL;
    pool->unk010 = NULL;
    pool->unk008 = list;
}

/* 21 insns. Take a free node, set func/data, push it on the active list. */
M577_NODE *fn_1_26C0(M577_LIST *list, M577_TASKFUNC func, void *data)
{
    M577_NODE *node;

    node = list->unk004;
    if (node) {
        list->unk004 = node->unk004;
        node->unk00C = func;
        node->unk010 = data;
        node->unk004 = list->unk000;
        if (node->unk004) {
            node->unk004->unk000 = node;
        }
        list->unk000 = node;
    }
    return node;
}

/* 30 insns. Unreferenced: return a node to the free list. */
void fn_1_2714(M577_NODE *node)
{
    M577_LIST *list;

    if (node) {
        list = node->unk008;
        if (node->unk000) {
            node->unk000->unk004 = node->unk004;
        } else {
            list->unk000 = node->unk004;
        }
        if (node->unk004) {
            node->unk004->unk000 = node->unk000;
        }
        node->unk000 = NULL;
        node->unk004 = list->unk004;
        node->unk00C = NULL;
        list->unk004 = node;
    }
}

/* 56 insns. Run every task; free those whose func returns TRUE. */
void fn_1_278C(M577_LIST *list)
{
    M577_NODE *node;
    M577_NODE *next;

    node = list->unk000;
    while (node) {
        next = node->unk004;
        if (node->unk00C && node->unk00C(node) && node) {
            M577_LIST *nodeList = node->unk008;

            if (node->unk000) {
                node->unk000->unk004 = node->unk004;
            } else {
                nodeList->unk000 = node->unk004;
            }
            if (node->unk004) {
                node->unk004->unk000 = node->unk000;
            }
            node->unk000 = NULL;
            node->unk004 = nodeList->unk004;
            node->unk00C = NULL;
            nodeList->unk004 = node;
        }
        node = next;
    }
}

/* 189 insns. Sprites and the two result models (model cache 11 and 13). */
void fn_1_286C(M577_WORK *work)
{
    s16 espId;
    HU3DMODELID mdl;

    work->unk1B54 = 800.0f;
    espId = espEntry(0x84001D, 11, 0);
    work->unk1B58 = espId;
    espDrawNoSet(espId, 0);
    espPosSet(espId, 288.0f, 240.0f);
    espAttrSet(espId, 1);
    espAttrSet(espId, 4);
    espId = espEntry(0x84001E, 10, 0);
    work->unk1B5A = espId;
    espDrawNoSet(espId, 0);
    espPosSet(espId, 288.0f, 240.0f);
    espAttrSet(espId, 1);
    espAttrSet(espId, 4);
    espId = espEntry(0x84001E, 10, 0);
    work->unk1B5C = espId;
    espDrawNoSet(espId, 0);
    espPosSet(espId, 288.0f, 240.0f);
    espAttrSet(espId, 1);
    espAttrSet(espId, 4);
    if (work->unk1B68[11] < 0) {
        mdl = work->unk1B68[11] = Hu3DModelCreateData(lbl_1_data_1FC[11]);
    } else {
        mdl = Hu3DModelLink(work->unk1B68[11]);
    }
    Hu3DModelAttrSet(mdl, 1);
    Hu3DModelAttrSet(mdl, 0x40000002);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(mdl, 1);
    if (work->unk1B68[13] < 0) {
        mdl = work->unk1B68[13] = Hu3DModelCreateData(lbl_1_data_1FC[13]);
    } else {
        mdl = Hu3DModelLink(work->unk1B68[13]);
    }
    Hu3DModelAttrSet(mdl, 1);
    Hu3DModelAttrSet(mdl, 0x40000002);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
}

/* 170 insns. Rope init: every node model is a link of model cache 0. */
void fn_1_2B60(M577_ROPE *rope, s32 num)
{
    M577_WORK *work = lbl_1_bss_C->data;
    s32 i;
    HU3DMODELID mdl;

    for (i = 0; i < num; i++) {
        if (work->unk1B68[0] < 0) {
            mdl = work->unk1B68[0] = Hu3DModelCreateData(lbl_1_data_1FC[0]);
        } else {
            mdl = Hu3DModelLink(work->unk1B68[0]);
        }
        rope->unk4AC[i] = mdl;
        Hu3DModelAttrSet(mdl, 1);
        Hu3DModelAttrSet(mdl, 0x40000002);
        Hu3DModelLayerSet(mdl, 3);
        Hu3DModelPosSet(mdl, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(mdl, 1);
        rope->unk000[i].x = 0.0f;
        rope->unk000[i].y = 0.0f;
        rope->unk000[i].z = 0.0f;
        rope->unk180[i].x = 0.0f;
        rope->unk180[i].y = 0.0f;
        rope->unk180[i].z = 0.0f;
        rope->unk300[i].x = 0.0f;
        rope->unk300[i].y = 0.0f;
        rope->unk300[i].z = 0.0f;
    }
    rope->unk4A8 = num;
    rope->unk480.x = 0.0f;
    rope->unk480.y = 0.0f;
    rope->unk480.z = 0.0f;
    rope->unk48C.x = 0.0f;
    rope->unk48C.y = 0.0f;
    rope->unk48C.z = 0.0f;
    rope->unk498 = 0.05f;
    rope->unk49C = 0.99f;
    rope->unk4A0 = 400.0f;
    rope->unk4A4 = 0.5f;
}
/* 419 insns */
void fn_1_2E08(M577_ROPE *rope)
{
    HuVecF dir;
    float len;
    float t;
    s32 i;
    s32 num;

    dir.x = rope->unk480.x - rope->unk48C.x;
    dir.y = rope->unk480.y - rope->unk48C.y;
    dir.z = rope->unk480.z - rope->unk48C.z;
    len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
    t = len / rope->unk4A0;
    if (t > 1.0f) {
        t = 1.0f;
    }
    num = rope->unk4A8;
    for (i = 0; i < num; i++) {
        rope->unk000[i].y -= 0.98f * (1.0f - t);
        rope->unk000[i].x += rope->unk180[i].x;
        rope->unk000[i].y += rope->unk180[i].y;
        rope->unk000[i].z += rope->unk180[i].z;
    }
    num = rope->unk4A8 - 1;
    rope->unk300[0] = rope->unk000[0] = rope->unk480;
    rope->unk300[num] = rope->unk000[num] = rope->unk48C;
    for (i = 0; i < num; i++) {
        dir.x = rope->unk000[i + 1].x - rope->unk000[i].x;
        dir.y = rope->unk000[i + 1].y - rope->unk000[i].y;
        dir.z = rope->unk000[i + 1].z - rope->unk000[i].z;
        len = sqrtf(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);
        t = rope->unk4A4 * (rope->unk498 - len);
        rope->unk000[i].x -= t * (dir.x / len);
        rope->unk000[i].y -= t * (dir.y / len);
        rope->unk000[i].z -= t * (dir.z / len);
        rope->unk000[i + 1].x += t * (dir.x / len);
        rope->unk000[i + 1].y += t * (dir.y / len);
        rope->unk000[i + 1].z += t * (dir.z / len);
    }
    num = rope->unk4A8;
    for (i = 0; i < num; i++) {
        if (rope->unk000[i].y < 40.0f) {
            rope->unk000[i].y = 40.0f - 0.8f * rope->unk180[i].y;
        }
        rope->unk180[i].x = rope->unk49C * (rope->unk000[i].x - rope->unk300[i].x);
        rope->unk180[i].y = rope->unk49C * (rope->unk000[i].y - rope->unk300[i].y);
        rope->unk180[i].z = rope->unk49C * (rope->unk000[i].z - rope->unk300[i].z);
        rope->unk300[i] = rope->unk000[i];
        Hu3DModelPosSetV(rope->unk4AC[i], &rope->unk000[i]);
    }
}

/* 393 insns */
void fn_1_3494(M577_TEAM *team, s16 side)
{
    s16 soloRate[3] = { 25, 60, 100 };
    s16 trioRate[3] = { 35, 70, 100 };
    M577_WORK *work;
    M577_PLAYER *player;
    s32 i;
    s32 j;
    s32 num;
    s16 rand;
    float t;

    work = lbl_1_bss_C->data;
    team->unk040 = side;
    team->unk042 = side ? 3 : 1;
    fn_1_45AC(team->unk01C, team->unk018->unk034);
    team->unk01C->unk060 = side;
    team->unk04A = 0;
    num = team->unk042;
    for (i = 0; i < num; i++) {
        player = team->unk000[i];
        Hu3DModelCameraSet(player->unk036, team->unk018->unk034);
        if (side) {
            if (player->unk044) {
                player->unk024 = fn_1_6D0C;
                rand = frandmod(100);
                for (j = 0; j < 3; j++) {
                    if (rand < trioRate[j]) {
                        break;
                    }
                }
                player->unk030 = fn_1_B460(i, player->unk046, j);
            }
            else {
                player->unk024 = fn_1_674C;
                player->unk030 = NULL;
            }
        }
        else {
            if (player->unk044) {
                player->unk024 = fn_1_6ACC;
                rand = frandmod(100);
                for (j = 0; j < 3; j++) {
                    if (rand < soloRate[j]) {
                        break;
                    }
                }
                player->unk030 = fn_1_B430(player->unk046, j);
            }
            else {
                player->unk024 = fn_1_64BC;
                player->unk030 = NULL;
            }
        }
        team->unk00C[i]->unk004 = team;
        fn_1_3E10(team->unk00C[i], player, side);
        team->unk00C[i]->unk020.z = 400.0f * i;
        team->unk00C[i]->unk018 = 0.0f;
        team->unk00C[i]->unk01C = -400.0f * i;
        t = (400.0f * i) / work->unk1AC8.unk008;
        team->unk00C[i]->unk054 = 30.0 + (16000.0 * cos(M_PI * (90.0f * t) / 180.0) - 16000.0);
        team->unk00C[i]->unk020.y = team->unk00C[i]->unk054;
        team->unk00C[i]->unk02C.x = 90.0f * t;
        Hu3DModelPosSetV(team->unk00C[i]->unk05C, &team->unk00C[i]->unk020);
        Hu3DModelPosSet(team->unk00C[i]->unk060, team->unk00C[i]->unk020.x, team->unk00C[i]->unk020.y, team->unk00C[i]->unk020.z);
        Hu3DModelRotSetV(team->unk00C[i]->unk05C, &team->unk00C[i]->unk02C);
        Hu3DModelCameraSet(team->unk00C[i]->unk05C, team->unk018->unk034);
        Hu3DModelCameraSet(team->unk00C[i]->unk060, team->unk018->unk034);
    }
    if (side == 0) {
        team->unk00C[0]->unk03C = &team->unk020[0]->unk480;
        team->unk00C[0]->unk040->unk00C = &team->unk020[0]->unk48C;
        Hu3DModelCameraSet(team->unk00C[0]->unk040->unk028, team->unk018->unk034);
        Hu3DModelCameraSet(team->unk00C[0]->unk040->unk02C, team->unk018->unk034);
    }
    else {
        team->unk00C[0]->unk03C = &team->unk020[0]->unk480;
        team->unk00C[1]->unk038 = &team->unk020[0]->unk48C;
        team->unk00C[1]->unk03C = &team->unk020[1]->unk480;
        team->unk00C[2]->unk038 = &team->unk020[1]->unk48C;
    }
    num = side ? 2 : 1;
    for (j = 0; j < num; j++) {
        for (i = 0; i < team->unk020[j]->unk4A8; i++) {
            Hu3DModelCameraSet(team->unk020[j]->unk4AC[i], team->unk018->unk034);
        }
    }
    team->unk034 = team->unk028->unk008 / 1680.0f;
    team->unk038 = 0.5f * team->unk034;
    team->unk030 = 0.0f;
    team->unk03C = 0.0f;
    team->unk044 = 0;
}

/* 214 insns */
void fn_1_3AB8(M577_WORK *work)
{
    s16 unused[4] = { 3, 2, 1, 1 };
    s16 slot[3] = { 0, 1, 2 };
    s32 i;
    s32 num;
    s16 a;
    s16 b;
    s16 tmp;

    for (i = 0; i < 3; i++) {
        a = frandmod(3);
        b = frandmod(3);
        tmp = slot[a];
        slot[a] = slot[b];
        slot[b] = tmp;
    }
    num = 0;
    for (i = 0; i < 4; i++) {
        if (work->unk000[i]->unk03C == 0) {
            work->unk010[0].unk000[0] = work->unk000[i];
            work->unk000[i]->unk01C = &work->unk010[0];
        }
        else {
            work->unk010[1].unk000[slot[num]] = work->unk000[i];
            work->unk000[i]->unk01C = &work->unk010[1];
            work->unk000[i]->unk048 = slot[num];
            num++;
        }
    }
    work->unk010[0].unk00C[0] = &work->unkA64[0];
    work->unk010[1].unk00C[0] = &work->unkA64[1];
    work->unk010[1].unk00C[1] = &work->unkA64[2];
    work->unk010[1].unk00C[2] = &work->unkA64[3];
    work->unk010[0].unk020[0] = &work->unkC04[0];
    work->unk010[1].unk020[0] = &work->unkC04[1];
    work->unk010[1].unk020[1] = &work->unkC04[2];
    work->unk010[0].unk028 = &work->unk1AC8;
    work->unk010[1].unk028 = &work->unk1AC8;
    work->unk010[0].unk01C = &work->unk990[0];
    work->unk010[1].unk01C = &work->unk990[1];
    work->unk010[0].unk018 = &work->unk920[0];
    work->unk010[1].unk018 = &work->unk920[1];
    work->unk010[0].unk01C = &work->unk990[0];
    work->unk010[1].unk01C = &work->unk990[1];
    work->unk010[0].unk00C[0]->unk040 = &work->unk1AD4;
    fn_1_2B60(work->unk010[0].unk020[0], 8);
    work->unk010[0].unk020[0]->unk4A0 = 100.0f;
    fn_1_2B60(work->unk010[1].unk020[0], 32);
    fn_1_2B60(work->unk010[1].unk020[1], 32);
    fn_1_3494(&work->unk010[0], 0);
    fn_1_3494(&work->unk010[1], 1);
    work->unk010[0].unk000[0]->unk020->unk044 = &work->unk1B04[0];
    work->unk010[1].unk000[0]->unk020->unk044 = &work->unk1B04[1];
    work->unk010[1].unk000[1]->unk020->unk044 = &work->unk1B04[2];
    work->unk010[1].unk000[2]->unk020->unk044 = &work->unk1B04[3];
    work->unk010[0].unk000[0]->unk020->unk040->unk010 = &work->unk1B04[4];
    fn_1_B5D4(&work->unk1B04[0], lbl_1_rodata_10[0], &work->unk010[0].unk000[0]->unk020->unk020);
    fn_1_B5D4(&work->unk1B04[1], lbl_1_rodata_10[1], &work->unk010[1].unk000[0]->unk020->unk020);
    fn_1_B5D4(&work->unk1B04[2], lbl_1_rodata_10[1], &work->unk010[1].unk000[1]->unk020->unk020);
    fn_1_B5D4(&work->unk1B04[3], lbl_1_rodata_10[1], &work->unk010[1].unk000[2]->unk020->unk020);
    fn_1_B5D4(&work->unk1B04[4], lbl_1_rodata_10[0], &work->unk010[0].unk000[0]->unk020->unk040->unk000);
}

#define M577_MDL(work, n, mdl)                                                  \
    if ((work)->unk1B68[n] < 0) {                                               \
        mdl = (work)->unk1B68[n] = Hu3DModelCreateData(lbl_1_data_1FC[n]);      \
    }                                                                           \
    else {                                                                      \
        mdl = Hu3DModelLink((work)->unk1B68[n]);                                \
    }

#define M577_MOT(work, n, mdl, mot)                                             \
    if ((work)->unk1B9A[n] < 0) {                                               \
        mot = (work)->unk1B9A[n] = Hu3DJointMotionData(mdl, lbl_1_data_260[n]); \
    }                                                                           \
    else {                                                                      \
        mot = (work)->unk1B9A[n];                                               \
    }

/* the same, assigned the other way round (0x5480, 0x55B4 store after the copy) */
#define M577_MOT2(work, n, mdl, mot)                                            \
    if ((work)->unk1B9A[n] < 0) {                                               \
        (work)->unk1B9A[n] = mot = Hu3DJointMotionData(mdl, lbl_1_data_260[n]); \
    }                                                                           \
    else {                                                                      \
        mot = (work)->unk1B9A[n];                                               \
    }

/* 487 insns */
void fn_1_3E10(M577_CART *cart, M577_PLAYER *player, s32 side)
{
    float a[2];
    float b[2];
    M577_WORK *work;
    HU3DMODELID mdl;
    float (*p)[2];
    float t;

    work = lbl_1_bss_C->data;
    cart->unk000 = player;
    cart->unk020.x = 0.0f;
    cart->unk020.y = 0.0f;
    cart->unk020.z = 0.0f;
    cart->unk02C.x = 0.0f;
    cart->unk02C.y = 0.0f;
    cart->unk02C.z = 0.0f;
    cart->unk048 = 0.0f;
    cart->unk062 = 0;
    cart->unk064 = 0;
    cart->unk058 = 0.0f;
    M577_MDL(work, 5, mdl);
    cart->unk05C = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 3);
    Hu3DModelPosSetV(mdl, &cart->unk020);
    Hu3DModelRotSetV(mdl, &cart->unk02C);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(mdl, 10.0f);
    M577_MDL(work, 6, mdl);
    cart->unk05E = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 3);
    Hu3DModelPosSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 8, mdl);
    cart->unk060 = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 1);
    Hu3DModelPosSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    if (side == 0) {
        cart->unk040->unk000.x = 0.0f;
        t = -400.0f / work->unk1AC8.unk008;
        cart->unk040->unk000.y = 30.0 + (16000.0 * cos(M_PI * (90.0f * t) / 180.0) - 16000.0);
        cart->unk040->unk000.z = 400.0f;
        cart->unk040->unk014 = 0.0f;
        cart->unk040->unk018 = 0.0f;
        cart->unk040->unk020 = cart->unk040->unk000.y;
        M577_MDL(work, 7, mdl);
        cart->unk040->unk028 = mdl;
        Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(mdl, 3);
        Hu3DModelPosSetV(mdl, &cart->unk040->unk000);
        Hu3DModelRotSet(mdl, 90.0f * t, 0.0f, 0.0f);
        Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
        M577_MDL(work, 6, mdl);
        cart->unk040->unk02A = mdl;
        Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(mdl, 3);
        Hu3DModelPosSet(mdl, 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelHookSet(cart->unk040->unk028, lbl_1_data_31C, cart->unk040->unk02A);
        M577_MDL(work, 8, mdl);
        cart->unk040->unk02C = mdl;
        Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(mdl, 1);
        Hu3DModelPosSet(mdl, cart->unk040->unk000.x, cart->unk040->unk000.y, cart->unk040->unk000.z);
        Hu3DModelRotSet(mdl, 90.0f * t, 0.0f, 0.0f);
        Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(mdl, 0.6f, 1.0f, 0.6f);
        cart->unk040->unk024 = 0.0f;
    }
    Hu3DModelHookSet(cart->unk05C, lbl_1_data_31C, cart->unk05E);
    Hu3DModelHookSet(cart->unk05C, lbl_1_data_323, player->unk036);
    player->unk020 = cart;
    p = cart->unk004->unk028->unk000;
    a[0] = (p[0][0] + p[1][0]) / 2.0f;
    a[1] = (p[0][1] + p[1][1]) / 2.0f;
    b[0] = (p[2][0] + p[3][0]) / 2.0f;
    b[1] = (p[2][1] + p[3][1]) / 2.0f;
    fn_1_A754(&cart->unk008, a, b);
}

#define M577_STAGEMDL(stage, mdl, cameraBit)            \
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);           \
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);                  \
    Hu3DModelLayerSet(mdl, 0);                          \
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);        \
    Hu3DModelRotSet(mdl, (stage)->unk000, 0.0f, 0.0f);  \
    Hu3DModelCameraSet(mdl, cameraBit)

/* 1148 insns */
void fn_1_45AC(M577_STAGE *stage, u16 cameraBit)
{
    M577_WORK *work;
    HU3DMODELID mdl;
    HU3DMOTID mot;
    s32 i;

    work = lbl_1_bss_C->data;
    stage->unk000 = 0.0f;
    M577_MDL(work, 1, mdl);
    stage->unk004 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 2, mdl);
    stage->unk006 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 3, mdl);
    stage->unk008 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    M577_MDL(work, 4, mdl);
    stage->unk00A = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, stage->unk000 - 22.5f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, cameraBit);
    M577_MDL(work, 9, mdl);
    stage->unk00C = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 10, mdl);
    stage->unk00E = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    M577_MDL(work, 12, mdl);
    M577_MOT(work, 3, mdl, mot);
    stage->unk010 = mdl;
    Hu3DMotionSet(mdl, mot);
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 12, mdl);
    M577_MOT(work, 3, mdl, mot);
    stage->unk012 = mdl;
    Hu3DMotionSet(mdl, mot);
    M577_STAGEMDL(stage, mdl, cameraBit);
    M577_MDL(work, 14, mdl);
    stage->unk014 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 15, mdl);
    stage->unk016 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    M577_MDL(work, 16, mdl);
    stage->unk018 = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    M577_MDL(work, 17, mdl);
    stage->unk01A = mdl;
    M577_STAGEMDL(stage, mdl, cameraBit);
    M577_MDL(work, 18, mdl);
    stage->unk01C = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, stage->unk000, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, cameraBit);
    M577_MDL(work, 19, mdl);
    stage->unk01E = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, stage->unk000, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, cameraBit);
    M577_MDL(work, 20, mdl);
    stage->unk020 = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, stage->unk000, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, cameraBit);
    M577_MDL(work, 22, mdl);
    M577_MOT(work, 1, mdl, mot);
    stage->unk038 = mdl;
    Hu3DMotionSet(mdl, mot);
    M577_STAGEMDL(stage, mdl, cameraBit);
    Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
    stage->unk052 = 0;
    M577_MDL(work, 23, mdl);
    M577_MOT2(work, 2, mdl, mot);
    stage->unk03A = mdl;
    Hu3DMotionSet(mdl, mot);
    M577_STAGEMDL(stage, mdl, cameraBit);
    stage->unk054 = 0;
    for (i = 0; i < 11; i++) {
        M577_MDL(work, 21, mdl);
        M577_MOT2(work, 0, mdl, mot);
        stage->unk022[i] = mdl;
        Hu3DMotionSet(mdl, mot);
        Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
        Hu3DModelLayerSet(mdl, 0);
        Hu3DModelPosSet(mdl, lbl_1_data_32C[i][1], -16000.0f, 0.0f);
        Hu3DModelRotSet(mdl, stage->unk000 + lbl_1_data_32C[i][0], 0.0f, 0.0f);
        Hu3DModelCameraSet(mdl, cameraBit);
        if (i < 6) {
            Hu3DModelAttrReset(mdl, HU3D_ATTR_DISPOFF);
        }
        stage->unk03C[i] = 0;
    }
    M577_MDL(work, 24, mdl);
    stage->unk056 = mdl;
    Hu3DModelAttrSet(mdl, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(mdl, HU3D_MOTATTR_PAUSE);
    Hu3DModelLayerSet(mdl, 0);
    Hu3DModelPosSet(mdl, 0.0f, -16000.0f, 0.0f);
    Hu3DModelRotSet(mdl, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdl, cameraBit);
}

/* 504 insns */
void fn_1_579C(M577_STAGE *stage)
{
    M577_WORK *work;
    M577_TASK *task0;
    M577_TASK *task1;
    s32 i;

    work = lbl_1_bss_C->data;
    Hu3DModelRotSet(stage->unk004, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk006, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk008, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk00A, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk00C, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk00E, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk010, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk012, stage->unk000 - 90.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk014, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk016, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk018, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk01A, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk01C, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk01E, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk020, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk038, stage->unk000, 0.0f, 0.0f);
    Hu3DModelRotSet(stage->unk03A, stage->unk000, 0.0f, 0.0f);
    for (i = 0; i < 11; i++) {
        Hu3DModelRotSet(stage->unk022[i], stage->unk000 + lbl_1_data_32C[i][0], 0.0f, 0.0f);
    }
    if (work->unk1B66 == 0) {
        return;
    }
    if (stage->unk000 > 10.0f && !(Hu3DModelAttrGet(stage->unk010) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrSet(stage->unk010, HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 55.0f && (Hu3DModelAttrGet(stage->unk012) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrReset(stage->unk00E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk012, HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 30.0f && !(Hu3DModelAttrGet(stage->unk014) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrSet(stage->unk014, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk004, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk038, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[2], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[3], HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 55.0f && !(Hu3DModelAttrGet(stage->unk016) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrSet(stage->unk016, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk006, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[5], HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 15.0f && (Hu3DModelAttrGet(stage->unk018) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrReset(stage->unk018, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk008, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk01C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk01E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk03A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk022[6], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk022[7], HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 80.0f && !(Hu3DModelAttrGet(stage->unk018) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrSet(stage->unk018, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk008, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk01C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk01E, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk03A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[6], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(stage->unk022[7], HU3D_ATTR_DISPOFF);
    }
    if (stage->unk000 > 40.0f && (Hu3DModelAttrGet(stage->unk01A) & HU3D_ATTR_DISPOFF)) {
        Hu3DModelAttrReset(stage->unk01A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk00A, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk020, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk022[8], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk022[9], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(stage->unk022[10], HU3D_ATTR_DISPOFF);
    }
    if (stage->unk052 == 0 && stage->unk000 - 16.25f >= 0.0f) {
        stage->unk052 = 1;
        Hu3DModelAttrReset(stage->unk038, HU3D_MOTATTR_PAUSE);
        if (stage->unk060) {
            task0 = work->unk0A8.unk004;
            if (task0) {
                work->unk0A8.unk004 = task0->unk004;
                task0->unk00C = fn_1_B3CC;
                task0->unk010 = &stage->unk05C;
                task0->unk004 = work->unk0A8.unk000;
                if (task0->unk004) {
                    task0->unk004->unk000 = task0;
                }
                work->unk0A8.unk000 = task0;
            }
            stage->unk05C = 0;
        }
        else {
            HuAudFXPlayPan(0x941, 0x30);
        }
    }
    if (stage->unk054 == 0 && stage->unk000 - 57.38f >= 0.0f) {
        stage->unk054 = 1;
        Hu3DModelAttrReset(stage->unk03A, HU3D_MOTATTR_PAUSE);
        if (stage->unk060) {
            task1 = work->unk0A8.unk004;
            if (task1) {
                work->unk0A8.unk004 = task1->unk004;
                task1->unk00C = fn_1_B3CC;
                task1->unk010 = &stage->unk05E;
                task1->unk004 = work->unk0A8.unk000;
                if (task1->unk004) {
                    task1->unk004->unk000 = task1;
                }
                work->unk0A8.unk000 = task1;
            }
            stage->unk05E = 0;
        }
        else {
            HuAudFXPlayPan(0x941, 0x30);
        }
    }
    for (i = 0; i < 11; i++) {
        if (stage->unk03C[i] == 0 && stage->unk000 + lbl_1_data_32C[i][0] >= 0.0f) {
            stage->unk03C[i] = 1;
            Hu3DModelAttrReset(stage->unk022[i], HU3D_MOTATTR_PAUSE);
        }
    }
}

/* 94 insns */
void fn_1_5F7C(M577_PLAYER *player)
{
    M577_CART *cart;

    cart = player->unk020;
    if (player->unk050 < 0) {
        cart->unk048 -= 0.3f;
        if (cart->unk048 < -10.0f) {
            cart->unk048 = -10.0f;
        }
        player->unk02C += 0.05f;
        if (player->unk02C > 1.0f) {
            player->unk02C = 1.0f;
        }
    }
    else if (player->unk050 > 0) {
        cart->unk048 += 0.3f;
        if (cart->unk048 > 10.0f) {
            cart->unk048 = 10.0f;
        }
        player->unk02C -= 0.05f;
        if (player->unk02C < 0.0f) {
            player->unk02C = 0.0f;
        }
    }
    else {
        player->unk02C = (player->unk02C > 0.5f) ? ((player->unk02C - 0.05f < 0.5f) ? 0.5f : player->unk02C - 0.05f)
                                                 : ((0.05f + player->unk02C > 0.5f) ? 0.5f : 0.05f + player->unk02C);
    }
}

/* 198 insns */
void fn_1_61A4(M577_PLAYER *player)
{
    M577_CART *cart;

    cart = player->unk020;
    if (player->unk050 < 0) {
        cart->unk048 -= 0.5f;
        if (cart->unk048 < -9.0f) {
            cart->unk048 = -8.5f;
        }
        player->unk02C += 0.05f;
        if (player->unk02C > 1.0f) {
            player->unk02C = 1.0f;
        }
    }
    else if (player->unk050 > 0) {
        cart->unk048 += 0.5f;
        if (cart->unk048 > 9.0f) {
            cart->unk048 = 8.5f;
        }
        player->unk02C -= 0.05f;
        if (player->unk02C < 0.0f) {
            player->unk02C = 0.0f;
        }
    }
    else {
        cart->unk048 = (cart->unk048 > 0.0f) ? ((cart->unk048 - 0.5f < 0.0f) ? 0.0f : cart->unk048 - 0.5f)
                                             : ((0.5f + cart->unk048 > 0.0f) ? 0.0f : 0.5f + cart->unk048);
        player->unk02C = (player->unk02C > 0.5f) ? ((player->unk02C - 0.05f < 0.5f) ? 0.5f : player->unk02C - 0.05f)
                                                 : ((0.05f + player->unk02C > 0.5f) ? 0.5f : 0.05f + player->unk02C);
    }
}

/* 164 insns */
void fn_1_64BC(M577_PLAYER *player)
{
    M577_CART *cart;

    cart = player->unk020;
    if (HuPadStkX[player->unk03E] < -32) {
        player->unk050 = -1;
    }
    else if (HuPadStkX[player->unk03E] > 32) {
        player->unk050 = 1;
    }
    else {
        player->unk050 = 0;
    }
    fn_1_5F7C(player);
}

/* 224 insns */
void fn_1_674C(M577_PLAYER *player)
{
    M577_CART *cart;

    cart = player->unk020;
    if (HuPadStkX[player->unk03E] < -32) {
        player->unk050 = -1;
    }
    else if (HuPadStkX[player->unk03E] > 32) {
        player->unk050 = 1;
    }
    else {
        player->unk050 = 0;
    }
    fn_1_61A4(player);
}

/* 144 insns */
void fn_1_6ACC(M577_PLAYER *player)
{
    player->unk050 = *player->unk030;
    player->unk030++;
    fn_1_5F7C(player);
}

/* 204 insns */
void fn_1_6D0C(M577_PLAYER *player)
{
    player->unk050 = *player->unk030;
    player->unk030++;
    fn_1_61A4(player);
}

/* 1 insns */
void fn_1_703C(M577_TEAM *team) { }

/* 154 insns */
void fn_1_7040(M577_TEAM *team)
{
    M577_PLAYER *player;
    M577_CART *cart;
    s32 i;
    s32 num;
    float t;

    switch (team->unk046) {
        case 0:
            if (lbl_1_data_2A0[team->unk040]) {
                lbl_1_data_2A0[team->unk040] = 0;
                HuAudFXStop(lbl_1_bss_0[team->unk040]);
            }
            team->unk048 = 0;
            team->unk046++;
        case 1:
            num = team->unk042;
            for (i = 0; i < num; i++) {
                player = team->unk000[i];
                cart = player->unk020;
                player->unk02C = (player->unk02C > 0.5f) ? ((player->unk02C - 0.1f < 0.5f) ? 0.5f : player->unk02C - 0.1f)
                                                         : ((0.1f + player->unk02C > 0.5f) ? 0.5f : 0.1f + player->unk02C);
                t = player->unk028 * player->unk02C;
                CharMotionTimeSet(player->unk03A, t);
                Hu3DMotionTimeSet(cart->unk05C, t);
                fn_1_B720(cart->unk044, 0);
            }
            if (team->unk040 == 0) {
                fn_1_B720(cart->unk040->unk010, 0);
            }
            team->unk048++;
            if (team->unk048 == 5) {
                team->unk046++;
            }
            break;
        case 2:
            team->unk02C = fn_1_703C;
            break;
    }
}

/* 10 insns */
void fn_1_72A8(M577_TEAM *team)
{
    M577_WORK *work;

    work = lbl_1_bss_C->data;
    team->unk030 = team->unk034;
}

/* 661 insns */
void fn_1_72D0(M577_TEAM *team)
{
    HuVec2f a;
    HuVec2f b;
    float pos[2];
    M577_WORK *work;
    M577_PLAYER *player;
    M577_CART *cart;
    M577_TOW *tow;
    float (*p)[2];
    s32 i;
    s32 num;
    float d;
    float dist;
    float k;
    float lineDist;
    float t;
    float pan;
    float pitch;

    work = lbl_1_bss_C->data;
    player = team->unk000[0];
    cart = player->unk020;
    if (team->unk04A == 0) {
        fn_1_72A8(team);
        fn_1_B720(cart->unk044, 1);
        fn_1_B720(cart->unk040->unk010, 1);
    }
    else {
        team->unk030 -= 0.2f;
        if (team->unk030 < 0.0f) {
            team->unk030 = 0.0f;
            team->unk02C = fn_1_7040;
            team->unk046 = 0;
        }
        if (team->unk030 < team->unk034 / 4.0f) {
            fn_1_B720(cart->unk044, 0);
            fn_1_B720(cart->unk040->unk010, 0);
        }
    }
    cart->unk020.x += cart->unk048;
    if (cart->unk048 > -0.3f && cart->unk048 < 0.3f) {
        cart->unk048 = 0.0f;
    }
    tow = cart->unk040;
    tow->unk000.x += tow->unk018;
    d = tow->unk000.x - cart->unk020.x;
    dist = fabsf(d);
    if (dist > 100.0f) {
        k = 0.2f * (100.0f - dist);
        cart->unk020.x -= k * (d / dist);
        tow->unk000.x += k * (d / dist);
    }
    tow->unk018 = 0.9f * (tow->unk000.x - tow->unk014);
    tow->unk014 = tow->unk000.x;
    cart->unk018 = cart->unk020.x;
    cart->unk01C += team->unk030;
    num = team->unk028->unk004 / 2 - 1;
    p = team->unk028->unk000;
    for (i = 0; i < num; i++, p += 2) {
        if (fn_1_B4D0(&cart->unk018, p)) {
            break;
        }
    }
    if (i == num) {
        if (player->unk034 == 0) {
            team->unk044 = 2;
            team->unk046 = 0;
            team->unk02C = fn_1_85F4;
            player->unk04A = 1;
            player->unk034 = 1;
        }
        else {
            p = team->unk028->unk000;
            pos[1] = cart->unk01C;
            for (i = 0; i < num; i++, p += 2) {
                a.x = (p[0][0] + p[1][0]) / 2.0f;
                a.y = (p[0][1] + p[1][1]) / 2.0f;
                b.x = (p[2][0] + p[3][0]) / 2.0f;
                b.y = (p[2][1] + p[3][1]) / 2.0f;
                fn_1_A754(&cart->unk008, &a.x, &b.x);
                pos[0] = fn_1_A9D0(&cart->unk008, pos[1]);
                if (fn_1_B4D0(pos, p)) {
                    break;
                }
            }
            if (pos[0] > cart->unk018) {
                a = *(HuVec2f *)p[0];
                b = *(HuVec2f *)p[2];
            }
            else {
                a = *(HuVec2f *)p[1];
                b = *(HuVec2f *)p[3];
            }
            fn_1_A754(&cart->unk008, &a.x, &b.x);
            cart->unk020.x = fn_1_A9D0(&cart->unk008, pos[1]);
            if (work->unk1B5E == 0 && cart->unk01C > team->unk028->unk008) {
                team->unk02C = fn_1_9380;
            }
        }
    }
    else {
        a.x = (p[0][0] + p[1][0]) / 2.0f;
        a.y = (p[0][1] + p[1][1]) / 2.0f;
        b.x = (p[2][0] + p[3][0]) / 2.0f;
        b.y = (p[2][1] + p[3][1]) / 2.0f;
        fn_1_A754(&cart->unk008, &a.x, &b.x);
        lineDist = fn_1_A8D4(&cart->unk008, &cart->unk018);
        if (lineDist > 75.0f) {
            team->unk044 = 0;
        }
        else {
            team->unk044 = 0;
        }
        if (work->unk1B5E == 0 && cart->unk01C > team->unk028->unk008) {
            team->unk02C = fn_1_9380;
        }
    }
    cart->unk048 *= 0.97f;
    team->unk03C += team->unk030;
    team->unk01C->unk000 = (90.0f * team->unk03C) / team->unk028->unk008;
    team->unk018->unk000.x = 0.5f * cart->unk020.x;
    Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
    Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
    cart->unk058 = cart->unk058 - (360.0f * team->unk030) / 273.94686980565;
    while (cart->unk058 > 180.0f) {
        cart->unk058 -= 360.0f;
    }
    while (cart->unk058 < -180.0f) {
        cart->unk058 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
    Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
    Hu3DModelPosSet(cart->unk040->unk02C, cart->unk040->unk000.x, cart->unk040->unk000.y, cart->unk040->unk000.z);
    cart->unk040->unk024 -= (360.0f * team->unk030) / 273.94686980565;
    while (cart->unk040->unk024 > 180.0f) {
        cart->unk040->unk024 -= 360.0f;
    }
    while (cart->unk040->unk024 < -180.0f) {
        cart->unk040->unk024 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk040->unk02A, cart->unk040->unk024, 0.0f, 0.0f);
    t = player->unk028 * player->unk02C;
    CharMotionTimeSet(player->unk03A, t);
    Hu3DMotionTimeSet(cart->unk05C, t);
    if (team->unk030 < team->unk034 / 4.0f) {
        if (lbl_1_data_2A0[0]) {
            lbl_1_data_2A0[0] = 0;
            HuAudFXStop(lbl_1_bss_0[0]);
        }
    }
    else {
        pan = cart->unk020.x / 700.0f;
        if (pan > 1.0f) {
            pan = 1.0f;
        }
        if (pan < -1.0f) {
            pan = -1.0f;
        }
        pan = 48.0f + 16.0f * pan;
        if (team->unk04A) {
            pitch = team->unk030 / team->unk034;
            pitch = 8191.0f * pitch - 8191.0f;
        }
        else {
            pitch = fabsf(cart->unk048) / 10.0f;
            if (pitch > 1.0f) {
                pitch = 1.0f;
            }
            pitch = 8191.0f * pitch;
        }
        if (!lbl_1_data_2A0[0]) {
            lbl_1_bss_0[0] = HuAudFXPlay(0x93C);
            lbl_1_data_2A0[0] = 1;
        }
        HuAudFXPanning(lbl_1_bss_0[0], pan);
        HuAudFXPitchSet(lbl_1_bss_0[0], pitch);
    }
}

/* 564 insns */
void fn_1_7D24(M577_TEAM *team)
{
    float a[2];
    float b[2];
    float pt[2];
    M577_WORK *work;
    M577_PLAYER *player;
    M577_CART *cart;
    float (*p)[2];
    s32 i;
    s32 j;
    s32 num;
    s32 count;
    float dist;
    float time;
    float maxX;
    float minX;
    float pan;
    float pitch;

    work = lbl_1_bss_C->data;
    if (team->unk04A == 0) {
        M577_WORK *work2 = lbl_1_bss_C->data;
        team->unk030 = team->unk034;
        for (j = 0; j < 3; j++) {
            player = team->unk000[j];
            cart = player->unk020;
            fn_1_B720(cart->unk044, 1);
        }
    }
    else {
        team->unk030 -= 0.2f;
        if (team->unk030 < 0.0f) {
            team->unk030 = 0.0f;
            team->unk02C = fn_1_7040;
            team->unk046 = 0;
        }
        if (team->unk030 < team->unk034 / 4.0f) {
            for (j = 0; j < 3; j++) {
                player = team->unk000[j];
                cart = player->unk020;
                fn_1_B720(cart->unk044, 0);
            }
        }
    }
    for (j = 0; j < 3; j++) {
        player = team->unk000[j];
        cart = player->unk020;
        cart->unk020.x += cart->unk048;
    }
    count = 0;
    for (i = 0; i < 3; i++) {
        player = team->unk000[i];
        cart = player->unk020;
        cart->unk018 = cart->unk020.x;
        cart->unk01C += team->unk030;
        num = team->unk028->unk004 / 2 - 1;
        p = team->unk028->unk000;
        for (j = 0; j < num; j++, p += 2) {
            if (fn_1_B4D0(&cart->unk018, p)) {
                break;
            }
        }
        if (j == num) {
            if (player->unk034 == 0) {
                count -= 3;
                player->unk04A = 1;
            }
            else {
                p = team->unk028->unk000;
                pt[1] = cart->unk01C;
                for (j = 0; j < num; j++, p += 2) {
                    a[0] = (p[0][0] + p[1][0]) / 2.0f;
                    a[1] = (p[0][1] + p[1][1]) / 2.0f;
                    b[0] = (p[2][0] + p[3][0]) / 2.0f;
                    b[1] = (p[2][1] + p[3][1]) / 2.0f;
                    fn_1_A754(&cart->unk008, a, b);
                    pt[0] = fn_1_A9D0(&cart->unk008, pt[1]);
                    if (fn_1_B4D0(pt, p)) {
                        break;
                    }
                }
                if (pt[0] > cart->unk018) {
                    *(HuVec2f *)a = *(HuVec2f *)p[0];
                    *(HuVec2f *)b = *(HuVec2f *)p[2];
                }
                else {
                    *(HuVec2f *)a = *(HuVec2f *)p[1];
                    *(HuVec2f *)b = *(HuVec2f *)p[3];
                }
                fn_1_A754(&cart->unk008, a, b);
                cart->unk020.x = fn_1_A9D0(&cart->unk008, pt[1]);
            }
        }
        else {
            a[0] = (p[0][0] + p[1][0]) / 2.0f;
            a[1] = (p[0][1] + p[1][1]) / 2.0f;
            b[0] = (p[2][0] + p[3][0]) / 2.0f;
            b[1] = (p[2][1] + p[3][1]) / 2.0f;
            fn_1_A754(&cart->unk008, a, b);
            dist = fn_1_A8D4(&cart->unk008, &cart->unk018);
            if (dist > 75.0f) {
                count++;
            }
        }
    }
    if (count < 0) {
        team->unk044 = 2;
        team->unk046 = 0;
        team->unk02C = fn_1_8BB8;
    }
    else {
        if (count == 0) {
            team->unk044 = 0;
        }
        else {
            team->unk044 = 0;
        }
        player = team->unk000[0];
        cart = player->unk020;
        if (work->unk1B5E == 1 && cart->unk01C > team->unk028->unk008) {
            team->unk02C = fn_1_9C08;
        }
    }
    team->unk03C += team->unk030;
    team->unk01C->unk000 = (90.0f * team->unk03C) / team->unk028->unk008;
    pitch = 0.0f;
    maxX = -20000.0f;
    minX = 20000.0f;
    for (j = 0; j < 3; j++) {
        player = team->unk000[j];
        cart = player->unk020;
        time = player->unk028 * player->unk02C;
        CharMotionTimeSet(player->unk03A, time);
        Hu3DMotionTimeSet(cart->unk05C, time);
        Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
        Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
        cart->unk058 = cart->unk058 - (360.0f * team->unk030) / 273.94686980565;
        while (cart->unk058 > 180.0f) {
            cart->unk058 -= 360.0f;
        }
        while (cart->unk058 < -180.0f) {
            cart->unk058 += 360.0f;
        }
        Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
        if (cart->unk020.x > maxX) {
            maxX = cart->unk020.x;
        }
        if (cart->unk020.x < minX) {
            minX = cart->unk020.x;
        }
        pitch += fabsf(cart->unk048);
    }
    team->unk018->unk000.x = 0.5f * (maxX + minX);
    if (team->unk030 < team->unk034 / 4.0f) {
        if (lbl_1_data_2A0[1]) {
            lbl_1_data_2A0[1] = 0;
            HuAudFXStop(lbl_1_bss_0[1]);
        }
    }
    else {
        pan = (maxX + minX) / 700.0f;
        if (pan > 1.0f) {
            pan = 1.0f;
        }
        if (pan < -1.0f) {
            pan = -1.0f;
        }
        pan = 80.0f + 16.0f * pan;
        if (team->unk04A) {
            pitch = team->unk030 / team->unk034;
            pitch = 8191.0f * pitch - 8191.0f;
        }
        else {
            pitch /= 3.0f;
            pitch /= 9.0f;
            if (pitch > 1.0f) {
                pitch = 1.0f;
            }
            pitch = 8191.0f * pitch;
        }
        if (!lbl_1_data_2A0[1]) {
            lbl_1_bss_0[1] = HuAudFXPlay(0x93D);
            lbl_1_data_2A0[1] = 1;
        }
        HuAudFXPanning(lbl_1_bss_0[1], pan);
        HuAudFXPitchSet(lbl_1_bss_0[1], pitch);
    }
}

/* 369 insns */
void fn_1_85F4(M577_TEAM *team)
{
    HuVecF a;
    HuVecF b;
    float pt[2];
    M577_PLAYER *player;
    M577_WORK *work;
    M577_CART *cart;
    float (*p)[2];
    s32 i;
    s32 num;
    M577_TASK *node;
    M577_TASK *node2;
    s32 k;
    float pan;
    float t;

    work = lbl_1_bss_C->data;
    player = team->unk000[0];
    cart = player->unk020;
    switch (team->unk046) {
        case 0:
            if (lbl_1_data_2A0[0]) {
                lbl_1_data_2A0[0] = 0;
                HuAudFXStop(lbl_1_bss_0[0]);
            }
            pan = cart->unk020.x / 700.0f;
            if (pan > 1.0f) {
                pan = 1.0f;
            }
            if (pan < -1.0f) {
                pan = -1.0f;
            }
            pan = 48.0f + 16.0f * pan;
            HuAudFXPlayPan(0x93E, pan);
            HuAudFXPlayPan(lbl_1_data_2A8[player->unk03A], pan);
            num = team->unk028->unk004 / 2 - 1;
            p = team->unk028->unk000;
            pt[1] = cart->unk01C;
            for (i = 0; i < num; i++, p += 2) {
                a.x = (p[0][0] + p[1][0]) / 2.0f;
                a.y = (p[0][1] + p[1][1]) / 2.0f;
                b.x = (p[2][0] + p[3][0]) / 2.0f;
                b.y = (p[2][1] + p[3][1]) / 2.0f;
                fn_1_A754(&cart->unk008, &a.x, &b.x);
                pt[0] = fn_1_A9D0(&cart->unk008, pt[1]);
                if (fn_1_B4D0(pt, p)) {
                    cart->unk04C = pt[0];
                    break;
                }
            }
            cart->unk050 = cart->unk018;
            cart->unk048 = 0.0f;
            cart->unk040->unk014 = cart->unk040->unk000.x;
            cart->unk040->unk018 = 0.0f;
            cart->unk040->unk01C = cart->unk04C;
            player->unk050 = 0;
            fn_1_B720(cart->unk044, 0);
            fn_1_B720(cart->unk040->unk010, 0);
            node = work->unk0A8.unk004;
            if (node) {
                work->unk0A8.unk004 = node->unk004;
                node->unk00C = fn_1_AB34;
                node->unk010 = player;
                node->unk004 = work->unk0A8.unk000;
                if (node->unk004) {
                    node->unk004->unk000 = node;
                }
                work->unk0A8.unk000 = node;
            }
            player->unk04C = 0;
            team->unk046++;
            break;
        case 1:
            if (player->unk04A != 1) {
                team->unk046++;
                team->unk048 = 0;
            }
            break;
        case 2:
            team->unk048++;
            num = team->unk020[0]->unk4A8;
            if (team->unk048 & 1) {
                Hu3DModelAttrSet(cart->unk05C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(cart->unk060, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(cart->unk040->unk028, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(cart->unk040->unk02C, HU3D_ATTR_DISPOFF);
                for (i = 0; i < num; i++) {
                    Hu3DModelAttrSet(team->unk020[0]->unk4AC[i], HU3D_ATTR_DISPOFF);
                }
            }
            else {
                Hu3DModelAttrReset(cart->unk05C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(cart->unk060, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(cart->unk040->unk028, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(cart->unk040->unk02C, HU3D_ATTR_DISPOFF);
                for (i = 0; i < num; i++) {
                    Hu3DModelAttrReset(team->unk020[0]->unk4AC[i], HU3D_ATTR_DISPOFF);
                }
            }
            t = team->unk048 / 30.0f;
            cart->unk020.x = cart->unk050 * (1.0f - t) + cart->unk04C * t;
            cart->unk040->unk000.x = cart->unk040->unk014 * (1.0f - t) + cart->unk040->unk01C * t;
            team->unk018->unk000.x = 0.5f * cart->unk020.x;
            if (team->unk048 == 30) {
                Hu3DModelAttrReset(cart->unk05C, HU3D_ATTR_DISPOFF);
                cart->unk040->unk014 = cart->unk020.x;
                team->unk044 = 0;
                team->unk02C = fn_1_72D0;
                player->unk04A = 0;
                node2 = work->unk0A8.unk004;
                if (node2) {
                    work->unk0A8.unk004 = node2->unk004;
                    node2->unk00C = fn_1_B318;
                    node2->unk010 = player;
                    node2->unk004 = work->unk0A8.unk000;
                    if (node2->unk004) {
                        node2->unk004->unk000 = node2;
                    }
                    work->unk0A8.unk000 = node2;
                }
                player->unk034 = 90;
            }
            break;
    }
    Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
    Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
    Hu3DModelPosSetV(cart->unk060, &cart->unk020);
    Hu3DModelPosSetV(cart->unk040->unk02C, &cart->unk040->unk000);
}

/* 498 insns */
void fn_1_8BB8(M577_TEAM *team)
{
    HuVecF a;
    HuVecF b;
    float pt[2];
    s32 i;
    M577_WORK *work;
    M577_CART *cart;
    float (*p)[2];
    M577_PLAYER *player;
    s32 j;
    s32 num;
    M577_TASK *node;
    M577_TASK *node2;
    M577_TASK *node3;
    float maxX2;
    float minX2;
    float pan;
    float t;
    float maxX;
    float minX;

    work = lbl_1_bss_C->data;
    switch (team->unk046) {
        case 0:
            if (lbl_1_data_2A0[1]) {
                lbl_1_data_2A0[1] = 0;
                HuAudFXStop(lbl_1_bss_0[1]);
            }
            maxX = -10000.0f;
            minX = 10000.0f;
            num = team->unk028->unk004 / 2 - 1;
            for (i = 0; i < 3; i++) {
                player = team->unk000[i];
                cart = player->unk020;
                if (cart->unk020.x > maxX) {
                    maxX = cart->unk020.x;
                }
                if (cart->unk020.x < minX) {
                    minX = cart->unk020.x;
                }
                fn_1_B720(cart->unk044, 0);
                if (player->unk04A) {
                    node = work->unk0A8.unk004;
                    if (node) {
                        work->unk0A8.unk004 = node->unk004;
                        node->unk00C = fn_1_AB34;
                        node->unk010 = player;
                        node->unk004 = work->unk0A8.unk000;
                        if (node->unk004) {
                            node->unk004->unk000 = node;
                        }
                        work->unk0A8.unk000 = node;
                    }
                    player->unk04C = 0;
                }
                else {
                    node2 = work->unk0A8.unk004;
                    if (node2) {
                        work->unk0A8.unk004 = node2->unk004;
                        node2->unk00C = fn_1_AF68;
                        node2->unk010 = player;
                        node2->unk004 = work->unk0A8.unk000;
                        if (node2->unk004) {
                            node2->unk004->unk000 = node2;
                        }
                        work->unk0A8.unk000 = node2;
                    }
                    player->unk04C = 0;
                }
                if (player->unk04A) {
                    p = team->unk028->unk000;
                    pt[1] = cart->unk01C;
                    for (j = 0; j < num; j++, p += 2) {
                        a.x = (p[0][0] + p[1][0]) / 2.0f;
                        a.y = (p[0][1] + p[1][1]) / 2.0f;
                        b.x = (p[2][0] + p[3][0]) / 2.0f;
                        b.y = (p[2][1] + p[3][1]) / 2.0f;
                        fn_1_A754(&cart->unk008, &a.x, &b.x);
                        pt[0] = fn_1_A9D0(&cart->unk008, pt[1]);
                        if (fn_1_B4D0(pt, p)) {
                            cart->unk04C = pt[0];
                            break;
                        }
                    }
                    cart->unk050 = cart->unk018;
                    cart->unk048 = 0.0f;
                    player->unk050 = 0;
                }
            }
            pan = (maxX + minX) / 700.0f;
            if (pan > 1.0f) {
                pan = 1.0f;
            }
            if (pan < -1.0f) {
                pan = -1.0f;
            }
            pan = 80.0f + 16.0f * pan;
            HuAudFXPlayPan(0x93F, pan);
            for (i = 0; i < 3; i++) {
                player = team->unk000[i];
                if (player->unk04A) {
                    HuAudFXPlayPan(lbl_1_data_2A8[player->unk03A], pan);
                }
            }
            team->unk046++;
            break;
        case 1:
            for (i = 0; i < 3; i++) {
                player = team->unk000[i];
                if (player->unk04A == 1) {
                    break;
                }
            }
            if (i == 3) {
                team->unk046++;
                team->unk048 = 0;
            }
            break;
        case 2:
            team->unk048++;
            if (team->unk048 == 30) {
                Hu3DModelAttrReset(team->unk00C[0]->unk05C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(team->unk00C[1]->unk05C, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(team->unk00C[2]->unk05C, HU3D_ATTR_DISPOFF);
                team->unk044 = 0;
                team->unk02C = fn_1_7D24;
                for (i = 0; i < 3; i++) {
                    player = team->unk000[i];
                    node3 = work->unk0A8.unk004;
                    if (node3) {
                        work->unk0A8.unk004 = node3->unk004;
                        node3->unk00C = fn_1_B318;
                        node3->unk010 = player;
                        node3->unk004 = work->unk0A8.unk000;
                        if (node3->unk004) {
                            node3->unk004->unk000 = node3;
                        }
                        work->unk0A8.unk000 = node3;
                    }
                    player->unk034 = 90;
                    if (player->unk04A == 2) {
                        player->unk04A = 0;
                    }
                }
            }
            num = team->unk020[0]->unk4A8;
            if (team->unk048 & 1) {
                for (i = 0; i < 3; i++) {
                    cart = team->unk00C[i];
                    Hu3DModelAttrSet(cart->unk05C, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(cart->unk060, HU3D_ATTR_DISPOFF);
                }
                for (j = 0; j < num; j++) {
                    Hu3DModelAttrSet(team->unk020[0]->unk4AC[j], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(team->unk020[1]->unk4AC[j], HU3D_ATTR_DISPOFF);
                }
            }
            else {
                for (i = 0; i < 3; i++) {
                    cart = team->unk00C[i];
                    Hu3DModelAttrReset(cart->unk05C, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(cart->unk060, HU3D_ATTR_DISPOFF);
                }
                for (j = 0; j < num; j++) {
                    Hu3DModelAttrReset(team->unk020[0]->unk4AC[j], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(team->unk020[1]->unk4AC[j], HU3D_ATTR_DISPOFF);
                }
            }
            t = team->unk048 / 30.0f;
            for (i = 0; i < 3; i++) {
                player = team->unk000[i];
                cart = player->unk020;
                if (player->unk04A == 2) {
                    cart->unk020.x = cart->unk050 * (1.0f - t) + cart->unk04C * t;
                }
            }
            maxX2 = -20000.0f;
            minX2 = 20000.0f;
            for (j = 0; j < 3; j++) {
                cart = team->unk00C[j];
                if (cart->unk020.x > maxX2) {
                    maxX2 = cart->unk020.x;
                }
                if (cart->unk020.x < minX2) {
                    minX2 = cart->unk020.x;
                }
            }
            team->unk018->unk000.x = 0.5f * (maxX2 + minX2);
            break;
    }
    Hu3DModelPosSetV(team->unk00C[0]->unk05C, &team->unk00C[0]->unk020);
    Hu3DModelPosSetV(team->unk00C[1]->unk05C, &team->unk00C[1]->unk020);
    Hu3DModelPosSetV(team->unk00C[2]->unk05C, &team->unk00C[2]->unk020);
    Hu3DModelPosSetV(team->unk00C[0]->unk060, &team->unk00C[0]->unk020);
    Hu3DModelPosSetV(team->unk00C[1]->unk060, &team->unk00C[1]->unk020);
    Hu3DModelPosSetV(team->unk00C[2]->unk060, &team->unk00C[2]->unk020);
}

/* 546 insns */
void fn_1_9380(M577_TEAM *team)
{
    M577_PLAYER *player;
    M577_CART *cart;
    M577_TOW *tow;
    float pitch;
    float pan;
    float dist;
    float d;
    float k;
    float time;

    player = team->unk000[0];
    cart = player->unk020;
    if (team->unk04A == 0) {
        M577_WORK *work = lbl_1_bss_C->data;
        team->unk030 = team->unk034;
        fn_1_B720(cart->unk044, 1);
        fn_1_B720(cart->unk040->unk010, 1);
    }
    else {
        team->unk030 -= 0.05f;
        if (team->unk030 < 0.0f) {
            team->unk030 = 0.0f;
            team->unk02C = fn_1_7040;
            team->unk046 = 0;
        }
        if (team->unk030 < team->unk034 / 4.0f) {
            fn_1_B720(cart->unk044, 0);
            fn_1_B720(cart->unk040->unk010, 0);
        }
    }
    cart->unk020.x = (cart->unk020.x > 0.0f) ? ((cart->unk020.x - 1.5f < 0.0f) ? 0.0f : cart->unk020.x - 1.5f)
                                             : ((1.5f + cart->unk020.x > 0.0f) ? 0.0f : 1.5f + cart->unk020.x);
    cart->unk048 = 0.0f;
    tow = cart->unk040;
    tow->unk000.x += tow->unk018;
    d = tow->unk000.x - cart->unk020.x;
    dist = fabsf(d);
    if (dist > 100.0f) {
        k = 0.2f * (100.0f - dist);
        cart->unk020.x -= k * (d / dist);
        tow->unk000.x += k * (d / dist);
    }
    tow->unk018 = 0.9f * (tow->unk000.x - tow->unk014);
    tow->unk014 = tow->unk000.x;
    team->unk03C += team->unk030;
    team->unk01C->unk000 = (90.0f * team->unk03C) / team->unk028->unk008;
    team->unk018->unk000.x = 0.5f * cart->unk020.x;
    Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
    Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
    cart->unk058 = cart->unk058 - (360.0f * team->unk030) / 273.94686980565;
    while (cart->unk058 > 180.0f) {
        cart->unk058 -= 360.0f;
    }
    while (cart->unk058 < -180.0f) {
        cart->unk058 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
    Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
    Hu3DModelPosSet(cart->unk040->unk02C, cart->unk040->unk000.x, cart->unk040->unk000.y, cart->unk040->unk000.z);
    cart->unk040->unk024 -= (360.0f * team->unk030) / 273.94686980565;
    while (cart->unk040->unk024 > 180.0f) {
        cart->unk040->unk024 -= 360.0f;
    }
    while (cart->unk040->unk024 < -180.0f) {
        cart->unk040->unk024 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk040->unk02A, cart->unk040->unk024, 0.0f, 0.0f);
    player->unk02C = (player->unk02C > 0.5f) ? ((player->unk02C - 0.05f < 0.5f) ? 0.5f : player->unk02C - 0.05f)
                                             : ((0.05f + player->unk02C > 0.5f) ? 0.5f : 0.05f + player->unk02C);
    time = player->unk028 * player->unk02C;
    CharMotionTimeSet(player->unk03A, time);
    Hu3DMotionTimeSet(cart->unk05C, time);
    if (team->unk030 < team->unk034 / 4.0f) {
        if (lbl_1_data_2A0[0]) {
            lbl_1_data_2A0[0] = 0;
            HuAudFXStop(lbl_1_bss_0[0]);
        }
    }
    else {
        pan = cart->unk020.x / 700.0f;
        if (pan > 1.0f) {
            pan = 1.0f;
        }
        if (pan < -1.0f) {
            pan = -1.0f;
        }
        pan = 48.0f + 16.0f * pan;
        if (team->unk04A) {
            pitch = team->unk030 / team->unk034;
            pitch = 8191.0f * pitch - 8191.0f;
        }
        else {
            pitch = fabsf(cart->unk048) / 10.0f;
            if (pitch > 1.0f) {
                pitch = 1.0f;
            }
            pitch = 8191.0f * pitch;
        }
        if (!lbl_1_data_2A0[0]) {
            lbl_1_bss_0[0] = HuAudFXPlay(0x93C);
            lbl_1_data_2A0[0] = 1;
        }
        HuAudFXPanning(lbl_1_bss_0[0], pan);
        HuAudFXPitchSet(lbl_1_bss_0[0], pitch);
    }
}

/* 473 insns */
void fn_1_9C08(M577_TEAM *team)
{
    M577_PLAYER *player;
    M577_CART *cart;
    s32 i;
    float pitch;
    float pan;
    float maxX;
    float minX;
    float time;

    if (team->unk04A == 0) {
        M577_WORK *work = lbl_1_bss_C->data;
        team->unk030 = team->unk034;
        for (i = 0; i < 3; i++) {
            player = team->unk000[i];
            cart = player->unk020;
            fn_1_B720(cart->unk044, 1);
        }
    }
    else {
        team->unk030 -= 0.05f;
        if (team->unk030 < 0.0f) {
            team->unk030 = 0.0f;
            team->unk02C = fn_1_7040;
            team->unk046 = 0;
        }
        if (team->unk030 < team->unk034 / 4.0f) {
            for (i = 0; i < 3; i++) {
                player = team->unk000[i];
                cart = player->unk020;
                fn_1_B720(cart->unk044, 0);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        player = team->unk000[i];
        cart = player->unk020;
        cart->unk020.x = (cart->unk020.x > 0.0f) ? ((cart->unk020.x - 1.5f < 0.0f) ? 0.0f : cart->unk020.x - 1.5f)
                                                 : ((1.5f + cart->unk020.x > 0.0f) ? 0.0f : 1.5f + cart->unk020.x);
        cart->unk048 = 0.0f;
    }
    team->unk03C += team->unk030;
    team->unk01C->unk000 = (90.0f * team->unk03C) / team->unk028->unk008;
    pitch = 0.0f;
    maxX = -20000.0f;
    minX = 20000.0f;
    for (i = 0; i < 3; i++) {
        player = team->unk000[i];
        cart = player->unk020;
        player->unk02C = (player->unk02C > 0.5f) ? ((player->unk02C - 0.05f < 0.5f) ? 0.5f : player->unk02C - 0.05f)
                                                 : ((0.05f + player->unk02C > 0.5f) ? 0.5f : 0.05f + player->unk02C);
        time = player->unk028 * player->unk02C;
        CharMotionTimeSet(player->unk03A, time);
        Hu3DMotionTimeSet(cart->unk05C, time);
        Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
        Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
        cart->unk058 = cart->unk058 - (360.0f * team->unk030) / 273.94686980565;
        while (cart->unk058 > 180.0f) {
            cart->unk058 -= 360.0f;
        }
        while (cart->unk058 < -180.0f) {
            cart->unk058 += 360.0f;
        }
        Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
        if (cart->unk020.x > maxX) {
            maxX = cart->unk020.x;
        }
        if (cart->unk020.x < minX) {
            minX = cart->unk020.x;
        }
        pitch += fabsf(cart->unk048);
    }
    team->unk018->unk000.x = 0.5f * (maxX + minX);
    if (team->unk030 < team->unk034 / 4.0f) {
        if (lbl_1_data_2A0[1]) {
            lbl_1_data_2A0[1] = 0;
            HuAudFXStop(lbl_1_bss_0[1]);
        }
    }
    else {
        pan = (maxX + minX) / 700.0f;
        if (pan > 1.0f) {
            pan = 1.0f;
        }
        if (pan < -1.0f) {
            pan = -1.0f;
        }
        pan = 80.0f + 16.0f * pan;
        if (team->unk04A) {
            pitch = team->unk030 / team->unk034;
            pitch = 8191.0f * pitch - 8191.0f;
        }
        else {
            pitch /= 3.0f;
            pitch /= 9.0f;
            if (pitch > 1.0f) {
                pitch = 1.0f;
            }
            pitch = 8191.0f * pitch;
        }
        if (!lbl_1_data_2A0[1]) {
            lbl_1_bss_0[1] = HuAudFXPlay(0x93D);
            lbl_1_data_2A0[1] = 1;
        }
        HuAudFXPanning(lbl_1_bss_0[1], pan);
        HuAudFXPitchSet(lbl_1_bss_0[1], pitch);
    }
}

/* 152 insns */
void fn_1_A36C(M577_TEAM *team)
{
    M577_PLAYER *player = team->unk000[0];
    M577_CART *cart = player->unk020;

    Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
    Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
    cart->unk058 -= 19.7118514397737;
    while (cart->unk058 > 180.0f) {
        cart->unk058 -= 360.0f;
    }
    while (cart->unk058 < -180.0f) {
        cart->unk058 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
    Hu3DModelPosSetV(cart->unk040->unk028, &cart->unk040->unk000);
    Hu3DModelPosSet(cart->unk040->unk02C, cart->unk040->unk000.x, cart->unk040->unk000.y, cart->unk040->unk000.z);
    cart->unk040->unk024 -= 19.7118514397737;
    while (cart->unk040->unk024 > 180.0f) {
        cart->unk040->unk024 -= 360.0f;
    }
    while (cart->unk040->unk024 < -180.0f) {
        cart->unk040->unk024 += 360.0f;
    }
    Hu3DModelRotSet(cart->unk040->unk02A, cart->unk040->unk024, 0.0f, 0.0f);
    if (lbl_1_data_2A0[0] == 0) {
        lbl_1_bss_0[0] = HuAudFXPlay(0x93C);
        lbl_1_data_2A0[0] = 1;
    }
    HuAudFXPanning(lbl_1_bss_0[0], 64);
    HuAudFXPitchSet(lbl_1_bss_0[0], 0);
}

/* 98 insns */
void fn_1_A5CC(M577_TEAM *team)
{
    M577_PLAYER *player;
    s32 i;
    M577_CART *cart;

    for (i = 0; i < 3; i++) {
        player = team->unk000[i];
        cart = player->unk020;
        Hu3DModelPosSetV(cart->unk05C, &cart->unk020);
        Hu3DModelPosSet(cart->unk060, cart->unk020.x, cart->unk020.y, cart->unk020.z);
        cart->unk058 -= 19.7118514397737;
        while (cart->unk058 > 180.0f) {
            cart->unk058 -= 360.0f;
        }
        while (cart->unk058 < -180.0f) {
            cart->unk058 += 360.0f;
        }
        Hu3DModelRotSet(cart->unk05E, cart->unk058, 0.0f, 0.0f);
    }
    if (lbl_1_data_2A0[1] == 0) {
        lbl_1_bss_0[1] = HuAudFXPlay(0x93D);
        lbl_1_data_2A0[1] = 1;
    }
    HuAudFXPanning(lbl_1_bss_0[1], 64);
    HuAudFXPitchSet(lbl_1_bss_0[1], 0);
}

/* 96 insns */
void fn_1_A754(M577_LINE *line, float *p0, float *p1)
{
    line->unk00C = p0[0] == p1[0];
    if (line->unk00C) {
        line->unk008 = p0[0];
    }
    else {
        line->unk000 = (p1[1] - p0[1]) / (p1[0] - p0[0]);
        line->unk008 = p0[1] + -line->unk000 * p0[0];
        line->unk004 = sqrtf(1.0f + line->unk000 * line->unk000);
    }
}

/* 63 insns */
float fn_1_A8D4(M577_LINE *line, float *pos)
{
    float dist;

    if (line->unk00C) {
        dist = fabsf(line->unk008 - pos[0]);
    }
    else {
        dist = fabsf(line->unk008 + (line->unk000 * pos[0] - pos[1])) / line->unk004;
    }
    return dist;
}

/* 31 insns */
float fn_1_A9D0(M577_LINE *line, float z)
{
    float x;

    if (line->unk00C) {
        x = line->unk008;
    }
    else {
        x = (z - line->unk008) / ((0.0f == line->unk000) ? 0.000001f : line->unk000);
    }
    return x;
}

/* 58 insns */
void fn_1_AA4C(M577_WORK *work)
{
    M577_TEAM *team;

    team = &work->unk010[0];
    Hu3DModelObjPosGet(team->unk00C[0]->unk05C, lbl_1_data_384, team->unk00C[0]->unk03C);
    Hu3DModelObjPosGet(team->unk00C[0]->unk040->unk028, lbl_1_data_38B, team->unk00C[0]->unk040->unk00C);
    team = &work->unk010[1];
    Hu3DModelObjPosGet(team->unk00C[0]->unk05C, lbl_1_data_384, team->unk00C[0]->unk03C);
    Hu3DModelObjPosGet(team->unk00C[1]->unk05C, lbl_1_data_38B, team->unk00C[1]->unk038);
    Hu3DModelObjPosGet(team->unk00C[1]->unk05C, lbl_1_data_384, team->unk00C[1]->unk03C);
    Hu3DModelObjPosGet(team->unk00C[2]->unk05C, lbl_1_data_38B, team->unk00C[2]->unk038);
}

#define M577_SPEED_EASE(v)                                                                  \
    (((v) > 0.5f) ? (((v) - 0.05f < 0.5f) ? 0.5f : (v) - 0.05f)                             \
                  : ((0.05f + (v) > 0.5f) ? 0.5f : 0.05f + (v)))

/* 269 insns */
s32 fn_1_AB34(M577_TASK *task)
{
    float time;
    float t;
    s32 done = 0;
    M577_PLAYER *player = task->unk010;

    switch (player->unk04C) {
        case 0:
            CharMotionShiftSet(player->unk03A, player->unk018->mtnId[3], 0.0f, 5.0f, 0x40000001);
            omVibrate(player->unk038, 60, 12, 0);
            player->unk04E = 0;
            player->unk04C++;
        case 1:
            player->unk04E++;
            if (player->unk04E == 60) {
                player->unk04C++;
            }
            t = player->unk04E / 60.0f;
            player->unk020->unk020.y = player->unk020->unk054
                + 15.0f * (1.0f - t) * (1.0 - cos(M_PI * (72.0f * player->unk04E) / 180.0));
            player->unk02C = M577_SPEED_EASE(player->unk02C);
            time = player->unk028 * player->unk02C;
            Hu3DMotionTimeSet(player->unk020->unk05C, time);
            break;
        case 2:
            player->unk020->unk020.y = player->unk020->unk054;
            CharMotionShiftSet(player->unk03A, player->unk018->mtnId[4], 0.0f, 5.0f, 0);
            player->unk04C++;
        case 3:
            if (player->unk018->mtnId[4] == Hu3DMotionIDGet(player->unk036)) {
                player->unk04C++;
            }
            break;
        case 4:
            if (Hu3DMotionEndCheck(player->unk036)) {
                CharMotionSet(player->unk03A, player->unk018->mtnId[5]);
                player->unk04C++;
            }
            break;
        case 5:
            if (Hu3DMotionEndCheck(player->unk036)) {
                CharMotionSet(player->unk03A, player->unk018->mtnId[2]);
                CharModelAttrSet(player->unk03A, 0x40000002);
                player->unk02C = 0.5f;
                time = player->unk028 * player->unk02C;
                CharMotionTimeSet(player->unk03A, time);
                Hu3DMotionTimeSet(player->unk020->unk05C, time);
                player->unk04A = 2;
                done = 1;
            }
            break;
    }
    return done;
}

/* 115 insns */
s32 fn_1_AF68(M577_TASK *task)
{
    float time;
    s32 done = 0;
    M577_PLAYER *player = task->unk010;

    switch (player->unk04C) {
        case 0:
            omVibrate(player->unk038, 60, 4, 2);
            player->unk04E = 0;
            player->unk04C++;
        case 1:
            player->unk04E++;
            if (player->unk04E == 60) {
                done = 1;
            }
            player->unk02C = M577_SPEED_EASE(player->unk02C);
            time = player->unk028 * player->unk02C;
            CharMotionTimeSet(player->unk03A, time);
            Hu3DMotionTimeSet(player->unk020->unk05C, time);
            break;
    }
    return done;
}

/* 78 insns */
void fn_1_B134(M577_WORK *work)
{
    float t;
    float y;

    t = work->unk010[0].unk03C / work->unk1AC8.unk008;
    if (t > 1.0f) {
        t = 1.0f;
    }
    y = 400.0f * (1.0f - t) + 120.0f * t;
    espPosSet(work->unk1B5A, 276.0f, y);
    t = work->unk010[1].unk03C / work->unk1AC8.unk008;
    if (t > 1.0f) {
        t = 1.0f;
    }
    y = 400.0f * (1.0f - t) + 120.0f * t;
    espPosSet(work->unk1B5C, 300.0f, y);
}

/* 43 insns */
void fn_1_B26C(M577_WORK *work)
{
    s16 mdl = work->unk1B68[13];
    float rot;
    float t;

    work->unk1B54 += 10.0f;
    t = work->unk1B54 / work->unk1AC8.unk008;
    rot = 90.0f * t;
    Hu3DModelRotSet(mdl, rot, 0.0f, 0.0f);
}

/* 45 insns */
s32 fn_1_B318(M577_TASK *task)
{
    s32 done = 0;
    M577_PLAYER *player = task->unk010;

    player->unk034--;
    if (player->unk034 == 0) {
        done = 1;
    }
    if (player->unk034 & 1) {
        Hu3DModelAttrSet(player->unk020->unk05C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(player->unk020->unk060, HU3D_ATTR_DISPOFF);
    }
    else {
        Hu3DModelAttrReset(player->unk020->unk05C, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(player->unk020->unk060, HU3D_ATTR_DISPOFF);
    }
    return done;
}

/* 25 insns */
s32 fn_1_B3CC(M577_TASK *task)
{
    s16 *count = task->unk010;

    if (*count == 1) {
        HuAudFXPlayPan(0x942, 80);
        return 1;
    }
    (*count)++;
    return 0;
}

