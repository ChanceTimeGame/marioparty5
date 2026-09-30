/*
 * m502dll bat.c -- decompiled from build/mp5-asm/m502dll/asm/REL/m502dll/bat.s;
 * functions are in reference order.
 */

#include "REL/m502dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x498 */ /* s32 lbl_1_rodata_498[3] = { 0x00000000, 0x00000000, 0x43340000 }; */
/* 0x4A4 */ /* s32 lbl_1_rodata_4A4[3] = { 0x00000000, 0x00000000, 0x43340000 }; */
/* 0x4B0 */ /* float lbl_1_rodata_4B0 = 0.0f; */
/* 0x4B4 */ /* float lbl_1_rodata_4B4 = -300.0f; */
/* 0x4B8 */ /* float lbl_1_rodata_4B8 = 600.0f; */
/* 0x4BC */ /* float lbl_1_rodata_4BC = 255.0f; */
/* 0x4C0 */ /* float lbl_1_rodata_4C0 = 30.0f; */
/* 0x4C4 */ /* float lbl_1_rodata_4C4 = 20.0f; */
/* 0x4C8 */ /* float lbl_1_rodata_4C8 = 305.0f; */
/* 0x4CC */ /* float lbl_1_rodata_4CC = -240.0f; */
/* 0x4D0 */ /* double lbl_1_rodata_4D0 = 4503601774854144; */
/* 0x4D8 */ /* s32 lbl_1_rodata_4D8[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x4E4 */ /* s32 lbl_1_rodata_4E4[3] = { 0x00000000, 0x00000000, 0x43340000 }; */
/* 0x4F0 */ /* float lbl_1_rodata_4F0 = 1.3f; */
/* 0x4F4 */ /* float lbl_1_rodata_4F4 = -390.0f; */
/* 0x4F8 */ /* float lbl_1_rodata_4F8 = 780.0f; */
/* 0x4FC */ /* float lbl_1_rodata_4FC = 300.0f; */
/* 0x500 */ /* s32 lbl_1_rodata_500[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x50C */ /* float lbl_1_rodata_50C = 150.0f; */
/* 0x510 */ /* float lbl_1_rodata_510 = 10.0f; */
/* 0x514 */ /* float lbl_1_rodata_514 = 6.0f; */
/* 0x518 */ /* float lbl_1_rodata_518 = 12.0f; */
/* 0x51C */ /* float lbl_1_rodata_51C = 1.0f; */
/* 0x520 */ /* float lbl_1_rodata_520 = 5.0f; */
/* 0x524 */ /* float lbl_1_rodata_524 = 0.05f; */
/* 0x528 */ /* float lbl_1_rodata_528 = 100.0f; */
/* 0x52C */ /* float lbl_1_rodata_52C = 0.5f; */
/* 0x530 */ /* float lbl_1_rodata_530 = 0.3f; */
/* 0x534 */ /* float lbl_1_rodata_534 = 0.1f; */
/* 0x538 */ /* float lbl_1_rodata_538 = 3.0f; */
/* 0x53C */ /* float lbl_1_rodata_53C = 0.03f; */
/* 0x540 */ /* float lbl_1_rodata_540 = 180.0f; */
/* 0x544 */ /* float lbl_1_rodata_544 = 75.0f; */
/* 0x548 */ /* float lbl_1_rodata_548 = 0.2f; */
/* 0x54C */ /* float lbl_1_rodata_54C = 2.0f; */
/* 0x550 */ /* float lbl_1_rodata_550 = -45.0f; */
/* 0x554 */ /* float lbl_1_rodata_554 = 285.0f; */
/* 0x558 */ /* float lbl_1_rodata_558 = 45.0f; */
/* 0x55C */ /* float lbl_1_rodata_55C = 18.0f; */
/* 0x560 */ /* double lbl_1_rodata_560 = 3.141592653589793; */
/* 0x568 */ /* double lbl_1_rodata_568 = 180; */
/* 0x570 */ /* float lbl_1_rodata_570 = -750.0f; */
/* 0x574 */ /* float lbl_1_rodata_574 = 750.0f; */
/* 0x578 */ /* double lbl_1_rodata_578 = 4503599627370496; */
/* 0x580 */ /* float lbl_1_rodata_580 = 480.0f; */

int rand8(void);

/* retail passes the camera word unnarrowed (lwz, no extsh): no prototype in scope */
void Hu3D3Dto2D();

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x5090 */ s16 lbl_1_bss_5090;

