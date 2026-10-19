/*
 * rescarddll object.c -- debug font, pad, camera, light, math and message-window helpers.
 * Twins: mdoptiondll/object.c and mdomakedll/object.c.
 */

#include "REL/rescardDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/mgdata.h"
#include "game/printfunc.h"
#include "game/disp.h"
#include "math.h"
#include "stdarg.h"
#include "string.h"

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
static const float lbl_1_rodata_130 = 1.5f; /* 0x130 */
/* 0x134 lbl_1_rodata_134 (0x8): 0x00000001 0x00000002 -- an aggregate initialiser, write it as a local */
/* 0x13C lbl_1_rodata_13C (0x20): 0x00000000 0x00000000 0x44200000 0x43F00000 0x00000000 0x00000000 0x44200000 0x43F00000 -- an aggregate initialiser, write it as a local */
/* 0x15C lbl_1_rodata_15C (0x30): 0x42B40000 0x41000000 0x450CA000 0x00000000 0x42A00000 0x00000000 0x42B40000 0x00000000 0x451C4000 0x00000000 0x43160000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_18C = 0.0f; /* 0x18C */
static const float lbl_1_rodata_190 = 30.0f; /* 0x190 */
static const float lbl_1_rodata_194 = 576.0f; /* 0x194 */
static const float lbl_1_rodata_198 = 640.0f; /* 0x198 */
static const float lbl_1_rodata_19C = 480.0f; /* 0x19C */
static const float lbl_1_rodata_1A0 = 20.0f; /* 0x1A0 */
static const float lbl_1_rodata_1A4 = 20000.0f; /* 0x1A4 */
static const float lbl_1_rodata_1A8 = 1.0f; /* 0x1A8 */
static const float lbl_1_rodata_1AC = 50.0f; /* 0x1AC */
static const float lbl_1_rodata_1B0 = 10.0f; /* 0x1B0 */
static const double lbl_1_rodata_1B8 = 3.141592653589793; /* 0x1B8 */
static const double lbl_1_rodata_1C0 = 180.0; /* 0x1C0 */
static const float lbl_1_rodata_1C8 = 45.0f; /* 0x1C8 */
static const float lbl_1_rodata_1CC = -45.0f; /* 0x1CC */
static const float lbl_1_rodata_1D0 = 1000.0f; /* 0x1D0 */
static const float lbl_1_rodata_1D4 = 0.1f; /* 0x1D4 */
static const float lbl_1_rodata_1D8 = 5.0f; /* 0x1D8 */
static const float lbl_1_rodata_1DC = 0.017453292f; /* 0x1DC */
static const float lbl_1_rodata_1E0 = 180.0f; /* 0x1E0 */
static const float lbl_1_rodata_1E4 = -180.0f; /* 0x1E4 */
static const float lbl_1_rodata_1E8 = 90.0f; /* 0x1E8 */
static const double lbl_1_rodata_1F0 = 1.0; /* 0x1F0 */
static const float lbl_1_rodata_1F8 = 360.0f; /* 0x1F8 */
static const float lbl_1_rodata_1FC = 540.0f; /* 0x1FC */
static const float lbl_1_rodata_200 = 720.0f; /* 0x200 */
/* 0x208 lbl_1_rodata_208 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_210 = 2.0f; /* 0x210 */
static const float lbl_1_rodata_214 = 3.0f; /* 0x214 */
static const float lbl_1_rodata_218 = 472.0f; /* 0x218 */
static const float lbl_1_rodata_21C = -10000.0f; /* 0x21C */
static const float lbl_1_rodata_220 = 374.0f; /* 0x220 (+4 bytes: section tail alignment) */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x770 */ static s32 stdCurveSampleNum[2];
/* 0x730 */ static float stdCurveTime[2][MDMATH_CURVE_SAMPLE_MAX];
/* 0x6F0 */ static float stdCurveSlope[2][MDMATH_CURVE_SAMPLE_MAX];

static void CurveInit(int sampleNum, float *sampleT, float *sample, float *sampleSlope);
static float CurveGet(int sampleNum, float t, float *sampleT, float *sample, float *sampleSlope);
static void StdCurveInit(int idx);
static float StdCurveGet(int type, float t);

/* --- functions (reference order), .data placed before its first user --- */
/* 18 insns */
void MdObjDebugFontCreate(OMOBJ *obj)
{
    MDDEBUGFONT_WORK *debugFont = obj->data;
    MdDebugFontCreate(debugFont);
    obj->objFunc = MdObjDebugFontMain;
}

/* 0x3F8 */ static float stdCurveSample[2][MDMATH_CURVE_SAMPLE_MAX] = {
    { 0.0f, 0.1f, 0.4f, 0.2f, 1.0f },
    { 0.0f, 0.5f, 1.0f },
};

/* 67 insns */
void MdObjDebugFontMain(OMOBJ *obj)
{
    MDDEBUGFONT_WORK *debugFont = obj->data;
    static char *ctrlStr_S289[MD_DEBUGFONT_CTRL_MAX] = {
        "nop",
        "camera",
        "light",
        "model"
    };
    MdDebugFontUpdate(debugFont);

    if(HuPadBtnDown[0] & PAD_BUTTON_LEFT) {
        if(--debugFont->ctrl == -1) {
            debugFont->ctrl = MD_DEBUGFONT_CTRL_MAX-1;
        }
    }
    if(HuPadBtnDown[0] & PAD_BUTTON_RIGHT) {
        debugFont->ctrl = ++debugFont->ctrl%MD_DEBUGFONT_CTRL_MAX;
    }
    MdDebugFontPrint(debugFont, "<- %s ->", ctrlStr_S289[debugFont->ctrl]);
    MdDebugFontPrint(debugFont, "X : FONT COLOR");
    MdDebugFontPrint(debugFont, "Y : FONT ONOFF");
}

