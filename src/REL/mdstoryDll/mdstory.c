/*
 * mdstoryDll mdstory.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mdstoryDll/asm/REL/mdstoryDll/mdstory.s.
 */

#include "REL/mdstoryDll.h"

/* mdparty.c/mdmini.c precedent: the particle helpers come from an #included .c, included right
 * after the overlay header and BEFORE game/frand.h: retail calls frandmod unprototyped there.
 * Its HU3DPARMANPARAM statics are .data 0x0-0x13F; its six static functions are emitted last in .text. */
#include "REL/mdstoryDll/effect.c"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/saveload.h"
#include "game/wipe.h"
#include "game/charman.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "math.h"
#include "messnum/syshelp.h" /* includes messdir_enum.h: MESS_STORYMODE_SYS has no messnum header yet */

/* mdparty.c MDPARTY_LERP_DATA (lbl_1_data_544) */
typedef struct MdStoryLerpData_s {
    HuVecF hvrA;
    HuVecF centerA;
    HuVecF hvrB;
    HuVecF centerB;
    int type;
    float step;
} MDSTORY_LERP_DATA;

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
static const float lbl_1_rodata_54 = 220.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 292.0f; /* 0x58 */
static const float lbl_1_rodata_5C = -1.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 32.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 15.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 0.5f; /* 0x68 */
static const float lbl_1_rodata_6C = 372.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 56.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 376.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 340.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 8.0f; /* 0x7C */
static const double lbl_1_rodata_80 = 0.9200000166893005; /* 0x80 */
static const float lbl_1_rodata_88 = 145.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 400.0f; /* 0x8C */
static const float lbl_1_rodata_90 = -64.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 80.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 640.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 24.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 1.5f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 12.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = -2.0f; /* 0xA8 */
static const float lbl_1_rodata_AC = 2.0f; /* 0xAC */
static const float lbl_1_rodata_B0 = 72.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = -28.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 352.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 224.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 1500.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 200.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 0.1f; /* 0xC8 */
static const float lbl_1_rodata_CC = 0.2f; /* 0xCC */
static const float lbl_1_rodata_D0 = 525.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 365.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = -50.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 0.8f; /* 0xDC */
static const float lbl_1_rodata_E0 = -525.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 4.0f; /* 0xE4 */
/* 0xE8 lbl_1_rodata_E8 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
/* 0xE9 lbl_1_rodata_E9 (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
/* 0xEC lbl_1_rodata_EC (0x1): 0xFF -- an aggregate initialiser, write it as a local */
/* 0xED lbl_1_rodata_ED (0x3): 0xFF, 0xFF, 0xFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_F0 = 105.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 18.0f; /* 0xF4 */
static const double lbl_1_rodata_F8 = 180.0; /* 0xF8 */
static const double lbl_1_rodata_100 = 3.141592653589793; /* 0x100 */
/* 0x108 lbl_1_rodata_108 (0x18): 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_120 = 0.11111111f; /* 0x120 */
static const float lbl_1_rodata_124 = 5.0f; /* 0x124 */
static const float lbl_1_rodata_128 = 10.0f; /* 0x128 */
static const float lbl_1_rodata_12C = 0.05f; /* 0x12C */
static const float lbl_1_rodata_130 = 0.01f; /* 0x130 */
static const float lbl_1_rodata_134 = -32.0f; /* 0x134 */
static const float lbl_1_rodata_138 = 0.4f; /* 0x138 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x120 */ SYS sysWork;
/* 0x11C */ SYS *sys;
/* 0x118 */ SYS *sysP;
/* 0x100 */ HuVecF lbl_1_bss_100[2];
/* 0xE8 */ HuVecF lbl_1_bss_E8[2];
/* 0xE4 */ float lbl_1_bss_E4;
/* 0xE0 */ float lbl_1_bss_E0;
/* 0xDC */ float lbl_1_bss_DC;
/* 0xD8 */ float lbl_1_bss_D8;
/* 0xD4 */ float lbl_1_bss_D4;
/* 0xD0 */ float lbl_1_bss_D0;
/* 0xA0 */ HuVecF lbl_1_bss_A0[4]; /* fn_1_4A98: cursor positions (mdparty ProcCursor pos[]) */
/* 0x9C */ s32 lbl_1_bss_9C;
/* 0x98 */ float lbl_1_bss_98;
/* 0x94 */ float lbl_1_bss_94;
/* 0x90 */ float lbl_1_bss_90;
/* 0x88 */ MDSTORY_EFFECT *lbl_1_bss_88[2]; /* fn_1_5B08: particle dot / glow effects */
/* 0x70 */ HuVecF lbl_1_bss_70[2]; /* fn_1_5B08: [1] = screen pos of the chosen character */
/* 0x58 */ HuVecF lbl_1_bss_58[2]; /* fn_1_5B08: chosen character start / end pos */
/* 0x40 */ HuVecF lbl_1_bss_40[2]; /* fn_1_709C: CAP_LV start/end position */
/* 0x28 */ HuVecF lbl_1_bss_28[2]; /* fn_1_766C lerpPos (a function static in the mdparty twin) */
/* 0x24 */ s32 lbl_1_bss_24;
/* 0x20 */ s32 lbl_1_bss_20;

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x144 */ char *lbl_1_data_144[1] = {
    "26"
};
/* 0x148 */ OMOVL lbl_1_data_148[7] = { /* the story boards, indexed by board number */
    DLL_w01sdll,
    DLL_w02sdll,
    DLL_w03sdll,
    DLL_w04sdll,
    DLL_w05sdll,
    DLL_w06sdll,
    DLL_w07sdll
};
/* 0x164 */ u32 lbl_1_data_164[7] = { DATA_w01s, DATA_w02s, DATA_w03s, DATA_w04s, DATA_w05s, DATA_w06s, DATA_w07s };
/* 0x180 */ HuVecF lbl_1_data_180[7][2] = { /* mdparty CharPos (first seven rows) */
    { { -250.0f, 0.0f, 0.0f }, { -250.0f, 0.0f, 0.0f } },
    { { -125.0f, 0.0f, 0.0f }, { -125.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 125.0f, 0.0f, 0.0f }, { 139.0f, 17.5f, -500.0f } },
    { { 275.0f, 9.0f, -300.0f }, { 266.0f, 2.0f, -200.0f } },
    { { -250.0f, -250.0f, 0.0f }, { -250.0f, -250.0f, 0.0f } },
    { { -125.0f, -250.0f, 0.0f }, { -140.5f, -270.0f, -400.0f } }
};
/* 0x228 */ HuVecF lbl_1_data_228[7][2] = { /* mdparty CharRot (first seven rows) */
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 10.0f, -2.0f, 0.0f }, { 10.0f, -4.0f, 0.0f } },
    { { 0.0f, -3.0f, 0.0f }, { 0.0f, -6.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }
};
/* 0x2D0 */ MD_FUNC MdFlowTbl[MDSTORY_FLOW_MAX] = {
    fn_1_2204,
    fn_1_24FC,
    fn_1_2D88,
    fn_1_3438,
    fn_1_3C2C
};
/* 0x2E4 */ MD_PROC MdProcTbl[MDSTORY_PROC_MAX] = {
    fn_1_46E4,
    fn_1_48EC,
    fn_1_4A98,
    fn_1_53D4,
    fn_1_5B08,
    fn_1_709C,
    fn_1_766C,
    fn_1_7FB4,
    fn_1_81F8,
    fn_1_8388
};
/* 0x30C */ u32 lbl_1_data_30C[7] = { DATA_w01s, DATA_w02s, DATA_w03s, DATA_w04s, DATA_w05s, DATA_w06s, DATA_w07s };

/* 479 insns */
/* twin: mdparty ObjectSetup. mdstory clears FLAG_BOARD_TUTORIAL and the party flag, only closes the
 * story board dirs (lbl_1_data_30C) */
void ObjectSetup(void)
{
    int i;
    sys = &sysWork;
    sysP = sys;
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowTime = 0;
    sys->flowMode = MDSTORY_FLOW_INIT;
    sys->ovlCallMode = MD_OVLCALL_GOTO;
    sys->nextDll = DLL_selmenuDLL;
    sys->exitF = FALSE;
    sys->skipWipeF = FALSE;
    _ClearFlag(FLAG_BOARD_TUTORIAL);
    GWPartyFSet(FALSE);
    for(i=0; i<7; i++) {
        HuDataDirClose(lbl_1_data_30C[i]);
    }
    sys->objman = omInitObjMan(512, 8192);
    sys->ovlHis = omOvlHisGet(0);
    sys->evtNo = sys->ovlHis->evtno;
    omGameSysInit(sys->objman);
    sys->obj[MDSTORY_OBJ_DEBUGFONT] = omAddObj(sys->objman, 100, 0, 0, MdObjDebugFontCreate);
    sys->obj[MDSTORY_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDSTORY_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDSTORY_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDSTORY_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDSTORY_OBJ_PAD] = omAddObj(sys->objman, 101, 0, 0, MdObjPadMain);
    sys->obj[MDSTORY_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDSTORY_OBJ_PAD]->data) {
        OSReport("sys->obj[MDSTORY_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDSTORY_OBJ_PAD]->data;
    sys->obj[MDSTORY_OBJ_CAMERA] = omAddObj(sys->objman, 102, 0, 0, MdObjCameraCreate);
    sys->obj[MDSTORY_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDSTORY_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDSTORY_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDSTORY_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDSTORY_OBJ_LIGHT] = omAddObj(sys->objman, 103, 0, 0, MdObjLightCreate);
    sys->obj[MDSTORY_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDSTORY_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDSTORY_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDSTORY_OBJ_LIGHT]->data;
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
    sys->star = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSTORY_STAR), HU_MEMNUM_OVL);
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

