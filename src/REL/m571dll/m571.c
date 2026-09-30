/*
 * m571dll -- a Donkey Kong minigame (MG_TYPE_DONKEY, overlay #82).
 *
 * Every function is written from the reference assembly, in reference order.
 * Line ranges are into build/mp5-asm/m571dll/asm/REL/m571dll/m571.s.
 *
 * Shape: seqman (MgSeqCreatePrio, lbl_1_data_D48) + MgActor players
 * (MgActorObjectSetup, MgPlayerCreate) + own OMOBJ groups, one TU of three
 * parts:
 *
 *  - ObjectSetup..fn_1_3944: this overlay's own code, below.
 *  - fn_1_3D94..fn_1_4C78: the shared helper block, instruction-identical
 *    to REL/m563dll/math.c. Included; already written.
 *  - fn_1_4D3C..fn_1_9350: the Donkey Kong host, shared with m573dll. In
 *    host.c with its data and bss; W2 ports it from m573.c.
 *
 * Emission order (measured on m559dll, and here): CodeWarrior emits this
 * file's own functions first, then those of the #included files in include
 * order. So math.c and host.c are included up top and still land after
 * fn_1_3944, in the reference order.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfex.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/mg/actman.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/wipe.h"

#include "datadir_enum.h"

#include "dolphin/mtx.h"
#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

/* Object manager. Declared ahead of the includes because host.c uses it;
 * its address sits between math.c's bss_650..674 and bss_684. */
OMOBJMAN *lbl_1_bss_680;

#include "REL/m563dll/math.c"
#include "REL/m571dll/host.c"

/* 0x8C bytes per player (group 0; fn_1_BF4 init, fn_1_D58 main). */
typedef struct M571Player_s {
    /* 0x00 */ s32 playerNo;
    /* 0x04 */ s32 charNo;
    /* 0x08 */ s32 padNo;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u16 unk16;
    /* 0x18 */ HuVecF pos;         /* fn_1_1264's first argument */
    /* 0x24 */ HuVecF unk24;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 pad32;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 unk40[0x08];
    /* 0x48 */ float unk48;
    /* 0x4C */ u8 unk4C[0x10];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 mode;
    /* 0x64 */ HuVecF target;      /* fn_1_1264's second argument */
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ s32 unk88;
} M571_PLAYER;                     /* 0x8C */

/* 0x34 bytes: one results line-up character (group 3; fn_1_3700). */
typedef struct M571Result_s {
    /* 0x00 */ s16 motNo;
    /* 0x02 */ HU3DMOTID motId[3];   /* the first three of lbl_1_data_1A4 */
    /* 0x08 */ HU3DMODELID mdlId;
    /* 0x0A */ s16 padA;
    /* 0x0C */ HuVecF pos;
    /* 0x18 */ HuVecF rot;
    /* 0x24 */ s32 playerNo;
    /* 0x28 */ s32 charNo;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
} M571_RESULT;                     /* 0x34 */

/* 0x14 bytes (fn_1_1D44 spawns; fn_1_1F74/fn_1_2088 run). */
typedef struct M571Eff14_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} M571_EFF14;

/* 0x3C bytes (fn_1_21DC/fn_1_2FE0 spawn; fn_1_2388/fn_1_2468 run). */
typedef struct M571Block_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF scale;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ float unk34;
    /* 0x38 */ s32 unk38;
} M571_BLOCK;

/* 0x10 bytes (fn_1_2F04 spawns; fn_1_3594/fn_1_36B8 run). */
typedef struct M571Cell_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ s32 no;
} M571_CELL;

void ObjectSetup(void);
void fn_1_68C(OMOBJ *obj);
void fn_1_BF4(OMOBJ *obj);
void fn_1_D58(OMOBJ *obj);
void fn_1_1078(OMOBJ *obj);
s32 fn_1_1168(OMOBJ *obj);
s32 fn_1_1264(HuVecF *pos, HuVecF *out);
void fn_1_1518(s16 mode, s16 frameNo);
void fn_1_1630(s16 mode, s16 frameNo);
void fn_1_16F4(s16 mode, s16 frameNo);
void fn_1_1760(s16 mode, s16 frameNo);
void fn_1_1898(OMOBJ *obj);
void fn_1_18B8(s16 mode, s16 frameNo);
void fn_1_1BA0(s16 mode, s16 frameNo);
void fn_1_1D44(s32 cellNo);
void fn_1_1F00(OMOBJ *obj);
void fn_1_1F74(OMOBJ *obj);
void fn_1_2088(OMOBJ *obj);
void fn_1_21DC(float x, float y, float z, s32 type, s32 cellNo, s32 playerNo);
void fn_1_231C(OMOBJ *obj);
void fn_1_2388(OMOBJ *obj);
void fn_1_2468(OMOBJ *obj);
void fn_1_27E8(OMOBJ *obj, s32 motNo, float time, s32 attr);
void fn_1_2870(s32 attrF);
s32 fn_1_28F4(HuVecF *pos);
s32 fn_1_2A14(OMOBJ *obj, s32 arg);
void fn_1_2D54(void);
void fn_1_2D58(void);
void fn_1_2E28(void);
void fn_1_2F04(float x, float y, float z, s32 kind, s32 no);
s32 fn_1_2FE0(OMOBJ *obj, s32 playerNo);
void fn_1_3520(void);
void fn_1_3594(OMOBJ *obj);
void fn_1_36B8(OMOBJ *obj);
void fn_1_3700(OMOBJ *obj);
void fn_1_38E8(OMOBJ *obj);
void fn_1_3944(void);

/* --- .data:0x1A4.. --- */

/* Result line-up motions. */
u32 lbl_1_data_1A4[5] = { 0x008C0000, 0x008C0006, 0x008C0031, 0x008C0001, 0x008C0002 };

OMCAMERAVIEW lbl_1_data_1B8 = { { 0.0f, 221.5f, -500.0f }, { 4.4f, 0.0f, 0.0f }, 526.0f };
OMCAMERAVIEW lbl_1_data_1D4 = { { 0.0f, 221.9f, 268.8f }, { -27.8f, 0.9f, 0.0f }, 1749.0f };
OMCAMERAVIEW lbl_1_data_1F0 = { { 0.0f, 221.5f, -500.0f }, { 4.4f, 0.0f, 0.0f }, 1200.0f };

