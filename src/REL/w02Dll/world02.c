/*
 * w02dll -- Mario Party 5's second party board. Six board events: a rainbow
 * bridge, a wind guru, thunder, rain, and two "zen" events.
 *
 * Reference assembly:
 *
 *     ./games/mp5/gen_asm.sh w02Dll
 *     build/mp5-asm/w02Dll/asm/REL/w02Dll/world02.s
 *
 * Nothing under build/ is committed. Note the case: the module is **w02Dll**
 * everywhere the decomp build touches it and **w02dll** everywhere the port
 * does. project.py prints a "Case mismatch" line about it; that is expected.
 *
 * THE NAMES ARE THE DISC'S -- upstream's config/GP5E01_00/rels/w02Dll/symbols.txt
 * names all but two of the functions, so what is left here is bodies.
 *
 * Verify per function, never by the headline number:
 *
 *   cd games/mp5 && ./build/tools/ninja build/GP5E01_00/src/REL/w02Dll/world02.o
 *   ./tally.py w02Dll src/REL/w02dll/world02.c 18568
 *   R=$PWD/build/GP5E01_00/w02Dll/obj/REL/w02Dll/world02.o
 *   O=$PWD/build/GP5E01_00/src/REL/w02Dll/world02.o
 *   diff <($PWD/fndiff.py fn $R MB2_Create) <($PWD/fndiff.py fn $O MB2_Create)
 *
 * fndiff.py needs absolute paths, and gen_asm.sh must have been run first --
 * without the reference object every diff reads as empty rather than erroring.
 *
 * ./dumpfn.py <asm.s> <fn> prints one function with its float constants
 * resolved to values, which is what makes two near-identical functions
 * comparable by diff.
 *
 * Read src/REL/w02dll/NOTES.md first, then w03dll's and w07dll's -- the two
 * finished boards. The rules that carry over unchanged: write functions in the
 * reference's order (inlining depends on it), a masu or model id local is int
 * rather than s16, and aggregate locals are declared in reverse stack-slot
 * order.
 */

#include "game/board/main.h"
#include "game/board/effect.h"
#include "game/board/audio.h"
#include "game/board/model.h"
#include "game/board/masu.h"
#include "game/board/scroll.h"
#include "game/board/opening.h"
#include "game/board/capsule.h"
#include "game/board/branch.h"
#include "game/board/camera.h"
#include "game/board/player.h"
#include "game/board/guide.h"
#include "game/board/window.h"
#include "game/board/coin.h"
#include "game/board/com.h"
#include "game/board/roulette.h"
#include "game/board/pad.h"
#include "game/board/star.h"

#include "game/sprite.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/gamemes.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/object.h"
#include "humath.h"

#include "datanum/w02.h"
#include "datanum/capsule.h"
#include "datanum/charmot.h"
#include "messnum/board_w02.h"
#include "game/flag.h"
#include "msm_grp.h"

/* This board's own random: seven bits divided by 127, where the DOL's
 * MBEffRandF() is sixteen bits divided by 65535. The 0.007874016f is 1/127 and
 * the `& 0x7F` shows up as `clrlwi r0,r3,25`. */
#define MB2_RandF() (0.007874016f*(frand() & 0x7F))
#include "math.h"

/* --- the board's own objects ---
 *
 * Unlike w03dll and w07dll, this board does not keep one flat work struct. It
 * runs five OMOBJ subsystems -- coins, coin effects, splashes, the arrow
 * ("yaji") and the rainbow -- each a global OMOBJ* whose obj->data carries the
 * subsystem's work. Every accessor below opens with the same shape: load the
 * global, return early if it is NULL, then read obj->data.
 */

/* This board's own particle system, in place of the DOL's MBEFFECT. The two are
 * the same shape and not the same layout -- the manager is 0x54 against
 * MBEFFECT's 0x40, and the per-particle record 0x58 against MBEFFECTDATA's
 * 0x5C -- so the DOL's structs cannot be reused. Both are pinned by
 * MB2_ParticleCreate's mallocs; the unk fields are the ones no written function
 * has touched yet. */

typedef struct MB2ParticleData_s {
    s16 time;                           /* 0x00 */
    s16 unk02;                          /* 0x02 */
    u8 unk04[0x08-0x04];                /* 0x04 */
    HuVecF vel;                         /* 0x08 */
    float unk14;                        /* 0x14 */
    float unk18;                        /* 0x18 */
    float unk1C;                        /* 0x1C */
    u8 unk20[0x24-0x20];                /* 0x20 */
    float unk24;                        /* 0x24 */
    u8 unk28[0x2C-0x28];                /* 0x28 */
    float unk2C;                        /* 0x2C */
    float unk30;                        /* 0x30 */
    float scale;                        /* 0x34 */
    HuVecF rot;                         /* 0x38 */
    HuVecF pos;                         /* 0x44 */
    GXColor color;                      /* 0x50 */
    int unk54;                          /* 0x54 */
} MB2_PARTICLEDATA;

typedef struct MB2Particle_s MB2_PARTICLE;
typedef void (*MB2PARTICLEHOOK)(HU3DMODEL *modelP, MB2_PARTICLE *partP, Mtx *mtx);

struct MB2Particle_s {
    s16 mode;                           /* 0x00 */
    s16 time;                           /* 0x02 */
    u8 unk04[0x20-0x04];                /* 0x04 */
    u8 blendMode;                       /* 0x20 */
    u8 unk21;                           /* 0x21 */
    u8 unk22;                           /* 0x22 */
    u8 unk23;                           /* 0x23 */
    u8 unk24[0x26-0x24];                /* 0x24 */
    s16 num;                            /* 0x26 */
    u32 unk28;                          /* 0x28 */
    u8 unk2C[0x30-0x2C];                /* 0x2C */
    u32 unk30;                          /* 0x30 */
    u32 dlSize;                         /* 0x34 */
    ANIMDATA *anim;                     /* 0x38 */
    MB2_PARTICLEDATA *data;             /* 0x3C */
    HuVecF *vertex;                     /* 0x40 */
    HuVec2f *st;                        /* 0x44 */
    void *dl;                           /* 0x48 */
    MB2PARTICLEHOOK hook;               /* 0x4C */
    HU3DMODEL *linkModelP;              /* 0x50 -- drawn first, recursively */
};

/* Each subsystem's work block, as far as it has been read. Replace the
 * placeholders a field at a time -- an offset here is only ever a load or a
 * store that has been seen in the reference. */

/* 0xC, pinned by MB2_CoinEffInit's malloc. */
typedef struct MB2CoinEffWork_s {
    int modelId;                        /* 0x00 */
    int num;                            /* 0x04 */
    ANIMDATA *anim;                     /* 0x08 */
} MB2_COINEFFWORK;

/* 0x14, pinned by MB2_SplashEffInit's malloc. Two effects, one per layer:
 * index 0 is the layer-1 normal-blended splash and index 1 the layer-2
 * additive one. */
typedef struct MB2SplashEffWork_s {
    int modelId[2];                     /* 0x00 -- int, not HU3DMODELID: the
                                         * reference stores the s16 result with
                                         * stw and indexes by 4 */
    int num[2];                         /* 0x08 */
    ANIMDATA *anim;                     /* 0x10 */
} MB2_SPLASHEFFWORK;

/* 0x84, pinned by MB2_CoinInit: the coin subsystem's work block is a bare
 * array of 32 of these, with no header -- the 0x1080 malloc is 32*0x84.
 * MB2_CoinUpdate names the rest. */
typedef struct MB2Coin_s {
    int mdlId;                          /* 0x00 */
    int useF;                           /* 0x04 */
    int mode;                           /* 0x08 */
    float speed;                        /* 0x0C */
    int no;                             /* 0x10 */
    int unk14;                          /* 0x14 */
    HuVecF pos;                         /* 0x18 */
    HuVecF rot;                         /* 0x24 */
    HuVecF scale;                       /* 0x30 */
    HuVecF startPos;                    /* 0x3C */
    HuVecF endPos;                      /* 0x48 */
    HuVecF playerPos[4];                /* 0x54 */
} MB2_COIN;

/* 0x4, pinned by MB2_YajiInit's malloc. The arrow's three models live in
 * obj->mdlId[0..2] and the highlighted one is obj->work[0], so the object
 * itself carries most of this subsystem's state and the work block is one
 * counter. */
typedef struct MB2YajiWork_s {
    int time;                           /* 0x00 */
} MB2_YAJIWORK;

/* The rainbow bridge's per-strand record, 0x28, pinned by MB2_RainbowObjCreate
 * (which fills every field) and by RainbowObjDraw (which names the three GX
 * arrays). Eight strands, allocated as one 0x140 block by MB2_RainbowObjInit.
 *
 * `num` is (pointNum-1)*3 -- three Hermite samples per input segment -- and
 * every array below is indexed by it. vtx/st/color are each allocated at
 * *twice* the size they are memset to, because there are two vertices per
 * sample; the memset covering only half is the disc's.
 */
typedef struct MB2RainbowData_s {
    int useF;                           /* 0x00 */
    int num;                            /* 0x04 */
    HuVecF *pos;                        /* 0x08 -- the spline samples */
    HuVecF *rot;                        /* 0x0C -- an angle pair per sample */
    HuVecF *vtx;                        /* 0x10 -- GX_VA_POS array */
    HuVec2f *st;                        /* 0x14 -- GX_VA_TEX0 array */
    GXColor *color;                     /* 0x18 -- GX_VA_CLR0 array */
    GXColor col;                        /* 0x1C -- the strand's tev colour */
    void *dl;                           /* 0x20 */
    u32 dlSize;                         /* 0x24 */
} MB2_RAINBOWDATA;

/* 0xC, pinned by MB2_RainbowObjInit's malloc. */
typedef struct MB2RainbowWork_s {
    int modelId;                        /* 0x00 */
    ANIMDATA *anim;                     /* 0x04 -- copied from mb2_Work */
    MB2_RAINBOWDATA *data;              /* 0x08 -- eight strands */
} MB2_RAINBOWWORK;

/* MB2Ev_Zen2's ride, 0x38 -- one record per segment of the chosen arc, built
 * into a vtxNum-long array on the HuMem heap and hung off mb2_Work.unk70.
 * `startLen` is the cumulative distance at the segment's start, so the ride
 * loop finds the current segment by walking until `dist` falls inside one. */
typedef struct MB2Zen2Data_s {
    float len;                          /* 0x00 */
    float startLen;                     /* 0x04 */
    HuVecF startPos;                    /* 0x08 */
    HuVecF endPos;                      /* 0x14 */
    HuVecF rot;                         /* 0x20 */
    HuVecF prevRot;                     /* 0x2C -- the previous segment's */
} MB2_ZEN2DATA;

/* MB2Ev_Rain's save of one HSF object: HSFOBJECT from `name` through
 * `mesh.curr`, which is exactly 0x64. The event moves nine pieces of the
 * board's scenery by writing their `mesh.base` directly and puts all of this
 * back at the end. HSFOBJECT itself is far bigger, so the prefix is spelled
 * out by hand. */
typedef struct MB2RainObjSave_s {
    char *name;                         /* 0x00 */
    u32 type;                           /* 0x04 */
    void *constData;                    /* 0x08 */
    u32 flags;                          /* 0x0C */
    HSFOBJECT *parent;                  /* 0x10 */
    u32 childNum;                       /* 0x14 */
    HSFOBJECT **child;                  /* 0x18 */
    HSFTRANSFORM base;                  /* 0x1C */
    HSFTRANSFORM curr;                  /* 0x40 */
} MB2_RAINOBJSAVE;

/* One piece of swimming scenery, 0x118, ten of them on MB2Ev_Rain's stack --
 * which is why that function's frame is nearly 4 KB. */
typedef struct MB2RainObj_s {
    HSFOBJECT *objP;                    /* 0x000 */
    MB2_RAINOBJSAVE save;               /* 0x004 */
    int mdlId;                          /* 0x068 */
    float dist;                         /* 0x06C */
    float speed;                        /* 0x070 -- the spin, ramped to 2 */
    float ofsY;                         /* 0x074 -- height above the water */
    int masuId;                         /* 0x078 -- -1 when it carries none */
    int step;                           /* 0x07C */
    int stepMax;                        /* 0x080 */
    int swimLen;                        /* 0x084 -- the delay before it moves */
    int bezierF;                        /* 0x088 -- set for indices 1-3 */
    HuVecF pos;                         /* 0x08C */
    HuVecF dir1;                        /* 0x098 */
    HuVecF dir2;                        /* 0x0A4 */
    HuVecF rot;                         /* 0x0B0 */
    HuVecF masuPos;                     /* 0x0BC */
    HuVecF masuOfs;                     /* 0x0C8 */
    int playerNum;                      /* 0x0D4 */
    int playerNo[4];                    /* 0x0D8 */
    HuVecF playerOfs[4];                /* 0x0E8 */
} MB2_RAINOBJ;

/* One player, 0x58. MB2Ev_Rain keeps two arrays of four: the ones the water
 * catches where they stand, and the ones it drops back at the start space. */
typedef struct MB2RainPlayer_s {
    int playerNo;                       /* 0x00 */
    int motId;                          /* 0x04 */
    int step;                           /* 0x08 */
    int stepMax;                        /* 0x0C */
    float dist;                         /* 0x10 */
    int sideF;                          /* 0x14 */
    int endF;                           /* 0x18 */
    HuVecF pos;                         /* 0x1C */
    HuVecF rot;                         /* 0x28 */
    HuVecF vel;                         /* 0x34 */
    HuVecF savePos;                     /* 0x40 */
    HuVecF startPos;                    /* 0x4C */
} MB2_RAINPLAYER;

/* A space the water lifts, 0x10. Three of them. */
typedef struct MB2RainMasu_s {
    int masuId;                         /* 0x00 */
    HuVecF pos;                         /* 0x04 */
} MB2_RAINMASU;

/* The board's own work block. 0xC4, from
 * config/GP5E01_00/rels/w02Dll/symbols.txt. Fields are named one at a time as
 * a written function touches them; everything else stays a placeholder. */
typedef struct MB2Work_s {
    int objMdlId[7];                    /* 0x00 */
    int kusaMdlId[4];                   /* 0x1C -- the four that breathe */
    int objMdlId2[16];                  /* 0x2C */
    ANIMDATA *rainbowAnim;              /* 0x6C */
    void *unk70;                        /* 0x70 -- freed by MB2_Kill */
    int lightId;                        /* 0x74 */
    HuVecF lightPos;                    /* 0x78 */
    HuVecF lightTarget;                 /* 0x84 */
    u8 lightR;                          /* 0x90 */
    u8 lightG;                          /* 0x91 */
    u8 lightB;                          /* 0x92 */
    u8 unk93;                           /* 0x93 */
    float unk94;                        /* 0x94 */
    int unk98;                          /* 0x98 */
    int unk9C;                          /* 0x9C */
    int unkA0;                          /* 0xA0 */
    int unkA4;                          /* 0xA4 */
    int unkA8;                          /* 0xA8 */
    float unkAC;                        /* 0xAC */
    int rot[5];                         /* 0xB0 -- five random start angles */
} MB2_WORK;

/* MB2_PathLenGet walks the board from a space and reports how far it got;
 * PathCheck is the recursion and these four are how the two communicate. */
static s16 mb2_PathMasuNo;
static s16 mb2_PathLen;
static s16 mb2_PathAllF;
static s16 mb2_PathValidF;

/* The board's camera, from MB2_Create. Each is its own .data symbol, so each
 * is a named static rather than a literal at the call. */
static HuVecF openingRot = { -33, 0, 0 };
static HuVecF openingOfs = { 0, 1400, 0 };
static float openingZoom = 20000;
static HuVecF mapViewRot = { -78, 0, 0 };
static HuVecF mapViewPos = { 19, -3, 187 };
static float mapViewZoom = 19866;

/* The two ambient sound emitters. */
static HuVecF mb2ev_Emiter1Pos = { 0, 200, 2150 };
static HuVecF mb2ev_Emiter2Pos = { -2925, 1210, -25 };

/* MB2_TimerObjUpdate's three: the countdown in frames, the frame it starts
 * counting from, and the on-screen message it drives. Upstream's symbol names
 * for the first two say "Obj" and "Value"; only the second is a value. */
static int mb2ev_TimerValue;
static int mb2ev_TimerObj;
static int mb2ev_TimerGameMesId;

/* Set once by MB2_CoinInit; only .x and .y are non-zero. */
static HuVecF mb2_CoinMaxDist;

/* Seven pastel tints, picked at random by MB2_CoinEffCreateColRand. */
static GXColor mb2ev_CoinEffColTbl[7] = {
    { 255, 127, 127, 255 },
    { 255, 127,  64, 255 },
    { 255, 255, 127, 255 },
    { 127, 255, 127, 255 },
    { 127, 127, 255, 255 },
    {  64,  64, 255, 255 },
    { 255, 127, 255, 255 },
};

/* Where the dynamo stands, and where its capsules are thrown from. */
static HuVecF mb2ev_DynamoPos = { 0, 300, 2150 };
static HuVecF mb2ev_BiriQCapsulePos = { 0, 250, 1650 };

/* The five rainbow arcs, as world-space control points. MB2_RainbowObjCreate
 * Catmull-Roms three samples per segment out of these. */
static HuVecF mb2ev_Rainbow1VtxTbl[10] = {
    { 1250, 300, 3100 },
    { 1199.568, 326.661, 3026.67 },
    { 1148.407, 349.08, 2952.47 },
    { 1096.113, 362.72, 2876.98 },
    { 1043.026, 361.417, 2800.94 },
    { 990.766, 342.337, 2726.77 },
    { 940.614, 308.92, 2656.17 },
    { 892.531, 266.645, 2588.89 },
    { 845.905, 219.419, 2523.88 },
    { 800, 170, 2460 },
};

static HuVecF mb2ev_Rainbow2VtxTbl[20] = {
    { -1200, 700, 1300 },
    { -1291.964, 743.942, 1346.68 },
    { -1382.014, 788.448, 1396.43 },
    { -1466.921, 834.131, 1453.48 },
    { -1539.02, 881.278, 1524.7 },
    { -1580.467, 928.213, 1616.64 },
    { -1563.531, 969.423, 1716.98 },
    { -1474.897, 992.177, 1776.6 },
    { -1364.581, 1002.961, 1777.13 },
    { -1270.675, 1015.835, 1720.79 },
    { -1224.387, 1036.946, 1622.16 },
    { -1216.906, 1066.805, 1514.74 },
    { -1235.444, 1106.81, 1412.06 },
    { -1276.334, 1159.136, 1322.23 },
    { -1335.749, 1221.672, 1251.04 },
    { -1407.514, 1287.394, 1195.65 },
    { -1489.253, 1350.859, 1152.84 },
    { -1582.244, 1404.255, 1121.02 },
    { -1688.228, 1434.387, 1103.3 },
    { -1799.999, 1440, 1100 },
};

static HuVecF mb2ev_Rainbow3VtxTbl[20] = {
    { -1800, 1540, -500 },
    { -1880.726, 1563.051, -541.46 },
    { -1955.005, 1599.109, -585.33 },
    { -2018.179, 1650.931, -630.78 },
    { -2068.714, 1715.038, -676.44 },
    { -2105.92, 1788.005, -721.6 },
    { -2127.28, 1867.937, -765.21 },
    { -2132.73, 1951.81, -806.18 },
    { -2123.829, 2036.928, -844 },
    { -2104.256, 2121.417, -879.28 },
    { -2075.773, 2204.186, -912.54 },
    { -2039.813, 2284.551, -944.38 },
    { -1996.263, 2361.491, -975.14 },
    { -1943.885, 2433.059, -1004.99 },
    { -1881.315, 2496.491, -1033.5 },
    { -1807.314, 2547.403, -1059.36 },
    { -1722.491, 2580.059, -1080.52 },
    { -1630.5, 2587.105, -1094 },
    { -1538.823, 2569.648, -1099.21 },
    { -1450.001, 2540, -1100 },
};

static HuVecF mb2ev_Rainbow4VtxTbl[20] = {
    { 1500, 2550, -1190 },
    { 1571.996, 2561.101, -1206.56 },
    { 1645.197, 2559.717, -1220.61 },
    { 1716.815, 2541.587, -1230.65 },
    { 1784.242, 2510.155, -1236.86 },
    { 1847.66, 2470.814, -1239.96 },
    { 1907.417, 2425.963, -1239.98 },
    { 1962.907, 2376.073, -1236.23 },
    { 2013.627, 2321.839, -1228.31 },
    { 2058.137, 2263.345, -1215.23 },
    { 2094.266, 2200.936, -1195.83 },
    { 2121.515, 2136.194, -1170.47 },
    { 2140.562, 2070.692, -1140.09 },
    { 2151.713, 2005.668, -1105.09 },
    { 2154.992, 1942.429, -1065.5 },
    { 2148.906, 1883.279, -1020.37 },
    { 2132.147, 1831.016, -969.85 },
    { 2104.564, 1788.458, -915.12 },
    { 2069.679, 1755.229, -858.07 },
    { 2030, 1730, -800 },
};

static HuVecF mb2ev_Rainbow5VtxTbl[20] = {
    { 1800, 1420, 1100 },
    { 1679.699, 1414.27, 1100.79 },
    { 1559.871, 1403.632, 1105.85 },
    { 1442.407, 1382.131, 1120.38 },
    { 1331.805, 1344.757, 1148.88 },
    { 1235.107, 1289.613, 1194.16 },
    { 1153.509, 1224.39, 1253.72 },
    { 1088.862, 1155.699, 1328.21 },
    { 1045.925, 1091.566, 1420.06 },
    { 1037.059, 1044.713, 1529.83 },
    { 1068.308, 1018.265, 1642.27 },
    { 1140.777, 1006.366, 1736.29 },
    { 1250.25, 999.706, 1782.19 },
    { 1366.816, 987.142, 1763.94 },
    { 1449.734, 957.98, 1684.69 },
    { 1480.7, 914.25, 1578.05 },
    { 1460.046, 859.905, 1473.98 },
    { 1389.962, 800.882, 1397.07 },
    { 1298.235, 744.402, 1343.53 },
    { 1200.001, 690.001, 1300 },
};
/* Space flag 1-9 picks one of the five arcs; 0 and 10 are not rainbows. */
static int mb2ev_RainbowNoTbl[11] = { 0, 1, 1, 2, 2, 3, 3, 4, 4, 0, 0 };

/* ...and which way along it the player walks. */
static int mb2ev_RainbowDirTbl[11] = { 0, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1 };

static HuVecF *mb2ev_RainbowVtxTbl[5] = {
    mb2ev_Rainbow1VtxTbl,
    mb2ev_Rainbow2VtxTbl,
    mb2ev_Rainbow3VtxTbl,
    mb2ev_Rainbow4VtxTbl,
    mb2ev_Rainbow5VtxTbl,
};

static int mb2ev_RainbowVtxNumTbl[5] = { 10, 20, 20, 20, 20 };

static int mb2ev_RainbowRevF[5] = { 0, 0, 0, 0, 1 };

/* --- MB2Ev_Zen2's nine arcs --- */

/* Three sets of three. A random set index picks the row; the player's arrow
 * choice picks left, centre or right within it. */
