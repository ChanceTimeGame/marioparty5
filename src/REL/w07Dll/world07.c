/*
 * w07dll -- Mario Party 5's seventh party board, "Bowser Nightmare": Bowser
 * himself walking the board, warp pipes, a rolling cube, a cannon, and red
 * spaces that decay back to blue over a few turns.
 *
 * Reference assembly:
 *
 *     ./games/mp5/gen_asm.sh w07Dll
 *     build/mp5-asm/w07Dll/asm/REL/w07Dll/world07.s
 *
 * Nothing under build/ is committed. Note the case: the module is **w07Dll**
 * everywhere the decomp build touches it (config.yml, configure.py, the asm
 * path) and **w07dll** everywhere the port does (ovl_table.h, this directory,
 * the .dll the loader searches for). project.py prints a "Case mismatch" line
 * about it; that is expected.
 *
 * THE NAMES ARE THE DISC'S, NOT INVENTED -- upstream's
 * config/GP5E01_00/rels/w07Dll/symbols.txt names every function, so what is
 * left here is bodies.
 *
 * Verify per function, never by the headline number:
 *
 *   cd games/mp5 && ./build/tools/ninja build/GP5E01_00/src/REL/w07Dll/world07.o
 *   ./tally.py w07Dll src/REL/w07dll/world07.c 11567
 *   R=$PWD/build/GP5E01_00/w07Dll/obj/REL/w07Dll/world07.o
 *   O=$PWD/build/GP5E01_00/src/REL/w07Dll/world07.o
 *   diff <($PWD/fndiff.py fn $R MB7_Create) <($PWD/fndiff.py fn $O MB7_Create)
 *
 * fndiff.py needs absolute paths, and gen_asm.sh must have been run first --
 * without the reference object every diff reads as empty rather than erroring.
 *
 * The closest worked examples are games/mp5/src/REL/w03dll/world03.c (finished)
 * and w06dll/world06.c. Read w03dll/NOTES.md before writing anything here; its
 * local-stack-slot rule and its "a model id local is int, not MBMODELID" rule
 * both apply unchanged.
 */

#include "game/board/main.h"
#include "game/board/effect.h"
#include "game/board/audio.h"
#include "game/board/model.h"
#include "game/board/masu.h"
#include "game/board/scroll.h"
#include "game/board/opening.h"
#include "game/board/capsule.h"
#include "game/board/branch.h"
#include "game/board/camera.h"
#include "game/board/player.h"
#include "game/board/guide.h"
#include "game/board/window.h"
#include "game/board/coin.h"
#include "game/board/com.h"
#include "game/board/roulette.h"
#include "game/board/star.h"

#include "game/sprite.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/wipe.h"
#include "game/gamemes.h"
#include "game/pad.h"
#include "game/process.h"
#include "game/object.h"
#include "humath.h"

#include "datanum/w07.h"
#include "datanum/capsulechar4.h"
#include "datanum/charmot.h"
#include "messnum/board_w07.h"

/* --- this board's space flags --- */

#define MB7EV_HOU_FLAG MASU_FLAG_BIT(7)
#define MB7EV_KOOPACUBE_FLAG MASU_FLAG_BIT_MULTI(8, 2)
#define MB7EV_KOOPACUBE_LINK_FLAG MASU_FLAG_BIT_MULTI(5, 2)
#define MB7EV_DOKANIN_FLAG (MASU_FLAG_BIT(10) | MASU_FLAG_BIT(12))
#define MB7EV_DOKAN_FLAG (MASU_FLAG_BIT(11) | MASU_FLAG_BIT(13))
#define MB7EV_RED_LINK_FLAG MASU_FLAG_BIT(14)
#define MB7EV_KOOPAWALK_FLAG MASU_FLAG_BIT(15)

#define MB7_OBJ_MAX 11
#define MB7_BACKOBJ_MAX 24
#define MB7_EFF_MAX 4

#define MB7EV_KOOPA_MAX 2

/* Bowser's own animation set, indexed into mb7ev_KoopaMotFileTbl. */
#define MB7EV_KOOPAMOT_IDLE 0
#define MB7EV_KOOPAMOT_WALK 1
#define MB7EV_KOOPAMOT_STOMP 2
#define MB7EV_KOOPAMOT_LAUGH 3
#define MB7EV_KOOPAMOT_JUMPSTART 4
#define MB7EV_KOOPAMOT_LOSE 5
#define MB7EV_KOOPAMOT_JUMP 6
#define MB7EV_KOOPAMOT_SPEAK 7
#define MB7EV_KOOPAMOT_HOLD 8
#define MB7EV_KOOPAMOT_MAX 9

typedef struct MB7Ev_Koopa_s {
    int focusF;                         /* 0x00 */
    int focusNextF;                     /* 0x04 */
    int coinLoseF;                      /* 0x08 */
    int mode;                           /* 0x0C */
    int prevMasuId;                     /* 0x10 */
    int masuId;                         /* 0x14 */
    int turnF;                          /* 0x18 */
    int landF;                          /* 0x1C */
    int step;                           /* 0x20 */
    float time;                         /* 0x24 */
    float maxTime;                      /* 0x28 */
    float accel;                        /* 0x2C */
    float angleY;                       /* 0x30 */
    int mdlId[4];                       /* 0x34 */
    int motId[MB7EV_KOOPAMOT_MAX];      /* 0x44 */
    int effMdlId;                       /* 0x68 */
    s32 dataStatId;                     /* 0x6C */
    int motNo;                          /* 0x70 */
    int fxStep;                         /* 0x74 */
    HuVecF pos;                         /* 0x78 */
    HuVecF rot;                         /* 0x84 */
    HuVecF vel;                         /* 0x90 */
} MB7EV_KOOPA;

/* One per player, 0x5C each. MB7Ev_KoopaWalk walks all four with a 0x5C
   stride; the pipe events use element 0 as scratch and never index it. */
typedef struct MB7Ev_Player_s {
    int enableF;                        /* 0x00 */
    int unk04;                          /* 0x04 */
    int mode;                           /* 0x08 */
    int masuId;                         /* 0x0C */
    int step;                           /* 0x10 */
    float maxTime;                      /* 0x14 */
    u8 unk18[0x1C-0x18];                /* 0x18 */
    float angleY;                       /* 0x1C */
    s16 motId;                          /* 0x20 */
    u8 unk22[0x2C-0x22];                /* 0x22 */
    HuVecF pos;                         /* 0x2C */
    HuVecF rot;                         /* 0x38 */
    HuVecF vel;                         /* 0x44 */
    u8 unk50[0x5C-0x50];                /* 0x50 */
} MB7EV_PLAYER;

/* The cannon's own work, 0x84. */
typedef struct MB7Ev_Hou_s {
    int mode;                           /* 0x00 */
    u8 unk04[0x10-0x04];                /* 0x04 */
    float angleY;                       /* 0x10 */
    float angleSpeed;                   /* 0x14 */
    float charge;                       /* 0x18 */
    int fireF;                          /* 0x1C */
    u8 unk20[0x30-0x20];                /* 0x20 */
    int fireEff[4];                     /* 0x30 */
    HuVecF firePos;                     /* 0x40 */
    HuVecF rot;                         /* 0x4C */
    u8 unk58[0x64-0x58];                /* 0x58 */
    HuVecF pos;                         /* 0x64 */
    u8 unk70[0x84-0x70];                /* 0x70 */
} MB7EV_HOU;

typedef struct MB7_Work_s {
    int objMdlId[MB7_OBJ_MAX];              /* 0x000 */
    int backObjMdlId[MB7_BACKOBJ_MAX];      /* 0x02C */
    ANIMDATA *effAnim88;                    /* 0x08C */
    ANIMDATA *effAnim8C;                    /* 0x090 */
    HU3DMODELID effMdlId[MB7_EFF_MAX];      /* 0x094 */
    int unk09C;                             /* 0x09C */
    MB7EV_KOOPA koopa;                      /* 0x0A0 */
    MB7EV_HOU hou;                          /* 0x13C */
    MB7EV_PLAYER player[GW_PLAYER_MAX];     /* 0x1C0 */
    int masuNum;                            /* 0x330 */
    u8 *masuRedTbl;                         /* 0x334 */
} MB7_WORK;

/* --- .data --- */

static u32 mb7_ObjFileTbl[MB7_OBJ_MAX] = {
    DATANUM(DATA_w07, 4),
    DATANUM(DATA_w07, 6),
    DATANUM(DATA_w07, 7),
    DATANUM(DATA_w07, 8),
    DATANUM(DATA_w07, 11),
    DATANUM(DATA_w07, 12),
    DATANUM(DATA_w07, 13),
    DATANUM(DATA_w07, 14),
    DATANUM(DATA_w07, 16),
    DATANUM(DATA_w07, 17),
    DATANUM(DATA_w07, 18),
};

static u32 mb7_BackObjFileTbl[MB7_BACKOBJ_MAX] = {
    DATANUM(DATA_w07, 5), DATANUM(DATA_w07, 5), DATANUM(DATA_w07, 5),
    DATANUM(DATA_w07, 5), DATANUM(DATA_w07, 5), DATANUM(DATA_w07, 5),
    DATANUM(DATA_w07, 9), DATANUM(DATA_w07, 9), DATANUM(DATA_w07, 9),
    DATANUM(DATA_w07, 9),
    DATANUM(DATA_w07, 10), DATANUM(DATA_w07, 10), DATANUM(DATA_w07, 10),
    DATANUM(DATA_w07, 10), DATANUM(DATA_w07, 10), DATANUM(DATA_w07, 10),
    DATANUM(DATA_w07, 15), DATANUM(DATA_w07, 15), DATANUM(DATA_w07, 15),
    DATANUM(DATA_w07, 15), DATANUM(DATA_w07, 15), DATANUM(DATA_w07, 15),
    DATANUM(DATA_w07, 15), DATANUM(DATA_w07, 15),
};

static HuVecF mb7ev_DoorPosTbl[MB7EV_KOOPA_MAX] = {
    { 4400, 495, -4000 },
    { -4400, 495, -4000 },
};

static HuVecF mb7ev_KoopaCubePosTbl[MB7EV_KOOPA_MAX][2] = {
    { { -3850, 1150, -5780 }, { -3635, 1150, -6000 } },
    { { 3850, 1150, -5780 }, { 3635, 1150, -6000 } },
};

static HuVecF mb7ev_KoopaAsibaPosTbl[MB7EV_KOOPA_MAX] = {
    { -3925, 1350, -6085 },
    { 3925, 1350, -6085 },
};

static HuVecF mb7ev_KoopaCubeDustColTbl[MB7EV_KOOPA_MAX*2] = {
    { 192, 64, 64 },
    { 0, 131, 131 },
    { 64, 64, 192 },
    { 131, 131, 0 },
};

static HuVecF mb7ev_KoopaWalkStartPosTbl[MB7EV_KOOPA_MAX] = {
    { 4580, 495, -4260 },
    { -4580, 495, -4260 },
};

static HuVecF mb7ev_DustColTbl[4] = {
    { 128, 128, 128 },
    { 64, 64, 64 },
    { 64, 64, 192 },
    { 131, 131, 0 },
};

static HuVecF mb7_BackObjPosTbl[MB7_BACKOBJ_MAX] = {
    { -685, 685, -4260 },   { 685, 685, -4260 },
    { -945, 400, -1120 },   { 945, 400, -1120 },
    { -615, -315, 645 },    { 615, -315, 645 },
    { -715, -100, -1600 },  { 715, -100, -1600 },
    { -715, -100, -2435 },  { 715, -100, -2435 },
    { -2270, 1465, -5835 }, { 2270, 1465, -5835 },
    { -3530, 500, -2660 },  { 3530, 500, -2660 },
    { -2895, 500, -2030 },  { 2895, 500, -2030 },
    { -615, 1400, -4950 },  { 615, 1400, -4950 },
    { -3025, 500, -3175 },  { 3025, 500, -3175 },
    { -2385, 500, -2545 },  { 2385, 500, -2545 },
    { -1245, -400, -300 },  { 1245, -400, -300 },
};

static float mb7_BackObjRotYTbl[MB7_BACKOBJ_MAX] = {
    -60, 60, -45, 45, 30, -30, 0, 0, 0, 0, -150, 150,
    -45, 45, -45, 45, 0, 0, -45, 45, -45, 45, 45, -45,
};

static char mb7ev_GuruPosHookName[] = "kupa_dream_all-guru_pos";

static char mb7ev_KupaPosHookName[] = "kupa_dream_all-kupa_pos";

static char mb7ev_FirePosHookName[] = "kupa_dream_all-fire_pos";

static char mb7ev_HikouPosHookName[] = "hikou_pos";

static u32 mb7ev_KoopaMotFileTbl[MB7EV_KOOPAMOT_MAX] = {
    CAPSULECHAR4_HSF_koopa_idle,
    CAPSULECHAR4_HSF_koopa_walk,
    CAPSULECHAR4_HSF_koopa_stomp,
    CAPSULECHAR4_HSF_koopa_laugh,
    CAPSULECHAR4_HSF_koopa_jump_start,
    CAPSULECHAR4_HSF_koopa_lose,
    CAPSULECHAR4_HSF_koopa_jump,
    CAPSULECHAR4_HSF_koopa_last5_speak,
    CAPSULECHAR4_HSF_koopa_hold,
};

