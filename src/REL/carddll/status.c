/*
 * carddll status.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/carddll/asm/REL/carddll/status.s.
 */

/* status calls Hu3D2Dto3D / Hu3D3Dto2D / Hu3DMtxRotGet unprototyped (an mr after these void calls): hide their
 * prototypes from CW only */
#ifdef __MWERKS__
#define Hu3D2Dto3D Hu3D2Dto3D_hidden
#define Hu3D3Dto2D Hu3D3Dto2D_hidden
#define Hu3DMtxRotGet Hu3DMtxRotGet_hidden
#endif
#include "REL/carddll.h"
#ifdef __MWERKS__
#undef Hu3D2Dto3D
#undef Hu3D3Dto2D
#undef Hu3DMtxRotGet
#endif

#ifndef __MWERKS__
#include "game/audio.h"
#else
#include "msm.h"
#endif
#include "game/esprite.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/frand.h"
#include "math.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x6C0 lbl_1_rodata_6C0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6CC lbl_1_rodata_6CC (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6D8 lbl_1_rodata_6D8 (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6E4 lbl_1_rodata_6E4 (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6F0 lbl_1_rodata_6F0 (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x6FC lbl_1_rodata_6FC (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x708 lbl_1_rodata_708 (0xC): 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x714 lbl_1_rodata_714 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_720 = -90.0f; /* 0x720 */
static const float lbl_1_rodata_724 = 0.0f; /* 0x724 */
static const float lbl_1_rodata_728 = 1.0f; /* 0x728 */
static const float lbl_1_rodata_72C = 4.0f; /* 0x72C */
static const float lbl_1_rodata_730 = 12.0f; /* 0x730 */
static const float lbl_1_rodata_734 = 360.0f; /* 0x734 */
static const float lbl_1_rodata_738 = 100.0f; /* 0x738 */
static const float lbl_1_rodata_73C = 6.0f; /* 0x73C */
static const float lbl_1_rodata_740 = 8.0f; /* 0x740 */
static const float lbl_1_rodata_744 = 0.5f; /* 0x744 */
static const float lbl_1_rodata_748 = 30.0f; /* 0x748 */
static const float lbl_1_rodata_74C = 1.5f; /* 0x74C */
static const float lbl_1_rodata_750 = 7.0f; /* 0x750 */
static const float lbl_1_rodata_754 = 10.0f; /* 0x754 */
static const float lbl_1_rodata_758 = 5.5f; /* 0x758 */
static const float lbl_1_rodata_75C = 60.0f; /* 0x75C */
static const float lbl_1_rodata_760 = 0.2f; /* 0x760 */
static const double lbl_1_rodata_768 = 3.141592653589793; /* 0x768 */
static const float lbl_1_rodata_770 = 90.0f; /* 0x770 */
static const double lbl_1_rodata_778 = 180.0; /* 0x778 */
/* 0x780 lbl_1_rodata_780 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x788 lbl_1_rodata_788 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x790 lbl_1_rodata_790 (0xC): 0x3E774BC6 0x3DFEF9DA 0x3E774BC6 -- an aggregate initialiser, write it as a local */
/* 0x79C lbl_1_rodata_79C (0xC): 0x00000000 0x00000002 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x7A8 lbl_1_rodata_7A8 (0xC): 0x42A00000 0x43BE0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7B4 lbl_1_rodata_7B4 (0xC): 0x438C0000 0x43700000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7C0 lbl_1_rodata_7C0 (0xC): 0x42A00000 0x43BE0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7CC lbl_1_rodata_7CC (0xC): 0x438C0000 0x43700000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7D8 lbl_1_rodata_7D8 (0xC): 0x42700000 0x43B40000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7E4 lbl_1_rodata_7E4 (0xC): 0x43820000 0x435C0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7F0 lbl_1_rodata_7F0 (0xC): 0x42700000 0x43B40000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x7FC lbl_1_rodata_7FC (0xC): 0x43820000 0x435C0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x808 lbl_1_rodata_808 (0xC): 0x42C80000 0x43C80000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x814 lbl_1_rodata_814 (0xC): 0x43960000 0x43820000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x820 lbl_1_rodata_820 (0xC): 0x42C80000 0x43C80000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x82C lbl_1_rodata_82C (0xC): 0x43960000 0x43820000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x838 lbl_1_rodata_838 (0xC): 0x42700000 0x43B40000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x844 lbl_1_rodata_844 (0xC): 0x43820000 0x435C0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x850 lbl_1_rodata_850 (0xC): 0x42700000 0x43B40000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x85C lbl_1_rodata_85C (0xC): 0x43820000 0x435C0000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x868 lbl_1_rodata_868 (0xC): 0x42C80000 0x43C80000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x874 lbl_1_rodata_874 (0xC): 0x43960000 0x43820000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x880 lbl_1_rodata_880 (0xC): 0x42C80000 0x43C80000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x88C lbl_1_rodata_88C (0xC): 0x43960000 0x43820000 0x43FA0000 -- an aggregate initialiser, write it as a local */
/* 0x898 lbl_1_rodata_898 (0xC): 0x43070000 0x43B18000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x8A4 lbl_1_rodata_8A4 (0xC): 0x43A78000 0x43570000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x8B0 lbl_1_rodata_8B0 (0xC): 0x43070000 0x43B18000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x8BC lbl_1_rodata_8BC (0xC): 0x43A78000 0x43570000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x8C8 lbl_1_rodata_8C8 (0xC): 0x00000000 0x00000000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x8D4 lbl_1_rodata_8D4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8E0 lbl_1_rodata_8E0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8EC lbl_1_rodata_8EC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x8F8 lbl_1_rodata_8F8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x904 lbl_1_rodata_904 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x910 lbl_1_rodata_910 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x91C lbl_1_rodata_91C (0xC): 0x43820000 0x43570000 0x44610000 -- an aggregate initialiser, write it as a local */
/* 0x928 lbl_1_rodata_928 (0xC): 0x43960000 0x437F0000 0x43E10000 -- an aggregate initialiser, write it as a local */
/* 0x934 lbl_1_rodata_934 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x940 lbl_1_rodata_940 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x94C lbl_1_rodata_94C (0xC): 0x42A00000 0x43BE0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x958 lbl_1_rodata_958 (0xC): 0x438F0000 0x436E0000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x964 lbl_1_rodata_964 (0xC): 0x43520000 0x42B40000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x970 lbl_1_rodata_970 (0xC): 0x43520000 0x42B40000 0x442F0000 -- an aggregate initialiser, write it as a local */
/* 0x97C lbl_1_rodata_97C (0xC): 0x3F19999A 0x3F19999A 0x3F19999A -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_988 = -50.0f; /* 0x988 */
static const float lbl_1_rodata_98C = -1.0f; /* 0x98C */
static const float lbl_1_rodata_990 = 1000.0f; /* 0x990 */
static const float lbl_1_rodata_994 = 2.0f; /* 0x994 */
static const float lbl_1_rodata_998 = 50.0f; /* 0x998 */
static const float lbl_1_rodata_99C = 286.0f; /* 0x99C */
static const float lbl_1_rodata_9A0 = 238.0f; /* 0x9A0 */
static const float lbl_1_rodata_9A4 = 0.6f; /* 0x9A4 */
static const float lbl_1_rodata_9A8 = 200.0f; /* 0x9A8 */
static const float lbl_1_rodata_9AC = 24.0f; /* 0x9AC */
/* 0x9B0 lbl_1_rodata_9B0 (0x4): 0x41900000 -- an aggregate initialiser, write it as a local */
/* 0x9B4 lbl_1_rodata_9B4 (0x48): 0x42B40000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x42B40000 0x00000000 0x00000000 0xC2B40000 0x00000000 0x00000000 0x43340000 0xC2B40000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x9FC lbl_1_rodata_9FC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA08 lbl_1_rodata_A08 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA14 lbl_1_rodata_A14 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA20 lbl_1_rodata_A20 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_A2C = 84.0f; /* 0xA2C */
static const float lbl_1_rodata_A30 = 47.0f; /* 0xA30 */
static const float lbl_1_rodata_A34 = 0.7f; /* 0xA34 */
static const float lbl_1_rodata_A38 = 67.0f; /* 0xA38 */
static const float lbl_1_rodata_A3C = 0.25f; /* 0xA3C */
static const float lbl_1_rodata_A40 = 20.0f; /* 0xA40 */
static const float lbl_1_rodata_A44 = 77.0f; /* 0xA44 */
static const float lbl_1_rodata_A48 = 0.85f; /* 0xA48 */
static const float lbl_1_rodata_A4C = 0.1f; /* 0xA4C */
static const float lbl_1_rodata_A50 = 0.9f; /* 0xA50 */
static const float lbl_1_rodata_A54 = 0.075f; /* 0xA54 */
static const float lbl_1_rodata_A58 = 0.95000005f; /* 0xA58 */
static const float lbl_1_rodata_A5C = 0.049999952f; /* 0xA5C */
static const float lbl_1_rodata_A60 = 0.97499996f; /* 0xA60 */
static const float lbl_1_rodata_A64 = 0.025000036f; /* 0xA64 */
static const float lbl_1_rodata_A68 = -900.0f; /* 0xA68 */
static const float lbl_1_rodata_A6C = 500.0f; /* 0xA6C */
static const float lbl_1_rodata_A70 = 150.0f; /* 0xA70 */
static const float lbl_1_rodata_A74 = 0.017453292f; /* 0xA74 */
static const float lbl_1_rodata_A78 = -45.0f; /* 0xA78 */
/* 0xA7C lbl_1_rodata_A7C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA88 lbl_1_rodata_A88 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xA94 lbl_1_rodata_A94 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAA0 lbl_1_rodata_AA0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAAC lbl_1_rodata_AAC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_AB8 = 0.0625f; /* 0xAB8 */
static const float lbl_1_rodata_ABC = 0.0375f; /* 0xABC */
static const float lbl_1_rodata_AC0 = 1400.0f; /* 0xAC0 */
static const float lbl_1_rodata_AC4 = 0.0015f; /* 0xAC4 */
static const float lbl_1_rodata_AC8 = 180.0f; /* 0xAC8 */
static const float lbl_1_rodata_ACC = 85.0f; /* 0xACC */
/* 0xAD0 lbl_1_rodata_AD0 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_ADC = 40.0f; /* 0xADC */
static const float lbl_1_rodata_AE0 = 115.0f; /* 0xAE0 */
static const float lbl_1_rodata_AE4 = 118.0f; /* 0xAE4 */
static const float lbl_1_rodata_AE8 = 0.38f; /* 0xAE8 */
/* 0xAEC lbl_1_rodata_AEC (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xAF8 lbl_1_rodata_AF8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB04 lbl_1_rodata_B04 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B10 = 420.0f; /* 0xB10 */
static const float lbl_1_rodata_B14 = 120.0f; /* 0xB14 */
static const float lbl_1_rodata_B18 = 26.0f; /* 0xB18 */
static const float lbl_1_rodata_B1C = 3.0f; /* 0xB1C */
/* 0xB20 lbl_1_rodata_B20 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB2C lbl_1_rodata_B2C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB38 lbl_1_rodata_B38 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB44 lbl_1_rodata_B44 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB50 lbl_1_rodata_B50 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B5C = 25.0f; /* 0xB5C */
static const float lbl_1_rodata_B60 = 0.001f; /* 0xB60 */
/* 0xB64 lbl_1_rodata_B64 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB70 lbl_1_rodata_B70 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xB7C lbl_1_rodata_B7C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB88 lbl_1_rodata_B88 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB94 lbl_1_rodata_B94 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBA0 lbl_1_rodata_BA0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBAC lbl_1_rodata_BAC (0xC): 0x00000000 0x00000000 0xC2480000 -- an aggregate initialiser, write it as a local */
/* 0xBB8 lbl_1_rodata_BB8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBC4 lbl_1_rodata_BC4 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xBD0 lbl_1_rodata_BD0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBDC lbl_1_rodata_BDC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBE8 lbl_1_rodata_BE8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xBF4 lbl_1_rodata_BF4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC00 lbl_1_rodata_C00 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC0C lbl_1_rodata_C0C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC18 lbl_1_rodata_C18 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC24 lbl_1_rodata_C24 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC30 lbl_1_rodata_C30 (0xC): 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xC3C lbl_1_rodata_C3C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_C48 = 0.3f; /* 0xC48 */
static const float lbl_1_rodata_C4C = 140.0f; /* 0xC4C */
static const float lbl_1_rodata_C50 = 0.035f; /* 0xC50 */
static const float lbl_1_rodata_C54 = 5.0f; /* 0xC54 */
static const float lbl_1_rodata_C58 = 0.002f; /* 0xC58 */
static const float lbl_1_rodata_C5C = -0.06f; /* 0xC5C */
static const float lbl_1_rodata_C60 = 17.0f; /* 0xC60 */
static const float lbl_1_rodata_C64 = 255.0f; /* 0xC64 */
static const float lbl_1_rodata_C68 = 64.0f; /* 0xC68 */
static const float lbl_1_rodata_C6C = 0.75f; /* 0xC6C */
/* 0xC70 lbl_1_rodata_C70 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC7C lbl_1_rodata_C7C (0xC): 0x00000000 0x00000000 0xBF800000 -- an aggregate initialiser, write it as a local */
/* 0xC88 lbl_1_rodata_C88 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_C94 = 130.0f; /* 0xC94 */
static const float lbl_1_rodata_C98 = -140.0f; /* 0xC98 */
static const float lbl_1_rodata_C9C = 45.0f; /* 0xC9C */
static const float lbl_1_rodata_CA0 = -75.0f; /* 0xCA0 */
static const float lbl_1_rodata_CA4 = 0.016666668f; /* 0xCA4 */
static const double lbl_1_rodata_CA8 = 90.0; /* 0xCA8 */
/* 0xCB0 lbl_1_rodata_CB0 (0xC): 0xC2960000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xCBC lbl_1_rodata_CBC (0xC): 0xC2F00000 0x430C0000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_CC8 = 400.0f; /* 0xCC8 */
static const float lbl_1_rodata_CCC = 250.0f; /* 0xCCC */
static const float lbl_1_rodata_CD0 = 300.0f; /* 0xCD0 */
/* 0xCD4 lbl_1_rodata_CD4 (0xC): 0xC2960000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_CE0 = 136.0f; /* 0xCE0 */
/* 0xCE4 lbl_1_rodata_CE4 (0x28): 0x00000003 0x00000004 0x00000003 0x00000000 0x00000002 0x00000003 0x00000002 0x00000000 0x00000001 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_D0C = 210.0f; /* 0xD0C */
static const float lbl_1_rodata_D10 = 0.05f; /* 0xD10 */
/* 0xD14 lbl_1_rodata_D14 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD20 lbl_1_rodata_D20 (0xC): 0x00000000 0x43480000 0xC3160000 -- an aggregate initialiser, write it as a local */
/* 0xD2C lbl_1_rodata_D2C (0xC): 0x3F000000 0x3F000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD38 lbl_1_rodata_D38 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD44 lbl_1_rodata_D44 (0xC): 0x3F000000 0x3F000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD50 lbl_1_rodata_D50 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD5C lbl_1_rodata_D5C (0xC): 0x3F000000 0x3F000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD68 lbl_1_rodata_D68 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD74 lbl_1_rodata_D74 (0xC): 0x3F000000 0x3F000000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0xD80 lbl_1_rodata_D80 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_D8C = 0.4f; /* 0xD8C */
/* 0xD90 lbl_1_rodata_D90 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD9C lbl_1_rodata_D9C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xDA8 lbl_1_rodata_DA8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xDB4 lbl_1_rodata_DB4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_DC0 = 170.0f; /* 0xDC0 */
/* 0xDC4 lbl_1_rodata_DC4 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_DC8 = -0.02f; /* 0xDC8 */
static const float lbl_1_rodata_DCC = 1.2f; /* 0xDCC */
static const float lbl_1_rodata_DD0 = -0.5f; /* 0xDD0 */
static const float lbl_1_rodata_DD4 = 0.8f; /* 0xDD4 */
/* 0xDD8 lbl_1_rodata_DD8 (0x10): 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_DE8 = 1.0; /* 0xDE8 */
static const double lbl_1_rodata_DF0 = 0.5; /* 0xDF0 */
static const double lbl_1_rodata_DF8 = 2.0; /* 0xDF8 */
static const float lbl_1_rodata_E00 = 448.0f; /* 0xE00 */
static const float lbl_1_rodata_E04 = 94.0f; /* 0xE04 */
static const float lbl_1_rodata_E08 = 340.0f; /* 0xE08 */
static const float lbl_1_rodata_E0C = 48.0f; /* 0xE0C */
static const float lbl_1_rodata_E10 = -10000.0f; /* 0xE10 */
static const float lbl_1_rodata_E14 = 432.0f; /* 0xE14 */
static const float lbl_1_rodata_E18 = 305.0f; /* 0xE18 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x21D8 */ CardStatus21D8 lbl_1_bss_21D8;
/* 0x2034 */ CardStatus2034 lbl_1_bss_2034;
/* 0x201C */ CardStatusMdl lbl_1_bss_201C[1];
/* 0x1FD4 */ CardStatusMdl lbl_1_bss_1FD4[3];
/* 0x1FBC */ CardStatusMdl lbl_1_bss_1FBC[1];
/* 0x1FA4 */ CardStatusMdl lbl_1_bss_1FA4[1];
/* 0x1F44 */ CardStatusMdl lbl_1_bss_1F44[4];
/* 0x1F2C */ CardStatusMdl lbl_1_bss_1F2C[1];
/* 0x1F14 */ CardStatusMdl lbl_1_bss_1F14[1];
/* 0x1EFC */ CardStatusMdl lbl_1_bss_1EFC[1];
/* 0x1ECC */ CardStatusMdl lbl_1_bss_1ECC[2];
/* 0x1E9C */ CardStatusMdl lbl_1_bss_1E9C[2];
/* 0x1E6C */ CardStatusMdl lbl_1_bss_1E6C[2];
/* 0x1E54 */ CardStatusMdl lbl_1_bss_1E54[1];
/* 0x1E3C */ CardStatusMdl lbl_1_bss_1E3C[1];
/* 0x1E24 */ CardStatusMdl lbl_1_bss_1E24[1];
/* 0x1E0C */ CardStatusMdl lbl_1_bss_1E0C[1];
/* 0x1B3C */ CardStatusMdl lbl_1_bss_1B3C[30];
/* 0x1AF4 */ CardStatusMdl lbl_1_bss_1AF4[3];
/* 0x1A7C */ CardStatusMdl lbl_1_bss_1A7C[5];
/* 0x1A1C */ CardStatusMdl lbl_1_bss_1A1C[4];
/* 0x1A04 */ CardStatusMdl lbl_1_bss_1A04[1];
/* 0x19EC */ CardStatusMdl lbl_1_bss_19EC[1];
/* 0x19D4 */ CardStatusMdl lbl_1_bss_19D4[1];
/* 0x19BC */ CardStatusMdl lbl_1_bss_19BC[1];
/* 0x19A4 */ CardStatusMdl lbl_1_bss_19A4[1];
/* 0x198C */ CardStatusMdl lbl_1_bss_198C[1];
/* 0x1974 */ CardStatusMdl lbl_1_bss_1974[1];
/* 0x1944 */ CardStatus1944 lbl_1_bss_1944;
/* 0x18DC */ CardStatus18DC lbl_1_bss_18DC;
/* 0x1848 */ CardStatus1848 lbl_1_bss_1848;
/* 0x17AC */ CardStatus17AC lbl_1_bss_17AC;
/* 0x12FC */ CardStatus12FC lbl_1_bss_12FC[30];
/* 0x12A8 */ CardStatus12A8 lbl_1_bss_12A8;

/* --- functions (reference order), .data placed before its first user --- */
/* 0x810 */ HuVecF lbl_1_data_810[3] = { { 500.0f, 1000.0f, 500.0f }, { -800.0f, 400.0f, 800.0f }, { 300.0f, 800.0f, -1200.0f } };

