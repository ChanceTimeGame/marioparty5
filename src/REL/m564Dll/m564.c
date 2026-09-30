/*
 * m564dll m564.c (fork A) -- the seqman hooks and shared helpers of this 4P
 * bomb minigame, plus the REL/mgframe.h framework compiled in as m523dll does.
 * Functions are in reference order; definition order decides inlining.
 *
 * All 18 game functions are raw-identical to the reference. The framework's
 * .bss (DebugCameraStart, MgMusicId, objman) is declared by hand rather than
 * through MGF_S_BSS so that .bss lands at the reference addresses.
 */

#include "REL/m564Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "game/mg/actman.h"
#include "game/flag.h"
#include "datadir_enum.h"

#include "math.h"

/* .rodata is the literal pool plus lbl_1_rodata_8C (list/m564.rodata.txt). */

/* --- .data --- */

/* the framework's OSReport strings (.data:0x0..0x6C) */
#define MGF_S_DATA
#include "REL/mgframe.h"

/* 0x6C: the live camera view (MgCameraViewSet, moved by fn_1_9FC toward bss_44). */
MGF_CAMERAVIEW lbl_1_data_6C = {
    1, 1, 20.0f, 20.0f, 5000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { -170.0f, 165.0f, 70.0f }, { -15.0f, 0.0f, 0.0f }, 311.0f
};

/* Hu3DShadowPosSet position, up and target; data_D8 is read by bomb and com. */
HuVecF lbl_1_data_B4 = { 0.0f, 4000.0f, 1.0f };
HuVecF lbl_1_data_C0 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_CC = { 0.0f, 0.0f, 0.0f };
HuVecF lbl_1_data_D8 = { 0.0f, 0.0f, 0.0f };
/* 0xE4 */ MGSEQ_PARAM lbl_1_data_E4 = { 60, MGSEQ_TIMER_TOP, fn_1_EC, fn_1_9FC, fn_1_C50, fn_1_C98, fn_1_D00, fn_1_F24, fn_1_FEC, NULL, fn_1_10F0 };
/* 0x10C */ char lbl_1_data_10C[] = "inf_light1";

/* --- .rodata tables --- */
const s32 lbl_1_rodata_8C[16] = {
    DATANUM(DATA_m564, 0x02), DATANUM(DATA_m564, 0x03), DATANUM(DATA_m564, 0x04), DATANUM(DATA_m564, 0x00),
    DATANUM(DATA_m564, 0x01), DATANUM(DATA_m564, 0x05), DATANUM(DATA_m564, 0x06), DATANUM(DATA_m564, 0x07),
    DATANUM(DATA_m564, 0x08), DATANUM(DATA_m564, 0x09), DATANUM(DATA_m564, 0x0A), DATANUM(DATA_m564, 0x0B),
    DATANUM(DATA_m564, 0x0C), DATANUM(DATA_m564, 0x0D), DATANUM(DATA_m564, 0x0E), DATANUM(DATA_m564, 0x0F)
};

/*
 * --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) ---
 *
 * The framework's three .bss objects are declared here by hand instead of
 * through mgframe.h's MGF_S_BSS: that section declares DebugCameraStart,
 * MgMusicId, objman in that order, and reverse emission would then put objman
 * lowest. The reference has DebugCameraStart at 0xAC, MgMusicId at 0xF4 and
 * objman at 0xF8. (m523.o carries the reversed layout; it never matched .bss.)
 */
