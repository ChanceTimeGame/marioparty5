/*
 * m524dll -- "Vicious Vending", a 4-player minigame: four players crank a
 * prize machine against a five second clock, and what each one wins is decided
 * before the game starts by a shuffled slot table. Three slots pay coins (1, 10
 * and 20); the fourth drops a Thwomp on the player's head.
 *
 * RUNS. Reached through bootdll -> instdll -> m524dll -> resultdll -> bootdll,
 * with game.devBootOverlay=7 and game.devForceMinigame=38: the stage and all
 * four machines render, players crank, prizes are awarded, the weight squashes
 * its player, the overlay unlinks cleanly and resultdll pays out. Nothing on
 * stderr. This is also the first MG_TYPE_4P minigame to reach resultdll --
 * before it, m526dll (2VS2) was the only type that path had ever seen.
 *
 * WHY THIS ONE: stage 1 of games/mp5/ROADMAP.md wants one minigame of every
 * type a board can request. Only MG_TYPE_2VS2 exists (m526dll), so every other
 * type currently resolves through the cross-type substitution fallback in
 * mgcall.c. m524dll is MG_TYPE_4P and the cheapest unbuilt candidate in the
 * whole pool at 36KB.
 *
 * SIZE: 76 functions, 24464 bytes of .text, 6116 instructions. Only six carry
 * real names in upstream's symbol file (_prolog, _epilog, ObjectSetup,
 * MgCameraMoveEntry, MgFlowSet, MgFlowNext) -- the other seventy are fn_1_XXXX
 * and every name here is invented. Each function below carries the fn_1_XXXX
 * it came from so it can be checked against the asm.
 *
 * HOW TO WORK ON IT:
 *   ./games/mp5/gen_asm.sh m524Dll                       # reference asm
 *   ./games/mp5/verify_obj.sh m524Dll REL/m524Dll/m524   # proof
 *
 * _prolog and _epilog are not reproduced. They are REL bootstrap that the port
 * replaces: a port overlay is a host shared library whose only export is
 * ObjectSetup. m526dll does the same.
 *
 * VERIFIED, and how to read it. Compared per function against the object dtk
 * splits out of the real REL, this file is +2 instructions over 6076 in total;
 * eleven functions differ, none by more than eight instructions, and none by a
 * mnemonic, register or constant. The remaining eleven are listed at the bottom
 * of this comment.
 *
 * verify_obj.sh's own headline number is NOT the measure here. It diffs the two
 * disassemblies as flat line streams, and this file's function order does not
 * match the original's (see the note on the inlined-helper block below), so the
 * diff misaligns and reports ~1450 "differences" that are almost entirely that
 * misalignment. Compare per function instead, with games/mp5/fndiff.py:
 *
 *   REF=games/mp5/build/GP5E01_00/m524Dll/obj/REL/m524Dll/m524.o
 *   OURS=games/mp5/build/GP5E01_00/src/REL/m524Dll/m524.o
 *   ./games/mp5/fndiff.py sizes $REF
 *   diff <(./games/mp5/fndiff.py fn $REF fn_1_3554) \
 *        <(./games/mp5/fndiff.py fn $OURS MgObjManInit)
 *
 * An equal instruction count is not proof -- diff any function that does
 * arithmetic. Note also that since this file #includes REL/mgframe.h its object
 * has TWO .text sections, both at VMA 0, which is why the raw objdump-and-awk
 * recipe this comment used to carry no longer works: objdump labels every
 * address in both sections and prints each function twice. fndiff.py filters
 * symbols by the section readelf puts them in.
 *
 * Still off, and worth a look if anyone picks this up: ObjectSetup +8,
 * M524PlayerOrderInit +2, M524PlayerModeWait -6, M524PlayerModeGoal +1,
 * M524CoinCreate -4, M524CoinIdle -1, M524WeightFall -1, M524FlowCameraOut -3,
 * M524FlowExit +2, MgCameraMoveEntry +1, MgVecOrbit +3. Every one of these is
 * the same shape of thing: the original keeps one more (or one fewer) named
 * local than this file does, so an extra `mr`/`fmr` or stack store appears.
 * They are cosmetic, not behavioural.
 *
 * THE FRAMEWORK LIVES IN REL/mgframe.h. Forty-one of the functions below are
 * not this minigame at all -- they are the camera, flow, timer, pad and vector
 * block Hudson compiled into every overlay. They were decompiled here, then
 * lifted into that header once m570dll turned out to carry a character-for-
 * character copy of forty of them. The header is #included at the points this
 * file used to define them, so the emitted code is unchanged: after the
 * extraction all 74 functions in this object were byte-identical to the ones
 * the file produced before it. Read mgframe.h's own header for why it is a
 * header, and why it is included more than once.
 *
 * DEAD CODE, KEPT: the overlay ships an out-of-line copy of several functions
 * that the compiler also inlined at their single call site (M524ParManCreate,
 * MgObjManInit, MgLightCreate, MgPadStkMagGet, MgPadStkAngleGet,
 * MgFlowEntry, MgTimerParamSetEx, MgCameraShakeEntry), plus a debug free-camera
 * (MgDebugCameraCreate / MgDebugCameraMain, driven by holding Y) and a
 * block of vector helpers at the end of the file that nothing in this overlay
 * calls. They are reproduced because they are in the original object and their
 * absence would change the translation unit.
 *
 * NO datanum/m524.h: the archive at files/data/m524.bin carries no file names,
 * so every name for its 17 models would be invented and would then conflict
 * with upstream's if they ever publish one. The raw DATANUM(DATA_m524, n) is
 * used instead, with a comment at each table.
 */

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
#include "game/printfunc.h"
#include "game/mg/timer.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"
#include "datanum/char.h"
#include "datanum/effect.h"

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

