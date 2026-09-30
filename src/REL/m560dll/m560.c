/*
 * m560dll -- a MG_TYPE_KUPA minigame: Bowser holds up a sign, all four players
 * race to press the button it names, eight signs each. Get one wrong and you
 * freeze for half a second; finish all eight and you walk clear of the arena.
 * Anyone still on it when the last finisher leaves gets breathed on. Winners
 * take ten coins.
 *
 * COMPLETE. Both translation units, 62 functions in m560.c and 7 in effect.c,
 * 7,414 instructions, every one checked per function against the objects dtk
 * splits out of the real REL. effect.c is byte-identical. m560.c is +1
 * instruction over 6,523: fifty-six of its sixty-two functions are line for
 * line identical and the other six differ only in which register or stack slot
 * the compiler picked -- for five of them the instruction multiset is provably
 * unchanged once registers and stack displacements are normalised, and the
 * sixth, M560KupaMain, is one instruction and four memory-versus-register
 * locals away in 887.
 *
 * WHY THIS ONE: stage 1 of games/mp5/ROADMAP.md wants one minigame of every
 * type a board can request. MG_TYPE_KUPA has three candidates and m560dll is
 * the cheapest at 45 KB / 7,611 instructions.
 *
 * SHAPE. Built on the DOL's sequence manager (game/mg/seqman.h) like m570dll,
 * not on the hand-rolled flow object m524dll uses: ObjectSetup hands
 * MgSeqCreatePrio an MGSEQ_PARAM whose seven hooks are the whole game. It does
 * NOT use the REL/mgframe.h framework -- no overlay outside m524dll and
 * m570dll does, which was checked across all 27 candidates of the five
 * remaining types before this one was started.
 *
 * TWO TRANSLATION UNITS, exactly as upstream's configure.py declares them:
 * REL/m560dll/m560.c (62 functions) and REL/m560dll/effect.c (7).
 *
 * HOW TO CHECK IT:
 *   ./games/mp5/gen_asm.sh m560Dll                          # reference asm
 *   REF=games/mp5/build/GP5E01_00/m560Dll/obj/REL/m560dll/m560.o
 *   OURS=games/mp5/build/GP5E01_00/src/REL/m560dll/m560.o
 *   ./games/mp5/fndiff.py sizes $REF
 *   diff <(./games/mp5/fndiff.py fn $REF fn_1_268C) \
 *        <(./games/mp5/fndiff.py fn $OURS M560KupaMain)
 *
 * Compare per function, never by verify_obj.sh's headline number -- see the
 * header of ../m524dll/m524.c for why, and games/mp5/fndiff.py for the tool.
 *
 * NO datanum/m560.h: the archive at files/data/m560.bin carries no file names,
 * so every name would be invented and would then conflict with upstream's if
 * they ever publish one. The raw DATANUM(DATA_m560, n) is used instead, with a
 * comment at each table.
 *
 * _prolog and _epilog are not reproduced. They are REL bootstrap that the port
 * replaces: a port overlay is a host shared library whose only export is
 * ObjectSetup. m524dll, m570dll and m526dll all do the same.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/hsfformat.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/flag.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/animdata.h"
#include "game/mg/seqman.h"
#include "game/hsfex.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"
#include "datanum/char.h"

#include "REL/m560dll/m560.h"

#include "dolphin/os.h"
#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/*
 * 0x98 bytes, one per player, allocated by ObjectSetup and never memset -- the
 * init function writes every field it uses.
 */
typedef struct M560Player_s {
    /* 0x00 */ s16 motNo;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ int unk04;
    /* 0x08 */ int unk08;
    /* 0x0C */ int unk0C;
    /* 0x10 */ int unk10;
    /* 0x14 */ int no;
    /* 0x18 */ int charNo;
    /* 0x1C */ int padNo;
    /* 0x20 */ int unk20;
    /* 0x24 */ int mode;
    /* 0x28 */ int timer;
    /* 0x2C */ HuVecF pos;
    /* 0x38 */ HuVecF posOld;
    /* 0x44 */ HuVecF rot;
    /* 0x50 */ int unk50;
    /* 0x54 */ int unk54;
    /* 0x58 */ int unk58;
    /* 0x5C */ int unk5C;
    /* 0x60 */ int signType;    /* SignTbl[signNo] -- which of the six signs */
    /* 0x64 */ int signNo;      /* 0..8, how far through the sequence */
    /* 0x68 */ int doneF;
    /* 0x6C */ int unk6C;
    /* 0x70 */ HU3DMODELID mdlId70;
    /* 0x72 */ HU3DMODELID mdlId72;
    /* 0x74 */ HU3DMODELID mdlId74;   /* the model the item and mark hook onto */
    /* 0x76 */ HU3DMODELID itemMdlId[7];
    /* 0x84 */ HU3DMODELID okMdlId;
    /* 0x86 */ HU3DMODELID ngMdlId;
    /* 0x88 */ int dif;
    /* 0x8C */ int comMissMod;  /* 1-in-this chance a COM presses Z instead */
    /* 0x90 */ int comWait;
    /* 0x94 */ int comWaitMax;
} M560_PLAYER;                  /* 0x98 */

/* 0x3C bytes -- Bowser. */
typedef struct M560Kupa_s {
    /* 0x00 */ int timer;
    /* 0x04 */ HU3DMODELID mdlId;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ HuVecF pos;
    /* 0x14 */ HuVecF rot;
    /* 0x20 */ HuVecF speed;
    /* 0x2C */ float motTime;
    /* 0x30 */ int motNo;
    /* 0x34 */ int mode;
    /* 0x38 */ int billMdlId;
} M560_KUPA;                    /* 0x3C */

typedef struct M560Bill_s M560_BILL;
typedef void (*M560BILLFUNC)(HU3DMODEL *modelP, M560_BILL *work, Mtx mtx);

/*
 * One camera-facing quad. `no` is its index into the system's arrays and -1
 * when the slot is free, which is the only liveness flag there is.
 */
typedef struct M560BillPart_s {
    /* 0x00 */ int unk00;
    /* 0x04 */ HuVecF basePos;
    /* 0x10 */ float time;
    /* 0x14 */ float angle;
    /* 0x18 */ float angleOfs;
    /* 0x1C */ float timeAdd;
    /* 0x20 */ float timeMax;
    /* 0x24 */ float posYTarget;
    /* 0x28 */ float zRot;
    /* 0x2C */ float scale;
    /* 0x30 */ HuVecF pos;
    /* 0x3C */ s16 cellNo;
    /* 0x3E */ s16 no;
} M560_BILLPART;                /* 0x40 */

/*
 * The billboard system itself, hung off a Hu3D hook model's hookData. One
 * display list, built once, indexing arrays the hook rewrites in place.
 */
struct M560Bill_s {
    /* 0x00 */ M560BILLFUNC func;
    /* 0x04 */ ANIMDATA *anim;
    /* 0x08 */ HuVecF *posSrc;   /* if set, every quad tracks it */
    /* 0x0C */ float *angleSrc;  /* likewise for the spin */
    /* 0x10 */ M560_BILLPART *part;
    /* 0x14 */ HuVecF *vtx;
    /* 0x18 */ HuVec2f *st;
    /* 0x1C */ HuVec2f *cellTbl;
    /* 0x20 */ GXColor *color;
    /* 0x24 */ void *dlBuf;
    /* 0x28 */ HuVecF quad[4];
    /* 0x58 */ u32 dlSize;
    /* 0x5C */ float cellSizeX;
    /* 0x60 */ float cellSizeY;
    /* 0x64 */ s16 maxCnt;
    /* 0x66 */ s16 liveCnt;
    /* 0x68 */ s16 cellNum;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 killF;
};                              /* 0x6C */

/* A doubly-linked id list with a static sentinel head. */
typedef struct M560IdNode_s {
    /* 0x00 */ u16 id;
    /* 0x02 */ s16 value;
    /* 0x04 */ struct M560IdNode_s *prev;
    /* 0x08 */ struct M560IdNode_s *next;
} M560_IDNODE;                  /* 0x0C */

/* One entry of the model cache M560ModelCreate keeps. */
typedef struct M560MdlCache_s {
    /* 0x00 */ unsigned int dataNum;
    /* 0x04 */ HU3DMODELID modelId;
    /* 0x06 */ s16 pad06;
} M560_MDLCACHE;                /* 0x08 */

/* --- forward declarations, asm address order --- */

/* sprite.h has this commented out -- see the note beside it there. */
void HuSprTexLoad(ANIMDATA *anim, s16 bmpNo, s16 texMapId, GXTexWrapMode wrapS, GXTexWrapMode wrapT, GXTexFilter filter);

void ObjectSetup(void);
static void M560PlayerInit(OMOBJ *obj);
static void M560PlayerMain(OMOBJ *obj);
static void M560PlayerBurn(OMOBJ *obj);
static int M560PlayerInputGet(M560_PLAYER *work);
static u16 M560ComInputGet(M560_PLAYER *work);
static void M560SignTblMake(void);
static void M560PlayerSignNext(M560_PLAYER *work, int okF);
static void M560PlayerSignReset(M560_PLAYER *work);
static void M560InitHook(s16 mode, s16 frameNo);
static void M560FadeInHook(s16 mode, s16 frameNo);
static void M560MainHook(s16 mode, s16 frameNo);
static void M560FinishHook(s16 mode, s16 frameNo);
static void M560PreWinnerHook(s16 mode, s16 frameNo);
static void M560WinnerHook(s16 mode, s16 frameNo);
static void M560PlayerMotionSet(OMOBJ *obj, int motNo, float speed, u32 attr);
static BOOL M560PlayerAnyDoneCheck(void);
static BOOL M560PlayerAllDoneCheck(void);
static void M560Nop(void);
static void M560DebugCameraMain(void);
static void M560KupaInit(OMOBJ *obj);
static void M560KupaMain(OMOBJ *obj);
static void M560KupaMotionSet(OMOBJ *obj, int motNo, float speed, u32 attr);
static void M560PlayerHitCheck(OMOBJ *obj);
static void M560BgmInit(void);
static void M560BgmPlay(void);
static void M560BgmFadeOut(void);
static void M560QuakeSet(u16 time, float amp, float decay, float freq, int flag);
static void M560QuakeMain(void);
static s16 M560PanGet(HuVecF *pos);
static s16 M560VolGet(HuVecF *pos);
static s16 M560KupaVolGet(void);
static void M560IdListInit(void);
static void M560IdListAdd(u16 id, s16 value);
static s16 M560IdListDel(s16 id);
static void M560ModelCacheInit(void);
static HU3DMODELID M560ModelCreate(unsigned int dataNum);
static void M560VecEase(float t, HuVecF *from, HuVecF *to, HuVecF *out);
static void M560CameraPosSet(HuVecF *pos, HuVecF *up, HuVecF *target);
static BOOL M560CameraMoveMain(float t, HuVecF *up);
static BOOL M560CameraMoveMainMulti(float t, HuVecF *up);
static float M560AngleApproach(float from, float to, float speed);
static void M560SeqFadeOut(s32 speed);
static void M560ModelObjPosGet(HU3DMODELID modelId, char *name, HuVecF *pos);
static int M560RandRange(int min, int max);
static BOOL M560HitCheck(HuVecF *a, HuVecF *b, float radiusA, float radiusB);
static s16 M560PanGetEx(HuVecF *pos, int base, int range);
static s16 M560VolGetEx(HuVecF *pos, int base, int range);
static void M560BillPartMain(HU3DMODEL *modelP, M560_BILL *work, Mtx mtx);
static void M560MtxTranspose(Mtx src, Mtx dst);
static void M560VecScaleN(HuVecF *src, HuVecF *dst, float scale, s16 count);
static void M560TexCoordSet(HuVec2f *st, HuVec2f *cellTbl, s16 cell, float width, float height);
static void M560BillHook(HU3DMODEL *modelP, Mtx *mtx);
static void M560CellTblMake(HuVec2f *st, s16 count, s16 cellX, float w, float h);
static HU3DMODELID M560BillCreate(ANIMDATA *anim, HuVecF *posSrc, float *angleSrc, s16 maxCnt, float size, s16 cellW, s16 cellH);
static M560_BILLPART *M560BillPartCreate(HU3DMODELID modelId, HuVecF *pos, GXColor *color, float scale, float zRot);
static void M560BillFuncSet(HU3DMODELID modelId, M560BILLFUNC func);
static void M560BillUnk6ASet(HU3DMODELID modelId, u8 value);
static void M560BillKillReq(HU3DMODELID modelId);
static BOOL M560BillKill(HU3DMODELID modelId);
static void M560BillPartEmit(HU3DMODELID modelId, s16 count, HuVecF *pos, float angle, float timeMax, float posYTarget);
static HU3DMODELID M560BillCreateEx(HuVecF *posSrc, float *angleSrc, s16 maxCnt);

