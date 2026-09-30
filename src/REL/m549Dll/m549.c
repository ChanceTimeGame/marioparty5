/*
 * m549dll -- a KETTOU duel (overlay #63): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, the dust particles and the sound helpers.
 * Written from the reference assembly, functions in reference order; line
 * ranges are into build/mp5-asm/m549Dll/asm/REL/m549Dll/m549.s.
 *
 * _prolog and _epilog are not reproduced.
 *
 * This unit is adaptation rather than fresh decompilation: every one of its 43
 * functions has an xmatch twin at >=0.80 and 38 at >=0.90, mostly against
 * m555.o, whose own donors are m543's and m553's m5NN.c. The shape transfers
 * and the constants do not -- m553's copied BGM number was caught only by the
 * diff (build/mp5-duelstage/20260915-m549-w0/m549c-twins.md).
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

#include "REL/m549Dll/m549.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M549_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))

void ObjectSetup(void);
void fn_1_320(s16 mode, s16 frameNo);
void fn_1_354(s16 mode, s16 frameNo);
void fn_1_380(s16 mode, s16 frameNo);
void fn_1_3AC(s16 mode, s16 frameNo);
void fn_1_3D8(s16 mode, s16 frameNo);
void fn_1_404(s16 mode, s16 frameNo);
void fn_1_430(s16 mode, s16 frameNo);
void fn_1_45C(s16 mode, s16 frameNo);
void fn_1_47C(s16 mode, s16 frameNo);
void fn_1_4A8(OMOBJ *obj);
/* game.c defines these returning s16; the hooks test the whole register, as retail's calls without a prototype did. */
s32 fn_1_4EE0(M549_WORK *work);
s32 fn_1_4FFC(void);
s32 fn_1_50A4(void);
s32 fn_1_5184(void);
s32 fn_1_569C(void);
s32 fn_1_5788(void);
s32 fn_1_57D8(void);
s32 fn_1_5A00(void);
s32 fn_1_5A40(void);
s16 fn_1_2F70(float x, float y, float z, float scale, M549_PARTICLEPARAM *param);
void fn_1_3144(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_320,
    fn_1_354,
    fn_1_380,
    fn_1_3AC,
    fn_1_3D8,
    fn_1_404,
    fn_1_430,
    fn_1_45C,
    fn_1_47C
};

/* Ten motions per character, in charNo order; DS_CHARMOTION_NUM is 10. */
unsigned int lbl_1_data_28[13][10] = {
    { 0x008C0000, 0x008C0002, 0x008C002B, 0x008C0006, 0x008C002E, 0x008700A7, 0x008700AA, 0x008C007C, 0x008C0081, 0x008700B8 },
    { 0x00330000, 0x00330002, 0x0033002B, 0x00330006, 0x0033002E, 0x002E00A7, 0x002E00AA, 0x0033007C, 0x00330081, 0x002E00B8 },
    { 0x00B70000, 0x00B70002, 0x00B7002B, 0x00B70006, 0x00B7002E, 0x00B200A7, 0x00B200AA, 0x00B7007C, 0x00B70081, 0x00B200B8 },
    { 0x00ED0000, 0x00ED0002, 0x00ED002B, 0x00ED0006, 0x00ED002E, 0x00E800A7, 0x00E800AA, 0x00ED007C, 0x00ED0081, 0x00E800B8 },
    { 0x00E60000, 0x00E60002, 0x00E6002B, 0x00E60006, 0x00E6002E, 0x00E100A7, 0x00E100AA, 0x00E6007C, 0x00E60081, 0x00E100B8 },
    { 0x00170000, 0x00170002, 0x0017002B, 0x00170006, 0x0017002E, 0x001200A7, 0x001200AA, 0x0017007C, 0x00170081, 0x001200B8 },
    { 0x00E00000, 0x00E00002, 0x00E0002B, 0x00E00006, 0x00E0002E, 0x00DB00A7, 0x00DB00AA, 0x00E0007C, 0x00E00081, 0x00DB00B8 },
    { 0x002D0000, 0x002D0002, 0x002D002B, 0x002D0006, 0x002D002E, 0x002800A7, 0x002800AA, 0x002D007C, 0x002D0081, 0x002800B8 },
    { 0x00C90000, 0x00C90002, 0x00C9002B, 0x00C90006, 0x00C9002E, 0x00C400A7, 0x00C400AA, 0x00C9007C, 0x00C90081, 0x00C400B8 },
    { 0x00B00000, 0x00B00002, 0x00B0002B, 0x00B00006, 0x00B0002E, 0x009C00A7, 0x009C00AA, 0x00B0007C, 0x00B00081, 0x009C00B8 },
    { 0x00B00000, 0x00B00002, 0x00B0002B, 0x00B00006, 0x00B0002E, 0x009C00A7, 0x009C00AA, 0x00B0007C, 0x00B00081, 0x009C00B8 },
    { 0x00B00000, 0x00B00002, 0x00B0002B, 0x00B00006, 0x00B0002E, 0x009C00A7, 0x009C00AA, 0x00B0007C, 0x00B00081, 0x009C00B8 },
    { 0x00B00000, 0x00B00002, 0x00B0002B, 0x00B00006, 0x00B0002E, 0x009C00A7, 0x009C00AA, 0x00B0007C, 0x00B00081, 0x009C00B8 }
};

