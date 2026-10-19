/*
 * mdbeachDll -- the Bonus Mode game host (mdomakedll -> omOvlCallEx(DLL_mdbeachdll, 1, evtno)):
 * evtno 0 = Beach Volley (m433dll), 1 = Ice Hockey (m580dll); 2 / 3 = back from that game.
 * Player count, character, team, rules and handicap setup, then a call into the minigame; B on the
 * first screen returns to mdomakedll. Decompiled 2026-10-01 from the reference assembly with the
 * mdmini/mdparty/mdomake twins (NOTES.md); functions keep their fn_1_XXXX names.
 */

#include "REL/mdbeachDll.h"

/* mdmini.c/mdomake.c precedent: the particle helpers come from an #included .c, included right
 * after the overlay header. Its HU3DPARMANPARAM statics are .data 0x0-0x13F; its six static
 * functions are emitted last in .text. */
#include "REL/mdbeachDll/effect.c"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/charman.h"
#include "game/armem.h"
#include "math.h"
#include "messnum/teamname.h"
#include "messnum/syshelp.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 90.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 0.0f; /* 0x14 */
/* 0x18 lbl_1_rodata_18 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_20 = 288.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 240.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 750.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 64.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 300.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 1000.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 30.0f; /* 0x38 */
static const float lbl_1_rodata_3C = -1.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 1.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 320.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 280.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 800.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 32.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 15.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 0.5f; /* 0x58 */
static const float lbl_1_rodata_5C = 5.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 8.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 60.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 360.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 0.2f; /* 0x6C */
static const float lbl_1_rodata_70 = 56.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 376.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 340.0f; /* 0x78 */
static const float lbl_1_rodata_7C = -64.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 196.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 120.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 112.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 4.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 176.8f; /* 0x90 */
static const float lbl_1_rodata_94 = -580.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 192.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 640.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 48.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 528.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 26.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = 46.0f; /* 0xAC */
static const float lbl_1_rodata_B0 = 3.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 188.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 208.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 368.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 88.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 224.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 352.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = 232.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 341.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 128.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 448.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 0.7f; /* 0xDC */
static const float lbl_1_rodata_E0 = 24.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 1.5f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 12.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = -2.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 2.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 72.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = -28.0f; /* 0xF8 */
static const float lbl_1_rodata_FC = 176.64f; /* 0xFC */
static const float lbl_1_rodata_100 = 4000.0f; /* 0x100 */
static const float lbl_1_rodata_104 = 168.0f; /* 0x104 */
static const float lbl_1_rodata_108 = 80.0f; /* 0x108 */
static const float lbl_1_rodata_10C = 2500.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 704.0f; /* 0x110 */
static const float lbl_1_rodata_114 = 200.0f; /* 0x114 */
static const float lbl_1_rodata_118 = 20.0f; /* 0x118 */
static const float lbl_1_rodata_11C = 270.0f; /* 0x11C */
static const float lbl_1_rodata_120 = -90.0f; /* 0x120 */
static const double lbl_1_rodata_128 = 3.141592653589793; /* 0x128 */
static const double lbl_1_rodata_130 = 180.0; /* 0x130 */
static const float lbl_1_rodata_138 = 180.0f; /* 0x138 */
static const float lbl_1_rodata_13C = -80.0f; /* 0x13C */
static const float lbl_1_rodata_140 = -8.0f; /* 0x140 */
static const float lbl_1_rodata_144 = -360.0f; /* 0x144 */
static const float lbl_1_rodata_148 = -128.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 252.0f; /* 0x14C */
static const float lbl_1_rodata_150 = 140.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 436.0f; /* 0x154 */
static const float lbl_1_rodata_158 = 108.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 468.0f; /* 0x15C */
static const float lbl_1_rodata_160 = -96.0f; /* 0x160 */
/* 0x164 lbl_1_rodata_164 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x165 gap_03_00000165_rodata: 0x00, 0x00, 0x00 */
/* 0x168 lbl_1_rodata_168 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0x169 lbl_1_rodata_169 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0x16C lbl_1_rodata_16C (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0x16D lbl_1_rodata_16D (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_170 = 0.11111111f; /* 0x170 */
static const float lbl_1_rodata_174 = 10.0f; /* 0x174 */
static const float lbl_1_rodata_178 = 0.05f; /* 0x178 */
static const float lbl_1_rodata_17C = 0.01f; /* 0x17C */
static const float lbl_1_rodata_180 = 0.1f; /* 0x180 */
static const float lbl_1_rodata_184 = -32.0f; /* 0x184 */
static const float lbl_1_rodata_188 = 0.4f; /* 0x188 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x808 */ SYS sysWork;
/* 0x804 */ SYS *sys;
/* 0x800 */ SYS *sysP;
/* 0x7E8 */ HuVecF lbl_1_bss_7E8[2];
/* 0x7D0 */ HuVecF lbl_1_bss_7D0[2];
/* 0x7CC */ float lbl_1_bss_7CC;
/* 0x7C8 */ float lbl_1_bss_7C8;
/* 0x7C4 */ float lbl_1_bss_7C4;
/* 0x7C0 */ float lbl_1_bss_7C0;
/* 0x798 */ s16 lbl_1_bss_798[10][2];
/* 0x748 */ HuVecF *lbl_1_bss_748[10][2]; /* fn_1_19AC: character posP, [chr][normal/game model] */
/* 0x6F8 */ HuVecF *lbl_1_bss_6F8[10][2]; /* fn_1_19AC: rotP */
/* 0x6A8 */ HuVecF *lbl_1_bss_6A8[10][2]; /* fn_1_19AC: scaleP */
/* 0x69C */ HuVecF lbl_1_bss_69C; /* fn_1_19AC */
/* 0x690 */ HuVecF lbl_1_bss_690; /* fn_1_19AC */
/* 0x660 */ HuVecF lbl_1_bss_660[4];
/* 0x65C */ s32 lbl_1_bss_65C;
/* 0x658 */ float lbl_1_bss_658;
/* 0x654 */ float lbl_1_bss_654;
/* 0x650 */ float lbl_1_bss_650;
/* 0x638 */ HuVecF lbl_1_bss_638[2];
/* 0x62C */ HuVecF lbl_1_bss_62C;
/* 0x5FC */ HuVecF lbl_1_bss_5FC[4];
/* 0x5E4 */ HuVecF lbl_1_bss_5E4[2];
/* 0x5DC */ s8 lbl_1_bss_5DC[4][2];
/* 0x5D8 */ float lbl_1_bss_5D8;
/* 0x5D4 */ float lbl_1_bss_5D4;
/* 0x5A4 */ HuVecF lbl_1_bss_5A4[4];
/* 0x574 */ MDBEACH_CAP_ANIM lbl_1_bss_574[4];
/* 0x484 */ HuVecF lbl_1_bss_484[10][2];
/* 0x394 */ HuVecF lbl_1_bss_394[10][2];
/* 0x392 gap_05_00000392_bss (0x2): alignment gap */
/* 0x390 */ s16 lbl_1_bss_390;
/* 0x318 */ MDBEACH_CAP_ANIM lbl_1_bss_318[10];
/* 0x258 */ HuVecF lbl_1_bss_258[4][4]; /* fn_1_EC34: per player 2D path points */
/* 0x198 */ HuVecF lbl_1_bss_198[4][4]; /* fn_1_EC34: per player 3D path points */
/* 0x138 */ HuVecF lbl_1_bss_138[4][2]; /* fn_1_EC34: saved 3D start points */
/* 0x118 */ float lbl_1_bss_118[4][2]; /* fn_1_EC34: rotY from/to (param 5) */
/* 0xE8 */ MDBEACH_JUMP lbl_1_bss_E8[4]; /* fn_1_EC34: per player jump state */
/* 0xE4 */ MDBEACH_JUMP_LAST lbl_1_bss_E4; /* fn_1_EC34: the player with the longest delay (2 bytes; dtk sized it 1) */
/* 0xD4 */ MDBEACH_EFFECT *lbl_1_bss_D4[4]; /* fn_1_EC34: ParticleGlow per player (param 5) */
/* 0xA4 */ float lbl_1_bss_A4[12];
/* 0x8C */ float lbl_1_bss_8C[6];
/* 0x5C */ HuVecF lbl_1_bss_5C[2][2]; /* fn_1_12E6C: 2D ball positions (Hu3D2Dto3D in) */
/* 0x2C */ HuVecF lbl_1_bss_2C[2][2]; /* fn_1_12E6C: 3D ball positions (Hu3D2Dto3D out) */
/* 0x28 */ s32 lbl_1_bss_28;
/* 0x4 */ extern s8 lbl_1_bss_4; /* defined after the last function (declaration order = .bss order) */
/* 0x0 */ extern s32 lbl_1_bss_0; /* defined after the last function */

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x144 */ char *lbl_1_data_144[1] = {
    "26"
};
/* 0x148 */ OMOVL lbl_1_data_148[2] = { DLL_m433dll, DLL_m580dll }; /* fn_1_79EC: the game per gameType */
/* 0x150 */ u32 lbl_1_data_150[2] = { DATA_m433, DATA_m580 };
/* 0x158 */ HuVecF lbl_1_data_158[2][10] = { /* fn_1_D45C/fn_1_EC34: [gameType][chr] (mulli 120) */
    { { 70.0f, 204.0f, 450.0f }, { 150.0f, 240.0f, 450.0f }, { 229.0f, 224.0f, 450.0f }, { 328.0f, 179.0f, 450.0f }, { 413.0f, 245.0f, 450.0f }, { 514.0f, 215.0f, 450.0f }, { 80.0f, 350.0f, 450.0f }, { 190.0f, 359.0f, 450.0f }, { 393.0f, 370.0f, 450.0f }, { 508.0f, 353.0f, 450.0f } },
    { { 76.0f, 194.0f, 450.0f }, { 138.0f, 265.0f, 450.0f }, { 234.0f, 216.0f, 450.0f }, { 322.0f, 194.0f, 450.0f }, { 400.0f, 255.0f, 450.0f }, { 499.0f, 211.0f, 450.0f }, { 66.0f, 354.0f, 450.0f }, { 183.0f, 365.0f, 450.0f }, { 392.0f, 374.0f, 450.0f }, { 497.0f, 358.0f, 450.0f } }
};
/* 0x248 */ HuVecF lbl_1_data_248[2][10] = { /* fn_1_146D0: finger 2D offset per gameType and character */
    { { -25.0f, -140.0f, 2500.0f }, { -25.0f, -140.0f, 2500.0f }, { -28.0f, -160.0f, 2500.0f }, { -55.0f, -114.0f, 2500.0f }, { -33.0f, -147.0f, 2500.0f }, { -28.0f, -152.0f, 2500.0f }, { -26.0f, -153.0f, 2500.0f }, { -31.0f, -116.0f, 2500.0f }, { -26.0f, -133.0f, 2500.0f }, { -31.0f, -133.0f, 2500.0f } },
    { { -25.0f, -132.0f, 2500.0f }, { -25.0f, -143.0f, 2500.0f }, { -25.0f, -152.0f, 2500.0f }, { -27.0f, -130.0f, 2500.0f }, { -31.0f, -131.0f, 2500.0f }, { -27.0f, -147.0f, 2500.0f }, { -25.0f, -157.0f, 2500.0f }, { -24.0f, -126.0f, 2500.0f }, { -27.0f, -129.0f, 2500.0f }, { -27.0f, -127.0f, 2500.0f } }
};
/* 0x338 */ HuVecF lbl_1_data_338[2][10] = { /* fn_1_19AC, fn_1_EC34: [gameType][chr] (mulli 120) */
    { { 0.0f, -30.0f, 1500.0f }, { 0.0f, -30.0f, 1500.0f }, { -8.0f, -17.0f, 1500.0f }, { -24.0f, -2.0f, 1500.0f }, { -8.0f, -26.0f, 1500.0f }, { -1.0f, -16.0f, 1500.0f }, { 0.0f, -16.0f, 1500.0f }, { 0.0f, -30.0f, 1500.0f }, { 0.0f, -24.0f, 1500.0f }, { 7.0f, -39.0f, 1500.0f } },
    { { 0.0f, -30.0f, 1500.0f }, { 4.0f, -30.0f, 1500.0f }, { -3.0f, -17.0f, 1500.0f }, { 2.0f, -27.0f, 1500.0f }, { 3.0f, -29.0f, 1500.0f }, { -1.0f, -16.0f, 1500.0f }, { 0.0f, -16.0f, 1500.0f }, { 0.0f, -30.0f, 1500.0f }, { 0.0f, -29.0f, 1500.0f }, { -1.0f, -39.0f, 1500.0f } }
};
/* 0x428 */ HuVecF lbl_1_data_428[2][10] = { /* fn_1_19AC: [gameType][chr] (mulli 120) */
    { { 0.0f, -60.0f, 1440.0f }, { 0.0f, -65.0f, 1440.0f }, { 0.0f, -70.0f, 1480.0f }, { 0.0f, -60.0f, 1440.0f }, { 0.0f, -50.0f, 1480.0f }, { 0.0f, -65.0f, 1470.0f }, { 0.0f, -65.0f, 1460.0f }, { 2.0f, -50.0f, 1440.0f }, { 30.0f, -55.0f, 1450.0f }, { 10.0f, -45.0f, 1490.0f } },
    { { 0.0f, -60.0f, 1440.0f }, { 0.0f, -65.0f, 1440.0f }, { 0.0f, -70.0f, 1480.0f }, { 0.0f, -60.0f, 1440.0f }, { 0.0f, -50.0f, 1480.0f }, { 0.0f, -65.0f, 1470.0f }, { 0.0f, -65.0f, 1460.0f }, { 2.0f, -50.0f, 1440.0f }, { 30.0f, -55.0f, 1450.0f }, { 10.0f, -45.0f, 1490.0f } }
};
/* 0x518 */ HuVecF lbl_1_data_518[10] = { { 0.0f, -85.0f, 0.0f }, { 0.0f, -90.0f, 0.0f }, { 0.0f, -102.0f, 0.0f }, { 0.0f, -84.0f, 0.0f }, { 0.0f, -80.0f, 0.0f }, { 0.0f, -102.0f, 0.0f }, { 0.0f, -115.0f, 0.0f }, { 0.0f, -66.0f, 0.0f }, { 0.0f, -80.0f, 0.0f }, { 0.0f, -60.0f, 0.0f } };
/* 0x590 */ MD_FUNC MdFlowTbl[MDBEACH_FLOW_MAX] = { fn_1_2D3C, fn_1_31A8, fn_1_4138, fn_1_57A8, fn_1_6E9C, fn_1_79EC };
/* 0x5A8 */ MD_PROC MdProcTbl[MDBEACH_PROC_MAX] = { fn_1_9A14, fn_1_9BAC, fn_1_9D58, fn_1_B1E8, fn_1_B91C, fn_1_D45C, fn_1_EC34, fn_1_118D0, fn_1_12314, fn_1_12894, fn_1_12E6C, fn_1_13A2C, fn_1_13850 };

/* 445 insns; twin: mdomake ObjectSetup (sets mgPauseExitF; evtNo 0/2 Beach Volley, 1/3 Ice Hockey) */
void ObjectSetup(void)
{
    sys = &sysWork;
    sysP = sys;
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowTime = 0;
    sys->flowMode = MDBEACH_FLOW_INIT;
    sys->ovlCallMode = MD_OVLCALL_GOTO;
    sys->nextDll = DLL_selmenuDLL;
    sys->exitF = FALSE;
    sys->skipWipeF = FALSE;
    mgPauseExitF = TRUE;
    sys->objman = omInitObjMan(512, 8192);
    sys->ovlHis = omOvlHisGet(0);
    sys->evtNo = sys->ovlHis->evtno;
    if(sys->evtNo == 0 || sys->evtNo == 2) {
        sys->gameType = 0;
    } else {
        sys->gameType = 1;
    }
    omGameSysInit(sys->objman);
    sys->obj[MDBEACH_OBJ_DEBUGFONT] = omAddObj(sys->objman, 100, 0, 0, MdObjDebugFontCreate);
    sys->obj[MDBEACH_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDBEACH_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDBEACH_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDBEACH_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDBEACH_OBJ_PAD] = omAddObj(sys->objman, 101, 0, 0, MdObjPadMain);
    sys->obj[MDBEACH_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDBEACH_OBJ_PAD]->data) {
        OSReport("sys->obj[MDBEACH_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDBEACH_OBJ_PAD]->data;
    sys->obj[MDBEACH_OBJ_CAMERA] = omAddObj(sys->objman, 102, 0, 0, MdObjCameraCreate);
    sys->obj[MDBEACH_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDBEACH_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDBEACH_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDBEACH_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDBEACH_OBJ_LIGHT] = omAddObj(sys->objman, 103, 0, 0, MdObjLightCreate);
    sys->obj[MDBEACH_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDBEACH_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDBEACH_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDBEACH_OBJ_LIGHT]->data;
    sys->light->createF = FALSE;
    sys->light->debugFont = sys->debugFont;
    sys->sprite = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDSPRITE_WORK), HU_MEMNUM_OVL);
    if(!sys->sprite) {
        OSReport("sys->sprite = NULL...\n");
    }
    sys->model = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDMODEL_WORK), HU_MEMNUM_OVL);
    if(!sys->model) {
        OSReport("sys->model = NULL...\n");
    }
    sys->star = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDBEACH_STAR), HU_MEMNUM_OVL);
    if(!sys->star) {
        OSReport("sys->star = NULL...\n");
    }
    sys->mess = HuMemDirectMallocNum(HEAP_MODEL, sizeof(MDMESS_WORK), HU_MEMNUM_OVL);
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
    sys->mainProc = HuPrcChildCreate(MdMain, 104, 12288, 0, sys->objman);
}

/* 49 insns; twin: mdsel MdMain */
void MdMain(void)
{
    MdInit();
    while(!omSysExitReq && !sys->exitF) {
        MdFlowTbl[sys->flowMode]();
        if(++sys->flowTime > 36000) {
            sys->flowTime = 0;
        }
        HuPrcVSleep();
    }
    MdClose();
}

/* 118 insns; twin: mdparty LoadProc. loadState 0 idle, 1 load sys->loadDir into ARAM, 2 wait for
 * loadProcReady, 3 start the four characters' motions, 4 end */
