/*
 * m576dll m576.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m576Dll/asm/REL/m576Dll/m576.s.
 */

#include "REL/m576dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/process.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/wipe.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"

#include "dolphin/mtx.h"
#include "math.h"
#include "string.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* double lbl_1_rodata_10 = 180; */
/* 0x18 */ /* float lbl_1_rodata_18 = 0.0f; */
/* 0x1C */ /* float lbl_1_rodata_1C = 71.42857f; */
/* 0x20 */ /* double lbl_1_rodata_20 = 4503601774854144; */
/* 0x28 */ /* float lbl_1_rodata_28 = 100.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 10.0f; */
/* 0x30 */ /* double lbl_1_rodata_30 = 4503599627370496; */
/* 0x38 */ /* double lbl_1_rodata_38 = 0.000001; */
/* 0x40 */ /* float lbl_1_rodata_40 = 0.01f; */
/* 0x44 */ /* float lbl_1_rodata_44 = -0.01f; */
/* 0x48 */ /* float lbl_1_rodata_48 = 10000000000.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 64.0f; */
/* 0x50 */ /* float lbl_1_rodata_50 = 16.0f; */
/* 0x54 */ /* float lbl_1_rodata_54 = 300.0f; */
/* 0x58 */ /* float lbl_1_rodata_58 = 700.0f; */
/* 0x5C */ /* float lbl_1_rodata_5C = 111.0f; */
/* 0x60 */ /* s32 lbl_1_rodata_60[3] = { 0x00000000, 0x45FA0000, 0x00000000 }; */
/* 0x6C */ /* s32 lbl_1_rodata_6C[3] = { 0x00000000, 0x00000000, 0x3F800000 }; */
/* 0x78 */ /* s32 lbl_1_rodata_78[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x84 */ /* s32 lbl_1_rodata_84[3] = { 0x00000000, 0xBF800000, 0x00000000 }; */
/* 0x90 */ /* float lbl_1_rodata_90 = 270.0f; */
/* 0x94 */ /* float lbl_1_rodata_94 = -50.0f; */
/* 0x98 */ /* float lbl_1_rodata_98 = 5000.0f; */
/* 0x9C */ /* float lbl_1_rodata_9C = 20.0f; */
/* 0xA0 */ /* float lbl_1_rodata_A0 = 15000.0f; */
/* 0xA4 */ /* float lbl_1_rodata_A4 = 1.2f; */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 640.0f; */
/* 0xAC */ /* float lbl_1_rodata_AC = 480.0f; */
/* 0xB0 */ /* float lbl_1_rodata_B0 = 1.0f; */
/* 0xB4 */ /* float lbl_1_rodata_B4 = 1000.0f; */
/* 0xB8 */ /* float lbl_1_rodata_B8 = -1.0f; */
/* 0xBC */ /* float lbl_1_rodata_BC = 15.0f; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = 10000.0f; */
/* 0xC4 */ /* float lbl_1_rodata_C4 = 0.5f; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 0.1; */
/* 0xD0 */ /* double lbl_1_rodata_D0 = 3201; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 0.5; */
/* 0xE0 */ /* double lbl_1_rodata_E0 = 3; */
/* 0xE8 */ /* float lbl_1_rodata_E8 = 180.0f; */
/* 0xF0 */ /* double lbl_1_rodata_F0 = 3.141592653589793; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 115.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = 50.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 150.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 75.0f; */
/* 0x108 */ /* float lbl_1_rodata_108 = 1300.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 80.0f; */
/* 0x110 */ /* float lbl_1_rodata_110 = -15.0f; */
/* 0x114 */ /* float lbl_1_rodata_114 = 45.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 0.017453292f; */
/* 0x120 */ /* double lbl_1_rodata_120 = 1.5; */
/* 0x128 */ /* float lbl_1_rodata_128 = 63.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 40.0f; */
/* 0x130 */ /* float lbl_1_rodata_130 = 160.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 7.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 142.85715f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 500.0f; */
/* 0x140 */ /* float lbl_1_rodata_140 = 3.0f; */
/* 0x144 */ /* float lbl_1_rodata_144 = 200.0f; */
/* 0x148 */ /* float lbl_1_rodata_148 = 5.0f; */
/* 0x14C */ /* float lbl_1_rodata_14C = 450.0f; */
/* 0x150 */ /* float lbl_1_rodata_150[2] = { 1400.0f, 0.0f }; */

