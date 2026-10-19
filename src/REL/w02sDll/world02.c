/*
 * w02sDll world02.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/w02sDll/asm/REL/w02sDll/world02.s.
 */

#include "REL/w02sDll.h"

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

#include "datanum/capsule.h"
#include "datanum/charmot.h"
#include "messnum/board_w02.h"
#include "game/flag.h"
#include "msm_grp.h"


#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"

/* This board's own random: seven bits divided by 127, where the DOL's
 * MBEffRandF() is sixteen bits divided by 65535. The 0.007874016f is 1/127 and
 * the `& 0x7F` shows up as `clrlwi r0,r3,25`. */
#define MB2_RandF() (0.007874016f*(frand() & 0x7F))

typedef struct MB2Zen2Data_s {
    float len;                          /* 0x00 */
    float startLen;                     /* 0x04 */
    HuVecF startPos;                    /* 0x08 */
    HuVecF endPos;                      /* 0x14 */
    HuVecF rot;                         /* 0x20 */
    HuVecF prevRot;                     /* 0x2C */
} MB2_ZEN2DATA;

/* ---- fork B types (from the twin) ---- */
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


/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 18000.0f; /* 0x10 */
static const float lbl_1_rodata_14 = -500.0f; /* 0x14 */
static const float lbl_1_rodata_18 = 0.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 1.0f; /* 0x1C */
static const float lbl_1_rodata_20 = 360.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 0.007874016f; /* 0x24 */
static const float lbl_1_rodata_28 = 12202.0f; /* 0x28 */
/* 0x30 lbl_1_rodata_30 = 4503599627370496: int->float conversion constant, compiler-generated */
static const double lbl_1_rodata_38 = 1.0; /* 0x38 */
static const double lbl_1_rodata_40 = 0.009999999776482582; /* 0x40 */
static const double lbl_1_rodata_48 = 3.141592653589793; /* 0x48 */
static const double lbl_1_rodata_50 = 180.0; /* 0x50 */
static const double lbl_1_rodata_58 = 0.0024999999441206455; /* 0x58 */
static const float lbl_1_rodata_60 = 0.03f; /* 0x60 */
static const float lbl_1_rodata_64 = 255.0f; /* 0x64 */
/* 0x68 lbl_1_rodata_68 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_70 = 45.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 1000.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 250000.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 0.3f; /* 0x7C */
static const float lbl_1_rodata_80 = -3700.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 18100.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 21300.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 3700.0f; /* 0x8C */
static const float lbl_1_rodata_90 = -18100.0f; /* 0x90 */
static const float lbl_1_rodata_94 = -21300.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 8.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 30.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 20.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 100.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 0.2f; /* 0xA8 */
static const float lbl_1_rodata_AC = 0.1f; /* 0xAC */
static const float lbl_1_rodata_B0 = 0.016666668f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 0.5f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 150.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 60.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 200.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = -1.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 300.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 3000.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 24.0f; /* 0xD0 */
static const double lbl_1_rodata_D8 = 200.0; /* 0xD8 */
static const float lbl_1_rodata_E0 = 180.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 27.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 0.25f; /* 0xE8 */
static const float lbl_1_rodata_EC = 15.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 25.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 50.0f; /* 0xF4 */
static const double lbl_1_rodata_F8 = 8.0; /* 0xF8 */
static const double lbl_1_rodata_100 = 45.0; /* 0x100 */
static const float lbl_1_rodata_108 = -45.0f; /* 0x108 */
static const double lbl_1_rodata_110 = 0.5; /* 0x110 */
static const double lbl_1_rodata_118 = 3.0; /* 0x118 */
static const double lbl_1_rodata_120 = 2.0; /* 0x120 */
static const double lbl_1_rodata_128 = 100.0; /* 0x128 */
static const float lbl_1_rodata_130 = 10.0f; /* 0x130 */
static const float lbl_1_rodata_134 = 30.000002f; /* 0x134 */
static const float lbl_1_rodata_138 = 250.0f; /* 0x138 */
static const float lbl_1_rodata_13C = -180.0f; /* 0x13C */
static const double lbl_1_rodata_140 = 360.0; /* 0x140 */
static const double lbl_1_rodata_148 = 0.0; /* 0x148 */
static const float lbl_1_rodata_150 = 170.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 22.5f; /* 0x154 */
static const float lbl_1_rodata_158 = 2.5f; /* 0x158 */
static const float lbl_1_rodata_15C = 90.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 192.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 63.0f; /* 0x164 */
static const float lbl_1_rodata_168 = 64.0f; /* 0x168 */
static const float lbl_1_rodata_16C = -0.5f; /* 0x16C */
static const float lbl_1_rodata_170 = 5.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 0.8f; /* 0x174 */
static const float lbl_1_rodata_178 = 0.75f; /* 0x178 */
static const float lbl_1_rodata_17C = 0.8166667f; /* 0x17C */
static const float lbl_1_rodata_180 = 0.05f; /* 0x180 */
static const float lbl_1_rodata_184 = 4.0f; /* 0x184 */
static const float lbl_1_rodata_188 = 2.0f; /* 0x188 */
static const float lbl_1_rodata_18C = -100000.0f; /* 0x18C */
static const float lbl_1_rodata_190 = 3.0f; /* 0x190 */
static const double lbl_1_rodata_198 = 75.0; /* 0x198 */

