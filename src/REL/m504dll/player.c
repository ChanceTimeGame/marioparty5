/*
 * m504dll player.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/player.s.
 */

#include "REL/m504dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* The swing/turn code inlines MSL's sqrtf algorithm, but the reference pools 0.5 and 3.0
 * as ordinary literals after the floats (0x120, 0x128): not math.h's copy, whose
 * `static const double _half/_three` would be extra .rodata (m565 player.c precedent).
 * The host uses the real sqrtf. */
static inline float PlayerSqrtF(float x)
{
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte((double)x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

/* (-180, 180] */
#define M504_ANGLE_WRAP(a) ((a) > 180.0f ? (a) - 360.0f : ((a) <= -180.0f ? 360.0f + (a) : (a)))
#define M504_ABS(a) (((a) >= 0.0f) ? (a) : -(a))

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0xE8 */ /* s32 lbl_1_rodata_E8[3] = { 0x435C0000, 0x00000000, 0x437A0000 }; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 0.0f; */
/* 0xF8 */ /* float lbl_1_rodata_F8 = 4.0f; */
/* 0xFC */ /* float lbl_1_rodata_FC = -120.0f; */
/* 0x100 */ /* float lbl_1_rodata_100 = 2.0f; */
/* 0x104 */ /* float lbl_1_rodata_104 = 1.0f; */
/* 0x108 */ /* float lbl_1_rodata_108 = 3.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 180.0f; */
/* 0x110 */ /* float lbl_1_rodata_110 = 360.0f; */
/* 0x114 */ /* float lbl_1_rodata_114 = -180.0f; */
/* 0x118 */ /* float lbl_1_rodata_118 = 0.9f; */
/* 0x120 */ /* double lbl_1_rodata_120 = 0.5; */
/* 0x128 */ /* double lbl_1_rodata_128 = 3; */
/* 0x130 */ /* float lbl_1_rodata_130 = 14.0f; */
/* 0x134 */ /* float lbl_1_rodata_134 = 56.0f; */
/* 0x138 */ /* float lbl_1_rodata_138 = 0.001f; */
/* 0x13C */ /* float lbl_1_rodata_13C = 6.0f; */
/* 0x140 */ /* double lbl_1_rodata_140 = 180; */
/* 0x148 */ /* double lbl_1_rodata_148 = 3.141592653589793; */
/* 0x150 */ /* float lbl_1_rodata_150 = 4.2000003f; */
/* 0x154 */ /* float lbl_1_rodata_154 = 0.5f; */
/* 0x158 */ /* float lbl_1_rodata_158 = 0.2f; */
/* 0x15C */ /* float lbl_1_rodata_15C = 50.0f; */
/* 0x160 */ /* double lbl_1_rodata_160 = 4503601774854144; */
/* 0x168 */ /* double lbl_1_rodata_168 = 360; */
/* 0x170 */ /* float lbl_1_rodata_170 = 200.0f; */
/* 0x174 */ /* float lbl_1_rodata_174 = 10.0f; */
/* 0x178 */ /* float lbl_1_rodata_178 = 90.0f; */
/* 0x17C */ /* float lbl_1_rodata_17C = 60.0f; */
/* 0x180 */ /* float lbl_1_rodata_180 = 1000.0f; */
/* 0x184 */ /* float lbl_1_rodata_184 = 60.000004f; */
/* 0x188 */ /* float lbl_1_rodata_188 = 75.0f; */
/* 0x18C */ /* float lbl_1_rodata_18C = -2.4333334f; */
/* 0x190 */ /* float lbl_1_rodata_190 = 15.0f; */
/* 0x198 */ /* double lbl_1_rodata_198 = 4503599627370496; */
/* 0x1A0 */ /* s32 lbl_1_rodata_1A0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1AC */ /* float lbl_1_rodata_1AC = 40.0f; */
/* 0x1B0 */ /* float lbl_1_rodata_1B0 = 600.0f; */
/* 0x1B4 */ /* float lbl_1_rodata_1B4 = 300.0f; */
/* 0x1B8 */ /* float lbl_1_rodata_1B8 = 1200.0f; */
/* 0x1BC */ /* float lbl_1_rodata_1BC = 1800.0f; */
/* 0x1C0 */ /* float lbl_1_rodata_1C0 = -200.0f; */
/* 0x1C4 */ /* float lbl_1_rodata_1C4 = 0.1f; */
/* 0x1C8 */ /* float lbl_1_rodata_1C8[2] = { 500.0f, 0.0f }; */
/* 0x1D0 */ /* s32 lbl_1_rodata_1D0[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1DC */ /* s32 lbl_1_rodata_1DC[3] = { 0x00000000, 0x00000000, 0x00000000 }; */

/* --- .data --- */
/* 0xA8 */ M504_STAGEOBJDATA lbl_1_data_A8[10] = {
    { 17, 0, { -425.0f, 0.0f, 1701.0f }, { -3.5e+02f, 0.0f, 2075.0f }, 0 },
    { -1, 1, { 3.2e+02f, 0.0f, 2.35e+03f }, { 6e+01f, 0.0f, 0.0f }, 0 },
    { 15, 0, { 25.0f, 0.0f, 4e+02f }, { 2.5e+02f, 0.0f, 6e+02f }, 0 },
    { 16, 0, { -3e+02f, 0.0f, 1.05e+03f }, { 25.0f, 0.0f, 1.45e+03f }, 0 },
    { -1, 0, { 0.0f, 0.0f, 1.75e+03f }, { 2.5e+02f, 0.0f, 2.15e+03f }, 0 },
    { 18, 1, { -5e+01f, 0.0f, 2.8e+03f }, { 194.0f, 0.0f, 0.0f }, 0 },
    { -1, 0, { -4e+02f, 0.0f, 1.05e+03f }, { -2e+02f, 0.0f, 1.45e+03f }, 1 },
    { -1, 0, { 2.5e+02f, 0.0f, 4e+02f }, { 4e+02f, 0.0f, 6e+02f }, 1 },
    { -1, 0, { 2.5e+02f, 0.0f, 1.75e+03f }, { 4e+02f, 0.0f, 2.15e+03f }, 1 },
    { -1, 0, { -4e+02f, 0.0f, 2719.0f }, { -244.0f, 0.0f, 2.88e+03f }, 1 }
};
/* 0x1E8 */ s16 lbl_1_data_1E8[14] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0, 0 }; /* unreferenced; dtk folds it into lbl_1_data_A8 */
/* 0x204 */ s32 lbl_1_data_204[13][12] = {
    { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C002B, 0x008C0017, 0x008C0018, 0x008C001A, 0x0087005F, 0x0087005C, 0x008C002F, 0x008C0031, 0x008C002C },
    { 0x00330000, 0x00330001, 0x00330002, 0x0033002B, 0x00330017, 0x00330018, 0x0033001A, 0x002E005F, 0x002E005C, 0x0033002F, 0x00330031, 0x0033002C },
    { 0x00B70000, 0x00B70001, 0x00B70002, 0x00B7002B, 0x00B70017, 0x00B70018, 0x00B7001A, 0x00B2005F, 0x00B2005C, 0x00B7002F, 0x00B70031, 0x00B7002C },
    { 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED002B, 0x00ED0017, 0x00ED0018, 0x00ED001A, 0x00E8005F, 0x00E8005C, 0x00ED002F, 0x00ED0031, 0x00ED002C },
    { 0x00E60000, 0x00E60001, 0x00E60002, 0x00E6002B, 0x00E60017, 0x00E60018, 0x00E6001A, 0x00E1005F, 0x00E1005C, 0x00E6002F, 0x00E60031, 0x00E6002C },
    { 0x00170000, 0x00170001, 0x00170002, 0x0017002B, 0x00170017, 0x00170018, 0x0017001A, 0x0012005F, 0x0012005C, 0x0017002F, 0x00170031, 0x0017002C },
    { 0x00E00000, 0x00E00001, 0x00E00002, 0x00E0002B, 0x00E00017, 0x00E00018, 0x00E0001A, 0x00DB005F, 0x00DB005C, 0x00E0002F, 0x00E00031, 0x00E0002C },
    { 0x002D0000, 0x002D0001, 0x002D0002, 0x002D002B, 0x002D0017, 0x002D0018, 0x002D001A, 0x0028005F, 0x0028005C, 0x002D002F, 0x002D0031, 0x002D002C },
    { 0x00C90000, 0x00C90001, 0x00C90002, 0x00C9002B, 0x00C90017, 0x00C90018, 0x00C9001A, 0x00C4005F, 0x00C4005C, 0x00C9002F, 0x00C90031, 0x00C9002C },
    { 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0002B, 0x00B00017, 0x00B00018, 0x00B0001A, 0x009C005F, 0x009C005C, 0x00B0002F, 0x00B00031, 0x00B0002C },
    { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C002B, 0x008C0017, 0x008C0018, 0x008C001A, 0x0087005F, 0x0087005C, 0x008C002F, 0x008C0031, 0x008C002C },
    { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C002B, 0x008C0017, 0x008C0018, 0x008C001A, 0x0087005F, 0x0087005C, 0x008C002F, 0x008C0031, 0x008C002C },
    { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C002B, 0x008C0017, 0x008C0018, 0x008C001A, 0x0087005F, 0x0087005C, 0x008C002F, 0x008C0031, 0x008C002C }
}; /* per-character data nums */
/* 0x474 */ HuVecF lbl_1_data_474 = { 800.0f, 4000.0f, 1500.0f }; /* shadow light position; z follows the player (fn_1_9334) */
/* 0x480 */ HuVecF lbl_1_data_480 = { 0.0f, 1.0f, 0.0f };
/* 0x48C */ HuVecF lbl_1_data_48C = { 0.0f, 0.0f, 0.0f }; /* shadow target; z follows the player */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7810 */ M504_NODE1 lbl_1_bss_7810; /* 0x10: the dynamic COM node (lbl_1_data_4134[0]) */


/* --- functions (reference order) --- */
/* 314 insns */
void fn_1_5934(M504_PLAYER *player, s32 playerNo, M504_LANE *lane)
{
    M504_WORK *work;
    OMOBJ *obj;
    u16 i;
    HU3DMODELID mdlId;
    char *hook;

    work = lane->unk000;
    obj = NULL;
    memset(player, 0, sizeof(M504_PLAYER));
    player->unk000 = lane;
    player->unk00C = playerNo;
    player->unk014 = GwPlayerConf[player->unk00C].grp;
    player->unk010 = GwPlayerConf[player->unk00C].charNo;
    obj = omAddObjEx(work->unk000, 100, 1, 12, -1, NULL);
    player->unk018 = obj;
    player->unk0C4 = 0;
    obj->mdlId[0] = CharModelCreate(player->unk010, 8);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharModelStepFxSet(player->unk010, 0);
    CharEffectLayerSet(4);
    for (i = 0; i < 12; i++) {
        obj->mtnId[i] = CharMotionCreate(player->unk010, lbl_1_data_204[player->unk010][i]);
        CharMotionSet(player->unk010, obj->mtnId[i]);
    }
    Hu3DMotionShiftSet(player->unk018->mdlId[0], player->unk018->mtnId[0], 0.0f, 4.0f, 0);
    player->unk08A = player->unk088 = 0;
    player->unk01C = 1;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelCameraSet(obj->mdlId[0], lbl_1_data_45E0[playerNo]);
    {
        HuVecF pos = { 220.0f, 0.0f, 250.0f };
        HuVecF *posP = &pos;
        player->unk060 = *posP;
    }
    omSetTra(obj, player->unk060.x, player->unk060.y, player->unk060.z);
    omSetRot(obj, 0.0f, -120.0f, 0.0f);
    player->unk080 = player->unk084 = -120.0f;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x3E001E, HU_MEMNUM_OVL, HEAP_MODEL));
    player->unk0C8 = mdlId;
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelScaleSet(mdlId, 2.0f, 2.0f, 2.0f);
    Hu3DModelCameraSet(mdlId, lbl_1_data_45E0[playerNo]);
    Hu3DModelLayerSet(mdlId, 5);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    player->unk0CA = Hu3DJointMotion(mdlId, HuDataSelHeapReadNum(0x3E0039, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdlId, player->unk0CA);
    Hu3DMotionSpeedSet(mdlId, 1.0f);
    Hu3DModelAttrSet(mdlId, 0);
    Hu3DModelAttrReset(mdlId, HU3D_ATTR_ZCMP_OFF);
    mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(0x3E001D, HU_MEMNUM_OVL, HEAP_MODEL));
    player->unk0CC = mdlId;
    Hu3DModelPosSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdlId, 0.0f, 0.0f, 0.0f);
    Hu3DModelCameraSet(mdlId, lbl_1_data_45E0[playerNo]);
    Hu3DModelLayerSet(mdlId, 5);
    Hu3DModelAttrSet(mdlId, HU3D_ATTR_DISPOFF);
    hook = CharModelItemHookGet(player->unk010, 8, 0);
    Hu3DModelHookSet(obj->mdlId[0], hook, mdlId);
    fn_1_B828(&player->unk020, playerNo, player);
}