static HuVecF mb2ev_Zen2Rainbow1VtxTbl[20] = {
    { -200, 3900, -1850 },
    { -383.691, 3957.388, -1632.8 },
    { -569.943, 3999.349, -1414.37 },
    { -759.893, 4006.413, -1195.55 },
    { -950.2, 3960.654, -982.16 },
    { -1133.776, 3852.119, -786.17 },
    { -1313.344, 3704.046, -613.26 },
    { -1496.564, 3535.799, -464.05 },
    { -1692.226, 3361.214, -340.09 },
    { -1907.234, 3192.807, -242.57 },
    { -2136.775, 3033.594, -164.17 },
    { -2369.884, 2878.006, -88.92 },
    { -2591.051, 2717.305, 7.43 },
    { -2759.3, 2543.466, 164.07 },
    { -2814.604, 2361.217, 379.6 },
    { -2747.107, 2177.241, 590.41 },
    { -2581.491, 1995.222, 741.25 },
    { -2367.963, 1822.911, 834.65 },
    { -2136.937, 1659.382, 898.31 },
    { -1900.002, 1500.002, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow2VtxTbl[20] = {
    { -0.0f, 3900, -1850 },
    { 2.515, 3963.649, -1516.32 },
    { 19.071, 3996.487, -1179 },
    { 64.98, 3962.608, -845.2 },
    { 148.358, 3837.864, -542.24 },
    { 253.175, 3643.807, -284.68 },
    { 352.856, 3413.188, -56.35 },
    { 428.063, 3160.465, 157.45 },
    { 455.205, 2894.713, 366.28 },
    { 396.277, 2633.664, 572.97 },
    { 237.762, 2403.402, 764.54 },
    { 31.742, 2195.484, 936.66 },
    { -183.519, 1987.069, 1096.75 },
    { -369.07, 1750.183, 1253.09 },
    { -489.389, 1474.039, 1408.27 },
    { -540.721, 1176.348, 1562.24 },
    { -527.638, 876.381, 1719.97 },
    { -437.547, 601.854, 1895.82 },
    { -249.679, 407.549, 2097.09 },
    { -0.001, 300, 2299.99 },
};

static HuVecF mb2ev_Zen2Rainbow3VtxTbl[20] = {
    { 200, 3900, -1850 },
    { 293.586, 4017.404, -1632.47 },
    { 394.429, 4099.883, -1403.07 },
    { 503.464, 4110.866, -1163.93 },
    { 613.226, 4042.236, -934.32 },
    { 725.561, 3929.754, -723.32 },
    { 849.838, 3801.236, -528.74 },
    { 1000.256, 3674.096, -353 },
    { 1200.559, 3576.967, -212.99 },
    { 1440.852, 3519.787, -119.88 },
    { 1683.247, 3457.704, -35.65 },
    { 1882.63, 3337.981, 86.4 },
    { 2018.671, 3164.915, 230.82 },
    { 2098.837, 2957.397, 372.46 },
    { 2130.558, 2727.509, 498.17 },
    { 2127.353, 2486.419, 606.01 },
    { 2102.257, 2241.094, 701.02 },
    { 2064.211, 1994.374, 787.94 },
    { 2018.829, 1747.238, 870.11 },
    { 1970.001, 1500.003, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow4VtxTbl[20] = {
    { -200, 3900, -1850 },
    { -429.937, 3970.303, -1578.29 },
    { -664.641, 4008.682, -1304.64 },
    { -903.124, 3977.542, -1034.33 },
    { -1131.647, 3852.676, -783.26 },
    { -1334.946, 3668.717, -546.05 },
    { -1504.575, 3467.395, -296.84 },
    { -1619.343, 3292.86, -2.01 },
    { -1641.059, 3162.092, 334.31 },
    { -1575.688, 3022.238, 661.69 },
    { -1456.392, 2836.731, 949.09 },
    { -1311.891, 2613.394, 1195.39 },
    { -1155.236, 2365.526, 1408.74 },
    { -992.286, 2098.527, 1592.37 },
    { -826.821, 1815.883, 1748.34 },
    { -660.925, 1521.952, 1881.41 },
    { -495.239, 1221.115, 1998.37 },
    { -329.903, 916.088, 2104.52 },
    { -164.866, 608.628, 2203.94 },
    { -0.002, 300.004, 2299.99 },
};

static HuVecF mb2ev_Zen2Rainbow5VtxTbl[20] = {
    { -0.0f, 3900, -1850 },
    { 1.133, 3952.1, -1586.88 },
    { 9.213, 3989.066, -1321.44 },
    { 31.846, 3993.611, -1054.57 },
    { 75.903, 3948.549, -794.66 },
    { 143.143, 3846.868, -556.73 },
    { 228.091, 3701.37, -348.41 },
    { 325.933, 3531.735, -165.27 },
    { 433.899, 3352.204, 2.07 },
    { 553.506, 3169.027, 157.19 },
    { 691.426, 2990.496, 302.1 },
    { 863.059, 2836.395, 437.37 },
    { 1092.497, 2755.268, 543.01 },
    { 1356.83, 2764.895, 576.34 },
    { 1609.945, 2700.367, 558.61 },
    { 1759.182, 2483.774, 585.69 },
    { 1836.328, 2238.497, 660.58 },
    { 1888.745, 1991.948, 752.14 },
    { 1931.346, 1745.822, 849.86 },
    { 1970, 1500.003, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow6VtxTbl[20] = {
    { 200, 3900, -1850 },
    { 312.828, 4037.487, -1588.2 },
    { 436.923, 4114.095, -1308.74 },
    { 568.465, 4077.719, -1025.38 },
    { 682.508, 3949.339, -760.19 },
    { 756.823, 3779.562, -504.03 },
    { 780.306, 3592.37, -250.36 },
    { 748.015, 3403.604, 1.07 },
    { 663.736, 3220.931, 245.03 },
    { 535.257, 3044.243, 473.66 },
    { 363.229, 2873.831, 676.78 },
    { 143.024, 2713.271, 835.92 },
    { -127.677, 2574.293, 916.45 },
    { -424.691, 2467.968, 903.02 },
    { -721.353, 2379.62, 837.35 },
    { -1013.081, 2288.386, 754.83 },
    { -1296.628, 2161.15, 699.83 },
    { -1545.663, 1970.648, 725.01 },
    { -1739.84, 1740.978, 821.54 },
    { -1899.999, 1500.002, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow7VtxTbl[20] = {
    { -200, 3900, -1850 },
    { -428.171, 3969.886, -1580.36 },
    { -661.023, 4008.65, -1308.8 },
    { -897.74, 3979.474, -1040.3 },
    { -1124.033, 3855.993, -790.68 },
    { -1314.348, 3658.507, -558.57 },
    { -1441.333, 3413.334, -329.06 },
    { -1464.622, 3145.97, -92.28 },
    { -1351.601, 2892.572, 132.4 },
    { -1103.064, 2695.024, 293.85 },
    { -766.264, 2590.652, 349.17 },
    { -409.103, 2555.593, 327.45 },
    { -52.105, 2540.375, 282.93 },
    { 305.089, 2513.975, 247.59 },
    { 658.514, 2449.893, 248.89 },
    { 987.826, 2324.067, 314.62 },
    { 1275.066, 2146.722, 438.12 },
    { 1525.683, 1941.645, 595.15 },
    { 1753.355, 1723.518, 768.97 },
    { 1969.997, 1500.003, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow8VtxTbl[20] = {
    { -0.0f, 3900, -1850 },
    { 1.724, 3958.553, -1556.67 },
    { 13.029, 4004.358, -1261.4 },
    { 43.935, 4023.525, -964.78 },
    { 106.254, 3998.353, -673.98 },
    { 202.648, 3920.42, -402.53 },
    { 313.205, 3799.751, -152.51 },
    { 410.826, 3645.382, 84 },
    { 453.021, 3458.88, 312.27 },
    { 362.978, 3263.239, 511.81 },
    { 149.855, 3102.214, 642.03 },
    { -106.456, 2968.213, 716.78 },
    { -374.053, 2841.098, 756.98 },
    { -639.687, 2704.464, 769.05 },
    { -894.626, 2548.588, 758.76 },
    { -1135.125, 2372.01, 739.07 },
    { -1358.734, 2173.846, 732.35 },
    { -1560.624, 1956.744, 768.15 },
    { -1737.879, 1729.674, 847.89 },
    { -1899.999, 1500.002, 949.99 },
};

static HuVecF mb2ev_Zen2Rainbow9VtxTbl[20] = {
    { 200, 3900, -1850 },
    { 321.057, 4046.076, -1569.27 },
    { 455.367, 4117.304, -1268.14 },
    { 595.575, 4055.788, -968.14 },
    { 721.198, 3910.239, -689.48 },
    { 824.595, 3735.333, -418.27 },
    { 900.756, 3554.676, -141.88 },
    { 944.238, 3381.77, 146.19 },
    { 952.703, 3212.513, 439.6 },
    { 927.023, 3036.135, 727.71 },
    { 867.757, 2842.836, 999.47 },
    { 778.95, 2626.907, 1244.83 },
    { 670.253, 2388.708, 1459.85 },
    { 553.617, 2131.415, 1646.93 },
    { 438.208, 1855.854, 1806.85 },
    { 332.712, 1562.432, 1939.51 },
    { 238.995, 1255.835, 2049.38 },
    { 154.32, 941.033, 2142.22 },
    { 75.653, 621.574, 2223.89 },
    { 0.001, 300.004, 2299.99 },
};

static HuVecF *mb2ev_Zen2RainbowVtxTbl[3][3] = {
    { mb2ev_Zen2Rainbow1VtxTbl, mb2ev_Zen2Rainbow2VtxTbl, mb2ev_Zen2Rainbow3VtxTbl },
    { mb2ev_Zen2Rainbow4VtxTbl, mb2ev_Zen2Rainbow5VtxTbl, mb2ev_Zen2Rainbow6VtxTbl },
    { mb2ev_Zen2Rainbow7VtxTbl, mb2ev_Zen2Rainbow8VtxTbl, mb2ev_Zen2Rainbow9VtxTbl },
};

static int mb2ev_Zen2RainbowVtxNumTbl[3][3] = {
    { 20, 20, 20 },
    { 20, 20, 20 },
    { 20, 20, 20 },
};

/* Which of the three spaces MB2Ev_Zen2 hunted down each arc lands on. */
static int mb2ev_Zen2DestTbl[3][3] = {
    { 0, 1, 2 },
    { 1, 2, 0 },
    { 2, 0, 1 },
};

/* Where the coin fountain plays while the arcs are being built. */
static HuVecF mb2ev_Zen2CoinBasePos = { 0, 3917, -2497 };

/* --- MB2Ev_Rain --- */

/* The nine pieces of scenery the flood cuts loose, plus the gate itself. */
static char *mb2ev_RainObjTbl[10] = {
    "suimon", "hs_a", "hs_b", "hs_c", "hs_d", "hs_e", "hs_f", "hs_g", "hs_h", "hs_i",
};

/* Which space each one carries, -1 for none. */
static s8 mb2ev_RainNoTbl[10] = { -1, 1, 2, 3, -1, -1, -1, -1, -1, -1 };

/* How long each one waits before it starts to swim. */
static int mb2ev_RainSwimLenTbl[10] = { 0, 240, 60, 180, 0, 90, 0, 0, 0, 0 };

static HuVecF mb2ev_RainSwimMidPos = { -3570, 1190, -625 };
static HuVecF mb2ev_RainSwimRightPos = { -2450, 1210, 500 };
static HuVecF mb2ev_RainSwimLeftPos = { -3200, 1620, -250 };
static HuVecF mb2ev_RainSwimDefPos = { 0, 0, 0 };

/* The four wind directions, in degrees, indexed by the space's own 1-4. */
static float mb2ev_WindGuru2RotTbl[5] = { 0, 180, 90, 0, -90 };

/* The guru's four hand bones, plus the miss. */
static char *mb2ev_WindGuru2HookTbl[5] = { "hazure", "k_f3", "k_f2", "k_f1", "k_f4" };

/* The three arrow directions, in degrees. */
static float yajiAngleTbl[3] = { -45, 0, 45 };

static OMOBJ *mb2_MainObj;
static int *mb2_SaveWorkP;
static MB2_WORK mb2_Work;

static OMOBJ *mb2_CoinObj;
static OMOBJ *mb2_CoinEffObj;
static OMOBJ *mb2_SplashEffObj;
static OMOBJ *mb2_YajiObj;
static OMOBJ *mb2_RainbowObj;

/* --- forward declarations, in the reference's order --- */

void ObjectSetup(void); /* 21 instructions */
static void MB2_Create(void); /* 755 instructions */
static void MB2_Kill(void); /* 42 instructions */
static void MB2_MainObjUpdate(OMOBJ *obj); /* 744 instructions */
static void MB2_LightSet(void); /* 110 instructions */
static void MB2_LightReset(void); /* 1 instructions */
static int MB2Ev_MasuHatena(int playerNo); /* 57 instructions */
static void MB2_Stub(void); /* 1 instructions */
static int MB2Ev_MasuWalkPre(int playerNo); /* 1 instructions */
static int MB2Ev_MasuWalkPost(int playerNo); /* 73 instructions */
static int MB2_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF); /* 75 instructions */
static int MB2Ev_Rainbow(int no, int playerNo); /* 1134 instructions */
static void MB2Ev_WindGuru2(int no, int playerNo); /* 618 instructions */
static void MB2Ev_Thunder(int playerNo); /* 1622 instructions */
static void MB2Ev_Rain(int playerNo); /* 1759 instructions -- NOT WRITTEN */
static void MB2Ev_Zen2(int playerNo); /* 1786 instructions -- NOT WRITTEN */
static void MB2Ev_Zen4(int playerNo); /* 2278 instructions -- NOT WRITTEN */
static void MB2_TimerObjUpdate(OMOBJ *obj); /* 122 instructions */
static void MB2_DentyuObjFlash(OMOBJ *obj); /* 59 instructions */
static void MB2_WaterSplashUpdate(OMOBJ *obj); /* 209 instructions */
static int MB2_WindGuru2MasuNoGet(int masuId, int no); /* 58 instructions */
static int MB2_RainbowMasuNoEndGet(int masuId); /* 79 instructions */
static BOOL MB2_PathCheck(int masuId); /* 19 instructions */
static s16 MB2_PathLenGet(s16 masuId, s16 num, s16 allF); /* 39 instructions */
static s16 PathCheck(s16 masuId, s16 num); /* 185 instructions */
static void MB2_CoinDispUpdate(int playerNo, int coin, int total); /* 140 instructions */
static float MB2_AngleDiff(float angle1, float angle2); /* 70 instructions */
static float MB2_AngleLerp(float target, float angle, float speed); /* 148 instructions */
static float fn_1_BF54(float rate, float angle, float target); /* 254 instructions */
static int MB2_MasuLinkGet(s16 masuId, s16 *linkTbl, BOOL linkF, BOOL pathF); /* 45 instructions */
static HSFOBJECT *MB2_ModelObjPtrGet(HU3DMODEL *modelP, char *name); /* 18 instructions */
static HSFOBJECT *objCall(HU3DMODEL *modelP, char *name, HSFOBJECT *object); /* 530 instructions */
static float MB2_BezierCalc(float t, float p0, float p1, float p2); /* 30 instructions */
static void MB2_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out); /* 71 instructions */
static void MB2_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11); /* 37 instructions */
static float fn_1_CEB8(float t, float p0, float p1, float p2, float p3, float tension); /* 90 instructions */
static void MB2_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out); /* 304 instructions */
static void MB2_CoinInit(void); /* 100 instructions */
static void MB2_CoinUpdate(OMOBJ *obj); /* 668 instructions */
static void MB2_CoinClose(void); /* 5 instructions */
static int MB2_CoinNumGet(void); /* 35 instructions */
static int MB2_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int no); /* 136 instructions */
static void MB2_CoinEffInit(void); /* 64 instructions */
static void MB2_CoinEffUpdate(OMOBJ *obj); /* 124 instructions */
static void MB2_CoinEffClose(void); /* 5 instructions */
static int MB2_CoinEffNumGet(void); /* 20 instructions */
static void MB2_CoinEffBlendModeSet(int blendMode); /* 29 instructions */
static int MB2_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color); /* 119 instructions */
static int MB2_CoinEffCreateRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no); /* 276 instructions */
static int MB2_CoinEffCreateColRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no); /* 211 instructions */
static void MB2_SplashEffInit(void); /* 99 instructions */
static void MB2_SplashEffUpdate(OMOBJ *obj); /* 130 instructions */
static void MB2_SplashEffClose(void); /* 5 instructions */
static int MB2_SplashEffNumGet(void); /* 22 instructions */
static void MB2_SplashEffCreate(HuVecF *pos, HuVecF *vel, GXColor *color, int time, int no, float scale, float rotZ, float accelY); /* 123 instructions */
static void MB2_SplashEffCreateRandX(HuVecF *pos, GXColor *color, float scale, int no); /* 150 instructions */
static HU3DMODELID MB2_ParticleCreate(ANIMDATA *anim, s16 maxCnt); /* 302 instructions */
static HU3DMODELID MB2_ParticleCopy(HU3DMODELID srcMdlId); /* 209 instructions */
static void ParticleDraw(HU3DMODEL *modelP, Mtx *mtx); /* 656 instructions */
static void MB2_YajiInit(HuVecF *pos); /* 146 instructions */
static void MB2_YajiUpdate(OMOBJ *obj); /* 137 instructions */
static void MB2_YajiClose(void); /* 5 instructions */
static void MB2_YajiHiliteSet(int no); /* 20 instructions */
static void MB2_YajiDispSet(int dispF); /* 45 instructions */
static void MB2_RainbowObjInit(void); /* 84 instructions */
static void MB2_RainbowObjUpdate(OMOBJ *obj); /* 46 instructions */
static void MB2_RainbowObjClose(void); /* 5 instructions */
static int MB2_RainbowObjCreate(HuVecF *point, int num, int reverseF); /* 744 instructions */
static void MB2_RainbowObjAlphaSet(int no, u8 alpha); /* 23 instructions */
static int MB2_RainbowObjVtxTopGet(int no, HuVecF **outPos); /* 25 instructions */
static void RainbowObjDraw(HU3DMODEL *modelP, Mtx *mtx); /* 176 instructions */

/* --- bodies, in the reference's order --- */

/* 21 instructions */
void ObjectSetup(void)
{
    GWPartyFSet(TRUE);
    MBObjectSetup(MBNO_WORLD_2, MB2_Create, MB2_Kill);
}

/* 755 instructions */
static void MB2_Create(void)
{
    int boardNo = MBBoardNoGet();
    int mdlId;

    HuAudSndGrpSetSet(MSM_GRP_BD2);
    MBMasuCreate(W02_BIN_masuData);
    MBScrollInit(W02_HSF_scrollCol, 18000, -500);
    mb2_Work.objMdlId[0] = mdlId = MBModelCreate(W02_HSF_obj01, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId[1] = mdlId = MBModelCreate(W02_HSF_obj07, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mdlId, 0.5);
    mb2_Work.objMdlId[2] = mdlId = MBModelCreate(W02_HSF_obj13, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId[3] = mdlId = MBModelCreate(W02_HSF_obj16, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId[4] = mdlId = MBModelCreate(W02_HSF_obj19, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0.05);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId[5] = mdlId = MBModelCreate(W02_HSF_obj20, NULL, FALSE);
    mb2_Work.objMdlId[6] = mdlId = MBModelCreate(W02_HSF_obj12, NULL, FALSE);
    mb2_Work.objMdlId2[0] = mdlId = MBModelCreate(W02_HSF_obj26, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.kusaMdlId[0] = mdlId = MBModelCreate(W02_HSF_obj21, NULL, FALSE);
    mb2_Work.kusaMdlId[1] = mdlId = MBModelCreate(W02_HSF_obj22, NULL, FALSE);
    mb2_Work.kusaMdlId[2] = mdlId = MBModelCreate(W02_HSF_obj23, NULL, FALSE);
    mb2_Work.kusaMdlId[3] = mdlId = MBModelCreate(W02_HSF_obj24, NULL, FALSE);
    mb2_Work.objMdlId2[1] = mdlId = MBModelCreate(W02_HSF_obj02, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    mb2_Work.objMdlId2[2] = mdlId = MBModelCreate(W02_HSF_obj03, NULL, FALSE);
    mb2_Work.objMdlId2[3] = mdlId = MBModelCreate(W02_HSF_obj04, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    mb2_Work.objMdlId2[4] = mdlId = MBModelCreate(W02_HSF_obj05, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mdlId, 0.5);
    mb2_Work.objMdlId2[5] = mdlId = MBModelCreate(W02_HSF_obj06, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId2[6] = mdlId = MBModelCreate(W02_HSF_obj08, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    MBModelPosSet(mdlId, -2640, 1250, 900);
    MBModelLayerSet(mdlId, 2);
    mb2_Work.objMdlId2[7] = mdlId = MBModelCreate(W02_HSF_obj08, NULL, TRUE);
    MBMotionSpeedSet(mdlId, 0);
    MBModelPosSet(mdlId, -2950, 1300, 800);
    MBModelLayerSet(mdlId, 2);
    mb2_Work.objMdlId2[8] = mdlId = MBModelCreate(W02_HSF_obj09, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mdlId, 0.33f);
    mb2_Work.objMdlId2[9] = mdlId = MBModelCreate(W02_HSF_obj10, NULL, FALSE);
    MBModelPosSet(mdlId, -2930, 1210, 20);
    MBModelRotSet(mdlId, 0, 45, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId2[10] = mdlId = MBModelCreate(W02_HSF_obj11, NULL, FALSE);
    MBModelPosSet(mdlId, -2930, 1215, 20);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId2[11] = mdlId = MBModelCreate(W02_HSF_obj14, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb2_Work.objMdlId2[12] = mdlId = MBModelCreate(W02_HSF_obj15, NULL, FALSE);
    mb2_Work.objMdlId2[13] = mdlId = MBModelCreate(W02_HSF_obj17, NULL, FALSE);
    MBModelRotSet(mdlId, 0, -50, 0);
    mb2_Work.objMdlId2[14] = mdlId = MBModelCreate(W02_HSF_obj18, NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    mb2_Work.objMdlId2[15] = mdlId = MBModelCreate(W02_HSF_obj25, NULL, FALSE);
    mdlId = MBCapsuleColCreate(W02_HSF_capsuleCol);
    mb2_Work.rainbowAnim = HuSprAnimRead(HuDataReadNum(W02_ANM_board, HU_MEMNUM_OVL));
    mb2_Work.unk70 = NULL;
    mb2_Work.lightId = -1;
    mb2_Work.unk94 = 1;
    mb2_Work.unk98 = 1;
    mb2_Work.unk9C = 1;
    mb2_Work.unkA0 = 1;
    mb2_Work.unkA4 = 0;
    mb2_Work.rot[0] = 360*MB2_RandF();
    mb2_Work.rot[1] = 360*MB2_RandF();
    mb2_Work.rot[2] = 360*MB2_RandF();
    mb2_Work.rot[3] = 360*MB2_RandF();
    mb2_Work.rot[4] = 360*MB2_RandF();
    mb2_Work.unkAC = 0;
    mb2_SaveWorkP = MBSaveWorkPGet();
    if(!_CheckFlag(FLAG_BOARD_OPENING)) {
        mb2_SaveWorkP[0] = (frand() & 0x7FFF)%3;
    }
    if(mb2_SaveWorkP[0] == 0) {
        mb2_SaveWorkP[0] = (frand() & 0x7FFF)%3;
    }
    if(mb2_SaveWorkP[0] < 1) {
        mb2_SaveWorkP[0] = 1;
    } else if(mb2_SaveWorkP[0] > 3) {
        mb2_SaveWorkP[0] = 3;
    }
    MB2_SplashEffInit();
    HuDataDirClose(DATA_w02);
    MBBranchFlagSet(MASU_FLAG_BIT(14));
    MBLightHookSet(MB2_LightSet, MB2_LightReset);
    MBMasuWalkPreHookSet(MB2Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB2Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB2Ev_MasuHatena);
    MBMasuPathCheckHookSet(MB2_MasuPathCheck);
    HuDataDirRead(DATA_capsule);
    mb2_MainObj = MBAddObj(32768, 0, 0, MB2_MainObjUpdate);
    MBAudFXEmiterCreate(1488, &mb2ev_Emiter1Pos, FALSE);
    MBAudFXEmiterCreate(1498, &mb2ev_Emiter2Pos, FALSE);
    MBOpeningViewSet(&openingRot, &openingOfs, openingZoom);
    MBMapViewCameraSet(&mapViewRot, &mapViewPos, mapViewZoom);
}

/* 42 instructions */
static void MB2_Kill(void)
{
    mb2_MainObj = NULL;
    if(mb2_Work.rainbowAnim) {
        HuSprAnimKill(mb2_Work.rainbowAnim);
    }
    mb2_Work.rainbowAnim = NULL;
    if(mb2_Work.unk70) {
        HuMemDirectFree(mb2_Work.unk70);
    }
    mb2_Work.unk70 = NULL;
    MB2_CoinClose();
    MB2_CoinEffClose();
    MB2_YajiClose();
    MB2_RainbowObjClose();
    MB2_SplashEffClose();
}

/* 744 instructions
 *
 * The board's idle animation, per frame: four bushes and one cloud breathe on
 * their own random phase, the global light fades in or out, one model rides
 * another's "sisof2" bone, three water splashes are spawned at the waterfall,
 * and two motions stop themselves when they end.
 *
 * Three locals here are written and never read -- the camera, the splash's
 * rotation, and the motion-time comparison at the bottom. All three are the
 * disc's; the function is short without them.
 */
static void MB2_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;
    GXColor colRand;
    float speed;
    GXColor col;
    HuVecF pos;
    HuVecF vec;
    Mtx mtx;
    HSFOBJECT *objP;
    HU3DMODEL *modelP;
    int mdlId;
    GXColor *colP;
    int i;
    int no;
    float scaleX;
    float scaleY;
    float scaleZ;
    float rate;
    float rotZ;

    if(MBKillCheck() || mb2_MainObj == NULL) {
        omDelObjEx(mbObjMan, mb2_MainObj);
        mb2_MainObj = NULL;
        return;
    }
    camera = MBCameraGet();
    for(i=0; i<4; i++) {
        mb2_Work.rot[i] += ((frand() & 0x7FFF)%3)+1;
        scaleX = 1+(0.01*HuSin(mb2_Work.rot[i]));
        scaleY = 1+(0.0025*HuSin(mb2_Work.rot[i]));
        scaleZ = 1+(0.01*HuSin(mb2_Work.rot[i]));
        MBModelScaleSet(mb2_Work.kusaMdlId[i], scaleX, scaleY, scaleZ);
    }
    mb2_Work.rot[4] += ((frand() & 0x7FFF)%3)+1;
    scaleX = 1+(0.01*HuSin(mb2_Work.rot[4]));
    scaleY = 1+(0.0025*HuSin(mb2_Work.rot[4]));
    scaleZ = 1+(0.01*HuSin(mb2_Work.rot[4]));
    mdlId = MBModelIdGet(mb2_Work.objMdlId2[15]);
    modelP = &Hu3DData[mdlId];
    objP = MB2_ModelObjPtrGet(modelP, "s_cloud00");
    if(objP) {
        objP->mesh.base.scale.x = scaleX;
        objP->mesh.base.scale.y = scaleY;
        objP->mesh.base.scale.z = scaleZ;
    }
    if(mb2_Work.lightId != -1) {
        if(mb2_Work.unk98) {
            if(mb2_Work.unk94 < 1) {
                if((mb2_Work.unk94 += 0.03f) > 1) {
                    mb2_Work.unk94 = 1;
                }
            }
        } else {
            if(mb2_Work.unk94 > 0) {
                if((mb2_Work.unk94 -= 0.03f) < 0) {
                    mb2_Work.unk94 = 0;
                }
            }
        }
        mb2_Work.lightR = mb2_Work.lightG = mb2_Work.lightB = mb2_Work.unk93 = 255*mb2_Work.unk94;
        Hu3DGLightColorSet(mb2_Work.lightId, mb2_Work.lightR, mb2_Work.lightG, mb2_Work.lightB, mb2_Work.unk93);
    }
    if(mb2_Work.unk9C) {
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
        MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
    }
    if(mb2_Work.unkA0) {
        for(i=0; i<3; i++) {
            rate = 0.5f-MB2_RandF();
            pos.x = -2925+(1.5*(100*(rate*HuSin(-45))));
            pos.y = 1210+(0.25f*(100*(0.5f-MB2_RandF())));
            pos.z = -25+(1.5*(100*(rate*HuCos(-45))));
            vec.x = vec.y = vec.z = 0;
            rate = 64*MB2_RandF();
            colRand.r = 170+rate;
            colRand.g = 170+rate;
            colRand.b = 190+rate;
            colRand.a = 64+(63*MB2_RandF());
            if(frand() & 1) {
                rotZ = 0.1f;
            } else {
                rotZ = -0.1f;
            }
            speed = rotZ;
            if(i >= 2) {
                if((++mb2_Work.unkA4 & 1) == 0) {
                    continue;
                }
            }
            if(i < 2) {
                no = 0;
            } else {
                no = 1;
            }
            col = colRand;
            colP = &col;
            MB2_SplashEffCreateRandX(&pos, colP, 1, no);
        }
    }
    if(mb2_Work.objMdlId[3] != -1) {
        if(mb2_Work.unkAC > 10) {
            MBMotionTimeGet(mb2_Work.objMdlId[3]) < 10;
        }
        mb2_Work.unkAC = MBMotionTimeGet(mb2_Work.objMdlId[3]);
    }
    if(MBMotionSpeedGet(mb2_Work.objMdlId2[6]) > 0 && MBMotionEndCheck(mb2_Work.objMdlId2[6])) {
        MBMotionSpeedSet(mb2_Work.objMdlId2[6], 0);
        MBMotionTimeSet(mb2_Work.objMdlId2[6], 0);
    }
    if(MBMotionSpeedGet(mb2_Work.objMdlId2[7]) > 0 && MBMotionEndCheck(mb2_Work.objMdlId2[7])) {
        MBMotionSpeedSet(mb2_Work.objMdlId2[7], 0);
        MBMotionTimeSet(mb2_Work.objMdlId2[7], 0);
    }
}

/* 110 instructions */
static void MB2_LightSet(void)
{
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(255, 255, 255);
    mb2_Work.lightPos.x = -3700;
    mb2_Work.lightPos.y = 18100;
    mb2_Work.lightPos.z = 21300;
    mb2_Work.lightTarget.x = 3700;
    mb2_Work.lightTarget.y = -18100;
    mb2_Work.lightTarget.z = -21300;
    mb2_Work.lightR = 255;
    mb2_Work.lightG = 255;
    mb2_Work.lightB = 255;
    mb2_Work.lightId = Hu3DGLightCreate(mb2_Work.lightPos.x, mb2_Work.lightPos.y, mb2_Work.lightPos.z,
                                        mb2_Work.lightTarget.x, mb2_Work.lightTarget.y, mb2_Work.lightTarget.z,
                                        mb2_Work.lightR, mb2_Work.lightG, mb2_Work.lightB);
    Hu3DGLightInfinitytSet(mb2_Work.lightId);
}

/* 1 instructions */
static void MB2_LightReset(void)
{
}

/* 57 instructions
 *
 * MASUHATENAHOOK returns int and this has no `return` -- nothing loads r3.
 */
static int MB2Ev_MasuHatena(int playerNo)
{
    s16 masuId;
    MASU *masu;
    int no;
    float decay;
    u32 flag;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    if(flag & MASU_FLAG_BIT_MULTI(4, 3)) {
        no = (flag & MASU_FLAG_BIT_MULTI(4, 3)) >> 4;
        switch(no) {
        case 1:
            MB2Ev_Thunder(playerNo);
            break;

        case 2:
            MB2Ev_Rain(playerNo);
            break;

        case 3:
            MB2Ev_Zen2(playerNo);
            break;

        case 4:
            MB2Ev_Zen4(playerNo);
            break;
        }
    }
    if(flag & MASU_FLAG_BIT_MULTI(7, 3)) {
        no = (flag & MASU_FLAG_BIT_MULTI(7, 3)) >> 7;
        MB2Ev_WindGuru2(no, playerNo);
    }
}

/* 1 instructions */
static void MB2_Stub(void)
{
}

/* 1 instructions */
static int MB2Ev_MasuWalkPre(int playerNo)
{
}

/* 73 instructions */
static int MB2Ev_MasuWalkPost(int playerNo)
{
    s16 masuId;
    int no;
    MASU *masu;
    u32 flag;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    if(flag & MASU_FLAG_BIT(12)) {
        HuAudFXPlay(1487);
        MBMotionTimeSet(mb2_Work.objMdlId2[6], 0);
        MBMotionSpeedSet(mb2_Work.objMdlId2[6], 1);
    }
    if(flag & MASU_FLAG_BIT(13)) {
        HuAudFXPlay(1487);
        MBMotionTimeSet(mb2_Work.objMdlId2[7], 0);
        MBMotionSpeedSet(mb2_Work.objMdlId2[7], 1);
    }
    if(flag & 0xF) {
        no = flag & 0xF;
        MB2Ev_Rainbow(no, playerNo);
    }
    return 0;
}

/* 75 instructions
 *
 * The board's MASUPATHCHECKHOOK. A space whose low flag nibble is set has a
 * rainbow leading off it; the destination is offered as an extra link, but
 * only to a player with five coins or fewer -- unless endF overrides.
 */
static int MB2_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    int endMasuId;
    int i;
    MASU *masu;
    int num;
    int playerNo;

    if(flag & 0xF) {
        endMasuId = MB2_RainbowMasuNoEndGet(id);
        if(endMasuId == -1) {
            return -1;
        }
        masu = MBMasuGet(MASU_LAYER_DEFAULT, id);
        for(i=0, num=0; i<masu->linkNum; i++) {
            if((MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & (MBBranchFlagGet()|(MASU_FLAG_BLOCKL|MASU_FLAG_BLOCKR))) == 0) {
                linkTbl[num] = masu->linkTbl[i];
                num++;
            }
        }
        playerNo = GwSystem.turnPlayerNo;
        if(playerNo < 0) {
            playerNo = 0;
        }
        if(MBPlayerCoinGet(playerNo) <= 5 || endF) {
            linkTbl[num] = endMasuId;
            num++;
        }
        return num;
    }
    return -1;
}

/* 1134 instructions
 *
 * The rainbow bridge. Five coins buys a walk along one of five arcs to the
 * space MB2_RainbowMasuNoEndGet names, trailing coin sparkles the whole way.
 * `no` 9 is the free one -- no window, no charge.
 *
 * Three locals here are written and never read: the MASU pointer, the total
 * arc length in frames, and the outer loop counter copied into a slot of its
 * own. All three are the disc's.
 */
static int MB2Ev_Rainbow(int no, int playerNo)
{
    int j;
    int choice;
    int frames;
    HuVecF *vtx;
    int i;
    int rbNo;
    int endMasuId;
    int rainbowNo;
    s16 masuId;
    int len2;
    int k;
    int len1;
    int num;
    float t;
    float mag;
    float targetAngle;
    float total;
    float angle;
    float decay;
    MASU *masu;
    int deadJ;
    int deadFrames;
    int retF;
    HuVecF *effPosP;
    HuVecF *effPosP2;
    HuVecF playerPos;
    HuVecF target;
    HuVecF vec;
    HuVecF rot;
    HuVecF effPos;
    HuVecF effPos2;

    retF = 0;
    if(no <= 0 || no > 10) {
        return 0;
    }
    if(no == 10) {
        return 0;
    }
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    rbNo = mb2ev_RainbowNoTbl[no];
    endMasuId = MB2_RainbowMasuNoEndGet(masuId);
    if(endMasuId == -1) {
        return 0;
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    MB2_RainbowObjInit();
    rainbowNo = MB2_RainbowObjCreate(mb2ev_RainbowVtxTbl[rbNo], mb2ev_RainbowVtxNumTbl[rbNo], mb2ev_RainbowRevF[rbNo]);
    MB2_RainbowObjAlphaSet(rainbowNo, 0);
    MB2_CoinEffInit();
    MBWalkNumDispSet(playerNo, FALSE);
    MBCameraFocusPlayerSet(playerNo);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    do {
        if(no == 9) {
            choice = 0;
            break;
        }
        MBAudFXPlay(757);
        MBWinCreateChoice(1, MESS_BOARD_W02_RAINBOW_ASK, 2, 0);
        MBTopWinAttrSet(HUWIN_ATTR_NOCANCEL);
        if(MBPlayerCoinGet(playerNo) < 5) {
            MBTopWinChoiceDisable(0);
        }
        if(GwPlayer[playerNo].comF) {
            num = (GwPlayer[playerNo].dif+1)*10;
            len1 = MB2_PathLenGet(masuId, num, 1);
            len2 = MB2_PathLenGet(endMasuId, num, 1);
            if(MBPlayerCoinGet(playerNo) < 5) {
                choice = 1;
            } else if(len1 == -1 && len2 == -1) {
                if(MB2_PathCheck(masuId)) {
                    choice = 1;
                } else if(MB2_PathCheck(endMasuId)) {
                    choice = 0;
                } else {
                    t = 0.6f+(0.4f*(GwPlayer[playerNo].dif/3.0f));
                    if(MB2_RandF() <= t) {
                        choice = 0;
                    } else {
                        choice = 1;
                    }
                }
            } else if(len1 != -1 && len2 != -1) {
                if(len2 < len1) {
                    choice = 0;
                } else {
                    choice = 1;
                }
            } else if(len2 != -1) {
                choice = 0;
            } else {
                choice = 1;
            }
            if(MBPlayerCoinGet(playerNo) >= 10) {
                if(choice == 0) {
                    MBComChoiceSetUp();
                } else {
                    MBComChoiceSetDown();
                }
            } else {
                MBComChoiceSetUp();
            }
        }
        MBTopWinWait();
        choice = MBWinLastChoiceGet();
        MBTopWinKill();
        switch(choice) {
        case 0:
        case 1:
            break;

        case 2:
            MBScrollExec(playerNo);
            MBStatusDispSetAll(TRUE);
            break;
        }
    } while(choice == 2);
    if(choice == 0) {
        if(no != 9) {
            MBCoinAddExec(playerNo, -5);
        }
        HuAudFXPlay(1480);
        for(j=0; j<30.0f; j++) {
            t = j/30.0f;
            MB2_RainbowObjAlphaSet(rainbowNo, 255*t);
            HuPrcVSleep();
        }
        MB2_RainbowObjAlphaSet(rainbowNo, 255);
        MBPlayerPosFixEvent(playerNo, endMasuId, FALSE);
        vtx = mb2ev_RainbowVtxTbl[rbNo];
        for(j=1, total=0; j<mb2ev_RainbowVtxNumTbl[rbNo]; j++) {
            PSVECSubtract(&vtx[j-1], &vtx[j], &vec);
            mag = PSVECMag(&vec);
            total += mag;
        }
        deadFrames = total/20;
        MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, HU3D_MOTATTR_LOOP);
        if(mb2ev_RainbowDirTbl[no] > 0) {
            MBPlayerPosGet(playerNo, &playerPos);
            target = vtx[0];
            PSVECSubtract(&target, &playerPos, &vec);
            mag = PSVECMag(&vec);
            frames = mag/20;
            for(j=0; j<frames; j++) {
                t = (float)j/(float)frames;
                PSVECSubtract(&target, &playerPos, &vec);
                PSVECScale(&vec, &vec, t);
                PSVECAdd(&playerPos, &vec, &vec);
                MBPlayerPosSetV(playerNo, &vec);
                PSVECSubtract(&target, &playerPos, &vec);
                MBPlayerRotGet(playerNo, &rot);
                rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
                MBPlayerRotSetV(playerNo, &rot);
                HuPrcVSleep();
            }
            MBPlayerPosSetV(playerNo, &target);
            for(j=0; j<mb2ev_RainbowVtxNumTbl[rbNo]-1; j++) {
                deadJ = j;
                k = j+1;
                MBPlayerPosGet(playerNo, &playerPos);
                target = vtx[k];
                PSVECSubtract(&target, &playerPos, &vec);
                mag = PSVECMag(&vec);
                frames = mag/20;
                MBPlayerRotGet(playerNo, &rot);
                angle = rot.y;
                PSVECSubtract(&target, &playerPos, &vec);
                targetAngle = 180*(atan2(vec.x, vec.z)/M_PI);
                for(i=0; i<frames; i++) {
                    t = (float)i/(float)frames;
                    PSVECSubtract(&target, &playerPos, &vec);
                    PSVECScale(&vec, &vec, t);
                    PSVECAdd(&playerPos, &vec, &vec);
                    MBPlayerPosSetV(playerNo, &vec);
                    rot.y = fn_1_BF54(t, angle, targetAngle);
                    MBPlayerRotSet(playerNo, 0, rot.y, 0);
                    MBPlayerPosGet(playerNo, &vec);
                    effPos = vec;
                    effPosP = &effPos;
                    decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
                    MB2_CoinEffCreateColRand(effPosP, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
                    HuPrcVSleep();
                }
                MBPlayerPosSetV(playerNo, &target);
                MBPlayerRotSet(playerNo, 0, targetAngle, 0);
            }
        } else {
            MBPlayerPosGet(playerNo, &playerPos);
            target = vtx[mb2ev_RainbowVtxNumTbl[rbNo]-1];
            PSVECSubtract(&target, &playerPos, &vec);
            mag = PSVECMag(&vec);
            frames = mag/20;
            for(j=0; j<frames; j++) {
                t = (float)j/(float)frames;
                PSVECSubtract(&target, &playerPos, &vec);
                PSVECScale(&vec, &vec, t);
                PSVECAdd(&playerPos, &vec, &vec);
                MBPlayerPosSetV(playerNo, &vec);
                PSVECSubtract(&target, &playerPos, &vec);
                MBPlayerRotGet(playerNo, &rot);
                rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
                MBPlayerRotSetV(playerNo, &rot);
                HuPrcVSleep();
            }
            MBPlayerPosSetV(playerNo, &target);
            for(j=mb2ev_RainbowVtxNumTbl[rbNo]-1; j>0; j--) {
                deadJ = j;
                k = j-1;
                MBPlayerPosGet(playerNo, &playerPos);
                target = vtx[k];
                PSVECSubtract(&target, &playerPos, &vec);
                mag = PSVECMag(&vec);
                frames = mag/20;
                MBPlayerRotGet(playerNo, &rot);
                angle = rot.y;
                PSVECSubtract(&target, &playerPos, &vec);
                targetAngle = 180*(atan2(vec.x, vec.z)/M_PI);
                for(i=0; i<frames; i++) {
                    t = (float)i/(float)frames;
                    PSVECSubtract(&target, &playerPos, &vec);
                    PSVECScale(&vec, &vec, t);
                    PSVECAdd(&playerPos, &vec, &vec);
                    MBPlayerPosSetV(playerNo, &vec);
                    rot.y = fn_1_BF54(t, angle, targetAngle);
                    MBPlayerRotSet(playerNo, 0, rot.y, 0);
                    MBPlayerPosGet(playerNo, &vec);
                    effPos2 = vec;
                    effPosP2 = &effPos2;
                    decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
                    MB2_CoinEffCreateColRand(effPosP2, 100*(0.3f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
                    HuPrcVSleep();
                }
                MBPlayerPosSetV(playerNo, &target);
                MBPlayerRotSet(playerNo, 0, targetAngle, 0);
            }
        }
        MBPlayerPosGet(playerNo, &playerPos);
        MBMasuPosGet(MASU_LAYER_DEFAULT, endMasuId, &target);
        PSVECSubtract(&target, &playerPos, &vec);
        mag = PSVECMag(&vec);
        frames = mag/20;
        for(j=0; j<frames; j++) {
            t = (float)j/(float)frames;
            PSVECSubtract(&target, &playerPos, &vec);
            PSVECScale(&vec, &vec, t);
            PSVECAdd(&playerPos, &vec, &vec);
            MBPlayerPosSetV(playerNo, &vec);
            PSVECSubtract(&target, &playerPos, &vec);
            MBPlayerRotGet(playerNo, &rot);
            rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
            MBPlayerRotSetV(playerNo, &rot);
            HuPrcVSleep();
        }
        MBPlayerPosSetV(playerNo, &target);
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        GwPlayer[playerNo].masuId = endMasuId;
        for(j=0; j<60.0f; j++) {
            t = j/60.0f;
            MB2_RainbowObjAlphaSet(rainbowNo, 255*(1-t));
            HuPrcVSleep();
        }
        MB2_RainbowObjAlphaSet(rainbowNo, 0);
        retF = 1;
    }
    MB2_RainbowObjClose();
    MB2_CoinEffClose();
    MBWalkNumDispSet(playerNo, TRUE);
    return retF;
}

/* 618 instructions
 *
 * The wind guru. The player is offered a ride; if they take it the guru's
 * blades are waited on until the right one comes round, the player is carried
 * to that blade on a 24-frame arc, spun with it for `saveNo` quarter-turns and
 * dropped on the space MB2_WindGuru2MasuNoGet picks.
 *
 * `startTime` in the second half is assigned and never read -- the disc's.
 */
static void MB2Ev_WindGuru2(int no, int playerNo)
{
    int j;
    int i;
    int masuId2;
    s16 masuId;
    MASU *masu;
    int choice;
    int len2;
    int linkNum;
    int len1;
    int saveNo;
    int num;
    float target;
    float t;
    float step;
    float time;
    float startTime;
    float speed;
    float endTime;
    HuVecF playerPos;
    HuVecF hookPos;
    HuVecF pos;
    HuVecF rot;
    Mtx mtx;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(no <= 0 || no > 4) {
        return;
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    MBWalkNumDispSet(playerNo, FALSE);
    MBCameraFocusPlayerSet(playerNo);
    MBPlayerRotateStart(playerNo, mb2ev_WindGuru2RotTbl[no], 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    do {
        for(j=0, linkNum=0; j<masu->linkNum; j++) {
            if((MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[j]) & (MBBranchFlagGet()|(MASU_FLAG_BLOCKL|MASU_FLAG_BLOCKR))) == 0) {
                linkNum++;
            }
        }
        if(linkNum <= 0) {
            choice = 0;
            break;
        }
        MBAudFXPlay(757);
        MBWinCreateChoice(1, MESS_BOARD_W02_WINDGURU_ASK, 2, 0);
        MBTopWinAttrSet(HUWIN_ATTR_NOCANCEL);
        if(GwPlayer[playerNo].comF) {
            masuId2 = MB2_WindGuru2MasuNoGet(masuId, -1);
            num = (GwPlayer[playerNo].dif+1)*10;
            len1 = MB2_PathLenGet(masuId, num, 1);
            len2 = MB2_PathLenGet(masuId2, num, 1);
            if(len1 == -1 && len2 == -1) {
                if(MB2_PathCheck(masuId)) {
                    MBComChoiceSetDown();
                } else if(MB2_PathCheck(masuId2)) {
                    MBComChoiceSetUp();
                } else if(frand() & 1) {
                    MBComChoiceSetUp();
                } else {
                    MBComChoiceSetDown();
                }
            } else if(len1 != -1 && len2 != -1) {
                if(len2 < len1) {
                    MBComChoiceSetUp();
                } else {
                    MBComChoiceSetDown();
                }
            } else if(len2 != -1) {
                MBComChoiceSetUp();
            } else {
                MBComChoiceSetDown();
            }
        }
        MBTopWinWait();
        choice = MBWinLastChoiceGet();
        MBTopWinKill();
        switch(choice) {
        case 0:
        case 1:
            break;

        case 2:
            MBScrollExec(playerNo);
            MBStatusDispSetAll(TRUE);
            break;
        }
    } while(choice == 2);
    if(choice == 0) {
        saveNo = mb2_SaveWorkP[0];
        mb2_SaveWorkP[0] = ((frand() & 0x7FFF)%3)+1;
        time = MBMotionTimeGet(mb2_Work.objMdlId[4]);
        startTime = time;
        step = 0.25f*MBMotionMaxTimeGet(mb2_Work.objMdlId[4]);
        for(i=0; i<4; i++) {
            if(time < i*step) {
                break;
            }
        }
        if(i >= 4) {
            i = 0;
            target = 4*step;
        } else {
            target = i*step;
        }
        do {
            HuPrcVSleep();
            time = MBMotionTimeGet(mb2_Work.objMdlId[4]);
        } while(time < target && time >= startTime);
        i = no-i;
        if(i < 1) {
            i += 4;
        }
        MBPlayerPosGet(playerNo, &playerPos);
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(j=0; j<24.0f; j++) {
            t = j/24.0f;
            Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId[4]), mb2ev_WindGuru2HookTbl[i], mtx);
            hookPos.x = mtx[0][3];
            hookPos.y = mtx[1][3];
            hookPos.z = mtx[2][3];
            PSVECSubtract(&hookPos, &playerPos, &pos);
            PSVECScale(&pos, &pos, t);
            PSVECAdd(&playerPos, &pos, &pos);
            pos.y += 300*HuSin(180*t);
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotGet(playerNo, &rot);
            PSVECSubtract(&hookPos, &playerPos, &pos);
            rot.y = 180*(atan2(pos.x, pos.z)/M_PI);
            MBPlayerRotSetV(playerNo, &rot);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        startTime = MBMotionTimeGet(mb2_Work.objMdlId[4]);
        step = 0.25f*MBMotionMaxTimeGet(mb2_Work.objMdlId[4]);
        endTime = step*saveNo;
        speed = MBMotionSpeedGet(mb2_Work.objMdlId[4]);
        target = 24*speed;
        while(target < endTime) {
            Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId[4]), mb2ev_WindGuru2HookTbl[i], mtx);
            hookPos.x = mtx[0][3];
            hookPos.y = mtx[1][3];
            hookPos.z = mtx[2][3];
            MBPlayerPosSetV(playerNo, &hookPos);
            HuPrcVSleep();
            target += speed;
        }
        masuId2 = MB2_WindGuru2MasuNoGet(masuId, saveNo);
        MBPlayerPosFixEvent(playerNo, masuId2, FALSE);
        MBPlayerPosGet(playerNo, &playerPos);
        MBMasuPosGet(MASU_LAYER_DEFAULT, masuId2, &hookPos);
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(j=0; j<24.0f; j++) {
            t = j/24.0f;
            PSVECSubtract(&hookPos, &playerPos, &pos);
            PSVECScale(&pos, &pos, t);
            PSVECAdd(&playerPos, &pos, &pos);
            pos.y += 300*HuSin(180*t);
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotGet(playerNo, &rot);
            PSVECSubtract(&hookPos, &playerPos, &pos);
            rot.y = 180*(atan2(pos.x, pos.z)/M_PI);
            MBPlayerRotSetV(playerNo, &rot);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        GwPlayer[playerNo].masuId = masuId2;
    }
    MBWalkNumDispSet(playerNo, TRUE);
}

/* 1622 instructions
 *
 * The dynamo. Ten seconds of mashing A charges `power` (0.02 a press, bleeding
 * 0.0015 a frame); the player's motion, the dynamo's spin speed and the SE's
 * pitch all follow it, and at the end `power` times the player's free capsule
 * slots come flying out on a Bezier.
 *
 * Four locals here are written and never read -- the MASU pointer, its flag
 * word, the camera's zoom and one loop counter. All four are the disc's.
 */
static void MB2Ev_Thunder(int playerNo)
{
    int i;
    int j;
    OMOBJ *obj;
    MBMODELID capMdlId;
    int seId;
    MBMODELID guideId;
    int motNo;
    HSFOBJECT *objP;
    s16 getNum;
    s16 capsuleNo;
    int comTimer;
    MBCAMERA *camera;
    s16 capNum;
    int fxTimer;
    int capMax;
    float t;
    float power;
    float scale;
    double value;
    s16 masuId;
    s16 choice;
    HU3DMODEL *modelP;
    MASU *masu;
    u32 flag;
    int mdlId;
    float camZoom;
    HuVecF playerPos;
    HuVecF dynamoPos;
    HuVecF pos;
    HuVecF camRot;
    HuVecF camRot2;
    HuVecF guidePos;
    HuVecF capStart;
    HuVecF capMid;
    HuVecF capEnd;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    MB2_CoinInit();
    MB2_CoinEffInit();
    camera = MBCameraGet();
    camRot = camera->rot;
    camZoom = camera->zoom;
    MBPlayerRotateStart(playerNo, 180, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBDataAsyncWait(MBDataDirReadAsync(DATA_guide));
    MBPlayerPosGet(playerNo, &playerPos);
    guidePos = playerPos;
    guidePos.z -= 400;
    guidePos.y += 200;
    guideId = MBGuideCreateFlag(2, &guidePos, FALSE, TRUE, TRUE, FALSE);
    MBModelLayerSet(guideId, 2);
    HuDataDirClose(DATA_guide);
    capMax = MBPlayerCapsuleMaxGet();
    if(MBPlayerCapsuleNumGet(playerNo) < capMax) {
        MBAudFXPlay(757);
        MBWinCreateChoice(1, MESS_BOARD_W02_THUNDER_ASK, 2, 0);
        MBTopWinAttrSet(HUWIN_ATTR_NOCANCEL);
        if(GwPlayer[playerNo].comF) {
            MBComChoiceSetUp();
        }
        MBTopWinWait();
        choice = MBWinLastChoiceGet();
        MBTopWinKill();
    } else {
        MBWinCreate(2, MESS_BOARD_W02_THUNDER_FULL, 2);
        MBTopWinWait();
        MBTopWinKill();
        choice = 1;
    }
    if(choice == 1) {
        MB2_CoinClose();
        MB2_CoinEffClose();
        MBGuideEnd(guideId);
        guideId = -1;
        return;
    }
    MBPlayerPosGet(playerNo, &playerPos);
    dynamoPos = mb2ev_DynamoPos;
    mb2_Work.unk98 = 0;
    camRot2.x = camRot.x;
    camRot2.y = camRot.y-30;
    camRot2.z = camRot.z;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), &camRot2, NULL, 3000, -1, 42);
    MBCameraMotionWait();
    for(i=0; i<60.0f; i++) {
        t = i/60.0f;
        guidePos.y = 200+playerPos.y+3*(100*HuSin(90*t));
        MBGuideMdlPosSetV(guideId, &guidePos);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=24.0f; i++) {
        t = i/24.0f;
        PSVECSubtract(&dynamoPos, &playerPos, &pos);
        PSVECScale(&pos, &pos, t);
        PSVECAdd(&playerPos, &pos, &pos);
        pos.y += 200*HuSin(180*t);
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    motNo = 1;
    MBWinCreate(2, MESS_BOARD_W02_THUNDER_INST, 2);
    MBTopWinWait();
    MBTopWinKill();
    MBWinCreateHelp(MESS_BOARD_W02_THUNDER_HELP);
    mdlId = MBModelIdGet(mb2_Work.objMdlId2[2]);
    modelP = &Hu3DData[mdlId];
    objP = MB2_ModelObjPtrGet(modelP, "dynamo");
    seId = -1;
    fxTimer = 0;
    MBAddObj(32768, 0, 0, MB2_TimerObjUpdate);
    mb2ev_TimerObj = 600;
    mb2ev_TimerValue = 600;
    for(i=0, comTimer=0; mb2ev_TimerObj > 0; i++) {
        if(GwPlayer[playerNo].comF) {
            comTimer--;
            if(comTimer <= 0) {
                comTimer = (8-(GwPlayer[playerNo].dif*2))+(0.01f*(60*MB2_RandF()));
                if(comTimer < 2) {
                    comTimer = 2;
                }
                power += 0.02f;
            }
        } else if(HuPadBtnDown[GwPlayer[playerNo].padNo] & PAD_BUTTON_A) {
            power += 0.02f;
        }
        if(power > 0) {
            power -= 0.0015f;
            if(power < 0) {
                power = 0;
            }
        }
        if(power > 1) {
            power = 1;
        }
        if(seId == -1 && power > 0) {
            seId = HuAudFXPlay(1483);
        } else if(seId != -1 && power <= 0) {
            HuAudFXStop(seId);
            seId = -1;
        } else if(seId != -1) {
            HuAudFXPitchSet(seId, 8191*power);
        }
        MBMotionSpeedSet(mb2_Work.objMdlId2[4], 0.5f+power);
        if(power > 0) {
            fxTimer--;
            if(fxTimer <= 0) {
                fxTimer = (int)(20*(1-power))+3;
                HuAudFXPlay(1482);
            }
        }
        if(power > 0.5f) {
            scale = 1;
        } else {
            scale = 2*power;
        }
        if(objP != NULL) {
            if((objP->mesh.base.rot.x += 10*scale) > 360) {
                objP->mesh.base.rot.x -= 360;
            }
        }
        if(MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) == -1) {
            if(scale <= 0) {
                if(motNo != 1) {
                    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 24, HU3D_MOTATTR_LOOP);
                    motNo = 1;
                }
            } else if(scale < 0.3f) {
                if(motNo != 2) {
                    MBPlayerMotionNoShiftSet(playerNo, 2, 0, 40, HU3D_MOTATTR_LOOP);
                    motNo = 2;
                }
                scale = 5*power;
                if(scale < 0.5f) {
                    scale = 0.5f;
                } else if(scale > 1) {
                    scale = 1;
                }
                MBPlayerMotionSpeedSet(playerNo, scale);
            } else {
                if(motNo != 3) {
                    MBPlayerMotionNoShiftSet(playerNo, 3, 0, 40, HU3D_MOTATTR_LOOP);
                    motNo = 3;
                }
                scale = 5*(power-0.3f);
                if(scale < 0.75f) {
                    scale = 0.75f;
                } else if(scale > 1) {
                    scale = 1;
                }
                MBPlayerMotionSpeedSet(playerNo, scale);
            }
        }
        MBMotionTimeSet(mb2_Work.objMdlId2[3], power*MBMotionMaxTimeGet(mb2_Work.objMdlId2[3]));
        HuPrcVSleep();
        if(power >= 1) {
            break;
        }
    }
    MBTopWinKill();
    mb2ev_TimerObj = 0;
    if(seId != -1) {
        HuAudFXStop(seId);
    }
    if(power > 0.85) {
        power = 1;
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    capMax = MBPlayerCapsuleMaxGet();
    capNum = capMax-MBPlayerCapsuleNumGet(playerNo);
    getNum = power*capNum;
    if(power > 0.9f) {
        getNum = capNum;
    }
    if(getNum > capNum) {
        getNum = capNum;
    }
    if(getNum > 0) {
        MBWinCreate(2, MESS_BOARD_W02_THUNDER_WIN, 2);
        MBTopWinWait();
        MBTopWinKill();
        mb2_Work.unk98 = 1;
        HuAudFXPlay(1489);
        MBMotionSpeedSet(mb2_Work.objMdlId2[1], 1);
        do {
            HuPrcVSleep();
        } while(!MBMotionEndCheck(mb2_Work.objMdlId2[1]));
        HuPrcSleep(30);
        for(i=0; i<getNum; i++) {
            MBPlayerPosGet(playerNo, &capEnd);
            capEnd.y += 250;
            capStart = mb2ev_BiriQCapsulePos;
            PSVECSubtract(&capEnd, &capStart, &capMid);
            PSVECScale(&capMid, &capMid, 1.2f);
            PSVECAdd(&capMid, &capStart, &capMid);
            if(frand() & 1) {
                capMid.x += 200;
            } else {
                capMid.x -= 200;
            }
            capMid.y += 100*(1+MB2_RandF());
            do {
                capsuleNo = MBCapsuleNextGet(-1);
            } while(capsuleNo == CAPSULE_KOOPA || capsuleNo == CAPSULE_MIRACLE);
            capMdlId = MBModelCreate(MBCapsuleMdlGet(capsuleNo), NULL, FALSE);
            MBModelAttrSet(capMdlId, HU3D_MOTATTR_LOOP);
            MBModelLayerSet(capMdlId, 2);
            HuAudFXPlay(868);
            for(j=0; j<=60.0f; j++) {
                t = j/60.0f;
                scale = HuSin(90*t);
                MB2_BezierCalcV(t, (float *)&capStart, (float *)&capMid, (float *)&capEnd, (float *)&pos);
                MBModelPosSetV(capMdlId, &pos);
                MBModelScaleSet(capMdlId, scale, scale, scale);
                HuPrcVSleep();
            }
            for(j=0; j<=120.0f; j++) {
                t = j/120.0f;
                pos.y = capEnd.y+0.2*(100*HuSin(720*t));
                MBModelPosSetV(capMdlId, &pos);
                HuPrcVSleep();
            }
            capStart = capEnd;
            capEnd.y -= 150;
            HuAudFXPlay(796);
            for(j=0; j<=60.0f; j++) {
                t = j/60.0f;
                scale = HuCos(90*t);
                PSVECSubtract(&capEnd, &capStart, &pos);
                PSVECScale(&pos, &pos, t);
                PSVECAdd(&pos, &capStart, &pos);
                value = HuSin(180*t);
                pos.x += 200*(HuSin(720*t)*value);
                value = HuSin(180*t);
                pos.z += 200*(HuCos(720*t)*value);
                MBModelPosSetV(capMdlId, &pos);
                MBModelScaleSet(capMdlId, scale, scale, scale);
                HuPrcVSleep();
            }
            MBModelDispSet(capMdlId, FALSE);
            MBPlayerCapsuleAdd(playerNo, capsuleNo);
            MBWinCreate(2, MESS_BOARD_W02_THUNDER_GET, -1);
            MBTopWinInsertMesSet(MBCapsuleMesGet(capsuleNo), 0);
            MBTopWinWait();
            MBTopWinKill();
            MBModelKill(capMdlId);
        }
        MBMotionSpeedSet(mb2_Work.objMdlId2[1], -1);
        j = 0;
        do {
            HuPrcVSleep();
        } while(MBMotionTimeGet(mb2_Work.objMdlId2[1]) > 0);
        HuAudFXPlay(1494);
        MBPlayerRotateStart(playerNo, 0, 15);
        while(!MBPlayerRotateCheck(playerNo)) {
            HuPrcVSleep();
        }
        MBPlayerWinLoseVoicePlay(playerNo, 12, 504);
        MBPlayerMotionNoShiftSet(playerNo, 12, 0, 8, 0);
    } else {
        MBWinCreate(2, MESS_BOARD_W02_THUNDER_LOSE, 2);
        MBTopWinWait();
        MBTopWinKill();
        MBPlayerRotateStart(playerNo, 0, 15);
        while(!MBPlayerRotateCheck(playerNo)) {
            HuPrcVSleep();
        }
        MBPlayerWinLoseVoicePlay(playerNo, 13, 512);
        MBPlayerMotionNoShiftSet(playerNo, 13, 0, 8, 0);
    }
    obj = MBAddObj(32768, 0, 0, MB2_DentyuObjFlash);
    obj->work[0] = 1;
    obj->work[1] = 0;
    obj->work[2] = 0;
    obj->trans.x = power;
    do {
        HuPrcVSleep();
    } while(!MBPlayerMotionEndCheck(playerNo) || MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
    MBMotionTimeSet(mb2_Work.objMdlId2[3], power*MBMotionMaxTimeGet(mb2_Work.objMdlId2[3]));
    obj->work[0] = 0;
    MBMotionSpeedSet(mb2_Work.objMdlId2[4], 0.5f);
    MBMotionSpeedSet(mb2_Work.objMdlId2[1], 0);
    MBMotionSpeedSet(mb2_Work.objMdlId2[3], 0);
    MBMotionTimeSet(mb2_Work.objMdlId2[3], 0);
    for(i=0; i<30.0f; i++) {
        t = i/30.0f;
        MBMotionTimeSet(mb2_Work.objMdlId2[1], (1-t)*MBMotionMaxTimeGet(mb2_Work.objMdlId2[1]));
    }
    MBMotionTimeSet(mb2_Work.objMdlId2[1], 0);
    MBGuideEnd(guideId);
    guideId = -1;
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=24.0f; i++) {
        t = i/24.0f;
        PSVECSubtract(&playerPos, &dynamoPos, &pos);
        PSVECScale(&pos, &pos, t);
        PSVECAdd(&dynamoPos, &pos, &pos);
        pos.y += 200*HuSin(180*t);
        MBPlayerPosSetV(playerNo, &pos);
        MBPlayerRotSet(playerNo, 0, 0, 0);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    mb2_Work.unk98 = 1;
    camRot2.x = camRot.x;
    camRot2.y = camRot.y;
    camRot2.z = camRot.z;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), &camRot2, NULL, 3000, -1, 42);
    MBCameraMotionWait();
    MB2_CoinClose();
    MB2_CoinEffClose();
    MB3MiracleGetExec(playerNo);
}

/* 1759 instructions
 *
 * The flood. The water gate opens, nine pieces of scenery are cut loose and
 * swim off down the board carrying whatever spaces and players stand on them,
 * and every player the water catches is washed back to the start space.
 *
 * Two locals here are written and never read: the landing space, and a MASU
 * pointer taken at the top. Both are the disc's, as is the restore loop at the
 * bottom, which walks all ten records without the NULL test the setup loop
 * uses.
 */
static void MB2Ev_Rain(int playerNo)
{
    int i;
    int j;
    int k;
    int num;
    int swimNum;
    int masuNum;
    int carriedNum;
    int no;
    int endF;
    int doneF;
    int fxId;
    int motId;
    int mdlId2;
    int mdlId;
    s16 masuId;
    MASU *masu;
    HU3DMODEL *modelP;
    OMOBJ *splashObj;
    MB2_RAINOBJ *objP;
    MB2_RAINPLAYER *swimP;
    MB2_RAINPLAYER *carriedP;
    GXColor *colP;
    GXColor col;
    GXColor colRand;
    float t;
    float waterY;
    float dist;
    float y;
    float rate;
    HuVecF playerPos;
    HuVecF vec2;
    HuVecF startPos;
    HuVecF vec;
    HuVecF ofs;
    MB2_RAINMASU masuTbl[3];
    Mtx mtx;
    MB2_RAINPLAYER swim[4];
    MB2_RAINPLAYER carried[4];
    MB2_RAINOBJ obj[10];

    waterY = 1190;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    MBPlayerPosGet(playerNo, &playerPos);
    startPos = playerPos;
    objP = obj;
    for(i=0, num=0; i<10; i++, objP++) {
        objP->mdlId = mb2_Work.objMdlId[1];
        mdlId2 = MBModelIdGet(objP->mdlId);
        modelP = &Hu3DData[mdlId2];
        objP->objP = MB2_ModelObjPtrGet(modelP, mb2ev_RainObjTbl[i]);
        if(objP->objP == NULL) {
            continue;
        }
        objP->save = *(MB2_RAINOBJSAVE *)objP->objP;
        objP->masuId = -1;
        if(mb2ev_RainNoTbl[i] > 0) {
            for(j=0; j<=MBMasuNumGet(MASU_LAYER_DEFAULT); j++) {
                if(MBMasuFlagGet(MASU_LAYER_DEFAULT, j) & MASU_FLAG_BIT_MULTI(10, 2)) {
                    no = (MBMasuFlagGet(MASU_LAYER_DEFAULT, j) & MASU_FLAG_BIT_MULTI(10, 2))>>10;
                    if(no == mb2ev_RainNoTbl[i]) {
                        objP->masuId = j;
                    }
                }
            }
        }
        objP->step = 0;
        objP->stepMax = 0;
        Hu3DModelObjMtxGet(MBModelIdGet(objP->mdlId), mb2ev_RainObjTbl[i], mtx);
        objP->pos.x = mtx[0][3];
        objP->pos.y = mtx[1][3];
        objP->pos.z = mtx[2][3];
        objP->rot.x = objP->rot.y = objP->rot.z = 0;
        PSVECSubtract(&mb2ev_RainSwimMidPos, &objP->pos, &objP->dir1);
        PSVECSubtract(&mb2ev_RainSwimRightPos, &objP->pos, &objP->dir2);
        objP->ofsY = objP->pos.y-waterY;
        objP->speed = 0;
        PSVECSubtract(&mb2ev_RainSwimMidPos, &objP->pos, &vec);
        dist = sqrtf((vec.x*vec.x)+(vec.z*vec.z));
        objP->dist = dist;
        objP->step = 0;
        objP->stepMax = dist/5;
        objP->swimLen = mb2ev_RainSwimLenTbl[i];
        if(i >= 1 && i <= 3) {
            objP->bezierF = 1;
        } else {
            objP->bezierF = 0;
        }
        if(objP->masuId == -1) {
            continue;
        }
        MBMasuPosGet(MASU_LAYER_DEFAULT, objP->masuId, &objP->masuPos);
        PSVECSubtract(&objP->masuPos, &objP->pos, &objP->masuOfs);
        for(j=0, objP->playerNum=0; j<4; j++) {
            if(objP->masuId == GwPlayer[j].masuId) {
                objP->playerNo[objP->playerNum] = j;
                MBPlayerPosGet(j, &vec);
                PSVECSubtract(&vec, &objP->pos, &objP->playerOfs[objP->playerNum]);
                objP->playerNum++;
            }
        }
        num += objP->playerNum;
    }
    swimP = swim;
    for(i=0, swimNum=0; i<4; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, GwPlayer[i].masuId) & MASU_FLAG_BIT(15)) {
            swimP->playerNo = i;
            swimP->motId = MBPlayerMotionCreate(i, CHARMOT_HSF_c000m1_354);
            if(masuId == GwPlayer[i].masuId) {
                swimP->sideF = 0;
            } else {
                swimP->sideF = 1;
            }
            MBPlayerPosGet(i, &swimP->pos);
            MBPlayerRotGet(i, &swimP->rot);
            swimP->savePos = swimP->pos;
            PSVECSubtract(&mb2ev_RainSwimMidPos, &swimP->pos, &vec);
            dist = sqrtf((vec.x*vec.x)+(vec.z*vec.z));
            swimP->dist = dist;
            swimP->step = 0;
            swimP->stepMax = dist/5;
            swimP++;
            swimNum++;
        }
    }
    for(i=1, masuNum=0; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & MASU_FLAG_BIT(15) && masuNum < 3) {
            masuTbl[masuNum].masuId = i;
            MBMasuPosGet(MASU_LAYER_DEFAULT, i, &masuTbl[masuNum].pos);
            masuNum++;
        }
    }
    motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_325);
    mdlId = MBModelCreate(BOARD_HSF_coin, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBPlayerPosGet(playerNo, &vec);
    MBModelPosSetV(mdlId, &vec);
    MBCameraModelViewSet(mdlId, NULL, NULL, 3000, -1, 10);
    MBCameraMotionWait();
    mb2_Work.unkA0 = 0;
    for(i=0; i<60.0f; i++) {
        t = 1-(i/60.0f);
        MBModelScaleSet(mb2_Work.objMdlId2[9], t, 1, 1);
        MBModelScaleSet(mb2_Work.objMdlId2[10], t, 1, t);
        HuPrcVSleep();
    }
    MBModelDispSet(mb2_Work.objMdlId2[9], FALSE);
    MBModelDispSet(mb2_Work.objMdlId2[10], FALSE);
    PSVECSubtract(&startPos, &vec, &vec2);
    MBPlayerRotateStart(playerNo, 45, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, motId, 0, 8, 0);
    HuPrcSleep(60);
    HuAudFXPlay(1490);
    for(j=0; j<swimNum; j++) {
        MBPlayerMotionNoSet(swim[j].playerNo, 9, 0);
        omVibrate(swim[j].playerNo, 12, 6, 6);
    }
    fxId = HuAudFXPlay(1484);
    for(i=0; i<60.0f; i++) {
        t = i/60.0f;
        obj[0].objP->mesh.base.pos.y = obj[0].save.base.pos.y-(600*t);
        swimP = swim;
        for(j=0; j<swimNum; j++, swimP++) {
            y = swimP->pos.y-(600*t);
            if(y <= waterY-50) {
                if(swimP->savePos.y > waterY-50) {
                    MBPlayerMotionNoShiftSet(swimP->playerNo, swimP->motId, 0, 8, HU3D_MOTATTR_LOOP);
                    for(k=0; k<16; k++) {
                        vec.x = swimP->pos.x+(1.5f*(100*(0.5f-MB2_RandF())));
                        vec.z = swimP->pos.z+(1.5f*(100*(0.5f*MB2_RandF())));
                        vec.y = waterY-50;
                        rate = k&1;
                        colRand.r = 230+rate;
                        colRand.g = 230+rate;
                        colRand.b = 240+rate;
                        colRand.a = 32+(32*MB2_RandF());
                        col = colRand;
                        colP = &col;
                        MB2_SplashEffCreateRandX(&vec, colP, 1, rate);
                    }
                    splashObj = MBAddObj(32768, 0, 0, MB2_WaterSplashUpdate);
                    splashObj->work[0] = 18;
                    splashObj->trans.x = swimP->pos.x;
                    splashObj->trans.y = waterY-50;
                    splashObj->trans.z = swimP->pos.z;
                }
                y = waterY-50;
            }
            MBPlayerPosSet(swimP->playerNo, swimP->pos.x, y, swimP->pos.z);
            swimP->savePos.y = y;
        }
        for(j=0; j<masuNum; j++) {
            y = masuTbl[j].pos.y-(600*t);
            PSMTXIdentity(mtx);
            mtx[0][3] = masuTbl[j].pos.x;
            mtx[1][3] = y;
            mtx[2][3] = masuTbl[j].pos.z;
            MBMasuMtxSet(masuTbl[j].masuId, mtx);
        }
        HuPrcVSleep();
    }
    if(fxId != -1) {
        HuAudFXStop(fxId);
    }
    MBMasuPlayerLightSet(playerNo, FALSE);
    HuAudFXPlay(1492);
    HuAudFXPlay(1491);
    endF = doneF = 0;
    do {
        if(waterY > 1040) {
            waterY -= 0.5f;
        } else {
            waterY = 1040;
        }
        MBModelPosSet(mb2_Work.objMdlId2[8], 0, waterY-1190, 0);
        i = 0;
        swimP = swim;
        for(; i<swimNum; i++, swimP++) {
            t = (float)++swimP->step/(float)swimP->stepMax;
            if(t > 1) {
                t = 1;
            }
            t = HuSin(90*t);
            if(swimP->sideF == 0) {
                PSVECSubtract(&mb2ev_RainSwimMidPos, &swimP->pos, &vec);
                PSVECScale(&vec, &vec, t);
                PSVECAdd(&swimP->pos, &vec, &vec);
            } else {
                MB2_BezierCalcV(t, (float *)&swimP->pos, (float *)&mb2ev_RainSwimLeftPos, (float *)&mb2ev_RainSwimMidPos, (float *)&vec);
            }
            vec.y = waterY-50;
            if(i == 0) {
                swimP->rot.y += 2;
            } else {
                swimP->rot.y -= 2;
            }
            MBPlayerPosSetV(swimP->playerNo, &vec);
            MBPlayerRotSetV(swimP->playerNo, &swimP->rot);
        }
        i = 0;
        swimP = swim;
        for(; i<swimNum; i++, swimP++) {
            if(swimP->step < swimP->stepMax) {
                break;
            }
        }
        if(i >= swimNum) {
            endF = 1;
        }
        i = 1;
        objP = &obj[1];
        for(; i<10; i++, objP++) {
            if(objP->objP == NULL) {
                continue;
            }
            if(++objP->step < objP->swimLen) {
                t = 0;
            } else {
                t = (float)(objP->step-objP->swimLen)/(float)objP->stepMax;
            }
            if(t > 1) {
                t = 1;
            }
            t = HuSin(90*t);
            if(objP->bezierF == 0) {
                PSVECScale(&objP->dir1, &vec, t);
            } else {
                MB2_BezierCalcV(t, (float *)&mb2ev_RainSwimDefPos, (float *)&objP->dir2, (float *)&objP->dir1, (float *)&vec);
            }
            vec.y = waterY-1190;
            objP->objP->mesh.base.pos.x = objP->save.base.pos.x+vec.x;
            objP->objP->mesh.base.pos.y = objP->save.base.pos.y+vec.y;
            objP->objP->mesh.base.pos.z = objP->save.base.pos.z+vec.z;
            if(objP->speed < 2) {
                objP->speed += 0.01f;
            }
            if(i == 0) {
                objP->rot.y += objP->speed;
            } else {
                objP->rot.y -= objP->speed;
            }
            objP->objP->mesh.base.rot.y = objP->save.base.rot.y+objP->rot.y;
            if(objP->masuId == -1) {
                continue;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(objP->mdlId), mb2ev_RainObjTbl[i], mtx);
            vec.x = mtx[0][3];
            vec.y = waterY+objP->ofsY;
            vec.z = mtx[2][3];
            PSVECAdd(&vec, &objP->masuOfs, &vec);
            PSMTXIdentity(mtx);
            mtx[0][3] = vec.x;
            mtx[1][3] = vec.y;
            mtx[2][3] = vec.z;
            MBMasuMtxSet(objP->masuId, mtx);
            for(j=0; j<objP->playerNum; j++) {
                Hu3DModelObjMtxGet(MBModelIdGet(objP->mdlId), mb2ev_RainObjTbl[i], mtx);
                vec.x = mtx[0][3];
                vec.y = waterY+objP->ofsY;
                vec.z = mtx[2][3];
                mtxRot(mtx, objP->rot.x, objP->rot.y, objP->rot.z);
                PSMTXMultVec(mtx, &objP->playerOfs[j], &ofs);
                PSVECAdd(&vec, &ofs, &vec);
                MBPlayerPosSetV(objP->playerNo[j], &vec);
                MBPlayerRotSetV(objP->playerNo[j], &objP->rot);
            }
        }
        i = 1;
        objP = &obj[1];
        for(; i<10; i++, objP++) {
            if((float)(objP->step-objP->swimLen) < (float)objP->stepMax) {
                break;
            }
        }
        if(i >= 10) {
            doneF = 1;
        }
        if(num <= 0) {
            doneF = 1;
        }
        HuPrcVSleep();
    } while(endF == 0 || doneF == 0);
    WipeColorSet(255, 255, 255);
    WipeCreate(2, 129, 1);
    WipeWait();
    MBMasuPlayerLightSet(playerNo, TRUE);
    carriedNum = 0;
    i = 0;
    swimP = swim;
    for(; i<swimNum; i++, swimP++) {
        if(carriedNum < 4) {
            carried[carriedNum].playerNo = swimP->playerNo;
            carriedNum++;
        }
    }
    i = 1;
    objP = &obj[1];
    for(; i<10; i++, objP++) {
        if(objP->masuId == -1) {
            continue;
        }
        for(j=0; j<objP->playerNum; j++) {
            if(carriedNum < 4) {
                carried[carriedNum].playerNo = objP->playerNo[j];
                carriedNum++;
            }
        }
    }
    mdlId2 = MBMasuFlagPosGet(MASU_LAYER_DEFAULT, MASU_FLAG_START, NULL);
    i = 0;
    carriedP = carried;
    for(; i<carriedNum; i++, carriedP++) {
        GwPlayer[carriedP->playerNo].masuId = mdlId2;
    }
    MBPlayerPosFixEvent(playerNo, mdlId2, TRUE);
    MBMasuPosGet(MASU_LAYER_DEFAULT, mdlId2, &vec);
    MBPlayerPosSetV(playerNo, &vec);
    i = 0;
    carriedP = carried;
    for(; i<carriedNum; i++, carriedP++) {
        MBPlayerPosGet(carriedP->playerNo, &carriedP->startPos);
        carriedP->pos.x = carriedP->startPos.x;
        carriedP->pos.y = (2000+carriedP->startPos.y)+(500.0f*i);
        carriedP->pos.z = carriedP->startPos.z;
        carriedP->vel.x = carriedP->vel.y = carriedP->vel.z = 0;
        MBPlayerRotSet(carriedP->playerNo, 0, 0, 0);
        carriedP->endF = 0;
    }
    MBCameraSkipSet(FALSE);
    MBCameraFocusMasuSet(mdlId2);
    MBCameraMotionWait();
    MBCameraSkipSet(TRUE);
    WipeCreate(1, 129, 30);
    do {
        i = 0;
        carriedP = carried;
        for(; i<carriedNum; i++, carriedP++) {
            if(carriedP->endF == 0) {
                PSVECAdd(&carriedP->pos, &carriedP->vel, &carriedP->pos);
                carriedP->vel.y -= 3.2666667f;
                if(carriedP->pos.y <= carriedP->startPos.y) {
                    MBPlayerMotionNoShiftSet(carriedP->playerNo, 6, 0, 8, HU3D_MOTATTR_LOOP);
                    carriedP->pos = carriedP->startPos;
                    carriedP->endF = 1;
                }
                MBPlayerPosSetV(carriedP->playerNo, &carriedP->pos);
            }
        }
        i = 0;
        carriedP = carried;
        for(; i<carriedNum; i++, carriedP++) {
            if(carriedP->endF == 0) {
                break;
            }
        }
        HuPrcVSleep();
    } while(i < carriedNum);
    WipeWait();
    for(i=0; i<60.0f; i++) {
        HuPrcVSleep();
    }
    i = 0;
    carriedP = carried;
    for(; i<carriedNum; i++, carriedP++) {
        MBPlayerMotionNoShiftSet(carriedP->playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    }
    for(i=0; i<60.0f; i++) {
        HuPrcVSleep();
    }
    mb2_Work.unkA0 = 1;
    MBModelPosSet(mb2_Work.objMdlId2[8], 0, 0, 0);
    MBModelScaleSet(mb2_Work.objMdlId2[9], 1, 1, 1);
    MBModelDispSet(mb2_Work.objMdlId2[9], TRUE);
    MBModelScaleSet(mb2_Work.objMdlId2[10], 1, 1, 1);
    MBModelDispSet(mb2_Work.objMdlId2[10], TRUE);
    objP = obj;
    for(i=0; i<10; i++, objP++) {
        *(MB2_RAINOBJSAVE *)objP->objP = objP->save;
    }
    for(i=0; i<masuNum; i++) {
        MBMasuMtxSet(masuTbl[i].masuId, NULL);
    }
    i = 1;
    objP = &obj[1];
    for(; i<10; i++, objP++) {
        if(objP->masuId != -1) {
            MBMasuMtxSet(objP->masuId, NULL);
        }
    }
    i = 0;
    swimP = swim;
    for(; i<swimNum; i++, swimP++) {
        if(swimP->motId != -1) {
            MBPlayerMotionKill(swimP->playerNo, swimP->motId);
        }
    }
    if(motId != -1) {
        MBPlayerMotionKill(playerNo, motId);
    }
    if(mdlId != -1) {
        MBModelKill(mdlId);
    }
}

/* 1786 instructions
 *
 * The three-way rainbow. A random set of three arcs is built over the board,
 * the player is lifted onto a pedestal, picks left/centre/right with the
 * stick, and is carried along that arc to whichever of three spaces
 * mb2ev_Zen2DestTbl names -- collecting the coins strewn along it.
 *
 * Two locals here are written and never read: the landing space's flag word
 * and an int zeroed just before the ride loop. Both are the disc's.
 */
static void MB2Ev_Zen2(int playerNo)
{
    int i;
    MB2_ZEN2DATA *data;
    MASU *masu2;
    int yajiNo;
    int no;
    int fxId;
    int vtxNum;
    int no2;
    s16 masuId;
    int destMasuId;
    int motId;
    int coin;
    MASU *masu;
    int stkX;
    float t;
    float sq;
    float frames;
    float dist;
    float total;
    float speed;
    float mag;
    float decay;
    u32 flag;
    HuVecF *vtxTop;
    int deadI;
    int stkY;
    int btn;
    int lastNo;
    int winId;
    HuVecF *effPosP;
    HuVecF *effPosP2;
    HuVecF *effPosP3;
    HuVecF *effPosP4;
    HuVecF playerPos;
    HuVecF rot;
    HuVecF target;
    HuVecF vec;
    HuVecF prevRot;
    int rainbowId[3];
    int masuTbl[3];
    HuVecF effPos;
    HuVecF effPos2;
    HuVecF effPos3;
    HuVecF effPos4;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    MB2_CoinInit();
    mb2_CoinMaxDist.x = 100;
    mb2_CoinMaxDist.y = 200;
    mb2_CoinMaxDist.z = -1;
    MB2_CoinEffInit();
    no = (frand() & 0x7FFF)%3;
    coin = MBPlayerCoinGet(playerNo);
    motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_308);
    for(i=1; i<MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu2 = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu2->flag & 0xF) {
            no2 = masu2->flag & MASU_FLAG_MAP;
            if(no2 == 2) {
                break;
            }
        }
    }
    if(i >= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        masuTbl[0] = masuId;
    } else {
        masuTbl[0] = i;
    }
    for(i=1; i<MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu2 = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu2->flag & MASU_FLAG_BIT_MULTI(4, 3)) {
            no2 = (masu2->flag & MASU_FLAG_MAP)>>4;
            if(no2 == 1) {
                break;
            }
        }
    }
    if(i >= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        masuTbl[1] = masuId;
    } else {
        masuTbl[1] = i;
    }
    for(i=1; i<MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu2 = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu2->flag & 0xF) {
            no2 = masu2->flag & MASU_FLAG_MAP;
            if(no2 == 7) {
                break;
            }
        }
    }
    if(i >= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        masuTbl[2] = masuId;
    } else {
        masuTbl[2] = i;
    }
    MBPlayerPosGet(playerNo, &playerPos);
    target.x = playerPos.x;
    target.y = 150+playerPos.y;
    target.z = playerPos.z-300;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, NULL, 3000, -1, 10);
    MBCameraMotionWait();
    MBPlayerRotateStart(playerNo, 180, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<27.0f; i++) {
        t = i/24.0f;
        PSVECSubtract(&target, &playerPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&playerPos, &vec, &vec);
        vec.y += 200*HuSin(180*t);
        MBPlayerPosSetV(playerNo, &vec);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MB2_YajiInit(&target);
    fxId = HuAudFXPlay(1496);
    MBMotionSpeedSet(mb2_Work.objMdlId2[11], 0.25f);
    MBMotionTimeSet(mb2_Work.objMdlId2[11], 0);
    while(MBMotionTimeGet(mb2_Work.objMdlId2[11]) <= 15) {
        HuPrcVSleep();
    }
    if(fxId != -1) {
        HuAudFXStop(fxId);
    }
    fxId = -1;
    HuAudFXPlay(1495);
    while(MBMotionTimeGet(mb2_Work.objMdlId2[11]) <= 25) {
        HuPrcVSleep();
    }
    WipeColorSet(255, 255, 255);
    WipeCreate(2, 0, 30);
    WipeWait();
    while(!MBMotionEndCheck(mb2_Work.objMdlId2[11])) {
        HuPrcVSleep();
    }
    MB2_RainbowObjInit();
    rainbowId[0] = MB2_RainbowObjCreate(mb2ev_Zen2RainbowVtxTbl[no][0], mb2ev_Zen2RainbowVtxNumTbl[no][0], 0);
    rainbowId[1] = MB2_RainbowObjCreate(mb2ev_Zen2RainbowVtxTbl[no][1], mb2ev_Zen2RainbowVtxNumTbl[no][1], 0);
    rainbowId[2] = MB2_RainbowObjCreate(mb2ev_Zen2RainbowVtxTbl[no][2], mb2ev_Zen2RainbowVtxNumTbl[no][2], 0);
    for(i=0; i<16; i++) {
        vec = mb2ev_Zen2CoinBasePos;
        vec.y += 100;
        effPos = vec;
        effPosP = &effPos;
        decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
        MB2_CoinEffCreateColRand(effPosP, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
    }
    MBMasuPlayerLightSet(playerNo, FALSE);
    HuAudFXPlay(1480);
    WipeColorSet(255, 255, 255);
    WipeCreate(1, 0, 90);
    do {
        if((frand() & 1) == 0) {
            effPos2 = mb2ev_Zen2CoinBasePos;
            effPosP2 = &effPos2;
            decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
            MB2_CoinEffCreateColRand(effPosP2, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 50, 0, 2);
        }
        for(i=0; i<6; i++) {
            if(MB2_RainbowObjVtxTopGet(rainbowId[(frand() & 0x7FFF)%3], &vtxTop)) {
                effPos3 = vtxTop[(frand() & 0x7FFF)%15];
                effPosP3 = &effPos3;
                decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
                MB2_CoinEffCreateColRand(effPosP3, 100*(0.1f+(0.1f*MB2_RandF())), decay, 150, 50, 0, 2);
            }
        }
        HuPrcVSleep();
    } while(WipeCheckEnd());
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 9, 0, 8, 0);
    while(MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1) {
        HuPrcVSleep();
    }
    while(!MBMotionEndCheck(MBPlayerModelGet(playerNo))) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBWinCreate(2, MESS_BOARD_W02_ZEN2_INST, -1);
    MBTopWinWait();
    MBTopWinKill();
    winId = MBWinCreateHelp(MESS_BOARD_W02_ZEN2_HELP);
    MBWinPosSet(winId, 201, 288);
    MB2_YajiDispSet(TRUE);
    yajiNo = 1;
    lastNo = yajiNo;
    if(GwPlayer[playerNo].comF == 0) {
        do {
            HuPrcVSleep();
            stkX = MBPadStkXGet(GwPlayer[playerNo].padNo);
            stkY = MBPadStkYGet(GwPlayer[playerNo].padNo);
            btn = HuPadBtnDown[GwPlayer[playerNo].padNo];
            if(fabs(stkX) > 8 || fabs(stkY) > 8) {
                t = 180*(atan2(stkX, -stkY)/M_PI);
                if(fabs(t) < 45) {
                    yajiNo = 1;
                } else if(t >= 45) {
                    yajiNo = 2;
                } else if(t <= -45) {
                    yajiNo = 0;
                }
                if(yajiNo != lastNo) {
                    MB2_YajiHiliteSet(yajiNo);
                }
                lastNo = yajiNo;
            }
        } while(!(btn & PAD_BUTTON_A));
    } else {
        HuPrcSleep(60*MB2_RandF());
        yajiNo = (frand() & 0x7FFF)%3;
        MB2_YajiHiliteSet(yajiNo);
        HuPrcSleep(60*MB2_RandF());
    }
    MB2_YajiDispSet(FALSE);
    MBTopWinKill();
    vtxNum = MB2_RainbowObjVtxTopGet(rainbowId[yajiNo], &vtxTop);
    destMasuId = masuTbl[mb2ev_Zen2DestTbl[no][yajiNo]];
    MBPlayerPosFixEvent(playerNo, destMasuId, TRUE);
    data = mb2_Work.unk70 = HuMemDirectMallocNum(HEAP_HEAP, vtxNum*sizeof(MB2_ZEN2DATA), HU_MEMNUM_OVL);
    memset(data, 0, vtxNum*sizeof(MB2_ZEN2DATA));
    for(i=0, total=0; i<vtxNum-1; i++, data++) {
        PSVECSubtract(&vtxTop[i+1], &vtxTop[i], &vec);
        data->len = PSVECMag(&vec);
        data->startLen = total;
        data->startPos = vtxTop[i];
        data->endPos = vtxTop[i+1];
        sq = (vec.x*vec.x)+(vec.z*vec.z);
        data->rot.x = -(180*(atan2(vec.y, sqrtf(sq))/M_PI));
        data->rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
        data->rot.z = 0;
        if(i == 0) {
            data->prevRot = data->rot;
        } else {
            data->prevRot = prevRot;
        }
        prevRot = data->rot;
        total += data->len;
    }
    for(i=4; i<mb2ev_Zen2RainbowVtxNumTbl[no][yajiNo]; i++) {
        if(frand() & 0xF) {
            vec = mb2ev_Zen2RainbowVtxTbl[no][yajiNo][i];
            vec.y += 50;
            MB2_CoinCreate(&vec, &vec, 0, 1);
        }
    }
    MBPlayerMotionNoShiftSet(playerNo, motId, 0, 8, 0);
    MBPlayerPosGet(playerNo, &playerPos);
    target = vtxTop[0];
    PSVECSubtract(&target, &playerPos, &vec);
    mag = PSVECMag(&vec);
    frames = 27;
    for(i=0; i<frames; i++) {
        t = i/frames;
        PSVECSubtract(&target, &playerPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&playerPos, &vec, &vec);
        vec.y += 2*(100*HuSin(180*t));
        MBPlayerPosSetV(playerNo, &vec);
        PSVECSubtract(&target, &playerPos, &vec);
        MBPlayerRotGet(playerNo, &rot);
        rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
        MBPlayerRotSetV(playerNo, &rot);
        HuPrcVSleep();
    }
    MBPlayerPosSetV(playerNo, &target);
    fxId = HuAudFXPlay(1497);
    dist = 0;
    speed = 10;
    deadI = 0;
    do {
        if(speed < 30) {
            speed += 0.1f;
        }
        dist += speed;
        data = mb2_Work.unk70;
        for(i=0; i<vtxNum-1; i++, data++) {
            if(dist < data->len+data->startLen) {
                break;
            }
        }
        if(i >= vtxNum-1) {
            break;
        }
        t = (dist-data->startLen)/data->len;
        PSVECSubtract(&data->endPos, &data->startPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&data->startPos, &vec, &vec);
        MBPlayerRotGet(playerNo, &rot);
        rot.x = fn_1_BF54(t, data->prevRot.x, data->rot.x);
        rot.y = fn_1_BF54(t, data->prevRot.y, data->rot.y);
        rot.z = 0;
        MBPlayerPosSetV(playerNo, &vec);
        MBPlayerRotSetV(playerNo, &rot);
        effPos4 = vec;
        effPosP4 = &effPos4;
        decay = 0.0166667f*(0.5f+(0.3f*MB2_RandF()));
        MB2_CoinEffCreateColRand(effPosP4, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
        HuPrcVSleep();
    } while(dist < total);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    if(fxId != -1) {
        HuAudFXStop(fxId);
    }
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    MBPlayerPosGet(playerNo, &playerPos);
    MBMasuPosGet(MASU_LAYER_DEFAULT, destMasuId, &target);
    PSVECSubtract(&target, &playerPos, &vec);
    mag = PSVECMag(&vec);
    frames = 27;
    for(i=0; i<frames; i++) {
        t = i/frames;
        PSVECSubtract(&target, &playerPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&playerPos, &vec, &vec);
        vec.y += 2*(100*HuSin(180*t));
        MBPlayerPosSetV(playerNo, &vec);
        PSVECSubtract(&target, &playerPos, &vec);
        MBPlayerRotGet(playerNo, &rot);
        rot.y = 180*(atan2(vec.x, vec.z)/M_PI);
        MBPlayerRotSetV(playerNo, &rot);
        HuPrcVSleep();
    }
    MBPlayerPosSetV(playerNo, &target);
    GwPlayer[playerNo].masuId = destMasuId;
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBMasuPlayerLightSet(playerNo, TRUE);
    for(i=0; i<60.0f; i++) {
        t = 1-(i/60.0f);
        MB2_RainbowObjAlphaSet(rainbowId[0], 255*t);
        MB2_RainbowObjAlphaSet(rainbowId[1], 255*t);
        MB2_RainbowObjAlphaSet(rainbowId[2], 255*t);
        HuPrcVSleep();
    }
    HuPrcSleep(30);
    coin = MBPlayerCoinGet(playerNo)-coin;
    MB2_CoinDispUpdate(playerNo, coin, 100);
    HuPrcSleep(30);
    MBMotionSpeedSet(mb2_Work.objMdlId2[11], 0);
    MBMotionTimeSet(mb2_Work.objMdlId2[11], 0);
    if(motId != -1) {
        MBPlayerMotionKill(playerNo, motId);
    }
    if(mb2_Work.unk70 != NULL) {
        HuMemDirectFree(mb2_Work.unk70);
    }
    mb2_Work.unk70 = NULL;
    MB2_RainbowObjClose();
    MB2_YajiClose();
    MB2_CoinClose();
    MB2_CoinEffClose();
}

/* Where a ride of `speed` ends up, given that it loses a hundredth of itself
 * every frame over `len`. Not a reference symbol: it is inlined at all five
 * of its call sites and no standalone copy survives, which is why it has to
 * be defined above MB2Ev_Zen4 -- `-inline auto` cannot reach forward. */
static float MB2Ev_Zen4Calc(float speed, float len)
{
    if(speed != 0) {
        return speed+(speed*((-1+sqrtf(1+(8*(len/speed))))*0.5f));
    }
    return 0;
}

/* 2278 instructions
 *
 * The ride. The player is carried onto "sisof1", a bone of the board's
 * obj18 model, and mashes A against a sixty-second timer; each press adds a
 * decaying push, and how high they get before letting go decides how many of
 * the twenty coins strung above them they collect.
 *
 * Three locals here are written and never read: the landing space, the timer
 * object and an int zeroed before the ride. All three are the disc's.
 */
static void MB2Ev_Zen4(int playerNo)
{
    int i;
    int step;
    int frames;
    int n;
    int coin;
    int endF;
    int doneF;
    int comStep;
    int releaseF;
    s16 masuId;
    float speed;
    float t;
    float v;
    float rate;
    float d;
    float posY;
    float velY;
    float maxTime;
    int motId2;
    int motId1;
    MASU *masu;
    float maxDist;
    OMOBJ *timerObj;
    int deadI;
    HuVecF playerPos;
    HuVecF startPos;
    HuVecF hookPos;
    HuVecF vel;
    HuVecF vec;
    Mtx mtx;

    doneF = 0;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MB2_CoinInit();
    MB2_CoinEffInit();
    MBPlayerPosGet(playerNo, &playerPos);
    startPos = playerPos;
    Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
    hookPos.x = mtx[0][3];
    hookPos.y = mtx[1][3];
    hookPos.z = mtx[2][3];
    motId1 = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_308);
    motId2 = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_309);
    PSVECSubtract(&hookPos, &startPos, &vec);
    MBPlayerRotateStart(playerNo, 180*(atan2(vec.x, vec.z)/M_PI), 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=24.0f; i++) {
        t = i/24.0f;
        PSVECSubtract(&hookPos, &startPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&startPos, &vec, &vec);
        vec.y += 200*HuSin(180*t);
        MBPlayerPosSetV(playerNo, &vec);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    for(i=0; i<12.0f; i++) {
        t = i/12.0f;
        maxTime = MBMotionMaxTimeGet(mb2_Work.objMdlId2[14]);
        MBMotionTimeSet(mb2_Work.objMdlId2[14], 0.33*HuSin(180*t)*maxTime);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
        MBPlayerPosSet(playerNo, mtx[0][3], mtx[1][3], mtx[2][3]);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
        MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
        HuPrcVSleep();
    }
    vec.x = 0;
    vec.y = 100;
    vec.z = 0;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, &vec, 3000, -1, 21);
    MBCameraMotionWait();
    for(i=0; i<20; i++) {
        vec.x = hookPos.x;
        vec.y = (800+hookPos.y)+(1.5f*(100.0f*i));
        vec.z = hookPos.z;
        MB2_CoinCreate(&vec, &vec, 0, 1);
    }
    coin = MBPlayerCoinGet(playerNo);
    MBWinCreate(2, MESS_BOARD_W02_ZEN4_INST, -1);
    MBTopWinWait();
    MBTopWinKill();
    MBWinCreateHelp(MESS_BOARD_W02_ZEN4_HELP);
    posY = 0;
    velY = 0;
    speed = 150;
    v = MB2Ev_Zen4Calc(speed, 25000);
    d = 0;
    n = 0;
    do {
        if(n < 10) {
            v = MB2Ev_Zen4Calc(speed, 25000)-(n*speed);
        }
        v -= speed;
        d = v/100;
        velY += d;
        posY += velY;
        maxDist = posY;
        n++;
        velY = 0;
    } while(v >= 0);
    timerObj = MBAddObj(32768, 0, 0, MB2_TimerObjUpdate);
    mb2ev_TimerObj = 3600;
    mb2ev_TimerValue = 300;
    do {
        if(GwPlayer[playerNo].comF) {
            HuPrcSleep(60*MB2_RandF());
        } else {
            while(!(HuPadBtnDown[GwPlayer[playerNo].padNo] & PAD_BUTTON_A)) {
                if(mb2ev_TimerObj <= 0) {
                    break;
                }
                HuPrcVSleep();
            }
            if(mb2ev_TimerObj <= 0) {
                rate = 0;
                break;
            }
        }
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        MBPlayerPosGet(playerNo, &playerPos);
        vel.x = 0;
        vel.y = 0;
        vel.z = 0;
        step = 0;
        releaseF = 0;
        deadI = 0;
        v = MB2Ev_Zen4Calc(speed, 25000);
        comStep = n*((0.35f+(0.2f*MB2_RandF()))+(0.15f*GwPlayer[playerNo].dif));
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
        do {
            HuPrcVSleep();
            endF = 0;
            if(step < 10 && mb2ev_TimerObj > 0 && releaseF == 0) {
                v = MB2Ev_Zen4Calc(speed, 25000)-(step*speed);
                if(!GwPlayer[playerNo].comF) {
                    if(!(HuPadBtn[GwPlayer[playerNo].padNo] & PAD_BUTTON_A)) {
                        v = MB2Ev_Zen4Calc(speed, 4000);
                        releaseF = 1;
                    }
                }
            }
            v -= speed;
            d = v/100;
            vel.y += d;
            PSVECAdd(&playerPos, &vel, &playerPos);
            MBPlayerPosSetV(playerNo, &playerPos);
            step++;
            if(GwPlayer[playerNo].comF) {
                comStep--;
                if(comStep <= 0) {
                    endF = 1;
                }
            } else {
                if((HuPadBtnDown[GwPlayer[playerNo].padNo] & (PAD_BUTTON_A|PAD_TRIGGER_L)) && mb2ev_TimerObj > 0) {
                    endF = 1;
                }
            }
            if(playerPos.y > mtx[1][3] && endF) {
                MBPlayerMotionNoShiftSet(playerNo, motId1, 0, 8, 0);
                MBTopWinKill();
                rate = (playerPos.y-mtx[1][3])/maxDist;
                if(rate > 1) {
                    rate = 1;
                } else if(rate < 0) {
                    rate = 0;
                }
                doneF = 1;
                step = 20;
                break;
            }
            vel.x = vel.y = vel.z = 0;
        } while(playerPos.y > mtx[1][3]);
        if(doneF == 0) {
            MBPlayerMotionNoShiftSet(playerNo, 5, 0, 8, 0);
            for(i=0; i<12.0f; i++) {
                t = i/12.0f;
                maxTime = MBMotionMaxTimeGet(mb2_Work.objMdlId2[14]);
                MBMotionTimeSet(mb2_Work.objMdlId2[14], 0.33*HuSin(180*t)*maxTime);
                Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
                MBPlayerPosSet(playerNo, mtx[0][3], mtx[1][3], mtx[2][3]);
                Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
                MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
                HuPrcVSleep();
            }
            do {
                HuPrcVSleep();
            } while(!MBPlayerMotionEndCheck(playerNo) || MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
            MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        }
    } while(doneF == 0);
    mb2ev_TimerObj = 0;
    MBTopWinKill();
    if(rate <= 0.01f) {
        goto skip;
    }
    do {
        HuPrcVSleep();
        step--;
    } while(step > 0);
    Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
    v = speed;
    vel.x = vel.y = vel.z = 0;
    do {
        HuPrcVSleep();
        v -= speed;
        d = v/100;
        vel.y += d;
        PSVECAdd(&playerPos, &vel, &playerPos);
        MBPlayerPosSetV(playerNo, &playerPos);
        vel.x = vel.y = vel.z = 0;
    } while(playerPos.y > mtx[1][3]);
    playerPos.y = mtx[1][3];
    MBPlayerPosSetV(playerNo, &playerPos);
    MBPlayerMotionNoShiftSet(playerNo, motId1, 0, 8, 0);
    frames = 30*(0.6f-(0.5f*rate));
    if(frames < 5) {
        frames = 5;
    }
    for(i=0; i<=frames; i++) {
        t = (float)i/(float)frames;
        MBMotionTimeSet(mb2_Work.objMdlId2[14], t*MBMotionMaxTimeGet(mb2_Work.objMdlId2[14]));
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
        MBPlayerPosSet(playerNo, mtx[0][3], mtx[1][3], mtx[2][3]);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
        MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
        HuPrcVSleep();
    }
    Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
    vel.x = 0;
    vel.y = -d;
    vel.z = 0;
    MBModelPosGet(mb2_Work.objMdlId2[13], &playerPos);
    mb2_Work.unk9C = 0;
    do {
        HuPrcVSleep();
        PSVECAdd(&playerPos, &vel, &playerPos);
        MBModelPosSetV(mb2_Work.objMdlId2[13], &playerPos);
        vel.y -= 3.2666667f;
    } while(playerPos.y > mtx[1][3]);
    MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
    mb2_Work.unk9C = 1;
    HuAudFXPlay(1493);
    for(i=0; i<=frames; i++) {
        t = (float)i/(float)frames;
        MBMotionTimeSet(mb2_Work.objMdlId2[14], (1-t)*MBMotionMaxTimeGet(mb2_Work.objMdlId2[14]));
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
        MBPlayerPosSet(playerNo, mtx[0][3], mtx[1][3], mtx[2][3]);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
        MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
        HuPrcVSleep();
    }
    HuAudFXPlay(1486);
    Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
    rate = 0.3f+(0.7f*rate);
    vel.x = 0;
    vel.y = 160*rate;
    vel.z = 0;
    MBPlayerPosGet(playerNo, &playerPos);
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    do {
        HuPrcVSleep();
        PSVECAdd(&playerPos, &vel, &playerPos);
        MBPlayerPosSetV(playerNo, &playerPos);
        vel.y -= 3.2666667f;
    } while(playerPos.y > mtx[1][3]);
    playerPos.y = mtx[1][3];
    MBPlayerPosSetV(playerNo, &playerPos);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    for(i=0; i<12.0f; i++) {
        t = i/12.0f;
        maxTime = MBMotionMaxTimeGet(mb2_Work.objMdlId2[14]);
        MBMotionTimeSet(mb2_Work.objMdlId2[14], 0.33*HuSin(180*t)*maxTime);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof1", mtx);
        MBPlayerPosSet(playerNo, mtx[0][3], mtx[1][3], mtx[2][3]);
        Hu3DModelObjMtxGet(MBModelIdGet(mb2_Work.objMdlId2[14]), "sisof2", mtx);
        MBModelPosSet(mb2_Work.objMdlId2[13], mtx[0][3], mtx[1][3], mtx[2][3]);
        HuPrcVSleep();
    }
skip:
    HuPrcSleep(60);
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=24.0f; i++) {
        t = i/24.0f;
        PSVECSubtract(&startPos, &hookPos, &vec);
        PSVECScale(&vec, &vec, t);
        PSVECAdd(&hookPos, &vec, &vec);
        vec.y += 200*HuSin(180*t);
        MBPlayerPosSetV(playerNo, &vec);
        PSVECSubtract(&startPos, &hookPos, &vec);
        MBPlayerRotSet(playerNo, 0, 180*(atan2(vec.x, vec.z)/M_PI), 0);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    HuPrcSleep(30);
    coin = MBPlayerCoinGet(playerNo)-coin;
    MB2_CoinDispUpdate(playerNo, coin, 20);
    HuPrcSleep(30);
    if(motId1 != -1) {
        MBPlayerMotionKill(playerNo, motId1);
    }
    if(motId2 != -1) {
        MBPlayerMotionKill(playerNo, motId2);
    }
    MB2_CoinClose();
    MB2_CoinEffClose();
}

/* 122 instructions
 *
 * Runs the "N seconds left" message down from mb2ev_TimerValue to zero. The
 * `+58` before the divide by 60 rounds the frame count up to whole seconds.
 */
static void MB2_TimerObjUpdate(OMOBJ *obj)
{
    if(MBKillCheck()) {
        mb2ev_TimerObj = 0;
    }
    if(mb2ev_TimerObj > mb2ev_TimerValue) {
        mb2ev_TimerGameMesId = -1;
    } else if(mb2ev_TimerObj == mb2ev_TimerValue) {
        mb2ev_TimerGameMesId = GameMesTimerCreate((mb2ev_TimerObj+58)/60);
    } else if(mb2ev_TimerObj < mb2ev_TimerValue) {
        if(mb2ev_TimerGameMesId != -1) {
            GameMesTimerValueSet(mb2ev_TimerGameMesId, (mb2ev_TimerObj+58)/60);
        }
        if(mb2ev_TimerObj <= 0) {
            if(mb2ev_TimerGameMesId != -1) {
                GameMesTimerEnd(mb2ev_TimerGameMesId);
            }
            mb2ev_TimerGameMesId = -1;
            omDelObjEx(mbObjMan, obj);
            return;
        }
    }
    mb2ev_TimerObj--;
}

/* 59 instructions
 *
 * The lamp-post: obj->work[1] counts frames, obj->work[2] flips every fourth,
 * and the model's motion is parked either at obj->trans.x of its length or at
 * zero. obj->work[0] is the liveness flag.
 */
static void MB2_DentyuObjFlash(OMOBJ *obj)
{
    if(MBKillCheck()) {
        obj->work[0] = 0;
    }
    if(obj->work[0] == 0) {
        omDelObjEx(mbObjMan, obj);
        return;
    }
    obj->work[1]++;
    if((obj->work[1] & 3) == 0) {
        obj->work[2] ^= 1;
    }
    if(obj->work[2] & 1) {
        MBMotionTimeSet(mb2_Work.objMdlId2[3], obj->trans.x*MBMotionMaxTimeGet(mb2_Work.objMdlId2[3]));
    } else {
        MBMotionTimeSet(mb2_Work.objMdlId2[3], 0);
    }
}

/* 209 instructions
 *
 * One splash a frame around obj->trans for obj->work[0] frames, every eighth
 * of them on the additive layer. It calls omDelObjEx on the last frame and
 * then spawns one more splash anyway -- that fall-through is the disc's.
 */
static void MB2_WaterSplashUpdate(OMOBJ *obj)
{
    GXColor colRand;
    GXColor col;
    HuVecF pos;
    int no;
    GXColor *colP;
    float rate;

    if(--obj->work[0] == 0 || MBKillCheck()) {
        omDelObjEx(mbObjMan, obj);
    }
    pos.x = obj->trans.x+1.5f*(100*(0.5f-MB2_RandF()));
    pos.z = obj->trans.z+1.5f*(100*(0.5f-MB2_RandF()));
    pos.y = obj->trans.y+0.5f*(100*(0.5f-MB2_RandF()));
    rate = 32*MB2_RandF();
    colRand.r = 200+rate;
    colRand.g = 200+rate;
    colRand.b = 220+rate;
    colRand.a = 32+(32*MB2_RandF());
    if((obj->work[0] & 7) == 0) {
        no = 1;
    } else {
        no = 0;
    }
    col = colRand;
    colP = &col;
    MB2_SplashEffCreateRandX(&pos, colP, 1, no);
}

/* 58 instructions
 *
 * A wind guru blows a player from one numbered space to the next: the space's
 * own bits 7-9 are a direction, `no` (or mb2_SaveWorkP[0] when it is -1) is
 * where the player is in the cycle, and the answer is the first space on the
 * board carrying the resulting number. With no match the player stays put.
 */
static int MB2_WindGuru2MasuNoGet(int masuId, int no)
{
    MASU *masu;
    int i;
    int no2;
    int flagNo;
    int dir;

    if(no == -1) {
        no2 = mb2_SaveWorkP[0];
    } else {
        no2 = no;
    }
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    dir = (masu->flag & MASU_FLAG_BIT_MULTI(7, 3)) >> 7;
    no2 = dir+no2;
    if(no2 >= 5) {
        no2 -= 4;
    }
    for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu->flag & MASU_FLAG_BIT_MULTI(7, 3)) {
            flagNo = (masu->flag & MASU_FLAG_BIT_MULTI(7, 3)) >> 7;
            if(flagNo == no2) {
                break;
            }
        }
    }
    if(i > MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        i = masuId;
    }
    return i;
}

/* 79 instructions -- the far end of the rainbow leading off a space. */
static int MB2_RainbowMasuNoEndGet(int masuId)
{
    int linkNum;
    MASU *masu;
    int linkId;
    int i;
    int type;
    s16 linkTbl[16];

    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    type = masu->flag & 0xF;
    if(type == 2 || type == 4 || type == 6 || type == 8) {
        return -1;
    }
    if((masu->flag & 0xF) == 0) {
        goto notFound;
    }
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    for(i=0; i<masu->linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & MASU_FLAG_BIT(14)) {
            break;
        }
    }
    if(i >= masu->linkNum) {
        goto notFound;
    }
    linkId = masu->linkTbl[i];
    linkNum = MB2_MasuLinkGet(linkId, linkTbl, TRUE, TRUE);
    for(i=0; i<linkNum; i++) {
        if(masuId != linkTbl[i]) {
            break;
        }
    }
    if(i >= linkNum) {
        goto notFound;
    }
    return linkTbl[i];
notFound:
    return -1;
}

/* 19 instructions */
static BOOL MB2_PathCheck(int masuId)
{
    if(MB2_PathLenGet(masuId, 25, 0) != -1) {
        return TRUE;
    }
    return FALSE;
}

/* 39 instructions */
static s16 MB2_PathLenGet(s16 masuId, s16 num, s16 allF)
{
    mb2_PathMasuNo = num;
    mb2_PathLen = num;
    mb2_PathAllF = allF;
    mb2_PathValidF = 0;
    PathCheck(masuId, num);
    if(mb2_PathValidF != 0) {
        return mb2_PathLen;
    }
    return -1;
}

/* 185 instructions
 *
 * MB2_PathLenGet's recursion: walk every branch out of a space for `num`
 * steps and record the shortest distance at which a star space is reached.
 * mb2_PathAllF additionally follows the rainbow off a space -- the second
 * half is the same "which link comes back to me" search MB2_MasuPathCheck
 * does, in reverse.
 */
static s16 PathCheck(s16 masuId, s16 num)
{
    int j;
    MASU *masu;
    MASU *linkMasu;
    s16 i;
    int type;
    s16 findF;
    int nextId;
    s16 len;
    int linkNum;
    int linkId;
    s16 linkTbl[10];

    findF = 0;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(MBMasuTypeGet(MASU_LAYER_DEFAULT, masuId) == MASU_TYPE_STAR) {
        len = mb2_PathMasuNo-num;
        if(len < mb2_PathLen) {
            mb2_PathLen = len;
        }
        mb2_PathValidF = 1;
        return 1;
    }
    if(MBMasuTypeGet(MASU_LAYER_DEFAULT, masuId) != MASU_TYPE_NONE && MBMasuTypeGet(MASU_LAYER_DEFAULT, masuId) != MASU_TYPE_STAR) {
        num--;
    }
    if(num >= 0) {
        for(i=0; i<masu->linkNum; i++) {
            if((MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & (MBBranchFlagGet()|(MASU_FLAG_BLOCKL|MASU_FLAG_BLOCKR))) == 0) {
                if(PathCheck(masu->linkTbl[i], num) != 0) {
                    findF = 1;
                }
            }
        }
    }
    if(mb2_PathAllF != 0 && num < mb2_PathMasuNo-1 && (masu->flag & 0xF) != 0) {
        linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        type = linkMasu->flag & 0xF;
        if(type == 2 || type == 4 || type == 6 || type == 8) {
            nextId = -1;
        } else {
            if((linkMasu->flag & 0xF) == 0) {
                goto notFound;
            }
            linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
            for(j=0; j<linkMasu->linkNum; j++) {
                if(MBMasuFlagGet(MASU_LAYER_DEFAULT, linkMasu->linkTbl[j]) & MASU_FLAG_BIT(14)) {
                    break;
                }
            }
            if(j >= linkMasu->linkNum) {
                goto notFound;
            }
            linkId = linkMasu->linkTbl[j];
            linkNum = MB2_MasuLinkGet(linkId, linkTbl, TRUE, TRUE);
            for(j=0; j<linkNum; j++) {
                if(masuId != linkTbl[j]) {
                    break;
                }
            }
            if(j >= linkNum) {
                goto notFound;
            }
            nextId = linkTbl[j];
            goto found;
        notFound:
            nextId = -1;
        found:
            ;
        }
        masuId = nextId;
        if(masuId != -1) {
            if(PathCheck(masuId, num) != 0) {
                findF = 1;
            }
        }
    }
    if(findF != 0) {
        return 1;
    }
    return 0;
}

/* 140 instructions
 *
 * A process: turn the player to face the camera, pop the coin counter above
 * their head, play the win, lose or big-win reaction, and wait for all of it
 * to finish. `total` only picks which of the two winning motions to use.
 */
static void MB2_CoinDispUpdate(int playerNo, int coin, int total)
{
    int dispId;
    int motId = -1;
    HuVecF pos;

    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    if(coin > 0) {
        MBPlayerPosGet(playerNo, &pos);
        pos.y += 250;
        dispId = MBCoinDispCreateSe(&pos, coin);
    } else {
        dispId = -1;
    }
    if(coin <= 0) {
        MBPlayerWinLoseVoicePlay(playerNo, 13, 512);
        MBPlayerMotionNoShiftSet(playerNo, 13, 0, 8, 0);
    } else if(coin < total) {
        MBPlayerWinLoseVoicePlay(playerNo, 12, 507);
        MBPlayerMotionNoShiftSet(playerNo, 12, 0, 8, 0);
    } else {
        MBPlayerWinLoseVoicePlay(playerNo, 12, 507);
        motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_356);
        MBPlayerMotionNoShiftSet(playerNo, motId, 0, 8, 0);
    }
    do {
        HuPrcVSleep();
    } while(!MBPlayerMotionEndCheck(playerNo) || MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    do {
        HuPrcVSleep();
    } while(MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
    if(dispId != -1) {
        while(!MBCoinDispKillCheck(dispId)) {
            HuPrcVSleep();
        }
    }
    if(motId != -1) {
        MBPlayerMotionKill(playerNo, motId);
    }
}

/* 70 instructions */
static float MB2_AngleDiff(float angle1, float angle2)
{
    float diff;

    if(angle1 >= 360) {
        angle1 -= 360;
    } else if(angle1 < 0) {
        angle1 += 360;
    }
    if(angle2 >= 360) {
        angle2 -= 360;
    } else if(angle2 < 0) {
        angle2 += 360;
    }
    diff = angle1-angle2;
    if(diff <= -180) {
        diff += 360;
    } else if(diff >= 180) {
        diff -= 360;
    }
    return diff;
}

/* 148 instructions */
static float MB2_AngleLerp(float target, float angle, float speed)
{
    float diff;
    float value;

    if(target >= 360.0) {
        target -= 360.0;
    } else if(target < 0.0) {
        target += 360.0;
    }
    if(angle >= 360.0) {
        angle -= 360.0;
    } else if(angle < 0.0) {
        angle += 360.0;
    }
    diff = 360.0+(target-angle);
    if(fabs(diff) >= 360.0) {
        diff = fmod(diff, 360.0);
    }
    if(diff < 180.0) {
        if(diff <= speed) {
            value = diff;
        } else {
            value = speed;
        }
    } else {
        if((360.0-diff) <= speed) {
            value = -(360.0-diff);
        } else {
            value = -speed;
        }
    }
    value += angle;
    if(value >= 360.0) {
        value -= 360.0;
    } else if(value < 0.0) {
        value += 360.0;
    }
    return value;
}

/* 254 instructions
 *
 * Two lines: turn `angle` toward `target` by `rate` of the way there. It is
 * 254 instructions because `MB2_AngleDiff` and `MB2_AngleLerp` are both
 * defined above it and both get inlined -- 70 and 148 instructions, plus the
 * `fabsf` in between. Nothing here has to be written longhand.
 */
static float fn_1_BF54(float rate, float angle, float target)
{
    float diff;

    diff = MB2_AngleDiff(target, angle);
    return MB2_AngleLerp(target, angle, fabs(diff*rate));
}

/* 45 instructions */
static int MB2_MasuLinkGet(s16 masuId, s16 *linkTbl, BOOL linkF, BOOL pathF)
{
    MASU *masu;
    int i;
    int num = 0;

    if(linkF) {
        masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        num = masu->linkNum;
        for(i=0; i<num; i++) {
            linkTbl[i] = masu->linkTbl[i];
        }
    }
    if(pathF) {
        num += MBMasuLinkTblGet(MASU_LAYER_DEFAULT, masuId, &linkTbl[num]);
    }
    return num;
}

/* 18 instructions */
static HSFOBJECT *MB2_ModelObjPtrGet(HU3DMODEL *modelP, char *name)
{
    HSFDATA *hsfP = modelP->hsf;

    return objCall(modelP, name, hsfP->root);
}

/* 530 instructions
 *
 * A depth-first search of an HSF object tree by name, and the reason it is
 * 530 instructions for a dozen lines of source: `cflags_rel` carries
 * `-inline auto`, and MWCC will inline a *recursive* function into itself.
 * The body appears four times over -- once per level -- with a fresh set of
 * stack slots each time, and only the innermost copy keeps the real `bl`.
 *
 * The two arms are textually identical; the split is HSF_OBJ_REPLICA against
 * everything else that has children. HSF_OBJ_CAMERA (7) and HSF_OBJ_LIGHT (8)
 * fall through to the NULL return, which is what the `cmpwi 7` / `cmpwi 9`
 * pair at the top of each copy is testing.
 *
 * `modelP` is never used except to be handed to the recursive call.
 */
static HSFOBJECT *objCall(HU3DMODEL *modelP, char *name, HSFOBJECT *object)
{
    HSFOBJECT *obj;
    HSFOBJECT *repObj;
    HSFOBJECT *ret;
    int i;

    switch(object->type) {
    case HSF_OBJ_NULL1:
    case HSF_OBJ_MESH:
    case HSF_OBJ_ROOT:
    case HSF_OBJ_JOINT:
    case HSF_OBJ_NULL2:
    case HSF_OBJ_NULL3:
    case HSF_OBJ_MAP:
        obj = object;
        if(strcmp(name, obj->name) == 0) {
            return obj;
        }
        for(i=0; i<obj->mesh.childNum; i++) {
            ret = objCall(modelP, name, obj->mesh.child[i]);
            if(ret) {
                return ret;
            }
        }
        break;

    case HSF_OBJ_REPLICA:
        repObj = object;
        if(strcmp(name, repObj->name) == 0) {
            return repObj;
        }
        for(i=0; i<repObj->mesh.childNum; i++) {
            ret = objCall(modelP, name, repObj->mesh.child[i]);
            if(ret) {
                return ret;
            }
        }
        break;
    }
    return NULL;
}

/* 30 instructions */
static float MB2_BezierCalc(float t, float p0, float p1, float p2)
{
    float u = 1.0-t;
    float value;

    value = (p2*(t*t))+((p0*(u*u))+(2.0*(p1*(u*t))));
    return value;
}

/* 71 instructions */
static void MB2_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out)
{
    int i;

    for(i=0; i<3; i++) {
        *out++ = MB2_BezierCalc(t, *p0++, *p1++, *p2++);
    }
}

/* 37 instructions */
static void MB2_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11)
{
    float t2 = t*t;
    float t3 = t*t2;
    float h = (3.0*t2)-t3-t3;

    *h00 = 1.0-h;
    *h10 = h;
    *h01 = t+((t3-t2)-t2);
    *h11 = t3-t2;
}

/* 90 instructions */
static float fn_1_CEB8(float t, float p0, float p1, float p2, float p3, float tension)
{
    float h00;
    float h10;
    float h01;
    float h11;
    float diff = p2-p1;
    float value;
    float rate1;
    float rate2;
    float m1;
    float m2;
    int no = p2-p1;

    if(p1 == p2) {
        m1 = diff;
    } else {
        rate1 = tension;
        m1 = rate1*(diff+(p1-p0));
    }
    if(p1 == p3) {
        m2 = diff;
    } else {
        rate2 = tension;
        m2 = rate2*(diff+(p3-p2));
    }
    MB2_HermiteCalc(t, &h00, &h10, &h01, &h11);
    return value = (h11*m2)+((h01*m1)+((h00*p1)+(h10*p2)));
}

/* 304 instructions */
static void MB2_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out)
{
    float rate = 0.5f;

    out[0] = fn_1_CEB8(t, p0[0], p1[0], p2[0], p3[0], rate);
    out[1] = fn_1_CEB8(t, p0[1], p1[1], p2[1], p3[1], rate);
    out[2] = fn_1_CEB8(t, p0[2], p1[2], p2[2], p3[2], rate);
}