static void LoadProc(void)
{
    OSTick tick;
    int i;
    while(1) {
        switch(sys->loadState) {
            case 0:
                break;

            case 1:
                CharDataClose(-1);
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(sys->loadDir);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                HuAR_MRAMtoARAM(sys->loadDir);
                while(HuARDMACheck());
                HuDataDirClose(sys->loadDir);
                sys->loadProcReady = 0;
                sys->loadState = 2;
                break;

            case 2:
                if(sys->loadProcReady == 1) {
                    sys->loadState = 3;
                }
                break;

            case 3:
                for(i=0; i<4; i++) {
                    CharMotionInitAsync(sys->chrSel[i]);
                }
                sys->loadState = 4;
                break;

            case 4:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 0x704 */ HuVecF lbl_1_data_704 = { 288.0f, 310.0f, 1250.0f }; /* fn_1_A30: the star's corner position (2D) */

/* 735 insns; twin: mdomake fn_1_938 (mdsel StarUpdate). star->mode: 0 none, 1 enter start, 2 enter,
 * 3 entered, 4 exit start, 5 exit, 6 gone, 7 to-corner start, 8 to corner, 9 in the corner,
 * 10 snap to the corner, 11 low-to-corner start, 12 low to corner, 13 done */
void fn_1_A30(void)
{
    MDBEACH_STAR *star; //r31
    MDMODEL_WORK *model; //r30
    int i; //r29
    HuVecF *pos; //r28
    MDCAMERA_WORK *camera; //r27
    MDMESS_WORK *mess; //r26
    HuVecF *rot; //r25
    HuVecF *scale; //r24

    model = sys->model;
    camera = sys->camera;
    mess = sys->mess;
    star = sys->star;
    pos = model->posP[MDMODEL_STAR];
    rot = model->rotP[MDMODEL_STAR];
    scale = model->scaleP[MDMODEL_STAR];
    star->mode = 0;
    star->motNext = 1;
    lbl_1_bss_7E8[0].x = 288;
    lbl_1_bss_7E8[0].y = 240;
    lbl_1_bss_7E8[0].z = 750;
    Hu3D2Dto3D(&lbl_1_bss_7E8[0], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[0]);
    *pos = lbl_1_bss_7D0[0];
    while(1) {
        model = sys->model;
        camera = sys->camera;
        mess = sys->mess;
        star = sys->star;
        pos = model->posP[MDMODEL_STAR];
        rot = model->rotP[MDMODEL_STAR];
        scale = model->scaleP[MDMODEL_STAR];
        switch(star->mode) {
            case 1:
                lbl_1_bss_7CC = 0;
                lbl_1_bss_7C8 = 0;
                lbl_1_bss_7C4 = 0;
                lbl_1_bss_7C0 = 0;
                lbl_1_bss_7E8[0].x = 288;
                lbl_1_bss_7E8[0].y = 240;
                lbl_1_bss_7E8[0].z = 750;
                lbl_1_bss_7E8[1].x = 64;
                lbl_1_bss_7E8[1].y = 300;
                lbl_1_bss_7E8[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_7E8[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[i]);
                }
                star->mode = 2;
                break;

            case 2:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_7CC, &lbl_1_bss_7C4, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_7C8, &lbl_1_bss_7C0, 30);
                MdMathLerp(&pos->x, lbl_1_bss_7D0[0].x, lbl_1_bss_7D0[1].x, lbl_1_bss_7C4);
                MdMathLerp(&pos->y, lbl_1_bss_7D0[0].y, lbl_1_bss_7D0[1].y, lbl_1_bss_7C4);
                MdMathLerpOfs(&pos->z, lbl_1_bss_7D0[0].z, lbl_1_bss_7D0[1].z, lbl_1_bss_7C4, -1*lbl_1_bss_7C0);
                if(lbl_1_bss_7CC >= 1) {
                    star->mode = 3;
                }
                break;

            case 4:
                lbl_1_bss_7CC = 0;
                lbl_1_bss_7C8 = 0;
                lbl_1_bss_7C4 = 0;
                lbl_1_bss_7C0 = 0;
                lbl_1_bss_7E8[0].x = 64;
                lbl_1_bss_7E8[0].y = 320;
                lbl_1_bss_7E8[0].z = 1000;
                lbl_1_bss_7E8[1].x = 288;
                lbl_1_bss_7E8[1].y = 240;
                lbl_1_bss_7E8[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_7E8[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[i]);
                }
                star->mode = 5;
                break;

            case 5:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_7CC, &lbl_1_bss_7C4, 30);
                MdMathLerp(&pos->x, lbl_1_bss_7D0[0].x, lbl_1_bss_7D0[1].x, lbl_1_bss_7C4);
                MdMathLerp(&pos->y, lbl_1_bss_7D0[0].y, lbl_1_bss_7D0[1].y, lbl_1_bss_7C4);
                MdMathLerp(&pos->z, lbl_1_bss_7D0[0].z, lbl_1_bss_7D0[1].z, lbl_1_bss_7C4);
                if(lbl_1_bss_7CC >= 1) {
                    star->mode = 6;
                }
                break;

            case 7:
                lbl_1_bss_7CC = 0;
                lbl_1_bss_7C8 = 0;
                lbl_1_bss_7C4 = 0;
                lbl_1_bss_7C0 = 0;
                lbl_1_bss_7E8[0].x = 288;
                lbl_1_bss_7E8[0].y = 240;
                lbl_1_bss_7E8[0].z = 750;
                lbl_1_bss_7E8[1] = lbl_1_data_704;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_7E8[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[i]);
                }
                star->mode = 8;
                break;

            case 8:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_7CC, &lbl_1_bss_7C4, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_7C8, &lbl_1_bss_7C0, 30);
                MdMathLerp(&pos->x, lbl_1_bss_7D0[0].x, lbl_1_bss_7D0[1].x, lbl_1_bss_7C4);
                MdMathLerp(&pos->y, lbl_1_bss_7D0[0].y, lbl_1_bss_7D0[1].y, lbl_1_bss_7C4);
                MdMathLerpOfs(&pos->z, lbl_1_bss_7D0[0].z, lbl_1_bss_7D0[1].z, lbl_1_bss_7C4, -1*lbl_1_bss_7C0);
                if(lbl_1_bss_7CC >= 1) {
                    star->mode = 9;
                }
                break;

            case 10:
                lbl_1_bss_7E8[1] = lbl_1_data_704;
                Hu3D2Dto3D(&lbl_1_bss_7E8[1], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[1]);
                *pos = lbl_1_bss_7D0[1];
                star->mode = 9;
                break;

            case 11:
                lbl_1_bss_7CC = 0;
                lbl_1_bss_7C8 = 0;
                lbl_1_bss_7C4 = 0;
                lbl_1_bss_7C0 = 0;
                lbl_1_bss_7E8[0].x = 288;
                lbl_1_bss_7E8[0].y = 280;
                lbl_1_bss_7E8[0].z = 800;
                lbl_1_bss_7E8[1] = lbl_1_data_704;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_7E8[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_7D0[i]);
                }
                star->mode = 12;
                break;

            case 12:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_7CC, &lbl_1_bss_7C4, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_7C8, &lbl_1_bss_7C0, 30);
                MdMathLerp(&pos->x, lbl_1_bss_7D0[0].x, lbl_1_bss_7D0[1].x, lbl_1_bss_7C4);
                MdMathLerp(&pos->y, lbl_1_bss_7D0[0].y, lbl_1_bss_7D0[1].y, lbl_1_bss_7C4);
                MdMathLerpOfs(&pos->z, lbl_1_bss_7D0[0].z, lbl_1_bss_7D0[1].z, lbl_1_bss_7C4, -1*lbl_1_bss_7C0);
                if(lbl_1_bss_7CC >= 1) {
                    star->mode = 13;
                }
                break;

            case 0:
            case 3:
            case 6:
            case 9:
            case 13:
                break;
        }
        switch(star->motNext) {
            case 0:
                break;

            case 1:
                Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE]);
                star->motNext = 0;
                break;

            case 2:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_TALK], 0, 32, HU3D_MOTATTR_LOOP);
                star->motNext = 0;
                break;

            case 3:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_IDLE], 0, 32, HU3D_MOTATTR_LOOP);
                star->motNext = 0;
                break;
        }
        fn_1_15418(MDMODEL_STAR, MDCAMERA_MAIN);
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 256 insns; twin: mdmini fn_1_1804 (mdparty PlayerSprUpdate). playerSpr->mode: 0 none, 1 grow start,
 * 2 grow, 3 shown, 4 shrink start, 5 shrink, 6 hidden */
void fn_1_15AC(void)
{
    MDBEACH_PLAYERSPR *playerSpr; //r31
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
        playerSpr->mode = 0;
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
                case 0:
                    break;

                case 1:
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
                    playerSpr->mode = 2;
                    break;

                case 2:
                    MdMathOscillate(MDMATH_OSC_90, &playerSpr->time, &playerSpr->t, 15);
                    MdMathOscillate(MDMATH_OSC_180, &playerSpr->ofsTime, &playerSpr->ofsT, 15);
                    MdMathLerpOfs(&playerNoScale->x, 0, 1, playerSpr->t, 0.5f*playerSpr->ofsT);
                    playerNoScale->y = playerNoScale->x;
                    MdMathLerpOfs(&comDifScale->x, 0, 1, playerSpr->t, 0.5f*playerSpr->ofsT);
                    comDifScale->y = comDifScale->x;
                    if(playerSpr->time >= 1) {
                        playerSpr->mode = 3;
                    }
                    break;

                case 3:
                    break;

                case 4:
                    playerSpr->time = 0;
                    playerSpr->ofsTime = 0;
                    playerSpr->t = 0;
                    playerSpr->ofsT = 0;
                    playerSpr->mode = 5;
                    break;

                case 5:
                    MdMathOscillate(MDMATH_OSC_90, &playerSpr->time, &playerSpr->t, 15);
                    MdMathLerp(&playerNoScale->x, 1, 0, playerSpr->t);
                    playerNoScale->y = playerNoScale->x;
                    MdMathLerp(&comDifScale->x, 1, 0, playerSpr->t);
                    comDifScale->y = comDifScale->x;
                    if(playerSpr->time >= 1) {
                        HuSprDispOff(playerNoGrpId, i);
                        HuSprDispOff(comDifGrpId, i);
                        playerSpr->mode = 6;
                    }
                    break;

                case 6:
                    break;
            }
        }
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 0x764 */ s32 lbl_1_data_764[4] = { 0x0, 0x0, 0x0, 0x0 };
/* 746 insns; the character models of the four players (Party-mode chr is a twin by idiom only).
 * lbl_1_bss_798/748/6F8/6A8 [chr][0] = the normal model's id/pos/rot/scale, [chr][1] = the
 * gameType's model (Volley or Hockey). unk204[i].mode: 0 none, 1 appear, 2 wait for the player
 * number, 3 idle (motion to idle once), 4 idle now, 5 hide, 6 hidden, 7 done */
void fn_1_19AC(void)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    MDBEACH_PLAYERSPR *chrPlayer; //r29
    MDCAMERA_WORK *camera; //r28
    MDBEACH_PLAYERSPR *playerSpr; //r27
    MDSPRITE_WORK *sprite; //r26
    BOOL motEndF; //r25

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerSpr = &sys->playerSpr[0];
    for(chrPlayer=&sys->unk204[0], i=0; i<4; i++, chrPlayer++) {
        chrPlayer->mode = 0;
    }
    for(i=0; i<10; i++) {
        lbl_1_bss_798[i][0] = model->mdlId[i+MDMODEL_MARIO];
        lbl_1_bss_748[i][0] = model->posP[i+MDMODEL_MARIO];
        lbl_1_bss_6F8[i][0] = model->rotP[i+MDMODEL_MARIO];
        lbl_1_bss_6A8[i][0] = model->scaleP[i+MDMODEL_MARIO];
        if(sys->gameType == 0) {
            lbl_1_bss_798[i][1] = model->mdlId[i+MDMODEL_MARIO_VOLLEY];
            lbl_1_bss_748[i][1] = model->posP[i+MDMODEL_MARIO_VOLLEY];
            lbl_1_bss_6F8[i][1] = model->rotP[i+MDMODEL_MARIO_VOLLEY];
            lbl_1_bss_6A8[i][1] = model->scaleP[i+MDMODEL_MARIO_VOLLEY];
        } else if(sys->gameType == 1) {
            lbl_1_bss_798[i][1] = model->mdlId[i+MDMODEL_MARIO_HOCKEY];
            lbl_1_bss_748[i][1] = model->posP[i+MDMODEL_MARIO_HOCKEY];
            lbl_1_bss_6F8[i][1] = model->rotP[i+MDMODEL_MARIO_HOCKEY];
            lbl_1_bss_6A8[i][1] = model->scaleP[i+MDMODEL_MARIO_HOCKEY];
        }
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        playerSpr = &sys->playerSpr[0];
        for(chrPlayer=&sys->unk204[0], i=0; i<4; i++, chrPlayer++) {
            switch(chrPlayer->mode) {
                case 0:
                    break;

                case 1:
                    Hu3DModelAttrSet(lbl_1_bss_798[sys->chrSel[i]][1], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_798[sys->chrSel[i]][0], HU3D_ATTR_DISPOFF);
                    if(sys->chrSel[i] == 8) {
                        Hu3DModelLayerSet(lbl_1_bss_798[sys->chrSel[i]][0], 2);
                    } else {
                        Hu3DModelLayerSet(lbl_1_bss_798[sys->chrSel[i]][0], 1);
                    }
                    Hu3D3Dto2D(lbl_1_bss_748[sys->chrSel[i]][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_690);
                    lbl_1_bss_690.x = lbl_1_bss_690.x+lbl_1_data_338[sys->gameType][sys->chrSel[i]].x;
                    lbl_1_bss_690.y += lbl_1_data_338[sys->gameType][sys->chrSel[i]].y;
                    lbl_1_bss_690.z = lbl_1_data_338[sys->gameType][sys->chrSel[i]].z;
                    Hu3D2Dto3D(&lbl_1_bss_690, camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_69C);
                    *lbl_1_bss_748[sys->chrSel[i]][0] = lbl_1_bss_69C;
                    fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
                    fn_1_15A40(sys->chrSel[i]+MDBEACH_AUD_SE_CHR_VOICE);
                    Hu3D3Dto2D(lbl_1_bss_748[sys->chrSel[i]][0], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_690);
                    lbl_1_bss_690.x = lbl_1_bss_690.x+lbl_1_data_428[sys->gameType][sys->chrSel[i]].x;
                    lbl_1_bss_690.y += lbl_1_data_428[sys->gameType][sys->chrSel[i]].y;
                    lbl_1_bss_690.z = lbl_1_data_428[sys->gameType][sys->chrSel[i]].z;
                    Hu3D2Dto3D(&lbl_1_bss_690, camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_69C);
                    Hu3DModelAttrReset(model->mdlId[i+MDMODEL_FLASH_1P], HU3D_ATTR_DISPOFF);
                    *model->posP[i+MDMODEL_FLASH_1P] = lbl_1_bss_69C;
                    Hu3DModelAttrReset(model->mdlId[i+MDMODEL_FLASH_1P], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(model->mdlId[i+MDMODEL_FLASH_1P], HU3D_MOTATTR_PAUSE);
                    Hu3DMotionSpeedSet(model->mdlId[i+MDMODEL_FLASH_1P], 5);
                    Hu3DMotionTimeSet(model->mdlId[i+MDMODEL_FLASH_1P], 0);
                    if(sys->chrSel[i] == 8) {
                        Hu3DModelLayerSet(model->mdlId[i+MDMODEL_FLASH_1P], 2);
                    } else {
                        Hu3DModelLayerSet(model->mdlId[i+MDMODEL_FLASH_1P], 1);
                    }
                    fn_1_146D0();
                    Hu3DMotionSet(lbl_1_bss_798[sys->chrSel[i]][0], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR+1]);
                    Hu3DModelAttrReset(lbl_1_bss_798[sys->chrSel[i]][0], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(lbl_1_bss_798[sys->chrSel[i]][0], HU3D_MOTATTR_PAUSE);
                    lbl_1_data_764[i] = FALSE;
                    playerSpr[i].mode = 1;
                    chrPlayer->mode = 2;
                    break;

                case 2:
                    if(playerSpr[i].mode == 3) {
                        chrPlayer->mode = 3;
                    }
                    break;

                case 3:
                    motEndF = FALSE;
                    if(!lbl_1_data_764[i]) {
                        motEndF = Hu3DMotionEndCheck(lbl_1_bss_798[sys->chrSel[i]][0]);
                        if(motEndF == TRUE) {
                            Hu3DMotionShiftSet(lbl_1_bss_798[sys->chrSel[i]][0], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR], 0, 32, HU3D_MOTATTR_LOOP);
                            lbl_1_data_764[i] = TRUE;
                        }
                    }
                    break;

                case 4:
                    lbl_1_data_764[i] = TRUE;
                    chrPlayer->mode = 3;
                    break;

                case 5:
                    Hu3DModelAttrSet(lbl_1_bss_798[sys->chrSel[i]][0], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_798[sys->chrSel[i]][1], HU3D_ATTR_DISPOFF);
                    if(sys->unk36[i] != 0 && sys->unk36[i] == 1) {
                        sys->unk36[i] = 0;
                    }
                    playerSpr[i].mode = 0;
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], i);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], i);
                    Hu3DModelAttrSet(model->mdlId[i+MDMODEL_FLASH_1P], HU3D_ATTR_DISPOFF);
                    chrPlayer->mode = 6;
                    break;

                case 6:
                    chrPlayer->mode = 7;
                    break;

                case 7:
                    break;
            }
        }
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 221 insns; the character turntable (twin: mdstory fn_1_1728). chr->mode: 0 none, 1 spin-up start,
 * 2 spin up to 8 deg/frame (unk14 speed, unk18 its start), 3 spin, 4 stop start (unk1C start
 * angle), 5 settle on 360, 6 stopped. The model set is the gameType's (Volley / Hockey). */
void fn_1_2554(void)
{
    MDBEACH_CHR *chr; //r31
    int i; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *rotP; //r28
    MDCAMERA_WORK *camera; //r27
    MDSPRITE_WORK *sprite; //r26
    HuVecF *posP; //r25
    HuVecF *scaleP; //r24

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    for(chr=&sys->chr[0], i=0; i<10; i++, chr++) {
        chr->unk14 = 0;
        chr->mode = 0;
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        for(chr=&sys->chr[0], i=0; i<10; i++, chr++) {
            if(sys->gameType == 0) {
                posP = model->posP[i+MDMODEL_MARIO_VOLLEY];
                rotP = model->rotP[i+MDMODEL_MARIO_VOLLEY];
                scaleP = model->scaleP[i+MDMODEL_MARIO_VOLLEY];
            } else if(sys->gameType == 1) {
                posP = model->posP[i+MDMODEL_MARIO_HOCKEY];
                rotP = model->rotP[i+MDMODEL_MARIO_HOCKEY];
                scaleP = model->scaleP[i+MDMODEL_MARIO_HOCKEY];
            }
            switch(chr->mode) {
                case 0:
                    break;

                case 1:
                    chr->time = 0;
                    chr->ofsTime = 0;
                    chr->t = 0;
                    chr->ofsT = 0;
                    chr->unk18 = chr->unk14;
                    chr->mode = 2;
                    break;

                case 2:
                    MdMathOscillate(MDMATH_OSC_90_REV, &chr->time, &chr->t, 30);
                    MdMathLerp(&chr->unk14, chr->unk18, 8, chr->t);
                    rotP->y += chr->unk14;
                    MdMathAngleClamp(&rotP->y);
                    if(chr->time >= 1) {
                        chr->mode = 3;
                    }
                    break;

                case 3:
                    rotP->y += chr->unk14;
                    MdMathAngleClamp(&rotP->y);
                    break;

                case 4:
                    chr->time = 0;
                    chr->ofsTime = 0;
                    chr->t = 0;
                    chr->ofsT = 0;
                    chr->unk1C = rotP->y;
                    chr->mode = 5;
                    break;

                case 5:
                    MdMathOscillate(MDMATH_OSC_90, &chr->time, &chr->t, 60);
                    MdMathOscillate(MDMATH_OSC_180, &chr->ofsTime, &chr->ofsT, 60);
                    MdMathLerpOfs(&rotP->y, chr->unk1C, 360, chr->t, 0.2f*chr->ofsT);
                    if(chr->time >= 1) {
                        MdMathAngleClamp(&rotP->y);
                        chr->mode = 6;
                    }
                    break;

                case 6:
                    break;
            }
        }
        HuPrcVSleep();
    }
}

/* 17 insns; twin: mdmini fn_1_2018 */
void fn_1_28C8(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_MAIN);
        HuPrcVSleep();
    }
}

/* 23 insns; twin: mdparty TextWinUpdate */
void fn_1_290C(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_HELP);
        MdMessMain(mess, MDMESS_WIN_3);
        MdMessMain(mess, MDMESS_WIN_4);
        HuPrcVSleep();
    }
}

/* 17 insns; twin: mdmini fn_1_2018 (window 2) */
void fn_1_2968(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_2);
        HuPrcVSleep();
    }
}

/* 160 insns */
void MdInit(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdModelCreate(sys->model, sys->camera);
    HuPrcVSleep();
    HuDataDirClose(DATA_mdbeach);
    HuPrcVSleep();
    MdToueiMdlInit();
    sys->starProc = HuPrcChildCreate(fn_1_A30, 106, 12288, 0, sys->objman);
    sys->chrProc = HuPrcChildCreate(fn_1_2554, 107, 12288, 0, sys->objman);
    sys->unk70Proc = HuPrcChildCreate(fn_1_19AC, 108, 12288, 0, sys->objman);
    sys->playerSprProc = HuPrcChildCreate(fn_1_15AC, 109, 12288, 0, sys->objman);
    sys->mainWinProc = HuPrcChildCreate(fn_1_28C8, 110, 4096, 0, sys->objman);
    sys->textWinProc = HuPrcChildCreate(fn_1_290C, 111, 4096, 0, sys->objman);
    sys->unk80Proc = HuPrcChildCreate(fn_1_2968, 112, 4096, 0, sys->objman);
    sys->loadState = 0;
    sys->loadAsyncStat = 0;
    sys->loadProcReady = FALSE;
    sys->loadDir = DATA_mdomake;
    sys->loadProc = HuPrcChildCreate(LoadProc, 105, 12288, 0, sys->objman);
    HuPrcVSleep();
}

/* 68 insns */
void MdClose(void)
{
    if(!sys->skipWipeF) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeWait();
    }
    HuAudAllStop();
    MdMessKill(sys->mess);
    if(sys->ovlCallMode == MD_OVLCALL_GOTO) {
        omOvlGotoEx(sys->nextDll, 1, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_CALL) {
        omOvlCallEx(sys->nextDll, 1, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_RETURN) {
        omOvlReturnEx(1, 1);
    }
    HuPrcEnd();
    while(1) {
        HuPrcVSleep();
    }
}

/* 283 insns */
void fn_1_2D3C(void)
{
    int i;
    MDMODEL_WORK *model;
    MDSPRITE_WORK *sprite;

    MDCAMERA_WORK *camera;
    MDMESS_WORK *mess;

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_COMDIF, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_5, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_6, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_7, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_8, FALSE);
    HuSprAttrReset(sprite->grpId[MDSPR_GRP_5], sys->gameType, HUSPR_ATTR_DISPOFF);
    HuSprAttrReset(sprite->grpId[MDSPR_GRP_5], 2, HUSPR_ATTR_DISPOFF);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_ATTR_DISPOFF);
    for(i=0; i<10; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<10; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO_VOLLEY], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<10; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO_HOCKEY], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<8; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_CAP_MAN_1P], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_FLASH_1P], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<2; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_VS_VOLLEY], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<3; i++) {
        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_BALL_NORMAL], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(model->mdlId[MDMODEL_FONTBGFILTER], HU3D_ATTR_DISPOFF);
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
    MdProcCall(MDBEACH_PROC_RESET, 0);
    HuPrcVSleep();
    if(sys->evtNo == 0 || sys->evtNo == 1) {
        sys->loadState = 1;
        sys->loadDir = lbl_1_data_150[sys->gameType];
    } else {
        CharDataClose(-1);
        sys->loadState = 2;
        sys->loadProcReady = FALSE;
    }
    if(sys->evtNo <= 1) {
        sys->subMode = 0;
        sys->flowMode = MDBEACH_FLOW_START;
    } else {
        sys->subMode = 10;
        sys->flowMode = MDBEACH_FLOW_HANDICAP;
    }
}

