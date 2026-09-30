/*
 * m573dll -- "KAWASHITE BANANA" (MG_TYPE_DONKEY), four players dodging
 * what Donkey Kong throws at them.
 *
 * One translation unit, 75 functions, 8,742 instructions; 72 written, 67 of
 * them exact. The three that are still stubs -- fn_1_2F40, fn_1_37A4 and
 * fn_1_3AD8 -- are unreferenced dead code, so the overlay runs without them;
 * NEXT.md says why they are not worth writing.
 *
 * Wired into PB_REL_FILES and RUN on 2026-09-02: it links, loads
 * (devBootOverlay=7, devForceMinigame=84), plays and returns to instdll, with
 * every heap total unchanged across the run.
 *
 * Each entry below carries the fn_1_XXXX it reproduces, that function's
 * reference instruction count, and the line range it occupies in
 *
 *     build/mp5-asm/m573dll/asm/REL/m573dll/m573.s
 *
 * so the next session can open any one of them without re-deriving the map.
 * Regenerate the asm with `./games/mp5/gen_asm.sh m573dll`; nothing under
 * build/ is committed.
 *
 * Verify per function, never by the headline number:
 *
 *   ./build/tools/ninja build/GP5E01_00/src/REL/m573dll/m573.o
 *   R=../../build/mp5-asm/m573dll/obj/REL/m573dll/m573.o
 *   O=build/GP5E01_00/src/REL/m573dll/m573.o
 *   diff <(./fndiff.py fn $R fn_1_5C8) <(./fndiff.py fn $O M573PlayerInit)
 *
 * | function      | insns | asm lines   |
 * | ------------- | ----: | ----------- |
 * | `ObjectSetup` |   330 |    61-396   |
 * | `fn_1_5C8   ` |   189 |   399-597   |
 * | `fn_1_8BC   ` |   316 |   600-927   |
 * | `fn_1_DAC   ` |    78 |   930-1016  |
 * | `fn_1_EE4   ` |    81 |  1019-1103  |
 * | `fn_1_1028  ` |   164 |  1106-1278  |
 * | `fn_1_12B8  ` |   281 |  1281-1573  |
 * | `fn_1_171C  ` |    68 |  1576-1655  |
 * | `fn_1_182C  ` |   122 |  1658-1786  |
 * | `fn_1_1A14  ` |    89 |  1789-1881  |
 * | `fn_1_1B78  ` |    49 |  1884-1940  |
 * | `fn_1_1C3C  ` |    26 |  1943-1972  |
 * | `fn_1_1CA4  ` |    72 |  1975-2057  |
 * | `fn_1_1DC4  ` |   188 |  2060-2255  |
 * | `fn_1_20B4  ` |   107 |  2258-2372  |
 * | `fn_1_2260  ` |    35 |  2375-2412  |
 * | `fn_1_22EC  ` |     1 |  2415-2417  |
 * | `fn_1_22F0  ` |   177 |  2420-2602  |
 * | `fn_1_25B4  ` |    55 |  2605-2664  |
 * | `fn_1_2690  ` |    97 |  2667-2768  |
 * | `fn_1_2814  ` |    15 |  2771-2787  |
 * | `fn_1_2850  ` |    38 |  2790-2830  |
 * | `fn_1_28E8  ` |    57 |  2833-2895  |
 * | `fn_1_29CC  ` |    70 |  2898-2972  |
 * | `fn_1_2AE4  ` |   175 |  2975-3160  |
 * | `fn_1_2DA0  ` |   104 |  3163-3277  |
 * | `fn_1_2F40  ` |   240 |  3280-3522  |
 * | `fn_1_3300  ` |     9 |  3525-3535  |
 * | `fn_1_3324  ` |    34 |  3538-3574  |
 * | `fn_1_33AC  ` |    41 |  3577-3624  |
 * | `fn_1_3450  ` |    22 |  3627-3652  |
 * | `fn_1_34A8  ` |    69 |  3655-3732  |
 * | `fn_1_35BC  ` |    87 |  3735-3824  |
 * | `fn_1_3718  ` |    35 |  3827-3863  |
 * | `fn_1_37A4  ` |   205 |  3866-4076  |
 * | `fn_1_3AD8  ` |   249 |  4079-4335  |
 * | `fn_1_3EBC  ` |    65 |  4338-4407  |
 * | `fn_1_3FC0  ` |    27 |  4410-4440  |
 * | `fn_1_402C  ` |    22 |  4443-4466  |
 * | `fn_1_4084  ` |    15 |  4469-4485  |
 * | `fn_1_40C0  ` |    24 |  4488-4515  |
 * | `fn_1_4120  ` |    49 |  4518-4568  |
 * | `fn_1_41E4  ` |    49 |  4571-4621  |
 * | `fn_1_42A8  ` |    66 |  4624-4698  |
 * | `fn_1_43B0  ` |    31 |  4701-4733  |
 * | `fn_1_442C  ` |    24 |  4736-4761  |
 * | `fn_1_448C  ` |    98 |  4764-4866  |
 * | `fn_1_4614  ` |    96 |  4869-4969  |
 * | `fn_1_4794  ` |  2322 |  4972-7402  |
 * | `fn_1_6BDC  ` |   258 |  7405-7672  |
 * | `fn_1_6FE4  ` |    20 |  7675-7698  |
 * | `fn_1_7034  ` |   204 |  7701-7915  |
 * | `fn_1_7364  ` |   333 |  7918-8257  |
 * | `fn_1_7898  ` |    13 |  8260-8275  |
 * | `fn_1_78CC  ` |    24 |  8278-8303  |
 * | `fn_1_792C  ` |     4 |  8306-8311  |
 * | `fn_1_793C  ` |    42 |  8314-8357  |
 * | `fn_1_79E4  ` |     6 |  8360-8367  |
 * | `fn_1_79FC  ` |    61 |  8370-8437  |
 * | `fn_1_7AF0  ` |    52 |  8440-8497  |
 * | `fn_1_7BC0  ` |   189 |  8500-8696  |
 * | `fn_1_7EB4  ` |    68 |  8699-8772  |
 * | `fn_1_7FC4  ` |    84 |  8775-8860  |
 * | `fn_1_8114  ` |   107 |  8863-8972  |
 * | `fn_1_82C0  ` |    45 |  8975-9021  |
 * | `fn_1_8374  ` |    21 |  9024-9050  |
 * | `fn_1_83C8  ` |     5 |  9053-9059  |
 * | `fn_1_83DC  ` |    12 |  9062-9075  |
 * | `fn_1_840C  ` |    12 |  9078-9091  |
 * | `fn_1_843C  ` |   126 |  9094-9225  |
 * | `fn_1_8634  ` |    24 |  9228-9255  |
 * | `fn_1_8694  ` |    92 |  9258-9353  |
 * | `fn_1_8804  ` |    15 |  9356-9372  |
 * | `fn_1_8840  ` |    31 |  9375-9407  |
 * | `fn_1_88BC  ` |    31 |  9410-9442  |
 *
 * fn_1_4794 is 2,322 instructions on its own -- 26% of the file. It is a
 * 29-way switch on host->unk30 through the jumptable at data_130, and most of
 * its bulk is helpers defined above it being inlined: M573Unk42A8,
 * M573Unk43B0, M573Unk448C, M573Unk4614 and M573Unk3EBC. A case that reloads
 * obj->data into a fresh register has had one of them inlined into it.
 *
 * The three functions still empty -- fn_1_2F40, fn_1_37A4 and fn_1_3AD8 --
 * are unreferenced: a leftover debug camera and two alternate camera
 * routines that shipped with nothing calling them. They do not affect
 * whether this overlay runs.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/mg/seqman.h"
#include "game/mg/score.h"
#include "game/gamemes.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"

/*
 * The player object's work, 0x90 bytes, allocated per player in ObjectSetup
 * and hung off OMOBJ.data. Named as fields are pinned down; the padding is
 * exact, so an unkNN is unexplained rather than unallocated.
 */
typedef struct M573Player_s {
    /* 0x00 */ s16 motNo;
    /* 0x02 */ u8 unk02[0x0E];
    /* 0x10 */ int playerNo;
    /* 0x14 */ int charNo;
    /* 0x18 */ int padNo;
    /* 0x1C */ int unk1C;
    /* 0x20 */ int unk20;
    /* 0x24 */ int unk24;
    /* 0x28 */ HuVecF pos;
    /* 0x34 */ HuVecF posLast;
    /* 0x40 */ HuVecF posPrev;
    /* 0x4C */ HuVecF rot;
    /* 0x58 */ float speed;
    /* 0x5C */ HuVecF vel;
    /* 0x68 */ float unk68;
    /* 0x6C */ float unk6C;
    /* 0x70 */ int dif;
    /* 0x74 */ int mode;
    /* 0x78 */ HuVecF target;
    /* 0x84 */ int unk84;
    /* 0x88 */ int comWait;
    /* 0x8C */ int unk8C;
} M573_PLAYER;                     /* 0x90 */

/* The host object's work, 0xB0 bytes: Donkey Kong himself. */
typedef struct M573Host_s {
    /* 0x00 */ HU3DMODELID modelId;
    /* 0x02 */ s16 pad02;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ u8 unk10[0x0C];
    /* 0x1C */ HuVecF rot;
    /* 0x28 */ float unk28;
    /* 0x2C */ int motNo;
    /* 0x30 */ int unk30;
    /* 0x34 */ int unk34;
    /* 0x38 */ int unk38;
    /* 0x3C */ float unk3C;
    /* 0x40 */ float unk40;
    /* 0x44 */ int unk44;      /* how many frames the 0x80 move takes */
    /* 0x48 */ int unk48;      /* and the two hop states' frame counts */
    /* 0x4C */ int unk4C;
    /* 0x50 */ float unk50;    /* how far the hop travels */
    /* 0x54 */ HU3DMODELID unk54;
    /* 0x56 */ HU3DMODELID unk56;
    /* 0x58 */ HU3DMODELID unk58;
    /* 0x5A */ u8 unk5A[0x06];
    /* 0x60 */ int unk60;
    /* 0x64 */ float unk64;
    /* 0x68 */ float unk68;
    /* 0x6C */ float unk6C;
    /* 0x70 */ float unk70;
    /* 0x74 */ float unk74;
    /* 0x78 */ u8 unk78[0x04];
    /* 0x7C */ int unk7C;
    /* 0x80 */ HuVecF dest;    /* a straight-line move: where to, */
    /* 0x8C */ HuVecF from;    /* where from, */
    /* 0x98 */ HuVecF step;    /* and the per-frame delta between them */
    /* 0xA4 */ int unkA4;
    /* 0xA8 */ HU3DMODELID unkA8[2];
    /* 0xAC */ HU3DMODELID unkAC;
    /* 0xAE */ s16 padAE;
} M573_HOST;                       /* 0xB0 */

/* The work of one thrown thing, hung off the group-1 objects in Objs[]. */
typedef struct M573Item_s {
    /* 0x00 */ HuVecF pos;
    /* 0x0C */ HuVecF rot;
    /* 0x18 */ HuVecF scale;
    /* 0x24 */ int kind;
    /* 0x28 */ int no;         /* its own slot in Objs[] */
    /* 0x2C */ int unk2C;
    /* 0x30 */ int unk30;
    /* 0x34 */ int playerNo;
} M573_ITEM;

/* The 0x18 work of the objects M573Unk82C0 spawns. */
typedef struct M573Eff_s {
    /* 0x00 */ int unk00;
    /* 0x04 */ int unk04;
    /* 0x08 */ int unk08;
    /* 0x0C */ HuVecF pos;
} M573_EFF;                        /* 0x18 */

/* The work of the twenty things Unk170 holds. */
typedef struct M573Slot2_s {
    /* 0x00 */ int mode;
    /* 0x04 */ int timer;
    /* 0x08 */ HuVecF pos;
    /* 0x14 */ HuVecF rot;
    /* 0x20 */ HuVecF target;   /* where it is flying to, in world space */
    /* 0x2C */ HuVecF vel;
    /* 0x38 */ HuVecF screen;   /* and where that is on screen */
    /* 0x44 */ int no;
} M573_SLOTOBJ;                    /* 0x48 */

/* bss_48C heads a doubly-linked list of these; M573Unk3324 pushes one on. */
typedef struct M573Node_s {
    /* 0x00 */ u16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ struct M573Node_s *prev;
    /* 0x08 */ struct M573Node_s *next;
} M573_NODE;                       /* 0x0C */

