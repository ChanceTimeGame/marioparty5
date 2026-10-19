/*
 * w04sDll world04.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/w04sDll/asm/REL/w04sDll/world04.s.
 */

#include "REL/w04sDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
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
#include "game/board/audio.h"
#include "game/board/camera.h"
#include "game/board/com.h"
#include "game/board/window.h"
#include "game/board/coin.h"
#include "game/esprite.h"
#include "game/gamemes.h"
#include "game/hsfex.h"
#include "datanum/board.h"
#include "datanum/capsule.h"
#include "datanum/charmot.h"
#include "messnum/board_w04.h"
#include "humath.h"
#include "math.h"


#include "game/board/main.h"
#include "game/process.h"
#include "datadir_enum.h"
#define W04S_ANM_bubbleEff DATANUM(DATA_w04s, 0x32)
#define W04S_SPR_sakana DATANUM(DATA_w04s, 0x34)
#define W04S_HSF_sakana0 DATANUM(DATA_w04s, 0x1A)
#define W04S_HSF_sakana1 DATANUM(DATA_w04s, 0x1B)
#define W04S_HSF_sakana2 DATANUM(DATA_w04s, 0x1C)
#define W04S_HSF_sakana3 DATANUM(DATA_w04s, 0x1D)
#define MB4_RandF() (0.007874016f*(frand() & 0x7F))

#define MB4EV_MASU_KIHON MASU_FLAG_BIT(0)
#define MB4EV_MASU_IRUKA MASU_FLAG_BIT(0)|MASU_FLAG_BIT(2) /* unparenthesised: the retail test is (flag & 1) | 4 */
#define MB4EV_MASU_BLOW MASU_FLAG_BIT(6)
#define MB4EV_MASU_BLOWDEST MASU_FLAG_BIT(7)
#define MB4EV_MASU_KAISOO MASU_FLAG_BIT(8)
#define MB4EV_MASU_PUKU MASU_FLAG_BIT(4)


typedef struct MB4BubbleEmit_s {
    int wait;
    int num;
    int time;
} MB4_BUBBLEEMIT;

/* One fish. 224 of them, laid out by MB4_SakanaInit and moved by MB4_SakanaDraw. */
typedef struct MB4Sakana_s {
    int mdlId;                     /* 0x00, -1 when the fish is a sprite */
    int effNo;                     /* 0x04, -1 when the fish is a model */
    int unk08;
    int unk0C;
    int unk10;
    int unk14;
    int unk18;
    int unk1C;
    int unk20;
    int unk24;
    int unk28;
    int unk2C;
    HuVecF pos;                    /* 0x30, the shoal's centre */
    HuVecF range;                  /* 0x3C */
    HuVecF targetPos;              /* 0x48 */
    HuVecF curPos;                 /* 0x54 */
    HuVecF dir;                    /* 0x60 */
    HuVecF rot;                    /* 0x6C */
    HuVecF rot2;                   /* 0x78 */
    float unk84;
    float scale;
    float unk8C;
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
    MB4_BUBBLEEMIT playerBubble[4];/* 0x058 */
    MB4_BUBBLEEMIT capsuleEmit;    /* 0x088, the capsule being animated */
    int capsuleNo;                 /* 0x094 */
    int capsuleMdlId;              /* 0x098 */
    int capsuleEndF;               /* 0x09C */
    int capsuleFlag;               /* 0x0A0 */
    MB4_BUBBLEEMIT storyEmit;      /* 0x0A4, the same for a story event */
    int storyCapsuleNo;            /* 0x0B0 */
    int storyMdlId;                /* 0x0B4 */
    int storyEndF;                 /* 0x0B8 */
    MB4_BUBBLEEMIT bubble[13];     /* 0x0BC */
    MB4_BUBBLEEMIT pukuBubble;     /* 0x158 */
    MB4_BUBBLEEMIT irukaBubble;    /* 0x164 */
    MB4_SAKANA sakana[14][16];     /* 0x170 */
    int sakanaEffMdlId;            /* 0x7F70 */
    int sakanaHookMdlId;           /* 0x7F74 */
} MB4_WORK;                        /* 0x7F78 */

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


/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 0.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 180.0f; /* 0x14 */
static const float lbl_1_rodata_18 = -45.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 2.0f; /* 0x1C */
static const float lbl_1_rodata_20 = 10.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 60.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 0.007874016f; /* 0x28 */
static const float lbl_1_rodata_2C = 5.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 12.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 20000.0f; /* 0x34 */
/* 0x38 lbl_1_rodata_38 = 4503599627370496: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_40 = 300.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 1.5f; /* 0x44 */
static const float lbl_1_rodata_48 = 0.5f; /* 0x48 */
static const float lbl_1_rodata_4C = 120.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 1.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 0.2f; /* 0x54 */
static const float lbl_1_rodata_58 = 100.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 0.25f; /* 0x5C */
static const float lbl_1_rodata_60 = 45.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 1000.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 250000.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 0.3f; /* 0x6C */
static const float lbl_1_rodata_70 = -3700.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 12000.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 22000.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 3700.0f; /* 0x7C */
static const float lbl_1_rodata_80 = -12000.0f; /* 0x80 */
static const float lbl_1_rodata_84 = -22000.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 2000.0f; /* 0x88 */
static const float lbl_1_rodata_8C = -1.0f; /* 0x8C */
static const double lbl_1_rodata_90 = 0.5; /* 0x90 */
static const double lbl_1_rodata_98 = 3.0; /* 0x98 */
static const double lbl_1_rodata_A0 = 180.0; /* 0xA0 */
static const double lbl_1_rodata_A8 = 3.141592653589793; /* 0xA8 */
static const double lbl_1_rodata_B0 = 90.0; /* 0xB0 */
static const float lbl_1_rodata_B8 = 360.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = -180.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 30.000002f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 2.5f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 8.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 24.0f; /* 0xCC */
static const double lbl_1_rodata_D0 = 200.0; /* 0xD0 */
static const float lbl_1_rodata_D8 = 30.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 50.0f; /* 0xDC */
/* 0xE0 lbl_1_rodata_E0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_E8 = 250.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 0.7f; /* 0xEC */
static const float lbl_1_rodata_F0 = -100.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 0.75f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 0.8f; /* 0xF8 */
static const float lbl_1_rodata_FC = 4.0f; /* 0xFC */
static const double lbl_1_rodata_100 = 0.4000000059604645; /* 0x100 */
static const double lbl_1_rodata_108 = 100.0; /* 0x108 */
static const double lbl_1_rodata_110 = 0.6000000238418579; /* 0x110 */
/* 0x118 lbl_1_rodata_118 (0xC): 0x42820000 0xC1A00000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_124 = 1.2f; /* 0x124 */
static const float lbl_1_rodata_128 = 3.0f; /* 0x128 */
static const double lbl_1_rodata_130 = 360.0; /* 0x130 */
static const double lbl_1_rodata_138 = 0.0; /* 0x138 */
static const double lbl_1_rodata_140 = 1.0; /* 0x140 */
static const double lbl_1_rodata_148 = 2.0; /* 0x148 */
static const float lbl_1_rodata_150 = 6.0f; /* 0x150 */
static const float lbl_1_rodata_154 = -6.0f; /* 0x154 */
static const float lbl_1_rodata_158 = -3.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 170.0f; /* 0x15C */
static const float lbl_1_rodata_160 = -200.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 22.5f; /* 0x164 */
static const float lbl_1_rodata_168 = 90.0f; /* 0x168 */
static const float lbl_1_rodata_16C = 192.0f; /* 0x16C */
static const float lbl_1_rodata_170 = 63.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 64.0f; /* 0x174 */
static const float lbl_1_rodata_178 = 0.1f; /* 0x178 */
static const float lbl_1_rodata_17C = 0.016666668f; /* 0x17C */
static const float lbl_1_rodata_180 = 255.0f; /* 0x180 */
static const float lbl_1_rodata_184 = 20.0f; /* 0x184 */
static const float lbl_1_rodata_188 = 640.0f; /* 0x188 */
static const float lbl_1_rodata_18C = 480.0f; /* 0x18C */
static const double lbl_1_rodata_190 = 15.0; /* 0x190 */
static const double lbl_1_rodata_198 = 2.5; /* 0x198 */
static const float lbl_1_rodata_1A0 = -2.5f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 500.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 3600.0f; /* 0x1A8 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x20 */ static MB4_WORK mb4_Work;
/* 0x14 */ static HuVecF mb4_CoinMaxDist;
/* 0xC */ static OMOBJ *mb4_BubbleEffObj[2];
/* 0x8 */ static OMOBJ *mb4_CoinEffObj;
/* 0x4 */ static OMOBJ *mb4_CoinObj;
/* 0x0 */ static OMOBJ *mb4_MainObj;

