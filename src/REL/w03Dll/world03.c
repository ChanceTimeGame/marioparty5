/*
 * w03dll -- Mario Party 5's third party board, "Pirate Dream": a rolling rock,
 * a pickaxe, a moving scaffold over a waterfall, and a bit of digging.
 *
 * All 38 functions are written; 35 are byte-identical. The table below carries
 * each function's reference instruction count and the line range it occupies in
 *
 *     build/mp5-asm/w03dll/asm/REL/w03Dll/world03.s
 *
 * Regenerate that with `./games/mp5/gen_asm.sh w03dll`; nothing under build/ is
 * committed. Note the case: the module is **w03Dll** everywhere the decomp
 * build touches it (config.yml, configure.py, the asm path) and **w03dll**
 * everywhere the port does (ovl_table.h, this directory, the .dll the loader
 * searches for). project.py prints a "Case mismatch" line about it; that is
 * expected.
 *
 * THE NAMES ARE THE DISC'S, NOT INVENTED. Unlike the minigame overlays, this
 * module's symbols survive in upstream's config, so every function below is
 * already named. That is most of the usual work done: what is left is bodies.
 *
 * Verify per function, never by the headline number:
 *
 *   ./build/tools/ninja build/GP5E01_00/src/REL/w03Dll/world03.o
 *   R=$PWD/games/mp5/build/GP5E01_00/w03Dll/obj/REL/w03Dll/world03.o
 *   O=$PWD/games/mp5/build/GP5E01_00/src/REL/w03Dll/world03.o
 *   diff <($PWD/games/mp5/fndiff.py fn $R MB3_Create) \
 *        <($PWD/games/mp5/fndiff.py fn $O MB3_Create)
 *
 * fndiff.py needs absolute paths, and gen_asm.sh must have been run first --
 * without the reference object every diff reads as empty rather than erroring.
 *
 * SHAPE: every board is the same at both ends. ObjectSetup is three lines, and
 * the last three functions are the shared geometry helpers. The middle is this
 * board's own events. games/mp5/src/REL/w06dll/world06.c is the closest worked
 * example at 2,717 lines; read its header for the MASU_FLAG_BITFIELD idiom that
 * declares a board's space flags.
 *
 * | function | insns | asm lines |
 * | --- | ---: | --- |
 * | `ObjectSetup             ` |    21 |   61-83   |
 * | `MB3_Create              ` |   140 |   86-227  |
 * | `MB3_ObjectCreate        ` |   427 |  230-677  |
 * | `MB3_Kill                ` |   174 |  680-871  |
 * | `MB3_MainObjUpdate       ` |   141 |  874-1028 |
 * | `MB3_Splash1EffHook      ` |   390 | 1031-1432 |
 * | `MB3_Splash2EffHook      ` |   353 | 1435-1799 |
 * | `MB3_LightSet            ` |    31 | 1802-1834 |
 * | `MB3_LightReset          ` |     1 | 1837-1839 |
 * | `MB3Ev_MasuHatena        ` |    52 | 1842-1899 |
 * | `MB3_Stub                ` |     1 | 1902-1904 |
 * | `MB3Ev_MasuWalkPre       ` |     1 | 1907-1909 |
 * | `MB3Ev_MasuWalkPost      ` |    65 | 1912-1981 |
 * | `MB3Ev_KubiBone          ` |   351 | 1984-2341 |
 * | `MB3Ev_YYHou             ` |   800 | 2344-3187 |
 * | `MB3_ImpactEffUpdate     ` |   101 | 3190-3292 |
 * | `MB3_ImpactEffHook       ` |   116 | 3295-3416 |
 * | `MB3_ImpactEffPosSet     ` |   311 | 3419-3735 |
 * | `MB3Ev_RollRock          ` |   558 | 3738-4343 |
 * | `MB3_RollRockPathUpdate  ` |   529 | 4346-4893 |
 * | `MB3_RollRockEffUpdate   ` |   395 | 4896-5296 |
 * | `MB3_RollRockEffHook     ` |   110 | 5299-5414 |
 * | `MB3_RollRockDustCreate  ` |   347 | 5417-5769 |
 * | `MB3Ev_Turuhasi          ` |  1138 | 5772-6964 |
 * | `MB3_TuruhasiEffHook     ` |    78 | 6967-7053 |
 * | `MB3_TuruhasiEffCreate   ` |   314 | 7056-7375 |
 * | `MB3Ev_Asiba             ` |   345 | 7378-7746 |
 * | `MB3_AsibaPlayerUpdate   ` |   572 | 7749-8341 |
 * | `MB3_AsibaMinYGet        ` |    76 | 8344-8423 |
 * | `MB3_TakiEffHook         ` |    84 | 8426-8519 |
 * | `MB3_AsibaPlayerEffCreate` |   670 | 8522-9205 |
 * | `MB3_CoinEffInit         ` |    37 | 9208-9248 |
 * | `MB3_CoinEffClose        ` |    27 | 9251-9282 |
 * | `MB3_CoinEffCreate       ` |   141 | 9285-9431 |
 * | `MB3_CoinEffUpdate       ` |    77 | 9434-9515 |
 * | `MB3_DistRatioGet        ` |    47 | 9518-9567 |
 * | `MB3Ev_BitGet            ` |    30 | 9570-9605 |
 * | `MB3Ev_MasuFlagGet       ` |    29 | 9608-9642 |
 *
 * _prolog and _epilog are not reproduced: they are REL bootstrap the port
 * replaces, as in every other overlay here.
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
#include "game/board/roulette.h"
#include "game/board/star.h"

#include "game/sprite.h"
#include "game/wipe.h"
#include "game/gamemes.h"
#include "game/pad.h"
#include "game/charman.h"
#include "dolphin/pad.h"

#include "humath.h"

#include "string.h"
#include "msm_grp.h"

#include "datanum/board.h"
#include "datanum/charmot.h"
#include "datanum/w03.h"
#include "messdir_enum.h"
#include "messnum/board_w03.h"


/* --- work --- */

/* One record per falling rock, twenty of them at work+0x88. MB3_ObjectCreate
 * only writes +0x0E, which made the array look as though it started at 0x96;
 * MB3_MainObjUpdate walks it with an explicit `p = &work->rock[0]` and settles
 * both the base and the fields. */
typedef struct MB3Rock_s {
    HuVecF vel;                    /* 0x00 */
    u16 timer;                     /* 0x0C */
    MBMODELID mdlId;               /* 0x0E */
    int emitter1;                  /* 0x10 */
    int emitter2;                  /* 0x14 */
} MB3_ROCK;                        /* 0x18 */

/* One per player at work+0x268, 0x64 each. **Two events share it** -- the
 * scaffold ride keys off `active` at +0x00 and the rolling rock off
 * `rockActive` at +0x08, and everything from `state` down is common. `state`
 * is the jumptable index in both, seeded to -1 and stepped by the update
 * function; the two jumptables differ (nine arms for the scaffold, eight for
 * the rock). */
typedef struct MB3PWork_s {
    s32 active;                    /* 0x00, MB3Ev_Asiba's */
    s32 no;                        /* 0x04, index into mb3ev_AsibaPosTbl */
    s32 rockActive;                /* 0x08, MB3Ev_RollRock's */
    s32 subNo;                     /* 0x0C */
    s32 state;                     /* 0x10 */
    s32 masuId;                    /* 0x14 */
    s32 timer;                     /* 0x18 */
    float unk1C;                   /* 0x1C */
    float unk20;                   /* 0x20 */
    float angle;                   /* 0x24 */
    s16 motId[2];                  /* 0x028 */
    u8 unk02C[0x030 - 0x02C];
    s32 effId;                     /* 0x030 */
    HuVecF pos;                    /* 0x034 */
    HuVecF rot;                    /* 0x040 */
    HuVecF vel;                    /* 0x04C */
    u8 unk058[0x064 - 0x058];
} MB3_PWORK;                       /* 0x64 */

/* Eight of these at work+0x3F8, memset as a block by MB3_CoinEffInit. */
typedef struct MB3CoinEff_s {
    s16 unk00;                     /* 0x00, a countdown */
    MBMODELID mdlId;               /* 0x02 */
    HuVecF pos;                    /* 0x04 */
    HuVecF vel;                    /* 0x10 */
    float rotY;                    /* 0x1C */
    float unk20;                   /* 0x20, eases toward 1 */
} MB3_COINEFF;                     /* 0x24 */

/* 0x518, from the memset in MB3_Create. Offsets named as they are found. */
typedef struct MB3Work_s {
    s32 objMdlId[9];               /* 0x000 -- word-sized model ids */
    s32 turuhasiMasuId;            /* 0x024 */
    s32 unk028;                    /* 0x028 */
    s32 unk02C;                    /* 0x02C, a masu id above y=2000 */
    s32 unk030;                    /* 0x030, a masu id below it */
    ANIMDATA *takiAnim;            /* 0x034 */
    ANIMDATA *splashAnim;          /* 0x038 */
    ANIMDATA *anim3C;              /* 0x03C */
    ANIMDATA *anim40;              /* 0x040 */
    HU3DMODELID takiEff[4];        /* 0x044 */
    HU3DMODELID splash1Eff[3];     /* 0x04C */
    HU3DMODELID splash2Eff[3];     /* 0x052 */
    HU3DMODELID eff58;             /* 0x058 */
    HU3DMODELID eff5A;             /* 0x05A */
    HU3DMODELID impactEff;         /* 0x05C */
    HU3DMODELID dustEff;           /* 0x05E */
    s16 turuhasiMot[2];            /* 0x060 */
    HuVecF rockPos;                /* 0x064 */
    s32 rockNo;                    /* 0x070 */
    s32 unk074;                    /* 0x074, gates the yybone matrix update */
    s32 timer[4];                  /* 0x078 */
    MB3_ROCK rock[20];             /* 0x088 */
    MB3_PWORK pwork[4];            /* 0x268 */
    MB3_COINEFF coinEff[8];        /* 0x3F8 */
} MB3_WORK;                        /* 0x518 */

static char mb3_YyBoneHookName[] = "yybone3-bnhook";

/* mb3_ObjFileTbl -- the nine board models, [4] deliberately absent. */
static const u32 mb3_ObjFileTbl[9] = {
    DATANUM(DATA_w03, 0x0A), DATANUM(DATA_w03, 0x04), DATANUM(DATA_w03, 0x0E),
    DATANUM(DATA_w03, 0x09), 0,                       DATANUM(DATA_w03, 0x0C),
    DATANUM(DATA_w03, 0x0D), DATANUM(DATA_w03, 0x05), DATANUM(DATA_w03, 0x0B),
};

/* mb3ev_AsibaPosTbl -- the eight waypoints the scaffold rides down. */
static HuVecF mb3ev_AsibaPosTbl[8] = {
    { 0, 3443.4f, -1884.01f },
    { 0, 3300.18f, -969.244f },
    { 0, 3142.13f, -829.8f },
    { 0, 1363.63f, -754.184f },
    { 0, 1344.01f, -325.654f },
    { 0, 1235.69f, -239.724f },
    { 0, 1, -154.724f },
    { 0, 1, 345.276f },
};

/* mb3ev_AsibaOfsTbl -- where a rider stands, one offset per quadrant. */
static HuVecF mb3ev_AsibaOfsTbl[4] = {
    { 40, 0, 60.000004f },
    { -120.000008f, 0, 0 },
    { 120.000008f, 0, -60.000004f },
    { -40, 0, -120.000008f },
};