/* 61 insns */
/* twin: mdparty MdMain */
void MdMain(void)
{
    if(sys->evtNo == 1) {
        omOvlReturn(1);
        HuPrcEnd();
        while(1) {
            HuPrcVSleep();
        }
    }
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

/* 197 insns */
/* twin: mdparty LoadProc. loadState here: 0 idle, 1 board dir -> ARAM, 2 DATA_storymode, 3 wait for
 * loadProcReady, 4 read the player's character and characters 10-12 (charDataDirTbl[charNo][4]) and
 * CharMotionInit them, 5 done (not mdparty's MD_LOAD_STATE_*). It never reads sys->loadDir. */
static void LoadProc(void)
{
    int i;
    OSTick tick;
    s16 charNo;

    while(1) {
        switch(sys->loadState) {
            case 0:
                break;

            case 1: /* board dir -> ARAM */
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
                sys->loadState = 2;
                break;

            case 2: /* DATA_storymode */
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(DATA_storymode);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadProcReady = FALSE;
                sys->loadState = 3;
                break;

            case 3: /* wait for the flow's loadProcReady */
                if(sys->loadProcReady == TRUE) {
                    sys->loadState = 4;
                }
                break;

            case 4: /* the player's character and characters 10-12 */
                for(i=0; i<4; i++) {
                    if(i == 0) {
                        charNo = GwPlayerConf[0].charNo;
                    } else {
                        charNo = i+9;
                    }
                    tick = OSGetTick();
                    sys->loadAsyncStat = HuDataDirReadAsync(charDataDirTbl[charNo][4]);
                    while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                        HuPrcVSleep();
                    }
                    OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                    OSReport("Finished!\n");
                    CharMotionInit(charNo);
                }
                sys->loadState = 5;
                break;

            case 5:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 0x47C */ float lbl_1_data_47C[8] = { 0.0f, 16.0f, 64.0f, 32.0f, -65.0f, 220.0f, 292.0f, 1000.0f };

/* 705 insns */
/* twin: mdparty StarUpdate (mode values MDPARTY_STAR_*). lbl_1_data_47C = curveData; lbl_1_bss_100 = pos2D,
 * lbl_1_bss_E8 = pos3D, E4 lerpTime, E0 lerpOfsTime, DC curveTime, D8 lerpT, D4 lerpOfsT, D0 curveT.
 * mdstory has no SNAP_LEFT: 10/11/12 are CENTER_START/CENTER/CENTER_END. MOVE_LEFT targets 2D (220, 292, 1000)
 * and passes +lerpOfsT to MdMathLerpOfs (CENTER keeps the twin's -1.0f*lerpOfsT). */
void fn_1_C24(void)
{
    MDSTORY_STAR *star; //r31
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
    star->mode = 0;
    star->motNext = 1;

    posP->x = 0;
    posP->y = 0;
    posP->z = 1800;
    fn_1_8B94(MDMODEL_STAR, MDCAMERA_FG);
    while(1) {
        model = sys->model;
        camera = sys->camera;
        mess = sys->mess;
        star = sys->star;
        posP = model->posP[MDMODEL_STAR];
        rotP = model->rotP[MDMODEL_STAR];
        scaleP = model->scaleP[MDMODEL_STAR];

        switch(star->mode) {
            case 0:
                break;

            case 1:
                lbl_1_bss_E4 = 0;
                lbl_1_bss_E0 = 0;
                lbl_1_bss_DC = 0;
                lbl_1_bss_D8 = 0;
                lbl_1_bss_D4 = 0;
                lbl_1_bss_D0 = 0;
                MdMathCurveInit(5, sys->curveTime, lbl_1_data_47C, sys->curveSlope);
                star->mode = 2;
                break;

            case 2:
                MdMathOscillate(MDMATH_OSC_90_REV, &lbl_1_bss_E4, &lbl_1_bss_D8, 60);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_E0, &lbl_1_bss_D4, 60);
                MdMathOscillate(MDMATH_OSC_0, &lbl_1_bss_DC, &lbl_1_bss_D0, 60);
                MdMathLerp(&posP->x, 0, 45, lbl_1_bss_D4);
                MdMathCurveGet(&posP->y, 5, sys->curveTime, lbl_1_data_47C, sys->curveSlope, lbl_1_bss_D0);
                MdMathLerp(&posP->z, 1800, 1300, lbl_1_bss_D8);
                MdMathLerp(&rotP->y, 0, 360, lbl_1_bss_D8);
                if(lbl_1_bss_E4 >= 1) {
                    star->mode = 3;
                }
                break;

            case 3:
                break;

            case 4:
                lbl_1_bss_E4 = 0;
                lbl_1_bss_E0 = 0;
                lbl_1_bss_D8 = 0;
                lbl_1_bss_D4 = 0;
                lbl_1_bss_100[0].x = 64;
                lbl_1_bss_100[0].y = 320;
                lbl_1_bss_100[0].z = 1000;
                lbl_1_bss_100[1].x = 288;
                lbl_1_bss_100[1].y = 240;
                lbl_1_bss_100[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_100[i], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_E8[i]);
                }
                star->mode = 5;
                break;

            case 5:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_E4, &lbl_1_bss_D8, 30);
                MdMathLerp(&posP->x, lbl_1_bss_E8[0].x, lbl_1_bss_E8[1].x, lbl_1_bss_D8);
                MdMathLerp(&posP->y, lbl_1_bss_E8[0].y, lbl_1_bss_E8[1].y, lbl_1_bss_D8);
                MdMathLerp(&posP->z, lbl_1_bss_E8[0].z, lbl_1_bss_E8[1].z, lbl_1_bss_D8);
                if(lbl_1_bss_E4 >= 1) {
                    star->mode = 6;
                }
                break;

            case 6:
                break;

            case 7:
                lbl_1_bss_E4 = 0;
                lbl_1_bss_E0 = 0;
                lbl_1_bss_DC = 0;
                lbl_1_bss_D8 = 0;
                lbl_1_bss_D4 = 0;
                lbl_1_bss_D0 = 0;
                lbl_1_bss_E8[0].x = 0;
                lbl_1_bss_E8[0].y = -65;
                lbl_1_bss_E8[0].z = 1300;
                lbl_1_bss_100[1].x = 220;
                lbl_1_bss_100[1].y = 292;
                lbl_1_bss_100[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_100[1], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_E8[1]);
                star->mode = 8;
                break;

            case 8:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_E4, &lbl_1_bss_D8, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_E0, &lbl_1_bss_D4, 30);
                MdMathLerp(&posP->x, lbl_1_bss_E8[0].x, lbl_1_bss_E8[1].x, lbl_1_bss_D8);
                MdMathLerp(&posP->y, lbl_1_bss_E8[0].y, lbl_1_bss_E8[1].y, lbl_1_bss_D8);
                MdMathLerpOfs(&posP->z, lbl_1_bss_E8[0].z, lbl_1_bss_E8[1].z, lbl_1_bss_D8, lbl_1_bss_D4);
                if(lbl_1_bss_E4 >= 1) {
                    star->mode = 9;
                }
                fn_1_8B94(MDMODEL_STAR, MDCAMERA_FG);
                break;

            case 9:
                break;

            case 10:
                lbl_1_bss_E4 = 0;
                lbl_1_bss_E0 = 0;
                lbl_1_bss_DC = 0;
                lbl_1_bss_D8 = 0;
                lbl_1_bss_D4 = 0;
                lbl_1_bss_D0 = 0;
                lbl_1_bss_E8[0].x = 0;
                lbl_1_bss_E8[0].y = -65;
                lbl_1_bss_E8[0].z = 1300;
                lbl_1_bss_100[1].x = 220;
                lbl_1_bss_100[1].y = 292;
                lbl_1_bss_100[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_100[1], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_E8[1]);
                star->mode = 11;
                break;

            case 11:
                MdMathOscillate(MDMATH_OSC_90_REV, &lbl_1_bss_E4, &lbl_1_bss_D8, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_E0, &lbl_1_bss_D4, 30);
                MdMathLerp(&posP->x, lbl_1_bss_E8[1].x, lbl_1_bss_E8[0].x, lbl_1_bss_D8);
                MdMathLerp(&posP->y, lbl_1_bss_E8[1].y, lbl_1_bss_E8[0].y, lbl_1_bss_D8);
                MdMathLerpOfs(&posP->z, lbl_1_bss_E8[1].z, lbl_1_bss_E8[0].z, lbl_1_bss_D8, -1.0f*lbl_1_bss_D4);
                if(lbl_1_bss_E4 >= 1) {
                    star->mode = 12;
                }
                fn_1_8B94(MDMODEL_STAR, MDCAMERA_FG);
                break;

            case 12:
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
        HuPrcVSleep();
    }
}
#ifdef __MWERKS__
#endif

