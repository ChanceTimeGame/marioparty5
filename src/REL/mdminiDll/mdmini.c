/*
 * mdminiDll -- the Minigame Mode hub (mode menu slot 2). Players, characters and COM levels,
 * then a submode from lbl_1_data_148: mgfree, mgmatch, w20 (circuit), decathlon, mgwars,
 * mgtour; or back to mdseldll. Decompiled 2026-09-28 from the reference assembly with the
 * mdparty/mdsel twins; functions keep their fn_1_XXXX names, twins are noted per function.
 * See src/REL/mdminidll/NOTES.md.
 */

#include "REL/mdminiDll.h"

/* mdparty.c/mdsel.c precedent: the particle helpers come from an #included .c, included right
 * after the overlay header and BEFORE game/frand.h: retail calls frandmod unprototyped there
 * (signed int result: xoris 0x8000 in ParticleDotCreate). Its HU3DPARMANPARAM statics are
 * .data 0x0-0x13F; its six static functions are emitted last in .text (unreferenced in mdmini). */
#include "REL/mdminiDll/effect.c"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/saveload.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "math.h"
#include "messnum/mgmode_sys.h"
#include "messnum/syshelp.h"

extern void MBPartySaveInit(int boardNo); /* mdparty.c:211 precedent */
#include "game/mgdata.h" /* fn_1_16978 sdHealthLoss/mgMatch*, fn_1_16358 mgDataTbl */


/* mdparty.c MDPARTY_LERP_DATA (fn_1_991C / lbl_1_data_724) */
typedef struct MdMiniLerpData_s {
    HuVecF hvrA;
    HuVecF centerA;
    HuVecF hvrB;
    HuVecF centerB;
    int type;
    float step;
} MDMINI_LERP_DATA;

/* fn_1_E44C lbl_1_bss_1A8[6]: one record per submode star (CAP_MODE_00..05), 0x34 bytes.
 * Layout measured from fn_1_E44C (twin: mdsel STAR_MODE_WORK, which has 3 time/t pairs, this has 4). */
typedef struct MdMiniE44CRec_s {
    s16 mode; //0x00
    s16 wait; //0x02 frames before the star enters (lbl_1_data_8CC)
    float radius; //0x04
    float angle; //0x08
    float startAngle; //0x0C
    float endAngle; //0x10
    float oscTime[4]; //0x14 MdMathOscillate inputs ([2] is only cleared)
    float oscT[4]; //0x24 MdMathOscillate outputs
} MDMINI_E44C_REC;

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 90.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 0.0f; /* 0x14 */
/* 0x18 lbl_1_rodata_18 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_20 = 1800.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 60.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 45.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 1300.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 360.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 1.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 64.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 320.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 1000.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 288.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 240.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 30.0f; /* 0x4C */
static const float lbl_1_rodata_50 = -65.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 300.0f; /* 0x54 */
static const float lbl_1_rodata_58 = -1.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 32.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 15.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 0.5f; /* 0x64 */
static const float lbl_1_rodata_68 = 372.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 340.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 16.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 8.0f; /* 0x74 */
static const double lbl_1_rodata_78 = 1.0; /* 0x78 */
static const float lbl_1_rodata_80 = 4.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 176.8f; /* 0x84 */
static const float lbl_1_rodata_88 = -580.0f; /* 0x88 */
static const float lbl_1_rodata_8C = -64.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 192.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 640.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 44.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 46.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 3.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 180.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = -200.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = 96.0f; /* 0xAC */
static const float lbl_1_rodata_B0 = 80.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = -460.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 120.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = -600.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 460.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 0.7f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 24.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 1.5f; /* 0xCC */
static const float lbl_1_rodata_D0 = 12.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = -2.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 2.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 72.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = -28.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 176.64f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 4000.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 168.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 2500.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 200.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 20.0f; /* 0xF8 */
static const float lbl_1_rodata_FC = 270.0f; /* 0xFC */
static const float lbl_1_rodata_100 = -90.0f; /* 0x100 */
static const double lbl_1_rodata_108 = 3.141592653589793; /* 0x108 */
static const double lbl_1_rodata_110 = 180.0; /* 0x110 */
static const float lbl_1_rodata_118 = 0.1f; /* 0x118 */
static const float lbl_1_rodata_11C = -2000.0f; /* 0x11C */
static const float lbl_1_rodata_120 = -50.0f; /* 0x120 */
static const float lbl_1_rodata_124 = 500.0f; /* 0x124 */
static const float lbl_1_rodata_128 = 145.0f; /* 0x128 */
static const float lbl_1_rodata_12C = 400.0f; /* 0x12C */
static const float lbl_1_rodata_130 = -525.0f; /* 0x130 */
static const float lbl_1_rodata_134 = 365.0f; /* 0x134 */
static const float lbl_1_rodata_138 = 0.8f; /* 0x138 */
static const float lbl_1_rodata_13C = 525.0f; /* 0x13C */
static const float lbl_1_rodata_140 = -15.0f; /* 0x140 */
static const float lbl_1_rodata_144 = -160.0f; /* 0x144 */
static const float lbl_1_rodata_148 = -380.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 380.0f; /* 0x14C */
/* 0x150 lbl_1_rodata_150 (0x10): 0x40800000 0x40000000 0x3FC00000 0x40400000 -- an aggregate initialiser, write it as a local */
/* 0x160 lbl_1_rodata_160 (0x10): 0x40800000 0x40000000 0x3FC00000 0x40400000 -- an aggregate initialiser, write it as a local */
/* 0x170 lbl_1_rodata_170 (0x10): 0x40800000 0x40000000 0x3FC00000 0x40400000 -- an aggregate initialiser, write it as a local */
/* 0x180 lbl_1_rodata_180 (0x10): 0x41000000 0x40800000 0x40400000 0x40C00000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_190 = -300.0f; /* 0x190 */
static const float lbl_1_rodata_194 = 50.0f; /* 0x194 */
static const float lbl_1_rodata_198 = -100.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 100.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 540.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = -540.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 0.2f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 250.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = -1000.0f; /* 0x1B0 */
static const float lbl_1_rodata_1B4 = -75.0f; /* 0x1B4 */
static const float lbl_1_rodata_1B8 = 75.0f; /* 0x1B8 */
static const float lbl_1_rodata_1BC = 160.0f; /* 0x1BC */
static const float lbl_1_rodata_1C0 = -10.0f; /* 0x1C0 */
static const float lbl_1_rodata_1C4 = 175.0f; /* 0x1C4 */
static const float lbl_1_rodata_1C8 = -175.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = 10.0f; /* 0x1CC */
/* 0x1D0 lbl_1_rodata_1D0 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x1D1 gap_03_000001D1_rodata: 0x00, 0x00, 0x00 */
/* 0x1D4 lbl_1_rodata_1D4 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x1D5 lbl_1_rodata_1D5 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x1D8 lbl_1_rodata_1D8 (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x1D9 lbl_1_rodata_1D9 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1DC = 105.0f; /* 0x1DC */
static const float lbl_1_rodata_1E0 = 18.0f; /* 0x1E0 */
/* 0x1E4 lbl_1_rodata_1E4 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x1E5 gap_03_000001E5_rodata: 0x0000 */
/* 0x1E7 lbl_1_rodata_1E7 (0x5): 0x00, 0x00, 0x00, 0x00, 0x00 -- an aggregate initialiser, write it as a local */
/* 0x1EC lbl_1_rodata_1EC (0x18): 0x01F6 0x01F8 0x01FA 0x01FB 0x01FE 0x01FF 0x0200 0x0201 0x0202 0x0233 0xFFFF 0x0000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_204 = 0.11111111f; /* 0x204 */
static const float lbl_1_rodata_208 = 5.0f; /* 0x208 */
static const float lbl_1_rodata_20C = 0.05f; /* 0x20C */
static const float lbl_1_rodata_210 = 0.01f; /* 0x210 */
static const float lbl_1_rodata_214 = -32.0f; /* 0x214 */
static const float lbl_1_rodata_218 = 0.4f; /* 0x218 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x3EC */ SYS sysWork;
/* 0x3E8 */ SYS *sys;
/* 0x3E4 */ SYS *sysP;
/* 0x3CC */ HuVecF lbl_1_bss_3CC[2];
/* 0x3B4 */ HuVecF lbl_1_bss_3B4[2];
/* 0x3B0 */ float lbl_1_bss_3B0;
/* 0x3AC */ float lbl_1_bss_3AC;
/* 0x3A8 */ float lbl_1_bss_3A8;
/* 0x3A4 */ float lbl_1_bss_3A4;
/* 0x3A0 */ float lbl_1_bss_3A0;
/* 0x39C */ float lbl_1_bss_39C;
/* 0x36C */ HuVecF lbl_1_bss_36C[4];
/* 0x368 */ s32 lbl_1_bss_368;
/* 0x364 */ float lbl_1_bss_364;
/* 0x360 */ float lbl_1_bss_360;
/* 0x35C */ float lbl_1_bss_35C;
/* 0x350 */ HuVecF lbl_1_bss_350;
/* 0x320 */ HuVecF lbl_1_bss_320[4];
/* 0x318 */ s8 lbl_1_bss_318[4][2];
/* 0x314 */ float lbl_1_bss_314;
/* 0x310 */ float lbl_1_bss_310;
/* 0x2E0 */ HuVecF lbl_1_bss_2E0[4];
/* 0x1A8 */ MDMINI_E44C_REC lbl_1_bss_1A8[6];
/* 0x19C */ HuVecF lbl_1_bss_19C;
/* 0x184 */ HuVecF lbl_1_bss_184[2];
/* 0x16C */ HuVecF lbl_1_bss_16C[2];
/* 0x154 */ HuVecF lbl_1_bss_154[2];
/* 0x13C */ HuVecF lbl_1_bss_13C[2];
/* 0x134 */ float lbl_1_bss_134[2];
/* 0x12C */ float lbl_1_bss_12C[2];
/* 0x124 */ float lbl_1_bss_124[2];
/* 0x120 */ s8 lbl_1_bss_120[2]; /* fn_1_10B0C: dtk sized it 1, the code indexes [0] and [1]; 0x121-0x123 are padding in retail */
/* 0x11C */ s32 lbl_1_bss_11C;
/* 0x118 */ s32 lbl_1_bss_118;
/* 0xF8 */ MDMINI_EFFECT *lbl_1_bss_F8[4][2];
/* 0x98 */ HuVecF lbl_1_bss_98[4][2];
/* 0x38 */ HuVecF lbl_1_bss_38[4][2];
/* 0x34 */ s32 lbl_1_bss_34;
/* 0x30 */ float lbl_1_bss_30;
/* 0x2C */ float lbl_1_bss_2C;
/* 0x28 */ s32 lbl_1_bss_28; /* fn_1_17008 streamNo (mdparty AudExec static) */
/* 0x24 */ s32 lbl_1_bss_24; /* fn_1_17008 seNo */
/* 0x1 gap_05_00000001_bss (0x3): alignment gap */
/* 0x0 */ extern s8 lbl_1_bss_0; /* defined after the last function (declaration order = .bss order) */

/* --- functions (reference order), .data placed before its first user --- */
/* 0x140 */ char *lbl_1_data_144 = "26"; /* 0x140 "26" + 0x144 pointer (mdparty.c:214) */
/* 0x148 */ OMOVL lbl_1_data_148[6] = { /* submode overlays, indexed by sys->unk3D */
    DLL_mgfreedll,
    DLL_mgmatchdll,
    DLL_w20dll,
    DLL_decathlondll,
    DLL_mgwarsdll,
    DLL_mgtourdll
};
/* 0x160 */ int lbl_1_data_160[6] = { DATA_mgfree, DATA_mgmatch, DATA_w20, DATA_decathlon, DATA_mgwars, DATA_mgtour };
/* 0x178 */ HuVecF lbl_1_data_178[10][2] = { /* mdparty CharPos */
    { { -250.0f, 0.0f, 0.0f }, { -250.0f, 0.0f, 0.0f } },
    { { -125.0f, 0.0f, 0.0f }, { -125.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 125.0f, 0.0f, 0.0f }, { 139.0f, 17.5f, -500.0f } },
    { { 275.0f, 9.0f, -300.0f }, { 266.0f, 2.0f, -200.0f } },
    { { -250.0f, -250.0f, 0.0f }, { -250.0f, -250.0f, 0.0f } },
    { { -125.0f, -250.0f, 0.0f }, { -140.5f, -270.0f, -400.0f } },
    { { 0.0f, -270.0f, -300.0f }, { -8.5f, -290.5f, -629.0f } },
    { { 125.0f, -250.0f, -1800.0f }, { 122.0f, -261.0f, -1800.0f } },
    { { 250.0f, -250.0f, -1000.0f }, { 245.5f, -254.0f, -1000.0f } }
};
/* 0x268 */ HuVecF lbl_1_data_268[10][2] = { /* mdparty CharRot */
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 10.0f, -2.0f, 0.0f }, { 10.0f, -4.0f, 0.0f } },
    { { 0.0f, -3.0f, 0.0f }, { 0.0f, -6.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, -4.0f, 0.0f }, { 0.0f, -2.0f, 0.0f } }
};
/* 0x358 */ MD_FUNC MdFlowTbl[MDMINI_FLOW_MAX] = { /* reference: lbl_1_data_358 (map.mdmini.txt) */
    fn_1_23D8,
    fn_1_27F8,
    fn_1_35A0,
    fn_1_5558,
    fn_1_6FB8,
    fn_1_7638,
    fn_1_81E0
};
/* 0x374 */ MD_PROC MdProcTbl[MDMINI_PROC_MAX] = { /* reference: lbl_1_data_374 (map.mdmini.txt) */
    fn_1_9714,
    fn_1_991C,
    fn_1_9AC8,
    fn_1_AF34,
    fn_1_B668,
    fn_1_C8B4,
    fn_1_E44C,
    fn_1_F6C4,
    fn_1_FC94,
    fn_1_10264,
    fn_1_106D4,
    fn_1_10B0C,
    fn_1_113D8,
    fn_1_11658,
    fn_1_149A4
};

/* 474 insns */
/* twin: mdparty ObjectSetup (no closeDir table: closes board/w20; subGameNo=0, FLAG_INST_MGMODE, mgPauseExitF) */
void ObjectSetup(void)
{
    sys = &sysWork;
    sysP = sys;
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowTime = 0;
    sys->flowMode = MDMINI_FLOW_INIT;
    sys->ovlCallMode = MD_OVLCALL_GOTO;
    sys->nextDll = DLL_selmenuDLL;
    sys->exitF = FALSE;
    sys->skipWipeF = FALSE;
    GWSubGameNoSet(0);
    _SetFlag(FLAG_INST_MGMODE);
    mgPauseExitF = FALSE;
    HuDataDirClose(DATA_board);
    HuARDirFree(DATA_board);
    HuDataDirClose(DATA_w20);
    HuARDirFree(DATA_w20);
    sys->objman = omInitObjMan(512, 8192);
    sys->ovlHis = omOvlHisGet(0);
    sys->evtNo = sys->ovlHis->evtno;
    omGameSysInit(sys->objman);
    sys->obj[MDMINI_OBJ_DEBUGFONT] = omAddObj(sys->objman, 100, 0, 0, MdObjDebugFontCreate);
    sys->obj[MDMINI_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDMINI_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDMINI_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDMINI_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDMINI_OBJ_PAD] = omAddObj(sys->objman, 101, 0, 0, MdObjPadMain);
    sys->obj[MDMINI_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDMINI_OBJ_PAD]->data) {
        OSReport("sys->obj[MDMINI_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDMINI_OBJ_PAD]->data;
    sys->obj[MDMINI_OBJ_CAMERA] = omAddObj(sys->objman, 102, 0, 0, MdObjCameraCreate);
    sys->obj[MDMINI_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDMINI_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDMINI_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDMINI_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDMINI_OBJ_LIGHT] = omAddObj(sys->objman, 103, 0, 0, MdObjLightCreate);
    sys->obj[MDMINI_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDMINI_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDMINI_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDMINI_OBJ_LIGHT]->data;
    sys->light->createF = FALSE;
    sys->light->debugFont = sys->debugFont;
    sys->sprite = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSPRITE_WORK), HU_MEMNUM_OVL);
    if(!sys->sprite) {
        OSReport("sys->sprite = NULL...\n");
    }
    sys->model = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMODEL_WORK), HU_MEMNUM_OVL);
    if(!sys->model) {
        OSReport("sys->model = NULL...\n");
    }
    sys->texbuf = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDTEXBUF_WORK), HU_MEMNUM_OVL);
    if(!sys->texbuf) {
        OSReport("sys->texbuf = NULL...\n");
    }
    sys->ring = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDRING_WORK), HU_MEMNUM_OVL);
    if(!sys->ring) {
        OSReport("sys->ring = NULL...\n");
    }
    sys->star = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMINI_STAR), HU_MEMNUM_OVL);
    if(!sys->star) {
        OSReport("sys->star = NULL...\n");
    }
    sys->mess = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMESS_WORK), HU_MEMNUM_OVL);
    if(!sys->mess) {
        OSReport("sys->mess = NULL...\n");
    }
    MdMessCreate(sys->mess);
    MdMathStdCurveInit();
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(FALSE);
    while(1) {
        if(sys->debugFont->createF == TRUE && sys->camera->createF == TRUE && sys->light->createF == TRUE) {
            break;
        }
        HuPrcVSleep();
    }
    sys->mainProc = HuPrcChildCreate(MdMain, 105, 12288, 0, sys->objman);
}

/* twin: mdsel MdMain */
void MdMain(void)
{
    fn_1_20A0();
    while(!omSysExitReq && !sys->exitF) {
        MdFlowTbl[sys->flowMode]();
        if(++sys->flowTime > 36000) {
            sys->flowTime = 0;
        }
        HuPrcVSleep();
    }
    fn_1_22C8();
}

/* 224 insns */
/* twin: mdparty LoadProc. loadState here: 0 idle, 1 mdsel dir, 2 characters + sys->loadDir,
 * 3 board -> ARAM + characters + w20 dir, 4 done (mdmini's states are not mdparty's MD_LOAD_STATE_*). */
