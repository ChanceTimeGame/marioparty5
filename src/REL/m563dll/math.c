/*
 * Helper set shared by m563.c and util.c. Both objects carry their own copy
 * (and their own copies of these globals), so everything here is static and
 * the file is included at the top of each unit, like m507's math.c. The
 * function names follow m563.c's reference addresses; util.c's copies sit at
 * fn_1_7A4C..fn_1_8930.
 */

#include <humath.h>
#include <math.h>

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/hsfex.h"
#include "game/hu3d.h"
#include "game/memory.h"

typedef struct M563MathNode_s {
    u16 id;
    s16 value;
    struct M563MathNode_s *prev;
    struct M563MathNode_s *next;
} M563_MATH_NODE;

typedef struct M563MathModel_s {
    u32 dataNum;
    HU3DMODELID mdlId;
} M563_MATH_MODEL;

static M563_MATH_MODEL mathModelCache[32];
static BOOL mathCamMoveF;
static int mathMusicNo;
static HuVecF mathCamTargetEnd[4];
static HuVecF mathCamTargetStart[4];
static HuVecF mathCamPosEnd[4];
static HuVecF mathCamPosStart[4];
static HuVecF mathCamTargetEnd1;
static HuVecF mathCamTargetStart1;
static HuVecF mathCamPosEnd1;
static HuVecF mathCamPosStart1;
static M563_MATH_NODE mathListHead;

static void fn_1_66D4(void)
{
    mathListHead.prev = NULL;
    mathListHead.next = NULL;
}

static void fn_1_66F8(u16 id, s16 value)
{
    M563_MATH_NODE *node;
    M563_MATH_NODE *head;
    M563_MATH_NODE *next;

    node = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M563_MATH_NODE), HU_MEMNUM_OVL);
    node->id = id;
    node->value = value;
    head = &mathListHead;
    next = head->next;
    head->next = node;
    if (NULL != next) {
        next->prev = node;
    }
    node->prev = head;
    node->next = next;
}

static s16 fn_1_6780(s16 id)
{
    M563_MATH_NODE *node;
    M563_MATH_NODE *next;
    M563_MATH_NODE *prev;
    s16 value;

    node = mathListHead.next;
    while (NULL != node) {
        if (id == node->id) {
            value = node->value;
            prev = node->prev;
            next = node->next;
            prev->next = next;
            if (NULL != next) {
                next->prev = prev;
            }
            HuMemDirectFree(node);
            return value;
        }
        node = node->next;
    }
    return -1;
}

static void fn_1_6824(void)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        mathModelCache[i].dataNum = 0;
        mathModelCache[i].mdlId = -1;
    }
}

static s16 fn_1_687C(u32 dataNum)
{
    s32 i;

    for (i = 0; i < 32; i++) {
        if (dataNum == mathModelCache[i].dataNum) {
            return Hu3DModelLink(mathModelCache[i].mdlId);
        }
    }
    for (i = 0; i < 32; i++) {
        if (mathModelCache[i].dataNum == 0) {
            mathModelCache[i].dataNum = dataNum;
            mathModelCache[i].mdlId = Hu3DModelCreateData(dataNum);
            return mathModelCache[i].mdlId;
        }
    }
    return Hu3DModelCreateData(dataNum);
}

static void fn_1_6990(float t, HuVecF *a, HuVecF *b, HuVecF *out)
{
    float weight;

    if (1.0f < t) {
        t = 1.0f;
    }
    weight = HuSin(90.0f * t) * HuSin(90.0f * t);
    out->x = a->x + (weight * (b->x - a->x));
    out->y = a->y + (weight * (b->y - a->y));
    out->z = a->z + (weight * (b->z - a->z));
}

static void fn_1_6AEC(HuVecF *pos, HuVecF *up, HuVecF *target)
{
    Hu3DCameraPosSetV(1, pos, up, target);
    mathCamPosStart1 = *pos;
    mathCamTargetStart1 = *target;
}

