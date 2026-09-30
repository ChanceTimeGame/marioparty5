/*
 * m549dll/cloud.c -- the drifting cloud shadow the arena floor is lit through.
 * Three functions and no counterpart in any other decompiled duel: a setup that
 * installs the two hooks, a layer hook that copies the framebuffer into a
 * scratch texture once per frame, and a material hook that builds the projected
 * texture matrices and the three-stage TEV/indirect setup that warps them.
 *
 * Written from the reference assembly, functions in reference order; line
 * ranges are into build/mp5-asm/m549Dll/asm/REL/m549Dll/cloud.s.
 */

#include "game/object.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/sprite.h"

#include "datadir_enum.h"

#include "REL/m549Dll/m549.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"

void fn_1_11694(s16 layerNo);
void fn_1_1172C(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material);

/* --- .data --- */

/* data_510 -- the 2x3 indirect matrix that warps the cloud texture. */
float lbl_1_data_510[2][3] = {
    { 0.03f, 0.0f, 0.02f },
    { 0.0f, 0.04f, 0.02f }
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

void *lbl_1_bss_1604;
ANIMDATA *lbl_1_bss_1600;
ANIMDATA *lbl_1_bss_15FC;
float lbl_1_bss_15F8;

/*
 * asm 9-71, 59 insns. Unreferenced -- nothing in the overlay calls it, so the
 * cloud is set up only if something outside does. Layer 8 gets the copy hook,
 * and the ten arena models 5..14 get the material hook.
 */
void fn_1_115A8(M549_WORK *work)
{
    int i;

    Hu3DLayerHookSet(8, fn_1_11694);
    lbl_1_bss_1604 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    lbl_1_bss_1600 = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m549, 0x19), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_15FC = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_effect, 0x0C), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i=0; i<10; i++) {
        Hu3DModelMatHookSet(work->models[i+5].modelId, fn_1_1172C);
    }
}

/*
 * asm 74-114, 38 insns. Once camera 1 is drawing, copy the framebuffer into the
 * scratch texture and drift the cloud a little further along.
 */
void fn_1_11694(s16 layerNo)
{
    if(Hu3DCameraBit & 2) {
        GXSetTexCopySrc(0, 0, 640, 480);
        GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(lbl_1_bss_1604, GX_FALSE);
        lbl_1_bss_15F8 -= 0.002f;
    }
}

/*
 * asm 117-411, 293 insns. The material hook: project the scratch texture from
 * the camera, scroll the cloud texture by lbl_1_bss_15F8, and combine the three
 * stages with an indirect warp off the cloud.
 */
void fn_1_1172C(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    GXColor color = { 0x10, 0x10, 0x10, 0x00 };
    HU3DCAMERA *cam = Hu3DCamera;
    GXTexObj tex;
    Mtx mtxObj;
    Mtx mtxScale;
    Mtx mtxWork;
    Mtx mtxLight;
    Mtx mtxInv;

    GXInitTexObj(&tex, lbl_1_bss_1604, 320, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&tex, GX_TEXMAP1);
    HuSprTexLoad(lbl_1_bss_1600, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_15FC, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    C_MTXLightPerspective(mtxLight, cam->fov, 1.3333334f, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, mtxInv);
    PSMTXConcat(mtxInv, drawObj->matrix, mtxObj);
    PSMTXConcat(mtxLight, Hu3DCameraMtx, mtxWork);
    PSMTXConcat(mtxWork, mtxObj, mtxWork);
    GXLoadTexMtxImm(mtxWork, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(mtxObj, 0.0f, lbl_1_bss_15F8, 0.0f);
    PSMTXScale(mtxScale, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(mtxScale, mtxObj, mtxWork);
    GXLoadTexMtxImm(mtxWork, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, color);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, lbl_1_data_510, -1);
}