/* Player start positions (fn_1_68C). */
HuVecF lbl_1_data_20C[4] = {
    { -475.0f, 50.0f, -470.0f }, { 475.0f, 50.0f, -470.0f },
    { -400.0f, 50.0f, 470.0f }, { 400.0f, 50.0f, 470.0f }
};

/* Result line-up positions (fn_1_3700). */
HuVecF lbl_1_data_23C[4] = {
    { -240.0f, 0.0f, -450.0f }, { -80.36f, 0.0f, -450.0f },
    { 80.36f, 0.0f, -450.0f }, { 240.66f, 0.0f, -450.0f }
};

/* The floor: a seven by seven grid of 120-unit cells, row-major, z outermost. */
HuVecF lbl_1_data_26C[49] = {
    { -360.0f, 0.0f, -360.0f }, { -240.0f, 0.0f, -360.0f }, { -120.0f, 0.0f, -360.0f }, { 0.0f, 0.0f, -360.0f },
    { 120.0f, 0.0f, -360.0f }, { 240.0f, 0.0f, -360.0f }, { 360.0f, 0.0f, -360.0f },
    { -360.0f, 0.0f, -240.0f }, { -240.0f, 0.0f, -240.0f }, { -120.0f, 0.0f, -240.0f }, { 0.0f, 0.0f, -240.0f },
    { 120.0f, 0.0f, -240.0f }, { 240.0f, 0.0f, -240.0f }, { 360.0f, 0.0f, -240.0f },
    { -360.0f, 0.0f, -120.0f }, { -240.0f, 0.0f, -120.0f }, { -120.0f, 0.0f, -120.0f }, { 0.0f, 0.0f, -120.0f },
    { 120.0f, 0.0f, -120.0f }, { 240.0f, 0.0f, -120.0f }, { 360.0f, 0.0f, -120.0f },
    { -360.0f, 0.0f, 0.0f }, { -240.0f, 0.0f, 0.0f }, { -120.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f },
    { 120.0f, 0.0f, 0.0f }, { 240.0f, 0.0f, 0.0f }, { 360.0f, 0.0f, 0.0f },
    { -360.0f, 0.0f, 120.0f }, { -240.0f, 0.0f, 120.0f }, { -120.0f, 0.0f, 120.0f }, { 0.0f, 0.0f, 120.0f },
    { 120.0f, 0.0f, 120.0f }, { 240.0f, 0.0f, 120.0f }, { 360.0f, 0.0f, 120.0f },
    { -360.0f, 0.0f, 240.0f }, { -240.0f, 0.0f, 240.0f }, { -120.0f, 0.0f, 240.0f }, { 0.0f, 0.0f, 240.0f },
    { 120.0f, 0.0f, 240.0f }, { 240.0f, 0.0f, 240.0f }, { 360.0f, 0.0f, 240.0f },
    { -360.0f, 0.0f, 360.0f }, { -240.0f, 0.0f, 360.0f }, { -120.0f, 0.0f, 360.0f }, { 0.0f, 0.0f, 360.0f },
    { 120.0f, 0.0f, 360.0f }, { 240.0f, 0.0f, 360.0f }, { 360.0f, 0.0f, 360.0f },
};

/*
 * .data:0x530, three 7x7 layouts nothing references (dtk folds them into
 * data_26C because they have no label). Values 0/1/5 only.
 */
s32 lbl_1_data_530[3][49] = {
    { 1,0,1,0,1,1,1, 0,1,5,1,0,1,0, 1,1,0,0,1,5,1, 1,0,1,1,1,0,1, 0,1,0,1,5,0,1, 1,5,1,0,1,1,1, 1,1,0,1,1,0,1 },
    { 0,1,0,1,1,1,1, 0,1,1,0,1,0,5, 1,1,1,1,0,1,0, 5,1,0,0,1,1,1, 1,1,1,1,1,1,5, 0,1,1,0,1,0,1, 1,1,0,5,0,1,0 },
    { 1,1,1,0,0,0,0, 1,0,0,1,1,1,1, 5,0,1,5,1,1,1, 1,0,1,1,1,0,1, 0,1,5,1,0,5,1, 0,1,1,1,1,0,1, 1,0,0,1,1,1,1 },
};

/*
 * The eight layouts fn_1_2E28 picks from (frandmod(8) into bss_8). Each
 * cell: -1 nothing, else the kind that stands on it (0, 1 or 5).
 */
s32 lbl_1_data_704[8][49] = {
    { -1,-1,-1,0,-1,-1,-1, -1,-1,5,1,0,-1,-1, -1,5,0,1,1,5,-1, 0,1,5,5,1,1,0, -1,5,0,1,5,5,-1, -1,-1,1,0,1,-1,-1, -1,-1,-1,1,-1,-1,-1 },
    { -1,-1,-1,5,-1,-1,-1, -1,-1,0,1,0,-1,-1, -1,0,5,1,5,1,-1, 5,1,0,1,0,1,5, -1,5,1,1,5,0,-1, -1,-1,1,5,1,-1,-1, -1,-1,-1,0,-1,-1,-1 },
    { 0,1,-1,5,-1,-1,0, 1,-1,5,1,-1,5,-1, 0,-1,0,1,1,-1,-1, 5,-1,1,0,5,-1,-1, 0,-1,0,1,0,-1,-1, 1,-1,1,5,-1,5,-1, 0,5,-1,1,-1,-1,0 },
    { 0,5,-1,1,-1,-1,1, 1,-1,0,5,-1,0,-1, 0,-1,1,5,1,-1,-1, 0,-1,5,0,0,-1,-1, 5,-1,0,1,1,-1,-1, 1,-1,0,1,-1,5,-1, 1,0,-1,5,-1,-1,5 },
    { -1,-1,-1,5,-1,-1,-1, -1,-1,5,1,0,-1,-1, -1,0,1,0,1,5,-1, 1,5,1,0,1,5,1, -1,-1,1,5,0,-1,-1, -1,-1,0,0,5,-1,-1, -1,-1,5,1,1,-1,-1 },
    { -1,-1,-1,0,-1,-1,-1, -1,-1,1,0,5,-1,-1, -1,1,5,1,5,1,-1, 5,0,1,5,0,1,1, -1,-1,5,0,5,-1,-1, -1,-1,1,5,0,-1,-1, -1,-1,1,0,1,-1,-1 },
    { -1,0,-1,-1,-1,0,-1, 0,1,5,-1,5,1,0, -1,1,-1,5,-1,5,-1, -1,-1,1,1,1,-1,-1, -1,5,-1,5,-1,1,-1, 0,5,0,-1,5,1,1, -1,1,-1,-1,-1,0,-1 },
    { -1,1,-1,-1,-1,5,-1, 5,5,0,-1,0,0,0, -1,0,-1,5,-1,0,-1, -1,-1,5,1,5,-1,-1, -1,1,-1,5,-1,1,-1, 1,0,1,-1,1,5,1, -1,1,-1,-1,-1,1,-1 },
};

