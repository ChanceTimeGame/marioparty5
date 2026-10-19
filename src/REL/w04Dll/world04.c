/*
 * w04dll -- fourth Mario Party 5 party board, "Undersea Dream". Complete.
 * Reference: build/mp5-asm/w04dll/asm/REL/w04Dll/world04.s
 * 64 game functions, 20,112 instructions (excludes _prolog and _epilog), all
 * written. 52 are byte-identical; the other twelve differ only in register
 * allocation (normalised difference 65 at worst -- see tally.py output).
 * See NOTES.md and CALLMAP.md for dependencies and verification status.
 *
 * From games/mp5:
 * ./build/tools/ninja build/GP5E01_00/src/REL/w04Dll/world04.o
 * ./tally.py w04Dll src/REL/w04dll/world04.c 20112
 */
#include "game/board/main.h"
#include "game/board/model.h"
#include "game/board/player.h"
#include "game/board/masu.h"
#include "game/board/branch.h"
#include "game/board/pause.h"
#include "game/board/capsule.h"
#include "game/board/opening.h"
#include "game/board/scroll.h"
#include "game/board/effect.h"
#include "game/board/pad.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/pad.h"
#include "datanum/board.h"
#include "game/board/audio.h"
#include "game/board/camera.h"
#include "game/board/com.h"
#include "game/board/window.h"
#include "game/board/coin.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/process.h"
#include "datanum/w04.h"
#include "datanum/capsule.h"
#include "datanum/charmot.h"
#include "messnum/board_w04.h"
#include "humath.h"
#include "math.h"

#define MB4_RandF() (0.007874016f*(frand() & 0x7F))

#define MB4EV_MASU_KIHON MASU_FLAG_BIT(0)
#define MB4EV_MASU_IRUKA MASU_FLAG_BIT(4)
#define MB4EV_MASU_BLOW MASU_FLAG_BIT(6)
#define MB4EV_MASU_BLOWDEST MASU_FLAG_BIT(7)
#define MB4EV_MASU_KAISOO MASU_FLAG_BIT(8)
#define MB4EV_MASU_PUKU MASU_FLAG_BIT(9)

static OMOBJ *mb4_MainObj;
static OMOBJ *mb4_BubbleEffObj;
static OMOBJ *mb4_CoinObj;
static OMOBJ *mb4_CoinEffObj;
static HuVecF mb4_CoinMaxDist;

typedef struct MB4BubbleEmit_s {
    int wait;
    int num;
    int time;
} MB4_BUBBLEEMIT;

/* One fish. 224 of them, laid out by MB4_SakanaInit and moved by MB4_SakanaDraw. */
typedef struct MB4Sakana_s {
    int mdlId;                     /* 0x00, -1 when the fish is a sprite */
    int effNo;                     /* 0x04, -1 when the fish is a model */
    int unk08;                     /* 0x08 */
    int unk0C;                     /* 0x0C */
    int unk10;                     /* 0x10 */
    int unk14;                     /* 0x14 */
    int unk18;                     /* 0x18 */
    int unk1C;                     /* 0x1C */
    int unk20;                     /* 0x20 */
    int unk24;                     /* 0x24 */
    int unk28;                     /* 0x28 */
    int unk2C;                     /* 0x2C */
    HuVecF pos;                    /* 0x30, the shoal's centre */
    HuVecF range;                  /* 0x3C, how far from it a fish may wander */
    HuVecF targetPos;              /* 0x48 */
    HuVecF curPos;                 /* 0x54 */
    HuVecF dir;                    /* 0x60 */
    HuVecF rot;                    /* 0x6C */
    HuVecF rot2;                   /* 0x78 */
    float unk84;                   /* 0x84 */
    float scale;                   /* 0x88 */
    float unk8C;                   /* 0x8C */
} MB4_SAKANA;                      /* 0x90 */

/*
 * Every model id here is stored word-sized even though MBModelCreate returns a
 * MBMODELID; the names follow the model's consumer where one is known, and the
 * offset otherwise. 0x00C is never written.
 */
typedef struct MB4Work_s {
    int mapMdlId;                  /* 0x000 */
    int mdlId004;                  /* 0x004 */
    int mdlId008;                  /* 0x008 */
    int unk00C;                    /* 0x00C */
    int kihonMdlId;                /* 0x010 -- MB4Ev_Kihon */
    int mdlId014;                  /* 0x014 */
    int pukuMdlId[2];              /* 0x018 */
    int irukaEvMdlId;              /* 0x020 -- MB4Ev_Iruka */
    int kaiMdlId[3];               /* 0x024 */
    int kaisooMdlId[3];            /* 0x030 -- MB4Ev_Kaisoo */
    int mdlId03C;                  /* 0x03C */
    int puku2MdlId;                /* 0x040 */
    int kihonSippMdlId;            /* 0x044 -- MB4Ev_Kihon */
    int irukaMdlId;                /* 0x048 -- MB4Ev_Iruka */
    int blowMdlId;                 /* 0x04C -- MB4Ev_Blow */
    int kihonChrMdlId;             /* 0x050 -- MB4Ev_Kihon */
    int coinLinkMdlId;             /* 0x054 */
    int mapViewMdlId;              /* 0x058 */
    MB4_BUBBLEEMIT playerBubble[4];/* 0x05C */
    MB4_BUBBLEEMIT capsuleEmit;    /* 0x08C, the capsule being animated */
    int capsuleNo;                 /* 0x098 */
    int capsuleMdlId;              /* 0x09C */
    int capsuleEndF;               /* 0x0A0 */
    int capsuleFlag;               /* 0x0A4 */
    MB4_BUBBLEEMIT storyEmit;      /* 0x0A8, the same for a story event */
    int storyCapsuleNo;            /* 0x0B4 */
    int storyMdlId;                /* 0x0B8 */
    int storyEndF;                 /* 0x0BC */
    MB4_BUBBLEEMIT bubble[13];     /* 0x0C0 */
    MB4_BUBBLEEMIT pukuBubble;     /* 0x15C */
    MB4_BUBBLEEMIT irukaBubble;    /* 0x168 */
    MB4_SAKANA sakana[14][16];     /* 0x174 */
    int sakanaEffMdlId;            /* 0x7F74 */
    int sakanaHookMdlId;           /* 0x7F78 */
} MB4_WORK;                        /* 0x7F7C */

typedef struct MB4Coin_s {
    int mdlId;
    int linkMdlId;
    int useF;
    int mode;
    float speed;
    int duration;
    int time;
    HuVecF pos;
    HuVecF rot;
    HuVecF scale;
    HuVecF startPos;
    HuVecF endPos;
    HuVecF playerPos[4];
} MB4_COIN;

typedef struct MB4SakanaTbl_s {
    HuVecF pos;
    HuVecF range;
    int num;
    int unk1C;
    int unk20;
} MB4_SAKANATBL;

typedef struct MB4CoinEffWork_s {
    int modelId;
    int num;
    ANIMDATA *anim;
} MB4_COINEFFWORK;

static MB4_WORK mb4_Work;

/* The dolphin's ride: 150 waypoints, of which MB4Ev_Iruka walks the first 100. */
static HuVecF mb4ev_IrukaPath[150] = {
    { -3260, 1270, -1300 },
    { -3314.356f, 1271.492f, -1062.65f },
    { -3361.814f, 1273.071f, -823.85f },
    { -3388.625f, 1274.898f, -581.99f },
    { -3371.477f, 1277.198f, -340.12f },
    { -3256.059f, 1280.269f, -130.79f },
    { -3033.134f, 1283.817f, -40.72f },
    { -2790.326f, 1290.23f, -31.25f },
    { -2548.234f, 1301.832f, -53.07f },
    { -2308.458f, 1320.273f, -90.99f },
    { -2070.666f, 1346.434f, -136.22f },
    { -1834.738f, 1382.24f, -184.49f },
    { -1600.934f, 1430.722f, -231.97f },
    { -1370.96f, 1498.833f, -273.18f },
    { -1147.314f, 1589.2f, -304.78f },
    { -934.89f, 1705.718f, -325.48f },
    { -741.696f, 1853.108f, -334.65f },
    { -581.809f, 2035.764f, -332.87f },
    { -480.824f, 2255.409f, -322.57f },
    { -486.804f, 2495.498f, -311 },
    { -598.449f, 2709.599f, -304.23f },
    { -775.073f, 2875.732f, -301.08f },
    { -992.903f, 2982.424f, -300.1f },
    { -1232.546f, 3014.454f, -300 },
    { -1465.683f, 2951.704f, -300 },
    { -1656.033f, 2802.635f, -300 },
    { -1778.269f, 2594.038f, -300 },
    { -1815.438f, 2354.926f, -299.86f },
    { -1782.32f, 2114.521f, -294.42f },
    { -1709.822f, 1883.671f, -270.84f },
    { -1618.333f, 1665.055f, -216.88f },
    { -1523.15f, 1464.393f, -118.87f },
    { -1441.909f, 1295.122f, 34.65f },
    { -1388.584f, 1172.842f, 237.66f },
    { -1349.713f, 1087.342f, 461.95f },
    { -1312.542f, 1025.772f, 694.48f },
    { -1265.66f, 982.637f, 929.4f },
    { -1201.722f, 950.476f, 1162 },
    { -1105.723f, 927.183f, 1384.12f },
    { -972.711f, 908.887f, 1586.6f },
    { -796.223f, 896.968f, 1753.2f },
    { -590.112f, 893.179f, 1881.23f },
    { -360.732f, 900.923f, 1960.69f },
    { -120.085f, 924.624f, 1978.21f },
    { 113.211f, 965.832f, 1929.49f },
    { 319.148f, 1023.986f, 1815.44f },
    { 484.826f, 1093.805f, 1652.25f },
    { 616.838f, 1169.116f, 1462.55f },
    { 711.024f, 1247.893f, 1252.81f },
    { 766.756f, 1328.137f, 1030.28f },
    { 769.365f, 1407.251f, 801.17f },
    { 701.752f, 1479.537f, 580.68f },
    { 544.818f, 1532.557f, 404.41f },
    { 332.466f, 1562.619f, 292.21f },
    { 96.365f, 1574.154f, 238.68f },
    { -146.315f, 1569.212f, 243.78f },
    { -378.574f, 1549.254f, 309.72f },
    { -584.056f, 1516.481f, 434.1f },
    { -736.108f, 1473.498f, 618.22f },
    { -844.663f, 1430.159f, 831.18f },
    { -908.087f, 1394.138f, 1063.15f },
    { -939.29f, 1369.422f, 1303.01f },
    { -935.546f, 1363.927f, 1545.9f },
    { -895.226f, 1386.526f, 1784.3f },
    { -813.158f, 1451.029f, 2002.51f },
    { -690.757f, 1561.891f, 2180 },
    { -538.993f, 1703.302f, 2306.2f },
    { -371.262f, 1855.287f, 2395.01f },
    { -189.231f, 2007.481f, 2448.86f },
    { 4.733f, 2151.217f, 2478.55f },
    { 214.811f, 2273.612f, 2483.52f },
    { 443.549f, 2351.796f, 2462.75f },
    { 680.212f, 2366.325f, 2412.15f },
    { 903.84f, 2314.089f, 2333.46f },
    { 1104.036f, 2215.993f, 2236.62f },
    { 1282.182f, 2090.711f, 2128.18f },
    { 1442.264f, 1950.79f, 2009.74f },
    { 1586.667f, 1804.876f, 1878.97f },
    { 1717.743f, 1659.518f, 1734.23f },
    { 1836.777f, 1520.328f, 1573.87f },
    { 1946.517f, 1390.419f, 1399.75f },
    { 2047.897f, 1271.842f, 1212.9f },
    { 2138.134f, 1164.87f, 1013.8f },
    { 2210.653f, 1069.689f, 801.96f },
    { 2259.025f, 987.097f, 578.4f },
    { 2265.702f, 924.285f, 343.84f },
    { 2226.329f, 883.431f, 107.87f },
    { 2123.892f, 874.979f, -111.65f },
    { 1976.253f, 892.501f, -303.21f },
    { 1799.48f, 928.96f, -465.93f },
    { 1606.772f, 977.256f, -606.39f },
    { 1405.264f, 1032.899f, -731.05f },
    { 1198.579f, 1093.289f, -844.6f },
    { 988.631f, 1156.891f, -950.17f },
    { 776.504f, 1222.762f, -1049.89f },
    { 562.849f, 1290.297f, -1145.19f },
    { 347.854f, 1359.367f, -1236.29f },
    { 132.24f, 1429.172f, -1325.34f },
    { -83.754f, 1499.433f, -1413.1f },
    { -300, 1570, -1500 },
    { -3100, 0, 3100 },
    { -2979.593f, 0, 3150.94f },
    { -2857.969f, 0, 3198.87f },
    { -2734.079f, 0, 3240.51f },
    { -2607.099f, 0, 3271.3f },
    { -2477.208f, 0, 3284.82f },
    { -2347.127f, 0, 3273.99f },
    { -2220.47f, 0, 3241.87f },
    { -2096.553f, 0, 3200.2f },
    { -1972.032f, 0, 3160.45f },
    { -1843.824f, 0, 3136.07f },
    { -1713.658f, 0, 3141.51f },
    { -1586.711f, 0, 3172.19f },
    { -1462.312f, 0, 3212.39f },
    { -1336.747f, 0, 3248.63f },
    { -1207.468f, 0, 3266.2f },
    { -1077.776f, 0, 3252.24f },
    { -951.905f, 0, 3217.07f },
    { -827.614f, 0, 3176.52f },
    { -701.099f, 0, 3144 },
    { -571.112f, 0, 3135.13f },
    { -442.428f, 0, 3156.55f },
    { -317.302f, 0, 3194.31f },
    { -192.745f, 0, 3234.01f },
    { -65.181f, 0, 3262.05f },
    { 65.181f, 0, 3262.05f },
    { 192.745f, 0, 3234.01f },
    { 317.301f, 0, 3194.31f },
    { 442.427f, 0, 3156.55f },
    { 571.112f, 0, 3135.13f },
    { 701.099f, 0, 3144 },
    { 827.614f, 0, 3176.52f },
    { 951.904f, 0, 3217.07f },
    { 1077.776f, 0, 3252.24f },
    { 1207.468f, 0, 3266.2f },
    { 1336.746f, 0, 3248.63f },
    { 1462.312f, 0, 3212.39f },
    { 1586.711f, 0, 3172.19f },
    { 1713.657f, 0, 3141.51f },
    { 1843.823f, 0, 3136.07f },
    { 1972.032f, 0, 3160.45f },
    { 2096.553f, 0, 3200.2f },
    { 2220.47f, 0, 3241.87f },
    { 2347.126f, 0, 3273.99f },
    { 2477.207f, 0, 3284.82f },
    { 2607.099f, 0, 3271.3f },
    { 2734.079f, 0, 3240.51f },
    { 2857.969f, 0, 3198.87f },
    { 2979.593f, 0, 3150.94f },
    { 3100, 0, 3100 },
};

static HuVecF mb4ev_KaiPosTbl[3] = {
    { 1784, 190, 1017 },
    { 1883, 190, 1116 },
    { 1983, 190, 1215 }
};

static HuVecF mb4ev_Puku2Pos = { 2041, 230, 958 };

static MB4_SAKANATBL mb4ev_SakanaTbl[14] = {
    { {    31,  321,  -171 }, 1100, 100,  700, 3, 1, 1 },
    { { -1655,  721,  2080 }, 2600, 500, 1000, 3, 0, 0 },
    { {  1125,  621,  2080 }, 2300, 500, 1000, 2, 0, 0 },
    { { -4540,  221,   591 }, 1000, 300,  800, 2, 1, 1 },
    { { -4540,  221, -1091 }, 1000, 300, 1000, 3, 1, 1 },
    { { -1523,  996, -1799 }, 1500, 250,  600, 4, 1, 1 },
    { {     0,  496, -2027 }, 1700, 500,  900, 6, 1, 1 },
    { {  1300,  896, -3027 }, 1500, 500,  900, 3, 1, 1 },
    { {  4386,  271, -1000 }, 1000, 300,  800, 3, 1, 1 },
    { {  4386,  271,     0 }, 1000, 300,  800, 2, 1, 1 },
    { { -2502,  996,   654 }, 2000, 200,  700, 2, 0, 0 },
    { {  2516, 1200,   465 }, 1900, 200,  700, 2, 0, 0 },
    { {   202, 1296,  -354 }, 2000, 200,  700, 2, 0, 0 },
    { {  2502,  696,  1254 }, 1000, 200,  700, 1, 0, 0 }
};

static HuVecF mb4ev_AkariPosTbl[2] = {
    { 2537, 600, -423 }, { 1983, 600, -652 }
};

static float mb4ev_AkariRotYTbl[2] = { -92.5f, 47.5f };

static HuVecF mb4ev_SKaiPosTbl[2] = {
    { 3427, 1450, -1786 }, { 2318, 1450, -2245 }
};

static float mb4ev_SKaiRotYTbl[2] = { -22.5f, 157.5f };

static HuVecF mb4ev_RBokPosTbl[2] = {
    { 3100, -150, 2450 }, { -3100, -150, 2450 }
};

static float mb4ev_RBokRotYTbl[2] = { 0, 0 };

static HuVecF mb4ev_SangoOPosTbl[3] = {
    { 835, -20, -490 },
    { 3980, -50, 280 },
    { 1112, 715, -2113 }
};

static HuVecF mb4ev_SangoORotTbl[3] = {
    { 0, 36, 0 },
    { -17, -160, 15 },
    { -91, -115, 87 }
};

static HuVecF mb4ev_YaziPosTbl[7] = {
    { -735, 455, -1111 },
    { -2240, 1167, -972 },
    { -3724, 1010, -1010 },
    { -2511, 515, -78 },
    { 2810, 505, -75 },
    { 1567, 555, -668 },
    { 1340, 855, -1855 }
};

static float mb4ev_YaziRotTbl[7] = { 0, 8, -12, 18, -22.5f, -18, -35 };

static HuVecF mb4ev_YaziExtPosTbl[3] = {
    { -1303, 7, 545 },
    { -3212, 387, 406 },
    { 2900, 105, 1153 }
};

static float mb4ev_YaziExtRotYTbl[3] = { 35, -30, 0 };

static HuVecF mb4ev_UeYaziPosTbl[1] = {
    { 1120, 455, -1100 }
};

static float mb4ev_UeYaziUpRotYTbl[1] = { 10 };

static HuVecF mb4ev_HasigoPosTbl[4] = {
    { -3856, 480, -32 },
    { -2610, 0, 560 },
    { 2990, 660, -650 },
    { 3300, 60, 700 }
};

static HuVecF mb4ev_HasigoRotTbl[4] = {
    { -10, -5, 0 },
    { -5, 30, 0 },
    { -5, 10, 0 },
    { -5, 15, 0 }
};

static HuVecF mb4ev_Sango1PosTbl[3] = {
    { -3900, 85, 1190 },
    { -2580, 953, -2095 },
    { -904, 367, -1707 }
};

