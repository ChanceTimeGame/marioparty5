/*
 * m543dll -- a KETTOU duel (overlay #57): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, the dust particles, the duellists' material
 * fades and the sound helpers. Written from the reference assembly, functions
 * in reference order; line ranges are into
 * build/mp5-asm/m543Dll/asm/REL/m543Dll/m543.s.
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

#include "REL/m543Dll/m543.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M543_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

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
s32 fn_1_5A6C(M543_WORK *work);
s32 fn_1_5B78(void);
s32 fn_1_5BB0(void);
s32 fn_1_5C20(void);
s32 fn_1_623C(void);
s32 fn_1_6314(void);
s32 fn_1_634C(void);
s32 fn_1_64AC(void);
s32 fn_1_64DC(void);
void fn_1_44C(s16 no);
void fn_1_E94(void);
void fn_1_139C(void);
s16 fn_1_2F3C(float x, float y, float z, float scale, M543_PARTICLEPARAM *param);
void fn_1_3110(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

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

/* Seven motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][7] = {
    { 0x008C0000, 0x008C0002, 0x008C000F, 0x008C0017, 0x008C0018, 0x008C0006, 0x008C0031 },
    { 0x00330000, 0x00330002, 0x0033000F, 0x00330017, 0x00330018, 0x00330006, 0x00330031 },
    { 0x00B70000, 0x00B70002, 0x00B7000F, 0x00B70017, 0x00B70018, 0x00B70006, 0x00B70031 },
    { 0x00ED0000, 0x00ED0002, 0x00ED000F, 0x00ED0017, 0x00ED0018, 0x00ED0006, 0x00ED0031 },
    { 0x00E60000, 0x00E60002, 0x00E6000F, 0x00E60017, 0x00E60018, 0x00E60006, 0x00E60031 },
    { 0x00170000, 0x00170002, 0x0017000F, 0x00170017, 0x00170018, 0x00170006, 0x00170031 },
    { 0x00E00000, 0x00E00002, 0x00E0000F, 0x00E00017, 0x00E00018, 0x00E00006, 0x00E00031 },
    { 0x002D0000, 0x002D0002, 0x002D000F, 0x002D0017, 0x002D0018, 0x002D0006, 0x002D0031 },
    { 0x00C90000, 0x00C90002, 0x00C9000F, 0x00C90017, 0x00C90018, 0x00C90006, 0x00C90031 },
    { 0x00B00000, 0x00B00002, 0x00B0000F, 0x00B00017, 0x00B00018, 0x00B00006, 0x00B00031 },
    { 0x00B00000, 0x00B00002, 0x00B0000F, 0x00B00017, 0x00B00018, 0x00B00006, 0x00B00031 },
    { 0x00B00000, 0x00B00002, 0x00B0000F, 0x00B00017, 0x00B00018, 0x00B00006, 0x00B00031 },
    { 0x00B00000, 0x00B00002, 0x00B0000F, 0x00B00017, 0x00B00018, 0x00B00006, 0x00B00031 }
};

/* files/data/m543.bin: the stage models (passed to fn_1_FA94). */
unsigned int lbl_1_data_194[17] = {
    0x00650000, 0x00650001, 0x00650002, 0x00650003, 0x00650004, 0x00650005, 0x00650006, 0x00650007,
    0x00650008, 0x00650009, 0x0065000A, 0x0065000B, 0x0065000C, 0x0065000D, 0x0065000E, 0x0065000F,
    0x00000000
};

