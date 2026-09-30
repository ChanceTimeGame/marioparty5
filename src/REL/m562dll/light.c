/*
 * m562dll light.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/light.s.
 */

#include "REL/m562dll.h"

#include "game/audio.h"
#include "game/frand.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "math.h"
#include "string.h"

#ifndef __MWERKS__
#include "game/hsfex.h"
#include "game/esprite.h"
#endif

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_A70 = 1.0f; /* 0xA70 */
static const float lbl_1_rodata_A74 = 30.0f; /* 0xA74 */
/* 0xA78 lbl_1_rodata_A78 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_A80 = 0.8f; /* 0xA80 (+4 bytes: section tail alignment) */

/* --- functions (reference order), .data placed before its first user --- */
/* 0xB10 */ float lbl_1_data_B10[3] = { 0.8f, 0.8f, 0.8f };
/* 0xB1C */ float lbl_1_data_B1C[3] = { 2000.0f, 10000.0f, 0.0f };
/* 0xB28 */ float lbl_1_data_B28[3] = { -1.0f, -1.0f, 0.0f };
/* 0xB34 */ GXColor lbl_1_data_B34 = { 0xFF, 0xFF, 0xFF, 0xFF };
/* 0xB35 */ /* lbl_1_data_B35: the last three bytes of the GXColor above (dtk split) */
/* 0xB38 */ float lbl_1_data_B38[3] = { 0.6f, 0.6f, 0.7f };
/* 0xB44 */ float lbl_1_data_B44[3] = { 2000.0f, 10000.0f, 0.0f };
/* 0xB50 */ float lbl_1_data_B50[3] = { -1.0f, -1.0f, 0.0f };
/* 0xB5C */ GXColor lbl_1_data_B5C = { 0xB2, 0x99, 0x7F, 0xFF };
/* 0xB5D */ /* lbl_1_data_B5D: the last three bytes of the GXColor above (dtk split) */
/* 0xB60 */ float lbl_1_data_B60[3] = { 0.1f, 0.1f, 0.4f };
/* 0xB6C */ float lbl_1_data_B6C[3] = { 2000.0f, 10000.0f, 0.0f };
/* 0xB78 */ float lbl_1_data_B78[3] = { -1.0f, -1.0f, 0.0f };
/* 0xB84 */ GXColor lbl_1_data_B84 = { 0x99, 0x7F, 0x4C, 0xFF };
/* 0xB85 */ /* lbl_1_data_B85: the last three bytes of the GXColor above (dtk split) */
/* 0xB88 */ float lbl_1_data_B88[3] = { 0.5f, 0.5f, 0.5f };
/* 0xB94 */ float lbl_1_data_B94[3] = { 0.0f, -2200.0f, 2300.0f };
/* 0xBA0 */ float lbl_1_data_BA0[3] = { 0.0f, 0.5f, -1.0f };
/* 0xBAC */ GXColor lbl_1_data_BAC = { 0xE5, 0xB2, 0xB2, 0xFF };
/* 0xBAD */ /* lbl_1_data_BAD: the last three bytes of the GXColor above (dtk split) */
/* 0xBB0 */ float lbl_1_data_BB0[3] = { 0.0f, 800.0f, 1000.0f };
/* 0xBBC */ float lbl_1_data_BBC[3] = { 0.0f, -1.0f, -1.0f };
/* 0xBC8 */ GXColor lbl_1_data_BC8 = { 0x60, 0x50, 0x60, 0xFF };

/* 57 insns */
void fn_1_2253C(M562_LIGHT *light, M562_WORK *work)
{
    memset(light, 0, sizeof(M562_LIGHT));
    light->unk00 = work;
    Hu3DAmbColorSet(1.0f, 1.0f, 1.0f);
    light->unk04 = Hu3DGLightCreateV((HuVecF *)lbl_1_data_B1C, (HuVecF *)lbl_1_data_B28, &lbl_1_data_B34);
    Hu3DGLightStaticSet(light->unk04, 1);
    Hu3DGLightInfinitytSet(light->unk04);
    light->unk06 = Hu3DGLightCreateV((HuVecF *)lbl_1_data_BB0, (HuVecF *)lbl_1_data_BBC, &lbl_1_data_BC8);
    Hu3DGLightSpotSet(light->unk06, GX_SP_COS, 30.0f);
    Hu3DGLightStaticSet(light->unk06, 1);
}

