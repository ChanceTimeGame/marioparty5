#ifndef _MDSTORYDLL_H
#define _MDSTORYDLL_H

#include "msm_se.h"
#include "msm_stream.h"
#include "msm.h"
#include "game/audio.h"

#include "game/object.h"
#include "game/printfunc.h"
#include "game/hu3d.h"
#include "game/sprite.h"
#include "game/window.h"
#include "game/pad.h"
#include "game/disp.h"

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

#define MDMESS_WIN_SPEAKER 0
#define MDMESS_WIN_NOSPEAKER 1
#define MDMESS_WIN_LIST_END -1

#define MDMATH_CURVE_SAMPLE_MAX 8

#define MDSTORY_TEXBUF_MIRROR 0
#define MDSTORY_TEXBUF_MAX 7

#define MDSTORY_TEXBUF_W 64
#define MDSTORY_TEXBUF_H 64

#define MDMODEL_CAP_MODE_NUM 6

#define MDLIGHT_MAX 1

#define MdProcCall(idx, arg) MdProcTbl[idx](arg)
#define MdProcWait(idx, arg) do { \
    while(!MdProcCall(idx, arg)) { \
        HuPrcVSleep(); \
    } \
} while(0)

#define MDSPR_GRP_MEMBERNO(grp, spr) ((spr)-(grp##_START))

#define MDSPR_GRP_INFO_DEFINE(grp, posX, posY) { grp##_START, grp##_END, posX, posY }

enum {
    MD_LOAD_STATE_NONE,
    MD_LOAD_STATE_BOARD_LOAD,
    MD_LOAD_STATE_WAIT,
    MD_LOAD_STATE_CHAR_LOAD,
    MD_LOAD_STATE_LOAD,
    MD_LOAD_STATE_DONE
};

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
    MDMESS_WIN_MAX //2 (mdparty: 4, with TEAM1/TEAM2)
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

/* fn_1_9384 commands (mdparty MdPartyAudExec; numbering measured from its jump table) */
#define MDSTORY_AUD_MUS_START 0
#define MDSTORY_AUD_MUS_STOP 1
#define MDSTORY_AUD_SE_CMN_MOVE 2 /* MSM_SE_CMN_01 */
#define MDSTORY_AUD_SE_CMN_CONFIRM 3 /* MSM_SE_CMN_03 */
#define MDSTORY_AUD_SE_CMN_CANCEL 4 /* MSM_SE_CMN_04 */
#define MDSTORY_AUD_SE_MENU_28 5 /* MSM_SE_MENU_28 panned on the selected character, handle kept */
#define MDSTORY_AUD_SE_MENU_MOVE 6 /* MSM_SE_MENU_27 */
#define MDSTORY_AUD_UNUSED7 7
#define MDSTORY_AUD_SE_STAR_ENTER 8 /* MSM_SE_GUIDE_52 */
#define MDSTORY_AUD_SE_STAR_CONFIRM 9 /* MSM_SE_GUIDE_52 */
#define MDSTORY_AUD_SE_CHR_MARIO 10
#define MDSTORY_AUD_SE_CHR_LUIGI 11
#define MDSTORY_AUD_SE_CHR_PEACH 12
#define MDSTORY_AUD_SE_CHR_YOSHI 13
#define MDSTORY_AUD_SE_CHR_WARIO 14
#define MDSTORY_AUD_SE_CHR_DAISY 15
#define MDSTORY_AUD_SE_CHR_WALUIGI 16
#define MDSTORY_AUD_SE_ALL_STOP 17

typedef void (*MD_FUNC)(void);
typedef BOOL (*MD_PROC)(int param);


/* MdFlowTbl (.data 0x2D0, 5 entries). Names are guesses from the mdparty twin. */
enum {
    MDSTORY_FLOW_INIT, //0 fn_1_2204 (twin MdPartyFlowInit)
    MDSTORY_FLOW_UNK1, //1 fn_1_24FC
    MDSTORY_FLOW_UNK2, //2 fn_1_2D88
    MDSTORY_FLOW_UNK3, //3 fn_1_3438
    MDSTORY_FLOW_UNK4, //4 fn_1_3C2C
    MDSTORY_FLOW_MAX //5
};