/* --- .data --- */
/* 0x0 */ MGSEQ_PARAM lbl_1_data_0 = { 45, 0, fn_1_48A0, fn_1_4920, fn_1_5288, fn_1_55C8, fn_1_5C04, fn_1_5EAC, fn_1_6730, fn_1_6734, fn_1_6764 };
/* 0x28 */ HuVecF lbl_1_data_28[4] = { { -300.0f, 1400.0f, 400.0f }, { 300.0f, 1400.0f, 400.0f }, { -300.0f, 1400.0f, 600.0f }, { 300.0f, 1400.0f, 600.0f } }; /* player start pos (fn_1_32CC) */
/* 0x58 */ HuVecF lbl_1_data_58[4] = { { -350.0f, 1400.0f, -280.0f }, { 450.0f, 1400.0f, -400.0f }, { 320.0f, 1400.0f, 400.0f }, { -500.0f, 1400.0f, 500.0f } }; /* lfs only (fn_1_FA0 ...) */
/* 0x88 */ HuVecF lbl_1_data_88[5] = { { 0.0f, 620.0f, -700.0f }, { -700.0f, 820.0f, -700.0f }, { 700.0f, 720.0f, -100.0f }, { -700.0f, 420.0f, 700.0f }, { 700.0f, 420.0f, 700.0f } }; /* slot actor start xz (fn_1_32CC) */
/* 0xC4 */ HuVecF lbl_1_data_C4[2] = { { -700.0f, 300.0f, 450.0f }, { 300.0f, 500.0f, -650.0f } }; /* model 3/4 pos (fn_1_32CC) */
/* 0xDC */ float lbl_1_data_DC[42] = { 0.0f, 520.0f, -650.0f, -500.0f, 0.0f, 550.0f, 250.0f, 0.0f, 700.0f, 580.0f, 200.0f, -580.0f, -500.0f, 300.0f, -400.0f, -730.0f, 300.0f, 300.0f, -670.0f, 300.0f, 700.0f, 140.0f, 500.0f, -650.0f, 700.0f, 550.0f, -100.0f, -700.0f, 300.0f, 450.0f, 480.0f, 500.0f, -650.0f, 600.7f, 500.0f, -470.0f, -300.0f, 300.0f, 750.0f, 200.0f, 500.0f, -100.0f };
/* 0x184 */ float lbl_1_data_184[12] = { -625.0f, 300.0f, 675.0f, -710.0f, 300.0f, 740.0f, 725.0f, 600.0f, -175.0f, 625.0f, 600.0f, -25.0f };
/* 0x1B4 */ HU3DPARMANPARAM lbl_1_data_1B4 = { /* was u8[0x50]: a big-endian float blob on the host (fn_1_5288) */
    40, 0,
    0.3f,
    30.0f,
    10.0f,
    { 0.0f, -0.2f, 0.0f },
    2.0f,
    1.0f,
    70.0f,
    0.98f,
    2,
    { { 255, 255, 255, 255 }, { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};
/* 0x204 */ GXColor lbl_1_data_204[5][4] = { /* per slot: colorStart[0..1], colorEnd[0..1] (fn_1_5288) */
    { { 255, 128, 128, 255 }, { 255, 64, 64, 255 }, { 255, 0, 0, 0 }, { 128, 64, 64, 0 } },
    { { 160, 160, 255, 255 }, { 128, 128, 255, 255 }, { 64, 64, 255, 0 }, { 128, 128, 255, 0 } },
    { { 128, 255, 128, 255 }, { 64, 255, 64, 255 }, { 0, 255, 0, 0 }, { 64, 255, 64, 0 } },
    { { 255, 255, 128, 255 }, { 255, 255, 64, 255 }, { 160, 160, 0, 0 }, { 160, 160, 64, 0 } },
    { { 192, 192, 255, 255 }, { 160, 160, 255, 255 }, { 64, 64, 128, 0 }, { 160, 160, 255, 0 } }
};
/* 0x254 */ s32 lbl_1_data_254[10] = { 0x00000200, 0x000001EC, 0x00000264, 0x000002B4, 0x0000028C, 0x000001C4, 0x000002A0, 0x000001D8, 0x00000278, 0x0000023C };
/* 0x27C */ HuVecF lbl_1_data_27C[4] = { { -300.0f, 0.0f, 400.0f }, { -100.0f, 0.0f, 400.0f }, { 100.0f, 0.0f, 400.0f }, { 300.0f, 0.0f, 400.0f } }; /* winner-screen player pos (fn_1_5EAC) */
/* 0x2AC */ char lbl_1_data_2AC[] = "m576 : \223\301\216\352\217\210\227\235 %d \202\314\203|\203W\203V\203\207\203\223\202\314\220\335\222\350\202\252\202\250\202\251\202\265\202\242\201@(Map No : %d, Attr : %x)\012";
/* 0x2F7 */ char lbl_1_data_2F7[] = "m576 : \223\301\216\352\217\210\227\235 %d \202\314\203|\203W\203V\203\207\203\223\202\252\214\251\202\302\202\251\202\347\202\310\202\242\012";
/* 0x326 */ char lbl_1_data_326[] = "m576 : \223\301\216\352\226\332\225W\203Z\203\213 %d \202\314\203|\203\212\203S\203\223\202\252\203q\203b\203g\202\265\202\310\202\242\201@(Map No : %d, Attr : %x)\012";
/* 0x371 */ char lbl_1_data_371[] = "m576 : \223\301\216\352\226\332\225W\203Z\203\213 %d \202\314\203|\203\212\203S\203\223\202\252\214\251\202\302\202\251\202\347\202\310\202\242\012";
/* 0x3A2 */ char lbl_1_data_3A2[] = "%d\n";
/* 0x3A6 */ char lbl_1_data_3A6[10] = "\224\273\222\350\n"; /* SJIS "judgement\n"; was s16[5] (byte-swapped on the host) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x2FC */ MGPLAYER *lbl_1_bss_2FC[5]; /* players 0..3; ->actor deref (fn_1_424 0x42C) */
/* 0x2EC */ M576_STAGEPL *lbl_1_bss_2EC[4]; /* COM work per COM player (fn_1_C1EC result, 0x4094); count lbl_1_bss_8 */
/* 0x2D8 */ MGACTOR *lbl_1_bss_2D8[5]; /* slot actors; ->pos/colGroundAttr (fn_1_668, fn_1_A54) */
/* 0x2C8 */ MGACTOR *lbl_1_bss_2C8[4]; /* actors param 4..7 (mdlId[6..9]) */
/* 0x2C4 */ s8 lbl_1_bss_2C4[4]; /* random permutation of 0..3 (stb/extsb [i]); dtk sized it 1 + 3 filler */
/* 0x2B4 */ s32 lbl_1_bss_2B4[4]; /* [0..1] -> 1, [2..3] -> 2 (fn_1_9EC) */
/* 0x2A0 */ s32 lbl_1_bss_2A0[5]; /* slot owner player no, -1 = free */
/* 0x28C */ s32 lbl_1_bss_28C[5]; /* slot particle manager id (extsh) */
/* 0x254 */ s32 lbl_1_bss_254[14]; /* MGACTOR_COLMAP_POLY.triNo per data_DC point */
/* 0x23C */ HuVecF lbl_1_bss_23C[2];
/* 0x20C */ HuVecF lbl_1_bss_20C[4]; /* player pos before MgActorExec (fn_1_4100) */
/* 0x7C */ HU3DPARMANPARAM lbl_1_bss_7C[5]; /* per-slot copy of data_1B4 (fn_1_5288) */
/* 0x58 */ HuVecF lbl_1_bss_58[3]; /* Hu3DCameraPosGet pos/up/target (fn_1_48A0) */
/* 0x54 */ s32 lbl_1_bss_54;
/* 0x40 */ s32 lbl_1_bss_40[5]; /* HuAudFX handles, [no-4] (fn_1_FA0) */
/* 0x3C */ s8 lbl_1_bss_3C[4]; /* per-player slot count, then win flag (stb/extsb [i]); dtk sized it 1 + 3 filler */
/* 0x28 */ s32 lbl_1_bss_28[5]; /* 0x14: 4-aligned, retype */
/* 0x24 */ s32 lbl_1_bss_24;
/* 0x20 */ s32 lbl_1_bss_20;
/* 0x1C */ s32 lbl_1_bss_1C;
/* 0x18 */ s32 lbl_1_bss_18;
/* 0x14 */ s32 lbl_1_bss_14;
/* 0x10 */ s32 lbl_1_bss_10;
/* 0xC */ s32 lbl_1_bss_C;
/* 0x8 */ s32 lbl_1_bss_8;
/* 0x4 */ OMOBJMAN *lbl_1_bss_4;
/* 0x0 */ OMOBJ *lbl_1_bss_0;

/*
 * Host fix: retail computes SE/voice volume as 111 + 16 * (coord / 700) with no
 * clamp, and stage coordinates reach 750, giving 128 -- out of musyx's 0..127
 * range. The host clamps; the GC build keeps the bare expression.
 */
#define M576_SEVOL(v) (v)

/* --- functions (reference order) --- */
/* 53 insns: fold an angle into (-180, 180) and step it toward 0 by b (0 inside the dead zone) */
float fn_1_A0(float a, float b)
{
    float t = fmod(a, 180.0);
    float r = t;
    if (fabsf(r) < b) {
        return 0.0f;
    }
    if (r > 0.0f) {
        r -= b;
    } else {
        r += b;
    }
    return r;
}

/* 18 insns */
s32 fn_1_174(s32 no, HuVecF *pos)
{
    if (pos) {
        *pos = ((HuVecF *)lbl_1_data_DC)[no];
    }
    return lbl_1_bss_254[no];
}

/* 30 insns */
BOOL fn_1_1BC(HuVecF *pos)
{
    *pos = lbl_1_bss_23C[0];
    return lbl_1_bss_C <= 71.42857f;
}

/* 30 insns */
BOOL fn_1_234(HuVecF *pos)
{
    *pos = lbl_1_bss_23C[1];
    return lbl_1_bss_10 <= 100.0f;
}

/* 94 insns */
void fn_1_2AC(HuVecF *pos, s32 range)
{
    pos->x += frandmod(range * 20) / 10.0f - range;
    pos->y += frandmod(range * 20) / 10.0f - range;
    pos->z += frandmod(range * 20) / 10.0f - range;
}

/* 8 insns */
s32 fn_1_424(s32 no)
{
    return lbl_1_bss_2FC[no]->stunType;
}

/* 86 insns */
BOOL fn_1_444(HuVecF *in, HuVecF *out)
{
    BOOL result;
    if (VECSquareMag(in) < 0.000001) {
        out->x = 0.01f * (frandmod(20) - 10.0f);
        out->z = 0.01f * (frandmod(20) - 10.0f);
        out->y = frandmod(2) ? 0.01f : -0.01f;
        VECNormalize(out, out);
        result = FALSE;
    } else {
        VECNormalize(in, out);
        result = TRUE;
    }
    return result;
}

/* 22 insns */
s32 fn_1_59C(void)
{
    s32 num = 0;
    s32 i = 5;
    while (i-- != 0) {
        if (lbl_1_bss_2A0[i] == -1) {
            num++;
        }
    }
    return num;
}

/* 29 insns */
s32 fn_1_5F4(s32 no, HuVecF *pos)
{
    if (pos) {
        MgActorPosGet(lbl_1_bss_2D8[no - 8], pos);
    }
    return lbl_1_bss_2A0[no - 8];
}

/* 76 insns */
s32 fn_1_668(MGPLAYER **playerP, HuVecF *pos, float *dist)
{
    HuVecF diff;
    float minDist = 10000000000.0f;
    s32 no = -1;
    s32 i = 5;
    float d;
    while (i-- != 0) {
        if (lbl_1_bss_2A0[i] == -1) {
            VECSubtract(&(*playerP)->actor->pos, &lbl_1_bss_2D8[i]->pos, &diff);
            d = VECSquareMag(&diff);
            if (minDist > d) {
                no = i + 8;
                minDist = d;
            }
        }
    }
    if (no >= 0) {
        if (pos) {
            *pos = lbl_1_bss_2D8[no - 8]->pos;
        }
        if (dist) {
            *dist = minDist;
        }
    }
    return no;
}

/* 25 insns */
s32 fn_1_798(MGPLAYER **playerP)
{
    s32 num = 0;
    s32 i = 5;
    while (i-- != 0) {
        if ((*playerP)->actor->param == lbl_1_bss_2A0[i]) {
            num++;
        }
    }
    return num;
}

/* 22 insns */
s32 fn_1_7FC(s32 playerNo)
{
    s32 num = 0;
    s32 i = 5;
    while (i-- != 0) {
        if (playerNo == lbl_1_bss_2A0[i]) {
            num++;
        }
    }
    return num;
}

/* 22 insns */
s32 fn_1_854(s32 playerNo)
{
    s32 num = 0;
    s32 i = 5;
    while (i-- != 0) {
        if (playerNo == lbl_1_bss_2A0[i]) {
            num++;
        }
    }
    return num;
}

/* 62 insns */
s32 fn_1_8AC(s32 *playerNoOut, HuVecF *pos)
{
    s32 num;
    s32 maxNo;
    s32 j;
    s32 max;
    s32 i;
    max = 0;
    for (i = 0; i < 4; i++) {
        num = 0;
        for (j = 0; j < 5; j++) {
            if (i == lbl_1_bss_2A0[j]) {
                num++;
            }
        }
        if (frandmod(2)) {
            if (max <= num) {
                maxNo = i;
                max = num;
            }
        } else {
            if (max < num) {
                maxNo = i;
                max = num;
            }
        }
    }
    if (max != 0) {
        if (playerNoOut) {
            *playerNoOut = maxNo;
        }
        if (pos) {
            MgActorPosGet(lbl_1_bss_2FC[maxNo]->actor, pos);
        }
    }
    return max;
}

/* 18 insns */
void fn_1_9A4(s32 playerNo, HuVecF *pos)
{
    MgActorPosGet(lbl_1_bss_2FC[playerNo]->actor, pos);
}

/* 26 insns */
s32 fn_1_9EC(s32 playerNo)
{
    if (lbl_1_bss_2B4[0] == playerNo || lbl_1_bss_2B4[1] == playerNo) {
        return 1;
    }
    if (lbl_1_bss_2B4[2] == playerNo || lbl_1_bss_2B4[3] == playerNo) {
        return 2;
    }
    return 0;
}

/* 28 insns */
u32 fn_1_A54(s32 no)
{
    switch (no) {
        case 0:
        case 1:
        case 2:
        case 3:
            return lbl_1_bss_2FC[no]->actor->colGroundAttr;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            return lbl_1_bss_2D8[no - 8]->colGroundAttr;
    }
    return 0;
}

/* 88 insns */
void fn_1_AC4(void)
{
    MGPLAYER *player;
    s32 i;
    while (1) {
        player = lbl_1_bss_2FC[0];
        if (lbl_1_bss_14 == 2) {
            for (i = 4; i-- != 0; player++) {
                CharModelVoicePanSet(player->charNo, 64.0f + 16.0f * (player->actor->pos.x / 300.0f));
                CharModelVoiceVolSet(player->charNo, 127);
            }
        } else {
            for (i = 4; i-- != 0; player++) {
                CharModelVoicePanSet(player->charNo, 64.0f + 16.0f * (player->actor->pos.x / 700.0f));
                CharModelVoiceVolSet(player->charNo, M576_SEVOL(111.0f + 16.0f * (player->actor->pos.z / 700.0f)));
            }
        }
        HuPrcVSleep();
    }
}

/* 15 insns */
void fn_1_C24(void)
{
    HuPrcChildCreate(fn_1_AC4, 200, 0x1000, 0, HuPrcCurrentGet());
}

/* 208 insns */
void ObjectSetup(void)
{
    HuVecF lightPos = { 0.0f, 8000.0f, 0.0f };
    HuVecF shadowUp = { 0.0f, 0.0f, 1.0f };
    HuVecF shadowTarget = { 0.0f, 0.0f, 0.0f };
    HuVecF lightDir = { 0.0f, -1.0f, 0.0f };
    HU3DLIGHTID lightId;

    lbl_1_bss_4 = MgActorObjectSetup();
    CRot.x = 270.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    Center.x = 0.0f;
    Center.y = 300.0f;
    Center.z = -50.0f;
    CZoom = 5000.0f;
    Hu3DCameraCreate(HU3D_CAM0);
    Hu3DCameraPerspectiveSet(HU3D_CAM0, 20.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(HU3D_CAM0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightStaticSet(lightId, TRUE);
    Hu3DGLightPosSetV(lightId, &lightPos, &lightDir);
    Hu3DShadowCreate(15.0f, 20.0f, 10000.0f);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&lightPos, &shadowUp, &shadowTarget);
    Hu3DShadowSizeSet(240);
    lbl_1_bss_0 = omAddObjEx(lbl_1_bss_4, 16, 20, 0, -1, fn_1_32CC);
    lbl_1_bss_8 = 0;
    lbl_1_bss_C = 0;
    lbl_1_bss_10 = 0;
    lbl_1_bss_14 = 0;
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(7, -1);
}

/* 125 insns */
void fn_1_FA0(MGACTOR *actor, int param)
{
    HuVecF up;
    s32 face;
    s32 no = actor->param;

    if (no < 13 && (actor->colGroundAttr & 0x407F) != 0) {
        if (actor->colMesh == 0) {
            face = actor->colFace;
        } else {
            face = -1;
        }
        fn_1_BAF4(no, face);
        switch (no) {
            case 4:
            case 5:
            case 6:
            case 7:
                up.x = up.z = 0.0f;
                up.y = 1.0f;
                if (VECDotProduct(&actor->colNorm, &up) < 0.1) {
                    break;
                }
                MgActorColAttrSet(actor, 2);
                actor->gravity = 0.0f;
                memset(&actor->forceA, 0, sizeof(HuVecF));
                actor->velY = 0.0f;
                Hu3DModelAttrReset(actor->mdlId, 0x40000002);
                HuAudFXStop(lbl_1_bss_40[no - 4]);
                HuAudFXPlayVolPan(0x93B, M576_SEVOL(111.0f + 16.0f * (lbl_1_data_58[no - 4].z / 700.0f)),
                    64.0f + 16.0f * (lbl_1_data_58[no - 4].x / 700.0f));
                break;
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
                break;
        }
    }
}

/* 239 insns */
MGACTOR *fn_1_1194(s32 playerNo, HuVecF pos)
{
    MGACTOR *actor = NULL;
    s32 i;

    if (lbl_1_bss_18 != 0) {
        return NULL;
    }
    i = 5;
    while (i-- != 0) {
        if (playerNo == lbl_1_bss_2A0[i]) {
            Hu3DParManAttrSet(lbl_1_bss_28C[i], 1);
            lbl_1_bss_2A0[i] = -1;
            actor = lbl_1_bss_2D8[i];
            break;
        }
    }
    if (!actor) {
        return NULL;
    }
    Hu3DModelAttrReset(actor->mdlId, 1);
    MgActorColAttrReset(actor, 2);
    MgActorColAttrSet(actor, 0x1000004);
    actor->gravity = 100.0f;
    MgActorPosSet(actor, &pos);
    actor->velY = 100.0f + 100.0f * ((-1.0f + sqrtf(3201.0f)) / 2.0f);
    actor->forceA.x = frandmod(200) / 10.0f - 10.0f;
    actor->forceA.y = 0.0f;
    actor->forceA.z = frandmod(200) / 10.0f - 10.0f;
    fn_1_EEF8(lbl_1_bss_2FC[playerNo]->playerNo);
    HuAudFXPlayVolPan(0x939, M576_SEVOL(111.0f + 16.0f * (actor->pos.x / 700.0f)), 64.0f + 16.0f * (actor->pos.x / 700.0f));
    return actor;
}

/*
 * Retail fn_1_1550 has two bare `return;`s in an int function. On the GameCube r3
 * still holds `a` there (non-NULL), so colman sees a true result; the host must
 * say so explicitly instead of returning garbage.
 */
#define M576_RETURN_A return

/* 1887 insns: the players' narrow-phase hook (MGACTOR_PARAM narrowHook, fn_1_32CC 0x3BA0);
 * a is the player's body, b the body it touched (b->type 0..6) */
int fn_1_1550(COL_NARROW_PARAM *a, COL_NARROW_PARAM *b)
{
    switch (b->type) {
        case 0:
        case 1: {
            MGPLAYER *player = lbl_1_bss_2FC[a->paramA];
            HuVecF pos;
            MGACTOR *actor;
            if (MgPlayerVibAttrCheck(player, 1)) {
                MgActorPosGet(player->actor, &pos);
                actor = fn_1_1194(a->paramA, pos);
            }
            break;
        }
        case 2: {
            MGPLAYER *player = lbl_1_bss_2FC[a->paramA];
            HuVecF pos;
            MGACTOR *actor;
            if (a->paramA == (u8)b->paramB) {
                return 0;
            }
            if (!MgPlayerVibAttrCheck(player, 0x40)) {
                return 0;
            }
            MgActorPosGet(player->actor, &pos);
            actor = fn_1_1194(a->paramA, pos);
            break;
        }
        case 3: {
            MGPLAYER *player = lbl_1_bss_2FC[a->paramA];
            HuVecF pos;
            MGACTOR *actor;
            if (a->paramA == (u8)b->paramB) {
                return 0;
            }
            if (!MgPlayerVibAttrCheck(player, 0x80)) {
                return 0;
            }
            MgActorPosGet(player->actor, &pos);
            actor = fn_1_1194(a->paramA, pos);
            break;
        }
        case 4: {
            MGPLAYER *player = lbl_1_bss_2FC[a->paramA];
            HuVecF pos;
            MGACTOR *actor;
            if (a->paramA == (u8)b->paramB) {
                return 0;
            }
            if (!MgPlayerVibAttrCheck(player, 0x100)) {
                return 0;
            }
            MgActorPosGet(player->actor, &pos);
            actor = fn_1_1194(a->paramA, pos);
            actor = fn_1_1194(a->paramA, pos);
            break;
        }
        case 6: {
            MGPLAYER *player;
            HuVecF dir;
            HuVecF pos;
            float angle;
            MGACTOR *actor;
            if (a->paramA >= 4) {
                return 1;
            }
            player = lbl_1_bss_2FC[a->paramA];
            VECSubtract(&a->point, &b->point, &dir);
            fn_1_444(&dir, &dir);
            if (dir.z > 1.0f) {
                dir.z = 1.0f;
            } else if (dir.z < -1.0f) {
                dir.z = -1.0f;
            }
            angle = acosf(dir.z);
            if (dir.x < 0.0f) {
                angle = -angle;
            }
            angle = 180.0f * angle / M_PI;
            if (!MgPlayerStunSet(player, 1, angle, -1)) {
                return 1;
            }
            MgActorPosGet(player->actor, &pos);
            actor = fn_1_1194(a->paramA, pos);
            return 1;
        }
        case 5: {
            MGPLAYER *player = lbl_1_bss_2FC[a->paramA];
            MGACTOR *actor;
            HuVecF pos;
            s32 no;
            s32 i;
            if (lbl_1_bss_14 != 0) {
                M576_RETURN_A; /* retail: bare return, r3 still holds a */
            }
            no = b->paramB - 8;
            actor = lbl_1_bss_2D8[no];
            if (lbl_1_bss_2A0[no] != -1) {
                M576_RETURN_A; /* retail: bare return, r3 still holds a */
            }
            fn_1_EEC0(player->playerNo);
            lbl_1_bss_2A0[no] = a->paramB;
            fn_1_BAF4(b->paramB, -1);
            MgActorColAttrSet(actor, 6);
            Hu3DModelAttrSet(actor->mdlId, 1);
            MgActorPosGet(actor, &pos);
            pos.y += 115.0f;
            i = lbl_1_bss_8;
            while (i-- != 0) {
                if (a->paramB == lbl_1_bss_2EC[i]->unk000->actor->param) {
                    lbl_1_bss_2EC[i]->unk030 = 0;
                    break;
                }
            }
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[no + 15], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[no + 15], 1);
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[no + 15], 0x40000002);
            Hu3DModelPosSet(lbl_1_bss_0->mdlId[no + 15], pos.x, pos.y, pos.z);
            HuAudFXPlayVolPan(0x938, M576_SEVOL(111.0f + 16.0f * (pos.z / 700.0f)), 64.0f + 16.0f * (pos.x / 700.0f));
            omVibrate(player->playerNo, 12, 4, 2);
            return 1;
        }
    }
    return 0;
}

/* 909 insns: main object process (added by ObjectSetup); runs once, then clears objFunc */
void fn_1_32CC(OMOBJ *obj)
{
    MGACTOR_COLMAP_POLY poly;
    MGACTOR_PARAM param;
    COL_ATTRPARAM attrParam;
    HuVecF pos;
    s32 order[4];
    HU3DMODELID mdlList[3];
    s32 i;
    s32 j;
    s32 r;
    s32 mdlId;
    BOOL com;

    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x01), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[2] = mdlList[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x02), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[3] = mdlList[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x04), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[4] = mdlList[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x05), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[5] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x00), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[6] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[7] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[8] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[9] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x06), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[10] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x07), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[11] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x08), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[12] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x09), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[13] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0A), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[14] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0B), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[15] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0C), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[16] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0D), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[17] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0E), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[18] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x0F), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[19] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m576, 0x10), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelLayerSet(obj->mdlId[0], 0);
    Hu3DModelLayerSet(obj->mdlId[1], 0);
    Hu3DModelLayerSet(obj->mdlId[3], 0);
    Hu3DModelLayerSet(obj->mdlId[4], 0);
    Hu3DModelLayerSet(obj->mdlId[5], 0);
    for (i = 6; i <= 9; i++) {
        Hu3DModelLayerSet(obj->mdlId[i], 1);
    }
    for (i = 10; i <= 14; i++) {
        Hu3DModelLayerSet(obj->mdlId[i], 2);
    }
    for (i = 15; i <= 19; i++) {
        Hu3DModelLayerSet(obj->mdlId[i], 2);
    }
    MgActorColMapInit(mdlList, 3, 40);
    MgActorColAttrParamGet(&attrParam, 1);
    attrParam.yDeviate = 1.0f;
    MgActorColAttrParamSet(&attrParam, 1);
    MgActorColAttrParamGet(&attrParam, 2);
    attrParam.yDeviate = 1.0f;
    MgActorColAttrParamSet(&attrParam, 2);
    MgActorColAttrParamGet(&attrParam, 0x80);
    attrParam.yDeviate = 1.0f;
    MgActorColAttrParamSet(&attrParam, 0x80);
    MgActorColAttrParamGet(&attrParam, 0x100);
    attrParam.yDeviate = 1.0f;
    MgActorColAttrParamSet(&attrParam, 0x100);
    Hu3DModelShadowMapSet(obj->mdlId[0]);
    Hu3DModelShadowSet(obj->mdlId[3]);
    Hu3DModelShadowSet(obj->mdlId[4]);
    Hu3DModelAttrSet(obj->mdlId[2], 1);
    Hu3DModelAttrSet(obj->mdlId[0], 0x40000001);
    Hu3DModelAttrSet(obj->mdlId[5], 0x40000002);
    Hu3DModelPosSetV(obj->mdlId[3], &lbl_1_data_C4[0]);
    Hu3DModelPosSetV(obj->mdlId[4], &lbl_1_data_C4[1]);
    lbl_1_bss_40[4] = -1;
    Hu3DModelAttrSet(obj->mdlId[15], 1);
    Hu3DModelAttrSet(obj->mdlId[16], 1);
    Hu3DModelAttrSet(obj->mdlId[17], 1);
    Hu3DModelAttrSet(obj->mdlId[18], 1);
    Hu3DModelAttrSet(obj->mdlId[19], 1);
    Hu3DModelAttrSet(obj->mdlId[15], 0x40000002);
    Hu3DModelAttrSet(obj->mdlId[16], 0x40000002);
    Hu3DModelAttrSet(obj->mdlId[17], 0x40000002);
    Hu3DModelAttrSet(obj->mdlId[18], 0x40000002);
    Hu3DModelAttrSet(obj->mdlId[19], 0x40000002);
    i = 5;
    while (i-- != 0) {
        lbl_1_bss_2A0[i] = -1;
    }
    Hu3DModelCameraInfoSet(obj->mdlId[0], 1);
    i = 9;
    while (i-- != 0) {
        pos = ((HuVecF *)lbl_1_data_DC)[i];
        pos.y -= 50.0f;
        ((HuVecF *)lbl_1_data_DC)[i].y += 50.0f;
        if (MgActorColMapPolyGet(&((HuVecF *)lbl_1_data_DC)[i], &pos, -1, &poly)) {
            if ((u32)poly.mdlNo == 0 && (poly.code & 0x407F)) {
                lbl_1_bss_254[i] = poly.triNo;
                ((HuVecF *)lbl_1_data_DC)[i] = poly.pos;
            } else {
                OSReport(lbl_1_data_2AC, i, poly.mdlNo, poly.code);
            }
        } else {
            OSReport(lbl_1_data_2F7, i);
        }
    }
    lbl_1_bss_254[9] = -1;
    lbl_1_bss_254[10] = -1;
    lbl_1_bss_254[11] = -1;
    i = 4;
    while (i-- != 0) {
        pos = ((HuVecF *)lbl_1_data_184)[i];
        pos.y -= 50.0f;
        ((HuVecF *)lbl_1_data_184)[i].y += 50.0f;
        if (MgActorColMapPolyGet(&((HuVecF *)lbl_1_data_184)[i], &pos, -1, &poly)) {
            if ((u32)poly.mdlNo == 0 && (poly.code & 0x407F)) {
                lbl_1_bss_2B4[i] = poly.triNo;
                ((HuVecF *)lbl_1_data_184)[i] = poly.pos;
            } else {
                OSReport(lbl_1_data_326, i, poly.mdlNo, poly.code);
            }
        } else {
            OSReport(lbl_1_data_371, i);
        }
    }
    param.height = 150.0f;
    param.radius = 50.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = fn_1_1550;
    param.correctHook = fn_1_FA0;
    for (i = 0; i < 4; i++) {
        com = GwPlayerConf[i].type ? TRUE : FALSE;
        param.param = i;
        lbl_1_bss_2FC[i] = MgPlayerCreateJumpAlt(i, &param, 8, 1, -1, NULL, com);
        if (!com) {
            MgPlayerVibrateCreate(lbl_1_bss_2FC[i]);
        }
    }
    param.height = 100.0f;
    param.radius = 75.0f;
    param.param = 0;
    param.type = 6;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = NULL;
    param.correctHook = fn_1_FA0;
    i = 4;
    while (i-- != 0) {
        mdlId = obj->mdlId[i + 6];
        lbl_1_bss_40[i] = -1;
        param.param = i + 4;
        lbl_1_bss_2C8[i] = MgActorCreate(&param, mdlId);
        MgActorColAttrSet(lbl_1_bss_2C8[i], 0x24);
        Hu3DModelAttrSet(mdlId, 0x40000002);
        lbl_1_bss_2C8[i]->gravity = 0.0f;
        MgActorPosSet(lbl_1_bss_2C8[i], &lbl_1_data_58[i]);
    }
    i = 4;
    while (i-- != 0) {
        order[i] = i;
    }
    i = 4;
    while (i-- != 0) {
        if (i != 0) {
            r = frandmod(i + 1);
        } else {
            r = 0;
        }
        lbl_1_bss_2C4[i] = order[r];
        for (j = 0; j <= i; j++) {
            if (j != r && j > r) {
                order[j - 1] = order[j];
            }
        }
    }
    param.height = 150.0f;
    param.radius = 50.0f;
    param.param = 0;
    param.type = 5;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = NULL;
    param.correctHook = fn_1_FA0;
    i = 5;
    while (i-- != 0) {
        mdlId = obj->mdlId[i + 10];
        param.param = i + 8;
        lbl_1_bss_2D8[i] = MgActorCreate(&param, mdlId);
        Hu3DModelAttrSet(mdlId, 0x40000001);
        Hu3DModelLayerSet(mdlId, 2);
        lbl_1_bss_2D8[i]->gravity = 0.0f;
        pos = lbl_1_data_88[i];
        pos.y = 1300.0f;
        MgActorPosSet(lbl_1_bss_2D8[i], &pos);
    }
    for (i = 0; i < 4; i++) {
        lbl_1_bss_2FC[i]->actor->gravity = 0.0f;
        MgActorPosSet(lbl_1_bss_2FC[i]->actor, &lbl_1_data_28[i]);
        if (GwPlayerConf[i].type == 0) {
            MgPlayerAttrSet(lbl_1_bss_2FC[i], MGPLAYER_ATTR_COMSTK);
            MgPlayerPadSet(lbl_1_bss_2FC[i], 0, 0, 0, 0);
        }
    }
    fn_1_C16C(obj->mdlId[2]);
    for (i = 0; i < 4; i++) {
        if (GwPlayerConf[i].type != 0) {
            lbl_1_bss_2EC[lbl_1_bss_8] = fn_1_C1EC(lbl_1_bss_2FC[i]);
            lbl_1_bss_8++;
        }
    }
    fn_1_C24();
    obj->objFunc = NULL;
}