M564_PLAYER *lbl_1_bss_100[4];   /* the four player works (player fn_1_3E7C) */
s32 lbl_1_bss_FC;                /* unreferenced; dtk sized objman 8 to cover it */
OMOBJMAN *objman;                /* bss_F8 (MGF_LINK_OBJMAN is external here) */
static s16 MgMusicId;            /* bss_F4 */
static MGF_CAMERAVIEW DebugCameraStart; /* bss_AC */
HU3DMODELID lbl_1_bss_8C[16];    /* stage models from lbl_1_rodata_8C */
MGF_CAMERAVIEW lbl_1_bss_44;     /* angle-mode view fn_1_EC derives from the Hu3D camera; the move target */
MGF_STAGELIGHT lbl_1_bss_28;     /* the "inf_light1" parameters (Hu3DGLightParamGet) */
int lbl_1_bss_24;                /* game phase, read by player/bomb */
int lbl_1_bss_20;                /* set by fn_1_F24 when nobody lost */
s16 lbl_1_bss_C[10];             /* [0] HuAudBGMPlay id; dtk sizes it 0x14 */
int lbl_1_bss_8;                 /* fn_1_D00 finish step */
OMOBJ *lbl_1_bss_4;              /* camera-move object */
int lbl_1_bss_0;                 /* fn_1_9FC fade-in step */

/* --- the framework helpers the game code inlines, so defined first (as m523) --- */
#define MGF_S_CAMERAMOVECHECK
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"

/* --- functions (reference order) --- */
/* ObjectSetup (m564, 19 insns) */
void ObjectSetup(void)
{
    objman = MgActorObjectSetup();
    MgSeqCreatePrio(&lbl_1_data_E4, 2000);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_C3C);
}

/* fn_1_EC (m564, 580 insns) MGSEQ init hook: stage, collision, camera, light, shadow, players and bombs. */
void fn_1_EC(s16 mode, s16 frameNo)
{
    int i;
    int k;
    int j;
    HU3DLIGHTID lightId;
    float rotY;
    float dz, dy, dx;
    float magSq;
    float angle;
    float ty, tx, tz;
    HU3DMODELID colMdl[3];
    float mtx[4][4];

    for (i = 0; i < 16; i++) {
        lbl_1_bss_8C[i] = Hu3DModelCreateData(lbl_1_rodata_8C[i]);
        Hu3DModelAttrSet(lbl_1_bss_8C[i], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_8C[i], HU3D_MOTATTR_LOOP);
        Hu3DModelLayerSet(lbl_1_bss_8C[i], 0);
        Hu3DModelPosSet(lbl_1_bss_8C[i], 0.0f, 0.0f, 0.0f);
        if (i >= 6 && i <= 15) {
            rotY = -(18.0f + 36.0f * (i - 6));
            Hu3DModelRotSet(lbl_1_bss_8C[i], 0.0f, rotY, 0.0f);
            Hu3DModelAttrReset(lbl_1_bss_8C[i], HU3D_MOTATTR_LOOP);
        } else {
            Hu3DModelRotSet(lbl_1_bss_8C[i], 0.0f, 0.0f, 0.0f);
        }
    }
    Hu3DModelLayerSet(lbl_1_bss_8C[5], 4);
    Hu3DModelAttrReset(lbl_1_bss_8C[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelPosSet(lbl_1_bss_8C[5], 496.0f, 320.0f, 425.0f);
    for (i = 0; i < 3; i++) {
        colMdl[i] = lbl_1_bss_8C[i];
        Hu3DModelAttrSet(lbl_1_bss_8C[i], HU3D_ATTR_DISPOFF);
    }
    MgActorColMapInit(colMdl, 3, 19);
    MgActorColMapMaskSet(0, 1);
    MgActorColMapMaskSet(1, 2);
    MgActorColMapMaskSet(2, 4);

    Hu3DCameraCreate(lbl_1_data_6C.no);
    Hu3DCameraViewportSet(lbl_1_data_6C.no, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DModelCameraInfoSet(lbl_1_bss_8C[3], lbl_1_data_6C.no);
    Hu3DCameraPerspectiveGet(lbl_1_data_6C.no, &lbl_1_data_6C.fov, &lbl_1_data_6C.near, &lbl_1_data_6C.far);
    lbl_1_bss_44 = lbl_1_data_6C;
    Hu3DCameraPosGet(lbl_1_bss_44.no, &lbl_1_bss_44.pos, &lbl_1_bss_44.up, &lbl_1_bss_44.target);
    dx = lbl_1_bss_44.pos.x - lbl_1_bss_44.target.x;
    dy = lbl_1_bss_44.pos.y - lbl_1_bss_44.target.y;
    dz = lbl_1_bss_44.pos.z - lbl_1_bss_44.target.z;
    magSq = dx * dx + dy * dy + dz * dz;
    lbl_1_bss_44.dist = sqrtf(magSq);
    angle = (atan2(dz, dx) / M_PI) * 180.0;
    lbl_1_bss_44.angle.y = -(angle - 90.0f);
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            mtx[j][k] = 0.0f;
        }
    }
    mtx[0][0] = mtx[2][2] = cos(M_PI * -angle / 180.0);
    mtx[2][0] = -sin(M_PI * -angle / 180.0);
    mtx[0][2] = sin(M_PI * -angle / 180.0);
    mtx[1][1] = mtx[3][3] = 1.0f;
    tx = dx * mtx[0][0] + dy * mtx[1][0] + dz * mtx[2][0];
    ty = dx * mtx[0][1] + dy * mtx[1][1] + dz * mtx[2][1];
    tz = dx * mtx[0][3] + dy * mtx[1][3] + dz * mtx[2][3]; /* retail: column 3, not 2; tz is dead */
    lbl_1_bss_44.angle.x = -((atan2(ty, tx) / M_PI) * 180.0);
    lbl_1_bss_44.angle.z = 0.0f;
    MgCameraViewSet(&lbl_1_data_6C);

    Hu3DModelLightInfoSet(lbl_1_bss_8C[3], 1);
    lightId = Hu3DModelLightIdGet(lbl_1_bss_8C[3], lbl_1_data_10C);
    Hu3DGLightParamGet(lightId, &lbl_1_bss_28.pos, &lbl_1_bss_28.target, &lbl_1_bss_28.color);
    Hu3DShadowCreate(lbl_1_bss_44.fov, lbl_1_bss_44.near, lbl_1_bss_44.far);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_data_B4, &lbl_1_data_C0, &lbl_1_data_CC);
    for (i = 3; i <= 15; i++) {
        Hu3DModelShadowMapSet(lbl_1_bss_8C[i]);
    }
    fn_1_3E7C();
    fn_1_60E8();
    fn_1_6858();
    omAddObjEx(objman, 0x1300, 0, 0, OM_GRP_NONE, fn_1_10F4);
    lbl_1_bss_24 = 0;
    MgSeqModeNext();
}

