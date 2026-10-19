/*
 * mdoptiondll mdoption.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mdoptiondll/asm/REL/mdoptiondll/mdoption.s.
 */

#include "REL/mdoptionDll.h"

#ifdef __MWERKS__
/* fork D: retail calls HuAudSStreamAllFadeOut unprototyped (implicit int: fn_1_6328 copies its
 * result, mr r5,r3); hide only that prototype from CodeWarrior. */
#define HuAudSStreamAllFadeOut HuAudSStreamAllFadeOut_Prototyped
#endif
#include "game/audio.h"
#ifdef __MWERKS__
#undef HuAudSStreamAllFadeOut
#endif
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "math.h"
#include "msm.h"
#include "messnum/syshelp.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const float lbl_1_rodata_10 = 0.9f; /* 0x10 */
/* 0x14 lbl_1_rodata_14 (0x10): 0x00000003 0x00000000 0x00000001 0x00000002 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_24 = 95.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 378.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 0.75f; /* 0x2C */
/* 0x30 lbl_1_rodata_30 (0x20): 0xFFFFFFFF 0xFFFFFFFF 0x001F003F 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_50 = 0.0f; /* 0x50 */
/* 0x54 lbl_1_rodata_54 (0xC): 0x00000000 0x00000000 0x44A00000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_60 = 3375.0f; /* 0x60 */
static const float lbl_1_rodata_64 = -50.0f; /* 0x64 */
static const float lbl_1_rodata_68 = 90.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 25.0f; /* 0x6C */
static const float lbl_1_rodata_70 = 2550.0f; /* 0x70 */
static const float lbl_1_rodata_74 = 120.0f; /* 0x74 */
static const float lbl_1_rodata_78 = 1.0f; /* 0x78 */
static const float lbl_1_rodata_7C = 135.0f; /* 0x7C */
static const float lbl_1_rodata_80 = 700.0f; /* 0x80 */
static const float lbl_1_rodata_84 = 110.0f; /* 0x84 */
static const float lbl_1_rodata_88 = 250.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 310.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 400.0f; /* 0x90 */
static const float lbl_1_rodata_94 = 260.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 550.0f; /* 0x98 */
static const double lbl_1_rodata_A0 = 3.141592653589793; /* 0xA0 */
static const float lbl_1_rodata_A8 = 360.0f; /* 0xA8 */
static const double lbl_1_rodata_B0 = 180.0; /* 0xB0 */
static const float lbl_1_rodata_B8 = 288.0f; /* 0xB8 */
static const float lbl_1_rodata_BC = 232.0f; /* 0xBC */
static const float lbl_1_rodata_C0 = 230.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 100.0f; /* 0xC4 */
static const float lbl_1_rodata_C8 = 170.0f; /* 0xC8 */
/* 0xCC lbl_1_rodata_CC (0xC): 0x00000000 0x00000000 0x44BB8000 -- an aggregate initialiser, write it as a local */
/* 0xD8 lbl_1_rodata_D8 (0xC): 0x00000000 0x00000000 0x44BB8000 -- an aggregate initialiser, write it as a local */
/* 0xE4 lbl_1_rodata_E4 (0xC): 0x00000000 0x00000000 0x44BB8000 -- an aggregate initialiser, write it as a local */
/* 0xF0 lbl_1_rodata_F0 (0xC): 0x00000000 0x00000000 0x44BB8000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_FC = 50.0f; /* 0xFC */
static const float lbl_1_rodata_100 = 15.0f; /* 0x100 */
static const float lbl_1_rodata_104 = -1.0f; /* 0x104 */
static const float lbl_1_rodata_108 = 0.4f; /* 0x108 */
static const float lbl_1_rodata_10C = 64.0f; /* 0x10C */
static const float lbl_1_rodata_110 = 96.0f; /* 0x110 */
static const float lbl_1_rodata_114 = 128.0f; /* 0x114 */
static const float lbl_1_rodata_118 = 126.0f; /* 0x118 */
static const float lbl_1_rodata_11C = 108.0f; /* 0x11C */
static const float lbl_1_rodata_120 = 48.0f; /* 0x120 */
static const float lbl_1_rodata_124 = 144.0f; /* 0x124 */
static const float lbl_1_rodata_128 = 2.0f; /* 0x128 */
/* 0x130 lbl_1_rodata_130 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_138 = 0.5f; /* 0x138 */
static const float lbl_1_rodata_13C = 40.0f; /* 0x13C */
static const float lbl_1_rodata_140 = 1000.0f; /* 0x140 */
static const float lbl_1_rodata_144 = 200.0f; /* 0x144 */
static const float lbl_1_rodata_148 = 600.0f; /* 0x148 */
static const float lbl_1_rodata_14C = 450.0f; /* 0x14C */
static const float lbl_1_rodata_150 = -400.0f; /* 0x150 */
static const float lbl_1_rodata_154 = 300.0f; /* 0x154 */
static const float lbl_1_rodata_158 = -500.0f; /* 0x158 */
static const float lbl_1_rodata_15C = 0.7f; /* 0x15C */
static const float lbl_1_rodata_160 = 45.0f; /* 0x160 */
static const float lbl_1_rodata_164 = 0.32f; /* 0x164 */
static const float lbl_1_rodata_168 = 0.8f; /* 0x168 */
static const float lbl_1_rodata_16C = 180.0f; /* 0x16C */
static const float lbl_1_rodata_170 = 320.0f; /* 0x170 */
static const float lbl_1_rodata_174 = 280.0f; /* 0x174 */
static const float lbl_1_rodata_178 = -370.0f; /* 0x178 */
static const float lbl_1_rodata_17C = -160.0f; /* 0x17C */
static const float lbl_1_rodata_180 = -100.0f; /* 0x180 */
static const float lbl_1_rodata_184 = 60.0f; /* 0x184 */
static const float lbl_1_rodata_188 = 12.5f; /* 0x188 */
static const float lbl_1_rodata_18C = 5.0f; /* 0x18C */
static const float lbl_1_rodata_190 = -5.0f; /* 0x190 */
static const float lbl_1_rodata_194 = -20.0f; /* 0x194 */
static const float lbl_1_rodata_198 = 0.6f; /* 0x198 */
static const float lbl_1_rodata_19C = -10.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 30.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 192.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 190.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 32.0f; /* 0x1AC */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x654 */ s16 lbl_1_bss_654;
/* 0x144 */ SYS sysWork;
/* 0x140 */ SYS *sys;
/* 0x13C */ SYS *sysP;
/* 0x10C */ MDOPTION_CAMLERP lbl_1_bss_10C[2]; /* fn_1_4A88: camera lerp from/to */
/* 0x1C */ HuVecF lbl_1_bss_1C[20]; /* fn_1_6328: [0] start pos, [1] travel (only these two are used) */
/* 0x4 */ HuVecF lbl_1_bss_4[2]; /* fn_1_A324: Hu3D2Dto3D output */
/* 0x0 */ static u8 lbl_1_bss_0[0x4]; /* dtk pad_05_00000000_bss: unmapped local static, unreferenced */

static void LoadProc(void);

/* --- functions (reference order), .data placed before its first user --- */
/* 0x0 */ MD_FUNC MdFlowTbl[6] = { fn_1_B54, fn_1_CBC, fn_1_133C, fn_1_1BD8, fn_1_2160, fn_1_2D20 };
/* 0x18 */ MD_PROC MdProcTbl[5] = { fn_1_4768, fn_1_4A88, fn_1_5320, fn_1_6328, fn_1_9FD8 };

/* 491 insns */
void ObjectSetup(void)
{
    sys = &sysWork;
    sysP = sys;
    memset(sysP, 0, sizeof(SYS));
    sys->unk3E0 = 0.9f;
    sys->flowMode = 0;
    sys->loadDir = 112;
    sys->objman = omInitObjMan(512, 8192);
    omGameSysInit(sys->objman);
    sys->obj[MDOPTION_OBJ_DEBUGFONT] = omAddObjEx(sys->objman, 100, 0, 0, -1, MdObjDebugFontCreate);
    sys->obj[MDOPTION_OBJ_DEBUGFONT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDDEBUGFONT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_DEBUGFONT]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_DEBUGFONT]->data = NULL...\n");
    }
    sys->debugFont = sys->obj[MDOPTION_OBJ_DEBUGFONT]->data;
    sys->debugFont->createF = FALSE;
    sys->obj[MDOPTION_OBJ_PAD] = omAddObjEx(sys->objman, 101, 0, 0, -1, MdObjPadMain);
    sys->obj[MDOPTION_OBJ_PAD]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDPAD_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_PAD]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_PAD]->data = NULL...\n");
    }
    sys->pad = sys->obj[MDOPTION_OBJ_PAD]->data;
    sys->obj[MDOPTION_OBJ_CAMERA] = omAddObjEx(sys->objman, 102, 0, 0, -1, MdObjCameraCreate);
    sys->obj[MDOPTION_OBJ_CAMERA]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDCAMERA_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_CAMERA]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_CAMERA]->data = NULL...\n");
    }
    sys->camera = sys->obj[MDOPTION_OBJ_CAMERA]->data;
    sys->camera->createF = FALSE;
    sys->camera->debugFont = sys->debugFont;
    sys->obj[MDOPTION_OBJ_LIGHT] = omAddObjEx(sys->objman, 103, 0, 0, -1, MdObjLightCreate);
    sys->obj[MDOPTION_OBJ_LIGHT]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDLIGHT_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_LIGHT]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_LIGHT]->data = NULL...\n");
    }
    sys->light = sys->obj[MDOPTION_OBJ_LIGHT]->data;
    sys->light->createF = FALSE;
    sys->light->debugFont = sys->debugFont;
    sys->obj[MDOPTION_OBJ_SHADOW] = omAddObjEx(sys->objman, 104, 0, 0, -1, MdObjShadowCreate);
    sys->obj[MDOPTION_OBJ_SHADOW]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSHADOW_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_SHADOW]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_SHADOW]->data = NULL...\n");
    }
    sys->shadow = sys->obj[MDOPTION_OBJ_SHADOW]->data;
    sys->shadow->createF = FALSE;
    sys->shadow->debugFont = sys->debugFont;
    sys->obj[MDOPTION_OBJ_MESS] = omAddObjEx(sys->objman, 105, 0, 0, -1, MdObjMessCreate);
    sys->obj[MDOPTION_OBJ_MESS]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMESS_WORK), HU_MEMNUM_OVL);
    if(!sys->obj[MDOPTION_OBJ_MESS]->data) {
        OSReport("sys->obj[MDOPTION_OBJ_MESS]->data = NULL...\n");
    }
    sys->mess = sys->obj[MDOPTION_OBJ_MESS]->data;
    sys->mess->createF = FALSE;
    sys->sprite = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDSPRITE_WORK), HU_MEMNUM_OVL);
    if(!sys->sprite) {
        OSReport("sys->sprite = NULL...\n");
    }
    memset(sys->sprite, 0, sizeof(MDSPRITE_WORK));
    sys->model = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MDMODEL_WORK), HU_MEMNUM_OVL);
    if(!sys->model) {
        OSReport("sys->model = NULL...\n");
    }
    memset(sys->model, 0, sizeof(MDMODEL_WORK));
    MdMathStdCurveInit();
    Hu3DBGColorSet(0, 0, 0);
    while(1) {
        if(sys->debugFont->createF == TRUE && sys->camera->createF == TRUE && sys->light->createF == TRUE
            && sys->shadow->createF == TRUE && sys->mess->createF == TRUE) {
            break;
        }
        HuPrcVSleep();
    }
    GwPlayerConf[0].padNo = 0;
    GwPlayerConf[0].type = 0;
    sys->mainProc = HuPrcChildCreate(MdMain, 107, 12288, 0, sys->objman);
}

