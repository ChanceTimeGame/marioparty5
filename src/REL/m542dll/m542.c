/*
 * m542dll -- a KETTOU duel (overlay #56): the sequence hooks, the arena models
 * and object bring-up. Written from the reference assembly, functions in
 * reference order; line ranges are into
 * build/mp5-asm/m542dll/asm/REL/m542dll/m542.s.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"
#include "game/gamemes.h"
#include "game/flag.h"

#include "datadir_enum.h"

#include "REL/m542dll/m542.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"
#include "dolphin/gx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void ObjectSetup(void);
void fn_1_248(s16 mode, s16 frameNo);
void fn_1_7A0(s16 mode, s16 frameNo);
void fn_1_7E4(s16 mode, s16 frameNo);
void fn_1_838(s16 mode, s16 frameNo);
void fn_1_9F0(s16 mode, s16 frameNo);
void fn_1_B70(s16 mode, s16 frameNo);
void fn_1_CC4(s16 mode, s16 frameNo);
void fn_1_CE8(s16 mode, s16 frameNo);
void fn_1_D1C(s16 mode, s16 frameNo);
void fn_1_D3C(OMOBJ *obj);
void fn_1_E20(int mdlNo, float alpha);
void fn_1_E9C(M542_MODEL *mdl);
void fn_1_FC8(void);
void fn_1_249C(void);
void fn_1_24F8(void);
void fn_1_2524(HU3DMODEL *model, Mtx *mtx);

/* --- .data --- */

/* files/data/m542.bin: the arena (passed to fn_1_84D0). */
unsigned int lbl_1_data_0[32] = {
    0x00640000, 0x00640001, 0x00640002, 0x00640003, 0x00640004, 0x00640005, 0x00640010, 0x00640011,
    0x00640012, 0x00640013, 0x00640014, 0x00640015, 0x00640016, 0x00640006, 0x00640007, 0x00640008,
    0x00640009, 0x0064000A, 0x0064000B, 0x0064000C, 0x0064000D, 0x0064000E, 0x0064000F, 0x0064001A,
    0x00640019, 0x00640018, 0x00640017, 0x0064001B, 0x0064001C, 0x0064001D, 0x0064001E, 0x0064001F
};

/* Nine motions per character, in charNo order. */
unsigned int lbl_1_data_80[13][9] = {
    { 0x008C0000, 0x008C0003, 0x008C0004, 0x008C0008, 0x008C0009, 0x008C000A, 0x008C002F, 0x008C002B, 0x008C0079 },
    { 0x00330000, 0x00330003, 0x00330004, 0x00330008, 0x00330009, 0x0033000A, 0x0033002F, 0x0033002B, 0x00330079 },
    { 0x00B70000, 0x00B70003, 0x00B70004, 0x00B70008, 0x00B70009, 0x00B7000A, 0x00B7002F, 0x00B7002B, 0x00B70079 },
    { 0x00ED0000, 0x00ED0003, 0x00ED0004, 0x00ED0008, 0x00ED0009, 0x00ED000A, 0x00ED002F, 0x00ED002B, 0x00ED0079 },
    { 0x00E60000, 0x00E60003, 0x00E60004, 0x00E60008, 0x00E60009, 0x00E6000A, 0x00E6002F, 0x00E6002B, 0x00E60079 },
    { 0x00170000, 0x00170003, 0x00170004, 0x00170008, 0x00170009, 0x0017000A, 0x0017002F, 0x0017002B, 0x00170079 },
    { 0x00E00000, 0x00E00003, 0x00E00004, 0x00E00008, 0x00E00009, 0x00E0000A, 0x00E0002F, 0x00E0002B, 0x00E00079 },
    { 0x002D0000, 0x002D0003, 0x002D0004, 0x002D0008, 0x002D0009, 0x002D000A, 0x002D002F, 0x002D002B, 0x002D0079 },
    { 0x00C90000, 0x00C90003, 0x00C90004, 0x00C90008, 0x00C90009, 0x00C9000A, 0x00C9002F, 0x00C9002B, 0x00C90079 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B00009, 0x00B0000A, 0x00B0002F, 0x00B0002B, 0x00B00079 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B00009, 0x00B0000A, 0x00B0002F, 0x00B0002B, 0x00B00079 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B00009, 0x00B0000A, 0x00B0002F, 0x00B0002B, 0x00B00079 },
    { 0x00B00000, 0x00B00003, 0x00B00004, 0x00B00008, 0x00B00009, 0x00B0000A, 0x00B0002F, 0x00B0002B, 0x00B00079 }
};

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_254 = {
    0, 0,
    fn_1_248,
    fn_1_7A0,
    fn_1_7E4,
    fn_1_838,
    fn_1_9F0,
    fn_1_B70,
    fn_1_CC4,
    fn_1_CE8,
    fn_1_D1C
};