/* 2478 insns */
s32 fn_1_36C00(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 i;
    s32 type;
    s32 num;
    s32 ret;
    s32 rnd;
    float t;
    float x;
    float y;
    HuVecF pos;

    ret = 0;
    type = 0;
    player = &work->player[work->unk174[work->unk170]];
    num = 1;
    if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x1000) {
        type = 0;
    }
    else if (lbl_1_bss_8C4[player->unk10][player->unk14] & 0x2000) {
        type = 1;
        num = 2;
    }
    else {
        type = 2;
    }
    switch (lbl_1_bss_1168[1]) {
        case 0:
            memset(&lbl_1_bss_21D8, 0, sizeof(lbl_1_bss_21D8));
            Hu3DCamera[1] = Hu3DCamera[0];
            lbl_1_bss_21D8.unk8 = 9;
            if (type == 0) {
                lbl_1_bss_21D8.mdl[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[78], HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_21D8.mdl[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[79], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            else if (type == 1) {
                lbl_1_bss_21D8.mdl[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[78], HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_21D8.mdl[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[78], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            else {
                lbl_1_bss_21D8.unk8 = 10;
                lbl_1_bss_21D8.mdl[0] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[79], HU_MEMNUM_OVL, HEAP_MODEL));
                lbl_1_bss_21D8.mdl[1] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[78], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            fn_1_9C74(&pos, player->unk10, player->unk14, 1, 1);
            for (i = 0; i < 2; i++) {
                Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[i], &pos);
                Hu3DModelRotSet(lbl_1_bss_21D8.mdl[i], -90.0f, 0.0f, 0.0f);
                Hu3DModelCameraSet(lbl_1_bss_21D8.mdl[i], 2);
                Hu3DModelLayerSet(lbl_1_bss_21D8.mdl[i], 7);
                Hu3DModelAttrSet(lbl_1_bss_21D8.mdl[i], 1);
            }
            lbl_1_bss_21D8.unk10 = Hu3DData[lbl_1_bss_478[player->unk10][player->unk14]].pos;
            lbl_1_bss_21D8.unk1C = Hu3DData[lbl_1_bss_478[player->unk10][player->unk14]].rot;
            lbl_1_bss_21D8.unkC = lbl_1_bss_21D8.unk10.y;
            lbl_1_bss_21D8.unk44 = lbl_1_bss_21D8.unk48 = 1.0f;
            lbl_1_bss_1168[1]++;
            break;
        case 1:
            lbl_1_bss_21D8.unk10.y += 4.0f;
            Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_21D8.unk10);
            lbl_1_bss_21D8.unk1C.y -= 12.0f;
            if (lbl_1_bss_21D8.unk1C.y < 0.0f) {
                lbl_1_bss_21D8.unk1C.y += 360.0f;
            }
            if (++lbl_1_bss_21D8.unk4 >= 60) {
                lbl_1_bss_21D8.unk1C.y = 0.0f;
                for (i = 0; i < num; i++) {
                    lbl_1_bss_21D8.unk28[i] = (HuVecF) { lbl_1_bss_21D8.unk10.x, 100.0f + lbl_1_bss_21D8.unk10.y, lbl_1_bss_21D8.unk10.z };
                    lbl_1_bss_21D8.unk28[i].x += 6.0f;
                    lbl_1_bss_21D8.unk28[i].z += 8.0f;
                    fn_1_3ED3C(lbl_1_bss_21D8.unk8, lbl_1_bss_21D8.unk28[i]);
                    fn_1_3F498(lbl_1_bss_21D8.unk8, i, (HuVecF) { -90.0f, 0.0f, 0.0f });
                }
                lbl_1_bss_21D8.unk4 = 0;
                lbl_1_bss_1168[1]++;
                fn_1_8D04((type != 2) ? 0x44C : 0x44D, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            Hu3DModelRotSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_21D8.unk1C);
            break;
        case 2:
            if (num == 2) {
                lbl_1_bss_21D8.unk28[0].x -= 1.0f;
                lbl_1_bss_21D8.unk28[1].x += 1.0f;
                fn_1_3F3D8(lbl_1_bss_21D8.unk8, 0, lbl_1_bss_21D8.unk28[0]);
                fn_1_3F3D8(lbl_1_bss_21D8.unk8, 1, lbl_1_bss_21D8.unk28[1]);
            }
            if (++lbl_1_bss_21D8.unk4 > 55) {
                for (i = 0; i < num; i++) {
                    Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[i], &lbl_1_bss_21D8.unk28[i]);
                    Hu3DModelAttrReset(lbl_1_bss_21D8.mdl[i], 1);
                }
                lbl_1_bss_21D8.unk4 = 0;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 3:
            if (++lbl_1_bss_21D8.unk4 < 40 && num == 2) {
                lbl_1_bss_21D8.unk28[0].x -= 1.0f;
                lbl_1_bss_21D8.unk28[1].x += 1.0f;
                Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[0], &lbl_1_bss_21D8.unk28[0]);
                Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[1], &lbl_1_bss_21D8.unk28[1]);
                fn_1_3F3D8(lbl_1_bss_21D8.unk8, 0, lbl_1_bss_21D8.unk28[0]);
                fn_1_3F3D8(lbl_1_bss_21D8.unk8, 1, lbl_1_bss_21D8.unk28[1]);
            }
            if (fn_1_3F714(lbl_1_bss_21D8.unk8, 0)) {
                lbl_1_bss_21D8.unk50 = 1;
                lbl_1_bss_21D8.unk4 = 0;
                if (type != 1) {
                    rnd = frandmod(128);
                    if (rnd < 2) {
                        lbl_1_bss_1168[1]++;
                        if (type == 0) {
                            lbl_1_bss_21D8.unk4C = 11;
                            lbl_1_bss_21D8.unk50 = 2;
                        }
                        else if (rnd == 0) {
                            lbl_1_bss_21D8.unk4C = 13;
                            lbl_1_bss_21D8.unk50 = 0;
                        }
                        else {
                            lbl_1_bss_21D8.unk4C = 14;
                            lbl_1_bss_21D8.unk50 = 2;
                        }
                        break;
                    }
                    lbl_1_bss_21D8.unk50 = type;
                }
                lbl_1_bss_21D8.unk4 = 0;
                lbl_1_bss_1168[1] = 10;
            }
            break;
        case 4:
            if (++lbl_1_bss_21D8.unk4 > 30) {
                Hu3DModelAttrSet(lbl_1_bss_21D8.mdl[0], 1);
                fn_1_3ED3C(lbl_1_bss_21D8.unk4C, lbl_1_bss_21D8.unk28[0]);
                fn_1_3F498(lbl_1_bss_21D8.unk4C, 0, (HuVecF) { -90.0f, 0.0f, 0.0f });
                lbl_1_bss_21D8.unk4 = 0;
                lbl_1_bss_1168[1]++;
                if (lbl_1_bss_21D8.unk50 == 2) {
                    omVibrate(work->unk174[work->unk170], 50, 6, 6);
                    if (lbl_1_bss_21D8.unk4C == 11) {
                        fn_1_8D04(0x41E, lbl_1_bss_478[player->unk10][player->unk14], 1);
                    }
                }
            }
            break;
        case 5:
            if (lbl_1_bss_21D8.unk50 == 0) {
                if (lbl_1_bss_21D8.unk4 == 0) {
                    omVibrate(work->unk174[work->unk170], 80, 6, 6);
                }
                if (lbl_1_bss_21D8.unk4 == 80) {
                    omVibrate(work->unk174[work->unk170], 160, 4, 2);
                }
                if (lbl_1_bss_21D8.unk4 == 40) {
                    fn_1_8D04(0x420, lbl_1_bss_478[player->unk10][player->unk14], 1);
                }
            }
            if (lbl_1_bss_21D8.unk4C == 14) {
                if (lbl_1_bss_21D8.unk4 == 40) {
                    omVibrate(work->unk174[work->unk170], 25, 4, 2);
                }
                if (lbl_1_bss_21D8.unk4 == 65) {
                    omVibrate(work->unk174[work->unk170], 40, 6, 6);
                }
                if (lbl_1_bss_21D8.unk4 == 38) {
                    fn_1_8D04(0x421, lbl_1_bss_478[player->unk10][player->unk14], 1);
                }
            }
            lbl_1_bss_21D8.unk4++;
            if (lbl_1_bss_21D8.unk4 == 80 && lbl_1_bss_21D8.unk4C == 13) {
                lbl_1_bss_21D8.unk8 = 9;
                fn_1_3ED3C(lbl_1_bss_21D8.unk8, lbl_1_bss_21D8.unk28[0]);
                fn_1_3F498(lbl_1_bss_21D8.unk8, 0, (HuVecF) { -90.0f, 0.0f, 0.0f });
                fn_1_8D04(0x44C, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            if (fn_1_3F714(lbl_1_bss_21D8.unk4C, 0)) {
                lbl_1_bss_21D8.unk4 = 0;
                fn_1_3F278(lbl_1_bss_21D8.unk4C, 0);
                if (lbl_1_bss_21D8.unk4C == 11) {
                    fn_1_3ED3C(12, lbl_1_bss_21D8.unk28[0]);
                    fn_1_3F498(12, 0, (HuVecF) { -90.0f, 0.0f, 0.0f });
                    lbl_1_bss_21D8.unk4 = 0;
                    lbl_1_bss_21D8.unk8 = 10;
                    lbl_1_bss_21D8.unk94 = Hu3DCamera[0].pos;
                    lbl_1_bss_21D8.unkA0 = Hu3DCamera[0].target;
                    lbl_1_bss_21D8.unk54 = 0;
                    lbl_1_bss_1168[1]++;
                    break;
                }
                if (lbl_1_bss_21D8.unk4C == 13) {
                    Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[1], &lbl_1_bss_21D8.unk28[0]);
                    Hu3DModelAttrReset(lbl_1_bss_21D8.mdl[1], 1);
                    lbl_1_bss_1168[1] = 7;
                }
                else {
                    Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[0], &lbl_1_bss_21D8.unk28[0]);
                    Hu3DModelAttrReset(lbl_1_bss_21D8.mdl[0], 1);
                    lbl_1_bss_1168[1] = 10;
                }
                lbl_1_bss_21D8.unk4 = 0;
            }
            break;
        case 6:
            if (lbl_1_bss_21D8.unk4 == 15) {
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
                fn_1_8D04(0x41F, lbl_1_bss_21D8.mdl[1], 2);
            }
            if (++lbl_1_bss_21D8.unk4 >= 30) {
                if (lbl_1_bss_21D8.unk54 < 4) {
                    fn_1_3F278(12, 0);
                    fn_1_3ED3C(12, lbl_1_bss_21D8.unk28[0]);
                    fn_1_3F498(12, 0, (HuVecF) { -90.0f, 0.0f, 0.0f });
                    if (lbl_1_bss_21D8.unk54 < 3) {
                        lbl_1_bss_21D8.unk4 = 0;
                        Hu3DCamera[0].target = lbl_1_bss_21D8.unk28[0];
                        PSVECAdd(&lbl_1_data_810[lbl_1_bss_21D8.unk54], &Hu3DCamera[0].target, &Hu3DCamera[0].pos);
                    }
                    else {
                        Hu3DCamera[0].pos = lbl_1_bss_21D8.unk94;
                        Hu3DCamera[0].target = lbl_1_bss_21D8.unkA0;
                    }
                    lbl_1_bss_21D8.unk54++;
                }
                else {
                    if (lbl_1_bss_21D8.unk4 == 45) {
                        fn_1_3ED3C(lbl_1_bss_21D8.unk8, lbl_1_bss_21D8.unk28[0]);
                        fn_1_3F498(lbl_1_bss_21D8.unk8, 0, (HuVecF) { -90.0f, 0.0f, 0.0f });
                        omVibrate(work->unk174[work->unk170], 170, 4, 2);
                        fn_1_8D04(0x41F, lbl_1_bss_21D8.mdl[1], 2);
                        fn_1_8D04(0x44D, lbl_1_bss_478[player->unk10][player->unk14], 1);
                    }
                    if (fn_1_3F714(12, 0)) {
                        fn_1_3F278(12, 0);
                        Hu3DModelPosSetV(lbl_1_bss_21D8.mdl[1], &lbl_1_bss_21D8.unk28[0]);
                        Hu3DModelAttrReset(lbl_1_bss_21D8.mdl[1], 1);
                        lbl_1_bss_21D8.unk4 = 0;
                        lbl_1_bss_1168[1] = 7;
                    }
                }
            }
            break;
        case 7:
            if (fn_1_3F714(lbl_1_bss_21D8.unk8, 0)) {
                lbl_1_bss_21D8.unk4 = 0;
                lbl_1_bss_1168[1] = 8;
            }
            break;
        case 8:
            if (++lbl_1_bss_21D8.unk4 >= 30) {
                if (lbl_1_bss_21D8.unk4 == 30) {
                    fn_1_8D04((lbl_1_bss_21D8.unk4C == 13) ? 0x44E : 0x455, lbl_1_bss_478[player->unk10][player->unk14], 1);
                }
                t = 0.5f * fn_1_4EEA0(2, (lbl_1_bss_21D8.unk4 - 30) / 30.0f);
                for (i = 0; i < 2; i++) {
                    Hu3DModelScaleSet(lbl_1_bss_21D8.mdl[i], 1.0f + t, 1.0f + t, 1.0f + t);
                }
                if (lbl_1_bss_21D8.unk4 >= 90) {
                    lbl_1_bss_21D8.unk48 = 1.5f;
                    lbl_1_bss_21D8.unk4 = 0;
                    lbl_1_bss_1168[1] = 10;
                }
            }
            break;
        case 9:
            break;
        case 10: {
            lbl_1_bss_21D8.unk88 = (HuVecF) { ((HuVec2f *)lbl_1_data_528)[work->unk170].x - 7.0f, ((HuVec2f *)lbl_1_data_528)[work->unk170].y - 12.0f, 0.0f };
            for (i = 0; i < 2; i++) {
                lbl_1_bss_21D8.unk58[i] = Hu3DData[lbl_1_bss_21D8.mdl[i]].pos;
                Hu3D3Dto2D(&Hu3DData[lbl_1_bss_21D8.mdl[i]].pos, 1, &lbl_1_bss_21D8.unk70[i]);
            }
            lbl_1_bss_1168[1]++;
            fn_1_8D04(0x353, lbl_1_bss_21D8.mdl[0], 1);
            break;
        }
        case 11:
            fn_1_8D04(0x8353, lbl_1_bss_21D8.mdl[0], 1);
            lbl_1_bss_21D8.unk40 -= 10.0f + 5.5f * fn_1_4EEA0(0, lbl_1_bss_21D8.unk4 / 60.0f);
            lbl_1_bss_21D8.unk44 = lbl_1_bss_21D8.unk48 - (lbl_1_bss_21D8.unk48 - 0.2f) * fn_1_4EEA0(0, lbl_1_bss_21D8.unk4 / 60.0f);
            for (i = 0; i < 2; i++) {
                Hu3DModelRotSet(lbl_1_bss_21D8.mdl[i], -90.0f, lbl_1_bss_21D8.unk40, 0.0f);
                Hu3DModelScaleSet(lbl_1_bss_21D8.mdl[i], lbl_1_bss_21D8.unk44, lbl_1_bss_21D8.unk44, lbl_1_bss_21D8.unk44);
                t = HuCos(90.0f * (lbl_1_bss_21D8.unk4 / 60.0f));
                x = lbl_1_bss_21D8.unk70[i].x;
                x += (1.0f - t) * (lbl_1_bss_21D8.unk88.x - lbl_1_bss_21D8.unk70[i].x);
                t = HuSin(90.0f * (lbl_1_bss_21D8.unk4 / 60.0f));
                y = lbl_1_bss_21D8.unk70[i].y;
                y += t * (lbl_1_bss_21D8.unk88.y - lbl_1_bss_21D8.unk70[i].y);
                Hu3DData[lbl_1_bss_21D8.mdl[i]].pos = fn_1_4EDB8(lbl_1_bss_21D8.unk58[i], x, y);
            }
            if (++lbl_1_bss_21D8.unk4 > 60) {
                Hu3DModelAttrSet(lbl_1_bss_21D8.mdl[0], 1);
                Hu3DModelAttrSet(lbl_1_bss_21D8.mdl[1], 1);
                (&player->unk40)[lbl_1_bss_21D8.unk50 + 1]++;
                player->unk40 = player->unk44 + player->unk48 * 2 + player->unk4C * -1;
                lbl_1_bss_1168[2] = 0;
                lbl_1_bss_1168[1]++;
                fn_1_2FFAC(work);
                if (lbl_1_bss_21D8.unk50 != 2) {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][0], 0.0f, 10.0f, 0);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x1F6;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1E2;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x25A;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2AA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x282;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1BA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x296;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][1], 0.0f, 10.0f, 0);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x200;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1EC;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x264;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2B4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x28C;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1C4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x2A0;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                HuAudFXPlay(8);
                if (lbl_1_bss_21D8.unk50 == 1) {
                    lbl_1_bss_21D8.unk4 = 0;
                }
            }
            if (lbl_1_bss_21D8.unk4 == 58) {
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
            }
            break;
        case 12:
            fn_1_1328C(lbl_1_bss_21D8.unk50);
            if (lbl_1_bss_21D8.unk50 == 1) {
                if (++lbl_1_bss_21D8.unk4 == 20) {
                    HuAudFXPlay(8);
                }
                if (lbl_1_bss_21D8.unk4 >= 20 && lbl_1_bss_1168[2] == 2) {
                    lbl_1_bss_1168[1]++;
                }
            }
            else if (lbl_1_bss_1168[2] == 2) {
                lbl_1_bss_1168[1]++;
            }
            break;
        case 13:
            if (Hu3DMotionEndCheck(lbl_1_bss_468[work->unk174[work->unk170]])) {
                lbl_1_bss_1168[1]++;
            }
            break;
        case 14:
            lbl_1_bss_12A8.unk28 = 60;
            lbl_1_bss_12A8.unk8[0] = fn_1_502DC(player->unk2C);
            if (lbl_1_bss_21D8.unk4C == 11) {
                fn_1_4FBC8(work, 0x27);
            }
            else if (lbl_1_bss_21D8.unk4C == 13) {
                fn_1_4FBC8(work, 0x26);
            }
            else {
                fn_1_4FBC8(work, lbl_1_bss_21D8.unk50 + 0x1A);
            }
            lbl_1_bss_1168[2]++;
            lbl_1_bss_1168[1]++;
            break;
        case 15:
        case 16:
            if (lbl_1_bss_1168[1] == 15 && fn_1_1328C(lbl_1_bss_21D8.unk50)) {
                lbl_1_bss_1168[1] = 16;
            }
            lbl_1_bss_21D8.unk10.y -= 8.0f;
            Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_21D8.unk10);
            if (lbl_1_bss_21D8.unk10.y < lbl_1_bss_21D8.unkC) {
                lbl_1_bss_21D8.unk10.y = lbl_1_bss_21D8.unkC;
                fn_1_3ED3C(0, lbl_1_bss_21D8.unk10);
                Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_21D8.unk10);
                lbl_1_bss_1168[1] = 0;
                Hu3DModelKill(lbl_1_bss_21D8.mdl[0]);
                Hu3DModelKill(lbl_1_bss_21D8.mdl[1]);
                fn_1_8D04(0x454, lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_1168[1] = 99;
                Hu3DModelShadowMapSet(lbl_1_bss_478[player->unk10][player->unk14]);
            }
            break;
        case 99:
            break;
    }
    if (lbl_1_bss_8[1] != 0) {
        if (HuAudSStreamStatGet(lbl_1_bss_8[0]) == 0) {
            HuAudSStreamVolSet(0, 127, 1000);
            lbl_1_bss_8[0] = lbl_1_bss_8[1] = 0;
            if (lbl_1_bss_1168[1] == 99) {
                lbl_1_bss_1168[1] = 0;
                ret = 1;
            }
        }
    }
    else if (lbl_1_bss_1168[1] == 99) {
        lbl_1_bss_1168[1] = 0;
        ret = 1;
    }
    return ret;
}

/* 12 insns */
void fn_1_392B8(void)
{
    memset(&lbl_1_bss_2034, 0, sizeof(lbl_1_bss_2034));
}

/* 55 insns */
void fn_1_392E8(s16 idx, HuVecF a1, HuVecF a2)
{
    lbl_1_bss_2034.rec[idx].unk18 = a1;
    lbl_1_bss_2034.rec[idx].unk24 = a2;
    lbl_1_bss_2034.rec[idx].unk48 = frandmod(90) - 45;
}

/* 0x834 */ float lbl_1_data_834[21] = { 0.24149999f, 0.12449999f, 0.24149999f, 90.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 90.0f, 0.0f, 0.0f, -90.0f, 0.0f, 0.0f, 180.0f, -90.0f, 0.0f, 0.0f };

