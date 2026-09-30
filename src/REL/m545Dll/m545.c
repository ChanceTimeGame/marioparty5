/*
 * m545dll -- a KETTOU duel (overlay #59): the sequence hooks, cameras, light,
 * shadow, the dust particles and the sound helpers. Written from the reference
 * assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m545Dll/asm/REL/m545Dll/m545.s.
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
#include "game/sprite.h"
#include "game/mg/seqman.h"

#include "REL/m545Dll/m545.h"

#include "dolphin/os.h"
#include "dolphin/mtx.h"

#include "math.h"
#include "humath.h"
#include "string.h"

void ObjectSetup(void);
void fn_1_2F0(s16 mode, s16 frameNo);
void fn_1_324(s16 mode, s16 frameNo);
void fn_1_358(s16 mode, s16 frameNo);
void fn_1_380(s16 mode, s16 frameNo);
void fn_1_3B4(s16 mode, s16 frameNo);
void fn_1_3E8(s16 mode, s16 frameNo);
void fn_1_41C(s16 mode, s16 frameNo);
void fn_1_450(s16 mode, s16 frameNo);
void fn_1_478(s16 mode, s16 frameNo);
void fn_1_4A4(OMOBJ *obj);
void fn_1_4A8(s16 no);
void fn_1_E3C(void);
void fn_1_1344(void);
s16 fn_1_1D4C(M545_PARTICLEPARAM *param, float x, float y, float z, float scale);
void fn_1_1F20(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx);

/* --- .data --- */

/* All nine hooks are used. */
MGSEQ_PARAM lbl_1_data_0 = {
    0, 0,
    fn_1_2F0,
    fn_1_324,
    fn_1_358,
    fn_1_380,
    fn_1_3B4,
    fn_1_3E8,
    fn_1_41C,
    fn_1_450,
    fn_1_478
};

/* Five motions per character, in charNo order. */
unsigned int lbl_1_data_28[13][5] = {
    { 0x008C0000, 0x0087005B, 0x0087005D, 0x0087005E, 0x008C0006 },
    { 0x00330000, 0x002E005B, 0x002E005D, 0x002E005E, 0x00330006 },
    { 0x00B70000, 0x00B2005B, 0x00B2005D, 0x00B2005E, 0x00B70006 },
    { 0x00ED0000, 0x00E8005B, 0x00E8005D, 0x00E8005E, 0x00ED0006 },
    { 0x00E60000, 0x00E1005B, 0x00E1005D, 0x00E1005E, 0x00E60006 },
    { 0x00170000, 0x0012005B, 0x0012005D, 0x0012005E, 0x00170006 },
    { 0x00E00000, 0x00DB005B, 0x00DB005D, 0x00DB005E, 0x00E00006 },
    { 0x002D0000, 0x0028005B, 0x0028005D, 0x0028005E, 0x002D0006 },
    { 0x00C90000, 0x00C4005B, 0x00C4005D, 0x00C4005E, 0x00C90006 },
    { 0x00B00000, 0x009C005B, 0x009C005D, 0x009C005E, 0x00B00006 },
    { 0x00B00000, 0x009C005B, 0x009C005D, 0x009C005E, 0x00B00006 },
    { 0x00B00000, 0x009C005B, 0x009C005D, 0x009C005E, 0x00B00006 },
    { 0x00B00000, 0x009C005B, 0x009C005D, 0x009C005E, 0x00B00006 }
};

/* files/data/m545.bin: the blocks, their shadows and the arena (passed to fn_1_77EC). */
unsigned int lbl_1_data_12C[19] = {
    0x0067000C, 0x0067000D, 0x0067000E, 0x0067000F, 0x00670010, 0x00670011, 0x00670012, 0x00670000,
    0x00670001, 0x00670002, 0x00670003, 0x00670004, 0x00670005, 0x00670006, 0x00670007, 0x00670008,
    0x00670009, 0x0067000A, 0x0067000B
};

