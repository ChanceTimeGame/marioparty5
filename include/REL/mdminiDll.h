#ifndef _MDMINIDLL_H
#define _MDMINIDLL_H

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

#define MDMINI_TEXBUF_MIRROR 0
#define MDMINI_TEXBUF_MAX 10

#define MDMINI_TEXBUF_W 64
#define MDMINI_TEXBUF_H 64

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

typedef void (*MD_FUNC)(void);
typedef BOOL (*MD_PROC)(int param);


/* MdFlowTbl (.data 0x358, 7 entries). Names past INIT are guesses from the twin / fields used. */
enum {
    MDMINI_FLOW_INIT, //0 fn_1_23D8 (twin MdPartyFlowInit)
    MDMINI_FLOW_PLAYER_NUM_SEL, //1 fn_1_27F8 (uses playerNum/prevPlayerNum/maxPlayerNum; guess)
    MDMINI_FLOW_CHR_SEL, //2 fn_1_35A0 (twin MdPartyFlowChrSel)
    MDMINI_FLOW_MODE_SEL, //3 fn_1_5558 (reads the submode table; guess)
    MDMINI_FLOW_UNK4, //4 fn_1_6FB8
    MDMINI_FLOW_UNK5, //5 fn_1_7638
    MDMINI_FLOW_UNK6, //6 fn_1_81E0
    MDMINI_FLOW_MAX //7
};

/* MdProcTbl (.data 0x374, 15 entries). UNKn: no reliable mdparty/mdsel twin. */
enum {
    MDMINI_PROC_RESET, //0 fn_1_9714
    MDMINI_PROC_CAMERA, //1 fn_1_991C
    MDMINI_PROC_CURSOR, //2 fn_1_9AC8
    MDMINI_PROC_WIN, //3 fn_1_AF34
    MDMINI_PROC_CAP_PLAYER, //4 fn_1_B668
    MDMINI_PROC_CHR, //5 fn_1_C8B4
    MDMINI_PROC_UNK6, //6 fn_1_E44C
    MDMINI_PROC_UNK7, //7 fn_1_F6C4
    MDMINI_PROC_UNK8, //8 fn_1_FC94
    MDMINI_PROC_UNK9, //9 fn_1_10264
    MDMINI_PROC_UNK10, //10 fn_1_106D4
    MDMINI_PROC_UNK11, //11 fn_1_10B0C
    MDMINI_PROC_FINGER, //12 fn_1_113D8
    MDMINI_PROC_UNK13, //13 fn_1_11658
    MDMINI_PROC_NAME, //14 fn_1_149A4
    MDMINI_PROC_MAX //15
};

/* fn_1_17008 (mdparty MdPartyAudExec) commands, from its 24-entry jump table. #defines, not an
 * enum: an anonymous enum advances CW's static-name counter. 10 has no case (mdparty's unused
 * BOARD_ENTER2); 11/12 both play MSM_SE_GUIDE_56 in retail. */
#define MDMINI_AUD_MUS_START 0
#define MDMINI_AUD_MUS_STOP 1
#define MDMINI_AUD_SE_CMN_MOVE 2 /* MSM_SE_CMN_01 */
#define MDMINI_AUD_SE_CMN_CONFIRM 3 /* MSM_SE_CMN_03 */
#define MDMINI_AUD_SE_CMN_CHRSEL 4 /* MSM_SE_CMN_02 */
#define MDMINI_AUD_SE_CMN_CANCEL 5 /* MSM_SE_CMN_04 */
#define MDMINI_AUD_SE_CMN_05 6 /* MSM_SE_CMN_05 (not in mdparty) */
#define MDMINI_AUD_SE_MENU_MOVE 7 /* MSM_SE_MENU_27 */
#define MDMINI_AUD_SE_MENU_28 8 /* MSM_SE_MENU_28 (mdparty BOARD_START) */
#define MDMINI_AUD_SE_MENU_29 9 /* MSM_SE_MENU_29, handle kept (mdparty BOARD_ENTER1) */
#define MDMINI_AUD_UNUSED10 10
#define MDMINI_AUD_SE_STAR_ENTER 11
#define MDMINI_AUD_SE_STAR_CONFIRM 12
#define MDMINI_AUD_SE_CHR_MARIO 13
#define MDMINI_AUD_SE_CHR_LUIGI 14
#define MDMINI_AUD_SE_CHR_PEACH 15
#define MDMINI_AUD_SE_CHR_YOSHI 16
#define MDMINI_AUD_SE_CHR_WARIO 17
#define MDMINI_AUD_SE_CHR_DAISY 18
#define MDMINI_AUD_SE_CHR_WALUIGI 19
#define MDMINI_AUD_SE_CHR_KINOPIO 20
#define MDMINI_AUD_SE_CHR_TERESA 21
#define MDMINI_AUD_SE_CHR_MINIKOOPA 22
#define MDMINI_AUD_SE_ALL_STOP 23