HuVecF lbl_1_data_D24 = { -100.0f, 8000.0f, 0.0f };   /* shadow position */
HuVecF lbl_1_data_D30 = { 0.0f, 1.0f, 0.0f };         /* shadow up */
HuVecF lbl_1_data_D3C = { 0.0f, 0.0f, 0.0f };         /* shadow target */

/* No START, FADEOUT or CLOSE hook. */
MGSEQ_PARAM lbl_1_data_D48 = {
    10,
    MGSEQ_TIMER_TOP,
    fn_1_1518,
    fn_1_1630,
    NULL,
    fn_1_16F4,
    fn_1_1760,
    fn_1_18B8,
    fn_1_1BA0,
    NULL,
    NULL
};

/* .data:0xD70.. are literals: the two ObjectSetup OSReports and fn_1_3944's
 * six debug-camera print8 formats. */

/* --- .bss:0x0..0x35C --- */

OMOBJ *lbl_1_bss_0;                 /* stage object; stored in ObjectSetup, never read */
s32 lbl_1_bss_4;                    /* live M571_CELL objects (fn_1_2F04 caps at 0x30) */
s32 lbl_1_bss_8;                    /* layout number into lbl_1_data_704 */
HU3DMODELID lbl_1_bss_C;            /* M571_BLOCK model sources, linked in fn_1_2388 */
HU3DMODELID lbl_1_bss_E;
HU3DMODELID lbl_1_bss_10;           /* M571_EFF14 model source */
HU3DMODELID lbl_1_bss_12;           /* player stage model source (fn_1_68C) */
HU3DMODELID lbl_1_bss_14[100];      /* M571_CELL model source; only [0] referenced, dtk size 0xC8 */
MGPLAYER *lbl_1_bss_DC[4];
s32 lbl_1_bss_EC;                   /* live M571_BLOCK objects (caps at 0x30) */
s32 lbl_1_bss_F0;                   /* live M571_EFF14 objects (caps at 0x30) */
s16 lbl_1_bss_F4[49];               /* unreferenced; dtk folds it into bss_F0 */
HU3DMODELID lbl_1_bss_156[53];      /* MgActorColMapInit(lbl_1_bss_156, 51, 55) */
OMOBJ *lbl_1_bss_1C0;
OMOBJ *lbl_1_bss_1C4;
OMOBJ *lbl_1_bss_1C8[49];           /* one per floor cell */
OMOBJ *lbl_1_bss_28C[49];
OMOBJ **lbl_1_bss_350;              /* group 3: result line-up */
OMOBJ **lbl_1_bss_354;              /* group 0: players */
HU3DLIGHTID lbl_1_bss_358;

/* asm 61-447, 379 insns. */
void ObjectSetup(void)
{
    OMOBJ *obj;
    s32 i;
    s32 j;

    OSReport("******* M571 ObjectSetup *********\n");
    OSReport("SOUNDMODE:%d\n", OSGetSoundMode());
    lbl_1_bss_680 = MgActorObjectSetup();
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSet(&lbl_1_data_1B8);
    lbl_1_bss_1C4 = omAddObjEx(lbl_1_bss_680, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_358 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_358, &lbl_1_data_E4, &lbl_1_data_F0);
    Hu3DGLightStaticSet(lbl_1_bss_358, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_358);
    Hu3DGLightColorSet(lbl_1_bss_358, lbl_1_data_FC[0], lbl_1_data_FC[1], lbl_1_data_FC[2], lbl_1_data_FC[3]);
    Hu3DShadowCreate(10.0f, 10.0f, 10000.0f);
    Hu3DShadowColSet(16, 16, 16);
    Hu3DShadowPosSet(&lbl_1_data_D24, &lbl_1_data_D30, &lbl_1_data_D3C);
    Hu3DShadowTPLvlSet(0.6f);
    fn_1_2D58();
    lbl_1_bss_12 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_12, HU3D_ATTR_DISPOFF);
    lbl_1_bss_10 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 6), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_10, HU3D_ATTR_DISPOFF);
    for (i = 0; i < 49; i++) {
        lbl_1_bss_28C[i] = NULL;
    }
    lbl_1_bss_E = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_E, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_C, HU3D_ATTR_DISPOFF);
    lbl_1_bss_F0 = 0;
    lbl_1_bss_EC = 0;
    fn_1_2E28();
    lbl_1_bss_0 = omAddObjEx(lbl_1_bss_680, 102, 54, 0, -1, fn_1_68C);
    HuPrcVSleep();
    omMakeGroupEx(lbl_1_bss_680, 1, 4);
    lbl_1_bss_350 = omGetGroupMemberListEx(lbl_1_bss_680, 1);
    omMakeGroupEx(lbl_1_bss_680, 0, 4);
    lbl_1_bss_354 = omGetGroupMemberListEx(lbl_1_bss_680, 0);
    for (i = 0; i < 4; i++) {
        obj = omAddObjEx(lbl_1_bss_680, 100, 0, 0, 0, fn_1_BF4);
        lbl_1_bss_354[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_680, 5, 1);
    lbl_1_bss_478 = omGetGroupMemberListEx(lbl_1_bss_680, 5);
    obj = omAddObjEx(lbl_1_bss_680, 106, 0, 0, 5, fn_1_7670);
    lbl_1_bss_478[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_HOST), HU_MEMNUM_OVL);
    obj->work[0] = 0;
    lbl_1_bss_364 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_364, HU3D_ATTR_DISPOFF);
    for (j = 0; j < 20; j++) {
        lbl_1_bss_368[j] = NULL;
    }
    lbl_1_bss_35C = -1;
    fn_1_2870(0);
    MgSeqCreatePrio(&lbl_1_data_D48, 1000);
}