/* --- functions (reference order) --- */
/* 34 insns */
void fn_1_C468(M502_BAT *bat, M502_PLAYER *player)
{
    s32 i;

    memset(bat, 0, sizeof(M502_BAT));
    bat->unk000 = player;
    for (i = 0; i < 8; i++) {
        fn_1_CB10(&bat->unk008[i], i, bat);
    }
    lbl_1_bss_5090 = 0;
}

/* 25 insns */
void fn_1_C4F0(M502_BAT *bat)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        fn_1_CE54(&bat->unk008[i]);
    }
    memset(bat, 0, sizeof(M502_BAT));
}

/* 349 insns */
void fn_1_C554(M502_BAT *bat)
{
    s32 i;
    M502_BATOBJ *obj;
    M502_CHAR *chr;
    float base;
    HuVecF pos;

    chr = &bat->unk000->unkF58;
    base = 0.0f;
    switch (bat->unk004) {
        case 0:
            fn_1_6CFC(0, 4, 1, &pos);
            if (chr->unk01C->trans.y < pos.y) {
                for (i = 0; i < 8; i++) {
                    obj = &bat->unk008[i];
                    if (i % 4 == 0) {
                        base = -300.0f + 600.0f * ((rand8() % 256) / 255.0f);
                    }
                    if (i < 5) {
                        fn_1_6CFC(0, 8, 1, &pos);
                        pos.x = base + 30.0f * (i % 4) + 20.0f * ((rand8() % 256) / 255.0f) - 30.0f;
                        pos.y -= 305.0f;
                        pos.z = -240.0f;
                        obj->unk018 = pos;
                        obj->unk030 = (HuVecF) { 0.0f, 0.0f, 180.0f };
                        obj->unk004 = 0;
                        obj->unk024.y = 0.0f;
                        Hu3DMotionSet(obj->unk00C, obj->unk00E);
                        Hu3DModelAttrReset(obj->unk00C, HU3D_MOTATTR_LOOP);
                    }
                    else {
                        obj->unk004 = 3;
                    }
                }
                bat->unk004++;
            }
            break;
        case 1:
            fn_1_6CFC(1, 4, 1, &pos);
            if (chr->unk01C->trans.y < pos.y) {
                for (i = 0; i < 8; i++) {
                    obj = &bat->unk008[i];
                    if (i % 4 == 0) {
                        base = -300.0f + 600.0f * ((rand8() % 256) / 255.0f);
                    }
                    fn_1_6CFC(1, 8, 1, &pos);
                    pos.x = base + 30.0f * (i % 4) + 20.0f * ((rand8() % 256) / 255.0f) - 30.0f;
                    pos.y -= 305.0f;
                    pos.z = -240.0f;
                    obj->unk018 = pos;
                    obj->unk030 = (HuVecF) { 0.0f, 0.0f, 180.0f };
                    obj->unk004 = 0;
                    obj->unk024.y = 0.0f;
                    Hu3DMotionSet(obj->unk00C, obj->unk00E);
                    Hu3DModelAttrReset(obj->unk00C, HU3D_MOTATTR_LOOP);
                }
                bat->unk004++;
            }
            break;
        case 2:
            break;
    }
    for (i = 0; i < 8; i++) {
        fn_1_CEBC(&bat->unk008[i]);
    }
}

/* 18 insns */
void fn_1_CAC8(M502_BAT *bat)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        bat->unk008[i].unk014 = 0;
        bat->unk008[i].unk004 = 3;
    }
}

