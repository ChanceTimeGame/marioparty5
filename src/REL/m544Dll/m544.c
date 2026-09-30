/*
 * m544dll -- a KETTOU duel (overlay #58): the sequence hooks, cameras, light,
 * shadow, the debug movers, the dust and flash particles and the sound
 * helpers. Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m544Dll/asm/REL/m544Dll/m544.s.
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

#include "REL/m544Dll/m544.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M544_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

void ObjectSetup(void);
void fn_1_37C(s16 mode, s16 frameNo);
void fn_1_3B0(s16 mode, s16 frameNo);
void fn_1_3DC(s16 mode, s16 frameNo);
void fn_1_3FC(s16 mode, s16 frameNo);
void fn_1_428(s16 mode, s16 frameNo);
void fn_1_448(s16 mode, s16 frameNo);
void fn_1_474(s16 mode, s16 frameNo);
void fn_1_4A0(s16 mode, s16 frameNo);
void fn_1_4C0(s16 mode, s16 frameNo);
/* game.c defines it returning s16; the hook tests the whole register, as retail's call without a prototype did. */
s32 fn_1_511C(void);
void fn_1_4EC(OMOBJ *obj);
void fn_1_4F0(s16 no);
void fn_1_F38(void);
void fn_1_1440(void);
s16 fn_1_2EE4(float x, float y, float z, float scale, M544_PARTICLEPARAM *param);
void fn_1_30B8(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_39E8(HuVecF pos, HuVecF target, float scale);
void fn_1_3AD4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_37C,
    fn_1_3B0,
    fn_1_3DC,
    fn_1_3FC,
    fn_1_428,
    fn_1_448,
    fn_1_474,
    fn_1_4A0,
    fn_1_4C0
};

/* Seven motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][7] = {
    { 0x008C0000, 0x008C001A, 0x00870026, 0x00870027, 0x00870028, 0x008C0006, 0x008C0007 },
    { 0x00330000, 0x0033001A, 0x002E0026, 0x002E0027, 0x002E0028, 0x00330006, 0x00330007 },
    { 0x00B70000, 0x00B7001A, 0x00B20026, 0x00B20027, 0x00B20028, 0x00B70006, 0x00B70007 },
    { 0x00ED0000, 0x00ED001A, 0x00E80026, 0x00E80027, 0x00E80028, 0x00ED0006, 0x00ED0007 },
    { 0x00E60000, 0x00E6001A, 0x00E10026, 0x00E10027, 0x00E10028, 0x00E60006, 0x00E60007 },
    { 0x00170000, 0x0017001A, 0x00120026, 0x00120027, 0x00120028, 0x00170006, 0x00170007 },
    { 0x00E00000, 0x00E0001A, 0x00DB0026, 0x00DB0027, 0x00DB0028, 0x00E00006, 0x00E00007 },
    { 0x002D0000, 0x002D001A, 0x00280026, 0x00280027, 0x00280028, 0x002D0006, 0x002D0007 },
    { 0x00C90000, 0x00C9001A, 0x00C40026, 0x00C40027, 0x00C40028, 0x00C90006, 0x00C90007 },
    { 0x00B00000, 0x00B0001A, 0x009C0026, 0x009C0027, 0x009C0028, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B0001A, 0x009C0026, 0x009C0027, 0x009C0028, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B0001A, 0x009C0026, 0x009C0027, 0x009C0028, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B0001A, 0x009C0026, 0x009C0027, 0x009C0028, 0x00B00006, 0x00B00007 }
};

/* The stage actor's four motions (fn_1_ADBC). */
unsigned int lbl_1_data_194[4] = {
    0x0066001A, 0x0066001B, 0x0066001C, 0x0066001D
};

/* files/data/m544.bin: the items, the throws, the arena and the actor (passed to fn_1_9EF8). */
unsigned int lbl_1_data_1A4[27] = {
    0x00660000, 0x00660001, 0x00660002, 0x00660003, 0x00660004, 0x00660005, 0x00660006, 0x00660007,
    0x00660008, 0x00660009, 0x0066000A, 0x0066000B, 0x0066000C, 0x0066000D, 0x0066000E, 0x0066000F,
    0x00660010, 0x00660011, 0x00660012, 0x00660013, 0x00660014, 0x00660015, 0x00660016, 0x00660017,
    0x00660018, 0x00660019, 0x00000000
};

