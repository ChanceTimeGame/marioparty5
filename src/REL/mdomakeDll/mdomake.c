/*
 * mdomakeDll -- the Bonus Mode hub (mdseldll's MdSelDll[0]). Card Party (mdcarddll), Beach Volley
 * (mdbeachdll, history evtno 2) and Ice Hockey (mdbeachdll, evtno 1 -> m580); B returns to
 * mdseldll. Decompiled 2026-10-01 from the reference assembly with the mdsel/mdmini/mdstory
 * twins; functions keep their fn_1_XXXX names, twins are noted per function.
 */

#include "REL/mdomakeDll.h"

/* mdmini.c precedent: the particle helpers come from an #included .c, included right after the
 * overlay header and BEFORE game/frand.h (retail calls frandmod unprototyped there). Its
 * HU3DPARMANPARAM statics are .data 0x0-0x13F; its six static functions are emitted last in .text. */
#include "REL/mdomakeDll/effect.c"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/charman.h"
#include "game/thpmain.h"
#include "datadir_enum.h"
#include "messnum/syshelp.h"
#include "math.h"

/* fn_1_5868 commands (mdsel MdSelAudExec layout) */
#define MDOMAKE_AUD_MUS_START 0
#define MDOMAKE_AUD_MUS_STOP 1
#define MDOMAKE_AUD_SE_CMN_MOVE 2 /* MSM_SE_CMN_01 */
#define MDOMAKE_AUD_SE_CMN_CONFIRM 3 /* MSM_SE_CMN_03 */
#define MDOMAKE_AUD_SE_CMN_CANCEL 4 /* MSM_SE_CMN_04 */
#define MDOMAKE_AUD_SE_MENU_27 5
#define MDOMAKE_AUD_SE_MENU_29 6
#define MDOMAKE_AUD_SE_STAR_TALK 7 /* MSM_SE_GUIDE_53, panned on the star */
#define MDOMAKE_AUD_SE_ALL_STOP 8

/* mdomake has no messnum header: Bonus Mode texts are message dir EXTRA */
#define MESS_EXTRA_ENTER MESSNUM(MESS_EXTRA, 0)
#define MESS_EXTRA_EXIT MESSNUM(MESS_EXTRA, 2)
#define MESS_EXTRA_GAME MESSNUM(MESS_EXTRA, 3) /* + selMode: the game's description */
#define MESS_EXTRA_GAME_START MESSNUM(MESS_EXTRA, 6) /* + selMode: the start confirmation */

/* mdparty/mdmini LERP_DATA (fn_1_2A78 / lbl_1_data_31C) */
typedef struct MdOmakeLerpData_s {
    HuVecF hvrA;
    HuVecF centerA;
    HuVecF hvrB;
    HuVecF centerB;
    int type;
    float step;
} MDOMAKE_LERP_DATA;

/* fn_1_3C24 lbl_1_bss_A0[3]: one record per game cap, 0x48 bytes (twin: mdmini MDMINI_E44C_REC) */
typedef struct MdOmakeCap_s {
    s16 mode; //0x00
    s16 wait; //0x02 frames before the cap enters (lbl_1_data_390)
    float oscTime[2]; //0x04 MdMathOscillate inputs
    float oscT[2]; //0x0C MdMathOscillate outputs
    float radius; //0x14
    float angle; //0x18
    float angleA; //0x1C lerp start of angle
    float radiusY; //0x20
    float angleY; //0x24
    float angleB; //0x28 lerp end of angle (param 0) / start of angleY (param 1)
    float scale; //0x2C (param 1)
    HuVecF from; //0x30 (param 2)
    HuVecF center; //0x3C
} MDOMAKE_CAP;


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
static const float lbl_1_rodata_48 = 32.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 372.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 56.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 376.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 340.0f; /* 0x58 */
static const float lbl_1_rodata_5C = -64.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 208.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 144.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 640.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 432.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 15.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 20.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 24.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 1.5f; /* 0x7C */
static const float lbl_1_rodata_80 = 12.0f; /* 0x80 */
static const float lbl_1_rodata_84 = -2.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 2.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 72.0f; /* 0x8C */
static const float lbl_1_rodata_90 = -28.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 8.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 225.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 250.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 150.0f; /* 0xA0 */
static const double lbl_1_rodata_A8 = 3.141592653589793; /* 0xA8 */
static const double lbl_1_rodata_B0 = 180.0; /* 0xB0 */
static const float lbl_1_rodata_B8 = 89.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 91.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = -149.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = -151.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = -29.0f; /* 0xC8 */
static const float lbl_1_rodata_CC = -31.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 0.75f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 60.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = -3000.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 120.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = -10.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 200.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 1200.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 2000.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = -180.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 16.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 3.0f; /* 0xF8 */
static const float lbl_1_rodata_FC = 0.3f; /* 0xFC */
static const float lbl_1_rodata_100 = 0.11111111f; /* 0x100 */
static const float lbl_1_rodata_104 = 5.0f; /* 0x104 */
static const float lbl_1_rodata_108 = 0.5f; /* 0x108 */
static const float lbl_1_rodata_10C = 10.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 0.05f; /* 0x110 */
static const float lbl_1_rodata_114 = 0.01f; /* 0x114 */
static const float lbl_1_rodata_118 = 0.1f; /* 0x118 */
static const float lbl_1_rodata_11C = -32.0f; /* 0x11C */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x208 */ SYS sysWork;
/* 0x204 */ SYS *sys;
/* 0x200 */ SYS *sysP;
/* 0x1FC */ MDOMAKE_EFFECT *lbl_1_bss_1FC; /* fn_1_1700: the star's glow particle */
/* 0x1E4 */ HuVecF lbl_1_bss_1E4[2]; /* fn_1_938: star pos2D */
/* 0x1CC */ HuVecF lbl_1_bss_1CC[2]; /* fn_1_938: star pos3D */
/* 0x1C8 */ float lbl_1_bss_1C8; /* fn_1_938: time */
/* 0x1C4 */ float lbl_1_bss_1C4; /* fn_1_938: timeY */
/* 0x1C0 */ float lbl_1_bss_1C0; /* fn_1_938: t */
/* 0x1BC */ float lbl_1_bss_1BC; /* fn_1_938: yt */
/* 0x18C */ HuVecF lbl_1_bss_18C[4]; /* fn_1_2BF8: cursor end points (R hidden/shown, L hidden/shown) */
/* 0x188 */ s32 lbl_1_bss_188;
/* 0x184 */ float lbl_1_bss_184;
/* 0x180 */ float lbl_1_bss_180;
/* 0x17C */ float lbl_1_bss_17C;
/* 0x178 */ s32 lbl_1_bss_178; /* fn_1_3C24: cleared, never read */
/* 0xA0 */ MDOMAKE_CAP lbl_1_bss_A0[MDMODEL_CAP_NUM]; /* fn_1_3C24 */
/* 0x94 */ HuVecF lbl_1_bss_94; /* fn_1_3C24: ring center */
/* 0x70 */ HuVecF lbl_1_bss_70[3]; /* fn_1_3C24 param 2: 3D targets of lbl_1_data_36C */
/* 0x6E gap_05_0000006E_bss (0x2): alignment gap */
/* 0x6C */ s16 lbl_1_bss_6C; /* fn_1_4F34 state */
/* 0x54 */ HuVecF lbl_1_bss_54[2]; /* fn_1_4F34: star pos2D */
/* 0x3C */ HuVecF lbl_1_bss_3C[2]; /* fn_1_4F34: star pos3D */
/* 0x24 */ HuVecF lbl_1_bss_24[2]; /* fn_1_4F34: star rot from/to */
/* 0x20 */ s32 lbl_1_bss_20; /* fn_1_5868: streamNo */

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x140 */ char *lbl_1_data_144 = "26"; /* 0x140 "26" + 0x144 pointer (mdsel.c:70) */
/* 0x148 */ OMOVL lbl_1_data_148[3] = { DLL_mdcarddll, DLL_mdbeachdll, DLL_mdbeachdll }; /* per selMode */
/* 0x154 */ unsigned int lbl_1_data_154[3] = { DATA_mdcard, DATA_mdbeach, DATA_mdbeach };
/* 0x160 */ char *lbl_1_data_198[3] = {
    "movie/ys_cp_0.thp",
    "movie/ys578_0.thp",
    "movie/ys580_0.thp"
};
/* 0x1A4 */ MD_FUNC MdFlowTbl[MDOMAKE_FLOW_MAX] = {
    fn_1_1700,
    fn_1_192C
};
/* 0x1AC */ MD_PROC MdProcTbl[MDOMAKE_PROC_MAX] = {
    fn_1_28BC,
    fn_1_2A78,
    fn_1_2BF8,
    fn_1_34F0,
    fn_1_3C24,
    fn_1_4F34,
    fn_1_54F0
};