static HuVecF mb4ev_Sango1RotTbl[3] = {
    { 0, 0, 0 },
    { -60, -135, 54 },
    { -75, -150, 78 }
};

static float mb4ev_Sango1ScaleTbl[3] = { 1, 1, 0.95f };

static HuVecF mb4ev_Sango2PosTbl[2] = {
    { -609, -84, 174 },
    { -3963, 397, -123 }
};

static HuVecF mb4ev_Sango2RotTbl[2] = {
    { -16, 180, 0 },
    { 34, 9, -14 }
};

static float mb4ev_Sango2ScaleTbl[2] = { 1, 0.7f };

static HuVecF mb4ev_Sango3PosTbl[6] = {
    { -2614, -71, 1954 },
    { -3877, -56, 1192 },
    { -2702, 1002, -1719 },
    { -1320, 692, -1024 },
    { 1570, 450, -1000 },
    { 3650, 100, 700 }
};

static HuVecF mb4ev_Sango3RotTbl[6] = {
    { 56, -7, -14 },
    { 59, -47, 12 },
    { 0, 0, 0 },
    { 87, 0, -158 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

static HuVecF mb4ev_Sango3ScaleTbl[6] = {
    { 1.2f, 1.2f, 1.2f },
    { 1.22f, 1.34f, 1.22f },
    { 1.3f, 1.3f, 1.3f },
    { 1.15f, 1.15f, 1.15f },
    { 1, 1, 1 },
    { 1, 1, 1 }
};

static HuVecF mb4ev_Sango4PosTbl[4] = {
    { -2660, 83, 1906 },
    { -2600, 985, -1485 },
    { 1800, 440, -980 },
    { 3770, 90, 880 }
};

static HuVecF mb4ev_Sango4RotTbl[4] = {
    { 31, -12, -8 },
    { 9, 23, 0 },
    { 0, 25, 0 },
    { 0, 36, 0 }
};

static float mb4ev_Sango4ScaleTbl[4] = { 1, 1.35f, 1.3f, 1.3f };

static HuVecF mb4ev_Sango5PosTbl[2] = {
    { -1407, 828, -1003 },
    { -2140, 1146, -1255 }
};

static HuVecF mb4ev_Sango5RotTbl[2] = {
    { 50, -7, 0 },
    { -76, 246, 67 }
};

static float mb4ev_Sango5ScaleTbl[2] = { 1.23f, 1.37f };

static HuVecF mb4ev_LeftSango5PosTbl[5] = {
    { -3900, 985, -1068 },
    { -2380, -109, 2013 },
    { 3215, 80, 1195 },
    { 3095, 480, 0 },
    { 3433, 1140, -1015 }
};

static HuVecF mb4ev_LeftSango5RotTbl[5] = {
    { 16, -6, 0 },
    { 42, 9, -2 },
    { 0, 0, 0 },
    { 0, 28, 0 },
    { 0, 30, 0 }
};

static float mb4ev_LeftSango5ScaleTbl[5] = { 1.17f, 1.51f, 1.5f, 1.2f, 1.3f };

static HuVecF mb4ev_Hitode1PosTbl[4] = {
    { -1452, -201, 2038 },
    { -2525, 287, 356 },
    { -2327, 298, 252 },
    { 1540, -48, 1900 }
};

static HuVecF mb4ev_Hitode1RotTbl[4] = {
    { 0, 0, 0 },
    { 90, 24, 0 },
    { 90, 31, 0 },
    { 22.5f, -42, 0 }
};

static float mb4ev_Hitode1ScaleTbl[4] = { 1, 0.57f, 0.34f, 0.6f };

static HuVecF mb4ev_Hitode2PosTbl[4] = {
    { -3313, 1497, -929 },
    { -3429, 1445, -950 },
    { -3188, 1445, -906 },
    { 1760, -85, 2080 }
};

static HuVecF mb4ev_Hitode2RotTbl[4] = {
    { 90, -10, 0 },
    { 85, -9, 29 },
    { 85, 9, 151 },
    { 27, 11, 6 }
};

static float mb4ev_Hitode2ScaleTbl[4] = { 1, 0.65f, 0.65f, 1 };

static int mb4ev_Puku2CapsuleTbl[9] = { 1, 11, 12, 13, 15, 17, 6, 25, 36 };

static HuVecF mb4ev_KaisooPosTbl[3] = {
    { -1570, 455, 57 },
    { -3071, 550, 44 },
    { -1075, 1089, -1404 }
};

static HuVecF mb4ev_KaisooRotTbl[3] = {
    { 0, 0, 0 },
    { 0, 0, 0 },
    { 0, 0, 0 }
};

static float mb4ev_KaisooScaleTbl[3] = { 1, 1, 1 };

static HuVecF openingRot = { -33, 0, 0 };
static HuVecF openingOfs = { 0, 500, 0 };
static float openingZoom = 16000;
static HuVecF mapViewRot = { -78, 0, 0 };
static HuVecF mapViewPos = { -181, -123, 80 };
static float mapViewZoom = 16171;

static HuVecF mb4ev_MasuKihonPosTbl[2] = {
    { 3100, -100, 3100 }, { -3100, -100, 3100 }
};

static HuVecF mb4ev_BubbleEmitPosTbl[13] = {
    { 3710, 240, 790 }, { 2870, 740, -160 }, { 1620, 700, -930 },
    { 2500, 160, 900 }, { 3170, 300, 1170 }, { 1940, 120, 550 },
    { 2860, 330, 760 }, { 1120, 320, 60 }, { -1470, 680, -900 },
    { -2700, 100, 2000 }, { -2780, 660, 1200 }, { -3950, 190, 780 },
    { -2000, 370, 260 }
};

static char mb4_ItemHookName[] = "itemhook_C";

/* Where each capsule character's bubbles leave its model, in joint space. */
static HuVecF mb4ev_JangoBubbleOfs = { 0, 350, 350 };
static HuVecF mb4ev_HanachanBubbleOfs = { 0, 10, 30.000002f };
static HuVecF mb4ev_HammerBroBubbleOfs = { 0, 0, 30.000002f };
static HuVecF mb4ev_PatapataBubbleOfs = { 0, 20, 40 };
static HuVecF mb4ev_KuriboBubbleOfs = { 0, 20, 40 };
static HuVecF mb4ev_BankBubbleOfs = { 0, 20, 40 };
static HuVecF mb4ev_KamekkuBubbleOfs = { 0, 20, 50 };
static HuVecF mb4ev_KokamekkuBubbleOfs = { 0, 10, 60.000004f };
static HuVecF mb4ev_UkkiBubbleOfs = { 0, 20, 50 };
static HuVecF mb4ev_JugemBubbleOfs = { 0, 20, 50 };
static HuVecF mb4ev_DuelBubbleOfs = { 0, 10, 50 };
static HuVecF mb4ev_DonkeyBubbleOfs = { 70, 40, 0 };

/* Bowser blows from both nostrils; the two rows are the two model variants. */
static HuVecF mb4ev_KoopaBubbleOfsTbl[2][2] = {
    { { -9, 30.000002f, 65 }, { 9, 30.000002f, 65 } },
    { { -9, 30.000002f, 65 }, { 9, 30.000002f, 65 } }
};


static HuVecF mb4ev_Puku2BubblePos = { -2800.0f, 300.0f, 1340.0f };
static HuVecF mb4ev_IrukaStartBubblePos = { -3320.0f, 1250.0f, -840.0f };
static HuVecF mb4ev_Puku2EmiterPos = { -2800.0f, 300.0f, 1340.0f };
static HuVecF mb4ev_PlayerBubbleOfs = { 0.0f, 0.0f, 0.0f };

static HuVecF mb4ev_IrukaBubbleOfsTbl[13] = {
    { 0, -10, 40 }, { 0, -15, 35 }, { 0, 20, 10 }, { 0, 50, 30 },
    { 0, 45, 20 }, { 0, 15, 10 }, { 0, 30, 30 }, { 0, -10, 25 },
    { 0, 0, 50 }, { 0, -20, 65 }, { 0, -20, 65 }, { 0, -20, 65 },
    { 0, -20, 65 }
};

static float mb4ev_IrukaTPLvlScaleTbl[13] = {
    1.1f, 1.0f, 0.8f, 1.1f, 1.2f, 0.7f, 0.9f, 0.8f, 0.7f, 1.2f, 1.1f, 1.1f, 1.3f
};

void ObjectSetup(void);
static void MB4_Create(void); /* 1612 instructions */
static void MB4_Kill(void); /* 21 instructions */
static void MB4_MainObjUpdate(OMOBJ *obj); /* 666 instructions */
static void MB4_LightSet(void); /* 70 instructions */
static void MB4_LightReset(void); /* 1 instructions */
static int MB4_MasuStub(void); /* 2 instructions */
static int MB4Ev_MasuWalkPre(int playerNo); /* 2 instructions */
static int MB4Ev_MasuHatena(int playerNo); /* 50 instructions */
static int MB4Ev_MasuWalkPost(int playerNo); /* 94 instructions */
static int MB4_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF); /* 2 instructions */
static void MB4Ev_IrukaBubbleCreate(int playerNo, HuVecF *ofs); /* 114 instructions */
static void MB4Ev_PlayerBubbleCreate(int playerNo); /* 114 instructions */
static void MB4Ev_Kihon(int playerNo); /* 2090 instructions */
static void MB4Ev_Iruka(int playerNo); /* 1410 instructions */
static void MB4Ev_Blow(int playerNo); /* 1188 instructions */
static void MB4Ev_Kaisoo(int playerNo); /* 1936 instructions */
static void MB4_CapsuleEffHook(int capsuleNo, int type, int mdlId, BOOL flag1, BOOL flag2, BOOL flag3); /* 1403 instructions */
static void MB4_CapsuleBubbleUpdate(void); /* 1507 instructions */
static void MB4_MapViewHook(BOOL dispF); /* 24 instructions */
static void MB4_CoinDispUpdate(int playerNo, int coins, int threshold); /* 139 instructions */
static void MB4_SakanaInit(void); /* 747 instructions */
static void MB4_SakanaDraw(HU3DMODEL *modelP, Mtx *matrix); /* 1473 instructions */
static void MB4_SakanaClose(void); /* 35 instructions */
static void MB4_SakanaOffsetInit(void); /* 45 instructions */
static void MB4_SakanaPosInit(void); /* 47 instructions */
static int MB4_SakanaCreate(int type); /* 72 instructions */
static void MB4_SakanaPosSet(int no, float x, float y, float z); /* 23 instructions */
static void MB4_SakanaOffsetSet(int no, float x, float y, float z); /* 27 instructions */
static void MB4_SakanaLenSet(int no, float len); /* 25 instructions */

static void MB4_CoinInit(void); /* 117 instructions */
static void MB4_CoinUpdate(OMOBJ *obj); /* 651 instructions */
static void MB4_CoinClose(void); /* 5 instructions */
static int MB4_CoinNumGet(void); /* 35 instructions */
static int MB4_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int duration); /* 166 instructions */
static int MB4_CoinNearGet(HuVecF *pos, float maxDist, HuVecF *out); /* 74 instructions */
static void MB4_CoinEffInit(void); /* 66 instructions */
static void MB4_CoinEffUpdate(OMOBJ *obj); /* 118 instructions */
static void MB4_CoinEffClose(void); /* 5 instructions */
static int MB4_CoinEffNumGet(void); /* 20 instructions */
static void MB4_CoinEffBlendModeSet(int blendMode); /* 29 instructions */
static int MB4_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color); /* 117 instructions */
static void MB4_BubbleEffInit(void); /* 62 instructions */
static void MB4_BubbleEffUpdate(OMOBJ *obj); /* 126 instructions */
static void MB4_BubbleEffClose(void); /* 5 instructions */
static int MB4_BubbleEffCreate(HuVecF *pos, float scale, int time); /* 190 instructions */

static s16 mb4_PathValidF;
static s16 mb4_PathLen;
static s16 mb4_PathMasuNo;

static void MB4_ModelMtxSet(s16 mdlId, Mtx mtx); /* 23 instructions */
static void MB4_PlayerMtxSet(s16 playerNo, Mtx mtx); /* 28 instructions */
static void MB4_ModelStub(HU3DMODEL *modelP); /* 1 instructions */
static s16 MB4_PathLenGet(s16 masuId, s16 num); /* 34 instructions */
static s16 PathCheck(s16 masuId, s16 num); /* 356 instructions */
static float MB4_HermiteSlopeCalc(float t, float p0, float p1, float m0, float m1); /* 71 instructions */
static float fn_1_DB68(float t, float p0, float p1, float p2, float p3); /* 77 instructions */
static float fn_1_DC9C(float t, float *p0, float *p1, float *p2, float *p3); /* 362 instructions */
static float MB4_PathTimeGet(float t, float *p0, float *p1, float *p2, float *p3); /* 1391 instructions */
static float MB4_PathNextTimeGet(float t, float *p0, float *p1, float *p2, float *p3); /* 19 instructions */

static float MB4_AngleDiff(float angle1, float angle2); /* 70 instructions */
static float MB4_AngleLerp(float target, float angle, float speed); /* 148 instructions */
static float fn_1_C6D0(float rate, float angle, float target); /* 254 instructions */
static float MB4_BezierCalc(float t, float p0, float p1, float p2); /* 30 instructions */
static void MB4_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out); /* 71 instructions */
static void MB4_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11); /* 37 instructions */
static float fn_1_D3D8(float t, float p0, float p1, float p2, float p3, float tension); /* 90 instructions */
static void MB4_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out); /* 304 instructions */

void ObjectSetup(void)
{
    GWPartyFSet(TRUE);
    MBObjectSetup(MBNO_WORLD_4, MB4_Create, MB4_Kill);
}