/* --- .bss --- */

static OMOBJ *mb7_MainObj;
static MB7_WORK mb7_Work;
static u8 *mb7_SaveWorkP;
static MBMODELID mb7_MainMdlId;

/* --- forward declarations --- */

void ObjectSetup(void);
static void MB7_Create(void); /* 159 instructions */
static void MB7_ObjectCreate(void); /* 251 instructions */
static void MB7_Kill(void); /* 108 instructions */
static void MB7_MainObjUpdate(OMOBJ *obj); /* 26 instructions */
static void MB7_LightSet(void); /* 34 instructions */
static void MB7_LightReset(void); /* 1 instructions */
static int MB7Ev_MasuHatena(int playerNo); /* 53 instructions */
static void MB7_MasuStub(void); /* 1 instructions */
static int MB7Ev_MasuWalkPre(int playerNo); /* 1 instructions */
static int MB7Ev_MasuWalkPost(int playerNo); /* 26 instructions */
static int MB7_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF); /* 45 instructions */
static void MB7Ev_KoopaWalk(int playerNo); /* 305 instructions */
static void MB7Ev_KoopaWalkUpdate(void); /* 1263 instructions */
static void MB7Ev_KoopaWalkPlayerUpdate(void); /* 186 instructions */
static void MB7Ev_KoopaWalkCoinLose(void); /* 27 instructions */
static void MB7_EffDustHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 639 instructions */
static void MB7Ev_Dokan(int playerNo); /* 420 instructions */
static void MB7Ev_DokanSet(int playerNo, int masuId, BOOL inF); /* 146 instructions */
static void MB7Ev_DokanPlayerSet(int playerNo, int masuId, BOOL inF); /* 113 instructions */
static void MB7Ev_DokanIn(int playerNo); /* 585 instructions */
static void MB7Ev_KoopaCube(int playerNo); /* 1357 instructions */
static void MB7Ev_KoopaAsibaUpdate(void); /* 60 instructions */
static HU3DMODELID MB7Ev_KoopaCubeDustCreate(HuVecF *pos, int mode); /* 38 instructions */
static void MB7Ev_KoopaCubeDustEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 446 instructions */
static void MB7Ev_Hou(int playerNo); /* 983 instructions */
static void MB7Ev_HouPlayerUpdate(void); /* 220 instructions */
static void MB7Ev_KoopaFire1Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 776 instructions */
static void MB7Ev_KoopaFire2Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 683 instructions */
static void MB7Ev_KoopaFire3Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 859 instructions */
static void MB7Ev_KoopaFire4Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 862 instructions */
static void MB7Ev_KoopaWalkDustCreate(int no); /* 29 instructions */
static void MB7Ev_KoopaInit(void); /* 39 instructions */
static void MB7Ev_KoopaCreate(void); /* 31 instructions */
static void MB7Ev_KoopaMotionCreate(int motNo); /* 31 instructions */
static void MB7Ev_KoopaDataClose(void); /* 14 instructions */
static void MB7Ev_KoopaMotionNoSet(int motNo, BOOL loopF); /* 37 instructions */
static void MB7Ev_KoopaMotionShiftSet(int motNo, BOOL loopF); /* 43 instructions */
static BOOL MB7Ev_KoopaMotionCheck(void); /* 22 instructions */
static void MB7Ev_KoopaWalkFxPlay(void); /* 70 instructions */
static void MB7Ev_KoopaClose(void); /* 33 instructions */
void MB7Ev_MasuRedSet(int masuId); /* 12 instructions */
static void MB7Ev_MasuRedInit(void); /* 121 instructions */
static void MB7Ev_MasuRedClose(void); /* 26 instructions */
static BOOL MB7Ev_RedResetWin(void); /* 21 instructions */
static void MB7Ev_RedResetHook(void); /* 153 instructions */
static float MB7_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3); /* 47 instructions */
static float MB7_AngleDiff(float start, float end); /* 45 instructions */
static unsigned int MB7Ev_BitGet(int outMask, unsigned int inMask); /* 30 instructions */
static unsigned int MB7Ev_MasuFlagGet(int outMask, unsigned int inMask); /* 29 instructions */

/* ObjectSetup -- 21 instructions */
void ObjectSetup(void)
{
    GWPartyFSet(TRUE);
    MBObjectSetup(MBNO_WORLD_7, MB7_Create, MB7_Kill);
}

/* 159 instructions */
static void MB7_Create(void)
{
    int boardNo = MBBoardNoGet();

    memset(&mb7_Work, 0, sizeof(MB7_WORK));
    HuAudSndGrpSetSet(MSM_GRP_BD7);
    mb7_SaveWorkP = MBSaveWorkPGet();
    MBMasuCreate(W07_BIN_masuData);
    mb7_MainMdlId = MBModelCreate(W07_HSF_map, NULL, FALSE);
    MBModelPosSet(mb7_MainMdlId, 0, 0, 0);
    MBModelAttrSet(mb7_MainMdlId, HU3D_MOTATTR_LOOP);
    MBScrollInit(W07_HSF_scrollCol, 21000, -2500);
    {
        HuVecF cameraPos = { 0, -1000, -4500 };
        HuVecF cameraRot = { -33, 0, 0 };
        HuVecF mapCameraPos = { 0, 0, -2500 };
        HuVecF mapCameraRot = { -78, 0, 0 };
        MBOpeningViewSet(&cameraRot, &cameraPos, 20000);
        MBMapViewCameraSet(&mapCameraRot, &mapCameraPos, 21000);
    }
    MBLightHookSet(MB7_LightSet, MB7_LightReset);
    MBCapsuleColCreate(W07_HSF_capsuleCol);
    MBBranchFlagSet(MASU_FLAG_BIT(6));
    MBBranchFlagSet(MASU_FLAG_BIT(5));
    MBMasuPathCheckHookSet(MB7_MasuPathCheck);
    if(GwSystem.last5Effect == MB_LAST5_EFF_REDKUPA) {
        MBMasuTypeChange(MASU_TYPE_RED, MASU_TYPE_KUPA);
    }
    MB7Ev_MasuRedInit();
    MB7_ObjectCreate();
    HuDataDirClose(DATA_w07);
    MBMasuWalkPreHookSet(MB7Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB7Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB7Ev_MasuHatena);
    mb7_MainObj = MBAddObj(32768, 0, 0, MB7_MainObjUpdate);
}

/* 251 instructions */
static void MB7_ObjectCreate(void)
{
    HuVecF pos = { 0, 0, 0 };
    int i;
    int mdlId;

    for(i=0; i<MB7_OBJ_MAX; i++) {
        mb7_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        mb7_Work.backObjMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_EFF_MAX; i++) {
        mb7_Work.effMdlId[i] = HU3D_MODELID_NONE;
    }
    for(i=0; i<MB7_OBJ_MAX; i++) {
        if(mb7_ObjFileTbl[i]) {
            mdlId = MBModelCreate(mb7_ObjFileTbl[i], NULL, FALSE);
            mb7_Work.objMdlId[i] = mdlId;
            MBModelPosSet(mdlId, 0, 0, 0);
            MBMotionSpeedSet(mdlId, 0);
            MBMotionShapeSpeedSet(mdlId, 0);
        }
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        mdlId = MBModelCreate(mb7_BackObjFileTbl[i], NULL, TRUE);
        mb7_Work.backObjMdlId[i] = mdlId;
        MBModelPosSetV(mdlId, &mb7_BackObjPosTbl[i]);
        MBModelRotSet(mdlId, 0, mb7_BackObjRotYTbl[i], 0);
    }
    mdlId = mb7_Work.objMdlId[0];
    if(mdlId >= 0) {
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_SHAPE_LOOP);
        MBMotionSpeedSet(mdlId, 0.5f);
        MBMotionShapeSpeedSet(mdlId, 0.5f);
    }
    mdlId = mb7_Work.objMdlId[2];
    if(mdlId >= 0) {
        MBModelPosSet(mdlId, 0, 1495, -4645);
    }
    for(i=4; i<=10; i++) {
        mdlId = mb7_Work.objMdlId[i];
        if(mdlId >= 0) {
            MBModelDispSet(mdlId, FALSE);
        }
    }
    Hu3DModelLayerSet(MBModelIdGet(mb7_Work.objMdlId[10]), 2);
    for(i=16; i<=24; i++) {
        mdlId = mb7_Work.backObjMdlId[i];
        if(mdlId >= 0) {
            MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
            MBMotionSpeedSet(mdlId, 1);
        }
    }
    mb7_Work.effAnim88 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w07, 0x13), HU_MEMNUM_OVL));
    mb7_Work.effAnim8C = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w07, 0x14), HU_MEMNUM_OVL));
    mb7_Work.effMdlId[0] = MBEffCreate(mb7_Work.effAnim88, 1);
    mb7_Work.effMdlId[1] = MBEffCreate(mb7_Work.effAnim8C, 1);
}

/* 108 instructions */
static void MB7_Kill(void)
{
    int i;

    if(mb7_MainMdlId >= 0) {
        MBModelKill(mb7_MainMdlId);
        mb7_MainMdlId = MB_MODEL_NONE;
    }
    MB7Ev_MasuRedClose();
    MBCameraModelViewSet(MB_MODEL_NONE, NULL, NULL, -1, 45, 63);
    for(i=0; i<MB7_OBJ_MAX; i++) {
        if(mb7_Work.objMdlId[i] >= 0) {
            MBModelKill(mb7_Work.objMdlId[i]);
        }
        mb7_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_BACKOBJ_MAX; i++) {
        if(mb7_Work.backObjMdlId[i] >= 0) {
            MBModelKill(mb7_Work.backObjMdlId[i]);
        }
        mb7_Work.backObjMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<MB7_EFF_MAX; i++) {
        if(mb7_Work.effMdlId[i] >= 0) {
            MBEffKill(mb7_Work.effMdlId[i]);
        }
        mb7_Work.effMdlId[i] = HU3D_MODELID_NONE;
    }
}

/* 26 instructions */
static void MB7_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;

    if(MBKillCheck()) {
        if(mb7_MainObj != NULL) {
            omDelObjEx(mbObjMan, mb7_MainObj);
        }
        return;
    }
    camera = MBCameraGet();
}

/* 34 instructions */
static void MB7_LightSet(void)
{
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DModelLightInfoSet(MBModelIdGet(mb7_MainMdlId), TRUE);
    MBPreTurnHookSet(MB7Ev_RedResetHook);
}

/* 1 instructions */
static void MB7_LightReset(void)
{
}

/* 53 instructions */
static int MB7Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    u32 flag;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    if(flag & MB7EV_KOOPAWALK_FLAG) {
        MB7Ev_KoopaWalk(playerNo);
    } else if(flag & MB7EV_DOKAN_FLAG) {
        MB7Ev_Dokan(playerNo);
    } else if(flag & MB7EV_DOKANIN_FLAG) {
        MB7Ev_DokanIn(playerNo);
    } else if(flag & MB7EV_KOOPACUBE_FLAG) {
        MB7Ev_KoopaCube(playerNo);
    } else if(flag & MB7EV_HOU_FLAG) {
        MB7Ev_Hou(playerNo);
    }
}

/* 1 instructions */
static void MB7_MasuStub(void)
{
}

/* 1 instructions -- MASUPLAYERHOOK says int, but the original has no return
   statement, so nothing loads r3. Same shape as w03dll's. */
static int MB7Ev_MasuWalkPre(int playerNo)
{
}

/* 26 instructions */
static int MB7Ev_MasuWalkPost(int playerNo)
{
    MASU *masu;
    u32 flag;
    s16 masuId;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    return 0;
}

/* 45 instructions */
static int MB7_MasuPathCheck(s16 id, u32 flag, s16 *linkTbl, BOOL endF)
{
    int num = 0;
    int i;
    int masuNum;
    int no;

    if(flag & MB7EV_DOKANIN_FLAG) {
        masuNum = MBMasuNumGet(MASU_LAYER_DEFAULT);
        no = 0;
        for(i=1; i<=masuNum; i++) {
            MASU *masuP = MBMasuGet(MASU_LAYER_DEFAULT, i);
            if(masuP->flag & MB7EV_DOKAN_FLAG) {
                linkTbl[num++] = i;
            }
        }
    }
    if(num <= 0) {
        num = -1;
    }
    return num;
}

