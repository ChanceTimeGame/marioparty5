/*
 * m546dll -- a KETTOU duel (overlay #60): the sequence hooks, cameras, lights,
 * shadow, the dust particles, the paper-piece hooks and the sound helpers.
 * Written from the reference assembly, functions in reference order; line
 * ranges are into build/mp5-asm/m546Dll/asm/REL/m546Dll/m546.s.
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
#include "game/printfunc.h"
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "REL/m546Dll/m546.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void ObjectSetup(void);
void fn_1_2F0(s16 mode, s16 frameNo);
void fn_1_324(s16 mode, s16 frameNo);
void fn_1_350(s16 mode, s16 frameNo);
void fn_1_370(s16 mode, s16 frameNo);
void fn_1_39C(s16 mode, s16 frameNo);
void fn_1_3C0(s16 mode, s16 frameNo);
void fn_1_3EC(s16 mode, s16 frameNo);
void fn_1_418(s16 mode, s16 frameNo);
void fn_1_438(s16 mode, s16 frameNo);
void fn_1_464(OMOBJ *obj);
void fn_1_468(s16 no);
void fn_1_DFC(void);
void fn_1_1304(void);
void fn_1_261C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_3048(void);
void fn_1_3BE0(HU3DMODEL *model, Mtx *mtx);
void fn_1_403C(void);
void fn_1_4BA8(HU3DMODEL *model, Mtx *mtx);
void fn_1_5190(void);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_2F0,
    fn_1_324,
    fn_1_350,
    fn_1_370,
    fn_1_39C,
    fn_1_3C0,
    fn_1_3EC,
    fn_1_418,
    fn_1_438
};

/* Nine motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][9] = {
    { 0x008C0000, 0x008C0001, 0x008C0002, 0x008C000D, 0x008C000E, 0x00870064, 0x00870065, 0x008C0006, 0x008C0007 },
    { 0x00330000, 0x00330001, 0x00330002, 0x0033000D, 0x0033000E, 0x002E0064, 0x002E0065, 0x00330006, 0x00330007 },
    { 0x00B70000, 0x00B70001, 0x00B70002, 0x00B7000D, 0x00B7000E, 0x00B20064, 0x00B20065, 0x00B70006, 0x00B70007 },
    { 0x00ED0000, 0x00ED0001, 0x00ED0002, 0x00ED000D, 0x00ED000E, 0x00E80064, 0x00E80065, 0x00ED0006, 0x00ED0007 },
    { 0x00E60000, 0x00E60001, 0x00E60002, 0x00E6000D, 0x00E6000E, 0x00E10064, 0x00E10065, 0x00E60006, 0x00E60007 },
    { 0x00170000, 0x00170001, 0x00170002, 0x0017000D, 0x0017000E, 0x00120064, 0x00120065, 0x00170006, 0x00170007 },
    { 0x00E00000, 0x00E00001, 0x00E00002, 0x00E0000D, 0x00E0000E, 0x00DB0064, 0x00DB0065, 0x00E00006, 0x00E00007 },
    { 0x002D0000, 0x002D0001, 0x002D0002, 0x002D000D, 0x002D000E, 0x00280064, 0x00280065, 0x002D0006, 0x002D0007 },
    { 0x00C90000, 0x00C90001, 0x00C90002, 0x00C9000D, 0x00C9000E, 0x00C40064, 0x00C40065, 0x00C90006, 0x00C90007 },
    { 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0000D, 0x00B0000E, 0x009C0064, 0x009C0065, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0000D, 0x00B0000E, 0x009C0064, 0x009C0065, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0000D, 0x00B0000E, 0x009C0064, 0x009C0065, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00001, 0x00B00002, 0x00B0000D, 0x00B0000E, 0x009C0064, 0x009C0065, 0x00B00006, 0x00B00007 }
};

/* files/data/m546.bin: nine stage models and the twelve arena models (passed to fn_1_B15C). */
unsigned int lbl_1_data_1FC[21] = {
    0x00680000, 0x00680001, 0x00680002, 0x00680003, 0x00680004, 0x00680005, 0x00680006, 0x00680007,
    0x00680008, 0x00680009, 0x0068000A, 0x0068000B, 0x0068000C, 0x0068000D, 0x0068000E, 0x0068000F,
    0x00680010, 0x00680011, 0x00680012, 0x00680013, 0x00680014
};