/* twin: mdmini ObjectSetup (no flags; frees the returning game's dir) */
void ObjectSetup(void)
{
    sys = &sysWork;
    sysP = sys;
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowTime = 0;
    sys->flowMode = MDOMAKE_FLOW_INIT;
    sys->ovlCallMode = MD_OVLCALL_RETURN;
    sys->nextDll = DLL_selmenuDLL;
    sys->exitF = FALSE;
    sys->skipWipeF = FALSE;
    sys->objman = omInitObjMan(512, 8192);
    sys->ovlHis = omOvlHisGet(0);
    sys->evtNo = sys->ovlHis->evtno;
    if(sys->evtNo == 2) {
        HuARDirFree(DATA_m433);
    } else if(sys->evtNo == 3) {
        HuARDirFree(DATA_m580);
    }
    CharDataClose(-1);
    omGameSysInit(sys->objman);
    sys->obj[MDOMAKE_OBJ_DEBUGFONT] = omAddObj(sys->objman, 100, 0, 0, MdObjDebugFontCreate);
    sys->obj[MDOMAKE_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOMAKE_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDOMAKE_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDOMAKE_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDOMAKE_OBJ_PAD] = omAddObj(sys->objman, 101, 0, 0, MdObjPadMain);
    sys->obj[MDOMAKE_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOMAKE_OBJ_PAD]->data) {
        OSReport("sys->obj[MDOMAKE_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDOMAKE_OBJ_PAD]->data;
    sys->obj[MDOMAKE_OBJ_CAMERA] = omAddObj(sys->objman, 102, 0, 0, MdObjCameraCreate);
    sys->obj[MDOMAKE_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOMAKE_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDOMAKE_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDOMAKE_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDOMAKE_OBJ_LIGHT] = omAddObj(sys->objman, 103, 0, 0, MdObjLightCreate);
    sys->obj[MDOMAKE_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOMAKE_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDOMAKE_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDOMAKE_OBJ_LIGHT]->data;
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
    sys->star = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDOMAKE_STAR), HU_MEMNUM_OVL);
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
    sys->mainProc = HuPrcChildCreate(MdMain, 104, 12288, 0, sys->objman);
}

/* twin: mdsel MdMain */
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

/* twin: mdsel LoadProc (loadState 0 idle, 1 load sys->loadDir, 2 done) */
static void LoadProc(void)
{
    OSTick tick;
    while(1) {
        switch(sys->loadState) {
            case 0:
                break;

            case 1:
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(sys->loadDir);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadState = 2;
                break;

            case 2:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}

/* twin: mdsel StarUpdate. star->mode: 0 none, 1 enter start, 2 enter, 3 idle, 4 snap to the
 * corner (return from a game), 5 exit start, 6 exit, 7 gone; 8 also skips the billboard. */
void fn_1_938(void)
{
    MDMODEL_WORK *model; //r31
    MDOMAKE_STAR *star; //r30
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
    lbl_1_bss_1E4[0].x = 288;
    lbl_1_bss_1E4[0].y = 240;
    lbl_1_bss_1E4[0].z = 750;
    Hu3D2Dto3D(&lbl_1_bss_1E4[0], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_1CC[0]);
    *pos = lbl_1_bss_1CC[0];
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
                lbl_1_bss_1C8 = 0;
                lbl_1_bss_1C4 = 0;
                lbl_1_bss_1C0 = 0;
                lbl_1_bss_1BC = 0;
                lbl_1_bss_1E4[0].x = 288;
                lbl_1_bss_1E4[0].y = 240;
                lbl_1_bss_1E4[0].z = 750;
                lbl_1_bss_1E4[1].x = 64;
                lbl_1_bss_1E4[1].y = 300;
                lbl_1_bss_1E4[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_1E4[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_1CC[i]);
                }
                star->mode = 2;
                break;

            case 2:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_1C8, &lbl_1_bss_1C0, 30);
                MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_1C4, &lbl_1_bss_1BC, 30);
                MdMathLerp(&pos->x, lbl_1_bss_1CC[0].x, lbl_1_bss_1CC[1].x, lbl_1_bss_1C0);
                MdMathLerp(&pos->y, lbl_1_bss_1CC[0].y, lbl_1_bss_1CC[1].y, lbl_1_bss_1C0);
                MdMathLerpOfs(&pos->z, lbl_1_bss_1CC[0].z, lbl_1_bss_1CC[1].z, lbl_1_bss_1C0, -1*lbl_1_bss_1BC);
                if(lbl_1_bss_1C8 >= 1) {
                    star->mode = 3;
                }
                break;

            case 4:
                lbl_1_bss_1E4[1].x = 64;
                lbl_1_bss_1E4[1].y = 300;
                lbl_1_bss_1E4[1].z = 1000;
                Hu3D2Dto3D(&lbl_1_bss_1E4[1], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_1CC[1]);
                *pos = lbl_1_bss_1CC[1];
                star->mode = 3;
                break;

            case 5:
                lbl_1_bss_1C8 = 0;
                lbl_1_bss_1C4 = 0;
                lbl_1_bss_1C0 = 0;
                lbl_1_bss_1BC = 0;
                lbl_1_bss_1E4[0].x = 64;
                lbl_1_bss_1E4[0].y = 320;
                lbl_1_bss_1E4[0].z = 1000;
                lbl_1_bss_1E4[1].x = 288;
                lbl_1_bss_1E4[1].y = 240;
                lbl_1_bss_1E4[1].z = 1000;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_bss_1E4[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_1CC[i]);
                }
                star->mode = 6;
                break;

            case 6:
                MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_1C8, &lbl_1_bss_1C0, 30);
                MdMathLerp(&pos->x, lbl_1_bss_1CC[0].x, lbl_1_bss_1CC[1].x, lbl_1_bss_1C0);
                MdMathLerp(&pos->y, lbl_1_bss_1CC[0].y, lbl_1_bss_1CC[1].y, lbl_1_bss_1C0);
                MdMathLerp(&pos->z, lbl_1_bss_1CC[0].z, lbl_1_bss_1CC[1].z, lbl_1_bss_1C0);
                if(lbl_1_bss_1C8 >= 1) {
                    star->mode = 7;
                }
                break;

            case 0:
            case 3:
            case 7:
            case 8:
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
        if(star->mode != 8) {
            fn_1_5778(MDMODEL_STAR, MDCAMERA_MAIN);
        }
        HuPrcVSleep();
    }
}

