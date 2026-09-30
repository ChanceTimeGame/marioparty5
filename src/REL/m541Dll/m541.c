/*
 * m541dll -- a KETTOU duel (overlay #55): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, the duellists' material fades and the sound
 * helpers. Written from the reference assembly, functions in reference order;
 * line ranges are into build/mp5-asm/m541Dll/asm/REL/m541Dll/m541.s. Adapted
 * from m551.c, which carries the same functions plus a particle and paper
 * system this overlay does not have.
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

#include "REL/m541Dll/m541.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M541_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))
#define M541_IDIST(a, b) ((((a)-(b)) > 0) ? ((a)-(b)) : ((a)-(-1*(b))))

void ObjectSetup(void);
void fn_1_2C0(s16 mode, s16 frameNo);
void fn_1_2F4(s16 mode, s16 frameNo);
void fn_1_320(s16 mode, s16 frameNo);
void fn_1_34C(s16 mode, s16 frameNo);
void fn_1_378(s16 mode, s16 frameNo);
void fn_1_3A4(s16 mode, s16 frameNo);
void fn_1_3D0(s16 mode, s16 frameNo);
void fn_1_3FC(s16 mode, s16 frameNo);
void fn_1_41C(s16 mode, s16 frameNo);
void fn_1_448(OMOBJ *obj);
/* game.c defines these returning s16; the hooks test the whole register, as retail's calls without a prototype did. */
s32 fn_1_5C98(M541_WORK *work);
s32 fn_1_5DA4(void);
s32 fn_1_5DD8(void);
s32 fn_1_5E48(void);
s32 fn_1_6728(void);
s32 fn_1_6BF0(void);
s32 fn_1_6C38(void);
s32 fn_1_6E20(void);
s32 fn_1_6E50(void);
void fn_1_44C(s16 no);
void fn_1_E94(void);
void fn_1_139C(void);
s16 fn_1_1A70(M541_WORK *work, s16 padNo, s16 no);
void fn_1_1DC4(void);
void fn_1_1DC8(s16 padNo);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_2C0,
    fn_1_2F4,
    fn_1_320,
    fn_1_34C,
    fn_1_378,
    fn_1_3A4,
    fn_1_3D0,
    fn_1_3FC,
    fn_1_41C
};

/* Eight motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][M541_MOTION_MAX] = {
    { 0x008C0000, 0x008C0002, 0x008C000A, 0x008C0017, 0x008C001A, 0x008C0024, 0x008C0006, 0x008C0007 },
    { 0x00330000, 0x00330002, 0x0033000A, 0x00330017, 0x0033001A, 0x00330024, 0x00330006, 0x00330007 },
    { 0x00B70000, 0x00B70002, 0x00B7000A, 0x00B70017, 0x00B7001A, 0x00B70024, 0x00B70006, 0x00B70007 },
    { 0x00ED0000, 0x00ED0002, 0x00ED000A, 0x00ED0017, 0x00ED001A, 0x00ED0024, 0x00ED0006, 0x00ED0007 },
    { 0x00E60000, 0x00E60002, 0x00E6000A, 0x00E60017, 0x00E6001A, 0x00E60024, 0x00E60006, 0x00E60007 },
    { 0x00170000, 0x00170002, 0x0017000A, 0x00170017, 0x0017001A, 0x00170024, 0x00170006, 0x00170007 },
    { 0x00E00000, 0x00E00002, 0x00E0000A, 0x00E00017, 0x00E0001A, 0x00E00024, 0x00E00006, 0x00E00007 },
    { 0x002D0000, 0x002D0002, 0x002D000A, 0x002D0017, 0x002D001A, 0x002D0024, 0x002D0006, 0x002D0007 },
    { 0x00C90000, 0x00C90002, 0x00C9000A, 0x00C90017, 0x00C9001A, 0x00C90024, 0x00C90006, 0x00C90007 },
    { 0x00B00000, 0x00B00002, 0x00B0000A, 0x00B00017, 0x00B0001A, 0x00B00024, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0000A, 0x00B00017, 0x00B0001A, 0x00B00024, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0000A, 0x00B00017, 0x00B0001A, 0x00B00024, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B0000A, 0x00B00017, 0x00B0001A, 0x00B00024, 0x00B00006, 0x00B00007 }
};

/* files/data/m541.bin: the stage models (passed to fn_1_19AB0). */
unsigned int lbl_1_data_1C8[12] = {
    DATANUM(DATA_m541, 0x00), DATANUM(DATA_m541, 0x01), DATANUM(DATA_m541, 0x02), DATANUM(DATA_m541, 0x03),
    DATANUM(DATA_m541, 0x04), DATANUM(DATA_m541, 0x05), DATANUM(DATA_m541, 0x06), DATANUM(DATA_m541, 0x07),
    DATANUM(DATA_m541, 0x08), DATANUM(DATA_m541, 0x09), DATANUM(DATA_m541, 0x0A), DATANUM(DATA_m541, 0x0B)
};

