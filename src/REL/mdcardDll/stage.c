/*
 * mdcarddll stage.c -- sprites and models of the Card Party setup hub (fork S, 2026-10-01).
 * Twins: mdomakedll/stage.c (MdSpriteCreate), mdpartydll/stage.c (getters, FontBGFilter),
 * mdoptiondll/stage.c (layer hook, ambient list), mdstorydll/stage.c (MdModelCreate shape,
 * MdToueiMdlInit).
 */

#include "REL/mdcardDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/disp.h"
#include "math.h"
#include "datadir_enum.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_270 = 0.0f; /* 0x270 */
static const float lbl_1_rodata_274 = 1.0f; /* 0x274 */
static const float lbl_1_rodata_278 = 0.6f; /* 0x278 */
/* 0x27C lbl_1_rodata_27C (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x27D lbl_1_rodata_27D (0x3): 0x00, 0x00, 0x80 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_280 = 8.0f; /* 0x280 */
static const float lbl_1_rodata_284 = 640.0f; /* 0x284 */
static const float lbl_1_rodata_288 = 480.0f; /* 0x288 */
static const float lbl_1_rodata_28C = -16777215.0f; /* 0x28C */

static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx);
static void Layer1Hook(s16 layerNo);

/* --- functions (reference order), .data placed before its first user --- */
/* 0xA40 */ static unsigned int SpriteAnimFile[MDSPR_ANIM_MAX] = {
    DATANUM(DATA_mdcard, 36),
    DATANUM(DATA_mdcard, 37),
    DATANUM(DATA_mdcard, 38),
    DATANUM(DATA_mdcard, 39),
    DATANUM(DATA_mdcard, 40),
    DATANUM(DATA_mdcard, 41)
};

/* 0xA58 */ static MDSPR_INFO SpriteInfo[MDSPR_MAX] = {
    { 1, 2, { 0, 0 }, { 1, 8 }, 0.6f },
    { 0, 1, { 0, -28 }, { 72, 1 }, 1.0f },
    { 0, 1, { 0, 32 }, { 72, 1 }, 1.0f },

    { 2, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 2, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 3, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 3, { 0, 0 }, { 1, 1 }, 1.0f },

    { 5, 5, { 0, 0 }, { 1, 1 }, 1.0f },
    { 5, 5, { 0, 0 }, { 1, 1 }, 1.0f },
    { 5, 5, { 0, 0 }, { 1, 1 }, 1.0f },
    { 5, 5, { 0, 0 }, { 1, 1 }, 1.0f },

    { 2, 6, { 64, 0 }, { 1, 1 }, 1.0f },
    { 2, 6, { -64, 0 }, { 1, 1 }, 1.0f },
};

/* 0xB90 */ static MDSPR_GRP_INFO SpriteGrpInfo[MDSPR_GRP_MAX] = {
    { 0, 2, 288, 408 },
    { 3, 6, 288, 240 },
    { 7, 10, 288, 240 },
    { 11, 12, 288, 240 },
};

