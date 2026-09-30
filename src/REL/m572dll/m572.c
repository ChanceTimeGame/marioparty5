/*
 * m572dll -- a Donkey Kong minigame (MG_TYPE_DONKEY, overlay #83).
 *
 * Every function is written from the reference assembly, in reference order.
 * Line ranges are into build/mp5-asm/m572dll/asm/REL/m572dll/m572.s.
 *
 * Shape: the same three-part single TU as m571dll -- seqman (MgSeqCreatePrio,
 * lbl_1_data_37C) + five omAddObjEx groups + the shared Donkey Kong host:
 *
 *  - ObjectSetup..fn_1_4C04: this overlay's own code (38 functions, 4,890).
 *  - fn_1_4D08..fn_1_5BEC:   REL/m563dll/math.c, included; already written.
 *  - fn_1_5CB0..fn_1_A2C4:   REL/m571dll/host.c, included; already written.
 *                            Shared with m571dll and m573dll.
 *
 * Emission order (measured on m559dll, m571dll and here): CodeWarrior emits
 * this file's own functions first, then those of the #included files in
 * include order -- which is the reference order. Data goes the other way:
 * the included files' .data comes first, so .data:0x0..0x1A4 is host.c's
 * (byte-identical to m571's) and this file's own starts at 0x1A4.
 *
 * The two included blocks keep m563's and m571's address names. The notebook
 * renames them onto this overlay's addresses with objcopy and map.txt; the
 * bss mapping is simply m571's address + 0x54. See NOTES.md.
 *
 * Groups, from ObjectSetup:
 *   0  4 players, prio 100, work 0x80, main fn_1_D94   (list lbl_1_bss_3A8)
 *   1  225 cells (15x15), created later                 (models bss_8/6/4)
 *   2  9 objects, prio 102, work 0x2C, main fn_1_C54    (list lbl_1_bss_3A0)
 *   3  1 host,    prio 104, work 0xB0, main fn_1_85E4   (host.c's, list bss_4CC)
 *   4  2 objects, prio 105, work 0x34, main fn_1_710    (list lbl_1_bss_3A4)
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

/* Object manager; host.c uses it. m571's lbl_1_bss_680 -> ours at 0x6D4. */
OMOBJMAN *lbl_1_bss_680;

#include "REL/m563dll/math.c"
#include "REL/m571dll/host.c"



/* ---- work structures -------------------------------------------------- */

/* 0x80 bytes per player (group 0; fn_1_D94 init, fn_1_1050 main).
 * Closest to m573's M573_PLAYER; the tail is m572's nine-lane rail state. */
typedef struct M572Player_s {
    /* 0x00 */ s16 motNo;          /* index into obj->mtnId[8] */
    /* 0x02 */ HU3DMOTID unk02[8]; /* never read; the ids live in obj->mtnId */
    /* 0x12 */ HU3DMODELID mdlId;
    /* 0x14 */ s32 playerNo;
    /* 0x18 */ s32 charNo;
    /* 0x1C */ s32 padNo;
    /* 0x20 */ s32 score;
    /* 0x24 */ s32 mode;
    /* 0x28 */ s32 timer;
    /* 0x2C */ float unk2C;        /* written, never read */
    /* 0x30 */ float unk30;        /* written, never read */
    /* 0x34 */ HuVecF pos;
    /* 0x40 */ HuVecF posPrev;
    /* 0x4C */ float unk4C;        /* written, never read */
    /* 0x50 */ HuVecF rot;
    /* 0x5C */ s32 lane;           /* 0..8 */
    /* 0x60 */ s32 laneTo;         /* -1 when not moving */
    /* 0x64 */ s32 laneMode;       /* fn_1_1500's jumptable_1_data_E68 */
    /* 0x68 */ s32 laneTimer;
    /* 0x6C */ s32 laneFrames;
    /* 0x70 */ float laneStep;
    /* 0x74 */ u16 btnDown;
    /* 0x76 */ u16 btn;
    /* 0x78 */ s32 dif;
    /* 0x7C */ s32 sfxHandle;      /* -1 = none */
} M572_PLAYER;                     /* 0x80 */

/* 0x40 bytes per item (group 1; fn_1_370C init, fn_1_3954 main).
 * m573's M573_ITEM through 0x37, plus col and motNo. */
typedef struct M572Item_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF scale;
    /* 0x24 */ s32 kind;           /* -1, 1 or 5 */
    /* 0x28 */ s32 no;             /* its cell, 0..224 */
    /* 0x2C */ s32 mode;
    /* 0x30 */ s32 timer;
    /* 0x34 */ s32 playerNo;
    /* 0x38 */ s32 col;            /* no % 9 */
    /* 0x3C */ s16 motNo;          /* 2 = none */
} M572_ITEM;                       /* 0x40 */

/* 0x2C bytes per lane pillar (group 2; fn_1_C54 init, fn_1_AC4 main). */
typedef struct M572Pillar_s {
    /* 0x00 */ HU3DMODELID mdlId;
    /* 0x02 */ HU3DMODELID mdlId2;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF rot;
    /* 0x1C */ s32 mode;
    /* 0x20 */ s32 timer;
    /* 0x24 */ float angle;
    /* 0x28 */ s32 no;             /* lane 0..8 */
} M572_PILLAR;                     /* 0x2C */

/* 0x34 bytes per sky flyer (group 4; fn_1_710 init, fn_1_9E4 main). */
typedef struct M572Flyer_s {
    /* 0x00 */ s32 no;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ HuVecF posStep;
    /* 0x1C */ HuVecF rot;
    /* 0x28 */ HuVecF rotStep;
} M572_FLYER;                      /* 0x34 */

void ObjectSetup(void);
static void fn_1_710(OMOBJ *obj);
static void fn_1_9E4(OMOBJ *obj);
static void fn_1_AC4(OMOBJ *obj);
static void fn_1_C54(OMOBJ *obj);
static void fn_1_D94(OMOBJ *obj);
static void fn_1_1050(OMOBJ *obj);
static void fn_1_1500(OMOBJ *obj);
static s32 fn_1_1F94(OMOBJ *obj, s32 lane);
static void fn_1_20A8(HuVecF *pos);
static void fn_1_214C(OMOBJ *obj);
static void fn_1_2404(OMOBJ *obj);
static void fn_1_2574(OMOBJ *obj);
static void fn_1_26EC(OMOBJ *obj);
static void fn_1_27FC(OMOBJ *obj);
static void fn_1_2974(s16 mode, s16 frameNo);
static void fn_1_2AD8(s16 mode, s16 frameNo);
static void fn_1_2C9C(s16 mode, s16 frameNo);
static void fn_1_2CFC(s16 mode, s16 frameNo);
static void fn_1_2DF0(s16 mode, s16 frameNo);
static void fn_1_30FC(s16 mode, s16 frameNo);
static void fn_1_32A8(OMOBJ *obj, s32 motNo, float time, s32 attr);
static void fn_1_3344(OMOBJ *obj, s32 motNo);
static void fn_1_33A4(void);
static void fn_1_33A8(void);
static void fn_1_3454(float x, float y, float z, s32 kind, s32 no);
static void fn_1_35A8(OMOBJ *obj);
static void fn_1_3634(void);
static void fn_1_370C(OMOBJ *obj);
static void fn_1_3954(OMOBJ *obj);
static void fn_1_3C9C(OMOBJ *obj, s32 motNo, float time, s32 attr);
static s32 fn_1_3D28(OMOBJ *obj, s32 dir);
static s32 fn_1_42DC(OMOBJ *obj, s32 dir);
static s32 fn_1_45A4(s32 cellNo, s32 playerNo);
static void fn_1_45E0(void);
static void fn_1_463C(void);
static void fn_1_498C(void);
static void fn_1_4C04(HuVecF *out, s32 cellNo);