/* 43 insns */
void fn_1_5E1C(M504_PLAYER *player)
{
    M504_LANE *lane;
    M504_WORK *work;

    lane = player->unk000;
    work = lane->unk000;
    fn_1_B898(&player->unk020);
    Hu3DModelHookReset(player->unk018->mdlId[0]);
    Hu3DModelKill(player->unk0CC);
    Hu3DMotionKill(player->unk0CA);
    Hu3DModelKill(player->unk0C8);
    if (player->unk018) {
        CharModelKill(player->unk010);
        omDelObjEx(work->unk000, player->unk018);
        player->unk018 = NULL;
    }
    memset(player, 0, sizeof(M504_PLAYER));
}

/* 36 insns */
s32 fn_1_5EC8(M504_PLAYER *player)
{
    M504_WORK *work;

    work = player->unk000->unk000;
    if (player->unk0C4 != 0) {
        fn_1_B8D8(&player->unk020);
    }
    else {
        player->unk020.unk02C = player->unk020.unk030 = player->unk020.unk034 = player->unk020.unk035 = 0;
    }
    player->unk004 = 0;
    if (work->unk1218 == 0) {
        fn_1_5F58(player);
        fn_1_9334(player);
    }
    return 0;
}

/* 121 insns */
s32 fn_1_5F58(M504_PLAYER *player)
{
    M504_LANE *lane;
    M504_WORK *work;
    OMOBJ *obj;
    HU3DMODELID mdlId;

    lane = player->unk000;
    work = lane->unk000;
    obj = player->unk018;
    switch (player->unk006) {
        case 0:
            fn_1_613C(player);
            break;
        case 1:
            fn_1_6AA0(player);
            break;
        case 2:
            fn_1_7710(player);
            break;
        case 3:
            fn_1_8A40(player);
            break;
        case 4:
            fn_1_85AC(player);
            break;
    }
    /* pans are constants 48/80/64: always in range */
    if (work->unk1218 == 0) {
        CharModelVoicePanSet(player->unk010, (lane->unk46C) ? 48 : 80);
    }
    else {
        CharModelVoicePanSet(player->unk010, 64);
    }
    mdlId = obj->mdlId[0];
    if (player->unk088 != player->unk08A && Hu3DMotionShiftIDGet(mdlId) < 0) {
        player->unk088 = player->unk08A;
        Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
        Hu3DMotionShiftSet(mdlId, obj->mtnId[player->unk088], 0.0f, 4.0f, (player->unk01C) ? HU3D_MOTATTR_LOOP : 0);
        if (player->unk088 != 7 && player->unk088 != 8) {
            Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        }
    }
    omSetTra(player->unk018, player->unk060.x, player->unk060.y, player->unk060.z);
    omSetRot(player->unk018, 0.0f, player->unk080, 0.0f);
    return 0;
}

