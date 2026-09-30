/*
 * m561dll -- a Bowser minigame (MG_TYPE_KUPA, overlay #72). Written from the
 * reference assembly, functions in reference order; line ranges are into
 * build/mp5-asm/m561dll/asm/REL/m561dll/m561.s.
 *
 * Shape: seqman + own OMOBJ groups, one TU plus effect.c, assembled like
 * m559dll from m560dll's parts:
 *
 *  - fn_1_6210..fn_1_70F4 are m563's math.c helper block, instruction-identical;
 *    included below with its names mapped to this overlay's addresses.
 *  - fn_1_7568..fn_1_8A18 are m560.c's billboard library (bill.c, ported from
 *    m559dll's copy); fn_1_71B8 is this overlay's own part update.
 *
 * CodeWarrior emits this file's own functions first, then those of its
 * #included files in include order, which is the reference order.
 *
 * _prolog and _epilog are not reproduced.
 */


#include "game/hu3d.h"
#include "game/sprite.h"
#include "dolphin/mtx.h"
#include "humath.h"
#include "string.h"

/* m560dll's billboard system, renamed (see m560.c for the field notes). */
typedef struct M561Bill_s M561_BILL;
typedef void (*M561BILLFUNC)(HU3DMODEL *modelP, M561_BILL *work, Mtx mtx);

typedef struct M561BillPart_s {
    /* 0x00 */ int unk00;
    /* 0x04 */ HuVecF basePos;
    /* 0x10 */ float time;
    /* 0x14 */ float angle;
    /* 0x18 */ float angleOfs;
    /* 0x1C */ float timeAdd;
    /* 0x20 */ float timeMax;
    /* 0x24 */ float posYTarget;
    /* 0x28 */ float zRot;
    /* 0x2C */ float scale;
    /* 0x30 */ HuVecF pos;
    /* 0x3C */ s16 cellNo;
    /* 0x3E */ s16 no;
} M561_BILLPART;

struct M561Bill_s {
    /* 0x00 */ M561BILLFUNC func;
    /* 0x04 */ ANIMDATA *anim;
    /* 0x08 */ HuVecF *posSrc;
    /* 0x0C */ float *angleSrc;
    /* 0x10 */ M561_BILLPART *part;
    /* 0x14 */ HuVecF *vtx;
    /* 0x18 */ HuVec2f *st;
    /* 0x1C */ HuVec2f *cellTbl;
    /* 0x20 */ GXColor *color;
    /* 0x24 */ void *dlBuf;
    /* 0x28 */ HuVecF quad[4];
    /* 0x58 */ u32 dlSize;
    /* 0x5C */ float cellSizeX;
    /* 0x60 */ float cellSizeY;
    /* 0x64 */ s16 maxCnt;
    /* 0x66 */ s16 liveCnt;
    /* 0x68 */ s16 cellNum;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 killF;
};

static void fn_1_71B8(HU3DMODEL *modelP, M561_BILL *work, Mtx mtx);
static void fn_1_7568(Mtx src, Mtx dst);
static void fn_1_75E4(HuVecF *src, HuVecF *dst, float scale, s16 count);
static void fn_1_7640(HuVec2f *st, HuVec2f *cellTbl, s16 cell, float width, float height);
static void fn_1_76E4(HU3DMODEL *modelP, Mtx *mtx);
static void fn_1_7E2C(HuVec2f *st, s16 count, s16 cellX, float w, float h);
static HU3DMODELID fn_1_7EF8(ANIMDATA *anim, HuVecF *posSrc, float *angleSrc, s16 maxCnt, float size, s16 cellW, s16 cellH);
static M561_BILLPART *fn_1_8550(HU3DMODELID modelId, HuVecF *pos, GXColor *color, float scale, float zRot);
static void fn_1_8658(HU3DMODELID modelId, M561BILLFUNC func);
static void fn_1_8690(HU3DMODELID modelId, u8 value);
static void fn_1_86C0(HU3DMODELID modelId);
static BOOL fn_1_86FC(HU3DMODELID modelId);
static void fn_1_87B8(HU3DMODELID modelId, s16 count, HuVecF *pos, float angle, float timeMax, float posYTarget);
static HU3DMODELID fn_1_8A18(HuVecF *posSrc, float *angleSrc, s16 maxCnt);


/* math.c's helpers carry m563's addresses; this overlay's copies sit here. */
#define fn_1_66D4 fn_1_6210
#define fn_1_66F8 fn_1_6234
#define fn_1_6780 fn_1_62BC
#define fn_1_6824 fn_1_6360
#define fn_1_687C fn_1_63B8
#define fn_1_6990 fn_1_64CC
#define fn_1_6AEC fn_1_6628
#define fn_1_6B78 fn_1_66B4
#define fn_1_6EAC fn_1_69E8
#define fn_1_7290 fn_1_6DCC
#define fn_1_7394 fn_1_6ED0
#define fn_1_7400 fn_1_6F3C
#define fn_1_7458 fn_1_6F94
#define fn_1_7494 fn_1_6FD0
#define fn_1_74F4 fn_1_7030
#define fn_1_75B8 fn_1_70F4
#include "REL/m563dll/math.c"
#include "REL/m561dll/bill.c"


#include "game/audio.h"
#include "game/charman.h"
#include "game/data.h"
#include "game/memory.h"
#include "game/flag.h"
#include "game/frand.h"
#include "game/gamework.h"
#include "game/hsfformat.h"
#include "game/mg/seqman.h"
#include "game/mg/timer.h"
#include "game/object.h"
#include "game/pad.h"
#include "game/printfunc.h"
#include "game/process.h"
#include "game/sprite.h"

#include "datadir_enum.h"

#include "dolphin/gx.h"
#include "dolphin/mtx.h"

#include "REL/m561dll/m561.h"

/* One timed camera key (lbl_1_data_6C: four paths of seven; lbl_1_data_29C: two). */
typedef struct M561CameraKey_s {
    /* 0x00 */ s32 time;
    /* 0x04 */ HuVecF pos;
    /* 0x10 */ float rot;
} M561_CAMERAKEY;

void ObjectSetup(void);
void fn_1_58C(OMOBJ *obj);
void fn_1_8C8(OMOBJ *obj);
void fn_1_1C8C(void);
void fn_1_1D10(void);
s32 fn_1_1DB4(M561_PLAYER *work);
void fn_1_1E28(s16 mode, s16 frameNo);
void fn_1_23BC(s16 mode, s16 frameNo);
void fn_1_2514(s16 mode, s16 frameNo);
void fn_1_2860(s16 mode, s16 frameNo);
void fn_1_289C(s16 mode, s16 frameNo);
void fn_1_298C(s16 mode, s16 frameNo);
void fn_1_2B50(OMOBJ *obj, s32 motNo, float shift, u32 attr);
void fn_1_2BDC(OMOBJ *obj, s32 motNo);
void fn_1_2C4C(OMOBJ *obj);
void fn_1_2F2C(OMOBJ *obj);
void fn_1_3210(void);
void fn_1_3214(void);
void fn_1_35D4(OMOBJ *obj);
void fn_1_38EC(OMOBJ *obj);
void fn_1_5394(OMOBJ *obj, s32 motNo, float shift, u32 attr);
s32 fn_1_5428(void);
float fn_1_54BC(s32 from, s32 to, s32 time);
void fn_1_55E0(s32 side);
void fn_1_5684(void);
float fn_1_5918(float ax, float az, float bx, float bz);
s32 fn_1_5A88(void);
s32 fn_1_5B20(void);
s32 fn_1_5BB8(M561_PLAYER *self);
float fn_1_5C48(float from, float to, s32 time);
void fn_1_5D58(void);
void fn_1_5D6C(void);
void fn_1_5D9C(void);
void fn_1_5DCC(u16 time, float amp, float decay, float freq, u16 flag);
void fn_1_5E28(void);
s16 fn_1_6078(HuVecF *pos);
s16 fn_1_60F4(HuVecF *pos);
s16 fn_1_6170(void);
void fn_1_61DC(HU3DMODELID modelId, HU3DMOTID motId, BOOL lagF);

/* --- .data --- */

HuVecF lbl_1_data_0 = { 0.0f, 10000.0f, 10000.0f };
HuVecF lbl_1_data_C = { 0.0f, 0.0f, 0.0f };
GXColor lbl_1_data_18 = { 255, 255, 255, 255 };
s32 lbl_1_data_1C = -1;
s32 lbl_1_data_20 = -1;

/* Character motions. */
u32 lbl_1_data_24[9] = { 0x008C0000, 0x008C0019, 0x008C0086, 0x008C0031, 0x008C0002, 0x008C002C, 0x008C0003, 0x008C0004, 0x008C0015 };