/* fn_1_9FC (m564, 144 insns) MGSEQ fade-in hook: camera sweep in, then wait for the bombs. */
void fn_1_9FC(s16 mode, s16 frameNo)
{
    int i;
    OMOBJ *obj;

    lbl_1_bss_24 = 1;
    switch (lbl_1_bss_0) {
        case 0:
            if (frameNo == 10) {
                HuAudFXPlay(0x2D7);
            }
            if (frameNo == 60) {
                lbl_1_bss_4 = MgCameraMoveEntry(&lbl_1_data_6C, &lbl_1_bss_44, 60.0f);
                lbl_1_bss_100[0]->mode = 1;
                lbl_1_bss_0++;
            }
            break;
        case 1:
            lbl_1_bss_100[0]->mode = 1;
            if (!MgCameraMoveCheck(lbl_1_bss_4)) {
                obj = lbl_1_bss_4;
                omDelObjEx(objman, obj);
                lbl_1_bss_0++;
            }
            break;
        case 2:
            if (lbl_1_bss_1E8[0]->unk020 == 7) {
                fn_1_43E0(lbl_1_bss_100[1]->unk02C, 4);
                fn_1_43E0(lbl_1_bss_100[2]->unk02C, 4);
                fn_1_43E0(lbl_1_bss_100[3]->unk02C, 4);
                for (i = 0; i < 4; i++) {
                    omVibrate(lbl_1_bss_100[i]->no, 12, 12, 0);
                }
                lbl_1_bss_0++;
            }
            break;
        case 3:
            break;
    }
    if (frameNo == 150) {
        MgSeqModeNext();
    }
}