/* --- .data --- */

static HuVecF LightPos = { 0.0f, 10000.0f, 10000.0f };       /* data_0 */
static HuVecF LightAim = { 0.0f, 0.0f, 0.0f };               /* data_C */
static GXColor LightColor = { 255, 255, 255, 255 };          /* data_18 */

/*
 * data_20 -- the eight motions every player model gets, in the order
 * M560PlayerMotionSet indexes them: 0 idle, 1 ready, 2 press, 3 cheer,
 * 4 unused, 5 walk, 6 the eye overlay, 7 burnt.
 */
static unsigned int PlayerMotDataTbl[8] = {
    CHARMOT_HSF_c000m1_300,
    CHARMOT_HSF_c000m1_325,
    CHAR_HSF_c000m1_489,
    CHARMOT_HSF_c000m1_488,
    CHARMOT_HSF_c000m1_301,
    CHARMOT_HSF_c000m1_355,
    CHARMOT_HSF_c000m1_eye,
    CHARMOT_HSF_c000m1_338
};

/* data_40 -- files/data/m560.bin 0x10..0x18, Bowser's nine motions. */
static int KupaMotDataTbl[9] = {
    DATANUM(DATA_m560, 0x10), DATANUM(DATA_m560, 0x11), DATANUM(DATA_m560, 0x12),
    DATANUM(DATA_m560, 0x13), DATANUM(DATA_m560, 0x14), DATANUM(DATA_m560, 0x15),
    DATANUM(DATA_m560, 0x16), DATANUM(DATA_m560, 0x17), DATANUM(DATA_m560, 0x18)
};

/*
 * data_64 -- one model per sign, 0x06..0x0B. Seven entries for six signs: the
 * table's last word is zero and the loop that reads it runs seven times, so
 * the shipped game reads data number 0 into itemMdlId[6]. That is what the
 * object does; the seventh model is never hooked, because SignTbl only ever
 * holds 0..5.
 */
static int SignMdlDataTbl[7] = {
    DATANUM(DATA_m560, 0x06), DATANUM(DATA_m560, 0x07), DATANUM(DATA_m560, 0x08),
    DATANUM(DATA_m560, 0x09), DATANUM(DATA_m560, 0x0A), DATANUM(DATA_m560, 0x0B),
    0
};

static OMCAMERAVIEW CameraView = {                    /* data_80 -- the play view */
    { 0.0f, 150.0f, -1544.0f }, { -10.1f, 0.0f, 0.0f }, 1070.0f
};

static OMCAMERAVIEW CameraViewOpen = {                /* data_9C -- pulled back for the entrance */
    { 0.0f, 334.7f, 0.0f }, { -5.4f, 0.0f, 0.0f }, 1174.0f
};

static OMCAMERAVIEW CameraViewLose = {                /* data_B8 -- over the losers */
    { 553.4f, 334.7f, -2.2f }, { -13.1f, 0.0f, 0.0f }, 2294.0f
};

/* data_D4 -- where the four players stand, left to right. */
static HuVecF PlayerPosTbl[4] = {
    { -400.0f, 20.0f, 0.0f },
    { -150.0f, 20.0f, 0.0f },
    {  150.0f, 20.0f, 0.0f },
    {  400.0f, 20.0f, 0.0f }
};

/* data_104 -- and where they queue up once they have finished, in finish order. */
static HuVecF FinishPosTbl[4] = {
    { 1000.0f, 40.0f, 230.0f },
    { 1150.0f, 40.0f, 230.0f },
    { 1300.0f, 40.0f, 230.0f },
    { 1450.0f, 40.0f, 230.0f }
};

static HuVecF KupaPos = { 0.0f, 0.0f, -1400.0f };            /* data_134 */
static HuVecF ShadowPos = { 0.0f, 5000.0f, 1.0f };           /* data_140 */
static HuVecF ShadowUp = { 0.0f, 1.0f, 0.0f };               /* data_14C */
static HuVecF ShadowTarget = { 0.0f, 0.0f, 0.0f };           /* data_158 */

/* data_164 -- the button each sign asks for. Z is deliberately absent from
 * the six the game draws from, which is what makes it the COM's wrong answer. */
static int SignBtnTbl[7] = {
    PAD_TRIGGER_L, PAD_TRIGGER_R, PAD_BUTTON_Y, PAD_BUTTON_X,
    PAD_BUTTON_A, PAD_BUTTON_B, PAD_TRIGGER_Z
};

/* data_180 -- the sequence manager's hooks; start, fadeOut and close are none. */
static MGSEQ_PARAM SeqParam = {
    0, 0,
    M560InitHook,
    M560FadeInHook,
    NULL,
    M560MainHook,
    M560FinishHook,
    M560PreWinnerHook,
    M560WinnerHook,
    NULL,
    NULL
};

static int SeEntryTbl[4] = { 0x984, 0x985, 0x986, 0x987 };   /* data_1A8 */
static int SeOkTbl[4] = { 0x988, 0x989, 0x98A, 0x98B };      /* data_1B8 */
static int SeNgTbl[4] = { 0x98C, 0x98D, 0x98E, 0x98F };      /* data_1C8 */
static int SeDoneTbl[4] = { 0x990, 0x991, 0x992, 0x993 };    /* data_1D8 */

static char SetupMesStr[] = "******* M560 ObjectSetup *********\n";  /* data_1E8 */
static char ItemHook2Str[] = "itemhook2";                            /* data_20C */
static char ItemHookLampStr[] = "itemhook_lamp";                     /* data_216 */
static char ItemHookFxStr[] = "itemhook_fx";                         /* data_224 */
static char ItemHookStr[] = "itemhook";                              /* data_258 */
static char CenterMesStr[] = "Center X:%.02f Y:%.02f Z:%.02f";       /* data_261 */
static char CRotMesStr[] = "CRot X:%.02f Y:%.02f Z:%.02f";           /* data_280 */
static char CZoomMesStr[] = "CZoom:%.02f";                           /* data_29D */
static char ItemHookMStr[] = "g000m0-itemhook_M";                    /* data_2A9 */
static char HeadStr[] = "g000m0-ns_hed";                             /* data_2BB */

/* --- .bss --- */

static void *SprAnim;               /* bss_0 */
static float QuakeOfs;              /* bss_4 -- this frame's shake offset */
static float QuakeFreq;             /* bss_8 */
static int QuakeFlag;               /* bss_C */
static float QuakeAngle;            /* bss_10 */
static float QuakeDecay;            /* bss_14 */
static float QuakeAmp;              /* bss_18 */
static int QuakeTime;               /* bss_20 */
static int BgmId;                   /* bss_24 */
static int SeFireId = -1;           /* data_1C */
static int FinishCnt;               /* bss_28 -- how many have walked clear */
static int SignTbl[8];              /* bss_2C -- the eight signs, made once */
static HU3DLIGHTID LightId;         /* bss_4C */
static HU3DMODELID StageMdlId[4];   /* bss_4E */
static OMOBJ *OutViewObj;           /* bss_2FC */
static OMOBJ **KupaObj;             /* bss_300 */
static OMOBJ **PlayerObj;           /* bss_304 */
static M560_MDLCACHE MdlCacheTbl[32]; /* bss_308 */
static int SeqId;                   /* bss_410 */
static HuVecF CameraTargetEndTbl[4];   /* bss_41C */
static HuVecF CameraTargetStartTbl[4]; /* bss_44C */
static HuVecF CameraPosEndTbl[4];      /* bss_47C */
static HuVecF CameraPosStartTbl[4];    /* bss_4AC */
static int CameraMoveF;             /* bss_40C */
static HuVecF CameraTargetEnd;      /* bss_4DC */
static HuVecF CameraTargetStart;    /* bss_4E8 */
static HuVecF CameraPosEnd;         /* bss_4F4 */
static HuVecF CameraPosStart;       /* bss_500 */
static OMOBJMAN *objman;            /* bss_50C */
static M560_IDNODE IdListHead;      /* bss_510 */

/* ===== decoded functions, asm address order ===== */
/* ObjectSetup -- the overlay's only export. */
void ObjectSetup(void)
{
    OMOBJ *obj;
    int i;

    OSReport(SetupMesStr);
    objman = omInitObjMan(200, 0x2000);
    omGameSysInit(objman);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 50000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    omCameraViewSet(&CameraView);
    OutViewObj = omAddObjEx(objman, 0x7FDA, 0, 0, OM_GRP_NONE, omOutView);
    OutViewObj->work[0] = 1;
    LightId = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(LightId, &LightPos, &LightAim);
    Hu3DGLightStaticSet(LightId, 1);
    Hu3DGLightInfinitytSet(LightId);
    Hu3DGLightColorSet(LightId, LightColor.r, LightColor.g, LightColor.b, LightColor.a);
    Hu3DShadowCreate(45.0f, 2000.0f, 25000.0f);
    Hu3DShadowPosSet(&ShadowPos, &ShadowUp, &ShadowTarget);
    Hu3DShadowTPLvlSet(0.3f);
    omMakeGroupEx(objman, 0, 4);
    PlayerObj = omGetGroupMemberListEx(objman, 0);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(objman, 100, 1, 8, 0, M560PlayerInit);
        PlayerObj[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M560_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(objman, 2, 1);
    KupaObj = omGetGroupMemberListEx(objman, 2);
    obj = omAddObjEx(objman, 0x66, 1, 9, 2, M560KupaInit);
    KupaObj[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M560_KUPA), HU_MEMNUM_OVL);
    SprAnim = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_m560, 0x19), HU_MEMNUM_OVL));
    HuSprAnimLock(SprAnim);
    M560SignTblMake();
    FinishCnt = 0;
    M560BgmInit();
    M560EffectInit();
    M560EffectParticleInit();
    MgSeqCreatePrio(&SeqParam, 1000);
}

