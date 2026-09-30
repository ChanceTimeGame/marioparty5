/*
 * mgfreeDll mgfree.c -- generated skeleton, stubs only. Functions are in reference
 * order; see build/mp5-asm/mgfreeDll/asm/REL/mgfreeDll/mgfree.s.
 */

#include "REL/mgfreeDll.h"

#include "game/audio.h"
#include "game/memory.h"
#include "game/pad.h"
#include "game/data.h"
#include "game/wipe.h"
#include "game/flag.h"
#include "game/gamework.h"
#include "game/thpmain.h"
#include "math.h"
#include "game/armem.h"
#include "game/mgdata.h"
#include "string.h"

/* decide.c lbl_1_data_330: window layout records (0x18) */
typedef struct MgFreeWinData_s {
    float x;
    float y;
    float w;
    float h;
    s32 pri;
    u32 attr;
} MGFREE_WINDATA;

/* --- .rodata: float/double literals (a used static const folds into the literal pool) --- */
/* 0x0 pad_03_00000000_rodata: 0x3FE00000 0x00000000 0x40080000 0x00000000 */
static const double lbl_1_rodata_10 = 180.0; /* 0x10 */
static const double lbl_1_rodata_18 = 360.0; /* 0x18 */
static const float lbl_1_rodata_20 = 180.0f; /* 0x20 */
static const float lbl_1_rodata_24 = 0.0f; /* 0x24 */
static const float lbl_1_rodata_28 = 121.0f; /* 0x28 */
static const float lbl_1_rodata_2C = 145.0f; /* 0x2C */
static const float lbl_1_rodata_30 = 120.0f; /* 0x30 */
static const float lbl_1_rodata_34 = 90.0f; /* 0x34 */
static const float lbl_1_rodata_38 = 45.0f; /* 0x38 */
static const float lbl_1_rodata_3C = 360.0f; /* 0x3C */
static const double lbl_1_rodata_40 = 3.141592653589793; /* 0x40 */
static const double lbl_1_rodata_48 = 0.5; /* 0x48 */
/* 0x50 lbl_1_rodata_50 = 4503601774854144: int->float conversion constant, compiler-generated */
/* 0x58 lbl_1_rodata_58 (0x4): 0x00970039 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_5C = 300.0f; /* 0x5C */
static const float lbl_1_rodata_60 = 20.0f; /* 0x60 */
static const float lbl_1_rodata_64 = 400.0f; /* 0x64 */
static const float lbl_1_rodata_68 = -20.0f; /* 0x68 */
static const float lbl_1_rodata_6C = 0.8f; /* 0x6C */
/* 0x70 lbl_1_rodata_70 (0xC): 0x453B8000 0x453B8000 0x453B8000 -- an aggregate initialiser, write it as a local */
/* 0x7C lbl_1_rodata_7C (0xC): 0xBF800000 0xBF800000 0xBF800000 -- an aggregate initialiser, write it as a local */
static const float lbl_1_rodata_88 = 60.0f; /* 0x88 */
static const float lbl_1_rodata_8C = 60000.0f; /* 0x8C */
static const float lbl_1_rodata_90 = 1.2f; /* 0x90 */
static const float lbl_1_rodata_94 = 640.0f; /* 0x94 */
static const float lbl_1_rodata_98 = 480.0f; /* 0x98 */
static const float lbl_1_rodata_9C = 1.0f; /* 0x9C */
static const float lbl_1_rodata_A0 = 1000.0f; /* 0xA0 */
static const float lbl_1_rodata_A4 = -1.0f; /* 0xA4 */
static const float lbl_1_rodata_A8 = 4.0f; /* 0xA8 */
static const double lbl_1_rodata_B0 = 0.7; /* 0xB0 */
static const double lbl_1_rodata_B8 = 1.5707963267948966; /* 0xB8 */
static const float lbl_1_rodata_C0 = 48.0f; /* 0xC0 */
static const float lbl_1_rodata_C4 = 1080.0f; /* 0xC4 */
static const double lbl_1_rodata_C8 = 1e-05; /* 0xC8 */
static const float lbl_1_rodata_D0 = 1e-05f; /* 0xD0 */
static const float lbl_1_rodata_D4 = 30.0f; /* 0xD4 */
/* 0xD8 lbl_1_rodata_D8 (0x10): 0x00000000 0x00000001 0x00000002 0x00000003 -- an aggregate initialiser, write it as a local */
/* 0xE8 lbl_1_rodata_E8 (0xC): 0x00000000 0x00000001 0x00000002 -- an aggregate initialiser, write it as a local */
/* 0xF4 gap_03_000000F4_rodata: 0x00000000 */

/* --- .bss (declared DESCENDING: CW emits .bss in reverse declaration order) --- */
/* 0x8 */ MGFREE_WORK lbl_1_bss_8;
/* 0x4 */ MGFREE_MODEWORK *lbl_1_bss_4;
/* 0x0 */ MGFREE_WORK *lbl_1_bss_0;

