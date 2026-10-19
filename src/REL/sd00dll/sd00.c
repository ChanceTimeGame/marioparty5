/*
 * sd00dll sd00.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/sd00dll/asm/REL/sd00dll/sd00.s.
 */

#include "REL/sd00dll.h"

#ifdef __MWERKS__
#pragma inline_max_size(200)
#endif

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/esprite.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
/* 0x10 lbl_1_rodata_10 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1C lbl_1_rodata_1C (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_28 = 60.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 20.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 35000.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 0.5f; /* 0x34 */
static const float lbl_1_rodata_38 = 640.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 1500.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 300.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 100.0f; /* 0x44 */
/* 0x48 lbl_1_rodata_48 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_54 = 500.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 234.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 600.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 1.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 108.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 138.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 12.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 0.05f; /* 0x70 */
static const float lbl_1_rodata_74 = 0.45f; /* 0x74 */
static const float lbl_1_rodata_78 = 9.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 6.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 2.5f; /* 0x80 */
static const float lbl_1_rodata_84 = 2.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 0.1f; /* 0x88 */
static const float lbl_1_rodata_8C = 0.9f; /* 0x8C */
static const float lbl_1_rodata_90 = 10.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 2.6f; /* 0x94 */
static const float lbl_1_rodata_98 = 320.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 90.0f; /* 0x9C */
/* 0xA0 lbl_1_rodata_A0 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0xA8 lbl_1_rodata_A8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xB4 lbl_1_rodata_B4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xC0 lbl_1_rodata_C0 (0xC): 0x00000000 0x43480000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xCC lbl_1_rodata_CC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xD8 lbl_1_rodata_D8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xE4 lbl_1_rodata_E4 (0xC): 0x00000000 0xC2700000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xF0 lbl_1_rodata_F0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0xFC lbl_1_rodata_FC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x108 lbl_1_rodata_108 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x114 lbl_1_rodata_114 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x120 lbl_1_rodata_120 (0xC): 0x00000000 0x00000000 0x447A0000 -- an aggregate initialiser, write it as a local */
/* 0x12C lbl_1_rodata_12C (0xC): 0x00000000 0x00000000 0xC47A0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_138 = 0.0f; /* 0x138 */
static const float lbl_1_rodata_13C = -1500.0f; /* 0x13C */
static const float lbl_1_rodata_140 = 150.0f; /* 0x140 */
static const float lbl_1_rodata_144 = 130.0f; /* 0x144 */
static const float lbl_1_rodata_148 = 170.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 180.0f; /* 0x14C */
static const float lbl_1_rodata_150 = 250.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 400.0f; /* 0x154 */
static const float lbl_1_rodata_158 = 260.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 15.0f; /* 0x15C */
static const float lbl_1_rodata_160 = 200.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 1250.0f; /* 0x164 */
static const float lbl_1_rodata_168 = 1000.0f; /* 0x168 */
static const float lbl_1_rodata_16C = 0.35f; /* 0x16C */
static const float lbl_1_rodata_170 = 45.0f; /* 0x170 */
/* 0x174 lbl_1_rodata_174 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x180 lbl_1_rodata_180 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x18C lbl_1_rodata_18C (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_198 = -1.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 540.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 1.02f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 1.04f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 1.01f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 128.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = 0.95f; /* 0x1B0 */
/* 0x1B8 lbl_1_rodata_1B8 = 4503599627370496: int->float conversion constant, compiler-generated */
/* 0x1C0 lbl_1_rodata_1C0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1CC lbl_1_rodata_1CC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1D8 lbl_1_rodata_1D8 (0x4): 0xFF, 0xFF, 0xFF, 0x00 -- an aggregate initialiser, write it as a local */
/* 0x1DC lbl_1_rodata_1DC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1E8 lbl_1_rodata_1E8 (0xC): 0x00000000 0x40A00000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x1F4 lbl_1_rodata_1F4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x200 lbl_1_rodata_200 (0xC): 0x00000000 0x40400000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x20C lbl_1_rodata_20C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x218 lbl_1_rodata_218 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_224 = 0.2f; /* 0x224 */
static const float lbl_1_rodata_228 = 5.0f; /* 0x228 */
static const float lbl_1_rodata_22C = 30.0f; /* 0x22C */
static const float lbl_1_rodata_230 = 0.995f; /* 0x230 */
static const float lbl_1_rodata_234 = 0.98f; /* 0x234 */
static const float lbl_1_rodata_238 = 0.92f; /* 0x238 */
static const float lbl_1_rodata_23C = 64.0f; /* 0x23C */
static const float lbl_1_rodata_240 = 1.005f; /* 0x240 */
static const float lbl_1_rodata_244 = 1.06f; /* 0x244 */
static const float lbl_1_rodata_248 = 1.03f; /* 0x248 */
/* 0x24C lbl_1_rodata_24C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x258 lbl_1_rodata_258 (0x4): 0xDA, 0xCB, 0x9E, 0x64 -- an aggregate initialiser, write it as a local */
/* 0x25C lbl_1_rodata_25C (0x4): 0xDA, 0xCB, 0x80, 0x64 -- an aggregate initialiser, write it as a local */
/* 0x260 lbl_1_rodata_260 (0x4): 0x00, 0x00, 0x00, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x264 lbl_1_rodata_264 (0x4): 0xFF, 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x268 lbl_1_rodata_268 (0x4): 0x00, 0x00, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x26C lbl_1_rodata_26C (0x4): 0xFF, 0x00, 0x00, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x270 lbl_1_rodata_270 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x27C lbl_1_rodata_27C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x288 lbl_1_rodata_288 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_294 = 0.25f; /* 0x294 */
static const float lbl_1_rodata_298 = 0.017453292f; /* 0x298 */
static const float lbl_1_rodata_29C = 4.0f; /* 0x29C */
/* 0x2A0 lbl_1_rodata_2A0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_2AC = 21.0f; /* 0x2AC */
static const double lbl_1_rodata_2B0 = 6.0; /* 0x2B0 */
static const float lbl_1_rodata_2B8 = 1.1f; /* 0x2B8 */
static const float lbl_1_rodata_2BC = 3.0f; /* 0x2BC */
static const float lbl_1_rodata_2C0 = 18.0f; /* 0x2C0 */
/* 0x2C4 lbl_1_rodata_2C4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x2D0 lbl_1_rodata_2D0 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_2DC = 0.005f; /* 0x2DC */
static const float lbl_1_rodata_2E0 = 50.0f; /* 0x2E0 */
static const float lbl_1_rodata_2E4 = 2000.0f; /* 0x2E4 */
static const double lbl_1_rodata_2E8 = 3.141592653589793; /* 0x2E8 */
static const float lbl_1_rodata_2F0 = -360.0f; /* 0x2F0 */
static const float lbl_1_rodata_2F4 = 360.0f; /* 0x2F4 */
static const float lbl_1_rodata_2F8 = 0.4f; /* 0x2F8 */
static const float lbl_1_rodata_2FC = 0.01f; /* 0x2FC */
static const float lbl_1_rodata_300 = -0.01f; /* 0x300 */
/* 0x304 lbl_1_rodata_304 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_310 = 8.333333f; /* 0x310 */
static const float lbl_1_rodata_314 = 80.0f; /* 0x314 */
/* 0x318 lbl_1_rodata_318 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x324 lbl_1_rodata_324 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x330 lbl_1_rodata_330 (0x4): 0xFF, 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x334 lbl_1_rodata_334 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x340 lbl_1_rodata_340 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x34C lbl_1_rodata_34C (0x4): 0xFF, 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_350 = 25.0f; /* 0x350 */
/* 0x354 lbl_1_rodata_354 (0x8): 0x00000003 0x00000005 -- an aggregate initialiser, write it as a local */
/* 0x35C lbl_1_rodata_35C (0x8): 0x00000002 0x00000001 -- an aggregate initialiser, write it as a local */
/* 0x364 lbl_1_rodata_364 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x370 lbl_1_rodata_370 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_37C = 56.0f; /* 0x37C */
static const float lbl_1_rodata_380 = -8.0f; /* 0x380 */
static const float lbl_1_rodata_384 = 8.0f; /* 0x384 */
/* 0x388 lbl_1_rodata_388 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x394 lbl_1_rodata_394 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_3A0 = 0.001f; /* 0x3A0 */
/* 0x3A4 lbl_1_rodata_3A4 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x3B0 lbl_1_rodata_3B0 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x3BC lbl_1_rodata_3BC (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x3C8 lbl_1_rodata_3C8 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x3D4 lbl_1_rodata_3D4 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const double lbl_1_rodata_3E0 = 180.0; /* 0x3E0 */
static const float lbl_1_rodata_3E8 = -180.0f; /* 0x3E8 */
static const double lbl_1_rodata_3F0 = 1.0; /* 0x3F0 */
static const float lbl_1_rodata_3F8 = 1.5f; /* 0x3F8 */
static const float lbl_1_rodata_3FC = 0.087f; /* 0x3FC */
static const float lbl_1_rodata_400 = 120.0f; /* 0x400 */
static const float lbl_1_rodata_404 = 0.19f; /* 0x404 */
/* 0x408 lbl_1_rodata_408 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x414 lbl_1_rodata_414 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_420 = -0.5f; /* 0x420 */
static const float lbl_1_rodata_424 = 8191.0f; /* 0x424 */
/* 0x428 lbl_1_rodata_428 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x434 lbl_1_rodata_434 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x440 lbl_1_rodata_440 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_44C = 0.75f; /* 0x44C */
/* 0x450 lbl_1_rodata_450 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_45C = -500.0f; /* 0x45C */
static const float lbl_1_rodata_460 = 350.0f; /* 0x460 */
/* 0x464 lbl_1_rodata_464 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x470 lbl_1_rodata_470 (0xC): 0x3F800000 0x3F800000 0x3F800000 -- an aggregate initialiser, write it as a local */
/* 0x47C lbl_1_rodata_47C (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x488 lbl_1_rodata_488 (0xC): 0x00000000 0x43960000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x494 lbl_1_rodata_494 (0xC): 0x00000000 0x43960000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4A0 lbl_1_rodata_4A0 (0xC): 0x00000000 0x43960000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4AC lbl_1_rodata_4AC (0xC): 0x00000000 0x43960000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4B8 lbl_1_rodata_4B8 (0xC): 0x00000000 0x43960000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4C4 lbl_1_rodata_4C4 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_4D0 = -1400.0f; /* 0x4D0 */
static const float lbl_1_rodata_4D4 = -1900.0f; /* 0x4D4 */
static const float lbl_1_rodata_4D8 = -1904.9999f; /* 0x4D8 */
static const float lbl_1_rodata_4DC = 38.1f; /* 0x4DC */
/* 0x4E0 lbl_1_rodata_4E0 (0xC): 0x00000000 0x3F800000 0x00000000 -- an aggregate initialiser, write it as a local */
/* 0x4EC lbl_1_rodata_4EC (0xC): 0x00000000 0x00000000 0x44FA0000 -- an aggregate initialiser, write it as a local */
/* 0x4F8 lbl_1_rodata_4F8 (0xC): 0x00000000 0x00000000 0x43FA0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_504 = 480.0f; /* 0x504 */
static const float lbl_1_rodata_508 = 1.2f; /* 0x508 */
static const float lbl_1_rodata_50C = 32.0f; /* 0x50C */
static const float lbl_1_rodata_510 = 0.060000002f; /* 0x510 */
static const float lbl_1_rodata_514 = 240.0f; /* 0x514 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x4 gap_05_00000004_bss (0x4): alignment gap */
/* 0x0 */ SDSYS *sys;

static void SdSeqInit(s16 mode, s16 frameNo);
static void SdSeqFadeIn(s16 mode, s16 frameNo);
static void SdSeqStart(s16 mode, s16 frameNo);
static void SdSeqMain(s16 mode, s16 frameNo);
static void SdSeqFinish(s16 mode, s16 frameNo);
static void SdSeqPreWinner(s16 mode, s16 frameNo);
static void SdSeqWinner(s16 mode, s16 frameNo);
static void SdSeqFadeOut(s16 mode, s16 frameNo);
static void SdSeqClose(s16 mode, s16 frameNo);
static void SdSeqUpdate(void);
static void SdSeqMachineSet(SDMACHINE *machine, s32 playerNo, s32 tireNo, s32 bodyNo, s32 partNo3, s32 gunNo, s32 charNo);
static s32 SdSeqMachineUpdate(SDMACHINE *machine);
static void MachineParticleUpdate(SDMACHINE *machine);
static void MachineExhaustUpdate(SDMACHINE *machine);
static void MachineExhaustAdd(SDMACHINE *machine);
static void MachineTrackEffUpdate(SDMACHINE *machine);
static void MachineTrackEffAdd(SDMACHINE *machine);
static void MachineEffectUpdate(SDMACHINE *machine);
static void MachineModeIdle(SDMACHINE *machine);
static void MachineMotionUpdate(SDMACHINE *machine);
static void MachineModeDamage(SDMACHINE *machine);
static void MachineFireCreate(SDMACHINE *machine);
static void MachineFireHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
static void MachineModeLaunch(SDMACHINE *machine);
static void MachineModeDie(SDMACHINE *machine);
static void MachineColUpdate(void);
static void MachineColSeparate(SDMACHINE *machine);
static void PlayDamageSound(void);
static void UpdateEnginePitch(SDMACHINE *machine, float pitch);
static void MachineDispSet(SDMACHINE *machine, s32 dispF);
static void MachineScaleSet(SDMACHINE *machine, HuVecF scale);
static void MachineCameraBitSet(SDMACHINE *machine, s32 cameraBit);
static void MachineCameraInit(SDMACHINE *machine, s32 a1);
static void MachineVelocityApply(SDMACHINE *machine, HuVecF *a1, HuVecF *a2);
static void MachineViewUpdate(s32 cameraNo, s32 a1, HuVecF a2, HuVecF a3, HuVecF a4, float a5);
static void MachinePosSet(SDMACHINE *machine, HuVecF pos);
static void MachinePosInit(SDMACHINE *machine);
static void MachineRotSet(SDMACHINE *machine, HuVecF rot);
static void MachineRotApply(SDMACHINE *machine, HuVecF *rot);
static void MachineRotAngleSet(SDMACHINE *machine, HuVecF *rot);
static void MachineRotAngleApply(SDMACHINE *machine, HuVecF *rot);
static void CameraSetViewPos(s32 cameraNo, HuVecF eye, HuVecF up, HuVecF target);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ s32 sdCameraBitTbl[8] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80 };
/* 0x20 */ static MGSEQ_PARAM seqModeTbl = { 0, 0, SdSeqInit, SdSeqFadeIn, SdSeqStart, SdSeqMain, SdSeqFinish, SdSeqPreWinner, SdSeqWinner, SdSeqFadeOut, SdSeqClose };