/* mb3ev_AsibaYureTimeTbl -- how long each quadrant rides before letting go. */
static int mb3ev_AsibaYureTimeTbl[4] = { 48, 51, 54, 57 };

/* mb3ev_TakiEffPosTbl -- three points down the waterfall. */
static HuVecF mb3ev_TakiEffPosTbl[3] = {
    { 0, 3345, -1885 },
    { 0, 1285, -775 },
    { 0, -35, -185 },
};

/* --- .bss --- */

static MB3_WORK mb3_Work;
static MBMODELID mb3_MainMdlId;
static OMOBJ *mb3_MainObj;

/* --- forward declarations --- */

void ObjectSetup(void);
static void MB3_Create(void); /* 140 instructions, world03.s:86-227 */
static void MB3_ObjectCreate(void); /* 427 instructions, world03.s:230-677 */
static void MB3_Kill(void); /* 174 instructions, world03.s:680-871 */
static void MB3_MainObjUpdate(OMOBJ *obj); /* 141 instructions, world03.s:874-1028 */
static void MB3_Splash1EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 390 instructions, world03.s:1031-1432 */
static void MB3_Splash2EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 353 instructions, world03.s:1435-1799 */
static void MB3_LightSet(void); /* 31 instructions, world03.s:1802-1834 */
static void MB3_LightReset(void); /* 1 instructions, world03.s:1837-1839 */
static int MB3Ev_MasuHatena(int playerNo); /* 52 instructions, world03.s:1842-1899 */
static void MB3_Stub(void); /* 1 instructions, world03.s:1902-1904 */
static int MB3Ev_MasuWalkPre(int playerNo); /* 1 instructions, world03.s:1907-1909 */
static int MB3Ev_MasuWalkPost(int playerNo); /* 65 instructions, world03.s:1912-1981 */
static void MB3Ev_KubiBone(MASU *masu, int no); /* 351 instructions, world03.s:1984-2341 */
static void MB3Ev_YYHou(int playerNo); /* 800 instructions, world03.s:2344-3187 */
static void MB3_ImpactEffUpdate(int mdlId, int count); /* 101 instructions, world03.s:3190-3292 */
static void MB3_ImpactEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 116 instructions, world03.s:3295-3416 */
static void MB3_ImpactEffPosSet(HuVecF *pos, float angleX, float angleY); /* 311 instructions, world03.s:3419-3735 */
static void MB3Ev_RollRock(int playerNo); /* 558 instructions, world03.s:3738-4343 */
static void MB3_RollRockPathUpdate(void); /* 529 instructions, world03.s:4346-4893 */
static void MB3_RollRockEffUpdate(HuVecF *pos); /* 395 instructions, world03.s:4896-5296 */
static void MB3_RollRockEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 110 instructions, world03.s:5299-5414 */
static void MB3_RollRockDustCreate(HuVecF *pos); /* 347 instructions, world03.s:5417-5769 */
static void MB3Ev_Turuhasi(int playerNo); /* 1138 instructions, world03.s:5772-6964 */
static void MB3_TuruhasiEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 78 instructions, world03.s:6967-7053 */
static void MB3_TuruhasiEffCreate(MB3_PWORK *work); /* 314 instructions, world03.s:7056-7375 */
static void MB3Ev_Asiba(int playerNo); /* 345 instructions, world03.s:7378-7746 */
static void MB3_AsibaPlayerUpdate(void); /* 572 instructions, world03.s:7749-8341 */
static float MB3_AsibaMinYGet(int no, HuVecF *pos); /* 76 instructions, world03.s:8344-8423 */
static void MB3_TakiEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix); /* 84 instructions, world03.s:8426-8519 */
static void MB3_AsibaPlayerEffCreate(MB3_PWORK *work, int no); /* 670 instructions, world03.s:8522-9205 */
static void MB3_CoinEffInit(void); /* 37 instructions, world03.s:9208-9248 */
static void MB3_CoinEffClose(void); /* 27 instructions, world03.s:9251-9282 */
static void MB3_CoinEffCreate(HuVecF *pos); /* 141 instructions, world03.s:9285-9431 */
static void MB3_CoinEffUpdate(void); /* 77 instructions, world03.s:9434-9515 */
static float MB3_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3); /* 47 instructions, world03.s:9518-9567 */
static unsigned int MB3Ev_BitGet(int outMask, unsigned int inMask); /* 30 instructions, world03.s:9570-9605 */
static unsigned int MB3Ev_MasuFlagGet(int outMask, unsigned int inMask); /* 29 instructions, world03.s:9608-9642 */

/* --- stubs --- */

/* ObjectSetup -- 21 instructions, world03.s:61-83 */
void ObjectSetup(void)
{
    GWPartyFSet(TRUE);
    MBObjectSetup(MBNO_WORLD_3, MB3_Create, MB3_Kill);
}

/* 140 instructions, world03.s:86-227 */
static void MB3_Create(void)
{
    int boardNo = MBBoardNoGet();

    HuAudSndGrpSetSet(MSM_GRP_BD3);
    memset(&mb3_Work, 0, sizeof(MB3_WORK));
    MBMasuCreate(W03_BIN_masuData);
    mb3_MainMdlId = MBModelCreate(W03_HSF_map, NULL, FALSE);
    MBModelPosSet(mb3_MainMdlId, 0, 0, 0);
    MBModelAttrSet(mb3_MainMdlId, HU3D_MOTATTR_LOOP);
    MBScrollInit(W03_HSF_scrollCol, 20000, -1700);
    {
        HuVecF cameraPos = { 0, 0, -4500 };
        HuVecF cameraRot = { -33, 0, 0 };
        HuVecF mapCameraPos = { -250, 0, -1700 };
        HuVecF mapCameraRot = { -78, 0, 0 };
        MBOpeningViewSet(&cameraRot, &cameraPos, 20000);
        MBMapViewCameraSet(&mapCameraRot, &mapCameraPos, 20000);
    }
    MBLightHookSet(MB3_LightSet, MB3_LightReset);
    MBCapsuleColCreate(W03_HSF_capsuleCol);
    MBBranchFlagSet(MASU_FLAG_BIT(6));
    MBBranchFlagSet(MASU_FLAG_BIT(1));

    MB3_ObjectCreate();
    HuDataDirClose(DATA_w03);
    MBMasuWalkPreHookSet(MB3Ev_MasuWalkPre);
    MBMasuWalkPostHookSet(MB3Ev_MasuWalkPost);
    MBMasuHatenaHookSet(MB3Ev_MasuHatena);
    mb3_MainObj = MBAddObj(32768, 0, 0, MB3_MainObjUpdate);
}

/* 427 instructions, world03.s:230-677 */
static void MB3_ObjectCreate(void)
{
    int i;
    int j;
    int mdlId;
    int masuId;
    int startId;
    int masuNum;
    MASU *masu;
    MASU *linkMasu;

    for(i=0; i<9; i++) {
        mb3_Work.objMdlId[i] = MB_MODEL_NONE;
        if(mb3_ObjFileTbl[i]) {
            mdlId = MBModelCreate(mb3_ObjFileTbl[i], NULL, FALSE);
            mb3_Work.objMdlId[i] = mdlId;
            MBModelPosSet(mdlId, 0, 0, 0);
            MBMotionSpeedSet(mdlId, 0);
        }
    }
    mdlId = mb3_Work.objMdlId[0];
    MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    MBMotionSpeedSet(mdlId, 1);
    MBModelDispSet(mb3_Work.objMdlId[8], FALSE);
    for(i=0; i<20; i++) {
        mb3_Work.rock[i].mdlId = MB_MODEL_NONE;
        mdlId = MBModelCreate(DATANUM(DATA_w03, 6), NULL, TRUE);
        mb3_Work.rock[i].mdlId = mdlId;
        MBModelPosSet(mdlId, 0, 0, 0);
        MBModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
        MBModelDispSet(mdlId, FALSE);
    }
    if(mb3_Work.objMdlId[2] > 0) {
        startId = MBMasuFlagFind(MASU_LAYER_DEFAULT, MASU_FLAG_BIT(11), MASU_FLAG_BIT(11));
        masu = MBMasuGet(MASU_LAYER_DEFAULT, startId);
        masuId = -1;
        for(j=0; j<masu->linkNum; j++) {
            masuId = masu->linkTbl[j];
            linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
            if(linkMasu->linkNum == 0) {
                break;
            }
            masuId = -1;
        }
        if(masuId < 0) {
            masuId = startId;
        }
        mb3_Work.turuhasiMasuId = masuId;
        linkMasu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        mdlId = mb3_Work.objMdlId[2];
        MBModelDispSet(mdlId, FALSE);
        MBModelPosSetV(mdlId, &linkMasu->pos);
        MBModelRotSet(mdlId, 0,
                      180.0 * (atan2(masu->pos.x - linkMasu->pos.x,
                                     masu->pos.z - linkMasu->pos.z) / M_PI), 0);
        mb3_Work.turuhasiMot[0] = MBMotionCreate(mdlId, DATANUM(DATA_w03, 0x0F));
        mb3_Work.turuhasiMot[1] = MBMotionCreate(mdlId, DATANUM(DATA_w03, 0x10));
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionSpeedSet(mdlId, 0);
    }
    if(mb3_Work.objMdlId[5] > 0) {
        masuNum = MBMasuNumGet(MASU_LAYER_DEFAULT);
        for(i=1; i<=masuNum; i++) {
            masu = MBMasuGet(MASU_LAYER_DEFAULT, i);
            if(masu->flag & MASU_FLAG_BIT(14)) {
                if(masu->pos.y > 2000) {
                    mb3_Work.unk02C = i;
                } else {
                    mb3_Work.unk030 = i;
                }
            }
        }
    }
    mb3_Work.takiAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x11), HU_MEMNUM_OVL));
    mb3_Work.splashAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x12), HU_MEMNUM_OVL));
    mb3_Work.anim3C = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x14), HU_MEMNUM_OVL));
    mb3_Work.anim40 = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_w03, 0x15), HU_MEMNUM_OVL));
    for(i=0; i<4; i++) {
        mb3_Work.takiEff[i] = MBEffCreate(mb3_Work.takiAnim, 64);
        MBEffHookSet(mb3_Work.takiEff[i], MB3_TakiEffHook);
        Hu3DModelLayerSet(mb3_Work.takiEff[i], 3);
    }
    for(i=0; i<3; i++) {
        mb3_Work.splash1Eff[i] = MBEffCreate(mb3_Work.splashAnim, 192);
        MBEffHookSet(mb3_Work.splash1Eff[i], MB3_Splash1EffHook);
        Hu3DModelLayerSet(mb3_Work.splash1Eff[i], 2);
        Hu3DModelPosSetV(mb3_Work.splash1Eff[i], &mb3ev_TakiEffPosTbl[i]);
        mb3_Work.splash2Eff[i] = MBEffCreate(mb3_Work.splashAnim, 48);
        MBEffHookSet(mb3_Work.splash2Eff[i], MB3_Splash2EffHook);
        Hu3DModelLayerSet(mb3_Work.splash2Eff[i], 2);
        Hu3DModelPosSet(mb3_Work.splash2Eff[i], mb3ev_TakiEffPosTbl[i].x,
                        mb3ev_TakiEffPosTbl[i].y, 50 + mb3ev_TakiEffPosTbl[i].z);
        MBAudFXEmiterSet(1500, &mb3ev_TakiEffPosTbl[i]);
    }
    mb3_Work.eff58 = MBEffCreate(mb3_Work.anim3C, 1);
    mb3_Work.eff5A = MBEffCreate(mb3_Work.anim40, 1);
}