/* 996 insns */
void fn_1_31A8(void)
{
    MDMESS_WORK *mess; //r31
    MDBEACH_STAR *star; //r30
    int choice; //r29

    MDMODEL_WORK *model; //sp+0x8

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            lbl_1_bss_0 = FALSE;
            sys->subMode = 1;
            break;

        case 1:
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            fn_1_15A40(MDBEACH_AUD_MUS_START);
            WipeWait();
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            MdMessWinOpen(mess, MDMESS_WIN_HELP, 1, 0, 0, 1, 32, 340, 512, 32, 0);
            MdMessWinOpen(mess, MDMESS_WIN_3, 1, 0, 0, 3, 288, -64, 224, 32, 0);
            MdMessWinOpen(mess, MDMESS_WIN_4, 1, 0, 0, 4, 288, -64, 224, 32, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_3, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_4, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_3, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_4, HUWIN_ATTR_ALIGN_CENTER);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            fn_1_15A40(MDBEACH_AUD_SE_STAR);
            if(sys->gameType == 0) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 0), MDMESS_WIN_LIST_END);
            } else if(sys->gameType == 1) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 0), MDMESS_WIN_LIST_END);
            }
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            /* retail: the "explain the rules?" question is Beach Volley's message for both games */
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_BEACH_VOLLEY, 1), MDMESS_WIN_LIST_END);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
            if(choice == -1 || choice == 1) {
                lbl_1_bss_0 = FALSE;
            } else if(choice == 0) {
                lbl_1_bss_0 = TRUE;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdProcWait(MDBEACH_PROC_NAME, 0);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                star->motNext = 3;
                star->mode = 7;
                while(star->mode != 9) {
                    HuPrcVSleep();
                }
                if(sys->gameType == 0) {
                    MdMessWinOpen(mess, MDMESS_WIN_2, 0, 0, 0, 2, 196, 120, 184, 96, 1);
                } else if(sys->gameType == 1) {
                    MdMessWinOpen(mess, MDMESS_WIN_2, 0, 0, 0, 2, 112, 120, 352, 128, 1);
                }
                MdMessWinSpeedSet(mess, MDMESS_WIN_2, 0);
                while(!MdMessWinCheck(mess, MDMESS_WIN_2)) {
                    HuPrcVSleep();
                }
                if(sys->gameType == 0) {
                    MdMessWinMesSet(mess, MDMESS_WIN_2, FALSE, MESSNUM(MESS_MGINST, 0x179), MDMESS_WIN_LIST_END);
                } else if(sys->gameType == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_2, FALSE, MESSNUM(MESS_MGINST, 0x17E), MDMESS_WIN_LIST_END);
                }
                star->motNext = 2;
                MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                if(sys->gameType == 0) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 18), MDMESS_WIN_LIST_END);
                } else if(sys->gameType == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 14), MDMESS_WIN_LIST_END);
                }
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinClose(mess, MDMESS_WIN_2);
                while(!MdMessWinCheck(mess, MDMESS_WIN_2)) {
                    HuPrcVSleep();
                }
            }
            if(!lbl_1_bss_0) {
                star->motNext = 3;
            }
            MdMessWinClose(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            if(!lbl_1_bss_0) {
                MdProcWait(MDBEACH_PROC_NAME, 0);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            }
            fn_1_13CAC();
            sys->prevPlayerNum = sys->playerNum;
            if(!lbl_1_bss_0) {
                star->mode = 7;
                while(star->mode != 9) {
                    HuPrcVSleep();
                }
            }
            MdProcWait(MDBEACH_PROC_CAP_PLAYER, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 4)+sys->playerNum, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            if(sys->maxPlayerNum > 1) {
                sys->unk2C4 = 0;
                MdProcWait(MDBEACH_PROC_CURSOR, 0);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            }
            sys->subMode = 2;
            break;

        case 2:
            if(sys->maxPlayerNum > 1 && ((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT))) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    sys->prevPlayerNum = sys->playerNum;
                    if(--sys->playerNum == -1) {
                        sys->playerNum = sys->maxPlayerNum-1;
                    }
                    sys->unk2C0 = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->prevPlayerNum = sys->playerNum;
                    sys->playerNum = ++sys->playerNum % sys->maxPlayerNum;
                    sys->unk2C0 = 1;
                }
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 4)+sys->playerNum, MDMESS_WIN_LIST_END);
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                MdProcWait(MDBEACH_PROC_CAP_PLAYER, sys->unk2C0+2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                if(sys->gameType == 0) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_BEACH_VOLLEY, 3), MDMESS_WIN_LIST_END);
                } else if(sys->gameType == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_ICE_HOCKEY, 3), MDMESS_WIN_LIST_END);
                }
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1 || choice == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 4)+sys->playerNum, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                } else if(choice == 0) {
                    MdMessWinClose(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_15A40(MDBEACH_AUD_MUS_STOP);
                    WipeWait();
                    if(sys->evtNo == 0 || sys->evtNo == 1) {
                        while(sys->loadState != 2) {
                            HuPrcVSleep();
                        }
                    }
                    mgPauseExitF = FALSE;
                    sys->ovlCallMode = MD_OVLCALL_RETURN;
                    sys->nextDll = DLL_mdomakedll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_14050();
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                if(sys->maxPlayerNum > 1) {
                    sys->unk2C4 = 0;
                    MdProcWait(MDBEACH_PROC_CURSOR, 1);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                }
                MdProcWait(MDBEACH_PROC_CAP_PLAYER, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDBEACH_FLOW_CHR_SEL;
            }
            break;
    }
}

/* 1436 insns */
void fn_1_4138(void)
{
    int i; //r31
    MDBEACH_PLAYERSPR *unk204; //r30
    MDMODEL_WORK *model; //r29
    MDBEACH_CHR *chr; //r28
    MDMESS_WORK *mess; //r27
    MDBEACH_STAR *star; //r26
    int result; //r25
    MDSPRITE_WORK *sprite; //r24

    MDBEACH_PLAYERSPR *playerSpr; //sp+0x8

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    unk204 = &sys->unk204[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                if(sys->padEnable[i] == FALSE) {
                    sys->chrSel[i] = 0;
                } else {
                    sys->chrSel[i] = i;
                }
                sys->chrSelEnd[i] = FALSE;
                sys->unk32[i] = sys->chrSel[i];
                sys->unk36[i] = 0;
            }
            sys->subMode = 1;
            break;

        case 1:
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 8), MDMESS_WIN_LIST_END);
            MdProcWait(MDBEACH_PROC_UNK5, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            MdProcWait(MDBEACH_PROC_FINGER, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                if(sys->padEnable[i] != FALSE) {
                    chr[sys->chrSel[i]].mode = 1;
                }
            }
            sys->subMode = 2;
            break;

        case 2:
            if(sys->chrSelEnd[0] == FALSE && (unk204[0].mode == 0 || unk204[0].mode == 3 || unk204[0].mode == 7) &&
                sys->chrSelEnd[1] == FALSE && (unk204[1].mode == 0 || unk204[1].mode == 3 || unk204[1].mode == 7) &&
                sys->chrSelEnd[2] == FALSE && (unk204[2].mode == 0 || unk204[2].mode == 3 || unk204[2].mode == 7) &&
                sys->chrSelEnd[3] == FALSE && (unk204[3].mode == 0 || unk204[3].mode == 3 || unk204[3].mode == 7) &&
                (HuPadBtnDown[0] & PAD_BUTTON_B)) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                for(i=0; i<4; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                }
                for(i=0; i<4; i++) {
                    if(sys->padEnable[i] == TRUE) {
                        chr[sys->chrSel[i]].mode = 4;
                    }
                }
                MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
                star->motNext = 3;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                MdProcWait(MDBEACH_PROC_UNK5, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                fn_1_13CAC();
                sys->prevPlayerNum = sys->playerNum;
                MdProcWait(MDBEACH_PROC_CAP_PLAYER, 4);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 4)+sys->playerNum, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                if(sys->maxPlayerNum > 1) {
                    sys->unk2C4 = 0;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                }
                sys->subMode = 2;
                sys->flowMode = MDBEACH_FLOW_START;
                break;
            }
            for(i=0; i<4; i++) {
                if(sys->padEnable[i] != FALSE && (unk204[i].mode == 0 || unk204[i].mode == 3 || unk204[i].mode == 7)) {
                    result = fn_1_14A68(i, FALSE);
                    if(result == TRUE) {
                        fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                        chr[sys->chrSel[i]].mode = 1;
                        chr[sys->unk32[i]].mode = 4;
                        fn_1_146D0();
                    } else if((HuPadBtnDown[i] & PAD_BUTTON_B) && sys->chrSelEnd[i] == TRUE) {
                        sys->chrSelEnd[i] = FALSE;
                        Hu3DModelAttrReset(model->mdlId[i+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                        unk204[i].mode = 5;
                        fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                    } else if((HuPadBtnDown[i] & PAD_BUTTON_A) && sys->chrSelEnd[i] == FALSE) {
                        sys->chrSelEnd[i] = TRUE;
                        Hu3DModelAttrSet(model->mdlId[i+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                        unk204[i].mode = 1;
                        fn_1_15A40(MDBEACH_AUD_SE_CMN_CHRSEL);
                        fn_1_15A40(sys->chrSel[i]+MDBEACH_AUD_SE_CHR_SEL);
                    }
                }
            }
            if(((sys->chrSelEnd[0] == TRUE && unk204[0].mode == 3) || sys->padEnable[0] == FALSE) &&
                ((sys->chrSelEnd[1] == TRUE && unk204[1].mode == 3) || sys->padEnable[1] == FALSE) &&
                ((sys->chrSelEnd[2] == TRUE && unk204[2].mode == 3) || sys->padEnable[2] == FALSE) &&
                ((sys->chrSelEnd[3] == TRUE && unk204[3].mode == 3) || sys->padEnable[3] == FALSE)) {
                if(sys->playerNum == 3) {
                    sys->subMode = 4;
                } else {
                    sys->selComNo = 0;
                    fn_1_14F44();
                    fn_1_146D0();
                    Hu3DModelAttrReset(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4.0f;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4.0f;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4.0f;
                    chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 1;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 9), MDMESS_WIN_LIST_END);
                    sys->subMode = 3;
                }
            }
            break;

        case 3:
            if(sys->selComNo == 0 && (HuPadBtnDown[0] & PAD_BUTTON_B)) {
                for(i=0; i<4; i++) {
                    if(sys->chrSelEnd[i] == TRUE) {
                        unk204[i].mode = 5;
                        sys->chrSelEnd[i] = FALSE;
                    }
                }
                chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 4;
                Hu3DModelAttrSet(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 8), MDMESS_WIN_LIST_END);
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                while(unk204[0].mode != 7) {
                    HuPrcVSleep();
                }
                MdProcWait(MDBEACH_PROC_FINGER, 0);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                for(i=0; i<4; i++) {
                    if(sys->padEnable[i] != FALSE) {
                        chr[sys->chrSel[i]].mode = 1;
                    }
                }
                sys->subMode = 2;
                break;
            }
            result = fn_1_14A68(sys->comPlayerNo[sys->selComNo], TRUE);
            if(result == TRUE) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 1;
                chr[sys->unk32[sys->comPlayerNo[sys->selComNo]]].mode = 4;
                fn_1_146D0();
            } else if((HuPadBtnDown[0] & PAD_BUTTON_B) && sys->selComNo > 0) {
                Hu3DModelAttrSet(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 4;
                sys->selComNo--;
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                unk204[sys->comPlayerNo[sys->selComNo]].mode = 5;
                while(unk204[sys->comPlayerNo[sys->selComNo]].mode != 7) {
                    HuPrcVSleep();
                }
                Hu3DModelAttrReset(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 1;
                sys->chrSelEnd[sys->comPlayerNo[sys->selComNo]] = FALSE;
                fn_1_146D0();
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                unk204[sys->comPlayerNo[sys->selComNo]].mode = 1;
                Hu3DModelAttrSet(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                if(sys->selComNo+1 < 3-sys->playerNum) {
                    fn_1_15A40(MDBEACH_AUD_SE_CMN_CHRSEL);
                } else {
                    fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                }
                fn_1_15A40(sys->chrSel[sys->comPlayerNo[sys->selComNo]]+MDBEACH_AUD_SE_CHR_SEL);
                while(unk204[sys->comPlayerNo[sys->selComNo]].mode != 3) {
                    HuPrcVSleep();
                }
                sys->chrSelEnd[sys->comPlayerNo[sys->selComNo]] = TRUE;
                sys->selComNo++;
                if(sys->selComNo < 3-sys->playerNum) {
                    fn_1_14F44();
                    fn_1_146D0();
                    chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 1;
                    Hu3DModelAttrReset(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4.0f;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4.0f;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4.0f;
                } else if(sys->selComNo >= 3-sys->playerNum) {
                    sys->subMode = 4;
                }
            }
            break;

        case 4:
            star->motNext = 3;
            MdMessWinClose(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
            MdProcWait(MDBEACH_PROC_UNK5, 2);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdProcWait(MDBEACH_PROC_MAP_ENTER, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->subMode = 0;
            sys->flowMode = MDBEACH_FLOW_TEAM_SEL;
            break;
    }
}

/* 1469 insns */
void fn_1_57A8(void)
{
    MDMESS_WORK *mess; //r31
    MDSPRITE_WORK *sprite; //r30
    int i; //r29
    MDBEACH_PLAYERSPR *unk204; //r28
    MDBEACH_STAR *star; //r27
    MDMODEL_WORK *model; //r26
    MDBEACH_CHR *chr; //r25
    int difMax; //r24
    MDBEACH_PLAYERSPR *playerSpr; //sp+0x8

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    unk204 = &sys->unk204[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->teamOrderNo = 0;
            fn_1_15048();
            fn_1_153C8();
            sys->subMode = 1;
            break;

        case 1:
            MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 10), MDMESS_WIN_LIST_END);
            MdProcWait(MDBEACH_PROC_UNK7, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            sys->unk2C4 = 1;
            MdProcWait(MDBEACH_PROC_CURSOR, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->subMode = 2;
            break;

        case 5:
            MdProcCall(MDBEACH_PROC_UNK5, 97);
            break;

        case 2:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    sys->unk2C0 = 0;
                    if(--sys->teamOrderNo == -1) {
                        sys->teamOrderNo = 2;
                    }
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk2C0 = 1;
                    sys->teamOrderNo = (++sys->teamOrderNo)%3;
                }
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                fn_1_153C8();
                fn_1_15048();
                MdProcWait(MDBEACH_PROC_MAP_ENTER, 2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                for(i=0; i<4; i++) {
                    chr[sys->chrSel[i]].mode = 4;
                }
                star->motNext = 3;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->unk2C4 = 1;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_UNK7, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_MAP_ENTER, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_UNK5, 3);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                if(sys->playerNum == 3) {
                    MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                    MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 2;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 8), MDMESS_WIN_LIST_END);
                    while(1) {
                        if(unk204[1].mode == 7 && unk204[2].mode == 7 && unk204[3].mode == 7) {
                            break;
                        }
                        HuPrcVSleep();
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    MdProcWait(MDBEACH_PROC_FINGER, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    for(i=0; i<4; i++) {
                        if(sys->padNoEnable[i] != -1) {
                            chr[sys->chrSel[i]].mode = 1;
                        }
                    }
                    sys->subMode = 2;
                    sys->flowMode = MDBEACH_FLOW_CHR_SEL;
                } else {
                    MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                    MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 2;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 9), MDMESS_WIN_LIST_END);
                    while(1) {
                        if((sys->padEnable[1] == TRUE || (sys->padEnable[1] == FALSE && unk204[1].mode == 7))
                            && (sys->padEnable[2] == TRUE || (sys->padEnable[2] == FALSE && unk204[2].mode == 7))
                            && (sys->padEnable[3] == TRUE || (sys->padEnable[3] == FALSE && unk204[3].mode == 7))) {
                            break;
                        }
                        HuPrcVSleep();
                    }
                    sys->selComNo = 0;
                    fn_1_14F44();
                    fn_1_146D0();
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    Hu3DModelAttrReset(model->mdlId[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P], HU3D_ATTR_DISPOFF);
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->x = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->y = 4;
                    model->scaleP[sys->comPlayerNo[sys->selComNo]+MDMODEL_FINGER_1P]->z = 4;
                    chr[sys->chrSel[sys->comPlayerNo[sys->selComNo]]].mode = 1;
                    sys->subMode = 3;
                    sys->flowMode = MDBEACH_FLOW_CHR_SEL;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, sys->teamNo[0]+MESS_TEAMNAME_START, MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, sys->teamNo[1]+MESS_TEAMNAME_START, MDMESS_WIN_LIST_END);
                sys->unk2C4 = 1;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                if(sys->playerNum == 3) {
                    sys->subMode = 4;
                } else {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 19), MDMESS_WIN_LIST_END);
                    for(i=0; i<4; i++) {
                        sys->comDif[i] = 1;
                        HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], i, sys->comDif[i]);
                    }
                    sys->selComNo = 0;
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    fn_1_146D0();
                    sys->subMode = 3;
                }
            }
            break;

        case 3:
            if(GwCommon.veryHardUnlock == TRUE) {
                difMax = 4;
            } else {
                difMax = 3;
            }
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->comDif[sys->teamComPlayerNo[sys->selComNo]] == -1) {
                        sys->comDif[sys->teamComPlayerNo[sys->selComNo]] = difMax-1;
                    }
                    sys->unk2C0 = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->comDif[sys->teamComPlayerNo[sys->selComNo]] = ++sys->comDif[sys->teamComPlayerNo[sys->selComNo]]%difMax;
                    sys->unk2C0 = 1;
                }
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                fn_1_146D0();
                HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo], sys->comDif[sys->teamComPlayerNo[sys->selComNo]]);
                sys->unk2C4 = 2;
                MdProcWait(MDBEACH_PROC_CURSOR, sys->unk2C0+2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                if(sys->selComNo == 0) {
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 1);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    sys->unk2C4 = 1;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 10), MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                    sys->subMode = 2;
                } else {
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 1);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    sys->selComNo--;
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    fn_1_146D0();
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                if(sys->selComNo+1 >= 3-sys->playerNum) {
                    fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                } else {
                    fn_1_15A40(MDBEACH_AUD_SE_CMN_CHRSEL);
                }
                sys->unk2C4 = 2;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                sys->selComNo++;
                if(sys->selComNo >= 3-sys->playerNum) {
                    sys->subMode = 4;
                } else {
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    fn_1_146D0();
                }
            }
            break;

        case 4:
            star->motNext = 3;
            MdMessWinClose(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
            sys->subMode = 0;
            if(sys->gameType == 0) {
                sys->flowMode = MDBEACH_FLOW_BONUS_SEL;
            } else if(sys->gameType == 1) {
                sys->flowMode = MDBEACH_FLOW_HANDICAP;
            }
            break;
    }
}

/* 724 insns */
void fn_1_6E9C(void)
{
    int i; //r31
    MDMESS_WORK *mess; //r30
    MDSPRITE_WORK *sprite; //r29
    MDBEACH_STAR *star; //r28

    MDMODEL_WORK *model; //sp+0x10
    MDBEACH_PLAYERSPR *playerSpr; //sp+0xC
    MDBEACH_PLAYERSPR *unk204; //sp+0x8

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    unk204 = &sys->unk204[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->unk58 = 0;
            sys->subMode = 1;
            break;

        case 1:
            MdProcWait(MDBEACH_PROC_UNK9, 1);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdProcWait(MDBEACH_PROC_UNK10, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 12)+sys->unk58, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            sys->unk2C4 = 3;
            MdProcWait(MDBEACH_PROC_CURSOR, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->subMode = 2;
            break;

        case 2:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                sys->unk59 = sys->unk58;
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk58 == -1) {
                        sys->unk58 = 2;
                    }
                    sys->unk2C0 = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk58 = ++sys->unk58 % 3;
                    sys->unk2C0 = 1;
                }
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 12)+sys->unk58, MDMESS_WIN_LIST_END);
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                MdProcWait(MDBEACH_PROC_UNK10, 2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                star->motNext = 3;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->unk2C4 = 3;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_UNK10, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_UNK9, 0);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                if(sys->playerNum == 3) {
                    MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                    MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 2;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 10), MDMESS_WIN_LIST_END);
                    for(i=0; i<3; i++) {
                        if(sys->comPlayerNo[i] != -1) {
                            HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->comPlayerNo[i]);
                            HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i]);
                        }
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                    sys->unk2C4 = 1;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    sys->subMode = 2;
                    sys->flowMode = MDBEACH_FLOW_TEAM_SEL;
                } else {
                    MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                    MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 2;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 19), MDMESS_WIN_LIST_END);
                    for(i=0; i<4; i++) {
                        HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], i, sys->comDif[i]);
                    }
                    sys->selComNo = 0;
                    for(i=0; i<3; i++) {
                        if(sys->comPlayerNo[i] != -1) {
                            HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->comPlayerNo[i]);
                            HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i]);
                        }
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->unk2C4 = 2;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                    fn_1_146D0();
                    sys->subMode = 3;
                    sys->flowMode = MDBEACH_FLOW_TEAM_SEL;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                star->motNext = 3;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->unk2C4 = 3;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDBEACH_FLOW_HANDICAP;
            }
            break;
    }
}