/* 73 insns */
void ObjectSetup(void)
{
    sys = HuMemDirectMallocNum(HEAP_MODEL, sizeof(SDSYS), HU_MEMNUM_OVL);
    memset(sys, 0, sizeof(SDSYS));
    sys->objman = omInitObjMan(200, 0x2000);
    omGameSysInit(sys->objman);
    SdCameraCreate();
    sys->cameraObj = omAddObjEx(sys->objman, 0, 0, 0, -1, SdCameraUpdate);
    sys->unk1E4[5] = -1;
    sys->unk15C = -1;
    sys->unkFF0 = -1;
    sys->streamNo = -1;
    MgSeqCreate(&seqModeTbl);
    HuWinInit(1);
}

/* 237 insns */
static void SdSeqInit(s16 mode, s16 frameNo)
{
    GWSDBATTLE *battle;
    SDMACHINE *machine;
    s32 i;
    s32 temp;

    battle = &GwSdBattle;
    Hu3DBGColorSet(0, 0, 0);
    Hu3DShadowMultiCreate(60.0f, 20.0f, 35000.0f, 3);
    Hu3DShadowMultiTPLvlSet(0.5f, 3);
    Hu3DShadowMultiSizeSet(128, 3);
    sys->gameType = battle->gameType;
    sys->unkC = battle->stageNo;
    if (battle->stageType1 != -1) {
        sys->comLevel = battle->stageType1;
    } else {
        sys->comLevel = battle->stageType2;
    }
    for (i = 0; i < 2; i++) {
        SdMachineConfigSet(i);
        sys->unk40[i] = battle->padNo[i];
    }
    sys->unk8 = 0;
    SdMachineEffectCreate();
    SdStageInit(sys->unkC);
    sys->unkC = 0;
    for (i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        temp = machine->com.unk3C;
        SdSeqMachineSet(machine, i, machine->tireNo, machine->bodyNo, machine->unk3C0, machine->gunNo, machine->charNo);
        machine->com.unk3C = temp;
        MachinePosInit(machine);
        MachineCameraInit(machine, 0);
    }
    SdMachineParticleCreate();
    SdStageObjCreate();
    SdSprCreate();
    SdCameraSplitSet(640.0f);
    for (i = 0; i < 60; i++) {
        SdSeqUpdate();
    }
    for (i = 0; i < 2; i++) {
        HuVecF eye;
        HuVecF target;
        machine = &sys->machine[i];
        eye = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
        PSVECNormalize(&eye, &eye);
        PSVECScale(&eye, &eye, 1500.0f);
        PSVECAdd(&machine->pos, &eye, &eye);
        eye.y += 300.0f;
        target = machine->pos;
        target.y += 100.0f;
        CameraSetViewPos(i, eye, (HuVecF){ 0.0f, 1.0f, 0.0f }, target);
    }
    SdFlagInit();
    SdRabbitInit();
    MgSeqModeNext();
}

/* 1055 insns */
static void SdSeqFadeIn(s16 mode, s16 frameNo)
{
    SDSPRWORK *spr;
    s32 i;
    s32 j;
    s32 k;
    s32 done;
    s32 time;
    s32 delay;
    s32 delay2;
    s32 hp;
    float t;
    HuVecF dir;
    HuVecF vel;

    spr = &sys->spr;
    switch (sys->unk8) {
        case 0:
            SdAuxSet();
            HuAudJinglePlay(133);
            SdHpSprCreate();
            sys->unk8++;
        case 1:
            for (i = 0; i < 2; i++) {
                sys->camera[i].unk7C = 1;
                sys->camera[i].unk80 = 500.0f;
            }
            sys->unk1C = sys->unk20 = sys->unk24 = sys->unk28 = 0;
            sys->unkC = sys->unk10 = sys->unk14 = 0;
            sys->unk8++;
            break;
        case 2:
            sys->unk1C++;
            t = MathLerp(2, sys->unk1C / 234.0f);
            for (i = 0; i < 2; i++) {
                sys->camera[i].unk80 = 500.0f + 500.0f * t;
                MachineVelocityApply(&sys->machine[i], &vel, &dir);
                sys->camera[i].target.y = sys->camera[i].targetCur.y = sys->machine[i].pos.y + 300.0f * t;
                dir = (HuVecF){ 300.0f + sys->machine[i].pos.x - 600.0f * i, 100.0f + sys->machine[i].pos.y, sys->machine[i].pos.z };
                MachineViewUpdate(i, i, dir, vel, sys->machine[i].pos, t);
            }
            if (t >= 1.0f) {
                sys->camera[0].unk4 = sys->camera[1].unk4 = 1;
            }
            if (sys->unk1C >= 60.0f && sys->unkC == 0) {
                sys->unkC = 1;
            }
            if (sys->unk1C >= 108.0f && sys->unk10 == 0 && sys->gameType == 0) {
                sys->unk10 = 1;
            }
            if (sys->unk1C >= 138.0f && sys->unk14 == 0) {
                sys->unk14 = 1;
            }
            if (sys->unk1C > 234.0f) {
                sys->unk8++;
            }
            break;
        case 3:
            sys->unk1C++;
            SdHpSprKill();
            sys->unk8++;
            break;
        case 4:
            sys->unk1C++;
            break;
    }
    switch (sys->unkC) {
        case 0:
            break;
        case 1:
            espDispOn(spr->unk24);
            espScaleSet(spr->unk24, 0.5f * (sys->unk20 / 12.0f), 0.05f);
            if (++sys->unk20 < 12.0f) {
                break;
            }
            sys->unk20 = 0;
            sys->unkC++;
            break;
        case 2:
            espScaleSet(spr->unk24, 0.5f, 0.05f + 0.45f * (sys->unk20 / 9.0f));
            if (++sys->unk20 < 9.0f) {
                break;
            }
            espScaleSet(spr->unk24, 0.5f, 0.5f);
            sys->unk20 = 0;
            sys->unkC++;
            break;
        case 3:
            done = 0;
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 3; j++) {
                    if (sys->unk20 == 6.0f * j) {
                        espDispOn(spr->unk46[i][j]);
                    }
                    delay = sys->unk20 - 6.0f * j;
                    t = delay / 12.0f;
                    if (t > 1.0f) {
                        t = 1.0f;
                        if (j == 2) {
                            done = 1;
                        }
                    }
                    espScaleSet(spr->unk46[i][j], 2.5f - 2.0f * t, 2.5f - 2.0f * t);
                    espTPLvlSet(spr->unk46[i][j], 0.1f + 0.9f * t);
                }
            }
            sys->unk20++;
            if (done) {
                for (i = 0; i < 2; i++) {
                    for (j = 0; j < 3; j++) {
                        espDispOff(spr->unk46[i][j]);
                    }
                    espDispOn(spr->unk26[i]);
                }
                sys->unk20 = 0;
                sys->unkC++;
            }
            break;
        case 4:
            break;
    }
    switch (sys->unk10) {
        case 0:
            break;
        case 1:
            for (i = 0; i < 2; i++) {
                for (j = 0; j < 8; j++) {
                    hp = sys->machine[i].unkE4 - j * 4;
                    delay = 10.0f * j;
                    done = 0;
                    for (k = 0; k < 3; k++) {
                        delay2 = 6.0f * k;
                        if (sys->unk24 == delay + delay2 && hp > 0) {
                            espDispOn(spr->unk52[i][j][k]);
                        }
                        time = sys->unk24 - (delay + delay2);
                        t = time / 12.0f;
                        if (t > 1.0f) {
                            t = 1.0f;
                            if (k == 2) {
                                done = 1;
                                if (j == 7) {
                                    done = 2;
                                }
                            }
                        }
                        espScaleSet(spr->unk52[i][j][k], 2.6f - 2.0f * t, 2.6f - 2.0f * t);
                        espTPLvlSet(spr->unk52[i][j][k], 0.1f + 0.9f * t);
                    }
                    if (done) {
                        if (hp > 0) {
                            espDispOn(spr->unk4[i][j]);
                        }
                        for (k = 0; k < 3; k++) {
                            espDispOff(spr->unk52[i][j][k]);
                        }
                    }
                    for (k = 0; k < 3; k++) {
                        if (spr->unk52[i][j][k] != -1) {
                            SdSprScissorUpdate(spr->unk52[i][j][k], i);
                        }
                    }
                    SdSprScissorUpdate(spr->unk4[i][j], i);
                }
            }
            sys->unk24++;
            if (done == 2) {
                sys->unk24 = 0;
                sys->unk10++;
            }
            break;
        case 2:
            break;
    }
    switch (sys->unk14) {
        case 0:
            break;
        case 1:
            sys->unk28++;
            t = 320.0f * MathLerp(1, sys->unk28 / 90.0f);
            SdCameraSplitSet(640.0f - t);
            if (sys->unk28 > 90.0f) {
                SdCameraSplitSet(320.0f);
                sys->unk28 = 0;
                sys->unk14++;
            }
            break;
        case 2:
            break;
    }
    SdSeqUpdate();
}

/* 62 insns */
static void SdSeqStart(s16 mode, s16 frameNo)
{
    sys->unk1C++;
    sys->unk8 = 0;
    if (sys->streamNo == -1 && (GameMesStatGet(GAMEMES_ID_NONE) & GAMEMES_STAT_FXPLAY)) {
        sys->streamNo = HuAudBGMPlay(sys->gameType + 44);
    }
    SdSeqUpdate();
    if (sys->timer == 0) {
        sys->timer = MgTimerCreate(0);
        MgTimerParamSet(sys->timer, 5400, 0, 0);
    }
}

/* 300 insns */
static void SdSeqMain(s16 mode, s16 frameNo)
{
    s32 winner = 0;
    s32 end;
    s32 i;

    if (MgSeqFrameNoGet() == 0) {
        sys->unk8 = 0;
        if (sys->unk38 == 0) {
            MgTimerModeOnSet(sys->timer, 1);
        }
    }
    sys->unk1C++;
    sys->unk34 = MgTimerValueGet(sys->timer);
    sys->unk34 /= 60.0f;
    SdSeqUpdate();
    winner = end = 0;
    if (sys->gameType == 0) {
        if (sys->machine[0].unkE4 <= 0 || sys->machine[1].unkE4 <= 0) {
            end = 1;
        }
    } else if (sys->gameType == 1) {
        if (SdFlagDispTimerGet(0) >= 3) {
            winner = end = 1;
        } else if (SdFlagDispTimerGet(1) >= 3) {
            winner = end = 2;
        }
    } else if (sys->gameType == 2) {
        if (SdRabbitDispTimerGet(0) >= 3) {
            winner = end = 1;
        } else if (SdRabbitDispTimerGet(1) >= 3) {
            winner = end = 2;
        }
    }
    if (winner != 0 && sys->machine[0].mode < 2 && sys->machine[1].mode < 2) {
        if (winner == 1) {
            sys->machine[0].mode = 5;
            sys->machine[1].mode = 4;
        } else {
            sys->machine[1].mode = 5;
            sys->machine[0].mode = 4;
        }
    }
    winner = 1;
    if (sys->machine[0].mode == 4 && sys->machine[1].mode != 4) {
        MgTimerModeOffSet(sys->timer);
        sys->machine[1].mode = 5;
    }
    if (sys->machine[1].mode == 4 && sys->machine[0].mode != 4) {
        MgTimerModeOffSet(sys->timer);
        sys->machine[0].mode = 5;
    }
    for (i = 0; i < 2; i++) {
        if (sys->machine[i].mode < 4) {
            winner = 0;
            break;
        }
        if (sys->machine[i].unk4 == 0) {
            winner = 0;
            break;
        }
    }
    if (end == 0 && MgTimerDoneCheck(sys->timer)) {
        sys->unkB68 = 1;
    }
    if (winner == 1 || sys->unkB68 != 0) {
        if (winner == 1 && sys->unkB68 == 0) {
            sys->unkB6C = 1;
        }
        if (sys->unk38 == 0 && sys->timer->stopF == 0) {
            sys->timer->stopF = 1;
            sys->timer->mode = 1;
        }
        MgSeqModeNext();
    }
}

/* 145 insns */
static void SdSeqFinish(s16 mode, s16 frameNo)
{
    GWSDBATTLE *battle = &GwSdBattle;

    SdSeqUpdate();
    sys->winnerNo = -1;
    if (sys->machine[0].mode == 5) {
        sys->winnerNo = 0;
    } else if (sys->machine[1].mode == 5) {
        sys->winnerNo = 1;
    }
    if (sys->streamNo != -1) {
        HuAudSStreamFadeOut(sys->streamNo, 100);
        sys->streamNo = -1;
    }
    if (sys->winnerNo == -1) {
        SdMachineFxStop(&sys->machine[0]);
        SdMachineFxStop(&sys->machine[1]);
    }
    battle->winnerNo = sys->winnerNo;
    if (sys->gameType == 0) {
        sdHealthLoss[0] = sys->machine[0].unk3D8 * 4 - sys->machine[0].unkE4;
        sdHealthLoss[1] = sys->machine[1].unk3D8 * 4 - sys->machine[1].unkE4;
    } else if (sys->gameType == 1) {
        sdHealthLoss[0] = SdFlagDispTimerGet(0);
        sdHealthLoss[1] = SdFlagDispTimerGet(1);
    } else {
        sdHealthLoss[0] = SdRabbitDispTimerGet(0);
        sdHealthLoss[1] = SdRabbitDispTimerGet(1);
    }
}