static void MB4_Create(void)
{
    int boardNo;
    int motTbl[16];
    MB4_BUBBLEEMIT *emit;
    int hu3dId;
    int mdlId;
    int i;

    boardNo = MBBoardNoGet();
    HuAudSndGrpSetSet(MSM_GRP_BD4);
    MBMasuCreate(W04_BIN_masuData);

    mb4_Work.mapMdlId = mdlId = MBModelCreate(W04_HSF_map, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.mdlId004 = mdlId = MBModelCreate(W04_HSF_obj13, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.mdlId008 = mdlId = MBModelCreate(W04_HSF_obj02, NULL, FALSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.kihonMdlId = mdlId = MBModelCreate(W04_HSF_kihonEv, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.mdlId014 = mdlId = MBModelCreate(W04_HSF_obj14, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.pukuMdlId[0] = mdlId = MBModelCreate(W04_HSF_puku0, NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.pukuMdlId[1] = mdlId = MBModelCreate(W04_HSF_puku1, NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.irukaEvMdlId = mdlId = MBModelCreate(W04_HSF_irukaEv, NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);

    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(W04_HSF_akari, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_AkariPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_AkariRotYTbl[i], 0);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(W04_HSF_sKai, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_SKaiPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_SKaiRotYTbl[i], 0);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(W04_HSF_rBok, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_RBokPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_RBokRotYTbl[i], 0);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(W04_HSF_sangoO, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_SangoOPosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_SangoORotTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<7; i++) {
        mdlId = MBModelCreate(W04_HSF_yazi, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_YaziPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_YaziRotTbl[i], 0);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(W04_HSF_yazi, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_YaziExtPosTbl[i]);
        MBModelRotSet(mdlId, 0, 180+mb4ev_YaziExtRotYTbl[i], 0);
    }
    for(i=0; i<1; i++) {
        mdlId = MBModelCreate(W04_HSF_ueYazi, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_UeYaziPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_UeYaziUpRotYTbl[i], 0);
    }
    for(i=0; i<4; i++) {
        mdlId = MBModelCreate(W04_HSF_hasigo, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_HasigoPosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_HasigoRotTbl[i]);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(W04_HSF_sango1, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango1PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango1RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango1ScaleTbl[i], mb4ev_Sango1ScaleTbl[i], mb4ev_Sango1ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(W04_HSF_sango2, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango2PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango2RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango2ScaleTbl[i], mb4ev_Sango2ScaleTbl[i], mb4ev_Sango2ScaleTbl[i]);
        if(i != 0) {
            MBModelLayerSet(mdlId, 1);
        }
        if(i == 0) {
            MBModelDispSet(mdlId, FALSE);
        }
    }
    for(i=0; i<6; i++) {
        mdlId = MBModelCreate(W04_HSF_sango3, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango3PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango3RotTbl[i]);
        MBModelScaleSetV(mdlId, &mb4ev_Sango3ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<4; i++) {
        mdlId = MBModelCreate(W04_HSF_sango4, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango4PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango4RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango4ScaleTbl[i], mb4ev_Sango4ScaleTbl[i], mb4ev_Sango4ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(W04_HSF_sango5, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango5PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango5RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango5ScaleTbl[i], mb4ev_Sango5ScaleTbl[i], mb4ev_Sango5ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<5; i++) {
        mdlId = MBModelCreate(W04_HSF_sango5, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_LeftSango5PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_LeftSango5RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_LeftSango5ScaleTbl[i], mb4ev_LeftSango5ScaleTbl[i], mb4ev_LeftSango5ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<4; i++) {
        mdlId = MBModelCreate(W04_HSF_hitode1, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Hitode1PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Hitode1RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Hitode1ScaleTbl[i], mb4ev_Hitode1ScaleTbl[i], mb4ev_Hitode1ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<4; i++) {
        mdlId = MBModelCreate(W04_HSF_hitode2, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Hitode2PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Hitode2RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Hitode2ScaleTbl[i], mb4ev_Hitode2ScaleTbl[i], mb4ev_Hitode2ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(W04_HSF_kaisoo, NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_KaisooPosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_KaisooRotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_KaisooScaleTbl[i], mb4ev_KaisooScaleTbl[i], mb4ev_KaisooScaleTbl[i]);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelLayerSet(mdlId, 1);
    }

    mb4_Work.kaiMdlId[0] = mdlId = MBModelCreate(W04_HSF_kai0, NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[0]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaiMdlId[1] = mdlId = MBModelCreate(W04_HSF_kai1, NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[1]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaiMdlId[2] = mdlId = MBModelCreate(W04_HSF_kai2, NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[2]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaisooMdlId[0] = mdlId = MBModelCreate(W04_HSF_kaisooEv0, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.kaisooMdlId[1] = mdlId = MBModelCreate(W04_HSF_kaisooEv1, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.kaisooMdlId[2] = mdlId = MBModelCreate(W04_HSF_kaisooEv2, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.mdlId03C = mdlId = MBModelCreate(W04_HSF_obj12, NULL, FALSE);
    MBModelLayerSet(mdlId, 1);

    motTbl[0] = W04_ANM_puku2_0;
    motTbl[1] = W04_ANM_puku2_1;
    motTbl[2] = -1;
    mb4_Work.puku2MdlId = mdlId = MBModelCreate(W04_HSF_puku2, motTbl, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_Puku2Pos);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBModelScaleSet(mdlId, 2, 2, 2);
    MBMotionNoSet(mdlId, 1, HU3D_MOTATTR_LOOP);

    motTbl[0] = W04_ANM_kihonSipp0;
    motTbl[1] = W04_ANM_kihonSipp1;
    motTbl[2] = W04_ANM_kihonSipp2;
    motTbl[3] = -1;
    mb4_Work.kihonSippMdlId = mdlId = MBModelCreate(W04_HSF_kihonSipp, motTbl, FALSE);
    MBMotionNoSet(mdlId, 1, HU3D_MOTATTR_LOOP);
    hu3dId = MBModelIdGet(mdlId);
    Hu3DModelClusterAttrSet(hu3dId, 0, HU3D_CLUSTER_ATTR_LOOP);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mdlId, FALSE);

    motTbl[0] = W04_ANM_iruka;
    motTbl[1] = -1;
    mb4_Work.irukaMdlId = mdlId = MBModelCreate(W04_HSF_iruka, motTbl, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mdlId, FALSE);

    mb4_Work.blowMdlId = mdlId = MBModelCreate(W04_HSF_blowEv, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBModelLayerSet(mdlId, 2);
    mb4_Work.kihonChrMdlId = mdlId = MBModelCreate(W04_HSF_kihonChr, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBModelLayerSet(mdlId, 1);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.coinLinkMdlId = mdlId = MBModelCreate(W04_HSF_coinLink, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBModelLayerSet(mdlId, 1);
    mb4_Work.mapViewMdlId = mdlId = MBModelCreate(W04_HSF_mapViewOff, NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBModelLayerSet(mdlId, 1);

    MB4_BubbleEffInit();
    emit = mb4_Work.playerBubble;
    for(i=0; i<4; i++, emit++) {
        emit->wait = (MB4_RandF()*60)*10;
        emit->num = (MB4_RandF()*10)+5;
        emit->time = frand();
    }
    emit = &mb4_Work.capsuleEmit;
    emit->num = 0;
    emit->time = frand();
    mb4_Work.capsuleNo = -1;
    mb4_Work.capsuleMdlId = -1;
    mb4_Work.capsuleEndF = 0;
    mb4_Work.capsuleFlag = 0;
    emit = &mb4_Work.storyEmit;
    emit->num = 0;
    emit->time = frand();
    mb4_Work.storyCapsuleNo = -1;
    mb4_Work.storyMdlId = -1;
    mb4_Work.storyEndF = 0;
    emit = mb4_Work.bubble;
    for(i=0; i<13; i++, emit++) {
        emit->wait = (MB4_RandF()*60)*12;
        emit->num = (MB4_RandF()*10)+5;
        emit->time = frand();
    }
    emit = &mb4_Work.pukuBubble;
    emit->wait = (MB4_RandF()*60)*12;
    emit->num = 0;
    emit->time = 0;
    emit = &mb4_Work.irukaBubble;
    emit->wait = (MB4_RandF()*60)*12;
    emit->num = 0;
    emit->time = 0;
    MB4_SakanaInit();

    MBCapsuleEffHookSet(MB4_CapsuleEffHook);
    MBScrollInit(W04_HSF_scrollCol, 20000, 0);
    MBLightHookSet(MB4_LightSet, MB4_LightReset);
    MBCapsuleColCreate(W04_HSF_capsuleCol);
    MBBranchFlagSet(MASU_FLAG_BIT(1)|MASU_FLAG_BIT(5)|MASU_FLAG_BIT(7));
    MBMasuPathCheckHookSet(MB4_MasuPathCheck);
    HuDataDirClose(DATA_w04);
    MBMasuWalkPreHookSet(MB4Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB4Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB4Ev_MasuHatena);
    mb4_MainObj = MBAddObj(32768, 0, 0, MB4_MainObjUpdate);
    MBOpeningViewSet(&openingRot, &openingOfs, openingZoom);
    MBMapViewCameraSet(&mapViewRot, &mapViewPos, mapViewZoom);
    MBMapViewHookSet(MB4_MapViewHook);
}

static void MB4_Kill(void)
{
    if(mb4_MainObj != NULL) {
        mb4_MainObj = NULL;
    }
    MB4_CoinClose();
    MB4_CoinEffClose();
    MB4_BubbleEffClose();
    MB4_SakanaClose();
}

static void MB4_MainObjUpdate(OMOBJ *obj)
{
    MB4_BUBBLEEMIT *emit;
    HuVecF playerPos;
    HuVecF scale;
    HuVecF pos;
    int i;

    if(MBKillCheck() || mb4_MainObj == NULL) {
        omDelObjEx(mbObjMan, obj);
        mb4_MainObj = NULL;
        return;
    }
    emit = mb4_Work.playerBubble;
    for(i=0; i<4; i++, emit++) {
        /*
         * On the DOL, playerPos is only written further down, so the first
         * pass reads it uninitialised and every later pass reads the previous
         * player's position. The third term also tests .y a second time
         * instead of .z. Both are what the disc does; kept verbatim.
         */
        if(playerPos.x == 0.0f && playerPos.y == 0.0f && playerPos.y == 0.0f) {
            continue;
        }
        if(MBPlayerMotionNoGet(i) == 10) {
            continue;
        }
        if(MBPlayerMotionNoGet(i) == 6) {
            continue;
        }
        if(!MBPlayerDispGet(i)) {
            continue;
        }
        emit->time++;
        if(--emit->wait > 0) {
            continue;
        }
        if(!MBPlayerAliveCheck(i)) {
            continue;
        }
        MBPlayerPosGet(i, &playerPos);
        MBPlayerScaleGet(i, &scale);
        if((emit->time & 3) != 0) {
            continue;
        }
        if(--emit->num > 0) {
            MB4Ev_PlayerBubbleCreate(i);
            continue;
        }
        emit->wait = ((MB4_RandF()*60)*5)+300;
        emit->num = (MB4_RandF()*10)+5;
    }
    MB4_CapsuleBubbleUpdate();
    emit = mb4_Work.bubble;
    for(i=0; i<13; i++, emit++) {
        emit->time++;
        if(--emit->wait > 0) {
            continue;
        }
        if((emit->time & 7) != 0) {
            continue;
        }
        if(--emit->num > 0) {
            MB4_BubbleEffCreate(&mb4ev_BubbleEmitPosTbl[i], (MB4_RandF()+0.5f)*1.5f,
                ((MB4_RandF()*0.2f)+1)*120);
            continue;
        }
        emit->wait = ((MB4_RandF()*60)*5)+300;
        emit->num = (MB4_RandF()*10)+5;
    }
    emit = &mb4_Work.pukuBubble;
    if(emit->num > 0) {
        emit->time++;
        if(--emit->wait <= 0 && (emit->time & 1) == 0 && --emit->num > 0) {
            pos = mb4ev_Puku2BubblePos;
            pos.x -= (MB4_RandF()*100)*0.5f;
            pos.y += (MB4_RandF()*100)*0.5f;
            pos.z -= ((MB4_RandF()-0.5f)*100)*0.25f;
            MB4_BubbleEffCreate(&pos, (MB4_RandF()+0.5f)*1.5f, ((MB4_RandF()*0.5f)+1)*120);
        }
    }
    emit = &mb4_Work.irukaBubble;
    if(emit->num > 0) {
        emit->time++;
        if(--emit->wait <= 0 && (emit->time & 1) == 0 && --emit->num > 0) {
            pos = mb4ev_IrukaStartBubblePos;
            pos.x -= (MB4_RandF()-0.5f)*100;
            pos.y += (MB4_RandF()-0.5f)*100;
            pos.z -= ((MB4_RandF()-0.5f)*100)*0.2f;
            MB4_BubbleEffCreate(&pos, (MB4_RandF()+0.5f)*1.5f, ((MB4_RandF()*0.5f)+1)*120);
        }
    }
    if(MBModelDispGet(mb4_Work.pukuMdlId[1]) && MBMotionEndCheck(mb4_Work.pukuMdlId[1])) {
        HuAudFXEmiterPlay(MSM_SE_BD4_08, &mb4ev_Puku2BubblePos);
        MBModelAttrSet(mb4_Work.pukuMdlId[0], HU3D_MOTATTR_PAUSE);
        MBModelAttrSet(mb4_Work.pukuMdlId[1], HU3D_MOTATTR_PAUSE);
        MBModelDispSet(mb4_Work.pukuMdlId[1], FALSE);
    }
}

static void MB4_LightSet(void)
{
    HuVecF pos;
    HuVecF dir;
    GXColor color;
    int lightId;

    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(255, 255, 255);
    pos.x = -3700;
    pos.y = 12000;
    pos.z = 22000;
    dir.x = 3700;
    dir.y = -12000;
    dir.z = -22000;
    color.r = 255;
    color.g = 255;
    color.b = 255;
    lightId = Hu3DGLightCreate(pos.x, pos.y, pos.z, dir.x, dir.y, dir.z,
        color.r, color.g, color.b);
    Hu3DGLightInfinitytSet(lightId);
}

static void MB4_LightReset(void)
{
}

static int MB4Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(masu->flag & MB4EV_MASU_KIHON) {
        MB4Ev_Kihon(playerNo);
    } else if(masu->flag & MB4EV_MASU_IRUKA) {
        MB4Ev_Iruka(playerNo);
    } else if(masu->flag & MB4EV_MASU_BLOW) {
        MB4Ev_Blow(playerNo);
    } else if(masu->flag & MB4EV_MASU_KAISOO) {
        MB4Ev_Kaisoo(playerNo);
    }
}

static int MB4_MasuStub(void)
{
    return 0;
}

static int MB4Ev_MasuWalkPre(int playerNo)
{
    return 0;
}

static int MB4Ev_MasuWalkPost(int playerNo)
{
    MASU *masu;
    s16 masuId;
    MB4_BUBBLEEMIT *emit;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(masu->flag & MB4EV_MASU_PUKU) {
        MBModelAttrReset(mb4_Work.pukuMdlId[0], HU3D_MOTATTR_PAUSE);
        MBMotionTimeSet(mb4_Work.pukuMdlId[0], 0);
        MBMotionSpeedSet(mb4_Work.pukuMdlId[0], 1);
        MBModelAttrReset(mb4_Work.pukuMdlId[1], HU3D_MOTATTR_PAUSE);
        MBMotionTimeSet(mb4_Work.pukuMdlId[1], 0);
        MBMotionSpeedSet(mb4_Work.pukuMdlId[1], 1);
        MBModelDispSet(mb4_Work.pukuMdlId[1], 1);
        HuAudFXEmiterPlay(0x5EF, &mb4ev_Puku2EmiterPos);
        emit = &mb4_Work.pukuBubble;
        emit->wait = 3;
        emit->num = 0x12;
        emit->time = -1;
    }
    return 0;
}

static int MB4_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    return -1;
}

static void MB4_CoinDispUpdate(int playerNo, int coins, int threshold)
{
    HuVecF pos;
    int motionId;
    int dispId;

    motionId = -1;
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    if(coins > 0) {
        MBPlayerPosGet(playerNo, &pos);
        pos.y += 250;
        dispId = MBCoinDispCreateSe(&pos, coins);
    } else {
        dispId = -1;
    }
    if(coins <= 0) {
        MBPlayerWinLoseVoicePlay(playerNo, 13, 0x200);
        MBPlayerMotionNoShiftSet(playerNo, 13, 0, 8, 0);
    } else if(coins < threshold) {
        MBPlayerWinLoseVoicePlay(playerNo, 12, 0x1FB);
        MBPlayerMotionNoShiftSet(playerNo, 12, 0, 8, 0);
    } else {
        MBPlayerWinLoseVoicePlay(playerNo, 12, 0x1FB);
        motionId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_356);
        MBPlayerMotionNoShiftSet(playerNo, motionId, 0, 8, 0);
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
    if(motionId != -1) {
        MBPlayerMotionKill(playerNo, motionId);
    }
}

static void MB4Ev_Kihon(int playerNo)
{
    s16 linkTbl[10];
    HuVecF playerPos;
    HuVecF playerPos2;
    HuVecF coinPos;
    HuVecF pos;
    HuVecF rot;
    HuVecF masuPos;
    HuVecF guidePos;
    HuVecF startPos;
    HuVecF endPos;
    HuVecF baseRot;
    HuVecF rotOfs;
    int maxTime;
    int coin;
    int seNo;
    int len1;
    int targetMasuId;
    int walkLen;
    float stkX;
    s16 masuIdSave;
    MASU *masu;
    MASU *masuNext;
    int angleTime;
    s16 masuId;
    int startMasuId;
    int nextMasuId;
    int motId;
    int guideId;
    int choice;
    int dirF;
    int len2;
    int time;
    s16 linkNum;
    int i;
    float t;
    float stkY;
    float speed;
    float lean;
    float dist;
    float diff;
    double absDiff;
    double absDiff2;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    coin = MBPlayerCoinGet(playerNo);
    startMasuId = masuId;
    MB4_CoinInit();
    MB4_CoinEffInit();
    pos.x = 0;
    pos.y = 200;
    pos.z = 0;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, &pos, 2000, -1, 42);
    MBCameraMotionWait();
    motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_435);
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    for(i=0; i<masu->linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & MASU_FLAG_BIT(1)) {
            break;
        }
    }
    if(i < masu->linkNum) {
        nextMasuId = masu->linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    } else {
        nextMasuId = masuId;
        masuPos.x = playerPos.x;
        masuPos.y = playerPos.y;
        masuPos.z = 200+playerPos.z;
    }
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=30.0f; i++) {
        t = i/30.0f;
        pos.x = playerPos.x+(t*(masuPos.x-playerPos.x));
        pos.y = playerPos.y+(t*(masuPos.y-playerPos.y));
        pos.z = playerPos.z+(t*(masuPos.z-playerPos.z));
        pos.y += 200.0*sin((M_PI*(180*t))/180.0);
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    GwPlayer[playerNo].masuId = nextMasuId;
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    masuNext = MBMasuGet(MASU_LAYER_DEFAULT, nextMasuId);
    for(i=0; i<masuNext->linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masuNext->linkTbl[i]) & MASU_FLAG_BIT(2)) {
            dirF = 0;
            break;
        }
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masuNext->linkTbl[i]) & MASU_FLAG_BIT(3)) {
            dirF = 1;
            break;
        }
    }
    if(i < masuNext->linkNum) {
        nextMasuId = masuNext->linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    } else {
        nextMasuId = masuId;
        masuPos.x = playerPos.x;
        masuPos.y = playerPos.y;
        masuPos.z = 200+playerPos.z;
    }
    MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, 0);
    for(i=0; i<=30.0f; i++) {
        t = i/30.0f;
        pos.x = playerPos.x+(t*(masuPos.x-playerPos.x));
        pos.y = playerPos.y+(t*(masuPos.y-playerPos.y));
        pos.z = playerPos.z+(t*(masuPos.z-playerPos.z));
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    GwPlayer[playerNo].masuId = nextMasuId;
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    MBDataAsyncWait(MBDataDirReadAsync(DATANUM(DATA_guide, 0)));
    guidePos = playerPos;
    if(dirF == 0) {
        guidePos.x -= 200;
    } else {
        guidePos.x += 200;
    }
    guidePos.y += 100;
    guideId = MBGuideCreateFlag(2, &guidePos, FALSE, TRUE, TRUE, FALSE);
    MBModelLayerSet(guideId, 2);
    HuDataDirClose(DATA_guide);
    MBAudFXPlay(MSM_SE_GUIDE_56);
    do {
        MBWinCreateChoice(MBWIN_TYPE_TALKCHOICE, MESS_BOARD_W04_KIHON_ASK, 2, 0);
        MBTopWinAttrSet(HUWIN_ATTR_NOCANCEL);
        if(GwPlayer[playerNo].comF) {
            for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
                if(i == startMasuId) {
                    continue;
                }
                if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & MASU_FLAG_BIT(0)) {
                    break;
                }
            }
            if(i <= MBMasuNumGet(MASU_LAYER_DEFAULT)) {
                targetMasuId = i;
            } else {
                targetMasuId = startMasuId;
            }
            walkLen = (GwPlayer[playerNo].dif+1)*10;
            len1 = MB4_PathLenGet(startMasuId, walkLen);
            len2 = MB4_PathLenGet(targetMasuId, walkLen);
            if(len1 == -1 && len2 == -1) {
                if(frand() & 3) {
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
        if(choice == 2) {
            masuIdSave = GwPlayer[playerNo].masuId;
            GwPlayer[playerNo].masuId = startMasuId;
            MBScrollExec(playerNo);
            MBStatusDispSetAll(TRUE);
            GwPlayer[playerNo].masuId = masuIdSave;
        }
    } while(choice >= 2);
    if(choice == 0) {
        MB4_SakanaOffsetInit();
        MBModelDispSet(mb4_Work.kihonChrMdlId, TRUE);
        MBModelDispSet(mb4_Work.kihonMdlId, TRUE);
        PSVECSubtract(&mb4ev_MasuKihonPosTbl[1], &mb4ev_MasuKihonPosTbl[0], &startPos);
        for(i=0; i<20; i++) {
            t = 0.1f+(0.8f*(i/20.0f));
            PSVECScale(&startPos, &pos, t);
            PSVECAdd(&mb4ev_MasuKihonPosTbl[0], &pos, &pos);
            pos.y += 100;
            pos.z += 400*(MB4_RandF()-0.5f);
            MB4_CoinCreate(&pos, &pos, 0, -1);
        }
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KIHON_COIN, 2);
        MBTopWinWait();
        MBTopWinKill();
        if(guideId != -1) {
            MBGuideEnd(guideId);
            guideId = -1;
        }
        if(dirF == 0) {
            startPos = mb4ev_MasuKihonPosTbl[1];
            endPos = mb4ev_MasuKihonPosTbl[0];
        } else {
            startPos = mb4ev_MasuKihonPosTbl[0];
            endPos = mb4ev_MasuKihonPosTbl[1];
        }
        MBModelPosSetV(mb4_Work.kihonSippMdlId, &startPos);
        PSVECSubtract(&endPos, &startPos, &pos);
        rot.z = rot.x = 0;
        rot.y = 180.0*(atan2(pos.x, pos.z)/M_PI);
        MBModelAttrReset(mb4_Work.kihonSippMdlId, HU3D_MOTATTR_PAUSE);
        MBModelRotSetV(mb4_Work.kihonSippMdlId, &rot);
        MBModelDispSet(mb4_Work.kihonSippMdlId, TRUE);
        MBModelPosSet(mb4_Work.coinLinkMdlId, startPos.x, -200, startPos.z);
        MBModelRotSetV(mb4_Work.coinLinkMdlId, &rot);
        MBModelScaleSet(mb4_Work.coinLinkMdlId, 2, 2, 2);
        MBModelDispSet(mb4_Work.coinLinkMdlId, TRUE);
        MBModelLayerSet(mb4_Work.coinLinkMdlId, 1);
        PSVECSubtract(&startPos, &playerPos, &pos);
        MBPlayerRotSet(playerNo, 0, 180.0*(atan2(pos.x, pos.z)/M_PI), 0);
        pos.x = 0;
        pos.y = 200;
        pos.z = 200;
        rot.x = -45;
        rot.y = 0;
        rot.z = 0;
        MBCameraModelViewSet(MBPlayerModelGet(playerNo), &rot, &pos, 2500, -1, 21);
        MBCameraMotionWait();
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        startPos.y += 30.000002f;
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            pos.x = playerPos.x+(t*(startPos.x-playerPos.x));
            pos.y = playerPos.y+(t*(startPos.y-playerPos.y));
            pos.z = playerPos.z+(t*(startPos.z-playerPos.z));
            pos.y += 200.0*sin((M_PI*(180*t))/180.0);
            MBPlayerPosSetV(playerNo, &pos);
            HuPrcVSleep();
        }
        if(motId != -1) {
            MBPlayerMotionNoShiftSet(playerNo, motId, 0, 8, HU3D_MOTATTR_LOOP);
        }
        for(i=0; i<=8; i++) {
            t = i/8.0f;
            if(dirF == 0) {
                MBPlayerRotSet(playerNo, 0, 90*t, 0);
            } else {
                MBPlayerRotSet(playerNo, 0, 90*(-t), 0);
            }
            HuPrcVSleep();
        }
        speed = 0;
        lean = 0;
        MBWinCreateHelp(MESS_BOARD_W04_KIHON_HELP);
        seNo = HuAudFXPlay(MSM_SE_BD4_01);
        PSVECSubtract(&endPos, &startPos, &pos);
        rot.z = rot.x = 0;
        rot.y = 180.0*(atan2(pos.x, pos.z)/M_PI);
        baseRot = rot;
        rotOfs.z = rotOfs.y = rotOfs.x = 0;
        dist = PSVECMag(&pos);
        maxTime = dist/5.0f;
        angleTime = 0;
        for(time=0; time<=maxTime; time++) {
            t = (float)time/(float)maxTime;
            stkX = MBPadStkXGet(GwPlayer[playerNo].padNo);
            stkY = MBPadStkYGet(GwPlayer[playerNo].padNo);
            lean *= 0.98f;
            if(t <= 0.9f) {
                if(!GwPlayer[playerNo].comF) {
                    if(stkY > 8) {
                        lean += 0.00015f*stkY;
                    } else if(stkY < 8) {
                        lean += 0.00015f*stkY;
                    }
                } else if(MB4_CoinNearGet(&coinPos, 200.0f*(GwPlayer[playerNo].dif+2), &pos)) {
                    diff = pos.z-coinPos.z;
                    absDiff = fabs(diff);
                    absDiff2 = absDiff;
                    if(absDiff2 > 20.0f*(5-GwPlayer[playerNo].dif)) {
                        if(pos.z < coinPos.z) {
                            lean += 0.0018000001f;
                        } else if(pos.z > coinPos.z) {
                            lean -= 0.0018000001f;
                        }
                    }
                }
                if(lean > 0.02f) {
                    lean = 0.02f;
                } else if(lean < -0.02f) {
                    lean = -0.02f;
                }
                speed += 0.75f*lean;
                if(speed > 1) {
                    speed = 1;
                } else if(speed < -1) {
                    speed = -1;
                }
            } else {
                speed *= 0.98f;
                lean *= 0.98f;
            }
            PSVECSubtract(&endPos, &startPos, &pos);
            PSVECScale(&pos, &pos, t);
            PSVECAdd(&startPos, &pos, &coinPos);
            coinPos.z -= 200*speed;
            coinPos.y += 0.15*(100.0*sin((M_PI*angleTime)/180.0));
            angleTime += 3;
            if(t < 0.9f) {
                if(dirF == 0) {
                    rotOfs.y = MB4_AngleLerp(45*lean, rotOfs.y, 0.5f);
                } else {
                    rotOfs.y = MB4_AngleLerp(-(45*lean), rotOfs.y, 0.5f);
                }
            } else {
                rotOfs.y = MB4_AngleLerp(0, rotOfs.y, 0.5f);
            }
            rot.x = baseRot.x+rotOfs.x;
            rot.y = baseRot.y+rotOfs.y;
            rot.z = baseRot.z+rotOfs.z;
            MBModelPosSetV(mb4_Work.kihonSippMdlId, &coinPos);
            MBModelRotSetV(mb4_Work.kihonSippMdlId, &rot);
            MBModelPosSet(mb4_Work.coinLinkMdlId, coinPos.x, -200, coinPos.z);
            MBModelRotSetV(mb4_Work.coinLinkMdlId, &rot);
            pos = coinPos;
            pos.y += 30.000002f;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSetV(playerNo, &rot);
            HuPrcVSleep();
        }
        MBTopWinKill();
        if(seNo != -1) {
            HuAudFXStop(seNo);
        }
        seNo = -1;
        MB4_SakanaPosInit();
        rot.x = -33;
        rot.y = 0;
        rot.z = 0;
        pos.x = 0;
        pos.y = 200;
        pos.z = 0;
        MBCameraModelViewSet(MBPlayerModelGet(playerNo), &rot, &pos, 2000, -1, 21);
        if(dirF == 0) {
            for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
                if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & MASU_FLAG_BIT(3)) {
                    break;
                }
            }
        } else {
            for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
                if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & MASU_FLAG_BIT(2)) {
                    break;
                }
            }
        }
        if(i > MBMasuNumGet(MASU_LAYER_DEFAULT)) {
            i = masuId;
        }
        nextMasuId = i;
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
        MBPlayerPosGet(playerNo, &playerPos);
        PSVECSubtract(&masuPos, &playerPos, &pos);
        MBPlayerRotSet(playerNo, 0, 180.0*(atan2(pos.x, pos.z)/M_PI), 0);
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(i=0; i<=8; i++) {
            t = i/8.0f;
            if(dirF == 0) {
                MBPlayerRotSet(playerNo, 0, 90+(90*t), 0);
            } else {
                MBPlayerRotSet(playerNo, 0, -90-(90*t), 0);
            }
            HuPrcVSleep();
        }
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            pos.x = playerPos.x+(t*(masuPos.x-playerPos.x));
            pos.y = playerPos.y+(t*(masuPos.y-playerPos.y));
            pos.z = playerPos.z+(t*(masuPos.z-playerPos.z));
            pos.y += 200.0*sin((M_PI*(180*t))/180.0);
            MBPlayerPosSetV(playerNo, &pos);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        GwPlayer[playerNo].masuId = nextMasuId;
        MBPlayerPosGet(playerNo, &playerPos);
        playerPos2 = playerPos;
        MBCameraMotionWait();
        HuPrcSleep(30);
        MBModelDispSet(mb4_Work.kihonSippMdlId, FALSE);
        MBModelDispSet(mb4_Work.coinLinkMdlId, FALSE);
        MBModelAttrSet(mb4_Work.kihonSippMdlId, HU3D_MOTATTR_PAUSE);
    }
    if(guideId != -1) {
        MBGuideEnd(guideId);
        guideId = -1;
    }
    MBModelDispSet(mb4_Work.kihonChrMdlId, FALSE);
    MBModelDispSet(mb4_Work.kihonMdlId, FALSE);
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    MBPlayerRotateStart(playerNo, 180, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    linkNum = MBMasuLinkTblGet(MASU_LAYER_DEFAULT, masuId, linkTbl);
    for(i=0; i<linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, linkTbl[i]) & MASU_FLAG_BIT(1)) {
            break;
        }
    }
    if(i < linkNum) {
        nextMasuId = linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    } else {
        nextMasuId = masuId;
        masuPos.x = playerPos.x;
        masuPos.y = playerPos.y;
        masuPos.z = playerPos.z-200;
    }
    MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, 0);
    for(i=0; i<=30.0f; i++) {
        t = i/30.0f;
        pos.x = playerPos.x+(t*(masuPos.x-playerPos.x));
        pos.y = playerPos.y+(t*(masuPos.y-playerPos.y));
        pos.z = playerPos.z+(t*(masuPos.z-playerPos.z));
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    GwPlayer[playerNo].masuId = nextMasuId;
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    linkNum = MBMasuLinkTblGet(MASU_LAYER_DEFAULT, nextMasuId, linkTbl);
    for(i=0; i<linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, linkTbl[i]) & MASU_FLAG_BIT(0)) {
            break;
        }
    }
    if(i < linkNum) {
        nextMasuId = linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    } else {
        nextMasuId = masuId;
        masuPos.x = playerPos.x;
        masuPos.y = playerPos.y;
        masuPos.z = playerPos.z-200;
    }
    MBPlayerPosFixEvent(playerNo, nextMasuId, FALSE);
    MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
    for(i=0; i<=30.0f; i++) {
        t = i/30.0f;
        pos.x = playerPos.x+(t*(masuPos.x-playerPos.x));
        pos.y = playerPos.y+(t*(masuPos.y-playerPos.y));
        pos.z = playerPos.z+(t*(masuPos.z-playerPos.z));
        pos.y += 200.0*sin((M_PI*(180*t))/180.0);
        MBPlayerPosSetV(playerNo, &pos);
        HuPrcVSleep();
    }
    GwPlayer[playerNo].masuId = nextMasuId;
    MBPlayerPosGet(playerNo, &playerPos);
    playerPos2 = playerPos;
    if(choice == 0) {
        MB4_CoinDispUpdate(playerNo, MBPlayerCoinGet(playerNo)-coin, 20);
    }
    if(motId != -1) {
        MBPlayerMotionKill(playerNo, motId);
    }
    MB4_CoinClose();
    MB4_CoinEffClose();
}

static void MB4Ev_Kaisoo(int playerNo)
{
    HuVecF playerPos;
    HuVecF startPos;
    HuVecF modelPos;
    HuVecF pos;
    HuVecF sprPos;
    HuVecF cameraRot;
    HuVecF rot;
    int coinMesId;
    int stkY;
    float zoom;
    MASU *masu;
    MBCAMERA *camera;
    int mdlId;
    int capMdlId;
    int curMdlId;
    int espId;
    int mesId;
    int capsuleNo;
    int sel;
    int wait;
    int comStep;
    int stkX;
    int btn;
    int fullF;
    int i;
    float t;
    float scale;
    float angle;
    float dist;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &playerPos);
    startPos = playerPos;
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, 0);
    camera = MBCameraGet();
    cameraRot = camera->rot;
    zoom = camera->zoom;
    mdlId = MBModelCreate(BOARD_HSF_coin, NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBPlayerPosGet(playerNo, &pos);
    pos.x += 500;
    pos.z -= 500;
    MBModelPosSetV(mdlId, &pos);
    rot.x = cameraRot.x;
    rot.y = cameraRot.y-45;
    rot.z = cameraRot.z;
    MBCameraModelViewSet(mdlId, &rot, NULL, 2000, -1, 42);
    MBCameraMotionWait();
    MBPlayerRotateStart(playerNo, 135, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        if(i == playerNo) {
            continue;
        }
        if(masuId == GwPlayer[i].masuId) {
            break;
        }
    }
    if(i >= 4) {
        MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, HU3D_MOTATTR_LOOP);
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            playerPos.x = startPos.x+200.0*sin((M_PI*(90*t))/180.0);
            playerPos.z = startPos.z-200.0*sin((M_PI*(90*t))/180.0);
            MBPlayerPosSetV(playerNo, &playerPos);
            MBPlayerRotSet(playerNo, 0, 135, 0);
            HuPrcVSleep();
        }
    } else {
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(i=0; i<=27.0f; i++) {
            t = i/27.0f;
            playerPos.x = startPos.x+(200*t);
            playerPos.z = startPos.z-(200*t);
            playerPos.y = startPos.y+250.0*sin((M_PI*(180*t))/180.0);
            MBPlayerPosSetV(playerNo, &playerPos);
            MBPlayerRotSet(playerNo, 0, 135, 0);
            HuPrcVSleep();
        }
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KAISOO_INST, 21);
    MBTopWinWait();
    MBTopWinKill();
    espId = espEntry(BOARD_ANM_cursor, 2000, 0);
    espDispOn(espId);
    espDrawNoSet(espId, 0);
    espAttrSet(espId, 1);
    espBankSet(espId, 0);
    Hu3D3Dto2D(&mb4ev_KaiPosTbl[1], 1, &sprPos);
    espPosSet(espId, sprPos.x, sprPos.y);
    sel = 1;
    wait = 0;
    capMdlId = -1;
    fullF = 0;
    MBWinCreateHelp(MESS_BOARD_W04_KAISOO_HELP);
    mesId = GameMesTimerCreate(5);
    if(!GwPlayer[playerNo].comF) {
        for(i=300; i>=0; i--) {
            HuPrcVSleep();
            GameMesTimerValueSet(mesId, (i+58)/60);
            if(wait <= 0) {
                stkX = MBPadStkXGet(GwPlayer[playerNo].padNo);
                stkY = MBPadStkYGet(GwPlayer[playerNo].padNo);
                btn = MBPadBtnDown(GwPlayer[playerNo].padNo);
            } else {
                btn = 0;
                stkY = btn;
                stkX = btn;
                wait--;
            }
            if(stkX < -8) {
                sel--;
                wait = 19;
            } else if(stkX > 8) {
                sel++;
                wait = 19;
            }
            if(sel < 0) {
                sel = 0;
            } else if(sel > 2) {
                sel = 2;
            }
            Hu3D3Dto2D(&mb4ev_KaiPosTbl[sel], 1, &pos);
            sprPos.x = sprPos.x+(0.1f*(pos.x-sprPos.x));
            sprPos.y = sprPos.y+(0.1f*(pos.y-sprPos.y));
            espPosSet(espId, sprPos.x, sprPos.y);
            if(btn & PAD_BUTTON_A) {
                break;
            }
        }
    } else {
        comStep = 0;
        wait = ((MB4_RandF()*60)*0.5f)+30;
        for(i=300; i>=0; i--) {
            HuPrcVSleep();
            GameMesTimerValueSet(mesId, (i+58)/60);
            btn = 0;
            stkY = btn;
            stkX = btn;
            if(comStep == 0) {
                if(--wait <= 0) {
                    if(MB4_RandF() < 0.33f) {
                        stkX = 0;
                    } else if(MB4_RandF() < 0.5f) {
                        stkX = -16;
                    } else {
                        stkX = 16;
                    }
                    comStep++;
                    wait = ((MB4_RandF()*60)*0.5f)+60;
                }
            } else if(--wait <= 0) {
                btn = PAD_BUTTON_A;
            }
            if(stkX < -8) {
                sel--;
                wait = 19;
            } else if(stkX > 8) {
                sel++;
                wait = 19;
            }
            if(sel < 0) {
                sel = 0;
            } else if(sel > 2) {
                sel = 2;
            }
            Hu3D3Dto2D(&mb4ev_KaiPosTbl[sel], 1, &pos);
            sprPos.x = sprPos.x+(0.1f*(pos.x-sprPos.x));
            sprPos.y = sprPos.y+(0.1f*(pos.y-sprPos.y));
            espPosSet(espId, sprPos.x, sprPos.y);
            if(btn & PAD_BUTTON_A) {
                break;
            }
        }
    }
    GameMesTimerEnd(mesId);
    mesId = -1;
    espKill(espId);
    MBTopWinKill();
    switch((frand() & 0x7FFF)%5) {
        case 0:
        case 1:
        case 2:
            capsuleNo = mb4ev_Puku2CapsuleTbl[(frand() & 0x7FFF)%9];
            if(GwSystem.teamF && capsuleNo == CAPSULE_MIRACLE) {
                capsuleNo = CAPSULE_SKINOKO;
            }
            capMdlId = MBModelCreate(MBCapsuleMdlGet(capsuleNo), NULL, FALSE);
            MBModelAttrSet(capMdlId, HU3D_MOTATTR_LOOP);
            curMdlId = capMdlId;
            break;

        default:
            if(frand() & 1) {
                curMdlId = mb4_Work.kaisooMdlId[1];
            } else {
                curMdlId = mb4_Work.kaisooMdlId[2];
            }
            break;
    }
    MBModelPosSetV(curMdlId, &mb4ev_KaiPosTbl[sel]);
    MBModelRotSet(curMdlId, 0, -45, 0);
    MBModelScaleSet(curMdlId, 0.5f, 0.5f, 0.5f);
    MBModelDispSet(curMdlId, TRUE);
    MBModelLayerSet(curMdlId, 2);
    MBMotionSpeedSet(mb4_Work.kaiMdlId[sel], 1);
    MBMotionTimeSet(mb4_Work.kaiMdlId[sel], 0);
    HuAudFXPlay(MSM_SE_BD4_06);
    i = 0;
    do {
        if(i++ < 30) {
            angle = -45+(60*(MB4_RandF()-0.5f));
            pos.x = mb4ev_KaiPosTbl[sel].x+75.0*sin((M_PI*angle)/180.0);
            pos.y = mb4ev_KaiPosTbl[sel].y;
            pos.z = mb4ev_KaiPosTbl[sel].z+75.0*cos((M_PI*angle)/180.0);
            MB4_BubbleEffCreate(&pos, 0.5f+(MB4_RandF()*0.5f), 180);
        }
        HuPrcVSleep();
    } while(!MBMotionEndCheck(mb4_Work.kaiMdlId[sel]));
    HuAudFXPlay(MSM_SE_BOARD_110);
    for(i=0; i<=60.0f; i++) {
        t = i/60.0f;
        modelPos = mb4ev_KaiPosTbl[sel];
        modelPos.y += 150.0*sin((M_PI*(90*t))/180.0);
        scale = 0.5f+(0.5f*t);
        MBModelPosSetV(curMdlId, &modelPos);
        MBModelRotSet(curMdlId, 0, -45, 0);
        MBModelScaleSet(curMdlId, scale, scale, scale);
        HuPrcVSleep();
    }
    if(MBPlayerCapsuleNumGet(playerNo) >= MBPlayerCapsuleMaxGet() && curMdlId == capMdlId) {
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KAISOO_FULL, 21);
        t = 0;
        do {
            if(t >= 1) {
                t -= 1;
            }
            t += 0.011111111f;
            if(t > 1) {
                t = 1;
            }
            modelPos = mb4ev_KaiPosTbl[sel];
            modelPos.y += 150.0+(0.2*(100.0*sin((M_PI*(360*t))/180.0)));
            MBModelPosSetV(curMdlId, &modelPos);
            HuPrcVSleep();
        } while(!MBTopWinDoneCheck() || t < 1);
        MBTopWinKill();
        for(i=0; i<=60.0f; i++) {
            t = i/60.0f;
            modelPos = mb4ev_KaiPosTbl[sel];
            modelPos.y += 150.0*cos((M_PI*(90*t))/180.0);
            scale = 1-(0.5f*t);
            MBModelPosSetV(curMdlId, &modelPos);
            MBModelRotSet(curMdlId, 0, -45, 0);
            MBModelScaleSet(curMdlId, scale, scale, scale);
            HuPrcVSleep();
        }
        MBMotionSpeedSet(mb4_Work.kaiMdlId[sel], -1);
        do {
            HuPrcVSleep();
        } while(MBMotionTimeGet(mb4_Work.kaiMdlId[sel]) > 0);
        fullF = 1;
    } else {
        for(i=0; i<=90.0f; i++) {
            t = i/90.0f;
            modelPos = mb4ev_KaiPosTbl[sel];
            modelPos.y += 150.0+(0.2*(100.0*sin((M_PI*(360*t))/180.0)));
            MBModelPosSetV(curMdlId, &modelPos);
            HuPrcVSleep();
        }
        PSVECSubtract(&modelPos, &playerPos, &pos);
        pos.y = 0;
        dist = PSVECMag(&pos);
        angle = 180.0*(atan2(pos.x, pos.z)/M_PI);
        HuAudFXPlay(MSM_SE_BOARD_38);
        for(i=0; i<=120.0f; i++) {
            t = i/120.0f;
            modelPos.x = playerPos.x+((dist*(1-t))*sin((M_PI*((720*t)+angle))/180.0));
            modelPos.z = playerPos.z+((dist*(1-t))*cos((M_PI*((720*t)+angle))/180.0));
            modelPos.y = (150*(1-t))+mb4ev_KaiPosTbl[sel].y-(50*t);
            scale = 1-t;
            MBModelPosSetV(curMdlId, &modelPos);
            MBModelScaleSet(curMdlId, scale, scale, scale);
            HuPrcVSleep();
        }
        MBModelDispSet(curMdlId, FALSE);
    }
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    rot.x = cameraRot.x;
    rot.y = cameraRot.y;
    rot.z = cameraRot.z;
    pos.x = 0;
    pos.z = 0;
    pos.y = 200;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), &rot, &pos, 2000, -1, 42);
    MBCameraMotionWait();
    if(curMdlId == mb4_Work.kaisooMdlId[0]) {
        MBCoinAddExec(playerNo, 10);
        MBPlayerPosGet(playerNo, &pos);
        pos.y += 250;
        coinMesId = MBCoinDispCreateSe(&pos, 10);
        MBAudFXPlay(MSM_SE_CMN_16);
        MBPlayerWinLoseVoicePlay(playerNo, 12, 504);
        MBPlayerMotionNoShiftSet(playerNo, 12, 0, 8, 0);
    } else if(curMdlId == capMdlId && fullF == 0) {
        MBPlayerCapsuleAdd(playerNo, capsuleNo);
        MBPlayerWinLoseVoicePlay(playerNo, 12, 504);
        MBPlayerMotionNoShiftSet(playerNo, 12, 0, 8, 0);
    } else {
        MBPlayerWinLoseVoicePlay(playerNo, 13, 512);
        MBPlayerMotionNoShiftSet(playerNo, 13, 0, 8, 0);
    }
    do {
        HuPrcVSleep();
    } while(!MBPlayerMotionEndCheck(playerNo)
        || MBMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
    if(curMdlId == mb4_Work.kaisooMdlId[0]) {
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KAISOO_COIN, -1);
    } else if(curMdlId == capMdlId) {
        if(fullF == 0) {
            MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KAISOO_CAPSULE, -1);
            MBTopWinInsertMesSet(MBCapsuleMesGet(capsuleNo), 0);
        }
    } else {
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_KAISOO_NONE, -1);
    }
    MBTopWinWait();
    MBTopWinKill();
    if(curMdlId == capMdlId && capsuleNo == CAPSULE_MIRACLE) {
        MB3MiracleGetExec(playerNo);
    }
    MBMotionSpeedSet(mb4_Work.kaiMdlId[sel], -3);
    MBPlayerRotateStart(playerNo, -45, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        if(i == playerNo) {
            continue;
        }
        if(masuId == GwPlayer[i].masuId) {
            break;
        }
    }
    if(i >= 4) {
        MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, HU3D_MOTATTR_LOOP);
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            playerPos.x = startPos.x+200.0*cos((M_PI*(90*t))/180.0);
            playerPos.z = startPos.z-200.0*cos((M_PI*(90*t))/180.0);
            MBPlayerPosSetV(playerNo, &playerPos);
            MBPlayerRotSet(playerNo, 0, -45, 0);
            HuPrcVSleep();
        }
    } else {
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(i=0; i<=27.0f; i++) {
            t = i/27.0f;
            playerPos.x = startPos.x+(200*(1-t));
            playerPos.z = startPos.z-(200*(1-t));
            playerPos.y = startPos.y+250.0*sin((M_PI*(180*t))/180.0);
            MBPlayerPosSetV(playerNo, &playerPos);
            MBPlayerRotSet(playerNo, 0, -45, 0);
            HuPrcVSleep();
        }
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBPlayerRotateStart(playerNo, 0, 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    do {
        HuPrcVSleep();
    } while(MBMotionTimeGet(mb4_Work.kaiMdlId[sel]) > 0);
    MBMotionSpeedSet(mb4_Work.kaiMdlId[sel], 0);
    MBMotionTimeSet(mb4_Work.kaiMdlId[sel], 0);
    if(mdlId != -1) {
        MBModelKill(mdlId);
    }
    if(capMdlId != -1) {
        MBModelKill(capMdlId);
    }
}

static void MB4Ev_Iruka(int playerNo)
{
    Mtx mtx;
    HuVecF destPos;
    HuVecF playerPos;
    HuVecF masuPos;
    HuVecF ofsPos;
    HuVecF pos;
    HuVecF vec;
    HuVecF rot;
    HuVecF p0;
    HuVecF p1;
    HuVecF curRot;
    HuVecF nextRot;
    HuVecF rotTarget;
    HuVecF prevRot;
    int motId[3];
    int idx;
    s16 masuId;
    MB4_BUBBLEEMIT *emit;
    MASU *masu;
    u32 branchFlag;
    int nextMasuId;
    int prevIdx;
    int nextIdx;
    int nextIdx2;
    int state;
    int revF;
    int maxTime;
    int seNo;
    int cnt;
    int i;
    int j;
    int k;
    float t;
    float u;
    float diff;
    float time;
    double absDiff;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &destPos);
    playerPos = destPos;
    motId[0] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_376);
    motId[1] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_435);
    motId[2] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_354);
    for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & MASU_FLAG_BIT(5)) {
            break;
        }
    }
    if(i > MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        i = masuId;
    }
    nextMasuId = i;
    MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    MBModelAttrReset(mb4_Work.irukaMdlId, HU3D_MOTATTR_PAUSE);
    MBModelPosSetV(mb4_Work.irukaMdlId, &mb4ev_IrukaPath[0]);
    MBMotionNoSet(mb4_Work.irukaMdlId, 1, HU3D_MOTATTR_LOOP);
    MBModelDispSet(mb4_Work.irukaMdlId, TRUE);
    MBCameraModelViewSet(mb4_Work.irukaMdlId, NULL, NULL, 2000, -1, 63);
    HuPrcSleep(48);
    MBModelAttrReset(mb4_Work.irukaEvMdlId, HU3D_MOTATTR_PAUSE);
    MBMotionTimeSet(mb4_Work.irukaEvMdlId, 0);
    MBMotionSpeedSet(mb4_Work.irukaEvMdlId, 1);
    emit = &mb4_Work.irukaBubble;
    emit->wait = 0;
    emit->num = 30;
    emit->time = -1;
    MBCameraMotionWait();
    PSVECSubtract(&mb4ev_IrukaPath[1], &mb4ev_IrukaPath[0], &vec);
    rot.x = (180.0*(atan2(sqrtf((vec.x*vec.x)+(vec.z*vec.z)), vec.y)/M_PI))-90.0;
    rot.y = 180.0*(atan2(vec.x, vec.z)/M_PI);
    rot.z = 0;
    rotTarget = rot;
    prevRot = rotTarget;
    revF = 0;
    state = 0;
    for(i=0; i<99U; i++) {
        p0 = mb4ev_IrukaPath[i];
        p1 = mb4ev_IrukaPath[i+1];
        prevIdx = i-1;
        idx = i;
        nextIdx = i+1;
        nextIdx2 = i+2;
        if(prevIdx < 0) {
            prevIdx = i;
        }
        if(nextIdx > 99U) {
            nextIdx = 99;
        }
        if(nextIdx2 > 99U) {
            nextIdx2 = 99;
        }
        if(i != 0) {
            curRot = nextRot;
        } else {
            curRot = rot;
        }
        PSVECSubtract(&p1, &p0, &vec);
        nextRot.y = 180.0*(atan2(vec.x, vec.z)/M_PI);
        nextRot.x = (180.0*(atan2(sqrtf((vec.x*vec.x)+(vec.z*vec.z)), vec.y)/M_PI))-90.0;
        nextRot.z = 0;
        if(revF) {
            if((nextRot.y += 180) > 180) {
                nextRot.y -= 360;
            }
            if(0 == nextRot.x) {
                nextRot.x = 180;
            } else if(nextRot.x > 0) {
                nextRot.x = 180-nextRot.x;
            } else {
                nextRot.x = -180-nextRot.x;
            }
        }
        diff = MB4_AngleDiff(prevRot.y, nextRot.y);
        absDiff = fabs(diff);
        if(absDiff > 90.0) {
            revF ^= 1;
            if(revF) {
                if((nextRot.y += 180) > 180) {
                    nextRot.y -= 360;
                }
                if(0 == nextRot.x) {
                    nextRot.x = 180;
                } else if(nextRot.x > 0) {
                    nextRot.x = 180-nextRot.x;
                } else {
                    nextRot.x = -180-nextRot.x;
                }
            } else {
                PSVECSubtract(&p1, &p0, &vec);
                nextRot.y = 180.0*(atan2(vec.x, vec.z)/M_PI);
                nextRot.x = (180.0*(atan2(sqrtf((vec.x*vec.x)+(vec.z*vec.z)), vec.y)/M_PI))-90.0;
                nextRot.z = 0;
            }
        }
        PSVECSubtract(&p1, &p0, &vec);
        time = MB4_PathNextTimeGet(1, &mb4ev_IrukaPath[prevIdx].x, &mb4ev_IrukaPath[idx].x,
            &mb4ev_IrukaPath[nextIdx].x, &mb4ev_IrukaPath[nextIdx2].x);
        maxTime = time/30.000002f;
        for(j=1; j<=maxTime; j++) {
            t = (float)j/(float)maxTime;
            MB4_HermiteCalcV(t, &mb4ev_IrukaPath[prevIdx].x, &mb4ev_IrukaPath[idx].x,
                &mb4ev_IrukaPath[nextIdx].x, &mb4ev_IrukaPath[nextIdx2].x, &pos.x);
            rotTarget.x = fn_1_C6D0(t, curRot.x, nextRot.x);
            rotTarget.y = fn_1_C6D0(t, curRot.y, nextRot.y);
            rotTarget.z = 0;
            rot.x = MB4_AngleLerp(rotTarget.x, rot.x, 2.5f);
            rot.y = MB4_AngleLerp(rotTarget.y, rot.y, 2.5f);
            rot.z = MB4_AngleLerp(rotTarget.z, rot.z, 2.5f);
            MBModelPosSetV(mb4_Work.irukaMdlId, &pos);
            MBModelRotSetV(mb4_Work.irukaMdlId, &rot);
            PSMTXIdentity(mtx);
            mtxRotCat(mtx, rot.x, rot.y, rot.z);
            ofsPos.x = 0;
            ofsPos.y = 30.000002f;
            ofsPos.z = 10;
            PSMTXMultVec(mtx, &ofsPos, &ofsPos);
            PSVECAdd(&ofsPos, &pos, &ofsPos);
            switch(state) {
                case 0:
                    if(i >= 1) {
                        HuAudFXPlay(MSM_SE_BD4_09);
                        MBPlayerMotionNoShiftSet(playerNo, motId[0], 0, 8, 0);
                        MBPlayerPosGet(playerNo, &destPos);
                        playerPos = destPos;
                        state++;
                        cnt = 0;
                    }
                    break;

                case 1:
                    cnt++;
                    u = cnt/24.0f;
                    PSVECSubtract(&ofsPos, &playerPos, &vec);
                    PSVECScale(&vec, &vec, u);
                    vec.y += 200.0*sin((M_PI*(180*u))/180.0);
                    PSVECAdd(&playerPos, &vec, &vec);
                    MBPlayerPosSetV(playerNo, &vec);
                    MBPlayerRotSet(playerNo, 0, 360*(-u), 0);
                    if(u >= 1) {
                        seNo = HuAudFXPlay(MSM_SE_BD4_02);
                        MBPlayerPosFixEvent(playerNo, nextMasuId, FALSE);
                        MBPlayerMotionNoShiftSet(playerNo, motId[1], 0, 8, HU3D_MOTATTR_LOOP);
                        MBPlayerPosSetV(playerNo, &ofsPos);
                        state++;
                        cnt = 0;
                    }
                    break;

                case 2:
                    MBPlayerPosSetV(playerNo, &ofsPos);
                    MBPlayerRotSetV(playerNo, &rot);
                    if(i >= 84U) {
                        MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, NULL, 2000, -1, 21);
                        MBPlayerMotionNoShiftSet(playerNo, motId[2], 0, 8, 0);
                        MBPlayerPosGet(playerNo, &destPos);
                        playerPos = destPos;
                        state++;
                        cnt = 0;
                    }
                    break;

                case 3:
                    cnt++;
                    u = cnt/30.0f;
                    PSVECSubtract(&masuPos, &playerPos, &vec);
                    PSVECScale(&vec, &vec, u);
                    vec.y += 200.0*sin((M_PI*(180*u))/180.0);
                    PSVECAdd(&playerPos, &vec, &vec);
                    MBPlayerPosSetV(playerNo, &vec);
                    MBPlayerRotSet(playerNo, 360*u, 0, 0);
                    if(u >= 1) {
                        if(seNo != -1) {
                            HuAudFXStop(seNo);
                        }
                        seNo = -1;
                        MBPlayerMotionNoShiftSet(playerNo, 6, 0, 8, HU3D_MOTATTR_LOOP);
                        MBPlayerPosSetV(playerNo, &masuPos);
                        state++;
                        cnt = 0;
                    }
                    break;
            }
            if(state >= 1 && state <= 3) {
                for(k=0; k<3; k++) {
                    vec.x = 50*(MB4_RandF()-0.5f);
                    vec.y = 50*(MB4_RandF()-0.5f);
                    vec.z = 50*(MB4_RandF()-0.5f);
                    MB4Ev_IrukaBubbleCreate(playerNo, &vec);
                }
            }
            HuPrcVSleep();
        }
        prevRot = nextRot;
    }
    MBPlayerPosSetV(playerNo, &masuPos);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    GwPlayer[playerNo].masuId = nextMasuId;
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBModelAttrSet(mb4_Work.irukaMdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mb4_Work.irukaMdlId, FALSE);
    HuPrcSleep(60);
    masu = MBMasuGet(MASU_LAYER_DEFAULT, nextMasuId);
    for(i=0; i<masu->linkNum; i++) {
        branchFlag = MBBranchFlagGet();
        if((MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & branchFlag) == 0) {
            break;
        }
    }
    if(i < masu->linkNum) {
        nextMasuId = masu->linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &destPos);
        MBPlayerPosGet(playerNo, &playerPos);
    } else {
        MBPlayerPosGet(playerNo, &playerPos);
        destPos = playerPos;
    }
    PSVECSubtract(&destPos, &playerPos, &vec);
    MBPlayerRotateStart(playerNo, 180.0*(atan2(vec.x, vec.z)/M_PI), 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerPosFixPlayer(playerNo, nextMasuId, FALSE);
    MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, 0);
    for(i=0; i<=30.0f; i++) {
        t = i/30.0f;
        vec.x = playerPos.x+(t*(destPos.x-playerPos.x));
        vec.y = playerPos.y+(t*(destPos.y-playerPos.y));
        vec.z = playerPos.z+(t*(destPos.z-playerPos.z));
        MBPlayerPosSetV(playerNo, &vec);
        HuPrcVSleep();
    }
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    GwPlayer[playerNo].masuId = nextMasuId;
    MBModelAttrSet(mb4_Work.irukaEvMdlId, HU3D_MOTATTR_PAUSE);
    MBMotionTimeSet(mb4_Work.irukaEvMdlId, 0);
    MBMotionSpeedSet(mb4_Work.irukaEvMdlId, 0);
    if(motId[0] != -1) {
        MBPlayerMotionKill(playerNo, motId[0]);
    }
    if(motId[1] != -1) {
        MBPlayerMotionKill(playerNo, motId[1]);
    }
    if(motId[2] != -1) {
        MBPlayerMotionKill(playerNo, motId[2]);
    }
}

