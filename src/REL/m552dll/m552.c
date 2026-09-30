/*
 * m552dll -- a KETTOU duel (overlay #66): the sequence hooks, cameras, the
 * block and board models, the digit sprites and the model flush. Written from
 * the reference assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m552dll/asm/REL/m552dll/m552.s.
 *
 * The [m5xx ...] tags name a built twin; "=" is instruction-identical
 * (symbol-normalized), "~" is the same function with this overlay's changes.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/hsfformat.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/esprite.h"
#include "game/mgdata.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"

#include "REL/m552dll/m552.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include "humath.h"

void ObjectSetup(void);
void fn_1_148(s16 mode, s16 frameNo);
void fn_1_524(s16 mode, s16 frameNo);
void fn_1_568(s16 mode, s16 frameNo);
void fn_1_620(s16 mode, s16 frameNo);
void fn_1_664(s16 mode, s16 frameNo);
void fn_1_69C(s16 mode, s16 frameNo);
void fn_1_6E0(s16 mode, s16 frameNo);
void fn_1_700(s16 mode, s16 frameNo);
void fn_1_730(s16 mode, s16 frameNo);
void fn_1_734(void);
void fn_1_AE8(s16 layerNo);
void fn_1_B20(void);
void fn_1_132C(int player);
void fn_1_14D0(M552_SLOT *slot);
void fn_1_15A4(OMOBJ *obj);
void fn_1_188C(void);
void fn_1_18E8(void);
void fn_1_1914(HU3DMODEL *model, Mtx *mtx);

/* --- .data --- */

/* files/data/m552.bin 0x00..0x2F: stage 0-5, blocks 6-9, board blocks 10-13, props 14-24, counters 25-30, 31-34, faces 35-47. */
unsigned int lbl_1_data_0[48] = {
    0x006E0000, 0x006E0001, 0x006E0002, 0x006E0003, 0x006E0004, 0x006E0005,
    0x006E0006, 0x006E0007, 0x006E0008, 0x006E0009, 0x006E000A, 0x006E000B,
    0x006E000C, 0x006E000D, 0x006E000E, 0x006E000F, 0x006E0010, 0x006E0011,
    0x006E0012, 0x006E0013, 0x006E0014, 0x006E0015, 0x006E0016, 0x006E0017,
    0x006E0018, 0x006E0019, 0x006E001A, 0x006E001B, 0x006E001C, 0x006E001D,
    0x006E001E, 0x006E001F, 0x006E0020, 0x006E0021, 0x006E0022, 0x006E0023,
    0x006E0024, 0x006E0025, 0x006E0026, 0x006E0027, 0x006E0028, 0x006E0029,
    0x006E002A, 0x006E002B, 0x006E002C, 0x006E002D, 0x006E002E, 0x006E002F
};

/* The digit sprites, ten per colour. */
unsigned int lbl_1_data_C0[40] = {
    0x006E0030, 0x006E0031, 0x006E0032, 0x006E0033, 0x006E0034,
    0x006E0035, 0x006E0036, 0x006E0037, 0x006E0038, 0x006E0039,
    0x006E0044, 0x006E0045, 0x006E0046, 0x006E0047, 0x006E0048,
    0x006E0049, 0x006E004A, 0x006E004B, 0x006E004C, 0x006E004D,
    0x006E004E, 0x006E004F, 0x006E0050, 0x006E0051, 0x006E0052,
    0x006E0053, 0x006E0054, 0x006E0055, 0x006E0056, 0x006E0057,
    0x006E003A, 0x006E003B, 0x006E003C, 0x006E003D, 0x006E003E,
    0x006E003F, 0x006E0040, 0x006E0041, 0x006E0042, 0x006E0043
};