/* 170 insns: per-frame actor step; slot particle follows its owner while it moves */
void fn_1_4100(void)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF ofs;
    HuVecF rot;
    HuVecF diff;
    MGACTOR *actor;
    s32 playerNo;
    s32 i;

    for (i = 0; i <= 3; i++) {
        MgActorPosGet(lbl_1_bss_2FC[i]->actor, &lbl_1_bss_20C[i]);
    }
    MgActorExec();
    i = 5;
    while (i-- != 0) {
        if (lbl_1_bss_2A0[i] != -1) {
            playerNo = lbl_1_bss_2A0[i];
            actor = lbl_1_bss_2FC[playerNo]->actor;
            MgActorPosGet(actor, &pos);
            VECSubtract(&pos, &lbl_1_bss_20C[playerNo], &diff);
            if (VECSquareMag(&diff) < 1.0f) {
                Hu3DParManAttrSet(lbl_1_bss_28C[i], 1);
                continue;
            }
            Hu3DParManAttrReset(lbl_1_bss_28C[i], 1);
            ofs.x = 0.0f;
            ofs.y = 80.0f;
            ofs.z = -15.0f;
            rot.x = 45.0f;
            rot.y = -actor->rotY;
            rot.z = 0.0f;
            MTXRotRad(mtx, 'Y', 0.017453292f * actor->rotY);
            MTXMultVec(mtx, &ofs, &ofs);
            MTXMultVec(mtx, &rot, &rot);
            VECAdd(&pos, &ofs, &pos);
            Hu3DParManRotSet(lbl_1_bss_28C[i], rot.x, rot.y, rot.z);
            Hu3DParManPosSet(lbl_1_bss_28C[i], pos.x, pos.y, pos.z);
        } else if (lbl_1_bss_2D8[i]->velY <= 0.0f) {
            MgActorColAttrReset(lbl_1_bss_2D8[i], 4);
        }
    }
}