static void MB4_CoinUpdate(OMOBJ *obj);
static void MB4_CoinEffUpdate(OMOBJ *obj);
static void MB4_BubbleEffUpdate(OMOBJ *obj);
static void MB4_SakanaDraw(HU3DMODEL *modelP, Mtx *matrix);

/* --- functions (reference order), .data placed before its first user --- */
/* 21 insns */
void ObjectSetup(void)
{
    GWPartyFSet(FALSE);
    MBObjectSetup(MBNO_WORLD_4, MB4_Create, MB4_Kill);
}

/* 0x0 */ static HuVecF mb4ev_Iruka1Path[100] = { { -4600.0f, 1300.0f, -900.0f }, { -4573.034f, 1215.942f, -794.85f }, { -4544.73f, 1132.205f, -689.8f }, { -4513.416f, 1049.226f, -585.01f }, { -4477.566f, 967.475f, -480.72f }, { -4435.419f, 887.62f, -377.35f }, { -4384.58f, 810.739f, -275.66f }, { -4323.074f, 738.184f, -176.79f }, { -4249.07f, 672.183f, -81.97f }, { -4160.644f, 617.657f, 7.49f }, { -4058.945f, 578.597f, 90.56f }, { -3944.98f, 561.026f, 164.61f }, { -3823.432f, 568.291f, 227.2f }, { -3699.797f, 597.694f, 278.49f }, { -3578.163f, 647.115f, 318.11f }, { -3459.058f, 707.638f, 349.44f }, { -3341.585f, 773.989f, 374.69f }, { -3224.757f, 843.131f, 395.06f }, { -3107.58f, 912.766f, 411.43f }, { -2989.013f, 980.773f, 424.23f }, { -2867.965f, 1044.797f, 433.81f }, { -2743.589f, 1102.422f, 440.47f }, { -2615.203f, 1150.621f, 444.48f }, { -2483.086f, 1187.473f, 447.73f }, { -2348.475f, 1213.249f, 454.57f }, { -2213.311f, 1227.102f, 473.29f }, { -2081.168f, 1232.415f, 509.11f }, { -1957.498f, 1231.019f, 567.86f }, { -1851.292f, 1225.498f, 654.06f }, { -1763.937f, 1219.431f, 759.23f }, { -1694.664f, 1214.386f, 877.27f }, { -1640.016f, 1210.498f, 1002.92f }, { -1596.901f, 1207.319f, 1133.08f }, { -1563.512f, 1204.522f, 1266.16f }, { -1540.919f, 1201.896f, 1401.55f }, { -1528.823f, 1199.182f, 1538.2f }, { -1526.122f, 1196.246f, 1675.26f }, { -1533.445f, 1192.971f, 1812.16f }, { -1552.651f, 1189.182f, 1948.05f }, { -1589.148f, 1184.45f, 2080.26f }, { -1641.263f, 1178.752f, 2206.74f }, { -1710.92f, 1171.903f, 2324.09f }, { -1798.882f, 1163.809f, 2428.28f }, { -1903.649f, 1154.56f, 2516.1f }, { -2022.11f, 1144.44f, 2584.75f }, { -2149.236f, 1133.875f, 2635.01f }, { -2280.944f, 1123.16f, 2670.97f }, { -2415.632f, 1112.423f, 2693.74f }, { -2552.093f, 1101.768f, 2703.95f }, { -2688.82f, 1091.436f, 2697.05f }, { -2824.026f, 1081.525f, 2676.92f }, { -2956.389f, 1072.172f, 2643.12f }, { -3083.968f, 1063.592f, 2594.07f }, { -3203.715f, 1056.114f, 2527.62f }, { -3309.018f, 1050.414f, 2439.71f }, { -3393.361f, 1047.014f, 2331.75f }, { -3455.068f, 1045.914f, 2209.62f }, { -3494.793f, 1046.942f, 2078.71f }, { -3514.608f, 1049.839f, 1943.33f }, { -3516.697f, 1054.371f, 1806.49f }, { -3502.782f, 1060.369f, 1670.29f }, { -3473.965f, 1067.733f, 1536.37f }, { -3429.652f, 1076.524f, 1406.73f }, { -3369.243f, 1086.809f, 1283.95f }, { -3293.864f, 1098.483f, 1170.1f }, { -3202.549f, 1111.615f, 1069.02f }, { -3095.122f, 1126.004f, 985.74f }, { -2974.3f, 1140.465f, 923.35f }, { -2844.74f, 1153.207f, 880.98f }, { -2710.435f, 1162.641f, 855.45f }, { -2573.958f, 1167.527f, 843.04f }, { -2436.802f, 1166.807f, 840.4f }, { -2299.857f, 1159.412f, 844.67f }, { -2163.769f, 1144.101f, 853.37f }, { -2029.225f, 1119.318f, 864.15f }, { -1897.25f, 1083.095f, 874.53f }, { -1769.587f, 1033.109f, 881.67f }, { -1648.902f, 967.666f, 882.65f }, { -1535.579f, 890.392f, 877.24f }, { -1428.51f, 805.261f, 865.81f }, { -1325.802f, 715.8f, 848.75f }, { -1225.205f, 625.121f, 826.32f }, { -1124.34f, 536.198f, 798.69f }, { -1020.825f, 452.239f, 765.9f }, { -912.448f, 377.062f, 728.06f }, { -797.591f, 315.291f, 685.56f }, { -675.965f, 271.969f, 639.4f }, { -549.439f, 250.277f, 591.32f }, { -421.237f, 247.636f, 542.77f }, { -293.426f, 259.594f, 494.53f }, { -166.838f, 282.362f, 446.87f }, { -41.67f, 313.172f, 399.83f }, { 82.119f, 350.086f, 353.37f }, { 204.255f, 392.945f, 307.6f }, { 325.221f, 439.427f, 262.32f }, { 445.375f, 488.293f, 217.37f }, { 564.767f, 539.297f, 172.73f }, { 683.414f, 592.263f, 128.39f }, { 801.814f, 645.861f, 84.15f }, { 920.001f, 700.0f, 40.0f } };
/* 0x4B0 */ static HuVecF mb4ev_Iruka2Path[100] = { { 30.0f, 1300.0f, -1720.0f }, { -47.566f, 1238.304f, -1649.92f }, { -125.145f, 1176.869f, -1579.63f }, { -202.737f, 1115.75f, -1509.08f }, { -280.367f, 1055.518f, -1437.81f }, { -358.027f, 996.322f, -1365.71f }, { -435.711f, 938.232f, -1292.75f }, { -513.417f, 881.719f, -1218.58f }, { -591.103f, 827.912f, -1142.41f }, { -668.706f, 776.704f, -1064.41f }, { -746.137f, 728.8f, -984.19f }, { -823.236f, 685.211f, -901.23f }, { -899.702f, 647.404f, -814.89f }, { -974.847f, 618.029f, -724.2f }, { -1047.915f, 598.881f, -629.22f }, { -1118.603f, 591.128f, -530.88f }, { -1186.982f, 595.538f, -430.72f }, { -1253.854f, 610.659f, -330.6f }, { -1320.317f, 634.523f, -231.91f }, { -1387.563f, 664.981f, -135.59f }, { -1456.694f, 699.925f, -42.16f }, { -1528.565f, 737.493f, 48.12f }, { -1603.721f, 776.158f, 135.23f }, { -1682.624f, 814.692f, 219.03f }, { -1765.479f, 852.021f, 299.49f }, { -1850.618f, 888.18f, 378.07f }, { -1937.204f, 923.24f, 455.57f }, { -2024.679f, 957.266f, 532.54f }, { -2112.543f, 989.893f, 609.67f }, { -2200.01f, 1021.283f, 687.75f }, { -2286.826f, 1051.634f, 766.95f }, { -2372.656f, 1080.806f, 847.67f }, { -2456.146f, 1108.152f, 931.42f }, { -2537.599f, 1134.236f, 1017.5f }, { -2616.829f, 1159.014f, 1106.04f }, { -2691.322f, 1181.394f, 1199.22f }, { -2761.465f, 1201.833f, 1296.05f }, { -2827.299f, 1220.443f, 1396.22f }, { -2886.777f, 1236.524f, 1500.8f }, { -2938.752f, 1250.159f, 1609.57f }, { -2984.883f, 1262.201f, 1721.06f }, { -3024.678f, 1272.698f, 1835.21f }, { -3054.541f, 1281.331f, 1952.54f }, { -3075.056f, 1288.738f, 2071.83f }, { -3085.615f, 1295.173f, 2192.37f }, { -3084.213f, 1300.79f, 2313.38f }, { -3068.217f, 1305.828f, 2433.4f }, { -3034.502f, 1310.627f, 2549.82f }, { -2979.893f, 1315.628f, 2658.11f }, { -2903.412f, 1321.292f, 2752.13f }, { -2808.775f, 1327.729f, 2827.56f }, { -2702.295f, 1334.355f, 2884.86f }, { -2588.762f, 1340.644f, 2926.45f }, { -2471.083f, 1346.236f, 2954.49f }, { -2351.045f, 1350.864f, 2970.46f }, { -2229.864f, 1354.278f, 2975.18f }, { -2108.797f, 1355.756f, 2966.56f }, { -1989.408f, 1354.891f, 2945.38f }, { -1873.189f, 1351.241f, 2911.53f }, { -1762.601f, 1343.93f, 2863.08f }, { -1661.895f, 1331.746f, 2797.57f }, { -1577.712f, 1313.429f, 2713.26f }, { -1516.148f, 1288.789f, 2612.46f }, { -1477.864f, 1259.183f, 2501.71f }, { -1459.951f, 1226.047f, 2386.67f }, { -1458.94f, 1190.313f, 2270.88f }, { -1472.018f, 1152.467f, 2156.41f }, { -1497.278f, 1112.674f, 2044.6f }, { -1534.048f, 1070.77f, 1936.77f }, { -1581.927f, 1026.417f, 1834.46f }, { -1640.686f, 979.221f, 1739.39f }, { -1711.573f, 928.4f, 1655.1f }, { -1797.968f, 872.935f, 1590.9f }, { -1896.463f, 815.329f, 1550.87f }, { -2002.128f, 758.524f, 1534.83f }, { -2110.603f, 704.582f, 1539.08f }, { -2219.414f, 654.16f, 1557.54f }, { -2328.029f, 606.422f, 1583.09f }, { -2436.758f, 560.742f, 1611.79f }, { -2546.105f, 516.521f, 1640.44f }, { -2656.529f, 473.412f, 1666.5f }, { -2768.341f, 431.944f, 1689.06f }, { -2881.765f, 393.235f, 1708.2f }, { -2996.979f, 358.541f, 1724.05f }, { -3114.077f, 329.244f, 1736.66f }, { -3233.005f, 306.908f, 1745.99f }, { -3353.539f, 294.068f, 1751.71f }, { -3474.806f, 292.229f, 1753.9f }, { -3595.535f, 303.276f, 1752.5f }, { -3713.979f, 328.487f, 1747.56f }, { -3828.605f, 367.124f, 1739.47f }, { -3938.836f, 416.572f, 1728.86f }, { -4044.712f, 474.442f, 1716.29f }, { -4146.529f, 538.916f, 1702.17f }, { -4244.685f, 608.609f, 1686.83f }, { -4339.625f, 682.438f, 1670.51f }, { -4431.524f, 759.848f, 1653.35f }, { -4521.49f, 839.392f, 1635.69f }, { -4610.758f, 919.682f, 1617.84f }, { -4700.0f, 1000.0f, 1600.0f } };
/* 0x960 */ static HuVecF mb4ev_KaiPosTbl[3] = { { 1784.0f, 190.0f, 1017.0f }, { 1883.0f, 190.0f, 1116.0f }, { 1983.0f, 190.0f, 1215.0f } };
/* 0x984 */ static HuVecF mb4ev_Puku2Pos = { 2041.0f, 230.0f, 958.0f };
/* 0x990 */ static MB4_SAKANATBL mb4ev_SakanaTbl[14] = { { { 31.0f, 321.0f, -171.0f }, { 1.1e+03f, 1e+02f, 7e+02f }, 3, 1, 1 }, { { -1655.0f, 721.0f, 2.08e+03f }, { 2.6e+03f, 5e+02f, 1e+03f }, 3, 0, 0 }, { { 1125.0f, 621.0f, 2.08e+03f }, { 2.3e+03f, 5e+02f, 1e+03f }, 2, 0, 0 }, { { -4.54e+03f, 221.0f, 591.0f }, { 1e+03f, 3e+02f, 8e+02f }, 2, 1, 1 }, { { -4.54e+03f, 221.0f, -1091.0f }, { 1e+03f, 3e+02f, 1e+03f }, 3, 1, 1 }, { { -1523.0f, 996.0f, -1799.0f }, { 1.5e+03f, 2.5e+02f, 6e+02f }, 4, 1, 1 }, { { 0.0f, 496.0f, -2027.0f }, { 1.7e+03f, 5e+02f, 9e+02f }, 6, 1, 1 }, { { 1.3e+03f, 896.0f, -3027.0f }, { 1.5e+03f, 5e+02f, 9e+02f }, 3, 1, 1 }, { { 4386.0f, 271.0f, -1e+03f }, { 1e+03f, 3e+02f, 8e+02f }, 3, 1, 1 }, { { 4386.0f, 271.0f, 0.0f }, { 1e+03f, 3e+02f, 8e+02f }, 2, 1, 1 }, { { -2502.0f, 996.0f, 654.0f }, { 2e+03f, 2e+02f, 7e+02f }, 2, 0, 0 }, { { 2516.0f, 1.2e+03f, 465.0f }, { 1.9e+03f, 2e+02f, 7e+02f }, 2, 0, 0 }, { { 202.0f, 1296.0f, -354.0f }, { 2e+03f, 2e+02f, 7e+02f }, 2, 0, 0 }, { { 2502.0f, 696.0f, 1254.0f }, { 1e+03f, 2e+02f, 7e+02f }, 1, 0, 0 } };
/* 0xB88 */ static HuVecF mb4ev_RBokPosTbl[1] = { { -3100.0f, -150.0f, 2450.0f } };
/* 0xB94 */ static float mb4ev_RBokRotYTbl[1] = { 0.0f }; /* w04dll has [2] */
/* 0xB98 */ static HuVecF mb4ev_YaziPosTbl[3] = { { -2240.0f, 1167.0f, -972.0f }, { -3724.0f, 1010.0f, -1010.0f }, { -2511.0f, 515.0f, -78.0f } };
/* 0xBBC */ static float mb4ev_YaziRotTbl[3] = { 8.0f, -12.0f, 18.0f };
/* 0xBC8 */ static HuVecF mb4ev_YaziExtPosTbl[1] = { { -1303.0f, 7.0f, 545.0f } };
/* 0xBD4 */ static float mb4ev_YaziExtRotTbl[1] = { 35.0f };
/* 0xBD8 */ static HuVecF mb4ev_HasigoPosTbl[2] = { { -3856.0f, 480.0f, -32.0f }, { -2610.0f, 0.0f, 560.0f } };
/* 0xBF0 */ static HuVecF mb4ev_HasigoRotTbl[2] = { { -10.0f, -5.0f, 0.0f }, { -5.0f, 30.0f, 0.0f } };
/* 0xC08 */ static HuVecF mb4ev_Sango1PosTbl[3] = { { -3900.0f, 85.0f, 1190.0f }, { -2580.0f, 953.0f, -2095.0f }, { -904.0f, 367.0f, -1707.0f } };
/* 0xC2C */ static HuVecF mb4ev_Sango1RotTbl[3] = { { 0.0f, 0.0f, 0.0f }, { -60.0f, -135.0f, 54.0f }, { -75.0f, -150.0f, 78.0f } };
/* 0xC50 */ static float mb4ev_Sango1ScaleTbl[3] = { 1.0f, 1.0f, 0.95f };
/* 0xC5C */ static HuVecF mb4ev_Sango2PosTbl[2] = { { -609.0f, -84.0f, 174.0f }, { -3963.0f, 397.0f, -123.0f } };
/* 0xC74 */ static HuVecF mb4ev_Sango2RotTbl[2] = { { -16.0f, 180.0f, 0.0f }, { 34.0f, 9.0f, -14.0f } };
/* 0xC8C */ static float mb4ev_Sango2ScaleTbl[2] = { 1.0f, 0.7f };
/* 0xC94 */ static HuVecF mb4ev_Sango3PosTbl[4] = { { -2614.0f, -71.0f, 1954.0f }, { -3877.0f, -56.0f, 1192.0f }, { -2702.0f, 1002.0f, -1719.0f }, { -1320.0f, 692.0f, -1024.0f } };
/* 0xCC4 */ static HuVecF mb4ev_Sango3RotTbl[4] = { { 56.0f, -7.0f, -14.0f }, { 59.0f, -47.0f, 12.0f }, { 0.0f, 0.0f, 0.0f }, { 87.0f, 0.0f, -158.0f } };
/* 0xCF4 */ static HuVecF mb4ev_Sango3ScaleTbl[4] = { { 1.2f, 1.2f, 1.2f }, { 1.22f, 1.34f, 1.22f }, { 1.3f, 1.3f, 1.3f }, { 1.15f, 1.15f, 1.15f } };
/* 0xD24 */ static HuVecF mb4ev_Sango4PosTbl[2] = { { -2660.0f, 83.0f, 1906.0f }, { -2600.0f, 985.0f, -1485.0f } };
/* 0xD3C */ static HuVecF mb4ev_Sango4RotTbl[2] = { { 31.0f, -12.0f, -8.0f }, { 9.0f, 23.0f, 0.0f } };
/* 0xD54 */ static float mb4ev_Sango4ScaleTbl[2] = { 1.0f, 1.35f };
/* 0xD5C */ static HuVecF mb4ev_Sango5PosTbl[2] = { { -1407.0f, 828.0f, -1003.0f }, { -2140.0f, 1146.0f, -1255.0f } };
/* 0xD74 */ static HuVecF mb4ev_Sango5RotTbl[2] = { { 50.0f, -7.0f, 0.0f }, { -76.0f, 246.0f, 67.0f } };
/* 0xD8C */ static float mb4ev_Sango5ScaleTbl[2] = { 1.23f, 1.37f };
/* 0xD94 */ static HuVecF mb4ev_LeftSango5PosTbl[2] = { { -3823.0f, 985.0f, -1068.0f }, { -2380.0f, -109.0f, 2013.0f } };
/* 0xDAC */ static HuVecF mb4ev_LeftSango5RotTbl[2] = { { 16.0f, -6.0f, 0.0f }, { 42.0f, 9.0f, -2.0f } };
/* 0xDC4 */ static float mb4ev_LeftSango5ScaleTbl[2] = { 1.17f, 1.51f };
/* 0xDCC */ static HuVecF mb4ev_Hitode1PosTbl[3] = { { -1452.0f, -201.0f, 2038.0f }, { -2525.0f, 287.0f, 356.0f }, { -2327.0f, 298.0f, 252.0f } };
/* 0xDF0 */ static HuVecF mb4ev_Hitode1RotTbl[3] = { { 0.0f, 0.0f, 0.0f }, { 90.0f, 24.0f, 0.0f }, { 90.0f, 31.0f, 0.0f } };
/* 0xE14 */ static float mb4ev_Hitode1ScaleTbl[3] = { 1.0f, 0.57f, 0.34f };
/* 0xE20 */ static HuVecF mb4ev_Hitode2PosTbl[3] = { { -3313.0f, 1497.0f, -929.0f }, { -3429.0f, 1445.0f, -950.0f }, { -3188.0f, 1445.0f, -906.0f } };
/* 0xE44 */ static HuVecF mb4ev_Hitode2RotTbl[3] = { { 90.0f, -10.0f, 0.0f }, { 85.0f, -9.0f, 29.0f }, { 85.0f, 9.0f, 151.0f } };
/* 0xE68 */ static float mb4ev_Hitode2ScaleTbl[3] = { 1.0f, 0.65f, 0.65f };
/* 0xE74 */ static HuVecF mb4ev_KaisooPosTbl[2] = { { -1570.0f, 455.0f, 57.0f }, { -1075.0f, 1089.0f, -1404.0f } };
/* 0xE8C */ static HuVecF mb4ev_KaisooRotTbl[2] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } };
/* 0xEA4 */ static float mb4ev_KaisooScaleTbl[2] = { 1.0f, 1.0f };
/* 0xEAC */ static HuVecF openingRot = { -33.0f, 0.0f, 0.0f };
/* 0xEB8 */ static HuVecF openingOfs = { -2172.0f, 240.0f, 1423.0f };
/* 0xEC4 */ static float openingZoom = 7314.0f;
/* 0xEC8 */ static HuVecF mapViewRot = { -78.0f, 20.0f, 0.0f };
/* 0xED4 */ static HuVecF mapViewPos = { -2189.0f, 95.0f, 812.0f };
/* 0xEE0 */ static float mapViewZoom = 7511.0f;

