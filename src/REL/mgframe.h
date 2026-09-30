/*
 * mgframe.h -- the minigame framework every Mario Party 5 overlay compiles in.
 *
 * WHAT THIS IS. Hudson gave each minigame overlay the same ~41 support
 * functions -- an object-manager bring-up, a camera model with an interpolator,
 * a shake, a debug free-camera, a hand-rolled flow object, a timer wrapper, a
 * pad-stick reader and a block of vector helpers. They are not a library: the
 * original compiles them *inside each overlay's translation unit*, which is why
 * they appear once per REL with their own static copies of the same three
 * OSReport strings. m524dll and m570dll were decompiled independently and 40 of
 * the 41 came out character-for-character identical (the 41st, the debug
 * camera, differs only in whether it prints a readout). This file is that
 * block, lifted once.
 *
 * WHY IT IS A HEADER AND NOT A .c. Because the original compiles it into each
 * overlay, a separately-compiled version would produce a different translation
 * unit -- different inlining decisions, different function order, and no way to
 * check a new overlay against its original object. It has to be #included.
 *
 * WHY IT IS INCLUDED MORE THAN ONCE. CodeWarrior only inlines a function it has
 * already seen, so *definition order decides the instruction stream*, and the
 * two overlays hoist different subsets of this block above their game code:
 * m524dll needs the flow control and the pad helpers up top, m570dll needs only
 * MgCameraMoveCheck and MgObjManInit. So the file is written to be included at
 * as many points as an overlay needs, each time naming the sections it wants:
 *
 *     #define MGF_S_OBJMAN
 *     #include "REL/mgframe.h"
 *
 * Every function carries a permanent MGF_HAVE_<name> guard, so it is emitted at
 * the *first* point that asks for it and skipped everywhere after. The section
 * selectors are #undef'd on the way out, so each include names its own set.
 * Within one include, functions come out in this file's order; to force a
 * different order, use two includes. m570dll does exactly that for the flow
 * block, whose original order is MgFlowEntry *before* MgFlowSet.
 *
 * SECTIONS, in the order this file emits them:
 *
 *   MGF_S_DECL             all the prototypes (put it in the overlay's own
 *                          forward-declaration block)
 *   MGF_S_DATA             the OSReport strings
 *   MGF_S_BSS              DebugCameraStart, MgMusicId, objman
 *   MGF_S_PLAYERCONF       MgPlayerConfSet
 *   MGF_S_PAD              MgPadStkMagGet, MgPadStkAngleGet
 *   MGF_S_FLOWCTL          MgFlowSet/Next/Get/Check, MgTimer*Ex, MgNop
 *   MGF_S_OBJMAN           MgObjManInit, MgLightCreate
 *   MGF_S_FLOWENTRY        MgFlowEntry
 *   MGF_S_CAMERAMOVECHECK  MgCameraMoveCheck on its own (m570dll hoists it)
 *   MGF_S_CAMERA           the thirteen camera functions
 *   MGF_S_FLOWMAIN         MgFlowMain, MgFlowExitWait
 *   MGF_S_FLOWSTEP         the six flow steps
 *   MGF_S_MATH             the vector and angle helpers
 *
 * KNOBS, all optional, all defined before the first include and left defined:
 *
 *   MGF_DEBUG_READOUT      emit the debug camera's print8 readout and its
 *                          format strings. m524dll has them; m570dll's object
 *                          has no such strings, so its debug camera is silent.
 *   MGF_LINK_PLAYERCONFSET
 *   MGF_LINK_VECAPPROACH
 *   MGF_LINK_ANGLEAPPROACH
 *   MGF_LINK_VECORBIT
 *   MGF_LINK_OBJMAN
 *   MGF_LINK_PADSTKMAGGET
 *   MGF_LINK_PLANENORMALGET
 *   MGF_LINK_PLANEDISTGET
 *   MGF_LINK_PLANECROSSGET linkage for the things a second translation
 *                          unit may need to reach; each defaults to `static`.
 *                          Define one to nothing to make it external.
 *
 * THE PLAYER WORK. MgPlayerConfSet fills in a header that every overlay's
 * player struct starts with. Spell that header with MGF_PLAYER_HEAD and pass
 * the work as (MGFPLAYER *) -- the cast costs nothing and keeps the layout
 * guaranteed rather than assumed.
 *
 * VERIFYING A CHANGE HERE. Both users are checked function by function against
 * the objects dtk splits out of the real RELs, so touching this file means
 * re-checking both. Keep a copy of the three objects, rebuild, and compare:
 *
 *   cd games/mp5
 *   cp build/GP5E01_00/src/REL/m524Dll/m524.o /tmp/m524.before.o     # and the
 *   ./build/tools/ninja build/GP5E01_00/src/REL/m524Dll/m524.o \    # other two
 *                       build/GP5E01_00/src/REL/m570Dll/m570.o \
 *                       build/GP5E01_00/src/REL/m570Dll/player.o
 *   ./fndiff.py diff /tmp/m524.before.o build/GP5E01_00/src/REL/m524Dll/m524.o
 *
 * Nothing about the emitted code should move; the extraction that created this
 * file left all 161 functions across the three objects byte-identical.
 *
 * Use fndiff.py rather than objdump directly. An object that includes this
 * header has TWO .text sections, both at VMA 0, so objdump labels every address
 * in both and prints each function twice -- once with a body that is not its
 * own. fndiff.py filters symbols by the section readelf reports.
 *
 * See games/mp5/ROADMAP.md and games/mp5/src/REL/m524dll/m524.c.
 */