/* MdProcTbl (.data 0x2E4, 10 entries). Names from the mdparty twin where it matches. */
enum {
    MDSTORY_PROC_RESET, //0 fn_1_46E4 (MdPartyProcReset)
    MDSTORY_PROC_CAMERA, //1 fn_1_48EC (MdPartyProcCamera)
    MDSTORY_PROC_UNK2, //2 fn_1_4A98
    MDSTORY_PROC_WIN, //3 fn_1_53D4 (MdPartyProcWin)
    MDSTORY_PROC_CHR, //4 fn_1_5B08 (MdPartyProcChr)
    MDSTORY_PROC_CAP_TURN, //5 fn_1_709C (MdPartyProcCapTurn)
    MDSTORY_PROC_CAP_PACK, //6 fn_1_766C (MdPartyProcCapPack)
    MDSTORY_PROC_UNK7, //7 fn_1_7FB4
    MDSTORY_PROC_FINGER, //8 fn_1_81F8 (MdPartyProcFinger)
    MDSTORY_PROC_NAME, //9 fn_1_8388 (MdPartyProcName)
    MDSTORY_PROC_MAX //10
};

/* stage.s SpriteAnimFile (10 files, mdstory dir 0x95) / SpriteInfo (15) / SpriteGrpInfo (5):
 * MDSPRITE_WORK is 0x50 (ObjectSetup mallocs 80). Anim names follow mdparty's order; 5-8 unverified. */
enum {
    MDSPR_ANIM_WIN_FRAME, //0 (file 0x2D)
    MDSPR_ANIM_WIN_BG, //1 (0x2E)
    MDSPR_ANIM_CURSOR, //2 (0x2B)
    MDSPR_ANIM_CURSOR_GLOW, //3 (0x2C)
    MDSPR_ANIM_PLAYERNO, //4 (0x31)
    MDSPR_ANIM_UNK5, //5 (0x32)
    MDSPR_ANIM_UNK6, //6 (0x33)
    MDSPR_ANIM_UNK7, //7 (0x2F)
    MDSPR_ANIM_UNK8, //8 (0x30)
    MDSPR_ANIM_NAME, //9 (0x34)
    MDSPR_ANIM_MAX //10
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
    MDSPR_PLAYERNO_1P, //13
    MDSPR_NAME, //14
    MDSPR_MAX //15
};

enum {
    MDSPR_GRP_WIN, //0
    MDSPR_GRP_CURSOR_LR, //1
    MDSPR_GRP_CURSOR_UDLR, //2
    MDSPR_GRP_PLAYERNO, //3
    MDSPR_GRP_NAME, //4
    MDSPR_GRP_MAX //5
};

enum {
    MDSPR_GRP_WIN_START = MDSPR_WIN_FRAME_TOP,
    MDSPR_GRP_WIN_END = MDSPR_WIN_BG,
    MDSPR_GRP_CURSOR_LR_START = MDSPR_CURSOR_LR_R,
    MDSPR_GRP_CURSOR_LR_END = MDSPR_CURSOR_LR_L,
    MDSPR_GRP_CURSOR_UDLR_START = MDSPR_CURSOR_UDLR_R,
    MDSPR_GRP_CURSOR_UDLR_END = MDSPR_CURSOR_GLOW_UDLR_D,
    MDSPR_GRP_PLAYERNO_START = MDSPR_PLAYERNO_1P,
    MDSPR_GRP_PLAYERNO_END = MDSPR_PLAYERNO_1P,
    MDSPR_GRP_NAME_START = MDSPR_NAME,
    MDSPR_GRP_NAME_END = MDSPR_NAME,
};

enum {
    MDSTORY_OBJ_DEBUGFONT, // 0
    MDSTORY_OBJ_PAD, //1
    MDSTORY_OBJ_CAMERA, //2
    MDSTORY_OBJ_LIGHT, //3
    MDSTORY_OBJ_MAX //4
};