/* 100 instructions */
static void MB2_CoinInit(void)
{
    OMOBJ *obj;
    MB2_COIN *coin;
    int i;
    int j;

    obj = mb2_CoinObj = MBAddObj(32768, 0, 0, MB2_CoinUpdate);
    coin = obj->data = HuMemDirectMallocNum(HEAP_HEAP, 32*sizeof(MB2_COIN), HU_MEMNUM_OVL);
    memset(coin, 0, 32*sizeof(MB2_COIN));
    mb2_CoinMaxDist.x = 100;
    mb2_CoinMaxDist.y = 170;
    mb2_CoinMaxDist.z = 0;
    for(i=0; i<32; i++, coin++) {
        coin->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(BOARD_HSF_coin, HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(coin->mdlId, 1);
        Hu3DModelAttrSet(coin->mdlId, HU3D_ATTR_DISPOFF);
        coin->useF = 0;
        coin->mode = 0;
        coin->speed = 0;
        coin->no = coin->unk14 = 0;
        for(j=0; j<4; j++) {
            MBPlayerPosGet(j, &coin->playerPos[j]);
        }
    }
}

/* 668 instructions
 *
 * `killF` is set to 0 once a coin and tested beside `getF`, and nothing ever
 * sets it -- the disc's, and the function is short without it.
 */
static void MB2_CoinUpdate(OMOBJ *obj)
{
    MB2_COIN *coin = omObjGetDataAs(obj, MB2_COIN);
    int j;
    int i;
    int hitF;
    int getF;
    int killF;
    GXColor *colP;
    HuVecF *velP;
    HuVecF *posP;
    HuVecF pos;
    HuVecF startPos;
    HuVecF endPos;
    HuVecF vec;
    HuVecF playerPos;
    HuVecF prevPos;
    HuVecF velRand;
    HuVecF posOut;
    HuVecF vel;
    GXColor colRand;
    GXColor col;
    float t;
    float mag;
    float angle;
    float rate;
    float angleY;

    if(MBKillCheck() || mb2_CoinObj == NULL) {
        for(i=0; i<32; i++, coin++) {
            Hu3DModelKill(coin->mdlId);
            coin->mdlId = -1;
        }
        omDelObjEx(mbObjMan, obj);
        mb2_CoinObj = NULL;
        return;
    }
    for(i=0; i<32; i++, coin++) {
        if(coin->useF == 0) {
            continue;
        }
        killF = 0;
        getF = 0;
        switch(coin->mode) {
        case 0:
            t = (float)++coin->unk14/(float)coin->no;
            startPos = coin->startPos;
            endPos = coin->endPos;
            PSVECSubtract(&endPos, &startPos, &vec);
            PSVECScale(&vec, &vec, t);
            PSVECAdd(&vec, &startPos, &vec);
            vec.y += coin->speed*HuSin(180*t);
            coin->pos = vec;
            coin->rot.y += 10;
            if(t >= 1) {
                coin->mode++;
                coin->unk14 = 0;
            }
            break;

        case 1:
            coin->pos = coin->endPos;
            coin->rot.y += 10;
            break;
        }
        if(coin->mode <= 2) {
            for(j=0; j<4; j++) {
                MBPlayerPosGet(j, &playerPos);
                prevPos = coin->playerPos[j];
                PSVECSubtract(&coin->pos, &playerPos, &vec);
                hitF = 0;
                if(playerPos.y >= prevPos.y) {
                    if(coin->pos.y >= prevPos.y && coin->pos.y <= playerPos.y+mb2_CoinMaxDist.y) {
                        hitF = 1;
                    } else if(coin->pos.y <= prevPos.y+mb2_CoinMaxDist.y && coin->pos.y >= playerPos.y) {
                        hitF = 1;
                    }
                }
                if(mb2_CoinMaxDist.z < 0) {
                    hitF = 1;
                }
                if(hitF) {
                    mag = vec.x*vec.x+vec.z*vec.z;
                    if(sqrtf(mag) < mb2_CoinMaxDist.x) {
                        MBPlayerCoinAdd(j, 1);
                        MBAudFXPlay(7);
                        getF = 1;
                    }
                }
                coin->playerPos[j] = playerPos;
            }
        }
        Hu3DModelPosSet(coin->mdlId, coin->pos.x, coin->pos.y, coin->pos.z);
        Hu3DModelRotSet(coin->mdlId, coin->rot.x, coin->rot.y, coin->rot.z);
        Hu3DModelScaleSet(coin->mdlId, coin->scale.x, coin->scale.y, coin->scale.z);
        if(getF || killF) {
            coin->useF = 0;
            Hu3DModelAttrSet(coin->mdlId, HU3D_ATTR_DISPOFF);
            if(getF) {
                for(j=0, angle=0; j<32; j++) {
                    angle += 22.5f*(1+MB2_RandF());
                    pos = coin->pos;
                    t = 2.5f*(1+MB2_RandF());
                    angleY = 45-(90*MB2_RandF());
                    velRand.x = t*(HuSin(angle)*HuCos(angleY));
                    velRand.y = t*(HuCos(angle)*HuCos(angleY));
                    velRand.z = t*HuSin(angleY);
                    rate = MB2_RandF();
                    colRand.r = 192+(63*rate);
                    colRand.g = 192+(63*rate);
                    colRand.b = 64+(63*rate);
                    colRand.a = 192+(63*MB2_RandF());
                    col = colRand;
                    colP = &col;
                    vel = velRand;
                    velP = &vel;
                    posOut = pos;
                    posP = &posOut;
                    MB2_CoinEffCreate(posP, velP, 100*(0.3f+(0.1f*MB2_RandF())), 0.0166667f*(1+(0.5f*MB2_RandF())), 0, colP);
                }
                break;
            }
        }
    }
}

/* 5 instructions */
static void MB2_CoinClose(void)
{
    mb2_CoinObj = NULL;
}

/* 35 instructions */
static int MB2_CoinNumGet(void)
{
    MB2_COIN *coin;
    int i;
    int num;
    OMOBJ *obj;

    obj = mb2_CoinObj;
    num = 0;
    if(mb2_CoinObj == NULL) {
        return 0;
    }
    for(coin = omObjGetDataAs(obj, MB2_COIN), i=0; i<32; i++, coin++) {
        if(coin->useF != 0) {
            num++;
        }
    }
    return num;
}

/* 136 instructions
 *
 * `mode` is written to a stack slot nothing reads -- a dead local, the same
 * `li 0`/`stw` shape w07dll's MB7_MasuPathCheck records.
 */
static int MB2_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int no)
{
    MB2_COIN *coin;
    int i;
    OMOBJ *obj;
    int mode;

    obj = mb2_CoinObj;
    mode = 0;
    if(mb2_CoinObj == NULL) {
        return -1;
    }
    for(coin = omObjGetDataAs(obj, MB2_COIN), i=0; i<32; i++, coin++) {
        if(coin->useF == 0) {
            break;
        }
    }
    if(i >= 32) {
        return -1;
    }
    coin->useF = 1;
    coin->mode = 0;
    coin->speed = speed;
    coin->no = no;
    coin->unk14 = 0;
    if(startPos != NULL) {
        coin->startPos = *startPos;
    }
    if(endPos != NULL) {
        coin->endPos = *endPos;
    }
    coin->pos = coin->startPos;
    coin->rot.x = coin->rot.y = coin->rot.z = 0;
    coin->scale.x = coin->scale.y = coin->scale.z = 1;
    coin->rot.y = 360*MB2_RandF();
    Hu3DModelPosSet(coin->mdlId, coin->pos.x, coin->pos.y, coin->pos.z);
    Hu3DModelRotSet(coin->mdlId, coin->rot.x, coin->rot.y, coin->rot.z);
    Hu3DModelScaleSet(coin->mdlId, coin->scale.x, coin->scale.y, coin->scale.z);
    Hu3DModelTPLvlSet(coin->mdlId, 1);
    Hu3DModelAttrReset(coin->mdlId, HU3D_ATTR_DISPOFF);
    return i;
}