/* 491 insns */
void fn_1_613C(M504_PLAYER *player)
{
    M504_WORK *work;
    M504_LANE *lane;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    M504_INPUT *input;
    float sum;
    HuVecF dir;
    HuVecF push;
    s16 hitA;
    s16 hitB;

    work = player->unk000->unk000;
    lane = player->unk000;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    input = &player->unk020;
    if (lbl_1_bss_0->unk122C != 0 && player->unk0D0 != 0 && wanwan->unk004 == 6 && wanwan->unk07C == 0) {
        player->unk078 = 0.0f;
        if (M504_ABS(player->unk080) > 3.0f) {
            player->unk080 = fn_1_68E8(0.0f, M504_ANGLE_WRAP(player->unk080), 0.9f);
            player->unk080 = M504_ANGLE_WRAP(player->unk080);
            player->unk08A = 1;
            player->unk01C = 1;
        }
        else {
            player->unk080 = 0.0f;
            player->unk08A = 0;
            player->unk01C = 1;
        }
        return;
    }
    sum = (float)input->unk034 * (float)input->unk034 + (float)input->unk035 * (float)input->unk035;
    player->unk078 = 14.0f * (PlayerSqrtF(sum) / 56.0f);
    if (player->unk078 >= 0.001f) {
        if (player->unk078 > 6.0f) {
            player->unk08A = 2;
            player->unk01C = 1;
        }
        else {
            player->unk08A = 1;
            player->unk01C = 1;
        }
        player->unk084 = 180.0 * (atan2(input->unk034, -input->unk035) / M_PI);
    }
    else {
        player->unk078 = 0.0f;
        player->unk08A = 0;
        player->unk01C = 1;
    }
    if (player->unk078 < 4.2000003f && player->unk0C4 != 0) {
        if (++player->unk090 > 15) {
            player->unk006 = 1;
            player->unk00A = 0;
            player->unk008 = 0;
        }
    }
    else {
        player->unk00A = 0;
        player->unk090 = 0;
        player->unk094 = 0;
    }
    player->unk07C = fn_1_68E8(player->unk084, player->unk07C, 0.5f);
    player->unk080 = fn_1_68E8(player->unk084, player->unk080, 0.2f);
    dir.x = player->unk078 * sin(M_PI * player->unk07C / 180.0);
    dir.z = player->unk078 * cos(M_PI * player->unk07C / 180.0);
    player->unk060.x += dir.x;
    player->unk060.z += dir.z;
    if (fn_1_B43C(wanwan, &player->unk060, 50.0f, &push, 0)) {
        player->unk006 = 3;
        player->unk008 = 0;
        player->unk060.x += push.x;
        player->unk060.z += push.z;
        omVibrate(lane->unk004, 30, 12, 0);
        fn_1_6A04(player, &push);
        Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        if (player->unk0C4 != 0) {
            if (lane->unk46C) {
                fn_1_5EC(0x64B);
            }
            else {
                fn_1_5EC(0x64C);
            }
        }
        return;
    }
    if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
        player->unk060.x += push.x;
        player->unk060.z += push.z;
    }
    if (input->unk030 & 0x100) {
        player->unk006 = 2;
        player->unk008 = 0;
    }
    if (player->unk08C) {
        player->unk006 = 4;
        player->unk00A = 0;
        player->unk008 = 0;
    }
}

