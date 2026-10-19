#ifndef _STORYMODE_EFFECT_H
#define _STORYMODE_EFFECT_H

/*
 * storymodedll's particle helpers (fn_1_A2B8..fn_1_A764), #included at the top of opening.c as
 * mdparty/mdstory include their effect.c: CW inlines them into every caller (no reference call
 * site is a `bl`) and emits the out-of-line copies last in .text. Their HU3DPARMANPARAM tables
 * are opening.c's first .data (0x38-0x177). Unlike mdstory's, frandmod is prototyped here.
 */

#include "game/hu3d.h"
#include "game/memory.h"
#include "game/frand.h"

/* 0x38 */ HU3DPARMANPARAM lbl_1_data_38 = { 30, 0, 50.0f, 10.0f, 180.0f, { 0.0f, -0.05f, 0.0f }, 20.0f, 0.8f, 10.0f, 1.0f, 2, { { 255, 255, 255, 255 }, { 255, 255, 64, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 128, 128, 0 }, { 255, 64, 32, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x88 */ HU3DPARMANPARAM lbl_1_data_88 = { 40, 0, 50.0f, 0.0f, 90.0f, { 0.0f, -0.05f, 0.0f }, 35.0f, 0.88f, 25.0f, 0.99f, 1, { { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 255, 128, 128, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0xD8 */ HU3DPARMANPARAM lbl_1_data_D8 = { 30, 0, 30.0f, 60.0f, 180.0f, { 0.0f, 0.0f, 0.0f }, 0.2f, 1.0f, 100.0f, 1.0f, 2, { { 255, 255, 255, 32 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }, { { 64, 32, 32, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } } };
/* 0x128 */ HU3DPARMANPARAM lbl_1_data_128 = { 50, 0, 2.0f, 30.0f, 180.0f, { 0.0f, -0.2f, 0.0f }, 1.0f, 0.8f, 30.0f, 0.95f, 3, { { 128, 192, 255, 255 }, { 255, 255, 64, 255 }, { 255, 96, 128, 255 }, { 0, 0, 0, 0 } }, { { 128, 192, 255, 0 }, { 255, 64, 32, 0 }, { 128, 16, 16, 0 }, { 0, 0, 0, 0 } } };

STORY_PARWORK *fn_1_A2B8(ANIMDATA *anim, s16 layer, s16 camBit)
{
    STORY_PARWORK *work;
    HU3DPARMANID parManId;
    float rotZ;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(STORY_PARWORK), HU_MEMNUM_OVL);
    parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_38);
    work->parManId[0] = parManId;
    Hu3DParManAttrSet(parManId, 0x65);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
    Hu3DParManRotSet(parManId, 90.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), layer);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), camBit);
    parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_88);
    work->parManId[1] = parManId;
    Hu3DParManAttrSet(parManId, 0x163);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
    rotZ = frandmod(80) - 40;
    Hu3DParManRotSet(parManId, frandmod(40) + 70, 0.0f, rotZ);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), layer);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), camBit);
    parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_D8);
    work->parManId[2] = parManId;
    Hu3DParManAttrSet(parManId, 0x21);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
    Hu3DParManRotSet(parManId, 0.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), layer);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), camBit);
    return work;
}

/* 55 insns */
void fn_1_A4F4(STORY_PARWORK *work, HuVecF *pos)
{
    Hu3DParManPosSet(work->parManId[0], pos->x, pos->y, pos->z);
    Hu3DParManTimeLimitSet(work->parManId[0], 2);
    Hu3DParManAttrReset(work->parManId[0], 1);
    Hu3DParManPosSet(work->parManId[1], pos->x, pos->y, pos->z);
    Hu3DParManTimeLimitSet(work->parManId[1], 2);
    Hu3DParManAttrReset(work->parManId[1], 1);
    Hu3DParManPosSet(work->parManId[2], pos->x, pos->y, pos->z);
    Hu3DParManTimeLimitSet(work->parManId[2], 5);
    Hu3DParManAttrReset(work->parManId[2], 1);
}

/* 19 insns */
void fn_1_A5D0(STORY_PARWORK *work)
{
    Hu3DParManKill(work->parManId[0]);
    Hu3DParManKill(work->parManId[1]);
    Hu3DParManKill(work->parManId[2]);
}

/* 55 insns */
STORY_PARWORK *fn_1_A61C(ANIMDATA *anim, s16 layer, s16 camBit)
{
    STORY_PARWORK *work;
    HU3DPARMANID parManId;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(STORY_PARWORK), HU_MEMNUM_OVL);
    parManId = Hu3DParManCreate(anim, 100, &lbl_1_data_128);
    work->parManId[0] = parManId;
    Hu3DParManAttrSet(parManId, 0x65);
    Hu3DParticleBlendModeSet(Hu3DParManModelIDGet(parManId), 1);
    Hu3DParManRotSet(parManId, 90.0f, 0.0f, 0.0f);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), layer);
    Hu3DModelCameraSet(Hu3DParManModelIDGet(parManId), camBit);
    return work;
}

/* 27 insns */
void fn_1_A6F8(STORY_PARWORK *work, HuVecF *pos)
{
    Hu3DParManPosSet(work->parManId[0], pos->x, pos->y, pos->z);
    Hu3DParManTimeLimitSet(work->parManId[0], 2);
    Hu3DParManAttrReset(work->parManId[0], 1);
}

/* 13 insns */
void fn_1_A764(STORY_PARWORK *work)
{
    Hu3DParManKill(work->parManId[0]);
}

#endif