void fn_1_8CC(void)
{
    OSTick tick;
    int i;
    s16 charNo;

    while(1) {
        switch(sys->loadState) {
            case 0:
                break;

            case 1:
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(DATA_mdsel);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadState = 4;
                break;

            case 2:
                CharDataClose(-1);
                for(i=0; i<GW_PLAYER_MAX; i++) {
                    charNo = GwPlayerConf[i].charNo;
                    CharMotionInitAsync(charNo);
                }
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(sys->loadDir);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadState = 4;
                break;

            case 3:
                CharDataClose(-1);
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(DATA_board);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                HuAR_MRAMtoARAM(DATA_board);
                while(HuARDMACheck());
                HuDataDirClose(DATA_board);
                for(i=0; i<GW_PLAYER_MAX; i++) {
                    charNo = GwPlayerConf[i].charNo;
                    CharMotionInitAsync(charNo);
                }
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(DATA_w20);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadState = 4;
                break;

            case 4:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}
/* 0x500 */ float lbl_1_data_500[5] = { 0.0f, 16.0f, 64.0f, 32.0f, -65.0f };
/* 750 insns */
/* twin: MdPartyStarUpdate (mdparty StarUpdate). lbl_1_data_500 = curveData; lbl_1_bss_3CC = pos2D,
 * lbl_1_bss_3B4 = pos3D, 3B0 lerpTime, 3AC lerpOfsTime, 3A8 curveTime, 3A4 lerpT, 3A0 lerpOfsT, 39C curveT.
 * Differs from the twin only in the MOVE_LEFT/CENTER start target (64, 300, 1000 instead of 54, 312, 1200). */
void fn_1_C4C(void)
{
    MDMINI_STAR *star; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *posP; //r29
    MDCAMERA_WORK *camera; //r28
    int i; //r27
    HuVecF *rotP; //r26
    MDMESS_WORK *mess; //r25
    HuVecF *scaleP; //r24

    model = sys->model;
    camera = sys->camera;
    mess = sys->mess;
    star = sys->star;
    posP = model->posP[MDMODEL_STAR];
    rotP = model->rotP[MDMODEL_STAR];
    scaleP = model->scaleP[MDMODEL_STAR];
    star->mode = MDMINI_STAR_NONE;
    star->motNext = 1;

    posP->x = 0;
    posP->y = 0;
    posP->z = 1800;
    fn_1_15CF8(MDMODEL_STAR, MDCAMERA_FG);
    while(1) {
        model = sys->model;
        camera = sys->camera;
        mess = sys->mess;
        star = sys->star;
        posP = model->posP[MDMODEL_STAR];
        rotP = model->rotP[MDMODEL_STAR];
        scaleP = model->scaleP[MDMODEL_STAR];

        switch(star->mode) {
            case MDMINI_STAR_NONE:
                break;

            case MDMINI_STAR_BACK_START:
                lbl_1_bss_3B0 = 0;
                lbl_1_bss_3AC = 0;
                lbl_1_bss_3A8 = 0;
                lbl_1_bss_3A4 = 0;
                lbl_1_bss_3A0 = 0;
                lbl_1_bss_39C = 0;
                MdMathCurveInit(5, sys->curveTime, lbl_1_data_500, sys->curveSlope);
                star->mode = MDMINI_STAR_BACK;
                break;

            case MDMINI_STAR_BACK:
                MdMathOscillate(MDMATH_OSC_90_REV, &lbl_1_bss_3B0, &lbl_1_bss_3A4, 60);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_3AC, &lbl_1_bss_3A0, 60);
                MdMathOscillate(MDMATH_OSC_0, &lbl_1_bss_3A8, &lbl_1_bss_39C, 60);
                MdMathLerp(&posP->x, 0, 45, lbl_1_bss_3A0);
                MdMathCurveGet(&posP->y, 5, sys->curveTime, lbl_1_data_500, sys->curveSlope, lbl_1_bss_39C);
                MdMathLerp(&posP->z, 1800, 1300, lbl_1_bss_3A4);
                MdMathLerp(&rotP->y, 0, 360, lbl_1_bss_3A4);
                if(lbl_1_bss_3B0 >= 1) {
                    star->mode = MDMINI_STAR_BACK_END;
                }
                break;

            case MDMINI_STAR_BACK_END:
                break;

            case MDMINI_STAR_DECENTER_START:
                lbl_1_bss_3B0 = 0;
                lbl_1_bss_3AC = 0;
                lbl_1_bss_3A4 = 0;
                lbl_1_bss_3A0 = 0;
                lbl_1_bss_3CC[0].x = 64;
                lbl_1_bss_3CC[0].y = 320;
                lbl_1_bss_3CC[0].z = 1000;
                lbl_1_bss_3CC[1].x = 288;
                lbl_1_bss_3CC[1].y = 240;
                lbl_1_bss_3CC[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_3CC[i], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_3B4[i]);
                }
                star->mode = MDMINI_STAR_DECENTER;
                break;

            case MDMINI_STAR_DECENTER:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_3B0, &lbl_1_bss_3A4, 30);
                MdMathLerp(&posP->x, lbl_1_bss_3B4[0].x, lbl_1_bss_3B4[1].x, lbl_1_bss_3A4);
                MdMathLerp(&posP->y, lbl_1_bss_3B4[0].y, lbl_1_bss_3B4[1].y, lbl_1_bss_3A4);
                MdMathLerp(&posP->z, lbl_1_bss_3B4[0].z, lbl_1_bss_3B4[1].z, lbl_1_bss_3A4);
                if(lbl_1_bss_3B0 >= 1) {
                    star->mode = MDMINI_STAR_DECENTER_END;
                }
                break;

            case MDMINI_STAR_DECENTER_END:
                break;

            case MDMINI_STAR_MOVE_LEFT_START:
                lbl_1_bss_3B0 = 0;
                lbl_1_bss_3AC = 0;
                lbl_1_bss_3A8 = 0;
                lbl_1_bss_3A4 = 0;
                lbl_1_bss_3A0 = 0;
                lbl_1_bss_39C = 0;
                lbl_1_bss_3B4[0].x = 0;
                lbl_1_bss_3B4[0].y = -65;
                lbl_1_bss_3B4[0].z = 1300;
                lbl_1_bss_3CC[1].x = 64;
                lbl_1_bss_3CC[1].y = 300;
                lbl_1_bss_3CC[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_3CC[1], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_3B4[1]);
                star->mode = MDMINI_STAR_MOVE_LEFT;
                break;

            case MDMINI_STAR_MOVE_LEFT:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_3B0, &lbl_1_bss_3A4, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_3AC, &lbl_1_bss_3A0, 30);
                MdMathLerp(&posP->x, lbl_1_bss_3B4[0].x, lbl_1_bss_3B4[1].x, lbl_1_bss_3A4);
                MdMathLerp(&posP->y, lbl_1_bss_3B4[0].y, lbl_1_bss_3B4[1].y, lbl_1_bss_3A4);
                MdMathLerpOfs(&posP->z, lbl_1_bss_3B4[0].z, lbl_1_bss_3B4[1].z, lbl_1_bss_3A4, -1.0f*lbl_1_bss_3A0);
                if(lbl_1_bss_3B0 >= 1) {
                    star->mode = MDMINI_STAR_MOVE_LEFT_END;
                }
                fn_1_15CF8(MDMODEL_STAR, MDCAMERA_FG);
                break;

            case MDMINI_STAR_SNAP_LEFT:
                lbl_1_bss_3CC[1].x = 64;
                lbl_1_bss_3CC[1].y = 300;
                lbl_1_bss_3CC[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_3CC[1], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_3B4[1]);
                *posP = lbl_1_bss_3B4[1];
                fn_1_15CF8(MDMODEL_STAR, MDCAMERA_FG);
                star->mode = MDMINI_STAR_MOVE_LEFT_END;
                break;

            case MDMINI_STAR_CENTER_START:
                lbl_1_bss_3B0 = 0;
                lbl_1_bss_3AC = 0;
                lbl_1_bss_3A8 = 0;
                lbl_1_bss_3A4 = 0;
                lbl_1_bss_3A0 = 0;
                lbl_1_bss_39C = 0;
                lbl_1_bss_3B4[0].x = 0;
                lbl_1_bss_3B4[0].y = -65;
                lbl_1_bss_3B4[0].z = 1300;
                lbl_1_bss_3CC[1].x = 64;
                lbl_1_bss_3CC[1].y = 300;
                lbl_1_bss_3CC[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_3CC[1], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_3B4[1]);
                star->mode = MDMINI_STAR_CENTER;
                break;

            case MDMINI_STAR_CENTER:
                MdMathOscillate(MDMATH_OSC_90_REV, &lbl_1_bss_3B0, &lbl_1_bss_3A4, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_3AC, &lbl_1_bss_3A0, 30);
                MdMathLerp(&posP->x, lbl_1_bss_3B4[1].x, lbl_1_bss_3B4[0].x, lbl_1_bss_3A4);
                MdMathLerp(&posP->y, lbl_1_bss_3B4[1].y, lbl_1_bss_3B4[0].y, lbl_1_bss_3A4);
                MdMathLerpOfs(&posP->z, lbl_1_bss_3B4[1].z, lbl_1_bss_3B4[0].z, lbl_1_bss_3A4, -1.0f*lbl_1_bss_3A0);
                if(lbl_1_bss_3B0 >= 1) {
                    star->mode = MDMINI_STAR_CENTER_END;
                }
                fn_1_15CF8(MDMODEL_STAR, MDCAMERA_FG);
                break;


            case MDMINI_STAR_CENTER_END:
                break;
        }
        switch(star->motNext) {
            case MDMINI_STAR_MOT_NONE:
                break;

            case MDMINI_STAR_MOT_RESET:
                Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE]);
                star->motNext = MDMINI_STAR_MOT_NONE;
                break;

            case MDMINI_STAR_MOT_TALK:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_TALK], 0, 32, HU3D_MOTATTR_LOOP);
                star->motNext = MDMINI_STAR_MOT_NONE;
                break;

            case MDMINI_STAR_MOT_IDLE:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE], 0, 32, HU3D_MOTATTR_LOOP);
                star->motNext = MDMINI_STAR_MOT_NONE;
                break;
        }
        HuPrcVSleep();
    }
}
/* 256 insns */
/* twin: MdPartyPlayerSprUpdate (mdparty PlayerSprUpdate) */
void fn_1_1804(void)
{
    MDMINI_PLAYERSPR *playerSpr; //r31
    HuVec2f *playerNoScale; //r30
    HuVec2f *comDifScale; //r29
    int i; //r28
    MDSPRITE_WORK *sprite; //r27
    HUSPRGRPID playerNoGrpId; //r26
    HUSPRGRPID comDifGrpId; //r25
    MDCAMERA_WORK *camera; //r24
    MDMODEL_WORK *model; //r23

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    comDifGrpId = sprite->grpId[MDSPR_GRP_COMDIF];
    for(playerSpr=&sys->playerSpr[0], i=0; i<4; i++, playerSpr++) {
        playerSpr->mode = MDMINI_PLAYERSPR_NONE;
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
        comDifGrpId = sprite->grpId[MDSPR_GRP_COMDIF];
        HuSprGrpPosSet(playerNoGrpId, 0, 0);
        HuSprGrpPosSet(comDifGrpId, 0, 0);
        for(playerSpr=&sys->playerSpr[0], i=0; i<4; i++, playerSpr++) {
            playerNoScale = MdSpriteScaleGet(sprite, MDSPR_GRP_PLAYERNO, i);
            comDifScale = MdSpriteScaleGet(sprite, MDSPR_GRP_COMDIF, i);
            switch(playerSpr->mode) {
                case MDMINI_PLAYERSPR_NONE:
                    break;

                case MDMINI_PLAYERSPR_GROW_START:
                    HuSprDispOn(playerNoGrpId, i);
                    HuSprDispOn(comDifGrpId, i);
                    playerNoScale->x = 0;
                    playerNoScale->y = 0;
                    comDifScale->x = 0;
                    comDifScale->y = 0;
                    playerSpr->time = 0;
                    playerSpr->ofsTime = 0;
                    playerSpr->t = 0;
                    playerSpr->ofsT = 0;
                    playerSpr->mode = MDMINI_PLAYERSPR_GROW;
                    break;

                case MDMINI_PLAYERSPR_GROW:
                    MdMathOscillate(MDMATH_OSC_90, &playerSpr->time, &playerSpr->t, 15);
                    MdMathOscillate(MDMATH_OSC_180, &playerSpr->ofsTime, &playerSpr->ofsT, 15);
                    MdMathLerpOfs(&playerNoScale->x, 0, 1, playerSpr->t, 0.5f*playerSpr->ofsT);
                    playerNoScale->y = playerNoScale->x;
                    MdMathLerpOfs(&comDifScale->x, 0, 1, playerSpr->t, 0.5f*playerSpr->ofsT);
                    comDifScale->y = comDifScale->x;
                    if(playerSpr->time >= 1) {
                        playerSpr->mode = MDMINI_PLAYERSPR_GROW_END;
                    }
                    break;

                case MDMINI_PLAYERSPR_GROW_END:
                    break;

                case MDMINI_PLAYERSPR_SHRINK_START:
                    playerSpr->time = 0;
                    playerSpr->ofsTime = 0;
                    playerSpr->t = 0;
                    playerSpr->ofsT = 0;
                    playerSpr->mode = MDMINI_PLAYERSPR_SHRINK;
                    break;

                case MDMINI_PLAYERSPR_SHRINK:
                    MdMathOscillate(MDMATH_OSC_90, &playerSpr->time, &playerSpr->t, 15);
                    MdMathLerp(&playerNoScale->x, 1, 0, playerSpr->t);
                    playerNoScale->y = playerNoScale->x;
                    MdMathLerp(&comDifScale->x, 1, 0, playerSpr->t);
                    comDifScale->y = comDifScale->x;
                    if(playerSpr->time >= 1) {
                        HuSprDispOff(playerNoGrpId, i);
                        HuSprDispOff(comDifGrpId, i);
                        playerSpr->mode = MDMINI_PLAYERSPR_SHRINK_END;
                    }
                    break;

                case MDMINI_PLAYERSPR_SHRINK_END:
                    break;
            }
        }
        HuPrcVSleep();
    }
}

/* 255 insns */
/* twin: MdPartyChrUpdate (mdparty ChrUpdate); lbl_1_data_178 = CharPos, lbl_1_data_268 = CharRot */
void fn_1_1C04(void)
{
    MDMINI_CHR *chr; //r31
    int i; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *posP; //r28
    HuVecF *rotP; //r27
    MDCAMERA_WORK *camera; //r26
    MDSPRITE_WORK *sprite; //r25

    HuVecF *scaleP; //sp+0x8
    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;

    for(chr=&sys->chr[0], i=0; i<10; i++, chr++) {
        chr->mode = MDMINI_CHR_NONE;
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        for(chr=&sys->chr[0], i=0; i<10; i++, chr++) {
            if(i != 0 && i != 1 && i != 2 && i != 5) {
                posP = model->posP[i+MDMODEL_MARIO];
                rotP = model->rotP[i+MDMODEL_MARIO];
                scaleP = model->scaleP[i+MDMODEL_MARIO];
                switch(chr->mode) {
                    case MDMINI_CHR_NONE:
                        break;

                    case MDMINI_CHR_INIT:
                        *posP = lbl_1_data_178[i][0];
                        *rotP = lbl_1_data_268[i][0];
                        chr->mode = MDMINI_CHR_NONE;
                        break;

                    case MDMINI_CHR_SELECT:
                    case MDMINI_CHR_SELECT_WAIT:
                        chr->origPos = *posP;
                        chr->origRot = *rotP;
                        if(chr->mode == MDMINI_CHR_SELECT) {
                            chr->pos = lbl_1_data_178[i][1];
                            chr->rot = lbl_1_data_268[i][1];
                        } else if(chr->mode == MDMINI_CHR_SELECT_WAIT) {
                            chr->pos = lbl_1_data_178[i][0];
                            chr->rot = lbl_1_data_268[i][0];
                        }
                        chr->time = 0;
                        chr->ofsTime = 0;
                        chr->t = 0;
                        chr->ofsT = 0;
                        if(chr->mode == MDMINI_CHR_SELECT) {
                            chr->mode = MDMINI_CHR_SELECT_MOVE;
                        } else if(chr->mode == MDMINI_CHR_SELECT_WAIT) {
                            chr->mode = MDMINI_CHR_SELECT_MOVE_WAIT;
                        }
                        break;

                    case MDMINI_CHR_SELECT_MOVE:
                    case MDMINI_CHR_SELECT_MOVE_WAIT:
                        if(chr->mode == MDMINI_CHR_SELECT_MOVE) {
                            MdMathOscillate(MDMATH_OSC_0, &chr->time, &chr->t, 15);
                        } else if(chr->mode == MDMINI_CHR_SELECT_MOVE_WAIT) {
                            MdMathOscillate(MDMATH_OSC_0, &chr->time, &chr->t, 15);
                        }
                        MdMathLerp(&posP->x, chr->origPos.x, chr->pos.x, chr->t);
                        MdMathLerp(&posP->y, chr->origPos.y, chr->pos.y, chr->t);
                        MdMathLerp(&posP->z, chr->origPos.z, chr->pos.z, chr->t);
                        MdMathLerp(&rotP->x, chr->origRot.x, chr->rot.x, chr->t);
                        MdMathLerp(&rotP->y, chr->origRot.y, chr->rot.y, chr->t);
                        MdMathLerp(&rotP->z, chr->origRot.z, chr->rot.z, chr->t);
                        if(chr->time >= 1) {
                            chr->mode = MDMINI_CHR_NONE;
                        }
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}

/* 6 insns */
/* twin: MdPartyRingUpdate (mdparty RingUpdate) */
void fn_1_2000(void)
{
    while(1) {
        MdRingMain();
        HuPrcVSleep();
    }
}

/* 17 insns */
/* twin: MdSelMainWinUpdate */
void fn_1_2018(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_MAIN);
        HuPrcVSleep();
    }
}

/* 17 insns */
/* twin: MdSelHelpWinUpdate */
void fn_1_205C(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_HELP);
        HuPrcVSleep();
    }
}

/* 138 insns */
/* twin: MdPartyInit (mdparty MdInit); mdmini adds the evtNo 1 save-mode pass and has no loadProcReady */
void fn_1_20A0(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdRingCreate();
    MdModelCreate(sys->model, sys->camera);
    MdToueiTexBufInit();
    HuPrcVSleep();
    HuDataDirClose(DATA_mdmini);
    HuPrcVSleep();
    if(sys->evtNo == 1) {
        SLSaveModeExec(FALSE);
    }
    HuPrcVSleep();
    MdToueiMdlInit();
    sys->starProc = HuPrcChildCreate(fn_1_C4C, 107, 12288, 0, sys->objman);
    sys->playerSprProc = HuPrcChildCreate(fn_1_1804, 108, 12288, 0, sys->objman);
    sys->chrProc = HuPrcChildCreate(fn_1_1C04, 109, 12288, 0, sys->objman);
    sys->mainWinProc = HuPrcChildCreate(fn_1_2018, 110, 4096, 0, sys->objman);
    sys->textWinProc = HuPrcChildCreate(fn_1_205C, 111, 4096, 0, sys->objman);
    sys->loadState = MD_LOAD_STATE_NONE;
    sys->loadAsyncStat = 0;
    sys->loadDir = DATA_rescard;
    sys->loadProc = HuPrcChildCreate(fn_1_8CC, 106, 12288, 0, sys->objman);
    HuPrcVSleep();
}

/* 68 insns */
/* twin: MdPartyClose (mdparty MdClose) */
void fn_1_22C8(void)
{
    if(!sys->skipWipeF) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeWait();
    }
    HuAudAllStop();
    MdMessKill(sys->mess);
    if(sys->ovlCallMode == MD_OVLCALL_GOTO) {
        omOvlGoto(sys->nextDll, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_CALL) {
        omOvlCall(sys->nextDll, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_RETURN) {
        omOvlReturn(1);
    }
    HuPrcEnd();
    while(1) {
        HuPrcVSleep();
    }
}

/* 264 insns */
/* twin: MdPartyFlowInit */
void fn_1_23D8(void)
{
    int i;
    MDMODEL_WORK *model;
    MDSPRITE_WORK *sprite;
    MDMINI_CHR *chr;

    MDCAMERA_WORK *camera;
    MDMESS_WORK *mess;

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    chr = &sys->chr[0];
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_COMDIF, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NAME, FALSE);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAR]);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_STAGE_CHR]);
    for(i=0; i<10; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_MARIO]);
    }
    for(i=0; i<4; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
    }
    for(i=0; i<4; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_COM_1P]);
    }
    for(i=0; i<10; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_CHR_00]);
    }
    for(i=0; i<MDMODEL_CAP_MODE_NUM; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MODE_00]);
    }
    Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_WIN]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_GENRE]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_VS]);
    for(i=0; i<4; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_FINGER_1P]);
    }
    for(i=0; i<4; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_RING_1P]);
    }
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    CharMotionVoiceOnSet(0, 47, 0);
    CharMotionVoiceOnSet(1, 6, 0);
    CharMotionVoiceOnSet(2, 6, 0);
    CharMotionVoiceOnSet(3, 6, 0);
    CharMotionVoiceOnSet(4, 6, 0);
    CharMotionVoiceOnSet(5, 6, 0);
    CharMotionVoiceOnSet(6, 6, 0);
    CharMotionVoiceOnSet(7, 6, 0);
    CharMotionVoiceOnSet(8, 6, 0);
    CharMotionVoiceOnSet(9, 6, 0);
    for(i=0; i<4; i++) {
        MdRingDispSet(i, FALSE);
    }
    sys->ringProc = HuPrcChildCreate(fn_1_2000, 104, 12288, 0, sys->objman);
    for(i=0; i<10; i++) {
        chr[i].mode = 1; /* mdparty MDPARTY_CHR_INIT */
    }
    HuPrcSleep(2);
    MdProcCall(MDMINI_PROC_RESET, 0);
    HuPrcVSleep();
    if(sys->evtNo == 0) {
        sys->subMode = 0;
        sys->flowMode = MDMINI_FLOW_PLAYER_NUM_SEL;
    } else if(sys->evtNo == 1) {
        sys->subMode = 50;
        sys->flowMode = MDMINI_FLOW_MODE_SEL;
    }
}
/* 874 insns */
void fn_1_27F8(void)
{
    MDMESS_WORK *mess;
    int ret;
    MDMINI_STAR *star;
    MDMODEL_WORK *model;
    MDMINI_CHR *chr;

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            fn_1_14C2C();
            sys->prevPlayerNum = sys->playerNum;
            fn_1_17008(0); /* music start */
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            sys->subMode = 1;
            break;

        case 1:
            ret = WipeCheckEnd();
            if(ret == FALSE) {
                MdProcWait(MDMINI_PROC_NAME, 0);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            ret = MdProcCall(MDMINI_PROC_WIN, FALSE);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 32, 372, 512, 64, 0);
                MdMessWinOpen(mess, MDMESS_WIN_HELP, MDMESS_WIN_NOSPEAKER, 0, 0, 1, 32, 340, 512, 32, 0);
                MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
                MdMessWinAttrSet(mess, MDMESS_WIN_MAIN, HUWIN_ATTR_ALIGN_CENTER);
                MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
                MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_ENTER, MDMESS_WIN_LIST_END);
                fn_1_17008(11);
                sys->subMode = 3;
            }
            break;

        case 3:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_PLAYER_NUM_START, MDMESS_WIN_LIST_END);
                while(MdMessWinCheck(mess, MDMESS_WIN_MAIN) == FALSE) {
                    HuPrcVSleep();
                }
                while(MdProcCall(MDMINI_PROC_NAME, 1) == FALSE) {
                    HuPrcVSleep();
                }
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->mode = 1;
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                sys->subMode = 4;
            }
            break;

        case 4:
            if(star->mode == 3) {
                sys->subMode = 6;
            }
            break;

        case 5:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                star->motNext = 3;
                sys->subMode = 6;
            }
            break;

        case 6:
            ret = MdProcCall(MDMINI_PROC_CAP_PLAYER, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2;
                if(sys->playerNum == 3) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_PLAYER_NUM_4, MDMESS_WIN_LIST_END);
                } else {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                        MESS_MGMODE_SYS_PLAYER_NUM,
                        MESS_MGMODE_SYS_PLAYER_NUM_1+sys->playerNum,
                        MESS_MGMODE_SYS_PLAYER_NUM_3-sys->playerNum,
                        MDMESS_WIN_LIST_END);
                }
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                star->motNext = 2;
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 8;
                } else {
                    sys->subMode = 7;
                }
            }
            break;

        case 7:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 8;
            }
            break;

        case 8:
            if(sys->maxPlayerNum > 1 && ((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT))) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    sys->prevPlayerNum = sys->playerNum;
                    if(--sys->playerNum == -1) {
                        sys->playerNum = sys->maxPlayerNum-1;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->prevPlayerNum = sys->playerNum;
                    sys->playerNum = (++sys->playerNum)%sys->maxPlayerNum;
                    sys->cursorDir = 1;
                }
                if(sys->playerNum == 3) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_PLAYER_NUM_4, MDMESS_WIN_LIST_END);
                } else {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                        MESS_MGMODE_SYS_PLAYER_NUM,
                        MESS_MGMODE_SYS_PLAYER_NUM_1+sys->playerNum,
                        MESS_MGMODE_SYS_PLAYER_NUM_3-sys->playerNum,
                        MDMESS_WIN_LIST_END);
                }
                fn_1_17008(2);
                sys->subMode = 9;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_QUIT, MDMESS_WIN_LIST_END);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_17008(5);
                sys->subMode = 10;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_14FD0();
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 3;
                fn_1_17008(3);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 15;
                } else {
                    sys->subMode = 14;
                }
            }
            break;

        case 9:
            ret = MdProcCall(MDMINI_PROC_CAP_PLAYER, sys->cursorDir+2);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 8;
            }
            break;

        case 10:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    if(sys->playerNum == 3) {
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_PLAYER_NUM_4, MDMESS_WIN_LIST_END);
                    } else {
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                            MESS_MGMODE_SYS_PLAYER_NUM,
                            MESS_MGMODE_SYS_PLAYER_NUM_1+sys->playerNum,
                            MESS_MGMODE_SYS_PLAYER_NUM_3-sys->playerNum,
                            MDMESS_WIN_LIST_END);
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->subMode = 8;
                } else if(ret == 0) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                    sys->subMode = 11;
                }
            }
            break;

        case 11:
            ret = MdProcCall(MDMINI_PROC_WIN, TRUE);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 13;
                } else {
                    sys->subMode = 12;
                }
            }
            break;

        case 12:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 13;
            }
            break;

        case 13:
            ret = MdProcCall(MDMINI_PROC_CAP_PLAYER, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->loadState = MD_LOAD_STATE_BOARD_LOAD;
                sys->loadDir = DATA_mdsel;
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                fn_1_17008(1); /* music stop */
                WipeWait();
                while(sys->loadState != MD_LOAD_STATE_LOAD) {
                    HuPrcVSleep();
                }
                omOvlHisChg(0, sys->ovlHis->ovl, 0, sys->ovlHis->stat);
                sys->ovlCallMode = MD_OVLCALL_RETURN;
                sys->nextDll = DLL_mdseldll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;

        case 14:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 15;
            }
            break;

        case 15:
            ret = MdProcCall(MDMINI_PROC_CAP_PLAYER, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDMINI_FLOW_CHR_SEL;
            }
            break;
    }
}
/* 2030 insns */
/* twin: MdPartyFlowChrSel. Character select: humans pick with their own pads (A pick, B undo),
 * then pad 1 picks each COM's character and difficulty. subMode states 0-15 (see OUT.txt). */