/* fn_1_4B0 -- the player object's first frame; it swaps itself for the main. */
static void M560PlayerInit(OMOBJ *obj)
{
    M560_PLAYER *work = obj->data;
    int waitEasy;
    int waitNormal;
    int waitHard;
    int waitVeryHard;
    float posX;
    float posY;
    float posZ;
    int i;

    work->no = obj->work[0];
    work->charNo = GwPlayerConf[work->no].charNo;
    work->padNo = GwPlayerConf[work->no].padNo;
    work->mode = 0;
    work->timer = 0;
    obj->mdlId[0] = CharModelCreate(work->charNo, 2);
    for(i=0; i<8; i++) {
        obj->mtnId[i] = CharMotionCreate(work->charNo, PlayerMotDataTbl[i]);
        CharMotionSet(work->charNo, obj->mtnId[i]);
    }
    work->motNo = 1;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[1]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    work->signType = -1;
    work->signNo = 0;
    work->signType = SignTbl[0];
    work->unk20 = 0;
    work->doneF = 0;
    work->unk6C = 0;
    work->comWait = 0;
    work->dif = GwPlayerConf[work->no].dif;
    switch(work->dif) {
        case 0:
            work->comMissMod = 5;
            waitEasy = frandmod(5)+35;
            work->comWaitMax = waitEasy;
            break;
        case 1:
            work->comMissMod = 8;
            waitNormal = frandmod(5)+35;
            work->comWaitMax = waitNormal;
            break;
        case 2:
            work->comMissMod = 15;
            waitHard = frandmod(5)+25;
            work->comWaitMax = waitHard;
            break;
        case 3:
            work->comMissMod = 20;
            waitVeryHard = frandmod(5)+20;
            work->comWaitMax = waitVeryHard;
            break;
    }
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    posZ = PlayerPosTbl[work->no].z;
    posY = PlayerPosTbl[work->no].y;
    posX = PlayerPosTbl[work->no].x;
    work->pos.x = posX;
    work->pos.y = posY;
    work->pos.z = posZ;
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    work->mdlId70 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 3), HU_MEMNUM_OVL, HEAP_MODEL));
    work->mdlId72 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 4), HU_MEMNUM_OVL, HEAP_MODEL));
    work->mdlId74 = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 5), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(work->mdlId70, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->mdlId70, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(work->mdlId72, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->mdlId72, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(work->mdlId74, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->mdlId74, HU3D_MOTATTR_PAUSE);
    work->okMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 0xC), HU_MEMNUM_OVL, HEAP_MODEL));
    work->ngMdlId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 0xD), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionTimeSet(work->okMdlId, 0.0f);
    Hu3DMotionTimeSet(work->ngMdlId, 0.0f);
    Hu3DModelAttrSet(work->okMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->okMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(work->ngMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->ngMdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelHookSet(work->mdlId70, ItemHook2Str, work->mdlId74);
    Hu3DModelPosSet(work->mdlId70, PlayerPosTbl[work->no].x, 0.0f, PlayerPosTbl[work->no].z);
    Hu3DModelHookSet(work->mdlId74, ItemHookLampStr, work->mdlId72);
    for(i=0; i<7; i++) {
        work->itemMdlId[i] = Hu3DModelCreate(HuDataSelHeapReadNum(SignMdlDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
        Hu3DModelAttrSet(work->itemMdlId[i], HU3D_ATTR_DISPOFF);
    }
    Hu3DModelAttrReset(work->mdlId70, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->mdlId72, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(work->mdlId74, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose(work->charNo);
    obj->objFunc = M560PlayerMain;
}

/*
 * fn_1_9F8 -- the player state machine. Modes 0, 3 and 7 are live states with
 * nothing to do per frame, and they are spelled out below because the object
 * has a ten-entry jumptable: written as a compare tree instead, this would not
 * be the same function.
 */
static void M560PlayerMain(OMOBJ *obj)
{
    M560_PLAYER *work = obj->data;
    M560_KUPA *kupa = KupaObj[0]->data;
    int ret;
    HuVecF screen;
    s16 pan;
    s16 panShift;
    s16 panSet;

    work->posOld = work->pos;
    switch(work->mode) {
        case 1:
            if(kupa->mode == 1 || kupa->mode == 4) {
                ret = M560PlayerInputGet(work);
                if(ret == 1) {
                    Hu3DModelHookObjReset(work->mdlId74, ItemHookFxStr);
                    Hu3DModelAttrSet(work->ngMdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(work->ngMdlId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(work->ngMdlId, 0.0f);
                    Hu3DMotionSpeedSet(work->ngMdlId, 0.0f);
                    Hu3DModelAttrReset(work->okMdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(work->okMdlId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(work->okMdlId, 0.0f);
                    Hu3DMotionSpeedSet(work->okMdlId, 1.0f);
                    Hu3DMotionCalc(work->okMdlId);
                    Hu3DModelHookSet(work->mdlId74, ItemHookFxStr, work->okMdlId);
                    M560PlayerSignNext(work, 1);
                    HuAudFXPlay(SeOkTbl[work->no]);
                } else if(ret == 2) {
                    omVibrate(work->no, 20, 4, 2);
                    Hu3DModelHookObjReset(work->mdlId74, ItemHookFxStr);
                    Hu3DModelAttrSet(work->okMdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(work->okMdlId, HU3D_ATTR_DISPOFF);
                    Hu3DMotionTimeSet(work->okMdlId, 0.0f);
                    Hu3DMotionSpeedSet(work->okMdlId, 0.0f);
                    Hu3DModelAttrReset(work->ngMdlId, HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(work->ngMdlId, HU3D_MOTATTR_PAUSE);
                    Hu3DMotionTimeSet(work->ngMdlId, 0.0f);
                    Hu3DMotionSpeedSet(work->ngMdlId, 1.0f);
                    Hu3DMotionCalc(work->ngMdlId);
                    Hu3DModelHookSet(work->mdlId74, ItemHookFxStr, work->ngMdlId);
                    M560PlayerSignNext(work, 0);
                    work->mode = 2;
                    work->timer = 0;
                    HuAudFXPlay(SeNgTbl[work->no]);
                }
            }
            break;

        case 2:
            if(work->timer > 30) {
                work->timer = 0;
                work->mode = 1;
            } else {
                work->timer++;
            }
            break;

        case 4:
            if(work->timer > 15) {
                work->timer = 0;
                work->mode = 5;
            } else {
                work->timer++;
            }
            break;

        case 5:
            M560PlayerMotionSet(obj, 5, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->pos.z > 150.0f) {
                work->mode = 6;
                work->rot.y = 90.0f;
            } else {
                work->pos.z += 5.0f;
                work->pos.y = 20.0f-(0.1875f*work->pos.z);
            }
            break;

        case 6:
            if(work->pos.x > 700.0f) {
                work->pos.x = FinishPosTbl[FinishCnt].x;
                work->pos.y = FinishPosTbl[FinishCnt].y;
                work->pos.z = FinishPosTbl[FinishCnt].z;
                work->rot.y = 0.0f;
                FinishCnt++;
                work->mode = 7;
                M560PlayerMotionSet(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                work->pos.x += 10.0f;
            }
            break;

        case 8:
            if(work->timer < 15) {
                M560PlayerBurn(obj);
            }
            M560PlayerMotionSet(obj, 7, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 45) {
                work->mode = 9;
                work->timer = 0;
            } else {
                work->timer++;
            }
            break;

        case 9:
            M560PlayerMotionSet(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer == 0) {
                Hu3DMotionOverlaySet(obj->mdlId[0], obj->mtnId[6]);
            }
            work->timer++;
            break;

        case 0:
        case 3:
        case 7:
            break;
    }
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    if(work->mode == 5 || work->mode == 5) {
        M560PlayerHitCheck(obj);
    }
    Hu3D3Dto2D(&work->pos, 1, &screen);
    pan = 32.0f+((screen.x/576.0f)*64.0f);
    panShift = pan;
    panSet = panShift;
    CharModelVoicePanSet(work->charNo, panSet);
}

/*
 * fn_1_FE4 -- scorch the loser. Every material's diffuse colour is knocked
 * down 10% a frame for fifteen frames, which is what turns the model black.
 *
 * Two things worth not tidying. Waluigi (charNo 3) is special-cased to skip
 * materials 1 and 2 rather than to test the eye bitmaps, and in that branch
 * the loop bound is re-read through modelP->hsf every iteration while the
 * other branch uses the cached pointer. Both are the object's.
 */
static void M560PlayerBurn(OMOBJ *obj)
{
    M560_PLAYER *work = obj->data;
    BOOL burnF = TRUE;
    HU3DMODEL *modelP = &Hu3DData[obj->mdlId[0]];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    char **eyeBmp;
    HSFATTRIBUTE *attr;
    int i;
    u32 j;

    if(work->charNo == 3) {
        for(i=0; i<modelP->hsf->materialNum; i++, material++) {
            if(i == 1) {
                continue;
            }
            if(i == 2) {
                continue;
            }
            material->color[0] *= 0.9f;
            material->color[1] *= 0.9f;
            material->color[2] *= 0.9f;
        }
    } else {
        eyeBmp = CharModelEyeBmpGet(work->charNo, 2);
        for(i=0; i<hsf->materialNum; i++, material++) {
            burnF = TRUE;
            for(j=0; j<material->attrNum; j++) {
                attr = &hsf->attribute[material->attr[j]];
                if(strcmp(eyeBmp[0], attr->bitmap->name) == 0 || strcmp(eyeBmp[1], attr->bitmap->name) == 0) {
                    burnF = FALSE;
                }
            }
            if(burnF) {
                material->color[0] *= 0.9f;
                material->color[1] *= 0.9f;
                material->color[2] *= 0.9f;
            }
        }
    }
}

/*
 * fn_1_12B4 -- one frame of input. Returns 0 for nothing, 1 for the button the
 * current sign asks for, 2 for anything else. A press of any kind starts the
 * press animation; only an exact match counts, so pressing two buttons at once
 * is a miss.
 */
static int M560PlayerInputGet(M560_PLAYER *work)
{
    u16 btn;
    u16 sign;
    int ret = 0;

    if(GwPlayerConf[work->no].type != 0) {
        btn = M560ComInputGet(work);
    } else {
        btn = HuPadBtnDown[work->padNo] & (PAD_TRIGGER_L|PAD_TRIGGER_R|PAD_BUTTON_A|PAD_BUTTON_B|PAD_BUTTON_X|PAD_BUTTON_Y);
    }
    sign = SignBtnTbl[SignTbl[work->signNo]];
    if(btn) {
        work->motNo = 2;
        Hu3DModelAttrReset(PlayerObj[work->no]->mdlId[0], HU3D_MOTATTR_PAUSE);
        CharMotionShiftSet(work->charNo, PlayerObj[work->no]->mtnId[work->motNo], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
        ret = 2;
    }
    if((btn & sign) && !(btn & ~sign)) {
        ret = 1;
    }
    return ret;
}

/*
 * fn_1_143C -- and the COM's. It answers every comWaitMax frames, which the
 * difficulty picks in the 20-40 range, and gets it wrong 1 time in comMissMod
 * by pressing Z -- a button the sign table can never ask for.
 */
static u16 M560ComInputGet(M560_PLAYER *work)
{
    u16 btn;

    if(work->comWait > work->comWaitMax) {
        work->comWait = 0;
        if(frandmod(work->comMissMod) == 0) {
            btn = PAD_TRIGGER_Z;
        } else {
            btn = SignBtnTbl[SignTbl[work->signNo]];
        }
    } else {
        work->comWait++;
        btn = 0;
    }
    return btn;
}

/*
 * fn_1_14E4 -- the eight signs, drawn once for everybody. Redrawn until the
 * new one differs from the one before it and has not already been used twice,
 * so no sign appears three times and none appears twice running.
 */
static void M560SignTblMake(void)
{
    int i;
    int j;
    int cnt;

    for(i=0; i<8; ) {
        SignTbl[i] = frandmod(6);
        if(i > 0 && SignTbl[i] == SignTbl[i-1]) {
            continue;
        }
        for(j=0, cnt=0; j<i; j++) {
            if(SignTbl[i] == SignTbl[j]) {
                cnt++;
            }
        }
        if(cnt >= 2) {
            continue;
        }
        i++;
    }
}

/*
 * fn_1_15D8 -- advance to the next sign, or finish. `okF` is zero on a wrong
 * press, which is what makes a miss cost time rather than progress.
 */
static void M560PlayerSignNext(M560_PLAYER *work, int okF)
{
    if(okF != 0 && work->signNo < 8) {
        Hu3DModelAttrSet(work->itemMdlId[work->signType], HU3D_ATTR_DISPOFF);
        Hu3DModelHookObjReset(work->mdlId74, ItemHookStr);
        work->signNo++;
        if(work->signNo == 8) {
            work->mode = 4;
            work->timer = 0;
            Hu3DModelAttrReset(work->mdlId70, HU3D_MOTATTR_PAUSE);
            Hu3DMotionSpeedSet(work->mdlId70, 2.0f);
            Hu3DMotionTimeSet(work->mdlId72, 8.0f);
            work->doneF = 1;
            omVibrate(work->no, 15, 4, 2);
            HuAudFXPlay(SeDoneTbl[work->no]);
        } else {
            work->signType = SignTbl[work->signNo];
            Hu3DMotionTimeSet(work->mdlId72, work->signNo);
            Hu3DModelHookSet(work->mdlId74, ItemHookStr, work->itemMdlId[work->signType]);
            Hu3DModelAttrReset(work->itemMdlId[work->signType], HU3D_ATTR_DISPOFF);
        }
    }
}

/* fn_1_1768 -- put the sign, the mark and the lamp back the way they started. */
static void M560PlayerSignReset(M560_PLAYER *work)
{
    Hu3DModelAttrSet(work->itemMdlId[work->signType], HU3D_ATTR_DISPOFF);
    Hu3DModelHookObjReset(work->mdlId74, ItemHookStr);
    Hu3DModelHookObjReset(work->mdlId74, ItemHookFxStr);
    Hu3DMotionTimeSet(work->okMdlId, 0.0f);
    Hu3DMotionTimeSet(work->ngMdlId, 0.0f);
    Hu3DModelAttrSet(work->okMdlId, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(work->ngMdlId, HU3D_ATTR_DISPOFF);
}

/* fn_1_1808 -- MGSEQ_MODE_INIT: the arena. */
static void M560InitHook(s16 mode, s16 frameNo)
{
    StageMdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    StageMdlId[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 1), HU_MEMNUM_OVL, HEAP_MODEL));
    StageMdlId[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 2), HU_MEMNUM_OVL, HEAP_MODEL));
    StageMdlId[3] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 0xE), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelShadowMapSet(StageMdlId[0]);
    Hu3DModelAttrSet(StageMdlId[3], HU3D_MOTATTR_LOOP);
    Hu3DModelAttrSet(StageMdlId[2], HU3D_MOTATTR_LOOP);
    M560BgmPlay();
    MgSeqModeNext();
}

/*
 * fn_1_18F8 -- MGSEQ_MODE_FADEIN. A HuPrcVSleep coroutine, so the frame
 * counts below are literal: Bowser lands at frame 110 with a dust ring and a
 * screen shake, the camera pulls back at 180, the players raise their lamps at
 * 290 and go to the ready pose at 305.
 */
static void M560FadeInHook(s16 mode, s16 frameNo)
{
    HuVecF pos = { 80.0f, 0.0f, -1150.0f };
    M560_KUPA *kupa = KupaObj[0]->data;
    M560_PLAYER *work;
    int i;
    s16 pan;

    for(i=0; i<60; i++) {
        HuPrcVSleep();
    }
    kupa->mode = 2;
    HuAudFXPlay(0x2C9);
    for(i=0; i<50; i++) {
        HuPrcVSleep();
    }
    M560EffectDustRingCreate(1, &pos);
    M560QuakeSet(60, 25.0f, 0.85f, 90.0f, 0);
    pan = M560PanGet(&kupa->pos);
    HuAudFXPlayVolPan(0x2C7, M560VolGet(&kupa->pos), pan);
    for(i=0; i<4; i++) {
        work = PlayerObj[i]->data;
        omVibrate(work->no, 15, 4, 2);
    }
    for(i=0; i<70; i++) {
        HuPrcVSleep();
    }
    omCameraViewMoveSimple(&CameraViewOpen, 120);
    for(i=0; i<110; i++) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        work = PlayerObj[i]->data;
        Hu3DModelAttrReset(work->mdlId74, HU3D_MOTATTR_PAUSE);
        Hu3DMotionSpeedSet(work->mdlId74, 3.0f);
        HuAudFXPlay(SeEntryTbl[i]);
    }
    for(i=0; i<15; i++) {
        HuPrcVSleep();
    }
    for(i=0; i<4; i++) {
        work = PlayerObj[i]->data;
        M560PlayerMotionSet(PlayerObj[work->no], 2, 8.0f, HU3D_MOTATTR_PAUSE);
    }
    for(i=0; i<45; i++) {
        HuPrcVSleep();
    }
    MgSeqModeNext();
}

/* fn_1_1B88 -- MGSEQ_MODE_MAIN. Bowser's mode 6 is what ends the round. */
static void M560MainHook(s16 mode, s16 frameNo)
{
    M560_KUPA *kupa = KupaObj[0]->data;
    M560_PLAYER *work;
    int i;

    if(MgSeqFrameNoGet() == 0) {
        kupa->mode = 1;
        for(i=0; i<4; i++) {
            work = PlayerObj[i]->data;
            work->mode = 1;
            Hu3DModelHookSet(work->mdlId74, ItemHookStr, work->itemMdlId[work->signType]);
            Hu3DModelAttrReset(work->itemMdlId[work->signType], HU3D_ATTR_DISPOFF);
        }
    }
    if(kupa->mode == 6) {
        MgSeqModeNext();
    }
    M560Nop();
}

/* fn_1_1C64 -- MGSEQ_MODE_FINISH: everyone back to idle, music down. */
static void M560FinishHook(s16 mode, s16 frameNo)
{
    M560_PLAYER *work;
    int i;

    if(MgSeqFrameNoGet() == 0) {
        M560BgmFadeOut();
        for(i=0; i<4; i++) {
            work = PlayerObj[i]->data;
            M560PlayerMotionSet(PlayerObj[work->no], 0, 8.0f, HU3D_MOTATTR_LOOP);
        }
    }
}

/*
 * fn_1_1D00 -- MGSEQ_MODE_PREWIN: swing the camera over the losers.
 *
 * A BUG IN THE ORIGINAL, reproduced. `fov` is set once and never updated, so
 * the ninety Hu3DCameraPerspectiveSet calls all pass the same 44.72 degrees.
 * 0.2777778 is 25/90 -- the intent was plainly to zoom in by 25 degrees over
 * the ninety frames, and `fov -= 0.2777778f` is what was meant. Writing it
 * that way would be a different function, so it is left as the object has it.
 */
static void M560PreWinnerHook(s16 mode, s16 frameNo)
{
    float fov = 45.0f;
    M560_PLAYER *work;
    int i;

    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    if(M560PlayerAnyDoneCheck()) {
        omCameraViewMoveSimple(&CameraViewLose, 90);
        for(i=0; i<4; i++) {
            work = PlayerObj[i]->data;
            if(work->doneF == 0) {
                Hu3DModelAttrSet(work->mdlId74, HU3D_MOTATTR_REV);
                Hu3DMotionSpeedSet(work->mdlId74, 1.0f);
            }
        }
        for(i=0; i<90; i++) {
            Hu3DCameraPerspectiveSet(1, fov-0.2777778f, 20.0f, 50000.0f, 1.2f);
            HuPrcVSleep();
        }
    }
    MgSeqModeNext();
}

/*
 * fn_1_1E30 -- MGSEQ_MODE_WINNER. Ten coins each to everyone who finished,
 * unless this is a practice run.
 */
static void M560WinnerHook(s16 mode, s16 frameNo)
{
    M560_KUPA *kupa = KupaObj[0]->data;
    M560_PLAYER *work;
    int i;
    int no;

    if(MgSeqFrameNoGet() == 0) {
        if(M560PlayerAnyDoneCheck()) {
            for(i=0; i<4; i++) {
                work = PlayerObj[i]->data;
                if(work->doneF) {
                    M560PlayerMotionSet(PlayerObj[work->no], 3, 8.0f, HU3D_MOTATTR_NONE);
                    no = work->no;
                    if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                        GwPlayer[no].mgCoinBonus = 10;
                    }
                }
            }
        }
        kupa->mode = 7;
    }
}

/* fn_1_1F38 -- shift a player into a motion, once. */
static void M560PlayerMotionSet(OMOBJ *obj, int motNo, float speed, u32 attr)
{
    M560_PLAYER *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        CharMotionShiftSet(work->charNo, obj->mtnId[work->motNo], 0.0f, speed, attr);
        if(motNo == 7) {
            omVibrate(work->no, 30, 12, 0);
        }
    }
}

/* fn_1_1FE4 */
static BOOL M560PlayerAnyDoneCheck(void)
{
    BOOL doneF = FALSE;
    M560_PLAYER *work;
    int i;

    for(i=0; i<4; i++) {
        work = PlayerObj[i]->data;
        if(work->doneF != 0) {
            doneF = TRUE;
            return doneF;
        }
    }
    return doneF;
}

/* fn_1_2054 */
static BOOL M560PlayerAllDoneCheck(void)
{
    BOOL doneF = FALSE;
    M560_PLAYER *work[4];
    int i;

    for(i=0; i<4; i++) {
        work[i] = PlayerObj[i]->data;
    }
    if(work[0]->doneF != 0 && work[1]->doneF != 0 && work[2]->doneF != 0 && work[3]->doneF != 0) {
        return TRUE;
    }
    return FALSE;
}

/* fn_1_20F4 -- an empty call left in the main hook. */
static void M560Nop(void)
{
}

/*
 * fn_1_20F8 -- the debug free camera and its readout, driven off the C-stick
 * and the triggers with X to snap back to the opening view. Nothing calls it:
 * the main hook calls M560Nop where this would go, so it is dead in the
 * shipped game and reproduced because it is in the object. It writes the
 * object system's Center/CRot/CZoom directly rather than a view of its own.
 */
static void M560DebugCameraMain(void)
{
    GXColor color;

    color.r = 0;
    color.g = 0;
    color.b = 144;
    color.a = 192;
    CZoom += HuPadTrigL[0]/5;
    CZoom -= HuPadTrigR[0]/5;
    Center.x += 10.0f*(HuPadSubStkX[0]/59.0f);
    Center.z -= 10.0f*(HuPadSubStkY[0]/59.0f);
    CRot.x += 5.0f*(HuPadSubStkY[1]/59.0f);
    CRot.y -= 5.0f*(HuPadSubStkX[1]/59.0f);
    printWin(16, 40, 384, 36, &color);
    fontcolor = 14;
    print8(16, 40, 1.5f, CenterMesStr, Center.x, Center.y, Center.z);
    print8(16, 52, 1.5f, CRotMesStr, CRot.x, CRot.y, CRot.z);
    print8(16, 64, 1.5f, CZoomMesStr, CZoom);
    if(HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&CameraViewOpen);
    }
}

/* fn_1_24B8 -- Bowser's first frame; it swaps itself for the main. */
static void M560KupaInit(OMOBJ *obj)
{
    M560_KUPA *work = obj->data;
    int i;

    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m560, 0xF), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i=0; i<9; i++) {
        obj->mtnId[i] = Hu3DJointMotion(obj->mdlId[0], HuDataSelHeapReadNum(KupaMotDataTbl[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    work->motNo = 9;
    M560KupaMotionSet(obj, 2, 0.0f, HU3D_MOTATTR_LOOP);
    Hu3DModelShadowSet(obj->mdlId[0]);
    work->mdlId = obj->mdlId[0];
    work->timer = 0;
    work->billMdlId = -1;
    work->pos.x = KupaPos.x;
    work->pos.y = KupaPos.y;
    work->pos.z = KupaPos.z;
    work->mode = 0;
    work->motTime = 0.0f;
    work->speed.x = work->speed.y = work->speed.z = 0.0f;
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    obj->objFunc = M560KupaMain;
}

/*
 * fn_1_268C -- Bowser. The biggest function in the overlay and the whole of
 * its direction: he lands, waits, breathes fire down the arena, and either
 * roars or slumps depending on whether anyone was still on it.
 *
 * The modes are 2 land, 3 slide forward, 4 settle, 1 breathe, 5 the flame,
 * 6 recover, 7 pick the end pose, 0 idle. Mode 1 is the one that matters: it
 * walks him from the back wall to z = -600 at a speed worked out once from
 * how far he has to go, and fires a dust ring off each hand as the motion
 * passes frames 10 and 60.
 *
 * The switch is emitted 2, 3, 4, 1, 5, 6, 7 with 0 empty, which is the order
 * below -- written in numeric order it would be a different function, and
 * case 0 has to be spelled out to get a jumptable rather than a compare tree.
 *
 * Eight functions are inlined into this one: M560PlayerSignReset,
 * M560PlayerAllDoneCheck, M560BillCreateEx (and through it M560BillFuncSet
 * and M560BillUnk6ASet), M560ModelObjPosGet, M560BillPartEmit and
 * M560BillKill. The last four are defined BELOW it, which is worth knowing:
 * CodeWarrior 1.3.2 will inline a static it has not reached yet, so the "only
 * what it has already seen" rule that m524dll established governs whether a
 * helper is expanded at its call site, not whether it can be.
 */
static void M560KupaMain(OMOBJ *obj)
{
    HuVecF flameL = { -80.0f, 0.0f, 70.0f };
    HuVecF flameR = { 80.0f, 0.0f, 70.0f };
    M560_KUPA *work;
    M560_PLAYER *player;
    HuVecF posHand;
    HuVecF posHead;
    HuVecF dir;
    HuVecF firePos;
    HuVecF flamePosL;
    HuVecF flamePosR;
    Mtx mtx;
    Mtx mtxHand;
    Mtx mtxHead;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    BOOL fireF;
    float motTime;
    float angle;
    float span;
    double spanLen;
    float step;
    float spanFire;
    double spanFireLen;
    s16 pan;
    int i;
    s16 j;
    s16 k;
    int frameNo;
    HU3DMODELID killId;
    HU3DMODEL *killModelP;
    M560_BILL *killBill;
    HU3DMODELID billMdlId;
    HU3DMODELID funcId;
    HU3DMODEL *funcModelP;
    M560_BILL *funcBill;
    HU3DMODELID blendId;
    HU3DMODEL *blendModelP;
    HU3DMODELID createId;
    HU3DMODELID createRet;
    HU3DMODELID handId;
    HU3DMODELID headId;
    HU3DMODELID emitId;
    M560_BILL *emitBill;
    M560_BILLPART *emitPart;
    M560_BILLPART *partRet;
    M560_BILLPART *part;
    GXColor *emitColorP;
    HU3DMODELID endId;
    HU3DMODEL *endModelP;
    M560_BILL *endBill;
    BOOL killedF;

    fireF = FALSE;
    work = obj->data;
    switch(work->mode) {
        case 2:
            M560KupaMotionSet(KupaObj[0], 3, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 120) {
                work->timer = 0;
                work->mode = 3;
                M560KupaMotionSet(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                work->timer++;
            }
            break;

        case 3:
            if(work->timer > 8) {
                work->timer = 0;
                work->mode = 0;
            } else {
                if(work->timer >= 0 && work->timer < 8) {
                    work->pos.z += 16.25f;
                }
                work->timer++;
            }
            break;

        case 4:
            M560KupaMotionSet(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer > 60) {
                work->timer = 0;
                work->mode = 1;
            } else {
                if(work->timer == 0) {
                    span = work->pos.z-(-600.0f);
                    spanLen = fabs(span);
                    step = spanLen;
                    work->speed.z = step/342.0f;
                }
                work->timer++;
            }
            break;

        case 1:
            if(work->billMdlId >= 0) {
                killId = work->billMdlId;
                killModelP = &Hu3DData[killId];
                killBill = killModelP->hookData;
                killBill->killF = 1;
            }
            Hu3DMotionSpeedSet(obj->mdlId[0], 0.8f);
            M560KupaMotionSet(obj, 8, 8.0f, HU3D_MOTATTR_LOOP);
            motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
            if(work->timer > 342.0f) {
                work->timer = 0;
                work->mode = 5;
                work->pos.z = -600.0f;
                M560KupaMotionSet(obj, 4, 8.0f, HU3D_MOTATTR_NONE);
                for(i=0; i<4; i++) {
                    player = PlayerObj[i]->data;
                    M560PlayerSignReset(player);
                }
            } else {
                if(work->timer == 0) {
                    spanFire = work->pos.z-(-600.0f);
                    spanFireLen = fabs(spanFire);
                    step = spanFireLen;
                    work->speed.z = step/342.0f;
                }
                work->pos.z += work->speed.z;
                if(work->motTime < 10.0f && motTime >= 10.0f) {
                    if(work->motNo == 8) {
                        M560QuakeSet(40, 10.0f, 0.95f, 90.0f, 1);
                        pan = M560PanGet(&work->pos);
                        HuAudFXPlayVolPan(0x2C7, M560KupaVolGet(), pan);
                    }
                    PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                    PSMTXMultVec(mtx, &flameL, &flamePosL);
                    PSVECAdd(&flamePosL, &work->pos, &flamePosL);
                    M560EffectDustRingCreate(1, &flamePosL);
                } else if(work->motTime < 60.0f && motTime >= 60.0f) {
                    if(work->motNo == 8) {
                        M560QuakeSet(40, 10.0f, 0.95f, 90.0f, 1);
                        pan = M560PanGet(&work->pos);
                        HuAudFXPlayVolPan(0x2C7, M560KupaVolGet(), pan);
                    }
                    PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                    PSMTXMultVec(mtx, &flameR, &flamePosR);
                    PSVECAdd(&flamePosR, &work->pos, &flamePosR);
                    M560EffectDustRingCreate(1, &flamePosR);
                }
                work->timer++;
            }
            work->motTime = motTime;
            break;

        case 5:
            if(work->timer == 0) {
                billMdlId = M560BillCreate(SprAnim, NULL, NULL, 512, 40.0f, 64, 64);
                funcId = billMdlId;
                funcModelP = &Hu3DData[funcId];
                funcBill = funcModelP->hookData;
                funcBill->func = M560BillPartMain;
                blendId = billMdlId;
                blendModelP = &Hu3DData[blendId];
                ((M560_BILL *)blendModelP->hookData)->unk6A = 0;
                Hu3DModelLayerSet(billMdlId, 5);
                createId = billMdlId;
                createRet = createId;
                work->billMdlId = createRet;
            }
            Hu3DMotionSpeedSet(obj->mdlId[0], 1.25f);
            if(work->timer > 45) {
                fireF = TRUE;
                if(SeFireId < 0) {
                    SeFireId = HuAudFXPlayPan(0x97B, M560PanGet(&work->pos));
                }
            } else {
                fireF = FALSE;
            }
            work->timer++;
            if(work->timer > 170) {
                work->mode = 6;
                work->timer = 0;
                Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
                if(SeFireId > 0) {
                    HuAudFXStop(SeFireId);
                    SeFireId = -1;
                }
            }
            break;

        case 6:
            M560KupaMotionSet(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
            work->timer++;
            if(work->timer > 60) {
                work->mode = 0;
                work->timer = 0;
            }
            break;

        case 7:
            if(M560PlayerAllDoneCheck()) {
                M560KupaMotionSet(obj, 6, 8.0f, HU3D_MOTATTR_NONE);
            } else {
                M560KupaMotionSet(obj, 5, 8.0f, HU3D_MOTATTR_NONE);
            }
            break;

        case 0:
            break;
    }
    if(work->billMdlId >= 0) {
        if(fireF) {
            handId = obj->mdlId[0];
            Hu3DModelObjMtxGet(handId, ItemHookMStr, mtxHand);
            posHand.x = mtxHand[0][3];
            posHand.y = mtxHand[1][3];
            posHand.z = mtxHand[2][3];
            headId = obj->mdlId[0];
            Hu3DModelObjMtxGet(headId, HeadStr, mtxHead);
            posHead.x = mtxHead[0][3];
            posHead.y = mtxHead[1][3];
            posHead.z = mtxHead[2][3];
            PSVECSubtract(&posHand, &posHead, &dir);
            angle = 180.0*(atan2(dir.x, dir.z)/M_PI);
            emitId = work->billMdlId;
            for(j=0; j<1; j++) {
                emitBill = Hu3DData[emitId].hookData;
                if(emitBill->killF) {
                    partRet = NULL;
                } else {
                    for(k=0, emitPart=emitBill->part; k<emitBill->maxCnt; k++, emitPart++) {
                        if(emitPart->no < 0) {
                            break;
                        }
                    }
                    if(k == emitBill->maxCnt) {
                        partRet = NULL;
                    } else {
                        emitColorP = &emitBill->color[k];
                        emitColorP->r = color.r;
                        emitColorP->g = color.g;
                        emitColorP->b = color.b;
                        emitColorP->a = color.a;
                        emitPart->pos = posHand;
                        emitPart->scale = 0.0f;
                        emitPart->zRot = 0.0f;
                        emitPart->cellNo = 0;
                        emitPart->unk00 = 0;
                        emitPart->no = k;
                        partRet = emitPart;
                    }
                }
                part = partRet;
                if(!part) {
                    break;
                }
                part->basePos = posHand;
                part->time = 0.0f;
                part->angle = angle;
                part->timeAdd = 10.0f;
                part->timeMax = 750.0f;
                part->posYTarget = 50.0f;
                part->angleOfs = (20.0f*frandf())-10.0f;
                part->timeAdd *= 0.8f+(0.4f*frandf());
                part->timeMax *= 0.9f+(0.3f*frandf());
            }
            if(SeFireId > 0) {
                firePos.x = 750.0*sin((M_PI*angle)/180.0);
                firePos.y = 0.0f;
                firePos.z = 750.0*cos((M_PI*angle)/180.0);
                HuAudFXPanning(SeFireId, M560PanGet(&firePos));
            }
        }
        endId = work->billMdlId;
        endModelP = &Hu3DData[endId];
        endBill = endModelP->hookData;
        if(endBill->killF && endBill->liveCnt == 0) {
            HuMemDirectFree(endBill->part);
            HuMemDirectFree(endBill->vtx);
            HuMemDirectFree(endBill->color);
            HuMemDirectFree(endBill->st);
            HuMemDirectFree(endBill->cellTbl);
            HuMemDirectFree(endBill->dlBuf);
            HuSprAnimKill(endBill->anim);
            HuMemDirectFree(endModelP->hookData);
            Hu3DModelKill(endId);
            killedF = TRUE;
        } else {
            killedF = FALSE;
        }
        if(killedF) {
            work->billMdlId = -1;
        }
    }
    M560QuakeMain();
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    frameNo = MgSeqFrameNoGet();
}

/* fn_1_3468 -- shift Bowser into a motion, once, with the roar that goes with it. */
static void M560KupaMotionSet(OMOBJ *obj, int motNo, float speed, u32 attr)
{
    M560_KUPA *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[motNo], 0.0f, speed, attr);
        work->motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
        if(work->motNo == 5) {
            HuAudFXPlayPan(0x2C9, M560PanGet(&work->pos));
            HuAudJinglePlay(0x7A);
        }
        if(work->motNo == 6) {
            HuAudFXPlayPan(0x2CA, M560PanGet(&work->pos));
            HuAudJinglePlay(0x7B);
        }
    }
}

/*
 * fn_1_354C -- push players apart. Anyone closer than 160 units in XZ is
 * shoved out along the line between them, weighted so the faster of the two
 * gives less ground, and then the one that was pushed is re-checked against
 * everybody -- which is what makes this recursive.
 *
 * A BUG IN THE ORIGINAL, reproduced. The second weight, the one that moves the
 * OTHER player, is `(0.6f*speedA)+(0.4f*speedA)` -- speedA twice, where the
 * first weight uses speedB for the 0.6 term. It reduces to speedA/(speedA+
 * speedB), so the other player is always pushed by this one's speed alone.
 * `0.6f*speedB` is plainly what was meant.
 */
static void M560PlayerHitCheck(OMOBJ *obj)
{
    M560_PLAYER *work = obj->data;
    M560_PLAYER *other;
    HuVecF vel;
    HuVecF dir;
    HuVecF posA;
    HuVecF posB;
    float speedA;
    float speedB;
    float overlap;
    float ratio;
    int i;

    PSVECSubtract(&work->pos, &work->posOld, &vel);
    speedA = PSVECMag(&vel);
    if(0.0f == speedA) {
        return;
    }
    for(i=0; i<4; i++) {
        if(i == work->no) {
            continue;
        }
        other = PlayerObj[i]->data;
        posA.x = work->pos.x;
        posA.y = work->pos.y;
        posA.z = work->pos.z;
        posA.y = 0.0f;
        posB.x = other->pos.x;
        posB.y = other->pos.y;
        posB.z = other->pos.z;
        posB.y = 0.0f;
        PSVECSubtract(&posA, &posB, &vel);
        overlap = PSVECMag(&vel);
        if(overlap >= 159.2f) {
            continue;
        }
        PSVECSubtract(&other->pos, &other->posOld, &vel);
        speedB = PSVECMag(&vel);
        PSVECSubtract(&posA, &posB, &dir);
        PSVECNormalize(&dir, &dir);
        overlap = 160.0f-overlap;
        ratio = ((0.6f*speedB)+(0.4f*speedA))/(speedA+speedB);
        work->pos.x += ratio*(overlap*dir.x);
        work->pos.y += ratio*(overlap*dir.y);
        work->pos.z += ratio*(overlap*dir.z);
        if(work->mode == 6) {
            ratio = ((0.6f*speedA)+(0.4f*speedA))/(speedA+speedB);
            other->pos.x += ratio*(overlap*-dir.x);
            other->pos.y += ratio*(overlap*-dir.y);
            other->pos.z += ratio*(overlap*-dir.z);
        }
        M560PlayerHitCheck(PlayerObj[i]);
    }
}

/* fn_1_381C */
static void M560BgmInit(void)
{
    BgmId = -1;
}

/* fn_1_3830 */
static void M560BgmPlay(void)
{
    BgmId = HuAudSStreamPlay(0x3F);
}

/* fn_1_3860 */
static void M560BgmFadeOut(void)
{
    HuAudSStreamFadeOut(BgmId, 100);
}

/* fn_1_3890 -- arm the screen shake. */
static void M560QuakeSet(u16 time, float amp, float decay, float freq, int flag)
{
    QuakeTime = time;
    QuakeAmp = amp;
    QuakeDecay = decay;
    QuakeFreq = freq;
    QuakeAngle = 90.0f;
    QuakeFlag = flag;
}

/*
 * fn_1_38EC -- one frame of the screen shake. The camera's own y is left
 * alone; this writes the object system's Center directly, so the shake rides
 * on top of whichever of the two views is current.
 */
static void M560QuakeMain(void)
{
    QuakeOfs = 0.0f;
    if(QuakeTime > 0) {
        QuakeOfs = QuakeAmp*sin((M_PI*QuakeAngle)/180.0);
        QuakeAngle += QuakeFreq;
        QuakeAmp *= QuakeDecay;
        QuakeTime--;
        if(QuakeFlag == 0) {
            Center.y = CameraView.center.y+QuakeOfs;
        } else {
            Center.y = CameraViewOpen.center.y+QuakeOfs;
        }
    }
}

/* fn_1_3A58 -- 3D position to stereo pan, 0..64 across the screen. */
static s16 M560PanGet(HuVecF *pos)
{
    HuVecF screen;
    s16 pan;

    Hu3D3Dto2D(pos, 1, &screen);
    pan = 32.0f+(64.0f*(screen.x/576.0f));
    return pan;
}

/* fn_1_3AD4 -- and to volume, off the vertical position. */
static s16 M560VolGet(HuVecF *pos)
{
    HuVecF screen;
    s16 vol;

    Hu3D3Dto2D(pos, 1, &screen);
    vol = 64.0f+(63.0f*(screen.y/480.0f));
    return vol;
}

/*
 * fn_1_3B50 -- how loud Bowser's breath is, as a function of how far he has
 * come forward: 88 at the back wall, rising to 127 by the time he reaches the
 * players. The span is measured from the spawn point to z = -600.
 */
static s16 M560KupaVolGet(void)
{
    M560_KUPA *kupa = KupaObj[0]->data;
    float span;
    double spanLen;
    float dist;
    double distLen;
    int max;
    s16 vol;

    span = KupaPos.z-(-600.0f);
    spanLen = fabs(span);
    max = spanLen;
    dist = KupaPos.z-kupa->pos.z;
    distLen = fabs(dist);
    vol = 88.0+(39.0*(distLen/max));
    return vol;
}

/* fn_1_3C8C -- empty the id list. */
static void M560IdListInit(void)
{
    IdListHead.prev = NULL;
    IdListHead.next = NULL;
}

/* fn_1_3CB0 -- push one id onto the front of the list. */
static void M560IdListAdd(u16 id, s16 value)
{
    M560_IDNODE *node;
    M560_IDNODE *head;
    M560_IDNODE *next;

    node = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M560_IDNODE), HU_MEMNUM_OVL);
    node->id = id;
    node->value = value;
    head = &IdListHead;
    next = head->next;
    head->next = node;
    if(NULL != next) {
        next->prev = node;
    }
    node->prev = head;
    node->next = next;
}

/* fn_1_3D38 -- find an id, unlink it, free it and hand back its value. */
static s16 M560IdListDel(s16 id)
{
    M560_IDNODE *node;
    M560_IDNODE *prev;
    M560_IDNODE *next;
    s16 value;

    for(node=IdListHead.next; NULL != node; node=node->next) {
        if(id == node->id) {
            value = node->value;
            prev = node->prev;
            next = node->next;
            prev->next = next;
            if(NULL != next) {
                next->prev = prev;
            }
            HuMemDirectFree(node);
            return value;
        }
    }
    return -1;
}

/* fn_1_3DDC -- empty the model cache. */
static void M560ModelCacheInit(void)
{
    int i;
    for(i=0; i<32; i++) {
        MdlCacheTbl[i].dataNum = 0;
        MdlCacheTbl[i].modelId = HU3D_MODELID_NONE;
    }
}

/*
 * fn_1_3E34 -- a 32-entry model cache. A data number already loaded is handed
 * back as a link rather than a second copy; a table that has filled up falls
 * through to an uncached create.
 */
static HU3DMODELID M560ModelCreate(unsigned int dataNum)
{
    int i;

    for(i=0; i<32; i++) {
        if(dataNum == MdlCacheTbl[i].dataNum) {
            return Hu3DModelLink(MdlCacheTbl[i].modelId);
        }
    }
    for(i=0; i<32; i++) {
        if(MdlCacheTbl[i].dataNum == 0) {
            MdlCacheTbl[i].dataNum = dataNum;
            MdlCacheTbl[i].modelId = Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
            return MdlCacheTbl[i].modelId;
        }
    }
    return Hu3DModelCreate(HuDataSelHeapReadNum(dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
}

/*
 * fn_1_3F48 -- interpolate between two points on a sin-squared curve, so the
 * move eases out of `from` and into `to`. `t` above 1 is clamped.
 */
static void M560VecEase(float t, HuVecF *from, HuVecF *to, HuVecF *out)
{
    float ratio;

    if(1.0f < t) {
        t = 1.0f;
    }
    ratio = sin((M_PI*(90.0f*t))/180.0)*sin((M_PI*(90.0f*t))/180.0);
    out->x = from->x+(ratio*(to->x-from->x));
    out->y = from->y+(ratio*(to->y-from->y));
    out->z = from->z+(ratio*(to->z-from->z));
}

/* fn_1_40A4 -- push a camera and remember where it ended up. */
static void M560CameraPosSet(HuVecF *pos, HuVecF *up, HuVecF *target)
{
    Hu3DCameraPosSetV(1, pos, up, target);
    CameraPosStart = *pos;
    CameraTargetStart = *target;
}

/*
 * fn_1_4130 -- one frame of a camera move, on the same sin-squared curve as
 * everything else here. Both M560VecEase calls are inlined.
 */
static BOOL M560CameraMoveMain(float t, HuVecF *up)
{
    HuVecF pos;
    HuVecF target;

    M560VecEase(t, &CameraPosStart, &CameraPosEnd, &pos);
    M560VecEase(t, &CameraTargetStart, &CameraTargetEnd, &target);
    Hu3DCameraPosSetV(1, &pos, up, &target);
    if(1.0f <= t) {
        return TRUE;
    }
    CameraMoveF = 1;
    return FALSE;
}

/*
 * fn_1_4464 -- the same move for four cameras at once, each with its own
 * pair of endpoints. Both M560VecEase calls are inlined here too.
 */
static BOOL M560CameraMoveMainMulti(float t, HuVecF *up)
{
    HuVecF pos;
    HuVecF target;
    int i;

    for(i=0; i<4; i++) {
        M560VecEase(t, &CameraPosStartTbl[i], &CameraPosEndTbl[i], &pos);
        M560VecEase(t, &CameraTargetStartTbl[i], &CameraTargetEndTbl[i], &target);
        Hu3DCameraPosSetV(1 << i, &pos, up, &target);
    }
    if(1.0f <= t) {
        return TRUE;
    }
    CameraMoveF = 1;
    return FALSE;
}

/* fn_1_4848 -- turn `from` toward `to` by `speed` of the way, wrapping at 360. */
static float M560AngleApproach(float from, float to, float speed)
{
    float diff;
    float result;

    diff = fmod(to-from, 360.0);
    if(0.0f > diff) {
        diff += 360.0f;
    }
    if(180.0f < diff) {
        diff -= 360.0f;
    }
    result = fmod(from+(diff*speed), 360.0);
    if(0.0f > result) {
        result += 360.0f;
    }
    return result;
}

/* fn_1_494C -- stop the sequence, at 1000 if the caller does not care. */
static void M560SeqFadeOut(s32 speed)
{
    if(SeqId >= 0) {
        if(speed < 0) {
            speed = 1000;
        }
        HuAudSeqFadeOut(SeqId, speed);
    }
    SeqId = -1;
}

/* fn_1_49B8 -- the world position of a named object inside a model. */
static void M560ModelObjPosGet(HU3DMODELID modelId, char *name, HuVecF *pos)
{
    Mtx mtx;

    Hu3DModelObjMtxGet(modelId, name, mtx);
    pos->x = mtx[0][3];
    pos->y = mtx[1][3];
    pos->z = mtx[2][3];
}

/* fn_1_4A10 -- a random int in [min, max). */
static int M560RandRange(int min, int max)
{
    return min+frandmod(max-min);
}

/*
 * fn_1_4A4C -- do two circles overlap, in XZ. Both differences are computed
 * twice rather than kept in a local, which is what the object does.
 */
static BOOL M560HitCheck(HuVecF *a, HuVecF *b, float radiusA, float radiusB)
{
    if(((b->x-a->x)*(b->x-a->x))+((b->z-a->z)*(b->z-a->z)) < ((radiusA+radiusB)*(radiusA+radiusB))) {
        return TRUE;
    }
    return FALSE;
}

/* fn_1_4AAC -- pan again, this time over a caller-chosen range. */
static s16 M560PanGetEx(HuVecF *pos, int base, int range)
{
    HuVecF screen;
    s16 pan;

    Hu3D3Dto2D(pos, 1, &screen);
    pan = base+((screen.x/576.0f)*(range-base));
    return pan;
}

/* fn_1_4B70 -- and volume. */
static s16 M560VolGetEx(HuVecF *pos, int base, int range)
{
    HuVecF screen;
    s16 vol;

    Hu3D3Dto2D(pos, 1, &screen);
    vol = base+((screen.y/480.0f)*(range-base));
    return vol;
}

/*
 * fn_1_4C34 -- one frame of every live quad, and the only thing in the
 * overlay that can put a player out.
 *
 * Each quad spirals outward from its base: `time` is both the radius and the
 * clock, so it walks out along `angle` while the alpha follows a cosine down
 * to nothing and the texture cell steps through the sheet. Once it is past
 * cell 12 -- late in its life, when it has spread wide -- it stops testing for
 * hits. A player within 90 units in XZ who is neither already burning nor
 * already finished goes to mode 8.
 *
 * posA and posB are written and never read. They are in the object, so they
 * are here.
 */
static void M560BillPartMain(HU3DMODEL *modelP, M560_BILL *work, Mtx mtx)
{
    M560_BILLPART *part = work->part;
    GXColor *color = work->color;
    M560_PLAYER *player;
    HuVecF posA[4];
    HuVecF posB[4];
    float ratio;
    float alpha;
    float ofs;
    float alphaClamp;
    BOOL hitF;
    s16 i;
    s16 j;

    work->liveCnt = 0;
    for(i=0; i<work->maxCnt; i++, part++, color++) {
        if(part->no < 0) {
            continue;
        }
        part->time += part->timeAdd;
        if(part->timeMax < part->time) {
            part->no = -1;
            continue;
        }
        work->liveCnt++;
        if(NULL != work->posSrc) {
            part->basePos = *work->posSrc;
        }
        if(NULL != work->angleSrc) {
            part->angle = *work->angleSrc;
        }
        part->pos.x = part->basePos.x+(part->time*sin((M_PI*(part->angle+part->angleOfs))/180.0));
        part->pos.y += 0.03f*(part->posYTarget-part->pos.y);
        part->pos.z = part->basePos.z+(part->time*cos((M_PI*(part->angle+part->angleOfs))/180.0));
        ratio = part->time/part->timeMax;
        alpha = 128.0*cos((M_PI*(90.0f*ratio))/180.0);
        if(255.0f < alpha) {
            alphaClamp = 255.0f;
        } else {
            alphaClamp = alpha;
        }
        color->a = alphaClamp;
        part->cellNo = work->cellNum*ratio;
        if(work->cellNum <= part->cellNo) {
            part->cellNo = work->cellNum-1;
        }
        ratio *= 2.0f;
        if(1.0f < ratio) {
            ratio = 1.0f;
        }
        part->scale = 1.5+(3.0*sin((M_PI*(100.0f*ratio))/180.0));
        ofs = 40.0f*part->scale;
        for(j=0; j<4; j++) {
            player = PlayerObj[j]->data;
            posA[j] = player->pos;
            posA[j].y += ofs;
            posB[j] = player->pos;
            posB[j].y += 170.0f-ofs;
            if(part->cellNo < 12) {
                if(((part->pos.x-player->pos.x)*(part->pos.x-player->pos.x))+((part->pos.z-player->pos.z)*(part->pos.z-player->pos.z)) < 8100.0f) {
                    hitF = TRUE;
                } else {
                    hitF = FALSE;
                }
                if(hitF && player->unk6C == 0 && player->doneF == 0) {
                    player->mode = 8;
                    player->unk6C = 1;
                }
            }
        }
    }
}

/* fn_1_510C -- transpose the rotation of a matrix and clear its translation. */
static void M560MtxTranspose(Mtx src, Mtx dst)
{
    dst[0][0] = src[0][0];
    dst[1][0] = src[0][1];
    dst[2][0] = src[0][2];
    dst[0][1] = src[1][0];
    dst[1][1] = src[1][1];
    dst[2][1] = src[1][2];
    dst[0][2] = src[2][0];
    dst[1][2] = src[2][1];
    dst[2][2] = src[2][2];
    dst[0][3] = 0.0f;
    dst[1][3] = 0.0f;
    dst[2][3] = 0.0f;
}

/* fn_1_5188 -- scale a run of vectors. */
static void M560VecScaleN(HuVecF *src, HuVecF *dst, float scale, s16 count)
{
    s16 i;

    for(i=0; i<count; i++, src++, dst++) {
        dst->x = src->x*scale;
        dst->y = src->y*scale;
        dst->z = src->z*scale;
    }
}

/*
 * fn_1_51E4 -- the four texture corners of one cell, anticlockwise from the
 * top left. `cell` indexes a table of cell origins.
 */
static void M560TexCoordSet(HuVec2f *st, HuVec2f *cellTbl, s16 cell, float width, float height)
{
    st[0].x = cellTbl[cell].x;
    st[0].y = cellTbl[cell].y;
    st[1].x = cellTbl[cell].x+width;
    st[1].y = cellTbl[cell].y;
    st[2].x = cellTbl[cell].x+width;
    st[2].y = cellTbl[cell].y+height;
    st[3].x = cellTbl[cell].x;
    st[3].y = cellTbl[cell].y+height;
}

/*
 * fn_1_5288 -- the draw hook: set up one TEV stage, point GX at the three
 * arrays and replay the display list built once in M560BillCreate.
 *
 * The whole per-frame cost is here, and it is all vertex writing. Each live
 * quad's four corners are the base quad scaled by the particle's own scale,
 * rotated about Z if it has any, and translated to its position; a dead quad
 * has its four corners zeroed so the list can stay a fixed size. The texture
 * corners come from the cell table. M560MtxTranspose, M560VecScaleN and
 * M560TexCoordSet are all defined above and are all inlined here.
 *
 * The intensity formats take their colour from the rasterizer rather than the
 * texture, which is what the I8/I4 test on the bitmap format selects.
 */
static void M560BillHook(HU3DMODEL *modelP, Mtx *mtx)
{
    M560_BILL *work = modelP->hookData;
    M560_BILLPART *part;
    HuVecF *vtx;
    HuVec2f *st;
    Mtx mtxT;
    ROMtx mtxRo;
    Mtx mtxRot;
    Mtx mtxRotWork;
    HuVecF quad[4];
    HuVecF corner[4];
    HuVecF out[4];
    M560BILLFUNC func;
    s16 fmt;
    s16 i;

    if(work->killF && work->liveCnt == 0) {
        return;
    }
    GXLoadPosMtxImm(*mtx, GX_PNMTX0);
    GXSetNumTevStages(1);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    fmt = work->anim->bmp->dataFmt & ANIM_BMP_FMTMASK;
    if(fmt == ANIM_BMP_I4 || fmt == ANIM_BMP_I8) {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXA, GX_CC_RASC, GX_CC_ZERO);
    } else {
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC, GX_CC_ZERO);
    }
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, 0, GX_DF_CLAMP, GX_AF_NONE);
    if(modelP->attr & HU3D_ATTR_ZWRITE_OFF) {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
    } else {
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    }
    HuSprTexLoad(work->anim, 0, GX_TEXMAP0, GX_REPEAT, GX_REPEAT, GX_LINEAR);
    GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_GEQUAL, 1);
    GXSetZCompLoc(GX_FALSE);
    switch(work->unk6A) {
        case 0:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_NOOP);
            break;
        case 1:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
            break;
        case 2:
            GXSetBlendMode(GX_BM_BLEND, GX_BL_ZERO, GX_BL_INVSRCCLR, GX_LO_NOOP);
            break;
    }
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetArray(GX_VA_POS, work->vtx, sizeof(HuVecF));
    GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetArray(GX_VA_CLR0, work->color, sizeof(GXColor));
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetArray(GX_VA_TEX0, work->st, sizeof(HuVec2f));
    M560MtxTranspose(*mtx, mtxT);
    PSMTXReorder(mtxT, mtxRo);
    if(!omPauseChk()) {
        if(work->func) {
            func = work->func;
            func(modelP, work, *mtx);
        }
    }
    part = work->part;
    vtx = work->vtx;
    st = work->st;
    PSMTXROMultVecArray(mtxRo, work->quad, quad, 4);
    for(i=0; i<work->maxCnt; i++, part++, st+=4) {
        if(part->no < 0) {
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            vtx->x = vtx->y = vtx->z = 0.0f;
            vtx++;
            continue;
        }
        if(0.0f == part->zRot) {
            M560VecScaleN(quad, corner, part->scale, 4);
            PSVECAdd(&corner[0], &part->pos, vtx++);
            PSVECAdd(&corner[1], &part->pos, vtx++);
            PSVECAdd(&corner[2], &part->pos, vtx++);
            PSVECAdd(&corner[3], &part->pos, vtx++);
        } else {
            M560VecScaleN(work->quad, corner, part->scale, 4);
            PSMTXRotRad(mtxRot, 'Z', 0.017453292f*part->zRot);
            PSMTXConcat(mtxT, mtxRot, mtxRotWork);
            PSMTXMultVecArray(mtxRotWork, corner, out, 4);
            PSVECAdd(&out[0], &part->pos, vtx++);
            PSVECAdd(&out[1], &part->pos, vtx++);
            PSVECAdd(&out[2], &part->pos, vtx++);
            PSVECAdd(&out[3], &part->pos, vtx++);
        }
        if(part->cellNo != -1) {
            M560TexCoordSet(st, work->cellTbl, part->cellNo, work->cellSizeX, work->cellSizeY);
        }
    }
    DCFlushRangeNoSync(work->vtx, (work->maxCnt*sizeof(HuVecF))*4);
    DCFlushRangeNoSync(work->st, (work->maxCnt*sizeof(HuVec2f))*4);
    GXCallDisplayList(work->dlBuf, work->dlSize);
}

/*
 * fn_1_59D0 -- lay out a texture-cell table: `cellX` cells across, each
 * `w` by `h` of the sheet. M560BillCreate is its only caller and inlines it.
 */
static void M560CellTblMake(HuVec2f *st, s16 count, s16 cellX, float w, float h)
{
    s16 i;
    s16 cx;
    s16 cy;

    for(i=0; i<count; i++, st++) {
        cx = i%cellX;
        cy = i/cellX;
        st->x = cx*w;
        st->y = cy*h;
    }
}

/*
 * fn_1_5A9C -- build the billboard system: `maxCnt` camera-facing quads drawn
 * from one animation sheet, all in a single display list.
 *
 * The list is built once here and never rebuilt. It indexes position, colour
 * and texture arrays that the per-frame hook rewrites in place, so a frame
 * costs one GXCallDisplayList and no geometry work at all. That is why the
 * quad corners, the cell table and the vertex arrays are all allocated up
 * front and why every index in the list is a constant.
 *
 * `cellW` and `cellH` are the size of one cell in texels; zero for either
 * means the whole sheet is one cell.
 */
static HU3DMODELID M560BillCreate(ANIMDATA *anim, HuVecF *posSrc, float *angleSrc, s16 maxCnt, float size, s16 cellW, s16 cellH)
{
    HU3DMODELID modelId;
    HU3DMODEL *modelP;
    M560_BILL *work;
    M560_BILLPART *part;
    HuVecF *vtx;
    HuVec2f *st;
    GXColor *color;
    void *dl;
    void *dlP;
    s16 cellX;
    s16 cellY;
    s16 i;

    modelId = Hu3DHookFuncCreate(M560BillHook);
    modelP = &Hu3DData[modelId];
    modelP->hookData = HuMemDirectMallocNum(HEAP_MODEL, sizeof(M560_BILL), modelP->mallocNo);
    work = modelP->hookData;
    anim->useNum++;
    work->anim = anim;
    work->posSrc = posSrc;
    work->angleSrc = angleSrc;
    work->maxCnt = maxCnt;
    work->unk6A = 0;
    work->func = NULL;
    work->liveCnt = maxCnt;
    work->killF = 0;
    work->part = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(M560_BILLPART), modelP->mallocNo);
    part = work->part;
    for(i=0; i<maxCnt; i++, part++) {
        part->no = -1;
        part->cellNo = -1;
    }
    work->vtx = HuMemDirectMallocNum(HEAP_MODEL, (maxCnt*sizeof(HuVecF))*4, modelP->mallocNo);
    vtx = work->vtx;
    for(i=0; i<maxCnt*4; i++, vtx++) {
        vtx->x = 0.0f;
        vtx->y = 0.0f;
        vtx->z = 0.0f;
    }
    work->color = HuMemDirectMallocNum(HEAP_MODEL, maxCnt*sizeof(GXColor), modelP->mallocNo);
    color = work->color;
    for(i=0; i<maxCnt; i++, color++) {
        color->r = 255;
        color->g = 255;
        color->b = 255;
        color->a = 255;
    }
    work->st = HuMemDirectMallocNum(HEAP_MODEL, (maxCnt*sizeof(HuVec2f))*4, modelP->mallocNo);
    st = work->st;
    for(i=0; i<maxCnt; i++) {
        st->x = 0.0f;
        st->y = 0.0f;
        st++;
        st->x = 1.0f;
        st->y = 0.0f;
        st++;
        st->x = 1.0f;
        st->y = 1.0f;
        st++;
        st->x = 0.0f;
        st->y = 1.0f;
        st++;
    }
    if(cellW != 0 || cellH != 0) {
        cellX = anim->bmp->sizeX/cellW;
        cellY = anim->bmp->sizeY/cellH;
        work->cellNum = cellX*cellY;
        work->cellSizeX = 1.0f/cellX;
        work->cellSizeY = 1.0f/cellY;
    } else {
        cellX = 1;
        work->cellNum = 1;
        work->cellSizeX = 1.0f;
        work->cellSizeY = 1.0f;
    }
    work->cellTbl = HuMemDirectMallocNum(HEAP_MODEL, work->cellNum*sizeof(HuVec2f), modelP->mallocNo);
    M560CellTblMake(work->cellTbl, work->cellNum, cellX, work->cellSizeX, work->cellSizeY);
    work->quad[0].x = work->quad[3].x = work->quad[2].y = work->quad[3].y = -size;
    work->quad[1].x = work->quad[2].x = work->quad[0].y = work->quad[1].y = size;
    work->quad[0].z = work->quad[1].z = work->quad[2].z = work->quad[3].z = 0.0f;
    dl = HuMemDirectMallocNum(HEAP_MODEL, 0x20000, modelP->mallocNo);
    dlP = dl;
    GXBeginDisplayList(dlP, 0x20000);
    GXBegin(GX_QUADS, GX_VTXFMT0, maxCnt*4);
    for(i=0; i<maxCnt; i++) {
        GXPosition1x16(i*4);
        GXColor1x16(i);
        GXTexCoord1x16(i*4);
        GXPosition1x16((i*4)+1);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+1);
        GXPosition1x16((i*4)+2);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+2);
        GXPosition1x16((i*4)+3);
        GXColor1x16(i);
        GXTexCoord1x16((i*4)+3);
    }
    work->dlSize = GXEndDisplayList();
    DCFlushRangeNoSync(dl, work->dlSize);
    work->dlBuf = HuMemDirectMallocNum(HEAP_MODEL, work->dlSize, modelP->mallocNo);
    memcpy(work->dlBuf, dl, work->dlSize);
    DCFlushRangeNoSync(work->dlBuf, work->dlSize);
    HuMemDirectFree(dl);
    return modelId;
}