/* 209 insns */
void fn_1_CB10(M502_BATOBJ *obj, u16 no, M502_BAT *bat)
{
    HU3DMODELID modelId;
    HuVecF pos;

    memset(obj, 0, sizeof(M502_BATOBJ));
    obj->unk000 = bat;
    modelId = Hu3DModelCreateData(DATANUM(DATA_m502, 0x85));
    obj->unk00C = modelId;
    obj->unk00E = Hu3DJointMotionData(modelId, DATANUM(DATA_m502, 0x86));
    obj->unk010 = Hu3DJointMotionData(modelId, DATANUM(DATA_m502, 0x87));
    obj->unk012 = Hu3DJointMotionData(modelId, DATANUM(DATA_m502, 0x88));
    Hu3DModelCameraSet(modelId, lbl_1_data_B60[bat->unk000->unk004]);
    Hu3DModelLayerSet(modelId, 0);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    obj->unk014 = 0;
    Hu3DModelScaleSet(modelId, 1.3f, 1.3f, 1.3f);
    pos = (HuVecF) { 0.0f, 0.0f, 0.0f };
    if (no < 8) {
        fn_1_6CFC(0, 8, 1, &pos);
        pos.x = -390.0f + 780.0f * ((rand8() % 256) / 255.0f);
    }
    else {
        fn_1_6CFC(1, 8, 1, &pos);
        pos.x = -390.0f + 780.0f * ((rand8() % 256) / 255.0f);
    }
    pos.y -= 300.0f;
    pos.z = -300.0f;
    obj->unk018 = pos;
    obj->unk030 = (HuVecF) { 0.0f, 0.0f, 180.0f };
    Hu3DModelPosSet(modelId, obj->unk018.x, obj->unk018.y, obj->unk018.z);
    Hu3DModelRotSet(modelId, obj->unk030.x, obj->unk030.y, obj->unk030.z);
}

/* 26 insns */
void fn_1_CE54(M502_BATOBJ *obj)
{
    Hu3DModelAttrSet(obj->unk00C, HU3D_MOTATTR_PAUSE);
    Hu3DMotionKill(obj->unk012);
    Hu3DMotionKill(obj->unk010);
    Hu3DMotionKill(obj->unk00E);
    Hu3DModelKill(obj->unk00C);
    memset(obj, 0, sizeof(M502_BATOBJ));
}