/* 28 insns */
void fn_1_22620(M562_LIGHT *light)
{
    if (light->unk06 >= 0) {
        Hu3DGLightKill(light->unk06);
        light->unk06 = -1;
    }
    if (light->unk04 != 0) {
        Hu3DGLightKill(light->unk04);
        light->unk04 = -1;
    }
    memset(light, 0, sizeof(M562_LIGHT));
}

/* 1 insns */
void fn_1_22690(M562_LIGHT *light) { }

/* 0xBC9 */ /* lbl_1_data_BC9: the last three bytes of the GXColor above (dtk split) */
/* 0xBCC */ float lbl_1_data_BCC[3] = { 0.0f, 1500.0f, 0.0f };
/* 0xBD8 */ float lbl_1_data_BD8[3] = { 0.0f, -1.0f, 0.02f };
/* 0xBE4 */ GXColor lbl_1_data_BE4 = { 0x80, 0x60, 0x80, 0xFF };
/* 0xBE8 */ GXColor lbl_1_data_BE8[2] = { { 0x00, 0x00, 0x00, 0x00 } }; /* [0] = the spot light colour of phase 3 (black); 8 bytes in the reference */

/* 1417 insns */
void fn_1_22694(M562_LIGHT *light, s16 mode, float t)
{
    M562_WORK *work = light->unk00;
    M562_BACK *back = &work->back;
    M562_STAGE *stage = &work->stage;
    GXColor col;
    HuVecF amb;
    HuVecF pos;
    HuVecF dir;

    if (mode == 3) {
        if (light->unk08 == 0) {
            Hu3DGLightKill(light->unk06);
            light->unk06 = Hu3DLLightCreateV(stage->unk5AE, (HuVecF *)lbl_1_data_BCC, (HuVecF *)lbl_1_data_BD8, &lbl_1_data_BE4);
            Hu3DLLightSpotSet(stage->unk5AE, light->unk06, GX_SP_COS, 30.0f);
            Hu3DLLightStaticSet(stage->unk5AE, light->unk06, 1);
            light->unk08 = 1;
        }
    }
    else if (light->unk08 != 0) {
        Hu3DGLightKill(light->unk06);
        light->unk06 = Hu3DGLightCreateV((HuVecF *)lbl_1_data_BB0, (HuVecF *)lbl_1_data_BBC, &lbl_1_data_BC8);
        Hu3DGLightSpotSet(light->unk06, GX_SP_COS, 30.0f);
        Hu3DGLightStaticSet(light->unk06, 1);
        light->unk08 = 0;
    }
    switch (mode) {
        case 0:
        amb.x = lbl_1_data_B10[0] * t + lbl_1_data_B88[0] * (1.0f - t);
        amb.y = lbl_1_data_B10[1] * t + lbl_1_data_B88[1] * (1.0f - t);
        amb.z = lbl_1_data_B10[2] * t + lbl_1_data_B88[2] * (1.0f - t);
        fn_1_23CB8(work, &amb);
        pos.x = lbl_1_data_B1C[0] * t + lbl_1_data_B94[0] * (1.0f - t);
        pos.y = lbl_1_data_B1C[1] * t + lbl_1_data_B94[1] * (1.0f - t);
        pos.z = lbl_1_data_B1C[2] * t + lbl_1_data_B94[2] * (1.0f - t);
        dir.x = lbl_1_data_B28[0] * t + lbl_1_data_BA0[0] * (1.0f - t);
        dir.y = lbl_1_data_B28[1] * t + lbl_1_data_BA0[1] * (1.0f - t);
        dir.z = lbl_1_data_B28[2] * t + lbl_1_data_BA0[2] * (1.0f - t);
        Hu3DGLightPosSetV(light->unk04, &pos, &dir);
        col.r = lbl_1_data_B34.r * t + lbl_1_data_BAC.r * (1.0f - t);
        col.g = lbl_1_data_B34.g * t + lbl_1_data_BAC.g * (1.0f - t);
        col.b = lbl_1_data_B34.b * t + lbl_1_data_BAC.b * (1.0f - t);
        col.a = lbl_1_data_B34.a * t + lbl_1_data_BAC.a * (1.0f - t);
        Hu3DGLightColorSet(light->unk04, col.r, col.g, col.b, col.a);
            Hu3DGLightColorSet(light->unk06, 0, 0, 0, 0);
            break;
        case 1:
        amb.x = lbl_1_data_B38[0] * t + lbl_1_data_B10[0] * (1.0f - t);
        amb.y = lbl_1_data_B38[1] * t + lbl_1_data_B10[1] * (1.0f - t);
        amb.z = lbl_1_data_B38[2] * t + lbl_1_data_B10[2] * (1.0f - t);
        fn_1_23CB8(work, &amb);
        pos.x = lbl_1_data_B44[0] * t + lbl_1_data_B1C[0] * (1.0f - t);
        pos.y = lbl_1_data_B44[1] * t + lbl_1_data_B1C[1] * (1.0f - t);
        pos.z = lbl_1_data_B44[2] * t + lbl_1_data_B1C[2] * (1.0f - t);
        dir.x = lbl_1_data_B50[0] * t + lbl_1_data_B28[0] * (1.0f - t);
        dir.y = lbl_1_data_B50[1] * t + lbl_1_data_B28[1] * (1.0f - t);
        dir.z = lbl_1_data_B50[2] * t + lbl_1_data_B28[2] * (1.0f - t);
        Hu3DGLightPosSetV(light->unk04, &pos, &dir);
        col.r = lbl_1_data_B5C.r * t + lbl_1_data_B34.r * (1.0f - t);
        col.g = lbl_1_data_B5C.g * t + lbl_1_data_B34.g * (1.0f - t);
        col.b = lbl_1_data_B5C.b * t + lbl_1_data_B34.b * (1.0f - t);
        col.a = lbl_1_data_B5C.a * t + lbl_1_data_B34.a * (1.0f - t);
        Hu3DGLightColorSet(light->unk04, col.r, col.g, col.b, col.a);
            Hu3DGLightColorSet(light->unk06, 0, 0, 0, 0);
            break;
        case 2:
        amb.x = lbl_1_data_B60[0] * t + lbl_1_data_B38[0] * (1.0f - t);
        amb.y = lbl_1_data_B60[1] * t + lbl_1_data_B38[1] * (1.0f - t);
        amb.z = lbl_1_data_B60[2] * t + lbl_1_data_B38[2] * (1.0f - t);
        fn_1_23CB8(work, &amb);
        pos.x = lbl_1_data_B6C[0] * t + lbl_1_data_B44[0] * (1.0f - t);
        pos.y = lbl_1_data_B6C[1] * t + lbl_1_data_B44[1] * (1.0f - t);
        pos.z = lbl_1_data_B6C[2] * t + lbl_1_data_B44[2] * (1.0f - t);
        dir.x = lbl_1_data_B78[0] * t + lbl_1_data_B50[0] * (1.0f - t);
        dir.y = lbl_1_data_B78[1] * t + lbl_1_data_B50[1] * (1.0f - t);
        dir.z = lbl_1_data_B78[2] * t + lbl_1_data_B50[2] * (1.0f - t);
        Hu3DGLightPosSetV(light->unk04, &pos, &dir);
        col.r = lbl_1_data_B84.r * t + lbl_1_data_B5C.r * (1.0f - t);
        col.g = lbl_1_data_B84.g * t + lbl_1_data_B5C.g * (1.0f - t);
        col.b = lbl_1_data_B84.b * t + lbl_1_data_B5C.b * (1.0f - t);
        col.a = lbl_1_data_B84.a * t + lbl_1_data_B5C.a * (1.0f - t);
        Hu3DGLightColorSet(light->unk04, col.r, col.g, col.b, col.a);
        pos.x = lbl_1_data_BB0[0] * t + lbl_1_data_BCC[0] * (1.0f - t);
        pos.y = lbl_1_data_BB0[1] * t + lbl_1_data_BCC[1] * (1.0f - t);
        pos.z = lbl_1_data_BB0[2] * t + lbl_1_data_BCC[2] * (1.0f - t);
        dir.x = lbl_1_data_BBC[0] * t + lbl_1_data_BD8[0] * (1.0f - t);
        dir.y = lbl_1_data_BBC[1] * t + lbl_1_data_BD8[1] * (1.0f - t);
        dir.z = lbl_1_data_BBC[2] * t + lbl_1_data_BD8[2] * (1.0f - t);
        Hu3DGLightPosSetV(light->unk06, &pos, &dir);
        col.r = lbl_1_data_BC8.r * t + lbl_1_data_BE8[0].r * (1.0f - t);
        col.g = lbl_1_data_BC8.g * t + lbl_1_data_BE8[0].g * (1.0f - t);
        col.b = lbl_1_data_BC8.b * t + lbl_1_data_BE8[0].b * (1.0f - t);
        col.a = lbl_1_data_BC8.a * t + lbl_1_data_BE8[0].a * (1.0f - t);
        Hu3DGLightColorSet(light->unk06, col.r, col.g, col.b, col.a);
            break;
        case 3:
        amb.x = lbl_1_data_B88[0] * t + lbl_1_data_B60[0] * (1.0f - t);
        amb.y = lbl_1_data_B88[1] * t + lbl_1_data_B60[1] * (1.0f - t);
        amb.z = lbl_1_data_B88[2] * t + lbl_1_data_B60[2] * (1.0f - t);
        fn_1_23CB8(work, &amb);
        pos.x = lbl_1_data_B94[0] * t + lbl_1_data_B6C[0] * (1.0f - t);
        pos.y = lbl_1_data_B94[1] * t + lbl_1_data_B6C[1] * (1.0f - t);
        pos.z = lbl_1_data_B94[2] * t + lbl_1_data_B6C[2] * (1.0f - t);
        dir.x = lbl_1_data_BA0[0] * t + lbl_1_data_B78[0] * (1.0f - t);
        dir.y = lbl_1_data_BA0[1] * t + lbl_1_data_B78[1] * (1.0f - t);
        dir.z = lbl_1_data_BA0[2] * t + lbl_1_data_B78[2] * (1.0f - t);
        Hu3DGLightPosSetV(light->unk04, &pos, &dir);
        col.r = lbl_1_data_BAC.r * t + lbl_1_data_B84.r * (1.0f - t);
        col.g = lbl_1_data_BAC.g * t + lbl_1_data_B84.g * (1.0f - t);
        col.b = lbl_1_data_BAC.b * t + lbl_1_data_B84.b * (1.0f - t);
        col.a = lbl_1_data_BAC.a * t + lbl_1_data_B84.a * (1.0f - t);
        Hu3DGLightColorSet(light->unk04, col.r, col.g, col.b, col.a);
            break;
    }
}

