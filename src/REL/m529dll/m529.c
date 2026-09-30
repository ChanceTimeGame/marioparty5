/*
 * m529dll -- HAND DE PYON (MG_TYPE_2VS2).
 *
 * Functional PC recovery, now included in PB_REL_FILES and verified through
 * gameplay, result, and overlay return.  Reference matching is still in
 * progress. Keep functions in the reference object's order; CodeWarrior's
 * inlining is sensitive to definition order.
 */

#include "game/charman.h"
#include "game/audio.h"
#include "game/esprite.h"
#include "game/gamework.h"
#include "game/gamemes.h"
#include "game/frand.h"
#include "game/hu3d.h"
#include "game/hsfex.h"
#include "game/memory.h"
#include "game/mg/score.h"
#include "game/mg/timer.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/wipe.h"
#include "datanum/mgconst.h"
#include <math.h>

/* The eight character motions at .data:0x8. The m529 data archive has no
 * published file-name table, so retain the original DATANUM values. */
static const u32 M529PlayerMotionData[8] = {
    0x008C0000, 0x008C0001, 0x008C0002, 0x00870043,
    0x008C0006, 0x008C0007, 0x008C0038, 0x008C003A
};

/* .data:0x28. The player group determines the starting lane. */
static const HuVecF M529PlayerStartPos[4] = {
    { -470.0f, 0.0f, 300.0f },
    { -145.0f, 0.0f, 300.0f },
    {  145.0f, 0.0f, 300.0f },
    {  470.0f, 0.0f, 300.0f }
};

/* .data:0x58. fn_1_B98 state 2004 continuously approaches these result
 * staging positions while its controller is between milestones 1007 and
 * 1008/1009. */
static const HuVecF M529PlayerResultPos[4] = {
    { -470.0f, 0.0f, 500.0f },
    { -115.0f, 0.0f, 500.0f },
    {  145.0f, 0.0f, 500.0f },
    {  470.0f, 0.0f, 500.0f }
};

/* .data:0x244, the target-scene asset list consumed by fn_1_1C8C. */
static const u32 M529TargetData[14] = {
    0x00570000, 0x00570001, 0x00570003, 0x00570002,
    0x00570004, 0x00570005, 0x0057000A, 0x00570006,
    0x00570007, 0x00570008, 0x00570009, 0x0057000E,
    0x0057000E, 0x0057000C
};

/* .data:0x88/.data:0xB8, the four player-side target models. */
static const HuVecF M529PlayerTargetPos[4] = {
    { -470.0f, 250.0f, 300.0f }, { -145.0f, 0.0f, 300.0f },
    { 145.0f, 250.0f, 300.0f }, { 470.0f, 0.0f, 300.0f }
};
static const HuVecF M529PlayerTargetRot[4] = {
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 270.0f, 0.0f },
    { 0.0f, 0.0f, 270.0f }, { 0.0f, 0.0f, 0.0f }
};

/* .data:0xE8, shared by the two front and two rear target pairs. */
static const HuVecF M529TargetPairPos[2] = {
    { -470.0f, 0.0f, 300.0f }, { 145.0f, 0.0f, 300.0f }
};

/* fn_1_2714's two four-model target sets. The first pair of tables is the
 * hidden starting arrangement; fn_1_3CE0 eases it toward the second pair. */
static const HuVecF M529TargetStartPos[2][4] = {
    {
        { -600.0f, 600.0f, 600.0f }, { 0.0f, 600.0f, 600.0f },
        { 0.0f, 0.0f, 600.0f }, { -600.0f, 0.0f, 600.0f }
    },
    {
        { 0.0f, 600.0f, 600.0f }, { 600.0f, 600.0f, 600.0f },
        { 600.0f, 0.0f, 600.0f }, { 0.0f, 0.0f, 600.0f }
    }
};
static const HuVecF M529TargetGoalPos[2][4] = {
    {
        { -350.0f, 200.0f, 600.0f }, { 0.0f, 200.0f, 600.0f },
        { 0.0f, 50.0f, 600.0f }, { -350.0f, 50.0f, 600.0f }
    },
    {
        { 0.0f, 200.0f, 600.0f }, { 350.0f, 200.0f, 600.0f },
        { 350.0f, 50.0f, 600.0f }, { 0.0f, 50.0f, 600.0f }
    }
};
static const HuVecF M529TargetSetRot[4] = {
    { 0.0f, -135.0f, 0.0f }, { 0.0f, 135.0f, 0.0f },
    { 0.0f, 45.0f, 0.0f }, { 0.0f, -45.0f, 0.0f }
};

static char M529DebugCenterText[] = "Center X:%.02f Y:%.02f Z:%.02f";
static char M529DebugRotationText[] = "CRot X:%.02f Y:%.02f Z:%.02f";
static char M529DebugZoomText[] = "CZoom:%.02f";
static char M529DebugCamBeginText[] = "static OBJ_CAMINFO CamK = {\n";
static char M529DebugCamCenterText[] = "\t{ %.01ff, %.01ff, %.01ff },\t/* center */\n";
static char M529DebugCamRotationText[] = "\t{ %.01ff, %.01ff, %.01ff },\t/* rot */\n";
static char M529DebugCamZoomText[] = "\t%.01ff,\t/* zoom */\n";
static char M529DebugCamEndText[] = "};\n\n";
static const HuVecF M529DebugCameraReportFrom[4] = {
    { 0.0f, 10.0f, -100.0f }, { 0.0f, 500.0f, 1720.0f },
    { 1618.0f, 1121.0f, 2276.0f }, { 0.0f, 919.0f, 2529.0f }
};
static const HuVecF M529DebugCameraReportTo[4] = {
    { -210.0f, 120.0f, -500.0f }, { 0.0f, 200.0f, -500.0f },
    { -100.0f, 200.0f, 300.0f }, { -100.0f, 200.0f, 300.0f }
};

/*
 * Allocated as 0xD0 bytes by ObjectSetup. All named fields below have direct
 * reads or writes in fn_1_5E0. The unknown ranges are deliberately retained:
 * inventing fields before their consumers are read is how a 64-bit port gets
 * silently mislaid out.
 */
typedef struct M529Player_s {
    /* 0x00 */ s32 side;
    /* 0x04 */ s32 motionNo;
    /* 0x08 */ s32 state;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 playerNo;
    /* 0x18 */ s32 group;
    /* 0x1C */ s32 partnerNo;
    /* 0x20 */ s32 partnerGroup;
    /* 0x24 */ s32 groupCopy;
    /* 0x28 */ s32 charNo;
    /* 0x2C */ s32 padNo;
    /* 0x30 */ u32 btn;
    /* 0x34 */ u32 btnDown;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ float unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ HuVecF pos;
    /* 0x90 */ HuVecF unk90;
    /* 0x9C */ float unk9C;
    /* 0xA0 */ u8 unkA0[4];
    /* 0xA4 */ float rotY;
    /* 0xA8 */ float unkA8;
    /* 0xAC */ HuVecF unkAC;
    /* 0xB8 */ s32 difficulty;
    /* 0xBC */ s32 comParamBC;
    /* 0xC0 */ s32 comParamC0;
    /* 0xC4 */ s32 comParamC4;
    /* 0xC8 */ s32 comParamC8;
    /* 0xCC */ s32 comParamCC;
} M529_PLAYER;

typedef char M529PlayerSizeCheck[(sizeof(M529_PLAYER) == 0xD0) ? 1 : -1];

/* lbl_1_bss_EC.  Slots are indexed by M529TargetData rather than by a
 * compact creation order: data entries 9 and 10 belong to fn_1_2714's
 * separate four-model target sets and are deliberately unused here. */
typedef struct M529TargetScene_s {
    /* 0x00 */ s16 modelId[14];
} M529_TARGET_SCENE;

typedef char M529TargetSceneSizeCheck[(sizeof(M529_TARGET_SCENE) == 0x1C) ? 1 : -1];

/* lbl_1_bss_118. ObjectSetup creates the priority-102 controller and stores
 * it here before any player callback can leave state 2000. */
static OMOBJ *M529ControllerObj;
static OMOBJ *M529PlayerObj[GW_PLAYER_MAX];
static OMOBJ *M529TargetObj;
static OMOBJMAN *M529ObjMan;
static M529_TARGET_SCENE M529TargetScene;
static s16 M529StageJointMotion;
/* lbl_1_bss_2C/D4/E0/E4: the small end-result stage-motion controller.
 * The retail function starts from the final joint-motion frame and rocks
 * through its final 40 frames while a human winning team is displayed. */
static s32 M529StageMotionLength;
static s32 M529StageMotionStarted;
static s32 M529StageMotionFrame;
static s32 M529StageMotionDirection;
/* lbl_1_bss_44..CC: fn_1_2714/fn_1_3CE0/fn_1_4048 target-set state. */
static s16 M529TargetModel[2][4];
static HuVecF M529TargetPos[2][4];
static float M529TargetPhase[2][4];
static float M529ControllerStateTimer;
/* lbl_1_bss_E8: reset before the opening wipe and advanced for each live
 * timer frame. Rear-lane inputs measure their interval against this clock. */
