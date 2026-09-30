/*
 * m514dll m514.c -- generated skeleton, stubs only. Functions are in reference
 * order. Line ranges are into build/mp5-asm/m514Dll/asm/REL/m514Dll/m514.s.
 */

#include "REL/m514Dll.h"

#include "game/audio.h"
#include "game/data.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/memory.h"
#include "game/mg/seqman.h"
#include "game/pad.h"
#include "game/sprite.h"

#include "math.h"

#include "datadir_enum.h"

/* --- .rodata (float/double literals: CodeWarrior pools these) --- */
/* 0x10 */ /* s32 lbl_1_rodata_10[3] = { 0x00000000, 0x00000000, 0x00000000 }; */
/* 0x1C */ /* s32 lbl_1_rodata_1C[3] = { 0x00000000, 0x00000000, 0xBF800000 }; */
/* 0x28 */ /* float lbl_1_rodata_28 = 45.0f; */
/* 0x2C */ /* float lbl_1_rodata_2C = 1.2f; */
/* 0x30 */ /* float lbl_1_rodata_30 = 0.0f; */
/* 0x38 */ /* double lbl_1_rodata_38 = 0.40000002086162567; */
/* 0x40 */ /* double lbl_1_rodata_40 = 120; */
/* 0x48 */ /* float lbl_1_rodata_48 = 120.0f; */
/* 0x4C */ /* float lbl_1_rodata_4C = 1200.0f; */
/* 0x50 */ /* double lbl_1_rodata_50 = 0.5; */
/* 0x58 */ /* double lbl_1_rodata_58 = 3; */
/* 0x60 */ /* double lbl_1_rodata_60 = 57.295780181884766; */
/* 0x68 */ /* double lbl_1_rodata_68 = 3.141592653589793; */
/* 0x70 */ /* double lbl_1_rodata_70 = 180; */
/* 0x78 */ /* float lbl_1_rodata_78 = 1.0f; */
/* 0x80 */ /* double lbl_1_rodata_80 = 1; */
/* 0x88 */ /* s32 lbl_1_rodata_88[6] = { 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000 }; */
/* 0xA0 */ /* double lbl_1_rodata_A0 = 0.1745329201221466; */
/* 0xA8 */ /* float lbl_1_rodata_A8 = 20.0f; */
/* 0xAC */ /* float lbl_1_rodata_AC = 0.4f; */
/* 0xB0 */ /* float lbl_1_rodata_B0 = 0.055555556f; */
/* 0xB4 */ /* float lbl_1_rodata_B4 = 48.0f; */
/* 0xB8 */ /* double lbl_1_rodata_B8 = 360; */
/* 0xC0 */ /* float lbl_1_rodata_C0 = 360.0f; */
/* 0xC4 */ /* float lbl_1_rodata_C4 = 180.0f; */

