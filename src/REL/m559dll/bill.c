/*
 * m559dll billboard block, #included by m559.c right after REL/m563dll/math.c.
 * CodeWarrior emits functions from included files after the including file's
 * own, in include order; this keeps the reference order (helpers, then this
 * block) with the game code ahead of both. Types and prototypes are in m559.c.
 */

#include "game/object.h"

extern ANIMDATA *lbl_1_bss_0;

/* asm 7130-7357, 216 insns. This overlay's billboard part update (M559BILLFUNC). */
static void fn_1_6678(HU3DMODEL *modelP, M559_BILL *work, Mtx mtx)
{
    M559_BILLPART *part = work->part;
    GXColor *color = work->color;
    float ratio;
    float alpha;
    float alphaClamp;
    s16 i;

    work->liveCnt = 0;
    for(i=0; i<work->maxCnt; i++, part++, color++) {
        if(part->no < 0) {
            continue;
        }
        part->time += part->timeAdd;
        if(part->timeMax < part->time) {
            part->no = -1;
            continue;
        }
        work->liveCnt++;
        if(NULL != work->posSrc) {
            part->basePos = *work->posSrc;
        }
        if(NULL != work->angleSrc) {
            part->angle = *work->angleSrc;
        }
        part->pos.x = part->basePos.x+(part->time*sin((M_PI*(part->angle+part->angleOfs))/180.0));
        part->pos.y += 0.03f*(part->posYTarget-part->pos.y);
        part->pos.z = part->basePos.z+(part->time*cos((M_PI*(part->angle+part->angleOfs))/180.0));
        ratio = part->time/part->timeMax;
        alpha = 128.0*cos((M_PI*(90.0f*ratio))/180.0);
        if(255.0f < alpha) {
            alphaClamp = 255.0f;
        } else {
            alphaClamp = alpha;
        }
        color->a = alphaClamp;
        part->cellNo = work->cellNum*ratio;
        if(work->cellNum <= part->cellNo) {
            part->cellNo = work->cellNum-1;
        }
        ratio *= 2.0f;
        if(1.0f < ratio) {
            ratio = 1.0f;
        }
        part->scale = 1.5*sin((M_PI*(5.0f+(100.0f*ratio)))/180.0);
    }
}

/* asm 7360-7392, 31 insns. = M560MtxTranspose. */
static void fn_1_69D8(Mtx src, Mtx dst)
{
    dst[0][0] = src[0][0];
    dst[1][0] = src[0][1];
    dst[2][0] = src[0][2];
    dst[0][1] = src[1][0];
    dst[1][1] = src[1][1];
    dst[2][1] = src[1][2];
    dst[0][2] = src[2][0];
    dst[1][2] = src[2][1];
    dst[2][2] = src[2][2];
    dst[0][3] = 0.0f;
    dst[1][3] = 0.0f;
    dst[2][3] = 0.0f;
}

/* asm 7395-7421, 23 insns. = M560VecScaleN. */
static void fn_1_6A54(HuVecF *src, HuVecF *dst, float scale, s16 count)
{
    s16 i;

    for(i=0; i<count; i++, src++, dst++) {
        dst->x = src->x*scale;
        dst->y = src->y*scale;
        dst->z = src->z*scale;
    }
}

/* asm 7424-7466, 41 insns. = M560TexCoordSet. */
static void fn_1_6AB0(HuVec2f *st, HuVec2f *cellTbl, s16 cell, float width, float height)
{
    st[0].x = cellTbl[cell].x;
    st[0].y = cellTbl[cell].y;
    st[1].x = cellTbl[cell].x+width;
    st[1].y = cellTbl[cell].y;
    st[2].x = cellTbl[cell].x+width;
    st[2].y = cellTbl[cell].y+height;
    st[3].x = cellTbl[cell].x;
    st[3].y = cellTbl[cell].y+height;
}