/* The four cameras fn_1_44C can create; only camera 0 is. */
M543_CAMERAINIT lbl_1_data_1D8[4] = {
    { { 500.0f, 208.0f, -5.0f }, { -45.0f, 0.0f, 0.0f }, 800.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, -5.0f }, { -89.0f, 0.0f, 0.0f }, 1605.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 20.0f }, { -35.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_2A8[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1B8C's and fn_1_1EE4's debug lines. */
char lbl_1_data_2C8[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_2F6[] = "OBJW %d";
char lbl_1_data_2FE[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_323[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* The dust puff fn_1_251C and fn_1_2898 edit and spawn. */
M543_PARTICLEPARAM lbl_1_data_340 = {
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

/* fn_1_39E4's sound effects. */
s16 lbl_1_data_378[4] = {
    0x819, 0x81A, 0x81B, 0x81C
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

HU3DMODELID lbl_1_bss_15DC;
M543_PARTICLEPARAM *lbl_1_bss_15D8;
OMOBJMAN *lbl_1_bss_15D4;
M543_WORK lbl_1_bss_12EC;
M543_MODEL lbl_1_bss_C24[M543_MODEL_MAX];
HU3DMOTID lbl_1_bss_C08[2][7];
M543_GAME lbl_1_bss_B94;
M543_DUELLIST lbl_1_bss_8DC[2];
M543_PANEL lbl_1_bss_33C[45];
M543_TILE lbl_1_bss_1C[40];
M543_CAMERA *lbl_1_bss_18;
M543_LIGHT *lbl_1_bss_14;
M543_SHADOW *lbl_1_bss_10;
M543_ACTORS lbl_1_bss_0;

/* asm 61-200, 136 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_15D4 = MgActorObjectSetup();
    fn_1_FA94(&lbl_1_bss_12EC, lbl_1_bss_C24, lbl_1_data_194);
    lbl_1_bss_18 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M543_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_18, 0, (sizeof(M543_CAMERA)*4)+8);
    lbl_1_bss_14 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M543_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_14, 0, sizeof(M543_LIGHT));
    lbl_1_bss_10 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M543_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_10, 0, sizeof(M543_SHADOW));
    fn_1_44C(0);
    fn_1_E94();
    fn_1_139C();
    fn_1_FCF4(0, lbl_1_data_28[lbl_1_bss_12EC.chr[0].charNo]);
    fn_1_FCF4(1, lbl_1_data_28[lbl_1_bss_12EC.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_FD14(i, lbl_1_bss_C08[i]);
    }
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_10304);
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_448);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 560);
    MgSeqModeDelaySet(7, 600);
    MgSeqModeDelaySet(9, 60);
}

/* asm 203-218, 13 insns. Init hook. */
void fn_1_2C0(s16 mode, s16 frameNo)
{
    if(fn_1_5A6C(&lbl_1_bss_12EC)) {
        MgSeqModeNext();
    }
}

/* asm 221-234, 11 insns. Fade-in hook. */
void fn_1_2F4(s16 mode, s16 frameNo)
{
    if(fn_1_5B78()) {
        MgSeqModeNext();
    }
}

/* asm 237-250, 11 insns. Start hook. */
void fn_1_320(s16 mode, s16 frameNo)
{
    if(fn_1_5BB0()) {
        MgSeqModeNext();
    }
}

/* asm 253-266, 11 insns. Main hook. */
void fn_1_34C(s16 mode, s16 frameNo)
{
    if(fn_1_5C20()) {
        MgSeqModeNext();
    }
}

/* asm 269-282, 11 insns. Finish hook. */
void fn_1_378(s16 mode, s16 frameNo)
{
    if(fn_1_623C()) {
        MgSeqModeNext();
    }
}

/* asm 285-298, 11 insns. Pre-winner hook. */
void fn_1_3A4(s16 mode, s16 frameNo)
{
    if(fn_1_6314()) {
        MgSeqModeNext();
    }
}

/* asm 301-314, 11 insns. Winner hook. */
void fn_1_3D0(s16 mode, s16 frameNo)
{
    if(fn_1_634C()) {
        MgSeqModeNext();
    }
}

/* asm 317-326, 8 insns. Fade-out hook. */
void fn_1_3FC(s16 mode, s16 frameNo)
{
    fn_1_64AC();
}

/* asm 329-342, 11 insns. Close hook. */
void fn_1_41C(s16 mode, s16 frameNo)
{
    if(fn_1_64DC()) {
        MgSeqModeNext();
    }
}

/* asm 345-347, 1 insn. An empty object. */
void fn_1_448(OMOBJ *obj)
{
}

/*
 * asm 350-659, 308 insns. Create camera `no` from lbl_1_data_1D8, then seed
 * the debug camera globals from camera 0's center and rotation and camera
 * `no`'s zoom (m544 fn_1_4F0).
 */
void fn_1_44C(s16 no)
{
    lbl_1_bss_18[no].no = no;
    lbl_1_bss_18[no].center.x = lbl_1_data_1D8[no].center.x;
    lbl_1_bss_18[no].center.y = lbl_1_data_1D8[no].center.y;
    lbl_1_bss_18[no].center.z = lbl_1_data_1D8[no].center.z;
    lbl_1_bss_18[no].rot.x = lbl_1_data_1D8[no].rot.x;
    lbl_1_bss_18[no].rot.y = lbl_1_data_1D8[no].rot.y;
    lbl_1_bss_18[no].rot.z = lbl_1_data_1D8[no].rot.z;
    lbl_1_bss_18[no].zoom = lbl_1_data_1D8[no].zoom;
    lbl_1_bss_18[no].aspect = lbl_1_data_1D8[no].aspect;
    lbl_1_bss_18[no].vpX = lbl_1_data_1D8[no].vpX;
    lbl_1_bss_18[no].vpY = lbl_1_data_1D8[no].vpY;
    lbl_1_bss_18[no].vpW = lbl_1_data_1D8[no].vpW;
    lbl_1_bss_18[no].vpH = lbl_1_data_1D8[no].vpH;
    lbl_1_bss_18[no].fov = lbl_1_data_1D8[no].fov;
    Hu3DCameraCreate(lbl_1_data_2A8[no]);
    Hu3DCameraViewportSet(lbl_1_data_2A8[no], lbl_1_bss_18[no].vpX, lbl_1_bss_18[no].vpY, lbl_1_bss_18[no].vpW, lbl_1_bss_18[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_2A8[no], lbl_1_bss_18[no].fov, 20.0f, 30000.0f, lbl_1_bss_18[no].aspect);
    fn_1_91C(no);
    Center.x = lbl_1_data_1D8[0].center.x;
    Center.y = lbl_1_data_1D8[0].center.y;
    Center.z = lbl_1_data_1D8[0].center.z;
    CRot.x = lbl_1_data_1D8[0].rot.x;
    CRot.y = lbl_1_data_1D8[0].rot.y;
    CRot.z = lbl_1_data_1D8[0].rot.z;
    CZoom = lbl_1_data_1D8[no].zoom;
}

/* asm 662-1013, 350 insns. Camera `no` from its center, rotation and zoom (m544 fn_1_9C0). */
void fn_1_91C(s16 no)
{
    lbl_1_bss_18[no].pos.x = lbl_1_bss_18[no].center.x+(lbl_1_bss_18[no].zoom*(cos((M_PI*lbl_1_bss_18[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_18[no].rot.y)/180.0)));
    lbl_1_bss_18[no].pos.y = lbl_1_bss_18[no].center.y+(lbl_1_bss_18[no].zoom*-sin((M_PI*lbl_1_bss_18[no].rot.x)/180.0));
    lbl_1_bss_18[no].pos.z = lbl_1_bss_18[no].center.z+(lbl_1_bss_18[no].zoom*(cos((M_PI*lbl_1_bss_18[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_18[no].rot.y)/180.0)));
    lbl_1_bss_18[no].up.x = sin((M_PI*lbl_1_bss_18[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_18[no].rot.y)/180.0);
    lbl_1_bss_18[no].up.y = cos((M_PI*lbl_1_bss_18[no].rot.x)/180.0);
    lbl_1_bss_18[no].up.z = sin((M_PI*lbl_1_bss_18[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_18[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_2A8[no], lbl_1_bss_18[no].pos.x, lbl_1_bss_18[no].pos.y, lbl_1_bss_18[no].pos.z,
        lbl_1_bss_18[no].up.x, lbl_1_bss_18[no].up.y, lbl_1_bss_18[no].up.z,
        lbl_1_bss_18[no].center.x, lbl_1_bss_18[no].center.y, lbl_1_bss_18[no].center.z);
}

/* asm 1016-1157, 140 insns. The global light (m544 fn_1_F38). */
void fn_1_E94(void)
{
    Hu3DLighInit();
    lbl_1_bss_14->pos.x = 0.0f;
    lbl_1_bss_14->pos.y = 0.0f;
    lbl_1_bss_14->pos.z = 0.0f;
    lbl_1_bss_14->target.x = 0.0f;
    lbl_1_bss_14->target.y = 0.0f;
    lbl_1_bss_14->target.z = 0.0f;
    lbl_1_bss_14->rot.x = -23.0f;
    lbl_1_bss_14->rot.y = 0.0f;
    lbl_1_bss_14->rot.z = 0.0f;
    lbl_1_bss_14->dist = 1000.0f;
    lbl_1_bss_14->color.r = 255;
    lbl_1_bss_14->color.g = 255;
    lbl_1_bss_14->color.b = 255;
    lbl_1_bss_14->color.a = 255;
    PSVECSubtract(&lbl_1_bss_14->target, &lbl_1_bss_14->pos, &lbl_1_bss_14->dir);
    lbl_1_bss_14->id = Hu3DGLightCreateV(&lbl_1_bss_14->pos, &lbl_1_bss_14->dir, &lbl_1_bss_14->color);
    fn_1_10C4();
    Hu3DGLightStaticSet(lbl_1_bss_14->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_14->id);
}

/* asm 1160-1343, 182 insns. Place the light from its target, rotation and distance (m544 fn_1_1168). */
void fn_1_10C4(void)
{
    lbl_1_bss_14->pos.x = lbl_1_bss_14->target.x+(lbl_1_bss_14->dist*(cos((M_PI*lbl_1_bss_14->rot.x)/180.0)*sin((M_PI*lbl_1_bss_14->rot.y)/180.0)));
    lbl_1_bss_14->pos.y = lbl_1_bss_14->target.y+(lbl_1_bss_14->dist*-sin((M_PI*lbl_1_bss_14->rot.x)/180.0));
    lbl_1_bss_14->pos.z = lbl_1_bss_14->target.z+(lbl_1_bss_14->dist*(cos((M_PI*lbl_1_bss_14->rot.x)/180.0)*cos((M_PI*lbl_1_bss_14->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_14->target, &lbl_1_bss_14->pos, &lbl_1_bss_14->dir);
    PSVECNormalize(&lbl_1_bss_14->dir, &lbl_1_bss_14->dir);
    Hu3DGLightPosSetV(lbl_1_bss_14->id, &lbl_1_bss_14->pos, &lbl_1_bss_14->dir);
    Hu3DGLightColorSet(lbl_1_bss_14->id, lbl_1_bss_14->color.r, lbl_1_bss_14->color.g, lbl_1_bss_14->color.b, lbl_1_bss_14->color.a);
}

/* asm 1346-1421, 74 insns. The shadow (m544 fn_1_1440 without the size). */
void fn_1_139C(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_10->rot.x = -90.0f;
    lbl_1_bss_10->rot.y = 0.0f;
    lbl_1_bss_10->rot.z = 0.0f;
    lbl_1_bss_10->target.x = 0.0f;
    lbl_1_bss_10->target.y = 0.0f;
    lbl_1_bss_10->target.z = 0.0f;
    lbl_1_bss_10->tpLvl = 0.5f;
    lbl_1_bss_10->dist = 3500.0f;
    fn_1_14C4();
}

/* asm 1424-1652, 227 insns. Place the shadow camera (m546 fn_1_1434, with the target's z). */
void fn_1_14C4(void)
{
    lbl_1_bss_10->pos.x = lbl_1_bss_10->target.x+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*sin((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    lbl_1_bss_10->pos.y = lbl_1_bss_10->target.y+(lbl_1_bss_10->dist*-sin((M_PI*lbl_1_bss_10->rot.x)/180.0));
    lbl_1_bss_10->pos.z = lbl_1_bss_10->target.z+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*cos((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    lbl_1_bss_10->up.x = sin((M_PI*lbl_1_bss_10->rot.x)/180.0)*sin((M_PI*lbl_1_bss_10->rot.y)/180.0);
    lbl_1_bss_10->up.y = cos((M_PI*lbl_1_bss_10->rot.x)/180.0);
    lbl_1_bss_10->up.z = sin((M_PI*lbl_1_bss_10->rot.x)/180.0)*cos((M_PI*lbl_1_bss_10->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_10->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_10->pos, &lbl_1_bss_10->up, &lbl_1_bss_10->target);
}

/* asm 1655-1734, 72 insns. Step *value toward end by (end-start)/div; the steps left, 0 once there (m546 fn_1_17BC). */
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
    step = M543_DIST(start, end);
    start = M543_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1737-1815, 71 insns. Unreferenced: fn_1_1850 without the final clamp to end. */
s16 fn_1_1970(float *value, float div, float start, float end)
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
    step = M543_DIST(start, end);
    start = M543_DIST(start, *value);
    if(step <= start) {
        count = 0;
    }
    return count;
}

/* asm 1818-1848, 29 insns. A timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1A8C(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1851-1863, 11 insns. */
void fn_1_1B00(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1866-1877, 10 insns. */
BOOL fn_1_1B2C(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1880-1895, 14 insns. */
void fn_1_1B54(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1898-2124, 213 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1B8C(M543_WORK *work, s16 padNo, s16 no)
{
    M543_MODEL *model;
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
    print8(25, 136, 1.5f, lbl_1_data_2C8, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_2F6, no);
    return result;
}

/* asm 2127-2129, 1 insn. */
void fn_1_1EE0(void)
{
}

/* asm 2132-2465, 302 insns. Unreferenced debug: move the camera globals with pad padNo (m544 fn_1_1E68 without the font colour). */
void fn_1_1EE4(s16 padNo)
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
    print8(25, 30, 1.5f, lbl_1_data_2FE, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_323, CRot.x, CRot.y, CRot.z);
}

/* asm 2468-2567, 96 insns. The dust particle model: 1000 puffs on layer 0. */
void fn_1_239C(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x650013, HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_15D8 = HuMemDirectMallocNum(HEAP_HEAP, 1000*sizeof(M543_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_15DC = Hu3DParticleCreate(anim, 1000);
    Hu3DParticleHookSet(lbl_1_bss_15DC, fn_1_3110);
    Hu3DParticleBlendModeSet(lbl_1_bss_15DC, 1);
    Hu3DModelLayerSet(lbl_1_bss_15DC, 0);
    Hu3DModelCameraSet(lbl_1_bss_15DC, 1);
    Hu3DModelAttrSet(lbl_1_bss_15DC, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_15DC, HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_15DC].hookData;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_15D8;
    particle->count = 0;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 2570-2796, 223 insns. Unreferenced: twelve dust puffs in a ring around pos (m544 fn_1_24AC). */
void fn_1_251C(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    for(i=0; i<12; i++) {
        size = 6.0f+frandmod(6);
        lbl_1_data_340.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_340.vel.y = 0.0f;
        lbl_1_data_340.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_340.alphaSpeed = alpha;
        puffPos.x = pos->x+(20.0*sin((M_PI*(30.0f*i))/180.0));
        puffPos.y = 10.0f+pos->y;
        puffPos.z = pos->z+(20.0*cos((M_PI*(30.0f*i))/180.0));
        lbl_1_data_340.accelY = 0.01f*frandmod(20);
        size = 20.0f+frandmod(20);
        fn_1_2F3C(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_340);
    }
}

/*
 * asm 2799-3231, 425 insns. A burst of 48 dust puffs along a wave at pos:
 * side 0 spreads along x, any other side along z.
 */
void fn_1_2898(HuVecF *pos, s16 side)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    if(side == 0) {
        for(i=0; i<48; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_340.vel.x = size*sin((M_PI*(7.5f*i))/180.0);
            lbl_1_data_340.vel.y = frandmod(2);
            lbl_1_data_340.vel.z = frandmod(10)-5.0f;
            alpha = -frandmod(6)-6.0f;
            lbl_1_data_340.alphaSpeed = alpha;
            puffPos.x = pos->x+(60.0*sin((M_PI*(7.5f*i))/180.0));
            puffPos.y = 5.0f+pos->y;
            puffPos.z = (pos->z+frandmod(40))-20.0f;
            lbl_1_data_340.accelY = 0.01f*frandmod(20);
            size = 10.0f+frandmod(15);
            fn_1_2F3C(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_340);
        }
    } else {
        for(i=0; i<48; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_340.vel.x = frandmod(10)-5.0f;
            lbl_1_data_340.vel.y = frandmod(2);
            lbl_1_data_340.vel.z = size*sin((M_PI*(7.5f*i))/180.0);
            alpha = -frandmod(6)-6.0f;
            lbl_1_data_340.alphaSpeed = alpha;
            puffPos.x = (pos->x+frandmod(40))-20.0f;
            puffPos.y = 5.0f+pos->y;
            puffPos.z = pos->z+(60.0*sin((M_PI*(7.5f*i))/180.0));
            lbl_1_data_340.accelY = 0.01f*frandmod(20);
            size = 10.0f+frandmod(15);
            fn_1_2F3C(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_340);
        }
    }
}

/* asm 3234-3359, 117 insns. Spawn one dust puff living 60 frames; the slot, or -1 when all are live (m544 fn_1_2EE4). */
s16 fn_1_2F3C(float x, float y, float z, float scale, M543_PARTICLEPARAM *param)
{
    HU3DMODEL *model;
    M543_PARTICLEPARAM *work;
    s16 result;
    s16 i;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    result = -1;
    model = &Hu3DData[lbl_1_bss_15DC];
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
        data->parManId = 60;
        particle->emitCnt = i;
        result = i;
    }
    return result;
}

/*
 * asm 3362-3648, 274 insns. The dust hook: move, fade and shrink every live
 * puff (m544 fn_1_30B8); parManId counts its life down. Retail counts the
 * live puffs and never reads the count.
 */
void fn_1_3110(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M543_PARTICLEPARAM *param;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 value;
    s16 liveNum;

    param = particle->work;
    liveNum = 0;
    data = particle->data;
    for(i=0, data->time=0; i<particle->maxCnt; i++, data++) {
        if(data->scale > 0.0f) {
            liveNum++;
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
            if(value < 10) {
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
            data->parManId--;
            if(data->parManId == 0) {
                data->scale = 0.0f;
            }
        }
    }
    DCStoreRangeNoSync(particle->data, particle->maxCnt*sizeof(HU3DPARTICLEDATA));
}

/* asm 3651-3716, 62 insns. Unreferenced: keep a copy of player's material colours. */
void fn_1_3558(s16 player)
{
    s16 unused;
    HSFMATERIAL *mat;
    s8 *buf;
    HU3DMODEL *model;
    s16 i;

    unused = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_8DC[player].matColor = HuMemDirectMallocNum(HEAP_HEAP, model->hsf->materialNum*3, HU_MEMNUM_OVL);
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        *buf++ = mat->color[0];
        *buf++ = mat->color[1];
        *buf++ = mat->color[2];
    }
}

/* asm 3719-3815, 92 insns. Unreferenced: scale player's material colours; 1 once the tint is under 0.9. */
s16 fn_1_3650(s16 player, float scale)
{
    s16 result;
    HU3DMODEL *model;
    HSFMATERIAL *mat;
    s16 i;

    result = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    if((lbl_1_bss_8DC[player].tint *= scale) < 0.9f) {
        result = 1;
    }
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] *= scale;
        mat->color[1] *= scale;
        mat->color[2] *= scale;
    }
    return result;
}

/* asm 3818-3884, 63 insns. Unreferenced: restore player's material colours from fn_1_3558's copy. */
void fn_1_37C0(s16 player)
{
    s16 unused;
    HU3DMODEL *model;
    s8 *buf;
    HSFMATERIAL *mat;
    s16 i;

    unused = 0;
    lbl_1_bss_8DC[player].tint = 255.0f;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_8DC[player].matColor;
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] = *buf;
        buf++;
        mat->color[1] = *buf;
        buf++;
        mat->color[2] = *buf;
        buf++;
    }
}

/* asm 3887-3900, 12 insns. */
void fn_1_38BC(void)
{
    lbl_1_bss_B94.jingleNo = HuAudJinglePlay(131);
}

/* asm 3903-3916, 12 insns. */
void fn_1_38EC(void)
{
    lbl_1_bss_B94.bgmNo = HuAudBGMPlay(86);
}

/* asm 3919-3948, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_391C(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_B94.bgmNo;
    } else {
        no = lbl_1_bss_B94.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 3951-3978, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_3984(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_B94.bgmNo;
    } else {
        no = lbl_1_bss_B94.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 3981-4012, 30 insns. */
void fn_1_39E4(s16 no)
{
    lbl_1_bss_B94.seF[no] = 1;
    lbl_1_bss_B94.seNo[no] = HuAudFXPlay(lbl_1_data_378[no]);
}

/* asm 4015-4050, 34 insns. */
void fn_1_3A5C(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_B94.seF[no] = 1;
    lbl_1_bss_B94.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_378[no], vol, pan);
}

/* asm 4053-4091, 36 insns. */
void fn_1_3AE4(s16 no, s16 pan)
{
    if(lbl_1_bss_B94.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_B94.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_B94.seNo[no], pan);
    }
}

/* asm 4094-4140, 43 insns. Unreferenced; fn_1_3C20 is the same. */
void fn_1_3B74(s16 no)
{
    if(lbl_1_bss_B94.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_B94.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_B94.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_B94.seNo[no]);
    }
}

/* asm 4143-4189, 43 insns. Unreferenced. */
void fn_1_3C20(s16 no)
{
    if(lbl_1_bss_B94.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_B94.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_B94.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_B94.seNo[no]);
    }
}

/* asm 4192-4201, 8 insns. */
void fn_1_3CCC(void)
{
    HuAudAllStop();
}