/* stage.s SpriteAnimFile (12 files, mdmini dir 0x90) / SpriteInfo (22) / SpriteGrpInfo (6):
 * MDSPRITE_WORK is 0x68 (ObjectSetup mallocs 104). */
enum {
    MDSPR_ANIM_WIN_FRAME, //0
    MDSPR_ANIM_WIN_BG, //1
    MDSPR_ANIM_CURSOR, //2
    MDSPR_ANIM_CURSOR_GLOW, //3
    MDSPR_ANIM_PLAYERNO, //4
    MDSPR_ANIM_COMDIF, //5
    MDSPR_ANIM_PLAYERNO_FINGER, //6
    MDSPR_ANIM_UNK7, //7 (file 0x36; no SpriteInfo user)
    MDSPR_ANIM_UNK8, //8 (file 0x3C; no SpriteInfo user)
    MDSPR_ANIM_EFFECT_DOT, //9 (fn_1_11658 reads animP[9]/[10] like mdparty's effect code)
    MDSPR_ANIM_EFFECT_GLOW, //10
    MDSPR_ANIM_MODE_NAME, //11
    MDSPR_ANIM_MAX //12
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
    MDSPR_MODE_NAME, //21
    MDSPR_MAX //22
};

enum {
    MDSPR_GRP_WIN, //0
    MDSPR_GRP_CURSOR_LR, //1
    MDSPR_GRP_CURSOR_UDLR, //2
    MDSPR_GRP_PLAYERNO, //3
    MDSPR_GRP_COMDIF, //4
    MDSPR_GRP_NAME, //5
    MDSPR_GRP_MAX //6
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
    MDSPR_GRP_NAME_START = MDSPR_MODE_NAME,
    MDSPR_GRP_NAME_END = MDSPR_MODE_NAME,
};

enum {
    MDMINI_OBJ_DEBUGFONT, // 0
    MDMINI_OBJ_PAD, //1
    MDMINI_OBJ_CAMERA, //2
    MDMINI_OBJ_LIGHT, //3
    MDMINI_OBJ_MAX //4
};

/* MdPosAdjustMode mdlInfo$1113 (.data 0xC98, 49 names): MDMODEL_WORK is 0x2E8 (ObjectSetup mallocs 744). */
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
    MDMODEL_KINOPIO, //10
    MDMODEL_TERESA, //11
    MDMODEL_MINIKOOPA, //12
    MDMODEL_CAP_MAN_1P, //13
    MDMODEL_CAP_MAN_2P, //14
    MDMODEL_CAP_MAN_3P, //15
    MDMODEL_CAP_MAN_4P, //16
    MDMODEL_CAP_COM_1P, //17
    MDMODEL_CAP_COM_2P, //18
    MDMODEL_CAP_COM_3P, //19
    MDMODEL_CAP_COM_4P, //20
    MDMODEL_CAP_CHR_00, //21
    MDMODEL_CAP_CHR_01, //22
    MDMODEL_CAP_CHR_02, //23
    MDMODEL_CAP_CHR_03, //24
    MDMODEL_CAP_CHR_04, //25
    MDMODEL_CAP_CHR_05, //26
    MDMODEL_CAP_CHR_06, //27
    MDMODEL_CAP_CHR_07, //28
    MDMODEL_CAP_CHR_08, //29
    MDMODEL_CAP_CHR_09, //30
    MDMODEL_CAP_MODE_00, //31
    MDMODEL_CAP_MODE_01, //32
    MDMODEL_CAP_MODE_02, //33
    MDMODEL_CAP_MODE_03, //34
    MDMODEL_CAP_MODE_04, //35
    MDMODEL_CAP_MODE_05, //36
    MDMODEL_CAP_WIN, //37
    MDMODEL_CAP_GENRE, //38
    MDMODEL_FINGER_1P, //39
    MDMODEL_FINGER_2P, //40
    MDMODEL_FINGER_3P, //41
    MDMODEL_FINGER_4P, //42
    MDMODEL_RING_1P, //43
    MDMODEL_RING_2P, //44
    MDMODEL_RING_3P, //45
    MDMODEL_RING_4P, //46
    MDMODEL_VS, //47
    MDMODEL_FONTBGFILTER, //48
    MDMODEL_MAX //49
};