/* 71 insns: the angle lerp (m510 fn_1_2840 / m565 fn_1_8F4) */
float fn_1_68E8(float cur, float target, float rate)
{
    float d;
    float r;

    d = fmod(target - cur, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    r = fmodf(cur + rate * r, 360.0f);
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* 39 insns: show the chomp's hit effect over the player (push unused) */
void fn_1_6A04(M504_PLAYER *player, HuVecF *push)
{
    M504_LANE *lane;
    M504_CAMERA *camera;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;

    lane = player->unk000;
    camera = &lane->unk3BC;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    Hu3DModelPosSet(wanwan->unk030, player->unk060.x, 200.0f + player->unk060.y, player->unk060.z);
    Hu3DMotionTimeSet(wanwan->unk030, 0.0f);
    Hu3DModelAttrReset(wanwan->unk030, HU3D_ATTR_DISPOFF);
    wanwan->unk034 = 1;
}

/* 796 insns: mode 1 -- stick released: turn to face the chomp, A arms the swing */
void fn_1_6AA0(M504_PLAYER *player)
{
    M504_WORK *work;
    M504_LANE *lane;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    M504_INPUT *input;
    float sum;
    float diff;
    float angle;
    float dot;
    HuVecF push;
    HuVecF dir;
    HuVecF toWan;
    s16 hitA;
    s16 hitB;

    work = player->unk000->unk000;
    lane = player->unk000;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    input = &player->unk020;
    sum = (float)input->unk034 * (float)input->unk034 + (float)input->unk035 * (float)input->unk035;
    player->unk078 = 14.0f * (PlayerSqrtF(sum) / 56.0f);
    if (player->unk078 > 4.2000003f) {
        player->unk006 = 0;
        player->unk00A = 0;
        player->unk008 = 0;
        return;
    }
    dir.x = sin(M_PI * player->unk07C / 180.0);
    dir.y = 0.0f;
    dir.z = cos(M_PI * player->unk07C / 180.0);
    PSVECSubtract(&wanwan->unk038, &player->unk060, &toWan);
    toWan.y = 0.0f;
    PSVECNormalize(&toWan, &toWan);
    dot = PSVECDotProduct(&dir, &toWan);
    diff = 180.0 * (acosf(dot) / M_PI);
    angle = 180.0 * (atan2(toWan.x, toWan.z) / M_PI);
    angle = M504_ANGLE_WRAP(angle);
    switch (player->unk008) {
        case 0:
            player->unk098 = 0;
            player->unk094 = 0;
            player->unk008++;
            break;
        case 1:
            if (M504_ABS(diff) > 10.0f) {
                player->unk08A = 1;
                player->unk01C = 1;
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            else {
                player->unk084 = angle;
                player->unk008++;
            }
            break;
        case 2:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            player->unk08A = 7;
            player->unk01C = 0;
            player->unk00A = 0;
            player->unk008++;
            break;
        case 3:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            if (player->unk00A == 4) {
                Hu3DModelAttrReset(player->unk0CC, HU3D_ATTR_DISPOFF);
            }
            if (player->unk00A >= 24) {
                player->unk094 = 1;
            }
            player->unk00A++;
            break;
    }
    player->unk07C = fn_1_68E8(player->unk084, player->unk07C, 0.5f);
    player->unk080 = fn_1_68E8(player->unk084, player->unk080, 0.2f);
    if (fn_1_B43C(wanwan, &player->unk060, 50.0f, &push, 0)) {
        player->unk006 = 3;
        player->unk008 = 0;
        player->unk060.x += push.x;
        player->unk060.z += push.z;
        omVibrate(lane->unk004, 30, 12, 0);
        fn_1_6A04(player, &push);
        Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        if (player->unk0C4 != 0) {
            if (lane->unk46C) {
                fn_1_5EC(0x64B);
            }
            else {
                fn_1_5EC(0x64C);
            }
        }
        return;
    }
    if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
        player->unk060.x += push.x;
        player->unk060.z += push.z;
    }
    if (input->unk030 & 0x100) {
        player->unk098 = 1;
    }
    if (player->unk098 && player->unk094) {
        player->unk098 = 0;
        player->unk006 = 2;
        player->unk008 = 0;
    }
    if (player->unk08C) {
        player->unk006 = 4;
        player->unk00A = 0;
        player->unk008 = 0;
    }
    if (player->unk0C4 == 0) {
        player->unk006 = 0;
        player->unk00A = 0;
        player->unk008 = 0;
        player->unk090 = 0;
    }
}

/* 935 insns: mode 2 -- the swing */
void fn_1_7710(M504_PLAYER *player)
{
    M504_WORK *work;
    M504_LANE *lane;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    M504_INPUT *input;
    OMOBJ *obj;
    HU3DMODELID mdlId;
    float diff;
    float angle;
    float dot;
    float time;
    float maxTime;
    HuVecF push;
    HuVecF dir;
    HuVecF toWan;
    s16 hitA;
    s16 hitB;

    work = player->unk000->unk000;
    lane = player->unk000;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    input = &player->unk020;
    obj = player->unk018;
    mdlId = player->unk018->mdlId[0];
    dir.x = sin(M_PI * player->unk07C / 180.0);
    dir.y = 0.0f;
    dir.z = cos(M_PI * player->unk07C / 180.0);
    PSVECSubtract(&wanwan->unk038, &player->unk060, &toWan);
    toWan.y = 0.0f;
    PSVECNormalize(&toWan, &toWan);
    dot = PSVECDotProduct(&dir, &toWan);
    diff = 180.0 * (acosf(dot) / M_PI);
    angle = 180.0 * (atan2(toWan.x, toWan.z) / M_PI);
    angle = M504_ANGLE_WRAP(angle);
    switch (player->unk008) {
        case 0:
            if (player->unk094) {
                player->unk008 = 3;
                player->unk088 = 7;
                player->unk08A = 8;
                player->unk01C = 0;
                player->unk00A = 0;
                Hu3DModelAttrReset(player->unk0CC, HU3D_ATTR_DISPOFF);
            }
            else if (M504_ABS(diff) > 10.0f) {
                player->unk08A = 1;
                player->unk01C = 1;
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            else {
                player->unk084 = angle;
                player->unk008++;
            }
            break;
        case 1:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            player->unk08A = 7;
            player->unk01C = 0;
            player->unk00A = 0;
            player->unk008++;
            break;
        case 2:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            if (player->unk00A++ >= 24) {
                player->unk08A = 8;
                player->unk01C = 0;
                player->unk00A = 0;
                player->unk008++;
            }
            if (player->unk00A == 4) {
                Hu3DModelAttrReset(player->unk0CC, HU3D_ATTR_DISPOFF);
            }
            break;
        case 3:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
            }
            if (player->unk00A++ >= 30) {
                omVibrate(lane->unk004, 15, 6, 6);
                Hu3DModelPosSet(player->unk0C8, player->unk060.x, 90.0f, player->unk060.z);
                Hu3DModelRotSet(player->unk0C8, 0.0f, player->unk084 - 180.0f, 0.0f);
                Hu3DMotionTimeSet(player->unk0C8, 0.0f);
                Hu3DMotionSpeedSet(player->unk0C8, 2.0f);
                Hu3DModelAttrReset(player->unk0C8, HU3D_ATTR_DISPOFF);
                player->unk008++;
                if (player->unk0C4 != 0) {
                    if (lane->unk46C) {
                        fn_1_5EC(0x65C);
                    }
                    else {
                        fn_1_5EC(0x65D);
                    }
                }
            }
            break;
        case 4:
            if (M504_ABS(diff) > 10.0f) {
                player->unk084 = fn_1_68E8(angle, player->unk084, 0.5f);
                Hu3DModelRotSet(player->unk0C8, 0.0f, player->unk084 - 180.0f, 0.0f);
            }
            time = Hu3DMotionTimeGet(player->unk0C8);
            maxTime = Hu3DMotionMaxTimeGet(player->unk0C8);
            if (time >= 0.5f * maxTime && (wanwan->unk004 == 5 || wanwan->unk004 == 6)) {
                fn_1_B1AC(wanwan);
            }
            if (player->unk00A++ >= 60) {
                Hu3DModelAttrSet(player->unk0C8, HU3D_ATTR_DISPOFF);
                player->unk00A = 30;
                player->unk006 = 1;
                player->unk008 = 3;
            }
            break;
    }
    player->unk07C = fn_1_68E8(player->unk084, player->unk07C, 0.5f);
    player->unk080 = fn_1_68E8(player->unk084, player->unk080, 0.2f);
    if (fn_1_B43C(wanwan, &player->unk060, 50.0f, &push, 0)) {
        Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        player->unk006 = 3;
        player->unk008 = 0;
        player->unk060.x += push.x;
        player->unk060.z += push.z;
        omVibrate(lane->unk004, 40, 12, 0);
        fn_1_6A04(player, &push);
        if (player->unk0C4 != 0) {
            if (lane->unk46C) {
                fn_1_5EC(0x64B);
            }
            else {
                fn_1_5EC(0x64C);
            }
        }
        return;
    }
    if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
        player->unk060.x += push.x;
        player->unk060.z += push.z;
    }
    if (player->unk0C4 == 0) {
        player->unk006 = 0;
        player->unk00A = 0;
        player->unk008 = 0;
        player->unk090 = 0;
    }
}

/* 293 insns: mode 4 */
void fn_1_85AC(M504_PLAYER *player)
{
    M504_WORK *work;
    M504_LANE *lane;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    M504_INPUT *input;
    OMOBJ *obj;
    HU3DMODELID mdlId;
    HuVecF push;
    s16 hitA;
    s16 hitB;

    work = player->unk000->unk000;
    lane = player->unk000;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    input = &player->unk020;
    obj = player->unk018;
    mdlId = player->unk018->mdlId[0];
    switch (player->unk008) {
        case 0:
            Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
            player->unk08A = 10;
            player->unk01C = 0;
            player->unk00A = 0;
            player->unk008++;
            break;
        case 1:
            break;
    }
    player->unk07C = fn_1_68E8(player->unk084, player->unk07C, 0.5f);
    player->unk080 = fn_1_68E8(player->unk084, player->unk080, 0.2f);
    if (fn_1_B43C(wanwan, &player->unk060, 50.0f, &push, 0)) {
        Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
        player->unk006 = 3;
        player->unk008 = 0;
        player->unk060.x += push.x;
        player->unk060.z += push.z;
        omVibrate(lane->unk004, 40, 12, 0);
        fn_1_6A04(player, &push);
        if (player->unk0C4 != 0) {
            if (lane->unk46C) {
                fn_1_5EC(0x64B);
            }
            else {
                fn_1_5EC(0x64C);
            }
        }
        return;
    }
    if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
        player->unk060.x += push.x;
        player->unk060.z += push.z;
    }
}

