/*
 * m554dll -- a KETTOU duel (overlay #68): the sequence hooks, the model
 * table, and object bring-up.
 *
 * Written from the reference assembly, functions in reference order. Line
 * ranges are into build/mp5-asm/m554dll/asm/REL/m554dll/m554.s.
 * The [m550 ...] tags name the m550dll function each one matches; "=" is
 * instruction-identical (symbol-normalized), "~" is the same function with
 * this overlay's changes. See NOTES.md for the measured table.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/hsfformat.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"

#include "datadir_enum.h"

#include "REL/m554dll/m554.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"

void ObjectSetup(void);
void fn_1_1C0(s16 mode, s16 frameNo);
void fn_1_808(s16 mode, s16 frameNo);
void fn_1_84C(s16 mode, s16 frameNo);
void fn_1_914(s16 mode, s16 frameNo);
void fn_1_958(s16 mode, s16 frameNo);
void fn_1_990(s16 mode, s16 frameNo);
void fn_1_9D4(s16 mode, s16 frameNo);
void fn_1_9F8(s16 mode, s16 frameNo);
void fn_1_A2C(s16 mode, s16 frameNo);
void fn_1_A30(OMOBJ *obj);
void fn_1_A64(void);
void fn_1_EB4(OMOBJ *obj);
void fn_1_1320(M554_MODEL *mdl);
void fn_1_144C(void);

/* --- .data --- */

u32 lbl_1_data_0 = 0x00700003;

/* files/data/m554.bin: the arena, 0x00..0x14 less 0x03 (which is data_0). */
unsigned int lbl_1_data_4[20] = {
    0x00700000, 0x00700001, 0x00700002, 0x00700004, 0x00700005,
    0x00700006, 0x00700007, 0x00700008, 0x00700009, 0x0070000A,
    0x0070000B, 0x0070000C, 0x0070000D, 0x0070000E, 0x0070000F,
    0x00700010, 0x00700011, 0x00700012, 0x00700013, 0x00700014
};

/* Five motions per character, in charNo order ([m550 CharMotDataTbl]). */
unsigned int lbl_1_data_54[13][5] = {
    { 0x008700AF, 0x008700B0, 0x008C007E, 0x008C002F, 0x008C002B },
    { 0x002E00AF, 0x002E00B0, 0x0033007E, 0x0033002F, 0x0033002B },
    { 0x00B200AF, 0x00B200B0, 0x00B7007E, 0x00B7002F, 0x00B7002B },
    { 0x00E800AF, 0x00E800B0, 0x00ED007E, 0x00ED002F, 0x00ED002B },
    { 0x00E100AF, 0x00E100B0, 0x00E6007E, 0x00E6002F, 0x00E6002B },
    { 0x001200AF, 0x001200B0, 0x0017007E, 0x0017002F, 0x0017002B },
    { 0x00DB00AF, 0x00DB00B0, 0x00E0007E, 0x00E0002F, 0x00E0002B },
    { 0x002800AF, 0x002800B0, 0x002D007E, 0x002D002F, 0x002D002B },
    { 0x00C400AF, 0x00C400B0, 0x00C9007E, 0x00C9002F, 0x00C9002B },
    { 0x009C00AF, 0x009C00B0, 0x00B0007E, 0x00B0002F, 0x00B0002B },
    { 0x009C00AF, 0x009C00B0, 0x00B0007E, 0x00B0002F, 0x00B0002B },
    { 0x009C00AF, 0x009C00B0, 0x00B0007E, 0x00B0002F, 0x00B0002B },
    { 0x009C00AF, 0x009C00B0, 0x00B0007E, 0x00B0002F, 0x00B0002B }
};

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_158 = {
    0, 0,
    fn_1_1C0,
    fn_1_808,
    fn_1_84C,
    fn_1_914,
    fn_1_958,
    fn_1_990,
    fn_1_9D4,
    fn_1_9F8,
    fn_1_A2C
};