/*
 * NO datanum/m573.h, for the same reason m560dll has none: the archive at
 * files/data/m573.bin carries no file names, so every name here would be
 * invented and would conflict with upstream's if they ever publish one.
 * The raw DATANUM(DATA_m573, n) is used instead.
 */

/* --- .data --- */

/* The nine sequence hooks data_2A4 names, and the two object mains. */
static void M573PlayerInit(OMOBJ *obj);
static void M573PlayerMain(OMOBJ *obj);
static void M573HostInit(OMOBJ *obj);
static void M573InitHook(s16 mode, s16 frameNo);
static void M573FadeInHook(s16 mode, s16 frameNo);
static void M573MainHook(s16 mode, s16 frameNo);
static void M573FinishHook(s16 mode, s16 frameNo);
static void M573PreWinnerHook(s16 mode, s16 frameNo);
static void M573WinnerHook(s16 mode, s16 frameNo);
static void M573Unk25B4(void);
static void M573Unk22EC(void);
static int M573Unk8374(void);
#ifndef __MWERKS__
/* Called before its definition with no prototype; GCC rejects the implicit extern
   declaration followed by a static definition. Kept out of the CW build. */
static int M573Unk6FE4(void);
#endif
static void M573Unk3450(void);
static void M573Unk402C(HU3DMODELID modelId, char *objName, HuVecF *dst);
static int M573HitCheck(HuVecF *a, HuVecF *b, float ra, float rb);
static int M573HitCheck2(HuVecF *a, HuVecF *b, float ra, float rb);
static void M573Unk442C(OMOBJ *obj, int motNo);
static void M573Unk7898(OMOBJ *obj);
static int M573Unk2814(int no, int playerNo);
static int M573RandRange(int min, int max);
static int M573RandRange2(int min, int max);
static int M573PanGet(HuVecF *pos);
static int M573VolGet(HuVecF *pos);
static int M573ScreenXLerp(HuVecF *pos, int min, int max);
static int M573ScreenYLerp(HuVecF *pos, int min, int max);
static void M573Unk792C(int val);
static void M573Unk79E4(int no, int val);
static void M573Unk83C8(void);
static void M573Unk3300(void);
static void M573Unk83DC(void);
static void M573Unk840C(void);
static void M573Unk78CC(void);
static void M573Unk43B0(OMOBJ *obj, int motNo, float time, int attr);
static void M573Unk3324(u16 a, s16 b);
static void M573Unk2260(OMOBJ *obj, int motNo, float time, int attr);
static void M573Unk3718(HuVecF *pos, HuVecF *up, HuVecF *aim);
static void M573Unk2850(OMOBJ *obj);
static s16 M573Unk33AC(s16 key);
static void M573Unk793C(int a, int b, int c, int d, int e);
static void M573Unk7364(OMOBJ *obj);
static void M573Unk2690(float x, float y, float z, int kind, int no);
static HU3DMODELID M573Unk34A8(u32 dataNum);
static void M573Unk2AE4(OMOBJ *obj);
static void M573Unk29CC(OMOBJ *obj);
static int M573Unk1028(HuVecF *pos, HuVecF *dst);
static int M573UnkEE4(OMOBJ *obj);
static void M573Unk8114(OMOBJ *obj);
static void M573Unk7BC0(OMOBJ *obj);
static void M573Unk7EB4(OMOBJ *obj);
static void M573Unk28E8(void);
static void M573Unk4794(OMOBJ *obj);
static void M573UnkDAC(OMOBJ *obj);
static void M573Unk12B8(M573_PLAYER *player, OMOBJ *obj);
static int M573Unk2DA0(HuVecF *pos, float radius);
static int M573Unk171C(HuVecF *pos, float radius);
static void M573Unk22F0(OMOBJ *obj);

/* data_0 -- each character's face icon for the score windows, indexed by
 * character number. Note 0x25 is skipped. */
static u32 CharIconTbl[13] = {
    DATANUM(DATA_mgconst, 0x20), DATANUM(DATA_mgconst, 0x21),
    DATANUM(DATA_mgconst, 0x22), DATANUM(DATA_mgconst, 0x23),
    DATANUM(DATA_mgconst, 0x24), DATANUM(DATA_mgconst, 0x26),
    DATANUM(DATA_mgconst, 0x27), DATANUM(DATA_mgconst, 0x28),
    DATANUM(DATA_mgconst, 0x29), DATANUM(DATA_mgconst, 0x2A),
    DATANUM(DATA_mgconst, 0x2B), DATANUM(DATA_mgconst, 0x2C),
    DATANUM(DATA_mgconst, 0x2D)
};

/* data_E4 / data_F0 / data_FC -- the one global light. */
static HuVecF LightPos = { 0.0f, 10000.0f, 10000.0f };
static HuVecF LightAim = { 0.0f, 0.0f, 0.0f };
static u8 LightColor[4] = { 255, 255, 255, 255 };

/* data_1C0 -- the one camera view the whole minigame plays from. */
static OMCAMERAVIEW CameraView = {
    { 0.0f, 221.5f, -500.0f },
    { 4.4f, 0.0f, 0.0f },
    526.0f
};

/* data_1A4 -- the seven motions every player model gets. */
static u32 PlayerMotData[7] = {
    CHARMOT_HSF_c000m1_300, CHARMOT_HSF_c000m1_306, CHARMOT_HSF_c000m1_360,
    CHARMOT_HSF_c000m1_301, CHARMOT_HSF_c000m1_302, CHARMOT_HSF_c000m1_442,
    CHARMOT_HSF_c000m1_324
};

/* data_214 -- where the four players start, one corner each. */
static HuVecF PlayerStartPos[4] = {
    { -75.0f, 0.0f, -75.0f },
    { 75.0f, 0.0f, -75.0f },
    { -75.0f, 0.0f, 75.0f },
    { 75.0f, 0.0f, 75.0f }
};

/* data_34 -- the host's fifteen joint motions. */
static u32 HostMotData[15] = {
    DATANUM(DATA_m571, 0x08), DATANUM(DATA_m571, 0x09), DATANUM(DATA_m571, 0x0A),
    DATANUM(DATA_m571, 0x0D), DATANUM(DATA_m571, 0x0E), DATANUM(DATA_m571, 0x0F),
    DATANUM(DATA_m571, 0x10), DATANUM(DATA_m571, 0x11), DATANUM(DATA_m571, 0x12),
    DATANUM(DATA_m571, 0x13), DATANUM(DATA_m571, 0x14), DATANUM(DATA_m571, 0x15),
    DATANUM(DATA_m571, 0x16), DATANUM(DATA_m571, 0x0B), DATANUM(DATA_m571, 0x0C)
};

/* data_70 -- where the host stands for the results. */
static HuVecF HostResultPos = { 0.0f, 100.0f, -750.0f };

/* data_9C / data_B4 -- where the host stands, and the way he faces, for each
 * of the two sides in states 25-28. */
static HuVecF HostSidePos[2] = {
    { -880.0f, 0.0f, -140.0f },
    { 880.0f, 0.0f, -140.0f }
};

static HuVecF HostSideRot[2] = {
    { 0.0f, 90.0f, 0.0f },
    { 0.0f, 270.0f, 0.0f }
};

/* data_CC -- the two side props, mirrored left and right. */
static HuVecF SidePos[2] = {
    { -700.0f, 0.0f, -140.0f },
    {  700.0f, 0.0f, -140.0f }
};

/* data_7C -- one screen position per player. */
static float Unk7CTbl[4][2] = {
    {  71.0f, 60.0f },
    { 191.0f, 60.0f },
    { 385.0f, 60.0f },
    { 505.0f, 60.0f }
};

/* data_1DC and data_1F8 -- the two views the camera moves to. */
static OMCAMERAVIEW CameraView2 = {
    { 0.0f, 183.4f, 86.1f },
    { -52.3f, 0.0f, 0.0f },
    2223.5f
};

static OMCAMERAVIEW CameraView3 = {
    { 0.0f, 221.5f, -500.0f },
    { 4.4f, 0.0f, 0.0f },
    1200.0f
};

/* data_244 -- where the four line up for the results. */
static HuVecF LineUpPos[4] = {
    { -240.0f,   0.0f, -450.0f },
    {  -80.36f,  0.0f, -450.0f },
    {   80.36f,  0.0f, -450.0f },
    {  240.66f,  0.0f, -450.0f }
};

/* data_280 / data_28C / data_298 -- where the shadow camera looks from. */
static HuVecF ShadowPos = { -100.0f, 8000.0f, 0.0f };
static HuVecF ShadowUp = { 0.0f, 1.0f, 0.0f };
static HuVecF ShadowAim = { 0.0f, 0.0f, 0.0f };

/*
 * data_2CC -- the floor, a nine by nine grid of 120-unit cells centred on
 * the origin. Index is row-major, z outermost.
 */
static HuVecF ObjPosTbl[81] = {
    { -480.0f, 0.0f, -480.0f }, { -360.0f, 0.0f, -480.0f }, { -240.0f, 0.0f, -480.0f },
    { -120.0f, 0.0f, -480.0f }, { 0.0f, 0.0f, -480.0f }, { 120.0f, 0.0f, -480.0f },
    { 240.0f, 0.0f, -480.0f }, { 360.0f, 0.0f, -480.0f }, { 480.0f, 0.0f, -480.0f },
    { -480.0f, 0.0f, -360.0f }, { -360.0f, 0.0f, -360.0f }, { -240.0f, 0.0f, -360.0f },
    { -120.0f, 0.0f, -360.0f }, { 0.0f, 0.0f, -360.0f }, { 120.0f, 0.0f, -360.0f },
    { 240.0f, 0.0f, -360.0f }, { 360.0f, 0.0f, -360.0f }, { 480.0f, 0.0f, -360.0f },
    { -480.0f, 0.0f, -240.0f }, { -360.0f, 0.0f, -240.0f }, { -240.0f, 0.0f, -240.0f },
    { -120.0f, 0.0f, -240.0f }, { 0.0f, 0.0f, -240.0f }, { 120.0f, 0.0f, -240.0f },
    { 240.0f, 0.0f, -240.0f }, { 360.0f, 0.0f, -240.0f }, { 480.0f, 0.0f, -240.0f },
    { -480.0f, 0.0f, -120.0f }, { -360.0f, 0.0f, -120.0f }, { -240.0f, 0.0f, -120.0f },
    { -120.0f, 0.0f, -120.0f }, { 0.0f, 0.0f, -120.0f }, { 120.0f, 0.0f, -120.0f },
    { 240.0f, 0.0f, -120.0f }, { 360.0f, 0.0f, -120.0f }, { 480.0f, 0.0f, -120.0f },
    { -480.0f, 0.0f, 0.0f }, { -360.0f, 0.0f, 0.0f }, { -240.0f, 0.0f, 0.0f },
    { -120.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 120.0f, 0.0f, 0.0f },
    { 240.0f, 0.0f, 0.0f }, { 360.0f, 0.0f, 0.0f }, { 480.0f, 0.0f, 0.0f },
    { -480.0f, 0.0f, 120.0f }, { -360.0f, 0.0f, 120.0f }, { -240.0f, 0.0f, 120.0f },
    { -120.0f, 0.0f, 120.0f }, { 0.0f, 0.0f, 120.0f }, { 120.0f, 0.0f, 120.0f },
    { 240.0f, 0.0f, 120.0f }, { 360.0f, 0.0f, 120.0f }, { 480.0f, 0.0f, 120.0f },
    { -480.0f, 0.0f, 240.0f }, { -360.0f, 0.0f, 240.0f }, { -240.0f, 0.0f, 240.0f },
    { -120.0f, 0.0f, 240.0f }, { 0.0f, 0.0f, 240.0f }, { 120.0f, 0.0f, 240.0f },
    { 240.0f, 0.0f, 240.0f }, { 360.0f, 0.0f, 240.0f }, { 480.0f, 0.0f, 240.0f },
    { -480.0f, 0.0f, 360.0f }, { -360.0f, 0.0f, 360.0f }, { -240.0f, 0.0f, 360.0f },
    { -120.0f, 0.0f, 360.0f }, { 0.0f, 0.0f, 360.0f }, { 120.0f, 0.0f, 360.0f },
    { 240.0f, 0.0f, 360.0f }, { 360.0f, 0.0f, 360.0f }, { 480.0f, 0.0f, 360.0f },
    { -480.0f, 0.0f, 480.0f }, { -360.0f, 0.0f, 480.0f }, { -240.0f, 0.0f, 480.0f },
    { -120.0f, 0.0f, 480.0f }, { 0.0f, 0.0f, 480.0f }, { 120.0f, 0.0f, 480.0f },
    { 240.0f, 0.0f, 480.0f }, { 360.0f, 0.0f, 480.0f }, { 480.0f, 0.0f, 480.0f },
};