/* asm 7469-7959, 466 insns. = M560BillHook. */
static void fn_1_6B54(HU3DMODEL *modelP, Mtx *mtx)
{
    M559_BILL *work = modelP->hookData;
    M559_BILLPART *part;
    HuVecF *vtx;
    HuVec2f *st;
    Mtx mtxT;
    ROMtx mtxRo;
    Mtx mtxRot;
    Mtx mtxRotWork;
    HuVecF quad[4];
    HuVecF corner[4];
    HuVecF out[4];
    M559BILLFUNC func;
    s16 fmt;
    s16 i;

    if(work->killF && work->liveCnt == 0) {
        return;
    }
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    fmt = work->anim->bmp->dataFmt & ANIM_BMP_FMTMASK;
    if(fmt == ANIM_BMP_I4 || fmt == ANIM_BMP_I8) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_RASC, GX_CC_ZERO);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if(modelP->attr & HU3D_ATTR_ZWRITE_OFF) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    } else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
    HuSprTexLoad(work->anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    switch(work->unk6A) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;
        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
            break;
        case 2:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCLR, GX_LO_NOOP);
            break;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, work->vtx, sizeof(HuVecF));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, work->color, sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, work->st, sizeof(HuVec2f));
    fn_1_69D8(*mtx, mtxT);
    PSMTXReorder(mtxT, mtxRo);
    if(!omPauseChk()) {
        if(work->func) {
            func = work->func;
            func(modelP, work, *mtx);
        }
    }
    part = work->part;
    vtx = work->vtx;
    st = work->st;
    PSMTXROMultVecArray(mtxRo, work->quad, quad, 4);
    for(i=0; i<work->maxCnt; i++, part++, st+=4) {
        if(part->no < 0) {
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            continue;
        }
        if(0.0f == part->zRot) {
            fn_1_6A54(quad, corner, part->scale, 4);
            PSVECAdd(&corner[0], &part->pos, vtx++);
            PSVECAdd(&corner[1], &part->pos, vtx++);
            PSVECAdd(&corner[2], &part->pos, vtx++);
            PSVECAdd(&corner[3], &part->pos, vtx++);
        } else {
            fn_1_6A54(work->quad, corner, part->scale, 4);
            PSMTXRotRad(mtxRot, 'Z', 0.017453292f*part->zRot);
            PSMTXConcat(mtxT, mtxRot, mtxRotWork);
            PSMTXMultVecArray(mtxRotWork, corner, out, 4);
            PSVECAdd(&out[0], &part->pos, vtx++);
            PSVECAdd(&out[1], &part->pos, vtx++);
            PSVECAdd(&out[2], &part->pos, vtx++);
            PSVECAdd(&out[3], &part->pos, vtx++);
        }
        if(part->cellNo != -1) {
            fn_1_6AB0(st, work->cellTbl, part->cellNo, work->cellSizeX, work->cellSizeY);
        }
    }
    DCFlushRangeNoSync(work->vtx, (work->maxCnt*sizeof(HuVecF))*4);
    DCFlushRangeNoSync(work->st, (work->maxCnt*sizeof(HuVec2f))*4);
    GXCallDisplayList(work->dlBuf, work->dlSize);
}

/* asm 7962-8016, 51 insns. = M560CellTblMake. */
static void fn_1_729C(HuVec2f *st, s16 count, s16 cellX, float w, float h)
{
    s16 i;
    s16 cx;
    s16 cy;

    for(i=0; i<count; i++, st++) {
        cx = i%cellX;
        cy = i/cellX;
        st->x = cx*w;
        st->y = cy*h;
    }
}