/* --- functions (reference order), .data placed before its first user --- */
/* 29 insns */
void fn_1_A0(s32 time)
{
    if (WipeTypeGet() == 0x89) {
        WipeCreate(1, 0, time);
    } else {
        WipeCreate(1, 5, time);
    }
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 19 insns */
void fn_1_114(s32 time)
{
    WipeCreate(2, 6, time);
    while (WipeCheckEnd()) {
        HuPrcVSleep();
    }
}

/* 26 insns */
void fn_1_160(s32 mdlId, float start, float end)
{
    Hu3DMotionStartEndSet(mdlId, start, end);
    Hu3DMotionTimeSet(mdlId, start);
    Hu3DMotionShapeTimeSet(mdlId, start);
}

/* 7 insns */
void fn_1_1C8(u32 flag)
{
    lbl_1_bss_0->flags |= flag;
}

/* 7 insns */
void fn_1_1E4(u32 flag)
{
    lbl_1_bss_0->flags &= ~flag;
}

/* 6 insns */
u32 fn_1_200(u32 flag)
{
    return lbl_1_bss_0->flags & flag;
}

/* 0x0 */ HuVecF lbl_1_data_0[2] = { { 0.0f, 970.0f, -900.0f }, { 0.0f, 3000.0f, -900.0f } };
/* 0x18 */ MGFREE_MDLDATA lbl_1_data_18[13] = {
    { DATANUM(DATA_mgfree, 2), 16, 0, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 3), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 4), 16, 5, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 5), 16, 5, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 6), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 8), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 10), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 12), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 13), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 11), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 9), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 7), 16, 3, 0, 0x40000001 },
    { DATANUM(DATA_mgfree, 14), 16, 4, 0, 0x40000001 }
};
/* 0x11C */ MGFREE_GENRE lbl_1_data_11C[8] = {
    { MG_TYPE_4P, 0xE0007 },
    { MG_TYPE_1VS3, 0xE0008 },
    { MG_TYPE_2VS2, 0xE0009 },
    { MG_TYPE_BATTLE, 0xE000A },
    { MG_TYPE_KETTOU, 0xE000B },
    { MG_TYPE_KUPA, 0xE000C },
    { MG_TYPE_DONKEY, 0xE000D },
    { MG_TYPE_LAST, 0xE000E }
};

/* 11 insns */
u8 fn_1_218(void)
{
    return lbl_1_data_11C[lbl_1_bss_4->genre].mgType;
}

/* 10 insns */
u32 fn_1_244(void)
{
    return lbl_1_data_11C[lbl_1_bss_4->genre].mes;
}

/* 18 insns */
void fn_1_26C(s32 evtno)
{
    OMOVLHIS *his = omOvlHisGet(0);
    omOvlHisChg(0, his->ovl, evtno, his->stat);
}

/* 4 insns */
float fn_1_2B4(float a, float b, float t)
{
    return b + t * (a - b);
}

/* 130 insns */
s32 fn_1_2C4(float *angle, float target, float speed)
{
    float a;
    float b;
    float diff = *angle - target;
    float t180 = fmod(diff, 180.0);
    float t360;
    a = t180;
    t360 = fmod(diff, 360.0);
    b = t360;
    if (fabsf(b) > 180.0f) {
        if (a > 0.0f) {
            a = -(180.0f - fabsf(a));
        } else {
            a = 180.0f - fabsf(a);
        }
    }
    if (fabsf(a) < speed) {
        *angle = target;
        return 1;
    }
    if (a > 0.0f) {
        a -= speed;
    } else {
        a += speed;
    }
    *angle = target + a;
    return 0;
}

