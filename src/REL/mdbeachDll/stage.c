/*
 * mdbeachdll stage.c -- sprites and models of the Beach Volley / Ice Hockey setup. Twins:
 * mdomakedll/stage.c and mdminidll/stage.c (MdSpriteCreate, the getters, FontBGFilter, the layer
 * hooks, MdToueiMdlInit); MdModelCreate has mdmini/mdparty's shape with this overlay's models.
 */

#include "REL/mdbeachDll.h"
#include "datadir_enum.h"

/* mdbeach.bin has no datanum header: file numbers are taken from the reference .data/asm */
static unsigned int SpriteAnimFile[MDSPR_ANIM_MAX] = {
    DATANUM(DATA_mdbeach, 76), /* win_frame */
    DATANUM(DATA_mdbeach, 77), /* win_bg */
    DATANUM(DATA_mdbeach, 74), /* cursor */
    DATANUM(DATA_mdbeach, 75), /* cursor_glow */
    DATANUM(DATA_mdbeach, 89), /* player number */
    DATANUM(DATA_mdbeach, 90), /* COM level */
    DATANUM(DATA_mdbeach, 91), /* finger texture (MdToueiMdlInit) */
    DATANUM(DATA_mdbeach, 78),
    DATANUM(DATA_mdbeach, 79),
    DATANUM(DATA_mdbeach, 80),
    DATANUM(DATA_mdbeach, 81),
    DATANUM(DATA_mdbeach, 82),
    DATANUM(DATA_mdbeach, 87),
    DATANUM(DATA_mdbeach, 88),
    DATANUM(DATA_mdbeach, 83),
    DATANUM(DATA_mdbeach, 84),
    DATANUM(DATA_mdbeach, 85),
    DATANUM(DATA_mdbeach, 86)
};

static MDSPR_INFO SpriteInfo[MDSPR_MAX] = {
    { MDSPR_ANIM_WIN_FRAME, 5, { 0, -28 }, { 72, 1 }, 1.0f },
    { MDSPR_ANIM_WIN_FRAME, 5, { 0, 32 }, { 72, 1 }, 1.0f },

    { MDSPR_ANIM_WIN_BG, 6, { 0, 0 }, { 1, 8 }, 0.6f },

    { MDSPR_ANIM_CURSOR, 14, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 14, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_CURSOR, 8, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 8, { -64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 8, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 8, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_CURSOR, 7, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 7, { -64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 7, { 64, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_CURSOR, 7, { -64, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_PLAYERNO, 9, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_PLAYERNO, 9, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_PLAYERNO, 9, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_PLAYERNO, 9, { 0, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_COMDIF, 10, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_COMDIF, 10, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_COMDIF, 10, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_COMDIF, 10, { 0, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_9, 16, { 0, 0 }, { 0.9f, 0.93333334f }, 1.0f },
    { MDSPR_ANIM_10, 16, { 0, 0 }, { 0.9f, 0.93333334f }, 1.0f },
    { MDSPR_ANIM_11, 15, { 0, 0 }, { 72, 60 }, 0.0f },

    { MDSPR_ANIM_12, 11, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_13, 11, { 0, 0 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_14, 13, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_16, 12, { 3, 10 }, { 1, 1 }, 1.0f },

    { MDSPR_ANIM_15, 13, { 0, 0 }, { 1, 1 }, 1.0f },
    { MDSPR_ANIM_17, 12, { -3, -3 }, { 1, 1 }, 1.0f },
};

static MDSPR_GRP_INFO SpriteGrpInfo[MDSPR_GRP_MAX] = {
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_WIN, 288, 408),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_CURSOR_LR, 288, 240),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_CURSOR_UDLR, 288, 240),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_PLAYERNO, 0, 0),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_COMDIF, 0, 0),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_5, 288, 240),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_6, 0, 0),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_7, 0, 0),
    MDSPR_GRP_INFO_DEFINE(MDSPR_GRP_8, 0, 0),
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
        sprite->animP[i] = HuSprAnimRead(HuDataSelHeapReadNum(SpriteAnimFile[i], HU_MEMNUM_OVL, HEAP_MODEL));

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
    grpId = sprite->grpId[MDSPR_GRP_5];
    HuSprGrpDrawNoSet(grpId, 127);
    grpId = sprite->grpId[MDSPR_GRP_7];
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_7, MDSPR_27), 0);
    grpId = sprite->grpId[MDSPR_GRP_8];
    HuSprBankSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_8, MDSPR_29), 0);
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_COMDIF, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_5, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_6, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_7, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_8, FALSE);
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

