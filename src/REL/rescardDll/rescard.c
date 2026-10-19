/*
 * rescardDll -- Bonus Mode's Card Party results (carddll -> omOvlGotoEx(DLL_rescarddll, 1, 0, 0)).
 * Reads GwPlayerConf[4] and GwCardCommon star/ztar counts, ranks the players (with the tiebreak
 * card draw, ResCardDraw*), then ResCardFlowWin: play again -> omOvlGotoEx(carddll) with the
 * counts cleared, or end -> omOvlReturnEx back to mdomakedll. Twins: mdseldll, mdbeachdll
 * (MdPosAdjustMode). See NOTES.md.
 */

#include "REL/rescardDll.h"

#ifdef __MWERKS__
#define HuAudSStreamPauseFadeOut HuAudSStreamPauseFadeOut_hidden
#endif
#include "game/audio.h"
#ifdef __MWERKS__
#undef HuAudSStreamPauseFadeOut
/* ResCardAudExec passes the int stream number unextended: retail's prototype took an int streamNo
 * (HuAudFXPlayPan's s16 pan is extended, so the rest of audio.h is retail's) */
void HuAudSStreamPauseFadeOut(int streamNo, BOOL pause, s32 speed);
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/gamemes.h"
#include "game/disp.h"
#include "msm.h"
#include "math.h"

#include "REL/rescardDll/effect.c"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 90.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 0.0f; /* 0x14 */
/* 0x18 lbl_1_rodata_18 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_20 = -450.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 300.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 100.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 48.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 376.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 1.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 2.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 60.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 0.45f; /* 0x40 */
static const float lbl_1_rodata_44 = 70.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 1800.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 30.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 0.75f; /* 0x50 */
static const float lbl_1_rodata_54 = 0.3f; /* 0x54 */
static const float lbl_1_rodata_58 = 2500.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 16.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 0.5f; /* 0x60 */
static const float lbl_1_rodata_64 = 20.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 25.0f; /* 0x68 */
static const float lbl_1_rodata_6C = -20.0f; /* 0x6C */
static const float lbl_1_rodata_70 = -10.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 10.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 144.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 340.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 3000.0f; /* 0x80 */
static const float lbl_1_rodata_84 = -128.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 180.0f; /* 0x88 */
static const float lbl_1_rodata_8C = -512.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 50.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 1.3f; /* 0x94 */
static const float lbl_1_rodata_98 = 1000.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 360.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 120.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = 1080.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 150.0f; /* 0xA8 */
/* 0xAC lbl_1_rodata_AC (0xC): 0xC3200000 0xC2A00000 0x42A00000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_B8 = 15.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 1.5f; /* 0xBC */
static const float lbl_1_rodata_C0 = 0.125f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 750.0f; /* 0xC4 */
static const double lbl_1_rodata_C8 = 3.141592653589793; /* 0xC8 */
static const double lbl_1_rodata_D0 = 180.0; /* 0xD0 */
static const float lbl_1_rodata_D8 = -90.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = -1.0f; /* 0xDC */
static const double lbl_1_rodata_E0 = 0.5; /* 0xE0 */
static const double lbl_1_rodata_E8 = 3.0; /* 0xE8 */
static const float lbl_1_rodata_F0 = 630.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 32.0f; /* 0xF4 */
static const double lbl_1_rodata_F8 = 100.0; /* 0xF8 */
static const double lbl_1_rodata_100 = 0.10000000149011612; /* 0x100 */
static const float lbl_1_rodata_108 = 4.0f; /* 0x108 */
static const float lbl_1_rodata_10C = 0.008333334f; /* 0x10C */
static const float lbl_1_rodata_110 = 0.11111111f; /* 0x110 */
static const float lbl_1_rodata_114 = 5.0f; /* 0x114 */
static const float lbl_1_rodata_118 = 0.05f; /* 0x118 */
static const float lbl_1_rodata_11C = 0.01f; /* 0x11C */
static const float lbl_1_rodata_120 = 0.1f; /* 0x120 */
static const float lbl_1_rodata_124 = -32.0f; /* 0x124 */
static const float lbl_1_rodata_128 = 0.4f; /* 0x128 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x408 */ SYS sysWork;
/* 0x404 */ SYS *sys;
/* 0x400 */ SYS *sysP;
/* 0x3FC */ static s8 winVoiceFlag[4];
/* 0x3F8 */ s32 lbl_1_bss_3F8;
/* 0x3C8 */ HuVecF lbl_1_bss_3C8[4]; /* ResCardProcPlayerFocus/StageFocus: camera center/hvr from, center/hvr to */
/* 0x3C4 */ float lbl_1_bss_3C4;
/* 0x3C0 */ float lbl_1_bss_3C0;
/* 0x3BC */ float lbl_1_bss_3BC;
/* 0x38C */ HuVecF lbl_1_bss_38C[4];
/* 0x35C */ HuVecF lbl_1_bss_35C[4];
/* 0x29C */ HuVecF lbl_1_bss_29C[8][2]; /* ResCardDrawStarUpdate: lbl_1_data_374[i] in 3D */
/* 0x290 */ float lbl_1_bss_290[3];
/* 0x274 */ RESCARD_EFFECT *lbl_1_bss_274[7]; /* only [0] used: ResCardDrawStarUpdate's ParticleGlowCreate */
/* 0x26C */ float lbl_1_bss_26C[2];
/* 0x264 */ float lbl_1_bss_264[2];
/* 0x258 */ HuVecF lbl_1_bss_258; /* ResCardStarUpdate: Hu3D2Dto3D of lbl_1_data_56C (the star's screen spot) */
/* 0xCC */ RESCARD_WINSTAR lbl_1_bss_CC[33];
/* 0xC8 */ s8 lbl_1_bss_C8;
/* 0x44 */ RESCARD_EFFECT *lbl_1_bss_44[33];
/* 0x40 */ s32 lbl_1_bss_40;
/* 0x34 */ s16 lbl_1_bss_34[6];
/* 0x10 */ extern s32 lbl_1_bss_10; /* defined after the last function (declaration order = .bss order) */
/* 0xC */ extern s16 lbl_1_bss_C; /* defined after the last function (declaration order = .bss order) */
/* 0x8 */ extern s32 lbl_1_bss_8; /* defined after the last function (declaration order = .bss order) */
/* 0x4 */ extern s32 lbl_1_bss_4; /* defined after the last function (declaration order = .bss order) */
/* 0x0 */ extern s32 lbl_1_bss_0; /* defined after the last function (declaration order = .bss order) */

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x140 */ MD_FUNC MdFlowTbl[4] = { ResCardFlowInit, ResCardFlowScore, ResCardFlowDraw, ResCardFlowWin };
/* 0x150 */ MD_PROC MdProcTbl[4] = { ResCardProcReset, ResCardProcDarken, ResCardProcPlayerFocus, ResCardProcStageFocus };

