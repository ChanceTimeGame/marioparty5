/*
 * sd00dll gun.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/gun.s.
 */

#include "REL/sd00dll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "game/mg/seqman.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x870 lbl_1_rodata_870 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x87C lbl_1_rodata_87C (0x10): 0x01, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00 -- an aggregate initialiser, write it as a local */
/* 0x88C lbl_1_rodata_88C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x898 lbl_1_rodata_898 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8A4 lbl_1_rodata_8A4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8B0 lbl_1_rodata_8B0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8BC lbl_1_rodata_8BC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8C8 lbl_1_rodata_8C8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_8D4 = 0.0f; /* 0x8D4 */
static const float lbl_1_rodata_8D8 = 0.5f; /* 0x8D8 */
static const float lbl_1_rodata_8DC = 45.0f; /* 0x8DC */
static const float lbl_1_rodata_8E0 = 150.0f; /* 0x8E0 */
static const float lbl_1_rodata_8E4 = 22.5f; /* 0x8E4 */
static const double lbl_1_rodata_8E8 = 180.0; /* 0x8E8 */
static const double lbl_1_rodata_8F0 = 3.141592653589793; /* 0x8F0 */
static const float lbl_1_rodata_8F8 = 7.5f; /* 0x8F8 */
static const float lbl_1_rodata_8FC = -7.5f; /* 0x8FC */
static const float lbl_1_rodata_900 = 0.017453292f; /* 0x900 */
static const float lbl_1_rodata_904 = 5.0f; /* 0x904 */
static const float lbl_1_rodata_908 = 1.0f; /* 0x908 */
/* 0x910 lbl_1_rodata_910 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x918 lbl_1_rodata_918 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_924 = 0.15f; /* 0x924 */
/* 0x928 lbl_1_rodata_928 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x929 lbl_1_rodata_929 (0x3): 0x00, 0x20, 0x80 -- an aggregate initialiser, write it as a local */
/* 0x92C lbl_1_rodata_92C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x938 lbl_1_rodata_938 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x944 lbl_1_rodata_944 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x950 lbl_1_rodata_950 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_95C = 2.0f; /* 0x95C */
static const float lbl_1_rodata_960 = 0.75f; /* 0x960 */
/* 0x964 lbl_1_rodata_964 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x970 lbl_1_rodata_970 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x97C lbl_1_rodata_97C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x988 lbl_1_rodata_988 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x994 lbl_1_rodata_994 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_9A0 = -0.5f; /* 0x9A0 */
static const float lbl_1_rodata_9A4 = 60.0f; /* 0x9A4 */
/* 0x9A8 lbl_1_rodata_9A8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_9B4 = 0.34906584f; /* 0x9B4 */
static const float lbl_1_rodata_9B8 = 240.0f; /* 0x9B8 */
static const float lbl_1_rodata_9BC = 15.0f; /* 0x9BC */
/* 0x9C0 lbl_1_rodata_9C0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x9CC lbl_1_rodata_9CC (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x9D8 lbl_1_rodata_9D8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_9E4 = 0.8f; /* 0x9E4 */
static const float lbl_1_rodata_9E8 = 30.0f; /* 0x9E8 */
static const float lbl_1_rodata_9EC = 40.0f; /* 0x9EC */
static const float lbl_1_rodata_9F0 = 0.1f; /* 0x9F0 */
/* 0x9F4 lbl_1_rodata_9F4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA00 lbl_1_rodata_A00 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A0C = 2.5f; /* 0xA0C */
/* 0xA10 lbl_1_rodata_A10 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA1C lbl_1_rodata_A1C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA28 lbl_1_rodata_A28 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A34 = 50.0f; /* 0xA34 */
static const float lbl_1_rodata_A38 = 10.0f; /* 0xA38 */
static const float lbl_1_rodata_A3C = 20.0f; /* 0xA3C */
static const float lbl_1_rodata_A40 = 18.0f; /* 0xA40 */
static const float lbl_1_rodata_A44 = 184.0f; /* 0xA44 */
static const float lbl_1_rodata_A48 = 51.25f; /* 0xA48 */
static const float lbl_1_rodata_A4C = -0.15f; /* 0xA4C */
/* 0xA50 lbl_1_rodata_A50 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA5C lbl_1_rodata_A5C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA68 lbl_1_rodata_A68 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A74 = 25.0f; /* 0xA74 */
/* 0xA78 lbl_1_rodata_A78 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A84 = 80.0f; /* 0xA84 */
static const float lbl_1_rodata_A88 = 90.0f; /* 0xA88 */
static const float lbl_1_rodata_A8C = 100.0f; /* 0xA8C */
static const float lbl_1_rodata_A90 = 0.05f; /* 0xA90 */
/* 0xA94 lbl_1_rodata_A94 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xAA0 lbl_1_rodata_AA0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAAC lbl_1_rodata_AAC (0x1): 0xDA -- an aggregate initialiser, write it as a local */
/* 0xAAD lbl_1_rodata_AAD (0x3): 0xCB, 0x9E, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xAB0 lbl_1_rodata_AB0 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xABC lbl_1_rodata_ABC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAC8 lbl_1_rodata_AC8 (0x1): 0xDA -- an aggregate initialiser, write it as a local */
/* 0xAC9 lbl_1_rodata_AC9 (0x3): 0xCB, 0x9E, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_ACC = 0.9f; /* 0xACC */
static const float lbl_1_rodata_AD0 = 1.04f; /* 0xAD0 */
/* 0xAD8 lbl_1_rodata_AD8 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0xAE0 lbl_1_rodata_AE0 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xAEC lbl_1_rodata_AEC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAF8 lbl_1_rodata_AF8 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xB04 lbl_1_rodata_B04 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB10 lbl_1_rodata_B10 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xB1C lbl_1_rodata_B1C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB28 lbl_1_rodata_B28 (0x1): 0xDA -- an aggregate initialiser, write it as a local */
/* 0xB29 lbl_1_rodata_B29 (0x3): 0xCB, 0x9E, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B2C = 300.0f; /* 0xB2C */
/* 0xB30 lbl_1_rodata_B30 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xB3C lbl_1_rodata_B3C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB48 lbl_1_rodata_B48 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB54 lbl_1_rodata_B54 (0x1): 0xDA -- an aggregate initialiser, write it as a local */
/* 0xB55 lbl_1_rodata_B55 (0x3): 0xCB, 0x9E, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B58 = 75.0f; /* 0xB58 */
/* 0xB5C lbl_1_rodata_B5C (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xB68 lbl_1_rodata_B68 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB74 lbl_1_rodata_B74 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB80 lbl_1_rodata_B80 (0x1): 0xDA -- an aggregate initialiser, write it as a local */
/* 0xB81 lbl_1_rodata_B81 (0x3): 0xCB, 0x9E, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xB84 lbl_1_rodata_B84 (0xC): 0x00000000 0x3F000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xB90 lbl_1_rodata_B90 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB9C lbl_1_rodata_B9C (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBA8 lbl_1_rodata_BA8 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0xBA9 lbl_1_rodata_BA9 (0x3): 0x00, 0x00, 0xB4 -- an aggregate initialiser, write it as a local */
/* 0xBAC lbl_1_rodata_BAC (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBB8 lbl_1_rodata_BB8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBC4 lbl_1_rodata_BC4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBD0 lbl_1_rodata_BD0 (0xC): 0x00000000 0xBF800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBDC lbl_1_rodata_BDC (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0xBDD lbl_1_rodata_BDD (0x3): 0x00, 0x00, 0xB4 -- an aggregate initialiser, write it as a local */
/* 0xBE0 lbl_1_rodata_BE0 (0xC): 0x00000000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xBEC lbl_1_rodata_BEC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBF8 lbl_1_rodata_BF8 (0xC): 0x00000000 0xBFC00000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC04 lbl_1_rodata_C04 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0xC05 lbl_1_rodata_C05 (0x3): 0x00, 0x00, 0xB4 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_C08 = 0.98f; /* 0xC08 */
static const float lbl_1_rodata_C0C = 1.08f; /* 0xC0C */
static const float lbl_1_rodata_C10 = 1.1f; /* 0xC10 */
/* 0xC14 lbl_1_rodata_C14 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xC20 lbl_1_rodata_C20 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xC2C lbl_1_rodata_C2C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC38 lbl_1_rodata_C38 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC39 lbl_1_rodata_C39 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_C3C = 0.95f; /* 0xC3C */
static const float lbl_1_rodata_C40 = 1.02f; /* 0xC40 */
static const float lbl_1_rodata_C44 = 200.0f; /* 0xC44 */
static const float lbl_1_rodata_C48 = 0.995f; /* 0xC48 */
static const float lbl_1_rodata_C4C = 0.92f; /* 0xC4C */
/* 0xC50 lbl_1_rodata_C50 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xC5C lbl_1_rodata_C5C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC68 lbl_1_rodata_C68 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC69 lbl_1_rodata_C69 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC6C lbl_1_rodata_C6C (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xC78 lbl_1_rodata_C78 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC84 lbl_1_rodata_C84 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC85 lbl_1_rodata_C85 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC88 lbl_1_rodata_C88 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC89 lbl_1_rodata_C89 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xC8C lbl_1_rodata_C8C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC98 lbl_1_rodata_C98 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xCA4 lbl_1_rodata_CA4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_CB0 = -80.0f; /* 0xCB0 */
/* 0xCB4 lbl_1_rodata_CB4 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0xCB5 lbl_1_rodata_CB5 (0x3): 0xFF, 0xFF, 0xB4 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_CB8 = 0.85f; /* 0xCB8 */
/* 0xCBC lbl_1_rodata_CBC (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xCC8 lbl_1_rodata_CC8 (0xC): 0x00000000 0x3F800000 0xBE800000 -- an aggregate initialiser, write it as a local */
/* 0xCD4 lbl_1_rodata_CD4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xCE0 lbl_1_rodata_CE0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xCEC lbl_1_rodata_CEC (0xC): 0x00000000 0x40A00000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xCF8 lbl_1_rodata_CF8 (0xC): 0x00000000 0x3FC00000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD04 lbl_1_rodata_D04 (0xC): 0x00000000 0x3F800000 0x3FC00000 -- an aggregate initialiser, write it as a local */
/* 0xD10 lbl_1_rodata_D10 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD1C lbl_1_rodata_D1C (0xC): 0x00000000 0x3E19999A 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD28 lbl_1_rodata_D28 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD34 lbl_1_rodata_D34 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD40 lbl_1_rodata_D40 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD4C lbl_1_rodata_D4C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_D58 = 360.0f; /* 0xD58 */
static const float lbl_1_rodata_D5C = 0.03125f; /* 0xD5C */
static const float lbl_1_rodata_D60 = 0.0625f; /* 0xD60 */
static const float lbl_1_rodata_D64 = 120.0f; /* 0xD64 */
static const float lbl_1_rodata_D68 = 72.0f; /* 0xD68 */
static const float lbl_1_rodata_D6C = 51.5f; /* 0xD6C */
static const float lbl_1_rodata_D70 = -15.0f; /* 0xD70 */
static const float lbl_1_rodata_D74 = -12.0f; /* 0xD74 */
static const float lbl_1_rodata_D78 = 320.0f; /* 0xD78 */
static const float lbl_1_rodata_D7C = 1.05f; /* 0xD7C */
/* 0xD80 lbl_1_rodata_D80 (0xC): 0 0 0 -- an aggregate initialiser, write it as a local */
/* 0xD8C gap_03_00000D8C_rodata: 0x00000000 */

