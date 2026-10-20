/*
 * m551dll -- a KETTOU duel (overlay #65): the sequence hooks, cameras, light,
 * shadow, timer and debug helpers, two dust-particle systems, the duellists'
 * material fades, the sound helpers, and the thousand scraps of paper that
 * blow across the stage. Written from the reference assembly, functions in
 * reference order; line ranges are into
 * build/mp5-asm/m551Dll/asm/REL/m551Dll/m551.s.
 *
 * _prolog and _epilog are not reproduced.
 *
 * Two constants a reader will not expect: the four paper models are named
 * "m546-kami01".."m546-kami04" -- m546's object names, not m551's -- and
 * fn_1_1970 is the *integer* twin of fn_1_1850, not the float one m543 has
 * under the same size.
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

#include "REL/m551Dll/m551.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

/* A distance that never goes negative the way retail computes it (m545's M545_DIST). */
#define M551_DIST(a, b) ((((a)-(b)) > 0.0f) ? ((a)-(b)) : ((a)-(-1.0f*(b))))
#define M551_IDIST(a, b) ((((a)-(b)) > 0) ? ((a)-(b)) : ((a)-(-1*(b))))

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
s32 fn_1_805C(M551_WORK *work);
s32 fn_1_81F4(void);
s32 fn_1_822C(void);
s32 fn_1_828C(void);
s32 fn_1_89B0(void);
s32 fn_1_8CBC(void);
s32 fn_1_8D20(void);
s32 fn_1_8FF4(void);
s32 fn_1_9024(void);
void fn_1_44C(s16 no);
void fn_1_E94(void);
void fn_1_139C(void);
s16 fn_1_1B44(M551_WORK *work, s16 padNo, s16 no);
void fn_1_1E98(void);
void fn_1_1E9C(s16 padNo);
void fn_1_3D38(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);
void fn_1_5614(HU3DMODEL *model, Mtx *mtx);

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

/* Fourteen motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][M551_MOTION_MAX] = {
    { 0x008C0000, 0x008C0002, 0x008C0003, 0x008C0004, 0x008C0009, 0x008C000A, 0x008C001B, 0x008C0024, 0x008C002B, 0x008C002F, 0x008C0031, 0x008C0039, 0x008C0006, 0x008C0007 },
    { 0x00330000, 0x00330002, 0x00330003, 0x00330004, 0x00330009, 0x0033000A, 0x0033001B, 0x00330024, 0x0033002B, 0x0033002F, 0x00330031, 0x00330039, 0x00330006, 0x00330007 },
    { 0x00B70000, 0x00B70002, 0x00B70003, 0x00B70004, 0x00B70009, 0x00B7000A, 0x00B7001B, 0x00B70024, 0x00B7002B, 0x00B7002F, 0x00B70031, 0x00B70039, 0x00B70006, 0x00B70007 },
    { 0x00ED0000, 0x00ED0002, 0x00ED0003, 0x00ED0004, 0x00ED0009, 0x00ED000A, 0x00ED001B, 0x00ED0024, 0x00ED002B, 0x00ED002F, 0x00ED0031, 0x00ED0039, 0x00ED0006, 0x00ED0007 },
    { 0x00E60000, 0x00E60002, 0x00E60003, 0x00E60004, 0x00E60009, 0x00E6000A, 0x00E6001B, 0x00E60024, 0x00E6002B, 0x00E6002F, 0x00E60031, 0x00E60039, 0x00E60006, 0x00E60007 },
    { 0x00170000, 0x00170002, 0x00170003, 0x00170004, 0x00170009, 0x0017000A, 0x0017001B, 0x00170024, 0x0017002B, 0x0017002F, 0x00170031, 0x00170039, 0x00170006, 0x00170007 },
    { 0x00E00000, 0x00E00002, 0x00E00003, 0x00E00004, 0x00E00009, 0x00E0000A, 0x00E0001B, 0x00E00024, 0x00E0002B, 0x00E0002F, 0x00E00031, 0x00E00039, 0x00E00006, 0x00E00007 },
    { 0x002D0000, 0x002D0002, 0x002D0003, 0x002D0004, 0x002D0009, 0x002D000A, 0x002D001B, 0x002D0024, 0x002D002B, 0x002D002F, 0x002D0031, 0x002D0039, 0x002D0006, 0x002D0007 },
    { 0x00C90000, 0x00C90002, 0x00C90003, 0x00C90004, 0x00C90009, 0x00C9000A, 0x00C9001B, 0x00C90024, 0x00C9002B, 0x00C9002F, 0x00C90031, 0x00C90039, 0x00C90006, 0x00C90007 },
    { 0x00B00000, 0x00B00002, 0x00B00003, 0x00B00004, 0x00B00009, 0x00B0000A, 0x00B0001B, 0x00B00024, 0x00B0002B, 0x00B0002F, 0x00B00031, 0x00B00039, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B00003, 0x00B00004, 0x00B00009, 0x00B0000A, 0x00B0001B, 0x00B00024, 0x00B0002B, 0x00B0002F, 0x00B00031, 0x00B00039, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B00003, 0x00B00004, 0x00B00009, 0x00B0000A, 0x00B0001B, 0x00B00024, 0x00B0002B, 0x00B0002F, 0x00B00031, 0x00B00039, 0x00B00006, 0x00B00007 },
    { 0x00B00000, 0x00B00002, 0x00B00003, 0x00B00004, 0x00B00009, 0x00B0000A, 0x00B0001B, 0x00B00024, 0x00B0002B, 0x00B0002F, 0x00B00031, 0x00B00039, 0x00B00006, 0x00B00007 }
};

/* files/data/m551.bin: the stage models (passed to fn_1_169F4). */
unsigned int lbl_1_data_300[26] = {
    DATANUM(DATA_m551, 0x00), DATANUM(DATA_m551, 0x01), DATANUM(DATA_m551, 0x02), DATANUM(DATA_m551, 0x03),
    DATANUM(DATA_m551, 0x04), DATANUM(DATA_m551, 0x05), DATANUM(DATA_m551, 0x06), DATANUM(DATA_m551, 0x07),
    DATANUM(DATA_m551, 0x08), DATANUM(DATA_m551, 0x09), DATANUM(DATA_m551, 0x0A), DATANUM(DATA_m551, 0x0B),
    DATANUM(DATA_m551, 0x0C), DATANUM(DATA_m551, 0x0D), DATANUM(DATA_m551, 0x0E), DATANUM(DATA_m551, 0x0F),
    DATANUM(DATA_m551, 0x10), DATANUM(DATA_m551, 0x11), DATANUM(DATA_m551, 0x12), DATANUM(DATA_m551, 0x13),
    DATANUM(DATA_m551, 0x14), DATANUM(DATA_m551, 0x15), DATANUM(DATA_m551, 0x16), DATANUM(DATA_m551, 0x17),
    DATANUM(DATA_m551, 0x18),
    0x00000000
};