/* ---- .data:0x1A4.. this overlay's own ---------------------------------- */

/* Character motions and models loaded by fn_1_33A8. */
u32 lbl_1_data_1A4[8] = {
    DATANUM(DATA_mariomot, 0x00), DATANUM(DATA_mariomot, 0x06),
    DATANUM(DATA_mariomot, 0x31), DATANUM(DATA_mariomot, 0x01),
    DATANUM(DATA_mario, 0x99),    DATANUM(DATA_mario, 0x9A),
    DATANUM(DATA_mariomot, 0x78), DATANUM(DATA_mariomot, 0x6E)
};

u32 lbl_1_data_1C4[9] = {
    DATANUM(DATA_m572, 0x03), DATANUM(DATA_m572, 0x04), DATANUM(DATA_m572, 0x05),
    DATANUM(DATA_m572, 0x06), DATANUM(DATA_m572, 0x07), DATANUM(DATA_m572, 0x08),
    DATANUM(DATA_m572, 0x09), DATANUM(DATA_m572, 0x0A), DATANUM(DATA_m572, 0x0B)
};

OMCAMERAVIEW lbl_1_data_1E8 = { { 0.0f, 221.5f, -500.0f }, { 4.4f, 0.0f, 0.0f },  526.0f };
OMCAMERAVIEW lbl_1_data_204 = { { 0.0f, 350.0f,    0.0f }, { 0.0f, 0.0f, 0.0f }, 1729.0f };
OMCAMERAVIEW lbl_1_data_220 = { { 0.0f, 221.5f, -500.0f }, { 4.4f, 0.0f, 0.0f }, 1200.0f };

HuVecF lbl_1_data_23C[4] = {
    { -360.0f, 0.0f, 0.0f }, { -120.0f, 0.0f, 0.0f },
    {  120.0f, 0.0f, 0.0f }, {  360.0f, 0.0f, 0.0f }
};

s32 lbl_1_data_26C[4] = { 1, 3, 5, 7 };

float lbl_1_data_27C[9] = {
    -480.0f, -360.0f, -240.0f, -120.0f, 0.0f, 120.0f, 240.0f, 360.0f, 480.0f
};

HuVecF lbl_1_data_2A0[5] = {
    { -240.0f,   0.0f, -450.0f }, { -80.36f,   0.0f, -450.0f },
    {  80.36f,   0.0f, -450.0f }, { 240.66f,   0.0f, -450.0f },
    {    0.0f, 100.0f, -800.0f }
};

HuVecF lbl_1_data_2DC[2] = { { 1000.0f, 1700.0f, -900.0f }, { 1100.0f, 1800.0f, -800.0f } };
HuVecF lbl_1_data_2F4[2] = { { -1100.0f, 2700.0f, -500.0f }, { -1000.0f, 2900.0f, -400.0f } };
HuVecF lbl_1_data_30C[2] = { { -10.0f, 30.0f, 0.0f }, { -10.0f, 30.0f, 0.0f } };
HuVecF lbl_1_data_324[2] = { {  60.0f, 30.0f, 0.0f }, {  60.0f, 30.0f, 0.0f } };

/* Global light: position, aim, colour. */
HuVecF lbl_1_data_33C = { 0.0f, 10000.0f, 10000.0f };
HuVecF lbl_1_data_348 = { 0.0f, 0.0f, 0.0f };
u8 lbl_1_data_354[4] = { 255, 255, 255, 255 };

/* Shadow: position, up, aim. */
HuVecF lbl_1_data_358 = { -100.0f, 8000.0f, 0.0f };
HuVecF lbl_1_data_364 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_370 = { 0.0f, 0.0f, 0.0f };

MGSEQ_PARAM lbl_1_data_37C = {
    10,
    MGSEQ_TIMER_TOP,
    fn_1_2974,
    fn_1_2AD8,
    NULL,
    fn_1_2C9C,
    fn_1_2CFC,
    fn_1_2DF0,
    fn_1_30FC,
    NULL,
    NULL
};

/* Three 15x15 cell layouts; 0 nothing, -1 / 1 / 5 the three kinds.
 * The last two rows of each are all zero. */
/* Three 225-cell layouts (9 lanes x 25 rows); 0 nothing, and -1, 1 or 5
 * the three kinds. fn_1_33A8 picks one with frandmod(3). */