static s32 M529RoundFrame;
static MGTIMER *M529Timer;
static GAMEMESID M529Message = -1;
static s32 M529Bgm = -1;
/* lbl_1_data_0: the opening-stage loop is faded with the result effects. */
static s32 M529StartSfx = -1;
/* lbl_1_bss_8: the final-stage joint-motion loop (effect 0x796). */
static s32 M529StageMotionSfx = -1;
/* lbl_1_bss_10 / lbl_1_bss_C: side-specific target-sequence loop effects. */
static s32 M529TargetSequenceSfx[2] = { -1, -1 };
static s32 M529TeamScore[2];
/* lbl_1_bss_18/DC: the minigame-6 record and its result-panel pulse flag. */
static s32 M529RecordScore;
static s32 M529RecordPulse;
static s32 M529ResultRecordChecked;
static s32 M529RecordMessageActive;
/* lbl_1_bss_1C: 0 and 1 select a team; 2 is the draw branch. */
static s32 M529Winner = 2;
/* lbl_1_bss_4 / lbl_1_bss_0: one result effect per winning side. */
static s32 M529ResultSfx[2] = { -1, -1 };
static OMCAMERAVIEW M529CameraView = {
    { -150.0f, 120.0f, -500.0f },
    { 0.0f, 11.4f, 0.0f },
    465.0f
};
static const OMCAMERAVIEW M529CameraMove[3] = {
    { { 0.0f, 200.0f, -500.0f }, { -7.7f, -0.0f, 0.0f }, 2240.2f },
    { { -100.0f, 200.0f, 300.0f }, { -19.4f, 41.0f, 0.0f }, 2775.7f },
    { { 0.0f, 50.0f, -100.0f }, { -18.3f, -0.0f, 0.0f }, 2775.0f }
};

/* fn_1_5204 allocates exactly 0x1C bytes. The side and centre win groups are
 * globals in the original; keeping their IDs separately preserves that
 * compact work layout and makes the display gate in fn_1_5680 explicit. */
typedef struct M529ScoreWork_s {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ MGSCORE *recordScore;
    /* 0x08 */ MGSCORE *teamScore[2];
    /* 0x10 */ s16 recordLabel;
    /* 0x12 */ s16 pad12;
    /* 0x14 */ s32 pulseRising;
    /* 0x18 */ float pulseScale;
} M529_SCORE_WORK;

static HUSPRGRPID M529TeamWin[2];
static HUSPRGRPID M529WinnerIcon;

/* These callbacks follow ObjectSetup in the reference object. Their bodies
 * are recovered with the target graph and main controller, respectively. */
static void M529MainController(OMOBJ *obj);
static void M529ExitAfterWipe(OMOBJ *obj);
static void M529PlayerTargetSequenceUpdate(OMOBJ *obj);
static void M529StageJointMotionUpdate(void);

/* fn_1_63E4. The retail exit fades every looping effect it owns before the
 * overlay return, rather than abruptly relying on HuAudAllStop below. */
static void M529EffectsFadeOut(void)
{
    s32 i;

    if (M529StartSfx != -1 && HuAudFXStatusGet(M529StartSfx)) {
        HuAudFXFadeOut(M529StartSfx, 1000);
    }
    for (i = 0; i < 2; i++) {
        if (M529TargetSequenceSfx[i] != -1) {
            HuAudFXFadeOut(M529TargetSequenceSfx[i], 1000);
        }
        if (M529ResultSfx[i] != -1) {
            HuAudFXFadeOut(M529ResultSfx[i], 1000);
        }
    }
    if (M529StageMotionSfx != -1) {
        HuAudFXFadeOut(M529StageMotionSfx, 1000);
    }
}

/* fn_1_57BC. This is reached from the controller's common tail while the
 * winning result is shown.  The original deliberately leaves its D4 flag at
 * zero after Hu3DMotionSet, so retain that behavior: setting the same joint
 * motion each tick is part of the retail sequence. */
static void M529StageJointMotionUpdate(void)
{
    if (M529StageMotionSfx == -1) {
        M529StageMotionSfx = HuAudFXPlay(0x796);
    }
    if (!M529StageMotionStarted) {
        Hu3DMotionSet(M529TargetScene.modelId[0], M529StageJointMotion);
    }
    Hu3DMotionTimeSet(M529TargetScene.modelId[0], (float)M529StageMotionFrame);
    Hu3DMotionSpeedSet(M529TargetScene.modelId[0], 1.5f);

    if (M529StageMotionDirection) {
        M529StageMotionFrame++;
        if (M529StageMotionFrame > M529StageMotionLength) {
            M529StageMotionDirection = FALSE;
        }
    } else {
        M529StageMotionFrame--;
        if (M529StageMotionFrame < M529StageMotionLength - 40) {
            M529StageMotionDirection = TRUE;
        }
    }
}

/* The following helpers are the unreferenced debug/camera support tail from
 * the retail object (fn_1_70B0 through fn_1_73D8).  They are intentionally
 * globally visible so CodeWarrior retains this dormant utility code. */
float M529DebugAngleApproach(float current, float target, float fraction)
{
    float delta = fmodf(target - current, 360.0f);

    if (delta < 0.0f) {
        delta += 360.0f;
    }
    if (delta > 180.0f) {
        delta -= 360.0f;
    }
    delta = fmodf(current + delta * fraction, 360.0f);
    if (delta < 0.0f) {
        delta += 360.0f;
    }
    return delta;
}

static s32 M529DebugSequence = -1;

typedef struct M529DebugNode_s {
    u16 key;
    s16 value;
    struct M529DebugNode_s *prev;
    struct M529DebugNode_s *next;
} M529_DEBUG_NODE;

typedef struct M529DebugNodeList_s {
    void *unused;
    M529_DEBUG_NODE *prev;
    M529_DEBUG_NODE *next;
} M529_DEBUG_NODE_LIST;

typedef struct M529DebugModelCacheEntry_s {
    s32 dataNum;
    s16 modelId;
    s16 pad;
} M529_DEBUG_MODEL_CACHE_ENTRY;

static M529_DEBUG_NODE_LIST M529DebugNodeList;
static M529_DEBUG_MODEL_CACHE_ENTRY M529DebugModelCache[32];
static HuVecF M529DebugCameraCenter;
static HuVecF M529DebugCameraRotation;
static HuVecF M529DebugCameraCenterTarget;
static HuVecF M529DebugCameraRotationTarget;
static HuVecF M529DebugCameraCenterMulti[4];
static HuVecF M529DebugCameraCenterMultiTarget[4];
static HuVecF M529DebugCameraRotationMulti[4];
static HuVecF M529DebugCameraRotationMultiTarget[4];
static s32 M529DebugCameraTransitionDone;

void M529DebugNodeListInit(void)
{
    M529DebugNodeList.prev = NULL;
    M529DebugNodeList.next = NULL;
}

void M529DebugNodeAdd(u16 key, s16 value)
{
    M529_DEBUG_NODE *node = HuMemDirectMallocNum(HEAP_HEAP, sizeof(*node), HU_MEMNUM_OVL);
    M529_DEBUG_NODE *oldFirst = M529DebugNodeList.next;

    node->key = key;
    node->value = value;
    M529DebugNodeList.next = node;
    if (oldFirst != NULL) {
        oldFirst->prev = node;
    }
    node->prev = (M529_DEBUG_NODE *)&M529DebugNodeList;
    node->next = oldFirst;
}

s16 M529DebugNodeRemove(u16 key)
{
    M529_DEBUG_NODE *node;

    for (node = M529DebugNodeList.next; node != NULL; node = node->next) {
        if (node->key == key) {
            s16 value = node->value;

            node->prev->next = node->next;
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            HuMemDirectFree(node);
            return value;
        }
    }
    return -1;
}

void M529DebugModelCacheInit(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        M529DebugModelCache[i].dataNum = 0;
        M529DebugModelCache[i].modelId = -1;
    }
}

s16 M529DebugModelCacheGet(s32 dataNum)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (M529DebugModelCache[i].dataNum == dataNum) {
            return Hu3DModelLink(M529DebugModelCache[i].modelId);
        }
    }
    for (i = 0; i < 32; i++) {
        if (M529DebugModelCache[i].dataNum == 0) {
            M529DebugModelCache[i].dataNum = dataNum;
            M529DebugModelCache[i].modelId = Hu3DModelCreateData(dataNum);
            return M529DebugModelCache[i].modelId;
        }
    }
    return Hu3DModelCreateData(dataNum);
}

void M529DebugVecEase90(float progress, const HuVecF *start, const HuVecF *end, HuVecF *result)
{
    float rate;

    if (progress > 1.0f) {
        progress = 1.0f;
    }
    rate = sinf(90.0f * progress * (float)M_PI / 180.0f);
    rate *= rate;
    result->x = start->x + rate * (end->x - start->x);
    result->y = start->y + rate * (end->y - start->y);
    result->z = start->z + rate * (end->z - start->z);
}

