/*
 * m523dll -- a 1-vs-3 minigame (MG_TYPE_1VS3, overlay #37). SKELETON (W1).
 *
 * Every game function below is an empty stub in reference order; the bodies
 * are W2 work. Do not reorder functions or includes: CodeWarrior inlines only
 * what it has already seen, so definition order decides the instruction
 * stream.
 *
 * Shape: the DOL sequence manager (MgSeqCreatePrio with lbl_1_data_1BC's nine
 * hooks) plus the REL/mgframe.h framework, included at the same points as
 * m570dll (also 1VS3). From fn_1_1014 to the end of this object the function
 * size sequence is identical to m570's, so the framework is not rewritten
 * here. When the assembly calls a framework address, write the framework name:
 *
 *   fn_1_1014 MgObjManInit        fn_1_2924 MgPadStkAngleGet
 *   fn_1_1068 MgCameraCreate      fn_1_2A34 MgFlowMain
 *   fn_1_1154 MgCameraViewSet     fn_1_2AE4 MgFlowExitWait
 *   fn_1_11A4 MgLightCreate       fn_1_2B1C MgFlowEntry
 *   fn_1_1200 MgDebugCameraMain   fn_1_2CBC MgFlowGet .. fn_1_2DD4 MgNop
 *   fn_1_1678 MgDebugCameraCreate fn_1_2DD8 MgFlowWipeWait .. fn_1_30D8 MgFlowTimerCreate
 *   fn_1_1724 MgDebugCameraStartSet fn_1_3178 MgPlayerConfSet
 *   fn_1_1754 MgCameraAngleApply  fn_1_3244 MgVecApproach
 *   fn_1_1E18 MgCameraAngleGet    fn_1_3368 MgAngleApproach
 *   fn_1_221C MgCameraMoveMain    fn_1_34D8 MgVecOrbit
 *   fn_1_2534 MgCameraMoveCheck   fn_1_3710 MgPlaneNormalGet
 *   fn_1_2568 MgCameraMoveKill    fn_1_3788 MgPlaneDistGet
 *   fn_1_259C MgCameraShakeMain   fn_1_37CC MgPlaneCrossGet
 *   fn_1_26E4 MgCameraShakeEntry  fn_1_27A0 MgPadStkMagGet
 *
 * .bss roles: bss_0/bss_4 are camera-move objects (their stat at data+0x9C is
 * MgCameraMoveCheck inlined); bss_44 is this overlay's own camera view,
 * copied from lbl_1_data_6C; bss_8C the stage models. bss_98
 * (DebugCameraStart), bss_E0 (MgMusicId) and bss_E4 (objman) are the
 * framework's.
 *
 * _prolog and _epilog are not reproduced: a port overlay is a host shared
 * library whose only export is ObjectSetup.
 */

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/mg/seqman.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/wipe.h"

#include "datadir_enum.h"

#include "REL/m523Dll.h"

#include "dolphin/os.h"

#include "math.h"
#include "humath.h"

/* --- .data --- */

/* the framework's OSReport strings (.data:0x0..0x6C) */
#define MGF_S_DATA
#include "REL/mgframe.h"

MGF_CAMERAVIEW lbl_1_data_6C = {
    1, 1, 20.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 190.0f, 72.0f }, { -20.0f, 0.0f, 0.0f }, 1000.0f
};

MGF_CAMERAVIEW lbl_1_data_B4 = {
    1, 1, 20.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 259.0f, 72.0f }, { -42.5f, 0.0f, 0.0f }, 4886.4f
};

MGF_CAMERAVIEW lbl_1_data_FC = {
    1, 1, 20.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 300.0f, 72.0f }, { -30.0f, 0.0f, 0.0f }, 2800.0f
};

MGF_CAMERAVIEW lbl_1_data_144 = {
    1, 1, 20.0f, 20.0f, 8000.0f,
    { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f },
    { 0.0f, 400.0f, 72.0f }, { -8.6f, 0.0f, 0.0f }, 2800.0f
};

/* Hu3DShadowPosSet position, up and target; data_1B0 is unreferenced. */
HuVecF lbl_1_data_18C = { 0.0f, 100000.0f, 1.0f };
HuVecF lbl_1_data_198 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_1A4 = { 0.0f, 0.0f, 0.0f };
HuVecF lbl_1_data_1B0 = { 0.0f, 0.0f, 0.0f };

MGSEQ_PARAM lbl_1_data_1BC = {
    30, MGSEQ_TIMER_RIGHT,
    fn_1_12C,
    fn_1_524,
    fn_1_634,
    fn_1_6CC,
    fn_1_714,
    fn_1_76C,
    fn_1_8C0,
    NULL,
    fn_1_8D4
};

