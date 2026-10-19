#ifndef REL_MDBEACHDLL_H
#define REL_MDBEACHDLL_H

/*
 * mdbeachdll (Bonus Mode game host: Beach Volley / Ice Hockey): types, cross-unit globals and
 * prototypes shared by its units (mdbeach, object, stage).
 *
 * Types are the mdmini/mdparty/mdomake twins' (same names and layouts where the reference shows
 * the same layout). SYS and the work sizes are measured from mdbeach.s (every sys-> access, and
 * ObjectSetup's HuMemDirectMallocNum sizes); offsets are GameCube ones. Fields without a certain
 * meaning are named by offset.
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
/* host only: retail calls Hu3D2Dto3D/Hu3D3Dto2D unprototyped (the u16 camera bit goes unextended,
 * fn_1_15BC8); the host gets hsfex.h's prototypes */
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

#define MDMESS_WIN_SPEAKER 0
#define MDMESS_WIN_NOSPEAKER 1
#define MDMESS_WIN_LIST_END -1

#define MDMATH_CURVE_SAMPLE_MAX 8

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

/* two cameras: MDCAMERA_WORK is 0x11C (ObjectSetup mallocs 284) */
enum {
    MDCAMERA_BG, //0 (HU3D_CAM0)
    MDCAMERA_MAIN, //1 (HU3D_CAM1)
    MDCAMERA_MAX //2
};

enum {
    MDCAMERA_FOCUS_TARGET, // 0
    MDCAMERA_FOCUS_POS, //1
    MDCAMERA_FOCUS_MAX //2
};