/* The four cameras fn_1_4F0 can create; only camera 0 is. */
M544_CAMERAINIT lbl_1_data_210[4] = {
    { { -12.0f, 208.0f, -120.0f }, { -11.0f, 0.0f, 500.0f }, 141.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { -220.0f, 218.0f, 0.0f }, { -11.0f, -29.0f, 0.0f }, 275.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 238.0f, 0.0f }, { -6.0f, 0.0f, 0.0f }, 695.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_2E0[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1B1C's and fn_1_1E68's debug lines. */
char lbl_1_data_300[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_32E[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_353[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* The dust puff fn_1_24AC and fn_1_2834 edit and spawn. */
M544_PARTICLEPARAM lbl_1_data_370 = {
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

/* fn_1_4020's sound effects. */
s16 lbl_1_data_3A8[6] = {
    0x81D, 0x81E, 0x81F, 0x820, 0x821, 0x2C4
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

OMOBJMAN *lbl_1_bss_818;
M544_WORK lbl_1_bss_530;
M544_MODEL lbl_1_bss_15C[M544_MODEL_MAX];
HU3DMOTID lbl_1_bss_130[3][7];      /* seven motions per duellist, then the actor's four */
M544_GAME lbl_1_bss_D0;
M544_DUELLIST lbl_1_bss_80[2];
M544_HOOK lbl_1_bss_C;
M544_CAMERA *lbl_1_bss_8;
M544_LIGHT *lbl_1_bss_4;
M544_SHADOW *lbl_1_bss_0;

/* asm 61-247, 183 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_818 = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_818);
    fn_1_9EF8(&lbl_1_bss_530, lbl_1_bss_15C, lbl_1_data_1A4);
    lbl_1_bss_8 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M544_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_8, 0, (sizeof(M544_CAMERA)*4)+8);
    lbl_1_bss_4 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M544_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_4, 0, sizeof(M544_LIGHT));
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M544_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M544_SHADOW));
    fn_1_4F0(0);
    fn_1_F38();
    fn_1_1440();
    fn_1_A144(1);
    for(i=0; i<2; i++) {
        fn_1_A3F0(i, lbl_1_data_28[lbl_1_bss_530.chr[i].charNo]);
        fn_1_A410(i, lbl_1_bss_130[i]);
    }
    fn_1_A3F0(2, lbl_1_data_194);
    fn_1_A410(2, lbl_1_bss_130[2]);
    fn_1_A430();
    fn_1_ADBC();
    omAddObjEx(lbl_1_bss_818, 32730, 0, 0, -1, fn_1_A9A4);
    omAddObjEx(lbl_1_bss_818, 32730, 0, 0, -1, fn_1_AF60);
    omAddObjEx(lbl_1_bss_818, 32730, 0, 0, -1, fn_1_4EC);
    fn_1_86BC();
    omAddObjEx(lbl_1_bss_818, 32730, 0, 0, -1, fn_1_89AC);
    omAddObjEx(lbl_1_bss_818, 32730, 0, 0, -1, fn_1_B318);
    Hu3DBGColorSet(186, 245, 255);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 300);
    MgSeqModeDelaySet(2, 320);
    MgSeqModeDelaySet(7, 180);
    MgSeqModeDelaySet(9, 60);
}

/* asm 250-265, 13 insns. Init hook. */
void fn_1_37C(s16 mode, s16 frameNo)
{
    if(fn_1_4328(&lbl_1_bss_530)) {
        MgSeqModeNext();
    }
}

/* asm 268-281, 11 insns. Fade-in hook. */
void fn_1_3B0(s16 mode, s16 frameNo)
{
    if(fn_1_4E08()) {
        MgSeqModeNext();
    }
}

/* asm 284-293, 8 insns. Start hook. */
void fn_1_3DC(s16 mode, s16 frameNo)
{
    fn_1_4E3C();
}

/* asm 296-309, 11 insns. Main hook. */
void fn_1_3FC(s16 mode, s16 frameNo)
{
    if(fn_1_4EB4()) {
        MgSeqModeNext();
    }
}

/* asm 312-321, 8 insns. Finish hook. */
void fn_1_428(s16 mode, s16 frameNo)
{
    fn_1_5098();
}

/* asm 324-337, 11 insns. Pre-winner hook. */
void fn_1_448(s16 mode, s16 frameNo)
{
    if(fn_1_511C()) {
        MgSeqModeNext();
    }
}

/* asm 340-353, 11 insns. Winner hook. */
void fn_1_474(s16 mode, s16 frameNo)
{
    if(fn_1_5158()) {
        MgSeqModeNext();
    }
}

/* asm 356-365, 8 insns. Fade-out hook. */
void fn_1_4A0(s16 mode, s16 frameNo)
{
    fn_1_5514();
}

/* asm 368-381, 11 insns. Close hook. */
void fn_1_4C0(s16 mode, s16 frameNo)
{
    if(fn_1_5544()) {
        MgSeqModeNext();
    }
}

/* asm 384-386, 1 insn. An empty object. */
void fn_1_4EC(OMOBJ *obj)
{
}

/*
 * asm 389-698, 308 insns. Create camera `no` from lbl_1_data_210, then seed
 * the debug camera globals from camera 0's center and rotation and camera
 * `no`'s zoom.
 */
void fn_1_4F0(s16 no)
{
    lbl_1_bss_8[no].no = no;
    lbl_1_bss_8[no].center.x = lbl_1_data_210[no].center.x;
    lbl_1_bss_8[no].center.y = lbl_1_data_210[no].center.y;
    lbl_1_bss_8[no].center.z = lbl_1_data_210[no].center.z;
    lbl_1_bss_8[no].rot.x = lbl_1_data_210[no].rot.x;
    lbl_1_bss_8[no].rot.y = lbl_1_data_210[no].rot.y;
    lbl_1_bss_8[no].rot.z = lbl_1_data_210[no].rot.z;
    lbl_1_bss_8[no].zoom = lbl_1_data_210[no].zoom;
    lbl_1_bss_8[no].aspect = lbl_1_data_210[no].aspect;
    lbl_1_bss_8[no].vpX = lbl_1_data_210[no].vpX;
    lbl_1_bss_8[no].vpY = lbl_1_data_210[no].vpY;
    lbl_1_bss_8[no].vpW = lbl_1_data_210[no].vpW;
    lbl_1_bss_8[no].vpH = lbl_1_data_210[no].vpH;
    lbl_1_bss_8[no].fov = lbl_1_data_210[no].fov;
    Hu3DCameraCreate(lbl_1_data_2E0[no]);
    Hu3DCameraViewportSet(lbl_1_data_2E0[no], lbl_1_bss_8[no].vpX, lbl_1_bss_8[no].vpY, lbl_1_bss_8[no].vpW, lbl_1_bss_8[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_2E0[no], lbl_1_bss_8[no].fov, 20.0f, 30000.0f, lbl_1_bss_8[no].aspect);
    fn_1_9C0(no);
    Center.x = lbl_1_data_210[0].center.x;
    Center.y = lbl_1_data_210[0].center.y;
    Center.z = lbl_1_data_210[0].center.z;
    CRot.x = lbl_1_data_210[0].rot.x;
    CRot.y = lbl_1_data_210[0].rot.y;
    CRot.z = lbl_1_data_210[0].rot.z;
    CZoom = lbl_1_data_210[no].zoom;
}

/* asm 701-1052, 350 insns. Camera `no` from its center, rotation and zoom (m545 fn_1_8C4). */
void fn_1_9C0(s16 no)
{
    lbl_1_bss_8[no].pos.x = lbl_1_bss_8[no].center.x+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].pos.y = lbl_1_bss_8[no].center.y+(lbl_1_bss_8[no].zoom*-sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0));
    lbl_1_bss_8[no].pos.z = lbl_1_bss_8[no].center.z+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].up.x = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    lbl_1_bss_8[no].up.y = cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0);
    lbl_1_bss_8[no].up.z = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_2E0[no], lbl_1_bss_8[no].pos.x, lbl_1_bss_8[no].pos.y, lbl_1_bss_8[no].pos.z,
        lbl_1_bss_8[no].up.x, lbl_1_bss_8[no].up.y, lbl_1_bss_8[no].up.z,
        lbl_1_bss_8[no].center.x, lbl_1_bss_8[no].center.y, lbl_1_bss_8[no].center.z);
}

/* asm 1055-1196, 140 insns. The global light (m545 fn_1_E3C). */
void fn_1_F38(void)
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
    fn_1_1168();
    Hu3DGLightStaticSet(lbl_1_bss_4->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_4->id);
}

/* asm 1199-1382, 182 insns. Place the light from its target, rotation and distance (m545 fn_1_106C). */
void fn_1_1168(void)
{
    lbl_1_bss_4->pos.x = lbl_1_bss_4->target.x+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*sin((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    lbl_1_bss_4->pos.y = lbl_1_bss_4->target.y+(lbl_1_bss_4->dist*-sin((M_PI*lbl_1_bss_4->rot.x)/180.0));
    lbl_1_bss_4->pos.z = lbl_1_bss_4->target.z+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*cos((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_4->target, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    PSVECNormalize(&lbl_1_bss_4->dir, &lbl_1_bss_4->dir);
    Hu3DGLightPosSetV(lbl_1_bss_4->id, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    Hu3DGLightColorSet(lbl_1_bss_4->id, lbl_1_bss_4->color.r, lbl_1_bss_4->color.g, lbl_1_bss_4->color.b, lbl_1_bss_4->color.a);
}

/* asm 1385-1462, 76 insns. The shadow (m545 fn_1_1344). */
void fn_1_1440(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_0->rot.x = -90.0f;
    lbl_1_bss_0->rot.y = 0.0f;
    lbl_1_bss_0->rot.z = 0.0f;
    lbl_1_bss_0->target.x = 0.0f;
    lbl_1_bss_0->target.y = 0.0f;
    lbl_1_bss_0->target.z = -250.0f;
    lbl_1_bss_0->tpLvl = 0.25f;
    lbl_1_bss_0->dist = 1500.0f;
    Hu3DShadowSizeSet(200);
    fn_1_1570();
}

/*
 * asm 1465-1688, 222 insns. Place the shadow camera (m545 fn_1_1474). Retail
 * leaves the target's z out of pos.z.
 */
void fn_1_1570(void)
{
    lbl_1_bss_0->pos.x = lbl_1_bss_0->target.x+(lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0)));
    lbl_1_bss_0->pos.y = lbl_1_bss_0->target.y+(lbl_1_bss_0->dist*-sin((M_PI*lbl_1_bss_0->rot.x)/180.0));
    lbl_1_bss_0->pos.z = lbl_1_bss_0->dist*(cos((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0));
    lbl_1_bss_0->up.x = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*sin((M_PI*lbl_1_bss_0->rot.y)/180.0);
    lbl_1_bss_0->up.y = cos((M_PI*lbl_1_bss_0->rot.x)/180.0);
    lbl_1_bss_0->up.z = sin((M_PI*lbl_1_bss_0->rot.x)/180.0)*cos((M_PI*lbl_1_bss_0->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_0->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_0->pos, &lbl_1_bss_0->up, &lbl_1_bss_0->target);
}

/*
 * asm 1691-1777, 77 insns. Step *value from start towards end by (end-start)/div;
 * the frames left, at least 1, or 0 once it has arrived (and is clamped there).
 */
s16 fn_1_18E8(float *value, float div, float start, float end)
{
    float step;
    s16 count;

    count = 0;
    step = (end-start)/div;
    *value += step;
    if(step) {
        count = (end-*value)/step;
    } else {
        count = 0;
    }
    if(count == 0) {
        count = 1;
    }
    step = M544_DIST(start, end);
    start = M544_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1780-1810, 29 insns. Unreferenced: a timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1A1C(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1813-1825, 11 insns. */
void fn_1_1A90(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1828-1839, 10 insns. Unreferenced. */
BOOL fn_1_1ABC(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1842-1857, 14 insns. */
void fn_1_1AE4(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1860-2084, 211 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1B1C(M544_WORK *work, s16 padNo, s16 no)
{
    M544_MODEL *model;
    s16 result;

    result = 0;
    model = &work->models[no];
    if(HuPadStkX[padNo] > 10) {
        model->pos.x += 1.0f;
    }
    if(HuPadStkX[padNo] < -10) {
        model->pos.x -= 1.0f;
    }
    if(HuPadStkY[padNo] > 10) {
        model->pos.y += 1.0f;
    }
    if(HuPadStkY[padNo] < -10) {
        model->pos.y -= 1.0f;
    }
    if(HuPadTrigL[padNo] > 10) {
        model->pos.z += 1.0f;
    }
    if(HuPadTrigR[padNo] > 10) {
        model->pos.z -= 1.0f;
    }
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
    print8(25, 136, 1.5f, lbl_1_data_300, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    return result;
}

/* asm 2087-2424, 306 insns. Unreferenced debug: move the camera globals with pad padNo. */
void fn_1_1E68(s16 padNo)
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
    fontcolor = 0;
    print8(25, 30, 1.5f, lbl_1_data_32E, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_353, CRot.x, CRot.y, CRot.z);
}

/* asm 2427-2525, 95 insns. The dust particle model (m545 fn_1_17EC without the id clears). */
void fn_1_2330(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x66001F, HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_820 = HuMemDirectMallocNum(HEAP_HEAP, 50*sizeof(M544_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_826 = Hu3DParticleCreate(anim, 50);
    Hu3DParticleHookSet(lbl_1_bss_826, fn_1_30B8);
    Hu3DModelLayerSet(lbl_1_bss_826, 3);
    Hu3DModelCameraSet(lbl_1_bss_826, 1);
    Hu3DModelAttrSet(lbl_1_bss_826, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_826, HU3D_ATTR_DISPOFF);
    Hu3DParticleBlendModeSet(lbl_1_bss_826, 1);
    particle = Hu3DData[lbl_1_bss_826].hookData;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_820;
    particle->count = 0;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 2528-2757, 226 insns. Unreferenced: twelve dust puffs in a ring around pos. */
void fn_1_24AC(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    for(i=0; i<12; i++) {
        size = 6.0+frandmod(6);
        lbl_1_data_370.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_370.vel.y = 0.0f;
        lbl_1_data_370.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_370.alphaSpeed = alpha;
        puffPos.x = pos->x+(20.0*sin((M_PI*(30.0f*i))/180.0));
        puffPos.y = 10.0f+pos->y;
        puffPos.z = pos->z+(20.0*cos((M_PI*(30.0f*i))/180.0));
        lbl_1_data_370.accelY = 0.01*frandmod(20);
        size = 20.0+frandmod(20);
        fn_1_2EE4(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_370);
    }
}

/*
 * asm 2760-3195, 428 insns. A burst of dust where an item lands: 48 puffs up a
 * vertical arc (side 0, dropped from the hook) or 36 across a horizontal one.
 * pos is moved first.
 */
void fn_1_2834(HuVecF *pos, s16 side)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    if(side == 0) {
        pos->y += 50.0f;
        for(i=0; i<48; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_370.vel.x = frandmod(10)-5.0f;
            lbl_1_data_370.vel.y = size*sin((M_PI*(7.5f*i))/180.0);
            lbl_1_data_370.vel.z = frandmod(2);
            alpha = -frandmod(6)-5;
            lbl_1_data_370.alphaSpeed = alpha;
            puffPos.x = (pos->x+frandmod(30))-15.0f;
            puffPos.y = pos->y+(40.0*sin((M_PI*(7.5f*i))/180.0));
            puffPos.z = 20.0f+pos->z;
            lbl_1_data_370.accelY = 0.01f*frandmod(20);
            size = 20.0+frandmod(20);
            fn_1_2EE4(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_370);
        }
    } else {
        pos->x -= 20.0f;
        pos->z += 50.0f;
        for(i=0; i<36; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_370.vel.x = frandmod(4)-2.0f;
            lbl_1_data_370.vel.y = frandmod(6)-3.0f;
            lbl_1_data_370.vel.z = size*sin((M_PI*(10.0f*i))/180.0);
            alpha = -frandmod(6)-5;
            lbl_1_data_370.alphaSpeed = alpha;
            puffPos.x = pos->x+frandmod(3);
            puffPos.y = (pos->y+frandmod(30))-15.0f;
            puffPos.z = pos->z+(40.0*sin((M_PI*(10.0f*i))/180.0));
            lbl_1_data_370.accelY = 0.01f*frandmod(20);
            size = 20.0+frandmod(20);
            fn_1_2EE4(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_370);
        }
    }
}

/* asm 3198-3323, 117 insns. Spawn one dust particle; the slot, or -1 when all are live (m545 fn_1_1D4C). */
s16 fn_1_2EE4(float x, float y, float z, float scale, M544_PARTICLEPARAM *param)
{
    HU3DMODEL *model;
    M544_PARTICLEPARAM *work;
    s16 result;
    s16 i;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    result = -1;
    model = &Hu3DData[lbl_1_bss_826];
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

/* asm 3326-3600, 262 insns. The dust hook: move, fade and shrink every live puff (m545 fn_1_1F20). */
void fn_1_30B8(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M544_PARTICLEPARAM *param;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 value;

    param = particle->work;
    data = particle->data;
    for(i=0, data->time=0; i<particle->maxCnt; i++, data++) {
        if(data->scale > 0.0f) {
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
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* asm 3603-3671, 67 insns. The one-particle flash model. */
void fn_1_34D0(void)
{
    HU3DPARTICLE *particle;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x66001E, HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_824 = Hu3DParticleCreate(anim, 1);
    Hu3DParticleHookSet(lbl_1_bss_824, fn_1_3AD4);
    Hu3DParticleBlendModeSet(lbl_1_bss_824, 0);
    Hu3DModelLayerSet(lbl_1_bss_824, 7);
    Hu3DModelAttrSet(lbl_1_bss_824, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_824, HU3D_ATTR_DISPOFF);
    lbl_1_bss_D0.flashF = 0;
    particle = Hu3DData[lbl_1_bss_824].hookData;
    particle->data->scale = 0.0f;
}

/*
 * asm 3674-3940, 259 insns. Flash above a fooled duellist's head (player 2 or
 * more: the loser), offset per character: player 0 from rodata_D8, player 1
 * from rodata_210.
 */
void fn_1_35DC(s16 player)
{
    HuVecF target;
    HuVecF start;
    HuVecF pos;
    float height[13] = { 150.0f, 170.0f, 188.0f, 169.0f, 164.0f, 180.0f, 204.0f, 103.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f };
    HuVecF offsetNear[13][2] = {
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { -10.0f, -50.0f, 0.0f }, { -10.0f, 50.0f, 0.0f } },
        { { -10.0f, -50.0f, 0.0f }, { -10.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { -10.0f, -50.0f, 0.0f }, { -10.0f, 50.0f, 0.0f } },
        { { 40.0f, -50.0f, 0.0f }, { 40.0f, 50.0f, 0.0f } },
        { { -5.0f, -50.0f, -10.0f }, { -5.0f, 60.0f, -10.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } },
        { { 0.0f, -50.0f, 0.0f }, { 0.0f, 50.0f, 0.0f } }
    };
    HuVecF offsetFar[13][2] = {
        { { 20.0f, -50.0f, 0.0f }, { 20.0f, 50.0f, 0.0f } },
        { { 20.0f, -50.0f, 0.0f }, { 20.0f, 50.0f, 0.0f } },
        { { 20.0f, -50.0f, -5.0f }, { 20.0f, 50.0f, -5.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 20.0f, -50.0f, -5.0f }, { 20.0f, 50.0f, -5.0f } },
        { { -25.0f, -50.0f, 0.0f }, { -25.0f, 50.0f, 0.0f } },
        { { 30.0f, -50.0f, 0.0f }, { 30.0f, 60.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } },
        { { 10.0f, -50.0f, 0.0f }, { 10.0f, 50.0f, 0.0f } }
    };
    s16 charNo;
    float scale;

    charNo = lbl_1_bss_914->chr[player].charNo;
    if(charNo >= 13) {
        charNo = 6;
    }
    if(player >= 2) {
        player = (lbl_1_bss_D0.result & 2) >> 1;
    }
    pos = lbl_1_bss_914->models[player+32].pos;
    target = pos;
    start = pos;
    if(player == 0) {
        target.x += offsetNear[charNo][0].x;
        target.y += offsetNear[charNo][0].y+height[charNo];
        target.z += offsetNear[charNo][0].z;
        start.x += offsetNear[charNo][1].x;
        start.y += offsetNear[charNo][1].y+height[charNo];
        start.z += offsetNear[charNo][1].z;
        scale = 35.0f;
    } else {
        target.x += offsetFar[charNo][0].x;
        target.y += offsetFar[charNo][0].y+height[charNo];
        target.z += offsetFar[charNo][0].z;
        start.x += offsetFar[charNo][1].x;
        start.y += offsetFar[charNo][1].y+height[charNo];
        start.z += offsetFar[charNo][1].z;
        scale = 50.0f;
    }
    fn_1_39E8(target, start, scale);
}

/* asm 3943-4004, 59 insns. Start the flash at pos, heading for target. */
void fn_1_39E8(HuVecF pos, HuVecF target, float scale)
{
    HU3DMODEL *model;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    model = &Hu3DData[lbl_1_bss_824];
    particle = model->hookData;
    data = particle->data;
    data->time = 0;
    data->parManId = 0;
    data->pos = pos;
    data->vel = pos;
    data->accel = target;
    data->color.r = 255;
    data->color.g = 255;
    data->color.b = 255;
    data->color.a = 255;
    data->scale = scale;
    if(data->scale) {
        lbl_1_bss_D0.flashF = 1;
    }
}

/*
 * asm 4007-4295, 265 insns. The flash hook: rise from vel.y to accel.y over
 * ten frames, drop 20 over three, hold 40 frames, then fade out.
 */
void fn_1_3AD4(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    HU3DPARTICLEDATA *data;
    s16 done;

    data = particle->data;
    done = 0;
    if(data->scale > 0.0f) {
        switch(data->time) {
            case 0:
                done += fn_1_18E8(&data->pos.y, 10.0f, data->vel.y, data->accel.y);
                if(done == 0) {
                    data->vel = data->pos;
                    data->accel = data->pos;
                    data->accel.y -= 20.0f;
                    data->speedDecay = 3.0f;
                    data->time++;
                }
                break;

            case 1:
                done += fn_1_18E8(&data->pos.y, 3.0f, data->vel.y, data->accel.y);
                if(done == 0) {
                    data->time++;
                }
                break;

            case 2:
                if(data->parManId++ > 40) {
                    data->time++;
                }
                break;

            case 3:
                if((data->color.a -= 50) < 50) {
                    data->color.a = 0;
                    data->scale = 0.0f;
                }
                break;
        }
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* asm 4298-4311, 12 insns. */
void fn_1_3EF8(void)
{
    lbl_1_bss_D0.jingleNo = HuAudJinglePlay(131);
}

/* asm 4314-4327, 12 insns. */
void fn_1_3F28(void)
{
    lbl_1_bss_D0.bgmNo = HuAudBGMPlay(59);
}

/* asm 4330-4359, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_3F58(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_D0.bgmNo;
    } else {
        no = lbl_1_bss_D0.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 4362-4389, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_3FC0(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_D0.bgmNo;
    } else {
        no = lbl_1_bss_D0.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 4392-4423, 30 insns. */
void fn_1_4020(s16 no)
{
    lbl_1_bss_D0.seF[no] = 1;
    lbl_1_bss_D0.seNo[no] = HuAudFXPlay(lbl_1_data_3A8[no]);
}

/* asm 4426-4461, 34 insns. */
void fn_1_4098(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_D0.seF[no] = 1;
    lbl_1_bss_D0.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_3A8[no], vol, pan);
}

/* asm 4464-4502, 36 insns. */
void fn_1_4120(s16 no, s16 pan)
{
    if(lbl_1_bss_D0.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_D0.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_D0.seNo[no], pan);
    }
}

/* asm 4505-4551, 43 insns. Unreferenced; fn_1_425C is the same. */
void fn_1_41B0(s16 no)
{
    if(lbl_1_bss_D0.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_D0.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_D0.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_D0.seNo[no]);
    }
}

/* asm 4554-4600, 43 insns. */
void fn_1_425C(s16 no)
{
    if(lbl_1_bss_D0.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_D0.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_D0.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_D0.seNo[no]);
    }
}

/* asm 4603-4612, 8 insns. */
void fn_1_4308(void)
{
    HuAudAllStop();
}