/* 4335 insns */
s32 fn_1_393C4(CardGameWork *work)
{
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    HuVecF pos;
    HuVecF posA;
    HuVecF posB;
    HuVecF pos2;
    HuVecF pos3;
    float scale[3] = { 0.24149999f, 0.12449999f, 0.24149999f };
    s32 layer[3] = { 0, 2, 0 };
    s32 flag;
    s32 i;

    switch (lbl_1_bss_2034.unk0[0]) {
        case 0:
            Hu3DZClearLayerSet(15);
            if (lbl_1_bss_2034.unk188 == 0) {
                lbl_1_bss_2034.unk18C = 1;
                lbl_1_bss_2034.unk0[2] = (player->unk50 & 2) ? 2 : 1;
                lbl_1_bss_2034.unk0[3] = (player->unk50 & 2) ? 1 : ((player->unk50 & 4) ? 2 : 0);
                if (player->unk50 & 0x800) {
                    lbl_1_bss_2034.unk0[2]++;
                }
                if (player->unk50 & 0x2000) {
                    lbl_1_bss_2034.unk18C = 0;
                    lbl_1_bss_2034.unk0[3] = 3;
                    lbl_1_bss_2034.unk0[2] = 2;
                }
                if ((player->unk50 & 0x1000) && lbl_1_bss_2034.unk190 == 0) {
                    lbl_1_bss_2034.unk190 = 1;
                    lbl_1_bss_2034.unk18C = 0;
                    lbl_1_bss_2034.unk0[3] = 4;
                    lbl_1_bss_2034.unk0[2] = 1;
                }
            }
            else {
                lbl_1_bss_2034.unk18C = 0;
                espDrawNoSet(lbl_1_bss_F9E[0], 64);
                espDrawNoSet(lbl_1_bss_F9E[1], 64);
                lbl_1_bss_2034.unk184 = espEntry(lbl_1_data_2B4[11], 0, 0);
                espDrawNoSet(lbl_1_bss_2034.unk184, 64);
                espPosSet(lbl_1_bss_2034.unk184, 0.0f, 0.0f);
                espBankSet(lbl_1_bss_2034.unk184, 0);
                espDispOff(lbl_1_bss_2034.unk184);
                fn_1_9C74(&lbl_1_bss_2034.unk194, player->unk10, player->unk14, 1, 1);
                lbl_1_bss_2034.unk194.x += -50.0f;
                lbl_1_bss_2034.unk194.y += 100.0f;
                lbl_1_bss_2034.unk0[2] = 1;
                lbl_1_bss_2034.unk0[3] = 0;
            }
            for (i = 0; i < 3; i++) {
                lbl_1_bss_2034.rec[i].unk0[0] = Hu3DModelCreateData(lbl_1_data_B0[lbl_1_bss_2034.unk0[3] + 0x39]);
                Hu3DModelPosSet(lbl_1_bss_2034.rec[i].unk0[0], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_2034.rec[i].unk0[0], 2);
                Hu3DModelLayerSet(lbl_1_bss_2034.rec[i].unk0[0], layer[i]);
                if (lbl_1_bss_2034.unk0[3] == 3) {
                    lbl_1_bss_2034.rec[i].unk0[1] = Hu3DModelCreateData(lbl_1_data_B0[0x3E]);
                    lbl_1_bss_2034.rec[i].unk0[2] = Hu3DModelCreateData(lbl_1_data_B0[0x3F]);
                    lbl_1_bss_2034.rec[i].unk0[3] = Hu3DModelCreateData(lbl_1_data_B0[0x4E]);
                    lbl_1_bss_2034.rec[i].unk0[5] = Hu3DLLightCreate(lbl_1_bss_2034.rec[i].unk0[3], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y,
                        Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 255, 255, 255);
                    Hu3DLLightInfinitytSet(lbl_1_bss_2034.rec[i].unk0[3], lbl_1_bss_2034.rec[i].unk0[5]);
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[2], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelLayerSet(lbl_1_bss_2034.rec[i].unk0[1], layer[i]);
                    Hu3DModelLayerSet(lbl_1_bss_2034.rec[i].unk0[2], layer[i]);
                    Hu3DModelLayerSet(lbl_1_bss_2034.rec[i].unk0[3], 4);
                }
                Hu3DModelScaleSet(lbl_1_bss_2034.rec[i].unk0[0], scale[i], scale[i], scale[i]);
                lbl_1_bss_2034.rec[i].unk78 = -1;
                lbl_1_bss_2034.rec[i].unk14 = i * 10;
            }
            if (lbl_1_bss_2034.unk0[2] == 1) {
                pos = (HuVecF) { 80.0f, 380.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 280.0f, 240.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(0, posA, posB);
                pos = (HuVecF) { 80.0f, 380.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk30);
                pos = (HuVecF) { 280.0f, 240.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk3C);
            }
            else if (lbl_1_bss_2034.unk0[2] == 2) {
                pos = (HuVecF) { 60.0f, 360.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 260.0f, 220.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(0, posA, posB);
                pos = (HuVecF) { 60.0f, 360.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk30);
                pos = (HuVecF) { 260.0f, 220.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk3C);
                pos = (HuVecF) { 100.0f, 400.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 300.0f, 260.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(1, posA, posB);
                pos = (HuVecF) { 100.0f, 400.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[1].unk30);
                pos = (HuVecF) { 300.0f, 260.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[1].unk3C);
            }
            else {
                pos = (HuVecF) { 60.0f, 360.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 260.0f, 220.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(0, posA, posB);
                pos = (HuVecF) { 60.0f, 360.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk30);
                pos = (HuVecF) { 260.0f, 220.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[0].unk3C);
                lbl_1_bss_2034.rec[0].unk14 = 10;
                pos = (HuVecF) { 100.0f, 400.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 300.0f, 260.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(1, posA, posB);
                pos = (HuVecF) { 100.0f, 400.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[1].unk30);
                pos = (HuVecF) { 300.0f, 260.0f, 500.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[1].unk3C);
                lbl_1_bss_2034.rec[1].unk14 = 20;
                pos = (HuVecF) { 135.0f, 355.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posA);
                pos = (HuVecF) { 335.0f, 215.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &posB);
                fn_1_392E8(2, posA, posB);
                pos = (HuVecF) { 135.0f, 355.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[2].unk30);
                pos = (HuVecF) { 335.0f, 215.0f, 1000.0f };
                Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.rec[2].unk3C);
                lbl_1_bss_2034.rec[2].unk14 = 0;
            }
            for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                Hu3DMotionTimeSet(lbl_1_bss_2034.rec[i].unk0[0], 1.0f);
                Hu3DMotionSpeedSet(lbl_1_bss_2034.rec[i].unk0[0], 0.0f);
                if (lbl_1_bss_2034.unk188 != 0) {
                    Hu3D3Dto2D(&lbl_1_bss_2034.unk194, 1, &lbl_1_bss_2034.unk194);
                    pos = (HuVecF) { lbl_1_bss_2034.unk194.x, lbl_1_bss_2034.unk194.y, 1000.0f };
                    Hu3D2Dto3D(&pos, 1, &lbl_1_bss_2034.unk194);
                    Hu3DModelPosSetV(lbl_1_bss_2034.rec[i].unk0[0], &lbl_1_bss_2034.unk194);
                }
                else {
                    Hu3DModelPosSetV(lbl_1_bss_2034.rec[i].unk0[0], &lbl_1_bss_2034.rec[i].unk18);
                }
                Hu3DModelRotSet(lbl_1_bss_2034.rec[i].unk0[0], 0.0f, lbl_1_bss_2034.rec[i].unk48, 0.0f);
                lbl_1_bss_2034.rec[i].unk58 = (HuVecF) { 0.0f, 0.0f, 0.0f };
                flag = frandmod(100);
                if (player->unk50 & 4) {
                    if (flag < 80) {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(2);
                    }
                    else {
                        lbl_1_bss_2034.rec[i].unk78 = 2;
                    }
                }
                else if (player->unk50 & 2) {
                    if (flag < 10) {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(2);
                    }
                    else if (flag < 20) {
                        lbl_1_bss_2034.rec[i].unk78 = 2;
                    }
                    else {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(3) + 3;
                    }
                }
                else {
                    if (flag < 10) {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(2);
                    }
                    else {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(4) + 2;
                    }
                }
                if (lbl_1_bss_2034.unk188 != 0) {
                    if (flag < 10) {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(2);
                    }
                    else {
                        lbl_1_bss_2034.rec[i].unk78 = frandmod(4) + 2;
                    }
                }
                lbl_1_bss_2034.rec[i].unk4C = frandmod(3) + 2;
                lbl_1_bss_2034.rec[i].unk50 = 1;
                lbl_1_bss_2034.rec[i].unk54 = 1;
                if (lbl_1_bss_2034.unk188 != 0) {
                    Hu3D3Dto2D(&lbl_1_bss_2034.unk194, 1, &pos);
                    pos.z = 1000.0f;
                    Hu3D2Dto3D(&pos, 1, &pos);
                    fn_1_3ED3C(16, pos);
                    omVibrate(work->unk174[work->unk170], 15, 12, 0);
                }
                else {
                    fn_1_3ED3C(16, lbl_1_bss_2034.rec[i].unk30);
                }
                fn_1_3F498(16, i, (HuVecF) { 0.0f, lbl_1_bss_2034.rec[i].unk48, 0.0f });
                fn_1_3F380(16, i, 2);
                fn_1_3F658(16, i, layer[i] + 1);
                fn_1_3F6B0(16, i, (HuVecF) { lbl_1_data_834[i], lbl_1_data_834[i], lbl_1_data_834[i] });
                lbl_1_bss_2034.unk1A0 = 2.0f;
                fn_1_3F594(16, i, lbl_1_bss_2034.unk1A0);
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x80, lbl_1_bss_2034.rec[i].unk58.x);
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x100, lbl_1_bss_2034.rec[i].unk58.y);
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x200, lbl_1_bss_2034.rec[i].unk58.z);
            }
            fn_1_8D04(0x442, lbl_1_bss_2034.rec[0].unk0[0], 1);
            lbl_1_bss_2034.unk0[1] = 0;
            if (lbl_1_bss_2034.unk188 != 0) {
                lbl_1_bss_2034.unk0[0] = 11;
            }
            else {
                lbl_1_bss_2034.unk0[0]++;
            }
            break;
        case 1:
            if (++lbl_1_bss_2034.unk0[1] == 12.0f / lbl_1_bss_2034.unk1A0) {
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrReset(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                }
            }
            if (lbl_1_bss_2034.unk0[1] >= 60.0f / lbl_1_bss_2034.unk1A0) {
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    if (lbl_1_bss_2034.unk18C == 1) {
                        if (player->unk34 == -1 || (player->unk50 & 0x20)) {
                            fn_1_502E0(15);
                        }
                        else {
                            fn_1_502E0(16);
                        }
                    }
                    else {
                        fn_1_502E0(24);
                    }
                }
                lbl_1_bss_2034.unk0[0]++;
                HuAudFXPlay(0x35C);
                lbl_1_bss_1C = fn_1_8D04(0x2F7, lbl_1_bss_2034.rec[0].unk0[0], 1);
            }
            break;
        case 2:
            for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                lbl_1_bss_2034.rec[i].unk58.x += 50.0f;
                lbl_1_bss_2034.rec[i].unk58.y += 30.0f;
                lbl_1_bss_2034.rec[i].unk58.z += 50.0f;
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x80, lbl_1_bss_2034.rec[i].unk58.x);
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x100, lbl_1_bss_2034.rec[i].unk58.y);
                Hu3DMotionForceSet(lbl_1_bss_2034.rec[i].unk0[0], "dice_jnt", 0x200, lbl_1_bss_2034.rec[i].unk58.z);
            }
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_A) {
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    lbl_1_bss_2034.rec[i].unkC = lbl_1_bss_2034.rec[i].unk10 = 0;
                }
                fn_1_50460();
                lbl_1_bss_2034.unk0[0]++;
                fn_1_8D04(0x446, lbl_1_bss_2034.rec[0].unk0[0], 1);
                HuAudFXStop(lbl_1_bss_1C);
                lbl_1_bss_20[8] = 0;
                break;
            }
            if (lbl_1_bss_2034.unk18C == 0) {
                break;
            }
            if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_START) {
                lbl_1_bss_2034.unk0[0] = 0;
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    fn_1_3F278(16, i);
                }
                Hu3DLayerHookSet(15, NULL);
                fn_1_50460();
                work->unk188 = 0xCA;
                HuAudFXPlay(0x3FA);
                HuAudSStreamVolSet(0, 0x60, 500);
            }
            else if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_B) {
                if (player->unk34 == -1 || (player->unk50 & 0x20)) {
                    break;
                }
                lbl_1_bss_2034.unk0[0] = 0;
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    fn_1_3F278(16, i);
                }
                fn_1_50460();
                Hu3DLayerHookSet(15, NULL);
                work->unk188 = 0xCB;
                work->unk19C = 7;
                HuAudFXPlay(0x3F9);
                HuAudSStreamVolSet(0, 0x60, 500);
            }
            else if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_BUTTON_Y) {
                lbl_1_bss_2034.unk0[0] = 0;
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    fn_1_3F278(16, i);
                }
                fn_1_50460();
                Hu3DLayerHookSet(15, NULL);
                work->unk188 = 0xCD;
                HuAudFXPlay(0x3FB);
                HuAudSStreamVolSet(0, 0x60, 500);
            }
            else if (HuPadBtnDown[work->unk174[work->unk170]] & PAD_TRIGGER_R) {
                lbl_1_bss_2034.unk0[0] = 0;
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    fn_1_3F278(16, i);
                }
                fn_1_50460();
                Hu3DLayerHookSet(15, NULL);
                work->unk188 = 0xCC;
                HuAudFXPlay(0x3FB);
                HuAudSStreamVolSet(0, 0x60, 500);
            }
            if (lbl_1_bss_2034.unk0[0] != 0) {
                break;
            }
            for (i = 0; i < 3; i++) {
                if (lbl_1_bss_2034.unk0[3] == 3) {
                    Hu3DLLightKill(lbl_1_bss_2034.rec[i].unk0[3], lbl_1_bss_2034.rec[i].unk0[5]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[1]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[2]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[3]);
                }
                Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[0]);
                fn_1_3F658(16, i, 4);
                fn_1_3F278(16, i);
            }
            if (lbl_1_bss_2034.unk188 != 0) {
                espKill(lbl_1_bss_2034.unk184);
                espDrawNoSet(lbl_1_bss_F9E[0], 0);
                espDrawNoSet(lbl_1_bss_F9E[1], 0);
            }
            HuAudFXStop(lbl_1_bss_1C);
            break;
        case 3:
            if (++lbl_1_bss_20[8] < 47) {
                fn_1_8D04(0x8446, lbl_1_bss_2034.rec[0].unk0[0], 1);
            }
            flag = 1;
            for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                lbl_1_bss_20[9] = i + 1;
                if (fn_1_3D780(&lbl_1_bss_2034.rec[i]) == 0) {
                    flag = 0;
                }
            }
            if (flag == 0) {
                break;
            }
            lbl_1_bss_2034.unk0[0]++;
            lbl_1_bss_2034.unk0[1] = 0;
            lbl_1_bss_20[9] = 0;
            lbl_1_bss_20[8] = 0;
            break;
        case 4:
            if (++lbl_1_bss_2034.unk0[1] < 45) {
                break;
            }
            flag = 0;
            for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                fn_1_3ED3C(16, lbl_1_bss_2034.rec[i].unk3C);
                fn_1_3F498(16, i, (HuVecF) { 0.0f, lbl_1_bss_2034.rec[i].unk48, 0.0f });
                fn_1_3F380(16, i, 2);
                fn_1_3F6B0(16, i, (HuVecF) { lbl_1_data_834[i], lbl_1_data_834[i], lbl_1_data_834[i] });
                if (lbl_1_bss_2034.unk188 != 0) {
                    fn_1_3F658(16, i, 7);
                }
                else {
                    fn_1_3F658(16, i, layer[i] + 1);
                }
                fn_1_3F594(16, i, lbl_1_bss_2034.unk1A0);
                if (lbl_1_bss_2034.unk0[3] == 3 && lbl_1_bss_2034.rec[i].unk78 == 3) {
                    fn_1_3F4EC(16, i, 1);
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_2034.rec[i].unk0[1], HU3D_ATTR_DISPOFF);
                    Hu3DMotionShapeTimeSet(lbl_1_bss_2034.rec[i].unk0[1], 0.0f);
                    Hu3DMotionShapeSpeedSet(lbl_1_bss_2034.rec[i].unk0[1], 2.0f);
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[1]].pos = Hu3DData[lbl_1_bss_2034.rec[i].unk0[2]].pos
                        = Hu3DData[lbl_1_bss_2034.rec[i].unk0[0]].pos;
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[1]].rot = Hu3DData[lbl_1_bss_2034.rec[i].unk0[2]].rot
                        = Hu3DData[lbl_1_bss_2034.rec[i].unk0[0]].rot;
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].rot = (HuVecF) { 0.0f, 0.0f, 0.0f };
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[1]].scale = Hu3DData[lbl_1_bss_2034.rec[i].unk0[2]].scale
                        = Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].scale = Hu3DData[lbl_1_bss_2034.rec[i].unk0[0]].scale;
                    if (i == 0) {
                        pos = (HuVecF) { 260.0f, 215.0f, 900.0f };
                    }
                    else {
                        pos = (HuVecF) { 300.0f, 255.0f, 450.0f };
                    }
                    Hu3D2Dto3D(&pos, 1, &pos);
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].pos = pos;
                    flag = 1;
                }
            }
            if (lbl_1_bss_2034.unk0[3] != 3 || lbl_1_bss_2034.rec[0].unk78 != 3 || lbl_1_bss_2034.rec[1].unk78 != 3) {
                fn_1_8D04(0x445, lbl_1_bss_2034.rec[0].unk0[0], 1);
            }
            lbl_1_bss_2034.unk0[1] = 0;
            if (flag == 0) {
                lbl_1_bss_2034.unk0[0]++;
            }
            else {
                lbl_1_bss_2034.unk0[0] += 2;
            }
            break;
        case 5:
            if (lbl_1_bss_2034.unk0[1] == 12.0f / lbl_1_bss_2034.unk1A0) {
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                }
                if (lbl_1_bss_2034.unk188 != 0) {
                    espPosSet(lbl_1_bss_2034.unk184, 286.0f, 238.0f);
                    espBankSet(lbl_1_bss_2034.unk184, lbl_1_bss_2034.rec[0].unk78 + 1);
                    espDispOn(lbl_1_bss_2034.unk184);
                    lbl_1_bss_2034.unk0[1] = 0;
                    lbl_1_bss_2034.unk0[0] = 13;
                }
            }
            if (++lbl_1_bss_2034.unk0[1] < 60.0f / lbl_1_bss_2034.unk1A0) {
                break;
            }
            work->unk184 = lbl_1_bss_2034.rec[0].unk78 + lbl_1_bss_2034.rec[1].unk78 + lbl_1_bss_2034.rec[2].unk78 + 3;
            lbl_1_bss_2034.unk0[0] = 20;
            if (lbl_1_bss_2034.unk0[3] != 3) {
                break;
            }
            lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
            fn_1_4FBC8(work, 0x35);
            break;
        case 6:
            if (lbl_1_bss_2034.unk0[1] == 12.0f / lbl_1_bss_2034.unk1A0) {
                for (i = 0; i < lbl_1_bss_2034.unk0[2]; i++) {
                    if (lbl_1_bss_2034.rec[i].unk78 != 3) {
                        Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[0], HU3D_ATTR_DISPOFF);
                    }
                }
            }
            if (++lbl_1_bss_2034.unk0[1] < 20) {
                break;
            }
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_2034.rec[i].unk78 == 3) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_2034.rec[i].unk0[2], HU3D_ATTR_DISPOFF);
                    Hu3DMotionShapeTimeSet(lbl_1_bss_2034.rec[i].unk0[2], 0.0f);
                    Hu3DMotionShapeSpeedSet(lbl_1_bss_2034.rec[i].unk0[2], 2.0f);
                    lbl_1_bss_2034.rec[i].unk0[4] = fn_1_3ED3C(9, Hu3DData[lbl_1_bss_2034.rec[i].unk0[2]].pos);
                    fn_1_3F6B0(9, lbl_1_bss_2034.rec[i].unk0[4], (HuVecF) { scale[i], scale[i], scale[i] });
                    fn_1_8D04(0x42F, lbl_1_bss_2034.rec[i].unk0[2], 1);
                    fn_1_8D04(0x457, lbl_1_bss_2034.rec[i].unk0[2], 1);
                }
            }
            lbl_1_bss_2034.unk0[1] = 0;
            lbl_1_bss_2034.unk0[0]++;
            break;
        case 7:
            if (++lbl_1_bss_2034.unk0[1] < 55) {
                break;
            }
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_2034.rec[i].unk78 == 3) {
                    Hu3DModelAttrReset(lbl_1_bss_2034.rec[i].unk0[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelCameraSet(lbl_1_bss_2034.rec[i].unk0[3], 2);
                    Hu3DModelLayerSet(lbl_1_bss_2034.rec[i].unk0[3], 7);
                }
            }
            lbl_1_bss_2034.unk0[1] = 0;
            lbl_1_bss_2034.unk0[0]++;
            break;
        case 8:
            flag = 0;
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_2034.rec[i].unk78 == 3 && fn_1_3F714(9, lbl_1_bss_2034.rec[i].unk0[4]) != 0) {
                    lbl_1_bss_2034.rec[i].unk64 = Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].pos;
                    Hu3D3Dto2D(&Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].pos, 1, &pos2);
                    pos3 = (HuVecF) { ((float(*)[2])lbl_1_data_528)[work->unk170][0] - 12.0f,
                        ((float(*)[2])lbl_1_data_528)[work->unk170][1] - 12.0f, 0.0f };
                    fn_1_4F144(i, pos2, pos3, 60, 0.0f, 0x21);
                    lbl_1_bss_2034.rec[i].unk74 = scale[i];
                    lbl_1_bss_2034.rec[i].unk70 = 0.0f;
                    flag = 1;
                    lbl_1_bss_20[0] = i;
                }
            }
            if (flag != 1) {
                break;
            }
            lbl_1_bss_2034.unk0[1] = 0;
            lbl_1_bss_2034.unk0[0]++;
            fn_1_8D04(0x353, lbl_1_bss_2034.rec[lbl_1_bss_20[0]].unk0[3], 1);
            break;
        case 9:
            fn_1_8D04(0x8353, lbl_1_bss_2034.rec[lbl_1_bss_20[0]].unk0[3], 1);
            lbl_1_bss_2034.unk0[1]++;
            flag = 0;
            for (i = 0; i < 2; i++) {
                if (lbl_1_bss_2034.rec[i].unk78 == 3) {
                    lbl_1_bss_2034.rec[i].unk74 = scale[i] - 0.6f * scale[i] * fn_1_4EEA0(0, lbl_1_bss_2034.unk0[1] / 60.0f);
                    lbl_1_bss_2034.rec[i].unk70 -= 10.0f + 5.5f * fn_1_4EEA0(0, lbl_1_bss_2034.unk0[1] / 60.0f);
                    Hu3DModelRotSet(lbl_1_bss_2034.rec[i].unk0[3], 0.0f, 0.0f, lbl_1_bss_2034.rec[i].unk70);
                    Hu3DModelScaleSet(lbl_1_bss_2034.rec[i].unk0[3], lbl_1_bss_2034.rec[i].unk74, lbl_1_bss_2034.rec[i].unk74,
                        lbl_1_bss_2034.rec[i].unk74);
                    if (fn_1_4F1EC(i, &pos) != 0) {
                        flag = 1;
                    }
                    Hu3DData[lbl_1_bss_2034.rec[i].unk0[3]].pos = fn_1_4EDB8(lbl_1_bss_2034.rec[i].unk64, pos.x, pos.y);
                }
            }
            if (flag == 1) {
                work->unk184 = 0;
                if (lbl_1_bss_2034.rec[0].unk78 == 3) {
                    work->unk184++;
                    player->unk44++;
                }
                if (lbl_1_bss_2034.rec[1].unk78 == 3) {
                    work->unk184++;
                    player->unk44++;
                }
                player->unk40 = player->unk44 + (player->unk48 * 2 + player->unk4C * -1);
                fn_1_2FFAC(work);
                Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][0], 0.0f,
                    10.0f, 0);
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                    lbl_1_bss_20[1] = 0x1F6;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                    lbl_1_bss_20[1] = 0x1E2;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                    lbl_1_bss_20[1] = 0x25A;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                    lbl_1_bss_20[1] = 0x2AA;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                    lbl_1_bss_20[1] = 0x282;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                    lbl_1_bss_20[1] = 0x1BA;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                    lbl_1_bss_20[1] = 0x296;
                }
                fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[1] = 0;
                for (i = 0; i < 2; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_2034.rec[i].unk0[3], HU3D_ATTR_DISPOFF);
                }
                lbl_1_bss_2034.unk0[0] = 16;
                HuAudFXPlay(8);
                if (lbl_1_bss_2034.rec[0].unk78 == 3 && lbl_1_bss_2034.rec[1].unk78 == 3) {
                    lbl_1_bss_2034.unk0[1] = 0;
                }
                lbl_1_bss_20[0] = 0;
            }
            if (lbl_1_bss_2034.unk0[1] == 58) {
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
            }
            break;
        case 10:
            if (Hu3DMotionEndCheck(lbl_1_bss_468[work->unk174[work->unk170]]) != 0) {
                lbl_1_bss_2034.unk0[0] = 20;
            }
            break;
        case 11:
            if (++lbl_1_bss_2034.unk0[1] == 12.0f / lbl_1_bss_2034.unk1A0) {
                Hu3DModelAttrReset(lbl_1_bss_2034.rec[0].unk0[0], HU3D_ATTR_DISPOFF);
            }
            if (lbl_1_bss_2034.unk0[1] >= 60.0f / lbl_1_bss_2034.unk1A0) {
                HuAudFXPlay(0x413);
                fn_1_4FBC8(work, 0x3E);
                Hu3D3Dto2D(&lbl_1_bss_2034.unk194, 1, &pos);
                posA = (HuVecF) { 80.0f, 380.0f, 0.0f };
                fn_1_4F144(0, pos, posA, 60, 200.0f, 0x355);
                lbl_1_bss_2034.unk0[0]++;
                fn_1_8D04(0x446, lbl_1_bss_2034.rec[0].unk0[0], 1);
            }
            break;
        case 12:
            fn_1_8D04(0x8446, lbl_1_bss_2034.rec[0].unk0[0], 1);
            if (fn_1_4F1EC(0, &pos) != 0) {
                if (GwPlayerConf[work->unk174[work->unk170]].type == 0) {
                    fn_1_502E0(24);
                }
                lbl_1_bss_2034.unk0[0] = 2;
                HuAudFXPlay(0x35C);
                lbl_1_bss_1C = fn_1_8D04(0x2F7, lbl_1_bss_2034.rec[0].unk0[0], 1);
            }
            Hu3DData[lbl_1_bss_2034.rec[0].unk0[0]].pos = fn_1_4EDB8(lbl_1_bss_2034.unk194, pos.x, pos.y);
            lbl_1_bss_2034.rec[0].unk58.y += 24.0f;
            Hu3DMotionForceSet(lbl_1_bss_2034.rec[0].unk0[0], "dice_jnt", 0x100, lbl_1_bss_2034.rec[0].unk58.y);
            break;
        case 13:
            if (++lbl_1_bss_2034.unk0[1] < 30.0f / lbl_1_bss_2034.unk1A0) {
                break;
            }
            pos = (HuVecF) { 286.0f, 238.0f, 0.0f };
            posA = (HuVecF) { 210.0f, 90.0f, 0.0f };
            fn_1_4F144(0, pos, posA, 60, 100.0f, 0x355);
            lbl_1_bss_2034.unk0[1] = 0;
            lbl_1_bss_2034.unk0[0]++;
            break;
        case 14:
            lbl_1_bss_2034.unk0[1]++;
            if (lbl_1_bss_2034.unk0[1] == 48) {
                posA = (HuVecF) { 210.0f, 90.0f, 700.0f };
                Hu3D2Dto3D(&posA, 1, &posA);
                fn_1_3ED3C(1, posA);
                fn_1_3F380(1, 0, 2);
                fn_1_3F658(1, 0, 7);
                fn_1_3F6B0(1, 0, (HuVecF) { 0.6f, 0.6f, 0.6f });
            }
            if (fn_1_4F1EC(0, &pos) != 0) {
                work->unk184 += lbl_1_bss_2034.rec[0].unk78 + 1;
                espDispOff(lbl_1_bss_2034.unk184);
                fn_1_30B00(work, 1);
                lbl_1_bss_2034.unk0[1] = 0;
                lbl_1_bss_2034.unk0[0]++;
            }
            espScaleSet(lbl_1_bss_2034.unk184, cos(M_PI * (18.0f * lbl_1_bss_2034.unk0[1]) / 180.0), 1.0f);
            espPosSet(lbl_1_bss_2034.unk184, pos.x, pos.y);
            break;
        case 15:
            if (++lbl_1_bss_2034.unk0[1] < 30) {
                break;
            }
            lbl_1_bss_2034.unk0[0] = 20;
            break;
        case 16:
            if (lbl_1_bss_2034.rec[0].unk78 == 3 && lbl_1_bss_2034.rec[1].unk78 == 3) {
                if (++lbl_1_bss_2034.unk0[1] != 20) {
                    break;
                }
                HuAudFXPlay(8);
            }
            lbl_1_bss_12A8.unk8[0] = GwPlayerConf[work->unk174[work->unk170]].charNo;
            fn_1_4FBC8(work, (work->unk184 == 1) ? 0x40 : 0x41);
            lbl_1_bss_2034.unk0[0] = 10;
            break;
        default:
            for (i = 0; i < 3; i++) {
                if (lbl_1_bss_2034.unk0[3] == 3) {
                    Hu3DLLightKill(lbl_1_bss_2034.rec[i].unk0[3], lbl_1_bss_2034.rec[i].unk0[5]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[1]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[2]);
                    Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[3]);
                }
                Hu3DModelKill(lbl_1_bss_2034.rec[i].unk0[0]);
                fn_1_3F658(16, i, 4);
                fn_1_3F278(16, i);
            }
            if (lbl_1_bss_2034.unk188 != 0) {
                espKill(lbl_1_bss_2034.unk184);
                espDrawNoSet(lbl_1_bss_F9E[0], 0);
                espDrawNoSet(lbl_1_bss_F9E[1], 0);
            }
            lbl_1_bss_2034.unk0[0] = 0;
            Hu3DLayerHookSet(15, NULL);
            return 1;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
    return 0;
}

/* 1201 insns */
s32 fn_1_3D780(CardStatusRec *rec)
{
    HuVecF tbl[6] = { { 90.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 90.0f }, { 0.0f, 0.0f, -90.0f }, { 0.0f, 0.0f, 180.0f },
        { -90.0f, 0.0f, 0.0f } };
    HuVecF pos;
    float t;
    float maxT = 84.0f;

    switch (rec->unkC) {
        case 0:
            rec->unk58.x += 50.0f;
            rec->unk58.y += 30.0f;
            rec->unk58.z += 50.0f;
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x80, rec->unk58.x);
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x100, rec->unk58.y);
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x200, rec->unk58.z);
            if (++rec->unk10 >= rec->unk14) {
                Hu3DMotionSpeedSet(rec->unk0[0], 1.0f);
                rec->unkC++;
            }
            break;
        case 1:
            t = Hu3DMotionTimeGet(rec->unk0[0]);
            if (t > maxT) {
                t = maxT;
                rec->unk10 = 0;
                rec->unkC++;
            }
            if (t <= 47.0f) {
            pos = (HuVecF) { rec->unk18.x + 0.6f * (t * (rec->unk24.x - rec->unk18.x)) / 47.0f,
                rec->unk18.y + 0.6f * (t * (rec->unk24.y - rec->unk18.y)) / 47.0f,
                rec->unk18.z + 0.6f * (t * (rec->unk24.z - rec->unk18.z)) / 47.0f };
            rec->unk58.x = -(0.7f * (t * (360.0f * rec->unk4C + tbl[rec->unk78].x))) / 47.0f;
            rec->unk58.y = 0.7f * (t * (360.0f * rec->unk50 + tbl[rec->unk78].y)) / 47.0f;
            rec->unk58.z = 0.7f * (t * (360.0f * rec->unk54 + tbl[rec->unk78].z)) / 47.0f;
            } else if (t <= 67.0f) {
            pos = (HuVecF) { rec->unk18.x + 0.6f * (rec->unk24.x - rec->unk18.x),
                rec->unk18.y + 0.6f * (rec->unk24.y - rec->unk18.y),
                rec->unk18.z + 0.6f * (rec->unk24.z - rec->unk18.z) };
            pos.x += 0.25f * ((t - 47.0f) * (rec->unk24.x - rec->unk18.x)) / 20.0f;
            pos.y += 0.25f * ((t - 47.0f) * (rec->unk24.y - rec->unk18.y)) / 20.0f;
            pos.z += 0.25f * ((t - 47.0f) * (rec->unk24.z - rec->unk18.z)) / 20.0f;
            rec->unk58.x = -(0.7f * (360.0f * rec->unk4C + tbl[rec->unk78].x));
            rec->unk58.y = 0.7f * (360.0f * rec->unk50 + tbl[rec->unk78].y);
            rec->unk58.z = 0.7f * (360.0f * rec->unk54 + tbl[rec->unk78].z);
            rec->unk58.x -= 0.2f * ((t - 47.0f) * (360.0f * rec->unk4C + tbl[rec->unk78].x)) / 20.0f;
            rec->unk58.y += 0.2f * ((t - 47.0f) * (360.0f * rec->unk50 + tbl[rec->unk78].y)) / 20.0f;
            rec->unk58.z += 0.2f * ((t - 47.0f) * (360.0f * rec->unk54 + tbl[rec->unk78].z)) / 20.0f;
            } else if (t <= 77.0f) {
            pos = (HuVecF) { rec->unk18.x + 0.85f * (rec->unk24.x - rec->unk18.x),
                rec->unk18.y + 0.85f * (rec->unk24.y - rec->unk18.y),
                rec->unk18.z + 0.85f * (rec->unk24.z - rec->unk18.z) };
            pos.x += 0.1f * ((t - 67.0f) * (rec->unk24.x - rec->unk18.x)) / 10.0f;
            pos.y += 0.1f * ((t - 67.0f) * (rec->unk24.y - rec->unk18.y)) / 10.0f;
            pos.z += 0.1f * ((t - 67.0f) * (rec->unk24.z - rec->unk18.z)) / 10.0f;
            rec->unk58.x = -(0.9f * (360.0f * rec->unk4C + tbl[rec->unk78].x));
            rec->unk58.y = 0.9f * (360.0f * rec->unk50 + tbl[rec->unk78].y);
            rec->unk58.z = 0.9f * (360.0f * rec->unk54 + tbl[rec->unk78].z);
            rec->unk58.x -= 0.075f * ((t - 67.0f) * (360.0f * rec->unk4C + tbl[rec->unk78].x)) / 10.0f;
            rec->unk58.y += 0.075f * ((t - 67.0f) * (360.0f * rec->unk50 + tbl[rec->unk78].y)) / 10.0f;
            rec->unk58.z += 0.075f * ((t - 67.0f) * (360.0f * rec->unk54 + tbl[rec->unk78].z)) / 10.0f;
            } else {
            pos = (HuVecF) { rec->unk18.x + 0.95000005f * (rec->unk24.x - rec->unk18.x),
                rec->unk18.y + 0.95000005f * (rec->unk24.y - rec->unk18.y),
                rec->unk18.z + 0.95000005f * (rec->unk24.z - rec->unk18.z) };
            pos.x += 0.049999952f * ((t - 77.0f) * (rec->unk24.x - rec->unk18.x)) / (maxT - 77.0f);
            pos.y += 0.049999952f * ((t - 77.0f) * (rec->unk24.y - rec->unk18.y)) / (maxT - 77.0f);
            pos.z += 0.049999952f * ((t - 77.0f) * (rec->unk24.z - rec->unk18.z)) / (maxT - 77.0f);
            rec->unk58.x = -(0.97499996f * (360.0f * rec->unk4C + tbl[rec->unk78].x));
            rec->unk58.y = 0.97499996f * (360.0f * rec->unk50 + tbl[rec->unk78].y);
            rec->unk58.z = 0.97499996f * (360.0f * rec->unk54 + tbl[rec->unk78].z);
            rec->unk58.x -= 0.025000036f * ((t - 77.0f) * (360.0f * rec->unk4C + tbl[rec->unk78].x)) / (maxT - 77.0f);
            rec->unk58.y += 0.025000036f * ((t - 77.0f) * (360.0f * rec->unk50 + tbl[rec->unk78].y)) / (maxT - 77.0f);
            rec->unk58.z += 0.025000036f * ((t - 77.0f) * (360.0f * rec->unk54 + tbl[rec->unk78].z)) / (maxT - 77.0f);
            }
            Hu3DModelPosSetV(rec->unk0[0], &pos);
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x80, rec->unk58.x);
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x100, rec->unk58.y);
            Hu3DMotionForceSet(rec->unk0[0], "dice_jnt", 0x200, rec->unk58.z);
            if (47.0f == t || 67.0f == t || 77.0f == t) {
                if (fn_1_8E88() & 0x2000) {
                    fn_1_8D04(0x42E, rec->unk0[0], 1);
                } else {
                    if (lbl_1_bss_20[9] == 1) {
                        (void)fn_1_8D04(0x444, rec->unk0[0], 1);
                    } else {
                        (void)fn_1_8D04(0x44B, rec->unk0[0], 1);
                    }
                }
            }
            break;
        case 2:
            return 1;
    }
    return 0;
}

/* 23 insns */
s32 fn_1_3EA44(CardGameWork *work)
{
    lbl_1_bss_2034.unk188 = 1;
    if (fn_1_393C4(work) == 0) {
        return 0;
    }
    lbl_1_bss_2034.unk188 = 0;
    return 1;
}

/* 0x8D8 */ CardStatusMdlTbl lbl_1_data_8D8[26] = { { 1, 0, 1, lbl_1_bss_201C }, { 3, 1, 1, lbl_1_bss_1FD4 }, { 1, 1, 1, lbl_1_bss_1FBC }, { 1, 0, 0, lbl_1_bss_1FA4 }, { 4, 1, 0, lbl_1_bss_1F44 }, { 1, 1, 0, lbl_1_bss_1F2C }, { 1, 1, 1, lbl_1_bss_1F14 }, { 1, 1, 1, lbl_1_bss_1EFC }, { 2, 0, 1, lbl_1_bss_1ECC }, { 2, 1, 1, lbl_1_bss_1E9C }, { 2, 1, 1, lbl_1_bss_1E6C }, { 1, 1, 0, lbl_1_bss_1E54 }, { 1, 0, 0, lbl_1_bss_1E3C }, { 1, 0, 0, lbl_1_bss_1E24 }, { 1, 1, 0, lbl_1_bss_1E0C }, { 30, 0, 1, lbl_1_bss_1B3C }, { 3, 1, 1, lbl_1_bss_1AF4 }, { 5, 1, 1, lbl_1_bss_1A7C }, { 4, 2, 1, lbl_1_bss_1A1C }, { 1, 0, 1, lbl_1_bss_1A04 }, { 1, 0, 1, lbl_1_bss_19EC }, { 1, 0, 1, lbl_1_bss_19D4 }, { 1, 1, 1, lbl_1_bss_19BC }, { 1, 1, 1, lbl_1_bss_19A4 }, { 1, 1, 1, lbl_1_bss_198C }, { 1, 1, 1, lbl_1_bss_1974 } };