s32 lbl_1_data_3A4[3][225] = {
    {
        0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -1, 0,
        0, 1, 0, -1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, -1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0,
        0, 1, 0, -1, 0, -1, 1, 0, 1, 0, -1, 0, 0, 1, 0,
        0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 0, -1, 0, 0, 0, 0, 5, 1, -1, 0, 0,
        0, 1, -1, 0, 0, 0, 0, 0, 5, -1, 0, 0, 0, -1, 0,
        0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 5, 0, 0,
        0, 0, 0, 5, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
        0, -1, 0, 0, 0, -1, 0, 1, 0, 0, 1, 0, 1, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, -1, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, -1, 1, -1, 0, 1, 0, 0,
        -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0,
        0, 0, 1, 0, -1, 0, 0, 0, -1, 0, -1, 0, 0, 0, 0,
        1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 1, 5, -1, 0, -1, 0, 1, 0,
        0, 0, -1, 0, 0, 0, 0, -1, 0, 1, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 5, 0, 1, 0, 0,
        0, -1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, -1, 0, -1,
        0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,
        0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 5, 0, -1,
        0, 0, 0, 0, -1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0,
        -1, 0, 0, 5, 0, -1, 0, 0, 0, 0, 0, 0, -1, 0, 0,
        0, 1, 1, 0, 1, 1, 0, 0, 1, 1, -1, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    {
        0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, -1, 1,
        -1, 0, -1, 1, -1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
        5, 0, 5, 0, 0, 0, 5, 0, 5, 0, 0, 0, 0, 0, 0,
        0, 0, 0, -1, 1, -1, 0, 0, 0, -1, 1, -1, 0, 0, 0,
        1, -1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 0, -1, -1, 1, -1, 0, -1, 1, -1, -1, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
        0, 1, 0, 0, 0, -1, 0, 0, 0, -1, 0, 0, 1, 0, 0,
        0, -1, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, -1,
        0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
};

s16 lbl_1_data_E30[9] = { 32, 40, 48, 56, 64, 72, 80, 88, 96 };

/* .data:0xE42.. are literals: ObjectSetup's OSReport, fn_1_1500's jump table
 * and the debug prints in fn_1_463C. */


/* ---- .bss:0x0..0x3A8 this overlay's own -------------------------------- */

/* CodeWarrior emits .bss in reverse declaration order, so these are declared
 * descending to land at the reference's addresses. */
s32 lbl_1_bss_3AC;              /* never read; dtk folds it into lbl_1_bss_3A8's size */
OMOBJ **lbl_1_bss_3A8;          /* group 0 member list (4 players) */
OMOBJ **lbl_1_bss_3A4;          /* group 4 member list (2) */
OMOBJ **lbl_1_bss_3A0;          /* group 2 member list (9) */
OMOBJ *lbl_1_bss_1C[225];       /* 0x384 -- the live item on each cell */
OMOBJ *lbl_1_bss_18;
HU3DLIGHTID lbl_1_bss_14;
HU3DMODELID lbl_1_bss_10[2];    /* dtk splits this, naming 0x12 gap_05_00000012_bss */
s32 lbl_1_bss_C;
HU3DMODELID lbl_1_bss_8;
HU3DMODELID lbl_1_bss_6;
HU3DMODELID lbl_1_bss_4;
s32 lbl_1_bss_0;                /* never read; dtk names it pad_05_00000000_bss */

void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;
    int j;

    OSReport("******* M572 ObjectSetup *********\n");
    lbl_1_bss_680 = omInitObjMan(200, 0x2000);
    omGameSysInit(lbl_1_bss_680);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSet(&lbl_1_data_1E8);
    lbl_1_bss_18 = omAddObjEx(lbl_1_bss_680, 0x7FDA, 0, 0, -1, omOutView);
    lbl_1_bss_18->work[0] = 2;
    lbl_1_bss_14 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_14, &lbl_1_data_33C, &lbl_1_data_348);
    Hu3DGLightStaticSet(lbl_1_bss_14, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_14);
    Hu3DGLightColorSet(lbl_1_bss_14, lbl_1_data_354[0], lbl_1_data_354[1], lbl_1_data_354[2], lbl_1_data_354[3]);
    Hu3DShadowCreate(30.0f, 10.0f, 10000.0f);
    Hu3DShadowColSet(16, 16, 16);
    Hu3DShadowPosSet(&lbl_1_data_358, &lbl_1_data_364, &lbl_1_data_370);
    Hu3DShadowTPLvlSet(0.6f);
    omMakeGroupEx(lbl_1_bss_680, 0, 4);
    lbl_1_bss_3A8 = omGetGroupMemberListEx(lbl_1_bss_680, 0);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(lbl_1_bss_680, 100, 1, 8, 0, fn_1_D94);
        lbl_1_bss_3A8[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M572_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_680, 3, 1);
    lbl_1_bss_478 = omGetGroupMemberListEx(lbl_1_bss_680, 3);
    obj = omAddObjEx(lbl_1_bss_680, 104, 0, 0, 3, fn_1_7670);
    lbl_1_bss_478[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, 0xB0, HU_MEMNUM_OVL);
    obj->work[0] = 1;
    omMakeGroupEx(lbl_1_bss_680, 2, 9);
    lbl_1_bss_3A0 = omGetGroupMemberListEx(lbl_1_bss_680, 2);
    for(i=0; i<9; i++) {
        obj = omAddObjEx(lbl_1_bss_680, 102, 2, 0, 2, fn_1_C54);
        lbl_1_bss_3A0[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M572_PILLAR), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_C = 0;
    omMakeGroupEx(lbl_1_bss_680, 1, 225);
    lbl_1_bss_8 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x10), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_6 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x12), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x0D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_8, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_6, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_4, HU3D_ATTR_DISPOFF);
    omMakeGroupEx(lbl_1_bss_680, 4, 2);
    lbl_1_bss_3A4 = omGetGroupMemberListEx(lbl_1_bss_680, 4);
    for(i=0; i<2; i++) {
        obj = omAddObjEx(lbl_1_bss_680, 105, 1, 1, 4, fn_1_710);
        lbl_1_bss_3A4[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M572_FLYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    lbl_1_bss_364 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_364, HU3D_ATTR_DISPOFF);
    for(j=0; j<20; j++) {
        lbl_1_bss_368[j] = NULL;
    }
    lbl_1_bss_35C = -1;
    fn_1_33A8();
    MgSeqCreatePrio(&lbl_1_data_37C, 1000);
}

static void fn_1_710(OMOBJ *obj)
{
    M572_FLYER *flyer;

    flyer = obj->data;
    flyer->no = obj->work[0];
    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x13), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(obj->mdlId[0], 0x40000001);
    flyer->pos.x = lbl_1_data_2DC[flyer->no].x;
    flyer->pos.y = lbl_1_data_2DC[flyer->no].y;
    flyer->pos.z = lbl_1_data_2DC[flyer->no].z;
    flyer->rot.x = lbl_1_data_30C[flyer->no].x;
    flyer->rot.y = lbl_1_data_30C[flyer->no].y;
    flyer->rot.z = lbl_1_data_30C[flyer->no].z;
    flyer->posStep.x = (lbl_1_data_2F4[flyer->no].x - lbl_1_data_2DC[flyer->no].x) / 200.0f;
    flyer->posStep.y = (lbl_1_data_2F4[flyer->no].y - lbl_1_data_2DC[flyer->no].y) / 200.0f;
    flyer->posStep.z = (lbl_1_data_2F4[flyer->no].z - lbl_1_data_2DC[flyer->no].z) / 200.0f;
    flyer->rotStep.x = (lbl_1_data_324[flyer->no].x - lbl_1_data_30C[flyer->no].x) / 200.0f;
    flyer->rotStep.y = (lbl_1_data_324[flyer->no].y - lbl_1_data_30C[flyer->no].y) / 200.0f;
    flyer->rotStep.z = (lbl_1_data_324[flyer->no].z - lbl_1_data_30C[flyer->no].z) / 200.0f;
    obj->objFunc = fn_1_9E4;
}

static void fn_1_9E4(OMOBJ *obj)
{
    M572_FLYER *flyer;

    flyer = obj->data;
    if(MgSeqModeGet() == 5 && MgSeqFrameNoGet() >= 400 && MgSeqFrameNoGet() <= 600) {
        flyer->pos.x += flyer->posStep.x;
        flyer->pos.y += flyer->posStep.y;
        flyer->pos.z += flyer->posStep.z;
        flyer->rot.x += flyer->rotStep.x;
        flyer->rot.y += flyer->rotStep.y;
        flyer->rot.z += flyer->rotStep.z;
    }
    omSetTra(obj, flyer->pos.x, flyer->pos.y, flyer->pos.z);
    omSetRot(obj, flyer->rot.x, flyer->rot.y, flyer->rot.z);
}