/* 1420 insns */
void MB4_Create(void)
{
    int boardNo;
    int motTbl[16];
    MB4_BUBBLEEMIT *emit;
    int hu3dId;
    int mdlId;
    int i;

    boardNo = MBBoardNoGet();
    HuAudSndGrpSetSet(MSM_GRP_BD4);
    MBMasuCreate(DATANUM(DATA_w04s, 0x00));

    mb4_Work.mapMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x01), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.mdlId004 = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x13), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.kihonMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x10), NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.mdlId014 = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x14), NULL, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.pukuMdlId[0] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x15), NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.pukuMdlId[1] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x16), NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.irukaEvMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x17), NULL, FALSE);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);

    for(i=0; i<1; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x07), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_RBokPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_RBokRotYTbl[i], 0);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x18), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_YaziPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb4ev_YaziRotTbl[i], 0);
    }
    for(i=0; i<1; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x18), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_YaziExtPosTbl[i]);
        MBModelRotSet(mdlId, 0, 180+mb4ev_YaziExtRotTbl[i], 0);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x04), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_HasigoPosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_HasigoRotTbl[i]);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x1E), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango1PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango1RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango1ScaleTbl[i], mb4ev_Sango1ScaleTbl[i], mb4ev_Sango1ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x1F), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango2PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango2RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango2ScaleTbl[i], mb4ev_Sango2ScaleTbl[i], mb4ev_Sango2ScaleTbl[i]);
        if(i != 0) {
            MBModelLayerSet(mdlId, 1);
        }
    }
    for(i=0; i<4; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x20), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango3PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango3RotTbl[i]);
        MBModelScaleSetV(mdlId, &mb4ev_Sango3ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x21), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango4PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango4RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango4ScaleTbl[i], mb4ev_Sango4ScaleTbl[i], mb4ev_Sango4ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x22), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Sango5PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Sango5RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Sango5ScaleTbl[i], mb4ev_Sango5ScaleTbl[i], mb4ev_Sango5ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x22), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_LeftSango5PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_LeftSango5RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_LeftSango5ScaleTbl[i], mb4ev_LeftSango5ScaleTbl[i], mb4ev_LeftSango5ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x23), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Hitode1PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Hitode1RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Hitode1ScaleTbl[i], mb4ev_Hitode1ScaleTbl[i], mb4ev_Hitode1ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<3; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x24), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_Hitode2PosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_Hitode2RotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_Hitode2ScaleTbl[i], mb4ev_Hitode2ScaleTbl[i], mb4ev_Hitode2ScaleTbl[i]);
        MBModelLayerSet(mdlId, 1);
    }
    for(i=0; i<2; i++) {
        mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x25), NULL, TRUE);
        MBModelPosSetV(mdlId, &mb4ev_KaisooPosTbl[i]);
        MBModelRotSetV(mdlId, &mb4ev_KaisooRotTbl[i]);
        MBModelScaleSet(mdlId, mb4ev_KaisooScaleTbl[i], mb4ev_KaisooScaleTbl[i], mb4ev_KaisooScaleTbl[i]);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelLayerSet(mdlId, 1);
    }

    mb4_Work.kaiMdlId[0] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x09), NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[0]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaiMdlId[1] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0A), NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[1]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaiMdlId[2] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0B), NULL, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_KaiPosTbl[2]);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    mb4_Work.kaisooMdlId[0] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0C), NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.kaisooMdlId[1] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0D), NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.kaisooMdlId[2] = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0E), NULL, FALSE);
    MBModelDispSet(mdlId, FALSE);
    mb4_Work.mdlId03C = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x12), NULL, FALSE);
    MBModelLayerSet(mdlId, 1);

    motTbl[0] = DATANUM(DATA_w04s, 0x28);
    motTbl[1] = DATANUM(DATA_w04s, 0x29);
    motTbl[2] = -1;
    mb4_Work.puku2MdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x27), motTbl, FALSE);
    MBModelPosSetV(mdlId, &mb4ev_Puku2Pos);
    MBModelRotSet(mdlId, 0, -45, 0);
    MBModelScaleSet(mdlId, 2, 2, 2);
    MBMotionNoSet(mdlId, 1, HU3D_MOTATTR_LOOP);

    motTbl[0] = DATANUM(DATA_w04s, 0x2B);
    motTbl[1] = DATANUM(DATA_w04s, 0x2C);
    motTbl[2] = DATANUM(DATA_w04s, 0x2D);
    motTbl[3] = -1;
    mb4_Work.kihonSippMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x2A), motTbl, FALSE);
    MBMotionNoSet(mdlId, 1, HU3D_MOTATTR_LOOP);
    hu3dId = MBModelIdGet(mdlId);
    Hu3DModelClusterAttrSet(hu3dId, 0, HU3D_CLUSTER_ATTR_LOOP);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mdlId, FALSE);

    motTbl[0] = DATANUM(DATA_w04s, 0x2F);
    motTbl[1] = -1;
    mb4_Work.irukaMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x2E), motTbl, FALSE);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mdlId, FALSE);

    mb4_Work.blowMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x0F), motTbl, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBModelLayerSet(mdlId, 2);
    mb4_Work.kihonChrMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x26), motTbl, FALSE);
    MBModelDispSet(mdlId, FALSE);
    MBModelLayerSet(mdlId, 1);
    MB4_ModelStub(&Hu3DData[MBModelIdGet(mdlId)]);
    mb4_Work.coinLinkMdlId = mdlId = MBModelCreate(DATANUM(DATA_w04s, 0x11), motTbl, FALSE);
    MBModelDispSet(mdlId, FALSE);
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
    mb4_Work.capsuleFlag = 0;
    mb4_Work.capsuleEndF = 0;
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
    MBScrollInit(DATANUM(DATA_w04s, 0x30), 20000, 0);
    MBLightHookSet(MB4_LightSet, MB4_LightReset);
    MBCapsuleColCreate(DATANUM(DATA_w04s, 0x31));
    MBBranchFlagSet(0);
    MBMasuPathCheckHookSet(MB4_MasuPathCheck);
    HuDataDirClose(DATA_w04s);
    MBMasuWalkPreHookSet(MB4Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB4Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB4Ev_MasuHatena);
    mb4_MainObj = MBAddObj(32768, 0, 0, MB4_MainObjUpdate);
    MBOpeningViewSet(&openingRot, &openingOfs, openingZoom);
    MBMapViewCameraSet(&mapViewRot, &mapViewPos, mapViewZoom);
}