/* Three stage prop positions; player.c reads them too. */
HuVecF lbl_1_data_1E4[3] = {
    { 0.0f, 0.0f, 600.0f },
    { -485.0f, 0.0f, -342.0f },
    { 570.0f, 0.0f, -120.0f },
};

/* --- .rodata tables --- */

/* files/data/m523.bin stage models (the archive carries no names). */
const s32 lbl_1_rodata_8C[5] = {
    DATANUM(DATA_m523, 0x00), DATANUM(DATA_m523, 0x01), DATANUM(DATA_m523, 0x02),
    DATANUM(DATA_m523, 0x05), DATANUM(DATA_m523, 0x03)
};

/*
 * fn_1_12C builds its stage light from a local MGF_STAGELIGHT whose
 * initializer is .rodata:0xA0: pos (-800, 1500, 800), target (800, -1500,
 * -800), color 255/255/255/255. Write it as a local, not a global.
 */

/* --- .bss --- */

OMOBJ *lbl_1_bss_0;
OMOBJ *lbl_1_bss_4;
int lbl_1_bss_8;
int lbl_1_bss_C;                 /* HuAudFXPlay id */
int lbl_1_bss_10;                /* HuAudSStreamPlay id */
int lbl_1_bss_14;
int lbl_1_bss_18;                /* game state, read by player.c */
int lbl_1_bss_1C;
int lbl_1_bss_20;
int lbl_1_bss_24;                /* dtk sizes this 0x20; only offset 0 is referenced */
MGF_CAMERAVIEW lbl_1_bss_44;
HU3DMODELID lbl_1_bss_8C[6];     /* five from lbl_1_rodata_8C */
/* DebugCameraStart (bss_98), MgMusicId (bss_E0) and objman (bss_E4) */
#define MGF_S_BSS
#include "REL/mgframe.h"

/* --- the framework helpers the game code inlines, so defined first (as m570) --- */
#define MGF_S_CAMERAMOVECHECK
#include "REL/mgframe.h"
#define MGF_S_OBJMAN
#include "REL/mgframe.h"

/* asm 61-97, 35 insns. MgObjManInit inlined, then the sequence manager. */
void ObjectSetup(void)
{
    MgObjManInit();
    MgSeqCreatePrio(&lbl_1_data_1BC, 2000);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_674);
    MgSeqModeDelaySet(MGSEQ_MODE_FADEIN, 300);
    MgSeqModeDelaySet(MGSEQ_MODE_PREWIN, 300);
}