/* --- .data --- */
/* 0x0 */ float lbl_1_data_0 = 20.0f;
/* 0x4 */ float lbl_1_data_4 = 25000.0f;
/* 0x8 */ float lbl_1_data_8 = 48.0f;
/* 0xC */ OMCAMERAVIEW lbl_1_data_C[2] = {     /* [0] ObjectSetup, [1] fn_1_7B0 (center.x from fn_1_9688) */
    { { -1500.0f, 1250.0f, 0.0f }, { -10.0f, 0.0f, 0.0f }, 1180.0f },
    { { -2500.0f, 120.0f, 0.0f }, { -15.0f, 0.0f, 0.0f }, 750.0f },
};
/* 0x44 */ HuVecF lbl_1_data_44 = { 100.0f, 800.0f, -100.0f };     /* global light position */
/* 0x50 */ HuVecF lbl_1_data_50 = { 0.3f, -0.8f, 0.3f };           /* global light direction */
/* 0x5C */ HuVecF lbl_1_data_5C = { 40.0f, -60.0f, 1000.0f };      /* light rotation x, y and distance */
/* 0x68 */ GXColor lbl_1_data_68 = { 255, 255, 255, 255 };       /* global light colour */
/* 0x6C */ s32 lbl_1_data_6C[9] = { 0x00000000, 0x459C4000, 0x447A0000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };
/* 0x90 */ MGSEQ_PARAM lbl_1_data_90 = {
    0, MGSEQ_TIMER_BOTTOM,
    fn_1_3A0,
    fn_1_448,
    fn_1_540,
    fn_1_580,
    fn_1_600,
    fn_1_7B0,
    fn_1_8A0,
    fn_1_958,
    fn_1_95C
};

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x6C gap_05_0000006C_bss (0x4) -- dtk filler */
/* 0x68 */ OMOBJMAN *lbl_1_bss_68;  /* the overlay's object manager */
/* 0x64 */ OMOBJ *lbl_1_bss_64;     /* fn_1_98C object; its data is 8 bytes (fn_1_163C/fn_1_16AC) */
/* 0x60 */ s32 lbl_1_bss_60;
/* 0x5C */ s32 lbl_1_bss_5C;        /* fn_1_448 fade-in step */
/* 0x58 */ s32 lbl_1_bss_58;        /* fn_1_9820 result: jingle on the winner screen */
/* 0x56 */ s16 lbl_1_bss_56;
/* 0x54 */ HU3DLIGHTID lbl_1_bss_54; /* global light */
/* 0x50 */ s32 lbl_1_bss_50;        /* HuAudBGMPlay stream id, -1 when none */
/* 0x4C */ s32 lbl_1_bss_4C;        /* HuAudFXPlay(0x6DD) id, -1 before it plays */
/* 0x40 */ HuVecF lbl_1_bss_40;     /* light target */
/* 0x34 */ HuVecF lbl_1_bss_34;     /* light position */
/* 0x28 */ HuVecF lbl_1_bss_28;     /* light target - position */
/* 0x20 */ s16 lbl_1_bss_20[4];     /* per player: winner charNo or -1 (fn_1_600) */
/* 0x18 */ s16 lbl_1_bss_18[4];
/* 0x10 */ s16 lbl_1_bss_10[4];     /* per player: charNo passed to MgSeqWinnerSet */
/* 0x8 */ s16 lbl_1_bss_8[4];       /* per player: nonzero if eligible to win */
/* 0x4 */ s32 lbl_1_bss_4;
/* 0x0 */ s32 lbl_1_bss_0;

/* --- functions (reference order) --- */
/* m514.c ObjectSetup, 192 insns. Object manager, camera, the fn_1_98C object, global light, then the sequence manager. */
void ObjectSetup(void)
{
    Mtx mtx;
    HuVecF unused0 = { 0.0f, 0.0f, 0.0f };
    HuVecF unused1 = { 0.0f, 0.0f, -1.0f };
    s32 i;
    HU3DLIGHT *light;

    lbl_1_bss_60 = 0;
    lbl_1_bss_58 = 0;
    lbl_1_bss_56 = 0;
    lbl_1_bss_50 = -1;
    lbl_1_bss_4C = -1;
    for (i = 0; i < 4; i++) {
        /*
         * Retail quirk: a constant [4], one past the end of each array. In
         * retail's .bss these land on bss_18[0], bss_20[0] and bss_10[0]; the
         * host does not keep that layout, so it stores to those elements.
         */
        lbl_1_bss_18[4] = lbl_1_bss_10[4] = -1;
        lbl_1_bss_8[4] = 0;
    }
    lbl_1_bss_68 = omInitObjMan(50, 0x2000);
    omGameSysInit(lbl_1_bss_68);
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 45.0f, lbl_1_data_0, lbl_1_data_4, 1.2f);
    lbl_1_bss_64 = omAddObjEx(lbl_1_bss_68, 32730, 0, 0, -1, fn_1_98C);
    omCameraViewSet(lbl_1_data_C);
    lbl_1_bss_54 = Hu3DGLightCreateV(&lbl_1_data_44, &lbl_1_data_50, &lbl_1_data_68);
    Hu3DGLightInfinitytSet(lbl_1_bss_54);
    light = &Hu3DGlobalLight[lbl_1_bss_54];
    light->type |= 0x8000;
    lbl_1_bss_40.x = lbl_1_bss_40.y = lbl_1_bss_40.z = 0.0f;
    lbl_1_bss_34.x = lbl_1_bss_34.z = 0.0f;
    lbl_1_bss_34.y = lbl_1_data_5C.z;
    mtxRot(mtx, lbl_1_data_5C.x, lbl_1_data_5C.y, 0.0f);
    PSMTXMultVec(mtx, &lbl_1_bss_34, &lbl_1_bss_34);
    Hu3DGLightPosAimSetV(lbl_1_bss_54, &lbl_1_bss_34, &lbl_1_bss_40);
    PSVECSubtract(&lbl_1_bss_40, &lbl_1_bss_34, &lbl_1_bss_28);
    MgSeqCreate(&lbl_1_data_90);
}

