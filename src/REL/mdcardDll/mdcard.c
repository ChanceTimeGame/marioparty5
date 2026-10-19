/*
 * mdcardDll -- Bonus Mode's Card Party setup hub (mdomakedll -> omOvlCallEx(DLL_mdcarddll, 1, 0, 0)).
 * Players, characters, COM, board size and pedestals; on start fn_1_9E88 writes GwPlayerConf[4]
 * and GwCardCommon and MdClose goes to carddll (omOvlGotoEx); quit returns to mdomakedll.
 * Twins: mdseldll/mdsel.c, mdminidll, mdstorydll, mdbeachdll (MdPosAdjustMode). See NOTES.md.
 */

#define MDCARD_HELPWIN_UNPROTO /* fn_1_1DF0: retail calls MdMessHelpWinCreate unprototyped */
#include "REL/mdcardDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/disp.h"
#include "math.h"
#include "msm.h"
#include "datadir_enum.h"
#include "messdir_enum.h"
#include "game/frand.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 80.0f; /* 0x10 */
static const float lbl_1_rodata_14 = 376.0f; /* 0x14 */
static const float lbl_1_rodata_18 = 1.0f; /* 0x18 */
static const float lbl_1_rodata_1C = 64.0f; /* 0x1C */
static const float lbl_1_rodata_20 = 160.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 48.0f; /* 0x24 */
static const double lbl_1_rodata_28 = 0.0; /* 0x28 */
static const double lbl_1_rodata_30 = 340.0; /* 0x30 */
static const float lbl_1_rodata_38 = 2.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 0.0f; /* 0x3C */
static const float lbl_1_rodata_40 = 56.0f; /* 0x40 */
static const float lbl_1_rodata_44 = 4.0f; /* 0x44 */
static const float lbl_1_rodata_48 = 470.0f; /* 0x48 */
static const float lbl_1_rodata_4C = 50.0f; /* 0x4C */
static const float lbl_1_rodata_50 = 15.0f; /* 0x50 */
static const float lbl_1_rodata_54 = 4000.0f; /* 0x54 */
static const float lbl_1_rodata_58 = 240.0f; /* 0x58 */
static const float lbl_1_rodata_5C = 0.5f; /* 0x5C */
static const float lbl_1_rodata_60 = -128.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 90.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 180.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 30.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 0.2f; /* 0x70 */
static const float lbl_1_rodata_74 = 512.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 288.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 176.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 3.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 200.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 20.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 270.0f; /* 0x8C */
static const float lbl_1_rodata_90 = -90.0f; /* 0x90 */
static const double lbl_1_rodata_98 = 3.141592653589793; /* 0x98 */
static const double lbl_1_rodata_A0 = 180.0; /* 0xA0 */
/* 0xA8 lbl_1_rodata_A8 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_B0 = 112.0f; /* 0xB0 */
static const float lbl_1_rodata_B4 = 464.0f; /* 0xB4 */
static const float lbl_1_rodata_B8 = 704.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 24.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 1.5f; /* 0xC0 */
static const float lbl_1_rodata_C4 = -240.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 1.5707964f; /* 0xC8 */
static const float lbl_1_rodata_CC = -384.0f; /* 0xCC */
static const float lbl_1_rodata_D0 = 2500.0f; /* 0xD0 */
static const float lbl_1_rodata_D4 = -180.0f; /* 0xD4 */
static const float lbl_1_rodata_D8 = 60.0f; /* 0xD8 */
static const float lbl_1_rodata_DC = 32.0f; /* 0xDC */
static const float lbl_1_rodata_E0 = 70.0f; /* 0xE0 */
static const float lbl_1_rodata_E4 = 150.0f; /* 0xE4 */
static const float lbl_1_rodata_E8 = 168.0f; /* 0xE8 */
static const float lbl_1_rodata_EC = 340.0f; /* 0xEC */
static const float lbl_1_rodata_F0 = 2000.0f; /* 0xF0 */
static const float lbl_1_rodata_F4 = 8.0f; /* 0xF4 */
static const float lbl_1_rodata_F8 = 0.75f; /* 0xF8 */
static const float lbl_1_rodata_FC = 25.0f; /* 0xFC */
/* 0x100 lbl_1_rodata_100 (0x1): 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_104 = 0.11111111f; /* 0x104 */
static const float lbl_1_rodata_108 = 5.0f; /* 0x108 */
static const float lbl_1_rodata_10C = 10.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 0.05f; /* 0x110 */
static const float lbl_1_rodata_114 = 0.01f; /* 0x114 */
static const float lbl_1_rodata_118 = 0.1f; /* 0x118 */
static const float lbl_1_rodata_11C = -32.0f; /* 0x11C */
static const float lbl_1_rodata_120 = 0.4f; /* 0x120 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x49C */ SYS sysWork;
/* 0x498 */ SYS *sys;
/* 0x494 */ SYS *sysP;
/* 0x2F0 */ HuVecF lbl_1_bss_2F0[7][5]; /* fn_1_80A8: per character pin pos, pin top, pin rot, finger pos, finger rot */
/* 0x200 */ float lbl_1_bss_200[4][15];
/* 0x1FC */ s32 lbl_1_bss_1FC;
/* 0x1F8 */ s32 lbl_1_bss_1F8;
/* 0x1C8 */ MDCARD_CAMLERP lbl_1_bss_1C8; /* fn_1_461C */
/* 0x1B0 */ HuVecF lbl_1_bss_1B0[2];
/* 0x1AC */ float lbl_1_bss_1AC;
/* 0x1A8 */ float lbl_1_bss_1A8;
/* 0x19C */ HuVecF lbl_1_bss_19C; /* fn_1_4F80: capsule start (mdmini lbl_1_bss_350) */
/* 0x16C */ HuVecF lbl_1_bss_16C[4]; /* fn_1_4F80: capsule targets */
/* 0x164 */ s8 lbl_1_bss_164[4][2]; /* fn_1_4F80: [player][new/old] 0 MAN 1 COM */
/* 0x160 */ float lbl_1_bss_160;
/* 0x15C */ float lbl_1_bss_15C;
/* 0x12C */ HuVecF lbl_1_bss_12C[4];
/* 0xFC */ HuVecF lbl_1_bss_FC[4]; /* fn_1_61F8: cursor arrow positions (mdstory lbl_1_bss_A0) */
/* 0xF0 */ float lbl_1_bss_F0[3];
/* 0xEC */ s8 lbl_1_bss_EC; /* fn_1_6B0C: init flag */
/* 0xD4 */ float lbl_1_bss_D4[6];
/* 0xA4 */ HuVecF lbl_1_bss_A4[4];
/* 0x8C */ HuVecF lbl_1_bss_8C[2]; /* fn_1_71B8: box 2D positions */
/* 0x68 */ HuVecF lbl_1_bss_68[3]; /* fn_1_71B8: box positions */
/* 0x44 */ HuVecF lbl_1_bss_44[3]; /* fn_1_71B8: box rotations */
/* 0x2C */ HuVecF lbl_1_bss_2C[2];
/* 0x28 */ s32 lbl_1_bss_28; /* fn_1_A094: BGM stream handle */

/* defined after MdPosAdjustMode (their .bss addresses are below its statics) */
extern s32 lbl_1_bss_4;
extern s8 lbl_1_bss_2;
extern s8 lbl_1_bss_1;
extern u8 lbl_1_bss_0;

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ float lbl_1_data_0[4] = { 0.64f, 4000.0f, 80.0f, 2500.0f };
/* 0x10 */ float lbl_1_data_10[6] = { 310.0f, 290.0f, 2500.0f, -70.0f, 200.0f, 150.0f };
/* 0x28 */ HuVecF lbl_1_data_28[7] = { { -65.0f, 134.5f, -371.0f }, { 103.5f, 134.5f, -371.0f }, { 272.0f, 134.5f, -371.0f }, { -151.0f, 110.5f, -115.0f }, { 18.5f, 134.5f, -115.0f }, { 190.5f, 134.5f, -115.0f }, { 362.0f, 135.0f, -115.0f } };
/* 0x7C */ HuVecF lbl_1_data_7C = { -90.0f, 0.0f, 0.0f };
/* 0x88 */ MD_FUNC MdFlowTbl[6] = { fn_1_DD8, fn_1_1058, fn_1_1448, fn_1_1DF0, fn_1_22B8, fn_1_2A3C };
/* 0xA0 */ MD_PROC MdProcTbl[10] = { fn_1_44F8, fn_1_461C, fn_1_4944, fn_1_4C00, fn_1_4DC8, fn_1_4F80, fn_1_61F8, fn_1_6B0C, fn_1_71B8, fn_1_78C4 };

/* 526 insns */
void ObjectSetup(void)
{
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
    sys->objman = omInitObjMan(512, 8192);
    omGameSysInit(sys->objman);
    sys->obj[MDCARD_OBJ_DEBUGFONT] = omAddObjEx(sys->objman, 100, 0, 0, -1, MdObjDebugFontCreate);
    sys->obj[MDCARD_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDCARD_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDCARD_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDCARD_OBJ_PAD] = omAddObjEx(sys->objman, 101, 0, 0, -1, MdObjPadMain);
    sys->obj[MDCARD_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_PAD]->data) {
        OSReport("sys->obj[MDCARD_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDCARD_OBJ_PAD]->data;
    sys->obj[MDCARD_OBJ_CAMERA] = omAddObjEx(sys->objman, 102, 0, 0, -1, MdObjCameraCreate);
    sys->obj[MDCARD_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDCARD_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDCARD_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDCARD_OBJ_LIGHT] = omAddObjEx(sys->objman, 103, 0, 0, -1, MdObjLightCreate);
    sys->obj[MDCARD_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDCARD_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDCARD_OBJ_LIGHT]->data;
    sys->light->createF = FALSE;
    sys->light->debugFont = sys->debugFont;
    sys->obj[MDCARD_OBJ_SHADOW] = omAddObjEx(sys->objman, 104, 0, 0, -1, MdObjShadowCreate);
    sys->obj[MDCARD_OBJ_SHADOW]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSHADOW_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_SHADOW]->data) {
        OSReport("sys->obj[MDCARD_OBJ_SHADOW]->data = NULL...\n");
    }
    sys->shadow = sys->obj[MDCARD_OBJ_SHADOW]->data;
    sys->shadow->createF = FALSE;
    sys->shadow->debugFont = sys->debugFont;
    sys->obj[MDCARD_OBJ_MESS] = omAddObjEx(sys->objman, 105, 0, 0, -1, MdObjMessCreate);
    sys->obj[MDCARD_OBJ_MESS]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMESS_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDCARD_OBJ_MESS]->data) {
        OSReport("sys->obj[MDCARD_OBJ_MESS]->data = NULL...\n");
    }
    sys->mess = sys->obj[MDCARD_OBJ_MESS]->data;
    sys->mess->createF = FALSE;
    sys->sprite = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSPRITE_WORK), HU_MEMNUM_OVL);
    if(!sys->sprite) {
        OSReport("sys->sprite = NULL...\n");
    }
    sys->model = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMODEL_WORK), HU_MEMNUM_OVL);
    if(!sys->model) {
        OSReport("sys->model = NULL...\n");
    }
    MdMathStdCurveInit();
    Hu3DBGColorSet(0, 0, 0);
    Hu3DNoSyncSet(FALSE);
    while(1) {
        if(sys->debugFont->createF == TRUE && sys->camera->createF == TRUE && sys->light->createF == TRUE
            && sys->shadow->createF == TRUE && sys->mess->createF == TRUE) {
            break;
        }
        HuPrcVSleep();
    }
    sys->mainProc = HuPrcChildCreate(MdMain, 107, 12288, 0, sys->objman);
    sys->loadState = MD_LOAD_STATE_NONE;
    sys->loadAsyncStat = 0;
    sys->loadDir = DATA_mdsel;
    sys->loadProc = HuPrcChildCreate(LoadProc, 110, 12288, 0, sys->objman);
}

/* 50 insns */
void MdMain(void)
{
    MdInit();
    while(!omSysExitReq && !sys->exitF) {
        MdFlowTbl[sys->flowMode]();
        fn_1_84AC();
        if(++sys->flowTime > 36000) {
            sys->flowTime = 0;
        }
        HuPrcVSleep();
    }
    MdClose();
}