/* The four cameras fn_1_468 can create; only camera 0 is. */
M546_CAMERAINIT lbl_1_data_250[4] = {
    { { 34.0f, 250.0f, 0.0f }, { -6.0f, 0.0f, 500.0f }, 1000.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_320[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* The dust puff fn_1_1B80 and fn_1_1F4C edit and spawn. */
M546_PARTICLEPARAM lbl_1_data_340 = {
    0.0f,
    { 255, 255, 255, 255 },
    { 0, 0, 0, 255 },
    { 0.0f, 2.0f, 1.0f },
    { 0.85f, 0.85f, 0.85f },
    0.2f,
    0.0f,
    1.0f,
    -3.0f,
    0.02f
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

HU3DMODELID lbl_1_bss_15284;        /* the dust particle model */
M546_PARTICLEPARAM *lbl_1_bss_15280; /* one spawn parameter per particle */
int lbl_1_bss_1527C;                /* unreferenced */
OMOBJMAN *lbl_1_bss_15278;
M546_WORK lbl_1_bss_15028;
M546_MODEL lbl_1_bss_14CFC[M546_MODEL_MAX];
HU3DMOTID lbl_1_bss_14CD8[18];      /* nine motions per duellist */
M546_GAME lbl_1_bss_14C40;
M546_DUEL lbl_1_bss_14B60[2];
M546_PIECESET lbl_1_bss_14AB8;
M546_PIECESET lbl_1_bss_14A10;
M546_PIECE lbl_1_bss_1F0[1000];
M546_PIECE lbl_1_bss_4C[5];
M546_CAMERA *lbl_1_bss_48;
M546_LIGHT *lbl_1_bss_44;
M546_POINTLIGHT lbl_1_bss_4[1];
M546_SHADOW *lbl_1_bss_0;

/* asm 61-210, 148 insns. */
void ObjectSetup(void)
{
    lbl_1_bss_15278 = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_15278);
    fn_1_B15C(&lbl_1_bss_15028, lbl_1_bss_14CFC, lbl_1_data_1FC);
    lbl_1_bss_48 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M546_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_48, 0, (sizeof(M546_CAMERA)*4)+8);
    lbl_1_bss_44 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M546_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_44, 0, sizeof(M546_LIGHT));
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M546_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M546_SHADOW));
    fn_1_468(0);
    fn_1_DFC();
    fn_1_1304();
    fn_1_B3A8(1);
    fn_1_B654(lbl_1_data_28[lbl_1_bss_15028.chr[0].charNo], lbl_1_data_28[lbl_1_bss_15028.chr[1].charNo]);
    fn_1_B678(lbl_1_bss_14CD8, &lbl_1_bss_14CD8[9]);
    fn_1_B69C();
    fn_1_BDCC();
    omAddObjEx(lbl_1_bss_15278, 32730, 0, 0, -1, fn_1_B9B4);
    omAddObjEx(lbl_1_bss_15278, 32730, 0, 0, -1, fn_1_BEF8);
    omAddObjEx(lbl_1_bss_15278, 32730, 0, 0, -1, fn_1_464);
    omAddObjEx(lbl_1_bss_15278, 32730, 0, 0, -1, fn_1_C250);
    Hu3DBGColorSet(186, 245, 255);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(2, 400);
    MgSeqModeDelaySet(7, 180);
    MgSeqModeDelaySet(9, 60);
}

/* asm 213-228, 13 insns. Init hook. */
void fn_1_2F0(s16 mode, s16 frameNo)
{
    if(fn_1_58D0(&lbl_1_bss_15028)) {
        MgSeqModeNext();
    }
}

/* asm 231-244, 11 insns. Fade-in hook. */
void fn_1_324(s16 mode, s16 frameNo)
{
    if(fn_1_6A90()) {
        MgSeqModeNext();
    }
}

/* asm 247-256, 8 insns. Start hook. */
void fn_1_350(s16 mode, s16 frameNo)
{
    fn_1_6AC4();
}

/* asm 259-272, 11 insns. Main hook. */
void fn_1_370(s16 mode, s16 frameNo)
{
    if(fn_1_6B2C()) {
        MgSeqModeNext();
    }
}

/* asm 275-285, 9 insns. Finish hook. */
void fn_1_39C(s16 mode, s16 frameNo)
{
    fn_1_6CD4();
    MgSeqModeNext();
}

/* asm 288-301, 11 insns. Pre-winner hook. */
void fn_1_3C0(s16 mode, s16 frameNo)
{
    if(fn_1_6D14()) {
        MgSeqModeNext();
    }
}

/* asm 304-317, 11 insns. Winner hook. */
void fn_1_3EC(s16 mode, s16 frameNo)
{
    if(fn_1_6D4C()) {
        MgSeqModeNext();
    }
}

/* asm 320-329, 8 insns. Fade-out hook. */
void fn_1_418(s16 mode, s16 frameNo)
{
    fn_1_6E94();
}

/* asm 332-345, 11 insns. Close hook. */
void fn_1_438(s16 mode, s16 frameNo)
{
    if(fn_1_6EC4()) {
        MgSeqModeNext();
    }
}

/* asm 348-350, 1 insn. An empty object. */
void fn_1_464(OMOBJ *obj)
{
}