/* 21 insns */
void MB4_Kill(void)
{
    if(mb4_MainObj != NULL) {
        mb4_MainObj = NULL;
    }
    MB4_CoinClose();
    MB4_CoinEffClose();
    MB4_BubbleEffClose();
    MB4_SakanaClose();
}

/* 0xEE4 */ static HuVecF lbl_1_data_EE4[4] = { { -9.0f, 30.000002f, 65.0f }, { 9.0f, 30.000002f, 65.0f }, { -9.0f, 30.000002f, 65.0f }, { 9.0f, 30.000002f, 65.0f } };
/* 0xF14 */ static HuVecF mb4ev_BubbleEmitPosTbl[13] = { { 3710.0f, 240.0f, 790.0f }, { 2870.0f, 740.0f, -160.0f }, { 1620.0f, 700.0f, -930.0f }, { 2500.0f, 160.0f, 900.0f }, { 3170.0f, 300.0f, 1170.0f }, { 1940.0f, 120.0f, 550.0f }, { 2860.0f, 330.0f, 760.0f }, { 1120.0f, 320.0f, 60.0f }, { -1470.0f, 680.0f, -900.0f }, { -2700.0f, 100.0f, 2000.0f }, { -2780.0f, 660.0f, 1200.0f }, { -3950.0f, 190.0f, 780.0f }, { -2000.0f, 370.0f, 260.0f } };
/* 0xFB0 */ static HuVecF mb4ev_Puku2BubblePos = { -2800.0f, 300.0f, 1340.0f };
/* 0xFBC */ static HuVecF mb4ev_IrukaStartBubblePos = { -3320.0f, 1250.0f, -840.0f };