/* 1070 insns */
static void SdSeqPreWinner(s16 mode, s16 frameNo)
{
    s32 winnerNo;
    SDSPRWORK *spr;
    SDMACHINE *winner;
    SDMACHINE *loser;
    SDCAMERA *camera;
    SDMACHINE *machine;
    s32 i;
    s32 j;
    s32 charNo;
    float x;
    float y;
    float z;
    float t;

    winnerNo = sys->winnerNo;
    spr = &sys->spr;
    if (sys->unkB68 != 0
        && (sys->machine[0].mode == 2 || sys->machine[0].mode == 3 || sys->machine[0].unk90 != 0 || sys->machine[1].mode == 2
            || sys->machine[1].mode == 3 || sys->machine[1].unk90 != 0)) {
        SdSeqUpdate();
        return;
    }
    if (winnerNo == -1) {
        sys->unkB70 = 1;
        MgSeqWinnerSet(CHARNO_NONE, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
        MgSeqModeNext();
        return;
    }
    winner = &sys->machine[winnerNo];
    loser = &sys->machine[winnerNo ^ 1];
    camera = &sys->camera[winnerNo];
    MgSeqModeChangeOff();
    switch (sys->unk8) {
        case 0:
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 45);
            WipeColorSet(255, 255, 255);
            sys->unkC = sys->unk20 = 0;
            sys->unk8++;
            break;
        case 1:
            if (WipeCheckEnd()) {
                break;
            }
            sys->unkB70 = 1;
            camera->unk7C = 0;
            SdStageClose();
            SdSprHideAll();
            SdCharInit(winner, loser);
            Hu3DModelCameraSet(sys->stageMdlId, sdCameraBitTbl[winnerNo]);
            if (sys->unk168 != -1) {
                Hu3DModelCameraSet(sys->unk168, sdCameraBitTbl[winnerNo]);
            }
            if (sys->unk160[winnerNo ^ 1] != -1) {
                Hu3DModelAttrSet(sys->unk160[winnerNo ^ 1], HU3D_ATTR_DISPOFF);
            }
            if (sys->stageNo == 7) {
                SdParticleCameraSet(winnerNo);
            }
            for (i = 0; i < 2; i++) {
                machine = (i == 0) ? winner : loser;
                SdMachineFxStop(machine);
                Hu3DModelPosSetV(machine->unk3B0, &winner->pos);
                Hu3DModelAttrSet(machine->charMdl, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(machine->unk3B0, HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(machine->unk3B0, HU3D_MOTATTR_PAUSE);
                if (sys->stageNo != 7 && sys->stageNo != 2) {
                    Hu3DModelAttrSet(machine->unk3B4, HU3D_ATTR_DISPOFF);
                    Hu3DModelShadowSet(machine->bodyMdl);
                    Hu3DModelShadowSet(machine->gunMdl);
                }
                Hu3DMotionTimeSet(machine->bodyMdl, 0.0f);
                Hu3DMotionSpeedSet(machine->bodyMdl, 0.0f);
                Hu3DMotionShapeTimeSet(machine->bodyMdl, 0.0f);
                Hu3DMotionShapeSpeedSet(machine->bodyMdl, 0.0f);
                Hu3DModelAttrSet(machine->gunMdl, HU3D_MOTATTR_PAUSE | HU3D_MOTATTR_SHAPE_PAUSE);
                for (j = 0; j < 4; j++) {
                    if (machine->tireMdl[j] != -1 && sys->stageNo != 7 && sys->stageNo != 2) {
                        Hu3DModelShadowSet(machine->tireMdl[j]);
                    }
                }
                MachineCameraBitSet(machine, sdCameraBitTbl[winnerNo]);
                Hu3DModelCameraSet(machine->unk3B0, sdCameraBitTbl[winnerNo]);
            }
            Hu3DModelAttrSet(sys->unk1E4[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[3], HU3D_ATTR_DISPOFF);
            MachineCameraBitSet(winner, 3);
            MachineCameraBitSet(loser, 3);
            x = y = z = 0.0f;
            if (sys->stageNo == 2 || sys->stageNo == 7) {
                z = -1500.0f;
            } else if (sys->stageNo == 5) {
                x = 150.0f;
            } else if (sys->stageNo == 6) {
                y = 130.0f;
            }
            if (winner->bodyNo == 3 && winner->tireNo == 5) {
                y += 10.0f;
            }
            if (winner->unk368 & 2) {
                MachinePosSet(winner, (HuVecF){ x - 170.0f, y + winner->unk360, z + (60.0f + winner->unk358) });
            } else {
                MachinePosSet(winner, (HuVecF){ x - 170.0f, y, z + (60.0f + winner->unk358) });
            }
            MachineRotSet(winner, (HuVecF){ 0.0f, 200.0f, 0.0f });
            Hu3DModelPosSet(winner->unk3B0, x, y, z);
            Hu3DModelRotSet(winner->unk3B0, 0.0f, 180.0f, 0.0f);
            camera->targetCur = camera->target = (HuVecF){ x, 150.0f + y, z };
            camera->eyeCur = camera->eye = (HuVecF){ x, 250.0f + y, z - 400.0f };
            y = 0.0f;
            if (sys->stageNo == 6) {
                y = 130.0f;
            }
            if (loser->bodyNo == 3 && loser->tireNo == 5) {
                y += 10.0f;
            }
            MachineRotSet(loser, (HuVecF){ 0.0f, -60.0f, 0.0f });
            if (loser->unk368 & 2) {
                MachinePosSet(loser, (HuVecF){ 260.0f + x, y + loser->unk360, 15.0f + (loser->unk360 + (300.0f + z + loser->unk358)) });
            } else {
                MachinePosSet(loser, (HuVecF){ 260.0f + x, y, 15.0f + (loser->unk360 + (300.0f + z + loser->unk358)) });
            }
            if (winner->charNo != 11) {
                Hu3DModelPosSet(loser->unk3B0, 200.0f + x, y, 250.0f + z);
            } else {
                Hu3DModelPosSet(loser->unk3B0, 250.0f + x, y, 200.0f + z);
            }
            Hu3DModelRotSet(loser->unk3B0, 0.0f, 200.0f, 0.0f);
            if (sys->stageNo != 7 && sys->stageNo != 2) {
                Hu3DShadowMultiSizeSet(240, 3);
            } else {
                Hu3DModelPosSetV(winner->unk3B4, &winner->pos);
                Hu3DModelPosSetV(loser->unk3B4, &loser->pos);
            }
            if (sys->stageNo != 3) {
                Hu3DShadowBuf[winnerNo].camTarget = (HuVecF){ x, y, 0.0f };
                Hu3DShadowBuf[winnerNo].camPos = (HuVecF){ x, 1250.0f + y, 0.0f };
            } else {
                Hu3DShadowBuf[winnerNo].camTarget = (HuVecF){ x, y - 1000.0f, 1000.0f };
                Hu3DShadowBuf[winnerNo].camPos = (HuVecF){ x, 1000.0f + y, -1000.0f };
            }
            Hu3DShadowMultiTPLvlSet(0.35f, 3);
            Hu3DShadowBuf[winnerNo].camTarget.z += z;
            Hu3DShadowBuf[winnerNo].camPos.z += z;
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 45);
            sys->unk8++;
            break;
        case 2:
            if (WipeCheckEnd()) {
                break;
            }
            sys->unk1C = sys->unk20 = 0;
            Hu3DModelAttrReset(winner->unk3B0, HU3D_MOTATTR_PAUSE);
            Hu3DModelAttrReset(loser->unk3B0, HU3D_MOTATTR_PAUSE);
            if (sys->machine[winnerNo].charNo < 10) {
                charNo = sys->machine[winnerNo].charNo;
            } else if (sys->machine[winnerNo].charNo == 10) {
                charNo = 13;
            } else {
                charNo = 14;
            }
            MgSeqWinnerSet(charNo, CHARNO_NONE, CHARNO_NONE, CHARNO_NONE);
            WipeColorSet(0, 0, 0);
            MgSeqModeDelaySet(MGSEQ_MODE_WINNER, 260);
            MgSeqModeNext();
            break;
    }
    if (sys->unkC == 0 && winnerNo != -1) {
        sys->unk20++;
        t = 320.0f * MathLerp(0, sys->unk20 / 45.0f);
        if (winnerNo == 0) {
            SdCameraSplitSet(320.0f + t);
        } else {
            SdCameraSplitSet(320.0f - t);
        }
        if (sys->unk20 > 45.0f) {
            SdCameraSplitSet(640.0f - 640.0f * winnerNo);
            sys->unk20 = 0;
            sys->unkC++;
        }
    }
    SdSeqUpdate();
}

/* 0x48 */ static u8 winnerSoundDelayTbl[12] = { 13, 0, 23, 105, 13, 29, 20, 13, 13, 13, 0, 0 };

/* 52 insns */
static void SdSeqWinner(s16 mode, s16 frameNo)
{
    if (sys->winnerNo != -1 && sys->unk20 == winnerSoundDelayTbl[sys->machine[sys->winnerNo].charNo]) {
        SdPlayerSoundPlay(&sys->machine[sys->winnerNo], 5);
    }
    sys->unk20++;
    SdSeqUpdate();
}

/* 24 insns */
static void SdSeqFadeOut(s16 mode, s16 frameNo)
{
    if (sys->unkFF0 != -1) {
        HuAudFXStop(sys->unkFF0);
        sys->unkFF0 = -1;
    }
    SdSeqUpdate();
}

/* 16 insns */
static void SdSeqClose(s16 mode, s16 frameNo)
{
    HuAudAUXSet(0, 1);
    SdFlagClose();
    SdRabbitClose();
    GameMesClose();
    HuAudAllStop();
    Hu3DModelAllKill();
    Hu3DLightAllKill();
}

/* 167 insns */
static void SdSeqUpdate(void)
{
    SDMACHINE *machine;
    s32 i;

    SdStageUpdate();
    for (i = 0; i < 2; i++) {
        if (MgSeqModeGet() >= MGSEQ_MODE_MAIN && MgSeqModeGet() <= MGSEQ_MODE_PREWIN && sys->unkB70 == 0) {
            SdSeqMachineUpdate(&sys->machine[i]);
        }
        if (MgSeqModeGet() >= MGSEQ_MODE_MAIN && MgSeqModeGet() < MGSEQ_MODE_PREWIN) {
            SdBulletUpdate(&sys->machine[i]);
        }
    }
    if (MgSeqModeGet() <= MGSEQ_MODE_PREWIN && sys->unkB70 == 0) {
        MachineColUpdate();
    }
    for (i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        if (MgSeqModeGet() <= MGSEQ_MODE_MAIN) {
            MachineColSeparate(machine);
        }
        if (MgSeqModeGet() <= MGSEQ_MODE_PREWIN && sys->unkB70 == 0) {
            SdStageMachineCol(machine);
            Hu3DModelPosSetV(machine->bodyMdl, &machine->pos);
            Hu3DModelRotSetV(machine->bodyMdl, &machine->rot);
            Hu3DModelPosSetV(machine->unk3B4, &machine->pos);
            MachineCameraInit(machine, 1);
            if (MgSeqModeGet() < MGSEQ_MODE_MAIN) {
                PSMTXCopy(machine->mtx, machine->unk108);
                machine->unk138 = machine->pos;
                machine->unk144 = machine->rot;
                machine->unk15C = machine->unkE0;
                machine->unkF8 = machine->unkE8 = (HuVecF){ 0.0f, 0.0f, 0.0f };
            }
            PSVECSubtract(&machine->pos, &machine->unk138, &machine->unk160);
        }
        if (MgSeqModeGet() > MGSEQ_MODE_INIT && MgSeqModeGet() < MGSEQ_MODE_PREWIN) {
            MachineParticleUpdate(&sys->machine[i]);
        }
    }
    if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
        PlayDamageSound();
    }
    SdVibrateUpdate();
    SdSprUpdate();
    SdFlagUpdate();
    SdRabbitUpdate();
    SdImpactUpdate();
}

/* 50 insns */
static void SdSeqMachineSet(SDMACHINE *machine, s32 playerNo, s32 tireNo, s32 bodyNo, s32 partNo3, s32 gunNo, s32 charNo)
{
    memset(machine, 0, sizeof(SDMACHINE));
    machine->mode = 1;
    machine->playerNo = playerNo;
    machine->cameraNo = playerNo;
    machine->unk348 = sys->unk40[playerNo];
    machine->tireNo = tireNo;
    machine->bodyNo = bodyNo;
    machine->unk3C0 = partNo3;
    machine->gunNo = gunNo;
    machine->charNo = charNo;
    SdMachineCreate(machine);
    PSMTXIdentity(machine->mtx);
    PSMTXCopy(machine->mtx, machine->unk108);
}

/* 755 insns */
static s32 SdSeqMachineUpdate(SDMACHINE *machine)
{
    s16 mdlA;
    s16 mdlB;
    s32 level;
    s32 i;
    HuVecF rot;
    s32 result = 0;

    PSMTXCopy(machine->mtx, machine->unk108);
    machine->unk138 = machine->pos;
    machine->unk144 = machine->rot;
    machine->unk15C = machine->unkE0;
    machine->unk28C = machine->unk3CC;
    machine->unk290 = machine->unk3D0;
    machine->unk288 = machine->unk3C8;
    if (!(machine->unk368 & 0x10)) {
        if (machine->unk28 == 1) {
            machine->unk290++;
            machine->unk28C++;
        } else if (machine->unk28 == 2) {
            machine->unk290 += 2;
            machine->unk28C += 2;
        }
    }
    if ((machine->unk368 & 0x50) != 0x50) {
        if (machine->unk28 == 3) {
            machine->unk288--;
            machine->unk28C--;
        } else if (machine->unk28 == 4) {
            machine->unk288 -= 2;
            machine->unk28C -= 2;
        }
    }
    if (!(machine->unk368 & 0x40) && machine->unk28 == 5 && machine->mode == 1 && machine->unk210 == 0) {
        HuVecF dir;
        dir = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
        PSVECScale(&dir, &dir, -1.0f);
        if (machine->bodyNo == 10) {
            SdMachineDamage(machine, dir, 2);
        } else {
            SdMachineDamage(machine, dir, 4);
        }
    }
    machine->unk28C = (machine->unk28C > 8) ? 8 : ((machine->unk28C < 1) ? 1 : machine->unk28C);
    machine->unk290 = (machine->unk290 > 8) ? 8 : ((machine->unk290 < 1) ? 1 : machine->unk290);
    machine->unk288 = (machine->unk288 > 8) ? 8 : ((machine->unk288 < 1) ? 1 : machine->unk288);
    if (GwPlayerConf[machine->playerNo].type != 0 && machine->com.unk3C == 0) {
        level = sys->unk34;
        if (level >= 45) {
            level = 9;
        } else {
            level = level / 5;
        }
        machine->unk288 = 10 - level;
        machine->unk290 = level;
        machine->unk28C = level;
        machine->unk288 = (machine->unk288 > 8) ? 8 : ((machine->unk288 < 1) ? 1 : machine->unk288);
        machine->unk28C = (machine->unk28C > 9) ? 9 : ((machine->unk28C < 1) ? 1 : machine->unk28C);
        machine->unk290 = (machine->unk290 > 9) ? 9 : ((machine->unk290 < 1) ? 1 : machine->unk290);
    }
    if (machine->unk328 != 0) {
        if (machine->unk328 == 1) {
            machine->unk28C += 2;
            machine->unk288 -= 1;
            machine->unk290 += 2;
            machine->unk28C = (machine->unk28C > 10) ? 10 : ((machine->unk28C < 1) ? 1 : machine->unk28C);
            machine->unk290 = (machine->unk290 > 10) ? 10 : ((machine->unk290 < 1) ? 1 : machine->unk290);
            machine->unk288 = (machine->unk288 > 10) ? 10 : ((machine->unk288 < 1) ? 1 : machine->unk288);
        } else {
            machine->unk28C -= 2;
            machine->unk288 += 1;
            machine->unk290 -= 2;
            machine->unk28C = (machine->unk28C > 8) ? 8 : ((machine->unk28C < 1) ? 1 : machine->unk28C);
            machine->unk290 = (machine->unk290 > 8) ? 8 : ((machine->unk290 < 1) ? 1 : machine->unk290);
            machine->unk288 = (machine->unk288 > 8) ? 8 : ((machine->unk288 < 1) ? 1 : machine->unk288);
        }
        machine->unk32C++;
        mdlA = (machine->unk328 == 1) ? sys->unk1E4[0] : sys->unk1E4[2];
        mdlB = (machine->unk328 == 1) ? sys->unk1E4[1] : sys->unk1E4[3];
        if (machine->unk32C < 540.0f) {
            Hu3DModelAttrReset(mdlA, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(mdlB, HU3D_ATTR_DISPOFF);
        } else {
            Hu3DModelAttrSet(mdlA, HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(mdlB, HU3D_ATTR_DISPOFF);
        }
        if (60.0f == machine->unk32C) {
            Hu3DModelAttrSet(mdlA, HU3D_MOTATTR_LOOP);
        } else if (540.0f == machine->unk32C) {
            Hu3DModelAttrReset(mdlA, HU3D_MOTATTR_LOOP);
            Hu3DMotionTimeSet(mdlB, 0.0f);
        } else if (600.0f == machine->unk32C) {
            Hu3DModelAttrSet(sys->unk1E4[0], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[1], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[2], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrSet(sys->unk1E4[3], HU3D_ATTR_DISPOFF);
            machine->unk32C = machine->unk328 = 0;
        }
        if (machine->unk330 == 1) {
            Hu3DModelCameraSet(mdlA, sdCameraBitTbl[machine->playerNo]);
            Hu3DModelCameraSet(mdlB, sdCameraBitTbl[machine->playerNo]);
        } else {
            Hu3DModelCameraSet(mdlA, 3);
            Hu3DModelCameraSet(mdlB, 3);
        }
        MathMtxRotGet(machine->mtx, &rot);
        Hu3DModelPosSetV(mdlA, &machine->pos);
        Hu3DModelRotSetV(mdlA, &rot);
        Hu3DModelPosSetV(mdlB, &machine->pos);
        Hu3DModelRotSetV(mdlB, &rot);
        MachineEffectUpdate(machine);
    }
    if (machine->bodyNo == 7) {
        if (sys->unk34 % 10 < 5) {
            MachineCameraBitSet(machine, sdCameraBitTbl[machine->playerNo]);
            machine->unk330 = 1;
        } else {
            MachineCameraBitSet(machine, 3);
            machine->unk330 = 0;
        }
    }
    switch (machine->mode) {
        case 0:
            break;
        case 1:
            MachineModeIdle(machine);
            break;
        case 2:
            MachineModeDamage(machine);
            break;
        case 3:
            MachineModeLaunch(machine);
            break;
        case 4:
            MachineModeDie(machine);
            break;
        case 5:
            MachineModeDie(machine);
            break;
    }
    if (machine->unk210 == 1) {
        machine->unk214++;
        if (machine->unk214 % 2 != 0) {
            MachineDispSet(machine, 1);
        } else {
            MachineDispSet(machine, 0);
        }
        if (machine->unk214 >= machine->unk218) {
            MachineDispSet(machine, 1);
            machine->unk210 = machine->unk214 = 0;
        }
    }
    MachineMotionUpdate(machine);
    SdMachineFxUpdate(machine);
    if (machine->unkE4 == 1) {
        HuAudFXVolSet(machine->unk3F0, 127);
    } else {
        HuAudFXVolSet(machine->unk3F0, 0);
    }
    if (MgSeqModeGet() > 5 && sys->unkB70 == 0) {
        MachineDispSet(machine, 1);
        MachineScaleSet(machine, (HuVecF){ 1.0f, 1.0f, 1.0f });
        for (i = 0; i < 4; i++) {
            if (machine->tireMdl[i] != -1) {
                Hu3DMotionSpeedSet(machine->tireMdl[i], 0.0f);
                Hu3DMotionShapeSpeedSet(machine->tireMdl[i], 0.0f);
            }
        }
    }
    return result;
}

/* 53 insns */
static void MachineParticleUpdate(SDMACHINE *machine)
{
    if (MgSeqModeGet() <= 5) {
        if (machine->bodyNo != 1 && machine->bodyNo != 9 && machine->bodyNo != 10) {
            if (sys->unk1C % 2 != 0) {
                MachineExhaustAdd(machine);
            }
        } else {
            MachineExhaustAdd(machine);
        }
        if (sys->unk1C % 2 != 0) {
            MachineTrackEffAdd(machine);
        }
    }
    MachineExhaustUpdate(machine);
    MachineTrackEffUpdate(machine);
}

/* 0x54 */ static GXColor particleColorTbl[11] = { { 255, 255, 255, 180 }, { 255, 192, 0, 180 }, { 255, 196, 220, 180 }, { 255, 255, 255, 180 }, { 0, 255, 76, 180 }, { 255, 168, 125, 180 }, { 255, 255, 255, 180 }, { 198, 0, 255, 180 }, { 190, 113, 53, 180 }, { 0, 255, 255, 180 }, { 64, 64, 150, 180 } };

/* 327 insns */
static void MachineExhaustUpdate(SDMACHINE *machine)
{
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 j;
    HU3DPARTICLE *particle;
    s32 type;
    s32 maxTime;
    HU3DPARTICLE *particleA = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLE *particleB = Hu3DData[sys->particleMdlId[10]].hookData;

    if (machine->bodyNo != 1 && machine->bodyNo != 9 && machine->bodyNo != 10) {
        type = 0;
        particle = particleA;
        maxTime = 60;
    } else {
        type = 1;
        particle = particleB;
        maxTime = 30;
    }
    for (i = 0; i < 30; i++) {
        data = &particle->data[machine->unk33C[0].unk0];
        if (data[i].time != 0) {
            for (j = 0; j < machine->unk208; j++) {
                data = &particle->data[machine->unk33C[j].unk0];
                data[i].pos.x += data[i].vel.x;
                data[i].pos.y += data[i].vel.y + data[i].accel.y;
                data[i].pos.z += data[i].vel.z;
                PSVECScale(&data[i].vel, &data[i].vel, 0.9f);
                if (machine->bodyNo == 3) {
                    data[i].accel.y *= 1.02f;
                    data[i].scale *= 1.04f;
                    if (data[i].scale > 180.0f) {
                        data[i].scale = 180.0f;
                    }
                    data[i].color.a *= 0.9f;
                } else {
                    data[i].accel.y *= 1.01f;
                    if (machine->bodyNo == 1 && j >= 2) {
                        data[i].scale *= 1.02f;
                    } else {
                        data[i].scale *= 1.01f;
                    }
                    if (data[i].scale > 128.0f) {
                        data[i].scale = 128.0f;
                    }
                    if (type == 0) {
                        data[i].color.a *= 0.95f;
                    } else {
                        if (data[i].parManId <= 8) {
                            data[i].color.r = 255 - (255 - particleColorTbl[machine->bodyNo].r) * data[i].parManId / 8;
                            data[i].color.g = 255 - (255 - particleColorTbl[machine->bodyNo].g) * data[i].parManId / 8;
                            data[i].color.b = 255 - (255 - particleColorTbl[machine->bodyNo].b) * data[i].parManId / 8;
                        }
                        data[i].color.a *= 0.9f;
                    }
                }
                if (++data[i].parManId >= maxTime) {
                    data[i].time = data[i].parManId = 0;
                    data[i].scale = 0.0f;
                }
            }
        }
    }
}

/* 684 insns */
static void MachineExhaustAdd(SDMACHINE *machine)
{
    HuVecF dir[4];
    HuVecF pos[4];
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 j;
    HU3DPARTICLE *particle;
    s32 type;
    s32 alpha;
    HU3DPARTICLE *particleA = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLE *particleB = Hu3DData[sys->particleMdlId[10]].hookData;
    GXColor color;

    if (machine->bodyNo != 1 && machine->bodyNo != 9 && machine->bodyNo != 10) {
        type = 0;
        particle = particleA;
    } else {
        type = 1;
        particle = particleB;
    }
    for (i = 0; i < machine->unk208; i++) {
        if (machine->bodyNo == 3) {
            dir[i] = (HuVecF){ machine->mtx[0][1], machine->mtx[1][1], machine->mtx[2][1] };
        } else {
            dir[i] = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
            PSVECScale(&dir[i], &dir[i], -1.0f);
        }
        pos[i] = machine->unk33C[i].unk4;
        PSMTXMultVec(machine->mtx, &pos[i], &pos[i]);
        PSVECAdd(&machine->pos, &pos[i], &pos[i]);
    }
    for (i = 0; i < 30; i++) {
        data = &particle->data[machine->unk33C[0].unk0];
        if (type == 0) {
            color = particleColorTbl[machine->bodyNo];
        } else {
            alpha = 0.2f * machine->unkE0;
            alpha = (alpha > 255) ? 255 : ((alpha < 0) ? 0 : alpha);
            color = (GXColor){ 255, 255, 255, alpha };
        }
        if (data[i].time == 0) {
            for (j = 0; j < machine->unk208; j++) {
                if (type == 0) {
                    data = &particle->data[machine->unk33C[j].unk0];
                } else {
                    data = &particleB->data[machine->unk33C[j].unk0];
                }
                if (machine->unk330 == 1) {
                    data[i].cameraBit = sdCameraBitTbl[machine->playerNo];
                } else {
                    data[i].cameraBit = 3;
                }
                data[i].time = 1;
                data[i].parManId = 0;
                data[i].vel = dir[j];
                if (machine->bodyNo == 3) {
                    data[i].pos = (HuVecF){ pos[j].x - 5.0f + rand8() % 10, pos[j].y - 5.0f + rand8() % 10, pos[j].z - 5.0f + rand8() % 10 };
                    PSVECScale(&data[i].vel, &data[i].vel, 10.0f);
                    data[i].scale = 30.0f + rand8() % 40;
                    data[i].accel = (HuVecF){ 0.0f, 5.0f, 0.0f };
                } else if (type == 0) {
                    data[i].pos = (HuVecF){ pos[j].x - 2.0f + rand8() % 5, pos[j].y - 2.0f + rand8() % 5, pos[j].z - 2.0f + rand8() % 5 };
                    data[i].scale = 30.0f + rand8() % 10;
                    data[i].accel = (HuVecF){ 0.0f, 3.0f, 0.0f };
                    PSVECScale(&data[i].vel, &data[i].vel, 5.0f);
                } else {
                    data[i].pos = (HuVecF){ pos[j].x, pos[j].y, pos[j].z };
                    if (machine->bodyNo == 1 && j >= 2) {
                        data[i].scale = 60.0f;
                    } else {
                        data[i].scale = 30.0f;
                    }
                    data[i].accel = (HuVecF){ 0.0f, 0.0f, 0.0f };
                    PSVECScale(&data[i].vel, &data[i].vel, 0.0f);
                }
                data[i].color = color;
            }
            break;
        }
    }
}

/* 327 insns */
static void MachineTrackEffUpdate(SDMACHINE *machine)
{
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 j;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 30; j++) {
            data = machine->unk340->unk20[i][j];
            if (data != 0 && data->time != 0) {
                data->pos.x += data->vel.x;
                data->pos.y += data->vel.y + data->accel.y;
                data->pos.z += data->vel.z;
                PSVECScale(&data->vel, &data->vel, 0.9f);
                if (data->parManId == 2) {
                    data->color.r *= 0.995f;
                    data->color.g *= 0.98f;
                    data->color.b *= 0.9f;
                    data->color.a *= 0.92f;
                    data->scale *= 1.01f;
                    data->accel.y *= 1.01f;
                    if (data->scale > 64.0f) {
                        data->scale = 64.0f;
                    }
                } else if (data->parManId == 4) {
                    if (data->time <= 30) {
                        data->scale *= 1.005f;
                    } else {
                        data->scale *= 0.95f;
                    }
                    data->accel.y *= 1.06f;
                    if (data->scale > 128.0f) {
                        data->scale = 128.0f;
                    }
                } else if (data->parManId == 6) {
                    data->color.a *= 0.9f;
                    if (data->time <= 30) {
                        data->scale *= 1.005f;
                    } else {
                        data->scale *= 0.95f;
                        if (data->pos.y < 0.0f) {
                            data->scale = 0.0f;
                            data->color.a = 0;
                        }
                    }
                    data->accel.y *= 1.06f;
                    if (data->scale > 128.0f) {
                        data->scale = 128.0f;
                    }
                } else {
                    data->color.a *= 0.95f;
                    if (data->parManId == 1) {
                        data->scale *= 1.02f;
                        data->accel.y *= 1.03f;
                    } else {
                        data->scale *= 1.04f;
                        data->accel.y *= 1.01f;
                    }
                    if (data->scale > 128.0f) {
                        data->scale = 128.0f;
                    }
                }
                if (++data->time >= 60) {
                    data->time = data->parManId = 0;
                    data->scale = 0.0f;
                    machine->unk340->unk20[i][j] = NULL;
                }
            }
        }
    }
}

/* 930 insns */
static void MachineTrackEffAdd(SDMACHINE *machine)
{
    HuVecF vel[2];
    HuVecF pos[2];
    float speed;
    float zRot;
    float accelY;
    HU3DPARTICLEDATA *data;
    s32 i;
    s32 k;
    s32 j;
    s32 gray;
    HU3DPARTICLE *particle0 = Hu3DData[sys->particleMdlId[3]].hookData;
    HU3DPARTICLE *particle1 = Hu3DData[sys->particleMdlId[2]].hookData;
    HU3DPARTICLE *particle2 = Hu3DData[sys->particleMdlId[9]].hookData;
    HU3DPARTICLE *particle3 = Hu3DData[sys->particleMdlId[11]].hookData;
    GXColor color;

    if (machine->unk368 & 2) {
        return;
    }
    speed = PSVECMag(&machine->unk160);
    if (speed < 1.0f) {
        return;
    }
    for (i = 0; i < 2; i++) {
        vel[i] = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
        PSVECScale(&vel[i], &vel[i], -1.0f);
        if (machine->unk1F0[i + 2] == 1 || machine->unk1F0[i + 2] == 4) {
            vel[i].y += 0.25f * speed;
        } else if (machine->unk1F0[i + 2] == 6) {
            vel[i].y += 0.25f * speed;
        }
        pos[i] = machine->unk1B0[i + 2];
        pos[i].y -= machine->unk364;
    }
    for (i = 0; i < 2; i++) {
        if (machine->unk1E0[i + 2] == 0 || machine->unk1F0[i + 2] == 5) {
            continue;
        }
        if (machine->unk1F0[i + 2] == 0 || machine->unk1F0[i + 2] == 3) {
            data = &particle0->data[machine->unk340->unk0[i][0]];
            if (machine->unk1F0[i + 2] == 0) {
                color = (GXColor){ 0xDA, 0xCB, 0x9E, 0x64 };
            } else {
                color = (GXColor){ 0xDA, 0xCB, 0x80, 0x64 };
            }
            zRot = 0.0f;
            accelY = 1.0f;
        } else if (machine->unk1F0[i + 2] == 4) {
            data = &particle1->data[machine->unk340->unk0[i][1]];
            gray = rand8() % 64 + 128;
            color = (GXColor){ gray, gray, gray, 0xFF };
            zRot = 0.017453292f * (4.0f * (rand8() % 90));
            accelY = -1.0f;
        } else if (machine->unk1F0[i + 2] == 6) {
            data = &particle3->data[machine->unk340->unk0[i][3]];
            zRot = 0.017453292f * (4.0f * (rand8() % 90));
            color = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
            zRot = 0.017453292f * (4.0f * (rand8() % 90));
            accelY = -1.0f;
        } else if (machine->unk1F0[i + 2] == 1 || machine->unk1F0[i + 2] == 2) {
            data = &particle2->data[machine->unk340->unk0[i][2]];
            zRot = 0.017453292f * (4.0f * (rand8() % 90));
            if (machine->unk1F0[i + 2] == 1) {
                color = (GXColor){ rand8() % 256, rand8() % 128 + 128, 0xFF, 0xFF };
            } else {
                color = (GXColor){ 0xFF, rand8() % 192 + 64, rand8() % 64, 0xFF };
                if (color.g < color.b) {
                    color.b = color.g;
                }
            }
            accelY = -1.0f;
        }
        for (k = 0; k < 30; k++) {
            if (data[k].time != 0) {
                continue;
            }
            for (j = 0; j < 30; j++) {
                if (machine->unk340->unk20[i][j] == 0) {
                    machine->unk340->unk20[i][j] = &data[k];
                    break;
                }
            }
            if (j == 30) {
                continue;
            }
            if (machine->unk330 == 1) {
                data[k].cameraBit = sdCameraBitTbl[machine->playerNo];
            } else {
                data[k].cameraBit = 3;
            }
            data[k].time = 1;
            data[k].parManId = machine->unk1F0[i + 2];
            data[k].vel = vel[i];
            data[k].accel = (HuVecF){ 0.0f, accelY, 0.0f };
            data[k].color = color;
            data[k].zRot = zRot;
            if (data[k].parManId == 6) {
                PSVECScale(&data[k].vel, &data[k].vel, 0.5f);
                data[k].pos = (HuVecF){ pos[i].x - 20.0f + rand8() % 40, pos[i].y + rand8() % 20, pos[i].z - 20.0f + rand8() % 40 };
            } else {
                PSVECScale(&data[k].vel, &data[k].vel, 2.5f);
                data[k].pos = (HuVecF){ pos[i].x - 20.0f + rand8() % 40, pos[i].y + rand8() % 20, pos[i].z - 20.0f + rand8() % 40 };
            }
            data[k].scale = 4.0f * speed + rand8() % 20;
            break;
        }
    }
}

/* 298 insns */
static void MachineEffectUpdate(SDMACHINE *machine)
{
    float scale;

    if (machine->unk32C >= 21.0f) {
        return;
    }
    if (machine->unk32C < 6.0f) {
        if (machine->unk328 == 1) {
            scale = 1.0f + 0.1f * machine->unk32C / 6.0f;
        } else {
            scale = 1.0f - 0.1f * machine->unk32C / 6.0f;
        }
    } else if (machine->unk32C < 9.0f) {
        scale = machine->unk32C - 6.0;
        if (machine->unk328 == 1) {
            scale = 1.1f - 0.1f * scale / 3.0f;
        } else {
            scale = 0.9f + 0.1f * scale / 3.0f;
        }
    } else if (machine->unk32C < 15.0f) {
        scale = machine->unk32C - 9.0f;
        if (machine->unk328 == 1) {
            scale = 1.0f + 0.1f * scale / 6.0f;
        } else {
            scale = 1.0f - 0.1f * scale / 6.0f;
        }
    } else if (machine->unk32C < 18.0f) {
        scale = machine->unk32C - 15.0f;
        if (machine->unk328 == 1) {
            scale = 1.1f - 0.1f * scale / 3.0f;
        } else {
            scale = 0.9f + 0.1f * scale / 3.0f;
        }
    } else {
        scale = 1.0f;
    }
    MachineScaleSet(machine, (HuVecF){ scale, scale, scale });
}

/* 369 insns */
static void MachineModeIdle(SDMACHINE *machine)
{
    Mtx rotMtx;
    HuVecF rotOfs;
    HuVecF base;
    HuVecF ofs;
    HuVecF side;
    HuVecF sideNeg;
    HuVecF front;
    float radius;
    float stkAbs;
    float stkX;
    float rot;
    float speed;
    s32 unused = 0;

    if (sys->unkB68 != 0) {
        return;
    }
    if (sys->gameType != 0 && machine->unk210 != 0) {
        return;
    }
    if (GwPlayerConf[machine->playerNo].type != 0) {
        SdComMain(machine);
    }
    SdGunUpdate(machine);
    if (machine->unk90 == 0) {
        if (HuPadBtn[machine->unk348] & PAD_BUTTON_A) {
            UpdateEnginePitch(machine, 1.0f);
        } else {
            UpdateEnginePitch(machine, -1.0f);
        }
    }
    speed = machine->unkE0 / 60.0f;
    stkX = HuPadStkX[machine->unk348];
    stkAbs = (stkX < 0.0f) ? -stkX : stkX;
    if (stkAbs > 60.0f) {
        stkAbs = 60.0f;
    }
    front = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
    side = (HuVecF){ machine->mtx[0][0], machine->mtx[1][0], machine->mtx[2][0] };
    PSVECScale(&side, &sideNeg, -1.0f);
    if (0.0f == stkX) {
        PSVECScale(&front, &rotOfs, speed);
        PSVECAdd(&machine->pos, &rotOfs, &machine->pos);
        rot = 0.0f;
    } else if ((machine->unk368 & 0xF) == 1 && 0.0f == speed && machine->tireNo != 5) {
        if (stkX > 0.0f) {
            rot = 0.005f * -(stkAbs * (9 - machine->unk288));
        } else {
            rot = 0.005f * (stkAbs * (9 - machine->unk288));
        }
        MTXRotDeg(rotMtx, 'y', rot);
        PSMTXConcat(machine->mtx, rotMtx, machine->mtx);
    } else {
        rot = 100.0f + 50.0f * machine->unk288;
        radius = rot + (2000.0f - rot) * (1.0f - stkAbs / 60.0f);
        PSVECScale(&side, &side, radius);
        PSVECScale(&sideNeg, &sideNeg, radius);
        rot = 3.141592653589793 * (2.0f * radius);
        rot = speed / rot;
        if (stkX > 0.0f) {
            rotOfs = side;
            base = sideNeg;
            rot *= -360.0f;
        } else {
            rotOfs = sideNeg;
            base = side;
            rot *= 360.0f;
        }
        MTXRotDeg(rotMtx, 'y', rot);
        PSMTXMultVec(rotMtx, &rotOfs, &ofs);
        PSVECAdd(&base, &machine->pos, &base);
        PSVECAdd(&base, &ofs, &machine->pos);
        PSMTXConcat(machine->mtx, rotMtx, machine->mtx);
    }
    MathMtxRotGet(machine->mtx, &machine->rot);
}

/* 316 insns */
static void MachineMotionUpdate(SDMACHINE *machine)
{
    float wheelSpeed;
    float speed;
    float stkX;
    float stkAbs;
    s32 i;
    HuVecF rot;

    if (sys->unkB68 != 0) {
        return;
    }
    speed = machine->unkE0 / 60.0f;
    if (machine->mode == 1) {
        stkX = HuPadStkX[machine->unk348];
        stkAbs = (stkX < 0.0f) ? -stkX : stkX;
        if (stkAbs > 60.0f) {
            stkAbs = 60.0f;
        }
    } else {
        stkX = 0.0f;
        UpdateEnginePitch(machine, -1.0f);
    }
    wheelSpeed = 3.141592653589793 * (2.0f * machine->unk360);
    wheelSpeed = speed / wheelSpeed;
    machine->unk180[0].x += 360.0f * wheelSpeed;
    wheelSpeed = 3.141592653589793 * (2.0f * machine->unk364);
    wheelSpeed = speed / wheelSpeed;
    machine->unk180[2].x += 360.0f * wheelSpeed;
    machine->unk180[0].y += 0.1f * ((0.25f * -stkX) - machine->unk180[0].y);
    machine->unk180[2].y = -machine->unk180[0].y;
    machine->unk180[1].x = machine->unk180[2].x = machine->unk180[3].x = machine->unk180[0].x;
    machine->unk180[1].z = machine->unk180[2].z = machine->unk180[3].z = machine->unk180[0].z;
    machine->unk180[1].y = machine->unk180[0].y;
    machine->unk180[3].y = machine->unk180[2].y;
    if (machine->bodyNo == 6 || machine->bodyNo == 4 || machine->bodyNo == 1 || machine->bodyNo == 7 || machine->bodyNo == 0) {
        Hu3DMotionSpeedSet(machine->bodyMdl, 0.1f * speed);
        Hu3DMotionShapeSpeedSet(machine->bodyMdl, 0.1f * speed);
    } else if (machine->bodyNo == 3) {
        Hu3DMotionShapeSpeedSet(machine->bodyMdl, 1.0f + 0.2f * speed);
    }
    for (i = 0; i < 4; i++) {
        if (machine->tireMdl[i] == -1) {
            continue;
        }
        if ((machine->unk368 & 0xF) == 2) {
            continue;
        }
        if ((machine->unk368 & 0xF) != 1) {
            MathMtxRotSet(&machine->unk180[i], &rot, NULL);
            machine->unk294[i]->mesh.base.rot.x = rot.x;
            machine->unk294[i]->mesh.base.rot.y = rot.y;
            machine->unk294[i]->mesh.base.rot.z = rot.z;
        } else if (speed > 0.0f) {
            Hu3DMotionShapeSpeedSet(machine->tireMdl[i], 0.4f * speed);
            Hu3DMotionSpeedSet(machine->tireMdl[i], 0.4f * speed);
        } else if (machine->tireNo != 5) {
            if (stkX > 0.0f) {
                wheelSpeed = 0.01f * (stkAbs * (9 - machine->unk288));
            } else {
                wheelSpeed = -0.01f * (stkAbs * (9 - machine->unk288));
            }
            if (i % 2) {
                wheelSpeed *= -1.0f;
            }
            Hu3DMotionShapeSpeedSet(machine->tireMdl[i], wheelSpeed);
            Hu3DMotionSpeedSet(machine->tireMdl[i], wheelSpeed);
        }
    }
}

/* 303 insns */
static void MachineModeDamage(SDMACHINE *machine)
{
    float ofs;
    HuVecF dir;

    dir = (HuVecF){ machine->unk21C[0][2], machine->unk21C[1][2], machine->unk21C[2][2] };
    dir.y = 0.0f;
    switch (machine->unk4) {
        case 0:
            PSMTXCopy(machine->mtx, machine->unk24C);
            machine->unk280 = 0.0f;
            machine->unk4++;
            break;
        case 1:
            machine->unk18++;
            ofs = 30.0f * MathLerp(5, machine->unk18 / 30.0f);
            ofs = 8.333333f;
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, ofs);
            PSVECAdd(&machine->pos, &dir, &machine->pos);
            machine->unkE8 = dir;
            ofs = 50.0f * MathLerp(5, machine->unk18 / 30.0f);
            machine->pos.y += ofs - machine->unk280;
            if (ofs > 0.0f) {
                machine->unk280 = ofs;
            }
            if (machine->unk18 >= 30.0f) {
                machine->unk280 = 0.0f;
                machine->unk4++;
                machine->unk18 = 0;
            }
            break;
        case 2:
            machine->unk18++;
            ofs = 8.333333f;
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, ofs);
            PSVECAdd(&machine->pos, &dir, &machine->pos);
            ofs = 5.0f * MathLerp(5, machine->unk18 / 15.0f);
            machine->pos.y += ofs - machine->unk280;
            if (ofs > 0.0f) {
                machine->unk280 = ofs;
            }
            if (machine->unk18 >= 15.0f) {
                machine->unk27C = 0.0f;
                machine->unk4++;
                machine->unk18 = 0;
            }
            break;
        case 3:
            machine->unk18++;
            ofs = 80.0f * MathLerp(1, machine->unk18 / 15.0f);
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, ofs - machine->unk27C);
            PSVECAdd(&machine->pos, &dir, &machine->pos);
            machine->unk27C = ofs;
            if (machine->unk18 >= 15.0f) {
                machine->unk214 = machine->unk4 = machine->unk18 = 0;
                if (machine->unkE4 > 0) {
                    machine->unk210 = 1;
                    machine->mode = 1;
                } else {
                    machine->mode = 4;
                }
            }
            break;
    }
}