/* asm 353-617, 263 insns. Create camera `no` from lbl_1_data_250. */
void fn_1_468(s16 no)
{
    lbl_1_bss_48[no].no = no;
    lbl_1_bss_48[no].center.x = lbl_1_data_250[no].center.x;
    lbl_1_bss_48[no].center.y = lbl_1_data_250[no].center.y;
    lbl_1_bss_48[no].center.z = lbl_1_data_250[no].center.z;
    lbl_1_bss_48[no].rot.x = lbl_1_data_250[no].rot.x;
    lbl_1_bss_48[no].rot.y = lbl_1_data_250[no].rot.y;
    lbl_1_bss_48[no].rot.z = lbl_1_data_250[no].rot.z;
    lbl_1_bss_48[no].zoom = lbl_1_data_250[no].zoom;
    lbl_1_bss_48[no].aspect = lbl_1_data_250[no].aspect;
    lbl_1_bss_48[no].vpX = lbl_1_data_250[no].vpX;
    lbl_1_bss_48[no].vpY = lbl_1_data_250[no].vpY;
    lbl_1_bss_48[no].vpW = lbl_1_data_250[no].vpW;
    lbl_1_bss_48[no].vpH = lbl_1_data_250[no].vpH;
    lbl_1_bss_48[no].fov = lbl_1_data_250[no].fov;
    Hu3DCameraCreate(lbl_1_data_320[no]);
    Hu3DCameraViewportSet(lbl_1_data_320[no], lbl_1_bss_48[no].vpX, lbl_1_bss_48[no].vpY, lbl_1_bss_48[no].vpW, lbl_1_bss_48[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_320[no], lbl_1_bss_48[no].fov, 20.0f, 30000.0f, lbl_1_bss_48[no].aspect);
    fn_1_884(no);
}

/* asm 620-971, 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_884(s16 no)
{
    lbl_1_bss_48[no].pos.x = lbl_1_bss_48[no].center.x+(lbl_1_bss_48[no].zoom*(cos((M_PI*lbl_1_bss_48[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_48[no].rot.y)/180.0)));
    lbl_1_bss_48[no].pos.y = lbl_1_bss_48[no].center.y+(lbl_1_bss_48[no].zoom*-sin((M_PI*lbl_1_bss_48[no].rot.x)/180.0));
    lbl_1_bss_48[no].pos.z = lbl_1_bss_48[no].center.z+(lbl_1_bss_48[no].zoom*(cos((M_PI*lbl_1_bss_48[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_48[no].rot.y)/180.0)));
    lbl_1_bss_48[no].up.x = sin((M_PI*lbl_1_bss_48[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_48[no].rot.y)/180.0);
    lbl_1_bss_48[no].up.y = cos((M_PI*lbl_1_bss_48[no].rot.x)/180.0);
    lbl_1_bss_48[no].up.z = sin((M_PI*lbl_1_bss_48[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_48[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_320[no], lbl_1_bss_48[no].pos.x, lbl_1_bss_48[no].pos.y, lbl_1_bss_48[no].pos.z,
        lbl_1_bss_48[no].up.x, lbl_1_bss_48[no].up.y, lbl_1_bss_48[no].up.z,
        lbl_1_bss_48[no].center.x, lbl_1_bss_48[no].center.y, lbl_1_bss_48[no].center.z);
}

/* asm 974-1115, 140 insns. The global light. */
void fn_1_DFC(void)
{
    Hu3DLighInit();
    lbl_1_bss_44->pos.x = 0.0f;
    lbl_1_bss_44->pos.y = 0.0f;
    lbl_1_bss_44->pos.z = 0.0f;
    lbl_1_bss_44->target.x = 0.0f;
    lbl_1_bss_44->target.y = 0.0f;
    lbl_1_bss_44->target.z = 0.0f;
    lbl_1_bss_44->rot.x = -23.0f;
    lbl_1_bss_44->rot.y = 0.0f;
    lbl_1_bss_44->rot.z = 0.0f;
    lbl_1_bss_44->dist = 1000.0f;
    lbl_1_bss_44->color.r = 255;
    lbl_1_bss_44->color.g = 255;
    lbl_1_bss_44->color.b = 255;
    lbl_1_bss_44->color.a = 255;
    PSVECSubtract(&lbl_1_bss_44->target, &lbl_1_bss_44->pos, &lbl_1_bss_44->dir);
    lbl_1_bss_44->id = Hu3DGLightCreateV(&lbl_1_bss_44->pos, &lbl_1_bss_44->dir, &lbl_1_bss_44->color);
    fn_1_102C();
    Hu3DGLightStaticSet(lbl_1_bss_44->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_44->id);
}

/* asm 1118-1301, 182 insns. Place the light from its target, rotation and distance. */
void fn_1_102C(void)
{
    lbl_1_bss_44->pos.x = lbl_1_bss_44->target.x+(lbl_1_bss_44->dist*(cos((M_PI*lbl_1_bss_44->rot.x)/180.0)*sin((M_PI*lbl_1_bss_44->rot.y)/180.0)));
    lbl_1_bss_44->pos.y = lbl_1_bss_44->target.y+(lbl_1_bss_44->dist*-sin((M_PI*lbl_1_bss_44->rot.x)/180.0));
    lbl_1_bss_44->pos.z = lbl_1_bss_44->target.z+(lbl_1_bss_44->dist*(cos((M_PI*lbl_1_bss_44->rot.x)/180.0)*cos((M_PI*lbl_1_bss_44->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_44->target, &lbl_1_bss_44->pos, &lbl_1_bss_44->dir);
    PSVECNormalize(&lbl_1_bss_44->dir, &lbl_1_bss_44->dir);
    Hu3DGLightPosSetV(lbl_1_bss_44->id, &lbl_1_bss_44->pos, &lbl_1_bss_44->dir);
    Hu3DGLightColorSet(lbl_1_bss_44->id, lbl_1_bss_44->color.r, lbl_1_bss_44->color.g, lbl_1_bss_44->color.b, lbl_1_bss_44->color.a);
}

/* asm 1304-1381, 76 insns. The shadow. */
void fn_1_1304(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_0->rot.x = -100.0f;
    lbl_1_bss_0->rot.y = 0.0f;
    lbl_1_bss_0->rot.z = 0.0f;
    lbl_1_bss_0->target.x = 0.0f;
    lbl_1_bss_0->target.y = 0.0f;
    lbl_1_bss_0->target.z = -250.0f;
    lbl_1_bss_0->dist = 2500.0f;
    lbl_1_bss_0->tpLvl = 0.3f;
    Hu3DShadowSizeSet(200);
    fn_1_1434();
}

/*
 * asm 1384-1611, 226 insns. Place the shadow camera. Retail leaves the
 * target's z out of pos.z and adds 300 instead.
 */
void fn_1_1434(void)
{
    lbl_1_bss_0->pos.x = lbl_1_bss_0->target.x+(lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0)));
    lbl_1_bss_0->pos.y = lbl_1_bss_0->target.y+(lbl_1_bss_0->dist*-sin((M_PI*lbl_1_bss_0->rot.x)/180.0));
    lbl_1_bss_0->pos.z = 300.0+(lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0)));
    lbl_1_bss_0->up.x = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0);
    lbl_1_bss_0->up.y = cos((M_PI*lbl_1_bss_0->rot.x)/180.0);
    lbl_1_bss_0->up.z = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_0->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_0->pos, &lbl_1_bss_0->up, &lbl_1_bss_0->target);
}

#define M546_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

/* asm 1614-1693, 72 insns. Step *value toward end by (end-start)/div; the steps left, 0 once there. */
s16 fn_1_17BC(float *value, float div, float start, float end)
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
    step = M546_DIST(start, end);
    start = M546_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1696-1726, 29 insns. */