void fn_1_35A0(void)
{
    int i;
    MDMODEL_WORK *model;
    MDMINI_PLAYERSPR *playerSpr;
    MDMESS_WORK *mess;
    MDMINI_CHR *chr;
    MDSPRITE_WORK *sprite;
    BOOL result;
    MDMINI_STAR *star;
    int difMax;

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                if(sys->padEnable[i] == FALSE) {
                    sys->chrSel[i] = 0;
                } else {
                    sys->chrSel[i] = i;
                }
                sys->chrSelEnd[i] = FALSE;
                sys->comDif[i] = 1;
                HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], i, sys->comDif[i]);
            }
            sys->subMode = 1;
            break;

        case 1:
            result = MdProcCall(MDMINI_PROC_CHR, 0);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2; /* mdparty MDPARTY_STAR_MOT_TALK */
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_CHR_SEL_MAN, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                sys->subMode = 2;
            }
            break;

        case 2:
            result = MdProcCall(MDMINI_PROC_FINGER, 0);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 3:
            if(sys->chrSelEnd[0] == FALSE &&
                (playerSpr[0].mode == 0 || playerSpr[0].mode == 6) &&
                (HuPadBtnDown[0] & PAD_BUTTON_B)) {
                    fn_1_17008(5);
                    star->motNext = 3; /* mdparty MDPARTY_STAR_MOT_IDLE */
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                    for(i=0; i<4; i++) {
                        Hu3DModelDispOff(model->mdlId[i+MDMODEL_FINGER_1P]);
                    }
                    for(i=0; i<4; i++) {
                        playerSpr[i].mode = 0;
                    }
                    MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
                    MdSpriteDispSet(sprite, MDSPR_GRP_COMDIF, FALSE);
                    for(i=0; i<4; i++) {
                        if(sys->chrSelEnd[i] == TRUE) {
                            Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                            chr[sys->chrSel[i]].mode = 3;
                        }
                    }
                    for(i=0; i<4; i++) {
                        MdRingDispSet(i, FALSE);
                    }
                    sys->subMode = 4;
            } else {
                for(i=0; i<4; i++) {
                    if(sys->padEnable[i] == FALSE) {
                        continue;
                    }
                    if(playerSpr[i].mode == 0 || playerSpr[i].mode == 3 || playerSpr[i].mode == 6) {
                        result = fn_1_15590(i, FALSE);
                        if(result == TRUE) {
                            fn_1_17008(2);
                            fn_1_153D0();
                        } else if((HuPadBtnDown[i] & PAD_BUTTON_B) && sys->chrSelEnd[i] == TRUE) {
                            sys->chrSelEnd[i] = FALSE;
                            Hu3DModelDispOn(model->mdlId[i+MDMODEL_FINGER_1P]);
                            playerSpr[i].mode = 4;
                            Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                            chr[sys->chrSel[i]].mode = 3;
                            fn_1_17008(5);
                            MdRingModeSet(i, 4);
                        } else if((HuPadBtnDown[i] & PAD_BUTTON_A) && sys->chrSelEnd[i] == FALSE) {
                            sys->chrSelEnd[i] = TRUE;
                            Hu3DModelDispOff(model->mdlId[i+MDMODEL_FINGER_1P]);
                            playerSpr[i].mode = 1;
                            Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_WIN], 0, 8, HU3D_MOTATTR_NONE);
                            chr[sys->chrSel[i]].mode = 2;
                            fn_1_17008(4);
                            fn_1_17008(sys->chrSel[i]+13);
                            MdRingModeSet(i, 1);
                            MdRingOfsSet(i, 0, 0, 0);
                            MdRingMdlSet(i, sys->chrSel[i]+MDMODEL_CAP_CHR_00);
                            MdRingScaleSet(i, 1.0);
                        }
                    }
                }
                if(((sys->chrSelEnd[0] == TRUE && playerSpr[0].mode == 3) || sys->padEnable[0] == FALSE) &&
                    ((sys->chrSelEnd[1] == TRUE && playerSpr[1].mode == 3) || sys->padEnable[1] == FALSE) &&
                    ((sys->chrSelEnd[2] == TRUE && playerSpr[2].mode == 3) || sys->padEnable[2] == FALSE) &&
                    ((sys->chrSelEnd[3] == TRUE && playerSpr[3].mode == 3) || sys->padEnable[3] == FALSE)) {
                    if(sys->playerNum == 3) {
                        star->motNext = 3;
                        MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                        MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                        sys->subMode = 14;
                    } else {
                        sys->selComNo = 0;
                        fn_1_15BF4();
                        fn_1_153D0();
                        Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                        model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4;
                        model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4;
                        model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4;
                        /* retail: '+ selComNo' here (0 at this point); the other two call sites subtract it */
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                            MESS_MGMODE_SYS_CHR_SEL_COM,
                            (MESS_MGMODE_SYS_PLAYER_NUM_1+2)-sys->playerNum+sys->selComNo,
                            MDMESS_WIN_LIST_END);
                        sys->subMode = 6;
                    }
                }
            }
            break;

        case 4:
            for(i=0; i<4; i++) {
                Hu3DModelDispOff(model->mdlId[i+MDMODEL_FINGER_1P]);
            }
            MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
            sys->subMode = 5;
            break;

        case 5:
            result = MdProcCall(MDMINI_PROC_CHR, 1);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                fn_1_14C2C();
                sys->prevPlayerNum = sys->playerNum;
                sys->subMode = 6;
                sys->flowMode = MDMINI_FLOW_PLAYER_NUM_SEL;
            }
            break;

        case 6:
            if(sys->selComNo == 0 && (HuPadBtnDown[0] & PAD_BUTTON_B)) {
                for(i=0; i<4; i++) {
                    if(sys->chrSelEnd[i] == TRUE) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                        chr[sys->chrSel[i]].mode = 3;
                        MdRingModeSet(i, 4);
                        playerSpr[i].mode = 4;
                        sys->chrSelEnd[i] = FALSE;
                    }
                }
                Hu3DModelDispOff(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_CHR_SEL_MAN, MDMESS_WIN_LIST_END);
                fn_1_17008(5);
                sys->subMode = 7;
            } else {
                result = fn_1_15590(sys->comPlayerNo[sys->selComNo], TRUE);
                if(result == TRUE) {
                    fn_1_17008(2);
                    fn_1_153D0();
                } else if((HuPadBtnDown[0] & PAD_BUTTON_B) && sys->selComNo > 0) {
                    Hu3DModelDispOff(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                    sys->selComNo--;
                    Hu3DMotionShiftSet(model->mdlId[sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDMODEL_MARIO], model->motId[(sys->chrSel[sys->comPlayerNo[sys->selComNo]]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                    chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 3;
                    fn_1_17008(5);
                    MdRingModeSet(sys->comPlayerNo[sys->selComNo], 4);
                    playerSpr[sys->comPlayerNo[sys->selComNo]].mode = 4;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                        MESS_MGMODE_SYS_CHR_SEL_COM,
                        (MESS_MGMODE_SYS_PLAYER_NUM_1+2)-sys->playerNum-sys->selComNo,
                        MDMESS_WIN_LIST_END);
                    sys->subMode = 15;
                } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                    playerSpr[sys->comPlayerNo[sys->selComNo]].mode = 1;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_DIF_SEL, MDMESS_WIN_LIST_END);
                    Hu3DModelDispOff(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                    Hu3DMotionShiftSet(model->mdlId[sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDMODEL_MARIO], model->motId[(sys->chrSel[sys->comPlayerNo[sys->selComNo]]*2)+MDMODEL_MOT_MARIO_WIN], 0, 8, HU3D_MOTATTR_NONE);
                    chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 2;
                    MdRingModeSet(sys->comPlayerNo[sys->selComNo], 1);
                    MdRingOfsSet(sys->comPlayerNo[sys->selComNo], 0, 0, 0);
                    MdRingMdlSet(sys->comPlayerNo[sys->selComNo], sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDMODEL_CAP_CHR_00);
                    MdRingScaleSet(sys->comPlayerNo[sys->selComNo], 1.0);
                    fn_1_17008(4);
                    fn_1_17008(sys->chrSel[sys->comPlayerNo[sys->selComNo]]+13);
                    sys->subMode = 8;
                }
            }
            break;

        case 7:
            if(playerSpr[0].mode == 6) {
                sys->subMode = 2;
            }
            break;

        case 8:
            if(playerSpr[sys->comPlayerNo[sys->selComNo]].mode == 3) {
                sys->subMode = 9;
            }
            break;

        case 9:
            result = MdProcCall(MDMINI_PROC_CURSOR, 4);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], (int)sys->comPlayerNo[sys->selComNo]);
                HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], (int)sys->comPlayerNo[sys->selComNo]);
                fn_1_153D0();
                sys->subMode = 10;
            }
            break;

        case 10:
            if(GwCommon.veryHardUnlock == TRUE) {
                difMax = 4;
            } else {
                difMax = 3;
            }
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->comDif[sys->comPlayerNo[sys->selComNo]] == -1) {
                        sys->comDif[sys->comPlayerNo[sys->selComNo]] = difMax-1;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->comDif[sys->comPlayerNo[sys->selComNo]] = ++sys->comDif[sys->comPlayerNo[sys->selComNo]]%difMax;
                    sys->cursorDir = 1;
                }
                fn_1_17008(2);
                fn_1_153D0();
                HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[sys->selComNo], sys->comDif[sys->comPlayerNo[sys->selComNo]]);
                sys->subMode = 11;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                playerSpr[sys->comPlayerNo[sys->selComNo]].mode = 4;
                Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                Hu3DMotionShiftSet(model->mdlId[sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDMODEL_MARIO], model->motId[(sys->chrSel[sys->comPlayerNo[sys->selComNo]]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 3;
                MdRingModeSet(sys->comPlayerNo[sys->selComNo], 4);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                    MESS_MGMODE_SYS_CHR_SEL_COM,
                    (MESS_MGMODE_SYS_PLAYER_NUM_1+2)-sys->playerNum-sys->selComNo,
                    MDMESS_WIN_LIST_END);
                fn_1_17008(5);
                sys->subMode = 12;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                sys->chrSelEnd[sys->comPlayerNo[sys->selComNo]] = TRUE;
                if(sys->selComNo+1 < 3-sys->playerNum) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                        MESS_MGMODE_SYS_CHR_SEL_COM,
                        (MESS_MGMODE_SYS_PLAYER_NUM_1+1)-sys->playerNum-sys->selComNo,
                        MDMESS_WIN_LIST_END);
                    fn_1_17008(4);
                } else {
                    fn_1_17008(3);
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                    star->motNext = 3;
                }
                sys->subMode = 13;
            }
            break;

        case 11:
            result = MdProcCall(MDMINI_PROC_CURSOR, sys->cursorDir+6);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 10;
            }
            break;

        case 12:
            result = MdProcCall(MDMINI_PROC_CURSOR, 5);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                sys->subMode = 6;
            }
            break;

        case 13:
            result = MdProcCall(MDMINI_PROC_CURSOR, 5);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->selComNo++;
                if(sys->selComNo < 3-sys->playerNum) {
                    fn_1_15BF4();
                    fn_1_153D0();
                    Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4;
                    sys->subMode = 6;
                } else if(sys->selComNo >= 3-sys->playerNum) {
                    sys->subMode = 14;
                }
            }
            break;

        case 14:
            result = MdProcCall(MDMINI_PROC_CHR, 2);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDMINI_FLOW_MODE_SEL;
            }
            break;

        case 15:
            if(playerSpr[sys->comPlayerNo[sys->selComNo]].mode == 6) {
                Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                sys->chrSelEnd[sys->comPlayerNo[sys->selComNo]] = FALSE;
                fn_1_153D0();
                sys->subMode = 6;
            }
            break;
    }
}
/* 1688 insns */
void fn_1_5558(void)
{
    int i;
    MDMESS_WORK *mess;
    MDMODEL_WORK *model;
    int ret;
    MDMINI_STAR *star;
    MDSPRITE_WORK *sprite;
    HuVec2f *scale;
    MDMINI_PLAYERSPR *playerSpr;
    MDMINI_CHR *chr;
    float maxTime;

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            sys->unk3D = 0;
            fn_1_16358();
            sys->subMode = 1;
            break;

        case 1:
            ret = MdProcCall(MDMINI_PROC_UNK6, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 8);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGFREE+sys->unk3D, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESSNUM(MESS_SYSHELP, 0x21), MDMESS_WIN_LIST_END);
                sys->subMode = 3;
            }
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                sys->unk3E = sys->unk3D;
                if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk3D = (++sys->unk3D)%6;
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk3D == -1) {
                        sys->unk3D = 5;
                    }
                    sys->cursorDir = 1;
                }
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGFREE+sys->unk3D, MDMESS_WIN_LIST_END);
                fn_1_17008(2);
                sys->subMode = 4;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_17008(5);
                sys->subMode = 5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                if(sys->unk3F[sys->unk3D] == TRUE) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                    fn_1_17008(3);
                    sys->subMode = 8;
                } else {
                    fn_1_17008(6);
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_X) {
                fn_1_17008(5);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_QUIT, MDMESS_WIN_LIST_END);
                while(MdMessWinCheck(mess, MDMESS_WIN_MAIN) == FALSE) {
                    HuPrcVSleep();
                }
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGFREE+sys->unk3D, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESSNUM(MESS_SYSHELP, 0x21), MDMESS_WIN_LIST_END);
                } else if(ret == 0) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                    MdProcWait(MDMINI_PROC_CURSOR, 9);
                    MdProcCall(MDMINI_PROC_RESET, 0);
                    MdProcWait(MDMINI_PROC_WIN, TRUE);
                    MdProcCall(MDMINI_PROC_RESET, 0);
                    sys->loadState = MD_LOAD_STATE_BOARD_LOAD;
                    sys->loadDir = DATA_mdsel;
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_17008(1);
                    WipeWait();
                    while(sys->loadState != MD_LOAD_STATE_LOAD) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 0, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_RETURN;
                    sys->nextDll = DLL_mdseldll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            }
            break;

        case 4:
            ret = MdProcCall(MDMINI_PROC_UNK6, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 5:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 9);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 6;
            }
            break;

        case 6:
            ret = MdProcCall(MDMINI_PROC_UNK6, 2);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 7;
            }
            break;

        case 7:
            ret = MdProcCall(MDMINI_PROC_CHR, 3);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                if(sys->playerNum == 3) {
                    sys->selComNo = 0;
                    for(i=0; i<4; i++) {
                        sys->chrSelEnd[i] = FALSE;
                        playerSpr[i].mode = 4;
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                        chr[sys->chrSel[i]].mode = 3;
                        MdRingModeSet(i, 4);
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_CHR_SEL_MAN, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->subMode = 2;
                    sys->flowMode = MDMINI_FLOW_CHR_SEL;
                } else {
                    sys->selComNo = 0;
                    for(i=0; i<3; i++) {
                        if(sys->comPlayerNo[i] != -1) {
                            sys->chrSelEnd[sys->comPlayerNo[i]] = FALSE;
                            playerSpr[sys->comPlayerNo[i]].mode = 4;
                            Hu3DMotionShiftSet(model->mdlId[sys->chrSel[sys->comPlayerNo[i]]+MDMODEL_MARIO], model->motId[(sys->chrSel[sys->comPlayerNo[i]]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                            chr[sys->chrSel[sys->comPlayerNo[i]]].mode = 3;
                            MdRingModeSet(sys->comPlayerNo[i], 4);
                        }
                    }
                    fn_1_15BF4();
                    fn_1_153D0();
                    Hu3DModelDispOn(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]);
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE,
                        MESS_MGMODE_SYS_CHR_SEL_COM,
                        (MESS_MGMODE_SYS_PLAYER_NUM_3-sys->playerNum)+sys->selComNo,
                        MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->subMode = 6;
                    sys->flowMode = MDMINI_FLOW_CHR_SEL;
                }
            }
            break;

        case 8:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 9);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 9;
            }
            break;

        case 9:
            ret = MdProcCall(MDMINI_PROC_UNK6, 3);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                if(sys->unk3D == 1) {
                    sys->subMode = 0;
                    sys->flowMode = MDMINI_FLOW_UNK4;
                } else {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_CONFIRM, MDMESS_WIN_LIST_END);
                    fn_1_17008(12);
                    sys->subMode = 10;
                }
            }
            break;

        case 10:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_RESET, MDMESS_WIN_LIST_END);
                    sys->subMode = 11;
                } else if(ret == 0) {
                    MdProcCall(MDMINI_PROC_RESET, 0);
                    fn_1_16978();
                    if(sys->unk3D == 2) {
                        _SetFlag(FLAG_MG_CIRCUIT);
                        MBPartySaveInit(8);
                    }
                    if(sys->unk3D == 2) {
                        sys->loadState = MD_LOAD_STATE_CHAR_LOAD;
                    } else {
                        sys->loadState = MD_LOAD_STATE_WAIT;
                        sys->loadDir = lbl_1_data_160[sys->unk3D];
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MG_START, MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    while(MdProcCall(MDMINI_PROC_UNK13, 1) == FALSE) {
                        HuPrcVSleep();
                    }
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 55);
                    fn_1_17008(1);
                    fn_1_17008(10);
                    while(WipeCheckEnd() != FALSE) {
                        MdProcCall(MDMINI_PROC_UNK13, 1);
                        HuPrcVSleep();
                    }
                    while(sys->loadState != MD_LOAD_STATE_LOAD) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                    sys->nextDll = lbl_1_data_148[sys->unk3D];
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            }
            break;

        case 11:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->motNext = 3;
                    sys->subMode = 12;
                } else if(ret == 0) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->mode = 11;
                    star->motNext = 3;
                    for(i=0; i<4; i++) {
                        sys->chrSelEnd[i] = FALSE;
                        playerSpr[i].mode = 4;
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                        chr[sys->chrSel[i]].mode = 3;
                        MdRingModeSet(i, 4);
                    }
                    sys->subMode = 13;
                }
            }
            break;

        case 12:
            ret = MdProcCall(MDMINI_PROC_UNK6, 4);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 13:
            ret = MdProcCall(MDMINI_PROC_UNK10, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                fn_1_14C2C();
                sys->prevPlayerNum = sys->playerNum;
                sys->subMode = 6;
                sys->flowMode = MDMINI_FLOW_PLAYER_NUM_SEL;
            }
            break;

        case 50:
            MdProcCall(MDMINI_PROC_RESET, 0);
            fn_1_14E24();
            fn_1_14FD0();
            fn_1_152D4();
            MdProcCall(MDMINI_PROC_CHR, 4);
            MdProcCall(MDMINI_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                maxTime = Hu3DMotionMotionMaxTimeGet(model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_WIN]);
                Hu3DModelAttrReset(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSpeedSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], 1.0f);
                Hu3DMotionSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_WIN]);
                Hu3DMotionTimeSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], maxTime);
                chr[sys->chrSel[i]].mode = 2;
            }
            for(i=0; i<4; i++) {
                MdRingModeSet(i, 1);
                MdRingOfsSet(i, 0, 0, 0);
                MdRingMdlSet(i, sys->chrSel[i]+MDMODEL_CAP_CHR_00);
                MdRingScaleSet(i, 1.0);
            }
            for(i=0; i<4; i++) {
                playerSpr[i].mode = 3;
                HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], i);
                scale = MdSpriteScaleGet(sprite, MDSPR_GRP_PLAYERNO, i);
                scale->x = scale->y = 1.0f;
            }
            for(i=0; i<3; i++) {
                if(sys->comPlayerNo[i] != -1) {
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->comPlayerNo[i]);
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i]);
                    scale = MdSpriteScaleGet(sprite, MDSPR_GRP_COMDIF, sys->comPlayerNo[i]);
                    scale->x = scale->y = 1.0f;
                    HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i], sys->comDif[sys->comPlayerNo[i]]);
                }
            }
            fn_1_153D0();
            star->mode = 10;
            star->motNext = 1;
            fn_1_17008(0);
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            sys->subMode = 51;
            break;

        case 51:
            ret = WipeCheckEnd();
            if(ret == FALSE) {
                sys->subMode = 52;
            }
            break;

        case 52:
            ret = MdProcCall(MDMINI_PROC_WIN, FALSE);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 32, 372, 512, 64, 0);
                MdMessWinOpen(mess, MDMESS_WIN_HELP, MDMESS_WIN_NOSPEAKER, 0, 0, 1, 32, 340, 512, 32, 0);
                MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
                MdMessWinAttrSet(mess, MDMESS_WIN_MAIN, HUWIN_ATTR_ALIGN_CENTER);
                MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
                MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                sys->unk3D = 0;
                fn_1_16358();
                sys->subMode = 53;
            }
            break;

        case 53:
            ret = MdProcCall(MDMINI_PROC_UNK6, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 54;
            }
            break;

        case 54:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 8);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGFREE+sys->unk3D, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESSNUM(MESS_SYSHELP, 0x21), MDMESS_WIN_LIST_END);
                star->motNext = 2;
                sys->subMode = 3;
            }
            break;
    }
}
/* 416 insns */
/* twins: MdPartyFlowBonusSel / MdPartyFlowPackSel. Mini-Game Match "wins needed" select
 * (sys->unk45: 0/1/2 = MGMATCH_MODE_3/5/7), MdFlowTbl[4]; B -> mode select, A -> flow 5. */
void fn_1_6FB8(void)
{
    BOOL result;
    MDMESS_WORK *mess;
    MDMINI_STAR *star;
    MDMODEL_WORK *model;

    MDMINI_CHR *chr;

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    chr = &sys->chr[0];

    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            sys->unk45 = 0;
            Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_TURN], sys->unk45);
            sys->subMode = 1;
            break;

        case 1:
            result = MdProcCall(MDMINI_PROC_UNK7, 0);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            result = MdProcCall(MDMINI_PROC_CURSOR, 12);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2; /* mdparty MDPARTY_STAR_MOT_TALK */
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGMATCH_MODE_3+sys->unk45, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                sys->subMode = 3;
            }
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk45 == -1) {
                        sys->unk45 = 2;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk45 = ++sys->unk45 % 3;
                    sys->cursorDir = 1;
                }
                Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_TURN], sys->unk45);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MGMATCH_MODE_3+sys->unk45, MDMESS_WIN_LIST_END);
                fn_1_17008(2);
                sys->subMode = 4;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                star->motNext = 3; /* mdparty MDPARTY_STAR_MOT_IDLE */
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_17008(5);
                sys->subMode = 5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_17008(3);
                sys->subMode = 8;
            }
            break;

        case 4:
            result = MdProcCall(MDMINI_PROC_UNK7, 1);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 5:
            result = MdProcCall(MDMINI_PROC_CURSOR, 13);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 6;
            }
            break;

        case 6:
            result = MdProcCall(MDMINI_PROC_UNK7, 2);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 7;
            }
            break;

        case 7:
            result = MdProcCall(MDMINI_PROC_UNK6, 4);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
                sys->flowMode = MDMINI_FLOW_MODE_SEL;
            }
            break;

        case 8:
            result = MdProcCall(MDMINI_PROC_CURSOR, 13);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 9;
            }
            break;

        case 9:
            result = MdProcCall(MDMINI_PROC_UNK7, 3);
            if(result == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDMINI_FLOW_UNK5;
            }
            break;
    }
}
/* 746 insns */
void fn_1_7638(void)
{
    int ret;
    MDMESS_WORK *mess;
    MDMINI_STAR *star;
    int i;
    MDMODEL_WORK *model;
    MDMINI_PLAYERSPR *playerSpr;
    MDMINI_CHR *chr;

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            sys->unk46 = 0;
            Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_BONUS], sys->unk46);
            sys->subMode = 1;
            break;

        case 1:
            ret = MdProcCall(MDMINI_PROC_UNK8, 0);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 16);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_GENRE_SEL, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                sys->subMode = 3;
            }
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk46 == -1) {
                        sys->unk46 = 2;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk46 = (++sys->unk46)%3;
                    sys->cursorDir = 1;
                }
                Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_BONUS], sys->unk46);
                fn_1_17008(2);
                sys->subMode = 4;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_17008(5);
                sys->subMode = 5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_17008(3);
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 2;
                MdProcWait(MDMINI_PROC_CURSOR, 17);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdProcWait(MDMINI_PROC_UNK8, 3);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDMINI_FLOW_UNK6;
            }
            break;

        case 4:
            ret = MdProcCall(MDMINI_PROC_UNK8, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 5:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 17);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 6;
            }
            break;

        case 6:
            ret = MdProcCall(MDMINI_PROC_UNK8, 2);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 7;
            }
            break;

        case 7:
            ret = MdProcCall(MDMINI_PROC_UNK7, 4);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
                sys->flowMode = MDMINI_FLOW_UNK4;
            }
            break;

        case 8:
            ret = MdProcCall(MDMINI_PROC_CURSOR, 17);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 9;
            }
            break;

        case 9:
            ret = MdProcCall(MDMINI_PROC_UNK8, 3);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_CONFIRM, MDMESS_WIN_LIST_END);
                fn_1_17008(12);
                sys->subMode = 10;
            }
            break;

        case 10:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_MGMODE_SYS_RESET, MDMESS_WIN_LIST_END);
                    sys->subMode = 11;
                } else if(ret == 0) {
                    sys->loadState = MD_LOAD_STATE_WAIT;
                    sys->loadDir = lbl_1_data_160[sys->unk3D];
                    fn_1_16978();
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_MGMODE_SYS_MG_START, MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    MdProcWait(MDMINI_PROC_UNK13, 0);
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 55);
                    fn_1_17008(1);
                    fn_1_17008(10);
                    HuPrcVSleep();
                    while(WipeCheckEnd() != FALSE) {
                        MdProcCall(MDMINI_PROC_UNK13, 0);
                        HuPrcVSleep();
                    }
                    while(sys->loadState != MD_LOAD_STATE_LOAD) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                    sys->nextDll = lbl_1_data_148[sys->unk3D];
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            }
            break;

        case 11:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->motNext = 3;
                    sys->subMode = 13;
                } else if(ret == 0) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->mode = 11;
                    star->motNext = 2;
                    for(i=0; i<4; i++) {
                        sys->chrSelEnd[i] = FALSE;
                        playerSpr[i].mode = 4;
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                        chr[sys->chrSel[i]].mode = 3;
                        MdRingModeSet(i, 4);
                    }
                    sys->subMode = 12;
                }
            }
            break;

        case 12:
            ret = MdProcCall(MDMINI_PROC_UNK10, 1);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                fn_1_14C2C();
                sys->prevPlayerNum = sys->playerNum;
                sys->subMode = 6;
                sys->flowMode = MDMINI_FLOW_PLAYER_NUM_SEL;
            }
            break;

        case 13:
            ret = MdProcCall(MDMINI_PROC_UNK8, 4);
            if(ret == TRUE) {
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;
    }
}