/* asm 8019-8441, 406 insns. = M560BillCreate. */
static HU3DMODELID fn_1_7368(ANIMDATA *anim, HuVecF *posSrc, float *angleSrc, s16 maxCnt, float size, s16 cellW, s16 cellH)
{
    HU3DMODELID modelId;
    HU3DMODEL *modelP;
    M559_BILL *work;
    M559_BILLPART *part;
    HuVecF *vtx;
    HuVec2f *st;
    GXColor *color;
    void *dl;
    void *dlP;
    s16 cellX;
    s16 cellY;
    s16 i;

    modelId = Hu3DHookFuncCreate(fn_1_6B54);
    modelP = &Hu3DData[modelId];
    modelP->hookData = HuMemDirectMallocNum(HEAP_MODEL, sizeof(M559_BILL), modelP->mallocNo);
    work = modelP->hookData;
    anim->useNum++;
    work->anim = anim;
    work->posSrc = posSrc;
    work->angleSrc = angleSrc;
    work->maxCnt = maxCnt;
    work->unk6A = 0;
    work->func = NULL;
    work->liveCnt = maxCnt;
    work->killF = 0;
    work->part = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(M559_BILLPART), modelP->mallocNo);
    part = work->part;
    for(i=0; i<maxCnt; i++, part++) {
        part->no = -1;
        part->cellNo = -1;
    }
    work->vtx = HuMemDirectMallocNum(HEAP_MODEL, (maxCnt*sizeof(HuVecF))*4, modelP->mallocNo);
    vtx = work->vtx;
    for(i=0; i<maxCnt*4; i++, vtx++) {
        vtx->x = 0.0f;
        vtx->y = 0.0f;
        vtx->z = 0.0f;
    }
    work->color = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(GXColor), modelP->mallocNo);
    color = work->color;
    for(i=0; i<maxCnt; i++, color++) {
        color->r = 255;
        color->g = 255;
        color->b = 255;
        color->a = 255;
    }
    work->st = HuMemDirectMallocNum(HEAP_MODEL, (maxCnt*sizeof(HuVec2f))*4, modelP->mallocNo);
    st = work->st;
    for(i=0; i<maxCnt; i++) {
        st->x = 0.0f;
        st->y = 0.0f;
        st++;
        st->x = 1.0f;
        st->y = 0.0f;
        st++;
        st->x = 1.0f;
        st->y = 1.0f;
        st++;
        st->x = 0.0f;
        st->y = 1.0f;
        st++;
    }
    if(cellW != 0 || cellH != 0) {
        cellX = anim->bmp->sizeX/cellW;
        cellY = anim->bmp->sizeY/cellH;
        work->cellNum = cellX*cellY;
        work->cellSizeX = 1.0f/cellX;
        work->cellSizeY = 1.0f/cellY;
    } else {
        cellX = 1;
        work->cellNum = 1;
        work->cellSizeX = 1.0f;
        work->cellSizeY = 1.0f;
    }
    work->cellTbl = HuMemDirectMallocNum(HEAP_MODEL, work->cellNum*sizeof(HuVec2f), modelP->mallocNo);
    fn_1_729C(work->cellTbl, work->cellNum, cellX, work->cellSizeX, work->cellSizeY);
    work->quad[0].x = work->quad[3].x = work->quad[2].y = work->quad[3].y = -size;
    work->quad[1].x = work->quad[2].x = work->quad[0].y = work->quad[1].y = size;
    work->quad[0].z = work->quad[1].z = work->quad[2].z = work->quad[3].z = 0.0f;
    dl = HuMemDirectMallocNum(HEAP_MODEL, 0x20000, modelP->mallocNo);
    dlP = dl;
    GXBeginDisplayList(dlP, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, maxCnt*4);
    for(i=0; i<maxCnt; i++) {
        GXPosition1x16(i*4);
        GXColor1x16(i);
        GXTexCoord1x16(i*4);
        GXPosition1x16((i*4)+1);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+1);
        GXPosition1x16((i*4)+2);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+2);
        GXPosition1x16((i*4)+3);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+3);
    }
    work->dlSize = GXEndDisplayList();
    DCFlushRangeNoSync(dl, work->dlSize);
    work->dlBuf = HuMemDirectMallocNum(HEAP_MODEL, work->dlSize, modelP->mallocNo);
    memcpy(work->dlBuf, dl, work->dlSize);
    DCFlushRangeNoSync(work->dlBuf, work->dlSize);
    HuMemDirectFree(dl);
    return modelId;
}