/* 2058 insns */
void fn_1_79EC(void)
{
    int i; //r31
    MDMESS_WORK *mess; //r30
    MDSPRITE_WORK *sprite; //r29
    MDBEACH_STAR *star; //r28
    int choice; //r27
    MDMODEL_WORK *model; //r26
    MDBEACH_PLAYERSPR *playerSpr; //r25
    MDBEACH_CHR *chr; //r24

    MDBEACH_PLAYERSPR *unk204; //sp+0x8

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    unk204 = &sys->unk204[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            if(sys->gameType == 0) {
                sys->unk5A = 0;
            } else if(sys->gameType == 1) {
                sys->unk5A = 0;
            }
            if(sys->gameType == 0) {
                HuSprBankSet(sprite->grpId[MDSPR_GRP_7], 1, sys->unk5A);
            } else if(sys->gameType == 1) {
                HuSprBankSet(sprite->grpId[MDSPR_GRP_8], 1, sys->unk5A);
            }
            sys->subMode = 1;
            break;

        case 1:
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            if(sys->gameType == 0) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 15), MDMESS_WIN_LIST_END);
            } else if(sys->gameType == 1) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 11), MDMESS_WIN_LIST_END);
            }
            MdProcWait(MDBEACH_PROC_UNK8, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_OPTION_ENTER, MDMESS_WIN_LIST_END);
            sys->unk2C4 = 4;
            MdProcWait(MDBEACH_PROC_CURSOR, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->subMode = 2;
            break;

        case 2:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(sys->gameType == 0) {
                        if(--sys->unk5A == -1) {
                            sys->unk5A = 2;
                        }
                    } else if(sys->gameType == 1) {
                        if(--sys->unk5A == -1) {
                            sys->unk5A = 2;
                        }
                    }
                    sys->unk2C0 = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    if(sys->gameType == 0) {
                        sys->unk5A = ++sys->unk5A % 3;
                    } else if(sys->gameType == 1) {
                        sys->unk5A = ++sys->unk5A % 3;
                    }
                    sys->unk2C0 = 1;
                }
                fn_1_15A40(MDBEACH_AUD_SE_CMN_MOVE);
                if(sys->gameType == 0) {
                    HuSprBankSet(sprite->grpId[MDSPR_GRP_7], 1, sys->unk5A);
                } else if(sys->gameType == 1) {
                    HuSprBankSet(sprite->grpId[MDSPR_GRP_8], 1, sys->unk5A);
                }
                sys->unk2C4 = 4;
                MdProcWait(MDBEACH_PROC_CURSOR, sys->unk2C0+2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_X) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                if(sys->gameType == 0) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_BEACH_VOLLEY, 3), MDMESS_WIN_LIST_END);
                } else if(sys->gameType == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_ICE_HOCKEY, 3), MDMESS_WIN_LIST_END);
                }
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1 || choice == 1) {
                    if(sys->gameType == 0) {
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 15), MDMESS_WIN_LIST_END);
                    } else if(sys->gameType == 1) {
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 11), MDMESS_WIN_LIST_END);
                    }
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_OPTION_ENTER, MDMESS_WIN_LIST_END);
                } else if(choice == 0) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    sys->unk2C4 = 4;
                    MdProcWait(MDBEACH_PROC_CURSOR, 1);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    MdMessWinClose(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_15A40(MDBEACH_AUD_MUS_STOP);
                    while(WipeCheckEnd()) {
                        HuPrcVSleep();
                    }
                    if(sys->evtNo == 0 || sys->evtNo == 1) {
                        while(sys->loadState != 2) {
                            HuPrcVSleep();
                        }
                    }
                    mgPauseExitF = FALSE;
                    sys->ovlCallMode = MD_OVLCALL_RETURN;
                    sys->nextDll = DLL_mdomakedll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CANCEL);
                star->motNext = 3;
                MdMessWinClose(mess, MDMESS_WIN_MAIN);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->unk2C4 = 4;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdProcWait(MDBEACH_PROC_UNK8, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                if(sys->gameType == 0) {
                    MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                    MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 2;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 12)+sys->unk58, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->unk2C4 = 3;
                    MdProcWait(MDBEACH_PROC_CURSOR, 0);
                    MdProcCall(MDBEACH_PROC_RESET, 0);
                    sys->subMode = 2;
                    sys->flowMode = MDBEACH_FLOW_BONUS_SEL;
                } else if(sys->gameType == 1) {
                    if(sys->playerNum == 3) {
                        MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                        MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                        while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                            HuPrcVSleep();
                        }
                        star->motNext = 2;
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 10), MDMESS_WIN_LIST_END);
                        for(i=0; i<3; i++) {
                            if(sys->comPlayerNo[i] != -1) {
                                HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->comPlayerNo[i]);
                                HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i]);
                            }
                        }
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                        MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                        MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, MESS_TEAMNAME_UNKNOWN, MDMESS_WIN_LIST_END);
                        sys->unk2C4 = 1;
                        MdProcWait(MDBEACH_PROC_CURSOR, 0);
                        MdProcCall(MDBEACH_PROC_RESET, 0);
                        sys->subMode = 2;
                        sys->flowMode = MDBEACH_FLOW_TEAM_SEL;
                    } else {
                        MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                        MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                        while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                            HuPrcVSleep();
                        }
                        star->motNext = 2;
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 19), MDMESS_WIN_LIST_END);
                        for(i=0; i<4; i++) {
                            HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], i, sys->comDif[i]);
                        }
                        sys->selComNo = 0;
                        for(i=0; i<3; i++) {
                            if(sys->comPlayerNo[i] != -1) {
                                HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->comPlayerNo[i]);
                                HuSprDispOff(sprite->grpId[MDSPR_GRP_COMDIF], sys->comPlayerNo[i]);
                            }
                        }
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                        sys->unk2C4 = 2;
                        MdProcWait(MDBEACH_PROC_CURSOR, 0);
                        MdProcCall(MDBEACH_PROC_RESET, 0);
                        HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], sys->teamComPlayerNo[sys->selComNo]);
                        HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[sys->selComNo]);
                        fn_1_146D0();
                        sys->subMode = 3;
                        sys->flowMode = MDBEACH_FLOW_TEAM_SEL;
                    }
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                fn_1_15A40(MDBEACH_AUD_SE_CMN_CONFIRM);
                sys->unk2C4 = 4;
                MdProcWait(MDBEACH_PROC_CURSOR, 1);
                MdProcCall(MDBEACH_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_BEACH_VOLLEY, 16), MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1 || choice == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_BEACH_VOLLEY, 17), MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                    if(choice == -1 || choice == 1) {
                        if(sys->gameType == 0) {
                            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 15), MDMESS_WIN_LIST_END);
                        } else if(sys->gameType == 1) {
                            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 11), MDMESS_WIN_LIST_END);
                        }
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_OPTION_ENTER, MDMESS_WIN_LIST_END);
                        sys->unk2C4 = 4;
                        MdProcWait(MDBEACH_PROC_CURSOR, 0);
                        MdProcCall(MDBEACH_PROC_RESET, 0);
                        sys->subMode = 2;
                    } else if(choice == 0) {
                        star->motNext = 3;
                        MdMessWinClose(mess, MDMESS_WIN_MAIN);
                        while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                            HuPrcVSleep();
                        }
                        for(i=0; i<4; i++) {
                            chr[sys->chrSel[i]].mode = 4;
                        }
                        WipeColorSet(0, 0, 0);
                        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                        while(WipeCheckEnd()) {
                            HuPrcVSleep();
                        }
                        MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
                        MdSpriteDispSet(sprite, MDSPR_GRP_COMDIF, FALSE);
                        MdSpriteDispSet(sprite, MDSPR_GRP_6, FALSE);
                        MdSpriteDispSet(sprite, MDSPR_GRP_7, FALSE);
                        MdSpriteDispSet(sprite, MDSPR_GRP_8, FALSE);
                        for(i=0; i<MDMODEL_CHR_NUM; i++) {
                            Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO], HU3D_ATTR_DISPOFF);
                        }
                        for(i=0; i<MDMODEL_CHR_NUM; i++) {
                            Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO_VOLLEY], HU3D_ATTR_DISPOFF);
                        }
                        for(i=0; i<MDMODEL_CHR_NUM; i++) {
                            Hu3DModelAttrSet(model->mdlId[i+MDMODEL_MARIO_HOCKEY], HU3D_ATTR_DISPOFF);
                        }
                        for(i=0; i<2; i++) {
                            Hu3DModelAttrSet(model->mdlId[i+MDMODEL_VS_VOLLEY], HU3D_ATTR_DISPOFF);
                        }
                        for(i=0; i<3; i++) {
                            Hu3DModelAttrSet(model->mdlId[i+MDMODEL_BALL_NORMAL], HU3D_ATTR_DISPOFF);
                        }
                        MdMessWinPosSet(mess, MDMESS_WIN_3, 288, -64);
                        MdMessWinPosSet(mess, MDMESS_WIN_4, 288, -64);
                        MdMessWinHomeClear(mess, MDMESS_WIN_3);
                        MdMessWinHomeClear(mess, MDMESS_WIN_4);
                        WipeColorSet(0, 0, 0);
                        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
                        while(WipeCheckEnd()) {
                            HuPrcVSleep();
                        }
                        fn_1_13CAC();
                        sys->prevPlayerNum = sys->playerNum;
                        MdProcWait(MDBEACH_PROC_CAP_PLAYER, 0);
                        MdProcCall(MDBEACH_PROC_RESET, 0);
                        MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
                        MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
                        while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                            HuPrcVSleep();
                        }
                        star->motNext = 2;
                        MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 4)+sys->playerNum, MDMESS_WIN_LIST_END);
                        MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                        if(sys->maxPlayerNum > 1) {
                            sys->unk2C4 = 0;
                            MdProcWait(MDBEACH_PROC_CURSOR, 0);
                            MdProcCall(MDBEACH_PROC_RESET, 0);
                        }
                        sys->subMode = 2;
                        sys->flowMode = MDBEACH_FLOW_START;
                    }
                } else if(choice == 0) {
                    fn_1_15508();
                    sys->loadProcReady = TRUE;
                    star->motNext = 3;
                    MdMessWinClose(mess, MDMESS_WIN_MAIN);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    fn_1_15A40(MDBEACH_AUD_MUS_STOP);
                    while(WipeCheckEnd()) {
                        MdProcCall(MDBEACH_PROC_MAP_ENTER, 5);
                        HuPrcVSleep();
                    }
                    while(sys->loadState != 4) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, sys->gameType+2, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                    sys->nextDll = lbl_1_data_148[sys->gameType];
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            }
            break;

        case 10:
            MdProcCall(MDBEACH_PROC_RESET, 0);
            fn_1_13EA4();
            fn_1_14050();
            fn_1_14354();
            sys->prevPlayerNum = sys->playerNum;
            MdMessWinOpen(mess, MDMESS_WIN_3, 1, 0, 0, 3, 288, -64, 224, 32, 0);
            MdMessWinOpen(mess, MDMESS_WIN_4, 1, 0, 0, 4, 288, -64, 224, 32, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_3, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_4, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_3, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_4, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinMesSet(mess, MDMESS_WIN_3, FALSE, sys->teamNo[0]+MESS_TEAMNAME_START, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_4, FALSE, sys->teamNo[1]+MESS_TEAMNAME_START, MDMESS_WIN_LIST_END);
            star->mode = 10;
            star->motNext = 1;
            MdProcCall(MDBEACH_PROC_UNK7, 4);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdProcCall(MDBEACH_PROC_UNK8, 3);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            if(sys->gameType == 0) {
                HuSprBankSet(sprite->grpId[MDSPR_GRP_7], 1, sys->unk5A);
            } else if(sys->gameType == 1) {
                HuSprBankSet(sprite->grpId[MDSPR_GRP_8], 1, sys->unk5A);
            }
            if(sys->gameType == 0) {
                MdProcCall(MDBEACH_PROC_UNK10, 3);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            } else if(sys->gameType == 1) {
                MdProcCall(MDBEACH_PROC_UNK9, 2);
                MdProcCall(MDBEACH_PROC_RESET, 0);
            }
            MdProcCall(MDBEACH_PROC_UNK5, 4);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdProcCall(MDBEACH_PROC_MAP_ENTER, 6);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                playerSpr[i].mode = 3;
                if(sys->padEnable[i]) {
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_PLAYERNO], i);
                }
            }
            for(i=0; i<3; i++) {
                if(sys->teamComPlayerNo[i] != -1) {
                    HuSprDispOn(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[i]);
                    HuSprBankSet(sprite->grpId[MDSPR_GRP_COMDIF], sys->teamComPlayerNo[i], sys->comDif[sys->teamComPlayerNo[i]]);
                }
            }
            HuPrcVSleep();
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, 5, 30);
            fn_1_15A40(MDBEACH_AUD_MUS_START);
            while(WipeCheckEnd()) {
                HuPrcVSleep();
            }
            MdProcWait(MDBEACH_PROC_NAME, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, 0, 1, 0, 0, 56, 376, 464, 64, 1);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            MdMessWinOpen(mess, MDMESS_WIN_HELP, 1, 0, 0, 1, 32, 340, 512, 32, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            star->motNext = 2;
            if(sys->gameType == 0) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_BEACH_VOLLEY, 15), MDMESS_WIN_LIST_END);
            } else if(sys->gameType == 1) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_ICE_HOCKEY, 11), MDMESS_WIN_LIST_END);
            }
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_OPTION_ENTER, MDMESS_WIN_LIST_END);
            sys->unk2C4 = 4;
            MdProcWait(MDBEACH_PROC_CURSOR, 0);
            MdProcCall(MDBEACH_PROC_RESET, 0);
            sys->subMode = 2;
            break;
    }
}

/* 102 insns */
BOOL fn_1_9A14(int param)
{
    sys->dirtyF = FALSE;
    sys->unk2AC = FALSE;
    sys->unk2B0 = FALSE;
    sys->unk2B4 = FALSE;
    sys->unk2B8 = FALSE;
    sys->unk2BC = FALSE;
    sys->procTime = 0.0f;
    sys->procOfsTime = 0.0f;
    sys->unk2D4 = 0.0f;
    sys->unk2D8 = 0.0f;
    sys->unk2DC = 0.0f;
    sys->procT = 0.0f;
    sys->procOfsT = 0.0f;
    sys->unk2E8 = 0.0f;
    sys->unk2EC = 0.0f;
    sys->unk2F0 = 0.0f;
    return FALSE;
}

/* 0x7B0 */ MDBEACH_LERP_DATA lbl_1_data_7B0[1] = { /* fn_1_9BAC; mdmini lbl_1_data_724 */
    { { -90.0f, -12.0f, 2500.0f }, { 0.0f, 400.0f, 1750.0f }, { -90.0f, 0.0f, 2500.0f }, { 0.0f, 200.0f, -250.0f }, 2, 30.0f }
};