#ifndef MGFRAME_H
#define MGFRAME_H

#include "game/object.h"
#include "game/gamework.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/wipe.h"
#include "game/pad.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/gamemes.h"
#include "game/printfunc.h"
#include "game/mg/timer.h"

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

#ifndef MGF_LINK_PLAYERCONFSET
#define MGF_LINK_PLAYERCONFSET static
#endif
#ifndef MGF_LINK_VECAPPROACH
#define MGF_LINK_VECAPPROACH static
#endif
#ifndef MGF_LINK_ANGLEAPPROACH
#define MGF_LINK_ANGLEAPPROACH static
#endif
#ifndef MGF_LINK_VECORBIT
#define MGF_LINK_VECORBIT static
#endif
#ifndef MGF_LINK_OBJMAN
#define MGF_LINK_OBJMAN static
#endif
#ifndef MGF_LINK_PADSTKMAGGET
#define MGF_LINK_PADSTKMAGGET static
#endif
#ifndef MGF_LINK_PLANENORMALGET
#define MGF_LINK_PLANENORMALGET static
#endif
#ifndef MGF_LINK_PLANEDISTGET
#define MGF_LINK_PLANEDISTGET static
#endif
#ifndef MGF_LINK_PLANECROSSGET
#define MGF_LINK_PLANECROSSGET static
#endif

typedef struct MgfStageLight_s {
    HuVecF pos;
    HuVecF target;
    GXColor color;
} MGF_STAGELIGHT;

/*
 * The camera description the framework passes around. `mode` 1 means the eye is
 * derived from `angle` and `dist` about `target` (MgCameraAngleApply); mode 0
 * means `pos` is used as written.
 */
typedef struct MgfCameraView_s {
    int no;
    int mode;
    float fov;
    float near;
    float far;
    HuVecF pos;
    HuVecF up;
    HuVecF target;
    HuVecF angle;
    float dist;
} MGF_CAMERAVIEW;

typedef struct MgfCameraMove_s {
    MGF_CAMERAVIEW *view;
    MGF_CAMERAVIEW start;
    MGF_CAMERAVIEW end;
    float timeMax;
    float time;
    int stat;
} MGF_CAMERAMOVE;

#define MGF_CAMERAMOVE_ACTIVE (1 << 1)

typedef void (*MGFLOWFUNC)(OMOBJ *obj);

/* The work of the single flow object -- the overlay's state machine. */
typedef struct MgfFlow_s {
    int step;
    MGFLOWFUNC *flowTbl;
    int flowMax;
    GAMEMESID gameMesId;
    MGTIMER *timer;
    int timerType;
    int timerMaxTime;
    int timerEndTime;
    int timerRecordTime;
    int unk24;
    int work[16];
} MGF_FLOW;

/*
 * The head of every overlay's player work -- what MgPlayerConfSet writes. Spell
 * it at the top of the overlay's own struct so the two cannot drift.
 */
#define MGF_PLAYER_HEAD \
    /* 0x00 */ s16 no;        \
    /* 0x02 */ s16 charNo;    \
    /* 0x04 */ s16 padNo;     \
    /* 0x06 */ s16 grp;       \
    /* 0x08 */ s16 dif;       \
    /* 0x0C */ int comF;      \
    /* 0x10 */ HuVecF pos;    \
    /* 0x1C */ HuVecF rot;    \
    /* 0x28 */ int mode

typedef struct MgfPlayer_s {
    MGF_PLAYER_HEAD;
} MGFPLAYER;

#endif /* MGFRAME_H */


