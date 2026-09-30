/*
 * m550dll/m550.c -- ObjectSetup, the nine sequence hooks and the model-hook
 * plumbing the other two files use.
 *
 * IN PROGRESS. See NOTES.md beside this file.
 *
 * Three of the nine hooks are pure dispatch: fadeIn, main and preWinner each
 * index one of the three tables below by Work->subMode and call through it,
 * which is why game.c is eleven entry points rather than a monolith.
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
#include "game/audio.h"
#include "game/frand.h"
#include "game/mg/seqman.h"

#include "datadir_enum.h"
#include "datanum/charmot.h"
#include "datanum/char.h"

#include "REL/m550dll/m550.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"

/* game.c, through the three sub-state tables below */
void M550FadeIn0(void);
void M550FadeIn1(void);
void M550FadeIn2(void);
void M550Main0(void);
void M550Main1(void);
void M550Main2(void);
void M550PreWin0(void);
void M550PreWin1(void);
void M550PreWin2(void);
void M550PreWin3(void);
void M550PreWin4(void);
void M550GameUnk2364(void);
void M550GameUnk2618(void);

/* --- forward declarations, asm address order --- */

void ObjectSetup(void);
static void M550InitHook(s16 mode, s16 frameNo);
static void M550FadeInHook(s16 mode, s16 frameNo);
static void M550StartHook(s16 mode, s16 frameNo);
static void M550MainHook(s16 mode, s16 frameNo);
static void M550FinishHook(s16 mode, s16 frameNo);
static void M550PreWinnerHook(s16 mode, s16 frameNo);
static void M550WinnerHook(s16 mode, s16 frameNo);
static void M550FadeOutHook(s16 mode, s16 frameNo);
static void M550CloseHook(s16 mode, s16 frameNo);
static void M550ModelFlush(OMOBJ *obj);
void M550ItemPosSet(int player, HuVecF *pos, HuVecF *rot);
static void M550ItemPosUpdateOne(int player);
void M550ItemPosUpdate(void);
void M550ItemHookVecGet(void);
void M550Unk10BC(int player);
static void M550ModelReset(M550_MODEL *mdl);
static void M550ObjCreate(void);

/* --- .data --- */

/* data_8 -- files/data/m550.bin 0x00..0x3B, the whole arena in order. */
static unsigned int StageDataTbl[60] = {
    DATANUM(DATA_m550, 0x00), DATANUM(DATA_m550, 0x01), DATANUM(DATA_m550, 0x02),
    DATANUM(DATA_m550, 0x03), DATANUM(DATA_m550, 0x04), DATANUM(DATA_m550, 0x05),
    DATANUM(DATA_m550, 0x06), DATANUM(DATA_m550, 0x07), DATANUM(DATA_m550, 0x08),
    DATANUM(DATA_m550, 0x09), DATANUM(DATA_m550, 0x0A), DATANUM(DATA_m550, 0x0B),
    DATANUM(DATA_m550, 0x0C), DATANUM(DATA_m550, 0x0D), DATANUM(DATA_m550, 0x0E),
    DATANUM(DATA_m550, 0x0F), DATANUM(DATA_m550, 0x10), DATANUM(DATA_m550, 0x11),
    DATANUM(DATA_m550, 0x12), DATANUM(DATA_m550, 0x13), DATANUM(DATA_m550, 0x14),
    DATANUM(DATA_m550, 0x15), DATANUM(DATA_m550, 0x16), DATANUM(DATA_m550, 0x17),
    DATANUM(DATA_m550, 0x18), DATANUM(DATA_m550, 0x19), DATANUM(DATA_m550, 0x1A),
    DATANUM(DATA_m550, 0x1B), DATANUM(DATA_m550, 0x1C), DATANUM(DATA_m550, 0x1D),
    DATANUM(DATA_m550, 0x1E), DATANUM(DATA_m550, 0x1F), DATANUM(DATA_m550, 0x20),
    DATANUM(DATA_m550, 0x21), DATANUM(DATA_m550, 0x22), DATANUM(DATA_m550, 0x23),
    DATANUM(DATA_m550, 0x24), DATANUM(DATA_m550, 0x25), DATANUM(DATA_m550, 0x26),
    DATANUM(DATA_m550, 0x27), DATANUM(DATA_m550, 0x28), DATANUM(DATA_m550, 0x29),
    DATANUM(DATA_m550, 0x2A), DATANUM(DATA_m550, 0x2B), DATANUM(DATA_m550, 0x2C),
    DATANUM(DATA_m550, 0x2D), DATANUM(DATA_m550, 0x2E), DATANUM(DATA_m550, 0x2F),
    DATANUM(DATA_m550, 0x30), DATANUM(DATA_m550, 0x31), DATANUM(DATA_m550, 0x32),
    DATANUM(DATA_m550, 0x33), DATANUM(DATA_m550, 0x34), DATANUM(DATA_m550, 0x35),
    DATANUM(DATA_m550, 0x36), DATANUM(DATA_m550, 0x37), DATANUM(DATA_m550, 0x38),
    DATANUM(DATA_m550, 0x39), DATANUM(DATA_m550, 0x3A), DATANUM(DATA_m550, 0x3B)
};