/* fn_1_60F4 -- take the first free quad, or nothing if the system is full. */
static M560_BILLPART *M560BillPartCreate(HU3DMODELID modelId, HuVecF *pos, GXColor *color, float scale, float zRot)
{
    M560_BILL *work = Hu3DData[modelId].hookData;
    M560_BILLPART *part;
    GXColor *colorP;
    s16 i;

    if(work->killF) {
        return NULL;
    }
    for(i=0, part=work->part; i<work->maxCnt; i++, part++) {
        if(part->no < 0) {
            break;
        }
    }
    if(i == work->maxCnt) {
        return NULL;
    }
    colorP = &work->color[i];
    colorP->r = color->r;
    colorP->g = color->g;
    colorP->b = color->b;
    colorP->a = color->a;
    part->pos = *pos;
    part->scale = scale;
    part->zRot = zRot;
    part->cellNo = 0;
    part->unk00 = 0;
    part->no = i;
    return part;
}

/* fn_1_61FC -- the per-frame update the hook runs over every live quad. */
static void M560BillFuncSet(HU3DMODELID modelId, M560BILLFUNC func)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M560_BILL *work = modelP->hookData;
    work->func = func;
}

/* fn_1_6234 */
static void M560BillUnk6ASet(HU3DMODELID modelId, u8 value)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    ((M560_BILL *)modelP->hookData)->unk6A = value;
}