/* 45 insns */
void MdMain(void)
{
    HuVecF dummy;
    MdInit();
    while(!omSysExitReq && !sys->exitF) {
        MdFlowTbl[sys->flowMode]();
#ifdef __MWERKS__
        ObjSelectUpdate(&dummy); /* retail passes a stack address the callee ignores */
#else
        ObjSelectUpdate();
#endif
        MdOptionCursorUpdate();
        MdOptionTrigSprUpdate();
        MdOptionStoryRankUpdate();
        MdOptionWaveEffectUpdate();
        MdOptionCapsuleOrbitUpdate();
        MdOptionCapsuleOrbitOutUpdate();
        MdModelRumbleUpdate();
        MdOptionStoryRankStarUpdate();
        MdOptionSpriteTitleUpdate();
        HuPrcVSleep();
    }
    MdClose();
}

/* 61 insns */
static void LoadProc(void)
{
    OSTick tick;
    while(1) {
        switch(sys->loadState) {
            case 0:
                break;

            case 1:
                tick = OSGetTick();
                sys->loadAsyncStat = HuDataDirReadAsync(DATA_rescard);
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

/* 51 insns */
void MdInit(void)
{
    MdSpriteCreate(sys->sprite);
    HuPrcVSleep();
    MdModelCreate(sys->model, sys->camera);
    HuPrcVSleep();
    HuDataDirClose(DATA_mdoption);
    HuPrcVSleep();
    sys->unk398 = 0;
    sys->unk39C = 0;
    sys->unk68 = HuPrcChildCreate(fn_1_A324, 109, 4096, 0, sys->objman);
    HuPrcVSleep();
}

/* 37 insns */
void MdClose(void)
{
    if(!sys->skipWipeF) {
        WipeColorSet(255, 255, 255);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
    }
    fn_1_A930(11);
    MdMessKill(sys->mess);
    omOvlReturnEx(1, 1);
    HuPrcEnd();
    while(1) {
        HuPrcVSleep();
    }
}

/* 90 insns */
void fn_1_B54(void)
{
    MDSPRITE_WORK *sprite = sys->sprite;
    MDMODEL_WORK *model = sys->model;
    MDMESS_WORK *mess = sys->mess;
    int i;
    s16 *p;
    for(i=0; i<4; i++) {
        sys->unk47[i] = 0;
    }
    Hu3DModelAttrReset(model->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(model->mdlId[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(model->mdlId[131], HU3D_ATTR_DISPOFF);
    MdProcTbl[0](0);
    p = &sys->unkA4;
    *p = 0;
    WipeColorSet(255, 255, 255);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
    fn_1_A930(0);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    sys->unk0 = 0;
    sys->unk1C = 0;
    sys->flowMode = 1;
}

/* 416 insns */
void fn_1_CBC(void)
{
    MDMODEL_WORK *model = sys->model; //r29
    MDMESS_WORK *mess = sys->mess; //r31
    s32 mesTbl[4] = { 3, 0, 1, 2 };
    int result; //r30
    switch(sys->unk0) {
        case 0:
            MdProcTbl[0](0);
            if(OSGetSoundMode() == OS_SOUND_MODE_MONO) {
                if(GwCommon.soundOutputMode != 0) {
                    GwCommon.soundOutputMode = 0;
                }
            } else {
                if(GwCommon.soundOutputMode == 0) {
                    GwCommon.soundOutputMode = 1;
                }
            }
            msmSysSetOutputMode(GwCommon.soundOutputMode);
            sys->unk4D0 = 1;
            sys->unk0 = 10;
            break;

        case 10:
            result = MdProcTbl[1](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unk0 = 12;
            }
            break;

        case 12:
            MdMessWinOpen(mess, 0, 95.0f, 378.0f, 450, 64, 0.75f, 0);
            MdMessWinPad1Set(mess, 0);
            MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 0));
            HuAudFXPlay(750);
            sys->unk0 = 1;
            break;

        case 1:
            result = MdMessWinCheck(mess, 0);
            if(result) {
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 1));
                sys->unk0 = 2;
            }
            break;

        case 2:
            result = MdMessWinCheck(mess, 0);
            if(result) {
                MdMessWinHomeClear(mess, 0);
                sys->unk4D0 = 2;
                sys->unk4 = 1;
                sys->unk0 = 3;
            }
            break;

        case 3:
        case 7:
            result = MdProcTbl[2](0);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, mesTbl[sys->unk4] + MESSNUM(MESS_MPOPTION, 3));
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                sys->unk0 = 4;
            }
            break;

        case 4:
            result = fn_1_A7F8();
            model->selMode[sys->unk4+3] = 1;
            if(result == 0 || result == 1) {
                if(result == 0) {
                    sys->unk4 = (sys->unk4 != 0) ? sys->unk4-1 : 3;
                } else {
                    sys->unk4 = (sys->unk4 < 3) ? sys->unk4+1 : 0;
                }
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, mesTbl[sys->unk4] + MESSNUM(MESS_MPOPTION, 3));
                fn_1_A930(2);
                MdProcTbl[2](50);
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                sys->unk0 = 5;
            } else if(result == 3) {
                model->selMode[sys->unk4+3] = 2;
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(3);
                sys->unk0 = 0;
                sys->unk8 = 0;
                sys->flowMode = sys->unk4+2;
            }
            break;

        case 5:
            result = MdProcTbl[2](101);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 2));
                sys->unk0 = 6;
            }
            break;

        case 6:
            result = MdMessWinChoiceGet(mess, 0);
            if(result == -1 || result == 1) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 7;
            } else if(result == 0) {
                MdMessWinKill(mess, 0);
                sys->unk0 = 100;
            }
            break;

        default:
            fn_1_A930(1);
            sys->exitF = TRUE;
            break;
    }
}

/* 551 insns */
void fn_1_133C(void)
{
    MDMODEL_WORK *model = sys->model; //r29
    MDMESS_WORK *mess = sys->mess; //r30
    int result; //r31
    switch(sys->unk0) {
        case 0:
            MdProcTbl[0](0), sys->unk0 = 1;
            break;

        case 1:
            MdProcTbl[2](101), result = MdProcTbl[3](0);
            if(result == TRUE) {
                MdProcTbl[0](0), MdMessWinHomeClear(mess, 0), MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 51)), sys->unk0 = 2;
            }
            break;

        case 2:
            if(MdMessWinStatGet(mess, 0) == 0) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 3;
            }
            break;

        case 3:
        case 4:
            result = MdProcTbl[2](1);
            if(result == TRUE) {
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                MdProcTbl[0](0);
                if(sys->unk0 == 3) {
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 52));
                }
                sys->unk0 = 5;
            }
            break;

        case 5:
            result = fn_1_A7F8();
            model->selMode[sys->unk8+8] = 1;
            if(result == 0 || result == 1) {
                if(result == 0) {
                    sys->unk8 = (sys->unk8 != 0) ? sys->unk8-1 : 4;
                } else {
                    sys->unk8 = (sys->unk8 < 4) ? sys->unk8+1 : 0;
                }
                fn_1_A930(2);
                MdProcTbl[2](51);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 52));
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 6;
            } else if(result == 3) {
                model->selMode[sys->unk8+8] = 2;
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(3);
                sys->unk0 = 7;
            }
            break;

        case 6:
            MdProcTbl[2](100);
            result = MdProcTbl[3](8);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unk0 = 3;
                sys->flowMode = 1;
            }
            break;

        case 7:
            MdProcTbl[2](100);
            result = MdProcTbl[3](sys->unk8+14);
            if(result == TRUE) {
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 37));
                sys->unkC = sys->unk10 = 0;
                MdProcTbl[0](0);
                sys->unk0 = 8;
            }
            break;

        case 8:
            result = fn_1_A7F8();
            if(result == 4 || result == 5) {
                if(result == 4) {
                    sys->unkC = (sys->unkC != 0) ? sys->unkC-1 : 4;
                } else {
                    sys->unkC = (sys->unkC < 4) ? sys->unkC+1 : 0;
                }
                MdOptionTrigSprSet(result-4);
                sys->unk10 = 0;
                MdOptionCursorReset();
                MdOptionListCursorPosSet(sys->unk8, sys->unkC, sys->unk10);
                fn_1_A930(8);
                MdProcTbl[2](51);
                MdOptionMgListWinUpdate(sys->sprite, sys->unk8, sys->unkC, sys->unk10);
            } else if((HuPadDStkRep[0] & PAD_BUTTON_UP) || (HuPadDStkRep[0] & PAD_BUTTON_DOWN)) {
                if(HuPadDStkRep[0] & PAD_BUTTON_UP) {
                    MdOptionCursorSet(&sys->unk10, 0, sys->unk8, sys->unkC);
                } else {
                    MdOptionCursorSet(&sys->unk10, 1, sys->unk8, sys->unkC);
                }
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 9;
            }
            break;

        case 9:
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionMgListWinUpdate(sys->sprite, sys->unk8, sys->unkC, sys->unk10);
            } else {
                MdProcTbl[0](0);
                sys->unk0 = 10;
            }
            break;

        case 10:
            result = MdProcTbl[3](4);
            if(result == TRUE) {
                MdProcTbl[0](0), sys->unk0 = 4;
            }
            break;
    }
}