/* Sub-state tables, indexed by lbl_1_bss_1954.mode[0]. */
void (*lbl_1_data_27C[4])(void) = { fn_1_2858, fn_1_2978, fn_1_2A14, fn_1_2AD0 };
void (*lbl_1_data_28C[3])(void) = { fn_1_2BDC, fn_1_2DAC, fn_1_2F90 };
s32 lbl_1_data_298 = -1;
void (*lbl_1_data_29C[3])(void) = { fn_1_5420, fn_1_5D30, fn_1_6A30 };

/* Thirteen texture-cell offsets, quarter steps (the m554 table). */
float lbl_1_data_2A8[13][2] = {
    { 0.0f, 0.0f },
    { 0.25f, 0.0f },
    { 0.5f, 0.0f },
    { 0.75f, 0.0f },
    { 0.0f, 0.25f },
    { 0.25f, 0.25f },
    { 0.5f, 0.25f },
    { 0.75f, 0.25f },
    { 0.0f, 0.25f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f },
    { 0.25f, 0.5f }
};

/* .data:0x310 "m542count01" and 0x31C "TL32m542burst01" are literals in fn_1_FC8. */

/* --- .bss --- */

s16 lbl_1_bss_0;                    /* the hook model (fn_1_249C, fn_1_24F8) */
s32 lbl_1_bss_4;
s32 lbl_1_bss_8;
s32 lbl_1_bss_C;
u8 lbl_1_bss_10;
M542_COM lbl_1_bss_14[2];           /* dtk's symbol is 0x40: 8 more bytes follow unreferenced */
HU3DMOTID lbl_1_bss_54[18];         /* nine motions per duellist */
OMCAMERAVIEW lbl_1_bss_78[4];

/* asm 61-174, 106 insns. */
void ObjectSetup(void)
{
    s16 i;
    s16 j;

    for(i=0; i<M542_MODEL_MAX; i++) {
        lbl_1_bss_1588[i].modelId = -1;
    }
    for(i=0; i<4; i++) {
        for(j=0; j<30; j++) {
            lbl_1_bss_E8[i][j].mode = 0;
            lbl_1_bss_E8[i][j].modelId = -1;
        }
    }
    fn_1_84D0(&lbl_1_bss_1954, lbl_1_bss_1588, lbl_1_data_0);
    lbl_1_bss_1954.objman = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_1954.objman);
    omAddObjEx(lbl_1_bss_1954.objman, 32730, 0, 0, -1, omOutView);
    omAddObjEx(lbl_1_bss_1954.objman, 32730, 0, 0, -1, fn_1_8C94);
    omAddObjEx(lbl_1_bss_1954.objman, 32730, 0, 0, -1, fn_1_94B4);
    MgSeqCreate(&lbl_1_data_254);
}