/* 110 insns */
void fn_1_4CC(void)
{
    s32 mdlId = lbl_1_bss_0->mdl[3];
    fn_1_1E4(4);
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_160(mdlId, 121.0f, 145.0f);
    while (!Hu3DMotionEndCheck(mdlId)) {
        if (fn_1_200(4)) {
            fn_1_160(mdlId, 121.0f, 145.0f);
            fn_1_1E4(4);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_160(mdlId, 0.0f, 120.0f);
    lbl_1_bss_0->proc1D4 = NULL;
    HuPrcEnd();
}

/* 33 insns */
void fn_1_684(void)
{
    fn_1_1C8(4);
    if (lbl_1_bss_0->proc1D4 == 0) {
        lbl_1_bss_0->proc1D4 = HuPrcChildCreate(fn_1_4CC, 100, 0x1000, 0, lbl_1_bss_0->objman);
    }
}

/* 110 insns */
void fn_1_708(void)
{
    s32 mdlId = lbl_1_bss_0->mdl[2];
    fn_1_1E4(8);
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_160(mdlId, 121.0f, 145.0f);
    while (!Hu3DMotionEndCheck(mdlId)) {
        if (fn_1_200(8)) {
            fn_1_160(mdlId, 121.0f, 145.0f);
            fn_1_1E4(8);
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(mdlId, HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_LOOP);
    fn_1_160(mdlId, 0.0f, 120.0f);
    lbl_1_bss_0->proc1D8 = NULL;
    HuPrcEnd();
}

/* 33 insns */
void fn_1_8C0(void)
{
    fn_1_1C8(8);
    if (lbl_1_bss_0->proc1D8 == 0) {
        lbl_1_bss_0->proc1D8 = HuPrcChildCreate(fn_1_708, 100, 0x1000, 0, lbl_1_bss_0->objman);
    }
}

/* 0x15C */ HuVecF lbl_1_data_15C = { 0.0f, 650.0f, -900.0f };
/* 0x168 */ float lbl_1_data_168[8] = { 20.0f, 120.0f, 220.0f, 320.0f, 370.0f, 320.0f, 220.0f, 120.0f };
/* 0x188 */ float lbl_1_data_188[8] = { 1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.7f, 0.8f, 0.9f };
/* 0x1A8 */ HuVecF lbl_1_data_1A8[2] = { { 270.0f, 0.0f, 200.0f }, { 5000.0f, 0.0f, 5000.0f } };

/* 594 insns */
void fn_1_944(s32 dir)
{
    MGFREE_PANEL *panel;
    s32 i;
    s32 count;
    s32 max;
    float t;
    float rad;
    float angle;
    HuVecF pos;

    fn_1_A454();
    lbl_1_bss_4->genre += dir;
    if (lbl_1_bss_4->genre < 0) {
        lbl_1_bss_4->genre += 8;
    }
    lbl_1_bss_4->genre %= 8;
    HuAudFXPlay(1267);
    if (dir > 0) {
        fn_1_8C0();
        panel = lbl_1_bss_0->panel;
        i = 8;
        while (i-- != 0) {
            panel->slot++;
            panel->slot = panel->slot % 8;
            panel++;
        }
    } else if (dir < 0) {
        fn_1_684();
        panel = lbl_1_bss_0->panel;
        i = 8;
        while (i-- != 0) {
            panel->slot--;
            if (panel->slot < 0) {
                panel->slot += 8;
            }
            panel++;
        }
    }
    max = 15;
    count = 0;
    Hu3DModelAttrSet(lbl_1_bss_0->mdl[12], HU3D_ATTR_DISPOFF);
    panel = lbl_1_bss_0->panel;
    i = 8;
    while (i-- != 0) {
        angle = 90.0f;
        angle += 45.0f * panel->slot;
        if (angle > 360.0f) {
            angle -= 360.0f;
        }
        panel->time = 0.0f;
        panel->angleStart = panel->angle;
        panel->yOfsStart = panel->yOfs;
        panel->scaleStart = panel->scale;
        panel->angleEnd = angle;
        panel->yOfsEnd = lbl_1_data_168[panel->slot];
        panel->scaleEnd = lbl_1_data_188[panel->slot];
        if (dir < 0 && panel->angleStart < panel->angleEnd) {
            panel->angleStart += 360.0f;
        }
        panel++;
    }
    while (count != max) {
        count++;
        panel = lbl_1_bss_0->panel;
        t = (float)count / max;
        t = sin(M_PI * t / 2.0);
        t = sin(M_PI * t / 2.0);
        i = 8;
        while (i-- != 0) {
            panel->angle = fn_1_2B4(panel->angleEnd, panel->angleStart, t);
            panel->yOfs = fn_1_2B4(panel->yOfsEnd, panel->yOfsStart, t);
            panel->scale = fn_1_2B4(panel->scaleEnd, panel->scaleStart, t);
            panel++;
        }
        panel = lbl_1_bss_0->panel;
        i = 8;
        while (i-- != 0) {
            rad = M_PI * panel->angle / 180.0;
            pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[0].x * cos(rad);
            pos.y = lbl_1_data_15C.y + panel->yOfs;
            pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[0].z * sin(rad);
            Hu3DModelPosSetV(panel->mdlId, &pos);
            Hu3DModelScaleSet(panel->mdlId, panel->scale, panel->scale, panel->scale);
            panel++;
        }
        HuPrcVSleep();
    }
    panel = lbl_1_bss_0->panel;
    i = 8;
    while (i-- != 0) {
        t = (float)count / max;
        panel->angle = fn_1_2B4(panel->angleEnd, panel->angleStart, t);
        panel->yOfs = fn_1_2B4(panel->yOfsEnd, panel->yOfsStart, t);
        panel->scale = fn_1_2B4(panel->scaleEnd, panel->scaleStart, t);
        if (panel->angle >= 360.0f) {
            panel->angle -= 360.0f;
        }
        if (panel->angle >= 360.0f) {
            panel->angle -= 360.0f;
        }
        if (panel->angle >= 360.0f) {
            panel->angle -= 360.0f;
        }
        rad = M_PI * panel->angle / 180.0;
        pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[0].x * cos(rad);
        pos.y = lbl_1_data_15C.y + panel->yOfs;
        pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[0].z * sin(rad);
        Hu3DModelPosSetV(panel->mdlId, &pos);
        Hu3DModelScaleSet(panel->mdlId, panel->scale, panel->scale, panel->scale);
        panel++;
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdl[12], HU3D_ATTR_DISPOFF);
    Hu3DMotionTimeSet(lbl_1_bss_0->mdl[12], 0.0f);
}

/* 0x1C0 */ HuVecF lbl_1_data_1C0[2] = { { -60.0f, -80.0f, 400.0f }, { 2000.0f, -80.0f, 400.0f } };

/* 183 insns */
void fn_1_128C(void)
{
    s32 count;
    s32 mgIdx;
    s32 loopF;
    char *movie;
    s32 thpId;

    thpId = -1;
    loopF = TRUE;
    while (loopF) {
        switch (lbl_1_bss_0->moviePhase) {
            case 0:
                OSReport("\t\tMovie Phase : \217\211\212\372\211\273\n");
                if (thpId >= 0) {
                    HuTHPClose();
                    Hu3DModelMatHookSet(lbl_1_bss_0->mdl[1], NULL);
                    thpId = -1;
                }
                count = 120;
                OSReport("\t\tMovie Phase : \212J\216n\203J\203E\203\223\203g\212J\216n\n");
                lbl_1_bss_0->moviePhase = 1;
                break;
            case 1:
                if (--count == 0) {
                    OSReport("\t\tMovie Phase : \212J\216n\203J\203E\203\223\203g\217I\227\271\n");
                    OSReport("\t\tMovie Phase : \203\200\201[\203r\201[\217I\227\271\221\322\213@\n");
                    lbl_1_bss_0->moviePhase = 2;
                }
                break;
            case 2:
                if (!HuTHPProcCheck()) {
                    OSReport("\t\tMovie Phase : \203\200\201[\203r\201[\217I\227\271\n");
                    lbl_1_bss_0->moviePhase = 3;
                }
                break;
            case 3:
                mgIdx = fn_1_A4DC();
                if (mgIdx >= 0) {
                    movie = mgDataTbl[mgIdx].movie[0];
                    if (mgIdx + GW_MGNO_BASE == 519) {
                        movie = mgDataTbl[mgIdx].movie[fn_1_4D4C()];
                    }
                    OSReport("\t\tMovie Phase : \203\200\201[\203r\201[\223\307\202\335\215\236\202\335\212J\216n\n");
                    thpId = HuTHPSprCreateVol(movie, 1, 0, 0.0f);
                    lbl_1_bss_0->moviePhase = 4;
                }
                break;
            case 4:
                if (HuTHPStartCheck()) {
                    OSReport("\t\tMovie Phase : \203\200\201[\203r\201[\223\307\202\335\215\236\202\335\217I\227\271\n");
                    Hu3DModelMatHookSet(lbl_1_bss_0->mdl[1], HuTHPMatHook);
                    lbl_1_bss_0->moviePhase = 5;
                }
                break;
            case 5:
                break;
            case 6:
                if (thpId >= 0) {
                    HuTHPClose();
                    Hu3DModelMatHookSet(lbl_1_bss_0->mdl[1], NULL);
                    thpId = -1;
                }
                lbl_1_bss_0->moviePhase = 5;
                break;
            case 7:
                if (thpId >= 0) {
                    HuTHPClose();
                    Hu3DModelMatHookSet(lbl_1_bss_0->mdl[1], NULL);
                    thpId = -1;
                }
                if (!HuTHPProcCheck()) {
                    loopF = FALSE;
                }
                break;
        }
        HuPrcVSleep();
    }
    lbl_1_bss_0->movieProc = 0;
    HuPrcEnd();
}
#ifdef __MWERKS__
#endif

/* 20 insns */
void fn_1_1568(void)
{
    lbl_1_bss_0->moviePhase = 7;
    while (lbl_1_bss_0->movieProc != 0) {
        HuPrcVSleep();
    }
}

/* 156 insns */
void fn_1_15B8(void)
{
    s32 mgIdx = fn_1_A4DC();

    if (lbl_1_bss_0->animId >= 0) {
        Hu3DAnimKill(lbl_1_bss_0->animId);
    }
    if (mgIdx >= 0) {
        if (mgIdx + GW_MGNO_BASE == 519) {
            switch (fn_1_4D4C()) {
                case 0:
                    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgAnim[mgIdx], lbl_1_bss_0->mdl[1], "mg_shot");
                    break;
                case 1:
                    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->anim92C[0], lbl_1_bss_0->mdl[1], "mg_shot");
                    break;
                case 2:
                    lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->anim92C[1], lbl_1_bss_0->mdl[1], "mg_shot");
                    break;
            }
        } else {
            lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->mgAnim[mgIdx], lbl_1_bss_0->mdl[1], "mg_shot");
        }
        lbl_1_bss_0->moviePhase = 0;
        if (lbl_1_bss_0->movieProc == 0) {
            lbl_1_bss_0->movieProc = HuPrcChildCreate(fn_1_128C, 200, 0x1000, 0, lbl_1_bss_0->objman);
        }
    } else {
        lbl_1_bss_0->animId = Hu3DAnimCreate(lbl_1_bss_0->anim934, lbl_1_bss_0->mdl[1], "mg_shot");
        lbl_1_bss_0->moviePhase = 6;
    }
}