/* fork B: only the field MB2_RainbowObjInit reads (0x6C); fork A owns the full layout (0xBC here). */
typedef struct MB2Work_s {
    int objMdlId[7];                    /* 0x00 */
    int kusaMdlId[4];                   /* 0x1C */
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
    int rot[5];                         /* 0xA8 */
} MB2_WORK;

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x30 */ static MB2_WORK mb2_Work;
/* 0x2C */ static int *mb2_SaveWorkP;
/* 0x28 */ static u8 mb2_TimerObj[0x4]; /* unreferenced (alignment 4) */
/* 0x24 */ static u8 mb2_TimerValue[0x4]; /* unreferenced (alignment 4) */
/* 0x18 */ static HuVecF mb2_CoinMaxDist;
/* 0x14 */ static OMOBJ *mb2_RainbowObj;
/* 0x10 */ static OMOBJ *mb2_YajiObj;
/* 0xC */ static OMOBJ *mb2_SplashEffObj;
/* 0x8 */ static OMOBJ *mb2_CoinEffObj;
/* 0x4 */ static OMOBJ *mb2_CoinObj;
/* 0x0 */ static OMOBJ *mb2_MainObj;

static void MB2_MainObjUpdate(OMOBJ *obj);
static HSFOBJECT * objCall(HU3DMODEL *modelP, char *name, HSFOBJECT *object);
static void MB2_CoinExec(OMOBJ *obj);
static void MB2_CoinEffUpdate(OMOBJ *obj);
static void MB2_SplashEffUpdate(OMOBJ *obj);
static void ParticleDraw(HU3DMODEL *modelP, Mtx *mtx);
static void MB2_YajiUpdate(OMOBJ *obj);
static void MB2_RainbowObjUpdate(OMOBJ *obj);
static void RainbowObjDraw(HU3DMODEL *modelP, Mtx *mtx);

/* --- functions (reference order), .data placed before its first user --- */
/* 21 insns */
void ObjectSetup(void)
{
    GWPartyFSet(FALSE);
    MBObjectSetup(MBNO_WORLD_2, MB2_Create, MB2_Kill);
}