/*
 * fn_1_6264 -- ask for the system to go away. It does not free anything; the
 * teardown happens in M560BillKill once the last quad has expired.
 */
static void M560BillKillReq(HU3DMODELID modelId)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M560_BILL *work = modelP->hookData;
    work->killF = 1;
}

/* fn_1_62A0 -- and the teardown, once nothing is left alive. */
static BOOL M560BillKill(HU3DMODELID modelId)
{
    HU3DMODEL *modelP = &Hu3DData[modelId];
    M560_BILL *work = modelP->hookData;

    if(work->killF && work->liveCnt == 0) {
        HuMemDirectFree(work->part);
        HuMemDirectFree(work->vtx);
        HuMemDirectFree(work->color);
        HuMemDirectFree(work->st);
        HuMemDirectFree(work->cellTbl);
        HuMemDirectFree(work->dlBuf);
        HuSprAnimKill(work->anim);
        HuMemDirectFree(modelP->hookData);
        Hu3DModelKill(modelId);
        return TRUE;
    }
    return FALSE;
}

/*
 * fn_1_635C -- emit `count` quads at once, each with its own jitter: the
 * direction spread over 20 degrees, the outward speed over 0.8..1.2 of the
 * base and the lifetime over 0.9..1.2. M560BillPartCreate is inlined.
 */