/* 481 insns */
void ObjectSetup(void)
{
    int i;
    sys = &sysWork;
    sysP = sys;
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->unk8 = 0;
    sys->flowTime = 0;
    sys->flowMode = 0;
    sys->ovlCallMode = MD_OVLCALL_GOTO;
    sys->nextDll = DLL_selmenuDLL;
    sys->exitF = FALSE;
    sys->skipWipeF = FALSE;
    sys->score = HuMemDirectMallocNum(HEAP_HEAP, sizeof(RESCARD_SCORE), HU_MEMNUM_OVL);
    if(!sys->score) {
        OSReport("sys->score = NULL...\n");
    }
    ResCardScoreCreate();
    sys->objman = omInitObjMan(512, 8192);
    omGameSysInit(sys->objman);
    sys->obj[RESCARD_OBJ_DEBUGFONT] = omAddObjEx(sys->objman, 100, 0, 0, -1, MdObjDebugFontCreate);
    sys->obj[RESCARD_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[RESCARD_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[RESCARD_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[RESCARD_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[RESCARD_OBJ_PAD] = omAddObjEx(sys->objman, 101, 0, 0, -1, MdObjPadMain);
    sys->obj[RESCARD_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[RESCARD_OBJ_PAD]->data) {
        OSReport("sys->obj[RESCARD_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[RESCARD_OBJ_PAD]->data;
    sys->obj[RESCARD_OBJ_CAMERA] = omAddObjEx(sys->objman, 102, 0, 0, -1, MdObjCameraCreate);
    sys->obj[RESCARD_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[RESCARD_OBJ_CAMERA]->data) {
        OSReport("sys->obj[RESCARD_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[RESCARD_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[RESCARD_OBJ_LIGHT] = omAddObjEx(sys->objman, 103, 0, 0, -1, MdObjLightCreate);
    sys->obj[RESCARD_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[RESCARD_OBJ_LIGHT]->data) {
        OSReport("sys->obj[RESCARD_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[RESCARD_OBJ_LIGHT]->data;
    sys->light->createF = FALSE;
    sys->light->debugFont = sys->debugFont;
    sys->obj[RESCARD_OBJ_MESS] = omAddObjEx(sys->objman, 104, 0, 0, -1, MdObjMessCreate);
    sys->obj[RESCARD_OBJ_MESS]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMESS_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[RESCARD_OBJ_MESS]->data) {
        OSReport("sys->obj[RESCARD_OBJ_MESS]->data = NULL...\n");
    }
    sys->mess = sys->obj[RESCARD_OBJ_MESS]->data;
    sys->mess->createF = FALSE;
    sys->sprite = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSPRITE_WORK), HU_MEMNUM_OVL);
    if(!sys->sprite) {
        OSReport("sys->sprite = NULL...\n");
    }
    sys->model = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMODEL_WORK), HU_MEMNUM_OVL);
    if(!sys->model) {
        OSReport("sys->model = NULL...\n");
    }
    for(i=0; i<16; i++) {
        sys->model->ambMdlId[i] = -1;
    }
    MdMathStdCurveInit();
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(FALSE);
    while(1) {
        if(sys->debugFont->createF == TRUE && sys->camera->createF == TRUE && sys->mess->createF == TRUE) {
            break;
        }
        HuPrcVSleep();
    }
    sys->mainProc = HuPrcChildCreate(MdMain, 105, 12288, 0, sys->objman);
    sys->loadState = MD_LOAD_STATE_NONE;
    sys->loadAsyncStat = 0;
    sys->loadDir = DATA_mdsel; /* retail: mdsel's data dir (copied from the mdsel host) */
    sys->loadProc = HuPrcChildCreate(LoadProc, 110, 12288, 0, sys->objman);
}

/* 57 insns */
void MdMain(void)
{
    MdInit();
    while(!omSysExitReq && !sys->exitF) {
        MdFlowTbl[sys->flowMode]();
        ResCardScoreUpdate();
        ResCardDrawUpdate();
        MdModelUpdateAmb(sys->model);
        ResCardSpotUpdate();
        if(++sys->flowTime > 36000) {
            sys->flowTime = 0;
        }
        HuPrcVSleep();
    }
    MdClose();
}

/* 64 insns */
static void LoadProc(void)
{
    OSTick tick;
    while(1) {
        switch(sys->loadState) {
            case MD_LOAD_STATE_NONE:
                break;

            case MD_LOAD_STATE_LOADING:
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(sys->loadDir);
                while(!HuDataGetAsyncStat(sys->loadAsyncStat)) {
                    HuPrcVSleep();
                }
                OSReport("Load Time:%d\n", OSTicksToMilliseconds(OSGetTick()-tick));
                OSReport("Finished!\n");
                sys->loadState = MD_LOAD_STATE_DONE;
                break;

            case MD_LOAD_STATE_DONE:
                HuPrcEnd();
                break;
        }
        HuPrcVSleep();
    }
}

/* 114 insns */
void MdInit(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdModelCreate(sys->model, sys->camera);
    HuPrcVSleep();
    MdLightSetupModel(sys->light);
    HuPrcVSleep();
    sys->timer = MgTimerCreate(0);
    MgTimerDispOff(sys->timer);
    ResCardSpotCreate();
    HuPrcVSleep();
    HuDataDirClose(DATA_rescard);
    HuPrcVSleep();
    sys->score->unkE0 = 0;
    sys->score->unkE4 = 1;
    sys->starProc = HuPrcChildCreate(ResCardStarUpdate, 106, 12288, 0, sys->objman);
    sys->pinProc = HuPrcChildCreate(ResCardPinUpdate, 107, 12288, 0, sys->objman);
    sys->bgmProc = HuPrcChildCreate(ResCardBGMReset, 108, 4096, 0, sys->objman);
    sys->winVoiceProc = HuPrcChildCreate(ResCardWinVoicePlay, 109, 4096, 0, sys->objman);
    HuPrcVSleep();
}

/* 87 insns */
void MdClose(void)
{
    if(!sys->skipWipeF) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeWait();
    }
    ResCardAudExec(28);
    MdMessKill(sys->mess);
    if(sys->score->gameMesId >= 0) {
        GameMesKill(sys->score->gameMesId);
    }
    MgTimerKill(sys->timer);
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

/* 325 insns */
void ResCardFlowInit(void)
{
    MDSPRITE_WORK *sprite;
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    int i;

    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    MdSpriteDispSet(sprite, 0, FALSE);
    MdSpriteDispSet(sprite, 1, FALSE);
    MdSpriteDispSet(sprite, 2, FALSE);
    MdSpriteDispSet(sprite, 3, FALSE);
    MdSpriteDispSet(sprite, 4, FALSE);
    MdSpriteDispSet(sprite, 5, FALSE);
    MdSpriteDispSet(sprite, 6, FALSE);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_ATTR_DISPOFF);
    for(i=0; i<6; i++) {
        Hu3DModelAttrReset(model->mdlId[MDMODEL_STAGE_BASE+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CUR_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrReset(model->mdlId[MDMODEL_PEDESTAL_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<2; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_POP_STAR+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<22; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_WIN_STAR_00+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<11; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_WIN_ZTAR_00+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD_STAR_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD_ZTAR_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD_SZTAR_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<8; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_DRAW_STAR+i], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_ATTR_DISPOFF);
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_CARDFLASH_1P+i], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(model->mdlId[MDMODEL_RING], HU3D_ATTR_DISPOFF);
    for(i=0; i<4; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_SPOT_0+i], HU3D_ATTR_DISPOFF);
    }
    for(i=0; i<4; i++) {
        model->posP[MDMODEL_PIN_1P+i]->x = -450.0f+(300.0f*i);
        model->posP[MDMODEL_PIN_1P+i]->y = 100.0f;
        model->posP[MDMODEL_PIN_1P+i]->z = 0.0f;
    }
    for(i=0; i<4; i++) {
        model->posP[MDMODEL_PEDESTAL_1P+i]->x = -450.0f+(300.0f*i);
        model->posP[MDMODEL_PEDESTAL_1P+i]->y = 0.0f;
        model->posP[MDMODEL_PEDESTAL_1P+i]->z = 0.0f;
    }
    MdProcTbl[0]();
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    ResCardAudExec(0);
    WipeWait();
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowMode = 1;
}
#ifdef __MWERKS__
#endif


/* 427 insns */
void ResCardFlowScore(void)
{
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    int i;
    int n;

    model = sys->model;
    mess = sys->mess;
    score = sys->score;
    draw = &score->draw;
    switch(sys->subMode) {
        case 0:
            MdMessWinOpen(mess, 1, 48.0f, 376.0f, 480, 64, 1.0f, 0);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 17));
            ResCardAudExec(25);
            sys->score->unkE4 = 2;
            lbl_1_bss_4 = 0;
            sys->subMode = 1;
            break;

        case 1:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                MdProcTbl[0]();
                ResCardAudExec(1);
                MdMessWinKill(mess, 1);
                sys->score->unkE4 = 3;
                sys->subMode = 8;
            }
            break;

        case 8:
            n = MdProcTbl[1]();
            if(n == TRUE) {
                MdProcTbl[0]();
                for(i=0; i<4; i++) {
                    sys->spot[i].mode = 1;
                }
                ResCardAudExec(5);
                sys->subMode = 2;
            }
            break;

        case 2:
            for(i=0; i<4; i++) {
                score->player[i].unk8 = 1;
            }
            sys->subMode = 3;
            break;

        case 3:
            if(score->player[0].unk8 == 3) {
                sys->subMode = 11;
            }
            break;

        case 11:
            if(++lbl_1_bss_4 >= 120) {
                lbl_1_bss_4 = 0;
                sys->subMode = 4;
            }
            break;

        case 12:
            if(++lbl_1_bss_4 >= 30) {
                lbl_1_bss_4 = 0;
                sys->subMode = 4;
            }
            break;

        case 4:
            n = 0;
            lbl_1_bss_3F8 = -1;
            for(i=0; i<4; i++) {
                if(score->rank[i] == score->maxRank) {
                    if(score->rank[i] != 1) {
                        ResCardPinMotStart(i);
                        sys->spot[i].mode = 7;
                    } else {
                        sys->spot[i].mode = 4;
                    }
                    score->player[i].unk8 = 4;
                    if(lbl_1_bss_3F8 == -1) {
                        lbl_1_bss_3F8 = i;
                    }
                    n++;
                }
            }
            if(score->maxRank > 1 && score->winNum > 1) {
                score->maxRank--;
            } else if(score->maxRank > 1 && score->winNum == 1 && n == 0) {
                score->maxRank--;
            }
            if(n != 0) {
                sys->subMode = 5;
            }
            break;

        case 5:
            if(score->player[lbl_1_bss_3F8].unk8 == 7) {
                if(score->maxRank == 1) {
                    sys->subMode = 6;
                } else {
                    sys->subMode = 11;
                }
                if(score->maxRank > 1 && score->winNum == 1) {
                    score->maxRank--;
                }
                if(score->maxRank == 1 && score->winNum == 1 && sys->subMode == 11) {
                    sys->subMode = 12;
                }
            }
            break;

        case 6:
            if(score->winNum > 1) {
                sys->subMode = 0;
                sys->flowMode = 2;
            } else {
                for(i=0; i<4; i++) {
                    if(score->rank[i] == 1) {
                        draw->unkC = i;
                        break;
                    }
                }
                MdMessWinOpen(mess, 1, 48.0f, 376.0f, 480, 64, 1.0f, 0);
                MdMessWinInsertMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 24), score->player[draw->unkC].charNo);
                ResCardAudExec(27);
                sys->score->unkE4 = 2;
                sys->subMode = 7;
            }
            break;

        case 7:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                for(i=0; i<4; i++) {
                    score->player[i].unk8 = 8;
                }
                sys->subMode = 0;
                sys->flowMode = 3;
            }
            break;

        case 9:
        case 10:
            break;
    }
}

/* 137 insns */
void ResCardFlowDraw(void)
{
    MDMESS_WORK *mess;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    int i;
    int n;

    mess = sys->mess;
    score = sys->score;
    draw = &score->draw;
    switch(sys->subMode) {
        case 0:
            sys->subMode = 1;
            break;

        case 1:
            MdMessWinOpen(mess, 1, 48.0f, 376.0f, 480, 64, 1.0f, 0);
            MdMessWinInsertMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 20), score->winNum+MESSNUM(MESS_MPCARD_SYS, 23));
            ResCardAudExec(26);
            sys->score->unkE4 = 2;
            ResCardAudExec(2);
            sys->subMode = 2;
            break;

        case 2:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 21));
                sys->subMode = 3;
            }
            break;

        case 3:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                for(i=0; i<4; i++) {
                    score->player[i].unk8 = 8;
                }
                draw->mode = 1;
                sys->subMode = 4;
            }
            break;

        case 4:
            if(draw->mode == 12) {
                sys->subMode = 0;
                sys->flowMode = 3;
            }
            break;
    }
}
#ifdef __MWERKS__
#endif


/* 322 insns */
void ResCardFlowWin(void)
{
    MDMESS_WORK *mess;
    int i;
    int n;
    RESCARD_SCORE *score;
    MDMODEL_WORK *model;
    RESCARD_DRAW *draw;

    model = sys->model;
    mess = sys->mess;
    score = sys->score;
    draw = &score->draw;
    switch(sys->subMode) {
        case 0:
            MdProcTbl[0]();
            Hu3DMotionSet(model->mdlId[MDMODEL_PIN_1P+draw->unkC], model->motId[MDMODEL_MOT_PIN_0_1P+draw->unkC]);
            Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN_1P+draw->unkC], HU3D_MOTATTR_LOOP);
            Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN_1P+draw->unkC], HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(model->mdlId[MDMODEL_PIN_1P+draw->unkC], 2.0f);
            sys->subMode = 1;
            break;

        case 1:
            n = MdProcTbl[2]();
            if(n == TRUE) {
                MdProcTbl[0]();
                score->gameMesId = GameMesMgWinnerCreate(score->player[draw->unkC].charNo, -1, -1, -1);
                ResCardAudExec(4);
                score->unkEA = 1;
                sys->subMode = 2;
            }
            break;

        case 2:
            if(!GameMesStatGet(score->gameMesId)) {
                sys->subMode = 3;
            }
            break;

        case 3:
            n = MdProcTbl[3]();
            if(n == TRUE) {
                MdProcTbl[0]();
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 18));
                sys->subMode = 4;
            }
            break;

        case 4:
            n = MdMessWinChoiceGet(mess, 1);
            if(n == -1 || n == 1) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 19));
                sys->loadState = MD_LOAD_STATE_LOADING;
                sys->loadDir = DATA_mdomake;
                sys->subMode = 5;
            } else if(n == 0) {
                sys->loadState = MD_LOAD_STATE_LOADING;
                sys->loadDir = DATA_card;
                for(i=0; i<4; i++) {
                    GwCardCommon.starNum[i] = 0;
                    GwCardCommon.ztarNum[i] = 0;
                }
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                ResCardAudExec(3);
                sys->subMode = 8;
            }
            break;

        case 5:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                ResCardAudExec(3);
                sys->subMode = 6;
            }
            break;

        case 6:
            n = WipeCheckEnd();
            if(n == 0) {
                sys->subMode = 7;
            }
            break;

        case 7:
            if(sys->loadState == MD_LOAD_STATE_DONE) {
                sys->ovlCallMode = MD_OVLCALL_RETURN;
                sys->nextDll = DLL_mdomakedll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;

        case 8:
            n = WipeCheckEnd();
            if(n == 0) {
                sys->subMode = 9;
            }
            break;

        case 9:
            if(sys->loadState == MD_LOAD_STATE_DONE) {
                sys->ovlCallMode = MD_OVLCALL_GOTO;
                sys->nextDll = DLL_carddll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;
    }
}