static void BulletKinokoUpdate(SDBULLET *bullet);
static void BulletSuikaUpdate(SDBULLET *bullet);
static void BulletBombUpdate(SDBULLET *bullet);
static void BulletKillerUpdate(SDBULLET *bullet);
static void BulletSanboUpdate(SDBULLET *bullet);
static void BulletPakkunUpdate(SDBULLET *bullet);
static void BulletKoopaFireUpdate(SDBULLET *bullet);
static void BulletAikunUpdate(SDBULLET *bullet);
static void BulletBananaUpdate(SDBULLET *bullet);
static void BulletLaserUpdate(SDBULLET *bullet);
static void BulletHaruUpdate(SDBULLET *bullet);
static void BulletKoopaArmUpdate(SDBULLET *bullet);
static void BulletBombSmallUpdate(SDBULLET *bullet);
static s32 BulletMachineCol(SDBULLET *bullet);
static s32 BulletParticleCol(SDBULLET *bullet, s32 effectNo, s32 a2);
static s32 BulletObjHitCheck(SDBULLET *bullet);
static s32 BulletParticleObjHitCheck(SDBULLET *bullet, s32 effectNo);
static void BulletParticleObjHitCreate(SDBULLET *bullet, s32 effectNo);
static s32 BulletRabbitHitCheck(SDBULLET *bullet);
static s32 BulletParticleRabbitHitCheck(SDBULLET *bullet, s32 effectNo);
static void BulletLaserCheck(SDBULLET *bullet);
static void BulletEffectUpdate(SDBULLET *bullet);
static void BulletEffectCreate(SDBULLET *bullet, Mtx mtx);
static void BulletAirEffectCreate(SDBULLET *bullet, Mtx mtx);
static void BulletImpactCreate(SDBULLET *bullet, Mtx mtx);
static void KinokoEffectUpdate(SDBULLET *bullet);
static void ShootEffectCreate(SDBULLET *bullet, Mtx mtx);
static void DustCloudImpactCreate(SDBULLET *bullet, Mtx mtx);
static void KinokoEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void SuikaEffectUpdate(SDBULLET *bullet);
static void SuikaEffectCreate(SDBULLET *bullet, Mtx mtx);
static void SuikaImpactCreate(SDBULLET *bullet, Mtx mtx);
static void SuikaEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void FlameEffectUpdate(SDBULLET *bullet);
static void FlameEffectUpdateData(SDBULLET *bullet);
static void BomheiAirEffectUpdate(SDBULLET *bullet, Mtx mtx);
static void BulletDustImpactCreate(SDBULLET *bullet, Mtx mtx);
static void KillerEffectUpdate(SDBULLET *bullet);
static void SanboEffectCreate(SDBULLET *bullet, Mtx mtx);
static void SanboImpactCreate(SDBULLET *bullet, Mtx mtx);
static void PakkunEffectUpdate(SDBULLET *bullet);
static void PakkunEffectCreate(SDBULLET *bullet, Mtx mtx);
static void PakkunAirEffectUpdate(SDBULLET *bullet, Mtx mtx);
static void PakkunImpactCreate(SDBULLET *bullet, Mtx mtx);
static void PakkunEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void PakkunEffectData2Update(HU3DPARTICLEDATA *data, s32 num);
static void BulletExplodeUpdate(SDBULLET *bullet);
static void KoopaFireEffectCreate(SDBULLET *bullet, Mtx mtx);
static void KoopaFireEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void AikunEffectUpdate(SDBULLET *bullet);
static void AikunEffectCreate(SDBULLET *bullet, Mtx mtx);
static void AikunImpactCreate(SDBULLET *bullet, Mtx mtx);
static void AikunEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void LaserAirEffectUpdate(SDBULLET *bullet, Mtx mtx);
static void LaserEffectUpdate(SDBULLET *bullet);
static void LaserEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);
static void KoopaArmEffectUpdate(SDBULLET *bullet);
static void StarEffectUpdate(SDBULLET *bullet);
static void KoopaArmImpactCreate(SDBULLET *bullet, Mtx mtx);
static void StarEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num);

/* --- functions (reference order), .data placed before its first user --- */
/* 593 insns */
void SdGunUpdate(SDMACHINE *machine)
{
    Mtx mtx;
    HuVecF dir;
    HuVecF dir2;
    HuVecF fwd;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF target;
    SDMACHINE *enemy = machine->enemy;
    s8 holdTbl[13] = { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1 };
    float angle1;
    float angle2;
    float dist;
    float distRabbit;
    float distEnemy;
    float dotRabbit;
    float dotEnemy;
    SDBULLET *bullet;
    SDGUN *gun;
    s32 flag;
    s32 j;
    s32 i;
    s32 played;

    played = 0;
    if(holdTbl[machine->gunNo] == 0) {
        if(!(HuPadBtn[machine->unk348] & PAD_BUTTON_B)) {
            return;
        }
    } else if(!(HuPadBtnDown[machine->unk348] & PAD_BUTTON_B)) {
        return;
    }
    for(i = 0; i < machine->gunNum; i++) {
        gun = &machine->gun[i];
        if(gun->unk0 > 0) {
            continue;
        }
        for(j = 0; j < machine->bulletNum; j++) {
            if(gun->bullet[j].mode != 0) {
                continue;
            }
            bullet = &gun->bullet[j];
            bullet->mode = 1;
            bullet->unk4 = bullet->time = bullet->unk18 = 0;
            bullet->unk11C.y = 0.0f;
            bullet->unk64 = bullet->param->unk14;
            PSMTXTrans(mtx, machine->pos.x, machine->pos.y, machine->pos.z);
            PSMTXConcat(mtx, machine->mtx, mtx);
            PSMTXConcat(mtx, gun->mtx, bullet->mtx);
            bullet->unk104 = bullet->unkD8 = bullet->pos = (HuVecF){ bullet->mtx[0][3], bullet->mtx[1][3], bullet->mtx[2][3] };
            if(sys->gameType != 2) {
                target = enemy->pos;
                target.y += enemy->unk35C / 2.0f;
            } else {
                flag = 0;
                target = SdRabbitPosGet();
                PSVECSubtract(&target, &machine->pos, &dir);
                PSVECSubtract(&enemy->pos, &machine->pos, &dir2);
                dir.y = dir2.y = 0.0f;
                distRabbit = PSVECMag(&dir);
                distEnemy = PSVECMag(&dir2);
                if(SdRabbitDoneCheck()) {
                    flag = 1;
                }
                if(!SdRabbitCheck()) {
                    flag = 1;
                } else if(enemy->mode >= 2 || enemy->unk210 != 0) {
                    flag = 0;
                } else if(distRabbit < 0.5f || distEnemy < 0.5f) {
                    flag = 1;
                } else {
                    fwd = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
                    PSVECNormalize(&dir, &dir);
                    dotRabbit = PSVECDotProduct(&dir, &fwd);
                    PSVECNormalize(&dir2, &dir2);
                    dotEnemy = PSVECDotProduct(&dir2, &fwd);
                    if(dotRabbit < dotEnemy) {
                        flag = 1;
                    }
                }
                if(flag == 0) {
                    target = SdRabbitPosGet();
                    target.y += 45.0f;
                } else {
                    target = enemy->pos;
                    target.y += enemy->unk35C / 2.0f;
                }
            }
            PSVECSubtract(&target, &bullet->unk104, &dir);
            if(bullet->param->unk0 == 2) {
                PSVECNormalize(&dir, &dir);
                PSVECScale(&dir, &dir, 150.0f);
                bullet->unk11C.z = 22.5f;
            }
            dist = PSVECMag(&dir);
            if(dist < bullet->param->unk20) {
                dir2 = (HuVecF){ dir.x, 0.0f, dir.z };
                PSVECNormalize(&dir2, &dir2);
                PSVECScale(&dir2, &dir2, bullet->param->unk20);
                dir = (HuVecF){ dir2.x, dir.y, dir2.z };
            } else if(0.0f == bullet->param->unk1C && dist > bullet->param->unkC) {
                dir2 = (HuVecF){ dir.x, 0.0f, dir.z };
                PSVECNormalize(&dir2, &dir2);
                PSVECScale(&dir2, &dir2, bullet->param->unkC);
                dir = (HuVecF){ dir2.x, dir.y, dir2.z };
            }
            bullet->unk11C.x = PSVECMag(&dir);
            angle1 = 180.0 * (atan2(bullet->mtx[0][2], bullet->mtx[2][2]) / M_PI);
            PSVECNormalize(&dir, &dir);
            angle2 = 180.0 * (atan2(dir.x, dir.z) / M_PI);
            if(angle1 - angle2 < 7.5f && angle1 - angle2 > -7.5f) {
                PSMTXIdentity(mtx);
            } else {
                PSMTXRotRad(mtx, 'y', 0.017453292f * (angle1 - angle2));
            }
            PSMTXMultVec(mtx, &dir, &dir);
            MathPlaneRotMtxGet(&dir, NULL, 0.0f, bullet->mtx);
            MathMtxRotGet(bullet->mtx, &bullet->unkE4);
            PSVECScale(&dir, &dir, bullet->unk11C.x);
            PSVECAdd(&dir, &bullet->unk104, &bullet->unk110);
            if(machine->gunNo == 12) {
                bullet->unk110.y = bullet->unk104.y;
            }
            bullet->gun->unk34 = bullet;
            bullet->unkFC = 5.0f * bullet->param->unk8;
            if(bullet->mdlId[0] != -1 && machine->gunNo != 4 && machine->gunNo != 1) {
                Hu3DModelAttrReset(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            }
            if(bullet->mdlId[1] != -1) {
                Hu3DModelAttrReset(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            }
            gun->unk0 = machine->unk20C;
            if(played == 0) {
                SdMachineFxGunPlay(bullet);
                played = 1;
            }
            if(bullet->unk11C.x < 1.0f) {
                bullet->unk11C.x = 1.0f;
            }
            break;
        }
    }
}

/* 0x10D0 */ static SDBULLETFUNC bulletUpdateFuncTbl[13] = { BulletKinokoUpdate, BulletSuikaUpdate, BulletBombUpdate, BulletKillerUpdate, BulletSanboUpdate, BulletPakkunUpdate, BulletKoopaFireUpdate, BulletAikunUpdate, BulletBananaUpdate, BulletLaserUpdate, BulletHaruUpdate, BulletKoopaArmUpdate, BulletBombSmallUpdate };

/* 62 insns */
void SdBulletUpdate(SDMACHINE *machine)
{
    SDBULLET *bullet;
    SDGUN *gun;
    s32 i;
    s32 j;

    for(i = 0; i < machine->gunNum; i++) {
        gun = &machine->gun[i];
        if(gun->unk0 != 0) {
            gun->unk0--;
        }
        for(j = 0; j < machine->bulletNum; j++) {
            bullet = &gun->bullet[j];
            bulletUpdateFuncTbl[machine->gunNo](bullet);
            BulletEffectUpdate(bullet);
            if(bullet->mdlId[0] != -1) {
                Hu3DModelPosSetV(bullet->mdlId[0], &bullet->pos);
                Hu3DModelRotSetV(bullet->mdlId[0], &bullet->unkE4);
            }
            if(bullet->mdlId[1] != -1) {
                Hu3DModelPosSetV(bullet->mdlId[1], &bullet->pos);
            }
        }
    }
}

/* 190 insns */
static void BulletKinokoUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF dir;
    HuVecF up;
    s32 hit;

    switch(bullet->mode) {
        case 0:
            break;
        case 1:
            bullet->unkD8 = bullet->pos;
            bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
            bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 0.15f * bullet->unk11C.x, bullet->unk11C.y);
            PSVECSubtract(&bullet->pos, &bullet->unkD8, &dir);
            up = (HuVecF){ bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
            MathPlaneRotMtxGet(&dir, &up, 0.0f, mtx);
            if(bullet->time == 0) {
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                BulletEffectCreate(bullet, mtx);
                Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
                Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
                bullet->time = 1;
            }
            MathMtxRotGet(mtx, &bullet->unkE4);
            hit = 0;
            if(BulletMachineCol(bullet)) {
                hit = 1;
            } else if(MgSeqModeGet() > 5) {
                hit = 1;
            } else if(BulletRabbitHitCheck(bullet)) {
                hit = 1;
            } else if(SdStageWallCheck(&bullet->pos, &dir)) {
                hit = 2;
            } else if(BulletObjHitCheck(bullet)) {
                hit = 2;
            } else if(SdStageFloorCheck(&bullet->pos, &dir)) {
                hit = 2;
            }
            if(hit != 0) {
                SdMachineFxImpactPlay(bullet);
                if(hit == 2) {
                    MathPlaneRotMtxGet(&dir, NULL, 0.0f, mtx);
                }
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                BulletImpactCreate(bullet, mtx);
                Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
                if(bullet->mdlId[1] != -1) {
                    Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
                }
                bullet->mode = 0;
            }
            break;
    }
}

/* 238 insns */
static void BulletSuikaUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF dir;
    HuVecF up;
    HuVecF ofs;
    float dist;
    s32 hit;

    switch(bullet->mode) {
        case 0:
            break;
        case 1:
            bullet->gun->unk3C = (GXColor){ 0xFF, 0x00, 0x20, 0x80 };
            bullet->mode++;
        case 2:
            bullet->unkD8 = bullet->pos;
            bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
            bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 0.0f, bullet->unk11C.y);
            PSVECSubtract(&bullet->pos, &bullet->unkD8, &dir);
            up = (HuVecF){ bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
            MathPlaneRotMtxGet(&dir, &up, 0.0f, mtx);
            if(bullet->time == 0) {
                if(bullet->machine->gunNo != 4) {
                    Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
                    Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
                }
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                BulletEffectCreate(bullet, mtx);
                bullet->time = 1;
            }
            MathMtxRotGet(mtx, &bullet->unkE4);
            hit = 0;
            if(BulletMachineCol(bullet)) {
                hit = 1;
            } else if(MgSeqModeGet() > 5) {
                hit = 1;
            } else if(BulletRabbitHitCheck(bullet)) {
                hit = 1;
            } else if(SdStageWallCheck(&bullet->pos, &dir)) {
                hit = 2;
            } else if(BulletObjHitCheck(bullet)) {
                hit = 2;
            } else if(SdStageFloorCheck(&bullet->pos, &dir)) {
                hit = 2;
            } else {
                PSVECSubtract(&bullet->pos, &bullet->unk104, &ofs);
                dist = PSVECMag(&ofs);
                if(dist > bullet->param->unkC) {
                    hit = 1;
                }
            }
            if(hit != 0) {
                SdMachineFxImpactPlay(bullet);
                if(hit == 2) {
                    MathPlaneRotMtxGet(&dir, NULL, 0.0f, mtx);
                }
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                BulletImpactCreate(bullet, mtx);
                if(bullet->mdlId[0] != -1) {
                    Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
                }
                if(bullet->mdlId[1] != -1) {
                    Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
                }
                bullet->mode = 0;
            }
            break;
    }
}