/* 0x0 */ static HuVecF mb2ev_Rainbow1VtxTbl[10] = { { 1200.0f, 1318.0f, 4600.0f }, { 1139.544f, 1360.827f, 4500.42f }, { 1077.953f, 1400.103f, 4400.1f }, { 1014.084f, 1431.451f, 4298.46f }, { 946.996f, 1448.85f, 4195.67f }, { 876.736f, 1444.483f, 4093.81f }, { 805.464f, 1414.57f, 3996.99f }, { 735.514f, 1365.811f, 3906.94f }, { 667.239f, 1306.381f, 3822.08f }, { 600.0f, 1242.0f, 3740.0f } };
/* 0x78 */ static HuVecF mb2ev_TaiyoRainbow1VtxTbl[20] = { { -200.0f, 2490.238f, 2385.0f }, { -279.208f, 2511.439f, 2455.77f }, { -358.642f, 2531.498f, 2526.62f }, { -438.518f, 2549.188f, 2597.6f }, { -519.031f, 2562.946f, 2668.73f }, { -600.27f, 2570.944f, 2739.88f }, { -682.121f, 2570.855f, 2810.73f }, { -764.052f, 2559.85f, 2880.51f }, { -844.829f, 2534.805f, 2947.83f }, { -922.261f, 2492.98f, 3010.52f }, { -993.386f, 2433.291f, 3065.88f }, { -1056.136f, 2358.414f, 3112.42f }, { -1112.065f, 2274.707f, 3152.14f }, { -1162.336f, 2185.147f, 3186.35f }, { -1208.15f, 2091.725f, 3216.3f }, { -1250.569f, 1995.741f, 3243.04f }, { -1290.479f, 1898.058f, 3267.44f }, { -1328.616f, 1799.269f, 3290.18f }, { -1365.605f, 1699.803f, 3311.86f }, { -1402.0f, 1600.0f, 3333.0f } };
/* 0x168 */ static HuVecF mb2ev_TaiyoRainbow2VtxTbl[20] = { { -0.0f, 2490.238f, 2385.0f }, { -0.0f, 2519.46f, 2516.85f }, { -0.0f, 2547.391f, 2648.99f }, { -0.0f, 2572.73f, 2781.65f }, { -0.0f, 2593.918f, 2915.02f }, { -0.0f, 2608.955f, 3049.22f }, { -0.0f, 2615.173f, 3184.09f }, { -0.0f, 2608.247f, 3318.89f }, { -0.0f, 2581.503f, 3451.02f }, { -0.0f, 2530.428f, 3575.49f }, { -0.0f, 2452.475f, 3685.08f }, { -0.0f, 2351.598f, 3774.38f }, { -0.0f, 2236.587f, 3844.93f }, { -0.0f, 2114.448f, 3902.34f }, { -0.0f, 1988.123f, 3949.95f }, { -0.0f, 1859.307f, 3990.43f }, { -0.0f, 1728.986f, 4025.84f }, { -0.0f, 1597.758f, 4057.75f }, { -0.0f, 1466.005f, 4087.44f }, { 0.0f, 1334.0f, 4116.0f } };
/* 0x258 */ static HuVecF mb2ev_TaiyoRainbow3VtxTbl[20] = { { 200.0f, 2490.238f, 2385.0f }, { 277.376f, 2510.953f, 2454.15f }, { 354.923f, 2530.593f, 2523.42f }, { 432.792f, 2548.035f, 2592.91f }, { 511.1f, 2561.975f, 2662.7f }, { 589.892f, 2570.772f, 2732.78f }, { 669.044f, 2571.663f, 2802.96f }, { 747.955f, 2561.974f, 2872.64f }, { 825.298f, 2538.336f, 2940.55f }, { 898.678f, 2497.609f, 3004.48f }, { 964.953f, 2438.594f, 3061.61f }, { 1021.661f, 2363.587f, 3109.82f }, { 1070.119f, 2278.852f, 3150.46f }, { 1112.203f, 2188.295f, 3185.28f }, { 1149.35f, 2094.015f, 3215.63f }, { 1182.792f, 1997.34f, 3242.63f }, { 1213.53f, 1899.116f, 3267.19f }, { 1242.374f, 1799.904f, 3290.04f }, { 1270.0f, 1700.098f, 3311.8f }, { 1297.0f, 1600.0f, 3333.0f } };
/* 0x348 */ static HuVecF openingRot = { -33.0f, 0.0f, 0.0f };
/* 0x354 */ static HuVecF openingOfs = { 266.0f, 2095.0f, 4317.0f };
/* 0x360 */ static float openingZoom = 7500.0f;
/* 0x364 */ static HuVecF mapViewRot = { -78.0f, 0.0f, 0.0f };
/* 0x370 */ static HuVecF mapViewPos = { 0.0f, -664.0f, 2625.0f };