/* 40 insns: = decathlonDll DecaSortChar */
void fn_1_43A8(s8 *a, s8 *b, s8 num)
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

/* 278 insns: final ranking -> mgCoinBonus (10 to the leader(s)), winners */
void fn_1_4448(void)
{
    s8 winNo[4];
    s8 score[4];
    s32 i;
    s32 max;
    s32 winNum;
    s32 rank;
    s32 place;
    s32 prev;

    winNum = 0;
    max = 0;
    for (i = 0; i <= 3; i++) {
        lbl_1_bss_3C[i] = fn_1_854(i);
        if (max < lbl_1_bss_3C[i]) {
            max = lbl_1_bss_3C[i];
        }
    }
    winNum = 0;
    if (lbl_1_bss_3C[0] != lbl_1_bss_3C[1] || lbl_1_bss_3C[1] != lbl_1_bss_3C[2] || lbl_1_bss_3C[2] != lbl_1_bss_3C[3]) {
        for (i = 0; i < 4; i++) {
            score[i] = lbl_1_bss_3C[i];
            winNo[i] = i;
        }
        fn_1_43A8(score, winNo, 4);
        rank = 0;
        place = 0;
        prev = score[3];
        i = 4;
        while (i-- != 0) {
            if (prev != score[i]) {
                place += rank;
                rank = 1;
            } else {
                rank++;
            }
            if (place == 0) {
                GWMgCoinBonusSet(winNo[i], 10);
            } else {
                GWMgCoinBonusSet(winNo[i], 0);
            }
            prev = score[i];
        }
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_3C[i] == max) {
                lbl_1_bss_3C[i] = 1;
                winNo[winNum] = lbl_1_bss_2FC[i]->charNo;
                winNum++;
            } else {
                lbl_1_bss_3C[i] = 0;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            lbl_1_bss_3C[i] = 0;
        }
        GWMgCoinBonusSet(0, 0);
        GWMgCoinBonusSet(1, 0);
        GWMgCoinBonusSet(2, 0);
        GWMgCoinBonusSet(3, 0);
    }
    for (i = winNum; i < 4; i++) {
        winNo[i] = -1;
    }
    MgSeqWinnerSet(winNo[0], winNo[1], winNo[2], winNo[3]);
}