static void MB4Ev_Blow(int playerNo)
{
    Mtx mtx;
    s16 linkTbl[10];
    HuVecF pos;
    HuVecF startPos;
    HuVecF nextPos;
    HuVecF vec;
    HuVecF endPos;
    HuVecF masuPos;
    HuVecF rot;
    int motId[2];
    s16 unused;
    MASU *masu;
    s16 masuId;
    int nextMasuId;
    int destMasuId;
    s16 linkNum;
    int dstMasuId;
    int seNo;
    int choice;
    int randF;
    int i;
    float t;
    float scale;
    float speed;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &pos);
    startPos = pos;
    motId[0] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_374);
    motId[1] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_354);
    vec.x = 0;
    vec.y = 200;
    vec.z = 0;
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, &vec, 2000, -1, 42);
    MBCameraMotionWait();
    for(i=0; i<masu->linkNum; i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]) & MB4EV_MASU_BLOWDEST) {
            break;
        }
    }
    if(i < masu->linkNum) {
        nextMasuId = masu->linkTbl[i];
        MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &nextPos);
    } else {
        nextMasuId = masuId;
        nextPos.x = pos.x-200;
        nextPos.y = pos.y;
        nextPos.z = 200+pos.z;
    }
    PSVECSubtract(&nextPos, &pos, &vec);
    MBPlayerRotateStart(playerNo, 180.0*(atan2(vec.x, vec.z)/M_PI), 15);
    while(!MBPlayerRotateCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBAudFXPlay(MSM_SE_GUIDE_56);
    MBWinCreateChoice(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W04_BLOW_ASK, 2, 0);
    MBTopWinAttrReset(HUWIN_ATTR_NOCANCEL);
    if(GwPlayer[playerNo].comF) {
        if(MBMasuPathTypeLenGet(masuId, 5) > 10) {
            MBComChoiceSetLeft();
        } else {
            MBComChoiceSetRight();
        }
    }
    MBTopWinWait();
    choice = MBWinLastChoiceGet();
    MBTopWinKill();
    if(choice == 0) {
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            vec.x = pos.x+(t*(nextPos.x-pos.x));
            vec.y = pos.y+(t*(nextPos.y-pos.y));
            vec.z = pos.z+(t*(nextPos.z-pos.z));
            vec.y += 200.0*sin((M_PI*(180*t))/180.0);
            MBPlayerPosSetV(playerNo, &vec);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        MBPlayerPosGet(playerNo, &pos);
        startPos = pos;
        vec.x = 0;
        vec.y = 200;
        vec.z = 0;
        MBCameraMasuViewSet(nextMasuId, NULL, &vec, 3000, -1, 21);
        HuPrcSleep(60);
        MBPlayerMotionNoShiftSet(playerNo, motId[0], 0, 8, 0);
        do {
            HuPrcVSleep();
        } while(!MBPlayerMotionEndCheck(playerNo)
            || Hu3DMotionShiftIDGet(MBPlayerModelGet(playerNo)) != -1);
        MBCameraQuakeSet(60, 50);
        seNo = HuAudFXPlay(MSM_SE_BD4_03);
        HuPrcSleep(60);
        if(seNo != -1) {
            HuAudFXStop(seNo);
        }
        seNo = -1;
        seNo = HuAudFXPlay(MSM_SE_BD4_04);
        MBPlayerMotionNoShiftSet(playerNo, motId[1], 0, 8, HU3D_MOTATTR_LOOP);
        for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
            if(MBMasuTypeGet(MASU_LAYER_DEFAULT, i) == MASU_TYPE_STAR) {
                break;
            }
        }
        if(i > MBMasuNumGet(MASU_LAYER_DEFAULT)) {
            i = masuId;
        }
        destMasuId = i;
        masuId = destMasuId;
        if(MB4_RandF() < 0.65f) {
            randF = 1;
        } else {
            randF = 0;
        }
        while(1) {
            if(randF) {
                linkNum = MBMasuLinkTblGet(MASU_LAYER_DEFAULT, masuId, linkTbl);
            } else {
                masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
                linkNum = masu->linkNum;
                for(i=0; i<linkNum; i++) {
                    linkTbl[i] = masu->linkTbl[i];
                }
            }
            if(linkNum > 0) {
                for(i=0; i<linkNum; i++) {
                    if((MBMasuFlagGet(MASU_LAYER_DEFAULT, linkTbl[i]) & MBBranchFlagGet()) == 0) {
                        break;
                    }
                }
                if(i < linkNum) {
                    dstMasuId = linkTbl[i];
                } else {
                    dstMasuId = masuId;
                }
            } else {
                dstMasuId = masuId;
            }
            if(masuId == dstMasuId) {
                break;
            }
            if(MBMasuTypeGet(MASU_LAYER_DEFAULT, dstMasuId) != MASU_TYPE_NONE) {
                break;
            }
            masuId = dstMasuId;
        }
        MBPlayerPosFixEvent(playerNo, dstMasuId, FALSE);
        MBMasuPosGet(MASU_LAYER_DEFAULT, dstMasuId, &masuPos);
        PSVECSubtract(&masuPos, &pos, &vec);
        PSVECScale(&vec, &vec, 0.5f);
        PSVECAdd(&pos, &vec, &endPos);
        if(pos.y > masuPos.y) {
            endPos.y = (5000+pos.y)+PSVECMag(&vec);
        } else {
            endPos.y = (5000+masuPos.y)+PSVECMag(&vec);
        }
        MBPlayerPosGet(playerNo, &vec);
        MBModelPosSetV(mb4_Work.blowMdlId, &vec);
        MBModelDispSet(mb4_Work.blowMdlId, TRUE);
        MBMotionTimeSet(mb4_Work.blowMdlId, 0);
        MBModelAttrSet(mb4_Work.blowMdlId, HU3D_MOTATTR_LOOP);
        MBModelAlphaSet(mb4_Work.blowMdlId, 0);
        MBModelScaleSet(mb4_Work.blowMdlId, 0, 0, 0);
        HuPrcVSleep();
        unused = 0;
        speed = 0;
        MBPlayerPosGet(playerNo, &pos);
        pos = vec;
        MBPlayerRotGet(playerNo, &rot);
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            scale = t;
            MBModelAlphaSet(mb4_Work.blowMdlId, 255*t);
            MBModelScaleSet(mb4_Work.blowMdlId, scale, 0.5f*scale, scale);
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.blowMdlId), "i_hook", mtx);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            rot.y += 10;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSet(playerNo, 0, rot.y, 0);
            HuPrcVSleep();
        }
        for(i=0; i<=60.0f; i++) {
            t = i/60.0f;
            scale = 0.5+(0.05*sin((M_PI*(720*t))/180.0));
            MBModelAlphaSet(mb4_Work.blowMdlId, 255);
            MBModelScaleSet(mb4_Work.blowMdlId, 1, scale, 1);
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.blowMdlId), "i_hook", mtx);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            rot.y += 10;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSet(playerNo, 0, rot.y, 0);
            HuPrcVSleep();
        }
        omVibrate(playerNo, 12, 4, 2);
        if(seNo != -1) {
            HuAudFXFadeOut(seNo, 1000);
        }
        seNo = -1;
        seNo = HuAudFXPlay(MSM_SE_BD4_05);
        vec = pos;
        for(i=0; i<=21.0f; i++) {
            t = i/21.0f;
            scale = 0.5f+t;
            MBModelScaleSet(mb4_Work.blowMdlId, 1, scale, 1);
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.blowMdlId), "i_hook", mtx);
            pos.x = mtx[0][3];
            pos.y = mtx[1][3];
            pos.z = mtx[2][3];
            rot.y += 10;
            speed = pos.y-vec.y;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSet(playerNo, 0, rot.y, 0);
            vec = pos;
            HuPrcVSleep();
        }
        if(seNo != -1) {
            HuAudFXFadeOut(seNo, 1000);
        }
        seNo = -1;
        WipeColorSet(255, 255, 255);
        WipeCreate(2, 0x81, 1);
        WipeWait();
        MBModelDispSet(mb4_Work.blowMdlId, FALSE);
        GwPlayer[playerNo].masuId = dstMasuId;
        MBPlayerPosFixEvent(playerNo, dstMasuId, TRUE);
        MBPlayerMotionSpeedSet(playerNo, 0);
        MBCameraSkipSet(FALSE);
        vec.x = 0;
        vec.y = 200;
        vec.z = 0;
        MBCameraMasuViewSet(dstMasuId, NULL, &vec, -1, -1, 1);
        MBCameraMotionWait();
        MBCameraSkipSet(TRUE);
        WipeCreate(1, 0x81, 30);
        startPos = masuPos;
        startPos.y += 3000;
        endPos = masuPos;
        endPos.y += 1500;
        for(i=0; i<=30.0f; i++) {
            t = i/30.0f;
            MB4_BezierCalcV(0.5f+(0.5f*t), &startPos.x, &endPos.x, &masuPos.x, &pos.x);
            MB4_BezierCalcV((0.5f+(0.5f*t))-0.01f, &startPos.x, &endPos.x, &masuPos.x, &vec.x);
            PSVECSubtract(&vec, &pos, &vec);
            rot.z = rot.y = rot.x = 0;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSetV(playerNo, &rot);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 6, 0, 8, HU3D_MOTATTR_LOOP);
        PSMTXIdentity(mtx);
        MB4_PlayerMtxSet(playerNo, mtx);
        pos = masuPos;
        rot.z = rot.y = rot.x = 0;
        speed = 35;
        do {
            HuPrcVSleep();
            pos.y += speed;
            speed -= 1.6333334f;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerRotSetV(playerNo, &rot);
        } while(pos.y > masuPos.y || speed >= 0);
        MBPlayerPosSetV(playerNo, &masuPos);
        MBPlayerRotSet(playerNo, 0, 0, 0);
        HuPrcSleep(60);
        MBPlayerMotionSpeedSet(playerNo, 1);
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
        vec.x = 0;
        vec.y = 200;
        vec.z = 0;
        MBCameraMasuViewSet(dstMasuId, NULL, &vec, 1500, -1, 42);
        MBCameraMotionWait();
    }
    if(motId[0] != -1) {
        MBPlayerMotionKill(playerNo, motId[0]);
    }
    if(motId[1] != -1) {
        MBPlayerMotionKill(playerNo, motId[1]);
    }
}