u32 lbl_1_data_48[9] = {
    DATANUM(DATA_m561, 0x01), DATANUM(DATA_m561, 0x02), DATANUM(DATA_m561, 0x03), DATANUM(DATA_m561, 0x04), DATANUM(DATA_m561, 0x05),
    DATANUM(DATA_m561, 0x06), DATANUM(DATA_m561, 0x07), DATANUM(DATA_m561, 0x08), DATANUM(DATA_m561, 0x09)
};

M561_CAMERAKEY lbl_1_data_6C[4][7] = {
    { { 70, { -80.0f, 0.0f, -2420.0f }, 0.0f }, { 230, { -60.0f, 0.0f, -1345.0f }, 1.0f }, { 270, { -58.0f, 0.0f, -1077.0f }, 3.8f }, { 285, { -68.0f, 0.0f, -978.0f }, -14.8f }, { 300, { -150.0f, 0.0f, -920.0f }, -50.0f }, { 315, { -239.0f, 0.0f, -875.0f }, -32.2f }, { 330, { -300.0f, 0.0f, -800.0f }, 0.0f } },
    { { 70, { -80.0f, 0.0f, -2630.0f }, 0.0f }, { 230, { -56.0f, 0.0f, -1622.0f }, 4.3f }, { 280, { -12.0f, 0.0f, -1310.0f }, 10.7f }, { 310, { 12.0f, 0.0f, -1123.0f }, 0.0f }, { 325, { 0.0f, 0.0f, -1030.0f }, -7.4f }, { 345, { -52.0f, 0.0f, -915.0f }, -1.2f }, { 365, { -100.0f, 0.0f, -830.0f }, 0.0f } },
    { { 70, { 80.0f, 0.0f, -2530.0f }, 0.0f }, { 210, { 73.0f, 0.0f, -1626.0f }, -5.0f }, { 260, { 46.0f, 0.0f, -1304.0f }, -6.5f }, { 295, { 26.0f, 0.0f, -1079.0f }, 0.0f }, { 310, { 44.0f, 0.0f, -985.0f }, 13.2f }, { 325, { 77.0f, 0.0f, -993.0f }, 10.5f }, { 340, { 100.0f, 0.0f, -830.0f }, 0.0f } },
    { { 70, { 80.0f, 0.0f, -2330.0f }, 0.0f }, { 240, { 47.0f, 0.0f, -1212.0f }, -5.0f }, { 260, { 58.0f, 0.0f, -1081.0f }, -2.4f }, { 275, { 88.0f, 0.0f, -989.0f }, 31.0f }, { 290, { 161.0f, 0.0f, -924.0f }, 56.5f }, { 305, { 248.0f, 0.0f, -878.0f }, 36.5f }, { 320, { 300.0f, 0.0f, -800.0f }, 0.0f } }
};
M561_CAMERAKEY lbl_1_data_29C[2] = { { 80, { 0.0f, 0.0f, -3000.0f }, 0.0f }, { 370, { 0.0f, 0.0f, -1800.0f }, 0.0f } };

float lbl_1_data_2C4[3] = { -45.0f, 0.0f, 45.0f };

OMCAMERAVIEW lbl_1_data_2D0 = { { 0.0f, 241.9f, -130.0f }, { -14.8f, 0.0f, 0.0f }, 2481.0f };

HuVecF lbl_1_data_2EC[8] = {
    { -80.0f, 0.0f, -2420.0f }, { -80.0f, 0.0f, -2630.0f }, { 80.0f, 0.0f, -2530.0f }, { 80.0f, 0.0f, -2330.0f },
    { -300.0f, 0.0f, -800.0f }, { -100.0f, 0.0f, -800.0f }, { 100.0f, 0.0f, -800.0f }, { 300.0f, 0.0f, -800.0f }
};

HuVecF lbl_1_data_34C = { 0.0f, 0.0f, -3000.0f };
HuVecF lbl_1_data_358 = { 0.0f, 0.0f, -1440.0f };
HuVecF lbl_1_data_364 = { 1.0f, 10000.0f, 0.0f };
HuVecF lbl_1_data_370 = { 0.0f, 1.0f, 0.0f };
HuVecF lbl_1_data_37C = { 0.0f, 0.0f, 0.0f };
HuVecF lbl_1_data_388[3] = { { -450.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 450.0f, 0.0f, 0.0f } };

HuVecF lbl_1_data_3AC[4][4] = {
    { { 0.0f, 0.0f, 300.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -75.0f, 0.0f, 300.0f }, { 75.0f, 0.0f, 300.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -175.0f, 0.0f, 300.0f }, { 0.0f, 0.0f, 300.0f }, { 175.0f, 0.0f, 300.0f }, { 0.0f, 0.0f, 0.0f } },
    { { -250.0f, 0.0f, 300.0f }, { -75.0f, 0.0f, 300.0f }, { 75.0f, 0.0f, 300.0f }, { 250.0f, 0.0f, 300.0f } }
};

s32 lbl_1_data_46C[3] = { 512, 256, 1024 };

MGSEQ_PARAM lbl_1_data_478 = {
    0, 0,
    fn_1_1E28,
    fn_1_23BC,
    NULL,
    fn_1_2514,
    fn_1_2860,
    fn_1_289C,
    fn_1_298C,
    NULL,
    NULL
};

/* --- .bss (CodeWarrior lays it out in reverse definition order; math.c owns bss_CC..bss_2D4 but for bss_2D0) --- */

OMOBJMAN *lbl_1_bss_2D0;
OMOBJ **lbl_1_bss_C8;              /* group 0: players */
OMOBJ **lbl_1_bss_C4;              /* group 1: Bowser */
s16 lbl_1_bss_A6[15];
s16 lbl_1_bss_A4;
s32 lbl_1_bss_9C[2];               /* unreferenced; dtk sizes lbl_1_bss_98 0xC */
MGTIMER *lbl_1_bss_98;
s32 lbl_1_bss_94;
s16 lbl_1_bss_92;
s16 lbl_1_bss_90;
float lbl_1_bss_8C;
s32 lbl_1_bss_88;
HuVecF lbl_1_bss_7C;
HuVecF lbl_1_bss_70;
HuVecF lbl_1_bss_64;
HuVecF lbl_1_bss_58;
HuVecF lbl_1_bss_4C;
HuVecF lbl_1_bss_40;
s32 lbl_1_bss_3C;
float lbl_1_bss_38;
float lbl_1_bss_34;
float lbl_1_bss_30;
float lbl_1_bss_2C;
float lbl_1_bss_28;
float lbl_1_bss_24;
u16 lbl_1_bss_20;
ANIMDATA *lbl_1_bss_1C;
s32 lbl_1_bss_10[3];
s32 lbl_1_bss_4[3];
s32 lbl_1_bss_0;

/* asm 61-379, 315 insns. */
void ObjectSetup(void)
{
    s32 i;
    OMOBJ *obj;

    OSReport("******* M561 ObjectSetup *********\n");
    lbl_1_bss_2D0 = omInitObjMan(200, 0x2000);
    omGameSysInit(lbl_1_bss_2D0);
    lbl_1_bss_92 = Hu3DMotionCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x18), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_90 = Hu3DModelCameraCreate(lbl_1_bss_92, 1);
    HuPrcVSleep();
    lbl_1_bss_8C = Hu3DMotionMotionMaxTimeGet(lbl_1_bss_92);
    Hu3DCameraPosGet(1, &lbl_1_bss_7C, &lbl_1_bss_70, &lbl_1_bss_64);
    HuPrcVSleep();
    Hu3DModelKill(lbl_1_bss_90);
    HuPrcVSleep();
    Hu3DCameraCreate(1);
    Hu3DCameraPerspectiveSet(1, 30.0f, 20.0f, 15000.0f, 1.2f);
    Hu3DCameraViewportSet(1, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    Hu3DCameraPosSetV(1, &lbl_1_bss_7C, &lbl_1_bss_70, &lbl_1_bss_64);
    lbl_1_bss_3C = 0;
    lbl_1_bss_38 = 0.0f;
    lbl_1_bss_A4 = Hu3DGLightCreate(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0, 0, 0);
    Hu3DGLightPosAimSetV(lbl_1_bss_A4, &lbl_1_data_0, &lbl_1_data_C);
    Hu3DGLightStaticSet(lbl_1_bss_A4, 1);
    Hu3DGLightInfinitytSet(lbl_1_bss_A4);
    Hu3DGLightColorSet(lbl_1_bss_A4, lbl_1_data_18.r, lbl_1_data_18.g, lbl_1_data_18.b, lbl_1_data_18.a);
    Hu3DShadowCreate(30.0f, 10.0f, 10000.0f);
    Hu3DShadowPosSet(&lbl_1_data_364, &lbl_1_data_370, &lbl_1_data_37C);
    Hu3DShadowTPLvlSet(0.5f);
    omMakeGroupEx(lbl_1_bss_2D0, 0, 4);
    lbl_1_bss_C8 = omGetGroupMemberListEx(lbl_1_bss_2D0, 0);
    for(i=0; i<4; i++) {
        obj = omAddObjEx(lbl_1_bss_2D0, 100, 1, 9, 0, fn_1_58C);
        lbl_1_bss_C8[i] = obj;
        obj->data = HuMemDirectMallocNum(HEAP_HEAP, sizeof(M561_PLAYER), HU_MEMNUM_OVL);
        obj->work[0] = i;
    }
    omMakeGroupEx(lbl_1_bss_2D0, 1, 1);
    lbl_1_bss_C4 = omGetGroupMemberListEx(lbl_1_bss_2D0, 1);
    obj = omAddObjEx(lbl_1_bss_2D0, 101, 1, 9, 1, fn_1_35D4);
    lbl_1_bss_C4[0] = obj;
    obj->data = HuMemDirectMallocNum(HEAP_HEAP, 0x60, HU_MEMNUM_OVL);
    lbl_1_bss_10[0] = lbl_1_bss_10[1] = lbl_1_bss_10[2] = 0;
    lbl_1_bss_4[0] = lbl_1_bss_4[1] = lbl_1_bss_4[2] = 0;
    lbl_1_bss_1C = HuSprAnimRead(HuDataReadNum(DATANUM(DATA_m561, 0x19), HU_MEMNUM_OVL));
    HuSprAnimLock(lbl_1_bss_1C);
    lbl_1_bss_0 = -1;
    fn_1_5D58();
    fn_1_8AE8();
    fn_1_9464();
    MgSeqCreatePrio(&lbl_1_data_478, 1000);
}