/* 32 insns: MGSEQ initHook */
void fn_1_48A0(s16 mode, s16 frameNo)
{
    s32 i;
    MgActorExec();
    for (i = 0; i < 4; i++) {
        MgPlayerPauseOn(lbl_1_bss_2FC[i]);
    }
    Hu3DCameraPosGet(HU3D_CAM0, &lbl_1_bss_58[0], &lbl_1_bss_58[1], &lbl_1_bss_58[2]);
    MgSeqModeNext();
}

/* 602 insns */
void fn_1_4920(s16 mode, s16 frameNo)
{
    HuVecF pos;
    HuVecF cam[3];
    s32 i;
    s32 range;
    s32 frame;

    MgActorExec();
    for (i = 0; i < 5; i++) {
        switch (i) {
            case 0:
                frame = 44;
                break;
            case 1:
                frame = 50;
                break;
            case 2:
                frame = 50;
                break;
            case 3:
                frame = 54;
                break;
            case 4:
                frame = 58;
                break;
        }
        if (frameNo == frame) {
            lbl_1_bss_2D8[i]->gravity = 100.0f;
            HuAudFXPlayVolPan(0x937, M576_SEVOL(111.0f + 16.0f * (lbl_1_bss_2D8[i]->pos.z / 700.0f)),
                64.0f + 16.0f * (lbl_1_bss_2D8[i]->pos.x / 700.0f));
        } else if (frameNo < frame) {
            lbl_1_bss_2D8[i]->velY = 100.0f;
        }
    }
    if (frameNo >= 30) {
        if (frameNo < 119) {
            range = (frameNo - 29) / 1.5;
            if (range == 0) {
                range = 1;
            }
            if (range >= 40) {
                range = 40;
            }
            if (lbl_1_bss_40[4] < 0) {
                lbl_1_bss_40[4] = HuAudFXPlay(0x3A1);
            }
            HuAudFXVolSet(lbl_1_bss_40[4], 63.0f + 64.0f * (range / 40.0f));
            if (frameNo % 10 == 0) {
                i = 4;
                while (i-- != 0) {
                    if (GwPlayerConf[i].type == GW_TYPE_MAN) {
                        if (range < 15) {
                            omVibrate(lbl_1_bss_2FC[i]->playerNo, 12, 6, 6);
                        } else if (range < 30) {
                            omVibrate(lbl_1_bss_2FC[i]->playerNo, 12, 4, 2);
                        } else {
                            omVibrate(lbl_1_bss_2FC[i]->playerNo, 12, 12, 0);
                        }
                    }
                }
            }
            cam[0] = lbl_1_bss_58[0];
            cam[1] = lbl_1_bss_58[1];
            cam[2] = lbl_1_bss_58[2];
            fn_1_2AC(&cam[0], range);
            fn_1_2AC(&cam[2], range);
            Hu3DCameraPosSetV(HU3D_CAM0, &cam[0], &cam[1], &cam[2]);
        } else if (frameNo == 119) {
            if (lbl_1_bss_40[4] >= 0) {
                HuAudFXStop(lbl_1_bss_40[4]);
                lbl_1_bss_40[4] = -1;
            }
            Hu3DCameraPosSetV(HU3D_CAM0, &lbl_1_bss_58[0], &lbl_1_bss_58[1], &lbl_1_bss_58[2]);
        } else if (frameNo == 120) {
            HuAudFXPlay(0x936);
            Hu3DMotionTimeSet(lbl_1_bss_0->mdlId[5], 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_0->mdlId[5], 0x40000002);
        } else if (frameNo == 210) {
            lbl_1_bss_1C = 1;
            for (i = 0; i < 4; i++) {
                Hu3DModelShadowSet(lbl_1_bss_2FC[i]->actor->mdlId);
                lbl_1_bss_2FC[i]->actor->gravity = 150.0f;
                MgActorColAttrSet(lbl_1_bss_2FC[i]->actor, 2);
                MgPlayerPauseOff(lbl_1_bss_2FC[i], &lbl_1_data_28[i]);
            }
        }
    }
    if (lbl_1_bss_1C == 1) {
        MgActorPosGet(lbl_1_bss_2FC[0]->actor, &pos);
        if (pos.y < 1000.0f) {
            lbl_1_bss_1C = 2;
            for (i = 0; i < 4; i++) {
                MgActorColAttrReset(lbl_1_bss_2FC[i]->actor, 2);
            }
        }
    }
    if (lbl_1_bss_20 == 0 && (lbl_1_bss_2FC[0]->actor->colGroundAttr & 0x407F) != 0) {
        lbl_1_bss_20 = 1;
        i = 4;
        while (i-- != 0) {
            if (GwPlayerConf[i].type == GW_TYPE_MAN) {
                omVibrate(lbl_1_bss_2FC[i]->playerNo, 12, 12, 0);
            }
        }
    }
}

