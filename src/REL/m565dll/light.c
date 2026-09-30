/*
 * m565dll light.c -- written 2026-09-23 (W1 forks; see NOTES.md). Functions are in reference
 * order. Line ranges are into build/mp5-asm/m565dll/asm/REL/m565dll/light.s.
 */

#include "REL/m565dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .data --- */
/* 0xC40 */ HuVecF lbl_1_data_C40 = { 7000.0f, 7000.0f, 7000.0f };
/* 0xC4C */ HuVecF lbl_1_data_C4C = { -1.0f, -1.0f, -1.0f };
/* 0xC58 */ GXColor lbl_1_data_C58 = { 0xFF, 0xFF, 0xFF, 0xFF };

/* --- functions (reference order) --- */
/* 30 insns */
void fn_1_FCBC(M565_LIGHT *light, M565_OBJECT *obj)
{
    memset(light, 0, sizeof(M565_LIGHT));
    light->unk000 = obj;
    light->unk004 = Hu3DGLightCreateV(&lbl_1_data_C40, &lbl_1_data_C4C, &lbl_1_data_C58);
    Hu3DGLightStaticSet(light->unk004, TRUE);
    Hu3DGLightInfinitytSet(light->unk004);
}

/* 21 insns */
void fn_1_FD34(M565_LIGHT *light)
{
    if (light->unk004 != 0) {
        Hu3DGLightKill(light->unk004);
        light->unk004 = 0;
    }
    memset(light, 0, sizeof(M565_LIGHT));
}

/* 1 insns */
void fn_1_FD88(M565_LIGHT *light)
{
}
