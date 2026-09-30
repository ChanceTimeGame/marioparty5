/*
 * m580Dll m580.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m580Dll/asm/REL/m580Dll/m580.s.
 */

#include "REL/m580Dll.h"

#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "math.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s32 lbl_1_rodata_10[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C */ /* s32 lbl_1_rodata_1C[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x28 */ /* float lbl_1_rodata_28 = 45.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 20.0f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 10000.0f; */
/* 0x34 */ /* float lbl_1_rodata_34 = 1.2f; */
/* 0x38 */ /* float lbl_1_rodata_38 = 0.0f; */
/* 0x3C */ /* float lbl_1_rodata_3C = 80.0f; */
/* 0x40 */ /* float lbl_1_rodata_40 = 5000.0f; */
/* 0x48 */ /* double lbl_1_rodata_48 = 0.5; */
/* 0x50 */ /* double lbl_1_rodata_50 = 3; */
/* 0x58 */ /* double lbl_1_rodata_58 = 180; */
/* 0x60 */ /* double lbl_1_rodata_60 = 3.141592653589793; */
/* 0x68 */ /* double lbl_1_rodata_68 = 600; */
/* 0x70 */ /* double lbl_1_rodata_70 = 1000; */
/* 0x78 */ /* double lbl_1_rodata_78 = 20; */
/* 0x80 */ /* double lbl_1_rodata_80 = 650; */
/* 0x88 */ /* double lbl_1_rodata_88 = -650; */
/* 0x90 */ /* double lbl_1_rodata_90 = 90; */
/* 0x98 */ /* double lbl_1_rodata_98 = 0; */
/* 0xA0 */ /* double lbl_1_rodata_A0 = 300; */
/* 0xA8 */ /* double lbl_1_rodata_A8 = 1200; */
/* 0xB0 */ /* double lbl_1_rodata_B0 = 800; */
/* 0xB8 */ /* double lbl_1_rodata_B8 = -800; */
/* 0xC0 */ /* double lbl_1_rodata_C0 = 0.03; */
/* 0xC8 */ /* double lbl_1_rodata_C8 = 4503601774854144; */
/* 0xD0 */ /* float lbl_1_rodata_D0 = 1.0f; */
/* 0xD8 */ /* double lbl_1_rodata_D8 = 1; */
/* 0xE0 */ /* double lbl_1_rodata_E0 = 2000; */
/* 0xE8 */ /* double lbl_1_rodata_E8 = 48; */
/* 0xF0 */ /* float lbl_1_rodata_F0 = 0.11111111f; */
/* 0xF4 */ /* float lbl_1_rodata_F4 = 32.0f; */
/* 0xF8 */ /* double lbl_1_rodata_F8 = -700; */
/* 0x100 */ /* double lbl_1_rodata_100 = 1400; */
/* 0x108 */ /* float lbl_1_rodata_108 = 31.0f; */
/* 0x10C */ /* float lbl_1_rodata_10C = 96.0f; */
/* 0x110 */ /* double lbl_1_rodata_110 = 2.388888888888889; */
/* 0x118 */ /* double lbl_1_rodata_118 = 0.7166666666666667; */
/* 0x120 */ /* double lbl_1_rodata_120 = 360; */
/* 0x128 */ /* float lbl_1_rodata_128 = 360.0f; */
/* 0x12C */ /* float lbl_1_rodata_12C = 180.0f; */