/* Sub-state tables, indexed by lbl_1_bss_B1C.mode[0]. */
void (*lbl_1_data_180[3])(void) = { fn_1_1F00, fn_1_2118, fn_1_22CC };
void (*lbl_1_data_18C[3])(void) = { fn_1_240C, fn_1_2654, fn_1_2800 };
void (*lbl_1_data_198[3])(void) = { fn_1_2870, fn_1_2C74, fn_1_31C8 };

/* No reference of its own; dtk folds it into data_198. */
float lbl_1_data_1A4 = 1.0f;

s32 lbl_1_data_1A8[2] = { 0, 0 };
float lbl_1_data_1B0[2] = { 0.5f, 0.2f };
float lbl_1_data_1B8[2] = { 0.0f, 2.0f };
s32 lbl_1_data_1C0 = 18;           /* fn_1_A34 counts it down, fn_1_A54 reads it */

/* Thirteen texture-cell offsets, quarter steps. */
float lbl_1_data_1C4[13][2] = {
    { 0.0f, 0.0f }, { 0.25f, 0.0f }, { 0.5f, 0.0f }, { 0.75f, 0.0f },
    { 0.0f, 0.25f }, { 0.25f, 0.25f }, { 0.5f, 0.25f }, { 0.75f, 0.25f },
    { 0.0f, 0.5f }, { 0.25f, 0.5f }, { 0.25f, 0.5f }, { 0.25f, 0.5f },
    { 0.25f, 0.5f }
};

/* .data:0x22C "CI8m554" is a literal in fn_1_144C. */

/* --- .bss --- */

s32 lbl_1_bss_0;                    /* fn_1_84C's once flag */
s32 lbl_1_bss_4;
HuVecF lbl_1_bss_8;
M554_SLOT lbl_1_bss_14[7];
s32 lbl_1_bss_68;                   /* unreferenced; dtk folds it into bss_14 */
M554_COM lbl_1_bss_6C[2];
HU3DMOTID lbl_1_bss_84[10];         /* five motions per duellist */
OMCAMERAVIEW lbl_1_bss_98[4];
s16 lbl_1_bss_108[2];
M554_MODEL lbl_1_bss_10C[M554_MODEL_MAX];
M554_WORK lbl_1_bss_B1C;

/* asm 61-136, 72 insns. [m550 ~ObjectSetup] */
void ObjectSetup(void)
{
    s16 i;

    for(i=0; i<M554_MODEL_MAX; i++) {
        lbl_1_bss_10C[i].modelId = HU3D_MODELID_NONE;
    }
    fn_1_62F0(&lbl_1_bss_B1C, lbl_1_bss_10C, lbl_1_data_4);
    lbl_1_bss_B1C.objman = omInitObjMan(50, 0x2000);
    omGameSysInit(lbl_1_bss_B1C.objman);
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, omOutView);
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_6E80);
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_A30);
    MgSeqCreate(&lbl_1_data_158);
}