/* 379 insns */
static void BulletBombUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF dir;
    HuVecF up;
    s32 hit;

    switch(bullet->mode) {
        case 0:
            break;
        case 1:
            BulletLaserCheck(bullet);
            bullet->unkD8 = bullet->pos;
            bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
            bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 2.0f * bullet->unk11C.z, bullet->unk11C.y);
            PSVECSubtract(&bullet->pos, &bullet->unkD8, &dir);
            up = (HuVecF){ bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
            MathPlaneRotMtxGet(&dir, &up, 0.0f, mtx);
            if(bullet->time == 0) {
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                BulletEffectCreate(bullet, mtx);
                Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_PAUSE);
                Hu3DMotionTimeSet(bullet->machine->gunMdl, 0.0f);
                bullet->time = 1;
            }
            MathMtxRotGet(mtx, &bullet->unkE4);
            hit = 0;
            dir = (HuVecF){ 0.0f, 1.0f, 0.0f };
            if(BulletMachineCol(bullet)) {
                hit = 1;
            } else if(MgSeqModeGet() > 5) {
                hit = 1;
            } else if(BulletRabbitHitCheck(bullet)) {
                hit = 1;
            } else if(SdStageWallCheck(&bullet->pos, NULL)) {
                hit = 2;
            } else if(BulletObjHitCheck(bullet)) {
                hit = 2;
            } else if(SdStageFloorCheck(&bullet->pos, &dir)) {
                hit = 3;
            }
            if(hit != 0) {
                if(hit != 3) {
                    SdMachineFxImpactPlay(bullet);
                } else {
                    SdImpactSoundStart(0x555, bullet->pos, 0.75f);
                }
                MathPlaneRotMtxGet(&dir, NULL, 0.0f, mtx);
                mtx[0][3] = bullet->pos.x;
                mtx[1][3] = bullet->pos.y;
                mtx[2][3] = bullet->pos.z;
                bullet->time = 0;
                if(hit < 3) {
                    BulletImpactCreate(bullet, mtx);
                    if(hit == 2) {
                        bullet->unk64 = bullet->param->unk18;
                        PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &dir);
                        MathPlaneRotMtxGet(&dir, NULL, 0.0f, bullet->mtx);
                        BulletMachineCol(bullet);
                        BulletRabbitHitCheck(bullet);
                        BulletObjHitCheck(bullet);
                    }
                    Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
                    if(bullet->mdlId[1] != -1) {
                        Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
                    }
                    bullet->mode = 0;
                } else {
                    Hu3DMotionSet(bullet->mdlId[0], bullet->mdlId[4]);
                    Hu3DModelAttrSet(bullet->mdlId[0], HU3D_MOTATTR_LOOP);
                    Hu3DMotionTimeSet(bullet->mdlId[0], 0.0f);
                    Hu3DModelAttrReset(bullet->mdlId[2], HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(bullet->mdlId[2], 0.0f);
                    BulletAirEffectCreate(bullet, mtx);
                    bullet->mode++;
                }
            }
            break;
        case 2:
            if(MgSeqModeGet() == 5 && ++bullet->time < bullet->param->unk10) {
                break;
            }
            dir = (HuVecF){ 0.0f, 1.0f, 0.0f };
            MathPlaneRotMtxGet(&dir, NULL, 0.0f, mtx);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletImpactCreate(bullet, mtx);
            bullet->unk64 = bullet->param->unk18;
            PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &dir);
            MathPlaneRotMtxGet(&dir, NULL, 0.0f, bullet->mtx);
            SdMachineFxImpactPlay(bullet);
            if(MgSeqModeGet() == 5) {
                BulletMachineCol(bullet);
                BulletRabbitHitCheck(bullet);
                BulletObjHitCheck(bullet);
            }
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(bullet->mdlId[2], HU3D_ATTR_DISPOFF);
            Hu3DMotionSet(bullet->mdlId[0], bullet->mdlId[3]);
            Hu3DMotionTimeSet(bullet->mdlId[0], 0.0f);
            SdModelGlowSet(bullet->mdlId[0]);
            bullet->time = bullet->mode = 0;
            break;
    }
}

/* 288 insns */
static void BulletKillerUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF vel;
    HuVecF dir;
    HuVecF up;
    HuVecF target;
    s32 hit;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        bullet->unkD8 = bullet->pos;
        dir = (HuVecF) { bullet->mtx[0][2], bullet->mtx[1][2], bullet->mtx[2][2] };
        PSVECScale(&dir, &vel, bullet->param->unk1C - 1.0f);
        if (bullet->machine->enemy->unk330 == 0) {
            target = bullet->machine->enemy->pos;
            target.y += bullet->machine->enemy->unk358;
        } else {
            PSVECAdd(&bullet->pos, &dir, &target);
        }
        PSVECSubtract(&target, &bullet->pos, &dir);
        PSVECNormalize(&dir, &dir);
        PSVECAdd(&vel, &dir, &vel);
        PSVECScale(&vel, &vel, bullet->unkFC / bullet->param->unk1C);
        PSVECAdd(&bullet->unkD8, &vel, &bullet->pos);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, bullet->mtx);
        if (bullet->time == 0) {
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            bullet->mtx[0][3] = bullet->pos.x;
            bullet->mtx[1][3] = bullet->pos.y;
            bullet->mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, bullet->mtx);
        }
        if (bullet->machine->gunNo == 9) {
            BulletAirEffectCreate(bullet, bullet->mtx);
        }
        bullet->time++;
        MathMtxRotGet(bullet->mtx, &bullet->unkE4);
        hit = 0;
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageWallCheck(&bullet->pos, NULL)) {
            hit = 2;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 2;
        } else if (bullet->time >= bullet->param->unkC) {
            hit = 2;
        } else if (SdStageFloorCheck(&bullet->pos, NULL)) {
            hit = 2;
        }
        if (hit) {
            SdMachineFxImpactPlay(bullet);
            vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
            MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletImpactCreate(bullet, mtx);
            if (hit == 2) {
                bullet->unk64 = bullet->param->unk18;
                PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &vel);
                MathPlaneRotMtxGet(&vel, NULL, 0.0f, bullet->mtx);
                BulletMachineCol(bullet);
                BulletRabbitHitCheck(bullet);
                BulletObjHitCheck(bullet);
            }
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            if (bullet->mdlId[1] != -1) {
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            }
            bullet->mode = 0;
        }
        break;
    }
}

/* 10 insns */
static void BulletSanboUpdate(SDBULLET *bullet)
{
    BulletSuikaUpdate(bullet);
}