/* --- .data --- */
/* 0x0 */ OMCAMERAVIEW lbl_1_data_0 = { { 0.0f, 1350.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1180.0f }; /* ObjectSetup */
/* 0x1C */ HuVecF lbl_1_data_1C = { 1e+02f, 8e+02f, -1e+02f }; /* global light position */
/* 0x28 */ HuVecF lbl_1_data_28 = { 0.3f, -0.8f, 0.3f };      /* global light direction */
/* 0x34 */ float lbl_1_data_34[3] = { 20.0f, 45.0f, 1000.0f };  /* light rotation x, y and distance */
/* 0x40 */ GXColor lbl_1_data_40 = { 255, 255, 255, 255 };      /* global light colour */
/* 0x44 */ HuVecF lbl_1_data_44 = { 0.0f, 1e+03f, 1.5e+03f };   /* shadow camera position */
/* 0x50 */ HuVecF lbl_1_data_50 = { 0.0f, 0.0f, 1.0f };         /* shadow camera up */
/* 0x5C */ HuVecF lbl_1_data_5C = { 0.0f, 0.0f, 0.0f };         /* shadow camera target */
/* 0x68 */ MGSEQ_PARAM lbl_1_data_68 = { 0, MGSEQ_TIMER_BOTTOM, fn_1_37C, fn_1_424, fn_1_510, fn_1_548, fn_1_574, fn_1_6FC, fn_1_740, fn_1_78C, fn_1_790 };

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x48 */ OMOBJMAN *lbl_1_bss_48;  /* the overlay's object manager (dtk size 8: trailing section pad) */
/* 0x44 */ OMOBJ *lbl_1_bss_44;     /* camera object (fn_1_7C4); data is M580_CAMERA */
/* 0x40 */ s32 lbl_1_bss_40;        /* fn_1_C5C: frames the puck has been out of play */
/* 0x3C */ s32 lbl_1_bss_3C;        /* fn_1_1F34 calls; CharLoseVoicePlay at 4 */
/* 0x38 */ s32 lbl_1_bss_38;        /* fn_1_424 intro step */
/* 0x34 */ s32 lbl_1_bss_34;        /* fn_1_11044 result (always 0): record broken */
/* 0x32 gap_05_00000032_bss (0x2) -- dtk filler */
/* 0x30 */ HU3DLIGHTID lbl_1_bss_30; /* global light */
/* 0x2C */ s32 lbl_1_bss_2C;        /* HuAudBGMPlay stream id, -1 when none */
/* 0x28 */ s32 lbl_1_bss_28;        /* HuAudFXPlayVol(0x39C) crowd loop id, -1 before it plays */
/* 0x24 */ s32 lbl_1_bss_24;        /* fn_1_246C: crowd swell frames left */
/* 0x20 */ s32 lbl_1_bss_20;        /* fn_1_246C: crowd swell attack frames left (18) */
/* 0x18 */ s16 lbl_1_bss_18[4];     /* per player: ready flag (fn_1_1EC4 / fn_1_1EE4) */
/* 0x10 */ s16 lbl_1_bss_10[4];     /* per player: winner charNo or -1 (fn_1_574) */
/* 0x8 */ s16 lbl_1_bss_8[4];       /* per player: team 0/1 (fn_1_1E14) */
/* 0x0 */ s16 lbl_1_bss_0[4];       /* per player: charNo (fn_1_1E14) */

/* --- functions (reference order) --- */
/* 183 insns */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF unused0 = { 0.0f, 0.0f, 0.0f };
    HuVecF unused1 = { 0.0f, 0.0f, -1.0f };
    HuVecF target;
    HuVecF pos;
    s32 i;

    lbl_1_bss_40 = 0;
    lbl_1_bss_3C = 0;
    lbl_1_bss_34 = 0;
    lbl_1_bss_2C = -1;
    lbl_1_bss_28 = -1;
    for (i = 0; i < 4; i++) {
        lbl_1_bss_18[i] = 0;
    }
    lbl_1_bss_48 = omInitObjMan(80, 0x2000);
    omGameSysInit(lbl_1_bss_48);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, 20.0f, 10000.0f, 1.2f);
    lbl_1_bss_44 = omAddObjEx(lbl_1_bss_48, 90, 0, 0, -1, fn_1_7C4);
    omCameraViewSet(&lbl_1_data_0);
    lbl_1_bss_30 = Hu3DGLightCreateV(&lbl_1_data_1C, &lbl_1_data_28, &lbl_1_data_40);
    Hu3DGLightInfinitytSet(lbl_1_bss_30);
    Hu3DGLightStaticSet(lbl_1_bss_30, TRUE);
    target.x = target.y = target.z = 0.0f;
    pos.x = pos.z = 0.0f;
    pos.y = lbl_1_data_34[2];
    mtxRot(mtx, lbl_1_data_34[0], lbl_1_data_34[1], 0.0f);
    PSMTXMultVec(mtx, &pos, &pos);
    Hu3DGLightPosAimSetV(lbl_1_bss_30, &pos, &target);
    Hu3DShadowCreate(80.0f, 20.0f, 5000.0f);
    Hu3DShadowPosSet(&lbl_1_data_44, &lbl_1_data_50, &lbl_1_data_5C);
    Hu3DShadowColSet(50, 50, 50);
    Hu3DShadowSizeSet(240);
    MgSeqCreate(&lbl_1_data_68);
    MgSeqModeHookAdd(MGSEQ_MODE_PREMAIN, fn_1_544);
}