/* asm 177-520, 342 insns. Init hook: arena, duellists, camera, light and shadow, the COM state and the fade quad. */
void fn_1_248(s16 mode, s16 frameNo)
{
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    HU3DLIGHTID lightId;

    fn_1_871C(0);
    fn_1_89DC(lbl_1_data_80[lbl_1_bss_1954.chr[0].no], lbl_1_data_80[lbl_1_bss_1954.chr[1].no]);
    fn_1_8A00(&lbl_1_bss_54[0], &lbl_1_bss_54[9]);
    fn_1_8A24();
    fn_1_9150();
    omAddObjEx(lbl_1_bss_1954.objman, 32730, 0, 0, -1, fn_1_92A4);
    fn_1_FC8();
    Center.x = 0.0f;
    Center.y = 275.0f;
    Center.z = 0.0f;
    CRot.x = -50.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 800.0f;
    lbl_1_bss_78[0].center.x = 0.0f;
    lbl_1_bss_78[0].center.y = 185.0f;
    lbl_1_bss_78[0].center.z = 0.0f;
    lbl_1_bss_78[0].rot.x = -10.0f;
    lbl_1_bss_78[0].rot.y = 0.0f;
    lbl_1_bss_78[0].rot.z = 0.0f;
    lbl_1_bss_78[0].zoom = 1120.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(lbl_1_bss_1954.objman, 32730, 0, 0, -1, fn_1_D3C);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    pos.x = 0.0f;
    pos.y = 1200.0f;
    pos.z = 600.0f;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    target.x = 0.0f;
    target.y = 0.0f;
    target.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&pos, &up, &target);
    Hu3DModelShadowSet(lbl_1_bss_1954.models[32].modelId);
    Hu3DModelShadowSet(lbl_1_bss_1954.models[33].modelId);
    Hu3DModelShadowMapSet(lbl_1_bss_1954.models[0].modelId);
    lbl_1_bss_1954.player[0].motNo = 0;
    lbl_1_bss_1954.player[0].speed = 1.0f;
    lbl_1_bss_1954.player[0].time = 0.0f;
    lbl_1_bss_1954.player[0].attr = HU3D_MOTATTR_LOOP;
    lbl_1_bss_1954.player[1].motNo = 0;
    lbl_1_bss_1954.player[1].speed = 1.0f;
    lbl_1_bss_1954.player[1].time = 0.0f;
    lbl_1_bss_1954.player[1].attr = HU3D_MOTATTR_LOOP;
    fn_1_4994();
    lbl_1_bss_10 = 0;
    fn_1_249C();
    Hu3DModelAttrReset(lbl_1_bss_0, HU3D_ATTR_DISPOFF);
    MgSeqModeDelaySet(mode+1, -1);
    MgSeqModeNext();
}

/* asm 523-541, 17 insns. Fade-in hook: runs data_27C by mode. */
void fn_1_7A0(s16 mode, s16 frameNo)
{
    lbl_1_data_27C[lbl_1_bss_1954.mode[0]]();
}

/* asm 544-566, 21 insns. Start hook. */
void fn_1_7E4(s16 mode, s16 frameNo)
{
    lbl_1_bss_1954.mode[0] = 0;
    lbl_1_bss_1954.mode[1] = 0;
    MgSeqModeDelaySet(mode+1, -1);
}

/* asm 569-684, 110 insns. Main hook: the sub-state, then the warning pulse (bss_10, the fade quad's alpha) once the clock passes 300. */
void fn_1_838(s16 mode, s16 frameNo)
{
    lbl_1_data_28C[lbl_1_bss_1954.mode[0]]();
    if(lbl_1_bss_4 != 0 || lbl_1_bss_8 != 0) {
        if(lbl_1_bss_C >= 300) {
            if(lbl_1_data_298 < 0) {
                lbl_1_data_298 = HuAudFXPlay(2066);
            }
            lbl_1_bss_8 = (lbl_1_bss_8+1)%48;
            lbl_1_bss_10 = 96.0*sin((M_PI*((lbl_1_bss_8*180)/48))/180.0);
        }
    } else if(lbl_1_data_298 >= 0) {
        HuAudFXFadeOut(lbl_1_data_298, 20);
        lbl_1_data_298 = -1;
    }
}

/* asm 687-787, 96 insns. Finish hook. */
void fn_1_9F0(s16 mode, s16 frameNo)
{
    if(lbl_1_data_298 >= 0) {
        HuAudFXFadeOut(lbl_1_data_298, 20);
        lbl_1_data_298 = -1;
    }
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_5120();
    if((lbl_1_bss_4 != 0 || lbl_1_bss_8 != 0) && lbl_1_bss_C >= 300) {
            lbl_1_bss_8 = (lbl_1_bss_8+1)%48;
            lbl_1_bss_10 = 96.0*sin((M_PI*((lbl_1_bss_8*180)/48))/180.0);
    }
}