/* 291 insns */
static void BulletPakkunUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF vel;
    HuVecF up;
    s32 hit;
    s32 damage;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        BulletLaserCheck(bullet);
        bullet->unkD8 = bullet->pos;
        bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
        bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, bullet->unk11C.z, bullet->unk11C.y);
        PSVECSubtract(&bullet->pos, &bullet->unkD8, &vel);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, mtx);
        if (bullet->time == 0) {
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, mtx);
        }
        bullet->time++;
        if ((bullet->time & 3) == 0) {
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletAirEffectCreate(bullet, mtx);
        }
        MathMtxRotGet(mtx, &bullet->unkE4);
        hit = 0;
        vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageFloorCheck(&bullet->pos, &vel)) {
            hit = 2;
        } else if (SdStageWallCheck(&bullet->pos, &vel)) {
            hit = 2;
            vel.y = -0.5f;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 2;
        }
        if (hit == 0) {
            damage = bullet->machine->unk3D4 / 3;
            if (damage == 0) {
                damage = 1;
            }
            BulletParticleCol(bullet, 1, damage);
            BulletParticleRabbitHitCheck(bullet, 1);
            BulletParticleObjHitCheck(bullet, 1);
            break;
        }
        SdMachineFxImpactPlay(bullet);
        if (bullet->mdlId[1] != -1) {
            Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
        }
        MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
        mtx[0][3] = bullet->pos.x;
        mtx[1][3] = bullet->pos.y;
        mtx[2][3] = bullet->pos.z;
        BulletImpactCreate(bullet, mtx);
        if (hit == 1) {
            bullet->mode = 0;
        } else {
            bullet->time = 0;
            bullet->mode = 2;
        }
        break;
    case 2:
        damage = bullet->machine->unk3D4 / 3;
        if (damage == 0) {
            damage = 1;
        }
        if (MgSeqModeGet() == 5) {
            BulletParticleCol(bullet, 1, damage);
            BulletParticleRabbitHitCheck(bullet, 1);
            BulletParticleObjHitCheck(bullet, 1);
        }
        if (++bullet->time >= 60.0f) {
            bullet->mode = 0;
        }
        break;
    }
}

/* 215 insns */
static void BulletKoopaFireUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    Mtx rotMtx;
    HuVecF pos;
    SDMACHINE *machine;
    SDGUN *gun;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
    case 2:
        machine = bullet->machine;
        gun = bullet->gun;
        bullet->time++;
        if (bullet->time == 1) {
            HuAudFXVolSet(bullet->machine->unk3F4, 127);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(bullet->machine->gunMdl, 0.0f);
        }
        if (bullet->time == 6) {
            Hu3DModelAttrSet(bullet->machine->gunMdl, HU3D_MOTATTR_PAUSE);
        }
        if (bullet->time % 2 == 0) {
            bullet->unkD8.y = PSVECMag(&machine->unk160);
            PSMTXTrans(mtx, machine->pos.x, machine->pos.y, machine->pos.z);
            PSMTXConcat(mtx, machine->mtx, mtx);
            PSMTXConcat(mtx, gun->mtx, mtx);
            PSMTXRotRad(rotMtx, 'x', 0.34906584f);
            pos = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
            PSMTXConcat(mtx, rotMtx, mtx);
            mtx[0][3] = pos.x;
            mtx[1][3] = pos.y;
            mtx[2][3] = pos.z;
            BulletEffectCreate(bullet, mtx);
        }
        BulletParticleObjHitCreate(bullet, 5);
        if (MgSeqModeGet() == 5) {
            BulletParticleCol(bullet, 5, bullet->machine->unk3D4);
            BulletParticleRabbitHitCheck(bullet, 5);
            BulletParticleObjHitCheck(bullet, 5);
        }
        if (bullet->mode == 1) {
            if (!(HuPadBtn[bullet->machine->unk348] & PAD_BUTTON_B) || MgSeqModeGet() != 5 || bullet->time >= 240.0f) {
                if (bullet->time >= 240.0f) {
                    bullet->gun->unk0 = 60;
                }
                HuAudFXVolSet(bullet->machine->unk3F4, 0);
                bullet->mode = 2;
            }
        } else if (bullet->time >= 15.0f) {
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_PAUSE);
            bullet->mode = 0;
        }
        break;
    }
}

/* 381 insns */
static void BulletAikunUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    Mtx gunMtx;
    HuVecF vel;
    HuVecF up;
    HuVecF pos;
    HuVecF dir;
    float dist;
    s32 hit;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    SDMACHINE *machine;
    SDGUN *gun;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        bullet->unkD8 = bullet->pos;
        bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
        bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 0.0f, bullet->unk11C.y);
        PSVECSubtract(&bullet->pos, &bullet->unk104, &vel);
        dist = PSVECMag(&vel) * 0.8f;
        if (bullet->time < 30.0f) {
            Hu3DModelScaleSet(bullet->mdlId[0], 0.75f, 0.75f, dist / 40.0f);
        }
        PSVECSubtract(&bullet->pos, &bullet->unkD8, &vel);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, mtx);
        if (bullet->time == 0) {
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, mtx);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            bullet->time = 1;
        }
        MathMtxRotGet(mtx, &bullet->unkE4);
        pos = bullet->pos;
        hit = 0;
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageWallCheck(&pos, NULL)) {
            hit = 1;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageFloorCheck(&pos, &vel)) {
            hit = 1;
        } else {
            PSVECSubtract(&bullet->pos, &bullet->unk104, &dir);
            dist = PSVECMag(&dir);
            if (dist > bullet->param->unkC) {
                hit = 1;
            }
        }
        if (hit) {
            SdMachineFxImpactPlay(bullet);
            vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
            MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletImpactCreate(bullet, mtx);
            bullet->mode++;
        }
        break;
    case 2:
        Hu3DData[bullet->mdlId[0]].scale.z -= bullet->unkFC / 40.0f;
        if (Hu3DData[bullet->mdlId[0]].scale.z > 0.1f) {
            break;
        }
        Hu3DData[bullet->mdlId[0]].scale.z = 0.1f;
        Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
        particle = Hu3DData[sys->particleMdlId[6]].hookData;
        data = particle->data;
        if (data->time == 0) {
            bullet->mode = 0;
        }
        break;
    }
    if (bullet->mode != 0) {
        particle = Hu3DData[sys->particleMdlId[6]].hookData;
        data = &particle->data[bullet->effectNo[6]];
        if (data->time != 0) {
            machine = bullet->machine;
            gun = bullet->gun;
            PSMTXTrans(gunMtx, machine->pos.x, machine->pos.y, machine->pos.z);
            PSMTXConcat(gunMtx, machine->mtx, gunMtx);
            PSMTXConcat(gunMtx, gun->mtx, gunMtx);
            pos = (HuVecF) { gunMtx[0][3], gunMtx[1][3], gunMtx[2][3] };
            data[0].pos = data[1].pos = data[2].pos = pos;
        }
    }
}

/* 268 insns */
static void BulletBananaUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    Mtx rotMtx;
    HuVecF vel;
    HuVecF up;
    HuVecF dir;
    float dist;
    s32 hit;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        bullet->unkD8 = bullet->pos;
        bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
        bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 0.0f, bullet->unk11C.y);
        PSVECSubtract(&bullet->pos, &bullet->unkD8, &vel);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, mtx);
        if (bullet->time == 0) {
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, mtx);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
        }
        bullet->time++;
        PSMTXRotRad(rotMtx, 'z', (bullet->time * 2.5f) * 0.017453292f);
        PSMTXConcat(mtx, rotMtx, mtx);
        MathMtxRotGet(mtx, &bullet->unkE4);
        hit = 0;
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageWallCheck(&bullet->pos, NULL)) {
            hit = 2;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 2;
        } else if (SdStageFloorCheck(&bullet->pos, &vel)) {
            hit = 2;
        } else {
            PSVECSubtract(&bullet->pos, &bullet->unk104, &dir);
            dist = PSVECMag(&dir);
            if (dist > bullet->param->unkC) {
                hit = 2;
            }
        }
        if (hit) {
            SdMachineFxImpactPlay(bullet);
            vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
            MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletImpactCreate(bullet, mtx);
            if (hit == 2) {
                bullet->unk64 = bullet->param->unk18;
                PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &vel);
                MathPlaneRotMtxGet(&vel, NULL, 0.0f, bullet->mtx);
                BulletMachineCol(bullet);
                BulletRabbitHitCheck(bullet);
                BulletObjHitCheck(bullet);
            }
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            if (bullet->mdlId[1] != -1) {
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            }
            bullet->mode = 0;
        }
        break;
    }
}

/* 10 insns */
static void BulletLaserUpdate(SDBULLET *bullet)
{
    BulletKillerUpdate(bullet);
}

/* 273 insns */
static void BulletHaruUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    Mtx rotMtx;
    HuVecF vel;
    HuVecF up;
    HuVecF dir;
    float dist;
    s32 hit;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        bullet->unkD8 = bullet->pos;
        bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
        bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 0.0f, bullet->unk11C.y);
        PSVECSubtract(&bullet->pos, &bullet->unkD8, &vel);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, mtx);
        if (bullet->time == 0) {
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, mtx);
        }
        bullet->time++;
        PSMTXRotRad(rotMtx, 'z', (bullet->time * 5.0f) * 0.017453292f);
        PSMTXConcat(mtx, rotMtx, mtx);
        MathMtxRotGet(mtx, &bullet->unkE4);
        hit = 0;
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (!(HuPadBtn[bullet->machine->unk348] & PAD_BUTTON_B)) {
            hit = 2;
        } else if (SdStageWallCheck(&bullet->pos, NULL)) {
            hit = 2;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 2;
        } else if (SdStageFloorCheck(&bullet->pos, &vel)) {
            hit = 2;
        } else {
            PSVECSubtract(&bullet->pos, &bullet->unk104, &dir);
            dist = PSVECMag(&dir);
            if (dist > bullet->param->unkC) {
                hit = 2;
            }
        }
        if (hit) {
            SdMachineFxImpactPlay(bullet);
            vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
            MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletImpactCreate(bullet, mtx);
            if (hit == 2) {
                bullet->unk64 = bullet->param->unk18;
                PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &vel);
                MathPlaneRotMtxGet(&vel, NULL, 0.0f, bullet->mtx);
                BulletMachineCol(bullet);
                BulletRabbitHitCheck(bullet);
                BulletObjHitCheck(bullet);
            }
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            if (bullet->mdlId[1] != -1) {
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            }
            bullet->gun->unk0 = bullet->machine->unk20C;
            bullet->mode = 0;
        }
        break;
    }
}