MGTIMER *fn_1_18DC(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1729-1741, 11 insns. */
void fn_1_1950(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1744-1755, 10 insns. */
BOOL fn_1_197C(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1758-1773, 14 insns. */
void fn_1_19A4(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1776-1886, 105 insns. The dust particle model. Retail clears the id sixteen times. */
void fn_1_19DC(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    for(i=0; i<16; i++) {
        lbl_1_bss_15284 = -1;
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x680015, HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_15280 = HuMemDirectMallocNum(HEAP_HEAP, 220*sizeof(M546_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_15284 = Hu3DParticleCreate(anim, 220);
    Hu3DParticleHookSet(lbl_1_bss_15284, fn_1_261C);
    Hu3DParticleBlendModeSet(lbl_1_bss_15284, 1);
    Hu3DModelLayerSet(lbl_1_bss_15284, 4);
    Hu3DModelCameraSet(lbl_1_bss_15284, 1);
    Hu3DModelAttrSet(lbl_1_bss_15284, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_15284, HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_15284].hookData;
    particle->count = 0;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_15280;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 1889-2135, 243 insns. Twelve dust puffs in a ring around pos. */
void fn_1_1B80(HuVecF *pos)
{
    s16 unk;
    HuVecF puffPos;
    float size;
    float mul;
    s16 i;
    s16 alpha;

    unk = 16;
    size = 0.8f;
    mul = 1.0f;
    for(i=0; i<12; i++) {
        puffPos.x = pos->x+(mul*(20.0*sin((M_PI*(30.0f*i))/180.0)));
        puffPos.y = pos->y+(10.0f*mul);
        puffPos.z = pos->z+(mul*(20.0*cos((M_PI*(30.0f*i))/180.0)));
        size = mul*(6.0+frandmod(6));
        lbl_1_data_340.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_340.vel.y = 0.0f;
        lbl_1_data_340.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_340.alphaSpeed = alpha;
        lbl_1_data_340.accelY = 0.01*frandmod(20);
        size = mul*(20.0+frandmod(20));
        fn_1_2448(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_340);
    }
}

/* asm 2138-2462, 319 insns. Eighteen rings of puffs, 170 out from pos. */
void fn_1_1F4C(HuVecF *pos)
{
    s16 unk;
    float scale;
    HuVecF center;
    HuVecF puffPos;
    float mul;
    float size;
    s16 j;
    s16 i;
    s16 alpha;

    scale = 1.0f;
    for(i=0; i<18; i++) {
        center.x = pos->x+(170.0*sin((M_PI*(20.0f*i))/180.0));
        center.y = pos->y;
        center.z = pos->z+(170.0*cos((M_PI*(20.0f*i))/180.0));
        unk = 16;
        size = 0.8f;
        mul = 1.0f;
        for(j=0; j<12; j++) {
            puffPos.x = center.x+(mul*(20.0*sin((M_PI*(30.0f*j))/180.0)));
            puffPos.y = center.y+(10.0f*mul);
            puffPos.z = center.z+(mul*(20.0*cos((M_PI*(30.0f*j))/180.0)));
            size = mul*(6.0+frandmod(6));
            lbl_1_data_340.vel.x = size*sin((M_PI*(30.0f*j))/180.0);
            lbl_1_data_340.vel.y = 0.0f;
            lbl_1_data_340.vel.z = size*cos((M_PI*(30.0f*j))/180.0);
            alpha = -frandmod(6)-7;
            lbl_1_data_340.alphaSpeed = alpha;
            lbl_1_data_340.accelY = 0.01*frandmod(20);
            size = mul*(20.0+frandmod(20));
            fn_1_2448(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_340);
        }
    }
}

/* asm 2465-2590, 117 insns. Spawn one particle; the slot, or -1 when all are live. */
s16 fn_1_2448(float x, float y, float z, float scale, M546_PARTICLEPARAM *param)
{
    s16 result;
    HU3DMODEL *model;
    M546_PARTICLEPARAM *work;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;

    result = -1;
    model = &Hu3DData[lbl_1_bss_15284];
    particle = model->hookData;
    work = particle->work;
    for(data=&particle->data[particle->emitCnt], i=particle->emitCnt; i<particle->maxCnt; i++, data++) {
        if(!data->scale) {
            break;
        }
    }
    if(i >= particle->maxCnt) {
        for(data=particle->data, i=0; i<particle->maxCnt; i++, data++) {
            if(!data->scale) {
                break;
            }
        }
    }
    if(i != particle->maxCnt) {
        work[i] = *param;
        data->pos.x = x;
        data->pos.y = y;
        data->pos.z = z;
        data->vel = param->vel;
        data->color = param->color;
        data->scaleBase = scale;
        data->scale = scale;
        data->parManId = -1;
        particle->emitCnt = i;
        result = i;
    }
    return result;
}

/* asm 2593-2867, 262 insns. The particle hook: move, fade and shrink every live puff. */
void fn_1_261C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M546_PARTICLEPARAM *param;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 value;

    param = particle->work;
    data = particle->data;
    for(i=0, data->time=0; i<particle->maxCnt; i++, data++) {
        if(0.0f == data->scale) {
            continue;
        }
        data->vel.x *= param[i].velMul.x;
        data->vel.y *= param[i].velMul.y;
        data->vel.z *= param[i].velMul.z;
        PSVECAdd(&data->vel, &data->pos, &data->pos);
        data->vel.y += param[i].accelY;
        value = data->color.r+(param[i].colorSpeed*(param[i].colorEnd.r-param[i].color.r));
        if(value < 0) {
            value = 0;
        } else if(value > 255) {
            value = 255;
        }
        data->color.r = value;
        value = data->color.g+(param[i].colorSpeed*(param[i].colorEnd.g-param[i].color.g));
        if(value < 0) {
            value = 0;
        } else if(value > 255) {
            value = 255;
        }
        data->color.g = value;
        value = data->color.b+(param[i].colorSpeed*(param[i].colorEnd.b-param[i].color.b));
        if(value < 0) {
            value = 0;
        } else if(value > 255) {
            value = 255;
        }
        data->color.b = value;
        value = data->color.a+param[i].alphaSpeed;
        if(value < 1) {
            data->scale = 0.0f;
        }
        data->color.a = value;
        if(data->scale) {
            data->scale = data->scaleBase;
            data->scaleBase += param[i].scaleSpeed;
            if(data->scaleBase <= 0.01f) {
                data->scale = 0.0f;
            }
        }
        data->time++;
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* asm 2870-3092, 219 insns. Debug: move and turn model mdlNo with pad padNo, and print it. Unreferenced. */
s16 fn_1_2A34(M546_WORK *work, s16 padNo, s16 mdlNo)
{
    s16 result;
    M546_MODEL *model;

    result = 0;
    model = &work->models[mdlNo];
    model->pos.x += (s8)HuPadStkX[padNo]/60;
    model->pos.y += (s8)HuPadStkY[padNo]/60;
    model->pos.z += HuPadTrigL[padNo]/60;
    model->pos.z -= HuPadTrigR[padNo]/60;
    model->rot.x += (s8)HuPadSubStkX[padNo]/50;
    model->rot.y += (s8)HuPadSubStkY[padNo]/50;
    if(HuPadBtnRep[padNo] & PAD_BUTTON_A) {
        model->rot.z += 1.0f;
    }
    if(HuPadBtnRep[padNo] & PAD_BUTTON_B) {
        model->rot.z -= 1.0f;
    }
    fontcolor = FONT_COLOR_BLACK;
    print8(25, 136, 1.5f, "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f", model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    return result;
}

/* asm 3095-3126, 30 insns. A random value in -1..1 in steps of 0.01. */
float fn_1_2DA0(void)
{
    s32 value;
    float result;

    value = frandmod(201)-100;
    result = value;
    result /= 100.0f;
    return result;
}

/* The pieces' colours and their multipliers, one per kind. */
HuVecF lbl_1_data_3A8[4] = {
    { 255.0f, 191.25f, 204.0f },
    { 255.0f, 255.0f, 153.0f },
    { 178.5f, 255.0f, 255.0f },
    { 153.0f, 255.0f, 191.25f }
};

HuVecF lbl_1_data_3D8[4] = {
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }
};

/* asm 3129-3259, 129 insns. Start the falling pieces at pos, drawn with models mdlNo..+3. */
void fn_1_2E18(M546_WORK *work, s16 mdlNo, HuVecF pos)
{
    memset(&lbl_1_bss_14AB8, 0, sizeof(M546_PIECESET));
    lbl_1_bss_14AB8.floorY = 105.0f;
    lbl_1_bss_14AB8.activeF = 1;
    lbl_1_bss_14AB8.modelId[0] = work->models[mdlNo].modelId;
    lbl_1_bss_14AB8.modelId[1] = work->models[mdlNo+1].modelId;
    lbl_1_bss_14AB8.modelId[2] = work->models[mdlNo+2].modelId;
    lbl_1_bss_14AB8.modelId[3] = work->models[mdlNo+3].modelId;
    sprintf(lbl_1_bss_14AB8.objName[0], "%s", "m546-kami01");
    sprintf(lbl_1_bss_14AB8.objName[1], "%s", "m546-kami02");
    sprintf(lbl_1_bss_14AB8.objName[2], "%s", "m546-kami03");
    sprintf(lbl_1_bss_14AB8.objName[3], "%s", "m546-kami04");
    lbl_1_bss_14AB8.pos = pos;
    lbl_1_bss_14AB8.timer = 10;
    lbl_1_bss_14AB8.num = 1;
    lbl_1_bss_14AB8.hookId = Hu3DHookFuncCreate(fn_1_3BE0);
    Hu3DModelCameraSet(lbl_1_bss_14AB8.hookId, lbl_1_data_320[0]);
    Hu3DModelLayerSet(lbl_1_bss_14AB8.hookId, 4);
}

/* asm 3262-3274, 11 insns. */
void fn_1_301C(void)
{
    Hu3DModelKill(lbl_1_bss_14AB8.hookId);
}

/* asm 3277-3818, 534 insns. Spawn num pieces into free slots in a ring 50 around the set's position. */
void fn_1_3048(void)
{
    s16 i;
    s16 kind;
    float angle;

    for(i=0; i<1000; i++) {
        if(lbl_1_bss_1F0[i].activeF != 0) {
            continue;
        }
        lbl_1_bss_1F0[i].activeF = 1;
        lbl_1_bss_1F0[i].timer = frandmod(30)+136;
        angle = 360.0f*fn_1_2DA0();
        lbl_1_bss_1F0[i].pos.x = lbl_1_bss_14AB8.pos.x+(50.0*sin((M_PI*angle)/180.0));
        lbl_1_bss_1F0[i].pos.y = lbl_1_bss_14AB8.pos.y;
        lbl_1_bss_1F0[i].pos.z = lbl_1_bss_14AB8.pos.z+(50.0*cos((M_PI*angle)/180.0));
        lbl_1_bss_1F0[i].rot.x = 0.0f;
        lbl_1_bss_1F0[i].rot.y = 0.0f;
        lbl_1_bss_1F0[i].rot.z = 0.0f;
        lbl_1_bss_1F0[i].vel.x = 0.8f*fn_1_2DA0();
        lbl_1_bss_1F0[i].vel.y = -1.0f*(6.5f*fn_1_2DA0());
        if(lbl_1_bss_1F0[i].vel.y > 0.0f) {
            lbl_1_bss_1F0[i].vel.y *= -1.0f;
        }
        if(lbl_1_bss_1F0[i].vel.y > -2.6000001f) {
            lbl_1_bss_1F0[i].vel.y = -2.6000001f;
        }
        lbl_1_bss_1F0[i].vel.z = 0.5f*fn_1_2DA0();
        lbl_1_bss_1F0[i].rotVel.x = 14.0f*fn_1_2DA0();
        lbl_1_bss_1F0[i].rotVel.y = 14.0f*fn_1_2DA0();
        lbl_1_bss_1F0[i].rotVel.z = 14.0f*fn_1_2DA0();
        lbl_1_bss_1F0[i].kind = kind = frandmod(4);
        lbl_1_bss_1F0[i].color.x = lbl_1_data_3A8[kind].x;
        lbl_1_bss_1F0[i].color.y = lbl_1_data_3A8[kind].y;
        lbl_1_bss_1F0[i].color.z = lbl_1_data_3A8[kind].z;
        kind = frandmod(4);
        lbl_1_bss_1F0[i].colorMul.x = lbl_1_data_3D8[kind].x;
        lbl_1_bss_1F0[i].colorMul.y = lbl_1_data_3D8[kind].y;
        lbl_1_bss_1F0[i].colorMul.z = lbl_1_data_3D8[kind].z;
        lbl_1_bss_1F0[i].tpLvl = 1.0f;
        lbl_1_bss_14AB8.total++;
        if(lbl_1_bss_14AB8.spawnCnt++ >= lbl_1_bss_14AB8.num) {
            break;
        }
    }
}

/* asm 3821-4035, 208 insns. The pieces object: fall and tumble until they land, then spawn more. */
void fn_1_38A0(void)
{
    s16 i;

    if(lbl_1_bss_14AB8.activeF) {
        for(i=0; i<1000; i++) {
            if(lbl_1_bss_1F0[i].activeF) {
                switch(lbl_1_bss_1F0[i].mode) {
                    case 0:
                        lbl_1_bss_1F0[i].pos.x += lbl_1_bss_1F0[i].vel.x;
                        lbl_1_bss_1F0[i].pos.y += lbl_1_bss_1F0[i].vel.y;
                        lbl_1_bss_1F0[i].pos.z += lbl_1_bss_1F0[i].vel.z;
                        lbl_1_bss_1F0[i].rot.x += lbl_1_bss_1F0[i].rotVel.x;
                        lbl_1_bss_1F0[i].rot.y += lbl_1_bss_1F0[i].rotVel.y;
                        lbl_1_bss_1F0[i].rot.z += lbl_1_bss_1F0[i].rotVel.z;
                        if(lbl_1_bss_1F0[i].pos.y <= 105.0f) {
                            lbl_1_bss_1F0[i].pos.y = lbl_1_bss_14AB8.floorY;
                            lbl_1_bss_1F0[i].rot.x = 0.0f;
                            lbl_1_bss_1F0[i].rot.z = 0.0f;
                            lbl_1_bss_14AB8.floorY += 0.001f;
                            lbl_1_bss_1F0[i].mode++;
                        }
                        break;

                    case 1:
                        break;
                }
            }
        }
        if(lbl_1_bss_14AB8.timer-- <= 0 && lbl_1_bss_14AB8.total < 1000) {
            lbl_1_bss_14AB8.timer = frandmod(2)+1;
            lbl_1_bss_14AB8.num = 1;
            lbl_1_bss_14AB8.spawnCnt = 0;
            fn_1_3048();
        }
    }
}

/* asm 4038-4190, 147 insns. The pieces' draw hook. */
void fn_1_3BE0(HU3DMODEL *model, Mtx *mtx)
{
    Mtx objMtx;
    Mtx rotMtx;
    s16 i;

    if(lbl_1_bss_14AB8.activeF) {
        Hu3DModelObjDrawInit();
        for(i=0; i<1000; i++) {
            if(lbl_1_bss_1F0[i].activeF) {
                PSMTXRotRad(rotMtx, 'z', 0.017453292f*lbl_1_bss_1F0[i].rot.z);
                PSMTXRotRad(objMtx, 'x', 0.017453292f*lbl_1_bss_1F0[i].rot.x);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXRotRad(rotMtx, 'y', 0.017453292f*lbl_1_bss_1F0[i].rot.y);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXTrans(rotMtx, lbl_1_bss_1F0[i].pos.x, lbl_1_bss_1F0[i].pos.y, lbl_1_bss_1F0[i].pos.z);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXConcat(*mtx, objMtx, objMtx);
                Hu3DModelTPLvlSet(lbl_1_bss_14AB8.modelId[lbl_1_bss_1F0[i].kind], lbl_1_bss_1F0[i].tpLvl);
                Hu3DModelObjDraw(lbl_1_bss_14AB8.modelId[lbl_1_bss_1F0[i].kind], lbl_1_bss_14AB8.objName[lbl_1_bss_1F0[i].kind], objMtx);
            }
        }
    }
}

/* asm 4193-4315, 121 insns. The same for num pieces thrown up at pos, drawn with models mdlNo..+3. */
void fn_1_3E2C(M546_WORK *work, s16 mdlNo, HuVecF pos, s16 num)
{
    memset(&lbl_1_bss_14A10, 0, sizeof(M546_PIECESET));
    lbl_1_bss_14A10.activeF = 1;
    lbl_1_bss_14A10.modelId[0] = work->models[mdlNo].modelId;
    lbl_1_bss_14A10.modelId[1] = work->models[mdlNo+1].modelId;
    lbl_1_bss_14A10.modelId[2] = work->models[mdlNo+2].modelId;
    lbl_1_bss_14A10.modelId[3] = work->models[mdlNo+3].modelId;
    sprintf(lbl_1_bss_14A10.objName[0], "%s", "m546-kami01");
    sprintf(lbl_1_bss_14A10.objName[1], "%s", "m546-kami02");
    sprintf(lbl_1_bss_14A10.objName[2], "%s", "m546-kami03");
    sprintf(lbl_1_bss_14A10.objName[3], "%s", "m546-kami04");
    lbl_1_bss_14A10.pos = pos;
    lbl_1_bss_14A10.num = num;
    lbl_1_bss_14A10.hookId = Hu3DHookFuncCreate(fn_1_4BA8);
    Hu3DModelCameraSet(lbl_1_bss_14A10.hookId, lbl_1_data_320[0]);
    Hu3DModelLayerSet(lbl_1_bss_14A10.hookId, 4);
    fn_1_403C();
}

/* asm 4318-4330, 11 insns. */
void fn_1_4010(void)
{
    Hu3DModelKill(lbl_1_bss_14A10.hookId);
}

/* asm 4333-4868, 528 insns. fn_1_3048 for the thrown set. */
void fn_1_403C(void)
{
    s16 i;
    s16 kind;
    float angle;

    for(i=0; i<lbl_1_bss_14A10.num; i++) {
        if(lbl_1_bss_4C[i].activeF != 0) {
            continue;
        }
        lbl_1_bss_4C[i].activeF = 1;
        lbl_1_bss_4C[i].timer = frandmod(30)+136;
        angle = 360.0f*fn_1_2DA0();
        lbl_1_bss_4C[i].pos.x = lbl_1_bss_14A10.pos.x+(50.0*sin((M_PI*angle)/180.0));
        lbl_1_bss_4C[i].pos.y = lbl_1_bss_14A10.pos.y;
        lbl_1_bss_4C[i].pos.z = lbl_1_bss_14A10.pos.z+(50.0*cos((M_PI*angle)/180.0));
        lbl_1_bss_4C[i].rot.x = 0.0f;
        lbl_1_bss_4C[i].rot.y = 0.0f;
        lbl_1_bss_4C[i].rot.z = 0.0f;
        lbl_1_bss_4C[i].vel.x = 0.8f*fn_1_2DA0();
        lbl_1_bss_4C[i].vel.y = -1.0f*(6.5f*fn_1_2DA0());
        if(lbl_1_bss_4C[i].vel.y > 0.0f) {
            lbl_1_bss_4C[i].vel.y *= -1.0f;
        }
        if(lbl_1_bss_4C[i].vel.y > -2.6000001f) {
            lbl_1_bss_4C[i].vel.y = -2.6000001f;
        }
        lbl_1_bss_4C[i].vel.z = fn_1_2DA0();
        lbl_1_bss_4C[i].rotVel.x = 14.0f*fn_1_2DA0();
        lbl_1_bss_4C[i].rotVel.y = 14.0f*fn_1_2DA0();
        lbl_1_bss_4C[i].rotVel.z = 14.0f*fn_1_2DA0();
        lbl_1_bss_4C[i].kind = kind = frandmod(4);
        lbl_1_bss_4C[i].color.x = lbl_1_data_3A8[kind].x;
        lbl_1_bss_4C[i].color.y = lbl_1_data_3A8[kind].y;
        lbl_1_bss_4C[i].color.z = lbl_1_data_3A8[kind].z;
        kind = frandmod(4);
        lbl_1_bss_4C[i].colorMul.x = lbl_1_data_3D8[kind].x;
        lbl_1_bss_4C[i].colorMul.y = lbl_1_data_3D8[kind].y;
        lbl_1_bss_4C[i].colorMul.z = lbl_1_data_3D8[kind].z;
        lbl_1_bss_4C[i].tpLvl = 1.0f;
        if(++lbl_1_bss_14A10.spawnCnt >= lbl_1_bss_14A10.num) {
            break;
        }
    }
}

/* asm 4871-5079, 203 insns. The thrown pieces object: fly until they land, then lie at 45 degrees. */
void fn_1_487C(void)
{
    s16 i;

    if(lbl_1_bss_14A10.activeF) {
        for(i=0; i<lbl_1_bss_14A10.num; i++) {
            if(lbl_1_bss_4C[i].activeF) {
                lbl_1_bss_4C[i].pos.x += lbl_1_bss_4C[i].vel.x;
                lbl_1_bss_4C[i].pos.y += lbl_1_bss_4C[i].vel.y;
                lbl_1_bss_4C[i].pos.z += lbl_1_bss_4C[i].vel.z;
                lbl_1_bss_4C[i].rot.x += lbl_1_bss_4C[i].rotVel.x;
                lbl_1_bss_4C[i].rot.y += lbl_1_bss_4C[i].rotVel.y;
                lbl_1_bss_4C[i].rot.z += lbl_1_bss_4C[i].rotVel.z;
                if(lbl_1_bss_4C[i].pos.y <= 105.0f) {
                    lbl_1_bss_4C[i].tpLvl = 1.0f;
                    lbl_1_bss_4C[i].pos.x -= lbl_1_bss_4C[i].vel.x;
                    lbl_1_bss_4C[i].pos.y = 105.0f;
                    lbl_1_bss_4C[i].pos.z -= lbl_1_bss_4C[i].vel.z;
                    lbl_1_bss_4C[i].rot.x = 0.0f;
                    lbl_1_bss_4C[i].rot.y = 45.0f;
                    lbl_1_bss_4C[i].rot.z = 0.0f;
                    lbl_1_bss_4C[i].timer = 100;
                }
            }
        }
    }
}

/* asm 5082-5237, 150 insns. The thrown pieces' draw hook. */
void fn_1_4BA8(HU3DMODEL *model, Mtx *mtx)
{
    Mtx objMtx;
    Mtx rotMtx;
    s16 i;

    if(lbl_1_bss_14A10.activeF) {
        Hu3DModelObjDrawInit();
        for(i=0; i<lbl_1_bss_14A10.num; i++) {
            if(lbl_1_bss_4C[i].activeF) {
                PSMTXRotRad(rotMtx, 'z', 0.017453292f*lbl_1_bss_4C[i].rot.z);
                PSMTXRotRad(objMtx, 'x', 0.017453292f*lbl_1_bss_4C[i].rot.x);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXRotRad(rotMtx, 'y', 0.017453292f*lbl_1_bss_4C[i].rot.y);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXTrans(rotMtx, lbl_1_bss_4C[i].pos.x, lbl_1_bss_4C[i].pos.y, lbl_1_bss_4C[i].pos.z);
                PSMTXConcat(rotMtx, objMtx, objMtx);
                PSMTXConcat(*mtx, objMtx, objMtx);
                Hu3DModelTPLvlSet(lbl_1_bss_14A10.modelId[lbl_1_bss_4C[i].kind], lbl_1_bss_4C[i].tpLvl);
                Hu3DModelObjDraw(lbl_1_bss_14A10.modelId[lbl_1_bss_4C[i].kind], lbl_1_bss_14A10.objName[lbl_1_bss_4C[i].kind], objMtx);
            }
        }
    }
}

/* asm 5240-5471, 228 insns. The point light. Unreferenced. */
void fn_1_4E00(void)
{
    s16 i;

    Hu3DLighInit();
    for(i=0; i<1; i++) {
        lbl_1_bss_4[i].activeF = 1;
        lbl_1_bss_4[i].pos.x = 0.0f;
        lbl_1_bss_4[i].pos.y = 0.0f;
        lbl_1_bss_4[i].pos.z = -2000.0f;
        lbl_1_bss_4[i].target.x = 0.0f;
        lbl_1_bss_4[i].target.y = 0.0f;
        lbl_1_bss_4[i].target.z = 0.0f;
        lbl_1_bss_4[i].rot.x = -90.0f;
        lbl_1_bss_4[i].rot.y = 0.0f;
        lbl_1_bss_4[i].rot.z = 0.0f;
        lbl_1_bss_4[i].dist = 700.0f;
        lbl_1_bss_4[i].color.r = 255;
        lbl_1_bss_4[i].color.g = 255;
        lbl_1_bss_4[i].color.b = 255;
        lbl_1_bss_4[i].color.a = 255;
        lbl_1_bss_4[i].unk38 = 120.0f*i;
        PSVECSubtract(&lbl_1_bss_4[i].target, &lbl_1_bss_4[i].pos, &lbl_1_bss_4[i].dir);
        lbl_1_bss_4[i].id = Hu3DGLightCreateV(&lbl_1_bss_4[i].pos, &lbl_1_bss_4[i].dir, &lbl_1_bss_4[i].color);
        fn_1_5190();
        Hu3DGLightStaticSet(lbl_1_bss_4[i].id, 1);
        Hu3DGLightPointSet(lbl_1_bss_4[i].id, 0.0f, 0.5f, GX_DA_OFF);
    }
}

/* asm 5474-5717, 239 insns. Debug: move the point light with pad 0 and print it. */
void fn_1_5190(void)
{
    s16 i;

    for(i=0; i<1; i++) {
        if(lbl_1_bss_4[i].activeF) {
            lbl_1_bss_4[i].pos.x += (s8)HuPadSubStkX[0]/5;
            lbl_1_bss_4[i].pos.y += (s8)HuPadStkX[0]/5;
            lbl_1_bss_4[i].pos.z += (s8)HuPadSubStkY[0]/5;
            fontcolor = FONT_COLOR_WHITE;
            print8(50, 100, 1.5f, "%f", lbl_1_bss_4[i].pos.x);
            fontcolor = FONT_COLOR_BLACK;
            print8(300, 100, 1.5f, "%f", lbl_1_bss_4[i].pos.z);
            PSVECSubtract(&lbl_1_bss_4[i].target, &lbl_1_bss_4[i].pos, &lbl_1_bss_4[i].dir);
            PSVECNormalize(&lbl_1_bss_4[i].dir, &lbl_1_bss_4[i].dir);
            Hu3DGLightPosSet(lbl_1_bss_4[i].id, lbl_1_bss_4[i].pos.x, lbl_1_bss_4[i].pos.y, lbl_1_bss_4[i].pos.z, 0.0f, 1.0f, 0.0f);
            Hu3DGLightColorSet(lbl_1_bss_4[i].id, lbl_1_bss_4[i].color.r, lbl_1_bss_4[i].color.g, lbl_1_bss_4[i].color.b, lbl_1_bss_4[i].color.a);
        }
    }
}

/* fn_1_5674's sound effects. */
s16 lbl_1_data_43E[7] = {
    0x82E, 0x82F, 0x830, 0x831, 0x832, 0x833, 0x834
};

/* asm 5720-5733, 12 insns. */
void fn_1_554C(void)
{
    lbl_1_bss_14C40.jingleNo = HuAudJinglePlay(131);
}

/* asm 5736-5749, 12 insns. */
void fn_1_557C(void)
{
    lbl_1_bss_14C40.bgmNo = HuAudBGMPlay(59);
}

/* asm 5752-5781, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_55AC(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_14C40.bgmNo;
    } else {
        no = lbl_1_bss_14C40.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 5784-5811, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_5614(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_14C40.bgmNo;
    } else {
        no = lbl_1_bss_14C40.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 5814-5845, 30 insns. */
void fn_1_5674(s16 no)
{
    lbl_1_bss_14C40.seF[no] = 1;
    lbl_1_bss_14C40.seNo[no] = HuAudFXPlay(lbl_1_data_43E[no]);
}

/* asm 5848-5883, 34 insns. */
void fn_1_56EC(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_14C40.seF[no] = 1;
    lbl_1_bss_14C40.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_43E[no], vol, pan);
}

/* asm 5886-5924, 36 insns. */
void fn_1_5774(s16 no, s16 pan)
{
    if(lbl_1_bss_14C40.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_14C40.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_14C40.seNo[no], pan);
    }
}

/* asm 5927-5973, 43 insns. */
void fn_1_5804(s16 no)
{
    if(lbl_1_bss_14C40.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_14C40.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_14C40.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_14C40.seNo[no]);
    }
}

/* asm 5976-5985, 8 insns. */
void fn_1_58B0(void)
{
    HuAudAllStop();
}