/* 443 insns */
void MB2_Create(void)
{
    int boardNo = MBBoardNoGet();
    int mdlId;

    HuAudSndGrpSetSet(MSM_GRP_BD2);
    MBMasuCreate(DATANUM(DATA_w02s, 0));
    MBScrollInit(DATANUM(DATA_w02s, 21), 18000, -500);
    mb2_Work.objMdlId[2] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 7), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.objMdlId[5] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 14), NULL, FALSE);
    mb2_Work.objMdlId[6] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 6), NULL, FALSE);
    mb2_Work.objMdlId2[0] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 20), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    mb2_Work.kusaMdlId[0] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 15), NULL, FALSE);
    mb2_Work.kusaMdlId[1] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 16), NULL, FALSE);
    mb2_Work.kusaMdlId[2] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 17), NULL, FALSE);
    mb2_Work.kusaMdlId[3] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 18), NULL, FALSE);
    MBModelDispSet(mb2_Work.kusaMdlId[0], FALSE);
    MBModelDispSet(mb2_Work.kusaMdlId[1], FALSE);
    MBModelDispSet(mb2_Work.kusaMdlId[3], FALSE);
    mb2_Work.objMdlId2[11] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 8), NULL, FALSE);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb2_Work.objMdlId2[12] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 9), NULL, FALSE);
    mb2_Work.objMdlId2[15] = mdlId = MBModelCreate(DATANUM(DATA_w02s, 19), NULL, FALSE);
    mdlId = MBCapsuleColCreate(DATANUM(DATA_w02s, 22));
    mb2_Work.rainbowAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w02s, 23), HU_MEMNUM_OVL));
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
    HuDataDirClose(DATA_w02s);
    MBBranchFlagSet(MASU_FLAG_BIT(6));
    MBLightHookSet(MB2_LightSet, MB2_LightReset);
    MBMasuWalkPreHookSet(MB2Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB2Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB2Ev_MasuHatena);
    MBMasuPathCheckHookSet(MB2_MasuPathCheck);
    HuDataDirRead(DATA_capsule);
    mb2_MainObj = MBAddObj(32768, 0, 0, MB2_MainObjUpdate);
    MBOpeningViewSet(&openingRot, &openingOfs, openingZoom);
    MBMapViewCameraSet(&mapViewRot, &mapViewPos, 12202);
}

/* 42 insns */
void MB2_Kill(void)
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

/* 405 insns */
static void MB2_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;
    HSFOBJECT *objP;
    HU3DMODEL *modelP;
    int mdlId;
    int i;
    float scaleX;
    float scaleY;
    float scaleZ;

    if(MBKillCheck() || mb2_MainObj == NULL) {
        omDelObjEx(mbObjMan, mb2_MainObj);
        mb2_MainObj = NULL;
        return;
    }
    camera = MBCameraGet();
    for(i=0; i<4; i++) {
        mb2_Work.rot[i] += ((frand() & 0x7FFF)%3)+1;
        scaleX = 1+(0.01f*HuSin(mb2_Work.rot[i]));
        scaleY = 1+(0.0025f*HuSin(mb2_Work.rot[i]));
        scaleZ = 1+(0.01f*HuSin(mb2_Work.rot[i]));
        MBModelScaleSet(mb2_Work.kusaMdlId[i], scaleX, scaleY, scaleZ);
    }
    mb2_Work.rot[4] += ((frand() & 0x7FFF)%3)+1;
    scaleX = 1+(0.01f*HuSin(mb2_Work.rot[4]));
    scaleY = 1+(0.0025f*HuSin(mb2_Work.rot[4]));
    scaleZ = 1+(0.01f*HuSin(mb2_Work.rot[4]));
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
}