/* asm 450-805, 346 insns. Stage and MgPlayer setup, run once. */
void fn_1_68C(OMOBJ *obj)
{
    MGACTOR_PARAM param;
    HuVecF pos;
    s32 i;

    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[2] = lbl_1_bss_156[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    obj->mdlId[3] = lbl_1_bss_156[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 4), HU_MEMNUM_OVL, HEAP_MODEL));
    for (i = 0; i < 49; i++) {
        obj->mdlId[4 + i] = lbl_1_bss_156[2 + i] = Hu3DModelLink(lbl_1_bss_12);
        if (lbl_1_data_704[lbl_1_bss_8][i] == -1) {
            pos.y = -1000.0f;
        } else {
            pos.y = lbl_1_data_26C[i].y;
        }
        pos.x = lbl_1_data_26C[i].x;
        pos.z = lbl_1_data_26C[i].z;
        Hu3DModelPosSet(obj->mdlId[4 + i], pos.x, pos.y, pos.z);
    }
    param.height = 150.0f;
    param.radius = 50.0f;
    param.param = 0;
    param.type = 0;
    param.attr = 0;
    param.correctHookParam = 0;
    param.narrowHook = NULL;
    param.correctHook = NULL;
    MgActorColMapInit(lbl_1_bss_156, 51, 55);
    lbl_1_bss_DC[0] = MgPlayerCreate(0, &param, 4, 1, -3, NULL);
    param.param++;
    lbl_1_bss_DC[1] = MgPlayerCreate(1, &param, 4, 1, -3, NULL);
    param.param++;
    lbl_1_bss_DC[2] = MgPlayerCreate(2, &param, 4, 1, -3, NULL);
    param.param++;
    lbl_1_bss_DC[3] = MgPlayerCreate(3, &param, 4, 1, -3, NULL);
    param.param++;
    lbl_1_bss_DC[0]->actor->pos.x = lbl_1_data_20C[0].x;
    lbl_1_bss_DC[0]->actor->pos.y = lbl_1_data_20C[0].y;
    lbl_1_bss_DC[0]->actor->pos.z = lbl_1_data_20C[0].z;
    lbl_1_bss_DC[1]->actor->pos.x = lbl_1_data_20C[1].x;
    lbl_1_bss_DC[1]->actor->pos.y = lbl_1_data_20C[1].y;
    lbl_1_bss_DC[1]->actor->pos.z = lbl_1_data_20C[1].z;
    lbl_1_bss_DC[2]->actor->pos.x = lbl_1_data_20C[2].x;
    lbl_1_bss_DC[2]->actor->pos.y = lbl_1_data_20C[2].y;
    lbl_1_bss_DC[2]->actor->pos.z = lbl_1_data_20C[2].z;
    lbl_1_bss_DC[3]->actor->pos.x = lbl_1_data_20C[3].x;
    lbl_1_bss_DC[3]->actor->pos.y = lbl_1_data_20C[3].y;
    lbl_1_bss_DC[3]->actor->pos.z = lbl_1_data_20C[3].z;
    MgPlayerVibrateCreate(lbl_1_bss_DC[0]);
    MgPlayerVibrateCreate(lbl_1_bss_DC[1]);
    MgPlayerVibrateCreate(lbl_1_bss_DC[2]);
    MgPlayerVibrateCreate(lbl_1_bss_DC[3]);
    MgActorColCylSet();
    Hu3DModelShadowMapSet(obj->mdlId[0]);
    Hu3DModelAttrSet(obj->mdlId[1], 0x40000001);
    CharEffectLayerSet(5);
    Hu3DModelAttrSet(obj->mdlId[2], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[3], HU3D_ATTR_DISPOFF);
    for (i = 0; i < 49; i++) {
        Hu3DModelAttrSet(obj->mdlId[4 + i], HU3D_ATTR_DISPOFF);
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelShadowSet(lbl_1_bss_DC[i]->actor->mdlId);
    }
    obj->objFunc = NULL;
}

/* asm 808-904, 89 insns. Player init. */
void fn_1_BF4(OMOBJ *obj)
{
    M571_PLAYER *player;

    player = obj->data;
    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->unkC = 0;
    player->unk30 = 0;
    player->unk7C = 0;
    player->unk78 = 0;
    player->unk5C = GwPlayerConf[player->playerNo].dif;
    player->mode = 0;
    player->unk80 = 0;
    switch (player->unk5C) {
        case 0: {
            s32 delay = frandmod(20) + 60;
            player->unk84 = delay;
            player->unk88 = 2;
            break;
        }
        case 1: {
            s32 delay = frandmod(15) + 30;
            player->unk84 = delay;
            player->unk88 = 7;
            break;
        }
        case 2: {
            s32 delay = frandmod(15) + 10;
            player->unk84 = delay;
            player->unk88 = 15;
            break;
        }
        case 3: {
            s32 delay = frandmod(4) + 1;
            player->unk84 = delay;
            player->unk88 = 0;
            break;
        }
    }
    obj->objFunc = fn_1_D58;
}

/* asm 907-1112, 200 insns. Player main. */
void fn_1_D58(OMOBJ *obj)
{
    M571_PLAYER *player;
    HuVecF screen;
    s32 no;
    s32 pan;
    s32 pan2;
    s32 pan3;

    player = obj->data;
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        fn_1_2870(1);
        if (GwPlayerConf[player->playerNo].type != 0) {
            player->unk70 = 0;
            player->unk74 = 0;
            player->unk78 = 0;
            player->unk7C = 0;
            fn_1_1078(obj);
            MgPlayerPadSet(lbl_1_bss_DC[player->playerNo], player->unk70, player->unk74, player->unk78, player->unk7C);
        }
        player->unk10 = lbl_1_bss_DC[player->playerNo]->actor->colGroundAttr;
        player->unk14 = lbl_1_bss_DC[player->playerNo]->actor->colMesh;
        player->unk16 = lbl_1_bss_DC[player->playerNo]->mode;
        if (player->unk16 == 3) {
            if (player->pos.y < 190.0f && player->unk3C != 0) {
                player->unk34++;
                no = fn_1_2A14(obj, 0);
                if (no != -1) {
                    fn_1_2FE0(lbl_1_bss_1C8[no], player->playerNo);
                    fn_1_1D44(no);
                    omVibrate((s16)player->padNo, 15, 6, 6);
                    player->unk3C = 0;
                }
            }
        } else {
            player->unk34 = 0;
            player->unk3C = 1;
        }
    } else {
        fn_1_2870(0);
    }
    player->pos.x = lbl_1_bss_DC[player->playerNo]->actor->pos.x;
    player->pos.y = lbl_1_bss_DC[player->playerNo]->actor->pos.y;
    player->pos.z = lbl_1_bss_DC[player->playerNo]->actor->pos.z;
    player->unk24.x = 0.0f;
    player->unk24.y = lbl_1_bss_DC[player->playerNo]->actor->rotY;
    player->unk24.z = 0.0f;
    player->unk48 = lbl_1_bss_DC[player->playerNo]->actor->velY;
    Hu3D3Dto2D(&player->pos, 1, &screen);
    pan = 32.0f + ((screen.x / 576.0f) * 64.0f);
    pan2 = pan;
    pan3 = pan2;
    CharModelVoicePanSet((s16)player->charNo, pan3);
}