/* 107 insns */
BOOL fn_1_9BAC(int param)
{
    MDBEACH_LERP_DATA *lerpP;
    MDCAMERA *camera;
    MDCAMERA_WORK *cameraWork;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[0];
    lerpP = &lbl_1_data_7B0[param];
    MdMathOscillate(lerpP->type, &sys->procTime, &sys->procT, lerpP->step);
    MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, lerpP->step);
    MdMathLerp(&camera->hvr.x, lerpP->hvrA.x, lerpP->hvrB.x, sys->procT);
    MdMathLerp(&camera->hvr.y, lerpP->hvrA.y, lerpP->hvrB.y, sys->procT);
    MdMathLerp(&camera->hvr.z, lerpP->hvrA.z, lerpP->hvrB.z, sys->procT);
    MdMathLerp(&camera->center.x, lerpP->centerA.x, lerpP->centerB.x, sys->procT);
    MdMathLerp(&camera->center.y, lerpP->centerA.y, lerpP->centerB.y, sys->procT);
    MdMathLerp(&camera->center.z, lerpP->centerA.z, lerpP->centerB.z, sys->procT);
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 1316 insns */
BOOL fn_1_9D58(int param)
{
    HuVec2f *sprScale; //r31
    HuVec2f *sprPos; //r30
    MDSPRITE_WORK *sprite; //r29
    HUSPRGRPID grpId; //r28
    MDCAMERA_WORK *camera; //r26

    MDMODEL_WORK *model; //sp+0x8
    HuVecF pos2D; //sp+0x18
    HuVecF pos3D; //sp+0xC

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_UDLR];
    if(!sys->unk2B8) {
        if(sys->unk2C4 == 0) {
            pos3D.x = 0;
            pos3D.y = 176.8f;
            pos3D.z = -580.0f;
            Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_BG].bit, &pos2D);
            lbl_1_bss_660[0].x = -64.0f;
            lbl_1_bss_660[0].y = pos2D.y;
            lbl_1_bss_660[0].z = 0;
            lbl_1_bss_660[1].x = pos2D.x-192;
            lbl_1_bss_660[1].y = pos2D.y;
            lbl_1_bss_660[1].z = 0;
            lbl_1_bss_660[2].x = 640.0f;
            lbl_1_bss_660[2].y = pos2D.y;
            lbl_1_bss_660[2].z = 0;
            lbl_1_bss_660[3].x = 192+pos2D.x;
            lbl_1_bss_660[3].y = pos2D.y;
            lbl_1_bss_660[3].z = 0;
        } else if(sys->unk2C4 == 1) {
            lbl_1_bss_660[0].x = -64.0f;
            lbl_1_bss_660[0].y = 192.0f;
            lbl_1_bss_660[0].z = 0;
            lbl_1_bss_660[1].x = 48.0f;
            lbl_1_bss_660[1].y = 192.0f;
            lbl_1_bss_660[1].z = 0;
            lbl_1_bss_660[2].x = 640.0f;
            lbl_1_bss_660[2].y = 192.0f;
            lbl_1_bss_660[2].z = 0;
            lbl_1_bss_660[3].x = 528.0f;
            lbl_1_bss_660[3].y = 192.0f;
            lbl_1_bss_660[3].z = 0;
        } else if(sys->unk2C4 == 2) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_PLAYERNO, sys->teamComPlayerNo[sys->selComNo]);
            pos2D.x = sprPos->x;
            pos2D.y = sprPos->y;
            pos2D.y -= 26.0f;
            lbl_1_bss_660[0].x = -64.0f;
            lbl_1_bss_660[0].y = pos2D.y;
            lbl_1_bss_660[0].z = 0;
            lbl_1_bss_660[1].x = pos2D.x-46;
            lbl_1_bss_660[1].y = pos2D.y;
            lbl_1_bss_660[1].z = 0;
            lbl_1_bss_660[2].x = 640.0f;
            lbl_1_bss_660[2].y = pos2D.y;
            lbl_1_bss_660[2].z = 0;
            lbl_1_bss_660[3].x = (46+pos2D.x)-3;
            lbl_1_bss_660[3].y = pos2D.y;
            lbl_1_bss_660[3].z = 0;
        } else if(sys->unk2C4 == 3) {
            lbl_1_bss_660[0].x = -64.0f;
            lbl_1_bss_660[0].y = 188.0f;
            lbl_1_bss_660[0].z = 0;
            lbl_1_bss_660[1].x = 208.0f;
            lbl_1_bss_660[1].y = 188.0f;
            lbl_1_bss_660[1].z = 0;
            lbl_1_bss_660[2].x = 640.0f;
            lbl_1_bss_660[2].y = 188.0f;
            lbl_1_bss_660[2].z = 0;
            lbl_1_bss_660[3].x = 368.0f;
            lbl_1_bss_660[3].y = 188.0f;
            lbl_1_bss_660[3].z = 0;
        } else if(sys->unk2C4 == 4) {
            if(sys->gameType == 0) {
                lbl_1_bss_660[0].x = -64.0f;
                lbl_1_bss_660[0].y = 88.0f;
                lbl_1_bss_660[0].z = 0;
                lbl_1_bss_660[1].x = 224.0f;
                lbl_1_bss_660[1].y = 88.0f;
                lbl_1_bss_660[1].z = 0;
                lbl_1_bss_660[2].x = 640.0f;
                lbl_1_bss_660[2].y = 88.0f;
                lbl_1_bss_660[2].z = 0;
                lbl_1_bss_660[3].x = 352.0f;
                lbl_1_bss_660[3].y = 88.0f;
                lbl_1_bss_660[3].z = 0;
            } else if(sys->gameType == 1) {
                lbl_1_bss_660[0].x = -64.0f;
                lbl_1_bss_660[0].y = 90.0f;
                lbl_1_bss_660[0].z = 0;
                lbl_1_bss_660[1].x = 232.0f;
                lbl_1_bss_660[1].y = 90.0f;
                lbl_1_bss_660[1].z = 0;
                lbl_1_bss_660[2].x = 640.0f;
                lbl_1_bss_660[2].y = 90.0f;
                lbl_1_bss_660[2].z = 0;
                lbl_1_bss_660[3].x = 341.0f;
                lbl_1_bss_660[3].y = 90.0f;
                lbl_1_bss_660[3].z = 0;
            }
        } else {
            lbl_1_bss_660[0].x = -64.0f;
            lbl_1_bss_660[0].y = 240.0f;
            lbl_1_bss_660[0].z = 0;
            lbl_1_bss_660[1].x = 128.0f;
            lbl_1_bss_660[1].y = 240.0f;
            lbl_1_bss_660[1].z = 0;
            lbl_1_bss_660[2].x = 640.0f;
            lbl_1_bss_660[2].y = 240.0f;
            lbl_1_bss_660[2].z = 0;
            lbl_1_bss_660[3].x = 448.0f;
            lbl_1_bss_660[3].y = 240.0f;
            lbl_1_bss_660[3].z = 0;
        }
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos->x = lbl_1_bss_660[0].x;
            sprPos->y = lbl_1_bss_660[0].y;
            if(sys->unk2C4 == 2) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprPos->x = lbl_1_bss_660[2].x;
            sprPos->y = lbl_1_bss_660[2].y;
            if(sys->unk2C4 == 2) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        } else if(param == 2) {
            /* retail takes the scale of UDLR_R, not of GLOW_UDLR_R */
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos->x = lbl_1_bss_660[1].x;
            sprPos->y = lbl_1_bss_660[1].y;
            if(sys->unk2C4 == 2) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), 0.0f);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3) {
            /* retail takes the scale of UDLR_L, not of GLOW_UDLR_L */
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
            sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprPos->x = lbl_1_bss_660[3].x;
            sprPos->y = lbl_1_bss_660[3].y;
            if(sys->unk2C4 == 2) {
                sprScale->x = sprScale->y = 0.7f;
            } else {
                sprScale->x = sprScale->y = 1.0f;
            }
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), 0.0f);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        sys->unk2B8 = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2DC, &sys->unk2F0, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[0].x, lbl_1_bss_660[1].x, sys->unk2F0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[2].x, lbl_1_bss_660[3].x, sys->unk2F0);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2DC, &sys->unk2F0, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[1].x, lbl_1_bss_660[0].x, sys->unk2F0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[3].x, lbl_1_bss_660[2].x, sys->unk2F0);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_180, &sys->unk2DC, &sys->unk2F0, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[1].x, lbl_1_bss_660[1].x-24.0f, sys->unk2F0);
        if(sys->unk2C4 == 2) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->unk2F0);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->unk2F0);
        }
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[1].x, lbl_1_bss_660[1].x-24.0f, sys->unk2F0);
        if(sys->unk2C4 == 2) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->unk2F0);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->unk2F0);
        }
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), sys->unk2F0);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_180, &sys->unk2DC, &sys->unk2F0, 15.0f);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[3].x, 24.0f+lbl_1_bss_660[3].x, sys->unk2F0);
        if(sys->unk2C4 == 2) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->unk2F0);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->unk2F0);
        }
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_660[3].x, 24.0f+lbl_1_bss_660[3].x, sys->unk2F0);
        if(sys->unk2C4 == 2) {
            MdMathLerp(&sprScale->x, 0.7f, 1.0f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 0.7f, 1.0f, sys->unk2F0);
        } else {
            MdMathLerp(&sprScale->x, 1.0f, 1.5f, sys->unk2F0);
            MdMathLerp(&sprScale->y, 1.0f, 1.5f, sys->unk2F0);
        }
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), sys->unk2F0);
    }
    if(sys->unk2DC >= 1.0f) {
        if(param == 1) {
            MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
        } else if(param == 2) {
            HuSprDispOff(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3) {
            HuSprDispOff(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 461 insns */
BOOL fn_1_B1E8(int param)
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
    if(!sys->dirtyF) {
        lbl_1_bss_65C = 0;
        lbl_1_bss_658 = topPos->y;
        lbl_1_bss_654 = bottomPos->y;
        lbl_1_bss_650 = bgScale->y;
        if(param == FALSE) {
            topPos->y = 0;
            bottomPos->y = 0;
            topScale->x = 0;
            bottomScale->x = 0;
            bgScale->x = 0;
            bgScale->y = 0;
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, TRUE);
        }
        sys->dirtyF = TRUE;
    }
    if(param == FALSE) {
        if(lbl_1_bss_65C == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 12);
            MdMathLerp(&topPos->y, 0, -2, sys->procT);
            MdMathLerp(&bottomPos->y, 0, 2, sys->procT);
            MdMathLerp(&topScale->x, 0, 72, sys->procT);
            MdMathLerp(&bottomScale->x, 0, 72, sys->procT);
            MdMathLerp(&bgScale->x, 0, 1, sys->procT);
            if(sys->procTime >= 1) {
                sys->procTime = 0;
                lbl_1_bss_65C = 1;
            }
        } else if(lbl_1_bss_65C == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
            MdMathLerp(&topPos->y, -2, -28, sys->procT);
            MdMathLerp(&bottomPos->y, 2, 32, sys->procT);
            MdMathLerp(&bgScale->y, 0, 8, sys->procT);
            if(sys->procTime >= 1) {
                lbl_1_bss_65C = 2;
            }
        }
    } else if(param == TRUE) {
        if(lbl_1_bss_65C == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
            MdMathLerp(&topPos->y, lbl_1_bss_658, -2, sys->procT);
            MdMathLerp(&bottomPos->y, lbl_1_bss_654, 2, sys->procT);
            MdMathLerp(&bgScale->y, lbl_1_bss_650, 0, sys->procT);
            if(sys->procTime >= 1) {
                sys->procTime = 0;
                lbl_1_bss_65C = 1;
            }
            
        } else if(lbl_1_bss_65C == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 12);
            MdMathLerp(&topPos->y, -2, 0, sys->procT);
            MdMathLerp(&bottomPos->y, 2, 0, sys->procT);
            MdMathLerp(&topScale->x, 72, 0, sys->procT);
            MdMathLerp(&bottomScale->x, 72, 0, sys->procT);
            MdMathLerp(&bgScale->x, 1, 0, sys->procT);
            if(sys->procTime >= 1) {
                lbl_1_bss_65C = 2;
            }
        }
    }
    if(lbl_1_bss_65C == 2) {
        if(param == TRUE) {
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x7E8 */ HuVecF lbl_1_data_7E8 = { 0.0f, 0.0f, 0.0f }; /* fn_1_B91C; mdparty ProcCapPlayer centerPos */
/* 0x7F4 */ HuVecF lbl_1_data_7F4[4] = { 0 }; /* fn_1_B91C; mdparty ProcCapPlayer playerPos */

/* 1744 insns */
BOOL fn_1_B91C(int param)
{
    int i; //r31
    MDBEACH_CAP_ANIM *anim; //r30
    MDMODEL_WORK *model; //r29
    MDCAMERA_WORK *camera; //r27

    HuVecF *posP[4][2]; //sp+0x48
    HuVecF *rotP[4][2]; //sp+0x28
    HuVecF *scaleP[4][2]; //sp+0x8

    model = sys->model;
    camera = sys->camera;
    if(!lbl_1_bss_4) {
        lbl_1_data_7E8.x = 288;
        lbl_1_data_7E8.y = 176.64f;
        lbl_1_data_7E8.z = 4000.0f;
        for(i=0; i<4; i++) {
            lbl_1_data_7F4[i].x = 168.0f+(i*80.0f);
            lbl_1_data_7F4[i].y = lbl_1_data_7E8.y;
            lbl_1_data_7F4[i].z = 2500;
        }
        lbl_1_bss_638[0].x = -64.0f;
        lbl_1_bss_638[0].y = lbl_1_data_7E8.y;
        lbl_1_bss_638[0].z = 2500;
        lbl_1_bss_638[1].x = 704.0f;
        lbl_1_bss_638[1].y = lbl_1_data_7E8.y;
        lbl_1_bss_638[1].z = 2500;
        lbl_1_bss_4 = TRUE;
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
                lbl_1_bss_5DC[i][0] = 0;
            } else {
                lbl_1_bss_5DC[i][0] = 1;
            }
            if(i < sys->prevPlayerNum+1) {
                lbl_1_bss_5DC[i][1] = 0;
            } else {
                lbl_1_bss_5DC[i][1] = 1;
            }
        }
        for(anim=lbl_1_bss_574, i=0; i<4; i++, anim++) {
            anim->mode = 0;
            anim->delay = 0;
            anim->time = 0;
            anim->t = 0;
        }
        if(param == 0) {
            lbl_1_bss_574[0].delay = 12;
            lbl_1_bss_574[1].delay = 8;
            lbl_1_bss_574[2].delay = 4;
            lbl_1_bss_574[3].delay = 0;
            Hu3D2Dto3D(&lbl_1_data_7E8, camera->camera[0].bit, &lbl_1_bss_62C);
            for(i=0; i<4; i++) {
                Hu3D2Dto3D(&lbl_1_data_7F4[i], camera->camera[0].bit, &lbl_1_bss_5FC[i]);
            }
            for(i=0; i<2; i++) {
                Hu3D2Dto3D(&lbl_1_bss_638[i], camera->camera[0].bit, &lbl_1_bss_5E4[i]);
            }
            for(i=0; i<4; i++) {
                posP[i][lbl_1_bss_5DC[i][0]]->x = lbl_1_bss_62C.x;
                posP[i][lbl_1_bss_5DC[i][0]]->y = lbl_1_bss_62C.y;
                posP[i][lbl_1_bss_5DC[i][0]]->z = lbl_1_bss_62C.z;
                rotP[i][lbl_1_bss_5DC[i][0]]->x = 0;
                rotP[i][lbl_1_bss_5DC[i][0]]->y = 0;
                rotP[i][lbl_1_bss_5DC[i][0]]->z = 0;
                scaleP[i][lbl_1_bss_5DC[i][0]]->x = 0;
                scaleP[i][lbl_1_bss_5DC[i][0]]->y = 0;
                scaleP[i][lbl_1_bss_5DC[i][0]]->z = 0;
                if(lbl_1_bss_5DC[i][0] == 0) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                } else if(lbl_1_bss_5DC[i][0] == 1) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                }
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 1) {
            lbl_1_bss_574[0].delay = 12;
            lbl_1_bss_574[1].delay = 8;
            lbl_1_bss_574[2].delay = 4;
            lbl_1_bss_574[3].delay = 0;
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 2 || param == 3) {
            for(i=0; i<4; i++) {
                if(lbl_1_bss_5DC[i][0] != lbl_1_bss_5DC[i][1]) {
                    posP[i][lbl_1_bss_5DC[i][1]]->x = lbl_1_bss_62C.x;
                    posP[i][lbl_1_bss_5DC[i][1]]->y = lbl_1_bss_62C.y;
                    posP[i][lbl_1_bss_5DC[i][1]]->z = lbl_1_bss_62C.z;
                    rotP[i][lbl_1_bss_5DC[i][1]]->x = 0;
                    rotP[i][lbl_1_bss_5DC[i][1]]->y = 0;
                    rotP[i][lbl_1_bss_5DC[i][1]]->z = 0;
                    scaleP[i][lbl_1_bss_5DC[i][1]]->x = 0;
                    scaleP[i][lbl_1_bss_5DC[i][1]]->y = 0;
                    scaleP[i][lbl_1_bss_5DC[i][1]]->z = 0;
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_5DC[i][0]*4)]);
                }
            }
            lbl_1_bss_5D8 = 200;
            lbl_1_bss_5D4 = 90;
            for(i=0; i<4; i++) {
                lbl_1_bss_5A4[i] = lbl_1_bss_5FC[i];
                lbl_1_bss_5A4[i].z -= lbl_1_bss_5D8;
            }
        } else if(param == 4) {
            lbl_1_bss_574[0].delay = 0;
            lbl_1_bss_574[1].delay = 4;
            lbl_1_bss_574[2].delay = 8;
            lbl_1_bss_574[3].delay = 12;
            Hu3D2Dto3D(&lbl_1_data_7E8, camera->camera[0].bit, &lbl_1_bss_62C);
            for(i=0; i<4; i++) {
                Hu3D2Dto3D(&lbl_1_data_7F4[i], camera->camera[0].bit, &lbl_1_bss_5FC[i]);
            }
            for(i=0; i<2; i++) {
                Hu3D2Dto3D(&lbl_1_bss_638[i], camera->camera[0].bit, &lbl_1_bss_5E4[i]);
            }
            for(i=0; i<4; i++) {
                scaleP[i][lbl_1_bss_5DC[i][0]]->x = 1;
                scaleP[i][lbl_1_bss_5DC[i][0]]->y = 1;
                scaleP[i][lbl_1_bss_5DC[i][0]]->z = 1;
                if(lbl_1_bss_5DC[i][0] == 0) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                } else if(lbl_1_bss_5DC[i][0] == 1) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P]);
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_COM_1P]);
                }
                *posP[i][lbl_1_bss_5DC[i][0]] = lbl_1_bss_5E4[1];
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 5) {
            for(i=0; i<4; i++) {
                scaleP[i][lbl_1_bss_5DC[i][0]]->x = 1;
                scaleP[i][lbl_1_bss_5DC[i][0]]->y = 1;
                scaleP[i][lbl_1_bss_5DC[i][0]]->z = 1;
                *posP[i][lbl_1_bss_5DC[i][0]] = lbl_1_bss_5E4[1];
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        for(anim=lbl_1_bss_574, i=0; i<4; i++, anim++) {
            switch(anim->mode) {
                case 0:
                    if(--anim->delay < 0) {
                        anim->mode++;
                    }
                    break;
                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &anim->time, &anim->t, 30);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->x, lbl_1_bss_5E4[0].x, lbl_1_bss_5FC[i].x, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->y, lbl_1_bss_5E4[0].y, lbl_1_bss_5FC[i].y, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->z, lbl_1_bss_5E4[0].z, lbl_1_bss_5FC[i].z, anim->t);
                    MdMathLerpScale(scaleP[i][lbl_1_bss_5DC[i][0]], 0, 1, anim->t);
                    if(anim->time >= 1) {
                        anim->mode++;
                    }
                    break;
                case 2:
                    break;
            }
        }
    } else if(param == 1) {
        for(anim=lbl_1_bss_574, i=0; i<4; i++, anim++) {
            switch(anim->mode) {
                case 0:
                    if(--anim->delay < 0) {
                        anim->mode++;
                    }
                    break;
                case 1:
                    MdMathOscillate(MDMATH_OSC_90_REV, &anim->time, &anim->t, 30);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->x, lbl_1_bss_5FC[i].x, lbl_1_bss_5E4[1].x, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->y, lbl_1_bss_5FC[i].y, lbl_1_bss_5E4[1].y, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->z, lbl_1_bss_5FC[i].z, lbl_1_bss_5E4[1].z, anim->t);
                    if(anim->time >= 1) {
                        anim->mode++;
                    }
                    break;
                case 2:
                    break;
            }
        }
    } else if(param == 2 || param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 20);
        if(param == 2) {
            MdMathLerp(&lbl_1_bss_5D4, 90, 270, sys->procT);
        } else if(param == 3) {
            MdMathLerp(&lbl_1_bss_5D4, 90, -90, sys->procT);
        }
        for(i=0; i<4; i++) {
            if(lbl_1_bss_5DC[i][0] != lbl_1_bss_5DC[i][1]) {
                MdMathLerpScale(scaleP[i][lbl_1_bss_5DC[i][1]], 1, 0, sys->procT);
                posP[i][lbl_1_bss_5DC[i][1]]->x = lbl_1_bss_5A4[i].x+(lbl_1_bss_5D8*HuCos(lbl_1_bss_5D4));
                posP[i][lbl_1_bss_5DC[i][1]]->y = lbl_1_bss_5A4[i].y;
                posP[i][lbl_1_bss_5DC[i][1]]->z = lbl_1_bss_5A4[i].z+(lbl_1_bss_5D8*HuSin(lbl_1_bss_5D4));
                MdMathLerpScale(scaleP[i][lbl_1_bss_5DC[i][0]], 0, 1, sys->procT);
                posP[i][lbl_1_bss_5DC[i][0]]->x = lbl_1_bss_5A4[i].x+(lbl_1_bss_5D8*HuCos(180.0f+lbl_1_bss_5D4));
                posP[i][lbl_1_bss_5DC[i][0]]->y = lbl_1_bss_5A4[i].y;
                posP[i][lbl_1_bss_5DC[i][0]]->z = lbl_1_bss_5A4[i].z+(lbl_1_bss_5D8*HuSin(180.0f+lbl_1_bss_5D4));
            }
        }
        if(sys->maxPlayerNum > 1) {
            sys->unk2C4 = 0;
            MdProcCall(MDBEACH_PROC_CURSOR, param);
        }
    } else if(param == 4) {
        for(anim=lbl_1_bss_574, i=0; i<4; i++, anim++) {
            switch(anim->mode) {
                case 0:
                    if(--anim->delay < 0) {
                        anim->mode++;
                    }
                    break;
                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &anim->time, &anim->t, 30);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->x, lbl_1_bss_5E4[1].x, lbl_1_bss_5FC[i].x, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->y, lbl_1_bss_5E4[1].y, lbl_1_bss_5FC[i].y, anim->t);
                    MdMathLerp(&posP[i][lbl_1_bss_5DC[i][0]]->z, lbl_1_bss_5E4[1].z, lbl_1_bss_5FC[i].z, anim->t);
                    if(anim->time >= 1) {
                        anim->mode++;
                    }
                    break;
                case 2:
                    break;
            }
        }
    } else if(param == 5) {
    }
    for(i=0; i<4; i++) {
        fn_1_15418(i+MDMODEL_CAP_MAN_1P, MDCAMERA_MAIN);
        fn_1_15418(i+MDMODEL_CAP_COM_1P, MDCAMERA_MAIN);
    }
    if(param == 0) {
        if(lbl_1_bss_574[0].mode == 2) {
            return TRUE;
        }
    } else if(param == 1) {
        if(lbl_1_bss_574[0].mode == 2) {
            for(i=0; i<4; i++) {
                Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_5DC[i][0]*4)]);
            }
            return TRUE;
        }
    } else if(param == 2 || param == 3) {
        if(sys->procTime >= 1) {
            for(i=0; i<4; i++) {
                if(lbl_1_bss_5DC[i][0] != lbl_1_bss_5DC[i][1]) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_MAN_1P+(lbl_1_bss_5DC[i][1]*4)]);
                }
            }
            return TRUE;
        }
    } else if(param == 4) {
        if(lbl_1_bss_574[3].mode == 2) {
            return TRUE;
        }
    } else if(param == 5) {
        return TRUE;
    }
    return FALSE;
}

/* 0x824 */ s16 lbl_1_data_824[10] = { 5, 9, 4, 8, 3, 2, 1, 7, 0, 6 };