static unsigned int CharMdlTbl[MDMODEL_CHR_NUM] = {
    DATANUM(DATA_mdbeach, 0),
    DATANUM(DATA_mdbeach, 4),
    DATANUM(DATA_mdbeach, 8),
    DATANUM(DATA_mdbeach, 12),
    DATANUM(DATA_mdbeach, 16),
    DATANUM(DATA_mdbeach, 20),
    DATANUM(DATA_mdbeach, 24),
    DATANUM(DATA_mdbeach, 28),
    DATANUM(DATA_mdbeach, 32),
    DATANUM(DATA_mdbeach, 36)
};

static unsigned int CharVolleyMdlTbl[MDMODEL_CHR_NUM] = {
    DATANUM(DATA_mdbeach, 40),
    DATANUM(DATA_mdbeach, 41),
    DATANUM(DATA_mdbeach, 42),
    DATANUM(DATA_mdbeach, 43),
    DATANUM(DATA_mdbeach, 44),
    DATANUM(DATA_mdbeach, 45),
    DATANUM(DATA_mdbeach, 46),
    DATANUM(DATA_mdbeach, 47),
    DATANUM(DATA_mdbeach, 48),
    DATANUM(DATA_mdbeach, 49)
};

static unsigned int CharHockeyMdlTbl[MDMODEL_CHR_NUM] = {
    DATANUM(DATA_mdbeach, 50),
    DATANUM(DATA_mdbeach, 51),
    DATANUM(DATA_mdbeach, 52),
    DATANUM(DATA_mdbeach, 53),
    DATANUM(DATA_mdbeach, 54),
    DATANUM(DATA_mdbeach, 55),
    DATANUM(DATA_mdbeach, 56),
    DATANUM(DATA_mdbeach, 57),
    DATANUM(DATA_mdbeach, 58),
    DATANUM(DATA_mdbeach, 59)
};

static unsigned int CapManFileTbl[2] = {
    DATANUM(DATA_mdbeach, 67), /* player capsule */
    DATANUM(DATA_mdbeach, 68) /* COM capsule */
};

static unsigned int VsFileTbl[3] = {
    DATANUM(DATA_mdbeach, 69), /* VS_VOLLEY */
    DATANUM(DATA_mdbeach, 70), /* VS_HOCKEY */
    0
};

static unsigned int BallMdlTbl[3] = {
    DATANUM(DATA_mdbeach, 62), /* BALL_NORMAL */
    DATANUM(DATA_mdbeach, 63), /* BALL_BOMB */
    DATANUM(DATA_mdbeach, 64) /* BALL_DICE */
};

static unsigned int StarMotFileTbl[3] = {
    DATANUM(DATA_mdbeach, 71),
    DATANUM(DATA_mdbeach, 72),
    DATANUM(DATA_mdbeach, 73)
};

/* three motions per character, on MDMODEL_MARIO+(i/3); the first is set */
static unsigned int CharMotTbl[MDMODEL_CHR_NUM*3] = {
    DATANUM(DATA_mdbeach, 1), DATANUM(DATA_mdbeach, 2), DATANUM(DATA_mdbeach, 3),
    DATANUM(DATA_mdbeach, 5), DATANUM(DATA_mdbeach, 6), DATANUM(DATA_mdbeach, 7),
    DATANUM(DATA_mdbeach, 9), DATANUM(DATA_mdbeach, 10), DATANUM(DATA_mdbeach, 11),
    DATANUM(DATA_mdbeach, 13), DATANUM(DATA_mdbeach, 14), DATANUM(DATA_mdbeach, 15),
    DATANUM(DATA_mdbeach, 17), DATANUM(DATA_mdbeach, 18), DATANUM(DATA_mdbeach, 19),
    DATANUM(DATA_mdbeach, 21), DATANUM(DATA_mdbeach, 22), DATANUM(DATA_mdbeach, 23),
    DATANUM(DATA_mdbeach, 25), DATANUM(DATA_mdbeach, 26), DATANUM(DATA_mdbeach, 27),
    DATANUM(DATA_mdbeach, 29), DATANUM(DATA_mdbeach, 30), DATANUM(DATA_mdbeach, 31),
    DATANUM(DATA_mdbeach, 33), DATANUM(DATA_mdbeach, 34), DATANUM(DATA_mdbeach, 35),
    DATANUM(DATA_mdbeach, 37), DATANUM(DATA_mdbeach, 38), DATANUM(DATA_mdbeach, 39)
};