/*
 * data_698 -- three layouts, one picked at random in M573Unk25B4. Each cell
 * is what stands on it: 0 nothing, and -1, 1 or 5 the three kinds.
 */
static int PatternTbl[3][81] = {
    {
         1,  1,  0, -1,  1, -1, -1,  5,  1,
        -1, -1,  1, -1,  0,  1,  1,  0, -1,
         1,  0,  0,  1,  1, -1, -1,  0,  1,
        -1,  1, -1,  0,  0,  0, -1,  1, -1,
         5,  1,  0,  0,  0,  0, -1,  1,  5,
        -1, -1,  1,  0,  0,  0,  1,  0, -1,
        -1,  1,  1,  0, -1,  0,  1,  0,  1,
         5,  0, -1,  1,  1,  1, -1,  1, -1,
        -1,  1,  1, -1,  1, -1,  1,  0,  1
    },
    {
        -1,  5, -1, -1,  1,  1, -1,  5, -1,
         1,  0,  1,  0,  1,  0, -1,  0,  1,
        -1,  1, -1,  1, -1,  1,  1,  0,  0,
        -1,  0,  1,  0,  0,  0,  1, -1, -1,
         1,  1, -1,  0,  0,  0,  0,  1,  1,
         0, -1,  1,  0,  0,  0, -1,  0,  1,
         1,  1,  0,  1,  0, -1, -1,  1, -1,
        -1,  1, -1,  1,  0,  1,  5,  1,  1,
        -1,  1, -1,  5, -1,  1, -1,  1, -1
    },
    {
        -1, -1,  1,  1,  1, -1, -1,  1,  1,
         5,  0,  1, -1,  0,  1,  1,  0, -1,
         0, -1, -1,  1,  0,  1, -1,  1,  5,
         1,  1,  0,  0,  0,  0,  1, -1,  1,
        -1,  0, -1,  0,  0,  0,  0,  1,  0,
        -1,  1,  1,  0,  0,  0, -1,  1, -1,
         1,  1, -1, -1,  1,  1,  0,  0,  5,
        -1,  0,  1,  1,  1, -1, -1,  1,  1,
        -1,  5, -1, -1,  0,  1,  0,  1, -1
    }
};

/* data_2A4 -- no START, FADEOUT or CLOSE hook. */
static MGSEQ_PARAM SeqParam = {
    10,
    MGSEQ_TIMER_TOP,
    M573InitHook,
    M573FadeInHook,
    NULL,
    M573MainHook,
    M573FinishHook,
    M573PreWinnerHook,
    M573WinnerHook,
    NULL,
    NULL
};

typedef struct M573Slot_s {
    /* 0x00 */ u32 dataNum;
    /* 0x04 */ HU3DMODELID modelId;
    /* 0x06 */ s16 pad06;
} M573_SLOT;                       /* 0x08 */

/* --- .bss --- */

static int Unk0;                    /* bss_0 */
static HU3DMODELID Model4;          /* bss_4 */
static HU3DMODELID Model6;          /* bss_6 */
static HU3DMODELID Model8;          /* bss_8 */
static int UnkC;                    /* bss_C */
static HU3DMODELID Models10[2];     /* bss_10 */
static OMOBJ *OutViewObj;           /* bss_14 */
static OMOBJ *Objs[81];             /* bss_18 -- group 1, one per thrown thing */
static OMOBJ **PlayerObjs;          /* bss_15C */
static HU3DLIGHTID LightId;         /* bss_160 */
static int Unk164;                  /* bss_164 */
static int Unk168;                  /* bss_168 */
static HU3DMODELID Model16C;        /* bss_16C */
static OMOBJ *Unk170[20];           /* bss_170 */
static MGSCORE *Scores[4];          /* bss_1C0 */
static s16 CountEsp[4];             /* bss_1D0 */
static s16 ItemEsp[4];              /* bss_1D8 */
static s16 FaceEsp[4];              /* bss_1E0 */
static HUSPRGRPID ScoreWins[4];     /* bss_1E8 */
static float Unk1F0[4];             /* bss_1F0 */
static int Unk200[4];               /* bss_200 */
static int Unk210[4];               /* bss_210 */
static int Unk220[4];               /* bss_220 */
static int Unk230[4];               /* bss_230 */
static int Unk240;                  /* bss_240 */
static int Unk244[4];               /* bss_244 */
static HU3DMOTID MotIds[16];        /* bss_254 */
static int Unk274;                  /* bss_274 */
static OMOBJ *Unk278;               /* bss_278 */
static OMOBJ **HostObjs;            /* bss_280 */
static M573_SLOT Slots[32];         /* bss_284 */
static int Unk384;
static int Unk388;                  /* bss_388 */
static int SeqNo;                   /* bss_38C */
static int Unk390[2];
static u8 Unk398[0x30];             /* bss_398 */
static u8 Unk3C8[0x30];             /* bss_3C8 */
static u8 Unk3F8[0x30];             /* bss_3F8 */
static u8 Unk428[0x30];             /* bss_428 */
static HuVecF Unk458;               /* bss_458 */
static HuVecF Unk464;               /* bss_464 */
static HuVecF Unk470;               /* bss_470 */
static HuVecF Unk47C;               /* bss_47C */
static OMOBJMAN *ObjMan;            /* bss_488 */
static M573_NODE ListHead;          /* bss_48C */

void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;
    int j;

    OSReport("******* M573 ObjectSetup **********\n");
    ObjMan = omInitObjMan(200, 0x2000);
    omGameSysInit(ObjMan);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSet(&CameraView);
    OutViewObj = omAddObjEx(ObjMan, 0x7FDA, 0, 0, -1, omOutView);
    OutViewObj->work[0] = 2;
    LightId = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(LightId, &LightPos, &LightAim);
    Hu3DGLightStaticSet(LightId, 1);
    Hu3DGLightInfinitytSet(LightId);
    Hu3DGLightColorSet(LightId, LightColor[0], LightColor[1], LightColor[2], LightColor[3]);
    Hu3DShadowCreate(10.0f, 10.0f, 10000.0f);
    Hu3DShadowColSet(16, 16, 16);
    Hu3DShadowPosSet(&ShadowPos, &ShadowUp, &ShadowAim);
    Hu3DShadowTPLvlSet(0.6f);
    omMakeGroupEx(ObjMan, 0, 4);
    PlayerObjs = omGetGroupMemberListEx(ObjMan, 0);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(ObjMan, 100, 1, 7, 0, M573PlayerInit);
        PlayerObjs[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(ObjMan, 2, 1);
    HostObjs = omGetGroupMemberListEx(ObjMan, 2);
    obj = omAddObjEx(ObjMan, 0x67, 0, 0, 2, M573HostInit);
    HostObjs[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, 0xB0, HU_MEMNUM_OVL);
    obj->work[0] = 2;
    UnkC = 0;
    omMakeGroupEx(ObjMan, 1, 0x51);
    Model8 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    Model6 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x04), HU_MEMNUM_OVL, HEAP_MODEL));
    Model4 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x05), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(Model8, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(Model6, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(Model4, HU3D_ATTR_DISPOFF);
    Model16C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(Model16C, HU3D_ATTR_DISPOFF);
    for(j=0; j<20; j++) {
        Unk170[j] = 0;
    }
    Unk164 = -1;
    M573Unk25B4();
    MgSeqCreatePrio(&SeqParam, 1000);
}

/*
 * fn_1_5C8 -- one player: their model, their seven motions, their corner of
 * the floor, and how long a computer player waits before its first dodge.
 */
static void M573PlayerInit(OMOBJ *obj)
{
    M573_PLAYER *player;
    float x;
    float y;
    float z;
    int i;

    player = obj->data;
    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->unk1C = 0;
    player->unk68 = player->unk6C = 0.0f;
    player->unk20 = 0;
    player->unk24 = 0;
    obj->mdlId[0] = CharModelCreate((s16)player->charNo, 2);
    for(i=0; i<7; i++) {
        obj->mtnId[i] = CharMotionCreate((s16)player->charNo, PlayerMotData[i]);
        CharMotionSet((s16)player->charNo, obj->mtnId[i]);
    }
    player->motNo = 0;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], 0x40000001);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[0]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    player->dif = GwPlayerConf[player->playerNo].dif;
    player->mode = 0;
    player->unk8C = 0;
    player->unk84 = 0;
    switch(player->dif) {
    case 0:
        {
            int wait = frandmod(20)+60;
            player->comWait = wait;
        }
        break;
    case 1:
        {
            int wait = frandmod(15)+30;
            player->comWait = wait;
        }
        break;
    case 2:
        {
            int wait = frandmod(15)+10;
            player->comWait = wait;
        }
        break;
    case 3:
        {
            int wait = frandmod(4)+1;
            player->comWait = wait;
        }
        break;
    }
    player->rot.x = player->rot.y = player->rot.z = 0.0f;
    z = PlayerStartPos[player->playerNo].z;
    y = PlayerStartPos[player->playerNo].y;
    x = PlayerStartPos[player->playerNo].x;
    player->pos.x = x;
    player->pos.y = y;
    player->pos.z = z;
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose((s16)player->charNo);
    obj->objFunc = M573PlayerMain;
}

/* fn_1_8840 -- stereo pan for a sound coming from a point in the world. */
static int M573PanGet(HuVecF *pos)
{
    HuVecF scr;
    int pan;

    Hu3D3Dto2D(pos, 1, &scr);
    pan = 32.0f + 64.0f * (scr.x / 576.0f);
    return pan;
}

/* fn_1_88BC -- and its volume, quieter the further up the screen it is. */
static int M573VolGet(HuVecF *pos)
{
    HuVecF scr;
    int vol;

    Hu3D3Dto2D(pos, 1, &scr);
    vol = 96.0f + 31.0f * (scr.y / 480.0f);
    return vol;
}

/*
 * fn_1_8BC -- one player's frame: their stick (or the computer's), then
 * whichever of the three states they are in. Standing on a cell that still
 * has something on it takes it; a cell whose kind is -1 knocks them over
 * instead.
 *
 * Two instructions long, in ten lines, and all of them the same thing: the
 * original passes the pan and volume on with plain mr and sth/lha and no
 * sign-extension anywhere, which needs HuAudFXPlayVolPan and
 * CharModelVoicePanSet to take int-width parameters. This tree's audio.h
 * and charman.h declare them s16, and so do the vendored definitions in
 * src/game, so the widths cannot be corrected from here on this evidence.
 * Same values either way.
 */
static void M573PlayerMain(OMOBJ *obj)
{
    M573_PLAYER *player;
    int no;
    int kind;

    player = obj->data;
    if(GwPlayerConf[player->playerNo].type != 0) {
        M573UnkDAC(obj);
    } else {
        player->unk68 = (s8)HuPadStkX[player->padNo];
        player->unk6C = (s8)HuPadStkY[player->padNo];
    }
    switch(player->unk20) {
    case 0:
        if(MgSeqModeGet() == 5) {
            player->posPrev = player->pos;
            M573Unk12B8(player, obj);
            no = M573Unk2DA0(&player->pos, 50.0f);
            if(no != -1) {
                kind = M573Unk2814(no, player->playerNo);
                if(kind == -1) {
                    M573Unk2260(PlayerObjs[player->playerNo], 5, 8.0f, 0);
                    player->unk20 = 1;
                    omVibrate((s16)player->padNo, 15, 12, 0);
                    HuAudFXPlayVolPan(0x97A, M573VolGet(&player->pos), M573PanGet(&player->pos));
                } else {
                    HuAudFXPlayVolPan(0x96C, M573VolGet(&player->pos), M573PanGet(&player->pos));
                }
            }
        }
        break;
    case 1:
        player->unk68 = player->unk6C = 0.0f;
        if(player->unk24 > 63) {
            player->unk24 = 0;
            player->unk20 = 2;
            CharMotionUpdateSet((s16)player->charNo, CHARMOT_HSF_c000m1_324, 0);
            M573Unk2260(PlayerObjs[player->playerNo], 6, 8.0f, 0);
            Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
        } else {
            player->unk24++;
        }
        break;
    case 2:
        player->unk68 = player->unk6C = 0.0f;
        if(player->unk24 > 38) {
            player->unk24 = 0;
            player->unk20 = 0;
            M573Unk2260(PlayerObjs[player->playerNo], 0, 8.0f, 0x40000001);
        } else {
            player->unk24++;
        }
        break;
    }
    CharModelVoicePanSet((s16)player->charNo, M573PanGet(&player->pos));
    omSetTra(obj, player->pos.x, player->pos.y, player->pos.z);
    omSetRot(obj, player->rot.x, player->rot.y, player->rot.z);
}