/* 229 insns */
void MdSpriteCreate(MDSPRITE_WORK *sprite)
{
    HUSPRGRPID grpId;
    MDSPR_INFO *sprInfo;
    int i;
    MDSPR_GRP_INFO *grpInfo;
    int j;
    int grpNum;
    for(i=0; i<MDSPR_ANIM_MAX; i++) {
        sprite->animP[i] = HuSprAnimRead(HuDataReadNum(SpriteAnimFile[i], HU_MEMNUM_OVL));
    }
    for(i=0; i<MDSPR_MAX; i++) {
        sprInfo = &SpriteInfo[i];
        sprite->sprId[i] = HuSprCreate(sprite->animP[sprInfo->animNo], 0, 0);
    }
    for(grpInfo=&SpriteGrpInfo[0], i=0; i<MDSPR_GRP_MAX; i++, grpInfo++) {
        grpNum = grpInfo->end-grpInfo->start+1;
        grpId = HuSprGrpCreate(grpNum);
        sprite->grpId[i] = grpId;
        for(sprInfo=&SpriteInfo[grpInfo->start], j=0; j<grpNum; j++, sprInfo++) {
            HuSprGrpMemberSet(grpId, j, sprite->sprId[grpInfo->start+j]);
            HuSprPriSet(grpId, j, sprInfo->pri);
            HuSprDispOn(grpId, j);
            HuSprPosSet(grpId, j, sprInfo->pos.x, sprInfo->pos.y);
            HuSprZRotSet(grpId, j, 0);
            HuSprScaleSet(grpId, j, sprInfo->scale.x, sprInfo->scale.y);
            HuSprColorSet(grpId, j, 255, 255, 255);
            HuSprTPLvlSet(grpId, j, sprInfo->tpLvl);
        }
        HuSprGrpPosSet(grpId, grpInfo->posX, grpInfo->posY);
        HuSprGrpCenterSet(grpId, 0, 0);
        HuSprGrpZRotSet(grpId, 0);
        HuSprGrpScaleSet(grpId, 1, 1);
        HuSprGrpDrawNoSet(grpId, 0);
        HuSprGrpScissorSet(grpId, 0, 0, 640, 480);
    }
    grpId = sprite->grpId[1];
    HuSprBankSet(grpId, 0, 3);
    HuSprBankSet(grpId, 1, 2);
    HuSprBankSet(grpId, 2, 3);
    HuSprBankSet(grpId, 3, 2);
    HuSprAttrSet(grpId, 2, HUSPR_ATTR_ADDCOL);
    HuSprAttrSet(grpId, 3, HUSPR_ATTR_ADDCOL);
    grpId = sprite->grpId[2];
    HuSprBankSet(grpId, 0, 0);
    HuSprBankSet(grpId, 1, 1);
    HuSprBankSet(grpId, 2, 2);
    HuSprBankSet(grpId, 3, 3);
    grpId = sprite->grpId[3];
    HuSprBankSet(grpId, 0, 3);
    HuSprBankSet(grpId, 1, 2);
    MdSpriteDispSet(sprite, 0, FALSE);
    MdSpriteDispSet(sprite, 1, FALSE);
    MdSpriteDispSet(sprite, 2, FALSE);
    MdSpriteDispSet(sprite, 3, FALSE);
    sprite->unk3C = 0.6f;
    HuSprExecLayerCameraSet(64, sysP->camera->camera[0].bit, 1);
}

/* 43 insns */
void MdSpriteDispSet(MDSPRITE_WORK *sprite, int grpNo, BOOL dispF)
{
    int i;
    MDSPR_GRP_INFO *grpInfo;
    HUSPRGRPID grpId;
    int grpNum;
    grpInfo = &SpriteGrpInfo[grpNo];
    grpId = sprite->grpId[grpNo];
    grpNum = grpInfo->end-grpInfo->start+1;
    for(i=0; i<grpNum; i++) {
        if(dispF == FALSE) {
            HuSprDispOff(grpId, i);
        } else if(dispF == TRUE) {
            HuSprDispOn(grpId, i);
        }
    }
}

/* 13 insns */
HuVec2f *MdSpriteGrpPosGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->pos;
}

/* 13 insns */
HuVec2f *MdSpriteGrpScaleGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->scale;
}

/* 22 insns */
HuVec2f *MdSpritePosGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->pos;
}

/* 22 insns */
HuVec2f *MdSpriteScaleGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->scale;
}

/* 22 insns */
float *MdSpriteAlphaGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->a;
}

/* 0xBC0 */ static unsigned int PinFileTbl[21] = {
    DATANUM(DATA_mdcard, 3), DATANUM(DATA_mdcard, 4), DATANUM(DATA_mdcard, 5),
    DATANUM(DATA_mdcard, 6), DATANUM(DATA_mdcard, 7), DATANUM(DATA_mdcard, 8),
    DATANUM(DATA_mdcard, 9), DATANUM(DATA_mdcard, 10), DATANUM(DATA_mdcard, 11),
    DATANUM(DATA_mdcard, 12), DATANUM(DATA_mdcard, 13), DATANUM(DATA_mdcard, 14),
    DATANUM(DATA_mdcard, 15), DATANUM(DATA_mdcard, 16), DATANUM(DATA_mdcard, 17),
    DATANUM(DATA_mdcard, 18), DATANUM(DATA_mdcard, 19), DATANUM(DATA_mdcard, 20),
    DATANUM(DATA_mdcard, 21), DATANUM(DATA_mdcard, 22), DATANUM(DATA_mdcard, 23)
};
/* 0xC14 */ static unsigned int ManFileTbl[2] = { DATANUM(DATA_mdcard, 30), DATANUM(DATA_mdcard, 31) };
/* 0xC1C */ static unsigned int CardFileTbl[5] = {
    DATANUM(DATA_mdcard, 25), DATANUM(DATA_mdcard, 26), DATANUM(DATA_mdcard, 27),
    DATANUM(DATA_mdcard, 28), DATANUM(DATA_mdcard, 29)
};
/* 0xC30 */ static unsigned int StarMotFileTbl[2] = { DATANUM(DATA_mdcard, 32), DATANUM(DATA_mdcard, 33) };