/* 229 insns */
static void BulletKoopaArmUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF ofs;
    float time;
    float maxTime;
    SDMACHINE *machine;
    SDGUN *gun;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        machine = bullet->machine;
        gun = bullet->gun;
        if (bullet->time == 0) {
            bullet->pos.y += 50.0f;
            bullet->mtx[0][3] = bullet->pos.x;
            bullet->mtx[1][3] = bullet->pos.y;
            bullet->mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, bullet->mtx);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            Hu3DMotionShapeSpeedSet(bullet->machine->gunMdl, 1.0f);
            bullet->time = 1;
        }
        time = Hu3DData[bullet->machine->gunMdl].motShapeWork.time;
        maxTime = Hu3DMotionShapeMaxTimeGet(bullet->machine->gunMdl);
        if (time < 10.0f) {
            PSMTXTrans(mtx, machine->pos.x, machine->pos.y, machine->pos.z);
            PSMTXConcat(mtx, machine->mtx, mtx);
            PSMTXConcat(mtx, gun->mtx, mtx);
            ofs = (HuVecF) { 0.0f, 20.0f - time * 18.0f, 184.0f + time * 51.25f };
            PSMTXMultVec(mtx, &ofs, &bullet->pos);
            if (BulletObjHitCheck(bullet) && Hu3DData[bullet->machine->gunMdl].motShapeWork.time >= 1.0f) {
                bullet->mtx[0][3] = bullet->pos.x;
                bullet->mtx[1][3] = bullet->pos.y;
                bullet->mtx[2][3] = bullet->pos.z;
                BulletImpactCreate(bullet, bullet->mtx);
                Hu3DMotionShapeSpeedSet(bullet->machine->gunMdl, -0.15f);
                HuAudFXPlayVolPan(bullet->machine->playerNo + 0x563, 127, (bullet->machine->playerNo * 32) + 48);
                bullet->mode = 2;
                break;
            }
            if (MgSeqModeGet() == 5 && (BulletMachineCol(bullet) || BulletRabbitHitCheck(bullet))) {
                bullet->mtx[0][3] = bullet->pos.x;
                bullet->mtx[1][3] = bullet->pos.y;
                bullet->mtx[2][3] = bullet->pos.z;
                BulletImpactCreate(bullet, bullet->mtx);
            }
        }
        if (time >= maxTime) {
            bullet->mode = 0;
        }
        break;
    case 2:
        if (Hu3DData[bullet->machine->gunMdl].motShapeWork.time < 0.1f) {
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            bullet->mode = 0;
        }
        break;
    }
}

/* 386 insns */
static void BulletBombSmallUpdate(SDBULLET *bullet)
{
    Mtx mtx;
    HuVecF vel;
    HuVecF up;
    s32 hit;

    switch (bullet->mode) {
    case 0:
        break;
    case 1:
        bullet->unkD8 = bullet->pos;
        bullet->unk11C.y += bullet->unkFC / bullet->unk11C.x;
        bullet->pos = MathVecInterpolate(bullet->unk104, bullet->unk110, 25.0f, bullet->unk11C.y);
        PSVECSubtract(&bullet->pos, &bullet->unkD8, &vel);
        up = (HuVecF) { bullet->mtx[0][1], bullet->mtx[1][1], bullet->mtx[2][1] };
        MathPlaneRotMtxGet(&vel, &up, 0.0f, mtx);
        if (bullet->time == 0) {
            mtx[0][3] = bullet->pos.x;
            mtx[1][3] = bullet->pos.y;
            mtx[2][3] = bullet->pos.z;
            BulletEffectCreate(bullet, mtx);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_SHAPE_PAUSE);
            Hu3DMotionShapeTimeSet(bullet->machine->gunMdl, 0.0f);
            Hu3DModelAttrReset(bullet->machine->gunMdl, HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(bullet->machine->gunMdl, 0.0f);
            bullet->time = 1;
        }
        MathMtxRotGet(mtx, &bullet->unkE4);
        hit = 0;
        vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
        if (BulletMachineCol(bullet)) {
            hit = 1;
        } else if (MgSeqModeGet() > 5) {
            hit = 1;
        } else if (BulletRabbitHitCheck(bullet)) {
            hit = 1;
        } else if (SdStageWallCheck(&bullet->pos, NULL)) {
            hit = 2;
        } else if (BulletObjHitCheck(bullet)) {
            hit = 2;
        } else if (SdStageFloorCheck(&bullet->pos, &vel)) {
            hit = 3;
        }
        if (hit == 0) {
            break;
        }
        if (hit != 3) {
            SdMachineFxImpactPlay(bullet);
        } else {
            SdImpactSoundStart(0x555, bullet->pos, 0.75f);
        }
        MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
        mtx[0][3] = bullet->pos.x;
        mtx[1][3] = bullet->pos.y;
        mtx[2][3] = bullet->pos.z;
        bullet->time = 0;
        if (hit < 3) {
            BulletImpactCreate(bullet, mtx);
            if (hit == 2) {
                bullet->unk64 = bullet->param->unk18;
                PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &vel);
                MathPlaneRotMtxGet(&vel, NULL, 0.0f, bullet->mtx);
                BulletRabbitHitCheck(bullet);
                BulletMachineCol(bullet);
                BulletObjHitCheck(bullet);
            }
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
            if (bullet->mdlId[1] != -1) {
                Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
            }
            bullet->mode = 0;
        } else {
            Hu3DMotionSet(bullet->mdlId[0], bullet->mdlId[4]);
            Hu3DModelAttrSet(bullet->mdlId[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_SHAPE_LOOP);
            Hu3DMotionTimeSet(bullet->mdlId[0], 0.0f);
            Hu3DModelAttrReset(bullet->mdlId[2], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(bullet->mdlId[2], 0.0f);
            BulletAirEffectCreate(bullet, mtx);
            bullet->mode++;
        }
        break;
    case 2:
        if (MgSeqModeGet() == 5 && ++bullet->time < bullet->param->unk10) {
            break;
        }
        SdMachineFxImpactPlay(bullet);
        vel = (HuVecF) { 0.0f, 1.0f, 0.0f };
        MathPlaneRotMtxGet(&vel, NULL, 0.0f, mtx);
        mtx[0][3] = bullet->pos.x;
        mtx[1][3] = bullet->pos.y;
        mtx[2][3] = bullet->pos.z;
        BulletImpactCreate(bullet, mtx);
        bullet->unk64 = bullet->param->unk18;
        PSVECSubtract(&bullet->machine->enemy->pos, &bullet->pos, &vel);
        MathPlaneRotMtxGet(&vel, NULL, 0.0f, bullet->mtx);
        if (MgSeqModeGet() == 5) {
            BulletMachineCol(bullet);
            BulletRabbitHitCheck(bullet);
            BulletObjHitCheck(bullet);
        }
        Hu3DModelAttrSet(bullet->mdlId[0], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bullet->mdlId[1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(bullet->mdlId[2], HU3D_ATTR_DISPOFF);
        Hu3DMotionSet(bullet->mdlId[0], bullet->mdlId[3]);
        Hu3DMotionTimeSet(bullet->mdlId[0], 0.0f);
        SdModelGlowSet(bullet->mdlId[0]);
        bullet->time = bullet->mode = 0;
        break;
    }
}

/* 121 insns */
static s32 BulletMachineCol(SDBULLET *bullet)
{
    SDMACHINE *enemy;
    HuVecF dir;
    HuVecF pos;
    float radius;
    float dist;

    enemy = bullet->machine->enemy;
    if (enemy->mode != 1) {
        return 0;
    }
    if (enemy->unk210 != 0) {
        return 0;
    }
    pos = enemy->pos;
    if (bullet->machine->gunNo != 11) {
        radius = bullet->unk64;
    } else {
        radius = 80.0f;
    }
    if (pos.y - enemy->unk354 > bullet->pos.y + radius) {
        return 0;
    }
    if (pos.y + enemy->unk35C < bullet->pos.y - radius) {
        return 0;
    }
    PSVECSubtract(&pos, &bullet->pos, &dir);
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (dist <= enemy->unk358 + radius) {
        pos = (HuVecF) { bullet->mtx[0][2], bullet->mtx[1][2], bullet->mtx[2][2] };
        SdMachineDamage(enemy, pos, bullet->machine->unk3D4);
        return 1;
    }
    return 0;
}

/* 114 insns */
static s32 BulletParticleCol(SDBULLET *bullet, s32 effectNo, s32 damage)
{
    SDMACHINE *enemy;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    HuVecF dir;
    HuVecF pos;
    float dist;
    s32 i;

    enemy = bullet->machine->enemy;
    particle = Hu3DData[sys->particleMdlId[effectNo]].hookData;
    data = &particle->data[bullet->effectNo[effectNo]];
    if (enemy->mode != 1) {
        return 0;
    }
    if (enemy->unk210 != 0) {
        return 0;
    }
    pos = enemy->pos;
    pos.y += enemy->unk358;
    for (i = 0; i < (&bullet->param->unk24)[effectNo]; i++) {
        if (0.0f != data[i].scale) {
            PSVECSubtract(&pos, &data[i].pos, &dir);
            dist = PSVECMag(&dir);
            if (dist <= enemy->unk358 + data[i].scale * 0.5f) {
                PSVECSubtract(&enemy->pos, &bullet->machine->pos, &pos);
                SdMachineDamage(enemy, pos, damage);
                return 1;
            }
        }
    }
    return 0;
}

/* 23 insns */
static s32 BulletObjHitCheck(SDBULLET *bullet)
{
    return SdStageObjHitCheck2(bullet->pos, bullet->unk64, 1);
}

/* 72 insns */
static s32 BulletParticleObjHitCheck(SDBULLET *bullet, s32 effectNo)
{
    HU3DPARTICLE *particle;
    s32 i;
    HU3DPARTICLEDATA *data;

    particle = Hu3DData[sys->particleMdlId[effectNo]].hookData;
    data = &particle->data[bullet->effectNo[effectNo]];
    for (i = 0; i < (&bullet->param->unk24)[effectNo]; i++) {
        if (0.0f != data[i].scale) {
            if (SdStageObjHitCheck2(data[i].pos, data[i].scale * 0.5f, 1)) {
                return 1;
            }
        }
    }
    return 0;
}

/* 81 insns */
static void BulletParticleObjHitCreate(SDBULLET *bullet, s32 effectNo)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s32 i;

    particle = Hu3DData[sys->particleMdlId[effectNo]].hookData;
    data = &particle->data[bullet->effectNo[effectNo]];
    for (i = 0; i < (&bullet->param->unk24)[effectNo]; i++) {
        if (0.0f != data[i].scale) {
            if (SdStageObjHitCheck2(data[i].pos, data[i].scale * 0.5f, 1)) {
                data[i].time = data[i].parManId = 0;
                data[i].scale = 0.0f;
            }
        }
    }
}

/* 104 insns */
static s32 BulletRabbitHitCheck(SDBULLET *bullet)
{
    HuVecF rabbitPos;
    HuVecF pos;

    if (sys->gameType != 2) {
        return 0;
    }
    if (SdRabbitDoneCheck()) {
        return 0;
    }
    if (!SdRabbitCheck()) {
        return 0;
    }
    rabbitPos = SdRabbitPosGet();
    if (bullet->machine->gunNo != 11) {
        if (bullet->pos.y - bullet->unk64 > rabbitPos.y + 90.0f) {
            return 0;
        }
        if (bullet->pos.y + bullet->unk64 < rabbitPos.y) {
            return 0;
        }
    }
    pos = bullet->pos;
    rabbitPos.y = pos.y = 0.0f;
    if (PSVECDistance(&rabbitPos, &pos) > 100.0f + bullet->unk64) {
        return 0;
    }
    SdRabbitPlayerCheck(bullet->machine->playerNo);
    HuAudFXPlayVolPan(bullet->machine->playerNo + 0x565, 127, (bullet->machine->playerNo * 32) + 48);
    HuAudFXPlayVolPan(bullet->machine->playerNo + 0x567, 127, (bullet->machine->playerNo * 32) + 48);
    SdPlayerSoundPlay(bullet->machine, 4);
    return 1;
}

/* 162 insns */
static s32 BulletParticleRabbitHitCheck(SDBULLET *bullet, s32 effectNo)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s32 i;
    HuVecF rabbitPos;
    HuVecF pos;

    particle = Hu3DData[sys->particleMdlId[effectNo]].hookData;
    data = &particle->data[bullet->effectNo[effectNo]];
    if (sys->gameType != 2) {
        return 0;
    }
    if (SdRabbitDoneCheck()) {
        return 0;
    }
    if (!SdRabbitCheck()) {
        return 0;
    }
    rabbitPos = SdRabbitPosGet();
    for (i = 0; i < (&bullet->param->unk24)[effectNo]; i++) {
        if (0.0f != data[i].scale) {
            if (bullet->machine->gunNo != 6) {
                if (data[i].pos.y - data[i].scale * 0.5f > rabbitPos.y + 90.0f) {
                    continue;
                }
                if (data[i].pos.y + data[i].scale * 0.5f < rabbitPos.y) {
                    continue;
                }
            }
            pos = data[i].pos;
            rabbitPos.y = pos.y = 0.0f;
            if (PSVECDistance(&rabbitPos, &pos) > 100.0f + data[i].scale * 0.5f) {
                continue;
            }
            HuAudFXPlayVolPan(bullet->machine->playerNo + 0x565, 127, (bullet->machine->playerNo * 32) + 48);
            HuAudFXPlayVolPan(bullet->machine->playerNo + 0x567, 127, (bullet->machine->playerNo * 32) + 48);
            SdPlayerSoundPlay(bullet->machine, 4);
            SdRabbitPlayerCheck(bullet->machine->playerNo);
            return 1;
        }
    }
    return 0;
}

/* 119 insns */
static void BulletLaserCheck(SDBULLET *bullet)
{
    HuVecF dir;
    float oldLen;
    float y;

    if (bullet->gun->unk34 == bullet) {
        if (HuPadBtn[bullet->machine->unk348] & PAD_BUTTON_B) {
            PSVECSubtract(&bullet->unk110, &bullet->unk104, &dir);
            y = dir.y;
            dir.y = 0.0f;
            oldLen = bullet->unk11C.x;
            bullet->unk11C.x = PSVECMag(&dir);
            bullet->unk11C.x += bullet->param->unkC / 45.0f;
            bullet->unk11C.x = (bullet->unk11C.x > bullet->param->unkC) ? bullet->param->unkC : ((bullet->unk11C.x < 1.0f) ? 1.0f : bullet->unk11C.x);
            bullet->unk11C.y *= oldLen / bullet->unk11C.x;
            bullet->unk11C.z = bullet->unk11C.x * (0.15f - 0.05f * (bullet->unk11C.x / bullet->param->unkC));
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, bullet->unk11C.x);
            dir.y = y;
            PSVECAdd(&dir, &bullet->unk104, &bullet->unk110);
        } else {
            bullet->gun->unk34 = NULL;
        }
    }
}