/*
 * data_F8 -- five motions per character, in charNo order. The five file
 * numbers are the same in every row, and CharMotionCreate remaps the
 * directory to the character it is given, so which row is picked does not
 * actually matter -- which is just as well, because M550InitHook indexes it
 * by the duellist's PLAYER number rather than by charNo.
 */
static unsigned int CharMotDataTbl[13][5] = {
    { CHAR_HSF_c000m1_474, CHAR_HSF_c000m1_475, CHARMOT_HSF_c000m1_433, CHARMOT_HSF_c000m1_481, CHARMOT_HSF_c000m1_474 },
    { DATANUM(DATA_luigi, 0xAC), DATANUM(DATA_luigi, 0xAD), DATANUM(DATA_luigimot, 0x60), DATANUM(DATA_luigimot, 0x80), DATANUM(DATA_luigimot, 0x7D) },
    { DATANUM(DATA_peach, 0xAC), DATANUM(DATA_peach, 0xAD), DATANUM(DATA_peachmot, 0x60), DATANUM(DATA_peachmot, 0x80), DATANUM(DATA_peachmot, 0x7D) },
    { DATANUM(DATA_yoshi, 0xAC), DATANUM(DATA_yoshi, 0xAD), DATANUM(DATA_yoshimot, 0x60), DATANUM(DATA_yoshimot, 0x80), DATANUM(DATA_yoshimot, 0x7D) },
    { DATANUM(DATA_wario, 0xAC), DATANUM(DATA_wario, 0xAD), DATANUM(DATA_wariomot, 0x60), DATANUM(DATA_wariomot, 0x80), DATANUM(DATA_wariomot, 0x7D) },
    { DATANUM(DATA_daisy, 0xAC), DATANUM(DATA_daisy, 0xAD), DATANUM(DATA_daisymot, 0x60), DATANUM(DATA_daisymot, 0x80), DATANUM(DATA_daisymot, 0x7D) },
    { DATANUM(DATA_waluigi, 0xAC), DATANUM(DATA_waluigi, 0xAD), DATANUM(DATA_waluigimot, 0x60), DATANUM(DATA_waluigimot, 0x80), DATANUM(DATA_waluigimot, 0x7D) },
    { DATANUM(DATA_kinopio, 0xAC), DATANUM(DATA_kinopio, 0xAD), DATANUM(DATA_kinopiomot, 0x60), DATANUM(DATA_kinopiomot, 0x80), DATANUM(DATA_kinopiomot, 0x7D) },
    { DATANUM(DATA_teresa, 0xAC), DATANUM(DATA_teresa, 0xAD), DATANUM(DATA_teresamot, 0x60), DATANUM(DATA_teresamot, 0x80), DATANUM(DATA_teresamot, 0x7D) },
    { DATANUM(DATA_minikoopa, 0xAC), DATANUM(DATA_minikoopa, 0xAD), DATANUM(DATA_minikoopamot, 0x60), DATANUM(DATA_minikoopamot, 0x80), DATANUM(DATA_minikoopamot, 0x7D) },
    { DATANUM(DATA_minikoopa, 0xAC), DATANUM(DATA_minikoopa, 0xAD), DATANUM(DATA_minikoopamot, 0x60), DATANUM(DATA_minikoopamot, 0x80), DATANUM(DATA_minikoopamot, 0x7D) },
    { DATANUM(DATA_minikoopa, 0xAC), DATANUM(DATA_minikoopa, 0xAD), DATANUM(DATA_minikoopamot, 0x60), DATANUM(DATA_minikoopamot, 0x80), DATANUM(DATA_minikoopamot, 0x7D) },
    { DATANUM(DATA_minikoopa, 0xAC), DATANUM(DATA_minikoopa, 0xAD), DATANUM(DATA_minikoopamot, 0x60), DATANUM(DATA_minikoopamot, 0x80), DATANUM(DATA_minikoopamot, 0x7D) }
};