/* asm 8444-8517, 66 insns. = M560BillPartCreate. */
static M559_BILLPART *fn_1_79C0(HU3DMODELID modelId, HuVecF *pos, GXColor *color, float scale, float zRot)
{
    M559_BILL *work = Hu3DData[modelId].hookData;
    M559_BILLPART *part;
    GXColor *colorP;
    s16 i;

    if(work->killF) {
        return NULL;
    }
    for(i=0, part=work->part; i<work->maxCnt; i++, part++) {
        if(part->no < 0) {
            break;
        }
    }
    if(i == work->maxCnt) {
        return NULL;
    }
    colorP = &work->color[i];
    colorP->r = color->r;
    colorP->g = color->g;
    colorP->b = color->b;
    colorP->a = color->a;
    part->pos = *pos;
    part->scale = scale;
    part->zRot = zRot;
    part->cellNo = 0;
    part->unk00 = 0;
    part->no = i;
    return part;
}

/* asm 8520-8535, 14 insns. = M560BillFuncSet. */
static void fn_1_7AC8(HU3DMODELID modelId, M559BILLFUNC func)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M559_BILL *work = modelP->hookData;
    work->func = func;
}

/* asm 8538-8551, 12 insns. = M560BillUnk6ASet. */
static void fn_1_7B00(HU3DMODELID modelId, u8 value)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    ((M559_BILL *)modelP->hookData)->unk6A = value;
}

/* asm 8554-8570, 15 insns. = M560BillKillReq. */
static void fn_1_7B30(HU3DMODELID modelId)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M559_BILL *work = modelP->hookData;
    work->killF = 1;
}

/* asm 8573-8623, 47 insns. = M560BillKill. */
static BOOL fn_1_7B6C(HU3DMODELID modelId)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M559_BILL *work = modelP->hookData;

    if(work->killF && work->liveCnt == 0) {
        HuMemDirectFree(work->part);
        HuMemDirectFree(work->vtx);
        HuMemDirectFree(work->color);
        HuMemDirectFree(work->st);
        HuMemDirectFree(work->cellTbl);
        HuMemDirectFree(work->dlBuf);
        HuSprAnimKill(work->anim);
        HuMemDirectFree(modelP->hookData);
        Hu3DModelKill(modelId);
        return TRUE;
    }
    return FALSE;
}

/* asm 8626-8788, 152 insns. = M560BillPartEmit. */
static void fn_1_7C28(HU3DMODELID modelId, s16 count, HuVecF *pos, float angle, float timeMax, float posYTarget)
{
    M559_BILLPART *part;
    GXColor color = { 0xFFu, 0xFFu, 0xFFu, 0xFFu };
    s16 i;

    for(i=0; i<count; i++) {
        part = fn_1_79C0(modelId, pos, &color, 0.0f, 0.0f);
        if(!part) {
            break;
        }
        part->basePos = *pos;
        part->time = 0.0f;
        part->angle = angle;
        part->timeAdd = 10.0f;
        part->timeMax = timeMax;
        part->posYTarget = posYTarget;
        part->angleOfs = (20.0f*frandf())-10.0f;
        part->timeAdd *= 0.8f+(0.4f*frandf());
        part->timeMax *= 0.9f+(0.3f*frandf());
    }
}

/* asm 8791-8844, 52 insns. = M560BillCreateEx, but model layer 4 (m560 uses 5). */
static HU3DMODELID fn_1_7E88(HuVecF *posSrc, float *angleSrc, s16 maxCnt)
{
    HU3DMODELID modelId = fn_1_7368(lbl_1_bss_0, posSrc, angleSrc, maxCnt, 40.0f, 64, 64);

    fn_1_7AC8(modelId, fn_1_6678);
    fn_1_7B00(modelId, 0);
    Hu3DModelLayerSet(modelId, 4);
    return modelId;
}