/* 476 insns: mode 3 -- hit by the chomp: thrown up, then either lands or is carried
 * over it (fn_1_91B0) */
void fn_1_8A40(M504_PLAYER *player)
{
    M504_LANE *lane;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    HU3DMODELID mdlId;
    float t;
    float s;
    float a;
    HuVecF pos;
    HuVecF push;
    s16 hitA;
    s16 hitB;

    lane = player->unk000;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    mdlId = player->unk018->mdlId[0];
    switch (player->unk008) {
        case 0:
            Hu3DModelAttrSet(player->unk0CC, HU3D_ATTR_DISPOFF);
            player->unk08A = 3;
            player->unk01C = 0;
            player->unk09E = 0;
            if (player->unk0C4 != 0) {
                if (lane->unk46C) {
                    fn_1_5EC(0x64D);
                }
                else {
                    fn_1_5EC(0x64E);
                }
            }
            player->unk008++;
        case 1:
            t = player->unk09E / 60.0f;
            a = 180.0f * t;
            s = sin(M_PI * a / 180.0);
            player->unk060.y = 1000.0f * s;
            player->unk09E++;
            if (player->unk060.y <= 0.0f && player->unk09E >= 30) {
                player->unk060.y = 0.0f;
                player->unk08A = 4;
                player->unk01C = 1;
                player->unk00A = 60;
                player->unk008++;
            }
            else if (player->unk09E >= 30 && fn_1_B43C(wanwan, &player->unk060, 60.000004f, &push, 1)) {
                fn_1_6A04(player, &push);
                fn_1_91B0(player);
                omVibrate(lane->unk004, 20, 12, 0);
                if (player->unk0C4 != 0) {
                    if (lane->unk46C) {
                        fn_1_5EC(0x64F);
                    }
                    else {
                        fn_1_5EC(0x650);
                    }
                }
            }
            break;
        case 2:
            if (fn_1_B43C(wanwan, &player->unk060, 75.0f, &push, 1)) {
                player->unk060.x += push.x;
                player->unk060.z += push.z;
            }
            if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
                player->unk060.x += push.x;
                player->unk060.z += push.z;
            }
            if (--player->unk00A == 0) {
                player->unk08A = 5;
                player->unk01C = 0;
                player->unk00A = 0;
                player->unk008++;
            }
            break;
        case 3:
            if (player->unk00A++ >= 30) {
                player->unk08A = 0;
                player->unk01C = 1;
                player->unk006 = 0;
                player->unk00A = 0;
                player->unk090 = 0;
                player->unk008 = 0;
            }
            break;
        case 4:
            player->unk06C.y += -2.4333334f;
            switch (player->unk09C) {
                case 0:
                    t = player->unk09E / 15.0f;
                    a = 90.0f * t;
                    s = sin(M_PI * a / 180.0);
                    s = player->unk0A0.y + s * (player->unk0AC.y - player->unk0A0.y);
                    PSVECSubtract(&player->unk0AC, &player->unk0A0, &pos);
                    pos.x *= t;
                    pos.y = s;
                    pos.z *= t;
                    pos.x += player->unk0A0.x;
                    pos.z += player->unk0A0.z;
                    player->unk060 = pos;
                    if (player->unk09E >= 15) {
                        player->unk09C++;
                    }
                    break;
                case 1:
                    t = (player->unk09E - 15) / 15.0f;
                    a = 90.0f + 90.0f * t;
                    s = sin(M_PI * a / 180.0);
                    s = player->unk0B8.y + s * (player->unk0AC.y - player->unk0B8.y);
                    PSVECSubtract(&player->unk0B8, &player->unk0AC, &pos);
                    pos.x *= t;
                    pos.y = s;
                    pos.z *= t;
                    pos.x += player->unk0AC.x;
                    pos.z += player->unk0AC.z;
                    player->unk060 = pos;
                    if (player->unk09E >= 30) {
                        player->unk09C++;
                    }
                    break;
                case 2:
                    player->unk060.y += player->unk06C.y;
                    break;
            }
            player->unk09E++;
            if (player->unk060.y <= 0.0f) {
                player->unk060.y = 0.0f;
                player->unk08A = 4;
                player->unk01C = 1;
                player->unk00A = 60;
                player->unk008 = 2;
                break;
            }
            if (player->unk09C != 0 && fn_1_B43C(wanwan, &player->unk060, 60.000004f, &push, 1)) {
                player->unk060.x += push.x;
                player->unk060.z += push.z;
            }
            if (fn_1_4030(stage, &player->unk060, 50.0f, &push, 0, &hitA, &hitB)) {
                player->unk060.x += push.x;
                player->unk060.z += push.z;
            }
            break;
    }
}