void M529DebugCameraSet(const HuVecF *center, const HuVecF *rotation, const HuVecF *up)
{
    Hu3DCameraPosSetV(1, (HuVecF *)center, (HuVecF *)rotation, (HuVecF *)up);
    M529DebugCameraCenter = *center;
    M529DebugCameraRotation = *up;
}

BOOL M529DebugCameraEase(const HuVecF *up, float progress)
{
    HuVecF center;
    HuVecF target;
    float rate;

    if (progress > 1.0f) {
        progress = 1.0f;
    }
    rate = sinf(90.0f * progress * (float)M_PI / 180.0f);
    rate *= rate;
    center.x = M529DebugCameraCenter.x
        + rate * (M529DebugCameraCenterTarget.x - M529DebugCameraCenter.x);
    center.y = M529DebugCameraCenter.y
        + rate * (M529DebugCameraCenterTarget.y - M529DebugCameraCenter.y);
    center.z = M529DebugCameraCenter.z
        + rate * (M529DebugCameraCenterTarget.z - M529DebugCameraCenter.z);
    target.x = M529DebugCameraRotation.x
        + rate * (M529DebugCameraRotationTarget.x - M529DebugCameraRotation.x);
    target.y = M529DebugCameraRotation.y
        + rate * (M529DebugCameraRotationTarget.y - M529DebugCameraRotation.y);
    target.z = M529DebugCameraRotation.z
        + rate * (M529DebugCameraRotationTarget.z - M529DebugCameraRotation.z);
    Hu3DCameraPosSetV(1, &center, (HuVecF *)up, &target);
    if (progress >= 1.0f) {
        return TRUE;
    }
    M529DebugCameraTransitionDone = TRUE;
    return FALSE;
}

BOOL M529DebugCameraEaseAll(const HuVecF *up, float progress)
{
    s32 i;
    float rate;

    if (progress > 1.0f) {
        progress = 1.0f;
    }
    rate = sinf(90.0f * progress * (float)M_PI / 180.0f);
    rate *= rate;
    for (i = 0; i < 4; i++) {
        HuVecF center;
        HuVecF target;

        center.x = M529DebugCameraCenterMulti[i].x
            + rate * (M529DebugCameraCenterMultiTarget[i].x - M529DebugCameraCenterMulti[i].x);
        center.y = M529DebugCameraCenterMulti[i].y
            + rate * (M529DebugCameraCenterMultiTarget[i].y - M529DebugCameraCenterMulti[i].y);
        center.z = M529DebugCameraCenterMulti[i].z
            + rate * (M529DebugCameraCenterMultiTarget[i].z - M529DebugCameraCenterMulti[i].z);
        target.x = M529DebugCameraRotationMulti[i].x
            + rate * (M529DebugCameraRotationMultiTarget[i].x - M529DebugCameraRotationMulti[i].x);
        target.y = M529DebugCameraRotationMulti[i].y
            + rate * (M529DebugCameraRotationMultiTarget[i].y - M529DebugCameraRotationMulti[i].y);
        target.z = M529DebugCameraRotationMulti[i].z
            + rate * (M529DebugCameraRotationMultiTarget[i].z - M529DebugCameraRotationMulti[i].z);
        Hu3DCameraPosSetV(1 << i, &center, (HuVecF *)up, &target);
    }
    if (progress >= 1.0f) {
        return TRUE;
    }
    M529DebugCameraTransitionDone = TRUE;
    return FALSE;
}

/* fn_1_5F74. This is the otherwise-unreferenced free-camera console from
 * the retail overlay.  It is kept functional for source completeness, but
 * no retail gameplay callback enters it. */
void M529DebugFreeCameraMain(void)
{
    GXColor color = { 0, 0, 144, 192 };

    CZoom += HuPadTrigL[0] / 5;
    CZoom -= HuPadTrigR[0] / 5;
    Center.x += 10.0f * (HuPadSubStkX[0] / 59.0f);
    Center.z -= 10.0f * (HuPadSubStkY[0] / 59.0f);
    CRot.x += 5.0f * (HuPadSubStkY[1] / 59.0f);
    CRot.y -= 5.0f * (HuPadSubStkX[1] / 59.0f);
    printWin(16, 40, 384, 36, &color);
    fontcolor = FONT_COLOR_YELLOW;
    print8(16, 40, 1.5f, M529DebugCenterText, Center.x, Center.y, Center.z);
    print8(16, 52, 1.5f, M529DebugRotationText, CRot.x, CRot.y, CRot.z);
    print8(16, 64, 1.5f, M529DebugZoomText, CZoom);
    if (HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&M529CameraView);
    }
}

/* fn_1_5A84. Derive the object-system camera view that looks from one debug
 * point to another, then emit the initializer format embedded in retail. */
void M529DebugCameraReport(const HuVecF *from, const HuVecF *to)
{
    float dx = from->x - to->x;
    float dy = from->y - to->y;
    float dz = from->z - to->z;
    float horizontal = sqrtf(dx * dx + dz * dz);
    float zoom = sqrtf(horizontal * horizontal + dy * dy);
    float yaw = atan2f(dz, dx) * 180.0f / (float)M_PI;
    float rotationY = 90.0f - yaw;
    float rotationX = -atan2f(dy, horizontal) * 180.0f / (float)M_PI;

    OSReport(M529DebugCamBeginText);
    OSReport(M529DebugCamCenterText, to->x, to->y, to->z);
    OSReport(M529DebugCamRotationText, rotationX, rotationY, 0.0f);
    OSReport(M529DebugCamZoomText, zoom);
    OSReport(M529DebugCamEndText);
}

/* fn_1_5A18. The original invokes the report helper for these four retained
 * designer camera pairs; nothing in the released overlay calls this hook. */
void M529DebugCameraReportAll(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        M529DebugCameraReport(&M529DebugCameraReportFrom[i], &M529DebugCameraReportTo[i]);
    }
}

void M529DebugSequenceFadeOut(s32 time)
{
    if (M529DebugSequence >= 0) {
        HuAudSeqFadeOut(M529DebugSequence, time < 0 ? 1000 : time);
    }
    M529DebugSequence = -1;
}

void M529DebugModelObjectPosGet(s16 modelId, char *objectName, HuVecF *position)
{
    Mtx matrix;

    Hu3DModelObjMtxGet(modelId, objectName, matrix);
    position->x = matrix[0][3];
    position->y = matrix[1][3];
    position->z = matrix[2][3];
}

s32 M529DebugRandRange(s32 minimum, s32 maximum)
{
    return minimum + frandmod(maximum - minimum);
}

BOOL M529DebugCircleOverlap(const HuVecF *a, const HuVecF *b, float radiusA, float radiusB)
{
    float dx = b->x - a->x;
    float dz = b->z - a->z;
    float radius = radiusA + radiusB;

    return dx * dx + dz * dz < radius * radius;
}

s32 M529DebugProjectXToRange(HuVecF *position, s32 minimum, s32 maximum)
{
    HuVecF screen;

    Hu3D3Dto2D(position, 1, &screen);
    return (s32)((float)minimum + screen.x / 576.0f * (float)(maximum - minimum));
}

s32 M529DebugProjectYToRange(HuVecF *position, s32 minimum, s32 maximum)
{
    HuVecF screen;

    Hu3D3Dto2D(position, 1, &screen);
    return (s32)((float)minimum + screen.y / 480.0f * (float)(maximum - minimum));
}

/* The retail result branch only suppresses a record when both members of the
 * relevant pair are COM-controlled.  For draws it uses the first pair.  The
 * original obtains the pair through fn_1_59BC; the group lookup below is the
 * equivalent host representation. */
static BOOL M529RecordTeamAllCom(void)
{
    s32 i;
    s32 team;

    team = M529Winner == 2 ? 0 : M529Winner;
    if (team < 0 || team >= 2) {
        return FALSE;
    }
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        if ((GwPlayerConf[i].grp < 2 ? 0 : 1) == team
            && GwPlayerConf[i].type == GW_TYPE_MAN) {
            return FALSE;
        }
    }
    return TRUE;
}