/* The four cameras fn_1_44C can create; only camera 0 is. */
M541_CAMERAINIT lbl_1_data_1F8[4] = {
    { { 0.0f, 208.0f, 75.0f }, { -48.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 75.0f }, { -48.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 20.0f }, { -35.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_2C8[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1A70's and fn_1_1DC8's debug lines. */
char lbl_1_data_2E8[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_316[] = "OBJW %d";
char lbl_1_data_31E[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_343[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* fn_1_270C's sound effects. */
s16 lbl_1_data_360[4] = {
    0x809, 0x80A, 0x80B, 0x808
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s32 lbl_1_bss_369C;                /* unreferenced; dtk sizes lbl_1_bss_3698 8 */
OMOBJMAN *lbl_1_bss_3698;
M541_WORK lbl_1_bss_33B0;
M541_MODEL lbl_1_bss_27E0[M541_MODEL_MAX];
HU3DMOTID lbl_1_bss_27C0[2][M541_MOTION_MAX];
M541_GAME lbl_1_bss_2734;
M541_DUELLIST lbl_1_bss_2614[2];
M541_BIG lbl_1_bss_45C;
M541_STAGE lbl_1_bss_2F0;
M541_MOVER lbl_1_bss_20[15];
M541_CAMERA *lbl_1_bss_1C;
M541_LIGHT *lbl_1_bss_18;
M541_SHADOW *lbl_1_bss_14;
M541_ACTORS lbl_1_bss_0;

/* asm 61-200, 136 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_3698 = MgActorObjectSetup();
    fn_1_19AB0(&lbl_1_bss_33B0, lbl_1_bss_27E0, lbl_1_data_1C8);
    lbl_1_bss_1C = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M541_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_1C, 0, (sizeof(M541_CAMERA)*4)+8);
    lbl_1_bss_18 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M541_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_18, 0, sizeof(M541_LIGHT));
    lbl_1_bss_14 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M541_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_14, 0, sizeof(M541_SHADOW));
    fn_1_44C(0);
    fn_1_E94();
    fn_1_139C();
    fn_1_19D10(0, lbl_1_data_28[lbl_1_bss_33B0.chr[0].charNo]);
    fn_1_19D10(1, lbl_1_data_28[lbl_1_bss_33B0.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_19D30(i, lbl_1_bss_27C0[i]);
    }
    omAddObjEx(lbl_1_bss_3698, 32730, 0, 0, -1, fn_1_1A320);
    omAddObjEx(lbl_1_bss_3698, 32730, 0, 0, -1, fn_1_448);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 470);
    MgSeqModeDelaySet(7, 180);
    MgSeqModeDelaySet(9, 60);
}

/* asm 203-218, 13 insns. Init hook. */
void fn_1_2C0(s16 mode, s16 frameNo)
{
    if(fn_1_5C98(&lbl_1_bss_33B0)) {
        MgSeqModeNext();
    }
}

/* asm 221-234, 11 insns. Fade-in hook. */
void fn_1_2F4(s16 mode, s16 frameNo)
{
    if(fn_1_5DA4()) {
        MgSeqModeNext();
    }
}

/* asm 237-250, 11 insns. Start hook. */
void fn_1_320(s16 mode, s16 frameNo)
{
    if(fn_1_5DD8()) {
        MgSeqModeNext();
    }
}

/* asm 253-266, 11 insns. Main hook. */
void fn_1_34C(s16 mode, s16 frameNo)
{
    if(fn_1_5E48()) {
        MgSeqModeNext();
    }
}

/* asm 269-282, 11 insns. Finish hook. */
void fn_1_378(s16 mode, s16 frameNo)
{
    if(fn_1_6728()) {
        MgSeqModeNext();
    }
}

/* asm 285-298, 11 insns. Pre-winner hook. */
void fn_1_3A4(s16 mode, s16 frameNo)
{
    if(fn_1_6BF0()) {
        MgSeqModeNext();
    }
}

/* asm 301-314, 11 insns. Winner hook. */
void fn_1_3D0(s16 mode, s16 frameNo)
{
    if(fn_1_6C38()) {
        MgSeqModeNext();
    }
}

/* asm 317-326, 8 insns. Fade-out hook. */
void fn_1_3FC(s16 mode, s16 frameNo)
{
    fn_1_6E20();
}

/* asm 329-342, 11 insns. Close hook. */
void fn_1_41C(s16 mode, s16 frameNo)
{
    if(fn_1_6E50()) {
        MgSeqModeNext();
    }
}

/* asm 345-347, 1 insn. An empty object. */
void fn_1_448(OMOBJ *obj)
{
}

/*
 * asm 350-659, 308 insns. Create camera `no` from lbl_1_data_1F8, then seed
 * the debug camera globals from camera 0's center and rotation and camera
 * `no`'s zoom (m543 fn_1_44C).
 */
void fn_1_44C(s16 no)
{
    lbl_1_bss_1C[no].no = no;
    lbl_1_bss_1C[no].center.x = lbl_1_data_1F8[no].center.x;
    lbl_1_bss_1C[no].center.y = lbl_1_data_1F8[no].center.y;
    lbl_1_bss_1C[no].center.z = lbl_1_data_1F8[no].center.z;
    lbl_1_bss_1C[no].rot.x = lbl_1_data_1F8[no].rot.x;
    lbl_1_bss_1C[no].rot.y = lbl_1_data_1F8[no].rot.y;
    lbl_1_bss_1C[no].rot.z = lbl_1_data_1F8[no].rot.z;
    lbl_1_bss_1C[no].zoom = lbl_1_data_1F8[no].zoom;
    lbl_1_bss_1C[no].aspect = lbl_1_data_1F8[no].aspect;
    lbl_1_bss_1C[no].vpX = lbl_1_data_1F8[no].vpX;
    lbl_1_bss_1C[no].vpY = lbl_1_data_1F8[no].vpY;
    lbl_1_bss_1C[no].vpW = lbl_1_data_1F8[no].vpW;
    lbl_1_bss_1C[no].vpH = lbl_1_data_1F8[no].vpH;
    lbl_1_bss_1C[no].fov = lbl_1_data_1F8[no].fov;
    Hu3DCameraCreate(lbl_1_data_2C8[no]);
    Hu3DCameraViewportSet(lbl_1_data_2C8[no], lbl_1_bss_1C[no].vpX, lbl_1_bss_1C[no].vpY, lbl_1_bss_1C[no].vpW, lbl_1_bss_1C[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_2C8[no], lbl_1_bss_1C[no].fov, 20.0f, 30000.0f, lbl_1_bss_1C[no].aspect);
    fn_1_91C(no);
    Center.x = lbl_1_data_1F8[0].center.x;
    Center.y = lbl_1_data_1F8[0].center.y;
    Center.z = lbl_1_data_1F8[0].center.z;
    CRot.x = lbl_1_data_1F8[0].rot.x;
    CRot.y = lbl_1_data_1F8[0].rot.y;
    CRot.z = lbl_1_data_1F8[0].rot.z;
    CZoom = lbl_1_data_1F8[no].zoom;
}

/* asm 662-1013, 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_91C(s16 no)
{
    lbl_1_bss_1C[no].pos.x = lbl_1_bss_1C[no].center.x+(lbl_1_bss_1C[no].zoom*(cos((M_PI*lbl_1_bss_1C[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_1C[no].rot.y)/180.0)));
    lbl_1_bss_1C[no].pos.y = lbl_1_bss_1C[no].center.y+(lbl_1_bss_1C[no].zoom*-sin((M_PI*lbl_1_bss_1C[no].rot.x)/180.0));
    lbl_1_bss_1C[no].pos.z = lbl_1_bss_1C[no].center.z+(lbl_1_bss_1C[no].zoom*(cos((M_PI*lbl_1_bss_1C[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_1C[no].rot.y)/180.0)));
    lbl_1_bss_1C[no].up.x = sin((M_PI*lbl_1_bss_1C[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_1C[no].rot.y)/180.0);
    lbl_1_bss_1C[no].up.y = cos((M_PI*lbl_1_bss_1C[no].rot.x)/180.0);
    lbl_1_bss_1C[no].up.z = sin((M_PI*lbl_1_bss_1C[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_1C[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_2C8[no], lbl_1_bss_1C[no].pos.x, lbl_1_bss_1C[no].pos.y, lbl_1_bss_1C[no].pos.z,
        lbl_1_bss_1C[no].up.x, lbl_1_bss_1C[no].up.y, lbl_1_bss_1C[no].up.z,
        lbl_1_bss_1C[no].center.x, lbl_1_bss_1C[no].center.y, lbl_1_bss_1C[no].center.z);
}

/* asm 1016-1157, 140 insns. The global light (m543 fn_1_E94). */
void fn_1_E94(void)
{
    Hu3DLighInit();
    lbl_1_bss_18->pos.x = 0.0f;
    lbl_1_bss_18->pos.y = 0.0f;
    lbl_1_bss_18->pos.z = 0.0f;
    lbl_1_bss_18->target.x = 0.0f;
    lbl_1_bss_18->target.y = 0.0f;
    lbl_1_bss_18->target.z = 0.0f;
    lbl_1_bss_18->rot.x = -23.0f;
    lbl_1_bss_18->rot.y = 0.0f;
    lbl_1_bss_18->rot.z = 0.0f;
    lbl_1_bss_18->dist = 1000.0f;
    lbl_1_bss_18->color.r = 255;
    lbl_1_bss_18->color.g = 255;
    lbl_1_bss_18->color.b = 255;
    lbl_1_bss_18->color.a = 255;
    PSVECSubtract(&lbl_1_bss_18->target, &lbl_1_bss_18->pos, &lbl_1_bss_18->dir);
    lbl_1_bss_18->id = Hu3DGLightCreateV(&lbl_1_bss_18->pos, &lbl_1_bss_18->dir, &lbl_1_bss_18->color);
    fn_1_10C4();
    Hu3DGLightStaticSet(lbl_1_bss_18->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_18->id);
}

/* asm 1160-1343, 182 insns. Place the light from its target, rotation and distance. */
void fn_1_10C4(void)
{
    lbl_1_bss_18->pos.x = lbl_1_bss_18->target.x+(lbl_1_bss_18->dist*(cos((M_PI*lbl_1_bss_18->rot.x)/180.0)*sin((M_PI*lbl_1_bss_18->rot.y)/180.0)));
    lbl_1_bss_18->pos.y = lbl_1_bss_18->target.y+(lbl_1_bss_18->dist*-sin((M_PI*lbl_1_bss_18->rot.x)/180.0));
    lbl_1_bss_18->pos.z = lbl_1_bss_18->target.z+(lbl_1_bss_18->dist*(cos((M_PI*lbl_1_bss_18->rot.x)/180.0)*cos((M_PI*lbl_1_bss_18->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_18->target, &lbl_1_bss_18->pos, &lbl_1_bss_18->dir);
    PSVECNormalize(&lbl_1_bss_18->dir, &lbl_1_bss_18->dir);
    Hu3DGLightPosSetV(lbl_1_bss_18->id, &lbl_1_bss_18->pos, &lbl_1_bss_18->dir);
    Hu3DGLightColorSet(lbl_1_bss_18->id, lbl_1_bss_18->color.r, lbl_1_bss_18->color.g, lbl_1_bss_18->color.b, lbl_1_bss_18->color.a);
}

/* asm 1346-1421, 74 insns. The shadow (m543 fn_1_139C at 3600, not 3500). */
void fn_1_139C(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_14->rot.x = -90.0f;
    lbl_1_bss_14->rot.y = 0.0f;
    lbl_1_bss_14->rot.z = 0.0f;
    lbl_1_bss_14->target.x = 0.0f;
    lbl_1_bss_14->target.y = 0.0f;
    lbl_1_bss_14->target.z = 0.0f;
    lbl_1_bss_14->tpLvl = 0.5f;
    lbl_1_bss_14->dist = 2600.0f;
    fn_1_14C4();
}

/* asm 1424-1652, 227 insns. Place the shadow camera. */
void fn_1_14C4(void)
{
    lbl_1_bss_14->pos.x = lbl_1_bss_14->target.x+(lbl_1_bss_14->dist*(cos((M_PI*lbl_1_bss_14->rot.x)/180.0)*sin((M_PI*lbl_1_bss_14->rot.y)/180.0)));
    lbl_1_bss_14->pos.y = lbl_1_bss_14->target.y+(lbl_1_bss_14->dist*-sin((M_PI*lbl_1_bss_14->rot.x)/180.0));
    lbl_1_bss_14->pos.z = lbl_1_bss_14->target.z+(lbl_1_bss_14->dist*(cos((M_PI*lbl_1_bss_14->rot.x)/180.0)*cos((M_PI*lbl_1_bss_14->rot.y)/180.0)));
    lbl_1_bss_14->up.x = sin((M_PI*lbl_1_bss_14->rot.x)/180.0)*sin((M_PI*lbl_1_bss_14->rot.y)/180.0);
    lbl_1_bss_14->up.y = cos((M_PI*lbl_1_bss_14->rot.x)/180.0);
    lbl_1_bss_14->up.z = sin((M_PI*lbl_1_bss_14->rot.x)/180.0)*cos((M_PI*lbl_1_bss_14->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_14->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_14->pos, &lbl_1_bss_14->up, &lbl_1_bss_14->target);
}

/* asm 1655-1734, 72 insns. Step *value toward end by (end-start)/div; the steps left, 0 once there. */
s16 fn_1_1850(float *value, float div, float start, float end)
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
    step = M541_DIST(start, end);
    start = M541_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1800-1830, 29 insns. A timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1970(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1833-1845, 11 insns. */
void fn_1_19E4(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1848-1859, 10 insns. */
BOOL fn_1_1A10(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1862-1877, 14 insns. */
void fn_1_1A38(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1880-2106, 213 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1A70(M541_WORK *work, s16 padNo, s16 no)
{
    M541_MODEL *model;
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
    print8(25, 136, 1.5f, lbl_1_data_2E8, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_316, no);
    return result;
}

/* asm 2109-2111, 1 insn. */
void fn_1_1DC4(void)
{
}

/* asm 2114-2447, 302 insns. Unreferenced debug: move the camera globals with pad padNo. */
void fn_1_1DC8(s16 padNo)
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
    print8(25, 30, 1.5f, lbl_1_data_31E, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_343, CRot.x, CRot.y, CRot.z);
}

/* asm 5955-6020, 62 insns. Unreferenced: keep a copy of player's material colours. */
void fn_1_2280(s16 player)
{
    s16 unused;
    s8 *buf;
    HSFMATERIAL *mat;
    HU3DMODEL *model;
    s16 i;

    unused = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_2614[player].matColor = HuMemDirectMallocNum(HEAP_HEAP, model->hsf->materialNum*3, HU_MEMNUM_OVL);
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        *buf++ = mat->color[0];
        *buf++ = mat->color[1];
        *buf++ = mat->color[2];
    }
}

/* Unreferenced: scale player's material colours; 1 once the tint is under 40. */
s16 fn_1_2378(s16 player, float scale)
{
    s16 result;
    HU3DMODEL *model;
    HSFMATERIAL *mat;
    s16 i;

    result = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    if((lbl_1_bss_2614[player].tint *= scale) < 40.0f) {
        result = 1;
    }
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] *= scale;
        mat->color[1] *= scale;
        mat->color[2] *= scale;
    }
    return result;
}

/* asm 6122-6188, 63 insns. Unreferenced: restore player's material colours from fn_1_2280's copy. */
void fn_1_24E8(s16 player)
{
    s16 unused;
    HU3DMODEL *model;
    s8 *buf;
    HSFMATERIAL *mat;
    s16 i;

    unused = 0;
    lbl_1_bss_2614[player].tint = 255.0f;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_2614[player].matColor;
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] = *buf;
        buf++;
        mat->color[1] = *buf;
        buf++;
        mat->color[2] = *buf;
        buf++;
    }
}

/* asm 6191-6204, 12 insns. */
void fn_1_25E4(void)
{
    lbl_1_bss_2734.jingleNo = HuAudJinglePlay(131);
}

/* asm 6207-6220, 12 insns. */
void fn_1_2614(void)
{
    lbl_1_bss_2734.bgmNo = HuAudBGMPlay(86);
}

/* asm 6223-6252, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_2644(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_2734.bgmNo;
    } else {
        no = lbl_1_bss_2734.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 6255-6282, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_26AC(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_2734.bgmNo;
    } else {
        no = lbl_1_bss_2734.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 6285-6316, 30 insns. */
void fn_1_270C(s16 no)
{
    if((no != 0 && no != 1 && no != 2) || lbl_1_bss_2734.seF[no] == -1) {
        lbl_1_bss_2734.seF[no] = 1;
        lbl_1_bss_2734.seNo[no] = HuAudFXPlay(lbl_1_data_360[no]);
    }
}

/* asm 6319-6354, 34 insns. */
void fn_1_27C8(s16 no, s16 vol, s16 pan)
{
    if((no != 0 && no != 1 && no != 2) || lbl_1_bss_2734.seF[no] == -1) {
        lbl_1_bss_2734.seF[no] = 1;
        lbl_1_bss_2734.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_360[no], vol, pan);
    }
}

/* asm 6357-6395, 36 insns. */
void fn_1_2894(s16 no, s16 pan)
{
    if(lbl_1_bss_2734.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_2734.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_2734.seNo[no], pan);
    }
}

/* asm 6398-6444, 43 insns. Unreferenced; fn_1_29EC is the same. */
void fn_1_2924(s16 no)
{
    if(lbl_1_bss_2734.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_2734.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_2734.seNo[no]) == 3)) {
        lbl_1_bss_2734.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_2734.seNo[no]);
    }
}

/* asm 6447-6493, 43 insns. Unreferenced. */
void fn_1_29EC(s16 no)
{
    if(lbl_1_bss_2734.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_2734.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_2734.seNo[no]) == 3)) {
        lbl_1_bss_2734.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_2734.seNo[no]);
    }
}

/* asm 6496-6505, 8 insns. */
void fn_1_2AB4(void)
{
    HuAudAllStop();
}