/* 167 insns */
void fn_1_3EAA0(void)
{
    s32 i;
    s32 j;

    fn_1_4E5A4();
    Hu3DLayerHookSet(12, fn_1_4E7A8);
    for (i = 0; i < 26; i++) {
        for (j = 0; j < lbl_1_data_8D8[i].num; j++) {
            memset(&lbl_1_data_8D8[i].mdl[j], 0, sizeof(CardStatusMdl));
            lbl_1_data_8D8[i].mdl[j].mdlId = Hu3DModelCreateData(lbl_1_data_344[i]);
            Hu3DModelPosSet(lbl_1_data_8D8[i].mdl[j].mdlId, -900.0f + 500.0f * (i % 6), 1000.0f - 500.0f * (i / 6), 0.0f);
            Hu3DModelRotSet(lbl_1_data_8D8[i].mdl[j].mdlId, 0.0f, 0.0f, 0.0f);
            Hu3DModelAttrSet(lbl_1_data_8D8[i].mdl[j].mdlId, HU3D_ATTR_DISPOFF);
            Hu3DModelCameraSet(lbl_1_data_8D8[i].mdl[j].mdlId, 1);
            Hu3DModelLayerSet(lbl_1_data_8D8[i].mdl[j].mdlId, 4);
            lbl_1_data_8D8[i].mdl[j].lightId = -1;
        }
    }
}

/* 335 insns */
s32 fn_1_3ED3C(s32 grp, HuVecF pos)
{
    s32 i;

    for (i = 0; i < lbl_1_data_8D8[grp].num; i++) {
        if (lbl_1_data_8D8[grp].mdl[i].unk4 == 0) {
            lbl_1_data_8D8[grp].mdl[i].unk4 = 1;
            lbl_1_data_8D8[grp].mdl[i].unk8 = 0;
            Hu3DModelRotSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 0.0f, 0.0f, 0.0f);
            Hu3DModelCameraSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 1);
            Hu3DModelLayerSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 4);
            Hu3DModelScaleSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 1.0f, 1.0f, 1.0f);
            if (grp == 18) {
                Hu3DModelTPLvlSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 0.2f);
                pos.y -= 12.0f;
            }
            if (grp == 4) {
                Hu3DModelAttrSet(lbl_1_data_8D8[grp].mdl[i].mdlId, HU3D_MOTATTR_LOOP);
                pos.y += 150.0f;
            }
            if (grp == 3) {
                Hu3DModelAttrSet(lbl_1_data_8D8[grp].mdl[i].mdlId, HU3D_MOTATTR_SHAPE_LOOP);
                pos.y += 100.0f;
            }
            lbl_1_data_8D8[grp].mdl[i].pos = pos;
            Hu3DModelPosSetV(lbl_1_data_8D8[grp].mdl[i].mdlId, &lbl_1_data_8D8[grp].mdl[i].pos);
            Hu3DModelAttrReset(lbl_1_data_8D8[grp].mdl[i].mdlId, HU3D_ATTR_DISPOFF);
            if (lbl_1_data_8D8[grp].unk4 == 1) {
                Hu3DMotionTimeSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 0.0f);
            } else if (lbl_1_data_8D8[grp].unk4 == 0) {
                Hu3DMotionShapeTimeSet(lbl_1_data_8D8[grp].mdl[i].mdlId, 0.0f);
            }
            if (grp == 3 || grp == 8 || grp == 9 || grp == 11 || grp == 12 || grp == 13 || grp == 14) {
                lbl_1_data_8D8[grp].mdl[i].lightId = Hu3DLLightCreate(lbl_1_data_8D8[grp].mdl[i].mdlId, Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y,
                    Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 255, 255, 255);
                Hu3DLLightInfinitytSet(lbl_1_data_8D8[grp].mdl[i].mdlId, lbl_1_data_8D8[grp].mdl[i].lightId);
            }
            if (grp == 1 || grp == 2) {
                if (fn_1_8E88() & 0x4000) {
                    fn_1_8D04(0x42C, lbl_1_data_8D8[grp].mdl[i].mdlId, 1);
                } else {
                    fn_1_8D04(0x319, lbl_1_data_8D8[grp].mdl[i].mdlId, 1);
                }
            }
            return i;
        }
    }
    return -1;
}

/* 66 insns */
void fn_1_3F278(s32 grp, s32 idx)
{
    lbl_1_data_8D8[grp].mdl[idx].unk4 = 0;
    Hu3DModelAttrSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, HU3D_ATTR_DISPOFF);
    if (lbl_1_data_8D8[grp].mdl[idx].lightId != -1) {
        Hu3DLLightKill(lbl_1_data_8D8[grp].mdl[idx].mdlId, lbl_1_data_8D8[grp].mdl[idx].lightId);
        lbl_1_data_8D8[grp].mdl[idx].lightId = -1;
    }
}

/* 22 insns */
void fn_1_3F380(s32 grp, s32 idx, s32 bit)
{
    Hu3DModelCameraSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, bit);
}

/* 48 insns */
void fn_1_3F3D8(s32 grp, s32 idx, HuVecF pos)
{
    if (grp == 18) {
        pos.y -= 12.0f;
    }
    if (grp == 4) {
        pos.y += 150.0f;
    }
    if (grp == 3) {
        pos.y += 100.0f;
    }
    Hu3DModelPosSetV(lbl_1_data_8D8[grp].mdl[idx].mdlId, &pos);
}

/* 21 insns */
void fn_1_3F498(s32 grp, s32 idx, HuVecF rot)
{
    Hu3DModelRotSetV(lbl_1_data_8D8[grp].mdl[idx].mdlId, &rot);
}

/* 21 insns */
void fn_1_3F4EC(s32 grp, s32 idx, u32 attr)
{
    Hu3DModelAttrSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, attr);
}

/* 21 insns */
void fn_1_3F540(s32 grp, s32 idx, u32 attr)
{
    Hu3DModelAttrReset(lbl_1_data_8D8[grp].mdl[idx].mdlId, attr);
}

/* 49 insns */
void fn_1_3F594(s32 grp, s32 idx, float speed)
{
    if (lbl_1_data_8D8[grp].unk4 == 1) {
        Hu3DMotionSpeedSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, speed);
    } else if (lbl_1_data_8D8[grp].unk4 == 0) {
        Hu3DMotionShapeSpeedSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, speed);
    }
}

/* 22 insns */
void fn_1_3F658(s32 grp, s32 idx, s32 layer)
{
    Hu3DModelLayerSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, layer);
}

/* 25 insns */
void fn_1_3F6B0(s32 grp, s32 idx, HuVecF scale)
{
    Hu3DModelScaleSet(lbl_1_data_8D8[grp].mdl[idx].mdlId, scale.x, scale.y, scale.z);
}

/* 10 insns */
s32 fn_1_3F714(s32 grp, s32 idx)
{
    return lbl_1_data_8D8[grp].mdl[idx].unk4 ^ 1;
}

/* 285 insns */
void fn_1_3F73C(void)
{
    Mtx mtx;
    HuVecF dir;
    float angle;
    float maxTime;
    s32 i;
    s32 j;

    for (i = 0; i < 26; i++) {
        for (j = 0; j < lbl_1_data_8D8[i].num; j++) {
            if (lbl_1_data_8D8[i].mdl[j].unk4 == 0) {
                continue;
            }
            if (++lbl_1_data_8D8[i].mdl[j].unk8 < 3) {
                continue;
            }
            if (i == 3 || i == 4 || i == 19 || i == 20 || i == 21) {
                VECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &dir);
                VECNormalize(&dir, &dir);
                angle = 180.0 * (atan2(dir.x, dir.z) / M_PI);
                Hu3DData[lbl_1_data_8D8[i].mdl[j].mdlId].rot.y = angle;
                MTXIdentity(mtx);
                MTXRotRad(mtx, 'y', MTXDegToRad(-angle));
                MTXMultVec(mtx, &dir, &dir);
                angle = -(180.0 * (atan2(dir.y, dir.z) / M_PI));
                if (angle < -45.0f) {
                    angle = -45.0f;
                }
                Hu3DData[lbl_1_data_8D8[i].mdl[j].mdlId].rot.x = angle;
            }
            if (lbl_1_data_8D8[i].unk4 == 1) {
                if (Hu3DMotionEndCheck(lbl_1_data_8D8[i].mdl[j].mdlId)) {
                    lbl_1_data_8D8[i].mdl[j].unk4 = 0;
                }
            } else if (lbl_1_data_8D8[i].unk4 == 0) {
                angle = Hu3DData[lbl_1_data_8D8[i].mdl[j].mdlId].motShapeWork.time;
                maxTime = Hu3DMotionShapeMaxTimeGet(lbl_1_data_8D8[i].mdl[j].mdlId);
                if (angle >= maxTime) {
                    lbl_1_data_8D8[i].mdl[j].unk4 = 0;
                }
            }
            if (lbl_1_data_8D8[i].mdl[j].unk4 == 0 && lbl_1_data_8D8[i].unk8 == 1) {
                lbl_1_data_8D8[i].mdl[j].unk4 = 0;
                Hu3DModelAttrSet(lbl_1_data_8D8[i].mdl[j].mdlId, HU3D_ATTR_DISPOFF);
                if (lbl_1_data_8D8[i].mdl[j].lightId != -1) {
                    Hu3DLLightKill(lbl_1_data_8D8[i].mdl[j].mdlId, lbl_1_data_8D8[i].mdl[j].lightId);
                    lbl_1_data_8D8[i].mdl[j].lightId = -1;
                }
            }
        }
    }
}

/* 40 insns */
void fn_1_3FBB0(float a0, float a1, float a2)
{
    s32 i;
    s32 j;

    for (i = 0; i < 26; i++) {
        for (j = 0; j < lbl_1_data_8D8[i].num; j++) {
            Hu3DModelAmbSet(lbl_1_data_8D8[i].mdl[j].mdlId, a0, a1, a2);
        }
    }
}

/* 67 insns */
s32 fn_1_3FC50(CardGameWork *work)
{
    switch (lbl_1_bss_1168[2]) {
        case 0:
            memset(&lbl_1_bss_18DC, 0, sizeof(CardStatus18DC));
            lbl_1_bss_1168[2]++;
            break;
        case 1:
            fn_1_3FDF0(work);
            break;
        case 2:
            fn_1_40F14(work);
            break;
        case 3:
            fn_1_414AC(work);
            break;
        case 4:
            fn_1_424A0(work);
            break;
        default:
            lbl_1_bss_1168[2] = 0;
            return 1;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
    return 0;
}

/* 37 insns */
void fn_1_3FD5C(void)
{
    Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[1], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSetV(lbl_1_bss_18DC.unk0[1], &Hu3DData[lbl_1_bss_18DC.unk0[0]].pos);
    Hu3DMotionTimeSet(lbl_1_bss_18DC.unk0[1], 0.0f);
    fn_1_8D04(0x319, lbl_1_bss_18DC.unk0[1], 2);
}

/* 1097 insns */
void fn_1_3FDF0(CardGameWork *work)
{
    Mtx mtx;
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF dir;
    HuVecF pos;
    CardPlayerWork *player;
    s32 i;
    float scale;

    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_18DC.unk4C) {
        case 0:
            lbl_1_bss_18DC.unk60 = 0;
            lbl_1_bss_18DC.unk5C = -1;
            fn_1_9C74(&lbl_1_bss_18DC.unk1C, player->unk10, player->unk14, 1, 1);
            lbl_1_bss_18DC.unk1C.x += -50.0f;
            for (i = 0; i < 3; i++) {
                lbl_1_bss_18DC.unk6[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[i + 33], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSet(lbl_1_bss_18DC.unk6[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk6[i], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk6[i], HU3D_ATTR_ZCMP_OFF);
                Hu3DModelLayerSet(lbl_1_bss_18DC.unk6[i], 7);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk6[i], HU3D_CAM1);
                Hu3DModelScaleSet(lbl_1_bss_18DC.unk6[i], 0.0625f, 0.0375f, 0.0625f);
            }
            for (i = 0; i < 3; i++) {
                lbl_1_bss_18DC.unk0[i] = Hu3DModelCreate((void *)HuDataSelHeapReadNum(lbl_1_data_3AC[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSetV(lbl_1_bss_18DC.unk0[i], &lbl_1_bss_18DC.unk1C);
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[i], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[i], HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(lbl_1_bss_18DC.unk0[i], 3);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[i], HU3D_CAM0);
            }
            Hu3DModelPosSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unk1C.x, lbl_1_bss_18DC.unk1C.y - 50.0f, lbl_1_bss_18DC.unk1C.z);
            Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[2], HU3D_CAM1);
            Hu3DModelScaleSet(lbl_1_bss_18DC.unk0[2], 1.0f, 1.0f, 1.0f);
            Hu3DModelMatHookSet(lbl_1_bss_18DC.unk0[2], fn_1_4E8E8);
            for (i = 0; i < 6; i++) {
                lbl_1_bss_18DC.unkC[i] = Hu3DJointMotion(lbl_1_bss_18DC.unk0[0], HuDataSelHeapReadNum(lbl_1_data_3B8[i], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            Hu3DMotionSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[0]);
            Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[2], HU3D_ATTR_DISPOFF);
            pos = Hu3DCamera[0].pos;
            pos.y -= 1400.0f;
            fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
            lbl_1_bss_18DC.unk18 = Hu3DLLightCreate(lbl_1_bss_18DC.unk0[0], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 0x80, 0x80, 0x80);
            Hu3DLLightInfinitytSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unk18);
            Hu3DLLightStaticSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unk18, TRUE);
            Hu3DModelScaleSet(lbl_1_bss_18DC.unk0[1], 0.9f, 0.9f, 0.9f);
            Hu3DModelCameraSet(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_CAM1);
            lbl_1_bss_18DC.unk4C++;
            fn_1_8D04(0x449, lbl_1_bss_478[player->unk10][player->unk14], 1);
            break;
        case 1:
            lbl_1_bss_18DC.unk54 += 2;
            if (lbl_1_bss_18DC.unk54 > 90) {
                lbl_1_bss_18DC.unk54 = 90;
            }
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_18DC.unk54 }, (HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_18DC.unk54 });
            if (fn_1_318E4()) {
                lbl_1_bss_18DC.unk54 = 90;
                Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[0], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM0 | HU3D_CAM1);
                Hu3DMotionTimeSet(lbl_1_bss_18DC.unk0[0], 0.0f);
                lbl_1_bss_18DC.unk28 = lbl_1_bss_18DC.unk1C;
                lbl_1_bss_18DC.unk4C++;
            }
            break;
        case 2:
            if (lbl_1_bss_18DC.unk54 == 80) {
                fn_1_8D04(0x419, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            lbl_1_bss_18DC.unk54--;
            if (!Hu3DMotionEndCheck(lbl_1_bss_18DC.unk0[0])) {
                lbl_1_bss_18DC.unk28.y = 150.0f - 200.0f * fn_1_4EEA0(0, lbl_1_bss_18DC.unk54 / 90.0f);
            }
            Hu3DModelPosSetV(lbl_1_bss_18DC.unk0[0], &lbl_1_bss_18DC.unk28);
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_18DC.unk54 }, (HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_18DC.unk54 });
            if (lbl_1_bss_18DC.unk54 == 60) {
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM1);
            }
            if (lbl_1_bss_18DC.unk54 <= 0) {
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[2], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM0);
                lbl_1_bss_18DC.unk34 = Hu3DCamera[0].pos;
                PSVECSubtract(&Hu3DData[lbl_1_bss_18DC.unk0[0]].pos, &Hu3DCamera[0].pos, &dir);
                lbl_1_bss_18DC.unk64 = PSVECMag(&dir);
                PSVECSubtract(&Hu3DCamera[0].target, &Hu3DCamera[0].pos, &pos);
                PSVECNormalize(&pos, &pos);
                PSVECScale(&pos, &pos, lbl_1_bss_18DC.unk64);
                PSVECAdd(&pos, &Hu3DCamera[0].pos, &Hu3DCamera[0].target);
                lbl_1_bss_18DC.unk58 = 0;
                for (i = 0; i < 4; i++) {
                    lbl_1_bss_18DC.unk58 += work->player[i].unk44 + work->player[i].unk48 + work->player[i].unk4C;
                }
                lbl_1_bss_18DC.unk58 -= work->player[work->unk174[work->unk170]].unk44 + work->player[work->unk174[work->unk170]].unk48 + work->player[work->unk174[work->unk170]].unk4C;
                Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[5], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                for (i = 0; i < 4; i++) {
                    if (!(work->player[i].unk50 & 0x200)) {
                        if (work->player[i].unk50 & 2) {
                            fn_1_3F4EC(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                        if (work->player[i].unk50 & 4) {
                            fn_1_3F4EC(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                    }
                }
                if (180.0f != player->unk18) {
                    if (player->unk50 & 2) {
                        fn_1_3F540(3, player->unk56, HU3D_ATTR_DISPOFF);
                    }
                    if (player->unk50 & 4) {
                        fn_1_3F540(4, player->unk56, HU3D_ATTR_DISPOFF);
                    }
                }
                lbl_1_bss_18DC.unk54 = 0;
                lbl_1_bss_18DC.unk4C++;
            }
            break;
        case 3:
            scale = 1.0f - lbl_1_bss_18DC.unk54 / 60.0f;
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                }
            }
            if (180.0f != player->unk18) {
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            }
            lbl_1_bss_18DC.unk54++;
            PSVECSubtract(&lbl_1_bss_18DC.unk34, &Hu3DCamera[0].target, &pos);
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'x', 0.017453292f * (85.0f * fn_1_4EEA0(2, lbl_1_bss_18DC.unk54 / 60.0f)));
            PSMTXMultVec(mtx, &pos, &pos);
            PSVECAdd(&pos, &Hu3DCamera[0].target, &Hu3DCamera[0].pos);
            if (lbl_1_bss_18DC.unk54 >= 60.0f) {
                fn_1_8D04(0x272, lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_18DC.unk4C = 0;
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 0x12);
                if (lbl_1_bss_18DC.unk58 == 0) {
                    lbl_1_bss_18DC.unk54 = lbl_1_bss_18DC.unk4C = 0;
                    lbl_1_bss_12A8.unk28 = 60;
                    fn_1_4FBC8(work, 0x13);
                    lbl_1_bss_1168[2] = 4;
                }
                else {
                    lbl_1_bss_1168[2] = 2;
                }
            }
            Hu3DModelCameraSet(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_CAM0);
            break;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
}

/* 354 insns */
void fn_1_40F14(CardGameWork *work)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    s32 cnt;
    s32 i;
    s32 ret;

    switch (lbl_1_bss_18DC.unk4C) {
        case 0:
            Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[1], 0.0f, 40.0f, HU3D_MOTATTR_NONE);
            Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM1);
            Hu3DZClearLayerSet(15);
            lbl_1_bss_18DC.unk4C++;
            break;
        case 1:
            if (lbl_1_bss_18DC.unkC[1] == Hu3DData[lbl_1_bss_18DC.unk0[0]].motId && Hu3DMotionTimeGet(lbl_1_bss_18DC.unk0[0]) >= 115.0f) {
                Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[1], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[1], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSetV(lbl_1_bss_18DC.unk0[1], &Hu3DData[lbl_1_bss_18DC.unk0[0]].pos);
                Hu3DMotionTimeSet(lbl_1_bss_18DC.unk0[1], 0.0f);
                lbl_1_bss_18DC.unk4C++;
                fn_1_8D04(0x319, lbl_1_bss_18DC.unk0[1], 2);
            }
            break;
        case 2:
            cnt = 0;
            if (Hu3DMotionTimeGet(lbl_1_bss_18DC.unk0[0]) >= 118.0f) {
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[0], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM0);
                Hu3DLayerHookSet(15, NULL);
                cnt++;
            }
            if (Hu3DMotionTimeGet(lbl_1_bss_18DC.unk0[1]) >= 12.0f) {
                lbl_1_bss_18DC.unk54 = 0;
                lbl_1_bss_18DC.unk4C++;
                lbl_1_bss_BF4 = Hu3DData[lbl_1_bss_18DC.unk0[0]].pos;
                lbl_1_bss_C00 = 0.38f;
                lbl_1_bss_BE8 = lbl_1_bss_18DC.unk0[1];
                lbl_1_bss_1168[1] = 0;
            }
            break;
        case 3:
            ret = fn_1_227A4(0, work);
            if (ret != 0) {
                if (ret == 1) {
                    lbl_1_bss_18DC.unk60 = 1;
                }
                lbl_1_bss_18DC.unk54 = 0;
                lbl_1_bss_18DC.unk4C++;
            }
            break;
        case 4:
            if (Hu3DMotionTimeGet(lbl_1_bss_18DC.unk0[1]) >= 10.0f) {
                for (i = 0; i < 3; i++) {
                    Hu3DModelAttrSet(lbl_1_bss_1050[i], HU3D_ATTR_DISPOFF);
                }
                Hu3DMotionSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[2]);
                Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[0], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_18DC.unk0[0], 0.0f);
                lbl_1_bss_18DC.unk4C++;
                fn_1_8D04(0x319, lbl_1_bss_18DC.unk0[1], 2);
            }
            break;
        case 5:
            cnt = 0;
            if (Hu3DMotionEndCheck(lbl_1_bss_18DC.unk0[0])) {
                cnt++;
            }
            if (Hu3DMotionEndCheck(lbl_1_bss_18DC.unk0[1])) {
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[1], HU3D_ATTR_DISPOFF);
                cnt++;
            }
            if (cnt == 2) {
                lbl_1_bss_18DC.unk54 = lbl_1_bss_18DC.unk4C = 0;
                if (lbl_1_bss_18DC.unk5C != -1) {
                    lbl_1_bss_1168[2] = 3;
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[5], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                    if (lbl_1_bss_18DC.unk60 == 0) {
                        lbl_1_bss_12A8.unk28 = 60;
                        fn_1_4FBC8(work, 0x14);
                    }
                    lbl_1_bss_1168[2] = 4;
                }
            }
            break;
    }
}

/* 4 insns */
void fn_1_4149C(s32 a0)
{
    lbl_1_bss_18DC.unk5C = a0;
}

/* 1021 insns */
void fn_1_414AC(CardGameWork *work)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    HuVecF start;
    HuVecF end;
    s32 i;
    s32 j;
    float t;

    switch (lbl_1_bss_18DC.unk4C) {
        case 0:
            lbl_1_bss_18DC.unk60 = 1;
            Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM1);
            Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            lbl_1_bss_18DC.unk54 = 0;
            for (j = 1; j < 4; j++) {
                if ((&work->player[lbl_1_bss_18DC.unk5C].unk40)[j] != 0) {
                    lbl_1_bss_18DC.unk58 = j - 1;
                    break;
                }
            }
            lbl_1_bss_18DC.unk1A = Hu3DLLightCreate(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 0xFF, 0xFF, 0xFF);
            Hu3DLLightInfinitytSet(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], lbl_1_bss_18DC.unk1A);
            Hu3DLLightStaticSet(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], lbl_1_bss_18DC.unk1A, TRUE);
            Hu3DModelAttrReset(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], HU3D_ATTR_DISPOFF);
            Hu3DModelRotSet(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], 90.0f, 0.0f, 0.0f);
            for (i = 0; ; i++) {
                if (work->unk174[i] == lbl_1_bss_18DC.unk5C) {
                    break;
                }
            }
            start = (HuVecF) { ((float(*)[2])lbl_1_data_528)[i][0] - 7.0f, ((float(*)[2])lbl_1_data_528)[i][1] - 12.0f, 0.0f };
            for (i = 0; ; i++) {
                if (work->unk174[i] == work->unk174[work->unk170]) {
                    break;
                }
            }
            end = (HuVecF) { ((float(*)[2])lbl_1_data_528)[i][0] - 7.0f, ((float(*)[2])lbl_1_data_528)[i][1] - 12.0f, 0.0f };
            fn_1_4F144(0, start, end, 0x78, 420.0f, 0x155);
            lbl_1_bss_18DC.unk54 = 0;
            lbl_1_bss_18DC.unk4C++;
        case 1:
            if (lbl_1_bss_18DC.unk54 == 4) {
                fn_1_8D04(0x456, lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], 1);
            }
            else {
                fn_1_8D04(0x8456, lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], 1);
            }
            if (fn_1_4F1EC(0, &start) != 0) {
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], HU3D_ATTR_DISPOFF);
                (&work->player[lbl_1_bss_18DC.unk5C].unk40)[lbl_1_bss_18DC.unk58 + 1]--;
                (&work->player[work->unk174[work->unk170]].unk40)[lbl_1_bss_18DC.unk58 + 1]++;
                work->player[lbl_1_bss_18DC.unk5C].unk40 = work->player[lbl_1_bss_18DC.unk5C].unk44 + work->player[lbl_1_bss_18DC.unk5C].unk48 * 2 + work->player[lbl_1_bss_18DC.unk5C].unk4C * -1;
                work->player[work->unk174[work->unk170]].unk40 = work->player[work->unk174[work->unk170]].unk44 + work->player[work->unk174[work->unk170]].unk48 * 2 + work->player[work->unk174[work->unk170]].unk4C * -1;
                if (lbl_1_bss_18DC.unk58 != 2) {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_18DC.unk5C], lbl_1_bss_430[lbl_1_bss_18DC.unk5C][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x1F6;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1E2;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x25A;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2AA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x282;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1BA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x296;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_18DC.unk5C], lbl_1_bss_430[lbl_1_bss_18DC.unk5C][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x200;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1EC;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x264;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2B4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x28C;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1C4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x2A0;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                fn_1_2FFAC(work);
                HuAudFXPlay(8);
                if (lbl_1_bss_18DC.unk58 == 1) {
                    lbl_1_bss_18DC.unk54 = 0;
                }
                lbl_1_bss_18DC.unk4C++;
            }
            t = fn_1_4EEA0(5, lbl_1_bss_18DC.unk54 / 120.0f);
            Hu3DData[lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58]].rot.y += 30.0f - 26.0f * t;
            Hu3DModelScaleSet(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], 0.0625f * (1.0f + 3.0f * t), 0.0375f * (1.0f + 3.0f * t), 0.0625f * (1.0f + 3.0f * t));
            lbl_1_bss_18DC.unk54++;
            end = Hu3DCamera[0].pos;
            end.z -= lbl_1_bss_18DC.unk64;
            Hu3DData[lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58]].pos = fn_1_4EDB8(end, start.x, start.y);
            break;
        case 2:
            if (lbl_1_bss_18DC.unk58 == 1) {
                if (++lbl_1_bss_18DC.unk54 == 20) {
                    HuAudFXPlay(8);
                }
                if (lbl_1_bss_18DC.unk54 < 20) {
                    break;
                }
            }
            if (Hu3DMotionEndCheck(lbl_1_bss_18DC.unk0[0]) != 0) {
                Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[5], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                Hu3DLLightKill(lbl_1_bss_18DC.unk6[lbl_1_bss_18DC.unk58], lbl_1_bss_18DC.unk1A);
                Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM0);
                lbl_1_bss_18DC.unk54 = lbl_1_bss_18DC.unk4C = 0;
                lbl_1_bss_1168[2] = 4;
            }
            break;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
}

