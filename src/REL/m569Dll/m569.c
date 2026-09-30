/*
 * m569dll m569.c (fork A) -- the seqman hooks of this 1VS3 minigame (#80), two
 * shared screen-pan helpers (m564's fn_1_1448/14D0), and the REL/mgframe.h
 * framework compiled in as m523dll and m564dll do. Functions are in reference
 * order; definition order decides inlining.
 *
 * map.txt renames each framework name to its reference label (fn_1_1148
 * MgObjManInit .. fn_1_3900 MgPlaneCrossGet; MgCameraMoveEntry, MgFlowSet and
 * MgFlowNext keep their names).
 */

#include "REL/m569dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "datadir_enum.h"

#include "math.h"

/* --- .data --- */

/* the framework's OSReport strings (.data:0x0..0x6C) */
#define MGF_S_DATA
#include "REL/mgframe.h"

/* 0x6C: the camera; fn_1_110 derives lbl_1_bss_34 from it, fn_1_820 moves it there. */
MGF_CAMERAVIEW lbl_1_data_6C = {
    1, 1, 0.0f, 0.0f, 0.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 100.0f, -800.0f }, { -10.0f, 0.0f, 0.0f }, 900.0f
};
/* Hu3DShadowPosSet position, up and target. */
HuVecF lbl_1_data_B4 = { 0.0f, 2500.0f, 100.0f };
HuVecF lbl_1_data_C0 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_CC = { 0.0f, 0.0f, 0.0f };
/* stage model positions (fn_1_110); score reads them too */
HuVecF lbl_1_data_D8[5] = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -350.0f, 450.0f, -200.0f }, { 350.0f, 450.0f, -200.0f }, { 0.0f, 0.0f, 0.0f } };
/* 0x114 */ MGSEQ_PARAM lbl_1_data_114 = { 0, 0, fn_1_110, fn_1_820, NULL, fn_1_9C4, fn_1_DD0, fn_1_E20, fn_1_FA8, NULL, fn_1_1010 };
/* 0x13C */ char lbl_1_data_13C[] = "inf_light1";

/* --- .rodata tables --- */
const s32 lbl_1_rodata_8C[5] = {
    DATANUM(DATA_m569, 0x00), DATANUM(DATA_m569, 0x01), DATANUM(DATA_m569, 0x02),
    DATANUM(DATA_m569, 0x03), DATANUM(DATA_m569, 0x04)
};

/*
 * --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) ---
 *
 * The framework's three .bss objects are declared by hand, not through
 * MGF_S_BSS (as m564): DebugCameraStart 0x88, MgMusicId 0xD0, objman 0xD4.
 */
OMOBJ **lbl_1_bss_F8;               /* the four player objects (player fn_1_3A48); dtk sizes it 8 (.bss tail pad to 0x100) */
M569_ROUND lbl_1_bss_D8[2];         /* per-round result (fn_1_9C4) */
OMOBJMAN *objman;                   /* bss_D4 */
static s16 MgMusicId;               /* bss_D0 */
static MGF_CAMERAVIEW DebugCameraStart; /* bss_88 */
HU3DMODELID lbl_1_bss_7C[6];        /* stage models (five used) */
MGF_CAMERAVIEW lbl_1_bss_34;        /* the view derived from the Hu3D camera; the fade-in move target */
MGF_STAGELIGHT lbl_1_bss_18;        /* "inf_light1" (Hu3DGLightParamGet) */
int lbl_1_bss_14;                   /* game phase */
MGTIMER *lbl_1_bss_10;              /* the game timer */
M569_KURIBO *lbl_1_bss_C;           /* fn_1_582C */
s16 lbl_1_bss_8;                    /* HuAudJinglePlay id */
int lbl_1_bss_4;                    /* fn_1_9C4 frame counter */
OMOBJ *lbl_1_bss_0;                 /* camera-move object */

/* --- the framework helpers the game code inlines, so defined first (as m523) --- */
#define MGF_S_CAMERAMOVECHECK
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"

