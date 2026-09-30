/*
 * The types and symbols m560.c and effect.c both need. The original compiles
 * the two as separate translation units (upstream's configure.py declares them
 * that way), and m560.c calls three functions out of effect.c.
 */
#ifndef M560_H
#define M560_H

#include "game/object.h"
#include "game/hu3d.h"
#include "humath.h"

/*
 * The per-particle parameters the dust effect carries alongside each
 * HU3DPARTICLEDATA. This is charman.c's EFFECTPARAM: it is file-local there,
 * so the original necessarily declares it a second time inside this overlay.
 * 0x38 bytes -- see effect.c for how the layout is pinned down.
 */
typedef struct M560EffectParam_s {
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
} M560_EFFECTPARAM;            /* 0x38 */

/* effect.c */
void M560EffectInit(void);
void M560EffectDustRingCreate(s16 cameraBit, HuVecF *pos);
void M560EffectParticleInit(void);

#endif
