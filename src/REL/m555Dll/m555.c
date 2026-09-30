/*
 * m555dll -- a KETTOU duel (overlay #69): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, a spark particle and the sound helpers.
 * Written from the reference assembly, functions in reference order; line
 * ranges are into build/mp5-asm/m555Dll/asm/REL/m555Dll/m555.s. Adapted from
 * m541.c and m553.c, which carry most of the same functions.
 *
 * _prolog and _epilog are not reproduced.
 */

#include "game/object.h"
#include "game/gamework.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/hu3d.h"
#include "game/memory.h"
#include "game/audio.h"
#include "game/frand.h"
#include "game/pad.h"
#include "game/sprite.h"
#include "game/printfunc.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"

#include "datadir_enum.h"

#include "REL/m555Dll/m555.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M555_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

void ObjectSetup(void);
void fn_1_308(s16 mode, s16 frameNo);
void fn_1_33C(s16 mode, s16 frameNo);
void fn_1_368(s16 mode, s16 frameNo);
void fn_1_394(s16 mode, s16 frameNo);
void fn_1_3C0(s16 mode, s16 frameNo);
void fn_1_3EC(s16 mode, s16 frameNo);
void fn_1_418(s16 mode, s16 frameNo);
void fn_1_444(s16 mode, s16 frameNo);
void fn_1_464(s16 mode, s16 frameNo);
void fn_1_490(OMOBJ *obj);
/* game.c defines these returning s16; the hooks test the whole register, as retail's calls without a prototype did. */
s32 fn_1_69C4(M555_WORK *work);
s32 fn_1_6A0C(void);
s32 fn_1_6A60(void);
s32 fn_1_6AF0(void);
s32 fn_1_6DF0(void);
s32 fn_1_6ECC(void);
s32 fn_1_6F3C(void);
s32 fn_1_71B4(void);
s32 fn_1_7364(void);
void fn_1_494(s16 no);
void fn_1_EDC(void);
void fn_1_13E4(void);
s16 fn_1_1BD4(M555_WORK *work, s16 padNo, s16 no);
void fn_1_1FC0(void);
void fn_1_1FC4(s16 padNo);
s16 fn_1_2800(HuVecF pos, HuVecF vel, float scale, float scaleSpeed);
void fn_1_28F0(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_308,
    fn_1_33C,
    fn_1_368,
    fn_1_394,
    fn_1_3C0,
    fn_1_3EC,
    fn_1_418,
    fn_1_444,
    fn_1_464
};

/* Two motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][2] = {
    { 0x008C001C, 0x008700BE },
    { 0x0033001C, 0x002E00BE },
    { 0x00B7001C, 0x00B200BE },
    { 0x00ED001C, 0x00E800BE },
    { 0x00E6001C, 0x00E100BE },
    { 0x0017001C, 0x001200BE },
    { 0x00E0001C, 0x00DB00BE },
    { 0x002D001C, 0x002800BE },
    { 0x00C9001C, 0x00C400BE },
    { 0x00B0001C, 0x009C00BE },
    { 0x00B0001C, 0x009C00BE },
    { 0x00B0001C, 0x009C00BE },
    { 0x00B0001C, 0x009C00BE }
};

/* files/data/m555.bin: the stage models (passed to fn_1_1A9A4). */
unsigned int lbl_1_data_90[48] = {
    DATANUM(DATA_m555, 0x00), DATANUM(DATA_m555, 0x01), DATANUM(DATA_m555, 0x02), DATANUM(DATA_m555, 0x03),
    DATANUM(DATA_m555, 0x04), DATANUM(DATA_m555, 0x05), DATANUM(DATA_m555, 0x06), DATANUM(DATA_m555, 0x07),
    DATANUM(DATA_m555, 0x08), DATANUM(DATA_m555, 0x09), DATANUM(DATA_m555, 0x0A), DATANUM(DATA_m555, 0x0B),
    DATANUM(DATA_m555, 0x0C), DATANUM(DATA_m555, 0x0D), DATANUM(DATA_m555, 0x0E), DATANUM(DATA_m555, 0x0F),
    DATANUM(DATA_m555, 0x10), DATANUM(DATA_m555, 0x11), DATANUM(DATA_m555, 0x12), DATANUM(DATA_m555, 0x13),
    DATANUM(DATA_m555, 0x14), DATANUM(DATA_m555, 0x15), DATANUM(DATA_m555, 0x16), DATANUM(DATA_m555, 0x17),
    DATANUM(DATA_m555, 0x18), DATANUM(DATA_m555, 0x19), DATANUM(DATA_m555, 0x1A), DATANUM(DATA_m555, 0x1B),
    DATANUM(DATA_m555, 0x1C), DATANUM(DATA_m555, 0x1D), DATANUM(DATA_m555, 0x1E), DATANUM(DATA_m555, 0x1F),
    DATANUM(DATA_m555, 0x20), DATANUM(DATA_m555, 0x21), DATANUM(DATA_m555, 0x22), DATANUM(DATA_m555, 0x23),
    DATANUM(DATA_m555, 0x24), DATANUM(DATA_m555, 0x25), DATANUM(DATA_m555, 0x26), DATANUM(DATA_m555, 0x27),
    DATANUM(DATA_m555, 0x28), DATANUM(DATA_m555, 0x29), DATANUM(DATA_m555, 0x2A), DATANUM(DATA_m555, 0x2B),
    DATANUM(DATA_m555, 0x2C), DATANUM(DATA_m555, 0x2D), DATANUM(DATA_m555, 0x2E), DATANUM(DATA_m555, 0x2F)
};