/* asm 1115-1183, 60 insns. */
void fn_1_1078(OMOBJ *obj)
{
    M571_PLAYER *player = obj->data;

    switch (player->mode) {
        case 0:
            if (fn_1_1264(&player->pos, &player->target) != 0) {
                player->mode = 1;
            } else {
                player->mode = 2;
            }
            break;
        case 1:
            if (fn_1_1168(obj) != 0) {
                player->mode = 2;
            } else if ((u32)(player->unk10 & 0xBF80) != 0) {
                player->unk78 |= 0x200;
            }
            break;
        case 2:
            player->unk80++;
            if (player->unk80 > player->unk84) {
                player->mode = 0;
                player->unk80 = 0;
            }
            break;
    }
}

/* asm 1186-1252, 63 insns. */
s32 fn_1_1168(OMOBJ *obj)
{
    M571_PLAYER *player;
    float lim;
    HuVecF v;
    HuVecF dir;

    lim = 3600.001f;
    player = obj->data;
    PSVECSubtract(&player->target, &player->pos, &v);
    v.y = 0.0f;
    if (PSVECSquareMag(&v) < lim) {
        return 1;
    }
    PSVECNormalize(&v, &v);
    dir.x = v.x;
    dir.y = v.z;
    player->unk70 = (s8)(56.0f * dir.x);
    player->unk74 = (s8)(56.0f * -dir.y);
    return 0;
}

/* asm 1255-1436, 173 insns. */
s32 fn_1_1264(HuVecF *pos, HuVecF *out)
{
    HuVecF best;
    float bestDist;
    float d;
    float dz;
    float dx;
    float d1;
    float ax;
    float az;
    float bx;
    float bz;
    float d2;
    float mag;
    s32 i;

    bestDist = 1000000.0f;
    for (i = 0; i < 49; i++) {
        if (lbl_1_bss_1C8[i] != NULL) {
            bz = lbl_1_data_26C[i].z;
            bx = lbl_1_data_26C[i].x;
            az = pos->z;
            ax = pos->x;
            dx = ax - bx;
            dz = az - bz;
            mag = HuMag2Point2D(dx, dz);
            d1 = sqrtf(mag);
            d2 = d1;
            d = d2;
            if (bestDist > d) {
                best.x = lbl_1_data_26C[i].x;
                best.y = lbl_1_data_26C[i].y;
                best.z = lbl_1_data_26C[i].z;
                bestDist = d;
            }
        }
    }
    if (1000000.0f != bestDist) {
        out->x = best.x;
        out->y = best.y;
        out->z = best.z;
        return 1;
    }
    return 0;
}

/* asm 1439-1514, 70 insns. MGSEQ init hook. */
void fn_1_1518(s16 mode, s16 frameNo)
{
    s32 charNo[4];
    M571_PLAYER *player;
    s32 i;
    s32 b;
    s32 c;
    s32 d;

    if (MgSeqFrameNoGet() == 0) {
        for (i = 0; i < 4; i++) {
            player = lbl_1_bss_354[i]->data;
            charNo[i] = player->charNo;
        }
        d = charNo[3];
        c = charNo[2];
        b = charNo[1];
        lbl_1_bss_43C[0] = charNo[0];
        lbl_1_bss_43C[1] = b;
        lbl_1_bss_43C[2] = c;
        lbl_1_bss_43C[3] = d;
        lbl_1_bss_438 = 0;
        omAddObjEx(lbl_1_bss_680, 101, 0, 0, -1, fn_1_7DF8);
    }
    if (WipeCheckEnd() == 0) {
        MgSeqModeNext();
        MgActorExec();
    }
    lbl_1_bss_35C = HuAudSStreamPlay(61);
}

/* asm 1517-1573, 49 insns. MGSEQ fade-in hook. */
void fn_1_1630(s16 mode, s16 frameNo)
{
    s32 i;
    M571_HOST *host;

    host = lbl_1_bss_478[0]->data;
    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    host->unk30 = 1;
    for(i=0; i<150; i++) {
        HuPrcVSleep();
    }
    omCameraViewMoveSimple(&lbl_1_data_1D4, 90);
    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    host->unk38 = 0;
    host->unk28 = 1300.0f;
    host->unk30 = 2;
    MgSeqModeNext();
}

/* asm 1576-1606, 27 insns. MGSEQ main hook. */
void fn_1_16F4(s16 mode, s16 frameNo)
{
    M571_HOST *host;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 0) {
        host->unk30 = 3;
    }
    fn_1_2D54();
    MgActorExec();
    if(lbl_1_bss_4 == 0) {
        MgSeqModeNext();
    }
}

/* asm 1609-1696, 78 insns. MGSEQ finish hook. */
void fn_1_1760(s16 mode, s16 frameNo)
{
    M571_PLAYER *player;
    s32 i;
    s32 j;
    s32 done;

    if(MgSeqFrameNoGet() == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_35C, 100);
        lbl_1_bss_1C0 = omAddObjEx(lbl_1_bss_680, 100, 0, 0, -1, fn_1_1898);
    }
    if(MgSeqFrameNoGet() > 300) {
        /* fn_1_8E08 inlined (as m573's finish hook): both arms say done. */
        for(j=0; j<20; j++) {
            if(lbl_1_bss_368[j] != NULL) {
                done = 1;
                goto ready;
            }
        }
        done = 1;
    ready:
        if(done != 0) {
            for(i=0; i<4; i++) {
                player = lbl_1_bss_354[i]->data;
                Hu3DModelAttrReset(lbl_1_bss_DC[i]->actor->mdlId, HU3D_ATTR_DISPOFF);
            }
            MgSeqModeNext();
        }
    }
}

/* asm 1699-1708, 8 insns. */
void fn_1_1898(OMOBJ *obj)
{
    MgActorExec();
}