/* five windows: MDMESS_WORK is 0x3C (ObjectSetup mallocs 60) */
enum {
    MDMESS_WIN_MAIN, //0
    MDMESS_WIN_HELP, //1
    MDMESS_WIN_2, //2
    MDMESS_WIN_3, //3
    MDMESS_WIN_4, //4
    MDMESS_WIN_MAX //5
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

/* MdFlowTbl (.data 0x590, 6 entries); twins from TWINS.txt */
enum {
    MDBEACH_FLOW_INIT, //0 fn_1_2D3C (mdmini fn_1_23D8)
    MDBEACH_FLOW_START, //1 fn_1_31A8 (mdparty MdPartyFlowStart)
    MDBEACH_FLOW_CHR_SEL, //2 fn_1_4138 (mdparty MdPartyFlowChrSel)
    MDBEACH_FLOW_TEAM_SEL, //3 fn_1_57A8 (mdparty MdPartyFlowTeamSel)
    MDBEACH_FLOW_BONUS_SEL, //4 fn_1_6E9C (mdparty MdPartyFlowBonusSel)
    MDBEACH_FLOW_HANDICAP, //5 fn_1_79EC (mdparty MdPartyFlowHandicap)
    MDBEACH_FLOW_MAX //6
};

/* MdProcTbl (.data 0x5A8, 13 entries) */
enum {
    MDBEACH_PROC_RESET, //0 fn_1_9A14
    MDBEACH_PROC_CAMERA, //1 fn_1_9BAC (mdmini fn_1_991C)
    MDBEACH_PROC_CURSOR, //2 fn_1_9D58 (mdmini fn_1_9AC8)
    MDBEACH_PROC_WIN, //3 fn_1_B1E8 (mdmini fn_1_AF34)
    MDBEACH_PROC_CAP_PLAYER, //4 fn_1_B91C (mdparty MdPartyProcCapPlayer)
    MDBEACH_PROC_UNK5, //5 fn_1_D45C
    MDBEACH_PROC_MAP_ENTER, //6 fn_1_EC34 (mdparty MdPartyProcMapEnter)
    MDBEACH_PROC_UNK7, //7 fn_1_118D0
    MDBEACH_PROC_UNK8, //8 fn_1_12314
    MDBEACH_PROC_UNK9, //9 fn_1_12894
    MDBEACH_PROC_UNK10, //10 fn_1_12E6C
    MDBEACH_PROC_FINGER, //11 fn_1_13A2C (mdmini fn_1_113D8)
    MDBEACH_PROC_NAME, //12 fn_1_13850 (mdmini fn_1_149A4)
    MDBEACH_PROC_MAX //13
};

/* fn_1_15A40 commands, from its 30-entry jump table. #defines, not an enum: an anonymous enum
 * advances CW's static-name counter. */
#define MDBEACH_AUD_MUS_START 0 /* MSM_STREAM_MGDECA (37), handle in lbl_1_bss_28 */
#define MDBEACH_AUD_MUS_STOP 1
#define MDBEACH_AUD_SE_CMN_MOVE 2 /* MSM_SE_CMN_01 */
#define MDBEACH_AUD_SE_CMN_CONFIRM 3 /* MSM_SE_CMN_03 */
#define MDBEACH_AUD_SE_CMN_CHRSEL 4 /* MSM_SE_CMN_02 */
#define MDBEACH_AUD_SE_CMN_CANCEL 5 /* MSM_SE_CMN_04 */
#define MDBEACH_AUD_SE_MENU_MOVE 6 /* MSM_SE_MENU_27 */
#define MDBEACH_AUD_SE_CHR_SEL 7 /* 7..16: MSM_SE_MENU_28 panned on model cmd-6 (MDMODEL_MARIO..MINIKOOPA) */
#define MDBEACH_AUD_SE_MENU_29 17 /* MSM_SE_MENU_29 */
#define MDBEACH_AUD_SE_CHR_VOICE 18 /* 18..27: lbl_1_data_9D8[cmd-18] panned on model cmd-17 */
#define MDBEACH_AUD_SE_STAR 28 /* MSM_SE_GUIDE_53 panned on the star (camera 1) */
#define MDBEACH_AUD_SE_ALL_STOP 29

/* fn_1_9BAC (mdmini fn_1_991C / mdparty ProcCamera lerpData): lbl_1_data_7B0 */
typedef struct MdBeachLerpData_s {
    HuVecF hvrA;
    HuVecF centerA;
    HuVecF hvrB;
    HuVecF centerB;
    int type;
    float step;
} MDBEACH_LERP_DATA;

/* stage.s SpriteAnimFile (18 files, mdbeach dir 0x8E) / SpriteInfo (30) / SpriteGrpInfo (9):
 * MDSPRITE_WORK is 0x98 (ObjectSetup mallocs 152). Names past COMDIF are by index. */
enum {
    MDSPR_ANIM_WIN_FRAME, //0 (file 76)
    MDSPR_ANIM_WIN_BG, //1 (77)
    MDSPR_ANIM_CURSOR, //2 (74)
    MDSPR_ANIM_CURSOR_GLOW, //3 (75)
    MDSPR_ANIM_PLAYERNO, //4 (89)
    MDSPR_ANIM_COMDIF, //5 (90)
    MDSPR_ANIM_FINGER, //6 (91; MdToueiMdlInit -> FINGER models)
    MDSPR_ANIM_7, //7 (78)
    MDSPR_ANIM_8, //8 (79)
    MDSPR_ANIM_9, //9 (80)
    MDSPR_ANIM_10, //10 (81)
    MDSPR_ANIM_11, //11 (82)
    MDSPR_ANIM_12, //12 (87)
    MDSPR_ANIM_13, //13 (88)
    MDSPR_ANIM_14, //14 (83)
    MDSPR_ANIM_15, //15 (84)
    MDSPR_ANIM_16, //16 (85)
    MDSPR_ANIM_17, //17 (86)
    MDSPR_ANIM_MAX //18
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
    MDSPR_PLAYERNO_2P, //14
    MDSPR_PLAYERNO_3P, //15
    MDSPR_PLAYERNO_4P, //16
    MDSPR_COMDIF_1P, //17
    MDSPR_COMDIF_2P, //18
    MDSPR_COMDIF_3P, //19
    MDSPR_COMDIF_4P, //20
    MDSPR_21, //21 (anim 9) group 5
    MDSPR_22, //22 (anim 10) group 5
    MDSPR_23, //23 (anim 11) group 5
    MDSPR_24, //24 (anim 12) group 6
    MDSPR_25, //25 (anim 13) group 6
    MDSPR_26, //26 (anim 14) group 7
    MDSPR_27, //27 (anim 16) group 7
    MDSPR_28, //28 (anim 15) group 8
    MDSPR_29, //29 (anim 17) group 8
    MDSPR_MAX //30
};

enum {
    MDSPR_GRP_WIN, //0
    MDSPR_GRP_CURSOR_LR, //1
    MDSPR_GRP_CURSOR_UDLR, //2
    MDSPR_GRP_PLAYERNO, //3
    MDSPR_GRP_COMDIF, //4
    MDSPR_GRP_5, //5
    MDSPR_GRP_6, //6
    MDSPR_GRP_7, //7
    MDSPR_GRP_8, //8
    MDSPR_GRP_MAX //9
};

enum {
    MDSPR_GRP_WIN_START = MDSPR_WIN_FRAME_TOP,
    MDSPR_GRP_WIN_END = MDSPR_WIN_BG,
    MDSPR_GRP_CURSOR_LR_START = MDSPR_CURSOR_LR_R,
    MDSPR_GRP_CURSOR_LR_END = MDSPR_CURSOR_LR_L,
    MDSPR_GRP_CURSOR_UDLR_START = MDSPR_CURSOR_UDLR_R,
    MDSPR_GRP_CURSOR_UDLR_END = MDSPR_CURSOR_GLOW_UDLR_D,
    MDSPR_GRP_PLAYERNO_START = MDSPR_PLAYERNO_1P,
    MDSPR_GRP_PLAYERNO_END = MDSPR_PLAYERNO_4P,
    MDSPR_GRP_COMDIF_START = MDSPR_COMDIF_1P,
    MDSPR_GRP_COMDIF_END = MDSPR_COMDIF_4P,
    MDSPR_GRP_5_START = MDSPR_21,
    MDSPR_GRP_5_END = MDSPR_23,
    MDSPR_GRP_6_START = MDSPR_24,
    MDSPR_GRP_6_END = MDSPR_25,
    MDSPR_GRP_7_START = MDSPR_26,
    MDSPR_GRP_7_END = MDSPR_27,
    MDSPR_GRP_8_START = MDSPR_28,
    MDSPR_GRP_8_END = MDSPR_29
};

enum {
    MDBEACH_OBJ_DEBUGFONT, // 0
    MDBEACH_OBJ_PAD, //1
    MDBEACH_OBJ_CAMERA, //2
    MDBEACH_OBJ_LIGHT, //3
    MDBEACH_OBJ_MAX //4
};

/* MdPosAdjustMode mdlInfo$1113 (.data 0xCC0, 53 names): MDMODEL_WORK is 0x330 (ObjectSetup mallocs 816). */
enum {
    MDMODEL_STAR, //0
    MDMODEL_MARIO, //1 (CharMdlTbl, 1..10)
    MDMODEL_LUIGI, //2
    MDMODEL_PEACH, //3
    MDMODEL_YOSHI, //4
    MDMODEL_WARIO, //5
    MDMODEL_DAISY, //6
    MDMODEL_WALUIGI, //7
    MDMODEL_KINOPIO, //8
    MDMODEL_TERESA, //9
    MDMODEL_MINIKOOPA, //10
    MDMODEL_MARIO_VOLLEY, //11 (CharVolleyMdlTbl, 11..20)
    MDMODEL_MARIO_HOCKEY = MDMODEL_MARIO_VOLLEY+10, //21 (CharHockeyMdlTbl, 21..30)
    MDMODEL_CAP_MAN_1P = MDMODEL_MARIO_HOCKEY+10, //31
    MDMODEL_CAP_MAN_2P, //32
    MDMODEL_CAP_MAN_3P, //33
    MDMODEL_CAP_MAN_4P, //34
    MDMODEL_CAP_COM_1P, //35
    MDMODEL_CAP_COM_2P, //36
    MDMODEL_CAP_COM_3P, //37
    MDMODEL_CAP_COM_4P, //38
    MDMODEL_FINGER_1P, //39
    MDMODEL_FINGER_2P, //40
    MDMODEL_FINGER_3P, //41
    MDMODEL_FINGER_4P, //42
    MDMODEL_FLASH_1P, //43
    MDMODEL_FLASH_2P, //44
    MDMODEL_FLASH_3P, //45
    MDMODEL_FLASH_4P, //46
    MDMODEL_VS_VOLLEY, //47
    MDMODEL_VS_HOCKEY, //48
    MDMODEL_BALL_NORMAL, //49
    MDMODEL_BALL_BOMB, //50
    MDMODEL_BALL_DICE, //51
    MDMODEL_FONTBGFILTER, //52
    MDMODEL_MAX //53
};

#define MDMODEL_CHR_NUM 10

enum {
    MDMODEL_ANIM_FINGER_1P, //0 (MdToueiMdlInit)
    MDMODEL_ANIM_FINGER_2P, //1
    MDMODEL_ANIM_FINGER_3P, //2
    MDMODEL_ANIM_FINGER_4P, //3
    MDMODEL_ANIM_MAX //4
};

enum {
    MDMODEL_MOT_STAR_IDLE, //0
    MDMODEL_MOT_STAR_TALK, //1
    MDMODEL_MOT_STAR_TALK_FAST, //2
    MDMODEL_MOT_CHR, //3: 3 motions per character (CharMotTbl, 30), on models MDMODEL_MARIO+(i/3)
    MDMODEL_MOT_MAX = MDMODEL_MOT_CHR+30 //33
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
    int selCamera; //0x118
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
    HUSPRID sprId[MDSPR_MAX]; //0x48
    HUSPRGRPID grpId[MDSPR_GRP_MAX]; //0x84
} MDSPRITE_WORK;

typedef struct MdModelDebugInfo_s {
    char *name; //0x00
    int cameraNo; //0x04
} MDMODEL_DEBUG_INFO;

typedef struct MdModelWork_s {
    HU3DMODELID mdlId[MDMODEL_MAX]; //0x00
    HU3DMOTID motId[MDMODEL_MOT_MAX]; //0x6A
    HU3DANIMID animId[MDMODEL_ANIM_MAX]; //0xAC
    HuVecF *posP[MDMODEL_MAX]; //0xB4
    HuVecF *rotP[MDMODEL_MAX]; //0x188
    HuVecF *scaleP[MDMODEL_MAX]; //0x25C
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

/* sys->star (ObjectSetup mallocs 20); only mode (0x2) and motNext (0x4) are accessed */
typedef struct MdBeachStar_s {
    s16 unk0;
    s16 mode; //0x02
    s16 motNext; //0x04
    s16 unk6;
    HuVecF unk8; /* guess: 0x8-0x13 never accessed */
} MDBEACH_STAR;

/* sys->unk204[4] and sys->playerSpr[4] (0x14 each; fn_1_15AC is mdmini fn_1_1804) */
typedef struct MdBeachPlayerSpr_s {
    int mode; //0x00
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
} MDBEACH_PLAYERSPR;

/* sys->chr[10] (0x20 each; fn_1_2554) */
typedef struct MdBeachChr_s {
    int mode; //0x00
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
    float unk14; //0x14
    float unk18; //0x18
    float unk1C; //0x1C
} MDBEACH_CHR;

/* lbl_1_bss_574[4] (fn_1_B91C): per-capsule staggered slide: mode 0 = wait delay frames, 1 = move, 2 = done */
typedef struct MdBeachCapAnim_s {
    s16 mode; //0x00
    s16 delay; //0x02
    float time; //0x04
    float t; //0x08
} MDBEACH_CAP_ANIM;

/* SYS for mdbeach, measured from every sys->/sysP-> access in mdbeach.s/object.s/stage.s:
 * 0x2F8 bytes on GC (sysWork's .bss size). The s8 block is mdparty's from 0x1A to 0x2D, then
 * differs (two extra [4] arrays, chrSelEnd at 0x3A, team block at 0x46). */
typedef struct Sys_s {
    int subMode; //0x00
    int unk4; //0x04
    int flowTime; //0x08
    int flowMode; //0x0C
    int ovlCallMode; //0x10
    OMOVL nextDll; //0x14
    s8 exitF; //0x18
    s8 skipWipeF; //0x19
    s8 gameType; //0x1A 0 Beach Volley (evtNo 0/2), 1 Ice Hockey (evtNo 1/3) (ObjectSetup)
    s8 playerNum; //0x1B (fn_1_13CAC: maxPlayerNum-1)
    s8 prevPlayerNum; //0x1C (mdparty layout; guess)
    s8 maxPlayerNum; //0x1D
    s8 padConnect[4]; //0x1E
    s8 padEnable[4]; //0x22
    s8 padNoConnect[4]; //0x26
    s8 padNoEnable[4]; //0x2A
    s8 chrSel[4]; //0x2E
    s8 unk32[4]; //0x32 (fn_1_4138: a copy of chrSel)
    s8 unk36[4]; //0x36 (fn_1_4138, fn_1_19AC, fn_1_EC34)
    s8 chrSelEnd[4]; //0x3A (fn_1_14F44)
    s8 comDif[4]; //0x3E
    s8 comPlayerNo[3]; //0x42
    s8 selComNo; //0x45
    s8 teamOrderNo; //0x46
    s8 teamPlayer[2][2]; //0x47
    s8 teamOrder[4]; //0x4B
    s8 teamOrderBackup[4]; //0x4F
    s8 teamNo[2]; //0x53
    s8 teamComPlayerNo[3]; //0x55
    s8 unk58; //0x58 (fn_1_6E9C, fn_1_12E6C, fn_1_14354, fn_1_15508, fn_1_79EC)
    s8 unk59; //0x59 (fn_1_6E9C, fn_1_12E6C)
    s8 unk5A; //0x5A (fn_1_14354, fn_1_15508, fn_1_79EC)
    OMOBJMAN *objman; //0x5C
    HUPROCESS *mainProc; //0x60
    HUPROCESS *loadProc; //0x64
    HUPROCESS *starProc; //0x68 fn_1_A30
    HUPROCESS *chrProc; //0x6C fn_1_2554
    HUPROCESS *unk70Proc; //0x70 fn_1_19AC
    HUPROCESS *playerSprProc; //0x74 fn_1_15AC
    HUPROCESS *mainWinProc; //0x78 fn_1_28C8
    HUPROCESS *textWinProc; //0x7C fn_1_290C
    HUPROCESS *unk80Proc; //0x80 fn_1_2968
    OMOBJ *obj[MDBEACH_OBJ_MAX]; //0x84
    OMOVLHIS *ovlHis; //0x94
    s32 evtNo; //0x98
    s16 loadState; //0x9C
    s16 loadAsyncStat; //0x9E
    unsigned int loadDir; //0xA0
    s16 loadProcReady; //0xA4
    MDDEBUGFONT_WORK *debugFont; //0xA8
    MDPAD_WORK *pad; //0xAC
    MDCAMERA_WORK *camera; //0xB0
    MDLIGHT_WORK *light; //0xB4
    MDSPRITE_WORK *sprite; //0xB8
    MDMODEL_WORK *model; //0xBC
    MDBEACH_STAR *star; //0xC0
    MDBEACH_CHR chr[10]; //0xC4
    MDBEACH_PLAYERSPR unk204[4]; //0x204 (fn_1_19AC)
    MDBEACH_PLAYERSPR playerSpr[4]; //0x254 (fn_1_15AC)
    MDMESS_WORK *mess; //0x2A4
    BOOL dirtyF; //0x2A8 (fn_1_13A2C, fn_1_13850, ...; cleared by fn_1_9A14)
    BOOL unk2AC; //0x2AC (fn_1_118D0)
    BOOL unk2B0; //0x2B0 (fn_1_12894)
    BOOL unk2B4; //0x2B4 (fn_1_12314)
    BOOL unk2B8; //0x2B8 (fn_1_9D58)
    BOOL unk2BC; //0x2BC (only cleared, fn_1_9A14)
    int unk2C0; //0x2C0
    int unk2C4; //0x2C4
    int unk2C8; //0x2C8 (never accessed)
    float procTime; //0x2CC
    float procOfsTime; //0x2D0
    float unk2D4; //0x2D4 (only cleared)
    float unk2D8; //0x2D8 (only cleared)
    float unk2DC; //0x2DC (fn_1_9D58, fn_1_12894)
    float procT; //0x2E0
    float procOfsT; //0x2E4
    float unk2E8; //0x2E8 (only cleared)
    float unk2EC; //0x2EC (only cleared)
    float unk2F0; //0x2F0 (fn_1_9D58, fn_1_12894)
    float unk2F4; //0x2F4 (never accessed)
} SYS;

/* fn_1_EC34 lbl_1_bss_E8[4]: one player's jump along lbl_1_bss_198 (0xC each) */
typedef struct MdBeachJump_s {
    s16 mode; //0x00 0 wait, 1 first leg, 2 second leg, 3 done
    s16 delay; //0x02 frames before the jump (frandmod)
    float time; //0x04
    float t; //0x08
} MDBEACH_JUMP;

/* fn_1_EC34 lbl_1_bss_E4: which player waits longest (its jump ends the proc) */
typedef struct MdBeachJumpLast_s {
    s8 playerNo; //0x00
    s8 delay; //0x01
} MDBEACH_JUMP_LAST;

#ifdef __MWERKS__
/* GameCube layout proof: sysWork's .bss size and ObjectSetup's HuMemDirectMallocNum sizes. */
typedef char MdBeachSysSizeCheck[sizeof(SYS) == 0x2F8 ? 1 : -1];
typedef char MdBeachSysMessCheck[(int)&((SYS *)0)->mess == 0x2A4 ? 1 : -1];
typedef char MdBeachSpriteSizeCheck[sizeof(MDSPRITE_WORK) == 0x98 ? 1 : -1];
typedef char MdBeachModelSizeCheck[sizeof(MDMODEL_WORK) == 0x330 ? 1 : -1];
typedef char MdBeachMessSizeCheck[sizeof(MDMESS_WORK) == 0x3C ? 1 : -1];
typedef char MdBeachStarSizeCheck[sizeof(MDBEACH_STAR) == 0x14 ? 1 : -1];
typedef char MdBeachCameraSizeCheck[sizeof(MDCAMERA_WORK) == 0x11C ? 1 : -1];
typedef char MdBeachLightSizeCheck[sizeof(MDLIGHT_WORK) == 0x60 ? 1 : -1];
#endif

extern SYS *sys;
extern SYS *sysP;
extern SYS sysWork;
extern MD_FUNC MdFlowTbl[MDBEACH_FLOW_MAX];
extern MD_PROC MdProcTbl[MDBEACH_PROC_MAX];

/* --- mdbeach.c --- */
void ObjectSetup(void);
void MdMain(void);
void fn_1_A30(void);
void fn_1_15AC(void);
void fn_1_19AC(void);
void fn_1_2554(void);
void fn_1_28C8(void);
void fn_1_290C(void);
void fn_1_2968(void);
void MdInit(void);
void MdClose(void);
void fn_1_2D3C(void);
void fn_1_31A8(void);
void fn_1_4138(void);
void fn_1_57A8(void);
void fn_1_6E9C(void);
void fn_1_79EC(void);
BOOL fn_1_9A14(int param);
BOOL fn_1_9BAC(int param);
BOOL fn_1_9D58(int param);
BOOL fn_1_B1E8(int param);
BOOL fn_1_B91C(int param);
BOOL fn_1_D45C(int param);
BOOL fn_1_EC34(int param);
BOOL fn_1_118D0(int param);
BOOL fn_1_12314(int param);
BOOL fn_1_12894(int param);
BOOL fn_1_12E6C(int param);
BOOL fn_1_13850(int param);
BOOL fn_1_13A2C(int param);
void fn_1_13CAC(void);
void fn_1_13EA4(void);
void fn_1_14050(void);
void fn_1_14354(void);
void fn_1_146D0(void);
BOOL fn_1_14A68(int playerNo, BOOL comSelF);
void fn_1_14F44(void);
void fn_1_15048(void);
void fn_1_153C8(void);
void fn_1_15418(int mdlNo, int cameraNo);
void fn_1_15508(void);
void fn_1_15A40(int cmd);
int fn_1_15BC8(int mdlNo, int cameraNo);
void MdPosAdjustMode(void);
void fn_1_16DE8(void);

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
void MdMessWinScaleSet(MDMESS_WORK *mess, int winNo, float scaleX, float scaleY);
void MdMessWinCenterPosSet(MDMESS_WORK *mess, int winNo, float posX, float posY);
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