/* m514.c fn_1_3A0, 42 insns. MGSEQ init hook: creates every unit's objects, then the camera motion. */
void fn_1_3A0(s16 mode, s16 frameNo)
{
    fn_1_8268(lbl_1_bss_68);
    fn_1_5B04(lbl_1_bss_68);
    fn_1_510C(lbl_1_bss_68);
    fn_1_1D9C(lbl_1_bss_68);
    fn_1_4270(lbl_1_bss_68);
    lbl_1_bss_4 = 0;
    lbl_1_bss_0 = 0;
    fn_1_163C(HuDataSelHeapReadNum(DATANUM(DATA_m514, 0x05), HU_MEMNUM_OVL, HEAP_MODEL));
    MgSeqModeNext();
}

/* m514.c fn_1_448, 62 insns. MGSEQ fade-in hook. */
void fn_1_448(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_5C = 0;
    }
    if (lbl_1_bss_4C == -1 && frameNo >= 18) {
        lbl_1_bss_4C = HuAudFXPlay(0x6DD);
    }
    switch (lbl_1_bss_5C) {
        case 0:
            if (frameNo < 30) {
                break;
            }
            lbl_1_bss_5C++;
        case 1:
            if (fn_1_16AC() == 0) {
                lbl_1_bss_5C++;
                MgSeqModeNext();
            }
            break;
        case 2:
            break;
    }
}

/* m514.c fn_1_540, 16 insns. MGSEQ start hook. */
void fn_1_540(s16 mode, s16 frameNo)
{
    if (frameNo == 0) {
        lbl_1_bss_50 = HuAudBGMPlay(0x34);
    }
}

/* m514.c fn_1_580, 32 insns. MGSEQ main hook. */
void fn_1_580(s16 mode, s16 frameNo)
{
    s32 next = 0;

    if (lbl_1_bss_0 != 0) {
        lbl_1_bss_0 = 0;
        if (++lbl_1_bss_4 >= 4) {
            next = 1;
        }
    }
    if (next) {
        MgSeqModeNext();
    }
}

/* m514.c fn_1_600, 108 insns. MGSEQ finish hook: winners are the highest fn_1_95BC score. */
void fn_1_600(s16 mode, s16 frameNo)
{
    s32 score[4];
    s32 i;
    s32 value;
    s32 max = 0;
    u16 winner;

    if (frameNo == 0) {
        if (lbl_1_bss_50 != -1) {
            HuAudSStreamFadeOut(lbl_1_bss_50, 100);
            lbl_1_bss_50 = -1;
        }
        lbl_1_bss_56 = 0;
        for (i = 0; i < 4; i++) {
            value = fn_1_95BC(i);
            if (value > max) {
                max = value;
            }
            score[i] = value;
        }
        for (i = 0; i < 4; i++) {
            lbl_1_bss_20[i] = -1;
            if (lbl_1_bss_8[i] != 0 && max == score[i]) {
                lbl_1_bss_20[i] = lbl_1_bss_10[i];
            }
        }
        winner = MgSeqWinnerSet(lbl_1_bss_20[0], lbl_1_bss_20[1], lbl_1_bss_20[2], lbl_1_bss_20[3]);
        if (!_CheckFlag(FLAG_INST_DECA)) {
            lbl_1_bss_58 = fn_1_9820();
        } else {
            fn_1_98F4();
        }
    }
}

