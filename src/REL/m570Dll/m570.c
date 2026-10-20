
#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/mg/timer.h"
#include "game/mg/seqman.h"
#include "game/mg/score.h"
#include "game/flag.h"
#include "game/esprite.h"

#include "datadir_enum.h"

#include "REL/m570Dll/m570.h"

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

/* --- forward declarations --- */

void ObjectSetup(void);
static void M570InitHook(s16 mode, s16 frameNo);
static void M570FadeInHook(s16 mode, s16 frameNo);
static void M570StartHook(s16 mode, s16 frameNo);
static void M570PreMainHook(s16 mode, s16 frameNo);
static void M570MainHook(s16 mode, s16 frameNo);
static void M570FinishHook(s16 mode, s16 frameNo);
static void M570PreWinnerHook(s16 mode, s16 frameNo);
static void M570WinnerHook(s16 mode, s16 frameNo);
static void M570CloseHook(s16 mode, s16 frameNo);
static void M570TimerCreate(void);
static void M570WinnerSet(void);
static void M570ScoreDispOn(void);
static void M570ScoreWinCreate(void);
static void M570ScoreFadeCreate(void);
static void M570ScoreFadeMain(OMOBJ *obj);
static void M570SprPopCreate(int no);
static void M570SprPopMain(OMOBJ *obj);
static void M570ParManMain(OMOBJ *obj);


/* the framework's own declarations arrive with REL/mgframe.h, in m570.h */

/* --- .data --- */

/* the framework's OSReport strings */
#define MGF_S_DATA
#include "REL/mgframe.h"

static MGSEQ_PARAM SeqParam = {
    0, 0,
    M570InitHook,
    M570FadeInHook,
    M570StartHook,
    M570MainHook,
    M570FinishHook,
    M570PreWinnerHook,
    M570WinnerHook,
    NULL,
    M570CloseHook
};

static MGF_STAGELIGHT StageLight = {
    { 0.0f, 300.0f, 0.001f },
    { 0.0f, -300.0f, 0.0f },
    { 255, 255, 255, 255 }
};

static HuVecF ShadowPos = { 0.0f, 1250.0f, 0.0f };   /* .data:0xB0 */
static HuVecF ShadowUp = { 1.0f, 0.0f, 0.0f };       /* .data:0xBC */
static HuVecF ShadowTarget = { 0.0f, 0.0f, 0.0f };   /* .data:0xC8 */

/* .data:0xD4 -- five positions, evenly spaced by 22. */
static float PosTbl[5] = { 244.0f, 266.0f, 288.0f, 310.0f, 332.0f };

/*
 * .data:0xE8..0x298 -- seven views, each the framework's 0x48-byte struct, and
 * each its own symbol rather than an array: the reference addresses them
 * directly, and indexing one array costs an addi the original does not have.
 * Two look at the left of the stage, two at the right, one from behind and two
 * are wide. All are mode 1, so the eye comes from angle and distance about the
 * target.
 */
static MGF_CAMERAVIEW StageViewL = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { -300.0f, 100.0f,   50.0f }, { -15.0f,  90.0f, 0.0f },  500.0f
};

static MGF_CAMERAVIEW StageViewL2 = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { -300.0f, 100.0f,   50.0f }, { -15.0f,   0.0f, 0.0f },  500.0f
};

static MGF_CAMERAVIEW StageViewR = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    {  300.0f, 100.0f,   50.0f }, { -15.0f, -90.0f, 0.0f },  600.0f
};

static MGF_CAMERAVIEW StageViewR2 = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    {  300.0f, 100.0f,   50.0f }, { -15.0f,   0.0f, 0.0f },  600.0f
};

static MGF_CAMERAVIEW StageViewB = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    {    0.0f, 100.0f, -300.0f }, { -10.0f,   0.0f, 0.0f },  400.0f
};

static MGF_CAMERAVIEW StageViewW = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    {    0.0f, 150.0f,    0.0f }, { -15.0f,   0.0f, 0.0f }, 1000.0f
};

static MGF_CAMERAVIEW StageViewW2 = {
    1, 1, 40.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    {    0.0f, 150.0f,    0.0f }, { -15.0f,   0.0f, 0.0f }, 1600.0f
};