/* Two motions per character, in charNo order. */
unsigned int lbl_1_data_160[13][2] = {
    { 0x008C0000, 0x008C0002 },
    { 0x00330000, 0x00330002 },
    { 0x00B70000, 0x00B70002 },
    { 0x00ED0000, 0x00ED0002 },
    { 0x00E60000, 0x00E60002 },
    { 0x00170000, 0x00170002 },
    { 0x00E00000, 0x00E00002 },
    { 0x008C0000, 0x008C0002 },
    { 0x008C0000, 0x008C0002 },
    { 0x008C0000, 0x008C0002 },
    { 0x008C0000, 0x008C0002 },
    { 0x008C0000, 0x008C0002 },
    { 0x008C0000, 0x008C0002 }
};

MGSEQ_PARAM lbl_1_data_1C8 = {
    0, 0,
    fn_1_148,
    fn_1_524,
    fn_1_568,
    fn_1_620,
    fn_1_664,
    fn_1_69C,
    fn_1_6E0,
    fn_1_700,
    fn_1_730
};

/* Sub-state tables, indexed by lbl_1_bss_4794.mode[0]. */
void (*lbl_1_data_1F0[4])(void) = { fn_1_1C40, fn_1_1FF4, fn_1_2180, fn_1_26BC };
void (*lbl_1_data_200[3])(void) = { fn_1_27B4, fn_1_2890, fn_1_2930 };
void (*lbl_1_data_20C[1])(void) = { fn_1_2E48 };

char *lbl_1_data_240[4] = { "m552score01", "m552score02", "m552score03", "m552score04" };

char *lbl_1_data_320[13] = {
    "TL32m552chara01", "TL32m552chara02", "TL32m552chara03", "TL32m552chara04",
    "TL32m552chara05", "TL32m552chara06", "TL32m552chara07", "TL32m552chara08",
    "TL32m552chara09", "TL32m552chara10", "TL32m552chara11", "TL32m552chara12",
    "TL32m552chara13"
};

/* .data:0x354 "m552count01" is a literal in fn_1_B20. */

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

M552_WORK lbl_1_bss_4794;
M552_FIELD lbl_1_bss_3700;
HU3DTEXSCRID lbl_1_bss_36E2[2][7];
HUSPRID lbl_1_bss_33C2[2][200];     /* [player][popup*50 + digit*10 + value] */
HUSPRID lbl_1_bss_33C0;
M552_SLOT lbl_1_bss_1340[208];
M552_SLOT lbl_1_bss_1200[8];
M552_SLOT lbl_1_bss_710[70];
M552_SLOT lbl_1_bss_530[12];
M552_SLOT lbl_1_bss_490[4];
M552_MODEL lbl_1_bss_84[M552_MODEL_MAX];
OMCAMERAVIEW lbl_1_bss_14[4];
HU3DMOTID lbl_1_bss_C[2][2];
u8 lbl_1_bss_A;                     /* fn_1_1914's quad alpha */
HU3DMODELID lbl_1_bss_8;            /* fn_1_1914's hook model */
OMOBJ *lbl_1_bss_4;                 /* omOutViewMulti */
int lbl_1_bss_0;                    /* MgSubModeGet */

/* asm 47-83, 42 insns. [m554 ~ObjectSetup] */
void ObjectSetup(void)
{
    s16 i;

    for(i=0; i<M552_MODEL_MAX; i++) {
        lbl_1_bss_84[i].modelId = HU3D_MODELID_NONE;
    }
    fn_1_B33C(&lbl_1_bss_4794, lbl_1_bss_84, lbl_1_data_0);
    lbl_1_bss_4794.objman = omInitObjMan(50, 0x2000);
    omGameSysInit(lbl_1_bss_4794.objman);
    MgSeqCreate(&lbl_1_data_1C8);
}