/* 40 insns */
BOOL ResCardProcReset(void)
{
    sys->unk1B8 = 0;
    sys->unk1BC = 0;
    sys->unk1C8 = 0.0f;
    sys->unk1CC = 0.0f;
    sys->unk1D0 = 0.0f;
    sys->unk1D4 = 0.0f;
    return FALSE;
}

/* 51 insns */
BOOL ResCardProcDarken(void)
{
    MDMODEL_WORK *model;

    model = sys->model;
    MdMathOscillate(MDMATH_OSC_90, &sys->unk1C8, &sys->unk1D0, 60.0f);
    MdMathLerp(&model->ambScale, 1.0f, 0.45f, sys->unk1D0);
    if(sys->unk1C8 >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 269 insns */
BOOL ResCardProcPlayerFocus(void)
{
    MDMODEL_WORK *model;
    MDCAMERA_WORK *cameraWork;
    MDCAMERA *camera;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;

    model = sys->model;
    cameraWork = sys->camera;
    camera = &cameraWork->camera[MDCAMERA_MAIN];
    score = sys->score;
    draw = &score->draw;
    if(sys->unk1B8 == 0) {
        lbl_1_bss_3C8[0] = camera->center;
        lbl_1_bss_3C8[1].x = camera->hvr.x;
        lbl_1_bss_3C8[1].y = camera->hvr.y;
        lbl_1_bss_3C8[1].z = camera->hvr.z;
        lbl_1_bss_3C8[2] = *model->posP[MDMODEL_PIN_1P+draw->unkC];
        lbl_1_bss_3C8[2].y += 70.0f;
        lbl_1_bss_3C8[3].x = camera->hvr.x;
        lbl_1_bss_3C8[3].y = camera->hvr.y;
        lbl_1_bss_3C8[3].z = 1800.0f;
        lbl_1_bss_3C0 = lbl_1_bss_3C4 = model->ambScale;
        lbl_1_bss_3BC = 1.0f;
        MdModelRemoveAmb(model, model->mdlId[MDMODEL_PIN_1P+draw->unkC]);
        sys->unk1B8 = 1;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->unk1C8, &sys->unk1D0, 60.0f);
    MdMathLerp(&camera->center.x, lbl_1_bss_3C8[0].x, lbl_1_bss_3C8[2].x, sys->unk1D0);
    MdMathLerp(&camera->center.y, lbl_1_bss_3C8[0].y, lbl_1_bss_3C8[2].y, sys->unk1D0);
    MdMathLerp(&camera->center.z, lbl_1_bss_3C8[0].z, lbl_1_bss_3C8[2].z, sys->unk1D0);
    MdMathLerp(&camera->hvr.x, lbl_1_bss_3C8[1].x, lbl_1_bss_3C8[3].x, sys->unk1D0);
    MdMathLerp(&camera->hvr.y, lbl_1_bss_3C8[1].y, lbl_1_bss_3C8[3].y, sys->unk1D0);
    MdMathLerp(&camera->hvr.z, lbl_1_bss_3C8[1].z, lbl_1_bss_3C8[3].z, sys->unk1D0);
    MdMathOscillate(MDMATH_OSC_90, &sys->unk1CC, &sys->unk1D4, 30.0f);
    MdMathLerp(&lbl_1_bss_3C0, lbl_1_bss_3C4, 0.75f, sys->unk1D4);
    MdMathLerp(&lbl_1_bss_3BC, 1.0f, 0.3f, sys->unk1D4);
    Hu3DModelAmbSet(model->mdlId[MDMODEL_PIN_1P+draw->unkC], lbl_1_bss_3C0, lbl_1_bss_3C0, lbl_1_bss_3C0);
    Hu3DModelTPLvlSet(model->mdlId[MDMODEL_SPOT_0+draw->unkC], lbl_1_bss_3BC);
    if(sys->unk1C8 >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 127 insns */
BOOL ResCardProcStageFocus(void)
{
    MDMODEL_WORK *model;
    MDCAMERA_WORK *cameraWork;
    MDCAMERA *camera;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;

    model = sys->model;
    cameraWork = sys->camera;
    camera = &cameraWork->camera[MDCAMERA_MAIN];
    score = sys->score;
    draw = &score->draw;
    MdMathOscillate(MDMATH_OSC_90, &sys->unk1C8, &sys->unk1D0, 60.0f);
    MdMathLerp(&camera->center.x, lbl_1_bss_3C8[2].x, lbl_1_bss_3C8[0].x, sys->unk1D0);
    MdMathLerp(&camera->center.y, lbl_1_bss_3C8[2].y, lbl_1_bss_3C8[0].y, sys->unk1D0);
    MdMathLerp(&camera->center.z, lbl_1_bss_3C8[2].z, lbl_1_bss_3C8[0].z, sys->unk1D0);
    MdMathLerp(&camera->hvr.x, lbl_1_bss_3C8[3].x, lbl_1_bss_3C8[1].x, sys->unk1D0);
    MdMathLerp(&camera->hvr.y, lbl_1_bss_3C8[3].y, lbl_1_bss_3C8[1].y, sys->unk1D0);
    MdMathLerp(&camera->hvr.z, lbl_1_bss_3C8[3].z, lbl_1_bss_3C8[1].z, sys->unk1D0);
    if(sys->unk1C8 >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 144 insns */
void ResCardScoreCreate(void)
{
    RESCARD_SCORE *score;
    int *state;
    RESCARD_SCORE_PLAYER *player;
    int i;
    int j;

    score = sys->score;
    state = &score->unkE0;
    for(player=score->player, i=0; i<4; i++, player++) {
        player->charNo = GwPlayerConf[i].charNo;
        player->starNum = (int)GwCardCommon.starNum[i];
        player->ztarNum = (int)GwCardCommon.ztarNum[i];
        player->type = GwPlayerConf[i].type;
        if(player->type == 1) {
            player->padNo = -1;
        } else {
            player->padNo = GwPlayerConf[i].padNo;
        }
        player->pedestalF = (int)GwCardCommon.pedestalF[i];
        score->player[i].unk8 = 0;
        player->unk14 = 0;
    }
    for(player=score->player, i=0; i<4; i++, player++) {
        score->rank[i] = 1;
        for(j=0; j<4; j++) {
            if(score->player[j].starNum-score->player[j].ztarNum > player->starNum-player->ztarNum) {
                score->rank[i]++;
            }
        }
    }
    score->gameMesId = -1;
    score->winNum = 0;
    score->maxRank = 1;
    for(i=0; i<4; i++) {
        if(score->rank[i] == 1) {
            score->winNum++;
        }
        if(score->maxRank < score->rank[i]) {
            score->maxRank = score->rank[i];
        }
    }
    ResCardDrawStarCreate();
    state[0] = 0;
    score->unkEA = 0;
}

/* 0x2FC */ s16 lbl_1_data_2FC[12] = { 256, 512, 0, 1023, 512, 257, 255, 512, 258, 1279, 512, 256 };

/* 624 insns */
void ResCardScoreUpdate(void)
{
    MDCAMERA_WORK *camera;
    MDMODEL_WORK *model;
    MDSPRITE_WORK *sprite;
    RESCARD_SCORE *score;
    RESCARD_SCORE_PLAYER *player;
    int i;
    int num;
    HuVecF *pinPos;
    HuVecF *pos;
    HuVecF *rot;
    HuVecF *scale;
    HuVecF *flashPos;
    HuVecF *flashRot;
    HuVecF *flashScale;
    float time;
    HUSPRGRPID grpId[4];

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    for(i=0; i<4; i++) {
        grpId[i] = sprite->grpId[MDSPR_GRP_NUM_0+i];
    }
    for(player=score->player, i=0; i<4; i++, player++) {
        pinPos = model->posP[MDMODEL_PIN_1P+i];
        pos = model->posP[MDMODEL_CARD_SZTAR_1P+i];
        rot = model->rotP[MDMODEL_CARD_SZTAR_1P+i];
        scale = model->scaleP[MDMODEL_CARD_SZTAR_1P+i];
        flashPos = model->posP[MDMODEL_EFF_DICEFLASH_1P+i];
        flashRot = model->rotP[MDMODEL_EFF_DICEFLASH_1P+i];
        flashScale = model->scaleP[MDMODEL_EFF_DICEFLASH_1P+i];
        switch(player->unk8) {
            case 0:
                break;

            case 1:
                lbl_1_bss_35C[i] = *pinPos;
                lbl_1_bss_35C[i].y += 300.0f;
                Hu3D3Dto2D(&lbl_1_bss_35C[i], camera->camera[MDCAMERA_MAIN].bit, &lbl_1_bss_38C[i]);
                lbl_1_bss_38C[i].z = 2500.0f;
                Hu3D2Dto3D(&lbl_1_bss_38C[i], camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_35C[i]);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_CARD_SZTAR_1P+i], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_ATTR_DISPOFF);
                pos->x = lbl_1_bss_35C[i].x;
                pos->y = lbl_1_bss_35C[i].y;
                pos->z = lbl_1_bss_35C[i].z;
                flashPos->x = lbl_1_bss_35C[i].x;
                flashPos->y = lbl_1_bss_35C[i].y;
                flashPos->z = lbl_1_bss_35C[i].z;
                rot->x = 90.0f;
                rot->y = (int)frandmod(360)-180;
                rot->z = 0.0f;
                flashRot->x = 0.0f;
                flashRot->y = 0.0f;
                flashRot->z = 0.0f;
                scale->x = 0.0f;
                scale->y = 0.0f;
                scale->z = 0.0f;
                flashScale->x = 1.0f;
                flashScale->y = 1.0f;
                flashScale->z = 1.0f;
                Hu3DMotionTimeSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], 0.0f);
                Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_MOTATTR_PAUSE);
                MdSpriteDispSet(sprite, 2, FALSE);
                MdSpriteDispSet(sprite, 3, FALSE);
                MdSpriteDispSet(sprite, 4, FALSE);
                MdSpriteDispSet(sprite, 5, FALSE);
                player->unkC = 0.0f;
                player->unk10 = 0.0f;
                player->unk8 = 2;
                break;

            case 2:
                rot->y += 16.0f;
                MdMathAngleClamp(&rot->y);
                MdMathOscillate(MDMATH_OSC_90, &player->unkC, &player->unk10, 60.0f);
                MdMathLerpScale(scale, 0.0f, 0.5f, player->unk10);
                if(player->unkC >= 1.0f) {
                    player->unk8 = 3;
                }
                break;

            case 3:
                rot->y += 16.0f;
                MdMathAngleClamp(&rot->y);
                break;

            case 4:
                rot->y += 16.0f;
                MdMathAngleClamp(&rot->y);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i], HU3D_MOTATTR_PAUSE);
                player->unk8 = 5;
                break;

            case 5:
                rot->y += 16.0f;
                MdMathAngleClamp(&rot->y);
                time = Hu3DMotionTimeGet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i]);
                if(time >= 20.0f) {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD_SZTAR_1P+i], HU3D_ATTR_DISPOFF);
                    player->unk8 = 6;
                }
                break;

            case 6:
                time = Hu3DMotionTimeGet(model->mdlId[MDMODEL_EFF_DICEFLASH_1P+i]);
                if(time >= 25.0f) {
                    num = player->starNum-player->ztarNum;
                    if(num < 0) {
                        HuSprBankSet(grpId[i], 0, 10);
                    }
                    if(num >= 10) {
                        HuSprBankSet(grpId[i], 1, num/10);
                    } else if(num <= -10) {
                        HuSprBankSet(grpId[i], 1, (num*-1)/10);
                    }
                    if(num == 0) {
                        HuSprBankSet(grpId[i], 2, 0);
                    } else if(num > 0) {
                        HuSprBankSet(grpId[i], 2, num%10);
                    } else if(num < 0) {
                        HuSprBankSet(grpId[i], 2, (num*-1)%10);
                    }
                    if(num < 0) {
                        HuSprAttrReset(grpId[i], 0, HUSPR_ATTR_DISPOFF);
                    }
                    if(num >= 10 || num <= -10) {
                        HuSprAttrReset(grpId[i], 1, HUSPR_ATTR_DISPOFF);
                    }
                    HuSprAttrReset(grpId[i], 2, HUSPR_ATTR_DISPOFF);
                    HuSprGrpPosSet(grpId[i], lbl_1_bss_38C[i].x, lbl_1_bss_38C[i].y);
                    if(num <= -10) {
                        HuSprPosSet(grpId[i], 0, -20.0f, 0.0f);
                        HuSprPosSet(grpId[i], 1, 0.0f, 0.0f);
                        HuSprPosSet(grpId[i], 2, 20.0f, 0.0f);
                    } else if(num <= -1) {
                        HuSprPosSet(grpId[i], 0, -10.0f, 0.0f);
                        HuSprPosSet(grpId[i], 2, 10.0f, 0.0f);
                    } else if(num >= 10) {
                        HuSprPosSet(grpId[i], 1, -10.0f, 0.0f);
                        HuSprPosSet(grpId[i], 2, 10.0f, 0.0f);
                    } else {
                        HuSprPosSet(grpId[i], 2, 0.0f, 0.0f);
                    }
                    if(score->rank[i] == 1) {
                        ResCardAudExec(7);
                    } else {
                        ResCardAudExec(6);
                    }
                    player->unk8 = 7;
                }
                break;

            case 7:
                break;

            case 8:
                player->unk8 = 9;
                break;

            case 9:
                MdSpriteDispSet(sprite, MDSPR_GRP_NUM_0+i, FALSE);
                player->unk8 = 10;
                break;

            case 10:
                break;
        }
    }
}