/* 666 insns */
void MB4_MainObjUpdate(OMOBJ *obj)
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

/* 70 insns */
void MB4_LightSet(void)
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

/* 1 insns */
void MB4_LightReset(void)
{
}

/* 30 insns */
int MB4Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    if(masu->flag & MB4EV_MASU_IRUKA) {
        MB4Ev_Iruka(playerNo);
    }
}

/* 2 insns */
int MB4_MasuStub(void)
{
    return 0;
}

/* 2 insns */
int MB4Ev_MasuWalkPre(int playerNo)
{
    return 0;
}

/* 0xFC8 */ static HuVecF mb4ev_Puku2EmiterPos = { -2800.0f, 300.0f, 1340.0f };

/* 94 insns */
int MB4Ev_MasuWalkPost(int playerNo)
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

/* 0xFD4 */ static s32 mb4ev_IrukaRotYPathNo[2] = { 0xB, 0xC };
/* 0xFDC */ static s32 mb4ev_IrukaRotXPathNo[2] = { 0x13, 0x10 };

/* 1205 insns */
void MB4Ev_Iruka(int playerNo)
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
    int cnt;
    HuVecF *path;
    int pathNo;
    int pathNum;
    int seNo;
    int nextMasuId;
    int prevIdx;
    int nextIdx;
    int nextIdx2;
    int state;
    int revF;
    int i;
    int j;
    int k;
    float t;
    float u;
    float diff;
    float time;
    double absDiff;
    int maxTime;
    int idx;
    u32 findFlag;
    MASU *masu;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerPosGet(playerNo, &destPos);
    playerPos = destPos;
    if(MBMasuFlagGet(MASU_LAYER_DEFAULT, masuId) & MASU_FLAG_BIT(0)) {
        path = mb4ev_Iruka1Path;
        pathNum = 100;
        findFlag = MASU_FLAG_BIT(1);
        pathNo = 0;
    } else {
        path = mb4ev_Iruka2Path;
        pathNum = 100;
        findFlag = MASU_FLAG_BIT(3);
        pathNo = 1;
    }
    motId[0] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_376);
    motId[1] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_435);
    motId[2] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_354);
    for(i=1; i<=MBMasuNumGet(MASU_LAYER_DEFAULT); i++) {
        if(MBMasuFlagGet(MASU_LAYER_DEFAULT, i) & findFlag) {
            break;
        }
    }
    if(i > MBMasuNumGet(MASU_LAYER_DEFAULT)) {
        i = masuId;
    }
    nextMasuId = i;
    MBMasuPosGet(MASU_LAYER_DEFAULT, nextMasuId, &masuPos);
    MBModelAttrReset(mb4_Work.irukaMdlId, HU3D_MOTATTR_PAUSE);
    MBModelPosSetV(mb4_Work.irukaMdlId, path);
    MBMotionNoSet(mb4_Work.irukaMdlId, 1, HU3D_MOTATTR_LOOP);
    MBModelDispSet(mb4_Work.irukaMdlId, TRUE);
    MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, NULL, 2000, -1, 63);
    MBCameraMotionWait();
    PSVECSubtract(&path[1], path, &vec);
    rot.x = (180.0*(atan2(sqrtf((vec.x*vec.x)+(vec.z*vec.z)), vec.y)/M_PI))-90.0;
    rot.y = 180.0*(atan2(vec.x, vec.z)/M_PI);
    rot.z = 0;
    rotTarget = rot;
    prevRot = rotTarget;
    revF = 0;
    state = 0;
    for(i=0; i<pathNum-1; i++) {
        p0 = path[i];
        p1 = path[i+1];
        prevIdx = i-1;
        idx = i;
        nextIdx = i+1;
        nextIdx2 = i+2;
        if(prevIdx < 0) {
            prevIdx = i;
        }
        if(nextIdx > (pathNum-1)) {
            nextIdx = pathNum-1;
        }
        if(nextIdx2 > (pathNum-1)) {
            nextIdx2 = pathNum-1;
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
        time = MB4_PathNextTimeGet(1, &path[prevIdx].x, &path[idx].x,
            &path[nextIdx].x, &path[nextIdx2].x);
        maxTime = time/30.000002f;
        for(j=1; j<=maxTime; j++) {
            t = (float)j/(float)maxTime;
            MB4_HermiteCalcV(t, &path[prevIdx].x, &path[idx].x,
                &path[nextIdx].x, &path[nextIdx2].x, &pos.x);
            rotTarget.x = fn_1_6E74(t, curRot.x, nextRot.x);
            rotTarget.y = fn_1_6E74(t, curRot.y, nextRot.y);
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
                    if(i >= mb4ev_IrukaRotYPathNo[pathNo]) {
                        HuAudFXPlay(MSM_SE_BD4_09);
                        MBPlayerMotionNoShiftSet(playerNo, motId[0], 0, 8, 0);
                        MBPlayerPosFixEvent(playerNo, nextMasuId, FALSE);
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
                        MBPlayerMotionNoShiftSet(playerNo, motId[1], 0, 8, HU3D_MOTATTR_LOOP);
                        MBPlayerPosSetV(playerNo, &ofsPos);
                        state++;
                        cnt = 0;
                    }
                    break;

                case 2:
                    MBPlayerPosSetV(playerNo, &ofsPos);
                    MBPlayerRotSetV(playerNo, &rot);
                    if(i >= pathNum-mb4ev_IrukaRotXPathNo[pathNo]) {
                        MBCameraModelViewSet(MBPlayerModelGet(playerNo), NULL, NULL, 2000, -1, 10);
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

                case 4:
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
    MBCameraMotionWait();
    MBPlayerPosSetV(playerNo, &masuPos);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    GwPlayer[playerNo].masuId = nextMasuId;
    HuPrcSleep(60);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 8, HU3D_MOTATTR_LOOP);
    MBModelAttrSet(mb4_Work.irukaMdlId, HU3D_MOTATTR_PAUSE);
    MBModelDispSet(mb4_Work.irukaMdlId, FALSE);
    HuPrcSleep(60);
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

/* 2 insns */
int MB4_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    return -1;
}

/* 139 insns */
void MB4_CoinDispUpdate(int playerNo, int coins, int threshold)
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

/* 0xFE4 */ static HuVecF mb4ev_IrukaBubbleOfsTbl[13] = { { 0.0f, -10.0f, 40.0f }, { 0.0f, -15.000001f, 35.0f }, { 0.0f, 20.0f, 10.0f }, { 0.0f, 50.0f, 30.000002f }, { 0.0f, 45.0f, 20.0f }, { 0.0f, 15.000001f, 10.0f }, { 0.0f, 30.000002f, 30.000002f }, { 0.0f, -10.0f, 25.0f }, { 0.0f, 0.0f, 50.0f }, { 0.0f, -20.0f, 65.0f }, { 0.0f, -20.0f, 65.0f }, { 0.0f, -20.0f, 65.0f }, { 0.0f, -20.0f, 65.0f } };
/* 0x1080 */ static float mb4ev_IrukaTPLvlScaleTbl[13] = { 1.1f, 1.0f, 0.8f, 1.1f, 1.2f, 0.7f, 0.9f, 0.8f, 0.7f, 1.2f, 1.1f, 1.1f, 1.3f };

/* 114 insns */
void MB4Ev_IrukaBubbleCreate(int playerNo, HuVecF *ofs)
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
        120*(1.0f+0.2f*MB4_RandF()));
}