/* The four cameras fn_1_4A8 can create; only camera 0 is. */
M545_CAMERAINIT lbl_1_data_178[4] = {
    { { 0.0f, 250.0f, 0.0f }, { -20.0f, 0.0f, 500.0f }, 1400.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f },
    { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 500.0f }, 500.0f, 1.33f, 0.0f, 0.0f, 640.0f, 480.0f, 45.0f }
};

s16 lbl_1_data_248[16] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, -32768
};

/* The dust puff fn_1_1980 edits and spawns. */
M545_PARTICLEPARAM lbl_1_data_268 = {
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

/* fn_1_2460's sound effects. */
s16 lbl_1_data_2A0[12] = {
    0x822, 0x823, 0x824, 0x825, 0x826, 0x827, 0x828, 0x829, 0x82A, 0x82B, 0x82C, 0x82D
};

/* --- .bss (CodeWarrior lays it out in reverse definition order) --- */

HU3DMODELID lbl_1_bss_8D4;          /* the dust particle model */
M545_PARTICLEPARAM *lbl_1_bss_8D0;  /* one spawn parameter per particle */
OMOBJMAN *lbl_1_bss_8CC;
M545_WORK lbl_1_bss_67C;
M545_MODEL lbl_1_bss_254[M545_MODEL_MAX];
HU3DMOTID lbl_1_bss_240[10];        /* five motions per duellist */
M545_GAME lbl_1_bss_19C;
M545_STACK lbl_1_bss_C[2];
M545_CAMERA *lbl_1_bss_8;
M545_LIGHT *lbl_1_bss_4;
M545_SHADOW *lbl_1_bss_0;

/* asm 64-172, 148 insns. */
void ObjectSetup(void)
{
    lbl_1_bss_8CC = omInitObjMan(50, 8192);
    omGameSysInit(lbl_1_bss_8CC);
    fn_1_77EC(&lbl_1_bss_67C, lbl_1_bss_254, lbl_1_data_12C);
    lbl_1_bss_8 = HuMemDirectMallocNum(HEAP_HEAP, (sizeof(M545_CAMERA)*4)+8, HU_MEMNUM_OVL);
    memset(lbl_1_bss_8, 0, (sizeof(M545_CAMERA)*4)+8);
    lbl_1_bss_4 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M545_LIGHT), HU_MEMNUM_OVL);
    memset(lbl_1_bss_4, 0, sizeof(M545_LIGHT));
    lbl_1_bss_0 = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M545_SHADOW), HU_MEMNUM_OVL);
    memset(lbl_1_bss_0, 0, sizeof(M545_SHADOW));
    fn_1_4A8(0);
    fn_1_E3C();
    fn_1_1344();
    fn_1_7A38(1);
    fn_1_7CE4(lbl_1_data_28[lbl_1_bss_67C.chr[0].charNo], lbl_1_data_28[lbl_1_bss_67C.chr[1].charNo]);
    fn_1_7D08(lbl_1_bss_240, &lbl_1_bss_240[5]);
    fn_1_7D2C();
    fn_1_8454();
    omAddObjEx(lbl_1_bss_8CC, 32730, 0, 0, -1, fn_1_803C);
    omAddObjEx(lbl_1_bss_8CC, 32730, 0, 0, -1, fn_1_8580);
    omAddObjEx(lbl_1_bss_8CC, 32730, 0, 0, -1, fn_1_4A4);
    omAddObjEx(lbl_1_bss_8CC, 32730, 0, 0, -1, fn_1_88F0);
    Hu3DBGColorSet(186, 245, 255);
    MgSeqCreate(&lbl_1_data_0);
    MgSeqModeDelaySet(2, 2000);
    MgSeqModeDelaySet(7, 180);
    MgSeqModeDelaySet(9, 60);
}