/* 174 instructions, world03.s:680-871 */
static void MB3_Kill(void)
{
    int i;

    if(mb3_MainMdlId >= 0) {
        MBModelKill(mb3_MainMdlId);
        mb3_MainMdlId = MB_MODEL_NONE;
    }
    MBCameraModelViewSet(MB_MODEL_NONE, NULL, NULL, -1, 45, 63);
    for(i=0; i<9; i++) {
        if(mb3_Work.objMdlId[i] >= 0) {
            MBModelKill(mb3_Work.objMdlId[i]);
        }
        mb3_Work.objMdlId[i] = MB_MODEL_NONE;
    }
    for(i=0; i<20; i++) {
        if(mb3_Work.rock[i].mdlId >= 0) {
            MBModelKill(mb3_Work.rock[i].mdlId);
        }
        mb3_Work.rock[i].mdlId = MB_MODEL_NONE;
    }
    for(i=0; i<4; i++) {
        if(mb3_Work.takiEff[i] >= 0) {
            MBEffKill(mb3_Work.takiEff[i]);
        }
        mb3_Work.takiEff[i] = HU3D_MODELID_NONE;
    }
    for(i=0; i<3; i++) {
        if(mb3_Work.splash1Eff[i] >= 0) {
            MBEffKill(mb3_Work.splash1Eff[i]);
        }
        mb3_Work.splash1Eff[i] = HU3D_MODELID_NONE;
        if(mb3_Work.splash2Eff[i] >= 0) {
            MBEffKill(mb3_Work.splash2Eff[i]);
        }
        mb3_Work.splash2Eff[i] = HU3D_MODELID_NONE;
    }
    if(mb3_Work.eff58 >= 0) {
        MBEffKill(mb3_Work.eff58);
    }
    if(mb3_Work.eff5A >= 0) {
        MBEffKill(mb3_Work.eff5A);
    }
    mb3_Work.eff58 = mb3_Work.eff5A = HU3D_MODELID_NONE;
}

/* 141 instructions, world03.s:874-1028 */
static void MB3_MainObjUpdate(OMOBJ *obj)
{
    MBCAMERA *camera;
    MB3_ROCK *rock;
    int i;
    int mdlId;
    HuVecF pos;
    Mtx matrix;

    if(MBKillCheck()) {
        if(mb3_MainObj != NULL) {
            omDelObjEx(mbObjMan, mb3_MainObj);
        }
        return;
    }
    camera = MBCameraGet();
    for(i=0; i<4; i++) {
        if(mb3_Work.timer[i] != 0) {
            mb3_Work.timer[i]--;
        }
    }
    rock = &mb3_Work.rock[0];
    for(i=0; i<20; i++, rock++) {
        if(rock->timer == 0) {
            continue;
        }
        mdlId = rock->mdlId;
        rock->timer--;
        if(rock->timer == 0) {
            MBModelDispSet(mdlId, FALSE);
            rock->emitter1 = rock->emitter2 = -1;
            continue;
        }
        if(rock->vel.y < 13.333333f) {
            rock->vel.y += 0.1388889f;
        }
        MBModelPosGet(mdlId, &pos);
        PSVECAdd(&pos, &rock->vel, &pos);
        MBModelPosSetV(mdlId, &pos);
        if(rock->emitter1 >= 0) {
            HuAudFXEmiterUpDate(rock->emitter1, &pos);
        }
        if(rock->emitter2 >= 0) {
            HuAudFXEmiterUpDate(rock->emitter2, &pos);
        }
    }
    if(mb3_Work.unk074 != 0) {
        Hu3DModelObjMtxGet(MBModelIdGet(mb3_Work.objMdlId[3]), mb3_YyBoneHookName, matrix);
        MBMasuMtxSet(MBMasuFlagMatchFind(MASU_LAYER_DEFAULT, MASU_FLAG_BIT(7)), matrix);
        if(MBMotionEndCheck(mb3_Work.objMdlId[3])) {
            mb3_Work.unk074 = 0;
        }
    }
}

/* 390 instructions, world03.s:1031-1432 */
static void MB3_Splash1EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    static HuVecF radius = { 250, 250, 250 };
    MBEFFECTDATA *data;
    int i;
    float rate;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>3);
        }
        effP->count = 1;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            data->time++;
            continue;
        }
        if(data->time == 0) {
            data->time++;
            data->rot.z = 360*MBEffRandF();
            rate = MBEffRandF();
            data->color.r = 0.98f*(160+(70*rate));
            data->color.g = 0.98f*(200+(40*rate));
            data->color.b = 0.98f*(180+(55*rate));
            data->vel.x = 1.6666666f*(0.8f*MBEffSRandF());
            data->vel.z = 1.6666666f+(1.6666666f*(2*MBEffRandF()));
            data->vel.y = 6.6666665f+(1.6666666f*(4*MBEffRandF()));
            data->parManId = effP->num>>3;
            data->pos.x = radius.x*MBEffSRandF();
            data->pos.z = 100*(0.3f*MBEffSRandF());
            data->pos.y = 100*(0.5f*MBEffRandF());
            data->color.a = 180+(70*MBEffRandF());
            data->scale = 60+(40*MBEffRandF());
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 10) {
            if(data->color.a >= 20) {
                data->color.a -= 20;
            }
            data->scale += 5.0f;
        }
    }
}

/* 353 instructions, world03.s:1435-1799 */
static void MB3_Splash2EffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    static HuVecF radius = { 250, 250, 250 };
    MBEFFECTDATA *data;
    int i;
    float rate;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
            data->time = -(i>>1);
        }
        effP->count = 1;
        effP->blendMode = MB_EFFECT_BLEND_ADDCOL;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time < 0) {
            data->time++;
            continue;
        }
        if(data->time == 0) {
            data->time++;
            data->rot.z = 360*MBEffRandF();
            rate = MBEffRandF();
            data->color.r = data->color.g = data->color.b = 255;
            data->vel.x = 1.6666666f*(0.8f*MBEffSRandF());
            data->vel.z = 1.6666666f+(1.6666666f*(4*MBEffRandF()));
            data->vel.y = 4.1666665f+(1.6666666f*(2.5f*MBEffRandF()));
            data->parManId = effP->num>>1;
            data->pos.x = radius.x*MBEffSRandF();
            data->pos.z = (100*(0.3f*MBEffSRandF()))-50;
            data->pos.y = 50+(100*(1.5f*MBEffRandF()));
            data->color.a = 20+(20*MBEffRandF());
            data->scale = 120+(50*MBEffRandF());
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
            continue;
        }
        if(data->parManId < 10) {
            if(data->color.a >= 10) {
                data->color.a -= 10;
            }
            data->scale += 5.0f;
        }
    }
}

/* 31 instructions, world03.s:1802-1834 */
static void MB3_LightSet(void)
{
    Hu3DShadowCreate(45, 1000, 250000);
    Hu3DShadowTPLvlSet(0.3f);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DModelLightInfoSet(MBModelIdGet(mb3_MainMdlId), TRUE);
}

/* 1 instructions, world03.s:1837-1839 */
static void MB3_LightReset(void)
{
}

/* 52 instructions, world03.s:1842-1899 */
static int MB3Ev_MasuHatena(int playerNo)
{
    MASU *masu;
    u32 flag;
    int no;

    masu = MBMasuGet(MASU_LAYER_DEFAULT, GwPlayer[playerNo].masuId);
    flag = (u16)masu->flag;
    if(flag & MASU_FLAG_BIT(11)) {
        MB3Ev_Turuhasi(playerNo);
    }
    if(flag & (MASU_FLAG_BIT(12) | MASU_FLAG_BIT(4) | MASU_FLAG_BIT(3))) {
        no = MB3Ev_BitGet(flag, MASU_FLAG_BIT(12) | MASU_FLAG_BIT(4) | MASU_FLAG_BIT(3));
        if(no == 1) {
            MB3Ev_RollRock(playerNo);
        }
    }
    if(flag & MASU_FLAG_BIT(13)) {
        MB3Ev_YYHou(playerNo);
    }
    if(flag & MASU_FLAG_BIT(14)) {
        MB3Ev_Asiba(playerNo);
    }
}

/* 1 instructions, world03.s:1902-1904 */
static void MB3_Stub(void)
{
}

/* 1 instructions, world03.s:1907-1909 */
static int MB3Ev_MasuWalkPre(int playerNo)
{
    /* The reference is a bare blr: declared int by MASUPLAYERHOOK, but with no
     * return statement. w06dll's equivalent returns 0 and is two instructions. */
}

/* 65 instructions, world03.s:1912-1981 */
static int MB3Ev_MasuWalkPost(int playerNo)
{
    MASU *masu;
    u32 flag;
    s16 masuId;
    int mdlId;
    int no;

    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    if((flag & MASU_FLAG_BIT(7)) && mb3_Work.unk074 == 0) {
        mdlId = mb3_Work.objMdlId[3];
        if(mdlId >= 0) {
            MBMotionTimeSet(mdlId, 0);
            MBMotionSpeedSet(mdlId, 1);
        }
        mb3_Work.unk074 = 1;
        MBAudFXPlay(1507);
    }
    if(flag & (MASU_FLAG_BIT(15) | MASU_FLAG_BIT(5))) {
        no = MB3Ev_BitGet(flag, MASU_FLAG_BIT(15) | MASU_FLAG_BIT(5));
        MB3Ev_KubiBone(masu, no);
    }
    return 0;
}

/* 351 instructions, world03.s:1984-2341 */
static void MB3Ev_KubiBone(MASU *masu, int no)
{
    static float radius[4] = { 0, 10, 60, 0 };
    HuVecF pos;
    HuVecF rot;
    Mtx mtxY;
    Mtx mtxZ;
    MB3_ROCK *rock;
    int mdlId;
    int i;
    int num;
    float base;
    float angle;
    float speed;

    if(mb3_Work.timer[no] != 0) {
        return;
    }
    mb3_Work.timer[no] = 180;
    pos = masu->pos;
    pos.y += 300.0f;
    base = radius[no];
    num = 10;
    for(rock = &mb3_Work.rock[0], i=0; i<20; i++, rock++) {
        if(rock->timer != 0) {
            continue;
        }
        rock->timer = 180;
        angle = base+(20*MBEffSRandF());
        speed = 6.6666665f+(1.6666666f*(3*MBEffRandF()));
        rock->vel.x = speed*HuSin(angle);
        rock->vel.z = speed*HuCos(angle);
        rock->vel.y = (1.6666666f*(-2*MBEffRandF()))-1.6666666f;
        PSMTXRotRad(mtxY, 'Y', 0.017453292f*angle);
        PSMTXRotRad(mtxZ, 'Z', 0.017453292f*(45*MBEffSRandF()));
        PSMTXConcat(mtxZ, mtxY, mtxY);
        Hu3DMtxRotGet(mtxY, &rot);
        mdlId = rock->mdlId;
        MBModelDispSet(mdlId, TRUE);
        MBModelPosSet(mdlId, pos.x+(100*(0.3*MBEffSRandF())), pos.y-(100*(0.3*MBEffRandF())), pos.z+(100*(0.3*MBEffSRandF())));
        MBModelRotSetV(mdlId, &rot);
        MBMotionTimeSet(mdlId, 6*MBEffRandF());
        rock->emitter1 = rock->emitter2 = -1;
        if(i == 0) {
            rock->emitter1 = HuAudFXEmiterPlay(0x5DE, &pos);
            rock->emitter2 = HuAudFXEmiterPlay(0x5E4, &pos);
        }
        num--;
        if(num <= 0) {
            break;
        }
    }
}