/*
 * fn_1_DAC -- a computer player's frame: look for somewhere to stand, run
 * for it, then stand still for as long as its difficulty says.
 */
static void M573UnkDAC(OMOBJ *obj)
{
    M573_PLAYER *player;

    player = obj->data;
    switch(player->mode) {
    case 0:
        if(M573Unk1028(&player->pos, &player->target) != 0) {
            player->mode = 1;
        } else {
            player->mode = 2;
            player->unk68 = player->unk6C = 0.0f;
        }
        break;
    case 1:
        player->unk8C++;
        if(player->unk8C > 120) {
            player->unk8C = 0;
            player->mode = 0;
        } else if(M573UnkEE4(obj) != 0) {
            player->mode = 2;
            player->unk68 = player->unk6C = 0.0f;
        }
        break;
    case 2:
        player->unk68 = player->unk6C = 0.0f;
        player->unk84++;
        if(player->unk84 > player->comWait) {
            player->mode = 0;
            player->unk84 = 0;
        }
        break;
    }
}

/*
 * fn_1_EE4 -- push a computer player's stick towards its target, and say
 * when it has arrived.
 */
static int M573UnkEE4(OMOBJ *obj)
{
    M573_PLAYER *player;
    float lim;
    HuVecF v;
    HuVecF dir;

    lim = 25.001f;
    player = obj->data;
    PSVECSubtract(&player->target, &player->pos, &v);
    v.y = 0.0f;
    if(PSVECSquareMag(&v) < lim) {
        return 1;
    }
    PSVECNormalize(&v, &v);
    dir.x = v.x;
    dir.y = v.z;
    player->unk68 = (s8)(56.0f * dir.x);
    player->unk6C = (s8)(56.0f * -dir.y);
    return 0;
}

/*
 * fn_1_1028 -- the nearest cell in XZ that still has something on it.
 * M573Dist2D is written out inline, with the three copies its return value
 * makes on the way out: this compiler will not inline forward.
 */
static int M573Unk1028(HuVecF *pos, HuVecF *dst)
{
    M573_ITEM *item;
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
    int i;

    bestDist = 1000000.0f;
    for(i=0; i<81; i++) {
        if(Objs[i] != NULL) {
            item = Objs[i]->data;
            if(item->kind != -1) {
                bz = item->pos.z;
                bx = item->pos.x;
                az = pos->z;
                ax = pos->x;
                dx = ax - bx;
                dz = az - bz;
                mag = HuMag2Point2D(dx, dz);
                d1 = sqrtf(mag);
                d2 = d1;
                d = d2;
                if(bestDist > d) {
                    best.x = item->pos.x;
                    best.y = item->pos.y;
                    best.z = item->pos.z;
                    bestDist = d;
                }
            }
        }
    }
    if(1000000.0f != bestDist) {
        dst->x = best.x;
        dst->y = best.y;
        dst->z = best.z;
        return 1;
    }
    return 0;
}

/*
 * fn_1_12B8 -- one player's movement: the stick becomes a velocity capped
 * at ten a frame, they turn four tenths of the way towards it, and they are
 * clamped to the floor twice -- once for themselves and once after the
 * shove that may have moved everybody. M573Unk3EBC written out.
 */
static void M573Unk12B8(M573_PLAYER *player, OMOBJ *obj)
{
    int motNo;
    int unused;
    float mag;
    float d;
    float r;
    float cur;
    float ang;
    float rr;

    if(1.0f == player->unk68) {
        unused = 0;
    }
    player->vel.x = 0.0f;
    player->vel.y = 0.0f;
    player->vel.z = 0.0f;
    player->vel.x = player->unk68 / 4.0f;
    player->vel.z = -player->unk6C / 4.0f;
    motNo = 0;
    mag = HuMag2Point2D(player->vel.x, player->vel.z);
    player->speed = sqrtf(mag);
    if(0.0f < player->speed) {
        if(10.0f <= player->speed) {
            player->vel.x /= player->speed;
            player->vel.z /= player->speed;
            player->speed = 10.0f;
            player->vel.x = 10.0f * player->vel.x;
            player->vel.z = 10.0f * player->vel.z;
        }
        ang = 180.0 * (atan2(player->vel.x, player->vel.z) / M_PI);
        cur = player->rot.y;
        d = fmod(ang - cur, 360.0);
        if(0.0f > d) {
            d += 360.0f;
        }
        if(180.0f < d) {
            d -= 360.0f;
        }
        r = fmod(cur + (d * 0.4f), 360.0);
        if(0.0f > r) {
            r += 360.0f;
        }
        rr = r;
        player->rot.y = rr;
        if(7.0f <= player->speed) {
            motNo = 4;
        } else {
            motNo = 3;
        }
    }
    PSVECAdd(&player->pos, &player->vel, &player->pos);
    M573Unk171C(&player->pos, 50.0f);
    M573Unk22F0(obj);
    M573Unk171C(&player->pos, 50.0f);
    player->posLast.x = player->pos.x;
    player->posLast.y = player->pos.y;
    player->posLast.z = player->pos.z;
    if(player->motNo != motNo) {
        player->motNo = (s16)motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[player->motNo], 0.0f, 8.0f, 0x40000001);
    }
}

/*
 * fn_1_171C -- keep a point inside the square floor, allowing for its own
 * radius, and say whether it had to be pushed back.
 */
static int M573Unk171C(HuVecF *pos, float radius)
{
    float lim;
    int hit;

    hit = 0;
    lim = 575.0f - radius;
    if(lim < pos->x) {
        pos->x = lim;
    }
    if(lim < pos->z) {
        pos->z = lim;
    }
    if(-lim > pos->x) {
        pos->x = -lim;
    }
    if(-lim > pos->z) {
        pos->z = -lim;
    }
    if(lim == ((0.0f > pos->x) ? -pos->x : pos->x)
            || lim == ((0.0f > pos->z) ? -pos->z : pos->z)) {
        hit = 1;
    }
    return hit;
}

/*
 * fn_1_182C -- push one circle out of another in XZ until they only touch.
 * Two exactly coincident points separate along -Z.
 */
static void M573Unk182C(HuVecF *a, HuVecF *b, float ra, float rb)
{
    float dx;
    float dz;
    float dist;

    dx = a->x - b->x;
    dz = a->z - b->z;
    dist = HuMagPoint2D(dx, dz);
    if(ra + rb > dist) {
        if(0.0f == dist) {
            dx = 0.0f;
            dz = -1.0f;
        } else {
            dx /= dist;
            dz /= dist;
        }
        a->x = b->x + (dx * (ra + rb));
        a->z = b->z + (dz * (ra + rb));
    }
}

/*
 * fn_1_1A14 -- MGSEQ_MODE_INIT: the floor and the sky, then the four
 * characters handed to the sprite object, then the music.
 */
static void M573InitHook(s16 mode, s16 frameNo)
{
    int charNo[4];
    M573_PLAYER *player;
    int i;
    int b;
    int c;
    int d;

    Models10[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x00), HU_MEMNUM_OVL, HEAP_MODEL));
    Models10[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x01), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelShadowMapSet(Models10[0]);
    Hu3DModelAttrSet(Models10[1], 0x40000001);
    for(i=0; i<4; i++) {
        player = PlayerObjs[i]->data;
        charNo[i] = player->charNo;
    }
    /*
     * M573Unk793C written out, for the same reason M573Unk8374 is in
     * MGSEQ_MODE_FINISH: the original inlines it from 0x793C, far below,
     * and this compiler will not inline forward. The four locals loaded
     * back to front are the inlined call binding its parameters.
     */
    d = charNo[3];
    c = charNo[2];
    b = charNo[1];
    Unk244[0] = charNo[0];
    Unk244[1] = b;
    Unk244[2] = c;
    Unk244[3] = d;
    Unk240 = 2;
    omAddObjEx(ObjMan, 0x65, 0, 0, -1, M573Unk7364);
    MgSeqModeNext();
    Unk164 = HuAudSStreamPlay(0x3D);
}

/*
 * fn_1_1B78 -- MGSEQ_MODE_FADEIN. Half a second, then Donkey Kong moves;
 * two and a half more, then the camera pulls back to CameraView2.
 */
static void M573FadeInHook(s16 mode, s16 frameNo)
{
    int i;
    M573_HOST *host;

    host = HostObjs[0]->data;
    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    host->unk30 = 1;
    for(i=0; i<150; i++) {
        HuPrcVSleep();
    }
    omCameraViewMoveSimple(&CameraView2, 90);
    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    host->unk38 = 0;
    host->unk28 = 1300.0f;
    host->unk30 = 2;
    MgSeqModeNext();
}

/* fn_1_1C3C -- MGSEQ_MODE_MAIN. */
static void M573MainHook(s16 mode, s16 frameNo)
{
    M573_HOST *host;

    host = HostObjs[0]->data;
    if(MgSeqFrameNoGet() == 0) {
        host->unk30 = 24;
    }
    M573Unk22EC();
    if(UnkC == 0) {
        MgSeqModeNext();
    }
}

/*
 * fn_1_1CA4 -- MGSEQ_MODE_FINISH: stand everyone still, stop the music,
 * and after five seconds move on.
 */