/* 0x1104 */ static SDBULLETMTXFUNC effectCreateFuncTbl[13] = { ShootEffectCreate, SuikaEffectCreate, ShootEffectCreate, ShootEffectCreate, SanboEffectCreate, PakkunEffectCreate, KoopaFireEffectCreate, AikunEffectCreate, ShootEffectCreate, ShootEffectCreate, ShootEffectCreate, ShootEffectCreate, ShootEffectCreate };
/* 0x1138 */ static SDBULLETMTXFUNC airEffectUpdateFuncTbl[13] = { NULL, NULL, BomheiAirEffectUpdate, NULL, NULL, PakkunAirEffectUpdate, NULL, NULL, NULL, LaserAirEffectUpdate, NULL, NULL, BomheiAirEffectUpdate };
/* 0x116C */ static SDBULLETMTXFUNC impactCreateFuncTbl[13] = { DustCloudImpactCreate, SuikaImpactCreate, BulletDustImpactCreate, BulletDustImpactCreate, SanboImpactCreate, PakkunImpactCreate, DustCloudImpactCreate, AikunImpactCreate, BulletDustImpactCreate, BulletDustImpactCreate, BulletDustImpactCreate, KoopaArmImpactCreate, BulletDustImpactCreate };
/* 0x11A0 */ static SDBULLETFUNC effectUpdateFuncTbl[13] = { KinokoEffectUpdate, NULL, FlameEffectUpdate, FlameEffectUpdate, KillerEffectUpdate, NULL, NULL, NULL, FlameEffectUpdate, FlameEffectUpdate, FlameEffectUpdate, KoopaArmEffectUpdate, FlameEffectUpdate };
/* 0x11D4 */ static SDBULLETFUNC flameEffectFuncTbl[13] = { NULL, NULL, FlameEffectUpdateData, FlameEffectUpdateData, NULL, NULL, NULL, NULL, FlameEffectUpdateData, FlameEffectUpdateData, FlameEffectUpdateData, NULL, FlameEffectUpdateData };
/* 0x1208 */ static SDBULLETFUNC bulletExplodeFuncTbl[13] = { NULL, NULL, NULL, NULL, NULL, NULL, BulletExplodeUpdate, NULL, NULL, NULL, NULL, NULL, NULL };
/* 0x123C */ static SDBULLETFUNC aikunEffectFuncTbl[13] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, AikunEffectUpdate, NULL, NULL, NULL, NULL, NULL };
/* 0x1270 */ static SDBULLETFUNC pakkunEffectFuncTbl[13] = { NULL, NULL, NULL, NULL, NULL, PakkunEffectUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
/* 0x12A4 */ static SDBULLETFUNC suikaEffectFuncTbl[13] = { NULL, SuikaEffectUpdate, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL };
/* 0x12D8 */ static SDBULLETFUNC starEffectFuncTbl[13] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, StarEffectUpdate, NULL };
/* 0x130C */ static SDBULLETFUNC laserEffectFuncTbl[13] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, LaserEffectUpdate, NULL, NULL, NULL };

/* 134 insns */
static void BulletEffectUpdate(SDBULLET *bullet)
{
    s32 gunNo = bullet->machine->gunNo;

    if (effectUpdateFuncTbl[gunNo]) {
        effectUpdateFuncTbl[gunNo](bullet);
    }
    if (flameEffectFuncTbl[gunNo]) {
        flameEffectFuncTbl[gunNo](bullet);
    }
    if (bulletExplodeFuncTbl[gunNo]) {
        bulletExplodeFuncTbl[gunNo](bullet);
    }
    if (aikunEffectFuncTbl[gunNo]) {
        aikunEffectFuncTbl[gunNo](bullet);
    }
    if (pakkunEffectFuncTbl[gunNo]) {
        pakkunEffectFuncTbl[gunNo](bullet);
    }
    if (suikaEffectFuncTbl[gunNo]) {
        suikaEffectFuncTbl[gunNo](bullet);
    }
    if (starEffectFuncTbl[gunNo]) {
        starEffectFuncTbl[gunNo](bullet);
    }
    if (laserEffectFuncTbl[gunNo]) {
        laserEffectFuncTbl[gunNo](bullet);
    }
}

/* 31 insns */
static void BulletEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    s32 gunNo = bullet->machine->gunNo;

    if (effectCreateFuncTbl[gunNo]) {
        effectCreateFuncTbl[gunNo](bullet, mtx);
    }
}

/* 31 insns */
static void BulletAirEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    s32 gunNo = bullet->machine->gunNo;
    if (airEffectUpdateFuncTbl[gunNo]) {
        airEffectUpdateFuncTbl[gunNo](bullet, mtx);
    }
}

/* 31 insns */
static void BulletImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    s32 gunNo = bullet->machine->gunNo;
    if (impactCreateFuncTbl[gunNo]) {
        impactCreateFuncTbl[gunNo](bullet, mtx);
    }
}

/* 39 insns */
static void KinokoEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    if (data[0].time) {
        KinokoEffectDataUpdate(&data[0], 8);
    }
    if (data[8].time) {
        KinokoEffectDataUpdate(&data[8], 8);
    }
}

/* 147 insns */
static void ShootEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    s32 i;

    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 8; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(mtx3, 'z', 0.017453292f * (45.0f * i));
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ 0xDA, 0xCB, 0x9E, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 148 insns */
static void DustCloudImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    s32 i;

    data += 8;
    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 8; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(mtx3, 'z', 0.017453292f * (45.0f * i));
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ 0xDA, 0xCB, 0x9E, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 101 insns */
static void KinokoEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;
    for (i = 0; i < num; i++) {
        data[i].pos.x += data[i].vel.x;
        data[i].pos.y += data[i].vel.y;
        data[i].pos.z += data[i].vel.z;
        PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
        data[i].scale *= 1.04f;
        data[i].color.a *= 0.9f;
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 39 insns */
static void SuikaEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[7]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[7]];
    if (data[0].time) {
        SuikaEffectDataUpdate(&data[0], 4);
    }
    if (data[4].time) {
        SuikaEffectDataUpdate(&data[4], 4);
    }
}

/* 173 insns */
static void SuikaEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[7]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[7]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    float angle;
    float base;
    s32 i;

    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    base = rand8() % 60;
    for (i = 0; i < 4; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        angle = base + 90.0f * i;
        PSMTXRotRad(mtx3, 'z', 0.017453292f * angle);
        data[i].zRot = 0.017453292f * -angle;
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = bullet->gun->unk3C;
        data[i].scale = 40.0f;
    }
}

/* 174 insns */
static void SuikaImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[7]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[7]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    float angle;
    float base;
    s32 i;

    data += 4;
    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    base = rand8() % 60;
    for (i = 0; i < 4; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        angle = base + 90.0f * i;
        PSMTXRotRad(mtx3, 'z', 0.017453292f * angle);
        data[i].zRot = 0.017453292f * -angle;
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = bullet->gun->unk3C;
        data[i].scale = 40.0f;
    }
}

