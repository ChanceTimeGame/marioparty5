/*
 * mdomakedll stage.c -- sprites and models of the Bonus Mode hub. Twins: mdstorydll/stage.c
 * (MdSpriteCreate, the getters, MdToueiMdlInit) and mdseldll/stage.c (MdModelCreate's shape,
 * FontBGFilter, the layer hooks).
 */

#include "REL/mdomakeDll.h"
#include "datadir_enum.h"

/* mdomake.bin has no datanum header: file numbers are taken from the reference .data/asm */
static unsigned int SpriteAnimFile[MDSPR_ANIM_MAX] = {
    DATANUM(DATA_mdomake, 10), /* win_frame */
    DATANUM(DATA_mdomake, 11), /* win_bg */
    DATANUM(DATA_mdomake, 8), /* cursor */
    DATANUM(DATA_mdomake, 9), /* cursor_glow */
    DATANUM(DATA_mdomake, 12),
    DATANUM(DATA_mdomake, 13),
    DATANUM(DATA_mdomake, 14),
    DATANUM(DATA_mdomake, 15),
    DATANUM(DATA_mdomake, 16)
};

static MDSPR_INFO SpriteInfo[MDSPR_MAX] = {
    { MDSPR_ANIM_WIN_FRAME, 2, { 0, -28 }, { 72, 1 }, 1.0f },
    { MDSPR_ANIM_WIN_FRAME, 2, { 0, 32 }, { 72, 1 }, 1.0f },

    { MDSPR_ANIM_WIN_BG, 3, { 0, 0 }, { 1, 8 }, 0.6f },

    { MDSPR_ANIM_CURSOR, 6, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 6, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_CURSOR, 5, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 5, { -64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 5, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 5, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_CURSOR, 4, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 4, { -64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 4, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 4, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_NAME, 7, { 0, 0 }, { 1, 1 }, 1.0f },
};

static MDSPR_GRP_INFO SpriteGrpInfo[MDSPR_GRP_MAX] = {
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_WIN, 288, 408),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_CURSOR_LR, 288, 240),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_CURSOR_UDLR, 288, 240),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_NAME, 288, 240),
};

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
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_LR];
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_R), 3);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_L), 2);
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_UDLR];
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R), 3);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L), 2);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_U), 0);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_D), 1);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), 3);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), 2);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_U), 0);
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_D), 1);
    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), HUSPR_ATTR_ADDCOL);
    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), HUSPR_ATTR_ADDCOL);
    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_U), HUSPR_ATTR_ADDCOL);
    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_D), HUSPR_ATTR_ADDCOL);
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NAME, FALSE);
}

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

HuVec2f *MdSpriteGrpPosGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->pos;
}

HuVec2f *MdSpriteGrpScaleGet(MDSPRITE_WORK *sprite, int grpNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    return &grp->scale;
}

HuVec2f *MdSpritePosGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->pos;
}

HuVec2f *MdSpriteScaleGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->scale;
}

float *MdSpriteAlphaGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo)
{
    HUSPRGRP *grp = &HuSprGrpData[sprite->grpId[grpNo]];
    HUSPRITE *spr = &HuSprData[grp->sprId[memberNo]];
    return &spr->a;
}

static unsigned int CapFileTbl[MDMODEL_CAP_NUM] = {
    DATANUM(DATA_mdomake, 2),
    DATANUM(DATA_mdomake, 3),
    DATANUM(DATA_mdomake, 4)
};

static unsigned int StarMotFileTbl[MDMODEL_MOT_MAX] = {
    DATANUM(DATA_mdomake, 5),
    DATANUM(DATA_mdomake, 6),
    DATANUM(DATA_mdomake, 7)
};

static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx);
static void Layer2Hook(s16 layerNo);
static void Layer1Hook(s16 layerNo);

void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera)
{
    int i;
    model->mdlId[MDMODEL_STAGE] = Hu3DModelCreateData(DATANUM(DATA_mdomake, 1));
    Hu3DModelDispOff(model->mdlId[MDMODEL_STAGE]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_STAGE], 0);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_STAGE], camera->camera[MDCAMERA_BG].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_STAGE], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_STAGE], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_STAGE], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAGE], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAGE], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_STAGE], 1.0f);
    model->mdlId[MDMODEL_STAR] = Hu3DModelCreateData(DATANUM(DATA_mdomake, 0));
    Hu3DModelDispOff(model->mdlId[MDMODEL_STAR]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_STAR], 1);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_STAR], camera->camera[MDCAMERA_MAIN].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_STAR], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_STAR], 1.0f);
    for(i=0; i<MDMODEL_CAP_NUM; i++) {
        model->mdlId[MDMODEL_CAP_00+i] = Hu3DModelCreateData(CapFileTbl[i]);
        Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_00+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_CAP_00+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_CAP_00+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_CAP_00+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_CAP_00+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_CAP_00+i], 1, 1, 1);
    }
    model->mdlId[MDMODEL_FONTBGFILTER] = Hu3DHookFuncCreate(FontBGFilter);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_FONTBGFILTER], 7);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_FONTBGFILTER], camera->camera[MDCAMERA_MAIN].bit);
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    for(i=0; i<MDMODEL_MOT_MAX; i++) {
        model->motId[MDMODEL_MOT_STAR_IDLE+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_STAR], StarMotFileTbl[i]);
    }
    Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE]);
    for(i=0; i<MDMODEL_MAX; i++) {
        HU3DMODEL *modelP = &Hu3DData[model->mdlId[i]];
        model->posP[i] = &modelP->pos;
        model->rotP[i] = &modelP->rot;
        model->scaleP[i] = &modelP->scale;
    }
    Hu3DLayerHookSet(1, Layer2Hook);
    Hu3DLayerHookSet(0, Layer1Hook);
}

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

static void Layer2Hook(s16 layerNo)
{
    if(Hu3DCameraNo == 0) {
        Hu3DZClear();
    }
}

static void Layer1Hook(s16 layerNo)
{
    if(Hu3DCameraNo == 1) {
        Hu3DZClear();
    }
}

static s16 ToueiAnmNoTbl[MDMODEL_CAP_NUM] = {
    MDSPR_ANIM_TOUEI_00,
    MDSPR_ANIM_TOUEI_01,
    MDSPR_ANIM_TOUEI_02
};

static s16 ToueiMdlNoTbl[MDMODEL_CAP_NUM] = {
    MDMODEL_CAP_00,
    MDMODEL_CAP_01,
    MDMODEL_CAP_02
};

static char *ToueiTexNameTbl[MDMODEL_CAP_NUM] = {
    "S3TC_mg_movie",
    "S3TC_mg_movie",
    "S3TC_mg_movie"
};

void MdToueiMdlInit(void)
{
    MDSPRITE_WORK *sprite = sysP->sprite;
    MDMODEL_WORK *model = sysP->model;
    int i; //r30

    for(i=0; i<MDMODEL_CAP_NUM; i++) {
        HU3DANIMID animId = Hu3DAnimCreate(sprite->animP[ToueiAnmNoTbl[i]], model->mdlId[ToueiMdlNoTbl[i]], ToueiTexNameTbl[i]);
        model->animId[i] = animId;
        Hu3DAnimSpeedSet(animId, 1);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_ANIMON);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_LOOP);
    }
    Hu3DAnmNoSet(model->animId[0], 0);
    Hu3DAnmNoSet(model->animId[1], 0);
    Hu3DAnmNoSet(model->animId[2], 0);
}