/* MdPosAdjustMode mdlInfo$1113 (.data 0x794, 26 names): MDMODEL_WORK is 0x1A0 (ObjectSetup mallocs 416). */
enum {
    MDMODEL_STAR, //0
    MDMODEL_STAGE, //1
    MDMODEL_STAGE_CHR, //2
    MDMODEL_MARIO, //3
    MDMODEL_LUIGI, //4
    MDMODEL_PEACH, //5
    MDMODEL_YOSHI, //6
    MDMODEL_WARIO, //7
    MDMODEL_DAISY, //8
    MDMODEL_WALUIGI, //9
    MDMODEL_CAP_CHR_00, //10
    MDMODEL_CAP_CHR_01, //11
    MDMODEL_CAP_CHR_02, //12
    MDMODEL_CAP_CHR_03, //13
    MDMODEL_CAP_CHR_04, //14
    MDMODEL_CAP_CHR_05, //15
    MDMODEL_CAP_CHR_06, //16
    MDMODEL_CAP_PACK_00, //17
    MDMODEL_CAP_PACK_01, //18
    MDMODEL_CAP_PACK_02, //19
    MDMODEL_CAP_PACK_03, //20
    MDMODEL_CAP_PACK_04, //21
    MDMODEL_CAP_LV, //22
    MDMODEL_FINGER_1P, //23
    MDMODEL_RING_1P, //24
    MDMODEL_FONTBGFILTER, //25
    MDMODEL_MAX //26
};

/* two anims (0x64); targets unverified */
enum {
    MDMODEL_ANIM_FINGER_1P, //0
    MDMODEL_ANIM_UNK1, //1
    MDMODEL_ANIM_MAX //2
};

/* StarMotTbl (3) + CharMotTbl (7 characters x 3) */
enum {
    MDMODEL_MOT_STAR_IDLE, //0
    MDMODEL_MOT_STAR_TALK, //1
    MDMODEL_MOT_STAR_TALK_FAST, //2
    MDMODEL_MOT_CHR_START, //3: character c's motion m is MDMODEL_MOT_CHR_START + c*3 + m
    MDMODEL_MOT_MAX = MDMODEL_MOT_CHR_START + 7 * 3 //24
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
    HUSPRID sprId[MDSPR_MAX]; //0x5C
    HUSPRGRPID grpId[MDSPR_GRP_MAX]; //0xAA
} MDSPRITE_WORK;

typedef struct MdModelDebugInfo_s {
    char *name; //0x00
    int cameraNo; //0x04
} MDMODEL_DEBUG_INFO;