/* 744 insns */
void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera)
{
    int i;
    model->unk27C = 1.0f;
    for(i=0; i<16; i++) {
        model->unk280[i] = -1;
    }
    model->mdlId[MDMODEL_STAR] = Hu3DModelCreateData(DATANUM(DATA_mdcard, 0));
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAR]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_STAR], 2);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_STAR], camera->camera[1].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_STAR], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_STAR], 1.0f);
    model->mdlId[MDMODEL_STAGE] = Hu3DModelCreateData(DATANUM(DATA_mdcard, 2));
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_STAGE], 0);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_STAGE], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_STAGE], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_STAGE], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_STAGE], 1, 1, 1);
    Hu3DModelShadowMapObjSet(model->mdlId[MDMODEL_STAGE], "stage-cloth");
    model->mdlId[MDMODEL_BOX] = Hu3DModelCreateData(DATANUM(DATA_mdcard, 1));
    Hu3DModelDispOn(model->mdlId[MDMODEL_BOX]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_BOX], 0);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_BOX], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_BOX], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_BOX], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_BOX], 1, 1, 1);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_BOX], 1.0f);
    Hu3DModelShadowSet(model->mdlId[MDMODEL_BOX]);
    for(i=0; i<21; i++) {
        model->mdlId[MDMODEL_PIN+i] = Hu3DModelCreateData(PinFileTbl[i]);
        Hu3DModelDispOn(model->mdlId[MDMODEL_PIN+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_PIN+i], 0);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_PIN+i], camera->camera[0].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_PIN+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_PIN+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_PIN+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_PIN+i], 1.0f);
        Hu3DModelShadowSet(model->mdlId[MDMODEL_PIN+i]);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_MAN+i] = Hu3DModelCreateData(ManFileTbl[0]);
        } else {
            model->mdlId[MDMODEL_MAN+i] = Hu3DModelLink(model->mdlId[MDMODEL_MAN]);
        }
        Hu3DModelDispOn(model->mdlId[MDMODEL_MAN+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_MAN+i], 2);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_MAN+i], camera->camera[1].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_MAN+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_MAN+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_MAN+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_MAN+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_MAN+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_MAN+i], 1.0f);
        if(i == 0) {
            model->mdlId[MDMODEL_COM+i] = Hu3DModelCreateData(ManFileTbl[1]);
        } else {
            model->mdlId[MDMODEL_COM+i] = Hu3DModelLink(model->mdlId[MDMODEL_COM]);
        }
        Hu3DModelDispOn(model->mdlId[MDMODEL_COM+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_COM+i], 2);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_COM+i], camera->camera[1].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_COM+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_COM+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_COM+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_COM+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_COM+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_COM+i], 1.0f);
    }
    model->mdlId[MDMODEL_FINGER] = Hu3DModelCreateData(DATANUM(DATA_mdcard, 24));
    Hu3DModelDispOn(model->mdlId[MDMODEL_FINGER]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_FINGER], 2);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_FINGER], camera->camera[0].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_FINGER], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_FINGER], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_FINGER], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_FINGER], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_FINGER], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_FINGER], 1.0f);
    for(i=0; i<5; i++) {
        model->mdlId[MDMODEL_CARD+i] = Hu3DModelCreateData(CardFileTbl[i]);
        Hu3DModelDispOn(model->mdlId[MDMODEL_CARD+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_CARD+i], 2);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_CARD+i], camera->camera[1].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_CARD+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_CARD+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_CARD+i], 1, 1, 1);
    }
    model->mdlId[MDMODEL_FONTBGFILTER] = Hu3DHookFuncCreate(FontBGFilter);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_FONTBGFILTER], 6);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_FONTBGFILTER], camera->camera[0].bit);
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    for(i=0; i<2; i++) {
        model->motId[MDMODEL_MOT_STAR+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_STAR], StarMotFileTbl[i]);
    }
    Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR]);
    for(i=0; i<21; i++) {
        model->motId[MDMODEL_MOT_PIN_A+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_PIN+i], DATANUM(DATA_mdcard, 34));
        model->motId[MDMODEL_MOT_PIN_B+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_PIN+i], DATANUM(DATA_mdcard, 35));
        Hu3DMotionSet(model->mdlId[MDMODEL_PIN+i], model->motId[MDMODEL_MOT_PIN_B+i]);
    }
    for(i=0; i<MDMODEL_MAX; i++) {
        HU3DMODEL *modelP = &Hu3DData[model->mdlId[i]];
        model->posP[i] = &modelP->pos;
        model->rotP[i] = &modelP->rot;
        model->scaleP[i] = &modelP->scale;
    }
    Hu3DLayerHookSet(1+HU3D_LAYER_HOOK_POST, Layer1Hook);
    MdModelUpdateAmb(model);
}