/* 70 insns */
void ResCardDrawStarCreate(void)
{
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    RESCARD_DRAW_STAR *star;
    int i;
    int n;

    n = 0;
    score = sys->score;
    draw = &score->draw;
    draw->mode = 0;
    draw->unk8 = 300;
    ResCardDrawCursorReset(0);
    draw->unk10 = 0;
    draw->unk18 = 0;
    draw->unk1C = 0;
    for(star=draw->star, i=0; i<8; i++, star++) {
        star->type = 1;
        star->mode = 0;
    }
    n = frandmod(8);
    draw->star[n].type = 0;
    n = 0;
    for(star=draw->star, i=0; i<8; i++, star++) {
        if(star->type == 0) {
            star->mdlNo = MDMODEL_DRAW_STAR;
        } else if(star->type == 1) {
            star->mdlNo = MDMODEL_DRAW_ZTAR_0+n;
            n++;
        }
    }
}
#ifdef __MWERKS__
#endif


/* 302 insns */
void ResCardDrawUpdate(void)
{
    MDMESS_WORK *mess;
    MDMODEL_WORK *model;
    MDSPRITE_WORK *sprite;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    int i;
    int n;
    BOOL doneF;

    mess = sys->mess;
    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    draw = &score->draw;
    switch(draw->mode) {
        case 0:
            break;

        case 1:
            for(i=0; i<8; i++) {
                draw->star[i].mode = 1;
            }
            draw->unk14 = 8;
            draw->unk18 = 0;
            draw->unk1C = 0;
            draw->mode = 2;
            break;

        case 2:
            if(draw->unk18 < 8) {
                draw->unk1C--;
                if(draw->unk1C < 0) {
                    draw->star[draw->unk18].mode = 3;
                    draw->unk1C = 8;
                    draw->unk18++;
                    ResCardAudExec(11);
                }
            } else if(draw->star[7].mode == 4) {
                draw->mode = 3;
            }
            break;

        case 3:
            MdMessWinHomeClear(mess, 1);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 22));
            draw->mode = 4;
            break;

        case 4:
            n = MdMessWinCheck(mess, 1);
            if(n != 0) {
                MdMessHelpWinCreate(mess, 0, MESSNUM(MESS_SYSHELP, 18), 144.0f, 340.0f, 0, 32, 0.0f, 0);
                draw->mode = 5;
            }
            break;

        case 5:
            ResCardDrawCursorModeSet(0);
            ResCardDrawTimerPosSet();
            MgTimerParamSet(sys->timer, 300, 0, 0);
            MgTimerDispOn(sys->timer);
            MdMessWinHomeClear(mess, 1);
            MdMessWinInsertMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 23), score->player[score->draw.unkC].charNo);
            draw->mode = 6;
            break;

        case 6:
            n = ResCardDrawCursorModeSet(1);
            if(n == 1) {
                MgTimerModeOnSet(sys->timer, 1);
                draw->unk4 = 0;
                draw->mode = 7;
            }
            break;

        case 7:
            doneF = MgTimerDoneCheck(sys->timer);
            n = ResCardDrawStkDirGet();
            if(n >= 0 && n <= 3) {
                ResCardDrawCursorMove(n);
                ResCardAudExec(8);
                ResCardDrawCursorModeSet(3);
            } else if(doneF == TRUE) {
                ResCardAudExec(10);
                ResCardDrawCursorModeSet(4);
                draw->unk4 = 0;
                draw->mode = 8;
            } else if(n == 4) {
                draw->unk14--;
                ResCardDrawCursorModeSet(4);
                MgTimerModeOffSet(sys->timer);
                if(draw->star[draw->unk10].type == 1) {
                    draw->star[draw->unk10].mode = 5;
                    ResCardAudExec(9);
                    draw->mode = 9;
                } else if(draw->star[draw->unk10].type == 0) {
                    draw->star[draw->unk10].mode = 10;
                    ResCardAudExec(9);
                    draw->mode = 10;
                }
            }
            break;

        case 8:
            if(draw->unk4 == 0) {
                MgTimerDispOff(sys->timer);
                draw->unk4 = 1;
            }
            n = ResCardDrawCursorModeSet(5);
            if(n == 1) {
                ResCardDrawCursorReset(1);
                draw->unk4 = 0;
                draw->mode = 11;
            }
            break;

        case 11:
            if(++draw->unk4 >= 60) {
                draw->mode = 5;
            }
            break;

        case 9:
            if(draw->star[draw->unk10].mode == 9) {
                ResCardDrawCursorReset(1);
                ResCardDrawCursorMove(1);
                ResCardDrawCursorModeSet(3);
                draw->mode = 5;
            }
            break;

        case 10:
            if(draw->star[draw->unk10].mode == 22) {
                draw->mode = 12;
            }
            break;

        case 12:
            break;
    }
    ResCardDrawStarUpdate();
}

/* 139 insns */
int ResCardDrawStkDirGet(void)
{
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    int dir;

    score = sys->score;
    draw = &score->draw;
    if(score->player[draw->unkC].type == 0) {
        dir = score->player[draw->unkC].padNo;
        if(sys->pad->DStkDown[dir] & PAD_BUTTON_LEFT) {
            return 0;
        }
        if(sys->pad->DStkDown[dir] & PAD_BUTTON_RIGHT) {
            return 1;
        }
        if(sys->pad->DStkDown[dir] & PAD_BUTTON_UP) {
            return 2;
        }
        if(sys->pad->DStkDown[dir] & PAD_BUTTON_DOWN) {
            return 3;
        }
        if(HuPadBtnDown[dir] & PAD_BUTTON_A) {
            return 4;
        }
    } else if(score->player[draw->unkC].type == 1) {
        dir = -1;
        if(sys->flowTime%15 == 0) {
            /* retail modifies unk4 twice in one expression (unsequenced); the host spells the intent */
            if(draw->unk14 == 1) {
                draw->unk4 = ++draw->unk4%2;
            } else {
                draw->unk4 = ++draw->unk4%8;
            }
            if(draw->unk4 == 0) {
                dir = 4;
            } else {
                dir = frandmod(4);
            }
        }
        return dir;
    }
    return -1;
}
#ifdef __MWERKS__
#endif