/* 64 instructions */
static void MB2_CoinEffInit(void)
{
    OMOBJ *obj;
    MB2_COINEFFWORK *work;
    HU3DMODEL *modelP;
    MB2_PARTICLE *partP;
    ANIMDATA *anim;
    int mdlId;

    obj = mb2_CoinEffObj = MBAddObj(32768, 0, 0, MB2_CoinEffUpdate);
    work = obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MB2_COINEFFWORK), HU_MEMNUM_OVL);
    memset(work, 0, sizeof(MB2_COINEFFWORK));
    anim = HuSprAnimRead(HuDataReadNum(CAPSULE_ANM_effCoin, HU_MEMNUM_OVL));
    work->anim = anim;
    work->modelId = mdlId = MB2_ParticleCreate(anim, 256);
    Hu3DModelLayerSet(work->modelId, 3);
    work->num = 0;
    modelP = &Hu3DData[work->modelId];
    partP = modelP->hookData;
    partP->blendMode = 1;
    partP->unk22 = 2;
}

/* 124 instructions */
static void MB2_CoinEffUpdate(OMOBJ *obj)
{
    MB2_COINEFFWORK *work = omObjGetDataAs(obj, MB2_COINEFFWORK);
    HU3DMODEL *modelP;
    MB2_PARTICLE *partP;
    MB2_PARTICLEDATA *data;
    int i;

    if(MBKillCheck() || mb2_CoinEffObj == NULL) {
        Hu3DModelKill(work->modelId);
        work->modelId = -1;
        HuSprAnimKill(work->anim);
        work->anim = NULL;
        omDelObjEx(mbObjMan, obj);
        mb2_CoinEffObj = NULL;
        return;
    }
    if(work->num <= 0) {
        Hu3DModelAttrSet(work->modelId, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(work->modelId, HU3D_ATTR_DISPOFF);
    modelP = &Hu3DData[work->modelId];
    partP = modelP->hookData;
    data = partP->data;
    partP->unk23 = 0;
    for(i=0; i<partP->num; i++, data++) {
        if(data->scale <= 0) {
            continue;
        }
        data->pos.x += data->vel.x;
        data->pos.y += data->vel.y;
        data->pos.z += data->vel.z;
        if(data->unk24) {
            data->vel.y -= data->unk24;
        }
        data->scale = data->unk14*data->unk18;
        data->unk18 -= data->unk1C;
        if(data->unk18 <= 0) {
            data->unk54 = 0;
            data->time = 0;
            data->scale = 0;
            work->num--;
        }
    }
}

/* 5 instructions */
static void MB2_CoinEffClose(void)
{
    mb2_CoinEffObj = NULL;
}

/* 20 instructions */
static int MB2_CoinEffNumGet(void)
{
    OMOBJ *obj = mb2_CoinEffObj;
    MB2_COINEFFWORK *work;

    if(mb2_CoinEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB2_COINEFFWORK);
    return work->num;
}

/* 29 instructions */
static void MB2_CoinEffBlendModeSet(int blendMode)
{
    OMOBJ *obj = mb2_CoinEffObj;
    MB2_COINEFFWORK *work;
    MB2_PARTICLE *partP;
    HU3DMODEL *modelP;

    if(mb2_CoinEffObj == NULL) {
        return;
    }
    work = omObjGetDataAs(obj, MB2_COINEFFWORK);
    modelP = &Hu3DData[work->modelId];
    partP = modelP->hookData;
    partP->blendMode = blendMode;
}

/* 119 instructions */
static int MB2_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color)
{
    OMOBJ *obj;
    MB2_COINEFFWORK *work;
    HU3DMODEL *modelP;
    MB2_PARTICLE *partP;
    MB2_PARTICLEDATA *data;
    int i;

    if(mb2_CoinEffObj == NULL) {
        return -1;
    }
    obj = mb2_CoinEffObj;
    work = omObjGetDataAs(obj, MB2_COINEFFWORK);
    modelP = &Hu3DData[work->modelId];
    partP = modelP->hookData;
    for(data = partP->data, i=0; i<partP->num; i++, data++) {
        if(data->scale <= 0) {
            break;
        }
    }
    if(i >= partP->num) {
        return -1;
    }
    data->time = data->unk02 = 0;
    data->pos.x = pos->x;
    data->pos.y = pos->y;
    data->pos.z = pos->z;
    data->vel.x = vel->x;
    data->vel.y = vel->y;
    data->vel.z = vel->z;
    data->unk14 = scale;
    data->unk18 = 1;
    data->unk1C = decay;
    data->unk24 = gravity;
    data->scale = scale;
    data->color = *color;
    data->rot.z = 360*MB2_RandF();
    data->unk54 = 0;
    data->time = 0;
    work->num++;
    return i;
}

/* 276 instructions
 *
 * `gravity` is assigned in all three arms of the switch and never read -- the
 * call passes a literal 0 for MB2_CoinEffCreate's gravity. It is the disc's,
 * and the function is two instructions short without it.
 */
static int MB2_CoinEffCreateRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no)
{
    GXColor colRand;
    GXColor col;
    HuVecF posRand;
    HuVecF velRand;
    HuVecF posOut;
    HuVecF vel;
    GXColor *colP;
    HuVecF *velP;
    HuVecF *posP;
    float rate;
    float gravity;

    if(mb2_CoinEffObj == NULL) {
        return -1;
    }
    posRand.x = pos->x+rangeX*(-0.5f+MB2_RandF());
    posRand.y = pos->y+rangeY*(-0.5f+MB2_RandF());
    posRand.z = pos->z+ofsZ;
    velRand.x = 0;
    velRand.z = 0;
    switch(no) {
    case 1:
        velRand.y = -1*(1+(0.2f*MB2_RandF()));
        gravity = 0;
        break;

    case 2:
        velRand.y = 1+(0.2f*MB2_RandF());
        gravity = 0.1f;
        break;

    default:
        velRand.y = 0;
        gravity = 0;
        break;
    }
    rate = MB2_RandF();
    colRand.r = 192+(63*rate);
    colRand.g = 192+(63*rate);
    colRand.b = 192+(63*rate);
    colRand.a = 192+(63*MB2_RandF());
    col = colRand;
    colP = &col;
    vel = velRand;
    velP = &vel;
    posOut = posRand;
    posP = &posOut;
    return MB2_CoinEffCreate(posP, velP, scale, decay, 0, colP);
}