/* 110 insns */
void MB2_LightSet(void)
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

/* 1 insns */
void MB2_LightReset(void)
{
}

/* 32 insns */
int MB2Ev_MasuHatena(int playerNo)
{
    s16 masuId;
    MASU *masu;
    u32 flag;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    if(flag & MASU_FLAG_BIT(0)) {
        MB2Ev_HatenaTaiyo(playerNo);
    }
}

/* 1 insns */
void MB2_Stub(void)
{
}

/* 1 insns */
int MB2Ev_MasuWalkPre(int playerNo)
{
}

/* 31 insns */
int MB2Ev_MasuWalkPost(int playerNo)
{
    s16 masuId;
    MASU *masu;
    u32 flag;
    int no;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = masu->flag & MASU_FLAG_MAP;
    if(flag & MASU_FLAG_BIT(1)) {
        no = 9;
        MB2Ev_Rainbow(no, playerNo);
    }
    return 0;
}

/* 2 insns */
int MB2_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    return -1;
}

/* 0x388 */ static s32 mb2ev_RainbowNoTbl[11] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
/* 0x3B4 */ static s32 mb2ev_RainbowDirTbl[11] = { 0x0, 0x1, 0xFFFFFFFF, 0x1, 0xFFFFFFFF, 0x1, 0xFFFFFFFF, 0x1, 0xFFFFFFFF, 0x1, 0xFFFFFFFF };
/* 0x3E0 */ static HuVecF *mb2ev_RainbowVtxTbl[5] = { mb2ev_Rainbow1VtxTbl, mb2ev_Rainbow1VtxTbl, mb2ev_Rainbow1VtxTbl, mb2ev_Rainbow1VtxTbl, mb2ev_Rainbow1VtxTbl };
/* 0x3F4 */ static s32 mb2ev_RainbowVtxNumTbl[5] = { 0xA, 0xA, 0xA, 0xA, 0xA };
/* 0x408 */ static s32 mb2ev_RainbowRevF[5] = { 0x0, 0x0, 0x0, 0x0, 0x1 };