/* 37 insns */
void fn_1_9A0(void)
{
    MDMESS_WORK *mess;
    s16 *choiceP;

    mess = sys->mess;
    choiceP = &sys->unk98;
    while(1) {
        mess = sys->mess;
        choiceP = &sys->unk98;
        switch(choiceP[0]) {
            case 0:
                break;

            case 1:
                choiceP[1] = MdMessWinChoiceGet(mess, 1);
                choiceP[0] = 2;
                break;

            case 2:
                break;
        }
        HuPrcVSleep();
    }
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

/* 100 insns */
void MdInit(void)
{
    MDCARD_REC *rec;
    MDCARD_PLAYERSPR *playerSpr;
    int i;
    int j;

    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdModelCreate(sys->model, sys->camera);
    HuPrcVSleep();
    HuDataDirClose(DATA_mdcard);
    HuPrcVSleep();
    MdToueiMdlInit();
    sys->unk38C = 0;
    sys->unk390 = 1;
    sys->unk5C = HuPrcChildCreate(fn_1_7DA0, 109, 12288, 0, sys->objman);
    for(playerSpr = sys->playerSpr, i = 0; i < 4; i++, playerSpr++) {
        playerSpr->mode = 0;
    }
    sys->unk58 = HuPrcChildCreate(fn_1_9100, 108, 4096, 0, sys->objman);
    for(rec = sys->unk9C, j = 0; j < 7; j++, rec++) {
        rec->unk0 = 0;
        rec->unk4 = 0;
    }
    HuPrcVSleep();
}

/* 69 insns */
void MdClose(void)
{
    if(!sys->skipWipeF) {
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        WipeWait();
    }
    fn_1_A094(MDCARD_AUD_ALL_STOP);
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

/* 160 insns */
void fn_1_DD8(void)
{
    MDSPRITE_WORK *sprite;
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    int i;
    s16 *choiceP;

    sprite = sys->sprite;
    model = sys->model;
    mess = sys->mess;
    for(i = 0; i < 4; i++) {
        sys->pedestalF[i] = 0;
    }
    MdSpriteDispSet(sprite, MDSPR_GRP_WIN, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_1, FALSE);
    MdSpriteDispSet(sprite, MDSPR_GRP_CURSOR_LR, FALSE);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_STAGE], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_ATTR_DISPOFF);
    for(i = 0; i < 7; i++) {
        Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN+(i*3)], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+(i*3)+1], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+(i*3)+2], HU3D_ATTR_DISPOFF);
    }
    for(i = 0; i < 8; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_MAN+i], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrSet(model->mdlId[MDMODEL_FINGER], HU3D_ATTR_DISPOFF);
    for(i = 0; i < 5; i++) {
        Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD+i], HU3D_ATTR_DISPOFF);
    }
    fn_1_98C8();
    MdProcTbl[0](0);
    choiceP = &sys->unk98;
    choiceP[0] = 0;
    sys->boardSize = 0;
    sys->playerNum = 3;
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    fn_1_A094(MDCARD_AUD_MUS_START);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    sys->subMode = 0;
    sys->unk4 = 0;
    sys->flowMode = 1;
}
#ifdef __MWERKS__
#endif

/* 252 insns */
void fn_1_1058(void)
{
    int result;
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;

    model = sys->model;
    mess = sys->mess;
    switch(sys->subMode) {
        case 0:
            MdProcTbl[0](0);
            sys->subMode = 6;
            break;

        case 6:
            result = MdProcTbl[1](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 8;
            }
            break;

        case 8:
            MdMessWinOpen(mess, 2, 80.0f, 376.0f, 416, 64, 1.0f, 0);
            MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 0));
            fn_1_A094(MDCARD_AUD_STAR);
            sys->unk390 = 2;
            sys->subMode = 1;
            break;

        case 1:
            result = MdMessWinCheck(mess, 2);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 1));
                sys->subMode = 2;
            }
            break;

        case 2:
            result = MdMessWinChoiceGet(mess, 2);
            if(result == -1) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 2));
                sys->subMode = 3;
            } else if(result == 0) {
                MdMessWinKill(mess, 2);
                sys->subMode = 0;
                sys->flowMode = 2;
            } else if(result == 1) {
                sys->subMode = 0;
                sys->flowMode = 3;
            }
            break;

        case 3:
            result = MdMessWinChoiceGet(mess, 2);
            if(result == -1 || result == 1) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 1));
                sys->subMode = 2;
            } else if(result == 0) {
                fn_1_A094(MDCARD_AUD_MUS_STOP);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                sys->loadState = MD_LOAD_STATE_LOADING;
                sys->loadDir = DATA_mdomake;
                sys->subMode = 4;
            }
            break;

        case 4:
            result = WipeCheckEnd();
            if(result == 0) {
                sys->subMode = 5;
            }
            break;

        case 5:
            if(sys->loadState == MD_LOAD_STATE_DONE) {
                sys->ovlCallMode = MD_OVLCALL_RETURN;
                sys->nextDll = DLL_mdomakedll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;

        case 7:
            break;
    }
}
#ifdef __MWERKS__
#endif

/* 618 insns */
void fn_1_1448(void)
{
    MDMESS_WORK *mess;
    int result;
    int i;
    MDMODEL_WORK *model;

    model = sys->model;
    mess = sys->mess;
    if(HuPadBtnDown[0] & PAD_BUTTON_B) {
        /* retail: always true (|| of two != tests) -- B skips to case 22 from any step */
        if(sys->subMode != 0 || sys->subMode != 22) {
            sys->subMode = 22;
        }
    }
    switch(sys->subMode) {
        case 0:
            MdProcTbl[0](0);
            MdMessWinOpen(mess, 1, 64.0f, 160.0f, 448, 96, 1.0f, 64);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 0));
            sys->subMode = 1;
            break;

        case 1:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 1));
                sys->subMode = 2;
            }
            break;

        case 2:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 2));
                sys->subMode = 3;
            }
            break;

        case 3:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                sys->subMode = 4;
            }
            break;

        case 4:
            result = MdProcTbl[2](33);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 3));
                sys->subMode = 5;
            }
            break;

        case 5:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                sys->subMode = 6;
            }
            break;

        case 6:
            result = MdProcTbl[4](33);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 7;
            }
            break;

        case 7:
            result = MdProcTbl[2](34);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 4));
                sys->subMode = 8;
            }
            break;

        case 8:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                sys->subMode = 9;
            }
            break;

        case 9:
            result = MdProcTbl[4](34);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 10;
            }
            break;

        case 10:
            result = MdProcTbl[2](35);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 5));
                sys->subMode = 11;
            }
            break;

        case 11:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                sys->subMode = 12;
            }
            break;

        case 12:
            result = MdProcTbl[4](35);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 13;
            }
            break;

        case 13:
            result = MdProcTbl[2](36);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 9));
                sys->subMode = 14;
            }
            break;

        case 14:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                sys->subMode = 15;
            }
            break;

        case 15:
            result = MdProcTbl[3](36);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 10));
                sys->subMode = 16;
            }
            break;

        case 16:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                sys->subMode = 17;
            }
            break;

        case 17:
            result = MdProcTbl[4](36);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 18;
            }
            break;

        case 18:
            result = MdProcTbl[2](37);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 7));
                sys->subMode = 19;
            }
            break;

        case 19:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinHomeClear(mess, 1);
                sys->subMode = 20;
            }
            break;

        case 20:
            result = MdProcTbl[4](37);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 1);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_TUTORIAL, 8));
                sys->subMode = 21;
            }
            break;

        case 21:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                MdMessWinKill(mess, 1);
                MdMessWinOpen(mess, 2, 80.0f, 376.0f, 416, 64, 1.0f, 0);
                sys->subMode = 0;
                sys->flowMode = 3;
            }
            break;

        case 22:
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            while(WipeCheckEnd()) {
                HuPrcVSleep();
            }
            for(i = 0; i < 5; i++) {
                Hu3DModelAttrSet(model->mdlId[MDMODEL_CARD+i], HU3D_ATTR_DISPOFF);
            }
            MdMessWinClose(mess, 1);
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            while(WipeCheckEnd()) {
                HuPrcVSleep();
            }
            MdMessWinOpen(mess, 2, 80.0f, 376.0f, 416, 64, 1.0f, 0);
            MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 1));
            sys->subMode = 2;
            sys->flowMode = 1;
            break;
    }
}

/* 306 insns */
void fn_1_1DF0(void)
{
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    s16 *choiceP;
    int result;

    model = sys->model;
    mess = sys->mess;
    choiceP = &sys->unk98;
    switch(sys->subMode) {
        case 0:
            sys->boardSize = 0;
            MdProcTbl[0](0);
            MdMessWinHomeClear(mess, 2);
            MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 3));
            fn_1_A094(12);
            Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_REV);
            Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(model->mdlId[MDMODEL_BOX], 1.0f);
            fn_1_A094(9);
            sys->subMode = 1;
            break;

        case 1:
            result = MdMessWinCheck(mess, 2);
            if(result != FALSE) {
                MdMessWinOpen(mess, 1, 48.0f, 64.0f, 480, 176, 1.0f, 64);
                sys->subMode = 2;
            }
            break;

        case 2:
            MdProcTbl[0](0);
            /* retail calls it unprototyped (double arguments): see MDCARD_HELPWIN_UNPROTO */
            MdMessHelpWinCreate(mess, 0, MESSNUM(MESS_SYSHELP, 4), 0.0, 340.0, 512, 32, 0.0, 0);
            MdMessWinAttrSet(mess, 1, HUWIN_ATTR_ALIGN_CENTER);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 4));
            MdMessWinChoiceNowSet(mess, 1, 0);
            lbl_1_bss_1FC = 0;
            MdMessWinHomeClear(mess, 2);
            MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 5));
            sys->unk50 = HuPrcChildCreate(fn_1_9A0, 106, 4096, 0, sys->objman);
            choiceP[0] = 1;
            sys->subMode = 3;
            break;

        case 3:
            lbl_1_bss_1F8 = MdMessWinChoiceNowGet(mess, 1);
            if(lbl_1_bss_1FC != lbl_1_bss_1F8 && lbl_1_bss_1F8 >= 0 && lbl_1_bss_1F8 <= 3) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 5)+lbl_1_bss_1F8);
            }
            lbl_1_bss_1FC = lbl_1_bss_1F8;
            if(choiceP[0] == 2) {
                HuPrcKill(sys->unk50);
                sys->subMode = 4;
            }
            break;

        case 4:
            result = MdMessWinCheck(mess, 1);
            if(result != FALSE) {
                if(choiceP[1] == -1) {
                    MdMessWinClose(mess, 0);
                    MdMessWinAttrReset(mess, 1, HUWIN_ATTR_ALIGN_CENTER);
                    MdMessWinKill(mess, 1);
                    MdMessWinHomeClear(mess, 2);
                    MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 1));
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_REV);
                    Hu3DMotionSpeedSet(model->mdlId[MDMODEL_BOX], 2.0f);
                    fn_1_A094(10);
                    sys->subMode = 2;
                    sys->flowMode = 1;
                } else {
                    sys->boardSize = choiceP[1];
                    sys->subMode = 0;
                    sys->flowMode = 4;
                }
            }
            break;
    }
}
#ifdef __MWERKS__
#endif