/* 198 insns */
/* twin: mdparty PlayerSprUpdate (MDPARTY_PLAYERSPR_* modes), one player and no COM-difficulty sprite */
void fn_1_1728(void)
{
    MDSTORY_PLAYERSPR *playerSpr; //r31
    HuVec2f *playerNoScale; //r30
    int i; //r29
    MDSPRITE_WORK *sprite; //r28
    HUSPRGRPID playerNoGrpId; //r27
    MDCAMERA_WORK *camera; //r26
    MDMODEL_WORK *model; //r25

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    for(playerSpr=&sys->playerSpr[0], i=0; i<1; i++, playerSpr++) {
        playerSpr->mode = 0;
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
        HuSprGrpPosSet(playerNoGrpId, 0, 0);
        for(playerSpr=&sys->playerSpr[0], i=0; i<1; i++, playerSpr++) {
            playerNoScale = MdSpriteScaleGet(sprite, MDSPR_GRP_PLAYERNO, i);
            switch(playerSpr->mode) {
                case 0:
                    break;

                case 1:
                    HuSprDispOn(playerNoGrpId, i);
                    playerNoScale->x = 0;
                    playerNoScale->y = 0;
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
                    if(playerSpr->time >= 1) {
                        HuSprDispOff(playerNoGrpId, i);
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

/* 255 insns */
/* twin: mdparty ChrUpdate (MDPARTY_CHR_* modes), seven characters; lbl_1_data_180 = CharPos, lbl_1_data_228 = CharRot */
void fn_1_1A40(void)
{
    MDSTORY_CHR *chr; //r31
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

    for(chr=&sys->chr[0], i=0; i<7; i++, chr++) {
        chr->mode = 0;
    }
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        for(chr=&sys->chr[0], i=0; i<7; i++, chr++) {
            if(i != 0 && i != 1 && i != 2 && i != 5) {
                posP = model->posP[i+MDMODEL_MARIO];
                rotP = model->rotP[i+MDMODEL_MARIO];
                scaleP = model->scaleP[i+MDMODEL_MARIO];
                switch(chr->mode) {
                    case 0:
                        break;

                    case 1:
                        *posP = lbl_1_data_180[i][0];
                        *rotP = lbl_1_data_228[i][0];
                        chr->mode = 0;
                        break;

                    case 2:
                    case 3:
                        chr->origPos = *posP;
                        chr->origRot = *rotP;
                        if(chr->mode == 2) {
                            chr->pos = lbl_1_data_180[i][1];
                            chr->rot = lbl_1_data_228[i][1];
                        } else if(chr->mode == 3) {
                            chr->pos = lbl_1_data_180[i][0];
                            chr->rot = lbl_1_data_228[i][0];
                        }
                        chr->time = 0;
                        chr->ofsTime = 0;
                        chr->t = 0;
                        chr->ofsT = 0;
                        if(chr->mode == 2) {
                            chr->mode = 4;
                        } else if(chr->mode == 3) {
                            chr->mode = 5;
                        }
                        break;

                    case 4:
                    case 5:
                        if(chr->mode == 4) {
                            MdMathOscillate(MDMATH_OSC_0, &chr->time, &chr->t, 15);
                        } else if(chr->mode == 5) {
                            MdMathOscillate(MDMATH_OSC_0, &chr->time, &chr->t, 15);
                        }
                        MdMathLerp(&posP->x, chr->origPos.x, chr->pos.x, chr->t);
                        MdMathLerp(&posP->y, chr->origPos.y, chr->pos.y, chr->t);
                        MdMathLerp(&posP->z, chr->origPos.z, chr->pos.z, chr->t);
                        MdMathLerp(&rotP->x, chr->origRot.x, chr->rot.x, chr->t);
                        MdMathLerp(&rotP->y, chr->origRot.y, chr->rot.y, chr->t);
                        MdMathLerp(&rotP->z, chr->origRot.z, chr->rot.z, chr->t);
                        if(chr->time >= 1) {
                            chr->mode = 0;
                        }
                        break;
                }
            }
        }
        HuPrcVSleep();
    }
}

/* 6 insns */
/* twin: mdparty RingUpdate */
void fn_1_1E3C(void)
{
    while(1) {
        MdRingMain();
        HuPrcVSleep();
    }
}

/* 17 insns */
/* twin: mdparty MainWinUpdate */
void fn_1_1E54(void)
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
/* twin: mdparty MainWinUpdate (help window) */
void fn_1_1E98(void)
{
    MDMESS_WORK *mess;

    mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_HELP);
        HuPrcVSleep();
    }
}

/* 134 insns */
/* twin: mdparty MdInit (no TextWin process; loadDir DATA_selmenu) */
void MdInit(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdRingCreate();
    MdModelCreate(sys->model, sys->camera);
    MdToueiTexBufInit();
    HuPrcVSleep();
    HuDataDirClose(DATA_mdstory);
    HuPrcVSleep();
    MdToueiMdlInit();
    sys->starProc = HuPrcChildCreate(fn_1_C24, 107, 12288, 0, sys->objman);
    sys->playerSprProc = HuPrcChildCreate(fn_1_1728, 108, 12288, 0, sys->objman);
    sys->chrProc = HuPrcChildCreate(fn_1_1A40, 109, 12288, 0, sys->objman);
    sys->mainWinProc = HuPrcChildCreate(fn_1_1E54, 110, 4096, 0, sys->objman);
    sys->textWinProc = HuPrcChildCreate(fn_1_1E98, 111, 4096, 0, sys->objman);
    sys->loadState = 0;
    sys->loadAsyncStat = 0;
    sys->loadProcReady = FALSE;
    sys->loadDir = DATA_selmenu;
    sys->loadProc = HuPrcChildCreate(LoadProc, 106, 12288, 0, sys->objman);
    HuPrcVSleep();
}

/* 68 insns */
/* twin: mdparty MdClose */
void MdClose(void)
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

/* 190 insns */
/* twin: mdparty MdPartyFlowInit (one ring, seven characters, no map/VS/bonus models) */
void fn_1_2204(void)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    MDSPRITE_WORK *sprite; //r29
    MDSTORY_CHR *chr; //r28

    MDCAMERA_WORK *camera; //sp+0xC
    MDMESS_WORK *mess; //sp+0x8

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    chr = &sys->chr[0];
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_PLAYERNO, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NAME, FALSE);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAR]);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_STAGE_CHR]);
    for(i=0; i<7; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_MARIO]);
    }
    for(i=0; i<7; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_CHR_00]);
    }
    for(i=0; i<5; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_PACK_00]);
    }
    Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_LV]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_FINGER_1P]);
    Hu3DModelDispOff(model->mdlId[MDMODEL_RING_1P]);
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    CharMotionVoiceOnSet(0, 47, 0);
    CharMotionVoiceOnSet(1, 6, 0);
    CharMotionVoiceOnSet(2, 6, 0);
    CharMotionVoiceOnSet(3, 6, 0);
    CharMotionVoiceOnSet(4, 6, 0);
    CharMotionVoiceOnSet(5, 6, 0);
    CharMotionVoiceOnSet(6, 6, 0);
    for(i=0; i<1; i++) {
        MdRingDispSet(i, FALSE);
    }
    sys->ringProc = HuPrcChildCreate(fn_1_1E3C, 104, 12288, 0, sys->objman);
    for(i=0; i<7; i++) {
        chr[i].mode = 1; /* mdparty MDPARTY_CHR_INIT */
    }
    HuPrcSleep(2);
    MdProcCall(MDSTORY_PROC_RESET, 0);
    HuPrcVSleep();
    sys->loadState = 1;
    sys->subMode = 0;
    sys->flowMode = MDSTORY_FLOW_UNK1;
}

/* 547 insns */
/* twin: mdparty MdPartyFlowStart (repeatCont/quit gotos are the twin's). Opens the windows, offers to
 * continue a saved story (GwCommon.storyContinue): continue -> SLBoardLoadStory and omOvlCall storymodedll;
 * quit -> return to mdseldll. subMode 2 asks whether to hear the explanation; 3 sends the star back. */
void fn_1_24FC(void)
{
    MDMESS_WORK *mess; //r31
    int choice; //r30
    MDSTORY_STAR *star; //r29

    MDMODEL_WORK *model; //sp+0x10
    MDSTORY_PLAYERSPR *playerSpr; //sp+0xC
    MDSTORY_CHR *chr; //sp+0x8

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDSTORY_PROC_RESET, 0);
            sys->subMode = 1;
            break;

        case 1:
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            fn_1_9384(0);
            WipeWait();
            MdProcWait(MDSTORY_PROC_NAME, 0);
            MdProcCall(MDSTORY_PROC_RESET, 0);
            MdProcWait(MDSTORY_PROC_WIN, 0);
            MdProcCall(MDSTORY_PROC_RESET, 0);
            /* retail opens MDMESS_WIN_MAIN twice; the second call's position and size win */
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 32, 372, 512, 64, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 56, 376, 464, 64, 0);
            MdMessWinOpen(mess, MDMESS_WIN_HELP, MDMESS_WIN_NOSPEAKER, 0, 0, 1, 64, 340, 448, 32, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_MAIN, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 0), MDMESS_WIN_LIST_END);
            fn_1_9384(8);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            repeatCont:
            if(GwCommon.storyContinue == TRUE) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 1), MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1) {
                    quit:
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 3), MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                    if(choice == -1) {
                        goto repeatCont;
                    }
                    if(choice == 1) {
                        goto repeatCont;
                    }
                    if(choice == 0) {
                        MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                        MdProcWait(MDSTORY_PROC_WIN, 1);
                        MdProcCall(MDSTORY_PROC_RESET, 0);
                        WipeColorSet(255, 255, 255);
                        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                        fn_1_9384(1);
                        WipeWait();
                        while(sys->loadState != 3) {
                            HuPrcVSleep();
                        }
                        omOvlHisChg(0, sys->ovlHis->ovl, 0, sys->ovlHis->stat);
                        sys->ovlCallMode = MD_OVLCALL_RETURN;
                        sys->nextDll = DLL_mdseldll;
                        sys->skipWipeF = TRUE;
                        sys->exitF = TRUE;
                    }
                } else if(choice == 0) {
                    SLBoardLoadStory();
                    sys->loadProcReady = TRUE;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdProcWait(MDSTORY_PROC_NAME, 1);
                    MdProcCall(MDSTORY_PROC_RESET, 0);
                    MdProcWait(MDSTORY_PROC_WIN, 1);
                    MdProcCall(MDSTORY_PROC_RESET, 0);
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_9384(1);
                    WipeWait();
                    while(sys->loadState != 5) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                    sys->nextDll = DLL_storymodedll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                } else if(choice == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 2), MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                }
            }
            sys->subMode = 2;
            break;

        case 2:
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 4), MDMESS_WIN_LIST_END);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
            if(choice == -1) {
                sys->subMode = 1;
                goto quit;
            } else if(choice == 0) {
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 26), MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                sys->subMode = 3;
            } else if(choice == 1) {
                sys->subMode = 3;
            }
            break;

        case 3:
            MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
            MdProcWait(MDSTORY_PROC_NAME, 1);
            MdProcCall(MDSTORY_PROC_RESET, 0);
            star->mode = 1;
            star->motNext = 3;
            while(star->mode != 3) {
                HuPrcVSleep();
            }
            sys->subMode = 0;
            sys->flowMode = MDSTORY_FLOW_UNK2;
            break;
    }
}