/* 354 insns */
void fn_1_1BD8(void)
{
    MDMODEL_WORK *model = sys->model; //r29
    MDMESS_WORK *mess = sys->mess; //r31
    int result; //r30
    switch(sys->unk0) {
        case 0:
            MdProcTbl[0](0);
            sys->unk0 = 1;
            sys->unk8 = GwCommon.rumbleF ^ 1;
            break;

        case 1:
            MdProcTbl[2](101);
            result = MdProcTbl[3](1);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                if(GwCommon.rumbleF) {
                    MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 7), MESSNUM(MESS_MPOPTION, 8));
                } else {
                    MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 7), MESSNUM(MESS_MPOPTION, 9));
                }
                sys->unk0 = 2;
            }
            break;

        case 2:
            if(MdMessWinStatGet(mess, 0) == 0) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 3;
            }
            break;

        case 3:
            result = MdProcTbl[2](2);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 70));
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                sys->unk0 = 4;
            }
            break;

        case 4:
            result = fn_1_A7F8();
            model->selMode[sys->unk8+13] = 1;
            if(result == 0 || result == 1) {
                sys->unk8 ^= 1;
                fn_1_A930(2);
                MdProcTbl[2](52);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 70));
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 5;
            } else if(result == 3) {
                model->selMode[sys->unk8+13] = 2;
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                GwCommon.rumbleF = sys->unk8 ^ 1;
                fn_1_A930(3);
                sys->unk0 = 6;
            }
            break;

        case 5:
            MdProcTbl[2](100);
            result = MdProcTbl[3](9);
            if(result == TRUE) {
                MdOptionCapsuleOrbitHideSet();
                MdProcTbl[0](0);
                sys->unk0 = 3;
                sys->flowMode = 1;
            }
            break;

        case 6:
            sys->unk3EC++;
            if(sys->unk3EC == 20 && sys->unk8 == 0) {
                omVibrate(0, 15, 12, 0);
            }
            MdProcTbl[2](100);
            result = MdProcTbl[3](sys->unk8+19);
            if(result == TRUE) {
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 10));
                MdProcTbl[0](0);
                sys->unk0 = 2;
            }
            break;
    }
}

/* 752 insns */
void fn_1_2160(void)
{
    MDMESS_WORK *mess; //r31
    MDMODEL_WORK *model; //r29
    int result; //r30
    model = sys->model;
    mess = sys->mess;
    switch(sys->unk0) {
        case 0:
            MdProcTbl[0](0);
            MdModelSoundTypeSet(GwCommon.soundOutputMode);
            sys->unk0 = 1;
            break;

        case 1:
            MdProcTbl[2](101), result = MdProcTbl[3](2);
            if(result == TRUE) {
                MdProcTbl[0](0), MdMessWinHomeClear(mess, 0), MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 12)), sys->unk0 = 2;
            }
            break;

        case 2:
            if(MdMessWinStatGet(mess, 0) == 0) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 3;
            }
            break;

        case 3:
        case 4:
            result = MdProcTbl[2](3);
            if(result == TRUE) {
                MdProcTbl[0](0), 0;
                if(sys->unk8 == 0) {
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 13));
                }
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                sys->unk0 = 5;
            }
            break;

        case 5:
            result = fn_1_A7F8();
            model->selMode[sys->unk8+15] = 1;
            if(result == 0 || result == 1) {
                sys->unk8 ^= 1;
                fn_1_A930(2);
                MdProcTbl[2](53);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 13));
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 6;
            } else if(result == 3) {
                if(sys->unk8 == 0) {
                    MdOptionCapsuleOrbitOutSet(GwCommon.soundOutputMode+17);
                    MdMessWinHomeClear(mess, 0);
                } else {
                    fn_1_1A278();
                }
                model->selMode[sys->unk8+15] = 2;
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(3);
                sys->unk0 = 7;
            }
            break;

        case 6:
            MdProcTbl[2](100);
            result = MdProcTbl[3](10);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unk0 = 3;
                sys->flowMode = 1;
            }
            break;

        case 7:
            MdProcTbl[2](100);
            result = MdProcTbl[3](sys->unk8+21);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unkC = sys->unk10 = sys->unk14 = 0;
                if(sys->unk8 == 0) {
                    sys->unkC = GwCommon.soundOutputMode;
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 15), sys->unkC + MESSNUM(MESS_MPOPTION, 16));
                    sys->unk0 = 8;
                } else {
                    sys->unk0 = 16;
                }
            }
            break;

        case 8:
            if(MdMessWinStatGet(mess, 0) == 0) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 9;
            }
            break;

        case 9:
            result = MdProcTbl[2](5);
            if(result == TRUE) {
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unkC + MESSNUM(MESS_MPOPTION, 72));
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                sys->unk0 = 10;
            }
            break;

        case 10:
            result = fn_1_A7F8();
            model->selMode[sys->unkC+17] = 1;
            if(result == 0 || result == 1) {
                if(result == 0) {
                    sys->unkC = (sys->unkC != 0) ? sys->unkC-1 : 2;
                } else {
                    sys->unkC = (sys->unkC < 2) ? sys->unkC+1 : 0;
                }
                fn_1_A930(2);
                MdProcTbl[2](55);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unkC + MESSNUM(MESS_MPOPTION, 72));
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 11;
            } else if(result == 3) {
                model->selMode[sys->unkC+17] = 2;
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(3);
                sys->unk0 = 12;
            }
            break;

        case 11:
            MdProcTbl[2](100);
            result = MdProcTbl[3](12);
            if(result == TRUE) {
                MdOptionCapsuleOrbitHideSet();
                MdProcTbl[0](0), sys->unk0 = 4;
            }
            break;

        case 12:
            MdProcTbl[2](100);
            result = MdProcTbl[3](sys->unkC+27);
            if(result == TRUE) {
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unkC + MESSNUM(MESS_MPOPTION, 19));
                MdProcTbl[0](0);
                sys->unk0 = 8;
            }
            break;

        case 13:
            result = fn_1_A7F8();
            if(HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_1A468(2);
            } else if(HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_1A468(3);
            } else if(HuPadDStkRep[0] & PAD_BUTTON_UP) {
                fn_1_1A468(0);
            } else if(HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
                fn_1_1A468(1);
            } else if(result == 4) {
                fn_1_1A468(4);
                MdOptionTrigSprSet(0);
            } else if(result == 5) {
                fn_1_1A468(5);
                MdOptionTrigSprSet(1);
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 14;
            } else if(result == 3) {
                fn_1_1B294();
            }
            MdOptionMgListWinUpdate(sys->sprite, 0, 0, 0);
            break;

        case 14:
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionMgListWinUpdate(sys->sprite, 0, 0, 0);
            } else {
                fn_1_1B26C();
                MdProcTbl[0](0);
                sys->unk0 = 15;
            }
            break;

        case 15:
            result = MdProcTbl[3](5);
            if(result == TRUE) {
                MdProcTbl[0](0), sys->unk0 = 4;
            }
            break;

        case 16:
            if(HuAudSStreamStatGet(lbl_1_bss_654) == 0) {
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 32));
                sys->unk0 = 13;
            }
            break;
    }
}