/* asm 139-542, 402 insns. MGSEQ init hook. [m550 ~M550InitHook] */
void fn_1_1C0(s16 mode, s16 frameNo)
{
    HuVecF shadowPos;
    HuVecF shadowUp;
    HuVecF shadowTarget;
    HU3DLIGHTID lightId;

    fn_1_653C(2);
    fn_1_6C20(lbl_1_data_54[lbl_1_bss_B1C.chr[0].charNo], lbl_1_data_54[lbl_1_bss_B1C.chr[1].charNo]);
    fn_1_6C44(&lbl_1_bss_84[0], &lbl_1_bss_84[5]);
    fn_1_6C68();
    fn_1_733C();
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_7490);
    fn_1_144C();
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_7880);
    Center.x = 0.0f;
    Center.y = 390.0f;
    Center.z = 200.0f;
    CRot.x = -20.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 220.0f;
    lbl_1_bss_98[0].center.x = 0.0f;
    lbl_1_bss_98[0].center.y = 400.0f;
    lbl_1_bss_98[0].center.z = 100.0f;
    lbl_1_bss_98[0].rot.x = -25.0f;
    lbl_1_bss_98[0].rot.y = 0.0f;
    lbl_1_bss_98[0].rot.z = 0.0f;
    lbl_1_bss_98[0].zoom = 1450.0f;
    lbl_1_bss_98[1].center.x = -40.0f;
    lbl_1_bss_98[1].center.y = 290.0f;
    lbl_1_bss_98[1].center.z = 200.0f;
    lbl_1_bss_98[1].rot.x = -14.0f;
    lbl_1_bss_98[1].rot.y = -26.0f;
    lbl_1_bss_98[1].rot.z = -8.0f;
    lbl_1_bss_98[1].zoom = 1560.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_EB4);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    shadowPos.x = 0.0f;
    shadowPos.y = 1200.0f;
    shadowPos.z = 10.0f;
    shadowUp.x = 0.0f;
    shadowUp.y = 1.0f;
    shadowUp.z = 0.0f;
    shadowTarget.x = 0.0f;
    shadowTarget.y = 0.0f;
    shadowTarget.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
    Hu3DModelShadowSet(lbl_1_bss_B1C.models[78].modelId);
    Hu3DModelShadowSet(lbl_1_bss_B1C.models[79].modelId);
    lbl_1_bss_B1C.player[0].motNo = 0;
    lbl_1_bss_B1C.player[0].speed = 1.0f;
    lbl_1_bss_B1C.player[0].time = 0.0f;
    lbl_1_bss_B1C.player[0].attr = HU3D_MOTATTR_LOOP;
    lbl_1_bss_B1C.player[1].motNo = 0;
    lbl_1_bss_B1C.player[1].speed = 1.0f;
    lbl_1_bss_B1C.player[1].time = 0.0f;
    lbl_1_bss_B1C.player[1].attr = HU3D_MOTATTR_LOOP;
    lbl_1_bss_B1C.run[0].dist = 800.0f;
    lbl_1_bss_B1C.run[0].angle = -22.5f;
    lbl_1_bss_B1C.run[1].dist = 800.0f;
    lbl_1_bss_B1C.run[1].angle = 22.5f;
    MgSeqModeDelaySet(mode+1, -1);
    MgSeqModeNext();
}

/* asm 545-563, 17 insns. MGSEQ fade-in hook, dispatches data_180. [m550 =M550FadeInHook] */
void fn_1_808(s16 mode, s16 frameNo)
{
    lbl_1_data_180[lbl_1_bss_B1C.mode[0]]();
}

/* asm 566-618, 50 insns. MGSEQ start hook. */
void fn_1_84C(s16 mode, s16 frameNo)
{
    lbl_1_bss_B1C.mode[0] = 0;
    lbl_1_bss_B1C.mode[1] = 0;
    MgSeqModeDelaySet(mode+1, -1);
    if(lbl_1_bss_0 == 0 && omCameraViewCheck(1)) {
        omAddObjEx(lbl_1_bss_B1C.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_53B0);
        Hu3DModelAttrReset(lbl_1_bss_B1C.models[77].modelId, HU3D_ATTR_DISPOFF);
        lbl_1_bss_0 = 1;
    }
}

/* asm 621-639, 17 insns. MGSEQ main hook, dispatches data_18C. [m550 =M550MainHook] */
void fn_1_914(s16 mode, s16 frameNo)
{
    lbl_1_data_18C[lbl_1_bss_B1C.mode[0]]();
}

/* asm 642-657, 14 insns. MGSEQ finish hook. [m550 ~M550StartHook, 0.78] */
void fn_1_958(s16 mode, s16 frameNo)
{
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_2804();
}

/* asm 660-678, 17 insns. MGSEQ pre-winner hook, dispatches data_198. [m550 =M550PreWinnerHook] */
void fn_1_990(s16 mode, s16 frameNo)
{
    lbl_1_data_198[lbl_1_bss_B1C.mode[0]]();
}

/* asm 681-691, 9 insns. MGSEQ winner hook. */
void fn_1_9D4(s16 mode, s16 frameNo)
{
    fn_1_31C8();
    MgSeqModeNext();
}

/* asm 694-709, 13 insns. MGSEQ fade-out hook. */
void fn_1_9F8(s16 mode, s16 frameNo)
{
    fn_1_31C8();
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
}