/* 305 instructions */
static void MB7Ev_KoopaWalk(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MASU *masu;
    int no;
    int i;
    int emitter;
    u32 flag;
    float zoom;

    koopa = &mb7_Work.koopa;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    zoom = MBCameraZoomGet();
    no = 0;
    if(masu->pos.x < 0) {
        no = 1;
    }
    MB7Ev_KoopaInit();
    MBPlayerMotIdleSet(playerNo);
    MBMotionTimeSet(mb7_Work.objMdlId[1], 0);
    MBMotionSpeedSet(mb7_Work.objMdlId[1], 1);
    emitter = -1;
    for(i=0; i<130; i++) {
        if(i == 0) {
            emitter = HuAudFXEmiterPlay(1558, &mb7ev_DoorPosTbl[no]);
        } else if(i == 120) {
            HuAudFXStop(emitter);
            HuAudFXEmiterPlay(1559, &mb7ev_DoorPosTbl[no]);
        }
        HuPrcVSleep();
    }
    MBMotionSpeedSet(mb7_Work.objMdlId[1], 0);
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_WALK);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LAUGH);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_JUMP);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_SPEAK);
    MB7Ev_KoopaDataClose();
    koopa->effMdlId = MBEffCreate(mb7_Work.effAnim8C, 128);
    MBEffHookSet(koopa->effMdlId, MB7_EffDustHook);
    Hu3DModelLayerSet(koopa->effMdlId, 2);
    koopa->prevMasuId = -1;
    koopa->masuId = GwPlayer[playerNo].masuId;
    MB7Ev_KoopaWalkUpdate();
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    MB7Ev_KoopaWalkPlayerUpdate();
    MBAudFXPlay(713);
    MBWinCreate(2, MESS_BOARD_W07_KOOPAWALK_BEGIN, 7);
    MBTopWinWait();
    MBTopWinKill();
    MBCameraPosViewSet(NULL, NULL, NULL, 2800, -1, 30);
    while(koopa->mode < 11) {
        MB7Ev_KoopaWalkUpdate();
        MB7Ev_KoopaWalkPlayerUpdate();
        HuPrcVSleep();
    }
    MBWinCreate(2, MESS_BOARD_W07_KOOPAWALK_END, 7);
    MBTopWinWait();
    MBTopWinKill();
    MBCameraFocusSet(-1);
    while(koopa->mode != -1) {
        MB7Ev_KoopaWalkUpdate();
        MB7Ev_KoopaWalkPlayerUpdate();
        HuPrcVSleep();
    }
    MBMotionSpeedSet(mb7_Work.objMdlId[1], 1);
    MBMotionTimeSet(mb7_Work.objMdlId[1], 240);
    for(i=0; i<130; i++) {
        if(i == 0) {
            emitter = HuAudFXEmiterPlay(1558, &mb7ev_DoorPosTbl[1-no]);
        } else if(i == 120) {
            HuAudFXStop(emitter);
            HuAudFXEmiterPlay(1559, &mb7ev_DoorPosTbl[1-no]);
        }
        MB7Ev_KoopaWalkPlayerUpdate();
        HuPrcVSleep();
    }
    MBMotionTimeSet(mb7_Work.objMdlId[1], 0);
    MBMotionSpeedSet(mb7_Work.objMdlId[1], 0);
    MBEffKill(koopa->effMdlId);
    koopa->effMdlId = -1;
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<GW_PLAYER_MAX; i++) {
        mb7_Work.player[i].mode = -1;
    }
    MB7Ev_KoopaWalkPlayerUpdate();
    MB7Ev_KoopaClose();
    MBCameraFocusPlayerSet(playerNo);
    MBCameraSkipSet(FALSE);
    MBCameraZoomSet(zoom);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
}

/* 1263 instructions */
static void MB7Ev_KoopaWalkUpdate(void)
{
    MB7EV_KOOPA *koopa;
    MASU *masu;
    int i;
    int mdlId;
    MASU *prevMasu;
    BOOL nextF;
    BOOL redF;
    int coinMdlId;
    MASU *linkMasu;
    int num;
    float t;
    float gravity;
    float diff;
    float angle;

    koopa = &mb7_Work.koopa;
    prevMasu = masu = NULL;
    if(koopa->prevMasuId > 0) {
        prevMasu = MBMasuGet(MASU_LAYER_DEFAULT, koopa->prevMasuId);
    }
    if(koopa->masuId > 0) {
        masu = MBMasuGet(MASU_LAYER_DEFAULT, koopa->masuId);
    }
    mdlId = koopa->mdlId[0];
    MB7Ev_KoopaWalkFxPlay();
    if(koopa->turnF) {
        if(koopa->step == 0) {
            koopa->angleY = 180.0 * (atan2(masu->pos.x - koopa->pos.x,
                                           masu->pos.z - koopa->pos.z) / M_PI);
            diff = MB7_AngleDiff(koopa->rot.y, koopa->angleY);
            angle = fabsf2(diff);
            if(angle > 20) {
                koopa->maxTime = 1/(0.33333334f*angle);
                koopa->time = 0;
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_WALK, TRUE);
                MBMotionSpeedSet(mdlId, 2);
                koopa->step++;
            }
        }
        if(koopa->step > 0) {
            koopa->time += 1;
            t = koopa->time*koopa->maxTime;
            if(t > 1) {
                t = 1;
            }
            MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f*t);
            diff = MB7_AngleDiff(koopa->rot.y, koopa->angleY);
            angle = fabsf2(diff);
            if(angle < 5) {
                koopa->turnF = 0;
                koopa->step = 0;
            }
            MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
            MBModelRotSetV(koopa->mdlId[0], &koopa->rot);
            return;
        }
    }
    nextF = FALSE;
    redF = FALSE;
    switch(koopa->mode) {
        case -1:
            break;

        case 0:
            i = 0;
            if(masu->pos.x < 0) {
                i++;
            }
            mb7_SaveWorkP[i] = 2;
            koopa->pos = mb7ev_KoopaWalkStartPosTbl[i];
            koopa->mode = 1;
            break;

        case 1:
            if(koopa->step == 0) {
                MBModelDispSet(mdlId, TRUE);
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_WALK, TRUE);
                MBMotionSpeedSet(mdlId, 2);
                PSVECSubtract(&masu->pos, &koopa->pos, &koopa->vel);
                koopa->angleY = koopa->rot.y = 180.0 * (atan2(koopa->vel.x, koopa->vel.z) / M_PI);
                koopa->maxTime = 0.120000005f*PSVECMag(&koopa->vel);
                PSVECScale(&koopa->vel, &koopa->vel, 1/koopa->maxTime);
                koopa->time = 0;
                koopa->step++;
            } else {
                koopa->time += 1;
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->time >= 0.68f*koopa->maxTime) {
                    koopa->focusNextF = 1;
                    koopa->mode = 3;
                    koopa->step = 0;
                }
            }
            break;

        case 2:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_WALK, TRUE);
                MBMotionSpeedSet(mdlId, 2);
                PSVECSubtract(&masu->pos, &koopa->pos, &koopa->vel);
                koopa->angleY = 180.0 * (atan2(koopa->vel.x, koopa->vel.z) / M_PI);
                koopa->maxTime = 0.15f*PSVECMag(&koopa->vel);
                PSVECScale(&koopa->vel, &koopa->vel, 1/koopa->maxTime);
                koopa->time = 0;
                koopa->step++;
            } else {
                koopa->time += 1;
                t = 0.06666667f*koopa->time;
                if(t > 1) {
                    t = 1;
                }
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f*t);
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->maxTime-koopa->time < 15) {
                    redF = TRUE;
                }
                if(koopa->time >= koopa->maxTime) {
                    nextF = TRUE;
                }
            }
            break;

        case 3:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_JUMP, FALSE);
                koopa->landF = 0;
                koopa->time = 0;
                koopa->step++;
            } else if(koopa->step == 1) {
                koopa->time += 1;
                if(koopa->time >= 25) {
                    PSVECSubtract(&masu->pos, &koopa->pos, &koopa->vel);
                    koopa->angleY = 180.0 * (atan2(koopa->vel.x, koopa->vel.z) / M_PI);
                    t = 1;
                    gravity = -4900;
                    koopa->vel.x /= t;
                    koopa->vel.z /= t;
                    koopa->vel.y = koopa->vel.y/t-(0.5f*t)*gravity;
                    PSVECScale(&koopa->vel, &koopa->vel, 0.016666668f);
                    koopa->maxTime = 60*t;
                    koopa->accel = 0.016666668f*(0.016666668f*gravity);
                    koopa->time = 0;
                    koopa->step++;
                }
            } else if(koopa->step == 2) {
                koopa->time += 1;
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                koopa->vel.y += koopa->accel;
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->time > 3) {
                    MBMotionSpeedSet(mdlId, 0.95f*MBMotionSpeedGet(mdlId));
                }
                if(MBMotionTimeGet(mdlId) > 40) {
                    MBMotionSpeedSet(mdlId, 0);
                    koopa->step++;
                }
            } else if(koopa->step == 3) {
                koopa->time += 1;
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                koopa->vel.y += koopa->accel;
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->maxTime-koopa->time < 10) {
                    MBMotionSpeedSet(mdlId, 1);
                    koopa->landF = 1;
                }
                if(koopa->vel.y < 0) {
                    if(koopa->pos.y-masu->pos.y < 200) {
                        koopa->landF = 1;
                    }
                    if(koopa->pos.y <= masu->pos.y) {
                        koopa->pos.y = masu->pos.y;
                        koopa->step++;
                        MBCameraQuakeSet(12, 50);
                        MBAudFXPlay(873);
                        MB7Ev_KoopaWalkDustCreate(0);
                        redF = TRUE;
                    }
                }
            } else if(koopa->step == 4) {
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                if(MBMotionEndCheck(mdlId)) {
                    koopa->landF = 0;
                    nextF = TRUE;
                }
            }
            break;

        case 4:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_SPEAK, FALSE);
                koopa->time = 0;
                koopa->step++;
            } else if(koopa->step == 1) {
                koopa->time += 1;
                if(koopa->time >= 10) {
                    PSVECSubtract(&masu->pos, &koopa->pos, &koopa->vel);
                    koopa->angleY = 180.0 * (atan2(koopa->vel.x, koopa->vel.z) / M_PI);
                    t = 0.6666667f;
                    gravity = -4900;
                    koopa->vel.x /= t;
                    koopa->vel.z /= t;
                    koopa->vel.y = koopa->vel.y/t-(0.5f*t)*gravity;
                    PSVECScale(&koopa->vel, &koopa->vel, 0.016666668f);
                    koopa->maxTime = 60*t;
                    koopa->accel = 0.016666668f*(0.016666668f*gravity);
                    koopa->time = 0;
                    koopa->step++;
                }
            } else if(koopa->step == 2) {
                koopa->time += 1;
                t = 0.06666667f*koopa->time;
                if(t > 1) {
                    t = 1;
                }
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f*t);
                koopa->vel.y += koopa->accel;
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->vel.y < 0 && koopa->pos.y <= masu->pos.y) {
                    koopa->pos.y = masu->pos.y;
                    koopa->step++;
                    MBCameraQuakeSet(12, 30.000002f);
                    MBAudFXPlay(873);
                    MB7Ev_KoopaWalkDustCreate(1);
                    redF = TRUE;
                }
            } else if(koopa->step == 3) {
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                if(MB7Ev_KoopaMotionCheck()) {
                    nextF = TRUE;
                }
            }
            break;

        case 5:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
                MBAudFXPlay(713);
                koopa->time = 0;
                koopa->step++;
            } else if(koopa->step == 1) {
                if(koopa->coinLoseF == 0 && MB7Ev_KoopaMotionCheck()) {
                    nextF = TRUE;
                }
            }
            break;

        case 10:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_WALK, TRUE);
                MBMotionSpeedSet(mdlId, 2);
                koopa->angleY = 0;
                koopa->time = 0;
                koopa->step++;
            } else if(koopa->step == 1) {
                koopa->time += 1;
                t = 0.1f*koopa->time;
                if(t > 1) {
                    t = 1;
                }
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f*t);
                diff = MB7_AngleDiff(koopa->rot.y, koopa->angleY);
                angle = fabsf2(diff);
                if(angle < 5) {
                    MBAudFXPlay(713);
                    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
                    koopa->step++;
                }
            } else if(koopa->step == 2) {
                if(MB7Ev_KoopaMotionCheck()) {
                    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
                    koopa->step = 0;
                    koopa->mode++;
                }
            }
            break;

        case 11:
            if(koopa->step == 0) {
                MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_WALK, TRUE);
                MBMotionSpeedSet(mdlId, 2);
                i = 0;
                if(masu->pos.x < 0) {
                    i++;
                }
                PSVECSubtract(&mb7ev_KoopaWalkStartPosTbl[i], &koopa->pos, &koopa->vel);
                koopa->angleY = 180.0 * (atan2(koopa->vel.x, koopa->vel.z) / M_PI);
                koopa->maxTime = 0.120000005f*PSVECMag(&koopa->vel);
                PSVECScale(&koopa->vel, &koopa->vel, 1/koopa->maxTime);
                koopa->time = 0;
                koopa->step++;
            } else if(koopa->step == 1) {
                koopa->time += 1;
                t = 0.033333335f*koopa->time;
                if(t > 1) {
                    t = 1;
                }
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f*t);
                diff = MB7_AngleDiff(koopa->rot.y, koopa->angleY);
                angle = fabsf2(diff);
                if(angle < 20) {
                    koopa->step++;
                }
            } else if(koopa->step == 2) {
                koopa->time += 1;
                MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
                PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
                if(koopa->time >= koopa->maxTime) {
                    koopa->mode++;
                    koopa->step = 0;
                }
            }
            break;

        case 12:
            koopa->mode = -1;
            break;
    }
    if(redF && MBMasuTypeGet(MASU_LAYER_DEFAULT, koopa->masuId) == MASU_TYPE_BLUE) {
        MBMasuTypeSet(MASU_LAYER_DEFAULT, koopa->masuId, MASU_TYPE_RED);
        MB7Ev_MasuRedSet(koopa->masuId);
        MBAudFXPlay(843);
        coinMdlId = mb7_Work.objMdlId[10];
        MBModelPosSetV(coinMdlId, &masu->pos);
        MBModelDispSet(coinMdlId, TRUE);
        MBMotionTimeSet(coinMdlId, 0);
        MBMotionSpeedSet(coinMdlId, 1);
    }
    MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
    MBModelRotSetV(koopa->mdlId[0], &koopa->rot);
    if(nextF && masu) {
        if(koopa->focusF) {
            koopa->mode = 5;
            koopa->step = 0;
            koopa->focusF = 0;
        } else {
            koopa->focusF = koopa->focusNextF;
            koopa->focusNextF = 0;
            if(koopa->focusF == 0) {
                MBCameraFocusMasuSet(-1);
                MBCameraFocusSet(koopa->mdlId[0]);
            } else {
                MBCameraFocusSet(-1);
                MBCameraFocusMasuSet(koopa->masuId);
            }
            if(prevMasu && (masu->flag & MB7EV_KOOPAWALK_FLAG)) {
                koopa->mode = 10;
                koopa->step = 0;
            } else {
                koopa->prevMasuId = koopa->masuId;
                prevMasu = masu;
                num = 0;
                do {
                    linkMasu = masu;
                    num++;
                    for(i=0; i<linkMasu->linkNum; i++) {
                        koopa->masuId = linkMasu->linkTbl[i];
                        masu = MBMasuGet(MASU_LAYER_DEFAULT, koopa->masuId);
                        if(masu->flag & MB7EV_RED_LINK_FLAG) {
                            break;
                        }
                    }
                } while((masu->flag & MASU_FLAG_CLIMBFROM) || (masu->flag & MASU_FLAG_CLIMBTO));
                for(i=0; i<GW_PLAYER_MAX; i++) {
                    if(koopa->masuId == GwPlayer[i].masuId) {
                        num = 2;
                        koopa->focusNextF = 1;
                    }
                }
                if(num > 1) {
                    koopa->mode = 3;
                    koopa->turnF = 1;
                } else if((prevMasu->flag & MASU_FLAG_JUMPFROM) && (masu->flag & MASU_FLAG_JUMPTO)) {
                    koopa->mode = 4;
                    koopa->turnF = 1;
                } else if((prevMasu->flag & MASU_FLAG_CLIMBFROM) && (masu->flag & MASU_FLAG_CLIMBTO)) {
                    koopa->mode = 3;
                    koopa->turnF = 1;
                } else {
                    koopa->mode = 2;
                }
                koopa->step = 0;
            }
        }
    }
}