/* 481 insns */
void fn_1_22B8(void)
{
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    s16 *choiceP;
    int result;

    model = sys->model;
    mess = sys->mess;
    choiceP = &sys->unk98;
    switch(sys->subMode) {
        case 0:
            MdProcTbl[0](0);
            fn_1_951C();
            sys->prevPlayerNum = sys->playerNum;
            MdMessWinHomeClear(mess, 1);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 9));
            sys->subMode = 1;
            break;

        case 1:
            result = MdProcTbl[5](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 13)-sys->playerNum);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 3;
                } else {
                    sys->subMode = 2;
                }
            }
            break;

        case 2:
            result = MdProcTbl[6](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 3;
            }
            break;

        case 3:
            if((sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) && sys->maxPlayerNum > 1) {
                sys->prevPlayerNum = sys->playerNum;
                if(--sys->playerNum == -1) {
                    sys->playerNum = sys->maxPlayerNum-1;
                }
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 13)-sys->playerNum);
                fn_1_A094(2);
                sys->subMode = 6;
            } else if((sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) && sys->maxPlayerNum > 1) {
                sys->prevPlayerNum = sys->playerNum;
                sys->playerNum = ++sys->playerNum % sys->maxPlayerNum;
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 13)-sys->playerNum);
                fn_1_A094(2);
                sys->subMode = 7;
            } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
                fn_1_A094(5);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 5;
                } else {
                    sys->subMode = 4;
                }
            } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
                fn_1_9714();
                fn_1_A094(3);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 9;
                } else {
                    sys->subMode = 8;
                }
            }
            break;

        case 4:
            result = MdProcTbl[6](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 5;
            }
            break;

        case 5:
            result = MdProcTbl[5](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinAttrSet(mess, 1, HUWIN_ATTR_ALIGN_CENTER);
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 4));
                MdMessWinChoiceNowSet(mess, 1, 0);
                lbl_1_bss_1FC = 0;
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 5));
                sys->unk50 = HuPrcChildCreate(fn_1_9A0, 106, 4096, 0, sys->objman);
                choiceP[0] = 1;
                sys->subMode = 3;
                sys->flowMode = 3;
            }
            break;

        case 6:
        case 7:
            result = MdProcTbl[5](sys->subMode-4);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 3;
            }
            break;

        case 8:
            result = MdProcTbl[6](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 9;
            }
            break;

        case 9:
            result = MdProcTbl[7](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 0;
                sys->flowMode = 5;
            }
            break;
    }
}
#ifdef __MWERKS__
#endif

/* 1711 insns */
void fn_1_2A3C(void)
{
    MDSPRITE_WORK *sprite;
    int *unk38CP;
    int motNo;
    int j;
    MDCARD_PLAYERSPR *playerSpr;
    int mdlNo;
    MDMESS_WORK *mess;
    int result;
    MDCARD_REC *rec;
    MDMODEL_WORK *model;
    int i;

    model = sys->model;
    sprite = sys->sprite;
    mess = sys->mess;
    unk38CP = &sys->unk38C;
    switch(sys->subMode) {
        case 0:
            sys->unk3A = 0;
            sys->chrSel[sys->unk3A] = 0;
            sys->unk36[sys->unk3A] = 0;
            MdProcTbl[0](0);
            MdMessWinHomeClear(mess, 2);
            MdMessWinInsertMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 14), MESSNUM(MESS_MPCARD_SYS, 28)+sys->padNoEnable[sys->unk3A]);
            sys->subMode = 1;
            break;

        case 1:
            result = MdProcTbl[8](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                fn_1_80A8();
                sys->subMode = 2;
            }
            break;

        case 2:
            result = MdProcTbl[9](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                lbl_1_bss_0 = 1;
                rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                rec->unk0 = 1;
                sys->subMode = 3;
            }
            break;

        case 3:
            result = fn_1_9A70();
            if(result == 0 || result == 1) {
                rec = &sys->unk9C[sys->unk36[sys->unk3A]];
                rec->unk0 = 4;
                fn_1_9CC8(result);
                sys->unk36[sys->unk3A] = sys->chrSel[sys->unk3A];
                rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                rec->unk0 = 1;
                fn_1_A094(2);
                MdProcTbl[9](2);
            } else if(result == 2) {
                fn_1_A094(5);
                if(sys->unk3A == 0) {
                    rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                    rec->unk0 = 4;
                    sys->subMode = 4;
                } else {
                    rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                    rec->unk0 = 4;
                    for(i = 0; i < 3; i++) {
                        Hu3DMotionShiftSet(model->mdlId[MDMODEL_PIN+(sys->chrSel[sys->unk3A-1]*3)+i], model->motId[MDMODEL_MOT_PIN_B+(sys->chrSel[sys->unk3A-1]*3)+i], 0.0f, 56.0f, HU3D_MOTATTR_NONE);
                    }
                    playerSpr = &sys->playerSpr[sys->unk3A-1];
                    playerSpr->mode = 4;
                    sys->subMode = 8;
                }
            } else if(result == 3) {
                sys->pedestalF[sys->unk3A] = result-3;
                rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                rec->unk0 = 7;
                rec->unk4 = sys->pedestalF[sys->unk3A];
                if(sys->unk3A < 3) {
                    fn_1_A094(4);
                } else {
                    fn_1_A094(3);
                }
                for(i = 0; i < 3; i++) {
                    mdlNo = MDMODEL_PIN+(sys->chrSel[sys->unk3A]*3)+i;
                    motNo = MDMODEL_MOT_PIN_B+(sys->chrSel[sys->unk3A]*3)+i;
                    Hu3DMotionSet(model->mdlId[mdlNo], model->motId[motNo]);
                    Hu3DMotionTimeSet(model->mdlId[mdlNo], 0.0f);
                    Hu3DModelAttrReset(model->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
                    Hu3DModelAttrSet(model->mdlId[mdlNo], HU3D_MOTATTR_PAUSE);
                    if(i == sys->pedestalF[sys->unk3A]) {
                        Hu3DModelAttrReset(model->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(model->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
                    }
                }
                sys->subMode = 7;
            }
            break;

        case 4:
            result = MdProcTbl[9](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 5;
            }
            break;

        case 5:
            result = MdProcTbl[8](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->subMode = 6;
            }
            break;

        case 6:
            result = MdProcTbl[7](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 13)-sys->playerNum);
                if(sys->maxPlayerNum == 1) {
                    sys->subMode = 3;
                } else {
                    sys->subMode = 2;
                }
                sys->flowMode = 4;
            }
            break;

        case 7:
            MdProcTbl[9](1);
            rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
            if(rec->unk0 == 9) {
                MdProcTbl[0](0);
                for(i = 0; i < 3; i++) {
                    mdlNo = MDMODEL_PIN+(sys->chrSel[sys->unk3A]*3)+i;
                    motNo = MDMODEL_MOT_PIN_A+(sys->chrSel[sys->unk3A]*3)+i;
                    Hu3DMotionSet(model->mdlId[mdlNo], model->motId[motNo]);
                    Hu3DMotionTimeSet(model->mdlId[mdlNo], 0.0f);
                    Hu3DModelAttrReset(model->mdlId[mdlNo], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(model->mdlId[mdlNo], HU3D_MOTATTR_LOOP);
                }
                playerSpr = &sys->playerSpr[sys->unk3A];
                playerSpr->mode = 1;
                sys->unk3A++;
                if(sys->unk3A >= 4) {
                    if(sys->padNoEnable[3] == -1) {
                        MdMessWinOpen(mess, 2, 80.0f, 376.0f, 416, 64, 1.0f, 0);
                        MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 15));
                        sys->unk390 = 2;
                    } else {
                        MdMessWinClose(mess, 0);
                        MdMessWinHomeClear(mess, 2);
                        MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 15));
                    }
                    sys->subMode = 10;
                } else {
                    sys->chrSel[sys->unk3A] = sys->chrSel[sys->unk3A-1];
                    fn_1_9CC8(1);
                    sys->unk36[sys->unk3A] = sys->chrSel[sys->unk3A];
                    if(sys->padNoEnable[sys->unk3A] != -1) {
                        MdMessWinHomeClear(mess, 2);
                        MdMessWinInsertMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 14), MESSNUM(MESS_MPCARD_SYS, 28)+sys->padNoEnable[sys->unk3A]);
                    } else if(sys->padNoEnable[sys->unk3A-1] != -1) {
                        MdMessWinClose(mess, 0);
                        MdMessWinKill(mess, 2);
                        sys->unk390 = 3;
                    }
                    sys->subMode = 2;
                }
            }
            break;

        case 8:
            MdProcTbl[9](1);
            rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
            if(rec->unk0 == 6) {
                MdProcTbl[0](0);
                sys->unk3A--;
                rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
                rec->unk0 = 10;
                if(sys->padNoEnable[sys->unk3A] != -1 && sys->padNoEnable[sys->unk3A+1] == -1) {
                    MdMessHelpWinCreate(mess, 0, MESSNUM(MESS_SYSHELP, 4), 0.0, 340.0, 512, 32, 0.0, 0);
                    MdMessWinOpen(mess, 2, 80.0f, 376.0f, 416, 64, 1.0f, 0);
                    MdMessWinInsertMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 14), MESSNUM(MESS_MPCARD_SYS, 28)+sys->padNoEnable[sys->unk3A]);
                } else if(sys->padNoEnable[sys->unk3A] != -1) {
                    MdMessWinHomeClear(mess, 2);
                    MdMessWinInsertMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 14), MESSNUM(MESS_MPCARD_SYS, 28)+sys->padNoEnable[sys->unk3A]);
                }
                sys->subMode = 9;
            }
            break;

        case 9:
            MdProcTbl[9](0);
            rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
            if(rec->unk0 == 12) {
                MdProcTbl[0](0);
                sys->pedestalF[sys->unk3A] = 0;
                for(i = 0; i < 3; i++) {
                    mdlNo = MDMODEL_PIN+(sys->chrSel[sys->unk3A]*3)+i;
                    motNo = MDMODEL_MOT_PIN_B+(sys->chrSel[sys->unk3A]*3)+i;
                    if(i == sys->pedestalF[sys->unk3A]) {
                        Hu3DModelAttrReset(model->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(model->mdlId[mdlNo], HU3D_ATTR_DISPOFF);
                    }
                }
                sys->subMode = 3;
            }
            break;

        case 10:
            result = MdMessWinChoiceGet(mess, 2);
            if(result == -1 || result == 1) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 16));
                sys->subMode = 11;
            } else if(result == 0) {
                for(i = 0; i < 4; i++) {
                    mdlNo = MDMODEL_PIN+(sys->chrSel[i]*3)+sys->pedestalF[i];
                    Hu3DModelLayerSet(model->mdlId[mdlNo], 2);
                }
                MdMessWinKill(mess, 2);
                sys->unk390 = 3;
                Hu3DModelAttrReset(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(model->mdlId[MDMODEL_BOX], 4.0f);
                fn_1_A094(10);
                fn_1_9E88();
                sys->loadState = MD_LOAD_STATE_LOADING;
                sys->loadDir = DATA_card;
                sys->subMode = 16;
            }
            break;

        case 11:
            result = MdMessWinChoiceGet(mess, 2);
            if(result == -1 || result == 1) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 2));
                sys->subMode = 12;
            } else if(result == 0) {
                sys->subMode = 13;
            }
            break;

        case 12:
            result = MdMessWinChoiceGet(mess, 2);
            if(result == -1 || result == 1) {
                MdMessWinHomeClear(mess, 2);
                MdMessWinMesSet(mess, 2, MESSNUM(MESS_MPCARD_SYS, 15));
                sys->subMode = 10;
            } else if(result == 0) {
                fn_1_A094(MDCARD_AUD_MUS_STOP);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                sys->loadState = MD_LOAD_STATE_LOADING;
                sys->loadDir = DATA_mdomake;
                sys->subMode = 14;
            }
            break;

        case 13:
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            while(WipeCheckEnd()) {
                HuPrcVSleep();
            }
            MdMessWinHomeClear(mess, 2);
            model->posP[MDMODEL_BOX]->x = 0.0f;
            model->posP[MDMODEL_BOX]->y = 0.0f;
            model->posP[MDMODEL_BOX]->z = 0.0f;
            model->rotP[MDMODEL_BOX]->x = 0.0f;
            model->rotP[MDMODEL_BOX]->y = 0.0f;
            model->rotP[MDMODEL_BOX]->z = 0.0f;
            Hu3DMotionTimeSet(model->mdlId[MDMODEL_BOX], 0.0f);
            Hu3DModelAttrSet(model->mdlId[MDMODEL_BOX], HU3D_MOTATTR_PAUSE);
            for(rec = sys->unk9C, i = 0; i < 7; i++, rec++) {
                rec->unk0 = 0;
            }
            fn_1_98C8();
            for(i = 0; i < 4; i++) {
                sys->pedestalF[i] = 0;
            }
            for(i = 0; i < 7; i++, rec++) {
                for(j = 0; j < 3; j++) {
                    if(j == 0) {
                        Hu3DModelAttrReset(model->mdlId[MDMODEL_PIN+(i*3)+j], HU3D_ATTR_DISPOFF);
                    } else {
                        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+(i*3)+j], HU3D_ATTR_DISPOFF);
                    }
                    Hu3DMotionSet(model->mdlId[MDMODEL_PIN+(i*3)+j], model->motId[MDMODEL_MOT_PIN_B+(i*3)+j]);
                    Hu3DMotionTimeSet(model->mdlId[MDMODEL_PIN+(i*3)+j], 0.0f);
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+(i*3)+j], HU3D_MOTATTR_PAUSE);
                }
            }
            MdSpriteDispSet(sprite, MDSPR_GRP_2, FALSE);
            for(playerSpr = sys->playerSpr, i = 0; i < 4; i++, playerSpr++) {
                playerSpr->mode = 0;
            }
            WipeColorSet(0, 0, 0);
            WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
            while(WipeCheckEnd()) {
                HuPrcVSleep();
            }
            sys->subMode = 0;
            sys->flowMode = 3;
            break;

        case 14:
            result = WipeCheckEnd();
            if(result == 0) {
                sys->subMode = 15;
            }
            break;

        case 15:
            if(sys->loadState == MD_LOAD_STATE_DONE) {
                sys->ovlCallMode = MD_OVLCALL_RETURN;
                sys->nextDll = DLL_mdomakedll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;

        case 16:
            result = Hu3DMotionEndCheck(model->mdlId[MDMODEL_BOX]);
            if(result == TRUE) {
                for(i = 0; i < 7; i++) {
                    if(i != sys->chrSel[0] && i != sys->chrSel[1] && i != sys->chrSel[2] && i != sys->chrSel[3]) {
                        Hu3DModelAttrSet(model->mdlId[MDMODEL_PIN+(i*3)], HU3D_ATTR_DISPOFF);
                    }
                }
                sys->subMode = 17;
            }
            break;

        case 17:
            result = MdProcTbl[8](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                *unk38CP = 1;
                for(playerSpr = sys->playerSpr, i = 0; i < 4; i++, playerSpr++) {
                    playerSpr->mode = 4;
                }
                sys->subMode = 18;
            }
            break;

        case 18:
            result = MdProcTbl[8](2);
            if(result == TRUE) {
                MdProcTbl[0](0);
                for(i = 0; i < 4; i++) {
                    rec = &sys->unk9C[sys->chrSel[i]];
                    rec->unk0 = 13;
                }
                fn_1_A094(MDCARD_AUD_MUS_STOP);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
                sys->subMode = 19;
            }
            break;

        case 19:
            result = WipeCheckEnd();
            if(result == 0) {
                sys->subMode = 20;
            }
            break;

        case 20:
            if(sys->loadState == MD_LOAD_STATE_DONE) {
                sys->ovlCallMode = MD_OVLCALL_GOTO;
                sys->nextDll = DLL_carddll;
                sys->skipWipeF = TRUE;
                sys->exitF = TRUE;
            }
            break;
    }
}