/* retail waits `while(HuTHPStartCheck())`, which falls through at once on the GameCube (THPStart is
 * still 0 right after HuTHPSprCreateVol); the host stub returns TRUE forever, so the wait would hang. */
#define MOVIE_START_WAIT() while(HuTHPStartCheck()) { HuPrcVSleep(); }

/* 0x314 */ s16 lbl_1_data_314[4] = { 1, 77, 79, 0 }; /* mgDataTbl index per selMode (0: own movie) */

/* the cap movie process: sys->movieState 1 starts selMode's movie on its cap, 2 switches from
 * prevSelMode's cap to selMode's */
void fn_1_1078(void)
{
    MDMODEL_WORK *model; //r31
    MGDATA *mgData; //r30

    model = sys->model;
    sys->movieState = 0;
    while(1) {
        model = sys->model;
        switch(sys->movieState) {
            case 0:
                break;

            case 1:
                if(sys->selMode == 0) {
                    HuTHPSprCreateVol(lbl_1_data_198[0], 1, 100, 0);
                } else {
                    mgData = &mgDataTbl[lbl_1_data_314[sys->selMode]];
                    HuTHPSprCreateVol(mgData->movie[0], 1, 100, 0);
                }
                MOVIE_START_WAIT();
                Hu3DModelMatHookSet(model->mdlId[sys->selMode+MDMODEL_CAP_00], HuTHPMatHook);
                sys->movieState = 0;
                break;

            case 2:
                HuTHPClose();
                while(HuTHPProcCheck()) {
                    HuPrcVSleep();
                }
                Hu3DModelMatHookSet(model->mdlId[sys->prevSelMode+MDMODEL_CAP_00], NULL);
                if(sys->selMode == 0) {
                    HuTHPSprCreateVol(lbl_1_data_198[0], 1, 100, 0);
                } else {
                    mgData = &mgDataTbl[lbl_1_data_314[sys->selMode]];
                    HuTHPSprCreateVol(mgData->movie[0], 1, 100, 0);
                }
                MOVIE_START_WAIT();
                Hu3DModelMatHookSet(model->mdlId[sys->selMode+MDMODEL_CAP_00], HuTHPMatHook);
                sys->movieState = 0;
                break;
        }
        HuPrcVSleep();
    }
}

/* twin: mdmini fn_1_2018 */
void fn_1_1314(void)
{
    MDMESS_WORK *mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_MAIN);
        HuPrcVSleep();
    }
}

/* twin: mdmini fn_1_205C */
void fn_1_1358(void)
{
    MDMESS_WORK *mess = sys->mess;
    while(1) {
        mess = sys->mess;
        MdMessMain(mess, MDMESS_WIN_HELP);
        HuPrcVSleep();
    }
}

/* twin: mdstory MdInit */
void MdInit(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdModelCreate(sys->model, sys->camera);
    HuPrcVSleep();
    HuDataDirClose(DATA_mdomake);
    HuPrcVSleep();
    MdToueiMdlInit();
    sys->starProc = HuPrcChildCreate(fn_1_938, 106, 12288, 0, sys->objman);
    sys->movieProc = HuPrcChildCreate(fn_1_1078, 107, 4096, 0, sys->objman);
    sys->mainWinProc = HuPrcChildCreate(fn_1_1314, 108, 4096, 0, sys->objman);
    sys->helpWinProc = HuPrcChildCreate(fn_1_1358, 109, 4096, 0, sys->objman);
    sys->loadState = 0;
    sys->loadAsyncStat = 0;
    sys->loadDir = DATA_mdsel;
    sys->loadProc = HuPrcChildCreate(LoadProc, 105, 12288, 0, sys->objman);
    HuPrcVSleep();
}

/* twin: mdmini fn_1_22C8. ovlCallMode 3/4 are this hub's: Beach Volley / Ice Hockey via mdbeachdll */
void MdClose(void)
{
    if(!sys->skipWipeF) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeWait();
    }
    HuTHPClose();
    while(HuTHPProcCheck()) {
        HuPrcVSleep();
    }
    HuAudAllStop();
    MdMessKill(sys->mess);
    if(sys->ovlCallMode == MD_OVLCALL_GOTO) {
        omOvlGotoEx(sys->nextDll, 1, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_CALL) {
        omOvlCallEx(sys->nextDll, 1, 0, 0);
    } else if(sys->ovlCallMode == MD_OVLCALL_RETURN) {
        omOvlReturnEx(1, 1);
    } else if(sys->ovlCallMode == MDOMAKE_OVLCALL_VOLLEY) {
        omOvlCallEx(sys->nextDll, 1, 0, 0);
    } else if(sys->ovlCallMode == MDOMAKE_OVLCALL_HOCKEY) {
        omOvlCallEx(sys->nextDll, 1, 1, 0);
    }
    HuPrcEnd();
    while(1) {
        HuPrcVSleep();
    }
}

/* twin: mdsel MdSelFlowInit (+ the star glow, mdsel's ParticleGlowCreate) */
void fn_1_1700(void)
{
    int i; //r28
    MDMODEL_WORK *model; //r31
    MDSPRITE_WORK *sprite; //r30

    MDCAMERA_WORK *camera; //r26
    MDMESS_WORK *mess; //sp+0x8

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_UDLR, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_NAME, FALSE);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAR]);
    Hu3DModelDispOn(model->mdlId[MDMODEL_STAGE]);
    for(i=0; i<MDMODEL_CAP_NUM; i++) {
        Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_00]);
    }
    Hu3DModelDispOn(model->mdlId[MDMODEL_FONTBGFILTER]);
    lbl_1_bss_1FC = ParticleGlowCreate(sprite->animP[MDSPR_ANIM_EFFECT], 0, camera->camera[MDCAMERA_MAIN].bit);
    MdProcCall(MDOMAKE_PROC_RESET, 0);
    HuPrcVSleep();
    if(sys->evtNo == 0) {
        sys->subMode = 0;
    } else {
        sys->subMode = 10;
    }
    sys->flowMode = MDOMAKE_FLOW_MAIN;
}
/* Retail keeps some proc results in a block-scoped variable (a `mr` after the call, and a volatile
 * register of its own at each site): these spell that form. */