/* asm 175-190, 13 insns. Init hook. */
void fn_1_2F0(s16 mode, s16 frameNo)
{
    if(fn_1_26BC(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 193-208, 13 insns. Fade-in hook. */
void fn_1_324(s16 mode, s16 frameNo)
{
    if(fn_1_2E88(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 211-222, 10 insns. Start hook. */
void fn_1_358(s16 mode, s16 frameNo)
{
    fn_1_2FE8(&lbl_1_bss_67C);
}

/* asm 225-240, 13 insns. Main hook. */
void fn_1_380(s16 mode, s16 frameNo)
{
    if(fn_1_3030(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 243-258, 13 insns. Finish hook. */
void fn_1_3B4(s16 mode, s16 frameNo)
{
    if(fn_1_3480(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 261-276, 13 insns. Pre-winner hook. */
void fn_1_3E8(s16 mode, s16 frameNo)
{
    if(fn_1_34EC(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 279-294, 13 insns. Winner hook. */
void fn_1_41C(s16 mode, s16 frameNo)
{
    if(fn_1_3538(&lbl_1_bss_67C)) {
        MgSeqModeNext();
    }
}

/* asm 297-308, 10 insns. Fade-out hook. */
void fn_1_450(s16 mode, s16 frameNo)
{
    fn_1_3600(&lbl_1_bss_67C);
}

/* asm 311-325, 11 insns. Close hook. */
void fn_1_478(s16 mode, s16 frameNo)
{
    if(fn_1_3638()) {
        MgSeqModeNext();
    }
}

/* asm 328-330, 1 insn. An empty object. */
void fn_1_4A4(OMOBJ *obj)
{
}

/* asm 333-543, 263 insns. Create camera `no` from lbl_1_data_178. */
void fn_1_4A8(s16 no)
{
    lbl_1_bss_8[no].no = no;
    lbl_1_bss_8[no].center.x = lbl_1_data_178[no].center.x;
    lbl_1_bss_8[no].center.y = lbl_1_data_178[no].center.y;
    lbl_1_bss_8[no].center.z = lbl_1_data_178[no].center.z;
    lbl_1_bss_8[no].rot.x = lbl_1_data_178[no].rot.x;
    lbl_1_bss_8[no].rot.y = lbl_1_data_178[no].rot.y;
    lbl_1_bss_8[no].rot.z = lbl_1_data_178[no].rot.z;
    lbl_1_bss_8[no].zoom = lbl_1_data_178[no].zoom;
    lbl_1_bss_8[no].aspect = lbl_1_data_178[no].aspect;
    lbl_1_bss_8[no].vpX = lbl_1_data_178[no].vpX;
    lbl_1_bss_8[no].vpY = lbl_1_data_178[no].vpY;
    lbl_1_bss_8[no].vpW = lbl_1_data_178[no].vpW;
    lbl_1_bss_8[no].vpH = lbl_1_data_178[no].vpH;
    lbl_1_bss_8[no].fov = lbl_1_data_178[no].fov;
    Hu3DCameraCreate(lbl_1_data_248[no]);
    Hu3DCameraViewportSet(lbl_1_data_248[no], lbl_1_bss_8[no].vpX, lbl_1_bss_8[no].vpY, lbl_1_bss_8[no].vpW, lbl_1_bss_8[no].vpH, 0.0f, 1.0f);
    Hu3DCameraPerspectiveSet(lbl_1_data_248[no], lbl_1_bss_8[no].fov, 20.0f, 30000.0f, lbl_1_bss_8[no].aspect);
    fn_1_8C4(no);
}

/* asm 546-793, 350 insns. Camera `no` from its center, rotation and zoom. */
void fn_1_8C4(s16 no)
{
    lbl_1_bss_8[no].pos.x = lbl_1_bss_8[no].center.x+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].pos.y = lbl_1_bss_8[no].center.y+(lbl_1_bss_8[no].zoom*-sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0));
    lbl_1_bss_8[no].pos.z = lbl_1_bss_8[no].center.z+(lbl_1_bss_8[no].zoom*(cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0)));
    lbl_1_bss_8[no].up.x = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*sin((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    lbl_1_bss_8[no].up.y = cos((M_PI*lbl_1_bss_8[no].rot.x)/180.0);
    lbl_1_bss_8[no].up.z = sin((M_PI*lbl_1_bss_8[no].rot.x)/180.0)*cos((M_PI*lbl_1_bss_8[no].rot.y)/180.0);
    Hu3DCameraPosSet(lbl_1_data_248[no], lbl_1_bss_8[no].pos.x, lbl_1_bss_8[no].pos.y, lbl_1_bss_8[no].pos.z,
        lbl_1_bss_8[no].up.x, lbl_1_bss_8[no].up.y, lbl_1_bss_8[no].up.z,
        lbl_1_bss_8[no].center.x, lbl_1_bss_8[no].center.y, lbl_1_bss_8[no].center.z);
}

/* asm 796-875, 140 insns. The global light. */
void fn_1_E3C(void)
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
    fn_1_106C();
    Hu3DGLightStaticSet(lbl_1_bss_4->id, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_4->id);
}

/* asm 878-1001, 182 insns. Place the light from its target, rotation and distance. */
void fn_1_106C(void)
{
    lbl_1_bss_4->pos.x = lbl_1_bss_4->target.x+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*sin((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    lbl_1_bss_4->pos.y = lbl_1_bss_4->target.y+(lbl_1_bss_4->dist*-sin((M_PI*lbl_1_bss_4->rot.x)/180.0));
    lbl_1_bss_4->pos.z = lbl_1_bss_4->target.z+(lbl_1_bss_4->dist*(cos((M_PI*lbl_1_bss_4->rot.x)/180.0)*cos((M_PI*lbl_1_bss_4->rot.y)/180.0)));
    PSVECSubtract(&lbl_1_bss_4->target, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    PSVECNormalize(&lbl_1_bss_4->dir, &lbl_1_bss_4->dir);
    Hu3DGLightPosSetV(lbl_1_bss_4->id, &lbl_1_bss_4->pos, &lbl_1_bss_4->dir);
    Hu3DGLightColorSet(lbl_1_bss_4->id, lbl_1_bss_4->color.r, lbl_1_bss_4->color.g, lbl_1_bss_4->color.b, lbl_1_bss_4->color.a);
}

/* asm 1004-1048, 76 insns. The shadow. */
void fn_1_1344(void)
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
    fn_1_1474();
}

/*
 * asm 1051-1184, 222 insns. Place the shadow camera. Retail leaves the
 * target's z out of pos.z.
 */
void fn_1_1474(void)
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

/* asm 1187-1260, 101 insns. The dust particle model. Retail clears the id sixteen times. */
void fn_1_17EC(void)
{
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;
    s16 j;
    ANIMDATA *anim;

    for(i=0; i<16; i++) {
        lbl_1_bss_8D4 = -1;
    }
    anim = HuSprAnimRead(HuDataSelHeapReadNum(0x670013, HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_8D0 = HuMemDirectMallocNum(HEAP_HEAP, 160*sizeof(M545_PARTICLEPARAM), HU_MEMNUM_OVL);
    lbl_1_bss_8D4 = Hu3DParticleCreate(anim, 160);
    Hu3DParticleHookSet(lbl_1_bss_8D4, fn_1_1F20);
    Hu3DParticleBlendModeSet(lbl_1_bss_8D4, 1);
    Hu3DModelLayerSet(lbl_1_bss_8D4, 4);
    Hu3DModelCameraSet(lbl_1_bss_8D4, 1);
    Hu3DModelAttrSet(lbl_1_bss_8D4, HU3D_ATTR_DISPOFF);
    Hu3DModelAttrReset(lbl_1_bss_8D4, HU3D_ATTR_DISPOFF);
    particle = Hu3DData[lbl_1_bss_8D4].hookData;
    particle->emitCnt = 0;
    particle->work = lbl_1_bss_8D0;
    particle->count = 0;
    for(j=0, data=particle->data; j<particle->maxCnt; j++, data++) {
        data->scale = 0.0f;
    }
}

/* asm 1263-1525, 243 insns. Twelve dust puffs in a ring around pos. */
void fn_1_1980(HuVecF *pos)
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
        size = mul*(6.0+frandmod(6));
        lbl_1_data_268.vel.x = size*sin((M_PI*(30.0f*i))/180.0);
        lbl_1_data_268.vel.y = 0.0f;
        lbl_1_data_268.vel.z = size*cos((M_PI*(30.0f*i))/180.0);
        alpha = -frandmod(6)-7;
        lbl_1_data_268.alphaSpeed = alpha;
        size = mul*(20.0+frandmod(20));
        puffPos.x = pos->x+(mul*(20.0*sin((M_PI*(30.0f*i))/180.0)));
        puffPos.y = pos->y+(10.0f*mul);
        puffPos.z = pos->z+(mul*(20.0*cos((M_PI*(30.0f*i))/180.0)));
        lbl_1_data_268.accelY = 0.01*frandmod(20);
        fn_1_1D4C(&lbl_1_data_268, puffPos.x, puffPos.y, puffPos.z, size);
    }
}

/* asm 1528-1662, 117 insns. Spawn one particle; the slot, or -1 when all are live. */
s16 fn_1_1D4C(M545_PARTICLEPARAM *param, float x, float y, float z, float scale)
{
    s16 result;
    HU3DMODEL *model;
    M545_PARTICLEPARAM *work;
    HU3DPARTICLE *particle;
    HU3DPARTICLEDATA *data;
    s16 i;

    result = -1;
    model = &Hu3DData[lbl_1_bss_8D4];
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

/* asm 1665-1937, 262 insns. The particle hook: move, fade and shrink every live puff. */
void fn_1_1F20(HU3DMODEL *model, HU3DPARTICLE *particle, Mtx mtx)
{
    M545_PARTICLEPARAM *param;
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

/* asm 1940-1952, 12 insns. */
void fn_1_2338(void)
{
    lbl_1_bss_19C.jingleNo = HuAudJinglePlay(131);
}

/* asm 1955-1967, 12 insns. */
void fn_1_2368(void)
{
    lbl_1_bss_19C.bgmNo = HuAudBGMPlay(59);
}

/* asm 1970-1997, 26 insns. Fade out the music (bgmF) or the jingle. */
void fn_1_2398(s16 bgmF, s16 speed)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_19C.bgmNo;
    } else {
        no = lbl_1_bss_19C.jingleNo;
    }
    HuAudSStreamFadeOut(no, speed);
}

/* asm 2000-2025, 24 insns. Stop the music (bgmF) or the jingle. */
void fn_1_2400(s16 bgmF)
{
    s16 no;

    if(bgmF) {
        no = lbl_1_bss_19C.bgmNo;
    } else {
        no = lbl_1_bss_19C.jingleNo;
    }
    HuAudSStreamStop(no);
}

/* asm 2028-2059, 30 insns. */
void fn_1_2460(s16 no)
{
    lbl_1_bss_19C.seF[no] = 1;
    lbl_1_bss_19C.seNo[no] = HuAudFXPlay(lbl_1_data_2A0[no]);
}

/* asm 2062-2097, 34 insns. */
void fn_1_24D8(s16 no, s16 vol, s16 pan)
{
    lbl_1_bss_19C.seF[no] = 1;
    lbl_1_bss_19C.seNo[no] = HuAudFXPlayVolPan(lbl_1_data_2A0[no], vol, pan);
}

/* asm 2100-2137, 36 insns. */
void fn_1_2560(s16 no, s16 pan)
{
    if(lbl_1_bss_19C.seF[no] == 1 && HuAudFXStatusGet(lbl_1_bss_19C.seNo[no]) == 2) {
        HuAudFXPanning(lbl_1_bss_19C.seNo[no], pan);
    }
}

/* asm 2140-2184, 43 insns. */
void fn_1_25F0(s16 no)
{
    if(lbl_1_bss_19C.seF[no] == 1 && (HuAudFXStatusGet(lbl_1_bss_19C.seNo[no]) == 2 || HuAudFXStatusGet(lbl_1_bss_19C.seNo[no]) == 3)) {
        HuAudFXStop(lbl_1_bss_19C.seNo[no]);
    }
}

/* asm 2187-2195, 8 insns. */
void fn_1_269C(void)
{
    HuAudAllStop();
}