/* 428 insns */
/* character select (twin for idioms: mdparty MdPartyFlowChrSel). unk23/unk27/unk2B are per-player
 * arrays in SYS; [0] is the player. fn_1_8948 is the cursor update (TRUE when the cursor moved). */
void fn_1_2D88(void)
{
    int i; //r31
    MDMESS_WORK *mess; //r30
    int ret; //r28
    MDMODEL_WORK *model; //r29
    MDSTORY_STAR *star; //r27
    MDSTORY_PLAYERSPR *playerSpr; //r26
    MDSTORY_CHR *chr; //r25

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDSTORY_PROC_RESET, 0);
            for(i=0; i<4; i++) {
                if(sys->padNoEnable[i] == -1) {
                    sys->chrSel[i] = 0;
                } else {
                    sys->chrSel[i] = sys->padNoEnable[i];
                }
                sys->chrSelEnd[i] = 0;
            }
            sys->subMode = 1;
            break;

        case 1:
            ret = MdProcCall(MDSTORY_PROC_CHR, 0);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 5), MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                star->motNext = 2;
                sys->subMode = 2;
            }
            break;

        case 2:
            ret = MdProcCall(MDSTORY_PROC_FINGER, 0);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 3:
            ret = fn_1_8948(0);
            if(ret == TRUE) {
                fn_1_9384(2);
                fn_1_87F4();
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_9384(4);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 3), MDMESS_WIN_LIST_END);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->subMode = 4;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_9384(3);
                fn_1_9384(sys->chrSel[0]+10);
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->chrSelEnd[0] = 1;
                Hu3DModelDispOff(model->mdlId[MDMODEL_FINGER_1P]);
                playerSpr->mode = 1;
                Hu3DMotionShiftSet(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], model->motId[MDMODEL_MOT_CHR_START+(sys->chrSel[0]*3)+1], 0, 8, HU3D_MOTATTR_NONE);
                chr[sys->chrSel[0]].mode = 2;
                MdRingModeSet(0, 1);
                MdRingOfsSet(0, 0, 0, 0);
                MdRingMdlSet(0, sys->chrSel[0]+MDMODEL_CAP_CHR_00);
                MdRingScaleSet(0, 0.92f);
                MdProcWait(MDSTORY_PROC_CHR, 2);
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDSTORY_FLOW_UNK3;
            }
            break;

        case 4:
            ret = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(ret == TRUE) {
                ret = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(ret == -1 || ret == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 5), MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                    sys->subMode = 3;
                } else if(ret == 0) {
                    star->motNext = 2;
                    Hu3DModelDispOff(model->mdlId[MDMODEL_FINGER_1P]);
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    MdProcWait(MDSTORY_PROC_WIN, 1);
                    MdProcCall(MDSTORY_PROC_RESET, 0);
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_9384(1);
                    WipeWait();
                    while(sys->loadState != 3) {
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
    }
}
#ifdef __MWERKS__
#endif

/* 509 insns */
/* difficulty select (twin for idioms: mdparty MdPartyFlowBonusSel/TurnSel). sys->unk2F is the level
 * 0-3 shown by Hu3DAnmNoSet on animId[1]; level 2 is skipped unless GwCommon.veryHardUnlock. */
void fn_1_3438(void)
{
    MDMODEL_WORK *model; //r31
    MDMESS_WORK *mess; //r30
    MDSTORY_STAR *star; //r29
    MDSTORY_PLAYERSPR *playerSpr; //r27
    MDSTORY_CHR *chr; //r26
    int ret; //r28

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDSTORY_PROC_RESET, 0);
            sys->unk2F = 0;
            Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_UNK1], sys->unk2F);
            sys->subMode = 1;
            break;

        case 1:
            ret = MdProcCall(MDSTORY_PROC_CAP_TURN, 0);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 7), MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            MdProcWait(MDSTORY_PROC_UNK2, 0);
            MdProcCall(MDSTORY_PROC_RESET, 0);
            sys->subMode = 3;
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk2F == -1) {
                        sys->unk2F = 3;
                    }
                    if(GwCommon.veryHardUnlock == FALSE && sys->unk2F == 2) {
                        sys->unk2F = 1;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk2F = ++sys->unk2F % 4;
                    if(GwCommon.veryHardUnlock == FALSE && sys->unk2F == 2) {
                        sys->unk2F = 3;
                    }
                    sys->cursorDir = 1;
                }
                fn_1_9384(2);
                Hu3DAnmNoSet(model->animId[MDMODEL_ANIM_UNK1], sys->unk2F);
                MdProcWait(MDSTORY_PROC_CAP_TURN, 1);
                MdProcCall(MDSTORY_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_9384(4);
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->subMode = 5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_9384(3);
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->subMode = 8;
            }
            break;

        case 4:
            ret = MdProcCall(MDSTORY_PROC_CAP_TURN, 1);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 5:
            ret = MdProcCall(MDSTORY_PROC_UNK2, 1);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 6;
            }
            break;

        case 6:
            ret = MdProcCall(MDSTORY_PROC_CAP_TURN, 2);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 7;
            }
            break;

        case 7:
            ret = MdProcCall(MDSTORY_PROC_CHR, 3);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->chrSelEnd[0] = 0;
                playerSpr->mode = 4;
                Hu3DMotionShiftSet(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], model->motId[MDMODEL_MOT_CHR_START+(sys->chrSel[0]*3)], 0, 8, HU3D_MOTATTR_NONE);
                chr[sys->chrSel[0]].mode = 3;
                MdRingModeSet(0, 4);
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 5), MDMESS_WIN_LIST_END);
                MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                sys->subMode = 2;
                sys->flowMode = MDSTORY_FLOW_UNK2;
            }
            break;

        case 8:
            ret = MdProcCall(MDSTORY_PROC_UNK2, 1);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 9;
            }
            break;

        case 9:
            ret = MdProcCall(MDSTORY_PROC_CAP_TURN, 3);
            if(ret == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 0;
                sys->flowMode = MDSTORY_FLOW_UNK4;
            }
            break;
    }
}
#ifdef __MWERKS__
#endif