/* twin: mdsel MdSelFlowMain. subMode 0 first entry, 1 intro, 2 select, 10 return from a game */
void fn_1_192C(void)
{
    MDMESS_WORK *mess; //r31
    MDOMAKE_STAR *star; //r30
    int choice; //r29
    MDMODEL_WORK *model; //sp+0x8

    model = sys->model;
    mess = sys->mess;
    star = sys->star;
    switch(sys->subMode) {
        case 0:
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            sys->selMode = 0;
            sys->movieState = 1;
            sys->subMode = 1;
            break;

        case 1:
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            fn_1_5868(MDOMAKE_AUD_MUS_START);
            WipeWait();
            while(!MdProcCall(MDOMAKE_PROC_NAME, 0)) {
                HuPrcVSleep();
            }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            while(MdProcCall(MDOMAKE_PROC_WIN, FALSE) == FALSE) {
 HuPrcVSleep();
 }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            star->motNext = 2;
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 32, 372, 512, 64, 0);
            /* retail opens MAIN twice; MdMessWinOpen ignores an open window, so this one is a no-op */
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 56, 376, 464, 64, 0);
            MdMessWinOpen(mess, MDMESS_WIN_HELP, MDMESS_WIN_NOSPEAKER, 0, 0, 1, 64, 340, 448, 32, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_MAIN, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_ENTER, MDMESS_WIN_LIST_END);
            fn_1_5868(MDOMAKE_AUD_SE_STAR_TALK);
            while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                HuPrcVSleep();
            }
            MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
            while(MdProcCall(MDOMAKE_PROC_NAME, 1) == FALSE) {
 HuPrcVSleep();
 }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            star->mode = 1;
            star->motNext = 3;
            while(star->mode != 3) {
                HuPrcVSleep();
            }
            while(!MdProcCall(MDOMAKE_PROC_UNK4, 0)) {
                HuPrcVSleep();
            }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            star->motNext = 3;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_GAME+sys->selMode, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            while(MdProcCall(MDOMAKE_PROC_UNK2, 0) == FALSE) {
 HuPrcVSleep();
 }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            sys->subMode = 2;
            break;

        case 2:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) || (sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT)) {
                sys->prevSelMode = sys->selMode;
                if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
                    if(--sys->selMode == -1) {
                        sys->selMode = 2;
                    }
                    sys->cursorDir = FALSE;
                } else if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
                    sys->selMode = (++sys->selMode)%3;
                    sys->cursorDir = TRUE;
                }
                fn_1_5868(MDOMAKE_AUD_SE_CMN_MOVE);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_GAME+sys->selMode, MDMESS_WIN_LIST_END);
                sys->movieState = 2;
                while(MdProcCall(MDOMAKE_PROC_UNK4, 1) == FALSE) {
 HuPrcVSleep();
 }
                MdProcCall(MDOMAKE_PROC_RESET, 0);
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_5868(MDOMAKE_AUD_SE_CMN_CANCEL);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, TRUE, MESS_EXTRA_EXIT, MDMESS_WIN_LIST_END);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                while(MdMessWinCheck(mess, MDMESS_WIN_MAIN) == FALSE) {
                    HuPrcVSleep();
                }
                choice = MdMessWinChoiceGet(mess, MDMESS_WIN_MAIN);
                if(choice == -1 || choice == 1) {
                    MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_GAME+sys->selMode, MDMESS_WIN_LIST_END);
                    MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
                } else if(choice == 0) {
                    sys->loadState = 1;
                    sys->loadDir = DATA_mdsel;
                    star->motNext = 3;
                    MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                    while(!MdProcCall(MDOMAKE_PROC_UNK2, 1)) {
                        HuPrcVSleep();
                    }
                    MdProcCall(MDOMAKE_PROC_RESET, 0);
                    while(!MdProcCall(MDOMAKE_PROC_WIN, TRUE)) {
                        HuPrcVSleep();
                    }
                    MdProcCall(MDOMAKE_PROC_RESET, 0);
                    WipeColorSet(255, 255, 255);
                    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                    fn_1_5868(MDOMAKE_AUD_MUS_STOP);
                    WipeWait();
                    while(sys->loadState == 1) {
                        HuPrcVSleep();
                    }
                    omOvlHisChg(0, sys->ovlHis->ovl, 0, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_RETURN;
                    sys->nextDll = DLL_mdseldll;
                    sys->skipWipeF = TRUE;
                    sys->exitF = TRUE;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_5868(MDOMAKE_AUD_SE_CMN_CONFIRM);
                MdMessWinHomeClear(mess, MDMESS_WIN_HELP);
                MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_GAME_START+sys->selMode, MDMESS_WIN_LIST_END);
                while(!MdMessWinCheck(mess, MDMESS_WIN_MAIN)) {
                    HuPrcVSleep();
                }
                sys->loadState = 1;
                sys->loadDir = lbl_1_data_154[sys->selMode];
                while(MdProcCall(MDOMAKE_PROC_UNK2, 1) == FALSE) {
 HuPrcVSleep();
 }
                MdProcCall(MDOMAKE_PROC_RESET, 0);
                while(!MdProcCall(MDOMAKE_PROC_UNK4, 2)) {
                    HuPrcVSleep();
                }
                MdProcCall(MDOMAKE_PROC_RESET, 0);
                while(MdProcCall(MDOMAKE_PROC_UNK5, 0) == FALSE) {
 HuPrcVSleep();
 }
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                fn_1_5868(MDOMAKE_AUD_MUS_STOP);
                HuPrcVSleep();
                while(WipeCheckEnd()) {
                    MdProcCall(MDOMAKE_PROC_UNK5, 0);
                    HuPrcVSleep();
                }
                while(sys->loadState == 1) {
                    HuPrcVSleep();
                }
                if(sys->selMode == 0) {
                    omOvlHisChg(0, sys->ovlHis->ovl, 1, sys->ovlHis->stat);
                    sys->ovlCallMode = MD_OVLCALL_CALL;
                } else if(sys->selMode == 1) {
                    omOvlHisChg(0, sys->ovlHis->ovl, 2, sys->ovlHis->stat);
                    sys->ovlCallMode = MDOMAKE_OVLCALL_VOLLEY;
                } else if(sys->selMode == 2) {
                    omOvlHisChg(0, sys->ovlHis->ovl, 3, sys->ovlHis->stat);
                    sys->ovlCallMode = MDOMAKE_OVLCALL_HOCKEY;
                }
                sys->nextDll = lbl_1_data_148[sys->selMode];
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;

        case 10:
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            sys->selMode = 0;
            star->mode = 4;
            while(star->mode != 3) {
                HuPrcVSleep();
            }
            while(!MdProcCall(MDOMAKE_PROC_UNK4, 3)) {
                HuPrcVSleep();
            }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            sys->movieState = 1;
            WipeColorSet(255, 255, 255);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            fn_1_5868(MDOMAKE_AUD_MUS_START);
            WipeWait();
            while(!MdProcCall(MDOMAKE_PROC_WIN, FALSE)) {
                HuPrcVSleep();
            }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 32, 372, 512, 64, 0);
            MdMessWinOpen(mess, MDMESS_WIN_MAIN, MDMESS_WIN_NOSPEAKER, 0, 0, 0, 56, 376, 464, 64, 0);
            MdMessWinOpen(mess, MDMESS_WIN_HELP, MDMESS_WIN_NOSPEAKER, 0, 0, 1, 64, 340, 448, 32, 0);
            MdMessWinSpeedSet(mess, MDMESS_WIN_HELP, 0);
            MdMessWinAttrSet(mess, MDMESS_WIN_MAIN, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinAttrSet(mess, MDMESS_WIN_HELP, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinPad1Set(mess, MDMESS_WIN_MAIN);
            star->motNext = 3;
            MdMessWinMesSet(mess, MDMESS_WIN_MAIN, FALSE, MESS_EXTRA_GAME+sys->selMode, MDMESS_WIN_LIST_END);
            MdMessWinMesSet(mess, MDMESS_WIN_HELP, FALSE, MESS_SYSHELP_MENU_SEL, MDMESS_WIN_LIST_END);
            while(MdProcCall(MDOMAKE_PROC_UNK2, 0) == FALSE) {
 HuPrcVSleep();
 }
            MdProcCall(MDOMAKE_PROC_RESET, 0);
            sys->subMode = 2;
            break;
    }
}