/* files/data/m549.bin: the stage models (passed to fn_1_11BC0). 0x08 is the
 * dust sprite fn_1_23FC reads and is deliberately not in this table. */
unsigned int lbl_1_data_230[22] = {
    0x006B0000, 0x006B0001, 0x006B0002, 0x006B0003, 0x006B0004, 0x006B0005, 0x006B0006, 0x006B0007,
    0x006B0009, 0x006B000A, 0x006B000B, 0x006B000C, 0x006B000D, 0x006B000E, 0x006B000F, 0x006B0010,
    0x006B0011, 0x006B0012, 0x006B0013, 0x006B0014, 0x006B0015, 0x006B0018
};

/* The four cameras fn_1_4AC can create; 0 and 1 are. */
M549_CAMERAINIT lbl_1_data_288[4] = {
    { { 0.0f, 131.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, 300.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 131.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, 300.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 131.0f, 0.0f }, { -26.0f, 0.0f, 0.0f }, 1602.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_358[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1BEC's and fn_1_1F44's debug lines. */
char lbl_1_data_378[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_3A6[] = "OBJW %d";
char lbl_1_data_3AE[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_3D3[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* The dust puff fn_1_2550 and fn_1_28CC edit and spawn. */
M549_PARTICLEPARAM lbl_1_data_3F0 = {
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

/* fn_1_36A4's sound effects. */
s16 lbl_1_data_428[12] = {
    0x845, 0x845, 0x846, 0x847, 0x848, 0x849, 0x84A, 0x84B,
    0x84C, 0x84D, 0x84E, 0
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

HU3DMODELID lbl_1_bss_15DC;
M549_PARTICLEPARAM *lbl_1_bss_15D8;
OMOBJMAN *lbl_1_bss_15D4;
M549_WORK lbl_1_bss_DD0;
M549_MODEL lbl_1_bss_628[M549_MODEL_MAX];
HU3DMOTID lbl_1_bss_600[2][10];
M549_GAME lbl_1_bss_580;
M549_DUELLIST lbl_1_bss_3B0[2];
M549_OBJ lbl_1_bss_158[10];
M549_STAGEOBJ lbl_1_bss_18[10];
M549_CAMERA *lbl_1_bss_14;
M549_LIGHT *lbl_1_bss_10;
M549_SHADOW *lbl_1_bss_C;
M549_ACTORS lbl_1_bss_0;

/* asm 61-224, 160 insns. Two cameras and four objects, where m553 has one and three. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_15D4 = MgActorObjectSetup();
    fn_1_11BC0(&lbl_1_bss_DD0, lbl_1_bss_628, lbl_1_data_230);
    lbl_1_bss_14 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M549_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_14, 0, (sizeof(M549_CAMERA)*4)+8);
    lbl_1_bss_10 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M549_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_10, 0, sizeof(M549_LIGHT));
    lbl_1_bss_C = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M549_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_C, 0, sizeof(M549_SHADOW));
    fn_1_4AC(0);
    fn_1_4AC(1);
    fn_1_EF4();
    fn_1_13FC();
    fn_1_11E0C(1);
    fn_1_12450(0, lbl_1_data_28[lbl_1_bss_DD0.chr[0].charNo]);
    fn_1_12450(1, lbl_1_data_28[lbl_1_bss_DD0.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_12470(i, lbl_1_bss_600[i]);
    }
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_12494);
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_12A60);
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_4A8);
    omAddObjEx(lbl_1_bss_15D4, 32730, 0, 0, -1, fn_1_12E80);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 6000);
    MgSeqModeDelaySet(7, 6000);
    MgSeqModeDelaySet(9, 60);
}

/* asm 227-242, 13 insns. Init hook. */
void fn_1_320(s16 mode, s16 frameNo)
{
    if(fn_1_4EE0(&lbl_1_bss_DD0)) {
        MgSeqModeNext();
    }
}

/* asm 245-258, 11 insns. Fade-in hook. */
void fn_1_354(s16 mode, s16 frameNo)
{
    if(fn_1_4FFC()) {
        MgSeqModeNext();
    }
}

/* asm 261-274, 11 insns. Start hook. */
void fn_1_380(s16 mode, s16 frameNo)
{
    if(fn_1_50A4()) {
        MgSeqModeNext();
    }
}

/* asm 277-290, 11 insns. Main hook. */
void fn_1_3AC(s16 mode, s16 frameNo)
{
    if(fn_1_5184()) {
        MgSeqModeNext();
    }
}

/* asm 293-306, 11 insns. Finish hook. */
void fn_1_3D8(s16 mode, s16 frameNo)
{
    if(fn_1_569C()) {
        MgSeqModeNext();
    }
}

/* asm 309-322, 11 insns. Pre-winner hook. */
void fn_1_404(s16 mode, s16 frameNo)
{
    if(fn_1_5788()) {
        MgSeqModeNext();
    }
}

/* asm 325-338, 11 insns. Winner hook. */
void fn_1_430(s16 mode, s16 frameNo)
{
    if(fn_1_57D8()) {
        MgSeqModeNext();
    }
}

/* asm 341-350, 8 insns. Fade-out hook. */
void fn_1_45C(s16 mode, s16 frameNo)
{
    fn_1_5A00();
}

/* asm 353-366, 11 insns. Close hook. */
void fn_1_47C(s16 mode, s16 frameNo)
{
    if(fn_1_5A40()) {
        MgSeqModeNext();
    }
}

/* asm 369-371, 1 insn. An empty object. */
void fn_1_4A8(OMOBJ *obj)
{
}

/*
 * asm 374-683, 308 insns. Create camera `no` from lbl_1_data_288, then seed the
 * debug camera globals from camera 0's center and rotation and camera `no`'s zoom.
 */
void fn_1_4AC(s16 no)
{
    lbl_1_bss_14[no].no = no;
    lbl_1_bss_14[no].center.x = lbl_1_data_288[no].center.x;
    lbl_1_bss_14[no].center.y = lbl_1_data_288[no].center.y;
    lbl_1_bss_14[no].center.z = lbl_1_data_288[no].center.z;
    lbl_1_bss_14[no].rot.x = lbl_1_data_288[no].rot.x;
    lbl_1_bss_14[no].rot.y = lbl_1_data_288[no].rot.y;
    lbl_1_bss_14[no].rot.z = lbl_1_data_288[no].rot.z;
    lbl_1_bss_14[no].zoom = lbl_1_data_288[no].zoom;
    lbl_1_bss_14[no].aspect = lbl_1_data_288[no].aspect;
    lbl_1_bss_14[no].vpX = lbl_1_data_288[no].vpX;
    lbl_1_bss_14[no].vpY = lbl_1_data_288[no].vpY;
    lbl_1_bss_14[no].vpW = lbl_1_data_288[no].vpW;
    lbl_1_bss_14[no].vpH = lbl_1_data_288[no].vpH;
    lbl_1_bss_14[no].fov = lbl_1_data_288[no].fov;
    Hu3DCameraCreate(lbl_1_data_358[no]);
    Hu3DCameraViewportSet(lbl_1_data_358[no], lbl_1_bss_14[no].vpX, lbl_1_bss_14[no].vpY, lbl_1_bss_14[no].vpW, lbl_1_bss_14[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_358[no], lbl_1_bss_14[no].fov, 20.0f, 40000.0f, lbl_1_bss_14[no].aspect);
    fn_1_97C(no);
    Center.x = lbl_1_data_288[0].center.x;
    Center.y = lbl_1_data_288[0].center.y;
    Center.z = lbl_1_data_288[0].center.z;
    CRot.x = lbl_1_data_288[0].rot.x;
    CRot.y = lbl_1_data_288[0].rot.y;
    CRot.z = lbl_1_data_288[0].rot.z;
    CZoom = lbl_1_data_288[no].zoom;
}

/* asm 686-1037, 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_97C(s16 no)
{
    lbl_1_bss_14[no].pos.x = lbl_1_bss_14[no].center.x+(lbl_1_bss_14[no].zoom*(cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_14[no].rot.y)/180.0)));
    lbl_1_bss_14[no].pos.y = lbl_1_bss_14[no].center.y+(lbl_1_bss_14[no].zoom*-sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0));
    lbl_1_bss_14[no].pos.z = lbl_1_bss_14[no].center.z+(lbl_1_bss_14[no].zoom*(cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_14[no].rot.y)/180.0)));
    lbl_1_bss_14[no].up.x = sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_14[no].rot.y)/180.0);
    lbl_1_bss_14[no].up.y = cos((M_PI*lbl_1_bss_14[no].rot.x)/180.0);
    lbl_1_bss_14[no].up.z = sin((M_PI*lbl_1_bss_14[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_14[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_358[no], lbl_1_bss_14[no].pos.x, lbl_1_bss_14[no].pos.y, lbl_1_bss_14[no].pos.z,
        lbl_1_bss_14[no].up.x, lbl_1_bss_14[no].up.y, lbl_1_bss_14[no].up.z,
        lbl_1_bss_14[no].center.x, lbl_1_bss_14[no].center.y, lbl_1_bss_14[no].center.z);
}

/* asm 1040-1181, 140 insns. The global light. */
void fn_1_EF4(void)
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
    fn_1_1124();
    Hu3DGLightStaticSet(lbl_1_bss_10->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_10->id);
}

/* asm 1184-1367, 182 insns. Place the light from its target, rotation and distance. */
void fn_1_1124(void)
{
    lbl_1_bss_10->pos.x = lbl_1_bss_10->target.x+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*sin((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    lbl_1_bss_10->pos.y = lbl_1_bss_10->target.y+(lbl_1_bss_10->dist*-sin((M_PI*lbl_1_bss_10->rot.x)/180.0));
    lbl_1_bss_10->pos.z = lbl_1_bss_10->target.z+(lbl_1_bss_10->dist*(cos((M_PI*lbl_1_bss_10->rot.x)/180.0)*cos((M_PI*lbl_1_bss_10->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_10->target, &lbl_1_bss_10->pos, &lbl_1_bss_10->dir);
    PSVECNormalize(&lbl_1_bss_10->dir, &lbl_1_bss_10->dir);
    Hu3DGLightPosSetV(lbl_1_bss_10->id, &lbl_1_bss_10->pos, &lbl_1_bss_10->dir);
    Hu3DGLightColorSet(lbl_1_bss_10->id, lbl_1_bss_10->color.r, lbl_1_bss_10->color.g, lbl_1_bss_10->color.b, lbl_1_bss_10->color.a);
}

/* asm 1370-1445, 74 insns. The shadow. */
void fn_1_13FC(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 40000.0f);
    lbl_1_bss_C->rot.x = -60.0f;
    lbl_1_bss_C->rot.y = 0.0f;
    lbl_1_bss_C->rot.z = 0.0f;
    lbl_1_bss_C->target.x = 0.0f;
    lbl_1_bss_C->target.y = 0.0f;
    lbl_1_bss_C->target.z = 0.0f;
    lbl_1_bss_C->tpLvl = 0.5f;
    lbl_1_bss_C->dist = 2300.0f;
    fn_1_1524();
}

/* asm 1448-1676, 227 insns. Place the shadow camera. */
void fn_1_1524(void)
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

/* asm 1679-1758, 72 insns. Step *value toward end by (end-start)/div; the steps left, 0 once there. */
s16 fn_1_18B0(float *value, float div, float start, float end)
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
    step = M549_DIST(start, end);
    start = M549_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1761-1839, 71 insns. Unreferenced: fn_1_18B0 without the final clamp to end. */
s16 fn_1_19D0(float *value, float div, float start, float end)
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
    step = M549_DIST(start, end);
    start = M549_DIST(start, *value);
    if(step <= start) {
        count = 0;
    }
    return count;
}

/* asm 1842-1872, 29 insns. A timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1AEC(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1875-1887, 11 insns. */
void fn_1_1B60(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1890-1901, 10 insns. */
BOOL fn_1_1B8C(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1904-1919, 14 insns. */
void fn_1_1BB4(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1922-2148, 213 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1BEC(M549_WORK *work, s16 padNo, s16 no)
{
    M549_MODEL *model;
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
    print8(25, 136, 1.5f, lbl_1_data_378, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_3A6, no);
    return result;
}

/* asm 2151-2153, 1 insn. */
void fn_1_1F40(void)
{
}

/* asm 2156-2489, 302 insns. Unreferenced debug: move the camera globals with pad padNo. */
void fn_1_1F44(s16 padNo)
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
    print8(25, 30, 1.5f, lbl_1_data_3AE, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_3D3, CRot.x, CRot.y, CRot.z);
}

/*
 * asm 2492-2580, 85 insns. The dust particle model: 100 puffs on layer 5. Its
 * sprite is DATANUM(DATA_m549, 0x08), the one entry lbl_1_data_230 skips.
 * Unlike m553's it does not toggle DISPOFF.
 */
void fn_1_23FC(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m549, 0x08), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_15D8 = HuMemDirectMallocNum(HEAP_HEAP, 100*sizeof(M549_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_15DC = Hu3DParticleCreate(anim, 100);
    Hu3DModelLayerSet(lbl_1_bss_15DC, 5);
    Hu3DParticleHookSet(lbl_1_bss_15DC, fn_1_3144);
    Hu3DModelCameraSet(lbl_1_bss_15DC, 1);
    Hu3DParticleBlendModeSet(lbl_1_bss_15DC, 1);
    particle = Hu3DData[lbl_1_bss_15DC].hookData;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_15D8;
    particle->count = 0;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 2583-2809, 223 insns. Twelve dust puffs in a 30-degree ring around pos. */
void fn_1_2550(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    for(i=0; i<12; i++) {
        size = 6.0f+frandmod(6);
        lbl_1_data_3F0.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_3F0.vel.y = 0.0f;
        lbl_1_data_3F0.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_3F0.alphaSpeed = alpha;
        puffPos.x = pos->x+(20.0*sin((M_PI*(30.0f*i))/180.0));
        puffPos.y = 10.0f+pos->y;
        puffPos.z = pos->z+(20.0*cos((M_PI*(30.0f*i))/180.0));
        lbl_1_data_3F0.accelY = 0.01f*frandmod(20);
        size = 20.0f+frandmod(20);
        fn_1_2F70(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_3F0);
    }
}

/*
 * asm 2812-3244, 425 insns. A burst of 48 dust puffs along a wave at pos:
 * side 0 spreads along x, any other side along z.
 */
void fn_1_28CC(HuVecF *pos, s16 side)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 alpha;

    if(side == 0) {
        for(i=0; i<48; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_3F0.vel.x = size*sin((M_PI*(7.5f*i))/180.0);
            lbl_1_data_3F0.vel.y = frandmod(2);
            lbl_1_data_3F0.vel.z = frandmod(10)-5.0f;
            alpha = -frandmod(6)-6.0f;
            lbl_1_data_3F0.alphaSpeed = alpha;
            puffPos.x = pos->x+(60.0*sin((M_PI*(7.5f*i))/180.0));
            puffPos.y = 5.0f+pos->y;
            puffPos.z = (pos->z+frandmod(40))-20.0f;
            lbl_1_data_3F0.accelY = 0.01f*frandmod(20);
            size = 10.0f+frandmod(15);
            fn_1_2F70(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_3F0);
        }
    } else {
        for(i=0; i<48; i++) {
            size = 5.0f+frandmod(5);
            lbl_1_data_3F0.vel.x = frandmod(10)-5.0f;
            lbl_1_data_3F0.vel.y = frandmod(2);
            lbl_1_data_3F0.vel.z = size*sin((M_PI*(7.5f*i))/180.0);
            alpha = -frandmod(6)-6.0f;
            lbl_1_data_3F0.alphaSpeed = alpha;
            puffPos.x = (pos->x+frandmod(40))-20.0f;
            puffPos.y = 5.0f+pos->y;
            puffPos.z = pos->z+(60.0*sin((M_PI*(7.5f*i))/180.0));
            lbl_1_data_3F0.accelY = 0.01f*frandmod(20);
            size = 10.0f+frandmod(15);
            fn_1_2F70(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_3F0);
        }
    }
}

/* asm 3247-3372, 117 insns. Spawn one dust puff living 60 frames; the slot, or -1 when all are live. */
s16 fn_1_2F70(float x, float y, float z, float scale, M549_PARTICLEPARAM *param)
{
    HU3DMODEL *model;
    M549_PARTICLEPARAM *work;
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
 * asm 3375-3657, 270 insns. The dust hook: move, fade and shrink every live
 * puff. parManId counts its life down. Retail declares a live-puff counter and
 * never increments it, and unlike m543's it does not flush the data range.
 */
void fn_1_3144(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M549_PARTICLEPARAM *param;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 value;
    s16 liveNum;

    param = particle->work;
    liveNum = 0;
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
}

/* asm 3660-3673, 12 insns. */
void fn_1_357C(void)
{
    lbl_1_bss_580.jingleNo = HuAudJinglePlay(131);
}

/* asm 3676-3689, 12 insns. */
void fn_1_35AC(void)
{
    lbl_1_bss_580.bgmNo = HuAudBGMPlay(55);
}

/* asm 3692-3721, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_35DC(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_580.bgmNo;
    } else {
        no = lbl_1_bss_580.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 3724-3751, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_3644(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_580.bgmNo;
    } else {
        no = lbl_1_bss_580.jingleNo;
    }
    HuAudSStreamStop(no);
}

/*
 * asm 3754-3802, 44 insns. Slots 0 and 1 are the two duellists' looping
 * effects, so they only restart once fn_1_39C4 has parked them at -1.
 */
void fn_1_36A4(s16 no)
{
    if((no != 0 && no != 1) || lbl_1_bss_580.seF[no] == -1) {
        lbl_1_bss_580.seF[no] = 1;
        lbl_1_bss_580.seNo[no] = HuAudFXPlay(lbl_1_data_428[no]);
    }
}

/* asm 3805-3857, 48 insns. */
void fn_1_3754(s16 no, s16 vol, s16 pan)
{
    if((no != 0 && no != 1) || lbl_1_bss_580.seF[no] == -1) {
        lbl_1_bss_580.seF[no] = 1;
        lbl_1_bss_580.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_428[no], vol, pan);
    }
}

/* asm 3860-3898, 36 insns. */
void fn_1_3814(s16 no, s16 pan)
{
    if(lbl_1_bss_580.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_580.seNo[no], pan);
    }
}

/* asm 3901-3939, 36 insns. */
void fn_1_38A4(s16 no, s16 pitch)
{
    if(lbl_1_bss_580.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 2) {
        HuAudFXPitchSet(lbl_1_bss_580.seNo[no], pitch);
    }
}

/* asm 3942-3980, 36 insns. */
void fn_1_3934(s16 no, s16 vol)
{
    if(lbl_1_bss_580.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 2) {
        HuAudFXVolSet(lbl_1_bss_580.seNo[no], vol);
    }
}

/* asm 3983-4036, 50 insns. Parking seF at -1 is what lets fn_1_36A4 restart slot 0 or 1. */
void fn_1_39C4(s16 no)
{
    if(lbl_1_bss_580.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 3)) {
        lbl_1_bss_580.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_580.seNo[no]);
    }
}

/* asm 4039-4092, 50 insns. Unreferenced; fn_1_39C4 is the same. */
void fn_1_3A8C(s16 no)
{
    if(lbl_1_bss_580.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_580.seNo[no]) == 3)) {
        lbl_1_bss_580.seF[no] = -1;
        HuAudFXStop(lbl_1_bss_580.seNo[no]);
    }
}

/* asm 4095-4104, 8 insns. */
void fn_1_3B54(void)
{
    HuAudAllStop();
}