/* asm 84-224, 247 insns. MGSEQ init hook. [m554 ~fn_1_1C0] */
void fn_1_148(s16 mode, s16 frameNo)
{
    HuVecF shadowPos;
    HuVecF shadowUp;
    HuVecF shadowTarget;
    HU3DLIGHTID lightId;

    fn_1_B588(0);
    fn_1_7888();
    fn_1_B810(lbl_1_data_160[lbl_1_bss_4794.chr[0].charNo], lbl_1_data_160[lbl_1_bss_4794.chr[1].charNo]);
    fn_1_B834(lbl_1_bss_C[0], lbl_1_bss_C[1]);
    fn_1_B858();
    fn_1_BF98();
    omAddObjEx(lbl_1_bss_4794.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_C14C);
    fn_1_B20();
    fn_1_734();
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(lbl_1_bss_4794.objman, 0x7FDA, 0, 0, OM_GRP_NONE, fn_1_15A4);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    shadowPos.x = 0.0f;
    shadowPos.y = 3600.0f;
    shadowPos.z = -10.0f;
    shadowUp.x = 0.0f;
    shadowUp.y = 1.0f;
    shadowUp.z = 0.0f;
    shadowTarget.x = 0.0f;
    shadowTarget.y = 0.0f;
    shadowTarget.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
    Hu3DModelShadowSet(lbl_1_bss_4794.models[0].modelId);
    Hu3DModelShadowSet(lbl_1_bss_4794.models[1].modelId);
    Hu3DModelShadowMapSet(lbl_1_bss_4794.models[2].modelId);
    lbl_1_bss_4794.player[0].motNo = 1;
    lbl_1_bss_4794.player[0].speed = 1.0f;
    lbl_1_bss_4794.player[0].time = 0.0f;
    lbl_1_bss_4794.player[0].attr = HU3D_MOTATTR_LOOP;
    lbl_1_bss_4794.player[1].motNo = 1;
    lbl_1_bss_4794.player[1].speed = 1.0f;
    lbl_1_bss_4794.player[1].time = 0.0f;
    lbl_1_bss_4794.player[1].attr = HU3D_MOTATTR_LOOP;
    lbl_1_bss_3700.board[0].cursor.x = -400.0f;
    lbl_1_bss_3700.board[1].cursor.x = 400.0f;
    lbl_1_bss_3700.board[0].cursor.y = 0.0f;
    lbl_1_bss_3700.board[1].cursor.y = 0.0f;
    lbl_1_bss_3700.board[0].cursor.z = 125.0f;
    lbl_1_bss_3700.board[1].cursor.z = 125.0f;
    MgSeqModeDelaySet(mode+1, -1);
    MgSeqModeNext();
    lbl_1_bss_0 = MgSubModeGet();
}

/* asm 225-240, 17 insns. MGSEQ fade-in hook, dispatches data_1F0. [m550 =M550FadeInHook] */
void fn_1_524(s16 mode, s16 frameNo)
{
    lbl_1_data_1F0[lbl_1_bss_4794.mode[0]]();
}

/* asm 241-278, 46 insns. MGSEQ start hook: the timer by sub-mode, and the queue's first frame. */
void fn_1_568(s16 mode, s16 frameNo)
{
    lbl_1_bss_4794.mode[0] = 0;
    lbl_1_bss_4794.mode[1] = 0;
    if(mgSubMode == 1) {
        MgTimerParamSet(lbl_1_bss_490C, 10800, 0, 0);
    }
    if(mgSubMode == 2) {
        MgTimerParamSet(lbl_1_bss_490C, 18000, 0, 0);
    }
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_88EC();
}

/* asm 279-294, 17 insns. MGSEQ main hook, dispatches data_200. [m550 =M550MainHook] */
void fn_1_620(s16 mode, s16 frameNo)
{
    lbl_1_data_200[lbl_1_bss_4794.mode[0]]();
}

/* asm 295-310, 14 insns. MGSEQ finish hook. [m554 ~fn_1_958] */
void fn_1_664(s16 mode, s16 frameNo)
{
    MgSeqModeDelaySet(mode+1, -1);
    fn_1_2AA0();
}

/* asm 311-326, 17 insns. MGSEQ pre-winner hook, dispatches data_20C. [m550 =M550PreWinnerHook] */
void fn_1_69C(s16 mode, s16 frameNo)
{
    lbl_1_data_20C[lbl_1_bss_4794.mode[0]]();
}

/* asm 327-336, 8 insns. MGSEQ winner hook. */
void fn_1_6E0(s16 mode, s16 frameNo)
{
    MgSeqModeNext();
}

/* asm 337-351, 12 insns. MGSEQ fade-out hook. */
void fn_1_700(s16 mode, s16 frameNo)
{
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
}