/* asm 1711-1906, 186 insns. MGSEQ pre-winner hook. */
void fn_1_18B8(s16 mode, s16 frameNo)
{
    M571_PLAYER *player;
    M571_HOST *host;
    M571_HOST *host2;
    OMOBJ *hostObj;
    OMOBJ *obj;
    s32 i;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 30) {
        WipeCreate(2, 6, 30);
        WipeColorSet(255, 255, 255);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        omDelObjEx(lbl_1_bss_680, lbl_1_bss_1C0);
        omCameraViewSet(&lbl_1_data_1F0);
        for(i=0; i<4; i++) {
            player = lbl_1_bss_354[i]->data;
            /* Retail passes the MGPLAYER, not its actor (see NOTES host audit). */
            MgActorKill((MGACTOR *)lbl_1_bss_DC[i]);
            omDelObjEx(lbl_1_bss_680, lbl_1_bss_354[i]);
        }
        CharModelKill(-1);
        for(i=0; i<4; i++) {
            obj = omAddObjEx(lbl_1_bss_680, 101, 1, 3, 1, fn_1_3700);
            lbl_1_bss_350[i] = obj;
            obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_RESULT), HU_MEMNUM_OVL);
            obj->work[0] = i;
        }
        fn_1_3520();
        host->unk30 = 0;
        hostObj = lbl_1_bss_478[0];
        host2 = hostObj->data;
        Hu3DMotionSpeedSet(host2->modelId, 1.0f);
        if(host2->motNo != 0) {
            host2->motNo = 0;
            Hu3DMotionShiftSet(host2->modelId, lbl_1_bss_44C[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
        }
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelHookObjReset(host->unk54, "itemhook1");
        Hu3DModelHookObjReset(host->unk54, "itemhook2");
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-r");
        Hu3DModelAttrSet(host->unk54, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
        HuPrcVSleep();
        host->pos.x = lbl_1_data_70.x;
        host->pos.y = lbl_1_data_70.y;
        host->pos.z = lbl_1_data_70.z;
        host->rot.x = host->rot.y = host->rot.z = 0.0f;
        WipeCreate(1, 5, 30);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        MgSeqModeNext();
    }
}

/* asm 1909-2021, 105 insns. MGSEQ winner hook. */
void fn_1_1BA0(s16 mode, s16 frameNo)
{
    M571_RESULT *result;
    s32 i;
    M571_HOST *host;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 0) {
        host->unk30 = 6;
        host->unk38 = 0;
        for(i=0; i<4; i++) {
            result = lbl_1_bss_350[i]->data;
            if(result->unk30 >= 1) {
                fn_1_27E8(lbl_1_bss_350[i], 1, 8.0f, 0);
            } else {
                fn_1_27E8(lbl_1_bss_350[i], 2, 8.0f, 0);
                if(lbl_1_bss_428[0] == 0 && lbl_1_bss_428[1] == 0 && lbl_1_bss_428[2] == 0 && lbl_1_bss_428[3] == 0) {
                    CharFXPlay((s16)result->charNo, 0x200);
                }
            }
            GWMgCoinBonusAdd(result->playerNo, result->unk30);
        }
    }
}

/* asm 2024-2137, 111 insns. */
void fn_1_1D44(s32 cellNo)
{
    OMOBJ *obj;
    M571_EFF14 *eff;

    if(lbl_1_bss_F0 <= 48) {
        lbl_1_bss_F0++;
        obj = omAddObjEx(lbl_1_bss_680, 104, 1, 0, -1, fn_1_1F74);
        obj->work[0] = 0;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_EFF14), HU_MEMNUM_OVL);
        eff = obj->data;
        eff->pos.x = lbl_1_data_26C[cellNo].x;
        eff->pos.y = lbl_1_data_26C[cellNo].y;
        eff->pos.z = lbl_1_data_26C[cellNo].z;
        eff->unkC = 0;
        HuAudFXPlayVolPan(0x96B, fn_1_9350(&eff->pos), fn_1_92D4(&eff->pos));
    }
}

/* asm 2140-2170, 29 insns. Unreferenced: inlined as fn_1_2088's removal. */
void fn_1_1F00(OMOBJ *obj)
{
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_F0--;
    omDelObjEx(lbl_1_bss_680, obj);
}

/* asm 2173-2243, 69 insns. M571_EFF14 init. */
void fn_1_1F74(OMOBJ *obj)
{
    M571_EFF14 *eff;

    eff = obj->data;
    obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_10);
    omSetTra(obj, eff->pos.x, eff->pos.y, eff->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(obj->mdlId[0], 0.0f);
    Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
    Hu3DModelAttrSet(obj->mdlId[0], 0);
    obj->objFunc = fn_1_2088;
}

/* asm 2246-2338, 85 insns. M571_EFF14 main: play once, blink 30 frames, remove. */
void fn_1_2088(OMOBJ *obj)
{
    M571_EFF14 *eff;

    eff = obj->data;
    switch (eff->unkC) {
        case 0:
            if (Hu3DMotionEndCheck(obj->mdlId[0])) {
                eff->unk10 = 0;
                eff->unkC = 1;
            }
            break;
        case 1:
            if (eff->unk10 > 30) {
                fn_1_1F00(obj);
                return;
            }
            eff->unk10++;
            if (eff->unk10 & 1) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
            break;
    }
    omSetTra(obj, eff->pos.x, eff->pos.y, eff->pos.z);
    omSetRot(obj, 0.0f, 0.0f, 0.0f);
}

/* asm 2341-2423, 80 insns. Unreferenced: inlined twice into fn_1_2FE0. */
void fn_1_21DC(float x, float y, float z, s32 type, s32 cellNo, s32 playerNo)
{
    OMOBJ *obj;
    M571_BLOCK *block;

    if (lbl_1_bss_EC <= 48) {
        lbl_1_bss_EC++;
        obj = omAddObjEx(lbl_1_bss_680, 105, 1, 0, -1, fn_1_2388);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_BLOCK), HU_MEMNUM_OVL);
        obj->work[0] = type;
        block = obj->data;
        block->pos.x = x;
        block->pos.y = y;
        block->pos.z = z;
        block->rot.x = block->rot.y = block->rot.z = 0.0f;
        block->unk24 = type;
        block->scale.x = block->scale.y = block->scale.z = 0.1f;
        block->unk2C = 1;
        block->unk30 = 0;
        block->unk34 = 0.0f;
        block->unk28 = cellNo;
        block->unk38 = playerNo;
    }
}