/* twin: mdparty MdPartyProcReset */
BOOL fn_1_28BC(int param)
{
    sys->winInitF = FALSE;
    sys->procInitF = FALSE;
    sys->cursorInitF = FALSE;
    sys->nameInitF = FALSE;
    sys->unk8C = FALSE;
    sys->procTime = 0.0f;
    sys->procOfsTime = 0.0f;
    sys->unkA0 = 0.0f;
    sys->sprTime = 0.0f;
    sys->cursorTime = 0.0f;
    sys->nameTime = 0.0f;
    sys->procT = 0.0f;
    sys->procOfsT = 0.0f;
    sys->unkB8 = 0.0f;
    sys->sprT = 0.0f;
    sys->cursorT = 0.0f;
    sys->nameT = 0.0f;
    return FALSE;
}

/* 0x31C */ MDOMAKE_LERP_DATA lbl_1_data_31C[1] = { /* fn_1_2A78; mdparty ProcCamera lerpData */
    { { 90.0f, 0.0f, 2000.0f }, { 0.0f, 0.0f, 0.0f }, { 90.0f, 0.0f, 1200.0f }, { 0.0f, 50.0f, 0.0f }, 2, 60.0f }
};

/* twin: mdmini fn_1_991C (one oscillator) */
BOOL fn_1_2A78(int param)
{
    MDOMAKE_LERP_DATA *lerpP;
    MDCAMERA_WORK *cameraWork;
    MDCAMERA *camera;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[MDCAMERA_BG];
    lerpP = &lbl_1_data_31C[param];
    MdMathOscillate(lerpP->type, &sys->cursorTime, &sys->cursorT, lerpP->step);
    MdMathLerp(&camera->hvr.x, lerpP->hvrA.x, lerpP->hvrB.x, sys->cursorT);
    MdMathLerp(&camera->hvr.y, lerpP->hvrA.y, lerpP->hvrB.y, sys->cursorT);
    MdMathLerp(&camera->hvr.z, lerpP->hvrA.z, lerpP->hvrB.z, sys->cursorT);
    MdMathLerp(&camera->center.x, lerpP->centerA.x, lerpP->centerB.x, sys->cursorT);
    MdMathLerp(&camera->center.y, lerpP->centerA.y, lerpP->centerB.y, sys->cursorT);
    MdMathLerp(&camera->center.z, lerpP->centerA.z, lerpP->centerB.z, sys->cursorT);
    /* retail reads procTime (0x98) here, not the cursorTime (0xA8) it advanced: transcribed as is */
    if(sys->procTime >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* twin: mdstory fn_1_4A98 (the left/right cursor arrows; fixed screen positions, no 3D anchor).
 * param 0 slide in, 1 slide out, 2 pulse right, 3 pulse left; lbl_1_bss_18C = the four end points */
BOOL fn_1_2BF8(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29
    HuVec2f *sprScale; //r28

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_CURSOR_UDLR];
    if(!sys->cursorInitF) {
        lbl_1_bss_18C[0].x = -64.0f;
        lbl_1_bss_18C[0].y = 208.0f;
        lbl_1_bss_18C[0].z = 0;
        lbl_1_bss_18C[1].x = 144.0f;
        lbl_1_bss_18C[1].y = 208.0f;
        lbl_1_bss_18C[1].z = 0;
        lbl_1_bss_18C[2].x = 640.0f;
        lbl_1_bss_18C[2].y = 208.0f;
        lbl_1_bss_18C[2].z = 0;
        lbl_1_bss_18C[3].x = 432.0f;
        lbl_1_bss_18C[3].y = 208.0f;
        lbl_1_bss_18C[3].z = 0;
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos->x = lbl_1_bss_18C[0].x;
            sprPos->y = lbl_1_bss_18C[0].y;
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
            sprPos->x = lbl_1_bss_18C[2].x;
            sprPos->y = lbl_1_bss_18C[2].y;
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        } else if(param == 2) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
            sprPos->x = lbl_1_bss_18C[1].x;
            sprPos->y = lbl_1_bss_18C[1].y;
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), 0);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        } else if(param == 3) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
            sprPos->x = lbl_1_bss_18C[3].x;
            sprPos->y = lbl_1_bss_18C[3].y;
            HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), 0);
            HuSprDispOn(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        }
        sys->cursorInitF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->cursorTime, &sys->cursorT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[0].x, lbl_1_bss_18C[1].x, sys->cursorT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[2].x, lbl_1_bss_18C[3].x, sys->cursorT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->cursorTime, &sys->cursorT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[1].x, lbl_1_bss_18C[0].x, sys->cursorT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[3].x, lbl_1_bss_18C[2].x, sys->cursorT);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_180, &sys->cursorTime, &sys->cursorT, 20);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[1].x, lbl_1_bss_18C[1].x-24, sys->cursorT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->cursorT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->cursorT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[1].x, lbl_1_bss_18C[1].x-24, sys->cursorT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->cursorT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->cursorT);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_R), sys->cursorT);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_180, &sys->cursorTime, &sys->cursorT, 20);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[3].x, 24+lbl_1_bss_18C[3].x, sys->cursorT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->cursorT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->cursorT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_CURSOR_UDLR, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L));
        MdMathLerp(&sprPos->x, lbl_1_bss_18C[3].x, 24+lbl_1_bss_18C[3].x, sys->cursorT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->cursorT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->cursorT);
        HuSprTPLvlSet(grpId, MDSPR_GRP_MEMBERNO(MDSPR_GRP_CURSOR_UDLR, MDSPR_CURSOR_GLOW_UDLR_L), sys->cursorT);
    }
    if(sys->cursorTime >= 1) {
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

/* twin: mdmini fn_1_AF34 (MdPartyProcWin); lbl_1_bss_188 state, 184 top y, 180 bottom y, 17C bg scale y */
BOOL fn_1_34F0(int param)
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
        lbl_1_bss_188 = 0;
        lbl_1_bss_184 = topPos->y;
        lbl_1_bss_180 = bottomPos->y;
        lbl_1_bss_17C = bgScale->y;
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
        if(lbl_1_bss_188 == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, 0, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, 0, 2, sys->sprT);
            MdMathLerp(&topScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bottomScale->x, 0, 72, sys->sprT);
            MdMathLerp(&bgScale->x, 0, 1, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_188 = 1;
            }
        } else if(lbl_1_bss_188 == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, -2, -28, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 32, sys->sprT);
            MdMathLerp(&bgScale->y, 0, 8, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_188 = 2;
            }
        }
    } else if(param == TRUE) {
        if(lbl_1_bss_188 == 0) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 15);
            MdMathLerp(&topPos->y, lbl_1_bss_184, -2, sys->sprT);
            MdMathLerp(&bottomPos->y, lbl_1_bss_180, 2, sys->sprT);
            MdMathLerp(&bgScale->y, lbl_1_bss_17C, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                sys->sprTime = 0;
                lbl_1_bss_188 = 1;
            }
            
        } else if(lbl_1_bss_188 == 1) {
            MdMathOscillate(MDMATH_OSC_90, &sys->sprTime, &sys->sprT, 12);
            MdMathLerp(&topPos->y, -2, 0, sys->sprT);
            MdMathLerp(&bottomPos->y, 2, 0, sys->sprT);
            MdMathLerp(&topScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bottomScale->x, 72, 0, sys->sprT);
            MdMathLerp(&bgScale->x, 1, 0, sys->sprT);
            if(sys->sprTime >= 1) {
                lbl_1_bss_188 = 2;
            }
        }
    }
    if(lbl_1_bss_188 == 2) {
        if(param == TRUE) {
            MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x354 */ float lbl_1_data_354[3] = { 90.0f, 210.0f, -30.0f }; /* fn_1_3C24: cap angle on the ring */
/* 0x360 */ float lbl_1_data_360[3] = { -90.0f, -210.0f, 30.0f }; /* fn_1_3C24: cap angleY on the ring */
/* 0x36C */ HuVecF lbl_1_data_36C[3] = { { 288.0f, 200.0f, 1200.0f }, { -64.0f, -32.0f, 4000.0f }, { 640.0f, -32.0f, 4000.0f } }; /* fn_1_3C24 param 2: 2D targets */
/* 0x390 */ s16 lbl_1_data_390[4] = { 8, 0, 4, 0 }; /* fn_1_3C24: entry delay per cap */
/* 0x398 */ float lbl_1_data_398[3] = { 270.0f, 90.0f, 180.0f }; /* fn_1_3C24 param 0: fly-in start angle */
/* 0x3A4 */ float lbl_1_data_3A4[3] = { 630.0f, -270.0f, -180.0f }; /* fn_1_3C24 param 0: fly-in end angle */

/* twin (loosely): mdmini fn_1_E44C. The three game caps on their ring around lbl_1_bss_94.
 * param 0 fly in, 1 rotate to the new selection (sys->cursorDir), 2 the selected cap
 * comes forward and the others leave (A), 3 place them at once (return from a game). */
BOOL fn_1_3C24(int param)
{
    MDOMAKE_CAP *capP; //r31
    int i; //r30
    HuVecF *pos; //r29
    MDMODEL_WORK *model; //r28
    HuVecF *scale; //r27
    HuVecF *rot; //r26
    MDCAMERA_WORK *camera; //r24
    MDSPRITE_WORK *sprite; //sp+0x8

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    if(!sys->procInitF) {
        if(param == 0) {
            lbl_1_bss_94.x = 0;
            lbl_1_bss_94.y = 225;
            lbl_1_bss_94.z = 0;
            for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
                pos = model->posP[i+MDMODEL_CAP_00];
                rot = model->rotP[i+MDMODEL_CAP_00];
                scale = model->scaleP[i+MDMODEL_CAP_00];
                rot->x = 0;
                rot->y = 0;
                rot->z = 0;
                scale->x = 0;
                scale->y = 0;
                scale->z = 0;
                capP->mode = 0;
                capP->wait = lbl_1_data_390[i];
                capP->oscTime[0] = 0;
                capP->oscTime[1] = 0;
                capP->oscT[0] = 0;
                capP->oscT[1] = 0;
                capP->radius = 250;
                capP->angle = lbl_1_data_354[i];
                capP->angleA = 0;
                capP->radiusY = 150;
                capP->angleY = lbl_1_data_360[i];
                capP->angleB = 0;
                pos->x = lbl_1_bss_94.x + capP->radius * HuCos(capP->angle);
                pos->y = lbl_1_bss_94.y + capP->radiusY * HuSin(capP->angleY);
                pos->z = lbl_1_bss_94.z + capP->radius * HuSin(capP->angle);
                capP->center = *pos;
                capP->radius = 1000;
                capP->angle = lbl_1_data_398[i];
                capP->angleA = lbl_1_data_398[i];
                capP->angleB = lbl_1_data_3A4[i];
                pos->x = capP->center.x + capP->radius * HuCos(capP->angle);
                pos->y = capP->center.y + capP->radius * HuSin(capP->angle);
                pos->z = capP->center.z;
            }
            fn_1_5868(MDOMAKE_AUD_SE_MENU_27);
        } else if(param == 1) {
            for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
                capP->mode = 0;
                capP->wait = 0;
                capP->oscTime[0] = 0;
                capP->oscTime[1] = 0;
                capP->oscT[0] = 0;
                capP->oscT[1] = 0;
                capP->angleA = capP->angle;
                capP->angleB = capP->angleY;
            }
        } else if(param == 2) {
            for(i = 0; i < 3; i++) {
                Hu3D2Dto3D(&lbl_1_data_36C[i], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_70[i]);
            }
            for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
                pos = model->posP[i+MDMODEL_CAP_00];
                rot = model->rotP[i+MDMODEL_CAP_00];
                scale = model->scaleP[i+MDMODEL_CAP_00];
                capP->mode = 0;
                capP->wait = 0;
                capP->oscTime[0] = 0;
                capP->oscTime[1] = 0;
                capP->oscT[0] = 0;
                capP->oscT[1] = 0;
                capP->from = *pos;
                if(capP->angle >= 89 && capP->angle <= 91) {
                    capP->center = lbl_1_bss_70[0];
                } else if(capP->angle <= -149 && capP->angle >= -151) {
                    capP->center = lbl_1_bss_70[1];
                } else if(capP->angle <= -29 && capP->angle >= -31) {
                    capP->center = lbl_1_bss_70[2];
                }
            }
            fn_1_5868(MDOMAKE_AUD_SE_MENU_27);
        } else if(param == 3) {
            lbl_1_bss_94.x = 0;
            lbl_1_bss_94.y = 225;
            lbl_1_bss_94.z = 0;
            for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
                pos = model->posP[i+MDMODEL_CAP_00];
                rot = model->rotP[i+MDMODEL_CAP_00];
                scale = model->scaleP[i+MDMODEL_CAP_00];
                rot->x = 0;
                rot->y = 0;
                rot->z = 0;
                if(i == sys->selMode) {
                    scale->x = 2;
                    scale->y = 2;
                    scale->z = 2;
                } else {
                    scale->x = 0.75f;
                    scale->y = 0.75f;
                    scale->z = 0.75f;
                }
                Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_00]);
                capP->mode = 0;
                capP->wait = lbl_1_data_390[i];
                capP->oscTime[0] = 0;
                capP->oscTime[1] = 0;
                capP->oscT[0] = 0;
                capP->oscT[1] = 0;
                capP->radius = 250;
                capP->angle = lbl_1_data_354[i];
                capP->angleA = 0;
                capP->radiusY = 150;
                capP->angleY = lbl_1_data_360[i];
                capP->angleB = 0;
                MdMathAngleClamp(&capP->angle);
                MdMathAngleClamp(&capP->angleY);
                pos->x = lbl_1_bss_94.x + capP->radius * HuCos(capP->angle);
                pos->y = lbl_1_bss_94.y + capP->radiusY * HuSin(capP->angleY);
                pos->z = lbl_1_bss_94.z + capP->radius * HuSin(capP->angle);
                capP->center = *pos;
            }
        }
        lbl_1_bss_178 = 0;
        sys->procInitF = TRUE;
    }
    if(param == 0) {
        for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
            pos = model->posP[i+MDMODEL_CAP_00];
            rot = model->rotP[i+MDMODEL_CAP_00];
            scale = model->scaleP[i+MDMODEL_CAP_00];
            switch(capP->mode) {
                case 0:
                    if(--capP->wait <= 0) {
                        Hu3DModelDispOn(model->mdlId[i+MDMODEL_CAP_00]);
                        capP->mode++;
                    }
                    break;

                case 1:
                    MdMathOscillate(MDMATH_OSC_90, &capP->oscTime[0], &capP->oscT[0], 60);
                    MdMathOscillate(MDMATH_OSC_180, &capP->oscTime[1], &capP->oscT[1], 60);
                    MdMathLerp(&capP->radius, 1000, 0, capP->oscT[0]);
                    MdMathLerp(&capP->angle, capP->angleA, capP->angleB, capP->oscT[0]);
                    pos->x = capP->center.x + capP->radius * HuCos(capP->angle);
                    pos->y = capP->center.y + capP->radius * HuSin(capP->angle);
                    MdMathLerp(&pos->z, -3000, capP->center.z, capP->oscT[0]);
                    if(i == sys->selMode) {
                        MdMathLerpScale(scale, 0, 2, capP->oscT[0]);
                    } else {
                        MdMathLerpScale(scale, 0, 0.75f, capP->oscT[0]);
                    }
                    if(capP->oscTime[0] >= 1) {
                        capP->radius = 250;
                        capP->radiusY = 150;
                        capP->angle = lbl_1_data_354[i];
                        capP->angleY = lbl_1_data_360[i];
                        MdMathAngleClamp(&capP->angle);
                        MdMathAngleClamp(&capP->angleY);
                        capP->mode++;
                    }
                    break;

                case 2:
                    break;
            }
        }
    } else if(param == 1) {
        for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
            pos = model->posP[i+MDMODEL_CAP_00];
            rot = model->rotP[i+MDMODEL_CAP_00];
            scale = model->scaleP[i+MDMODEL_CAP_00];
            switch(capP->mode) {
                case 0:
                    MdMathOscillate(MDMATH_OSC_90, &capP->oscTime[0], &capP->oscT[0], 20);
                    MdMathOscillate(MDMATH_OSC_180, &capP->oscTime[1], &capP->oscT[1], 20);
                    if(sys->cursorDir == 0) {
                        MdMathLerp(&capP->angle, capP->angleA, 120+capP->angleA, capP->oscT[0]);
                        MdMathLerp(&capP->angleY, capP->angleB, capP->angleB-120, capP->oscT[0]);
                    } else if(sys->cursorDir == 1) {
                        MdMathLerp(&capP->angle, capP->angleA, capP->angleA-120, capP->oscT[0]);
                        MdMathLerp(&capP->angleY, capP->angleB, 120+capP->angleB, capP->oscT[0]);
                    }
                    pos->x = lbl_1_bss_94.x + capP->radius * HuCos(capP->angle);
                    pos->y = lbl_1_bss_94.y + capP->radiusY * HuSin(capP->angleY);
                    pos->z = lbl_1_bss_94.z + capP->radius * HuSin(capP->angle);
                    if(i == sys->selMode) {
                        MdMathLerpOfs(&capP->scale, 0.75f, 2, capP->oscT[0], capP->oscT[1]);
                    } else if(i == sys->prevSelMode) {
                        MdMathLerp(&capP->scale, 2, 0.75f, capP->oscT[0]);
                    } else {
                        capP->scale = 0.75f;
                    }
                    scale->x = capP->scale;
                    scale->y = capP->scale;
                    scale->z = capP->scale;
                    if(capP->oscTime[0] >= 1) {
                        MdMathAngleClamp(&capP->angle);
                        MdMathAngleClamp(&capP->angleY);
                        capP->mode++;
                    }
                    break;

                case 1:
                    break;
            }
        }
        if(sys->cursorDir == 0) {
            MdProcCall(MDOMAKE_PROC_UNK2, 3);
        } else if(sys->cursorDir == 1) {
            MdProcCall(MDOMAKE_PROC_UNK2, 2);
        }
    } else if(param == 2) {
        for(capP = &lbl_1_bss_A0[0], i = 0; i < MDMODEL_CAP_NUM; i++, capP++) {
            pos = model->posP[i+MDMODEL_CAP_00];
            rot = model->rotP[i+MDMODEL_CAP_00];
            scale = model->scaleP[i+MDMODEL_CAP_00];
            switch(capP->mode) {
                case 0:
                    if(i == sys->selMode) {
                        MdMathOscillate(MDMATH_OSC_90, &capP->oscTime[0], &capP->oscT[0], 30);
                        MdMathOscillate(MDMATH_OSC_180, &capP->oscTime[1], &capP->oscT[1], 30);
                        MdMathLerp(&pos->x, capP->from.x, capP->center.x, capP->oscT[0]);
                        MdMathLerpOfs(&pos->y, capP->from.y, capP->center.y, capP->oscT[0], -10.0f*capP->oscT[1]);
                        MdMathLerp(&pos->z, capP->from.z, capP->center.z, capP->oscT[0]);
                    } else {
                        MdMathOscillate(MDMATH_OSC_90_REV, &capP->oscTime[0], &capP->oscT[0], 30);
                        MdMathOscillate(MDMATH_OSC_180, &capP->oscTime[1], &capP->oscT[1], 30);
                        MdMathLerp(&pos->x, capP->from.x, capP->center.x, capP->oscT[0]);
                        MdMathLerp(&pos->y, capP->from.y, capP->center.y, capP->oscT[0]);
                        MdMathLerpOfs(&pos->z, capP->from.z, capP->center.z, capP->oscT[0], capP->oscT[1]);
                    }
                    if(capP->oscTime[0] >= 1) {
                        if(i != sys->selMode) {
                            Hu3DModelDispOff(model->mdlId[i+MDMODEL_CAP_00]);
                        }
                        capP->mode++;
                    }
                    break;

                case 1:
                    break;
            }
        }
    } else {
        param == 3;
    }
    if(param == 0) {
        if(lbl_1_bss_A0[0].mode == 2) {
            return TRUE;
        }
    } else if(param == 1) {
        if(lbl_1_bss_A0[0].mode == 1) {
            return TRUE;
        }
    } else if(param == 2) {
        if(lbl_1_bss_A0[0].mode == 1) {
            return TRUE;
        }
    } else if(param == 3) {
        return TRUE;
    }
    return FALSE;
}

