#ifndef REL_MDOMAKEDLL_H
#define REL_MDOMAKEDLL_H

/*
 * mdomakedll (Bonus Mode hub): types, cross-unit globals and prototypes shared by its units
 * (mdomake, object, stage). Types are the mdstory/mdmini/mdsel twins' (same names and
 * layouts where the reference shows the same layout); SYS and the work sizes are measured
 * from mdomake.s (fields.py, ObjectSetup's HuMemDirectMallocNum sizes).
 */

#include "game/object.h"
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/hu3d.h"
#include "game/window.h"
#include "game/process.h"
#include "game/pad.h"
#include "game/disp.h"

#ifndef __MWERKS__
/* host only: retail calls Hu3D2Dto3D/Hu3D3Dto2D unprototyped (the u16 camera bit goes unextended);
 * the host gets hsfex.h's prototypes */
#include "game/hsfex.h"
#endif

#define MDMATH_OSC_0 0
#define MDMATH_OSC_90 1
#define MDMATH_OSC_90_REV 2
#define MDMATH_OSC_180 3
#define MDMATH_OSC_360 4
#define MDMATH_OSC_540 5
#define MDMATH_OSC_720 6

#define MD_OVLCALL_GOTO 0
#define MD_OVLCALL_CALL 1
#define MD_OVLCALL_RETURN 2
#define MDOMAKE_OVLCALL_VOLLEY 3 /* omOvlCallEx(nextDll, 1, 0, 0): Beach Volley */
#define MDOMAKE_OVLCALL_HOCKEY 4 /* omOvlCallEx(nextDll, 1, 1, 0): Ice Hockey */

#define MDMESS_WIN_SPEAKER 0
#define MDMESS_WIN_NOSPEAKER 1
#define MDMESS_WIN_LIST_END -1

#define MDMATH_CURVE_SAMPLE_MAX 8

#define MDLIGHT_MAX 1

#define MdProcCall(idx, arg) MdProcTbl[idx](arg)

#define MDSPR_GRP_MEMBERNO(grp, spr) ((spr)-(grp##_START))
#define MDSPR_GRP_INFO_DEFINE(grp, posX, posY) { grp##_START, grp##_END, posX, posY }

enum {
    MDMATH_CURVE_STD_BOUNCE, //0
    MDMATH_CURVE_STD_LINE, //1
    MDMATH_CURVE_STD_MAX // 2
};

enum {
    MD_DEBUGFONT_CTRL_NOP, //0
    MD_DEBUGFONT_CTRL_CAMERA, //1
    MD_DEBUGFONT_CTRL_LIGHT, //2
    MD_DEBUGFONT_CTRL_MODEL, //3
    MD_DEBUGFONT_CTRL_MAX //4
};

enum {
    MDCAMERA_BG, //0
    MDCAMERA_MAIN, //1
    MDCAMERA_FG, //2
    MDCAMERA_MAX //3
};

enum {
    MDCAMERA_FOCUS_TARGET, // 0
    MDCAMERA_FOCUS_POS, //1
    MDCAMERA_FOCUS_MAX //2
};

enum {
    MDMESS_WIN_MAIN, //0
    MDMESS_WIN_HELP, //1
    MDMESS_WIN_MAX //2
};

enum {
    MDLIGHT_TYPE_NOP, //0
    MDLIGHT_TYPE_G_DIRECT, //1
    MDLIGHT_TYPE_L_DIRECT, //2
    MDLIGHT_TYPE_G_POINT, //3
    MDLIGHT_TYPE_L_POINT, //4
    MDLIGHT_TYPE_G_SPOT, //5
    MDLIGHT_TYPE_L_SPOT, //6
    MDLIGHT_TYPE_MAX
};

typedef void (*MD_FUNC)(void);
typedef BOOL (*MD_PROC)(int param);