/* 42 insns. MGSEQ init hook: every unit's create function, then the intro camera motion. */
void fn_1_37C(s16 mode, s16 frameNo)
{
    fn_1_EE34(lbl_1_bss_48);
    fn_1_110A0(lbl_1_bss_48);
    fn_1_8358(lbl_1_bss_48);
    fn_1_2804(lbl_1_bss_48);
    fn_1_8A64(lbl_1_bss_48);
    fn_1_C8F8(lbl_1_bss_48);
    fn_1_D7E0(lbl_1_bss_48);
    fn_1_1838(HuDataSelHeapReadNum(0x86000F, HU_MEMNUM_OVL, HEAP_MODEL));
    MgSeqModeNext();
}

/* 59 insns. MGSEQ fade-in hook: BGM and the crowd loop, then waits for the camera motion. */
void fn_1_424(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_38 = 0;
    }
    if (lbl_1_bss_2C == -1 && frameNo >= 18) {
        lbl_1_bss_2C = HuAudBGMPlay(0x54);
        lbl_1_bss_28 = HuAudFXPlayVol(0x39C, 84);
    }
    switch (lbl_1_bss_38) {
        case 0:
            if (!fn_1_18A8() && !fn_1_D544()) {
                lbl_1_bss_38++;
                MgSeqModeNext();
            }
            break;
        case 1:
            break;
    }
}

/* 13 insns. MGSEQ start hook: crowd swell. */
void fn_1_510(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        fn_1_246C(180);
    }
}

/* 1 insns. Mode-hook for MGSEQ_MODE_PREMAIN. */
void fn_1_544(s16 mode, s16 frameNo)
{
}

/* 11 insns. MGSEQ main hook: ends when score.c's timer runs out. */
void fn_1_548(s16 mode, s16 frameNo)
{
    if (!fn_1_1104C()) {
        MgSeqModeNext();
    }
}

/* 98 insns. MGSEQ finish hook: the team with the higher score wins; a tie has no winner. */
void fn_1_574(s16 mode, s16 frameNo)
{
    s32 i;
    s32 score0;
    s32 score1;
    u16 winner;

    if (frameNo == 0) {
        if (lbl_1_bss_2C != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_2C, 100);
            lbl_1_bss_2C = -1;
        }
        HuAudFXPlay(0x966);
        fn_1_246C(180);
        score0 = fn_1_1100C(0);
        score1 = fn_1_1100C(1);
        for (i = 0; i < 4; i++) {
            lbl_1_bss_10[i] = -1;
            if ((score0 > score1 && lbl_1_bss_8[i] == 0) || (score0 < score1 && lbl_1_bss_8[i] == 1)) {
                lbl_1_bss_10[i] = lbl_1_bss_0[i];
            }
        }
        winner = MgSeqWinnerSet(lbl_1_bss_10[0], lbl_1_bss_10[1], lbl_1_bss_10[2], lbl_1_bss_10[3]);
        lbl_1_bss_34 = fn_1_11044();
    }
}