static void MB4Ev_IrukaBubbleCreate(int playerNo, HuVecF *ofs)
{
    Mtx mtx;
    HuVecF pos;
    int charNo;

    charNo = GwPlayer[playerNo].charNo;
    Hu3DModelObjMtxGet(MBModelIdGet(MBPlayerModelGet(playerNo)), "ske_head", mtx);
    pos.x = mb4ev_IrukaBubbleOfsTbl[charNo].z;
    pos.y = mb4ev_IrukaBubbleOfsTbl[charNo].y;
    pos.z = mb4ev_IrukaBubbleOfsTbl[charNo].x;
    PSMTXMultVec(mtx, &pos, &pos);
    PSVECAdd(&pos, ofs, &pos);
    MB4_BubbleEffCreate(&pos, mb4ev_IrukaTPLvlScaleTbl[charNo]*(0.3f+0.7f*MB4_RandF()),
        120*(0.5f+0.2f*MB4_RandF()));
}

static void MB4Ev_PlayerBubbleCreate(int playerNo)
{
    Mtx mtx;
    HuVecF pos;
    int charNo;

    charNo = GwPlayer[playerNo].charNo;
    Hu3DModelObjMtxGet(MBModelIdGet(MBPlayerModelGet(playerNo)), "ske_head", mtx);
    pos.x = mb4ev_IrukaBubbleOfsTbl[charNo].z;
    pos.y = mb4ev_IrukaBubbleOfsTbl[charNo].y;
    pos.z = mb4ev_IrukaBubbleOfsTbl[charNo].x;
    PSMTXMultVec(mtx, &pos, &pos);
    PSVECAdd(&pos, &mb4ev_PlayerBubbleOfs, &pos);
    MB4_BubbleEffCreate(&pos, mb4ev_IrukaTPLvlScaleTbl[charNo]*(0.3f+0.7f*MB4_RandF()),
        120*(0.5f+0.2f*MB4_RandF()));
}