/* asm 382-598, 207 insns. Player object init. */
void fn_1_58C(OMOBJ *obj)
{
    M561_PLAYER *work;
    s32 i;
    s32 wait0;
    s32 wait1;
    s32 wait2;
    s32 wait3;

    work = obj->data;
    work->no = obj->work[0];
    work->charNo = GwPlayerConf[work->no].charNo;
    work->padNo = GwPlayerConf[work->no].padNo;
    work->mode = 1;
    work->timer = 0;
    work->unk7C = 0;
    work->unk5C = 0.0f;
    work->unk94 = 0;
    work->unk80 = 0;
    work->unk84 = 0;
    work->unk58 = 0.0f;
    work->unk98 = 0;
    work->unk9C = 0.0f;
    work->unkA8 = 0.0f;
    obj->mdlId[0] = CharModelCreate(work->charNo, 2);
    CharEffectLayerSet(6);
    for(i=0; i<9; i++) {
        obj->mtnId[i] = CharMotionCreate(work->charNo, lbl_1_data_24[i]);
        CharMotionSet(work->charNo, obj->mtnId[i]);
    }
    work->motNo = 5;
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_LOOP);
    Hu3DMotionSet(obj->mdlId[0], obj->mtnId[5]);
    Hu3DModelShadowSet(obj->mdlId[0]);
    work->dif = GwPlayerConf[work->no].dif;
    switch(work->dif) {
        case 0:
            wait0 = frandmod(90)+90;
            work->unk90 = wait0;
            break;
        case 1:
            wait1 = frandmod(60)+60;
            work->unk90 = wait1;
            break;
        case 2:
            wait2 = frandmod(45)+45;
            work->unk90 = wait2;
            break;
        case 3:
            wait3 = frandmod(30)+30;
            work->unk90 = wait3;
            break;
    }
    work->rot.x = work->rot.y = work->rot.z = 0.0f;
    work->pos.x = lbl_1_data_2EC[work->no].x;
    work->pos.y = lbl_1_data_2EC[work->no].y;
    work->pos.z = lbl_1_data_2EC[work->no].z;
    work->unk40 = work->pos;
    work->scale = 1.0f;
    omSetSca(obj, work->scale, work->scale, work->scale);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
    Hu3DModelAttrReset(obj->mdlId[0], HU3D_ATTR_DISPOFF);
    CharMotionDataClose(work->charNo);
    obj->objFunc = fn_1_8C8;
}