enum {
    MDMODEL_ANIM_FINGER_1P, //0
    MDMODEL_ANIM_FINGER_2P, //1
    MDMODEL_ANIM_FINGER_3P, //2
    MDMODEL_ANIM_FINGER_4P, //3
    
    MDMODEL_ANIM_CAP_TURN, //4 (mdparty name; mdmini's anim 4/5 targets unverified)
    MDMODEL_ANIM_CAP_BONUS, //5
    
    MDMODEL_ANIM_MAX //6
};

enum {
    MDMODEL_MOT_STAR_IDLE, //0
    MDMODEL_MOT_STAR_TALK, //1
    MDMODEL_MOT_STAR_TALK_FAST, //2
    
    MDMODEL_MOT_MARIO_IDLE,//3
    MDMODEL_MOT_MARIO_WIN, //4
    
    MDMODEL_MOT_LUIGI_IDLE, //5
    MDMODEL_MOT_LUIGI_WIN, //6
    
    MDMODEL_MOT_PEACH_IDLE, //7
    MDMODEL_MOT_PEACH_WIN, //8
    
    MDMODEL_MOT_YOSHI_IDLE, //9
    MDMODEL_MOT_YOSHI_WIN, //10
    
    MDMODEL_MOT_WARIO_IDLE, //11
    MDMODEL_MOT_WARIO_WIN, //12
    
    MDMODEL_MOT_DAISY_IDLE, //13
    MDMODEL_MOT_DAISY_WIN, //14
    
    MDMODEL_MOT_WALUIGI_IDLE, //15
    MDMODEL_MOT_WALUIGI_WIN, //16
    
    MDMODEL_MOT_KINOPIO_IDLE, //17
    MDMODEL_MOT_KINOPIO_WIN, //18
    
    MDMODEL_MOT_TERESA_IDLE, //19
    MDMODEL_MOT_TERESA_WIN, //20
    
    MDMODEL_MOT_MINIKOOPA_IDLE, //21
    MDMODEL_MOT_MINIKOOPA_WIN, //22
    
    MDMODEL_MOT_MAX //23
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
    MDTEXBUF_UNIT unit[MDMINI_TEXBUF_MAX]; //0x00
    int unk1E0;
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
    MDRING ring[4]; //0x00
    float scale; //0x110
} MDRING_WORK;

/* mdmini.c state values (fork A; mdparty.c keeps its twins' values in mdparty.c) */
#define MDMINI_STAR_NONE 0
#define MDMINI_STAR_BACK_START 1
#define MDMINI_STAR_BACK 2
#define MDMINI_STAR_BACK_END 3
#define MDMINI_STAR_DECENTER_START 4
#define MDMINI_STAR_DECENTER 5
#define MDMINI_STAR_DECENTER_END 6
#define MDMINI_STAR_MOVE_LEFT_START 7
#define MDMINI_STAR_MOVE_LEFT 8
#define MDMINI_STAR_MOVE_LEFT_END 9
#define MDMINI_STAR_SNAP_LEFT 10
#define MDMINI_STAR_CENTER_START 11
#define MDMINI_STAR_CENTER 12
#define MDMINI_STAR_CENTER_END 13

#define MDMINI_STAR_MOT_NONE 0
#define MDMINI_STAR_MOT_RESET 1
#define MDMINI_STAR_MOT_TALK 2
#define MDMINI_STAR_MOT_IDLE 3

#define MDMINI_PLAYERSPR_NONE 0
#define MDMINI_PLAYERSPR_GROW_START 1
#define MDMINI_PLAYERSPR_GROW 2
#define MDMINI_PLAYERSPR_GROW_END 3
#define MDMINI_PLAYERSPR_SHRINK_START 4
#define MDMINI_PLAYERSPR_SHRINK 5
#define MDMINI_PLAYERSPR_SHRINK_END 6

#define MDMINI_CHR_NONE 0
#define MDMINI_CHR_INIT 1
#define MDMINI_CHR_SELECT 2
#define MDMINI_CHR_SELECT_WAIT 3
#define MDMINI_CHR_SELECT_MOVE 4
#define MDMINI_CHR_SELECT_MOVE_WAIT 5

typedef struct MdMiniPlayerSpr_s {
    int mode; //0x00
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
} MDMINI_PLAYERSPR;