static void M560BillPartEmit(HU3DMODELID modelId, s16 count, HuVecF *pos, float angle, float timeMax, float posYTarget)
{
    M560_BILLPART *part;
    GXColor color = { 0xFF, 0xFF, 0xFF, 0xFF };
    s16 i;

    for(i=0; i<count; i++) {
        part = M560BillPartCreate(modelId, pos, &color, 0.0f, 0.0f);
        if(!part) {
            break;
        }
        part->basePos = *pos;
        part->time = 0.0f;
        part->angle = angle;
        part->timeAdd = 10.0f;
        part->timeMax = timeMax;
        part->posYTarget = posYTarget;
        part->angleOfs = (20.0f*frandf())-10.0f;
        part->timeAdd *= 0.8f+(0.4f*frandf());
        part->timeMax *= 0.9f+(0.3f*frandf());
    }
}

/*
 * fn_1_65BC -- the overlay's one billboard system: 40-unit quads off the
 * sprite sheet ObjectSetup loaded, cut into 64x64 cells. Both helpers above
 * are inlined here.
 */
static HU3DMODELID M560BillCreateEx(HuVecF *posSrc, float *angleSrc, s16 maxCnt)
{
    HU3DMODELID modelId = M560BillCreate(SprAnim, posSrc, angleSrc, maxCnt, 40.0f, 64, 64);

    M560BillFuncSet(modelId, M560BillPartMain);
    M560BillUnk6ASet(modelId, 0);
    Hu3DModelLayerSet(modelId, 5);
    return modelId;
}