/* 686 insns */
void fn_1_3C2C(void)
{
    MDMESS_WORK *mess;
    MDSTORY_STAR *star;
    int result;
    MDMODEL_WORK *model;
    int i;
    MDSTORY_PLAYERSPR *playerSpr;
    MDSTORY_CHR *chr;

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    playerSpr = &sys->playerSpr[0];
    chr = &sys->chr[0];

    switch(sys->subMode) {
        case 0:
            (void)MdProcCall(MDSTORY_PROC_RESET, 0);
            sys->unk30 = 0;
            sys->subMode = 1;
            break;

        case 1:
            result = MdProcCall(MDSTORY_PROC_CAP_PACK, 0);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 2;
            }
            break;

        case 2:
            star->motNext = 2;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 0x15)+sys->unk30, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            MdProcWait(MDSTORY_PROC_UNK2, 0);
            MdProcCall(MDSTORY_PROC_RESET, 0);
            sys->subMode = 3;
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    if(--sys->unk30 == -1) {
                        sys->unk30 = 4;
                    }
                    sys->cursorDir = 0;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    sys->unk30 = ++sys->unk30 % 5;
                    sys->cursorDir = 1;
                }
                fn_1_9384(2);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 0x15)+sys->unk30, MDMESS_WIN_LIST_END);
                for(i=0; i<5; i++) {
                    if(i == sys->unk30) {
                        Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_PACK_00+i]);
                    } else {
                        Hu3DModelDispOff(model->mdlId[MDMODEL_CAP_PACK_00+i]);
                    }
                }
                sys->subMode = 4;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_9384(4);
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->subMode = 5;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_9384(3);
                star->motNext = 3;
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                sys->subMode = 8;
            }
            break;

        case 4:
            result = MdProcCall(MDSTORY_PROC_CAP_PACK, 1);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 3;
            }
            break;

        case 5:
            result = MdProcCall(MDSTORY_PROC_UNK2, 1);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 6;
            }
            break;

        case 6:
            result = MdProcCall(MDSTORY_PROC_CAP_PACK, 2);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 7;
            }
            break;

        case 7:
            result = MdProcCall(MDSTORY_PROC_CAP_TURN, 4);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 2;
                sys->flowMode = MDSTORY_FLOW_UNK3;
            }
            break;

        case 8:
            result = MdProcCall(MDSTORY_PROC_UNK2, 1);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                sys->subMode = 9;
            }
            break;

        case 9:
            result = MdProcCall(MDSTORY_PROC_CAP_PACK, 3);
            if(result == TRUE) {
                MdProcCall(MDSTORY_PROC_RESET, 0);
                star->motNext = 2;
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 0x8), MDMESS_WIN_LIST_END);
                fn_1_9384(9);
                sys->subMode = 10;
            }
            break;

        case 10:
            result = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(result == TRUE) {
                result = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(result == -1 || result == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESSNUM(MESS_STORYMODE_SYS, 0x9), MDMESS_WIN_LIST_END);
                    sys->subMode = 11;
                } else if(result == 0) {
                    MdProcCall(MDSTORY_PROC_RESET, 0);
                    fn_1_8C84();
                    sys->loadProcReady = 1;
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESSNUM(MESS_STORYMODE_SYS, 0xA), MDMESS_WIN_LIST_END);
                    while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                        HuPrcVSleep();
                    }
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                    fn_1_9384(1);
                    fn_1_9384(7);
                    while(WipeCheckEnd()) {
                        MdProcCall(MDSTORY_PROC_CHR, 4);
                        HuPrcVSleep();
                    }
                    while(sys->loadState != MD_LOAD_STATE_DONE) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                    sys->nextDll = DLL_storymodedll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            }
            break;

        case 11:
            result = MdMessWinCheck(mess, MDMESS_WIN_MAIN);
            if(result == TRUE) {
                result = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(result == -1 || result == 1) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    while(MdProcCall(MDSTORY_PROC_CAP_PACK, 4) == 0) {
                        HuPrcVSleep();
                    }
                    (void)MdProcCall(MDSTORY_PROC_RESET, 0);
                    sys->subMode = 2;
                } else if(result == 0) {
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    sys->chrSelEnd[0] = 0;
                    playerSpr->mode = 4;
                    Hu3DMotionShiftSet(model->mdlId[MDMODEL_MARIO+sys->chrSel[0]], model->motId[MDMODEL_MOT_CHR_START+(sys->chrSel[0]*3)], 0, 8, HU3D_MOTATTR_NONE);
                    chr[sys->chrSel[0]].mode = 3;
                    MdRingModeSet(0, 4);
                    Hu3DModelDispOff(model->mdlId[MDMODEL_RING_1P]);
                    MdProcWait(MDSTORY_PROC_UNK7, 0);
                    MdProcCall(MDSTORY_PROC_RESET, 0);
                    sys->subMode = 1;
                    sys->flowMode = MDSTORY_FLOW_UNK2;
                }
            }
            break;
    }
}

/* 130 insns */
BOOL fn_1_46E4(int param)
{
    sys->dirtyF = FALSE;
    sys->unk298 = FALSE;
    sys->unk29C = FALSE;
    sys->winInitF = FALSE;
    sys->nameInitF = FALSE;
    sys->unk2A8 = FALSE;
    sys->procTime = 0.0f;
    sys->procOfsTime = 0.0f;
    sys->cameraTime = 0.0f;
    sys->cameraTotalTime = 0.0f;
    sys->unk2C4 = 0.0f;
    sys->sprTime = 0.0f;
    sys->nameTime = 0.0f;
    sys->procT = 0.0f;
    sys->procOfsT = 0.0f;
    sys->cameraT = 0.0f;
    sys->cameraTotalT = 0.0f;
    sys->unk2E0 = 0.0f;
    sys->sprT = 0.0f;
    sys->nameT = 0.0f;
    return FALSE;
}

/* 0x544 */ MDSTORY_LERP_DATA lbl_1_data_544[1] = { /* mdparty ProcCamera lerpData */
    { { -90.0f, -12.0f, 2500.0f }, { 0.0f, 400.0f, 1750.0f }, { -90.0f, 0.0f, 2500.0f }, { 0.0f, 200.0f, -250.0f }, 2, 30.0f }
};