typedef struct MdMiniChar_s {
    int mode; //0x04
    float time; //0x04
    float ofsTime; //0x08
    float t; //0x0C
    float ofsT; //0x10
    HuVecF origPos; //0x14
    HuVecF pos; //0x20
    HuVecF origRot; //0x2C
    HuVecF rot; //0x38
} MDMINI_CHR;

typedef struct MdMiniStar_s {
    s16 unk0;
    s16 mode; //0x02
    s16 motNext; //0x04
} MDMINI_STAR;

/* SYS for mdmini, measured from every sys->/sysP-> access in mdmini.s/object.s/stage.s:
 * 0x4A4 bytes on GC (mdparty's is 0x4AC). Names are mdparty's where the twin function
 * uses the same field; unkXXX where mdmini has no mdparty counterpart. */
typedef struct Sys_s {
    int subMode; //0x00
    int unk4; //0x04
    int flowTime; //0x08
    int flowMode; //0x0C
    int ovlCallMode; //0x10
    OMOVL nextDll; //0x14
    s8 exitF; //0x18
    s8 skipWipeF; //0x19
    s8 playerNum; //0x1A (mdparty has gameType at 0x1A; mdmini does not)
    s8 prevPlayerNum; //0x1B
    s8 maxPlayerNum; //0x1C
    s8 padConnect[4]; //0x1D
    s8 padEnable[4]; //0x21
    s8 padNoConnect[4]; //0x25
    s8 padNoEnable[4]; //0x29
    s8 chrSel[4]; //0x2D
    s8 chrSelEnd[4]; //0x31
    s8 comDif[4]; //0x35
    s8 comPlayerNo[3]; //0x39
    s8 selComNo; //0x3C
    s8 unk3D; //0x3D selected submode: indexes lbl_1_data_148 / lbl_1_data_160
    s8 unk3E; //0x3E previous submode (fn_1_5558, fn_1_E44C)
    s8 unk3F[6]; //0x3F per-submode enable flags, written by fn_1_16358
    s8 unk45; //0x45 -> mgMatchMaxScore in fn_1_16978
    s8 unk46; //0x46 -> mgMatchGameType in fn_1_16978
    s8 teamOrderNo; //0x47
    s8 teamPlayer[2][2]; //0x48
    s8 teamOrder[4]; //0x4C
    s8 teamOrderBackup[4]; //0x50
    s8 teamNo[2]; //0x54
    s8 teamComPlayerNo[3]; //0x56
    s8 unk59; //0x59 second team-order selector (fn_1_161B8)
    s8 unk5A[4]; //0x5A order, from lbl_1_data_A2A[unk59]
    s8 unk5E[4]; //0x5E backup of unk5A (fn_1_16308)
    s8 unk62[3]; //0x62 com player list, from lbl_1_data_A1A[unk59]
    OMOBJMAN *objman; //0x68
    HUPROCESS *mainProc; //0x6C
    HUPROCESS *loadProc; //0x70
    HUPROCESS *starProc; //0x74
    HUPROCESS *playerSprProc; //0x78
    HUPROCESS *chrProc; //0x7C
    HUPROCESS *ringProc; //0x80
    HUPROCESS *mainWinProc; //0x84
    HUPROCESS *textWinProc; //0x88
    OMOBJ *obj[MDMINI_OBJ_MAX]; //0x8C
    OMOVLHIS *ovlHis; //0x9C
    s32 evtNo; //0xA0
    s16 loadState; //0xA4
    s16 loadAsyncStat; //0xA6
    unsigned int loadDir; //0xA8 (no loadProcReady after it, unlike mdparty)
    MDDEBUGFONT_WORK *debugFont; //0xAC
    MDPAD_WORK *pad; //0xB0
    MDCAMERA_WORK *camera; //0xB4
    MDLIGHT_WORK *light; //0xB8
    MDSPRITE_WORK *sprite; //0xBC
    MDMODEL_WORK *model; //0xC0
    MDTEXBUF_WORK *texbuf; //0xC4
    MDMINI_STAR *star; //0xC8
    MDMINI_PLAYERSPR playerSpr[4]; //0xCC
    MDMINI_CHR chr[10]; //0x11C
    MDMESS_WORK *mess; //0x3C4
    MDRING_WORK *ring; //0x3C8
    BOOL dirtyF; //0x3CC
    BOOL cursorInitF; //0x3D0 (fn_1_9AC8, the cursor proc)
    BOOL winInitF; //0x3D4 (fn_1_AF34)
    BOOL unk3D8; //0x3D8 (fn_1_10264)
    BOOL nameInitF; //0x3DC (fn_1_149A4)
    BOOL unk3E0; //0x3E0 (only cleared, fn_1_9714)
    int cursorDir; //0x3E4
    int unk3E8; //0x3E8 (never accessed)
    float procTime; //0x3EC
    float procOfsTime; //0x3F0
    float cameraTime; //0x3F4
    float cameraTotalTime; //0x3F8
    float sprTime; //0x3FC
    float unk400; //0x400 (fn_1_10264)
    float nameTime; //0x404
    float procT; //0x408
    float procOfsT; //0x40C
    float cameraT; //0x410
    float cameraTotalT; //0x414
    float sprT; //0x418
    float unk41C; //0x41C (fn_1_10264)
    float nameT; //0x420
    float curveTime[8]; //0x424
    float curveSlope[24]; //0x444
} SYS;