static void fn_1_AC4(OMOBJ *obj)
{
    M572_PILLAR *pillar;
    float y;

    pillar = obj->data;
    switch(pillar->mode) {
    case 0:
        break;
    case 1:
        if((float)pillar->timer > 45.0f) {
            pillar->mode = 0;
            pillar->timer = 0;
            pillar->pos.y = 0.0f;
        } else {
            pillar->timer++;
            pillar->angle -= 2.0f;
            if(pillar->angle < 0.0f) {
                pillar->mode = 0;
                pillar->timer = 0;
                pillar->pos.y = 0.0f;
            }
            y = 45.0 + 700.0 * sin((M_PI * pillar->angle) / 180.0);
            pillar->pos.y = y;
        }
        break;
    }
    Hu3DModelPosSet(pillar->mdlId, pillar->pos.x, pillar->pos.y, pillar->pos.z);
    Hu3DModelRotSet(pillar->mdlId, pillar->rot.x, pillar->rot.y, pillar->rot.z);
}

static void fn_1_C54(OMOBJ *obj)
{
    M572_PILLAR *pillar;

    pillar = obj->data;
    pillar->no = obj->work[0];
    pillar->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_1C4[pillar->no], HU_MEMNUM_OVL, HEAP_MODEL));
    pillar->mdlId2 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x0C), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelPosSet(pillar->mdlId2, lbl_1_data_27C[pillar->no], 0.0f, 0.0f);
    Hu3DModelAttrSet(pillar->mdlId2, 0x40000002);
    pillar->pos.x = 0.0f;
    pillar->pos.y = 745.0f;
    pillar->pos.z = 0.0f;
    pillar->rot.x = pillar->rot.y = pillar->rot.z = 0.0f;
    pillar->mode = 0;
    pillar->timer = 0;
    pillar->angle = 90.0f;
    obj->objFunc = fn_1_AC4;
}

static void fn_1_D94(OMOBJ *obj)
{
    M572_PLAYER *player;
    float x;
    float y;
    float z;
    int i;

    player = obj->data;
    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->score = 0;
    player->mode = 0;
    player->timer = 0;
    player->btnDown = player->btn = 0;
    player->laneMode = 0;
    player->laneTimer = 0;
    player->laneFrames = 0;
    player->btnDown = 0;
    player->sfxHandle = -1;
    obj->mdlId[0] = CharModelCreate((s16)player->charNo, 2);
    for(i=0; i<8; i++) {
        obj->mtnId[i] = CharMotionCreate((s16)player->charNo, lbl_1_data_1A4[i]);
        CharMotionSet((s16)player->charNo, obj->mtnId[i]);
    }
    player->motNo = 0;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], 0x40000001);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    player->mdlId = obj->mdlId[0];
    player->dif = GwPlayerConf[player->playerNo].dif;
    player->rot.x = player->rot.y = player->rot.z = 0.0f;
    z = lbl_1_data_23C[player->playerNo].z;
    y = lbl_1_data_23C[player->playerNo].y;
    x = lbl_1_data_23C[player->playerNo].x;
    player->pos.x = x;
    player->pos.y = y;
    player->pos.z = z;
    player->lane = lbl_1_data_26C[player->playerNo];
    player->laneTo = -1;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose((s16)player->charNo);
    obj->objFunc = fn_1_1050;
}

static void fn_1_1050(OMOBJ *obj)
{
    M572_PLAYER *player;
    int no;
    int kind;

    player = obj->data;
    switch(player->mode) {
    case 0:
        break;
    case 1:
        fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 3, 8.0f, 0x40000001);
        player->rot.y += 6.0f;
        if(player->rot.y > 180.0f) {
            player->rot.y = 180.0f;
            player->mode = 2;
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 4, 8.0f, 0x40000001);
        }
        break;
    case 2:
        if((float)player->timer > 8.0f) {
            player->mode = 3;
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            player->timer = 0;
        } else {
            player->timer++;
            player->pos.z -= 3.0f;
        }
        break;
    case 3:
        if(GwPlayerConf[player->playerNo].type != 0) {
            switch(player->dif) {
            case 0:
                fn_1_2404(obj);
                break;
            case 1:
                fn_1_2574(obj);
                break;
            case 2:
                fn_1_26EC(obj);
                break;
            case 3:
                fn_1_27FC(obj);
                break;
            }
        } else {
            player->btnDown = HuPadBtnDown[player->padNo];
            player->btn = HuPadBtn[player->padNo];
        }
        fn_1_1500(obj);
        no = fn_1_3D28(obj, 0);
        if(no != -2) {
            kind = fn_1_45A4(no, player->playerNo);
            if(kind == -1) {
                player->mode = 4;
                omVibrate((s16)player->padNo, 15, 12, 0);
                player->timer = 0;
                player->unk2C = 0.0f;
                player->unk4C = player->pos.y;
                HuAudFXPlayPan(0x977, lbl_1_data_E30[player->lane]);
            } else {
                HuAudFXPlayPan(0x96C, lbl_1_data_E30[player->lane]);
            }
        }
        break;
    case 4:
        if(player->timer > 25) {
            player->timer = 0;
            player->mode = 3;
            player->unk2C = 0.0f;
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 4, 8.0f, 0x40000001);
        } else {
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 7, 8.0f, 0x40000001);
            player->timer++;
            player->pos.y -= 3.4041665f;
            if(player->timer & 1) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
        }
        break;
    }
    if(MgSeqModeGet() == 6 && player->laneMode != 3 && player->laneMode != 4) {
        Hu3DMotionSpeedSet(player->mdlId, 0.0f);
    }
    fn_1_20A8(&player->pos);
    fn_1_214C(obj);
    player->posPrev = player->pos;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
}