/* 331 insns */
static void MachineFireCreate(SDMACHINE *machine)
{
    int rand8(void);
    HU3DPARTICLE *particle;
    HU3DPARTICLE *particle2;
    HU3DPARTICLEDATA *data;
    s32 i;
    SDMACHINEFIRE *fire = &machine->fire;

    particle = Hu3DData[fire->mdlId[0]].hookData;
    particle2 = Hu3DData[fire->mdlId[1]].hookData;
    data = particle->data;
    for (i = 0; i < 20; i++) {
        if (data[i].time == 0) {
            data[i].time = 1;
            data[i].parManId = 0;
            data[i].pos = (HuVecF){ (machine->pos.x - 25.0f) + (rand8() % 50), machine->pos.y, (machine->pos.z - 25.0f) + (rand8() % 50) };
            data[i].scale = 100.0f + (rand8() % 40);
            data[i].vel = (HuVecF){ 0.0f, 1.0f, 0.0f };
            data[i].color = (GXColor){ 255, 255, 255, 255 };
            break;
        }
    }
    data = particle2->data;
    for (i = 0; i < 20; i++) {
        if (data[i].time == 0) {
            data[i].time = 1;
            data[i].parManId = 0;
            data[i].pos = (HuVecF){ (machine->pos.x - 25.0f) + (rand8() % 50), machine->pos.y, (machine->pos.z - 25.0f) + (rand8() % 50) };
            data[i].scale = 100.0f + (rand8() % 40);
            data[i].vel = (HuVecF){ 0.0f, 1.0f, 0.0f };
            data[i].color = (GXColor){ 255, 255, 255, 255 };
            break;
        }
    }
}