static s32 fn_1_6B78(float t, HuVecF *up)
{
    HuVecF pos;
    HuVecF target;
    float posT;
    float targetT;
    float posWeight;
    float targetWeight;

    posT = t;
    if (1.0f < posT) {
        posT = 1.0f;
    }
    posWeight = HuSin(90.0f * posT) * HuSin(90.0f * posT);
    pos.x = mathCamPosStart1.x + (posWeight * (mathCamPosEnd1.x - mathCamPosStart1.x));
    pos.y = mathCamPosStart1.y + (posWeight * (mathCamPosEnd1.y - mathCamPosStart1.y));
    pos.z = mathCamPosStart1.z + (posWeight * (mathCamPosEnd1.z - mathCamPosStart1.z));
    targetT = t;
    if (1.0f < targetT) {
        targetT = 1.0f;
    }
    targetWeight = HuSin(90.0f * targetT) * HuSin(90.0f * targetT);
    target.x = mathCamTargetStart1.x + (targetWeight * (mathCamTargetEnd1.x - mathCamTargetStart1.x));
    target.y = mathCamTargetStart1.y + (targetWeight * (mathCamTargetEnd1.y - mathCamTargetStart1.y));
    target.z = mathCamTargetStart1.z + (targetWeight * (mathCamTargetEnd1.z - mathCamTargetStart1.z));
    Hu3DCameraPosSetV(1, &pos, up, &target);
    if (1.0f <= t) {
        return 1;
    }
    mathCamMoveF = TRUE;
    return 0;
}

static s32 fn_1_6EAC(float t, HuVecF *up)
{
    HuVecF pos;
    HuVecF target;
    s32 i;
    float posT;
    float targetT;
    float posWeight;
    float targetWeight;

    for (i = 0; i < 4; i++) {
        posT = t;
        if (1.0f < posT) {
            posT = 1.0f;
        }
        posWeight = HuSin(90.0f * posT) * HuSin(90.0f * posT);
        pos.x = mathCamPosStart[i].x + (posWeight * (mathCamPosEnd[i].x - mathCamPosStart[i].x));
        pos.y = mathCamPosStart[i].y + (posWeight * (mathCamPosEnd[i].y - mathCamPosStart[i].y));
        pos.z = mathCamPosStart[i].z + (posWeight * (mathCamPosEnd[i].z - mathCamPosStart[i].z));
        targetT = t;
        if (1.0f < targetT) {
            targetT = 1.0f;
        }
        targetWeight = HuSin(90.0f * targetT) * HuSin(90.0f * targetT);
        target.x = mathCamTargetStart[i].x + (targetWeight * (mathCamTargetEnd[i].x - mathCamTargetStart[i].x));
        target.y = mathCamTargetStart[i].y + (targetWeight * (mathCamTargetEnd[i].y - mathCamTargetStart[i].y));
        target.z = mathCamTargetStart[i].z + (targetWeight * (mathCamTargetEnd[i].z - mathCamTargetStart[i].z));
        Hu3DCameraPosSetV(1 << i, &pos, up, &target);
    }
    if (1.0f <= t) {
        return 1;
    }
    mathCamMoveF = TRUE;
    return 0;
}

static float fn_1_7290(float angle, float target, float rate)
{
    float delta;
    float result;

    delta = fmod(target - angle, 360.0);
    if (0.0f > delta) {
        delta += 360.0f;
    }
    if (180.0f < delta) {
        delta -= 360.0f;
    }
    result = fmod(angle + (delta * rate), 360.0);
    if (0.0f > result) {
        result += 360.0f;
    }
    return result;
}

static void fn_1_7394(s32 speed)
{
    if (mathMusicNo >= 0) {
        if (speed < 0) {
            speed = 1000;
        }
        HuAudSeqFadeOut(mathMusicNo, speed);
    }
    mathMusicNo = -1;
}

static void fn_1_7400(s16 mdlId, char *objName, HuVecF *out)
{
    Mtx mtx;

    Hu3DModelObjMtxGet(mdlId, objName, mtx);
    out->x = mtx[0][3];
    out->y = mtx[1][3];
    out->z = mtx[2][3];
}

static u32 fn_1_7458(u32 min, u32 max)
{
    return min + frandmod(max - min);
}

static s32 fn_1_7494(HuVecF *a, HuVecF *b, float radiusA, float radiusB)
{
    if ((((b->x - a->x) * (b->x - a->x)) + ((b->z - a->z) * (b->z - a->z))) < ((radiusA + radiusB) * (radiusA + radiusB))) {
        return 1;
    }
    return 0;
}

static s32 fn_1_74F4(HuVecF *pos, s32 min, s32 max)
{
    HuVecF screen;
    s32 value;

    Hu3D3Dto2D(pos, 1, &screen);
    value = min + ((screen.x / 576.0f) * (max - min));
    return value;
}

static s32 fn_1_75B8(HuVecF *pos, s32 min, s32 max)
{
    HuVecF screen;
    s32 value;

    Hu3D3Dto2D(pos, 1, &screen);
    value = min + ((screen.y / 480.0f) * (max - min));
    return value;
}