/* 186 instructions */
static void MB7Ev_KoopaWalkPlayerUpdate(void)
{
    MB7EV_KOOPA *koopa;
    MB7EV_PLAYER *player;
    int i;
    HUPROCESS *process;
    HuVecF dir;

    koopa = &mb7_Work.koopa;
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        switch(player->mode) {
            case 0:
                player->masuId = GwPlayer[i].masuId;
                MBPlayerPosGet(i, &player->pos);
                MBPlayerRotGet(i, &player->rot);
                player->unk04 = -1;
                player->mode++;
                break;

            case 1:
                if(koopa->masuId == player->masuId && koopa->landF != 0) {
                    player->step = 0;
                    player->mode++;
                }
                break;

            case 2:
                if(player->step == 0) {
                    omVibrate(i, 12, 4, 2);
                    MBPlayerMotionNoSet(i, 10, HU3D_MOTATTR_NONE);
                    player->step++;
                } else if(player->step == 1) {
                    if(MBPlayerMotionTimeGet(i) > 30) {
                        MBPlayerMotionSpeedSet(i, 0);
                        player->mode++;
                        player->step = 0;
                    }
                }
                break;

            case 3:
                if(player->step == 0) {
                    PSVECSubtract(&koopa->pos, &player->pos, &dir);
                    dir.y = 0.01f;
                    if(PSVECMag(&dir) > 150) {
                        MBPlayerMotionSpeedSet(i, 1);
                        process = MBPrcCreate(MB7Ev_KoopaWalkCoinLose, 8205, 0x4000);
                        process->property = (void *)i;
                        player->step++;
                    }
                } else if(player->step == 1) {
                    if(MBPlayerMotionEndCheck(i)) {
                        player->mode++;
                        MBPlayerMotionNoShiftSet(i, 6, 0, 8, HU3D_MOTATTR_LOOP);
                    }
                }
                break;

            case 4:
                break;

            case -1:
                MBPlayerMotionNoSet(i, 1, HU3D_MOTATTR_LOOP);
                player->motId = -1;
                player->rot.y = 0;
                break;
        }
        MBPlayerPosSetV(i, &player->pos);
        MBPlayerRotSetV(i, &player->rot);
    }
}

/* 27 instructions */
static void MB7Ev_KoopaWalkCoinLose(void)
{
    MB7EV_KOOPA *koopa;
    HUPROCESS *process;

    process = HuPrcCurrentGet();
    koopa = &mb7_Work.koopa;

    koopa->coinLoseF = 1;
    MBCoinAddDispExec((int)process->property, -10, TRUE);
    process->property = NULL;
    koopa->coinLoseF = 0;
    HuPrcEnd();
}

/* 29 instructions -- deliberately OUTSIDE the dont_inline block: the reference
   inlines this at both of MB7Ev_Dokan's call sites and still emits a
   standalone copy. */
static void MB7Ev_KoopaWalkDustCreate(int no)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    MBEFFECT *effP;

    Hu3DModelPosSetV(koopa->effMdlId, &koopa->pos);
    effP = Hu3DData[koopa->effMdlId].hookData;
    effP->mode = no+1;
}

/* 639 instructions */
static void MB7_EffDustHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;
    HuVecF vec;
    float angle;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            data->parManId = 0;
        }
        effP->mode = 0;
        effP->count = 1;
        return;
    }
    if(effP->mode != 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->parManId = effP->mode-1;
            data->time = 60*(0.7f+(0.4f*MBEffRandF()));
            angle = 360*MBEffRandF();
            vec.x = HuSin(angle);
            vec.z = HuCos(angle);
            vec.y = 0;
            if(data->parManId == 0) {
                PSVECScale(&vec, &data->pos, 100*(0.7f*(0.5f+(0.5f*MBEffRandF()))));
                data->pos.y = 20+(20*MBEffRandF());
                PSVECScale(&vec, &data->vel, 1.6666666f*(15*(0.7f+(0.3f*MBEffRandF()))));
                data->vel.y = 1.6666666f*(0.7f*(0.4f+(0.6f*MBEffRandF())));
                data->scale = 30+(20*MBEffRandF());
                data->color.a = 50+(60*MBEffRandF());
            } else if(data->parManId == 1) {
                PSVECScale(&vec, &data->pos, 100*(0.7f*(0.5f+(0.5f*MBEffRandF()))));
                data->pos.y = 20+(20*MBEffRandF());
                PSVECScale(&vec, &data->vel, 1.6666666f*(9*(0.7f+(0.3f*MBEffRandF()))));
                data->vel.y = 1.6666666f*(1.2f*(0.4f+(0.6f*MBEffRandF())));
                data->scale = 30+(20*MBEffRandF());
                data->color.a = 40+(30*MBEffRandF());
            }
            data->rot.z = 360*MBEffRandF();
            angle = 0.3f+(0.7f*MBEffRandF());
            data->color.r = mb7ev_DustColTbl[0].x+(mb7ev_DustColTbl[0].x*angle);
            data->color.g = mb7ev_DustColTbl[0].y+(mb7ev_DustColTbl[0].y*angle);
            data->color.b = mb7ev_DustColTbl[0].z+(mb7ev_DustColTbl[0].z*angle);
        }
        effP->mode = 0;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        if(data->parManId == 0) {
            data->vel.x *= 0.84f;
            data->vel.z *= 0.84f;
        } else if(data->parManId == 1) {
            data->vel.x *= 0.88f;
            data->vel.z *= 0.88f;
        }
        data->time--;
        if(data->time <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        } else if(data->time < 16 && data->color.a >= 5) {
            data->color.a -= 5;
        }
        if(data->color.a >= 2) {
            data->color.a -= 2;
        }
        data->scale += 3.0f;
    }
}

/* 420 instructions */
static void MB7Ev_Dokan(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MB7EV_PLAYER *dokan;
    int destMasuId;
    int i;
    int masuId;
    MASU *masu;
    u32 findFlag;
    u32 flag;
    HuVecF rot;
    HuVecF hookPos;
    HuVecF pos;

    koopa = &mb7_Work.koopa;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    MBPlayerMotIdleSet(playerNo);
    MB7Ev_KoopaInit();
    findFlag = MASU_FLAG_BIT(12);
    if(flag & MASU_FLAG_BIT(11)) {
        findFlag = MASU_FLAG_BIT(10);
    }
    destMasuId = MBMasuFlagFind(MASU_LAYER_DEFAULT, findFlag, findFlag);
    Hu3DModelObjPosGet(MBModelIdGet(mb7_MainMdlId), mb7ev_GuruPosHookName, &hookPos);
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    dokan = &mb7_Work.player[0];
    MBPlayerPosGet(playerNo, &dokan->pos);
    MBPlayerRotGet(playerNo, &dokan->rot);
    dokan->motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_434);
    MBCameraFocusPlayerSet(-1);
    MB7Ev_DokanSet(playerNo, masuId, TRUE);
    MBPlayerMotionNoShiftSet(playerNo, dokan->motId, 0, 8, HU3D_MOTATTR_NONE);
    MB7Ev_DokanPlayerSet(playerNo, masuId, FALSE);
    MBPlayerMotionKill(playerNo, dokan->motId);
    MB7Ev_DokanSet(playerNo, masuId, FALSE);
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LAUGH);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_STOMP);
    MB7Ev_KoopaDataClose();
    koopa->effMdlId = MBEffCreate(mb7_Work.effAnim8C, 128);
    MBEffHookSet(koopa->effMdlId, MB7_EffDustHook);
    Hu3DModelLayerSet(koopa->effMdlId, 2);
    masu = MBMasuGet(MASU_LAYER_DEFAULT, destMasuId);
    GwPlayer[playerNo].masuId = destMasuId;
    MBPlayerPosFixPlayer(playerNo, destMasuId, TRUE);
    MBPlayerPosReset(playerNo);
    dokan->rot.y = 0;
    MBPlayerPosGet(playerNo, &dokan->pos);
    MBPlayerRotSetV(playerNo, &dokan->rot);
    MBPlayerMotIdleSet(playerNo);
    MBCameraFocusMasuSet(destMasuId);
    MB7Ev_DokanSet(playerNo, destMasuId, TRUE);
    MB7Ev_DokanPlayerSet(playerNo, destMasuId, TRUE);
    MB7Ev_DokanSet(playerNo, destMasuId, FALSE);
    koopa->pos = hookPos;
    koopa->rot.y = 180.0 * (atan2(dokan->pos.x - koopa->pos.x,
                                  dokan->pos.z - koopa->pos.z) / M_PI);
    MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
    MBModelRotSetV(koopa->mdlId[0], &koopa->rot);
    MBModelDispSet(koopa->mdlId[0], TRUE);
    MB7Ev_KoopaMotionNoSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    MBMotionTimeSet(koopa->mdlId[0], 100);
    koopa->pos.y += 1000;
    koopa->vel.y = 0;
    while(hookPos.y < koopa->pos.y) {
        koopa->vel.y += -0.5444445f;
        PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
        if(hookPos.y > koopa->pos.y) {
            koopa->pos.y = hookPos.y;
        }
        MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
        HuPrcVSleep();
    }
    MB7Ev_KoopaWalkDustCreate(0);
    MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
    dokan->angleY = 180.0 * (atan2(koopa->pos.x - dokan->pos.x,
                                   koopa->pos.z - dokan->pos.z) / M_PI);
    MBCameraQuakeSet(18, 200);
    MBAudFXPlay(873);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        MBAngleMoveTo(&dokan->rot.y, dokan->angleY, 0.15f);
        MBPlayerRotSetV(playerNo, &dokan->rot);
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    MBCameraFocusMasuSet(-1);
    PSVECSubtract(&koopa->pos, &dokan->pos, &pos);
    PSVECScale(&pos, &pos, 0.5f);
    PSVECAdd(&dokan->pos, &pos, &pos);
    pos.y += 100;
    MBCameraPosViewSet(&pos, NULL, NULL, 2500, -1, 60);
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    MBAudFXPlay(713);
    MBWinCreate(2, MESS_BOARD_W07_DOKAN, 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    koopa->vel.y = 16.666666f;
    for(i=0; i<100; i++) {
        if(i == 65) {
            MBCameraQuakeSet(18, 50);
            MB7Ev_KoopaWalkDustCreate(1);
            MBAudFXPlay(716);
        }
        if(i > 70) {
            koopa->vel.y += -0.27222225f;
            PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
            MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
        }
        HuPrcVSleep();
    }
    MBMotionSpeedSet(koopa->mdlId[0], 0);
    MBEffKill(koopa->effMdlId);
    koopa->effMdlId = -1;
    MB7Ev_KoopaClose();
}