/* m514.c fn_1_7B0, 60 insns. MGSEQ pre-winner hook. */
void fn_1_7B0(s16 mode, s16 frameNo)
{
    if (_CheckFlag(FLAG_INST_DECA)) {
        MgSeqModeSet(MGSEQ_MODE_FADEOUT);
    } else {
        if (frameNo == 0) {
            lbl_1_data_C[1].center.x = fn_1_9688();
            omCameraViewMove(&lbl_1_data_C[1], 72, 0);
        }
        if (frameNo == 90 && lbl_1_bss_58 != 0 && !_CheckFlag(FLAG_MG_PRACTICE)) {
            HuAudJinglePlay(0x86);
        }
        if ((lbl_1_bss_58 == 0 || _CheckFlag(FLAG_MG_PRACTICE)) && frameNo >= 90) {
            MgSeqModeNext();
        }
    }
}

/* m514.c fn_1_8A0, 46 insns. MGSEQ winner hook: 10 bonus coins to each winner. */
void fn_1_8A0(s16 mode, s16 frameNo)
{
    s32 i;

    if (frameNo == 0) {
        for (i = 0; i < 4; i++) {
            if (lbl_1_bss_20[i] >= 0) {
                GWMgCoinBonusSet(i, GWMgCoinBonusGet(i) + 10);
            }
        }
    }
}

/* m514.c fn_1_958, 1 insns. MGSEQ fade-out hook. */
void fn_1_958(s16 mode, s16 frameNo)
{
}

/* m514.c fn_1_95C, 12 insns. MGSEQ close hook: every unit's close function. */
void fn_1_95C(s16 mode, s16 frameNo)
{
    fn_1_5B8C();
    fn_1_51BC();
    fn_1_1EA0();
    fn_1_4344();
    fn_1_8300();
}

/* m514.c fn_1_98C, 22 insns. Object created by ObjectSetup: 8-byte data (no pointer members), then fn_1_9E4. */
void fn_1_98C(OMOBJ *obj)
{
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M514_MAIN), HU_MEMNUM_OVL);
    memset(obj->data, 0, sizeof(M514_MAIN));
    obj->objFunc = fn_1_9E4;
}

/* 708 insns */
void fn_1_9E4(OMOBJ *obj)
{
    M514_MAIN *work = obj->data;
    HuVecF pos;
    HuVecF target;
    HuVecF up;
    HuVecF upBase;
    HuVecF dir;
    float rotX;
    float rotY;
    float rotZ;

    /* SE volume (fn_1_19F4) ramps from 48 up to 120 by 0.4 a frame */
    if ((lbl_1_data_8 += (1.0f / 60.0f) * 24.0) > 120.0) {
        lbl_1_data_8 = 120.0f;
    }
    Hu3DCameraPosGet(1, &pos, &up, &target);
    fn_1_14F4(&lbl_1_bss_28, &target, 1200.0f);
    /* while the intro camera motion (fn_1_163C) plays, wait for it; when it
     * ends, adopt its final eye/target as Center/CRot/CZoom */
    if (work->unk000 != 0) {
        if (!Hu3DMotionEndCheck(work->unk006)) {
            return;
        }
        Hu3DModelKill(work->unk006);
        Center = target;
        dir.x = pos.x - target.x;
        dir.y = pos.y - target.y;
        dir.z = pos.z - target.z;
        CRot.x = 57.29578f * atan2(-dir.y, sqrtf(dir.x * dir.x + dir.z * dir.z));
        CRot.y = 57.29578f * atan2(dir.x, dir.z);
        CRot.z = 0.0f;
        CZoom = sqrtf((dir.z * dir.z) + ((dir.x * dir.x) + (dir.y * dir.y)));
        work->unk000 = 0;
    }
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

/* The float tan fn_1_14F4 needs: libc/math.h declares tanf extern, but retail
 * inlines it the way math.h's sinf/cosf are inlined. A named float local for the
 * tan result claims f28 ahead of fabs's inline parameter (raw=12, registers only);
 * this inline's return temporary does not (raw=0). */
static inline float fn_1_tanf(float x) { return (float)tan((double)x); }

/* 82 insns */
void fn_1_14F4(HuVecF *dir, HuVecF *target, float dist)
{
    static const HuVecF lbl_1_rodata_88[2] = { { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f } };
    HuVecF pos;
    HuVecF norm;
    const HuVecF *up = lbl_1_rodata_88;
    float d = dist / fn_1_tanf(0.17453292f); /* 10 degrees */

    PSVECNormalize(dir, &norm);
    PSVECScale(&norm, &pos, d);
    PSVECSubtract(target, &pos, &pos);
    if (fabs(norm.y) > 0.5) {
        up++;
    }
    Hu3DShadowCreate(20.0f, d - dist, d + dist);
    Hu3DShadowPosSet(&pos, (HuVecF *)up, target);
    Hu3DShadowSizeSet(480);
    Hu3DShadowTPLvlSet(0.4f);
}

/* 28 insns */
void fn_1_163C(void *data)
{
    OMOBJ *obj = lbl_1_bss_64;
    M514_MAIN *work = obj->data;

    work->unk004 = Hu3DMotionCreate(data);
    work->unk006 = Hu3DModelCameraCreate(work->unk004, 1);
    Hu3DCameraMotionStart(work->unk006, 1);
    work->unk000 = 1;
}

/* 12 insns */
s32 fn_1_16AC(void)
{
    OMOBJ *obj = lbl_1_bss_64;
    M514_MAIN *work = obj->data;

    return work->unk000;
}

/* 4 insns */
s16 fn_1_16DC(void)
{
    return lbl_1_bss_56;
}

/* 6 insns */
s32 fn_1_16EC(s32 no)
{
    return lbl_1_bss_20[no];
}

/* 68 insns */
s32 fn_1_1704(u32 no)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (lbl_1_bss_20[i] >= 0) {
            break;
        }
    }
    if (i >= 4) {
        for (i = 0; i < 4; i++) {
            if (no == lbl_1_bss_18[i] && lbl_1_bss_8[i] != 0) {
                return 1;
            }
        }
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (no == lbl_1_bss_18[i]) {
            return (lbl_1_bss_20[i] >= 0) ? 1 : -1;
        }
    }
    /* Retail has no return here: r3 still holds `no`, and this spelling emits
     * no code for it. Reached when `no` is not one of the four group numbers
     * fn_1_1838 recorded; the caller then treats it as "not -1". */
    return no;
}