/*
 * The minigame framework -- the camera, flow, timer and vector block that
 * every overlay compiles in. See REL/mgframe.h for why it is a header that
 * gets included more than once. This overlay's object carries the debug
 * camera's format strings, so it asks for the readout.
 */
#define MGF_DEBUG_READOUT
#include "REL/mgframe.h"

typedef struct M524Player_s {
    MGF_PLAYER_HEAD;           /* what MgPlayerConfSet fills in */
    float angle;
    float angleNext;
    int dir;
    float motTime;
    BOOL doneF;
    HuVecF signPos;
    HuVecF signVel;
    u16 payoutWait;
    HU3DPARMANID parManId;
    int coin;
    BOOL squashF;
    BOOL endF;
} M524_PLAYER;

/* One coin, or the one weight -- they share an object function and a work. */
typedef struct M524Coin_s {
    int unk00;
    HuVecF pos;
    HuVecF vel;
} M524_COIN;

/* --- forward declarations, asm address order --- */

static HU3DPARMANID M524ParManCreate(HuVecF *pos);
void ObjectSetup(void);
static void M524GameInit(void);
static void M524StageCreate(void);
static void M524PlayerOrderInit(void);
static void M524PlayerInit(OMOBJ *obj);
static void M524PlayerItemCreate(OMOBJ *obj);
static void M524PlayerPrizeCreate(OMOBJ *obj);
static void M524PlayerSignCreate(OMOBJ *obj);
static void M524PlayerMain(OMOBJ *obj);
static void M524PlayerModeEntry(OMOBJ *obj);
static void M524PlayerModeWait(OMOBJ *obj);
static float M524AngleDiffGet(float from, float to);
static void M524PlayerModeCrank(OMOBJ *obj);
static void M524PlayerModeTimeUp(OMOBJ *obj);
static void M524PlayerModeGoal(OMOBJ *obj);
static void M524PlayerModeResult(OMOBJ *obj);
static void M524PlayerModeSign(OMOBJ *obj);
static void M524PlayerModePrize(OMOBJ *obj);
static void M524CoinCreate(OMOBJ *playerObj, HuVecF *pos, int num);
static void M524CoinFall(OMOBJ *obj);
static void M524CoinInit(OMOBJ *obj);
static void M524CoinIdle(OMOBJ *obj);
static void M524WeightCreate(OMOBJ *playerObj, HuVecF *pos);
static void M524WeightFall(OMOBJ *obj);
static void M524PlayerModePayout(OMOBJ *obj);
static void M524PlayerModeWin(OMOBJ *obj);
static void M524PlayerModeEnd(OMOBJ *obj);
static void M524FlowOpening(OMOBJ *obj);
static void M524FlowPlay(OMOBJ *obj);
static void M524FlowCameraOut(OMOBJ *obj);
static void M524FlowFinish(OMOBJ *obj);
static void M524FlowExit(OMOBJ *obj);

/* ...and the framework's, from REL/mgframe.h */
#define MGF_S_DECL
#include "REL/mgframe.h"

/* --- .data --- */

/* the framework's OSReport strings and debug-camera formats */
#define MGF_S_DATA
#include "REL/mgframe.h"

static MGF_STAGELIGHT StageLight = {
    { -800.0f, 1500.0f, 800.0f },
    { 800.0f, -1500.0f, -800.0f },
    { 255, 255, 255, 255 }
};

/*
 * [0] the play view, [1] the wide result view, [2] scratch: M524FlowExit
 * overwrites it with the live view before pulling the camera away.
 */
static MGF_CAMERAVIEW CameraViewData[3] = {
    {
        1, 1,
        20.0f, 20.0f, 7000.0f,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 0.98f, -0.17f },
        { 0.0f, 150.0f, 0.0f },
        { -10.0f, 0.0f, 0.0f },
        2250.0f
    },
    {
        1, 1,
        20.0f, 20.0f, 7000.0f,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 300.0f, 0.0f },
        { -0.3f, 0.0f, 0.0f },
        2650.0f
    },
    {
        1, 0,
        20.0f, 20.0f, 7000.0f,
        { 0.0f, 0.0f, 0.0f },
        { 0.0f, 1.0f, 0.0f },
        { 0.0f, 500.0f, 0.0f },
        { -10.0f, 0.0f, 0.0f },
        5000.0f
    }
};

static HuVecF ShadowTarget = { 0.0f, 0.0f, 300.0f };

static MGFLOWFUNC FlowTbl[] = {
    MgFlowWipeWait,
    M524FlowOpening,
    MgFlowMgStart,
    MgFlowTimerCreate,
    M524FlowPlay,
    M524FlowCameraOut,
    M524FlowFinish,
    MgFlowMgFinish,
    M524FlowExit,
    MgFlowReturn,
    NULL
};

static float PlayerPosTbl[4] = { -300.0f, -100.0f, 100.0f, 300.0f };
static s16 PlayerPanTbl[4] = { 0x28, 0x38, 0x48, 0x58 };
static s16 CrankSeTbl[4] = { 0x754, 0x755, 0x756, 0x757 };
static s16 PrizeSeTbl[4] = { 0x758, 0x759, 0x75A, 0x75B };
static s16 SignSeTbl[4] = { 0x75C, 0x75D, 0x75E, 0x75F };
static s16 BurstSeTbl[4] = { 0x760, 0x761, 0x762, 0x763 };
static s16 WeightSeTbl[4] = { 0x764, 0x765, 0x766, 0x767 };

static HU3DPARMANPARAM ParManParam = {
    50, 0,
    20.0f,
    100.0f,
    0.0f,
    { 0.0f, 0.0f, 0.0f },
    1.0f,
    0.0f,
    400.0f,
    0.97f,
    1,
    { { 255, 255, 255, 255 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } },
    { { 255, 255, 255, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } }
};