/* 1014 insns */
void fn_1_CEBC(M502_BATOBJ *obj)
{
    M502_PLAYER *player;
    M502_CHAR *chr;
    M502_BLOCK *block;
    M502_BLOCKCELL *cell;
    s32 visible;
    float t;
    HuVecF pos;
    HuVecF top;
    HuVecF bot;
    HuVecF top2d;
    HuVecF bot2d;
    s16 floor;
    s16 row;
    s16 lane;

    player = obj->unk000->unk000;
    chr = &player->unkF58;
    block = &player->unk008;
    bot2d = (HuVecF) { 0.0f, 0.0f, 0.0f };
    top2d = bot2d;
    if (obj->unk004 >= 3) {
        visible = 0;
    }
    else {
        bot = obj->unk018;
        top = bot;
        top.y += 300.0f;
        bot.y -= 300.0f;
        Hu3D3Dto2D(&top, obj->unk000->unk000->unk1048.unk004, &top2d);
        Hu3D3Dto2D(&bot, obj->unk000->unk000->unk1048.unk004, &bot2d);
        visible = fn_1_DE94(&top2d) || fn_1_DE94(&bot2d);
    }
    if (obj->unk014 != 0 && !visible) {
        Hu3DModelAttrSet(obj->unk00C, HU3D_ATTR_DISPOFF);
        obj->unk014 = 0;
    }
    else if (obj->unk014 == 0 && visible) {
        Hu3DModelAttrReset(obj->unk00C, HU3D_ATTR_DISPOFF);
        obj->unk014 = 1;
    }
    switch (obj->unk004) {
        case 0:
            pos = obj->unk018;
            pos.x += 150.0f;
            pos.y += 300.0f;
            fn_1_6E1C(&pos, &floor, &row, &lane);
            cell = &block->unk004[floor][row * 3 + lane];
            if (floor < 6 && cell->unk004 == 0) {
                obj->unk004++;
            }
            else if (chr->unk01C->trans.y < obj->unk018.y && chr->unk01C->trans.x > obj->unk018.x - 150.0f
                && chr->unk01C->trans.x < 150.0f + obj->unk018.x) {
                obj->unk004++;
            }
            break;
        case 1:
            if (lbl_1_bss_5090++ < 4) {
                fn_1_218(fn_1_198(0x62F), (chr->unk010 == 0) ? 40 : (chr->unk010 == 1) ? 56 : (chr->unk010 == 2) ? 72 : 88);
            }
            obj->unk03C = (rand8() % 100 < 50) ? 1 : 0;
            obj->unk044 = rand8() % 100;
            obj->unk006 = 0;
            obj->unk008 = rand8() % 180 + 180;
            obj->unk00A = (rand8() % 100) / 10 + 10;
            obj->unk004++;
            break;
        case 2:
            if (obj->unk006 == 3) {
                Hu3DMotionSet(obj->unk00C, obj->unk010);
                Hu3DMotionSpeedSet(obj->unk00C, 10.0f);
                Hu3DModelAttrReset(obj->unk00C, HU3D_MOTATTR_LOOP);
            }
            else if (obj->unk006 == 8) {
                Hu3DMotionSet(obj->unk00C, obj->unk012);
                Hu3DMotionSpeedSet(obj->unk00C, 6.0f);
                Hu3DModelAttrSet(obj->unk00C, HU3D_MOTATTR_LOOP);
            }
            if (obj->unk006 >= 12) {
                t = (obj->unk006 - 16) / 12.0f;
                t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);
                if (obj->unk006 < 24) {
                    obj->unk018.y += (1.0f - t) * (5.0f + 0.05f * obj->unk044);
                }
                if (obj->unk03C) {
                    obj->unk018.x -= ((100.0f + obj->unk044) / 10.0f) * (0.5f + 0.5f * t);
                    obj->unk018.z -= (0.05f * obj->unk044) * (0.5f + 0.5f * t);
                }
                else {
                    obj->unk018.x += ((100.0f + obj->unk044) / 10.0f) * (0.5f + 0.5f * t);
                    obj->unk018.z -= (0.05f * obj->unk044) * (0.5f + 0.5f * t);
                }
            }
            else {
                t = obj->unk006 / 12.0f;
                t = 1.0f - ((t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t));
                obj->unk018.y -= t * (10.0f + 0.3f * obj->unk044);
                if (obj->unk03C) {
                    obj->unk018.x -= ((100.0f + obj->unk044) / 10.0f) * (0.1f + 0.1f * t);
                }
                else {
                    obj->unk018.x += ((100.0f + obj->unk044) / 10.0f) * (0.1f + 0.1f * t);
                }
            }
            if (obj->unk03C) {
                obj->unk030.z = (obj->unk030.z - (3.0f + 0.03f * obj->unk044) > 180.0f) ? 180.0f
                    : ((obj->unk030.z - (3.0f + 0.03f * obj->unk044) < 75.0f - 0.2f * obj->unk044) ? 75.0f - 0.2f * obj->unk044
                                                                                                  : obj->unk030.z - (3.0f + 0.03f * obj->unk044));
                obj->unk030.y = (obj->unk030.y - (2.0f + 0.03f * obj->unk044) > 0.0f) ? 0.0f
                    : ((obj->unk030.y - (2.0f + 0.03f * obj->unk044) < -45.0f) ? -45.0f : obj->unk030.y - (2.0f + 0.03f * obj->unk044));
            }
            else {
                obj->unk030.z = (obj->unk030.z + (3.0f + 0.03f * obj->unk044) > 285.0f + 0.2f * obj->unk044) ? 285.0f + 0.2f * obj->unk044
                    : ((obj->unk030.z + (3.0f + 0.03f * obj->unk044) < 180.0f) ? 180.0f : obj->unk030.z + (3.0f + 0.03f * obj->unk044));
                obj->unk030.y = (obj->unk030.y + (2.0f + 0.03f * obj->unk044) > 45.0f) ? 45.0f
                    : ((obj->unk030.y + (2.0f + 0.03f * obj->unk044) < 0.0f) ? 0.0f : obj->unk030.y + (2.0f + 0.03f * obj->unk044));
            }
            t = (obj->unk008 / 180.0f > 1.0f) ? 1.0f : ((obj->unk008 / 180.0f < 0.0f) ? 0.0f : obj->unk008 / 180.0f);
            t = 12.0f + 18.0f * (1.0f - t);
            obj->unk024.y += t * sin(M_PI * (float)(obj->unk008 * obj->unk00A % 360 + 180) / 180.0);
            if (obj->unk018.x < -750.0f || obj->unk018.x > 750.0f) {
                if (lbl_1_bss_5090 != 0) {
                    lbl_1_bss_5090--;
                }
                obj->unk004++;
            }
            obj->unk006++;
            obj->unk008++;
            break;
        case 3:
            break;
    }
    Hu3DModelPosSet(obj->unk00C, obj->unk018.x + obj->unk024.x, obj->unk018.y + obj->unk024.y, obj->unk018.z + obj->unk024.z);
    Hu3DModelRotSet(obj->unk00C, obj->unk030.x, obj->unk030.y, obj->unk030.z);
}

/* 17 insns */
s32 fn_1_DE94(HuVecF *pos)
{
    if (pos->y < 0.0f || pos->y >= 480.0f) {
        return 0;
    }
    return 1;
}
