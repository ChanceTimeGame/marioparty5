/*
 * rescarddll stage.c -- sprites and models of the Card Party results. Twins: mdpartydll/stage.c
 * (MdModelCreate shape, RingMatHook, getters, FontBGFilter), mdminidll/stage.c (MdSpriteCreate),
 * mdoptiondll/stage.c (ambient list).
 */

#include "REL/rescardDll.h"

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

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_228 = 0.0f; /* 0x228 */
static const float lbl_1_rodata_22C = 1.0f; /* 0x22C */
static const float lbl_1_rodata_230 = 0.6f; /* 0x230 */
/* 0x234 lbl_1_rodata_234 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x235 lbl_1_rodata_235 (0x3): 0xFF, 0xFF, 0x40 -- an aggregate initialiser, write it as a local */
/* 0x238 lbl_1_rodata_238 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x239 lbl_1_rodata_239 (0x3): 0x00, 0x00, 0x80 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_23C = 8.0f; /* 0x23C */
static const float lbl_1_rodata_240 = 640.0f; /* 0x240 */
static const float lbl_1_rodata_244 = 480.0f; /* 0x244 */
static const float lbl_1_rodata_248 = -16777215.0f; /* 0x248 */

static void RingMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);
static void FontBGFilter(HU3DMODEL *modelP, Mtx *mtx);
static void Layer1Clear(s16 layerNo);
static void Layer2Clear(s16 layerNo);

/* --- functions (reference order), .data placed before its first user --- */
/* 0xFA8 */ static u32 SpriteAnimFile[MDSPR_ANIM_MAX] = { DATANUM(DATA_rescard, 51), DATANUM(DATA_rescard, 52), DATANUM(DATA_rescard, 53), DATANUM(DATA_rescard, 54), DATANUM(DATA_rescard, 55) };
/* 0xFBC */ static MDSPR_INFO SpriteInfo[MDSPR_MAX] = {
    { 1, 2, { 0, 0 }, { 1, 8 }, 0.6f },
    { 0, 1, { 0, -28 }, { 72, 1 }, 1.0f },
    { 0, 1, { 0, 32 }, { 72, 1 }, 1.0f },

    { 2, 3, { 64, 0 }, { 1, 1 }, 1.0f },
    { 2, 3, { -64, 0 }, { 1, 1 }, 1.0f },

    { 3, 4, { -20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { -20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { -20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { -20, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 0, 0 }, { 1, 1 }, 1.0f },
    { 3, 4, { 20, 0 }, { 1, 1 }, 1.0f },

    { 3, 5, { 0, 0 }, { 2, 2 }, 1.0f },
};
/* 0x116C */ static MDSPR_GRP_INFO SpriteGrpInfo[MDSPR_GRP_MAX] = {
    { 0, 2, 288, 408 },
    { 3, 4, 288, 240 },
    { 5, 7, 288, 240 },
    { 8, 10, 288, 240 },
    { 11, 13, 288, 240 },
    { 14, 16, 288, 240 },
    { 17, 17, 288, 240 },
};

/* 268 insns */
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
            HuSprAttrReset(grpId, j, HUSPR_ATTR_DISPOFF);
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
    HuSprBankSet(grpId, 0, 3);
    HuSprBankSet(grpId, 1, 2);
    grpId = sprite->grpId[MDSPR_GRP_NUM_0];
    HuSprBankSet(grpId, 0, 10);
    HuSprBankSet(grpId, 1, 1);
    HuSprBankSet(grpId, 2, 2);
    HuSprGrpDrawNoSet(grpId, 64);
    grpId = sprite->grpId[MDSPR_GRP_NUM_0+1];
    HuSprBankSet(grpId, 0, 10);
    HuSprBankSet(grpId, 1, 1);
    HuSprBankSet(grpId, 2, 2);
    HuSprGrpDrawNoSet(grpId, 64);
    grpId = sprite->grpId[MDSPR_GRP_NUM_0+2];
    HuSprBankSet(grpId, 0, 10);
    HuSprBankSet(grpId, 1, 1);
    HuSprBankSet(grpId, 2, 2);
    HuSprGrpDrawNoSet(grpId, 64);
    grpId = sprite->grpId[MDSPR_GRP_NUM_0+3];
    HuSprBankSet(grpId, 0, 10);
    HuSprBankSet(grpId, 1, 1);
    HuSprBankSet(grpId, 2, 2);
    HuSprGrpDrawNoSet(grpId, 64);
    grpId = sprite->grpId[MDSPR_GRP_6];
    HuSprBankSet(grpId, 0, 0);
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NUM_0, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NUM_0+1, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NUM_0+2, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NUM_0+3, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_6, FALSE);
    sprite->unk48 = 0.6f;
    HuSprExecLayerCameraSet(64, sysP->camera->camera[MDCAMERA_FG].bit, 3);
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
            HuSprAttrSet(grpId, i, HUSPR_ATTR_DISPOFF);
        } else if(dispF == TRUE) {
            HuSprAttrReset(grpId, i, HUSPR_ATTR_DISPOFF);
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

/* 116 insns */
static void RingMatHook(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXColor color = { 0x00, 0xFF, 0xFF, 0x40 };
    Mtx trans;
    Mtx scale;
    Mtx texMtx;
    GXSetColorUpdate(TRUE);
    GXSetAlphaUpdate(TRUE);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_DSTALPHA, GX_LO_INVCOPY);
    GXSetNumTevStages(1);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0);
    MTXTrans(trans, 0, 0, 0);
    MTXScale(scale, 1, 1, 1);
    MTXConcat(scale, trans, texMtx);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_A0, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
}