/* 800 instructions, world03.s:2344-3187 */
static void MB3Ev_YYHou(int playerNo)
{
    u32 flag;
    int playerTbl[4];
    HuVecF pos;
    HuVecF vel;
    HuVecF vec;
    HuVecF rot;
    Mtx mtxB;
    Mtx mtxA;
    MASU *masu;
    s16 masuId;
    int i;
    int mdlId;
    int hooMdlId;
    int count;
    int frame;
    int warpId;
    MASU *masuP;
    int liveF;
    float scale;
    float time;
    float grav;
    float angle;

    frame = 0;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerMotIdleSet(playerNo);
    flag = (u16)masu->flag;
    mdlId = MBModelCreate(BOARD_HSF_effExplode, NULL, FALSE);
    MBModelLayerSet(mdlId, 6);
    MBModelDispSet(mdlId, FALSE);
    playerTbl[0] = playerTbl[1] = playerTbl[2] = playerTbl[3] = -1;
    count = 0;
    liveF = 1;
    mb3_Work.impactEff = MBEffCreate(mb3_Work.anim40, 32);
    MBEffAttrSet(mb3_Work.impactEff, MB_EFFECT_ATTR_UPAUSE);
    MBEffHookSet(mb3_Work.impactEff, MB3_ImpactEffHook);
    Hu3DModelLayerSet(mb3_Work.impactEff, 3);
    if(liveF != 0) {
        hooMdlId = mb3_Work.objMdlId[1];
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 8, 0);
        MBPlayerPosGet(playerNo, &pos);
        Hu3DModelObjPosGet(MBModelIdGet(mb3_Work.objMdlId[1]), "yy_hou2-thook", &vel);
        vel.y += 200;
        VECSubtract(&vel, &pos, &vel);
        time = 0.6f;
        grav = -4900;
        vel.x /= time;
        vel.z /= time;
        vel.y = (vel.y/time)-((0.5f*time)*grav);
        VECScale(&vel, &vel, 0.016666668f);
        time *= 60;
        grav *= 0.0002777778f;
        MBPlayerRotSet(playerNo, 0, HuAtan(vel.x, vel.z), 0);
        for(i=0; i<3; i++) {
            HuPrcVSleep();
        }
        for(i=0; i<(int)time; i++) {
            vel.y += grav;
            VECAdd(&pos, &vel, &pos);
            MBPlayerPosSetV(playerNo, &pos);
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 5, 0, 0, 0);
        time = 30;
        scale = 1;
        for(i=0; i<(int)time; i++) {
            pos.y += -200/time;
            scale *= 0.95f;
            MBPlayerPosSetV(playerNo, &pos);
            MBPlayerScaleSet(playerNo, scale, scale, scale);
            HuPrcVSleep();
        }
        warpId = -1;
        for(i=0; i<masu->linkNum; i++) {
            warpId = masu->linkTbl[i];
            masuP = MBMasuGet(MASU_LAYER_DEFAULT, warpId);
            if(masuP->linkNum == 0) {
                break;
            }
            warpId = -1;
        }
        if(warpId < 0) {
            warpId = masuId;
        }
        MBCameraFocusSet(-1);
        MBMotionSpeedSet(hooMdlId, 1);
        MBMotionTimeSet(hooMdlId, 0);
        MBAudFXPlay(0x5DF);
        for(i=0; i<MBMotionMaxTimeGet(hooMdlId)-10; i++) {
            HuPrcVSleep();
        }
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 0, 0x40000001);
        MBPlayerPosGet(playerNo, &pos);
        MBPlayerWinLoseVoicePlay(playerNo, 1, 0x1F9);
        angle = 0;
        vel.x = HuSin(210)*HuCos(60);
        vel.y = HuSin(60);
        vel.z = HuCos(210)*HuCos(60);
        VECScale(&vel, &vec, 200);
        VECAdd(&pos, &vec, &vec);
        MB3_ImpactEffPosSet(&vec, 60, 200);
        MBAudFXPlay(0x5E0);
        omVibrate(playerNo, 12, 4, 2);
        VECScale(&vel, &vel, 33.333332f);
        MBCameraQuakeSet(18, 500);
        for(i=0; i<30.0f; i++) {
            angle += 18;
            PSMTXRotRad(mtxB, 'Y', 0.017453292f*angle);
            PSMTXRotRad(mtxA, 'X', 0.5235988f);
            PSMTXConcat(mtxA, mtxB, mtxB);
            PSMTXRotRad(mtxA, 'Y', 3.6651914f);
            PSMTXConcat(mtxA, mtxB, mtxB);
            Hu3DMtxRotGet(mtxB, &rot);
            MBPlayerRotSetV(playerNo, &rot);
            VECAdd(&pos, &vel, &pos);
            MBPlayerPosSetV(playerNo, &pos);
            scale += 0.3f*(1-scale);
            MBPlayerScaleSet(playerNo, scale, scale, scale);
            HuPrcVSleep();
        }
        MBPlayerScaleSet(playerNo, 1, 1, 1);
        i = (int)(3*MBEffRandF())+1;
        warpId = MBMasuFlagFind(MASU_LAYER_DEFAULT, MB3Ev_MasuFlagGet(i, MASU_FLAG_BIT(8)|MASU_FLAG_BIT(9)), MASU_FLAG_BIT(8)|MASU_FLAG_BIT(9));
        count = 0;
        for(i=0; i<4; i++) {
            if(warpId == GwPlayer[i].masuId) {
                playerTbl[i] = i;
                count++;
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        MBEffKill(mb3_Work.impactEff);
        mb3_Work.impactEff = mb3_Work.dustEff = -1;
        MBPlayerPosFixWarp(playerNo, warpId, TRUE);
        MBCameraFocusMasuSet(warpId);
        MBCameraSkipSet(0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        masu = MBMasuGet(MASU_LAYER_DEFAULT, warpId);
        pos.x = masu->pos.x;
        pos.y = masu->pos.y;
        pos.z = masu->pos.z;
        pos.y += 1000;
        vel.x = vel.z = 0;
        vel.y = -5;
        MBPlayerRotSet(playerNo, 0, 0, 0);
        MBPlayerScaleSet(playerNo, 1, 1, 1);
        MBPlayerMotionNoShiftSet(playerNo, 4, 0, 0, 0);
        while(pos.y > masu->pos.y) {
            if(pos.y-masu->pos.y < 200 && MBPlayerMotionNoGet(playerNo) != 5) {
                MBPlayerMotionNoShiftSet(playerNo, 5, 0, 0, 0);
                frame = 0;
                if(count != 0) {
                    MBModelDispSet(mdlId, TRUE);
                    MBMotionTimeSet(mdlId, 0);
                }
            }
            MBPlayerPosSetV(playerNo, &pos);
            MB3_ImpactEffUpdate(mdlId, frame);
            frame++;
            HuPrcVSleep();
            VECAdd(&pos, &vel, &pos);
            vel.y += grav;
        }
        GwPlayer[playerNo].masuId = warpId;
        do {
            MB3_ImpactEffUpdate(mdlId, frame);
            frame++;
            HuPrcVSleep();
        } while(MBPlayerMotionEndCheck(playerNo) == 0);
        MBPlayerMotIdleSet(playerNo);
        for(i=0; i<30; i++) {
            frame++;
            MB3_ImpactEffUpdate(mdlId, frame);
            HuPrcVSleep();
        }
        if(count != 0) {
            MBModelDispSet(mdlId, FALSE);
            for(i=0; i<4; i++) {
                if(playerTbl[i] >= 0) {
                    MBPlayerMotionNoSet(i, 6, 0x40000001);
                }
            }
            for(i=0; i<4; i++) {
                if(playerTbl[i] >= 0) {
                    MBCoinAddDispExec(i, -5, TRUE);
                }
            }
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        for(i=0; i<4; i++) {
            if(playerTbl[i] >= 0) {
                MBPlayerMotionNoSet(i, 1, 0x40000001);
            }
        }
        MBMotionSpeedSet(mb3_Work.objMdlId[1], 0);
        MBMotionTimeSet(mb3_Work.objMdlId[1], 0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
    }
    MBModelKill(mdlId);
}

/* 101 instructions, world03.s:3190-3292 */
static void MB3_ImpactEffUpdate(int mdlId, int count)
{
    HuVecF outPos;
    HuVecF pos = { 0, 0, -500 };
    Mtx mtx;
    float t;
    float scale;

    PSMTXInverse(Hu3DCameraMtx, mtx);
    PSMTXMultVec(mtx, &pos, &outPos);
    mtx[0][3] = mtx[1][3] = mtx[2][3] = 0;
    t = count/30.0f;
    scale = (1+(5*t))+(0.5*HuSin(16*(360*t)));
    scale *= 0.4f;
    MBModelPosSetV(mdlId, &outPos);
    MBModelMtxSet(mdlId, &mtx);
    MBModelScaleSet(mdlId, scale, scale, scale);
}

/* 116 instructions, world03.s:3295-3416 */
static void MB3_ImpactEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;

    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.x *= 0.9f;
        data->vel.y *= 0.9f;
        data->vel.z *= 0.9f;
        data->scale += 6.0f;
        data->color.a *= 0.98f;
        if(data->time < 24.0f) {
            data->color.a = 0.9f*data->color.a;
        }
        if(--data->time == 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        }
    }
}

/* 311 instructions, world03.s:3419-3735 */
static void MB3_ImpactEffPosSet(HuVecF *pos, float angleX, float angleY)
{
    MBEFFECT *effP = Hu3DData[mb3_Work.impactEff].hookData;
    HuVecF dir;
    HuVecF vec;
    Mtx mtx;
    Mtx mtxY;
    MBEFFECTDATA *data;
    int i;
    u32 num;
    float rate;
    float speed;

    PSMTXRotRad(mtx, 'X', 0.017453292f*angleX);
    PSMTXRotRad(mtxY, 'Y', 0.017453292f*angleY);
    PSMTXConcat(mtx, mtxY, mtx);
    PSMTXTransApply(mtx, mtx, pos->x, pos->y, pos->z);
    data = effP->data;
    num = 32;
    for(i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time = 60*(0.7f+(0.5f*MBEffRandF()));
        rate = 360*MBEffSRandF();
        dir.x = HuCos(rate);
        dir.y = HuSin(rate);
        dir.z = 0.5f;
        VECScale(&dir, &vec, 20);
        PSMTXMultVec(mtx, &vec, &data->pos);
        speed = 13.333333f+(1.6666666f*(7*MBEffRandF()));
        VECScale(&dir, &vec, speed);
        PSMTXMultVecSR(mtx, &vec, &data->vel);
        data->rot.z = 360*MBEffRandF();
        data->scale = 20+(20*MBEffRandF());
        data->color.a = 100+(80*MBEffRandF());
        rate = MBEffRandF();
        data->color.r = 150+(70*rate);
        data->color.g = 144+(70*rate);
        data->color.b = 140+(70*rate);
        num--;
        if(num < 1) {
            break;
        }
    }
}

/* 558 instructions, world03.s:3738-4343 */
static void MB3Ev_RollRock(int playerNo)
{
    u32 flag;
    int masuNum;
    HuVecF pos;
    HuVecF target;
    MASU *masu;
    MASU *masuP;
    MASU *masuL;
    int i;
    int j;
    int mdlId;
    int state;
    int audId;
    s16 masuId;
    s16 bestId;
    int count;
    int timer;
    int best;
    s16 linkId;
    int done;
    float zoom;

    state = 0;
    audId = -1;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerMotIdleSet(playerNo);
    flag = (u16)masu->flag;
    memset(&mb3_Work.pwork[0], 0, sizeof(mb3_Work.pwork));
    for(i=0; i<4; i++) {
        bestId = GwPlayer[i].masuId;
        masuP = MBMasuGet(MASU_LAYER_DEFAULT, bestId);
        for(j=0; j<masuP->linkNum; j++) {
            linkId = masuP->linkTbl[j];
            masuL = MBMasuGet(MASU_LAYER_DEFAULT, linkId);
            if(masuL->flag & MASU_FLAG_BIT(6)) {
                mb3_Work.pwork[i].rockActive = 1;
                mb3_Work.pwork[i].masuId = linkId;
                break;
            }
        }
    }
    mb3_Work.rockNo = 0;
    masuNum = MBMasuNumGet(MASU_LAYER_DEFAULT);
    best = 0;
    bestId = 0;
    for(i=1; i<=masuNum; i++) {
        count = 0;
        masuP = MBMasuGet(MASU_LAYER_DEFAULT, i);
        while((masuP->flag & MASU_FLAG_BIT(6)) && masuP->linkNum != 0) {
            masuL = NULL;
            for(j=0; j<masuP->linkNum; j++) {
                masuL = MBMasuGet(MASU_LAYER_DEFAULT, masuP->linkTbl[j]);
                if(masuL->flag & MASU_FLAG_BIT(6)) {
                    break;
                }
                masuL = NULL;
            }
            if(masuL == NULL) {
                break;
            }
            masuP = masuL;
            count++;
        }
        if(best < count) {
            bestId = i;
            best = count;
        }
    }
    mb3_Work.unk028 = bestId;
    MB3_RollRockPathUpdate();
    mdlId = mb3_Work.objMdlId[7];
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    zoom = MBCameraZoomGet();
    mb3_Work.impactEff = MBEffCreate(mb3_Work.anim3C, 32);
    MBEffAttrSet(mb3_Work.impactEff, MB_EFFECT_ATTR_UPAUSE);
    MBEffHookSet(mb3_Work.impactEff, MB3_TuruhasiEffHook);
    Hu3DModelLayerSet(mb3_Work.impactEff, 3);
    mb3_Work.dustEff = MBEffCreate(mb3_Work.anim40, 64);
    MBEffAttrSet(mb3_Work.dustEff, MB_EFFECT_ATTR_UPAUSE);
    MBEffHookSet(mb3_Work.dustEff, MB3_RollRockEffHook);
    Hu3DModelLayerSet(mb3_Work.dustEff, 3);
    MBCameraFocusSet(-1);
    Hu3DModelObjPosGet(MBModelIdGet(mdlId), "trap-iwa1", &target);
    MBCameraPosTargetSetV(&target);
    MBCameraZoomSet(3000);
    MBCameraSkipSet(0);
    MBStarDispSetAll(FALSE);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    MBCameraQuakeSet(60, 50);
    while(WipeCheckEnd()) {
        MBCameraPosTargetSetV(&target);
        HuPrcVSleep();
    }
    MBMotionSpeedSet(mdlId, 1.2f);
    do {
        masuP = MBMasuGet(MASU_LAYER_DEFAULT, mb3_Work.unk028);
        switch(state) {
            case 0:
                if((int)MB3Ev_BitGet(masuP->flag, MASU_FLAG_BIT(12)|MASU_FLAG_BIT(4)|MASU_FLAG_BIT(3)) == 2) {
                    state++;
                }
                break;

            case 1:
                WipeColorSet(0, 0, 0);
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 30);
                state++;
                break;

            case 2:
                if(WipeCheckEnd()) {
                    break;
                }
                MBAudFXPlay(0x5E5);
                MBMotionSpeedSet(mdlId, 6);
                timer = 25;
                state++;
                break;

            case 3:
                timer--;
                if(timer >= 0) {
                    break;
                }
                MBMotionSpeedSet(mdlId, 1.2f);
                WipeCreate(WIPE_MODE_IN, WIPE_TYPE_NORMAL, 30);
                i = MBMasuFlagFind(MASU_LAYER_DEFAULT, MB3Ev_MasuFlagGet(2, MASU_FLAG_BIT(15)|MASU_FLAG_BIT(5)), MASU_FLAG_BIT(15)|MASU_FLAG_BIT(5));
                MB3Ev_KubiBone(MBMasuGet(MASU_LAYER_DEFAULT, i), 2);
                state++;
                break;
        }
        Hu3DModelObjPosGet(MBModelIdGet(mdlId), "trap-iwa1", &pos);
        target = mb3_Work.rockPos = pos;
        MBCameraPosTargetSetV(&target);
        VECSubtract(&pos, &masuP->pos, &pos);
        pos.y = 0.1f;
        if(VECMag(&pos) < 240.00002f) {
            for(j=0; j<masuP->linkNum; j++) {
                masuL = MBMasuGet(MASU_LAYER_DEFAULT, masuP->linkTbl[j]);
                if(masuL->flag & MASU_FLAG_BIT(6)) {
                    mb3_Work.unk028 = masuP->linkTbl[j];
                    break;
                }
            }
        }
        if(MBMotionTimeGet(mdlId) > 10 && MBMotionTimeGet(mdlId) < 800) {
            MB3_RollRockEffUpdate(&mb3_Work.rockPos);
            MB3_RollRockDustCreate(&mb3_Work.rockPos);
        }
        if(MBMotionTimeGet(mdlId) > 10) {
            if(MBMotionTimeGet(mdlId) < 820) {
                if(audId < 0) {
                    audId = HuAudFXPlay(0x5E2);
                }
            } else if(audId >= 0) {
                HuAudFXStop(audId);
                audId = -1;
                OSReport("GOROGORO Stop!\n");
            }
        }
        MB3_RollRockPathUpdate();
        HuPrcVSleep();
        done = 1;
        for(i=0; i<4; i++) {
            if(mb3_Work.pwork[i].rockActive == 1) {
                done = 0;
            }
        }
    } while(done == 0);
    for(i=0; i<60; i++) {
        MB3_RollRockPathUpdate();
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    MBStarDispSetAll(TRUE);
    MBEffKill(mb3_Work.impactEff);
    MBEffKill(mb3_Work.dustEff);
    mb3_Work.impactEff = mb3_Work.dustEff = -1;
    for(i=0; i<4; i++) {
        mb3_Work.pwork[i].state = -1;
    }
    MB3_RollRockPathUpdate();
    masuId = GwPlayer[playerNo].masuId;
    MBPlayerPosFixCurr(masuId, 1);
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    MBCameraFocusSet(-1);
    MBCameraZoomSet(zoom);
    MBCameraFocusMasuSet(masuId);
    MBCameraSkipSet(0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<60; i++) {
        HuPrcVSleep();
    }
}

/* 529 instructions, world03.s:4346-4893 */
static void MB3_RollRockPathUpdate(void)
{
    static float radius[4] = { 180, 90, 270, 0 };
    HuVecF vec;
    HuVecF pos;
    HuVecF ofs;
    HuVecF dir;
    MASU *masu;
    MASU *masuP;
    MB3_PWORK *work;
    int i;
    int masuId;
    int hitF;
    float dist;
    float mag;
    float angle;

    dist = 450;
    masuId = mb3_Work.unk028;
    pos = mb3_Work.rockPos;
    for(;;) {
        masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
        VECSubtract(&masu->pos, &pos, &vec);
        vec.y = 0.0001f;
        mag = VECMag(&vec);
        dist -= mag;
        if(dist <= 0) {
            break;
        }
        pos = masu->pos;
        masuId = masu->linkTbl[0];
    }
    dist += mag;
    angle = HuAtan(vec.x, vec.z);
    VECSubtract(&masu->pos, &pos, &dir);
    VECScale(&dir, &vec, dist/mag);
    VECAdd(&pos, &vec, &pos);
    VECNormalize(&dir, &dir);
    hitF = 0;
    if(!(masu->flag & MASU_FLAG_BIT(6))) {
        hitF = 1;
    }
    for(work = &mb3_Work.pwork[0], i=0; i<4; i++, work++) {
        if(work->rockActive == 0) {
            continue;
        }
        masuP = MBMasuGet(MASU_LAYER_DEFAULT, work->masuId);
        switch(work->state) {
            case 0:
                MBPlayerPosGet(i, &work->pos);
                MBPlayerRotGet(i, &work->rot);
                work->subNo = -1;
                work->state++;
                break;

            case 1:
                MBAngleMoveTo(&work->rot.y, 0, 0.1f);
                VECSubtract(&pos, &masuP->pos, &vec);
                vec.y = 0.01f;
                if(VECMag(&vec) > 600) {
                    break;
                }
                work->subNo = mb3_Work.rockNo++;
                MBPlayerMotionNoShiftSet(i, 9, 0, 0, 0);
                work->unk1C = 36;
                work->state++;
                /* falls through */

            case 2:
                mag = HuAtan(mb3_Work.rockPos.x-work->pos.x, mb3_Work.rockPos.z-work->pos.z);
                MBAngleMoveTo(&work->rot.y, mag, 0.1f);
                work->unk1C -= 1;
                if(work->unk1C > 0) {
                    break;
                }
                MBPlayerMotionNoShiftSet(i, 3, 0, 8, 0x40000001);
                work->state++;
                /* falls through */

            case 3:
                VECScale(&dir, &vec, 14.166666f);
                VECAdd(&work->pos, &vec, &work->pos);
                ofs.x = 100*(1.2f*HuSin(angle+radius[work->subNo]));
                ofs.y = 0;
                ofs.z = 100*(1.2f*HuCos(angle+radius[work->subNo]));
                VECAdd(&pos, &ofs, &vec);
                VECSubtract(&vec, &work->pos, &vec);
                VECScale(&vec, &vec, 0.08f);
                VECAdd(&vec, &work->pos, &work->pos);
                MBAngleMoveTo(&work->rot.y, angle, 0.15f);
                if(hitF == 0) {
                    break;
                }
                VECAdd(&masu->pos, &ofs, &vec);
                VECSubtract(&vec, &work->pos, &vec);
                mag = 0.8f;
                dist = -2450;
                vec.x /= mag;
                vec.z /= mag;
                vec.y = (vec.y/mag)-((0.5f*mag)*dist);
                VECScale(&vec, &work->vel, 0.016666668f);
                work->unk1C = 60*mag;
                work->unk20 = 0.016666668f*(0.016666668f*dist);
                work->angle = angle;
                MBPlayerMotionNoShiftSet(i, 4, 0, 8, 0);
                work->timer = 0;
                work->masuId = masu->linkTbl[0];
                work->state++;
                break;

            case 4:
                work->vel.y += work->unk20;
                VECAdd(&work->pos, &work->vel, &work->pos);
                if(work->timer == 0 && work->unk1C <= 5) {
                    MBPlayerMotionNoShiftSet(i, 5, 0, 0, 0);
                    work->timer++;
                }
                MBAngleMoveTo(&work->rot.y, work->angle, 0.15f);
                work->unk1C -= 1;
                if(work->unk1C > 0) {
                    break;
                }
                work->rockActive = 2;
                work->unk1C = 12;
                work->state++;
                break;

            case 5:
                work->unk1C -= 1;
                if(work->unk1C > 0) {
                    break;
                }
                MBPlayerMotionNoShiftSet(i, 1, 0, 8, 0x40000001);
                work->state++;
                break;

            case 6:
                MBAngleMoveTo(&work->rot.y, 0, 0.15f);
                work->rockActive = 2;
                break;

            case -1:
                GwPlayer[i].masuId = work->masuId;
                MBPlayerPosReset(i);
                work->rot.x = work->rot.y = work->rot.z = 0;
                MBPlayerMotionNoShiftSet(i, 1, 0, 0, 0x40000001);
                break;
        }
        if(work->state >= 0) {
            MBPlayerPosSetV(i, &work->pos);
        }
        MBPlayerRotSetV(i, &work->rot);
    }
}

/* 395 instructions, world03.s:4896-5296 */
static void MB3_RollRockEffUpdate(HuVecF *pos)
{
    MBEFFECT *effP = Hu3DData[mb3_Work.impactEff].hookData;
    HuVecF dir;
    MBEFFECTDATA *data;
    int i;
    int num;
    float rate;
    float speed;

    num = 1;
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time++;
        data->rot.z = 360*MBEffRandF();
        rate = MBEffRandF();
        data->color.r = 230;
        data->color.g = 255;
        data->color.b = 255;
        data->pos.x = pos->x+(100*(0.2f*MBEffSRandF()));
        data->pos.y = pos->y-150;
        data->pos.z = pos->z+(100*(0.2f*MBEffSRandF()));
        rate = 360*MBEffRandF();
        dir.x = HuSin(rate);
        dir.z = HuCos(rate);
        speed = 13.333333f+(1.6666666f*(5*MBEffRandF()));
        data->vel.x = (dir.x*speed)+(1.6666666f*MBEffSRandF());
        data->vel.z = (dir.z*speed)+(1.6666666f*MBEffSRandF());
        data->vel.y = 3.3333333f+(1.6666666f*(2*MBEffRandF()));
        data->parManId = 18+(0.2f*(60*MBEffRandF()));
        data->color.a = 150+(100*MBEffRandF());
        data->scale = 20+(40*MBEffRandF());
        data->animBank = 3*MBEffRandF();
        num--;
        if(num <= 0) {
            break;
        }
    }
}