/* 240 insns */
static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx)
{
    MDDEBUGFONT_WORK *debugFont = sysP->debugFont;
    GXColor color = { 0, 0, 0, 128 };
    s16 width = 0;
    if(debugFont->printF == TRUE) {
        Mtx44 proj;
        width = debugFont->maxLen*(int)(8.0f*debugFont->size);
        GXSetViewport(0, 0, HU_FB_WIDTH, HU_FB_HEIGHT, 0, 1);
        MTXOrtho(proj, 0, 480, 0, 640, 0, -16777215);
        GXSetProjection(proj, GX_ORTHOGRAPHIC);
        MTXIdentity(*mtx);
        GXLoadPosMtxImm(*mtx, GX_PNMTX0);
        GXSetColorUpdate(TRUE);
        GXSetAlphaUpdate(FALSE);
        GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        GXSetNumChans(1);
        GXSetNumTexGens(0);
        GXSetNumTevStages(1);
        GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_NONE, GX_AF_SPEC);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR_NULL);
        GXSetTevColor(GX_COLOR1, color);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_C0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_A0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S16, 0);
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3s16(debugFont->posX, debugFont->posY+debugFont->ofsY, 0);
        GXPosition3s16(debugFont->posX+width, debugFont->posY+debugFont->ofsY, 0);
        GXPosition3s16(debugFont->posX+width, debugFont->posY+debugFont->rowOfsY, 0);
        GXPosition3s16(debugFont->posX, debugFont->posY+debugFont->rowOfsY, 0);
        GXEnd();
    }
}

/* 8 insns */
static void Layer1Hook(s16 layerNo)
{
    Hu3DZClear();
}

/* 19 insns */
void MdModelAddAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unk280[i] == -1) {
            model->unk280[i] = mdlId;
            break;
        }
    }
}

/* 22 insns */
void MdModelRemoveAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unk280[i] == mdlId) {
            model->unk280[i] = -1;
            break;
        }
    }
}

/* 29 insns */
void MdModelUpdateAmb(MDMODEL_WORK *model)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->unk280[i] != -1) {
            Hu3DModelAmbSet(model->unk280[i], model->unk27C, model->unk27C, model->unk27C);
        }
    }
}

/* 0xC44 */ static s16 ToueiAnmNoTbl[1] = { 4 };
/* 0xC46 */ static s16 ToueiMdlNoTbl[1] = { MDMODEL_FINGER };
/* 0xC50 */ static char *ToueiTexNameTbl[1] = {
    "dummy"
};

/* 66 insns */
void MdToueiMdlInit(void)
{
    MDSPRITE_WORK *sprite = sysP->sprite;
    MDMODEL_WORK *model = sysP->model;
    int i; //r30

    for(i=0; i<1; i++) {
        HU3DANIMID animId = Hu3DAnimCreate(sprite->animP[ToueiAnmNoTbl[i]], model->mdlId[ToueiMdlNoTbl[i]], ToueiTexNameTbl[i]);
        model->animId[i] = animId;
        Hu3DAnimSpeedSet(animId, 1);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_ANIMON);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_LOOP);
    }
    Hu3DAnmNoSet(model->animId[0], 0);
}