/* data_1FC -- all nine hooks are used. */
static MGSEQ_PARAM SeqParam = {
    0, 0,
    M550InitHook,
    M550FadeInHook,
    M550StartHook,
    M550MainHook,
    M550FinishHook,
    M550PreWinnerHook,
    M550WinnerHook,
    M550FadeOutHook,
    M550CloseHook
};

static void (*FadeInFuncTbl[3])(void) = { M550FadeIn0, M550FadeIn1, M550FadeIn2 };
static void (*MainFuncTbl[3])(void) = { M550Main0, M550Main1, M550Main2 };
static void (*PreWinFuncTbl[5])(void) = { M550PreWin0, M550PreWin1, M550PreWin2, M550PreWin3, M550PreWin4 };

/* --- .bss --- */

MGTIMER *Unk0;               /* bss_0 -- the duel clock */
M550_COM Com[2];             /* bss_4 */
static HU3DMOTID MotIdTbl[10];      /* bss_24 -- five motions per duellist */
OMCAMERAVIEW CameraView[4];  /* bss_38 */
static M550_MODEL Models[M550_MODEL_MAX];  /* bss_A8 */
M550_WORK Work;              /* bss_14AC */

/* ===== decoded functions, asm address order ===== */

/* ObjectSetup -- the overlay's only export. */
void ObjectSetup(void)
{
    s16 i;

    for(i=0; i<M550_MODEL_MAX; i++) {
        Models[i].modelId = HU3D_MODELID_NONE;
    }
    M550WorkInit(&Work, Models, StageDataTbl);
    Work.objman = omInitObjMan(50, 0x2000);
    omGameSysInit(Work.objman);
    omAddObjEx(Work.objman, 0x7FDA, 0, 0, OM_GRP_NONE, omOutView);
    omAddObjEx(Work.objman, 0x7FDA, 0, 0, OM_GRP_NONE, M550PadRead);
    MgSeqCreate(&SeqParam);
}

/*
 * fn_1_198 -- MGSEQ_MODE_INIT. The whole overlay's bring-up: the arena, the
 * two duellists and their motions, the camera, the one light, the shadow and
 * the three objects that run every frame.
 */
