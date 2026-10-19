/*
 * mdoptiondll object.c -- debug font, pad, camera, light, shadow, math helpers and the message
 * windows (fork S, 2026-10-01). Twins: mdstorydll/object.c, mdseldll/object.c.
 */

#include "REL/mdoptionDll.h"

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
/* 0x1B0 lbl_1_rodata_1B0 (0x8): 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_1B8 = 1.5f; /* 0x1B8 */
/* 0x1BC lbl_1_rodata_1BC (0x8): 0x00000001 0x00000002 -- an aggregate initialiser, write it as a local */
/* 0x1C4 lbl_1_rodata_1C4 (0x20): 0x00000000 0x00000000 0x44200000 0x43F00000 0x00000000 0x00000000 0x44200000 0x43F00000 -- an aggregate initialiser, write it as a local */
/* 0x1E4 lbl_1_rodata_1E4 (0x30): 0x42B40000 0x40A00000 0x458CA000 0x00000000 0xC2480000 0x00000000 0x42B40000 0x00000000 0x451C4000 0x00000000 0x43C80000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_214 = 3375.0f; /* 0x214 */
static const float lbl_1_rodata_218 = 0.0f; /* 0x218 */
static const float lbl_1_rodata_21C = 30.0f; /* 0x21C */
static const float lbl_1_rodata_220 = 576.0f; /* 0x220 */
static const float lbl_1_rodata_224 = 640.0f; /* 0x224 */
static const float lbl_1_rodata_228 = 480.0f; /* 0x228 */
static const float lbl_1_rodata_22C = 20.0f; /* 0x22C */
static const float lbl_1_rodata_230 = 20000.0f; /* 0x230 */
static const float lbl_1_rodata_234 = 1.0f; /* 0x234 */
static const float lbl_1_rodata_238 = 50.0f; /* 0x238 */
static const float lbl_1_rodata_23C = 10.0f; /* 0x23C */
static const double lbl_1_rodata_240 = 3.141592653589793; /* 0x240 */
static const double lbl_1_rodata_248 = 180.0; /* 0x248 */
static const float lbl_1_rodata_250 = 45.0f; /* 0x250 */
static const float lbl_1_rodata_254 = 35.0f; /* 0x254 */
static const float lbl_1_rodata_258 = 1000.0f; /* 0x258 */
static const float lbl_1_rodata_25C = 0.1f; /* 0x25C */
static const float lbl_1_rodata_260 = 5.0f; /* 0x260 */
static const float lbl_1_rodata_264 = 10000.0f; /* 0x264 */
static const float lbl_1_rodata_268 = 0.3f; /* 0x268 */
static const float lbl_1_rodata_26C = 65.0f; /* 0x26C */
static const float lbl_1_rodata_270 = 6000.0f; /* 0x270 */
static const float lbl_1_rodata_274 = 0.017453292f; /* 0x274 */
static const float lbl_1_rodata_278 = 180.0f; /* 0x278 */
static const float lbl_1_rodata_27C = -180.0f; /* 0x27C */
static const float lbl_1_rodata_280 = 90.0f; /* 0x280 */
static const double lbl_1_rodata_288 = 1.0; /* 0x288 */
static const float lbl_1_rodata_290 = 360.0f; /* 0x290 */
static const float lbl_1_rodata_294 = 540.0f; /* 0x294 */
static const float lbl_1_rodata_298 = 720.0f; /* 0x298 */
/* 0x2A0 lbl_1_rodata_2A0 = 4503601774854144: int->float conversion constant, compiler-generated */
static const float lbl_1_rodata_2A8 = 2.0f; /* 0x2A8 */
/* 0x2AC lbl_1_rodata_2AC (0x4): 0x40400000 -- an aggregate initialiser, write it as a local */
/* 0x2B0 lbl_1_rodata_2B0 (0x6C): 0x00000000 0x42440000 0x00000000 0x00000000 0x42A80000 0x00000000 0x00000000 0x42E00000 0x00000000 0x00000000 0x42400000 0x00000000 0x00000000 0x42400000 0x00000000 0x00000000 0x42400000 0x00000000 0x00000000 0x42400000 0x00000000 0x00000000 0x42400000 0x00000000 0x00000000 0x42400000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_31C = 138.0f; /* 0x31C */
static const float lbl_1_rodata_320 = 133.0f; /* 0x320 */
static const float lbl_1_rodata_324 = 344.0f; /* 0x324 */
static const float lbl_1_rodata_328 = 472.0f; /* 0x328 */
static const float lbl_1_rodata_32C = -10000.0f; /* 0x32C */
static const float lbl_1_rodata_330 = 374.0f; /* 0x330 */
/* 0x334 lbl_1_rodata_334 (0xC): 0x00000000 0x00000000 0x00000000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_340 = 0.4f; /* 0x340 */
static const float lbl_1_rodata_344 = 0.025f; /* 0x344 */
static const float lbl_1_rodata_348 = 0.5f; /* 0x348 */
static const double lbl_1_rodata_350 = 0.5; /* 0x350 */
static const float lbl_1_rodata_358 = -90.0f; /* 0x358 */
/* 0x35C lbl_1_rodata_35C (0x18): 0x00000000 0x3F800000 0x00000000 0x00000000 0x00000000 0x3F800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_374 = 0.98f; /* 0x374 */
static const double lbl_1_rodata_378 = 1.2000000476837158; /* 0x378 */
static const float lbl_1_rodata_380 = 288.0f; /* 0x380 */
static const float lbl_1_rodata_384 = 240.0f; /* 0x384 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x7E0 */ static s32 stdCurveSampleNum[2];
/* 0x7A0 */ static float stdCurveTime[2][MDMATH_CURVE_SAMPLE_MAX];
/* 0x760 */ static float stdCurveSlope[2][MDMATH_CURVE_SAMPLE_MAX];

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
        "shadow",
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
void MdObjShadowCreate(OMOBJ *obj)
{
    MDSHADOW_WORK *shadow = obj->data;
    MdShadowCreate(shadow);
    obj->objFunc = MdObjShadowMain;
}