/* fn_1_C3C (m564, 5 insns) MGSEQ_MODE_PREMAIN hook added by ObjectSetup. */
void fn_1_C3C(s16 mode, s16 frameNo)
{
    lbl_1_bss_24 = 2;
}

/* fn_1_C50 (m564, 18 insns) MGSEQ start hook. */
void fn_1_C50(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_C[0] = HuAudBGMPlay(0x36);
    }
    fn_1_653C();
}

/* fn_1_C98 (m564, 26 insns) MGSEQ main hook: ends when three players are out. */
void fn_1_C98(s16 mode, s16 frameNo)
{
    int i;
    int num = 0;

    for (i = 0; i < 4; i++) {
        if (fn_1_5E5C(i)) {
            num++;
        }
    }
    if (num >= 3) {
        MgSeqModeNext();
    }
    fn_1_653C();
}

/* fn_1_D00 (m564, 137 insns) MGSEQ finish hook. */
void fn_1_D00(s16 mode, s16 frameNo)
{
    int i;
    int num;
    s16 charNo[4];

    if (frameNo == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_C[0], 100);
    }
    switch (lbl_1_bss_8) {
        case 0:
            lbl_1_bss_24 = 3;
            fn_1_8DEC();
            lbl_1_bss_8++;
            break;
        case 1:
            if (fn_1_8EC8()) {
                lbl_1_bss_8++;
            }
            break;
        case 2:
            num = 0;
            for (i = 0; i < 4; i++) {
                if (lbl_1_bss_100[i]->unk034 != 0) {
                    num++;
                    lbl_1_bss_100[i]->mode = 1;
                    lbl_1_bss_1E8[lbl_1_bss_100[i]->unk038]->unk058 = 1;
                }
            }
            if (num == 0) {
                lbl_1_bss_8++;
            }
            break;
        case 3:
            for (i = 0; i < 4; i++) {
                charNo[i] = CHARNO_NONE;
                if (!fn_1_5E5C(i)) {
                    fn_1_43E0(lbl_1_bss_100[i]->unk02C, 5);
                    charNo[i] = lbl_1_bss_100[i]->charNo;
                }
            }
            MgSeqWinnerSet(charNo[0], charNo[1], charNo[2], charNo[3]);
            break;
    }
}

/* fn_1_F24 (m564, 50 insns) MGSEQ pre-winner hook: winners' motion and coin bonus. */
void fn_1_F24(s16 mode, s16 frameNo)
{
    int i;

    if (frameNo == 30) {
        lbl_1_bss_20 = 1;
        for (i = 0; i < 4; i++) {
            if (!fn_1_5E5C(i)) {
                fn_1_4204(lbl_1_bss_100[i]->unk02C, 5);
                /* a direct mgCoinBonus (+0x2C) store, not GWMgCoinBonusSet; practice-guarded */
                if (!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[i].mgCoinBonus = 10;
                }
                lbl_1_bss_20 = 0;
            }
        }
        MgSeqModeNext();
    }
}

/* fn_1_FEC (m564, 65 insns) MGSEQ winner hook: with no winner, blow the remaining bombs. */
void fn_1_FEC(s16 mode, s16 frameNo)
{
    int i;

    if (lbl_1_bss_20 == 0) {
        if (frameNo == 0) {
            fn_1_8F6C();
        }
        if (frameNo == 100) {
            HuAudFXPlay(0x8D8);
            for (i = 0; i < 15; i++) {
                if (lbl_1_bss_1E8[i]->unk020 == 8) {
                    fn_1_7210(lbl_1_bss_1E8[i], 0);
                }
            }
            for (i = 0; i < 4; i++) {
                if (!fn_1_5E5C(i)) {
                    omVibrate(lbl_1_bss_100[i]->no, 12, 12, 0);
                }
            }
        }
    }
}