/* 208 insns */
void fn_1_5288(s16 mode, s16 frameNo)
{
    HuVecF pos;
    s32 i;
    ANIMDATA *anim;

    if (lbl_1_bss_24 == 0) {
        MgActorPosGet(lbl_1_bss_2FC[0]->actor, &pos);
        if (pos.y < 1000.0f) {
            lbl_1_bss_24 = 1;
            for (i = 0; i < 4; i++) {
                MgActorColAttrReset(lbl_1_bss_2FC[i]->actor, 2);
            }
        }
    }
    if (lbl_1_bss_28[0] == 0 && (lbl_1_bss_2FC[0]->actor->colGroundAttr & 0x407F) != 0) {
        lbl_1_bss_28[0] = 1;
        i = 4;
        while (i-- != 0) {
            if (GwPlayerConf[i].type == GW_TYPE_MAN) {
                omVibrate(lbl_1_bss_2FC[i]->playerNo, 12, 12, 0);
            }
        }
    }
    if (frameNo == 1) {
        anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_effect, 1), HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_54 = HuAudBGMPlay(0x35);
        Hu3DParManInit();
        for (i = 0; i < 5; i++) {
            lbl_1_data_1B4.colorStart[0] = lbl_1_data_204[i][0];
            lbl_1_data_1B4.colorStart[1] = lbl_1_data_204[i][1];
            lbl_1_data_1B4.colorEnd[0] = lbl_1_data_204[i][2];
            lbl_1_data_1B4.colorEnd[1] = lbl_1_data_204[i][3];
            lbl_1_bss_7C[i] = lbl_1_data_1B4;
            lbl_1_bss_28C[i] = Hu3DParManCreate(anim, 100, &lbl_1_bss_7C[i]);
            Hu3DParManAttrSet(lbl_1_bss_28C[i], 0x65);
            Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(lbl_1_bss_28C[i]), 1);
        }
    }
    MgActorExec();
}