/* 110 instructions, world03.s:5299-5414 */
static void MB3_RollRockEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;

    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.x *= 0.94f;
        data->vel.z *= 0.94f;
        data->scale += 6.0f;
        data->color.a *= 0.99f;
        if(data->time < 24.0f) {
            data->color.a = 0.9f*data->color.a;
        }
        if(--data->time == 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        }
    }
}

/* 347 instructions, world03.s:5417-5769 */
static void MB3_RollRockDustCreate(HuVecF *pos)
{
    MBEFFECT *effP = Hu3DData[mb3_Work.dustEff].hookData;
    HuVecF dir;
    MBEFFECTDATA *data;
    int i;
    u32 num;
    float rate;
    float speed;

    data = effP->data;
    num = 1;
    for(i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time = 60*(0.7f+(0.5f*MBEffRandF()));
        rate = 360*MBEffSRandF();
        dir.x = HuSin(rate);
        dir.y = 0;
        dir.z = HuCos(rate);
        data->pos.x = pos->x+(100*MBEffSRandF());
        data->pos.y = pos->y-120.00001f;
        data->pos.z = pos->z+(100*MBEffSRandF());
        speed = 1.6666666f*(10*MBEffRandF());
        data->vel.x = dir.x*speed;
        data->vel.z = dir.z*speed;
        data->vel.y = speed*(0.1f+(0.2f*MBEffRandF()));
        data->rot.z = 360*MBEffRandF();
        data->scale = 90+(100*MBEffRandF());
        data->color.a = 100+(80*MBEffRandF());
        rate = MBEffRandF();
        data->color.r = 70+(70*rate);
        data->color.g = 64+(68*rate);
        data->color.b = 54+(60*rate);
        num--;
        if(num < 1) {
            break;
        }
    }
}