static void M550InitHook(s16 mode, s16 frameNo)
{
    HuVecF shadowPos;
    HuVecF shadowUp;
    HuVecF shadowTarget;
    HU3DLIGHTID lightId;

    M550StageModelCreate(2);
    M550CharMotDataSet(CharMotDataTbl[Work.chr[0].no], CharMotDataTbl[Work.chr[1].no]);
    M550CharMotIdSet(&MotIdTbl[0], &MotIdTbl[5]);
    M550CharModelCreate();
    M550CharMotionCreate();
    omAddObjEx(Work.objman, 0x7FDA, 0, 0, OM_GRP_NONE, M550MotionExec);
    M550ObjCreate();
    Center.x = 0.0f;
    Center.y = 1000.0f;
    Center.z = 100.0f;
    CRot.x = -90.0f;
    CRot.y = 0.0f;
    CRot.z = 0.0f;
    CZoom = 4000.0f;
    CameraView[1].center.x = 0.0f;
    CameraView[1].center.y = 1150.0f;
    CameraView[1].center.z = 0.0f;
    CameraView[1].rot.x = -10.0f;
    CameraView[1].rot.y = 0.0f;
    CameraView[1].rot.z = 0.0f;
    CameraView[1].zoom = 700.0f;
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 100000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraScissorSet(1, 0, 0, 640, 480);
    lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
    Hu3DGLightInfinitytSet(lightId);
    Hu3DGLightStaticSet(lightId, 1);
    omAddObjEx(Work.objman, 0x7FDA, 0, 0, OM_GRP_NONE, M550ModelFlush);
    Hu3DBGColorSet(0, 0, 0);
    Hu3DShadowCreate(45.0f, 20.0f, 15000.0f);
    shadowPos.x = 0.0f;
    shadowPos.y = 1200.0f;
    shadowPos.z = 600.0f;
    shadowUp.x = 0.0f;
    shadowUp.y = 1.0f;
    shadowUp.z = 0.0f;
    shadowTarget.x = 0.0f;
    shadowTarget.y = 0.0f;
    shadowTarget.z = 0.0f;
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);
    Work.player[0].motNo = 0;
    Work.player[0].speed = 1.0f;
    Work.player[0].time = 0.0f;
    Work.player[0].attr = HU3D_MOTATTR_LOOP;
    Work.player[1].motNo = 0;
    Work.player[1].speed = 1.0f;
    Work.player[1].time = 0.0f;
    Work.player[1].attr = HU3D_MOTATTR_LOOP;
    Hu3DFogClear();
    MgSeqModeDelaySet(mode+1, -1);
    omAddObjEx(Work.objman, 0x7FDA, 0, 0, OM_GRP_NONE, M550StageMain);
    MgSeqModeNext();
}

/* fn_1_6B4 -- MGSEQ_MODE_FADEIN, dispatched by sub-state. */
static void M550FadeInHook(s16 mode, s16 frameNo)
{
    FadeInFuncTbl[Work.mode[0]]();
}

/* fn_1_6F8 -- MGSEQ_MODE_START. */
static void M550StartHook(s16 mode, s16 frameNo)
{
    Work.mode[0] = 0;
    Work.mode[1] = 0;
    MgSeqModeDelaySet(mode+1, -1);
    M550ItemPosUpdate();
}

/* fn_1_750 -- MGSEQ_MODE_MAIN, dispatched by sub-state. */
static void M550MainHook(s16 mode, s16 frameNo)
{
    MainFuncTbl[Work.mode[0]]();
}

/* fn_1_794 -- MGSEQ_MODE_FINISH. */
static void M550FinishHook(s16 mode, s16 frameNo)
{
    MgSeqModeDelaySet(mode+1, -1);
    if(Work.mode[0] != 0) {
        M550GameUnk2618();
    } else {
        M550GameUnk2364();
    }
    MgSeqModeDelaySet(mode+1, -1);
}

/* fn_1_7FC -- MGSEQ_MODE_PREWIN, dispatched by sub-state. */
static void M550PreWinnerHook(s16 mode, s16 frameNo)
{
    PreWinFuncTbl[Work.mode[0]]();
}

/* fn_1_840 -- MGSEQ_MODE_WINNER. */
static void M550WinnerHook(s16 mode, s16 frameNo)
{
    if(Work.mode[0] != 0) {
        CZoom += 5.0f;
    }
    M550ItemPosUpdate();
    MgSeqModeNext();
}

/* fn_1_8A0 -- MGSEQ_MODE_FADEOUT. */
static void M550FadeOutHook(s16 mode, s16 frameNo)
{
    if(Work.mode[0] != 0) {
        CZoom += 5.0f;
    }
    if(!WipeCheckEnd()) {
        MgSeqModeNext();
    }
    M550ItemPosUpdate();
}

/* fn_1_910 -- MGSEQ_MODE_CLOSE, and empty. */
static void M550CloseHook(s16 mode, s16 frameNo)
{
}

/*
 * fn_1_914 -- the one place the model table reaches Hu3D. Everything else in
 * the overlay only writes pos and rot.
 */
