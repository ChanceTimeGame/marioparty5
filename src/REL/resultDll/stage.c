/*
 * resultDll stage.c -- PORTED (hand-written, not a generated skeleton).
 * Reference: build/mp5-asm/resultDll/asm/REL/resultDll/stage.s.
 * Shape follows Mario Party 4's resultDll datalist.c and MP5 instdll's stage.c;
 * the MP5 table (STAGE_MODEL, resultDll.h) adds a layer and a camera bit and gives
 * positions in screen space (Hu3D2Dto3D on HU3D_CAM1).
 */

#include "REL/resultDll.h"

#include "game/hsfex.h"

/* Retail calls the esp* functions UNPROTOTYPED: espEntry's int result is extsh'd into
 * an s16, every s16 id is re-extended at each call (default promotion) and espAttrSet's
 * attr arrives without the u16 clrlwi a prototype adds. Mario Party 4's resultDll
 * datalist.c keeps the header out of the GameCube build the same way. */
#ifndef __MWERKS__
#include "game/esprite.h"
#endif

void StageModelCreate(STAGE_MODEL *modelTbl)
{
    STAGE_MODEL *modelP;
    s16 i;
    s16 clearI;
    HU3DMODELID modelId;
    void *data;
    HuVecF pos;

    modelP = modelTbl;
    for(clearI = 0; clearI < STAGE_MDL_MAX; clearI++) {
        StageMdlId[clearI] = StageMotId[clearI] = HU3D_MODELID_NONE;
    }
    for(i = 0; modelP->dataNum != HU_DATANUM_NONE; modelP++, i++) {
        if(modelP->type == STAGE_MODEL_TYPE_MODEL) {
            data = HuDataSelHeapReadNum(modelP->dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
            modelId = Hu3DModelCreate(data);
            StageMdlId[i] = modelId;
            Hu3DModelCameraSet(modelId, modelP->cameraBit);
            Hu3D2Dto3D(&modelP->pos, HU3D_CAM1, &pos);
            Hu3DModelAttrSet(modelId, modelP->attr);
            Hu3DModelPosSetV(modelId, &pos);
            Hu3DModelRotSetV(modelId, &modelP->rot);
            Hu3DModelScaleSetV(modelId, &modelP->scale);
            Hu3DModelLayerSet(modelId, modelP->layer);
        } else if(modelP->type == STAGE_MODEL_TYPE_MOT) {
            data = HuDataSelHeapReadNum(modelP->dataNum, HU_MEMNUM_OVL, HEAP_MODEL);
            StageMotId[i] = Hu3DJointMotion(StageMdlId[modelP->motMdl], data);
        }
    }
    modelP = modelTbl;
    for(i = 0; modelP->dataNum != HU_DATANUM_NONE; modelP++, i++) {
        if(modelP->type == STAGE_MODEL_TYPE_LINK) {
            modelId = Hu3DModelLink(StageMdlId[modelP->linkMdl]);
            StageMdlId[i] = modelId;
            Hu3DModelCameraSet(modelId, modelP->cameraBit);
            Hu3D2Dto3D(&modelP->pos, HU3D_CAM1, &pos);
            Hu3DModelAttrSet(modelId, modelP->attr);
            Hu3DModelPosSetV(modelId, &pos);
            Hu3DModelRotSetV(modelId, &modelP->rot);
            Hu3DModelScaleSetV(modelId, &modelP->scale);
            Hu3DModelLayerSet(modelId, modelP->layer);
        }
    }
}

void StageSpriteCreate(STAGE_SPRITE *spriteTbl)
{
    STAGE_SPRITE *spriteP;
    s16 sprId;
    s16 clearI;
    s16 i;

    spriteP = spriteTbl;
    for(clearI = 0; clearI < STAGE_SPR_MAX; clearI++) {
        StageSprId[clearI] = -1;
    }
    for(i = 0; spriteP->dataNum; i++, spriteP++) {
        sprId = espEntry(spriteP->dataNum, 100, 0);
        StageSprId[i] = sprId;
        espPosSet(sprId, spriteP->x, spriteP->y);
        espColorSet(sprId, spriteP->color.r, spriteP->color.g, spriteP->color.b);
        espTPLvlSet(sprId, spriteP->color.a / 255.0f);
        espPriSet(sprId, spriteP->prio);
        espAttrSet(sprId, spriteP->attr);
        espDrawNoSet(sprId, 64);
        HuSprExecLayerCameraSet(64, HU3D_CAM1, 1);
    }
}

void StageSpriteKill(void)
{
    s16 i;
    for(i = 0; i < STAGE_SPR_MAX; i++) {
        if(StageSprId[i] != -1) {
            espKill(StageSprId[i]);
        }
    }
}