/* 1357 insns: Minigame Mode team / confirm flow (MdFlowTbl[6]). subMode 0 = enter from the
 * mode menu, 1 = 2-vs-2 team pick (teamOrderNo), 2 = 1-vs-3 pick (unk59), 3 = start confirmation. */
void fn_1_81E0(void)
{
    int i; //r31
    MDMESS_WORK *mess; //r30
    MDMINI_STAR *star; //r29
    MDMODEL_WORK *model; //r28
    int choice; //r27
    MDMINI_PLAYERSPR *playerSpr; //r26
    MDMINI_CHR *chr; //r25

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDMINI_PROC_RESET, 0);
            if(sys->unk46 == 0) {
                MdProcWait(MDMINI_PROC_UNK11, 0);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            } else if(sys->unk46 == 2) {
                sys->teamOrderNo = 0;
                fn_1_15DE8();
                fn_1_16168();
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD001A /* MESS_MGMODE_SYS_TEAM_SEL */, MDMESS_WIN_LIST_END);
                for(i=0; i<4; i++) {
                    if(sys->teamOrder[i] < 2) {
                        MdRingModeSet(i, 9);
                    } else {
                        MdRingModeSet(i, 11);
                    }
                }
                MdProcWait(MDMINI_PROC_CHR, 5);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                MdProcWait(MDMINI_PROC_CURSOR, 20);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 1;
            } else if(sys->unk46 == 1) {
                sys->unk59 = 0;
                fn_1_161B8();
                fn_1_16308();
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD001A /* MESS_MGMODE_SYS_TEAM_SEL */, MDMESS_WIN_LIST_END);
                for(i=0; i<4; i++) {
                    if(sys->unk5A[i] < 1) {
                        MdRingModeSet(i, 9);
                    } else {
                        MdRingModeSet(i, 11);
                    }
                }
                MdProcWait(MDMINI_PROC_CHR, 8);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                MdProcWait(MDMINI_PROC_CURSOR, 20);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 1:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->teamOrderNo == -1) {
                        sys->teamOrderNo = 2;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->teamOrderNo = (++sys->teamOrderNo)%3;
                    sys->cursorDir = 1;
                }
                fn_1_17008(2);
                fn_1_16168();
                fn_1_15DE8();
                for(i=0; i<4; i++) {
                    if(sys->teamOrder[i] < 2) {
                        MdRingModeSet(i, 9);
                    } else {
                        MdRingModeSet(i, 11);
                    }
                }
                MdProcWait(MDMINI_PROC_CHR, 7);
                MdProcCall(MDMINI_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_17008(5);
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 3;
                MdProcWait(MDMINI_PROC_CURSOR, 21);
                MdProcCall(MDMINI_PROC_RESET, 0);
                for(i=0; i<4; i++) {
                    MdRingModeSet(i, 13);
                }
                MdProcWait(MDMINI_PROC_CHR, 6);
                MdProcCall(MDMINI_PROC_RESET, 0);
                Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_BONUS], sys->unk46);
                MdProcWait(MDMINI_PROC_UNK8, 4);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD0016 /* MESS_MGMODE_SYS_GENRE_SEL */, MDMESS_WIN_LIST_END);
                star->motNext = 2;
                MdProcWait(MDMINI_PROC_CURSOR, 16);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                sys->subMode = 3;
                sys->flowMode = MDMINI_FLOW_UNK5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_17008(3);
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 3;
                MdProcWait(MDMINI_PROC_CURSOR, 21);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdProcWait(MDMINI_PROC_UNK11, 0);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 2:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk59 == -1) {
                        sys->unk59 = 3;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk59 = (++sys->unk59)%4;
                    sys->cursorDir = 1;
                }
                fn_1_17008(2);
                fn_1_16308();
                fn_1_161B8();
                for(i=0; i<4; i++) {
                    if(sys->unk5A[i] < 1) {
                        MdRingModeSet(i, 9);
                    } else {
                        MdRingModeSet(i, 11);
                    }
                }
                MdProcWait(MDMINI_PROC_CHR, 10);
                MdProcCall(MDMINI_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_17008(5);
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 3;
                MdProcWait(MDMINI_PROC_CURSOR, 21);
                MdProcCall(MDMINI_PROC_RESET, 0);
                for(i=0; i<4; i++) {
                    MdRingModeSet(i, 13);
                }
                MdProcWait(MDMINI_PROC_CHR, 9);
                MdProcCall(MDMINI_PROC_RESET, 0);
                Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_CAP_BONUS], sys->unk46);
                MdProcWait(MDMINI_PROC_UNK8, 4);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD0016 /* MESS_MGMODE_SYS_GENRE_SEL */, MDMESS_WIN_LIST_END);
                star->motNext = 2;
                MdProcWait(MDMINI_PROC_CURSOR, 16);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                sys->subMode = 3;
                sys->flowMode = MDMINI_FLOW_UNK5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_17008(3);
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                star->motNext = 3;
                MdProcWait(MDMINI_PROC_CURSOR, 21);
                MdProcCall(MDMINI_PROC_RESET, 0);
                MdProcWait(MDMINI_PROC_UNK11, 0);
                MdProcCall(MDMINI_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 3:
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, 0xD0017 /* MESS_MGMODE_SYS_CONFIRM */, MDMESS_WIN_LIST_END);
            fn_1_17008(12);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
            if(choice == -1 || choice == 1) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, 0xD0018 /* MESS_MGMODE_SYS_RESET */, MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1 || choice == 1) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    if(sys->unk46 == 0) {
                        MdProcWait(MDMINI_PROC_UNK11, 1);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        MdProcWait(MDMINI_PROC_UNK8, 4);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD0016 /* MESS_MGMODE_SYS_GENRE_SEL */, MDMESS_WIN_LIST_END);
                        star->motNext = 2;
                        MdProcWait(MDMINI_PROC_CURSOR, 16);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                        sys->subMode = 3;
                        sys->flowMode = MDMINI_FLOW_UNK5;
                    } else if(sys->unk46 == 2) {
                        MdProcWait(MDMINI_PROC_UNK11, 1);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        star->motNext = 2;
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD001A /* MESS_MGMODE_SYS_TEAM_SEL */, MDMESS_WIN_LIST_END);
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                        MdProcWait(MDMINI_PROC_CURSOR, 20);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        sys->subMode = 1;
                    } else if(sys->unk46 == 1) {
                        MdProcWait(MDMINI_PROC_UNK11, 1);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        star->motNext = 2;
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD001A /* MESS_MGMODE_SYS_TEAM_SEL */, MDMESS_WIN_LIST_END);
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, 0x20004 /* MESS_SYSHELP_MENU_SEL */, MDMESS_WIN_LIST_END);
                        MdProcWait(MDMINI_PROC_CURSOR, 20);
                        MdProcCall(MDMINI_PROC_RESET, 0);
                        sys->subMode = 2;
                    }
                } else if(choice == 0) {
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->mode = 11;
                    star->motNext = 2;
                    for(i=0; i<4; i++) {
                        sys->chrSelEnd[i] = FALSE;
                        playerSpr[i].mode = 4;
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*2)+MDMODEL_MOT_MARIO_IDLE], 0, 16, HU3D_MOTATTR_LOOP);
                        chr[sys->chrSel[i]].mode = 3;
                        MdRingModeSet(i, 4);
                    }
                    MdProcWait(MDMINI_PROC_UNK10, 1);
                    MdProcCall(MDMINI_PROC_RESET, 0);
                    fn_1_14C2C();
                    sys->prevPlayerNum = sys->playerNum;
                    sys->subMode = 6;
                    sys->flowMode = MDMINI_FLOW_PLAYER_NUM_SEL;
                }
            } else if(choice == 0) {
                sys->loadState = 2;
                sys->loadDir = lbl_1_data_160[sys->unk3D];
                fn_1_16978();
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, 0xD0019 /* MESS_MGMODE_SYS_MG_START */, MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdProcWait(MDMINI_PROC_UNK13, 0);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 55);
                fn_1_17008(1);
                fn_1_17008(10);
                HuPrcVSleep();
                while(WipeCheckEnd()) {
                    MdProcCall(MDMINI_PROC_UNK13, 0);
                    HuPrcVSleep();
                }
                while(sys->loadState != 4) {
                    HuPrcVSleep();
                }
                omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                sys->ovlCallMode = MD_OVLCALL_CALL;
                sys->nextDll = lbl_1_data_148[sys->unk3D];
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;
    }
}

/* 130 insns */
/* twin: MdPartyProcReset */
BOOL fn_1_9714(int param)
{
    sys->dirtyF = FALSE;
    sys->cursorInitF = FALSE;
    sys->winInitF = FALSE;
    sys->unk3D8 = FALSE;
    sys->nameInitF = FALSE;
    sys->unk3E0 = FALSE;
    sys->procTime = 0.0f;
    sys->procOfsTime = 0.0f;
    sys->cameraTime = 0.0f;
    sys->cameraTotalTime = 0.0f;
    sys->sprTime = 0.0f;
    sys->unk400 = 0.0f;
    sys->nameTime = 0.0f;
    sys->procT = 0.0f;
    sys->procOfsT = 0.0f;
    sys->cameraT = 0.0f;
    sys->cameraTotalT = 0.0f;
    sys->sprT = 0.0f;
    sys->unk41C = 0.0f;
    sys->nameT = 0.0f;
    return FALSE;
}

/* 0x724 */ MDMINI_LERP_DATA lbl_1_data_724[1] = { /* fn_1_991C; mdparty ProcCamera lerpData */
    { { 90.0f, 0.0f, 1920.0f }, { 0.0f, 0.0f, 0.0f }, { 90.0f, 0.0f, 500.0f }, { 0.0f, 150.0f, 0.0f }, 1, 60.0f }
};

/* 107 insns */
/* twin: MdPartyProcCamera; lbl_1_data_724 = lerpData */
BOOL fn_1_991C(int param)
{
    MDMINI_LERP_DATA *lerpP;
    MDCAMERA_WORK *cameraWork;
    MDCAMERA *camera;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[MDCAMERA_MAIN];
    lerpP = &lbl_1_data_724[param];
    MdMathOscillate(lerpP->type, &sys->cameraTime, &sys->cameraT, lerpP->step);
    MdMathOscillate(MDMATH_OSC_180, &sys->cameraTotalTime, &sys->cameraTotalT, lerpP->step);
    MdMathLerp(&camera->hvr.x, lerpP->hvrA.x, lerpP->hvrB.x, sys->cameraT);
    MdMathLerp(&camera->hvr.y, lerpP->hvrA.y, lerpP->hvrB.y, sys->cameraT);
    MdMathLerp(&camera->hvr.z, lerpP->hvrA.z, lerpP->hvrB.z, sys->cameraT);
    MdMathLerp(&camera->center.x, lerpP->centerA.x, lerpP->centerB.x, sys->cameraT);
    MdMathLerp(&camera->center.y, lerpP->centerA.y, lerpP->centerB.y, sys->cameraT);
    MdMathLerp(&camera->center.z, lerpP->centerA.z, lerpP->centerB.z, sys->cameraT);
    /* retail reads procTime (0x3EC) here, not the twin's cameraTotalTime: transcribed as is */
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 1307 insns: the left/right cursor arrows (sprite group CURSOR_UDLR members R, L, GLOW_R, GLOW_L).
 * param = mode*4 + action: action 0 = slide in, 1 = slide out, 2 = pulse right, 3 = pulse left;
 * mode 0 = player-number select, 1 = COM difficulty (on the COM's character), 2 = submode select,
 * 3 = CAP_WIN capsule, 4 = CAP_GENRE capsule, 5 = team select. Owns lbl_1_bss_36C (the four
 * cursor end points: R hidden/shown, L hidden/shown). Returns TRUE when the animation is done. */
BOOL fn_1_9AC8(int param)
{
    HuVec2f *sprScale; //r30
    HuVec2f *sprPos; //r29
    MDSPRITE_WORK *sprite; //r28
    MDCAMERA_WORK *camera; //r27
    HUSPRGRPID grpId; //r26
    MDMODEL_WORK *model; //r25

    HuVecF pos2D; //sp+0x14
    HuVecF pos3D; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_UDLR];
    if(!sys->cursorInitF) {
        if(param >= 0 && param <= 3) {
            pos3D.x = 0;
            pos3D.y = 176.8f;
            pos3D.z = -580.0f;
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-192;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = 192+pos2D.x;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        } else if(param >= 4 && param <= 7) {
            pos3D = *model->posP[sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDMODEL_CAP_CHR_00];
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            pos2D.y -= 44.0f;
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-46;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = (46+pos2D.x)-3;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        } else if(param >= 8 && param <= 11) {
            pos3D.x = 0;
            pos3D.y = 180.0f;
            pos3D.z = -200.0f;
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-96;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = 96+pos2D.x;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        } else if(param >= 12 && param <= 15) {
            pos3D = *model->posP[MDMODEL_CAP_WIN];
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-80;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = 80+pos2D.x;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        } else if(param >= 16 && param <= 19) {
            pos3D = *model->posP[MDMODEL_CAP_GENRE];
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-80;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = 80+pos2D.x;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        } else if(param >= 20 && param <= 23) {
            pos3D.x = -460.0f;
            pos3D.y = 120.0f;
            pos3D.z = -600.0f;
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[0].x = -64.0f;
            lbl_1_bss_36C[0].y = pos2D.y;
            lbl_1_bss_36C[0].z = 0;
            lbl_1_bss_36C[1].x = pos2D.x-64;
            lbl_1_bss_36C[1].y = pos2D.y;
            lbl_1_bss_36C[1].z = 0;
            pos3D.x = 460.0f;
            pos3D.y = 120.0f;
            pos3D.z = -600.0f;
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
            lbl_1_bss_36C[2].x = 640.0f;
            lbl_1_bss_36C[2].y = pos2D.y;
            lbl_1_bss_36C[2].z = 0;
            lbl_1_bss_36C[3].x = 64+pos2D.x;
            lbl_1_bss_36C[3].y = pos2D.y;
            lbl_1_bss_36C[3].z = 0;
        }
        if(param == 0 || param == 4 || param == 8 || param == 12 || param == 16 || param == 20) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos->x = lbl_1_bss_36C[0].x;
            sprPos->y = lbl_1_bss_36C[0].y;
            if(param == 4) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprPos->x = lbl_1_bss_36C[2].x;
            sprPos->y = lbl_1_bss_36C[2].y;
            if(param == 4) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        } else if(param == 2 || param == 6 || param == 10 || param == 14 || param == 18 || param == 22) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
            sprPos->x = lbl_1_bss_36C[1].x;
            sprPos->y = lbl_1_bss_36C[1].y;
            if(param == 6) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), 0.0f);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3 || param == 7 || param == 11 || param == 15 || param == 19 || param == 23) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
            sprPos->x = lbl_1_bss_36C[3].x;
            sprPos->y = lbl_1_bss_36C[3].y;
            if(param == 7) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), 0.0f);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        sys->cursorInitF = TRUE;
    }
    if(param == 0 || param == 4 || param == 8 || param == 12 || param == 16 || param == 20) {
        MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[0].x, lbl_1_bss_36C[1].x, sys->sprT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[2].x, lbl_1_bss_36C[3].x, sys->sprT);
    } else if(param == 1 || param == 5 || param == 9 || param == 13 || param == 17 || param == 21) {
        MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[1].x, lbl_1_bss_36C[0].x, sys->sprT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[3].x, lbl_1_bss_36C[2].x, sys->sprT);
    } else if(param == 2 || param == 6 || param == 10 || param == 14 || param == 18 || param == 22) {
        MdMathOscillate(MDMATH_OSC_180, &sys->sprTime, &sys->sprT, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[1].x, lbl_1_bss_36C[1].x-24.0f, sys->sprT);
        if(param == 6) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->sprT);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->sprT);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->sprT);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->sprT);
        }
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[1].x, lbl_1_bss_36C[1].x-24.0f, sys->sprT);
        MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->sprT);
        MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->sprT);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), sys->sprT);
    } else if(param == 3 || param == 7 || param == 11 || param == 15 || param == 19 || param == 23) {
        MdMathOscillate(MDMATH_OSC_180, &sys->sprTime, &sys->sprT, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[3].x, 24.0f+lbl_1_bss_36C[3].x, sys->sprT);
        if(param == 7) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->sprT);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->sprT);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->sprT);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->sprT);
        }
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_36C[3].x, 24.0f+lbl_1_bss_36C[3].x, sys->sprT);
        MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->sprT);
        MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->sprT);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), sys->sprT);
    }
    if(sys->sprTime >= 1.0f) {
        if(param == 1 || param == 5 || param == 9 || param == 13 || param == 17 || param == 21) {
            MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
        } else if(param == 2 || param == 6 || param == 10 || param == 14 || param == 18 || param == 22) {
            HuSprDispOff(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3 || param == 7 || param == 11 || param == 15 || param == 19 || param == 23) {
            HuSprDispOff(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 461 insns */
/* twin: MdPartyProcWin / MdSelProcWinUpdate; lbl_1_bss_368 = lbl_1_bss_368, 364 lbl_1_bss_364, 360 lbl_1_bss_360, 35C lbl_1_bss_35C */
BOOL fn_1_AF34(int param)
{
    MDSPRITE_WORK *sprite; //r31
    HuVec2f *bgScale; //r30
    HuVec2f *topPos; //r29
    HuVec2f *bottomPos; //r28
    HuVec2f *topScale; //r27
    HuVec2f *bottomScale; //r26
    
    HuVec2f *bgPos; //sp+0xC
    HUSPRGRPID grpId; //sp+0x8
    
    
    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_WIN];
    topPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_TOP));
    bottomPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_BOTTOM));
    bgPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_BG));
    topScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_TOP));
    bottomScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_BOTTOM));
    bgScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_BG));
    if(!sys->winInitF) {
        lbl_1_bss_368 = 0;
        lbl_1_bss_364 = topPos->y;
        lbl_1_bss_360 = bottomPos->y;
        lbl_1_bss_35C = bgScale->y;
        if(param == FALSE) {
            topPos->y = 0;
            bottomPos->y = 0;
            topScale->x = 0;
            bottomScale->x = 0;
            bgScale->x = 0;
            bgScale->y = 0;
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, TRUE);
        }
        sys->winInitF = TRUE;
    }
    if(param == FALSE) {
        if(lbl_1_bss_368 == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, 0, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, 0, 2, sys->sprT);
            MdMathLerp(&topScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bottomScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bgScale->x, 0, 1, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_368 = 1;
            }
        } else if(lbl_1_bss_368 == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, -2, -28, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 32, sys->sprT);
            MdMathLerp(&bgScale->y, 0, 8, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_368 = 2;
            }
        }
    } else if(param == TRUE) {
        if(lbl_1_bss_368 == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, lbl_1_bss_364, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, lbl_1_bss_360, 2, sys->sprT);
            MdMathLerp(&bgScale->y, lbl_1_bss_35C, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_368 = 1;
            }
            
        } else if(lbl_1_bss_368 == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, -2, 0, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 0, sys->sprT);
            MdMathLerp(&topScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bottomScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bgScale->x, 1, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_368 = 2;
            }
        }
    }
    if(lbl_1_bss_368 == 2) {
        if(param == TRUE) {
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}


/* 0x75C */ HuVecF lbl_1_data_75C = { 0.0f, 0.0f, 0.0f }; /* fn_1_B668; mdparty ProcCapPlayer centerPos */
/* 0x768 */ HuVecF lbl_1_data_768[4] = { 0 }; /* fn_1_B668; mdparty ProcCapPlayer playerPos */

/* 1171 insns */
/* twin: MdPartyProcCapPlayer. lbl_1_data_75C = lbl_1_data_75C, 768 lbl_1_data_768; lbl_1_bss_350 lbl_1_bss_350,
 * 320 lbl_1_bss_320, 318 lbl_1_bss_318, 314 lbl_1_bss_314, 310 lbl_1_bss_310, 2E0 lbl_1_bss_2E0; lbl_1_bss_0 = lbl_1_bss_0 */
BOOL fn_1_B668(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    MDCAMERA_WORK *camera; //r28
    
    HuVecF *posP[4][2]; //sp+0x48
    HuVecF *rotP[4][2]; //sp+0x28
    HuVecF *scaleP[4][2]; //sp+0x8
    
    
    model = sys->model;
    
    camera = sys->camera;
    if(!lbl_1_bss_0) {
        lbl_1_data_75C.x = 288;
        lbl_1_data_75C.y = 176.64f;
        lbl_1_data_75C.z = 4000.0f;
        for(i=0; i<4; i++) {
            lbl_1_data_768[i].x = 168.0f+(i*80.0f);
            lbl_1_data_768[i].y = lbl_1_data_75C.y;
            lbl_1_data_768[i].z = 2500;
        }
        lbl_1_bss_0 = TRUE;
    }
    for(i=0; i<4; i++) {
        posP[i][0] = model->posP[i+MDMODEL_CAP_MAN_1P];
        posP[i][1] = model->posP[i+MDMODEL_CAP_COM_1P];
        
        rotP[i][0] = model->rotP[i+MDMODEL_CAP_MAN_1P];
        rotP[i][1] = model->rotP[i+MDMODEL_CAP_COM_1P];
        
        scaleP[i][0] = model->scaleP[i+MDMODEL_CAP_MAN_1P];
        scaleP[i][1] = model->scaleP[i+MDMODEL_CAP_COM_1P];
    }
    if(!sys->dirtyF) {
        for(i=0; i<4; i++) {
            if(i < sys->playerNum+1) {
                lbl_1_bss_318[i][0] = 0;
            } else {
                lbl_1_bss_318[i][0] = 1;
            }
            if(i < sys->prevPlayerNum+1) {
                lbl_1_bss_318[i][1] = 0;
            } else {
                lbl_1_bss_318[i][1] = 1;
            }
        }
        if(param == 0) {
            Hu3D2Dto3D(&lbl_1_data_75C, camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_350);
            for(i=0; i<4; i++) {
                Hu3D2Dto3D(&lbl_1_data_768[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_320[i]);
            }
            for(i=0; i<4; i++) {
                posP[i][lbl_1_bss_318[i][0]]->x = lbl_1_bss_350.x;
                posP[i][lbl_1_bss_318[i][0]]->y = lbl_1_bss_350.y;
                posP[i][lbl_1_bss_318[i][0]]->z = lbl_1_bss_350.z;
                rotP[i][lbl_1_bss_318[i][0]]->x = 0;
                rotP[i][lbl_1_bss_318[i][0]]->y = 0;
                rotP[i][lbl_1_bss_318[i][0]]->z = 0;
                scaleP[i][lbl_1_bss_318[i][0]]->x = 0;
                scaleP[i][lbl_1_bss_318[i][0]]->y = 0;
                scaleP[i][lbl_1_bss_318[i][0]]->z = 0;
                if(lbl_1_bss_318[i][0] == 0) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                } else if(lbl_1_bss_318[i][0] == 1) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                }
            }
            fn_1_17008(7); /* SE (mdparty AUD cmd 7 is SE_BOARD_START; mdmini's cmd table unnamed) */
        } else if(param != 1 && (param == 2 || param == 3)) {
            for(i=0; i<4; i++) {
                if(lbl_1_bss_318[i][0] != lbl_1_bss_318[i][1]) {
                    posP[i][lbl_1_bss_318[i][1]]->x = lbl_1_bss_350.x;
                    posP[i][lbl_1_bss_318[i][1]]->y = lbl_1_bss_350.y;
                    posP[i][lbl_1_bss_318[i][1]]->z = lbl_1_bss_350.z;
                    rotP[i][lbl_1_bss_318[i][1]]->x = 0;
                    rotP[i][lbl_1_bss_318[i][1]]->y = 0;
                    rotP[i][lbl_1_bss_318[i][1]]->z = 0;
                    scaleP[i][lbl_1_bss_318[i][1]]->x = 0;
                    scaleP[i][lbl_1_bss_318[i][1]]->y = 0;
                    scaleP[i][lbl_1_bss_318[i][1]]->z = 0;
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_318[i][0]*4)]);
                }
            }
            lbl_1_bss_314 = 200;
            lbl_1_bss_310 = 90;
            for(i=0; i<4; i++) {
                lbl_1_bss_2E0[i] = lbl_1_bss_320[i];
                lbl_1_bss_2E0[i].z -= lbl_1_bss_314;
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        for(i=0; i<4; i++) {
            MdMathLerp(&posP[i][lbl_1_bss_318[i][0]]->x, lbl_1_bss_350.x, lbl_1_bss_320[i].x, sys->procT);
            MdMathLerp(&posP[i][lbl_1_bss_318[i][0]]->y, lbl_1_bss_350.y, lbl_1_bss_320[i].y, sys->procT);
            MdMathLerp(&posP[i][lbl_1_bss_318[i][0]]->z, lbl_1_bss_350.z, lbl_1_bss_320[i].z, sys->procT);
            MdMathLerpScale(scaleP[i][lbl_1_bss_318[i][0]], 0, 1, sys->procT);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        for(i=0; i<4; i++) {
            MdMathLerpScale(scaleP[i][lbl_1_bss_318[i][0]], 1, 0, sys->procT);
        }
    } else if(param == 2 || param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 20);
        if(param == 2) {
            MdMathLerp(&lbl_1_bss_310, 90, 270, sys->procT);
        } else if(param == 3) {
            MdMathLerp(&lbl_1_bss_310, 90, -90, sys->procT);
        }
        for(i=0; i<4; i++) {
            if(lbl_1_bss_318[i][0] != lbl_1_bss_318[i][1]) {
                MdMathLerpScale(scaleP[i][lbl_1_bss_318[i][1]], 1, 0, sys->procT);
                posP[i][lbl_1_bss_318[i][1]]->x = lbl_1_bss_2E0[i].x+(lbl_1_bss_314*HuCos(lbl_1_bss_310));
                posP[i][lbl_1_bss_318[i][1]]->y = lbl_1_bss_2E0[i].y;
                posP[i][lbl_1_bss_318[i][1]]->z = lbl_1_bss_2E0[i].z+(lbl_1_bss_314*HuSin(lbl_1_bss_310));
                MdMathLerpScale(scaleP[i][lbl_1_bss_318[i][0]], 0, 1, sys->procT);
                posP[i][lbl_1_bss_318[i][0]]->x = lbl_1_bss_2E0[i].x+(lbl_1_bss_314*HuCos(180.0f+lbl_1_bss_310));
                posP[i][lbl_1_bss_318[i][0]]->y = lbl_1_bss_2E0[i].y;
                posP[i][lbl_1_bss_318[i][0]]->z = lbl_1_bss_2E0[i].z+(lbl_1_bss_314*HuSin(180.0f+lbl_1_bss_310));
            }
        }
        if(sys->maxPlayerNum > 1) {
            MdProcCall(MDMINI_PROC_CURSOR, param);
        }
    }
    for(i=0; i<4; i++) {
        fn_1_15CF8(i+MDMODEL_CAP_MAN_1P, MDCAMERA_FG);
        fn_1_15CF8(i+MDMODEL_CAP_COM_1P, MDCAMERA_FG);
    }
    if(sys->procTime >= 1) {
        if(param != 0) {
            if(param == 1) {
                for(i=0; i<4; i++) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_318[i][0]*4)]);
                }
            } else if(param == 2 || param == 3) {
                for(i=0; i<4; i++) {
                    if(lbl_1_bss_318[i][0] != lbl_1_bss_318[i][1]) {
                        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_318[i][1]*4)]);
                    }
                }
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x798 */ HuVecF lbl_1_data_798 = { 0.0f, 0.0f, -1000.0f }; /* fn_1_C8B4; mdparty ProcChr centerPos */
/* 0x7A4 */ HuVecF lbl_1_data_7A4[10] = { { -440.0f, 400.0f, -600.0f }, { -220.0f, 400.0f, -600.0f }, { 0.0f, 400.0f, -600.0f }, { 220.0f, 400.0f, -600.0f }, { 440.0f, 400.0f, -600.0f }, { -440.0f, 130.0f, -600.0f }, { -220.0f, 130.0f, -600.0f }, { 0.0f, 130.0f, -600.0f }, { 220.0f, 130.0f, -600.0f }, { 440.0f, 130.0f, -600.0f } };
/* 0x81C */ HuVecF lbl_1_data_81C[4] = { { -360.0f, -160.0f, 250.0f }, { -120.0f, -160.0f, 500.0f }, { 120.0f, -160.0f, 750.0f }, { 360.0f, -160.0f, 1000.0f } };
/* 0x84C */ HuVecF lbl_1_data_84C[4] = { { -460.0f, 120.0f, -600.0f }, { -220.0f, 120.0f, -600.0f }, { 220.0f, 120.0f, -600.0f }, { 460.0f, 120.0f, -600.0f } };
/* 0x87C */ HuVec2f lbl_1_data_87C[4] = { { -130.0f, -900.0f }, { 260.0f, -1100.0f }, { -30.0f, 900.0f }, { 80.0f, 1100.0f } }; /* fn_1_C8B4; mdparty cursorTeamPos */
/* 0x89C */ HuVecF lbl_1_data_89C[4] = { { -460.0f, 120.0f, -600.0f }, { -20.0f, 120.0f, -600.0f }, { 220.0f, 120.0f, -600.0f }, { 460.0f, 120.0f, -600.0f } };