/* 399 insns */
void fn_1_55C8(s16 mode, s16 frameNo)
{
    s32 i;
    MGACTOR *actor;
    s32 no;

    switch (frameNo) {
        case 0:
            for (i = 0; i < 4; i++) {
                if (GwPlayerConf[i].type == GW_TYPE_MAN) {
                    MgPlayerAttrReset(lbl_1_bss_2FC[i], MGPLAYER_ATTR_COMSTK);
                }
            }
            for (i = 0; i <= 3; i++) {
                MgActorPosGet(lbl_1_bss_2FC[i]->actor, &lbl_1_bss_20C[i]);
            }
            fn_1_EA08(lbl_1_bss_4);
            break;
        case 480:
            no = 0;
            goto drop;
        case 960:
            no = 1;
            goto drop;
        case 1440:
            no = 2;
            goto drop;
        case 1920:
            no = 3;
        drop:
            actor = lbl_1_bss_2C8[lbl_1_bss_2C4[no]];
            OSReport(lbl_1_data_3A2, actor->param - 4);
            lbl_1_bss_40[actor->param - 4] = HuAudFXPlayVolPan(0x93A,
                M576_SEVOL(111.0f + 16.0f * (lbl_1_data_58[actor->param - 4].z / 700.0f)),
                64.0f + 16.0f * (lbl_1_data_58[actor->param - 4].x / 700.0f));
            actor->gravity = 160.0f;
            MgActorColAttrReset(actor, 4);
            break;
    }
    lbl_1_bss_C++;
    lbl_1_bss_10++;
    lbl_1_bss_23C[0] = lbl_1_data_C4[0];
    if (lbl_1_bss_C < 71.42857f) {
        lbl_1_bss_23C[0].y += 7.0f * lbl_1_bss_C;
    } else if (lbl_1_bss_C < 142.85715f) {
        lbl_1_bss_23C[0].y += 500.0f - 7.0f * (lbl_1_bss_C - 71.42857f);
    } else {
        lbl_1_bss_C = 0;
    }
    Hu3DModelPosSetV(lbl_1_bss_0->mdlId[3], &lbl_1_bss_23C[0]);
    lbl_1_bss_23C[1] = lbl_1_data_C4[1];
    if (lbl_1_bss_10 < 100.0f) {
        lbl_1_bss_23C[1].x += 3.0f * lbl_1_bss_10;
    } else if (lbl_1_bss_10 < 200.0f) {
        lbl_1_bss_23C[1].x += 300.0f - 3.0f * (lbl_1_bss_10 - 100.0f);
    } else {
        lbl_1_bss_10 = 0;
    }
    Hu3DModelPosSetV(lbl_1_bss_0->mdlId[4], &lbl_1_bss_23C[1]);
    for (i = 0; i < lbl_1_bss_8; i++) {
        fn_1_C31C(lbl_1_bss_2EC[i]);
    }
    fn_1_4100();
}

