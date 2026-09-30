/*
 * m562dll sprite.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/m562dll/asm/REL/m562dll/sprite.s.
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
static const float lbl_1_rodata_A88 = 32.0f; /* 0xA88 */
static const float lbl_1_rodata_A8C = 112.0f; /* 0xA8C */
static const float lbl_1_rodata_A90 = 544.0f; /* 0xA90 */
static const float lbl_1_rodata_A94 = 0.0f; /* 0xA94 */
static const float lbl_1_rodata_A98 = 24.0f; /* 0xA98 */
/* 0xAA0 lbl_1_rodata_AA0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_AA8 = 1.0f; /* 0xAA8 */
static const float lbl_1_rodata_AAC = 0.5f; /* 0xAAC */

/* --- functions (reference order), .data placed before its first user --- */
/* 0xBF0 */ u32 lbl_1_data_BF0[16] = { DATA_mgconst, DATANUM(DATA_mgconst, 1), DATANUM(DATA_mgconst, 2), DATANUM(DATA_mgconst, 3), DATANUM(DATA_mgconst, 4), DATANUM(DATA_mgconst, 6), DATANUM(DATA_mgconst, 7), DATANUM(DATA_mgconst, 8), DATANUM(DATA_mgconst, 9), DATANUM(DATA_mgconst, 10), DATANUM(DATA_mgconst, 11), DATANUM(DATA_mgconst, 12), DATANUM(DATA_mgconst, 13), DATANUM(DATA_mgconst, 10), DATANUM(DATA_mgconst, 10), DATANUM(DATA_m562, 111) };

/* 171 insns: create an HP gauge (frame + 10 cells; kind picks the frame: player charNo or 15 = Bowser) */
void fn_1_23ECC(M562_SPRITE *sprite, s32 kind, s16 value, s32 side, M562_WORK *work)
{
    HUSPRGRPID grpId;
    HUSPRID sprId;
    s32 i;

    memset(sprite, 0, sizeof(M562_SPRITE));
    sprite->unk00 = work;
    sprite->unk2C = value;
    sprite->unk2E = sprite->unk2C * 5;
    sprite->unk04 = 0;
    sprite->unk08 = 0;
    sprite->unk10 = HuSprAnimDataRead(lbl_1_data_BF0[kind]);
    sprite->unk28 = HuSprAnimDataRead(DATANUM(DATA_m562, 0x6E));
    sprite->unk0C = grpId = HuSprGrpCreate(11);
    if (side == 0) {
        HuSprGrpPosSet(grpId, 32.0f, 112.0f);
    } else {
        HuSprGrpPosSet(grpId, 544.0f, 112.0f);
    }
    sprite->unk0E = sprId = HuSprCreate(sprite->unk10, 10, 0);
    HuSprGrpMemberSet(grpId, 0, sprId);
    HuSprPosSet(grpId, 0, 0.0f, 0.0f);
    HuSprScaleSet(grpId, 0, 0.0f, 0.0f);
    for (i = 0; i < 10; i++) {
        sprite->unk14[i] = sprId = HuSprCreate(sprite->unk28, 10, 0);
        HuSprGrpMemberSet(grpId, i + 1, sprId);
        HuSprPosSet(grpId, i + 1, 0.0f, 32.0f + 24.0f * i);
        HuSprBankSet(grpId, i + 1, 0);
        HuSprScaleSet(grpId, i + 1, 0.0f, 0.0f);
        if (i >= value) {
            HuSprScaleSet(grpId, i + 1, 0.0f, 0.0f);
        }
    }
}

/* 29 insns */
void fn_1_24178(M562_SPRITE *sprite)
{
    s32 i;

    for (i = 0; i < 10; i++) {
        HuSprKill(sprite->unk14[i]);
    }
    HuSprKill(sprite->unk0E);
    HuSprGrpKill(sprite->unk0C);
    memset(sprite, 0, sizeof(M562_SPRITE));
}

/* 160 insns: per frame; the displayed value (x5) steps towards unk2C every other frame */
void fn_1_241EC(M562_SPRITE *sprite)
{
    M562_WORK *work = sprite->unk00;
    s32 i;

    sprite->unk2C = (sprite->unk2C > 10) ? 10 : ((sprite->unk2C < 0) ? 0 : sprite->unk2C);
    if (sprite->unk04 && !sprite->unk08) {
        HuSprScaleSet(sprite->unk0C, 0, 1.0f, 1.0f);
        sprite->unk08 = 1;
    } else if (!sprite->unk04 && sprite->unk08) {
        for (i = 0; i < 11; i++) {
            HuSprScaleSet(sprite->unk0C, i, 0.0f, 0.0f);
        }
        sprite->unk08 = 0;
    }
    if (sprite->unk08) {
        for (i = 0; i < 10; i++) {
            if (i >= (sprite->unk2E + 4) / 5) {
                HuSprScaleSet(sprite->unk0C, i + 1, 0.0f, 0.0f);
            } else {
                HuSprScaleSet(sprite->unk0C, i + 1, 0.5f, 0.5f);
                if (i < sprite->unk2E / 5) {
                    HuSprBankSet(sprite->unk0C, i + 1, 0);
                } else {
                    HuSprBankSet(sprite->unk0C, i + 1, 4 - sprite->unk2E % 5);
                }
            }
        }
        if (work->unk0008 % 2 == 0) {
            if (sprite->unk2E < sprite->unk2C * 5) {
                sprite->unk2E++;
            } else if (sprite->unk2E > sprite->unk2C * 5) {
                sprite->unk2E--;
            }
        }
    }
}