/* ===== declarations ===== */
#ifdef MGF_S_DECL
MGF_LINK_PLAYERCONFSET void MgPlayerConfSet(MGFPLAYER *work, s16 no);
MGF_LINK_PADSTKMAGGET float MgPadStkMagGet(s16 padNo);
static float MgPadStkAngleGet(s16 padNo);
void MgFlowSet(OMOBJ *obj, int step);
void MgFlowNext(OMOBJ *obj);
static int MgFlowGet(OMOBJ *obj);
static BOOL MgFlowCheck(OMOBJ *obj, int step);
static void MgTimerParamSetEx(OMOBJ *obj, int type, int maxTime, int endTime, int recordTime);
static BOOL MgTimerDoneCheckEx(OMOBJ *obj);
static void MgTimerStartEx(OMOBJ *obj);
static void MgNop(void);
static void MgObjManInit(void);
static HU3DLIGHTID MgLightCreate(MGF_STAGELIGHT *light);
static OMOBJ *MgFlowEntry(MGFLOWFUNC *flowTbl);
static MGF_CAMERAVIEW *MgCameraCreate(MGF_CAMERAVIEW *src);
static void MgCameraViewSet(MGF_CAMERAVIEW *view);
static void MgDebugCameraMain(OMOBJ *obj);
static void MgDebugCameraStartSet(MGF_CAMERAVIEW *view);
static void MgDebugCameraCreate(MGF_CAMERAVIEW *view);
static void MgCameraAngleApply(MGF_CAMERAVIEW *view);
static void MgCameraAngleGet(MGF_CAMERAVIEW *view);
static void MgCameraMoveMain(OMOBJ *obj);
OMOBJ *MgCameraMoveEntry(MGF_CAMERAVIEW *view, MGF_CAMERAVIEW *target, float time);
static BOOL MgCameraMoveCheck(OMOBJ *obj);
static void MgCameraMoveKill(OMOBJ *obj);
static void MgCameraShakeMain(OMOBJ *obj);
static void MgCameraShakeEntry(MGF_CAMERAVIEW *view, int time, int amp);
static void MgFlowMain(OMOBJ *obj);
static void MgFlowExitWait(OMOBJ *obj);
static void MgFlowWipeWait(OMOBJ *obj);
static void MgFlowReturn(OMOBJ *obj);
static void MgFlowGameMes(OMOBJ *obj, s16 mesNo, s16 type);
static void MgFlowMgStart(OMOBJ *obj);
static void MgFlowMgFinish(OMOBJ *obj);
static void MgFlowTimerCreate(OMOBJ *obj);
MGF_LINK_VECAPPROACH BOOL MgVecApproach(HuVecF *pos, HuVecF *target, HuVecF *rot, float speed);
MGF_LINK_ANGLEAPPROACH float MgAngleApproach(float from, float to, float speed);
MGF_LINK_VECORBIT BOOL MgVecOrbit(HuVecF *center, HuVecF *pos, HuVecF *target, float speed);
MGF_LINK_PLANENORMALGET void MgPlaneNormalGet(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *normal);
MGF_LINK_PLANEDISTGET float MgPlaneDistGet(HuVecF *normal, HuVecF *plane, HuVecF *pos);
MGF_LINK_PLANECROSSGET BOOL MgPlaneCrossGet(HuVecF *normal, HuVecF *plane, HuVecF *from, HuVecF *to, HuVecF *cross);
#endif


/* ===== .data ===== */
#ifdef MGF_S_DATA
#ifdef MGF_DEBUG_READOUT
/* The debug free-camera's readout, kept because the object still compiles it. */
static char PosMesStr[] = "pos : x=%.2f y=%.2f z=%.2f";
static char TargetMesStr[] = "int : x=%.2f y=%.2f z=%.2f";
static char UpMesStr[] = "up  : x=%.2f y=%.2f z=%.2f";
static char AngleMesStr[] = "ang : x=%f y=%f";
static char DistMesStr[] = "dis : %.2f";
static char PosModeMesStr[] = "mod : pos";
static char AngleModeMesStr[] = "mod : ang";
#endif
static char CameraNumDiffMesStr[] = "MgCameraMoveEntry : Camera Number Different\n";
static char FlowSetOverMesStr[] = "MgFlowSet : Value is Max Over\n";
static char FlowNextOverMesStr[] = "MgFlowNext : Value is Max Over\n";
#endif


/* ===== .bss ===== */
#ifdef MGF_S_BSS
static MGF_CAMERAVIEW DebugCameraStart;
static s16 MgMusicId;
MGF_LINK_OBJMAN OMOBJMAN *objman;
#endif


/* ===== 1. the player work header ===== */
#if defined(MGF_S_PLAYERCONF) && !defined(MGF_HAVE_MgPlayerConfSet)
#define MGF_HAVE_MgPlayerConfSet
/* m524 fn_1_57F4 -- the out-of-line half of an overlay's player init. */
MGF_LINK_PLAYERCONFSET void MgPlayerConfSet(MGFPLAYER *work, s16 no)
{
    work->no = no;
    work->charNo = GwPlayerConf[no].charNo;
    work->padNo = GwPlayerConf[no].padNo;
    work->grp = GwPlayerConf[no].grp;
    work->comF = GwPlayerConf[no].type;
    work->dif = GwPlayerConf[no].dif;
    work->mode = 0;
    work->pos.z = work->pos.y = work->pos.x = 0.0f;
    work->rot.z = work->rot.y = work->rot.x = 0.0f;
}
#endif


/* ===== 2. the pad stick ===== */
#if defined(MGF_S_PAD) && !defined(MGF_HAVE_MgPadStkMagGet)
#define MGF_HAVE_MgPadStkMagGet
/* m524 fn_1_4E1C */
MGF_LINK_PADSTKMAGGET float MgPadStkMagGet(s16 padNo)
{
    return sqrtf((float)(HuSquare(HuPadStkX[padNo])+HuSquare(HuPadStkY[padNo])));
}
/* m524 fn_1_4FA0 -- stick direction in degrees, 0 straight up, clockwise. */
static float MgPadStkAngleGet(s16 padNo)
{
    float angle = ((atan2(HuPadStkY[padNo], HuPadStkX[padNo])/M_PI)*180.0)-90.0;
    if(angle < 0.0f) {
        angle += 360.0f;
    }
    return angle;
}
#endif