/* 1682 insns */
void fn_1_2D20(void)
{
    MDMODEL_WORK *model = sys->model; //r29
    MDMESS_WORK *mess = sys->mess; //r30
    int result; //r31
    GWDECASCORE *decaScore; //r28
    switch(sys->unk0) {
        case 0:
            MdProcTbl[0](0);
            sys->unk0 = 1;
            break;

        case 1:
            MdProcTbl[2](101), result = MdProcTbl[3](3);
            if(result == TRUE) {
                MdProcTbl[0](0), MdMessWinHomeClear(mess, 0), MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 23)), sys->unk0 = 2;
            }
            break;

        case 2:
            if(MdMessWinStatGet(mess, 0) == 0) {
                MdMessWinHomeClear(mess, 0);
                sys->unk0 = 3;
            }
            break;

        case 3:
        case 4:
            result = MdProcTbl[2](4);
            if(result == TRUE) {
                MdProcTbl[0](0), 0;
                if(sys->unk0 == 3) {
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 24));
                }
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                sys->unk0 = 5;
            }
            break;

        case 5:
            result = fn_1_A7F8();
            model->selMode[sys->unk8+20] = 1;
            if(result == 0 || result == 1) {
                if(result == 0) {
                    sys->unk8 = (sys->unk8 != 0) ? sys->unk8-1 : 3;
                } else {
                    sys->unk8 = (sys->unk8 < 3) ? sys->unk8+1 : 0;
                }
                fn_1_A930(2);
                MdProcTbl[2](54), MdMessWinHomeClear(mess, 0), MdMessWinMesSet(mess, 0, sys->unk8 + MESSNUM(MESS_MPOPTION, 24));
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                result = MdProcTbl[0](0);
                sys->unk0 = 6;
            } else if(result == 3) {
                model->selMode[sys->unk8+20] = 2;
                if(sys->unk8 != 0) {
                    MdMessWinHomeClear(mess, 0);
                }
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(3);
                sys->unk0 = 7;
            }
            break;

        case 6:
            MdProcTbl[2](100);
            result = MdProcTbl[3](11);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unk0 = 7;
                sys->flowMode = 1;
            }
            break;

        case 7:
            MdProcTbl[2](100), result = MdProcTbl[3](sys->unk8+23);
            if(result == TRUE) {
                MdProcTbl[0](0);
                sys->unkC = 0;
                if(sys->unk8 == 0) {
                    MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 36));
                    sys->unk0 = 8;
                } else if(sys->unk8 == 1) {
                    sys->unk0 = 10;
                } else if(sys->unk8 == 2) {
                    sys->unk0 = 21;
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 46));
                } else {
                    MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 11));
                    sys->unk0 = 26;
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 50));
                }
            }
            break;

        case 8:
            result = fn_1_A7F8();
            if((HuPadDStkRep[0] & PAD_BUTTON_UP) || (HuPadDStkRep[0] & PAD_BUTTON_DOWN)) {
                if(HuPadDStkRep[0] & PAD_BUTTON_UP) {
                    MdOptionCursorSet(&sys->unkC, 0, 0, 0);
                } else {
                    MdOptionCursorSet(&sys->unkC, 1, 0, 0);
                }
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(4);
                sys->unk0 = 9;
            }
            break;

        case 9:
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionMgListWinUpdate(sys->sprite, sys->unkC, 0, 0);
            } else {
                MdProcTbl[0](0);
                sys->unk0 = 29;
            }
            break;

        case 10:
            result = MdProcTbl[2](6);
            if(result == TRUE) {
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                MdProcTbl[0](0);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unkC + MESSNUM(MESS_MPOPTION, 75));
                sys->unk0 = 11;
            }
            break;

        case 11:
            result = fn_1_A7F8();
            model->selMode[sys->unkC+24] = 1;
            if(result == 0 || result == 1) {
                sys->unkC ^= 1;
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, sys->unkC + MESSNUM(MESS_MPOPTION, 75));
                fn_1_A930(2);
                MdProcTbl[2](56), 0;
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                MdProcTbl[0](0);
                sys->unk0 = 12;
            } else if(result == 3) {
                model->selMode[sys->unkC+24] = 2;
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(3);
                MdProcTbl[0](0), sys->unk0 = 13;
            }
            break;

        case 12:
            MdProcTbl[2](100), result = MdProcTbl[3](13);
            if(result == TRUE) {
                MdProcTbl[0](0), sys->unk0 = 3;
            }
            break;

        case 13:
            MdProcTbl[2](100), result = MdProcTbl[3](sys->unkC+30);
            if(result == TRUE) {
                MdProcTbl[0](0), sys->unk10 = sys->unk14 = 0;
                if(sys->unkC == 0) {
                    sys->unk0 = 14;
                    MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 31));
                    MdMessWinHomeClear(mess, 0);
                    MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 38), sys->unk10 + MESSNUM(MESS_MPOPTION, 29));
                } else {
                    sys->unk0 = 16;
                    MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 42));
                }
            }
            break;

        case 14:
            result = fn_1_A7F8();
            if(result == 4 || result == 5) {
                fn_1_A930(8);
                if(result == 4) {
                    sys->unk10 = (sys->unk10 != 0) ? sys->unk10-1 : 7;
                } else {
                    sys->unk10 = (sys->unk10 < 7) ? sys->unk10+1 : 0;
                }
                MdOptionTrigSprSet(result-4);
                MdMessWinHomeClear(mess, 0);
                if(sys->unk10 < 7) {
                    if(sys->unk10 == 6 && GwCommon.w07Unlock == 0) {
                        MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 38), MESSNUM(MESS_MPOPTION, 81));
                    } else {
                        MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 38), sys->unk10 + MESSNUM(MESS_MPOPTION, 29));
                    }
                    MdOptionBoardRecordUpdate(sys->sprite, sys->unk10);
                } else {
                    MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 39));
                    MdOptionBoardTotalRecordUpdate(sys->sprite);
                }
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                sys->unk0 = 15;
            }
            break;

        case 15:
            MdProcTbl[2](100);
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                if(sys->unk10 < 7) {
                    MdOptionBoardRecordUpdate(sys->sprite, sys->unk10);
                } else {
                    MdOptionBoardTotalRecordUpdate(sys->sprite);
                }
            } else {
                MdProcTbl[0](0);
                sys->unk0 = 30;
            }
            break;

        case 16:
            result = MdProcTbl[2](11);
            if(result == TRUE) {
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                MdProcTbl[0](0);
                sys->unk0 = 17;
            }
            break;

        case 17:
            result = fn_1_A7F8();
            if(result == 0) {
                sys->unk10--;
                if(sys->unk10 == -1) {
                    sys->unk10 = 3;
                } else if(sys->unk10 == 3) {
                    sys->unk10 = 6;
                }
                MdProcTbl[2](61), fn_1_A930(2);
            } else if(result == 1) {
                sys->unk10++;
                if(sys->unk10 == 4) {
                    sys->unk10 = 0;
                } else if(sys->unk10 == 7) {
                    sys->unk10 = 4;
                }
                MdProcTbl[2](61), fn_1_A930(2);
            } else if(result == 6) {
                sys->unk10 -= 4;
                if(sys->unk10 == -4) {
                    sys->unk10 = 4;
                } else if(sys->unk10 < 0) {
                    sys->unk10 += 7;
                }
                MdProcTbl[2](61);
                fn_1_A930(2);
            } else if(result == 7) {
                sys->unk10 += 4;
                if(sys->unk10 == 7) {
                    sys->unk10 = 6;
                } else if(sys->unk10 > 6) {
                    sys->unk10 -= 7;
                }
                MdProcTbl[2](61);
                fn_1_A930(2);
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                sys->unk0 = 18;
            } else if(result == 3) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                MdProcTbl[0](0);
                fn_1_A930(3);
                sys->unk0 = 19;
            }
            break;

        case 18:
            MdProcTbl[2](100), result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionStoryRecordUpdate(sys->sprite);
            } else {
                MdProcTbl[0](0), sys->unk0 = 30;
            }
            break;

        case 19:
            result = MdProcTbl[2](100);
            if(result == TRUE) {
                MdProcTbl[0](0), MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 11));
                MdOptionStoryTotalRecordUpdate(sys->sprite, sys->unk10);
                MdMessWinInsertMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 43), sys->unk10);
                sys->unk0 = 20;
            }
            break;

        case 20:
            result = fn_1_A7F8();
            if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(4);
                MdOptionStoryRecordUpdate(sys->sprite);
                sys->unk0 = 16;
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 42));
            }
            break;

        case 21:
            result = MdProcTbl[2](10);
            if(result == TRUE) {
                MdMessWinMesSet(mess, 1, MESS_SYSHELP_MENU_SEL);
                MdProcTbl[0](0), sys->unk0 = 22;
            }
            break;

        case 22:
            result = fn_1_A7F8();
            if(result == 0 || result == 1 || result == 6 || result == 7) {
                fn_1_A930(2);
                if(result == 0) {
                    sys->unkC = (sys->unkC % 5 != 0) ? sys->unkC-1 : (sys->unkC/5)*5+4;
                } else if(result == 1) {
                    sys->unkC = (sys->unkC % 5 < 4) ? sys->unkC+1 : (sys->unkC/5)*5;
                } else {
                    sys->unkC = (sys->unkC < 5) ? sys->unkC+5 : sys->unkC-5;
                }
                MdProcTbl[2](60);
            } else if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                fn_1_A930(4);
                sys->unk0 = 23;
            } else if(result == 3) {
                decaScore = &GwCommon.decaScore[sys->unkC];
                if(decaScore->charNo == -1) {
                    fn_1_A930(5);
                } else {
                    MdMessWinHomeClear(mess, 1);
                    MdMessWinHomeClear(mess, 0);
                    MdProcTbl[0](0);
                    fn_1_A930(3);
                    sys->unk0 = 24;
                }
            }
            break;

        case 23:
            MdProcTbl[2](100);
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionDecaRecordUpdate(sys->sprite);
            } else {
                MdProcTbl[0](0);
                sys->unk0 = 28;
            }
            break;

        case 24:
            result = MdProcTbl[2](100);
            if(result == TRUE) {
                u32 insertMes[8] = { -1, -1, MESSNUM(MESS_MPOPTION, 63), -1, -1, -1, -1, -1 };
                result = MdOptionDecaGetBestRecord(sys->unkC);
                insertMes[0] = result + MESSNUM(MESS_MG_DECATHLON, 38);
                insertMes[1] = GwCommon.decaScore[sys->unkC].charNo;
                MdMessWinMesSet(mess, 1, MESSNUM(MESS_SYSHELP, 11));
                MdMessWinHomeClear(mess, 0);
                MdMessWinInsertMultiMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 47), insertMes);
                MdProcTbl[0](0), MdOptionDecaTotalRecordUpdate(sys->sprite, sys->unkC);
                sys->unk0 = 25;
            }
            break;

        case 25:
            result = fn_1_A7F8();
            if(result == 2) {
                MdMessWinHomeClear(mess, 1);
                MdMessWinHomeClear(mess, 0);
                MdMessWinMesSet(mess, 0, MESSNUM(MESS_MPOPTION, 46));
                MdOptionDecaRecordUpdate(sys->sprite);
                fn_1_A930(4);
                sys->unk0 = 21;
            }
            break;

        case 26:
            result = fn_1_A7F8();
            if(result == 2) {
                MdMessWinHomeClear(mess, 0);
                MdMessWinHomeClear(mess, 1);
                fn_1_A930(4);
                sys->unk0 = 27;
            }
            break;

        case 27:
            result = MdProcTbl[4](100);
            if(result == FALSE) {
                MdOptionSdRecordUpdate(sys->sprite);
            } else {
                result = MdProcTbl[0](0);
                sys->unk0 = 28;
            }
            break;

        case 28:
        case 29:
            result = MdProcTbl[3](6);
            if(result == TRUE) {
                MdProcTbl[0](0), 0;
                if(sys->unk0 == 29) {
                    sys->unk0 = 4;
                } else {
                    sys->unk0 = 3;
                }
            }
            break;

        case 30:
            result = MdProcTbl[3](7);
            if(result == TRUE) {
                MdProcTbl[0](0), sys->unk0 = 10;
            }
            break;
    }
}