/* 0x374 */ HuVecF lbl_1_data_374[8][2] = { { { 396.0f, 84.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 288.0f, 84.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 180.0f, 84.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 444.0f, 180.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 132.0f, 180.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 396.0f, 276.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 288.0f, 276.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } }, { { 180.0f, 276.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } }; /* the eight card spots (screen); [1] is the fly-in start */

/* 992 insns */
void ResCardDrawStarUpdate(void)
{
    int i;
    int n;
    MDSPRITE_WORK *sprite;
    MDMESS_WORK *mess;
    BOOL endF;
    MDCAMERA_WORK *camera;
    MDMODEL_WORK *model;
    RESCARD_SCORE *score;
    RESCARD_DRAW *draw;
    float time;
    RESCARD_DRAW_STAR *star;
    int j;
    HuVecF *pos;
    HuVecF *rot;
    HuVecF *scale;
    HuVecF *scrPos;
    HuVecF *pos3D;
    HuVecF *pinPos;

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    draw = &score->draw;
    mess = sys->mess;
    time = 0.0f;
    for(star=draw->star, i=0; i<8; i++, star++) {
        pos = model->posP[star->mdlNo];
        rot = model->rotP[star->mdlNo];
        scale = model->scaleP[star->mdlNo];
        scrPos = lbl_1_data_374[i];
        pos3D = lbl_1_bss_29C[i];
        switch(star->mode) {
            case 0:
                break;

            case 1:
                scrPos[0].z = 3000.0f;
                scrPos[1].x = scrPos[0].x;
                scrPos[1].y = scrPos[0].y;
                scrPos[1].z = scrPos[0].z;
                scrPos[1].x = -128.0f;
                for(j=0; j<2; j++) {
                    Hu3D2Dto3D(&scrPos[j], camera->camera[MDCAMERA_FG].bit, &pos3D[j]);
                }
                pos->x = pos3D[1].x;
                pos->y = pos3D[1].y;
                pos->z = pos3D[1].z;
                rot->x = 90.0f;
                rot->y = 180.0f;
                rot->z = 0.0f;
                scale->x = 1.0f;
                scale->y = 1.0f;
                scale->z = 1.0f;
                Hu3DModelAttrReset(model->mdlId[star->mdlNo], HU3D_ATTR_DISPOFF);
                star->time = 0.0f;
                star->t = 0.0f;
                star->mode = 2;
                break;

            case 2:
                break;

            case 3:
                MdMathOscillate(MDMATH_OSC_90, &star->time, &star->t, 30.0f);
                MdMathLerp(&pos->x, pos3D[1].x, pos3D[0].x, star->t);
                MdMathLerp(&pos->y, pos3D[1].y, pos3D[0].y, star->t);
                MdMathLerp(&pos->z, pos3D[1].z, pos3D[0].z, star->t);
                if(star->time >= 1.0f) {
                    star->mode = 4;
                }
                break;

            case 4:
                break;

            case 5:
            case 6:
                star->time = 0.0f;
                star->t = 0.0f;
                if(star->mode == 5) {
                    MgTimerDispOff(sys->timer);
                }
                if(star->mode == 5) {
                    star->mode = 7;
                } else if(star->mode == 6) {
                    star->mode = 8;
                }
                break;

            case 7:
                j = ResCardDrawCursorModeSet(5);
                MdMathOscillate(MDMATH_OSC_0, &star->time, &star->t, 60.0f);
                MdMathLerp(&rot->y, 180.0f, 0.0f, star->t);
                if(star->time >= 1.0f) {
                    star->time = 0.0f;
                    star->t = 0.0f;
                    ResCardAudExec(13);
                    star->mode = 8;
                }
                break;

            case 8:
                MdMathOscillate(MDMATH_OSC_90_REV, &star->time, &star->t, 30.0f);
                MdMathLerp(&rot->z, 0.0f, -512.0f, star->t);
                MdMathLerpScale(scale, 1.0f, 0.0f, star->t);
                if(star->time >= 1.0f) {
                    star->mode = 9;
                }
                break;

            case 9:
                break;

            case 10:
                MgTimerDispOff(sys->timer);
                star->time = 0.0f;
                star->t = 0.0f;
                lbl_1_bss_8 = 0;
                lbl_1_bss_290[0] = 0.0f;
                lbl_1_bss_290[1] = 0.0f;
                lbl_1_bss_290[2] = 0.0f;
                score->player[score->draw.unkC].starNum++;
                star->mode = 11;
                break;

            case 11:
                j = ResCardDrawCursorModeSet(5);
                MdMathOscillate(MDMATH_OSC_0, &star->time, &star->t, 60.0f);
                MdMathLerp(&rot->y, 180.0f, 0.0f, star->t);
                if(star->time >= 1.0f) {
                    star->time = 0.0f;
                    star->t = 0.0f;
                    MdMessWinClose(mess, 0);
                    star->mode = 12;
                }
                break;

            case 12:
                for(j=0; j<8; j++) {
                    if(draw->star[j].mode == 4) {
                        draw->star[j].mode = 6;
                    }
                }
                for(j=0; j<4; j++) {
                    if(score->rank[j] == 1 && j != draw->unkC) {
                        ResCardPinMotStart(j);
                        sys->spot[j].mode = 10;
                    }
                }
                model->posP[MDMODEL_EFF_STARFLASH]->x = pos->x;
                model->posP[MDMODEL_EFF_STARFLASH]->y = pos->y;
                model->posP[MDMODEL_EFF_STARFLASH]->z = 50.0f+pos->z;
                model->rotP[MDMODEL_EFF_STARFLASH]->x = 0.0f;
                model->rotP[MDMODEL_EFF_STARFLASH]->y = 0.0f;
                model->rotP[MDMODEL_EFF_STARFLASH]->z = 0.0f;
                model->scaleP[MDMODEL_EFF_STARFLASH]->x = 2.0f;
                model->scaleP[MDMODEL_EFF_STARFLASH]->y = 2.0f;
                model->scaleP[MDMODEL_EFF_STARFLASH]->z = 2.0f;
                Hu3DMotionSpeedSet(model->mdlId[MDMODEL_EFF_STARFLASH], 1.0f);
                Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_ATTR_DISPOFF);
                ResCardAudExec(14);
                star->mode = 13;
                break;

            case 13:
                time = Hu3DMotionTimeGet(model->mdlId[MDMODEL_EFF_STARFLASH]);
                if(time >= 20.0f) {
                    model->posP[MDMODEL_POP_STAR]->x = pos->x;
                    model->posP[MDMODEL_POP_STAR]->y = pos->y;
                    model->posP[MDMODEL_POP_STAR]->z = pos->z;
                    lbl_1_bss_290[0] = model->posP[MDMODEL_POP_STAR]->x;
                    lbl_1_bss_290[1] = model->posP[MDMODEL_POP_STAR]->y;
                    lbl_1_bss_290[2] = model->posP[MDMODEL_POP_STAR]->z;
                    model->rotP[MDMODEL_POP_STAR]->x = 0.0f;
                    model->rotP[MDMODEL_POP_STAR]->y = 0.0f;
                    model->rotP[MDMODEL_POP_STAR]->z = 0.0f;
                    model->scaleP[MDMODEL_POP_STAR]->x = 1.3f;
                    model->scaleP[MDMODEL_POP_STAR]->y = 1.3f;
                    model->scaleP[MDMODEL_POP_STAR]->z = 1.3f;
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_POP_STAR], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_POP_STAR], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_POP_STAR], HU3D_ATTR_DISPOFF);
                    ResCardAudExec(15);
                    star->mode = 14;
                }
                break;

            case 14:
                if(++lbl_1_bss_8 >= 60) {
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_MOTATTR_LOOP);
                    star->mode = 16;
                }
                break;

            case 16:
                endF = Hu3DMotionEndCheck(model->mdlId[MDMODEL_EFF_STARFLASH]);
                if(endF == TRUE) {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_EFF_STARFLASH], HU3D_ATTR_DISPOFF);
                    star->mode = 15;
                }
                break;

            case 15:
                MdMathOscillate(MDMATH_OSC_90_REV, &star->time, &star->t, 30.0f);
                MdMathLerp(&rot->z, 0.0f, -512.0f, star->t);
                MdMathLerpScale(scale, 1.0f, 0.0f, star->t);
                if(star->time >= 1.0f) {
                    MdMessWinHomeClear(mess, 1);
                    MdMessWinInsertMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 24), score->player[score->draw.unkC].charNo);
                    ResCardAudExec(27);
                    star->time = 0.0f;
                    star->t = 0.0f;
                    star->mode = 23;
                }
                break;

            case 23:
                if((n = MdMessWinCheck(mess, 1)) != 0) {
                    star->mode = 17;
                }
                break;

            case 17:
                MdMathOscillate(MDMATH_OSC_90_REV, &star->time, &star->t, 30.0f);
                MdMathLerp(&model->posP[MDMODEL_POP_STAR]->y, lbl_1_bss_290[1], 1000.0f, star->t);
                MdMathLerp(&model->rotP[MDMODEL_POP_STAR]->y, 0.0f, 360.0f, star->t);
                if(star->time >= 1.0f) {
                    star->time = 0.0f;
                    star->t = 0.0f;
                    Hu3DModelLayerSet(model->mdlId[MDMODEL_POP_STAR], 2);
                    Hu3DModelCameraSet(model->mdlId[MDMODEL_POP_STAR], camera->camera[MDCAMERA_MAIN].bit);
                    pinPos = model->posP[MDMODEL_PIN_1P+draw->unkC];
                    lbl_1_bss_290[0] = pinPos->x;
                    lbl_1_bss_290[1] = pinPos->y;
                    lbl_1_bss_290[2] = pinPos->z;
                    model->posP[MDMODEL_POP_STAR]->x = pinPos->x;
                    model->posP[MDMODEL_POP_STAR]->y = 1000.0f;
                    model->posP[MDMODEL_POP_STAR]->z = pinPos->z;
                    model->rotP[MDMODEL_POP_STAR]->y = 0.0f;
                    model->scaleP[MDMODEL_POP_STAR]->x = 1.0f;
                    model->scaleP[MDMODEL_POP_STAR]->y = 1.0f;
                    model->scaleP[MDMODEL_POP_STAR]->z = 1.0f;
                    lbl_1_bss_274[0] = ParticleGlowCreate(sprite->animP[4], 1, camera->camera[MDCAMERA_MAIN].bit);
                    star->mode = 18;
                }
                break;

            case 18:
                MdMathOscillate(MDMATH_OSC_90, &star->time, &star->t, 30.0f);
                MdMathLerp(&model->posP[MDMODEL_POP_STAR]->y, 1000.0f, 300.0f+lbl_1_bss_290[1], star->t);
                if(star->time >= 1.0f) {
                    star->time = 0.0f;
                    star->t = 0.0f;
                    star->mode = 19;
                }
                break;

            case 19:
                MdMathOscillate(MDMATH_OSC_90_REV, &star->time, &star->t, 120.0f);
                MdMathLerp(&model->rotP[MDMODEL_POP_STAR]->y, 0.0f, 1080.0f, star->t);
                ParticleGlowPosSet(lbl_1_bss_274[0], model->posP[MDMODEL_POP_STAR]);
                if(star->time >= 1.0f) {
                    star->time = 0.0f;
                    star->t = 0.0f;
                    ResCardAudExec(1);
                    star->mode = 20;
                }
                break;

            case 20:
                MdMathOscillate(MDMATH_OSC_90_REV, &star->time, &star->t, 30.0f);
                MdMathLerp(&model->posP[MDMODEL_POP_STAR]->y, 300.0f+lbl_1_bss_290[1], 150.0f+lbl_1_bss_290[1], star->t);
                MdMathLerpScale(model->scaleP[MDMODEL_POP_STAR], 1.0f, 0.0f, star->t);
                ParticleGlowPosSet(lbl_1_bss_274[0], model->posP[MDMODEL_POP_STAR]);
                if(star->time >= 1.0f) {
                    ResCardAudExec(16);
                    star->time = 0.0f;
                    star->t = 0.0f;
                    star->mode = 22;
                }
                break;

            case 21:
                if((n = MdMessWinCheck(mess, 1)) != 0) {
                    star->mode = 22;
                }
                break;

            case 22:
                break;
        }
    }
}