static void M550ModelFlush(OMOBJ *obj)
{
    M550_MODEL *mdl;
    int i;

    for(mdl=Models, i=0; i<M550_MODEL_MAX; i++, mdl++) {
        if(mdl->modelId < 0) {
            continue;
        }
        Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
        Hu3DModelRotSetV(mdl->modelId, &mdl->rot);
    }
}

/* fn_1_984 -- set every material's invAlpha on one model. */
void M550MatAlphaSet(int mdlNo, float alpha)
{
    HU3DMODEL *modelP = &Hu3DData[Work.models[mdlNo].modelId];
    HSFDATA *hsf = modelP->hsf;
    HSFMATERIAL *material = hsf->material;
    int i;

    for(i=0; i<modelP->hsf->materialNum; i++, material++) {
        material->invAlpha = alpha;
    }
}

/*
 * fn_1_A00 -- park one duellist's forty-one held-item models on the same
 * position and rotation. The slots are 30 + 11 per player, and an id of zero
 * -- not -1 -- is what counts as unused here.
 */
void M550ItemPosSet(int player, HuVecF *pos, HuVecF *rot)
{
    M550_MODEL *mdl;
    float x;
    float y;
    float z;
    int i;

    x = pos->x;
    y = pos->y;
    z = pos->z;
    for(i=0; i<30; i++) {
        mdl = &Models[(player*30)+(i+6)];
        if(mdl->modelId != 0) {
            Hu3DModelPosSet(mdl->modelId, x, y, z);
            mdl->pos.x = x;
            mdl->pos.y = y;
            mdl->pos.z = z;
            mdl->rot.x = rot->x;
            mdl->rot.y = rot->y;
            mdl->rot.z = rot->z;
        }
    }
    for(i=0; i<11; i++) {
        mdl = &Models[(player*11)+(i+126)];
        if(mdl->modelId != 0) {
            Hu3DModelPosSet(mdl->modelId, x, y, z);
            mdl->pos.x = x;
            mdl->pos.y = y;
            mdl->pos.z = z;
            mdl->rot.x = rot->x;
            mdl->rot.y = rot->y;
            mdl->rot.z = rot->z;
        }
    }
}

/* fn_1_B5C -- where one duellist's item hook is, and everything it carries. */
static void M550ItemPosUpdateOne(int player)
{
    Mtx hookMtx;
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;

    PSMTXIdentity(mtx);
    Hu3DModelObjPosGet(Work.models[player+2].modelId, CharModelItemHookGet(Work.chr[player].charNo, 1, 4), &pos);
    Hu3DModelObjMtxGet(Work.models[player+2].modelId, CharModelItemHookGet(Work.chr[player].charNo, 1, 4), hookMtx);
    PSMTXConcat(hookMtx, mtx, hookMtx);
    Hu3DMtxRotGet(hookMtx, &rot);
    M550ItemPosSet(player, &pos, &rot);
}

/* fn_1_D64 -- and both of them. */
void M550ItemPosUpdate(void)
{
    int i;

    for(i=0; i<2; i++) {
        M550ItemPosUpdateOne(i);
    }
}

/* fn_1_F7C -- the same two hooks, kept for game.c rather than applied. */
void M550ItemHookVecGet(void)
{
    Mtx hookMtx;
    Mtx mtx;
    HuVecF pos;
    HuVecF rot;
    int i;

    for(i=0; i<2; i++) {
        PSMTXIdentity(mtx);
        Hu3DModelObjPosGet(Work.models[i+2].modelId, CharModelItemHookGet(Work.chr[i].charNo, 1, 4), &pos);
        Hu3DModelObjMtxGet(Work.models[i+2].modelId, CharModelItemHookGet(Work.chr[i].charNo, 1, 4), hookMtx);
        PSMTXConcat(hookMtx, mtx, hookMtx);
        Hu3DMtxRotGet(hookMtx, &rot);
        Work.hookVec[i*2] = pos;
        Work.hookVec[(i*2)+1] = rot;
    }
}

/*
 * ===========================================================================
 * NOT YET DECOMPILED.
 * ===========================================================================
 */