/* .data:0x2FC */
static HU3DPARMANPARAM ParManParam = {
    30, 0,
    100.0f,
    15.0f,
    180.0f,
    { 0.0f, 0.0f, 0.0f },
    1.2f,
    0.98f,
    30.0f,
    1.0f,
    1,
    { { 255, 255, 255, 112 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};

/* --- .rodata tables --- */

/* files/data/m570.bin. As with m524dll the archive carries no names, so the
 * raw DATANUM is used rather than an invented datanum/m570.h. */
static int MdlDataTbl[13] = {
    DATANUM(DATA_m570, 0x00), DATANUM(DATA_m570, 0x01), DATANUM(DATA_m570, 0x02),
    DATANUM(DATA_m570, 0x03), DATANUM(DATA_m570, 0x04), DATANUM(DATA_m570, 0x05),
    DATANUM(DATA_m570, 0x06), DATANUM(DATA_m570, 0x07), DATANUM(DATA_m570, 0x08),
    DATANUM(DATA_m570, 0x09), DATANUM(DATA_m570, 0x0A), DATANUM(DATA_m570, 0x18),
    DATANUM(DATA_m570, 0x18)
};

/*
 * Five score panels, each two sprites: the odd-numbered file is the back plate
 * (entered at priority 0x20) and the even-numbered one the face over it (0x10).
 * M570ScoreWinCreate builds both runs in one pass.
 */
static int SprFaceDataTbl[5] = {
    DATANUM(DATA_m570, 0x1A), DATANUM(DATA_m570, 0x1C), DATANUM(DATA_m570, 0x1E),
    DATANUM(DATA_m570, 0x20), DATANUM(DATA_m570, 0x22)
};

static int SprPlateDataTbl[5] = {
    DATANUM(DATA_m570, 0x19), DATANUM(DATA_m570, 0x1B), DATANUM(DATA_m570, 0x1D),
    DATANUM(DATA_m570, 0x1F), DATANUM(DATA_m570, 0x21)
};

/* --- .bss --- */

static s16 SprPlateId[5];               /* bss_2C */
static s16 SprFaceId[5];                /* bss_36 */
static s16 ScoreWinId;                  /* bss_40 */
static int BgmId;                       /* bss_48 -- this overlay's own stream, -1 when idle */
static s16 StateTime;                   /* bss_4C */
static s16 SubStateNo;                  /* bss_4E -- the round number, 0..5 */
static int WinStartF;                   /* bss_0 */
static OMOBJ *CameraMoveObj;            /* bss_4 */
static int StateCount;                  /* bss_8 */
static OMOBJ *CameraMoveObj2;           /* bss_C */
static int SeId;                        /* bss_44 */
static s16 StateNo;                     /* bss_50 */
s16 WinGrp;                      /* bss_52 */
static MGF_CAMERAVIEW CameraWork;      /* bss_54  -- this overlay's own view */
static MGTIMER *Timer;                  /* bss_9C */
static HU3DMODELID StageMdlId[14];      /* bss_A0 -- 13 used */
/* DebugCameraStart (bss_BC), MgMusicId (bss_104) and objman (bss_108) */
#define MGF_S_BSS
#include "REL/mgframe.h"

/* --- the two framework helpers the game code inlines, so defined first --- */
#define MGF_S_CAMERAMOVECHECK
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"

/*
 * ObjectSetup -- the overlay's only export, and complete. The first three
 * statements are MgObjManInit inlined.
 */
void ObjectSetup(void)
{
    MgObjManInit();
    MgSeqCreatePrio(&SeqParam, 2000);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, M570PreMainHook);
    MgSeqModeDelaySet(MGSEQ_MODE_FADEIN, 1500);
}

/*
 * ===========================================================================
 * NOT YET WRITTEN -- the 22 game-specific functions, in asm address order.
 * ===========================================================================
 * Each stub carries the symbol it has to reproduce, its line range in
 * build/mp5-asm/m570Dll/asm/REL/m570Dll/m570.s (regenerate with gen_asm.sh)
 * and the reference instruction count. Fill them in from the top: the nine
 * MGSEQ hooks are the spine of the minigame and the rest hang off them.
 *
 * The `fn_1_4xxx`/`fn_1_5xxx` calls in the reference are into player.c, which
 * is a separate translation unit and entirely unwritten.
 */

/*
 * fn_1_120  asm   97- 357   259 insns  -- MGSEQ_MODE_INIT.
 * Builds the whole stage, then hands off to player.c for the roster.
 */
static void M570InitHook(s16 mode, s16 frameNo)
{
    int i;

    for(i=0; i<13; i++) {
        StageMdlId[i] = Hu3DModelCreateData(MdlDataTbl[i]);
        Hu3DModelAttrSet(StageMdlId[i], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(StageMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(StageMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(StageMdlId[i], 0);
        Hu3DModelAmbSet(StageMdlId[i], 1.0f, 1.0f, 1.0f);
    }
    Hu3DModelPosSet(StageMdlId[4], 0.0f, 0.0f, -270.0f);
    Hu3DModelAttrReset(StageMdlId[10], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(StageMdlId[10], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(StageMdlId[11], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(StageMdlId[12], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(StageMdlId[11], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrReset(StageMdlId[12], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(StageMdlId[11], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(StageMdlId[12], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(StageMdlId[11], -350.0f, 0.0f, 540.0f);
    Hu3DModelPosSet(StageMdlId[12], 350.0f, 0.0f, 540.0f);
    MgCameraCreate(&StageViewL);
    CameraWork = StageViewL;
    MgLightCreate(&StageLight);
    Hu3DShadowCreate(CameraWork.fov, CameraWork.near, CameraWork.far);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&ShadowPos, &ShadowUp, &ShadowTarget);
    Hu3DModelShadowMapSet(StageMdlId[3]);
    M570PlayerCreate();
    StateNo = 0;
    SubStateNo = 0;
    StateTime = 0;
    WinGrp = -1;
    BgmId = -1;
    M570PlayerStageSet();
    M570CrowdCreate();
    M570ScoreWinCreate();
    MgSeqModeNext();
}

/*
 * fn_1_520  asm  360- 728   367 insns  -- MGSEQ_MODE_FADEIN.
 *
 * The opening cinematic, and the largest function in the file: a seven-state
 * jumptable that pans across the solo player, cross-fades to the three
 * chasers introducing themselves one every twenty frames, cuts behind the
 * stage for its set-up animation, then pulls out to the wide view and puts
 * everyone in their ready pose. Anything past state 6 falls through to
 * MgSeqModeNext.
 */
static void M570FadeInHook(s16 mode, s16 frameNo)
{
    OMOBJ *obj;
    int i;

    if(!WipeCheckEnd() && BgmId == -1) {
        BgmId = HuAudSStreamPlay(0x25);
    }
    switch(StateNo) {
        case 0:
            CameraMoveObj2 = MgCameraMoveEntry(&StageViewL, &StageViewL2, 120.0f);
            M570PlayerMotionSet(SoloPlayer, 3);
            StateNo = 1;
            SeId = HuAudFXPlay(0x39C);
            break;

        case 1:
            if(!MgCameraMoveCheck(CameraMoveObj2)) {
                obj = CameraMoveObj2;
                omDelObjEx(objman, obj);
                StateNo = 2;
                StateCount = 0;
            }
            break;

        case 2:
            StateCount++;
            if(StateCount == 29) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 60);
            }
            if(StateCount == 30) {
                CameraMoveObj2 = MgCameraMoveEntry(&StageViewR, &StageViewR2, 120.0f);
                StateNo = 3;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 60);
                StateCount = 0;
            }
            break;

        case 3:
            if(StateCount == 0) {
                M570PlayerMotionSet(ChaserObj[0], 3);
            } else if(StateCount == 20) {
                M570PlayerMotionSet(ChaserObj[1], 3);
            } else if(StateCount == 40) {
                M570PlayerMotionSet(ChaserObj[2], 3);
            }
            StateCount++;
            if(!MgCameraMoveCheck(CameraMoveObj2)) {
                obj = CameraMoveObj2;
                omDelObjEx(objman, obj);
                StateNo = 4;
                StateCount = 0;
            }
            break;

        case 4:
            StateCount++;
            if(StateCount == 29) {
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 60);
            }
            if(StateCount == 30) {
                MgCameraViewSet(&StageViewB);
                StateNo = 5;
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 60);
                M570CrowdIdleSet();
                M570PlayerIntroSet();
                HuAudFXStop(SeId);
                StateCount = 0;
            }
            break;

        case 5:
            if(WipeCheckEnd()) {
                break;
            }
            if(StateCount == 0) {
                Hu3DModelAttrReset(StageMdlId[10], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(StageMdlId[8], HU3D_ATTR_DISPOFF);
                Hu3DModelAttrSet(StageMdlId[9], HU3D_ATTR_DISPOFF);
            }
            if(Hu3DMotionEndCheck(StageMdlId[10])) {
                CameraMoveObj2 = MgCameraMoveEntry(&StageViewB, &StageViewW, 30.0f);
                StateNo = 6;
            }
            StateCount++;
            break;

        case 6:
            if(!MgCameraMoveCheck(CameraMoveObj2)) {
                obj = CameraMoveObj2;
                omDelObjEx(objman, obj);
                StateNo = 8;
                for(i=0; i<4; i++) {
                    M570PlayerMotionSet(PlayerObj[i], 4);
                }
            }
            break;

        default:
            MgSeqModeNext();
            break;
    }
}

/* fn_1_A78  asm  731- 733     1 insn   -- MGSEQ_MODE_START.
 * A single `blr` in the original: an empty hook, not a missing one. */
static void M570StartHook(s16 mode, s16 frameNo)
{
}

/* fn_1_A7C  asm  736- 753    16 insns  -- MGSEQ_MODE_PREMAIN, added by MgSeqModeHookAdd */
static void M570PreMainHook(s16 mode, s16 frameNo)
{
    StateNo = 9;
    StateTime = 0;
    M570ScoreDispOn();
}

/*
 * fn_1_ABC  asm  756- 947   190 insns  -- MGSEQ_MODE_MAIN.
 *
 * The round loop. State 9 sets a round going, 10 runs it against the clock,
 * 11 scores it. Five rounds, or an early finish if player.c says the solo
 * player has already been caught.
 */
static void M570MainHook(s16 mode, s16 frameNo)
{
    switch(StateNo) {
        case 9:
            if(StateTime == 0) {
                M570PlayerRoundStart();
                M570StageMotionSet(1);
            }
            if(StateTime++ == 20) {
                M570TimerCreate();
                SeId = HuAudFXPlayVol(0x39C, 96);
                M570CrowdReactSet(1);
                M570SprPopCreate(SubStateNo);
                StateNo = 10;
                StateTime = 0;
            }
            break;
        case 10:
            if(StateTime++ == 60) {
                HuAudFXStop(SeId);
            }
            if(MgTimerDoneCheck(Timer)) {
                StateNo = 11;
                M570PlayerRoundEnd();
                StateTime = 0;
            }
            break;
        case 11:
            StateTime++;
            if(StateTime == 90) {
                SubStateNo++;
                MgTimerKill(Timer);
                M570PlayerScore();
                if(M570PlayerCaughtCheck() || SubStateNo == 5) {
                    if(M570PlayerCaughtCheck()) {
                        WinGrp = 0;
                    } else {
                        WinGrp = 1;
                        SoloPlayer->caughtF = 1;
                        SoloPlayer->mode = 5;
                        M570PlayerMotionSet(SoloPlayer, 6);
                    }
                    M570WinnerSet();
                    StateNo = 13;
                    M570StageMotionSet(2);
                    SeId = HuAudFXPlayVol(0x39C, 96);
                    M570CrowdReactSet(2);
                    M570ScoreFadeCreate();
                    MgSeqModeNext();
                }
            } else if(StateTime == 180) {
                StateTime = 0;
                StateNo = 9;
            }
            break;
    }
}

/* fn_1_D88  asm  950- 977    26 insns  -- MGSEQ_MODE_FINISH */
static void M570FinishHook(s16 mode, s16 frameNo)
{
    if(frameNo == 0 && BgmId != -1) {
        HuAudSStreamFadeOut(BgmId, 100);
    }
    StateNo = 13;
}

/*
 * fn_1_DEC  asm  980-1077    96 insns  -- MGSEQ_MODE_PREWIN.
 * Pulls the camera out to the wide view over 80 frames, then hands on.
 */
static void M570PreWinnerHook(s16 mode, s16 frameNo)
{
    if(frameNo == 0) {
        HuAudFXStop(SeId);
    }
    switch(StateNo) {
        case 13:
            CameraMoveObj = MgCameraMoveEntry(&StageViewW, &StageViewW2, 80.0f);
            M570PlayerWinPose();
            StateNo = 14;
            break;
        case 14:
            if(!MgCameraMoveCheck(CameraMoveObj)) {
                OMOBJ *obj;
                WinStartF = 0;
                obj = CameraMoveObj;
                omDelObjEx(objman, obj);
                StateNo = 15;
                M570PlayerWinSet();
                M570StageMotionSet(3);
                SeId = HuAudFXPlayVol(0x39C, 96);
                M570CrowdReactSet(20);
                MgSeqModeNext();
            }
            break;
    }
}

/*
 * fn_1_F54  asm 1080-1141    60 insns  -- MGSEQ_MODE_WINNER.
 * At frame 100 the two side models appear, everyone's pad rumbles, and the
 * fanfare plays.
 */
static void M570WinnerHook(s16 mode, s16 frameNo)
{
    int i;

    if(frameNo == 0) {
        StateNo = 17;
    }
    if(frameNo == 100) {
        for(i=0; i<4; i++) {
            omVibrate(i, 60, 12, 0);
        }
        HuAudFXPlay(0x914);
        Hu3DModelAttrReset(StageMdlId[11], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(StageMdlId[12], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(StageMdlId[11], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(StageMdlId[12], HU3D_MOTATTR_PAUSE);
    }
}

/* fn_1_1034 asm 1144-1146     1 insn   -- MGSEQ_MODE_CLOSE. Empty, as above. */
static void M570CloseHook(s16 mode, s16 frameNo)
{
}

/* fn_1_1174  asm 1239-1337   97 insns -- the score readout, hidden at first. */
static void M570ScoreWinCreate(void)
{
    HUSPRID sprId;
    int i;

    ScoreWinId = MgScoreWinCreate(132, 40);
    MgScoreWinPosSet(ScoreWinId, 288.0f, 420.0f);
    MgScoreWinDispSet(ScoreWinId, 0);
    for(i=0; i<5; i++) {
        sprId = espEntry(SprPlateDataTbl[i], 0x20, 0);
        espDrawNoSet(sprId, 0);
        espPosSet(sprId, PosTbl[i], 420.0f);
        espDispOff(sprId);
        SprPlateId[i] = sprId;

        sprId = espEntry(SprFaceDataTbl[i], 0x10, 0);
        espDrawNoSet(sprId, 0);
        espPosSet(sprId, PosTbl[i], 420.0f);
        espDispOff(sprId);
        SprFaceId[i] = sprId;
    }
}

/* fn_1_1038  asm 1149-1174   24 insns -- the three-minute clock. */
static void M570TimerCreate(void)
{
    Timer = MgTimerCreate(MGTIMER_TYPE_NORMAL);
    MgTimerParamSet(Timer, 180, 0, 0);
    MgTimerModeOnSet(Timer, MGTIMER_OFFTYPE_FADEOUT);
}

/*
 * fn_1_1098  asm 1177-1236   58 insns -- decide the winners.
 *
 * 1VS3: everyone whose grp matches WinGrp has won, so the winning side is
 * one player or three. MgSeqWinnerSet takes four character numbers and
 * CHARNO_NONE for the empty slots, which is what the -1 fill is doing.
 */
static void M570WinnerSet(void)
{
    s16 charNo[4];
    int i;

    for(i=0; i<4; i++) {
        charNo[i] = CHARNO_NONE;
        if(WinGrp == PlayerObj[i]->grp) {
            charNo[i] = PlayerObj[i]->charNo;
            if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                GwPlayer[i].mgCoinBonus = 10;
            }
        }
    }
    MgSeqWinnerSet(charNo[0], charNo[1], charNo[2], charNo[3]);
}

/* fn_1_12F0  asm 1340-1368   27 insns -- reveal the score readout. */
static void M570ScoreDispOn(void)
{
    int i;
    MgScoreWinDispSet(ScoreWinId, 1);
    for(i=0; i<5; i++) {
        espDispOn(SprPlateId[i]);
    }
}

/* fn_1_1464  asm 1446-1464   17 insns */
static void M570ScoreFadeCreate(void)
{
    omAddObjEx(objman, 0x1300, 0, 0, OM_GRP_NONE, M570ScoreFadeMain);
}

/*
 * fn_1_15FC  asm 1558-1589   30 insns -- pop one score panel's face sprite.
 * work[0] is the sprite, work[1] its frame counter.
 */
static void M570SprPopCreate(int no)
{
    OMOBJ *obj = omAddObjEx(objman, 0x1300, 0, 0, OM_GRP_NONE, M570SprPopMain);
    obj->work[0] = SprFaceId[no];
    obj->work[1] = 0;
}

/*
 * fn_1_16D4  asm 1621-1688   66 insns -- a one-shot particle burst, with an
 * object to kill it 30 frames later.
 */
HU3DPARMANID M570ParManCreate(HuVecF *pos)
{
    void *data = HuDataSelHeapReadNum(DATANUM(DATA_effect, 2), HU_MEMNUM_OVL, HEAP_MODEL);
    ANIMDATA *anim = HuSprAnimRead(data);
    HU3DPARMANID parManId = Hu3DParManCreate(anim, 100, &ParManParam);
    OMOBJ *obj;

    Hu3DParManPosSet(parManId, pos->x, pos->y, pos->z);
    Hu3DParManVecSet(parManId, 0.0f, 0.0f, 1.0f);
    Hu3DParManTimeLimitSet(parManId, 30);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 3);
    obj = omAddObjEx(objman, 0x1300, 0, 0, OM_GRP_NONE, M570ParManMain);
    obj->work[0] = 30;
    obj->work[1] = parManId;
    return parManId;
}

/*
 * fn_1_17DC  asm 1691-1726   34 insns -- stereo pan for a world position:
 * project it through the live camera and map screen x across the pan range.
 */
s16 M570PanGet(HuVecF *pos)
{
    HuVec2f screen;
    s16 pan;
    Hu3D3Dto2D(pos, (s16)CameraWork.no, &screen);
    pan = 32+(64.0f*(screen.x/576.0f));
    return pan;
}

/* fn_1_1864  asm 1729-1773   43 insns -- play a sound panned to a position. */
void M570SePlay(HuVecF *pos, s16 seId)
{
    HuAudFXPlayPan(seId, M570PanGet(pos));
}

/*
 * fn_1_1674  asm 1592-1618   25 insns -- a particle burst that deletes itself.
 * work[0] is the countdown, work[1] the HU3DPARMANID.
 */
static void M570ParManMain(OMOBJ *obj)
{
    obj->work[0]--;
    if(obj->work[0] == 0) {
        Hu3DParManKill((HU3DPARMANID)obj->work[1]);
        omDelObjEx(objman, obj);
    }
}

/*
 * fn_1_1354  asm 1371-1443   71 insns -- the object M570Fn1354Create starts.
 * Stubbed rather than left declared-only: a static that is declared and never
 * defined compiles clean under C89 and only fails at link, and this file is
 * not in PB_REL_FILES yet, so nothing would catch it. That is exactly how
 * m524dll shipped a mode-dispatch table naming three functions that did not
 * exist.
 */
static void M570ScoreFadeMain(OMOBJ *obj)
{
    float tpLvl;
    int i;

    obj->work[0]++;
    tpLvl = 1.0f-(0.05f*obj->work[0]);
    MgScoreWinTPLvlSet(ScoreWinId, tpLvl);
    for(i=0; i<5; i++) {
        espTPLvlSet(SprPlateId[i], tpLvl);
        espTPLvlSet(SprFaceId[i], tpLvl);
    }
    if(obj->work[0] == 20) {
        omDelObjEx(objman, obj);
    }
}

/*
 * fn_1_14A8  asm 1467-1555   87 insns -- the pop itself: the sprite fades up
 * from nothing over 60 frames while its scale falls back to 1.
 */
static void M570SprPopMain(OMOBJ *obj)
{
    float scale;
    s16 sprId = obj->work[0];
    float t;

    if(obj->work[1] == 0) {
        espDispOn(obj->work[0]);
    }
    t = sin((M_PI*((90.0f*obj->work[1])/60.0f))/180.0);
    scale = 1.0f+(2.0f-(2.0f*t));
    espScaleSet(sprId, scale, scale);
    espTPLvlSet(sprId, t);
    obj->work[1]++;
    if(obj->work[1] > 60) {
        omDelObjEx(objman, obj);
    }
}

/* Every function in m570.c is now written. player.c is not. */

/*
 * ===========================================================================
 * The framework, from REL/mgframe.h. The order below is the original object's,
 * and it is why the header is included eight times rather than once: within one
 * include the header emits in its own order, so MgFlowEntry ahead of the flow
 * control block -- which is how this object has it -- takes two.
 * ===========================================================================
 */
#define MGF_S_CAMERA
#include "REL/mgframe.h"

#define MGF_S_PAD
#include "REL/mgframe.h"

#define MGF_S_FLOWMAIN
#include "REL/mgframe.h"

#define MGF_S_FLOWENTRY
#include "REL/mgframe.h"
#define MGF_S_FLOWCTL
#include "REL/mgframe.h"

#define MGF_S_FLOWSTEP
#include "REL/mgframe.h"

#define MGF_S_PLAYERCONF
#include "REL/mgframe.h"

#define MGF_S_MATH
#include "REL/mgframe.h"