/* Nine motions plus the terminator CharModelMotListCreate stops on. */
static unsigned int PlayerMotDataTbl[] = {
    CHARMOT_HSF_c000m1_300,
    CHARMOT_HSF_c000m1_301,
    CHARMOT_HSF_c000m1_313,
    CHARMOT_HSF_c000m1_314,
    CHARMOT_HSF_c000m1_356,
    CHAR_HSF_c000m1_375,
    CHARMOT_HSF_c000m1_327,
    CHARMOT_HSF_c000m1_357,
    CHARMOT_HSF_c000m1_306,
    0
};

/* --- .rodata tables --- */

/* files/data/m524.bin, by index: the stage, its shadow caster, and the props. */
static int StageMdlDataTbl[5] = {
    DATANUM(DATA_m524, 0x10),
    DATANUM(DATA_m524, 0x00),
    DATANUM(DATA_m524, 0x01),
    DATANUM(DATA_m524, 0x03),
    DATANUM(DATA_m524, 0x02)
};

/* One announcement sign per slot, and one prize per slot. */
static int SignMdlDataTbl[4] = {
    DATANUM(DATA_m524, 0x06),
    DATANUM(DATA_m524, 0x07),
    DATANUM(DATA_m524, 0x08),
    DATANUM(DATA_m524, 0x09)
};

static int PrizeMdlDataTbl[4] = {
    DATANUM(DATA_m524, 0x0A),
    DATANUM(DATA_m524, 0x0B),
    DATANUM(DATA_m524, 0x0C),
    DATANUM(DATA_m524, 0x0D)
};

/* The two slot layouts the shuffle starts from. */
static s16 PlayerOrderTbl[2][4] = {
    { 0, 1, 2, 3 },
    { 0, 0, 2, 3 }
};

/* Slot -> coins, written to each player's mgCoin by fn_1_6D8. */
static s16 CoinTbl[4] = { 0, 1, 10, 20 };

/* --- .bss --- */

static int OpeningStartF;      /* bss_0 */
static int TimerStartF;        /* bss_4 */
static OMOBJ *CameraMoveObj;   /* bss_8 */
static s16 JingleId;           /* bss_C */
static HU3DMODELID CoinMdlId;  /* bss_E */
static s16 PlayerOrder[4];     /* bss_10 */
static MGF_CAMERAVIEW *CameraWork; /* bss_18 */
static OMOBJ **PlayerObj;      /* bss_1C */
static OMOBJ *CameraObj;       /* bss_20 */
static HU3DMODELID StageMdlId[6]; /* bss_24 */
static int PlayF;              /* bss_30 -- written once by M524GameInit, never read */
/* DebugCameraStart (bss_34), MgMusicId (bss_7C) and objman (bss_80) */
#define MGF_S_BSS
#include "REL/mgframe.h"

/* ===== decoded functions, asm address order ===== */
/*
 * Small helpers that the compiler expands at their call sites. They are
 * gathered here, ahead of everything that uses them, because CodeWarrior
 * only inlines a function it has already seen -- defined lower down, as they
 * sit in the original object, every call would be emitted out of line and the
 * instruction stream would not match. Their out-of-line bodies are still
 * emitted, just earlier in the file than the original places them, so the
 * verify_obj.sh diff shows a shifted `bl` target for each.
 */
#define MGF_S_PLAYERCONF
#define MGF_S_PAD
#define MGF_S_FLOWCTL
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"
#define MGF_S_FLOWENTRY
#include "REL/mgframe.h"