/* 271 insns */
int ResCardDrawCursorModeSet(int mode)
{
    int i; //r31
    RESCARD_DRAW *draw; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *pos; //r28
    HuVecF *starPos; //r27
    HuVecF *scale; //r26
    HuVecF *rot; //r25
    RESCARD_SCORE *score; //r24
    MDSPRITE_WORK *sprite; //sp+0xC

    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    draw = &score->draw;
    {
    HuVecF ofs = { -160.0f, -80.0f, 80.0f };
    pos = model->posP[MDMODEL_CUR_1P+draw->unkC];
    rot = model->rotP[MDMODEL_CUR_1P+draw->unkC];
    scale = model->scaleP[MDMODEL_CUR_1P+draw->unkC];
    starPos = model->posP[draw->star[draw->unk10].mdlNo];
    switch(mode) {
        case 0:
            pos->x = starPos->x+ofs.x;
            pos->y = starPos->y+ofs.y;
            pos->z = starPos->z+ofs.z;
            rot->x = 90.0f;
            rot->y = 0.0f;
            rot->z = 0.0f;
            scale->x = 0.0f;
            scale->y = 0.0f;
            scale->z = 0.0f;
            for(i=0; i<4; i++) {
                if(i == draw->unkC) {
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_CUR_1P+draw->unkC], HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_CUR_1P+i], HU3D_ATTR_DISPOFF);
                }
            }
            for(i=0; i<2; i++) {
                lbl_1_bss_26C[i] = 0.0f;
                lbl_1_bss_264[i] = 0.0f;
            }
            break;
        case 1:
            MdMathOscillate(MDMATH_OSC_90, &lbl_1_bss_26C[0], &lbl_1_bss_264[0], 15.0f);
            MdMathOscillate(MDMATH_OSC_180, &lbl_1_bss_26C[1], &lbl_1_bss_264[1], 15.0f);
            MdMathLerpScaleOfs(scale, 0.0f, 1.0f, lbl_1_bss_264[0], 1.5f*lbl_1_bss_264[1]);
            if(lbl_1_bss_26C[0] >= 1.0f) {
                return TRUE;
            }
            break;
        case 3:
            pos->x = starPos->x+ofs.x;
            pos->y = starPos->y+ofs.y;
            pos->z = starPos->z+ofs.z;
            break;
        case 4:
            for(i=0; i<2; i++) {
                lbl_1_bss_26C[i] = 0.0f;
                lbl_1_bss_264[i] = 0.0f;
            }
            break;
        case 5:
            MdMathOscillate(MDMATH_OSC_90_REV, &lbl_1_bss_26C[0], &lbl_1_bss_264[0], 15.0f);
            MdMathLerpScale(scale, 1.0f, 0.0f, lbl_1_bss_264[0]);
            if(lbl_1_bss_26C[0] >= 1.0f) {
                Hu3DModelAttrSet(model->mdlId[MDMODEL_CUR_1P+draw->unkC], HU3D_ATTR_DISPOFF);
                return TRUE;
            }
            break;
    }
    }
    return FALSE;
}

/* 96 insns */
void ResCardDrawTimerPosSet(void)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    RESCARD_DRAW *draw; //r29
    RESCARD_SCORE *score; //r28
    HuVecF *pos; //r27

    HuVecF pos2D; //sp+0x18
    HuVecF timerPos; //sp+0xC
    MDSPRITE_WORK *sprite; //sp+0x8

    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    draw = &score->draw;
    timerPos.x = 0.0f;
    timerPos.y = 0.0f;
    timerPos.z = 0.0f;
    for(i=0; i<8; i++) {
        pos = model->posP[draw->star[i].mdlNo];
        Hu3D3Dto2D(pos, sys->camera->camera[MDCAMERA_FG].bit, &pos2D);
        timerPos.x += pos2D.x;
        timerPos.y += pos2D.y;
    }
    if(0.0f != timerPos.x) {
        timerPos.x /= 8.0f;
    }
    if(0.0f != timerPos.y) {
        timerPos.y /= 8.0f;
    }
    MgTimerPosSet(sys->timer, timerPos.x, timerPos.y);
}

/* 38 insns */
void ResCardDrawCursorReset(int no)
{
    int playerNo = 3; //r31
    RESCARD_DRAW *draw; //r30
    int i; //r29
    RESCARD_SCORE *score; //r28

    score = sys->score;
    draw = &score->draw;
    if(no == 1) {
        playerNo = draw->unkC;
    }
    for(i=0; i<3; i++) {
        playerNo++;
        playerNo %= 4;
        if(score->rank[playerNo] == 1) {
            draw->unkC = playerNo;
            break;
        }
    }
}

/* 0x494 */ s8 lbl_1_data_494[8][2] = { { 2, 4 }, { 3, 1 }, { 5, 2 }, { 1, 6 }, { 8, 3 }, { 4, 7 }, { 6, 8 }, { 7, 5 } };
/* 0x4A4 */ s8 lbl_1_data_4A4[8][2][8] = { 6, 4, 7, 8, 5, 2, 3, 1, 4, 6, 7, 8, 5, 2, 3, 1, 7, 6, 8, 4, 5, 1, 3, 2, 7, 8, 6, 5, 4, 3, 1, 2, 8, 5, 7, 6, 4, 2, 1, 3, 5, 8, 7, 6, 4, 2, 1, 3, 1, 2, 3, 6, 7, 8, 5, 4, 6, 7, 8, 1, 2, 3, 5, 4, 3, 2, 1, 8, 7, 6, 4, 5, 8, 7, 6, 3, 2, 1, 4, 5, 4, 1, 2, 3, 5, 7, 8, 6, 1, 4, 2, 3, 5, 7, 8, 6, 2, 3, 1, 5, 4, 8, 6, 7, 2, 1, 3, 4, 5, 6, 8, 7, 5, 3, 2, 1, 4, 7, 6, 8, 3, 5, 2, 1, 4, 7, 6, 8 };

/* 86 insns */
void ResCardDrawCursorMove(int dir)
{
    RESCARD_DRAW *draw; //r31
    int no; //r30
    int i; //r29
    RESCARD_SCORE *score; //r28

    score = sys->score;
    draw = &score->draw;
    if(dir == 0 || dir == 1) {
        no = draw->unk10;
        for(i=0; i<8; i++) {
            no = lbl_1_data_494[no][dir]-1;
            if(draw->star[no].mode != 9) {
                draw->unk10 = no;
                break;
            }
        }
    } else if(dir == 2 || dir == 3) {
        no = 0;
        for(i=0; i<8; i++) {
            if(draw->star[lbl_1_data_4A4[draw->unk10][dir-2][no]-1].mode != 9) {
                draw->unk10 = lbl_1_data_4A4[draw->unk10][dir-2][no]-1;
                break;
            }
            no++;
        }
    }
}

/* 118 insns */
void ResCardSpotCreate(void)
{
    RESCARD_SPOT *spot; //r31
    int i; //r30
    RESCARD_SPOT *spotBase; //r29
    MDMODEL_WORK *model; //sp+0x8

    model = sys->model;
    spotBase = sys->spot;
    for(spot=spotBase, i=0; i<4; i++, spot++) {
        spot->mode = 0;
        spot->pos.x = -450.0f+(300.0f*i);
        spot->pos.y = 750.0f;
        spot->pos.z = 50.0f;
        spot->unk1C.x = spot->pos.x;
        spot->unk1C.y = 0.0f;
        spot->unk1C.z = 0.0f;
        spot->unk10 = spot->unk1C;
        spot->unk28 = 1.0f;
        spot->unk2C = 0.0f;
        spot->unk30 = 0.0f;
        spot->unk34 = 0.0f;
        spot->unk38 = (int)frandmod(360);
        spot->unk3C = 0.0f;
        spot->unk40 = (int)frandmod(360);
    }
    ResCardSpotScaleCalc();
}

/* 213 insns */
void ResCardSpotScaleCalc(void)
{
    RESCARD_SPOT *spot; //r31
    int i; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *scale; //r28
    HuVecF *pos; //r27
    HuVecF *rot; //r26
    RESCARD_SPOT *spotBase; //r25
    Mtx *mtx; //r24
    float dist; //f28
    float scaleZ; //f27

    HuVecF rotVec; //sp+0x18
    HuVecF dir; //sp+0xC

    model = sys->model;
    spotBase = sys->spot;
    for(spot=spotBase, i=0; i<4; i++, spot++) {
        pos = model->posP[MDMODEL_SPOT_0+i];
        rot = model->rotP[MDMODEL_SPOT_0+i];
        scale = model->scaleP[MDMODEL_SPOT_0+i];
        spot->unk10.x = spot->unk1C.x+(spot->unk34*cos(M_PI*spot->unk3C/180.0));
        spot->unk10.z = spot->unk1C.z+(spot->unk34*sin(M_PI*spot->unk3C/180.0));
        if(spot->unk10.x == spot->pos.x && spot->unk10.z == spot->pos.z) {
            spot->unk10.z -= 1.0f;
        }
        *pos = spot->pos;
        mtx = MdMathMatrixDir(&spot->pos, &spot->unk10);
        Hu3DMtxRotGet(*mtx, &rotVec);
        if(-90.0f == rotVec.y) {
            rotVec.x *= -1.0f;
        }
        *rot = rotVec;
        dir.x = spot->pos.x-spot->unk10.x;
        dir.y = spot->pos.y-spot->unk10.y;
        dir.z = spot->pos.z-spot->unk10.z;
        dist = HuMagVecF(&dir);
        scaleZ = dist/630.0f;
        scale->x = spot->unk28;
        scale->y = spot->unk28;
        scale->z = scaleZ;
    }
}

/* 0x524 */ float lbl_1_data_524[4] = { 2.5f, 400.0f, 0.3f, 180.0f };

/* 115 insns */
void ResCardSpotAngleUpdate(int spotNo, int mode)
{
    RESCARD_SPOT *spot; //r31
    RESCARD_SPOT *spotBase; //r30

    spotBase = sys->spot;
    spot = &spotBase[spotNo];
    if(mode == 0) {
        spot->unk38 += lbl_1_data_524[0];
        MdMathAngleClamp(&spot->unk38);
        spot->unk34 = lbl_1_data_524[1]*sin(M_PI*spot->unk38/180.0);
        spot->unk40 += lbl_1_data_524[2];
        MdMathAngleClamp(&spot->unk40);
        spot->unk3C = lbl_1_data_524[3]*sin(M_PI*spot->unk40/180.0);
        MdMathAngleClamp(&spot->unk3C);
    } else if(mode == 1) {
        MdMathAngleClamp(&spot->unk38);
        spot->unk34 = lbl_1_data_524[1]*sin(M_PI*spot->unk38/180.0);
        MdMathAngleClamp(&spot->unk40);
        spot->unk3C = lbl_1_data_524[3]*sin(M_PI*spot->unk40/180.0);
        MdMathAngleClamp(&spot->unk3C);
    }
}