/* asm 352-354, 1 insn. MGSEQ close hook. */
void fn_1_730(s16 mode, s16 frameNo)
{
}

/* asm 355-488, 237 insns. The split-screen view object and cameras 0-2. */
void fn_1_734(void)
{
    int camBit[5] = { HU3D_CAM0, HU3D_CAM1, HU3D_CAM2, HU3D_CAM3, HU3D_CAM4 };
    int i;

    lbl_1_bss_4 = omAddObjEx(lbl_1_bss_4794.objman, 0x7FDA, 0, 0, OM_GRP_NONE, omOutViewMulti);
    lbl_1_bss_4->work[0] = 3;
    lbl_1_bss_14[0].center.x = 0.0f;
    lbl_1_bss_14[0].center.y = 500.0f;
    lbl_1_bss_14[0].center.z = 0.0f;
    lbl_1_bss_14[0].rot.x = 0.0f;
    lbl_1_bss_14[0].rot.y = 0.0f;
    lbl_1_bss_14[0].rot.z = 0.0f;
    lbl_1_bss_14[0].zoom = 300.0f;
    lbl_1_bss_14[1].center.x = 0.0f;
    lbl_1_bss_14[1].center.y = 0.0f;
    lbl_1_bss_14[1].center.z = 0.0f;
    lbl_1_bss_14[1].rot.x = 0.0f;
    lbl_1_bss_14[1].rot.y = 0.0f;
    lbl_1_bss_14[1].rot.z = 0.0f;
    lbl_1_bss_14[1].zoom = 1950.0f;
    Hu3DCameraCreate(HU3D_CAM0|HU3D_CAM1|HU3D_CAM2|HU3D_CAM3|HU3D_CAM4);
    for(i=0; i<3; i++) {
        Hu3DCameraPerspectiveSet(camBit[i], 45.0f, 20.0f, 50000.0f, 1.2f);
        Hu3DCameraViewportSet(camBit[i], 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(camBit[i], 0, 0, 640, 480);
        CenterM[i].x = 0.0f;
        CenterM[i].y = 0.0f;
        CenterM[i].z = 500.0f;
        CRotM[i].x = -20.0f;
        CRotM[i].y = 0.0f;
        CRotM[i].z = 0.0f;
        CZoomM[i] = 900.0f;
    }
    Hu3DLayerHookSet(11, fn_1_AE8);
    fn_1_91BC();
}

/* asm 489-503, 14 insns. Layer 11's hook: clear Z under camera 2. */
void fn_1_AE8(s16 layerNo)
{
    if(Hu3DCameraBit & HU3D_CAM2) {
        Hu3DZClear();
    }
}

/*
 * asm 504-973, 515 insns. The props (models 8-18), each colour's 40 queue and
 * 12 board block models (bss_1340) with their two extra (bss_1200) and one
 * shadow source (bss_490), the counters (models 19-30), models 31-34 and the
 * faces (35-36), then both duellists' digit sprites.
 */
void fn_1_B20(void)
{
    HuVecF posTbl[11] = {
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.0f, 0.0f },
        { -400.0f, 0.0f, 125.0f },
        { 400.0f, 0.0f, 125.0f },
        { -400.0f, 0.0f, 125.0f },
        { 400.0f, 0.0f, 125.0f },
        { -400.0f, 0.0f, 125.0f },
        { 400.0f, 0.0f, 125.0f },
        { 0.0f, 0.0f, 0.0f }
    };
    M552_MODEL *mdl;
    int i;
    M552_SLOT *slot;
    int j;

    for(i=0; i<11; i++) {
        mdl = &lbl_1_bss_84[i+8];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+14], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        if(i >= 4 && i < 10) {
            Hu3DModelCameraSet(mdl->modelId, HU3D_CAM2);
            if(i == 4 || i == 5) {
                Hu3DModelLayerSet(mdl->modelId, 4);
            } else {
                Hu3DModelLayerSet(mdl->modelId, 5);
            }
        } else {
            Hu3DModelCameraSet(mdl->modelId, HU3D_CAM0);
        }
        Hu3DModelPosSetV(mdl->modelId, &posTbl[i]);
        mdl->pos.x = posTbl[i].x;
        mdl->pos.y = posTbl[i].y;
        mdl->pos.z = posTbl[i].z;
        mdl->rot.x = 0.0f;
        mdl->rot.y = 0.0f;
        mdl->rot.z = 0.0f;
        if(i == 0 || i == 1) {
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
        } else {
            Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
        }
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelAttrReset(mdl->modelId, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<4; i++) {
        slot = &lbl_1_bss_1340[i*40];
        for(j=0; j<40; j++, slot++) {
            if(j == 0) {
                slot->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+6], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                slot->modelId = Hu3DModelLink(lbl_1_bss_1340[i*40].modelId);
            }
            Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(slot->modelId, HU3D_CAM0);
            slot->pos.z = -100.0f;
        }
        slot = &lbl_1_bss_1340[(i*12)+160];
        for(j=0; j<12; j++, slot++) {
            if(j == 0) {
                slot->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+10], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                slot->modelId = Hu3DModelLink(lbl_1_bss_1340[(i*12)+160].modelId);
            }
            Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(slot->modelId, HU3D_CAM1);
            slot->pos.z = -100.0f;
        }
        slot = &lbl_1_bss_1200[i*2];
        for(j=0; j<2; j++, slot++) {
            slot->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+10], HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelCameraSet(slot->modelId, HU3D_CAM0);
            Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
        }
        slot = &lbl_1_bss_490[i];
        slot->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+6], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(slot->modelId, HU3D_CAM0);
        Hu3DModelAttrSet(slot->modelId, HU3D_ATTR_DISPOFF);
        slot->pos.z = -100.0f;
    }
    for(i=0; i<2; i++) {
        for(j=0; j<6; j++) {
            mdl = &lbl_1_bss_84[19+(i*6)+j];
            if(i == 0) {
                mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[j+25], HU_MEMNUM_OVL, HEAP_MODEL));
            } else {
                mdl->modelId = Hu3DModelLink((lbl_1_bss_4794.models+19)[j].modelId);
            }
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(mdl->modelId, HU3D_CAM0);
            Hu3DModelPosSet(mdl->modelId, (i*1020)-510, 0.0f, 0.0f);
            mdl->pos.x = (i*1020)-510;
            mdl->pos.y = 0.0f;
            mdl->pos.z = 0.0f;
            lbl_1_bss_36E2[i][j] = Hu3DTexScrollCreate(mdl->modelId, "m552count01");
        }
    }
    for(i=0; i<4; i++) {
        mdl = &lbl_1_bss_84[i+31];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[i+31], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, HU3D_CAM0);
        Hu3DModelPosSet(mdl->modelId, 0.0f, 0.0f, 0.0f);
        mdl->pos.x = 0.0f;
        mdl->pos.y = 0.0f;
        mdl->pos.z = 0.0f;
    }
    for(i=0; i<2; i++) {
        mdl = &lbl_1_bss_84[i+35];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_0[lbl_1_bss_4794.chr[i].charNo+35], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelCameraSet(mdl->modelId, HU3D_CAM0);
        Hu3DModelPosSet(mdl->modelId, (i*800)-400, 0.0f, 0.0f);
        mdl->pos.x = (i*800)-400;
        mdl->pos.y = 0.0f;
        mdl->pos.z = 0.0f;
        lbl_1_bss_36E2[i][6] = Hu3DTexScrollCreate(mdl->modelId, lbl_1_data_320[lbl_1_bss_4794.chr[i].charNo]);
    }
    for(i=0; i<2; i++) {
        fn_1_132C(i);
    }
}