/* 97 insns: carried over the chomp -- arc from here to the far side (fn_1_B52C) */
void fn_1_91B0(M504_PLAYER *player)
{
    M504_LANE *lane;
    M504_WANWAN *wanwan;
    HuVecF mid;
    HuVecF end;

    lane = player->unk000;
    wanwan = &lane->unk0DC;
    if (!fn_1_B52C(wanwan, &end)) {
        player->unk06C.x = 0.0f;
        player->unk06C.y = 40.0f;
        player->unk06C.z = 0.0f;
        player->unk008 = 1;
        return;
    }
    player->unk09C = 0;
    player->unk09E = 0;
    player->unk0A0 = player->unk060;
    player->unk0B8 = end;
    PSVECSubtract(&player->unk0B8, &player->unk0A0, &mid);
    PSVECScale(&mid, &mid, 0.5f);
    PSVECAdd(&mid, &player->unk0A0, &mid);
    mid.y += 600.0f;
    player->unk0AC = mid;
    {
        HuVecF vel = { 0.0f, 0.0f, 0.0f };
        HuVecF *velP = &vel;
        player->unk06C = *velP;
    }
    player->unk008 = 4;
}

/* 211 insns: camera follow + shadow */
void fn_1_9334(M504_PLAYER *player)
{
    M504_LANE *lane;
    M504_CAMERA *camera;
    M504_STAGE *stage;
    M504_WANWAN *wanwan;
    float t;
    float dist;
    float z;
    float eyeZ;
    float eyeY;
    float tgtZ;
    float ofsY;

    lane = player->unk000;
    camera = &lane->unk3BC;
    stage = &lane->unk15C;
    wanwan = &lane->unk0DC;
    z = player->unk060.z;
    dist = (player->unk060.z - wanwan->unk038.z >= 0.0f) ? player->unk060.z - wanwan->unk038.z : -(player->unk060.z - wanwan->unk038.z);
    dist = (dist < 300.0f) ? 0.0f : dist - 300.0f;
    t = dist / 1200.0f;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
    if (player->unk060.z > wanwan->unk038.z) {
        eyeZ = 1000.0f + 1000.0f * t;
        eyeY = 1800.0f;
        tgtZ = -200.0f * t;
    }
    else {
        eyeZ = 1000.0f;
        eyeY = 1800.0f;
        tgtZ = 200.0f * t;
    }
    ofsY = (player->unk006 == 3) ? 0.5f * player->unk060.y : 0.0f;
    camera->unk018.z = z + tgtZ;
    camera->unk018.y = 300.0f + ofsY;
    camera->unk00C.z = z + eyeZ;
    camera->unk00C.y = eyeY + ofsY;
    camera->unk060 = 0.1f;
    lbl_1_data_474.z = z + (500.0f + eyeZ);
    lbl_1_data_48C.z = z;
    Hu3DShadowMultiPosSet(&lbl_1_data_474, &lbl_1_data_480, &lbl_1_data_48C, lbl_1_data_45E0[player->unk000->unk004]);
}

/*
 * Retail pools two { 0, 0, 0 } vector literals after the last float (.rodata 0x1D0,
 * 0x1DC) that no code references: the initializers of a helper that was never called
 * and so never emitted. This inline reproduces them; it has no symbol.
 */
static inline void PlayerUnusedInit(M504_PLAYER *player)
{
    HuVecF pos = { 0.0f, 0.0f, 0.0f };
    HuVecF target = { 0.0f, 0.0f, 0.0f };

    Hu3DShadowMultiPosSet(&pos, &lbl_1_data_480, &target, 0);
}

