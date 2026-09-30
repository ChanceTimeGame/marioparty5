/*
 * m553dll -- a KETTOU duel (overlay #67): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, the dust particles, the duellists' material
 * fades and the sound helpers. Written from the reference assembly, functions
 * in reference order; line ranges are into
 * build/mp5-asm/m553Dll/asm/REL/m553Dll/m553.s.
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
#include "game/mg/actman.h"

#include "datadir_enum.h"

#include "REL/m553Dll/m553.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M553_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

void ObjectSetup(void);
void fn_1_2F0(s16 mode, s16 frameNo);
void fn_1_324(s16 mode, s16 frameNo);
void fn_1_350(s16 mode, s16 frameNo);
void fn_1_37C(s16 mode, s16 frameNo);
void fn_1_3A8(s16 mode, s16 frameNo);
void fn_1_3D4(s16 mode, s16 frameNo);
void fn_1_400(s16 mode, s16 frameNo);
void fn_1_42C(s16 mode, s16 frameNo);
void fn_1_44C(s16 mode, s16 frameNo);
void fn_1_478(OMOBJ *obj);
/* game.c defines these returning s16; the hooks test the whole register, as retail's calls without a prototype did. */
s32 fn_1_6064(M553_WORK *work);
s32 fn_1_6170(void);
s32 fn_1_61A8(void);
s32 fn_1_6218(void);
s32 fn_1_6850(void);
s32 fn_1_6928(void);
s32 fn_1_6964(void);
s32 fn_1_6BDC(void);
s32 fn_1_6C0C(void);
void fn_1_47C(s16 no);
void fn_1_94C(s16 no);
void fn_1_EC4(void);
void fn_1_10F4(void);
void fn_1_13CC(void);
void fn_1_14F4(void);
s16 fn_1_2D1C(s16 time, float x, float y, float z, float scale, float scaleBase, s16 parManId, M553_PARTICLEPARAM *param);
void fn_1_2E8C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
/* stage.c */
void fn_1_D9A4(M553_WORK *work, M553_MODEL *models, unsigned int *dataTbl);
void fn_1_DBF0(s16 stageNo);
void fn_1_E234(s16 no, unsigned int *data);
void fn_1_E254(s16 no, HU3DMOTID *id);
void fn_1_E844(OMOBJ *obj);
void fn_1_EC64(OMOBJ *obj);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_2F0,
    fn_1_324,
    fn_1_350,
    fn_1_37C,
    fn_1_3A8,
    fn_1_3D4,
    fn_1_400,
    fn_1_42C,
    fn_1_44C
};

/* Five motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][5] = {
    { 0x008C0000, 0x008C0002, 0x008C001A, 0x008C002F, 0x008C0007 },
    { 0x00330000, 0x00330002, 0x0033001A, 0x0033002F, 0x00330007 },
    { 0x00B70000, 0x00B70002, 0x00B7001A, 0x00B7002F, 0x00B70007 },
    { 0x00ED0000, 0x00ED0002, 0x00ED001A, 0x00ED002F, 0x00ED0007 },
    { 0x00E60000, 0x00E60002, 0x00E6001A, 0x00E6002F, 0x00E60007 },
    { 0x00170000, 0x00170002, 0x0017001A, 0x0017002F, 0x00170007 },
    { 0x00E00000, 0x00E00002, 0x00E0001A, 0x00E0002F, 0x00E00007 },
    { 0x002D0000, 0x002D0002, 0x002D001A, 0x002D002F, 0x002D0007 },
    { 0x00C90000, 0x00C90002, 0x00C9001A, 0x00C9002F, 0x00C90007 },
    { 0x00B00000, 0x00B00002, 0x00B0001A, 0x00B0002F, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0001A, 0x00B0002F, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0001A, 0x00B0002F, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0001A, 0x00B0002F, 0x00B00007 }
};

/* files/data/m553.bin: the stage models (passed to fn_1_D9A4). */
unsigned int lbl_1_data_12C[25] = {
    0x006F0000, 0x006F0001, 0x006F0002, 0x006F0003, 0x006F0004, 0x006F0005, 0x006F0006, 0x006F0007,
    0x006F0008, 0x006F0009, 0x006F000A, 0x006F000B, 0x006F000D, 0x006F000E, 0x006F000F, 0x006F0010,
    0x006F0011, 0x006F0012, 0x006F0013, 0x006F0014, 0x006F0015, 0x006F0016, 0x006F0017, 0x006F0018,
    0x006F001B
};