/* 31 insns */
void MdObjPadMain(OMOBJ *obj)
{
    MDPAD_WORK *pad = obj->data;
    int i;
    for(i=0; i<4; i++) {
        pad->DStkDown[i] = HuPadDStk[i] & ~pad->DStk[i];
        pad->DStk[i] = HuPadDStk[i];
    }
}

/* 18 insns */
void MdObjCameraCreate(OMOBJ *obj)
{
    MDCAMERA_WORK *camera = obj->data;
    MdCameraCreate(camera);
    obj->objFunc = MdObjCameraMain;
}

/* 15 insns */
void MdObjCameraMain(OMOBJ *obj)
{
    MDCAMERA_WORK *camera = obj->data;
    MdCameraUpdate(camera);
}

/* 18 insns */
void MdObjLightCreate(OMOBJ *obj)
{
    MDLIGHT_WORK *light = obj->data;
    MdLightCreate(light);
    obj->objFunc = MdObjLightMain;
}

/* 15 insns */
void MdObjLightMain(OMOBJ *obj)
{
    MDLIGHT_WORK *light = obj->data;
    MdLightUpdate(light);
}

/* 18 insns */
void MdObjMessCreate(OMOBJ *obj)
{
    MDMESS_WORK *mess = obj->data;
    MdMessCreate(mess);
    obj->objFunc = MdObjMessMain;
}

/* 5 insns */
void MdObjMessMain(OMOBJ *obj)
{
    MDMESS_WORK *mess = obj->data;
    MdMessMain(mess);
}

/* 25 insns */
void MdDebugFontCreate(MDDEBUGFONT_WORK *debugFont)
{
    debugFont->createF = TRUE;
    debugFont->ctrl = MD_DEBUGFONT_CTRL_CAMERA;
    debugFont->printF = FALSE;
    debugFont->color = FONT_COLOR_YELLOW;
    debugFont->posX = 16;
    debugFont->posY = 40;
    debugFont->ofsY = 216;
    debugFont->rowOfsY = 0;
    debugFont->rowH = 15;
    debugFont->size = 1.5f;
    debugFont->maxLen = 0;
}

/* 5 insns */
void MdDebugFontUpdate(MDDEBUGFONT_WORK *debugFont)
{
    debugFont->maxLen = 0;
    debugFont->rowOfsY = debugFont->ofsY;
}

/* 74 insns */
void MdDebugFontPrint(MDDEBUGFONT_WORK *debugFont, const char *str, ...)
{
    size_t len = 0;
    char outBuf[160];
    va_list arg;
    if(debugFont->printF) {
        va_start(arg, str);
        vsprintf(outBuf, str, arg);
        len = strlen(outBuf);
        if(debugFont->maxLen < len) {
            debugFont->maxLen = len;
        }
        fontcolor = debugFont->color;
        print8(debugFont->posX, debugFont->posY+debugFont->rowOfsY, debugFont->size, "%s", outBuf);
        va_end(arg);
        debugFont->rowOfsY += debugFont->rowH;
    }
}

/* 244 insns */
void MdCameraCreate(MDCAMERA_WORK *cameraWork)
{
    int bit[MDCAMERA_MAX] = { HU3D_CAM0, HU3D_CAM1 };
    MDCAMERA_RECT rect[MDCAMERA_MAX] = {
        { 0, 0, 640, 480 },
        { 0, 0, 640, 480 },
    };
    MDCAMERA_PARAM param[MDCAMERA_MAX] = {
        {
            { 90, 8, 2250 },
            { 0, 80, 0 },
        },
        {
            { 90, 0, 2500 },
            { 0, 150, 0 },
        },
    };
    float aspect[MDCAMERA_MAX];

    MDCAMERA *camera;
    int i;

    cameraWork->selCamera = 0;
    cameraWork->createF = TRUE;
    for(i=0; i<MDCAMERA_MAX; i++) {
        camera = &cameraWork->camera[i];
        camera->bit = bit[i];
        Hu3DCameraCreate(camera->bit);
        camera->pos.x = 0;
        camera->pos.y = 0;
        camera->pos.z = 0;
        camera->target.x = 0;
        camera->target.y = 0;
        camera->target.z = 0;
        camera->hvr.x = param[i].hvr.x;
        camera->hvr.y = param[i].hvr.y;
        camera->hvr.z = param[i].hvr.z;
        camera->unk50 = 0;
        camera->center.x = param[i].center.x;
        camera->center.y = param[i].center.y;
        camera->center.z = param[i].center.z;
        camera->fovy = 30;
        aspect[i] = ((rect[i].w*HU_DISP_WIDTH)/640)/((rect[i].h*480)/480);
        Hu3DCameraPerspectiveSet(camera->bit, camera->fovy, 20, 20000, aspect[i]);
        Hu3DCameraViewportSet(camera->bit, rect[i].x, rect[i].y, rect[i].w, rect[i].h, 0, 1);
        Hu3DCameraScissorSet(camera->bit, rect[i].x, rect[i].y, rect[i].w, rect[i].h);
    }
    MdCameraUpdate(cameraWork);
}

/* 186 insns */
void MdCameraDebug(MDCAMERA_WORK *cameraWork)
{
    MDCAMERA *camera;
    if(HuPadBtnDown[0] & PAD_TRIGGER_R) {
        cameraWork->selCamera = ++cameraWork->selCamera%MDCAMERA_MAX;
    }
    camera = &cameraWork->camera[cameraWork->selCamera];
    if(HuPadTrigL[0] <= 75) {
        if(HuPadSubStkX[0] <= -29) {
            camera->hvr.x += 1;
        } else if(HuPadSubStkX[0] >= 29) {
            camera->hvr.x -= 1;
        }
        if(HuPadSubStkY[0] <= -29) {
            camera->hvr.y -= 1;
        } else if(HuPadSubStkY[0] >= 29) {
            camera->hvr.y += 1;
        }
    } else if(HuPadBtn[0] & PAD_TRIGGER_L) {
        if(HuPadStkY[0] <= -36) {
            camera->center.y -= 50;
        } else if(HuPadStkY[0] >= 36) {
            camera->center.y += 50;
        }
        if(HuPadSubStkY[0] <= -29) {
            camera->hvr.z += 50;
        } else if(HuPadSubStkY[0] >= 29) {
            camera->hvr.z -= 50;
        }
    } else {
        if(HuPadStkY[0] <= -36) {
            camera->center.y -= 10;
        } else if(HuPadStkY[0] >= 36) {
            camera->center.y += 10;
        }
        if(HuPadSubStkY[0] <= -29) {
            camera->hvr.z += 10;
        } else if(HuPadSubStkY[0] >= 29) {
            camera->hvr.z -= 10;
        }
    }
}