/* twin (loosely): mdmini fn_1_10264. The star flies from the corner to the selected cap and spins
 * (A on a game): lbl_1_bss_54/3C = star pos2D/pos3D, lbl_1_bss_24 = rot from/to, lbl_1_bss_6C state.
 * From procTime 0.3 on it also slides the window out (proc 3) and runs the camera lerp (proc 1). */
BOOL fn_1_4F34(int param)
{
    HuVecF *pos; //r31
    MDCAMERA_WORK *camera; //r30
    HuVecF *rot; //r29
    MDMODEL_WORK *model; //r28
    MDMESS_WORK *mess; //r26
    MDSPRITE_WORK *sprite; //sp+0xC
    HuVecF *scale; //sp+0x8

    camera = sys->camera;
    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    pos = model->posP[MDMODEL_STAR];
    rot = model->rotP[MDMODEL_STAR];
    scale = model->scaleP[MDMODEL_STAR];
    if(!sys->procInitF) {
        lbl_1_bss_54[0].x = 64;
        lbl_1_bss_54[0].y = 300;
        lbl_1_bss_54[0].z = 1000;
        Hu3D2Dto3D(&lbl_1_bss_54[0], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_3C[0]);
        *pos = lbl_1_bss_3C[0];
        lbl_1_bss_54[1].x = 288;
        lbl_1_bss_54[1].y = 200;
        lbl_1_bss_54[1].z = 1200;
        Hu3D2Dto3D(&lbl_1_bss_54[1], camera->camera[MDCAMERA_BG].bit, &lbl_1_bss_3C[1]);
        Hu3D3Dto2D(&lbl_1_bss_3C[1], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_54[1]);
        lbl_1_bss_54[1].z = 2000;
        Hu3D2Dto3D(&lbl_1_bss_54[1], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_3C[1]);
        fn_1_5778(MDMODEL_STAR, MDCAMERA_MAIN);
        rot->z = 0;
        lbl_1_bss_24[0] = *rot;
        lbl_1_bss_24[1].x = 0;
        lbl_1_bss_24[1].y = -180;
        lbl_1_bss_24[1].z = 16;
        fn_1_5868(MDOMAKE_AUD_SE_MENU_29);
        lbl_1_bss_6C = 0;
        sys->procInitF = TRUE;
    }
    switch(lbl_1_bss_6C) {
        case 0:
        case 1:
            MdMathOscillate(MDMATH_OSC_90_REV, &sys->procTime, &sys->procT, 90);
            MdMathOscillate(MDMATH_OSC_180, &sys->procOfsTime, &sys->procOfsT, 90);
            MdMathLerpOfs(&pos->x, lbl_1_bss_3C[0].x, lbl_1_bss_3C[1].x, sys->procT, 1.5f*sys->procOfsT);
            MdMathLerpOfs(&pos->y, lbl_1_bss_3C[0].y, lbl_1_bss_3C[1].y, sys->procT, 1.5f*sys->procOfsT);
            MdMathLerpOfs(&pos->z, lbl_1_bss_3C[0].z, lbl_1_bss_3C[1].z, sys->procT, 0);
            MdMathLerp(&rot->x, lbl_1_bss_24[0].x, lbl_1_bss_24[1].x, sys->procT);
            MdMathLerp(&rot->y, lbl_1_bss_24[0].y, lbl_1_bss_24[1].y, sys->procT);
            MdMathLerpOfs(&rot->z, lbl_1_bss_24[0].z, lbl_1_bss_24[1].z, sys->procT, 3.0f*sys->procOfsT);
            ParticleGlowPosSet(lbl_1_bss_1FC, pos);
            if(sys->procTime >= 0.3f) {
                MdProcCall(MDOMAKE_PROC_WIN, TRUE);
                MdProcCall(MDOMAKE_PROC_CAMERA, 0);
            }
            if(lbl_1_bss_6C == 0 && sys->procTime >= 0.3f) {
                MdMessWinHomeClear(mess, MDMESS_WIN_MAIN);
                lbl_1_bss_6C++;
            }
            break;
    }
    if(lbl_1_bss_6C == 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x3B0 */ HuVecF lbl_1_data_3B0[2] = { { 288.0f, -128.0f, 0.0f }, { 288.0f, 64.0f, 0.0f } }; /* fn_1_54F0 */

/* twin: mdmini fn_1_149A4 (MdPartyProcName) */
BOOL fn_1_54F0(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29

    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_NAME];
    if(!sys->nameInitF) {
        if(param == 0) {
            HuSprGrpPosSet(grpId, 0, 0);
            HuSprPosSet(grpId, 0, lbl_1_data_3B0[1].x, lbl_1_data_3B0[1].y);
            HuSprDispOn(grpId, 0);
        } else if(param == 1) {

        }
        sys->nameInitF = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_3B0[0].x, lbl_1_data_3B0[1].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_3B0[0].y, lbl_1_data_3B0[1].y, sys->nameT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->nameTime, &sys->nameT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_NAME, 0);
        MdMathLerp(&sprPos->x, lbl_1_data_3B0[1].x, lbl_1_data_3B0[0].x, sys->nameT);
        MdMathLerp(&sprPos->y, lbl_1_data_3B0[1].y, lbl_1_data_3B0[0].y, sys->nameT);
    }
    if(sys->nameTime >= 1) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* twin: mdmini fn_1_15CF8 (mdsel MdSelBillboardUpdate) */
void fn_1_5778(int mdlNo, int cameraNo)
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

/* twin: mdsel MdSelAudExec */
void fn_1_5868(int cmd)
{
    int pan;

    switch(cmd) {
        case MDOMAKE_AUD_MUS_START:
            lbl_1_bss_20 = HuAudBGMPlay(MSM_STREAM_MODE);
            break;

        case MDOMAKE_AUD_MUS_STOP:
            HuAudSStreamFadeOut(lbl_1_bss_20, 1000);
            break;

        case MDOMAKE_AUD_SE_CMN_MOVE:
        case MDOMAKE_AUD_SE_CMN_CONFIRM:
        case MDOMAKE_AUD_SE_CMN_CANCEL:
        case MDOMAKE_AUD_SE_MENU_27:
        case MDOMAKE_AUD_SE_MENU_29:
            if(cmd == MDOMAKE_AUD_SE_CMN_MOVE) {
                HuAudFXPlay(MSM_SE_CMN_01);
            } else if(cmd == MDOMAKE_AUD_SE_CMN_CONFIRM) {
                HuAudFXPlay(MSM_SE_CMN_03);
            } else if(cmd == MDOMAKE_AUD_SE_CMN_CANCEL) {
                HuAudFXPlay(MSM_SE_CMN_04);
            } else if(cmd == MDOMAKE_AUD_SE_MENU_27) {
                HuAudFXPlay(MSM_SE_MENU_27);
            } else if(cmd == MDOMAKE_AUD_SE_MENU_29) {
                HuAudFXPlay(MSM_SE_MENU_29);
            }
            break;

        case MDOMAKE_AUD_SE_STAR_TALK:
            pan = fn_1_5988(MDMODEL_STAR, MDCAMERA_MAIN);
            if(cmd == MDOMAKE_AUD_SE_STAR_TALK) {
                HuAudFXPlayPan(MSM_SE_GUIDE_53, pan);
            }
            break;

        case MDOMAKE_AUD_SE_ALL_STOP:
            HuAudAllStop();
            break;
    }
}

/* twin: mdmini fn_1_171B4 (mdsel MdSelFXPanGet) */
int fn_1_5988(int mdlNo, int cameraNo)
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
        { "STAGE", MDCAMERA_BG },
        { "CAP_CARD", MDCAMERA_BG },
        { "CAP_VOLLEY", MDCAMERA_BG },
        { "CAP_HOCKEY", MDCAMERA_BG },
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