/* 0x534 */ u32 lbl_1_data_534[1] = { HU_DATANUM_NONE };
/* 2502 insns */
void ResCardSpotUpdate(void)
{
    RESCARD_SPOT *spot; //r31
    int i; //sp+0x1C8
    MDMODEL_WORK *model; //sp+0x1C4
    RESCARD_SPOT *spotBase; //sp+0x1C0

    model = sys->model;
    spotBase = sys->spot;
    for(spot=spotBase, i=0; i<4; i++, spot++) {
        switch(spot->mode) {
            case 0:
                break;
            case 1:
                Hu3DModelAttrReset(model->mdlId[MDMODEL_SPOT_0+i], HU3D_ATTR_DISPOFF);
                spot->unk2C = 0.0f;
                spot->unk30 = 0.0f;
                spot->unk28 = 0.0f;
                spot->mode = 2;
                ResCardSpotScaleCalc();
                break;
            case 2:
                MdMathOscillate(MDMATH_OSC_90_REV, &spot->unk2C, &spot->unk30, 30.0f);
                MdMathLerp(&spot->unk28, 0.0f, 1.0f, spot->unk30);
                if(spot->unk2C >= 1.0f) {
                    spot->mode = 3;
                }
                ResCardSpotAngleUpdate(i, 0);
                ResCardSpotScaleCalc();
                break;
            case 3:
                ResCardSpotAngleUpdate(i, 0);
                ResCardSpotScaleCalc();
                break;
            case 4:
                spot->unk2C = 0.0f;
                spot->unk30 = 0.0f;
                spot->unk48 = spot->unk38;
                spot->unk4C = spot->unk40;
                spot->mode = 5;
                ResCardSpotAngleUpdate(i, 1);
                ResCardSpotScaleCalc();
                break;
            case 5:
                MdMathOscillate(MDMATH_OSC_90, &spot->unk2C, &spot->unk30, 120.0f);
                MdMathLerp(&spot->unk38, spot->unk48, 0.0f, spot->unk30);
                if(spot->unk2C >= 1.0f) {
                    spot->mode = 6;
                }
                ResCardSpotAngleUpdate(i, 1);
                ResCardSpotScaleCalc();
                break;
            case 6:
                break;
            case 7:
                spot->unk2C = 0.0f;
                spot->unk30 = 0.0f;
                spot->unk44 = spot->unk28;
                spot->mode = 8;
                ResCardSpotScaleCalc();
                break;
            case 8:
                MdMathOscillate(MDMATH_OSC_90_REV, &spot->unk2C, &spot->unk30, 30.0f);
                MdMathLerp(&spot->unk28, spot->unk44, 0.0f, spot->unk30);
                if(spot->unk2C >= 1.0f) {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_SPOT_0+i], HU3D_ATTR_DISPOFF);
                    spot->mode = 9;
                }
                ResCardSpotAngleUpdate(i, 0);
                ResCardSpotScaleCalc();
                break;
            case 9:
                break;
            case 10:
                spot->unk2C = 0.0f;
                spot->unk30 = 0.0f;
                spot->unk44 = spot->unk28;
                spot->mode = 11;
                ResCardSpotScaleCalc();
                break;
            case 11:
                MdMathOscillate(MDMATH_OSC_90_REV, &spot->unk2C, &spot->unk30, 30.0f);
                MdMathLerp(&spot->unk28, spot->unk44, 0.0f, spot->unk30);
                if(spot->unk2C >= 1.0f) {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_SPOT_0+i], HU3D_ATTR_DISPOFF);
                    spot->mode = 12;
                }
                ResCardSpotAngleUpdate(i, 1);
                ResCardSpotScaleCalc();
                break;
            case 12:
                break;
        }
    }
}

/* 0x56C */ HuVecF lbl_1_data_56C = { 64.0f, 308.0f, 1280.0f };

/* 120 insns */
void ResCardStarUpdate(void)
{
    MDMODEL_WORK *model; //r31
    int *state; //r30
    MDCAMERA_WORK *camera; //r29
    HuVecF *pos; //r28
    MDMESS_WORK *mess; //r27
    HuVecF *rot; //r26
    HuVecF *scale; //r25

    model = sys->model;
    camera = sys->camera;
    mess = sys->mess;
    state = &sys->score->unkE0;
    pos = model->posP[MDMODEL_STAR];
    rot = model->rotP[MDMODEL_STAR];
    scale = model->scaleP[MDMODEL_STAR];
    while(TRUE) {
        model = sys->model;
        camera = sys->camera;
        mess = sys->mess;
        state = &sys->score->unkE0;
        pos = model->posP[MDMODEL_STAR];
        rot = model->rotP[MDMODEL_STAR];
        scale = model->scaleP[MDMODEL_STAR];
        switch(state[0]) {
            case 0:
                Hu3D2Dto3D(&lbl_1_data_56C, camera->camera[MDCAMERA_FG].bit, &lbl_1_bss_258);
                *pos = lbl_1_bss_258;
                ResCardBillboardUpdate(MDMODEL_STAR, MDCAMERA_FG);
                break;
        }
        switch(state[1]) {
            case 0:
                break;
            case 1:
                Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_0]);
                state[1] = 0;
                break;
            case 2:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_0+1], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state[1] = 0;
                break;
            case 3:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR_0], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state[1] = 0;
                break;
        }
        HuPrcVSleep();
    }
}

/* 507 insns */
void ResCardPinUpdate(void)
{
    RESCARD_WINSTAR *star; //r31
    int i; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *pos; //r28
    HuVecF *scale; //r27
    HuVecF *pinPos; //r26
    RESCARD_SCORE *score; //r25
    RESCARD_SCORE_PLAYER *player; //r24
    RESCARD_DRAW *draw; //r23
    HuVecF *rot; //r22
    MDCAMERA_WORK *camera; //r19
    MDSPRITE_WORK *sprite; //r18
    float radius; //f31
    int motTime; //sp+0x18

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    score = sys->score;
    draw = &score->draw;
    radius = 300.0f;
    while(TRUE) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        score = sys->score;
        draw = &score->draw;
        radius = 300.0f;
        player = &score->player[draw->unkC];
        switch(score->unkEA) {
            case 0:
                break;
            case 1:
                for(i=0; i<33; i++) {
                    lbl_1_bss_44[i] = NULL;
                }
                pinPos = model->posP[MDMODEL_PIN_1P+draw->unkC];
                lbl_1_bss_C8 = 0;
                for(star=lbl_1_bss_CC, i=0; i<33; i++, star++) {
                    if(i < player->starNum) {
                        lbl_1_bss_44[lbl_1_bss_C8] = ParticleGlowCreate(sprite->animP[4], 0, camera->camera[MDCAMERA_MAIN].bit);
                        star->mdlNo = MDMODEL_WIN_STAR_00+i;
                        lbl_1_bss_C8++;
                    } else if(i < player->starNum+player->ztarNum) {
                        star->mdlNo = MDMODEL_WIN_ZTAR_00+(i-player->starNum);
                        lbl_1_bss_C8++;
                    } else {
                        star->mdlNo = -1;
                    }
                }
                for(star=lbl_1_bss_CC, i=0; i<lbl_1_bss_C8; i++, star++) {
                    if(star->mdlNo != -1) {
                        star->unk0 = 0;
                        star->unk1 = 0;
                        star->angle = (360.0f/lbl_1_bss_C8)*i;
                        MdMathAngleClamp(&star->angle);
                        pos = model->posP[star->mdlNo];
                        rot = model->rotP[star->mdlNo];
                        scale = model->scaleP[star->mdlNo];
                        pos->x = pinPos->x+(radius*cos(M_PI*star->angle/180.0));
                        pos->y = 100.0+(pinPos->y+(0.1f*(100.0*sin(M_PI*(4.0f*star->angle)/180.0))));
                        pos->z = pinPos->z+(radius*sin(M_PI*star->angle/180.0));
                        rot->x = 0.0f;
                        rot->y = 0.0f;
                        rot->z = 0.0f;
                        star->scale = 0.0f;
                        scale->x = star->scale;
                        scale->y = star->scale;
                        scale->z = star->scale;
                        motTime = frandmod(60);
                        Hu3DMotionTimeSet(model->mdlId[MDMODEL_WIN_STAR_00], motTime);
                        Hu3DModelAttrReset(model->mdlId[star->mdlNo], HU3D_ATTR_DISPOFF);
                    }
                }
                score->unkEA = 2;
                break;
            case 2:
                pinPos = model->posP[MDMODEL_PIN_1P+draw->unkC];
                for(star=lbl_1_bss_CC, i=0; i<lbl_1_bss_C8; i++, star++) {
                    /* retail tests entry 0's mdlNo for every entry (harmless: entries below
                       lbl_1_bss_C8 are all in use) */
                    if(lbl_1_bss_CC->mdlNo != -1) {
                        pos = model->posP[star->mdlNo];
                        rot = model->rotP[star->mdlNo];
                        scale = model->scaleP[star->mdlNo];
                        star->angle -= 2.0f;
                        pos->x = pinPos->x+(radius*cos(M_PI*star->angle/180.0));
                        pos->y = 100.0+(pinPos->y+(0.1f*(100.0*sin(M_PI*(4.0f*star->angle)/180.0))));
                        pos->z = pinPos->z+(radius*sin(M_PI*star->angle/180.0));
                        if(star->scale < 0.5f) {
                            star->scale += 1.0f/120.0f;
                            if(star->scale >= 0.5f) {
                                star->scale = 0.5f;
                            }
                            scale->x = star->scale;
                            scale->y = star->scale;
                            scale->z = star->scale;
                        }
                        if(lbl_1_bss_44[i] != 0) {
                            ParticleGlowPosSet(lbl_1_bss_44[i], pos);
                        }
                    }
                }
                break;
        }
        HuPrcVSleep();
    }
}

/* 73 insns */
void ResCardPinMotStart(int playerNo)
{
    MDMODEL_WORK *model; //r31
    int motNo; //r29
    int speed; //r28

    model = sys->model;
    motNo = frandmod(2);
    /* retail: integer division, so speed is always 0 (1..49 / 100) and every pin plays at 0.5 */
    speed = ((int)frandmod(49)+1)/100;
    Hu3DMotionSet(model->mdlId[MDMODEL_PIN_1P+playerNo], model->motId[MDMODEL_MOT_PIN_1_1P+(motNo*4)+playerNo]);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN_1P+playerNo], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN_1P+playerNo], HU3D_MOTATTR_PAUSE);
    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_PIN_1P+playerNo], 0.5f+speed);
    ResCardAudExec(playerNo+17);
}

/* 60 insns */
void ResCardBillboardUpdate(int mdlNo, int cameraNo)
{
    MDCAMERA *camera; //r31
    HuVecF *pos; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *rot; //r28
    MDCAMERA_WORK *cameraWork; //r27

    float rotY;
    HuVecF dir;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[cameraNo];
    model = sys->model;
    pos = model->posP[mdlNo];
    rot = model->rotP[mdlNo];
    dir.x = camera->pos.x-pos->x;
    dir.y = camera->pos.y-pos->y;
    dir.z = camera->pos.z-pos->z;
    rotY = HuAtan(dir.x, dir.z);
    rot->y = rotY;
}