static void M573FinishHook(s16 mode, s16 frameNo)
{
    M573_PLAYER *player;
    int i;
    int j;
    int done;

    if(MgSeqFrameNoGet() == 0) {
        for(i=0; i<4; i++) {
            player = PlayerObjs[i]->data;
            if(player->unk20 == 0) {
                M573Unk2260(PlayerObjs[player->playerNo], 0, 8.0f, 0x40000001);
            }
        }
        HuAudSStreamFadeOut(Unk164, 100);
    }
    if(MgSeqFrameNoGet() > 300) {
        /*
         * M573Unk8374 written out. The original inlines it here -- it is
         * defined at 0x8374, well past this function, and nothing calls it
         * out of line -- and this compiler will not inline forward, so the
         * body is repeated rather than called. The goto is what its two
         * "return 1" arms become once inlined.
         */
        for(j=0; j<20; j++) {
            if(Unk170[j] != NULL) {
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

/*
 * fn_1_1DC4 -- MGSEQ_MODE_PREWIN: wipe to white, line the four up in front
 * of the host, give each of them their score, clear the floor and wipe
 * back in.
 */
static void M573PreWinnerHook(s16 mode, s16 frameNo)
{
    M573_PLAYER *player;
    M573_HOST *host;
    M573_HOST *host2;
    OMOBJ *hostObj;
    int i;
    HuVecF scr;
    int pan;

    host = HostObjs[0]->data;
    if(MgSeqFrameNoGet() == 30) {
        WipeCreate(2, 6, 30);
        WipeColorSet(255, 255, 255);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        omCameraViewSet(&CameraView3);
        for(i=0; i<4; i++) {
            player = PlayerObjs[i]->data;
            player->pos.x = LineUpPos[i].x;
            player->pos.y = LineUpPos[i].y;
            player->pos.z = LineUpPos[i].z;
            player->rot.x = player->rot.y = player->rot.z = 0.0f;
            Hu3DModelAttrReset(PlayerObjs[player->playerNo]->mdlId[0], HU3D_ATTR_DISPOFF);
            M573Unk2260(PlayerObjs[player->playerNo], 0, 0.0f, 0x40000001);
            player->unk1C = Unk230[player->playerNo];
            /*
             * M573PanGet written out. Four lines short of exact: the
             * original passes the value on with two plain mr and no
             * sign-extension, which needs CharModelVoicePanSet's pan
             * parameter to be wider than the s16 this tree's charman.h
             * declares. Same value either way.
             */
            Hu3D3Dto2D(&player->pos, 1, &scr);
            pan = 32.0f + 64.0f * (scr.x / 576.0f);
            CharModelVoicePanSet((s16)player->charNo, pan);
        }
        host->unk30 = 0;
        hostObj = HostObjs[0];
        host2 = hostObj->data;
        Hu3DMotionSpeedSet(host2->modelId, 1.0f);
        if(host2->motNo != 0) {
            host2->motNo = 0;
            Hu3DMotionShiftSet(host2->modelId, MotIds[0], 0.0f, 0.0f, 0x40000001);
        }
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        host->pos.x = HostResultPos.x;
        host->pos.y = HostResultPos.y;
        host->pos.z = HostResultPos.z;
        host->rot.x = host->rot.y = host->rot.z = 0.0f;
        M573Unk28E8();
        WipeCreate(1, 5, 30);
        do {
            HuPrcVSleep();
        } while(WipeCheckEnd() != 0);
        MgSeqModeNext();
    }
}

/*
 * fn_1_20B4 -- MGSEQ_MODE_WINNER: anyone who scored cheers, anyone who did
 * not slumps, and everybody is paid what they scored unless this is
 * practice.
 */
static void M573WinnerHook(s16 mode, s16 frameNo)
{
    M573_PLAYER *player;
    int i;
    M573_HOST *host;
    s32 no;
    s16 coin;

    host = HostObjs[0]->data;
    if(MgSeqFrameNoGet() == 0) {
        host->unk30 = 6;
        host->unk38 = 0;
        for(i=0; i<4; i++) {
            player = PlayerObjs[i]->data;
            if(player->unk1C >= 1) {
                M573Unk2260(PlayerObjs[player->playerNo], 1, 8.0f, 0);
            } else {
                M573Unk2260(PlayerObjs[player->playerNo], 2, 8.0f, 0);
                if(Unk230[0] == 0 && Unk230[1] == 0 && Unk230[2] == 0 && Unk230[3] == 0) {
                    CharFXPlay((s16)player->charNo, 0x200);
                }
            }
            coin = player->unk1C + GWMgCoinBonusGet(player->playerNo);
            no = player->playerNo;
            if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                GwPlayer[no].mgCoinBonus = coin;
            }
        }
    }
}

/* fn_1_2260 -- shift one player onto a motion, if they are not on it. */
static void M573Unk2260(OMOBJ *obj, int motNo, float time, int attr)
{
    M573_PLAYER *player;

    player = obj->data;
    if(player->motNo != motNo) {
        player->motNo = (s16)motNo;
        CharMotionShiftSet((s16)player->charNo, obj->mtnId[player->motNo], 0.0f, time, attr);
    }
}

/* fn_1_22EC -- empty. */
static void M573Unk22EC(void)
{
}

/*
 * fn_1_22F0 -- push two players apart when they end a frame inside each
 * other, weighted by how fast each was moving, and recurse so a shove can
 * carry on down a chain. The second weight uses mySpeed on both sides,
 * where the first uses otherSpeed and mySpeed; that is the original.
 */
static void M573Unk22F0(OMOBJ *obj)
{
    M573_PLAYER *player;
    M573_PLAYER *other;
    int i;
    HuVecF v;
    HuVecF n;
    HuVecF a;
    HuVecF b;
    float dist;
    float w;
    float mySpeed;
    float otherSpeed;

    player = obj->data;
    PSVECSubtract(&player->pos, &player->posPrev, &v);
    mySpeed = PSVECMag(&v);
    if(0.0f == mySpeed) {
        return;
    }
    for(i=0; i<4; i++) {
        if(i == player->playerNo) {
            continue;
        }
        other = PlayerObjs[i]->data;
        a.x = player->pos.x;
        a.y = player->pos.y;
        a.z = player->pos.z;
        a.y = 0.0f;
        b.x = other->pos.x;
        b.y = other->pos.y;
        b.z = other->pos.z;
        b.y = 0.0f;
        PSVECSubtract(&a, &b, &v);
        dist = PSVECMag(&v);
        if(dist >= 99.5f) {
            continue;
        }
        PSVECSubtract(&other->pos, &other->posPrev, &v);
        otherSpeed = PSVECMag(&v);
        PSVECSubtract(&a, &b, &n);
        PSVECNormalize(&n, &n);
        dist = 100.0f - dist;
        w = ((0.6f * otherSpeed) + (0.4f * mySpeed)) / (mySpeed + otherSpeed);
        player->pos.x += w * (dist * n.x);
        player->pos.y += w * (dist * n.y);
        player->pos.z += w * (dist * n.z);
        w = ((0.6f * mySpeed) + (0.4f * mySpeed)) / (mySpeed + otherSpeed);
        other->pos.x += w * (dist * -n.x);
        other->pos.y += w * (dist * -n.y);
        other->pos.z += w * (dist * -n.z);
        M573Unk22F0(PlayerObjs[i]);
    }
}

/*
 * fn_1_25B4 -- pick one of the three layouts at random and stand something
 * on every cell it names.
 */
static void M573Unk25B4(void)
{
    int pattern;
    int i;

    pattern = frandmod(3);
    Unk0 = pattern;
    for(i=0; i<81; i++) {
        if(PatternTbl[pattern][i] != 0) {
            M573Unk2690(ObjPosTbl[i].x, ObjPosTbl[i].y, ObjPosTbl[i].z, PatternTbl[pattern][i], i);
        }
    }
}

/*
 * fn_1_2690 -- stand one thing on one cell of the floor, up to eighty-one
 * of them. Kind 1 leans back thirty degrees and sits a little further out.
 */
static void M573Unk2690(float x, float y, float z, int kind, int no)
{
    OMOBJ *obj;
    M573_ITEM *item;

    if(UnkC <= 80) {
        obj = omAddObjEx(ObjMan, 0x65, 1, 0, 1, M573Unk29CC);
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_ITEM), HU_MEMNUM_OVL);
        obj->work[0] = kind;
        item = obj->data;
        item->pos.x = x;
        item->pos.y = y;
        if(kind == 1) {
            item->rot.x = -30.0f;
            item->pos.z = 30.0f + z;
        } else {
            item->rot.x = 0.0f;
            item->pos.z = z;
        }
        item->rot.y = 0.0f;
        item->rot.z = 0.0f;
        item->kind = kind;
        item->scale.x = item->scale.y = item->scale.z = 1.0f;
        item->unk2C = 0;
        item->unk30 = 0;
        item->no = no;
        if(item->kind != -1) {
            UnkC++;
        }
    }
}

/* fn_1_2814 -- hand one thrown thing to a player, and say what it is. */
static int M573Unk2814(int no, int playerNo)
{
    M573_ITEM *item;

    item = Objs[no]->data;
    item->unk2C = 1;
    item->playerNo = playerNo;
    return item->kind;
}

/* fn_1_2850 -- retire one thrown thing. */
static void M573Unk2850(OMOBJ *obj)
{
    M573_ITEM *item;

    item = obj->data;
    Hu3DModelKill(obj->mdlId[0]);
    if(item->kind != -1) {
        UnkC--;
    }
    Objs[item->no] = NULL;
    omDelObjEx(ObjMan, obj);
}

/* fn_1_28E8 -- retire every thrown thing at once. */
static void M573Unk28E8(void)
{
    int i;
    OMOBJ *obj;
    M573_ITEM *item;

    for(i=0; i<81; i++) {
        if(Objs[i] != NULL) {
            obj = Objs[i];
            item = obj->data;
            Hu3DModelKill(obj->mdlId[0]);
            if(item->kind != -1) {
                UnkC--;
            }
            Objs[item->no] = NULL;
            omDelObjEx(ObjMan, obj);
        }
    }
}

/* fn_1_29CC -- one thrown thing: which of the three models it is, and
 * where it stands. */
static void M573Unk29CC(OMOBJ *obj)
{
    M573_ITEM *item;

    item = obj->data;
    if(obj->work[0] == 1) {
        obj->mdlId[0] = Hu3DModelLink(Model8);
    } else if(obj->work[0] == 5) {
        obj->mdlId[0] = Hu3DModelLink(Model6);
    } else {
        obj->mdlId[0] = Hu3DModelLink(Model4);
    }
    Hu3DModelShadowSet(obj->mdlId[0]);
    omSetTra(obj, item->pos.x, item->pos.y, item->pos.z);
    omSetRot(obj, item->rot.x, item->rot.y, item->rot.z);
    omSetSca(obj, item->scale.x, item->scale.y, item->scale.z);
    Objs[item->no] = obj;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = M573Unk2AE4;
}

/*
 * fn_1_2AE4 -- one thrown thing's frame. Kind -1 blinks for half a second
 * and vanishes; anything else vanishes at once and leaves a spawner behind.
 * M573Unk2850 and M573Unk82C0 are both written out, twice each, because
 * both are defined below this and this compiler will not inline forward.
 */
static void M573Unk2AE4(OMOBJ *obj)
{
    M573_ITEM *item;
    M573_EFF *eff1;
    M573_EFF *eff2;
    M573_ITEM *it1;
    M573_ITEM *it2;
    OMOBJ *o1;
    OMOBJ *o2;
    int a1;
    int a2;

    item = obj->data;
    switch(item->unk2C) {
    case 0:
        break;
    case 1:
        if(item->kind == -1) {
            if(item->unk30 > 30) {
                it1 = obj->data;
                Hu3DModelKill(obj->mdlId[0]);
                if(it1->kind != -1) {
                    UnkC--;
                }
                Objs[it1->no] = NULL;
                omDelObjEx(ObjMan, obj);
                return;
            }
            item->unk30++;
            if(item->unk30 & 1) {
                Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            } else {
                Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            }
        } else {
            it2 = obj->data;
            Hu3DModelKill(obj->mdlId[0]);
            if(it2->kind != -1) {
                UnkC--;
            }
            Objs[it2->no] = NULL;
            omDelObjEx(ObjMan, obj);
            if(item->kind == 1) {
                a1 = item->playerNo;
                o1 = omAddObjEx(ObjMan, 0x66, 0, 0, -1, M573Unk8114);
                o1->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_EFF), HU_MEMNUM_OVL);
                eff1 = o1->data;
                eff1->pos.x = item->pos.x;
                eff1->pos.y = item->pos.y;
                eff1->pos.z = item->pos.z;
                eff1->unk08 = a1;
                eff1->unk00 = 1;
                eff1->unk04 = 0;
            } else if(item->kind == 5) {
                a2 = item->playerNo;
                o2 = omAddObjEx(ObjMan, 0x66, 0, 0, -1, M573Unk8114);
                o2->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_EFF), HU_MEMNUM_OVL);
                eff2 = o2->data;
                eff2->pos.x = item->pos.x;
                eff2->pos.y = item->pos.y;
                eff2->pos.z = item->pos.z;
                eff2->unk08 = a2;
                eff2->unk00 = 5;
                eff2->unk04 = 0;
            }
        }
        break;
    }
    omSetTra(obj, item->pos.x, item->pos.y, item->pos.z);
    omSetRot(obj, item->rot.x, item->rot.y, item->rot.z);
    omSetSca(obj, item->scale.x, item->scale.y, item->scale.z);
}

/*
 * fn_1_2DA0 -- which cell a point is standing on, or -1. M573HitCheck is
 * written out here for the third time, for the same forward-inline reason.
 */
static int M573Unk2DA0(HuVecF *pos, float radius)
{
    M573_ITEM *item;
    HuVecF cell;
    HuVecF p;
    float r;
    int hit;
    int i;

    for(i=0; i<81; i++) {
        if(Objs[i] != NULL) {
            item = Objs[i]->data;
            if(item->unk2C == 0) {
                cell.x = ObjPosTbl[i].x;
                cell.y = ObjPosTbl[i].y;
                cell.z = ObjPosTbl[i].z;
                p.x = pos->x;
                p.y = pos->y;
                p.z = pos->z;
                if(item->kind == 1) {
                    r = 25.0f;
                } else if(item->kind == 5) {
                    r = 40.0f;
                } else {
                    r = 40.0f;
                }
                if(((p.x - cell.x) * (p.x - cell.x)) + ((p.z - cell.z) * (p.z - cell.z)) < ((r + radius) * (r + radius))) {
                    hit = 1;
                } else {
                    hit = 0;
                }
                if(hit != 0) {
                    return i;
                }
            }
        }
    }
    return -1;
}

/* fn_1_2F40 -- 240 instructions, asm 3280-3522. */
static void M573Unk2F40(void)
{
}

/* fn_1_3300 -- 9. */
static void M573Unk3300(void)
{
    ListHead.prev = NULL;
    ListHead.next = NULL;
}

/* fn_1_3324 -- push one node on the front of the list. */
static void M573Unk3324(u16 a, s16 b)
{
    M573_NODE *node;
    M573_NODE *head;
    M573_NODE *next;

    node = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_NODE), HU_MEMNUM_OVL);
    node->unk00 = a;
    node->unk02 = b;
    head = &ListHead;
    next = head->next;
    head->next = node;
    if(NULL != next) {
        next->prev = node;
    }
    node->prev = head;
    node->next = next;
}

/* fn_1_33AC -- find one node by key, unlink it, free it, and hand back
 * what it carried. -1 if there is no such node. */