/* 655 insns */
void fn_1_424A0(CardGameWork *work)
{
    HuVecF up = { 0.0f, 1.0f, 0.0f };
    CardPlayerWork *player;
    s32 i;
    float scale;

    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_18DC.unk4C) {
        case 0:
            if (lbl_1_bss_18DC.unk60 == 1) {
                fn_1_8D04(0x272, lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 0x15);
            }
            lbl_1_bss_18DC.unk54 = 0;
            lbl_1_bss_18DC.unk4C++;
            lbl_1_bss_18DC.unk28 = Hu3DData[lbl_1_bss_18DC.unk0[0]].pos;
            lbl_1_bss_18DC.unk40 = Hu3DCamera[0].target;
            lbl_1_bss_18DC.unk34 = Hu3DCamera[0].pos;
            Hu3DMotionShiftSet(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unkC[3], 0.0f, 25.0f, HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(lbl_1_bss_18DC.unk0[2], HU3D_ATTR_DISPOFF);
            Hu3DModelPosSet(lbl_1_bss_18DC.unk0[2], lbl_1_bss_18DC.unk1C.x, lbl_1_bss_18DC.unk1C.y, lbl_1_bss_18DC.unk1C.z);
            Hu3DModelCameraSet(lbl_1_bss_18DC.unk0[0], HU3D_CAM0 | HU3D_CAM1);
            fn_1_8D04(0x449, lbl_1_bss_478[player->unk10][player->unk14], 1);
            break;
        case 1:
            if (lbl_1_bss_18DC.unk54 == 10) {
                fn_1_8D04(0x41A, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            if (lbl_1_bss_18DC.unk54 <= 90) {
                Hu3DCamera[0].target.y = lbl_1_bss_18DC.unk40.y - 50.0f * fn_1_4EEA0(2, lbl_1_bss_18DC.unk54 / 90.0f);
                Hu3DCamera[0].pos.y = lbl_1_bss_18DC.unk34.y + 50.0f * fn_1_4EEA0(2, lbl_1_bss_18DC.unk54 / 90.0f);
            }
            Hu3DCamera[1] = Hu3DCamera[0];
            lbl_1_bss_18DC.unk54++;
            lbl_1_bss_18DC.unk28.y -= 1.5f;
            Hu3DModelPosSetV(lbl_1_bss_18DC.unk0[0], &lbl_1_bss_18DC.unk28);
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.001f * lbl_1_bss_18DC.unk54 }, (HuVecF) { 0.0f, 0.0f, 0.001f * lbl_1_bss_18DC.unk54 });
            if (lbl_1_bss_18DC.unk54 >= 120) {
                lbl_1_bss_18DC.unk54 = 120;
                lbl_1_bss_18DC.unk4C++;
            }
            break;
        case 2:
            lbl_1_bss_18DC.unk54--;
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.001f * lbl_1_bss_18DC.unk54 }, (HuVecF) { 0.0f, 0.0f, 0.001f * lbl_1_bss_18DC.unk54 });
            if (lbl_1_bss_18DC.unk54 <= 0) {
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[2], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_18DC.unk0[0], HU3D_ATTR_DISPOFF);
                lbl_1_bss_18DC.unk54 = 0;
                Hu3DLLightKill(lbl_1_bss_18DC.unk0[0], lbl_1_bss_18DC.unk18);
                Hu3DMotionSet(lbl_1_bss_18DC.unk0[0], HU3D_MOTID_NONE);
                for (i = 0; i < 6; i++) {
                    Hu3DMotionKill(lbl_1_bss_18DC.unkC[i]);
                }
                for (i = 0; i < 3; i++) {
                    Hu3DModelKill(lbl_1_bss_18DC.unk6[i]);
                }
                for (i = 0; i < 3; i++) {
                    Hu3DModelKill(lbl_1_bss_18DC.unk0[i]);
                }
                lbl_1_bss_18DC.unk4C++;
            }
            break;
        case 3:
            lbl_1_bss_18DC.unk54++;
            scale = lbl_1_bss_18DC.unk54 / 30.0f;
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                }
            }
            if (180.0f != player->unk18) {
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            }
            if (lbl_1_bss_18DC.unk54 >= 30) {
                for (i = 0; i < 4; i++) {
                    if (!(work->player[i].unk50 & 0x200)) {
                        if (work->player[i].unk50 & 2) {
                            fn_1_3F540(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                        if (work->player[i].unk50 & 4) {
                            fn_1_3F540(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelScaleSet(lbl_1_bss_468[i], 1.0f, 1.0f, 1.0f);
                    }
                }
                fn_1_317F0(&Hu3DCamera[0].pos, &Hu3DCamera[0].pos, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
                lbl_1_bss_18DC.unk4C = 0;
                lbl_1_bss_1168[2]++;
            }
            break;
    }
}

/* 0xA78 */ HuVecF lbl_1_data_A78[4][2] = { { { -50.0f, 300.0f, -1200.0f }, { -50.0f, 125.0f, 0.0f } }, { { -300.0f, 150.0f, -1000.0f }, { -50.0f, 125.0f, -200.0f } }, { { 300.0f, 150.0f, -1000.0f }, { 0.0f, 125.0f, -200.0f } }, { { 0.0f, 150.0f, -400.0f }, { 0.0f, 225.0f, 0.0f } } };

/* 4699 insns */
s32 fn_1_42EDC(CardGameWork *work)
{
    s32 ret = 0;
    HuVecF pos = { 0.0f, 1.0f, 0.0f };
    CardPlayerWork *player = &work->player[work->unk174[work->unk170]];
    Mtx mtx;
    HuVecF rot;
    HuVecF ofs;
    HuVecF target;
    CardPlayerWork *other;
    s32 i;
    s32 j;
    s32 n;
    float scale;

    switch (lbl_1_bss_1168[1]) {
        case 0:
            lbl_1_bss_1848.unk78[0] = lbl_1_bss_1848.unk78[1] = lbl_1_bss_1848.unk78[2] = -1;
            lbl_1_bss_1848.unk8C = -1;
            fn_1_9C74(&lbl_1_bss_1848.unk14, player->unk10, player->unk14, 1, 1);
            lbl_1_bss_1848.unk14.x += -50.0f;
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            pos = lbl_1_data_A78[0][0];
            target = lbl_1_data_A78[0][1];
            PSMTXMultVec(mtx, &pos, &pos);
            PSVECAdd(&lbl_1_bss_1848.unk14, &pos, &pos);
            PSMTXMultVec(mtx, &target, &target);
            PSVECAdd(&lbl_1_bss_1848.unk14, &target, &target);
            fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &target);
            pos = (HuVecF) { 0.0f, 0.0f, 1.0f };
            PSMTXMultVec(mtx, &pos, &pos);
            for (i = 0; i < 3; i++) {
                lbl_1_bss_1848.unk6[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[i + 0x21], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSet(lbl_1_bss_1848.unk6[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_1848.unk6[i], HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(lbl_1_bss_1848.unk6[i], 3);
                Hu3DModelCameraSet(lbl_1_bss_1848.unk6[i], HU3D_CAM0);
                Hu3DModelScaleSet(lbl_1_bss_1848.unk6[i], 0.5f, 0.3f, 0.5f);
            }
            for (i = 0; i < 3; i++) {
                lbl_1_bss_1848.unk0[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_3D0[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSet(lbl_1_bss_1848.unk0[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[i], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[i], HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(lbl_1_bss_1848.unk0[i], 3);
                Hu3DModelCameraSet(lbl_1_bss_1848.unk0[i], HU3D_CAM0);
            }
            Hu3DModelCameraSet(lbl_1_bss_1848.unk0[2], HU3D_CAM1);
            Hu3DModelMatHookSet(lbl_1_bss_1848.unk0[2], fn_1_4E8E8);
            for (i = 0; i < 4; i++) {
                lbl_1_bss_1848.unkC[i] = Hu3DJointMotion(lbl_1_bss_1848.unk0[0], HuDataSelHeapReadNum(lbl_1_data_3DC[i], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            Hu3DMotionSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[0]);
            lbl_1_bss_1848.unk78[0] = Hu3DLLightCreate(lbl_1_bss_478[player->unk10][player->unk14], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, pos.x, pos.y, pos.z, 255, 255, 255);
            Hu3DLLightInfinitytSet(lbl_1_bss_478[player->unk10][player->unk14], lbl_1_bss_1848.unk78[0]);
            Hu3DLLightStaticSet(lbl_1_bss_478[player->unk10][player->unk14], lbl_1_bss_1848.unk78[0], TRUE);
            lbl_1_bss_1848.unk78[1] = Hu3DLLightCreate(lbl_1_bss_1848.unk0[0], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, pos.x, pos.y, pos.z, 255, 255, 255);
            Hu3DLLightInfinitytSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unk78[1]);
            Hu3DLLightStaticSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unk78[1], TRUE);
            Hu3DModelPosSetV(lbl_1_bss_1848.unk0[0], &lbl_1_bss_1848.unk14);
            Hu3DModelPosSetV(lbl_1_bss_1848.unk0[2], &lbl_1_bss_1848.unk14);
            Hu3DMotionSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[0]);
            Hu3DModelCameraSet(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_CAM1);
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    if (work->player[i].unk50 & 2) {
                        fn_1_3F4EC(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                    }
                    if (work->player[i].unk50 & 4) {
                        fn_1_3F4EC(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            if (player->unk50 & 2) {
                fn_1_3F540(3, player->unk56, HU3D_ATTR_DISPOFF);
            }
            if (player->unk50 & 4) {
                fn_1_3F540(4, player->unk56, HU3D_ATTR_DISPOFF);
            }
            if (0.0f == player->unk18) {
                lbl_1_bss_1848.unk20 = Hu3DCamera[0].pos;
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1] = 100;
            }
            else {
                lbl_1_bss_1168[1]++;
            }
            break;
        case 1:
            lbl_1_bss_1848.unk4C++;
            scale = 1.0f - lbl_1_bss_1848.unk4C / 60.0f;
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                }
            }
            Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            if (fn_1_318E4()) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1848.unk60 = lbl_1_bss_1848.unk54 = (HuVecF) { 0.0f, 0.0f, 0.0f };
                lbl_1_bss_1168[1]++;
            }
            break;
        case 2:
            lbl_1_bss_1848.unk60 = lbl_1_bss_1848.unk14;
            lbl_1_bss_1848.unk4C++;
            if (180.0f != player->unk18) {
                if (0.0f == player->unk18) {
                    lbl_1_bss_1848.unk54.y = 180.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                else if (90.0f == player->unk18) {
                    lbl_1_bss_1848.unk54.y = -90.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                else {
                    lbl_1_bss_1848.unk54.y = 90.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                lbl_1_bss_1848.unk60.y += 50.0f * fn_1_4EEA0(5, lbl_1_bss_1848.unk4C / 30.0f);
                Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk60);
                Hu3DModelRotSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk54);
                if (lbl_1_bss_1848.unk4C < 30) {
                    break;
                }
                fn_1_3ED3C(0, lbl_1_bss_1848.unk14);
                fn_1_8D04(0x454, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            lbl_1_bss_1848.unk4C = 0;
            lbl_1_bss_1168[1]++;
            break;
        case 3:
            if (++lbl_1_bss_1848.unk4C >= 15) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x41B, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            break;
        case 4:
            lbl_1_bss_1848.unk4C++;
            lbl_1_bss_1848.unk60 = (HuVecF) { 0.0f, 0.0f, 0.0f };
            lbl_1_bss_1848.unk60.y += 150.0f * fn_1_4EEA0(1, lbl_1_bss_1848.unk4C / 30.0f);
            lbl_1_bss_1848.unk60.z += 140.0f * (lbl_1_bss_1848.unk4C / 30.0f);
            if (0.0f == player->unk18) {
                lbl_1_bss_1848.unk54.x += 3.0f;
            }
            else if (90.0f == player->unk18) {
                lbl_1_bss_1848.unk54.z += 3.0f;
            }
            else if (180.0f == player->unk18) {
                lbl_1_bss_1848.unk54.x += 3.0f;
            }
            else {
                lbl_1_bss_1848.unk54.z -= 3.0f;
            }
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            PSMTXMultVec(mtx, &lbl_1_bss_1848.unk60, &lbl_1_bss_1848.unk60);
            PSVECAdd(&lbl_1_bss_1848.unk60, &lbl_1_bss_1848.unk14, &lbl_1_bss_1848.unk60);
            Hu3DModelRotSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk54);
            Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk60);
            if (lbl_1_bss_1848.unk4C >= 30) {
                lbl_1_bss_1848.unk4C = 0;
                Hu3DModelAttrReset(lbl_1_bss_1848.unk0[2], HU3D_ATTR_DISPOFF);
                Hu3DModelRotSetV(lbl_1_bss_1848.unk0[2], &lbl_1_bss_1848.unk54);
                Hu3DModelPosSetV(lbl_1_bss_1848.unk0[2], &lbl_1_bss_1848.unk60);
                Hu3DCamera[1] = Hu3DCamera[0];
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x449, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            break;
        case 5:
            lbl_1_bss_1848.unk4C++;
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_1848.unk4C }, (HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_1848.unk4C });
            if (lbl_1_bss_1848.unk4C >= 90) {
                pos = (HuVecF) { 0.0f, 0.0f, -50.0f };
                rot = (HuVecF) { 0.0f, 180.0f + player->unk18, 0.0f };
                PSMTXIdentity(mtx);
                PSMTXRotRad(mtx, 'y', 0.017453292f * (180.0f + player->unk18));
                PSMTXMultVec(mtx, &pos, &pos);
                PSVECAdd(&pos, &lbl_1_bss_1848.unk60, &pos);
                Hu3DModelPosSetV(lbl_1_bss_1848.unk0[0], &pos);
                Hu3DModelRotSetV(lbl_1_bss_1848.unk0[0], &rot);
                Hu3DModelAttrReset(lbl_1_bss_1848.unk0[0], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_1848.unk0[0], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_1848.unk0[0], HU3D_CAM0 | HU3D_CAM1);
                Hu3DMotionTimeSet(lbl_1_bss_1848.unk0[0], 0.0f);
                pos = (HuVecF) { 0.0f, 0.0f, 1.0f };
                PSMTXMultVec(mtx, &pos, &pos);
                lbl_1_bss_1848.unk6C = pos;
                lbl_1_bss_1848.unk20 = lbl_1_bss_1848.unk14;
                lbl_1_bss_1848.unk4C = 90;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 6:
            if (lbl_1_bss_1848.unk4C == 90) {
                fn_1_8D04(0x419, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            PSVECScale(&lbl_1_bss_1848.unk6C, &pos, 0.035f * lbl_1_bss_1848.unk4C);
            PSVECAdd(&pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos);
            if (lbl_1_bss_1848.unk4C == 60) {
                Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                    lbl_1_bss_20[1] = 0x1FD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                    lbl_1_bss_20[1] = 0x1E9;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                    lbl_1_bss_20[1] = 0x261;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                    lbl_1_bss_20[1] = 0x2B1;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                    lbl_1_bss_20[1] = 0x289;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                    lbl_1_bss_20[1] = 0x1C1;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                    lbl_1_bss_20[1] = 0x29D;
                }
                fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[1] = 0;
            }
            lbl_1_bss_1848.unk4C--;
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_1848.unk4C }, (HuVecF) { 0.0f, 0.0f, 0.0015f * lbl_1_bss_1848.unk4C });
            if (lbl_1_bss_1848.unk4C <= 0) {
                fn_1_8D04(0x272, lbl_1_bss_478[player->unk10][player->unk14], 1);
                Hu3DMotionShiftSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[3], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 0x16);
                lbl_1_bss_1848.unk4C = 0;
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[2], HU3D_ATTR_DISPOFF);
                Hu3DModelCameraSet(lbl_1_bss_1848.unk0[0], HU3D_CAM0);
                lbl_1_bss_1848.unk20 = Hu3DData[lbl_1_bss_1848.unk0[0]].pos;
                n = player->unk44 + player->unk48 + player->unk4C;
                if (n == 0) {
                    lbl_1_bss_12A8.unk28 = 60;
                    fn_1_4FBC8(work, 0x17);
                    Hu3DMotionShiftSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    Hu3DModelAttrReset(lbl_1_bss_1848.unk0[2], HU3D_ATTR_DISPOFF);
                    lbl_1_bss_1168[1] = 17;
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    lbl_1_bss_1168[1]++;
                }
            }
            break;
        case 7:
        case 8:
        case 9:
        case 10:
            lbl_1_bss_1848.unk4C++;
            PSVECScale(&lbl_1_bss_1848.unk6C, &pos, 5.0f);
            PSVECAdd(&pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos);
            Hu3DData[lbl_1_bss_1848.unk0[0]].pos.y = lbl_1_bss_1848.unk20.y;
            Hu3DData[lbl_1_bss_1848.unk0[0]].pos.y += 2.0f * lbl_1_bss_1848.unk4C;
            Hu3DData[lbl_1_bss_1848.unk0[0]].pos.y += 100.0f * fn_1_4EEA0(5, lbl_1_bss_1848.unk4C / 30.0f);
            if (lbl_1_bss_1168[1] == 10) {
                Hu3DCamera[0].target = Hu3DData[lbl_1_bss_1848.unk0[0]].pos;
            }
            if (lbl_1_bss_1848.unk4C >= 30) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1] += 4;
            }
            if (lbl_1_bss_1848.unk4C == 28) {
                omVibrate(work->unk174[work->unk170], (lbl_1_bss_1168[1] < 10) ? 15 : 90, 12, 0);
                HuAudFXPlay(0x453);
            }
            break;
        case 11:
        case 12:
        case 13:
        case 14:
            if (++lbl_1_bss_1848.unk4C >= 30) {
                lbl_1_bss_1848.unk4C = 0;
                if (lbl_1_bss_1168[1] < 14) {
                    Hu3DData[lbl_1_bss_1848.unk0[0]].pos = lbl_1_bss_1848.unk20;
                    Hu3DMotionTimeSet(lbl_1_bss_1848.unk0[0], 0.0f);
                    PSMTXIdentity(mtx);
                    PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
                    pos = lbl_1_data_A78[lbl_1_bss_1168[1] - 10][0];
                    target = lbl_1_data_A78[lbl_1_bss_1168[1] - 10][1];
                    PSMTXMultVec(mtx, &pos, &pos);
                    PSVECAdd(&lbl_1_bss_1848.unk14, &pos, &Hu3DCamera[0].pos);
                    PSMTXMultVec(mtx, &target, &target);
                    PSVECAdd(&lbl_1_bss_1848.unk14, &target, &Hu3DCamera[0].target);
                    if (lbl_1_bss_1168[1] == 13) {
                        Hu3DModelAttrSet(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_ATTR_DISPOFF);
                        if (player->unk50 & 2) {
                            fn_1_3F4EC(3, player->unk56, HU3D_ATTR_DISPOFF);
                        }
                        if (player->unk50 & 4) {
                            fn_1_3F4EC(4, player->unk56, HU3D_ATTR_DISPOFF);
                        }
                    }
                    lbl_1_bss_1168[1] -= 3;
                }
                else {
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    WipeColorSet(0, 0, 0);
                    lbl_1_bss_1168[1]++;
                }
            }
            break;
        case 15:
            if (WipeCheckEnd()) {
                break;
            }
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            pos = lbl_1_data_A78[0][0];
            target = lbl_1_data_A78[0][1];
            PSMTXMultVec(mtx, &pos, &pos);
            PSVECAdd(&lbl_1_bss_1848.unk14, &pos, &Hu3DCamera[0].pos);
            PSMTXMultVec(mtx, &target, &target);
            PSVECAdd(&lbl_1_bss_1848.unk14, &target, &Hu3DCamera[0].target);
            Hu3DData[lbl_1_bss_1848.unk0[0]].pos = lbl_1_bss_1848.unk20;
            Hu3DModelAttrReset(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_ATTR_DISPOFF);
            if (player->unk50 & 2) {
                fn_1_3F540(3, player->unk56, HU3D_ATTR_DISPOFF);
            }
            if (player->unk50 & 4) {
                fn_1_3F540(4, player->unk56, HU3D_ATTR_DISPOFF);
            }
            Hu3DMotionSet(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unkC[2]);
            Hu3DModelAttrSet(lbl_1_bss_1848.unk0[0], HU3D_MOTATTR_PAUSE);
            Hu3DMotionTimeSet(lbl_1_bss_1848.unk0[0], 0.0f);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
            WipeColorSet(0, 0, 0);
            lbl_1_bss_1168[1]++;
            break;
        case 16:
            if (WipeCheckEnd()) {
                break;
            }
            n = player->unk44 + player->unk48 + player->unk4C;
            Hu3DModelAttrReset(lbl_1_bss_1848.unk0[0], HU3D_MOTATTR_PAUSE);
            n = frandmod(n);
            if (n < player->unk44) {
                lbl_1_bss_1848.unk8C = 0;
            }
            else if (n - player->unk44 < player->unk48) {
                lbl_1_bss_1848.unk8C = 1;
            }
            else {
                lbl_1_bss_1848.unk8C = 2;
            }
            PSVECScale(&lbl_1_bss_1848.unk6C, &pos, -1.0f);
            lbl_1_bss_1848.unk78[2] = Hu3DLLightCreate(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, pos.x, pos.y, pos.z, 255, 255, 255);
            Hu3DLLightInfinitytSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], lbl_1_bss_1848.unk78[2]);
            Hu3DLLightStaticSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], lbl_1_bss_1848.unk78[2], TRUE);
            lbl_1_bss_1168[1] = 19;
            break;
        case 17:
            if (lbl_1_bss_1848.unk4C == 0) {
                fn_1_8D04(0x449, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            if (lbl_1_bss_1848.unk4C == 10) {
                fn_1_8D04(0x41A, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            lbl_1_bss_1848.unk4C++;
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.002f * lbl_1_bss_1848.unk4C }, (HuVecF) { 0.0f, 0.0f, 0.002f * lbl_1_bss_1848.unk4C });
            PSVECScale(&lbl_1_bss_1848.unk6C, &pos, -0.06f * lbl_1_bss_1848.unk4C);
            PSVECAdd(&pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos, &Hu3DData[lbl_1_bss_1848.unk0[0]].pos);
            if (lbl_1_bss_1848.unk4C <= 30) {
                Hu3DData[lbl_1_bss_1848.unk0[0]].rot.y += 6.0f;
            }
            if (lbl_1_bss_1848.unk4C >= 80) {
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[0], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1168[1]++;
            }
            break;
        case 18:
            lbl_1_bss_1848.unk4C--;
            fn_1_4E848((HuVecF) { 0.0f, 0.0f, 0.002f * lbl_1_bss_1848.unk4C }, (HuVecF) { 0.0f, 0.0f, 0.002f * lbl_1_bss_1848.unk4C });
            if (lbl_1_bss_1848.unk4C <= 0) {
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[2], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1168[1] = 23;
            }
            break;
        case 19:
            if (Hu3DMotionTimeGet(lbl_1_bss_1848.unk0[0]) >= 20.0f) {
                Hu3DModelPosSetV(lbl_1_bss_1848.unk0[1], &Hu3DData[lbl_1_bss_1848.unk0[0]].pos);
                Hu3DModelRotSetV(lbl_1_bss_1848.unk0[1], &Hu3DData[lbl_1_bss_1848.unk0[0]].rot);
                Hu3DModelAttrReset(lbl_1_bss_1848.unk0[1], HU3D_MOTATTR_LOOP | HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(lbl_1_bss_1848.unk0[1], HU3D_ATTR_DISPOFF);
                Hu3DMotionTimeSet(lbl_1_bss_1848.unk0[1], 0.0f);
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x319, lbl_1_bss_1848.unk0[1], 2);
            }
            break;
        case 20:
            if (Hu3DMotionTimeGet(lbl_1_bss_1848.unk0[1]) >= 5.0f) {
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[0], HU3D_ATTR_DISPOFF);
            }
            if (Hu3DMotionTimeGet(lbl_1_bss_1848.unk0[1]) >= 17.0f) {
                Hu3DModelPosSetV(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], &Hu3DData[lbl_1_bss_1848.unk0[0]].pos);
                Hu3DModelRotSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], 90.0f, Hu3DData[lbl_1_bss_1848.unk0[0]].rot.y, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1168[1]++;
            }
            break;
        case 21:
            if (Hu3DMotionEndCheck(lbl_1_bss_1848.unk0[1])) {
                do {
                    lbl_1_bss_1848.unk90 = frandmod(100) / 25;
                } while (lbl_1_bss_1848.unk90 == work->unk174[work->unk170]);
                lbl_1_bss_12A8.unk28 = 60;
                lbl_1_bss_12A8.unk8[0] = fn_1_502DC(work->player[lbl_1_bss_1848.unk90].unk2C);
                fn_1_4FBC8(work, 0x18);
                lbl_1_bss_1848.unk80 = Hu3DData[lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C]].pos;
                Hu3D3Dto2D(&Hu3DData[lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C]].pos, HU3D_CAM0, &rot);
                for (j = 0;; j++) {
                    if (work->unk174[j] == lbl_1_bss_1848.unk90) {
                        break;
                    }
                }
                ofs = (HuVecF) { ((float(*)[2])lbl_1_data_528)[j][0] - 7.0f, ((float(*)[2])lbl_1_data_528)[j][1] - 12.0f, 0.0f };
                fn_1_4F144(0, rot, ofs, 60, 0.0f, 0x21);
                Hu3DModelAttrSet(lbl_1_bss_1848.unk0[1], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1848.unk50 = 1.0f;
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1]++;
                fn_1_8D04(0x353, lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], 1);
            }
            break;
        case 22:
            fn_1_8D04(0x8353, lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], 1);
            lbl_1_bss_1848.unk50 = 1.0f - 0.85f * fn_1_4EEA0(1, lbl_1_bss_1848.unk4C / 60.0f);
            Hu3DModelScaleSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], 0.5f * lbl_1_bss_1848.unk50, 0.3f * lbl_1_bss_1848.unk50, 0.5f * lbl_1_bss_1848.unk50);
            Hu3DData[lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C]].rot.y -= 10.0f + lbl_1_bss_1848.unk4C / 2.0f;
            fn_1_4F1EC(0, &pos);
            Hu3DData[lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C]].pos = fn_1_4EDB8(lbl_1_bss_1848.unk80, pos.x, pos.y);
            if (lbl_1_bss_1848.unk4C == 35) {
                Hu3DModelLayerSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], 7);
                Hu3DModelCameraSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], HU3D_CAM1);
            }
            if (++lbl_1_bss_1848.unk4C > 60) {
                Hu3DModelAttrSet(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], HU3D_ATTR_DISPOFF);
                lbl_1_bss_1848.unk4C = 0;
                (&player->unk40)[lbl_1_bss_1848.unk8C + 1]--;
                player->unk40 = player->unk44 + player->unk48 * 2 + player->unk4C * -1;
                other = &work->player[lbl_1_bss_1848.unk90];
                (&other->unk40)[lbl_1_bss_1848.unk8C + 1]++;
                other->unk40 = other->unk44 + other->unk48 * 2 + other->unk4C * -1;
                if (lbl_1_bss_1848.unk8C != 2) {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_1848.unk90], lbl_1_bss_430[lbl_1_bss_1848.unk90][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x200;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1EC;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x264;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2B4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x28C;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1C4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x2A0;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                else {
                    Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_1848.unk90], lbl_1_bss_430[lbl_1_bss_1848.unk90][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x1F6;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1E2;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x25A;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2AA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x282;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1BA;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x296;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                fn_1_2FFAC(work);
                HuAudFXPlay(8);
                if (lbl_1_bss_1848.unk8C == 1) {
                    lbl_1_bss_1848.unk4C = 0;
                }
                lbl_1_bss_1168[1]++;
            }
            break;
        case 23:
            if (lbl_1_bss_1848.unk8C == 1) {
                if (++lbl_1_bss_1848.unk4C != 20) {
                    break;
                }
                HuAudFXPlay(8);
                lbl_1_bss_1848.unk4C = 0;
            }
            if (lbl_1_bss_1848.unk8C >= 0) {
                fn_1_8D04(0x272, lbl_1_bss_478[player->unk10][player->unk14], 1);
                lbl_1_bss_12A8.unk28 = 60;
                fn_1_4FBC8(work, 0x19);
            }
            lbl_1_bss_1848.unk60 = Hu3DData[lbl_1_bss_478[player->unk10][player->unk14]].pos;
            lbl_1_bss_1848.unk54 = Hu3DData[lbl_1_bss_478[player->unk10][player->unk14]].rot;
            lbl_1_bss_1168[1]++;
            fn_1_8D04(0x41C, lbl_1_bss_478[player->unk10][player->unk14], 1);
            break;
        case 24:
            lbl_1_bss_1848.unk4C++;
            pos = (HuVecF) { 0.0f, 0.0f, 0.0f };
            pos.y -= 150.0f * fn_1_4EEA0(0, lbl_1_bss_1848.unk4C / 30.0f);
            pos.z -= 140.0f * (lbl_1_bss_1848.unk4C / 30.0f);
            if (0.0f == player->unk18) {
                lbl_1_bss_1848.unk54.x -= 3.0f;
            }
            else if (90.0f == player->unk18) {
                lbl_1_bss_1848.unk54.z -= 3.0f;
            }
            else if (180.0f == player->unk18) {
                lbl_1_bss_1848.unk54.x -= 3.0f;
            }
            else {
                lbl_1_bss_1848.unk54.z += 3.0f;
            }
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            PSMTXMultVec(mtx, &pos, &pos);
            PSVECAdd(&lbl_1_bss_1848.unk60, &pos, &pos);
            Hu3DModelRotSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk54);
            Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &pos);
            if (lbl_1_bss_1848.unk4C >= 30) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 25:
            if (++lbl_1_bss_1848.unk4C >= 15) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 26:
            lbl_1_bss_1848.unk60 = lbl_1_bss_1848.unk14;
            lbl_1_bss_1848.unk4C++;
            if (180.0f != player->unk18) {
                if (0.0f == player->unk18) {
                    lbl_1_bss_1848.unk54.y = 180.0f - 180.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                else if (90.0f == player->unk18) {
                    lbl_1_bss_1848.unk54.y = -90.0f + 90.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                else {
                    lbl_1_bss_1848.unk54.y = 90.0f - 90.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 30.0f);
                }
                lbl_1_bss_1848.unk60.y += 50.0f * fn_1_4EEA0(5, lbl_1_bss_1848.unk4C / 30.0f);
                Hu3DModelPosSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk60);
                Hu3DModelRotSetV(lbl_1_bss_478[player->unk10][player->unk14], &lbl_1_bss_1848.unk54);
                if (lbl_1_bss_1848.unk4C < 30) {
                    break;
                }
                fn_1_3ED3C(0, lbl_1_bss_1848.unk14);
                fn_1_8D04(0x454, lbl_1_bss_478[player->unk10][player->unk14], 1);
            }
            lbl_1_bss_1848.unk4C = 0;
            Hu3DLLightKill(lbl_1_bss_478[player->unk10][player->unk14], lbl_1_bss_1848.unk78[0]);
            Hu3DLLightKill(lbl_1_bss_1848.unk0[0], lbl_1_bss_1848.unk78[1]);
            if (lbl_1_bss_1848.unk78[2] != -1) {
                Hu3DLLightKill(lbl_1_bss_1848.unk6[lbl_1_bss_1848.unk8C], lbl_1_bss_1848.unk78[2]);
            }
            Hu3DMotionSet(lbl_1_bss_1848.unk0[0], HU3D_MOTID_NONE);
            for (i = 0; i < 4; i++) {
                Hu3DMotionKill(lbl_1_bss_1848.unkC[i]);
            }
            for (i = 0; i < 3; i++) {
                Hu3DModelKill(lbl_1_bss_1848.unk0[i]);
            }
            for (i = 0; i < 3; i++) {
                Hu3DModelKill(lbl_1_bss_1848.unk6[i]);
            }
            Hu3DModelCameraSet(lbl_1_bss_468[work->unk174[work->unk170]], HU3D_CAM0);
            if (0.0f == player->unk18) {
                PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &lbl_1_bss_1848.unk20);
                lbl_1_bss_1168[1] = 101;
            }
            else {
                lbl_1_bss_1168[1] = 27;
            }
            break;
        case 27:
            lbl_1_bss_1848.unk4C++;
            scale = lbl_1_bss_1848.unk4C / 30.0f;
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                }
            }
            Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            if (lbl_1_bss_1848.unk4C >= 30.0f) {
                for (i = 0; i < 4; i++) {
                    if (!(work->player[i].unk50 & 0x200)) {
                        if (work->player[i].unk50 & 2) {
                            fn_1_3F540(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                        if (work->player[i].unk50 & 4) {
                            fn_1_3F540(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                        }
                        Hu3DModelScaleSet(lbl_1_bss_468[i], 1.0f, 1.0f, 1.0f);
                    }
                }
                fn_1_317F0(&Hu3DCamera[0].pos, &Hu3DCamera[0].pos, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
                lbl_1_bss_1168[1] = 0;
                ret = 1;
            }
            break;
        case 100:
            lbl_1_bss_1848.unk4C += 3;
            Hu3DCamera[0].up = (HuVecF) { 0.0f, 0.0f, 1.0f };
            PSMTXIdentity(mtx);
            Hu3DCamera[0].pos.z -= 5.0f;
            PSMTXRotRad(mtx, 'y', 0.017453292f * (180.0f - 180.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 180.0f)));
            PSMTXMultVec(mtx, &Hu3DCamera[0].up, &Hu3DCamera[0].up);
            if (lbl_1_bss_1848.unk4C == 180) {
                Hu3DCamera[0].up = (HuVecF) { 0.0f, 1.0f, 0.0f };
                lbl_1_bss_1848.unk4C = 0;
                PSMTXIdentity(mtx);
                PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
                pos = lbl_1_data_A78[0][0];
                target = lbl_1_data_A78[0][1];
                PSMTXMultVec(mtx, &pos, &pos);
                PSVECAdd(&lbl_1_bss_1848.unk14, &pos, &pos);
                PSMTXMultVec(mtx, &target, &target);
                PSVECAdd(&lbl_1_bss_1848.unk14, &target, &target);
                fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &target);
                lbl_1_bss_1168[1] = 1;
            }
            break;
        case 101:
            lbl_1_bss_1848.unk4C += 3;
            PSMTXIdentity(mtx);
            Hu3DCamera[0].pos.z -= 5.0f;
            if (Hu3DCamera[0].target.x >= 0.0f) {
                PSMTXRotRad(mtx, 'y', 0.017453292f * (180.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 180.0f)));
            }
            else {
                PSMTXRotRad(mtx, 'y', 0.017453292f * -(180.0f * fn_1_4EEA0(2, lbl_1_bss_1848.unk4C / 180.0f)));
            }
            PSMTXMultVec(mtx, &lbl_1_bss_1848.unk20, &pos);
            PSVECAdd(&Hu3DCamera[0].target, &pos, &Hu3DCamera[0].pos);
            Hu3DCamera[0].target.x += 1.0f;
            if (lbl_1_bss_1848.unk4C >= 180) {
                lbl_1_bss_1848.unk4C = 0;
                lbl_1_bss_1168[1] = 27;
            }
            break;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
    return ret;
}