/* 230 insns */
static void MachineFireHook(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s32 i;

    data = particle->data;
    for (i = 0; i < 20; i++) {
        if (data[i].time == 0) {
            continue;
        }
        data[i].pos.x += data[i].vel.x;
        data[i].pos.y += data[i].vel.y;
        data[i].pos.z += data[i].vel.z;
        PSVECScale(&data[i].vel, &data[i].vel, 1.01f);
        data[i].scale *= 1.04f;
        if (data[i].scale > 320.0f) {
            data[i].scale = 320.0f;
        }
        if (particle->dataCnt == 0) {
            if (data[i].parManId < 30) {
                data[i].color.r += 5;
                data[i].color.g += 5;
                data[i].color.b += 5;
            } else {
                data[i].color.r -= 15;
                data[i].color.g -= 15;
                data[i].color.b -= 15;
            }
        } else {
            data[i].color.r *= 0.995f;
            data[i].color.g *= 0.98f;
            data[i].color.b *= 0.9f;
            data[i].color.a *= 0.92f;
            if (data[i].color.a < 2) {
                data[i].scale = 0.0f;
            }
        }
        if (++data[i].parManId >= 40) {
            data[i].time = data[i].parManId = 0;
            data[i].scale = 0.0f;
        }
    }
    DCStoreRangeNoSync(data, 20 * sizeof(HU3DPARTICLEDATA));
}