static s16 M573Unk33AC(s16 key)
{
    M573_NODE *node;
    M573_NODE *next;
    M573_NODE *prev;
    s16 val;

    for(node = ListHead.next; NULL != node; node = node->next) {
        if(key == node->unk00) {
            val = node->unk02;
            prev = node->prev;
            next = node->next;
            prev->next = next;
            if(NULL != next) {
                next->prev = prev;
            }
            HuMemDirectFree(node);
            return val;
        }
    }
    return -1;
}

/* fn_1_3450 -- clear the thirty-two slots. */
static void M573Unk3450(void)
{
    int i;

    for(i=0; i<32; i++) {
        Slots[i].dataNum = 0;
        Slots[i].modelId = -1;
    }
}

/*
 * fn_1_34A8 -- a thirty-two entry model cache: link an existing one, else
 * load into the first free slot, else load one nobody will ever free.
 */
static HU3DMODELID M573Unk34A8(u32 dataNum)
{
    int i;

    for(i=0; i<32; i++) {
        if(dataNum == Slots[i].dataNum) {
            return Hu3DModelLink(Slots[i].modelId);
        }
    }
    for(i=0; i<32; i++) {
        if(Slots[i].dataNum == 0) {
            Slots[i].dataNum = dataNum;
            Slots[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
            return Slots[i].modelId;
        }
    }
    return Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/*
 * fn_1_35BC -- ease one point towards another, t clamped at 1 and shaped
 * by sin squared so it starts and stops smoothly.
 */
static void M573Unk35BC(float t, HuVecF *from, HuVecF *to, HuVecF *dst)
{
    float s;

    if(1.0f < t) {
        t = 1.0f;
    }
    s = sin((M_PI * (90.0f * t)) / 180.0) * sin((M_PI * (90.0f * t)) / 180.0);
    dst->x = from->x + (s * (to->x - from->x));
    dst->y = from->y + (s * (to->y - from->y));
    dst->z = from->z + (s * (to->z - from->z));
}

/* fn_1_3718 -- point the camera, and remember where it is looking. */
static void M573Unk3718(HuVecF *pos, HuVecF *up, HuVecF *aim)
{
    Hu3DCameraPosSetV(1, pos, up, aim);
    Unk47C = *pos;
    Unk464 = *aim;
}

/* fn_1_37A4 -- 205 instructions, asm 3866-4076. */
static void M573Unk37A4(void)
{
}

/* fn_1_3AD8 -- 249 instructions, asm 4079-4335. */
static void M573Unk3AD8(void)
{
}

/* fn_1_3EBC -- step an angle t of the way from one to another, the short
 * way round, and hand back the result in 0..360. */
static float M573Unk3EBC(float from, float to, float t)
{
    float d;
    float r;

    d = fmod(to - from, 360.0);
    if(0.0f > d) {
        d += 360.0f;
    }
    if(180.0f < d) {
        d -= 360.0f;
    }
    r = fmod(from + (d * t), 360.0);
    if(0.0f > r) {
        r += 360.0f;
    }
    return r;
}

/* fn_1_3FC0 -- stop the sequence, fading over `fade` ms or a second. */
static void M573Unk3FC0(int fade)
{
    if(SeqNo >= 0) {
        if(fade < 0) {
            fade = 1000;
        }
        HuAudSeqFadeOut(SeqNo, fade);
    }
    SeqNo = -1;
}

/* fn_1_402C -- where one named hook of a model is, in world space. */
static void M573Unk402C(HU3DMODELID modelId, char *objName, HuVecF *dst)
{
    Mtx mtx;

    Hu3DModelObjMtxGet(modelId, objName, mtx);
    dst->x = mtx[0][3];
    dst->y = mtx[1][3];
    dst->z = mtx[2][3];
}

/* fn_1_4084 -- a random int in [min, max). fn_1_8804 is a second copy. */
static int M573RandRange(int min, int max)
{
    return min + frandmod(max - min);
}

/* fn_1_40C0 -- do two circles overlap, in XZ only. fn_1_8634 is a copy. */
static int M573HitCheck(HuVecF *a, HuVecF *b, float ra, float rb)
{
    if(((b->x - a->x) * (b->x - a->x)) + ((b->z - a->z) * (b->z - a->z)) < ((ra + rb) * (ra + rb))) {
        return 1;
    }
    return 0;
}

/* fn_1_4120 -- where a point sits across the screen, mapped onto min..max. */
static int M573ScreenXLerp(HuVecF *pos, int min, int max)
{
    HuVecF scr;
    int val;

    Hu3D3Dto2D(pos, 1, &scr);
    val = min + (scr.x / 576.0f) * (max - min);
    return val;
}

/* fn_1_41E4 -- and down it. */
static int M573ScreenYLerp(HuVecF *pos, int min, int max)
{
    HuVecF scr;
    int val;

    Hu3D3Dto2D(pos, 1, &scr);
    val = min + (scr.y / 480.0f) * (max - min);
    return val;
}

/* fn_1_42A8 -- the host's motions, with the sounds that go with them. */
static void M573Unk42A8(OMOBJ *obj, int motNo, float time, int attr)
{
    M573_HOST *host;

    host = obj->data;
    if(motNo == 8) {
        Hu3DMotionSpeedSet(host->modelId, 2.0f);
    } else {
        Hu3DMotionSpeedSet(host->modelId, 1.0f);
    }
    if(host->motNo != motNo) {
        if(motNo == 2 || motNo == 13) {
            HuAudFXPlay(0x2DB);
        } else if(motNo == 14) {
            HuAudFXPlay(0x2DD);
        }
        host->motNo = motNo;
        Hu3DMotionShiftSet(host->modelId, MotIds[motNo], 0.0f, time, attr);
        if(motNo == 14) {
            HuAudJinglePlay(0x7A);
        }
        if(motNo == 13) {
            HuAudJinglePlay(0x79);
        }
    }
}

/* fn_1_43B0 -- 31. */
static void M573Unk43B0(OMOBJ *obj, int motNo, float time, int attr)
{
    M573_HOST *host;

    host = obj->data;
    host->motNo = motNo;
    Hu3DMotionShiftSet(host->modelId, MotIds[motNo], 0.0f, time, attr);
}

/* fn_1_442C -- 24. */
static void M573Unk442C(OMOBJ *obj, int motNo)
{
    M573_HOST *host;

    host = obj->data;
    host->motNo = motNo;
    Hu3DMotionSet(host->modelId, MotIds[motNo]);
}

/* fn_1_448C -- which hand the host holds the thing in, by unk7C mod 3. */
static void M573Unk448C(OMOBJ *obj)
{
    M573_HOST *host;

    host = obj->data;
    if(host->unk7C % 3 == 0) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
        Hu3DModelHookSet(host->modelId, "a-itemhook-r", host->unk56);
        Hu3DModelAttrReset(host->unk56, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    } else if(host->unk7C % 3 == 1) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-r");
        Hu3DModelHookSet(host->modelId, "a-itemhook-l", host->unk58);
        Hu3DModelAttrReset(host->unk58, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, 0x40000002);
        Hu3DMotionTimeSet(host->unk58, 0.0f);
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
    } else if(host->unk7C % 3 == 2) {
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-r");
        Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    }
}

/* fn_1_4614 -- and which of the two hooks on the other model it hangs from. */
static void M573Unk4614(OMOBJ *obj)
{
    M573_HOST *host;

    host = obj->data;
    if(host->unk7C % 3 == 0) {
        host->rot.y = 90.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook1");
        Hu3DModelHookSet(host->unk54, "itemhook2", host->modelId);
        host->unk74 = 180.0f;
    } else if(host->unk7C % 3 == 1) {
        host->rot.y = 270.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook2");
        Hu3DModelHookSet(host->unk54, "itemhook1", host->modelId);
        host->unk74 = 0.0f;
    } else if(host->unk7C % 3 == 2) {
        host->rot.y = 90.0f;
        Hu3DModelHookObjReset(host->unk54, "itemhook1");
        Hu3DModelHookSet(host->unk54, "itemhook2", host->modelId);
        host->unk74 = 180.0f;
    }
}

/*
 * fn_1_4794 -- Donkey Kong's whole state machine, a 29-way switch on
 * host->unk30 driven by the jumptable at data_130. States 0 and 23 fall
 * straight to the tail.
 */
static void M573Unk4794(OMOBJ *obj)
{
    M573_HOST *host;

    host = obj->data;
    switch(host->unk30) {
    case 1:
        M573Unk42A8(obj, 2, 8.0f, 0);
        break;

    case 2:
        if(host->unk38 == 0) {
            M573Unk42A8(obj, 3, 8.0f, 0);
            HuAudFXPlay(0x969);
        } else if(host->unk38 > 5) {
            if(host->unk38 > 30) {
                host->unk30 = 0;
                M573Unk42A8(obj, 0, 8.0f, 0x40000001);
                Hu3DModelAttrSet(host->modelId, HU3D_ATTR_DISPOFF);
            } else {
                host->pos.y = host->unk40 + 300.0 * sin((M_PI * host->unk3C) / 180.0);
                host->unk3C += 3.6f;
            }
        }
        host->unk38++;
        break;

    case 3:
        host->rot.y = 90.0f;
        host->pos.x = host->pos.y = host->pos.z = 0.0f;
        host->unk7C = 0;
        M573Unk4614(obj);
        M573Unk448C(obj);
        M573Unk42A8(obj, host->unk7C % 3 + 5, 0.0f, 0x40000002);
        Hu3DMotionSpeedSet(host->modelId, 0.0f);
        host->unk68 = -60.0f;
        host->unk64 = 0.0f;
        host->unk6C = -90.0f;
        host->unk70 = 0.0f;
        host->unk74 = 180.0f;
        Hu3DModelRotSet(host->unk54, host->unk70, host->unk74, host->unk64 + host->unk68);
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(host->unk54, HU3D_ATTR_DISPOFF);
        host->unk30 = 4;
        break;

    case 4:
        host->unk68 = (90.0 * sin((M_PI * host->unk6C) / 180.0)) / 1.5;
        host->unk6C += 1.0f;
        host->unk60++;
        Hu3DModelRotSet(host->unk54, host->unk70, host->unk74, host->unk64 + host->unk68);
        if(host->unk60 > 180) {
            host->unk30 = 5;
            host->unk38 = 0;
        } else {
            if(host->unk60 == 30) {
                Hu3DModelAttrReset(host->modelId, 0x40000002);
                Hu3DMotionSpeedSet(host->modelId, 1.0f);
                if(host->unk7C % 3 == 1) {
                    Hu3DModelAttrReset(host->unk58, 0x40000002);
                    Hu3DModelAttrSet(host->unk58, 0);
                }
            }
            if(host->unk7C == 1 && host->unk60 == 102) {
                HuAudFXPlay(0x96A);
            }
        }
        break;

    case 5:
        if(host->unk38 > 30) {
            host->unk30 = 4;
            host->unk38 = 0;
            host->unk60 = 0;
            host->unk7C++;
            M573Unk4614(obj);
            M573Unk448C(obj);
            M573Unk42A8(obj, host->unk7C % 3 + 5, 0.0f, 0x40000002);
            Hu3DMotionSpeedSet(host->modelId, 0.0f);
            if(host->unk7C >= 3) {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
        }
        break;

    case 6:
        if(host->unk38 == 0) {
            if(M573Unk6FE4() == 0) {
                M573Unk42A8(obj, 14, 8.0f, 0);
            } else {
                M573Unk42A8(obj, 13, 8.0f, 0);
            }
        }
        break;

    case 7:
        host->from.x = host->pos.x;
        host->from.y = host->pos.y;
        host->from.z = host->pos.z;
        host->step.x = (host->dest.x - host->from.x) / host->unk44;
        host->step.y = (host->dest.y - host->from.y) / host->unk44;
        host->step.z = (host->dest.z - host->from.z) / host->unk44;
        host->rot.y = 180.0 * (atan2(host->dest.x - host->pos.x, host->dest.z - host->pos.z) / M_PI);
        host->unk30 = 8;
        M573Unk42A8(obj, 1, 8.0f, 0x40000001);
        break;

    case 8:
        if(host->unk38 > host->unk44) {
            if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
            host->pos.x += host->step.x;
            host->pos.y += host->step.y;
            host->pos.z += host->step.z;
        }
        break;

    case 9:
        host->unk3C = 0.0f;
        host->unk40 = host->pos.y;
        host->unk30 = 10;
        break;

    case 10:
        if(host->unk38 > host->unk48) {
            if(host->unk4C > 0) {
                host->unk30 = 11;
                host->unk38 = 0;
            } else if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
            M573Unk42A8(obj, 0, 8.0f, 0x40000001);
        } else {
            M573Unk42A8(obj, 3, 8.0f, 0);
            host->pos.y = host->unk40 + 100.0 * sin((M_PI * host->unk3C) / 180.0);
            host->pos.x = host->pos.x + (host->unk50 * sin((M_PI * host->rot.y) / 180.0)) / host->unk48;
            host->pos.z = host->pos.z + (host->unk50 * cos((M_PI * host->rot.y) / 180.0)) / host->unk48;
            host->unk38++;
            host->unk3C += 180.0f / host->unk48;
        }
        break;

    case 11:
        if(host->unk38 > host->unk4C) {
            if(host->unk34 != -1) {
                host->unk30 = host->unk34;
                host->unk34 = -1;
                host->unk38 = 0;
            } else {
                host->unk30 = 0;
            }
        } else {
            host->unk38++;
            host->pos.y = host->unk40 + 100.0 * sin((M_PI * (host->unk3C + host->unk38)) / 180.0);
        }
        break;

    case 12:
        M573Unk42A8(obj, 1, 8.0f, 0x40000001);
        if(host->unk38 > 30) {
            host->unk30 = 7;
            host->dest.x = 180.0f;
            host->dest.y = host->pos.y;
            host->dest.z = -800.0f;
            host->unk44 = 30;
            host->unk34 = 13;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->rot.y += 3.6666667f;
        }
        break;

    case 13:
        host->unk30 = 9;
        host->unk34 = 15;
        host->unk48 = 40;
        host->unk4C = 0;
        host->unk50 = 200.0f;
        host->unk38 = 0;
        break;

    case 14:
        host->unk30 = 7;
        host->dest.x = 410.0f;
        host->dest.y = 0.0f;
        host->dest.z = -880.0f;
        host->unk44 = 30;
        host->unk34 = 15;
        host->unk38 = 0;
        break;

    case 15:
        M573Unk42A8(obj, 8, 8.0f, 0x40000001);
        if(host->unk38 > 180) {
            host->rot.x = 0.0f;
            host->unk30 = 9;
            host->unk34 = 16;
            host->unk48 = 45;
            host->unk4C = 15;
            host->unk50 = 100.0f;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->pos.x += -0.075f;
            host->pos.y += 4.3333335f;
            host->pos.z += -0.575f;
            host->rot.y = 215.0f;
            host->rot.x = 10.0f;
        }
        break;

    case 16:
        host->unk30 = 7;
        host->dest.x = 220.0f;
        host->dest.y = 860.0f;
        host->dest.z = -1050.0f;
        host->unk44 = 30;
        host->unk34 = 17;
        host->unk38 = 0;
        break;

    case 17:
        M573Unk42A8(obj, 10, 8.0f, 0x40000001);
        if(host->unk38 > 120) {
            host->unk30 = 7;
            host->dest.x = 10.0f;
            host->dest.y = 860.0f;
            host->dest.z = -1070.0f;
            host->unk44 = 30;
            host->unk34 = 18;
            host->unk38 = 0;
        } else {
            host->rot.y = M573Unk3EBC(host->rot.y, 0.0f, 0.5f);
            host->unk38++;
        }
        break;

    case 18:
        M573Unk42A8(obj, 8, 8.0f, 0x40000001);
        if(host->unk38 > 180) {
            host->rot.x = 0.0f;
            host->unk30 = 9;
            host->unk34 = 19;
            host->unk48 = 45;
            host->unk4C = 20;
            host->unk50 = 100.0f;
            host->unk38 = 0;
        } else {
            host->unk38++;
            host->pos.y += 3.2777777f;
            host->rot.y = -161.0f;
            host->rot.x = 10.0f;
        }
        break;

    case 19:
        host->unk30 = 7;
        host->dest.x = -180.0f;
        host->dest.y = 1450.0f;
        host->dest.z = -1150.0f;
        host->unk44 = 30;
        host->unk34 = 21;
        host->unk40 = host->pos.y;
        host->unk3C = 0.0f;
        host->unk38 = 0;
        break;

    case 20:
        M573Unk42A8(obj, 9, 8.0f, 0x40000001);
        if(host->unk38 > 120) {
            host->unk30 = 0;
            host->unk38 = 0;
        } else {
            host->rot.y = M573Unk3EBC(host->rot.y, 0.0f, 0.5f);
            host->unk38++;
        }
        break;

    case 21:
        if(host->unk38 > 60.0f) {
            host->unk30 = 22;
            M573Unk42A8(obj, 4, 8.0f, 0);
            host->unk38 = 0;
        } else {
            M573Unk42A8(obj, 3, 8.0f, 0);
            host->pos.y = host->unk40 + 450.0 * sin((M_PI * host->unk3C) / 180.0);
            host->pos.x = host->pos.x + (200.0 * sin((M_PI * host->rot.y) / 180.0)) / 90.0;
            host->pos.z = host->pos.z + (200.0 * cos((M_PI * host->rot.y) / 180.0)) / 90.0;
            host->unk38++;
            host->unk3C += 2.0f;
        }
        break;

    case 22:
        host->unk38++;
        if(host->unk38 > 30) {
            M573Unk42A8(obj, 9, 8.0f, 0x40000001);
        }
        host->rot.y = M573Unk3EBC(host->rot.y, 0.0f, 0.5f);
        break;

    case 24:
        if(host->unk38 > 40) {
            host->unk38 = 0;
            host->unk30 = 25;
        } else {
            host->unk38++;
        }
        break;

    case 25:
        host->pos.x = HostSidePos[host->unkA4].x;
        host->pos.y = HostSidePos[host->unkA4].y;
        host->pos.z = HostSidePos[host->unkA4].z;
        host->rot.x = HostSideRot[host->unkA4].x;
        host->rot.y = HostSideRot[host->unkA4].y;
        host->rot.z = HostSideRot[host->unkA4].z;
        Hu3DModelAttrReset(host->modelId, HU3D_ATTR_DISPOFF);
        host->unk30 = 26;
        M573Unk43B0(obj, 1, 8.0f, 0x40000001);
        Hu3DModelAttrReset(host->unkA8[host->unkA4], 0x40000002);
        Hu3DMotionTimeSet(host->unkA8[host->unkA4], 0.0f);
        if(host->unkA4 == 0) {
            HuAudFXPlay(0x978);
        } else if(host->unkA4 == 1) {
            HuAudFXPlay(0x979);
        }
        break;

    case 26:
        if(host->unkA4 % 2 == 0) {
            host->pos.x += 2.0f;
        } else {
            host->pos.x -= 2.0f;
        }
        if(host->unk38 > 100) {
            host->unk38 = 0;
            host->unk30 = 28;
            if(host->unkA4 % 2 == 0) {
                M573Unk42A8(obj, 11, 8.0f, 0);
                Hu3DModelHookSet(host->modelId, "a-itemhook-l", host->unkAC);
                Hu3DModelAttrReset(host->unkAC, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(host->unkAC, 0x40000002);
            } else {
                M573Unk42A8(obj, 12, 8.0f, 0);
            }
        } else {
            host->unk38++;
        }
        break;

    case 27:
        if(host->unkA4 % 2 == 0) {
            host->pos.x -= 3.3333333f;
        } else {
            host->pos.x += 3.3333333f;
        }
        if(host->unk38 > 60) {
            host->unk38 = 0;
            host->unk30 = 24;
            host->unkA4++;
            if(host->unkA4 >= 2) {
                host->unkA4 = 0;
                M573Unk43B0(obj, 0, 0.0f, 0);
                host->unk30 = 23;
            }
        } else {
            host->unk38++;
        }
        break;

    case 28:
        if(host->unk38 > 112) {
            host->unk38 = 0;
            host->unk30 = 27;
            M573Unk43B0(obj, 1, 8.0f, 0);
            Hu3DModelHookObjReset(host->modelId, "a-itemhook-l");
            Hu3DModelAttrSet(host->unkAC, HU3D_ATTR_DISPOFF);
        } else {
            host->unk38++;
        }
        if(host->unkA4 == 0 && host->unk38 == 52) {
            HuAudFXPlayPan(0x96A, 0x20);
        }
        break;
    }
    Hu3DModelPosSet(host->modelId, host->pos.x, host->pos.y, host->pos.z);
    Hu3DModelRotSet(host->modelId, host->rot.x, host->rot.y, host->rot.z);
}

/*
 * fn_1_6BDC -- Donkey Kong: his model and its fifteen joint motions, and,
 * depending on which of the three the object was made for, either the thing
 * he holds or the two mirrored side props.
 */
static void M573HostInit(OMOBJ *obj)
{
    M573_HOST *host;
    int i;

    host = obj->data;
    host->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x07), HU_MEMNUM_OVL, HEAP_MODEL));
    if(obj->work[0] == 0) {
        host->unk54 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk54, HU3D_ATTR_DISPOFF);
        Hu3DModelPosSet(host->unk54, 0.0f, 1050.0f, 300.0f);
        Hu3DModelRotSet(host->unk54, 0.0f, 180.0f, 0.0f);
        Hu3DMotionClusterSpeedSet(host->unk54, 0, 1.0f);
        Hu3DModelClusterAttrSet(host->unk54, 0, 0xC0000001);
        host->unk56 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1D), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk56, HU3D_ATTR_DISPOFF);
        host->unk58 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1B), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unk58, 0x40000002);
        Hu3DModelAttrSet(host->unk58, HU3D_ATTR_DISPOFF);
    } else if(obj->work[0] == 1) {
    } else if(obj->work[0] == 2) {
        for(i=0; i<2; i++) {
            host->unkA8[i] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x02), HU_MEMNUM_OVL, HEAP_MODEL));
            Hu3DModelPosSet(host->unkA8[i], SidePos[i].x, SidePos[i].y, SidePos[i].z);
            Hu3DModelAttrSet(host->unkA8[i], 0x40000002);
            if(i == 0) {
                Hu3DModelScaleSet(host->unkA8[i], 1.0f, 1.0f, 1.0f);
            } else {
                Hu3DModelScaleSet(host->unkA8[i], -1.0f, 1.0f, 1.0f);
            }
        }
        host->unkAC = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1C), HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(host->unkAC, 0x40000002);
        Hu3DModelAttrSet(host->unkAC, HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<15; i++) {
        MotIds[i] = Hu3DJointMotion(host->modelId, HuDataSelHeapReadNum(HostMotData[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    host->motNo = 0;
    Hu3DMotionSet(host->modelId, MotIds[0]);
    Hu3DModelAttrSet(host->modelId, 0x40000001);
    Hu3DModelShadowSet(host->modelId);
    host->pos.x = HostResultPos.x;
    host->pos.y = HostResultPos.y;
    host->pos.z = HostResultPos.z;
    host->rot.x = host->rot.y = host->rot.z = 0.0f;
    host->unk30 = 0;
    host->unk34 = -1;
    host->unk38 = 0;
    host->unk28 = 0.0f;
    host->unk60 = 0;
    host->unk7C = 0;
    host->unk40 = host->pos.y;
    host->unk3C = 0.0f;
    host->unkA4 = 0;
    obj->objFunc = M573Unk4794;
}

/* fn_1_6FE4 -- the four scores added up. */
static int M573Unk6FE4(void)
{
    int i;
    int total;

    total = 0;
    for(i=0; i<4; i++) {
        total += Unk230[i];
    }
    return total;
}

/*
 * fn_1_7034 -- the HUD's per-frame half, live from sequence mode 5 on. Shows
 * everything M573Unk7364 created hidden, tracks each player's count, and runs
 * the thirteen-frame pop the counter does when Unk210 is raised: four frames
 * growing by 0.2 to a ceiling of 1.8, then nine shrinking by 0.1 back to 1.0.
 */
static void M573Unk7034(OMOBJ *obj)
{
    int i;

    if(MgSeqModeGet() < 5) {
        return;
    }
    for(i=0; i<4; i++) {
        MgScoreWinDispSet(ScoreWins[i], TRUE);
        espDispOn(FaceEsp[i]);
        espDispOn(ItemEsp[i]);
        espDispOn(CountEsp[i]);
        MgScoreDispOn(Scores[i]);
        if(Unk230[i] > 99) {
            MgScoreValueSet(Scores[i], 99);
        } else {
            MgScoreValueSet(Scores[i], Unk230[i]);
        }
        if(Unk210[i] != 0) {
            if(Unk220[i] > 12) {
                Unk210[i] = 0;
                Unk220[i] = 0;
                Unk1F0[i] = 1.0f;
                MgScoreDigitScaleSet(Scores[i], Unk1F0[i], Unk1F0[i]);
            } else {
                if(Unk220[i] < 4) {
                    if((Unk1F0[i] += 0.2f) >= 1.8f) {
                        Unk1F0[i] = 1.8f;
                    }
                } else {
                    if((Unk1F0[i] -= 0.1f) <= 1.0f) {
                        Unk1F0[i] = 1.0f;
                    }
                }
                Unk220[i]++;
                MgScoreDigitScaleSet(Scores[i], Unk1F0[i], Unk1F0[i]);
            }
        }
    }
}

/*
 * fn_1_7364 -- build the four players' HUD and then hand the object over to
 * M573Unk7034. Each player gets a score window, three sprites -- their face,
 * the thing being counted, and an "x" -- and a two-digit counter, all created
 * hidden and positioned off the window origin in Unk7CTbl.
 */
static void M573Unk7364(OMOBJ *obj)
{
    int i;

    for(i=0; i<4; i++) {
        ScoreWins[i] = MgScoreWinCreate(112, 40);
        MgScoreWinTPLvlSet(ScoreWins[i], 0.85f);
        MgScoreWinPosSet(ScoreWins[i], Unk7CTbl[i][0], Unk7CTbl[i][1]);
        MgScoreWinDispSet(ScoreWins[i], FALSE);

        FaceEsp[i] = espEntry(CharIconTbl[Unk244[i]], 0x63, 0);
        espDispOff(FaceEsp[i]);
        espDrawNoSet(FaceEsp[i], 0);
        espPosSet(FaceEsp[i], Unk7CTbl[i][0] - 38.0f, Unk7CTbl[i][1]);
        espAttrSet(FaceEsp[i], 1);

        if(Unk240 == 0) {
            ItemEsp[i] = espEntry(DATANUM(DATA_m571, 0x1E), 0x63, 0);
        } else if(Unk240 == 1) {
            ItemEsp[i] = espEntry(DATANUM(DATA_m572, 0x14), 0x63, 0);
        } else {
            ItemEsp[i] = espEntry(DATANUM(DATA_m573, 0x06), 0x63, 0);
        }
        espDispOff(ItemEsp[i]);
        espDrawNoSet(ItemEsp[i], 0);
        espPosSet(ItemEsp[i], Unk7CTbl[i][0] - 15.0f, Unk7CTbl[i][1]);
        espAttrSet(ItemEsp[i], 1);

        CountEsp[i] = espEntry(DATANUM(DATA_mgconst, 0x30), 0x63, 0xF);
        espDispOff(CountEsp[i]);
        espDrawNoSet(CountEsp[i], 0);
        espPosSet(CountEsp[i], 4.0f + Unk7CTbl[i][0], Unk7CTbl[i][1]);
        espAttrSet(CountEsp[i], 1);

        Scores[i] = MgScoreCreate(DATANUM(DATA_mgconst, 0x31), -1, TRUE);
        MgScoreValueSet(Scores[i], 0);
        MgScorePosSet(Scores[i], 22.0f + Unk7CTbl[i][0], Unk7CTbl[i][1]);
        MgScoreMaxDigitSet(Scores[i], 2);
        MgScoreDispOff(Scores[i]);
        MgScorePriSet(Scores[i], 0x63);

        Unk210[i] = 0;
        Unk220[i] = 0;
        Unk200[i] = 0;
        Unk1F0[i] = 1.0f;
    }
    obj->objFunc = M573Unk7034;
}

/* fn_1_7898 -- 13. */
static void M573Unk7898(OMOBJ *obj)
{
    if(Unk274 != 0) {
        MgActorExec();
    }
}

/* fn_1_78CC -- 24. */
static void M573Unk78CC(void)
{
    Unk274 = 1;
    Unk278 = omAddObjEx(ObjMan, 100, 0, 0, -1, M573Unk7898);
}

/* fn_1_792C -- 4. */
static void M573Unk792C(int val)
{
    Unk274 = val;
}

/* fn_1_793C -- 42. */
static void M573Unk793C(int a, int b, int c, int d, int e)
{
    Unk244[0] = a;
    Unk244[1] = b;
    Unk244[2] = c;
    Unk244[3] = d;
    Unk240 = e;
    omAddObjEx(ObjMan, 0x65, 0, 0, -1, M573Unk7364);
}

/* fn_1_79E4 -- 6. */
static void M573Unk79E4(int no, int val)
{
    Unk230[no] = val;
}

/*
 * fn_1_79FC -- the model the twenty slots draw, borrowed from whichever of
 * m571, m572 or this overlay's own archive the caller names.
 */
static void M573Unk79FC(int no)
{
    int i;

    if(no == 0) {
        Model16C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m571, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    } else if(no == 1) {
        Model16C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m572, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    } else {
        Model16C = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m573, 0x03), HU_MEMNUM_OVL, HEAP_MODEL));
    }
    Hu3DModelAttrSet(Model16C, HU3D_ATTR_DISPOFF);
    for(i=0; i<20; i++) {
        Unk170[i] = NULL;
    }
}