static void MB4_CapsuleEffHook(int capsuleNo, int type, int mdlId, BOOL flag1, BOOL flag2, BOOL flag3)
{
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    HuVecF vec;
    float angle;
    int time;
    int i;

    switch(capsuleNo) {
        case CAPSULE_KOOPA:
        case CAPSULE_VS:
            mb4_Work.capsuleEndF = 0;
            switch(type) {
                case 3:
                case 4:
                    mb4_Work.capsuleEmit.num = 8+(MB4_RandF()*5);
                    mb4_Work.capsuleEmit.time = frand();
                    mb4_Work.capsuleEmit.wait = 0;
                    mb4_Work.capsuleNo = CAPSULE_KOOPA;
                    mb4_Work.capsuleMdlId = mdlId;
                    mb4_Work.capsuleFlag = flag1;
                    break;

                case 1:
                case 2:
                    mb4_Work.capsuleNo = -1;
                    mb4_Work.capsuleMdlId = -1;
                    break;
            }
            if(type == 4) {
                mb4_Work.capsuleEndF = 1;
            }
            break;

        case CAPSULE_INVALID:
            mb4_Work.storyEndF = 0;
            switch(type) {
                case 3:
                case 4:
                    mb4_Work.storyEmit.num = 8+(MB4_RandF()*5);
                    mb4_Work.storyEmit.time = frand();
                    mb4_Work.storyEmit.wait = 0;
                    mb4_Work.storyCapsuleNo = CAPSULE_INVALID;
                    mb4_Work.storyMdlId = mdlId;
                    break;

                case 1:
                case 2:
                    mb4_Work.storyCapsuleNo = -1;
                    mb4_Work.storyMdlId = -1;
                    break;
            }
            if(type == 4) {
                mb4_Work.storyEndF = 1;
            }
            break;

        case CAPSULE_KILLER:
            switch(type) {
                case 5:
                    for(i=0; i<2; i++) {
                        MBModelPosGet(mdlId, &pos);
                        MBModelRotGet(mdlId, &rot);
                        mtxRot(mtx, -rot.x, rot.y, rot.z);
                        vec.x = 0;
                        vec.y = 0;
                        vec.z = -100;
                        PSMTXMultVec(mtx, &vec, &vec);
                        PSVECAdd(&pos, &vec, &pos);
                        pos.x += 100*(MB4_RandF()-0.5f);
                        pos.y += 100*(MB4_RandF()-0.5f);
                        pos.z += 100*(MB4_RandF()-0.5f);
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;

                case 6:
                    for(i=0; i<32; i++) {
                        MBModelPosGet(mdlId, &pos);
                        pos.x += 1.5f*(100*(MB4_RandF()-0.5f));
                        pos.y += 1.5f*(100*(MB4_RandF()-0.5f));
                        pos.z += 0.5f*(100*(MB4_RandF()-0.5f));
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;
            }
            break;

        case CAPSULE_PAKKUN:
            switch(type) {
                case 7:
                    for(i=0; i<16; i++) {
                        MBModelPosGet(mdlId, &pos);
                        pos.x += 100*(MB4_RandF()-0.5f);
                        pos.z += 100*(MB4_RandF()-0.5f);
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;

                case 6:
                    Hu3DModelObjMtxGet(MBModelIdGet(mdlId), mb4_ItemHookName, mtx);
                    vec.x = mtx[0][3];
                    vec.y = mtx[1][3];
                    vec.z = mtx[2][3];
                    for(i=0; i<32; i++) {
                        MBModelPosGet(mdlId, &pos);
                        pos.x = vec.x+(100*(MB4_RandF()-0.5f));
                        pos.y = vec.y+(100*(MB4_RandF()-0.5f));
                        pos.z = vec.z+(100*(MB4_RandF()-0.5f));
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;
            }
            break;

        case CAPSULE_BOMHEI:
            switch(type) {
                case 7:
                    break;

                case 8:
                    for(i=0; i<2; i++) {
                        MBModelPosGet(mdlId, &pos);
                        pos.x += 100*(MB4_RandF()-0.5f);
                        pos.z += 100*(MB4_RandF()-0.5f);
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;

                case 6:
                    for(i=0; i<64; i++) {
                        MBModelPosGet(mdlId, &pos);
                        pos.x += 2*(100*(MB4_RandF()-0.5f));
                        pos.y += 2*(100*(MB4_RandF()-0.5f));
                        pos.z += 0.5f*(100*(MB4_RandF()-0.5f));
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;
            }
            break;

        default:
            switch(type) {
                case 3:
                    mb4_Work.capsuleEmit.num = 12+(MB4_RandF()*4);
                    mb4_Work.capsuleEmit.time = frand();
                    mb4_Work.capsuleNo = capsuleNo;
                    mb4_Work.capsuleMdlId = mdlId;
                    mb4_Work.capsuleFlag = flag1;
                    break;

                case 8:
                    if(capsuleNo == CAPSULE_JUGEM) {
                        MBModelPosGet(mdlId, &pos);
                        angle = 360*MB4_RandF();
                        pos.x += 0.4*(100.0*sin((M_PI*angle)/180.0));
                        pos.z += 0.4*(100.0*cos((M_PI*angle)/180.0));
                        pos.y += 0.2f*(100*(MB4_RandF()-0.5f));
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    } else {
                        MBModelPosGet(mdlId, &pos);
                        angle = 360*MB4_RandF();
                        pos.x += 0.6*(100.0*sin((M_PI*angle)/180.0));
                        pos.z += 0.6*(100.0*cos((M_PI*angle)/180.0));
                        pos.y -= 0.2f*(100*MB4_RandF());
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    }
                    break;

                case 1:
                case 2:
                    mb4_Work.capsuleNo = -1;
                    mb4_Work.capsuleMdlId = -1;
                    break;
            }
            break;
    }
}

static void MB4_CapsuleBubbleUpdate(void)
{
    MB4_BUBBLEEMIT *emit;
    Mtx mtx;
    HuVecF pos;
    int time;
    int dispF;
    int no;
    int i;

    if(mb4_Work.storyCapsuleNo != -1 && mb4_Work.storyMdlId != -1) {
        emit = &mb4_Work.storyEmit;
        dispF = MBModelDispGet(mb4_Work.storyMdlId);
        if(!dispF) {
            mb4_Work.storyCapsuleNo = -1;
            mb4_Work.storyMdlId = -1;
            emit->num = 0;
        }
        if(--emit->wait <= 0 && emit->num > 0) {
            emit->time++;
            if((emit->time & 3) == 0) {
                HuVecF ofs = { 65, -20, 0 };

                Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.storyMdlId), "ske_head", mtx);
                PSMTXMultVec(mtx, &ofs, &pos);
                time = 120*(1+(MB4_RandF()*0.2f));
                MB4_BubbleEffCreate(&pos, 1.2f*(0.3f+(MB4_RandF()*0.7f)), time);
                if(--emit->num <= 0) {
                    if(mb4_Work.storyEndF) {
                        emit->num = 8+(MB4_RandF()*5);
                        emit->time = frand();
                        emit->wait = 180+((MB4_RandF()*60)*3);
                    } else {
                        mb4_Work.storyMdlId = -1;
                    }
                }
            }
        }
    }
    if(mb4_Work.capsuleNo == -1 || mb4_Work.capsuleMdlId == -1) {
        return;
    }
    emit = &mb4_Work.capsuleEmit;
    switch(mb4_Work.capsuleNo) {
        case CAPSULE_JANGO:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "jyan", mtx);
            PSMTXMultVec(mtx, &mb4ev_JangoBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_HANACHAN:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "nose", mtx);
            PSMTXMultVec(mtx, &mb4ev_HanachanBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_HAMMERBRO:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "head", mtx);
            PSMTXMultVec(mtx, &mb4ev_HammerBroBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_PATAPATA:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "noko_head", mtx);
            PSMTXMultVec(mtx, &mb4ev_PatapataBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_KURIBO:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "body", mtx);
            PSMTXMultVec(mtx, &mb4ev_KuriboBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_BANK:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "noko_head", mtx);
            PSMTXMultVec(mtx, &mb4ev_BankBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_KAMEKKU:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "neck", mtx);
            PSMTXMultVec(mtx, &mb4ev_KamekkuBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_KOKAMEKKU:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "neck", mtx);
            PSMTXMultVec(mtx, &mb4ev_KokamekkuBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_UKKI:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "neck", mtx);
            PSMTXMultVec(mtx, &mb4ev_UkkiBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_JUGEM:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "j_uekuti", mtx);
            PSMTXMultVec(mtx, &mb4ev_JugemBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_DUEL:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "head", mtx);
            PSMTXMultVec(mtx, &mb4ev_DuelBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_DONKEY:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if((emit->time & 3) != 0) {
                break;
            }
            Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "ske_head", mtx);
            PSMTXMultVec(mtx, &mb4ev_DonkeyBubbleOfs, &pos);
            time = 120*(1+(MB4_RandF()*0.2f));
            MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            if(--emit->num <= 0) {
                mb4_Work.capsuleMdlId = -1;
            }
            break;

        case CAPSULE_KOOPA:
            if(emit->num <= 0) {
                break;
            }
            emit->time++;
            if(--emit->wait > 0) {
                break;
            }
            if((emit->time & 3) != 0) {
                break;
            }
            if(mb4_Work.capsuleFlag == 0) {
                Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "ns_hed", mtx);
            } else {
                Hu3DModelObjMtxGet(MBModelIdGet(mb4_Work.capsuleMdlId), "ns_hed", mtx);
            }
            if(mb4_Work.capsuleFlag == 0) {
                no = 0;
            } else {
                no = 1;
            }
            for(i=0; i<2; i++) {
                pos.x = mb4ev_KoopaBubbleOfsTbl[no][i].z;
                pos.y = mb4ev_KoopaBubbleOfsTbl[no][i].y;
                pos.z = mb4ev_KoopaBubbleOfsTbl[no][i].x;
                PSMTXMultVec(mtx, &pos, &pos);
                time = 120*(1+(MB4_RandF()*0.2f));
                MB4_BubbleEffCreate(&pos, 0.75f*(0.5f+MB4_RandF()), time);
            }
            if(--emit->num <= 0) {
                if(mb4_Work.capsuleEndF) {
                    emit->num = 8+(MB4_RandF()*5);
                    emit->time = frand();
                    emit->wait = 180+((MB4_RandF()*60)*3);
                } else {
                    mb4_Work.capsuleMdlId = -1;
                }
            }
            break;
    }
}



static float MB4_AngleDiff(float angle1, float angle2)
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

static float MB4_AngleLerp(float target, float angle, float speed)
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

static float fn_1_C6D0(float rate, float angle, float target)
{
    float diff;

    diff = MB4_AngleDiff(target, angle);
    return MB4_AngleLerp(target, angle, fabs(diff*rate));
}

static float MB4_BezierCalc(float t, float p0, float p1, float p2)
{
    float u = 1.0-t;
    float value;

    value = (p2*(t*t))+((p0*(u*u))+(2.0*(p1*(u*t))));
    return value;
}

static void MB4_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out)
{
    int i;

    for(i=0; i<3; i++) {
        *out++ = MB4_BezierCalc(t, *p0++, *p1++, *p2++);
    }
}

static void MB4_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11)
{
    float t2 = t*t;
    float t3 = t*t2;
    float h = (3.0*t2)-t3-t3;

    *h00 = 1.0-h;
    *h10 = h;
    *h01 = t+((t3-t2)-t2);
    *h11 = t3-t2;
}