/* asm 100-364, 254 insns. MGSEQ init hook: stage, camera, light, shadow, players. */
void fn_1_12C(s16 mode, s16 frameNo)
{
    int i;
    s16 id;
    s16 propId[3];

    for (i = 0; i < 5; i++) {
        lbl_1_bss_8C[i] = Hu3DModelCreateData(lbl_1_rodata_8C[i]);
        Hu3DModelAttrSet(lbl_1_bss_8C[i], HU3D_MOTATTR_LOOP);
        Hu3DModelPosSet(lbl_1_bss_8C[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelRotSet(lbl_1_bss_8C[i], 0.0f, 0.0f, 0.0f);
        Hu3DModelLayerSet(lbl_1_bss_8C[i], 0);
    }
    Hu3DModelLayerSet(lbl_1_bss_8C[1], 3);
    Hu3DMotionSpeedSet(lbl_1_bss_8C[3], 0.4f);

    id = Hu3DModelCreateData(DATANUM(DATA_m523, 0x04));
    for (i = 0; i < 3; i++) {
        if (i == 0) {
            propId[i] = id;
        } else {
            propId[i] = Hu3DModelLink(id);
        }
        Hu3DModelPosSetV(propId[i], &lbl_1_data_1E4[i]);
        Hu3DModelLayerSet(propId[i], 2);
    }

    MgCameraCreate(&lbl_1_data_6C);
    lbl_1_bss_44 = lbl_1_data_6C;

    {
        MGF_STAGELIGHT light = {
            { -800.0f, 1500.0f, 800.0f },
            { 800.0f, -1500.0f, -800.0f },
            { 255, 255, 255, 255 }
        };
        HU3DLIGHTID lightId = Hu3DGLightCreateV(&light.pos, &light.target, &light.color);
        Hu3DGLightStaticSet(lightId, 1);
        Hu3DGLightInfinitytSet(lightId);
    }
    Hu3DShadowCreate(1.0f, lbl_1_data_B4.near, 100000.0f);
    Hu3DShadowTPLvlSet(0.35f);
    Hu3DShadowPosSet(&lbl_1_data_18C, &lbl_1_data_198, &lbl_1_data_1A4);
    Hu3DModelShadowMapSet(lbl_1_bss_8C[0]);
    Hu3DModelShadowMapSet(lbl_1_bss_8C[1]);
    for (i = 0; i < 3; i++) {
        Hu3DModelShadowMapSet(propId[i]);
    }

    fn_1_39DC();
    lbl_1_bss_8 = -1;
    lbl_1_bss_24 = 10;
    lbl_1_bss_20 = 0;
    Hu3DModelAttrSet(lbl_1_bss_8C[0], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrReset(lbl_1_bss_8C[0], HU3D_MOTATTR_LOOP);
    omAddObjEx(objman, 0x1300, 0, 0, OM_GRP_NONE, fn_1_8E8);
    lbl_1_bss_C = HuAudFXPlay(0x751);
    lbl_1_bss_18 = 0;
    lbl_1_bss_14 = 0;
    MgSeqModeNext();
}

/* asm 367-442, 68 insns. MGSEQ fade-in hook. */
void fn_1_524(s16 mode, s16 frameNo)
{
    OMOBJ *obj;

    if (frameNo == 0x1E) {
        HuAudFXPlay(0x74A);
    }
    switch (lbl_1_bss_14) {
        case 3:
            lbl_1_bss_4 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_B4, 30.0f);
            lbl_1_bss_14 = 4;
            break;
        case 4:
            if (!MgCameraMoveCheck(lbl_1_bss_4)) {
                obj = lbl_1_bss_4;
                omDelObjEx(objman, obj);
                MgSeqModeNext();
            }
            break;
    }
}

/* asm 445-463, 16 insns. MGSEQ start hook. */
void fn_1_634(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_10 = HuAudSStreamPlay(0x34);
    }
}

/* asm 466-489, 22 insns. Added by ObjectSetup with MgSeqModeHookAdd; creates the fn_1_7C84 object. */
void fn_1_674(s16 mode, s16 frameNo)
{
    lbl_1_bss_1C = 0;
    fn_1_405C();
    omAddObjEx(objman, 0x1100, 0, 0, OM_GRP_NONE, fn_1_7C84);
}

/* asm 492-512, 18 insns. MGSEQ main hook. */
void fn_1_6CC(s16 mode, s16 frameNo)
{
    if (lbl_1_bss_13C->mode == 2) {
        lbl_1_bss_1C = 1;
        MgSeqModeNext();
    }
}

/* asm 515-539, 22 insns. MGSEQ finish hook. */
void fn_1_714(s16 mode, s16 frameNo)
{
    lbl_1_bss_18 = 2;
    if (frameNo == 0) {
        HuAudSStreamFadeOut(lbl_1_bss_10, 100);
        fn_1_BB0();
        fn_1_4858();
    }
}

/* asm 542-636, 85 insns. MGSEQ pre-winner hook. */
void fn_1_76C(s16 mode, s16 frameNo)
{
    int i;
    OMOBJ *obj;
    BOOL allSet = TRUE;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_140[i]->unk54 == 0) {
            allSet = FALSE;
        }
    }
    if (lbl_1_bss_0 == NULL) {
        if (allSet) {
            if (lbl_1_bss_1C == 0) {
                lbl_1_bss_0 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_FC, 30.0f);
            } else {
                lbl_1_bss_0 = MgCameraMoveEntry(&lbl_1_bss_44, &lbl_1_data_144, 30.0f);
            }
        }
    } else {
        if (!MgCameraMoveCheck(lbl_1_bss_0)) {
            obj = lbl_1_bss_0;
            omDelObjEx(objman, obj);
            MgSeqModeNext();
        }
    }
}

/* asm 639-645, 5 insns. MGSEQ winner hook. */
void fn_1_8C0(s16 mode, s16 frameNo)
{
    lbl_1_bss_18 = 4;
}

/* asm 648-654, 5 insns. MGSEQ close hook. */
void fn_1_8D4(s16 mode, s16 frameNo)
{
    lbl_1_bss_18 = 5;
}