static BOOL M529RecordUpdate(void)
{
    s32 value;

    value = M529Winner == 2 ? M529TeamScore[0] : M529TeamScore[M529Winner];
    if (value <= M529RecordScore || M529RecordTeamAllCom()) {
        return FALSE;
    }
    GWMgRecordSet(6, value);
    M529RecordScore = value;
    M529RecordPulse = TRUE;
    return TRUE;
}
static void M529TargetInit(OMOBJ *obj)
{
    s32 i;

    /* fn_1_1C8C creates the two target pairs first. */
    for (i = 0; i < 2; i++) {
        s16 modelId;

        modelId = M529TargetScene.modelId[7 + i] = Hu3DModelCreateData(M529TargetData[7 + i]);
        Hu3DModelShadowMapSet(modelId);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(modelId, 1);
        Hu3DModelPosSet(modelId, M529TargetPairPos[i].x, M529TargetPairPos[i].y, M529TargetPairPos[i].z);

        modelId = M529TargetScene.modelId[11 + i] = Hu3DModelCreateData(M529TargetData[11 + i]);
        Hu3DModelShadowMapSet(modelId);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF);
        Hu3DModelLayerSet(modelId, 2);
        Hu3DModelPosSet(modelId, M529TargetPairPos[i].x, M529TargetPairPos[i].y, M529TargetPairPos[i].z);
        Hu3DMotionSpeedSet(modelId, 0.0f);
        Hu3DMotionTimeSet(modelId, 0.0f);
    }

    for (i = 0; i < 4; i++) {
        s16 modelId = M529TargetScene.modelId[1 + i] = Hu3DModelCreateData(M529TargetData[1 + i]);

        Hu3DModelShadowSet(modelId);
        Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
        Hu3DModelLayerSet(modelId, 4);
        Hu3DModelPosSet(modelId, M529PlayerTargetPos[i].x, M529PlayerTargetPos[i].y, M529PlayerTargetPos[i].z);
        Hu3DModelRotSet(modelId, M529PlayerTargetRot[i].x, M529PlayerTargetRot[i].y, M529PlayerTargetRot[i].z);
        Hu3DMotionSpeedSet(modelId, 0.0f);
        Hu3DMotionTimeSet(modelId, 0.0f);
    }

    M529TargetScene.modelId[5] = Hu3DModelCreateData(M529TargetData[5]);
    Hu3DModelAttrSet(M529TargetScene.modelId[5], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DMotionSpeedSet(M529TargetScene.modelId[5], 0.0f);

    M529TargetScene.modelId[6] = Hu3DModelCreateData(M529TargetData[6]);
    Hu3DModelAttrSet(M529TargetScene.modelId[6], HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
    Hu3DModelRotSet(M529TargetScene.modelId[6], 0.0f, 30.0f, 0.0f);
    Hu3DModelPosSet(M529TargetScene.modelId[6], -1300.0f, -350.0f, -2500.0f);

    M529TargetScene.modelId[0] = Hu3DModelCreateData(M529TargetData[0]);
    Hu3DModelAttrSet(M529TargetScene.modelId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelLayerSet(M529TargetScene.modelId[0], 0);
    Hu3DMotionSpeedSet(M529TargetScene.modelId[0], 0.0f);
    Hu3DMotionTimeSet(M529TargetScene.modelId[0], 0.0f);
    Hu3DModelShadowMapSet(M529TargetScene.modelId[0]);
    Hu3DModelPosSet(M529TargetScene.modelId[0], 0.0f, 4.0f, 200.0f);
    M529StageMotionLength = (s32)Hu3DMotionMaxTimeGet(M529TargetScene.modelId[0]);
    M529StageMotionDirection = FALSE;
    M529StageMotionFrame = M529StageMotionLength;
    M529StageJointMotion = Hu3DJointMotionData(M529TargetScene.modelId[0], 0x0057000B);
    M529StageMotionStarted = FALSE;

    /* The reference reveals only the models it actually created.  In
     * particular, data entries 9 and 10 are owned by fn_1_2714. */
    for (i = 0; i < 14; i++) {
        if (i != 9 && i != 10) {
            Hu3DModelAttrReset(M529TargetScene.modelId[i], HU3D_ATTR_DISPOFF);
        }
    }
    obj->objFunc = M529MainController;
}
static void M529TargetUpdate(OMOBJ *obj);
static void M529AuxControllerInit(OMOBJ *obj);

/* fn_1_1780 (63 instructions). This maps the distance from the target lane
 * into the accuracy band used by the player controller. */
static void M529PlayerScoreBandUpdate(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    if (player->unk74 >= 1 && player->unk74 <= 7) {
        player->unk80 = 5;
        player->unk54 = 1;
    } else if (player->unk74 >= 8 && player->unk74 <= 20) {
        player->unk80 = 4;
        player->unk54 = 1;
    } else if (player->unk74 >= 21 && player->unk74 <= 40) {
        player->unk80 = 3;
        player->unk54 = 1;
    } else if (player->unk74 >= 41 && player->unk74 <= 59) {
        player->unk80 = 2;
        player->unk54 = 1;
    } else {
        player->unk80 = 1;
        player->unk54 = 0;
    }

    if (player->unk80 == 1 || player->unk64 >= player->unk70) {
        player->unk60 = 0;
    }
}

/* fn_1_B98's rear-lane input half. fn_1_4780 consumes the resulting band. */
static void M529PlayerTimingInputUpdate(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    if ((player->btnDown & 0x40) != 0 && (player->btnDown & 0x20) == 0) {
        if (player->unk7C == 1 || player->unk7C == -1) {
            player->unk74 = M529RoundFrame - player->unk78;
            player->unk78 = M529RoundFrame;
            player->unk7C = 0;
            M529PlayerScoreBandUpdate(obj);
        }
    } else if ((player->btnDown & 0x20) != 0
        && (player->unk7C == 0 || player->unk7C == -1)) {
        player->unk74 = M529RoundFrame - player->unk78;
        player->unk78 = M529RoundFrame;
        player->unk7C = 1;
        M529PlayerScoreBandUpdate(obj);
    }
    if (M529RoundFrame - player->unk78 >= 61) {
        player->unk80 = 1;
    }
    M529PlayerTargetSequenceUpdate(obj);
}

/* fn_1_4780's target-motion core. Its midpoint latch is the retail
 * score-commit point. */
static void M529PlayerTargetSequenceUpdate(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    M529_PLAYER *partner = M529PlayerObj[player->partnerNo]->data;
    s16 targetA = player->side == 3001 ? 1 : 3;
    s16 targetB = targetA + 1;
    s32 sfxSide = player->side == 3001 ? 0 : 1;

    if (player->unk60 != 0) {
        player->unk54 = 1;
    }
    switch (player->unk80) {
        case 0:
            player->unk68 = 0.0f;
            player->unk60 = 0;
            break;
        case 1:
        case 2:
            player->unk68 = 1.0f;
            break;
        case 3:
            player->unk68 = 1.2f;
            break;
        case 4:
            player->unk68 = 1.5f;
            break;
        case 5:
            player->unk68 = 2.0f;
            break;
    }
    if (GwPlayerConf[player->playerNo].type != GW_TYPE_MAN && player->unk6C == 0) {
        player->unk68 = 1.0f;
    }
    if (M529TargetSequenceSfx[sfxSide] != -1) {
        s16 pitch = 0;

        if (player->unk68 == 2.0f) {
            pitch = 0x2000;
        } else if (player->unk68 == 1.5f) {
            pitch = 0x1000;
        } else if (player->unk68 == 1.2f) {
            pitch = 0x6A4;
        }
        HuAudFXPitchSet(M529TargetSequenceSfx[sfxSide], pitch);
    }

    if (player->unk58 == 0 && player->unk54 != 0) {
        player->unk6C++;
        player->unk48 = 1;
        if (player->unk68 < 1.0f) {
            player->unk68 = 1.0f;
        }
        if (player->unk68 > 2.0f) {
            player->unk68 = 2.0f;
        }
        /* fn_1_4780 divides (motion length + 1), then truncates. */
        player->unk70 = (s32)((Hu3DMotionMaxTimeGet(M529TargetScene.modelId[targetA]) + 1.0f)
            / player->unk68);
        player->unk50 = player->unk70 / 2 - 1;
        player->unk64 = 0;
        player->unk58 = 1;
        player->unk54 = 0;
        Hu3DMotionSpeedSet(M529TargetScene.modelId[targetA], player->unk68);
        Hu3DMotionSpeedSet(M529TargetScene.modelId[targetB], player->unk68);
        CharMotionSpeedSet(player->charNo, player->unk68);
        Hu3DMotionTimeSet(M529TargetScene.modelId[targetA], 0.0f);
        Hu3DMotionTimeSet(M529TargetScene.modelId[targetB], 0.0f);
        CharMotionTimeSet(player->charNo, 0.0f);
    }

    if (player->unk58 != 0) {
        player->unk64++;
        player->unk5C = player->unk64 == player->unk50 + 1;
        if (player->unk64 >= player->unk70) {
            player->unk58 = 0;
            if (player->unk60 != 0) {
                Hu3DMotionSpeedSet(M529TargetScene.modelId[targetA], player->unk68);
                Hu3DMotionSpeedSet(M529TargetScene.modelId[targetB], player->unk68);
                CharMotionSpeedSet(player->charNo, player->unk68);
            } else {
                Hu3DMotionSpeedSet(M529TargetScene.modelId[targetA], 0.0f);
                Hu3DMotionSpeedSet(M529TargetScene.modelId[targetB], 0.0f);
                CharMotionSpeedSet(player->charNo, 0.0f);
            }
            Hu3DMotionTimeSet(M529TargetScene.modelId[targetA], 0.0f);
            Hu3DMotionTimeSet(M529TargetScene.modelId[targetB], 0.0f);
            CharMotionTimeSet(player->charNo, 0.0f);
            player->unk64 = 0;
        }
    }

    if (player->unk5C != 0 && (partner->unk0C == 0 || partner->unk0C == 2)) {
        if (partner->unk40 != 0) {
            if (player->state == 2001 && player->unk48 != 0) {
                M529TeamScore[player->side == 3001 ? 0 : 1]++;
                player->unk48 = 0;
            }
        } else if (partner->unk0C == 0) {
            partner->unk0C = 1;
        }
    }

    if (player->unk58 == 0 && player->unk54 == 0) {
        if (M529TargetSequenceSfx[sfxSide] != -1) {
            HuAudFXStop(M529TargetSequenceSfx[sfxSide]);
            M529TargetSequenceSfx[sfxSide] = -1;
        }
    } else if (M529TargetSequenceSfx[sfxSide] == -1) {
        M529TargetSequenceSfx[sfxSide] = HuAudFXPlay(sfxSide == 0 ? 0x790 : 0x791);
    }
}

/* fn_1_444C / fn_1_4488: gates used by the input and scripted states. */
static s32 M529PlayerInputReady(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    return player->unk40 != 0 || player->unk3C == 0;
}

static s32 M529PlayerScoreReady(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    return player->unk58 != 0 || player->unk54 == 0;
}

/* fn_1_4F10/fn_1_500C/fn_1_5084 and their two direct leaves.  The original
 * main state machine consumes these as pad-button bits, so keep them separate
 * from the target-sequence update that consumes a rear-lane timing attempt. */
static u16 M529ComFrontButtonDown(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    M529_PLAYER *partner = M529PlayerObj[player->partnerNo]->data;

    switch (player->difficulty) {
        case GW_DIF_EASY:
            if (player->unk40 == 0 && --player->comParamC4 < 0) {
                player->comParamC4 = frandmod(30) + 30;
                return PAD_BUTTON_A;
            }
            break;
        case GW_DIF_NORMAL:
        case GW_DIF_HARD:
        case GW_DIF_VERYHARD:
            if (player->unk40 == 0 && frandmod(player->comParamBC) != 0
                && partner->unk64 == partner->unk50) {
                return PAD_BUTTON_A;
            }
            break;
    }
    return 0;
}

static u16 M529ComFrontButton(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    return player->difficulty == GW_DIF_EASY ? PAD_BUTTON_A : 0;
}

static u16 M529ComRearDecision(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    if (player->unk7C == -1) {
        return 0x40;
    }
    return player->unk7C == 0 ? 0x20 : 0x40;
}

static s32 M529ComDelay(s32 min, s32 max)
{
    return min > max ? 0 : min + frandmod(max - min);
}

static u16 M529ComRearButtonDown(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    u16 button = 0;

    if (player->difficulty < GW_DIF_EASY || player->difficulty > GW_DIF_VERYHARD) {
        return 0;
    }
    if (player->comParamCC == -1) {
        player->comParamC4 = 0;
    }
    if (--player->comParamC4 < 0) {
        if (player->unk7C == -1 || frandmod(player->comParamC0) != 0) {
            button = M529ComRearDecision(obj);
        }
        player->comParamC4 = M529ComDelay(player->comParamC8, player->comParamCC);
    }
    return button;
}

/* fn_1_44C4. Handles the post-input hop and restores the idle motion after
 * the player returns to the ground. */
static void M529PlayerHopUpdate(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    if (player->unk40 == 0 && player->unk3C != 0) {
        HuVecF screenPos;

        player->unk44 = 0;
        player->unk40 = 1;
        player->unk3C = 0;
        player->unk38 = 0;
        player->unk90.y = 1300.0f;
        player->motionNo = 3;
        CharMotionShiftSet(player->charNo, obj->mtnId[3], 0.0f, 4.0f, HU3D_MOTATTR_NONE);
        Hu3D3Dto2D(&player->pos, 1, &screenPos);
        CharFXPlayPan(player->charNo, 0x9E,
            (s16)(32.0f + screenPos.x / 576.0f * 64.0f));
    }

    if (player->unk40 != 0) {
        if (player->unk44 == 6) {
            player->unk38 = (player->btn & 0x100) != 0;
        }
        player->unk90.y += player->unk38 ? -36.0000025f : -146.25001f;
        player->pos.y += 1.35f * (1.0f / 60.0f) * player->unk90.y;
        player->unk44++;
        if (player->pos.y <= 0.0f) {
            player->unk40 = 0;
            player->pos.y = 0.0f;
            player->unk38 = 0;
            CharModelLandDustCreate(player->charNo, &player->pos);
        }
    }

    if (player->unk9C > player->pos.y && player->pos.y <= 65.0f && player->motionNo != 0) {
        player->motionNo = 0;
        CharMotionShiftSet(player->charNo, obj->mtnId[0], 0.0f, 5.0f, HU3D_MOTATTR_LOOP);
    }
    player->unk9C = player->pos.y;
}

static float M529AngleApproach(float angle, float rate)
{
    float delta = fmodf(-angle, 360.0f);

    if (delta < 0.0f) {
        delta += 360.0f;
    }
    if (delta > 180.0f) {
        delta -= 360.0f;
    }
    angle = fmodf(angle + delta * rate, 360.0f);
    return angle < 0.0f ? angle + 360.0f : angle;
}

/* The fall-through body after fn_1_B98's state-2004 controller checks.  The
 * reference writes the per-axis delta to unkAC before adding it to pos. */
static void M529PlayerResultMoveUpdate(M529_PLAYER *player)
{
    const HuVecF *target = &M529PlayerResultPos[player->group];

    player->unkAC.x = (target->x - player->pos.x) / 60.0f;
    player->unkAC.y = (target->y - player->pos.y) / 60.0f;
    player->unkAC.z = (target->z - player->pos.z) / 60.0f;
    player->pos.x += player->unkAC.x;
    player->pos.y += player->unkAC.y;
    player->pos.z += player->unkAC.z;
}

/* fn_1_187C. Player hit-reaction state.  fn_1_B98 selects the collision state;
 * this is the recovered local response once unk0C == 1 has been entered. */
static void M529PlayerCollisionUpdate(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    s16 targetMotion;

    if (player->unk0C == 0 || player->unk0C == 2) {
        if (player->unk0C == 2 && ++player->unk10 > 120) {
            player->unk0C = 0;
            player->unk10 = 0;
        }
        if ((player->btnDown & 0x100) != 0 && player->unk40 == 0) {
            player->unk3C = 1;
        }
        M529PlayerHopUpdate(obj);
    } else if (player->unk0C == 1) {
        if (player->motionNo != 7) {
            HuVecF screenPos;

            player->motionNo = 7;
            CharMotionShiftSet(player->charNo, obj->mtnId[7], 0.0f, 8.0f,
                HU3D_MOTATTR_LOOP);
            if (player->side == 3000) {
                targetMotion = M529TargetScene.modelId[11];
                Hu3DMotionTimeSet(targetMotion, 0.0f);
                Hu3DMotionSpeedSet(targetMotion, 1.0f);
                HuAudFXPlay(0x792);
            } else {
                targetMotion = M529TargetScene.modelId[12];
                Hu3DMotionTimeSet(targetMotion, 0.0f);
                Hu3DMotionSpeedSet(targetMotion, 1.0f);
                HuAudFXPlay(0x793);
            }
            Hu3D3Dto2D(&player->pos, 1, &screenPos);
            CharFXPlayPan(player->charNo, 0x1FD,
                (s16)(32.0f + screenPos.x / 576.0f * 64.0f));
            omVibrate(player->playerNo, 12, 12, 0);
        }
        if (++player->unk10 > 30) {
            player->unk0C = 2;
            player->unk10 = 0;
            player->motionNo = 0;
            CharMotionShiftSet(player->charNo, obj->mtnId[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
        }
    }

    if (player->unk0C == 1 || player->unk0C == 2) {
        if ((++player->unk4C & 1) == 0) {
            CharModelAttrSet(player->charNo, HU3D_ATTR_DISPOFF);
        } else {
            CharModelAttrReset(player->charNo, HU3D_ATTR_DISPOFF);
        }
    } else {
        player->unk4C = 0;
        CharModelAttrReset(player->charNo, HU3D_ATTR_DISPOFF);
    }

    targetMotion = M529TargetScene.modelId[player->side == 3000 ? 11 : 12];
    if (Hu3DMotionEndCheck(targetMotion)) {
        Hu3DMotionSpeedSet(targetMotion, 0.0f);
        Hu3DMotionTimeSet(targetMotion, 0.0f);
    }
}

/* fn_1_B98 follows this initializer in the reference object. The first state
 * remains separated from input state 2001 so the original helper ownership
 * can be restored incrementally without changing the player ABI. */
void M529PlayerMain(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;

    switch (player->state) {
        case 2000:
            if (M529ControllerObj->work[0] >= 1004) {
                player->state++;
            }
            break;
        case 2001:
            /* The 2v2 front lanes accept held and edge input; rear lanes use
             * edge input only. COM sampling joins here once fn_1_4F10..5084
             * is recovered. */
            if (M529ControllerObj->work[0] == 1004) {
                if (GwPlayerConf[player->playerNo].type == GW_TYPE_MAN) {
                    player->btnDown = HuPadBtnDown[player->padNo];
                    player->btn = (player->side == 3000 || player->side == 3002)
                        ? HuPadBtn[player->padNo]
                        : 0;
                } else {
                    if (player->side == 3000 || player->side == 3002) {
                        player->btn = M529ComFrontButton(obj);
                        player->btnDown = M529ComFrontButtonDown(obj);
                    } else {
                        player->btn = 0;
                        player->btnDown = M529ComRearButtonDown(obj);
                    }
                }
                M529PlayerCollisionUpdate(obj);
                if (player->side == 3001 || player->side == 3003) {
                    M529PlayerTimingInputUpdate(obj);
                }
            }
            if (M529ControllerObj->work[0] >= 1005) {
                player->state = 2002;
            }
            break;
        case 2002:
            if (player->side == 3000 || player->side == 3002) {
                CharModelAttrReset(player->charNo, HU3D_ATTR_DISPOFF);
                if (M529PlayerInputReady(obj)) {
                    M529PlayerHopUpdate(obj);
                }
            } else if (M529PlayerScoreReady(obj)) {
                M529PlayerTargetSequenceUpdate(obj);
            }
            if (M529ControllerObj->work[0] >= 1006) {
                player->state = 2003;
                player->motionNo = 0;
                CharMotionShiftSet(player->charNo, obj->mtnId[0], 0.0f, 8.0f,
                    HU3D_MOTATTR_LOOP);
            }
            break;
        case 2003:
            player->rotY = M529AngleApproach(player->rotY, 0.5f);
            if (M529ControllerObj->work[0] >= 1007) {
                player->state = 2004;
            }
            break;
        case 2004:
            if (player->motionNo != 2) {
                player->motionNo = 2;
                CharMotionShiftSet(player->charNo, obj->mtnId[2], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            }
            if (M529ControllerObj->work[0] == 1008) {
                player->state = 2005;
                player->motionNo = 0;
                CharMotionShiftSet(player->charNo, obj->mtnId[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            } else if (M529ControllerObj->work[0] == 1009) {
                player->state = 2006;
                player->motionNo = 0;
                CharMotionShiftSet(player->charNo, obj->mtnId[0], 0.0f, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                M529PlayerResultMoveUpdate(player);
            }
            break;
        case 2005:
            if (M529ControllerObj->work[0] == 1009) {
                player->state = 2006;
            }
            break;
        case 2006:
            if (M529ControllerObj->work[0] >= 1009) {
                player->state = 2007;
                if (player->side == 3000 || player->side == 3001) {
                    if (M529Winner == 0) {
                        player->motionNo = 4;
                        if (M529ResultSfx[0] == -1) {
                            M529ResultSfx[0] = HuAudFXPlay(0x794);
                        }
                    } else {
                        player->motionNo = 5;
                        if (M529Winner == 2 && player->playerNo == 0) {
                            HuVecF screenPos;

                            Hu3D3Dto2D(&player->pos, 1, &screenPos);
                            CharFXPlayPan(player->charNo, 0x200,
                                (s16)(32.0f + screenPos.x / 576.0f * 64.0f));
                        }
                    }
                } else if (M529Winner == 1) {
                    player->motionNo = 4;
                    if (M529ResultSfx[1] == -1) {
                        M529ResultSfx[1] = HuAudFXPlay(0x795);
                    }
                } else {
                    player->motionNo = 5;
                    if (M529Winner == 2 && player->playerNo == 0) {
                        HuVecF screenPos;

                        Hu3D3Dto2D(&player->pos, 1, &screenPos);
                        CharFXPlayPan(player->charNo, 0x200,
                            (s16)(32.0f + screenPos.x / 576.0f * 64.0f));
                    }
                }
                CharMotionShiftSet(player->charNo, obj->mtnId[player->motionNo],
                    0.0f, 8.0f, HU3D_MOTATTR_NONE);
            }
            break;
        case 2007:
            player->rotY = M529AngleApproach(player->rotY, 0.4f);
            break;
        case 2008:
            break;
    }

    /* fn_1_B98 continuously re-pans characters once the result sequence has
     * begun.  The draw cheer has its own one-shot pan above; this keeps the
     * ordinary character voices spatially correct while the camera moves. */
    if (player->state > 2002) {
        HuVecF screenPos;

        Hu3D3Dto2D(&player->pos, 1, &screenPos);
        CharModelVoicePanSet(player->charNo,
            (s16)(32.0f + screenPos.x / 576.0f * 64.0f));
    }
    obj->trans = player->pos;
    obj->rot.x = 0.0f;
    obj->rot.y = player->rotY;
    obj->rot.z = 0.0f;
}

/* fn_1_5E0, 366 instructions. */
static void M529PlayerInit(OMOBJ *obj)
{
    M529_PLAYER *player = obj->data;
    s32 i;

    player->playerNo = obj->work[0];
    player->charNo = GwPlayerConf[player->playerNo].charNo;
    player->group = GwPlayerConf[player->playerNo].grp;
    player->groupCopy = player->group;
    player->padNo = GwPlayerConf[player->playerNo].padNo;
    player->difficulty = GwPlayerConf[player->playerNo].dif;
    player->state = 2000;
    player->motionNo = 0;
    player->unk0C = 0;
    player->unk10 = 0;
    player->unk38 = 0;
    player->unk3C = 0;
    player->unk40 = 0;
    player->unk44 = 0;
    player->unk48 = 0;
    player->unk4C = 0;
    player->unk50 = 30;
    player->unk54 = 0;
    player->unk58 = 0;
    player->unk5C = 0;
    player->unk60 = 0;
    player->unk64 = 0;
    player->unk68 = 0.0f;
    player->unk7C = -1;
    player->unk80 = 0;
    player->unkAC.x = 0.0f;
    player->unkAC.y = 0.0f;
    player->unkAC.z = 0.0f;
    player->unk90.x = 0.0f;
    player->unk90.y = 0.0f;
    player->unk90.z = 0.0f;
    player->unk70 = 60;
    player->unk74 = 60;
    player->unk78 = 0;
    player->unk6C = 0;

    switch (player->group) {
        case 0:
            player->side = 3000;
            player->partnerGroup = 1;
            break;
        case 1:
            player->side = 3001;
            player->partnerGroup = 0;
            break;
        case 2:
            player->side = 3002;
            player->partnerGroup = 3;
            break;
        case 3:
            player->side = 3003;
            player->partnerGroup = 2;
            break;
    }
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        if (i != player->playerNo && GwPlayerConf[i].grp == player->partnerGroup) {
            player->partnerNo = i;
        }
    }

    player->comParamC4 = 0;
    switch (player->difficulty) {
        case 0:
            player->comParamC8 = 35;
            player->comParamCC = 55;
            player->comParamC4 = player->comParamC8;
            player->comParamC0 = 10;
            player->comParamBC = 10;
            break;
        case 1:
            player->comParamC8 = 20;
            player->comParamCC = 50;
            player->comParamC4 = player->comParamC8;
            player->comParamC0 = 20;
            player->comParamBC = 5;
            break;
        case 2:
            player->comParamC8 = 8;
            player->comParamCC = 40;
            player->comParamC4 = player->comParamC8;
            player->comParamC0 = 15;
            player->comParamBC = 40;
            break;
        case 3:
            player->comParamC8 = 1;
            player->comParamCC = 25;
            player->comParamC4 = player->comParamC8;
            player->comParamC0 = 50;
            player->comParamBC = 50;
            break;
    }

    obj->mdlId[0] = CharModelCreate(player->charNo, 2);
    Hu3DModelShadowSet(obj->mdlId[0]);
    CharModelStepFxSet(player->charNo, FALSE);
    for (i = 0; i < 8; i++) {
        obj->mtnId[i] = CharMotionCreate(player->charNo, M529PlayerMotionData[i]);
        CharMotionSet(player->charNo, obj->mtnId[i]);
    }
    CharModelAttrSet(player->charNo, HU3D_ATTR_DISPOFF);
    CharModelAttrSet(player->charNo, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(obj->mdlId[0], 3);
    CharMotionSet(player->charNo, obj->mtnId[0]);
    CharEffectLayerSet(2);

    if (player->side == 3000 || player->side == 3002) {
        player->rotY = 0.0f;
    } else {
        player->rotY = 180.0f;
        CharMotionSet(player->charNo, obj->mtnId[6]);
        CharMotionSpeedSet(player->charNo, 0.0f);
        CharMotionTimeSet(player->charNo, 0.0f);
    }
    player->unkA8 = 0.0f;
    player->pos = M529PlayerStartPos[player->group];
    obj->trans = player->pos;
    obj->rot.x = 0.0f;
    obj->rot.y = player->rotY;
    obj->rot.z = 0.0f;
    CharModelAttrReset(player->charNo, HU3D_ATTR_DISPOFF);
    CharMotionDataClose(player->charNo);
    obj->objFunc = M529PlayerMain;
}

/* ObjectSetup. The object priorities and model/motion capacities are the
 * values from the original graph; camera/light values are the first view in
 * its .data camera table. */
void ObjectSetup(void)
{
    s32 i;
    HU3DLIGHTID light;
    static HuVecF lightPos = { 0.0f, 1500.0f, 0.0f };
    static HuVecF lightAim = { 0.0f, 0.0f, 0.0f };
    static HuVecF shadowPos = { 0.0f, 1500.0f, 0.0f };
    static HuVecF shadowUp = { 0.0f, 1.0f, 0.0f };
    static HuVecF shadowTarget = { 0.0f, 0.0f, 300.0f };

    M529TeamScore[0] = 0;
    M529TeamScore[1] = 0;
    M529RecordScore = GWMgRecordGet(6);
    M529RecordPulse = FALSE;
    M529ResultRecordChecked = FALSE;
    M529RecordMessageActive = FALSE;
    M529Winner = -1;
    M529ControllerStateTimer = 0.0f;
    M529RoundFrame = 0;
    M529TargetObj = NULL;
    M529Message = -1;
    M529Bgm = -1;
    M529StartSfx = -1;
    M529StageMotionSfx = -1;
    M529StageMotionStarted = FALSE;
    M529StageMotionDirection = FALSE;
    M529TargetSequenceSfx[0] = -1;
    M529TargetSequenceSfx[1] = -1;
    M529ResultSfx[0] = -1;
    M529ResultSfx[1] = -1;
    M529ObjMan = omInitObjMan(200, 0x2000);
    omGameSysInit(M529ObjMan);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 7000.0f, 4.0f / 3.0f);
    omCameraViewSet(&M529CameraView);
    omAddObjEx(M529ObjMan, 0x7FDA, 0, 0, OM_GRP_NONE, omOutView)->work[0] = 1;

    light = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0, 0, 0, 0, 0, 0);
    Hu3DGLightPosAimSetV(light, &lightPos, &lightAim);
    Hu3DGLightStaticSet(light, TRUE);
    Hu3DGLightColorSet(light, 255, 255, 255, 255);
    Hu3DGLightInfinitytSet(light);
    Hu3DShadowCreate(20.0f, 20.0f, 7000.0f);
    Hu3DShadowColSet(0, 0, 64);
    Hu3DShadowTPLvlSet(0.5f);
    Hu3DShadowPosSet(&shadowPos, &shadowUp, &shadowTarget);

    omMakeGroupEx(M529ObjMan, 0, GW_PLAYER_MAX);

    for (i = 0; i < GW_PLAYER_MAX; i++) {
        M529PlayerObj[i] = omAddObjEx(M529ObjMan, 100, 1, 8, 0, M529PlayerInit);
        M529PlayerObj[i]->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M529_PLAYER), HU_MEMNUM_OVL);
        M529PlayerObj[i]->work[0] = i;
    }

    M529ControllerObj = omAddObjEx(M529ObjMan, 101, 14, 0, OM_GRP_NONE, M529TargetInit);
    M529ControllerObj->work[0] = 1000;
    M529TargetObj = omAddObjEx(M529ObjMan, 103, 8, 0, OM_GRP_NONE, M529TargetUpdate);
    M529TargetObj->work[0] = 0;
    omAddObjEx(M529ObjMan, 102, 0, 0, OM_GRP_NONE, M529AuxControllerInit);
    M529Timer = MgTimerCreate(0);
    MgTimerParamSet(M529Timer, 0x708, 0, 0);
    WipeCreate(WIPE_MODE_IN, WIPE_TYPE_PREVTYPE, 60);
}

/* fn_1_3CE0. The original uses lbl_1_bss_1C, which doubles as the final
 * winner selector: 0 and 1 select a target set; -1 and 2 leave both hidden. */
static void M529TargetMoveInUpdate(void)
{
    s32 i;
    s32 set = M529Winner;

    if (set < 0 || set >= 2) {
        return;
    }
    for (i = 0; i < 4; i++) {
        Hu3DModelAttrReset(M529TargetModel[set][i], HU3D_ATTR_DISPOFF);
        M529TargetPos[set][i].x += (M529TargetGoalPos[set][i].x - M529TargetPos[set][i].x) / 60.0f;
        M529TargetPos[set][i].y += (M529TargetGoalPos[set][i].y - M529TargetPos[set][i].y) / 60.0f;
        M529TargetPos[set][i].z += (M529TargetGoalPos[set][i].z - M529TargetPos[set][i].z) / 60.0f;
        Hu3DModelPosSet(M529TargetModel[set][i], M529TargetPos[set][i].x,
            M529TargetPos[set][i].y, M529TargetPos[set][i].z);
    }
}

/* fn_1_4048. The chosen target set floats with a phase-offset sine-squared
 * bob. The base position stays in M529TargetPos so fn_1_3CE0 can continue to
 * converge independently of this display-only offset. */
static void M529TargetWaveUpdate(void)
{
    s32 i;
    s32 set = M529Winner;

    if (set < 0 || set >= 2) {
        return;
    }
    for (i = 0; i < 4; i++) {
        float wave = sinf(3.14159265358979323846f * M529TargetPhase[set][i]);

        wave *= wave;
        Hu3DModelPosSet(M529TargetModel[set][i], M529TargetPos[set][i].x,
            M529TargetPos[set][i].y + 25.0f * wave, M529TargetPos[set][i].z);
        M529TargetPhase[set][i] += 0.011111111f;
    }
}

/* fn_1_2B70. The initializer below replaces itself with this compact target
 * controller. The result presentation selects work[0] = 1 to reveal the
 * winning team's set for 61 frames before it settles into its wave. */
static void M529TargetController(OMOBJ *obj)
{
    if (obj->work[0] == 1) {
        if (obj->work[1] > 60) {
            obj->work[0] = 2;
            obj->work[1] = 0;
        } else {
            M529TargetMoveInUpdate();
            obj->work[1]++;
        }
    }
    M529TargetWaveUpdate();
}

/* fn_1_2714. This priority-103 object owns the data-table entries 9 and 10,
 * four copies per side. They remain hidden until fn_1_3CE0's transition;
 * making them visible at construction would expose the off-stage staging
 * positions and is the visual error the previous placeholder avoided. */
static void M529TargetUpdate(OMOBJ *obj)
{
    s32 i;
    s32 set;

    for (set = 0; set < 2; set++) {
        for (i = 0; i < 4; i++) {
            s16 modelId = M529TargetModel[set][i] = Hu3DModelCreateData(M529TargetData[9 + set]);

            Hu3DModelShadowSet(modelId);
            Hu3DModelAttrSet(modelId, HU3D_ATTR_DISPOFF | HU3D_ATTR_NOCULL);
            M529TargetPos[set][i] = M529TargetStartPos[set][i];
            Hu3DModelPosSet(modelId, M529TargetPos[set][i].x, M529TargetPos[set][i].y,
                M529TargetPos[set][i].z);
            Hu3DModelRotSet(modelId, M529TargetSetRot[i].x, M529TargetSetRot[i].y,
                M529TargetSetRot[i].z);
            M529TargetPhase[set][i] = 0.5f * (float)i;
        }
    }
    obj->objFunc = M529TargetController;
}

static void M529ScoreUpdate(OMOBJ *obj)
{
    M529_SCORE_WORK *score = obj->data;
    s32 i;

    MgScoreValueSet(score->recordScore, M529RecordScore);
    if (M529RecordPulse) {
        if (!score->pulseRising) {
            score->pulseScale += 0.02f;
            if (score->pulseScale >= 1.2f) {
                score->pulseScale = 1.2f;
                score->pulseRising = TRUE;
            }
        } else {
            score->pulseScale -= 0.04f;
            if (score->pulseScale <= 1.0f) {
                score->pulseScale = 1.0f;
                score->pulseRising = FALSE;
            }
        }
        MgScoreDigitScaleSet(score->recordScore, score->pulseScale, score->pulseScale);
        espScaleSet(score->recordLabel, score->pulseScale, score->pulseScale);
    }
    for (i = 0; i < 2; i++) {
        MgScoreValueSet(score->teamScore[i], M529TeamScore[i]);
        if (M529ControllerObj->work[0] >= 1004) {
            MgScoreDispOn(score->teamScore[i]);
            MgScoreWinDispSet(M529TeamWin[i], TRUE);
        } else {
            MgScoreDispOff(score->teamScore[i]);
            MgScoreWinDispSet(M529TeamWin[i], FALSE);
        }
    }
    MgScoreWinDispSet(M529WinnerIcon, TRUE);
    espDispOn(score->recordLabel);
    MgScoreDispOn(score->recordScore);
}

/* fn_1_5204: two team panels, a centre win icon, and the small record panel.
 * The constants below are the original .rodata:E8..108 layout. */
static void M529AuxControllerInit(OMOBJ *obj)
{
    M529_SCORE_WORK *score;

    score = HuMemDirectMallocNum(HEAP_HEAP, sizeof(*score), HU_MEMNUM_OVL);
    obj->data = score;
    score->unk00 = 0;

    M529TeamWin[0] = MgScoreWinCreate(64, 40);
    MgScoreWinColorSet(M529TeamWin[0], 0xFA, 0x00, 0x1E);
    MgScoreWinTPLvlSet(M529TeamWin[0], 0.7f);
    MgScoreWinPosSet(M529TeamWin[0], 48.0f, 60.0f);
    score->teamScore[0] = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
    MgScoreValueSet(score->teamScore[0], M529TeamScore[0]);
    MgScorePosSet(score->teamScore[0], 38.0f, 60.0f);
    MgScoreMaxDigitSet(score->teamScore[0], 2);
    MgScoreDispOff(score->teamScore[0]);

    M529TeamWin[1] = MgScoreWinCreate(64, 40);
    MgScoreWinColorSet(M529TeamWin[1], 0x00, 0x32, 0xFA);
    MgScoreWinTPLvlSet(M529TeamWin[1], 0.7f);
    MgScoreWinPosSet(M529TeamWin[1], 528.0f, 60.0f);
    score->teamScore[1] = MgScoreCreate(MGCONST_ANM_scoreMedium, -1, TRUE);
    MgScoreValueSet(score->teamScore[1], M529TeamScore[1]);
    MgScorePosSet(score->teamScore[1], 518.0f, 60.0f);
    MgScoreMaxDigitSet(score->teamScore[1], 2);
    MgScoreDispOff(score->teamScore[1]);

    M529WinnerIcon = MgScoreWinCreate(72, 48);
    MgScoreWinTPLvlSet(M529WinnerIcon, 0.7f);
    MgScoreWinPosSet(M529WinnerIcon, 288.0f, 416.0f);
    score->recordLabel = espEntry(MGCONST_ANM_scoreRecord, 10, 0);
    espDispOff(score->recordLabel);
    espDrawNoSet(score->recordLabel, 0);
    espPosSet(score->recordLabel, 269.0f, 416.0f);
    score->recordScore = MgScoreCreate(MGCONST_ANM_scoreSmall, -1, TRUE);
    MgScoreValueSet(score->recordScore, M529RecordScore);
    MgScorePosSet(score->recordScore, 290.0f, 416.0f);
    MgScoreMaxDigitSet(score->recordScore, 2);
    MgScoreDispOff(score->recordScore);
    MgScoreColorSet(score->recordScore, 0x42, 0xFF, 0x7A);
    score->pulseRising = FALSE;
    score->pulseScale = 1.0f;
    obj->objFunc = M529ScoreUpdate;
}

static GAMEMESID M529WinnerMessageCreate(void)
{
    s16 winner[GW_PLAYER_MAX] = {
        GAMEMES_MG_WINNER_NONE, GAMEMES_MG_WINNER_NONE,
        GAMEMES_MG_WINNER_NONE, GAMEMES_MG_WINNER_NONE
    };
    s32 i;
    s32 n = 0;

    if (M529Winner == 2) {
        HuAudJinglePlay(0x7B);
        /* fn_1_2BEC uses the ordinary MG draw panel (2, 2). Passing only
         * the type to the winner panel makes its initializer consume four
         * nonexistent variadic character arguments on the PC host. */
        return GameMesMgDrawCreate();
    }
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        if ((GwPlayerConf[i].grp < 2 ? 0 : 1) == M529Winner) {
            winner[n++] = GwPlayerConf[i].charNo;
            GWMgCoinBonusAdd(i, 10);
        }
    }
    HuAudJinglePlay(0x79);
    return GameMesMgWinnerCreate(winner[0], winner[1], winner[2], winner[3]);
}

/* fn_1_4290. The Object Manager invokes this after the final wipe finishes;
 * do not return before WipeCheckEnd or resultdll can observe a live overlay. */
static void M529ExitAfterWipe(OMOBJ *obj)
{
    s32 i;

    (void)obj;
    if (WipeCheckEnd()) {
        return;
    }
    if (M529Message >= 0) {
        GameMesKill(M529Message);
        M529Message = -1;
    }
    GameMesClose();
    HuAudAllStop();
    for (i = 0; i < GW_PLAYER_MAX; i++) {
        if (M529PlayerObj[i] != NULL) {
            M529_PLAYER *player = M529PlayerObj[i]->data;
            if (player != NULL) {
                CharModelKill(player->charNo);
            }
        }
    }
    MgTimerKill(M529Timer);
    omOvlReturnEx(1, TRUE);
}

/* fn_1_2BEC, state 1000. The target initializer installs this callback on
 * the priority-101 object. Its first 15 frames are the opening camera gate. */
static void M529MainController(OMOBJ *obj)
{
    switch (obj->work[0]) {
        case 1000:
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer >= 15.0f) {
                obj->work[0]++;
                M529ControllerStateTimer = 0.0f;
                Hu3DMotionSpeedSet(M529TargetScene.modelId[0], 1.0f);
                M529StartSfx = HuAudFXPlay(0x797);
            }
            break;
        case 1001:
            /* Reference camera move: 60 frames (data:0x328). */
            if (M529ControllerStateTimer == 0.0f) {
                omCameraViewMoveSimple((OMCAMERAVIEW *)&M529CameraMove[0], 60);
            }
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer >= 60.0f) {
                obj->work[0]++;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1002:
            /* Reference camera move: 80 frames (data:0x344). */
            if (M529ControllerStateTimer == 0.0f) {
                omCameraViewMoveSimple((OMCAMERAVIEW *)&M529CameraMove[1], 80);
            }
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer >= 80.0f) {
                obj->work[0]++;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1003:
            if (M529Message == -1) {
                M529Message = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_START);
                M529Bgm = HuAudSStreamPlay(60);
            } else if (GameMesStatGet(M529Message) == 0) {
                M529Message = -1;
                MgTimerModeOnSet(M529Timer, TRUE);
                obj->work[0] = 1004;
            }
            break;
        case 1004:
            M529ControllerStateTimer += 1.0f;
            M529RoundFrame++;
            if (MgTimerDoneCheck(M529Timer)) {
                if (M529TeamScore[0] > M529TeamScore[1]) {
                    M529Winner = 0;
                } else if (M529TeamScore[1] > M529TeamScore[0]) {
                    M529Winner = 1;
                } else {
                M529Winner = 2;
                }
                obj->work[0] = 1005;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1005:
            if (M529Message == -1) {
                M529Message = GameMesCreate(GAMEMES_MES_MG, GAMEMES_MG_TYPE_FINISH);
                HuAudSStreamFadeOut(M529Bgm, 100);
            } else if (GameMesStatGet(M529Message) == 0) {
                M529Message = -1;
                obj->work[0] = 1006;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1006:
            /* Retail's post-FINISH gate is a plain 30-frame delay. */
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer >= 30.0f) {
                obj->work[0] = 1007;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1007:
            if (M529ControllerStateTimer == 0.0f) {
                omCameraViewMoveSimple((OMCAMERAVIEW *)&M529CameraMove[2], 80);
            }
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer >= 80.0f) {
                M529ResultRecordChecked = TRUE;
                obj->work[0] = M529RecordUpdate() ? 1008 : 1009;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1008:
            if (M529Message == -1) {
                M529RecordMessageActive = TRUE;
                M529Message = GameMesRecordCreate(M529RecordScore);
            } else if (GameMesStatGet(M529Message) == 0) {
                M529Message = -1;
                M529RecordMessageActive = FALSE;
                obj->work[0] = 1009;
                M529ControllerStateTimer = 0.0f;
            }
            break;
        case 1009:
            /* 2BEC creates the winner panel as it enters this state, keeps
             * it visible for 31 ticks, then starts the final fade. */
            if (M529ControllerStateTimer > 30.0f) {
                obj->work[0] = 1010;
                M529ControllerStateTimer = 0.0f;
                M529Message = -1;
            } else {
                if (M529ControllerStateTimer == 0.0f) {
                    M529Message = M529WinnerMessageCreate();
                    M529TargetObj->work[0] = 1;
                }
                M529ControllerStateTimer += 1.0f;
            }
            break;
        case 1010:
            M529ControllerStateTimer += 1.0f;
            if (M529ControllerStateTimer > 0.0f) {
                HuAudSeqAllFadeOut(1000);
                HuAudSStreamAllFadeOut(1000);
                M529EffectsFadeOut();
                M529Message = -1;
                WipeCreate(WIPE_MODE_OUT, WIPE_TYPE_WHITEFADE, 60);
                obj->objFunc = M529ExitAfterWipe;
            }
            break;
    }

    /* fn_1_2BEC's common tail selects this small stage flourish only for a
     * non-draw result above 49 points with a human on the winning pair. */
    if (obj->work[0] >= 1009 && M529Winner != 2
        && (M529TeamScore[0] > 49 || M529TeamScore[1] > 49)) {
        s32 firstPlayer = M529Winner * 2;
        M529_PLAYER *first = M529PlayerObj[firstPlayer]->data;
        M529_PLAYER *second = M529PlayerObj[firstPlayer + 1]->data;

        if (GwPlayerConf[first->playerNo].type == GW_TYPE_MAN
            || GwPlayerConf[second->playerNo].type == GW_TYPE_MAN) {
            M529StageJointMotionUpdate();
        }
    }
}