static float fn_1_D3D8(float t, float p0, float p1, float p2, float p3, float tension)
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
    MB4_HermiteCalc(t, &h00, &h10, &h01, &h11);
    return value = (h11*m2)+((h01*m1)+((h00*p1)+(h10*p2)));
}

static void MB4_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out)
{
    float rate = 0.5f;

    out[0] = fn_1_D3D8(t, p0[0], p1[0], p2[0], p3[0], rate);
    out[1] = fn_1_D3D8(t, p0[1], p1[1], p2[1], p3[1], rate);
    out[2] = fn_1_D3D8(t, p0[2], p1[2], p2[2], p3[2], rate);
}

static void MB4_ModelMtxSet(s16 mdlId, Mtx mtx)
{
    HU3DMODEL *modelP;
    int modelId;

    modelId = MBModelIdGet(mdlId);
    modelP = &Hu3DData[modelId];
    MTXCopy(mtx, modelP->mtx);
}

static void MB4_PlayerMtxSet(s16 playerNo, Mtx mtx)
{
    int modelId;
    HU3DMODEL *modelP;
    MBMODELID mdlId;

    mdlId = MBPlayerModelGet(playerNo);
    modelId = MBModelIdGet(mdlId);
    modelP = &Hu3DData[modelId];
    MTXCopy(mtx, modelP->mtx);
}

static void MB4_ModelStub(HU3DMODEL *modelP)
{
}

static s16 MB4_PathLenGet(s16 masuId, s16 num)
{
    mb4_PathMasuNo = num;
    mb4_PathLen = num;
    mb4_PathValidF = 0;
    PathCheck(masuId, num);
    if(mb4_PathValidF != 0) {
        return mb4_PathLen;
    }
    return -1;
}

/* MWCC expands this recursion through four levels before emitting a call. */
static s16 PathCheck(s16 masuId, s16 num)
{
    MASU *masu;
    s16 i;
    s16 findF;
    s16 len;

    findF = 0;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(MBMasuTypeGet(MASU_LAYER_DEFAULT, masuId) == MASU_TYPE_STAR) {
        len = mb4_PathMasuNo-num;
        if(len < mb4_PathLen) {
            mb4_PathLen = len;
        }
        mb4_PathValidF = 1;
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
    if(findF != 0) {
        return 1;
    }
    return 0;
}

/* Preserve the reference's -6*t*t-6*t coefficient, despite the name. */
static float MB4_HermiteSlopeCalc(float t, float p0, float p1, float m0, float m1)
{
    float t2 = t*t;
    float h0 = (6*t2)-(6*t);
    float h1 = (-6*t2)-(6*t);
    float h2 = 1+((3*t2)-(4*t));
    float h3 = (3*t2)-(2*t);

    return (h3*m1)+((h2*m0)+((h0*p0)+(h1*p1)));
}

static float fn_1_DB68(float t, float p0, float p1, float p2, float p3)
{
    float m0 = 0.5f*((p2+(p1-p0))-p1);
    float m1 = 0.5f*((p2+(p1-p0))-p1);
    float a = m1+(m0+((2*p1)-(2*p2)));
    float b = (((-3*p1)+(3*p2))-(2*m0))-m1;
    float c = m0;

    return c+((t*((3*a)*t))+((2*b)*t));
}

/* Kept before PathTimeGet: this wrapper must call, not inline, that body. */
static float MB4_PathNextTimeGet(float t, float *p0, float *p1, float *p2, float *p3)
{
    /* The reference ignores t and always asks for the whole segment. */
    return MB4_PathTimeGet(1, p0, p1, p2, p3);
}

/* The fourth control point is unused in the reference's speed calculation. */
static float fn_1_DC9C(float t, float *p0, float *p1, float *p2, float *p3)
{
    float x = fn_1_DB68(t, p0[0], p1[0], p2[0], p3[0]);
    float y = fn_1_DB68(t, p0[1], p1[1], p2[1], p3[1]);
    float z = fn_1_DB68(t, p0[2], p1[2], p2[2], p3[2]);

    return sqrtf((x*x)+(y*y)+(z*z));
}

/* Simpson integration of the speed, with sixteen subintervals. */
static float MB4_PathTimeGet(float t, float *p0, float *p1, float *p2, float *p3)
{
    float start = 0;
    float end = t;
    int num = 16;
    float step = (end-start)/num;
    float step2 = step+step;
    float sum = fn_1_DC9C(start, p0, p1, p2, p3)+fn_1_DC9C(end, p0, p1, p2, p3);
    float time;
    int i;

    for(i=1, time=start+step; i<num; i+=2, time+=step2) {
        sum += fn_1_DC9C(time, p0, p1, p2, p3)*4;
    }
    for(i=2, time=start+step2; i<num; i+=2, time+=step2) {
        sum += fn_1_DC9C(time, p0, p1, p2, p3)*2;
    }
    return (step/3)*sum;
}

static void MB4_BubbleEffInit(void)
{
    OMOBJ *obj;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;
    HU3DMODEL *modelP;
    ANIMDATA *anim;

    obj = MBAddObj(32768, 1, 0, MB4_BubbleEffUpdate);
    mb4_BubbleEffObj = obj;
    anim = HuSprAnimRead(HuDataReadNum(W04_ANM_bubbleEff, HU_MEMNUM_OVL));
    obj->data = anim;
    obj->mdlId[0] = MBEffCreate(anim, 1024);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    modelP = &Hu3DData[obj->mdlId[0]];
    effP = modelP->hookData;
    data = effP->data;
    effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    for(i=0; i<effP->num; i++, data++) {
        data->scale = 0;
    }
}

static void MB4_BubbleEffUpdate(OMOBJ *obj)
{
    MBEFFECTDATA *data;
    MBEFFECT *effP;
    int i;
    HU3DMODEL *modelP;

    modelP = &Hu3DData[obj->mdlId[0]];
    effP = modelP->hookData;
    data = effP->data;
    if(MBKillCheck() || mb4_BubbleEffObj == NULL) {
        MBEffKill(obj->mdlId[0]);
        obj->mdlId[0] = HU3D_MODELID_NONE;
        obj->data = NULL;
        omDelObjEx(mbObjMan, obj);
        mb4_BubbleEffObj = NULL;
        return;
    }
    for(i=0; i<effP->num; i++, data++) {
        if(data->scale <= 0) {
            continue;
        }
        if(++data->time > 360) {
            data->time -= 360;
        }
        data->pos.x += data->vel.x*HuSin(2.0f*data->time);
        data->pos.y += data->vel.y;
        data->accel.x -= data->accel.y;
        data->color.a = 255*data->accel.x;
        if(data->accel.x < 0) {
            data->scale = 0;
        }
    }
}

static void MB4_BubbleEffClose(void)
{
    mb4_BubbleEffObj = NULL;
}

static int MB4_BubbleEffCreate(HuVecF *pos, float scale, int time)
{
    MBEFFECTDATA *data;
    MBEFFECT *effP;
    int i;
    HU3DMODEL *modelP;

    if(mb4_BubbleEffObj == NULL) {
        return -1;
    }
    modelP = &Hu3DData[mb4_BubbleEffObj->mdlId[0]];
    effP = modelP->hookData;
    data = effP->data;
    for(i=0; i<effP->num; i++, data++) {
        if(data->scale <= 0) {
            break;
        }
    }
    if(i >= effP->num) {
        return -1;
    }
    if(scale <= 0) {
        scale = 1;
    }
    data->pos = *pos;
    data->vel.x = 0.5f*(1.5f+(0.2f*MB4_RandF()));
    data->vel.z = 1.5f+(0.2f*MB4_RandF());
    data->vel.y = 2*(1.5f+(0.2f*MB4_RandF()));
    data->accel.x = 1;
    data->accel.y = 1.0f/time;
    data->time = frand()%360;
    data->scale = 20*scale;
    data->color.r = data->color.g = data->color.b = data->color.a = 255;
    return i;
}

static void MB4_MapViewHook(BOOL dispF)
{
    if(dispF != 0) {
        MBModelDispSet(mb4_Work.mapViewMdlId, FALSE);
    } else {
        MBModelDispSet(mb4_Work.mapViewMdlId, TRUE);
    }
}

static void MB4_CoinInit(void)
{
    OMOBJ *obj;
    MB4_COIN *base;
    MB4_COIN *coin;
    int i;
    int j;

    obj = mb4_CoinObj = MBAddObj(32768, 0, 0, MB4_CoinUpdate);
    base = coin = obj->data = HuMemDirectMallocNum(HEAP_HEAP, 32*sizeof(MB4_COIN), HU_MEMNUM_OVL);
    memset(coin, 0, 32*sizeof(MB4_COIN));
    mb4_CoinMaxDist.x = 100;
    mb4_CoinMaxDist.y = 170;
    mb4_CoinMaxDist.z = 0;
    for(i=0; i<32; i++, coin++) {
        if(i == 0) {
            coin->mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(BOARD_HSF_coin, HU_MEMNUM_OVL, HEAP_MODEL));
        } else {
            coin->mdlId = Hu3DModelLink(base->mdlId);
        }
        Hu3DModelCameraSet(coin->mdlId, 1);
        Hu3DModelAttrSet(coin->mdlId, HU3D_ATTR_DISPOFF);
        coin->linkMdlId = Hu3DModelLink(MBModelIdGet(mb4_Work.coinLinkMdlId));
        Hu3DModelAttrSet(coin->linkMdlId, HU3D_ATTR_DISPOFF);
        coin->useF = 0;
        coin->mode = 0;
        coin->speed = 0;
        coin->duration = coin->time = 0;
        for(j=0; j<4; j++) {
            MBPlayerPosGet(j, &coin->playerPos[j]);
        }
    }
}

static void MB4_CoinUpdate(OMOBJ *obj)
{
    MB4_COIN *coin = omObjGetDataAs(obj, MB4_COIN);
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

    if(MBKillCheck() || mb4_CoinObj == NULL) {
        for(i=0; i<32; i++, coin++) {
            Hu3DModelKill(coin->mdlId);
            coin->mdlId = -1;
            Hu3DModelKill(coin->linkMdlId);
            coin->linkMdlId = -1;
        }
        omDelObjEx(mbObjMan, obj);
        mb4_CoinObj = NULL;
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
            t = (float)++coin->time/(float)coin->duration;
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
                coin->time = 0;
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
                mag = vec.x*vec.x+vec.z*vec.z;
                if(sqrtf(mag) < mb4_CoinMaxDist.x) {
                    MBPlayerCoinAdd(j, 1);
                    MBAudFXPlay(7);
                    getF = 1;
                }
                coin->playerPos[j] = playerPos;
            }
        }
        Hu3DModelPosSet(coin->mdlId, coin->pos.x, coin->pos.y, coin->pos.z);
        Hu3DModelRotSet(coin->mdlId, coin->rot.x, coin->rot.y, coin->rot.z);
        Hu3DModelScaleSet(coin->mdlId, coin->scale.x, coin->scale.y, coin->scale.z);
        Hu3DModelPosSet(coin->linkMdlId, coin->pos.x, -200, coin->pos.z);
        Hu3DModelRotSet(coin->linkMdlId, coin->rot.x, coin->rot.y, coin->rot.z);
        Hu3DModelScaleSet(coin->linkMdlId, coin->scale.x, coin->scale.y, coin->scale.z);
        if(getF || killF) {
            coin->useF = 0;
            Hu3DModelAttrSet(coin->mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(coin->linkMdlId, HU3D_ATTR_DISPOFF);
            if(getF) {
                for(j=0, angle=0; j<32; j++) {
                    angle += 22.5f*(1+MB4_RandF());
                    pos = coin->pos;
                    t = 2.5f*(1+MB4_RandF());
                    angleY = 45-(90*MB4_RandF());
                    velRand.x = t*(HuSin(angle)*HuCos(angleY));
                    velRand.y = t*(HuCos(angle)*HuCos(angleY));
                    velRand.z = t*HuSin(angleY);
                    rate = MB4_RandF();
                    colRand.r = 192+(63*rate);
                    colRand.g = 192+(63*rate);
                    colRand.b = 64+(63*rate);
                    colRand.a = 192+(63*MB4_RandF());
                    col = colRand;
                    colP = &col;
                    vel = velRand;
                    velP = &vel;
                    posOut = pos;
                    posP = &posOut;
                    MB4_CoinEffCreate(posP, velP, 100*(0.3f+(0.1f*MB4_RandF())), 0.0166667f*(1+(0.5f*MB4_RandF())), 0, colP);
                }
                break;
            }
        }
    }
}

static void MB4_CoinClose(void)
{
    mb4_CoinObj = NULL;
}

static int MB4_CoinNumGet(void)
{
    MB4_COIN *coin;
    int i;
    int num;
    OMOBJ *obj;

    obj = mb4_CoinObj;
    num = 0;
    if(mb4_CoinObj == NULL) {
        return 0;
    }
    for(coin = omObjGetDataAs(obj, MB4_COIN), i=0; i<32; i++, coin++) {
        if(coin->useF != 0) {
            num++;
        }
    }
    return num;
}

static int MB4_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int duration)
{
    MB4_COIN *coin;
    int i;
    OMOBJ *obj;
    int mode;

    obj = mb4_CoinObj;
    mode = 0;
    if(mb4_CoinObj == NULL) {
        return -1;
    }
    for(coin = omObjGetDataAs(obj, MB4_COIN), i=0; i<32; i++, coin++) {
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
    coin->duration = duration;
    coin->time = 0;
    if(startPos != NULL) {
        coin->startPos = *startPos;
    }
    if(endPos != NULL) {
        coin->endPos = *endPos;
    }
    coin->pos = coin->startPos;
    coin->rot.x = coin->rot.y = coin->rot.z = 0;
    coin->scale.x = coin->scale.y = coin->scale.z = 1;
    coin->rot.y = 360*MB4_RandF();
    Hu3DModelPosSet(coin->mdlId, coin->pos.x, coin->pos.y, coin->pos.z);
    Hu3DModelRotSet(coin->mdlId, coin->rot.x, coin->rot.y, coin->rot.z);
    Hu3DModelScaleSet(coin->mdlId, coin->scale.x, coin->scale.y, coin->scale.z);
    Hu3DModelTPLvlSet(coin->mdlId, 1);
    Hu3DModelAttrReset(coin->mdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(coin->linkMdlId, coin->pos.x, -200, coin->pos.z);
    Hu3DModelRotSet(coin->linkMdlId, coin->rot.x, coin->rot.y, coin->rot.z);
    Hu3DModelScaleSet(coin->linkMdlId, coin->scale.x, coin->scale.y, coin->scale.z);
    Hu3DModelTPLvlSet(coin->linkMdlId, 1);
    Hu3DModelAttrReset(coin->linkMdlId, HU3D_ATTR_DISPOFF);
    return i;
}

static int MB4_CoinNearGet(HuVecF *pos, float maxDist, HuVecF *out)
{
    OMOBJ *obj = mb4_CoinObj;
    MB4_COIN *coin;
    int i;
    int nearNo;
    float dist;
    float nearDist;
    HuVecF vec;

    if(mb4_CoinObj == NULL) {
        return -1;
    }
    coin = omObjGetDataAs(obj, MB4_COIN);
    nearNo = -1;
    nearDist = 10000;
    for(i=0; i<32; i++, coin++) {
        if(coin->useF == 0) {
            continue;
        }
        PSVECSubtract(&coin->pos, pos, &vec);
        dist = PSVECMag(&vec);
        if(dist > maxDist) {
            continue;
        }
        if(dist < nearDist) {
            nearNo = i;
            nearDist = dist;
        }
    }
    coin = omObjGetDataAs(obj, MB4_COIN);
    if(nearNo >= 0) {
        *out = coin[nearNo].pos;
    }
    return nearNo;
}

static void MB4_CoinEffInit(void)
{
    OMOBJ *obj;
    MBEFFECT *effP;
    MB4_COINEFFWORK *work;
    HU3DMODEL *modelP;
    ANIMDATA *anim;
    int mdlId;

    obj = mb4_CoinEffObj = MBAddObj(32768, 0, 0, MB4_CoinEffUpdate);
    work = obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MB4_COINEFFWORK), HU_MEMNUM_OVL);
    memset(work, 0, sizeof(MB4_COINEFFWORK));
    anim = HuSprAnimRead(HuDataReadNum(CAPSULE_ANM_effCoin, HU_MEMNUM_OVL));
    work->anim = anim;
    work->modelId = mdlId = MBEffCreate(anim, 256);
    Hu3DModelLayerSet(work->modelId, 3);
    MBEffAttrReset(work->modelId, MB_EFFECT_ATTR_UPAUSE);
    work->num = 0;
    modelP = &Hu3DData[work->modelId];
    effP = modelP->hookData;
    effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
}