/* The four cameras fn_1_44C can create; only camera 0 is. */
M551_CAMERAINIT lbl_1_data_368[4] = {
    { { 0.0f, 215.0f, -325.0f }, { -35.0f, 0.0f, 0.0f }, 119.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 20.0f }, { -35.0f, 0.0f, 0.0f }, 1415.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 208.0f, 20.0f }, { -40.0f, 0.0f, 0.0f }, 1500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_438[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* fn_1_1B44's and fn_1_1E9C's debug lines. */
char lbl_1_data_458[] = "OBJ X:%.1f Y:%.1f Z:%.1f RX%.1f RY%.1f RZ%.1f";
char lbl_1_data_486[] = "OBJW %d";
char lbl_1_data_48E[] = "CAMPOS X:%.1f Y:%.1f Z:%.1f ZOOM%.1f";
char lbl_1_data_4B3[] = "CAMROT X:%.1f Y:%.1f Z:%.1f";

/* The dust puff fn_1_2610, fn_1_29DC and fn_1_3270 edit and spawn. */
M551_PARTICLEPARAM lbl_1_data_4D0 = {
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

/* One of the four paper colours fn_1_43F8 picks from. */
float lbl_1_data_508[4][3] = {
    { 255.0f, 191.25f, 204.0f },
    { 255.0f, 255.0f, 153.0f },
    { 178.5f, 255.0f, 255.0f },
    { 153.0f, 255.0f, 191.25f }
};

/* And one of the four scales, all of which are 1. */
float lbl_1_data_538[4][3] = {
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f }
};

/* fn_1_41C8 copies the paper models' object names through sprintf. */
char lbl_1_data_568[] = "%s";
char lbl_1_data_56B[] = "m546-kami01";
char lbl_1_data_577[] = "m546-kami02";
char lbl_1_data_583[] = "m546-kami03";
char lbl_1_data_58F[] = "m546-kami04";

/* fn_1_5CEC's sound effects. */
s16 lbl_1_data_59C[8] = {
    0x861, 0x862, 0x863, 0x864, 0x865, 0x866, 0x867, 0x868
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

s32 lbl_1_bss_17994;                /* unreferenced; dtk sizes lbl_1_bss_17990 8 */
OMOBJMAN *lbl_1_bss_17990;
M551_WORK lbl_1_bss_176A8;
M551_MODEL lbl_1_bss_16D94[M551_MODEL_MAX];
HU3DMOTID lbl_1_bss_16D5C[2][M551_MOTION_MAX];
M551_GAME lbl_1_bss_16CB4;
M551_DUELLIST lbl_1_bss_16A84[2];
M551_PANEL lbl_1_bss_16844[12];
M551_PAPERMAN lbl_1_bss_1679C;
M551_PAPER lbl_1_bss_3C[M551_PAPER_MAX];
M551_CAMERA *lbl_1_bss_38;
M551_LIGHT *lbl_1_bss_34;
M551_SHADOW *lbl_1_bss_30;
M551_ACTORS lbl_1_bss_0;

/* asm 61-200, 136 insns. */
void ObjectSetup(void)
{
    s16 i;

    lbl_1_bss_17990 = MgActorObjectSetup();
    fn_1_169F4(&lbl_1_bss_176A8, lbl_1_bss_16D94, lbl_1_data_300);
    lbl_1_bss_38 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M551_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_38, 0, (sizeof(M551_CAMERA)*4)+8);
    lbl_1_bss_34 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M551_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_34, 0, sizeof(M551_LIGHT));
    lbl_1_bss_30 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M551_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_30, 0, sizeof(M551_SHADOW));
    fn_1_44C(0);
    fn_1_E94();
    fn_1_139C();
    fn_1_16C54(0, lbl_1_data_28[lbl_1_bss_176A8.chr[0].charNo]);
    fn_1_16C54(1, lbl_1_data_28[lbl_1_bss_176A8.chr[1].charNo]);
    for(i=0; i<2; i++) {
        fn_1_16C74(i, lbl_1_bss_16D5C[i]);
    }
    omAddObjEx(lbl_1_bss_17990, 32730, 0, 0, -1, fn_1_17264);
    omAddObjEx(lbl_1_bss_17990, 32730, 0, 0, -1, fn_1_448);
    Hu3DBGColorSet(0, 0, 0);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(3, 1);
    MgSeqModeDelaySet(2, 1);
    MgSeqModeDelaySet(2, 450);
    MgSeqModeDelaySet(7, 6000);
    MgSeqModeDelaySet(9, 60);
}

/* asm 203-218, 13 insns. Init hook. */
void fn_1_2C0(s16 mode, s16 frameNo)
{
    if(fn_1_805C(&lbl_1_bss_176A8)) {
        MgSeqModeNext();
    }
}

/* asm 221-234, 11 insns. Fade-in hook. */
void fn_1_2F4(s16 mode, s16 frameNo)
{
    if(fn_1_81F4()) {
        MgSeqModeNext();
    }
}

/* asm 237-250, 11 insns. Start hook. */
void fn_1_320(s16 mode, s16 frameNo)
{
    if(fn_1_822C()) {
        MgSeqModeNext();
    }
}