/* ===== 3. flow control and the timer wrapper ===== */
#if defined(MGF_S_FLOWCTL) && !defined(MGF_HAVE_MgFlowSet)
#define MGF_HAVE_MgFlowSet
/* MgFlowSet */
void MgFlowSet(OMOBJ *obj, int step)
{
    MGF_FLOW *work = obj->data;
    if(step >= work->flowMax) {
        OSReport(FlowSetOverMesStr);
        return;
    }
    work->step = step;
}
/* MgFlowNext */
void MgFlowNext(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    if(work->step == work->flowMax-1) {
        OSReport(FlowNextOverMesStr);
        return;
    }
    work->step++;
}
/* m524 fn_1_5338 */
static int MgFlowGet(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    return work->step;
}
/* m524 fn_1_5354 */
static BOOL MgFlowCheck(OMOBJ *obj, int step)
{
    MGF_FLOW *work = obj->data;
    if(step == MgFlowGet(obj)) {
        return TRUE;
    }
    return FALSE;
}
/* m524 fn_1_53A0 -- stash the timer's parameters until MgFlowTimerCreate runs.
 * Times arrive in seconds and are kept in frames. */
static void MgTimerParamSetEx(OMOBJ *obj, int type, int maxTime, int endTime, int recordTime)
{
    MGF_FLOW *work = obj->data;
    work->timerType = type;
    work->timerMaxTime = maxTime*60;
    work->timerEndTime = endTime*60;
    work->timerRecordTime = recordTime*60;
}
/* m524 fn_1_53D4 */
static BOOL MgTimerDoneCheckEx(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    return MgTimerDoneCheck(work->timer);
}
/* m524 fn_1_5410 */
static void MgTimerStartEx(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    if(work->timer->stopF == 0) {
        work->timer->stopF = TRUE;
        work->timer->mode = MGTIMER_MODE_ON;
    }
}
/* m524 fn_1_5450 */
static void MgNop(void)
{
}
#endif


/* ===== 4. object manager and stage light ===== */
#if defined(MGF_S_OBJMAN) && !defined(MGF_HAVE_MgObjManInit)
#define MGF_HAVE_MgObjManInit
/* m524 fn_1_3554 -- the object manager bring-up ObjectSetup opens with. */
static void MgObjManInit(void)
{
    objman = omInitObjMan(200, 0x1000);
    MgMusicId = -1;
    omGameSysInit(objman);
}
/* m524 fn_1_36E4 -- the stage light. Never reached out of line: ObjectSetup is
 * its only caller and the compiler inlines it there. */
static HU3DLIGHTID MgLightCreate(MGF_STAGELIGHT *light)
{
    HU3DLIGHTID lightId = Hu3DGLightCreateV(&light->pos, &light->target, &light->color);
    Hu3DGLightStaticSet(lightId, 1);
    Hu3DGLightInfinitytSet(lightId);
    return lightId;
}
#endif


/* ===== 5. the flow constructor ===== */
#if defined(MGF_S_FLOWENTRY) && !defined(MGF_HAVE_MgFlowEntry)
#define MGF_HAVE_MgFlowEntry
/* m524 fn_1_5198 -- the out-of-line flow constructor; ObjectSetup inlines it. */
static OMOBJ *MgFlowEntry(MGFLOWFUNC *flowTbl)
{
    OMOBJ *obj;
    MGF_FLOW *work;
    int max;
    int i;

    for(max=0; flowTbl[max] != NULL; max++) {
        ;
    }
    obj = omAddObjEx(objman, 0x2000, 0, 0, OM_GRP_NONE, MgFlowMain);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MGF_FLOW), HU_MEMNUM_OVL);
    work = obj->data;
    work->flowMax = max;
    work->flowTbl = flowTbl;
    work->step = 0;
    work->gameMesId = -1;
    for(i=0; i<16; i++) {
        work->work[i] = 0;
    }
    return obj;
}
#endif


/* ===== 6. MgCameraMoveCheck, on its own for overlays that hoist it ===== */
#if (defined(MGF_S_CAMERAMOVECHECK) || defined(MGF_S_CAMERA)) && !defined(MGF_HAVE_MgCameraMoveCheck_EARLY)
#ifdef MGF_S_CAMERAMOVECHECK
#define MGF_HAVE_MgCameraMoveCheck_EARLY
#define MGF_HAVE_MgCameraMoveCheck
/* m524 fn_1_4BB0 */
static BOOL MgCameraMoveCheck(OMOBJ *obj)
{
    MGF_CAMERAMOVE *work = obj->data;
    if(work->stat & MGF_CAMERAMOVE_ACTIVE) {
        return TRUE;
    }
    return FALSE;
}
#endif
#endif


/* ===== 7. the camera ===== */
#if defined(MGF_S_CAMERA) && !defined(MGF_HAVE_MgCameraCreate)
#define MGF_HAVE_MgCameraCreate
/* m524 fn_1_35A8 -- register a camera with Hu3D and keep a heap copy of its view. */
static MGF_CAMERAVIEW *MgCameraCreate(MGF_CAMERAVIEW *src)
{
    MGF_CAMERAVIEW *view = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MGF_CAMERAVIEW), HU_MEMNUM_OVL);
    *view = *src;
    Hu3DCameraCreate(src->no);
    Hu3DCameraViewportSet(src->no, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(src->no, src->fov, src->near, src->far, 1.2f);
    MgCameraViewSet(src);
    return view;
}
/* m524 fn_1_3694 -- push a view at Hu3D, deriving the eye from angle+distance
 * first when the view is in that mode. */