/* 1766 insns. twin: mdparty MdPartyProcChr. Data: lbl_1_data_798 centerPos, 7A4 chrPos[10],
 * 81C playerPos[4], 84C/89C team positions (indexed by teamOrder / unk5A), 87C cursorTeamPos. */
BOOL fn_1_C8B4(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *posP; //r29
    HuVecF *scaleP; //r28
    HuVecF *rotP; //r26
    MDMINI_STAR *star; //r25

    MDCAMERA_WORK *camera; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    star = sys->star;
    if(!sys->dirtyF) {
        if(param == 0) {
            for(i=0; i<10; i++) {
                posP = model->posP[i+MDMODEL_CAP_CHR_00];
                rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
                scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
                *posP = lbl_1_data_798;
                scaleP->x = 0;
                scaleP->y = 0;
                scaleP->z = 0;
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_CHR_00]);
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO]);
            }
            Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE_CHR]);
            Hu3DLayerHookSet(1+HU3D_LAYER_HOOK_POST, MdToueiLayerHook);
            fn_1_17008(7);
        } else if(param != 1) {
            if(param == 2) {
                star->mode = 7; /* mdparty MDPARTY_STAR_MOVE_LEFT_START */
                fn_1_17008(7);
            } else if(param == 3) {
                star->mode = 11; /* mdparty MDPARTY_STAR_CENTER_START */
                fn_1_17008(7);
            } else if(param == 4) {
                for(i=0; i<4; i++) {
                    posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                    rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                    scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                    *posP = lbl_1_data_81C[i];
                    posP->z = lbl_1_data_7A4[sys->chrSel[i]].z;
                    scaleP->x = 1;
                    scaleP->y = 1;
                    scaleP->z = 0.1f;
                    Hu3DModelDispOn(model->mdlId[sys->chrSel[i]+MDMODEL_CAP_CHR_00]);
                    Hu3DModelDispOn(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO]);
                }
                for(i=0; i<10; i++) {
                    posP = model->posP[i+MDMODEL_CAP_CHR_00];
                    rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
                    scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
                    if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                        *posP = lbl_1_data_7A4[i];
                        scaleP->x = 0;
                        scaleP->y = 0;
                        scaleP->z = 0;
                        Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_CHR_00]);
                        Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO]);
                    }
                }
                Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE_CHR]);
                Hu3DLayerHookSet(1+HU3D_LAYER_HOOK_POST, MdToueiLayerHook);
                sys->procTime = 1.0f;
            } else if(param == 5) {

            } else if(param == 6) {
                fn_1_17008(7);
            } else if(param == 7) {
                fn_1_17008(7);
            } else if(param == 8) {

            } else if(param == 9) {
                fn_1_17008(7);
            } else if(param == 10) {
                fn_1_17008(7);
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        for(i=0; i<10; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_798.x, lbl_1_data_7A4[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_798.y, lbl_1_data_7A4[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_798.z, lbl_1_data_7A4[i].z, sys->procT);
            MdMathLerp(&scaleP->x, 0, 1, sys->procT);
            MdMathLerp(&scaleP->y, 0, 1, sys->procT);
            MdMathLerp(&scaleP->z, 0, 0.1f, sys->procT);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        for(i=0; i<10; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            MdMathLerp(&scaleP->x, 1, 0, sys->procT);
            MdMathLerp(&scaleP->y, 1, 0, sys->procT);
            MdMathLerp(&scaleP->z, 0.1f, 0, sys->procT);
        }
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_7A4[sys->chrSel[i]].x, lbl_1_data_81C[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_7A4[sys->chrSel[i]].y, lbl_1_data_81C[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_7A4[sys->chrSel[i]].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        for(i=0; i<10; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                MdMathLerp(&scaleP->x, 1, 0, sys->procT);
                MdMathLerp(&scaleP->y, 1, 0, sys->procT);
                MdMathLerp(&scaleP->z, 0.1f, 0, sys->procT);
            }
        }
        fn_1_153D0();
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_81C[i].x, lbl_1_data_7A4[sys->chrSel[i]].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_81C[i].y, lbl_1_data_7A4[sys->chrSel[i]].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_7A4[sys->chrSel[i]].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        for(i=0; i<10; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                MdMathLerp(&scaleP->x, 0, 1, sys->procT);
                MdMathLerp(&scaleP->y, 0, 1, sys->procT);
                MdMathLerp(&scaleP->z, 0.0f, 0.1f, sys->procT);
            }
        }
        fn_1_153D0();
    } else if(param == 4) {

    } else if(param == 5) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_81C[i].x, lbl_1_data_84C[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_81C[i].y, lbl_1_data_84C[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_84C[i].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        MdProcCall(MDMINI_PROC_UNK9, 0);
        fn_1_153D0();
    } else if(param == 6) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_84C[sys->teamOrder[i]].x, lbl_1_data_81C[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_84C[sys->teamOrder[i]].y, lbl_1_data_81C[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_84C[sys->teamOrder[i]].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        MdProcCall(MDMINI_PROC_UNK9, 1);
        fn_1_153D0();
    } else if(param == 7) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15);
        for(i=0; i<4; i++) {
            if(sys->teamOrder[i] != sys->teamOrderBackup[i]) {
                posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                MdMathLerp(&posP->x, lbl_1_data_84C[sys->teamOrderBackup[i]].x, lbl_1_data_84C[sys->teamOrder[i]].x, sys->procT);
                MdMathLerp(&posP->y, lbl_1_data_84C[sys->teamOrderBackup[i]].y, lbl_1_data_87C[sys->teamOrder[i]].x, sys->procOfsT);
                MdMathLerp(&posP->z, -600, lbl_1_data_87C[sys->teamOrder[i]].y, sys->procOfsT);
            }
        }
        fn_1_153D0();
        MdProcCall(MDMINI_PROC_CURSOR, sys->cursorDir+22);
    } else if(param == 8) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_81C[i].x, lbl_1_data_89C[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_81C[i].y, lbl_1_data_89C[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_89C[i].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        MdProcCall(MDMINI_PROC_UNK9, 0);
        fn_1_153D0();
    } else if(param == 9) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<4; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_89C[sys->unk5A[i]].x, lbl_1_data_81C[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_89C[sys->unk5A[i]].y, lbl_1_data_81C[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_89C[sys->unk5A[i]].z, lbl_1_data_81C[i].z, sys->procOfsT);
        }
        MdProcCall(MDMINI_PROC_UNK9, 1);
        fn_1_153D0();
    } else if(param == 10) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15);
        for(i=0; i<4; i++) {
            if(sys->unk5A[i] != sys->unk5E[i]) {
                posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                MdMathLerp(&posP->x, lbl_1_data_89C[sys->unk5E[i]].x, lbl_1_data_89C[sys->unk5A[i]].x, sys->procT);
                MdMathLerp(&posP->y, lbl_1_data_89C[sys->unk5E[i]].y, lbl_1_data_87C[sys->unk5A[i]].x, sys->procOfsT);
                MdMathLerp(&posP->z, -600, lbl_1_data_87C[sys->unk5A[i]].y, sys->procOfsT);
            }
        }
        fn_1_153D0();
        MdProcCall(MDMINI_PROC_CURSOR, sys->cursorDir+22);
    }
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x8CC */ s16 lbl_1_data_8CC[6] = { 30, 40, 50, 0, 10, 20 };
/* 0x8D8 */ float lbl_1_data_8D8[6] = { 90.0f, 30.0f, -30.0f, 270.0f, 210.0f, 150.0f };
/* 0x8F0 */ float lbl_1_data_8F0[6] = { 45.0f, 40.0f, 45.0f, 60.0f, 55.0f, 50.0f };