static void fn_1_1500(OMOBJ *obj)
{
    M572_PLAYER *player = obj->data;

    switch (player->laneMode) {
    case 0:
        if (MgSeqModeGet() == 5) {
            if (player->btn & PAD_BUTTON_A) {
                player->pos.y += 6.45f;
                Hu3DModelAttrReset(player->mdlId, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(player->mdlId, 3.0f);
                if (player->sfxHandle == -1) {
                    player->sfxHandle = HuAudFXPlayPan(player->playerNo + 0x96F, lbl_1_data_E30[player->lane]);
                } else if (HuAudFXStatusGet(player->sfxHandle) == 0) {
                    player->sfxHandle = -1;
                }
            }
            if (player->btn & PAD_BUTTON_B) {
                player->pos.y -= 6.808333f;
                Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(player->mdlId, 3.0f);
            }
            if (!(player->btn & PAD_BUTTON_A) && !(player->btn & PAD_BUTTON_B)) {
                Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            }
            if (player->btnDown & PAD_TRIGGER_L) {
                player->laneTimer = 0;
                if (fn_1_1F94(obj, player->lane - 1)) {
                    player->laneMode = 3;
                    player->laneTo = player->lane - 1;
                    fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 5, 8.0f, 0);
                    HuAudFXPlayPan(player->playerNo + 0x973, lbl_1_data_E30[player->lane]);
                } else {
                    player->laneMode = 5;
                }
            }
            if (player->btnDown & PAD_TRIGGER_R) {
                player->laneTimer = 0;
                if (fn_1_1F94(obj, player->lane + 1)) {
                    player->laneMode = 4;
                    player->laneTo = player->lane + 1;
                    fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 6, 8.0f, 0);
                    HuAudFXPlayPan(player->playerNo + 0x973, lbl_1_data_E30[player->lane]);
                } else {
                    player->laneMode = 6;
                }
            }
        }
        break;

    case 5:
        player->laneTimer++;
        if (player->laneTimer > 20.0f) {
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            player->laneTimer = 0;
            player->laneMode = 0;
            player->pos.x = lbl_1_data_27C[player->lane];
        } else if (player->laneTimer < 10.0f) {
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 5, 8.0f, 0);
            player->pos.x -= 3.0f;
        } else {
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_REV);
            player->pos.x += 3.0f;
        }
        break;

    case 6:
        player->laneTimer++;
        if (player->laneTimer > 20.0f) {
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            player->laneTimer = 0;
            player->laneMode = 0;
            player->pos.x = lbl_1_data_27C[player->lane];
        } else if (player->laneTimer < 10.0f) {
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 6, 8.0f, 0);
            player->pos.x += 3.0f;
        } else {
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_REV);
            player->pos.x -= 3.0f;
        }
        break;

    case 7:
        if (player->laneTimer > player->laneFrames) {
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            player->laneTimer = 0;
            player->laneMode = 0;
            player->pos.x = lbl_1_data_27C[player->lane];
        } else {
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_REV);
            player->pos.x += player->laneStep;
            player->laneTimer++;
        }
        break;

    case 8:
        if (player->laneTimer > player->laneFrames) {
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            player->laneTimer = 0;
            player->laneMode = 0;
            player->pos.x = lbl_1_data_27C[player->lane];
        } else {
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_REV);
            player->pos.x -= player->laneStep;
            player->laneTimer++;
        }
        break;

    case 3:
        player->laneTimer++;
        if (player->laneTimer > 20.0f) {
            player->laneTimer = 0;
            player->laneMode = 0;
            player->lane--;
            player->laneTo = -1;
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            if (player->lane < 0) {
                player->lane = 0;
            }
            player->pos.x = lbl_1_data_27C[player->lane];
        } else if (fn_1_1F94(obj, player->lane - 1) == 0) {
            player->laneFrames = player->laneTimer;
            player->laneStep = fabs(lbl_1_data_27C[player->lane] - player->pos.x) / player->laneFrames;
            player->laneTimer = 0;
            player->laneMode = 7;
        } else {
            player->pos.x -= 6.0f;
        }
        break;

    case 4:
        player->laneTimer++;
        if (player->laneTimer > 20.0f) {
            player->laneTimer = 0;
            player->laneMode = 0;
            player->lane++;
            player->laneTo = -1;
            fn_1_3344(lbl_1_bss_3A8[player->playerNo], 4);
            Hu3DModelAttrSet(player->mdlId, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
            if (player->lane >= 9) {
                player->lane = 8;
            }
            player->pos.x = lbl_1_data_27C[player->lane];
        } else if (fn_1_1F94(obj, player->lane + 1) == 0) {
            player->laneFrames = player->laneTimer;
            player->laneStep = fabs(player->pos.x - lbl_1_data_27C[player->lane]) / player->laneFrames;
            player->laneTimer = 0;
            player->laneMode = 8;
        } else {
            player->pos.x += 6.0f;
        }
        break;
    }
}

static s32 fn_1_1F94(OMOBJ *obj, s32 lane)
{
    M572_PLAYER *other;
    int i;
    M572_PLAYER *player;
    float d;

    player = obj->data;
    if(lane < 0) {
        return 0;
    }
    if(lane >= 9) {
        return 0;
    }
    for(i=0; i<4; i++) {
        if(i == player->playerNo) {
            continue;
        }
        other = lbl_1_bss_3A8[i]->data;
        if(lane == other->lane || lane == other->laneTo) {
            d = fabs(player->pos.y - other->pos.y);
            if(d <= 150.0f) {
                return 0;
            }
        }
    }
    return 1;
}

static void fn_1_20A8(HuVecF *pos)
{
    float top;
    float bottom;

    top = 280.0f + Center.y;
    bottom = Center.y - 350.0f;
    if(top < 150.0f + pos->y) {
        pos->y = top - 150.0f;
    }
    if(bottom > pos->y) {
        pos->y = bottom;
    }
}

static void fn_1_214C(OMOBJ *obj)
{
    M572_PLAYER *player;
    M572_PLAYER *other;
    int i;
    int unusedFlag;
    HuVecF v;
    HuVecF n;
    HuVecF a;
    HuVecF b;
    float dist;
    float otherSpeed;
    float mySpeed;
    float w;

    player = obj->data;
    if(player->playerNo == 1) {
        unusedFlag = 0;
    }
    PSVECSubtract(&player->pos, &player->posPrev, &v);
    mySpeed = PSVECMag(&v);
    if(0.0f == mySpeed) {
        return;
    }
    for(i=0; i<4; i++) {
        if(i == player->playerNo) {
            continue;
        }
        other = lbl_1_bss_3A8[i]->data;
        if(player->lane != other->lane) {
            continue;
        }
        if(player->playerNo == 1 && other->playerNo == 0) {
            unusedFlag = 0;
        }
        a.x = player->pos.x;
        a.y = player->pos.y;
        a.z = player->pos.z;
        a.z = 0.0f;
        b.x = other->pos.x;
        b.y = other->pos.y;
        b.z = other->pos.z;
        b.z = 0.0f;
        PSVECSubtract(&a, &b, &v);
        dist = PSVECMag(&v);
        if(dist >= 159.2f) {
            continue;
        }
        PSVECSubtract(&other->pos, &other->posPrev, &v);
        otherSpeed = PSVECMag(&v);
        PSVECSubtract(&a, &b, &n);
        if(0.0f == n.x && 0.0f == n.y && 0.0f == n.x) {
            continue;
        }
        PSVECNormalize(&n, &n);
        dist = 160.0f - dist;
        w = ((0.6f * otherSpeed) + (0.4f * mySpeed)) / (mySpeed + otherSpeed);
        player->pos.y += w * (dist * n.y);
        w = ((0.6f * mySpeed) + (0.4f * mySpeed)) / (mySpeed + otherSpeed);
        other->pos.y += w * (dist * -n.y);
    }
}