static void MgCameraViewSet(MGF_CAMERAVIEW *view)
{
    if(view->mode == 1) {
        MgCameraAngleApply(view);
    }
    Hu3DCameraPosSetV(view->no, &view->pos, &view->up, &view->target);
}
/*
 * m524 fn_1_3740 -- the debug free camera. Nothing creates it in the shipped
 * game; hold Y and it drives the live view off the pad. Whether it also prints
 * that view is per overlay: m524dll's object carries the format strings and
 * m570dll's does not, so the readout is behind MGF_DEBUG_READOUT.
 */
static void MgDebugCameraMain(OMOBJ *obj)
{
    MGF_CAMERAVIEW *view = ((MGF_CAMERAVIEW *)(obj)->work[0]);
    if(!(HuPadBtn[0] & PAD_BUTTON_Y)) {
        return;
    }
#ifdef MGF_DEBUG_READOUT
    print8(16, 48, 1.5f, PosMesStr, view->pos.x, view->pos.y, view->pos.z);
    print8(16, 64, 1.5f, TargetMesStr, view->target.x, view->target.y, view->target.z);
    print8(16, 80, 1.5f, UpMesStr, view->up.x, view->up.y, view->up.z);
    print8(16, 96, 1.5f, AngleMesStr, view->angle.x, view->angle.y);
    print8(16, 112, 1.5f, DistMesStr, view->dist);
    if(obj->work[2] == 0) {
        print8(16, 128, 1.5f, PosModeMesStr);
    } else {
        print8(16, 128, 1.5f, AngleModeMesStr);
    }
#endif
    if(HuPadBtnDown[0] & PAD_BUTTON_START) {
        *view = DebugCameraStart;
    }
    if(HuPadBtnDown[0] & PAD_BUTTON_B) {
        obj->work[2]++;
        if(obj->work[2] == 2) {
            obj->work[2] = 0;
        }
    }
    switch(obj->work[2]) {
        case 0:
            view->pos.z -= 0.1f*HuPadTrigL[0];
            view->pos.z += 0.1f*HuPadTrigR[0];
            view->pos.x += 0.1f*HuPadStkX[0];
            view->pos.y += 0.1f*HuPadStkY[0];
            MgCameraAngleGet(view);
            break;
        case 1:
            view->angle.x -= 0.1f*HuPadStkY[0];
            view->angle.y += 0.1f*HuPadStkX[0];
            view->dist -= 0.1f*HuPadTrigL[0];
            view->dist += 0.1f*HuPadTrigR[0];
            MgCameraAngleApply(view);
            break;
    }
    if(HuPadBtn[0] & PAD_BUTTON_X) {
        view->target.z -= 0.1f*HuPadSubStkY[0];
    } else {
        view->target.x += 0.1f*HuPadSubStkX[0];
        view->target.y += 0.1f*HuPadSubStkY[0];
    }
    Hu3DCameraPosSetV(view->no, &view->pos, &view->up, &view->target);
}
/* m524 fn_1_3DA0 */
static void MgDebugCameraStartSet(MGF_CAMERAVIEW *view)
{
    DebugCameraStart = *view;
}
/* m524 fn_1_3CF4 */
static void MgDebugCameraCreate(MGF_CAMERAVIEW *view)
{
    OMOBJ *obj = omAddObjEx(objman, 0x4000, 0, 0, OM_GRP_NONE, MgDebugCameraMain);
    (obj)->work[0] = (u32)(view);
    if(view->mode == 0) {
        obj->work[2] = 0;
    } else {
        obj->work[2] = 1;
    }
    MgDebugCameraStartSet(view);
}
/* m524 fn_1_3DD0 -- place the eye on a sphere around the target, then roll `up`
 * about the view axis by angle.z (Rodrigues). */
static void MgCameraAngleApply(MGF_CAMERAVIEW *view)
{
    float rotX = view->angle.x;
    float rotY = view->angle.y;
    float rotZ = view->angle.z;
    HuVecF axis;
    float upX;
    float upY;
    float upZ;

    view->pos.x = view->target.x+(view->dist*(sin((M_PI*rotY)/180.0)*cos((M_PI*rotX)/180.0)));
    view->pos.y = view->target.y+(view->dist*-sin((M_PI*rotX)/180.0));
    view->pos.z = view->target.z+(view->dist*(cos((M_PI*rotY)/180.0)*cos((M_PI*rotX)/180.0)));
    PSVECSubtract(&view->pos, &view->target, &axis);
    PSVECNormalize(&axis, &axis);
    upX = sin((M_PI*rotX)/180.0)*sin((M_PI*rotY)/180.0);
    upY = cos((M_PI*rotX)/180.0);
    upZ = sin((M_PI*rotX)/180.0)*cos((M_PI*rotY)/180.0);
    view->up.x = (upX*((axis.x*axis.x)+((1.0f-(axis.x*axis.x))*cos((M_PI*rotZ)/180.0))))
               +((upY*(((axis.x*axis.y)*(1.0-cos((M_PI*rotZ)/180.0)))-(axis.z*sin((M_PI*rotZ)/180.0))))
               + (upZ*(((axis.x*axis.z)*(1.0-cos((M_PI*rotZ)/180.0)))+(axis.y*sin((M_PI*rotZ)/180.0)))));
    view->up.y = (upY*((axis.y*axis.y)+((1.0f-(axis.y*axis.y))*cos((M_PI*rotZ)/180.0))))
               +((upX*(((axis.x*axis.y)*(1.0-cos((M_PI*rotZ)/180.0)))+(axis.z*sin((M_PI*rotZ)/180.0))))
               + (upZ*(((axis.y*axis.z)*(1.0-cos((M_PI*rotZ)/180.0)))-(axis.x*sin((M_PI*rotZ)/180.0)))));
    view->up.z = (upZ*((axis.z*axis.z)+((1.0f-(axis.z*axis.z))*cos((M_PI*rotZ)/180.0))))
               +((upY*(((axis.y*axis.z)*(1.0-cos((M_PI*rotZ)/180.0)))+(axis.x*sin((M_PI*rotZ)/180.0))))
               + (upX*(((axis.x*axis.z)*(1.0-cos((M_PI*rotZ)/180.0)))-(axis.y*sin((M_PI*rotZ)/180.0)))));
    PSVECNormalize(&view->up, &view->up);
}
/* m524 fn_1_4494 -- the inverse: recover angle and distance from an eye the
 * debug camera has moved by hand. The third row of the rotate below reads
 * column 3, not column 2, and its result is discarded -- that is what the
 * object does. */