/* 137 insns */
void MdCameraUpdate(MDCAMERA_WORK *cameraWork)
{
    int i;
    static HuVecF up_S417 = { 0, 1, 0 };
    static HuVecF forward_S418 = { 0, 0, 1 };

    for(i=0; i<MDCAMERA_MAX; i++) {
        MDCAMERA *camera = &cameraWork->camera[i];
        camera->target.x = camera->center.x;
        camera->target.y = camera->center.y;
        camera->target.z = camera->center.z;
        camera->pos.x = camera->target.x+(camera->hvr.z*HuCos(camera->hvr.y)*HuCos(camera->hvr.x));
        camera->pos.y = camera->target.y+(camera->hvr.z*HuSin(camera->hvr.y));
        camera->pos.z = camera->target.z+(camera->hvr.z*HuCos(camera->hvr.y)*HuSin(camera->hvr.x));
        VECSubtract(&camera->target, &camera->pos, &camera->dir);
        VECNormalize(&camera->dir, &camera->dir);
        VECCrossProduct(&up_S417, &camera->dir, &camera->cross);
        VECNormalize(&camera->cross, &camera->cross);
        VECCrossProduct(&camera->dir, &camera->cross, &camera->up);
        VECNormalize(&camera->up, &camera->up);
        Hu3DCameraPosSet(camera->bit,
            camera->pos.x, camera->pos.y, camera->pos.z,
            camera->up.x, camera->up.y, camera->up.z,
            camera->target.x, camera->target.y, camera->target.z);
    }
}

/* 52 insns */
void MdCameraPrint(MDCAMERA_WORK *cameraWork)
{
    MDCAMERA *camera = &cameraWork->camera[cameraWork->selCamera];
    MdDebugFontPrint(cameraWork->debugFont, "camera(HU3D_CAM%d))", cameraWork->selCamera);
    MdDebugFontPrint(cameraWork->debugFont, "   hvr(%.1f / %.1f / %.1f / %.1f)", camera->hvr.x, camera->hvr.y, camera->hvr.z);
    MdDebugFontPrint(cameraWork->debugFont, "   pos(%.1f / %.1f / %.1f)", camera->pos.x, camera->pos.y, camera->pos.z);
    MdDebugFontPrint(cameraWork->debugFont, "target(%.1f / %.1f / %.1f)", camera->target.x, camera->target.y, camera->target.z);
    MdDebugFontPrint(cameraWork->debugFont, "  fovy(%.1f)", camera->fovy);
}

/* 7 insns */
void MdCameraPosSet(MDCAMERA *camera, float h, float v, float r, float cx, float cy, float cz)
{
    camera->hvr.x = h;
    camera->hvr.y = v;
    camera->hvr.z = r;
    camera->center.x = cx;
    camera->center.y = cy;
    camera->center.z = cz;
}

/* 110 insns */
void MdLightCreate(MDLIGHT_WORK *lightWork)
{
    MDLIGHT *light;
    Hu3DLighInit();
    lightWork->createF = TRUE;
    lightWork->lightSel = 0;
    light = &lightWork->light[0];
    light->type = MDLIGHT_TYPE_G_DIRECT;
    light->hvr.x = 45;
    light->hvr.y = -45;
    light->hvr.z = 1000;
    light->center.x = 0;
    light->center.y = 0;
    light->center.z = 0;
    light->rgb.r = 255;
    light->rgb.g = 224;
    light->rgb.b = 144;
    light->rgb.a = 255;
    light->pos.x = 0;
    light->pos.y = 0;
    light->pos.z = 0;
    light->target.x = 0;
    light->target.y = 0;
    light->target.z = 0;
    light->lightDir.x = 0;
    light->lightDir.y = 0;
    light->lightDir.z = 1;
    light->lightPos = light->pos;
    VECSubtract(&light->target, &light->pos, &light->lightDir);
    light->gLightId = Hu3DGLightCreateV(&light->lightPos, &light->lightDir, &light->rgb);
    MdLightUpdateData(light);
    Hu3DGLightStaticSet(light->gLightId, TRUE);
    Hu3DGLightInfinitytSet(light->gLightId);
    light = &lightWork->light[1];
    light->type = MDLIGHT_TYPE_NOP;
}

/* 11 insns */
void MdLightSetupModel(MDLIGHT_WORK *lightWork)
{
    /* retail: model in r30 plus an unused saved r31; the body was probably compiled out (fork S: masked residue) */
    HU3DMODEL *modelP;
    MDMODEL_WORK *model = sysP->model;
    model->ambScale;
}

/* 23 insns */
void MdLightUpdate(MDLIGHT_WORK *lightWork)
{
    int i;
    for(i=0; i<MDLIGHT_MAX; i++) {
        MDLIGHT *light = &lightWork->light[i];
        MdLightUpdateData(light);
    }
}