static void MB4_CoinEffUpdate(OMOBJ *obj)
{
    MB4_COINEFFWORK *work = omObjGetDataAs(obj, MB4_COINEFFWORK);
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;

    if(MBKillCheck() || mb4_CoinEffObj == NULL) {
        MBEffKill(work->modelId);
        work->modelId = -1;
        work->anim = NULL;
        omDelObjEx(mbObjMan, obj);
        mb4_CoinEffObj = NULL;
        return;
    }
    if(work->num <= 0) {
        Hu3DModelAttrSet(work->modelId, HU3D_ATTR_DISPOFF);
        return;
    }
    Hu3DModelAttrReset(work->modelId, HU3D_ATTR_DISPOFF);
    modelP = &Hu3DData[work->modelId];
    effP = modelP->hookData;
    data = effP->data;
    for(i=0; i<effP->num; i++, data++) {
        if(data->scale <= 0) {
            continue;
        }
        data->pos.x += data->vel.x;
        data->pos.y += data->vel.y;
        data->pos.z += data->vel.z;
        if(data->colorIdx) {
            data->vel.y -= data->colorIdx;
        }
        data->scale = data->accel.x*data->accel.y;
        data->accel.y -= data->accel.z;
        if(data->accel.y <= 0) {
            data->time = 0;
            data->scale = 0;
            work->num--;
        }
    }
}

static void MB4_CoinEffClose(void)
{
    mb4_CoinEffObj = NULL;
}

static int MB4_CoinEffNumGet(void)
{
    OMOBJ *obj = mb4_CoinEffObj;
    MB4_COINEFFWORK *work;

    if(mb4_CoinEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB4_COINEFFWORK);
    return work->num;
}

static void MB4_CoinEffBlendModeSet(int blendMode)
{
    OMOBJ *obj = mb4_CoinEffObj;
    MB4_COINEFFWORK *work;
    MBEFFECT *effP;
    HU3DMODEL *modelP;

    if(mb4_CoinEffObj == NULL) {
        return;
    }
    work = omObjGetDataAs(obj, MB4_COINEFFWORK);
    modelP = &Hu3DData[work->modelId];
    effP = modelP->hookData;
    effP->blendMode = blendMode;
}

static int MB4_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color)
{
    OMOBJ *obj;
    MB4_COINEFFWORK *work;
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;

    if(mb4_CoinEffObj == NULL) {
        return -1;
    }
    obj = mb4_CoinEffObj;
    work = omObjGetDataAs(obj, MB4_COINEFFWORK);
    modelP = &Hu3DData[work->modelId];
    effP = modelP->hookData;
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->scale <= 0) {
            break;
        }
    }
    if(i >= effP->num) {
        return -1;
    }
    data->time = data->parManId = 0;
    data->pos.x = pos->x;
    data->pos.y = pos->y;
    data->pos.z = pos->z;
    data->vel.x = vel->x;
    data->vel.y = vel->y;
    data->vel.z = vel->z;
    data->accel.x = scale;
    data->accel.y = 1;
    data->accel.z = decay;
    data->colorIdx = gravity;
    data->scale = scale;
    data->color = *color;
    data->rot.z = 360*MB4_RandF();
    data->time = 0;
    work->num++;
    return i;
}

static void MB4_SakanaInit(void)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    MB4_SAKANA *sakana;
    ANIMDATA *anim;
    int i;
    int j;

    anim = HuSprAnimRead(HuDataReadNum(W04_SPR_sakana, HU_MEMNUM_OVL));
    mb4_Work.sakanaEffMdlId = MBEffCreate(anim, 128);
    Hu3DModelLayerSet(mb4_Work.sakanaEffMdlId, 1);
    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = effP->data;
    for(j=0; j<effP->num; j++, data++) {
        data->dispF = 0;
    }
    MBEffAttrSet(mb4_Work.sakanaEffMdlId, MB_EFFECT_ATTR_3D);
    memset(mb4_Work.sakana, 0, sizeof(mb4_Work.sakana));
    for(i=0; i<14; i++) {
        for(j=0; j<16; j++) {
            mb4_Work.sakana[i][j].mdlId = -1;
        }
    }
    for(i=0; i<14; i++) {
        sakana = &mb4_Work.sakana[i][0];
        for(j=0; j<mb4ev_SakanaTbl[i].num; j++, sakana++) {
            if(mb4ev_SakanaTbl[i].unk1C != 0) {
                sakana->effNo = MB4_SakanaCreate((frand() & 0x7FFF) % 4);
                sakana->mdlId = -1;
            } else {
                switch((frand() & 0x7FFF) % 4) {
                    case 0:
                        sakana->mdlId = MBModelCreate(W04_HSF_sakana0, NULL, TRUE);
                        break;
                    case 1:
                        sakana->mdlId = MBModelCreate(W04_HSF_sakana1, NULL, TRUE);
                        break;
                    case 2:
                        sakana->mdlId = MBModelCreate(W04_HSF_sakana2, NULL, TRUE);
                        break;
                    default:
                        sakana->mdlId = MBModelCreate(W04_HSF_sakana3, NULL, TRUE);
                        break;
                }
                MBModelLayerSet(sakana->mdlId, 2);
                sakana->effNo = -1;
            }
            sakana->unk08 = frand();
            sakana->unk0C = frand();
            sakana->unk10 = 0;
            sakana->unk14 = 0;
            sakana->unk18 = ((MB4_RandF()*60)*2)+60;
            sakana->unk1C = (MB4_RandF()*10)+10;
            sakana->unk20 = (MB4_RandF()*60)*10;
            sakana->unk24 = ((MB4_RandF()*60)*2)+120;
            switch(mb4ev_SakanaTbl[i].unk20) {
                case 0:
                    sakana->unk28 = 0;
                    break;
                case 1:
                    sakana->unk28 = j & 1;
                    break;
                default:
                    sakana->unk28 = 1;
                    break;
            }
            sakana->unk2C = 1;
            sakana->pos = mb4ev_SakanaTbl[i].pos;
            sakana->range = mb4ev_SakanaTbl[i].range;
            sakana->targetPos.x = sakana->pos.x+((MB4_RandF()-0.5f)*sakana->range.x);
            sakana->targetPos.y = sakana->pos.y+((MB4_RandF()-0.5f)*sakana->range.y);
            sakana->targetPos.z = sakana->pos.z+((MB4_RandF()-0.5f)*sakana->range.z);
            sakana->curPos.x = sakana->pos.x+((MB4_RandF()-0.5f)*sakana->range.x);
            sakana->curPos.y = sakana->pos.y+((MB4_RandF()-0.5f)*sakana->range.y);
            sakana->curPos.z = sakana->pos.z+((MB4_RandF()-0.5f)*sakana->range.z);
            sakana->dir.x = MB4_RandF()-0.5f;
            sakana->dir.y = MB4_RandF()-0.5f;
            sakana->dir.z = MB4_RandF()-0.5f;
            PSVECNormalize(&sakana->dir, &sakana->dir);
            sakana->rot.x = 180.0*(atan2(sqrtf((sakana->dir.x*sakana->dir.x)+(sakana->dir.z*sakana->dir.z)),
                sakana->dir.y)/M_PI);
            sakana->rot.y = 180.0*(atan2(sakana->dir.x, sakana->dir.z)/M_PI);
            sakana->rot.z = 0;
            sakana->rot2 = sakana->rot;
            sakana->unk84 = 2.5f*(1+MB4_RandF());
            sakana->scale = 0.25f+(MB4_RandF()*0.5f);
            sakana->unk8C = 0.25f+(MB4_RandF()*0.25f);
            if(sakana->mdlId != -1) {
                MBModelPosSetV(sakana->mdlId, &sakana->curPos);
                MBModelRotSetV(sakana->mdlId, &sakana->rot);
                MBModelScaleSet(sakana->mdlId, sakana->scale, sakana->scale, sakana->scale);
                MBModelLayerSet(sakana->mdlId, 2);
            } else {
                MB4_SakanaPosSet(sakana->effNo, sakana->curPos.x, sakana->curPos.y, sakana->curPos.z);
                MB4_SakanaOffsetSet(sakana->effNo, sakana->rot.x, sakana->rot.y, sakana->rot.z);
                MB4_SakanaLenSet(sakana->effNo, sakana->scale);
            }
        }
    }
    mb4_Work.sakanaHookMdlId = Hu3DHookFuncCreate(MB4_SakanaDraw);
    Hu3DModelCameraSet(mb4_Work.sakanaHookMdlId, 1);
    Hu3DModelLayerSet(mb4_Work.sakanaHookMdlId, 7);
}

static void MB4_SakanaDraw(HU3DMODEL *modelP, Mtx *matrix)
{
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    HU3DMODEL *bubbleModelP;
    MBEFFECT *bubbleEffP;
    MBEFFECTDATA *bubbleData;
    MB4_SAKANA *sakana;
    HuVecF vec;
    HuVecF diff;
    float len;
    float speed;
    float cosX;
    float rotOfs;
    float bubbleScale;
    int bubbleTime;
    int i;
    int j;
    int k;

    if(MBPauseProcCheck()) {
        return;
    }
    for(i=0; i<14; i++) {
        sakana = &mb4_Work.sakana[i][0];
        for(j=0; j<mb4ev_SakanaTbl[i].num; j++, sakana++) {
            sakana->unk08++;
            len = 0;
            speed = sakana->unk84;
            if((sakana->unk08 & 3) == 0) {
                Hu3D3Dto2D(&sakana->curPos, 1, &vec);
                if((vec.x < 0 || vec.x > 640) && (vec.y < 0 || vec.y > 480)) {
                    sakana->unk2C = 0;
                } else {
                    sakana->unk2C = 1;
                }
            }
            if(sakana->unk2C == 0 && sakana->mdlId == -1) {
                modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
                effP = modelP->hookData;
                data = &effP->data[sakana->effNo];
                data->dispF = 0;
                continue;
            }
            if(sakana->unk28 == 0) {
                PSVECSubtract(&sakana->targetPos, &sakana->curPos, &diff);
                if(--sakana->unk10 <= 0) {
                    len = PSVECMag(&diff);
                    PSVECSubtract(&sakana->pos, &sakana->curPos, &vec);
                    if(len <= sakana->unk84 || --sakana->unk24 <= 0
                        || fabs(vec.x) > sakana->range.x
                        || fabs(vec.y) > sakana->range.y
                        || fabs(vec.z) > sakana->range.z) {
                        sakana->targetPos.x = sakana->pos.x+((MB4_RandF()-0.5f)*sakana->range.x);
                        sakana->targetPos.y = sakana->pos.y+((MB4_RandF()-0.5f)*sakana->range.y);
                        sakana->targetPos.z = sakana->pos.z+((MB4_RandF()-0.5f)*sakana->range.z);
                        sakana->unk10 = 60;
                        sakana->unk24 = ((MB4_RandF()*60)*2)+120;
                    }
                }
                if(--sakana->unk18 <= 0) {
                    rotOfs = 15.0*sin((M_PI*sakana->unk14)/180.0);
                    if((sakana->unk14 += 5) >= 720) {
                        sakana->unk14 = 0;
                        sakana->unk18 = ((MB4_RandF()*60)*2)+60;
                    }
                } else {
                    rotOfs = 0;
                }
                if(--sakana->unk20 <= 0) {
                    if((sakana->unk1C & 3) == 0) {
                        PSVECScale(&sakana->dir, &vec, 50*sakana->scale);
                        PSVECAdd(&sakana->curPos, &vec, &vec);
                        bubbleTime = 120*(1+(MB4_RandF()*0.2f));
                        bubbleScale = sakana->scale*(0.5f+MB4_RandF());
                        if(mb4_BubbleEffObj != NULL) {
                            bubbleModelP = &Hu3DData[mb4_BubbleEffObj->mdlId[0]];
                            bubbleEffP = bubbleModelP->hookData;
                            bubbleData = bubbleEffP->data;
                            for(k=0; k<bubbleEffP->num; k++, bubbleData++) {
                                if(bubbleData->scale <= 0) {
                                    break;
                                }
                            }
                            if(k < bubbleEffP->num) {
                                if(bubbleScale <= 0) {
                                    bubbleScale = 1;
                                }
                                bubbleData->pos = vec;
                                bubbleData->vel.x = 0.5f*(1.5f+(0.2f*MB4_RandF()));
                                bubbleData->vel.z = 1.5f+(0.2f*MB4_RandF());
                                bubbleData->vel.y = 2*(1.5f+(0.2f*MB4_RandF()));
                                bubbleData->accel.x = 1;
                                bubbleData->accel.y = 1.0f/bubbleTime;
                                bubbleData->time = frand()%360;
                                bubbleData->scale = 20*bubbleScale;
                                bubbleData->color.r = bubbleData->color.g =
                                    bubbleData->color.b = bubbleData->color.a = 255;
                            }
                        }
                    }
                    if(--sakana->unk1C <= 0) {
                        sakana->unk1C = (MB4_RandF()*10)+10;
                        sakana->unk20 = 300+((MB4_RandF()*60)*5);
                    }
                }
                sakana->rot2.x = 180.0*(atan2(diff.y,
                    sqrtf((diff.x*diff.x)+(diff.z*diff.z)))/M_PI);
                sakana->rot2.y = 180.0*(atan2(diff.x, diff.z)/M_PI);
            } else {
                PSVECSubtract(&sakana->targetPos, &sakana->curPos, &diff);
                if((sakana->unk08 & 1) == 0 && --sakana->unk10 <= 0) {
                    len = PSVECMag(&diff);
                    if(len <= sakana->unk84 || --sakana->unk24 <= 0) {
                        sakana->targetPos.x = sakana->pos.x+((MB4_RandF()-0.5f)*sakana->range.x);
                        sakana->targetPos.y = sakana->pos.y+((MB4_RandF()-0.5f)*sakana->range.y);
                        sakana->targetPos.z = sakana->pos.z+((MB4_RandF()-0.5f)*sakana->range.z);
                        sakana->unk10 = 60;
                        sakana->unk24 = ((MB4_RandF()*60)*2)+120;
                    }
                }
                if((sakana->unk08 & 3) == 0) {
                    sakana->rot2.x = 180.0*(atan2(diff.y,
                        sqrtf((diff.x*diff.x)+(diff.z*diff.z)))/M_PI);
                    sakana->rot2.y = 180.0*(atan2(diff.x, diff.z)/M_PI);
                }
            }
            sakana->rot.x = MB4_AngleLerp(sakana->rot2.x, sakana->rot.x, 2.5f);
            sakana->rot.y = MB4_AngleLerp(sakana->rot2.y, sakana->rot.y, 2.5f);
            sakana->rot.z = 0;
            cosX = cos((M_PI*sakana->rot.x)/180.0);
            sakana->dir.y = sin((M_PI*sakana->rot.x)/180.0);
            sakana->dir.x = cosX*sin((M_PI*sakana->rot.y)/180.0);
            sakana->dir.z = cosX*cos((M_PI*sakana->rot.y)/180.0);
            if(len > 1000) {
                speed = speed*2;
            }
            sakana->unk0C = sakana->unk0C+(1+(MB4_RandF()*3));
            if(sakana->unk0C > 360) {
                sakana->unk0C -= 360;
            }
            PSVECScale(&sakana->dir, &vec,
                speed*(0.5+fabs(0.5*sin((M_PI*sakana->unk0C)/180.0))));
            PSVECAdd(&sakana->curPos, &vec, &sakana->curPos);
            if(sakana->mdlId != -1) {
                if(sakana->unk2C == 0) {
                    MBModelDispSet(sakana->mdlId, FALSE);
                } else {
                    MBModelDispSet(sakana->mdlId, TRUE);
                    MBModelPosSetV(sakana->mdlId, &sakana->curPos);
                    MBModelRotSet(sakana->mdlId, -sakana->rot.x, sakana->rot.y+rotOfs,
                        sakana->rot.z);
                }
            } else {
                modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
                effP = modelP->hookData;
                data = &effP->data[sakana->effNo];
                if(sakana->unk2C == 0) {
                    data->dispF = 0;
                } else {
                    data->dispF = 1;
                    data->pos = sakana->curPos;
                    data->rot = sakana->rot;
                    data->rot.y -= 90;
                }
            }
        }
    }
}

static void MB4_SakanaClose(void)
{
    if(mb4_Work.sakanaEffMdlId != -1) {
        MBEffKill(mb4_Work.sakanaEffMdlId);
    }
    mb4_Work.sakanaEffMdlId = -1;
    if(mb4_Work.sakanaHookMdlId != -1) {
        Hu3DModelKill(mb4_Work.sakanaHookMdlId);
    }
    mb4_Work.sakanaHookMdlId = -1;
}

static int MB4_SakanaCreate(int type)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;
    int animBank;

    if(mb4_Work.sakanaEffMdlId == -1) {
        return -1;
    }
    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = effP->data;
    for(i=0; i<effP->num; i++, data++) {
        if(data->dispF == 0) {
            break;
        }
    }
    if(i >= effP->num) {
        return -1;
    }
    data->dispF = 1;
    data->pos.x = data->pos.y = data->pos.z = 0;
    data->rot.x = data->rot.y = data->rot.z = 0;
    data->scale = 100;
    /* The original stores an uninitialised scratch register here. */
    data->animBank = animBank;
    data->color.r = data->color.g = data->color.b = data->color.a = 255;
    return i;
}

static void MB4_SakanaOffsetInit(void)
{
    MB4_SAKANA *sakana;
    int i;
    int j;

    for(i=0; i<14; i++) {
        sakana = &mb4_Work.sakana[i][0];
        if(mb4ev_SakanaTbl[i].unk1C == 0) {
            for(j=0; j<mb4ev_SakanaTbl[i].num; j++, sakana++) {
                sakana->pos.y = 500;
                sakana->pos.z = 3600;
            }
        }
    }
}

static void MB4_SakanaPosInit(void)
{
    MB4_SAKANA *sakana;
    int i;
    int j;

    for(i=0; i<14; i++) {
        sakana = &mb4_Work.sakana[i][0];
        if(mb4ev_SakanaTbl[i].unk1C == 0) {
            for(j=0; j<mb4ev_SakanaTbl[i].num; j++, sakana++) {
                sakana->pos = mb4ev_SakanaTbl[i].pos;
            }
        }
    }
}

static void MB4_SakanaPosSet(int no, float x, float y, float z)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;

    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = &effP->data[no];
    data->pos.x = x;
    data->pos.y = y;
    data->pos.z = z;
}

static void MB4_SakanaOffsetSet(int no, float x, float y, float z)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;

    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = &effP->data[no];
    data->rot.x = x;
    data->rot.y = y-90;
    data->rot.z = z;
}

static void MB4_SakanaLenSet(int no, float len)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;

    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = &effP->data[no];
    data->scale = 100*len;
}