/* 211 instructions -- MB2_CoinEffCreateRand with the colour taken from a
 * seven-entry table instead of randomised per channel. `gravity` is the same
 * dead local. */
static int MB2_CoinEffCreateColRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no)
{
    GXColor col;
    HuVecF posRand;
    HuVecF velRand;
    HuVecF posOut;
    HuVecF vel;
    GXColor *colP;
    HuVecF *velP;
    HuVecF *posP;
    float gravity;

    if(mb2_CoinEffObj == NULL) {
        return -1;
    }
    posRand.x = pos->x+rangeX*(-0.5f+MB2_RandF());
    posRand.y = pos->y+rangeY*(-0.5f+MB2_RandF());
    posRand.z = pos->z+ofsZ;
    velRand.x = 0;
    velRand.z = 0;
    switch(no) {
    case 1:
        velRand.y = -1*(1+(0.2f*MB2_RandF()));
        gravity = 0;
        break;

    case 2:
        velRand.y = 1+(0.2f*MB2_RandF());
        gravity = 0.1f;
        break;

    default:
        velRand.y = 0;
        gravity = 0;
        break;
    }
    col = mb2ev_CoinEffColTbl[(frand() & 0x7FFF)%7];
    colP = &col;
    vel = velRand;
    velP = &vel;
    posOut = posRand;
    posP = &posOut;
    return MB2_CoinEffCreate(posP, velP, scale, decay, 0, colP);
}