/* 327 insns */
void MdLightUpdateData(MDLIGHT *light)
{
    if(light->type == MDLIGHT_TYPE_NOP) {
        return;
    }
    if(light->type == MDLIGHT_TYPE_G_DIRECT || light->type == MDLIGHT_TYPE_L_DIRECT) {
        light->target.x = light->center.x;
        light->target.y = light->center.y;
        light->target.z = light->center.z;
        light->pos.x = light->target.x+(light->hvr.z*HuCos(light->hvr.y)*HuCos(light->hvr.x));
        light->pos.y = light->target.y+(light->hvr.z*HuSin(light->hvr.y));
        light->pos.z = light->target.z+(light->hvr.z*HuCos(light->hvr.y)*HuSin(light->hvr.x));
        light->lightPos = light->pos;
        VECSubtract(&light->target, &light->pos, &light->lightDir);
        VECNormalize(&light->lightDir, &light->lightDir);
        if(light->type == MDLIGHT_TYPE_G_DIRECT) {
            Hu3DGLightPosSetV(light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DGLightColorSet(light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
        } else if(light->type == MDLIGHT_TYPE_L_DIRECT) {
            Hu3DLLightPosSetV(light->lLightId, light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DLLightColorSet(light->lLightId, light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
        }
    } else if(light->type == MDLIGHT_TYPE_G_POINT || light->type == MDLIGHT_TYPE_L_POINT) {
        light->target.x = light->center.x;
        light->target.y = light->center.y;
        light->target.z = light->center.z;
        light->pos.x = light->target.x+(light->hvr.z*HuCos(light->hvr.y)*HuCos(light->hvr.x));
        light->pos.y = light->target.y+(light->hvr.z*HuSin(light->hvr.y));
        light->pos.z = light->target.z+(light->hvr.z*HuCos(light->hvr.y)*HuSin(light->hvr.x));
        light->lightPos = light->target;
        VECSubtract(&light->pos, &light->target, &light->lightDir);
        VECNormalize(&light->lightDir, &light->lightDir);
        if(light->type == MDLIGHT_TYPE_G_POINT) {
            Hu3DGLightPosSetV(light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DGLightColorSet(light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
        } else if(light->type == MDLIGHT_TYPE_L_POINT) {
            Hu3DLLightPosSetV(light->lLightId, light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DLLightColorSet(light->lLightId, light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
            Hu3DLLightPointSet(light->lLightId, light->gLightId, light->hvr.z, 0.1f, GX_DA_GENTLE);
        }
    } else if(light->type == MDLIGHT_TYPE_G_SPOT || light->type == MDLIGHT_TYPE_L_SPOT) {
        light->lightPos = light->pos;
        VECSubtract(&light->target, &light->pos, &light->lightDir);
        VECNormalize(&light->lightDir, &light->lightDir);
        if(light->type == MDLIGHT_TYPE_G_SPOT) {
            Hu3DGLightPosSetV(light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DGLightColorSet(light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
        } else if(light->type == MDLIGHT_TYPE_L_SPOT) {
            Hu3DLLightPosSetV(light->lLightId, light->gLightId, &light->lightPos, &light->lightDir);
            Hu3DLLightColorSet(light->lLightId, light->gLightId, light->rgb.r, light->rgb.g, light->rgb.b, light->rgb.a);
        }
    }
}

/* 385 insns */
void MdLightDebug(MDLIGHT_WORK *lightWork)
{
    MDLIGHT *light;
    if(HuPadBtnDown[0] & PAD_TRIGGER_R) {
        lightWork->lightSel = ++lightWork->lightSel%MDLIGHT_MAX;
    }
    light = &lightWork->light[lightWork->lightSel];
    if(light->type == MDLIGHT_TYPE_G_DIRECT || light->type == MDLIGHT_TYPE_L_DIRECT) {
        if(HuPadTrigL[0] <= 75) {
            if(HuPadSubStkX[0] <= -29) {
                light->hvr.x += 1;
            } else if(HuPadSubStkX[0] >= 29) {
                light->hvr.x -= 1;
            }
            if(HuPadSubStkY[0] <= -29) {
                light->hvr.y -= 1;
            } else if(HuPadSubStkY[0] >= 29) {
                light->hvr.y += 1;
            }
        } else {
            if(HuPadSubStkY[0] <= -29) {
                light->hvr.z -= 5;
            } else if(HuPadSubStkY[0] >= 29) {
                light->hvr.z += 5;
            }
        }
    } else if(light->type == MDLIGHT_TYPE_G_POINT || light->type == MDLIGHT_TYPE_L_POINT) {
        if(HuPadTrigL[0] <= 75) {
            if(HuPadSubStkX[0] <= -29) {
                light->center.x += 10;
            } else if(HuPadSubStkX[0] >= 29) {
                light->center.x -= 10;
            }
            if(HuPadSubStkY[0] <= -29) {
                light->center.z -= 10;
            } else if(HuPadSubStkY[0] >= 29) {
                light->center.z += 10;
            }
        } else {
            if(HuPadSubStkY[0] <= -29) {
                light->center.y -= 5;
            } else if(HuPadSubStkY[0] >= 29) {
                light->center.y += 5;
            }
            if(HuPadSubStkX[0] <= -29) {
                light->hvr.z -= 5;
            } else if(HuPadSubStkX[0] >= 29) {
                light->hvr.z += 5;
            }
        }
    } else if(light->type == MDLIGHT_TYPE_G_SPOT || light->type == MDLIGHT_TYPE_L_SPOT) {
        if(HuPadTrigL[0] <= 75) {
            if(HuPadSubStkX[0] <= -29) {
                light->pos.x -= 5;
            } else if(HuPadSubStkX[0] >= 29) {
                light->pos.x += 5;
            }
            if(HuPadSubStkY[0] <= -29) {
                light->pos.z -= 5;
            } else if(HuPadSubStkY[0] >= 29) {
                light->pos.z += 5;
            }
            if(HuPadStkY[0] <= -36) {
                light->pos.y -= 5;
            } else if(HuPadStkY[0] >= 36) {
                light->pos.y += 5;
            }
        } else {
            if(HuPadSubStkX[0] <= -29) {
                light->target.x -= 5;
            } else if(HuPadSubStkX[0] >= 29) {
                light->target.x += 5;
            }
            if(HuPadSubStkY[0] <= -29) {
                light->target.z -= 5;
            } else if(HuPadSubStkY[0] >= 29) {
                light->target.z += 5;
            }
            if(HuPadStkY[0] <= -36) {
                light->target.y -= 5;
            } else if(HuPadStkY[0] >= 36) {
                light->target.y += 5;
            }
        }
    }
}

/* 60 insns */
void MdLightPrint(MDLIGHT_WORK *lightWork)
{
    MDLIGHT *light = &lightWork->light[lightWork->lightSel];
    static char *lightType_S590[MDLIGHT_TYPE_MAX] = {
        "NOP",
        "G_DIRECT",
        "L_DIRECT",
        "G_POINT",
        "L_POINT",
        "G_SPOT",
        "L_SPOT"
    };
    MdDebugFontPrint(lightWork->debugFont, "light(%d)->%s)", lightWork->lightSel, lightType_S590[light->type]);
    MdDebugFontPrint(lightWork->debugFont, "   hvr(%.1f / %.1f / %.1f)", light->hvr.x, light->hvr.y, light->hvr.z);
    MdDebugFontPrint(lightWork->debugFont, "   pos(%.1f / %.1f / %.1f)", light->pos.x, light->pos.y, light->pos.z);
    MdDebugFontPrint(lightWork->debugFont, "target(%.1f / %.1f / %.1f)", light->target.x, light->target.y, light->target.z);
    MdDebugFontPrint(lightWork->debugFont, "rgb(%d / %d / %d)", light->rgb.r, light->rgb.g, light->rgb.b);
}

/* 85 insns */
Mtx *MdMathMatrixDir(HuVecF *start, HuVecF *end)
{
    static Mtx out_S604;
    static HuVecF up_S606 = { 0, 1, 0 };
    HuVecF cross;
    HuVecF cross2;
    HuVecF dir;
    HuVecF a;
    HuVecF b;

    b = *end;
    a = *start;
    VECSubtract(&b, &a, &dir);
    VECNormalize(&dir, &dir);
    VECCrossProduct(&up_S606, &dir, &cross);
    VECNormalize(&cross, &cross);
    VECCrossProduct(&dir, &cross, &cross2);
    VECNormalize(&cross2, &cross2);
    out_S604[0][1] = cross2.x;
    out_S604[1][1] = cross2.y;
    out_S604[2][1] = cross2.z;
    out_S604[0][0] = cross.x;
    out_S604[1][0] = cross.y;
    out_S604[2][0] = cross.z;
    out_S604[0][2] = dir.x;
    out_S604[1][2] = dir.y;
    out_S604[2][2] = dir.z;
    return &out_S604;
}

/* 45 insns */
void MdMathMatrixRot(Mtx *matrix, HuVecF *rot)
{
    Mtx rotX, rotY, rotZ;
    MTXRotDeg(rotX, 'X', rot->x);
    MTXRotDeg(rotY, 'Y', rot->y);
    MTXRotDeg(rotZ, 'Z', rot->z);
    MTXConcat(rotZ, rotX, *matrix);
    MTXConcat(*matrix, rotY, *matrix);
}

/* 11 insns */
void MdMathClamp(float *val, float min, float max)
{
    if(*val <= min) {
        *val = min;
    }
    if(*val >= max) {
        *val = max;
    }
}

/* 34 insns */
void MdMathAngleClamp(float *angle)
{
    if(*angle > 180.0f) {
        *angle = -180.0f+(*angle-180.0f);
    } else if(*angle < -180.0f) {
        *angle = 180.0f+(*angle+180.0f);
    }
}

/* 234 insns */
void MdMathOscillate(int type, float *in, float *out, float t)
{
    *in += 1/t;
    if(*in <= 0) {
        *in = 0;
    }
    if(*in >= 1) {
        *in = 1;
    }
    switch(type) {
        case MDMATH_OSC_0:
            *out = *in;
            break;

        case MDMATH_OSC_90:
            *out = HuSin((*in)*90);
            break;

        case MDMATH_OSC_90_REV:
            *out = 1-HuSin(90-((*in)*90));
            break;

        case MDMATH_OSC_180:
            *out = HuSin((*in)*180);
            break;

        case MDMATH_OSC_360:
            *out = HuSin((*in)*360);
            break;

        case MDMATH_OSC_540:
            *out = HuSin((*in)*540);
            break;

        case MDMATH_OSC_720:
            *out = HuSin((*in)*720);
            break;
    }
}

/* 49 insns */
void MdMathStdCurveGet(int type, float *in, float *out, float t)
{
    *in += 1/t;
    if(*in <= 0) {
        *in = 0;
    }
    if(*in >= 1) {
        *in = 1;
    }
    *out = StdCurveGet(type, *in);
}

/* 5 insns */
void MdMathLerp(float *out, float a, float b, float t)
{
    *out = a+(t*(b-a));
}

/* 13 insns */
void MdMathLerpScale(HuVecF *out, float a, float b, float t)
{
    float result = a+(t*(b-a));
    out->x = result;
    out->y = result;
    out->z = result;
}

/* 10 insns */
void MdMathLerpColor(u8 *out, float a, float b, float t)
{
    *out = a+(t*(b-a));
}

/* 6 insns */
void MdMathLerpOfs(float *out, float a, float b, float t, float ofs)
{
    *out = a+((b-a)*(t+ofs));
}

/* 14 insns */
void MdMathLerpScaleOfs(HuVecF *out, float a, float b, float t, float ofs)
{
    float result = a+((b-a)*(t+ofs));
    out->x = result;
    out->y = result;
    out->z = result;
}

/* 64 insns */
void MdMathCurveInit(int sampleNum, float *sampleT, float *sample, float *sampleSlope)
{
    int i;
    sampleT[0] = 0;
    (sampleT-1)[sampleNum] = 1;
    for(i=1; i<sampleNum-1; i++) {
        sampleT[i] = (1.0f/(sampleNum-1))*i;
    }

    CurveInit(sampleNum, sampleT, sample, sampleSlope);
}

/* 22 insns */
void MdMathCurveGet(float *out, int sampleNum, float *sampleT, float *sample, float *sampleSlope, float t)
{
    *out = CurveGet(sampleNum, t, sampleT, sample, sampleSlope);
}

/* 123 insns */
void MdMathStdCurveInit(void)
{
    int i;
    int j;
    for(i=0; i<2; i++) {
        for(j=0; j<MDMATH_CURVE_SAMPLE_MAX; j++) {
            if(1.0f == stdCurveSample[i][j]) {
                stdCurveSampleNum[i] = j+1;
                break;
            }
        }
    }
    for(i=0; i<2; i++) {
        stdCurveTime[i][0] = 0;
        stdCurveTime[i][stdCurveSampleNum[i]-1] = 1;
        for(j=1; j<stdCurveSampleNum[i]-1; j++) {
            stdCurveTime[i][j] = (1.0f/(stdCurveSampleNum[i]-1))*j;
        }
    }
    for(i=0; i<2; i++) {
        StdCurveInit(i);
    }
}

/* 301 insns */
static void CurveInit(int sampleNum, float *sampleT, float *sample, float *sampleSlope)
{
    int i;
    float step;
    static float dt_S734[MDMATH_CURVE_SAMPLE_MAX+1];
    static float dt2_S735[MDMATH_CURVE_SAMPLE_MAX+1];
    static float slope_S736[MDMATH_CURVE_SAMPLE_MAX+1];
    sampleNum--;
    for(i=0; i<sampleNum; i++) {
        dt_S734[i] = sampleT[i+1]-sampleT[i];
        slope_S736[i] = (sample[i+1]-sample[i])/dt_S734[i];
    }
    slope_S736[sampleNum] = slope_S736[0];
    for(i=1; i<sampleNum; i++) {
        dt2_S735[i] = 2*(sampleT[i+1]-sampleT[i-1]);
    }
    dt2_S735[sampleNum] = 2*(dt_S734[0]+dt_S734[sampleNum-1]);
    for(i=1; i<=sampleNum; i++) {
        sampleSlope[i] = slope_S736[i]-slope_S736[i-1];
    }
    slope_S736[1] = dt_S734[0];
    slope_S736[sampleNum-1] = dt_S734[sampleNum-1];
    slope_S736[sampleNum] = dt2_S735[sampleNum];
    for(i=2; i<sampleNum-1; i++) {
        slope_S736[i] = 0;
    }
    for(i=1; i<sampleNum; i++) {
        step = dt_S734[i]/dt2_S735[i];
        sampleSlope[i+1] = sampleSlope[i+1]-(step*sampleSlope[i]);
        dt2_S735[i+1] = dt2_S735[i+1]-(step*dt_S734[i]);
        slope_S736[i+1] = slope_S736[i+1]-(step*slope_S736[i]);

    }
    slope_S736[0] = slope_S736[sampleNum];
    sampleSlope[0] = sampleSlope[sampleNum];
    for(i=sampleNum-2; i>=0; i--) {
        step = dt_S734[i]/dt2_S735[i+1];
        sampleSlope[i] = sampleSlope[i]-(step*sampleSlope[i+1]);
        slope_S736[i] = slope_S736[i]-(step*slope_S736[i+1]);
    }
    step = sampleSlope[0]/slope_S736[0];
    sampleSlope[0] = step;
    sampleSlope[sampleNum] = step;
    for(i=1; i<sampleNum; i++) {
        sampleSlope[i] = (sampleSlope[i]-(step*slope_S736[i]))/dt2_S735[i];
    }
}

/* 105 insns */
static float CurveGet(int sampleNum, float t, float *sampleT, float *sample, float *sampleSlope)
{
    float dt;
    float sampleDt;
    float len;

    int i;
    int num;
    int mid;

    sampleNum--;
    len = sampleT[sampleNum]-sampleT[0];
    while(t > sampleT[sampleNum]) {
        t -= len;
    }
    while(t < sampleT[0]) {
        t += len;
    }
    for(i=0, num=sampleNum; i<num;) {
        mid = (i+num)/2;
        if(sampleT[mid] < t) {
            i = mid+1;
        } else {
            num = mid;
        }
    }
    if(i > 0) {
        i--;
    }
    sampleDt = sampleT[i+1]-sampleT[i];
    dt = t-sampleT[i];
    return sample[i]+(dt*((dt*((3*sampleSlope[i])+((dt*(sampleSlope[i+1]-sampleSlope[i]))/sampleDt)))+(((sample[i+1]-sample[i])/sampleDt)-(sampleDt*((2*sampleSlope[i])+sampleSlope[i+1])))));
}

/* 324 insns */
static void StdCurveInit(int idx)
{
    int i;
    float *point;
    int pointNum;
    float *time;
    float *samplePoint;
    float step;

    static float dt_S800[MDMATH_CURVE_SAMPLE_MAX+1];
    static float dt2_S801[MDMATH_CURVE_SAMPLE_MAX+1];
    static float slope_S802[MDMATH_CURVE_SAMPLE_MAX+1];

    pointNum = stdCurveSampleNum[idx]-1;
    time = &stdCurveTime[idx][0];
    samplePoint = &stdCurveSample[idx][0];
    point = &stdCurveSlope[idx][0];
    for(i=0; i<pointNum; i++) {
        dt_S800[i] = time[i+1]-time[i];
        slope_S802[i] = (samplePoint[i+1]-samplePoint[i])/dt_S800[i];
    }
    slope_S802[pointNum] = slope_S802[0];
    for(i=1; i<pointNum; i++) {
        dt2_S801[i] = 2*(time[i+1]-time[i-1]);
    }
    dt2_S801[pointNum] = 2*(dt_S800[0]+dt_S800[pointNum-1]);
    for(i=1; i<=pointNum; i++) {
        point[i] = slope_S802[i]-slope_S802[i-1];
    }
    slope_S802[1] = dt_S800[0];
    slope_S802[pointNum-1] = dt_S800[pointNum-1];
    slope_S802[pointNum] = dt2_S801[pointNum];
    for(i=2; i<pointNum-1; i++) {
        slope_S802[i] = 0;
    }
    for(i=1; i<pointNum; i++) {
        step = dt_S800[i]/dt2_S801[i];
        point[i+1] = point[i+1]-(step*point[i]);
        dt2_S801[i+1] = dt2_S801[i+1]-(step*dt_S800[i]);
        slope_S802[i+1] = slope_S802[i+1]-(step*slope_S802[i]);

    }
    slope_S802[0] = slope_S802[pointNum];
    point[0] = point[pointNum];
    for(i=pointNum-2; i>=0; i--) {
        step = dt_S800[i]/dt2_S801[i+1];
        point[i] = point[i]-(step*point[i+1]);
        slope_S802[i] = slope_S802[i]-(step*slope_S802[i+1]);
    }
    step = point[0]/slope_S802[0];
    point[0] = step;
    point[pointNum] = step;
    for(i=1; i<pointNum; i++) {
        point[i] = (point[i]-(step*slope_S802[i]))/dt2_S801[i];
    }
}

/* 124 insns */
static float StdCurveGet(int type, float t)
{
    float dt;
    float sampleDt;
    float len;

    float *sampleT;
    float *sampleSlope;
    float *sample;
    int i;
    int num;
    int mid;

    int sampleNum;
    sampleNum = stdCurveSampleNum[type]-1;
    sampleT = &stdCurveTime[type][0];
    sample = &stdCurveSample[type][0];
    sampleSlope = &stdCurveSlope[type][0];
    len = sampleT[sampleNum]-sampleT[0];
    while(t > sampleT[sampleNum]) {
        t -= len;
    }
    while(t < sampleT[0]) {
        t += len;
    }
    for(i=0, num=sampleNum; i<num;) {
        mid = (i+num)/2;
        if(sampleT[mid] < t) {
            i = mid+1;
        } else {
            num = mid;
        }
    }
    if(i > 0) {
        i--;
    }
    sampleDt = sampleT[i+1]-sampleT[i];
    dt = t-sampleT[i];
    return sample[i]+(dt*((dt*((3*sampleSlope[i])+((dt*(sampleSlope[i+1]-sampleSlope[i]))/sampleDt)))+(((sample[i+1]-sample[i])/sampleDt)-(sampleDt*((2*sampleSlope[i])+sampleSlope[i+1])))));
}

/* 186 insns */
void MdMessCreate(MDMESS_WORK *mess)
{
    MDMESS_HELPWIN *win; //r31
    int i; //r29
    mess->dlgMode = 0;
    mess->dlgWinId = HUWIN_NONE;
    mess->createF = TRUE;
    HuWinInit(0);
    for(win=&mess->win[0], i=0; i<MDMESS_WIN_MAX; i++, win++) {
        win->winId = HUWIN_NONE;
        win->unk4 = 0;
        win->unk8 = 0;
        win->unkC = 0;
    }
}

/* 0x614 jumptable_1_data_614 comes from the switch */

/* 62 insns */
void MdMessMain(MDMESS_WORK *mess)
{
    s16 stat;
    switch(mess->dlgMode) {
        case 0:
            break;

        case 1:
            MdMessDlgWinCreateInsert(mess, mess->dlgMes);
            mess->dlgMode = 3;
            break;

        case 2:
            MdMessDlgWinCreateInsert(mess, mess->dlgMes);
            mess->dlgMode = 4;
            break;

        case 3:
            stat = HuWinStatGet(mess->dlgWinId);
            if(stat == HUWIN_STAT_NONE) {
                mess->dlgMode = 5;
            }
            break;

        case 4:
            stat = HuWinStatGet(mess->dlgWinId);
            if(stat == HUWIN_STAT_NONE) {
                mess->dlgMode = 6;
            }
            break;

        case 5:
            break;

        case 6:
            mess->dlgChoice = HuWinChoiceGet(mess->dlgWinId, -1);
            mess->dlgMode = 5;
            break;

        case 7:
            MdMessDlgWinKill(mess);
            mess->dlgMode = 0;
            break;
    }
}

/* 8 insns */
void MdMessKill(MDMESS_WORK *mess)
{
    HuWinAllKill();
}

/* 136 insns */
void MdMessDlgMesSet(MDMESS_WORK *mess, int cmd, u32 mes)
{
    switch(cmd) {
        case 0:
            MdMessDlgWinKill(mess);
            mess->dlgMode = 0;
            break;

        case 1:
        case 3:
            if(mess->dlgWinId == HUWIN_NONE) {
                if(cmd == 1) {
                    mess->dlgInsertF = FALSE;
                } else {
                    mess->dlgInsertF = TRUE;
                }
                mess->dlgMes = mes;
                mess->dlgMode = 1;
            }
            break;

        case 2:
        case 4:
            if(mess->dlgWinId == HUWIN_NONE) {
                if(cmd == 2) {
                    mess->dlgInsertF = FALSE;
                } else {
                    mess->dlgInsertF = TRUE;
                }
                mess->dlgMes = mes;
                mess->dlgMode = 2;
            }
            break;

        case 5:
            MdMessMain(mess);
            break;
    }
}

/* 8 insns */
void MdMessDlgInsertMesReset(MDMESS_WORK *mess)
{
    MDMESS_INSERT *insert = &mess->insert;
    insert->num = 0;
}

/* 20 insns */
void MdMessDlgInsertMesAdd(MDMESS_WORK *mess, u32 mes, s16 insertNo)
{
    MDMESS_INSERT *insert = &mess->insert;
    insert->mes[insert->num] = mes;
    insert->insertNo[insert->num] = insertNo;
    if(insert->num < MDMESS_INSERTMES_MAX) {
        insert->num++;
    }
}

/* 103 insns */
void MdMessDlgWinCreateInsert(MDMESS_WORK *mess, u32 mes)
{
    MDMESS_INSERT *insert = &mess->insert;
    int i;
    HUWIN *w;
    HuVec2f size;
    if(mess->dlgWinId == HUWIN_NONE) {
        if(mess->dlgInsertF == TRUE) {
            for(i=0; i<insert->num; i++) {
                HuWinInsertMesSizeGet(insert->mes[i], insert->insertNo[i]);
            }
        }
        HuWinMesMaxSizeGet(1, &size, mes);
        if(size.x >= 472) {
            size.x = 472;
        }
        mess->dlgWinId = HuWinCreate(-10000, 374, size.x, 64, 0);
        if(mess->dlgInsertF == TRUE) {
            for(i=0; i<insert->num; i++) {
                HuWinInsertMesSet(mess->dlgWinId, insert->mes[i], insert->insertNo[i]);
            }
        }
        HuWinBGTPLvlSet(mess->dlgWinId, 0);
        HuWinDrawNoSet(mess->dlgWinId, 0);
        HuWinPriSet(mess->dlgWinId, 0);
        HuWinPriSet(mess->dlgWinId, 0);
        HuWinMesSet(mess->dlgWinId, mes);
        w = &winData[mess->dlgWinId];
        w->padMask = 1;
        HuWinDispOn(mess->dlgWinId);
    }
}

/* 21 insns */
void MdMessDlgWinKill(MDMESS_WORK *mess)
{
    if(mess->dlgWinId != HUWIN_NONE) {
        HuWinHomeClear(mess->dlgWinId);
        HuWinDispOff(mess->dlgWinId);
        HuWinKill(mess->dlgWinId);
        mess->dlgWinId = HUWIN_NONE;
    }
}

/* 91 insns */
void MdMessHelpWinCreate(MDMESS_WORK *mess, int winNo, u32 mes, float posX, float posY, s16 w, s16 h, float tpLvl, s16 drawNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HUWIN *winP;
    HuVec2f size;
    if(win->winId == HUWIN_NONE) {
        HuWinMesMaxSizeGet(1, &size, mes);
        if(size.x >= 472) {
            size.x = 472;
        }
        if(w == 0) {
            w = size.x;
        }
        if(h == 0) {
            h = size.y;
        }
        win->winId = HuWinCreate(0, 0, w, h, 0);
        HuWinPosSet(win->winId, posX, posY);
        HuWinBGTPLvlSet(win->winId, tpLvl);
        HuWinDrawNoSet(win->winId, drawNo);
        HuWinPriSet(win->winId, 0);
        HuWinMesSet(win->winId, mes);
        winP = &winData[win->winId];
        winP->padMask = 1;
        HuWinDispOn(win->winId);
    }
}

/* 62 insns */
void MdMessWinOpen(MDMESS_WORK *mess, int winNo, float posX, float posY, s16 w, s16 h, float tpLvl, s16 drawNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HUWIN *winP;
    if(win->winId == HUWIN_NONE) {
        win->winId = HuWinExCreateFrame(posX, posY, w, h, HUWIN_SPEAKER_NONE, 1);
        HuWinPosSet(win->winId, posX, posY);
        HuWinMesPalSet(win->winId, 7, 0, 0, 0);
        HuWinBGTPLvlSet(win->winId, tpLvl);
        HuWinDrawNoSet(win->winId, drawNo);
        HuWinPriSet(win->winId, 0);
        winP = &winData[win->winId];
        winP->padMask = 1;
        HuWinExOpen(win->winId);
    }
}

/* 27 insns */
void MdMessWinClose(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinHomeClear(win->winId);
        HuWinDispOff(win->winId);
        HuWinKill(win->winId);
        win->winId = HUWIN_NONE;
    }
}

/* 27 insns */
void MdMessWinKill(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinHomeClear(win->winId);
        HuWinExClose(win->winId);
        HuWinExKill(win->winId);
        win->winId = HUWIN_NONE;
    }
}

/* 25 insns */
void MdMessWinPosSet(MDMESS_WORK *mess, int winNo, float posX, float posY)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinPosSet(win->winId, posX, posY);
    }
}

/* 39 insns */
void MdMessWinHomeClear(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinHomeClear(win->winId);
    }
}

/* 23 insns */
void MdMessWinMesSet(MDMESS_WORK *mess, int winNo, u32 mes)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinMesSet(win->winId, mes);
    }
}

/* 28 insns */
void MdMessWinInsertMesSet(MDMESS_WORK *mess, int winNo, u32 mes, u32 insertMes)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinInsertMesSet(win->winId, insertMes, 0);
        HuWinMesSet(win->winId, mes);
    }
}

/* 25 insns */
BOOL MdMessWinCheck(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    s16 stat;
    if((stat = HuWinStatGet(win->winId)) == HUWIN_STAT_NONE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 23 insns */
s16 MdMessWinChoiceGet(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    s16 choice = HuWinChoiceGet(win->winId, -1);
    return choice;
}

/* 16 insns */
s16 MdMessWinChoiceNowGet(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HUWIN *winP = &winData[win->winId];
    return winP->choice;
}

/* 16 insns */
void MdMessWinChoiceSet(MDMESS_WORK *mess, int winNo, s16 choice)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HUWIN *winP = &winData[win->winId];
    winP->choice = choice;
}

/* 22 insns */
s16 MdMessWinStatGet(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    s16 stat = HuWinStatGet(win->winId);
    return stat;
}

/* 20 insns */
void MdMessWinAttrSet(MDMESS_WORK *mess, int winNo, u32 attr)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HuWinAttrSet(win->winId, attr);
}

/* 20 insns */
void MdMessWinAttrReset(MDMESS_WORK *mess, int winNo, u32 attr)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HuWinAttrReset(win->winId, attr);
}

/* 1 insns */