/* The four cameras fn_1_494 can create; only camera 0 is. */
M555_CAMERAINIT lbl_1_data_150[4] = {
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1250.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, 1250.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 20.0f }, { -35.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_220[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1BD4's and fn_1_1FC4's debug lines. */
char lbl_1_data_240[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_26E[] = "OBJW %d";
char lbl_1_data_276[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_29B[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* fn_1_2B10's sound effects. */
s16 lbl_1_data_2B8[12] = {
    0x893, 0x894, 0x895, 0x896, 0x897, 0x898, 0x899, 0x89A, 0x89B, 0x89C, 0x89D, 0x89E
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s16 lbl_1_bss_302A;                /* unreferenced; dtk sizes lbl_1_bss_3028 8 */
HU3DMODELID lbl_1_bss_3028;
s32 lbl_1_bss_3024;                /* unreferenced; dtk sizes lbl_1_bss_3020 8 */
OMOBJMAN *lbl_1_bss_3020;
M555_WORK lbl_1_bss_2D38;
M555_MODEL lbl_1_bss_1A84[M555_MODEL_MAX];
HU3DMOTID lbl_1_bss_1A7C[2][2];
M555_GAME lbl_1_bss_1894;
M555_DUELLIST lbl_1_bss_120C[2];
M555_UNK11E4 lbl_1_bss_11E4;
M555_UNK11C8 lbl_1_bss_11C8;
M555_UNKB88 lbl_1_bss_B88[50];
M555_UNKB74 lbl_1_bss_B74;
M555_UNK214 lbl_1_bss_214[100];
M555_UNK0C lbl_1_bss_C;
M555_CAMERA *lbl_1_bss_8;
M555_LIGHT *lbl_1_bss_4;
M555_SHADOW *lbl_1_bss_0;

/* asm 61-218, 154 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_3020 = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_3020);
    fn_1_1A9A4(&lbl_1_bss_2D38, lbl_1_bss_1A84, lbl_1_data_90);
    lbl_1_bss_8 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M555_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_8, 0, (sizeof(M555_CAMERA)*4)+8);
    lbl_1_bss_4 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M555_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_4, 0, sizeof(M555_LIGHT));
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M555_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M555_SHADOW));
    fn_1_494(0);
    fn_1_EDC();
    fn_1_13E4();
    fn_1_1AC04(0, lbl_1_data_28[lbl_1_bss_2D38.chr[0].charNo]);
    fn_1_1AC04(1, lbl_1_data_28[lbl_1_bss_2D38.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_1AC24(i, lbl_1_bss_1A7C[i]);
    }
    fn_1_1AC44();
    fn_1_1B2F8();
    omAddObjEx(lbl_1_bss_3020, 32730, 0, 0, -1, fn_1_1AF38);
    omAddObjEx(lbl_1_bss_3020, 32730, 0, 0, -1, fn_1_1B4B0);
    omAddObjEx(lbl_1_bss_3020, 32730, 0, 0, -1, fn_1_490);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 6000);
    MgSeqModeDelaySet(7, 6000);
    MgSeqModeDelaySet(9, 60);
}

void fn_1_308(s16 mode, s16 frameNo)
{
    if(fn_1_69C4(&lbl_1_bss_2D38)) {
        MgSeqModeNext();
    }
}

void fn_1_33C(s16 mode, s16 frameNo)
{
    if(fn_1_6A0C()) {
        MgSeqModeNext();
    }
}

void fn_1_368(s16 mode, s16 frameNo)
{
    if(fn_1_6A60()) {
        MgSeqModeNext();
    }
}

void fn_1_394(s16 mode, s16 frameNo)
{
    if(fn_1_6AF0()) {
        MgSeqModeNext();
    }
}

void fn_1_3C0(s16 mode, s16 frameNo)
{
    if(fn_1_6DF0()) {
        MgSeqModeNext();
    }
}

void fn_1_3EC(s16 mode, s16 frameNo)
{
    if(fn_1_6ECC()) {
        MgSeqModeNext();
    }
}

void fn_1_418(s16 mode, s16 frameNo)
{
    if(fn_1_6F3C()) {
        MgSeqModeNext();
    }
}

void fn_1_444(s16 mode, s16 frameNo)
{
    fn_1_71B4();
}

void fn_1_464(s16 mode, s16 frameNo)
{
    if(fn_1_7364()) {
        MgSeqModeNext();
    }
}

void fn_1_490(OMOBJ *obj)
{
}
void fn_1_494(s16 no)
{
    lbl_1_bss_8[no].no = no;
    lbl_1_bss_8[no].center.x = lbl_1_data_150[no].center.x;
    lbl_1_bss_8[no].center.y = lbl_1_data_150[no].center.y;
    lbl_1_bss_8[no].center.z = lbl_1_data_150[no].center.z;
    lbl_1_bss_8[no].rot.x = lbl_1_data_150[no].rot.x;
    lbl_1_bss_8[no].rot.y = lbl_1_data_150[no].rot.y;
    lbl_1_bss_8[no].rot.z = lbl_1_data_150[no].rot.z;
    lbl_1_bss_8[no].zoom = lbl_1_data_150[no].zoom;
    lbl_1_bss_8[no].aspect = lbl_1_data_150[no].aspect;
    lbl_1_bss_8[no].vpX = lbl_1_data_150[no].vpX;
    lbl_1_bss_8[no].vpY = lbl_1_data_150[no].vpY;
    lbl_1_bss_8[no].vpW = lbl_1_data_150[no].vpW;
    lbl_1_bss_8[no].vpH = lbl_1_data_150[no].vpH;
    lbl_1_bss_8[no].fov = lbl_1_data_150[no].fov;
    Hu3DCameraCreate(lbl_1_data_220[no]);
    Hu3DCameraViewportSet(lbl_1_data_220[no], lbl_1_bss_8[no].vpX, lbl_1_bss_8[no].vpY, lbl_1_bss_8[no].vpW, lbl_1_bss_8[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_220[no], lbl_1_bss_8[no].fov, 20.0f, 40000.0f, lbl_1_bss_8[no].aspect);
    fn_1_964(no);
    Center.x = lbl_1_data_150[0].center.x;
    Center.y = lbl_1_data_150[0].center.y;
    Center.z = lbl_1_data_150[0].center.z;
    CRot.x = lbl_1_data_150[0].rot.x;
    CRot.y = lbl_1_data_150[0].rot.y;
    CRot.z = lbl_1_data_150[0].rot.z;
    CZoom = lbl_1_data_150[no].zoom;
}

void fn_1_964(s16 no)
{
    lbl_1_bss_8[no].pos.x = lbl_1_bss_8[no].center.x+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].pos.y = lbl_1_bss_8[no].center.y+(lbl_1_bss_8[no].zoom*-sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0));
    lbl_1_bss_8[no].pos.z = lbl_1_bss_8[no].center.z+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].up.x = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    lbl_1_bss_8[no].up.y = cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0);
    lbl_1_bss_8[no].up.z = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_220[no], lbl_1_bss_8[no].pos.x, lbl_1_bss_8[no].pos.y, lbl_1_bss_8[no].pos.z,
        lbl_1_bss_8[no].up.x, lbl_1_bss_8[no].up.y, lbl_1_bss_8[no].up.z,
        lbl_1_bss_8[no].center.x, lbl_1_bss_8[no].center.y, lbl_1_bss_8[no].center.z);
}

void fn_1_EDC(void)
{
    Hu3DLighInit();
    lbl_1_bss_4->pos.x = 0.0f;
    lbl_1_bss_4->pos.y = 0.0f;
    lbl_1_bss_4->pos.z = 0.0f;
    lbl_1_bss_4->target.x = 0.0f;
    lbl_1_bss_4->target.y = 0.0f;
    lbl_1_bss_4->target.z = 0.0f;
    lbl_1_bss_4->rot.x = -23.0f;
    lbl_1_bss_4->rot.y = 0.0f;
    lbl_1_bss_4->rot.z = 0.0f;
    lbl_1_bss_4->dist = 1000.0f;
    lbl_1_bss_4->color.r = 255;
    lbl_1_bss_4->color.g = 255;
    lbl_1_bss_4->color.b = 255;
    lbl_1_bss_4->color.a = 255;
    PSVECSubtract(&lbl_1_bss_4->target, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    lbl_1_bss_4->id = Hu3DGLightCreateV(&lbl_1_bss_4->pos, &lbl_1_bss_4->dir, &lbl_1_bss_4->color);
    fn_1_110C();
    Hu3DGLightStaticSet(lbl_1_bss_4->id, 0);
    Hu3DGLightInfinitytSet(lbl_1_bss_4->id);
}

void fn_1_110C(void)
{
    lbl_1_bss_4->pos.x = lbl_1_bss_4->target.x+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*sin((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    lbl_1_bss_4->pos.y = lbl_1_bss_4->target.y+(lbl_1_bss_4->dist*-sin((M_PI*lbl_1_bss_4->rot.x)/180.0));
    lbl_1_bss_4->pos.z = lbl_1_bss_4->target.z+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*cos((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_4->target, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    PSVECNormalize(&lbl_1_bss_4->dir, &lbl_1_bss_4->dir);
    Hu3DGLightPosSetV(lbl_1_bss_4->id, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    Hu3DGLightColorSet(lbl_1_bss_4->id, lbl_1_bss_4->color.r, lbl_1_bss_4->color.g, lbl_1_bss_4->color.b, lbl_1_bss_4->color.a);
}

void fn_1_13E4(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 40000.0f);
    lbl_1_bss_0->rot.x = -90.0f;
    lbl_1_bss_0->rot.y = 0.0f;
    lbl_1_bss_0->rot.z = 0.0f;
    lbl_1_bss_0->target.x = 0.0f;
    lbl_1_bss_0->target.y = 0.0f;
    lbl_1_bss_0->target.z = 0.0f;
    lbl_1_bss_0->tpLvl = 0.5f;
    lbl_1_bss_0->dist = 3500.0f;
    fn_1_150C();
}

void fn_1_150C(void)
{
    lbl_1_bss_0->pos.x = lbl_1_bss_0->target.x+(lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0)));
    lbl_1_bss_0->pos.y = lbl_1_bss_0->target.y+(lbl_1_bss_0->dist*-sin((M_PI*lbl_1_bss_0->rot.x)/180.0));
    lbl_1_bss_0->pos.z = lbl_1_bss_0->target.z+(lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0)));
    lbl_1_bss_0->up.x = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0);
    lbl_1_bss_0->up.y = cos((M_PI*lbl_1_bss_0->rot.x)/180.0);
    lbl_1_bss_0->up.z = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_0->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_0->pos, &lbl_1_bss_0->up, &lbl_1_bss_0->target);
}

s16 fn_1_1898(float *value, float div, float start, float end)
{
    float step;
    s16 count;

    count = 0;
    step = (end-start)/div;
    *value += step;
    if(step) {
        count = (end-*value)/step;
    }
    count++;
    step = M555_DIST(start, end);
    start = M555_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

s16 fn_1_19B8(float *value, float div, float start, float end)
{
    float step;
    s16 count;

    count = 0;
    step = (end-start)/div;
    *value += step;
    if(step) {
        count = (end-*value)/step;
    }
    count++;
    step = M555_DIST(start, end);
    start = M555_DIST(start, *value);
    if(step <= start) {
        count = 0;
    }
    return count;
}

MGTIMER *fn_1_1AD4(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

void fn_1_1B48(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

BOOL fn_1_1B74(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

void fn_1_1B9C(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1579-1872, 251 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1BD4(M555_WORK *work, s16 padNo, s16 no)
{
    M555_MODEL *model;
    s16 result;

    result = 0;
    model = &work->models[no];
    model->pos.x += HuPadStkX[padNo];
    model->pos.y += HuPadStkY[padNo];
    model->pos.z += HuPadTrigL[padNo];
    model->pos.z -= HuPadTrigR[padNo];
    model->rot.x += HuPadSubStkX[padNo]/10;
    model->rot.y += HuPadSubStkY[padNo]/10;
    if(HuPadSubStkX[padNo] > 10) {
        model->rot.x += 1.0f;
    }
    if(HuPadSubStkX[padNo] < -10) {
        model->rot.x -= 1.0f;
    }
    if(HuPadSubStkY[padNo] > 10) {
        model->rot.y += 1.0f;
    }
    if(HuPadSubStkY[padNo] < -10) {
        model->rot.y -= 1.0f;
    }
    if(HuPadBtnRep[padNo] & PAD_BUTTON_A) {
        model->rot.z += 1.0f;
    }
    if(HuPadBtnRep[padNo] & PAD_BUTTON_B) {
        model->rot.z -= 1.0f;
    }
    fontcolor = 0;
    print8(25, 136, 1.5f, lbl_1_data_240, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_26E, no);
    return result;
}

void fn_1_1FC0(void)
{
}

void fn_1_1FC4(s16 padNo)
{
    int btn;
    int btnDown;
    s8 stkX;
    s8 stkY;
    s8 subStkX;
    s8 subStkY;

    btn = HuPadBtn[padNo];
    btnDown = HuPadBtnDown[padNo];
    stkX = (s8)HuPadStkX[padNo];
    stkX = (((stkX >= 0) ? stkX : -stkX) < 10) ? 0 : stkX;
    stkY = (s8)HuPadStkY[padNo];
    stkY = (((stkY >= 0) ? stkY : -stkY) < 10) ? 0 : stkY;
    subStkX = (s8)HuPadSubStkX[padNo];
    subStkX = (((subStkX >= 0) ? subStkX : -subStkX) < 8) ? 0 : subStkX;
    subStkY = (s8)HuPadSubStkY[padNo];
    subStkY = (((subStkY >= 0) ? subStkY : -subStkY) < 8) ? 0 : subStkY;
    if(btn & PAD_BUTTON_X) {
        CZoom += 20.0f;
    }
    if(btn & PAD_BUTTON_Y) {
        CZoom -= 20.0f;
    }
    if(stkX > 0) {
        Center.x += 10.0f;
    }
    if(stkX < 0) {
        Center.x -= 10.0f;
    }
    if(stkY > 0) {
        Center.y += 10.0f;
    }
    if(stkY < 0) {
        Center.y -= 10.0f;
    }
    if(subStkX > 0) {
        CRot.y += 1.0f;
    }
    if(subStkX < 0) {
        CRot.y -= 1.0f;
    }
    if(subStkY > 0) {
        CRot.x += 1.0f;
    }
    if(subStkY < 0) {
        CRot.x -= 1.0f;
    }
    if(btn & 0x2000) {
        CRot.z += 1.0f;
    }
    if(btn & 0x4000) {
        CRot.z -= 1.0f;
    }
    if(btn & PAD_BUTTON_UP) {
        Center.z += 10.0f;
    }
    if(btn & PAD_BUTTON_DOWN) {
        Center.z -= 10.0f;
    }
    print8(25, 30, 1.5f, lbl_1_data_276, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_29B, CRot.x, CRot.y, CRot.z);
}

/* 87 insns. The spark particle model: 60 sparks on layer 4. */
void fn_1_247C(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m555, 0x35), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_3028 = Hu3DParticleCreate(anim, 60);
    Hu3DParticleBlendModeSet(lbl_1_bss_3028, 0);
    Hu3DParticleColSet(lbl_1_bss_3028, 255, 255, 255);
    Hu3DParticleScaleSet(lbl_1_bss_3028, 0.0f);
    Hu3DParticleHookSet(lbl_1_bss_3028, fn_1_28F0);
    Hu3DModelLayerSet(lbl_1_bss_3028, 4);
    Hu3DModelAttrSet(lbl_1_bss_3028, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_3028, HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_3028].hookData;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->time = 0;
    }
}

/* 138 insns. A spark near pos, flying off along z. */
void fn_1_25D8(HuVecF *pos)
{
    float scale;
    float scaleSpeed;
    s16 rand;
    HuVecF p;
    HuVecF vel;

    p = *pos;
    rand = frandmod(20);
    p.x = pos->x+(rand-10);
    rand = frandmod(20);
    p.y = pos->y+(rand-10);
    rand = frandmod(20);
    p.z = pos->z+(rand-10);
    vel.x = 0.0f;
    vel.y = 0.0f;
    rand = frandmod(2);
    vel.z = rand+15;
    rand = frandmod(9);
    scale = rand+34;
    scaleSpeed = 2.0f;
    fn_1_2800(p, vel, scale, scaleSpeed);
}

/* 60 insns. Start the first free spark. */
s16 fn_1_2800(HuVecF pos, HuVecF vel, float scale, float scaleSpeed)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 result;

    particle = Hu3DData[lbl_1_bss_3028].hookData;
    result = 0;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        if(data->time == 0) {
            data->pos = pos;
            data->vel = vel;
            data->color.r = 255;
            data->color.g = 255;
            data->color.b = 255;
            data->color.a = 255;
            data->scaleBase = scaleSpeed;
            data->scale = scale;
            data->time = 1;
            data->parManId = 27;
            break;
        }
    }
    return result;
}

/* 62 insns. The particle hook: move, fade and grow each live spark. */
void fn_1_28F0(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s16 i;

    for(data=particle->data, i=0; i<particle->maxCnt; i++, data++) {
        if(data->time != 0) {
            PSVECAdd(&data->vel, &data->pos, &data->pos);
            data->color.r = data->parManId*7;
            data->color.g = data->parManId*7;
            data->color.b = data->parManId*7;
            data->color.a = data->parManId*7;
            data->scale += data->scaleBase;
            if(data->parManId-- <= 0) {
                data->time = 0;
            }
        }
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* 12 insns. */
void fn_1_29E8(void)
{
    lbl_1_bss_1894.jingleNo = HuAudJinglePlay(131);
}

/* 12 insns. */
void fn_1_2A18(void)
{
    lbl_1_bss_1894.bgmNo = HuAudBGMPlay(53);
}

/* 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_2A48(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_1894.bgmNo;
    } else {
        no = lbl_1_bss_1894.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_2AB0(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_1894.bgmNo;
    } else {
        no = lbl_1_bss_1894.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* 50 insns. Sounds 2, 3, 6 and 7 do not restart while playing. */
void fn_1_2B10(s16 no)
{
    if((no != 2 && no != 3 && no != 6 && no != 7) || lbl_1_bss_1894.seF[no] == -1) {
        lbl_1_bss_1894.seF[no] = 1;
        lbl_1_bss_1894.seNo[no] = HuAudFXPlay(lbl_1_data_2B8[no]);
    }
}

/* 54 insns. */
void fn_1_2BD8(s16 no, s16 vol, s16 pan)
{
    if((no != 2 && no != 3 && no != 6 && no != 7) || lbl_1_bss_1894.seF[no] == -1) {
        lbl_1_bss_1894.seF[no] = 1;
        lbl_1_bss_1894.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_2B8[no], vol, pan);
    }
}

/* 36 insns. */
void fn_1_2CB0(s16 no, s16 pan)
{
    if(lbl_1_bss_1894.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_1894.seNo[no], pan);
    }
}

/* 36 insns. */
void fn_1_2D40(s16 no, s16 pitch)
{
    if(lbl_1_bss_1894.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 2) {
        HuAudFXPitchSet(lbl_1_bss_1894.seNo[no], pitch);
    }
}

/* 36 insns. */
void fn_1_2DD0(s16 no, s16 vol)
{
    if(lbl_1_bss_1894.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 2) {
        HuAudFXVolSet(lbl_1_bss_1894.seNo[no], vol);
    }
}

/* 50 insns. */
void fn_1_2E60(s16 no, s16 speed)
{
    if(lbl_1_bss_1894.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 3)) {
        lbl_1_bss_1894.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_1894.seNo[no]);
    }
}

/* 50 insns. */
void fn_1_2F28(s16 no)
{
    if(lbl_1_bss_1894.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_1894.seNo[no]) == 3)) {
        lbl_1_bss_1894.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_1894.seNo[no]);
    }
}

/* 8 insns. */
void fn_1_2FF0(void)
{
    HuAudAllStop();
}