/* 0x11C0 */ static u32 StageFileTbl[6] = { DATANUM(DATA_rescard, 1), DATANUM(DATA_rescard, 2), DATANUM(DATA_rescard, 3), DATANUM(DATA_rescard, 4), DATANUM(DATA_rescard, 5), DATANUM(DATA_rescard, 6) };
/* 0x11D8 */ static u32 PinFileTbl[21] = { DATANUM(DATA_rescard, 7), DATANUM(DATA_rescard, 8), DATANUM(DATA_rescard, 9), DATANUM(DATA_rescard, 10), DATANUM(DATA_rescard, 11), DATANUM(DATA_rescard, 12), DATANUM(DATA_rescard, 13), DATANUM(DATA_rescard, 14), DATANUM(DATA_rescard, 15), DATANUM(DATA_rescard, 16), DATANUM(DATA_rescard, 17), DATANUM(DATA_rescard, 18), DATANUM(DATA_rescard, 19), DATANUM(DATA_rescard, 20), DATANUM(DATA_rescard, 21), DATANUM(DATA_rescard, 22), DATANUM(DATA_rescard, 23), DATANUM(DATA_rescard, 24), DATANUM(DATA_rescard, 25), DATANUM(DATA_rescard, 26), DATANUM(DATA_rescard, 27) };
/* 0x122C */ static u32 CurFileTbl[7] = { DATANUM(DATA_rescard, 28), DATANUM(DATA_rescard, 29), DATANUM(DATA_rescard, 30), DATANUM(DATA_rescard, 31), DATANUM(DATA_rescard, 32), DATANUM(DATA_rescard, 33), DATANUM(DATA_rescard, 34) };
/* 0x1248 */ static u32 PopFileTbl[2] = { DATANUM(DATA_rescard, 36), DATANUM(DATA_rescard, 37) };
/* 0x1250 */ static u32 StarMotFileTbl[2] = { DATANUM(DATA_rescard, 46), DATANUM(DATA_rescard, 47) };
/* 0x1258 */ static u32 PinMotFileTbl[3] = { DATANUM(DATA_rescard, 48), DATANUM(DATA_rescard, 49), DATANUM(DATA_rescard, 50) };

#define MDL_SETUP(no, layer, cameraNo) \
    Hu3DModelLayerSet(model->mdlId[no], layer); \
    Hu3DModelCameraSet(model->mdlId[no], camera->camera[cameraNo].bit); \
    Hu3DModelPosSet(model->mdlId[no], 0, 0, 0); \
    Hu3DModelRotSet(model->mdlId[no], 0, 0, 0); \
    Hu3DModelScaleSet(model->mdlId[no], 1, 1, 1)