/* 225 insns */
void ResCardAudExec(int cmd)
{
    MDMODEL_WORK *model; //r30
    MDCAMERA_WORK *camera; //r29
    int pan; //r28
    int fxPan; //r27

    HuVecF pos; //sp+0x14
    HuVecF pos2D; //sp+0x8

    model = sys->model;
    camera = sys->camera;
    switch(cmd) {
        case 0:
            lbl_1_bss_40 = HuAudBGMPlay(21);
            break;
        case 1:
        case 2:
            if(cmd == 1) {
                HuAudSStreamPauseFadeOut(lbl_1_bss_40, TRUE, 1000);
            } else if(cmd == 2) {
                HuAudSStreamPauseFadeOut(lbl_1_bss_40, FALSE, 1000);
            }
            break;
        case 3:
            HuAudSStreamFadeOut(lbl_1_bss_40, 1000);
            break;
        case 4:
            lbl_1_bss_0 = 1;
            HuAudJinglePlay(129);
            break;
        case 5:
        case 6:
        case 7:
            if(cmd == 5) {
                lbl_1_bss_C = 0;
                HuAudFXPlay(31);
            } else if(cmd == 6) {
                HuAudFXPlay(33);
            } else if(cmd == 7) {
                if(lbl_1_bss_C == 0) {
                    lbl_1_bss_C = 1;
                    HuAudFXPlay(32);
                }
            }
            break;
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
            if(cmd == 8) {
                HuAudFXPlay(0);
            } else if(cmd == 9) {
                HuAudFXPlay(2);
            } else if(cmd == 11) {
                HuAudFXPlay(1021);
            } else if(cmd == 12) {
                HuAudFXPlay(4);
            } else if(cmd == 13) {
                HuAudFXPlay(1039);
            } else if(cmd == 14) {
                HuAudFXPlay(1100);
            } else if(cmd == 15) {
                HuAudFXPlay(1139);
            } else if(cmd == 16) {
                HuAudFXPlay(851);
            }
            break;
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            if(cmd <= 20) {
                pos = *model->posP[cmd-10];
                Hu3D3Dto2D(&pos, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
                pan = MSM_PAN_LEFT+((MSM_PAN_WIDTH/HU_DISP_WIDTH)*pos2D.x);
                HuAudFXPlayPan(1140, pan);
                winVoiceFlag[cmd-17] = 1;
            } else if(cmd <= 24) {
                pos = *model->posP[cmd-10];
                Hu3D3Dto2D(&pos, camera->camera[MDCAMERA_MAIN].bit, &pos2D);
                pan = MSM_PAN_LEFT+((MSM_PAN_WIDTH/HU_DISP_WIDTH)*pos2D.x);
                HuAudFXPlayPan(1141, pan);
            }
            break;
        case 25:
        case 26:
        case 27:
            fxPan = ResCardFXPanGet(MDMODEL_STAR, MDCAMERA_FG);
            if(cmd == 25) {
                HuAudFXPlayPan(754, fxPan);
            } else if(cmd == 26) {
                HuAudFXPlayPan(753, fxPan);
            } else if(cmd == 27) {
                HuAudFXPlayPan(753, fxPan);
            }
            break;
        case 28:
            HuAudAllStop();
            break;
    }
}

/* 46 insns */
int ResCardFXPanGet(int mdlNo, int cameraNo)
{
    MDCAMERA *camera; //r31
    MDMODEL_WORK *model; //r30

    MDCAMERA_WORK *cameraWork; //r29
    HuVecF *pos3D; //r28
    int result; //r27

    HuVecF pos2D;

    cameraWork = sys->camera;
    camera = &cameraWork->camera[cameraNo];
    model = sys->model;
    pos3D = model->posP[mdlNo];
    Hu3D3Dto2D(pos3D, camera->bit, &pos2D);
    result = MSM_PAN_LEFT+((MSM_PAN_WIDTH/HU_DISP_WIDTH)*pos2D.x);
    return result;
}

/* 41 insns */
void ResCardBGMReset(void)
{
    lbl_1_bss_0 = 0;
    lbl_1_bss_10 = 0;
    while(TRUE) {
        switch(lbl_1_bss_0) {
            case 0:
                break;
            case 1:
                if(++lbl_1_bss_10 >= 300) {
                    ResCardAudExec(2);
                    lbl_1_bss_0++;
                }
                break;
            case 2:
                break;
        }
        HuPrcVSleep();
    }
}

/* 54 insns */
void ResCardWinVoicePlay(void)
{
    int i; //r31

    for(i=0; i<4; i++) {
        winVoiceFlag[i] = 0;
        lbl_1_bss_34[i] = 0;
    }
    while(TRUE) {
        for(i=0; i<4; i++) {
            switch(winVoiceFlag[i]) {
                case 0:
                    break;
                case 1:
                    if(++lbl_1_bss_34[i] >= 40) {
                        winVoiceFlag[i] = 0;
                        ResCardAudExec(i+21);
                    }
                    break;
            }
        }
        HuPrcVSleep();
    }
}


/* 1117 insns */
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
        { "STAGE_BASE", MDCAMERA_MAIN },
        { "STAGE_SIDE", MDCAMERA_MAIN },
        { "STAGE_OBJ1", MDCAMERA_MAIN },
        { "STAGE_OBJ2", MDCAMERA_MAIN },
        { "STAGE_OBJ3", MDCAMERA_MAIN },
        { "STAGE_OBJ4", MDCAMERA_MAIN },
        { "PIN_1P", MDCAMERA_MAIN },
        { "PIN_2P", MDCAMERA_MAIN },
        { "PIN_3P", MDCAMERA_MAIN },
        { "PIN_4P", MDCAMERA_MAIN },
        { "CUR_1P", MDCAMERA_MAIN },
        { "CUR_2P", MDCAMERA_MAIN },
        { "CUR_3P", MDCAMERA_MAIN },
        { "CUR_4P", MDCAMERA_MAIN },
        { "PEDESTAL_1P", MDCAMERA_MAIN },
        { "PEDESTAL_2P", MDCAMERA_MAIN },
        { "PEDESTAL_3P", MDCAMERA_MAIN },
        { "PEDESTAL_4P", MDCAMERA_MAIN },
        { "POP_STAR", MDCAMERA_MAIN },
        { "POP_ZTAR", MDCAMERA_MAIN },
        { "WIN_STAR_00", MDCAMERA_MAIN },
        { "WIN_STAR_01", MDCAMERA_MAIN },
        { "WIN_STAR_02", MDCAMERA_MAIN },
        { "WIN_STAR_03", MDCAMERA_MAIN },
        { "WIN_STAR_04", MDCAMERA_MAIN },
        { "WIN_STAR_05", MDCAMERA_MAIN },
        { "WIN_STAR_06", MDCAMERA_MAIN },
        { "WIN_STAR_07", MDCAMERA_MAIN },
        { "WIN_STAR_08", MDCAMERA_MAIN },
        { "WIN_STAR_09", MDCAMERA_MAIN },
        { "WIN_STAR_10", MDCAMERA_MAIN },
        { "WIN_STAR_11", MDCAMERA_MAIN },
        { "WIN_STAR_12", MDCAMERA_MAIN },
        { "WIN_STAR_13", MDCAMERA_MAIN },
        { "WIN_STAR_14", MDCAMERA_MAIN },
        { "WIN_STAR_15", MDCAMERA_MAIN },
        { "WIN_STAR_16", MDCAMERA_MAIN },
        { "WIN_STAR_17", MDCAMERA_MAIN },
        { "WIN_STAR_18", MDCAMERA_MAIN },
        { "WIN_STAR_19", MDCAMERA_MAIN },
        { "WIN_STAR_20", MDCAMERA_MAIN },
        { "WIN_STAR_21", MDCAMERA_MAIN },
        { "WIN_ZTAR_00", MDCAMERA_MAIN },
        { "WIN_ZTAR_01", MDCAMERA_MAIN },
        { "WIN_ZTAR_02", MDCAMERA_MAIN },
        { "WIN_ZTAR_03", MDCAMERA_MAIN },
        { "WIN_ZTAR_04", MDCAMERA_MAIN },
        { "WIN_ZTAR_05", MDCAMERA_MAIN },
        { "WIN_ZTAR_06", MDCAMERA_MAIN },
        { "WIN_ZTAR_07", MDCAMERA_MAIN },
        { "WIN_ZTAR_08", MDCAMERA_MAIN },
        { "WIN_ZTAR_09", MDCAMERA_MAIN },
        { "WIN_ZTAR_10", MDCAMERA_MAIN },
        { "CARD_STAR_1P", MDCAMERA_MAIN },
        { "CARD_STAR_2P", MDCAMERA_MAIN },
        { "CARD_STAR_3P", MDCAMERA_MAIN },
        { "CARD_STAR_4P", MDCAMERA_MAIN },
        { "CARD_ZTAR_1P", MDCAMERA_MAIN },
        { "CARD_ZTAR_2P", MDCAMERA_MAIN },
        { "CARD_ZTAR_3P", MDCAMERA_MAIN },
        { "CARD_ZTAR_4P", MDCAMERA_MAIN },
        { "CARD_SZTAR_1P", MDCAMERA_MAIN },
        { "CARD_SZTAR_2P", MDCAMERA_MAIN },
        { "CARD_SZTAR_3P", MDCAMERA_MAIN },
        { "CARD_SZTAR_4P", MDCAMERA_MAIN },
        { "DRAW_STAR", MDCAMERA_MAIN },
        { "DRAW_ZTAR_0", MDCAMERA_MAIN },
        { "DRAW_ZTAR_1", MDCAMERA_MAIN },
        { "DRAW_ZTAR_2", MDCAMERA_MAIN },
        { "DRAW_ZTAR_3", MDCAMERA_MAIN },
        { "DRAW_ZTAR_4", MDCAMERA_MAIN },
        { "DRAW_ZTAR_5", MDCAMERA_MAIN },
        { "DRAW_ZTAR_6", MDCAMERA_MAIN },
        { "EFF_STARFLASH", MDCAMERA_MAIN },
        { "EFF_DICEFLASH_1P", MDCAMERA_MAIN },
        { "EFF_DICEFLASH_2P", MDCAMERA_MAIN },
        { "EFF_DICEFLASH_3P", MDCAMERA_MAIN },
        { "EFF_DICEFLASH_4P", MDCAMERA_MAIN },
        { "EFF_CARDFLASH_1P", MDCAMERA_MAIN },
        { "EFF_CARDFLASH_2P", MDCAMERA_MAIN },
        { "EFF_CARDFLASH_3P", MDCAMERA_MAIN },
        { "EFF_CARDFLASH_4P", MDCAMERA_MAIN },
        { "RING", MDCAMERA_MAIN },
        { "SPOT_0", MDCAMERA_MAIN },
        { "SPOT_1", MDCAMERA_MAIN },
        { "SPOT_2", MDCAMERA_MAIN },
        { "SPOT_3", MDCAMERA_MAIN },
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
                HuSprPosSet(grpId, 0, 32, 0);
                HuSprPosSet(grpId, 1, -32, 0);
                sprRot_S1133 += 2;
                MdMathAngleClamp(&sprRot_S1133);
                HuSprGrpZRotSet(grpId, sprRot_S1133);
                Hu3D3Dto2D(pos, camera->camera[mdlInfoP_S1131->cameraNo].bit, &pos2D);
                HuSprGrpPosSet(grpId, pos2D.x, pos2D.y);
                if(attr & HU3D_ATTR_DISPOFF) {
                    HuSprAttrSet(grpId, 0, HUSPR_ATTR_ADDCOL);
                    HuSprAttrSet(grpId, 1, HUSPR_ATTR_ADDCOL);
                    HuSprGrpTPLvlSet(grpId, 0.4f);
                } else {
                    HuSprAttrReset(grpId, 0, HUSPR_ATTR_ADDCOL);
                    HuSprAttrReset(grpId, 1, HUSPR_ATTR_ADDCOL);
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

/* --- .bss declared last (lowest addresses; MdPosAdjustMode's statics are 0x14-0x33) --- */
/* 0x10 */ s32 lbl_1_bss_10;
/* 0xE gap_05_0000000E_bss (0x2): alignment gap */
/* 0xC */ s16 lbl_1_bss_C;
/* 0x8 */ s32 lbl_1_bss_8;
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;