/* 17 insns. MGSEQ pre-winner hook. */
void fn_1_6FC(s16 mode, s16 frameNo)
{
    if (lbl_1_bss_34 == 0 && frameNo >= 120) {
        MgSeqModeNext();
    }
}

/* 19 insns. MGSEQ winner hook: no coin payout in this overlay. */
void fn_1_740(s16 mode, s16 frameNo)
{
    s32 i;

    if (frameNo == 0) {
        for (i = 0; i < 19; i++) {
            HuPrcVSleep();
        }
    }
}

/* 1 insns */
void fn_1_78C(s16 mode, s16 frameNo)
{
}

/* 13 insns. MGSEQ close hook: every unit's close function. */
void fn_1_790(s16 mode, s16 frameNo)
{
    fn_1_83F8();
    fn_1_C998();
    fn_1_29EC();
    fn_1_8B60();
    fn_1_11128();
    fn_1_EEBC();
}

/* 28 insns. Camera object: M580_CAMERA data (no pointer members), then fn_1_834. */
void fn_1_7C4(OMOBJ *obj)
{
    M580_CAMERA *work = obj->data;

    work = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M580_CAMERA), HU_MEMNUM_OVL);
    obj->data = work;
    memset(work, 0, sizeof(M580_CAMERA));
    fn_1_18D8(1);
    obj->objFunc = fn_1_834;
}

/* 25 insns */
void fn_1_834(OMOBJ *obj)
{
    M580_CAMERA *work = obj->data;

    fn_1_898(obj);
    if (work->unk000 == 0) {
        fn_1_C5C(obj);
        fn_1_10D8(obj);
    }
    fn_1_248C();
    work->unk00C = 0;
}