static void fn_1_2404(OMOBJ *obj)
{
    M572_PLAYER *player;
    s32 kind;
    s32 l;
    s32 r;

    player = obj->data;
    player->btn |= PAD_BUTTON_A;
    player->btnDown = 0;
    kind = fn_1_3D28(obj, 1);
    if(kind == 1 || kind == 5) {
        s32 rnd = frandmod(2);
        if(rnd == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else if(rnd == 1) {
            player->btnDown |= PAD_TRIGGER_R;
        }
    }
    kind = fn_1_3D28(obj, 2);
    if(kind == -1) {
        l = 1;
    } else {
        l = 0;
    }
    kind = fn_1_3D28(obj, 3);
    if(kind == -1) {
        r = 1;
    } else {
        r = 0;
    }
    if(l == 1 && r == 1) {
        if(frandmod(2) == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else {
            player->btnDown |= PAD_TRIGGER_R;
        }
    } else if(l) {
        player->btnDown |= PAD_TRIGGER_L;
    } else if(r) {
        player->btnDown |= PAD_TRIGGER_R;
    }
}

static void fn_1_2574(OMOBJ *obj)
{
    M572_PLAYER *player;
    s32 kind;
    s32 l;
    s32 r;

    player = obj->data;
    player->btn |= PAD_BUTTON_A;
    player->btnDown = 0;
    kind = fn_1_3D28(obj, 1);
    if(kind == 5) {
        s32 rnd = frandmod(2);
        if(rnd == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else if(rnd == 1) {
            player->btnDown |= PAD_TRIGGER_R;
        }
    }
    kind = fn_1_3D28(obj, 2);
    if(kind == -1 || kind == 1) {
        l = 1;
    } else {
        l = 0;
    }
    kind = fn_1_3D28(obj, 3);
    if(kind == -1 || kind == 1) {
        r = 1;
    } else {
        r = 0;
    }
    if(l == 1 && r == 1) {
        if(frandmod(2) == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else {
            player->btnDown |= PAD_TRIGGER_R;
        }
    } else if(l) {
        player->btnDown |= PAD_TRIGGER_L;
    } else if(r) {
        player->btnDown |= PAD_TRIGGER_R;
    }
}

static void fn_1_26EC(OMOBJ *obj)
{
    M572_PLAYER *player;
    s32 kind;
    s32 l;
    s32 r;

    player = obj->data;
    player->btn |= PAD_BUTTON_A;
    player->btnDown = 0;
    kind = fn_1_3D28(obj, 2);
    if(kind != -2) {
        l = 1;
    } else {
        l = 0;
    }
    kind = fn_1_3D28(obj, 3);
    if(kind != -2) {
        r = 1;
    } else {
        r = 0;
    }
    if(l == 1 && r == 1) {
        if(frandmod(2) == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else {
            player->btnDown |= PAD_TRIGGER_R;
        }
    } else if(l) {
        player->btnDown |= PAD_TRIGGER_L;
    } else if(r) {
        player->btnDown |= PAD_TRIGGER_R;
    }
}

static void fn_1_27FC(OMOBJ *obj)
{
    M572_PLAYER *player;
    s32 kind;
    s32 l;
    s32 r;

    player = obj->data;
    player->btn |= PAD_BUTTON_A;
    player->btnDown = 0;
    kind = fn_1_3D28(obj, 1);
    if(kind == -1) {
        s32 rnd = frandmod(2);
        if(rnd == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else if(rnd == 1) {
            player->btnDown |= PAD_TRIGGER_R;
        }
    }
    kind = fn_1_3D28(obj, 2);
    if(kind != -1 && kind != -2) {
        l = 1;
    } else {
        l = 0;
    }
    kind = fn_1_3D28(obj, 3);
    if(kind != -1 && kind != -2) {
        r = 1;
    } else {
        r = 0;
    }
    if(l == 1 && r == 1) {
        if(frandmod(2) == 0) {
            player->btnDown |= PAD_TRIGGER_L;
        } else {
            player->btnDown |= PAD_TRIGGER_R;
        }
    } else if(l) {
        player->btnDown |= PAD_TRIGGER_L;
    } else if(r) {
        player->btnDown |= PAD_TRIGGER_R;
    }
}

static void fn_1_2974(s16 mode, s16 frameNo)
{
    s32 charNo[4];
    M572_PLAYER *player;
    s32 i;
    s32 b;
    s32 c;
    s32 d;

    lbl_1_bss_10[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x00), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_10[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x01), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelShadowMapSet(lbl_1_bss_10[1]);
    Hu3DModelAttrSet(lbl_1_bss_10[0], HU3D_MOTATTR_LOOP);
    for(i=0; i<4; i++) {
        player = lbl_1_bss_3A8[i]->data;
        charNo[i] = player->charNo;
    }
    d = charNo[3];
    c = charNo[2];
    b = charNo[1];
    lbl_1_bss_43C[0] = charNo[0];
    lbl_1_bss_43C[1] = b;
    lbl_1_bss_43C[2] = c;
    lbl_1_bss_43C[3] = d;
    lbl_1_bss_438 = 1;
    omAddObjEx(lbl_1_bss_680, 101, 0, 0, -1, fn_1_7DF8);
    MgSeqModeNext();
    lbl_1_bss_35C = HuAudSStreamPlay(0x3D);
}

static void fn_1_2AD8(s16 mode, s16 frameNo)
{
    M571_HOST *host;
    s32 i;
    M572_PILLAR *pillar;
    s32 j;
    M572_PLAYER *player;

    host = lbl_1_bss_478[0]->data;
    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    host->unk30 = 1;
    for(i=0; i<150; i++) {
        HuPrcVSleep();
    }
    omCameraViewMoveSimple(&lbl_1_data_204, 90);
    host->unk38 = 0;
    host->unk30 = 12;
    HuAudFXPlay(0x96E);
    for(i=0; i<9; i++) {
        pillar = lbl_1_bss_3A0[i]->data;
        pillar->mode = 1;
        Hu3DModelAttrReset(pillar->mdlId2, HU3D_MOTATTR_PAUSE);
        for(j=0; j<5; j++) {
            HuPrcVSleep();
        }
    }
    for(i=0; i<45.0f; i++) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        player = lbl_1_bss_3A8[i]->data;
        player->mode = 1;
    }
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
    MgSeqModeNext();
}

static void fn_1_2C9C(s16 mode, s16 frameNo)
{
    M571_HOST *host;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 0) {
    }
    fn_1_33A4();
    fn_1_45E0();
    if(lbl_1_bss_C == 0) {
        MgSeqModeNext();
    }
}

static void fn_1_2CFC(s16 mode, s16 frameNo)
{
    M572_PLAYER *player;
    s32 i;
    s32 j;
    s32 done;

    if(MgSeqFrameNoGet() == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_35C, 100);
        for(i=0; i<4; i++) {
            player = lbl_1_bss_3A8[i]->data;
            Hu3DMotionSpeedSet(player->mdlId, 0.0f);
        }
    }
    if(MgSeqFrameNoGet() > 300) {
        /* fn_1_8E08 inlined: both arms say done. */
        for(j=0; j<20; j++) {
            if(lbl_1_bss_368[j] != NULL) {
                done = 1;
                goto ready;
            }
        }
        done = 1;
    ready:
        if(done != 0) {
            MgSeqModeNext();
        }
    }
}

static void fn_1_2DF0(s16 mode, s16 frameNo)
{
    M571_HOST *host;
    s32 i;
    M572_PLAYER *player;
    OMOBJ *hostObj;
    M571_HOST *host2;
    M572_PILLAR *pillar;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 30) {
        WipeCreate(2, 6, 30);
        WipeColorSet(255, 255, 255);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        omCameraViewSet(&lbl_1_data_220);
        for(i=0; i<4; i++) {
            player = lbl_1_bss_3A8[i]->data;
            player->pos.x = lbl_1_data_2A0[i].x;
            player->pos.y = lbl_1_data_2A0[i].y;
            player->pos.z = lbl_1_data_2A0[i].z;
            player->rot.x = player->rot.y = player->rot.z = 0.0f;
            Hu3DModelAttrReset(player->mdlId, HU3D_ATTR_DISPOFF);
            fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 0, 0.0f, HU3D_MOTATTR_LOOP);
            player->score = lbl_1_bss_428[player->playerNo];
            CharModelVoicePanSet((s16)player->charNo, fn_1_92D4(&player->pos));
        }
        host->unk30 = 0;
        hostObj = lbl_1_bss_478[0];
        host2 = hostObj->data;
        Hu3DMotionSpeedSet(host2->modelId, 1.0f);
        if(host2->motNo != 0) {
            host2->motNo = 0;
            Hu3DMotionShiftSet(host2->modelId, lbl_1_bss_44C[0], 0.0f, 0.0f, HU3D_MOTATTR_LOOP);
        }
        host->pos.x = lbl_1_data_70.x;
        host->pos.y = lbl_1_data_70.y;
        host->pos.z = lbl_1_data_70.z;
        host->rot.x = host->rot.y = host->rot.z = 0.0f;
        fn_1_3634();
        for(i=0; i<9; i++) {
            pillar = lbl_1_bss_3A0[i]->data;
            Hu3DModelAttrSet(pillar->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(pillar->mdlId2, HU3D_ATTR_DISPOFF);
        }
        WipeCreate(1, 5, 30);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        MgSeqModeNext();
    }
}

static void fn_1_30FC(s16 mode, s16 frameNo)
{
    s32 i;
    M571_HOST *host;
    M572_PLAYER *player;

    host = lbl_1_bss_478[0]->data;
    if(MgSeqFrameNoGet() == 0) {
        host->unk30 = 6;
        host->unk38 = 0;
        for(i=0; i<4; i++) {
            player = lbl_1_bss_3A8[i]->data;
            if(player->score >= 1) {
                fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 1, 8.0f, 0);
            } else {
                fn_1_32A8(lbl_1_bss_3A8[player->playerNo], 2, 8.0f, 0);
                if(lbl_1_bss_428[0] == 0 && lbl_1_bss_428[1] == 0 && lbl_1_bss_428[2] == 0 && lbl_1_bss_428[3] == 0) {
                    CharFXPlay((s16)player->charNo, 0x200);
                }
            }
            GWMgCoinBonusAdd(player->playerNo, player->score);
        }
    }
}

static void fn_1_32A8(OMOBJ *obj, s32 motNo, float time, s32 attr)
{
    M572_PLAYER *player;

    player = obj->data;
    if (player->motNo != motNo) {
        player->motNo = motNo;
        CharMotionShiftSet(player->charNo, obj->mtnId[player->motNo], 0.0f, time, attr);
        player->unk30 = 0.0f;
    }
}

static void fn_1_3344(OMOBJ *obj, s32 motNo)
{
    M572_PLAYER *player;

    player = obj->data;
    player->motNo = motNo;
    CharMotionSet(player->charNo, obj->mtnId[player->motNo]);
}

static void fn_1_33A4(void)
{
}

static void fn_1_33A8(void)
{
    HuVecF pos;
    s32 pattern;
    s32 i;

    pattern = frandmod(3);
    for (i = 0; i < 225; i++) {
        if (lbl_1_data_3A4[pattern][i] != 0) {
            fn_1_4C04(&pos, i);
            fn_1_3454(pos.x, pos.y, pos.z, lbl_1_data_3A4[pattern][i], i);
        }
    }
}

static void fn_1_3454(float x, float y, float z, s32 kind, s32 no)
{
    OMOBJ *obj;
    M572_ITEM *item;

    if (lbl_1_bss_C <= 224) {
        lbl_1_bss_C++;
        obj = omAddObjEx(lbl_1_bss_680, 101, 1, 2, 1, fn_1_370C);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M572_ITEM), HU_MEMNUM_OVL);
        obj->work[0] = kind;
        item = obj->data;
        item->pos.x = x;
        item->pos.y = y;
        item->pos.z = z;
        item->rot.x = item->rot.y = item->rot.z = 0.0f;
        item->kind = kind;
        item->scale.x = item->scale.y = item->scale.z = 1.0f;
        item->mode = 0;
        item->timer = 0;
        item->no = no;
        item->col = no % 9;
        item->motNo = 2;
    }
}