/* asm 790-878, 85 insns. Pre-winner hook: the sub-state, and the pulse runs down. */
void fn_1_B70(s16 mode, s16 frameNo)
{
    lbl_1_data_29C[lbl_1_bss_1954.mode[0]]();
    if((lbl_1_bss_4 != 0 || lbl_1_bss_8 != 0) && lbl_1_bss_C >= 300) {
            lbl_1_bss_8 = (lbl_1_bss_8+1)%48;
            lbl_1_bss_10 = 96.0*sin((M_PI*((lbl_1_bss_8*180)/48))/180.0);
    }
}

/* asm 881-891, 9 insns. Winner hook. */
void fn_1_CC4(s16 mode, s16 frameNo)
{
    MgSeqModeNext();
    fn_1_737C();
}

/* asm 894-909, 13 insns. Fade-out hook; identical to m548 fn_1_A9C. */
void fn_1_CE8(s16 mode, s16 frameNo)
{
    fn_1_737C();
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
}

/* asm 912-921, 8 insns. Close hook. */
void fn_1_D1C(s16 mode, s16 frameNo)
{
    fn_1_24F8();
}

/* asm 924-990, 57 insns. Object main: push the model table and every live particle at Hu3D. */
void fn_1_D3C(OMOBJ *obj)
{
    M542_MODEL *mdl = lbl_1_bss_1588;
    int i;
    M542_PARTICLE *part;
    int j;

    for(i=0; i<M542_MODEL_MAX; i++, mdl++) {
        if(mdl->modelId >= 0) {
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
        }
    }
    for(i=0; i<4; i++) {
        for(j=0; j<30; j++) {
            part = &lbl_1_bss_E8[i][j];
            if(part->mode != 0) {
                Hu3DModelPosSetV(part->modelId, &part->pos);
                Hu3DModelRotSetV(part->modelId, &part->rot);
            }
        }
    }
}