/* fn_1_10F0 (m564, 1 insns) MGSEQ close hook. */
void fn_1_10F0(s16 mode, s16 frameNo)
{
}

/* fn_1_10F4 (m564, 38 insns) Object created by fn_1_EC: actor exec, then the live players' rotation. */
void fn_1_10F4(OMOBJ *obj)
{
    int i;
    HU3DMODELID mdlId;

    MgActorExec();
    for (i = 0; i < 4; i++) {
        if (fn_1_5E5C(i)) {
            mdlId = lbl_1_bss_100[i]->unk02C->actor->mdlId;
            Hu3DModelRotSetV(mdlId, &lbl_1_bss_100[i]->rot);
        }
    }
}

/* fn_1_118C (m564, 82 insns) A random point on the xz ring [min, max) about center. */
void fn_1_118C(HuVecF *center, float min, float max, HuVecF *out)
{
    float angle;
    float dist;

    dist = min + (s32)frandmod((s32)(max - min));
    angle = (s32)frandmod(360);
    out->x = center->x + dist * cos(M_PI * angle / 180.0);
    out->z = center->z + dist * sin(M_PI * angle / 180.0);
}

/* fn_1_12D4 (m564, 25 insns) m523 fn_1_C88: yaw from a to b. */
float fn_1_12D4(HuVecF *a, HuVecF *b)
{
    HuVecF d;

    PSVECSubtract(b, a, &d);
    return (float)((atan2(d.x, d.z) / M_PI) * 180.0);
}

/* fn_1_1338 (m564, 27 insns) m523 fn_1_CEC: signed angle difference in (-180, 180]. */
float fn_1_1338(float a, float b)
{
    float d = b - a;

    if (d < -180.0f) {
        d += 360.0f;
    }
    if (d > 180.0f) {
        d = d - 360.0f;
    }
    return d;
}

/* fn_1_13A4 (m564, 19 insns) xz distance from a to b. */
float fn_1_13A4(HuVecF *a, HuVecF *b)
{
    HuVecF d;

    PSVECSubtract(b, a, &d);
    d.y = 0.0f;
    return PSVECMag(&d);
}

/* fn_1_13F0 (m564, 22 insns) xz vector from a to b into out; returns its length. */
float fn_1_13F0(HuVecF *a, HuVecF *b, HuVecF *out)
{
    PSVECSubtract(b, a, out);
    out->y = 0.0f;
    return PSVECMag(out);
}

/* fn_1_1448 (m564, 34 insns) m570 M570PanGet: stereo pan for a world position. Returns s16: an int return adds an extsh in fn_1_14D0. */
s16 fn_1_1448(HuVecF *pos)
{
    HuVecF screen;
    s16 pan;

    Hu3D3Dto2D(pos, (s16)lbl_1_bss_44.no, &screen);
    pan = 32 + (64.0f * (screen.x / 576.0f));
    return pan;
}

/* fn_1_14D0 (m564, 43 insns) m570 M570SePlay: play a sound panned to a position. */
void fn_1_14D0(HuVecF *pos, s16 seNo)
{
    HuAudFXPlayPan(seNo, fn_1_1448(pos));
}

/*
 * ===========================================================================
 * The framework, from REL/mgframe.h, in m523dll's include order. map.txt maps
 * each name to its reference label (fn_1_157C MgObjManInit .. fn_1_3D34
 * MgPlaneCrossGet; MgCameraMoveEntry, MgFlowSet and MgFlowNext keep their
 * names). Twelve of the 41 are not raw=0: the same twelve gaps m523.o, m524.o
 * and m570.o carry (see OUT.txt).
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