static void fn_1_35A8(OMOBJ *obj)
{
    M572_ITEM *item;

    item = obj->data;
    Hu3DModelKill(obj->mdlId[0]);
    lbl_1_bss_C--;
    lbl_1_bss_1C[item->no] = NULL;
    omDelObjEx(lbl_1_bss_680, obj);
}

static void fn_1_3634(void)
{
    s32 i;

    for (i = 0; i < 225; i++) {
        if (lbl_1_bss_1C[i] != NULL) {
            fn_1_35A8(lbl_1_bss_1C[i]);
        }
    }
}

static void fn_1_370C(OMOBJ *obj)
{
    M572_ITEM *item;
    float drop;
    float maxTime;
    float time;

    item = obj->data;
    if (obj->work[0] == 1) {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_8);
        drop = 30.0f;
    } else if (obj->work[0] == 5) {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_6);
        drop = 30.0f;
    } else {
        obj->mdlId[0] = Hu3DModelLink(lbl_1_bss_4);
        obj->mtnId[0] = Hu3DJointMotionData(obj->mdlId[0], DATANUM(DATA_m572, 0x0E));
        obj->mtnId[1] = Hu3DJointMotionData(obj->mdlId[0], DATANUM(DATA_m572, 0x0F));
        Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
        Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
        maxTime = Hu3DMotionMaxTimeGet(obj->mdlId[0]);
        time = (1.0f / 255.0f) * maxTime * (frand() & 0xFF);
        Hu3DMotionTimeSet(obj->mdlId[0], time);
        drop = 0.0f;
    }
    item->pos.y -= drop;
    omSetTra(obj, item->pos.x, item->pos.y, item->pos.z);
    omSetRot(obj, item->rot.x, item->rot.y, item->rot.z);
    omSetSca(obj, item->scale.x, item->scale.y, item->scale.z);
    lbl_1_bss_1C[item->no] = obj;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = fn_1_3954;
}