/* 241 insns. While the intro camera motion plays, adopt its eye/target as Center/CRot/CZoom. */
void fn_1_898(OMOBJ *obj)
{
    M580_CAMERA *work = obj->data;
    HuVecF pos;
    HuVecF target;
    HuVecF up;
    HuVecF dir;

    if (work->unk000 != 0) {
        Hu3DCameraPosGet(1, &pos, &up, &target);
        Center = target;
        work->unk070 = Center;
        dir.x = pos.x - target.x;
        dir.y = pos.y - target.y;
        dir.z = pos.z - target.z;
        CRot.x = HuAtan(-dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
        CRot.y = HuAtan(dir.x, dir.z);
        CRot.z = 0.0f;
        CZoom = sqrtf((dir.z * dir.z) + ((dir.x * dir.x) + (dir.y * dir.y)));
        if (Hu3DMotionEndCheck(work->unk006)) {
            Hu3DModelKill(work->unk006);
            work->unk07C = CRot;
            work->unk088 = CZoom;
            work->unk000 = 0;
        }
    }
}

/* 287 insns. Camera follow: eases Center/CRot.x/CZoom towards the base view,
 * pulled back while the puck is out of play and widened for players near the
 * side walls. */
void fn_1_C5C(OMOBJ *obj)
{
    M580_CAMERA *work = obj->data;
    HuVecF *pos = work->unk010;
    s32 i;
    s32 far;
    s32 right;
    s32 left;
    float x;
    float y;
    float z;
    float rotX;
    float zoom;

    if (work->unk008 != 0) {
        x = work->unk070.x;
        y = work->unk070.y;
        z = work->unk070.z;
        rotX = work->unk07C.x;
        zoom = work->unk088;
        if (!fn_1_1104C()) {
            if (MgSeqModeGet() != MGSEQ_MODE_FINISH) {
                y -= 600.0;
                z -= 1000.0;
                rotX += 20.0;
            }
            goto apply;
        }
        if (fn_1_D544() || fn_1_D6EC()) {
            far = 0;
            lbl_1_bss_40++;
            for (i = 0; i < work->unk00C; i++, pos++) {
                if (pos->x > 650.0 || pos->x < -650.0) {
                    break;
                }
            }
            if (i >= work->unk00C) {
                if (MgSeqModeGet() == MGSEQ_MODE_MAIN) {
                    if (lbl_1_bss_40 > 90.0) {
                        far = 1;
                    }
                } else if (lbl_1_bss_40 > 0.0) {
                    far = 1;
                }
            }
            if (far) {
                z += 300.0;
                zoom -= 1200.0;
                goto apply;
            }
        } else {
            lbl_1_bss_40 = 0;
        }
        /* Retail: pos is not reset after the loop above, so this walks on from
         * where that one stopped (up to unk010[14], past the 0x8C work). */
        right = 0;
        left = 0;
        for (i = 0; i < work->unk00C; i++, pos++) {
            if (pos->x > 800.0) {
                right = 1;
            }
            if (pos->x < -800.0) {
                left = 1;
            }
        }
        if (right) {
            x += 300.0;
            zoom += 300.0;
        }
        if (left) {
            x -= 300.0;
            zoom += 300.0;
            if (right) {
                zoom += 300.0;
            }
        }
    apply:
        Center.x = Center.x + 0.03 * (x - Center.x);
        Center.y += 0.03 * (y - Center.y);
        Center.z += 0.03 * (z - Center.z);
        CRot.x = CRot.x + 0.03 * (rotX - CRot.x);
        CZoom = CZoom + 0.03 * (zoom - CZoom);
    }
}

/* 472 insns. Center/CRot/CZoom to Hu3DCameraPosSet (m514 fn_1_9E4's tail). */
void fn_1_10D8(OMOBJ *obj)
{
    HuVecF pos;
    HuVecF target;
    HuVecF up;
    HuVecF upBase;
    HuVecF dir;
    float rotX;
    float rotY;
    float rotZ;

    rotX = CRot.x;
    rotY = CRot.y;
    rotZ = CRot.z;
    pos.x = Center.x + (CZoom * (HuSin(rotY) * HuCos(rotX)));
    pos.y = Center.y + (CZoom * -HuSin(rotX));
    pos.z = Center.z + (CZoom * (HuCos(rotY) * HuCos(rotX)));
    target.x = Center.x;
    target.y = Center.y;
    target.z = Center.z;
    upBase.x = HuSin(rotY) * HuSin(rotX);
    upBase.y = HuCos(rotX);
    upBase.z = HuCos(rotY) * HuSin(rotX);
    PSVECSubtract(&pos, &target, &dir);
    PSVECNormalize(&dir, &dir);
    up.x = (upBase.x * ((dir.x * dir.x) + ((1.0f - (dir.x * dir.x)) * HuCos(rotZ))))
         + (upBase.y * (((dir.x * dir.y) * (1.0 - HuCos(rotZ))) - (dir.z * HuSin(rotZ))))
         + (upBase.z * (((dir.x * dir.z) * (1.0 - HuCos(rotZ))) + (dir.y * HuSin(rotZ))));
    up.y = (upBase.y * ((dir.y * dir.y) + ((1.0f - (dir.y * dir.y)) * HuCos(rotZ))))
         + (upBase.x * (((dir.x * dir.y) * (1.0 - HuCos(rotZ))) + (dir.z * HuSin(rotZ))))
         + (upBase.z * (((dir.y * dir.z) * (1.0 - HuCos(rotZ))) - (dir.x * HuSin(rotZ))));
    up.z = (upBase.z * ((dir.z * dir.z) + ((1.0f - (dir.z * dir.z)) * HuCos(rotZ))))
         + ((upBase.x * (((dir.x * dir.z) * (1.0 - HuCos(rotZ))) - (dir.y * HuSin(rotZ))))
            + (upBase.y * (((dir.y * dir.z) * (1.0 - HuCos(rotZ))) + (dir.x * HuSin(rotZ)))));
    PSVECNormalize(&up, &up);
    Hu3DCameraPosSet(1, pos.x, pos.y, pos.z, up.x, up.y, up.z, target.x, target.y, target.z);
}

/* 28 insns */
void fn_1_1838(void *data)
{
    OMOBJ *obj = lbl_1_bss_44;
    M580_CAMERA *work = obj->data;

    work->unk004 = Hu3DMotionCreate(data);
    work->unk006 = Hu3DModelCameraCreate(work->unk004, 1);
    Hu3DCameraMotionStart(work->unk006, 1);
    work->unk000 = 1;
}

/* 12 insns */
s32 fn_1_18A8(void)
{
    OMOBJ *obj = lbl_1_bss_44;
    M580_CAMERA *work = obj->data;

    return work->unk000;
}

/* 12 insns */
void fn_1_18D8(s32 on)
{
    OMOBJ *obj = lbl_1_bss_44;
    M580_CAMERA *work = obj->data;

    work->unk008 = on;
}

/* 26 insns. Adds a camera focus point for this frame (at most 8). */
void fn_1_1908(HuVecF *pos)
{
    OMOBJ *obj = lbl_1_bss_44;
    M580_CAMERA *work = obj->data;

    if (work->unk00C < 8) {
        work->unk010[work->unk00C++] = *pos;
    }
}

/* 229 insns. 0..1 factor from camera distance and pitch (effect.c). */
float fn_1_1970(void)
{
    float y;
    float z;
    float dist;
    float a;
    float b;

    y = Center.y + CZoom * -HuSin(CRot.x);
    z = Center.z + CZoom * (HuCos(CRot.y) * HuCos(CRot.x));
    dist = sqrtf(y * y + z * z);
    a = (dist - 800.0) / 2000.0;
    if (a < 0.0) {
        a = 0.0f;
    }
    if (a > 1.0) {
        a = 1.0f;
    }
    b = CRot.x;
    b = (20.0 - (48.0 + b)) / 20.0;
    if (b < 0.0) {
        b = 0.0f;
    }
    if (b > 1.0) {
        b = 1.0f;
    }
    b = 0.5 + 0.5 * b;
    return a * b;
}

/* 15 insns. Seconds left. */
s32 fn_1_1D04(void)
{
    return fn_1_1104C() / 60;
}

/* 6 insns */
s32 fn_1_1D40(s32 no)
{
    return lbl_1_bss_10[no];
}

/* 47 insns. 1 if the team won, -1 if it lost, 0 on a tie. */
s32 fn_1_1D58(u32 team)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_10[i] >= 0) {
            break;
        }
    }
    if (i >= 4) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (team == lbl_1_bss_8[i]) {
            return (lbl_1_bss_10[i] >= 0) ? 1 : -1;
        }
    }
    /* Retail has no return here: r3 still holds `team` (this spelling emits no
     * code). Unreachable while every team has a member. */
    return team;
}