/* 97 insns */
void fn_1_5C04(s16 mode, s16 frameNo)
{
    COL_ATTRPARAM param;
    s32 i;

    lbl_1_bss_18 = 1;
    if (frameNo == 0) {
        lbl_1_bss_14 = 1;
        MgActorColAttrParamGet(&param, 1);
        param.yDeviate = 0.0f;
        MgActorColAttrParamSet(&param, 1);
        MgActorColAttrParamGet(&param, 2);
        param.yDeviate = 0.0f;
        MgActorColAttrParamSet(&param, 2);
        MgActorColAttrParamGet(&param, 0x80);
        param.yDeviate = 1.0f;
        MgActorColAttrParamSet(&param, 0x80);
        MgActorColAttrParamGet(&param, 0x100);
        param.yDeviate = 1.0f;
        MgActorColAttrParamSet(&param, 0x100);
        i = 4;
        while (i-- != 0) {
            if (GwPlayerConf[i].type == GW_TYPE_MAN) {
                MgPlayerAttrSet(lbl_1_bss_2FC[i], MGPLAYER_ATTR_COMSTK | MGPLAYER_ATTR_STUNOFF);
                lbl_1_bss_2FC[i]->squishTime = 0.0f;
            }
        }
        MgSeqModeDelaySet(MGSEQ_MODE_PREWIN, 180);
        HuAudSStreamStop(lbl_1_bss_54);
    }
    fn_1_4100();
}

/* 73 insns */
s32 fn_1_5D88(MGPLAYER *player, s32 seNo)
{
    if (lbl_1_bss_14 == 2) {
        return HuAudFXPlayVolPan((&lbl_1_data_254[player->charNo])[seNo], 127, 64.0f + 16.0f * (player->actor->pos.x / 300.0f));
    } else {
        return HuAudFXPlayVolPan((&lbl_1_data_254[player->charNo])[seNo], 127, 64.0f + 16.0f * (player->actor->pos.x / 700.0f));
    }
}

/* 545 insns */
void fn_1_5EAC(s16 mode, s16 frameNo)
{
    HuVecF target;
    HuVecF up;
    HuVecF pos;
    s32 i;
    s32 motId;
    s32 drawF;

    if (frameNo <= 60) {
        fn_1_4100();
    }
    switch (frameNo) {
        case 0:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
            break;
        case 60:
            fn_1_4448();
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_WHITEFADE, 60);
            i = 4;
            while (i-- != 0) {
                Hu3DModelAttrReset(lbl_1_bss_2FC[i]->actor->mdlId, HU3D_ATTR_DISPOFF);
                Hu3DModelScaleSet(lbl_1_bss_2FC[i]->actor->mdlId, 1.0f, 1.0f, 1.0f);
                Hu3DModelRotSet(lbl_1_bss_2FC[i]->actor->mdlId, 0.0f, 0.0f, 0.0f);
                Hu3DModelPosSetV(lbl_1_bss_2FC[i]->actor->mdlId, &lbl_1_data_27C[i]);
                if (lbl_1_bss_2FC[i]->motNo != 0) {
                    CharMotionShiftSet(lbl_1_bss_2FC[i]->charNo, lbl_1_bss_2FC[i]->omObj->mtnId[0], 0.0f, 5.0f, 0x40000001);
                    lbl_1_bss_2FC[i]->motNo = 0;
                }
                lbl_1_bss_2FC[i]->actor->pos = lbl_1_data_27C[i];
            }
            i = 5;
            while (i-- != 0) {
                Hu3DModelAttrSet(lbl_1_bss_2D8[i]->mdlId, HU3D_ATTR_DISPOFF);
            }
            i = 4;
            while (i-- != 0) {
                Hu3DModelAttrSet(lbl_1_bss_2C8[i]->mdlId, HU3D_ATTR_DISPOFF);
            }
            i = 5;
            while (i-- != 0) {
                Hu3DParManAttrSet(lbl_1_bss_28C[i], 1);
            }
            Hu3DCameraPosGet(HU3D_CAM0, &pos, &up, &target);
            target.x = 0.0f;
            target.y = 200.0f;
            target.z = 0.0f;
            pos.x = 0.0f;
            pos.y = 450.0f;
            pos.z = 1400.0f;
            Hu3DCameraPerspectiveSet(HU3D_CAM0, 40.0f, 20.0f, 10000.0f, 1.2f);
            Hu3DCameraPosSetV(HU3D_CAM0, &pos, &up, &target);
            fn_1_4448();
            lbl_1_bss_14 = 2;
            break;
        case 120:
            drawF = TRUE;
            OSReport(lbl_1_data_3A6);
            i = 4;
            while (i-- != 0) {
                if (lbl_1_bss_3C[i] != 0) {
                    motId = CharMotionCreate(lbl_1_bss_2FC[i]->charNo, CHARMOT_HSF_c000m1_359);
                    drawF = FALSE;
                } else {
                    motId = CharMotionCreate(lbl_1_bss_2FC[i]->charNo, CHARMOT_HSF_c000m1_360);
                }
                CharMotionShiftSet(lbl_1_bss_2FC[i]->charNo, motId, 0.0f, 5.0f, 0);
            }
            if (drawF) {
                fn_1_5D88(lbl_1_bss_2FC[0], 0);
                fn_1_5D88(lbl_1_bss_2FC[1], 0);
                fn_1_5D88(lbl_1_bss_2FC[2], 0);
                fn_1_5D88(lbl_1_bss_2FC[3], 0);
            }
            MgSeqModeNext();
            break;
    }
}

/* 1 insns */
void fn_1_6730(s16 mode, s16 frameNo) { }

/* 12 insns */
void fn_1_6734(s16 mode, s16 frameNo)
{
    if (frameNo >= 60) {
        MgSeqModeNext();
    }
}

/* 8 insns */
void fn_1_6764(s16 mode, s16 frameNo)
{
    MgSeqModeNext();
}