/* MdFlowTbl (.data 0x1A4, 2 entries) */
enum {
    MDOMAKE_FLOW_INIT, //0 fn_1_1700 (twin MdSelFlowInit)
    MDOMAKE_FLOW_MAIN, //1 fn_1_192C (twin MdSelFlowMain)
    MDOMAKE_FLOW_MAX //2
};

/* MdProcTbl (.data 0x1AC, 7 entries) */
enum {
    MDOMAKE_PROC_RESET, //0 fn_1_28BC (mdparty MdPartyProcReset)
    MDOMAKE_PROC_CAMERA, //1 fn_1_2A78 (mdmini fn_1_991C)
    MDOMAKE_PROC_UNK2, //2 fn_1_2BF8 (mdstory fn_1_4A98)
    MDOMAKE_PROC_WIN, //3 fn_1_34F0 (mdmini fn_1_AF34)
    MDOMAKE_PROC_UNK4, //4 fn_1_3C24 (mdmini fn_1_E44C, 0.53)
    MDOMAKE_PROC_UNK5, //5 fn_1_4F34 (mdmini fn_1_10264, 0.53)
    MDOMAKE_PROC_NAME, //6 fn_1_54F0 (mdmini fn_1_149A4)
    MDOMAKE_PROC_MAX //7
};

/* stage.s SpriteAnimFile (9 files, mdomake dir 0x91) / SpriteInfo (14) / SpriteGrpInfo (4):
 * MDSPRITE_WORK is 0x48 (ObjectSetup mallocs 72). */
enum {
    MDSPR_ANIM_WIN_FRAME, //0 (file 10)
    MDSPR_ANIM_WIN_BG, //1 (11)
    MDSPR_ANIM_CURSOR, //2 (8)
    MDSPR_ANIM_CURSOR_GLOW, //3 (9)
    MDSPR_ANIM_EFFECT, //4 (12; particle texture, no SpriteInfo user)
    MDSPR_ANIM_TOUEI_00, //5 (13; MdToueiMdlInit, cap 0)
    MDSPR_ANIM_TOUEI_01, //6 (14; cap 1)
    MDSPR_ANIM_TOUEI_02, //7 (15; cap 2)
    MDSPR_ANIM_NAME, //8 (16)
    MDSPR_ANIM_MAX //9
};

enum {
    MDSPR_WIN_FRAME_TOP, //0
    MDSPR_WIN_FRAME_BOTTOM, //1
    MDSPR_WIN_BG, //2
    MDSPR_CURSOR_LR_R, //3
    MDSPR_CURSOR_LR_L, //4
    MDSPR_CURSOR_UDLR_R, //5
    MDSPR_CURSOR_UDLR_L, //6
    MDSPR_CURSOR_UDLR_U, //7
    MDSPR_CURSOR_UDLR_D, //8
    MDSPR_CURSOR_GLOW_UDLR_R, //9
    MDSPR_CURSOR_GLOW_UDLR_L, //10
    MDSPR_CURSOR_GLOW_UDLR_U, //11
    MDSPR_CURSOR_GLOW_UDLR_D, //12
    MDSPR_NAME, //13
    MDSPR_MAX //14
};

enum {
    MDSPR_GRP_WIN, //0
    MDSPR_GRP_CURSOR_LR, //1
    MDSPR_GRP_CURSOR_UDLR, //2
    MDSPR_GRP_NAME, //3
    MDSPR_GRP_MAX //4
};

enum {
    MDSPR_GRP_WIN_START = MDSPR_WIN_FRAME_TOP,
    MDSPR_GRP_WIN_END = MDSPR_WIN_BG,
    MDSPR_GRP_CURSOR_LR_START = MDSPR_CURSOR_LR_R,
    MDSPR_GRP_CURSOR_LR_END = MDSPR_CURSOR_LR_L,
    MDSPR_GRP_CURSOR_UDLR_START = MDSPR_CURSOR_UDLR_R,
    MDSPR_GRP_CURSOR_UDLR_END = MDSPR_CURSOR_GLOW_UDLR_D,
    MDSPR_GRP_NAME_START = MDSPR_NAME,
    MDSPR_GRP_NAME_END = MDSPR_NAME
};