static void fn_1_3954(OMOBJ *obj)
{
    M572_ITEM *item;
    M572_PILLAR *pillar;
    float y;

    item = obj->data;
    pillar = lbl_1_bss_3A0[item->col]->data;
    switch (item->mode) {
    case 0:
        break;
    case 1:
        if (item->kind == -1) {
            if (item->timer > 30) {
                fn_1_3C9C(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
                item->mode = 2;
                item->timer = 0;
            } else {
                fn_1_3C9C(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
                item->timer++;
                if (item->timer & 1) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
                }
            }
        } else {
            fn_1_35A8(obj);
            if (item->kind == 1) {
                fn_1_8D54(&item->pos, item->playerNo, 1);
            } else if (item->kind == 5) {
                fn_1_8D54(&item->pos, item->playerNo, 5);
            }
        }
        break;
    case 2:
        fn_1_35A8(obj);
        break;
    }
    y = pillar->pos.y - 45.0f;
    omSetTra(obj, item->pos.x, item->pos.y + y, item->pos.z);
    omSetRot(obj, item->rot.x, item->rot.y, item->rot.z);
    omSetSca(obj, item->scale.x, item->scale.y, item->scale.z);
}

static void fn_1_3C9C(OMOBJ *obj, s32 motNo, float time, s32 attr)
{
    M572_ITEM *item;

    item = obj->data;
    if (item->motNo != motNo) {
        item->motNo = motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[item->motNo], 0.0f, time, attr);
    }
}

static s32 fn_1_3D28(OMOBJ *obj, s32 dir)
{
    M572_PLAYER *player;
    M572_ITEM *item;
    s32 i;
    HuVecF ipos;
    HuVecF ppos;
    HuVecF cpos;
    float r;

    player = obj->data;
    for(i = 0; i < 225; i++) {
        if(lbl_1_bss_1C[i] == NULL) {
            continue;
        }
        item = lbl_1_bss_1C[i]->data;
        if(item->mode != 0) {
            continue;
        }
        if(dir == 0 || dir == 1) {
            if(player->lane != item->col) {
                continue;
            }
        }
        fn_1_4C04(&cpos, i);
        ipos.x = cpos.x;
        ipos.y = 0.0f;
        ipos.z = cpos.y;
        ppos.y = 0.0f;
        if(item->kind == 1) {
            r = 25.0f;
        } else if(item->kind == 5) {
            r = 40.0f;
        } else {
            r = 40.0f;
        }
        if(dir == 1) {
            ppos.x = player->pos.x;
            ppos.z = 35.0f + (150.0f + player->pos.y);
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                return item->kind;
            }
        } else if(dir == 2) {
            ppos.x = player->pos.x - 120.0f;
            ppos.z = 75.0f + player->pos.y;
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                return item->kind;
            }
        } else if(dir == 3) {
            ppos.x = 120.0f + player->pos.x;
            ppos.z = 75.0f + player->pos.y;
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                return item->kind;
            }
        } else if(dir == 4) {
            ppos.x = player->pos.x - 120.0f;
            ppos.z = 50.0f + (150.0f + player->pos.y);
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                return item->kind;
            }
        } else if(dir == 5) {
            ppos.x = 120.0f + player->pos.x;
            ppos.z = 50.0f + (150.0f + player->pos.y);
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                return item->kind;
            }
        } else {
            ppos.x = player->pos.x;
            ppos.z = 75.0f + player->pos.y;
            if(fn_1_90C8(&ipos, &ppos, r, 75.0f)) {
                return i;
            }
        }
    }
    return -2;
}

static s32 fn_1_42DC(OMOBJ *obj, s32 dir)
{
    M572_ITEM *item;
    s32 i;
    M572_PLAYER *player;
    HuVecF ipos;
    HuVecF ppos;
    HuVecF cpos;
    float r;

    player = obj->data;
    for(i = 0; i < 225; i++) {
        if(lbl_1_bss_1C[i] == NULL) {
            continue;
        }
        item = lbl_1_bss_1C[i]->data;
        if(item->mode != 0) {
            continue;
        }
        if(player->lane != item->col) {
            continue;
        }
        fn_1_4C04(&cpos, i);
        ipos.x = cpos.x;
        ipos.y = 0.0f;
        ipos.z = cpos.y;
        ppos.x = player->pos.x;
        ppos.y = 0.0f;
        if(item->kind == 1) {
            r = 25.0f;
        } else if(item->kind == 5) {
            r = 40.0f;
        } else {
            r = 40.0f;
        }
        if(dir == 1) {
            ppos.z = 50.0f + (150.0f + player->pos.y);
            if(fn_1_90C8(&ipos, &ppos, r, 0.0f)) {
                OSReport("%d COM HIT ppos.z:%f kind:%d\n", i, ppos.z, item->kind);
                return item->kind;
            }
        } else {
            ppos.z = 75.0f + player->pos.y;
            if(fn_1_90C8(&ipos, &ppos, r, 75.0f)) {
                OSReport("%d BANANA HIT ppos.z:%f kind:%d\n", i, ppos.z, item->kind);
                return i;
            }
        }
    }
    return -2;
}

static s32 fn_1_45A4(s32 cellNo, s32 playerNo)
{
    M572_ITEM *item;

    item = lbl_1_bss_1C[cellNo]->data;
    item->mode = 1;
    item->playerNo = playerNo;
    return item->kind;
}

static void fn_1_45E0(void)
{
    Center.y += 3.5833333f;
    if(Center.y > 2500.0f) {
        Center.y = 2500.0f;
    }
}

static void fn_1_463C(void)
{
    GXColor color;

    color.r = 0;
    color.g = 0;
    color.b = 144;
    color.a = 192;
    CZoom += HuPadTrigL[0] / 5;
    CZoom -= HuPadTrigR[0] / 5;
    Center.y -= 2.0f * (HuPadSubStkY[0] / 59.0f);
    CRot.x += 5.0f * (HuPadSubStkY[1] / 59.0f);
    CRot.y -= 5.0f * (HuPadSubStkX[1] / 59.0f);
    printWin(16, 40, 384, 36, &color);
    fontcolor = 14;
    print8(16, 40, 1.5f, "Center X:%.02f Y:%.02f Z:%.02f", Center.x, Center.y, Center.z);
    print8(16, 52, 1.5f, "CRot X:%.02f Y:%.02f Z:%.02f", CRot.x, CRot.y, CRot.z);
    print8(16, 64, 1.5f, "CZoom:%.02f", CZoom);
    if(HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&lbl_1_data_204);
    }
}

static void fn_1_498C(void)
{
    GXColor color;

    color.r = 0;
    color.g = 0;
    color.b = 144;
    color.a = 192;
    if(HuPadSubStkY[0] > 29.5f) {
        Center.y += 3.5833333f;
        if(Center.y > 2500.0f) {
            Center.y = 2500.0f;
        }
    }
    if(HuPadSubStkY[0] < -29.5f) {
        Center.y -= 3.5833333f;
        if(Center.y < 350.0f) {
            Center.y = 350.0f;
        }
    }
    CRot.x += 5.0f * (HuPadSubStkY[1] / 59.0f);
    CRot.y -= 5.0f * (HuPadSubStkX[1] / 59.0f);
    if(HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&lbl_1_data_204);
    }
}

static void fn_1_4C04(HuVecF *out, s32 cellNo)
{
    s32 col;
    s32 row;

    col = cellNo % 9;
    row = cellNo / 9;
    out->x = (120.0f*col)-480.0f;
    out->y = 2000.0f-((100.0f*row)-400.0f);
    out->z = -40.0f;
}