/* ObjectSetup -- the overlay's only export. */
void ObjectSetup(void)
{
    HU3DLIGHTID lightId;
    MGF_FLOW *work;
    OMOBJ *obj;
    int i;

    MgObjManInit();
    M524GameInit();
    CameraWork = MgCameraCreate(&CameraViewData[0]);
    lightId = MgLightCreate(&StageLight);
    Hu3DShadowCreate(20.0f, 20.0f, 7000.0f);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&StageLight.pos, &CameraViewData[0].up, &ShadowTarget);
    Hu3DShadowSizeSet(320);
    M524StageCreate();
    omMakeGroupEx(objman, 0, 4);
    PlayerObj = omGetGroupMemberListEx(objman, 0);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(objman, 0x2000, 5, 9, 0, M524PlayerInit);
        PlayerObj[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M524_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    CameraObj = MgFlowEntry(FlowTbl);
    work = CameraObj->data;
    MgTimerParamSetEx(CameraObj, MGTIMER_TYPE_NORMAL, 5, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
}


/* fn_1_A0 -- create the dust/spark particle manager at a world position. */
static HU3DPARMANID M524ParManCreate(HuVecF *pos)
{
    void *data = HuDataSelHeapReadNum(DATANUM(DATA_effect, 2), HU_MEMNUM_OVL, HEAP_MODEL);
    ANIMDATA *anim = HuSprAnimRead(data);
    HU3DPARMANID parManId = Hu3DParManCreate(anim, 100, &ParManParam);
    Hu3DParManRotSet(parManId, 0.0f, 0.0f, 0.0f);
    Hu3DParManPosSet(parManId, pos->x, pos->y, pos->z);
    Hu3DModelLayerSet(Hu3DParManModelIDGet(parManId), 2);
    return parManId;
}

/* fn_1_438 -- one-shot game state reset, called from ObjectSetup. */
static void M524GameInit(void)
{
    M524PlayerOrderInit();
    PlayF = 0;
    JingleId = -1;
}

/* fn_1_478 -- load the stage models. */
static void M524StageCreate(void)
{
    int i;
    for(i=0; i<5; i++) {
        StageMdlId[i] = Hu3DModelCreateData(StageMdlDataTbl[i]);
        Hu3DModelAttrSet(StageMdlId[i], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(StageMdlId[i], HU3D_MOTATTR_PAUSE);
        Hu3DModelPosSet(StageMdlId[i], 0.0f, 0.0f, 0.0f);
        switch(i) {
            case 0:
                Hu3DCameraMotionOn(StageMdlId[i], (u16)CameraViewData[0].no);
                Hu3DModelPosSet(StageMdlId[i], PlayerPosTbl[1], 0.0f, 200.0f);
                break;
            case 1:
                Hu3DModelShadowMapSet(StageMdlId[i]);
                break;
            case 4:
                Hu3DModelAttrReset(StageMdlId[i], HU3D_MOTATTR_PAUSE);
                Hu3DModelAttrSet(StageMdlId[i], HU3D_MOTATTR_LOOP);
                break;
        }
        Hu3DModelRotSet(StageMdlId[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrReset(StageMdlId[i], HU3D_ATTR_DISPOFF);
    }
    CoinMdlId = Hu3DModelCreateData(DATANUM(DATA_m524, 0x0E));
    Hu3DModelAttrSet(CoinMdlId, HU3D_ATTR_DISPOFF);
}

/* fn_1_6D8 -- pick each player's slot, then set its coins in mgCoin (GwPlayer
 * +0x2A; this was coinBattle before the 06ea9f6c GWPLAYER layout fix). */
static void M524PlayerOrderInit(void)
{
    s16 i;
    s16 j;
    s16 tmp;
    int no = frandmod(2);
    for(i=0; i<4; i++) {
        PlayerOrder[i] = PlayerOrderTbl[no][i];
    }
    for(i=0; i<4; i++) {
        j = frandmod(4);
        tmp = PlayerOrder[i];
        PlayerOrder[i] = PlayerOrder[j];
        PlayerOrder[j] = tmp;
    }
    for(i=0; i<4; i++) {
        GwPlayer[i].mgCoin = CoinTbl[PlayerOrder[i]];
    }
}

/* fn_1_848 -- per-player object constructor (omAddObjEx's first call). */
static void M524PlayerInit(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    s16 no = obj->work[0];
    HU3DMODELID modelId;
    s16 charNo;

    MgPlayerConfSet((MGFPLAYER *)work, no);
    work->motTime = 0.0f;
    work->dir = 0;
    work->doneF = FALSE;
    work->squashF = FALSE;
    work->endF = FALSE;
    work->coin = -1;

    charNo = work->charNo;
    modelId = CharModelMotListCreate(charNo, 2, PlayerMotDataTbl, obj->mtnId);
    obj->mdlId[0] = modelId;
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharModelAttrSet(charNo, HU3D_MOTATTR_PAUSE);
    CharMotionSet(charNo, obj->mtnId[0]);
    CharEffectLayerSet(2);

    work->pos.x = PlayerPosTbl[work->no]-70.0f;
    work->pos.y = 0.0f;
    work->pos.z = 320.0f;
    work->rot.x = 0.0f;
    work->rot.y = 90.0f;
    work->rot.z = 0.0f;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);

    M524PlayerItemCreate(obj);
    M524PlayerPrizeCreate(obj);
    M524PlayerSignCreate(obj);
    CharModelVoicePanSet(work->charNo, PlayerPanTbl[work->no]);
    obj->work[0] = 0;
    obj->objFunc = M524PlayerMain;
}

/* fn_1_AD0 -- the crank/handle model pair that stands in front of a player. */
static void M524PlayerItemCreate(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    HU3DMODELID modelId;

    modelId = Hu3DModelCreateData(DATANUM(DATA_m524, 4));
    obj->mdlId[1] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelPosSet(modelId, PlayerPosTbl[work->no], 0.0f, 200.0f);
    Hu3DMotionStartEndSet(modelId, 0.0f, 60.0f);

    modelId = Hu3DModelCreateData(DATANUM(DATA_m524, 5));
    obj->mdlId[2] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(modelId, PlayerPosTbl[work->no]-6.0f, 75.0f, 238.0f);
}

/* fn_1_C24 -- the prize model, chosen by this player's shuffled slot. */
static void M524PlayerPrizeCreate(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int dataNum = PrizeMdlDataTbl[PlayerOrder[work->no]];
    HU3DMODELID modelId = Hu3DModelCreateData(dataNum);
    obj->mdlId[3] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(modelId, PlayerPosTbl[work->no], 0.0f, 200.0f);
}

/* fn_1_D08 -- the banner/sign that drops in above the player. */
static void M524PlayerSignCreate(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int dataNum = SignMdlDataTbl[PlayerOrder[work->no]];
    HU3DMODELID modelId = Hu3DModelCreateData(dataNum);
    obj->mdlId[4] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
    work->signPos.x = PlayerPosTbl[work->no];
    work->signPos.y = 1000.0f;
    work->signPos.z = -400.0f;
    work->signVel.x = 0.0f;
    work->signVel.y = -40.0f;
    work->signVel.z = 0.0f;
    Hu3DModelPosSetV(modelId, &work->signPos);
}

/* fn_1_E2C -- the per-player object function, installed by M524PlayerInit. */
static void M524PlayerMain(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int no = work->no;

    switch(work->mode) {
        case 0:
            M524PlayerModeEntry(obj);
            break;
        case 1:
            if(MgFlowCheck(CameraObj, 3)) {
                work->mode = 2;
            }
            break;
        case 2:
            M524PlayerModeWait(obj);
            if(work->mode != 2) {
                obj->work[0] = 0;
                obj->work[1] = -1;
            }
            break;
        case 3:
            M524PlayerModeCrank(obj);
            if(work->mode != 3) {
                obj->work[0] = 0;
            }
            break;
        case 4:  M524PlayerModeTimeUp(obj);  break;
        case 5:  M524PlayerModeGoal(obj);    break;
        case 6:  M524PlayerModeResult(obj);  break;
        case 7:  M524PlayerModeSign(obj);    break;
        case 8:  M524PlayerModePrize(obj);   break;
        case 9:  M524PlayerModePayout(obj);  break;
        case 10: M524PlayerModeWin(obj);     break;
        case 11: M524PlayerModeEnd(obj);     break;
    }
}

/* fn_1_F84 -- mode 0: walk in from off-screen, then hand over to mode 1. */
static void M524PlayerModeEntry(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;

    if(obj->work[0] == 0) {
        if(!MgFlowCheck(CameraObj, 2)) {
            return;
        }
        Hu3DModelAttrReset(obj->mdlId[1], HU3D_MOTATTR_PAUSE);
        CharModelAttrReset(work->charNo, HU3D_MOTATTR_LOOP);
        CharMotionSet(work->charNo, obj->mtnId[2]);
        CharMotionStartEndSet(work->charNo, 61.0f, 120.0f);
        CharMotionTimeSet(work->charNo, 61.0f);
        CharMotionShiftSet(work->charNo, obj->mtnId[1], 0.0f, 60.0f, HU3D_MOTATTR_LOOP);
    }
    obj->work[0]++;
    work->rot.y += 1.5f;
    work->pos.x = (1.1666666f*obj->work[0])+(PlayerPosTbl[work->no]-70.0f);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    if(obj->work[0] == 60) {
        work->pos.x = PlayerPosTbl[work->no];
        omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
        CharModelAttrSet(work->charNo, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(work->charNo, obj->mtnId[4], 0.0f, 15.0f, HU3D_MOTATTR_PAUSE);
        obj->work[0] = 0;
        work->mode = 1;
    }
}

/* fn_1_11D4 -- mode 2: wait for the stick (or the COM's timer) to start a crank. */
static void M524PlayerModeWait(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int no = work->no;
    MGF_FLOW *camera = CameraObj->data;

    if(MgTimerDoneCheck(camera->timer)) {
        work->mode = 4;
        return;
    }
    if(work->comF) {
        if(obj->work[0] == 0) {
            obj->work[0] = 1;
            obj->work[1] = frandmod(20)*5;
        }
        if(obj->work[1] == 0) {
            work->angle = 0.0f;
            obj->work[0] = 0;
            work->mode = 3;
        }
        obj->work[1]--;
        return;
    }
    if(MgPadStkMagGet(work->padNo) < 50.0f) {
        return;
    }
    work->angle = MgPadStkAngleGet(work->padNo);
    work->mode = 3;
}

/* fn_1_1568 -- signed shortest angular difference, in degrees. */
static float M524AngleDiffGet(float from, float to)
{
    float diff;
    if(to > 180.0f) {
        to -= 360.0f;
    }
    if(from > 180.0f) {
        from -= 360.0f;
    }
    diff = to-from;
    if(diff > 180.0f) {
        diff -= 360.0f;
    }
    if(diff < -180.0f) {
        diff += 360.0f;
    }
    return diff;
}

/* fn_1_161C -- mode 3: crank. Stick rotation drives the character's motion
 * time directly; one full revolution of motion finishes the player's run. */
static void M524PlayerModeCrank(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int no = work->no;
    s16 padNo = work->padNo;
    MGF_FLOW *camera = CameraObj->data;
    float mag;
    float diff;
    float maxTime;

    if(MgTimerDoneCheck(camera->timer)) {
        work->mode = 4;
        return;
    }
    if(work->comF) {
        mag = 20.0f;
        work->angleNext = work->angle+(frandmod(150)/10.0f);
    } else {
        mag = MgPadStkMagGet(padNo);
        work->angleNext = MgPadStkAngleGet(padNo);
    }
    if(mag < 10.0f) {
        work->mode = 2;
        return;
    }
    diff = M524AngleDiffGet(work->angle, work->angleNext);
    work->angle = work->angleNext;
    if(work->dir == 0) {
        if(fabs(diff) < 10.0) {
            return;
        }
        if(diff < 0.0f) {
            work->dir = -1;
            work->motTime = CharMotionMaxTimeGet(work->charNo);
        } else {
            work->dir = 1;
        }
    } else {
        if(work->dir*diff <= 0.0f) {
            return;
        }
    }
    if(fabs(diff) >= 50.0) {
        return;
    }
    maxTime = CharMotionMaxTimeGet(work->charNo);
    work->motTime += diff/(360.0f/maxTime);
    if(obj->work[1] == -1) {
        obj->work[1] = HuAudFXPlay(CrankSeTbl[work->no]);
    } else if(!HuAudFXStatusGet(obj->work[1])) {
        obj->work[1] = -1;
    }
    if((work->dir == 1 && work->motTime >= maxTime) || (work->dir == -1 && work->motTime <= 0.0f)) {
        work->motTime = 0.0f;
        CharMotionTimeSet(work->charNo, maxTime);
        Hu3DMotionTimeSet(obj->mdlId[2], 60.0f);
        Hu3DModelAttrReset(obj->mdlId[1], HU3D_MOTATTR_LOOP);
        work->mode = 5;
    } else {
        CharMotionTimeSet(work->charNo, work->motTime);
        Hu3DMotionTimeSet(obj->mdlId[2], work->motTime);
    }
}

/* fn_1_1CBC -- mode 4: the timer ran out mid-crank; play the swing out. */
static void M524PlayerModeTimeUp(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    if(obj->work[0] == 0) {
        CharModelAttrReset(work->charNo, HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(obj->mdlId[2], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(obj->mdlId[1], HU3D_MOTATTR_LOOP);
        if(work->dir == -1) {
            CharModelAttrSet(work->charNo, HU3D_MOTATTR_REV);
            Hu3DModelAttrSet(obj->mdlId[2], HU3D_MOTATTR_REV);
        }
        obj->work[0] = 1;
        obj->work[2] = 0;
    }
    if(obj->work[1] != -1) {
        if(!HuAudFXStatusGet(obj->work[1])) {
            obj->work[1] = -1;
        }
    }
    if(obj->work[1] == -1) {
        obj->work[1] = HuAudFXPlay(CrankSeTbl[work->no]);
    }
    if(CharMotionEndCheck(work->charNo)) {
        obj->work[0] = 0;
        work->mode = 5;
    }
    obj->work[2]++;
}

/* fn_1_1DF8 -- mode 5: the crank came round; reveal the prize. */
static void M524PlayerModeGoal(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    switch(obj->work[0]) {
        case 0:
            Hu3DMotionStartEndSet(obj->mdlId[1], 60.0f, 100.0f);
            Hu3DMotionTimeSet(obj->mdlId[1], 60.0f);
            Hu3DModelAttrReset(obj->mdlId[3], HU3D_ATTR_DISPOFF);
            Hu3DModelAttrReset(obj->mdlId[3], HU3D_MOTATTR_PAUSE);
            obj->work[0] = 1;
            obj->work[1] = 55;
            break;
        case 1:
            if(obj->work[1] == 0) {
                break;
            }
            obj->work[1]--;
            if(obj->work[1] == 13) {
                HuAudFXPlay(PrizeSeTbl[work->no]);
            }
            if(obj->work[1] == 0) {
                CharMotionShiftSet(work->charNo, obj->mtnId[5], 0.0f, 30.0f, HU3D_MOTATTR_NONE);
                obj->work[0] = 2;
                obj->work[1] = 60;
            }
            break;
        case 2:
            obj->work[1]--;
            if(obj->work[1] == 0) {
                CharMotionShiftSet(work->charNo, obj->mtnId[0], 0.0f, 20.0f, HU3D_MOTATTR_LOOP);
                work->doneF = TRUE;
                obj->work[0] = obj->work[1] = 0;
                work->mode = 6;
            }
            break;
    }
}

/* fn_1_1FB8 -- mode 6: hold until the camera calls the result, then drop the sign. */
static void M524PlayerModeResult(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    if(!MgFlowCheck(CameraObj, 6)) {
        return;
    }
    if(obj->work[0] == 0) {
        obj->work[0] = 1;
        obj->work[1] = work->no*40;
    }
    if(obj->work[1] == 0) {
        obj->work[0] = 0;
        HuAudFXPlay(SignSeTbl[work->no]);
        Hu3DModelAttrReset(obj->mdlId[4], HU3D_ATTR_DISPOFF);
        work->mode = 7;
    } else {
        obj->work[1]--;
    }
}

/* fn_1_20A0 -- mode 7: the sign swings down into shot. */
static void M524PlayerModeSign(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    if(Hu3DMotionEndCheck(obj->mdlId[4])) {
        work->mode = 8;
        return;
    }
    if(Hu3DMotionTimeGet(obj->mdlId[4]) > 60.0f) {
        return;
    }
    if(work->signPos.y <= 760.0f && 0.0f == work->signVel.z) {
        work->signPos.y = 760.0f;
        work->signVel.y = -5.2f;
        work->signVel.z = 12.333333f;
        Hu3DModelAttrReset(obj->mdlId[4], HU3D_MOTATTR_PAUSE);
    }
    work->signPos.y += work->signVel.y;
    work->signPos.z += work->signVel.z;
    Hu3DModelPosSetV(obj->mdlId[4], &work->signPos);
}

/* fn_1_21BC -- mode 8: the sign bursts and pays out. Slot 0 is the booby prize:
 * a weight drops on the player instead of coins. */
static void M524PlayerModePrize(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    HuVecF pos;

    pos.x = work->signPos.x;
    pos.y = work->signPos.y;
    pos.z = work->signPos.z+150.0f;
    work->parManId = M524ParManCreate(&pos);
    Hu3DParManTimeLimitSet(work->parManId, 1);
    Hu3DModelKill(obj->mdlId[4]);
    HuAudFXPlay(BurstSeTbl[work->no]);
    switch(PlayerOrder[work->no]) {
        case 0:
            work->coin = 1;
            M524WeightCreate(obj, &work->signPos);
            break;
        case 1:
            work->coin = 1;
            M524CoinCreate(obj, &work->signPos, work->coin);
            break;
        case 2:
            work->coin = 10;
            M524CoinCreate(obj, &work->signPos, work->coin);
            break;
        case 3:
            work->coin = 20;
            M524CoinCreate(obj, &work->signPos, work->coin);
            break;
    }
    CharMotionShiftSet(work->charNo, obj->mtnId[6], 0.0f, 10.0f, HU3D_MOTATTR_NONE);
    work->payoutWait = 10;
    work->mode = 9;
}

/* fn_1_23C8 -- scatter `num` coin objects around `pos`. */
static void M524CoinCreate(OMOBJ *playerObj, HuVecF *pos, int num)
{
    M524_PLAYER *player = playerObj->data;
    int i;
    for(i=0; i<num; i++) {
        OMOBJ *obj = omAddObjEx(objman, 0x2000, 1, 0, OM_GRP_NONE, M524CoinInit);
        M524_COIN *work;
        HU3DMODELID modelId;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M524_COIN), HU_MEMNUM_OVL);
        obj->work[0] = player->no;
        obj->work[1] = i;
        obj->work[2] = i*3;
        work = obj->data;
        modelId = Hu3DModelLink(CoinMdlId);
        obj->mdlId[0] = modelId;
        work->pos.x = (pos->x+frandmod(80))-40.0f;
        work->pos.y = (pos->y+frandmod(200))-100.0f;
        work->pos.z = (pos->z+frandmod(100))-50.0f;
        work->vel.x = 0.0f;
        work->vel.y = 0.0f;
        work->vel.z = 0.0f;
        omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
        omSetSca(obj, 1.0f, 1.0f, 1.0f);
        Hu3DMotionTimeSet(modelId, frandmod(58));
        Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelShadowSet(modelId);
    }
}

/* fn_1_2630 -- a coin falling onto its owner. */
static void M524CoinFall(OMOBJ *obj)
{
    M524_COIN *work = obj->data;
    M524_PLAYER *player;
    HuVecF pos;

    if(obj->work[2] != 0) {
        obj->work[2]--;
        return;
    }
    player = PlayerObj[obj->work[0]]->data;
    work->vel.y += 1.96f;
    work->pos.y -= work->vel.y;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    if(work->pos.y <= CharModelHeightGet(player->charNo)) {
        pos.x = player->pos.x;
        pos.y = work->pos.y;
        pos.z = player->pos.z;
        HuAudFXPlayPan(7, PlayerPanTbl[player->no]);
        CharEffectCoinGlowCreate(CameraViewData[0].no, &pos);
        player->coin--;
        obj->objFunc = M524CoinIdle;
    }
}

/* fn_1_2760 -- a payout object's first frame: wait out the player's delay,
 * then branch on whether this is the weight or a coin. */
static void M524CoinInit(OMOBJ *obj)
{
    M524_PLAYER *player = PlayerObj[obj->work[0]]->data;
    if(player->payoutWait != 0) {
        return;
    }
    if(PlayerOrder[player->no] == 0) {
        obj->objFunc = M524WeightFall;
    } else {
        obj->objFunc = M524CoinFall;
    }
}

/* fn_1_27D8 -- a payout object that has landed. Coins are thrown away; the
 * weight stays put and re-rolls its animation once. */
static void M524CoinIdle(OMOBJ *obj)
{
    M524_PLAYER *player = PlayerObj[obj->work[0]]->data;
    if(PlayerOrder[player->no] != 0) {
        Hu3DModelKill(obj->mdlId[0]);
        omDelObjEx(objman, obj);
        return;
    }
    if(obj->work[1] == 0) {
        return;
    }
    obj->work[1]--;
    if(obj->work[1] == 0) {
        Hu3DMotionTimeSet(obj->mdlId[0], (s32)frandmod(150)+50);
    }
}

/* fn_1_28C8 -- the booby prize: one weight, spawned above the player. */
static void M524WeightCreate(OMOBJ *playerObj, HuVecF *pos)
{
    M524_PLAYER *player = playerObj->data;
    HU3DMODELID modelId = Hu3DModelCreateData(DATANUM(DATA_m524, 0x0F));
    OMOBJ *obj = omAddObjEx(objman, 0x2000, 1, 0, OM_GRP_NONE, M524CoinInit);
    M524_COIN *work;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M524_COIN), HU_MEMNUM_OVL);
    obj->work[0] = player->no;
    work = obj->data;
    obj->mdlId[0] = modelId;
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_PAUSE);
    Hu3DModelShadowSet(modelId);
    work->pos.x = pos->x;
    work->pos.y = pos->y-100.0f;
    work->pos.z = pos->z;
    work->vel.x = 0.0f;
    work->vel.y = 0.0f;
    work->vel.z = 0.0f;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
}

/* fn_1_29F4 -- the weight falling: squashes the player on the way past, then
 * lands, kicks up smoke and shakes the camera. */
static void M524WeightFall(OMOBJ *obj)
{
    M524_COIN *work = obj->data;
    s16 no = obj->work[0];
    OMOBJ *playerObj = PlayerObj[no];
    M524_PLAYER *player = PlayerObj[no]->data;
    MGF_CAMERAVIEW *view;
    OMOBJ *shakeObj;
    MGF_CAMERAVIEW *shake;

    work->vel.y += 1.96f;
    work->pos.y -= work->vel.y;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    if(work->pos.y < CharModelHeightGet(player->charNo) && player->squashF == 0) {
        CharModelAttrReset(player->charNo, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(player->charNo, playerObj->mtnId[7], 0.0f, 5.0f, HU3D_MOTATTR_NONE);
        Hu3DMotionShiftStartEndSet(playerObj->mdlId[0], 0.0f, 30.0f);
        Hu3DModelAttrReset(playerObj->mdlId[1], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrReset(playerObj->mdlId[1], HU3D_MOTATTR_LOOP);
        Hu3DMotionStartEndSet(playerObj->mdlId[1], 101.0f, 105.0f);
        Hu3DMotionTimeSet(playerObj->mdlId[1], 101.0f);
        player->squashF = 1;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    if(work->pos.y > 0.0f) {
        return;
    }
    work->pos.y = 0.0f;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    player->coin--;
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    work->pos.z += 150.0f;
    CharEffectSmokeCreate(CameraViewData[0].no, &work->pos);
    view = CameraWork;
    shakeObj = omAddObjEx(objman, 0x2000, 0, 0, OM_GRP_NONE, MgCameraShakeMain);
    shakeObj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MGF_CAMERAVIEW), HU_MEMNUM_OVL);
    shake = shakeObj->data;
    shakeObj->work[0] = 15;
    shakeObj->work[1] = 5;
    *shake = *view;
    (shakeObj)->work[2] = (u32)(view);
    omVibrate(player->no, 15, 12, 0);
    HuAudFXPlayPan(0x2C1, PlayerPanTbl[player->no]);
    HuAudFXPlay(WeightSeTbl[player->no]);
    obj->work[1] = 50;
    obj->objFunc = M524CoinIdle;
}

/* fn_1_2D30 -- mode 9: hold until every player's payout has landed. */
static void M524PlayerModePayout(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    int i;
    if(work->payoutWait != 0) {
        work->payoutWait--;
    }
    for(i=0; i<4; i++) {
        work = PlayerObj[i]->data;
        if(work->coin != 0) {
            return;
        }
    }
    work = obj->data;
    work->endF = TRUE;
    work->mode = 10;
}

/* fn_1_2DB4 -- mode 10: winners turn on the spot and cheer. */
static void M524PlayerModeWin(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    if(PlayerOrder[work->no] == 0) {
        work->mode = 11;
        return;
    }
    if(obj->work[0] == 0) {
        obj->work[0] = 1;
        CharModelAttrReset(work->charNo, HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(work->charNo, obj->mtnId[3], 1.0f, 20.0f, HU3D_MOTATTR_NONE);
        Hu3DMotionShiftStartEndSet(obj->mdlId[0], 1.0f, 60.0f);
        return;
    }
    work->rot.y -= 3.0f;
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    if(CharMotionShiftIDGet(work->charNo) == -1 && CharMotionEndCheck(work->charNo)) {
        obj->work[0] = 0;
        work->mode = 11;
    }
}

/* fn_1_2EEC -- mode 11: the last pose, held until the overlay leaves. */
static void M524PlayerModeEnd(OMOBJ *obj)
{
    M524_PLAYER *work = obj->data;
    if(!MgFlowCheck(CameraObj, 8)) {
        return;
    }
    if(PlayerOrder[work->no] != 0) {
        CharMotionShiftSet(work->charNo, obj->mtnId[8], 0.0f, 20.0f, HU3D_MOTATTR_NONE);
    }
    work->mode = 12;
}

/* --- game flow steps, in the order of the table at .data:0x1EC --- */

/* fn_1_2FB0 -- step 1: run the stage's own camera motion as the opening. */
static void M524FlowOpening(OMOBJ *obj)
{
    if(OpeningStartF == 0) {
        Hu3DCameraMotionStart(StageMdlId[0], (u16)CameraViewData[0].no);
        Hu3DModelAttrReset(StageMdlId[0], HU3D_MOTATTR_PAUSE);
        MgMusicId = HuAudSStreamPlay(0x12);
        HuAudFXPlay(0x753);
        OpeningStartF = 1;
    }
    if(Hu3DMotionEndCheck(StageMdlId[0])) {
        Hu3DModelKill(StageMdlId[0]);
        MgFlowNext(obj);
    }
}

/* fn_1_30BC -- step 4: start the clock once everyone is cranking, and hold
 * the flow until all four have finished their crank. */
static void M524FlowPlay(OMOBJ *obj)
{
    MGF_FLOW *work;
    int i;
    if(TimerStartF == 0) {
        for(i=0; i<4; i++) {
            M524_PLAYER *player = PlayerObj[i]->data;
            if(player->mode < 5) {
                break;
            }
        }
        if(i == 4) {
            work = obj->data;
            if(work->timer->stopF == 0) {
                work->timer->stopF = TRUE;
                work->timer->mode = MGTIMER_MODE_ON;
            }
            TimerStartF = 1;
        }
    }
    for(i=0; i<4; i++) {
        M524_PLAYER *player = PlayerObj[i]->data;
        if(player->doneF == 0) {
            return;
        }
    }
    MgFlowNext(obj);
}

/* fn_1_31EC -- step 5: pull the camera back to the wide result view. */
static void M524FlowCameraOut(OMOBJ *obj)
{
    MGF_CAMERAMOVE *move;
    if(CameraMoveObj == NULL) {
        CameraMoveObj = MgCameraMoveEntry(CameraWork, &CameraViewData[1], 30.0f);
    }
    move = CameraMoveObj->data;
    if(!(move->stat & 2)) {
        omDelObjEx(objman, CameraMoveObj);
        MgFlowNext(obj);
    }
}

/* fn_1_32F0 -- step 6: everyone has been paid; fade the music out. */
static void M524FlowFinish(OMOBJ *obj)
{
    int i;
    for(i=0; i<4; i++) {
        M524_PLAYER *player = PlayerObj[i]->data;
        if(player->endF == 0) {
            return;
        }
    }
    HuAudSStreamFadeOut(MgMusicId, 100);
    MgFlowNext(obj);
}

/* fn_1_33B4 -- step 8: the jingle, the wipe out, and the long camera pull
 * that plays under it. */
static void M524FlowExit(OMOBJ *obj)
{
    if(obj->work[0] == 0) {
        obj->work[0] = 1;
        obj->work[1] = 210;
        JingleId = HuAudJinglePlay(0x79);
    }
    obj->work[1]--;
    if(obj->work[1] != 0) {
        return;
    }
    WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_NORMAL, 60);
    CameraWork->mode = 0;
    CameraViewData[2] = *CameraWork;
    MgCameraAngleApply(&CameraViewData[2]);
    CameraViewData[2].pos.z += 1000.0f;
    CameraViewData[2].target.y += 400.0f;
    CameraViewData[2].pos.y -= 200.0f;
    MgCameraMoveEntry(CameraWork, &CameraViewData[2], 120.0f);
    MgFlowNext(obj);
}


/* the framework camera: the view model, the interpolator, the shake and the
 * debug free-camera. */
#define MGF_S_CAMERA
#include "REL/mgframe.h"


/* the flow object and the steps every overlay shares. */
#define MGF_S_FLOWMAIN
#define MGF_S_FLOWSTEP
#include "REL/mgframe.h"


/*
 * The vector helpers close the object out. Nothing in this overlay calls
 * them; they are in the shipped REL, so they are compiled in.
 */
#define MGF_S_MATH
#include "REL/mgframe.h"