/* 15 insns */
void MdObjShadowMain(OMOBJ *obj)
{
    MDSHADOW_WORK *shadow = obj->data;
    MdShadowUpdate(shadow);
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
    float unused = sysP->unk3E0;
    int bit[MDCAMERA_MAX] = { HU3D_CAM0, HU3D_CAM1 };
    MDCAMERA_RECT rect[MDCAMERA_MAX] = {
        { 0, 0, 640, 480 },
        { 0, 0, 640, 480 },
    };
    MDCAMERA_PARAM param[MDCAMERA_MAX] = {
        {
            { 90, 5, 4500 },
            { 0, -50, 0 },
        },
        {
            { 90, 0, 2500 },
            { 0, 400, 0 },
        },
    };
    float aspect[MDCAMERA_MAX];

    MDCAMERA *camera;
    int i;

    param[0].hvr.z = 3375;
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
    light->hvr.y = 35;
    light->hvr.z = 1000;
    light->center.x = 0;
    light->center.y = 0;
    light->center.z = 0;
    light->rgb.r = 204;
    light->rgb.g = 179;
    light->rgb.b = 115;
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

/* 74 insns */
void MdShadowCreate(MDSHADOW_WORK *shadowWork)
{
    MDCAMERA_WORK *cameraWork = sysP->camera;
    MDSHADOW *shadow;
    int i;
    shadowWork->createF = TRUE;
    shadowWork->shadowSel = 0;
    Hu3DShadowCreate(30, 20, 10000);
    for(i=0; i<MDSHADOW_MAX; i++) {
        shadow = &shadowWork->shadow[i];
        shadow->cameraBit = cameraWork->camera[0].bit;
        shadow->tpLvl = 0.3f;
        shadow->hvr.x = 65;
        shadow->hvr.y = 65;
        shadow->hvr.z = 6000;
        shadow->center.x = 0;
        shadow->center.y = 0;
        shadow->center.z = 0;
    }
    MdShadowUpdate(shadowWork);
}

/* 131 insns */
void MdShadowUpdate(MDSHADOW_WORK *shadowWork)
{
    int i;
    static HuVecF up_S606 = { 0, 1, 0 };
    static HuVecF forward_S607 = { 0, 0, 1 };

    for(i=0; i<MDSHADOW_MAX; i++) {
        MDSHADOW *shadow = &shadowWork->shadow[i];
        shadow->target.x = shadow->center.x;
        shadow->target.y = shadow->center.y;
        shadow->target.z = shadow->center.z;
        shadow->pos.x = shadow->target.x+(shadow->hvr.z*HuCos(shadow->hvr.y)*HuCos(shadow->hvr.x));
        shadow->pos.y = shadow->target.y+(shadow->hvr.z*HuSin(shadow->hvr.y));
        shadow->pos.z = shadow->target.z+(shadow->hvr.z*HuCos(shadow->hvr.y)*HuSin(shadow->hvr.x));
        VECSubtract(&shadow->target, &shadow->pos, &shadow->dir);
        VECNormalize(&shadow->dir, &shadow->dir);
        VECCrossProduct(&up_S606, &shadow->dir, &shadow->cross);
        VECNormalize(&shadow->cross, &shadow->cross);
        VECCrossProduct(&shadow->dir, &shadow->cross, &shadow->up);
        VECNormalize(&shadow->up, &shadow->up);
        Hu3DShadowTPLvlSet(shadow->tpLvl);
        Hu3DShadowPosSet(&shadow->pos, &shadow->up, &shadow->target);
    }
}

/* 185 insns */
void MdShadowDebug(MDSHADOW_WORK *shadowWork)
{
    MDSHADOW *shadow;
    if(HuPadBtnDown[0] & PAD_TRIGGER_R) {
        shadowWork->shadowSel = ++shadowWork->shadowSel%MDSHADOW_MAX;
    }
    shadow = &shadowWork->shadow[shadowWork->shadowSel];
    if(HuPadTrigL[0] <= 75) {
        if(HuPadSubStkX[0] <= -29) {
            shadow->hvr.x += 1;
        } else if(HuPadSubStkX[0] >= 29) {
            shadow->hvr.x -= 1;
        }
        if(HuPadSubStkY[0] <= -29) {
            shadow->hvr.y -= 1;
        } else if(HuPadSubStkY[0] >= 29) {
            shadow->hvr.y += 1;
        }
    } else if(HuPadBtn[0] & PAD_TRIGGER_L) {
        if(HuPadSubStkY[0] <= -29) {
            shadow->hvr.z += 50;
        } else if(HuPadSubStkY[0] >= 29) {
            shadow->hvr.z -= 50;
        }
        if(HuPadStkY[0] <= -36) {
            shadow->center.y -= 50;
        } else if(HuPadStkY[0] >= 36) {
            shadow->center.y += 50;
        }
    } else {
        if(HuPadSubStkY[0] <= -29) {
            shadow->hvr.z += 10;
        } else if(HuPadSubStkY[0] >= 29) {
            shadow->hvr.z -= 10;
        }
        if(HuPadStkY[0] <= -36) {
            shadow->center.y -= 10;
        } else if(HuPadStkY[0] >= 36) {
            shadow->center.y += 10;
        }
    }
}

/* 46 insns */
void MdShadowPrint(MDSHADOW_WORK *shadowWork)
{
    MDSHADOW *shadow = &shadowWork->shadow[shadowWork->shadowSel];
    MdDebugFontPrint(shadowWork->debugFont, "shadow(%d))", shadowWork->shadowSel);
    MdDebugFontPrint(shadowWork->debugFont, "   hvr(%.1f / %.1f / %.1f)", shadow->hvr.x, shadow->hvr.y, shadow->hvr.z);
    MdDebugFontPrint(shadowWork->debugFont, "   pos(%.1f / %.1f / %.1f)", shadow->pos.x, shadow->pos.y, shadow->pos.z);
    MdDebugFontPrint(shadowWork->debugFont, "target(%.1f / %.1f / %.1f)", shadow->target.x, shadow->target.y, shadow->target.z);
}

/* 85 insns */
Mtx *MdMathMatrixDir(HuVecF *start, HuVecF *end)
{
    static Mtx out_S604;
    static HuVecF up_S650 = { 0, 1, 0 };
    HuVecF cross;
    HuVecF cross2;
    HuVecF dir;
    HuVecF a;
    HuVecF b;

    b = *end;
    a = *start;
    VECSubtract(&b, &a, &dir);
    VECNormalize(&dir, &dir);
    VECCrossProduct(&up_S650, &dir, &cross);
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

/* 45 insns */
void MdMathMatrixRotRPY(Mtx *matrix, HuVecF *rot)
{
    Mtx rotX, rotY, rotZ;
    MTXRotDeg(rotX, 'X', rot->x);
    MTXRotDeg(rotY, 'Y', rot->y);
    MTXRotDeg(rotZ, 'Z', rot->z);
    MTXConcat(rotZ, rotY, *matrix);
    MTXConcat(*matrix, rotX, *matrix);
}

/* 18 insns */
void MdMathMtxTrans(Mtx src, Mtx dst, HuVecF *trans)
{
    MTXTransApply(src, dst, trans->x, trans->y, trans->z);
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

        case MDMATH_OSC_COS_180:
            *out = HuCos((*in)*180);
            break;

        case MDMATH_OSC_COS_360:
            *out = HuCos((*in)*360);
            break;

        case MDMATH_OSC_COS_540:
            *out = HuCos((*in)*540);
            break;

        case MDMATH_OSC_COS_720:
            *out = HuCos((*in)*720);
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
    MDMESS_HELPWIN *win; //r29
    int i; //r30
    MDMESS_DLGPOS *dlgPos; //r28
    int no; //r27
    mess->dlgMode = 0;
    mess->dlgWinId = HUWIN_NONE;
    mess->createF = TRUE;
    for(win=&mess->win[0], i=0; i<MDMESS_HELPWIN_MAX; i++, win++) {
        win->winId = HUWIN_NONE;
        win->unk4 = 0;
        win->unk8 = 0;
        win->unkC = 0;
    }
    dlgPos = &mess->dlgPos;
    dlgPos->mode = 0;
    dlgPos->unk8 = 0;
    dlgPos->unkC = 0;
    dlgPos->unk10 = 0;
    dlgPos->unk14 = 0;
    {
    HuVecF ofs[9] = {
        { 0, 49, 0 },
        { 0, 84, 0 },
        { 0, 112, 0 },
        { 0, 48, 0 },
        { 0, 48, 0 },
        { 0, 48, 0 },
        { 0, 48, 0 },
        { 0, 48, 0 },
        { 0, 48, 0 },
    };
    for(i=2; i<MDMESS_HELPWIN_MAX; i++) {
        no = i-2;
        if(i < 4) {
            if(i == 2) {
                /* retail reads ofs[no] past ofs[8] for no >= 9 (help windows 11-17) */
                MdMessHelpWinCreate(mess, i, 0, 138, ofs[no].y, 300, 28, 0, 0);
            } else {
                MdMessHelpWinCreate(mess, i, 0, 0, ofs[no].y, 566, 28, 0, 0);
            }
        } else {
            MdMessHelpWinCreate(mess, i, 0x20000B, 138, ofs[no].y, 300, 28, 1, 0);
        }
        MdMessWinHomeClear(mess, i);
        MdMessWinAttrSet(mess, i, HUWIN_ATTR_DISPOFF);
        MdMessWinSpeedSet(mess, i, 0);
        MdMessWinScaleSet(mess, i, 0, 0);
    }
    MdMessWinPosSet(mess, 2, 133, ofs[0].y);
    MdMessHelpWinCreate(mess, 1, 0x20004, 0, 344, 576, 28, 0, 0);
    MdMessWinHomeClear(mess, 1);
    MdMessWinAttrSet(mess, 1, HUWIN_ATTR_ALIGN_CENTER);
    }
}

/* 0x614 jumptable_1_data_614 comes from the switch */

/* 62 insns */
void MdMessUpdate(MDMESS_WORK *mess)
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
    MDMESS_DLGPOS *dlgPos = &mess->dlgPos;
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
            MdMessUpdate(mess);
            break;

        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
            if(cmd == 6) {
                dlgPos->mode = 1;
            } else if(cmd == 7) {
                dlgPos->mode = 2;
            } else if(cmd == 8) {
                dlgPos->mode = 3;
            } else if(cmd == 9) {
                dlgPos->mode = 4;
            } else if(cmd == 10) {
                dlgPos->mode = 5;
            } else if(cmd == 11) {
                dlgPos->mode = 6;
            }
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
        HuWinDispOn(win->winId);
    }
}