/*
 * asm 974-1079, 105 insns. One duellist's popup digits: four popups of five
 * digits in each colour's ten (the first digit only 0-3), hidden; and the
 * shared sprite bss_33C0.
 */
void fn_1_132C(int player)
{
    int k;
    int i;
    int j;

    for(i=0; i<4; i++) {
        for(j=0; j<5; j++) {
            for(k=0; k<10; k++) {
                lbl_1_bss_33C2[player][k+((i*50)+(j*10))] = -1;
                if(j != 0 || k < 4) {
                    lbl_1_bss_33C2[player][k+((i*50)+(j*10))] = espEntry(lbl_1_data_C0[k+(i*10)], 210, 0);
                    espDispOff(lbl_1_bss_33C2[player][k+((i*50)+(j*10))]);
                    espDrawNoSet(lbl_1_bss_33C2[player][k+((i*50)+(j*10))], 0);
                }
            }
        }
    }
    lbl_1_bss_33C0 = espEntry(0x6E0058, 15, 0);
    espDispOff(lbl_1_bss_33C0);
}

/* asm 1080-1132, 53 insns. Fade a cleared block out over 20 frames (inlined into fn_1_15A4). */
void fn_1_14D0(M552_SLOT *slot)
{
    float alpha;
    HU3DMODEL *modelP = &Hu3DData[slot->modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    slot->timer++;
    alpha = slot->timer;
    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha/20.0f;
    }
    if(slot->timer == 20) {
        slot->mode = 0;
    }
}