/* 624 insns */
static void MachineModeLaunch(SDMACHINE *machine)
{
    float time;
    float stkX;
    float stkY;
    s32 i;
    s32 j;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    HuVecF side;
    HuVecF front;
    SDMACHINEFIRE *fire = &machine->fire;
    s32 animTbl[2] = { 3, 5 };
    s32 blendTbl[2] = { 2, 1 };

    if (GwPlayerConf[machine->playerNo].type != 0) {
        SdComMain(machine);
    }
    switch (machine->unk4) {
        case 0:
            for (i = 0; i < 2; i++) {
                fire->mdlId[i] = Hu3DParticleCreate(sys->unk16C[animTbl[i]], 20);
                particle = Hu3DData[fire->mdlId[i]].hookData;
                particle->dataCnt = i;
                data = particle->data;
                Hu3DParticleColSet(fire->mdlId[i], 255, 255, 255);
                Hu3DParticleBlendModeSet(fire->mdlId[i], blendTbl[i]);
                Hu3DParticleHookSet(fire->mdlId[i], MachineFireHook);
                Hu3DModelLayerSet(fire->mdlId[i], 5);
                Hu3DModelPosSet(fire->mdlId[i], 0.0f, 0.0f, 0.0f);
                Hu3DParticleAnimModeSet(fire->mdlId[i], 0);
                for (j = 0; j < particle->maxCnt; j++, data++) {
                    data->time = 0;
                    data->scale = 0.0f;
                    data->cameraBit = 3;
                }
            }
            fire->time = 0;
            fire->pos = machine->pos;
            machine->unk16C = 1;
            machine->unk18 = 0;
            machine->unk4++;
            break;
        case 1:
            time = 90.0f;
            if (machine->unk18 >= time / 2.0f) {
                machine->unk16C = 0;
                for (i = 0; i < 4; i++) {
                    machine->unk170[i] = 1.0f;
                }
                if (machine->unk90 == 0) {
                    SdVibrate(machine->playerNo, 1, 15);
                    HuAudFXPlayVolPan(machine->playerNo + 0x555, 127, (machine->playerNo * 32) + 48);
                    fire->pos = machine->pos;
                    machine->unk18 = 0;
                    machine->unk4++;
                    break;
                }
            }
            fire->pos.x = machine->pos.x;
            fire->pos.z = machine->pos.z;
            machine->unk18++;
            machine->pos = MathVecInterpolate(fire->pos, fire->pos, 1500.0f, machine->unk18 / time);
            machine->unk138 = machine->pos;
            machine->unk138.x = machine->pos.x = fire->pos.x;
            machine->unk138.z = machine->pos.z = fire->pos.z;
            break;
        case 2:
            time = 30.0f;
            if (machine->unk18 >= time / 2.0f && machine->unk90 == 0) {
                SdVibrate(machine->playerNo, 1, 5);
                HuAudFXPlayVolPan(machine->playerNo + 0x555, 95, (machine->playerNo * 32) + 48);
                fire->pos = machine->pos;
                machine->unk18 = 0;
                machine->unk4++;
                break;
            }
            fire->pos.x = machine->pos.x;
            fire->pos.z = machine->pos.z;
            machine->unk18++;
            machine->pos = MathVecInterpolate(fire->pos, fire->pos, 50.0f, machine->unk18 / time);
            machine->unk138 = machine->pos;
            machine->unk138.x = machine->pos.x = fire->pos.x;
            machine->unk138.z = machine->pos.z = fire->pos.z;
            break;
        case 3:
            time = 15.0f;
            if (machine->unk18 >= time / 2.0f && machine->unk90 == 0) {
                HuAudFXPlayVolPan(machine->playerNo + 0x555, 63, (machine->playerNo * 32) + 48);
                fire->pos = machine->pos;
                machine->unk18 = 0;
                machine->unk4++;
                break;
            }
            fire->pos.x = machine->pos.x;
            fire->pos.z = machine->pos.z;
            machine->unk18++;
            machine->pos = MathVecInterpolate(fire->pos, fire->pos, 25.0f, machine->unk18 / time);
            machine->unk138 = machine->pos;
            machine->unk138.x = machine->pos.x = fire->pos.x;
            machine->unk138.z = machine->pos.z = fire->pos.z;
            break;
        case 4:
            machine->unk214 = machine->unk4 = machine->unk18 = 0;
            Hu3DModelKill(fire->mdlId[0]);
            Hu3DModelKill(fire->mdlId[1]);
            if (machine->unkE4 > 0) {
                machine->mode = 1;
            } else {
                machine->mode = 4;
            }
            return;
    }
    stkX = HuPadStkX[machine->unk348] / 56.0f;
    stkY = HuPadStkY[machine->unk348] / 56.0f;
    if (sys->unkB68 != 0) {
        stkX = stkY = 0.0f;
    }
    side = (HuVecF){ machine->mtx[0][0], machine->mtx[1][0], machine->mtx[2][0] };
    front = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
    PSVECScale(&side, &side, -8.0f * stkX);
    PSVECScale(&front, &front, 8.0f * stkY);
    PSVECAdd(&machine->pos, &side, &machine->pos);
    PSVECAdd(&machine->pos, &front, &machine->pos);
    fire->time++;
    if ((fire->time % 2) == 0 && machine->unk4 == 1) {
        MachineFireCreate(machine);
    }
}

/* 86 insns */
static void MachineModeDie(SDMACHINE *machine)
{
    HuVecF side;
    HuVecF front;

    side = (HuVecF){ machine->unk21C[0][0], machine->unk21C[1][0], machine->unk21C[2][0] };
    front = (HuVecF){ machine->unk21C[0][2], machine->unk21C[1][2], machine->unk21C[2][2] };
    front.y = 0.0f;
    switch (machine->unk4) {
        case 0:
            UpdateEnginePitch(machine, -1.0f);
            if (machine->unkE0 < 0.001f) {
                machine->unk4++;
            }
            break;
        case 1:
            machine->unkE0 = 0.0f;
            break;
    }
}