/* 4 insns */
s32 fn_1_1814(void)
{
    return lbl_1_bss_4;
}

/* 5 insns */
void fn_1_1824(s32 no)
{
    lbl_1_bss_0 = 1;
}

/* 14 insns */
void fn_1_1838(s32 no, s32 arg1, s32 charNo)
{
    no &= 3;
    lbl_1_bss_18[no] = (s16)arg1;
    lbl_1_bss_10[no] = (s16)charNo;
}

/* 8 insns */
void fn_1_1870(s32 no)
{
    lbl_1_bss_8[no & 3] = 1;
}

/* 29 insns */
void fn_1_1890(s32 no)
{
    if (++lbl_1_bss_60 == 4) {
        CharLoseVoicePlay(lbl_1_bss_10[0], lbl_1_bss_10[1], lbl_1_bss_10[2], lbl_1_bss_10[3]);
    }
}

/* 23 insns */
s32 fn_1_1904(float x)
{
    s32 pan;
    x *= (32.0f / 576.0f);
    pan = 48.0f + x;
    if (pan < 48) {
        pan = 48;
    }
    if (pan > 80) {
        pan = 80;
    }
    return pan;
}

/* 37 insns */
s32 fn_1_1960(HuVecF *pos)
{
    HuVecF out;
    Hu3D3Dto2D(pos, 1, &out);
    return fn_1_1904(out.x);
}

/* 9 insns */
s32 fn_1_19F4(HuVecF *pos)
{
    return lbl_1_data_8;
}

/* 55 insns */
s32 fn_1_1A18(s32 seNo, HuVecF *pos)
{
    return HuAudFXPlayVolPan(seNo, fn_1_19F4(pos), fn_1_1960(pos));
}

/* 54 insns */
void fn_1_1AF4(s32 seId, HuVecF *pos)
{
    if (seId != -1 && HuAudFXStatusGet(seId) == 2) {
        HuAudFXPanning(seId, fn_1_1960(pos));
    }
}

/* 71 insns */
float fn_1_1BCC(float cur, float target, float rate)
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
float fn_1_1CE8(float from, float to)
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