/* 116 insns */
void fn_1_1828(void)
{
    s32 time;

    if (lbl_1_bss_0->cam >= 0) {
        Hu3DCameraMotionOff(lbl_1_bss_0->mdl[lbl_1_bss_0->cam]);
        Hu3DModelAttrSet(lbl_1_bss_0->mdl[lbl_1_bss_0->cam], HU3D_MOTATTR_PAUSE);
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdl[lbl_1_bss_0->camNext], HU3D_MOTATTR_PAUSE);
    Hu3DCameraMotionOn(lbl_1_bss_0->mdl[lbl_1_bss_0->camNext], HU3D_CAM4);
    Hu3DCameraMotionStart(lbl_1_bss_0->mdl[lbl_1_bss_0->camNext], HU3D_CAM4);
    lbl_1_bss_0->cam = lbl_1_bss_0->camNext;
    time = Hu3DMotionMaxTimeGet(lbl_1_bss_0->mdl[lbl_1_bss_0->camNext]);
    while (time-- != 0) {
        HuPrcVSleep();
    }
    fn_1_1C8(2);
    HuPrcEnd();
}

/* 99 insns */
void fn_1_19F8(s32 cam)
{
    fn_1_1E4(2);
    if (lbl_1_bss_0->cam == cam) {
        fn_1_1C8(2);
        return;
    }
    lbl_1_bss_0->camNext = cam;
    if (cam < 0) {
        if (lbl_1_bss_0->cam >= 0) {
            Hu3DCameraMotionOff(lbl_1_bss_0->mdl[lbl_1_bss_0->cam]);
            Hu3DModelAttrSet(lbl_1_bss_0->mdl[lbl_1_bss_0->cam], HU3D_MOTATTR_PAUSE);
        }
        lbl_1_bss_0->cam = lbl_1_bss_0->camNext;
        fn_1_1C8(2);
    } else {
        fn_1_1E4(2);
        HuPrcChildCreate(fn_1_1828, 100, 0x1000, 0, lbl_1_bss_0->objman);
        HuPrcVSleep();
    }
}