/* --- functions (reference order) --- */
/* ObjectSetup (28 insns): MgObjManInit inlined, then the sequence manager. */
void ObjectSetup(void)
{
    MgObjManInit();
    MgSeqCreate(&lbl_1_data_114);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_94C);
}

/* fn_1_110 (452 insns) MGSEQ init hook: stage, camera, light, shadow, actors. */
void fn_1_110(s16 mode, s16 frameNo)
{
    int i;
    int k;
    int j;
    HU3DLIGHTID lightId;
    float dz, dy, dx;
    float magSq;
    float angle;
    float ty, tx, tz;
    float mtx[4][4];

    for (i = 0; i < 5; i++) {
        lbl_1_bss_7C[i] = Hu3DModelCreateData(lbl_1_rodata_8C[i]);
        Hu3DModelLayerSet(lbl_1_bss_7C[i], 0);
        Hu3DModelPosSetV(lbl_1_bss_7C[i], &lbl_1_data_D8[i]);
        Hu3DModelRotSet(lbl_1_bss_7C[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelAttrSet(lbl_1_bss_7C[i], HU3D_MOTATTR_LOOP);
    }
    Hu3DCameraCreate(lbl_1_data_6C.no);
    Hu3DCameraViewportSet(lbl_1_data_6C.no, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DModelCameraInfoSet(lbl_1_bss_7C[0], lbl_1_data_6C.no);
    Hu3DCameraPerspectiveGet(lbl_1_data_6C.no, &lbl_1_data_6C.fov, &lbl_1_data_6C.near, &lbl_1_data_6C.far);
    lbl_1_bss_34 = lbl_1_data_6C;
    Hu3DCameraPosGet(lbl_1_bss_34.no, &lbl_1_bss_34.pos, &lbl_1_bss_34.up, &lbl_1_bss_34.target);
    dx = lbl_1_bss_34.pos.x - lbl_1_bss_34.target.x;
    dy = lbl_1_bss_34.pos.y - lbl_1_bss_34.target.y;
    dz = lbl_1_bss_34.pos.z - lbl_1_bss_34.target.z;
    magSq = (dz * dz) + ((dx * dx) + (dy * dy));
    lbl_1_bss_34.dist = sqrtf(magSq);
    angle = (atan2(dz, dx) / M_PI) * 180.0;
    lbl_1_bss_34.angle.y = -(angle - 90.0f);
    for (j = 0; j < 4; j++) {
        for (k = 0; k < 4; k++) {
            mtx[j][k] = 0.0f;
        }
    }
    mtx[0][0] = mtx[2][2] = cos(M_PI * -angle / 180.0);
    mtx[2][0] = -sin(M_PI * -angle / 180.0);
    mtx[0][2] = sin(M_PI * -angle / 180.0);
    mtx[1][1] = mtx[3][3] = 1.0f;
    tx = (dz * mtx[2][0]) + ((dx * mtx[0][0]) + (dy * mtx[1][0]));
    ty = (dz * mtx[2][1]) + ((dx * mtx[0][1]) + (dy * mtx[1][1]));
    tz = (dz * mtx[2][3]) + ((dx * mtx[0][3]) + (dy * mtx[1][3])); /* retail: column 3, not 2; tz is dead */
    lbl_1_bss_34.angle.x = -((atan2(ty, tx) / M_PI) * 180.0);
    lbl_1_bss_34.angle.z = 0.0f;
    MgCameraViewSet(&lbl_1_data_6C);

    Hu3DModelLightInfoSet(lbl_1_bss_7C[0], 1);
    lightId = Hu3DModelLightIdGet(lbl_1_bss_7C[0], lbl_1_data_13C);
    Hu3DGLightParamGet(lightId, &lbl_1_bss_18.pos, &lbl_1_bss_18.target, &lbl_1_bss_18.color);
    Hu3DShadowCreate(lbl_1_data_6C.fov, lbl_1_data_6C.near, lbl_1_data_6C.far);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_data_B4, &lbl_1_data_C0, &lbl_1_data_CC);
    Hu3DModelShadowMapSet(lbl_1_bss_7C[0]);
    fn_1_3A48();
    lbl_1_bss_C = fn_1_582C();
    fn_1_6DB4();
    fn_1_80AC();
    lbl_1_bss_14 = 0;
    lbl_1_bss_8 = -1;
    fn_1_9B2C();
    MgSeqModeNext();
}

/* fn_1_820 (75 insns) MGSEQ fade-in hook: the jingle, then the camera move phase 1/2 asks for. */
void fn_1_820(s16 mode, s16 frameNo)
{
    int i;
    OMOBJ *obj;

    if (frameNo == 0) {
        fn_1_74B0();
        lbl_1_bss_8 = HuAudJinglePlay(0x88);
    }
    switch (lbl_1_bss_14) {
        case 1:
            if (lbl_1_bss_0 == NULL) {
                lbl_1_bss_0 = MgCameraMoveEntry(&lbl_1_data_6C, &lbl_1_bss_34, 90.0f);
            }
            break;
        case 2:
            if (lbl_1_bss_0 != NULL) {
                obj = lbl_1_bss_0;
                omDelObjEx(objman, obj);
                for (i = 0; i < 4; i++) {
                    fn_1_4EB4(i, 1);
                }
                lbl_1_bss_0 = NULL;
            }
            break;
    }
}

/* fn_1_94C (30 insns) MGSEQ_MODE_PREMAIN hook added by ObjectSetup: score, 10 s timer, phase 3. */
void fn_1_94C(s16 mode, s16 frameNo)
{
    fn_1_87D4();
    lbl_1_bss_10 = MgTimerCreate(MGTIMER_TYPE_NORMAL);
    MgTimerParamSet(lbl_1_bss_10, 600, 0, 0);
    MgTimerModeOnSet(lbl_1_bss_10, MGTIMER_OFFTYPE_FADEOUT);
    fn_1_80FC();
    lbl_1_bss_14 = 3;
}

/* fn_1_9C4 (259 insns) MGSEQ main hook: two rounds of phases 3..7 / 8..12. */
void fn_1_9C4(s16 mode, s16 frameNo)
{
    int i;
    int round;
    int done;
    int n;

    if (lbl_1_bss_14 >= 3 && lbl_1_bss_14 <= 6) {
        round = 0;
    } else {
        round = 1;
    }
    switch (lbl_1_bss_14) {
        case 3:
        case 8:
            if (fn_1_8544()) {
                for (i = 0; i < 3; i++) {
                    if (lbl_1_bss_D8[round].unk004[i] != -1) {
                        fn_1_4EB4(lbl_1_bss_D8[round].unk004[i], 2);
                    }
                }
                lbl_1_bss_14++;
            }
            break;
        case 4:
        case 9:
            if (MgTimerDoneCheck(lbl_1_bss_10)) {
                fn_1_8614();
                lbl_1_bss_14++;
            } else if (fn_1_85C0()) {
                if (lbl_1_bss_10->stopF == 0) {
                    lbl_1_bss_10->stopF = TRUE;
                    lbl_1_bss_10->mode = MGTIMER_MODE_ON;
                }
                lbl_1_bss_14++;
            }
            break;
        case 5:
        case 10:
            lbl_1_bss_4++;
            if (lbl_1_bss_4 == 90) {
                lbl_1_bss_D8[round].unk000 = fn_1_86C4();
                fn_1_8A74(round, fn_1_86C4());
            } else if (lbl_1_bss_4 > 90) {
                if (fn_1_8AAC(round)) {
                    fn_1_833C();
                    lbl_1_bss_4 = 0;
                    lbl_1_bss_14++;
                    fn_1_54A8(round);
                    if (lbl_1_bss_D8[round].unk000 > 0) {
                        fn_1_6D9C(lbl_1_bss_C);
                        fn_1_74B0();
                        fn_1_735C();
                    }
                }
            }
            break;
        case 6:
        case 11:
            lbl_1_bss_4++;
            if (lbl_1_bss_4 == 120) {
                lbl_1_bss_4 = 0;
                lbl_1_bss_14++;
            }
            break;
        case 7:
            if (lbl_1_bss_4++ == 0) {
                fn_1_4F14(lbl_1_bss_D8[0].unk004[0]);
                for (i = 0; i < 3; i++) {
                    fn_1_5138(lbl_1_bss_D8[1].unk004[i]);
                }
            } else {
                done = TRUE;
                for (i = 0; i < 4; i++) {
                    if (fn_1_4EE4(i)) {
                        done = FALSE;
                    }
                }
                if (done) {
                    MgTimerParamSet(lbl_1_bss_10, 600, 0, 0);
                    MgTimerModeOnSet(lbl_1_bss_10, MGTIMER_OFFTYPE_FADEOUT);
                    fn_1_80FC();
                    lbl_1_bss_4 = 0;
                    lbl_1_bss_14 = 8;
                }
            }
            break;
        case 12:
            MgSeqModeNext();
            break;
    }
}

/* fn_1_DD0 (20 insns) MGSEQ finish hook. */
void fn_1_DD0(s16 mode, s16 frameNo)
{
    int i;

    if (frameNo == 30) {
        for (i = 0; i < 4; i++) {
            fn_1_52F8(i);
        }
    }
}

/* fn_1_E20 (98 insns) MGSEQ pre-winner hook: result jingle and win/lose motions. */
void fn_1_E20(s16 mode, s16 frameNo)
{
    int i;
    M569_PLAYER *work;
    int win;

    if (frameNo == 0) {
        fn_1_8ADC();
    }
    if (frameNo == 70) {
        if (lbl_1_bss_D8[0].unk000 != 0 || lbl_1_bss_D8[1].unk000 != 0) {
            win = FALSE;
            HuAudJinglePlay(0x79);
        } else {
            win = TRUE;
            HuAudJinglePlay(0x7B);
        }
        for (i = 0; i < 4; i++) {
            work = lbl_1_bss_F8[i]->data;
            if (work->unk04C != 0) {
                fn_1_4B8C(lbl_1_bss_F8[i], 4);
            } else {
                if (win) {
                    work->unk06C = 1;
                } else {
                    work->unk06C = 0;
                }
                fn_1_4B8C(lbl_1_bss_F8[i], 5);
            }
        }
    }
    if (frameNo >= 60) {
        if (frameNo == 60) {
            fn_1_74B0();
            fn_1_741C();
        }
        if (lbl_1_bss_D8[0].unk000 != 0 || lbl_1_bss_D8[1].unk000 != 0) {
            fn_1_6D9C(lbl_1_bss_C);
        }
    }
}

/* fn_1_FA8 (26 insns) MGSEQ winner hook. */
void fn_1_FA8(s16 mode, s16 frameNo)
{
    if (lbl_1_bss_D8[0].unk000 != 0 || lbl_1_bss_D8[1].unk000 != 0) {
        fn_1_6D9C(lbl_1_bss_C);
    }
    if (frameNo == 40) {
        MgSeqModeNext();
    }
}

/* fn_1_1010 (1 insn) MGSEQ close hook. */
void fn_1_1010(s16 mode, s16 frameNo)
{
}

s16 fn_1_1014(HuVecF *pos)
{
    HuVecF screen;
    s16 pan;

    Hu3D3Dto2D(pos, (s16)lbl_1_bss_34.no, &screen);
    pan = 32 + (64.0f * (screen.x / 576.0f));
    return pan;
}

/* fn_1_109C (43 insns) = m564 fn_1_14D0 (m570 M570SePlay): play a sound panned to a position. */
void fn_1_109C(HuVecF *pos, s16 seNo)
{
    HuAudFXPlayPan(seNo, fn_1_1014(pos));
}

/*
 * ===========================================================================
 * The framework, from REL/mgframe.h, in m523dll's include order.
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