/* 73 insns */
BOOL fn_1_44F8(int param)
{
    sys->unk39C = FALSE;
    sys->unk3A0 = 0;
    sys->unk3A4 = 0;
    sys->time = 0;
    sys->ofsTime = 0;
    sys->unk3B8 = 0;
    sys->unk3BC = 0;
    sys->t = 0;
    sys->ofsT = 0;
    sys->unk3C8 = 0;
    sys->unk3CC = 0;
    return FALSE;
}

/* 202 insns */
BOOL fn_1_461C(int param)
{
    MDCAMERA *camera;
    MDCAMERA_WORK *cameraWork;
    cameraWork = sys->camera;
    camera = &cameraWork->camera[0];
    if(!sys->unk39C) {
        lbl_1_bss_1C8.center = camera->center;
        lbl_1_bss_1C8.hvr.x = camera->hvr.x;
        lbl_1_bss_1C8.hvr.y = camera->hvr.y;
        lbl_1_bss_1C8.hvr.z = camera->hvr.z;
        lbl_1_bss_1C8.centerEnd.x = 0.0f;
        lbl_1_bss_1C8.centerEnd.y = 470.0f;
        lbl_1_bss_1C8.centerEnd.z = 0.0f;
        lbl_1_bss_1C8.hvrEnd.x = 50.0f;
        lbl_1_bss_1C8.hvrEnd.y = 15.0f;
        lbl_1_bss_1C8.hvrEnd.z = 4000.0f;
        sys->unk39C = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 240.0f);
    MdMathOscillate(MDMATH_OSC_180, &sys->ofsTime, &sys->ofsT, 240.0f);
    MdMathLerp(&camera->center.x, lbl_1_bss_1C8.center.x, lbl_1_bss_1C8.centerEnd.x, sys->t);
    MdMathLerp(&camera->center.y, lbl_1_bss_1C8.center.y, lbl_1_bss_1C8.centerEnd.y, sys->t);
    MdMathLerp(&camera->center.z, lbl_1_bss_1C8.center.z, lbl_1_bss_1C8.centerEnd.z, sys->t);
    MdMathLerp(&camera->hvr.x, lbl_1_bss_1C8.hvr.x, lbl_1_bss_1C8.hvrEnd.x, sys->t);
    MdMathLerp(&camera->hvr.y, lbl_1_bss_1C8.hvr.y, lbl_1_bss_1C8.hvrEnd.y, sys->t);
    MdMathLerpOfs(&camera->hvr.z, lbl_1_bss_1C8.hvr.z, lbl_1_bss_1C8.hvrEnd.z, sys->t, 0.5f*sys->ofsT);
    if(sys->time >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x318 */ HuVecF lbl_1_data_318[2] = { { 288.0f, 100.0f, 3000.0f }, { 0.0f, 0.0f, 0.0f } };

/* 175 insns */
BOOL fn_1_4944(int param)
{
    HuVecF *pos;
    MDMODEL_WORK *model;
    HuVecF *rot;
    HuVecF *scale;
    int i;
    MDCAMERA_WORK *cameraWork;
    model = sys->model;
    cameraWork = sys->camera;
    pos = model->posP[param];
    rot = model->rotP[param];
    scale = model->scaleP[param];
    if(!sys->unk39C) {
        lbl_1_data_318[1] = lbl_1_data_318[0];
        lbl_1_data_318[1].x = -128.0f;
        for(i=0; i<2; i++) {
            Hu3D2Dto3D(&lbl_1_data_318[i], cameraWork->camera[1].bit, &lbl_1_bss_1B0[i]);
        }
        pos->x = lbl_1_bss_1B0[1].x;
        pos->y = lbl_1_bss_1B0[1].y;
        pos->z = lbl_1_bss_1B0[1].z;
        rot->x = 90.0f;
        rot->y = 180.0f;
        rot->z = 0.0f;
        scale->x = 1.0f;
        scale->y = 1.0f;
        scale->z = 1.0f;
        Hu3DModelAttrReset(model->mdlId[param], HU3D_ATTR_DISPOFF);
        fn_1_A094(6);
        sys->unk39C = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 30.0f);
    MdMathLerp(&pos->x, lbl_1_bss_1B0[1].x, lbl_1_bss_1B0[0].x, sys->t);
    MdMathLerp(&pos->y, lbl_1_bss_1B0[1].y, lbl_1_bss_1B0[0].y, sys->t);
    MdMathLerp(&pos->z, lbl_1_bss_1B0[1].z, lbl_1_bss_1B0[0].z, sys->t);
    if(sys->time >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 114 insns */
BOOL fn_1_4C00(int param)
{
    MDMODEL_WORK *model;
    HuVecF *rot;
    MDCAMERA_WORK *cameraWork;
    HuVecF *pos;
    HuVecF *scale;
    model = sys->model;
    cameraWork = sys->camera;
    pos = model->posP[param];
    rot = model->rotP[param];
    scale = model->scaleP[param];
    if(!sys->unk39C) {
        lbl_1_bss_1AC = rot->y;
        fn_1_A094(8);
        sys->unk39C = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 30.0f);
    MdMathOscillate(MDMATH_OSC_180, &sys->ofsTime, &sys->ofsT, 30.0f);
    MdMathLerpOfs(&rot->y, lbl_1_bss_1AC, 180.0f+lbl_1_bss_1AC, sys->t, 0.2f*sys->ofsT);
    if(sys->time >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 110 insns */
BOOL fn_1_4DC8(int param)
{
    MDMODEL_WORK *model;
    HuVecF *rot;
    HuVecF *scale;
    MDCAMERA_WORK *cameraWork;
    HuVecF *pos;
    model = sys->model;
    cameraWork = sys->camera;
    pos = model->posP[param];
    rot = model->rotP[param];
    scale = model->scaleP[param];
    if(!sys->unk39C) {
        lbl_1_bss_1A8 = rot->z;
        fn_1_A094(7);
        sys->unk39C = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 30.0f);
    MdMathLerp(&rot->z, lbl_1_bss_1A8, lbl_1_bss_1A8-512.0f, sys->t);
    MdMathLerpScale(scale, 1.0f, 0.0f, sys->t);
    if(sys->time >= 1.0f) {
        Hu3DModelAttrSet(model->mdlId[param], HU3D_ATTR_DISPOFF);
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x330 */ HuVecF lbl_1_data_330 = { 0.0f, 0.0f, 0.0f }; /* fn_1_4F80; mdmini lbl_1_data_75C */
/* 0x33C */ HuVecF lbl_1_data_33C[4] = { 0 }; /* fn_1_4F80; mdmini lbl_1_data_768 */

/* 1182 insns */
BOOL fn_1_4F80(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    MDCAMERA_WORK *camera; //r28
    
    HuVecF *posP[4][2]; //sp+0x48
    HuVecF *rotP[4][2]; //sp+0x28
    HuVecF *scaleP[4][2]; //sp+0x8
    
    
    model = sys->model;
    
    camera = sys->camera;
    if(!lbl_1_bss_1) {
        lbl_1_data_330.x = 288;
        lbl_1_data_330.y = 64+(176*lbl_1_data_0[0]);
        lbl_1_data_330.z = lbl_1_data_0[1];
        for(i=0; i<4; i++) {
            lbl_1_data_33C[i].x = (288-((3*lbl_1_data_0[2])/2.0f))+(i*lbl_1_data_0[2]);
            lbl_1_data_33C[i].y = lbl_1_data_330.y;
            lbl_1_data_33C[i].z = lbl_1_data_0[3];
        }
        lbl_1_bss_1 = TRUE;
    }
    for(i=0; i<4; i++) {
        posP[i][0] = model->posP[i+MDMODEL_MAN];
        posP[i][1] = model->posP[i+MDMODEL_COM];
        
        rotP[i][0] = model->rotP[i+MDMODEL_MAN];
        rotP[i][1] = model->rotP[i+MDMODEL_COM];
        
        scaleP[i][0] = model->scaleP[i+MDMODEL_MAN];
        scaleP[i][1] = model->scaleP[i+MDMODEL_COM];
    }
    if(!sys->unk39C) {
        for(i=0; i<4; i++) {
            if(i < sys->playerNum+1) {
                lbl_1_bss_164[i][0] = 0;
            } else {
                lbl_1_bss_164[i][0] = 1;
            }
            if(i < sys->prevPlayerNum+1) {
                lbl_1_bss_164[i][1] = 0;
            } else {
                lbl_1_bss_164[i][1] = 1;
            }
        }
        if(param == 0) {
            Hu3D2Dto3D(&lbl_1_data_330, camera->camera[1].bit, &lbl_1_bss_19C);
            for(i=0; i<4; i++) {
                Hu3D2Dto3D(&lbl_1_data_33C[i], camera->camera[1].bit, &lbl_1_bss_16C[i]);
            }
            for(i=0; i<4; i++) {
                posP[i][lbl_1_bss_164[i][0]]->x = lbl_1_bss_19C.x;
                posP[i][lbl_1_bss_164[i][0]]->y = lbl_1_bss_19C.y;
                posP[i][lbl_1_bss_164[i][0]]->z = lbl_1_bss_19C.z;
                rotP[i][lbl_1_bss_164[i][0]]->x = 0;
                rotP[i][lbl_1_bss_164[i][0]]->y = 0;
                rotP[i][lbl_1_bss_164[i][0]]->z = 0;
                scaleP[i][lbl_1_bss_164[i][0]]->x = 0;
                scaleP[i][lbl_1_bss_164[i][0]]->y = 0;
                scaleP[i][lbl_1_bss_164[i][0]]->z = 0;
                if(lbl_1_bss_164[i][0] == 0) {
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_MAN]);
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_COM]);
                } else if(lbl_1_bss_164[i][0] == 1) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_MAN]);
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_COM]);
                }
            }
        } else if(param != 1 && (param == 2 || param == 3)) {
            for(i=0; i<4; i++) {
                if(lbl_1_bss_164[i][0] != lbl_1_bss_164[i][1]) {
                    posP[i][lbl_1_bss_164[i][1]]->x = lbl_1_bss_19C.x;
                    posP[i][lbl_1_bss_164[i][1]]->y = lbl_1_bss_19C.y;
                    posP[i][lbl_1_bss_164[i][1]]->z = lbl_1_bss_19C.z;
                    rotP[i][lbl_1_bss_164[i][1]]->x = 0;
                    rotP[i][lbl_1_bss_164[i][1]]->y = 0;
                    rotP[i][lbl_1_bss_164[i][1]]->z = 0;
                    scaleP[i][lbl_1_bss_164[i][1]]->x = 0;
                    scaleP[i][lbl_1_bss_164[i][1]]->y = 0;
                    scaleP[i][lbl_1_bss_164[i][1]]->z = 0;
                    Hu3DModelDispOn(model->mdlId[i+MDMODEL_MAN+(lbl_1_bss_164[i][0]*4)]);
                }
            }
            lbl_1_bss_160 = 200;
            lbl_1_bss_15C = 90;
            for(i=0; i<4; i++) {
                lbl_1_bss_12C[i] = lbl_1_bss_16C[i];
                lbl_1_bss_12C[i].z -= lbl_1_bss_160;
            }
        }
        sys->unk39C = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 30);
        for(i=0; i<4; i++) {
            MdMathLerp(&posP[i][lbl_1_bss_164[i][0]]->x, lbl_1_bss_19C.x, lbl_1_bss_16C[i].x, sys->t);
            MdMathLerp(&posP[i][lbl_1_bss_164[i][0]]->y, lbl_1_bss_19C.y, lbl_1_bss_16C[i].y, sys->t);
            MdMathLerp(&posP[i][lbl_1_bss_164[i][0]]->z, lbl_1_bss_19C.z, lbl_1_bss_16C[i].z, sys->t);
            MdMathLerpScale(scaleP[i][lbl_1_bss_164[i][0]], 0, 1, sys->t);
        }
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->time, &sys->t, 15);
        for(i=0; i<4; i++) {
            MdMathLerpScale(scaleP[i][lbl_1_bss_164[i][0]], 1, 0, sys->t);
        }
    } else if(param == 2 || param == 3) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->time, &sys->t, 20);
        if(param == 2) {
            MdMathLerp(&lbl_1_bss_15C, 90, 270, sys->t);
        } else if(param == 3) {
            MdMathLerp(&lbl_1_bss_15C, 90, -90, sys->t);
        }
        for(i=0; i<4; i++) {
            if(lbl_1_bss_164[i][0] != lbl_1_bss_164[i][1]) {
                MdMathLerpScale(scaleP[i][lbl_1_bss_164[i][1]], 1, 0, sys->t);
                posP[i][lbl_1_bss_164[i][1]]->x = lbl_1_bss_12C[i].x+(lbl_1_bss_160*HuCos(lbl_1_bss_15C));
                posP[i][lbl_1_bss_164[i][1]]->y = lbl_1_bss_12C[i].y;
                posP[i][lbl_1_bss_164[i][1]]->z = lbl_1_bss_12C[i].z+(lbl_1_bss_160*HuSin(lbl_1_bss_15C));
                MdMathLerpScale(scaleP[i][lbl_1_bss_164[i][0]], 0, 1, sys->t);
                posP[i][lbl_1_bss_164[i][0]]->x = lbl_1_bss_12C[i].x+(lbl_1_bss_160*HuCos(180.0f+lbl_1_bss_15C));
                posP[i][lbl_1_bss_164[i][0]]->y = lbl_1_bss_12C[i].y;
                posP[i][lbl_1_bss_164[i][0]]->z = lbl_1_bss_12C[i].z+(lbl_1_bss_160*HuSin(180.0f+lbl_1_bss_15C));
            }
        }
        MdProcTbl[6](param);
    }
    for(i=0; i<4; i++) {
        fn_1_942C(i+MDMODEL_MAN, 1);
        fn_1_942C(i+MDMODEL_COM, 1);
    }
    if(sys->time >= 1) {
        if(param != 0) {
            if(param == 1) {
                for(i=0; i<4; i++) {
                    Hu3DModelDispOff(model->mdlId[i+MDMODEL_MAN+(lbl_1_bss_164[i][0]*4)]);
                }
            } else if(param == 2 || param == 3) {
                for(i=0; i<4; i++) {
                    if(lbl_1_bss_164[i][0] != lbl_1_bss_164[i][1]) {
                        Hu3DModelDispOff(model->mdlId[i+MDMODEL_MAN+(lbl_1_bss_164[i][1]*4)]);
                    }
                }
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 581 insns */
BOOL fn_1_61F8(int param)
{
    HuVec2f *sprPos; //r31
    MDSPRITE_WORK *sprite; //r30
    HUSPRGRPID grpId; //r29
    HuVec2f *sprScale; //r28
    MDMODEL_WORK *model;

    sprite = sys->sprite;
    model = sys->model;
    grpId = sprite->grpId[MDSPR_GRP_1];
    if(!lbl_1_bss_2) {
        lbl_1_bss_FC[0].x = 112;
        lbl_1_bss_FC[1].x = 464;
        lbl_1_bss_FC[0].y = 64+(176*lbl_1_data_0[0]);
        lbl_1_bss_FC[1].y = lbl_1_bss_FC[0].y;
        lbl_1_bss_FC[2].x = -128;
        lbl_1_bss_FC[3].x = 704;
        lbl_1_bss_FC[2].y = lbl_1_bss_FC[0].y;
        lbl_1_bss_FC[3].y = lbl_1_bss_FC[1].y;
        lbl_1_bss_2 = TRUE;
    }
    if(!sys->unk3A0) {
        HuSprGrpPosSet(grpId, 0, 0);
        if(param == 0) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 0);
            sprPos->x = lbl_1_bss_FC[2].x;
            sprPos->y = lbl_1_bss_FC[2].y;
            HuSprDispOn(grpId, 0);
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 1);
            sprPos->x = lbl_1_bss_FC[3].x;
            sprPos->y = lbl_1_bss_FC[3].y;
            HuSprDispOn(grpId, 1);
        } else if(param == 1) {
        } else if(param == 2) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 2);
            sprPos->x = lbl_1_bss_FC[2].x;
            sprPos->y = lbl_1_bss_FC[2].y;
            HuSprTPLvlSet(grpId, 2, 0);
            HuSprDispOn(grpId, 2);
        } else if(param == 3) {
            sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 3);
            sprPos->x = lbl_1_bss_FC[3].x;
            sprPos->y = lbl_1_bss_FC[3].y;
            HuSprTPLvlSet(grpId, 3, 0);
            HuSprDispOn(grpId, 3);
        }
        sys->unk3A0 = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->ofsTime, &sys->ofsT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[2].x, lbl_1_bss_FC[0].x, sys->ofsT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[3].x, lbl_1_bss_FC[1].x, sys->ofsT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->ofsTime, &sys->ofsT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[0].x, lbl_1_bss_FC[2].x, sys->ofsT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[1].x, lbl_1_bss_FC[3].x, sys->ofsT);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_180, &sys->ofsTime, &sys->ofsT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 0);
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_1, 0);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[0].x, lbl_1_bss_FC[0].x-24, sys->ofsT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->ofsT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->ofsT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 2);
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_1, 2);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[0].x, lbl_1_bss_FC[0].x-24, sys->ofsT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->ofsT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->ofsT);
        HuSprTPLvlSet(grpId, 2, sys->ofsT);
    } else if(param == 3) {
        MdMathOscillate(MDMATH_OSC_180, &sys->ofsTime, &sys->ofsT, 15);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 1);
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_1, 1);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[1].x, 24+lbl_1_bss_FC[1].x, sys->ofsT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->ofsT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->ofsT);
        sprPos = MdSpritePosGet(sprite, MDSPR_GRP_1, 3);
        sprScale = MdSpriteScaleGet(sprite, MDSPR_GRP_1, 3);
        MdMathLerp(&sprPos->x, lbl_1_bss_FC[1].x, 24+lbl_1_bss_FC[1].x, sys->ofsT);
        MdMathLerp(&sprScale->x, 1, 1.5f, sys->ofsT);
        MdMathLerp(&sprScale->y, 1, 1.5f, sys->ofsT);
        HuSprTPLvlSet(grpId, 3, sys->ofsT);
    }
    if(sys->ofsTime >= 1) {
        if(param == 0) {
        } else if(param == 1) {
            HuSprDispOff(grpId, 0);
            HuSprDispOff(grpId, 1);
        } else if(param == 2) {
            HuSprDispOff(grpId, 2);
        } else if(param == 3) {
            HuSprDispOff(grpId, 3);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 427 insns */
BOOL fn_1_6B0C(int param)
{
    int i;
    MDMODEL_WORK *model;
    MDMESS_WORK *mess;
    MDCAMERA_WORK *cameraWork;
    HuVecF pos2D[4];
    HuVecF pos3D[4];
    cameraWork = sys->camera;
    model = sys->model;
    mess = sys->mess;
    if(!lbl_1_bss_EC) {
        lbl_1_bss_D4[0] = 48.0f;
        lbl_1_bss_D4[1] = 64.0f;
        lbl_1_bss_D4[3] = 48.0f;
        lbl_1_bss_D4[4] = -240.0f;
        for(i=0; i<4; i++) {
            lbl_1_bss_A4[i].x = 48.0f-((288.0f-((3.0f*lbl_1_data_0[2])/2.0f))+(i*lbl_1_data_0[2]));
            lbl_1_bss_A4[i].y = 64.0f-(64.0f+(176.0f*lbl_1_data_0[0]));
        }
        lbl_1_bss_EC = 1;
    }
    if(!sys->unk39C) {
        if(param == 0) {
            lbl_1_bss_F0[0] = 48.0f;
            lbl_1_bss_F0[1] = 64.0f;
        } else if(param == 1) {
            MdMessWinOpen(mess, 1, lbl_1_bss_D4[3], lbl_1_bss_D4[4], 480, 176, 1.0f, 64);
            MdMessWinHomeClear(mess, 1);
            MdMessWinAttrSet(mess, 1, 0x800);
            MdMessWinMesSet(mess, 1, MESSNUM(MESS_MPCARD_SYS, 9));
            for(i=0; i<4; i++) {
                if(i < sys->playerNum+1) {
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_MAN+i], HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrReset(model->mdlId[MDMODEL_COM+i], HU3D_ATTR_DISPOFF);
                }
            }
        }
        sys->unk39C = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->time, &sys->t, 30.0f);
        MdMathLerp(&lbl_1_bss_F0[0], lbl_1_bss_D4[0], lbl_1_bss_D4[3], sys->t);
        MdMathLerp(&lbl_1_bss_F0[1], lbl_1_bss_D4[1], lbl_1_bss_D4[4], sys->t);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 30.0f);
        MdMathLerp(&lbl_1_bss_F0[0], lbl_1_bss_D4[3], lbl_1_bss_D4[0], sys->t);
        MdMathLerp(&lbl_1_bss_F0[1], lbl_1_bss_D4[4], lbl_1_bss_D4[1], sys->t);
    }
    MdMessWinPosSet(mess, 1, lbl_1_bss_F0[0], lbl_1_bss_F0[1]);
    for(i=0; i<4; i++) {
        pos2D[i].x = lbl_1_bss_F0[0]-lbl_1_bss_A4[i].x;
        pos2D[i].y = lbl_1_bss_F0[1]-lbl_1_bss_A4[i].y;
        pos2D[i].z = lbl_1_data_0[3];
        Hu3D2Dto3D(&pos2D[i], cameraWork->camera[1].bit, &pos3D[i]);
        if(i < sys->playerNum+1) {
            *model->posP[MDMODEL_MAN+i] = pos3D[i];
            fn_1_942C(MDMODEL_MAN+i, 1);
        } else {
            *model->posP[MDMODEL_COM+i] = pos3D[i];
            fn_1_942C(MDMODEL_COM+i, 1);
        }
    }
    if(sys->time >= 1.0f) {
        if(param == 0) {
            MdMessWinClose(mess, 1);
            for(i=0; i<4; i++) {
                if(i < sys->playerNum+1) {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_MAN+i], HU3D_ATTR_DISPOFF);
                } else {
                    Hu3DModelAttrSet(model->mdlId[MDMODEL_COM+i], HU3D_ATTR_DISPOFF);
                }
            }
        } else if(param == 1) {
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 451 insns */
BOOL fn_1_71B8(int param)
{
    HuVecF *pos;
    HuVecF *rot;
    MDMODEL_WORK *model;
    MDCAMERA_WORK *cameraWork;
    Mtx *mtx;
    HuVecF *scale;
    Mtx rotMtx;
    cameraWork = sys->camera;
    model = sys->model;
    pos = model->posP[MDMODEL_BOX];
    rot = model->rotP[MDMODEL_BOX];
    scale = model->scaleP[MDMODEL_BOX];
    if(!sys->unk39C) {
        lbl_1_bss_8C[0].x = lbl_1_data_10[0];
        lbl_1_bss_8C[0].y = lbl_1_data_10[1];
        lbl_1_bss_8C[0].z = lbl_1_data_10[2];
        lbl_1_bss_68[0].x = 0.0f;
        lbl_1_bss_68[0].y = 0.0f;
        lbl_1_bss_68[0].z = 0.0f;
        Hu3D2Dto3D(&lbl_1_bss_8C[0], cameraWork->camera[0].bit, &lbl_1_bss_68[1]);
        lbl_1_bss_44[0].x = 0.0f;
        lbl_1_bss_44[0].y = 0.0f;
        lbl_1_bss_44[0].z = 0.0f;
        mtx = MdMathMatrixDir(&lbl_1_bss_68[1], &cameraWork->camera[0].pos);
        PSMTXRotRad(rotMtx, 'X', 1.5707964f);
        PSMTXConcat(*mtx, rotMtx, *mtx);
        Hu3DMtxRotGet(*mtx, &lbl_1_bss_44[1]);
        if(param == 2) {
            lbl_1_bss_8C[1].x = 288.0f;
            lbl_1_bss_8C[1].y = -384.0f;
            lbl_1_bss_8C[1].z = 2500.0f;
            Hu3D2Dto3D(&lbl_1_bss_8C[1], cameraWork->camera[0].bit, &lbl_1_bss_68[2]);
            lbl_1_bss_44[2].x = 0.0f;
            lbl_1_bss_44[2].y = -180.0f;
            lbl_1_bss_44[2].z = 0.0f;
        }
        sys->unk39C = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 60.0f);
        MdMathLerp(&pos->x, lbl_1_bss_68[0].x, lbl_1_bss_68[1].x, sys->t);
        MdMathLerp(&pos->y, lbl_1_bss_68[0].y, lbl_1_bss_68[1].y, sys->t);
        MdMathLerp(&pos->z, lbl_1_bss_68[0].z, lbl_1_bss_68[1].z, sys->t);
        MdMathLerp(&rot->x, lbl_1_bss_44[0].x, lbl_1_bss_44[1].x, sys->t);
        MdMathLerp(&rot->y, lbl_1_bss_44[0].y, lbl_1_bss_44[1].y, sys->t);
        MdMathLerp(&rot->z, lbl_1_bss_44[0].z, lbl_1_bss_44[1].z, sys->t);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->time, &sys->t, 30.0f);
        MdMathLerp(&pos->x, lbl_1_bss_68[1].x, lbl_1_bss_68[0].x, sys->t);
        MdMathLerp(&pos->y, lbl_1_bss_68[1].y, lbl_1_bss_68[0].y, sys->t);
        MdMathLerp(&pos->z, lbl_1_bss_68[1].z, lbl_1_bss_68[0].z, sys->t);
        MdMathLerp(&rot->x, lbl_1_bss_44[1].x, lbl_1_bss_44[0].x, sys->t);
        MdMathLerp(&rot->y, lbl_1_bss_44[1].y, lbl_1_bss_44[0].y, sys->t);
        MdMathLerp(&rot->z, lbl_1_bss_44[1].z, lbl_1_bss_44[0].z, sys->t);
    } else if(param == 2) {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->time, &sys->t, 60.0f);
        MdMathLerp(&pos->x, lbl_1_bss_68[0].x, lbl_1_bss_68[2].x, sys->t);
        MdMathLerp(&pos->y, lbl_1_bss_68[0].y, lbl_1_bss_68[2].y, sys->t);
        MdMathLerp(&pos->z, lbl_1_bss_68[0].z, lbl_1_bss_68[2].z, sys->t);
        MdMathLerp(&rot->x, lbl_1_bss_44[0].x, lbl_1_bss_44[2].x, sys->t);
        MdMathLerp(&rot->y, lbl_1_bss_44[0].y, lbl_1_bss_44[2].y, sys->t);
        MdMathLerp(&rot->z, lbl_1_bss_44[0].z, lbl_1_bss_44[2].z, sys->t);
        MdMathLerpScale(scale, 1.0f, 0.0f, sys->t);
    }
    fn_1_98C8();
    if(sys->time >= 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 311 insns */
BOOL fn_1_78C4(int param)
{
    MDMODEL_WORK *model;
    HuVecF *scale;
    MDCARD_REC *rec;
    HuVecF *pos;
    HuVecF *rot;
    MDCAMERA_WORK *cameraWork;
    cameraWork = sys->camera;
    model = sys->model;
    pos = model->posP[MDMODEL_FINGER];
    rot = model->rotP[MDMODEL_FINGER];
    scale = model->scaleP[MDMODEL_FINGER];
    if(!sys->unk39C) {
        if(param == 0) {
            rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
            *pos = lbl_1_bss_2F0[sys->chrSel[sys->unk3A]][3];
            *rot = lbl_1_bss_2F0[sys->chrSel[sys->unk3A]][4];
            scale->x = 0.0f;
            scale->y = 0.0f;
            scale->z = 0.0f;
            Hu3DModelAttrReset(model->mdlId[MDMODEL_FINGER], HU3D_ATTR_DISPOFF);
            if(sys->padNoEnable[sys->unk3A] == -1) {
                Hu3DAnmNoSet(model->animId[0], 4);
            } else {
                Hu3DAnmNoSet(model->animId[0], sys->padNoEnable[sys->unk3A]);
            }
        } else if(param == 1) {
        } else if(param == 2) {
        }
        sys->unk39C = TRUE;
    }
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 15.0f);
        MdMathOscillate(MDMATH_OSC_180, &sys->ofsTime, &sys->ofsT, 15.0f);
        MdMathLerpScaleOfs(scale, 0.0f, 4.0f, sys->t, 2.0f*sys->ofsT);
    } else if(param == 1) {
        MdMathOscillate(MDMATH_OSC_90, &sys->time, &sys->t, 15.0f);
        MdMathLerpScale(scale, 4.0f, 0.0f, sys->t);
    } else if(param == 2) {
        rec = &sys->unk9C[sys->chrSel[sys->unk3A]];
        *pos = lbl_1_bss_2F0[sys->chrSel[sys->unk3A]][3];
        *rot = lbl_1_bss_2F0[sys->chrSel[sys->unk3A]][4];
    }
    if(sys->time >= 1.0f) {
        if(param == 0) {
        } else if(param == 1) {
            Hu3DModelAttrSet(model->mdlId[MDMODEL_FINGER], HU3D_ATTR_DISPOFF);
        } else if(param == 2) {
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x36C */ HuVecF lbl_1_data_36C[2] = { { 64.0f, 308.0f, 1280.0f }, { 64.0f, -128.0f, 1280.0f } };

/* 194 insns */
void fn_1_7DA0(void)
{
    MDMODEL_WORK *model;
    MDCARD_STARSTATE *state;
    HuVecF *pos;
    int i;
    MDCAMERA_WORK *cameraWork;
    MDMESS_WORK *mess;
    HuVecF *rot;
    HuVecF *scale;
    model = sys->model;
    cameraWork = sys->camera;
    mess = sys->mess;
    state = (MDCARD_STARSTATE *)&sys->unk38C;
    pos = model->posP[MDMODEL_STAR];
    rot = model->rotP[MDMODEL_STAR];
    scale = model->scaleP[MDMODEL_STAR];
    while(TRUE) {
        model = sys->model;
        cameraWork = sys->camera;
        mess = sys->mess;
        state = (MDCARD_STARSTATE *)&sys->unk38C;
        pos = model->posP[MDMODEL_STAR];
        rot = model->rotP[MDMODEL_STAR];
        scale = model->scaleP[MDMODEL_STAR];
        switch(state->mode) {
            case 0:
                Hu3D2Dto3D(&lbl_1_data_36C[0], cameraWork->camera[1].bit, &lbl_1_bss_2C[0]);
                *pos = lbl_1_bss_2C[0];
                fn_1_942C(MDMODEL_STAR, 1);
                break;
            case 1:
                state->time = 0.0f;
                state->t = 0.0f;
                for(i=0; i<2; i++) {
                    Hu3D2Dto3D(&lbl_1_data_36C[i], cameraWork->camera[1].bit, &lbl_1_bss_2C[i]);
                }
                state->mode = 2;
                break;
            case 2:
                MdMathOscillate(MDMATH_OSC_90_REV, &state->time, &state->t, 60.0f);
                MdMathLerp(&pos->x, lbl_1_bss_2C[0].x, lbl_1_bss_2C[1].x, state->t);
                MdMathLerp(&pos->y, lbl_1_bss_2C[0].y, lbl_1_bss_2C[1].y, state->t);
                MdMathLerp(&pos->z, lbl_1_bss_2C[0].z, lbl_1_bss_2C[1].z, state->t);
                if(state->time >= 1.0f) {
                    state->mode = 3;
                }
                break;
            case 3:
                break;
        }
        switch(state->motMode) {
            case 0:
                break;
            case 1:
                Hu3DModelAttrSet(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[MDMODEL_STAR], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR]);
                state->motMode = 0;
                break;
            case 2:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR+1], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state->motMode = 0;
                break;
            case 3:
                Hu3DMotionShiftSet(model->mdlId[MDMODEL_STAR], model->motId[MDMODEL_MOT_STAR], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state->motMode = 0;
                break;
        }
        HuPrcVSleep();
    }
}

/* 0x384 */ HuVecF lbl_1_data_384[4] = { { -300.0f, 2200.0f, -100.0f }, { -100.0f, 2200.0f, -100.0f }, { 100.0f, 2200.0f, -100.0f }, { 300.0f, 2200.0f, -100.0f } };

/* 257 insns */
void fn_1_80A8(void)
{
    int i;
    MDMODEL_WORK *model;
    MDCAMERA *camera;
    Mtx *mtx;
    HuVecF *pos;
    HuVecF *rot;
    MDCAMERA_WORK *cameraWork;
    Mtx *dirMtx;
    Mtx boxRotMtx;
    Mtx boxMtx;
    Mtx pinRotMtx;
    Mtx pinMtx;
    HuVecF ofs;
    cameraWork = sys->camera;
    camera = &cameraWork->camera[0];
    model = sys->model;
    MdMathMatrixRotRPY(&boxRotMtx, model->rotP[MDMODEL_BOX]);
    MdMathMtxTrans(boxRotMtx, boxMtx, model->posP[MDMODEL_BOX]);
    MdMathMatrixRotRPY(&pinRotMtx, &lbl_1_data_7C);
    for(i=0; i<7; i++) {
        pos = model->posP[MDMODEL_PIN+(i*3)];
        rot = model->rotP[MDMODEL_PIN+(i*3)];
        lbl_1_bss_2F0[i][0] = *pos;
        ofs = lbl_1_data_28[i];
        ofs.y += 200.0f;
        MdMathMtxTrans(pinRotMtx, pinMtx, &ofs);
        PSMTXConcat(boxMtx, pinMtx, pinMtx);
        Hu3DMtxTransGet(pinMtx, &lbl_1_bss_2F0[i][1]);
        lbl_1_bss_2F0[i][2] = *rot;
        ofs = lbl_1_data_28[i];
        ofs.x -= 70.0f;
        ofs.y += 150.0f;
        ofs.z -= 200.0f;
        MdMathMtxTrans(pinRotMtx, pinMtx, &ofs);
        PSMTXConcat(boxMtx, pinMtx, pinMtx);
        Hu3DMtxTransGet(pinMtx, &lbl_1_bss_2F0[i][3]);
        dirMtx = MdMathMatrixDir(&lbl_1_bss_2F0[i][3], &camera->pos);
        Hu3DMtxRotGet(*dirMtx, &lbl_1_bss_2F0[i][4]);
    }
    for(i=0; i<4; i++) {
        lbl_1_bss_200[i][0] = 168.0f+(80.0f*i);
        lbl_1_bss_200[i][1] = 340.0f;
        lbl_1_bss_200[i][2] = 2000.0f;
        Hu3D2Dto3D((HuVecF *)&lbl_1_bss_200[i][0], camera->bit, (HuVecF *)&lbl_1_bss_200[i][3]);
        mtx = MdMathMatrixDir((HuVecF *)&lbl_1_bss_200[i][3], &camera->pos);
        Hu3DMtxRotGet(*mtx, (HuVecF *)&lbl_1_bss_200[i][6]);
        *(HuVecF *)&lbl_1_bss_200[i][9] = lbl_1_data_384[i];
        mtx = MdMathMatrixDir((HuVecF *)&lbl_1_bss_200[i][3], (HuVecF *)&lbl_1_bss_200[i][9]);
        Hu3DMtxRotGet(*mtx, (HuVecF *)&lbl_1_bss_200[i][12]);
    }
}


/* 789 insns */
void fn_1_84AC(void)
{
    MDCARD_REC *rec;
    int j;
    int i;
    int k;
    MDMODEL_WORK *model;
    MDCAMERA_WORK *cameraWork;
    HuVecF *pos[3];
    HuVecF *rot[3];
    HuVecF *scale[3];
    cameraWork = sys->camera;
    model = sys->model;
    rec = sys->unk9C;
    for(i=0; i<7; i++, rec++) {
        for(j=0; j<3; j++) {
            pos[j] = model->posP[MDMODEL_PIN+(i*3)+j];
            rot[j] = model->rotP[MDMODEL_PIN+(i*3)+j];
            scale[j] = model->scaleP[MDMODEL_PIN+(i*3)+j];
        }
        switch(rec->unk0) {
            case 0:
                break;
            case 1:
                rec->unk8 = 0.0f;
                rec->unkC = 0.0f;
                rec->unk10 = 0.0f;
                rec->unk14 = 0.0f;
                rec->unk30 = pos[0]->x;
                rec->unk34 = pos[0]->y;
                rec->unk38 = pos[0]->z;
                rec->unk3C = lbl_1_bss_2F0[i][1].x;
                rec->unk40 = lbl_1_bss_2F0[i][1].y;
                rec->unk44 = lbl_1_bss_2F0[i][1].z;
                rec->unk0 = 2;
                break;
            case 2:
                MdMathOscillate(MDMATH_OSC_90, &rec->unk8, &rec->unk10, 8.0f);
                MdMathOscillate(MDMATH_OSC_180, &rec->unkC, &rec->unk14, 8.0f);
                MdMathLerpOfs(&pos[0]->x, rec->unk30, rec->unk3C, rec->unk10, 0.75f*rec->unk14);
                MdMathLerpOfs(&pos[0]->y, rec->unk34, rec->unk40, rec->unk10, 0.75f*rec->unk14);
                MdMathLerpOfs(&pos[0]->z, rec->unk38, rec->unk44, rec->unk10, 0.75f*rec->unk14);
                for(j=1; j<3; j++) {
                    *pos[j] = *pos[0];
                }
                if(rec->unk8 >= 1.0f) {
                    rec->unk0 = 3;
                }
                break;
            case 3:
                break;
            case 4:
                rec->unk8 = 0.0f;
                rec->unkC = 0.0f;
                rec->unk10 = 0.0f;
                rec->unk14 = 0.0f;
                rec->unk30 = pos[0]->x;
                rec->unk34 = pos[0]->y;
                rec->unk38 = pos[0]->z;
                rec->unk3C = lbl_1_bss_2F0[i][0].x;
                rec->unk40 = lbl_1_bss_2F0[i][0].y;
                rec->unk44 = lbl_1_bss_2F0[i][0].z;
                rec->unk0 = 5;
                break;
            case 5:
                MdMathOscillate(MDMATH_OSC_90, &rec->unk8, &rec->unk10, 8.0f);
                MdMathLerp(&pos[0]->x, rec->unk30, rec->unk3C, rec->unk10);
                MdMathLerp(&pos[0]->y, rec->unk34, rec->unk40, rec->unk10);
                MdMathLerp(&pos[0]->z, rec->unk38, rec->unk44, rec->unk10);
                for(j=1; j<3; j++) {
                    *pos[j] = *pos[0];
                }
                if(rec->unk8 >= 1.0f) {
                    rec->unk0 = 6;
                }
                break;
            case 6:
                break;
            case 7:
                rec->unk8 = 0.0f;
                rec->unkC = 0.0f;
                rec->unk10 = 0.0f;
                rec->unk14 = 0.0f;
                rec->unk30 = pos[0]->x;
                rec->unk34 = pos[0]->y;
                rec->unk38 = pos[0]->z;
                rec->unk3C = lbl_1_bss_200[sys->unk3A][3];
                rec->unk40 = lbl_1_bss_200[sys->unk3A][4];
                rec->unk44 = lbl_1_bss_200[sys->unk3A][5];
                rec->unk48 = rot[0]->x;
                rec->unk4C = rot[0]->y;
                rec->unk50 = rot[0]->z;
                rec->unk54 = lbl_1_bss_200[sys->unk3A][6];
                rec->unk58 = lbl_1_bss_200[sys->unk3A][7];
                rec->unk5C = lbl_1_bss_200[sys->unk3A][8];
                rec->unk0 = 8;
                break;
            case 8:
                MdMathOscillate(MDMATH_OSC_90, &rec->unk8, &rec->unk10, 25.0f);
                MdMathOscillate(MDMATH_OSC_180, &rec->unkC, &rec->unk14, 25.0f);
                MdMathLerp(&pos[0]->x, rec->unk30, rec->unk3C, rec->unk10);
                MdMathLerp(&pos[0]->y, rec->unk34, rec->unk40, rec->unk10);
                MdMathLerp(&pos[0]->z, rec->unk38, rec->unk44, rec->unk10);
                MdMathLerp(&rot[0]->x, rec->unk48, rec->unk54, rec->unk10);
                MdMathLerp(&rot[0]->y, rec->unk4C, rec->unk58, rec->unk10);
                MdMathLerp(&rot[0]->z, rec->unk50, rec->unk5C, rec->unk10);
                for(j=1; j<3; j++) {
                    *pos[j] = *pos[0];
                    *rot[j] = *rot[0];
                }
                if(rec->unk8 >= 1.0f) {
                    rec->unk0 = 9;
                }
                break;
            case 9:
                break;
            case 10:
                rec->unk8 = 0.0f;
                rec->unkC = 0.0f;
                rec->unk10 = 0.0f;
                rec->unk14 = 0.0f;
                rec->unk30 = pos[0]->x;
                rec->unk34 = pos[0]->y;
                rec->unk38 = pos[0]->z;
                rec->unk3C = lbl_1_bss_2F0[i][1].x;
                rec->unk40 = lbl_1_bss_2F0[i][1].y;
                rec->unk44 = lbl_1_bss_2F0[i][1].z;
                rec->unk48 = rot[0]->x;
                rec->unk4C = rot[0]->y;
                rec->unk50 = rot[0]->z;
                rec->unk54 = lbl_1_bss_2F0[i][2].x;
                rec->unk58 = lbl_1_bss_2F0[i][2].y;
                rec->unk5C = lbl_1_bss_2F0[i][2].z;
                rec->unk0 = 11;
                break;
            case 11:
                MdMathOscillate(MDMATH_OSC_90, &rec->unk8, &rec->unk10, 25.0f);
                MdMathOscillate(MDMATH_OSC_180, &rec->unkC, &rec->unk14, 25.0f);
                MdMathLerp(&pos[0]->x, rec->unk30, rec->unk3C, rec->unk10);
                MdMathLerp(&pos[0]->y, rec->unk34, rec->unk40, rec->unk10);
                MdMathLerp(&pos[0]->z, rec->unk38, rec->unk44, rec->unk10);
                MdMathLerp(&rot[0]->x, rec->unk48, rec->unk54, rec->unk10);
                MdMathLerp(&rot[0]->y, rec->unk4C, rec->unk58, rec->unk10);
                MdMathLerp(&rot[0]->z, rec->unk50, rec->unk5C, rec->unk10);
                for(j=1; j<3; j++) {
                    *pos[j] = *pos[0];
                    *rot[j] = *rot[0];
                }
                if(rec->unk8 >= 1.0f) {
                    rec->unk0 = 12;
                }
                break;
            case 12:
                break;
            case 13:
                k = 0;
                for(j=0; j<4; j++) {
                    if(i == sys->chrSel[j]) {
                        k = j;
                        break;
                    }
                }
                rec->unk8 = 0.0f;
                rec->unkC = 0.0f;
                rec->unk10 = 0.0f;
                rec->unk14 = 0.0f;
                rec->unk30 = pos[0]->x;
                rec->unk34 = pos[0]->y;
                rec->unk38 = pos[0]->z;
                rec->unk3C = lbl_1_bss_200[k][9];
                rec->unk40 = lbl_1_bss_200[k][10];
                rec->unk44 = lbl_1_bss_200[k][11];
                rec->unk48 = rot[0]->x;
                rec->unk4C = rot[0]->y;
                rec->unk50 = rot[0]->z;
                rec->unk54 = lbl_1_bss_200[k][12];
                rec->unk58 = lbl_1_bss_200[k][13];
                rec->unk5C = lbl_1_bss_200[k][14];
                rec->unk0 = 14;
                break;
            case 14:
                MdMathOscillate(MDMATH_OSC_90_REV, &rec->unk8, &rec->unk10, 64.0f);
                MdMathLerp(&pos[0]->x, rec->unk30, rec->unk3C, rec->unk10);
                MdMathLerp(&pos[0]->y, rec->unk34, rec->unk40, rec->unk10);
                MdMathLerp(&pos[0]->z, rec->unk38, rec->unk44, rec->unk10);
                MdMathLerp(&rot[0]->x, rec->unk48, rec->unk54, rec->unk10);
                MdMathLerp(&rot[0]->y, rec->unk4C, rec->unk58, rec->unk10);
                MdMathLerp(&rot[0]->z, rec->unk50, rec->unk5C, rec->unk10);
                for(j=1; j<3; j++) {
                    *pos[j] = *pos[0];
                    *rot[j] = *rot[0];
                }
                if(rec->unk8 >= 1.0f) {
                    rec->unk0 = 15;
                }
                break;
            case 15:
                break;
        }
    }
}


/* 203 insns */
void fn_1_9100(void)
{
    MDCARD_PLAYERSPR *playerSpr; //r31
    HuVec2f *playerNoScale; //r30
    int i; //r29
    MDSPRITE_WORK *sprite; //r28
    HUSPRGRPID playerNoGrpId; //r27
    MDCAMERA_WORK *camera; //r26
    MDMODEL_WORK *model; //r25

    camera = sys->camera;
    model = sys->model;
    sprite = sys->sprite;
    playerNoGrpId = sprite->grpId[MDSPR_GRP_2];
    while(1) {
        camera = sys->camera;
        model = sys->model;
        sprite = sys->sprite;
        playerNoGrpId = sprite->grpId[MDSPR_GRP_2];
        HuSprGrpPosSet(playerNoGrpId, 0, 0);
        for(playerSpr=&sys->playerSpr[0], i=0; i<4; i++, playerSpr++) {
            playerNoScale = MdSpriteScaleGet(sprite, MDSPR_GRP_2, i);
            switch(playerSpr->mode) {
                case 0:
                    break;

                case 1:
                    HuSprDispOn(playerNoGrpId, i);
                    HuSprPosSet(playerNoGrpId, i, lbl_1_bss_200[i][0], lbl_1_bss_200[i][1]-64);
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

/* 60 insns */
void fn_1_942C(int mdlNo, int cameraNo)
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

/* 126 insns */
void fn_1_951C(void)
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

/* 109 insns */
void fn_1_9714(void)
{
    int i;
    MDSPRITE_WORK *sprite;
    HUSPRGRPID grpId;
    sprite = sys->sprite;
    grpId = sprite->grpId[MDSPR_GRP_2];
    for(i=0; i<4; i++) {
        sys->padNoEnable[i] = sys->padNoConnect[i];
        if(i > sys->playerNum) {
            sys->padNoEnable[i] = -1;
        }
    }
    for(i=0; i<4; i++) {
        sys->padEnable[i] = 0;
    }
    for(i=0; i<4; i++) {
        if(sys->padNoEnable[i] != -1) {
            sys->padEnable[sys->padNoEnable[i]] = 1;
        }
    }
    for(i=0; i<4; i++) {
        if(sys->padNoEnable[i] != -1) {
            HuSprBankSet(grpId, i, sys->padNoEnable[i]);
        } else {
            HuSprBankSet(grpId, i, 4);
        }
    }
}

/* 106 insns */
void fn_1_98C8(void)
{
    MDCARD_REC *rec;
    MDMODEL_WORK *model;
    int i;
    int j;
    HuVecF *boxPos;
    HuVecF *boxRot;
    HuVecF *pos;
    HuVecF *rot;
    Mtx boxRotMtx;
    Mtx boxMtx;
    Mtx pinRotMtx;
    Mtx pinMtx;
    model = sys->model;
    boxPos = model->posP[MDMODEL_BOX];
    boxRot = model->rotP[MDMODEL_BOX];
    MdMathMatrixRotRPY(&boxRotMtx, boxRot);
    MdMathMtxTrans(boxRotMtx, boxMtx, boxPos);
    rec = sys->unk9C;
    for(i=0; i<7; i++, rec++) {
        if(rec->unk0 != 9 && rec->unk0 != 13 && rec->unk0 != 14 && rec->unk0 != 15) {
            MdMathMatrixRotRPY(&pinRotMtx, &lbl_1_data_7C);
            MdMathMtxTrans(pinRotMtx, pinMtx, &lbl_1_data_28[i]);
            PSMTXConcat(boxMtx, pinMtx, pinMtx);
            for(j=0; j<3; j++) {
                pos = model->posP[MDMODEL_PIN+(i*3)+j];
                rot = model->rotP[MDMODEL_PIN+(i*3)+j];
                Hu3DMtxTransGet(pinMtx, pos);
                Hu3DMtxRotGet(pinMtx, rot);
            }
            rec->unk18 = *model->posP[MDMODEL_PIN+(i*3)];
            rec->unk24 = *model->rotP[MDMODEL_PIN+(i*3)];
        }
    }
}

/* 150 insns */
int fn_1_9A70(void)
{
    int result;
    result = -1;
    if(sys->padNoEnable[sys->unk3A] != -1) {
        if(sys->pad->DStkDown[sys->padNoEnable[sys->unk3A]] & PAD_BUTTON_LEFT) {
            result = 0;
        } else if(sys->pad->DStkDown[sys->padNoEnable[sys->unk3A]] & PAD_BUTTON_RIGHT) {
            result = 1;
        } else if(HuPadBtnDown[sys->padNoEnable[sys->unk3A]] & PAD_BUTTON_B) {
            result = 2;
        } else if(HuPadBtnDown[sys->padNoEnable[sys->unk3A]] & PAD_BUTTON_A) {
            result = 3;
        }
    } else {
        if((sys->flowTime % 15) == 0) {
            lbl_1_bss_4 = ++lbl_1_bss_4 % 8;
            if(lbl_1_bss_4 == 0) {
                result = 3;
            } else {
                result = frandmod(2);
            }
        }
    }
    return result;
}

/* 112 insns */
void fn_1_9CC8(int dir)
{
    int i;
    MDCARD_REC *rec;
    s8 enableF[7];
    rec = sys->unk9C;
    for(i=0; i<7; i++, rec++) {
        if(rec->unk0 == 9) {
            enableF[i] = 0;
        } else {
            enableF[i] = 1;
        }
    }
    for(i=0; i<7; i++) {
        if(dir == 0) {
            if(--sys->chrSel[sys->unk3A] == -1) {
                sys->chrSel[sys->unk3A] = 6;
            }
        } else if(dir == 1) {
            sys->chrSel[sys->unk3A] = ++sys->chrSel[sys->unk3A] % 7;
        }
        if(enableF[sys->chrSel[sys->unk3A]] == 1) {
            break;
        }
    }
}

/* 131 insns */
void fn_1_9E88(void)
{
    int i;
    s8 j;
    s8 charNo[4];
    for(i=0; i<4; i++) {
        charNo[i] = -1;
    }
    for(i=0; i<4; i++) {
        if(sys->padNoEnable[i] != -1) {
            charNo[sys->padNoEnable[i]] = sys->chrSel[i];
        } else {
            j = i;
            break;
        }
    }
    for(i=0; i<4; i++) {
        if(charNo[i] == -1) {
            charNo[i] = sys->chrSel[j];
            j++;
        }
    }
    for(i=0; i<4; i++) {
        GwPlayerConf[i].charNo = charNo[i];
        if(sys->padEnable[i] == 0) {
            GwPlayerConf[i].type = 1;
        } else {
            GwPlayerConf[i].type = 0;
        }
        GwPlayerConf[i].padNo = i;
        ((u8 *)GwCardCommon.pedestalF)[i] = sys->pedestalF[i]; /* clrlwi: retail's GwCardCommon.pedestalF was u8 */
        GwCardCommon.starNum[i] = 0;
        GwCardCommon.ztarNum[i] = 0;
    }
    GwCardCommon.boardSize = sys->boardSize;
}

/* 92 insns */
void fn_1_A094(int cmd)
{
    int pan;
    switch(cmd) {
        case MDCARD_AUD_MUS_START:
            lbl_1_bss_28 = HuAudBGMPlay(39);
            break;

        case MDCARD_AUD_MUS_STOP:
            HuAudSStreamFadeOut(lbl_1_bss_28, 1000);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
            if(cmd == 2) {
                HuAudFXPlay(0); /* MSM_SE_CMN_01 */
            } else if(cmd == 3) {
                HuAudFXPlay(2); /* MSM_SE_CMN_03 */
            } else if(cmd == 4) {
                HuAudFXPlay(1); /* MSM_SE_CMN_02 */
            } else if(cmd == 5) {
                HuAudFXPlay(3); /* MSM_SE_CMN_04 */
            } else if(cmd == 6) {
                HuAudFXPlay(1021);
            } else if(cmd == 7) {
                HuAudFXPlay(1039);
            } else if(cmd == 8) {
                HuAudFXPlay(1014);
            } else if(cmd == 9) {
                HuAudFXPlay(1137);
            } else if(cmd == 10) {
                HuAudFXPlay(1138);
            }
            break;

        case 11:
        case 12:
            pan = fn_1_A204(MDMODEL_STAR, 1);
            if(cmd == 11) {
                HuAudFXPlayPan(754, pan);
            }
            break;

        case MDCARD_AUD_ALL_STOP:
            HuAudAllStop();
            break;
    }
}

/* 46 insns */
int fn_1_A204(int mdlNo, int cameraNo)
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

/* 0x410 */ HuVecF lbl_1_data_410 = { 0.0f, 1.0f, 0.0f };

/* 100 insns */
void fn_1_A2BC(int mdlNo, int cameraNo)
{
    MDMODEL_WORK *model;
    MDCAMERA_WORK *cameraWork;
    Mtx mtx;
    HuVecF rot;
    HuVecF side;
    HuVecF up;
    HuVecF dir;
    HuVecF mdlPos;
    HuVecF camPos;
    cameraWork = sys->camera;
    model = sys->model;
    camPos = cameraWork->camera[cameraNo].pos;
    mdlPos = *model->posP[mdlNo];
    PSVECSubtract(&camPos, &mdlPos, &dir);
    PSVECNormalize(&dir, &dir);
    PSVECCrossProduct(&lbl_1_data_410, &dir, &side);
    PSVECNormalize(&side, &side);
    PSVECCrossProduct(&dir, &side, &up);
    PSVECNormalize(&up, &up);
    mtx[0][1] = up.x;
    mtx[1][1] = up.y;
    mtx[2][1] = up.z;
    mtx[0][0] = side.x;
    mtx[1][0] = side.y;
    mtx[2][0] = side.z;
    mtx[0][2] = dir.x;
    mtx[1][2] = dir.y;
    mtx[2][2] = dir.z;
    Hu3DMtxRotGet(mtx, &rot);
    model->rotP[mdlNo]->x = rot.x;
    model->rotP[mdlNo]->y = rot.y;
    model->rotP[mdlNo]->z = rot.z;
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
        { "STAR", 0 },
        { "STAGE", 0 },
        { "BOX", 0 },
        { "PIN0_MARIO", 0 },
        { "PIN1_MARIO", 0 },
        { "PIN2_MARIO", 0 },
        { "PIN0_LUIGI", 0 },
        { "PIN1_LUIGI", 0 },
        { "PIN2_LUIGI", 0 },
        { "PIN0_PEACH", 0 },
        { "PIN1_PEACH", 0 },
        { "PIN2_PEACH", 0 },
        { "PIN0_YOSHI", 0 },
        { "PIN1_YOSHI", 0 },
        { "PIN2_YOSHI", 0 },
        { "PIN0_WARIO", 0 },
        { "PIN1_WARIO", 0 },
        { "PIN2_WARIO", 0 },
        { "PIN0_DAISY", 0 },
        { "PIN1_DAISY", 0 },
        { "PIN2_DAISY", 0 },
        { "PIN0_WALUIGI", 0 },
        { "PIN1_WALUIGI", 0 },
        { "PIN2_WALUIGI", 0 },
        { "MAN0", 0 },
        { "MAN1", 0 },
        { "MAN2", 0 },
        { "MAN3", 0 },
        { "COM0", 0 },
        { "COM1", 0 },
        { "COM2", 0 },
        { "COM3", 0 },
        { "FINGER", 0 },
        { "CARD_ROOT", 0 },
        { "CARD_ITEM", 0 },
        { "CARD_EVENT", 0 },
        { "CARD_KOOPA", 0 },
        { "CARD_STAR", 1 },
        { "FONTBGFILTER", 0 }
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
                HuSprPosSet(grpId, MDSPR_CURSOR_LR_R, 32, 0);
                HuSprPosSet(grpId, MDSPR_CURSOR_LR_L, -32, 0);
                sprRot_S1133 += 2;
                MdMathAngleClamp(&sprRot_S1133);
                HuSprGrpZRotSet(grpId, sprRot_S1133);
                Hu3D3Dto2D(pos, camera->camera[mdlInfoP_S1131->cameraNo].bit, &pos2D);
                HuSprGrpPosSet(grpId, pos2D.x, pos2D.y);
                if(attr & HU3D_ATTR_DISPOFF) {
                    HuSprAttrSet(grpId, MDSPR_CURSOR_LR_R, HUSPR_ATTR_ADDCOL);
                    HuSprAttrSet(grpId, MDSPR_CURSOR_LR_L, HUSPR_ATTR_ADDCOL);
                    HuSprGrpTPLvlSet(grpId, 0.4f);
                } else {
                    HuSprAttrReset(grpId, MDSPR_CURSOR_LR_R, HUSPR_ATTR_ADDCOL);
                    HuSprAttrReset(grpId, MDSPR_CURSOR_LR_L, HUSPR_ATTR_ADDCOL);
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

/* --- .bss declared last (lowest addresses; MdPosAdjustMode's statics are 0x8-0x27) --- */
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x3 gap_05_00000003_bss (0x1): alignment gap */
/* 0x2 */ s8 lbl_1_bss_2; /* fn_1_61F8: lbl_1_bss_FC set */
/* 0x1 */ s8 lbl_1_bss_1; /* fn_1_4F80: positions set */
/* 0x0 */ u8 lbl_1_bss_0;