/* 218 insns */
void fn_1_1B84(void)
{
    MGFREE_MDLDATA *data;
    s32 i;
    s32 mdlId;

    for (i = 13; i-- != 0;) {
        data = &lbl_1_data_18[i];
        mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(data->dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_0->mdl[i] = mdlId;
        Hu3DModelCameraSet(mdlId, data->camera);
        Hu3DModelLayerSet(mdlId, data->layer);
        if (data->attr != 0) {
            Hu3DModelAttrSet(mdlId, data->attr);
        }
        if (data->attr2 != 0) {
            Hu3DModelAttrSet(mdlId, data->attr2);
        }
    }
    Hu3DModelPosSetV(lbl_1_bss_0->mdl[1], &lbl_1_data_1C0[0]);
    fn_1_160(lbl_1_bss_0->mdl[12], 0.0f, 300.0f);
    Hu3DModelPosSet(lbl_1_bss_0->mdl[3], 20.0f, 0.0f, 400.0f);
    Hu3DModelPosSet(lbl_1_bss_0->mdl[2], -20.0f, 0.0f, 400.0f);
    Hu3DModelScaleSet(lbl_1_bss_0->mdl[3], 0.8f, 0.8f, 0.8f);
    Hu3DModelScaleSet(lbl_1_bss_0->mdl[2], 0.8f, 0.8f, 0.8f);
    fn_1_160(lbl_1_bss_0->mdl[3], 0.0f, 120.0f);
    fn_1_160(lbl_1_bss_0->mdl[2], 0.0f, 120.0f);
    {
        s32 camData[] = { DATANUM(DATA_mgfree, 0x39) };
        for (i = 1; i-- != 0;) {
            mdlId = Hu3DModelCameraCreate(Hu3DMotionCreate(HuDataSelHeapReadNum(camData[i], HU_MEMNUM_OVL, HEAP_MODEL)), HU3D_CAM4);
            lbl_1_bss_0->mdl[i + 13] = mdlId;
            Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DCameraMotionOff(mdlId);
        }
    }
}

/* 25 insns */
void ObjectSetup(void)
{
    _SetFlag(FLAG_MGINST_ON);
    mgPauseExitF = TRUE;
    GwSystem.subGameNo = 0;
    HuPrcChildCreate(fn_1_1F50, 200, 0x3000, 0, HuPrcCurrentGet());
}

/* 67 insns */
void fn_1_1F50(void)
{
    OMOVLHIS *his = omOvlHisGet(0);
    s32 loopF;

    fn_1_21AC();
    loopF = TRUE;
    while (loopF) {
        switch (his->evtno) {
            case 0:
                fn_1_2C40();
                break;
            case 1:
                fn_1_37A4();
                break;
            case 2:
                fn_1_3C8C();
                break;
            case 3:
                fn_1_205C();
                break;
            case 4:
                HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
                lbl_1_bss_0->streamNo = -1;
                fn_1_114(60);
                loopF = FALSE;
                break;
        }
        HuPrcVSleep();
    }
    fn_1_45A4();
    omOvlReturnEx(1, 1);
    HuPrcEnd();
}

/* 84 insns */
void fn_1_205C(void)
{
    s32 mgNo;

    HuAudSStreamFadeOut(lbl_1_bss_0->streamNo, 1000);
    lbl_1_bss_0->streamNo = -1;
    fn_1_114(60);
    fn_1_1568();
    fn_1_26C(1);
    HuDataDirClose(DATA_mgfree);
    HuDataDirClose(DATA_instpic);
    GwSystem.mgNo = lbl_1_bss_0->mgNo;
    mgNo = lbl_1_bss_0->mgNo + GW_MGNO_BASE;
    GWMgUnlockSet(mgNo);
    GwSystem.mgNo = mgNo - GW_MGNO_BASE;
    GWMgInstFSet(TRUE);
    omOvlCallEx(DLL_instdll, 1, 0, 0);
    while (1) {
        HuPrcVSleep();
    }
}

/* 677 insns */
void fn_1_21AC(void)
{
    s32 k;
    MGFREE_MDLDATA *data;
    MGFREE_PANEL *panel;
    s32 i;
    ANIMDATA *anim;
    s32 mdlId;
    HU3DMODELID modelId;
    s32 j;
    s32 lightId;
    s32 slot;
    HU3DMOTID motId;
    OMOVLHIS *his;
    float angle;

    his = omOvlHisGet(0);
    lbl_1_bss_4 = (MGFREE_MODEWORK *)mgModeWork;
    lbl_1_bss_0 = &lbl_1_bss_8;
    HuDataSelHeapReadNum(DATA_instpic, HU_MEMNUM_OVL, HEAP_MODEL);
    HuAR_DVDtoARAM(DATA_mgfree);
    lbl_1_bss_0->cam = -1;
    lbl_1_bss_0->animId = -1;
    lbl_1_bss_0->proc1D4 = 0;
    lbl_1_bss_0->proc1D8 = 0;
    lbl_1_bss_0->movieProc = 0;
    lbl_1_bss_0->streamNo = -1;
    lbl_1_bss_0->moviePhase = 0;
    {
        HuVecF lightPos = { 3000.0f, 3000.0f, 3000.0f };
        HuVecF lightDir = { -1.0f, -1.0f, -1.0f };
        lbl_1_bss_0->objman = omInitObjMan(200, 1000);
        omGameSysInit(lbl_1_bss_0->objman);
        Hu3DCameraCreate(HU3D_CAM4);
        Hu3DCameraPerspectiveSet(HU3D_CAM4, 60.0f, 20.0f, 60000.0f, 1.2f);
        Hu3DCameraViewportSet(HU3D_CAM4, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        Hu3DCameraScissorSet(HU3D_CAM4, 0, 0, 640, 480);
        lightId = Hu3DGLightCreate(0.0f, 1000.0f, 1000.0f, 0.0f, -1.0f, -1.0f, 255, 255, 255);
        Hu3DGLightStaticSet(lightId, 1);
        Hu3DGLightPosSetV(lightId, &lightPos, &lightDir);
    }
    HuWinInit(1);
    if (his->evtno == 0) {
        _SetFlag(FLAG_INST_NOHISCHG);
        _SetFlag(FLAG_INST_MGMODE);
        mgInstExitF = 1;
        lbl_1_bss_4->genre = 0;
        lbl_1_bss_4->unk4 = 0;
        lbl_1_bss_4->unk8 = 0;
        lbl_1_bss_4->unkC = 0;
    }
    i = 13;
    while (i-- != 0) {
        data = &lbl_1_data_18[i];
        mdlId = Hu3DModelCreate(HuDataSelHeapReadNum(data->dataNum, HU_MEMNUM_OVL, HEAP_MODEL));
        lbl_1_bss_0->mdl[i] = mdlId;
        Hu3DModelCameraSet(mdlId, data->camera);
        Hu3DModelLayerSet(mdlId, data->layer);
        if (data->attr != 0) {
            Hu3DModelAttrSet(mdlId, data->attr);
        }
        if (data->attr2 != 0) {
            Hu3DModelAttrSet(mdlId, data->attr2);
        }
    }
    Hu3DModelPosSetV(lbl_1_bss_0->mdl[1], &lbl_1_data_1C0[0]);
    fn_1_160(lbl_1_bss_0->mdl[12], 0.0f, 300.0f);
    Hu3DModelPosSet(lbl_1_bss_0->mdl[3], 20.0f, 0.0f, 400.0f);
    Hu3DModelPosSet(lbl_1_bss_0->mdl[2], -20.0f, 0.0f, 400.0f);
    Hu3DModelScaleSet(lbl_1_bss_0->mdl[3], 0.8f, 0.8f, 0.8f);
    Hu3DModelScaleSet(lbl_1_bss_0->mdl[2], 0.8f, 0.8f, 0.8f);
    fn_1_160(lbl_1_bss_0->mdl[3], 0.0f, 120.0f);
    fn_1_160(lbl_1_bss_0->mdl[2], 0.0f, 120.0f);
    {
        s32 camMot[1] = { DATANUM(DATA_mgfree, 0x39) };
        i = 1;
        while (i-- != 0) {
            mdlId = Hu3DModelCameraCreate(Hu3DMotionCreate(HuDataSelHeapReadNum(camMot[i], HU_MEMNUM_OVL, HEAP_MODEL)), HU3D_CAM4);
            lbl_1_bss_0->mdl[i + 13] = mdlId;
            Hu3DModelAttrSet(mdlId, HU3D_MOTATTR_PAUSE);
            Hu3DCameraMotionOff(mdlId);
        }
    }
    modelId = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_decathlon, 0), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_0->mdlId = modelId;
    lbl_1_bss_0->pos = lbl_1_data_0[0];
    his = HuDataSelHeapReadNum(DATANUM(DATA_decathlon, 1), HU_MEMNUM_OVL, HEAP_MODEL);
    motId = Hu3DJointMotion(modelId, (void *)his);
    Hu3DMotionSet(modelId, motId);
    Hu3DModelAttrSet(modelId, HU3D_MOTATTR_LOOP);
    Hu3DModelLayerSet(modelId, 4);
    Hu3DModelCameraSet(modelId, HU3D_CAM4);
    Hu3DModelPosSetV(modelId, &lbl_1_bss_0->pos);
    Hu3DModelScaleSet(modelId, 4.0f, 4.0f, 4.0f);
    for (k = 0; k < 8; k++) {
        if (k != 0) {
            lbl_1_data_188[k] = 0.7 * lbl_1_data_188[k - 1];
        } else {
            lbl_1_data_188[k] = 1.0f;
        }
    }
    lbl_1_data_188[7] = lbl_1_data_188[1];
    lbl_1_data_188[6] = lbl_1_data_188[2];
    lbl_1_data_188[5] = lbl_1_data_188[3];
    for (k = 0; k < 8; k++) {
        slot = (8 - lbl_1_bss_4->genre + k) % 8;
        panel = &lbl_1_bss_0->panel[slot];
        angle = 90.0f + 45.0f * k;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }
        panel->mdlId = lbl_1_bss_0->mdl[slot + 4];
        panel->angle = angle;
        panel->yOfs = lbl_1_data_168[k];
        panel->scale = lbl_1_data_188[k];
        panel->slot = k;
    }
    for (k = 0; mgDataTbl[k].ovl != 0xFFFF; k++) {
        j = 8;
        while (j-- != 0) {
            if (lbl_1_data_11C[j].mgType == mgDataTbl[k].type) {
                anim = HuSprAnimRead(HuDataSelHeapReadNum(mgDataTbl[k].instPic[0], HU_MEMNUM_OVL, HEAP_MODEL));
                HuSprAnimLock(anim);
                lbl_1_bss_0->mgAnim[k] = anim;
                break;
            }
        }
    }
    for (k = 0; k < 2; k++) {
        anim = HuSprAnimRead(HuDataSelHeapReadNum(mgDataTbl[18].instPic[k + 1], HU_MEMNUM_OVL, HEAP_MODEL));
        HuSprAnimLock(anim);
        lbl_1_bss_0->anim92C[k] = anim;
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_mgfree, 0x1C), HU_MEMNUM_OVL, HEAP_MODEL));
    HuSprAnimLock(anim);
    lbl_1_bss_0->anim934 = anim;
}