typedef struct MdModelWork_s {
    HU3DMODELID mdlId[MDMODEL_MAX]; //0x00
    HU3DMOTID motId[MDMODEL_MOT_MAX]; //0x72
    HU3DANIMID animId[MDMODEL_ANIM_MAX]; //0xA0
    HuVecF *posP[MDMODEL_MAX]; //0xAC
    HuVecF *rotP[MDMODEL_MAX]; //0x190
    HuVecF *scaleP[MDMODEL_MAX]; //0x274
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

typedef struct MdTexBufUnit_s {
    void *addr; //0x00
    GXTexObj texObj; //0x04
    s16 posX; //0x24
    s16 posY; //0x26
    u16 w; //0x28
    u16 h; //0x2A
    GXTexFmt texFmt; //0x2C
} MDTEXBUF_UNIT;

typedef struct MdTexBufWork_s {
    MDTEXBUF_UNIT unit[MDSTORY_TEXBUF_MAX]; //0x00 (no trailing word: ObjectSetup mallocs 0x150)
} MDTEXBUF_WORK;

typedef struct MdRing_s {
    BOOL disp; //0x00
    int mode; //0x04
    GXColor color; //0x08
    GXColor endColor; //0x0C
    int unk10;
    float time; //0x14
    float ofsTime; //0x18
    float t; //0x1C
    float ofsT; //0x20
    int mdlNo; //0x24
    HuVecF **posP; //0x28
    HuVecF **rotP; //0x2C
    HuVecF **scaleP; //0x30
    int baseMdlNo; //0x34
    HuVecF baseOfs; //0x38
} MDRING;

typedef struct MdRingWork_s {
    MDRING ring[1]; //0x00 (one player)
    float scale; //0x44
} MDRING_WORK;

/* mdstory.c state values (same as mdmini/mdparty's twins) */
#define MDSTORY_STAR_NONE 0

typedef struct MdStoryPlayerSpr_s {
    int mode; //0x00
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
} MDSTORY_PLAYERSPR;

typedef struct MdStoryChar_s {
    int mode; //0x00
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
    HuVecF origPos; //0x14
    HuVecF pos; //0x20
    HuVecF origRot; //0x2C
    HuVecF rot; //0x38
} MDSTORY_CHR;

typedef struct MdStoryStar_s {
    s16 unk0;
    s16 mode; //0x02
    s16 motNext; //0x04
} MDSTORY_STAR;

/* SYS for mdstory, measured from every sys-> access in mdstory.s (fields.py): 0x370 bytes on GC.
 * The layout is mdparty's with the 4-player and team parts removed: one playerSpr, seven chr.
 * Names are mdparty's where the twin function uses the same field; unkXXX otherwise. */
typedef struct Sys_s {
    int subMode; //0x00
    int unk4; //0x04
    int flowTime; //0x08
    int flowMode; //0x0C
    int ovlCallMode; //0x10
    OMOVL nextDll; //0x14
    s8 exitF; //0x18
    s8 skipWipeF; //0x19
    s8 unk1A; //0x1A (fn_1_8610, mdparty MdPartyPadSetupStory)
    s8 padConnect[4]; //0x1B (fn_1_8610, mdparty padConnect)
    s8 padNoConnect[4]; //0x1F (fn_1_8610, mdparty padNoConnect)
    s8 padNoEnable[4]; //0x23 (fn_1_872C, mdparty padNoEnable; fn_1_2D88 also reads it as a preselected character, -1 = none)
    s8 chrSel[4]; //0x27 per player: selected character ([0] is the story player; fn_1_2D88 copies padNoEnable here)
    s8 chrSelEnd[4]; //0x2B per player: character decided (fn_1_2D88 sets [0] on A, fn_1_3438 clears it)
    s8 unk2F; //0x2F
    s8 unk30; //0x30
    OMOBJMAN *objman; //0x34
    HUPROCESS *mainProc; //0x38
    HUPROCESS *loadProc; //0x3C
    HUPROCESS *starProc; //0x40
    HUPROCESS *playerSprProc; //0x44
    HUPROCESS *chrProc; //0x48
    HUPROCESS *ringProc; //0x4C
    HUPROCESS *mainWinProc; //0x50
    HUPROCESS *textWinProc; //0x54
    OMOBJ *obj[MDSTORY_OBJ_MAX]; //0x58
    OMOVLHIS *ovlHis; //0x68
    s32 evtNo; //0x6C
    s16 loadState; //0x70
    s16 loadAsyncStat; //0x72
    unsigned int loadDir; //0x74
    s16 loadProcReady; //0x78
    MDDEBUGFONT_WORK *debugFont; //0x7C
    MDPAD_WORK *pad; //0x80
    MDCAMERA_WORK *camera; //0x84
    MDLIGHT_WORK *light; //0x88
    MDSPRITE_WORK *sprite; //0x8C
    MDMODEL_WORK *model; //0x90
    MDTEXBUF_WORK *texbuf; //0x94
    MDSTORY_STAR *star; //0x98
    MDRING_WORK *ring; //0x9C (read by every Ring* function in stage.s)
    MDSTORY_PLAYERSPR playerSpr[1]; //0xA0
    MDSTORY_CHR chr[7]; //0xB4
    MDMESS_WORK *mess; //0x290
    BOOL dirtyF; //0x294 (procs 46E4/5B08/709C/766C/7FB4/81F8: the per-proc init flag)
    BOOL unk298; //0x298 (only cleared, fn_1_46E4)
    BOOL unk29C; //0x29C (fn_1_4A98)
    BOOL winInitF; //0x2A0 (fn_1_53D4)
    BOOL nameInitF; //0x2A4 (fn_1_8388)
    BOOL unk2A8; //0x2A8 (only cleared, fn_1_46E4)
    int cursorDir; //0x2AC
    int unk2B0; //0x2B0 (never accessed)
    float procTime; //0x2B4
    float procOfsTime; //0x2B8
    float cameraTime; //0x2BC
    float cameraTotalTime; //0x2C0
    float unk2C4; //0x2C4 (fn_1_4A98)
    float sprTime; //0x2C8 (fn_1_53D4)
    float nameTime; //0x2CC
    float procT; //0x2D0
    float procOfsT; //0x2D4
    float cameraT; //0x2D8
    float cameraTotalT; //0x2DC
    float unk2E0; //0x2E0 (fn_1_4A98)
    float sprT; //0x2E4
    float nameT; //0x2E8
    float curveTime[8]; //0x2EC
    float curveSlope[25]; //0x30C
} SYS;

#ifdef __MWERKS__
/* GameCube layout proof: sysWork's .bss size and ObjectSetup's HuMemDirectMallocNum sizes. */
typedef char MdStorySysSizeCheck[sizeof(SYS) == 0x370 ? 1 : -1];
typedef char MdStorySpriteSizeCheck[sizeof(MDSPRITE_WORK) == 0x50 ? 1 : -1];
typedef char MdStoryModelSizeCheck[sizeof(MDMODEL_WORK) == 0x1A0 ? 1 : -1];
typedef char MdStoryTexBufSizeCheck[sizeof(MDTEXBUF_WORK) == 0x150 ? 1 : -1];
typedef char MdStoryRingSizeCheck[sizeof(MDRING_WORK) == 0x48 ? 1 : -1];
typedef char MdStoryMessSizeCheck[sizeof(MDMESS_WORK) == 0x18 ? 1 : -1];
typedef char MdStoryStarSizeCheck[sizeof(MDSTORY_STAR) == 0x6 ? 1 : -1];
typedef char MdStoryCameraSizeCheck[sizeof(MDCAMERA_WORK) == 0x1A4 ? 1 : -1];
typedef char MdStoryLightSizeCheck[sizeof(MDLIGHT_WORK) == 0x60 ? 1 : -1];
#endif

extern SYS *sys;
extern SYS *sysP;
extern SYS sysWork;
extern MD_FUNC MdFlowTbl[MDSTORY_FLOW_MAX];
extern MD_PROC MdProcTbl[MDSTORY_PROC_MAX];

void MdMain(void);
void MdInit(void);
void MdClose(void);

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

void MdMessCreate(MDMESS_WORK *mess);
void MdMessKill(MDMESS_WORK *mess);
void MdMessMain(MDMESS_WORK *mess, int winNo);
void MdMessWinOpen(MDMESS_WORK *mess, int winNo, s16 type, s16 frame, s16 drawNo, s16 pri, float posX, float posY, s16 w, s16 h, float bgTPLvl);
void MdMessWinClose(MDMESS_WORK *mess, int winNo);
void MdMessWinKill(MDMESS_WORK *mess, int winNo);
void MdMessWinPosSet(MDMESS_WORK *mess, int winNo, float posX, float posY);
void MdMessWinScaleSet(MDMESS_WORK *mess, int winNo, float scaleX, float scaleY);
void MdMessWinCenterPosSet(MDMESS_WORK *mess, int winNo, float posX, float posY);

void MdMessWinSpeedSet(MDMESS_WORK *mess, int winNo, s16 speed);
void MdMessWinAttrSet(MDMESS_WORK *mess, int winNo, u32 attr);
void MdMessWinAttrReset(MDMESS_WORK *mess, int winNo, u32 attr);
void MdMessWinPad1Set(MDMESS_WORK *mess, int winNo);
void MdMessWinMesSet(MDMESS_WORK *mess, int winNo, BOOL choice, ...);
BOOL MdMessWinCheck(MDMESS_WORK *mess, int winNo);
s16 MdMessWinChoiceNowGet(MDMESS_WORK *mess, int winNo);
void MdMessWinChoiceSet(MDMESS_WORK *mess, int winNo, s16 choice);
int MdMessWinChoiceGet(MDMESS_WORK *mess, int winNo);
void MdMessWinHomeClear(MDMESS_WORK *mess, int winNo);
s16 MdMessWinStatGet(MDMESS_WORK *mess, int winNo);

Mtx *MdMathMatrixDir(HuVecF *start, HuVecF *end);
void MdMathMatrixRot(Mtx *matrix, HuVecF *rot);

void MdMathClamp(float *val, float min, float max);

void MdMathAngleClamp(float *angle);


void MdMathOscillate(int type, float *in, float *out, float t);
void MdMathLerp(float *out, float a, float b, float t);
void MdMathLerpOfs(float *out, float a, float b, float t, float ofs);
void MdMathLerpColor(u8 *out, float a, float b, float t);
void MdMathLerpScale(HuVecF *out, float a, float b, float t);
void MdMathLerpScaleOfs(HuVecF *out, float a, float b, float t, float ofs);
void MdMathStdCurveGet(int type, float *in, float *out, float t);

void MdMathCurveInit(int sampleNum, float *sampleT, float *sample, float *sampleSlope);
void MdMathCurveGet(float *out, int sampleNum, float *sampleT, float *sample, float *sampleSlope, float t);
void MdMathStdCurveInit(void);

void MdSpriteCreate(MDSPRITE_WORK *sprite);
HuVec2f *MdSpritePosGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);
HuVec2f *MdSpriteScaleGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);
float *MdSpriteAlphaGet(MDSPRITE_WORK *sprite, int grpNo, int memberNo);