/* 107 insns */
BOOL fn_1_48EC(int param)
{
    MDSTORY_LERP_DATA *lerpP;
    MDCAMERA_WORK *cameraWork;
    MDCAMERA *camera;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[MDCAMERA_MAIN];
    lerpP = &lbl_1_data_544[param];
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

/* 591 insns */
BOOL fn_1_4A98(int param)
{
    HuVec2f *sprPos;
    MDSPRITE_WORK *sprite;
    HUSPRGRPID grpId;
    HuVec2f *sprScale;
    MDCAMERA_WORK *camera;

    HuVecF pos2D;
    HuVecF pos3D;

    camera = sys->camera;
    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_UDLR];
    if(!sys->unk29C) {
        pos3D.x = 0;
        pos3D.y = 145;
        pos3D.z = 400;
        Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
        lbl_1_bss_A0[0].x = -64.0f;
        lbl_1_bss_A0[0].y = pos2D.y;
        lbl_1_bss_A0[0].z = 0;
        lbl_1_bss_A0[1].x = pos2D.x-80;
        lbl_1_bss_A0[1].y = pos2D.y;
        lbl_1_bss_A0[1].z = 0;
        lbl_1_bss_A0[2].x = 640.0f;
        lbl_1_bss_A0[2].y = pos2D.y;
        lbl_1_bss_A0[2].z = 0;
        lbl_1_bss_A0[3].x = pos2D.x+80;
        lbl_1_bss_A0[3].y = pos2D.y;
        lbl_1_bss_A0[3].z = 0;
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos->x = lbl_1_bss_A0[0].x;
            sprPos->y = lbl_1_bss_A0[0].y;
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprPos->x = lbl_1_bss_A0[2].x;
            sprPos->y = lbl_1_bss_A0[2].y;
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        } else if(param == 2) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
            sprPos->x = lbl_1_bss_A0[1].x;
            sprPos->y = lbl_1_bss_A0[1].y;
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), 0);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
            sprPos->x = lbl_1_bss_A0[3].x;
            sprPos->y = lbl_1_bss_A0[3].y;
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), 0);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        sys->unk29C = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2C4, &sys->unk2E0, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[0].x, lbl_1_bss_A0[1].x, sys->unk2E0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[2].x, lbl_1_bss_A0[3].x, sys->unk2E0);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk2C4, &sys->unk2E0, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[1].x, lbl_1_bss_A0[0].x, sys->unk2E0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[3].x, lbl_1_bss_A0[2].x, sys->unk2E0);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_180, &sys->unk2C4, &sys->unk2E0, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[1].x, lbl_1_bss_A0[1].x-24, sys->unk2E0);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->unk2E0);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->unk2E0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[1].x, lbl_1_bss_A0[1].x-24, sys->unk2E0);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->unk2E0);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->unk2E0);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), sys->unk2E0);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_180, &sys->unk2C4, &sys->unk2E0, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[3].x, 24+lbl_1_bss_A0[3].x, sys->unk2E0);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->unk2E0);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->unk2E0);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_A0[3].x, 24+lbl_1_bss_A0[3].x, sys->unk2E0);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->unk2E0);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->unk2E0);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), sys->unk2E0);
    }
    if(sys->unk2C4 >= 1) {
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
BOOL fn_1_53D4(int param)
{
    MDSPRITE_WORK *sprite;
    HuVec2f *bgScale;
    HuVec2f *topPos;
    HuVec2f *bottomPos;
    HuVec2f *topScale;
    HuVec2f *bottomScale;

    HuVec2f *bgPos;
    HUSPRGRPID grpId;

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_WIN];
    topPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_TOP));
    bottomPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_BOTTOM));
    bgPos = MdSpritePosGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_BG));
    topScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_TOP));
    bottomScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_FRAME_BOTTOM));
    bgScale = MdSpriteScaleGet(sprite, MDSPR_GRP_WIN, MDSPR_GRP_MEMBERNO(MDSPR_GRP_WIN, MDSPR_WIN_BG));
    if(!sys->winInitF) {
        lbl_1_bss_9C = 0;
        lbl_1_bss_98 = topPos->y;
        lbl_1_bss_94 = bottomPos->y;
        lbl_1_bss_90 = bgScale->y;
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
        if(lbl_1_bss_9C == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, 0, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, 0, 2, sys->sprT);
            MdMathLerp(&topScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bottomScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bgScale->x, 0, 1, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_9C = 1;
            }
        } else if(lbl_1_bss_9C == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, -2, -28, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 32, sys->sprT);
            MdMathLerp(&bgScale->y, 0, 8, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_9C = 2;
            }
        }
    } else if(param == TRUE) {
        if(lbl_1_bss_9C == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, lbl_1_bss_98, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, lbl_1_bss_94, 2, sys->sprT);
            MdMathLerp(&bgScale->y, lbl_1_bss_90, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_9C = 1;
            }
        } else if(lbl_1_bss_9C == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, -2, 0, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 0, sys->sprT);
            MdMathLerp(&topScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bottomScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bgScale->x, 1, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_9C = 2;
            }
        }
    }
    if(lbl_1_bss_9C == 2) {
        if(param == TRUE) {
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x57C */ float lbl_1_data_57C[3] = { 0.0f, 0.0f, -1000.0f };
/* 0x588 */ HuVecF lbl_1_data_588[7] = { { -330.0f, 400.0f, -600.0f }, { -110.0f, 400.0f, -600.0f }, { 110.0f, 400.0f, -600.0f }, { 330.0f, 400.0f, -600.0f }, { -220.0f, 130.0f, -600.0f }, { 0.0f, 130.0f, -600.0f }, { 220.0f, 130.0f, -600.0f } };
/* 0x5DC */ HuVecF lbl_1_data_5DC[4] = { { 120.0f, -160.0f, 750.0f }, { 120.0f, -160.0f, 750.0f }, { 120.0f, -160.0f, 750.0f }, { 120.0f, -160.0f, 750.0f } };

/* 1381 insns */
BOOL fn_1_5B08(int param)
{
    int i;
    MDMODEL_WORK *model;
    HuVecF *scaleP;
    HuVecF *posP;
    MDCAMERA_WORK *camera;
    HuVecF *rotP;
    MDSPRITE_WORK *sprite;
    MDSTORY_STAR *star;

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    star = sys->star;
    if(!sys->dirtyF) {
        if(param == 0) {
            for(i=0; i<7; i++) {
                posP = model->posP[i+MDMODEL_CAP_CHR_00];
                rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
                scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
                *posP = *(HuVecF *)lbl_1_data_57C;
                scaleP->x = 0;
                scaleP->y = 0;
                scaleP->z = 0;
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_CHR_00]);
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_MARIO]);
            }
            Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE_CHR]);
            Hu3DLayerHookSet(1+HU3D_LAYER_HOOK_POST, MdToueiLayerHook);
            fn_1_9384(6);
        } else if(param == 2) {
            star->mode = 7;
            fn_1_9384(6);
        } else if(param == 3) {
            star->mode = 10;
            fn_1_9384(6);
        } else if(param == 4) {
            lbl_1_bss_88[0] = ParticleDotCreate(sprite->animP[MDSPR_ANIM_UNK7], 4, camera->camera[MDCAMERA_MAIN].bit);
            lbl_1_bss_88[1] = ParticleGlowCreate(sprite->animP[MDSPR_ANIM_UNK8], 4, camera->camera[MDCAMERA_MAIN].bit);
            ParticleDotPosSet(lbl_1_bss_88[0], model->posP[sys->chrSel[0]+MDMODEL_CAP_CHR_00]);
            for(i=0; i<7; i++) {
                Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_CHR_00]);
                Hu3DModelDispOff(model->mdlId[i+MDMODEL_MARIO]);
            }
            Hu3DModelDispOff(model->mdlId[MDMODEL_STAGE_CHR]);
            Hu3DModelDispOff(model->mdlId[MDMODEL_RING_1P]);
            Hu3DModelDispOn(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO]);
            Hu3DLayerHookSet(1+HU3D_LAYER_HOOK_POST, NULL);
            Hu3DModelLayerSet(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], 1);
            Hu3DModelCameraSet(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], camera->camera[MDCAMERA_MAIN].bit);
            lbl_1_bss_70[1].x = 352;
            lbl_1_bss_70[1].y = 224;
            lbl_1_bss_70[1].z = 1500;
            Hu3D2Dto3D(&lbl_1_bss_70[1], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_58[1]);
            *model->posP[sys->chrSel[0]+MDMODEL_MARIO] = *model->posP[sys->chrSel[0]+MDMODEL_CAP_CHR_00];
            model->posP[sys->chrSel[0]+MDMODEL_MARIO]->y -= 200;
            lbl_1_bss_58[0] = *model->posP[sys->chrSel[0]+MDMODEL_MARIO];
            model->rotP[sys->chrSel[0]+MDMODEL_MARIO]->x = 0;
            model->rotP[sys->chrSel[0]+MDMODEL_MARIO]->y = 0;
            model->rotP[sys->chrSel[0]+MDMODEL_MARIO]->z = 0;
            model->scaleP[sys->chrSel[0]+MDMODEL_MARIO]->x = 2;
            model->scaleP[sys->chrSel[0]+MDMODEL_MARIO]->y = 2;
            model->scaleP[sys->chrSel[0]+MDMODEL_MARIO]->z = 2;
            HuSprDispOff(sprite->grpId[MDSPR_GRP_PLAYERNO], 0);
            Hu3DMotionSet(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], model->motId[(sys->chrSel[0]*3)+5]); /* MDMODEL_MOT_CHR_START+c*3+2 */
            Hu3DModelAttrReset(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(model->mdlId[sys->chrSel[0]+MDMODEL_MARIO], HU3D_MOTATTR_PAUSE);
            fn_1_9384(5);
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        for(i=0; i<7; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_57C[0], lbl_1_data_588[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_57C[1], lbl_1_data_588[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_57C[2], lbl_1_data_588[i].z, sys->procT);
            MdMathLerp(&scaleP->x, 0, 1, sys->procT);
            MdMathLerp(&scaleP->y, 0, 1, sys->procT);
            MdMathLerp(&scaleP->z, 0, 0.1f, sys->procT);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15);
        for(i=0; i<7; i++) {
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
        for(i=0; i<1; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_588[sys->chrSel[i]].x, lbl_1_data_5DC[i].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_588[sys->chrSel[i]].y, lbl_1_data_5DC[i].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_588[sys->chrSel[i]].z, lbl_1_data_5DC[i].z, sys->procOfsT);
        }
        for(i=0; i<7; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            if(i != sys->chrSel[0]) {
                MdMathLerp(&scaleP->x, 1, 0, sys->procT);
                MdMathLerp(&scaleP->y, 1, 0, sys->procT);
                MdMathLerp(&scaleP->z, 0.1f, 0, sys->procT);
            }
        }
        fn_1_87F4();
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 30);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 30);
        for(i=0; i<1; i++) {
            posP = model->posP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[sys->chrSel[i]+MDMODEL_CAP_CHR_00];
            MdMathLerp(&posP->x, lbl_1_data_5DC[i].x, lbl_1_data_588[sys->chrSel[i]].x, sys->procT);
            MdMathLerp(&posP->y, lbl_1_data_5DC[i].y, lbl_1_data_588[sys->chrSel[i]].y, sys->procT);
            MdMathLerp(&posP->z, lbl_1_data_588[sys->chrSel[i]].z, lbl_1_data_5DC[i].z, sys->procOfsT);
        }
        for(i=0; i<7; i++) {
            posP = model->posP[i+MDMODEL_CAP_CHR_00];
            rotP = model->rotP[i+MDMODEL_CAP_CHR_00];
            scaleP = model->scaleP[i+MDMODEL_CAP_CHR_00];
            if(i != sys->chrSel[0]) {
                MdMathLerp(&scaleP->x, 0, 1, sys->procT);
                MdMathLerp(&scaleP->y, 0, 1, sys->procT);
                MdMathLerp(&scaleP->z, 0, 0.1f, sys->procT);
            }
        }
        fn_1_87F4();
    } else if(param == 4) {
        posP = model->posP[sys->chrSel[0]+MDMODEL_MARIO];
        rotP = model->rotP[sys->chrSel[0]+MDMODEL_MARIO];
        scaleP = model->scaleP[sys->chrSel[0]+MDMODEL_MARIO];
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 60);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 60);
        MdMathOscillate(MDMATH_OSC_180, &sys->cameraTime, &sys->cameraT, 60);
        MdMathLerp(&posP->x, lbl_1_bss_58[0].x, lbl_1_bss_58[1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_58[0].y, lbl_1_bss_58[1].y, sys->cameraT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_58[0].z, lbl_1_bss_58[1].z, sys->procT, 0.2f*sys->procOfsT);
        ParticleGlowPosSet(lbl_1_bss_88[1], model->posP[sys->chrSel[0]+MDMODEL_MARIO]);
        (void)MdProcCall(MDSTORY_PROC_WIN, TRUE);
    }
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 372 insns */
BOOL fn_1_709C(int param)
{
    HuVecF *posP;
    MDMODEL_WORK *model;
    HuVecF *scaleP;

    MDCAMERA_WORK *camera;
    HuVecF *rotP;

    camera = sys->camera;
    model = sys->model;
    posP = model->posP[MDMODEL_CAP_LV];
    rotP = model->rotP[MDMODEL_CAP_LV];
    scaleP = model->scaleP[MDMODEL_CAP_LV];

    if(!sys->dirtyF) {
        if(param == 0) {
            posP->x = 0;
            posP->y = 145;
            posP->z = 400;

            scaleP->x = 0;
            scaleP->y = 0;
            scaleP->z = 0;
            Hu3DModelDispOn(model->mdlId[MDMODEL_CAP_LV]);
        } else if(param == 1) {
        } else if(param == 2) {
        } else if(param == 3) {
            lbl_1_bss_40[0] = *posP;
            lbl_1_bss_40[1].x = 525;
            lbl_1_bss_40[1].y = 365;
            lbl_1_bss_40[1].z = -50;
            fn_1_9384(6);
        } else if(param == 4) {
            fn_1_9384(6);
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 0, 1, sys->procT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdProcCall(MDSTORY_PROC_UNK2, sys->cursorDir+2);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 1, 0, sys->procT);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_40[0].x, lbl_1_bss_40[1].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_40[0].y, lbl_1_bss_40[1].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_40[0].z, lbl_1_bss_40[1].z, sys->procT, -1.0f*sys->procOfsT);
        MdMathLerpScale(scaleP, 1, 0.8f, sys->procT);
    } else if(param == 4) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP->x, lbl_1_bss_40[1].x, lbl_1_bss_40[0].x, sys->procT);
        MdMathLerp(&posP->y, lbl_1_bss_40[1].y, lbl_1_bss_40[0].y, sys->procT);
        MdMathLerpOfs(&posP->z, lbl_1_bss_40[1].z, lbl_1_bss_40[0].z, sys->procT, sys->procOfsT);
        MdMathLerpScale(scaleP, 0.8f, 1.0f, sys->procT);
    }
    fn_1_8B94(MDMODEL_CAP_LV, MDCAMERA_MAIN);
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 594 insns */
BOOL fn_1_766C(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *posP[5]; //sp+0x34
    HuVecF *rotP[5]; //sp+0x20
    HuVecF *scaleP[5]; //sp+0xC
    MDCAMERA_WORK *camera; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    for(i=0; i<5; i++) {
        posP[i] = model->posP[i+MDMODEL_CAP_PACK_00];
        rotP[i] = model->rotP[i+MDMODEL_CAP_PACK_00];
        scaleP[i] = model->scaleP[i+MDMODEL_CAP_PACK_00];
    }
    if(!sys->dirtyF) {
        if(param == 0) {
            for(i=0; i<5; i++) {
                posP[i]->x = 0;
                posP[i]->y = 145;
                posP[i]->z = 400;

                scaleP[i]->x = 0;
                scaleP[i]->y = 0;
                scaleP[i]->z = 0;
            }
            for(i=0; i<5; i++) {
                if(i == sys->unk30) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_PACK_00]);
                } else {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_PACK_00]);
                }
            }
        } else if(param != 1 && param != 2) {
            if(param == 3) {
                lbl_1_bss_28[0] = *posP[sys->unk30];
                lbl_1_bss_28[1].x = -525;
                lbl_1_bss_28[1].y = 365;
                lbl_1_bss_28[1].z = -50;
                fn_1_9384(MDSTORY_AUD_SE_MENU_MOVE);
            } else if(param == 4) {
                fn_1_9384(MDSTORY_AUD_SE_MENU_MOVE);
            }
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        for(i=0; i<5; i++) {
            MdMathLerpScale(scaleP[i], 0, 1, sys->procT);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdProcCall(MDSTORY_PROC_UNK2, sys->cursorDir+2);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        for(i=0; i<5; i++) {
            MdMathLerpScale(scaleP[i], 1, 0, sys->procT);
        }
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP[0]->x, lbl_1_bss_28[0].x, lbl_1_bss_28[1].x, sys->procT);
        MdMathLerp(&posP[0]->y, lbl_1_bss_28[0].y, lbl_1_bss_28[1].y, sys->procT);
        MdMathLerpOfs(&posP[0]->z, lbl_1_bss_28[0].z, lbl_1_bss_28[1].z, sys->procT, sys->procOfsT*-1);
        *posP[1] = *posP[0];
        *posP[2] = *posP[0];
        *posP[3] = *posP[0];
        *posP[4] = *posP[0];
        MdMathLerpScale(scaleP[0], 1.0f, 0.8f, sys->procT);
        *scaleP[1] = *scaleP[0];
        *scaleP[2] = *scaleP[0];
        *scaleP[3] = *scaleP[0];
        *scaleP[4] = *scaleP[0];
    } else if(param == 4) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 15.0f);
        MdMathLerp(&posP[0]->x, lbl_1_bss_28[1].x, lbl_1_bss_28[0].x, sys->procT);
        MdMathLerp(&posP[0]->y, lbl_1_bss_28[1].y, lbl_1_bss_28[0].y, sys->procT);
        MdMathLerpOfs(&posP[0]->z, lbl_1_bss_28[1].z, lbl_1_bss_28[0].z, sys->procT, sys->procOfsT*1);
        *posP[1] = *posP[0];
        *posP[2] = *posP[0];
        *posP[3] = *posP[0];
        *posP[4] = *posP[0];
        MdMathLerpScale(scaleP[0], 0.8f, 1.0f, sys->procT);
        *scaleP[1] = *scaleP[0];
        *scaleP[2] = *scaleP[0];
        *scaleP[3] = *scaleP[0];
        *scaleP[4] = *scaleP[0];
    }
    for(i=0; i<5; i++) {
        fn_1_8B94(i+MDMODEL_CAP_PACK_00, MDCAMERA_MAIN);
    }
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 145 insns */
BOOL fn_1_7FB4(int param)
{
    HuVecF *scaleP; //r31
    MDMODEL_WORK *model; //r30
    int i; //r29
    MDSTORY_STAR *star; //r28

    model = sys->model;
    star = sys->star;
    if(!sys->dirtyF) {
        star->mode = 10;
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->procTime, &sys->procT, 30);
        scaleP = model->scaleP[sys->chrSel[0]+MDMODEL_CAP_CHR_00];
        MdMathLerp(&scaleP->x, 1, 0, sys->procT);
        MdMathLerp(&scaleP->y, 1, 0, sys->procT);
        MdMathLerp(&scaleP->z, 0.1f, 0, sys->procT);
        scaleP = model->scaleP[MDMODEL_CAP_LV];
        MdMathLerpScale(scaleP, 0.8f, 0, sys->procT);
        for(i=0; i<5; i++) {
            scaleP = model->scaleP[i+MDMODEL_CAP_PACK_00];
            MdMathLerpScale(scaleP, 0.8f, 0, sys->procT);
        }
    }
    if(sys->procTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 100 insns */
BOOL fn_1_81F8(int param)
{
    MDMODEL_WORK *model; //r31
    HuVecF *scaleP; //r30

    MDCAMERA_WORK *camera; //sp+0x10
    HuVecF *posP; //sp+0xC
    HuVecF *rotP; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    posP = model->posP[MDMODEL_FINGER_1P];
    rotP = model->rotP[MDMODEL_FINGER_1P];
    scaleP = model->scaleP[MDMODEL_FINGER_1P];
    if(!sys->dirtyF) {
        if(param == 0) {
            scaleP->x = 0;
            scaleP->y = 0;
            scaleP->z = 0;
            Hu3DModelDispOn(model->mdlId[MDMODEL_FINGER_1P]);
            fn_1_87F4();
        }
        sys->dirtyF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 15.0f);
        MdMathLerpScale(scaleP, 0, 4, sys->procT);
    }
    if(param == 0) {
        if(sys->procTime >= 1) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/* 0x60C */ HuVecF lbl_1_data_60C[2] = { { 288.0f, -128.0f, 0.0f }, { 288.0f, 64.0f, 0.0f } }; /* fn_1_8388 (mdparty ProcName pos) */

/* 162 insns */
BOOL fn_1_8388(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_NAME];
    if(!sys->nameInitF) {
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            HuSprPosSet(grpId, 0, lbl_1_data_60C[1].x, lbl_1_data_60C[1].y);
            HuSprDispOn(grpId, 0);
        } else if(param == 1) {

        }
        sys->nameInitF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_60C[0].x, lbl_1_data_60C[1].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_60C[0].y, lbl_1_data_60C[1].y, sys->nameT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_60C[1].x, lbl_1_data_60C[0].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_60C[1].y, lbl_1_data_60C[0].y, sys->nameT);
    }
    if(sys->nameTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 71 insns */
void fn_1_8610(void)
{
    int i; //r31
    s8 padNo[4] = { 0, -1, -1, -1 };
    sys->unk1A = 0;
    for(i=0; i<4; i++) {
        sys->padNoConnect[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(padNo[i] == 0) {
            sys->padNoConnect[sys->unk1A] = i;
            sys->padConnect[i] = TRUE;
            sys->unk1A++;
        } else {
            sys->padConnect[i] = FALSE;
        }
    }
}

/* 50 insns */
void fn_1_872C(void)
{
    MDSPRITE_WORK *sprite = sys->sprite; //r30
    MDMODEL_WORK *model = sys->model;
    HUSPRGRPID grpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    int comNum = 0;
    s8 padNo[4] = { -1, -1, -1, -1 };
    int i; //r31
    for(i=0; i<4; i++) {
        if(i == 0) {
            sys->padNoEnable[i] = 0;
        } else {
            sys->padNoEnable[i] = -1;
        }
    }
}

/* 85 insns */
void fn_1_87F4(void)
{
    HuVecF *fingerPosP; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *chrPosP; //r29
    MDCAMERA_WORK *camera; //r28
    MDSPRITE_WORK *sprite; //r27
    HUSPRGRPID playerNoGrpId; //r26

    HuVecF pos3D; //sp+0x14
    HuVecF pos2D; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    fingerPosP = model->posP[MDMODEL_FINGER_1P];
    chrPosP = model->posP[sys->chrSel[0]+MDMODEL_CAP_CHR_00];
    playerNoGrpId = sprite->grpId[MDSPR_GRP_PLAYERNO];
    HuSprGrpPosSet(playerNoGrpId, 0, 0);
    *fingerPosP = *chrPosP;
    fingerPosP->x -= 60;
    fingerPosP->y += 105;
    fingerPosP->z += 30;
    pos3D = *chrPosP;
    Hu3D3Dto2D(&pos3D, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
    HuSprPosSet(playerNoGrpId, 0, pos2D.x, pos2D.y-18);
}

/* 0x624 */ s8 lbl_1_data_624[4][7] = { /* fn_1_8948: the next character per D-pad direction (left, right, up, down) */
    { 0, 6, 5, 4, 3, 2, 1 },
    { 0, 1, 2, 3, 4, 5, 6 },
    { 0, 3, 6, 2, 5, 1, 4 },
    { 0, 4, 1, 5, 2, 6, 3 }
};

/* 147 insns */
BOOL fn_1_8948(int playerNo)
{
    int padNo; //r31
    int i; //r30
    int dir; //r29
    int next; //r28

    padNo = 0;
    if(sys->chrSelEnd[playerNo] == TRUE) {
        return FALSE;
    }
    if((sys->pad->DStkDown[padNo] & PAD_BUTTON_LEFT) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_RIGHT) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_UP) ||
        (sys->pad->DStkDown[padNo] & PAD_BUTTON_DOWN)) {
        if(sys->pad->DStkDown[padNo] & PAD_BUTTON_LEFT) {
            dir = 0;
        } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_RIGHT) {
            dir = 1;
        } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_UP) {
            dir = 2;
        } else if(sys->pad->DStkDown[padNo] & PAD_BUTTON_DOWN) {
            dir = 3;
        }
        for(i=0; i<7; i++) {
            if(sys->chrSel[playerNo] == lbl_1_data_624[dir][i]) {
                next = i;
                next = ++next % 7;
                sys->chrSel[playerNo] = lbl_1_data_624[dir][next];
                break;
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 60 insns */
void fn_1_8B94(int mdlNo, int cameraNo)
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

/* 448 insns */
void fn_1_8C84(void)
{
    int i; //r31
    int boardNo; //r30
    int j; //r29

    if(sys->unk30 == 0) {
        GWMgPackSet(GW_MGPACK_ALL);
    } else if(sys->unk30 == 1) {
        GWMgPackSet(GW_MGPACK_EASY);
    } else if(sys->unk30 == 2) {
        GWMgPackSet(GW_MGPACK_ACTION);
    } else if(sys->unk30 == 3) {
        GWMgPackSet(GW_MGPACK_SKILL);
    } else if(sys->unk30 == 4) {
        GWMgPackSet(GW_MGPACK_GOOFY);
    }
    GwCommon.storyMgPack = GwSystem.mgPack;
    GwSystem.boardNo = 0;
    GwSystem.turnNo = 1;
    GWBonusStarFSet(TRUE);
    GWTeamFSet(FALSE);
    if(sys->unk2F == 0) {
        GwPlayer[0].dif = 1;
        for(i=1; i<4; i++) {
            GwPlayer[i].dif = 1;
        }
    } else if(sys->unk2F == 1) {
        GwPlayer[0].dif = 2;
        for(i=1; i<4; i++) {
            GwPlayer[i].dif = 2;
        }
    } else if(sys->unk2F == 2) {
        GwPlayer[0].dif = 3;
        for(i=1; i<4; i++) {
            GwPlayer[i].dif = 3;
        }
    } else if(sys->unk2F == 3) {
        GwPlayer[0].dif = 0;
        for(i=1; i<4; i++) {
            GwPlayer[i].dif = 0;
        }
    }
    /* the player and the three Story Mode rivals (Toad, Boo, Koopa Kid) */
    GwPlayer[0].charNo = sys->chrSel[0];
    GwPlayer[1].charNo = 10;
    GwPlayer[2].charNo = 11;
    GwPlayer[3].charNo = 12;
    GwPlayer[0].comF = FALSE;
    GwPlayer[1].comF = TRUE;
    GwPlayer[2].comF = TRUE;
    GwPlayer[3].comF = TRUE;
    for(i=0; i<4; i++) {
        GwPlayer[i].padNo = i;
        GwPlayer[i].grp = i;
        ((s8 *)&GwPlayer[i])[3] = 0;
        GwPlayerConf[i].charNo = GwPlayer[i].charNo;
        GwPlayerConf[i].padNo = GwPlayer[i].padNo;
        GwPlayerConf[i].dif = GwPlayer[i].dif;
        GwPlayerConf[i].type = GwPlayer[i].comF;
        GwPlayerConf[i].grp = GwPlayer[i].grp;
    }
    {
        /* four distinct random boards w01-w06 (linear probing on a repeat), then w07 */
        int boardUsed[6] = { 0, 0, 0, 0, 0, 0 };
        for(i=0; i<4; i++) {
            boardNo = frandmod(6);
            if(boardUsed[boardNo] == 0) {
                boardUsed[boardNo] = 1;
                GwCommon.storyBoardNo[i] = boardNo;
            } else if(boardUsed[boardNo] == 1) {
                for(j=0; j<5; j++) {
                    boardNo = ++boardNo % 6;
                    if(boardUsed[boardNo] == 0) {
                        boardUsed[boardNo] = 1;
                        GwCommon.storyBoardNo[i] = boardNo;
                        break;
                    }
                }
            }
        }
    }
    GwCommon.storyBoardNo[4] = 6;
    GwCommon.storyNo = -2;
}
#ifdef __MWERKS__
#endif

/* 0x640 */ s32 lbl_1_data_640[7] = { /* fn_1_9384 character voices (mdparty charSe) */
    MSM_SE_VOICE_MARIO+11,
    MSM_SE_VOICE_LUIGI+11,
    MSM_SE_VOICE_PEACH+11,
    MSM_SE_VOICE_YOSHI+11,
    MSM_SE_VOICE_WARIO+11,
    MSM_SE_VOICE_DAISY+11,
    MSM_SE_VOICE_WALUIGI+11
};

/* 104 insns */
void fn_1_9384(int cmd)
{
    int pan; //r30

    /* mdparty's function statics streamNo / seNo are the file-scope lbl_1_bss_24 / lbl_1_bss_20 */
    switch(cmd) {
        case MDSTORY_AUD_MUS_START:
            lbl_1_bss_24 = HuAudBGMPlay(MSM_STREAM_MODE);
            break;

        case MDSTORY_AUD_MUS_STOP:
            HuAudSStreamFadeOut(lbl_1_bss_24, 1000);
            break;

        case MDSTORY_AUD_SE_CMN_MOVE:
        case MDSTORY_AUD_SE_CMN_CONFIRM:
        case MDSTORY_AUD_SE_CMN_CANCEL:
        case MDSTORY_AUD_SE_MENU_MOVE:
            if(cmd == MDSTORY_AUD_SE_CMN_MOVE) {
                HuAudFXPlay(MSM_SE_CMN_01);
            } else if(cmd == MDSTORY_AUD_SE_CMN_CONFIRM) {
                HuAudFXPlay(MSM_SE_CMN_03);
            } else if(cmd == MDSTORY_AUD_SE_CMN_CANCEL) {
                HuAudFXPlay(MSM_SE_CMN_04);
            } else if(cmd == MDSTORY_AUD_SE_MENU_MOVE) {
                HuAudFXPlay(MSM_SE_MENU_27);
            }
            break;

        case MDSTORY_AUD_SE_MENU_28:
        {
            int pan = fn_1_9524(sys->chrSel[0]+MDMODEL_MARIO, MDCAMERA_MAIN);
            if(cmd == MDSTORY_AUD_SE_MENU_28) {
                lbl_1_bss_20 = HuAudFXPlayPan(MSM_SE_MENU_28, pan);
            }
        }
            break;

        case MDSTORY_AUD_SE_STAR_ENTER:
        case MDSTORY_AUD_SE_STAR_CONFIRM:
        {
            int pan = fn_1_9524(MDMODEL_STAR, MDCAMERA_FG);
            /* retail plays the same SE for both commands */
            if(cmd == MDSTORY_AUD_SE_STAR_ENTER) {
                HuAudFXPlayPan(MSM_SE_GUIDE_52, pan);
            } else if(cmd == MDSTORY_AUD_SE_STAR_CONFIRM) {
                HuAudFXPlayPan(MSM_SE_GUIDE_52, pan);
            }
        }
            break;

        case MDSTORY_AUD_SE_CHR_MARIO:
        case MDSTORY_AUD_SE_CHR_LUIGI:
        case MDSTORY_AUD_SE_CHR_PEACH:
        case MDSTORY_AUD_SE_CHR_YOSHI:
        case MDSTORY_AUD_SE_CHR_WARIO:
        case MDSTORY_AUD_SE_CHR_DAISY:
        case MDSTORY_AUD_SE_CHR_WALUIGI:
        {
            int pan = fn_1_9524((cmd-MDSTORY_AUD_SE_CHR_MARIO)+MDMODEL_CAP_CHR_00, MDCAMERA_MAIN);
            HuAudFXPlayPan(lbl_1_data_640[cmd-MDSTORY_AUD_SE_CHR_MARIO], pan);
        }
            break;

        case MDSTORY_AUD_SE_ALL_STOP:
            HuAudAllStop();
            break;
    }
}

/* 46 insns */
int fn_1_9524(int mdlNo, int cameraNo)
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

/* 0x794 */ static MDMODEL_DEBUG_INFO mdlInfo[MDMODEL_MAX] = { /* MdPosAdjustMode (a function static in the twin) */
    { "STAR", MDCAMERA_FG },
    { "STAGE", MDCAMERA_MAIN },
    { "STAGE_CHR", MDCAMERA_BG },
    { "MARIO", MDCAMERA_BG },
    { "LUIGI", MDCAMERA_BG },
    { "PEACH", MDCAMERA_BG },
    { "YOSHI", MDCAMERA_BG },
    { "WARIO", MDCAMERA_BG },
    { "DAISY", MDCAMERA_BG },
    { "WALUIGI", MDCAMERA_BG },
    { "CAP_CHR_00", MDCAMERA_MAIN },
    { "CAP_CHR_01", MDCAMERA_MAIN },
    { "CAP_CHR_02", MDCAMERA_MAIN },
    { "CAP_CHR_03", MDCAMERA_MAIN },
    { "CAP_CHR_04", MDCAMERA_MAIN },
    { "CAP_CHR_05", MDCAMERA_MAIN },
    { "CAP_CHR_06", MDCAMERA_MAIN },
    { "CAP_PACK_00", MDCAMERA_MAIN },
    { "CAP_PACK_01", MDCAMERA_MAIN },
    { "CAP_PACK_02", MDCAMERA_MAIN },
    { "CAP_PACK_03", MDCAMERA_MAIN },
    { "CAP_PACK_04", MDCAMERA_MAIN },
    { "CAP_LV", MDCAMERA_MAIN },
    { "FINGER_1P", MDCAMERA_MAIN },
    { "RING_1P", MDCAMERA_MAIN },
    { "FONTBGFILTER", MDCAMERA_FG },
};

/* 1114 insns */
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