/* 0x10C0 */ HuVecF lbl_1_data_10C0 = { 0.0f, 0.0f, 0.0f }; /* the twin's mb4ev_PlayerBubbleOfs */

/* 114 insns */
void MB4Ev_PlayerBubbleCreate(int playerNo)
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
    PSVECAdd(&pos, &lbl_1_data_10C0, &pos);
    MB4_BubbleEffCreate(&pos, mb4ev_IrukaTPLvlScaleTbl[charNo]*(0.3f+0.7f*MB4_RandF()),
        120*(1.0f+0.2f*MB4_RandF()));
}

void MB4_CapsuleEffHook(int capsuleNo, int type, int mdlId, BOOL flag1, BOOL flag2, BOOL flag3)
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
                    Hu3DModelObjMtxGet(MBModelIdGet(mdlId), "itemhook_C", mtx);
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
                        pos.x += 0.4f*(100.0*sin((M_PI*angle)/180.0));
                        pos.z += 0.4f*(100.0*cos((M_PI*angle)/180.0));
                        pos.y += 0.2f*(100*(MB4_RandF()-0.5f));
                        time = 120*(1+(MB4_RandF()*0.2f));
                        MB4_BubbleEffCreate(&pos, 0.75f*(0.8f+MB4_RandF()), time);
                    } else {
                        MBModelPosGet(mdlId, &pos);
                        angle = 360*MB4_RandF();
                        pos.x += 0.6f*(100.0*sin((M_PI*angle)/180.0));
                        pos.z += 0.6f*(100.0*cos((M_PI*angle)/180.0));
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

static HuVecF mb4ev_JangoBubbleOfs = { 0.0f, 350.0f, 350.0f };
static HuVecF mb4ev_HanachanBubbleOfs = { 0.0f, 10.0f, 30.000002f };
static HuVecF mb4ev_HammerBroBubbleOfs = { 0.0f, 0.0f, 30.000002f };
static HuVecF mb4ev_PatapataBubbleOfs = { 0.0f, 20.0f, 40.0f };
static HuVecF mb4ev_KuriboBubbleOfs = { 0.0f, 20.0f, 40.0f };
static HuVecF mb4ev_BankBubbleOfs = { 0.0f, 20.0f, 40.0f };
static HuVecF mb4ev_KamekkuBubbleOfs = { 0.0f, 20.0f, 50.0f };
static HuVecF mb4ev_KokamekkuBubbleOfs = { 0.0f, 10.0f, 60.000004f };
static HuVecF mb4ev_UkkiBubbleOfs = { 0.0f, 20.0f, 50.0f };
static HuVecF mb4ev_JugemBubbleOfs = { 0.0f, 20.0f, 50.0f };
static HuVecF mb4ev_DuelBubbleOfs = { 0.0f, 10.0f, 50.0f };
static HuVecF mb4ev_DonkeyBubbleOfs = { 70.0f, 40.0f, 0.0f };
static HuVecF mb4ev_KoopaBubbleOfsTbl[2][2] = { { { -9.0f, 30.000002f, 65.0f }, { 9.0f, 30.000002f, 65.0f } }, { { -9.0f, 30.000002f, 65.0f }, { 9.0f, 30.000002f, 65.0f } } };

void MB4_CapsuleBubbleUpdate(void)
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
        if(emit->num > 0) {
            emit->time++;
            if(--emit->wait <= 0 && (emit->time & 3) == 0) {
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
#ifdef __MWERKS__
#endif

float MB4_AngleDiff(float angle1, float angle2)
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

float MB4_AngleLerp(float target, float angle, float speed)
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

float fn_1_6E74(float rate, float angle, float target)
{
    float diff;

    diff = MB4_AngleDiff(target, angle);
    return MB4_AngleLerp(target, angle, fabs(diff*rate));
}

void MB4_ModelMtxSet(s16 mdlId, Mtx mtx)
{
    HU3DMODEL *modelP;
    int modelId;

    modelId = MBModelIdGet(mdlId);
    modelP = &Hu3DData[modelId];
    MTXCopy(mtx, modelP->mtx);
}

void MB4_PlayerMtxSet(s16 playerNo, Mtx mtx)
{
    int modelId;
    HU3DMODEL *modelP;
    MBMODELID mdlId;

    mdlId = MBPlayerModelGet(playerNo);
    modelId = MBModelIdGet(mdlId);
    modelP = &Hu3DData[modelId];
    MTXCopy(mtx, modelP->mtx);
}

void MB4_ModelStub(HU3DMODEL *modelP)
{
}

float MB4_BezierCalc(float t, float p0, float p1, float p2)
{
    float u = 1.0-t;
    float value;

    value = (p2*(t*t))+((p0*(u*u))+(2.0*(p1*(u*t))));
    return value;
}

void MB4_BezierCalcV(float t, float *p0, float *p1, float *p2, float *out)
{
    int i;

    for(i=0; i<3; i++) {
        *out++ = MB4_BezierCalc(t, *p0++, *p1++, *p2++);
    }
}

void MB4_HermiteCalc(float t, float *h00, float *h10, float *h01, float *h11)
{
    float t2 = t*t;
    float t3 = t*t2;
    float h = (3.0*t2)-t3-t3;

    *h00 = 1.0-h;
    *h10 = h;
    *h01 = t+((t3-t2)-t2);
    *h11 = t3-t2;
}

float fn_1_7564(float t, float p0, float p1, float p2, float p3, float tension)
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

void MB4_HermiteCalcV(float t, float *p0, float *p1, float *p2, float *p3, float *out)
{
    float rate = 0.5f;

    out[0] = fn_1_7564(t, p0[0], p1[0], p2[0], p3[0], rate);
    out[1] = fn_1_7564(t, p0[1], p1[1], p2[1], p3[1], rate);
    out[2] = fn_1_7564(t, p0[2], p1[2], p2[2], p3[2], rate);
}

float MB4_HermiteSlopeCalc(float t, float p0, float p1, float m0, float m1)
{
    float t2 = t*t;
    float h0 = (6*t2)-(6*t);
    float h1 = (-6*t2)-(6*t);
    float h2 = 1+((3*t2)-(4*t));
    float h3 = (3*t2)-(2*t);

    return (h3*m1)+((h2*m0)+((h0*p0)+(h1*p1)));
}

/* Kept before PathTimeGet: this wrapper must call, not inline, that body. */
float MB4_PathNextTimeGet(float t, float *p0, float *p1, float *p2, float *p3)
{
    /* The reference ignores t and always asks for the whole segment. */
    return MB4_PathTimeGet(1, p0, p1, p2, p3);
}

float fn_1_7CF4(float t, float p0, float p1, float p2, float p3)
{
    float m0 = 0.5f*((p2+(p1-p0))-p1);
    float m1 = 0.5f*((p2+(p1-p0))-p1);
    float a = m1+(m0+((2*p1)-(2*p2)));
    float b = (((-3*p1)+(3*p2))-(2*m0))-m1;
    float c = m0;

    return c+((t*((3*a)*t))+((2*b)*t));
}

/* The fourth control point is unused in the reference's speed calculation. */
float fn_1_7E28(float t, float *p0, float *p1, float *p2, float *p3)
{
    float x = fn_1_7CF4(t, p0[0], p1[0], p2[0], p3[0]);
    float y = fn_1_7CF4(t, p0[1], p1[1], p2[1], p3[1]);
    float z = fn_1_7CF4(t, p0[2], p1[2], p2[2], p3[2]);

    return sqrtf((x*x)+(y*y)+(z*z));
}

/* Simpson integration of the speed, with sixteen subintervals. */
float MB4_PathTimeGet(float t, float *p0, float *p1, float *p2, float *p3)
{
    float start = 0;
    float end = t;
    int num = 16;
    float step = (end-start)/num;
    float step2 = step+step;
    float sum = fn_1_7E28(start, p0, p1, p2, p3)+fn_1_7E28(end, p0, p1, p2, p3);
    float time;
    int i;

    for(i=1, time=start+step; i<num; i+=2, time+=step2) {
        sum += fn_1_7E28(time, p0, p1, p2, p3)*4;
    }
    for(i=2, time=start+step2; i<num; i+=2, time+=step2) {
        sum += fn_1_7E28(time, p0, p1, p2, p3)*2;
    }
    return (step/3)*sum;
}

/* 117 insns */
void MB4_CoinInit(void)
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

/* 651 insns */
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
                    MB4_CoinEffCreate(posP, velP, 100*(0.3f+(0.1f*MB4_RandF())), 0.016666668f*(1+(0.5f*MB4_RandF())), 0, colP);
                }
                break;
            }
        }
    }
}