/* asm 657-843, 178 insns. Object created by fn_1_12C. */
void fn_1_8E8(OMOBJ *obj)
{
    int i;
    float t;
    s16 vol;
    BOOL moving;

    if (lbl_1_bss_18 != 5) {
        t = (lbl_1_bss_44.dist - lbl_1_data_6C.dist) / (lbl_1_data_B4.dist - lbl_1_data_6C.dist);
        vol = 127.0f - 63.0f*t;
        HuAudFXVolSet(lbl_1_bss_C, vol);

        moving = FALSE;
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_140[i]->grp != 0) {
                if (lbl_1_bss_140[i]->mode != 6) {
                    if (PSVECMag(&lbl_1_bss_140[i]->vel) > 0.1f) {
                        moving = TRUE;
                    }
                }
            }
        }
        if (moving) {
            if (lbl_1_bss_8 == -1) {
                lbl_1_bss_8 = HuAudFXPlay(0x74B);
            }
        } else {
            if (lbl_1_bss_8 != -1) {
                HuAudFXStop(lbl_1_bss_8);
                lbl_1_bss_8 = -1;
            }
        }

        if (lbl_1_bss_20 != 0) {
            if (Hu3DMotionEndCheck(lbl_1_bss_8C[0])) {
                Hu3DModelAttrSet(lbl_1_bss_8C[0], HU3D_MOTATTR_PAUSE);
                lbl_1_bss_24 = frandmod(0x78) + 0x78;
                lbl_1_bss_20 = 0;
            }
        } else {
            if (lbl_1_bss_24 > 0) {
                lbl_1_bss_24--;
                if (lbl_1_bss_24 == 0) {
                    HuAudFXPlay(0x752);
                    Hu3DModelAttrReset(lbl_1_bss_8C[0], HU3D_MOTATTR_PAUSE);
                    Hu3DMotionTimeSet(lbl_1_bss_8C[0], 0.0f);
                    lbl_1_bss_20 = 1;
                }
            }
        }
    }
}

/* asm 846-904, 54 insns. Sets the winners (MgSeqWinnerSet). */
void fn_1_BB0(void)
{
    s16 charNo[4];
    int i;

    for (i = 0; i < 4; i++) {
        charNo[i] = CHARNO_NONE;
        if (lbl_1_bss_1C == lbl_1_bss_140[i]->grp) {
            charNo[i] = lbl_1_bss_140[i]->charNo;
            if (!_CheckFlag(FLAG_MG_PRACTICE)) {
                GwPlayer[i].mgCoinBonus = 10;
            }
        }
    }
    MgSeqWinnerSet(charNo[0], charNo[1], charNo[2], charNo[3]);
}

/* asm 907-933, 25 insns. Called from player.c. */
float fn_1_C88(HuVecF *a, HuVecF *b)
{
    HuVecF d;

    PSVECSubtract(b, a, &d);
    return (float)((atan2(d.x, d.z) / M_PI) * 180.0);
}

/* asm 936-966, 27 insns. Called from player.c. */
float fn_1_CEC(float a, float b)
{
    float d = b - a;

    if (d < -180.0f) {
        d = d + 360.0f;
    }
    if (d > 180.0f) {
        d = d - 360.0f;
    }
    return d;
}

/* asm 969-1037, 64 insns. Called from player.c. */
float fn_1_D58(HuVecF *a, HuVecF *b, HuVecF *c, HuVecF *d)
{
    HuVecF seg, toA, proj, closest;
    float sqMag, t;

    PSVECSubtract(c, b, &seg);
    PSVECSubtract(a, b, &toA);
    sqMag = PSVECSquareMag(&seg);
    t = PSVECDotProduct(&seg, &toA) / sqMag;
    if (t < 0.0f || t > 1.0f) {
        return -1.0f;
    }
    PSVECScale(&seg, &proj, t);
    PSVECAdd(b, &proj, d);
    PSVECSubtract(&proj, &toA, &closest);
    return PSVECMag(&closest);
}

/* asm 1040-1096, 55 insns. Called from player.c: 3D position to two s16 outputs via Hu3D3Dto2D. */
void fn_1_E58(HuVecF *pos, s16 *outA, s16 *outB)
{
    HuVec2f screen;

    Hu3D3Dto2D(pos, (s16)lbl_1_bss_44.no, &screen);
    *outB = (s16)(48.0f + 32.0f*(screen.x/576.0f));
    *outA = (s16)(96.0f + 31.0f*(screen.y/480.0f));
}

/* asm 1099-1156, 56 insns. Called from player.c: positional HuAudFXPlayVolPan. */
int fn_1_F34(HuVecF *pos, s16 seNo)
{
    HuVec2f screen;
    s16 pan, vol;

    Hu3D3Dto2D(pos, (s16)lbl_1_bss_44.no, &screen);
    pan = 48.0f + 32.0f*(screen.x/576.0f);
    vol = 96.0f + 31.0f*(screen.y/480.0f);
    return HuAudFXPlayVolPan(seNo, vol, pan);
}

/*
 * ===========================================================================
 * The framework, from REL/mgframe.h, in m570dll's include order.
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