/* 200 insns */
BOOL fn_1_4768(int param)
{
    sys->unk3E4 = 0;
    sys->unk3E8 = 0;
    sys->unk418 = 0;
    sys->unk41C = 0;
    sys->unk3EC = 0;
    sys->unk3F8[0] = 0;
    sys->unk3F8[1] = 0;
    sys->unk3F8[2] = 0;
    sys->unk3F8[3] = 0;
    sys->unk408[0] = 0;
    sys->unk408[1] = 0;
    sys->unk408[2] = 0;
    sys->unk408[3] = 0;
    sys->unk420[0] = 0;
    sys->unk420[1] = 0;
    sys->unk420[2] = 0;
    sys->unk420[3] = 0;
    sys->unk420[4] = 0;
    sys->unk420[5] = 0;
    sys->unk438[0] = 0;
    sys->unk438[1] = 0;
    sys->unk438[2] = 0;
    sys->unk438[3] = 0;
    sys->unk438[4] = 0;
    sys->unk438[5] = 0;
    sys->unk450 = 0;
    sys->unk454[0] = 0;
    sys->unk454[1] = 0;
    sys->unk45C[0] = 0;
    sys->unk45C[1] = 0;
    return FALSE;
}

/* 550 insns */
BOOL fn_1_4A88(int param)
{
    MDCAMERA_WORK *cameraWork; //r28
    MDCAMERA *camera; //r30
    MDMODEL_WORK *model; //r31
    int i; //r29
    float scaleBase; //f31
    float c; //f30
    float s; //f29
    HuVecF pos; //sp+0x4C
    float scale; //sp+0xC
    float angle; //sp+0x8

    cameraWork = sys->camera;
    camera = &cameraWork->camera[0];
    model = sysP->model;
    scaleBase = sys->unk3E0;
    if(sys->unk3E4 == 0) {
        lbl_1_bss_10C[0].center = camera->center;
        lbl_1_bss_10C[0].hvr.x = camera->hvr.x;
        lbl_1_bss_10C[0].hvr.y = camera->hvr.y;
        lbl_1_bss_10C[0].hvr.z = 3375;
        lbl_1_bss_10C[1].center.x = 0;
        lbl_1_bss_10C[1].center.y = -50;
        lbl_1_bss_10C[1].center.z = 0;
        lbl_1_bss_10C[1].hvr.x = 90;
        lbl_1_bss_10C[1].hvr.y = 25;
        lbl_1_bss_10C[1].hvr.z = 2550;
        sys->unk3E4 = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_90, &sys->unk3F8[0], &sys->unk408[0], 120);
    MdMathLerp(&camera->center.x, lbl_1_bss_10C[0].center.x, lbl_1_bss_10C[1].center.x, sys->unk408[0]);
    MdMathLerp(&camera->center.y, lbl_1_bss_10C[0].center.y, lbl_1_bss_10C[1].center.y, sys->unk408[0]);
    MdMathLerp(&camera->center.z, lbl_1_bss_10C[0].center.z, lbl_1_bss_10C[1].center.z, sys->unk408[0]);
    MdMathLerp(&camera->hvr.x, lbl_1_bss_10C[0].hvr.x, lbl_1_bss_10C[1].hvr.x, sys->unk408[0]);
    MdMathLerp(&camera->hvr.y, lbl_1_bss_10C[0].hvr.y, lbl_1_bss_10C[1].hvr.y, sys->unk408[0]);
    MdMathLerp(&camera->hvr.z, lbl_1_bss_10C[0].hvr.z, lbl_1_bss_10C[1].hvr.z, sys->unk408[0]);
    MdMathLerp(&scale, 0, 1, sys->unk408[0]);
    Hu3DModelScaleSet(model->mdlId[1], scaleBase, scaleBase, scaleBase);
    Hu3DModelScaleSet(model->mdlId[2], scale*scaleBase, scale*scaleBase, scale*scaleBase);
    MdMathLerp(&angle, 135, 135, sys->unk408[0]);
    MdMathPolarCoord(&pos, *model->posP[2], 700, 700, scale*scaleBase, angle);
    Hu3DModelScaleSet(model->mdlId[3], scale, scale, scale);
    Hu3DModelPosSetV(model->mdlId[3], &pos);
    MdMathLerp(&angle, 110, 110, sys->unk408[0]);
    MdMathPolarCoord(&pos, *model->posP[2], 250, 250, scale*scaleBase, angle);
    Hu3DModelScaleSet(model->mdlId[4], scale, scale, scale);
    Hu3DModelPosSetV(model->mdlId[4], &pos);
    MdMathLerp(&angle, 310, 310, sys->unk408[0]);
    MdMathPolarCoord(&pos, *model->posP[2], 400, 400, scale*scaleBase, angle);
    Hu3DModelScaleSet(model->mdlId[5], scale, scale, scale);
    Hu3DModelPosSetV(model->mdlId[5], &pos);
    MdMathLerp(&angle, 260, 260, sys->unk408[0]);
    MdMathPolarCoord(&pos, *model->posP[2], 550, 550, scale*scaleBase, angle);
    Hu3DModelScaleSet(model->mdlId[6], scale, scale, scale);
    Hu3DModelPosSetV(model->mdlId[6], &pos);
    MdMathOscillate(MDMATH_OSC_180, &sys->unk3F8[1], &sys->unk408[1], 120);
    c = cos(M_PI*(360*sys->unk408[0])/180.0);
    s = sin(M_PI*(360*sys->unk408[0])/180.0);
    {
        HuVecF pos2D = { 0, 0, 1280 };
        HuVecF *pos2DP;
        pos2D.x = 288-((232*sys->unk408[0])*c);
        pos2D.y = 230-(100*sys->unk408[1])+(170*sys->unk408[0])+((232*sys->unk408[0])*s);
        pos2DP = &pos2D;
        pos = *pos2DP;
    }
    Hu3D2Dto3D(&pos, cameraWork->camera[1].bit, &pos);
    Hu3DModelPosSetV(model->mdlId[0], &pos);
    Hu3DModelScaleSet(model->mdlId[0], sys->unk408[0], sys->unk408[0], sys->unk408[0]);
    if(sys->unk3F8[0] >= 1) {
        sys->unk3D8 = TRUE;
        sys->unk398 = 1;
        for(i=0; i<4; i++) {
            sys->unk4DC[i] = *model->posP[i+3];
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 1026 insns */
BOOL fn_1_5320(int param)
{
    HuVecF *pos; //r31
    MDMODEL_WORK *model; //r30
    HuVecF *scale; //r29
    MDCAMERA_WORK *camera; //r27
    HuVecF *rot; //r26
    HuVecF pos2D; //sp+0x44
    HuVecF pos3D; //sp+0x38

    camera = sys->camera;
    model = sys->model;
    pos = model->posP[131];
    rot = model->rotP[131];
    scale = model->scaleP[131];
    if(sys->unk3E4 == 0) {
        if(param < 50) {
            if(param == 0) {
                *pos = *model->posP[sys->unk4+3];
            } else if(param == 1) {
                *pos = *model->posP[sys->unk8+8];
            } else if(param == 2) {
                *pos = *model->posP[sys->unk8+13];
            } else if(param == 3) {
                *pos = *model->posP[sys->unk8+15];
            } else if(param == 4) {
                *pos = *model->posP[sys->unk8+20];
            } else if(param == 5) {
                *pos = *model->posP[sys->unkC+17];
            } else if(param == 6) {
                *pos = *model->posP[sys->unkC+24];
            }
            if(param == 0) {
                if(sys->unk4 == 0) {
                    pos->x += 100;
                } else {
                    pos->x -= 100;
                }
                pos->y += 100;
            } else {
                pos->x -= 50;
                pos->y += 50;
            }
            rot->x = 0;
            rot->y = 0;
            rot->z = 0;
            scale->x = 0;
            scale->y = 0;
            scale->z = 0;
            Hu3DModelAttrReset(model->mdlId[131], HU3D_ATTR_DISPOFF);
        }
        sys->unk3E4 = TRUE;
    }
    if(param >= 100) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk3F8[0], &sys->unk408[0], 15);
        if(param == 101) {
            if(sys->unk4 == 0) {
                MdMathLerp(&scale->x, -1, 0, sys->unk408[0]);
                MdMathLerp(&scale->y, 1, 0, sys->unk408[0]);
                MdMathLerp(&scale->z, 1, 0, sys->unk408[0]);
            } else {
                MdMathLerpScale(scale, 1, 0, sys->unk408[0]);
            }
        } else {
            MdMathLerpScale(scale, 0.4f, 0, sys->unk408[0]);
        }
    } else if(param >= 50) {
        if(param == 50) {
            *pos = *model->posP[sys->unk4+3];
            if(sys->unk4 == 0) {
                scale->x = -1;
                scale->y = 1;
                scale->z = 1;
            } else {
                scale->x = 1;
                scale->y = 1;
                scale->z = 1;
            }
        } else if(param == 51) {
            *pos = *model->posP[sys->unk8+8];
        } else if(param == 52) {
            *pos = *model->posP[sys->unk8+13];
        } else if(param == 53) {
            *pos = *model->posP[sys->unk8+15];
        } else if(param == 54) {
            *pos = *model->posP[sys->unk8+20];
        } else if(param == 55) {
            *pos = *model->posP[sys->unkC+17];
        } else if(param == 56) {
            *pos = *model->posP[sys->unkC+24];
        } else if(param == 60) {
            HuVecF init = { 0, 0, 1500 };
            HuVecF *initP;
            init.x = 64.0f+(96.0f*(sys->unkC%5));
            init.y = 128.0f+(126.0f*(sys->unkC/5));
            initP = &init;
            pos2D = *initP;
            Hu3D2Dto3D(&pos2D, camera->camera[0].bit, &pos3D);
            *pos = pos3D;
        } else if(param == 61) {
            HuVecF init = { 0, 0, 1500 };
            HuVecF *initP;
            init.x = 108.0f+(96.0f*(sys->unk10%4))+(48.0f*(sys->unk10/4));
            init.y = 144.0f+(126.0f*(sys->unk10/4));
            initP = &init;
            pos2D = *initP;
            Hu3D2Dto3D(&pos2D, camera->camera[0].bit, &pos3D);
            *pos = pos3D;
        }
        if(param == 50) {
            if(sys->unk4 == 0) {
                pos->x += 100;
            } else {
                pos->x -= 100;
            }
            pos->y += 100;
        } else if(param <= 56) {
            pos->x -= 50;
            pos->y += 50;
        }
    } else {
        if(param == 10) {
            HuVecF init = { 0, 0, 1500 };
            HuVecF *initP;
            init.x = 64.0f+(96.0f*(sys->unkC%5));
            init.y = 128.0f+(126.0f*(sys->unkC/5));
            initP = &init;
            pos2D = *initP;
            Hu3D2Dto3D(&pos2D, camera->camera[0].bit, &pos3D);
            *pos = pos3D;
        } else if(param == 11) {
            HuVecF init = { 0, 0, 1500 };
            HuVecF *initP;
            init.x = 108.0f+(96.0f*(sys->unk10%4))+(48.0f*(sys->unk10/4));
            init.y = 144.0f+(126.0f*(sys->unk10/4));
            initP = &init;
            pos2D = *initP;
            Hu3D2Dto3D(&pos2D, camera->camera[0].bit, &pos3D);
            *pos = pos3D;
        }
        MdMathOscillate(MDMATH_OSC_90, &sys->unk3F8[0], &sys->unk408[0], 15);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk3F8[1], &sys->unk408[1], 15);
        if(param == 0) {
            if(sys->unk4 != 0) {
                MdMathLerpScaleOfs(scale, 0, 1, sys->unk408[0], 2*sys->unk408[1]);
            } else {
                MdMathLerpOfs(&scale->x, 0, -1, sys->unk408[0], 2*sys->unk408[1]);
                MdMathLerpOfs(&scale->y, 0, 1, sys->unk408[0], 2*sys->unk408[1]);
                MdMathLerpOfs(&scale->z, 0, 1, sys->unk408[0], 2*sys->unk408[1]);
            }
        } else {
            MdMathLerpScaleOfs(scale, 0, 0.4f, sys->unk408[0], 2*sys->unk408[1]);
        }
    }
    if(sys->unk3F8[0] >= 1) {
        if(param >= 100) {
            Hu3DModelAttrSet(model->mdlId[131], HU3D_ATTR_DISPOFF);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}
#ifdef __MWERKS__
#endif
#ifdef __MWERKS__
#endif
#ifdef __MWERKS__
#endif

/* 3884 insns */
BOOL fn_1_6328(int param)
{
    int i; //r31
    MDMODEL_WORK *model; //r30
    int no; //r29
    HuVecF *pos; //r27
    BOOL result; //r26
    BOOL procEnd; //r25
    float ofsY; //f31
    float ofsZ; //f30
    float ofsZ2; //f29
    float ofsY2; //f28
    HuVecF polarPos; //sp+0x138
    HuVecF dir; //sp+0x12C
    MDCAMERA_WORK *camera; //sp+0x44
    HuVecF *rot; //sp+0x40
    HuVecF *scale; //sp+0x3C
    float angle; //sp+0x38
    float mdlScale; //sp+0x34

    result = FALSE;
    procEnd = FALSE;
    camera = sys->camera;
    model = sys->model;
    pos = model->posP[sys->unk4+3];
    rot = model->rotP[sys->unk4+3];
    scale = model->scaleP[sys->unk4+3];
    if(!sys->unk418) {
        switch(param) {
            case 0:
            case 4:
                sys->unk3DC = 1;
                MdSpriteFadeDispSet(TRUE);
                for(i=0; i<5; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+8], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+8], pos);
                    Hu3DModelScaleSet(model->mdlId[i+8], 0.5f, 0.5f, 0.5f);
                }
                break;

            case 1:
                MdOptionCapsuleOrbitOutSet(sys->unk8+13);
                sys->unk3DC = 2;
                MdSpriteFadeDispSet(TRUE);
                for(i=0; i<2; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+13], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+13], pos);
                    Hu3DModelScaleSet(model->mdlId[i+13], 0.5f, 0.5f, 0.5f);
                }
                break;

            case 2:
            case 5:
                sys->unk3DC = 3;
                MdSpriteFadeDispSet(TRUE);
                for(i=0; i<2; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+15], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+15], pos);
                    Hu3DModelScaleSet(model->mdlId[i+15], 0.5f, 0.5f, 0.5f);
                }
                break;

            case 3:
            case 6:
                sys->unk3DC = 4;
                MdSpriteFadeDispSet(TRUE);
                for(i=0; i<4; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+20], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+20], pos);
                    Hu3DModelScaleSet(model->mdlId[i+20], 0.5f, 0.5f, 0.5f);
                }
                break;

            case 7:
                MdSpriteFadeDispSet(TRUE);
                for(i=0; i<2; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+24], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+24], pos);
                    Hu3DModelScaleSet(model->mdlId[i+24], 0.5f, 0.5f, 0.5f);
                }
                break;

            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                no = param-14;
                lbl_1_bss_1C[0] = *model->posP[no+8];
                PSVECSubtract(model->posP[3], model->posP[no+8], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 19:
            case 20:
                no = param-19;
                lbl_1_bss_1C[0] = *model->posP[no+13];
                PSVECSubtract(model->posP[4], model->posP[no+13], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 21:
            case 22:
                no = param-21;
                lbl_1_bss_1C[0] = *model->posP[no+15];
                PSVECSubtract(model->posP[5], model->posP[no+15], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 27:
            case 28:
            case 29:
                no = param-27;
                lbl_1_bss_1C[0] = *model->posP[no+17];
                PSVECSubtract(model->posP[5], model->posP[no+17], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 23:
            case 24:
            case 25:
            case 26:
                no = param-23;
                lbl_1_bss_1C[0] = *model->posP[no+20];
                PSVECSubtract(model->posP[6], model->posP[no+20], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 30:
            case 31:
                no = param-30;
                lbl_1_bss_1C[0] = *model->posP[no+24];
                PSVECSubtract(model->posP[6], model->posP[no+24], &lbl_1_bss_1C[1]);
                fn_1_A930(10);
                break;

            case 12:
                for(i=0; i<2; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+15], HU3D_ATTR_DISPOFF);
                }
                break;

            case 13:
                for(i=0; i<4; i++) {
                    Hu3DModelAttrReset(model->mdlId[i+20], HU3D_ATTR_DISPOFF);
                }
                break;
        }
        sys->unk418 = TRUE;
    }
    if(param >= 0 && param <= 3) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        no = param;
        PSVECSubtract(&Hu3DCamera[0].target, &Hu3DCamera[0].pos, &dir);
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, &dir, 1000);
        PSVECAdd(&dir, &Hu3DCamera[0].pos, &dir);
        dir.y += 50;
        MdMathLerp(&pos->x, sys->unk4DC[no].x, dir.x, sys->unk438[0]);
        MdMathLerp(&pos->y, sys->unk4DC[no].y, dir.y, sys->unk438[0]);
        MdMathLerp(&pos->z, sys->unk4DC[no].z, dir.z, sys->unk438[0]);
    } else if(param == 4 || param == 5 || param == 6 || param == 7 || param == 12 || param == 13) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
    } else if(param >= 8 && param <= 11) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        no = param-8;
        PSVECSubtract(&Hu3DCamera[0].target, &Hu3DCamera[0].pos, &dir);
        PSVECNormalize(&dir, &dir);
        PSVECScale(&dir, &dir, 1000);
        dir.y += 50;
        PSVECAdd(&dir, &Hu3DCamera[0].pos, &dir);
        MdMathLerp(&pos->x, dir.x, sys->unk4DC[no].x, sys->unk438[0]);
        MdMathLerp(&pos->y, dir.y, sys->unk4DC[no].y, sys->unk438[0]);
        MdMathLerp(&pos->z, dir.z, sys->unk4DC[no].z, sys->unk438[0]);
    } else if(param >= 14 && param <= 18) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-14;
        for(i=0; i<5; i++) {
            if(i == no) {
                if(i == 0 || i == 4) {
                    ofsY = 200;
                    ofsZ = 600;
                    ofsZ2 = 0;
                } else if(i == 1 || i == 3) {
                    ofsY = 250;
                    ofsZ = 450;
                    ofsZ2 = -400;
                } else {
                    ofsY = 300;
                    ofsZ = 400;
                    ofsZ2 = -500;
                }
                model->posP[i+8]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
                model->posP[i+8]->y = lbl_1_bss_1C[0].y+(ofsY*sys->unk438[2]);
                model->posP[i+8]->z = lbl_1_bss_1C[0].z+(ofsZ*sys->unk438[2])+(ofsZ2*sys->unk420[0]);
                if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
                    if(i == 0 || i == 4) {
                        MdOptionWaveEffectSet(1, 0);
                    }
                    if(i == 1 || i == 3) {
                        MdOptionWaveEffectSet(1, 1);
                    } else {
                        MdOptionWaveEffectSet(1, 2);
                    }
                }
                if(sys->unk420[0] > 0.7f) {
                    Hu3DModelAttrSet(model->mdlId[i+8], HU3D_ATTR_DISPOFF);
                    procEnd = MdProcTbl[4](0);
                    if(sys->unk18 == 0) {
                        MdOptionMgListUpdate(sys->sprite);
                    }
                    MdOptionMgListWinUpdate(sys->sprite, sys->unk8, 0, 0);
                }
            } else {
                if(i < no) {
                    MdMathLerp(&angle, 90.0f+(45.0f*i), 0, sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 90.0f+(45.0f*i), 360, sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+8], mdlScale, mdlScale, mdlScale);
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+8], &polarPos);
            }
        }
    } else if(param >= 19 && param <= 20) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-19;
        model->posP[no+13]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
        model->posP[no+13]->y = lbl_1_bss_1C[0].y+(200*sys->unk438[2]);
        model->posP[no+13]->z = lbl_1_bss_1C[0].z+(600*sys->unk438[2]);
        if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
            MdModelRumbleSet(no);
            MdOptionCapsuleOrbitOutSet(no+13);
            if(no == 0) {
                Hu3DModelAttrReset(model->mdlId[4], HU3D_MOTATTR_PAUSE);
            } else {
                Hu3DModelAttrSet(model->mdlId[4], HU3D_MOTATTR_PAUSE);
            }
            MdOptionWaveEffectSet(2, 0);
        }
    } else if(param >= 21 && param <= 22) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-21;
        for(i=0; i<2; i++) {
            model->posP[no+15]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
            model->posP[no+15]->y = lbl_1_bss_1C[0].y+(200*sys->unk438[2]);
            model->posP[no+15]->z = lbl_1_bss_1C[0].z+(600*sys->unk438[2]);
            if(i == no) {
                if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
                    MdOptionWaveEffectSet(3, 0);
                }
                if(sys->unk420[0] > 0.7f) {
                    Hu3DModelAttrSet(model->mdlId[i+15], HU3D_ATTR_DISPOFF);
                    if(param == 22) {
                        procEnd = MdProcTbl[4](0);
                        if(no == 1 && sys->unk18 == 0) {
                            MdOptionMgListUpdate(sys->sprite);
                        }
                        MdOptionMgListWinUpdate(sys->sprite, 0, 0, 0);
                    }
                }
            } else {
                if(i < no) {
                    MdMathLerp(&angle, 90.0f+(180.0f*i), 0, sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 90.0f+(180.0f*i), 360, sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+15], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+15], mdlScale, mdlScale, mdlScale);
            }
        }
        if(param == 21 && sys->unk420[0] > 0.5f) {
            MdMathOscillate(MDMATH_OSC_90, &sys->unk420[3], &sys->unk438[3], 40);
            for(i=0; i<3; i++) {
                MdMathLerp(&angle, 0, 90.0f+(90.0f*i), sys->unk438[3]);
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[3]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelAttrReset(model->mdlId[i+17], HU3D_ATTR_DISPOFF);
                Hu3DModelPosSetV(model->mdlId[i+17], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[3]);
                Hu3DModelScaleSet(model->mdlId[i+17], mdlScale, mdlScale, mdlScale);
            }
        }
    } else if(param >= 27 && param <= 29) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-27;
        if(no != 1) {
            ofsY = 200;
            ofsZ = 600;
            ofsZ2 = 0;
            ofsY2 = 0;
        } else {
            ofsY = 320;
            ofsZ = 280;
            ofsZ2 = -370;
            ofsY2 = -160;
        }
        if(sys->unk48C == 0) {
            if(sys->unk420[0] > 0.5f && no != 1) {
                GwCommon.soundOutputMode = sys->unkC;
                MdModelSoundTypeSet(GwCommon.soundOutputMode);
                msmSysSetOutputMode(GwCommon.soundOutputMode);
                if(GwCommon.soundOutputMode == 0) {
                    OSSetSoundMode(OS_SOUND_MODE_MONO);
                } else {
                    OSSetSoundMode(OS_SOUND_MODE_STEREO);
                }
                MdOptionCapsuleOrbitOutSet(no+17);
                MdOptionWaveEffectSet(3, 0);
            } else if(sys->unk420[0] > 0.4f && no == 1) {
                GwCommon.soundOutputMode = sys->unkC;
                MdModelSoundTypeSet(GwCommon.soundOutputMode);
                msmSysSetOutputMode(GwCommon.soundOutputMode);
                if(GwCommon.soundOutputMode == 0) {
                    OSSetSoundMode(OS_SOUND_MODE_MONO);
                } else {
                    OSSetSoundMode(OS_SOUND_MODE_STEREO);
                }
                MdOptionCapsuleOrbitOutSet(no+17);
                MdOptionWaveEffectSet(3, 1);
            }
        }
        model->posP[no+17]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
        model->posP[no+17]->y = lbl_1_bss_1C[0].y+(ofsY*sys->unk438[2])+(ofsY2*sys->unk438[1]);
        model->posP[no+17]->z = lbl_1_bss_1C[0].z+(ofsZ*sys->unk438[2])+(ofsZ2*sys->unk438[1]);
        if(param == 27) {
            model->posP[18]->x = 100*sys->unk438[1];
        }
        if(param == 29) {
            model->posP[18]->x = -100*sys->unk438[1];
        }
    } else if(param >= 23 && param <= 26) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-23;
        for(i=0; i<4; i++) {
            if(i == no) {
                if(i == 0 || i == 3) {
                    ofsY = 200;
                    ofsZ = 600;
                    ofsZ2 = 0;
                } else {
                    ofsY = 250;
                    ofsZ = 450;
                    ofsZ2 = -400;
                }
                model->posP[i+20]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
                model->posP[i+20]->y = lbl_1_bss_1C[0].y+(ofsY*sys->unk438[2]);
                model->posP[i+20]->z = lbl_1_bss_1C[0].z+(ofsZ2*sys->unk420[0])+(ofsZ*sys->unk438[2]);
                if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
                    if(i == 0 || i == 3) {
                        MdOptionWaveEffectSet(4, 0);
                    } else {
                        MdOptionWaveEffectSet(4, 1);
                    }
                }
                if(sys->unk420[0] > 0.7f) {
                    if(no != 1) {
                        procEnd = MdProcTbl[4](0);
                        if(no == 0) {
                            if(sys->unk18 == 0) {
                                MdOptionMgListUpdate(sys->sprite);
                            }
                            MdOptionMgListWinUpdate(sys->sprite, 0, 0, 0);
                        }
                        if(no == 2) {
                            MdOptionDecaRecordUpdate(sys->sprite);
                        }
                        if(no == 3) {
                            MdOptionSdRecordUpdate(sys->sprite);
                        }
                    }
                    Hu3DModelAttrSet(model->mdlId[i+20], HU3D_ATTR_DISPOFF);
                }
            } else {
                if(i < no) {
                    MdMathLerp(&angle, 90.0f+(60.0f*i), 0, sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 90.0f+(60.0f*i), 360, sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+20], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+20], mdlScale, mdlScale, mdlScale);
            }
        }
        if(param == 24) {
            if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
                MdOptionWaveEffectSet(4, 0);
            }
            if(sys->unk420[0] > 0.7f) {
                MdMathOscillate(MDMATH_OSC_90, &sys->unk420[3], &sys->unk438[3], 40);
                for(i=0; i<2; i++) {
                    MdMathLerp(&angle, 0, 90.0f+(180.0f*i), sys->unk438[3]);
                    MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[3]);
                    MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                    Hu3DModelAttrReset(model->mdlId[i+24], HU3D_ATTR_DISPOFF);
                    Hu3DModelPosSetV(model->mdlId[i+24], &polarPos);
                    MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[3]);
                    Hu3DModelScaleSet(model->mdlId[i+24], mdlScale, mdlScale, mdlScale);
                }
            }
        }
    } else if(param >= 30 && param <= 31) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk420[0], &sys->unk438[0], 40);
        MdMathOscillate(MDMATH_OSC_180, &sys->unk420[1], &sys->unk438[1], 40);
        MdMathOscillate(MDMATH_OSC_360, &sys->unk420[2], &sys->unk438[2], 40);
        no = param-30;
        for(i=0; i<2; i++) {
            if(i == no) {
                model->posP[no+24]->x = lbl_1_bss_1C[0].x+(lbl_1_bss_1C[1].x*sys->unk438[1]);
                model->posP[no+24]->y = lbl_1_bss_1C[0].y+(200*sys->unk438[2]);
                model->posP[no+24]->z = lbl_1_bss_1C[0].z+(600*sys->unk438[2]);
            } else {
                if(i < no) {
                    MdMathLerp(&angle, 90.0f+(180.0f*i), 0, sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 90.0f+(180.0f*i), 360, sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+24], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+24], mdlScale, mdlScale, mdlScale);
            }
        }
        if(sys->unk420[0] > 0.5f && sys->unk48C == 0) {
            MdOptionWaveEffectSet(4, 0);
        }
        if(sys->unk420[0] > 0.7f) {
            Hu3DModelAttrSet(model->mdlId[no+24], HU3D_ATTR_DISPOFF);
            procEnd = MdProcTbl[4](0);
            if(no == 0) {
                MdOptionBoardRecordUpdate(sys->sprite, 0);
            }
            if(no == 1) {
                MdOptionStoryRecordUpdate(sys->sprite);
            }
        }
    }
    switch(param) {
        case 0:
        case 4:
            for(i=0; i<5; i++) {
                if(param == 0) {
                    MdMathLerp(&angle, 12.5f, 90.0f+(45.0f*i), sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 360, 90.0f+(45.0f*i), sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+8], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+8], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 1:
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 5, 90.0f+(180.0f*i), sys->unk438[0]);
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+13], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+13], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 2:
        case 5:
            for(i=0; i<2; i++) {
                if(param == 2) {
                    MdMathLerp(&angle, -5, 90.0f+(180.0f*i), sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 360, 90.0f+(180.0f*i), sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+15], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+15], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 3:
        case 6:
            for(i=0; i<4; i++) {
                if(param == 3) {
                    MdMathLerp(&angle, -20, 90.0f+(60.0f*i), sys->unk438[0]);
                } else {
                    MdMathLerp(&angle, 360, 90.0f+(60.0f*i), sys->unk438[0]);
                }
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+20], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+20], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 7:
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 360, 90.0f+(180.0f*i), sys->unk438[0]);
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+24], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+24], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 8:
            for(i=0; i<5; i++) {
                MdMathLerp(&angle, 90.0f+(45.0f*i), 12.5f, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.6f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+8], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+8], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 9:
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 90.0f+(180.0f*i), 5, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.6f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+13], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+13], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 10:
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 90.0f+(180.0f*i), -5, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.6f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+15], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+15], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 11:
            for(i=0; i<4; i++) {
                MdMathLerp(&angle, 90.0f+(60.0f*i), -10, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.6f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+20], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+20], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 12:
            for(i=0; i<3; i++) {
                MdMathLerp(&angle, 90.0f+(90.0f*i), 0, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+17], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+17], mdlScale, mdlScale, mdlScale);
            }
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 360, 90.0f+(180.0f*i), sys->unk438[0]);
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, 1, angle); /* retail: radius scale 1, not mdlScale */
                Hu3DModelPosSetV(model->mdlId[i+15], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+15], mdlScale, mdlScale, mdlScale);
            }
            break;

        case 13:
            for(i=0; i<2; i++) {
                MdMathLerp(&angle, 90.0f+(180.0f*i), 0, sys->unk438[0]);
                MdMathLerp(&mdlScale, 1, 0.8f, sys->unk420[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+24], &polarPos);
                MdMathLerp(&mdlScale, 0.5f, 0.32f, sys->unk420[0]);
                Hu3DModelScaleSet(model->mdlId[i+24], mdlScale, mdlScale, mdlScale);
            }
            for(i=0; i<4; i++) {
                MdMathLerp(&angle, 360, 90.0f+(60.0f*i), sys->unk438[0]);
                MdMathLerp(&mdlScale, 0.8f, 1, sys->unk438[0]);
                MdMathPolarCoord(&polarPos, *pos, 180, 180, mdlScale, angle);
                Hu3DModelPosSetV(model->mdlId[i+20], &polarPos);
                MdMathLerp(&mdlScale, 0.32f, 0.5f, sys->unk438[0]);
                Hu3DModelScaleSet(model->mdlId[i+20], mdlScale, mdlScale, mdlScale);
            }
            break;
    }
    if(sys->unk420[0] >= 1) {
        if((param >= 14 && param <= 18) || param == 22 || param == 30 || param == 31 || param == 23 || param == 25 || param == 26) {
            if(procEnd) {
                if(param == 22) {
                    HuAudSStreamAllFadeOut(100);
                }
                result = TRUE;
                sys->unk50C = TRUE;
            }
        } else if((param >= 21 && param <= 22) || param == 24) {
            if(sys->unk420[3] >= 1) {
                result = TRUE;
            }
        } else {
            result = TRUE;
        }
        switch(param) {
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
                for(i=0; i<5; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+8], HU3D_ATTR_DISPOFF);
                }
                break;

            case 21:
            case 22:
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+15], HU3D_ATTR_DISPOFF);
                }
                break;

            case 23:
            case 24:
            case 25:
            case 26:
                for(i=0; i<4; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+20], HU3D_ATTR_DISPOFF);
                }
                break;

            case 30:
            case 31:
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+24], HU3D_ATTR_DISPOFF);
                }
                break;

            case 8:
                sys->unk3DC = 0;
                MdSpriteFadeDispSet(FALSE);
                for(i=0; i<5; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+8], HU3D_ATTR_DISPOFF);
                }
                break;

            case 9:
                sys->unk3DC = 0;
                MdSpriteFadeDispSet(FALSE);
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+13], HU3D_ATTR_DISPOFF);
                }
                break;

            case 10:
                sys->unk3DC = 0;
                MdSpriteFadeDispSet(FALSE);
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+15], HU3D_ATTR_DISPOFF);
                }
                break;

            case 11:
                sys->unk3DC = 0;
                MdSpriteFadeDispSet(FALSE);
                for(i=0; i<4; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+20], HU3D_ATTR_DISPOFF);
                }
                break;

            case 12:
                for(i=0; i<3; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+17], HU3D_ATTR_DISPOFF);
                }
                break;

            case 13:
                for(i=0; i<2; i++) {
                    Hu3DModelAttrSet(model->mdlId[i+24], HU3D_ATTR_DISPOFF);
                }
                break;
        }
        if(result == TRUE) {
            sys->unk48C = 0;
        }
    }
    return result;
}