/* asm 601-1905, 1265 insns. Player object main. */
void fn_1_8C8(OMOBJ *obj)
{
    M561_PLAYER *work;
    float dx;
    float dy;
    float dz;
    float dist;
    s32 vol;
    HuVecF target;
    HuVecF pos;
    BOOL hitF;

    work = obj->data;
    if(lbl_1_bss_94) {
        if(GwPlayerConf[work->no].type) {
            work->btn = fn_1_1DB4(work);
        } else {
            work->btn = HuPadBtnDown[work->padNo];
        }
    }
    if(work->mode == 0) {
        Hu3DCameraPosGet(1, &lbl_1_bss_58, &lbl_1_bss_4C, &lbl_1_bss_40);
        dx = work->pos.x-lbl_1_bss_58.x;
        dy = work->pos.y-lbl_1_bss_58.y;
        dz = work->pos.z-lbl_1_bss_58.z;
        dist = sqrtf(dz*dz+((dx*dx)+(dy*dy)));
        vol = 127.0*(fabs(6000.0f-dist)/6000.0);
        CharModelVoiceVolSet(work->charNo, vol);
    } else {
        CharModelVoicePanSet(work->charNo, fn_1_7030(&work->pos, 32, 96));
        CharModelVoiceVolSet(work->charNo, 127);
    }
    switch(work->mode) {
        case 0:
            work->unk64.x = (lbl_1_data_6C[work->no][work->unk98].pos.x-work->pos.x)/(lbl_1_data_6C[work->no][work->unk98].time-work->unk9C);
            work->unk64.y = (lbl_1_data_6C[work->no][work->unk98].pos.y-work->pos.y)/(lbl_1_data_6C[work->no][work->unk98].time-work->unk9C);
            work->unk64.z = (lbl_1_data_6C[work->no][work->unk98].pos.z-work->pos.z)/(lbl_1_data_6C[work->no][work->unk98].time-work->unk9C);
            work->pos.x += work->unk64.x;
            work->pos.y += work->unk64.y;
            work->pos.z += work->unk64.z;
            work->rot.y += work->unkA8;
            work->unk9C += 1.0f;
            if(work->unk9C >= lbl_1_data_6C[work->no][work->unk98].time) {
                work->unk98++;
                work->rot.y = lbl_1_data_6C[work->no][work->unk98-1].rot;
                work->unkA8 = fn_1_5C48(lbl_1_data_6C[work->no][work->unk98-1].rot, lbl_1_data_6C[work->no][work->unk98].rot, lbl_1_data_6C[work->no][work->unk98].time-lbl_1_data_6C[work->no][work->unk98-1].time);
                if(work->unk98 > 7) {
                    work->mode = 1;
                    work->unk64.x = work->unk64.y = work->unk64.z = 0.0f;
                    work->rot.y = 0.0f;
                    work->unkA8 = 0.0f;
                    work->pos.x = lbl_1_data_6C[work->no][6].pos.x;
                    work->pos.y = lbl_1_data_6C[work->no][6].pos.y;
                    work->pos.z = lbl_1_data_6C[work->no][6].pos.z;
                    fn_1_2B50(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
                }
            }
            break;

        case 2:
            if(work->btn & PAD_BUTTON_A) {
                work->unk7C = 1;
                work->unk3C = &lbl_1_data_388[1];
                work->mode = 3;
                work->unk80 = 1;
            }
            if(work->btn & PAD_BUTTON_B) {
                work->unk7C = 0;
                work->unk3C = &lbl_1_data_388[0];
                work->mode = 3;
                work->unk80 = 1;
            }
            if(work->btn & PAD_BUTTON_X) {
                work->unk7C = 2;
                work->unk3C = &lbl_1_data_388[2];
                work->mode = 3;
                work->unk80 = 1;
            }
            break;

        case 3:
            fn_1_2B50(obj, 4, 8.0f, HU3D_MOTATTR_LOOP);
            work->unk40 = work->pos;
            work->unk64.x = work->unk3C->x-work->pos.x;
            work->unk64.y = 0.0f;
            work->unk64.z = work->unk3C->z-work->pos.z;
            PSVECNormalize(&work->unk64, &work->unk64);
            work->rot.y = 180.0*(atan2(work->unk64.x, work->unk64.z)/M_PI);
            work->unk70.x = 10.0*sin((M_PI*work->rot.y)/180.0);
            work->unk70.y = 0.0f;
            work->unk70.z = 10.0*cos((M_PI*work->rot.y)/180.0);
            PSVECAdd(&work->pos, &work->unk70, &work->pos);
            fn_1_2C4C(obj);
            fn_1_2F2C(obj);
            target.x = work->unk3C->x;
            target.y = work->unk3C->y;
            target.z = work->unk3C->z;
            pos.x = work->pos.x;
            pos.y = work->pos.y;
            pos.z = work->pos.z;
            if(((pos.x-target.x)*(pos.x-target.x))+((pos.z-target.z)*(pos.z-target.z)) < 108900.0f) {
                hitF = TRUE;
            } else {
                hitF = FALSE;
            }
            if(hitF) {
                work->mode = 4;
                fn_1_2B50(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            }
            break;

        case 6:
            if(work->timer > 5) {
                work->mode = 3;
                work->timer = 0;
            } else {
                work->timer++;
            }
            break;

        case 4:
            if(fn_1_5BB8(work)) {
                work->mode = 5;
                work->unk58 = work->pos.y;
                work->unk60 = fn_1_5918(work->pos.x, work->pos.z, lbl_1_data_388[work->unk7C].x, lbl_1_data_388[work->unk7C].z);
            }
            break;

        case 5:
            if(work->timer > 60.0f) {
                work->timer = 0;
                work->mode = 7;
            } else if(work->timer == 0 && !fn_1_5BB8(work)) {
                work->mode = 4;
            } else {
                fn_1_2B50(obj, 6, 8.0f, 0);
                work->pos.y = work->unk58+(550.0*sin((M_PI*work->unk5C)/180.0));
                work->pos.x = work->pos.x+((work->unk60*sin((M_PI*work->rot.y)/180.0))/60.0);
                work->pos.z = work->pos.z+((work->unk60*cos((M_PI*work->rot.y)/180.0))/60.0);
                work->unk5C += 3.0f;
                work->timer++;
            }
            break;

        case 7:
            work->pos.x = lbl_1_data_388[work->unk7C].x;
            work->pos.y = lbl_1_data_388[work->unk7C].y;
            work->pos.z = lbl_1_data_388[work->unk7C].z;
            work->rot.y = 0.0f;
            work->scale = 1.0f;
            fn_1_2BDC(obj, 0);
            break;

        case 8:
            if(work->unkA0 > work->unkA4) {
                work->mode = 9;
                omVibrate(work->no, 30, 12, 0);
                CharFXPlayPan(work->charNo, 505, fn_1_7030(&work->pos, 32, 96));
            } else {
                work->unkA0++;
            }
            break;

        case 9:
            fn_1_2B50(obj, 8, 8.0f, 0);
            if(work->timer > 45.0f) {
                work->timer = 0;
                work->mode = 7;
            } else {
                work->pos.y = work->unk58+(500.0*sin((M_PI*work->unk5C)/180.0));
                work->unk5C += 4.0f;
                work->timer++;
            }
            break;

        case 10:
            if(work->unkA0 > work->unkA4) {
                work->mode = 11;
                fn_1_2B50(obj, 6, 8.0f, 0);
            } else {
                work->unkA0++;
            }
            break;

        case 11:
            if(work->timer > 60.0f) {
                work->timer = 0;
                work->mode = 13;
                fn_1_2B50(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                if(55.0f == work->timer) {
                    fn_1_2B50(obj, 7, 8.0f, 0);
                }
                work->pos.y = work->unk58+(400.0*sin((M_PI*work->unk5C)/180.0));
                if(work->unk5C >= 0.0f && work->unk5C < 90.0f) {
                    if(work->pos.y > 200.0f) {
                        work->pos.x = work->pos.x+(1.25*((work->unk60*sin((M_PI*work->rot.y)/180.0))/60.0));
                        work->pos.z = work->pos.z+(1.25*((work->unk60*cos((M_PI*work->rot.y)/180.0))/60.0));
                    }
                } else if(work->unk5C >= 90.0f && work->unk5C < 180.0f) {
                    work->pos.x = work->pos.x+(1.25*((work->unk60*sin((M_PI*work->rot.y)/180.0))/60.0));
                    work->pos.z = work->pos.z+(1.25*((work->unk60*cos((M_PI*work->rot.y)/180.0))/60.0));
                }
                work->unk5C += 3.0f;
                work->timer++;
            }
            break;

        case 12:
            fn_1_2B50(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer > 15) {
                fn_1_2B50(obj, 2, 8.0f, 0);
                work->timer = 0;
                work->mode = 13;
            } else {
                work->timer++;
            }
            break;

        case 13:
            work->rot.y = fn_1_6DCC(work->rot.y, 0.0f, 0.4f);
            break;
    }
    omSetSca(obj, work->scale, work->scale, work->scale);
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

/* asm 1908-1945, 33 insns. */
void fn_1_1C8C(void)
{
    M561_PLAYER *work;
    s32 i;

    for(i=0; i<4; i++) {
        work = lbl_1_bss_C8[i]->data;
        if(work->unk80 == 0) {
            work->btn = lbl_1_data_46C[frandmod(3)];
        }
    }
}

/* asm 1948-1995, 41 insns. Wait for every player to reach mode 7. */
void fn_1_1D10(void)
{
    M561_PLAYER *work[4];
    s32 i;

    for(i=0; i<4; i++) {
        work[i] = lbl_1_bss_C8[i]->data;
    }
    while(1) {
        if(work[0]->mode == 7 && work[1]->mode == 7 && work[2]->mode == 7 && work[3]->mode == 7) {
            break;
        }
        HuPrcVSleep();
    }
}

/* asm 1998-2030, 29 insns. A computer player's button. */
s32 fn_1_1DB4(M561_PLAYER *work)
{
    s32 btn;

    if(work->unk94 > work->unk90) {
        btn = lbl_1_data_46C[frandmod(3)];
    } else {
        work->unk94++;
        btn = 0;
    }
    return btn;
}

/* asm 2033-2395, 357 insns. MGSEQ init hook: the stage models, the timer and the opening camera. */
void fn_1_1E28(s16 mode, s16 frameNo)
{
    M561_PLAYER *work;
    M561_KUPA *kupa;
    s32 i;

    lbl_1_bss_A6[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0A), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelShadowMapSet(lbl_1_bss_A6[0]);
    lbl_1_bss_A6[3] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x14), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[4] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x15), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[5] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x16), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[6] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x17), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DMotionTimingHookSet(lbl_1_bss_A6[4], fn_1_61DC);
    Hu3DModelAttrSet(lbl_1_bss_A6[3], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_A6[4], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_A6[5], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_A6[6], HU3D_MOTATTR_PAUSE);
    Hu3DModelAttrSet(lbl_1_bss_A6[4], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_A6[5], HU3D_ATTR_DISPOFF);
    Hu3DModelAttrSet(lbl_1_bss_A6[6], HU3D_ATTR_DISPOFF);
    lbl_1_bss_A6[1] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0B), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[7] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0D), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_A6[7], HU3D_MOTATTR_LOOP);
    lbl_1_bss_A6[2] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0C), HU_MEMNUM_OVL, HEAP_MODEL));
    Hu3DModelAttrSet(lbl_1_bss_A6[2], HU3D_MOTATTR_LOOP);
    lbl_1_bss_A6[8] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0F), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[9] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x0E), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[10] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x10), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[11] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[12] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    lbl_1_bss_A6[13] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x11), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i=0; i<3; i++) {
        Hu3DModelPosSet(lbl_1_bss_A6[i+8], lbl_1_data_388[i].x, lbl_1_data_388[i].y, lbl_1_data_388[i].z);
        Hu3DModelAttrSet(lbl_1_bss_A6[i+8], HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(lbl_1_bss_A6[i+8], 0.0f);
        Hu3DModelPosSet(lbl_1_bss_A6[i+11], lbl_1_data_388[i].x, lbl_1_data_388[i].y, lbl_1_data_388[i].z);
        Hu3DModelAttrSet(lbl_1_bss_A6[i+11], HU3D_MOTATTR_PAUSE);
        Hu3DMotionTimeSet(lbl_1_bss_A6[i+11], 0.0f);
    }
    lbl_1_bss_98 = MgTimerCreate(MGTIMER_TYPE_NORMAL);
    MgTimerPosSet(lbl_1_bss_98, 288.0f, 64.0f);
    lbl_1_bss_94 = 0;
    Hu3DCameraPosSetV(1, &lbl_1_bss_7C, &lbl_1_bss_70, &lbl_1_bss_64);
    HuPrcVSleep();
    lbl_1_bss_90 = Hu3DModelCameraCreate(lbl_1_bss_92, 1);
    Hu3DMotionSpeedSet(lbl_1_bss_90, 1.0f);
    Hu3DCameraMotionStart(lbl_1_bss_90, 1);
    for(i=0; i<4; i++) {
        work = lbl_1_bss_C8[i]->data;
        work->mode = 0;
    }
    kupa = lbl_1_bss_C4[0]->data;
    kupa->mode = 0;
    fn_1_5D6C();
    MgSeqModeNext();
}

/* asm 2398-2495, 86 insns. MGSEQ fade-in hook: the opening, timed to the camera motion. */
void fn_1_23BC(s16 mode, s16 frameNo)
{
    s32 i;
    s32 j;
    M561_PLAYER *work;

    for(i=0; i<30; i++) {
        HuPrcVSleep();
    }
    for(i=0; i<lbl_1_bss_8C; i++) {
        if(i == 285) {
            Hu3DModelAttrReset(lbl_1_bss_A6[3], HU3D_MOTATTR_PAUSE);
        }
        if(i == 320) {
            HuAudFXPlay(2452);
        }
        if(i == 335) {
            for(j=0; j<4; j++) {
                work = lbl_1_bss_C8[j]->data;
                omVibrate(work->no, 15, 12, 0);
            }
        }
        if(i == 355) {
            HuAudFXPlay(2456);
        }
        HuPrcVSleep();
    }
    Hu3DCameraPosGet(1, &lbl_1_bss_7C, &lbl_1_bss_70, &lbl_1_bss_64);
    Hu3DModelKill(lbl_1_bss_90);
    HuPrcVSleep();
    MgSeqModeNext();
}