/* 1526 insns */
BOOL fn_1_D45C(int param)
{
    int i; //r31
    MDBEACH_CAP_ANIM *anim; //r30
    s16 k; //r29
    MDCAMERA_WORK *camera; //r28
    MDMODEL_WORK *model; //r27
    int j; //r26

    HuVecF *posP[10]; //sp+0x60
    HuVecF *rotP[10]; //sp+0x38
    HuVecF *scaleP[10]; //sp+0x10
    MDBEACH_STAR *star; //sp+0xC
    MDBEACH_CHR *chr; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    star = sys->star;
    chr = sys->chr;
    k = 0;
    j = 0;
    for(i=0; i<10; i++) {
        if(sys->gameType == 0) {
            posP[i] = model->posP[i+MDMODEL_MARIO_VOLLEY];
            rotP[i] = model->rotP[i+MDMODEL_MARIO_VOLLEY];
            scaleP[i] = model->scaleP[i+MDMODEL_MARIO_VOLLEY];
        } else if(sys->gameType == 1) {
            posP[i] = model->posP[i+MDMODEL_MARIO_HOCKEY];
            rotP[i] = model->rotP[i+MDMODEL_MARIO_HOCKEY];
            scaleP[i] = model->scaleP[i+MDMODEL_MARIO_HOCKEY];
        }
    }
    if(!sys->dirtyF) {
        if(param == 0) {
            for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
                anim->mode = 0;
                anim->time = 0;
                anim->t = 0;
            }
            for(j=0, i=0; i<10; i++) {
                anim = &lbl_1_bss_318[lbl_1_data_824[i]];
                anim->delay = j*4;
                j++;
            }
            for(i=0; i<10; i++) {
                lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                lbl_1_bss_484[i][0] = lbl_1_bss_484[i][1];
                lbl_1_bss_484[i][0].x = -80.0f;
                Hu3D2Dto3D(&lbl_1_bss_484[i][0], camera->camera[0].bit, &lbl_1_bss_394[i][0]);
                Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
            }
            for(i=0; i<10; i++) {
                if(sys->gameType == 0) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO_VOLLEY]);
                } else if(sys->gameType == 1) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO_HOCKEY]);
                }
                *posP[i] = lbl_1_bss_394[i][0];
                rotP[i]->x = 0;
                rotP[i]->y = 0;
                rotP[i]->z = 0;
                scaleP[i]->x = 1;
                scaleP[i]->y = 1;
                scaleP[i]->z = 1;
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 1) {
            for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
                anim->mode = 0;
                anim->time = 0;
                anim->t = 0;
            }
            for(j=0, i=9; i>=0; i--) {
                anim = &lbl_1_bss_318[lbl_1_data_824[i]];
                anim->delay = j*4;
                j++;
            }
            for(i=0; i<10; i++) {
                lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                lbl_1_bss_484[i][0] = lbl_1_bss_484[i][1];
                lbl_1_bss_484[i][0].x = -80.0f;
                Hu3D2Dto3D(&lbl_1_bss_484[i][0], camera->camera[0].bit, &lbl_1_bss_394[i][0]);
                Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 2) {
            for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
                anim->mode = 0;
                anim->time = 0;
                anim->t = 0;
            }
            for(k=0, j=0, i=0; i<10; i++) {
                if(sys->chrSel[0] == lbl_1_data_824[k] || sys->chrSel[1] == lbl_1_data_824[k] || sys->chrSel[2] == lbl_1_data_824[k] || sys->chrSel[3] == lbl_1_data_824[k]) {
                    k++;
                } else {
                    anim = &lbl_1_bss_318[lbl_1_data_824[k]];
                    anim->delay = j*4;
                    lbl_1_bss_390 = lbl_1_data_824[k];
                    k++;
                    j++;
                }
            }
            for(i=0; i<10; i++) {
                lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                lbl_1_bss_484[i][0] = lbl_1_bss_484[i][1];
                lbl_1_bss_484[i][0].x = 640.0f;
                Hu3D2Dto3D(&lbl_1_bss_484[i][0], camera->camera[0].bit, &lbl_1_bss_394[i][0]);
                Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 3) {
            for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
                anim->mode = 0;
                anim->time = 0;
                anim->t = 0;
            }
            for(k=9, j=0, i=0; i<10; i++) {
                if((sys->chrSel[0] == lbl_1_data_824[k] && sys->chrSelEnd[0] == 1)
                    || (sys->chrSel[1] == lbl_1_data_824[k] && sys->chrSelEnd[1] == 1)
                    || (sys->chrSel[2] == lbl_1_data_824[k] && sys->chrSelEnd[2] == 1)
                    || (sys->chrSel[3] == lbl_1_data_824[k] && sys->chrSelEnd[3] == 1)) {
                    k--;
                } else {
                    anim = &lbl_1_bss_318[lbl_1_data_824[k]];
                    anim->delay = j*4;
                    lbl_1_bss_390 = lbl_1_data_824[k];
                    k--;
                    j++;
                }
            }
            for(i=0; i<10; i++) {
                lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                lbl_1_bss_484[i][0] = lbl_1_bss_484[i][1];
                lbl_1_bss_484[i][0].x = 640.0f;
                Hu3D2Dto3D(&lbl_1_bss_484[i][0], camera->camera[0].bit, &lbl_1_bss_394[i][0]);
                Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 4) {
            for(i=0; i<10; i++) {
                if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                    lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                    lbl_1_bss_484[i][1].x = 640.0f;
                    Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
                    *posP[i] = lbl_1_bss_394[i][1];
                    if(sys->gameType == 0) {
                        Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO_VOLLEY]);
                    } else if(sys->gameType == 1) {
                        Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO_HOCKEY]);
                    }
                }
            }
            for(i=0; i<10; i++) {
                if(i == sys->chrSel[0] || i == sys->chrSel[1] || i == sys->chrSel[2] || i == sys->chrSel[3]) {
                    lbl_1_bss_484[i][1] = lbl_1_data_158[sys->gameType][i];
                    Hu3D2Dto3D(&lbl_1_bss_484[i][1], camera->camera[0].bit, &lbl_1_bss_394[i][1]);
                    *posP[i] = lbl_1_bss_394[i][1];
                }
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
            switch(anim->mode) {
                case 0:
                    if(--anim->delay < 0) {
                        anim->mode++;
                    }
                    break;
                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &anim->time, &anim->t, 30);
                    MdMathLerp(&posP[i]->x, lbl_1_bss_394[i][0].x, lbl_1_bss_394[i][1].x, anim->t);
                    MdMathLerp(&posP[i]->y, lbl_1_bss_394[i][0].y, lbl_1_bss_394[i][1].y, anim->t);
                    MdMathLerp(&posP[i]->z, lbl_1_bss_394[i][0].z, lbl_1_bss_394[i][1].z, anim->t);
                    if(anim->time >= 1) {
                        anim->mode++;
                    }
                    break;
                case 2:
                    break;
            }
        }
    } else if(param == 1) {
        for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
            switch(anim->mode) {
                case 0:
                    if(--anim->delay < 0) {
                        anim->mode++;
                    }
                    break;
                case 1:
                    MdMathOscillate(MDMATH_OSC_90_REV, &anim->time, &anim->t, 30);
                    MdMathLerp(&posP[i]->x, lbl_1_bss_394[i][1].x, lbl_1_bss_394[i][0].x, anim->t);
                    MdMathLerp(&posP[i]->y, lbl_1_bss_394[i][1].y, lbl_1_bss_394[i][0].y, anim->t);
                    MdMathLerp(&posP[i]->z, lbl_1_bss_394[i][1].z, lbl_1_bss_394[i][0].z, anim->t);
                    if(anim->time >= 1) {
                        anim->mode++;
                    }
                    break;
                case 2:
                    break;
            }
        }
    } else if(param == 2) {
        for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
            if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                switch(anim->mode) {
                    case 0:
                        if(--anim->delay < 0) {
                            anim->mode++;
                        }
                        break;
                    case 1:
                        MdMathOscillate(MDMATH_OSC_90_REV, &anim->time, &anim->t, 30);
                        MdMathLerp(&posP[i]->x, lbl_1_bss_394[i][1].x, lbl_1_bss_394[i][0].x, anim->t);
                        MdMathLerp(&posP[i]->y, lbl_1_bss_394[i][1].y, lbl_1_bss_394[i][0].y, anim->t);
                        MdMathLerp(&posP[i]->z, lbl_1_bss_394[i][1].z, lbl_1_bss_394[i][0].z, anim->t);
                        if(anim->time >= 1) {
                            anim->mode++;
                        }
                        break;
                    case 2:
                        break;
                }
            }
        }
    } else if(param == 3) {
        for(anim=lbl_1_bss_318, i=0; i<10; i++, anim++) {
            if((i != sys->chrSel[0] || sys->chrSelEnd[0] != 1)
                && (i != sys->chrSel[1] || sys->chrSelEnd[1] != 1)
                && (i != sys->chrSel[2] || sys->chrSelEnd[2] != 1)
                && (i != sys->chrSel[3] || sys->chrSelEnd[3] != 1)) {
                switch(anim->mode) {
                    case 0:
                        if(--anim->delay < 0) {
                            anim->mode++;
                        }
                        break;
                    case 1:
                        MdMathOscillate(MDMATH_OSC_90_REV, &anim->time, &anim->t, 30);
                        MdMathLerp(&posP[i]->x, lbl_1_bss_394[i][0].x, lbl_1_bss_394[i][1].x, anim->t);
                        MdMathLerp(&posP[i]->y, lbl_1_bss_394[i][0].y, lbl_1_bss_394[i][1].y, anim->t);
                        MdMathLerp(&posP[i]->z, lbl_1_bss_394[i][0].z, lbl_1_bss_394[i][1].z, anim->t);
                        if(anim->time >= 1) {
                            anim->mode++;
                        }
                        break;
                    case 2:
                        break;
                }
            }
        }
    } else if(param == 4) {
    }
    if(param == 0) {
        if(lbl_1_bss_318[lbl_1_data_824[9]].mode == 2) {
            return TRUE;
        }
    } else if(param == 1) {
        if(lbl_1_bss_318[lbl_1_data_824[0]].mode == 2) {
            return TRUE;
        }
    } else if(param == 2) {
        if(lbl_1_bss_318[lbl_1_bss_390].mode == 2) {
            return TRUE;
        }
    } else if(param == 3) {
        if(lbl_1_bss_318[lbl_1_bss_390].mode == 2) {
            return TRUE;
        }
    } else if(param == 4) {
        return TRUE;
    }
    return FALSE;
}

/* 0x838 */ HuVecF lbl_1_data_838[4] = { { 96.0f, 224.0f, 1500.0f }, { 192.0f, 224.0f, 1500.0f }, { 384.0f, 224.0f, 1500.0f }, { 480.0f, 224.0f, 1500.0f } };
/* 0x868 */ float lbl_1_data_868[4] = { 176.0f, 232.0f, 344.0f, 400.0f };

/* 2855 insns; mdparty MdPartyProcMapEnter idioms. The four characters (MDMODEL_MARIO + chrSel)
 * jump between 3D points derived from 2D slots (lbl_1_data_838/868, Hu3D2Dto3D on camera 0):
 * lbl_1_bss_258[i][n] are the 2D points, lbl_1_bss_198[i][n] the 3D ones (leg 1 [0]->[1],
 * leg 2 [2]->[3]), lbl_1_bss_138[i] the saved start, lbl_1_bss_E8[i] the per-player state (a
 * random delay, then the legs), lbl_1_bss_E4 the player who waits longest (the proc ends when
 * that one lands). param 0 jump onto the court slots, 1 jump back (players beyond playerNum or
 * without a pad slide their volley/hockey model off to x=640: playerSpr mode 5), 2 move to the
 * team slots (+ PROC_CURSOR param+unk2C0), 3/4 hop sideways to / back from the team side
 * (+ PROC_UNK7 2/3), 5 jump turning 360 with a glow particle, 6 place them at once. */
BOOL fn_1_EC34(int param)
{
    int i; //r31
    MDBEACH_JUMP *jumpP; //r30
    MDMODEL_WORK *model; //r29
    MDCAMERA_WORK *camera; //r28
    HuVecF *posP; //r27
    MDBEACH_PLAYERSPR *playerSpr; //r25
    HuVecF *rotP; //r23
    HuVecF *mdlPosP; //r22
    HuVecF *scaleP; //r20
    MDSPRITE_WORK *sprite; //r18

    HuVecF pos; //sp+0x30
    HuVecF pos2D; //sp+0x24
    HuVecF pos3D; //sp+0x18
    MDBEACH_STAR *star; //sp+0x14

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    star = sys->star;
    playerSpr = sys->unk204;
    if(!sys->dirtyF) {
        if(param == 0) {
            lbl_1_bss_E4.playerNo = lbl_1_bss_E4.delay = 0;
            for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
                jumpP->mode = 0;
                jumpP->delay = frandmod(8);
                if(jumpP->delay > lbl_1_bss_E4.delay) {
                    lbl_1_bss_E4.playerNo = i;
                    lbl_1_bss_E4.delay = jumpP->delay;
                }
                jumpP->time = 0;
                jumpP->t = 0;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_198[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                lbl_1_bss_138[i][0] = lbl_1_bss_198[i][0];
                lbl_1_bss_258[i][1] = lbl_1_data_838[i];
                lbl_1_bss_258[i][1].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][1]);
                lbl_1_bss_198[i][1].x = lbl_1_bss_198[i][0].x;
                lbl_1_bss_138[i][1] = lbl_1_bss_198[i][1];
                lbl_1_bss_258[i][2] = lbl_1_data_838[i];
                lbl_1_bss_258[i][2].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][2], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][2]);
                lbl_1_bss_258[i][3] = lbl_1_data_838[i];
                Hu3D2Dto3D(&lbl_1_bss_258[i][3], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][3]);
            }
        } else if(param == 1) {
            lbl_1_bss_E4.playerNo = lbl_1_bss_E4.delay = 0;
            for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
                jumpP->mode = 0;
                jumpP->delay = frandmod(8);
                if(jumpP->delay > lbl_1_bss_E4.delay) {
                    lbl_1_bss_E4.playerNo = i;
                    lbl_1_bss_E4.delay = jumpP->delay;
                }
                jumpP->time = 0;
                jumpP->t = 0;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_198[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                lbl_1_bss_258[i][1] = lbl_1_data_838[sys->teamOrder[i]];
                lbl_1_bss_258[i][1].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][1]);
                lbl_1_bss_198[i][1].x = lbl_1_bss_198[i][0].x;
                lbl_1_bss_198[i][2] = lbl_1_bss_138[i][1];
                lbl_1_bss_198[i][3] = lbl_1_bss_138[i][0];
            }
        } else if(param == 2) {
            lbl_1_bss_E4.playerNo = lbl_1_bss_E4.delay = 0;
            for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
                jumpP->mode = 0;
                jumpP->delay = frandmod(8);
                if(jumpP->delay > lbl_1_bss_E4.delay) {
                    lbl_1_bss_E4.playerNo = i;
                    lbl_1_bss_E4.delay = jumpP->delay;
                }
                jumpP->time = 0;
                jumpP->t = 0;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_198[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                lbl_1_bss_258[i][1] = lbl_1_data_838[sys->teamOrderBackup[i]];
                lbl_1_bss_258[i][1].x = lbl_1_data_868[sys->teamOrderBackup[i]];
                lbl_1_bss_258[i][1].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][1]);
                lbl_1_bss_258[i][2] = lbl_1_data_838[sys->teamOrder[i]];
                lbl_1_bss_258[i][2].x = lbl_1_data_868[sys->teamOrder[i]];
                lbl_1_bss_258[i][2].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][2], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][2]);
                lbl_1_bss_258[i][3] = lbl_1_data_838[sys->teamOrder[i]];
                Hu3D2Dto3D(&lbl_1_bss_258[i][3], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][3]);
            }
        } else if(param == 3 || param == 4) {
            for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
                jumpP->mode = 0;
                jumpP->delay = 0;
                jumpP->time = 0;
                jumpP->t = 0;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_258[i][0] = lbl_1_data_838[sys->teamOrder[i]];
                Hu3D2Dto3D(&lbl_1_bss_258[i][0], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][0]);
                lbl_1_bss_258[i][1] = lbl_1_bss_258[i][0];
                if(sys->teamOrder[i] < 2) {
                    lbl_1_bss_258[i][1].x -= 32.0f;
                } else {
                    lbl_1_bss_258[i][1].x += 32.0f;
                }
                Hu3D2Dto3D(&lbl_1_bss_258[i][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][1]);
            }
        } else if(param == 5) {
            lbl_1_bss_E4.playerNo = lbl_1_bss_E4.delay = 0;
            for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
                jumpP->mode = 0;
                jumpP->delay = frandmod(12);
                if(jumpP->delay > lbl_1_bss_E4.delay) {
                    lbl_1_bss_E4.playerNo = i;
                    lbl_1_bss_E4.delay = jumpP->delay;
                }
                jumpP->time = 0;
                jumpP->t = 0;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_198[i][0] = *model->posP[sys->chrSel[i]+MDMODEL_MARIO];
                lbl_1_bss_258[i][1] = lbl_1_data_838[sys->teamOrder[i]];
                lbl_1_bss_258[i][1].x = lbl_1_data_868[sys->teamOrder[i]];
                lbl_1_bss_258[i][1].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][1]);
                lbl_1_bss_258[i][2] = lbl_1_data_838[sys->teamOrder[i]];
                lbl_1_bss_258[i][2].x = lbl_1_data_868[sys->teamOrder[i]];
                lbl_1_bss_258[i][2].y = -8.0f;
                Hu3D2Dto3D(&lbl_1_bss_258[i][2], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][2]);
                lbl_1_bss_258[i][3] = lbl_1_data_838[sys->teamOrder[i]];
                Hu3D2Dto3D(&lbl_1_bss_258[i][3], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][3]);
                lbl_1_bss_118[i][0] = model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y;
                if(sys->teamOrder[i] < 2) {
                    lbl_1_bss_118[i][1] = 360.0f;
                } else {
                    lbl_1_bss_118[i][1] = -360.0f;
                }
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_D4[i] = ParticleGlowCreate(sprite->animP[MDSPR_ANIM_8], 0, camera->camera[MDCAMERA_BG].bit);
            }
            fn_1_15A40(MDBEACH_AUD_SE_MENU_29);
        } else if(param == 6) {
            for(i=0; i<4; i++) {
                if(sys->gameType == 0) {
                    Hu3D3Dto2D(model->posP[sys->chrSel[i]+MDMODEL_MARIO_VOLLEY], camera->camera[MDCAMERA_BG].bit, &pos2D);
                } else if(sys->gameType == 1) {
                    Hu3D3Dto2D(model->posP[sys->chrSel[i]+MDMODEL_MARIO_HOCKEY], camera->camera[MDCAMERA_BG].bit, &pos2D);
                }
                pos2D.x += lbl_1_data_338[sys->gameType][sys->chrSel[i]].x;
                pos2D.y += lbl_1_data_338[sys->gameType][sys->chrSel[i]].y;
                pos2D.z = lbl_1_data_338[sys->gameType][sys->chrSel[i]].z;
                Hu3D2Dto3D(&pos2D, camera->camera[MDCAMERA_BG].bit, &pos3D);
                lbl_1_bss_138[i][0] = pos3D;
                pos2D = lbl_1_data_838[i];
                pos2D.y = -8.0f;
                Hu3D2Dto3D(&pos2D, camera->camera[MDCAMERA_BG].bit, &pos3D);
                pos3D.x = lbl_1_bss_138[i][0].x;
                lbl_1_bss_138[i][1] = pos3D;
            }
            for(i=0; i<4; i++) {
                lbl_1_bss_258[i][3] = lbl_1_data_838[sys->teamOrder[i]];
                Hu3D2Dto3D(&lbl_1_bss_258[i][3], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_198[i][3]);
                *model->posP[sys->chrSel[i]+MDMODEL_MARIO] = lbl_1_bss_198[i][3];
                model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->x = 0;
                model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->y = 0;
                model->rotP[sys->chrSel[i]+MDMODEL_MARIO]->z = 0;
                model->scaleP[sys->chrSel[i]+MDMODEL_MARIO]->x = 1.0f;
                model->scaleP[sys->chrSel[i]+MDMODEL_MARIO]->y = 1.0f;
                model->scaleP[sys->chrSel[i]+MDMODEL_MARIO]->z = 1.0f;
                Hu3DModelDispOn(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO]);
                fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
                Hu3DMotionSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR]);
                Hu3DModelAttrSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], HU3D_MOTATTR_PAUSE);
                playerSpr[i].mode = 4;
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
            switch(jumpP->mode) {
                case 0:
                    if(--jumpP->delay < 0) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR+2], 0, 4, HU3D_MOTATTR_NONE);
                        jumpP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &jumpP->time, &jumpP->t, 30);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][0].x, lbl_1_bss_198[i][1].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][0].y, lbl_1_bss_198[i][1].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][0].z, lbl_1_bss_198[i][1].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR], 0, 30, HU3D_MOTATTR_LOOP);
                        jumpP->time = 0;
                        jumpP->mode++;
                    }
                    break;

                case 2:
                    MdMathOscillate(MDMATH_OSC_90_REV, &jumpP->time, &jumpP->t, 30);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][2].x, lbl_1_bss_198[i][3].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][2].y, lbl_1_bss_198[i][3].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][2].z, lbl_1_bss_198[i][3].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        jumpP->mode++;
                    }
                    break;

                case 3:
                    break;
            }
            fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
        }
        fn_1_146D0();
    } else if(param == 1) {
        for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
            switch(jumpP->mode) {
                case 0:
                    if(--jumpP->delay < 0) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR+2], 0, 2, HU3D_MOTATTR_NONE);
                        jumpP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &jumpP->time, &jumpP->t, 30);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][0].x, lbl_1_bss_198[i][1].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][0].y, lbl_1_bss_198[i][1].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][0].z, lbl_1_bss_198[i][1].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR], 0, 30, HU3D_MOTATTR_LOOP);
                        jumpP->time = 0;
                        jumpP->mode++;
                        if(sys->playerNum == 3) {
                            playerSpr[i].mode = 5;
                            sys->unk36[i] = 1;
                            sys->chrSelEnd[i] = FALSE;
                            Hu3DModelDispOff(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO]);
                            if(sys->gameType == 0) {
                                mdlPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_VOLLEY];
                            } else if(sys->gameType == 1) {
                                mdlPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_HOCKEY];
                            }
                            pos = lbl_1_data_158[sys->gameType][sys->chrSel[i]];
                            pos.x = 640.0f;
                            Hu3D2Dto3D(&pos, camera->camera[MDCAMERA_BG].bit, mdlPosP);
                        } else if(sys->padEnable[i] == FALSE) {
                            playerSpr[i].mode = 5;
                            sys->unk36[i] = 1;
                            sys->chrSelEnd[i] = FALSE;
                            Hu3DModelDispOff(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO]);
                            if(sys->gameType == 0) {
                                mdlPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_VOLLEY];
                            } else if(sys->gameType == 1) {
                                mdlPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_HOCKEY];
                            }
                            pos = lbl_1_data_158[sys->gameType][sys->chrSel[i]];
                            pos.x = 640.0f;
                            Hu3D2Dto3D(&pos, camera->camera[MDCAMERA_BG].bit, mdlPosP);
                        }
                    }
                    break;

                case 2:
                    MdMathOscillate(MDMATH_OSC_90_REV, &jumpP->time, &jumpP->t, 30);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][2].x, lbl_1_bss_198[i][3].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][2].y, lbl_1_bss_198[i][3].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][2].z, lbl_1_bss_198[i][3].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        jumpP->mode++;
                    }
                    break;

                case 3:
                    break;
            }
            fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
        }
        fn_1_146D0();
    } else if(param == 2) {
        for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
            switch(jumpP->mode) {
                case 0:
                    if(--jumpP->delay < 0) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR+2], 0, 2, HU3D_MOTATTR_NONE);
                        jumpP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &jumpP->time, &jumpP->t, 20);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][0].x, lbl_1_bss_198[i][1].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][0].y, lbl_1_bss_198[i][1].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][0].z, lbl_1_bss_198[i][1].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR], 0, 20, HU3D_MOTATTR_LOOP);
                        jumpP->time = 0;
                        jumpP->mode++;
                    }
                    break;

                case 2:
                    MdMathOscillate(MDMATH_OSC_90_REV, &jumpP->time, &jumpP->t, 20);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][2].x, lbl_1_bss_198[i][3].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][2].y, lbl_1_bss_198[i][3].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][2].z, lbl_1_bss_198[i][3].z, jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        jumpP->mode++;
                    }
                    break;

                case 3:
                    break;
            }
            fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
        }
        fn_1_146D0();
        sys->unk2C4 = 1;
        MdProcCall(MDBEACH_PROC_CURSOR, param+sys->unk2C0);
    } else if(param == 3 || param == 4) {
        for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
            switch(jumpP->mode) {
                case 0:
                    if(--jumpP->delay < 0) {
                        jumpP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &jumpP->time, &jumpP->t, 15);
                    if(param == 3) {
                        MdMathLerp(&posP->x, lbl_1_bss_198[i][0].x, lbl_1_bss_198[i][1].x, jumpP->t);
                        MdMathLerp(&posP->y, lbl_1_bss_198[i][0].y, lbl_1_bss_198[i][1].y, jumpP->t);
                        MdMathLerp(&posP->z, lbl_1_bss_198[i][0].z, lbl_1_bss_198[i][1].z, jumpP->t);
                    } else if(param == 4) {
                        MdMathLerp(&posP->x, lbl_1_bss_198[i][1].x, lbl_1_bss_198[i][0].x, jumpP->t);
                        MdMathLerp(&posP->y, lbl_1_bss_198[i][1].y, lbl_1_bss_198[i][0].y, jumpP->t);
                        MdMathLerp(&posP->z, lbl_1_bss_198[i][1].z, lbl_1_bss_198[i][0].z, jumpP->t);
                    }
                    if(jumpP->time >= 1.0f) {
                        jumpP->mode++;
                    }
                    break;

                case 2:
                    break;
            }
            fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
        }
        fn_1_146D0();
        if(param == 3) {
            MdProcCall(MDBEACH_PROC_UNK7, 2);
        } else if(param == 4) {
            MdProcCall(MDBEACH_PROC_UNK7, 3);
        }
    } else if(param == 5) {
        for(jumpP=lbl_1_bss_E8, i=0; i<4; i++, jumpP++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_MARIO];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_MARIO];
            switch(jumpP->mode) {
                case 0:
                    if(--jumpP->delay < 0) {
                        Hu3DMotionShiftSet(model->mdlId[sys->chrSel[i]+MDMODEL_MARIO], model->motId[(sys->chrSel[i]*3)+MDMODEL_MOT_CHR+2], 0, 4, HU3D_MOTATTR_NONE);
                        jumpP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90_REV, &jumpP->time, &jumpP->t, 30);
                    MdMathLerp(&posP->x, lbl_1_bss_198[i][0].x, lbl_1_bss_198[i][1].x, jumpP->t);
                    MdMathLerp(&posP->y, lbl_1_bss_198[i][0].y, lbl_1_bss_198[i][1].y, jumpP->t);
                    MdMathLerp(&posP->z, lbl_1_bss_198[i][0].z, lbl_1_bss_198[i][1].z, jumpP->t);
                    MdMathLerp(&rotP->y, lbl_1_bss_118[i][0], lbl_1_bss_118[i][1], jumpP->t);
                    if(jumpP->time >= 1.0f) {
                        jumpP->mode = 3;
                    }
                    ParticleGlowPosSet(lbl_1_bss_D4[i], posP);
                    break;

                case 3:
                    break;
            }
        }
        fn_1_146D0();
    } else if(param == 6) {
        fn_1_15418(sys->chrSel[i]+MDMODEL_MARIO, MDCAMERA_BG);
        fn_1_146D0();
    }
    if(param == 0) {
        if(lbl_1_bss_E8[lbl_1_bss_E4.playerNo].mode == 3) {
            return TRUE;
        }
    } else if(param == 1) {
        if(lbl_1_bss_E8[lbl_1_bss_E4.playerNo].mode == 3) {
            return TRUE;
        }
    } else if(param == 2) {
        if(lbl_1_bss_E8[lbl_1_bss_E4.playerNo].mode == 3) {
            return TRUE;
        }
    } else if(param == 3 || param == 4) {
        if(lbl_1_bss_E8[2].mode == 2) {
            return TRUE;
        }
    } else if(param == 5) {
        if(lbl_1_bss_E8[lbl_1_bss_E4.playerNo].mode == 3) {
            return TRUE;
        }
    } else if(param == 6) {
        return TRUE;
    }
    return FALSE;
}