/* 1014 insns */
int MB2Ev_Rainbow(int no, int playerNo)
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
        MBWinCreateChoice(1, MESS_BOARD_W02_RAINBOW_ASK, 0, 0);
        MBTopWinAttrSet(HUWIN_ATTR_NOCANCEL);
        if(MBPlayerCoinGet(playerNo) < 10) {
            MBTopWinChoiceDisable(0);
        }
        if(GwPlayer[playerNo].comF) {
            MBComChoiceSetUp();
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
            MBCoinAddExec(playerNo, -10);
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
                    rot.y = fn_1_42FC(t, angle, targetAngle);
                    MBPlayerRotSet(playerNo, 0, rot.y, 0);
                    MBPlayerPosGet(playerNo, &vec);
                    effPos = vec;
                    effPosP = &effPos;
                    decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
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
                    rot.y = fn_1_42FC(t, angle, targetAngle);
                    MBPlayerRotSet(playerNo, 0, rot.y, 0);
                    MBPlayerPosGet(playerNo, &vec);
                    effPos2 = vec;
                    effPosP2 = &effPos2;
                    decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
                    MB2_CoinEffCreateColRand(effPosP2, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
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

/* 0x41C */ static HuVecF *mb2ev_TaiyoRainbowVtxTbl[3][3] = {
    { mb2ev_TaiyoRainbow1VtxTbl, mb2ev_TaiyoRainbow2VtxTbl, mb2ev_TaiyoRainbow3VtxTbl },
    { mb2ev_TaiyoRainbow1VtxTbl, mb2ev_TaiyoRainbow2VtxTbl, mb2ev_TaiyoRainbow3VtxTbl },
    { mb2ev_TaiyoRainbow1VtxTbl, mb2ev_TaiyoRainbow2VtxTbl, mb2ev_TaiyoRainbow3VtxTbl },
};
/* 0x440 */ static s32 mb2ev_TaiyoRainbowVtxNumTbl[3][3] = { { 20, 20, 20 }, { 20, 20, 20 }, { 20, 20, 20 } };
/* 0x464 */ static s32 mb2ev_TaiyoDestTbl[3][3] = { { 0, 1, 2 }, { 0, 1, 2 }, { 0, 1, 2 } };
/* 0x488 */ static HuVecF mb2ev_TaiyoCoinBasePos = { 0.0f, 2940.0f, -860.0f };

/* 1709 insns */
void MB2Ev_HatenaTaiyo(int playerNo)
{
    int i;
    MB2_ZEN2DATA *data;
    MASU *masu2;
    int yajiNo;
    int no;
    int fxId;
    int vtxNum;
    s16 masuId;
    int destMasuId;
    int motId;
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
    int coin;
    int lastNo;
    s16 winId;
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
        if(masu2->flag & MASU_FLAG_BIT(4)) {
            break;
        }
    }
    if(i >= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        masuTbl[0] = masuId;
    } else {
        masuTbl[0] = i;
    }
    for(i=1; i<MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu2 = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu2->flag & MASU_FLAG_BIT(3)) {
            break;
        }
    }
    if(i >= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        masuTbl[1] = masuId;
    } else {
        masuTbl[1] = i;
    }
    for(i=1; i<MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        masu2 = MBMasuGet(MASU_LAYER_DEFAULT, i);
        if(masu2->flag & MASU_FLAG_BIT(5)) {
            break;
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
    rainbowId[0] = MB2_RainbowObjCreate(mb2ev_TaiyoRainbowVtxTbl[no][0], mb2ev_TaiyoRainbowVtxNumTbl[no][0], 0);
    rainbowId[1] = MB2_RainbowObjCreate(mb2ev_TaiyoRainbowVtxTbl[no][1], mb2ev_TaiyoRainbowVtxNumTbl[no][1], 0);
    rainbowId[2] = MB2_RainbowObjCreate(mb2ev_TaiyoRainbowVtxTbl[no][2], mb2ev_TaiyoRainbowVtxNumTbl[no][2], 0);
    for(i=0; i<16; i++) {
        vec = mb2ev_TaiyoCoinBasePos;
        vec.y += 100;
        effPos = vec;
        effPosP = &effPos;
        decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
        MB2_CoinEffCreateColRand(effPosP, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 100, 0, 2);
    }
    MBMasuPlayerLightSet(playerNo, FALSE);
    HuAudFXPlay(1480);
    WipeColorSet(255, 255, 255);
    WipeCreate(1, 0, 90);
    do {
        if((frand() & 1) == 0) {
            effPos2 = mb2ev_TaiyoCoinBasePos;
            effPosP2 = &effPos2;
            decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
            MB2_CoinEffCreateColRand(effPosP2, 100*(0.2f+(0.1f*MB2_RandF())), decay, 150, 50, 0, 2);
        }
        for(i=0; i<6; i++) {
            if(MB2_RainbowObjVtxTopGet(rainbowId[(frand() & 0x7FFF)%3], &vtxTop)) {
                effPos3 = vtxTop[(frand() & 0x7FFF)%18];
                effPosP3 = &effPos3;
                decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
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
    destMasuId = masuTbl[mb2ev_TaiyoDestTbl[no][yajiNo]];
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
        if(speed < 30.000002f) {
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
        rot.x = fn_1_42FC(t, data->prevRot.x, data->rot.x);
        rot.y = fn_1_42FC(t, data->prevRot.y, data->rot.y);
        rot.z = 0;
        MBPlayerPosSetV(playerNo, &vec);
        MBPlayerRotSetV(playerNo, &rot);
        effPos4 = vec;
        effPosP4 = &effPos4;
        decay = 0.016666668f*(0.5f+(0.3f*MB2_RandF()));
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

/* 78 insns */
int MB2_RainbowMasuNoEndGet(int masuId)
{
    int linkNum;
    MASU *masu;
    int linkId;
    int i;
    int type;
    s16 linkTbl[16];

    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    type = 9;
    if(type == 2 || type == 4 || type == 6 || type == 8) {
        return -1;
    }
    if((masu->flag & 0x3E) == 0) {
        goto notFound;
    }
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    for(i=0; i<masu->linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & MASU_FLAG_BIT(6)) {
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

/* 139 insns */
void MB2_CoinDispUpdate(int playerNo, int coin, int total)
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
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
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

/* 70 insns */
float MB2_AngleDiff(float angle1, float angle2)
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

/* 148 insns */
float MB2_AngleLerp(float target, float angle, float speed)
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

/* 254 insns */
float fn_1_42FC(float rate, float angle, float target)
{
    float diff;

    diff = MB2_AngleDiff(target, angle);
    return MB2_AngleLerp(target, angle, fabs(diff*rate));
}

/* 45 insns */
int MB2_MasuLinkGet(s16 masuId, s16 *linkTbl, BOOL linkF, BOOL pathF)
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

/* 18 insns */
HSFOBJECT *MB2_ModelObjPtrGet(HU3DMODEL *modelP, char *name)
{
    HSFDATA *hsfP = modelP->hsf;

    return objCall(modelP, name, hsfP->root);
}

/* 530 insns */
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

/* 30 insns */
float MB2_BezierCalc(float t, float p0, float p1, float p2)
{
    float u = 1.0-t;
    float value;

    value = (p2*(t*t))+((p0*(u*u))+(2.0*(p1*(u*t))));
    return value;
}

/* 71 insns */
void MB2_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out)
{
    int i;

    for(i=0; i<3; i++) {
        *out++ = MB2_BezierCalc(t, *p0++, *p1++, *p2++);
    }
}

/* 37 insns */
void MB2_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11)
{
    float t2 = t*t;
    float t3 = t*t2;
    float h = (3.0*t2)-t3-t3;

    *h00 = 1.0-h;
    *h10 = h;
    *h01 = t+((t3-t2)-t2);
    *h11 = t3-t2;
}

/* 90 insns */
float fn_1_5260(float t, float p0, float p1, float p2, float p3, float tension)
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

/* 304 insns */
void MB2_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out)
{
    float rate = 0.5f;

    out[0] = fn_1_5260(t, p0[0], p1[0], p2[0], p3[0], rate);
    out[1] = fn_1_5260(t, p0[1], p1[1], p2[1], p3[1], rate);
    out[2] = fn_1_5260(t, p0[2], p1[2], p2[2], p3[2], rate);
}

/* 100 insns */
void MB2_CoinInit(void)
{
    OMOBJ *obj;
    MB2_COIN *coin;
    int i;
    int j;

    obj = mb2_CoinObj = MBAddObj(32768, 0, 0, MB2_CoinExec);
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

/* 668 insns */
static void MB2_CoinExec(OMOBJ *obj)
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
                    MB2_CoinEffCreate(posP, velP, 100*(0.3f+(0.1f*MB2_RandF())), 0.016666668f*(1+(0.5f*MB2_RandF())), 0, colP);
                }
                break;
            }
        }
    }
}

/* 5 insns */
void MB2_CoinClose(void)
{
    mb2_CoinObj = NULL;
}

/* 35 insns */
int MB2_CoinNumGet(void)
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

/* 136 insns */
int MB2_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int no)
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

/* 64 insns */
void MB2_CoinEffInit(void)
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

/* 124 insns */
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

/* 5 insns */
void MB2_CoinEffClose(void)
{
    mb2_CoinEffObj = NULL;
}

/* 20 insns */
int MB2_CoinEffNumGet(void)
{
    OMOBJ *obj = mb2_CoinEffObj;
    MB2_COINEFFWORK *work;

    if(mb2_CoinEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB2_COINEFFWORK);
    return work->num;
}

/* 29 insns */
void MB2_CoinEffBlendModeSet(int blendMode)
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

/* 119 insns */
int MB2_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color)
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