static void MgCameraAngleGet(MGF_CAMERAVIEW *view)
{
    float dx = view->pos.x-view->target.x;
    float dy = view->pos.y-view->target.y;
    float dz = view->pos.z-view->target.z;
    float mtx[4][4];
    float angY;
    float rotX;
    float rotY;
    float rotZ;
    int i;
    int j;

    view->dist = sqrtf((dz*dz)+((dx*dx)+(dy*dy)));
    angY = (atan2(dz, dx)/M_PI)*180.0;
    view->angle.y = -(angY-90.0f);
    for(i=0; i<4; i++) {
        for(j=0; j<4; j++) {
            mtx[i][j] = 0.0f;
        }
    }
    mtx[2][2] = mtx[0][0] = cos((M_PI*-angY)/180.0);
    mtx[2][0] = -sin((M_PI*-angY)/180.0);
    mtx[0][2] = sin((M_PI*-angY)/180.0);
    mtx[3][3] = mtx[1][1] = 1.0f;
    rotX = (dz*mtx[2][0])+((dx*mtx[0][0])+(dy*mtx[1][0]));
    rotY = (dz*mtx[2][1])+((dx*mtx[0][1])+(dy*mtx[1][1]));
    rotZ = (dz*mtx[2][3])+((dx*mtx[0][3])+(dy*mtx[1][3]));
    view->angle.x = -((atan2(rotY, rotX)/M_PI)*180.0);
    view->angle.z = 0.0f;
}
/* m524 fn_1_4898 -- interpolate one camera view into another over `timeMax`
 * frames. */
static void MgCameraMoveMain(OMOBJ *obj)
{
    MGF_CAMERAMOVE *work = obj->data;
    MGF_CAMERAVIEW *view;
    MGF_CAMERAVIEW *start;
    MGF_CAMERAVIEW *end;
    float t;

    if(!(work->stat & MGF_CAMERAMOVE_ACTIVE)) {
        return;
    }
    view = work->view;
    start = &work->start;
    end = &work->end;
    work->time += 1.0f;
    t = work->time/work->timeMax;
    if(view->mode == 0) {
        view->pos.x = start->pos.x+(t*(end->pos.x-start->pos.x));
        view->pos.y = start->pos.y+(t*(end->pos.y-start->pos.y));
        view->pos.z = start->pos.z+(t*(end->pos.z-start->pos.z));
    } else {
        view->dist = start->dist+(t*(end->dist-start->dist));
        view->angle.x = start->angle.x+(t*(end->angle.x-start->angle.x));
        view->angle.y = start->angle.y+(t*(end->angle.y-start->angle.y));
    }
    view->target.x = start->target.x+(t*(end->target.x-start->target.x));
    view->target.y = start->target.y+(t*(end->target.y-start->target.y));
    view->target.z = start->target.z+(t*(end->target.z-start->target.z));
    if(work->time >= work->timeMax) {
        *view = work->end;
        work->stat &= ~MGF_CAMERAMOVE_ACTIVE;
    }
    MgCameraViewSet(view);
}
/* MgCameraMoveEntry */
OMOBJ *MgCameraMoveEntry(MGF_CAMERAVIEW *view, MGF_CAMERAVIEW *target, float time)
{
    OMOBJ *obj;
    MGF_CAMERAMOVE *work;

    if(view->no != target->no) {
        OSReport(CameraNumDiffMesStr);
        return NULL;
    }
    obj = omAddObjEx(objman, 0x2000, 0, 0, OM_GRP_NONE, MgCameraMoveMain);
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MGF_CAMERAMOVE), HU_MEMNUM_OVL);
    work = obj->data;
    work->timeMax = time;
    work->time = 0.0f;
    work->view = view;
    work->start = *view;
    work->end = *target;
    work->stat = 3;
    if(view->mode == 1) {
        MgCameraAngleApply(&work->start);
        MgCameraAngleApply(&work->end);
    }
    return obj;
}
#ifndef MGF_HAVE_MgCameraMoveCheck
#define MGF_HAVE_MgCameraMoveCheck
/* m524 fn_1_4BB0 */
static BOOL MgCameraMoveCheck(OMOBJ *obj)
{
    MGF_CAMERAMOVE *work = obj->data;
    if(work->stat & MGF_CAMERAMOVE_ACTIVE) {
        return TRUE;
    }
    return FALSE;
}
#endif
/* m524 fn_1_4BE4 */
static void MgCameraMoveKill(OMOBJ *obj)
{
    omDelObjEx(objman, obj);
}
/* m524 fn_1_4C18 -- jitter the look-at point for `time` frames, then put the
 * real view back and delete itself. */