/* 99 instructions */
static void MB2_SplashEffInit(void)
{
    OMOBJ *obj;
    MB2_SPLASHEFFWORK *work;
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    ANIMDATA *anim;
    int mdlId;
    int i;
    int j;

    obj = mb2_SplashEffObj = MBAddObj(32768, 0, 0, MB2_SplashEffUpdate);
    work = obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MB2_SPLASHEFFWORK), HU_MEMNUM_OVL);
    memset(work, 0, sizeof(MB2_SPLASHEFFWORK));
    anim = HuSprAnimRead(HuDataReadNum(W02_ANM_splashEff, HU_MEMNUM_OVL));
    work->anim = anim;
    for(i=0; i<2; i++) {
        work->modelId[i] = mdlId = MBEffCreate(anim, 256);
        modelP = &Hu3DData[work->modelId[i]];
        effP = modelP->hookData;
        for(data = effP->data, j=0; j<effP->num; j++, data++) {
            data->dispF = FALSE;
        }
        if(j == 0) {
            Hu3DModelLayerSet(work->modelId[i], 1);
            effP->blendMode = MB_EFFECT_BLEND_NORMAL;
        } else {
            Hu3DModelLayerSet(work->modelId[i], 2);
            effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
        }
        MBEffAttrSet(work->modelId[i], MB_EFFECT_ATTR_STOPCNT);
        work->num[i] = 0;
    }
}