/* asm 2426-2454, 27 insns. Unreferenced: inlined as fn_1_2468's case 3. */
void fn_1_231C(OMOBJ *obj)
{
    M571_BLOCK *block;

    block = obj->data;
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_EC--;
    omDelObjEx(lbl_1_bss_680, obj);
}

/* asm 2457-2516, 56 insns. M571_BLOCK init. */
void fn_1_2388(OMOBJ *obj)
{
    M571_BLOCK *block;

    block = obj->data;
    if (obj->work[0] == 0) {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_E);
    } else {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_C);
    }
    Hu3DModelShadowSet(obj->mdlId[0]);
    omSetTra(obj, block->pos.x, block->pos.y, block->pos.z);
    omSetRot(obj, block->rot.x, block->rot.y, block->rot.z);
    omSetSca(obj, block->scale.x, block->scale.y, block->scale.z);
    lbl_1_bss_28C[block->unk28] = obj;
    obj->objFunc = fn_1_2468;
}

/* asm 2519-2757, 224 insns. M571_BLOCK main. */
void fn_1_2468(OMOBJ *obj)
{
    M571_BLOCK *block;
    float s;

    block = obj->data;
    switch (block->unk2C) {
        case 1:
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            block->unk30++;
            if (block->unk30 > 30) {
                block->unk30 = 0;
                block->scale.x = block->scale.y = block->scale.z = 1.0f;
                block->unk2C = 0;
                break;
            }
            s = sin((M_PI * block->unk34) / 180.0);
            block->unk34 += 4.3333335f;
            block->scale.x = block->scale.y = block->scale.z = 1.25 * s;
            if (block->unk34 <= 90.0f) {
                block->pos.y += 10.0f;
            }
            break;
        case 0:
            if (block->unk30 > 10) {
                block->unk30 = 0;
                if (block->unk38 != -1) {
                    if (block->unk24 == 0) {
                        fn_1_8D54(&block->pos, block->unk38, 1);
                    } else if (block->unk24 == 1) {
                        fn_1_8D54(&block->pos, block->unk38, 5);
                    }
                }
                block->unk2C = 3;
            } else {
                block->unk30++;
            }
            break;
        case 2:
            if (block->unk30 > 30) {
                block->unk2C = 3;
                break;
            }
            block->unk30++;
            if (block->unk30 & 1) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
            break;
        case 3:
            fn_1_231C(obj);
            return;
    }
    omSetTra(obj, block->pos.x, block->pos.y, block->pos.z);
    omSetRot(obj, block->rot.x, block->rot.y, block->rot.z);
    omSetSca(obj, block->scale.x, block->scale.y, block->scale.z);
}

/* asm 2760-2796, 34 insns. Result line-up motion change. */
void fn_1_27E8(OMOBJ *obj, s32 motNo, float time, s32 attr)
{
    M571_RESULT *result;

    result = obj->data;
    if (result->motNo != motNo) {
        result->motNo = motNo;
        CharMotionShiftSet(result->charNo, result->motId[motNo], 0.0f, time, attr);
    }
}

/* asm 2799-2837, 33 insns. */
void fn_1_2870(s32 attrF)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (attrF) {
            MgPlayerAttrReset(lbl_1_bss_DC[i], 1);
        } else {
            MgPlayerAttrSet(lbl_1_bss_DC[i], 1);
        }
    }
}

/* asm 2840-2919, 72 insns. Unreferenced: inlined into fn_1_2A14. The live
 * floor cell within 90 units (x/z) of pos, or -1. */
s32 fn_1_28F4(HuVecF *pos)
{
    HuVecF a;
    HuVecF b;
    s32 hit;
    s32 i;

    for (i = 0; i < 49; i++) {
        if (lbl_1_bss_1C8[i] != NULL) {
            b.x = lbl_1_data_26C[i].x;
            b.y = lbl_1_data_26C[i].y;
            b.z = lbl_1_data_26C[i].z;
            a.x = pos->x;
            a.y = pos->y;
            a.z = pos->z;
            if ((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z) < 8100.0f) {
                hit = 1;
            } else {
                hit = 0;
            }
            if (hit) {
                return i;
            }
        }
    }
    return -1;
}

/* asm 2922-3139, 208 insns. The floor cell under a point in front of the player. */
s32 fn_1_2A14(OMOBJ *obj, s32 arg)
{
    M571_PLAYER *player;
    HuVecF pos;

    player = obj->data;
    if (arg == 0) {
        pos.x = 3.5 * (player->unk34 * sin((M_PI * player->unk24.y) / 180.0));
        pos.y = 0.0f;
        pos.z = 3.5 * (player->unk34 * cos((M_PI * player->unk24.y) / 180.0));
    } else {
        pos.x = 3.5 * (player->unk38 * sin((M_PI * player->unk24.y) / 180.0));
        pos.y = 0.0f;
        pos.z = 3.5 * (player->unk38 * cos((M_PI * player->unk24.y) / 180.0));
    }
    pos.x += player->pos.x;
    pos.z += player->pos.z;
    return fn_1_28F4(&pos);
}

/* asm 3142-3144, 1 insn. */
void fn_1_2D54(void)
{
}

/* asm 3147-3202, 52 insns. Floor cell group and model. */
void fn_1_2D58(void)
{
    s32 i;

    omMakeGroupEx(lbl_1_bss_680, 2, 49);
    lbl_1_bss_14[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 5), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_14[0], HU3D_ATTR_DISPOFF);
    /* Retail stores the group's member list in the first cell slot, then clears every slot. */
    lbl_1_bss_1C8[0] = (OMOBJ *)omGetGroupMemberListEx(lbl_1_bss_680, 2);
    lbl_1_bss_4 = 0;
    for (i = 0; i < 49; i++) {
        lbl_1_bss_1C8[i] = NULL;
    }
}

/* asm 3205-3264, 55 insns. Pick a layout and spawn its cells. */
void fn_1_2E28(void)
{
    s32 layout;
    s32 i;

    layout = frandmod(8);
    lbl_1_bss_8 = layout;
    for (i = 0; i < 49; i++) {
        if (lbl_1_data_704[layout][i] != -1) {
            fn_1_2F04(lbl_1_data_26C[i].x, lbl_1_data_26C[i].y, lbl_1_data_26C[i].z, lbl_1_data_704[layout][i], i);
        }
    }
}