/* 1576 insns */
void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera)
{
    int i;
    HU3DMODEL *modelP;
    int playerInfo[4][2];
    for(i=0; i<4; i++) {
        playerInfo[i][0] = sysP->score->player[i].charNo;
        playerInfo[i][1] = sysP->score->player[i].pedestalF;
    }
    model->ambScale = 1.0f;
    for(i=0; i<16; i++) {
        model->ambMdlId[i] = -1;
    }
    model->mdlId[MDMODEL_STAR] = Hu3DModelCreateData(DATANUM(DATA_rescard, 0));
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_ATTR_DISPOFF);
    MDL_SETUP(MDMODEL_STAR, 6, MDCAMERA_FG);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_STAR], 1.0f);
    for(i=0; i<6; i++) {
        model->mdlId[MDMODEL_STAGE_BASE+i] = Hu3DModelCreateData(StageFileTbl[i]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_STAGE_BASE+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_STAGE_BASE+i, 0, MDCAMERA_MAIN);
        MdModelAddAmb(model, model->mdlId[MDMODEL_STAGE_BASE+i]);
    }
    for(i=0; i<4; i++) {
        model->mdlId[MDMODEL_PIN_1P+i] = Hu3DModelCreateData(PinFileTbl[(playerInfo[i][0]*3)+playerInfo[i][1]]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_PIN_1P+i, 1, MDCAMERA_MAIN);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_PIN_1P+i], 1.0f);
        MdModelAddAmb(model, model->mdlId[MDMODEL_PIN_1P+i]);
    }
    for(i=0; i<4; i++) {
        model->mdlId[MDMODEL_CUR_1P+i] = Hu3DModelCreateData(CurFileTbl[playerInfo[i][0]]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CUR_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_CUR_1P+i, 5, MDCAMERA_FG);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_PEDESTAL_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 35));
        } else {
            model->mdlId[MDMODEL_PEDESTAL_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_PEDESTAL_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_PEDESTAL_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_PEDESTAL_1P+i, 1, MDCAMERA_MAIN);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PEDESTAL_1P+i], HU3D_MOTATTR_PAUSE);
        MdModelAddAmb(model, model->mdlId[MDMODEL_PEDESTAL_1P+i]);
    }
    for(i=0; i<2; i++) {
        model->mdlId[MDMODEL_POP_STAR+i] = Hu3DModelCreateData(PopFileTbl[i]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_POP_STAR+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_POP_STAR+i, 6, MDCAMERA_FG);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_POP_STAR+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_POP_STAR+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_POP_STAR+i], 1.0f);
    }
    for(i=0; i<22; i++) {
        model->mdlId[MDMODEL_WIN_STAR_00+i] = Hu3DModelLink(model->mdlId[MDMODEL_POP_STAR]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_WIN_STAR_00+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_WIN_STAR_00+i, 1, MDCAMERA_MAIN);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_WIN_STAR_00+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_WIN_STAR_00+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_WIN_STAR_00+i], 1.0f);
    }
    for(i=0; i<11; i++) {
        model->mdlId[MDMODEL_WIN_ZTAR_00+i] = Hu3DModelLink(model->mdlId[MDMODEL_POP_ZTAR]);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_WIN_ZTAR_00+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_WIN_ZTAR_00+i, 1, MDCAMERA_MAIN);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_WIN_ZTAR_00+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_WIN_ZTAR_00+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_WIN_ZTAR_00+i], 1.0f);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_CARD_STAR_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 38));
        } else {
            model->mdlId[MDMODEL_CARD_STAR_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_CARD_STAR_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CARD_STAR_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_CARD_STAR_1P+i, 5, MDCAMERA_MAIN);
        if(i == 0) {
            model->mdlId[MDMODEL_CARD_ZTAR_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 39));
        } else {
            model->mdlId[MDMODEL_CARD_ZTAR_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_CARD_ZTAR_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CARD_ZTAR_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_CARD_ZTAR_1P+i, 5, MDCAMERA_MAIN);
        if(i == 0) {
            model->mdlId[MDMODEL_CARD_SZTAR_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 40));
        } else {
            model->mdlId[MDMODEL_CARD_SZTAR_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_CARD_SZTAR_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_CARD_SZTAR_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_CARD_SZTAR_1P+i, 4, MDCAMERA_FG);
    }
    for(i=0; i<8; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_DRAW_STAR+i] = Hu3DModelLink(model->mdlId[MDMODEL_CARD_STAR_1P]);
        } else {
            model->mdlId[MDMODEL_DRAW_STAR+i] = Hu3DModelLink(model->mdlId[MDMODEL_CARD_ZTAR_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_DRAW_STAR+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_DRAW_STAR+i, 5, MDCAMERA_FG);
    }
    model->mdlId[MDMODEL_EFF_STARFLASH] = Hu3DModelCreateData(DATANUM(DATA_rescard, 41));
    Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_ATTR_DISPOFF);
    MDL_SETUP(MDMODEL_EFF_STARFLASH, 6, MDCAMERA_FG);
    Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_EFF_STARFLASH], 1.0f);
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 42));
        } else {
            model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_EFF_DICEFLASH_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_EFF_DICEFLASH_1P+i, 5, MDCAMERA_FG);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], 1.0f);
    }
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 43));
        } else {
            model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i] = Hu3DModelLink(model->mdlId[MDMODEL_EFF_CARDFLASH_1P]);
        }
        Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_EFF_CARDFLASH_1P+i, 0, MDCAMERA_MAIN);
        Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i], HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i], 1.0f);
    }
    model->mdlId[MDMODEL_RING] = Hu3DModelCreateData(DATANUM(DATA_rescard, 44));
    Hu3DModelAttrSet(model->mdlId[MDMODEL_RING], HU3D_ATTR_DISPOFF);
    MDL_SETUP(MDMODEL_RING, 1, MDCAMERA_MAIN);
    Hu3DModelMatHookSet(model->mdlId[MDMODEL_RING], RingMatHook);
    for(i=0; i<4; i++) {
        if(i == 0) {
            model->mdlId[MDMODEL_SPOT_0+i] = Hu3DModelCreateData(DATANUM(DATA_rescard, 45));
        } else {
            model->mdlId[MDMODEL_SPOT_0+i] = Hu3DModelLink(model->mdlId[MDMODEL_SPOT_0]);
        }
        Hu3DModelAttrSet(model->mdlId[MDMODEL_SPOT_0+i], HU3D_ATTR_DISPOFF);
        MDL_SETUP(MDMODEL_SPOT_0+i, 2, MDCAMERA_MAIN);
    }
    model->mdlId[MDMODEL_FONTBGFILTER] = Hu3DHookFuncCreate(FontBGFilter);
    Hu3DModelLayerSet(model->mdlId[MDMODEL_FONTBGFILTER], 7);
    Hu3DModelCameraSet(model->mdlId[MDMODEL_FONTBGFILTER], camera->camera[MDCAMERA_FG].bit);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_FONTBGFILTER], HU3D_ATTR_DISPOFF);
    for(i=0; i<2; i++) {
        model->motId[MDMODEL_MOT_STAR_0+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_STAR], StarMotFileTbl[i]);
    }
    Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_0]);
    for(i=0; i<4; i++) {
        model->motId[MDMODEL_MOT_PIN_0_1P+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_PIN_1P+i], PinMotFileTbl[0]);
        model->motId[MDMODEL_MOT_PIN_1_1P+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_PIN_1P+i], PinMotFileTbl[1]);
        model->motId[MDMODEL_MOT_PIN_2_1P+i] = Hu3DJointMotionData(model->mdlId[MDMODEL_PIN_1P+i], PinMotFileTbl[2]);
        Hu3DMotionSet(model->mdlId[MDMODEL_PIN_1P+i], model->motId[MDMODEL_MOT_PIN_1_1P+i]);
    }
    for(i=0; i<MDMODEL_MAX; i++) {
        modelP = &Hu3DData[model->mdlId[i]];
        model->posP[i] = &modelP->pos;
        model->rotP[i] = &modelP->rot;
        model->scaleP[i] = &modelP->scale;
    }
    Hu3DLayerHookSet(1, Layer1Clear);
    Hu3DLayerHookSet(2, Layer1Clear);
    Hu3DLayerHookSet(4, Layer2Clear);
    Hu3DLayerHookSet(5, Layer2Clear);
    Hu3DLayerHookSet(6, Layer2Clear);
    MdModelUpdateAmb(model);
}

#undef MDL_SETUP

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
        GXSetTevColor(GX_TEVREG0, color);
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

/* 13 insns */
static void Layer1Clear(s16 layerNo)
{
    if(Hu3DCameraNo == MDCAMERA_MAIN) {
        Hu3DZClear();
    }
}

/* 13 insns */
static void Layer2Clear(s16 layerNo)
{
    if(Hu3DCameraNo == MDCAMERA_FG) {
        Hu3DZClear();
    }
}

/* 19 insns */
void MdModelAddAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->ambMdlId[i] == -1) {
            model->ambMdlId[i] = mdlId;
            break;
        }
    }
}

/* 22 insns */
void MdModelRemoveAmb(MDMODEL_WORK *model, HU3DMODELID mdlId)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->ambMdlId[i] == mdlId) {
            model->ambMdlId[i] = -1;
            break;
        }
    }
}

/* 29 insns */
void MdModelUpdateAmb(MDMODEL_WORK *model)
{
    int i;
    for(i=0; i<16; i++) {
        if(model->ambMdlId[i] != -1) {
            Hu3DModelAmbSet(model->ambMdlId[i], model->ambScale, model->ambScale, model->ambScale);
        }
    }
}