/* asm 253-266, 11 insns. Main hook. */
void fn_1_34C(s16 mode, s16 frameNo)
{
    if(fn_1_828C()) {
        MgSeqModeNext();
    }
}

/* asm 269-282, 11 insns. Finish hook. */
void fn_1_378(s16 mode, s16 frameNo)
{
    if(fn_1_89B0()) {
        MgSeqModeNext();
    }
}

/* asm 285-298, 11 insns. Pre-winner hook. */
void fn_1_3A4(s16 mode, s16 frameNo)
{
    if(fn_1_8CBC()) {
        MgSeqModeNext();
    }
}

/* asm 301-314, 11 insns. Winner hook. */
void fn_1_3D0(s16 mode, s16 frameNo)
{
    if(fn_1_8D20()) {
        MgSeqModeNext();
    }
}

/* asm 317-326, 8 insns. Fade-out hook. */
void fn_1_3FC(s16 mode, s16 frameNo)
{
    fn_1_8FF4();
}

/* asm 329-342, 11 insns. Close hook. */
void fn_1_41C(s16 mode, s16 frameNo)
{
    if(fn_1_9024()) {
        MgSeqModeNext();
    }
}

/* asm 345-347, 1 insn. An empty object. */
void fn_1_448(OMOBJ *obj)
{
}

/*
 * asm 350-659, 308 insns. Create camera `no` from lbl_1_data_368, then seed
 * the debug camera globals from camera 0's center and rotation and camera
 * `no`'s zoom (m543 fn_1_44C).
 */