void MdSpriteDispSet(MDSPRITE_WORK *sprite, int grpNo, BOOL dispF);
HuVec2f *MdSpriteGrpPosGet(MDSPRITE_WORK *sprite, int grpNo);
HuVec2f *MdSpriteGrpScaleGet(MDSPRITE_WORK *sprite, int grpNo);


void MdModelCreate(MDMODEL_WORK *model, MDCAMERA_WORK *camera);
void MdToueiTexBufInit(void);
void MdTexBufObjPosSet(MDTEXBUF_UNIT *unit, HU3DMODELID modelId, char *objName, u16 cameraBit, HuVecF *ofsP);
void MdTexBufPosSet(MDTEXBUF_UNIT *unit, HuVecF *posP, u16 cameraBit);

void MdToueiMdlInit(void); /* mdmini/mdstory stage.o names: mdparty MdModelAnimInit, MdTexBufInit, MdTexBufLayerHook, MdSpriteGrpDispSet, MdRingBaseMdlSet, MdRingBaseOfsSet */

void MdRingCreate(void);
void MdRingMain(void);
void MdRingDispSet(int no, BOOL dispF);
void MdRingOfsSet(int no, float x, float y, float z);
void MdRingModeSet(int no, int mode);
void MdRingMdlSet(int no, int mdlNo);
void MdRingColorReset(int no);
//void MdRingScaleSet(int no, float scale);