/* asm 1133-1288, 155 insns. Object main installed by fn_1_148: the model flush. */
void fn_1_15A4(OMOBJ *obj)
{
    M552_MODEL *mdl;
    M552_SLOT *slot;
    int i;

    mdl = lbl_1_bss_84;
    slot = lbl_1_bss_1340;
    for(i=0; i<M552_MODEL_MAX; i++, mdl++) {
        if(mdl->modelId >= 0) {
            Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
            Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
        }
    }
    for(i=0; i<208; i++, slot++) {
        if(slot->mode != 0) {
            Hu3DModelPosSetV(slot->modelId, &slot->pos);
            Hu3DModelRotSetV(slot->modelId, &slot->rot);
            if(slot->mode != 3) {
                slot->timer++;
            }
            if(slot->timer == 100) {
                Hu3DMotionTimeSet(slot->modelId, 0.0f);
                slot->timer = 0;
            }
        }
    }
    slot = lbl_1_bss_710;
    for(i=0; i<70; i++, slot++) {
        if(slot->mode != 0) {
            Hu3DModelPosSetV(slot->modelId, &slot->pos);
            Hu3DModelRotSet(slot->modelId, 0.0f, 0.0f, 0.0f);
            if(slot->mode == 2) {
                fn_1_14D0(slot);
                if(slot->mode == 0) {
                    Hu3DModelKill(slot->modelId);
                    slot->timer = 0;
                }
            }
        }
    }
    slot = lbl_1_bss_530;
    for(i=0; i<12; i++, slot++) {
        if(slot->mode != 0) {
            Hu3DModelPosSetV(slot->modelId, &slot->pos);
            Hu3DModelRotSetV(slot->modelId, &slot->rot);
        }
    }
}

/* asm 1289-1320, 31 insns. [m550 =M550MatAlphaSet] */
void fn_1_1810(int mdlNo, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[lbl_1_bss_4794.models[mdlNo].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}

/* asm 1321-1338, 23 insns. The full-screen quad (drawn by fn_1_1914, alpha bss_A). [m542 ~fn_1_249C] */
void fn_1_188C(void)
{
    lbl_1_bss_8 = Hu3DHookFuncCreate(fn_1_1914);
    Hu3DModelLayerSet(lbl_1_bss_8, 5);
    Hu3DModelCameraSet(lbl_1_bss_8, HU3D_CAM0);
}

/* asm 1339-1349, 11 insns. [m542 =fn_1_24F8] */
void fn_1_18E8(void)
{
    Hu3DModelKill(lbl_1_bss_8);
}

/* asm 1350-1526, 203 insns. Hook draw: a black full-screen quad at alpha bss_A. [m542 ~fn_1_2524] */
void fn_1_1914(HU3DMODEL *model, Mtx *mtx)
{
    GXColor color = { 0, 0, 0, 0 };
    Mtx44 proj;

    color.a = lbl_1_bss_A;
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