/* asm 712-714, 1 insn. MGSEQ close hook. [m550 =M550CloseHook] */
void fn_1_A2C(s16 mode, s16 frameNo)
{
}

/* asm 717-719, 1 insn. Object main installed by ObjectSetup. */
void fn_1_A30(OMOBJ *obj)
{
}

/* asm 722-731, 8 insns. Called from game.c. */
void fn_1_A34(void)
{
    lbl_1_data_1C0--;
}

/* asm 734-739, 4 insns. Called from game.c. */
s32 fn_1_A54(void)
{
    return lbl_1_data_1C0;
}

/*
 * asm 742-1029, 276 insns. Called by fn_1_EB4 while it animates model 2:
 * drifts the sixty models 17..76 and, every data_1C0 frames, drops the next
 * three of them in at bss_8 (model 2's position).
 */
void fn_1_A64(void)
{
    M554_MODEL *mdl;
    int i;

    lbl_1_data_1A8[1]++;
    for(i=0; i<60; i++) {
        mdl = &lbl_1_bss_10C[i+17];
        if(i%3 == 0) {
            mdl->pos.x -= 6.0f;
            mdl->pos.z -= 4.0f;
            mdl->pos.y -= 1.0f;
        }
        if(i%3 == 1) {
            mdl->pos.y -= 1.0f;
            mdl->pos.z -= 2.0f;
        }
        if(i%3 == 2) {
            mdl->pos.x += 6.0f;
            mdl->pos.z -= 4.0f;
            mdl->pos.y -= 1.0f;
        }
    }
    if(lbl_1_data_1A8[1]++ > lbl_1_data_1C0) {
        for(i=0; i<3; i++) {
            mdl = &lbl_1_bss_10C[(lbl_1_bss_4*3)+(i+17)];
            mdl->pos = lbl_1_bss_8;
            mdl->pos.x += 50.0*sin((M_PI*((i*45)+(((i-5)*2)-45)))/180.0);
            mdl->pos.z += 40.0*cos((M_PI*((i*45)+(((i-5)*2)-45)))/180.0);
            mdl->pos.y -= 25.0f;
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
            if(i == 1) {
                Hu3DModelScaleSet(mdl->modelId, 6.0f, 6.0f, 6.0f);
            } else {
                Hu3DModelScaleSet(mdl->modelId, 5.0f, 5.0f, 5.0f);
            }
        }
        lbl_1_data_1A8[1] = 0;
        lbl_1_bss_4 = (lbl_1_bss_4+1)%10;
        if(lbl_1_bss_4 == 0 && lbl_1_data_1C0 > 8) {
            lbl_1_data_1C0--;
        }
    }
}

/*
 * asm 1032-1295, 252 insns. Object main installed by fn_1_1C0: the model
 * flush, except that model 2 sways on a circle once its rot.y is zero.
 */
void fn_1_EB4(OMOBJ *obj)
{
    HuVecF pos;
    HuVecF rot;
    M554_MODEL *mdl;
    int i;

    for(mdl=lbl_1_bss_10C, i=0; i<M554_MODEL_MAX; i++, mdl++) {
        if(mdl->modelId < 0) {
            continue;
        }
        if(i == 2) {
            pos = mdl->pos;
            rot = mdl->rot;
            if(0.0f == mdl->rot.y) {
                lbl_1_data_1A8[0]++;
                if(lbl_1_data_1A8[0] > 30) {
                    lbl_1_data_1A8[0] = 0;
                    if(lbl_1_data_1B0[0] < 25.0f) {
                        lbl_1_data_1B0[0] += 1.25f;
                    }
                    if(lbl_1_data_1B8[1] < 25.0f) {
                        lbl_1_data_1B8[1] += 0.5f;
                    }
                    if(lbl_1_data_1B0[1] < 2.0f) {
                        lbl_1_data_1B0[1] += 0.1f;
                    }
                }
                lbl_1_data_1B8[0] -= lbl_1_data_1B8[1];
                if(lbl_1_data_1B8[0] > 360.0f) {
                    lbl_1_data_1B8[0] -= 360.0f;
                }
                if(lbl_1_data_1B8[0] < 0.0f) {
                    lbl_1_data_1B8[0] += 360.0f;
                }
                pos.z += lbl_1_data_1B0[0]*cos((M_PI*lbl_1_data_1B8[0])/180.0);
                pos.x += lbl_1_data_1B0[0]*sin((M_PI*lbl_1_data_1B8[0])/180.0);
                rot.z = lbl_1_data_1B0[1]*cos((M_PI*lbl_1_data_1B8[0])/180.0);
                rot.x = lbl_1_data_1B0[1]*sin((M_PI*lbl_1_data_1B8[0])/180.0);
            }
            lbl_1_bss_8 = pos;
            Hu3DModelPosSetV(mdl->modelId, &pos);
            Hu3DModelRotSetV(mdl->modelId, &rot);
            fn_1_A64();
        } else {
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
        }
    }
}