/* 152 insns */
void fn_1_47848(CardGameWork *work, float a1, float a2, float a3)
{
    HU3DMODEL *modelP;
    s32 i;
    s32 j;
    s32 k;
    u8 c;
    u8 col;

    modelP = Hu3DData;
    c = 255.0f * a1;
    for (i = 0; i < HU3D_MODEL_MAX; i++, modelP++) {
        if (modelP->hsf != 0) {
            modelP->ambR = a1;
            modelP->ambG = a2;
            modelP->ambB = a3;
        }
    }
    for (i = 0; i < 5; i++) {
        Hu3DModelAmbSet(lbl_1_bss_17AC.unk0[i], 1.0f, 1.0f, 1.0f);
    }
    Hu3DModelAmbSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
    for (k = 0; k < 26; k++) {
        for (j = 0; j < lbl_1_data_8D8[k].num; j++) {
            Hu3DModelAmbSet(lbl_1_data_8D8[k].mdl[j].mdlId, 1.0f, 1.0f, 1.0f);
        }
    }
    col = 64.0f + 0.75f * c;
    Hu3DGLightColorSet(lbl_1_bss_314, col, col, col, col);
    col = 255 - c;
    Hu3DGLightColorSet(lbl_1_bss_17AC.unk10[12], col, col, col, col);
}


/* 878 insns */
s32 fn_1_47AA8(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 i;
    s32 ret = 0;
    HuVecF pos = { 0.0f, 1.0f, 0.0f };

    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_1168[1]) {
        case 0:
            memset(&lbl_1_bss_17AC, 0, sizeof(lbl_1_bss_17AC));
            fn_1_9C74(&lbl_1_bss_17AC.unk34, player->unk10, player->unk14, 1, 1);
            lbl_1_bss_17AC.unk34.x += -50.0f;
            for (i = 0; i < 5; i++) {
                lbl_1_bss_17AC.unk0[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_3EC[i], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSet(lbl_1_bss_17AC.unk0[i], 0.0f, 0.0f, 0.0f);
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[i], HU3D_ATTR_DISPOFF);
                Hu3DModelLayerSet(lbl_1_bss_17AC.unk0[i], 3);
                Hu3DModelCameraSet(lbl_1_bss_17AC.unk0[i], 1);
            }
            for (i = 0; i < 6; i++) {
                lbl_1_bss_17AC.unk10[i] = Hu3DJointMotion(lbl_1_bss_17AC.unk0[0], HuDataSelHeapReadNum(lbl_1_data_400[i], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            Hu3DMotionSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[0]);
            for (; i < 10; i++) {
                lbl_1_bss_17AC.unk10[i] = Hu3DJointMotion(lbl_1_bss_17AC.unk0[1], HuDataSelHeapReadNum(lbl_1_data_400[i], HU_MEMNUM_OVL, HEAP_MODEL));
            }
            PSVECSubtract(&Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos, &lbl_1_bss_17AC.unk34, &pos);
            PSVECScale(&pos, &pos, 0.75f);
            PSVECAdd(&lbl_1_bss_17AC.unk34, &pos, &pos);
            pos.y += 100.0f;
            lbl_1_bss_17AC.unk10[12] = Hu3DGLightCreate(pos.x, pos.y, pos.z, 0.0f, 1.0f, 0.0f, 0, 0, 0);
            Hu3DGLightPointSet(lbl_1_bss_17AC.unk10[12], 200.0f, 1.0f, GX_DA_MEDIUM);
            Hu3DGLightStaticSet(lbl_1_bss_17AC.unk10[12], TRUE);
            lbl_1_bss_17AC.unk10[13] = Hu3DGLightCreate(pos.x, pos.y, pos.z, 0.0f, 1.0f, 0.0f, 0, 0, 0);
            Hu3DGLightPointSet(lbl_1_bss_17AC.unk10[13], 200.0f, 1.0f, GX_DA_MEDIUM);
            Hu3DGLightStaticSet(lbl_1_bss_17AC.unk10[13], TRUE);
            Hu3DMotionSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[6]);
            lbl_1_bss_17AC.unk7C = 0;
            lbl_1_bss_1168[1]++;
            break;
        case 1:
            lbl_1_bss_1168[1]++;
            break;
        case 2:
            if (fn_1_48860(work) != 0) {
                lbl_1_bss_5E = 0;
                Hu3DZClearLayerSet(15);
                lbl_1_bss_17AC.unk7C = 255;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 3:
            lbl_1_bss_17AC.unk7C -= 8;
            if (lbl_1_bss_17AC.unk7C <= 16) {
                lbl_1_bss_17AC.unk7C = 16;
                if (frandmod(10) >= 7) {
                    lbl_1_bss_1168[1]++;
                }
                else {
                    lbl_1_bss_1168[1] += 2;
                }
            }
            fn_1_47848(work, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f);
            break;
        case 4:
            if (fn_1_493F4(work) != 0) {
                if (lbl_1_bss_17AC.unk84 == 0) {
                    lbl_1_bss_1168[1] = 7;
                }
                else {
                    lbl_1_bss_1168[1]++;
                }
            }
            break;
        case 5:
            if (fn_1_4AB58(work) != 0) {
                lbl_1_bss_17AC.unk7C = 16;
                lbl_1_bss_1168[1]++;
            }
            break;
        case 6:
            if (lbl_1_bss_17AC.unk7C == 16) {
                if (lbl_1_bss_8[0] != -1) {
                    HuAudSStreamStop(lbl_1_bss_8[0]);
                    HuAudSStreamVolSet(0, 127, 1000);
                }
                lbl_1_bss_8[0] = 0;
            }
            lbl_1_bss_17AC.unk7C += 8;
            if (lbl_1_bss_17AC.unk7C >= 255) {
                lbl_1_bss_17AC.unk7C = 255;
                lbl_1_bss_1168[1]++;
            }
            fn_1_47848(work, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f);
            break;
        case 7:
            if (fn_1_48EF8(work) != 0) {
                Hu3DMotionSet(lbl_1_bss_17AC.unk0[0], -1);
                Hu3DMotionSet(lbl_1_bss_17AC.unk0[1], -1);
                for (i = 0; i < 10; i++) {
                    Hu3DMotionKill(lbl_1_bss_17AC.unk10[i]);
                }
                for (i = 0; i < 5; i++) {
                    Hu3DModelKill(lbl_1_bss_17AC.unk0[i]);
                }
                Hu3DGLightKill(lbl_1_bss_17AC.unk10[12]);
                Hu3DGLightKill(lbl_1_bss_17AC.unk10[13]);
                Hu3DLayerHookSet(15, NULL);
                lbl_1_bss_1168[1] = 0;
                ret = 1;
            }
            break;
    }
    Hu3DCamera[1] = Hu3DCamera[0];
    return ret;
}

/* 0xAF8 */ HuVecF lbl_1_data_AF8[2] = { { 1000.0f, 300.0f, -1000.0f }, { 0.0f, 150.0f, -200.0f } };

/* 422 insns */
s32 fn_1_48860(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 i;
    s32 ret;
    float scale;
    Mtx mtx;
    HuVecF pos;
    HuVecF target;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_17AC.unk70) {
        case 0:
            lbl_1_bss_17AC.unk58 = Hu3DCamera[0].pos;
            lbl_1_bss_17AC.unk64 = Hu3DCamera[0].target;
            lbl_1_bss_17AC.unk7C = 0;
            if (0.0f == player->unk18) {
                lbl_1_bss_17AC.unk90 = 130.0f;
            }
            else if (90.0f == player->unk18) {
                lbl_1_bss_17AC.unk90 = -140.0f;
            }
            else if (180.0f == player->unk18) {
                lbl_1_bss_17AC.unk90 = -50.0f;
            }
            else {
                lbl_1_bss_17AC.unk90 = 40.0f;
            }
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    if (work->player[i].unk50 & 2) {
                        fn_1_3F4EC(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                    }
                    if (work->player[i].unk50 & 4) {
                        fn_1_3F4EC(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                    }
                }
            }
            if (player->unk50 & 2) {
                fn_1_3F540(3, player->unk56, HU3D_ATTR_DISPOFF);
            }
            if (player->unk50 & 4) {
                fn_1_3F540(4, player->unk56, HU3D_ATTR_DISPOFF);
            }
            lbl_1_bss_17AC.unk70++;
            break;
        case 1:
            lbl_1_bss_17AC.unk7C++;
            Hu3DCamera[0].up = (HuVecF) { 0.0f, 0.0f, -1.0f };
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * (lbl_1_bss_17AC.unk90 * fn_1_4EEA0(2, lbl_1_bss_17AC.unk7C / 45.0f)));
            PSMTXMultVec(mtx, &Hu3DCamera[0].up, &Hu3DCamera[0].up);
            PSVECSubtract(&lbl_1_bss_17AC.unk58, &lbl_1_bss_17AC.unk64, &pos);
            pos.z += lbl_1_bss_17AC.unk7C;
            PSMTXMultVec(mtx, &pos, &pos);
            PSVECAdd(&pos, &lbl_1_bss_17AC.unk64, &Hu3DCamera[0].pos);
            scale = 1.0f - lbl_1_bss_17AC.unk7C / 45.0f;
            for (i = 0; i < 4; i++) {
                if (!(work->player[i].unk50 & 0x200)) {
                    Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                }
            }
            Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            if (lbl_1_bss_17AC.unk7C >= 45) {
                Hu3DCamera[0].up = (HuVecF) { 0.0f, 1.0f, 0.0f };
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk70++;
            }
            break;
        case 2:
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            PSMTXMultVec(mtx, &lbl_1_data_AF8[0], &pos);
            PSVECAdd(&pos, &lbl_1_bss_17AC.unk34, &pos);
            PSMTXMultVec(mtx, &lbl_1_data_AF8[1], &target);
            PSVECAdd(&target, &lbl_1_bss_17AC.unk34, &target);
            fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &target);
            lbl_1_bss_17AC.unk70++;
            break;
        case 3:
            if (fn_1_318E4() != 0) {
                lbl_1_bss_17AC.unk70 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 319 insns */
s32 fn_1_48EF8(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 i;
    s32 ret;
    float scale;
    Mtx mtx;
    HuVecF pos;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_17AC.unk70) {
        case 0:
            PSVECSubtract(&Hu3DCamera[0].pos, &Hu3DCamera[0].target, &lbl_1_bss_17AC.unk40);
            PSVECSubtract(&lbl_1_bss_17AC.unk34, &Hu3DCamera[0].target, &lbl_1_bss_17AC.unk64);
            lbl_1_bss_17AC.unk64.x -= -75.0f;
            lbl_1_bss_17AC.unk64.y += 150.0f;
            PSVECScale(&lbl_1_bss_17AC.unk64, &lbl_1_bss_17AC.unk64, 0.016666668f);
            lbl_1_bss_17AC.unk90 = 180.0 * (atan2(lbl_1_bss_17AC.unk40.z, lbl_1_bss_17AC.unk40.x) / 3.141592653589793) - 90.0;
            lbl_1_bss_17AC.unk7C = 0;
            lbl_1_bss_17AC.unk70++;
            break;
        case 1:
            lbl_1_bss_17AC.unk7C++;
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * (lbl_1_bss_17AC.unk90 * fn_1_4EEA0(2, lbl_1_bss_17AC.unk7C / 45.0f)));
            PSMTXMultVec(mtx, &lbl_1_bss_17AC.unk40, &pos);
            PSVECAdd(&lbl_1_bss_17AC.unk64, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
            PSVECAdd(&pos, &Hu3DCamera[0].target, &Hu3DCamera[0].pos);
            scale = lbl_1_bss_17AC.unk7C / 45.0f;
            if (work->unk1D4 != 10) {
                for (i = 0; i < 4; i++) {
                    if (!(work->player[i].unk50 & 0x200)) {
                        Hu3DModelScaleSet(lbl_1_bss_468[i], scale, scale, scale);
                    }
                }
                Hu3DModelScaleSet(lbl_1_bss_468[work->unk174[work->unk170]], 1.0f, 1.0f, 1.0f);
            }
            if (lbl_1_bss_17AC.unk7C >= 45) {
                if (work->unk1D4 != 10) {
                    for (i = 0; i < 4; i++) {
                        if (!(work->player[i].unk50 & 0x200)) {
                            if (work->player[i].unk50 & 2) {
                                fn_1_3F540(3, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                            }
                            if (work->player[i].unk50 & 4) {
                                fn_1_3F540(4, work->player[i].unk56, HU3D_ATTR_DISPOFF);
                            }
                            Hu3DModelScaleSet(lbl_1_bss_468[i], 1.0f, 1.0f, 1.0f);
                        }
                    }
                }
                fn_1_317F0(&Hu3DCamera[0].pos, &Hu3DCamera[0].pos, &Hu3DCamera[0].target, &Hu3DCamera[0].target);
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk70 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}


/* 1497 insns */
s32 fn_1_493F4(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 ret;
    float y;
    Mtx mtx;
    HuVecF pos;
    HuVecF target;
    HuVecF ofs;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_17AC.unk70) {
        case 0:
            Hu3DModelPosSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk34.x, 400.0f, lbl_1_bss_17AC.unk34.z);
            Hu3DModelRotSet(lbl_1_bss_17AC.unk0[1], 0.0f, 180.0f + player->unk18, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[1], HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(lbl_1_bss_17AC.unk0[1], 0.0f);
            Hu3DModelPosSet(lbl_1_bss_17AC.unk0[2], lbl_1_bss_17AC.unk34.x, 400.0f, lbl_1_bss_17AC.unk34.z);
            Hu3DModelRotSet(lbl_1_bss_17AC.unk0[2], 0.0f, 180.0f + player->unk18, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[2], HU3D_ATTR_DISPOFF);
            lbl_1_bss_17AC.unk7C = 0;
            lbl_1_bss_17AC.unk70++;
            break;
        case 1:
            lbl_1_bss_17AC.unk7C++;
            y = 400.0f - 250.0f * fn_1_4EEA0(1, lbl_1_bss_17AC.unk7C / 60.0f);
            Hu3DData[lbl_1_bss_17AC.unk0[2]].pos.y = y;
            Hu3DData[lbl_1_bss_17AC.unk0[1]].pos.y = y;
            if (lbl_1_bss_17AC.unk7C >= 60) {
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk70++;
            }
            break;
        case 2:
            PSVECSubtract(&Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos, &lbl_1_bss_17AC.unk34, &pos);
            PSVECScale(&pos, &pos, 7.0f);
            pos.y = 300.0f;
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            ofs = (HuVecF) { -75.0f, 0.0f, 0.0f };
            PSMTXMultVec(mtx, &ofs, &ofs);
            PSVECAdd(&pos, &lbl_1_bss_17AC.unk34, &pos);
            PSVECAdd(&pos, &ofs, &pos);
            target = lbl_1_bss_17AC.unk34;
            target.y += 150.0f;
            PSVECAdd(&target, &ofs, &target);
            fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &target);
            lbl_1_bss_17AC.unk7C = 0;
            lbl_1_bss_17AC.unk70++;
            break;
        case 3:
            lbl_1_bss_17AC.unk7C += 4;
            if (lbl_1_bss_17AC.unk7C >= 255) {
                lbl_1_bss_17AC.unk7C = 255;
            }
            fn_1_47848(work, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f);
            if (fn_1_318E4() != 0) {
                HuAudSStreamVolSet(0, 127, 1000);
                fn_1_8D04(0x237, lbl_1_bss_17AC.unk0[1], 1);
                lbl_1_bss_17AC.unk7C = 0;
                fn_1_4FBC8(work, 0x30);
                if (frandmod(100) < 60) {
                    lbl_1_bss_17AC.unk70++;
                }
                else {
                    lbl_1_bss_17AC.unk70 = 10;
                }
                if (fn_1_5710(work, work->unk170, 2) != 0) {
                    lbl_1_bss_17AC.unk70 = 10;
                }
            }
            break;
        case 4:
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[7], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            fn_1_4FBC8(work, 0x32);
            lbl_1_bss_17AC.unk70++;
            break;
        case 5:
            if (lbl_1_bss_17AC.unk10[7] == Hu3DData[lbl_1_bss_17AC.unk0[1]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[1])) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[6], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_17AC.unk2E[2] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[103], HU_MEMNUM_OVL, HEAP_MODEL));
                Hu3DModelPosSet(lbl_1_bss_17AC.unk2E[2], Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos.x, 400.0f,
                    Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos.z);
                Hu3DModelCameraSet(lbl_1_bss_17AC.unk2E[2], 1);
                Hu3DModelRotSet(lbl_1_bss_17AC.unk2E[2], 0.0f, 180.0f + player->unk18, 0.0f);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk2E[2], HU3D_ATTR_DISPOFF);
                lbl_1_bss_17AC.unk70++;
            }
            break;
        case 6:
            if (lbl_1_bss_20[0] == 0) {
                if (fn_1_8D04(0x319, lbl_1_bss_17AC.unk2E[2], 1) != -1) {
                    lbl_1_bss_20[0] = 1;
                }
            }
            Hu3DData[lbl_1_bss_17AC.unk2E[2]].pos.y -= 5.0f;
            if (Hu3DData[lbl_1_bss_17AC.unk2E[2]].pos.y <= 250.0f) {
                Hu3DData[lbl_1_bss_17AC.unk2E[2]].pos.y = 250.0f;
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk94 = 1.0f;
                lbl_1_bss_17AC.unk70++;
            }
            break;
        case 7:
            if (++lbl_1_bss_17AC.unk7C >= 30) {
                if (lbl_1_bss_17AC.unk7C == 30) {
                    fn_1_8D04(0x31B, lbl_1_bss_17AC.unk2E[2], 1);
                    lbl_1_bss_20[0] = 0;
                }
                Hu3DData[lbl_1_bss_17AC.unk2E[2]].pos.y -= 6.0f;
                lbl_1_bss_17AC.unk94 *= 0.85f;
                Hu3DModelScaleSet(lbl_1_bss_17AC.unk2E[2], lbl_1_bss_17AC.unk94, lbl_1_bss_17AC.unk94, lbl_1_bss_17AC.unk94);
                if (lbl_1_bss_17AC.unk7C > 45) {
                    Hu3DModelKill(lbl_1_bss_17AC.unk2E[2]);
                    if (!(player->unk50 & 4)) {
                        if (player->unk50 & 2) {
                            player->unk50 &= ~2;
                            fn_1_3F278(3, player->unk56);
                        }
                        player->unk56 = fn_1_3ED3C(4, Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos);
                        player->unk50 |= 4;
                        work->unk1D4 = 20;
                    }
                    lbl_1_bss_17AC.unk7C = 0;
                    lbl_1_bss_17AC.unk70++;
                }
            }
            break;
        case 8:
            if (++lbl_1_bss_17AC.unk7C >= 5) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[9], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                fn_1_8D04(0x237, lbl_1_bss_17AC.unk0[1], 1);
                fn_1_4FBC8(work, 0x33);
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk70++;
            }
            break;
        case 9:
            lbl_1_bss_17AC.unk7C++;
            y = 150.0f + 250.0f * fn_1_4EEA0(0, lbl_1_bss_17AC.unk7C / 60.0f);
            Hu3DData[lbl_1_bss_17AC.unk0[2]].pos.y = y;
            Hu3DData[lbl_1_bss_17AC.unk0[1]].pos.y = y;
            if (lbl_1_bss_17AC.unk7C >= 60) {
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[1], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[2], HU3D_ATTR_DISPOFF);
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk70 = 0;
                ret = 1;
                lbl_1_bss_8[0] = -1;
            }
            break;
        case 10:
            fn_1_4FBC8(work, 0x31);
            fn_1_8D04(0x236, lbl_1_bss_17AC.unk0[1], 1);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[8], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            lbl_1_bss_17AC.unk70++;
            break;
        case 11:
            if (lbl_1_bss_17AC.unk10[8] == Hu3DData[lbl_1_bss_17AC.unk0[1]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[1])) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[1], lbl_1_bss_17AC.unk10[6], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_17AC.unk4C = Hu3DData[lbl_1_bss_17AC.unk0[1]].pos;
                Hu3D3Dto2D(&Hu3DData[lbl_1_bss_17AC.unk0[1]].pos, 1, &pos);
                target = (HuVecF) { -120.0f, 140.0f, 0.0f };
                fn_1_4F144(0, pos, target, 60, 60.0f, 0x455);
                lbl_1_bss_17AC.unk7C = 255;
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk70++;
                HuAudSStreamVolSet(0, 0, 1000);
            }
            break;
        case 12:
            if (++lbl_1_bss_17AC.unk80 < 30) {
                Hu3DData[lbl_1_bss_17AC.unk0[1]].rot.y -= 1.5f;
                Hu3DData[lbl_1_bss_17AC.unk0[2]].rot.y -= 1.5f;
            }
            lbl_1_bss_17AC.unk7C -= 8;
            if (lbl_1_bss_17AC.unk7C <= 16) {
                lbl_1_bss_17AC.unk7C = 16;
            }
            fn_1_47848(work, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f, lbl_1_bss_17AC.unk7C / 255.0f);
            if (fn_1_4F1EC(0, &pos) != 0) {
                lbl_1_bss_17AC.unk70++;
            }
            Hu3DData[lbl_1_bss_17AC.unk0[1]].pos = Hu3DData[lbl_1_bss_17AC.unk0[2]].pos = fn_1_4EDB8(lbl_1_bss_17AC.unk4C, pos.x, pos.y);
            break;
        case 13:
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[2], HU3D_ATTR_DISPOFF);
            lbl_1_bss_17AC.unk70 = 0;
            lbl_1_bss_17AC.unk84 = 1;
            ret = 1;
            break;
    }
    return ret;
}