void fn_1_44C(s16 no)
{
    lbl_1_bss_38[no].no = no;
    lbl_1_bss_38[no].center.x = lbl_1_data_368[no].center.x;
    lbl_1_bss_38[no].center.y = lbl_1_data_368[no].center.y;
    lbl_1_bss_38[no].center.z = lbl_1_data_368[no].center.z;
    lbl_1_bss_38[no].rot.x = lbl_1_data_368[no].rot.x;
    lbl_1_bss_38[no].rot.y = lbl_1_data_368[no].rot.y;
    lbl_1_bss_38[no].rot.z = lbl_1_data_368[no].rot.z;
    lbl_1_bss_38[no].zoom = lbl_1_data_368[no].zoom;
    lbl_1_bss_38[no].aspect = lbl_1_data_368[no].aspect;
    lbl_1_bss_38[no].vpX = lbl_1_data_368[no].vpX;
    lbl_1_bss_38[no].vpY = lbl_1_data_368[no].vpY;
    lbl_1_bss_38[no].vpW = lbl_1_data_368[no].vpW;
    lbl_1_bss_38[no].vpH = lbl_1_data_368[no].vpH;
    lbl_1_bss_38[no].fov = lbl_1_data_368[no].fov;
    Hu3DCameraCreate(lbl_1_data_438[no]);
    Hu3DCameraViewportSet(lbl_1_data_438[no], lbl_1_bss_38[no].vpX, lbl_1_bss_38[no].vpY, lbl_1_bss_38[no].vpW, lbl_1_bss_38[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_438[no], lbl_1_bss_38[no].fov, 20.0f, 30000.0f, lbl_1_bss_38[no].aspect);
    fn_1_91C(no);
    Center.x = lbl_1_data_368[0].center.x;
    Center.y = lbl_1_data_368[0].center.y;
    Center.z = lbl_1_data_368[0].center.z;
    CRot.x = lbl_1_data_368[0].rot.x;
    CRot.y = lbl_1_data_368[0].rot.y;
    CRot.z = lbl_1_data_368[0].rot.z;
    CZoom = lbl_1_data_368[no].zoom;
}

/* asm 662-1013, 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_91C(s16 no)
{
    lbl_1_bss_38[no].pos.x = lbl_1_bss_38[no].center.x+(lbl_1_bss_38[no].zoom*(cos((M_PI*lbl_1_bss_38[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_38[no].rot.y)/180.0)));
    lbl_1_bss_38[no].pos.y = lbl_1_bss_38[no].center.y+(lbl_1_bss_38[no].zoom*-sin((M_PI*lbl_1_bss_38[no].rot.x)/180.0));
    lbl_1_bss_38[no].pos.z = lbl_1_bss_38[no].center.z+(lbl_1_bss_38[no].zoom*(cos((M_PI*lbl_1_bss_38[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_38[no].rot.y)/180.0)));
    lbl_1_bss_38[no].up.x = sin((M_PI*lbl_1_bss_38[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_38[no].rot.y)/180.0);
    lbl_1_bss_38[no].up.y = cos((M_PI*lbl_1_bss_38[no].rot.x)/180.0);
    lbl_1_bss_38[no].up.z = sin((M_PI*lbl_1_bss_38[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_38[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_438[no], lbl_1_bss_38[no].pos.x, lbl_1_bss_38[no].pos.y, lbl_1_bss_38[no].pos.z,
        lbl_1_bss_38[no].up.x, lbl_1_bss_38[no].up.y, lbl_1_bss_38[no].up.z,
        lbl_1_bss_38[no].center.x, lbl_1_bss_38[no].center.y, lbl_1_bss_38[no].center.z);
}

/* asm 1016-1157, 140 insns. The global light (m543 fn_1_E94). */
void fn_1_E94(void)
{
    Hu3DLighInit();
    lbl_1_bss_34->pos.x = 0.0f;
    lbl_1_bss_34->pos.y = 0.0f;
    lbl_1_bss_34->pos.z = 0.0f;
    lbl_1_bss_34->target.x = 0.0f;
    lbl_1_bss_34->target.y = 0.0f;
    lbl_1_bss_34->target.z = 0.0f;
    lbl_1_bss_34->rot.x = -23.0f;
    lbl_1_bss_34->rot.y = 0.0f;
    lbl_1_bss_34->rot.z = 0.0f;
    lbl_1_bss_34->dist = 1000.0f;
    lbl_1_bss_34->color.r = 255;
    lbl_1_bss_34->color.g = 255;
    lbl_1_bss_34->color.b = 255;
    lbl_1_bss_34->color.a = 255;
    PSVECSubtract(&lbl_1_bss_34->target, &lbl_1_bss_34->pos, &lbl_1_bss_34->dir);
    lbl_1_bss_34->id = Hu3DGLightCreateV(&lbl_1_bss_34->pos, &lbl_1_bss_34->dir, &lbl_1_bss_34->color);
    fn_1_10C4();
    Hu3DGLightStaticSet(lbl_1_bss_34->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_34->id);
}

/* asm 1160-1343, 182 insns. Place the light from its target, rotation and distance. */
void fn_1_10C4(void)
{
    lbl_1_bss_34->pos.x = lbl_1_bss_34->target.x+(lbl_1_bss_34->dist*(cos((M_PI*lbl_1_bss_34->rot.x)/180.0)*sin((M_PI*lbl_1_bss_34->rot.y)/180.0)));
    lbl_1_bss_34->pos.y = lbl_1_bss_34->target.y+(lbl_1_bss_34->dist*-sin((M_PI*lbl_1_bss_34->rot.x)/180.0));
    lbl_1_bss_34->pos.z = lbl_1_bss_34->target.z+(lbl_1_bss_34->dist*(cos((M_PI*lbl_1_bss_34->rot.x)/180.0)*cos((M_PI*lbl_1_bss_34->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_34->target, &lbl_1_bss_34->pos, &lbl_1_bss_34->dir);
    PSVECNormalize(&lbl_1_bss_34->dir, &lbl_1_bss_34->dir);
    Hu3DGLightPosSetV(lbl_1_bss_34->id, &lbl_1_bss_34->pos, &lbl_1_bss_34->dir);
    Hu3DGLightColorSet(lbl_1_bss_34->id, lbl_1_bss_34->color.r, lbl_1_bss_34->color.g, lbl_1_bss_34->color.b, lbl_1_bss_34->color.a);
}

/* asm 1346-1421, 74 insns. The shadow (m543 fn_1_139C at 3600, not 3500). */
void fn_1_139C(void)
{
    Hu3DShadowCreate(30.0f, 20.0f, 30000.0f);
    lbl_1_bss_30->rot.x = -90.0f;
    lbl_1_bss_30->rot.y = 0.0f;
    lbl_1_bss_30->rot.z = 0.0f;
    lbl_1_bss_30->target.x = 0.0f;
    lbl_1_bss_30->target.y = 0.0f;
    lbl_1_bss_30->target.z = 0.0f;
    lbl_1_bss_30->tpLvl = 0.5f;
    lbl_1_bss_30->dist = 3600.0f;
    fn_1_14C4();
}

/* asm 1424-1652, 227 insns. Place the shadow camera. */
void fn_1_14C4(void)
{
    lbl_1_bss_30->pos.x = lbl_1_bss_30->target.x+(lbl_1_bss_30->dist*(cos((M_PI*lbl_1_bss_30->rot.x)/180.0)*sin((M_PI*lbl_1_bss_30->rot.y)/180.0)));
    lbl_1_bss_30->pos.y = lbl_1_bss_30->target.y+(lbl_1_bss_30->dist*-sin((M_PI*lbl_1_bss_30->rot.x)/180.0));
    lbl_1_bss_30->pos.z = lbl_1_bss_30->target.z+(lbl_1_bss_30->dist*(cos((M_PI*lbl_1_bss_30->rot.x)/180.0)*cos((M_PI*lbl_1_bss_30->rot.y)/180.0)));
    lbl_1_bss_30->up.x = sin((M_PI*lbl_1_bss_30->rot.x)/180.0)*sin((M_PI*lbl_1_bss_30->rot.y)/180.0);
    lbl_1_bss_30->up.y = cos((M_PI*lbl_1_bss_30->rot.x)/180.0);
    lbl_1_bss_30->up.z = sin((M_PI*lbl_1_bss_30->rot.x)/180.0)*cos((M_PI*lbl_1_bss_30->rot.y)/180.0);
    Hu3DShadowTPLvlSet(lbl_1_bss_30->tpLvl);
    Hu3DShadowPosSet(&lbl_1_bss_30->pos, &lbl_1_bss_30->up, &lbl_1_bss_30->target);
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
    step = M551_DIST(start, end);
    start = M551_DIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1737-1797, 53 insns. Unreferenced: fn_1_1850 on an int. */
s16 fn_1_1970(int *value, int div, int start, int end)
{
    s16 step;
    s16 count;

    count = 0;
    step = (end-start)/div;
    *value += step;
    if(step) {
        count = (end-*value)/step;
    }
    count++;
    step = M551_IDIST(start, end);
    start = M551_IDIST(start, *value);
    if(step <= start) {
        *value = end;
        count = 0;
    }
    return count;
}

/* asm 1800-1830, 29 insns. A timer of maxTime seconds at x, y. */
MGTIMER *fn_1_1A44(int type, int maxTime, int endTime, float x, float y)
{
    MGTIMER *timer;

    timer = MgTimerCreate(type);
    MgTimerParamSet(timer, maxTime*60, endTime*60, 0);
    MgTimerPosSet(timer, x, y);
    return timer;
}

/* asm 1833-1845, 11 insns. */
void fn_1_1AB8(MGTIMER *timer)
{
    MgTimerModeOnSet(timer, 1);
}

/* asm 1848-1859, 10 insns. */
BOOL fn_1_1AE4(MGTIMER *timer)
{
    return MgTimerDoneCheck(timer);
}

/* asm 1862-1877, 14 insns. */
void fn_1_1B0C(MGTIMER *timer)
{
    MgTimerDispOff(timer);
    MgTimerKill(timer);
}

/* asm 1880-2106, 213 insns. Unreferenced debug: move model `no` with pad padNo. */
s16 fn_1_1B44(M551_WORK *work, s16 padNo, s16 no)
{
    M551_MODEL *model;
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
    print8(25, 136, 1.5f, lbl_1_data_458, model->pos.x, model->pos.y, model->pos.z, model->rot.x, model->rot.y, model->rot.z);
    print8(25, 154, 1.5f, lbl_1_data_486, no);
    return result;
}

/* asm 2109-2111, 1 insn. */
void fn_1_1E98(void)
{
}

/* asm 2114-2447, 302 insns. Unreferenced debug: move the camera globals with pad padNo. */
void fn_1_1E9C(s16 padNo)
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
    print8(25, 30, 1.5f, lbl_1_data_48E, Center.x, Center.y, Center.z, CZoom);
    print8(25, 48, 1.5f, lbl_1_data_4B3, CRot.x, CRot.y, CRot.z);
}

/*
 * asm 2450-2630, 175 insns. Two dust-particle models of 150 puffs each, on
 * layer 4. Both share lbl_1_bss_17998, so the second create overwrites the
 * first's work pointer -- harmless, because fn_1_3B58 reads the work back off
 * the particle rather than off the global.
 */
void fn_1_2354(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    ANIMDATA *anim;

    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m551, 0x19), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_17998 = HuMemDirectMallocNum(HEAP_HEAP, 150*sizeof(M551_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_1799C[0] = Hu3DParticleCreate(anim, 150);
    Hu3DParticleHookSet(lbl_1_bss_1799C[0], fn_1_3D38);
    Hu3DParticleBlendModeSet(lbl_1_bss_1799C[0], 1);
    Hu3DModelLayerSet(lbl_1_bss_1799C[0], 4);
    Hu3DModelCameraSet(lbl_1_bss_1799C[0], 1);
    Hu3DModelAttrSet(lbl_1_bss_1799C[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_1799C[0], HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_1799C[0]].hookData;
    particle->count = 0;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_17998;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(DATANUM(DATA_m551, 0x1A), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_17998 = HuMemDirectMallocNum(HEAP_HEAP, 150*sizeof(M551_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_1799C[1] = Hu3DParticleCreate(anim, 150);
    Hu3DParticleHookSet(lbl_1_bss_1799C[1], fn_1_3D38);
    Hu3DParticleBlendModeSet(lbl_1_bss_1799C[1], 1);
    Hu3DModelLayerSet(lbl_1_bss_1799C[1], 4);
    Hu3DModelCameraSet(lbl_1_bss_1799C[1], 1);
    Hu3DModelAttrSet(lbl_1_bss_1799C[1], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_1799C[1], HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_1799C[1]].hookData;
    particle->count = 0;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_17998;
    for(i=0, data=particle->data; i<particle->maxCnt; i++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 2633-2879, 243 insns. Unreferenced: twelve dust puffs in a ring around pos. */
void fn_1_2610(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    float scale;
    s16 i;
    s16 alpha;
    s16 unused;

    unused = 16;
    size = 0.8f;
    scale = 1.0f;
    for(i=0; i<12; i++) {
        puffPos.x = pos->x+(scale*(20.0*sin((M_PI*(30.0f*i))/180.0)));
        puffPos.y = pos->y+(10.0f*scale);
        puffPos.z = pos->z+(scale*(20.0*cos((M_PI*(30.0f*i))/180.0)));
        size = scale*(6.0f+frandmod(6));
        lbl_1_data_4D0.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_4D0.vel.y = 0.0f;
        lbl_1_data_4D0.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01*frandmod(20);
        size = scale*(20.0+frandmod(20));
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 1);
    }
}

/* asm 2882-3436, 549 insns. Unreferenced: two rings of 36 puffs, the second offset by half a turn. */
void fn_1_29DC(HuVecF *pos)
{
    HuVecF puffPos;
    float step;
    float radius;
    float size;
    s16 i;
    s16 num;
    s16 alpha;

    num = 36;
    step = 360.0f/num;
    for(i=0; i<num; i++) {
        radius = 120.0f+frandmod(20);
        puffPos.x = pos->x+(sin((M_PI*(step*i))/180.0)*radius);
        puffPos.y = 10.0f+pos->y;
        radius = 120.0f+frandmod(20);
        puffPos.z = pos->z+(cos((M_PI*(step*i))/180.0)*radius);
        size = 3.0f+frandmod(5);
        lbl_1_data_4D0.vel.x = size*sin((M_PI*(step*i))/180.0);
        lbl_1_data_4D0.vel.y = frandmod(5);
        lbl_1_data_4D0.vel.z = size*cos((M_PI*(step*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01*frandmod(20);
        size = 30.0f+frandmod(30);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 1);
    }
    for(i=0; i<num; i++) {
        radius = 80.0f+frandmod(50);
        puffPos.x = pos->x+(sin((M_PI*((num/2)+(step*i)))/180.0)*radius);
        puffPos.y = 10.0f+pos->y;
        radius = 80.0f+frandmod(50);
        puffPos.z = pos->z+(cos((M_PI*((num/2)+(step*i)))/180.0)*radius);
        size = 3.0f+frandmod(5);
        lbl_1_data_4D0.vel.x = size*sin((M_PI*((num/2)+(step*i)))/180.0);
        lbl_1_data_4D0.vel.y = frandmod(5);
        lbl_1_data_4D0.vel.z = size*cos((M_PI*((num/2)+(step*i)))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01*frandmod(20);
        size = 30.0f+frandmod(30);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 1);
    }
}

/* asm 3439-4018, 570 insns. Unreferenced: dust along the far edge, the top, and both sides. */
void fn_1_3270(HuVecF *pos)
{
    HuVecF puffPos;
    float size;
    s16 i;
    s16 backNum;
    s16 topNum;
    s16 rightNum;
    s16 leftNum;
    s16 alpha;

    backNum = 35;
    topNum = 20;
    rightNum = 10;
    leftNum = 10;
    for(i=0; i<backNum; i++) {
        puffPos.x = pos->x+(frandmod(220)-110.0f);
        puffPos.y = pos->y+frandmod(200);
        puffPos.z = 130.0f+pos->z;
        lbl_1_data_4D0.vel.x = frandmod(4)-2.0f;
        lbl_1_data_4D0.vel.y = 5.0f+frandmod(10);
        lbl_1_data_4D0.vel.z = 0.0f;
        alpha = -frandmod(6)-5;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01f*frandmod(20);
        size = 40.0f+frandmod(40);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 0);
    }
    for(i=0; i<topNum; i++) {
        puffPos.x = pos->x+(frandmod(220)-110.0f);
        puffPos.y = 200.0f+pos->y;
        puffPos.z = pos->z+frandmod(100);
        lbl_1_data_4D0.vel.x = frandmod(4)-2.0f;
        lbl_1_data_4D0.vel.y = 5.0f+frandmod(10);
        lbl_1_data_4D0.vel.z = 0.0f;
        alpha = -frandmod(6)-5;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01f*frandmod(20);
        size = 40.0f+frandmod(40);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 0);
    }
    for(i=0; i<rightNum; i++) {
        puffPos.x = 100.0f+pos->x;
        puffPos.y = pos->y+frandmod(200);
        puffPos.z = pos->z+frandmod(100);
        lbl_1_data_4D0.vel.x = frandmod(4)-2.0f;
        lbl_1_data_4D0.vel.y = 5.0f+frandmod(10);
        lbl_1_data_4D0.vel.z = 0.0f;
        alpha = -frandmod(6)-5;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01f*frandmod(20);
        size = 40.0f+frandmod(40);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 0);
    }
    for(i=0; i<leftNum; i++) {
        puffPos.x = pos->x-100.0f;
        puffPos.y = pos->y+frandmod(200);
        puffPos.z = pos->z+frandmod(100);
        lbl_1_data_4D0.vel.x = frandmod(4)-2.0f;
        lbl_1_data_4D0.vel.y = 5.0f+frandmod(10);
        lbl_1_data_4D0.vel.z = 0.0f;
        alpha = -frandmod(6)-5;
        lbl_1_data_4D0.alphaSpeed = alpha;
        lbl_1_data_4D0.accelY = 0.01f*frandmod(20);
        size = 40.0f+frandmod(40);
        fn_1_3B58(puffPos.x, puffPos.y, puffPos.z, size, &lbl_1_data_4D0, 0);
    }
}

/*
 * asm 4021-4149, 120 insns. Spawn one dust puff in particle model `no`; the
 * slot, or -1 when all are live. Unlike m543's it never expires by count:
 * parManId is -1, so only the alpha and the scale retire a puff.
 */
s16 fn_1_3B58(float x, float y, float z, float scale, M551_PARTICLEPARAM *param, s16 no)
{
    HU3DMODEL *model;
    M551_PARTICLEPARAM *work;
    s16 result;
    s16 i;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;

    result = -1;
    model = &Hu3DData[lbl_1_bss_1799C[no]];
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

/*
 * asm 4152-4426, 262 insns. The dust hook: move, fade and shrink every live
 * puff (m544 fn_1_30B8). Unlike m543's it has no life counter and no count of
 * the live puffs, and the alpha retires a puff below 1 rather than below 10.
 */
void fn_1_3D38(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M551_PARTICLEPARAM *param;
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

/*
 * asm 4429-4460, 30 insns. A random number in [-1, 1]. CALLMAP calls it
 * unreferenced because fn_1_43F8 is its only caller and CodeWarrior inlines
 * it at all seven call sites; the out-of-line copy is emitted anyway.
 */
float fn_1_4150(void)
{
    int rand;
    float value;

    rand = frandmod(201)-100;
    value = rand;
    value = value/100.0f;
    return value;
}

/* asm 4463-4593, 129 insns. The paper emitter at pos, drawn from work->models[mdlNo..mdlNo+3]. */
void fn_1_41C8(M551_WORK *work, s16 mdlNo, HuVecF *pos)
{
    memset(&lbl_1_bss_1679C, 0, sizeof(M551_PAPERMAN));
    lbl_1_bss_1679C.activeF = 1;
    lbl_1_bss_1679C.scale = 1.0f;
    lbl_1_bss_1679C.mdlId[0] = work->models[mdlNo].modelId;
    lbl_1_bss_1679C.mdlId[1] = work->models[mdlNo+1].modelId;
    lbl_1_bss_1679C.mdlId[2] = work->models[mdlNo+2].modelId;
    lbl_1_bss_1679C.mdlId[3] = work->models[mdlNo+3].modelId;
    sprintf(lbl_1_bss_1679C.name[0], lbl_1_data_568, lbl_1_data_56B);
    sprintf(lbl_1_bss_1679C.name[1], lbl_1_data_568, lbl_1_data_577);
    sprintf(lbl_1_bss_1679C.name[2], lbl_1_data_568, lbl_1_data_583);
    sprintf(lbl_1_bss_1679C.name[3], lbl_1_data_568, lbl_1_data_58F);
    lbl_1_bss_1679C.pos = *pos;
    lbl_1_bss_1679C.wait = 10;
    lbl_1_bss_1679C.num = 1;
    lbl_1_bss_1679C.hookId = Hu3DHookFuncCreate(fn_1_5614);
    Hu3DModelCameraSet(lbl_1_bss_1679C.hookId, (u16)lbl_1_data_438[0]);
    Hu3DModelLayerSet(lbl_1_bss_1679C.hookId, 0);
}

/* asm 4596-4608, 11 insns. */
void fn_1_43CC(void)
{
    Hu3DModelKill(lbl_1_bss_1679C.hookId);
}

/*
 * asm 4611-5176, 558 insns. Spawn up to `num` scraps this call: each gets a
 * random bearing off the emitter, a downward velocity of at least 2.6, three
 * tumble rates, one of four colours and one of four scales.
 */
void fn_1_43F8(void)
{
    float angle;
    float rand;
    s16 i;
    s16 no;

    for(i=0; i<M551_PAPER_MAX; i++) {
        if(lbl_1_bss_3C[i].activeF != 0) {
            continue;
        }
        lbl_1_bss_3C[i].activeF = 1;
        lbl_1_bss_3C[i].timer = frandmod(30)+136;
        lbl_1_bss_1679C.scale += 0.001f;
        lbl_1_bss_3C[i].restY = lbl_1_bss_1679C.scale;
        lbl_1_bss_3C[i].moveF = 1;
        rand = fn_1_4150();
        angle = 360.0f*rand;
        lbl_1_bss_3C[i].pos.x = lbl_1_bss_1679C.pos.x+(25.0*sin((M_PI*angle)/180.0));
        lbl_1_bss_3C[i].pos.y = lbl_1_bss_1679C.pos.y;
        lbl_1_bss_3C[i].pos.z = lbl_1_bss_1679C.pos.z+(25.0*cos((M_PI*angle)/180.0));
        lbl_1_bss_3C[i].rot.x = 0.0f;
        lbl_1_bss_3C[i].rot.y = 0.0f;
        lbl_1_bss_3C[i].rot.z = 0.0f;
        rand = fn_1_4150();
        lbl_1_bss_3C[i].vel.x = 0.4f*rand;
        rand = fn_1_4150();
        lbl_1_bss_3C[i].vel.y = -1.0f*(6.5f*rand);
        if(lbl_1_bss_3C[i].vel.y > 0.0f) {
            lbl_1_bss_3C[i].vel.y *= -1.0f;
        }
        if(lbl_1_bss_3C[i].vel.y > -2.6000001f) {
            lbl_1_bss_3C[i].vel.y = -2.6000001f;
        }
        rand = fn_1_4150();
        lbl_1_bss_3C[i].vel.z = 0.4f*rand;
        rand = fn_1_4150();
        lbl_1_bss_3C[i].rotSpeed.x = 14.0f*rand;
        rand = fn_1_4150();
        lbl_1_bss_3C[i].rotSpeed.y = 14.0f*rand;
        rand = fn_1_4150();
        lbl_1_bss_3C[i].rotSpeed.z = 14.0f*rand;
        no = frandmod(4);
        lbl_1_bss_3C[i].no = no;
        lbl_1_bss_3C[i].color[0] = lbl_1_data_508[no][0];
        lbl_1_bss_3C[i].color[1] = lbl_1_data_508[no][1];
        lbl_1_bss_3C[i].color[2] = lbl_1_data_508[no][2];
        no = frandmod(4);
        lbl_1_bss_3C[i].scale[0] = lbl_1_data_538[no][0];
        lbl_1_bss_3C[i].scale[1] = lbl_1_data_538[no][1];
        lbl_1_bss_3C[i].scale[2] = lbl_1_data_538[no][2];
        lbl_1_bss_3C[i].tpLvl = 1.0f;
        lbl_1_bss_1679C.total++;
        if(lbl_1_bss_1679C.cnt++ >= lbl_1_bss_1679C.num) {
            break;
        }
    }
}

/*
 * asm 5179-5797, 601 insns. Fly every live scrap, land it, and top the field
 * up: mode 0 falls until it is inside the octagonal floor and near enough the
 * spot model to land on it (3) or beside it (1); 1 and 2 settle it; 3 rests it
 * on the model; 4 is done.
 */
void fn_1_4CB0(void)
{
    float x;
    float z;
    float dx;
    float dz;
    float dist;
    s16 i;

    if(lbl_1_bss_1679C.activeF == 0) {
        return;
    }
    for(i=0; i<M551_PAPER_MAX; i++) {
        if(lbl_1_bss_3C[i].activeF == 0) {
            continue;
        }
        if(lbl_1_bss_3C[i].moveF != 0) {
            lbl_1_bss_3C[i].pos.x += lbl_1_bss_3C[i].vel.x;
            lbl_1_bss_3C[i].pos.y += lbl_1_bss_3C[i].vel.y;
            lbl_1_bss_3C[i].pos.z += lbl_1_bss_3C[i].vel.z;
            lbl_1_bss_3C[i].rot.x += lbl_1_bss_3C[i].rotSpeed.x;
            lbl_1_bss_3C[i].rot.y += lbl_1_bss_3C[i].rotSpeed.y;
            lbl_1_bss_3C[i].rot.z += lbl_1_bss_3C[i].rotSpeed.z;
        }
        x = lbl_1_bss_3C[i].pos.x;
        z = lbl_1_bss_3C[i].pos.z;
        switch(lbl_1_bss_3C[i].mode) {
            case 0:
                if(lbl_1_bss_3C[i].pos.y <= 101.0f) {
                    if((-x+z) > -784.0f && x < 554.0f && (x+z) < 784.0f && z < 554.0f
                        && (-x+z) < 784.0f && x > -554.0f && (x+z) > -784.0f && z > -554.0f) {
                        dx = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.mdlSel].mdlNo[1]].pos.x-x;
                        dz = lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.mdlSel].mdlNo[1]].pos.z-z;
                        dist = sqrt((dx*dx)+(dz*dz));
                        if(dist <= 70.0f) {
                            lbl_1_bss_3C[i].mode = 3;
                        } else {
                            lbl_1_bss_3C[i].mode = 1;
                        }
                    } else {
                        lbl_1_bss_3C[i].mode = 2;
                    }
                }
                break;

            case 1:
                lbl_1_bss_3C[i].pos.y = 101.0f+lbl_1_bss_3C[i].restY;
                lbl_1_bss_3C[i].rot.x = 0.0f;
                lbl_1_bss_3C[i].rot.z = 0.0f;
                lbl_1_bss_3C[i].moveF = 0;
                lbl_1_bss_3C[i].mode = 4;
                break;

            case 2:
                if(lbl_1_bss_3C[i].pos.y <= 1.0f) {
                    lbl_1_bss_3C[i].pos.y = 1.0f+lbl_1_bss_3C[i].restY;
                    lbl_1_bss_3C[i].rot.x = 0.0f;
                    lbl_1_bss_3C[i].rot.z = 0.0f;
                    lbl_1_bss_3C[i].moveF = 0;
                    lbl_1_bss_3C[i].mode = 4;
                }
                break;

            case 3:
                lbl_1_bss_3C[i].pos.y = 36.0f+lbl_1_bss_17A00->models[lbl_1_bss_179A0[lbl_1_bss_16CB4.mdlSel].mdlNo[1]].pos.y;
                lbl_1_bss_3C[i].pos.y += lbl_1_bss_3C[i].restY;
                lbl_1_bss_3C[i].rot.x = 0.0f;
                lbl_1_bss_3C[i].rot.z = 0.0f;
                lbl_1_bss_3C[i].moveF = 0;
                break;

            case 4:
                break;
        }
    }
    if(lbl_1_bss_1679C.wait-- <= 0) {
        if(lbl_1_bss_1679C.total < M551_PAPER_MAX) {
            lbl_1_bss_1679C.wait = frandmod(2)+1;
            lbl_1_bss_1679C.num = 1;
            lbl_1_bss_1679C.cnt = 0;
            fn_1_43F8();
        }
    }
}

/* asm 5800-5952, 147 insns. Draw every live scrap as its model's object. */
void fn_1_5614(HU3DMODEL *model, Mtx *mtx)
{
    Mtx mtx2;
    Mtx rot;
    s16 i;

    if(lbl_1_bss_1679C.activeF != 0) {
        Hu3DModelObjDrawInit();
        for(i=0; i<M551_PAPER_MAX; i++) {
            if(lbl_1_bss_3C[i].activeF == 0) {
                continue;
            }
            PSMTXRotRad(rot, 'z', 0.017453292f*lbl_1_bss_3C[i].rot.z);
            PSMTXRotRad(mtx2, 'x', 0.017453292f*lbl_1_bss_3C[i].rot.x);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXRotRad(rot, 'y', 0.017453292f*lbl_1_bss_3C[i].rot.y);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXTrans(rot, lbl_1_bss_3C[i].pos.x, lbl_1_bss_3C[i].pos.y, lbl_1_bss_3C[i].pos.z);
            PSMTXConcat(rot, mtx2, mtx2);
            PSMTXConcat(*mtx, mtx2, mtx2);
            Hu3DModelTPLvlSet(lbl_1_bss_1679C.mdlId[lbl_1_bss_3C[i].no], lbl_1_bss_3C[i].tpLvl);
            Hu3DModelObjDraw(lbl_1_bss_1679C.mdlId[lbl_1_bss_3C[i].no], lbl_1_bss_1679C.name[lbl_1_bss_3C[i].no], mtx2);
        }
    }
}

/* asm 5955-6020, 62 insns. Unreferenced: keep a copy of player's material colours. */
void fn_1_5860(s16 player)
{
    s16 unused;
    HSFMATERIAL *mat;
    s8 *buf;
    HU3DMODEL *model;
    s16 i;

    unused = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_16A84[player].matColor = HuMemDirectMallocNum(HEAP_HEAP, model->hsf->materialNum*3, HU_MEMNUM_OVL);
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        *buf++ = mat->color[0];
        *buf++ = mat->color[1];
        *buf++ = mat->color[2];
    }
}

/* asm 6023-6119, 92 insns. Unreferenced: scale player's material colours; 1 once the tint is under 40. */
s16 fn_1_5958(s16 player, float scale)
{
    s16 result;
    HU3DMODEL *model;
    HSFMATERIAL *mat;
    s16 i;

    result = 0;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    if((lbl_1_bss_16A84[player].tint *= scale) < 40.0f) {
        result = 1;
    }
    for(i=0, mat=model->hsf->material; i<model->hsf->materialNum; i++, mat++) {
        mat->color[0] *= scale;
        mat->color[1] *= scale;
        mat->color[2] *= scale;
    }
    return result;
}

/* asm 6122-6188, 63 insns. Unreferenced: restore player's material colours from fn_1_5860's copy. */
void fn_1_5AC8(s16 player)
{
    s16 unused;
    HU3DMODEL *model;
    s8 *buf;
    HSFMATERIAL *mat;
    s16 i;

    unused = 0;
    lbl_1_bss_16A84[player].tint = 255.0f;
    model = &Hu3DData[lbl_1_bss_0.player[player]->actor->mdlId];
    buf = lbl_1_bss_16A84[player].matColor;
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
void fn_1_5BC4(void)
{
    lbl_1_bss_16CB4.jingleNo = HuAudJinglePlay(131);
}

/* asm 6207-6220, 12 insns. */
void fn_1_5BF4(void)
{
    lbl_1_bss_16CB4.bgmNo = HuAudBGMPlay(62);
}

/* asm 6223-6252, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_5C24(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_16CB4.bgmNo;
    } else {
        no = lbl_1_bss_16CB4.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 6255-6282, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_5C8C(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_16CB4.bgmNo;
    } else {
        no = lbl_1_bss_16CB4.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 6285-6316, 30 insns. */
void fn_1_5CEC(s16 no)
{
    lbl_1_bss_16CB4.seF[no] = 1;
    lbl_1_bss_16CB4.seNo[no] = HuAudFXPlay(lbl_1_data_59C[no]);
}

/* asm 6319-6354, 34 insns. */
void fn_1_5D64(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_16CB4.seF[no] = 1;
    lbl_1_bss_16CB4.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_59C[no], vol, pan);
}

/* asm 6357-6395, 36 insns. */
void fn_1_5DEC(s16 no, s16 pan)
{
    if(lbl_1_bss_16CB4.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_16CB4.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_16CB4.seNo[no], pan);
    }
}

/* asm 6398-6444, 43 insns. Unreferenced; fn_1_5F28 is the same. */
void fn_1_5E7C(s16 no)
{
    if(lbl_1_bss_16CB4.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_16CB4.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_16CB4.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_16CB4.seNo[no]);
    }
}

/* asm 6447-6493, 43 insns. Unreferenced. */
void fn_1_5F28(s16 no)
{
    if(lbl_1_bss_16CB4.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_16CB4.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_16CB4.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_16CB4.seNo[no]);
    }
}

/* asm 6496-6505, 8 insns. */
void fn_1_5FD4(void)
{
    HuAudAllStop();
}