/* asm 1298-1332, 31 insns. [m550 =M550MatAlphaSet] */
void fn_1_12A4(int mdlNo, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[lbl_1_bss_B1C.models[mdlNo].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}

/* asm 1335-1411, 75 insns. [m550 =M550ModelReset] */
void fn_1_1320(M554_MODEL *mdl)
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

/*
 * asm 1414-2109, 685 insns. [m550 ~M550ObjCreate] Everything the duel
 * draws; fn_1_1320 is inlined at every creation site.
 */
void fn_1_144C(void)
{
    M554_MODEL *mdl;
    int i;
    HU3DMOTID motId;

    mdl = &lbl_1_bss_10C[2];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[2], HU_MEMNUM_OVL, HEAP_MODEL));
    motId = Hu3DJointMotion(mdl->modelId, HuDataSelHeapReadNum(lbl_1_data_0, HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionSet(mdl->modelId, motId);
    fn_1_1320(mdl);
    Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
    Hu3DModelScaleSet(mdl->modelId, 5.0f, 5.0f, 5.0f);
    Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
    mdl->pos.x = 0.0f;
    mdl->pos.y = -200.0f;
    mdl->pos.z = -600.0f;
    mdl->rot.x = 0.0f;
    mdl->rot.y = -180.0f;
    mdl->rot.z = 0.0f;
    Hu3DModelLayerSet(mdl->modelId, 3);
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_10C[i+3];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[3], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_1320(mdl);
        lbl_1_bss_108[i] = Hu3DTexScrollCreate(mdl->modelId, "CI8m554");
        if(lbl_1_bss_108[i] >= 0) {
            Hu3DTexScrollPosSet(lbl_1_bss_108[i], lbl_1_data_1C4[lbl_1_bss_B1C.chr[i].charNo][0], lbl_1_data_1C4[lbl_1_bss_B1C.chr[i].charNo][1], 0.0f);
        }
        Hu3DModelHookSet(lbl_1_bss_10C[i+78].modelId, CharModelItemHookGet(lbl_1_bss_B1C.chr[i].charNo, 1, 0), mdl->modelId);
        mdl = &lbl_1_bss_10C[i+5];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[4], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_1320(mdl);
        Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        Hu3DModelAttrSet(mdl->modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelShadowMapSet(mdl->modelId);
        Hu3DModelLayerSet(mdl->modelId, 4);
    }
    for(i=0; i<7; i++) {
        mdl = &lbl_1_bss_10C[i+7];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[i+5], HU_MEMNUM_OVL, HEAP_MODEL));
        fn_1_1320(mdl);
        Hu3DModelLayerSet(mdl->modelId, 4);
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<60; i++) {
        mdl = &lbl_1_bss_10C[i+17];
        if(i == 0) {
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[12], HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            mdl->modelId = Hu3DModelLink(lbl_1_bss_B1C.models[17].modelId);
        }
        fn_1_1320(mdl);
        Hu3DModelLayerSet(mdl->modelId, 4);
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelScaleSet(mdl->modelId, 6.0f, 6.0f, 6.0f);
    }
    mdl = &lbl_1_bss_10C[77];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_4[13], HU_MEMNUM_OVL, HEAP_MODEL));
    fn_1_1320(mdl);
    Hu3DModelLayerSet(mdl->modelId, 3);
    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
}