/* 0x878 */ float lbl_1_data_878[3] = { 114.0f, 8.0f, 0.0f };

/* 657 insns; mdomake fn_1_2BF8 shape. The two group-6 sprites (24/25) slide along x with message
 * windows 3/4 attached (offset lbl_1_data_878). param 0 slide in (+ PROC_UNK9 0), 1 slide out
 * (+ PROC_UNK9 1), 2 / 3 the second pair of end points in / out, 4 place at the end point.
 * lbl_1_bss_A4 = four (x, y, z) end points. */
BOOL fn_1_118D0(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    MDMESS_WORK *mess; //r28
    HUSPRGRPID grpId; //r27

    sprite = sys->sprite;
    mess = sys->mess;
    grpId = sprite->grpId[MDSPR_GRP_6];
    if(!sys->unk2AC) {
        if(param == 0 || param == 1 || param == 4) {
            lbl_1_bss_A4[0] = -128.0f;
            lbl_1_bss_A4[1] = 252.0f;
            lbl_1_bss_A4[2] = 0;
            lbl_1_bss_A4[3] = 140.0f;
            lbl_1_bss_A4[4] = 252.0f;
            lbl_1_bss_A4[5] = 0;
            lbl_1_bss_A4[6] = 704.0f;
            lbl_1_bss_A4[7] = 252.0f;
            lbl_1_bss_A4[8] = 0;
            lbl_1_bss_A4[9] = 436.0f;
            lbl_1_bss_A4[10] = 252.0f;
            lbl_1_bss_A4[11] = 0;
        } else if(param == 2 || param == 3) {
            lbl_1_bss_A4[0] = 140.0f;
            lbl_1_bss_A4[1] = 252.0f;
            lbl_1_bss_A4[2] = 0;
            lbl_1_bss_A4[3] = 108.0f;
            lbl_1_bss_A4[4] = 252.0f;
            lbl_1_bss_A4[5] = 0;
            lbl_1_bss_A4[6] = 436.0f;
            lbl_1_bss_A4[7] = 252.0f;
            lbl_1_bss_A4[8] = 0;
            lbl_1_bss_A4[9] = 468.0f;
            lbl_1_bss_A4[10] = 252.0f;
            lbl_1_bss_A4[11] = 0;
        }
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
            sprPos->x = lbl_1_bss_A4[0];
            sprPos->y = lbl_1_bss_A4[1];
            HuSprAttrReset(grpId, 0, HUSPR_ATTR_DISPOFF);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
            sprPos->x = lbl_1_bss_A4[6];
            sprPos->y = lbl_1_bss_A4[7];
            HuSprAttrReset(grpId, 1, HUSPR_ATTR_DISPOFF);
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 1) {
            fn_1_15A40(MDBEACH_AUD_SE_MENU_MOVE);
        } else if(param == 4) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
            sprPos->x = lbl_1_bss_A4[3];
            sprPos->y = lbl_1_bss_A4[4];
            HuSprAttrReset(grpId, 0, HUSPR_ATTR_DISPOFF);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
            sprPos->x = lbl_1_bss_A4[9];
            sprPos->y = lbl_1_bss_A4[10];
            HuSprAttrReset(grpId, 1, HUSPR_ATTR_DISPOFF);
        }
        sys->unk2AC = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[0], lbl_1_bss_A4[3], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_3, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[6], lbl_1_bss_A4[9], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_4, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        MdProcCall(MDBEACH_PROC_UNK9, 0);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[3], lbl_1_bss_A4[0], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_3, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[9], lbl_1_bss_A4[6], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_4, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        MdProcCall(MDBEACH_PROC_UNK9, 1);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[0], lbl_1_bss_A4[3], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_3, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[6], lbl_1_bss_A4[9], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_4, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[3], lbl_1_bss_A4[0], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_3, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_A4[9], lbl_1_bss_A4[6], sys->procT);
        MdMessWinPosSet(mess, MDMESS_WIN_4, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
    } else if(param == 4) {
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 0);
        MdMessWinPosSet(mess, MDMESS_WIN_3, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_6, 1);
        MdMessWinPosSet(mess, MDMESS_WIN_4, sprPos->x-lbl_1_data_878[0], sprPos->y-lbl_1_data_878[1]);
        sys->procTime = 1.0f;
    }
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 352 insns; mdmini fn_1_10264 shape. The game's title sprite group (7 Beach Volley, 8 Ice Hockey)
 * drops in from the top: param 0 in, 1 back out, 2 down to the lower position, 3 place at once.
 * lbl_1_bss_8C = two (x, y, z) end points. */
BOOL fn_1_12314(int param)
{
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29

    HuVecF pos; //sp+0x8

    sprite = sys->sprite;
    if(sys->gameType == 0) {
        grpId = sprite->grpId[MDSPR_GRP_7];
    } else if(sys->gameType == 1) {
        grpId = sprite->grpId[MDSPR_GRP_8];
    }
    if(!sys->unk2B4) {
        if(param == 0 || param == 1 || param == 3) {
            lbl_1_bss_8C[0] = 288.0f;
            lbl_1_bss_8C[1] = -96.0f;
            lbl_1_bss_8C[2] = 0;
            lbl_1_bss_8C[3] = 288.0f;
            lbl_1_bss_8C[4] = 88.0f;
            lbl_1_bss_8C[5] = 0;
        } else if(param == 2) {
            lbl_1_bss_8C[0] = 288.0f;
            lbl_1_bss_8C[1] = 88.0f;
            lbl_1_bss_8C[2] = 0;
            lbl_1_bss_8C[3] = 288.0f;
            lbl_1_bss_8C[4] = 128.0f;
            lbl_1_bss_8C[5] = 0;
        }
        if(param == 0) {
            HuSprGrpPosSet(grpId, lbl_1_bss_8C[0], lbl_1_bss_8C[1]);
            if(sys->gameType == 0) {
                MdSpriteDispSet(sprite, MDSPR_GRP_7, TRUE);
            } else if(sys->gameType == 1) {
                MdSpriteDispSet(sprite, MDSPR_GRP_8, TRUE);
            }
        } else if(param == 1) {
        } else if(param == 2) {
        } else if(param == 3) {
            HuSprGrpPosSet(grpId, lbl_1_bss_8C[3], lbl_1_bss_8C[4]);
            if(sys->gameType == 0) {
                MdSpriteDispSet(sprite, MDSPR_GRP_7, TRUE);
            } else if(sys->gameType == 1) {
                MdSpriteDispSet(sprite, MDSPR_GRP_8, TRUE);
            }
        }
        sys->unk2B4 = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        MdMathLerp(&pos.x, lbl_1_bss_8C[0], lbl_1_bss_8C[3], sys->procT);
        MdMathLerp(&pos.y, lbl_1_bss_8C[1], lbl_1_bss_8C[4], sys->procT);
        HuSprGrpPosSet(grpId, pos.x, pos.y);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathLerp(&pos.x, lbl_1_bss_8C[3], lbl_1_bss_8C[0], sys->procT);
        MdMathLerp(&pos.y, lbl_1_bss_8C[4], lbl_1_bss_8C[1], sys->procT);
        HuSprGrpPosSet(grpId, pos.x, pos.y);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
        MdMathLerp(&pos.x, lbl_1_bss_8C[0], lbl_1_bss_8C[3], sys->procT);
        MdMathLerp(&pos.y, lbl_1_bss_8C[1], lbl_1_bss_8C[4], sys->procT);
        HuSprGrpPosSet(grpId, pos.x, pos.y);
    } else if(param == 3) {
        sys->procTime = 1.0f;
    }
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x884 */ HuVecF lbl_1_data_884[3] = { { -12.0f, 320.0f, 500.0f }, { -12.0f, 120.0f, 0.0f }, { -12.0f, 320.0f, -500.0f } }; /* fn_1_12894: VS model pos */
/* 0x8A8 */ HuVecF lbl_1_data_8A8[3] = { { 60.0f, 0.0f, 270.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, -270.0f, 0.0f } }; /* fn_1_12894: VS model rot */

/* 374 insns; mdmini fn_1_10264 shape. The game's VS logo model (MDMODEL_VS_VOLLEY + gameType):
 * param 0 swings in from lbl_1_data_884/8A8[0] to [1] shrinking 3 -> 1, 1 swings on out to [2]
 * shrinking 1 -> 0 and hides it, 2 place at [1]. Own timer sys->unk2DC / unk2F0. */
BOOL fn_1_12894(int param)
{
    HuVecF *scaleP; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *posP; //r29
    HuVecF *rotP; //r28

    MDCAMERA_WORK *camera; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    posP = model->posP[sys->gameType+MDMODEL_VS_VOLLEY];
    rotP = model->rotP[sys->gameType+MDMODEL_VS_VOLLEY];
    scaleP = model->scaleP[sys->gameType+MDMODEL_VS_VOLLEY];
    if(!sys->unk2B0) {
        if(param == 0) {
            *posP = lbl_1_data_884[0];
            *rotP = lbl_1_data_8A8[0];
            scaleP->x = 3.0f;
            scaleP->y = 3.0f;
            scaleP->z = 3.0f;
            Hu3DModelDispOn(model->mdlId[sys->gameType+MDMODEL_VS_VOLLEY]);
        } else if(param == 2) {
            *posP = lbl_1_data_884[1];
            *rotP = lbl_1_data_8A8[1];
            scaleP->x = 1.0f;
            scaleP->y = 1.0f;
            scaleP->z = 1.0f;
            Hu3DModelDispOn(model->mdlId[sys->gameType+MDMODEL_VS_VOLLEY]);
        }
        sys->unk2B0 = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2DC, &sys->unk2F0, 30);
        MdMathLerp(&posP->x, lbl_1_data_884[0].x, lbl_1_data_884[1].x, sys->unk2F0);
        MdMathLerp(&posP->y, lbl_1_data_884[0].y, lbl_1_data_884[1].y, sys->unk2F0);
        MdMathLerp(&posP->z, lbl_1_data_884[0].z, lbl_1_data_884[1].z, sys->unk2F0);
        MdMathLerp(&rotP->x, lbl_1_data_8A8[0].x, lbl_1_data_8A8[1].x, sys->unk2F0);
        MdMathLerp(&rotP->y, lbl_1_data_8A8[0].y, lbl_1_data_8A8[1].y, sys->unk2F0);
        MdMathLerp(&rotP->z, lbl_1_data_8A8[0].z, lbl_1_data_8A8[1].z, sys->unk2F0);
        MdMathLerpScale(scaleP, 3.0f, 1.0f, sys->unk2F0);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2DC, &sys->unk2F0, 30);
        MdMathLerp(&posP->x, lbl_1_data_884[1].x, lbl_1_data_884[2].x, sys->unk2F0);
        MdMathLerp(&posP->y, lbl_1_data_884[1].y, lbl_1_data_884[2].y, sys->unk2F0);
        MdMathLerp(&posP->z, lbl_1_data_884[1].z, lbl_1_data_884[2].z, sys->unk2F0);
        MdMathLerp(&rotP->x, lbl_1_data_8A8[1].x, lbl_1_data_8A8[2].x, sys->unk2F0);
        MdMathLerp(&rotP->y, lbl_1_data_8A8[1].y, lbl_1_data_8A8[2].y, sys->unk2F0);
        MdMathLerp(&rotP->z, lbl_1_data_8A8[1].z, lbl_1_data_8A8[2].z, sys->unk2F0);
        MdMathLerpScale(scaleP, 1.0f, 0.0f, sys->unk2F0);
    } else if(param == 2) {
        sys->unk2DC = 1.0f;
    }
    if(sys->unk2DC >= 1.0f) {
        if(param == 1) {
            Hu3DModelDispOff(model->mdlId[sys->gameType+MDMODEL_VS_VOLLEY]);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x8CC */ HuVecF lbl_1_data_8CC[3] = { { 288.0f, 188.0f, 1500.0f }, { 288.0f, 188.0f, 2000.0f }, { 288.0f, 188.0f, 5000.0f } }; /* fn_1_12E6C: 2D ball positions */
/* 0x8F0 */ HuVecF lbl_1_data_8F0[3] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 40.0f, 0.0f, 0.0f } };

/* 633 insns; mdmini fn_1_F6C4 shape. The three ball models (MDMODEL_BALL_NORMAL/BOMB/DICE),
 * selection sys->unk58 (previous sys->unk59): param 0 the selected ball pops in (scale 0 -> 4 with
 * an overshoot), 1 it shrinks away, 2 the previous ball moves back and shrinks while the new one
 * comes forward and grows (+ PROC_CURSOR unk2C0+2), 3 place them at once (selected at scale 4). */
BOOL fn_1_12E6C(int param)
{
    MDMODEL_WORK *model; //r31
    int i; //r30
    MDCAMERA_WORK *camera; //r29
    HuVecF *posP; //r28

    camera = sys->camera;
    model = sys->model;
    if(!sys->dirtyF) {
        if(param == 0) {
            lbl_1_bss_5C[0][0] = lbl_1_data_8CC[1];
            Hu3D2Dto3D(&lbl_1_bss_5C[0][0], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_2C[0][0]);
            for(i=0; i<3; i++) {
                *model->posP[i+MDMODEL_BALL_NORMAL] = lbl_1_bss_2C[0][0];
                *model->rotP[i+MDMODEL_BALL_NORMAL] = lbl_1_data_8F0[i];
                model->scaleP[i+MDMODEL_BALL_NORMAL]->x = 0;
                model->scaleP[i+MDMODEL_BALL_NORMAL]->y = 0;
                model->scaleP[i+MDMODEL_BALL_NORMAL]->z = 0;
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_BALL_NORMAL]);
            }
        } else if(param == 1) {
        } else if(param == 2) {
            lbl_1_bss_5C[0][0] = lbl_1_data_8CC[1];
            lbl_1_bss_5C[0][1] = lbl_1_data_8CC[2];
            lbl_1_bss_5C[1][0] = lbl_1_data_8CC[0];
            lbl_1_bss_5C[1][1] = lbl_1_data_8CC[1];
            for(i=0; i<2; i++) {
                Hu3D2Dto3D(&lbl_1_bss_5C[0][i], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_2C[0][i]);
                Hu3D2Dto3D(&lbl_1_bss_5C[1][i], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_2C[1][i]);
            }
        } else if(param == 3) {
            lbl_1_bss_5C[0][0] = lbl_1_data_8CC[1];
            Hu3D2Dto3D(&lbl_1_bss_5C[0][0], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_2C[0][0]);
            *model->posP[sys->unk58+MDMODEL_BALL_NORMAL] = lbl_1_bss_2C[0][0];
            *model->rotP[sys->unk58+MDMODEL_BALL_NORMAL] = lbl_1_data_8F0[sys->unk58];
            model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL]->x = 4.0f;
            model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL]->y = 4.0f;
            model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL]->z = 4.0f;
            Hu3DModelDispOn(model->mdlId[sys->unk58+MDMODEL_BALL_NORMAL]);
            for(i=0; i<3; i++) {
                if(i != sys->unk58) {
                    *model->posP[i+MDMODEL_BALL_NORMAL] = lbl_1_bss_2C[0][0];
                    *model->rotP[i+MDMODEL_BALL_NORMAL] = lbl_1_data_8F0[i];
                    model->scaleP[i+MDMODEL_BALL_NORMAL]->x = 0;
                    model->scaleP[i+MDMODEL_BALL_NORMAL]->y = 0;
                    model->scaleP[i+MDMODEL_BALL_NORMAL]->z = 0;
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_BALL_NORMAL]);
                }
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15);
        MdMathLerpScaleOfs(model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL], 0, 4.0f, sys->procT, sys->procOfsT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        MdMathLerpScale(model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL], 4.0f, 0, sys->procT);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
        MdMathLerpScale(model->scaleP[sys->unk59+MDMODEL_BALL_NORMAL], 4.0f, 0, sys->procT);
        MdMathLerpScale(model->scaleP[sys->unk58+MDMODEL_BALL_NORMAL], 8.0f, 4.0f, sys->procT);
        posP = model->posP[sys->unk59+MDMODEL_BALL_NORMAL];
        MdMathLerp(&posP->x, lbl_1_bss_2C[0][0].x, lbl_1_bss_2C[0][1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_2C[0][0].y, lbl_1_bss_2C[0][1].y, sys->procT);
        MdMathLerp(&posP->z, lbl_1_bss_2C[0][0].z, lbl_1_bss_2C[0][1].z, sys->procT);
        posP = model->posP[sys->unk58+MDMODEL_BALL_NORMAL];
        MdMathLerp(&posP->x, lbl_1_bss_2C[1][0].x, lbl_1_bss_2C[1][1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_2C[1][0].y, lbl_1_bss_2C[1][1].y, sys->procT);
        MdMathLerp(&posP->z, lbl_1_bss_2C[1][0].z, lbl_1_bss_2C[1][1].z, sys->procT);
        sys->unk2C4 = 3;
        MdProcCall(MDBEACH_PROC_CURSOR, sys->unk2C0+2);
    } else if(param == 3) {
        sys->procTime = 1.0f;
    }
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 119 insns; mdmini fn_1_149A4 (mdparty MdPartyProcName shape): fades sprite 2 of group 5 */
BOOL fn_1_13850(int param)
{
    HUSPRGRPID grpId; //r31
    MDSPRITE_WORK *sprite; //r29

    float tpLvl; //sp+0x8

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_5];
    if(!sys->dirtyF) {
        if(param == 0) {
            HuSprTPLvlSet(grpId, 2, 0);
        } else if(param == 1) {
            HuSprTPLvlSet(grpId, 2, 0.5f);
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15);
        MdMathLerp(&tpLvl, 0, 0.5f, sys->procT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        MdMathLerp(&tpLvl, 0, 0.5f, sys->procT);
    }
    HuSprTPLvlSet(grpId, 2, tpLvl);
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 160 insns; mdmini fn_1_113D8 (mdparty MdPartyProcFinger) */
BOOL fn_1_13A2C(int param)
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
            fn_1_146D0();
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

/* 126 insns; mdmini fn_1_14C2C (mdparty MdPartyPadSetup) */
void fn_1_13CAC(void)
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

/* 107 insns; mdmini fn_1_14E24 (mdparty MdPartyPadSetupStory) */
void fn_1_13EA4(void)
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

/* 193 insns; mdmini fn_1_14FD0 (mdparty MdPartyPlayerSetupInit) */
void fn_1_14050(void)
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

/* 223 insns; mdmini fn_1_152D4 (mdparty MdPartyPlayerCfgRead) plus the match settings read back
 * from mgMatchGameType / mgMatchMaxScore (the inverse of fn_1_15508) */
void fn_1_14354(void)
{
    int i;
    for(i=0; i<4; i++) {
        sys->chrSel[i] = GwPlayerConf[i].charNo;
        sys->comDif[i] = GwPlayerConf[i].dif;
    }
    if(GwPlayer[1].grp == 0) {
        sys->teamOrderNo = 0;
    } else if(GwPlayer[2].grp == 0) {
        sys->teamOrderNo = 1;
    } else if(GwPlayer[3].grp == 0) {
        sys->teamOrderNo = 2;
    }
    fn_1_15048();
    fn_1_153C8();
    if(sys->gameType == 0) {
        if(mgMatchGameType == 0) {
            sys->unk58 = 0;
        } else if(mgMatchGameType == 1) {
            sys->unk58 = 1;
        } else if(mgMatchGameType == 2) {
            sys->unk58 = 2;
        }
        if((mgMatchMaxScore & 0xFF) == 10) {
            sys->unk5A = 0;
        } else if((mgMatchMaxScore & 0xFF) == 15) {
            sys->unk5A = 1;
        } else if((mgMatchMaxScore & 0xFF) == 20) {
            sys->unk5A = 2;
        } else {
            sys->unk5A = 0;
        }
    } else if(sys->gameType == 1) {
        if(mgMatchMaxScore == 1) {
            sys->unk5A = 0;
        } else if(mgMatchMaxScore == 2) {
            sys->unk5A = 1;
        } else if(mgMatchMaxScore == 3) {
            sys->unk5A = 2;
        } else {
            sys->unk5A = 0;
        }
    }
    for(i=0; i<4; i++) {
        sys->chrSelEnd[i] = TRUE;
    }
    sys->selComNo = 3-sys->playerNum;
}

/* 230 insns; mdmini fn_1_153D0 (mdparty MdPartyPlayerSprUpdate): the finger sits at the 2D
 * offset lbl_1_data_248[gameType][chr] from the game-costume character; the player number /
 * COM level sprites at lbl_1_data_518[chr] from the plain character */
void fn_1_146D0(void)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    MDCAMERA_WORK *camera; //r29
    MDSPRITE_WORK *sprite; //r28
    HuVecF *chrPosP; //r27
    HuVecF *fingerPosP; //r26
    HuVecF *sprChrPosP; //r25
    HUSPRGRPID playerNoGrpId; //r24
    HUSPRGRPID comDifGrpId; //r23

    HuVecF pos3D; //sp+0x1C
    HuVecF pos2D; //sp+0x10
    HuVec2f *sprPos[2]; //sp+0x8 (player number, COM level)

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    comDifGrpId = sprite->grpId[MDSPR_GRP_COMDIF];
    HuSprGrpPosSet(playerNoGrpId, 0, 0);
    HuSprGrpPosSet(comDifGrpId, 0, 0);
    for(i=0; i<4; i++) {
        fingerPosP = model->posP[i+MDMODEL_FINGER_1P];
        if(sys->gameType == 0) {
            chrPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_VOLLEY];
        } else if(sys->gameType == 1) {
            chrPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO_HOCKEY];
        }
        sprChrPosP = model->posP[sys->chrSel[i]+MDMODEL_MARIO];
        pos3D = *chrPosP;
        Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_BG].bit, &pos2D);
        pos2D.x += lbl_1_data_248[sys->gameType][sys->chrSel[i]].x;
        pos2D.y += lbl_1_data_248[sys->gameType][sys->chrSel[i]].y;
        pos2D.z = lbl_1_data_248[sys->gameType][sys->chrSel[i]].z;
        Hu3D2Dto3D(&pos2D, camera->camera[MDCAMERA_BG].bit, &pos3D);
        *fingerPosP = pos3D;
        pos3D = *sprChrPosP;
        Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_BG].bit, &pos2D);
        sprPos[0] = MdSpritePosGet(sprite, MDSPR_GRP_PLAYERNO, i);
        sprPos[1] = MdSpritePosGet(sprite, MDSPR_GRP_COMDIF, i);
        sprPos[0]->x = sprPos[1]->x = pos2D.x+lbl_1_data_518[sys->chrSel[i]].x;
        sprPos[0]->y = sprPos[1]->y = pos2D.y+lbl_1_data_518[sys->chrSel[i]].y;
    }
}