/* 146 instructions */
static void MB7Ev_DokanSet(int playerNo, int masuId, BOOL inF)
{
    MB7EV_PLAYER *dokan;
    MASU *masu;
    int i;
    int mdlId;
    float scale;
    float time;
    float height;
    float ofsY;
    HuVecF pos;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    dokan = &mb7_Work.player[0];
    mdlId = mb7_Work.objMdlId[8];
    height = 100;
    MBModelDispSet(mdlId, TRUE);
    pos = masu->pos;
    if(inF) {
        pos.y -= height;
    }
    time = 30;
    if(inF) {
        time = 45;
    }
    if(inF) {
        MBAudFXPlay(1560);
    }
    for(i=0; i<time; i++) {
        scale = (0.4f*i)/time;
        ofsY = height/time;
        if(inF) {
            pos.y += ofsY;
            scale += 0.8f;
        } else {
            pos.y -= ofsY;
            scale = 1.2f-scale;
        }
        MBModelPosSetV(mdlId, &pos);
        MBModelScaleSet(mdlId, scale, 1, scale);
        dokan->pos.y = pos.y+height;
        MBPlayerPosSetV(playerNo, &dokan->pos);
        HuPrcVSleep();
    }
    if(!inF) {
        MBModelDispSet(mdlId, FALSE);
        dokan->pos = masu->pos;
        MBPlayerPosSetV(playerNo, &dokan->pos);
    }
}

/* 113 instructions */
static void MB7Ev_DokanPlayerSet(int playerNo, int masuId, BOOL inF)
{
    MB7EV_PLAYER *dokan;
    int i;
    MASU *masu;
    float t;
    float scale;
    float time;
    float masuY;
    float posY;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    dokan = &mb7_Work.player[0];
    masuY = masu->pos.y;
    posY = dokan->pos.y;
    time = 45;
    if(inF) {
        MBModelDispSet(MBPlayerModelGet(playerNo), TRUE);
        time = 30;
    } else {
        MBAudFXPlay(1561);
    }
    for(i=0; i<=time; i++) {
        t = i*(1.0f/time);
        if(!inF) {
            t = 1-t;
        }
        scale = t*t;
        dokan->pos.y = masuY+(t*(posY-masuY));
        MBPlayerPosSetV(playerNo, &dokan->pos);
        MBPlayerScaleSet(playerNo, scale, scale, scale);
        HuPrcVSleep();
    }
    if(!inF) {
        MBModelDispSet(MBPlayerModelGet(playerNo), FALSE);
    }
}

/* 585 instructions */
static void MB7Ev_DokanIn(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MB7EV_PLAYER *dokan;
    int destMasuId;
    int i;
    int masuId;
    MASU *masu;
    u32 findFlag;
    u32 flag;
    HuVecF rot;
    HuVecF hookPos;
    HuVecF pos;

    koopa = &mb7_Work.koopa;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    MBPlayerMotIdleSet(playerNo);
    MB7Ev_KoopaInit();
    findFlag = MASU_FLAG_BIT(13);
    if(flag & MASU_FLAG_BIT(10)) {
        findFlag = MASU_FLAG_BIT(11);
    }
    destMasuId = MBMasuFlagFind(MASU_LAYER_DEFAULT, findFlag, findFlag);
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LOSE);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_STOMP);
    MB7Ev_KoopaDataClose();
    koopa->effMdlId = MBEffCreate(mb7_Work.effAnim8C, 128);
    MBEffHookSet(koopa->effMdlId, MB7_EffDustHook);
    Hu3DModelLayerSet(koopa->effMdlId, 2);
    Hu3DModelObjPosGet(MBModelIdGet(mb7_MainMdlId), mb7ev_GuruPosHookName, &hookPos);
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    dokan = &mb7_Work.player[0];
    MBPlayerPosGet(playerNo, &dokan->pos);
    MBPlayerRotGet(playerNo, &dokan->rot);
    dokan->motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_434);
    koopa->pos = hookPos;
    koopa->rot.y = 180.0 * (atan2(dokan->pos.x - koopa->pos.x,
                                  dokan->pos.z - koopa->pos.z) / M_PI);
    MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
    MBModelRotSetV(koopa->mdlId[0], &koopa->rot);
    MBModelDispSet(koopa->mdlId[0], TRUE);
    MB7Ev_KoopaMotionNoSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    MBMotionTimeSet(koopa->mdlId[0], 100);
    koopa->pos.y += 1000;
    koopa->vel.y = 0;
    while(hookPos.y < koopa->pos.y) {
        koopa->vel.y += -0.5444445f;
        PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
        if(hookPos.y > koopa->pos.y) {
            koopa->pos.y = hookPos.y;
        }
        MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
        HuPrcVSleep();
    }
    MB7Ev_KoopaWalkDustCreate(0);
    MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
    dokan->angleY = 180.0 * (atan2(koopa->pos.x - dokan->pos.x,
                                   koopa->pos.z - dokan->pos.z) / M_PI);
    MBCameraQuakeSet(18, 200);
    MBAudFXPlay(873);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        MBAngleMoveTo(&dokan->rot.y, dokan->angleY, 0.15f);
        MBPlayerRotSetV(playerNo, &dokan->rot);
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    MBCameraFocusPlayerSet(-1);
    PSVECSubtract(&koopa->pos, &dokan->pos, &pos);
    PSVECScale(&pos, &pos, 0.5f);
    PSVECAdd(&dokan->pos, &pos, &pos);
    pos.y += 100;
    MBCameraPosViewSet(&pos, NULL, NULL, 2500, -1, 30);
    MB7Ev_KoopaMotionNoSet(MB7EV_KOOPAMOT_LOSE, FALSE);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    MBAudFXPlay(714);
    MBWinCreate(2, MESS_BOARD_W07_DOKANIN, 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    koopa->vel.y = 16.666666f;
    for(i=0; i<100; i++) {
        if(i == 65) {
            MBCameraQuakeSet(18, 50);
            MB7Ev_KoopaWalkDustCreate(1);
            MBAudFXPlay(716);
        }
        if(i > 70) {
            koopa->vel.y += -0.27222225f;
            PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
            MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
        }
        HuPrcVSleep();
    }
    MBMotionSpeedSet(koopa->mdlId[0], 0);
    MBCameraFocusPlayerSet(-1);
    MB7Ev_DokanSet(playerNo, masuId, TRUE);
    MBPlayerMotionNoShiftSet(playerNo, dokan->motId, 0, 8, HU3D_MOTATTR_NONE);
    MB7Ev_DokanPlayerSet(playerNo, masuId, FALSE);
    MBPlayerMotionKill(playerNo, dokan->motId);
    MB7Ev_DokanSet(playerNo, masuId, FALSE);
    masu = MBMasuGet(MASU_LAYER_DEFAULT, destMasuId);
    GwPlayer[playerNo].masuId = destMasuId;
    MBPlayerPosFixPlayer(playerNo, destMasuId, TRUE);
    MBPlayerPosReset(playerNo);
    dokan->rot.y = 0;
    MBPlayerPosGet(playerNo, &dokan->pos);
    MBPlayerRotSetV(playerNo, &dokan->rot);
    MBPlayerMotIdleSet(playerNo);
    MBCameraFocusMasuSet(destMasuId);
    MB7Ev_DokanSet(playerNo, destMasuId, TRUE);
    MB7Ev_DokanPlayerSet(playerNo, destMasuId, TRUE);
    MB7Ev_DokanSet(playerNo, destMasuId, FALSE);
    MBEffKill(koopa->effMdlId);
    koopa->effMdlId = -1;
    MB7Ev_KoopaClose();
}