/* 1182 insns */
BOOL fn_1_E44C(int param)
{
    MDMINI_E44C_REC *starP;
    int i;
    MDMODEL_WORK *model;
    HuVecF *pos;
    HuVecF *scale;
    HuVecF *rot;
    MDCAMERA_WORK *cameraWork;

    cameraWork = sys->camera;
    model = sys->model;
    if(!sys->dirtyF) {
        if(param == 0) {
            lbl_1_bss_184[0].x = 0;
            lbl_1_bss_184[0].y = 0;
            lbl_1_bss_184[0].z = -2000;
            lbl_1_bss_184[1].x = 0;
            lbl_1_bss_184[1].y = 180;
            lbl_1_bss_184[1].z = -200;
            lbl_1_bss_19C = lbl_1_bss_184[0];
            for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
                pos = model->posP[MDMODEL_CAP_MODE_00 + i];
                rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
                scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
                starP->mode = 0;
                starP->wait = lbl_1_data_8CC[i];
                starP->radius = 0;
                starP->angle = -90;
                starP->startAngle = starP->angle;
                starP->endAngle = lbl_1_data_8D8[i];
                starP->oscTime[0] = 0;
                starP->oscTime[1] = 0;
                starP->oscTime[2] = 0;
                starP->oscTime[3] = 0;
                starP->oscT[0] = 0;
                starP->oscT[1] = 0;
                starP->oscT[2] = 0;
                starP->oscT[3] = 0;
                pos->x = lbl_1_bss_19C.x + starP->radius * HuCos(starP->angle);
                pos->y = lbl_1_bss_19C.y;
                pos->z = lbl_1_bss_19C.z + starP->radius * HuSin(starP->angle);
                rot->x = 0;
                rot->y = 0;
                rot->z = 0;
                scale->x = 0;
                scale->y = 0;
                scale->z = 0;
                Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_MODE_00 + i]);
            }
            fn_1_17008(7);
        } else if(param == 1) {
            for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
                starP->mode = 0;
                starP->startAngle = starP->angle;
                if(sys->cursorDir == 0) {
                    starP->endAngle = 60 + starP->angle;
                } else if(sys->cursorDir == 1) {
                    starP->endAngle = starP->angle - 60;
                }
                starP->oscTime[1] = 0;
                starP->oscT[1] = 0;
            }
        } else if(param == 2) {
            for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
                starP->mode = 0;
                starP->oscTime[0] = 0;
                starP->oscTime[1] = 0;
                starP->oscTime[2] = 0;
                starP->oscTime[3] = 0;
                starP->oscT[0] = 0;
                starP->oscT[1] = 0;
                starP->oscT[2] = 0;
                starP->oscT[3] = 0;
            }
        } else if(param == 3) {
            for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
                starP->mode = 0;
                starP->oscTime[0] = 0;
                starP->oscTime[1] = 0;
                starP->oscTime[2] = 0;
                starP->oscTime[3] = 0;
                starP->oscT[0] = 0;
                starP->oscT[1] = 0;
                starP->oscT[2] = 0;
                starP->oscT[3] = 0;
            }
            lbl_1_bss_16C[0] = *model->posP[MDMODEL_CAP_MODE_00 + sys->unk3D];
            lbl_1_bss_16C[1].x = 0;
            lbl_1_bss_16C[1].y = -50;
            lbl_1_bss_16C[1].z = 500;
        } else if(param == 4) {
            for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
                starP->mode = 0;
                starP->oscTime[0] = 0;
                starP->oscTime[1] = 0;
                starP->oscTime[2] = 0;
                starP->oscTime[3] = 0;
                starP->oscT[0] = 0;
                starP->oscT[1] = 0;
                starP->oscT[2] = 0;
                starP->oscT[3] = 0;
                if(i != sys->unk3D) {
                    Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_MODE_00 + i]);
                }
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        MdMathLerp(&lbl_1_bss_19C.x, lbl_1_bss_184[0].x, lbl_1_bss_184[1].x, sys->procT);
        MdMathLerp(&lbl_1_bss_19C.y, lbl_1_bss_184[0].y, lbl_1_bss_184[1].y, sys->procT);
        MdMathLerp(&lbl_1_bss_19C.z, lbl_1_bss_184[0].z, lbl_1_bss_184[1].z, sys->procT);
        for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
            pos = model->posP[MDMODEL_CAP_MODE_00 + i];
            rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
            scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
            switch(starP->mode) {
                case 0:
                    if(--starP->wait <= 0) {
                        starP->wait = 0;
                        starP->mode = 1;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[0], &starP->oscT[0], lbl_1_data_8F0[i]);
                    MdMathLerp(&starP->radius, 0, 300, starP->oscT[0]);
                    MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[1], &starP->oscT[1], lbl_1_data_8F0[i]);
                    MdMathLerp(&starP->angle, starP->startAngle, starP->endAngle, starP->oscT[1]);
                    pos->x = lbl_1_bss_19C.x + starP->radius * HuCos(starP->angle);
                    pos->y = lbl_1_bss_19C.y;
                    pos->z = lbl_1_bss_19C.z + starP->radius * HuSin(starP->angle);
                    MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[3], &starP->oscT[3], lbl_1_data_8F0[i]);
                    if(i == sys->unk3D) {
                        MdMathLerpScale(scale, 0, 1.5f, starP->oscT[3]);
                    } else {
                        MdMathLerpScale(scale, 0, 0.5f, starP->oscT[3]);
                    }
                    if(starP->oscTime[1] >= 1) {
                        MdMathAngleClamp(&starP->angle);
                        starP->mode++;
                    }
                    break;

                case 2:
                    break;
            }
        }
    } else if(param == 1) {
        for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
            pos = model->posP[MDMODEL_CAP_MODE_00 + i];
            rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
            scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
            switch(starP->mode) {
                case 0:
                    MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[1], &starP->oscT[1], 15);
                    MdMathLerp(&starP->angle, starP->startAngle, starP->endAngle, starP->oscT[1]);
                    pos->x = lbl_1_bss_19C.x + starP->radius * HuCos(starP->angle);
                    pos->y = lbl_1_bss_19C.y;
                    pos->z = lbl_1_bss_19C.z + starP->radius * HuSin(starP->angle);
                    if(i == sys->unk3D) {
                        MdMathLerpScale(scale, 0.5f, 1.5f, starP->oscT[1]);
                    } else if(i == sys->unk3E) {
                        MdMathLerpScale(scale, 1.5f, 0.5f, starP->oscT[1]);
                    }
                    if(starP->oscTime[1] >= 1) {
                        MdMathAngleClamp(&starP->angle);
                        starP->mode++;
                    }
                    break;

                case 1:
                    break;
            }
        }
        if(sys->cursorDir == 0) {
            MdProcCall(MDMINI_PROC_CURSOR, 11);
        } else if(sys->cursorDir == 1) {
            MdProcCall(MDMINI_PROC_CURSOR, 10);
        }
    } else if(param == 2) {
        for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
            pos = model->posP[MDMODEL_CAP_MODE_00 + i];
            rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
            scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
            switch(starP->mode) {
                case 0:
                    MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[3], &starP->oscT[3], 15);
                    MdMathLerpScale(scale, 1, 0, starP->oscT[3]);
                    if(starP->oscTime[3] >= 1) {
                        starP->mode++;
                    }
                    break;

                case 1:
                    break;
            }
        }
    } else if(param == 3) {
        for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
            pos = model->posP[MDMODEL_CAP_MODE_00 + i];
            rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
            scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
            if(i == sys->unk3D) {
                switch(starP->mode) {
                    case 0:
                        MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[0], &starP->oscT[0], 15);
                        MdMathOscillate(MDMATH_OSC_180, &starP->oscTime[1], &starP->oscT[1], 15);
                        MdMathLerpScaleOfs(scale, 1.5f, 2, starP->oscT[0], 2 * starP->oscT[1]);
                        if(starP->oscTime[0] >= 1) {
                            starP->mode++;
                        }
                        break;

                    case 1:
                        break;
                }
            } else {
                switch(starP->mode) {
                    case 0:
                        MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[0], &starP->oscT[0], 15);
                        MdMathLerpScale(scale, 0.5f, 0, starP->oscT[0]);
                        if(starP->oscTime[0] >= 1) {
                            starP->mode++;
                        }
                        break;

                    case 1:
                        break;
                }
            }
        }
    } else if(param == 4) {
        for(starP = &lbl_1_bss_1A8[0], i = 0; i < 6; i++, starP++) {
            pos = model->posP[MDMODEL_CAP_MODE_00 + i];
            rot = model->rotP[MDMODEL_CAP_MODE_00 + i];
            scale = model->scaleP[MDMODEL_CAP_MODE_00 + i];
            if(i == sys->unk3D) {
                switch(starP->mode) {
                    case 0:
                        MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[0], &starP->oscT[0], 15);
                        MdMathLerpScale(scale, 2, 1.5f, starP->oscT[0]);
                        if(starP->oscTime[0] >= 1) {
                            starP->mode++;
                        }
                        break;

                    case 1:
                        break;
                }
            } else {
                switch(starP->mode) {
                    case 0:
                        MdMathOscillate(MDMATH_OSC_90, &starP->oscTime[0], &starP->oscT[0], 15);
                        MdMathLerpScale(scale, 0, 0.5f, starP->oscT[0]);
                        if(starP->oscTime[0] >= 1) {
                            starP->mode++;
                        }
                        break;

                    case 1:
                        break;
                }
            }
        }
    }
    if(param == 0) {
        if(lbl_1_bss_1A8[2].mode == 2) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if(param == 1) {
        if(lbl_1_bss_1A8[5].mode == 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if(param == 2) {
        if(lbl_1_bss_1A8[5].mode == 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if(param == 3) {
        if(lbl_1_bss_1A8[sys->unk3D].mode == 1) {
            for(i = 0; i < 6; i++) {
                if(i != sys->unk3D) {
                    Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_MODE_00 + i]);
                }
            }
            return TRUE;
        } else {
            return FALSE;
        }
    } else if(param == 4) {
        if(lbl_1_bss_1A8[sys->unk3D].mode == 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/* 372 insns. twin: mdparty MdPartyProcCapTurn (here the MDMODEL_CAP_WIN caption; the
 * param-3 start/end positions are kept in lbl_1_bss_154). */
BOOL fn_1_F6C4(int param)
{
    HuVecF *posP; //r31
    HuVecF *scaleP; //r30
    MDMODEL_WORK *model; //r28
    MDCAMERA_WORK *camera; //sp+0xC
    HuVecF *rotP; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    posP = model->posP[MDMODEL_CAP_WIN];
    rotP = model->rotP[MDMODEL_CAP_WIN];
    scaleP = model->scaleP[MDMODEL_CAP_WIN];

    if(!sys->dirtyF) {
        if(param == 0) {
            posP->x = 0;
            posP->y = 145;
            posP->z = 400;

            scaleP->x = 0;
            scaleP->y = 0;
            scaleP->z = 0;
            Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_WIN]);
        } else if(param != 1) {
            if(param == 2) {

            } else if(param == 3) {
                lbl_1_bss_154[0] = *posP;
                lbl_1_bss_154[1].x = -525;
                lbl_1_bss_154[1].y = 365;
                lbl_1_bss_154[1].z = -50;
                fn_1_17008(7);
            } else if(param == 4) {
                fn_1_17008(7);
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 0, 1, sys->procT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdProcCall(MDMINI_PROC_CURSOR, sys->cursorDir+14);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 1, 0, sys->procT);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_154[0].x, lbl_1_bss_154[1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_154[0].y, lbl_1_bss_154[1].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_154[0].z, lbl_1_bss_154[1].z, sys->procT, -1*sys->procOfsT);
        MdMathLerpScale(scaleP, 1, 0.8f, sys->procT);
    } else if(param == 4) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_154[1].x, lbl_1_bss_154[0].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_154[1].y, lbl_1_bss_154[0].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_154[1].z, lbl_1_bss_154[0].z, sys->procT, sys->procOfsT);
        MdMathLerpScale(scaleP, 0.8f, 1.0f, sys->procT);
    }
    fn_1_15CF8(MDMODEL_CAP_WIN, MDCAMERA_MAIN);
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 372 insns. twin: mdparty MdPartyProcCapTurn (here the MDMODEL_CAP_GENRE caption; the
 * param-3 start/end positions are kept in lbl_1_bss_13C). */
BOOL fn_1_FC94(int param)
{
    HuVecF *posP; //r31
    HuVecF *scaleP; //r30
    MDMODEL_WORK *model; //r28
    MDCAMERA_WORK *camera; //sp+0xC
    HuVecF *rotP; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    posP = model->posP[MDMODEL_CAP_GENRE];
    rotP = model->rotP[MDMODEL_CAP_GENRE];
    scaleP = model->scaleP[MDMODEL_CAP_GENRE];

    if(!sys->dirtyF) {
        if(param == 0) {
            posP->x = 0;
            posP->y = 145;
            posP->z = 400;

            scaleP->x = 0;
            scaleP->y = 0;
            scaleP->z = 0;
            Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_GENRE]);
        } else if(param != 1) {
            if(param == 2) {

            } else if(param == 3) {
                lbl_1_bss_13C[0] = *posP;
                lbl_1_bss_13C[1].x = 525;
                lbl_1_bss_13C[1].y = 365;
                lbl_1_bss_13C[1].z = -50;
                fn_1_17008(7);
            } else if(param == 4) {
                fn_1_17008(7);
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 0, 1, sys->procT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdProcCall(MDMINI_PROC_CURSOR, sys->cursorDir+18);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 1, 0, sys->procT);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_13C[0].x, lbl_1_bss_13C[1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_13C[0].y, lbl_1_bss_13C[1].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_13C[0].z, lbl_1_bss_13C[1].z, sys->procT, -1*sys->procOfsT);
        MdMathLerpScale(scaleP, 1, 0.8f, sys->procT);
    } else if(param == 4) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_13C[1].x, lbl_1_bss_13C[0].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_13C[1].y, lbl_1_bss_13C[0].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_13C[1].z, lbl_1_bss_13C[0].z, sys->procT, sys->procOfsT);
        MdMathLerpScale(scaleP, 0.8f, 1.0f, sys->procT);
    }
    fn_1_15CF8(MDMODEL_CAP_GENRE, MDCAMERA_MAIN);
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x908 */ HuVecF lbl_1_data_908[5] = { { 0.0f, 150.0f, 500.0f }, { 0.0f, 95.0f, 0.0f }, { 0.0f, 150.0f, -500.0f }, { 0.0f, -120.0f, 0.0f }, { 0.0f, 75.0f, 0.0f } };
/* 0x944 */ HuVecF lbl_1_data_944[3] = { { 60.0f, 0.0f, 270.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -270.0f, 0.0f } };

/* 284 insns */
BOOL fn_1_10264(int param)
{
    HuVecF *pos;
    MDMODEL_WORK *model;
    HuVecF *rot;
    HuVecF *scale;
    MDCAMERA_WORK *cameraWork;

    cameraWork = sys->camera;
    model = sys->model;
    pos = model->posP[MDMODEL_VS];
    rot = model->rotP[MDMODEL_VS];
    scale = model->scaleP[MDMODEL_VS];
    if(!sys->unk3D8) {
        if(param == 0) {
            *pos = lbl_1_data_908[0];
            if(sys->unk46 == 2) {
                pos->x = -15;
            } else if(sys->unk46 == 1) {
                pos->x = -200;
            }
            *rot = lbl_1_data_944[0];
            scale->x = 3;
            scale->y = 3;
            scale->z = 3;
            Hu3DModelDispOn(model->mdlId[MDMODEL_VS]);
        } else if(param == 1) {
        }
        sys->unk3D8 = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk400, &sys->unk41C, 30);
        MdMathLerp(&pos->y, lbl_1_data_908[0].y, lbl_1_data_908[1].y, sys->unk41C);
        MdMathLerp(&pos->z, lbl_1_data_908[0].z, lbl_1_data_908[1].z, sys->unk41C);
        MdMathLerp(&rot->x, lbl_1_data_944[0].x, lbl_1_data_944[1].x, sys->unk41C);
        MdMathLerp(&rot->y, lbl_1_data_944[0].y, lbl_1_data_944[1].y, sys->unk41C);
        MdMathLerp(&rot->z, lbl_1_data_944[0].z, lbl_1_data_944[1].z, sys->unk41C);
        MdMathLerpScale(scale, 3, 1, sys->unk41C);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk400, &sys->unk41C, 30);
        MdMathLerp(&pos->y, lbl_1_data_908[1].y, lbl_1_data_908[2].y, sys->unk41C);
        MdMathLerp(&pos->z, lbl_1_data_908[1].z, lbl_1_data_908[2].z, sys->unk41C);
        MdMathLerp(&rot->x, lbl_1_data_944[1].x, lbl_1_data_944[2].x, sys->unk41C);
        MdMathLerp(&rot->y, lbl_1_data_944[1].y, lbl_1_data_944[2].y, sys->unk41C);
        MdMathLerp(&rot->z, lbl_1_data_944[1].z, lbl_1_data_944[2].z, sys->unk41C);
        MdMathLerpScale(scale, 1, 0, sys->unk41C);
    }
    if(sys->unk400 >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 270 insns */
BOOL fn_1_106D4(int param)
{
    HuVecF *scale;
    MDMODEL_WORK *model;
    int i;
    MDCAMERA_WORK *cameraWork;

    cameraWork = sys->camera;
    model = sys->model;
    if(!sys->dirtyF) {
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        scale = model->scaleP[MDMODEL_CAP_MODE_00 + sys->unk3D];
        MdMathLerpScale(scale, 2, 0, sys->procT);
        for(i = 0; i < 4; i++) {
            scale = model->scaleP[MDMODEL_CAP_CHR_00 + sys->chrSel[i]];
            MdMathLerp(&scale->x, 1, 0, sys->procT);
            MdMathLerp(&scale->y, 1, 0, sys->procT);
            MdMathLerp(&scale->z, 0.1f, 0, sys->procT);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        scale = model->scaleP[MDMODEL_CAP_WIN];
        MdMathLerpScale(scale, 1, 0, sys->procT);
        scale = model->scaleP[MDMODEL_CAP_GENRE];
        MdMathLerpScale(scale, 1, 0, sys->procT);
        scale = model->scaleP[MDMODEL_CAP_MODE_00 + sys->unk3D];
        MdMathLerpScale(scale, 2, 0, sys->procT);
        for(i = 0; i < 4; i++) {
            scale = model->scaleP[MDMODEL_CAP_CHR_00 + sys->chrSel[i]];
            MdMathLerp(&scale->x, 1, 0, sys->procT);
            MdMathLerp(&scale->y, 1, 0, sys->procT);
            MdMathLerp(&scale->z, 0.1f, 0, sys->procT);
        }
        if(sys->unk46 != 0) {
            scale = model->scaleP[MDMODEL_VS];
            MdMathLerpScale(scale, 1, 0, sys->procT);
        }
    }
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 563 insns */
BOOL fn_1_10B0C(int param)
{
    MDMODEL_WORK *model;
    int i;
    HuVecF *pos;
    HuVecF *scale;
    MDCAMERA_WORK *cameraWork;
    MDSPRITE_WORK *sprite;

    cameraWork = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    if(!sys->dirtyF) {
        if(param == 0 || param == 1) {
            for(i = 0; i < 2; i++) {
                lbl_1_bss_134[i] = 0;
                lbl_1_bss_12C[i] = 0;
                lbl_1_bss_120[i] = 0;
            }
            lbl_1_bss_11C = 0;
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        if(sys->unk46 == 0) {
            for(i = 0; i < 4; i++) {
                pos = model->posP[MDMODEL_CAP_CHR_00 + sys->chrSel[i]];
                MdMathLerp(&pos->y, -160, 120, sys->procT);
            }
            fn_1_153D0();
        }
        lbl_1_bss_11C++;
        if(lbl_1_bss_11C >= 4) {
            lbl_1_bss_120[0] = 1;
        }
        if(lbl_1_bss_11C >= 6) {
            lbl_1_bss_120[1] = 1;
        }
        if(lbl_1_bss_120[0]) {
            MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_134[0], &lbl_1_bss_124[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_12C[0], &lbl_1_bss_124[1], 20);
            pos = model->posP[MDMODEL_CAP_WIN];
            scale = model->scaleP[MDMODEL_CAP_WIN];
            MdMathLerp(&pos->x, -525, -380, lbl_1_bss_124[0]);
            MdMathLerp(&pos->y, 365, 340, lbl_1_bss_124[0]);
            MdMathLerpOfs(&pos->z, -50, 0, lbl_1_bss_124[0], 2 * lbl_1_bss_124[1]);
            MdMathLerpScale(scale, 0.8f, 1, lbl_1_bss_124[0]);
        }
        if(lbl_1_bss_120[1]) {
            MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_134[1], &lbl_1_bss_124[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_12C[1], &lbl_1_bss_124[1], 20);
            pos = model->posP[MDMODEL_CAP_GENRE];
            scale = model->scaleP[MDMODEL_CAP_GENRE];
            MdMathLerp(&pos->x, 525, 380, lbl_1_bss_124[0]);
            MdMathLerp(&pos->y, 365, 340, lbl_1_bss_124[0]);
            MdMathLerpOfs(&pos->z, -50, 0, lbl_1_bss_124[0], 2 * lbl_1_bss_124[1]);
            MdMathLerpScale(scale, 0.8f, 1, lbl_1_bss_124[0]);
        }
        fn_1_15CF8(MDMODEL_CAP_WIN, MDCAMERA_MAIN);
        fn_1_15CF8(MDMODEL_CAP_GENRE, MDCAMERA_MAIN);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        if(sys->unk46 == 0) {
            for(i = 0; i < 4; i++) {
                pos = model->posP[MDMODEL_CAP_CHR_00 + sys->chrSel[i]];
                MdMathLerp(&pos->y, 120, -160, sys->procT);
            }
            fn_1_153D0();
        }
        lbl_1_bss_11C++;
        if(lbl_1_bss_11C >= 6) {
            lbl_1_bss_120[0] = 1;
        }
        if(lbl_1_bss_11C >= 4) {
            lbl_1_bss_120[1] = 1;
        }
        if(lbl_1_bss_120[0]) {
            MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_134[0], &lbl_1_bss_124[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_12C[0], &lbl_1_bss_124[1], 20);
            pos = model->posP[MDMODEL_CAP_WIN];
            scale = model->scaleP[MDMODEL_CAP_WIN];
            MdMathLerp(&pos->x, -380, -525, lbl_1_bss_124[0]);
            MdMathLerp(&pos->y, 340, 365, lbl_1_bss_124[0]);
            MdMathLerpOfs(&pos->z, 0, -50, lbl_1_bss_124[0], 2 * lbl_1_bss_124[1]);
            MdMathLerpScale(scale, 1, 0.8f, lbl_1_bss_124[0]);
        }
        if(lbl_1_bss_120[1]) {
            MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_134[1], &lbl_1_bss_124[0], 20);
            MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_12C[1], &lbl_1_bss_124[1], 20);
            pos = model->posP[MDMODEL_CAP_GENRE];
            scale = model->scaleP[MDMODEL_CAP_GENRE];
            MdMathLerp(&pos->x, 380, 525, lbl_1_bss_124[0]);
            MdMathLerp(&pos->y, 340, 365, lbl_1_bss_124[0]);
            MdMathLerpOfs(&pos->z, 0, -50, lbl_1_bss_124[0], 2 * lbl_1_bss_124[1]);
            MdMathLerpScale(scale, 1, 0.8f, lbl_1_bss_124[0]);
        }
        fn_1_15CF8(MDMODEL_CAP_WIN, MDCAMERA_MAIN);
        fn_1_15CF8(MDMODEL_CAP_GENRE, MDCAMERA_MAIN);
    }
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 160 insns */
/* 160 insns; mdparty MdPartyProcFinger */
BOOL fn_1_113D8(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30

    HuVecF *posP[4]; //sp+0x2C
    HuVecF *rotP[4]; //sp+0x1C
    HuVecF *scaleP[4]; //sp+0xC
    MDCAMERA_WORK *camera; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    for(i=0; i<4; i++) {
        posP[i] = model->posP[i+MDMODEL_FINGER_1P];
        rotP[i] = model->rotP[i+MDMODEL_FINGER_1P];
        scaleP[i] = model->scaleP[i+MDMODEL_FINGER_1P];
    }
    if(!sys->dirtyF) {
        if(param == 0) {
            for(i=0; i<4; i++) {
                if(sys->padEnable[i]) {
                    scaleP[i]->x = 0;
                    scaleP[i]->y = 0;
                    scaleP[i]->z = 0;
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_FINGER_1P]);
                }
            }
            fn_1_153D0();
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0){
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        for(i=0; i<4; i++) {
            if(sys->padEnable[i]) {
                MdMathLerpScale(scaleP[i], 0, 4, sys->procT);
            }
        }
    }
    if(param == 0) {
        if(sys->procTime >= 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/* 3283 insns. Twin: mdparty MdPartyProcMapEnter. The chosen players fly from their
 * capsule seats into the screen before the submode's DLL is entered.
 * Statics (file scope, skeleton): lbl_1_bss_118 mode, lbl_1_bss_F8 effectP[4][2],
 * lbl_1_bss_98 effectPos[4][2], lbl_1_bss_38 effectRot[4][2], lbl_1_bss_34 enterTime,
 * lbl_1_bss_30 vsScaleTime, lbl_1_bss_2C vsScaleT. */
BOOL fn_1_11658(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *posP; //r29
    HuVecF *rotP; //r28
    MDSPRITE_WORK *sprite; //r23
    HuVecF *scaleP; //r22
    MDCAMERA_WORK *camera; //r20

    MDMINI_STAR *star; //sp+0x4C
    MDMESS_WORK *mess; //sp+0x48

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    star = sys->star;
    mess = sys->mess;
    if(!sys->dirtyF) {
        if(param == 0 || param == 1) {
        }
        lbl_1_bss_30 = 0;
        lbl_1_bss_2C = 0;
        lbl_1_bss_118 = 0;
        sys->dirtyF = TRUE;
    }
    if(param == 0 || param == 1) {
        switch(lbl_1_bss_118) {
            case 0:
                for(i=0; i<4; i++) {
                    HuSprAttrSet(sprite->grpId[MDSPR_GRP_PLAYERNO], i, HUSPR_ATTR_DISPOFF);
                    HuSprAttrSet(sprite->grpId[MDSPR_GRP_COMDIF], i, HUSPR_ATTR_DISPOFF);
                }
                for(i=0; i<4; i++) {
                    MdRingModeSet(i, 4);
                }
                for(i=0; i<4; i++) {
                    Hu3DModelAttrSet(model->mdlId[sys->chrSel[i]+MDMODEL_CAP_CHR_00], HU3D_ATTR_DISPOFF);
                }
                Hu3DModelAttrSet(model->mdlId[MDMODEL_STAGE_CHR], HU3D_ATTR_DISPOFF);
                for(i=0; i<4; i++) {
                    Hu3DModelLayerSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], 3);
                    Hu3DModelCameraSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], camera->camera[MDCAMERA_MAIN].bit);
                    *model->posP[sys->chrSel[i]+MDMODEL_MARIO] = *model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
                    model->posP[sys->chrSel[i]+MDMODEL_MARIO]->z = 0;
                }
                for(i=0; i<4; i++) {
                    lbl_1_bss_F8[i][0] = ParticleDotCreate(sprite->animP[MDSPR_ANIM_EFFECT_DOT], 4, camera->camera[MDCAMERA_MAIN].bit);
                    ParticleDotPosSet(lbl_1_bss_F8[i][0], model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00]);
                    lbl_1_bss_F8[i][1] = ParticleGlowCreate(sprite->animP[MDSPR_ANIM_EFFECT_GLOW], 4, camera->camera[MDCAMERA_MAIN].bit);
                    ParticleGlowPosSet(lbl_1_bss_F8[i][1], model->posP[sys->chrSel[i]+MDMODEL_MARIO]);
                }
                if(param == 0) {
                    if(sys->unk46 == 0) {
                        for(i=0; i<4; i++) {
                            lbl_1_bss_98[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            lbl_1_bss_38[i][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        }
                    } else if(sys->unk46 == 2) {
                        for(i=0; i<4; i++) {
                            lbl_1_bss_98[sys->teamOrder[i]][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            lbl_1_bss_38[sys->teamOrder[i]][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        }
                    } else if(sys->unk46 == 1) {
                        for(i=0; i<4; i++) {
                            lbl_1_bss_98[sys->unk5A[i]][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            lbl_1_bss_38[sys->unk5A[i]][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        }
                    }
                } else if(param == 1) {
                    for(i=0; i<4; i++) {
                        lbl_1_bss_98[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                        lbl_1_bss_38[i][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                    }
                }
                lbl_1_bss_98[0][1].x = -300;
                lbl_1_bss_98[0][1].y = 50+lbl_1_bss_98[0][0].y;
                lbl_1_bss_98[0][1].z = 200+lbl_1_bss_98[0][0].z;
                lbl_1_bss_98[1][1].x = -100;
                lbl_1_bss_98[1][1].y = 50+lbl_1_bss_98[1][0].y;
                lbl_1_bss_98[1][1].z = 200+lbl_1_bss_98[1][0].z;
                lbl_1_bss_98[2][1].x = 100;
                lbl_1_bss_98[2][1].y = 50+lbl_1_bss_98[2][0].y;
                lbl_1_bss_98[2][1].z = 200+lbl_1_bss_98[2][0].z;
                lbl_1_bss_98[3][1].x = 300;
                lbl_1_bss_98[3][1].y = 50+lbl_1_bss_98[3][0].y;
                lbl_1_bss_98[3][1].z = 200+lbl_1_bss_98[3][0].z;

                lbl_1_bss_38[0][1].x = 0;
                lbl_1_bss_38[0][1].y = 540;
                lbl_1_bss_38[0][1].z = 0;
                lbl_1_bss_38[1][1].x = 0;
                lbl_1_bss_38[1][1].y = 540;
                lbl_1_bss_38[1][1].z = 0;
                lbl_1_bss_38[2][1].x = 0;
                lbl_1_bss_38[2][1].y = -540;
                lbl_1_bss_38[2][1].z = 0;
                lbl_1_bss_38[3][1].x = 0;
                lbl_1_bss_38[3][1].y = -540;
                lbl_1_bss_38[3][1].z = 0;
                fn_1_17008(8);
                lbl_1_bss_118++;
                break;

            case 1:
                MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 45.0f);
                MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 45.0f);
                if(param == 0 && sys->unk46 != 0) {
                    MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_30, &lbl_1_bss_2C, 15.0f);
                    MdMathLerpScale(model->scaleP[MDMODEL_VS], 1, 0, lbl_1_bss_2C);
                }
                if(param == 0) {
                    if(sys->unk46 == 0) {
                        float ofsTbl[4] = { 4, 2, 1.5f, 3 };
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerpOfs(&posP->x, lbl_1_bss_98[i][0].x, lbl_1_bss_98[i][1].x, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[i]));
                            MdMathLerpOfs(&posP->y, lbl_1_bss_98[i][0].y, lbl_1_bss_98[i][1].y, sys->procT, 0.1f*(sys->procOfsT*ofsTbl[i]));
                            MdMathLerpOfs(&posP->z, lbl_1_bss_98[i][0].z, lbl_1_bss_98[i][1].z, sys->procT, 0.5f*(sys->procOfsT*ofsTbl[i]));
                            MdMathLerp(&rotP->y, lbl_1_bss_38[i][0].y, lbl_1_bss_38[i][1].y, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    } else if(sys->unk46 == 2) {
                        float ofsTbl[4] = { 4, 2, 1.5f, 3 };
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerpOfs(&posP->x, lbl_1_bss_98[sys->teamOrder[i]][0].x, lbl_1_bss_98[sys->teamOrder[i]][1].x, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[sys->teamOrder[i]]));
                            MdMathLerpOfs(&posP->y, lbl_1_bss_98[sys->teamOrder[i]][0].y, lbl_1_bss_98[sys->teamOrder[i]][1].y, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[sys->teamOrder[i]]));
                            MdMathLerpOfs(&posP->z, lbl_1_bss_98[sys->teamOrder[i]][0].z, lbl_1_bss_98[sys->teamOrder[i]][1].z, sys->procT, 0.5f*(sys->procOfsT*ofsTbl[sys->teamOrder[i]]));
                            MdMathLerp(&rotP->y, lbl_1_bss_38[sys->teamOrder[i]][0].y, lbl_1_bss_38[sys->teamOrder[i]][1].y, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    } else if(sys->unk46 == 1) {
                        float ofsTbl[4] = { 4, 2, 1.5f, 3 };
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerpOfs(&posP->x, lbl_1_bss_98[sys->unk5A[i]][0].x, lbl_1_bss_98[sys->unk5A[i]][1].x, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[sys->unk5A[i]]));
                            MdMathLerpOfs(&posP->y, lbl_1_bss_98[sys->unk5A[i]][0].y, lbl_1_bss_98[sys->unk5A[i]][1].y, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[sys->unk5A[i]]));
                            MdMathLerpOfs(&posP->z, lbl_1_bss_98[sys->unk5A[i]][0].z, lbl_1_bss_98[sys->unk5A[i]][1].z, sys->procT, 0.5f*(sys->procOfsT*ofsTbl[sys->unk5A[i]]));
                            MdMathLerp(&rotP->y, lbl_1_bss_38[sys->unk5A[i]][0].y, lbl_1_bss_38[sys->unk5A[i]][1].y, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    }
                } else if(param == 1) {
                    float ofsTbl[4] = { 8, 4, 3, 6 };
                    for(i=0; i<4; i++) {
                        posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                        rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                        MdMathLerpOfs(&posP->x, lbl_1_bss_98[i][0].x, lbl_1_bss_98[i][1].x, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[i]));
                        MdMathLerpOfs(&posP->y, lbl_1_bss_98[i][0].y, lbl_1_bss_98[i][1].y, sys->procT, 0.2f*(sys->procOfsT*ofsTbl[i]));
                        MdMathLerpOfs(&posP->z, lbl_1_bss_98[i][0].z, lbl_1_bss_98[i][1].z, sys->procT, 0.5f*(sys->procOfsT*ofsTbl[i]));
                        MdMathLerp(&rotP->y, lbl_1_bss_38[i][0].y, lbl_1_bss_38[i][1].y, sys->procT);
                        ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                    }
                }
                if(sys->procTime >= 1) {
                    sys->procTime = 0;
                    sys->procOfsTime = 0;
                    sys->procT = 0;
                    sys->procOfsT = 0;
                    if(param == 0) {
                        if(sys->unk46 == 0) {
                            for(i=0; i<4; i++) {
                                lbl_1_bss_98[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->x);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->z);
                                lbl_1_bss_38[i][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            }
                        } else if(sys->unk46 == 2) {
                            for(i=0; i<4; i++) {
                                lbl_1_bss_98[sys->teamOrder[i]][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->x);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->z);
                                lbl_1_bss_38[sys->teamOrder[i]][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            }
                        } else if(sys->unk46 == 1) {
                            for(i=0; i<4; i++) {
                                lbl_1_bss_98[sys->unk5A[i]][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->x);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y);
                                MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->z);
                                lbl_1_bss_38[sys->unk5A[i]][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            }
                        }
                    } else if(param == 1) {
                        for(i=0; i<4; i++) {
                            lbl_1_bss_98[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->x);
                            MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y);
                            MdMathAngleClamp(&model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->z);
                            lbl_1_bss_38[i][0] = *model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        }
                    }
                    lbl_1_bss_98[0][1].x = -200;
                    lbl_1_bss_98[0][1].y = 250;
                    lbl_1_bss_98[0][1].z = -1000;
                    lbl_1_bss_98[1][1].x = -75;
                    lbl_1_bss_98[1][1].y = 250;
                    lbl_1_bss_98[1][1].z = -1000;
                    lbl_1_bss_98[2][1].x = 75;
                    lbl_1_bss_98[2][1].y = 250;
                    lbl_1_bss_98[2][1].z = -1000;
                    lbl_1_bss_98[3][1].x = 200;
                    lbl_1_bss_98[3][1].y = 250;
                    lbl_1_bss_98[3][1].z = -1000;

                    lbl_1_bss_38[0][1].x = 90;
                    lbl_1_bss_38[0][1].y = 160;
                    lbl_1_bss_38[0][1].z = -10;
                    lbl_1_bss_38[1][1].x = 90;
                    lbl_1_bss_38[1][1].y = 175;
                    lbl_1_bss_38[1][1].z = -10;
                    lbl_1_bss_38[2][1].x = 90;
                    lbl_1_bss_38[2][1].y = -175;
                    lbl_1_bss_38[2][1].z = 10;
                    lbl_1_bss_38[3][1].x = 90;
                    lbl_1_bss_38[3][1].y = -160;
                    lbl_1_bss_38[3][1].z = 10;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    star->motNext = 3; /* mdparty MDPARTY_STAR_MOT_IDLE slot; mdmini has no star-motion enum */
                    lbl_1_bss_34 = 0;
                    lbl_1_bss_118++;
                }
                break;

            case 2:
                if(++lbl_1_bss_34 >= 0) {
                    fn_1_17008(9);
                    lbl_1_bss_118++;
                }
                break;

            case 3:
                MdProcCall(MDMINI_PROC_CAMERA, 0);
                MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 60.0f);
                if(param == 0) {
                    if(sys->unk46 == 0) {
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerp(&posP->x, lbl_1_bss_98[i][0].x, lbl_1_bss_98[i][1].x, sys->procT);
                            MdMathLerp(&posP->y, lbl_1_bss_98[i][0].y, lbl_1_bss_98[i][1].y, sys->procT);
                            MdMathLerp(&posP->z, lbl_1_bss_98[i][0].z, lbl_1_bss_98[i][1].z, sys->procT);
                            MdMathLerp(&rotP->x, lbl_1_bss_38[i][0].x, lbl_1_bss_38[i][1].x, sys->procT);
                            MdMathLerp(&rotP->y, lbl_1_bss_38[i][0].y, lbl_1_bss_38[i][1].y, sys->procT);
                            MdMathLerp(&rotP->z, lbl_1_bss_38[i][0].z, lbl_1_bss_38[i][1].z, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    } else if(sys->unk46 == 2) {
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerp(&posP->x, lbl_1_bss_98[sys->teamOrder[i]][0].x, lbl_1_bss_98[sys->teamOrder[i]][1].x, sys->procT);
                            MdMathLerp(&posP->y, lbl_1_bss_98[sys->teamOrder[i]][0].y, lbl_1_bss_98[sys->teamOrder[i]][1].y, sys->procT);
                            MdMathLerp(&posP->z, lbl_1_bss_98[sys->teamOrder[i]][0].z, lbl_1_bss_98[sys->teamOrder[i]][1].z, sys->procT);
                            MdMathLerp(&rotP->x, lbl_1_bss_38[sys->teamOrder[i]][0].x, lbl_1_bss_38[sys->teamOrder[i]][1].x, sys->procT);
                            MdMathLerp(&rotP->y, lbl_1_bss_38[sys->teamOrder[i]][0].y, lbl_1_bss_38[sys->teamOrder[i]][1].y, sys->procT);
                            MdMathLerp(&rotP->z, lbl_1_bss_38[sys->teamOrder[i]][0].z, lbl_1_bss_38[sys->teamOrder[i]][1].z, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    } else if(sys->unk46 == 1) {
                        for(i=0; i<4; i++) {
                            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                            MdMathLerp(&posP->x, lbl_1_bss_98[sys->unk5A[i]][0].x, lbl_1_bss_98[sys->unk5A[i]][1].x, sys->procT);
                            MdMathLerp(&posP->y, lbl_1_bss_98[sys->unk5A[i]][0].y, lbl_1_bss_98[sys->unk5A[i]][1].y, sys->procT);
                            MdMathLerp(&posP->z, lbl_1_bss_98[sys->unk5A[i]][0].z, lbl_1_bss_98[sys->unk5A[i]][1].z, sys->procT);
                            MdMathLerp(&rotP->x, lbl_1_bss_38[sys->unk5A[i]][0].x, lbl_1_bss_38[sys->unk5A[i]][1].x, sys->procT);
                            MdMathLerp(&rotP->y, lbl_1_bss_38[sys->unk5A[i]][0].y, lbl_1_bss_38[sys->unk5A[i]][1].y, sys->procT);
                            MdMathLerp(&rotP->z, lbl_1_bss_38[sys->unk5A[i]][0].z, lbl_1_bss_38[sys->unk5A[i]][1].z, sys->procT);
                            ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                        }
                    }
                } else if(param == 1) {
                    for(i=0; i<4; i++) {
                        posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                        rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
                        scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
                        MdMathLerp(&posP->x, lbl_1_bss_98[i][0].x, lbl_1_bss_98[i][1].x, sys->procT);
                        MdMathLerp(&posP->y, lbl_1_bss_98[i][0].y, lbl_1_bss_98[i][1].y, sys->procT);
                        MdMathLerp(&posP->z, lbl_1_bss_98[i][0].z, lbl_1_bss_98[i][1].z, sys->procT);
                        MdMathLerp(&rotP->x, lbl_1_bss_38[i][0].x, lbl_1_bss_38[i][1].x, sys->procT);
                        MdMathLerp(&rotP->y, lbl_1_bss_38[i][0].y, lbl_1_bss_38[i][1].y, sys->procT);
                        MdMathLerp(&rotP->z, lbl_1_bss_38[i][0].z, lbl_1_bss_38[i][1].z, sys->procT);
                        ParticleGlowPosSet(lbl_1_bss_F8[i][1], posP);
                    }
                }
                if(sys->procTime >= 1) {
                    sys->procTime = 0;
                    sys->procOfsTime = 0;
                    sys->procT = 0;
                    sys->procOfsT = 0;
                    lbl_1_bss_118++;
                }
                break;
        }
        if(lbl_1_bss_118 >= 2) {
            MdProcCall(MDMINI_PROC_WIN, 1);
        }
    }
    if(param == 0 || param == 1) {
        if(lbl_1_bss_118 == 3) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    /* retail bug: no return value when param is not 0/1 (r3 undefined; callers pass 0/1) */
}

/* 0x968 */ HuVecF lbl_1_data_968[2] = { { 288.0f, -128.0f, 0.0f }, { 288.0f, 64.0f, 0.0f } };

/* 162 insns */
/* 162 insns; mdparty MdPartyProcName (pos[2] is lbl_1_data_968 at file scope) */
BOOL fn_1_149A4(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_NAME];
    if(!sys->nameInitF) {
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            HuSprPosSet(grpId, 0, lbl_1_data_968[1].x, lbl_1_data_968[1].y);
            HuSprDispOn(grpId, 0);
        } else if(param == 1) {

        }
        sys->nameInitF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_968[0].x, lbl_1_data_968[1].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_968[0].y, lbl_1_data_968[1].y, sys->nameT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_968[1].x, lbl_1_data_968[0].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_968[1].y, lbl_1_data_968[0].y, sys->nameT);
    }
    if(sys->nameTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 126 insns */
/* 126 insns; mdparty MdPartyPadSetup */
void fn_1_14C2C(void)
{
    int i; //r31
    u16 stat; //r30
    s8 padNo[4] = { 0, 0, 0, 0 };
    sys->maxPlayerNum = 0;
    for(i=0; i<4; i++) {
        sys->padNoConnect[i] = -1;
    }
    for(i=0; i<4; i++) {
        stat = HuPadStatGet(i);
        if(stat == 0) {
            sys->padNoConnect[sys->maxPlayerNum] = i;
            sys->padConnect[i] = TRUE;
            sys->maxPlayerNum++;
        } else {
            sys->padConnect[i] = FALSE;
        }
    }
    if(sys->padConnect[0] == FALSE) {
        for(i=0; i<4; i++) {
            sys->padNoConnect[i] = -1;
            sys->padConnect[i] = FALSE;
        }
        sys->padNoConnect[0] = 0;
        sys->padConnect[0] = TRUE;
        sys->maxPlayerNum = 1;
    }
    sys->playerNum = sys->maxPlayerNum-1;
}

/* 107 insns */
/* 107 insns; mdparty MdPartyPadSetupStory */
void fn_1_14E24(void)
{
    int i; //r31
    s8 padNo[4] = { 0, -1, -1, -1 };
    sys->maxPlayerNum = 0;
    for(i=0; i<4; i++) {
        sys->padNoConnect[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(GwPlayerConf[i].type == GW_TYPE_MAN) {
            padNo[i] = 0;
        } else if(GwPlayerConf[i].type == GW_TYPE_COM) {
            padNo[i] = -1;
        }
    }
    for(i=0; i<4; i++) {
        if(padNo[i] == 0) {
            sys->padNoConnect[sys->maxPlayerNum] = i;
            sys->padConnect[i] = TRUE;
            sys->maxPlayerNum++;
        } else {
            sys->padConnect[i] = FALSE;
        }
    }
    sys->playerNum = sys->maxPlayerNum-1;
}

/* 193 insns */
/* 193 insns; mdparty MdPartyPlayerSetupInit */
void fn_1_14FD0(void)
{
    MDSPRITE_WORK *sprite = sys->sprite; //r28
    MDMODEL_WORK *model = sys->model; //r29
    HUSPRGRPID grpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    int comNum = 0; //r30
    s8 padNo[4] = { -1, -1, -1, -1 }; //sp+0x8
    int i; //r31
    for(i=0; i<4; i++) {
        sys->padNoEnable[i] = sys->padNoConnect[i];
        if(i > sys->playerNum) {
            sys->padNoEnable[i] = -1;
        }
    }
    for(i=0; i<3; i++) {
        sys->comPlayerNo[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(sys->padNoEnable[i] != -1) {
            padNo[sys->padNoEnable[i]] = 0;
        }
    }
    for(i=0; i<4; i++) {
        if(padNo[i] == -1) {
            sys->comPlayerNo[comNum] = i;
            comNum++;
            if(comNum >= 3) {
                break;
            }
        }
    }
    for(i=0; i<4; i++) {
        sys->padEnable[i] = FALSE;
    }
    for(i=0; i<4; i++) {
        if(sys->padNoEnable[i] != -1) {
            sys->padEnable[sys->padNoEnable[i]] = TRUE;
        }
    }
    for(i=0; i<4; i++) {
        if(sys->padEnable[i] == TRUE) {
            HuSprBankSet(grpId, (int)i, i);
        } else {
            HuSprBankSet(grpId, (int)i, 4);
        }
    }
    for(i=0; i<4; i++) {
        if(sys->padEnable[i] == TRUE) {
            Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_1P+i], i);
        } else {
            Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_FINGER_1P+i], 4);
        }
    }
}