/* 1138 instructions, world03.s:5772-6964 */
static void MB3Ev_Turuhasi(int playerNo)
{
    u32 flag;
    HuVecF pos;
    HuVecF camRot;
    HuVecF coinPos;
    MASU *masu;
    MASU *masuT;
    MB3_PWORK *work;
    s16 masuId;
    int i;
    int mdlId;
    int digF;
    int coinNum;
    int motF;
    int pressF;
    int effF;
    int coinF;
    int btn;
    int mesId;
    float t;
    float zoom;
    int frameLeft;

    digF = 0;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    MBPlayerMotIdleSet(playerNo);
    flag = (u16)masu->flag;
    masuT = MBMasuGet(MASU_LAYER_DEFAULT, mb3_Work.turuhasiMasuId);
    mdlId = mb3_Work.objMdlId[2];
    if(MBPlayerCoinGet(playerNo) < 5) {
        pos = masuT->pos;
        pos.y -= 100;
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionTimeSet(mdlId, 0);
        MBMotionSpeedSet(mdlId, 1);
        MBModelPosSetV(mdlId, &pos);
        MBModelDispSet(mdlId, TRUE);
        MBAudFXPlay(0x5E7);
        HuPrcVSleep();
        for(i=0; i<20; i++) {
            t = 1-(0.05263158f*i);
            t = 1-(t*t);
            MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
            HuPrcVSleep();
        }
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[1], 0x40000001);
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W03_TURUHASI_NOCOIN, HUWIN_SPEAKER_CHORO);
        MBTopWinWait();
        MBTopWinKill();
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionTimeSet(mdlId, MBMotionMaxTimeGet(mdlId));
        MBMotionSpeedSet(mdlId, -2);
        for(i=0; i<10; i++) {
            t = 0.11111111f*i;
            t = 1-(t*t);
            MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
            HuPrcVSleep();
        }
        MBModelDispSet(mdlId, FALSE);
        return;
    }
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        if(i != playerNo) {
            MBModelDispSet(MBPlayerModelGet(i), FALSE);
        }
    }
    MBPlayerRotSet(playerNo, 0, HuAtan(masuT->pos.x-masu->pos.x, masuT->pos.z-masu->pos.z), 0);
    MBCameraFocusMasuSet(mb3_Work.turuhasiMasuId);
    zoom = MBCameraZoomGet();
    MBCameraZoomSet(2000);
    MBCameraSkipSet(0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    mdlId = mb3_Work.objMdlId[2];
    pos = masuT->pos;
    pos.y -= 100;
    MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
    MBMotionTimeSet(mdlId, 0);
    MBMotionSpeedSet(mdlId, 1);
    MBModelPosSetV(mdlId, &pos);
    MBModelDispSet(mdlId, TRUE);
    MBAudFXPlay(0x5E7);
    HuPrcVSleep();
    for(i=0; i<20; i++) {
        t = 1-(0.05263158f*i);
        t = 1-(t*t);
        MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
        HuPrcVSleep();
    }
    MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[1], 0x40000001);
    MBWinCreateChoice(MBWIN_TYPE_RESULT, MESS_BOARD_W03_TURUHASI_ASK, HUWIN_SPEAKER_CHORO, 0);
    if(GwPlayer[playerNo].comF) {
        MBComChoiceSetUp();
    }
    MBTopWinWait();
    digF = 0;
    if(MBWinLastChoiceGet() == 0) {
        digF = 1;
    }
    MBTopWinKill();
    if(digF != 0) {
        memset(&mb3_Work.pwork[0], 0, sizeof(mb3_Work.pwork));
        work = &mb3_Work.pwork[0];
        MBCoinAddDispExec(playerNo, -5, TRUE);
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        for(i=0; i<4; i++) {
            if(i != playerNo) {
                MBModelDispSet(MBPlayerModelGet(i), FALSE);
            }
        }
        MBPlayerRotSet(playerNo, 0, HuAtan(masuT->pos.x-masu->pos.x, masuT->pos.z-masu->pos.z), 0);
        pos.x = -826;
        pos.y = 4162;
        pos.z = -2260;
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionTimeSet(mdlId, 0);
        MBMotionSpeedSet(mdlId, 0);
        MBModelPosSetV(mdlId, &pos);
        MBPlayerPosSet(playerNo, 200+masu->pos.x, masu->pos.y, 600+masu->pos.z);
        MBPlayerRotSet(playerNo, 0, 0, 0);
        MBPlayerPosGet(playerNo, &work->pos);
        MBPlayerRotGet(playerNo, &work->rot);
        work->motId[0] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_381);
        work->motId[1] = MBPlayerMotionCreate(playerNo, CHARMOT_HSF_c000m1_382);
        MBPlayerMotionNoShiftSet(playerNo, work->motId[0], 0, 0, 0x40000001);
        MBModelRotSet(mb3_Work.objMdlId[8], 90, 0, 0);
        MBModelPosSet(mb3_Work.objMdlId[8], 0, 0, 10);
        MBModelDispSet(mb3_Work.objMdlId[8], TRUE);
        MBModelHookSet(MBPlayerModelGet(playerNo), CharModelItemHookGet(GwPlayer[playerNo].charNo, 2, 0), mb3_Work.objMdlId[8]);
        work->effId = MBEffCreate(mb3_Work.anim3C, 64);
        MBEffAttrSet(work->effId, MB_EFFECT_ATTR_UPAUSE);
        MBEffHookSet(work->effId, MB3_TuruhasiEffHook);
        Hu3DModelLayerSet(work->effId, 3);
        Hu3DModelPosSetV(work->effId, &work->pos);
        MB3_CoinEffInit();
        MBCameraFocusSet(-1);
        MBCameraPosTargetSet(150+masu->pos.x, masu->pos.y, 500+masu->pos.z);
        MBCameraZoomSet(2500);
        MBCameraRotGet(&camRot);
        MBCameraRotSet(camRot.x, -20, camRot.z);
        MBCameraSkipSet(0);
        WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        MBMotionSpeedSet(mdlId, 1);
        MBAudFXPlay(0x5E7);
        for(i=0; i<20; i++) {
            t = 1-(0.05263158f*i);
            t = 1-(t*t);
            MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
            HuPrcVSleep();
        }
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[1], 0x40000001);
        mesId = GameMesTimerCreate(5);
        GameMesTimerValueSet(mesId, 5);
        MBWinCreate(MBWIN_TYPE_TALKEVENT, MESS_BOARD_W03_TURUHASI_INST, HUWIN_SPEAKER_CHORO);
        MBTopWinWait();
        MBTopWinKill();
        MBPlayerMotionNoSet(playerNo, work->motId[1], 0);
        MBPlayerMotionTimeSet(playerNo, 0);
        MBPlayerMotionSpeedSet(playerNo, 0);
        coinNum = 0;
        motF = 1;
        pressF = 0;
        effF = 0;
        coinF = 0;
        for(i=0; i<360; i++) {
            btn = HuPadBtnDown[GwPlayer[playerNo].padNo];
            if(GwPlayer[playerNo].comF && (i & 3) == 0 && MBEffRandF() < 0.6f) {
                btn |= PAD_BUTTON_A;
            }
            if(i >= 300) {
                btn = 0;
            }
            if(btn & PAD_BUTTON_A) {
                pressF = 1;
                work->timer++;
            }
            if(work->timer >= 3) {
                work->timer = 0;
                coinNum++;
                coinF = 1;
            }
            if(pressF != 0) {
                if(motF == 0) {
                    MBPlayerMotionTimeSet(playerNo, 0);
                    MBPlayerMotionSpeedSet(playerNo, 2);
                    motF = 1;
                } else {
                    MBPlayerMotionTimeSet(playerNo, 5);
                    MBPlayerMotionSpeedSet(playerNo, 1);
                    pressF = 0;
                    motF = 0;
                }
            }
            if(MBPlayerMotionEndCheck(playerNo)) {
                MBPlayerMotionTimeSet(playerNo, 0);
                MBPlayerMotionSpeedSet(playerNo, 0);
                motF = 1;
            }
            if(effF == 0) {
                if(MBPlayerMotionTimeGet(playerNo) >= 5) {
                    effF = 1;
                    MBAudFXPlay(0x5E1);
                    MB3_TuruhasiEffCreate(work);
                    if(coinF != 0) {
                        coinPos = work->pos;
                        coinPos.z += 100;
                        MB3_CoinEffCreate(&coinPos);
                        coinF = 0;
                    }
                }
            } else if(motF != 0) {
                effF = 0;
            }
            MB3_CoinEffUpdate();
            if(mesId >= 0) {
                frameLeft = 299-i;
                if(frameLeft >= 0) {
                    GameMesTimerValueSet(mesId, frameLeft/60);
                } else {
                    GameMesTimerEnd(mesId);
                    mesId = -1;
                }
            }
            HuPrcVSleep();
        }
        MBCoinAddDispExec(playerNo, coinNum, TRUE);
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionTimeSet(mdlId, MBMotionMaxTimeGet(mdlId));
        MBMotionSpeedSet(mdlId, -2);
        for(i=0; i<10; i++) {
            t = 0.11111111f*i;
            t = 1-(t*t);
            MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
            HuPrcVSleep();
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
        MBCameraRotSetV(&camRot);
        MBModelHookReset(MBPlayerModelGet(playerNo));
        MBModelDispSet(mb3_Work.objMdlId[8], FALSE);
        MBPlayerMotionKill(playerNo, work->motId[0]);
        MBPlayerMotionKill(playerNo, work->motId[1]);
        MBPlayerMotionNoShiftSet(playerNo, 1, 0, 0, 0x40000001);
        MB3_CoinEffClose();
        MBEffKill(work->effId);
    } else {
        MBMotionNoSet(mdlId, mb3_Work.turuhasiMot[0], 0);
        MBMotionTimeSet(mdlId, MBMotionMaxTimeGet(mdlId));
        MBMotionSpeedSet(mdlId, -2);
        for(i=0; i<10; i++) {
            t = 0.11111111f*i;
            t = 1-(t*t);
            MBModelPosSet(mdlId, pos.x, pos.y+(100*t), pos.z);
            HuPrcVSleep();
        }
        WipeColorSet(0, 0, 0);
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
        while(WipeCheckEnd()) {
            HuPrcVSleep();
        }
    }
    MBModelDispSet(mdlId, FALSE);
    for(i=0; i<4; i++) {
        MBModelDispSet(MBPlayerModelGet(i), TRUE);
    }
    MBPlayerPosReset(playerNo);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    MBPlayerMotionNoShiftSet(playerNo, 1, 0, 0, 0x40000001);
    MBModelPosSetV(mb3_Work.objMdlId[2], &masuT->pos);
    MBCameraFocusMasuSet(masuId);
    MBCameraZoomSet(zoom);
    MBCameraSkipSet(0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 78 instructions, world03.s:6967-7053 */
static void MB3_TuruhasiEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
        }
        effP->count = 1;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        } else if(data->parManId < 10) {
            if(data->color.a >= 20) {
                data->color.a -= 20;
            }
        }
    }
}