/* 1357 instructions */
static void MB7Ev_KoopaCube(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MB7EV_PLAYER *player;
    MASU *masu;
    MASU *linkMasu;
    int masuId;
    int cubeMasuId;
    int no;
    int i;
    int j;
    int choice;
    int mdlId;
    int cubeMdlId;
    int dustEff;
    int seId;
    int hideMdlId;
    float t;
    HuVecF dummy;
    HuVecF cameraRot;
    HuVecF cameraPos;
    HuVecF pos;
    HuVecF vel;

    koopa = &mb7_Work.koopa;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    cubeMasuId = -1;
    for(i=0; i<masu->linkNum; i++) {
        linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, masu->linkTbl[i]);
        if(linkMasu->flag & MB7EV_KOOPACUBE_LINK_FLAG) {
            cubeMasuId = masu->linkTbl[i];
            break;
        }
    }
    if(cubeMasuId < 0) {
        return;
    }
    no = 0;
    if(linkMasu->pos.x >= 0) {
        no = 1;
    }
    MB7Ev_KoopaInit();
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    player = &mb7_Work.player[0];
    MBPlayerPosGet(playerNo, &player->pos);
    MBPlayerRotGet(playerNo, &player->rot);
    MBPlayerMotionNoShiftSet(playerNo, 2, 0, 8, HU3D_MOTATTR_LOOP);
    player->angleY = 180.0 * (atan2(linkMasu->pos.x - player->pos.x,
                                    linkMasu->pos.z - player->pos.z) / M_PI);
    for(i=0; i<30.0f; i++) {
        MBAngleMoveTo(&player->rot.y, player->angleY, 0.15f);
        MBPlayerRotSetV(playerNo, &player->rot);
        HuPrcVSleep();
    }
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LAUGH);
    MB7Ev_KoopaDataClose();
    PSVECSubtract(&linkMasu->pos, &player->pos, &player->vel);
    player->maxTime = 0.060000002f*PSVECMag(&player->vel);
    PSVECScale(&player->vel, &player->vel, 1/player->maxTime);
    player->rot.y = player->angleY;
    MBPlayerMotionNoShiftSet(playerNo, 3, 0, 8, HU3D_MOTATTR_LOOP);
    MBPlayerPosFixPlayer(playerNo, cubeMasuId, FALSE);
    for(i=0; i<player->maxTime; i++) {
        PSVECAdd(&player->pos, &player->vel, &player->pos);
        MBPlayerPosSetV(playerNo, &player->pos);
        MBPlayerRotSetV(playerNo, &player->rot);
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    mdlId = mb7_Work.objMdlId[7];
    MBMotionSpeedSet(mdlId, 1);
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBModelDispSet(mdlId, TRUE);
    MBModelHookSet(mdlId, mb7ev_HikouPosHookName, koopa->mdlId[0]);
    koopa->pos = mb7ev_KoopaAsibaPosTbl[no];
    koopa->pos.y += 500;
    koopa->maxTime = 120;
    koopa->vel.y = -1000/koopa->maxTime;
    koopa->rot.y = koopa->angleY = 180+player->angleY;
    MBModelDispSet(koopa->mdlId[0], TRUE);
    MBCameraFocusPlayerSet(-1);
    PSVECSubtract(&mb7ev_KoopaAsibaPosTbl[no], &player->pos, &cameraPos);
    PSVECScale(&cameraPos, &cameraPos, 0.75f);
    PSVECAdd(&player->pos, &cameraPos, &cameraPos);
    cameraPos.y -= 350;
    MBCameraPosViewSet(&cameraPos, NULL, NULL, 3000, -1, 120);
    MBCameraRotGet(&cameraRot);
    for(i=0; i<koopa->maxTime; i++) {
        if(i > 0.7f*koopa->maxTime) {
            koopa->vel.y *= 0.9f;
        }
        MB7Ev_KoopaAsibaUpdate();
        HuPrcVSleep();
    }
    koopa->vel.y = 0;
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
    MBAudFXPlay(713);
    MBWinCreate(2, MESS_BOARD_W07_KOOPACUBE_BEGIN, 7);
    MBTopWinWait();
    MBTopWinKill();
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    HuPrcVSleep();
    HuPrcVSleep();
    for(i=0; i<2; i++) {
        cubeMdlId = mb7_Work.objMdlId[i+4];
        MBModelDispSet(cubeMdlId, TRUE);
        MBModelPosSetV(cubeMdlId, &mb7ev_KoopaCubePosTbl[no][i]);
        MBModelRotSet(cubeMdlId, 0, player->angleY, 0);
    }
    MBAudFXPlay(1568);
    for(i=0; i<=16; i++) {
        t = sin(M_PI*(90*(0.0625f*i))/180);
        for(j=0; j<2; j++) {
            MBModelScaleSet(mb7_Work.objMdlId[j+4], t, t, t);
        }
        HuPrcVSleep();
    }
    MBWinCreateChoice(2, MESS_BOARD_W07_KOOPACUBE_CHOICE, 7, 0);
    if(GwPlayer[playerNo].comF) {
        if(0.000030517578f*(frand() & 0xFFFF)-1 >= 0) {
            MBComChoiceSetUp();
        } else {
            MBComChoiceSetDown();
        }
    }
    MBTopWinWait();
    choice = MBWinLastChoiceGet() & 1;
    MBTopWinKill();
    pos = player->pos;
    pos.y += 275;
    PSVECSubtract(&pos, &mb7ev_KoopaCubePosTbl[no][choice], &vel);
    PSVECScale(&vel, &vel, 0.033333335f);
    pos = mb7ev_KoopaCubePosTbl[no][choice];
    MBModelDispSet(mb7_Work.objMdlId[5-choice], FALSE);
    dustEff = MB7Ev_KoopaCubeDustCreate(&mb7ev_KoopaCubePosTbl[no][1-choice], 1-choice);
    MBAudFXPlay(1569);
    for(i=0; i<30.0f; i++) {
        PSVECAdd(&pos, &vel, &pos);
        MBModelPosSetV(mb7_Work.objMdlId[choice+4], &pos);
        HuPrcVSleep();
    }
    MBEffKill(dustEff);
    MBPlayerMotionNoShiftSet(playerNo, 2, 0, 8, HU3D_MOTATTR_LOOP);
    for(i=0; i<30.0f; i++) {
        MBAngleMoveTo(&player->rot.y, cameraRot.y, 0.15f);
        MBPlayerRotSetV(playerNo, &player->rot);
        MB7Ev_KoopaAsibaUpdate();
        HuPrcVSleep();
    }
    koopa->angleY = koopa->rot.y;
    MBPlayerMotionNoSet(playerNo, 11, HU3D_MOTATTR_NONE);
    j = 0;
    for(i=0; i<42; i++) {
        if(i >= 27) {
            if(i == 27) {
                MBAudFXPlay(814);
            }
            j++;
            t = sin(M_PI*(12.0f*j)/180);
            vel = pos;
            vel.y += 100*t;
            MBModelPosSetV(mb7_Work.objMdlId[choice+4], &vel);
            MBModelScaleSet(mb7_Work.objMdlId[choice+4], 1+0.5f*t, 1-0.5f*t, 1+0.5f*t);
        }
        HuPrcVSleep();
    }
    while(!MBPlayerMotionEndCheck(playerNo)) {
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    for(i=0; i<2; i++) {
        hideMdlId = mb7_Work.objMdlId[i+4];
        MBModelDispSet(hideMdlId, FALSE);
    }
    dustEff = MB7Ev_KoopaCubeDustCreate(&pos, choice);
    MBCameraQuakeSet(60, 50);
    seId = MBAudFXPlay(1562);
    for(i=0; i<60; i++) {
        if(i == 30) {
            MBAudFXStop(seId);
        }
        HuPrcVSleep();
    }
    MBEffKill(dustEff);
    if(0.000030517578f*(frand() & 0xFFFF)-1 >= 0) {
        mdlId = mb7_Work.objMdlId[6];
        MBModelPosSetV(mdlId, &player->pos);
        MBMotionTimeSet(mdlId, 0);
        MBMotionSpeedSet(mdlId, 1);
        MBModelDispSet(mdlId, TRUE);
        MBAudFXPlay(1564);
        MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
        i = 0;
        while(!MBPlayerMotionEndCheck(playerNo)) {
            i++;
            if(i == 10) {
                omVibrate(playerNo, 12, 6, 6);
                WipeColorSet(255, 255, 255);
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 54);
            }
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 6, 0, 8, HU3D_MOTATTR_LOOP);
        while(!MBMotionEndCheck(mdlId)) {
            HuPrcVSleep();
        }
        MBModelDispSet(mdlId, FALSE);
        MBCoinAddDispExec(playerNo, -(MBPlayerCoinGet(playerNo) >> 1), TRUE);
    } else {
        mdlId = mb7_Work.objMdlId[3];
        MBMotionTimeSet(mdlId, 0);
        MBMotionSpeedSet(mdlId, 1);
        player->motId = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_376);
        MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
        player->vel.x = player->vel.y = player->vel.z = 0;
        for(i=0; i<10; i++) {
            if((i & 3) == 0) {
                MBAudFXPlay(1563);
            }
            HuPrcVSleep();
        }
        for(i=0; i<60.0f; i++) {
            if(((i+10) & 3) == 0 && i < 20) {
                MBAudFXPlay(1563);
            }
            if(i == 15) {
                MBPlayerMotionNoShiftSet(playerNo, player->motId, 0, 8, HU3D_MOTATTR_NONE);
            } else if(i == 30) {
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
            }
            if((i & 15) == 0) {
                omVibrate(playerNo, 12, 6, 6);
            }
            player->vel.y -= 0.5444445f;
            PSVECAdd(&player->pos, &player->vel, &player->pos);
            MBPlayerPosSetV(playerNo, &player->pos);
            MBCameraPosTargetGet(&cameraPos);
            cameraPos.y += player->vel.y;
            MBCameraPosTargetSetV(&cameraPos);
            HuPrcVSleep();
        }
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        masuId = MBMasuFlagFind(MASU_LAYER_DEFAULT, MASU_FLAG_START, MASU_FLAG_START);
        masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        MBPlayerPosFixPlayer(playerNo, masuId, TRUE);
        GwPlayer[playerNo].masuId = masuId;
        MBPlayerPosReset(playerNo);
        MBPlayerMotionNoSet(playerNo, 6, HU3D_MOTATTR_LOOP);
        MBPlayerRotSet(playerNo, 0, 0, 0);
        MBPlayerPosGet(playerNo, &player->pos);
        for(i=0; i<GW_PLAYER_MAX; i++) {
            if(i != playerNo) {
                MBModelDispSet(MBPlayerModelGet(i), FALSE);
            }
        }
        MBCameraSkipSet(FALSE);
        MBCameraFocusPlayerSet(-1);
        cameraPos = player->pos;
        cameraPos.y += 150;
        MBCameraPosViewSet(&cameraPos, NULL, NULL, 2500, -1, 1);
        for(i=0; i<10; i++) {
            HuPrcVSleep();
        }
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
        MBMotionTimeSet(mdlId, 0);
        MBMotionSpeedSet(mdlId, 0);
        MBPlayerMotionKill(playerNo, player->motId);
        player->motId = -1;
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        koopa->pos = masu->pos;
        koopa->pos.y += 1000;
        koopa->pos.z -= 400;
        koopa->maxTime = 120;
        koopa->vel.y = -1000/koopa->maxTime;
        koopa->rot.y = koopa->angleY = 0;
        for(i=0; i<koopa->maxTime; i++) {
            if(i > 0.7f*koopa->maxTime) {
                koopa->vel.y *= 0.9f;
            }
            MB7Ev_KoopaAsibaUpdate();
            HuPrcVSleep();
        }
        koopa->vel.y = 0;
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
    MBAudFXPlay(713);
    MBWinCreate(2, MESS_BOARD_W07_KOOPACUBE_END, 7);
    MBTopWinWait();
    MBTopWinKill();
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    koopa->maxTime = 120;
    koopa->vel.y = 0;
    for(i=0; i<koopa->maxTime; i++) {
        if(koopa->vel.y < 11.666666f) {
            koopa->vel.y += 0.2777778f;
        }
        MB7Ev_KoopaAsibaUpdate();
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    MBModelHookReset(mb7_Work.objMdlId[7]);
    MB7Ev_KoopaClose();
    MBModelDispSet(mb7_Work.objMdlId[7], FALSE);
    for(i=0; i<GW_PLAYER_MAX; i++) {
        MBModelDispSet(MBPlayerModelGet(i), TRUE);
    }
    MBPlayerPosFixPlayer(playerNo, masuId, TRUE);
    GwPlayer[playerNo].masuId = masuId;
    MBPlayerPosReset(playerNo);
    MBPlayerMotionNoSet(playerNo, 1, HU3D_MOTATTR_LOOP);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    MBCameraFocusMasuSet(masuId);
    MBCameraSkipSet(FALSE);
    MBCameraZoomSet(2000);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
}

/* 60 instructions */
static void MB7Ev_KoopaAsibaUpdate(void)
{
    MB7EV_KOOPA *koopa;
    int mdlId;

    mdlId = mb7_Work.objMdlId[7];
    koopa = &mb7_Work.koopa;
    MBModelDispSet(mdlId, TRUE);
    MBAngleMoveTo(&koopa->rot.y, koopa->angleY, 0.15f);
    PSVECAdd(&koopa->pos, &koopa->vel, &koopa->pos);
    MBModelPosSetV(mdlId, &koopa->pos);
    MBModelRotSetV(mdlId, &koopa->rot);
    MBModelPosSet(koopa->mdlId[0], 0, 0, 0);
    MBModelRotSet(koopa->mdlId[0], 0, 0, 0);
}

/* 38 instructions */
static HU3DMODELID MB7Ev_KoopaCubeDustCreate(HuVecF *pos, int mode)
{
    int mdlId;
    MBEFFECT *effP;

    mdlId = MBEffCreate(mb7_Work.effAnim8C, 64);
    MBEffHookSet(mdlId, MB7Ev_KoopaCubeDustEffHook);
    Hu3DModelLayerSet(mdlId, 2);
    Hu3DModelPosSetV(mdlId, pos);
    effP = Hu3DData[mdlId].hookData;
    effP->mode = mode;
    return mdlId;
}

/* 446 instructions */
static void MB7Ev_KoopaCubeDustEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;
    HuVecF vec;
    float angle;
    float rate;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->time = 1;
            data->parManId = 60*(0.4f+(0.3f*MBEffRandF()));
            angle = 360*MBEffSRandF();
            vec.x = HuSin(angle);
            vec.z = HuCos(angle);
            vec.y = 1+HuSin(360*MBEffRandF());
            if(vec.y > 1.0f) {
                vec.y -= 2.0f;
            }
            rate = 0.5f+(0.5f*vec.y);
            rate *= 0.7f;
            PSVECScale(&vec, &data->pos, 100*(0.5f*(0.5f+(0.5f*MBEffRandF()))));
            PSVECScale(&vec, &data->vel, 1.6666666f*(1.5f*(0.7f+(0.3f*MBEffRandF()))));
            data->rot.z = 360*MBEffRandF();
            data->scale = 60+(60*MBEffRandF());
            data->color.a = 50+(80*MBEffRandF());
            angle = (0.7f*rate)+(0.3f*MBEffRandF());
            data->color.r = mb7ev_KoopaCubeDustColTbl[effP->mode*2].x+(angle*mb7ev_KoopaCubeDustColTbl[(effP->mode*2)+1].x);
            data->color.g = mb7ev_KoopaCubeDustColTbl[effP->mode*2].y+(angle*mb7ev_KoopaCubeDustColTbl[(effP->mode*2)+1].y);
            data->color.b = mb7ev_KoopaCubeDustColTbl[effP->mode*2].z+(angle*mb7ev_KoopaCubeDustColTbl[(effP->mode*2)+1].z);
        }
        effP->count = 1;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.27222225f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        } else if(data->parManId < 10 && data->color.a >= 10) {
            data->color.a -= 10;
        }
        if(data->color.a >= 10) {
            data->color.a -= 2;
        }
        data->scale += 4.0f;
    }
}