/* fn_1_7AF0 -- retire one of the twenty and give its slot back. */
static void M573Unk7AF0(OMOBJ *obj)
{
    M573_SLOTOBJ *work;
    int i;

    work = obj->data;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelKill(obj->mdlId[0]);
    Unk168--;
    for(i=0; i<20; i++) {
        if(obj == Unk170[i]) {
            Unk170[i] = NULL;
            break;
        }
    }
    omDelObjEx(ObjMan, obj);
}

/*
 * fn_1_7BC0 -- one of the twenty flying to its owner's corner of the
 * screen over thirty frames, spinning as it goes, then scoring.
 *
 * The three identical pos.y = target.y lines are the original's: it lands
 * only the y, three times over, where x and z are never assigned.
 */
static void M573Unk7BC0(OMOBJ *obj)
{
    M573_SLOTOBJ *work;
    M573_SLOTOBJ *dead;
    int i;

    work = obj->data;
    switch(work->mode) {
    case 0:
        Hu3D2Dto3D(&work->screen, 1, &work->target);
        work->vel.x = (work->target.x - work->pos.x) / (30.0f - (float)work->timer);
        work->vel.y = (work->target.y - work->pos.y) / (30.0f - (float)work->timer);
        work->vel.z = (work->target.z - work->pos.z) / (30.0f - (float)work->timer);
        work->pos.x += work->vel.x;
        work->pos.y += work->vel.y;
        work->pos.z += work->vel.z;
        work->rot.y += 10.0f;
        work->timer++;
        if((float)work->timer > 30.0f) {
            work->pos.y = work->target.y;
            work->pos.y = work->target.y;
            work->pos.y = work->target.y;
            dead = obj->data;
            Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelKill(obj->mdlId[0]);
            Unk168--;
            for(i=0; i<20; i++) {
                if(obj == Unk170[i]) {
                    Unk170[i] = NULL;
                    break;
                }
            }
            omDelObjEx(ObjMan, obj);
            Unk230[work->no]++;
            Unk210[work->no] = 1;
            HuAudFXPlay(0x96D);
        }
        break;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

/* fn_1_7EB4 -- and take one, on the first free slot of the twenty. */
static void M573Unk7EB4(OMOBJ *obj)
{
    M573_SLOTOBJ *work;
    int i;

    work = obj->data;
    obj->mdlId[0] = Hu3DModelLink(Model16C);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetSca(obj, 1.0f, 1.0f, 1.0f);
    for(i=0; i<20; i++) {
        if(NULL == Unk170[i]) {
            Unk170[i] = obj;
            break;
        }
    }
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    obj->objFunc = M573Unk7BC0;
}

/* fn_1_7FC4 -- 84. */
static void M573Unk7FC4(HuVecF *pos, int no)
{
    OMOBJ *obj;
    M573_SLOTOBJ *work;

    Unk168++;
    obj = omAddObjEx(ObjMan, 0x66, 1, 0, -1, M573Unk7EB4);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_SLOTOBJ), HU_MEMNUM_OVL);
    work = obj->data;
    work->mode = 0;
    work->timer = 0;
    work->screen.x = Unk7CTbl[no][0];
    work->screen.y = 20.0f + Unk7CTbl[no][1];
    work->screen.z = 1500.0f;
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    work->pos.x = pos->x;
    work->pos.y = pos->y;
    work->pos.z = pos->z;
    work->vel.x = work->target.y = work->vel.z = 0.0f;
    work->no = no;
}