enum {
    MDOMAKE_OBJ_DEBUGFONT, // 0
    MDOMAKE_OBJ_PAD, //1
    MDOMAKE_OBJ_CAMERA, //2
    MDOMAKE_OBJ_LIGHT, //3
    MDOMAKE_OBJ_MAX //4
};

/* MdPosAdjustMode mdlInfo$1113 (.data 0x400, 6 names): MDMODEL_WORK is 0x60 (ObjectSetup mallocs 96). */
enum {
    MDMODEL_STAR, //0
    MDMODEL_STAGE, //1
    MDMODEL_CAP_00, //2 Card Party
    MDMODEL_CAP_01, //3 Beach Volley
    MDMODEL_CAP_02, //4 Ice Hockey
    MDMODEL_FONTBGFILTER, //5
    MDMODEL_MAX //6
};

#define MDMODEL_CAP_NUM 3

enum {
    MDMODEL_MOT_STAR_IDLE, //0
    MDMODEL_MOT_STAR_TALK, //1
    MDMODEL_MOT_STAR_TALK_FAST, //2
    MDMODEL_MOT_MAX //3
};

typedef struct MdDebugFontWork_s {
    BOOL createF; //0x00
    int ctrl; //0x04
    BOOL printF; //0x08
    int color; //0x0C
    s16 posX; //0x10
    s16 posY; //0x12
    s16 ofsY; //0x14
    s16 rowOfsY; //0x16
    s16 rowH; //0x18
    s16 maxLen; //0x1A
    float size; //0x1C
} MDDEBUGFONT_WORK;

typedef struct MdPadWork_s {
    u16 DStkDown[4];
    u16 DStk[4];
} MDPAD_WORK;

typedef struct MdCameraTypeInfo_s {
    int bit;
    int focusType;
} MDCAMERA_TYPE_INFO;

typedef struct MdCameraRect_s {
    float x;
    float y;
    float w;
    float h;
} MDCAMERA_RECT;

typedef struct MdCameraParam_s {
    HuVecF hvr;
    HuVecF center;
} MDCAMERA_PARAM;

typedef struct MdCamera_s {
    u16 bit; //0x00
    int focusType; //0x04
    HuVecF pos; //0x08
    HuVecF target; //0x14
    HuVecF cross; //0x20
    HuVecF up; //0x2C
    HuVecF dir; //0x38
    HuVecF hvr; //0x44
    float unk50;
    HuVecF center; //0x54
    HuVecF unk60[3];
    float fovy; //0x84
} MDCAMERA;

typedef struct MdCameraWork_s {
    BOOL createF; //0x00
    MDDEBUGFONT_WORK *debugFont; //0x04
    MDCAMERA camera[MDCAMERA_MAX]; //0x08
    int selCamera;
} MDCAMERA_WORK;

typedef struct MdLight_s {
    s16 type; //0x00
    HU3DLIGHTID gLightId; //0x02
    HU3DLLIGHTID lLightId; //0x04
    HuVecF hvr; //0x08
    HuVecF center; //0x14
    HuVecF pos; //0x20
    HuVecF target; //0x2C
    HuVecF lightPos; //0x38
    HuVecF lightDir; //0x44
    GXColor rgb; //0x50
} MDLIGHT;

typedef struct MdLightWork_s {
    BOOL createF; //0x00
    int lightSel; //0x04
    MDDEBUGFONT_WORK *debugFont; //0x08
    MDLIGHT light[MDLIGHT_MAX]; //0x0C
} MDLIGHT_WORK;

typedef struct MdSpriteWork_s {
    ANIMDATA *animP[MDSPR_ANIM_MAX]; //0x00
    HUSPRID sprId[MDSPR_MAX]; //0x24
    HUSPRGRPID grpId[MDSPR_GRP_MAX]; //0x40
} MDSPRITE_WORK;