/* 63 insns */
/* 63 insns; mdparty MdPartyPlayerCfgRead */
void fn_1_152D4(void)
{
    int i;
    for(i=0; i<4; i++) {
        sys->chrSel[i] = GwPlayerConf[i].charNo;
        sys->comDif[i] = GwPlayerConf[i].dif;
    }
    sys->selComNo = 3-sys->playerNum;
    for(i=0; i<4; i++) {
        sys->chrSelEnd[i] = TRUE;
    }
    sys->selComNo = 3-sys->playerNum;
}

/* 112 insns */
/* 112 insns; mdparty MdPartyPlayerSprUpdate */
void fn_1_153D0(void)
{
    int i; //r31
    HuVecF *fingerPosP; //r30
    MDMODEL_WORK *model; //r29
    MDSPRITE_WORK *sprite; //r28
    HuVecF *chrPosP; //r27
    MDCAMERA_WORK *camera; //r26
    HUSPRGRPID playerNoGrpId; //r25
    HUSPRGRPID comDifGrpId; //r24

    HuVecF pos3D; //sp+0x14
    HuVecF pos2D; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    comDifGrpId = sprite->grpId[MDSPR_GRP_COMDIF];
    HuSprGrpPosSet(playerNoGrpId, 0, 0);
    HuSprGrpPosSet(comDifGrpId, 0, 0);
    for(i=0; i<4; i++) {
        fingerPosP = model->posP[i+MDMODEL_FINGER_1P];
        chrPosP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
        *fingerPosP = *chrPosP;
        fingerPosP->x -= 60;
        fingerPosP->y += 105;
        fingerPosP->z += 30;
        pos3D = *chrPosP;
        Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
        HuSprPosSet(playerNoGrpId, (int)i, pos2D.x, pos2D.y-18);
        HuSprPosSet(comDifGrpId, (int)i, pos2D.x, pos2D.y-18);
    }
}

/* 0x980 */ s8 lbl_1_data_980[5][4] = { { 0, 4, 1, 3 }, { 1, 0, 2, 4 }, { 2, 1, 3, 0 }, { 3, 2, 4, 1 }, { 4, 3, 0, 2 } }; /* fn_1_15590; mdparty fixPos (UP) */
/* 0x994 */ s8 lbl_1_data_994[5][4] = { { 0, 1, 4, 2 }, { 1, 2, 0, 3 }, { 2, 3, 1, 4 }, { 3, 4, 2, 0 }, { 4, 0, 3, 1 } }; /* fn_1_15590; mdparty fixPos (DOWN) */

/* 409 insns */
/* 409 insns; mdparty MdPartyChrSelCursorUpdate (fixPos tables are lbl_1_data_980/994 at file scope) */
BOOL fn_1_15590(int playerNo, BOOL comSelF)
{
    int i; //r31
    int padNo; //r30

    s8 selFlag[10]; //sp+0x8
    if(sys->chrSelEnd[playerNo] == TRUE) {
        return FALSE;
    }
    if(comSelF == FALSE) {
        padNo = playerNo;
    } else if(comSelF == TRUE) {
        padNo = 0;
    }
    if((sys->pad->DStkDown[padNo] & PAD_BUTTON_LEFT) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_RIGHT) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_UP) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_DOWN)) {
            for(i=0; i<10; i++) {
                selFlag[i] = -1;
            }
            for(i=0; i<4; i++) {
                if(comSelF == FALSE) {
                    if(i == playerNo) {
                        continue;
                    }
                    if(sys->padEnable[i] == FALSE) {
                        continue;
                    }
                } else if(comSelF == TRUE) {
                    if(i == playerNo) {
                        continue;
                    }
                    if(sys->chrSelEnd[i] == FALSE) {
                        continue;
                    }
                }
                selFlag[sys->chrSel[i]] = 0;
            }
            if(sys->pad->DStkDown[padNo] & PAD_BUTTON_LEFT) {
                for(i=0; i<4; i++) {
                    if(--sys->chrSel[playerNo] == -1) {
                        sys->chrSel[playerNo] = 9;
                    }
                    if(selFlag[sys->chrSel[playerNo]] == -1) {
                        break;
                    }
                }
            } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_RIGHT) {
                for(i=0; i<4; i++) {
                    sys->chrSel[playerNo] = ++sys->chrSel[playerNo] %10;
                    if(selFlag[sys->chrSel[playerNo]] == -1) {
                        break;
                    }
                }
            } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_UP) {
                if(sys->chrSel[playerNo] < 5) {
                    for(i=0; i<4; i++) {
                        if(selFlag[lbl_1_data_980[sys->chrSel[playerNo]][i]+5] == -1) {
                            sys->chrSel[playerNo] = lbl_1_data_980[sys->chrSel[playerNo]][i]+5;
                            break;
                        }
                    }
                } else {
                    for(i=0; i<4; i++) {
                        if(selFlag[lbl_1_data_980[sys->chrSel[playerNo]-5][i]] == -1) {
                            sys->chrSel[playerNo] = lbl_1_data_980[sys->chrSel[playerNo]-5][i];
                            break;
                        }
                    }
                }
            } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_DOWN) {
                if(sys->chrSel[playerNo] < 5) {
                    for(i=0; i<4; i++) {
                        if(selFlag[lbl_1_data_994[sys->chrSel[playerNo]][i]+5] == -1) {
                            sys->chrSel[playerNo] = lbl_1_data_994[sys->chrSel[playerNo]][i]+5;
                            break;
                        }
                    }
                } else {
                    for(i=0; i<4; i++) {
                        if(selFlag[lbl_1_data_994[sys->chrSel[playerNo]-5][i]] == -1) {
                            sys->chrSel[playerNo] = lbl_1_data_994[sys->chrSel[playerNo]-5][i];
                            break;
                        }
                    }
                }
            }
            return TRUE;
        } else {
            return FALSE;
        }

}

/* 65 insns */
/* 65 insns; mdparty MdPartyChrComInit */
void fn_1_15BF4(void)
{
    int i; //r31
    s8 selFlag[10];
    int temp = 0;
    for(i=0; i<10; i++) {
        selFlag[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(sys->chrSelEnd[i] == TRUE) {
            selFlag[sys->chrSel[i]] = 0;
        }
    }
    for(i=0; i<4; i++) {
        if(selFlag[i] == -1) {
            sys->chrSel[sys->comPlayerNo[sys->selComNo]] = i;
            break;
        }
    }
}

/* 60 insns */
/* 60 insns; mdparty MdPartyModelBBoardSet / mdsel MdSelBillboardUpdate */
void fn_1_15CF8(int mdlNo, int cameraNo)
{
    MDCAMERA *camera; //r31
    HuVecF *posP; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *rotP; //r28
    MDCAMERA_WORK *cameraWork; //r27

    float rotY;
    HuVecF dir;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[cameraNo];
    model = sys->model;
    posP = model->posP[mdlNo];
    rotP = model->rotP[mdlNo];
    dir.x = camera->pos.x-posP->x;
    dir.y = camera->pos.y-posP->y;
    dir.z = camera->pos.z-posP->z;
    rotY = HuAtan(dir.x, dir.z);
    rotP->y = rotY;
}

/* 0x9A8 */ s8 lbl_1_data_9A8[3][4] = { { 0, 1, 2, 3 }, { 0, 2, 1, 3 }, { 0, 3, 1, 2 } }; /* fn_1_15DE8; mdparty teamPlayer */
/* 0x9B4 */ s8 lbl_1_data_9B4[3][4] = { { 0, 1, 2, 3 }, { 0, 2, 1, 3 }, { 0, 2, 3, 1 } }; /* fn_1_15DE8; mdparty teamOrder */
/* 0x9C0 */ s8 lbl_1_data_9C0[45][2] = { /* fn_1_15DE8; mdparty teamChr */
    { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 }, { 0, 8 }, { 0, 9 },
    { 1, 2 }, { 1, 3 }, { 1, 4 }, { 1, 5 }, { 1, 6 }, { 1, 7 }, { 1, 8 }, { 1, 9 },
    { 2, 3 }, { 2, 4 }, { 2, 5 }, { 2, 6 }, { 2, 7 }, { 2, 8 }, { 2, 9 },
    { 3, 4 }, { 3, 5 }, { 3, 6 }, { 3, 7 }, { 3, 8 }, { 3, 9 },
    { 4, 5 }, { 4, 6 }, { 4, 7 }, { 4, 8 }, { 4, 9 },
    { 5, 6 }, { 5, 7 }, { 5, 8 }, { 5, 9 },
    { 6, 7 }, { 6, 8 }, { 6, 9 },
    { 7, 8 }, { 7, 9 },
    { 8, 9 }
};

/* 224 insns */
/* 224 insns; mdparty MdPartyTeamPlayerUpdate (teamPlayer/teamOrder/teamChr are lbl_1_data_9A8/9B4/9C0) */
void fn_1_15DE8(void)
{
    int i; //r31
    int j; //r30
    int comNum; //r29

    comNum = 0;
    for(i=0; i<2; i++) {
        sys->teamPlayer[0][i] = lbl_1_data_9A8[sys->teamOrderNo][i];
        sys->teamPlayer[1][i] = lbl_1_data_9A8[sys->teamOrderNo][i+2];
    }
    for(i=0; i<4; i++) {
        sys->teamOrder[i] = lbl_1_data_9B4[sys->teamOrderNo][i];
    }
    for(i=0; i<2; i++) {
        for(j=0; j<45; j++) {
            if((sys->chrSel[sys->teamPlayer[i][0]] == lbl_1_data_9C0[j][0] &&
                sys->chrSel[sys->teamPlayer[i][1]] == lbl_1_data_9C0[j][1]) ||
                (sys->chrSel[sys->teamPlayer[i][1]] == lbl_1_data_9C0[j][0] &&
                sys->chrSel[sys->teamPlayer[i][0]] == lbl_1_data_9C0[j][1])) {
                    sys->teamNo[i] = j;
                    break;
                }
        }
    }

    for(i=0; i<3; i++) {
        sys->teamComPlayerNo[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(!sys->padEnable[lbl_1_data_9A8[sys->teamOrderNo][i]]) {
            sys->teamComPlayerNo[comNum] = lbl_1_data_9A8[sys->teamOrderNo][i];
            comNum++;
            if(comNum >= 3) {
                break;
            }
        }
    }
}

/* 20 insns */
/* 20 insns; mdparty MdPartyTeamOrderBackup */
void fn_1_16168(void)
{
    int i;
    for(i=0; i<4; i++) {
        sys->teamOrderBackup[i] = sys->teamOrder[i];
    }
}

/* 0xA1A */ s8 lbl_1_data_A1A[4][4] = { { 0, 1, 2, 3 }, { 1, 0, 2, 3 }, { 2, 0, 1, 3 }, { 3, 0, 1, 2 } }; /* fn_1_161B8 -> sys->unk62 */
/* 0xA2A */ s8 lbl_1_data_A2A[4][4] = { { 0, 1, 2, 3 }, { 1, 0, 2, 3 }, { 1, 2, 0, 3 }, { 1, 2, 3, 0 } }; /* fn_1_161B8 -> sys->unk5A (+2 bytes alignment) */

/* 84 insns */
void fn_1_161B8(void)
{
    int comNum = 0;
    int i;
    for(i = 0; i < 4; i++) {
        sys->unk5A[i] = lbl_1_data_A2A[sys->unk59][i];
    }
    for(i = 0; i < 3; i++) {
        sys->unk62[i] = -1;
    }
    for(i = 0; i < 4; i++) {
        if(sys->padEnable[lbl_1_data_A1A[sys->unk59][i]] == 0) {
            sys->unk62[comNum] = lbl_1_data_A1A[sys->unk59][i];
            if(++comNum >= 3) {
                break;
            }
        }
    }
}

/* 20 insns */
/* 20 insns; mdparty MdPartyTeamOrderBackup (second order block: unk5E = unk5A) */
void fn_1_16308(void)
{
    int i;
    for(i=0; i<4; i++) {
        sys->unk5E[i] = sys->unk5A[i];
    }
}

/* 392 insns */
void fn_1_16358(void)
{
    MDMODEL_WORK *model = sys->model;
    int i;
    int mgNo;
    MGDATA *mgData;
    BOOL unlockF;

    for(i = 0; i < 6; i++) {
        sys->unk3F[i] = 0;
    }
    sys->unk3F[0] = 1;
    {
        s8 typeF[3] = { 0, 0, 0 };
        mgNo = 0;
        mgData = &mgDataTbl[mgNo];
        do {
            if(typeF[0] == 0 && mgData->type == MG_TYPE_4P && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[0] = 1;
                }
            } else if(typeF[1] == 0 && mgData->type == MG_TYPE_1VS3 && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[1] = 1;
                }
            } else if(typeF[2] == 0 && mgData->type == MG_TYPE_2VS2 && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[2] = 1;
                }
            }
            mgNo++;
            mgData++;
        } while(mgData->ovl != (u16)DLL_NONE);
        if(typeF[0] == 1 && typeF[1] == 1 && typeF[2] == 1) {
            sys->unk3F[1] = 1;
        }
    }
    {
        s8 typeF[5] = { 0, 0, 0, 0, 0 };
        mgNo = 0;
        mgData = &mgDataTbl[mgNo];
        do {
            if(typeF[0] == 0 && mgData->type == MG_TYPE_4P && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[0] = 1;
                }
            } else if(typeF[1] == 0 && mgData->type == MG_TYPE_1VS3 && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[1] = 1;
                }
            } else if(typeF[2] == 0 && mgData->type == MG_TYPE_2VS2 && !(mgData->flag & MG_FLAG_NOSTORY)) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[2] = 1;
                }
            } else if(typeF[3] == 0 && mgData->type == MG_TYPE_KUPA) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[3] = 1;
                }
            } else if(typeF[4] == 0 && mgData->type == MG_TYPE_KETTOU) {
                unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
                if(unlockF == TRUE) {
                    typeF[4] = 1;
                }
            }
            mgNo++;
            mgData++;
        } while(mgData->ovl != (u16)DLL_NONE);
        if(typeF[0] == 1 && typeF[1] == 1 && typeF[2] == 1 && typeF[3] == 1 && typeF[4] == 1) {
            sys->unk3F[2] = 1;
        }
    }
    {
        s16 decaMgTbl[11] = { 502, 504, 506, 507, 510, 511, 512, 513, 514, 563, -1 };
        mgNo = 0;
        mgData = &mgDataTbl[decaMgTbl[mgNo]];
        while(1) {
            unlockF = GWMgUnlockGet(decaMgTbl[mgNo]);
            if(unlockF == FALSE) {
                sys->unk3F[3] = 0;
                break;
            }
            mgNo++;
            if(decaMgTbl[mgNo] == -1) {
                sys->unk3F[3] = 1;
                break;
            }
            mgData = &mgDataTbl[decaMgTbl[mgNo]];
        }
    }
    mgNo = 0;
    mgData = &mgDataTbl[mgNo];
    do {
        if(mgData->type == MG_TYPE_4P && !(mgData->flag & MG_FLAG_NOSTORY)) {
            unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
            if(unlockF == TRUE) {
                sys->unk3F[4] = 1;
                break;
            }
        }
        mgNo++;
        mgData++;
    } while(mgData->ovl != (u16)DLL_NONE);
    mgNo = 0;
    mgData = &mgDataTbl[mgNo];
    do {
        if(mgData->type == MG_TYPE_KETTOU) {
            unlockF = GWMgUnlockGet(mgNo + GW_MGNO_BASE);
            if(unlockF == TRUE) {
                sys->unk3F[5] = 1;
                break;
            }
        }
        mgNo++;
        mgData++;
    } while(mgData->ovl != (u16)DLL_NONE);
    for(i = 0; i < 6; i++) {
        if(sys->unk3F[i] == 0) {
            Hu3DModelTPLvlSet(model->mdlId[MDMODEL_CAP_MODE_00 + i], 0.2f);
        }
    }
}