/* 14 insns. player.c records each player's team and charNo. */
void fn_1_1E14(s32 no, s32 team, s32 charNo)
{
    no &= 3;
    lbl_1_bss_8[no] = (s16)team;
    lbl_1_bss_0[no] = (s16)charNo;
}

/* 30 insns. The charNo of the idx-th member of a team, or -1. */
s32 fn_1_1E4C(u32 team, u32 idx)
{
    s32 n = 0;
    s32 i;

    for (i = 0; i < 4; i++) {
        if (team == lbl_1_bss_8[i]) {
            if (idx == n) {
                return lbl_1_bss_0[i];
            }
            n++;
        }
    }
    return -1;
}

/* 8 insns */
void fn_1_1EC4(s32 no)
{
    no &= 3;
    lbl_1_bss_18[no] = 1;
}

/* 20 insns. 1 once all four players set their flag. */
s32 fn_1_1EE4(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_18[i] == 0) {
            return 0;
        }
    }
    return 1;
}

/* 29 insns */
void fn_1_1F34(s32 no)
{
    if (++lbl_1_bss_3C == 4) {
        CharLoseVoicePlay(lbl_1_bss_0[0], lbl_1_bss_0[1], lbl_1_bss_0[2], lbl_1_bss_0[3]);
    }
}