typedef struct MdModelDebugInfo_s {
    char *name; //0x00
    int cameraNo; //0x04
} MDMODEL_DEBUG_INFO;

typedef struct MdModelWork_s {
    HU3DMODELID mdlId[MDMODEL_MAX]; //0x00
    HU3DMOTID motId[MDMODEL_MOT_MAX]; //0x0C
    HU3DANIMID animId[MDMODEL_CAP_NUM]; //0x12 (MdToueiMdlInit)
    HuVecF *posP[MDMODEL_MAX]; //0x18
    HuVecF *rotP[MDMODEL_MAX]; //0x30
    HuVecF *scaleP[MDMODEL_MAX]; //0x48
} MDMODEL_WORK;

typedef struct MdMessWin_s {
    s16 mode;
    HUWINID winId; //0x02
    s16 choice; //0x04
    s16 unk6;
    s16 type; //0x08
    s16 unkA;
} MDMESS_WIN;

typedef struct MdMess_s {
    MDMESS_WIN win[MDMESS_WIN_MAX];
} MDMESS_WORK;

typedef struct MdSprInfo_s {
    s16 animNo; //0x00
    s16 pri; //0x02
    HuVec2f pos; //0x04
    HuVec2f scale; //0xC
    float tpLvl; //0x14
} MDSPR_INFO;

typedef struct MdSprGrpInfo_s {
    s16 start; //0x00
    s16 end; //0x02
    float posX; //0x04
    float posY; //0x08
} MDSPR_GRP_INFO;

typedef struct MdOmakeStar_s {
    s16 unk0;
    s16 mode; //0x02
    s16 motNext; //0x04
} MDOMAKE_STAR;

/* SYS for mdomake, measured from every sys->/sysP-> access in mdomake.s/stage.s (fields.py):
 * 0xC8 bytes on GC (sysWork's .bss size). Head is mdsel's with two more s8 and more procs. */
typedef struct Sys_s {
    int subMode; //0x00
    int unk4; //0x04
    int flowTime; //0x08
    int flowMode; //0x0C
    int ovlCallMode; //0x10
    OMOVL nextDll; //0x14
    s8 exitF; //0x18
    s8 skipWipeF; //0x19
    s8 selMode; //0x1A selected Bonus game (0 Card Party, 1 Beach Volley, 2 Ice Hockey)
    s8 prevSelMode; //0x1B
    OMOBJMAN *objman; //0x1C
    HUPROCESS *mainProc; //0x20
    HUPROCESS *loadProc; //0x24
    HUPROCESS *starProc; //0x28
    HUPROCESS *movieProc; //0x2C fn_1_1078
    HUPROCESS *mainWinProc; //0x30 fn_1_1314
    HUPROCESS *helpWinProc; //0x34 fn_1_1358
    OMOBJ *obj[MDOMAKE_OBJ_MAX]; //0x38
    OMOVLHIS *ovlHis; //0x48
    s32 evtNo; //0x4C
    s16 movieState; //0x50 fn_1_1078: 1 start the selected cap's movie, 2 switch caps
    s16 loadState; //0x52
    s16 loadAsyncStat; //0x54
    unsigned int loadDir; //0x58
    MDDEBUGFONT_WORK *debugFont; //0x5C
    MDPAD_WORK *pad; //0x60
    MDCAMERA_WORK *camera; //0x64
    MDLIGHT_WORK *light; //0x68
    MDSPRITE_WORK *sprite; //0x6C
    MDMODEL_WORK *model; //0x70
    MDOMAKE_STAR *star; //0x74
    MDMESS_WORK *mess; //0x78
    BOOL winInitF; //0x7C (fn_1_34F0)
    BOOL procInitF; //0x80 (fn_1_3C24, fn_1_4F34)
    BOOL cursorInitF; //0x84 (fn_1_2BF8)
    BOOL nameInitF; //0x88 (fn_1_54F0)
    BOOL unk8C; //0x8C (only cleared, fn_1_28BC)
    int cursorDir; //0x90 last D-pad turn: 0 right (selMode-1), 1 left (selMode+1); fn_1_3C24 param 1
    int unk94; //0x94 (never accessed)
    float procTime; //0x98
    float procOfsTime; //0x9C (fn_1_4F34)
    float unkA0; //0xA0 (only cleared)
    float sprTime; //0xA4 (fn_1_34F0)
    float cursorTime; //0xA8 (fn_1_2BF8 cursor; fn_1_2A78 camera lerp shares it)
    float nameTime; //0xAC (fn_1_54F0)
    float procT; //0xB0
    float procOfsT; //0xB4
    float unkB8; //0xB8 (only cleared)
    float sprT; //0xBC
    float cursorT; //0xC0
    float nameT; //0xC4
} SYS;

