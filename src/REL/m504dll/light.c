/*
 * m504dll light.c -- decompiled from the reference assembly; functions are in reference
 * order. Line ranges are into build/mp5-asm/m504dll/asm/REL/m504dll/light.s.
 */

#include "REL/m504dll.h"

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
/* 0x45F0 */ HuVecF lbl_1_data_45F0 = { 0.0f, 2000.0f, 500.0f }; /* light pos */
/* 0x45FC */ HuVecF lbl_1_data_45FC = { -1.0f, -1.0f, -1.0f }; /* light dir */
/* 0x4608 */ GXColor lbl_1_data_4608 = { 0xFF, 0xFF, 0xFF, 0xFF };

/* --- functions (reference order) --- */
/* 30 insns */
void fn_1_D03C(M504_LIGHT *light, M504_WORK *work)
{
    memset(light, 0, sizeof(M504_LIGHT));
    light->unk000 = work;
    light->unk004 = Hu3DGLightCreateV(&lbl_1_data_45F0, &lbl_1_data_45FC, &lbl_1_data_4608);
    Hu3DGLightStaticSet(light->unk004, TRUE);
    Hu3DGLightInfinitytSet(light->unk004);
}

/* 21 insns */
void fn_1_D0B4(M504_LIGHT *light)
{
    if (light->unk004 != 0) {
        Hu3DGLightKill(light->unk004);
        light->unk004 = 0;
    }
    memset(light, 0, sizeof(M504_LIGHT));
}

/* 1 insns */
void fn_1_D108(M504_LIGHT *light)
{
}