/* 62 insns */
void MdMessWinOpen(MDMESS_WORK *mess, int winNo, float posX, float posY, s16 w, s16 h, float tpLvl, s16 drawNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId == HUWIN_NONE) {
        win->winId = HuWinExCreateFrame(posX, posY, w, h, HUWIN_SPEAKER_NONE, 0);
        HuWinPosSet(win->winId, posX, posY);
        HuWinMesPalSet(win->winId, 7, 255, 255, 255);
        HuWinBGTPLvlSet(win->winId, tpLvl);
        HuWinDrawNoSet(win->winId, drawNo);
        HuWinPriSet(win->winId, 0);
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

/* 22 insns */
void MdMessWinSpeedSet(MDMESS_WORK *mess, int winNo, s16 speed)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinMesSpeedSet(win->winId, 0);
    }
}

/* 25 insns */
void MdMessWinScaleSet(MDMESS_WORK *mess, int winNo, float scaleX, float scaleY)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinScaleSet(win->winId, scaleX, scaleY);
    }
}

/* 39 insns */
void MdMessWinHomeClear(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HUWIN *winP;
    int i;
    if(win->winId != HUWIN_NONE) {
        winP = &winData[win->winId];
        HuWinHomeClear(win->winId);
        for(i=0; i<HUWIN_INSERTMES_MAX; i++) {
            winP->messDataInsert[i] = NULL;
        }
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

/* 43 insns */
void MdMessWinInsertMultiMesSet(MDMESS_WORK *mess, int winNo, u32 mes, u32 *insertMes)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    int i;
    if(win->winId != HUWIN_NONE) {
        for(i=0; i<8; i++) {
            if(insertMes[i] != (u32)-1) {
                HuWinInsertMesSet(win->winId, insertMes[i], i);
            }
        }
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

/* 22 insns */
void MdMessWinPad1Set(MDMESS_WORK *mess, int winNo)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    if(win->winId != HUWIN_NONE) {
        HuWinDisablePlayerSet(win->winId, HUWIN_PLAYER_2|HUWIN_PLAYER_3|HUWIN_PLAYER_4);
    }
}

/* 20 insns */
void MdMessWinAttrReset(MDMESS_WORK *mess, int winNo, u32 attr)
{
    MDMESS_HELPWIN *win = &mess->win[winNo];
    HuWinAttrReset(win->winId, attr);
}

/* 1 insns */
void fn_1_F980(void)
{
}

/* 73 insns */
void MdMathPolarCoord(HuVecF *out, HuVecF center, float scaleZ, float scaleX, float radius, float angle)
{
    HuVecF ofs = { 0, 0, 0 };
    ofs.z -= radius*(scaleZ*HuCos(angle));
    ofs.x -= radius*(scaleX*HuSin(angle));
    VECAdd(&ofs, &center, &ofs);
    *out = ofs;
}

/* 361 insns */
void ObjSelectUpdate(void)
{
    MDMODEL_WORK *model = sysP->model; //r31
    MDCAMERA_WORK *cameraWork = sysP->camera;
    int i; //r30
    int mdlNo; //r29
    float scale; //f29
    float s; //f28
    float baseZ; //f31
    float z; //f30
    HuVecF dir;
    Mtx mtx;
    for(i=0; i<=22; i++) {
        if(i == 4) {
            continue;
        }
        mdlNo = i+3;
        VECSubtract(&Hu3DCamera[0].pos, model->posP[mdlNo], &dir);
        MdMathMtxRotCalc(&dir, &Hu3DCamera[0].up, 0, mtx);
        MdMathMtxRotGet(mtx, &dir);
        *model->rotP[mdlNo] = dir;
        if(i < 5) {
            Hu3DModelLayerSet(model->mdlId[mdlNo], 1);
        }
        if(!sysP->unk3D8) {
            continue;
        }
        if(i < 5) {
            scale = 1.0f;
        } else {
            scale = 0.4f;
        }
        if(model->selMode[mdlNo] == 1) {
            model->selT[mdlNo] += 0.1f;
            if(model->selT[mdlNo] > 1.0f) {
                model->selT[mdlNo] = 1.0f;
            }
            model->selMode[mdlNo] = 0;
        } else if(model->selMode[mdlNo] == 0) {
            model->selT[mdlNo] -= 0.1f;
            if(model->selT[mdlNo] < 0.0f) {
                model->selT[mdlNo] = 0.0f;
            }
        } else if(model->selMode[mdlNo] == 2) {
            model->selT[mdlNo] -= 0.025f;
            if(model->selT[mdlNo] < 0.0f) {
                model->selMode[mdlNo] = 0;
                model->selT[mdlNo] = 0.0f;
            }
        }
        s = scale+((0.5f*scale)*((1.0-HuCos(180*model->selT[mdlNo]))/2.0));
        model->scaleP[mdlNo]->z = s;
        model->scaleP[mdlNo]->y = s;
        model->scaleP[mdlNo]->x = s;
    }
    if(sysP->unk3DC) {
        Hu3DModelLayerSet(model->mdlId[sysP->unk3DC+2], 3);
    }
    *model->posP[7] = *model->posP[4];
    *model->rotP[7] = *model->rotP[4];
    Hu3DModelLayerSet(model->mdlId[7], Hu3DData[model->mdlId[4]].layerNo);
    baseZ = model->posP[3]->z;
    for(i=8; i<=12; i++) {
        z = model->posP[i]->z;
        if(baseZ >= z) {
            Hu3DModelLayerSet(model->mdlId[i], 3);
        } else {
            Hu3DModelLayerSet(model->mdlId[i], 6);
        }
    }
    baseZ = model->posP[4]->z;
    for(i=13; i<=14; i++) {
        z = model->posP[i]->z;
        if(baseZ >= z) {
            Hu3DModelLayerSet(model->mdlId[i], 3);
        } else {
            Hu3DModelLayerSet(model->mdlId[i], 6);
        }
    }
    baseZ = model->posP[5]->z;
    for(i=15; i<=19; i++) {
        z = model->posP[i]->z;
        if(baseZ >= z) {
            Hu3DModelLayerSet(model->mdlId[i], 3);
        } else {
            Hu3DModelLayerSet(model->mdlId[i], 6);
        }
    }
    baseZ = model->posP[6]->z;
    for(i=20; i<=25; i++) {
        z = model->posP[i]->z;
        if(baseZ >= z) {
            Hu3DModelLayerSet(model->mdlId[i], 3);
        } else {
            Hu3DModelLayerSet(model->mdlId[i], 6);
        }
    }
}

/* 30 insns */
void MdMathMtxRotGet(Mtx mtx, HuVecF *rot)
{
    float temp;
    Hu3DMtxRotGet(mtx, rot);
    if(rot->y == -90.0f) {
        temp = -rot->z;
        rot->z = -rot->x;
        rot->x = temp;
    }
}

/* 121 insns */
void MdMathMtxRotCalc(HuVecF *dir, HuVecF *up, float roll, Mtx out)
{
    HuVecF upDef[2] = {
        { 0, 1, 0 },
        { 0, 0, 1 }
    };
    Mtx rollMtx;
    HuVecF cross;
    HuVecF cross2;
    HuVecF dirN;
    HuVecF upN;
    float absY;
    VECNormalize(dir, &dirN);
    if(up) {
        VECNormalize(up, &upN);
    } else {
        absY = (dirN.y > 0) ? dirN.y : -dirN.y;
        if(absY < 0.98f) {
            upN = upDef[0];
        } else {
            upN = upDef[1];
        }
    }
    VECCrossProduct(&upN, &dirN, &cross);
    VECNormalize(&cross, &cross);
    VECCrossProduct(&dirN, &cross, &cross2);
    VECNormalize(&cross2, &cross2);
    out[0][0] = cross.x;
    out[1][0] = cross.y;
    out[2][0] = cross.z;
    out[0][1] = cross2.x;
    out[1][1] = cross2.y;
    out[2][1] = cross2.z;
    out[0][2] = dirN.x;
    out[1][2] = dirN.y;
    out[2][2] = dirN.z;
    if(!up) {
        MTXRotDeg(rollMtx, 'z', roll);
        MTXConcat(out, rollMtx, out);
    }
}

/* 150 insns */
void MdMath3Dto2D(HuVecF *pos, s16 cameraBit, HuVecF *out)
{
    s16 i;
    HU3DCAMERA *camera;
    Mtx lookAt;
    HuVecF viewPos;
    float x;
    float y;
    for(i=0; i<16; i++) {
        if(cameraBit & (1 << i)) {
            break;
        }
    }
    camera = &Hu3DCamera[i];
    C_MTXLookAt(lookAt, &camera->pos, &camera->up, &camera->target);
    MTXMultVec(lookAt, pos, &viewPos);
    x = (viewPos.z*(HuSin(camera->fov/2.0f)/HuCos(camera->fov/2.0f)))*1.2f;
    y = viewPos.z*(HuSin(camera->fov/2.0f)/HuCos(camera->fov/2.0f));
    out->x = 288.0f+(viewPos.x*(288.0f/-x));
    out->y = 240.0f+(viewPos.y*(240.0f/y));
    out->z = viewPos.z;
}
