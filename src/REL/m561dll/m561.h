/*
 * The types and symbols m561.c and effect.c both need. The original compiles
 * the two as separate translation units (upstream's configure.py declares them
 * that way), and m561.c calls three functions out of effect.c.
 */
#ifndef M561_H
#define M561_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/*
 * The per-particle parameters the dust effect carries alongside each
 * HU3DPARTICLEDATA. This is charman.c's EFFECTPARAM: it is file-local there,
 * so the original necessarily declares it a second time inside this overlay.
 * 0x38 bytes -- see effect.c for how the layout is pinned down.
 */
typedef struct M561EffectParam_s {
    /* 0x00 */ u32 attr;
    /* 0x04 */ GXColor colorBegin;
    /* 0x08 */ GXColor colorEnd;
    /* 0x0C */ HuVecF vel;
    /* 0x18 */ HuVecF velDecay;
    /* 0x24 */ float gravity;
    /* 0x28 */ u32 zero;
    /* 0x2C */ float scaleVel;
    /* 0x30 */ float alphaBase;
    /* 0x34 */ float colorWeight;
} M561_EFFECTPARAM;            /* 0x38 */

/* One player's work (obj->data, 0xAC, fn_1_58C). */
typedef struct M561Player_s {
    /* 0x00 */ s16 motNo;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ u8 unk04[0x10];
    /* 0x14 */ s32 no;
    /* 0x18 */ s32 charNo;
    /* 0x1C */ s32 padNo;
    /* 0x20 */ s32 btn;
    /* 0x24 */ s32 mode;
    /* 0x28 */ s32 timer;
    /* 0x2C */ HuVecF pos;
    /* 0x38 */ float scale;
    /* 0x3C */ HuVecF *unk3C;
    /* 0x40 */ HuVecF unk40;
    /* 0x4C */ HuVecF rot;
    /* 0x58 */ float unk58;
    /* 0x5C */ float unk5C;
    /* 0x60 */ float unk60;
    /* 0x64 */ HuVecF unk64;
    /* 0x70 */ HuVecF unk70;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 dif;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ s32 unk90;
    /* 0x94 */ s32 unk94;
    /* 0x98 */ s32 unk98;
    /* 0x9C */ float unk9C;
    /* 0xA0 */ s32 unkA0;
    /* 0xA4 */ s32 unkA4;
    /* 0xA8 */ float unkA8;
} M561_PLAYER;                      /* 0xAC */

/* Bowser (group 1, fn_1_38EC's obj->data). 0x60 bytes; offset-named where no function proves a meaning. */
typedef struct M561Kupa_s {
    /* 0x00 */ HU3DMODELID unk00;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF speed;
    /* 0x1C */ HuVecF rot;
    /* 0x28 */ float unk28;         /* rot.y step toward the next side */
    /* 0x2C */ s32 motNo;
    /* 0x30 */ s32 mode;
    /* 0x34 */ s32 timer;
    /* 0x38 */ s32 unk38;           /* key index into lbl_1_data_29C */
    /* 0x3C */ float unk3C;         /* key time */
    /* 0x40 */ float motTime;
    /* 0x44 */ s32 unk44;           /* fire billboard model, -1 for none */
    /* 0x48 */ s32 unk48;           /* second fire billboard model */
    /* 0x4C */ s32 unk4C;           /* side 0-2 (lbl_1_data_2C4) */
    /* 0x50 */ s32 unk50;           /* previous side */
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
} M561_KUPA;                        /* 0x60 */

/* effect.c */
void fn_1_8AE8(void);
void fn_1_8BCC(s16 cameraBit, HuVecF *pos);
void fn_1_9464(void);

#endif