/* 101 insns */
static void SuikaEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;
    for (i = 0; i < num; i++) {
        data[i].pos.x += data[i].vel.x;
        data[i].pos.y += data[i].vel.y;
        data[i].pos.z += data[i].vel.z;
        PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
        data[i].scale *= 1.04f;
        data[i].color.a *= 0.9f;
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 211 insns */
static void FlameEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    s32 unused = 0;
    s32 i;
    s32 j;

    if (data[0].time) {
        for (i = 0; i < 8; i++) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].scale *= 1.04f;
            data[i].color.a *= 0.9f;
        }
        if (++data->parManId >= 60) {
            data->time = data->parManId = 0;
            for (i = 0; i < 8; i++) {
                data[i].scale = 0.0f;
            }
        }
    }
    if (data[8].time) {
        for (j = 0; j < 8; j++) {
            (data + 8)[j].pos.x += (data + 8)[j].vel.x;
            (data + 8)[j].pos.y += (data + 8)[j].vel.y;
            (data + 8)[j].pos.z += (data + 8)[j].vel.z;
            PSVECScale(&(data + 8)[j].vel, &(data + 8)[j].vel, 0.9f);
            (data + 8)[j].scale *= 1.04f;
            (data + 8)[j].color.a *= 0.9f;
        }
        if (++data[8].parManId >= 60) {
            data[8].time = data[8].parManId = 0;
            for (j = 0; j < 8; j++) {
                (data + 8)[j].scale = 0.0f;
            }
        }
    }
    if (data[16].time) {
        SdEffectFlameUpdate(&data[16], 48);
    }
}

/* 35 insns */
static void FlameEffectUpdateData(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[4]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[4]];
    s32 unused = 0;
    if (data->time) {
        SdEffectFlameUpdateData(data, 25);
    }
}

/* 148 insns */
static void BomheiAirEffectUpdate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    s32 i;

    data += 8;
    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 8; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(mtx3, 'z', 0.017453292f * (45.0f * i));
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ 0xDA, 0xCB, 0x9E, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 55 insns */
static void BulletDustImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particleA = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *dataA = &particleA->data[bullet->effectNo[3]];
    HU3DPARTICLE *particleB = Hu3DData[sys->particleMdlId[4]].hookData;
    HU3DPARTICLEDATA *dataB = &particleB->data[bullet->effectNo[4]];

    SdEffectDustCreateData(bullet->pos, &dataA[16], dataB, bullet->param->unk18 / 300.0f);
}

/* 203 insns */
static void KillerEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    s32 i;
    s32 j;

    if (data[0].time) {
        for (i = 0; i < 1; i++) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].scale *= 1.04f;
            data[i].color.a *= 0.9f;
        }
        if (++data->parManId >= 60) {
            data->time = data->parManId = 0;
            for (i = 0; i < 1; i++) {
                data[i].scale = 0.0f;
            }
        }
    }
    if (data[1].time) {
        for (j = 0; j < 1; j++) {
            (data + 1)[j].pos.x += (data + 1)[j].vel.x;
            (data + 1)[j].pos.y += (data + 1)[j].vel.y;
            (data + 1)[j].pos.z += (data + 1)[j].vel.z;
            PSVECScale(&(data + 1)[j].vel, &(data + 1)[j].vel, 0.9f);
            (data + 1)[j].scale *= 1.04f;
            (data + 1)[j].color.a *= 0.9f;
        }
        if (++data[1].parManId >= 60) {
            data[1].time = data[1].parManId = 0;
            for (j = 0; j < 1; j++) {
                (data + 1)[j].scale = 0.0f;
            }
        }
    }
}

/* 129 insns */
static void SanboEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    s32 i;

    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 1; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        data[i].vel = (HuVecF){ mtx[0][2], mtx[1][2], mtx[2][2] };
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ 0xDA, 0xCB, 0x9E, 0xFF };
        data[i].scale = 75.0f;
    }
}

/* 130 insns */
static void SanboImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    s32 i;

    data += 1;
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 1; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        data[i].vel = (HuVecF){ mtx[0][2], mtx[1][2], mtx[2][2] };
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ 0xDA, 0xCB, 0x9E, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 42 insns */
static void PakkunEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[1]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[1]];
    if (data[0].time) {
        PakkunEffectDataUpdate(&data[0], 4);
    }
    PakkunEffectData2Update(&data[4], 12);
    if (data[16].time) {
        PakkunEffectDataUpdate(&data[16], 8);
    }
}

/* 196 insns */
static void PakkunEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[1]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[1]];
    HuVecF dir = { 0.0f, 0.5f, 1.0f };
    s32 i;

    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 4; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(mtx3, 'z', 0.017453292f * (45.0f + 90.0f * i));
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        data[i].accel = (HuVecF){ 0.0f, -1.0f, 0.0f };
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ rand8() % 128 + 128, rand8() % 128 + 128, rand8() % 128 + 128, 0xB4 };
        data[i].scale = 80.0f;
    }
}

/* 294 insns */
static void PakkunAirEffectUpdate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    Mtx mtx4;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[1]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[1]];
    HuVecF dir = { 0.0f, 1.0f, 0.0f };
    s32 rot;
    s32 i;

    data += 4;
    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    for (i = 0; i < 12; i++) {
        if (data[i].time == 0) {
            rot = rand8() % 41 - 20;
            PSMTXRotRad(mtx3, 'y', 0.017453292f * rot);
            PSMTXConcat(mtx2, mtx3, mtx4);
            rot = rand8() % 21 - 10;
            PSMTXRotRad(mtx3, 'x', 0.017453292f * rot);
            PSMTXConcat(mtx4, mtx3, mtx4);
            data[i].time = 1;
            data[i].parManId = 0;
            data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
            data[i].vel = (HuVecF){ mtx4[0][2], mtx4[1][2], mtx4[2][2] };
            PSVECScale(&data[i].vel, &data[i].vel, bullet->unkFC);
            data[i].accel = (HuVecF){ 0.0f, -1.0f, 0.0f };
            data[i].color = (GXColor){ rand8() % 128 + 128, rand8() % 128 + 128, rand8() % 128 + 128, 0xB4 };
            data[i].scale = 90.0f + rand8() % 20;
            data[i].zRot = rand8() % 120;
            break;
        }
    }
}

/* 193 insns */
static void PakkunImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    Mtx mtx2;
    Mtx mtx3;
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[1]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[1]];
    HuVecF dir = { 0.0f, 1.0f, 1.0f };
    s32 i;

    data += 16;
    PSMTXCopy(mtx, mtx2);
    mtx2[0][3] = mtx2[1][3] = mtx2[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 8; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(mtx3, 'z', 0.017453292f * (45.0f * i));
        PSMTXConcat(mtx2, mtx3, mtx3);
        PSMTXMultVec(mtx3, &dir, &data[i].vel);
        data[i].accel = (HuVecF){ 0.0f, -1.5f, 0.0f };
        PSVECScale(&data[i].vel, &data[i].vel, 15.0f);
        data[i].color = (GXColor){ rand8() % 128 + 128, rand8() % 128 + 128, rand8() % 128 + 128, 0xB4 };
        data[i].scale = 80.0f;
    }
}

/* 109 insns */
static void PakkunEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;
    for (i = 0; i < num; i++) {
        data[i].pos.x += data[i].vel.x;
        data[i].pos.y += data[i].vel.y + data[i].accel.y;
        data[i].pos.z += data[i].vel.z;
        PSVECScale(&data[i].vel, &data[i].vel, 0.98f);
        data[i].accel.y *= 1.08f;
        data[i].scale *= 0.98f;
        if (data->parManId % 2 == 0) {
            data[i].zRot += 45.0f;
        }
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 114 insns */
static void PakkunEffectData2Update(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;
    for (i = 0; i < num; i++) {
        if (data[i].time) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y + data[i].accel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].accel.y *= 1.1f;
            data[i].scale *= 0.98f;
            if (data[i].parManId % 2 == 0) {
                data[i].zRot += 45.0f;
            }
            if (++data[i].parManId >= 36) {
                data[i].time = data[i].parManId = 0;
                data[i].scale = 0.0f;
            }
        }
    }
}

/* 30 insns */
static void BulletExplodeUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[5]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[5]];

    KoopaFireEffectDataUpdate(data, 30);
}

/* 229 insns */
static void KoopaFireEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[5]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[5]];
    HuVecF dir = { 0.0f, 0.0f, 1.0f };
    HuVecF dir2 = { 0.0f, 0.0f, 1.0f };
    Mtx m;
    Mtx rot;
    Mtx tmp;
    s32 i;
    s32 ang;

    PSMTXCopy(mtx, m);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    for (i = 0; i < 30; i++) {
        if (data[i].time == 0) {
            ang = rand8() % 31 - 15;
            PSMTXRotRad(rot, 'y', 0.017453292f * ang);
            PSMTXConcat(m, rot, tmp);
            ang = rand8() % 15 - 7;
            PSMTXRotRad(rot, 'x', 0.017453292f * ang);
            PSMTXConcat(tmp, rot, tmp);
            data[i].time = 1;
            data[i].parManId = 0;
            data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
            PSMTXMultVec(tmp, &dir, &data[i].vel);
            PSVECScale(&data[i].vel, &data[i].vel, 25.0f + bullet->unkD8.y);
            data[i].accel.y = 1.0f;
            data[i].color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
            data[i].scale = 45.0f + (rand8() % 15);
            break;
        }
    }
}

/* 206 insns */
static void KoopaFireEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;

    for (i = 0; i < num; i++) {
        if (data[i].time != 0) {
            if (data[i].scale > 0.0f) {
                data[i].pos.x += data[i].vel.x;
                data[i].pos.y += data[i].vel.y + data[i].accel.y;
                data[i].pos.z += data[i].vel.z;
                PSVECScale(&data[i].vel, &data[i].vel, 0.95f);
                data[i].accel.y *= 1.02f;
                data[i].scale *= 1.08f;
                if (data[i].scale > 200.0f) {
                    data[i].scale = 200.0f;
                }
                data[i].color.r *= 0.995f;
                data[i].color.g *= 0.98f;
                data[i].color.b *= 0.9f;
                data[i].color.a *= 0.92f;
                if (data[i].color.a < 2) {
                    data[i].scale = 0.0f;
                }
            }
            if (++data[i].parManId >= 60) {
                data[i].time = data[i].parManId = 0;
                data[i].scale = 0.0f;
            }
        }
    }
}

/* 39 insns */
static void AikunEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[6]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[6]];

    if (data[0].time != 0) {
        AikunEffectDataUpdate(&data[0], 3);
    }
    if (data[3].time != 0) {
        AikunEffectDataUpdate(&data[3], 3);
    }
}

/* 107 insns */
static void AikunEffectCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[6]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[6]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    Mtx m;
    s32 i;

    PSMTXCopy(mtx, m);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 3; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        data[i].color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 108 insns */
static void AikunImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[6]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[6]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    Mtx m;
    s32 i;
    data += 3;
    PSMTXCopy(mtx, m);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 3; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        data[i].color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
        data[i].scale = 50.0f;
    }
}

/* 93 insns */
static void AikunEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;

    for (i = 0; i < num; i++) {
        if (data->parManId >= i * 10 + 60) {
            data[i].scale = 0.0f;
        } else if (data->parManId >= i * 10) {
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].scale *= 1.04f;
            data[i].color.a *= 0.9f;
        }
    }
    if (++data->parManId >= 80) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 146 insns */