/* 130 instructions */
static void MB2_SplashEffUpdate(OMOBJ *obj)
{
    MB2_SPLASHEFFWORK *work = omObjGetDataAs(obj, MB2_SPLASHEFFWORK);
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;
    int j;
    float rate;

    if(MBKillCheck() || mb2_SplashEffObj == NULL) {
        for(i=0; i<2; i++) {
            if(work->modelId[i] != -1) {
                MBEffKill(work->modelId[i]);
            }
            work->modelId[i] = -1;
        }
        omDelObjEx(mbObjMan, obj);
        mb2_SplashEffObj = NULL;
        return;
    }
    for(i=0; i<2; i++) {
        modelP = &Hu3DData[work->modelId[i]];
        effP = modelP->hookData;
        for(data = effP->data, j=0; j<effP->num; j++, data++) {
            if(data->dispF == 0) {
                continue;
            }
            PSVECAdd(&data->pos, &data->vel, &data->pos);
            data->vel.y -= data->accel.y;
            rate = (float)data->time/(float)data->parManId;
            data->time--;
            data->color.a = data->accel.z*rate;
            if(rate <= 0) {
                data->dispF = FALSE;
                work->num[i]--;
            }
        }
    }
}

/* 5 instructions */
static void MB2_SplashEffClose(void)
{
    mb2_SplashEffObj = NULL;
}

/* 22 instructions */
static int MB2_SplashEffNumGet(void)
{
    OMOBJ *obj = mb2_SplashEffObj;
    MB2_SPLASHEFFWORK *work;

    if(mb2_SplashEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB2_SPLASHEFFWORK);
    return work->num[0]+work->num[1];
}

/* 123 instructions */
static void MB2_SplashEffCreate(HuVecF *pos, HuVecF *vel, GXColor *color, int time, int no, float scale, float rotZ, float accelY)
{
    OMOBJ *obj = mb2_SplashEffObj;
    MB2_SPLASHEFFWORK *work = omObjGetDataAs(obj, MB2_SPLASHEFFWORK);
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;
    int no2;

    if(mb2_SplashEffObj == NULL) {
        return;
    }
    if(no == 0) {
        modelP = &Hu3DData[work->modelId[0]];
    } else {
        modelP = &Hu3DData[work->modelId[1]];
    }
    effP = modelP->hookData;
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->dispF == 0) {
            break;
        }
    }
    if(i >= effP->num) {
        return;
    }
    data->time = data->parManId = time;
    data->pos = *pos;
    data->scale = scale;
    data->color = *color;
    data->rot.z = rotZ;
    data->animBank = 0;
    data->animNo = 0;
    data->animSpeed = 0;
    data->animTime = 0;
    data->dispF = TRUE;
    if(vel == NULL) {
        data->vel.x = data->vel.y = data->vel.z = 0;
    } else {
        data->vel = *vel;
    }
    data->accel.y = accelY;
    data->accel.z = color->a;
    if(no == 0) {
        no2 = 0;
    } else {
        no2 = 1;
    }
    work->num[no2]++;
}

/* 150 instructions */
static void MB2_SplashEffCreateRandX(HuVecF *pos, GXColor *color, float scale, int no)
{
    HuVecF vel;
    GXColor col;
    GXColor *colP;
    int time;
    float rotZ;

    vel.x = 0;
    vel.z = 0;
    vel.y = 5*(0.8f+(0.1f*MB2_RandF()));
    col = *color;
    colP = &col;
    time = 60*(0.25f+(0.05f*MB2_RandF()));
    rotZ = 360*MB2_RandF();
    MB2_SplashEffCreate(pos, &vel, colP, time, no, scale*(100*(0.75f+(0.5f*MB2_RandF()))), rotZ, 0.8166667f);
}

/* 302 instructions */
static HU3DMODELID MB2_ParticleCreate(ANIMDATA *anim, s16 maxCnt)
{
    HU3DMODELID modelId = Hu3DHookFuncCreate(ParticleDraw);
    MB2_PARTICLEDATA *partData;
    s16 i;
    MB2_PARTICLE *partP;
    HU3DMODEL *modelP;
    HuVecF *vertex;
    HuVec2f *st;
    void *dl;
    void *dlP;

    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    modelP = &Hu3DData[modelId];
    modelP->hookData = partP = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MB2_PARTICLE), modelP->mallocNo);
    partP->anim = anim;
    partP->num = maxCnt;
    partP->blendMode = 0;
    partP->unk22 = 0;
    partP->hook = NULL;
    partP->linkModelP = NULL;
    partP->unk28 = 0;
    partP->unk21 = 0;
    partP->unk23 = 0;
    partP->unk30 = 0;
    partP->mode = partP->time = 0;
    partP->data = partData = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(MB2_PARTICLEDATA), modelP->mallocNo);
    memset(partData, 0, maxCnt*sizeof(MB2_PARTICLEDATA));
    for(i=0; i<maxCnt; i++, partData++) {
        partData->scale = 0;
        partData->rot.x = partData->rot.y = partData->rot.z = 0;
        partData->unk2C = 0;
        partData->unk30 = 1;
        partData->pos.x = ((frand() & 0x7F)-64)*20;
        partData->pos.y = ((frand() & 0x7F)-64)*30;
        partData->pos.z = ((frand() & 0x7F)-64)*20;
        partData->color.r = partData->color.g = partData->color.b = partData->color.a = 255;
        partData->unk54 = 0;
    }
    partP->vertex = vertex = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(HuVecF)*4, modelP->mallocNo);
    for(i=0; i<maxCnt*4; i++, vertex++) {
        vertex->x = vertex->y = vertex->z = 0;
    }
    partP->st = st = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(HuVec2f)*4, modelP->mallocNo);
    for(i=0; i<maxCnt; i++) {
        st->x = 0;
        st->y = 0;
        st++;
        st->x = 1;
        st->y = 0;
        st++;
        st->x = 1;
        st->y = 1;
        st++;
        st->x = 0;
        st->y = 1;
        st++;
    }
    dl = HuMemDirectMallocNum(HEAP_MODEL, 0x10000, modelP->mallocNo);
    dlP = dl;
    DCFlushRange(dl, 0x10000);
    GXBeginDisplayList(dlP, 0x10000);
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
    partP->dlSize = GXEndDisplayList();
    partP->dl = HuMemDirectMallocNum(HEAP_MODEL, partP->dlSize, modelP->mallocNo);
    memcpy(partP->dl, dl, partP->dlSize);
    DCFlushRange(partP->dl, partP->dlSize);
    HuMemDirectFree(dl);
    return modelId;
}