/* 276 insns */
int MB2_CoinEffCreateRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no)
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

/* 0x494 */ static GXColor mb2ev_CoinEffColTbl[7] = { { 255, 127, 127, 255 }, { 255, 127, 64, 255 }, { 255, 255, 127, 255 }, { 127, 255, 127, 255 }, { 127, 127, 255, 255 }, { 64, 64, 255, 255 }, { 255, 127, 255, 255 } };

/* 211 insns */
int MB2_CoinEffCreateColRand(HuVecF *pos, float scale, float decay, float rangeX, float rangeY, float ofsZ, int no)
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

/* 99 insns */
void MB2_SplashEffInit(void)
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
    anim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w02s, 24), HU_MEMNUM_OVL));
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

/* 130 insns */
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

/* 5 insns */
void MB2_SplashEffClose(void)
{
    mb2_SplashEffObj = NULL;
}

/* 22 insns */
int MB2_SplashEffNumGet(void)
{
    OMOBJ *obj = mb2_SplashEffObj;
    MB2_SPLASHEFFWORK *work;

    if(mb2_SplashEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB2_SPLASHEFFWORK);
    return work->num[0]+work->num[1];
}

/* 123 insns */
void MB2_SplashEffCreate(HuVecF *pos, HuVecF *vel, GXColor *color, int time, int no, float scale, float rotZ, float accelY)
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