static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx);
static void Layer2Hook(s16 layerNo);
static void Layer1Hook(s16 layerNo);

void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera)
{
    int i;
    for(i=0; i<MDMODEL_CHR_NUM; i++) {
        model->mdlId[MDMODEL_MARIO+i] = Hu3DModelCreateData(CharMdlTbl[i]);
        Hu3DModelDispOff(model->mdlId[MDMODEL_MARIO+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_MARIO+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_MARIO+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_MARIO+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_MARIO+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_MARIO+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_MARIO+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_MARIO+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_MARIO+i], 1.0f);
    }
    for(i=0; i<MDMODEL_CHR_NUM; i++) {
        model->mdlId[MDMODEL_MARIO_VOLLEY+i] = Hu3DModelCreateData(CharVolleyMdlTbl[i]);
        Hu3DModelDispOff(model->mdlId[MDMODEL_MARIO_VOLLEY+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_MARIO_VOLLEY+i], 0);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_MARIO_VOLLEY+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_MARIO_VOLLEY+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_MARIO_VOLLEY+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_MARIO_VOLLEY+i], 1, 1, 1);
    }
    for(i=0; i<MDMODEL_CHR_NUM; i++) {
        model->mdlId[MDMODEL_MARIO_HOCKEY+i] = Hu3DModelCreateData(CharHockeyMdlTbl[i]);
        Hu3DModelDispOff(model->mdlId[MDMODEL_MARIO_HOCKEY+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_MARIO_HOCKEY+i], 0);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_MARIO_HOCKEY+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_MARIO_HOCKEY+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_MARIO_HOCKEY+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_MARIO_HOCKEY+i], 1, 1, 1);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_CAP_MAN_1P+i] = Hu3DModelCreateData(CapManFileTbl[0]);
        } else {
            model->mdlId[MDMODEL_CAP_MAN_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_CAP_MAN_1P]);
        }
        Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_MAN_1P+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CAP_MAN_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_CAP_MAN_1P+i], 1.0f);
        if(i == 0) {
            model->mdlId[MDMODEL_CAP_COM_1P+i] = Hu3DModelCreateData(CapManFileTbl[1]);
        } else {
            model->mdlId[MDMODEL_CAP_COM_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_CAP_COM_1P]);
        }
        Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_COM_1P+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_CAP_COM_1P+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_CAP_COM_1P+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_CAP_COM_1P+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_CAP_COM_1P+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_CAP_COM_1P+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CAP_COM_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CAP_COM_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_CAP_COM_1P+i], 1.0f);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_FINGER_1P+i] = Hu3DModelCreateData(DATANUM(DATA_mdbeach, 61));
        } else {
            model->mdlId[MDMODEL_FINGER_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_FINGER_1P]);
        }
        Hu3DModelDispOff(model->mdlId[MDMODEL_FINGER_1P+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_FINGER_1P+i], 4);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_FINGER_1P+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_FINGER_1P+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_FINGER_1P+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_FINGER_1P+i], 1, 1, 1);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_FINGER_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_FINGER_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_FINGER_1P+i], 1.0f);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_FLASH_1P+i] = Hu3DModelCreateData(DATANUM(DATA_mdbeach, 65));
        } else {
            model->mdlId[MDMODEL_FLASH_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_FLASH_1P]);
        }
        Hu3DModelDispOff(model->mdlId[MDMODEL_FLASH_1P+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_FLASH_1P+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_FLASH_1P+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_FLASH_1P+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_FLASH_1P+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_FLASH_1P+i], 0.8f, 0.8f, 0.8f);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_FLASH_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_FLASH_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_FLASH_1P+i], 1.0f);
    }
    for(i=0; i<2; i++) {
        model->mdlId[MDMODEL_VS_VOLLEY+i] = Hu3DModelCreateData(VsFileTbl[i]);
        Hu3DModelDispOn(model->mdlId[MDMODEL_VS_VOLLEY+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_VS_VOLLEY+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_VS_VOLLEY+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_VS_VOLLEY+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_VS_VOLLEY+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_VS_VOLLEY+i], 1, 1, 1);
    }
    for(i=0; i<3; i++) {
        model->mdlId[MDMODEL_BALL_NORMAL+i] = Hu3DModelCreateData(BallMdlTbl[i]);
        Hu3DModelDispOn(model->mdlId[MDMODEL_BALL_NORMAL+i]);
        Hu3DModelLayerSet(model->mdlId[MDMODEL_BALL_NORMAL+i], 1);
        Hu3DModelCameraSet(model->mdlId[MDMODEL_BALL_NORMAL+i], camera->camera[MDCAMERA_BG].bit);
        Hu3DModelPosSet(model->mdlId[MDMODEL_BALL_NORMAL+i], 0, 0, 0);
        Hu3DModelRotSet(model->mdlId[MDMODEL_BALL_NORMAL+i], 0, 0, 0);
        Hu3DModelScaleSet(model->mdlId[MDMODEL_BALL_NORMAL+i], 1, 1, 1);
    }
    model->mdlId[MDMODEL_STAR] = Hu3DModelCreateData(DATANUM(DATA_mdbeach, 60));
    Hu3DModelDispOff(model->mdlId[MDMODEL_STAR]);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_STAR], 0);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_STAR], camera->camera[MDCAMERA_MAIN].bit);
    Hu3DModelPosSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelRotSet(model->mdlId[MDMODEL_STAR], 0, 0, 0);
    Hu3DModelScaleSet(model->mdlId[MDMODEL_STAR], 1, 1, 1);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_STAR], 1.0f);
    model->mdlId[MDMODEL_FONTBGFILTER] = Hu3DHookFuncCreate(FontBGFilter);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_FONTBGFILTER], 7);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_FONTBGFILTER], camera->camera[MDCAMERA_MAIN].bit);
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    for(i=0; i<3; i++) {
        model->motId[MDMODEL_MOT_STAR_IDLE+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_STAR], StarMotFileTbl[i]);
    }
    Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE]);
    for(i=0; i<MDMODEL_CHR_NUM*3; i++) {
        model->motId[MDMODEL_MOT_CHR+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_MARIO+(i/3)], CharMotTbl[i]);
        if((i%3) == 0) {
            Hu3DMotionSet(model->mdlId[MDMODEL_MARIO+(i/3)], model->motId[MDMODEL_MOT_CHR+i]);
        }
    }
    for(i=0; i<MDMODEL_MAX; i++) {
        HU3DMODEL *modelP = &Hu3DData[model->mdlId[i]];
        model->posP[i] = &modelP->pos;
        model->rotP[i] = &modelP->rot;
        model->scaleP[i] = &modelP->scale;
    }
    Hu3DLayerHookSet(1, Layer2Hook);
    Hu3DLayerHookSet(2, Layer2Hook);
    Hu3DLayerHookSet(4, Layer2Hook);
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
    if(Hu3DCameraNo == MDCAMERA_BG) {
        Hu3DZClear();
    }
}