/* The four cameras fn_1_47C can create; only camera 0 is. */
M553_CAMERAINIT lbl_1_data_190[4] = {
    { { 0.0f, 194.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, 50.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 194.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, 1732.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 206.0f, 0.0f }, { -32.0f, 0.0f, 0.0f }, 1732.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_260[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1BBC's and fn_1_1F14's debug lines. */
char lbl_1_data_280[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_2AE[] = "OBJW %d";
char lbl_1_data_2B6[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_2DB[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* The dust puff fn_1_28D4 and fn_1_2B4C edit and spawn. */
M553_PARTICLEPARAM lbl_1_data_2F8 = {
    0.0f,
    { 255, 255, 255, 255 },
    { 0, 0, 0, 255 },
    { 0.0f, 2.0f, 1.0f },
    { 0.85f, 0.85f, 0.85f },
    0.2f,
    0.0f,
    1.0f,
    -5.0f,
    0.02f
};

/* fn_1_37DC's sound effects. */
s16 lbl_1_data_330[24] = {
    0x88C, 0x878, 0x879, 0x87A, 0x87B, 0x87C, 0x87D, 0x87E,
    0x87F, 0x880, 0x881, 0x882, 0x883, 0x884, 0x885, 0x886,
    0x887, 0x888, 0x889, 0x88A, 0x88B, 0x319, 0, 0
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

/* lbl_1_bss_1EF0 and lbl_1_bss_1EF4 are unreferenced; they are why dtk sizes
 * lbl_1_bss_1EEC as 12 bytes, and lbl_1_bss_1EE4 is why it sizes 1EE0 as 8. */
u32 lbl_1_bss_1EF4;
u32 lbl_1_bss_1EF0;
HU3DMODELID lbl_1_bss_1EEC;
M553_PARTICLEPARAM *lbl_1_bss_1EE8;
u32 lbl_1_bss_1EE4;
OMOBJMAN *lbl_1_bss_1EE0;
M553_WORK lbl_1_bss_16DC;
M553_MODEL lbl_1_bss_7FC[M553_MODEL_MAX];
HU3DMOTID lbl_1_bss_7E8[2][5];
M553_GAME lbl_1_bss_70C;
M553_DUELLIST lbl_1_bss_48C[2];
M553_STATE lbl_1_bss_478;
M553_STAGEOBJ lbl_1_bss_18[35];
M553_CAMERA *lbl_1_bss_14;
M553_LIGHT *lbl_1_bss_10;
M553_SHADOW *lbl_1_bss_C;
M553_ACTORS lbl_1_bss_0;

/* asm 47-164, 148 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_1EE0 = MgActorObjectSetup();
    fn_1_D9A4(&lbl_1_bss_16DC, lbl_1_bss_7FC, lbl_1_data_12C);
    lbl_1_bss_14 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M553_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_14, 0, (sizeof(M553_CAMERA)*4)+8);
    lbl_1_bss_10 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M553_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_10, 0, sizeof(M553_LIGHT));
    lbl_1_bss_C = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M553_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_C, 0, sizeof(M553_SHADOW));
    fn_1_47C(0);
    fn_1_EC4();
    fn_1_13CC();
    fn_1_DBF0(1);
    fn_1_E234(0, lbl_1_data_28[lbl_1_bss_16DC.chr[0].charNo]);
    fn_1_E234(1, lbl_1_data_28[lbl_1_bss_16DC.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_E254(i, lbl_1_bss_7E8[i]);
    }
    omAddObjEx(lbl_1_bss_1EE0, 32730, 0, 0, -1, fn_1_E844);
    omAddObjEx(lbl_1_bss_1EE0, 32730, 0, 0, -1, fn_1_478);
    omAddObjEx(lbl_1_bss_1EE0, 32730, 0, 0, -1, fn_1_EC64);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 6000);
    MgSeqModeDelaySet(7, 6000);
    MgSeqModeDelaySet(9, 60);
}

/* asm 165-179, 13 insns. Init hook. */
void fn_1_2F0(s16 mode, s16 frameNo)
{
    if(fn_1_6064(&lbl_1_bss_16DC)) {
        MgSeqModeNext();
    }
}

/* asm 180-193, 11 insns. Fade-in hook. */
void fn_1_324(s16 mode, s16 frameNo)
{
    if(fn_1_6170()) {
        MgSeqModeNext();
    }
}

/* asm 194-207, 11 insns. Start hook. */
void fn_1_350(s16 mode, s16 frameNo)
{
    if(fn_1_61A8()) {
        MgSeqModeNext();
    }
}

/* asm 208-221, 11 insns. Main hook. */
void fn_1_37C(s16 mode, s16 frameNo)
{
    if(fn_1_6218()) {
        MgSeqModeNext();
    }
}

/* asm 222-235, 11 insns. Finish hook. */
void fn_1_3A8(s16 mode, s16 frameNo)
{
    if(fn_1_6850()) {
        MgSeqModeNext();
    }
}

/* asm 236-249, 11 insns. Pre-winner hook. */
void fn_1_3D4(s16 mode, s16 frameNo)
{
    if(fn_1_6928()) {
        MgSeqModeNext();
    }
}

/* asm 250-263, 11 insns. Winner hook. */
void fn_1_400(s16 mode, s16 frameNo)
{
    if(fn_1_6964()) {
        MgSeqModeNext();
    }
}

/* asm 264-273, 8 insns. Fade-out hook. */
void fn_1_42C(s16 mode, s16 frameNo)
{
    fn_1_6BDC();
}

/* asm 274-287, 11 insns. Close hook. */
void fn_1_44C(s16 mode, s16 frameNo)
{
    if(fn_1_6C0C()) {
        MgSeqModeNext();
    }
}

/* asm 288-290, 1 insn. An empty object. */
void fn_1_478(OMOBJ *obj)
{
}

/*
 * 308 insns. Create camera `no` from lbl_1_data_190, then seed the debug camera
 * globals from camera 0's center and rotation and camera `no`'s zoom.
 */
void fn_1_47C(s16 no)
{
    lbl_1_bss_14[no].no = no;
    lbl_1_bss_14[no].center.x = lbl_1_data_190[no].center.x;
    lbl_1_bss_14[no].center.y = lbl_1_data_190[no].center.y;
    lbl_1_bss_14[no].center.z = lbl_1_data_190[no].center.z;
    lbl_1_bss_14[no].rot.x = lbl_1_data_190[no].rot.x;
    lbl_1_bss_14[no].rot.y = lbl_1_data_190[no].rot.y;
    lbl_1_bss_14[no].rot.z = lbl_1_data_190[no].rot.z;
    lbl_1_bss_14[no].zoom = lbl_1_data_190[no].zoom;
    lbl_1_bss_14[no].aspect = lbl_1_data_190[no].aspect;
    lbl_1_bss_14[no].vpX = lbl_1_data_190[no].vpX;
    lbl_1_bss_14[no].vpY = lbl_1_data_190[no].vpY;
    lbl_1_bss_14[no].vpW = lbl_1_data_190[no].vpW;
    lbl_1_bss_14[no].vpH = lbl_1_data_190[no].vpH;
    lbl_1_bss_14[no].fov = lbl_1_data_190[no].fov;
    Hu3DCameraCreate(lbl_1_data_260[no]);
    Hu3DCameraViewportSet(lbl_1_data_260[no], lbl_1_bss_14[no].vpX, lbl_1_bss_14[no].vpY, lbl_1_bss_14[no].vpW, lbl_1_bss_14[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_260[no], lbl_1_bss_14[no].fov, 20.0f, 40000.0f, lbl_1_bss_14[no].aspect);
    fn_1_94C(no);
    Center.x = lbl_1_data_190[0].center.x;
    Center.y = lbl_1_data_190[0].center.y;
    Center.z = lbl_1_data_190[0].center.z;
    CRot.x = lbl_1_data_190[0].rot.x;
    CRot.y = lbl_1_data_190[0].rot.y;
    CRot.z = lbl_1_data_190[0].rot.z;
    CZoom = lbl_1_data_190[no].zoom;
}

/* 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_94C(s16 no)
{
    lbl_1_bss_14[no].pos.x = lbl_1_bss_14[no].center.x+(lbl_1_bss_14[no].zoom*(cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_14[no].rot.y)/180.0)));
    lbl_1_bss_14[no].pos.y = lbl_1_bss_14[no].center.y+(lbl_1_bss_14[no].zoom*-sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0));
    lbl_1_bss_14[no].pos.z = lbl_1_bss_14[no].center.z+(lbl_1_bss_14[no].zoom*(cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_14[no].rot.y)/180.0)));
    lbl_1_bss_14[no].up.x = sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_14[no].rot.y)/180.0);
    lbl_1_bss_14[no].up.y = cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0);
    lbl_1_bss_14[no].up.z = sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_14[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_260[no], lbl_1_bss_14[no].pos.x, lbl_1_bss_14[no].pos.y, lbl_1_bss_14[no].pos.z,
        lbl_1_bss_14[no].up.x, lbl_1_bss_14[no].up.y, lbl_1_bss_14[no].up.z,
        lbl_1_bss_14[no].center.x, lbl_1_bss_14[no].center.y, lbl_1_bss_14[no].center.z);
}

/* 140 insns. The global light. */
void fn_1_EC4(void)
{
    Hu3DLighInit();
    lbl_1_bss_10->pos.x = 0.0f;
    lbl_1_bss_10->pos.y = 0.0f;
    lbl_1_bss_10->pos.z = 0.0f;
    lbl_1_bss_10->target.x = 0.0f;
    lbl_1_bss_10->target.y = 0.0f;
    lbl_1_bss_10->target.z = 0.0f;
    lbl_1_bss_10->rot.x = -45.0f;
    lbl_1_bss_10->rot.y = 0.0f;
    lbl_1_bss_10->rot.z = 0.0f;
    lbl_1_bss_10->dist = 1000.0f;
    lbl_1_bss_10->color.r = 255;
    lbl_1_bss_10->color.g = 255;
    lbl_1_bss_10->color.b = 255;
    lbl_1_bss_10->color.a = 255;
    PSVECSubtract(&lbl_1_bss_10->target, &lbl_1_bss_10->pos, &lbl_1_bss_10->dir);
    lbl_1_bss_10->id = Hu3DGLightCreateV(&lbl_1_bss_10->pos, &lbl_1_bss_10->dir, &lbl_1_bss_10->color);
    fn_1_10F4();
    Hu3DGLightStaticSet(lbl_1_bss_10->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_10->id);
}

/* 182 insns. Place the light from its target, rotation and distance. */
void fn_1_10F4(void)
{
    lbl_1_bss_10->pos.x = lbl_1_bss_10->target.x+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*sin((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    lbl_1_bss_10->pos.y = lbl_1_bss_10->target.y+(lbl_1_bss_10->dist*-sin((M_PI*lbl_1_bss_10->rot.x)/180.0));
    lbl_1_bss_10->pos.z = lbl_1_bss_10->target.z+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*cos((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_10->target, &lbl_1_bss_10->pos, &lbl_1_bss_10->dir);
    PSVECNormalize(&lbl_1_bss_10->dir, &lbl_1_bss_10->dir);
    Hu3DGLightPosSetV(lbl_1_bss_10->id, &lbl_1_bss_10->pos, &lbl_1_bss_10->dir);
    Hu3DGLightColorSet(lbl_1_bss_10->id, lbl_1_bss_10->color.r, lbl_1_bss_10->color.g, lbl_1_bss_10->color.b, lbl_1_bss_10->color.a);
}

/* 74 insns. The shadow. */
void fn_1_13CC(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 40000.0f);
    lbl_1_bss_C->rot.x = -70.0f;
    lbl_1_bss_C->rot.y = 0.0f;
    lbl_1_bss_C->rot.z = 0.0f;
    lbl_1_bss_C->target.x = 0.0f;
    lbl_1_bss_C->target.y = 0.0f;
    lbl_1_bss_C->target.z = 0.0f;
    lbl_1_bss_C->tpLvl = 0.5f;
    lbl_1_bss_C->dist = 2800.0f;
    fn_1_14F4();
}

/* 227 insns. Place the shadow camera. */
void fn_1_14F4(void)
{
    lbl_1_bss_C->pos.x = lbl_1_bss_C->target.x+(lbl_1_bss_C->dist*(cos((M_PI*lbl_1_bss_C->rot.x)/180.0)*sin((M_PI*lbl_1_bss_C->rot.y)/180.0)));
    lbl_1_bss_C->pos.y = lbl_1_bss_C->target.y+(lbl_1_bss_C->dist*-sin((M_PI*lbl_1_bss_C->rot.x)/180.0));
    lbl_1_bss_C->pos.z = lbl_1_bss_C->target.z+(lbl_1_bss_C->dist*(cos((M_PI*lbl_1_bss_C->rot.x)/180.0)*cos((M_PI*lbl_1_bss_C->rot.y)/180.0)));
    lbl_1_bss_C->up.x = sin((M_PI*lbl_1_bss_C->rot.x)/180.0)*sin((M_PI*lbl_1_bss_C->rot.y)/180.0);
    lbl_1_bss_C->up.y = cos((M_PI*lbl_1_bss_C->rot.x)/180.0);
    lbl_1_bss_C->up.z = sin((M_PI*lbl_1_bss_C->rot.x)/180.0)*cos((M_PI*lbl_1_bss_C->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_C->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_C->pos, &lbl_1_bss_C->up, &lbl_1_bss_C->target);
}

/* 72 insns. Step *value toward end by (end-start)/div; the steps left, 0 once there. */
s16 fn_1_1880(float *value, float div, float start, float end)
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
    step = M553_DIST(start, end);
    start = M553_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* 71 insns. Unreferenced: fn_1_1880 without the final clamp to end. */
s16 fn_1_19A0(float *value, float div, float start, float end)
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
    step = M553_DIST(start, end);
    start = M553_DIST(start, *value);
    if(step <= start) {
        count = 0;
    }
    return count;
}

/* 29 insns. A timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1ABC(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* 11 insns. */
void fn_1_1B30(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* 10 insns. */
BOOL fn_1_1B5C(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* 14 insns. */
void fn_1_1B84(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* 213 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1BBC(M553_WORK *work, s16 padNo, s16 no)
{
    M553_MODEL *model;
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
    print8(25, 136, 1.5f, lbl_1_data_280, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_2AE, no);
    return result;
}

/* 1 insn. */
void fn_1_1F10(void)
{
}

/* 302 insns. Unreferenced debug: move the camera globals with pad padNo. */
void fn_1_1F14(s16 padNo)
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
    print8(25, 30, 1.5f, lbl_1_data_2B6, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_2DB, CRot.x, CRot.y, CRot.z);
}

/* 96 insns. The dust particle model: 1000 puffs on layer 6. */
void fn_1_23CC(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m553, 0x0C), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_1EE8 = HuMemDirectMallocNum(HEAP_HEAP, 1000*sizeof(M553_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_1EEC = Hu3DParticleCreate(anim, 1000);
    Hu3DParticleHookSet(lbl_1_bss_1EEC, fn_1_2E8C);
    Hu3DParticleBlendModeSet(lbl_1_bss_1EEC, 1);
    Hu3DModelLayerSet(lbl_1_bss_1EEC, 6);
    Hu3DModelCameraSet(lbl_1_bss_1EEC, 1);
    Hu3DModelAttrSet(lbl_1_bss_1EEC, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_1EEC, HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_1EEC].hookData;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_1EE8;
    particle->count = 0;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* 226 insns. Twelve dust puffs in a 30-degree ring around pos. */
void fn_1_254C(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    for(i=0; i<12; i++) {
        size = 6.0f+frandmod(6);
        lbl_1_data_2F8.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_2F8.vel.y = 0.0f;
        lbl_1_data_2F8.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_2F8.alphaSpeed = alpha;
        puffPos.x = pos->x+(20.0*sin((M_PI*(30.0f*i))/180.0));
        puffPos.y = 10.0f+pos->y;
        puffPos.z = pos->z+(20.0*cos((M_PI*(30.0f*i))/180.0));
        lbl_1_data_2F8.accelY = 0.01f*frandmod(20);
        size = 20.0f+frandmod(20);
        fn_1_2D1C(0, puffPos.x, puffPos.y, puffPos.z, size, size, 60, &lbl_1_data_2F8);
    }
}

/* 158 insns. Thirty dust puffs scattered around pos. */
void fn_1_28D4(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    for(i=0; i<30; i++) {
        puffPos.x = pos->x+(frandmod(120)-60.0f);
        puffPos.y = pos->y+(frandmod(100)-100.0f);
        puffPos.z = 60.0f+pos->z;
        lbl_1_data_2F8.vel.x = frandmod(4)-2.0f;
        lbl_1_data_2F8.vel.y = frandmod(8);
        lbl_1_data_2F8.vel.z = 0.0f;
        alpha = -frandmod(6)-5;
        lbl_1_data_2F8.alphaSpeed = alpha;
        lbl_1_data_2F8.accelY = 0.01f*frandmod(20);
        size = 20.0f+frandmod(40);
        fn_1_2D1C(0, puffPos.x, puffPos.y, puffPos.z, size, size, 60, &lbl_1_data_2F8);
    }
}

/* 116 insns. Ten slower puffs rising from pos. */
void fn_1_2B4C(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;

    for(i=0; i<10; i++) {
        puffPos.x = pos->x+(frandmod(110)-55.0f);
        puffPos.y = pos->y-10.0f;
        puffPos.z = 55.0f+pos->z;
        lbl_1_data_2F8.vel.x = 0.1f;
        lbl_1_data_2F8.vel.y = 0.1f*(6.0f+frandmod(8));
        lbl_1_data_2F8.vel.z = 0.0f;
        lbl_1_data_2F8.accelY = 0.0f;
        size = 7.0f+frandmod(10);
        fn_1_2D1C(1, puffPos.x, puffPos.y, puffPos.z, size, 1.0f, 40, &lbl_1_data_2F8);
    }
}

/* 92 insns. Spawn one dust puff into the first free slot; the slot, or -1. */
s16 fn_1_2D1C(s16 time, float x, float y, float z, float scale, float scaleBase, s16 parManId, M553_PARTICLEPARAM *param)
{
    HU3DMODEL *model;
    M553_PARTICLEPARAM *work;
    s16 result;
    s16 i;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    result = -1;
    model = &Hu3DData[lbl_1_bss_1EEC];
    particle = model->hookData;
    work = particle->work;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        if(data->scale == 0.0f) {
            work[i] = *param;
            data->pos.x = x;
            data->pos.y = y;
            data->pos.z = z;
            data->vel = param->vel;
            data->color = param->color;
            data->scaleBase = scaleBase;
            data->scale = scale;
            data->time = time;
            data->parManId = parManId;
            particle->emitCnt = i;
            result = i;
            break;
        }
    }
    return result;
}

/*
 * 305 insns. The dust hook: move, fade and shrink every live puff. A puff whose
 * time is 0 runs the full update; any other just drifts and fades six a frame.
 * parManId counts its life down. Retail counts the live puffs and never reads
 * the count.
 */
void fn_1_2E8C(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M553_PARTICLEPARAM *param;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 value;
    s16 liveNum;
    s16 fade;

    param = particle->work;
    liveNum = 0;
    data = particle->data;
    for(i=0; i<particle->maxCnt; i++, data++) {
        if(data->scale > 0.0f) {
            liveNum++;
            if(data->time == 0) {
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
                if(value < 0) {
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
                data->parManId--;
                if(data->parManId <= 0) {
                    data->scale = 0.0f;
                }
            } else {
                PSVECAdd(&data->vel, &data->pos, &data->pos);
                fade = 6;
                value = data->color.a-fade;
                if(value < 0) {
                    value = 0;
                } else if(value > 255) {
                    value = 255;
                }
                data->color.a = value;
                data->scale += data->scaleBase;
                data->parManId--;
                if(data->parManId <= 0) {
                    data->scale = 0.0f;
                }
            }
        }
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* 62 insns. Unreferenced: keep a copy of player's material colours. */
void fn_1_3350(s16 player)
{
    s16 unused;
    HSFMATERIAL *mat;
    s8 *buf;
    HU3DMODEL *model;
    s16 i;

    unused = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_48C[player].matColor = HuMemDirectMallocNum(HEAP_HEAP, model->hsf->materialNum*3, HU_MEMNUM_OVL);
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        *buf++ = mat->color[0];
        *buf++ = mat->color[1];
        *buf++ = mat->color[2];
    }
}

/* 92 insns. Unreferenced: scale player's material colours. */
s16 fn_1_3448(s16 player, float scale)
{
    s16 result;
    HU3DMODEL *model;
    HSFMATERIAL *mat;
    s16 i;

    result = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    if((lbl_1_bss_48C[player].tint *= scale) < 0.9f) {
        result = 1;
    }
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] *= scale;
        mat->color[1] *= scale;
        mat->color[2] *= scale;
    }
    return result;
}

/* 63 insns. Unreferenced: restore player's material colours. */
void fn_1_35B8(s16 player)
{
    s16 unused;
    HU3DMODEL *model;
    s8 *buf;
    HSFMATERIAL *mat;
    s16 i;

    unused = 0;
    lbl_1_bss_48C[player].tint = 255.0f;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_48C[player].matColor;
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] = *buf;
        buf++;
        mat->color[1] = *buf;
        buf++;
        mat->color[2] = *buf;
        buf++;
    }
}

/* 12 insns. */
void fn_1_36B4(void)
{
    lbl_1_bss_70C.jingleNo = HuAudJinglePlay(131);
}

/* 12 insns. */
void fn_1_36E4(void)
{
    lbl_1_bss_70C.bgmNo = HuAudBGMPlay(54);
}

/* 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_3714(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_70C.bgmNo;
    } else {
        no = lbl_1_bss_70C.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_377C(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_70C.bgmNo;
    } else {
        no = lbl_1_bss_70C.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* 30 insns. */
void fn_1_37DC(s16 no)
{
    lbl_1_bss_70C.seF[no] = 1;
    lbl_1_bss_70C.seNo[no] = HuAudFXPlay(lbl_1_data_330[no]);
}

/* 34 insns. */
void fn_1_3854(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_70C.seF[no] = 1;
    lbl_1_bss_70C.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_330[no], vol, pan);
}

/* 36 insns. */
void fn_1_38DC(s16 no, s16 pan)
{
    if(lbl_1_bss_70C.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_70C.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_70C.seNo[no], pan);
    }
}

/* 43 insns. Unreferenced; fn_1_3A18 is the same. */
void fn_1_396C(s16 no)
{
    if(lbl_1_bss_70C.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_70C.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_70C.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_70C.seNo[no]);
    }
}

/* 43 insns. Unreferenced. */
void fn_1_3A18(s16 no)
{
    if(lbl_1_bss_70C.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_70C.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_70C.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_70C.seNo[no]);
    }
}

/* 8 insns. */
void fn_1_3AC4(void)
{
    HuAudAllStop();
}