/* asm 2498-2728, 211 insns. MGSEQ main hook. */
void fn_1_2514(s16 mode, s16 frameNo)
{
    M561_KUPA *kupa = lbl_1_bss_C4[0]->data;
    s32 i;
    s32 k;
    M561_PLAYER *work;
    s32 j;
    M561_PLAYER *other;
    M561_PLAYER *workA[4];
    M561_PLAYER *workB[4];

    fn_1_3210();
    if(MgSeqFrameNoGet() == 0) {
        Hu3DModelAttrSet(lbl_1_bss_A6[4], HU3D_MOTATTR_LOOP);
        Hu3DModelAttrReset(lbl_1_bss_A6[4], HU3D_MOTATTR_PAUSE);
        Hu3DModelAttrSet(lbl_1_bss_A6[3], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrReset(lbl_1_bss_A6[4], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_A6[5], HU3D_ATTR_DISPOFF);
        Hu3DModelAttrSet(lbl_1_bss_A6[6], HU3D_ATTR_DISPOFF);
        for(i=0; i<4; i++) {
            work = lbl_1_bss_C8[i]->data;
            work->mode = 2;
            fn_1_2B50(lbl_1_bss_C8[work->no], 0, 8.0f, HU3D_MOTATTR_LOOP);
        }
        MgTimerParamSet(lbl_1_bss_98, 300, 0, 0);
        MgTimerModeOnSet(lbl_1_bss_98, 1);
    }
    if(MgTimerDoneCheck(lbl_1_bss_98) || fn_1_5A88()) {
        if(lbl_1_bss_98->stopF == 0) {
            lbl_1_bss_98->stopF = 1;
            lbl_1_bss_98->mode = 1;
        }
        lbl_1_bss_94 = 0;
        for(j=0; j<4; j++) {
            other = lbl_1_bss_C8[j]->data;
            if(other->unk80 == 0) {
                other->btn = lbl_1_data_46C[frandmod(3)];
            }
        }
        for(i=0; i<4; i++) {
            workA[i] = lbl_1_bss_C8[i]->data;
        }
        for(k=0; k<4; k++) {
            workB[k] = lbl_1_bss_C8[k]->data;
        }
        while(1) {
            if(workB[0]->mode == 7 && workB[1]->mode == 7 && workB[2]->mode == 7 && workB[3]->mode == 7) {
                break;
            }
            HuPrcVSleep();
        }
        kupa->mode = 2;
        kupa->pos.x = lbl_1_data_358.x;
        kupa->pos.y = lbl_1_data_358.y;
        kupa->pos.z = lbl_1_data_358.z;
        do {
            HuPrcVSleep();
        } while(kupa->mode != 12);
        MgSeqModeNext();
    } else {
        lbl_1_bss_94 = 1;
    }
}

/* asm 2731-2748, 15 insns. MGSEQ finish hook. */
void fn_1_2860(s16 mode, s16 frameNo)
{
    if(MgSeqFrameNoGet() == 0) {
        fn_1_5D9C();
        MgTimerKill(lbl_1_bss_98);
    }
}

/* asm 2751-2820, 60 insns. MGSEQ pre-winner hook. */
void fn_1_289C(s16 mode, s16 frameNo)
{
    M561_KUPA *kupa = lbl_1_bss_C4[0]->data;
    s32 i;

    fn_1_5684();
    if(lbl_1_bss_0 == 0) {
        for(i=0; i<30; i++) {
            HuPrcVSleep();
        }
    } else {
        for(i=0; i<(s32)(60.0f*lbl_1_bss_0); i++) {
            HuPrcVSleep();
        }
        for(i=0; i<30; i++) {
            HuPrcVSleep();
        }
    }
    MgSeqModeNext();
}

/* asm 2823-2947, 113 insns. MGSEQ winner hook: 10 coins to each player not caught. */
void fn_1_298C(s16 mode, s16 frameNo)
{
    s32 i;
    M561_KUPA *kupa = lbl_1_bss_C4[0]->data;
    M561_PLAYER *work;
    s32 no;

    if(MgSeqFrameNoGet() == 0) {
        for(i=0; i<4; i++) {
            work = lbl_1_bss_C8[i]->data;
            if(work->unk84 == 0) {
                no = work->no;
                if(!_CheckFlag(FLAG_MG_PRACTICE)) {
                    GwPlayer[no].mgCoinBonus = 10;
                }
            }
        }
        if(lbl_1_bss_0 == 0) {
            kupa->mode = 13;
            HuAudFXPlayPan(713, fn_1_6078(&kupa->pos));
            HuAudJinglePlay(122);
        } else if(lbl_1_bss_0 == 4) {
            kupa->mode = 14;
            HuAudFXPlayPan(714, fn_1_6078(&kupa->pos));
            HuAudJinglePlay(123);
        } else {
            kupa->mode = 13;
            HuAudFXPlayPan(713, fn_1_6078(&kupa->pos));
            HuAudJinglePlay(122);
        }
        for(i=0; i<4; i++) {
            work = lbl_1_bss_C8[i]->data;
            if(work->unk84 == 0) {
                fn_1_2B50(lbl_1_bss_C8[i], 2, 8.0f, HU3D_MOTATTR_NONE);
            }
        }
    }
}

/* asm 2950-2987, 35 insns. Player motion shift (m559 fn_1_2948). */
void fn_1_2B50(OMOBJ *obj, s32 motNo, float shift, u32 attr)
{
    M561_PLAYER *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        CharMotionShiftSet(work->charNo, obj->mtnId[work->motNo], 0.0f, shift, attr);
    }
}

/* asm 2990-3020, 28 insns. Player motion set, no shift. */
void fn_1_2BDC(OMOBJ *obj, s32 motNo)
{
    M561_PLAYER *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        CharMotionSet(work->charNo, obj->mtnId[work->motNo]);
    }
}

/*
 * asm 3023-3214, 184 insns. Push players apart (m560's M560PlayerHitCheck with
 * a lower-numbered-player rule and no recursion): within 160 in XZ, a player
 * numbered above the other goes to mode 6 instead of pushing.
 */
void fn_1_2C4C(OMOBJ *obj)
{
    M561_PLAYER *work = obj->data;
    M561_PLAYER *other;
    HuVecF vel;
    HuVecF dir;
    HuVecF posA;
    HuVecF posB;
    float speedA;
    float speedB;
    float overlap;
    float ratio;
    s32 i;

    PSVECSubtract(&work->pos, &work->unk40, &vel);
    speedA = PSVECMag(&vel);
    if(0.0f == speedA) {
        return;
    }
    for(i=0; i<4; i++) {
        if(i == work->no) {
            continue;
        }
        other = lbl_1_bss_C8[i]->data;
        posA.x = work->pos.x;
        posA.y = work->pos.y;
        posA.z = work->pos.z;
        posA.y = 0.0f;
        posB.x = other->pos.x;
        posB.y = other->pos.y;
        posB.z = other->pos.z;
        posB.y = 0.0f;
        PSVECSubtract(&posA, &posB, &vel);
        overlap = PSVECMag(&vel);
        if(overlap >= 159.2f) {
            continue;
        }
        if(work->no > other->no) {
            work->mode = 6;
            return;
        }
        PSVECSubtract(&other->pos, &other->unk40, &vel);
        speedB = PSVECMag(&vel);
        PSVECSubtract(&posA, &posB, &dir);
        PSVECNormalize(&dir, &dir);
        overlap = 160.0f-overlap;
        ratio = ((0.6f*speedB)+(0.4f*speedA))/(speedA+speedB);
        work->pos.x += ratio*(overlap*dir.x);
        work->pos.y += ratio*(overlap*dir.y);
        work->pos.z += ratio*(overlap*dir.z);
        if(other->mode == 3 || other->mode == 6) {
            ratio = ((0.6f*speedA)+(0.4f*speedA))/(speedA+speedB);
            other->pos.x += ratio*(overlap*-dir.x);
            other->pos.y += ratio*(overlap*-dir.y);
            other->pos.z += ratio*(overlap*-dir.z);
        }
    }
}

/* Squared XZ distance under a radius, the way the object inlines it. */
static inline s32 fn_1_DistCheck(HuVecF *a, HuVecF *b, float radius2)
{
    if(((a->x-b->x)*(a->x-b->x))+((a->z-b->z)*(a->z-b->z)) < radius2) {
        return 1;
    }
    return 0;
}