/* 826 insns */
s32 fn_1_4AB58(CardGameWork *work)
{
    CardPlayerWork *player;
    s32 ret;
    s32 endF;
    s32 rnd;
    Mtx mtx;
    HuVecF pos;
    HuVecF target;
    HuVecF ofs;

    ret = 0;
    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_17AC.unk70) {
        case 0:
            Hu3DModelPosSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk34.x, 0.0f, lbl_1_bss_17AC.unk34.z);
            Hu3DModelRotSet(lbl_1_bss_17AC.unk0[0], 0.0f, 180.0f + player->unk18, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[0], HU3D_ATTR_DISPOFF);
            Hu3DMotionTimeSet(lbl_1_bss_17AC.unk0[0], 100.0f);
            lbl_1_bss_17AC.unk70++;
            break;
        case 1:
            if (Hu3DMotionTimeGet(lbl_1_bss_17AC.unk0[0]) >= 136.0f) {
                Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                    lbl_1_bss_20[1] = 0x1FD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                    lbl_1_bss_20[1] = 0x1E9;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                    lbl_1_bss_20[1] = 0x261;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                    lbl_1_bss_20[1] = 0x2B1;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                    lbl_1_bss_20[1] = 0x289;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                    lbl_1_bss_20[1] = 0x1C1;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                    lbl_1_bss_20[1] = 0x29D;
                }
                fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[1] = 0;
                fn_1_8D04(0x2C7, lbl_1_bss_17AC.unk0[0], 1);
                fn_1_31AC0(&lbl_1_bss_E68[1], &lbl_1_bss_E68[2]);
                lbl_1_bss_F3C[0] = 50;
                lbl_1_bss_17AC.unk70++;
                omVibrate(0, 15, 12, 0);
                omVibrate(1, 15, 12, 0);
                omVibrate(2, 15, 12, 0);
                omVibrate(3, 15, 12, 0);
            }
            break;
        case 2:
            endF = 0;
            if (Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                endF = 1;
            }
            pos.x = lbl_1_bss_E68[1].x + frandmod(lbl_1_bss_F3C[0]);
            pos.y = lbl_1_bss_E68[1].y + frandmod(lbl_1_bss_F3C[0]);
            pos.z = lbl_1_bss_E68[1].z + frandmod(lbl_1_bss_F3C[0]);
            fn_1_31710(&pos);
            pos.x = lbl_1_bss_E68[2].x + frandmod(lbl_1_bss_F3C[0]);
            pos.y = lbl_1_bss_E68[2].y + frandmod(lbl_1_bss_F3C[0]);
            pos.z = lbl_1_bss_E68[2].z + frandmod(lbl_1_bss_F3C[0]);
            fn_1_31788(&pos);
            if (lbl_1_bss_F3C[0] == 5) {
                omVibrate(0, 60, 4, 2);
                omVibrate(1, 60, 4, 2);
                omVibrate(2, 60, 4, 2);
                omVibrate(3, 60, 4, 2);
            }
            lbl_1_bss_F3C[0] -= 3;
            if (lbl_1_bss_F3C[0] < 3) {
                lbl_1_bss_F3C[0] = 3;
                if (endF != 0) {
                    fn_1_31710(&lbl_1_bss_E68[1]);
                    fn_1_31788(&lbl_1_bss_E68[2]);
                    lbl_1_bss_17AC.unk7C = 0;
                    if (lbl_1_bss_17AC.unk84 == 0) {
                        lbl_1_bss_17AC.unk70++;
                    }
                    else {
                        lbl_1_bss_17AC.unk70 = 5;
                    }
                    if (lbl_1_bss_17AC.unk70 == 5) {
                        lbl_1_bss_8[0] = HuAudSStreamChanPlay(16, 2);
                    }
                }
            }
            break;
        case 3:
            PSVECSubtract(&Hu3DData[lbl_1_bss_468[work->unk174[work->unk170]]].pos, &lbl_1_bss_17AC.unk34, &pos);
            PSVECScale(&pos, &pos, 7.0f);
            pos.y = 300.0f;
            PSMTXIdentity(mtx);
            PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
            ofs = (HuVecF) { -75.0f, 0.0f, 0.0f };
            PSMTXMultVec(mtx, &ofs, &ofs);
            PSVECAdd(&pos, &lbl_1_bss_17AC.unk34, &pos);
            PSVECAdd(&pos, &ofs, &pos);
            target = lbl_1_bss_17AC.unk34;
            target.y += 150.0f;
            PSVECAdd(&target, &ofs, &target);
            fn_1_317F0(&Hu3DCamera[0].pos, &pos, &Hu3DCamera[0].target, &target);
            lbl_1_bss_17AC.unk70++;
            break;
        case 4:
            if (fn_1_318E4() != 0) {
                lbl_1_bss_17AC.unk70++;
            }
            if (lbl_1_bss_17AC.unk70 == 5) {
                lbl_1_bss_8[0] = HuAudSStreamChanPlay(16, 2);
            }
            break;
        case 5:
            fn_1_8D04(0x2C9, lbl_1_bss_17AC.unk0[0], 1);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            fn_1_4FBC8(work, 0x29);
            if (lbl_1_bss_17AC.unk10[4] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
            fn_1_4FBC8(work, 0x2A);
            if (lbl_1_bss_17AC.unk10[4] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
            }
            fn_1_4FBC8(work, 0x2B);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[2], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            fn_1_8D04(0x2CB, lbl_1_bss_17AC.unk0[0], 1);
            if (player->unk50 & 0x1000) {
                rnd = frandmod(2);
            }
            else {
                rnd = frandmod(3);
            }
            lbl_1_bss_17AC.unk78 = rnd;
            if (lbl_1_bss_17AC.unk78 == 0 && work->player[0].unk34 == -1 && work->player[1].unk34 == -1 && work->player[0].unk3C == -1
                && work->player[3].unk34 == -1) {
                lbl_1_bss_17AC.unk78 = 1;
            }
            lbl_1_bss_17AC.unk70++;
            break;
        case 6:
            if (fn_1_4B840(work) != 0) {
                lbl_1_bss_17AC.unk70 += lbl_1_bss_17AC.unk78 + 1;
            }
            break;
        case 7:
            if (fn_1_4BDD4(work) != 0) {
                lbl_1_bss_17AC.unk70 = 10;
            }
            break;
        case 8:
            if (fn_1_4C1E4(work) != 0) {
                lbl_1_bss_17AC.unk70 = 10;
            }
            break;
        case 9:
            if (fn_1_4D8C4(work) != 0) {
                lbl_1_bss_17AC.unk70 = 10;
            }
            break;
        case 10:
            if (fn_1_4E388(work) != 0) {
                lbl_1_bss_17AC.unk70 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 357 insns */
s32 fn_1_4B840(CardGameWork *work)
{
    s32 ret = 0;
    s32 tbl[10] = { 3, 4, 3, 0, 2, 3, 2, 0, 1, 0 };

    switch (lbl_1_bss_17AC.unk74) {
        case 0:
            if (lbl_1_bss_17AC.unk10[2] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                lbl_1_bss_17AC.unk10[14] = espEntry(lbl_1_data_2B4[lbl_1_bss_17AC.unk78 + 18], 0, 0);
                espDrawNoSet(lbl_1_bss_17AC.unk10[14], 0);
                espPosSet(lbl_1_bss_17AC.unk10[14], 210.0f, 100.0f);
                espScaleSet(lbl_1_bss_17AC.unk10[14], 3.0f, 3.0f);
                lbl_1_bss_17AC.unk80 = 30;
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 1:
            lbl_1_bss_17AC.unk80--;
            if (lbl_1_bss_17AC.unk80 <= 10) {
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk80 = 10;
                lbl_1_bss_17AC.unk74++;
                HuAudFXPlay(0x438);
            }
            espScaleSet(lbl_1_bss_17AC.unk10[14], 0.1f * lbl_1_bss_17AC.unk80, 0.1f * lbl_1_bss_17AC.unk80);
            break;
        case 2:
            espScaleSet(lbl_1_bss_17AC.unk10[14], 1.0f + 0.05f * tbl[lbl_1_bss_17AC.unk7C], 1.0f + 0.05f * tbl[lbl_1_bss_17AC.unk7C]);
            lbl_1_bss_17AC.unk7C++;
            if (lbl_1_bss_17AC.unk7C > 10) {
                espScaleSet(lbl_1_bss_17AC.unk10[14], 1.0f, 1.0f);
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk80 = 10;
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 3:
            if (++lbl_1_bss_17AC.unk7C >= 30) {
                lbl_1_bss_17AC.unk80--;
                if (lbl_1_bss_17AC.unk80 <= 0) {
                    lbl_1_bss_17AC.unk80 = 0;
                    lbl_1_bss_17AC.unk74++;
                }
                espScaleSet(lbl_1_bss_17AC.unk10[14], 0.1f * lbl_1_bss_17AC.unk80, 0.1f * lbl_1_bss_17AC.unk80);
            }
            break;
        case 4:
            /* retail bug: kills the sprite numbered by the data number, not the entry id in unk10[14] */
            espKill(lbl_1_data_2B4[lbl_1_bss_17AC.unk78 + 18]);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
            lbl_1_bss_17AC.unk74 = 0;
            ret = 1;
            break;
    }
    return ret;
}

/* 260 insns */
s32 fn_1_4BDD4(CardGameWork *work)
{
    s32 cards[12];
    s32 count[4];
    s32 used[4];
    s32 ret;
    s32 per;
    s32 j;
    s32 n;
    s32 rnd;
    CardPlayerWork *player;
    s32 i;

    ret = 0;
    switch (lbl_1_bss_17AC.unk74) {
        case 0:
            fn_1_4FBC8(work, 0x2C);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[5], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            lbl_1_bss_17AC.unk74++;
            lbl_1_bss_20[0] = 0;
            break;
        case 1:
            if (++lbl_1_bss_20[0] == 30) {
                fn_1_8D04(0x2CC, lbl_1_bss_17AC.unk0[0], 1);
            }
            if (lbl_1_bss_17AC.unk10[5] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                WipeColorSet(255, 255, 255);
                lbl_1_bss_17AC.unk74++;
                omVibrate(0, 60, 6, 6);
                omVibrate(1, 60, 6, 6);
                omVibrate(2, 60, 6, 6);
                omVibrate(3, 60, 6, 6);
                HuAudFXPlay(0x439);
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            if (!WipeCheckEnd()) {
                memset(cards, -1, sizeof(cards));
                n = 0;
                for (i = 0; i < 4; i++) {
                    count[i] = used[i] = 0;
                    player = &work->player[i];
                    for (j = 0; j < 3; j++) {
                        if ((&player->unk34)[j] == -1) {
                            break;
                        }
                        cards[n] = (&player->unk34)[j];
                        n++;
                    }
                    player->unk34 = player->unk38 = player->unk3C = -1;
                }
                per = n / 4;
                for (i = 0; i < per * 4; i++) {
                    do {
                        rnd = frandmod(100) / 25;
                    } while (count[rnd] >= per);
                    (&work->player[rnd].unk34)[count[rnd]] = cards[i];
                    count[rnd]++;
                }
                for (i = per * 4; i < n; i++) {
                    do {
                        rnd = frandmod(100) / 25;
                    } while (used[rnd] != 0);
                    (&work->player[rnd].unk34)[count[rnd]] = cards[i];
                    used[rnd] = 1;
                }
                fn_1_2FFAC(work);
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 3:
            if (!WipeCheckEnd()) {
                lbl_1_bss_17AC.unk74 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}


/* 1464 insns */
s32 fn_1_4C1E4(CardGameWork *work)
{
    s32 ret = 0;
    Mtx mtx;
    Mtx rotMtx;
    HuVecF pos;
    HuVecF rot = { 0.0f, 0.0f, 0.0f };
    HuVecF pos2d;
    HuVecF ofs;
    CardPlayerWork *player;
    CardPlayerWork *target;
    s32 i;
    s32 j;

    player = &work->player[work->unk174[work->unk170]];
    switch (lbl_1_bss_17AC.unk74) {
        case 0:
            fn_1_4FBC8(work, 0x2D);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[5], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            lbl_1_bss_17AC.unk74++;
            lbl_1_bss_20[0] = 0;
            break;
        case 1:
            if (++lbl_1_bss_20[0] == 30) {
                fn_1_8D04(0x2CC, lbl_1_bss_17AC.unk0[0], 1);
            }
            if (lbl_1_bss_17AC.unk10[5] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionEndCheck(lbl_1_bss_17AC.unk0[0])) {
                for (i = 0; i < 2; i++) {
                    lbl_1_bss_17AC.unk2E[i] = Hu3DModelCreate(HuDataSelHeapReadNum(lbl_1_data_B0[i + 78], HU_MEMNUM_OVL, HEAP_MODEL));
                    Hu3DModelPosSet(lbl_1_bss_17AC.unk2E[i], 0.0f, 0.0f, 0.0f);
                    Hu3DModelAttrSet(lbl_1_bss_17AC.unk2E[i], HU3D_ATTR_DISPOFF);
                    Hu3DModelLayerSet(lbl_1_bss_17AC.unk2E[i], 3);
                    Hu3DModelCameraSet(lbl_1_bss_17AC.unk2E[i], HU3D_CAM0);
                    Hu3DModelScaleSet(lbl_1_bss_17AC.unk2E[i], 0.5f, 0.5f, 1.0f);
                }
                pos = (HuVecF) { 0.0f, 200.0f, -150.0f };
                PSMTXIdentity(mtx);
                PSMTXRotRad(mtx, 'y', 0.017453292f * player->unk18);
                PSMTXMultVec(mtx, &pos, &pos);
                PSVECAdd(&pos, &lbl_1_bss_17AC.unk34, &lbl_1_bss_17AC.unk40);
                Hu3DGLightPosSet(lbl_1_bss_17AC.unk10[13], lbl_1_bss_17AC.unk40.x, lbl_1_bss_17AC.unk40.y, lbl_1_bss_17AC.unk40.z, 0.0f, 1.0f, 0.0f);
                lbl_1_bss_17AC.unk10[10] = Hu3DLLightCreate(lbl_1_bss_17AC.unk2E[0], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 255, 255, 255);
                Hu3DLLightInfinitytSet(lbl_1_bss_17AC.unk2E[0], lbl_1_bss_17AC.unk10[10]);
                lbl_1_bss_17AC.unk10[11] = Hu3DLLightCreate(lbl_1_bss_17AC.unk2E[1], Hu3DCamera[0].pos.x, Hu3DCamera[0].pos.y, Hu3DCamera[0].pos.z, 0.0f, 0.0f, -1.0f, 255, 255, 255);
                Hu3DLLightInfinitytSet(lbl_1_bss_17AC.unk2E[1], lbl_1_bss_17AC.unk10[11]);
                fn_1_3ED3C(9, lbl_1_bss_17AC.unk40);
                rot.y = 180.0f + player->unk18;
                fn_1_3F498(9, 0, rot);
                fn_1_3F6B0(9, 0, (HuVecF) { 0.5f, 0.5f, 1.0f });
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk74++;
                lbl_1_bss_17AC.unk98 = 0;
                fn_1_8D04(0x44C, lbl_1_bss_17AC.unk0[0], 1);
                lbl_1_bss_20[0] = 0;
            }
            break;
        case 2:
            lbl_1_bss_17AC.unk98 += 4;
            if (lbl_1_bss_17AC.unk98 > 255) {
                lbl_1_bss_17AC.unk98 = 255;
            }
            Hu3DGLightColorSet(lbl_1_bss_17AC.unk10[13], lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98);
            if (++lbl_1_bss_17AC.unk80 > 55) {
                Hu3DModelPosSetV(lbl_1_bss_17AC.unk2E[0], &lbl_1_bss_17AC.unk40);
                rot.y = 180.0f + player->unk18;
                Hu3DModelRotSetV(lbl_1_bss_17AC.unk2E[0], &rot);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk2E[0], HU3D_ATTR_DISPOFF);
                lbl_1_bss_17AC.unk7C = 0;
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 3:
            if (++lbl_1_bss_17AC.unk7C >= 150) {
                if (lbl_1_bss_17AC.unk98 >= 8) {
                    lbl_1_bss_17AC.unk98 -= 8;
                }
                Hu3DGLightColorSet(lbl_1_bss_17AC.unk10[13], lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98);
            }
            if (fn_1_3F714(9, 0) && ++lbl_1_bss_17AC.unk80 > 30) {
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk2E[0], HU3D_ATTR_DISPOFF);
                fn_1_3ED3C(11, lbl_1_bss_17AC.unk40);
                fn_1_3F498(11, 0, (HuVecF) { 0.0f, 180.0f + player->unk18, 0.0f });
                fn_1_3F6B0(11, 0, (HuVecF) { 0.5f, 0.5f, 1.0f });
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk74++;
                omVibrate(work->unk174[work->unk170], 50, 6, 6);
                fn_1_8D04(0x41E, lbl_1_bss_17AC.unk2E[0], 1);
            }
            break;
        case 4:
            if (fn_1_3F714(11, 0)) {
                fn_1_3F278(11, 0);
                fn_1_3ED3C(12, lbl_1_bss_17AC.unk40);
                fn_1_3F498(12, 0, (HuVecF) { 0.0f, 180.0f + player->unk18, 0.0f });
                fn_1_3F6B0(12, 0, (HuVecF) { 0.5f, 0.5f, 1.0f });
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 5:
            if (++lbl_1_bss_17AC.unk80 == 10) {
                fn_1_3ED3C(10, lbl_1_bss_17AC.unk40);
                fn_1_3F498(10, 0, (HuVecF) { 0.0f, 180.0f + player->unk18, 0.0f });
                fn_1_3F6B0(10, 0, (HuVecF) { 0.5f, 0.5f, 1.0f });
                omVibrate(work->unk174[work->unk170], 15, 12, 0);
                fn_1_8D04(0x41F, lbl_1_bss_17AC.unk2E[0], 1);
                fn_1_8D04(0x44D, lbl_1_bss_17AC.unk2E[0], 1);
            }
            if (fn_1_3F714(12, 0)) {
                fn_1_3F278(12, 0);
                Hu3DModelPosSetV(lbl_1_bss_17AC.unk2E[1], &lbl_1_bss_17AC.unk40);
                rot.y = 180.0f + player->unk18;
                Hu3DModelRotSetV(lbl_1_bss_17AC.unk2E[1], &rot);
                Hu3DModelCameraSet(lbl_1_bss_17AC.unk2E[1], HU3D_CAM0);
                Hu3DModelLayerSet(lbl_1_bss_17AC.unk2E[1], 7);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk2E[1], HU3D_ATTR_DISPOFF);
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 6:
            if (fn_1_3F714(10, 0)) {
                Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1], 0.0f, 30.0f, HU3D_MOTATTR_LOOP);
                lbl_1_bss_17AC.unk88 = frandmod(100) / 25;
                lbl_1_bss_17AC.unk4C = Hu3DData[lbl_1_bss_17AC.unk2E[1]].pos;
                Hu3D3Dto2D(&Hu3DData[lbl_1_bss_17AC.unk2E[1]].pos, 1, &pos2d);
                j = 0;
                while (TRUE) {
                    if (work->unk174[j] == lbl_1_bss_17AC.unk88) {
                        break;
                    }
                    j++;
                }
                ofs = (HuVecF) { ((float (*)[2])lbl_1_data_528)[j][0] - 7.0f, ((float (*)[2])lbl_1_data_528)[j][1] - 12.0f, 0.0f };
                fn_1_4F144(0, pos2d, ofs, 60, 0.0f, 0x21);
                lbl_1_bss_17AC.unk90 = 0.0f;
                lbl_1_bss_17AC.unk94 = 1.0f;
                lbl_1_bss_17AC.unk80 = 0;
                lbl_1_bss_17AC.unk74++;
                fn_1_8D04(0x353, lbl_1_bss_17AC.unk2E[1], 1);
            }
            break;
        case 7:
            fn_1_8D04(0x8353, lbl_1_bss_17AC.unk2E[1], 1);
            lbl_1_bss_17AC.unk94 = 0.5f - 0.4f * fn_1_4EEA0(0, lbl_1_bss_17AC.unk80 / 60.0f);
            lbl_1_bss_17AC.unk90 -= 10.0f + 5.5f * fn_1_4EEA0(0, lbl_1_bss_17AC.unk80 / 60.0f);
            PSMTXIdentity(mtx);
            PSMTXRotRad(rotMtx, 'y', 0.017453292f * (180.0f + player->unk18));
            PSMTXConcat(mtx, rotMtx, mtx);
            PSMTXRotRad(rotMtx, 'z', 0.017453292f * lbl_1_bss_17AC.unk90);
            PSMTXConcat(mtx, rotMtx, mtx);
            Hu3DMtxRotGet(mtx, &rot);
            Hu3DModelRotSetV(lbl_1_bss_17AC.unk2E[1], &rot);
            Hu3DModelScaleSet(lbl_1_bss_17AC.unk2E[1], lbl_1_bss_17AC.unk94, lbl_1_bss_17AC.unk94, lbl_1_bss_17AC.unk94);
            fn_1_4F1EC(0, &pos);
            Hu3DData[lbl_1_bss_17AC.unk2E[1]].pos = fn_1_4EDB8(lbl_1_bss_17AC.unk4C, pos.x, pos.y);
            if (lbl_1_bss_17AC.unk80 == 40) {
                Hu3DModelCameraSet(lbl_1_bss_17AC.unk2E[1], HU3D_CAM1);
            }
            if (++lbl_1_bss_17AC.unk80 > 60) {
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk2E[1], HU3D_ATTR_DISPOFF);
                target = &work->player[lbl_1_bss_17AC.unk88];
                target->unk4C++;
                target->unk40 = target->unk44 + target->unk48 * 2 + target->unk4C * -1;
                fn_1_2FFAC(work);
                Hu3DMotionShiftSet(lbl_1_bss_468[lbl_1_bss_17AC.unk88], lbl_1_bss_430[lbl_1_bss_17AC.unk88][1], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
                if (lbl_1_bss_17AC.unk88 == work->unk174[work->unk170]) {
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                        lbl_1_bss_20[1] = 0x200;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                        lbl_1_bss_20[1] = 0x1EC;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                        lbl_1_bss_20[1] = 0x264;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                        lbl_1_bss_20[1] = 0x2B4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                        lbl_1_bss_20[1] = 0x28C;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                        lbl_1_bss_20[1] = 0x1C4;
                    }
                    if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                        lbl_1_bss_20[1] = 0x2A0;
                    }
                    fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                    lbl_1_bss_20[1] = 0;
                }
                lbl_1_bss_17AC.unk74++;
                HuAudFXPlay(8);
            }
            if (lbl_1_bss_17AC.unk80 == 58) {
                omVibrate(lbl_1_bss_17AC.unk88, 15, 12, 0);
            }
            break;
        case 8:
            if (Hu3DMotionEndCheck(lbl_1_bss_468[lbl_1_bss_17AC.unk88])) {
                Hu3DLLightKill(lbl_1_bss_17AC.unk2E[0], lbl_1_bss_17AC.unk10[10]);
                Hu3DLLightKill(lbl_1_bss_17AC.unk2E[1], lbl_1_bss_17AC.unk10[11]);
                for (i = 0; i < 2; i++) {
                    Hu3DModelKill(lbl_1_bss_17AC.unk2E[i]);
                }
                lbl_1_bss_17AC.unk74 = 0;
                ret = 1;
                lbl_1_bss_12A8.unk8[0] = GwPlayerConf[lbl_1_bss_17AC.unk88].charNo;
                fn_1_4FBC8(work, 0x42);
            }
            break;
    }
    return ret;
}

/* 689 insns */
s32 fn_1_4D8C4(CardGameWork *work)
{
    s32 ret = 0;
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;

    switch (lbl_1_bss_17AC.unk74) {
        case 0:
            fn_1_4FBC8(work, 0x2E);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[3], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            Hu3DMotionTimeSet(lbl_1_bss_17AC.unk0[3], 0.0f);
            Hu3DMotionTimeSet(lbl_1_bss_17AC.unk0[4], 0.0f);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[4], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[3], HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[4], HU3D_MOTATTR_PAUSE);
            lbl_1_bss_17AC.unk74++;
            break;
        case 1:
            if (lbl_1_bss_17AC.unk10[3] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionTimeGet(lbl_1_bss_17AC.unk0[0]) >= 50.0f) {
                Hu3DMotionShiftSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][2], 0.0f, 10.0f, HU3D_MOTATTR_LOOP);
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 0) {
                    lbl_1_bss_20[1] = 0x1F9;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 1) {
                    lbl_1_bss_20[1] = 0x1E5;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 2) {
                    lbl_1_bss_20[1] = 0x25D;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 3) {
                    lbl_1_bss_20[1] = 0x2AD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 4) {
                    lbl_1_bss_20[1] = 0x285;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 5) {
                    lbl_1_bss_20[1] = 0x1BD;
                }
                if (GwPlayerConf[work->unk174[work->unk170]].charNo == 6) {
                    lbl_1_bss_20[1] = 0x299;
                }
                fn_1_8D04(lbl_1_bss_20[1], lbl_1_bss_468[work->unk174[work->unk170]], 1);
                lbl_1_bss_20[1] = 0;
                Hu3DModelObjMtxGet(lbl_1_bss_17AC.unk0[0], "itemhook_M_1", mtx);
                pos = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
                Hu3DMtxRotGet(mtx, &rot);
                Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[3], &pos);
                Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[3], &rot);
                Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[4], &pos);
                Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[4], &rot);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[3], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[3], HU3D_MOTATTR_PAUSE);
                lbl_1_bss_17AC.unk98 = 0;
                lbl_1_bss_17AC.unk74++;
                omVibrate(0, 170, 4, 2);
                omVibrate(1, 170, 4, 2);
                omVibrate(2, 170, 4, 2);
                omVibrate(3, 170, 4, 2);
                lbl_1_bss_20[0] = fn_1_8D04(0x43A, lbl_1_bss_17AC.unk0[4], 1);
            }
            break;
        case 2:
            lbl_1_bss_17AC.unk98 += 12;
            if (lbl_1_bss_17AC.unk98 > 200) {
                lbl_1_bss_17AC.unk98 = 200;
            }
            Hu3DGLightColorSet(lbl_1_bss_17AC.unk10[13], lbl_1_bss_17AC.unk98, lbl_1_bss_17AC.unk98 / 2, 0, 0x7F);
            Hu3DModelObjMtxGet(lbl_1_bss_17AC.unk0[0], "itemhook_M_1", mtx);
            pos = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
            Hu3DMtxRotGet(mtx, &rot);
            Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[3], &pos);
            Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[3], &rot);
            Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[4], &pos);
            Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[4], &rot);
            fn_1_8D04(0x843A, lbl_1_bss_17AC.unk0[4], 1);
            if (Hu3DMotionTimeGet(lbl_1_bss_17AC.unk0[3]) >= 26.0f) {
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[3], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[4], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(lbl_1_bss_17AC.unk0[4], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[4], HU3D_MOTATTR_LOOP);
                lbl_1_bss_17AC.unk74++;
            }
            break;
        case 3:
            Hu3DModelObjMtxGet(lbl_1_bss_17AC.unk0[0], "itemhook_M_1", mtx);
            pos = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
            Hu3DMtxRotGet(mtx, &rot);
            Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[4], &pos);
            Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[4], &rot);
            fn_1_8D04(0x843A, lbl_1_bss_17AC.unk0[4], 1);
            if (Hu3DMotionTimeGet(lbl_1_bss_17AC.unk0[0]) >= 170.0f) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                WipeColorSet(0, 0, 0);
                lbl_1_bss_17AC.unk74++;
                HuAudFXFadeOut(lbl_1_bss_20[0], 100);
            }
            break;
        case 4:
            Hu3DModelObjMtxGet(lbl_1_bss_17AC.unk0[0], "itemhook_M_1", mtx);
            pos = (HuVecF) { mtx[0][3], mtx[1][3], mtx[2][3] };
            Hu3DMtxRotGet(mtx, &rot);
            Hu3DModelPosSetV(lbl_1_bss_17AC.unk0[4], &pos);
            Hu3DModelRotSetV(lbl_1_bss_17AC.unk0[4], &rot);
            if (!WipeCheckEnd()) {
                fn_1_2FBCC(work);
                Hu3DMotionSet(lbl_1_bss_468[work->unk174[work->unk170]], lbl_1_bss_430[work->unk174[work->unk170]][6]);
                Hu3DGLightColorSet(lbl_1_bss_17AC.unk10[13], 0, 0, 0, 0);
                Hu3DMotionSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[1]);
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[4], HU3D_ATTR_DISPOFF);
                Hu3DModelHookReset(lbl_1_bss_17AC.unk0[0]);
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 60);
                lbl_1_bss_17AC.unk74++;
                HuAudFXStop(lbl_1_bss_20[0]);
            }
            break;
        case 5:
            if (!WipeCheckEnd()) {
                lbl_1_bss_17AC.unk74 = 0;
                ret = 1;
            }
            break;
    }
    return ret;
}