/* 133 insns */
void fn_1_23CB8(M562_WORK *work, HuVecF *amb)
{
    M562_LIGHT *light = &work->light;
    M562_BACK *back = &work->back;
    M562_KOOPA *koopa = &work->koopa;
    M562_KOOPABOSS *koopaboss = &work->koopaboss;
    M562_PLAYER *player = &work->player;
    M562_STAGE *stage = &work->stage;
    s32 i;
    M562_STAGETILE *entry;

    Hu3DModelAmbSet(back->unk0C, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(back->unk0E, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(back->unk10, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(back->unk1A, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(back->unk1C, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(back->unk20, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(koopaboss->unk020, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(player->unk024, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5A8, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5AA, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5AC, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5AE, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5B0, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5B6, amb->x, amb->y, amb->z);
    Hu3DModelAmbSet(stage->unk5C0, amb->x, amb->y, amb->z);
    for (i = 0; i < 20; i++) {
        entry = &stage->unk008[i];
        Hu3DModelAmbSet(entry->unk08, amb->x, amb->y, amb->z);
    }
    if (koopa->mode == 3) {
        Hu3DModelAmbSet(koopa->model, amb->x, amb->y, amb->z);
    }
    else {
        Hu3DModelAmbSet(koopa->model, 0.8f, 0.8f, 0.8f);
    }
    light->unk0C = *amb;
}