/* asm 3267-3324, 55 insns. */
void fn_1_2F04(float x, float y, float z, s32 kind, s32 no)
{
    OMOBJ *obj;
    M571_CELL *cell;

    if (lbl_1_bss_4 <= 48) {
        obj = omAddObjEx(lbl_1_bss_680, 103, 1, 0, 2, fn_1_3594);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M571_CELL), HU_MEMNUM_OVL);
        obj->work[0] = kind;
        cell = obj->data;
        cell->pos.x = x;
        cell->pos.y = y;
        cell->pos.z = z;
        cell->no = no;
        lbl_1_bss_4++;
    }
}

/* asm 3327-3668, 336 insns. Break a floor cell; playerNo -1 clears it silently. */
s32 fn_1_2FE0(OMOBJ *obj, s32 playerNo)
{
    M571_CELL *cell;
    HuVecF pos;
    s32 kind;

    cell = obj->data;
    Hu3DModelKill(obj->mdlId[0]);
    pos.x = lbl_1_data_26C[cell->no].x;
    pos.y = lbl_1_data_26C[cell->no].y;
    pos.z = lbl_1_data_26C[cell->no].z;
    kind = lbl_1_data_704[lbl_1_bss_8][cell->no];
    Hu3DModelPosSet(lbl_1_bss_156[cell->no + 2], pos.x, -1000.0f, pos.z);
    if (playerNo != -1) {
        if (kind == 1) {
            fn_1_21DC(pos.x, pos.y, pos.z, 0, cell->no, playerNo);
            HuAudFXPlayVolPan(0x96C, fn_1_9350(&pos), fn_1_92D4(&pos));
        } else if (kind == 5) {
            fn_1_21DC(pos.x, pos.y, pos.z, 1, cell->no, playerNo);
            HuAudFXPlayVolPan(0x96C, fn_1_9350(&pos), fn_1_92D4(&pos));
        }
    }
    lbl_1_bss_1C8[cell->no] = NULL;
    lbl_1_bss_4--;
    omDelObjEx(lbl_1_bss_680, obj);
    return kind;
}

/* asm 3671-3704, 29 insns. Clear every remaining floor cell. */
void fn_1_3520(void)
{
    s32 i;

    for (i = 0; i < 49; i++) {
        if (lbl_1_bss_1C8[i] != NULL) {
            fn_1_2FE0(lbl_1_bss_1C8[i], -1);
        }
    }
}

/* asm 3707-3781, 73 insns. M571_CELL init. */
void fn_1_3594(OMOBJ *obj)
{
    M571_CELL *cell;

    cell = obj->data;
    obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_14[0]);
    Hu3DModelShadowMapSet(obj->mdlId[0]);
    omSetTra(obj, cell->pos.x, cell->pos.y, cell->pos.z);
    omSetRot(obj, 0.0f, 1.4117647f * (u8)frand(), 0.0f);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    lbl_1_bss_1C8[cell->no] = obj;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_36B8;
}

/* asm 3784-3803, 18 insns. M571_CELL main. */
void fn_1_36B8(OMOBJ *obj)
{
    M571_CELL *cell;

    cell = obj->data;
    omSetTra(obj, cell->pos.x, cell->pos.y, cell->pos.z);
}

/* asm 3806-3931, 122 insns. Result line-up character init. */
void fn_1_3700(OMOBJ *obj)
{
    M571_RESULT *result;
    HuVecF screen;
    s32 i;
    s32 pan;
    s32 pan2;
    s32 pan3;

    result = obj->data;
    result->playerNo = obj->work[0];
    result->charNo = GwPlayerConf[result->playerNo].charNo;
    result->unk30 = lbl_1_bss_428[result->playerNo];
    obj->mdlId[0] = CharModelCreate(result->charNo, 2);
    for (i = 0; i < 3; i++) {
        result->motId[i] = CharMotionCreate(result->charNo, lbl_1_data_1A4[i]);
    }
    CharMotionSet(result->charNo, result->motId[0]);
    result->motNo = 3;
    result->mdlId = obj->mdlId[0];
    result->pos.x = lbl_1_data_23C[result->playerNo].x;
    result->pos.y = lbl_1_data_23C[result->playerNo].y;
    result->pos.z = lbl_1_data_23C[result->playerNo].z;
    result->rot.x = result->rot.y = result->rot.z = 0.0f;
    Hu3DModelAttrSet(result->mdlId, 0x40000001);
    Hu3DModelShadowSet(result->mdlId);
    Hu3D3Dto2D(&result->pos, 1, &screen);
    pan = 32.0f + 64.0f * (screen.x / 576.0f);
    pan2 = pan;
    pan3 = pan2;
    CharModelVoicePanSet(result->charNo, pan3);
    obj->objFunc = fn_1_38E8;
}

/* asm 3934-3958, 23 insns. Result line-up character main. */
void fn_1_38E8(OMOBJ *obj)
{
    M571_RESULT *result;

    result = obj->data;
    omSetTra(obj, result->pos.x, result->pos.y, result->pos.z);
    omSetRot(obj, result->rot.x, result->rot.y, result->rot.z);
}

/* asm 3961-4239, 276 insns. Unreferenced debug camera readout (Center/CRot/CZoom). */
void fn_1_3944(void)
{
    GXColor color;

    color.r = 0;
    color.g = 0;
    color.b = 0x90;
    color.a = 0xC0;
    CZoom += HuPadTrigL[0] / 5;
    CZoom -= HuPadTrigR[0] / 5;
    Center.x += 10.0f * (HuPadSubStkX[0] / 59.0f);
    Center.z -= 10.0f * (HuPadSubStkY[0] / 59.0f);
    CRot.x += 5.0f * (HuPadSubStkY[1] / 59.0f);
    CRot.y -= 5.0f * (HuPadSubStkX[1] / 59.0f);
    printWin(16, 40, 324, 84, &color);
    fontcolor = 14;
    print8(16, 40, 1.5f, "Center.x:%.02f", Center.x);
    print8(16, 52, 1.5f, "Center.y:%.02f", Center.y);
    print8(16, 64, 1.5f, "Center.z:%.02f", Center.z);
    print8(16, 76, 1.5f, "CRot.x:%.02f", CRot.x);
    print8(16, 88, 1.5f, "CRot.y:%.02f", CRot.y);
    /* Retail labels CRot.z with the CRot.y format. */
    print8(16, 100, 1.5f, "CRot.y:%.02f", CRot.z);
    print8(16, 112, 1.5f, "CZoom:%.02f", CZoom);
    if (HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&lbl_1_data_1D4);
    }
}