/* 211 insns */
BOOL fn_1_9FD8(int param)
{
    HuVecF *scale; //r31 (HuSprGrpData[].scale; retail also clears the float after it, center.x)
    HuVec2f *pos; //r30
    float t; //sp+0x10
    MDCAMERA_WORK *camera; //sp+0xC
    MDMODEL_WORK *model; //sp+0x8

    camera = sys->camera;
    model = sys->model;
    pos = MdSpriteGrpPosGet(sys->sprite, 0);
    scale = (HuVecF *)MdSpriteGrpScaleGet(sys->sprite, 0);
    if(!sys->unk450) {
        if(param < 50) {
            fn_1_A930(6);
            scale->x = 0;
            scale->y = 0;
            scale->z = 0;
        }
        sys->unk450 = TRUE;
    }
    MdMathOscillate(MDMATH_OSC_180, &sys->unk454[1], &sys->unk45C[1], 30);
    if(param == 0) {
        MdMathOscillate(MDMATH_OSC_90, &sys->unk454[0], &sys->unk45C[0], 30);
        MdMathLerp(&t, 0, 1, sys->unk45C[0]);
        scale->x = scale->y = t;
        pos->x = 288-(100*sys->unk45C[1]);
        pos->y = 192+(50*sys->unk45C[1]);
    } else {
        MdMathOscillate(MDMATH_OSC_90_REV, &sys->unk454[0], &sys->unk45C[0], 30);
        MdMathLerp(&t, 1, 0, sys->unk45C[0]);
        scale->x = scale->y = t;
        pos->x = 288+(100*sys->unk45C[1]);
        pos->y = 190-(50*sys->unk45C[1]);
    }
    if(sys->unk454[0] >= 1) {
        if(param != 0) {
            MdOptionModeSpriteKill(sys->sprite);
            fn_1_A930(7);
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 0x3E0 */ HuVecF lbl_1_data_3E0[2] = { { 56.0f, 400.0f, 1280.0f }, { 64.0f, -128.0f, 1280.0f } };

/* 124 insns */
void fn_1_A324(void)
{
    MDMODEL_WORK *model; //r31
    int *state; //r30
    MDCAMERA_WORK *camera; //r29
    HuVecF *pos; //r28
    MDMESS_WORK *mess; //r27
    HuVecF *rot; //r26
    HuVecF *scale; //r25
    s16 winStat; //sp+0x8

    model = sys->model;
    camera = sys->camera;
    mess = sys->mess;
    state = &sys->unk398;
    pos = model->posP[0];
    rot = model->rotP[0];
    scale = model->scaleP[0];
    while(TRUE) {
        model = sys->model;
        camera = sys->camera;
        mess = sys->mess;
        state = &sys->unk398;
        pos = model->posP[0];
        rot = model->rotP[0];
        scale = model->scaleP[0];
        switch(state[0]) {
            case 0:
                break;
            case 1:
                Hu3D2Dto3D(&lbl_1_data_3E0[0], camera->camera[1].bit, &lbl_1_bss_4[0]);
                *pos = lbl_1_bss_4[0];
                break;
        }
        fn_1_A514(0, 1);
        winStat = MdMessWinStatGet(mess, 0);
        switch(state[1]) {
            case 0:
                break;
            case 1:
                Hu3DModelAttrSet(model->mdlId[0], HU3D_MOTATTR_LOOP);
                Hu3DModelAttrReset(model->mdlId[0], HU3D_MOTATTR_PAUSE);
                Hu3DMotionSet(model->mdlId[0], model->motId[0]);
                state[1] = 0;
                break;
            case 2:
                Hu3DMotionShiftSet(model->mdlId[0], model->motId[1], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state[1] = 0;
                break;
            case 3:
                Hu3DMotionShiftSet(model->mdlId[0], model->motId[0], 0.0f, 32.0f, HU3D_MOTATTR_LOOP);
                state[1] = 0;
                break;
        }
        HuPrcVSleep();
    }
}

/* 60 insns */
void fn_1_A514(int mdlNo, int cameraNo)
{
    MDCAMERA *camera; //r31
    HuVecF *pos; //r30
    MDMODEL_WORK *model; //r29
    HuVecF *rot; //r28
    MDCAMERA_WORK *cameraWork; //r27
    float angle; //f31
    HuVecF dir; //sp+0xC

    cameraWork = sys->camera;
    camera = &cameraWork->camera[cameraNo];
    model = sys->model;
    pos = model->posP[mdlNo];
    rot = model->rotP[mdlNo];
    dir.x = camera->pos.x - pos->x;
    dir.y = camera->pos.y - pos->y;
    dir.z = camera->pos.z - pos->z;
    angle = 180.0 * (atan2(dir.x, dir.z) / M_PI);
    rot->y = angle;
}

/* 87 insns */
void fn_1_A604(void)
{
    int i; //r31
    u16 stat; //r30
    s8 padNo[4] = { 0, 0, 0, 0 };

    sys->unk31 = 0;
    for(i=0; i<4; i++) {
        sys->padNoConnect[i] = -1;
    }
    for(i=0; i<4; i++) {
        stat = HuPadStatGet(i);
        if(stat == 0) {
            sys->padNoConnect[sys->unk31] = i;
            sys->padConnect[i] = TRUE;
            sys->unk31++;
        } else {
            sys->padConnect[i] = FALSE;
        }
    }
    sys->unk2F = sys->unk31-1;
}

/* 38 insns */
void fn_1_A760(void)
{
    MDSPRITE_WORK *sprite; //sp+0x8
    int i; //r31

    sprite = sys->sprite;
    for(i=0; i<4; i++) {
        sys->padNoEnable[i] = sys->padNoConnect[i];
        if(i > sys->unk2F) {
            sys->padNoEnable[i] = -1;
        }
    }
}

/* 78 insns */
int fn_1_A7F8(void)
{
    int dir = -1; //r31
    if(sys->pad->DStkDown[0] & PAD_BUTTON_LEFT) {
        dir = 0;
    } else if(sys->pad->DStkDown[0] & PAD_BUTTON_RIGHT) {
        dir = 1;
    } else if(sys->pad->DStkDown[0] & PAD_BUTTON_UP) {
        dir = 6;
    } else if(sys->pad->DStkDown[0] & PAD_BUTTON_DOWN) {
        dir = 7;
    } else if(HuPadBtnDown[0] & PAD_BUTTON_B) {
        dir = 2;
    } else if(HuPadBtnDown[0] & PAD_BUTTON_A) {
        dir = 3;
    } else if(HuPadBtnDown[0] & PAD_TRIGGER_L) {
        dir = 4;
    } else if(HuPadBtnDown[0] & PAD_TRIGGER_R) {
        dir = 5;
    }
    return dir;
}

/* 79 insns */
void fn_1_A930(int cmd)
{
    switch(cmd) {
        case 0:
            lbl_1_bss_654 = HuAudBGMPlay(4);
            break;

        case 1:
            HuAudSStreamFadeOut(lbl_1_bss_654, 1000);
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
                HuAudFXPlay(3); /* MSM_SE_CMN_04 */
            } else if(cmd == 5) {
                HuAudFXPlay(4); /* MSM_SE_CMN_05 */
            } else if(cmd == 6) {
                HuAudFXPlay(1445);
            } else if(cmd == 7) {
                HuAudFXPlay(1448);
            } else if(cmd == 8) {
                HuAudFXPlay(1446);
            } else if(cmd == 9) {
                HuAudFXPlay(1447);
            } else if(cmd == 10) {
                HuAudFXPlay(1449);
            }
            break;

        case 11:
            HuAudAllStop();
            break;
    }
}