static void MgCameraShakeMain(OMOBJ *obj)
{
    MGF_CAMERAVIEW *work = obj->data;
    int amp = obj->work[1];
    MGF_CAMERAVIEW *view;

    if(obj->work[0] == 0) {
        MgCameraViewSet(((MGF_CAMERAVIEW *)(obj)->work[2]));
        omDelObjEx(objman, obj);
        return;
    }
    view = ((MGF_CAMERAVIEW *)(obj)->work[2]);
    work->target.x = (view->target.x+frandmod(amp*2))-amp;
    view = ((MGF_CAMERAVIEW *)(obj)->work[2]);
    work->target.y = (view->target.y+frandmod(amp*2))-amp;
    MgCameraViewSet(work);
    obj->work[0]--;
}
/* m524 fn_1_4D60 -- the out-of-line shake constructor; overlays that shake the
 * camera themselves build the same object inline. */
static void MgCameraShakeEntry(MGF_CAMERAVIEW *view, int time, int amp)
{
    OMOBJ *obj = omAddObjEx(objman, 0x2000, 0, 0, OM_GRP_NONE, MgCameraShakeMain);
    MGF_CAMERAVIEW *work;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(MGF_CAMERAVIEW), HU_MEMNUM_OVL);
    work = obj->data;
    obj->work[0] = time;
    obj->work[1] = amp;
    *work = *view;
    (obj)->work[2] = (u32)(view);
}
#endif


/* ===== 8. the flow object itself ===== */
#if defined(MGF_S_FLOWMAIN) && !defined(MGF_HAVE_MgFlowMain)
#define MGF_HAVE_MgFlowMain
/* m524 fn_1_50B0 -- the flow object: run the current step, or start the exit. */
static void MgFlowMain(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    if(omSysExitReq) {
        if(MgMusicId != -1) {
            HuAudFadeOut(1000);
            MgMusicId = -1;
        }
        obj->objFunc = MgFlowExitWait;
        WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
        return;
    }
    work->flowTbl[work->step](obj);
}
/* m524 fn_1_5160 */
static void MgFlowExitWait(OMOBJ *obj)
{
    if(!WipeCheckEnd()) {
        omOvlReturnEx(1, 1);
    }
}
#endif


/* ===== 9. the shared flow steps ===== */
#if defined(MGF_S_FLOWSTEP) && !defined(MGF_HAVE_MgFlowWipeWait)
#define MGF_HAVE_MgFlowWipeWait
/* m524 fn_1_5454 -- hold until the wipe-in finishes. */
static void MgFlowWipeWait(OMOBJ *obj)
{
    if(!WipeCheckEnd()) {
        MgFlowNext(obj);
    }
}
/* m524 fn_1_54CC -- the last step; hand the board back its turn. */
static void MgFlowReturn(OMOBJ *obj)
{
    if(MgMusicId != -1) {
        HuAudFadeOut(1000);
        MgMusicId = -1;
    }
    if(!WipeCheckEnd()) {
        omOvlReturnEx(1, 1);
    }
}
/* m524 fn_1_5530 -- put a GAMEMES banner up and wait for it to clear. */
static void MgFlowGameMes(OMOBJ *obj, s16 mesNo, s16 type)
{
    MGF_FLOW *work = obj->data;
    if(work->gameMesId == -1) {
        work->gameMesId = GameMesCreate(mesNo, type);
        return;
    }
    if(GameMesStatGet(work->gameMesId)) {
        return;
    }
    work->gameMesId = -1;
    MgFlowNext(obj);
}
/* m524 fn_1_55EC -- "START!". */
static void MgFlowMgStart(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    if(work->gameMesId == -1) {
        work->gameMesId = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_START);
        return;
    }
    if(GameMesStatGet(work->gameMesId)) {
        return;
    }
    work->gameMesId = -1;
    MgFlowNext(obj);
}
/* m524 fn_1_56A0 -- "FINISH!". */
static void MgFlowMgFinish(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    if(work->gameMesId == -1) {
        work->gameMesId = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_FINISH);
        return;
    }
    if(GameMesStatGet(work->gameMesId)) {
        return;
    }
    work->gameMesId = -1;
    MgFlowNext(obj);
}
/* m524 fn_1_5754 -- build the clock from the parameters ObjectSetup left. */
static void MgFlowTimerCreate(OMOBJ *obj)
{
    MGF_FLOW *work = obj->data;
    work->timer = MgTimerCreate(work->timerType);
    MgTimerParamSet(work->timer, work->timerMaxTime, work->timerEndTime, work->timerRecordTime);
    MgTimerModeOnSet(work->timer, MGTIMER_OFFTYPE_FADEOUT);
    MgFlowNext(obj);
}
#endif