/* 983 instructions */
static void MB7Ev_Hou(int playerNo)
{
    MB7EV_KOOPA *koopa;
    MB7EV_HOU *hou;
    MB7EV_PLAYER *player;
    MASU *masu;
    int emitter;
    int mdlId;
    int i;
    int masuId;
    BOOL endF;
    u32 flag;
    HuVecF pos;
    HuVecF fxPos;
    HuVecF cameraPos;
    HuVecF rot;

    koopa = &mb7_Work.koopa;
    hou = &mb7_Work.hou;
    emitter = -1;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    MB7Ev_KoopaInit();
    MBCameraFocusPlayerSet(-1);
    MBCameraPlayerViewSet(playerNo, NULL, NULL, 1500, -1, 30);
    MBPlayerMotionNoShiftSet(playerNo, 2, 0, 8, HU3D_MOTATTR_LOOP);
    for(i=0; i<30.0f; i++) {
        MBPlayerRotGet(playerNo, &rot);
        MBAngleMoveTo(&rot.y, 0, 0.15f);
        MBPlayerRotSetV(playerNo, &rot);
        HuPrcVSleep();
    }
    memset(&mb7_Work.player[0], 0, sizeof(mb7_Work.player));
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        masuId = GwPlayer[i].masuId;
        masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        if(masu->flag & MB7EV_HOU_FLAG) {
            player->enableF = 1;
            player->masuId = masuId;
        }
    }
    MB7Ev_HouPlayerUpdate();
    MB7Ev_KoopaCreate();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_LAUGH);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_STOMP);
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_HOLD);
    MB7Ev_KoopaDataClose();
    MBPlayerMotionNoSet(playerNo, 9, HU3D_MOTATTR_NONE);
    MBCameraQuakeSet(18, 200);
    MBAudFXPlay(873);
    for(i=0; i<18.0f; i++) {
        HuPrcVSleep();
    }
    MBPlayerMotIdleSet(playerNo);
    memset(hou, 0, sizeof(MB7EV_HOU));
    mdlId = mb7_Work.objMdlId[2];
    Hu3DModelObjPosGet(MBModelIdGet(mdlId), mb7ev_KupaPosHookName, &pos);
    Hu3DModelObjPosGet(MBModelIdGet(mdlId), mb7ev_FirePosHookName, &hou->firePos);
    hou->pos = pos;
    MBMotionSpeedSet(mb7_Work.objMdlId[9], 1);
    MBModelAttrSet(mb7_Work.objMdlId[9], HU3D_MOTATTR_LOOP);
    koopa->pos = pos;
    koopa->pos.z -= 120.00001f;
    MBModelPosSetV(koopa->mdlId[0], &koopa->pos);
    MBModelDispSet(koopa->mdlId[0], TRUE);
    MBCameraFocusPlayerSet(-1);
    cameraPos = pos;
    cameraPos.z += 500;
    MBCameraPosViewSet(&cameraPos, NULL, NULL, 3000, -1, 60);
    MBAudFXPlay(713);
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_LAUGH, FALSE);
    while(!MBMotionEndCheck(koopa->mdlId[0])) {
        HuPrcVSleep();
    }
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    MBWinCreate(2, MESS_BOARD_W07_HOU_BEGIN, 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_HOLD, FALSE);
    hou->fireEff[0] = MBEffCreate(mb7_Work.effAnim88, 256);
    MBEffHookSet(hou->fireEff[0], MB7Ev_KoopaFire1Hook);
    Hu3DModelLayerSet(hou->fireEff[0], 2);
    Hu3DModelPosSet(hou->fireEff[0], 0, 0, 0);
    hou->fireEff[1] = MBEffCreate(mb7_Work.effAnim88, 64);
    MBEffHookSet(hou->fireEff[1], MB7Ev_KoopaFire2Hook);
    Hu3DModelLayerSet(hou->fireEff[1], 2);
    Hu3DModelPosSet(hou->fireEff[1], 0, 0.05f, 0.05f);
    hou->fireEff[2] = MBEffCreate(mb7_Work.effAnim88, 64);
    MBEffHookSet(hou->fireEff[2], MB7Ev_KoopaFire3Hook);
    Hu3DModelLayerSet(hou->fireEff[2], 2);
    Hu3DModelPosSet(hou->fireEff[2], 0, -0.05f, -0.05f);
    hou->fireEff[3] = MBEffCreate(mb7_Work.effAnim88, 64);
    MBEffHookSet(hou->fireEff[3], MB7Ev_KoopaFire4Hook);
    Hu3DModelLayerSet(hou->fireEff[3], 2);
    Hu3DModelPosSet(hou->fireEff[3], 0, 0, -0.05f);
    endF = FALSE;
    while(!endF) {
        switch(hou->mode) {
            case 0:
                hou->angleY = 0;
                hou->angleSpeed = 0;
                hou->charge = 0;
                hou->fireF = 0;
                koopa->maxTime = 1;
                hou->mode++;
                emitter = HuAudFXEmiterPlay(1565, &pos);
                /* falls through */

            case 1:
                hou->angleY += hou->angleSpeed;
                if(hou->angleY > -45) {
                    if(hou->angleSpeed > -1) {
                        hou->angleSpeed += -0.02f;
                    }
                } else if(hou->angleY < -80 && hou->angleSpeed < -0.33333334f) {
                    hou->angleSpeed += 0.02f;
                }
                if(hou->angleY > -100) {
                    break;
                }
                hou->fireF = 1;
                hou->angleY = -100;
                hou->angleSpeed = 0;
                hou->mode++;
                HuAudFXStop(emitter);
                emitter = HuAudFXEmiterPlay(1567, &fxPos);
                break;

            case 2:
                HuAudFXEmiterUpDate(emitter, &fxPos);
                hou->charge += 0.05f*(1-hou->charge);
                hou->angleY += hou->angleSpeed;
                if(hou->angleY < 0) {
                    if(hou->angleSpeed < 0.5f) {
                        hou->angleSpeed += 0.01f;
                    }
                } else if(hou->angleY > 100 && hou->angleSpeed > 0.33333334f) {
                    hou->angleSpeed += -0.015000001f;
                }
                if(hou->angleY < 115) {
                    break;
                }
                hou->angleY = 115;
                hou->angleSpeed = 0;
                hou->fireF = 0;
                MBAudFXStop(emitter);
                hou->mode++;
                emitter = HuAudFXEmiterPlay(1565, &pos);
                break;

            case 3:
                hou->charge *= 0.95f;
                hou->angleY += hou->angleSpeed;
                if(hou->angleY > 45) {
                    if(hou->angleSpeed > -1) {
                        hou->angleSpeed += -0.02f;
                    }
                } else if(hou->angleY < 20 && hou->angleSpeed < -0.33333334f) {
                    hou->angleSpeed += 0.02f;
                }
                if(hou->angleY > 0) {
                    break;
                }
                hou->angleY = 0;
                hou->mode++;
                HuAudFXStop(emitter);
                MBAudFXPlay(1566);
                /* falls through */

            case 4:
                endF = TRUE;
                break;
        }
        hou->rot.y = hou->angleY;
        MBModelRotSetV(mdlId, &hou->rot);
        Hu3DModelObjPosGet(MBModelIdGet(mdlId), mb7ev_KupaPosHookName, &pos);
        Hu3DModelObjPosGet(MBModelIdGet(mdlId), mb7ev_FirePosHookName, &hou->firePos);
        hou->pos = pos;
        koopa->maxTime *= 0.93f;
        pos.x = pos.x+(-50*koopa->maxTime-50)*sin(M_PI*hou->rot.y/180);
        pos.z = pos.z+(-50*koopa->maxTime-50)*cos(M_PI*hou->rot.y/180);
        MBModelPosSetV(koopa->mdlId[0], &pos);
        MBModelRotSetV(koopa->mdlId[0], &hou->rot);
        if(hou->charge <= 0 || hou->fireF == 0) {
            MBModelDispSet(mb7_Work.objMdlId[9], FALSE);
        } else {
            MBModelDispSet(mb7_Work.objMdlId[9], TRUE);
            MBModelPosSet(mb7_Work.objMdlId[9], hou->firePos.x, hou->firePos.y-60.000004f, hou->firePos.z);
            MBModelRotSetV(mb7_Work.objMdlId[9], &hou->rot);
            MBModelScaleSet(mb7_Work.objMdlId[9], hou->charge, hou->charge, hou->charge);
        }
        fxPos.x = 250.0*(hou->charge*sin(M_PI*hou->rot.y/180));
        fxPos.z = 250.0*(hou->charge*cos(M_PI*hou->rot.y/180));
        fxPos.y = hou->firePos.y;
        MB7Ev_HouPlayerUpdate();
        player = &mb7_Work.player[0];
        for(i=0; i<GW_PLAYER_MAX; i++, player++) {
            if(player->enableF && player->mode < 3) {
                endF = FALSE;
            }
        }
        HuPrcVSleep();
    }
    MBEffKill(hou->fireEff[0]);
    MBEffKill(hou->fireEff[1]);
    MBEffKill(hou->fireEff[2]);
    MBEffKill(hou->fireEff[3]);
    hou->fireEff[0] = hou->fireEff[1] = hou->fireEff[2] = hou->fireEff[3] = -1;
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    MBAudFXPlay(713);
    MBWinCreate(2, MESS_BOARD_W07_HOU_END, 7);
    MBTopWinWait();
    MBTopWinKill();
    MB7Ev_KoopaMotionShiftSet(MB7EV_KOOPAMOT_STOMP, FALSE);
    cameraPos = pos;
    cameraPos.z -= 80;
    for(i=0; i<100; i++) {
        pos.z += 0.15f*(cameraPos.z-pos.z);
        MBModelPosSetV(koopa->mdlId[0], &pos);
        if(i == 65) {
            MBCameraQuakeSet(18, 50);
            MBAudFXPlay(716);
        }
        HuPrcVSleep();
    }
    MBMotionSpeedSet(koopa->mdlId[0], 0);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        if(player->enableF) {
            player->mode = -1;
        }
    }
    MB7Ev_HouPlayerUpdate();
    MB7Ev_KoopaClose();
    MBCameraFocusPlayerSet(playerNo);
    MBCameraSkipSet(FALSE);
    MBCameraZoomSet(2000);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<30.0f; i++) {
        HuPrcVSleep();
    }
}

/* 220 instructions */
static void MB7Ev_HouPlayerUpdate(void)
{
    MB7EV_HOU *hou;
    MB7EV_PLAYER *player;
    int i;
    MASU *masu;
    int j;
    int capsuleMax;
    float absDiff;

    hou = &mb7_Work.hou;
    player = &mb7_Work.player[0];
    for(i=0; i<GW_PLAYER_MAX; i++, player++) {
        if(player->enableF == 0) {
            continue;
        }
        masu = MBMasuGet(MASU_LAYER_DEFAULT, player->masuId);
        switch(player->mode) {
            case 0:
                player->motId = MBPlayerMotionCreate(i, CHARMOT_HSF_c000m1_321);
                MBPlayerPosGet(i, &player->pos);
                MBPlayerRotGet(i, &player->rot);
                player->unk04 = -1;
                player->mode++;
                break;

            case 1:
                if(hou->charge < 0.8f) {
                    break;
                }
                absDiff = fabsf2(MB7_AngleDiff(180.0 * (atan2(player->pos.x - hou->pos.x,
                                                             player->pos.z - hou->pos.z) / M_PI),
                                               hou->angleY));
                if(absDiff > 10) {
                    break;
                }
                capsuleMax = MBPlayerCapsuleMaxGet();
                for(j=0; j<capsuleMax; j++) {
                    MBPlayerCapsuleRemove(i, 0);
                }
                omVibrate(i, 12, 4, 2);
                MBPlayerMotionNoShiftSet(i, player->motId, 0, 8, HU3D_MOTATTR_LOOP);
                MBPlayerWinLoseVoicePlay(i, 1, 505);
                player->vel.y = 32.666668f;
                player->step = 0;
                player->mode++;
                /* falls through */

            case 2:
                player->vel.y += -0.8166667f;
                PSVECAdd(&player->pos, &player->vel, &player->pos);
                if(player->pos.y > masu->pos.y) {
                    break;
                }
                player->pos.y = masu->pos.y;
                player->vel.y *= -0.7f;
                player->step++;
                omVibrate(i, 12, 4, 2);
                if(player->step >= 2) {
                    player->vel.y = 0;
                    player->mode++;
                    MBPlayerMotionNoShiftSet(i, 6, 0, 8, HU3D_MOTATTR_LOOP);
                }
                break;

            case 3:
                break;

            case -1:
                MBPlayerMotionNoSet(i, 1, HU3D_MOTATTR_LOOP);
                MBPlayerMotionKill(i, player->motId);
                player->motId = -1;
                player->rot.y = 0;
                break;
        }
        MBPlayerPosSetV(i, &player->pos);
        MBPlayerRotSetV(i, &player->rot);
    }
}

/* 39 instructions */
static void MB7Ev_KoopaInit(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    int i;

    memset(koopa, 0, sizeof(MB7EV_KOOPA));
    koopa->motNo = -1;
    koopa->fxStep = 0;
    koopa->mdlId[0] = koopa->mdlId[1] = koopa->mdlId[2] = koopa->mdlId[3] = MB_MODEL_NONE;
    for(i=0; i<MB7EV_KOOPAMOT_MAX; i++) {
        koopa->motId[i] = -1;
    }
    koopa->dataStatId = MBDataDirReadAsync(DATA_capsulechar4);
}

/* 31 instructions */
static void MB7Ev_KoopaCreate(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    MBDataAsyncWait(koopa->dataStatId);
    koopa->mdlId[0] = MBModelCreate(CAPSULECHAR4_HSF_koopa, NULL, TRUE);
    MBModelDispSet(koopa->mdlId[0], FALSE);
    HuPrcVSleep();
    MB7Ev_KoopaMotionCreate(MB7EV_KOOPAMOT_IDLE);
    MB7Ev_KoopaMotionNoSet(MB7EV_KOOPAMOT_IDLE, TRUE);
    HuPrcVSleep();
}

/* 31 instructions */
static void MB7Ev_KoopaMotionCreate(int motNo)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    if(koopa->motId[motNo] < 0) {
        koopa->motId[motNo] = MBMotionCreate(koopa->mdlId[0], mb7ev_KoopaMotFileTbl[motNo]);
    }
}

/* 14 instructions */
static void MB7Ev_KoopaDataClose(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    HuDataDirClose(koopa->dataStatId);
}

/* 37 instructions */
static void MB7Ev_KoopaMotionNoSet(int motNo, BOOL loopF)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    u32 attr = HU3D_MOTATTR_NONE;

    if(loopF) {
        attr = HU3D_MOTATTR_LOOP;
        if(motNo == koopa->motNo) {
            return;
        }
        koopa->fxStep = 0;
    }
    MBMotionNoSet(koopa->mdlId[0], koopa->motId[motNo], attr);
    koopa->motNo = motNo;
}

/* 43 instructions */
static void MB7Ev_KoopaMotionShiftSet(int motNo, BOOL loopF)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    u32 attr = HU3D_MOTATTR_NONE;

    if(loopF) {
        attr = HU3D_MOTATTR_LOOP;
        if(motNo == koopa->motNo) {
            return;
        }
        koopa->fxStep = 0;
    }
    MBMotionShiftSet(koopa->mdlId[0], koopa->motId[motNo], 0, 8, attr);
    koopa->motNo = motNo;
}

/* 22 instructions */
static BOOL MB7Ev_KoopaMotionCheck(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;

    if(MBMotionShiftIDGet(koopa->mdlId[0]) >= 0) {
        return FALSE;
    }
    return MBMotionEndCheck(koopa->mdlId[0]);
}

/* 70 instructions */
static void MB7Ev_KoopaWalkFxPlay(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    float time;

    if(koopa->motNo != MB7EV_KOOPAMOT_WALK) {
        return;
    }
    time = MBMotionTimeGet(koopa->mdlId[0]);
    if(koopa->fxStep == 0) {
        if(time >= 15) {
            if(time < 25) {
                HuAudFXEmiterPlay(711, &koopa->pos);
            }
            koopa->fxStep = 1;
        }
    } else if(koopa->fxStep == 1) {
        if(time >= 65) {
            if(time < 75) {
                HuAudFXEmiterPlay(711, &koopa->pos);
            }
            koopa->fxStep = 2;
        }
    } else {
        if(time < 65) {
            koopa->fxStep = 0;
        }
    }
}