/* 5 insns */
void MB4_CoinClose(void)
{
    mb4_CoinObj = NULL;
}

/* 35 insns */
int MB4_CoinNumGet(void)
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

/* 166 insns */
int MB4_CoinCreate(HuVecF *startPos, HuVecF *endPos, float speed, int duration)
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

/* 66 insns */
void MB4_CoinEffInit(void)
{
    OMOBJ *obj;
    MB4_COINEFFWORK *work;
    MBEFFECT *effP;
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

/* 118 insns */
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

/* 5 insns */
void MB4_CoinEffClose(void)
{
    mb4_CoinEffObj = NULL;
}

/* 20 insns */
int MB4_CoinEffNumGet(void)
{
    OMOBJ *obj = mb4_CoinEffObj;
    MB4_COINEFFWORK *work;

    if(mb4_CoinEffObj == NULL) {
        return 0;
    }
    work = omObjGetDataAs(obj, MB4_COINEFFWORK);
    return work->num;
}

/* 29 insns */
void MB4_CoinEffBlendModeSet(int blendMode)
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

/* 117 insns */
int MB4_CoinEffCreate(HuVecF *pos, HuVecF *vel, float scale, float decay, float gravity, GXColor *color)
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

/* 62 insns */
void MB4_BubbleEffInit(void)
{
    OMOBJ *obj;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;
    HU3DMODEL *modelP;
    ANIMDATA *anim;

    obj = MBAddObj(32768, 1, 0, MB4_BubbleEffUpdate);
    mb4_BubbleEffObj[0] = obj;
    anim = HuSprAnimRead(HuDataReadNum(W04S_ANM_bubbleEff, HU_MEMNUM_OVL));
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

/* 126 insns */
static void MB4_BubbleEffUpdate(OMOBJ *obj)
{
    MBEFFECTDATA *data;
    MBEFFECT *effP;
    int i;
    HU3DMODEL *modelP;

    modelP = &Hu3DData[obj->mdlId[0]];
    effP = modelP->hookData;
    data = effP->data;
    if(MBKillCheck() || mb4_BubbleEffObj[0] == NULL) {
        MBEffKill(obj->mdlId[0]);
        obj->mdlId[0] = HU3D_MODELID_NONE;
        obj->data = NULL;
        omDelObjEx(mbObjMan, obj);
        mb4_BubbleEffObj[0] = NULL;
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

/* 5 insns */
void MB4_BubbleEffClose(void)
{
    mb4_BubbleEffObj[0] = NULL;
}

/* 190 insns */
int MB4_BubbleEffCreate(HuVecF *pos, float scale, int time)
{
    MBEFFECTDATA *data;
    MBEFFECT *effP;
    int i;
    HU3DMODEL *modelP;

    if(mb4_BubbleEffObj[0] == NULL) {
        return -1;
    }
    modelP = &Hu3DData[mb4_BubbleEffObj[0]->mdlId[0]];
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

/* 747 insns */
void MB4_SakanaInit(void)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    MB4_SAKANA *sakana;
    ANIMDATA *anim;
    int i;
    int j;

    anim = HuSprAnimRead(HuDataReadNum(W04S_SPR_sakana, HU_MEMNUM_OVL));
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
                        sakana->mdlId = MBModelCreate(W04S_HSF_sakana0, NULL, TRUE);
                        break;
                    case 1:
                        sakana->mdlId = MBModelCreate(W04S_HSF_sakana1, NULL, TRUE);
                        break;
                    case 2:
                        sakana->mdlId = MBModelCreate(W04S_HSF_sakana2, NULL, TRUE);
                        break;
                    default:
                        sakana->mdlId = MBModelCreate(W04S_HSF_sakana3, NULL, TRUE);
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

/* 1473 insns */
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
                        if(mb4_BubbleEffObj[0] != NULL) {
                            bubbleModelP = &Hu3DData[mb4_BubbleEffObj[0]->mdlId[0]];
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

/* 35 insns */
void MB4_SakanaClose(void)
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

/* 45 insns */
void MB4_SakanaOffsetInit(void)
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

/* 47 insns */
void MB4_SakanaPosInit(void)
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

/* 72 insns */
int MB4_SakanaCreate(int type)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;
    int i;

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
    data->animBank = type;
    data->color.r = data->color.g = data->color.b = data->color.a = 255;
    return i;
}

/* 23 insns */
void MB4_SakanaPosSet(int no, float x, float y, float z)
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

/* 27 insns */
void MB4_SakanaOffsetSet(int no, float x, float y, float z)
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

/* 25 insns */
void MB4_SakanaLenSet(int no, float len)
{
    HU3DMODEL *modelP;
    MBEFFECT *effP;
    MBEFFECTDATA *data;

    modelP = &Hu3DData[mb4_Work.sakanaEffMdlId];
    effP = modelP->hookData;
    data = &effP->data[no];
    data->scale = 100*len;
}