/* ===== 10. vector and angle helpers ===== */
#if defined(MGF_S_MATH) && !defined(MGF_HAVE_MgVecApproach)
#define MGF_HAVE_MgVecApproach
/* m524 fn_1_58C0 -- step `pos` toward `target` at `speed`, facing it as it goes. */
MGF_LINK_VECAPPROACH BOOL MgVecApproach(HuVecF *pos, HuVecF *target, HuVecF *rot, float speed)
{
    HuVecF dir;
    float mag;

    PSVECSubtract(target, pos, &dir);
    mag = PSVECMag(&dir);
    if(0.0f == mag) {
        return TRUE;
    }
    PSVECNormalize(&dir, &dir);
    PSVECScale(&dir, &dir, speed);
    if(PSVECMag(&dir) >= mag) {
        *pos = *target;
        return TRUE;
    }
    PSVECAdd(pos, &dir, pos);
    rot->y = (atan2(dir.x, dir.z)/M_PI)*180.0;
    return FALSE;
}
/* m524 fn_1_59E4 -- turn `from` toward `to` by at most `speed`, wrapping at 360. */
MGF_LINK_ANGLEAPPROACH float MgAngleApproach(float from, float to, float speed)
{
    float mod;
    float diff;
    float wrap;
    float result;

    mod = fmod(to-from, 360.0);
    diff = mod;
    if(diff < 0.0f) {
        diff += 360.0f;
    }
    if(diff > 180.0f) {
        diff -= 360.0f;
    }
    if(fabs(diff) > speed) {
        if(diff < 0.0f) {
            diff = -speed;
        } else {
            diff = speed;
        }
    }
    wrap = fmod(from+diff, 360.0);
    result = wrap;
    if(result < 0.0f) {
        result += 360.0f;
    }
    return result;
}
/* m524 fn_1_5B54 -- walk `pos` around `center` toward `target`, 30 degrees a step. */
MGF_LINK_VECORBIT BOOL MgVecOrbit(HuVecF *center, HuVecF *pos, HuVecF *target, float speed)
{
    HuVecF radius;
    HuVecF dir;
    HuVecF start;
    float mag;
    float angle;

    start = *pos;
    while(TRUE) {
        PSVECSubtract(pos, center, &radius);
        if(0.0f == PSVECMag(&radius)) {
            return FALSE;
        }
        PSVECSubtract(pos, target, &dir);
        mag = PSVECMag(&dir);
        if(mag >= speed) {
            return FALSE;
        }
        if(0.0f != mag) {
            PSVECNormalize(&dir, &dir);
            PSVECScale(&dir, &dir, speed);
            PSVECAdd(target, &dir, pos);
        } else {
            *pos = *center;
        }
        PSVECSubtract(pos, center, &dir);
        if(PSVECMag(&dir) >= 0.001f) {
            return TRUE;
        }
        mag = PSVECMag(&radius);
        angle = ((atan2(dir.z, dir.x)/M_PI)*180.0)+30.0f;
        radius.x = mag*sin((M_PI*angle)/180.0);
        radius.z = mag*cos((M_PI*angle)/180.0);
        PSVECAdd(center, &radius, pos);
    }
}
/* m524 fn_1_5D8C */
MGF_LINK_PLANENORMALGET void MgPlaneNormalGet(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *normal)
{
    HuVecF cb;
    HuVecF ba;
    PSVECSubtract(c, b, &cb);
    PSVECSubtract(b, a, &ba);
    PSVECCrossProduct(&cb, &ba, normal);
    PSVECNormalize(normal, normal);
}
/* m524 fn_1_5E04 */
MGF_LINK_PLANEDISTGET float MgPlaneDistGet(HuVecF *normal, HuVecF *plane, HuVecF *pos)
{
    HuVecF ofs;
    PSVECSubtract(pos, plane, &ofs);
    return PSVECDotProduct(normal, &ofs);
}
/* m524 fn_1_5E48 */
MGF_LINK_PLANECROSSGET BOOL MgPlaneCrossGet(HuVecF *normal, HuVecF *plane, HuVecF *from, HuVecF *to, HuVecF *cross)
{
    HuVecF dir;
    float num;
    float den;

    PSVECSubtract(to, from, &dir);
    num = MgPlaneDistGet(normal, plane, from);
    den = MgPlaneDistGet(normal, to, from);
    if(0.0f == den) {
        return FALSE;
    }
    PSVECScale(&dir, &dir, num/den);
    PSVECAdd(from, &dir, cross);
    return TRUE;
}
#endif


/* Section selectors are per-include; clear them on the way out. */
#undef MGF_S_DECL
#undef MGF_S_DATA
#undef MGF_S_BSS
#undef MGF_S_PLAYERCONF
#undef MGF_S_PAD
#undef MGF_S_FLOWCTL
#undef MGF_S_OBJMAN
#undef MGF_S_FLOWENTRY
#undef MGF_S_CAMERAMOVECHECK
#undef MGF_S_CAMERA
#undef MGF_S_FLOWMAIN
#undef MGF_S_FLOWSTEP
#undef MGF_S_MATH