/* 209 instructions
 *
 * MB2_ParticleCreate again, for a second manager that shares the first one's
 * display list and texture: `dlSize` and `dl` are copied straight across at
 * the end rather than rebuilt, so this costs no GXBeginDisplayList. It also
 * skips the `memset` of the particle array and the `unk23` store that the
 * original has -- both are the disc's.
 */
static HU3DMODELID MB2_ParticleCopy(HU3DMODELID srcMdlId)
{
    HU3DMODEL *srcModelP = &Hu3DData[srcMdlId];
    HU3DMODEL *modelP;
    MB2_PARTICLE *srcPartP = srcModelP->hookData;
    HU3DMODELID modelId = Hu3DHookFuncCreate(srcModelP->hookFunc);
    MB2_PARTICLEDATA *partData;
    s16 i;
    MB2_PARTICLE *partP;
    HuVecF *vertex;
    HuVec2f *st;
    int maxCnt;

    Hu3DModelCameraSet(modelId, HU3D_CAM0);
    modelP = &Hu3DData[modelId];
    modelP->hookData = partP = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MB2_PARTICLE), modelP->mallocNo);
    partP->anim = srcPartP->anim;
    partP->num = srcPartP->num;
    maxCnt = partP->num;
    partP->blendMode = 0;
    partP->unk22 = srcPartP->unk22;
    partP->hook = NULL;
    partP->linkModelP = NULL;
    partP->unk28 = 0;
    partP->unk21 = 0;
    partP->unk30 = 0;
    partP->mode = partP->time = 0;
    partP->data = partData = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(MB2_PARTICLEDATA), modelP->mallocNo);
    for(i=0; i<maxCnt; i++, partData++) {
        partData->scale = 0;
        partData->rot.x = partData->rot.y = partData->rot.z = 0;
        partData->unk2C = 0;
        partData->unk30 = 1;
        partData->pos.x = ((frand() & 0x7F)-64)*20;
        partData->pos.y = ((frand() & 0x7F)-64)*30;
        partData->pos.z = ((frand() & 0x7F)-64)*20;
        partData->color.r = partData->color.g = partData->color.b = partData->color.a = 255;
        partData->unk54 = 0;
    }
    partP->vertex = vertex = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(HuVecF)*4, modelP->mallocNo);
    for(i=0; i<maxCnt*4; i++, vertex++) {
        vertex->x = vertex->y = vertex->z = 0;
    }
    partP->st = st = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(HuVec2f)*4, modelP->mallocNo);
    for(i=0; i<maxCnt; i++) {
        st->x = 0;
        st->y = 0;
        st++;
        st->x = 1;
        st->y = 0;
        st++;
        st->x = 1;
        st->y = 1;
        st++;
        st->x = 0;
        st->y = 1;
        st++;
    }
    partP->dlSize = srcPartP->dlSize;
    partP->dl = srcPartP->dl;
    return modelId;
}

/* 656 instructions
 *
 * The draw hook every MB2_PARTICLE manager is created with. One quad per live
 * particle, billboarded through the inverse of the camera matrix, with three
 * spellings of the same thing chosen by `unk22`: a full 3-axis rotation, the
 * common case of no rotation at all, and a Z-only spin composed onto the
 * billboard.
 *
 * `partP->unk28 = 0` just before `partP->unk28 = partP->unk30` at the bottom
 * is dead, and it is the disc's.
 */
static void ParticleDraw(HU3DMODEL *modelP, Mtx *mtx)
{
    static HuVecF vtxTbl[4] = {
        { -0.5f,  0.5f, 0 },
        {  0.5f,  0.5f, 0 },
        {  0.5f, -0.5f, 0 },
        { -0.5f, -0.5f, 0 },
    };
    static HuVec2f uvTbl[4] = {
        { 0,    0    },
        { 0.25f, 0    },
        { 0.25f, 0.25f },
        { 0,    0.25f },
    };
    MB2_PARTICLE *partP;
    MB2_PARTICLEDATA *partData;
    HuVecF *vertex;
    HuVec2f *st;
    HuVecF *vecP;
    s16 i;
    s16 j;
    HuVecF *vtxP;
    s16 fmt;
    s16 u;
    s16 v;
    MB2PARTICLEHOOK hook;
    Mtx mtxA;
    Mtx mtxC;
    Mtx mtxD;
    HuVecF vec[4];
    HuVecF out[4];
    HuVecF vtx[4];
    ROMtx mtxB;

    partP = modelP->hookData;
    if(shadowModelDrawF) {
        return;
    }
    if(partP->linkModelP && partP->linkModelP != modelP) {
        ParticleDraw(partP->linkModelP, mtx);
    }
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    if(shadowModelDrawF) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ONE, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
        GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
    } else {
        fmt = partP->anim->bmp->dataFmt & 0xF;
        if(fmt == 7 || fmt == 8) {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ONE, GX_CC_RASC, GX_CC_ZERO);
        } else {
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
        }
        if(partP->unk22 & 1) {
            GXSetZMode(GX_FALSE, GX_LEQUAL, GX_FALSE);
        } else if(modelP->attr & HU3D_ATTR_ZWRITE_OFF) {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
        } else {
            GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
        }
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(partP->anim, 0, 0, 1, 1, 1);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    switch(partP->blendMode) {
    case 0:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        break;

    case 1:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
        break;

    case 2:
        GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCALPHA, GX_LO_NOOP);
        break;
    }
    if(HmfInverseMtxF3X3(*mtx, mtxA) == 0) {
        PSMTXIdentity(mtxA);
    }
    PSMTXReorder(mtxA, mtxB);
    if(partP->hook) {
        hook = partP->hook;
        hook(modelP, partP, mtx);
    }
    partData = partP->data;
    vertex = partP->vertex;
    st = partP->st;
    if(partP->unk22 & 4) {
        PSMTXIdentity(mtxA);
        PSMTXIdentity((MtxPtr)mtxB);
        vtx[0] = vtxTbl[0];
        vtx[1] = vtxTbl[1];
        vtx[2] = vtxTbl[2];
        vtx[3] = vtxTbl[3];
    } else {
        PSMTXROMultVecArray(mtxB, vtxTbl, vtx, 4);
    }
    for(i=0; i<partP->num; i++, partData++) {
        if(!partData->scale) {
            vertex->x = vertex->y = vertex->z = 0;
            vertex++;
            vertex->x = vertex->y = vertex->z = 0;
            vertex++;
            vertex->x = vertex->y = vertex->z = 0;
            vertex++;
            vertex->x = vertex->y = vertex->z = 0;
            vertex++;
        } else if(partP->unk22 & 8) {
            PSVECScale(&vtxTbl[0], &vec[0], partData->scale);
            PSVECScale(&vtxTbl[1], &vec[1], partData->scale);
            PSVECScale(&vtxTbl[2], &vec[2], partData->scale);
            PSVECScale(&vtxTbl[3], &vec[3], partData->scale);
            mtxRot(mtxC, partData->rot.x, partData->rot.y, partData->rot.z);
            PSMTXMultVecArray(mtxC, vec, out, 4);
            PSVECAdd(&out[0], &partData->pos, vertex++);
            PSVECAdd(&out[1], &partData->pos, vertex++);
            PSVECAdd(&out[2], &partData->pos, vertex++);
            PSVECAdd(&out[3], &partData->pos, vertex++);
        } else if(!partData->rot.z) {
            vecP = vec;
            vtxP = vtx;
            PSVECScale(vtxP++, vecP, partData->scale);
            PSVECAdd(vecP++, &partData->pos, vertex++);
            PSVECScale(vtxP++, vecP, partData->scale);
            PSVECAdd(vecP++, &partData->pos, vertex++);
            PSVECScale(vtxP++, vecP, partData->scale);
            PSVECAdd(vecP++, &partData->pos, vertex++);
            PSVECScale(vtxP++, vecP, partData->scale);
            PSVECAdd(vecP++, &partData->pos, vertex++);
        } else {
            PSVECScale(&vtxTbl[0], &vec[0], partData->scale);
            PSVECScale(&vtxTbl[1], &vec[1], partData->scale);
            PSVECScale(&vtxTbl[2], &vec[2], partData->scale);
            PSVECScale(&vtxTbl[3], &vec[3], partData->scale);
            PSMTXRotRad(mtxD, 'Z', partData->rot.z);
            PSMTXConcat(mtxA, mtxD, mtxC);
            PSMTXMultVecArray(mtxC, vec, out, 4);
            PSVECAdd(&out[0], &partData->pos, vertex++);
            PSVECAdd(&out[1], &partData->pos, vertex++);
            PSVECAdd(&out[2], &partData->pos, vertex++);
            PSVECAdd(&out[3], &partData->pos, vertex++);
        }
    }
    partData = partP->data;
    st = partP->st;
    if((partP->unk22 & 2) == 0) {
        for(i=0; i<partP->num; i++, partData++) {
            u = partData->unk54 & 3;
            v = (partData->unk54 >> 2) & 3;
            for(j=0; j<4; j++, st++) {
                st->x = (0.25f*u)+uvTbl[j].x;
                st->y = (0.25f*v)+uvTbl[j].y;
            }
        }
    } else {
        for(i=0; i<partP->num; i++, partData++) {
            for(j=0; j<4; j++, st++) {
                st->x = 4*uvTbl[j].x;
                st->y = 4*uvTbl[j].y;
            }
        }
    }
    DCFlushRangeNoSync(partP->vertex, partP->num*sizeof(HuVecF)*4);
    DCFlushRangeNoSync(partP->st, partP->num*sizeof(HuVec2f)*4);
    DCFlushRangeNoSync(partP->data, partP->num*sizeof(MB2_PARTICLEDATA));
    PPCSync();
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, partP->vertex, sizeof(HuVecF));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, &partP->data->color, sizeof(MB2_PARTICLEDATA));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, partP->st, sizeof(HuVec2f));
    GXCallDisplayList(partP->dl, partP->dlSize);
    if(shadowModelDrawF) {
        return;
    }
    if((partP->unk21 & 2) == 0) {
        partP->unk28++;
    }
    if(partP->unk30 != 0 && partP->unk30 <= partP->unk28) {
        if(partP->unk21 & 1) {
            partP->unk28 = 0;
        }
        partP->unk28 = partP->unk30;
    }
}

/* 146 instructions */
static void MB2_YajiInit(HuVecF *pos)
{
    OMOBJ *obj;
    MB2_YAJIWORK *work;
    int i;
    float angle;
    float z;

    obj = mb2_YajiObj = MBAddObj(32768, 3, 0, MB2_YajiUpdate);
    work = obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MB2_YAJIWORK), HU_MEMNUM_OVL);
    work->time = 0;
    for(i=0; i<3; i++) {
        angle = yajiAngleTbl[i];
        obj->mdlId[i] = Hu3DModelCreate(HuDataSelHeapReadNum(BOARD_HSF_yaji, HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelCameraSet(obj->mdlId[i], 1);
        Hu3DModelAttrSet(obj->mdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(obj->mdlId[i], 3);
        z = pos->z+3*(100*HuCos(angle));
        Hu3DModelPosSet(obj->mdlId[i], pos->x+3*(100*HuSin(angle)), 100+pos->y, z);
        Hu3DModelRotSet(obj->mdlId[i], 0, angle, 0);
    }
    obj->work[0] = 1;
    obj->stat |= OM_STAT_MODELPAUSE;
}

/* 137 instructions */
static void MB2_YajiUpdate(OMOBJ *obj)
{
    HU3DMODEL *modelP;
    MB2_YAJIWORK *work = omObjGetDataAs(obj, MB2_YAJIWORK);
    int i;
    float scale;
    double av;
    double value;

    if(MBKillCheck() || mb2_YajiObj == NULL) {
        omDelObjEx(mbObjMan, obj);
        mb2_YajiObj = NULL;
        return;
    }
    for(i=0; i<3; i++) {
        modelP = &Hu3DData[obj->mdlId[i]];
        scale = modelP->scale.z;
        if(modelP->attr & HU3D_ATTR_DISPOFF) {
            continue;
        }
        if(obj->work[0] == i) {
            work->time += 6;
            value = HuSin(work->time%360);
            av = fabs(value);
            scale = 2+av;
        } else {
            if(scale > 2.0f) {
                scale -= 0.1f;
            }
            if(scale < 2.0f) {
                scale += 0.1f;
            }
        }
        Hu3DModelScaleSet(obj->mdlId[i], scale, scale, scale);
    }
}

/* 5 instructions */
static void MB2_YajiClose(void)
{
    mb2_YajiObj = NULL;
}

/* 20 instructions */
static void MB2_YajiHiliteSet(int no)
{
    OMOBJ *obj = mb2_YajiObj;
    MB2_YAJIWORK *work = omObjGetDataAs(obj, MB2_YAJIWORK);

    if(mb2_YajiObj == NULL) {
        return;
    }
    obj->work[0] = no;
    work->time = 0;
}

/* 45 instructions */
static void MB2_YajiDispSet(int dispF)
{
    OMOBJ *obj = mb2_YajiObj;
    int i;
    MB2_YAJIWORK *work = omObjGetDataAs(obj, MB2_YAJIWORK);

    if(mb2_YajiObj == NULL) {
        return;
    }
    for(i=0; i<3; i++) {
        if(dispF) {
            Hu3DModelAttrReset(obj->mdlId[i], HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(obj->mdlId[i], HU3D_ATTR_DISPOFF);
        }
    }
    work->time = 0;
}

/* 84 instructions */
static void MB2_RainbowObjInit(void)
{
    OMOBJ *obj;
    MB2_RAINBOWWORK *work;
    MB2_RAINBOWDATA *data;
    HU3DMODEL *modelP;
    int i;

    obj = mb2_RainbowObj = MBAddObj(32768, 0, 0, MB2_RainbowObjUpdate);
    work = obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MB2_RAINBOWWORK), HU_MEMNUM_OVL);
    memset(work, 0, sizeof(MB2_RAINBOWWORK));
    work->modelId = Hu3DHookFuncCreate(RainbowObjDraw);
    Hu3DModelCameraSet(work->modelId, 1);
    Hu3DModelLayerSet(work->modelId, 3);
    modelP = &Hu3DData[work->modelId];
    modelP->pos.y = -100000;
    modelP->pos.z = -100000;
    modelP->hookData = work;
    work->anim = mb2_Work.rainbowAnim;
    data = work->data = HuMemDirectMallocNum(HEAP_MODEL, 8*sizeof(MB2_RAINBOWDATA), modelP->mallocNo);
    memset(data, 0, 8*sizeof(MB2_RAINBOWDATA));
    for(i=0; i<8; i++, data++) {
        data->useF = 0;
    }
}

/* 46 instructions */
static void MB2_RainbowObjUpdate(OMOBJ *obj)
{
    MB2_RAINBOWWORK *work = omObjGetDataAs(obj, MB2_RAINBOWWORK);
    MB2_RAINBOWDATA *data;
    int i;

    if(MBKillCheck() || mb2_RainbowObj == NULL) {
        Hu3DModelKill(work->modelId);
        omDelObjEx(mbObjMan, obj);
        mb2_RainbowObj = NULL;
        return;
    }
    for(data = work->data, i=0; i<8; i++, data++) {
    }
}

/* 5 instructions */
static void MB2_RainbowObjClose(void)
{
    mb2_RainbowObj = NULL;
}

/* 744 instructions
 *
 * Takes the board's control points, Catmull-Roms three samples per segment
 * into data->pos, derives a pitch/yaw pair per sample into data->rot, and
 * builds a 75-unit-wide triangle strip out of them -- two vertices per
 * sample, fading to transparent over the first and last five.
 *
 * The reverse-winding branch interleaves its indices 2i+1, 2i, 2i+1, 2i,
 * 2i+1, 2i where the forward one is 2i, 2i, 2i, 2i+1, 2i+1, 2i+1, so each
 * vertex there takes its colour from the *other* one. That is the disc's; the
 * three GX*1x16 calls all compile to one FIFO store, so only the index
 * sequence is recoverable and it is transcribed as it stands.
 */
static int MB2_RainbowObjCreate(HuVecF *point, int num, int reverseF)
{
    MB2_RAINBOWDATA *data;
    int i;
    GXColor *colorP;
    HuVecF *posP;
    HU3DMODEL *modelP;
    HuVec2f *stP;
    MB2_RAINBOWWORK *work;
    int j;
    void *buf;
    OMOBJ *obj;
    int no;
    void *dlBuf;
    HuVecF vec;
    HuVecF p0;
    HuVecF p1;
    HuVecF p2;
    HuVecF p3;
    float t;
    float mag;

    obj = mb2_RainbowObj;
    if(mb2_RainbowObj == NULL) {
        return -1;
    }
    work = omObjGetDataAs(obj, MB2_RAINBOWWORK);
    data = work->data;
    modelP = &Hu3DData[work->modelId];
    for(i=0; i<8; i++, data++) {
        if(data->useF == 0) {
            break;
        }
    }
    if(i >= 8) {
        return -1;
    }
    no = i;
    data->useF = 1;
    posP = data->pos = HuMemDirectMallocNum(HEAP_MODEL, (num*3)*sizeof(HuVecF), modelP->mallocNo);
    memset(data->pos, 0, (num*3)*sizeof(HuVecF));
    for(i=0; i<num-1; i++) {
        if(i > 0) {
            p0 = point[i-1];
        } else {
            p0 = point[i];
        }
        p1 = point[i];
        p2 = point[i+1];
        if(i < num-2) {
            p3 = point[i+2];
        } else {
            p3 = point[i+1];
        }
        for(j=0; j<3; j++) {
            t = j/3.0f;
            MB2_HermiteCalcV(t, (float *)&p0, (float *)&p1, (float *)&p2, (float *)&p3, (float *)posP);
            posP++;
        }
    }
    num = (num-1)*3;
    data->num = num;
    data->rot = HuMemDirectMallocNum(HEAP_MODEL, num*sizeof(HuVecF), modelP->mallocNo);
    memset(data->rot, 0, num*sizeof(HuVecF));
    for(i=0; i<num; i++) {
        if(i < num-1) {
            PSVECSubtract(&data->pos[i+1], &data->pos[i], &vec);
        }
        mag = vec.x*vec.x+vec.z*vec.z;
        data->rot[i].x = 180*(atan2(sqrtf(mag), vec.y)/M_PI);
        data->rot[i].y = 180*(atan2(vec.x, vec.z)/M_PI);
        data->rot[i].z = 0;
    }
    data->col.r = data->col.g = data->col.b = data->col.a = 255;
    posP = data->vtx = HuMemDirectMallocNum(HEAP_MODEL, (num*sizeof(HuVecF))*2, modelP->mallocNo);
    memset(data->vtx, 0, num*sizeof(HuVecF));
    stP = data->st = HuMemDirectMallocNum(HEAP_MODEL, (num*sizeof(HuVec2f))*2, modelP->mallocNo);
    memset(data->st, 0, num*sizeof(HuVec2f));
    colorP = data->color = HuMemDirectMallocNum(HEAP_MODEL, (num*sizeof(GXColor))*2, modelP->mallocNo);
    memset(data->color, 0, num*sizeof(GXColor));
    for(i=0; i<num; i++) {
        posP->x = data->pos[i].x+75*HuSin(90+data->rot[i].y);
        posP->z = data->pos[i].z+75*HuCos(90+data->rot[i].y);
        posP->y = data->pos[i].y;
        stP->x = 0;
        stP->y = (1/(float)num)*i;
        colorP->r = colorP->g = colorP->b = 0xC0;
        if(i < 5) {
            colorP->a = 192*(i/5.0f);
        } else if(i > num-5) {
            colorP->a = 192*((5-(i-(num-5)))/5.0f);
        } else {
            colorP->a = 0xC0;
        }
        posP++;
        stP++;
        colorP++;
        posP->x = data->pos[i].x+75*HuSin(data->rot[i].y-90);
        posP->z = data->pos[i].z+75*HuCos(data->rot[i].y-90);
        posP->y = data->pos[i].y;
        stP->x = 1;
        stP->y = (1/(float)num)*i;
        colorP->r = colorP->g = colorP->b = 0xFF;
        if(i < 5) {
            colorP->a = 192*(i/5.0f);
        } else if(i > num-5) {
            colorP->a = 192*((5-(i-(num-5)))/5.0f);
        } else {
            colorP->a = 0xC0;
        }
        posP++;
        stP++;
        colorP++;
    }
    DCFlushRange(data->vtx, (num*sizeof(HuVecF))*2);
    DCFlushRange(data->st, (num*sizeof(HuVec2f))*2);
    DCFlushRange(data->color, (num*sizeof(GXColor))*2);
    dlBuf = buf = HuMemDirectMallocNum(HEAP_MODEL, 0x10000, modelP->mallocNo);
    DCFlushRange(buf, 0x10000);
    GXBeginDisplayList(dlBuf, 0x10000);
    GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, num*2);
    if(reverseF == 0) {
        for(i=0; i<num; i++) {
            GXPosition1x16(i*2);
            GXColor1x16(i*2);
            GXTexCoord1x16(i*2);
            GXPosition1x16((i*2)+1);
            GXColor1x16((i*2)+1);
            GXTexCoord1x16((i*2)+1);
        }
    } else {
        for(i=num-1; i>=0; i--) {
            GXPosition1x16((i*2)+1);
            GXColor1x16(i*2);
            GXTexCoord1x16((i*2)+1);
            GXPosition1x16(i*2);
            GXColor1x16((i*2)+1);
            GXTexCoord1x16(i*2);
        }
    }
    data->dlSize = GXEndDisplayList();
    data->dl = HuMemDirectMallocNum(HEAP_MODEL, data->dlSize, modelP->mallocNo);
    memcpy(data->dl, buf, data->dlSize);
    DCFlushRange(data->dl, data->dlSize);
    HuMemDirectFree(buf);
    return no;
}

/* 23 instructions */
static void MB2_RainbowObjAlphaSet(int no, u8 alpha)
{
    MB2_RAINBOWWORK *work;
    MB2_RAINBOWDATA *data;
    OMOBJ *obj = mb2_RainbowObj;

    if(mb2_RainbowObj == NULL) {
        return;
    }
    work = omObjGetDataAs(obj, MB2_RAINBOWWORK);
    data = &work->data[no];
    data->col.a = alpha;
}

/* 25 instructions
 *
 * The NULL path falls off the end without setting r3 -- the reference has no
 * `li r3,0` there, so the guard is written as the positive form with no else.
 */
static int MB2_RainbowObjVtxTopGet(int no, HuVecF **outPos)
{
    MB2_RAINBOWDATA *data;
    MB2_RAINBOWWORK *work;
    OMOBJ *obj = mb2_RainbowObj;

    if(mb2_RainbowObj == NULL) {
        return;
    }
    work = omObjGetDataAs(obj, MB2_RAINBOWWORK);
    data = &work->data[no];
    *outPos = data->pos;
    return data->num;
}

/* 176 instructions */
static void RainbowObjDraw(HU3DMODEL *modelP, Mtx *mtx)
{
    MB2_RAINBOWWORK *work;
    MB2_RAINBOWDATA *data;
    int i;

    if(mb2_RainbowObj == NULL) {
        return;
    }
    work = modelP->hookData;
    data = work->data;
    if(shadowModelDrawF) {
        return;
    }
    PSMTXCopy(Hu3DCameraMtx, *mtx);
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A2, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    HuSprTexLoad(work->anim, 0, 0, 1, 1, 1);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    GXSetCullMode(GX_CULL_NONE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
    for(i=0, data=work->data; i<8; i++, data++) {
        if(data->useF == 0) {
            continue;
        }
        GXClearVtxDesc();
        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetArray(GX_VA_POS, data->vtx, sizeof(HuVecF));
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetArray(GX_VA_CLR0, data->color, sizeof(GXColor));
        GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetArray(GX_VA_TEX0, data->st, sizeof(HuVec2f));
        GXSetTevColor(GX_TEVREG2, data->col);
        GXCallDisplayList(data->dl, data->dlSize);
    }
}
