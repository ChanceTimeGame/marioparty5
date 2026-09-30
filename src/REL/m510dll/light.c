/*
 * m510dll light.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m510dll/asm/REL/m510dll/light.s.
 */

#include "REL/m510dll.h"

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
/* 0x400 */ HuVecF lbl_1_data_400 = { 7000.0f, 7000.0f, 7000.0f };
/* 0x40C */ HuVecF lbl_1_data_40C = { -1.0f, -1.0f, -1.0f };
/* 0x418 */ GXColor lbl_1_data_418 = { 255, 255, 255, 255 };

/* --- functions (reference order) --- */
/* 30 insns */
void fn_1_959C(M510_LIGHT *light, M510_WORK *work)
{
    memset(light, 0, sizeof(M510_LIGHT));
    light->unk000 = work;
    light->unk004 = Hu3DGLightCreateV(&lbl_1_data_400, &lbl_1_data_40C, &lbl_1_data_418);
    Hu3DGLightStaticSet(light->unk004, TRUE);
    Hu3DGLightInfinitytSet(light->unk004);
}

/* 21 insns */
void fn_1_9614(M510_LIGHT *light)
{
    if (light->unk004 != 0) {
        Hu3DGLightKill(light->unk004);
        light->unk004 = 0;
    }
    memset(light, 0, sizeof(M510_LIGHT));
}

/* 1 insns */
void fn_1_9668(M510_LIGHT *light)
{
}