/*
 * fn_1_8114 -- drip one of the twenty out every fifteenth frame until the
 * count runs down. M573Unk7FC4 written out, forward inline again.
 */
static void M573Unk8114(OMOBJ *obj)
{
    M573_EFF *eff;
    OMOBJ *obj2;
    M573_SLOTOBJ *work;
    int no;

    eff = obj->data;
    if(eff->unk04 % 15 == 0) {
        no = eff->unk08;
        Unk168++;
        obj2 = omAddObjEx(ObjMan, 0x66, 1, 0, -1, M573Unk7EB4);
        obj2->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_SLOTOBJ), HU_MEMNUM_OVL);
        work = obj2->data;
        work->mode = 0;
        work->timer = 0;
        work->screen.x = Unk7CTbl[no][0];
        work->screen.y = 20.0f + Unk7CTbl[no][1];
        work->screen.z = 1500.0f;
        work->rot.x = work->rot.y = work->rot.z = 0.0f;
        work->pos.x = eff->pos.x;
        work->pos.y = eff->pos.y;
        work->pos.z = eff->pos.z;
        work->vel.x = work->target.y = work->vel.z = 0.0f;
        work->no = no;
        eff->unk00--;
        if(eff->unk00 <= 0) {
            omDelObjEx(ObjMan, obj);
        }
    }
    eff->unk04++;
}

/* fn_1_82C0 -- 45. */
static void M573Unk82C0(HuVecF *pos, int a, int b)
{
    OMOBJ *obj;
    M573_EFF *eff;

    obj = omAddObjEx(ObjMan, 0x66, 0, 0, -1, M573Unk8114);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M573_EFF), HU_MEMNUM_OVL);
    eff = obj->data;
    eff->pos.x = pos->x;
    eff->pos.y = pos->y;
    eff->pos.z = pos->z;
    eff->unk08 = a;
    eff->unk00 = b;
    eff->unk04 = 0;
}

/*
 * fn_1_8374 -- both arms return 1, in the original as well as here: the
 * loop finds a live slot and returns 1, and falling off the end returns 1
 * too. Reproduced as it is.
 */
static int M573Unk8374(void)
{
    int i;

    for(i=0; i<20; i++) {
        if(Unk170[i] != NULL) {
            return 1;
        }
    }
    return 1;
}

/* fn_1_83C8 -- forget the stream handle without stopping it. */
static void M573Unk83C8(void)
{
    Unk164 = -1;
}

/* fn_1_83DC -- start the minigame's streamed music. */
static void M573Unk83DC(void)
{
    Unk164 = HuAudSStreamPlay(0x3D);
}

/* fn_1_840C -- and fade it out over 100ms. */
static void M573Unk840C(void)
{
    HuAudSStreamFadeOut(Unk164, 100);
}

/* fn_1_843C -- the same overlap test as M573HitCheck, but in all three axes
 * and on the true distance rather than its square. */
static int M573Unk843C(HuVecF *a, HuVecF *b, float ra, float rb)
{
    float dx;
    float dy;
    float dz;
    float sum;
    float dist;

    dx = a->x - b->x;
    dy = a->y - b->y;
    dz = a->z - b->z;
    dist = HuMagPoint3D(dx, dy, dz);
    sum = ra + rb;
    if(sum > dist) {
        return 1;
    }
    return 0;
}

/* fn_1_8634 -- the original carries this twice; see M573HitCheck. */
static int M573HitCheck2(HuVecF *a, HuVecF *b, float ra, float rb)
{
    if(((b->x - a->x) * (b->x - a->x)) + ((b->z - a->z) * (b->z - a->z)) < ((ra + rb) * (ra + rb))) {
        return 1;
    }
    return 0;
}

/*
 * fn_1_8694 -- the distance between two points in XZ. This is the helper
 * M573Unk1028 inlines; it is emitted here as well because M573Unk2F40 and
 * M573Unk37A4 call it out of line.
 */
static float M573Dist2D(float ax, float az, float bx, float bz)
{
    float dx;
    float dz;
    float d;

    dx = ax - bx;
    dz = az - bz;
    d = HuMagPoint2D(dx, dz);
    return d;
}

/* fn_1_8804 -- the original carries this twice; see M573RandRange. */
static int M573RandRange2(int min, int max)
{
    return min + frandmod(max - min);
}