/*
 * fn_1_10BC -- bring in one duellist's marker, offset from their item hook:
 * 80 forward, 20 up and 30 to whichever side they are on.
 */
void M550Unk10BC(int player)
{
    HuVecF pos;
    M550_MODEL *mdl;

    Hu3DModelObjPosGet(Work.models[player+2].modelId, CharModelItemHookGet(Work.chr[player].charNo, 1, 4), &pos);
    mdl = &Models[player+149];
    Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DMotionSpeedSet(mdl->modelId, 3.0f);
    pos.z += 80.0f;
    pos.x += 30-(player*60);
    pos.y += 20.0f;
    mdl->pos = pos;
    Hu3DModelPosSetV(mdl->modelId, &mdl->pos);
}

/* fn_1_11F0 -- put one model back at the origin, still and visible. */
static void M550ModelReset(M550_MODEL *mdl)
{
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    Hu3DModelPosSet(mdl->modelId, 0.0f, 0.0f, 0.0f);
    Hu3DModelRotSet(mdl->modelId, 0.0f, 0.0f, 0.0f);
    mdl->pos.x = 0.0f;
    mdl->pos.y = 0.0f;
    mdl->pos.z = 0.0f;
    mdl->rot.x = 0.0f;
    mdl->rot.y = 0.0f;
    mdl->rot.z = 0.0f;
    Hu3DModelCameraSet(mdl->modelId, 1);
    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
    Hu3DModelAttrReset(mdl->modelId, HU3D_ATTR_DISPOFF);
}

/*
 * fn_1_131C -- everything the duel itself draws: two runs of thirty models
 * per duellist, eleven more, the object hooked to their hand, their marker,
 * and one shared model outside the loop. M550ModelReset is inlined at every
 * one of the six creation sites.
 */
static void M550ObjCreate(void)
{
    M550_MODEL *mdl;
    int i;
    int j;

    for(i=0; i<2; i++) {
        for(j=0; j<30; j++) {
            mdl = &Models[(i*30)+(j+6)];
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[j+2], HU_MEMNUM_OVL, HEAP_MODEL));
            M550ModelReset(mdl);
        }
        for(j=0; j<30; j++) {
            mdl = &Models[(i*30)+(j+66)];
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[32], HU_MEMNUM_OVL, HEAP_MODEL));
            M550ModelReset(mdl);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
            Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
            Hu3DModelLayerSet(mdl->modelId, 3);
        }
        for(j=0; j<11; j++) {
            mdl = &Models[(i*11)+(j+126)];
            mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[j+33], HU_MEMNUM_OVL, HEAP_MODEL));
            M550ModelReset(mdl);
            Hu3DMotionTimeSet(mdl->modelId, 0.0f);
            Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
            Hu3DModelLayerSet(mdl->modelId, 2);
        }
        mdl = &Models[i+4];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[44], HU_MEMNUM_OVL, HEAP_MODEL));
        M550ModelReset(mdl);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelLayerSet(mdl->modelId, 5);
        Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
        Hu3DModelHookSet(Models[i+2].modelId, CharModelItemHookGet(Work.chr[i].charNo, 1, 0), mdl->modelId);
        mdl = &Models[i+149];
        mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[46], HU_MEMNUM_OVL, HEAP_MODEL));
        M550ModelReset(mdl);
        Hu3DMotionTimeSet(mdl->modelId, 0.0f);
        Hu3DModelLayerSet(mdl->modelId, 4);
        Hu3DMotionSpeedSet(mdl->modelId, 0.0f);
        Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
    }
    mdl = &Models[148];
    mdl->modelId = Hu3DModelCreate(HuDataSelHeapReadNum(StageDataTbl[45], HU_MEMNUM_OVL, HEAP_MODEL));
    M550ModelReset(mdl);
    Hu3DMotionTimeSet(mdl->modelId, 0.0f);
    Hu3DMotionSpeedSet(mdl->modelId, 1.0f);
    Hu3DModelLayerSet(mdl->modelId, 4);
    Hu3DModelAttrSet(mdl->modelId, HU3D_ATTR_DISPOFF);
}