/* asm 3217-3410, 185 insns. Keep a player out of the three pillars (radius 330). */
void fn_1_2F2C(OMOBJ *obj)
{
    M561_PLAYER *work = obj->data;
    s32 i;
    HuVecF pos;
    float dx;
    float dz;
    float dist;

    for(i=0; i<3; i++) {
        if(work->unk7C == i) {
            continue;
        }
        pos.x = lbl_1_data_388[i].x;
        pos.y = lbl_1_data_388[i].y;
        pos.z = lbl_1_data_388[i].z;
        dx = work->pos.x-lbl_1_data_388[i].x;
        dz = work->pos.z-lbl_1_data_388[i].z;
        dist = sqrtf((dx*dx)+(dz*dz));
        if(fn_1_DistCheck(&work->pos, &pos, 108900.0f)) {
            dx /= dist;
            dz /= dist;
            work->pos.x = (330.0f*dx)+lbl_1_data_388[i].x;
            work->pos.z = (330.0f*dz)+lbl_1_data_388[i].z;
        }
    }
}

/* asm 3413-3415, 1 insn. Empty. */
void fn_1_3210(void)
{
}

/* asm 3418-3660, 240 insns. Unreferenced: debug camera readout (m559 fn_1_2CA8). */
void fn_1_3214(void)
{
    GXColor color;

    color.r = 0;
    color.g = 0;
    color.b = 144;
    color.a = 192;
    CZoom += HuPadTrigL[0] / 5;
    CZoom -= HuPadTrigR[0] / 5;
    Center.x += 10.0f * (HuPadSubStkX[0] / 59.0f);
    Center.z -= 10.0f * (HuPadSubStkY[0] / 59.0f);
    CRot.x += 5.0f * (HuPadSubStkY[1] / 59.0f);
    CRot.y -= 5.0f * (HuPadSubStkX[1] / 59.0f);
    printWin(16, 40, 384, 36, &color);
    fontcolor = 14;
    print8(16, 40, 1.5f, "Center X:%.02f Y:%.02f Z:%.02f", Center.x, Center.y, Center.z);
    print8(16, 52, 1.5f, "CRot X:%.02f Y:%.02f Z:%.02f", CRot.x, CRot.y, CRot.z);
    print8(16, 64, 1.5f, "CZoom:%.02f", CZoom);
    if(HuPadBtnDown[0] & PAD_BUTTON_X) {
        omCameraViewSet(&lbl_1_data_2D0);
    }
}

/* asm 3663-3864, 198 insns. Bowser object init. */
void fn_1_35D4(OMOBJ *obj)
{
    M561_KUPA *work = obj->data;
    s32 i;

    obj->mdlId[0] = Hu3DModelCreate(HuDataSelHeapReadNum(DATANUM(DATA_m561, 0x00), HU_MEMNUM_OVL, HEAP_MODEL));
    for(i=0; i<9; i++) {
        obj->mtnId[i] = Hu3DJointMotion(obj->mdlId[0], HuDataSelHeapReadNum(lbl_1_data_48[i], HU_MEMNUM_OVL, HEAP_MODEL));
    }
    work->motNo = 9;
    fn_1_5394(obj, 0, 0.0f, HU3D_MOTATTR_LOOP);
    work->unk00 = obj->mdlId[0];
    work->pos.x = lbl_1_data_34C.x;
    work->pos.y = lbl_1_data_34C.y;
    work->pos.z = lbl_1_data_34C.z;
    work->rot.x = 0.0f;
    work->rot.y = 0.0f;
    work->rot.z = 0.0f;
    work->mode = 1;
    work->timer = 0;
    work->motTime = 0.0f;
    work->unk44 = -1;
    work->unk38 = 0;
    work->unk3C = 0.0f;
    work->unk58 = 0;
    work->unk5C = 0;
    work->unk44 = fn_1_8A18(NULL, NULL, 128);
    work->unk48 = fn_1_8A18(NULL, NULL, 10);
    Hu3DModelShadowSet(obj->mdlId[0]);
    omSetSca(obj, 1.5f, 1.5f, 1.5f);
    obj->objFunc = fn_1_38EC;
}

/*
 * asm 3867-5662, 1,706 insns. Bowser. Modes 0 fly in along lbl_1_data_29C,
 * 1 idle, 2-3 land and shake the stage, 4 walk forward, 5 wait, 8 pause, 6
 * turn to a side, 9/10/11 the three attacks, 7 turn to the middle, 13/14 the
 * end poses. Its two fire billboards (unk44, unk48) are fed and torn down
 * after the switch; fn_1_6F3C, fn_1_87B8 and fn_1_86FC are inlined there.
 */