/* 314 instructions, world03.s:7056-7375 */
static void MB3_TuruhasiEffCreate(MB3_PWORK *work)
{
    MBEFFECT *effP = Hu3DData[work->effId].hookData;
    MBEFFECTDATA *data;
    int i;
    int num;
    float rate;
    float speed;

    num = 3;
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time++;
        data->rot.z = 360*MBEffRandF();
        rate = MBEffRandF();
        data->color.r = 215;
        data->color.g = 255;
        data->color.b = 205;
        rate = work->rot.y;
        data->pos.x = 100*HuSin(rate);
        data->pos.y = 0;
        data->pos.z = 100*HuCos(rate);
        rate = 360*MBEffRandF();
        speed = 6.6666665f+(1.6666666f*(1.5f*MBEffRandF()));
        data->vel.x = speed*HuSin(rate);
        data->vel.z = speed*HuCos(rate);
        data->vel.y = 6.6666665f+(1.6666666f*(5*MBEffRandF()));
        data->parManId = 30+(0.3f*(60*MBEffRandF()));
        data->color.a = 128+(100*MBEffRandF());
        data->scale = 5+(40*MBEffRandF());
        data->animBank = 3*MBEffRandF();
        num--;
        if(num <= 0) {
            break;
        }
    }
}

/* 345 instructions, world03.s:7378-7746 */
static void MB3Ev_Asiba(int playerNo)
{
    Mtx mtx;
    u32 flag;
    MASU *masu;
    s16 masuId;
    int done;
    int mdlId;
    int upper;
    int num;
    int i;

    done = 0;
    masuId = GwPlayer[playerNo].masuId;
    masu = MBMasuGet(MASU_LAYER_DEFAULT, masuId);
    flag = (u16)masu->flag;
    upper = 0;
    mdlId = mb3_Work.objMdlId[6];
    if(masu->pos.y > 2000) {
        upper = 1;
        mdlId = mb3_Work.objMdlId[5];
    }
    MBMotionSpeedSet(mdlId, 0);
    MBMotionTimeSet(mdlId, 0);
    memset(&mb3_Work.pwork[0], 0, sizeof(mb3_Work.pwork));
    num = 0;
    for(i=0; i<4; i++) {
        if(masuId == GwPlayer[i].masuId) {
            mb3_Work.pwork[i].active = 1;
            mb3_Work.pwork[i].masuId = masuId;
            if(upper == 0) {
                mb3_Work.pwork[i].no = 3;
            }
            MBPlayerMotionNoShiftSet(i, 9, 0, 0, 0);
            num++;
        } else if(mb3_Work.unk02C == GwPlayer[i].masuId || mb3_Work.unk030 == GwPlayer[i].masuId) {
            MBModelDispSet(MBPlayerModelGet(i), FALSE);
        }
    }
    MB3_AsibaPlayerUpdate();
    HuPrcVSleep();
    MBPlayerPosFixFlagSet(FALSE);
    MBMotionSpeedSet(mb3_Work.objMdlId[5], 1);
    MBMotionSpeedSet(mb3_Work.objMdlId[6], 1);
    MBAudFXPlay(0x5E6);
    do {
        Hu3DModelObjMtxGet(MBModelIdGet(mb3_Work.objMdlId[5]), "takispl-tkhook", mtx);
        MBMasuMtxSet(mb3_Work.unk02C, mtx);
        Hu3DModelObjMtxGet(MBModelIdGet(mb3_Work.objMdlId[6]), "takispl-tkhook", mtx);
        MBMasuMtxSet(mb3_Work.unk030, mtx);
        MB3_AsibaPlayerUpdate();
        HuPrcVSleep();
        done = 1;
        for(i=0; i<4; i++) {
            if(mb3_Work.pwork[i].active == 1) {
                done = 0;
            }
        }
    } while(done == 0);
    MBPlayerRotSet(playerNo, 0, 0, 0);
    MBMotionSpeedSet(mb3_Work.objMdlId[5], 0);
    MBMotionTimeSet(mb3_Work.objMdlId[5], 0);
    MBMotionSpeedSet(mb3_Work.objMdlId[6], 0);
    MBMotionTimeSet(mb3_Work.objMdlId[6], 0);
    for(i=0; i<60; i++) {
        MB3_AsibaPlayerUpdate();
        HuPrcVSleep();
    }
    WipeColorSet(0, 0, 0);
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_CROSSCOPY, 1);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    Hu3DModelObjMtxGet(MBModelIdGet(mb3_Work.objMdlId[5]), "takispl-tkhook", mtx);
    MBMasuMtxSet(mb3_Work.unk02C, mtx);
    Hu3DModelObjMtxGet(MBModelIdGet(mb3_Work.objMdlId[6]), "takispl-tkhook", mtx);
    MBMasuMtxSet(mb3_Work.unk030, mtx);
    masuId = MBMasuFlagFind(MASU_LAYER_DEFAULT, MASU_FLAG_BIT(2), MASU_FLAG_BIT(2));
    for(i=0; i<4; i++) {
        MBModelDispSet(MBPlayerModelGet(i), TRUE);
        mb3_Work.pwork[i].state = -1;
        if(mb3_Work.pwork[i].active != 0) {
            GwPlayer[i].masuId = masuId;
            MBPlayerPosReset(i);
        }
    }
    MB3_AsibaPlayerUpdate();
    MBPlayerPosFixFlagSet(TRUE);
    MBPlayerPosFixCurr(masuId, 1);
    MBCameraSkipSet(0);
    MBCameraFocusMasuSet(masuId);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_CROSSCOPY, 30);
    while(WipeCheckEnd()) {
        HuPrcVSleep();
    }
    for(i=0; i<60; i++) {
        HuPrcVSleep();
    }
}