/* 235 insns */
static void MachineColUpdate(void)
{
    SDMACHINE *machine1;
    SDMACHINE *machine2;
    float push;
    float dist;
    HuVecF dir;
    HuVecF tmp;

    machine1 = &sys->machine[0];
    machine2 = &sys->machine[1];
    PSVECSubtract(&machine1->pos, &machine2->pos, &dir);
    dir.y = 0.0f;
    dist = PSVECMag(&dir);
    if (dist > machine1->unk358 + machine2->unk358) {
        return;
    }
    if (machine1->pos.y - machine1->unk354 > machine2->pos.y + machine2->unk35C) {
        return;
    }
    if (machine2->pos.y - machine2->unk354 > machine1->pos.y + machine1->unk35C) {
        return;
    }
    if (machine1->unk334 == 0) {
        if (sys->unkB68 != 0 || sys->unkB6C != 0) {
            machine1->unk334 = machine2->unk334 = 1;
        }
        SdVibrate(machine1->playerNo, 0, 5);
        SdVibrate(machine2->playerNo, 0, 5);
        HuAudFXPlayVolPan(0x561, 127, 64);
    }
    PSVECSubtract(&machine1->unk138, &machine2->unk138, &tmp);
    push = PSVECMag(&tmp);
    PSVECSubtract(&machine1->pos, &machine2->pos, &tmp);
    push -= PSVECMag(&tmp);
    if (0.0f == PSVECMag(&dir)) {
        dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, 0.5f * ((machine1->unk358 + machine2->unk358) - dist));
    machine1->pos.x += dir.x;
    machine1->pos.z += dir.z;
    machine2->pos.x -= dir.x;
    machine2->pos.z -= dir.z;
    if (0.0f == PSVECMag(&dir)) {
        dir = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    PSVECNormalize(&dir, &dir);
    if (push < 5.0f) {
        push = 5.0f;
    }
    PSVECScale(&dir, &dir, 0.5f * push);
    machine1->unkE8 = (HuVecF){ dir.x, 0.0f, dir.z };
    machine2->unkE8 = (HuVecF){ -dir.x, 0.0f, -dir.z };
}

/* 322 insns */
static void MachineColSeparate(SDMACHINE *machine)
{
    float rotDiff;
    float friction;
    float velScale;
    float sideScale;
    float sideMin;
    float velY;
    s32 setF;
    HuVecF delta;
    Mtx rotMtx;

    setF = 0;
    if (sys->unkB68 == 0 && machine->mode != 4) {
        PSVECSubtract(&machine->pos, &machine->unk138, &delta);
        rotDiff = (180.0 * (atan2(machine->mtx[0][2], machine->mtx[2][2]) / 3.141592653589793))
            - (180.0 * (atan2(machine->unk108[0][2], machine->unk108[2][2]) / 3.141592653589793));
        if (rotDiff > 180.0f) {
            rotDiff -= 360.0f;
        }
        if (rotDiff < -180.0f) {
            rotDiff += 360.0f;
        }
        velY = delta.y;
        if (!(machine->unk368 & 0x10)) {
            if (!(machine->unk368 & 0x20)) {
                friction = 1.0f;
            } else {
                friction = 0.5f;
            }
            if (machine->unk28 == 1) {
                machine->unk104 = 60.0f * friction;
                velScale = 1.0 + 0.25f * friction;
                sideScale = 1.0f + 1.5f * friction;
                sideMin = 0.087f;
                setF = 1;
            } else if (machine->unk28 == 2) {
                machine->unk104 = 120.0f * friction;
                velScale = 1.0f + 0.5f * friction;
                sideScale = 1.0f + 4.0f * friction;
                sideMin = 0.087f;
                setF = 1;
            }
        }
        if (setF == 0) {
            machine->unk104 *= 0.95f;
            if (machine->unk104 < 10.0f) {
                machine->unk104 = 10.0f;
            }
            velScale = 1.0f;
            sideScale = 0.2f;
            sideMin = 0.19f;
        }
        PSVECScale(&machine->unkE8, &machine->unkE8, machine->unk104 - 1.0f);
        PSVECAdd(&machine->unkE8, &delta, &machine->unkE8);
        machine->unkF4 *= machine->unk104 - 1.0f;
        machine->unkF4 += rotDiff;
        if (!(PSVECMag(&machine->unkF8) == 0.0f)) {
            if (0.0f == PSVECMag(&machine->unkF8)) {
                machine->unkF8 = (HuVecF){ 1.0f, 1.0f, 1.0f };
            }
            PSVECNormalize(&machine->unkF8, &machine->unkF8);
            if (((machine->unkF8.y < 0.0f) ? -machine->unkF8.y : machine->unkF8.y) > sideMin) {
                PSVECScale(&machine->unkF8, &machine->unkF8, sideScale);
                machine->unkF8.y = 0.0f;
                PSVECAdd(&machine->unkE8, &machine->unkF8, &machine->unkE8);
            }
        }
        machine->unkF4 /= machine->unk104;
        PSVECScale(&machine->unkE8, &machine->unkE8, 1.0f / machine->unk104);
        machine->unkE8.y = 0.0f;
        PSVECScale(&machine->unkE8, &delta, velScale);
        delta.y = velY;
        PSVECAdd(&machine->unk138, &delta, &machine->pos);
        MTXRotDeg(rotMtx, 'y', machine->unkF4);
        PSMTXConcat(machine->unk108, rotMtx, machine->mtx);
        MathMtxRotGet(machine->mtx, &machine->rot);
    }
}

/* 205 insns */
s32 SdMachineDamage(SDMACHINE *machine, HuVecF pos, s32 damage)
{
    float angle;
    Mtx rotMtx;

    if (sys->unkB68 != 0) {
        return 0;
    }
    if (machine->mode >= 2) {
        return 0;
    }
    if (machine->enemy->mode >= 4) {
        return 0;
    }
    if (sys->gameType == 1) {
        if (SdFlagDispTimerGet(0) >= 3 || SdFlagDispTimerGet(1) >= 3) {
            return 0;
        }
    } else if (sys->gameType == 2) {
        if (SdRabbitDispTimerGet(0) >= 3 || SdRabbitDispTimerGet(1) >= 3) {
            return 0;
        }
    }
    HuAudFXPlayVolPan(machine->playerNo + 0x55D, 127, (machine->playerNo * 32) + 48);
    if (damage <= 2) {
        SdVibrate(machine->playerNo, 0, 15);
    } else if (damage <= 5) {
        SdVibrate(machine->playerNo, 1, 15);
    } else {
        SdVibrate(machine->playerNo, 2, 15);
    }
    pos.y = 0.0f;
    if (0.0f == PSVECMag(&pos)) {
        pos = (HuVecF){ 1.0f, 1.0f, 1.0f };
    }
    PSVECNormalize(&pos, &pos);
    angle = 180.0 * (atan2(pos.x, pos.z) / 3.141592653589793);
    MTXRotDeg(rotMtx, 'y', angle);
    PSMTXCopy(rotMtx, machine->unk21C);
    if (sys->gameType == 0) {
        if (machine->enemy->unkE4 > 0 && machine->unk338 == 0) {
            machine->unk338 = damage;
        }
        machine->unk218 = 240;
    } else {
        machine->unk218 = 60.0f + 15.0f * damage;
    }
    machine->mode = 2;
    if (machine->unk28 == 5 && sys->gameType != 0) {
        machine->mode = 3;
    }
    machine->unk4 = machine->unk18 = 0;
    return 1;
}

/* 51 insns */
static void PlayDamageSound(void)
{
    SDMACHINE *machine;
    s32 i;

    for (i = 0; i < 2; i++) {
        machine = &sys->machine[i];
        if (machine->unk338 > 0) {
            machine->unkE4 -= machine->unk338;
            machine->unk338 = 0;
            if (machine->unkE4 > 0) {
                SdPlayerSoundPlay(machine, 0);
            } else {
                machine->unkE4 = 0;
                HuAudFXPlayVolPan(machine->playerNo + 0x57B, 127, (machine->playerNo * 32) + 48);
                SdPlayerSoundPlay(machine, 1);
            }
        }
    }
}

/* 239 insns */
static void UpdateEnginePitch(SDMACHINE *machine, float pitch)
{
    float limit;
    float maxSpeed;
    float gear;
    HuVecF front;

    maxSpeed = 200.0f + 100.0f * machine->unk28C;
    front = (HuVecF){ machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
    limit = (front.y > 0.5f) ? 0.5f : ((front.y < -0.5f) ? -0.5f : front.y);
    if (maxSpeed < 0.0f) {
        limit = 1.0f + (-limit / 0.5f);
    }
    if (maxSpeed > 0.0f) {
        if (machine->unk39C & 1) {
            limit = 1.0f;
        } else {
            limit = 1.0f - ((0.5f * limit) / 0.5f);
        }
    }
    limit = (limit > 2.0f) ? 2.0f : ((limit < 0.5f) ? 0.5f : limit);
    if (machine->unk290 == 10) {
        gear = 0.25f;
    } else if (machine->unk290 == 9) {
        gear = 0.5f;
    } else {
        gear = 9 - machine->unk290;
    }
    machine->unkE0 += pitch * (maxSpeed / (30.0f * gear));
    machine->unkE0 = (machine->unkE0 > maxSpeed * limit) ? maxSpeed * limit : ((machine->unkE0 < 0.0f) ? 0.0f : machine->unkE0);
    HuAudFXPitchSet(machine->unk3DC, (8191.0f * machine->unkE0) / 1500.0f);
}

/* 71 insns */
static void MachineDispSet(SDMACHINE *machine, s32 dispF)
{
    s32 i;

    if (dispF == 0) {
        Hu3DModelAttrSet(machine->unk3B4, 1);
        Hu3DModelAttrSet(machine->bodyMdl, 1);
        Hu3DModelAttrSet(machine->gunMdl, 1);
        Hu3DModelAttrSet(machine->charMdl, 1);
        for (i = 0; i < 4; i++) {
            if (machine->tireMdl[i] != -1) {
                Hu3DModelAttrSet(machine->tireMdl[i], 1);
            }
        }
    } else {
        Hu3DModelAttrReset(machine->unk3B4, 1);
        Hu3DModelAttrReset(machine->bodyMdl, 1);
        Hu3DModelAttrReset(machine->gunMdl, 1);
        Hu3DModelAttrReset(machine->charMdl, 1);
        for (i = 0; i < 4; i++) {
            if (machine->tireMdl[i] != -1) {
                Hu3DModelAttrReset(machine->tireMdl[i], 1);
            }
        }
    }
}

/* 47 insns */
static void MachineScaleSet(SDMACHINE *machine, HuVecF scale)
{
    s32 i;

    Hu3DModelScaleSet(machine->bodyMdl, scale.x, scale.y, scale.z);
    Hu3DModelScaleSet(machine->gunMdl, scale.x, scale.y, scale.z);
    Hu3DModelScaleSet(machine->charMdl, scale.x, scale.y, scale.z);
    for (i = 0; i < 4; i++) {
        if (machine->tireMdl[i] != -1) {
            Hu3DModelScaleSet(machine->tireMdl[i], scale.x, scale.y, scale.z);
        }
    }
}

/* 42 insns */
static void MachineCameraBitSet(SDMACHINE *machine, s32 cameraBit)
{
    s32 i;

    Hu3DModelCameraSet(machine->bodyMdl, cameraBit);
    Hu3DModelCameraSet(machine->gunMdl, cameraBit);
    Hu3DModelCameraSet(machine->charMdl, cameraBit);
    for (i = 0; i < 4; i++) {
        if (machine->tireMdl[i] != -1) {
            Hu3DModelCameraSet(machine->tireMdl[i], cameraBit);
        }
    }
    Hu3DModelCameraSet(machine->unk3B4, cameraBit);
}

/* 174 insns */
static void MachineCameraInit(SDMACHINE *machine, s32 a1)
{
    SDCAMERA *camera = &sys->camera[machine->cameraNo];
    HuVecF eye;
    HuVecF target;
    HuVecF dirA;
    HuVecF dirB;
    float dot;

    if (camera->unk4 != 0) {
        camera->unk7C = 1;
        camera->unk80 = 1000.0f;
        MachineVelocityApply(machine, &eye, &target);
        if (a1 == 0) {
            CameraSetViewPos(machine->cameraNo, eye, (HuVecF) { 0.0f, 1.0f, 0.0f }, target);
        } else {
            VECSubtract(&Hu3DCamera[machine->cameraNo].target, &Hu3DCamera[machine->cameraNo].pos, &dirA);
            dirB = (HuVecF) { machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
            dirA.y = dirB.y = 0.0f;
            VECNormalize(&dirA, &dirA);
            VECNormalize(&dirB, &dirB);
            dot = VECDotProduct(&dirA, &dirB);
            dot = 0.25f + 0.75f * (1.0f - dot);
            SdCameraViewSet(machine->cameraNo, eye, (HuVecF) { 0.0f, 1.0f, 0.0f }, target, dot);
        }
    }
}

/* 80 insns */
static void MachineVelocityApply(SDMACHINE *machine, HuVecF *a1, HuVecF *a2)
{
    SDCAMERA *camera = &sys->camera[machine->cameraNo];
    HuVecF dir;

    dir = (HuVecF) { machine->mtx[0][2], machine->mtx[1][2], machine->mtx[2][2] };
    dir.y = 0.0f;
    VECNormalize(&dir, &dir);
    VECScale(&dir, &dir, -500.0f);
    dir.y += 350.0f;
    VECAdd(&machine->pos, &dir, a1);
    *a2 = machine->pos;
    a2->y += 300.0f;
}

/* 236 insns */
static void MachineViewUpdate(s32 cameraNo, s32 a1, HuVecF a2, HuVecF a3, HuVecF a4, float a5)
{
    SDCAMERA *camera = &sys->camera[cameraNo];
    Mtx m;
    HuVecF d1;
    HuVecF d2;
    HuVecF v;
    float ang1;
    float ang2;
    float angD;
    float dist1;
    float dist2;
    float distD;

    if (a5 >= 1.0f) {
        camera->eye = a3;
        camera->eyeCur = camera->eye;
        return;
    }
    camera->unk4 = 0;
    VECSubtract(&a2, &a4, &d1);
    d1.y = 0.0f;
    dist1 = VECMag(&d1);
    if (VECMag(&d1) == 0.0f) {
        d1 = (HuVecF) { 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&d1, &d1);
    ang1 = 180.0 * (atan2(d1.x, d1.z) / M_PI);
    VECSubtract(&a3, &a4, &d2);
    d2.y = 0.0f;
    dist2 = VECMag(&d2);
    if (VECMag(&d2) == 0.0f) {
        d2 = (HuVecF) { 1.0f, 1.0f, 1.0f };
    }
    VECNormalize(&d2, &d2);
    ang2 = 180.0 * (atan2(d2.x, d2.z) / M_PI);
    angD = ang2 - ang1;
    distD = dist2 - dist1;
    if (a1 == 1) {
        angD *= -1.0f;
    }
    a4.y = 0.0f;
    v = (HuVecF) { 0.0f, 0.0f, dist1 + distD * a5 };
    PSMTXRotRad(m, 'y', 0.017453292f * (ang1 + angD * a5));
    PSMTXMultVec(m, &v, &v);
    VECAdd(&v, &a4, &a4);
    ang1 = a3.y - a2.y;
    a4.y = a2.y + ang1 * a5;
    camera->eye = a4;
    camera->eyeCur = camera->eye;
}

/* 32 insns */
static void MachinePosSet(SDMACHINE *machine, HuVecF pos)
{
    machine->unk138 = pos;
    machine->pos = machine->unk138;
    machine->pos.y += machine->unk354;
    Hu3DModelPosSetV(machine->bodyMdl, &machine->pos);
}

/* 454 insns */
static void MachinePosInit(SDMACHINE *machine)
{
    if (sys->stageNo == 7 || sys->stageNo == 6) {
        MachinePosSet(machine, (HuVecF) { -1400.0f + 100.0f * (float) (machine->playerNo * 28), 300.0f, -1400.0f + 100.0f * (float) (machine->playerNo * 28) });
    } else if (sys->stageNo == 5) {
        MachinePosSet(machine, (HuVecF) { -1900.0f + 100.0f * (float) (machine->playerNo * 38), 300.0f, -1400.0f + 100.0f * (float) (machine->playerNo * 28) });
    } else if (sys->stageNo == 3) {
        if (machine->tireNo == 9) {
            MachinePosSet(machine, (HuVecF) { -1904.9999f + 100.0f * (38.1f * (float) machine->playerNo), 300.0f, -1900.0f + 100.0f * (float) (machine->playerNo * 38) });
        } else {
            MachinePosSet(machine, (HuVecF) { -1900.0f + 100.0f * (float) (machine->playerNo * 38), 300.0f, -1900.0f + 100.0f * (float) (machine->playerNo * 38) });
        }
    } else {
        MachinePosSet(machine, (HuVecF) { -1900.0f + 100.0f * (float) (machine->playerNo * 38), 300.0f, -1900.0f + 100.0f * (float) (machine->playerNo * 38) });
    }
    MachineRotSet(machine, (HuVecF) { 0.0f, 90.0f + 180.0f * (float) machine->playerNo, 0.0f });
}

/* 27 insns */
static void MachineRotSet(SDMACHINE *machine, HuVecF rot)
{
    MathMtxRotSet(&rot, &machine->rot, machine->mtx);
    Hu3DModelRotSetV(machine->bodyMdl, &machine->rot);
    PSMTXCopy(machine->mtx, machine->unk108);
    machine->unk144 = machine->rot;
}

/* 64 insns */
static void MachineRotApply(SDMACHINE *machine, HuVecF *rot)
{
    Mtx m;

    PSMTXRotRad(m, 'y', rot->y * 0.017453292f);
    PSMTXConcat(machine->mtx, m, machine->mtx);
    PSMTXRotRad(m, 'x', rot->x * 0.017453292f);
    PSMTXConcat(machine->mtx, m, machine->mtx);
    PSMTXRotRad(m, 'z', rot->z * 0.017453292f);
    PSMTXConcat(machine->mtx, m, machine->mtx);
    MathMtxRotGet(machine->mtx, &machine->rot);
    Hu3DModelRotSetV(machine->bodyMdl, &machine->rot);
    PSMTXCopy(machine->mtx, machine->unk108);
    machine->unk144 = machine->rot;
}

/* 24 insns */
static void MachineRotAngleSet(SDMACHINE *machine, HuVecF *rot)
{
    MathMtxRotSet(rot, &machine->rot, 0);
    Hu3DModelRotSetV(machine->bodyMdl, &machine->rot);
    machine->unk144 = machine->rot;
}

/* 67 insns */
static void MachineRotAngleApply(SDMACHINE *machine, HuVecF *rot)
{
    Mtx m;
    Mtx r;

    PSMTXIdentity(m);
    PSMTXRotRad(r, 'y', rot->y * 0.017453292f);
    PSMTXConcat(m, r, m);
    PSMTXRotRad(r, 'x', rot->x * 0.017453292f);
    PSMTXConcat(m, r, m);
    PSMTXRotRad(r, 'z', rot->z * 0.017453292f);
    PSMTXConcat(m, r, m);
    PSMTXConcat(m, machine->mtx, m);
    MathMtxRotGet(m, &machine->rot);
    Hu3DModelRotSetV(machine->bodyMdl, &machine->rot);
    machine->unk144 = machine->rot;
}

/* 0x80 */ static u32 p1MotFileTbl[12] = { DATANUM(DATA_sd00, 113), DATANUM(DATA_sd00, 115), DATANUM(DATA_sd00, 117), DATANUM(DATA_sd00, 119), DATANUM(DATA_sd00, 121), DATANUM(DATA_sd00, 123), DATANUM(DATA_sd00, 125), DATANUM(DATA_sd00, 127), DATANUM(DATA_sd00, 129), DATANUM(DATA_sd00, 131), DATANUM(DATA_sd00, 134), DATANUM(DATA_sd00, 137) };
/* 0xB0 */ static u32 p2MotFileTbl[12] = { DATANUM(DATA_sd00, 114), DATANUM(DATA_sd00, 116), DATANUM(DATA_sd00, 118), DATANUM(DATA_sd00, 120), DATANUM(DATA_sd00, 122), DATANUM(DATA_sd00, 124), DATANUM(DATA_sd00, 126), DATANUM(DATA_sd00, 128), DATANUM(DATA_sd00, 130), DATANUM(DATA_sd00, 132), DATANUM(DATA_sd00, 135), DATANUM(DATA_sd00, 138) };

/* 86 insns */
void SdCharInit(SDMACHINE *machine1, SDMACHINE *machine2)
{
    SDMACHINE *machine;
    void *data;
    s32 i;
    s32 dataNum;

    for (i = 0; i < 2; i++) {
        machine = (i == 0) ? machine1 : machine2;
        if (machine->charNo < 10) {
            dataNum = charDataDirTbl[machine->charNo][3];
        } else if (machine->charNo == 10) {
            dataNum = DATANUM(DATA_sd00, 133);
        } else {
            dataNum = DATANUM(DATA_sd00, 136);
        }
        machine->unk3B0 = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        data = (i == 0) ? HuDataSelHeapReadNum(p1MotFileTbl[machine->charNo], HU_MEMNUM_OVL, HEAP_MODEL)
                        : HuDataSelHeapReadNum(p2MotFileTbl[machine->charNo], HU_MEMNUM_OVL, HEAP_MODEL);
        machine->unk3B2 = Hu3DJointMotion(machine->unk3B0, data);
        Hu3DMotionSet(machine->unk3B0, machine->unk3B2);
        Hu3DMotionTimeSet(machine->unk3B0, 1.0f);
        Hu3DModelShadowSet(machine->unk3B0);
    }
}

/* 184 insns */
void SdCameraCreate(void)
{
    SDCAMERA *camera;
    s32 i;

    for (i = 0; i < 2; i++) {
        camera = &sys->camera[i];
        camera->unk0 = sdCameraBitTbl[i];
        camera->up = (HuVecF) { 0.0f, 1.0f, 0.0f };
        camera->eye = (HuVecF) { 0.0f, 0.0f, 2000.0f };
        camera->eyeCur = (HuVecF) { 0.0f, 0.0f, 500.0f };
        camera->unk44 = 0.1f;
        Hu3DCameraCreate(sdCameraBitTbl[i]);
        Hu3DCameraPosSetV(sdCameraBitTbl[i], &camera->eyeCur, &camera->up, &camera->targetCur);
    }
    Hu3DCameraViewportSet(sdCameraBitTbl[0], 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(sdCameraBitTbl[0], 0, 0, 640, 480);
    Hu3DCameraPerspectiveSet(sdCameraBitTbl[0], 60.0f, 20.0f, 35000.0f, 1.2f);
    Hu3DCameraViewportSet(sdCameraBitTbl[1], 640.0f, 0.0f, 32.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(sdCameraBitTbl[1], 640, 0, 32, 480);
    Hu3DCameraPerspectiveSet(sdCameraBitTbl[1], 60.0f, 20.0f, 35000.0f, 0.06000000238f);
}

/* 163 insns */
void SdCameraSplitSet(float t)
{
    float x = 0.0f;
    float w = t;

    if (w < 32.0f) {
        w = 32.0f;
        x = t - 32.0f;
    }
    Hu3DCameraViewportSet(sdCameraBitTbl[0], x, 0.0f, w, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(sdCameraBitTbl[0], 0, 0, (u32) t, 480);
    Hu3DCameraPerspectiveSet(sdCameraBitTbl[0], 60.0f, 20.0f, 35000.0f, 1.2f * (w / 640.0f));
    w = 640.0f - t;
    if (w < 32.0f) {
        w = 32.0f;
    }
    Hu3DCameraViewportSet(sdCameraBitTbl[1], t, 0.0f, w, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(sdCameraBitTbl[1], (u32) t, 0, (u32) w, 480);
    Hu3DCameraPerspectiveSet(sdCameraBitTbl[1], 60.0f, 20.0f, 35000.0f, 1.2f * (w / 640.0f));
    espPosSet(sys->spr.unkB2, 0.9f * t, 240.0f);
}

/* 0xE0 */ static float cameraYOfsTbl[10] = { 400.0f, 0.0f, 1000.0f, 800.0f, 500.0f, 1000.0f, 1000.0f, 1000.0f, 500.0f, 0.0f };

/* 352 insns */
void SdCameraUpdate(OMOBJ *obj)
{
    SDCAMERA *camera;
    HuVecF eyeD;
    HuVecF tgtD;
    HuVecF q;
    HuVecF pos;
    HuVecF dir;
    float f;
    float ang2;
    float ang1;
    s32 i;

    for (i = 0; i < 2; i++) {
        VECSubtract(&Hu3DCamera[i].target, &Hu3DCamera[i].pos, &dir);
        VECNormalize(&dir, &dir);
        ang1 = 180.0 * (atan2(dir.x, dir.z) / M_PI);
        camera = &sys->camera[i];
        VECSubtract(&camera->eye, &camera->eyeCur, &eyeD);
        VECSubtract(&camera->target, &camera->targetCur, &tgtD);
        VECScale(&eyeD, &eyeD, camera->unk44);
        VECScale(&tgtD, &tgtD, camera->unk44);
        VECAdd(&camera->eyeCur, &eyeD, &camera->eyeCur);
        VECAdd(&camera->targetCur, &tgtD, &camera->targetCur);
        pos = camera->eyeCur;
        f = SdStageEdgeDistRadiusGet(pos, 500.0f);
        if (f < 0.0f) {
            f = 0.0f;
        }
        if (f < 1500.0f) {
            f = (1500.0f - f) / 1500.0f;
            pos.y += cameraYOfsTbl[sys->stageNo] * MathLerp(0, f);
        }
        if (camera->unk7C != 0) {
            VECSubtract(&pos, &camera->targetCur, &q);
            VECNormalize(&q, &q);
            VECScale(&q, &q, camera->unk80);
            VECAdd(&q, &camera->targetCur, &pos);
        }
        Hu3DCameraPosSetV(camera->unk0, &pos, &camera->up, &camera->targetCur);
        VECSubtract(&Hu3DCamera[i].target, &Hu3DCamera[i].pos, &dir);
        VECNormalize(&dir, &dir);
        ang2 = 180.0 * (atan2(dir.x, dir.z) / M_PI);
        SdStageBackRotYSet(i, ang2, ang1);
        if (camera->unk84 > 0.0f) {
            f = (rand8() % 2) ? -1.0f : 1.0f;
            Hu3DCamera[i].pos.x += camera->unk84 * f;
            Hu3DCamera[i].target.x += camera->unk84 * f;
            f = (rand8() % 2) ? -1.0f : 1.0f;
            Hu3DCamera[i].pos.y += camera->unk84 * f;
            Hu3DCamera[i].target.y += camera->unk84 * f;
            f = (rand8() % 2) ? -1.0f : 1.0f;
            Hu3DCamera[i].pos.z += camera->unk84 * f;
            Hu3DCamera[i].target.z += camera->unk84 * f;
            camera->unk84 *= 0.9f;
        }
    }
    if (sys->stageNo == 2) {
        Hu3DCamera[2] = Hu3DCamera[0];
        Hu3DCamera[3] = Hu3DCamera[1];
    }
}

/* 93 insns */
HuVecF SdSinLerp(float t, HuVecF *from, HuVecF *to)
{
    HuVecF out;
    float w;

    if (1.0f < t) {
        t = 1.0f;
    }
    w = sin(M_PI * (90.0f * t) / 180.0) * sin(M_PI * (90.0f * t) / 180.0);
    out.x = from->x + w * (to->x - from->x);
    out.y = from->y + w * (to->y - from->y);
    out.z = from->z + w * (to->z - from->z);
    return out;
}

/* 53 insns */
static void CameraSetViewPos(s32 cameraNo, HuVecF eye, HuVecF up, HuVecF target)
{
    SDCAMERA *camera = &sys->camera[cameraNo];

    camera->up = up;
    camera->eye = camera->eyeCur = camera->eyeStart = eye;
    camera->target = camera->targetCur = camera->targetStart = target;
}

/* 30 insns */
void SdCameraViewSet(s32 cameraNo, HuVecF eye, HuVecF up, HuVecF target, float rate)
{
    SDCAMERA *camera = &sys->camera[cameraNo];

    camera->up = up;
    camera->eye = eye;
    camera->target = target;
    camera->unk44 = rate;
}

/* 29 insns */
void SdCameraViewBeginSet(s32 cameraNo, HuVecF eye, HuVecF up, HuVecF target)
{
    SDCAMERA *camera = &sys->camera[cameraNo];

    camera->up = up;
    camera->eyeStart = eye;
    camera->targetStart = target;
}

/* 33 insns */
void SdCameraViewEndSet(s32 cameraNo, HuVecF eye, HuVecF up, HuVecF target)
{
    SDCAMERA *camera = &sys->camera[cameraNo];

    camera->up = up;
    camera->eyeEnd = eye;
    camera->targetEnd = target;
    camera->time = 0.0f;
}

/* 12 insns */
void SdCameraViewSpeedSet(s32 cameraNo, float time)
{
    SDCAMERA *camera = &sys->camera[cameraNo];

    camera->time = time;
}

/* 219 insns */
s32 SdCameraViewUpdate(s32 cameraNo, float frames, HuVecF *up)
{
    SDCAMERA *camera = &sys->camera[cameraNo];
    HuVecF eye;
    HuVecF target;

    camera->time += 1.0f / frames;
    eye = SdSinLerp(camera->time, &camera->eyeStart, &camera->eyeEnd);
    target = SdSinLerp(camera->time, &camera->targetStart, &camera->targetEnd);
    camera->up = *up;
    camera->eye = camera->eyeCur = eye;
    camera->target = camera->targetCur = target;
    if (1.0f <= camera->time) {
        return 1;
    }
    return 0;
}

/* 108 insns */
void SdVibrate(s32 playerNo, s32 a1, s32 a2)
{
    s32 flag = 0;

    if (GwPlayerConf[playerNo].type == 0) {
        if (sys->vibrate[playerNo].unk0 < a1) {
            flag = 1;
        } else if (sys->vibrate[playerNo].unk0 == a1 && sys->vibrate[playerNo].unk4 < a2) {
            flag = 1;
        }
        if (flag != 0) {
            if (a1 == 0) {
                omVibrate(sys->machine[playerNo].playerNo, a2, 6, 6);
            } else if (a1 == 1) {
                omVibrate(sys->machine[playerNo].playerNo, a2, 4, 2);
            } else if (a1 == 2) {
                omVibrate(sys->machine[playerNo].playerNo, a2, 12, 0);
            }
            sys->vibrate[playerNo].unk0 = a1;
            sys->vibrate[playerNo].unk4 = a2;
        }
    }
}

/* 34 insns */
void SdVibrateUpdate(void)
{
    s32 i;

    for (i = 0; i < 2; i++) {
        if (--sys->vibrate[i].unk4 < 0) {
            sys->vibrate[i].unk4 = 0;
            sys->vibrate[i].unk0 = -1;
        }
    }
}