#ifdef __MWERKS__
/* GameCube layout proof: sysWork's .bss size and ObjectSetup's HuMemDirectMallocNum sizes. */
typedef char MdOmakeSysSizeCheck[sizeof(SYS) == 0xC8 ? 1 : -1];
typedef char MdOmakeSpriteSizeCheck[sizeof(MDSPRITE_WORK) == 0x48 ? 1 : -1];
typedef char MdOmakeModelSizeCheck[sizeof(MDMODEL_WORK) == 0x60 ? 1 : -1];
typedef char MdOmakeMessSizeCheck[sizeof(MDMESS_WORK) == 0x18 ? 1 : -1];
typedef char MdOmakeStarSizeCheck[sizeof(MDOMAKE_STAR) == 0x6 ? 1 : -1];
typedef char MdOmakeCameraSizeCheck[sizeof(MDCAMERA_WORK) == 0x1A4 ? 1 : -1];
typedef char MdOmakeLightSizeCheck[sizeof(MDLIGHT_WORK) == 0x60 ? 1 : -1];
#endif

extern SYS *sys;
extern SYS *sysP;
extern SYS sysWork;
extern MD_FUNC MdFlowTbl[MDOMAKE_FLOW_MAX];
extern MD_PROC MdProcTbl[MDOMAKE_PROC_MAX];

/* --- mdomake.c --- */
void ObjectSetup(void);
void MdMain(void);
void fn_1_938(void);
void fn_1_1078(void);
void fn_1_1314(void);
void fn_1_1358(void);
void MdInit(void);
void MdClose(void);
void fn_1_1700(void);
void fn_1_192C(void);
BOOL fn_1_28BC(int param);
BOOL fn_1_2A78(int param);
BOOL fn_1_2BF8(int param);
BOOL fn_1_34F0(int param);
BOOL fn_1_3C24(int param);
BOOL fn_1_4F34(int param);
BOOL fn_1_54F0(int param);
void fn_1_5778(int mdlNo, int cameraNo);
void fn_1_5868(int cmd);
int fn_1_5988(int mdlNo, int cameraNo);
void MdPosAdjustMode(void);

/* --- object.c --- */
void MdObjDebugFontCreate(OMOBJ *obj);
void MdObjDebugFontMain(OMOBJ *obj);
void MdObjPadMain(OMOBJ *obj);
void MdObjCameraCreate(OMOBJ *obj);
void MdObjCameraMain(OMOBJ *obj);
void MdObjLightCreate(OMOBJ *obj);
void MdObjLightMain(OMOBJ *obj);

void MdDebugFontCreate(MDDEBUGFONT_WORK *debugFont);
void MdDebugFontUpdate(MDDEBUGFONT_WORK *debugFont);
void MdDebugFontPrint(MDDEBUGFONT_WORK *debugFont, const char *str, ...);