/* 23 insns. Pan (32..96) for a screen x. */
s32 fn_1_1FA8(float x)
{
    s32 pan;
    x *= (64.0f / 576.0f);
    pan = 32.0f + x;
    if (pan < 32) {
        pan = 32;
    }
    if (pan > 96) {
        pan = 96;
    }
    return pan;
}

/* 37 insns. Pan for a 3D position. */
s32 fn_1_2004(HuVecF *pos)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_1FA8(out.x);
}

/* 37 insns. Volume (96..127) for a 3D position's depth. */
s32 fn_1_2098(HuVecF *pos)
{
    float z;
    s32 vol;

    z = (pos->z - -700.0) / 1400.0;
    z *= 31.0f;
    vol = 96.0f + z;
    if (vol < 96) {
        vol = 96;
    }
    if (vol > 127) {
        vol = 127;
    }
    return vol;
}

/* 77 insns. Positional HuAudFXPlayVolPan. */
s32 fn_1_212C(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayVolPan(seNo, fn_1_2098(pos), fn_1_2004(pos));
}

/* 46 insns. Positional HuAudFXPlayPan. */
s32 fn_1_2260(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayPan(seNo, fn_1_2004(pos));
}

/* 85 insns. Re-pans and re-volumes a playing SE. */
void fn_1_2318(s32 seId, HuVecF *pos)
{
    if (seId != -1 && HuAudFXStatusGet(seId) == 2) {
        HuAudFXPanning(seId, fn_1_2004(pos));
        HuAudFXVolSet(seId, fn_1_2098(pos));
    }
}

/* 8 insns. Starts a crowd swell of `time` frames. */
void fn_1_246C(s32 time)
{
    lbl_1_bss_24 = time;
    lbl_1_bss_20 = 18;
}

/* 106 insns. Crowd loop volume: 84, raised to 127 over 18 frames by fn_1_246C, then decays. */
void fn_1_248C(void)
{
    s32 vol;

    if (lbl_1_bss_28 != -1) {
        if (lbl_1_bss_24 > 0) {
            lbl_1_bss_24--;
        }
        if (lbl_1_bss_20 > 0) {
            lbl_1_bss_20--;
        }
        if (lbl_1_bss_24 == 0) {
            HuAudFXVolSet(lbl_1_bss_28, 84);
        } else {
            if (lbl_1_bss_20 != 0) {
                vol = 127 - (s32)((43.0 / 18.0) * lbl_1_bss_20);
            } else {
                vol = (s32)((43.0 / 60.0) * lbl_1_bss_24) + 84;
            }
            if (vol < 84) {
                vol = 84;
            }
            if (vol > 127) {
                vol = 127;
            }
            HuAudFXVolSet(lbl_1_bss_28, vol);
        }
    }
}

/* 71 insns */
float fn_1_2634(float cur, float target, float rate)
{
    float d;
    float e;
    float r;

    d = fmod(target - cur, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    e = fmod(cur + rate * r, 360.0);
    r = e;
    if (r < 0.0f) {
        r += 360.0f;
    }
    return r;
}

/* 45 insns */
float fn_1_2750(float from, float to)
{
    float d;
    float r;

    d = fmod(to - from, 360.0);
    r = d;
    if (r < 0.0f) {
        r += 360.0f;
    }
    if (r > 180.0f) {
        r -= 360.0f;
    }
    return r;
}