/* 572 instructions, world03.s:7749-8341 */
static void MB3_AsibaPlayerUpdate(void)
{
    Mtx mtxY;
    HuVecF vec;
    Mtx mtxX;
    MASU *masu;
    MB3_PWORK *work;
    int i;
    float time;
    float grav;

    for(work = &mb3_Work.pwork[0], i=0; i<4; i++, work++) {
        if(work->active == 0) {
            continue;
        }
        switch(work->state) {
            case 0:
                MBPlayerPosGet(i, &work->pos);
                MBPlayerRotGet(i, &work->rot);
                work->motId[0] = MBPlayerMotionCreate(i, CHARMOT_HSF_c000m1_376);
                work->motId[1] = MBPlayerMotionCreate(i, CHARMOT_HSF_c000m1_332);
                work->effId = mb3_Work.takiEff[i];
                masu = MBMasuGet(MASU_LAYER_DEFAULT, work->masuId);
                VECSubtract(&work->pos, &masu->pos, &vec);
                vec.y = 0.1f;
                if(VECMag(&vec) < 30.000002f) {
                    work->subNo = 1;
                } else if(vec.z >= 0) {
                    work->subNo = 0;
                    if(vec.x < 0) {
                        work->subNo = 1;
                    }
                } else {
                    work->subNo = 2;
                    if(vec.x < 0) {
                        work->subNo = 3;
                    }
                }
                masu = MBMasuGet(MASU_LAYER_DEFAULT, work->masuId);
                VECSubtract(&work->pos, &masu->pos, &work->vel);
                work->timer = mb3ev_AsibaYureTimeTbl[work->subNo];
                work->state++;
                break;

            case 1:
                masu = MBMasuGet(MASU_LAYER_DEFAULT, work->masuId);
                MTXMultVec(masu->matrix, &work->vel, &work->pos);
                work->timer--;
                if(work->timer != 0) {
                    break;
                }
                VECAdd(&masu->pos, &mb3ev_AsibaOfsTbl[work->subNo], &vec);
                vec.y = MB3_AsibaMinYGet(work->no, &vec);
                VECSubtract(&vec, &work->pos, &vec);
                time = 0.6f;
                grav = -1960;
                vec.x /= time;
                vec.z /= time;
                vec.y = (vec.y/time)-((0.5f*time)*grav);
                VECScale(&vec, &work->vel, 0.016666668f);
                work->unk1C = 60*time;
                work->unk20 = 0.016666668f*(0.016666668f*grav);
                MBPlayerMotionNoShiftSet(i, work->motId[0], 0, 8, 0);
                work->state++;
                /* falls through */

            case 2:
                work->vel.y += work->unk20;
                VECAdd(&work->pos, &work->vel, &work->pos);
                if((70+work->pos.y) > MB3_AsibaMinYGet(work->no, &work->pos)) {
                    break;
                }
                MBPlayerMotionNoShiftSet(i, work->motId[1], 0, 8, 0x40000001);
                MB3_AsibaPlayerEffCreate(work, 0);
                MBAudFXPlay(0x5DD);
                work->state++;
                break;

            case 3:
                work->vel.x *= 0.5f;
                work->vel.z *= 0.5f;
                work->vel.y += -2*work->unk20;
                if(work->vel.y < 0) {
                    work->vel.y *= 0.6f;
                }
                work->rot.x *= 0.95f;
                VECAdd(&work->pos, &work->vel, &work->pos);
                if(work->vel.y < 0) {
                    break;
                }
                if(work->pos.y < MB3_AsibaMinYGet(work->no, &work->pos)) {
                    break;
                }
                work->vel.x = 0;
                work->vel.y = 0;
                if(work->no >= 6) {
                    work->state = 7;
                    break;
                }
                work->state++;
                break;

            case 4:
                work->vel.z += 0.2f*(6.6666665f-work->vel.z);
                VECAdd(&work->pos, &work->vel, &work->pos);
                work->pos.y = MB3_AsibaMinYGet(work->no, &work->pos);
                work->rot.y += 3.0000002f;
                work->rot.x *= 0.95f;
                MB3_AsibaPlayerEffCreate(work, 1);
                if(work->pos.z < mb3ev_AsibaPosTbl[work->no+1].z) {
                    break;
                }
                MBPlayerMotionNoShiftSet(i, work->motId[0], 0, 16, 0);
                work->state++;
                break;

            case 5:
                work->vel.z *= 0.95f;
                work->vel.y += work->unk20;
                VECAdd(&work->pos, &work->vel, &work->pos);
                work->rot.y += 3.0000002f;
                work->rot.x -= 1;
                if(work->pos.y > mb3ev_AsibaPosTbl[work->no+2].y) {
                    break;
                }
                work->state++;
                break;

            case 6:
                work->vel.z *= 0.95f;
                work->vel.y += work->unk20;
                VECAdd(&work->pos, &work->vel, &work->pos);
                work->rot.y += 3.0000002f;
                work->rot.x += 1.5000001f;
                if((70+work->pos.y) > MB3_AsibaMinYGet(work->no+3, &work->pos)) {
                    break;
                }
                MBPlayerMotionNoShiftSet(i, work->motId[1], 0, 8, 0x40000001);
                work->state = 2;
                work->no += 3;
                MB3_AsibaPlayerEffCreate(work, 0);
                MBAudFXPlay(0x5DD);
                break;

            case 7:
                work->vel.z += 0.2f*(1.6666666f-work->vel.z);
                VECAdd(&work->pos, &work->vel, &work->pos);
                work->pos.y = MB3_AsibaMinYGet(work->no, &work->pos);
                work->rot.x *= 0.95f;
                work->active = 2;
                break;

            case -1:
                MBPlayerMotionNoShiftSet(i, 1, 0, 0, 0x40000001);
                MBPlayerMotionKill(i, work->motId[0]);
                MBPlayerMotionKill(i, work->motId[1]);
                work->rot.x = work->rot.y = work->rot.z = 0;
                break;
        }
        if(work->state >= 0) {
            MBPlayerPosSetV(i, &work->pos);
        }
        PSMTXRotRad(mtxY, 'Y', 0.017453292f*work->rot.y);
        PSMTXRotRad(mtxX, 'X', 0.017453292f*work->rot.x);
        PSMTXConcat(mtxX, mtxY, mtxY);
        Hu3DMtxRotGet(mtxY, &vec);
        MBPlayerRotSetV(i, &vec);
    }
}

/* 76 instructions, world03.s:8344-8423 */
static float MB3_AsibaMinYGet(int no, HuVecF *pos)
{
    HuVecF dir;
    float t;
    float y;

    VECSubtract(&mb3ev_AsibaPosTbl[no + 1], &mb3ev_AsibaPosTbl[no], &dir);
    if(fabsf2(dir.z) < 0.1f) {
        return mb3ev_AsibaPosTbl[no].y;
    }
    t = (pos->z - mb3ev_AsibaPosTbl[no].z) / dir.z;
    y = dir.y * t + mb3ev_AsibaPosTbl[no].y;
    return y;
}

/* 84 instructions, world03.s:8426-8519 */
static void MB3_TakiEffHook(HU3DMODEL *modelP, MBEFFECT *effP, Mtx matrix)
{
    MBEFFECTDATA *data;
    int i;

    if(effP->count == 0) {
        for(data = effP->data, i=0; i<effP->num; i++, data++) {
            data->scale = 0;
            data->color.a = 0;
        }
        effP->count = 1;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time == 0) {
            continue;
        }
        VECAdd(&data->pos, &data->vel, &data->pos);
        data->vel.y += -0.5444445f;
        data->parManId--;
        if(data->parManId <= 0) {
            data->time = 0;
            data->scale = 0;
            data->color.a = 0;
        } else if(data->parManId < 10) {
            if(data->color.a >= 20) {
                data->color.a -= 20;
            }
            data->scale += 5;
        }
    }
}

/* 670 instructions, world03.s:8522-9205 */
static void MB3_AsibaPlayerEffCreate(MB3_PWORK *work, int no)
{
    int num;
    MBEFFECT *effP = Hu3DData[work->effId].hookData;
    MBEFFECTDATA *data;
    int i;
    float rate;
    float radius;

    num = 2;
    if(no == 0) {
        num = 60;
    }
    for(data = effP->data, i=0; i<effP->num; i++, data++) {
        if(data->time != 0) {
            continue;
        }
        data->time++;
        data->rot.z = 360*MBEffRandF();
        rate = MBEffRandF();
        data->color.r = 190+(60*rate);
        data->color.g = 220+(35*rate);
        data->color.b = 205+(43*rate);
        switch(no) {
            case 0:
                data->vel.x = data->vel.z = 0;
                data->vel.y = 6.6666665f+(1.6666666f*(4*MBEffRandF()));
                data->parManId = 36+(0.3f*(60*MBEffRandF()));
                rate = 360*MBEffRandF();
                radius = 50+(100*(0.3f*MBEffRandF()));
                data->pos.x = work->pos.x+(radius*HuSin(rate));
                data->pos.z = work->pos.z+(radius*HuCos(rate));
                data->pos.y = work->pos.y;
                data->pos.y = MB3_AsibaMinYGet(work->no, &data->pos);
                data->pos.y -= 100*MBEffRandF();
                data->color.a = 180+(70*MBEffRandF());
                data->scale = 40+(50*MBEffRandF());
                break;

            case 1:
                data->vel.x = 1.6666666f*(0.3f*MBEffSRandF());
                data->vel.z = 1.6666666f*(2*MBEffRandF());
                data->vel.y = 3.3333333f+(1.6666666f*(2*MBEffRandF()));
                data->parManId = 18;
                rate = 180+(45*MBEffSRandF());
                data->pos.x = work->pos.x+(100*(0.8f*HuSin(rate)));
                data->pos.z = 30.000002f+(work->pos.z+(100*(0.3f*HuCos(rate))));
                data->pos.y = work->pos.y;
                data->pos.y = MB3_AsibaMinYGet(work->no, &data->pos);
                data->color.a = 180+(70*MBEffRandF());
                data->scale = 20+(40*MBEffRandF());
                break;
        }
        num--;
        if(num <= 0) {
            break;
        }
    }
}

/* 37 instructions, world03.s:9208-9248 */
static void MB3_CoinEffInit(void)
{
    MB3_COINEFF *coin = &mb3_Work.coinEff[0];
    int i;

    memset(coin, 0, sizeof(mb3_Work.coinEff));
    for(i=0; i<8; i++, coin++) {
        coin->mdlId = MBModelCreate(DATANUM(DATA_board, 2), NULL, TRUE);
        MBModelDispSet(coin->mdlId, FALSE);
        coin->unk20 = 1;
    }
}

/* 27 instructions, world03.s:9251-9282 */
static void MB3_CoinEffClose(void)
{
    MB3_COINEFF *coin = &mb3_Work.coinEff[0];
    int i;

    for(i=0; i<8; i++, coin++) {
        if(coin->mdlId != 0) {
            MBModelKill(coin->mdlId);
        }
        coin->mdlId = 0;
    }
}

/* 141 instructions, world03.s:9285-9431 */
static void MB3_CoinEffCreate(HuVecF *pos)
{
    MB3_COINEFF *coin = &mb3_Work.coinEff[0];
    int i;
    float angle;
    float speed;

    for(i=0; i<8; i++, coin++) {
        if(coin->unk00 != 0) {
            continue;
        }
        coin->unk00 = 60;
        MBModelDispSet(coin->mdlId, TRUE);
        coin->pos = *pos;
        angle = 360*MBEffRandF();
        speed = (1.6666666f*(1.3f*MBEffRandF()))+2.1666665f;
        coin->vel.x = speed*HuSin(angle);
        coin->vel.z = speed*HuCos(angle);
        coin->vel.y = 21.666666f;
        coin->rotY = 360*MBEffRandF();
        coin->unk20 = 0.2f;
        break;
    }
}

/* 77 instructions, world03.s:9434-9515 */
static void MB3_CoinEffUpdate(void)
{
    MB3_COINEFF *coin = &mb3_Work.coinEff[0];
    int i;

    for(i=0; i<8; i++, coin++) {
        if(coin->unk00 == 0) {
            continue;
        }
        VECAdd(&coin->pos, &coin->vel, &coin->pos);
        coin->vel.y += -0.5444445f;
        coin->rotY += 6.0000005f;
        coin->unk20 += 0.1f * (1 - coin->unk20);
        MBModelPosSetV(coin->mdlId, &coin->pos);
        MBModelRotSet(coin->mdlId, 0, coin->rotY, 0);
        MBModelScaleSet(coin->mdlId, coin->unk20, coin->unk20, coin->unk20);
        coin->unk00--;
        if(coin->unk00 == 0) {
            MBModelDispSet(coin->mdlId, FALSE);
        }
    }
}

/* 47 instructions, world03.s:9518-9567 */
static float MB3_DistRatioGet(HuVecF *vec1, HuVecF *vec2, HuVecF *vec3)
{
    float mag = VECMag(vec3);
    if(mag > 0) {
        mag = ((vec3->x*(vec1->x-vec2->x))+(vec3->y*(vec1->y-vec2->y))+(vec3->z*(vec1->z-vec2->z)))/mag;
    }
    return mag;
}

/* 30 instructions, world03.s:9570-9605 */
static unsigned int MB3Ev_BitGet(int outMask, unsigned int inMask)
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

/* 29 instructions, world03.s:9608-9642 */
static unsigned int MB3Ev_MasuFlagGet(int outMask, unsigned int inMask)
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