/* asm 993-1027, 31 insns. m550 M550MatAlphaSet; unreferenced. */
void fn_1_E20(int mdlNo, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[lbl_1_bss_1954.models[mdlNo].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}

/* asm 1030-1106, 75 insns. m550 M550ModelReset; unreferenced. */
void fn_1_E9C(M542_MODEL *mdl)
{
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(mdl->modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdl->modelId, 0.0f, 0.0f, 0.0f);
    mdl->pos.x = 0.0f;
    mdl->pos.y = 0.0f;
    mdl->pos.z = 0.0f;
    mdl->rot.x = 0.0f;
    mdl->rot.y = 0.0f;
    mdl->rot.z = 0.0f;
    Hu3DModelCameraSet(mdl->modelId, 1);
    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
    Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
}

/* asm 1109-2472, 1333 insns. The arena props, both counter boards and their scrolls, the 120 linked particle models and the two burst models. Retail quirk kept: the particle loop resets model 29 (the template) after each link, not the link. */
void fn_1_FC8(void)
{
    M542_MODEL *mdl;
    int i;
    int j;

    mdl = &lbl_1_bss_1588[6];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[6], HU_MEMNUM_OVL, HEAP_MODEL));
    fn_1_E9C(mdl);
    for(i=0; i<4; i++) {
        mdl = &lbl_1_bss_1588[i+7];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+7], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_E9C(mdl);
        Hu3DModelAttrReset(mdl->modelId, HU3D_MOTATTR_LOOP);
        if(i >= 2) {
            Hu3DModelShadowMapSet(mdl->modelId);
        }
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1588[i+11];
        if(i == 0) {
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[11], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(lbl_1_bss_1954.models[11].modelId);
        }
        fn_1_E9C(mdl);
        Hu3DModelPosSet(mdl->modelId, -210.0f+(420.0f*i), 0.0f, 254.0f);
        mdl->pos.x = -210.0f+(420.0f*i);
        mdl->pos.y = 0.0f;
        mdl->pos.z = 254.0f;
        Hu3DModelShadowMapSet(mdl->modelId);
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1588[i+13];
        if(i == 0) {
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[12], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(lbl_1_bss_1954.models[13].modelId);
        }
        fn_1_E9C(mdl);
        Hu3DModelPosSet(mdl->modelId, -210.0f+(420.0f*i), 0.0f, 254.0f);
        mdl->pos.x = -210.0f+(420.0f*i);
        mdl->pos.y = 0.0f;
        mdl->pos.z = 254.0f;
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1588[i+15];
        if(lbl_1_bss_1954.chr[i].charNo > 9) {
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[22], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[lbl_1_bss_1954.chr[i].charNo+13], HU_MEMNUM_OVL, HEAP_MODEL));
        }
        fn_1_E9C(mdl);
        Hu3DModelLayerSet(mdl->modelId, 4);
        Hu3DModelPosSet(mdl->modelId, -290.0f+(580.0f*i), 132.0f, -128.0f);
        mdl->pos.x = -290.0f+(580.0f*i);
        mdl->pos.y = 132.0f;
        mdl->pos.z = -128.0f;
    }
    for(i=0; i<5; i++) {
        for(j=0; j<2; j++) {
            mdl = &lbl_1_bss_1588[i+((j*5)+17)];
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+23], HU_MEMNUM_OVL, HEAP_MODEL));
            fn_1_E9C(mdl);
            Hu3DModelPosSet(mdl->modelId, -210.0f+(420.0f*j), 0.0f, 0.0f);
            mdl->pos.x = -210.0f+(420.0f*j);
            mdl->pos.y = 0.0f;
            mdl->pos.z = 0.0f;
            if(i == 4) {
                Hu3DMotionTimeSet(mdl->modelId, 30.0f);
                Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
                Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
            } else {
                lbl_1_bss_1940[j][i] = Hu3DTexScrollCreate(mdl->modelId, "m542count01");
            }
        }
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1588[i+27];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+28], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_E9C(mdl);
        Hu3DModelLayerSet(mdl->modelId, 4);
        Hu3DModelPosSet(mdl->modelId, -290.0f+(580.0f*i), 132.0f, -128.0f);
        mdl->pos.x = -290.0f+(580.0f*i);
        mdl->pos.y = 132.0f;
        mdl->pos.z = -128.0f;
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_1940[i][4] = Hu3DTexScrollCreate(mdl->modelId, "TL32m542burst01");
        Hu3DTexScrollPosSet(lbl_1_bss_1940[i][4], lbl_1_data_2A8[lbl_1_bss_1954.chr[i].charNo][0], lbl_1_data_2A8[lbl_1_bss_1954.chr[i].charNo][1], 0.0f);
    }
    mdl = &lbl_1_bss_1588[29];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[30], HU_MEMNUM_OVL, HEAP_MODEL));
    fn_1_E9C(mdl);
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    for(i=0; i<4; i++) {
        for(j=0; j<30; j++) {
            lbl_1_bss_E8[i][j].modelId = Hu3DModelLink(mdl->modelId);
            fn_1_E9C(mdl);
            Hu3DModelAttrSet(lbl_1_bss_E8[i][j].modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(lbl_1_bss_E8[i][j].modelId, 5);
        }
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_1588[i+30];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[31], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_E9C(mdl);
        Hu3DModelLayerSet(mdl->modelId, 5);
        Hu3DModelPosSet(mdl->modelId, -290.0f+(580.0f*i), 464.0f, -128.0f);
        mdl->pos.x = -290.0f+(580.0f*i);
        mdl->pos.y = 464.0f;
        mdl->pos.z = -128.0f;
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    }
}

/* asm 2475-2499, 23 insns. The full-screen fade quad (drawn by fn_1_2524, alpha bss_10). */
void fn_1_249C(void)
{
    lbl_1_bss_0 = Hu3DHookFuncCreate(fn_1_2524);
    Hu3DModelLayerSet(lbl_1_bss_0, 6);
    Hu3DModelCameraSet(lbl_1_bss_0, 1);
}

/* asm 2502-2514, 11 insns. */
void fn_1_24F8(void)
{
    Hu3DModelKill(lbl_1_bss_0);
}

/* asm 2517-2723, 205 insns. Hook draw: a red full-screen quad at alpha bss_10. */
void fn_1_2524(HU3DMODEL *model, Mtx *mtx)
{
    GXColor color = { 0, 0, 0, 0 };
    Mtx44 proj;

    color.r = 255;
    color.a = lbl_1_bss_10;
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, -16777215.0f);
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
    GXPosition3s16(0, 0, 0);
    GXPosition3s16(640, 0, 0);
    GXPosition3s16(640, 480, 0);
    GXPosition3s16(0, 480, 0);
    GXEnd();
}