void MdToueiLayerHook(s16 layerNo);

/* mdstory.c prototypes (reference names; see mdstory.c for each function's twin) */
/* --- mdstory.c --- */
void ObjectSetup(void);
void MdMain(void);
void fn_1_C24(void);
void fn_1_1728(void);
void fn_1_1A40(void);
void fn_1_1E3C(void);
void fn_1_1E54(void);
void fn_1_1E98(void);
void MdInit(void);
void MdClose(void);
void fn_1_2204(void);
void fn_1_24FC(void);
void fn_1_2D88(void);
void fn_1_3438(void);
void fn_1_3C2C(void);
BOOL fn_1_46E4(int param);
BOOL fn_1_48EC(int param);
BOOL fn_1_4A98(int param);
BOOL fn_1_53D4(int param);
BOOL fn_1_5B08(int param);
BOOL fn_1_709C(int param);
BOOL fn_1_766C(int param);
BOOL fn_1_7FB4(int param);
BOOL fn_1_81F8(int param);
BOOL fn_1_8388(int param);
void fn_1_8610(void);
void fn_1_872C(void);
void fn_1_87F4(void);
BOOL fn_1_8948(int playerNo);
void fn_1_8B94(int mdlNo, int cameraNo);
void fn_1_8C84(void);
void fn_1_9384(int cmd);
int fn_1_9524(int mdlNo, int cameraNo);
void MdPosAdjustMode(void);

#endif