/* 33 instructions */
static void MB7Ev_KoopaClose(void)
{
    MB7EV_KOOPA *koopa = &mb7_Work.koopa;
    int i;

    for(i=0; i<4; i++) {
        if(koopa->mdlId[i] >= 0) {
            MBModelKill(koopa->mdlId[i]);
        }
        koopa->mdlId[i] = MB_MODEL_NONE;
    }
}

/* 776 instructions */
static void MB7Ev_KoopaFire1Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF dir;
    HuVecF pos;
    HuVecF vec;
    float value;
    float rate;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>3);
        }
        effP->count = 1;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = -0.15f;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&dir, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            value = rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF())));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->parManId = 20;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate);
            if(data->pos.y > 0) {
                data->pos.y *= 1+(3*MBEffRandF());
            }
            PSVECAdd(&pos, &data->pos, &data->pos);
            data->accel.x = 100+(80*MBEffRandF());
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(30+(30*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.95f;
        data->vel.z *= 0.95f;
        if(data->pos.y > pos.y+(50*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(90*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 683 instructions */
static void MB7Ev_KoopaFire2Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF dir;
    HuVecF pos;
    HuVecF vec;
    float value;
    float rate;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = -0.15f;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&dir, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            value = MBEffRandF();
            data->color.r = data->color.g = data->color.b = 255;
            data->color.r = 128+(127*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            value = rate*(1.3333334f+(1.6666666f*(1.2f*MBEffRandF())));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate);
            if(data->pos.y > 0) {
                data->pos.y *= 1+(2*MBEffRandF());
            }
            PSVECAdd(&pos, &data->pos, &data->pos);
            data->accel.x = rate*(50+(70*MBEffRandF()));
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(40+(60*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 1.088889f*data->accel.y;
        data->vel.x *= 0.95f;
        data->vel.z *= 0.95f;
        if(data->pos.y > pos.y+(50*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 859 instructions */
static void MB7Ev_KoopaFire3Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF vel;
    HuVecF pos;
    HuVecF firePos;
    HuVecF dir;
    HuVecF vec;
    float value;
    float rate;
    float power;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = 0;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&vel, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    firePos = hou->firePos;
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            power = HuSin(90*MBEffRandF());
            value = (0.7f+(0.3f*power))*(rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF()))));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->vel.y += rate*(-2.5f-(1.6666666f*MBEffRandF()));
            value = 1-(0.7f*power);
            PSVECScale(&dir, &vel, 1.6666666f*(7*(value*rate)));
            PSVECAdd(&vel, &data->vel, &data->vel);
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate*power);
            PSVECScale(&dir, &vel, 100*(1.8f*(power*hou->charge)));
            PSVECAdd(&firePos, &data->pos, &data->pos);
            PSVECAdd(&vel, &data->pos, &data->pos);
            data->accel.x = 80+(80*MBEffRandF());
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(30+(30*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.98f;
        data->vel.z *= 0.98f;
        if(data->pos.y > pos.y+(50*0.6f*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(50*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 862 instructions */
static void MB7Ev_KoopaFire4Hook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MB7EV_HOU *hou;
    MBEFFECTDATA *data;
    int i;
    HuVecF vel;
    HuVecF pos;
    HuVecF firePos;
    HuVecF dir;
    HuVecF vec;
    float value;
    float rate;
    float power;
    float speed;

    hou = &mb7_Work.hou;
    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>2);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    dir.x = HuSin(hou->angleY);
    dir.y = 0;
    dir.z = HuCos(hou->angleY);
    PSVECScale(&vel, &pos, 250*hou->charge);
    PSVECAdd(&pos, &hou->firePos, &pos);
    firePos = hou->firePos;
    rate = 0.3f+(0.7f*hou->charge);
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            continue;
        }
        if(data->time == 0) {
            if(hou->fireF == 0) {
                continue;
            }
            data->time++;
            data->rot.z = 360*MBEffRandF();
            data->color.r = data->color.g = data->color.b = 160+(95*MBEffRandF());
            value = 360*MBEffRandF();
            data->pos.x = HuSin(value);
            data->pos.z = HuCos(value);
            value = 1-HuSin(90*MBEffRandF());
            if(MBEffSRandF() < 0) {
                value *= -1;
            }
            data->pos.y = value;
            value = 1-(value*value);
            if(value <= 0) {
                value = 0;
            } else {
                value = sqrtf(1+(value*value));
            }
            data->pos.x *= value;
            data->pos.z *= value;
            power = HuSin(90*MBEffRandF());
            value = (0.7f+(0.3f*power))*(rate*(2.5f+(1.6666666f*(1.5f*MBEffRandF()))));
            data->vel.x = data->pos.x*value;
            data->vel.z = data->pos.z*value;
            data->vel.y = data->pos.y*value;
            data->vel.y += rate*(-2.1666665f-(1.6666666f*MBEffRandF()));
            value = 1-(0.7f*power);
            PSVECScale(&dir, &vel, 1.6666666f*(7*(value*rate)));
            PSVECAdd(&vel, &data->vel, &data->vel);
            data->parManId = 16;
            PSVECScale(&data->pos, &data->pos, 50*0.6f*rate*power);
            PSVECScale(&dir, &vel, 100*(1.8f*(power*hou->charge)));
            PSVECAdd(&firePos, &data->pos, &data->pos);
            PSVECAdd(&vel, &data->pos, &data->pos);
            data->accel.x = rate*(50+(60*MBEffRandF()));
            data->accel.y = rate;
            data->color.a = 0;
            data->scale = rate*(40+(40*MBEffRandF()));
            data->animBank = (int)(1000*MBEffRandF())&3;
            value = 360*MBEffRandF();
            speed = rate*(3.3333333f+(1.6666666f*(2*MBEffRandF())));
            data->speedDecay += speed*HuSin(value);
            data->scaleBase += speed*HuCos(value);
        }
        PSVECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += 0.8166668f*data->accel.y;
        data->vel.x *= 0.98f;
        data->vel.z *= 0.98f;
        if(data->pos.y > pos.y+(50*0.6f*data->accel.y)) {
            PSVECSubtract(&pos, &data->pos, &vec);
            data->vel.x += 0.7f*(0.016666668f*vec.x);
            data->vel.z += 0.7f*(0.016666668f*vec.z);
            if(data->pos.y > pos.y+(50*data->accel.y)) {
                data->vel.x += 1.3f*(0.016666668f*data->speedDecay);
                data->vel.z += 1.3f*(0.016666668f*data->scaleBase);
            }
        }
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 8) {
            if(data->color.a >= 30) {
                data->color.a -= 30;
            }
            data->scale += 5.0f;
        } else {
            data->color.a = data->color.a+(0.3f*(data->accel.x-data->color.a));
            data->scale += 2.0f;
        }
    }
}

/* 121 instructions */
static void MB7Ev_MasuRedInit(void)
{
    MASU *masu;
    int i;
    int j;
    int masuId;
    int k;
    MASU *linkMasu;
    int linkId;
    int no;
    int turnNum;

    mb7_Work.masuNum = MBMasuNumGet(MASU_LAYER_DEFAULT)+1;
    mb7_Work.masuRedTbl = HuMemDirectMallocNum(HEAP_HEAP, mb7_Work.masuNum, HU_MEMNUM_OVL);
    memset(mb7_Work.masuRedTbl, 0, mb7_Work.masuNum);
    for(i=0; i<MB7EV_KOOPA_MAX; i++) {
        if(mb7_SaveWorkP[i] == 0) {
            continue;
        }
        turnNum = mb7_SaveWorkP[i];
        for(j=1; j<mb7_Work.masuNum; j++) {
            masu = MBMasuGet(MASU_LAYER_DEFAULT, j);
            if(masu->type != MASU_TYPE_HATENA) {
                continue;
            }
            if(!(masu->flag & MB7EV_KOOPAWALK_FLAG)) {
                continue;
            }
            if(masu->pos.x >= 0) {
                no = 0;
            } else {
                no = 1;
            }
            if(i == no) {
                break;
            }
        }
        if(j >= mb7_Work.masuNum) {
            continue;
        }
        masuId = j;
        do {
            for(k=0; k<masu->linkNum; k++) {
                linkId = masu->linkTbl[k];
                linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, linkId);
                if(linkMasu->flag & MB7EV_RED_LINK_FLAG) {
                    break;
                }
            }
            masuId = linkId;
            masu = linkMasu;
            if(masu->type == MASU_TYPE_BLUE) {
                MBMasuTypeSet(MASU_LAYER_DEFAULT, masuId, MASU_TYPE_RED);
                mb7_Work.masuRedTbl[masuId] = turnNum;
            }
        } while(!(masu->flag & MB7EV_KOOPAWALK_FLAG));
    }
}

/* 26 instructions */
static void MB7Ev_MasuRedClose(void)
{
    if(mb7_Work.masuRedTbl) {
        HuMemDirectFree(mb7_Work.masuRedTbl);
    }
    mb7_Work.masuRedTbl = NULL;
    mb7_Work.masuNum = 0;
    MBPreTurnHookSet(NULL);
}

/* 12 instructions */
void MB7Ev_MasuRedSet(int masuId)
{
    if(mb7_Work.masuRedTbl != NULL) {
        mb7_Work.masuRedTbl[masuId] = 2;
    }
}

/* 21 instructions */
static BOOL MB7Ev_RedResetWin(void)
{
    int winId;

    winId = MBWinCreate(2, MESS_BOARD_W07_REDRESET, -1);
    MBWinPlayerDisable(winId, -1);
    MBTopWinWait();
    MBTopWinKill();
    return TRUE;
}

/* 153 instructions */
static void MB7Ev_RedResetHook(void)
{
    int i;
    BOOL resetF;

    if(mb7_Work.masuRedTbl == NULL) {
        return;
    }
    resetF = FALSE;
    for(i=0; i<MB7EV_KOOPA_MAX; i++) {
        if(mb7_SaveWorkP[i] == 0) {
            continue;
        }
        mb7_SaveWorkP[i]--;
        if(mb7_SaveWorkP[i] == 0) {
            resetF = TRUE;
        }
    }
    if(GwSystem.turnMax-GwSystem.turnNo == 4 && mb7_SaveWorkP[0]+mb7_SaveWorkP[1] != 0) {
        mb7_SaveWorkP[0] = mb7_SaveWorkP[1] = 0;
        resetF = TRUE;
        for(i=1; i<mb7_Work.masuNum; i++) {
            if(mb7_Work.masuRedTbl[i] != 0) {
                mb7_Work.masuRedTbl[i] = 1;
            }
        }
    }
    if(resetF) {
        for(i=1; i<mb7_Work.masuNum; i++) {
            if(mb7_Work.masuRedTbl[i] == 0) {
                continue;
            }
            mb7_Work.masuRedTbl[i]--;
            if(mb7_Work.masuRedTbl[i] != 0) {
                continue;
            }
            if(MBMasuTypeGet(MASU_LAYER_DEFAULT, i) != MASU_TYPE_RED) {
                continue;
            }
            MBMasuTypeSet(MASU_LAYER_DEFAULT, i, MASU_TYPE_BLUE);
        }
        MBPlayerPreTurnHookSet(0, MB7Ev_RedResetWin);
    } else {
        for(i=1; i<mb7_Work.masuNum; i++) {
            if(mb7_Work.masuRedTbl[i] != 0) {
                mb7_Work.masuRedTbl[i]--;
            }
        }
    }
}

/* 47 instructions */
static float MB7_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3)
{
    float mag = VECMag(vec3);
    if(mag > 0) {
        mag = ((vec3->x*(vec1->x-vec2->x))+(vec3->y*(vec1->y-vec2->y))+(vec3->z*(vec1->z-vec2->z)))/mag;
    }
    return mag;
}

/* 45 instructions */
static float MB7_AngleDiff(float start, float end)
{
    float angle = fmodf(end-start, 360);
    if(angle < 0) {
        angle += 360;
    }
    if(angle > 180) {
        angle -= 360;
    }
    return angle;
}

/* 30 instructions */
static unsigned int MB7Ev_BitGet(int outMask, unsigned int inMask)
{
    unsigned int bitIn;
    int i;
    unsigned int result;
    int bitOut;

    outMask &= inMask;
    result = 0;
    bitOut = bitIn = (1 << 0);

    for(i=0; i<32; i++) {
        if(inMask & bitIn) {
            if(outMask & bitIn) {
                result |= bitOut;
            }
            bitOut <<= 1;
        }
        bitIn <<= 1;
    }
    return result;
}

/* 29 instructions */
static unsigned int MB7Ev_MasuFlagGet(int outMask, unsigned int inMask)
{
    unsigned int bitIn;
    int i;
    int bitOut;
    unsigned int result;

    bitIn = bitOut = (1 << 0);
    result = 0;
    for(i=0; i<32; i++) {
        if(inMask & bitIn) {
            if(outMask & bitOut) {
                result |= bitIn;
            }
            bitOut <<= 1;
        }
        bitIn <<= 1;
    }
    return result;
}