void MdCameraCreate(MDCAMERA_WORK *cameraWork);
void MdCameraDebug(MDCAMERA_WORK *cameraWork);
void MdCameraUpdate(MDCAMERA_WORK *cameraWork);
void MdCameraPrint(MDCAMERA_WORK *cameraWork);
void MdCameraPosSet(MDCAMERA *camera, float h, float v, float r, float cx, float cy, float cz);

void MdLightCreate(MDLIGHT_WORK *lightWork);
void MdLightUpdate(MDLIGHT_WORK *lightWork);
void MdLightUpdateData(MDLIGHT *light);
void MdLightDebug(MDLIGHT_WORK *lightWork);
void MdLightPrint(MDLIGHT_WORK *lightWork);

Mtx *MdMathMatrixDir(HuVecF *start, HuVecF *end);
void MdMathMatrixRot(Mtx *matrix, HuVecF *rot);
void MdMathClamp(float *val, float min, float max);
void MdMathAngleClamp(float *angle);
void MdMathOscillate(int type, float *in, float *out, float t);
void MdMathStdCurveGet(int type, float *in, float *out, float t);
void MdMathLerp(float *out, float a, float b, float t);
void MdMathLerpScale(HuVecF *out, float a, float b, float t);
void MdMathLerpColor(u8 *out, float a, float b, float t);
void MdMathLerpOfs(float *out, float a, float b, float t, float ofs);
void MdMathLerpScaleOfs(HuVecF *out, float a, float b, float t, float ofs);
void MdMathCurveInit(int sampleNum, float *sampleT, float *sample, float *sampleSlope);
void MdMathCurveGet(float *out, int sampleNum, float *sampleT, float *sample, float *sampleSlope, float t);
void MdMathStdCurveInit(void);

void MdMessCreate(MDMESS_WORK *mess);
void MdMessMain(MDMESS_WORK *mess, int winNo);
void MdMessKill(MDMESS_WORK *mess);
void MdMessWinOpen(MDMESS_WORK *mess, int winNo, s16 type, s16 frame, s16 drawNo, s16 pri, float posX, float posY, s16 w, s16 h, float bgTPLvl);
void MdMessWinClose(MDMESS_WORK *mess, int winNo);
void MdMessWinKill(MDMESS_WORK *mess, int winNo);
void MdMessWinPosSet(MDMESS_WORK *mess, int winNo, float posX, float posY);
void MdMessWinSpeedSet(MDMESS_WORK *mess, int winNo, s16 speed);
void MdMessWinPad1Set(MDMESS_WORK *mess, int winNo);
void MdMessWinHomeClear(MDMESS_WORK *mess, int winNo);
void MdMessWinMesSet(MDMESS_WORK *mess, int winNo, BOOL choice, ...);
s16 MdMessWinChoiceNowGet(MDMESS_WORK *mess, int winNo);
void MdMessWinChoiceSet(MDMESS_WORK *mess, int winNo, s16 choice);
int MdMessWinChoiceGet(MDMESS_WORK *mess, int winNo);
s16 MdMessWinStatGet(MDMESS_WORK *mess, int winNo);
BOOL MdMessWinCheck(MDMESS_WORK *mess, int winNo);
void MdMessWinAttrSet(MDMESS_WORK *mess, int winNo, u32 attr);
void MdMessWinAttrReset(MDMESS_WORK *mess, int winNo, u32 attr);

/* --- stage.c --- */
void MdSpriteCreate(MDSPRITE_WORK *sprite);
void MdSpriteDispSet(MDSPRITE_WORK *sprite, int grpNo, BOOL dispF);
HuVec2f *MdSpriteGrpPosGet(MDSPRITE_WORK *sprite, int grpNo);
HuVec2f *MdSpriteGrpScaleGet(MDSPRITE_WORK *sprite, int grpNo);
HuVec2f *MdSpritePosGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);
HuVec2f *MdSpriteScaleGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);
float *MdSpriteAlphaGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);
void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera);
void MdToueiMdlInit(void);

#endif