/* 135 insns */
s32 fn_1_4E388(CardGameWork *work)
{
    s32 ret;

    ret = 0;
    switch (lbl_1_bss_17AC.unk74) {
        case 0:
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[4], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            lbl_1_bss_17AC.unk74++;
            break;
        case 1:
            fn_1_8D04(0x2C9, lbl_1_bss_17AC.unk0[0], 1);
            fn_1_4FBC8(work, 0x2F);
            Hu3DMotionShiftSet(lbl_1_bss_17AC.unk0[0], lbl_1_bss_17AC.unk10[0], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
            HuAudSStreamFadeOut(lbl_1_bss_8[0], 1000);
            lbl_1_bss_17AC.unk74++;
            lbl_1_bss_20[0] = 0;
            break;
        case 2:
            if (++lbl_1_bss_20[0] == 50) {
                fn_1_8D04(0x2CC, lbl_1_bss_17AC.unk0[0], 1);
            }
            if (lbl_1_bss_17AC.unk10[0] == Hu3DData[lbl_1_bss_17AC.unk0[0]].motId && Hu3DMotionTimeGet(lbl_1_bss_17AC.unk0[0]) >= 100.0f) {
                Hu3DModelAttrSet(lbl_1_bss_17AC.unk0[0], HU3D_ATTR_DISPOFF);
                lbl_1_bss_17AC.unk74 = 0;
                ret = 1;
                lbl_1_bss_20[0] = 0;
            }
            break;
    }
    return ret;
}

/* 109 insns */
void fn_1_4E5A4(void)
{
    lbl_1_bss_1944.unk0 = HuMemDirectMallocNum(HEAP_MODEL, GXGetTexBufferSize(320, 240, GX_TF_RGB565, GX_FALSE, 0), HU_MEMNUM_OVL);
    lbl_1_bss_1944.unk4 = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_card, 0xDC), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1944.unk8 = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_card, 0xDD), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1944.unk14.x = 0.0f;
    lbl_1_bss_1944.unk14.y = 0.0f;
    lbl_1_bss_1944.unk14.z = 0.0f;
    lbl_1_bss_1944.unk20.x = 0.0f;
    lbl_1_bss_1944.unk20.y = 0.0f;
    lbl_1_bss_1944.unk20.z = 0.0f;
    lbl_1_bss_1944.unk2C = (GXColor) { 0, 0, 0, 0 };
    lbl_1_bss_1944.unkC = 0.0f;
    lbl_1_bss_1944.unk10 = -0.02f;
}

/* 20 insns */
void fn_1_4E758(void)
{
    if (lbl_1_bss_1944.unk0 != 0) {
        HuMemDirectFree(lbl_1_bss_1944.unk0);
        lbl_1_bss_1944.unk0 = 0;
    }
}

/* 40 insns */
void fn_1_4E7A8(s16 layerNo)
{
    HU3DWATER *waterP = &Hu3DWaterData;
    s32 pause;

    if (Hu3DCameraBit & 1) {
        GXSetTexCopySrc(0, 0, 640, 480);
        GXSetTexCopyDst(320, 240, GX_TF_RGB565, GX_TRUE);
        GXCopyTex(lbl_1_bss_1944.unk0, GX_FALSE);
        if ((pause = omPauseChk() + omUPauseFlag) == 0) {
            pause;
        }
    }
}

/* 25 insns */
void fn_1_4E848(HuVecF a0, HuVecF a1)
{
    lbl_1_bss_1944.unk14.x = a0.x;
    lbl_1_bss_1944.unk14.y = a0.y;
    lbl_1_bss_1944.unk14.z = a0.z;
    lbl_1_bss_1944.unk20.x = a1.x;
    lbl_1_bss_1944.unk20.y = a1.y;
    lbl_1_bss_1944.unk20.z = a1.z;
}

/* 11 insns */
void fn_1_4E8AC(GXColor *color)
{
    lbl_1_bss_1944.unk2C = *color;
}

/* 4 insns */
void fn_1_4E8D8(float a0)
{
    lbl_1_bss_1944.unk10 = a0;
}

/* 308 insns */
void fn_1_4E8E8(HU3DDRAWOBJ *drawObj, HSFMATERIAL *material)
{
    s32 pause;
    GXTexObj texObj;
    Mtx trans;
    Mtx scale;
    Mtx mtx;
    Mtx proj;
    Mtx invCam;
    HU3DCAMERA *cameraP;

    cameraP = &Hu3DCamera[Hu3DCameraNo];
    if ((pause = omPauseChk() + omUPauseFlag) == 0) {
        lbl_1_bss_1944.unkC += lbl_1_bss_1944.unk10;
    }
    GXInitTexObj(&texObj, lbl_1_bss_1944.unk0, 320, 240, GX_TF_RGB565, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP1);
    HuSprTexLoad(lbl_1_bss_1944.unk4, 0, GX_TEXMAP2, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    HuSprTexLoad(lbl_1_bss_1944.unk8, 0, GX_TEXMAP3, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetNumTexGens(3);
    GXSetNumTevStages(3);
    C_MTXLightPerspective(proj, cameraP->fov, 1.2f, 0.5f, -0.5f, 0.5f, 0.5f);
    PSMTXInverse(Hu3DCameraMtx, invCam);
    PSMTXConcat(invCam, drawObj->matrix, trans);
    PSMTXConcat(proj, Hu3DCameraMtx, mtx);
    PSMTXConcat(mtx, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX1, GX_MTX3x4);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_POS, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
    PSMTXTrans(trans, 0.0f, lbl_1_bss_1944.unkC, 0.0f);
    PSMTXScale(scale, 0.8f, 0.8f, 1.0f);
    PSMTXConcat(scale, trans, mtx);
    GXLoadTexMtxImm(mtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXSetTexCoordGen2(GX_TEXCOORD2, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevColor(GX_TEVREG0, lbl_1_bss_1944.unk2C);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_TEXC, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD2, GX_TEXMAP0, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_CPREV, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD1, GX_TEXMAP3, GX_COLOR0);
    GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_TEXC, GX_CC_A0, GX_CC_CPREV);
    GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_KONST);
    GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumIndStages(1);
    GXSetIndTexOrder(GX_INDTEXSTAGE0, GX_TEXCOORD1, GX_TEXMAP2);
    GXSetIndTexCoordScale(GX_INDTEXSTAGE0, GX_ITS_1, GX_ITS_1);
    GXSetTevIndWarp(GX_TEVSTAGE0, GX_INDTEXSTAGE0, GX_TRUE, GX_FALSE, GX_ITM_0);
    GXSetIndTexMtx(GX_ITM_0, (float (*)[3])&lbl_1_bss_1944.unk14, -1);
}

/* 58 insns */
HuVecF fn_1_4EDB8(HuVecF pos, float a1, float a2)
{
    HuVecF dir;
    HuVecF pos2d;
    HuVecF out;
    float dist;

    VECSubtract(&Hu3DCamera[0].pos, &pos, &dir);
    dist = VECMag(&dir);
    pos2d = (HuVecF) { a1, a2, dist };
    Hu3D2Dto3D(&pos2d, 1, &out);
    return out;
}

/* 157 insns */
float fn_1_4EEA0(s32 mode, float t)
{
    float ret;

    if (t >= 1.0f) {
        t = 1.0f;
    }
    switch (mode) {
        case 0:
            ret = 1.0 - cos(M_PI * (90.0f * t) / 180.0);
            break;
        case 1:
            ret = sin(M_PI * (90.0f * t) / 180.0);
            break;
        case 2:
            ret = (1.0 - cos(M_PI * (180.0f * t) / 180.0)) / 2.0;
            break;
        case 3:
            if (t < 0.5) {
                ret = sin(M_PI * (90.0f * t) / 180.0);
            }
            else {
                ret = 2.0 - cos(M_PI * (90.0f * t) / 180.0);
            }
            ret *= 0.5f;
            break;
        case 4:
            ret = t;
            break;
        case 5:
            ret = sin(M_PI * (180.0f * t) / 180.0);
            break;
    }
    return ret;
}

/* 12 insns */
void fn_1_4F114(void)
{
    memset(lbl_1_bss_12FC, 0, sizeof(lbl_1_bss_12FC));
}

/* 42 insns */
void fn_1_4F144(s32 idx, HuVecF a1, HuVecF a2, s32 a3, float a4, s32 a5)
{
    lbl_1_bss_12FC[idx].unk0 = 0;
    lbl_1_bss_12FC[idx].unk4 = a1;
    lbl_1_bss_12FC[idx].unk10 = a2;
    lbl_1_bss_12FC[idx].unk1C = a3;
    lbl_1_bss_12FC[idx].unk20 = a4;
    lbl_1_bss_12FC[idx].unk24 = a5;
}

/* 631 insns */
s32 fn_1_4F1EC(s32 idx, HuVecF *a1)
{
    float k;
    float t;
    s32 mode;

    t = lbl_1_bss_12FC[idx].unk0;
    t /= lbl_1_bss_12FC[idx].unk1C;
    *a1 = lbl_1_bss_12FC[idx].unk4;
    if ((mode = lbl_1_bss_12FC[idx].unk24 & 0xF) != 0) {
        k = fn_1_4EEA0(mode - 1, t);
        a1->x += k * (lbl_1_bss_12FC[idx].unk10.x - lbl_1_bss_12FC[idx].unk4.x);
    }
    if ((mode = (lbl_1_bss_12FC[idx].unk24 & 0xF0) >> 4) != 0) {
        k = fn_1_4EEA0(mode - 1, t);
        a1->y += k * (lbl_1_bss_12FC[idx].unk10.y - lbl_1_bss_12FC[idx].unk4.y);
    }
    if ((mode = (lbl_1_bss_12FC[idx].unk24 & 0xF00) >> 8) != 0) {
        if (mode == 1) {
            a1->x -= lbl_1_bss_12FC[idx].unk20 * fn_1_4EEA0(5, t);
        }
        else if (mode == 2) {
            a1->x += lbl_1_bss_12FC[idx].unk20 * fn_1_4EEA0(5, t);
        }
        else if (mode == 3) {
            a1->y -= lbl_1_bss_12FC[idx].unk20 * fn_1_4EEA0(5, t);
        }
        else {
            a1->y += lbl_1_bss_12FC[idx].unk20 * fn_1_4EEA0(5, t);
        }
    }
    lbl_1_bss_12FC[idx].unk0++;
    if (lbl_1_bss_12FC[idx].unk0 > lbl_1_bss_12FC[idx].unk1C) {
        lbl_1_bss_12FC[idx].unk0 = lbl_1_bss_12FC[idx].unk1C;
        return 1;
    }
    return 0;
}

/* 13 insns */
void fn_1_4FBC8(CardGameWork *work, s32 mess)
{
    fn_1_4FBFC(work, mess);
    fn_1_4FFEC();
}

/* 0xBA8 */ u32 lbl_1_data_BA8[67] = { DATA_daisymdl0, DATANUM(DATA_daisymdl0, 1), DATANUM(DATA_daisymdl0, 2), DATANUM(DATA_daisymdl0, 7), DATANUM(DATA_daisymdl0, 9), DATANUM(DATA_daisymdl0, 10), DATANUM(DATA_daisymdl0, 11), DATANUM(DATA_daisymdl0, 12), DATANUM(DATA_daisymdl0, 13), DATANUM(DATA_daisymdl0, 14), DATANUM(DATA_daisymdl0, 15), DATANUM(DATA_daisymdl0, 16), DATANUM(DATA_daisymdl0, 17), DATANUM(DATA_daisymdl0, 18), DATANUM(DATA_daisymdl0, 19), DATANUM(DATA_daisymdl0, 20), DATANUM(DATA_daisymdl0, 21), DATANUM(DATA_daisymdl0, 22), DATANUM(DATA_daisymdl0, 23), DATANUM(DATA_daisymdl0, 24), DATANUM(DATA_daisymdl0, 25), DATANUM(DATA_daisymdl0, 26), DATANUM(DATA_daisymdl0, 27), DATANUM(DATA_daisymdl0, 28), DATANUM(DATA_daisymdl0, 29), DATANUM(DATA_daisymdl0, 30), DATANUM(DATA_daisymdl0, 31), DATANUM(DATA_daisymdl0, 32), DATANUM(DATA_daisymdl0, 33), DATANUM(DATA_daisymdl0, 34), DATANUM(DATA_daisymdl0, 35), DATANUM(DATA_daisymdl0, 8), DATANUM(DATA_daisymdl0, 3), DATANUM(DATA_daisymdl0, 4), DATANUM(DATA_daisymdl0, 5), DATANUM(DATA_daisymdl0, 6), DATANUM(DATA_daisymdl0, 36), DATANUM(DATA_daisymdl0, 37), DATANUM(DATA_daisymdl0, 38), DATANUM(DATA_daisymdl0, 39), DATANUM(DATA_daisymdl0, 40), DATANUM(DATA_daisymdl0, 41), DATANUM(DATA_daisymdl0, 42), DATANUM(DATA_daisymdl0, 43), DATANUM(DATA_daisymdl0, 44), DATANUM(DATA_daisymdl0, 45), DATANUM(DATA_daisymdl0, 46), DATANUM(DATA_daisymdl0, 47), DATANUM(DATA_daisymdl0, 48), DATANUM(DATA_daisymdl0, 49), DATANUM(DATA_daisymdl0, 50), DATANUM(DATA_daisymdl0, 51), DATANUM(DATA_daisymdl0, 52), DATANUM(DATA_daisymdl0, 53), DATANUM(DATA_daisymdl0, 54), DATANUM(DATA_daisymdl0, 55), DATANUM(DATA_daisymdl0, 56), DATANUM(DATA_daisymdl0, 57), DATANUM(DATA_daisymdl0, 58), DATANUM(DATA_daisymdl0, 59), DATANUM(DATA_daisymdl0, 60), DATANUM(DATA_daisymdl0, 61), DATANUM(DATA_daisymdl0, 62), DATANUM(DATA_daisymdl0, 63), DATANUM(DATA_daisymdl0, 64), DATANUM(DATA_daisymdl0, 65), DATANUM(DATA_daisymdl0, 66) };

/* 252 insns */
void fn_1_4FBFC(CardGameWork *work, s32 mess)
{
    HuVec2f size;
    float y;
    s32 i;
    u32 messId;
    void *data;

    if (lbl_1_bss_12A8.unk40 == 0) {
        if (lbl_1_bss_12A8.unk44 != -1) {
            HuWinExKill(lbl_1_bss_12A8.unk44);
        }
        if (lbl_1_bss_12A8.unk4C != -1) {
            HuWinSprKill(lbl_1_bss_12A8.unk44, lbl_1_bss_12A8.unk4C);
            HuSprAnimKill(lbl_1_bss_12A8.unk48);
        }
        for (i = 0; lbl_1_bss_12A8.unk8[i] != (u32)-1; i++) {
            HuWinInsertMesSizeGet(lbl_1_bss_12A8.unk8[i], i);
        }
        if (lbl_1_bss_12A8.unk30 == 0) {
            messId = lbl_1_data_BA8[mess - 1];
        }
        else {
            messId = 0x140000 + mess - 1;
        }
        HuWinMesMaxSizeGet(1, &size, messId);
        if (lbl_1_bss_12A8.unk2C != 0 || lbl_1_bss_12A8.unk30 != 0) {
            size.x = 448.0f;
            size.y = 94.0f;
        }
        y = 340.0f;
        if (lbl_1_bss_12A8.unk30 != 0 && lbl_1_bss_12A8.unk34 != 0) {
            y = 48.0f;
        }
        lbl_1_bss_12A8.unk44 = HuWinExCreateFrame(-10000.0f, y, size.x, size.y, -1, 1);
        if (lbl_1_bss_12A8.unk3C != -1) {
            data = HuDataSelHeapReadNum(lbl_1_bss_12A8.unk3C, HU_MEMNUM_OVL, HEAP_MODEL);
            lbl_1_bss_12A8.unk48 = HuSprAnimRead(data);
            lbl_1_bss_12A8.unk4C = HuWinAnimSet(lbl_1_bss_12A8.unk44, lbl_1_bss_12A8.unk48, 0, 48.0f, size.y / 2);
        }
        if (lbl_1_bss_12A8.unk0 == 0) {
            HuWinExOpen(lbl_1_bss_12A8.unk44);
        }
        else {
            HuWinDispOn(lbl_1_bss_12A8.unk44);
        }
        HuWinMesPalSet(lbl_1_bss_12A8.unk44, 7, 0, 0, 0);
        for (i = 0; lbl_1_bss_12A8.unk8[i] != (u32)-1; i++) {
            HuWinInsertMesSet(lbl_1_bss_12A8.unk44, lbl_1_bss_12A8.unk8[i], i);
        }
        if (lbl_1_bss_12A8.unk38 != 0) {
            fn_1_500D0(work, lbl_1_bss_12A8.unk44);
        }
        HuWinMesSpeedSet(lbl_1_bss_12A8.unk44, lbl_1_bss_12A8.unk4);
        HuWinMesSet(lbl_1_bss_12A8.unk44, messId);
    }
}

/* 57 insns */
void fn_1_4FFEC(void)
{
    if (lbl_1_bss_12A8.unk40 == 0 && lbl_1_bss_12A8.unk44 != -1) {
        HuWinMesWait(lbl_1_bss_12A8.unk44);
        if (lbl_1_bss_12A8.unk0 == 0) {
            HuWinExClose(lbl_1_bss_12A8.unk44);
        }
        if (lbl_1_bss_12A8.unk4C != -1) {
            HuWinSprKill(lbl_1_bss_12A8.unk44, lbl_1_bss_12A8.unk4C);
            HuSprAnimKill(lbl_1_bss_12A8.unk48);
        }
        HuWinExKill(lbl_1_bss_12A8.unk44);
        HuWinComKeyReset();
        fn_1_501B4(1);
    }
}

/* 57 insns */
void fn_1_500D0(CardGameWork *work, HUWINID winId)
{
    HUWIN *winP;
    s16 i;

    winP = &winData[winId];
    winP->padMask = 1 << GwPlayerConf[work->unk174[work->unk170]].padNo;
    if (GwPlayerConf[work->unk174[work->unk170]].type != 0) {
        for (i = 0; i < 10; i++) {
            HuWinComKeyWait(0x100, 0x100, 0x100, 0x100, GWComKeyDelayGet());
        }
    }
}

/* 74 insns */
void fn_1_501B4(s32 a0)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        lbl_1_bss_12A8.unk8[i] = -1;
    }
    lbl_1_bss_12A8.unk44 = -1;
    lbl_1_bss_12A8.unk4 = 1;
    lbl_1_bss_12A8.unk2C = lbl_1_bss_12A8.unk28 = lbl_1_bss_12A8.unk0 = 0;
    lbl_1_bss_12A8.unk34 = 0;
    lbl_1_bss_12A8.unk3C = lbl_1_bss_12A8.unk4C = -1;
    lbl_1_bss_12A8.unk48 = 0;
    if (a0 == 0) {
        lbl_1_bss_12A8.unk38 = lbl_1_bss_12A8.unk30 = 0;
        lbl_1_bss_12A8.unk50 = -1;
        lbl_1_bss_12A8.unk40 = 0;
        HuWinComKeyReset();
    }
}

/* 1 insns */
s32 fn_1_502DC(s32 a0)
{
}

/* 0xCB4 */ u32 lbl_1_data_CB4[27] = { DATA_bdemo, DATANUM(DATA_bdemo, 1), DATANUM(DATA_bdemo, 2), DATANUM(DATA_bdemo, 3), DATANUM(DATA_bdemo, 4), DATANUM(DATA_bdemo, 5), DATANUM(DATA_bdemo, 6), DATANUM(DATA_bdemo, 7), DATANUM(DATA_bdemo, 8), DATANUM(DATA_bdemo, 9), DATANUM(DATA_bdemo, 10), DATANUM(DATA_bdemo, 11), DATANUM(DATA_bdemo, 12), DATANUM(DATA_bdemo, 13), DATANUM(DATA_bdemo, 14), DATANUM(DATA_bdemo, 15), DATANUM(DATA_bdemo, 16), DATANUM(DATA_bdemo, 17), DATANUM(DATA_bdemo, 18), DATANUM(DATA_bdemo, 19), DATANUM(DATA_bdemo, 20), DATANUM(DATA_bdemo, 21), DATANUM(DATA_bdemo, 22), DATANUM(DATA_bdemo, 23), DATANUM(DATA_bdemo, 24), DATANUM(DATA_bdemo, 25), DATANUM(DATA_bdemo, 26) };

/* 96 insns */
void fn_1_502E0(s32 a0)
{
    HuVec2f size;
    float x;
    float y;

    if (lbl_1_bss_12A8.unk40 == 0 && lbl_1_bss_12A8.unk50 == -1) {
        HuWinMesMaxSizeGet(1, &size, lbl_1_data_CB4[a0 - 1]);
        x = -10000.0f;
        if (lbl_1_bss_12A8.unk2C == 0) {
            y = 432.0f - size.y;
        }
        else {
            y = 305.0f;
        }
        lbl_1_bss_12A8.unk50 = HuWinCreate(x, y, size.x, size.y, 0);
        HuWinBGTPLvlSet(lbl_1_bss_12A8.unk50, 0.0f);
        HuWinMesSpeedSet(lbl_1_bss_12A8.unk50, 0);
        HuWinMesSet(lbl_1_bss_12A8.unk50, lbl_1_data_CB4[a0 - 1]);
    }
}

/* 26 insns */
void fn_1_50460(void)
{
    if (lbl_1_bss_12A8.unk40 == 0 && lbl_1_bss_12A8.unk50 != -1) {
        HuWinKill(lbl_1_bss_12A8.unk50);
        lbl_1_bss_12A8.unk50 = -1;
    }
}

