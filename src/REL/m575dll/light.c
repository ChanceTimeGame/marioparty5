/*
 * m575dll light.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m575dll/asm/REL/m575dll/light.s.
 */

#include "REL/m575dll.h"

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
/* 0x2C0 */ HuVecF lbl_1_data_2C0 = { 7000.0f, 7000.0f, 7000.0f };
/* 0x2CC */ HuVecF lbl_1_data_2CC = { -1.0f, -1.0f, -1.0f };
/* 0x2D8 */ GXColor lbl_1_data_2D8[2] = { { 255, 255, 255, 255 }, { 0, 0, 0, 0 } }; /* white; the second is a zero word dtk folds in */

/* --- functions (reference order) --- */
void fn_1_9250(M575_LIGHT *light, M575_TEAM *team)
{
    memset(light, 0, sizeof(M575_LIGHT));
    light->unk000 = team;
    light->unk004 = Hu3DGLightCreateV(&lbl_1_data_2C0, &lbl_1_data_2CC, &lbl_1_data_2D8[0]);
    Hu3DGLightStaticSet(light->unk004, TRUE);
    Hu3DGLightInfinitytSet(light->unk004);
}

void fn_1_92C8(M575_LIGHT *light)
{
    if (light->unk004 != 0) {
        Hu3DGLightKill(light->unk004);
        light->unk004 = 0;
    }
    memset(light, 0, sizeof(M575_LIGHT));
}

void fn_1_931C(M575_LIGHT *light)
{
}