#ifdef __MWERKS__
/* GameCube layout proof: sysWork's .bss size and ObjectSetup's HuMemDirectMallocNum sizes. */
typedef char MdMiniSysSizeCheck[sizeof(SYS) == 0x4A4 ? 1 : -1];
typedef char MdMiniSpriteSizeCheck[sizeof(MDSPRITE_WORK) == 0x68 ? 1 : -1];
typedef char MdMiniModelSizeCheck[sizeof(MDMODEL_WORK) == 0x2E8 ? 1 : -1];
typedef char MdMiniMessSizeCheck[sizeof(MDMESS_WORK) == 0x18 ? 1 : -1];
typedef char MdMiniStarSizeCheck[sizeof(MDMINI_STAR) == 0x6 ? 1 : -1];
#endif

extern SYS *sys;
extern SYS *sysP;
extern SYS sysWork;
extern MD_FUNC MdFlowTbl[MDMINI_FLOW_MAX];
extern MD_PROC MdProcTbl[MDMINI_PROC_MAX];

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

void MdToueiMdlInit(void); /* mdmini stage.o names: mdparty MdModelAnimInit, MdTexBufInit, MdTexBufLayerHook, MdSpriteGrpDispSet, MdRingBaseMdlSet, MdRingBaseOfsSet */

void MdRingCreate(void);
void MdRingMain(void);
void MdRingDispSet(int no, BOOL dispF);
void MdRingOfsSet(int no, float x, float y, float z);
void MdRingModeSet(int no, int mode);
void MdRingMdlSet(int no, int mdlNo);
void MdRingColorReset(int no);
//void MdRingScaleSet(int no, float scale);

void MdToueiLayerHook(s16 layerNo);

/* mdmini.c prototypes (reference names; see mdmini.c for each function's twin) */
/* --- mdmini.c --- */
void ObjectSetup(void);
void MdMain(void);
void fn_1_8CC(void);
void fn_1_C4C(void);
void fn_1_1804(void);
void fn_1_1C04(void);
void fn_1_2000(void);
void fn_1_2018(void);
void fn_1_205C(void);
void fn_1_20A0(void);
void fn_1_22C8(void);
void fn_1_23D8(void);
void fn_1_27F8(void);
void fn_1_35A0(void);
void fn_1_5558(void);
void fn_1_6FB8(void);
void fn_1_7638(void);
void fn_1_81E0(void);
BOOL fn_1_9714(int param);
BOOL fn_1_991C(int param);
BOOL fn_1_9AC8(int param);
BOOL fn_1_AF34(int param);
BOOL fn_1_B668(int param);
BOOL fn_1_C8B4(int param);
BOOL fn_1_E44C(int param);
BOOL fn_1_F6C4(int param);
BOOL fn_1_FC94(int param);
BOOL fn_1_10264(int param);
BOOL fn_1_106D4(int param);
BOOL fn_1_10B0C(int param);
BOOL fn_1_113D8(int param);
BOOL fn_1_11658(int param);
BOOL fn_1_149A4(int param);
void fn_1_14C2C(void);
void fn_1_14E24(void);
void fn_1_14FD0(void);
void fn_1_152D4(void);
void fn_1_153D0(void);
BOOL fn_1_15590(int playerNo, BOOL comSelF);
void fn_1_15BF4(void);
void fn_1_15CF8(int mdlNo, int cameraNo);
void fn_1_15DE8(void);
void fn_1_16168(void);
void fn_1_161B8(void);
void fn_1_16308(void);
void fn_1_16358(void);
void fn_1_16978(void);
void fn_1_17008(int cmd);
int fn_1_171B4(int mdlNo, int cameraNo);
void MdPosAdjustMode(void);

#endif