/* 729 insns */
void fn_1_2C40(void)
{
    HuVecF pos;
    CAMMOTIONWORK *path;
    int num;
    MGFREE_PANEL *panel;
    s32 j;
    s32 i;
    s32 k;
    s32 l;
    float angle;
    float r;
    float t;
    float t2;
    float t3;
    float t4;

    fn_1_26C(2);
    panel = lbl_1_bss_0->panel;
    j = 8;
    while (j-- != 0) {
        angle = M_PI * panel->angle / 180.0;
        pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[1].x * cos(angle);
        pos.y = lbl_1_data_15C.y + panel->yOfs;
        pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[1].z * sin(angle);
        Hu3DModelPosSetV(panel->mdlId, &pos);
        Hu3DModelScaleSet(panel->mdlId, 0.0f, 0.0f, 0.0f);
        panel++;
    }
    pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[0].x * cos(M_PI / 2);
    pos.y = lbl_1_data_15C.y + lbl_1_data_168[0];
    pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[0].z * sin(M_PI / 2);
    Hu3DModelPosSetV(lbl_1_bss_0->mdl[12], &pos);
    Hu3DModelAttrSet(lbl_1_bss_0->mdl[12], HU3D_ATTR_DISPOFF);
    Hu3DModelPosSetV(lbl_1_bss_0->mdl[1], &lbl_1_data_1C0[1]);
    Hu3DModelTPLvlSet(lbl_1_bss_0->mdl[3], 0.0f);
    Hu3DModelTPLvlSet(lbl_1_bss_0->mdl[2], 0.0f);
    lbl_1_bss_0->pos = lbl_1_data_0[1];
    Hu3DModelPosSetV(lbl_1_bss_0->mdlId, &lbl_1_bss_0->pos);
    lbl_1_bss_0->streamNo = HuAudBGMPlay(35);
    path = lbl_1_bss_0->camPath;
    num = 31;
    path = lbl_1_bss_0->camPath;
    lbl_1_bss_0->camPathNum = CamMotionExPathGet(lbl_1_bss_0->mdl[13], 6, 48.0f, 0, &path, &num);
    path = &lbl_1_bss_0->camPath[lbl_1_bss_0->camPathNum - 1];
    lbl_1_bss_4->camPos = path->pos;
    lbl_1_bss_4->camUp = path->up;
    lbl_1_bss_4->camTarget = path->target;
    lbl_1_bss_4->camFov = path->fov;
    Hu3DCameraPosSetV(HU3D_CAM4, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
    Hu3DCameraPerspectiveSet(HU3D_CAM4, lbl_1_bss_4->camFov, 20.0f, 60000.0f, 1.2f);
    fn_1_19F8(13);
    fn_1_6BC4(1, lbl_1_bss_4->unk4, lbl_1_bss_4->unk8, lbl_1_bss_4->unkC);
    fn_1_A0(60);
    for (i = 0; i <= 60.0f; i++) {
        t = i / 60.0f;
        t = sin(M_PI * t / 2.0);
        t = sin(M_PI * t / 2.0);
        lbl_1_bss_0->pos.y = lbl_1_data_0[1].y + t * (lbl_1_data_0[0].y - lbl_1_data_0[1].y);
        Hu3DModelPosSetV(lbl_1_bss_0->mdlId, &lbl_1_bss_0->pos);
        t = i / 60.0f;
        Hu3DModelRotSet(lbl_1_bss_0->mdlId, 0.0f, 1080.0f * t, 0.0f);
        HuPrcVSleep();
    }
    k = 60;
    while (k-- != 0) {
        t2 = k / 60.0f;
        t2 = sin(M_PI * t2 / 2.0);
        t2 = sin(M_PI * t2 / 2.0);
        panel = lbl_1_bss_0->panel;
        j = 8;
        while (j-- != 0) {
            angle = M_PI * panel->angle / 180.0;
            pos.y = lbl_1_data_15C.y + panel->yOfs;
            r = lbl_1_data_1A8[0].x + t2 * (lbl_1_data_1A8[1].x - lbl_1_data_1A8[0].x);
            pos.x = lbl_1_data_15C.x + r * cos(angle);
            r = lbl_1_data_1A8[0].z + t2 * (lbl_1_data_1A8[1].z - lbl_1_data_1A8[0].z);
            pos.z = lbl_1_data_15C.z + r * sin(angle);
            Hu3DModelPosSetV(panel->mdlId, &pos);
            r = panel->scale * (1.0f - t2);
            if (r < 1e-05) {
                r = 1e-05f;
            }
            Hu3DModelScaleSet(panel->mdlId, r, r, r);
            panel++;
        }
        HuPrcVSleep();
    }
    Hu3DModelAttrReset(lbl_1_bss_0->mdl[12], HU3D_ATTR_DISPOFF);
    fn_1_A068();
    l = 60;
    while (l-- != 0) {
        t3 = l / 60.0f;
        pos = lbl_1_data_1C0[0];
        pos.x = lbl_1_data_1C0[0].x + t3 * (lbl_1_data_1C0[1].x - lbl_1_data_1C0[0].x);
        Hu3DModelPosSetV(lbl_1_bss_0->mdl[1], &pos);
        HuPrcVSleep();
    }
    for (j = 0; j <= 30.0f; j++) {
        t4 = j / 30.0f;
        Hu3DModelTPLvlSet(lbl_1_bss_0->mdl[3], t4);
        Hu3DModelTPLvlSet(lbl_1_bss_0->mdl[2], t4);
        HuPrcVSleep();
    }
}

/* 314 insns */
void fn_1_37A4(void)
{
    HuVecF pos;
    CAMMOTIONWORK *path;
    int num;
    MGFREE_PANEL *panel;
    s32 i;
    float angle;

    fn_1_26C(2);
    panel = lbl_1_bss_0->panel;
    i = 8;
    while (i-- != 0) {
        angle = (M_PI * panel->angle) / 180.0;
        pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[0].x * cos(angle);
        pos.y = lbl_1_data_15C.y + panel->yOfs;
        pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[0].z * sin(angle);
        Hu3DModelPosSetV(panel->mdlId, &pos);
        Hu3DModelScaleSet(panel->mdlId, panel->scale, panel->scale, panel->scale);
        panel++;
    }
    pos.x = lbl_1_data_15C.x + lbl_1_data_1A8[0].x * cos(M_PI / 2);
    pos.y = lbl_1_data_15C.y + lbl_1_data_168[0];
    pos.z = lbl_1_data_15C.z + lbl_1_data_1A8[0].z * sin(M_PI / 2);
    Hu3DModelPosSetV(lbl_1_bss_0->mdl[12], &pos);
    lbl_1_bss_0->streamNo = HuAudBGMPlay(35);
    path = lbl_1_bss_0->camPath;
    num = 31;
    path = lbl_1_bss_0->camPath;
    lbl_1_bss_0->camPathNum = CamMotionExPathGet(lbl_1_bss_0->mdl[13], 6, 48.0f, 0, &path, &num);
    path = &lbl_1_bss_0->camPath[lbl_1_bss_0->camPathNum - 1];
    lbl_1_bss_4->camPos = path->pos;
    lbl_1_bss_4->camUp = path->up;
    lbl_1_bss_4->camTarget = path->target;
    lbl_1_bss_4->camFov = path->fov;
    Hu3DCameraPosSetV(16, &lbl_1_bss_4->camPos, &lbl_1_bss_4->camUp, &lbl_1_bss_4->camTarget);
    Hu3DCameraPerspectiveSet(16, lbl_1_bss_4->camFov, 20.0f, 60000.0f, 1.2f);
    fn_1_19F8(13);
    fn_1_6BC4(0, lbl_1_bss_4->unk4, lbl_1_bss_4->unk8, lbl_1_bss_4->unkC);
    fn_1_A0(60);
}
#ifdef __MWERKS__
#endif
#ifdef __MWERKS__
#endif

/* 582 insns */
void fn_1_3C8C(void)
{
    s32 mode;
    s32 mgIdx;
    MGDATA *mgData;

    mode = 0;
    lbl_1_bss_0->mgNo = -1;
    while (lbl_1_bss_0->mgNo < 0) {
        HuPrcVSleep();
        if (!fn_1_A544()) {
            continue;
        }
        switch (mode) {
        case 0:
            if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_4D20(5);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_4D20(4);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
                fn_1_4D20(2);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
                fn_1_4D20(3);
            }
            if (HuPadBtnDown[0] & PAD_TRIGGER_L) {
                fn_1_944(-1);
            } else if (HuPadBtnDown[0] & PAD_TRIGGER_R) {
                fn_1_944(1);
            } else if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                mgIdx = fn_1_A4DC();
                if (mgIdx >= 0) {
                    mgData = &mgDataTbl[mgIdx];
                    fn_1_4D20(19);
                    switch (mgData->type) {
                    case MG_TYPE_4P:
                    case MG_TYPE_BATTLE:
                    case MG_TYPE_KUPA:
                    case MG_TYPE_DONKEY:
                        mode = 7;
                        break;
                    case MG_TYPE_2VS2:
                        HuAudFXPlay(1);
                        mode = 1;
                        break;
                    case MG_TYPE_1VS3:
                        HuAudFXPlay(1);
                        mode = 2;
                        break;
                    case MG_TYPE_KETTOU:
                        HuAudFXPlay(1);
                        mode = 3;
                        break;
                    case MG_TYPE_LAST:
                        HuAudFXPlay(1);
                        mode = 4;
                        break;
                    case MG_TYPE_SD:
                        break;
                    }
                } else {
                    HuAudFXPlay(4);
                }
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                mode = 8;
            }
            break;
        case 1:
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                GwPlayerConf[fn_1_4D60(0)].grp = 0;
                GwPlayerConf[fn_1_4D60(1)].grp = 0;
                GwPlayerConf[fn_1_4D60(2)].grp = 1;
                GwPlayerConf[fn_1_4D60(3)].grp = 1;
                mode = 7;
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                mode = 0;
                fn_1_4D20(21);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_4D20(8);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_4D20(7);
            }
            break;
        case 2:
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                GwPlayerConf[fn_1_4D60(0)].grp = 0;
                GwPlayerConf[fn_1_4D60(1)].grp = 1;
                GwPlayerConf[fn_1_4D60(2)].grp = 1;
                GwPlayerConf[fn_1_4D60(3)].grp = 1;
                if (fn_1_A4DC() + 501 == 519) {
                    HuAudFXPlay(1);
                    fn_1_4D20(20);
                    mode = 5;
                } else {
                    mode = 7;
                }
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                mode = 0;
                fn_1_4D20(21);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_4D20(10);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_4D20(9);
            }
            break;
        case 3:
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                GwPlayerConf[fn_1_4D60(0)].grp = 0;
                GwPlayerConf[fn_1_4D60(1)].grp = 1;
                GwPlayerConf[fn_1_4D60(2)].grp = 3;
                GwPlayerConf[fn_1_4D60(3)].grp = 3;
                if (fn_1_A4DC() + 501 == 552) {
                    HuAudFXPlay(1);
                    fn_1_4D20(20);
                    mode = 6;
                } else {
                    mode = 7;
                }
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                mode = 0;
                fn_1_4D20(21);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_4D20(12);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_4D20(11);
            }
            break;
        case 4:
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                s32 difTbl[4] = { 0, 1, 2, 3 };
                GwPlayerConf[0].dif = difTbl[fn_1_4D4C()];
                GwSystem.subGameNo = -1;
                mode = 7;
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                mode = 0;
                fn_1_4D20(21);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_RIGHT) {
                fn_1_4D20(14);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_LEFT) {
                fn_1_4D20(13);
            }
            break;
        case 5:
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                s32 subGameNo = fn_1_4D4C();
                GwSystem.subGameNo = subGameNo;
                mode = 7;
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                fn_1_4D20(22);
                mode = 2;
            } else if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
                fn_1_4D20(15);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
                fn_1_4D20(16);
            }
            break;
        case 6: {
            s32 subModeTbl[3] = { 0, 1, 2 };
            if (HuPadBtnDown[0] & PAD_BUTTON_A) {
                mgSubMode = subModeTbl[fn_1_4D4C()];
                mode = 7;
            } else if (HuPadBtnDown[0] & PAD_BUTTON_B) {
                HuAudFXPlay(3);
                fn_1_4D20(22);
                mode = 3;
            } else if (HuPadDStkRep[0] & PAD_BUTTON_UP) {
                fn_1_4D20(17);
            } else if (HuPadDStkRep[0] & PAD_BUTTON_DOWN) {
                fn_1_4D20(18);
            }
            break;
        }
        case 7:
            if (fn_1_A4DC() >= 0) {
                HuAudFXPlay(2);
                lbl_1_bss_0->mgNo = fn_1_A4DC();
                fn_1_26C(3);
            } else {
                mode = 0;
            }
            break;
        case 8:
            HuAudFXPlay(3);
            fn_1_26C(4);
            lbl_1_bss_0->mgNo = 0;
            break;
        }
    }
    fn_1_6B80(&lbl_1_bss_4->unk4, &lbl_1_bss_4->unk8, &lbl_1_bss_4->unkC);
}

/* 66 insns */
void fn_1_45A4(void)
{
    fn_1_1568();
    HuARDirFree(DATA_mgfree);
    HuDataDirClose(DATA_mgfree);
    HuDataDirClose(DATA_instpic);
    mgInstExitF = FALSE;
    mgPauseExitF = FALSE;
    mgSubMode = 0;
    GWMgInstFSet(TRUE);
    fn_1_26C(0);
    _ClearFlag(FLAG_INST_NOHISCHG);
    _ClearFlag(FLAG_INST_MGMODE);
    memset(lbl_1_bss_4, 0, sizeof(MGFREE_MODEWORK));
}

/* 12 insns */
u32 fn_1_46AC(s32 listNo)
{
    return mgDataTbl[lbl_1_bss_974->list[listNo].mgIdx].nameMes;
}