/* 420 insns. twin: mdparty MdPartySaveInit (reduced: no board/turn/bonus setup here).
 * Writes the Minigame Mode match settings (sys->unk45 -> mgMatchMaxScore 3/5/7,
 * sys->unk46 -> mgMatchGameType 0/1/2), the teams (GwPlayer[].grp) when the chosen submode is
 * mgmatch (sys->unk3D == 1), and the per-player GwPlayer / GwPlayerConf setup. */
void fn_1_16978(void)
{
    int i;
    for(i=0; i<4; i++) {
        sdHealthLoss[i] = 0;
    }
    if(sys->unk45 == 0) {
        mgMatchMaxScore = 3;
    } else if(sys->unk45 == 1) {
        mgMatchMaxScore = 5;
    } else if(sys->unk45 == 2) {
        mgMatchMaxScore = 7;
    }
    if(sys->unk46 == 0) {
        mgMatchGameType = 0;
    } else if(sys->unk46 == 1) {
        mgMatchGameType = 1;
    } else if(sys->unk46 == 2) {
        mgMatchGameType = 2;
    }
    if(sys->unk3D == 1) {
        GwPlayer[0].grp = 0;
        if(sys->unk46 == 0) {
            /* retail stores 0,1,2,3 into the 1-bit grp field: players get 0,1,0,1 */
            GwPlayer[0].grp = 0;
            GwPlayer[1].grp = 1;
            GwPlayer[2].grp = 2;
            GwPlayer[3].grp = 3;
        } else if(sys->unk46 == 1) {
            GwPlayer[0].grp = 0;
            GwPlayer[1].grp = 1;
            GwPlayer[2].grp = 1;
            GwPlayer[3].grp = 1;
            for(i=0; i<4; i++) {
                if(sys->unk5A[i] < 1) {
                    GwPlayer[i].grp = 0;
                } else {
                    GwPlayer[i].grp = 1;
                }
            }
        } else if(sys->unk46 == 2) {
            GwPlayer[0].grp = 0;
            GwPlayer[1].grp = 0;
            GwPlayer[2].grp = 1;
            GwPlayer[3].grp = 1;
            for(i=0; i<4; i++) {
                if(sys->teamOrder[i] < 2) {
                    GwPlayer[i].grp = 0;
                } else {
                    GwPlayer[i].grp = 1;
                }
            }
        }
    } else {
        GwPlayer[0].grp = 0;
        GwPlayer[1].grp = 1;
        GwPlayer[2].grp = 2;
        GwPlayer[3].grp = 3;
    }
    for(i=0; i<4; i++) {
        if(!sys->padEnable[i]) {
            GwPlayer[i].comF = TRUE;
        } else {
            GwPlayer[i].comF = FALSE;
        }
        GwPlayer[i].charNo = sys->chrSel[i];
        GwPlayer[i].dif = sys->comDif[i];
        if(sys->padNoEnable[i] != -1) {
            GwPlayer[i].padNo = sys->padNoConnect[i];
        } else {
            GwPlayer[i].padNo = -1;
        }
        GwPlayerConf[i].charNo = GwPlayer[i].charNo;
        GwPlayerConf[i].padNo = GwPlayer[i].padNo = i;
        GwPlayerConf[i].dif = GwPlayer[i].dif;
        GwPlayerConf[i].type = GwPlayer[i].comF;
        GwPlayerConf[i].grp = GwPlayer[i].grp;
    }
}
/* 0xA3C */ s32 lbl_1_data_A3C[10] = { 0x201, 0x1ED, 0x265, 0x2B5, 0x28D, 0x1C5, 0x2A1, 0x1D9, 0x279, 0x23D };
/* 107 insns */
/* 107 insns; mdparty MdPartyAudExec (command numbers: MDMINI_AUD_* in mdminiDll.h) */
void fn_1_17008(int cmd)
{
    int pan; //r30

    /* mdparty's function statics streamNo / seNo are the file-scope lbl_1_bss_28 / lbl_1_bss_24 */
    switch(cmd) {
        case MDMINI_AUD_MUS_START:
            lbl_1_bss_28 = HuAudBGMPlay(MSM_STREAM_MODE);
            break;

        case MDMINI_AUD_MUS_STOP:
            HuAudSStreamFadeOut(lbl_1_bss_28, 1000);
            break;

        case MDMINI_AUD_SE_CMN_MOVE:
        case MDMINI_AUD_SE_CMN_CONFIRM:
        case MDMINI_AUD_SE_CMN_CHRSEL:
        case MDMINI_AUD_SE_CMN_CANCEL:
        case MDMINI_AUD_SE_CMN_05:
        case MDMINI_AUD_SE_MENU_MOVE:
        case MDMINI_AUD_SE_MENU_28:
        case MDMINI_AUD_SE_MENU_29:
            if(cmd == MDMINI_AUD_SE_CMN_MOVE) {
                HuAudFXPlay(MSM_SE_CMN_01);
            } else if(cmd == MDMINI_AUD_SE_CMN_CONFIRM) {
                HuAudFXPlay(MSM_SE_CMN_03);
            } else if(cmd == MDMINI_AUD_SE_CMN_CHRSEL) {
                HuAudFXPlay(MSM_SE_CMN_02);
            } else if(cmd == MDMINI_AUD_SE_CMN_CANCEL) {
                HuAudFXPlay(MSM_SE_CMN_04);
            } else if(cmd == MDMINI_AUD_SE_CMN_05) {
                HuAudFXPlay(MSM_SE_CMN_05);
            } else if(cmd == MDMINI_AUD_SE_MENU_MOVE) {
                HuAudFXPlay(MSM_SE_MENU_27);
            } else if(cmd == MDMINI_AUD_SE_MENU_28) {
                HuAudFXPlay(MSM_SE_MENU_28);
            } else if(cmd == MDMINI_AUD_SE_MENU_29) {
                lbl_1_bss_24 = HuAudFXPlay(MSM_SE_MENU_29);
            }
            break;

        case MDMINI_AUD_SE_STAR_ENTER:
        case MDMINI_AUD_SE_STAR_CONFIRM:
        {
            int pan = fn_1_171B4(MDMODEL_STAR, MDCAMERA_FG);
            /* retail plays the same SE for both commands */
            if(cmd == MDMINI_AUD_SE_STAR_ENTER) {
                HuAudFXPlayPan(MSM_SE_GUIDE_56, pan);
            } else if(cmd == MDMINI_AUD_SE_STAR_CONFIRM) {
                HuAudFXPlayPan(MSM_SE_GUIDE_56, pan);
            }
        }

            break;

        case MDMINI_AUD_SE_CHR_MARIO:
        case MDMINI_AUD_SE_CHR_LUIGI:
        case MDMINI_AUD_SE_CHR_PEACH:
        case MDMINI_AUD_SE_CHR_YOSHI:
        case MDMINI_AUD_SE_CHR_WARIO:
        case MDMINI_AUD_SE_CHR_DAISY:
        case MDMINI_AUD_SE_CHR_WALUIGI:
        case MDMINI_AUD_SE_CHR_KINOPIO:
        case MDMINI_AUD_SE_CHR_TERESA:
        case MDMINI_AUD_SE_CHR_MINIKOOPA:
        {
            int pan = fn_1_171B4((cmd-MDMINI_AUD_SE_CHR_MARIO)+MDMODEL_CAP_CHR_00, MDCAMERA_MAIN);
            HuAudFXPlayPan(lbl_1_data_A3C[cmd-MDMINI_AUD_SE_CHR_MARIO], pan);
        }
            break;

        case MDMINI_AUD_SE_ALL_STOP:
            HuAudAllStop();
            break;
    }
}

/* 46 insns */
/* 46 insns; mdsel MdSelFXPanGet / mdparty MdPartyFXPanGet */
int fn_1_171B4(int mdlNo, int cameraNo)
{
    MDCAMERA *camera; //r31
    MDMODEL_WORK *model; //r30

    MDCAMERA_WORK *cameraWork; //r29
    HuVecF *posP; //r28
    int result; //r27

    HuVecF pos2D;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[cameraNo];
    model = sys->model;
    posP = model->posP[mdlNo];
    Hu3D3Dto2D(posP, camera->bit, &pos2D);
    result = MSM_PAN_LEFT+((MSM_PAN_WIDTH/HU_DISP_WIDTH)*pos2D.x);
    return result;
}

/* 0xC98 */ static MDMODEL_DEBUG_INFO mdlInfo[MDMODEL_MAX] = { /* MdPosAdjustMode (a function static in the twin) */
    { "STAR", MDCAMERA_FG },
    { "STAGE", MDCAMERA_MAIN },
    { "STAGE_CHR", MDCAMERA_MAIN },
    { "MARIO", MDCAMERA_MAIN },
    { "LUIGI", MDCAMERA_MAIN },
    { "PEACH", MDCAMERA_MAIN },
    { "YOSHI", MDCAMERA_MAIN },
    { "WARIO", MDCAMERA_MAIN },
    { "DAISY", MDCAMERA_MAIN },
    { "WALUIGI", MDCAMERA_MAIN },
    { "KINOPIO", MDCAMERA_MAIN },
    { "TERESA", MDCAMERA_MAIN },
    { "MINIKOOPA", MDCAMERA_MAIN },
    { "CAP_MAN_1P", MDCAMERA_MAIN },
    { "CAP_MAN_2P", MDCAMERA_MAIN },
    { "CAP_MAN_3P", MDCAMERA_MAIN },
    { "CAP_MAN_4P", MDCAMERA_MAIN },
    { "CAP_COM_1P", MDCAMERA_MAIN },
    { "CAP_COM_2P", MDCAMERA_MAIN },
    { "CAP_COM_3P", MDCAMERA_MAIN },
    { "CAP_COM_4P", MDCAMERA_MAIN },
    { "CAP_CHR_00", MDCAMERA_MAIN },
    { "CAP_CHR_01", MDCAMERA_MAIN },
    { "CAP_CHR_02", MDCAMERA_MAIN },
    { "CAP_CHR_03", MDCAMERA_MAIN },
    { "CAP_CHR_04", MDCAMERA_MAIN },
    { "CAP_CHR_05", MDCAMERA_MAIN },
    { "CAP_CHR_06", MDCAMERA_MAIN },
    { "CAP_CHR_07", MDCAMERA_MAIN },
    { "CAP_CHR_08", MDCAMERA_MAIN },
    { "CAP_CHR_09", MDCAMERA_MAIN },
    { "CAP_MODE_00", MDCAMERA_MAIN },
    { "CAP_MODE_01", MDCAMERA_MAIN },
    { "CAP_MODE_02", MDCAMERA_MAIN },
    { "CAP_MODE_03", MDCAMERA_MAIN },
    { "CAP_MODE_04", MDCAMERA_MAIN },
    { "CAP_MODE_05", MDCAMERA_MAIN },
    { "CAP_WIN", MDCAMERA_MAIN },
    { "CAP_GENRE", MDCAMERA_MAIN },
    { "FINGER_1P", MDCAMERA_MAIN },
    { "FINGER_2P", MDCAMERA_MAIN },
    { "FINGER_3P", MDCAMERA_MAIN },
    { "FINGER_4P", MDCAMERA_MAIN },
    { "RING_1P", MDCAMERA_MAIN },
    { "RING_2P", MDCAMERA_MAIN },
    { "RING_3P", MDCAMERA_MAIN },
    { "RING_4P", MDCAMERA_MAIN },
    { "VS", MDCAMERA_MAIN },
    { "FONTBGFILTER", MDCAMERA_FG },
};

/* 1114 insns; mdsel MdPosAdjustMode (mdlInfo is the file-scope table above) */
void MdPosAdjustMode(void)
{
    HuVecF *pos; //r31
    HuVecF *rot; //r30
    HuVecF *scale; //r29
    MDDEBUGFONT_WORK *debugFont; //r28
    MDMODEL_WORK *model; //r27
    HUSPRGRPID grpId; //r26
    int i; //r25
    u32 attr; //r24
    MDSPRITE_WORK *sprite; //r23
    MDCAMERA_WORK *camera; //r22
    
    HuVecF pos2D; //sp+0x8
    
    
    static MDMODEL_DEBUG_INFO *mdlInfoP; /* .bss 0x20 */
    static HuVec2f sprPos;
    static float sprRot;
    static int menuSel;
    static int mdlSel;
    static int dispTimer;
    static BOOL showF;
    
    debugFont = sys->debugFont;
    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_LR];
    if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
        if(showF == FALSE) {
            if(HuPadBtn[0] & PAD_BUTTON_X) {
                if(++dispTimer >= 60) {
                    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, TRUE);
                    dispTimer = 0;
                    showF = TRUE;
                }
            } else {
                dispTimer = 0;
            }
        } else if(showF == TRUE) {
            while(1) {
                if(HuPadBtn[0] & PAD_BUTTON_X) {
                    if(++dispTimer >= 60) {
                        MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
                        dispTimer = 0;
                        showF = FALSE;
                        break;
                    }
                } else {
                    dispTimer = 0;
                }
                if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
                    if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                        for(i=0; i<MDMODEL_MAX; i++) {
                            if(--mdlSel == -1) {
                                mdlSel = MDMODEL_MAX-1;
                            }
                            attr = Hu3DModelAttrGet(model->mdlId[mdlSel]);
                            if(!(attr & HU3D_ATTR_DISPOFF)) {
                                break;
                            }
                        }
                    } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                        for(i=0; i<MDMODEL_MAX; i++) {
                            mdlSel = ++mdlSel % MDMODEL_MAX;
                            attr = Hu3DModelAttrGet(model->mdlId[mdlSel]);
                            if(!(attr & HU3D_ATTR_DISPOFF)) {
                                break;
                            }
                        }
                    }
                    if(HuPadBtnDown[0] & PAD_BUTTON_DOWN) {
                        menuSel = ++menuSel % 3;
                    }
                    mdlInfoP = &mdlInfo[mdlSel];
                    pos = model->posP[mdlSel];
                    rot = model->rotP[mdlSel];
                    scale = model->scaleP[mdlSel];
                    attr = Hu3DModelAttrGet(model->mdlId[mdlSel]);
                    if(menuSel == 0) {
                        if(HuPadTrigL[0] <= 75) {
                            if(HuPadSubStkX[0] <= -29) {
                                pos->x -= 5;
                            } else if(HuPadSubStkX[0] >= 29) {
                                pos->x += 5;
                            }
                            if(HuPadStkY[0] <= -36) {
                                pos->y -= 5;
                            } else if(HuPadStkY[0] >= 36) {
                                pos->y += 5;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                pos->z += 5;
                            } else if(HuPadSubStkY[0] >= 29) {
                                pos->z -= 5;
                            }
                        } else if(HuPadBtn[0] & PAD_TRIGGER_L) {
                            if(HuPadSubStkX[0] <= -29) {
                                pos->x -= 0.5f;
                            } else if(HuPadSubStkX[0] >= 29) {
                                pos->x += 0.5f;
                            }
                            if(HuPadStkY[0] <= -36) {
                                pos->y -= 0.5f;
                            } else if(HuPadStkY[0] >= 36) {
                                pos->y += 0.5f;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                pos->z += 0.5f;
                            } else if(HuPadSubStkY[0] >= 29) {
                                pos->z -= 0.5f;
                            }
                        } else {
                            if(HuPadSubStkX[0] <= -29) {
                                pos->x -= 1.0f;
                            } else if(HuPadSubStkX[0] >= 29) {
                                pos->x += 1.0f;
                            }
                            if(HuPadStkY[0] <= -36) {
                                pos->y -= 1.0f;
                            } else if(HuPadStkY[0] >= 36) {
                                pos->y += 1.0f;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                pos->z += 1.0f;
                            } else if(HuPadSubStkY[0] >= 29) {
                                pos->z -= 1.0f;
                            }
                        }
                    } else if(menuSel == 1) {
                        if(HuPadTrigL[0] <= 75) {
                            if(HuPadSubStkX[0] <= -29) {
                                rot->x -= 10;
                            } else if(HuPadSubStkX[0] >= 29) {
                                rot->x += 10;
                            }
                            if(HuPadStkY[0] <= -36) {
                                rot->y -= 10;
                            } else if(HuPadStkY[0] >= 36) {
                                rot->y += 10;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                rot->z += 10;
                            } else if(HuPadSubStkY[0] >= 29) {
                                rot->z -= 10;
                            }
                        } else if(HuPadBtn[0] & PAD_TRIGGER_L) {
                            if(HuPadSubStkX[0] <= -29) {
                                rot->x -= 1;
                            } else if(HuPadSubStkX[0] >= 29) {
                                rot->x += 1;
                            }
                            if(HuPadStkY[0] <= -36) {
                                rot->y -= 1;
                            } else if(HuPadStkY[0] >= 36) {
                                rot->y += 1;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                rot->z += 1;
                            } else if(HuPadSubStkY[0] >= 29) {
                                rot->z -= 1;
                            }
                        } else {
                            if(HuPadSubStkX[0] <= -29) {
                                rot->x -= 5;
                            } else if(HuPadSubStkX[0] >= 29) {
                                rot->x += 5;
                            }
                            if(HuPadStkY[0] <= -36) {
                                rot->y -= 5;
                            } else if(HuPadStkY[0] >= 36) {
                                rot->y += 5;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                rot->z += 5;
                            } else if(HuPadSubStkY[0] >= 29) {
                                rot->z -= 5;
                            }
                        }
                    } else if(menuSel == 2) {
                        if(HuPadTrigL[0] <= 75) {
                            if(HuPadSubStkX[0] <= -29) {
                                scale->x -= 0.05f;
                                scale->y -= 0.05f;
                                scale->z -= 0.05f;
                            } else if(HuPadSubStkX[0] >= 29) {
                                scale->x += 0.05f;
                                scale->y += 0.05f;
                                scale->z += 0.05f;
                            }
                        } else if(HuPadBtn[0] & PAD_TRIGGER_L) {
                            if(HuPadSubStkX[0] <= -29) {
                                scale->x -= 0.01f;
                            } else if(HuPadSubStkX[0] >= 29) {
                                scale->x += 0.01f;
                            }
                            if(HuPadStkY[0] <= -36) {
                                scale->y -= 0.01f;
                            } else if(HuPadStkY[0] >= 36) {
                                scale->y += 0.01f;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                scale->z += 0.01f;
                            } else if(HuPadSubStkY[0] >= 29) {
                                scale->z -= 0.01f;
                            }
                        } else {
                            if(HuPadSubStkX[0] <= -29) {
                                scale->x -= 0.1f;
                            } else if(HuPadSubStkX[0] >= 29) {
                                scale->x += 0.1f;
                            }
                            if(HuPadStkY[0] <= -36) {
                                scale->y -= 0.1f;
                            } else if(HuPadStkY[0] >= 36) {
                                scale->y += 0.1f;
                            }
                            if(HuPadSubStkY[0] <= -29) {
                                scale->z += 0.1f;
                            } else if(HuPadSubStkY[0] >= 29) {
                                scale->z -= 0.1f;
                            }
                        }
                    }
                }
                HuSprPosSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_R), 32, 0);
                HuSprPosSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_L), -32, 0);
                sprRot += 2;
                MdMathAngleClamp(&sprRot);
                HuSprGrpZRotSet(grpId, sprRot);
                Hu3D3Dto2D(pos, camera->camera[mdlInfoP->cameraNo].bit, &pos2D);
                HuSprGrpPosSet(grpId, pos2D.x, pos2D.y);
                if(attr & HU3D_ATTR_DISPOFF) {
                    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_R), HUSPR_ATTR_ADDCOL);
                    HuSprAttrSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_L), HUSPR_ATTR_ADDCOL);
                    HuSprGrpTPLvlSet(grpId, 0.4f);
                } else {
                    HuSprAttrReset(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_R), HUSPR_ATTR_ADDCOL);
                    HuSprAttrReset(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_LR, MDSPR_CURSOR_LR_L), HUSPR_ATTR_ADDCOL);
                    HuSprGrpTPLvlSet(grpId, 1.0f);
                }
                MdDebugFontPrint(debugFont, "POS-ADJUST-MODE(%2d / %2d) -> %s", mdlSel, MDMODEL_MAX, mdlInfoP->name);
                if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
                    if(menuSel == 0) {
                        MdDebugFontPrint(debugFont, "*  POS(%.1f / %.1f / %.1f)", pos->x, pos->y, pos->z);
                    } else {
                        MdDebugFontPrint(debugFont, "   POS(%.1f / %.1f / %.1f)", pos->x, pos->y, pos->z);
                    }
                    if(menuSel == 1) {
                        MdDebugFontPrint(debugFont, "*  ROT(%.1f / %.1f / %.1f)", rot->x, rot->y, rot->z);
                    } else {
                        MdDebugFontPrint(debugFont, "   ROT(%.1f / %.1f / %.1f)", rot->x, rot->y, rot->z);
                    }
                    if(menuSel == 2) {
                        MdDebugFontPrint(debugFont, "*SCALE(%.2f / %.2f / %.2f)", scale->x, scale->y, scale->z);
                    } else {
                        MdDebugFontPrint(debugFont, " SCALE(%.2f / %.2f / %.2f)", scale->x, scale->y, scale->z);
                    }
                }
                HuPrcVSleep();
            }
        }
    }
}

/* --- .bss declared last (lowest addresses): mdparty.c capPlayerInitF precedent --- */
/* 0x0 */ s8 lbl_1_bss_0;