/* 0x914 */ s8 lbl_1_data_914[10][2][4] = { /* fn_1_14A68: per character, UP candidates [0] and DOWN candidates [1] */
    { { 6, 9, 7, 8 }, { 6, 7, 9, 8 } },
    { { 7, 6, 8, 9 }, { 7, 8, 6, 9 } },
    { { 7, 8, 6, 9 }, { 8, 7, 9, 6 } },
    { { 7, 8, 6, 9 }, { 8, 7, 9, 6 } },
    { { 8, 7, 9, 6 }, { 8, 9, 7, 6 } },
    { { 9, 8, 6, 7 }, { 9, 6, 8, 7 } },
    { { 0, 5, 1, 4 }, { 0, 1, 5, 2 } },
    { { 1, 0, 2, 5 }, { 1, 2, 0, 3 } },
    { { 4, 3, 5, 2 }, { 4, 5, 3, 0 } },
    { { 5, 4, 0, 3 }, { 5, 0, 4, 1 } }
};

/* 311 insns; mdmini fn_1_15590 (mdparty MdPartyChrSelCursorUpdate); UP/DOWN pick from the
 * per-character candidate lists lbl_1_data_914 instead of mdmini's fixPos rows */
BOOL fn_1_14A68(int playerNo, BOOL comSelF)
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
            sys->unk32[playerNo] = sys->chrSel[playerNo];
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
                for(i=0; i<4; i++) {
                    if(selFlag[lbl_1_data_914[sys->chrSel[playerNo]][0][i]] == -1) {
                        sys->chrSel[playerNo] = lbl_1_data_914[sys->chrSel[playerNo]][0][i];
                        break;
                    }
                }
            } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_DOWN) {
                for(i=0; i<4; i++) {
                    if(selFlag[lbl_1_data_914[sys->chrSel[playerNo]][1][i]] == -1) {
                        sys->chrSel[playerNo] = lbl_1_data_914[sys->chrSel[playerNo]][1][i];
                        break;
                    }
                }
            }
            return TRUE;
        } else {
            return FALSE;
        }

}

/* 65 insns; mdmini fn_1_15BF4 (mdparty MdPartyChrComInit) */
void fn_1_14F44(void)
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

/* 0x964 */ s8 lbl_1_data_964[3][4] = { { 0, 1, 2, 3 }, { 0, 2, 1, 3 }, { 0, 3, 1, 2 } }; /* fn_1_15048; mdparty teamPlayer */
/* 0x970 */ s8 lbl_1_data_970[3][4] = { { 0, 1, 2, 3 }, { 0, 2, 1, 3 }, { 0, 2, 3, 1 } }; /* fn_1_15048; mdparty teamOrder */
/* 0x97C */ s8 lbl_1_data_97C[45][2] = { /* fn_1_15048; mdparty teamChr */
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

/* 224 insns; mdmini fn_1_15DE8 (mdparty MdPartyTeamPlayerUpdate) */
void fn_1_15048(void)
{
    int i; //r31
    int j; //r30
    int comNum; //r29

    comNum = 0;
    for(i=0; i<2; i++) {
        sys->teamPlayer[0][i] = lbl_1_data_964[sys->teamOrderNo][i];
        sys->teamPlayer[1][i] = lbl_1_data_964[sys->teamOrderNo][i+2];
    }
    for(i=0; i<4; i++) {
        sys->teamOrder[i] = lbl_1_data_970[sys->teamOrderNo][i];
    }
    for(i=0; i<2; i++) {
        for(j=0; j<45; j++) {
            if((sys->chrSel[sys->teamPlayer[i][0]] == lbl_1_data_97C[j][0] &&
                sys->chrSel[sys->teamPlayer[i][1]] == lbl_1_data_97C[j][1]) ||
                (sys->chrSel[sys->teamPlayer[i][1]] == lbl_1_data_97C[j][0] &&
                sys->chrSel[sys->teamPlayer[i][0]] == lbl_1_data_97C[j][1])) {
                    sys->teamNo[i] = j;
                    break;
                }
        }
    }

    for(i=0; i<3; i++) {
        sys->teamComPlayerNo[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(!sys->padEnable[lbl_1_data_964[sys->teamOrderNo][i]]) {
            sys->teamComPlayerNo[comNum] = lbl_1_data_964[sys->teamOrderNo][i];
            comNum++;
            if(comNum >= 3) {
                break;
            }
        }
    }
}

/* 20 insns; mdmini fn_1_16168 (mdparty MdPartyTeamOrderBackup) */
void fn_1_153C8(void)
{
    int i;
    for(i=0; i<4; i++) {
        sys->teamOrderBackup[i] = sys->teamOrder[i];
    }
}

/* 60 insns; mdmini fn_1_15CF8 (mdparty MdPartyModelBBoardSet) */
void fn_1_15418(int mdlNo, int cameraNo)
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

/* 334 insns; mdmini fn_1_16978 (mdparty MdPartySaveInit, reduced): the match settings for the
 * minigame (m433 Beach Volley: mgMatchGameType 0-2 from unk58 and the max score from unk5A;
 * m580 Ice Hockey: max score 1-3), then the per-player GwPlayer / GwPlayerConf setup */
void fn_1_15508(void)
{
    int i;
    if(sys->gameType == 0) {
        if(sys->unk58 == 0) {
            mgMatchGameType = 0;
        } else if(sys->unk58 == 1) {
            mgMatchGameType = 1;
        } else if(sys->unk58 == 2) {
            mgMatchGameType = 2;
        }
        if(sys->unk58 == 2) {
            if(sys->unk5A == 0) {
                mgMatchMaxScore = 1546;
            } else if(sys->unk5A == 1) {
                mgMatchMaxScore = 1551;
            } else if(sys->unk5A == 2) {
                mgMatchMaxScore = 1556;
            }
        } else {
            if(sys->unk5A == 0) {
                mgMatchMaxScore = 10;
            } else if(sys->unk5A == 1) {
                mgMatchMaxScore = 15;
            } else if(sys->unk5A == 2) {
                mgMatchMaxScore = 20;
            }
        }
    } else if(sys->gameType == 1) {
        if(sys->unk5A == 0) {
            mgMatchMaxScore = 1;
        } else if(sys->unk5A == 1) {
            mgMatchMaxScore = 2;
        } else if(sys->unk5A == 2) {
            mgMatchMaxScore = 3;
        }
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
        if(sys->teamOrder[i] <= 1) {
            GwPlayer[i].grp = 0;
        } else {
            GwPlayer[i].grp = 1;
        }
        GwPlayerConf[i].charNo = GwPlayer[i].charNo;
        GwPlayerConf[i].padNo = GwPlayer[i].padNo = i;
        GwPlayerConf[i].dif = GwPlayer[i].dif;
        GwPlayerConf[i].type = GwPlayer[i].comF;
        GwPlayerConf[i].grp = GwPlayer[i].grp;
    }
}

/* 0x9D8 */ s32 lbl_1_data_9D8[10] = { 0x201, 0x1ED, 0x265, 0x2B5, 0x28D, 0x1C5, 0x2A1, 0x1D9, 0x279, 0x23D }; /* fn_1_15A40: character voices */

/* 98 insns; mdparty MdPartyAudExec (command numbers: MDBEACH_AUD_* in mdbeachdll.gen.h) */
void fn_1_15A40(int cmd)
{
    switch(cmd) {
        case MDBEACH_AUD_MUS_START:
            lbl_1_bss_28 = HuAudBGMPlay(MSM_STREAM_MGDECA);
            break;

        case MDBEACH_AUD_MUS_STOP:
            HuAudSStreamFadeOut(lbl_1_bss_28, 1000);
            break;

        case MDBEACH_AUD_SE_CMN_MOVE:
        case MDBEACH_AUD_SE_CMN_CONFIRM:
        case MDBEACH_AUD_SE_CMN_CHRSEL:
        case MDBEACH_AUD_SE_CMN_CANCEL:
        case MDBEACH_AUD_SE_MENU_MOVE:
        case MDBEACH_AUD_SE_MENU_29:
            if(cmd == MDBEACH_AUD_SE_CMN_MOVE) {
                HuAudFXPlay(MSM_SE_CMN_01);
            } else if(cmd == MDBEACH_AUD_SE_CMN_CONFIRM) {
                HuAudFXPlay(MSM_SE_CMN_03);
            } else if(cmd == MDBEACH_AUD_SE_CMN_CHRSEL) {
                HuAudFXPlay(MSM_SE_CMN_02);
            } else if(cmd == MDBEACH_AUD_SE_CMN_CANCEL) {
                HuAudFXPlay(MSM_SE_CMN_04);
            } else if(cmd == MDBEACH_AUD_SE_MENU_MOVE) {
                HuAudFXPlay(MSM_SE_MENU_27);
            } else if(cmd == MDBEACH_AUD_SE_MENU_29) {
                HuAudFXPlay(MSM_SE_MENU_29);
            }
            break;

        case MDBEACH_AUD_SE_CHR_SEL:
        case MDBEACH_AUD_SE_CHR_SEL+1:
        case MDBEACH_AUD_SE_CHR_SEL+2:
        case MDBEACH_AUD_SE_CHR_SEL+3:
        case MDBEACH_AUD_SE_CHR_SEL+4:
        case MDBEACH_AUD_SE_CHR_SEL+5:
        case MDBEACH_AUD_SE_CHR_SEL+6:
        case MDBEACH_AUD_SE_CHR_SEL+7:
        case MDBEACH_AUD_SE_CHR_SEL+8:
        case MDBEACH_AUD_SE_CHR_SEL+9:
        {
            int pan = fn_1_15BC8((cmd-MDBEACH_AUD_SE_CHR_SEL)+MDMODEL_MARIO, MDCAMERA_BG);
            HuAudFXPlayPan(MSM_SE_MENU_28, pan);
        }
            break;

        case MDBEACH_AUD_SE_CHR_VOICE:
        case MDBEACH_AUD_SE_CHR_VOICE+1:
        case MDBEACH_AUD_SE_CHR_VOICE+2:
        case MDBEACH_AUD_SE_CHR_VOICE+3:
        case MDBEACH_AUD_SE_CHR_VOICE+4:
        case MDBEACH_AUD_SE_CHR_VOICE+5:
        case MDBEACH_AUD_SE_CHR_VOICE+6:
        case MDBEACH_AUD_SE_CHR_VOICE+7:
        case MDBEACH_AUD_SE_CHR_VOICE+8:
        case MDBEACH_AUD_SE_CHR_VOICE+9:
        {
            int pan = fn_1_15BC8((cmd-MDBEACH_AUD_SE_CHR_VOICE)+MDMODEL_MARIO, MDCAMERA_BG);
            HuAudFXPlayPan(lbl_1_data_9D8[cmd-MDBEACH_AUD_SE_CHR_VOICE], pan);
        }
            break;

        case MDBEACH_AUD_SE_STAR:
        {
            int pan = fn_1_15BC8(MDMODEL_STAR, MDCAMERA_MAIN);
            if(cmd == MDBEACH_AUD_SE_STAR) {
                HuAudFXPlayPan(MSM_SE_GUIDE_53, pan);
            }
        }
            break;

        case MDBEACH_AUD_SE_ALL_STOP:
            HuAudAllStop();
            break;
    }
}

/* 46 insns; mdmini fn_1_171B4 (mdsel MdSelFXPanGet / mdparty MdPartyFXPanGet) */
int fn_1_15BC8(int mdlNo, int cameraNo)
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

/* 1114 insns; mdmini/mdomake MdPosAdjustMode */
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
    
    
    static MDMODEL_DEBUG_INFO mdlInfo_S1113[MDMODEL_MAX] = {
        { "STAR", MDCAMERA_MAIN },
        { "MARIO", MDCAMERA_BG },
        { "LUIGI", MDCAMERA_BG },
        { "PEACH", MDCAMERA_BG },
        { "YOSHI", MDCAMERA_BG },
        { "WARIO", MDCAMERA_BG },
        { "DAISY", MDCAMERA_BG },
        { "WALUIGI", MDCAMERA_BG },
        { "KINOPIO", MDCAMERA_BG },
        { "TERESA", MDCAMERA_BG },
        { "MINIKOOPA", MDCAMERA_BG },
        { "MARIO_VOLLEY", MDCAMERA_BG },
        { "LUIGI_VOLLEY", MDCAMERA_BG },
        { "PEACH_VOLLEY", MDCAMERA_BG },
        { "YOSHI_VOLLEY", MDCAMERA_BG },
        { "WARIO_VOLLEY", MDCAMERA_BG },
        { "DAISY_VOLLEY", MDCAMERA_BG },
        { "WALUIGI_VOLLEY", MDCAMERA_BG },
        { "KINOPIO_VOLLEY", MDCAMERA_BG },
        { "TERESA_VOLLEY", MDCAMERA_BG },
        { "MINIKOOPA_VOLLEY", MDCAMERA_BG },
        { "MARIO_HOCKEY", MDCAMERA_BG },
        { "LUIGI_HOCKEY", MDCAMERA_BG },
        { "PEACH_HOCKEY", MDCAMERA_BG },
        { "YOSHI_HOCKEY", MDCAMERA_BG },
        { "WARIO_HOCKEY", MDCAMERA_BG },
        { "DAISY_HOCKEY", MDCAMERA_BG },
        { "WALUIGI_HOCKEY", MDCAMERA_BG },
        { "KINOPIO_HOCKEY", MDCAMERA_BG },
        { "TERESA_HOCKEY", MDCAMERA_BG },
        { "MINIKOOPA_HOCKEY", MDCAMERA_BG },
        { "CAP_MAN_1P", MDCAMERA_BG },
        { "CAP_MAN_2P", MDCAMERA_BG },
        { "CAP_MAN_3P", MDCAMERA_BG },
        { "CAP_MAN_4P", MDCAMERA_BG },
        { "CAP_COM_1P", MDCAMERA_BG },
        { "CAP_COM_2P", MDCAMERA_BG },
        { "CAP_COM_3P", MDCAMERA_BG },
        { "CAP_COM_4P", MDCAMERA_BG },
        { "FINGER_1P", MDCAMERA_BG },
        { "FINGER_2P", MDCAMERA_BG },
        { "FINGER_3P", MDCAMERA_BG },
        { "FINGER_4P", MDCAMERA_BG },
        { "FLASH_1P", MDCAMERA_BG },
        { "FLASH_2P", MDCAMERA_BG },
        { "FLASH_3P", MDCAMERA_BG },
        { "FLASH_4P", MDCAMERA_BG },
        { "VS_VOLLEY", MDCAMERA_BG },
        { "VS_HOCKEY", MDCAMERA_BG },
        { "BALL_NORMAL", MDCAMERA_BG },
        { "BALL_BOMB", MDCAMERA_BG },
        { "BALL_DICE", MDCAMERA_BG },
        { "FONTBGFILTER", MDCAMERA_MAIN },
    };
    static MDMODEL_DEBUG_INFO *mdlInfoP_S1131;
    static HuVec2f sprPos_S1132;
    static float sprRot_S1133;
    static int menuSel_S1134;
    static int mdlSel_S1135;
    static int dispTimer_S1136;
    static BOOL showF_S1137;
    
    debugFont = sys->debugFont;
    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_LR];
    if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
        if(showF_S1137 == FALSE) {
            if(HuPadBtn[0] & PAD_BUTTON_X) {
                if(++dispTimer_S1136 >= 60) {
                    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, TRUE);
                    dispTimer_S1136 = 0;
                    showF_S1137 = TRUE;
                }
            } else {
                dispTimer_S1136 = 0;
            }
        } else if(showF_S1137 == TRUE) {
            while(1) {
                if(HuPadBtn[0] & PAD_BUTTON_X) {
                    if(++dispTimer_S1136 >= 60) {
                        MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
                        dispTimer_S1136 = 0;
                        showF_S1137 = FALSE;
                        break;
                    }
                } else {
                    dispTimer_S1136 = 0;
                }
                if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
                    if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                        for(i=0; i<MDMODEL_MAX; i++) {
                            if(--mdlSel_S1135 == -1) {
                                mdlSel_S1135 = MDMODEL_MAX-1;
                            }
                            attr = Hu3DModelAttrGet(model->mdlId[mdlSel_S1135]);
                            if(!(attr & HU3D_ATTR_DISPOFF)) {
                                break;
                            }
                        }
                    } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                        for(i=0; i<MDMODEL_MAX; i++) {
                            mdlSel_S1135 = ++mdlSel_S1135 % MDMODEL_MAX;
                            attr = Hu3DModelAttrGet(model->mdlId[mdlSel_S1135]);
                            if(!(attr & HU3D_ATTR_DISPOFF)) {
                                break;
                            }
                        }
                    }
                    if(HuPadBtnDown[0] & PAD_BUTTON_DOWN) {
                        menuSel_S1134 = ++menuSel_S1134 % 3;
                    }
                    mdlInfoP_S1131 = &mdlInfo_S1113[mdlSel_S1135];
                    pos = model->posP[mdlSel_S1135];
                    rot = model->rotP[mdlSel_S1135];
                    scale = model->scaleP[mdlSel_S1135];
                    attr = Hu3DModelAttrGet(model->mdlId[mdlSel_S1135]);
                    if(menuSel_S1134 == 0) {
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
                    } else if(menuSel_S1134 == 1) {
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
                    } else if(menuSel_S1134 == 2) {
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
                sprRot_S1133 += 2;
                MdMathAngleClamp(&sprRot_S1133);
                HuSprGrpZRotSet(grpId, sprRot_S1133);
                Hu3D3Dto2D(pos, camera->camera[mdlInfoP_S1131->cameraNo].bit, &pos2D);
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
                MdDebugFontPrint(debugFont, "POS-ADJUST-MODE(%2d / %2d) -> %s", mdlSel_S1135, MDMODEL_MAX, mdlInfoP_S1131->name);
                if(debugFont->ctrl == MD_DEBUGFONT_CTRL_MODEL) {
                    if(menuSel_S1134 == 0) {
                        MdDebugFontPrint(debugFont, "*  POS(%.1f / %.1f / %.1f)", pos->x, pos->y, pos->z);
                    } else {
                        MdDebugFontPrint(debugFont, "   POS(%.1f / %.1f / %.1f)", pos->x, pos->y, pos->z);
                    }
                    if(menuSel_S1134 == 1) {
                        MdDebugFontPrint(debugFont, "*  ROT(%.1f / %.1f / %.1f)", rot->x, rot->y, rot->z);
                    } else {
                        MdDebugFontPrint(debugFont, "   ROT(%.1f / %.1f / %.1f)", rot->x, rot->y, rot->z);
                    }
                    if(menuSel_S1134 == 2) {
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

/* 1 insns */
void fn_1_16DE8(void)
{
}

/* --- .bss declared last (lowest addresses; MdPosAdjustMode's statics are 0x8-0x27) --- */
/* 0x5 gap_05_00000005_bss (0x3): alignment gap */
/* 0x4 */ s8 lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;