static void Layer1Hook(s16 layerNo)
{
    if(Hu3DCameraNo == MDCAMERA_MAIN) {
        Hu3DZClear();
    }
}

static s16 ToueiAnmNoTbl[4] = {
    MDSPR_ANIM_FINGER,
    MDSPR_ANIM_FINGER,
    MDSPR_ANIM_FINGER,
    MDSPR_ANIM_FINGER
};

static s16 ToueiMdlNoTbl[4] = {
    MDMODEL_FINGER_1P,
    MDMODEL_FINGER_2P,
    MDMODEL_FINGER_3P,
    MDMODEL_FINGER_4P
};

static char *ToueiTexNameTbl[4] = {
    "dummy",
    "dummy",
    "dummy",
    "dummy"
};

void MdToueiMdlInit(void)
{
    MDSPRITE_WORK *sprite = sysP->sprite;
    MDMODEL_WORK *model = sysP->model;
    int i; //r30

    for(i=0; i<4; i++) {
        HU3DANIMID animId = Hu3DAnimCreate(sprite->animP[ToueiAnmNoTbl[i]], model->mdlId[ToueiMdlNoTbl[i]], ToueiTexNameTbl[i]);
        model->animId[MDMODEL_ANIM_FINGER_1P+i] = animId;
        Hu3DAnimSpeedSet(animId, 1);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_ANIMON);
        Hu3DAnimAttrSet(animId, HU3D_ANIM_ATTR_LOOP);
    }
    Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_1P], 0);
    Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_2P], 0);
    Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_3P], 0);
    Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_4P], 0);
}