static void LaserAirEffectUpdate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[10]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[10]];
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    HuVecF dir;
    s32 i;

    dir = (HuVecF){ mtx[0][2], mtx[1][2], mtx[2][2] };
    PSVECScale(&dir, &dir, -80.0f);
    PSVECAdd(&bullet->pos, &dir, &dir);
    for (i = 0; i < 20; i++) {
        if (data[i].time == 0) {
            data[i].time = 1;
            data[i].parManId = 0;
            data[i].vel = (HuVecF){ 0.0f, 0.0f, 0.0f };
            data[i].accel = (HuVecF){ 0.0f, 0.0f, 0.0f };
            data[i].pos = dir;
            data[i].scale = 45.0f;
            data[i].color = color;
            break;
        }
    }
}

/* 30 insns */
static void LaserEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[10]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[10]];

    LaserEffectDataUpdate(data, 20);
}

/* 124 insns */
static void LaserEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    GXColor color = { 0x00, 0xFF, 0xFF, 0xB4 };
    s32 i;

    for (i = 0; i < num; i++) {
        if (data[i].time != 0) {
            data[i].scale *= 0.98f;
            if (data[i].parManId <= 6) {
                data[i].color.r = 255 - (255 - color.r) * data[i].parManId / 6;
                data[i].color.g = 255 - (255 - color.g) * data[i].parManId / 6;
                data[i].color.b = 255 - (255 - color.b) * data[i].parManId / 6;
            }
            data[i].color.a *= 0.85f;
            if (++data[i].parManId >= 20) {
                data[i].time = data[i].parManId = 0;
                data[i].scale = 0.0f;
            }
        }
    }
}

/* 118 insns */
static void KoopaArmEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[3]];
    s32 i;

    if (data->time != 0) {
        for (i = 0; i < 8; i++) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].scale *= 1.04f;
            data[i].color.a *= 0.9f;
        }
        if (++data->parManId >= 60) {
            data->time = data->parManId = 0;
            for (i = 0; i < 8; i++) {
                data[i].scale = 0.0f;
            }
        }
    }
}

/* 33 insns */
static void StarEffectUpdate(SDBULLET *bullet)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[8]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[8]];

    if (data->time != 0) {
        StarEffectDataUpdate(data, 12);
    }
}

/* 224 insns */
static void KoopaArmImpactCreate(SDBULLET *bullet, Mtx mtx)
{
    HU3DPARTICLE *particle = Hu3DData[sys->particleMdlId[8]].hookData;
    HU3DPARTICLEDATA *data = &particle->data[bullet->effectNo[8]];
    HuVecF dir = { 0.0f, 1.0f, 1.5f };
    HuVecF dir2 = { 0.0f, 1.0f, -0.25f };
    Mtx m;
    Mtx rot;
    s32 i;

    PSMTXCopy(mtx, m);
    m[0][3] = m[1][3] = m[2][3] = 0.0f;
    PSVECNormalize(&dir, &dir);
    PSVECNormalize(&dir2, &dir2);
    data->time = 1;
    data->parManId = 0;
    for (i = 0; i < 8; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(rot, 'z', 0.017453292f * (45.0f * i));
        PSMTXConcat(m, rot, rot);
        PSMTXMultVec(rot, &dir, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 25.0f);
        data[i].color.a = 255;
        data[i].scale = 30.0f;
    }
    for (i = 8; i < 12; i++) {
        data[i].pos = (HuVecF){ mtx[0][3], mtx[1][3], mtx[2][3] };
        PSMTXRotRad(rot, 'z', 0.017453292f * (60.0f + 90.0f * (i - 8)));
        PSMTXConcat(m, rot, rot);
        PSMTXMultVec(rot, &dir2, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 40.0f);
        data[i].color.a = 255;
        data[i].scale = 15.0f;
    }
}

/* 115 insns */
static void StarEffectDataUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;

    for (i = 0; i < num; i++) {
        data[i].pos.x += data[i].vel.x;
        data[i].pos.y += data[i].vel.y;
        data[i].pos.z += data[i].vel.z;
        PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
        data[i].scale *= 1.04f;
        if (data[i].scale > 80.0f) {
            data[i].scale = 80.0f;
        }
        data[i].color.a *= 0.95f;
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 652 insns */
void SdEffectDustCreateData(HuVecF pos, HU3DPARTICLEDATA *data, HU3DPARTICLEDATA *data2, float scale)
{
    HuVecF dir0 = { 0.0f, 5.0f, 1.0f };
    HuVecF dir1 = { 0.0f, 1.5f, 1.0f };
    HuVecF dir2 = { 0.0f, 1.0f, 1.5f };
    HuVecF dir3 = { 0.0f, 0.0f, 1.0f };
    HuVecF dir4 = { 0.0f, 0.15f, 1.0f };
    Mtx m;
    Mtx m2;
    Mtx rot;
    float size0;
    float size1;
    s32 i;

    PSMTXIdentity(m);
    PSMTXCopy(m, m2);
    m[0][3] = pos.x;
    m[1][3] = pos.y;
    m[2][3] = pos.z;
    PSVECNormalize(&dir0, &dir0);
    PSVECNormalize(&dir1, &dir1);
    PSVECNormalize(&dir2, &dir2);
    PSVECNormalize(&dir3, &dir3);
    PSVECNormalize(&dir4, &dir4);
    data->time = 1;
    for (i = 0; i < 48; i++) {
        data[i].parManId = 0;
        data[i].pos = (HuVecF){ m[0][3], m[1][3], m[2][3] };
        data[i].color.r = data[i].color.g = data[i].color.b = data[i].color.a = 255;
    }
    for (i = 0; i < 32; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (360.0f * i / 32.0f));
        PSMTXConcat(m2, rot, rot);
        PSMTXMultVec(rot, &dir4, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 40.0f * scale);
        if (i % 2 != 0) {
            size0 = 50.0f * scale;
        } else {
            size0 = 60.0f * scale;
        }
        data[i].scale = size0;
    }
    for (i = 32; i < 48; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (360.0f * i / 16.0f));
        PSMTXConcat(m2, rot, rot);
        PSMTXMultVec(rot, &dir0, &data[i].vel);
        PSVECScale(&data[i].vel, &data[i].vel, 40.0f * scale);
        if (i % 2 != 0) {
            size1 = 50.0f * scale;
        } else {
            size1 = 40.0f * scale;
        }
        data[i].scale = size1;
    }
    data2->time = 1;
    for (i = 0; i < 25; i++) {
        data2[i].parManId = 0;
        data2[i].pos = (HuVecF){ m[0][3], m[1][3], m[2][3] };
        data2[i].color.r = data2[i].color.g = data2[i].color.b = data2[i].color.a = 255;
    }
    for (i = 0; i < 1; i++) {
        data2[i].vel = (HuVecF){ 0.0f, 1.0f, 0.0f };
        PSVECScale(&data2[i].vel, &data2[i].vel, 15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 1; i < 4; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (120.0f * i));
        PSMTXMultVec(rot, &dir1, &data2[i].vel);
        PSVECScale(&data2[i].vel, &data2[i].vel, 15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 4; i < 9; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (72.0f * i));
        PSMTXMultVec(rot, &dir2, &data2[i].vel);
        PSVECScale(&data2[i].vel, &data2[i].vel, 15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 9; i < 16; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (51.5f * i));
        PSMTXMultVec(rot, &dir3, &data2[i].vel);
        PSVECScale(&data2[i].vel, &data2[i].vel, 15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 16; i < 21; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (72.0f * i));
        PSMTXMultVec(rot, &dir2, &data2[i].vel);
        PSVECScale(&data2[i].vel, &data2[i].vel, -15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 21; i < 24; i++) {
        PSMTXRotRad(rot, 'y', 0.017453292f * (120.0f * i));
        PSMTXMultVec(rot, &dir1, &data2[i].vel);
        PSVECScale(&data2[i].vel, &data2[i].vel, -15.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
    for (i = 24; i < 25; i++) {
        data2[i].vel = (HuVecF){ 0.0f, 1.0f, 0.0f };
        PSVECScale(&data2[i].vel, &data2[i].vel, -12.0f * scale);
        data2[i].scale = 100.0f * scale;
    }
}

/* 149 insns */
void SdEffectFlameUpdate(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;

    for (i = 0; i < num; i++) {
        if (data[i].scale != 0.0f) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            if (data->parManId % 2 != 0) {
                data[i].zRot += 45.0f;
            }
            data[i].scale *= 1.04f;
            if (data[i].scale > 320.0f) {
                data[i].scale = 320.0f;
            }
            data[i].color.a *= 0.9f;
            if (data[i].color.a < 2) {
                data[i].scale = 0.0f;
            }
        }
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 191 insns */
void SdEffectFlameUpdateData(HU3DPARTICLEDATA *data, s32 num)
{
    s32 i;

    for (i = 0; i < num; i++) {
        if (data[i].scale != 0.0f) {
            data[i].pos.x += data[i].vel.x;
            data[i].pos.y += data[i].vel.y;
            data[i].pos.z += data[i].vel.z;
            PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
            data[i].scale *= 1.05f;
            if (data[i].scale > 320.0f) {
                data[i].scale = 320.0f;
            }
            data[i].color.r *= 0.995f;
            data[i].color.g *= 0.98f;
            data[i].color.b *= 0.9f;
            data[i].color.a *= 0.92f;
            if (data[i].color.a < 2) {
                data[i].scale = 0.0f;
            }
        }
    }
    if (++data->parManId >= 60) {
        data->time = data->parManId = 0;
        for (i = 0; i < num; i++) {
            data[i].scale = 0.0f;
        }
    }
}

/* 0x1340: string literals */
/* 0x1350 */ static char *bulletObjTbl[13] = { "", "bul02", "", "", "bul05", "", "", "", "", "", "", "", "" };

/* 112 insns */
void SdBulletDraw(HU3DMODEL *model, Mtx *mtx)
{
    SDMACHINE *machine;
    SDBULLET *bullet;
    HU3DMODELID mdlId;
    Mtx m;
    HuVecF pos;
    s32 i;
    s32 j;
    s32 k;

    if (MgSeqModeGet() == 5) {
        Hu3DModelObjDrawInit();
        for (i = 0; i < 2; i++) {
            machine = &sys->machine[i];
            if (machine->gunNo == 4 || machine->gunNo == 1) {
                mdlId = machine->gun[0].bullet->mdlId[0];
                Hu3DModelAttrReset(mdlId, 1);
                for (j = 0; j < machine->gunNum; j++) {
                    for (k = 0; k < machine->bulletNum; k++) {
                        bullet = &machine->gun[j].bullet[k];
                        if (bullet->mode != 0) {
                            PSMTXTrans(m, bullet->pos.x, bullet->pos.y, bullet->pos.z);
                            PSMTXConcat(*mtx, m, m);
                            pos = (HuVecF){ m[0][3], m[1][3], m[2][3] };
                            PSMTXConcat(m, bullet->mtx, m);
                            m[0][3] = pos.x;
                            m[1][3] = pos.y;
                            m[2][3] = pos.z;
                            Hu3DModelObjDraw(mdlId, bulletObjTbl[machine->gunNo], m);
                        }
                    }
                }
                Hu3DModelAttrSet(mdlId, 1);
            }
        }
    }
}