/* 150 insns */
void MB2_SplashEffCreateRandX(HuVecF *pos, GXColor *color, float scale, int no)
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

/* 302 insns */
HU3DMODELID MB2_ParticleCreate(ANIMDATA *anim, s16 maxCnt)
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

/* 209 insns */
HU3DMODELID MB2_ParticleCopy(HU3DMODELID srcMdlId)
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

/* 656 insns */
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

/* 0x500 */ static float yajiAngleTbl[3] = { -45.0f, 0.0f, 45.0f };

/* 146 insns */
void MB2_YajiInit(HuVecF *pos)
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
        Hu3DModelPosSet(obj->mdlId[i], pos->x+3*(100*HuSin(angle)), 100+pos->y, pos->z+3*(100*HuCos(angle)));
        Hu3DModelRotSet(obj->mdlId[i], 0, angle, 0);
    }
    obj->work[0] = 1;
    obj->stat |= OM_STAT_MODELPAUSE;
}

/* 137 insns */
static void MB2_YajiUpdate(OMOBJ *obj)
{
    HU3DMODEL *modelP;
    MB2_YAJIWORK *work = omObjGetDataAs(obj, MB2_YAJIWORK);
    int i;
    float scale;
    double value;
    double av;

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
            work->time += 3;
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

/* 5 insns */
void MB2_YajiClose(void)
{
    mb2_YajiObj = NULL;
}

/* 20 insns */
void MB2_YajiHiliteSet(int no)
{
    OMOBJ *obj = mb2_YajiObj;
    MB2_YAJIWORK *work = omObjGetDataAs(obj, MB2_YAJIWORK);

    if(mb2_YajiObj == NULL) {
        return;
    }
    obj->work[0] = no;
    work->time = 0;
}

/* 45 insns */
void MB2_YajiDispSet(int dispF)
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

/* 84 insns */
void MB2_RainbowObjInit(void)
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

/* 46 insns */
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

/* 5 insns */
void MB2_RainbowObjClose(void)
{
    mb2_RainbowObj = NULL;
}

/* 744 insns */
int MB2_RainbowObjCreate(HuVecF *point, int num, int reverseF)
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

/* 23 insns */
void MB2_RainbowObjAlphaSet(int no, u8 alpha)
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

/* 25 insns */
int MB2_RainbowObjVtxTopGet(int no, HuVecF **outPos)
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

/* 176 insns */
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