void fn_1_38EC(OMOBJ *obj)
{
    Mtx mtx;
    Mtx mtxHand;
    Mtx mtxHead;
    Mtx mtxHand2;
    Mtx mtxHead2;
    HuVecF posHand;
    HuVecF posHead;
    HuVecF dir;
    M561_PLAYER *player;
    BOOL fireF = FALSE;
    BOOL fireF2 = FALSE;
    HuVecF flameL = { -80.0f, 0.0f, 70.0f };
    HuVecF flameR = { 80.0f, 0.0f, 70.0f };
    HuVecF flamePosL;
    HuVecF flamePosR;
    M561_KUPA *work;
    float motTime;
    float angle;
    s32 i;

    work = obj->data;
    switch(work->mode) {
        case 0:
            Hu3DMotionSpeedSet(obj->mdlId[0], 0.8f);
            fn_1_5394(obj, 8, 8.0f, HU3D_MOTATTR_LOOP);
            motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
            if(work->motTime < 10.0f && motTime >= 10.0f) {
                if(work->motNo == 8) {
                    HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                }
                PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                PSMTXMultVec(mtx, &flameL, &flamePosL);
                PSVECAdd(&flamePosL, &work->pos, &flamePosL);
                fn_1_8BCC(1, &flamePosL);
            } else if(work->motTime < 60.0f && motTime >= 60.0f) {
                if(work->motNo == 8) {
                    HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                }
                PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                PSMTXMultVec(mtx, &flameR, &flamePosR);
                PSVECAdd(&flamePosR, &work->pos, &flamePosR);
                fn_1_8BCC(1, &flamePosR);
            }
            work->speed.x = (lbl_1_data_29C[work->unk38].pos.x-work->pos.x)/(lbl_1_data_29C[work->unk38].time-work->unk3C);
            work->speed.y = (lbl_1_data_29C[work->unk38].pos.y-work->pos.y)/(lbl_1_data_29C[work->unk38].time-work->unk3C);
            work->speed.z = (lbl_1_data_29C[work->unk38].pos.z-work->pos.z)/(lbl_1_data_29C[work->unk38].time-work->unk3C);
            work->pos.x += work->speed.x;
            work->pos.y += work->speed.y;
            work->pos.z += work->speed.z;
            work->unk3C += 1.0f;
            if(work->unk3C >= lbl_1_data_29C[work->unk38].time) {
                work->unk38++;
                if(work->unk38 > 2) {
                    work->mode = 1;
                    work->speed.x = work->speed.y = work->speed.z = 0.0f;
                }
            } else {
                work->motTime = motTime;
            }
            break;

        case 1:
            Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
            fn_1_5394(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            break;

        case 2:
            if(work->timer > 30) {
                work->timer = 0;
                work->mode = 3;
                fn_1_5394(obj, 7, 8.0f, HU3D_MOTATTR_NONE);
            } else {
                work->timer++;
            }
            break;

        case 3:
            Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
            if(work->timer > 80) {
                work->timer = 0;
                work->mode = 4;
                fn_1_5394(obj, 8, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                if(work->timer == 30) {
                    fn_1_5DCC(30, 5.0f, 0.95f, 90.0f, 2);
                    for(i=0; i<4; i++) {
                        player = lbl_1_bss_C8[i]->data;
                        omVibrate(player->no, 15, 12, 0);
                    }
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(lbl_1_bss_A6[5], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrReset(lbl_1_bss_A6[6], HU3D_MOTATTR_PAUSE);
                    Hu3DModelAttrSet(lbl_1_bss_A6[3], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrSet(lbl_1_bss_A6[4], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_A6[5], HU3D_ATTR_DISPOFF);
                    Hu3DModelAttrReset(lbl_1_bss_A6[6], HU3D_ATTR_DISPOFF);
                    HuAudFXPlay(0x996);
                    HuAudFXPlay(0x999);
                } else if(work->timer == 50) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                }
                work->timer++;
            }
            break;

        case 4:
            Hu3DMotionSpeedSet(obj->mdlId[0], 0.8f);
            motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
            if(work->timer > 215) {
                work->timer = 0;
                work->mode = 5;
                fn_1_5394(obj, 3, 8.0f, HU3D_MOTATTR_NONE);
            } else {
                if(work->motTime < 10.0f && motTime >= 10.0f) {
                    if(work->motNo == 8) {
                        fn_1_5DCC(60, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                    PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                    PSMTXMultVec(mtx, &flameL, &flamePosL);
                    PSVECAdd(&flamePosL, &work->pos, &flamePosL);
                    fn_1_8BCC(1, &flamePosL);
                } else if(work->motTime < 60.0f && motTime >= 60.0f) {
                    if(work->motNo == 8) {
                        fn_1_5DCC(60, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                    PSMTXRotRad(mtx, 'Y', 0.017453292f*work->rot.y);
                    PSMTXMultVec(mtx, &flameR, &flamePosR);
                    PSVECAdd(&flamePosR, &work->pos, &flamePosR);
                    fn_1_8BCC(1, &flamePosR);
                }
                work->timer++;
                work->pos.z += 3.2558138f;
            }
            work->motTime = motTime;
            break;

        case 5:
            if(work->timer > 140) {
                work->timer = 0;
                work->mode = 8;
                fn_1_5394(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
                work->unk50 = 1;
                work->unk4C = fn_1_5428();
                work->unk54 = 0;
            } else {
                Hu3DMotionSpeedSet(obj->mdlId[0], 1.0f);
                work->timer++;
            }
            break;

        case 8:
            if(work->timer > 30) {
                work->timer = 0;
                work->mode = 6;
            } else {
                work->timer++;
            }
            break;

        case 6:
            if(work->timer > 130) {
                work->timer = 0;
                if(work->unk54 == 0) {
                    if(work->unk58 == 0) {
                        if(frandmod(10) >= 5) {
                            work->mode = 9;
                        } else {
                            work->mode = 11;
                        }
                    } else {
                        work->mode = 11;
                    }
                } else if(work->unk54 == 1) {
                    if(work->unk5C == 0) {
                        if(frandmod(10) >= 5) {
                            work->mode = 10;
                        } else {
                            work->mode = 11;
                        }
                    } else {
                        work->mode = 11;
                    }
                }
                work->rot.y = lbl_1_data_2C4[work->unk4C];
            } else {
                work->unk28 = fn_1_54BC(lbl_1_data_2C4[work->unk50], lbl_1_data_2C4[work->unk4C], 130);
                motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
                if(0.0f == work->unk28) {
                    work->timer = 130;
                    work->motNo = -1;
                } else {
                    fn_1_5394(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
                }
                if(work->motTime < 25.0f && motTime >= 25.0f) {
                    if(work->motNo == 1) {
                        fn_1_5DCC(30, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                } else if(work->motTime < 75.0f && motTime >= 75.0f) {
                    if(work->motNo == 1) {
                        fn_1_5DCC(30, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                }
                work->rot.y += work->unk28;
                work->timer++;
            }
            work->motTime = motTime;
            break;

        case 9:
            fn_1_5394(obj, 4, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 80) {
                work->timer = 0;
                work->mode = 8;
                work->unk50 = work->unk4C;
                work->unk4C = fn_1_5428();
                work->unk58 = 1;
            } else {
                if(work->timer == 50) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                } else if(work->timer == 60) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                }
                work->timer++;
            }
            break;

        case 10:
            fn_1_5394(obj, 4, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 80) {
                work->timer = 0;
                work->mode = 8;
                work->unk50 = work->unk4C;
                work->unk4C = fn_1_5428();
                work->unk5C = 1;
            } else {
                if(work->timer == 50) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF2 = TRUE;
                    if(lbl_1_data_20 < 0) {
                        lbl_1_data_20 = HuAudFXPlayPan(0x997, fn_1_6170());
                    }
                } else if(work->timer == 80) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF2 = FALSE;
                    if(lbl_1_data_20 > 0) {
                        HuAudFXStop(lbl_1_data_20);
                        lbl_1_data_20 = -1;
                    }
                }
                work->timer++;
            }
            break;

        case 11:
            fn_1_5394(obj, 4, 8.0f, HU3D_MOTATTR_NONE);
            if(work->timer > 200) {
                if(lbl_1_data_1C > 0) {
                    HuAudFXStop(lbl_1_data_1C);
                    lbl_1_data_1C = -1;
                }
                work->timer = 0;
                fn_1_5394(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
                work->unk54++;
                if(work->unk54 == 2) {
                    work->mode = 7;
                    work->unk50 = work->unk4C;
                    work->unk4C = 1;
                } else if(fn_1_5B20()) {
                    work->mode = 7;
                    work->unk50 = work->unk4C;
                    work->unk4C = 1;
                } else {
                    work->mode = 8;
                    work->unk50 = work->unk4C;
                    work->unk4C = fn_1_5428();
                }
            } else {
                if(work->timer >= 50) {
                    Hu3DModelAttrSet(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF = TRUE;
                    if(lbl_1_data_1C < 0) {
                        lbl_1_data_1C = HuAudFXPlayPan(0x97B, fn_1_6170());
                    }
                    if(work->timer == 80) {
                        Hu3DModelAttrReset(lbl_1_bss_A6[work->unk4C+8], HU3D_MOTATTR_PAUSE);
                        Hu3DModelAttrReset(lbl_1_bss_A6[work->unk4C+11], HU3D_MOTATTR_PAUSE);
                        fn_1_55E0(work->unk4C);
                        lbl_1_bss_10[work->unk4C] = 1;
                    }
                } else if(work->timer == 170) {
                    Hu3DModelAttrReset(obj->mdlId[0], HU3D_MOTATTR_PAUSE);
                    fireF = FALSE;
                }
                work->timer++;
            }
            break;

        case 7:
            fn_1_5394(obj, 1, 8.0f, HU3D_MOTATTR_LOOP);
            if(work->timer > 130) {
                work->timer = 0;
                work->rot.y = lbl_1_data_2C4[work->unk4C];
                work->mode = 12;
                fn_1_5394(obj, 0, 8.0f, HU3D_MOTATTR_LOOP);
            } else {
                work->unk28 = fn_1_54BC(lbl_1_data_2C4[work->unk50], lbl_1_data_2C4[work->unk4C], 130);
                motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
                if(0.0f == work->unk28) {
                    work->timer = 130;
                }
                if(work->motTime < 25.0f && motTime >= 25.0f) {
                    if(work->motNo == 1) {
                        fn_1_5DCC(30, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                } else if(work->motTime < 75.0f && motTime >= 75.0f) {
                    if(work->motNo == 1) {
                        fn_1_5DCC(30, 2.0f, 0.75f, 90.0f, 1);
                        HuAudFXPlayVolPan(0x2C7, fn_1_60F4(&work->pos), fn_1_6078(&work->pos));
                    }
                }
                work->rot.y += work->unk28;
                work->timer++;
            }
            work->motTime = motTime;
            break;

        case 12:
            break;

        case 13:
            fn_1_5394(obj, 5, 8.0f, HU3D_MOTATTR_NONE);
            break;

        case 14:
            fn_1_5394(obj, 6, 8.0f, HU3D_MOTATTR_NONE);
            break;
    }
    if(work->unk44 >= 0) {
        if(fireF) {
            fn_1_6F3C(obj->mdlId[0], "g000m0-itemhook_M", &posHand);
            fn_1_6F3C(obj->mdlId[0], "g000m0-ns_hed", &posHead);
            PSVECSubtract(&posHand, &posHead, &dir);
            angle = 180.0*(atan2(dir.x, dir.z)/M_PI);
            fn_1_87B8(work->unk44, 1, &posHand, angle, 750.0f, 50.0f);
        }
        if(fn_1_86FC(work->unk44)) {
            work->unk44 = -1;
        }
    }
    if(work->unk48 >= 0) {
        if(fireF2) {
            fn_1_6F3C(obj->mdlId[0], "g000m0-itemhook_M", &posHand);
            fn_1_6F3C(obj->mdlId[0], "g000m0-ns_hed", &posHead);
            PSVECSubtract(&posHand, &posHead, &dir);
            angle = 180.0*(atan2(dir.x, dir.z)/M_PI);
            fn_1_87B8(work->unk48, 1, &posHand, angle, 350.0f, 50.0f);
        }
        if(fn_1_86FC(work->unk48)) {
            work->unk48 = -1;
        }
    }
    fn_1_5E28();
    omSetTra(obj, work->pos.x, work->pos.y, work->pos.z);
    omSetRot(obj, work->rot.x, work->rot.y, work->rot.z);
}

/* asm 5665-5704, 37 insns. Shift Bowser into a motion, once, and note the motion time. */
void fn_1_5394(OMOBJ *obj, s32 motNo, float shift, u32 attr)
{
    M561_KUPA *work = obj->data;

    if(work->motNo != motNo) {
        work->motNo = motNo;
        Hu3DMotionShiftSet(obj->mdlId[0], obj->mtnId[motNo], 0.0f, shift, attr);
        work->motTime = Hu3DMotionTimeGet(obj->mdlId[0]);
    }
}

/* asm 5707-5747, 37 insns. A random side still free in lbl_1_bss_10, or -1 when all three are taken. */
s32 fn_1_5428(void)
{
    s32 side;

    if(lbl_1_bss_10[0] && lbl_1_bss_10[1] && lbl_1_bss_10[2]) {
        return -1;
    }
    do {
        side = frandmod(3);
    } while(lbl_1_bss_10[side]);
    return side;
}

/* asm 5750-5828, 73 insns. = m559 fn_1_5308: the per-frame step of the shorter turn from `from` to `to` degrees. */
float fn_1_54BC(s32 from, s32 to, s32 time)
{
    float delta;
    float step;

    if(from == to) {
        return 0.0f;
    }
    delta = fmod(to - from, 360.0);
    if(0.0f > delta) {
        delta += 360.0f;
    }
    if(180.0f < delta) {
        delta -= 360.0f;
    }
    step = delta / time;
    return step;
}

/* asm 5831-5876, 41 insns. Knock off every player standing on `side`, 30 frames apart. */
void fn_1_55E0(s32 side)
{
    M561_PLAYER *player;
    s32 i;
    s32 count;

    for(i=0, count=0; i<4; i++) {
        player = lbl_1_bss_C8[i]->data;
        if(player->unk7C == side) {
            player->unkA4 = count*30;
            player->unkA0 = 0;
            count++;
            player->mode = 8;
            player->unk5C = 0.0f;
            player->unk58 = player->pos.y;
            player->timer = 0;
            player->unk84 = 1;
        }
    }
}

/* asm 5879-6055, 165 insns. Line up the players of the first free side on their marks. */
void fn_1_5684(void)
{
    M561_PLAYER *player;
    s32 i;
    s32 j;
    s32 side;

    for(i=0; i<3; i++) {
        if(lbl_1_bss_10[i] == 0) {
            side = i;
            break;
        }
    }
    for(i=0, j=0; i<4; i++) {
        player = lbl_1_bss_C8[i]->data;
        if(player->unk7C == side) {
            player->unkA4 = j*60;
            player->unkA0 = 0;
            j++;
            player->mode = 10;
            player->unk5C = 0.0f;
            player->unk58 = player->pos.y;
            player->timer = 0;
        }
    }
    lbl_1_bss_0 = j;
    for(i=0, j=0; i<4; i++) {
        player = lbl_1_bss_C8[i]->data;
        if(player->unk7C == side) {
            player->unk60 = fn_1_5918(player->pos.x, player->pos.z, lbl_1_data_3AC[lbl_1_bss_0-1][j].x, lbl_1_data_3AC[lbl_1_bss_0-1][j].z);
            player->unk3C->x = lbl_1_data_3AC[lbl_1_bss_0-1][j].x;
            player->unk3C->y = 0.0f;
            player->unk3C->z = lbl_1_data_3AC[lbl_1_bss_0-1][j].z;
            player->unk64.x = player->unk3C->x-player->pos.x;
            player->unk64.y = 0.0f;
            player->unk64.z = player->unk3C->z-player->pos.z;
            PSVECNormalize(&player->unk64, &player->unk64);
            player->rot.y = 180.0*(atan2(player->unk64.x, player->unk64.z)/M_PI);
            j++;
        }
    }
}

/* asm 6058-6153, 92 insns. The distance between two points in XZ (m573 fn_1_8694). */
float fn_1_5918(float ax, float az, float bx, float bz)
{
    float dx;
    float dz;
    float d;

    dx = ax-bx;
    dz = az-bz;
    d = HuMagPoint2D(dx, dz);
    return d;
}

/* asm 6156-6199, 38 insns. TRUE once every player is in mode 7. */
s32 fn_1_5A88(void)
{
    M561_PLAYER *player[4];
    s32 i;

    for(i=0; i<4; i++) {
        player[i] = lbl_1_bss_C8[i]->data;
    }
    if(player[0]->mode == 7 && player[1]->mode == 7 && player[2]->mode == 7 && player[3]->mode == 7) {
        return 1;
    }
    return 0;
}

/* 38 insns. TRUE once every player's unk84 is set. */
s32 fn_1_5B20(void)
{
    M561_PLAYER *player[4];
    s32 i;

    for(i=0; i<4; i++) {
        player[i] = lbl_1_bss_C8[i]->data;
    }
    if(player[0]->unk84 != 0 && player[1]->unk84 != 0 && player[2]->unk84 != 0 && player[3]->unk84 != 0) {
        return 1;
    }
    return 0;
}

/* 36 insns. FALSE while a teammate in mode 5 is still under 90. */
s32 fn_1_5BB8(M561_PLAYER *self)
{
    M561_PLAYER *player;
    s32 i;

    for(i=0; i<4; i++) {
        player = lbl_1_bss_C8[i]->data;
        if(self != player && player->mode == 5 && self->unk7C == player->unk7C && player->unk5C < 90.0f) {
            return 0;
        }
    }
    return 1;
}

/* 68 insns. The per-frame step that turns angle `from` to `to` the short way in `time` frames. */
float fn_1_5C48(float from, float to, s32 time)
{
    float diff;
    float step;

    if(from == to) {
        return 0.0f;
    }
    diff = fmod(to-from, 360.0);
    if(0.0f > diff) {
        diff += 360.0f;
    }
    if(180.0f < diff) {
        diff -= 360.0f;
    }
    step = diff/time;
    return step;
}

/* 5 insns. (m573 fn_1_83C8) */
void fn_1_5D58(void)
{
    lbl_1_bss_88 = -1;
}

/* 12 insns. (m560 fn_1_3830) */
void fn_1_5D6C(void)
{
    lbl_1_bss_88 = HuAudSStreamPlay(0x3F);
}

/* 12 insns. */
void fn_1_5D9C(void)
{
    HuAudSStreamFadeOut(lbl_1_bss_88, 100);
}

/* 23 insns. Arm the camera shake (m560 fn_1_3890). */
void fn_1_5DCC(u16 time, float amp, float decay, float freq, u16 flag)
{
    lbl_1_bss_3C = time;
    lbl_1_bss_34 = amp;
    lbl_1_bss_30 = decay;
    lbl_1_bss_28 = freq;
    lbl_1_bss_2C = 90.0f;
    lbl_1_bss_20 = flag;
}

/* 148 insns. One frame of the camera shake: flag 2 shakes the target in x and y, flag 1 in y. */
void fn_1_5E28(void)
{
    lbl_1_bss_24 = 0.0f;
    if(lbl_1_bss_3C > 0) {
        lbl_1_bss_24 = lbl_1_bss_34*sin((M_PI*lbl_1_bss_2C)/180.0);
        lbl_1_bss_2C += lbl_1_bss_28;
        lbl_1_bss_34 *= lbl_1_bss_30;
        lbl_1_bss_3C--;
        if(lbl_1_bss_20 == 2) {
            Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_7C.x, lbl_1_bss_7C.y, lbl_1_bss_7C.z, lbl_1_bss_70.x, lbl_1_bss_70.y, lbl_1_bss_70.z, lbl_1_bss_64.x+lbl_1_bss_24, lbl_1_bss_64.y+lbl_1_bss_24, lbl_1_bss_64.z);
        } else if(lbl_1_bss_20 == 1) {
            Hu3DCameraPosSet(HU3D_CAM0, lbl_1_bss_7C.x, lbl_1_bss_7C.y, lbl_1_bss_7C.z, lbl_1_bss_70.x, lbl_1_bss_70.y, lbl_1_bss_70.z, lbl_1_bss_64.x, lbl_1_bss_64.y+lbl_1_bss_24, lbl_1_bss_64.z);
        }
    }
}

/* 31 insns. Stereo pan for a point in the world (m573 fn_1_8840). */
s16 fn_1_6078(HuVecF *pos)
{
    HuVecF scr;
    s16 pan;

    Hu3D3Dto2D(pos, 1, &scr);
    pan = 32.0f+(64.0f*(scr.x/576.0f));
    return pan;
}

/* 31 insns. And its volume, off the screen height (m560 fn_1_3AD4). */
s16 fn_1_60F4(HuVecF *pos)
{
    HuVecF scr;
    s16 vol;

    Hu3D3Dto2D(pos, 1, &scr);
    vol = 64.0f+(63.0f*(scr.y/480.0f));
    return vol;
}

/* 27 insns. 32, 64 or 96 by lbl_1_bss_C4[0]'s unk4C. */
s16 fn_1_6170(void)
{
    M561_KUPA *work;
    s16 value;

    work = lbl_1_bss_C4[0]->data;
    if(work->unk4C == 0) {
        value = 32;
    } else if(work->unk4C == 1) {
        value = 64;
    } else if(work->unk4C == 2) {
        value = 96;
    }
    return value;
}

/* 13 insns. A motion timing hook: a sound on each lagged key. */
void fn_1_61DC(HU3DMODELID modelId, HU3DMOTID motId, BOOL lagF)
{
    if(lagF) {
        HuAudFXPlay(0x995);
    }
}
